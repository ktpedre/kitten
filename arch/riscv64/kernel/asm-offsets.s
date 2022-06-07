	.file	"asm-offsets.c"
	.option nopic
# GNU C99 (Buildroot 2022.02.1) version 10.3.0 (riscv64-buildroot-linux-uclibc)
#	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version none
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -nostdinc -I include -I ofed/include
# -isysroot /tmp/buildroot-2022.02.1/output/host/riscv64-buildroot-linux-uclibc/sysroot
# -D __KERNEL__ -D __LWK__ -D __KERNEL__ -D TEXT_OFFSET=0x00080000
# -D KBUILD_STR(s)=#s -D KBUILD_BASENAME=KBUILD_STR(asm_offsets)
# -D KBUILD_MODNAME=KBUILD_STR(asm_offsets)
# -isystem /tmp/buildroot-2022.02.1/output/host/lib/gcc/riscv64-buildroot-linux-uclibc/10.3.0/include
# -include include/lwk/autoconf.h -MD arch/riscv64/kernel/.asm-offsets.s.d
# arch/riscv64/kernel/asm-offsets.c -march=rv64imafd -mabi=lp64d
# -auxbase-strip arch/riscv64/kernel/asm-offsets.s -g -g -O2 -Wall -Wundef
# -Wstrict-prototypes -Wno-trigraphs -Wno-sign-compare
# -Wno-unused-parameter -Wno-pointer-sign -w -std=gnu99
# -fno-strict-aliasing -fno-strict-overflow -fno-common -fno-pie
# -fno-stack-protector -fgnu89-inline -fno-omit-frame-pointer
# -fno-optimize-sibling-calls -fno-builtin -ffunction-sections
# -fno-reorder-blocks -funit-at-a-time -fverbose-asm
# options enabled:  -faggressive-loop-optimizations -falign-functions
# -falign-jumps -falign-labels -falign-loops -fallocation-dce
# -fauto-inc-dec -fbranch-count-reg -fcaller-saves -fcode-hoisting
# -fcombine-stack-adjustments -fcompare-elim -fcprop-registers
# -fcrossjumping -fcse-follow-jumps -fdefer-pop
# -fdelete-null-pointer-checks -fdevirtualize -fdevirtualize-speculatively
# -fdwarf2-cfi-asm -fearly-inlining -feliminate-unused-debug-symbols
# -feliminate-unused-debug-types -fexpensive-optimizations
# -fforward-propagate -ffp-int-builtin-inexact -ffunction-cse
# -ffunction-sections -fgcse -fgcse-lm -fgnu-unique
# -fguess-branch-probability -fhoist-adjacent-loads -fident -fif-conversion
# -fif-conversion2 -findirect-inlining -finline -finline-atomics
# -finline-functions -finline-functions-called-once
# -finline-small-functions -fipa-bit-cp -fipa-cp -fipa-icf
# -fipa-icf-functions -fipa-icf-variables -fipa-profile -fipa-pure-const
# -fipa-ra -fipa-reference -fipa-reference-addressable -fipa-sra
# -fipa-stack-alignment -fipa-vrp -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots
# -fisolate-erroneous-paths-dereference -fivopts -fkeep-static-consts
# -fleading-underscore -flifetime-dse -flra-remat -fmath-errno
# -fmerge-constants -fmerge-debug-strings -fmove-loop-invariants
# -foptimize-strlen -fpartial-inlining -fpeephole -fpeephole2 -fplt
# -fprefetch-loop-arrays -free -freg-struct-return -freorder-functions
# -frerun-cse-after-loop -fsched-critical-path-heuristic
# -fsched-dep-count-heuristic -fsched-group-heuristic -fsched-interblock
# -fsched-last-insn-heuristic -fsched-rank-heuristic -fsched-spec
# -fsched-spec-insn-heuristic -fsched-stalled-insns-dep -fschedule-fusion
# -fschedule-insns -fschedule-insns2 -fsection-anchors
# -fsemantic-interposition -fshow-column -fshrink-wrap
# -fshrink-wrap-separate -fsigned-zeros -fsplit-ivs-in-unroller
# -fsplit-wide-types -fssa-backprop -fssa-phiopt -fstdarg-opt
# -fstore-merging -fstrict-volatile-bitfields -fsync-libcalls
# -fthread-jumps -ftoplevel-reorder -ftrapping-math -ftree-bit-ccp
# -ftree-builtin-call-dce -ftree-ccp -ftree-ch -ftree-coalesce-vars
# -ftree-copy-prop -ftree-cselim -ftree-dce -ftree-dominator-opts
# -ftree-dse -ftree-forwprop -ftree-fre -ftree-loop-if-convert
# -ftree-loop-im -ftree-loop-ivcanon -ftree-loop-optimize
# -ftree-parallelize-loops= -ftree-phiprop -ftree-pre -ftree-pta
# -ftree-reassoc -ftree-scev-cprop -ftree-sink -ftree-slsr -ftree-sra
# -ftree-switch-conversion -ftree-tail-merge -ftree-ter -ftree-vrp
# -funit-at-a-time -fvar-tracking -fvar-tracking-assignments -fverbose-asm
# -fwrapv -fwrapv-pointer -fzero-initialized-in-bss -mdiv -mexplicit-relocs
# -mfdiv -mplt -mstrict-align -muclibc

	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.asm_offsets,"ax",@progbits
	.align	2
	.globl	asm_offsets
	.type	asm_offsets, @function
asm_offsets:
.LFB231:
	.file 1 "arch/riscv64/kernel/asm-offsets.c"
	.loc 1 25 1
	.cfi_startproc
	.loc 1 26 2
# arch/riscv64/kernel/asm-offsets.c:25: {
	.loc 1 25 1 is_stmt 0
	addi	sp,sp,-16	#,,
	.cfi_def_cfa_offset 16
	sd	s0,8(sp)	#,
	.cfi_offset 8, -8
	addi	s0,sp,16	#,,
	.cfi_def_cfa 8, 0
# arch/riscv64/kernel/asm-offsets.c:26: 	OFFSET(TASK_THREAD_RA, task_struct, arch.thread.ra);
	.loc 1 26 2
#APP
# 26 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_RA 200 offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 27 2 is_stmt 1
# 27 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_SP 208 offsetof(struct task_struct, arch.thread.sp)	#
# 0 "" 2
	.loc 1 28 2
# 28 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S0 232 offsetof(struct task_struct, arch.thread.s[0])	#
# 0 "" 2
	.loc 1 29 2
# 29 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S1 240 offsetof(struct task_struct, arch.thread.s[1])	#
# 0 "" 2
	.loc 1 30 2
# 30 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S2 248 offsetof(struct task_struct, arch.thread.s[2])	#
# 0 "" 2
	.loc 1 31 2
# 31 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S3 256 offsetof(struct task_struct, arch.thread.s[3])	#
# 0 "" 2
	.loc 1 32 2
# 32 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S4 264 offsetof(struct task_struct, arch.thread.s[4])	#
# 0 "" 2
	.loc 1 33 2
# 33 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S5 272 offsetof(struct task_struct, arch.thread.s[5])	#
# 0 "" 2
	.loc 1 34 2
# 34 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S6 280 offsetof(struct task_struct, arch.thread.s[6])	#
# 0 "" 2
	.loc 1 35 2
# 35 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S7 288 offsetof(struct task_struct, arch.thread.s[7])	#
# 0 "" 2
	.loc 1 36 2
# 36 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S8 296 offsetof(struct task_struct, arch.thread.s[8])	#
# 0 "" 2
	.loc 1 37 2
# 37 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S9 304 offsetof(struct task_struct, arch.thread.s[9])	#
# 0 "" 2
	.loc 1 38 2
# 38 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S10 312 offsetof(struct task_struct, arch.thread.s[10])	#
# 0 "" 2
	.loc 1 39 2
# 39 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S11 320 offsetof(struct task_struct, arch.thread.s[11])	#
# 0 "" 2
	.loc 1 40 2
# 40 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_TI_FLAGS 184 offsetof(struct task_struct, arch.flags)	#
# 0 "" 2
	.loc 1 41 2
# 41 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_TI_KERNEL_SP 208 offsetof(struct task_struct, arch.thread.sp)	#
# 0 "" 2
	.loc 1 42 2
# 42 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_TI_USER_SP 216 offsetof(struct task_struct, arch.thread.user_sp)	#
# 0 "" 2
	.loc 1 43 3
# 43 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_TI_PREEMPT_COUNT 224 offsetof(struct task_struct, arch.thread.preempt_count)	#
# 0 "" 2
	.loc 1 45 2
# 45 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F0 328 offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 46 2
# 46 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F1 336 offsetof(struct task_struct, arch.thread.fstate.f[1])	#
# 0 "" 2
	.loc 1 47 2
# 47 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F2 344 offsetof(struct task_struct, arch.thread.fstate.f[2])	#
# 0 "" 2
	.loc 1 48 2
# 48 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F3 352 offsetof(struct task_struct, arch.thread.fstate.f[3])	#
# 0 "" 2
	.loc 1 49 2
# 49 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F4 360 offsetof(struct task_struct, arch.thread.fstate.f[4])	#
# 0 "" 2
	.loc 1 50 2
# 50 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F5 368 offsetof(struct task_struct, arch.thread.fstate.f[5])	#
# 0 "" 2
	.loc 1 51 2
# 51 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F6 376 offsetof(struct task_struct, arch.thread.fstate.f[6])	#
# 0 "" 2
	.loc 1 52 2
# 52 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F7 384 offsetof(struct task_struct, arch.thread.fstate.f[7])	#
# 0 "" 2
	.loc 1 53 2
# 53 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F8 392 offsetof(struct task_struct, arch.thread.fstate.f[8])	#
# 0 "" 2
	.loc 1 54 2
# 54 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F9 400 offsetof(struct task_struct, arch.thread.fstate.f[9])	#
# 0 "" 2
	.loc 1 55 2
# 55 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F10 408 offsetof(struct task_struct, arch.thread.fstate.f[10])	#
# 0 "" 2
	.loc 1 56 2
# 56 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F11 416 offsetof(struct task_struct, arch.thread.fstate.f[11])	#
# 0 "" 2
	.loc 1 57 2
# 57 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F12 424 offsetof(struct task_struct, arch.thread.fstate.f[12])	#
# 0 "" 2
	.loc 1 58 2
# 58 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F13 432 offsetof(struct task_struct, arch.thread.fstate.f[13])	#
# 0 "" 2
	.loc 1 59 2
# 59 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F14 440 offsetof(struct task_struct, arch.thread.fstate.f[14])	#
# 0 "" 2
	.loc 1 60 2
# 60 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F15 448 offsetof(struct task_struct, arch.thread.fstate.f[15])	#
# 0 "" 2
	.loc 1 61 2
# 61 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F16 456 offsetof(struct task_struct, arch.thread.fstate.f[16])	#
# 0 "" 2
	.loc 1 62 2
# 62 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F17 464 offsetof(struct task_struct, arch.thread.fstate.f[17])	#
# 0 "" 2
	.loc 1 63 2
# 63 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F18 472 offsetof(struct task_struct, arch.thread.fstate.f[18])	#
# 0 "" 2
	.loc 1 64 2
# 64 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F19 480 offsetof(struct task_struct, arch.thread.fstate.f[19])	#
# 0 "" 2
	.loc 1 65 2
# 65 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F20 488 offsetof(struct task_struct, arch.thread.fstate.f[20])	#
# 0 "" 2
	.loc 1 66 2
# 66 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F21 496 offsetof(struct task_struct, arch.thread.fstate.f[21])	#
# 0 "" 2
	.loc 1 67 2
# 67 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F22 504 offsetof(struct task_struct, arch.thread.fstate.f[22])	#
# 0 "" 2
	.loc 1 68 2
# 68 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F23 512 offsetof(struct task_struct, arch.thread.fstate.f[23])	#
# 0 "" 2
	.loc 1 69 2
# 69 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F24 520 offsetof(struct task_struct, arch.thread.fstate.f[24])	#
# 0 "" 2
	.loc 1 70 2
# 70 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F25 528 offsetof(struct task_struct, arch.thread.fstate.f[25])	#
# 0 "" 2
	.loc 1 71 2
# 71 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F26 536 offsetof(struct task_struct, arch.thread.fstate.f[26])	#
# 0 "" 2
	.loc 1 72 2
# 72 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F27 544 offsetof(struct task_struct, arch.thread.fstate.f[27])	#
# 0 "" 2
	.loc 1 73 2
# 73 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F28 552 offsetof(struct task_struct, arch.thread.fstate.f[28])	#
# 0 "" 2
	.loc 1 74 2
# 74 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F29 560 offsetof(struct task_struct, arch.thread.fstate.f[29])	#
# 0 "" 2
	.loc 1 75 2
# 75 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F30 568 offsetof(struct task_struct, arch.thread.fstate.f[30])	#
# 0 "" 2
	.loc 1 76 2
# 76 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F31 576 offsetof(struct task_struct, arch.thread.fstate.f[31])	#
# 0 "" 2
	.loc 1 77 2
# 77 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_FCSR 584 offsetof(struct task_struct, arch.thread.fstate.fcsr)	#
# 0 "" 2
	.loc 1 82 2
# 82 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_SIZE 288 sizeof(struct pt_regs)	#
# 0 "" 2
	.loc 1 83 2
# 83 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_EPC 0 offsetof(struct pt_regs, epc)	#
# 0 "" 2
	.loc 1 84 2
# 84 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_RA 8 offsetof(struct pt_regs, ra)	#
# 0 "" 2
	.loc 1 85 2
# 85 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_FP 64 offsetof(struct pt_regs, s0)	#
# 0 "" 2
	.loc 1 86 2
# 86 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S0 64 offsetof(struct pt_regs, s0)	#
# 0 "" 2
	.loc 1 87 2
# 87 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S1 72 offsetof(struct pt_regs, s1)	#
# 0 "" 2
	.loc 1 88 2
# 88 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S2 144 offsetof(struct pt_regs, s2)	#
# 0 "" 2
	.loc 1 89 2
# 89 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S3 152 offsetof(struct pt_regs, s3)	#
# 0 "" 2
	.loc 1 90 2
# 90 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S4 160 offsetof(struct pt_regs, s4)	#
# 0 "" 2
	.loc 1 91 2
# 91 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S5 168 offsetof(struct pt_regs, s5)	#
# 0 "" 2
	.loc 1 92 2
# 92 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S6 176 offsetof(struct pt_regs, s6)	#
# 0 "" 2
	.loc 1 93 2
# 93 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S7 184 offsetof(struct pt_regs, s7)	#
# 0 "" 2
	.loc 1 94 2
# 94 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S8 192 offsetof(struct pt_regs, s8)	#
# 0 "" 2
	.loc 1 95 2
# 95 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S9 200 offsetof(struct pt_regs, s9)	#
# 0 "" 2
	.loc 1 96 2
# 96 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S10 208 offsetof(struct pt_regs, s10)	#
# 0 "" 2
	.loc 1 97 2
# 97 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S11 216 offsetof(struct pt_regs, s11)	#
# 0 "" 2
	.loc 1 98 2
# 98 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_SP 16 offsetof(struct pt_regs, sp)	#
# 0 "" 2
	.loc 1 99 2
# 99 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_TP 32 offsetof(struct pt_regs, tp)	#
# 0 "" 2
	.loc 1 100 2
# 100 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A0 80 offsetof(struct pt_regs, a0)	#
# 0 "" 2
	.loc 1 101 2
# 101 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A1 88 offsetof(struct pt_regs, a1)	#
# 0 "" 2
	.loc 1 102 2
# 102 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A2 96 offsetof(struct pt_regs, a2)	#
# 0 "" 2
	.loc 1 103 2
# 103 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A3 104 offsetof(struct pt_regs, a3)	#
# 0 "" 2
	.loc 1 104 2
# 104 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A4 112 offsetof(struct pt_regs, a4)	#
# 0 "" 2
	.loc 1 105 2
# 105 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A5 120 offsetof(struct pt_regs, a5)	#
# 0 "" 2
	.loc 1 106 2
# 106 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A6 128 offsetof(struct pt_regs, a6)	#
# 0 "" 2
	.loc 1 107 2
# 107 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A7 136 offsetof(struct pt_regs, a7)	#
# 0 "" 2
	.loc 1 108 2
# 108 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T0 40 offsetof(struct pt_regs, t0)	#
# 0 "" 2
	.loc 1 109 2
# 109 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T1 48 offsetof(struct pt_regs, t1)	#
# 0 "" 2
	.loc 1 110 2
# 110 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T2 56 offsetof(struct pt_regs, t2)	#
# 0 "" 2
	.loc 1 111 2
# 111 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T3 224 offsetof(struct pt_regs, t3)	#
# 0 "" 2
	.loc 1 112 2
# 112 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T4 232 offsetof(struct pt_regs, t4)	#
# 0 "" 2
	.loc 1 113 2
# 113 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T5 240 offsetof(struct pt_regs, t5)	#
# 0 "" 2
	.loc 1 114 2
# 114 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T6 248 offsetof(struct pt_regs, t6)	#
# 0 "" 2
	.loc 1 115 2
# 115 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_GP 24 offsetof(struct pt_regs, gp)	#
# 0 "" 2
	.loc 1 116 2
# 116 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_ORIG_A0 280 offsetof(struct pt_regs, orig_a0)	#
# 0 "" 2
	.loc 1 117 2
# 117 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_STATUS 256 offsetof(struct pt_regs, status)	#
# 0 "" 2
	.loc 1 118 2
# 118 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_BADADDR 264 offsetof(struct pt_regs, badaddr)	#
# 0 "" 2
	.loc 1 119 2
# 119 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_CAUSE 272 offsetof(struct pt_regs, cause)	#
# 0 "" 2
	.loc 1 282 2
# 282 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_RA_RA 0 offsetof(struct task_struct, arch.thread.ra) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 286 2
# 286 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_SP_RA 8 offsetof(struct task_struct, arch.thread.sp) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 290 2
# 290 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S0_RA 32 offsetof(struct task_struct, arch.thread.s[0]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 294 2
# 294 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S1_RA 40 offsetof(struct task_struct, arch.thread.s[1]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 298 2
# 298 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S2_RA 48 offsetof(struct task_struct, arch.thread.s[2]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 302 2
# 302 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S3_RA 56 offsetof(struct task_struct, arch.thread.s[3]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 306 2
# 306 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S4_RA 64 offsetof(struct task_struct, arch.thread.s[4]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 310 2
# 310 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S5_RA 72 offsetof(struct task_struct, arch.thread.s[5]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 314 2
# 314 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S6_RA 80 offsetof(struct task_struct, arch.thread.s[6]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 318 2
# 318 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S7_RA 88 offsetof(struct task_struct, arch.thread.s[7]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 322 2
# 322 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S8_RA 96 offsetof(struct task_struct, arch.thread.s[8]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 326 2
# 326 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S9_RA 104 offsetof(struct task_struct, arch.thread.s[9]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 330 2
# 330 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S10_RA 112 offsetof(struct task_struct, arch.thread.s[10]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 334 2
# 334 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S11_RA 120 offsetof(struct task_struct, arch.thread.s[11]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 339 2
# 339 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F0_F0 0 offsetof(struct task_struct, arch.thread.fstate.f[0]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 343 2
# 343 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F1_F0 8 offsetof(struct task_struct, arch.thread.fstate.f[1]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 347 2
# 347 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F2_F0 16 offsetof(struct task_struct, arch.thread.fstate.f[2]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 351 2
# 351 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F3_F0 24 offsetof(struct task_struct, arch.thread.fstate.f[3]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 355 2
# 355 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F4_F0 32 offsetof(struct task_struct, arch.thread.fstate.f[4]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 359 2
# 359 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F5_F0 40 offsetof(struct task_struct, arch.thread.fstate.f[5]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 363 2
# 363 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F6_F0 48 offsetof(struct task_struct, arch.thread.fstate.f[6]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 367 2
# 367 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F7_F0 56 offsetof(struct task_struct, arch.thread.fstate.f[7]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 371 2
# 371 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F8_F0 64 offsetof(struct task_struct, arch.thread.fstate.f[8]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 375 2
# 375 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F9_F0 72 offsetof(struct task_struct, arch.thread.fstate.f[9]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 379 2
# 379 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F10_F0 80 offsetof(struct task_struct, arch.thread.fstate.f[10]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 383 2
# 383 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F11_F0 88 offsetof(struct task_struct, arch.thread.fstate.f[11]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 387 2
# 387 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F12_F0 96 offsetof(struct task_struct, arch.thread.fstate.f[12]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 391 2
# 391 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F13_F0 104 offsetof(struct task_struct, arch.thread.fstate.f[13]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 395 2
# 395 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F14_F0 112 offsetof(struct task_struct, arch.thread.fstate.f[14]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 399 2
# 399 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F15_F0 120 offsetof(struct task_struct, arch.thread.fstate.f[15]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 403 2
# 403 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F16_F0 128 offsetof(struct task_struct, arch.thread.fstate.f[16]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 407 2
# 407 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F17_F0 136 offsetof(struct task_struct, arch.thread.fstate.f[17]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 411 2
# 411 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F18_F0 144 offsetof(struct task_struct, arch.thread.fstate.f[18]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 415 2
# 415 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F19_F0 152 offsetof(struct task_struct, arch.thread.fstate.f[19]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 419 2
# 419 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F20_F0 160 offsetof(struct task_struct, arch.thread.fstate.f[20]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 423 2
# 423 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F21_F0 168 offsetof(struct task_struct, arch.thread.fstate.f[21]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 427 2
# 427 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F22_F0 176 offsetof(struct task_struct, arch.thread.fstate.f[22]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 431 2
# 431 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F23_F0 184 offsetof(struct task_struct, arch.thread.fstate.f[23]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 435 2
# 435 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F24_F0 192 offsetof(struct task_struct, arch.thread.fstate.f[24]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 439 2
# 439 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F25_F0 200 offsetof(struct task_struct, arch.thread.fstate.f[25]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 443 2
# 443 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F26_F0 208 offsetof(struct task_struct, arch.thread.fstate.f[26]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 447 2
# 447 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F27_F0 216 offsetof(struct task_struct, arch.thread.fstate.f[27]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 451 2
# 451 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F28_F0 224 offsetof(struct task_struct, arch.thread.fstate.f[28]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 455 2
# 455 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F29_F0 232 offsetof(struct task_struct, arch.thread.fstate.f[29]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 459 2
# 459 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F30_F0 240 offsetof(struct task_struct, arch.thread.fstate.f[30]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 463 2
# 463 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F31_F0 248 offsetof(struct task_struct, arch.thread.fstate.f[31]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 467 2
# 467 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_FCSR_F0 256 offsetof(struct task_struct, arch.thread.fstate.fcsr) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 476 2
# 476 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_SIZE_ON_STACK 288 ALIGN(sizeof(struct pt_regs), STACK_ALIGN)	#
# 0 "" 2
	.loc 1 478 2
# 478 "arch/riscv64/kernel/asm-offsets.c" 1
	
->KERNEL_MAP_VIRT_ADDR 8 offsetof(struct kernel_mapping, virt_addr)	#
# 0 "" 2
	.loc 1 482 3
# 482 "arch/riscv64/kernel/asm-offsets.c" 1
	
->__NR_syscall_max -1 sizeof(syscalls) - 1	#
# 0 "" 2
# arch/riscv64/kernel/asm-offsets.c:485: }
	.loc 1 485 1 is_stmt 0
#NO_APP
	ld	s0,8(sp)		#,
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16	#,,
	.cfi_def_cfa_offset 0
	jr	ra		#
	.cfi_endproc
.LFE231:
	.size	asm_offsets, .-asm_offsets
	.text
.Letext0:
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0xb7
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x8
	.byte	0x1
	.4byte	.LASF12
	.byte	0xc
	.4byte	.LASF13
	.4byte	.LASF14
	.4byte	.Ldebug_ranges0+0
	.8byte	0
	.4byte	.Ldebug_line0
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF0
	.byte	0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF1
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF2
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF3
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF4
	.byte	0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF5
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF6
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF7
	.byte	0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF8
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF10
	.byte	0x4
	.4byte	0x45
	.4byte	0x8d
	.byte	0x5
	.4byte	0x8d
	.byte	0x7f
	.byte	0
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF11
	.byte	0x6
	.4byte	.LASF15
	.byte	0x1
	.byte	0x12
	.byte	0xd
	.4byte	0x7d
	.byte	0x7
	.4byte	.LASF16
	.byte	0x1
	.byte	0x18
	.byte	0x6
	.8byte	.LFB231
	.8byte	.LFE231-.LFB231
	.byte	0x1
	.byte	0x9c
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.byte	0x1
	.byte	0x11
	.byte	0x1
	.byte	0x25
	.byte	0xe
	.byte	0x13
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0x1b
	.byte	0xe
	.byte	0x55
	.byte	0x17
	.byte	0x11
	.byte	0x1
	.byte	0x10
	.byte	0x17
	.byte	0
	.byte	0
	.byte	0x2
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0xe
	.byte	0
	.byte	0
	.byte	0x3
	.byte	0x24
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x3e
	.byte	0xb
	.byte	0x3
	.byte	0x8
	.byte	0
	.byte	0
	.byte	0x4
	.byte	0x1
	.byte	0x1
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0xd
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0x34
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0x2e
	.byte	0
	.byte	0x3f
	.byte	0x19
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x27
	.byte	0x19
	.byte	0x11
	.byte	0x1
	.byte	0x12
	.byte	0x7
	.byte	0x40
	.byte	0x18
	.byte	0x97,0x42
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_aranges,"",@progbits
	.4byte	0x2c
	.2byte	0x2
	.4byte	.Ldebug_info0
	.byte	0x8
	.byte	0
	.2byte	0
	.2byte	0
	.8byte	.LFB231
	.8byte	.LFE231-.LFB231
	.8byte	0
	.8byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.8byte	.LFB231
	.8byte	.LFE231
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF4:
	.string	"long long int"
.LASF1:
	.string	"unsigned int"
.LASF16:
	.string	"asm_offsets"
.LASF12:
	.ascii	"GNU C99 10.3.0 -march=rv64ima"
	.string	"fd -mabi=lp64d -g -g -O2 -std=gnu99 -fno-strict-aliasing -fno-strict-overflow -fno-common -fno-pie -fno-stack-protector -fgnu89-inline -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-builtin -ffunction-sections -fno-reorder-blocks -funit-at-a-time"
.LASF0:
	.string	"long unsigned int"
.LASF9:
	.string	"long long unsigned int"
.LASF15:
	.string	"syscalls"
.LASF14:
	.string	"/tmp/home/kitten"
.LASF7:
	.string	"unsigned char"
.LASF3:
	.string	"char"
.LASF2:
	.string	"long int"
.LASF10:
	.string	"_Bool"
.LASF11:
	.string	"ssizetype"
.LASF5:
	.string	"short unsigned int"
.LASF6:
	.string	"signed char"
.LASF13:
	.string	"arch/riscv64/kernel/asm-offsets.c"
.LASF8:
	.string	"short int"
	.ident	"GCC: (Buildroot 2022.02.1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
