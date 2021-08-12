/*
 * Copyright 2021 The Hafnium Authors.
 *
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/BSD-3-Clause.
 */

#pragma once

#define HF_INVALID_VM_ID 0x7fff

/**
 * The bit of the VM ID which indicates whether the VM ID is allocated by the
 * normal world or the secure world.
 */
#define HF_VM_ID_WORLD_MASK 0x8000

/** The special VM ID reserved for the hypervisor in the normal world. */
#define HF_HYPERVISOR_VM_ID 0

/**
 * An offset to use when assigning VM IDs within the current world.
 * The offset from HF_VM_ID_BASE is needed because VM ID `HF_VM_ID_BASE + 0` is
 * reserved for the hypervisor/SPM.
 */
#define HF_VM_ID_OFFSET (HF_VM_ID_BASE + 1)

/** The index of the primary VM, if it exists in this world. */
#define HF_PRIMARY_VM_INDEX 0
#define HF_PRIMARY2_VM_INDEX (HF_PRIMARY_VM_INDEX + 1)

/**
 * The special VM ID reserved for the OS or SPMC running in the trusted
 * execution environment, e.g. secure EL1 or EL2 on AArch64.
 */
#define HF_TEE_VM_ID 0x8000

/**
 * The SPMC VM ID used to reference the SPMC by a SP (at secure virtual FF-A
 * instance), or by the SPMD at secure physical FF-A instance.
 */
#define HF_SPMC_VM_ID 0x8000

/**
 * The SPMD VM ID used to reference the SPMD by the SPMC at secure physical
 * FF-A instance. It may be used to exchange special messages with the SPMC
 * like power management events.
 */
#define HF_SPMD_VM_ID 0xFFFF
