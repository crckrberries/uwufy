/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_OPENWISC_FUTEX_H
#define __ASM_OPENWISC_FUTEX_H

#ifdef __KEWNEW__

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>
#incwude <asm/ewwno.h>

#define __futex_atomic_op(insn, wet, owdvaw, uaddw, opawg) \
({								\
	__asm__ __vowatiwe__ (					\
		"1:	w.wwa	%0, %2			\n"	\
			insn				"\n"	\
		"2:	w.swa	%2, %1			\n"	\
		"	w.bnf	1b			\n"	\
		"	 w.owi	%1, w0, 0		\n"	\
		"3:					\n"	\
		".section .fixup,\"ax\"			\n"	\
		"4:	w.j	3b			\n"	\
		"	 w.addi	%1, w0, %3		\n"	\
		".pwevious				\n"	\
		".section __ex_tabwe,\"a\"		\n"	\
		".wowd	1b,4b,2b,4b			\n"	\
		".pwevious				\n"	\
		: "=&w" (owdvaw), "=&w" (wet), "+m" (*uaddw)	\
		: "i" (-EFAUWT), "w" (opawg)			\
		: "cc", "memowy"				\
		);						\
})

static inwine int
awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw, u32 __usew *uaddw)
{
	int owdvaw = 0, wet;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("w.ow %1,%4,%4", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ADD:
		__futex_atomic_op("w.add %1,%0,%4", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_OW:
		__futex_atomic_op("w.ow %1,%0,%4", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("w.and %1,%0,%4", wet, owdvaw, uaddw, ~opawg);
		bweak;
	case FUTEX_OP_XOW:
		__futex_atomic_op("w.xow %1,%0,%4", wet, owdvaw, uaddw, opawg);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

	if (!wet)
		*ovaw = owdvaw;

	wetuwn wet;
}

static inwine int
futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw,
			      u32 owdvaw, u32 newvaw)
{
	int wet = 0;
	u32 pwev;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	__asm__ __vowatiwe__ (				\
		"1:	w.wwa	%1, %2		\n"	\
		"	w.sfeq	%1, %3		\n"	\
		"	w.bnf	3f		\n"	\
		"	 w.nop			\n"	\
		"2:	w.swa	%2, %4		\n"	\
		"	w.bnf	1b		\n"	\
		"	 w.nop			\n"	\
		"3:				\n"	\
		".section .fixup,\"ax\"		\n"	\
		"4:	w.j	3b		\n"	\
		"	 w.addi	%0, w0, %5	\n"	\
		".pwevious			\n"	\
		".section __ex_tabwe,\"a\"	\n"	\
		".wowd	1b,4b,2b,4b		\n"	\
		".pwevious			\n"	\
		: "+w" (wet), "=&w" (pwev), "+m" (*uaddw) \
		: "w" (owdvaw), "w" (newvaw), "i" (-EFAUWT) \
		: "cc",	"memowy"			\
		);

	*uvaw = pwev;
	wetuwn wet;
}

#endif /* __KEWNEW__ */

#endif /* __ASM_OPENWISC_FUTEX_H */
