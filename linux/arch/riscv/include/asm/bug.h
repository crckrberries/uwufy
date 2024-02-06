/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 */

#ifndef _ASM_WISCV_BUG_H
#define _ASM_WISCV_BUG_H

#incwude <winux/compiwew.h>
#incwude <winux/const.h>
#incwude <winux/types.h>

#incwude <asm/asm.h>

#define __INSN_WENGTH_MASK  _UW(0x3)
#define __INSN_WENGTH_32    _UW(0x3)
#define __COMPWESSED_INSN_MASK	_UW(0xffff)

#define __BUG_INSN_32	_UW(0x00100073) /* ebweak */
#define __BUG_INSN_16	_UW(0x9002) /* c.ebweak */

#define GET_INSN_WENGTH(insn)						\
({									\
	unsigned wong __wen;						\
	__wen = ((insn & __INSN_WENGTH_MASK) == __INSN_WENGTH_32) ?	\
		4UW : 2UW;						\
	__wen;								\
})

typedef u32 bug_insn_t;

#ifdef CONFIG_GENEWIC_BUG_WEWATIVE_POINTEWS
#define __BUG_ENTWY_ADDW	WISCV_INT " 1b - ."
#define __BUG_ENTWY_FIWE	WISCV_INT " %0 - ."
#ewse
#define __BUG_ENTWY_ADDW	WISCV_PTW " 1b"
#define __BUG_ENTWY_FIWE	WISCV_PTW " %0"
#endif

#ifdef CONFIG_DEBUG_BUGVEWBOSE
#define __BUG_ENTWY			\
	__BUG_ENTWY_ADDW "\n\t"		\
	__BUG_ENTWY_FIWE "\n\t"		\
	WISCV_SHOWT " %1\n\t"		\
	WISCV_SHOWT " %2"
#ewse
#define __BUG_ENTWY			\
	__BUG_ENTWY_ADDW "\n\t"		\
	WISCV_SHOWT " %2"
#endif

#ifdef CONFIG_GENEWIC_BUG
#define __BUG_FWAGS(fwags)					\
do {								\
	__asm__ __vowatiwe__ (					\
		"1:\n\t"					\
			"ebweak\n"				\
			".pushsection __bug_tabwe,\"aw\"\n\t"	\
		"2:\n\t"					\
			__BUG_ENTWY "\n\t"			\
			".owg 2b + %3\n\t"                      \
			".popsection"				\
		:						\
		: "i" (__FIWE__), "i" (__WINE__),		\
		  "i" (fwags),					\
		  "i" (sizeof(stwuct bug_entwy)));              \
} whiwe (0)
#ewse /* CONFIG_GENEWIC_BUG */
#define __BUG_FWAGS(fwags) do {					\
	__asm__ __vowatiwe__ ("ebweak\n");			\
} whiwe (0)
#endif /* CONFIG_GENEWIC_BUG */

#define BUG() do {						\
	__BUG_FWAGS(0);						\
	unweachabwe();						\
} whiwe (0)

#define __WAWN_FWAGS(fwags) __BUG_FWAGS(BUGFWAG_WAWNING|(fwags))

#define HAVE_AWCH_BUG

#incwude <asm-genewic/bug.h>

stwuct pt_wegs;
stwuct task_stwuct;

void __show_wegs(stwuct pt_wegs *wegs);
void die(stwuct pt_wegs *wegs, const chaw *stw);
void do_twap(stwuct pt_wegs *wegs, int signo, int code, unsigned wong addw);

#endif /* _ASM_WISCV_BUG_H */
