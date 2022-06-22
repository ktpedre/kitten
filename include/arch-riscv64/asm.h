/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2015 Regents of the University of California
 */

#ifndef _ASM_RISCV_ASM_H
#define _ASM_RISCV_ASM_H

#ifdef __ASSEMBLY__
#define __ASM_STR(x)	x
#else
#define __ASM_STR(x)	#x
#endif

#if __riscv_xlen == 64
#define __REG_SEL(a, b)	__ASM_STR(a)
#elif __riscv_xlen == 32
#define __REG_SEL(a, b)	__ASM_STR(b)
#else
#error "Unexpected __riscv_xlen"
#endif

#define REG_L		__REG_SEL(ld, lw)
#define REG_S		__REG_SEL(sd, sw)
#define REG_SC		__REG_SEL(sc.d, sc.w)
#define REG_ASM		__REG_SEL(.dword, .word)
#define SZREG		__REG_SEL(8, 4)
#define LGREG		__REG_SEL(3, 2)

#if __SIZEOF_POINTER__ == 8
#ifdef __ASSEMBLY__
#define RISCV_PTR		.dword
#define RISCV_SZPTR		8
#define RISCV_LGPTR		3
#else
#define RISCV_PTR		".dword"
#define RISCV_SZPTR		"8"
#define RISCV_LGPTR		"3"
#endif
#elif __SIZEOF_POINTER__ == 4
#ifdef __ASSEMBLY__
#define RISCV_PTR		.word
#define RISCV_SZPTR		4
#define RISCV_LGPTR		2
#else
#define RISCV_PTR		".word"
#define RISCV_SZPTR		"4"
#define RISCV_LGPTR		"2"
#endif
#else
#error "Unexpected __SIZEOF_POINTER__"
#endif

#if (__SIZEOF_INT__ == 4)
#define RISCV_INT		__ASM_STR(.word)
#define RISCV_SZINT		__ASM_STR(4)
#define RISCV_LGINT		__ASM_STR(2)
#else
#error "Unexpected __SIZEOF_INT__"
#endif

#if (__SIZEOF_SHORT__ == 2)
#define RISCV_SHORT		__ASM_STR(.half)
#define RISCV_SZSHORT		__ASM_STR(2)
#define RISCV_LGSHORT		__ASM_STR(1)
#else
#error "Unexpected __SIZEOF_SHORT__"
#endif

#define EX_TYPE_NONE			0
#define EX_TYPE_FIXUP			1
#define EX_TYPE_BPF			2
#define EX_TYPE_UACCESS_ERR_ZERO	3

/* #define __ASM_EXTABLE_RAW(insn, fixup, type, data)	\ */
/* 	".pushsection	__ex_table, \"a\"\n"		\ */
/* 	".balign	4\n"				\ */
/* 	".long		((" insn ") - .)\n"		\ */
/* 	".long		((" fixup ") - .)\n"		\ */
/* 	".short		(" type ")\n"			\ */
/* 	".short		(" data ")\n"			\ */
/* 	".popsection\n" */

/* #define _ASM_EXTABLE(insn, fixup)	\ */
/* 	__ASM_EXTABLE_RAW(#insn, #fixup, __stringify(EX_TYPE_FIXUP), "0") */

/* /\* Exception table entry *\/ */
/* # define _ASM_EXTABLE(from,to) \ */
/* 	__ASM_EX_SEC	\ */
/* 	_ASM_ALIGN "\n" \ */
/* 	_ASM_PTR #from "," #to "\n" \ */
/* 	" .previous\n" */

#endif /* _ASM_RISCV_ASM_H */
