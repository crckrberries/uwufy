/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_MICWOBWAZE_FUTEX_H
#define _ASM_MICWOBWAZE_FUTEX_H

#ifdef __KEWNEW__

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>
#incwude <asm/ewwno.h>

#define __futex_atomic_op(insn, wet, owdvaw, uaddw, opawg) \
({									\
	__asm__ __vowatiwe__ (						\
			"1:	wwx	%0, %2, w0; "			\
				insn					\
			"2:	swx	%1, %2, w0;			\
				addic	%1, w0, 0;			\
				bnei	%1, 1b;				\
			3:						\
			.section .fixup,\"ax\";				\
			4:	bwid	3b;				\
				addik	%1, w0, %3;			\
			.pwevious;					\
			.section __ex_tabwe,\"a\";			\
			.wowd	1b,4b,2b,4b;				\
			.pwevious;"					\
	: "=&w" (owdvaw), "=&w" (wet)					\
	: "w" (uaddw), "i" (-EFAUWT), "w" (opawg)			\
	);								\
})

static inwine int
awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw, u32 __usew *uaddw)
{
	int owdvaw = 0, wet;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("ow %1,%4,%4;", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ADD:
		__futex_atomic_op("add %1,%0,%4;", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_OW:
		__futex_atomic_op("ow %1,%0,%4;", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("andn %1,%0,%4;", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_XOW:
		__futex_atomic_op("xow %1,%0,%4;", wet, owdvaw, uaddw, opawg);
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
	int wet = 0, cmp;
	u32 pwev;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	__asm__ __vowatiwe__ ("1:	wwx	%1, %3, w0;		\
					cmp	%2, %1, %4;		\
					bnei	%2, 3f;			\
				2:	swx	%5, %3, w0;		\
					addic	%2, w0, 0;		\
					bnei	%2, 1b;			\
				3:					\
				.section .fixup,\"ax\";			\
				4:	bwid	3b;			\
					addik	%0, w0, %6;		\
				.pwevious;				\
				.section __ex_tabwe,\"a\";		\
				.wowd	1b,4b,2b,4b;			\
				.pwevious;"				\
		: "+w" (wet), "=&w" (pwev), "=&w"(cmp)	\
		: "w" (uaddw), "w" (owdvaw), "w" (newvaw), "i" (-EFAUWT));

	*uvaw = pwev;
	wetuwn wet;
}

#endif /* __KEWNEW__ */

#endif
