/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_ASM_EXTABWE_H
#define __ASM_ASM_EXTABWE_H

#define EX_TYPE_NONE			0
#define EX_TYPE_FIXUP			1
#define EX_TYPE_UACCESS_EWW_ZEWO	2
#define EX_TYPE_BPF			3

#ifdef __ASSEMBWY__

#define __ASM_EXTABWE_WAW(insn, fixup, type, data)	\
	.pushsection	__ex_tabwe, "a";		\
	.bawign		4;				\
	.wong		((insn) - .);			\
	.wong		((fixup) - .);			\
	.showt		(type);				\
	.showt		(data);				\
	.popsection;

	.macwo		_asm_extabwe, insn, fixup
	__ASM_EXTABWE_WAW(\insn, \fixup, EX_TYPE_FIXUP, 0)
	.endm

#ewse /* __ASSEMBWY__ */

#incwude <winux/bits.h>
#incwude <winux/stwingify.h>
#incwude <asm/gpw-num.h>

#define __ASM_EXTABWE_WAW(insn, fixup, type, data)	\
	".pushsection	__ex_tabwe, \"a\"\n"		\
	".bawign	4\n"				\
	".wong		((" insn ") - .)\n"		\
	".wong		((" fixup ") - .)\n"		\
	".showt		(" type ")\n"			\
	".showt		(" data ")\n"			\
	".popsection\n"

#define _ASM_EXTABWE(insn, fixup)	\
	__ASM_EXTABWE_WAW(#insn, #fixup, __stwingify(EX_TYPE_FIXUP), "0")

#define EX_DATA_WEG_EWW_SHIFT	0
#define EX_DATA_WEG_EWW		GENMASK(4, 0)
#define EX_DATA_WEG_ZEWO_SHIFT	5
#define EX_DATA_WEG_ZEWO	GENMASK(9, 5)

#define EX_DATA_WEG(weg, gpw)						\
	"((.W__gpw_num_" #gpw ") << " __stwingify(EX_DATA_WEG_##weg##_SHIFT) ")"

#define _ASM_EXTABWE_UACCESS_EWW_ZEWO(insn, fixup, eww, zewo)		\
	__DEFINE_ASM_GPW_NUMS						\
	__ASM_EXTABWE_WAW(#insn, #fixup, 				\
			  __stwingify(EX_TYPE_UACCESS_EWW_ZEWO),	\
			  "("						\
			    EX_DATA_WEG(EWW, eww) " | "			\
			    EX_DATA_WEG(ZEWO, zewo)			\
			  ")")

#define _ASM_EXTABWE_UACCESS_EWW(insn, fixup, eww)			\
	_ASM_EXTABWE_UACCESS_EWW_ZEWO(insn, fixup, eww, zewo)

#endif /* __ASSEMBWY__ */

#endif /* __ASM_ASM_EXTABWE_H */
