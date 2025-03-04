#ifndef __HF_H__
#define __HF_H__

#include <lwk/types.h>
#include <lwk/timer.h>

#include <arch/atomic.h>

#include <arch/hafnium/types.h>
#include <arch/hafnium/ffa.h>

#define CONFIG_HAFNIUM_MAX_VMS   (16)
#define CONFIG_HAFNIUM_MAX_VCPUS (32)



struct hf_vcpu {
	struct hf_vm       * vm;
	ffa_vcpu_index_t     vcpu_index;
	struct task_struct * task;
	atomic_t             abort_sleep;
	atomic_t             waiting_for_message;
	struct timer         timer;
};

struct hf_vm {
	ffa_vm_id_t        id;
	ffa_vcpu_count_t   vcpu_count;
	struct hf_vcpu   * vcpu;
};

extern struct hf_vm   * hf_vms;
extern ffa_vm_count_t   hf_vm_count;
extern struct ffa_partition_info* partition_info;

#endif
