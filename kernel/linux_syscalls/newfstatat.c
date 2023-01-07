#include <lwk/kfs.h>
#include <arch/uaccess.h>
#include <arch-generic/fcntl.h>


int
newfstatat(int       fd,
           uaddr_t   u_pathname, 
           uaddr_t   u_buf,
           int       flags)
{
	char pathname[ MAX_PATHLEN ];
	struct inode * root_inode = NULL;
	struct inode * inode = NULL;

	int ret = -EBADF;

	if( strncpy_from_user( pathname, (void*) u_pathname, sizeof(pathname) ) < 0 ) {
		printk("bad copy from user\n");

		return -EFAULT;
	}

	if ((pathname[0] == '/') ||
	    (fd          == AT_FDCWD)) {
		root_inode = kfs_root;
	} else {
		struct file * root_file = get_current_file(fd);
		
		if (!root_file) {
			return -EBADF;
		}

		root_inode = root_file->inode;
	}

__lock(&_lock);
	
	if (strlen(pathname) != 0) {
		inode = kfs_lookup(root_inode, pathname, 0);
	} else if (flags & AT_EMPTY_PATH) {
		inode = root_inode;
	} else {
		ret = -ENOENT;
		goto out;
	}

	if (inode == NULL) {
		printk(KERN_WARNING
		"Attempting fstat() on fd %d with no backing inode.\n", fd);
	}

	ret = kfs_stat(inode, u_buf);
out:
__unlock(&_lock);
	return ret;

}