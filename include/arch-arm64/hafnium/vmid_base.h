/*
 * Copyright 2020 The Hafnium Authors.
 *
 * Use of this source code is governed by a BSD-style
 * license that can be found in the LICENSE file or at
 * https://opensource.org/licenses/BSD-3-Clause.
 */

#pragma once

#include <arch/hafnium/vm_ids.h>

#if SECURE_WORLD == 1
#define HF_VM_ID_BASE 0x8000
#define HF_OTHER_WORLD_ID HF_HYPERVISOR_VM_ID

/**
 * When running in the secure world, treat the normal world as the primary VM,
 * as it is responsible for scheduling.
 */
#define HF_PRIMARY_VM_ID HF_OTHER_WORLD_ID
#define HF_PRIMARY2_VM_ID (HF_OTHER_WORLD_ID + 1)

#else
#define HF_VM_ID_BASE 0
#define HF_OTHER_WORLD_ID HF_TEE_VM_ID

/**
 * The ID of the primary VM, which is responsible for scheduling.
 *
 * This is not equal to its index because ID 0 is reserved for the hypervisor
 * itself. The primary VM therefore gets ID 1 and all other VMs come after that.
 */
#define HF_PRIMARY_VM_ID (HF_VM_ID_OFFSET + HF_PRIMARY_VM_INDEX)
#define HF_PRIMARY2_VM_ID (HF_PRIMARY_VM_ID + 1)

#endif
