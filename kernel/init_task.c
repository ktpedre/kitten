#include <lwk/kernel.h>
#include <lwk/smp.h>
#include <lwk/params.h>
#include <lwk/init.h>
#include <lwk/elf.h>
#include <lwk/kfs.h>
#include <lwk/sched.h>
#include <lwk/initrd.h>

/**
 * Maximum number of arguments and environment variables that may
 * be passed to the init_task.
 */
#define INIT_MAX_ARGC 32
#define INIT_MAX_ENVC 32

/**
 * Maximum length of the init_argv= and init_envp= strings on the
 * kernel boot command line.
 */
#define INIT_ARGV_LEN 1024
#define INIT_ENVP_LEN 1024

/**
 * The init_task ELF executable.
 */
static uint8_t * init_elf_image;

/**
 * Amount of memory to reserve for the init_task's heap.
 */
unsigned long init_heap_size = (1024 * 1024 * 32);  /* 32 MB */
param(init_heap_size, ulong);

/**
 * Amount of memory to reserve for the init_task's stack.
 */
unsigned long init_stack_size = (1024 * 256);  /* 256 KB */
param(init_stack_size, ulong);

/**
 * Arguments to pass to the init_task.
 */
static char init_argv_str[INIT_ARGV_LEN] = { 0 };
param_string(init_argv, init_argv_str, sizeof(init_argv_str));

/**
 * Environment to pass to the init_task.
 */
static char init_envp_str[INIT_ENVP_LEN] = { 0 };
param_string(init_envp, init_envp_str, sizeof(init_envp_str));


static int
__initrd_is_elf(paddr_t initrd_start, 
		paddr_t initrd_end)
{
	uint8_t elf_hdr[4] = {0x7f, 'E', 'L', 'F'}; 

	if (initrd_end - initrd_start <= sizeof(elf_hdr)) {
		return 0;
	} 

	if (memcmp(__va(initrd_start), elf_hdr, sizeof(elf_hdr)) == 0) {
		return 1;
	}

	return 0;
}




/**
 *  Set the up userspace environment using INITRD data
 */
int
setup_userspace(paddr_t initrd_start, 
                paddr_t initrd_end)
{
	if (__initrd_is_elf(initrd_start, initrd_end)) {
		printk("INITRD: ELF executable\n");
		init_elf_image = __va(initrd_start);
	} else if (initrd_is_initrd(initrd_start, initrd_end)) {
		printk("INITRD: INITRD archive\n");
		init_elf_image = unpack_initrd(initrd_start, initrd_end); 

	} else {
		printk("Error: Invalid INITRD format\n");
		return -EINVAL;
	}

	if (init_elf_image == NULL) {
		printk("Error: Invalid INITRD\n");
		return -EINVAL;
	}

	return 0;
}


/**
 * Creates the init_task.
 */
int
create_init_task(void)
{
	int status;
	start_state_t start_state = {
		.task_id	= ANY_ID,
		.task_name	= "init_task",
		.user_id	= 0,
		.group_id	= 0,
		.cpu_id		= ANY_ID,
		.use_args	= false,
	};

	if (!init_elf_image) {
		printk("No init_elf_image found.\n");
		return -EINVAL;
	}
	
	/* This initializes start_state aspace_id, entry_point, and stack_ptr */
	status =
	elf_load(
		init_elf_image,
		start_state.task_name,
		INIT_ASPACE_ID,
		PAGE_SIZE,
		init_heap_size,
		init_stack_size,
		init_argv_str,
		init_envp_str,
		&start_state,
		0,
		&elf_dflt_alloc_pmem
	);
	if (status) {
		printk("Failed to load init_task (status=%d).\n", status);
		return status;
	}

	/* This prevents the address space from being deleted by
	 * user-space, since the kernel never releases this reference */
	if (!aspace_acquire(INIT_ASPACE_ID)) {
		printk("Failed to acquire INIT_ASPACE_ID.\n");
		return status;
	}


	struct task_struct *new_task = __task_create(&start_state, NULL);

	sched_wakeup_task(new_task, TASK_STOPPED);

	return 0;
}



