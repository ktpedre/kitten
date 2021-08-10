/*
 * Copyright 2018 The Hafnium Authors.
 *
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/BSD-3-Clause.
 */

#pragma once

#include <arch/hafnium/abi.h>
#include <arch/hafnium/ffa.h>
#include <arch/hafnium/types.h>

/**
 * This function must be implemented to trigger the architecture-specific
 * mechanism to call to the hypervisor.
 */
int64_t hf_call(uint64_t arg0, uint64_t arg1, uint64_t arg2, uint64_t arg3);
struct ffa_value ffa_call(struct ffa_value args);

/**
 * Returns the VM's own ID.
 */
static inline struct ffa_value ffa_id_get(void)
{
	return ffa_call((struct ffa_value){.func = FFA_ID_GET_32});
}

/**
 * Requests information for partitions instantiated in the system. The
 * information is returned in the RX buffer of the caller as an array of
 * partition information descriptors (struct ffa_partition_info).
 *
 * A Null UUID (UUID that is all zeros) returns information for all partitions,
 * whereas a non-Null UUID returns information only for partitions that match.
 *
 * Returns:
 *  - FFA_SUCCESS on success. The count of partition information descriptors
 *    populated in the RX buffer is returned in arg2 (register w2).
 *  - FFA_BUSY if the caller's RX buffer is not free.
 *  - FFA_NO_MEMORY if the results do not fit in the callers RX buffer.
 *  - FFA_INVALID_PARAMETERS for an unrecognized UUID.
 */
static inline struct ffa_value ffa_partition_info_get(
	const struct ffa_uuid *uuid)
{
	return ffa_call((struct ffa_value){.func = FFA_PARTITION_INFO_GET_32,
					   .arg1 = uuid->uuid[0],
					   .arg2 = uuid->uuid[1],
					   .arg3 = uuid->uuid[2],
					   .arg4 = uuid->uuid[3]});
}

/**
 * Returns the VM's own ID.
 */
static inline ffa_vm_id_t hf_vm_get_id(void)
{
	return ffa_id_get().arg2;
}

/**
 * Runs the given vCPU of the given VM.
 */
static inline struct ffa_value ffa_run(ffa_vm_id_t vm_id,
				       ffa_vcpu_index_t vcpu_idx)
{
	return ffa_call((struct ffa_value){.func = FFA_RUN_32,
					   ffa_vm_vcpu(vm_id, vcpu_idx)});
}

/**
 * Hints that the vCPU is willing to yield its current use of the physical CPU.
 * This call always returns FFA_SUCCESS.
 */
static inline struct ffa_value ffa_yield(void)
{
	return ffa_call((struct ffa_value){.func = FFA_YIELD_32});
}

/**
 * Configures the pages to send/receive data through. The pages must not be
 * shared.
 *
 * Returns:
 *  - FFA_ERROR FFA_INVALID_PARAMETERS if the given addresses are not properly
 *    aligned or are the same.
 *  - FFA_ERROR FFA_NO_MEMORY if the hypervisor was unable to map the buffers
 *    due to insufficient page table memory.
 *  - FFA_ERROR FFA_DENIED if the pages are already mapped or are not owned by
 *    the caller.
 *  - FFA_SUCCESS on success if no further action is needed.
 *  - FFA_RX_RELEASE if it was called by the primary VM and the primary VM now
 *    needs to wake up or kick waiters.
 */
static inline struct ffa_value ffa_rxtx_map(hf_ipaddr_t send, hf_ipaddr_t recv)
{
	return ffa_call(
		(struct ffa_value){.func = FFA_RXTX_MAP_64,
				   .arg1 = send,
				   .arg2 = recv,
				   .arg3 = HF_MAILBOX_SIZE / FFA_PAGE_SIZE});
}

/**
 * Copies data from the sender's send buffer to the recipient's receive buffer.
 *
 * If the recipient's receive buffer is busy, it can optionally register the
 * caller to be notified when the recipient's receive buffer becomes available.
 *
 * Attributes may include:
 *  - FFA_MSG_SEND_NOTIFY, to notify the caller when it should try again.
 *  - FFA_MSG_SEND_LEGACY_MEMORY_*, to send a legacy architected memory sharing
 *    message.
 *
 * Returns FFA_SUCCESS if the message is sent, or an error code otherwise:
 *  - INVALID_PARAMETERS: one or more of the parameters do not conform.
 *  - BUSY: the message could not be delivered either because the mailbox
 *    was full or the target VM is not yet set up.
 */
static inline struct ffa_value ffa_msg_send(ffa_vm_id_t sender_vm_id,
					    ffa_vm_id_t target_vm_id,
					    uint32_t size, uint32_t attributes)
{
	return ffa_call((struct ffa_value){
		.func = FFA_MSG_SEND_32,
		.arg1 = ((uint64_t)sender_vm_id << 16) | target_vm_id,
		.arg3 = size,
		.arg4 = attributes});
}

static inline struct ffa_value ffa_mem_donate(uint32_t length,
					      uint32_t fragment_length)
{
	return ffa_call((struct ffa_value){.func = FFA_MEM_DONATE_32,
					   .arg1 = length,
					   .arg2 = fragment_length});
}

static inline struct ffa_value ffa_mem_lend(uint32_t length,
					    uint32_t fragment_length)
{
	return ffa_call((struct ffa_value){.func = FFA_MEM_LEND_32,
					   .arg1 = length,
					   .arg2 = fragment_length});
}

static inline struct ffa_value ffa_mem_share(uint32_t length,
					     uint32_t fragment_length)
{
	return ffa_call((struct ffa_value){.func = FFA_MEM_SHARE_32,
					   .arg1 = length,
					   .arg2 = fragment_length});
}

static inline struct ffa_value ffa_mem_retrieve_req(uint32_t length,
						    uint32_t fragment_length)
{
	return ffa_call((struct ffa_value){.func = FFA_MEM_RETRIEVE_REQ_32,
					   .arg1 = length,
					   .arg2 = fragment_length});
}

static inline struct ffa_value ffa_mem_relinquish(void)
{
	return ffa_call((struct ffa_value){.func = FFA_MEM_RELINQUISH_32});
}

static inline struct ffa_value ffa_mem_reclaim(ffa_memory_handle_t handle,
					       ffa_memory_region_flags_t flags)
{
	return ffa_call((struct ffa_value){.func = FFA_MEM_RECLAIM_32,
					   .arg1 = (uint32_t)handle,
					   .arg2 = (uint32_t)(handle >> 32),
					   .arg3 = flags});
}

static inline struct ffa_value ffa_mem_frag_rx(ffa_memory_handle_t handle,
					       uint32_t fragment_offset)
{
	/* Note that sender MBZ at virtual instance. */
	return ffa_call((struct ffa_value){.func = FFA_MEM_FRAG_RX_32,
					   .arg1 = (uint32_t)handle,
					   .arg2 = (uint32_t)(handle >> 32),
					   .arg3 = fragment_offset});
}

static inline struct ffa_value ffa_mem_frag_tx(ffa_memory_handle_t handle,
					       uint32_t fragment_length)
{
	/* Note that sender MBZ at virtual instance. */
	return ffa_call((struct ffa_value){.func = FFA_MEM_FRAG_TX_32,
					   .arg1 = (uint32_t)handle,
					   .arg2 = (uint32_t)(handle >> 32),
					   .arg3 = fragment_length});
}

/**
 * Called by secondary VMs to receive a message. This will block until a message
 * is received.
 *
 * The mailbox must be cleared before a new message can be received.
 *
 * If no message is immediately available and there are no enabled and pending
 * interrupts (irrespective of whether interrupts are enabled globally), then
 * this will block until a message is available or an enabled interrupt becomes
 * pending. This matches the behaviour of the WFI instruction on AArch64, except
 * that a message becoming available is also treated like a wake-up event.
 *
 * Returns:
 *  - FFA_MSG_SEND if a message is successfully received.
 *  - FFA_ERROR FFA_NOT_SUPPORTED if called from the primary VM.
 *  - FFA_ERROR FFA_INTERRUPTED if an interrupt happened during the call.
 */
static inline struct ffa_value ffa_msg_wait(void)
{
	return ffa_call((struct ffa_value){.func = FFA_MSG_WAIT_32});
}

/**
 * Called by secondary VMs to receive a message. The call will return whether or
 * not a message is available.
 *
 * The mailbox must be cleared before a new message can be received.
 *
 * Returns:
 *  - FFA_MSG_SEND if a message is successfully received.
 *  - FFA_ERROR FFA_NOT_SUPPORTED if called from the primary VM.
 *  - FFA_ERROR FFA_INTERRUPTED if an interrupt happened during the call.
 *  - FFA_ERROR FFA_RETRY if there was no pending message.
 */
static inline struct ffa_value ffa_msg_poll(void)
{
	return ffa_call((struct ffa_value){.func = FFA_MSG_POLL_32});
}

/**
 * Releases the caller's mailbox so that a new message can be received. The
 * caller must have copied out all data they wish to preserve as new messages
 * will overwrite the old and will arrive asynchronously.
 *
 * Returns:
 *  - FFA_ERROR FFA_DENIED on failure, if the mailbox hasn't been read.
 *  - FFA_SUCCESS on success if no further action is needed.
 *  - FFA_RX_RELEASE if it was called by the primary VM and the primary VM now
 *    needs to wake up or kick waiters. Waiters should be retrieved by calling
 *    hf_mailbox_waiter_get.
 */
static inline struct ffa_value ffa_rx_release(void)
{
	return ffa_call((struct ffa_value){.func = FFA_RX_RELEASE_32});
}

/**
 * Retrieves the next VM whose mailbox became writable. For a VM to be notified
 * by this function, the caller must have called api_mailbox_send before with
 * the notify argument set to true, and this call must have failed because the
 * mailbox was not available.
 *
 * It should be called repeatedly to retrieve a list of VMs.
 *
 * Returns -1 if no VM became writable, or the id of the VM whose mailbox
 * became writable.
 */
static inline int64_t hf_mailbox_writable_get(void)
{
	return hf_call(HF_MAILBOX_WRITABLE_GET, 0, 0, 0);
}

/**
 * Retrieves the next VM waiting to be notified that the mailbox of the
 * specified VM became writable. Only primary VMs are allowed to call this.
 *
 * Returns -1 on failure or if there are no waiters; the VM id of the next
 * waiter otherwise.
 */
static inline int64_t hf_mailbox_waiter_get(ffa_vm_id_t vm_id)
{
	return hf_call(HF_MAILBOX_WAITER_GET, vm_id, 0, 0);
}

/**
 * Enables or disables a given interrupt ID.
 *
 * Returns 0 on success, or -1 if the intid is invalid.
 */
static inline int64_t hf_interrupt_enable(uint32_t intid, bool enable,
					  enum interrupt_type type)
{
	return hf_call(HF_INTERRUPT_ENABLE, intid, enable, type);
}

/**
 * Gets the ID of the pending interrupt (if any) and acknowledge it.
 *
 * Returns HF_INVALID_INTID if there are no pending interrupts.
 */
static inline uint32_t hf_interrupt_get(void)
{
	return hf_call(HF_INTERRUPT_GET, 0, 0, 0);
}

/**
 * Injects a virtual interrupt of the given ID into the given target vCPU.
 * This doesn't cause the vCPU to actually be run immediately; it will be taken
 * when the vCPU is next run, which is up to the scheduler.
 *
 * Returns:
 *  - -1 on failure because the target VM or vCPU doesn't exist, the interrupt
 *    ID is invalid, or the current VM is not allowed to inject interrupts to
 *    the target VM.
 *  - 0 on success if no further action is needed.
 *  - 1 if it was called by the primary VM and the primary VM now needs to wake
 *    up or kick the target vCPU.
 */
static inline int64_t hf_interrupt_inject(ffa_vm_id_t target_vm_id,
					  ffa_vcpu_index_t target_vcpu_idx,
					  uint32_t intid)
{
	return hf_call(HF_INTERRUPT_INJECT, target_vm_id, target_vcpu_idx,
		       intid);
}

/**
 * Sends a character to the debug log for the VM.
 *
 * Returns 0 on success, or -1 if it failed for some reason.
 */
static inline int64_t hf_debug_log(char c)
{
	return hf_call(HF_DEBUG_LOG, c, 0, 0);
}

/** Obtains the Hafnium's version of the implemented FF-A specification. */
static inline int32_t ffa_version(uint32_t requested_version)
{
	return ffa_call((struct ffa_value){.func = FFA_VERSION_32,
					   .arg1 = requested_version})
		.func;
}

/**
 * Discovery function returning information about the implementation of optional
 * FF-A interfaces.
 *
 * Returns:
 *  - FFA_SUCCESS in .func if the optional interface with function_id is
 * implemented.
 *  - FFA_ERROR in .func if the optional interface with function_id is not
 * implemented.
 */
static inline struct ffa_value ffa_features(uint32_t function_id)
{
	return ffa_call((struct ffa_value){.func = FFA_FEATURES_32,
					   .arg1 = function_id});
}

static inline struct ffa_value ffa_msg_send_direct_req(
	ffa_vm_id_t sender_vm_id, ffa_vm_id_t target_vm_id, uint32_t arg3,
	uint32_t arg4, uint32_t arg5, uint32_t arg6, uint32_t arg7)
{
	return ffa_call((struct ffa_value){
		.func = FFA_MSG_SEND_DIRECT_REQ_32,
		.arg1 = ((uint64_t)sender_vm_id << 16) | target_vm_id,
		.arg3 = arg3,
		.arg4 = arg4,
		.arg5 = arg5,
		.arg6 = arg6,
		.arg7 = arg7,
	});
}

static inline struct ffa_value ffa_msg_send_direct_resp(
	ffa_vm_id_t sender_vm_id, ffa_vm_id_t target_vm_id, uint32_t arg3,
	uint32_t arg4, uint32_t arg5, uint32_t arg6, uint32_t arg7)
{
	return ffa_call((struct ffa_value){
		.func = FFA_MSG_SEND_DIRECT_RESP_32,
		.arg1 = ((uint64_t)sender_vm_id << 16) | target_vm_id,
		.arg3 = arg3,
		.arg4 = arg4,
		.arg5 = arg5,
		.arg6 = arg6,
		.arg7 = arg7,
	});
}

static inline uint32_t hf_pin_vm(ffa_vm_id_t target_vm_id, uint64_t cpu_id)
{
	return hf_call(HF_PIN_VM, target_vm_id, cpu_id, 0);
}
