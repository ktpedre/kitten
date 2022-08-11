	.file	"asm-offsets.c"
	.option nopic
# GNU C99 (Buildroot 2022.02.1) version 10.3.0 (riscv64-buildroot-linux-gnu)
#	compiled by GNU C version 11.2.0, GMP version 6.2.1, MPFR version 4.1.0, MPC version 1.2.1, isl version none
# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -nostdinc -I include -I ofed/include
# -isysroot /tmp/buildroot-2022.02.1/output/host/riscv64-buildroot-linux-gnu/sysroot
# -D __KERNEL__ -D __LWK__ -D __KERNEL__ -D TEXT_OFFSET=0x00080000
# -D KBUILD_STR(s)=#s -D KBUILD_BASENAME=KBUILD_STR(asm_offsets)
# -D KBUILD_MODNAME=KBUILD_STR(asm_offsets)
# -isystem /tmp/buildroot-2022.02.1/output/host/lib/gcc/riscv64-buildroot-linux-gnu/10.3.0/include
# -include include/lwk/autoconf.h -MD arch/riscv64/kernel/.asm-offsets.s.d
# arch/riscv64/kernel/asm-offsets.c -mabi=lp64d -march=rv64imafdc
# -auxbase-strip arch/riscv64/kernel/asm-offsets.s -g -g -O2 -Wall -Wundef
# -Wstrict-prototypes -Wno-trigraphs -Wno-sign-compare
# -Wno-unused-parameter -Wno-pointer-sign -w -std=gnu99
# -fstack-protector-strong -fno-strict-aliasing -fno-strict-overflow
# -fno-common -fno-pie -fno-stack-protector -fgnu89-inline
# -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-builtin
# -ffunction-sections -fno-reorder-blocks -funit-at-a-time -fverbose-asm
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
# -mfdiv -mglibc -mplt -mstrict-align

	.text
.Ltext0:
	.cfi_sections	.debug_frame
	.section	.text.asm_offsets,"ax",@progbits
	.align	1
	.globl	asm_offsets
	.type	asm_offsets, @function
asm_offsets:
.LFB370:
	.file 1 "arch/riscv64/kernel/asm-offsets.c"
	.loc 1 30 1
	.cfi_startproc
	.loc 1 31 2
# arch/riscv64/kernel/asm-offsets.c:30: {
	.loc 1 30 1 is_stmt 0
	addi	sp,sp,-16	#,,
	.cfi_def_cfa_offset 16
	sd	s0,8(sp)	#,
	.cfi_offset 8, -8
	addi	s0,sp,16	#,,
	.cfi_def_cfa 8, 0
# arch/riscv64/kernel/asm-offsets.c:31: 	OFFSET(TASK_THREAD_RA, task_struct, arch.thread.ra);
	.loc 1 31 2
#APP
# 31 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_RA 200 offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 32 2 is_stmt 1
# 32 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_KERN_SP 216 offsetof(struct task_struct, arch.thread.kern_sp)	#
# 0 "" 2
	.loc 1 33 2
# 33 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S0 248 offsetof(struct task_struct, arch.thread.s[0])	#
# 0 "" 2
	.loc 1 34 2
# 34 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S1 256 offsetof(struct task_struct, arch.thread.s[1])	#
# 0 "" 2
	.loc 1 35 2
# 35 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S2 264 offsetof(struct task_struct, arch.thread.s[2])	#
# 0 "" 2
	.loc 1 36 2
# 36 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S3 272 offsetof(struct task_struct, arch.thread.s[3])	#
# 0 "" 2
	.loc 1 37 2
# 37 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S4 280 offsetof(struct task_struct, arch.thread.s[4])	#
# 0 "" 2
	.loc 1 38 2
# 38 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S5 288 offsetof(struct task_struct, arch.thread.s[5])	#
# 0 "" 2
	.loc 1 39 2
# 39 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S6 296 offsetof(struct task_struct, arch.thread.s[6])	#
# 0 "" 2
	.loc 1 40 2
# 40 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S7 304 offsetof(struct task_struct, arch.thread.s[7])	#
# 0 "" 2
	.loc 1 41 2
# 41 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S8 312 offsetof(struct task_struct, arch.thread.s[8])	#
# 0 "" 2
	.loc 1 42 2
# 42 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S9 320 offsetof(struct task_struct, arch.thread.s[9])	#
# 0 "" 2
	.loc 1 43 2
# 43 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S10 328 offsetof(struct task_struct, arch.thread.s[10])	#
# 0 "" 2
	.loc 1 44 2
# 44 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S11 336 offsetof(struct task_struct, arch.thread.s[11])	#
# 0 "" 2
	.loc 1 45 2
# 45 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_FLAGS 184 offsetof(struct task_struct, arch.flags)	#
# 0 "" 2
	.loc 1 46 2
# 46 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_KERNEL_SP0 208 offsetof(struct task_struct, arch.thread.kern_sp0)	#
# 0 "" 2
	.loc 1 47 2
# 47 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_KERNEL_SP 216 offsetof(struct task_struct, arch.thread.kern_sp)	#
# 0 "" 2
	.loc 1 48 2
# 48 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_USER_SP 224 offsetof(struct task_struct, arch.thread.user_sp)	#
# 0 "" 2
	.loc 1 49 3
# 49 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_PREEMPT_COUNT 232 offsetof(struct task_struct, arch.thread.preempt_count)	#
# 0 "" 2
	.loc 1 51 2
# 51 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F0 344 offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 52 2
# 52 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F1 352 offsetof(struct task_struct, arch.thread.fstate.f[1])	#
# 0 "" 2
	.loc 1 53 2
# 53 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F2 360 offsetof(struct task_struct, arch.thread.fstate.f[2])	#
# 0 "" 2
	.loc 1 54 2
# 54 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F3 368 offsetof(struct task_struct, arch.thread.fstate.f[3])	#
# 0 "" 2
	.loc 1 55 2
# 55 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F4 376 offsetof(struct task_struct, arch.thread.fstate.f[4])	#
# 0 "" 2
	.loc 1 56 2
# 56 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F5 384 offsetof(struct task_struct, arch.thread.fstate.f[5])	#
# 0 "" 2
	.loc 1 57 2
# 57 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F6 392 offsetof(struct task_struct, arch.thread.fstate.f[6])	#
# 0 "" 2
	.loc 1 58 2
# 58 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F7 400 offsetof(struct task_struct, arch.thread.fstate.f[7])	#
# 0 "" 2
	.loc 1 59 2
# 59 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F8 408 offsetof(struct task_struct, arch.thread.fstate.f[8])	#
# 0 "" 2
	.loc 1 60 2
# 60 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F9 416 offsetof(struct task_struct, arch.thread.fstate.f[9])	#
# 0 "" 2
	.loc 1 61 2
# 61 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F10 424 offsetof(struct task_struct, arch.thread.fstate.f[10])	#
# 0 "" 2
	.loc 1 62 2
# 62 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F11 432 offsetof(struct task_struct, arch.thread.fstate.f[11])	#
# 0 "" 2
	.loc 1 63 2
# 63 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F12 440 offsetof(struct task_struct, arch.thread.fstate.f[12])	#
# 0 "" 2
	.loc 1 64 2
# 64 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F13 448 offsetof(struct task_struct, arch.thread.fstate.f[13])	#
# 0 "" 2
	.loc 1 65 2
# 65 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F14 456 offsetof(struct task_struct, arch.thread.fstate.f[14])	#
# 0 "" 2
	.loc 1 66 2
# 66 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F15 464 offsetof(struct task_struct, arch.thread.fstate.f[15])	#
# 0 "" 2
	.loc 1 67 2
# 67 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F16 472 offsetof(struct task_struct, arch.thread.fstate.f[16])	#
# 0 "" 2
	.loc 1 68 2
# 68 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F17 480 offsetof(struct task_struct, arch.thread.fstate.f[17])	#
# 0 "" 2
	.loc 1 69 2
# 69 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F18 488 offsetof(struct task_struct, arch.thread.fstate.f[18])	#
# 0 "" 2
	.loc 1 70 2
# 70 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F19 496 offsetof(struct task_struct, arch.thread.fstate.f[19])	#
# 0 "" 2
	.loc 1 71 2
# 71 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F20 504 offsetof(struct task_struct, arch.thread.fstate.f[20])	#
# 0 "" 2
	.loc 1 72 2
# 72 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F21 512 offsetof(struct task_struct, arch.thread.fstate.f[21])	#
# 0 "" 2
	.loc 1 73 2
# 73 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F22 520 offsetof(struct task_struct, arch.thread.fstate.f[22])	#
# 0 "" 2
	.loc 1 74 2
# 74 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F23 528 offsetof(struct task_struct, arch.thread.fstate.f[23])	#
# 0 "" 2
	.loc 1 75 2
# 75 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F24 536 offsetof(struct task_struct, arch.thread.fstate.f[24])	#
# 0 "" 2
	.loc 1 76 2
# 76 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F25 544 offsetof(struct task_struct, arch.thread.fstate.f[25])	#
# 0 "" 2
	.loc 1 77 2
# 77 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F26 552 offsetof(struct task_struct, arch.thread.fstate.f[26])	#
# 0 "" 2
	.loc 1 78 2
# 78 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F27 560 offsetof(struct task_struct, arch.thread.fstate.f[27])	#
# 0 "" 2
	.loc 1 79 2
# 79 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F28 568 offsetof(struct task_struct, arch.thread.fstate.f[28])	#
# 0 "" 2
	.loc 1 80 2
# 80 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F29 576 offsetof(struct task_struct, arch.thread.fstate.f[29])	#
# 0 "" 2
	.loc 1 81 2
# 81 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F30 584 offsetof(struct task_struct, arch.thread.fstate.f[30])	#
# 0 "" 2
	.loc 1 82 2
# 82 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F31 592 offsetof(struct task_struct, arch.thread.fstate.f[31])	#
# 0 "" 2
	.loc 1 83 2
# 83 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_FCSR 600 offsetof(struct task_struct, arch.thread.fstate.fcsr)	#
# 0 "" 2
	.loc 1 88 2
# 88 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_SIZE 288 sizeof(struct pt_regs)	#
# 0 "" 2
	.loc 1 89 2
# 89 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_EPC 0 offsetof(struct pt_regs, epc)	#
# 0 "" 2
	.loc 1 90 2
# 90 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_RA 8 offsetof(struct pt_regs, ra)	#
# 0 "" 2
	.loc 1 91 2
# 91 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_FP 64 offsetof(struct pt_regs, s0)	#
# 0 "" 2
	.loc 1 92 2
# 92 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S0 64 offsetof(struct pt_regs, s0)	#
# 0 "" 2
	.loc 1 93 2
# 93 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S1 72 offsetof(struct pt_regs, s1)	#
# 0 "" 2
	.loc 1 94 2
# 94 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S2 144 offsetof(struct pt_regs, s2)	#
# 0 "" 2
	.loc 1 95 2
# 95 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S3 152 offsetof(struct pt_regs, s3)	#
# 0 "" 2
	.loc 1 96 2
# 96 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S4 160 offsetof(struct pt_regs, s4)	#
# 0 "" 2
	.loc 1 97 2
# 97 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S5 168 offsetof(struct pt_regs, s5)	#
# 0 "" 2
	.loc 1 98 2
# 98 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S6 176 offsetof(struct pt_regs, s6)	#
# 0 "" 2
	.loc 1 99 2
# 99 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S7 184 offsetof(struct pt_regs, s7)	#
# 0 "" 2
	.loc 1 100 2
# 100 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S8 192 offsetof(struct pt_regs, s8)	#
# 0 "" 2
	.loc 1 101 2
# 101 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S9 200 offsetof(struct pt_regs, s9)	#
# 0 "" 2
	.loc 1 102 2
# 102 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S10 208 offsetof(struct pt_regs, s10)	#
# 0 "" 2
	.loc 1 103 2
# 103 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_S11 216 offsetof(struct pt_regs, s11)	#
# 0 "" 2
	.loc 1 104 2
# 104 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_SP 16 offsetof(struct pt_regs, sp)	#
# 0 "" 2
	.loc 1 105 2
# 105 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_TP 32 offsetof(struct pt_regs, tp)	#
# 0 "" 2
	.loc 1 106 2
# 106 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A0 80 offsetof(struct pt_regs, a0)	#
# 0 "" 2
	.loc 1 107 2
# 107 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A1 88 offsetof(struct pt_regs, a1)	#
# 0 "" 2
	.loc 1 108 2
# 108 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A2 96 offsetof(struct pt_regs, a2)	#
# 0 "" 2
	.loc 1 109 2
# 109 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A3 104 offsetof(struct pt_regs, a3)	#
# 0 "" 2
	.loc 1 110 2
# 110 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A4 112 offsetof(struct pt_regs, a4)	#
# 0 "" 2
	.loc 1 111 2
# 111 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A5 120 offsetof(struct pt_regs, a5)	#
# 0 "" 2
	.loc 1 112 2
# 112 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A6 128 offsetof(struct pt_regs, a6)	#
# 0 "" 2
	.loc 1 113 2
# 113 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_A7 136 offsetof(struct pt_regs, a7)	#
# 0 "" 2
	.loc 1 114 2
# 114 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T0 40 offsetof(struct pt_regs, t0)	#
# 0 "" 2
	.loc 1 115 2
# 115 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T1 48 offsetof(struct pt_regs, t1)	#
# 0 "" 2
	.loc 1 116 2
# 116 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T2 56 offsetof(struct pt_regs, t2)	#
# 0 "" 2
	.loc 1 117 2
# 117 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T3 224 offsetof(struct pt_regs, t3)	#
# 0 "" 2
	.loc 1 118 2
# 118 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T4 232 offsetof(struct pt_regs, t4)	#
# 0 "" 2
	.loc 1 119 2
# 119 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T5 240 offsetof(struct pt_regs, t5)	#
# 0 "" 2
	.loc 1 120 2
# 120 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_T6 248 offsetof(struct pt_regs, t6)	#
# 0 "" 2
	.loc 1 121 2
# 121 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_GP 24 offsetof(struct pt_regs, gp)	#
# 0 "" 2
	.loc 1 122 2
# 122 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_ORIG_A0 280 offsetof(struct pt_regs, orig_a0)	#
# 0 "" 2
	.loc 1 123 2
# 123 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_STATUS 256 offsetof(struct pt_regs, status)	#
# 0 "" 2
	.loc 1 124 2
# 124 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_BADADDR 264 offsetof(struct pt_regs, badaddr)	#
# 0 "" 2
	.loc 1 125 2
# 125 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_CAUSE 272 offsetof(struct pt_regs, cause)	#
# 0 "" 2
	.loc 1 132 2
# 132 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_RA_RA 0 offsetof(struct task_struct, arch.thread.ra) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 136 2
# 136 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_USER_SP_RA 24 offsetof(struct task_struct, arch.thread.user_sp) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 140 2
# 140 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S0_RA 48 offsetof(struct task_struct, arch.thread.s[0]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 144 2
# 144 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S1_RA 56 offsetof(struct task_struct, arch.thread.s[1]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 148 2
# 148 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S2_RA 64 offsetof(struct task_struct, arch.thread.s[2]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 152 2
# 152 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S3_RA 72 offsetof(struct task_struct, arch.thread.s[3]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 156 2
# 156 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S4_RA 80 offsetof(struct task_struct, arch.thread.s[4]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 160 2
# 160 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S5_RA 88 offsetof(struct task_struct, arch.thread.s[5]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 164 2
# 164 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S6_RA 96 offsetof(struct task_struct, arch.thread.s[6]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 168 2
# 168 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S7_RA 104 offsetof(struct task_struct, arch.thread.s[7]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 172 2
# 172 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S8_RA 112 offsetof(struct task_struct, arch.thread.s[8]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 176 2
# 176 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S9_RA 120 offsetof(struct task_struct, arch.thread.s[9]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 180 2
# 180 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S10_RA 128 offsetof(struct task_struct, arch.thread.s[10]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 184 2
# 184 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_S11_RA 136 offsetof(struct task_struct, arch.thread.s[11]) - offsetof(struct task_struct, arch.thread.ra)	#
# 0 "" 2
	.loc 1 189 2
# 189 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F0_F0 0 offsetof(struct task_struct, arch.thread.fstate.f[0]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 193 2
# 193 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F1_F0 8 offsetof(struct task_struct, arch.thread.fstate.f[1]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 197 2
# 197 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F2_F0 16 offsetof(struct task_struct, arch.thread.fstate.f[2]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 201 2
# 201 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F3_F0 24 offsetof(struct task_struct, arch.thread.fstate.f[3]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 205 2
# 205 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F4_F0 32 offsetof(struct task_struct, arch.thread.fstate.f[4]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 209 2
# 209 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F5_F0 40 offsetof(struct task_struct, arch.thread.fstate.f[5]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 213 2
# 213 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F6_F0 48 offsetof(struct task_struct, arch.thread.fstate.f[6]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 217 2
# 217 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F7_F0 56 offsetof(struct task_struct, arch.thread.fstate.f[7]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 221 2
# 221 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F8_F0 64 offsetof(struct task_struct, arch.thread.fstate.f[8]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 225 2
# 225 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F9_F0 72 offsetof(struct task_struct, arch.thread.fstate.f[9]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 229 2
# 229 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F10_F0 80 offsetof(struct task_struct, arch.thread.fstate.f[10]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 233 2
# 233 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F11_F0 88 offsetof(struct task_struct, arch.thread.fstate.f[11]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 237 2
# 237 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F12_F0 96 offsetof(struct task_struct, arch.thread.fstate.f[12]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 241 2
# 241 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F13_F0 104 offsetof(struct task_struct, arch.thread.fstate.f[13]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 245 2
# 245 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F14_F0 112 offsetof(struct task_struct, arch.thread.fstate.f[14]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 249 2
# 249 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F15_F0 120 offsetof(struct task_struct, arch.thread.fstate.f[15]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 253 2
# 253 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F16_F0 128 offsetof(struct task_struct, arch.thread.fstate.f[16]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 257 2
# 257 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F17_F0 136 offsetof(struct task_struct, arch.thread.fstate.f[17]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 261 2
# 261 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F18_F0 144 offsetof(struct task_struct, arch.thread.fstate.f[18]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 265 2
# 265 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F19_F0 152 offsetof(struct task_struct, arch.thread.fstate.f[19]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 269 2
# 269 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F20_F0 160 offsetof(struct task_struct, arch.thread.fstate.f[20]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 273 2
# 273 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F21_F0 168 offsetof(struct task_struct, arch.thread.fstate.f[21]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 277 2
# 277 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F22_F0 176 offsetof(struct task_struct, arch.thread.fstate.f[22]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 281 2
# 281 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F23_F0 184 offsetof(struct task_struct, arch.thread.fstate.f[23]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 285 2
# 285 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F24_F0 192 offsetof(struct task_struct, arch.thread.fstate.f[24]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 289 2
# 289 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F25_F0 200 offsetof(struct task_struct, arch.thread.fstate.f[25]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 293 2
# 293 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F26_F0 208 offsetof(struct task_struct, arch.thread.fstate.f[26]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 297 2
# 297 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F27_F0 216 offsetof(struct task_struct, arch.thread.fstate.f[27]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 301 2
# 301 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F28_F0 224 offsetof(struct task_struct, arch.thread.fstate.f[28]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 305 2
# 305 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F29_F0 232 offsetof(struct task_struct, arch.thread.fstate.f[29]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 309 2
# 309 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F30_F0 240 offsetof(struct task_struct, arch.thread.fstate.f[30]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 313 2
# 313 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_F31_F0 248 offsetof(struct task_struct, arch.thread.fstate.f[31]) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 317 2
# 317 "arch/riscv64/kernel/asm-offsets.c" 1
	
->TASK_THREAD_FCSR_F0 256 offsetof(struct task_struct, arch.thread.fstate.fcsr) - offsetof(struct task_struct, arch.thread.fstate.f[0])	#
# 0 "" 2
	.loc 1 326 2
# 326 "arch/riscv64/kernel/asm-offsets.c" 1
	
->PT_SIZE_ON_STACK 288 ALIGN(sizeof(struct pt_regs), STACK_ALIGN)	#
# 0 "" 2
	.loc 1 328 2
# 328 "arch/riscv64/kernel/asm-offsets.c" 1
	
->KERNEL_MAP_VIRT_ADDR 8 offsetof(struct kernel_mapping, virt_addr)	#
# 0 "" 2
	.loc 1 331 2
# 331 "arch/riscv64/kernel/asm-offsets.c" 1
	
->SBI_HART_BOOT_TASK_PTR_OFFSET 0 offsetof(struct sbi_hart_boot_data, task_ptr)	#
# 0 "" 2
	.loc 1 332 2
# 332 "arch/riscv64/kernel/asm-offsets.c" 1
	
->SBI_HART_BOOT_STACK_PTR_OFFSET 8 offsetof(struct sbi_hart_boot_data, stack_ptr)	#
# 0 "" 2
	.loc 1 334 3
# 334 "arch/riscv64/kernel/asm-offsets.c" 1
	
->__NR_syscall_max 534 sizeof(syscalls) - 1	#
# 0 "" 2
# arch/riscv64/kernel/asm-offsets.c:337: }
	.loc 1 337 1 is_stmt 0
#NO_APP
	ld	s0,8(sp)		#,
	.cfi_restore 8
	.cfi_def_cfa 2, 16
	addi	sp,sp,16	#,,
	.cfi_def_cfa_offset 0
	jr	ra		#
	.cfi_endproc
.LFE370:
	.size	asm_offsets, .-asm_offsets
	.text
.Letext0:
	.file 2 "include/arch/types.h"
	.file 3 "include/lwk/types.h"
	.file 4 "include/lwk/idspace.h"
	.file 5 "include/lwk/cpumask.h"
	.file 6 "include/arch/uapi_ptrace.h"
	.file 7 "include/arch/processor.h"
	.file 8 "include/lwk/list.h"
	.file 9 "include/arch/signal.h"
	.file 10 "include/lwk/signal.h"
	.file 11 "include/arch/task.h"
	.file 12 "include/lwk/task.h"
	.file 13 "include/arch/current.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.4byte	0x6f2
	.2byte	0x4
	.4byte	.Ldebug_abbrev0
	.byte	0x8
	.byte	0x1
	.4byte	.LASF71
	.byte	0xc
	.4byte	.LASF72
	.4byte	.LASF73
	.4byte	.Ldebug_ranges0+0
	.8byte	0
	.4byte	.Ldebug_line0
	.byte	0x2
	.byte	0x2
	.byte	0x7
	.4byte	.LASF0
	.byte	0x2
	.byte	0x1
	.byte	0x6
	.4byte	.LASF1
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF2
	.byte	0x2
	.byte	0x2
	.byte	0x5
	.4byte	.LASF3
	.byte	0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.byte	0x4
	.4byte	.LASF6
	.byte	0x2
	.byte	0x16
	.byte	0x16
	.4byte	0x58
	.byte	0x2
	.byte	0x4
	.byte	0x7
	.4byte	.LASF4
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF5
	.byte	0x4
	.4byte	.LASF7
	.byte	0x2
	.byte	0x19
	.byte	0x1d
	.4byte	0x72
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF8
	.byte	0x2
	.byte	0x8
	.byte	0x7
	.4byte	.LASF9
	.byte	0x2
	.byte	0x8
	.byte	0x5
	.4byte	.LASF10
	.byte	0x5
	.byte	0x8
	.4byte	0x8d
	.byte	0x2
	.byte	0x1
	.byte	0x8
	.4byte	.LASF11
	.byte	0x4
	.4byte	.LASF12
	.byte	0x3
	.byte	0x73
	.byte	0x11
	.4byte	0x4c
	.byte	0x4
	.4byte	.LASF13
	.byte	0x3
	.byte	0x84
	.byte	0x11
	.4byte	0xac
	.byte	0x2
	.byte	0x1
	.byte	0x2
	.4byte	.LASF14
	.byte	0x4
	.4byte	.LASF15
	.byte	0x4
	.byte	0x10
	.byte	0x16
	.4byte	0x58
	.byte	0x6
	.4byte	.LASF17
	.byte	0x8
	.byte	0x5
	.byte	0x91
	.byte	0x10
	.4byte	0xda
	.byte	0x7
	.4byte	.LASF19
	.byte	0x5
	.byte	0x91
	.byte	0x1a
	.4byte	0xda
	.byte	0
	.byte	0
	.byte	0x8
	.4byte	0x79
	.4byte	0xea
	.byte	0x9
	.4byte	0x79
	.byte	0
	.byte	0
	.byte	0x4
	.4byte	.LASF16
	.byte	0x5
	.byte	0x91
	.byte	0x3b
	.4byte	0xbf
	.byte	0x8
	.4byte	0x8d
	.4byte	0x106
	.byte	0x9
	.4byte	0x79
	.byte	0x1f
	.byte	0
	.byte	0xa
	.4byte	.LASF18
	.2byte	0x108
	.byte	0x6
	.byte	0x3b
	.byte	0x8
	.4byte	0x12e
	.byte	0xb
	.string	"f"
	.byte	0x6
	.byte	0x3c
	.byte	0x8
	.4byte	0x12e
	.byte	0
	.byte	0xc
	.4byte	.LASF20
	.byte	0x6
	.byte	0x3d
	.byte	0x8
	.4byte	0x4c
	.2byte	0x100
	.byte	0
	.byte	0x8
	.4byte	0x66
	.4byte	0x13e
	.byte	0x9
	.4byte	0x79
	.byte	0x1f
	.byte	0
	.byte	0xa
	.4byte	.LASF21
	.2byte	0x1a0
	.byte	0x7
	.byte	0x37
	.byte	0x8
	.4byte	0x1bf
	.byte	0xb
	.string	"ra"
	.byte	0x7
	.byte	0x39
	.byte	0x10
	.4byte	0x79
	.byte	0
	.byte	0x7
	.4byte	.LASF22
	.byte	0x7
	.byte	0x3a
	.byte	0x10
	.4byte	0x79
	.byte	0x8
	.byte	0x7
	.4byte	.LASF23
	.byte	0x7
	.byte	0x3b
	.byte	0x10
	.4byte	0x79
	.byte	0x10
	.byte	0x7
	.4byte	.LASF24
	.byte	0x7
	.byte	0x3c
	.byte	0x10
	.4byte	0x79
	.byte	0x18
	.byte	0x7
	.4byte	.LASF25
	.byte	0x7
	.byte	0x3d
	.byte	0x10
	.4byte	0x79
	.byte	0x20
	.byte	0xb
	.string	"tp"
	.byte	0x7
	.byte	0x3e
	.byte	0x10
	.4byte	0x79
	.byte	0x28
	.byte	0xb
	.string	"s"
	.byte	0x7
	.byte	0x3f
	.byte	0x10
	.4byte	0x1bf
	.byte	0x30
	.byte	0x7
	.4byte	.LASF26
	.byte	0x7
	.byte	0x40
	.byte	0x1d
	.4byte	0x106
	.byte	0x90
	.byte	0xc
	.4byte	.LASF27
	.byte	0x7
	.byte	0x41
	.byte	0x10
	.4byte	0x79
	.2byte	0x198
	.byte	0
	.byte	0x8
	.4byte	0x79
	.4byte	0x1cf
	.byte	0x9
	.4byte	0x79
	.byte	0xb
	.byte	0
	.byte	0x6
	.4byte	.LASF28
	.byte	0x10
	.byte	0x8
	.byte	0x1f
	.byte	0x8
	.4byte	0x1f7
	.byte	0x7
	.4byte	.LASF29
	.byte	0x8
	.byte	0x20
	.byte	0x14
	.4byte	0x1f7
	.byte	0
	.byte	0x7
	.4byte	.LASF30
	.byte	0x8
	.byte	0x20
	.byte	0x1b
	.4byte	0x1f7
	.byte	0x8
	.byte	0
	.byte	0x5
	.byte	0x8
	.4byte	0x1cf
	.byte	0xd
	.4byte	.LASF31
	.byte	0x8
	.byte	0x8
	.2byte	0x19b
	.byte	0x8
	.4byte	0x21a
	.byte	0xe
	.4byte	.LASF32
	.byte	0x8
	.2byte	0x19c
	.byte	0x15
	.4byte	0x245
	.byte	0
	.byte	0
	.byte	0xd
	.4byte	.LASF33
	.byte	0x10
	.byte	0x8
	.2byte	0x19f
	.byte	0x8
	.4byte	0x245
	.byte	0xe
	.4byte	.LASF29
	.byte	0x8
	.2byte	0x1a0
	.byte	0x15
	.4byte	0x245
	.byte	0
	.byte	0xe
	.4byte	.LASF34
	.byte	0x8
	.2byte	0x1a0
	.byte	0x1d
	.4byte	0x24b
	.byte	0x8
	.byte	0
	.byte	0x5
	.byte	0x8
	.4byte	0x21a
	.byte	0x5
	.byte	0x8
	.4byte	0x245
	.byte	0xf
	.byte	0x8
	.byte	0x9
	.byte	0x45
	.byte	0x9
	.4byte	0x268
	.byte	0x7
	.4byte	.LASF35
	.byte	0x9
	.byte	0x46
	.byte	0x10
	.4byte	0xda
	.byte	0
	.byte	0
	.byte	0x4
	.4byte	.LASF36
	.byte	0x9
	.byte	0x47
	.byte	0x3
	.4byte	0x251
	.byte	0x6
	.4byte	.LASF37
	.byte	0x18
	.byte	0xa
	.byte	0xc
	.byte	0x8
	.4byte	0x29c
	.byte	0x7
	.4byte	.LASF38
	.byte	0xa
	.byte	0xd
	.byte	0x13
	.4byte	0x1cf
	.byte	0
	.byte	0x7
	.4byte	.LASF39
	.byte	0xa
	.byte	0xe
	.byte	0xd
	.4byte	0x268
	.byte	0x10
	.byte	0
	.byte	0xa
	.4byte	.LASF40
	.2byte	0x1b0
	.byte	0xb
	.byte	0x1e
	.byte	0x8
	.4byte	0x2d2
	.byte	0x7
	.4byte	.LASF41
	.byte	0xb
	.byte	0x1f
	.byte	0xc
	.4byte	0x94
	.byte	0
	.byte	0x7
	.4byte	.LASF42
	.byte	0xb
	.byte	0x20
	.byte	0x11
	.4byte	0x79
	.byte	0x8
	.byte	0x7
	.4byte	.LASF43
	.byte	0xb
	.byte	0x21
	.byte	0x18
	.4byte	0x13e
	.byte	0x10
	.byte	0
	.byte	0xa
	.4byte	.LASF44
	.2byte	0x2b0
	.byte	0xc
	.byte	0x6d
	.byte	0x8
	.4byte	0x444
	.byte	0xb
	.string	"id"
	.byte	0xc
	.byte	0x6e
	.byte	0x9
	.4byte	0xb3
	.byte	0
	.byte	0x7
	.4byte	.LASF45
	.byte	0xc
	.byte	0x6f
	.byte	0xc
	.4byte	0xb3
	.byte	0x4
	.byte	0x7
	.4byte	.LASF46
	.byte	0xc
	.byte	0x71
	.byte	0x9
	.4byte	0xf6
	.byte	0x8
	.byte	0x7
	.4byte	.LASF47
	.byte	0xc
	.byte	0x73
	.byte	0xf
	.4byte	0x46d
	.byte	0x28
	.byte	0xb
	.string	"uid"
	.byte	0xc
	.byte	0x75
	.byte	0x9
	.4byte	0xb3
	.byte	0x2c
	.byte	0xb
	.string	"gid"
	.byte	0xc
	.byte	0x76
	.byte	0x9
	.4byte	0xb3
	.byte	0x30
	.byte	0x7
	.4byte	.LASF48
	.byte	0xc
	.byte	0x78
	.byte	0x13
	.4byte	0x467
	.byte	0x38
	.byte	0x7
	.4byte	.LASF49
	.byte	0xc
	.byte	0x79
	.byte	0x13
	.4byte	0x1cf
	.byte	0x40
	.byte	0x7
	.4byte	.LASF37
	.byte	0xc
	.byte	0x7b
	.byte	0x14
	.4byte	0x274
	.byte	0x50
	.byte	0x7
	.4byte	.LASF50
	.byte	0xc
	.byte	0x7c
	.byte	0xc
	.4byte	0x268
	.byte	0x68
	.byte	0x7
	.4byte	.LASF51
	.byte	0xc
	.byte	0x7e
	.byte	0x9
	.4byte	0xb3
	.byte	0x70
	.byte	0x7
	.4byte	.LASF52
	.byte	0xc
	.byte	0x7f
	.byte	0xd
	.4byte	0xea
	.byte	0x78
	.byte	0x7
	.4byte	.LASF53
	.byte	0xc
	.byte	0x80
	.byte	0x9
	.4byte	0xb3
	.byte	0x80
	.byte	0x7
	.4byte	.LASF54
	.byte	0xc
	.byte	0x83
	.byte	0x10
	.4byte	0x494
	.byte	0x88
	.byte	0x7
	.4byte	.LASF55
	.byte	0xc
	.byte	0x84
	.byte	0x10
	.4byte	0x494
	.byte	0x90
	.byte	0x7
	.4byte	.LASF56
	.byte	0xc
	.byte	0x86
	.byte	0x11
	.4byte	0x79
	.byte	0x98
	.byte	0x7
	.4byte	.LASF41
	.byte	0xc
	.byte	0x87
	.byte	0xc
	.4byte	0x94
	.byte	0xa0
	.byte	0x7
	.4byte	.LASF57
	.byte	0xc
	.byte	0x88
	.byte	0xb
	.4byte	0x268
	.byte	0xa8
	.byte	0x7
	.4byte	.LASF58
	.byte	0xc
	.byte	0x8a
	.byte	0x8
	.4byte	0x45
	.byte	0xb0
	.byte	0x7
	.4byte	.LASF59
	.byte	0xc
	.byte	0x8c
	.byte	0x13
	.4byte	0x29c
	.byte	0xb8
	.byte	0xc
	.4byte	.LASF60
	.byte	0xc
	.byte	0x8d
	.byte	0x13
	.4byte	0x49f
	.2byte	0x268
	.byte	0xc
	.4byte	.LASF61
	.byte	0xc
	.byte	0x8e
	.byte	0x13
	.4byte	0x1cf
	.2byte	0x270
	.byte	0x10
	.string	"rr"
	.byte	0xc
	.byte	0x91
	.byte	0x4
	.4byte	0x479
	.2byte	0x280
	.byte	0xc
	.4byte	.LASF62
	.byte	0xc
	.byte	0xb7
	.byte	0x9
	.4byte	0xa0
	.2byte	0x290
	.byte	0xc
	.4byte	.LASF63
	.byte	0xc
	.byte	0xb9
	.byte	0xb
	.4byte	0x87
	.2byte	0x298
	.byte	0x10
	.string	"mm"
	.byte	0xc
	.byte	0xba
	.byte	0x13
	.4byte	0x467
	.2byte	0x2a0
	.byte	0xc
	.4byte	.LASF64
	.byte	0xc
	.byte	0xbd
	.byte	0x1a
	.4byte	0x1fd
	.2byte	0x2a8
	.byte	0
	.byte	0x11
	.4byte	.LASF65
	.byte	0xd
	.byte	0x14
	.byte	0x1e
	.4byte	0x450
	.byte	0x5
	.byte	0x8
	.4byte	0x2d2
	.byte	0x11
	.4byte	.LASF66
	.byte	0xd
	.byte	0x1f
	.byte	0x18
	.4byte	0x79
	.byte	0x12
	.4byte	.LASF48
	.byte	0x5
	.byte	0x8
	.4byte	0x462
	.byte	0x4
	.4byte	.LASF67
	.byte	0xc
	.byte	0x60
	.byte	0x16
	.4byte	0x58
	.byte	0x6
	.4byte	.LASF68
	.byte	0x10
	.byte	0xc
	.byte	0x8f
	.byte	0x9
	.4byte	0x494
	.byte	0x7
	.4byte	.LASF69
	.byte	0xc
	.byte	0x90
	.byte	0x14
	.4byte	0x1cf
	.byte	0
	.byte	0
	.byte	0x5
	.byte	0x8
	.4byte	0x45
	.byte	0x12
	.4byte	.LASF60
	.byte	0x5
	.byte	0x8
	.4byte	0x49a
	.byte	0x8
	.4byte	0x8d
	.4byte	0x4b6
	.byte	0x13
	.4byte	0x79
	.2byte	0x216
	.byte	0
	.byte	0x14
	.4byte	.LASF70
	.byte	0x1
	.byte	0x17
	.byte	0xd
	.4byte	0x4a5
	.2byte	0x217
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x1
	.byte	0x15
	.4byte	.LASF74
	.byte	0x1
	.byte	0x1d
	.byte	0x6
	.8byte	.LFB370
	.8byte	.LFE370-.LFB370
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
	.byte	0x16
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
	.byte	0x5
	.byte	0xf
	.byte	0
	.byte	0xb
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x6
	.byte	0x13
	.byte	0x1
	.byte	0x3
	.byte	0xe
	.byte	0xb
	.byte	0xb
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x7
	.byte	0xd
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
	.byte	0x38
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0x8
	.byte	0x1
	.byte	0x1
	.byte	0x49
	.byte	0x13
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x9
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0xa
	.byte	0x13
	.byte	0x1
	.byte	0x3
	.byte	0xe
	.byte	0xb
	.byte	0x5
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xb
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x38
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0xc
	.byte	0xd
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
	.byte	0x38
	.byte	0x5
	.byte	0
	.byte	0
	.byte	0xd
	.byte	0x13
	.byte	0x1
	.byte	0x3
	.byte	0xe
	.byte	0xb
	.byte	0xb
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0xe
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0x5
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x38
	.byte	0xb
	.byte	0
	.byte	0
	.byte	0xf
	.byte	0x13
	.byte	0x1
	.byte	0xb
	.byte	0xb
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x1
	.byte	0x13
	.byte	0
	.byte	0
	.byte	0x10
	.byte	0xd
	.byte	0
	.byte	0x3
	.byte	0x8
	.byte	0x3a
	.byte	0xb
	.byte	0x3b
	.byte	0xb
	.byte	0x39
	.byte	0xb
	.byte	0x49
	.byte	0x13
	.byte	0x38
	.byte	0x5
	.byte	0
	.byte	0
	.byte	0x11
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
	.byte	0x3f
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0x12
	.byte	0x13
	.byte	0
	.byte	0x3
	.byte	0xe
	.byte	0x3c
	.byte	0x19
	.byte	0
	.byte	0
	.byte	0x13
	.byte	0x21
	.byte	0
	.byte	0x49
	.byte	0x13
	.byte	0x2f
	.byte	0x5
	.byte	0
	.byte	0
	.byte	0x14
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
	.byte	0x1c
	.byte	0x3
	.byte	0
	.byte	0
	.byte	0x15
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
	.8byte	.LFB370
	.8byte	.LFE370-.LFB370
	.8byte	0
	.8byte	0
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.8byte	.LFB370
	.8byte	.LFE370
	.8byte	0
	.8byte	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF63:
	.string	"comm"
.LASF13:
	.string	"bool"
.LASF7:
	.string	"__u64"
.LASF58:
	.string	"exit_status"
.LASF47:
	.string	"state"
.LASF3:
	.string	"short int"
.LASF52:
	.string	"cpu_mask"
.LASF15:
	.string	"id_t"
.LASF44:
	.string	"task_struct"
.LASF16:
	.string	"cpumask_t"
.LASF5:
	.string	"long long int"
.LASF60:
	.string	"fdTable"
.LASF39:
	.string	"sigset"
.LASF51:
	.string	"cpu_id"
.LASF59:
	.string	"arch"
.LASF25:
	.string	"preempt_count"
.LASF64:
	.string	"preempt_notifiers"
.LASF6:
	.string	"__u32"
.LASF35:
	.string	"bitmap"
.LASF33:
	.string	"hlist_node"
.LASF37:
	.string	"sigpending"
.LASF45:
	.string	"rank"
.LASF53:
	.string	"cpu_target_id"
.LASF73:
	.string	"/tmp/home/kitten"
.LASF19:
	.string	"bits"
.LASF69:
	.string	"sched_link"
.LASF10:
	.string	"long int"
.LASF56:
	.string	"ptrace"
.LASF31:
	.string	"hlist_head"
.LASF22:
	.string	"kern_sp0"
.LASF54:
	.string	"set_child_tid"
.LASF71:
	.ascii	"GNU C99 10.3.0 -mabi=lp64d -march=rv64imafdc -g -g -O2 "
	.string	"-std=gnu99 -fstack-protector-strong -fno-strict-aliasing -fno-strict-overflow -fno-common -fno-pie -fno-stack-protector -fgnu89-inline -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-builtin -ffunction-sections -fno-reorder-blocks -funit-at-a-time"
.LASF57:
	.string	"saved_sigmask"
.LASF2:
	.string	"unsigned char"
.LASF27:
	.string	"bad_cause"
.LASF23:
	.string	"kern_sp"
.LASF1:
	.string	"signed char"
.LASF41:
	.string	"flags"
.LASF8:
	.string	"long long unsigned int"
.LASF12:
	.string	"uint32_t"
.LASF4:
	.string	"unsigned int"
.LASF40:
	.string	"arch_task"
.LASF34:
	.string	"pprev"
.LASF50:
	.string	"sigblocked"
.LASF43:
	.string	"thread"
.LASF0:
	.string	"short unsigned int"
.LASF67:
	.string	"taskstate_t"
.LASF17:
	.string	"cpumask"
.LASF11:
	.string	"char"
.LASF26:
	.string	"fstate"
.LASF72:
	.string	"arch/riscv64/kernel/asm-offsets.c"
.LASF38:
	.string	"list"
.LASF14:
	.string	"_Bool"
.LASF46:
	.string	"name"
.LASF70:
	.string	"syscalls"
.LASF68:
	.string	"task_rr"
.LASF9:
	.string	"long unsigned int"
.LASF36:
	.string	"sigset_t"
.LASF49:
	.string	"aspace_link"
.LASF24:
	.string	"user_sp"
.LASF65:
	.string	"riscv_current_is_tp"
.LASF42:
	.string	"addr_limit"
.LASF18:
	.string	"__riscv_d_ext_state"
.LASF61:
	.string	"migrate_link"
.LASF74:
	.string	"asm_offsets"
.LASF62:
	.string	"sched_irqs_on"
.LASF20:
	.string	"fcsr"
.LASF21:
	.string	"thread_struct"
.LASF48:
	.string	"aspace"
.LASF55:
	.string	"clear_child_tid"
.LASF30:
	.string	"prev"
.LASF66:
	.string	"current_stack_pointer"
.LASF29:
	.string	"next"
.LASF32:
	.string	"first"
.LASF28:
	.string	"list_head"
	.ident	"GCC: (Buildroot 2022.02.1) 10.3.0"
	.section	.note.GNU-stack,"",@progbits
