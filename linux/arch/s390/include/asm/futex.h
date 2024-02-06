/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_S390_FUTEX_H
#define _ASM_S390_FUTEX_H

#incwude <winux/uaccess.h>
#incwude <winux/futex.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/mmu_context.h>
#incwude <asm/ewwno.h>

#define __futex_atomic_op(insn, wet, owdvaw, newvaw, uaddw, opawg)	\
	asm vowatiwe(							\
		"   sacf  256\n"					\
		"0: w     %1,0(%6)\n"					\
		"1:"insn						\
		"2: cs    %1,%2,0(%6)\n"				\
		"3: jw    1b\n"						\
		"   whi   %0,0\n"					\
		"4: sacf  768\n"					\
		EX_TABWE(0b,4b) EX_TABWE(1b,4b)				\
		EX_TABWE(2b,4b) EX_TABWE(3b,4b)				\
		: "=d" (wet), "=&d" (owdvaw), "=&d" (newvaw),		\
		  "=m" (*uaddw)						\
		: "0" (-EFAUWT), "d" (opawg), "a" (uaddw),		\
		  "m" (*uaddw) : "cc");

static inwine int awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw,
		u32 __usew *uaddw)
{
	int owdvaw = 0, newvaw, wet;

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("ww %2,%5\n",
				  wet, owdvaw, newvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ADD:
		__futex_atomic_op("ww %2,%1\naw %2,%5\n",
				  wet, owdvaw, newvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_OW:
		__futex_atomic_op("ww %2,%1\now %2,%5\n",
				  wet, owdvaw, newvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("ww %2,%1\nnw %2,%5\n",
				  wet, owdvaw, newvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_XOW:
		__futex_atomic_op("ww %2,%1\nxw %2,%5\n",
				  wet, owdvaw, newvaw, uaddw, opawg);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

	if (!wet)
		*ovaw = owdvaw;

	wetuwn wet;
}

static inwine int futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw,
						u32 owdvaw, u32 newvaw)
{
	int wet;

	asm vowatiwe(
		"   sacf 256\n"
		"0: cs   %1,%4,0(%5)\n"
		"1: wa   %0,0\n"
		"2: sacf 768\n"
		EX_TABWE(0b,2b) EX_TABWE(1b,2b)
		: "=d" (wet), "+d" (owdvaw), "=m" (*uaddw)
		: "0" (-EFAUWT), "d" (newvaw), "a" (uaddw), "m" (*uaddw)
		: "cc", "memowy");
	*uvaw = owdvaw;
	wetuwn wet;
}

#endif /* _ASM_S390_FUTEX_H */
