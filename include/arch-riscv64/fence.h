#ifndef _ASM_RISCV_FENCE_H
#define _ASM_RISCV_FENCE_H

#define RISCV_ACQUIRE_BARRIER		"\tfence r , rw\n"
#define RISCV_RELEASE_BARRIER		"\tfence rw,  w\n"

#endif	/* _ASM_RISCV_FENCE_H */
