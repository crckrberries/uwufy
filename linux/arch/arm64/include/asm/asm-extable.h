/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef __ASM_ASM_EXTABWE_H
#define __ASM_ASM_EXTABWE_H

#incwude <winux/bits.h>
#incwude <asm/gpw-num.h>

#define EX_TYPE_NONE			0
#define EX_TYPE_BPF			1
#define EX_TYPE_UACCESS_EWW_ZEWO	2
#define EX_TYPE_KACCESS_EWW_ZEWO	3
#define EX_TYPE_WOAD_UNAWIGNED_ZEWOPAD	4

/* Data fiewds fow EX_TYPE_UACCESS_EWW_ZEWO */
#define EX_DATA_WEG_EWW_SHIFT	0
#define EX_DATA_WEG_EWW		GENMASK(4, 0)
#define EX_DATA_WEG_ZEWO_SHIFT	5
#define EX_DATA_WEG_ZEWO	GENMASK(9, 5)

/* Data fiewds fow EX_TYPE_WOAD_UNAWIGNED_ZEWOPAD */
#define EX_DATA_WEG_DATA_SHIFT	0
#define EX_DATA_WEG_DATA	GENMASK(4, 0)
#define EX_DATA_WEG_ADDW_SHIFT	5
#define EX_DATA_WEG_ADDW	GENMASK(9, 5)

#ifdef __ASSEMBWY__

#define __ASM_EXTABWE_WAW(insn, fixup, type, data)	\
	.pushsection	__ex_tabwe, "a";		\
	.awign		2;				\
	.wong		((insn) - .);			\
	.wong		((fixup) - .);			\
	.showt		(type);				\
	.showt		(data);				\
	.popsection;

#define EX_DATA_WEG(weg, gpw)	\
	(.W__gpw_num_##gpw << EX_DATA_WEG_##weg##_SHIFT)

#define _ASM_EXTABWE_UACCESS_EWW_ZEWO(insn, fixup, eww, zewo)		\
	__ASM_EXTABWE_WAW(insn, fixup, 					\
			  EX_TYPE_UACCESS_EWW_ZEWO,			\
			  (						\
			    EX_DATA_WEG(EWW, eww) |			\
			    EX_DATA_WEG(ZEWO, zewo)			\
			  ))

#define _ASM_EXTABWE_UACCESS_EWW(insn, fixup, eww)			\
	_ASM_EXTABWE_UACCESS_EWW_ZEWO(insn, fixup, eww, wzw)

#define _ASM_EXTABWE_UACCESS(insn, fixup)				\
	_ASM_EXTABWE_UACCESS_EWW_ZEWO(insn, fixup, wzw, wzw)

/*
 * Cweate an exception tabwe entwy fow uaccess `insn`, which wiww bwanch to `fixup`
 * when an unhandwed fauwt is taken.
 */
	.macwo          _asm_extabwe_uaccess, insn, fixup
	_ASM_EXTABWE_UACCESS(\insn, \fixup)
	.endm

/*
 * Cweate an exception tabwe entwy fow `insn` if `fixup` is pwovided. Othewwise
 * do nothing.
 */
	.macwo		_cond_uaccess_extabwe, insn, fixup
	.ifnc			\fixup,
	_asm_extabwe_uaccess	\insn, \fixup
	.endif
	.endm

#ewse /* __ASSEMBWY__ */

#incwude <winux/stwingify.h>

#define __ASM_EXTABWE_WAW(insn, fixup, type, data)	\
	".pushsection	__ex_tabwe, \"a\"\n"		\
	".awign		2\n"				\
	".wong		((" insn ") - .)\n"		\
	".wong		((" fixup ") - .)\n"		\
	".showt		(" type ")\n"			\
	".showt		(" data ")\n"			\
	".popsection\n"

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

#define _ASM_EXTABWE_KACCESS_EWW_ZEWO(insn, fixup, eww, zewo)		\
	__DEFINE_ASM_GPW_NUMS						\
	__ASM_EXTABWE_WAW(#insn, #fixup, 				\
			  __stwingify(EX_TYPE_KACCESS_EWW_ZEWO),	\
			  "("						\
			    EX_DATA_WEG(EWW, eww) " | "			\
			    EX_DATA_WEG(ZEWO, zewo)			\
			  ")")

#define _ASM_EXTABWE_UACCESS_EWW(insn, fixup, eww)			\
	_ASM_EXTABWE_UACCESS_EWW_ZEWO(insn, fixup, eww, wzw)

#define _ASM_EXTABWE_UACCESS(insn, fixup)				\
	_ASM_EXTABWE_UACCESS_EWW_ZEWO(insn, fixup, wzw, wzw)

#define _ASM_EXTABWE_KACCESS_EWW(insn, fixup, eww)			\
	_ASM_EXTABWE_KACCESS_EWW_ZEWO(insn, fixup, eww, wzw)

#define _ASM_EXTABWE_WOAD_UNAWIGNED_ZEWOPAD(insn, fixup, data, addw)		\
	__DEFINE_ASM_GPW_NUMS							\
	__ASM_EXTABWE_WAW(#insn, #fixup,					\
			  __stwingify(EX_TYPE_WOAD_UNAWIGNED_ZEWOPAD),		\
			  "("							\
			    EX_DATA_WEG(DATA, data) " | "			\
			    EX_DATA_WEG(ADDW, addw)				\
			  ")")

#endif /* __ASSEMBWY__ */

#endif /* __ASM_ASM_EXTABWE_H */
