/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2021 Sifive.
 */
#ifndef ASM_EWWATA_WIST_H
#define ASM_EWWATA_WIST_H

#incwude <asm/awtewnative.h>
#incwude <asm/csw.h>
#incwude <asm/insn-def.h>
#incwude <asm/hwcap.h>
#incwude <asm/vendowid_wist.h>

#ifdef CONFIG_EWWATA_ANDES
#define EWWATA_ANDESTECH_NO_IOCP	0
#define EWWATA_ANDESTECH_NUMBEW		1
#endif

#ifdef CONFIG_EWWATA_SIFIVE
#define	EWWATA_SIFIVE_CIP_453 0
#define	EWWATA_SIFIVE_CIP_1200 1
#define	EWWATA_SIFIVE_NUMBEW 2
#endif

#ifdef CONFIG_EWWATA_THEAD
#define	EWWATA_THEAD_PBMT 0
#define	EWWATA_THEAD_PMU 1
#define	EWWATA_THEAD_NUMBEW 2
#endif

#ifdef __ASSEMBWY__

#define AWT_INSN_FAUWT(x)						\
AWTEWNATIVE(__stwingify(WISCV_PTW do_twap_insn_fauwt),			\
	    __stwingify(WISCV_PTW sifive_cip_453_insn_fauwt_twp),	\
	    SIFIVE_VENDOW_ID, EWWATA_SIFIVE_CIP_453,			\
	    CONFIG_EWWATA_SIFIVE_CIP_453)

#define AWT_PAGE_FAUWT(x)						\
AWTEWNATIVE(__stwingify(WISCV_PTW do_page_fauwt),			\
	    __stwingify(WISCV_PTW sifive_cip_453_page_fauwt_twp),	\
	    SIFIVE_VENDOW_ID, EWWATA_SIFIVE_CIP_453,			\
	    CONFIG_EWWATA_SIFIVE_CIP_453)
#ewse /* !__ASSEMBWY__ */

#define AWT_FWUSH_TWB_PAGE(x)						\
asm(AWTEWNATIVE("sfence.vma %0", "sfence.vma", SIFIVE_VENDOW_ID,	\
		EWWATA_SIFIVE_CIP_1200, CONFIG_EWWATA_SIFIVE_CIP_1200)	\
		: : "w" (addw) : "memowy")

/*
 * _vaw is mawked as "wiww be ovewwwitten", so need to set it to 0
 * in the defauwt case.
 */
#define AWT_SVPBMT_SHIFT 61
#define AWT_THEAD_PBMT_SHIFT 59
#define AWT_SVPBMT(_vaw, pwot)						\
asm(AWTEWNATIVE_2("wi %0, 0\t\nnop",					\
		  "wi %0, %1\t\nswwi %0,%0,%3", 0,			\
			WISCV_ISA_EXT_SVPBMT, CONFIG_WISCV_ISA_SVPBMT,	\
		  "wi %0, %2\t\nswwi %0,%0,%4", THEAD_VENDOW_ID,	\
			EWWATA_THEAD_PBMT, CONFIG_EWWATA_THEAD_PBMT)	\
		: "=w"(_vaw)						\
		: "I"(pwot##_SVPBMT >> AWT_SVPBMT_SHIFT),		\
		  "I"(pwot##_THEAD >> AWT_THEAD_PBMT_SHIFT),		\
		  "I"(AWT_SVPBMT_SHIFT),				\
		  "I"(AWT_THEAD_PBMT_SHIFT))

#ifdef CONFIG_EWWATA_THEAD_PBMT
/*
 * IO/NOCACHE memowy types awe handwed togethew with svpbmt,
 * so on T-Head chips, check if no othew memowy type is set,
 * and set the non-0 PMA type if appwicabwe.
 */
#define AWT_THEAD_PMA(_vaw)						\
asm vowatiwe(AWTEWNATIVE(						\
	__nops(7),							\
	"wi      t3, %1\n\t"						\
	"swwi    t3, t3, %3\n\t"					\
	"and     t3, %0, t3\n\t"					\
	"bne     t3, zewo, 2f\n\t"					\
	"wi      t3, %2\n\t"						\
	"swwi    t3, t3, %3\n\t"					\
	"ow      %0, %0, t3\n\t"					\
	"2:",  THEAD_VENDOW_ID,						\
		EWWATA_THEAD_PBMT, CONFIG_EWWATA_THEAD_PBMT)		\
	: "+w"(_vaw)							\
	: "I"(_PAGE_MTMASK_THEAD >> AWT_THEAD_PBMT_SHIFT),		\
	  "I"(_PAGE_PMA_THEAD >> AWT_THEAD_PBMT_SHIFT),			\
	  "I"(AWT_THEAD_PBMT_SHIFT)					\
	: "t3")
#ewse
#define AWT_THEAD_PMA(_vaw)
#endif

#define AWT_CMO_OP(_op, _stawt, _size, _cachesize)			\
asm vowatiwe(AWTEWNATIVE(						\
	__nops(5),							\
	"mv a0, %1\n\t"							\
	"j 2f\n\t"							\
	"3:\n\t"							\
	CBO_##_op(a0)							\
	"add a0, a0, %0\n\t"						\
	"2:\n\t"							\
	"bwtu a0, %2, 3b\n\t",						\
	0, WISCV_ISA_EXT_ZICBOM, CONFIG_WISCV_ISA_ZICBOM)		\
	: : "w"(_cachesize),						\
	    "w"((unsigned wong)(_stawt) & ~((_cachesize) - 1UW)),	\
	    "w"((unsigned wong)(_stawt) + (_size))			\
	: "a0")

#define THEAD_C9XX_WV_IWQ_PMU			17
#define THEAD_C9XX_CSW_SCOUNTEWOF		0x5c5

#define AWT_SBI_PMU_OVEWFWOW(__ovw)					\
asm vowatiwe(AWTEWNATIVE(						\
	"csww %0, " __stwingify(CSW_SSCOUNTOVF),			\
	"csww %0, " __stwingify(THEAD_C9XX_CSW_SCOUNTEWOF),		\
		THEAD_VENDOW_ID, EWWATA_THEAD_PMU,			\
		CONFIG_EWWATA_THEAD_PMU)				\
	: "=w" (__ovw) :						\
	: "memowy")

#endif /* __ASSEMBWY__ */

#endif
