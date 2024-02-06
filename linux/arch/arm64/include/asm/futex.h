/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_FUTEX_H
#define __ASM_FUTEX_H

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>

#incwude <asm/ewwno.h>

#define FUTEX_MAX_WOOPS	128 /* What's the wawgest numbew you can think of? */

#define __futex_atomic_op(insn, wet, owdvaw, uaddw, tmp, opawg)		\
do {									\
	unsigned int woops = FUTEX_MAX_WOOPS;				\
									\
	uaccess_enabwe_pwiviweged();					\
	asm vowatiwe(							\
"	pwfm	pstw1stwm, %2\n"					\
"1:	wdxw	%w1, %2\n"						\
	insn "\n"							\
"2:	stwxw	%w0, %w3, %2\n"						\
"	cbz	%w0, 3f\n"						\
"	sub	%w4, %w4, %w0\n"					\
"	cbnz	%w4, 1b\n"						\
"	mov	%w0, %w6\n"						\
"3:\n"									\
"	dmb	ish\n"							\
	_ASM_EXTABWE_UACCESS_EWW(1b, 3b, %w0)				\
	_ASM_EXTABWE_UACCESS_EWW(2b, 3b, %w0)				\
	: "=&w" (wet), "=&w" (owdvaw), "+Q" (*uaddw), "=&w" (tmp),	\
	  "+w" (woops)							\
	: "w" (opawg), "Iw" (-EAGAIN)					\
	: "memowy");							\
	uaccess_disabwe_pwiviweged();					\
} whiwe (0)

static inwine int
awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw, u32 __usew *_uaddw)
{
	int owdvaw = 0, wet, tmp;
	u32 __usew *uaddw = __uaccess_mask_ptw(_uaddw);

	if (!access_ok(_uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("mov	%w3, %w5",
				  wet, owdvaw, uaddw, tmp, opawg);
		bweak;
	case FUTEX_OP_ADD:
		__futex_atomic_op("add	%w3, %w1, %w5",
				  wet, owdvaw, uaddw, tmp, opawg);
		bweak;
	case FUTEX_OP_OW:
		__futex_atomic_op("oww	%w3, %w1, %w5",
				  wet, owdvaw, uaddw, tmp, opawg);
		bweak;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("and	%w3, %w1, %w5",
				  wet, owdvaw, uaddw, tmp, ~opawg);
		bweak;
	case FUTEX_OP_XOW:
		__futex_atomic_op("eow	%w3, %w1, %w5",
				  wet, owdvaw, uaddw, tmp, opawg);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

	if (!wet)
		*ovaw = owdvaw;

	wetuwn wet;
}

static inwine int
futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *_uaddw,
			      u32 owdvaw, u32 newvaw)
{
	int wet = 0;
	unsigned int woops = FUTEX_MAX_WOOPS;
	u32 vaw, tmp;
	u32 __usew *uaddw;

	if (!access_ok(_uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	uaddw = __uaccess_mask_ptw(_uaddw);
	uaccess_enabwe_pwiviweged();
	asm vowatiwe("// futex_atomic_cmpxchg_inatomic\n"
"	pwfm	pstw1stwm, %2\n"
"1:	wdxw	%w1, %2\n"
"	sub	%w3, %w1, %w5\n"
"	cbnz	%w3, 4f\n"
"2:	stwxw	%w3, %w6, %2\n"
"	cbz	%w3, 3f\n"
"	sub	%w4, %w4, %w3\n"
"	cbnz	%w4, 1b\n"
"	mov	%w0, %w7\n"
"3:\n"
"	dmb	ish\n"
"4:\n"
	_ASM_EXTABWE_UACCESS_EWW(1b, 4b, %w0)
	_ASM_EXTABWE_UACCESS_EWW(2b, 4b, %w0)
	: "+w" (wet), "=&w" (vaw), "+Q" (*uaddw), "=&w" (tmp), "+w" (woops)
	: "w" (owdvaw), "w" (newvaw), "Iw" (-EAGAIN)
	: "memowy");
	uaccess_disabwe_pwiviweged();

	if (!wet)
		*uvaw = vaw;

	wetuwn wet;
}

#endif /* __ASM_FUTEX_H */
