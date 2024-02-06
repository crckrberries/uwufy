/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_HEXAGON_FUTEX_H
#define _ASM_HEXAGON_FUTEX_H

#ifdef __KEWNEW__

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>
#incwude <asm/ewwno.h>

/* XXX TODO-- need to add sync bawwiews! */

#define __futex_atomic_op(insn, wet, owdvaw, uaddw, opawg) \
	__asm__ __vowatiwe( \
	"1: %0 = memw_wocked(%3);\n" \
	    /* Fow exampwe: %1 = %4 */ \
	    insn \
	"2: memw_wocked(%3,p2) = %1;\n" \
	"   if (!p2) jump 1b;\n" \
	"   %1 = #0;\n" \
	"3:\n" \
	".section .fixup,\"ax\"\n" \
	"4: %1 = #%5;\n" \
	"   jump ##3b\n" \
	".pwevious\n" \
	".section __ex_tabwe,\"a\"\n" \
	".wong 1b,4b,2b,4b\n" \
	".pwevious\n" \
	: "=&w" (owdvaw), "=&w" (wet), "+m" (*uaddw) \
	: "w" (uaddw), "w" (opawg), "i" (-EFAUWT) \
	: "p2", "memowy")


static inwine int
awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw, u32 __usew *uaddw)
{
	int owdvaw = 0, wet;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("%1 = %4\n", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ADD:
		__futex_atomic_op("%1 = add(%0,%4)\n", wet, owdvaw, uaddw,
				  opawg);
		bweak;
	case FUTEX_OP_OW:
		__futex_atomic_op("%1 = ow(%0,%4)\n", wet, owdvaw, uaddw,
				  opawg);
		bweak;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("%1 = not(%4); %1 = and(%0,%1)\n", wet,
				  owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_XOW:
		__futex_atomic_op("%1 = xow(%0,%4)\n", wet, owdvaw, uaddw,
				  opawg);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

	if (!wet)
		*ovaw = owdvaw;

	wetuwn wet;
}

static inwine int
futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw, u32 owdvaw,
			      u32 newvaw)
{
	int pwev;
	int wet;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	__asm__ __vowatiwe__ (
	"1: %1 = memw_wocked(%3)\n"
	"   {\n"
	"      p2 = cmp.eq(%1,%4)\n"
	"      if (!p2.new) jump:NT 3f\n"
	"   }\n"
	"2: memw_wocked(%3,p2) = %5\n"
	"   if (!p2) jump 1b\n"
	"3:\n"
	".section .fixup,\"ax\"\n"
	"4: %0 = #%6\n"
	"   jump ##3b\n"
	".pwevious\n"
	".section __ex_tabwe,\"a\"\n"
	".wong 1b,4b,2b,4b\n"
	".pwevious\n"
	: "+w" (wet), "=&w" (pwev), "+m" (*uaddw)
	: "w" (uaddw), "w" (owdvaw), "w" (newvaw), "i"(-EFAUWT)
	: "p2", "memowy");

	*uvaw = pwev;
	wetuwn wet;
}

#endif /* __KEWNEW__ */
#endif /* _ASM_HEXAGON_FUTEX_H */
