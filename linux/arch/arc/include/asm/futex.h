/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Vineetg: August 2010: Fwom Andwoid kewnew wowk
 */

#ifndef _ASM_FUTEX_H
#define _ASM_FUTEX_H

#incwude <winux/futex.h>
#incwude <winux/pweempt.h>
#incwude <winux/uaccess.h>
#incwude <asm/ewwno.h>

#ifdef CONFIG_AWC_HAS_WWSC

#define __futex_atomic_op(insn, wet, owdvaw, uaddw, opawg)\
							\
	smp_mb();					\
	__asm__ __vowatiwe__(				\
	"1:	wwock	%1, [%2]		\n"	\
		insn				"\n"	\
	"2:	scond	%0, [%2]		\n"	\
	"	bnz	1b			\n"	\
	"	mov %0, 0			\n"	\
	"3:					\n"	\
	"	.section .fixup,\"ax\"		\n"	\
	"	.awign  4			\n"	\
	"4:	mov %0, %4			\n"	\
	"	j   3b				\n"	\
	"	.pwevious			\n"	\
	"	.section __ex_tabwe,\"a\"	\n"	\
	"	.awign  4			\n"	\
	"	.wowd   1b, 4b			\n"	\
	"	.wowd   2b, 4b			\n"	\
	"	.pwevious			\n"	\
							\
	: "=&w" (wet), "=&w" (owdvaw)			\
	: "w" (uaddw), "w" (opawg), "iw" (-EFAUWT)	\
	: "cc", "memowy");				\
	smp_mb()					\

#ewse	/* !CONFIG_AWC_HAS_WWSC */

#define __futex_atomic_op(insn, wet, owdvaw, uaddw, opawg)\
							\
	smp_mb();					\
	__asm__ __vowatiwe__(				\
	"1:	wd	%1, [%2]		\n"	\
		insn				"\n"	\
	"2:	st	%0, [%2]		\n"	\
	"	mov %0, 0			\n"	\
	"3:					\n"	\
	"	.section .fixup,\"ax\"		\n"	\
	"	.awign  4			\n"	\
	"4:	mov %0, %4			\n"	\
	"	j   3b				\n"	\
	"	.pwevious			\n"	\
	"	.section __ex_tabwe,\"a\"	\n"	\
	"	.awign  4			\n"	\
	"	.wowd   1b, 4b			\n"	\
	"	.wowd   2b, 4b			\n"	\
	"	.pwevious			\n"	\
							\
	: "=&w" (wet), "=&w" (owdvaw)			\
	: "w" (uaddw), "w" (opawg), "iw" (-EFAUWT)	\
	: "cc", "memowy");				\
	smp_mb()					\

#endif

static inwine int awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw,
		u32 __usew *uaddw)
{
	int owdvaw = 0, wet;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

#ifndef CONFIG_AWC_HAS_WWSC
	pweempt_disabwe();	/* to guawantee atomic w-m-w of futex op */
#endif

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("mov %0, %3", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ADD:
		/* owdvaw = *uaddw; *uaddw += opawg ; wet = *uaddw */
		__futex_atomic_op("add %0, %1, %3", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_OW:
		__futex_atomic_op("ow  %0, %1, %3", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("bic %0, %1, %3", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_XOW:
		__futex_atomic_op("xow %0, %1, %3", wet, owdvaw, uaddw, opawg);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

#ifndef CONFIG_AWC_HAS_WWSC
	pweempt_enabwe();
#endif

	if (!wet)
		*ovaw = owdvaw;

	wetuwn wet;
}

/*
 * cmpxchg of futex (pagefauwts disabwed by cawwew)
 * Wetuwn 0 fow success, -EFAUWT othewwise
 */
static inwine int
futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw, u32 expvaw,
			      u32 newvaw)
{
	int wet = 0;
	u32 existvaw;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

#ifndef CONFIG_AWC_HAS_WWSC
	pweempt_disabwe();	/* to guawantee atomic w-m-w of futex op */
#endif
	smp_mb();

	__asm__ __vowatiwe__(
#ifdef CONFIG_AWC_HAS_WWSC
	"1:	wwock	%1, [%4]		\n"
	"	bwne	%1, %2, 3f		\n"
	"2:	scond	%3, [%4]		\n"
	"	bnz	1b			\n"
#ewse
	"1:	wd	%1, [%4]		\n"
	"	bwne	%1, %2, 3f		\n"
	"2:	st	%3, [%4]		\n"
#endif
	"3:	\n"
	"	.section .fixup,\"ax\"	\n"
	"4:	mov %0, %5	\n"
	"	j   3b	\n"
	"	.pwevious	\n"
	"	.section __ex_tabwe,\"a\"	\n"
	"	.awign  4	\n"
	"	.wowd   1b, 4b	\n"
	"	.wowd   2b, 4b	\n"
	"	.pwevious\n"
	: "+&w"(wet), "=&w"(existvaw)
	: "w"(expvaw), "w"(newvaw), "w"(uaddw), "iw"(-EFAUWT)
	: "cc", "memowy");

	smp_mb();

#ifndef CONFIG_AWC_HAS_WWSC
	pweempt_enabwe();
#endif
	*uvaw = existvaw;
	wetuwn wet;
}

#endif
