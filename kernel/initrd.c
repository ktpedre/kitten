#include <lwk/kfs.h>
#include <lwk/pmem.h>
#include <arch/uaccess.h>
#include <lwk/ctype.h>
#include <lwk/stat.h>


#define MAX_FILE_SIZE (256 * 1024 * 1024)   /* 256 MB for now... */

struct initrd_file_info {
	uint8_t * data;

	struct mutex fop_mutex; /* We probably want this... */
};


static uint8_t cpio_magic_newc[6] = {'0', '7', '0', '7', '0', '1'};
static uint8_t cpio_magic_crc[6]  = {'0', '7', '0', '7', '0', '2'};

struct cpio_header {
	uint8_t c_magic[6];
	uint8_t c_ino[8];
	uint8_t c_mode[8];
	uint8_t c_uid[8];
	uint8_t c_gid[8];
	uint8_t c_nlink[8];
	uint8_t c_mtime[8];
	uint8_t c_filesize[8];
	uint8_t c_maj[8];
	uint8_t c_min[8];
	uint8_t c_rmaj[8];
	uint8_t c_rmin[8];
	uint8_t c_namesize[8];
	uint8_t c_chksum[8];

} __attribute__((packed));




#define dbg(fmt,args...)
//#define dbg _KDBG

#define PRIV_DATA(x) ((struct initrd_file_info *) x)

int 
initrd_is_initrd(paddr_t initrd_start, 
                 paddr_t initrd_end)
{

	if (initrd_end - initrd_start <= sizeof(cpio_magic_newc)) {
		return 0;
	} 

	if (memcmp(__va(initrd_start), cpio_magic_newc, sizeof(cpio_magic_newc)) == 0) {
		return 1;
	}

	return 0;
}




static int initrd_open(struct inode * inode, struct file * file)
{
	file->pos = 0;
	file->private_data = inode->i_private;

	return 0;
}

static ssize_t
initrd_read(struct file * file,
            char        * buf,
            size_t        len,
            loff_t      * off)
{
	struct initrd_file_info  * file_info = PRIV_DATA(file->private_data);

	len = file->pos + len > file->inode->size ?
	      file->inode->size - file->pos : len;

	if ( copy_to_user(buf, file_info->data + file->pos, len) ) {
		return -EFAULT;
	}

	file->pos += len;

	return len;
}

static ssize_t
initrd_write(struct file * file,
             const char  * buf,
             size_t        len,
             loff_t      * off)
{
	return -EPERM;
}

static ssize_t
initrd_lseek(struct file * file,
             off_t         offset,
             int           whence)
{
//	struct initrd_file_info  * file_info = PRIV_DATA(file->private_data);

	switch ( whence ) {
	    case 0: /* SEEK_SET */
		if ( offset > MAX_FILE_SIZE ) 
			return -EINVAL; 
		file->pos = offset;
		break;

	     case 1: /*  SEEK_CUR */
		if ( file->pos + offset > MAX_FILE_SIZE ) 
			return -EINVAL; 
		file->pos += offset;
		break;

	     case 2: /* SEEK_END */
		file->pos = file->inode->size;
		break;

	     default:
		return -EINVAL;
	}
	return file->pos;
}

static int 
initrd_ioctl(struct file * file,
                int           request,
                uaddr_t       addr	
)
{
	return -EINVAL;
}

static int create(struct inode *inode, int mode)
{
	dbg("\n");
	inode->i_private = kmem_alloc( sizeof( struct initrd_file_info ) );
	inode->size = 0;

	return 0;	
}

static int unlink(struct inode * inode)
{
	//struct initrd_file_info  * file_info = PRIV_DATA(inode->i_private);

	dbg("\n");

	kmem_free( inode->i_private );
	return 0;	
}

struct inode_operations initrd_iops = {
	.create = create,	
	.unlink = unlink,
};

struct kfs_fops initrd_fops = {
	.open  = initrd_open,
	.read  = initrd_read,
	.lseek = initrd_lseek,
	.write = initrd_write,
	.ioctl = initrd_ioctl,
};



static inline uint32_t 
__cpio_hdr_to_u32(uint8_t * val)
{
	uint32_t result = 0;
	int i = 0;

	for (i = 0; i < 8; i++) {
		uint32_t tmp = isdigit(val[i]) ? val[i] - '0' : tolower(val[i]) - 'a' + 10;
		result += (tmp << ((7 - i) * 4)); 
	}

	return result;
}


uint8_t *
unpack_initrd(paddr_t initrd_start, 
              paddr_t initrd_end)
{
	uint8_t * init_exec_ptr = NULL;
	paddr_t offset       = 0;

	while (1) {

		struct cpio_header * hdr = __va(initrd_start + offset);
		
		char    * file_name = NULL;
		uint8_t * file_data = NULL;

		uint32_t name_size  = 0;
		uint32_t data_size  = 0;
		uint32_t file_mode  = 0;


		if (initrd_start + offset >= initrd_end) {
			// End of archive
			break;
		}


		if (memcmp(hdr->c_magic, cpio_magic_newc, sizeof(cpio_magic_newc)) != 0) {
			printk("Error: Invalid CPIO Archive\n");
			return NULL;
		}

		name_size = __cpio_hdr_to_u32(hdr->c_namesize);
		data_size = __cpio_hdr_to_u32(hdr->c_filesize);
		file_mode = __cpio_hdr_to_u32(hdr->c_mode);

		file_name = __va(initrd_start + offset + sizeof(struct cpio_header));
		file_data = __va(ALIGN(initrd_start + offset + sizeof(struct cpio_header) + name_size, 4));


		// printk("CPIO File: %s [size=%d] [mode=%x]\n", file_name, data_size, file_mode);

		if (name_size == 0) {
			printk("CPIO Error: Invalid name length\n");
			return NULL;
		}

		if (strncmp(file_name, "TRAILER!!!", strlen(file_name)) == 0) {
			// end of archive
			break;
		}


		if (S_ISDIR(file_mode)) {
			kfs_mkdir(file_name, file_mode);
		} else if (S_ISREG(file_mode)) {
			struct initrd_file_info * file_info  = NULL;
			struct inode            * file_inode = NULL;

			file_inode = kfs_create(file_name, &initrd_iops, &initrd_fops, file_mode, NULL, 0);

			if (file_inode == NULL) {
				printk("Error: Could not create file from initrd\n");
				return NULL;
			}

			file_info        = PRIV_DATA(file_inode->i_private);
			file_info->data  = file_data;
			file_inode->size = data_size;

			//printk("%s at %p (file_info at %p)\n", file_name, file_data, file_info);

			if (strncmp(file_name, "init", strlen(file_name)) == 0) {
				printk("Found init\n");
				init_exec_ptr = file_data;
			}

		} else if (S_ISLNK(file_mode)) {
			//printk("Symlinks not yet supported\n");
		} else {
			printk("Error: INITRD file type (%o) not supported\n", file_mode & S_IFMT);
		}

		offset += sizeof(struct cpio_header);
		offset += name_size;
		offset  = ALIGN(offset, 4);
		offset += data_size;
		offset  = ALIGN(offset, 4);
	}

	return init_exec_ptr;
}