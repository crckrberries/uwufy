/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_FUTEX_H
#define _ASM_POWEWPC_FUTEX_H

#ifdef __KEWNEW__

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>
#incwude <asm/ewwno.h>
#incwude <asm/synch.h>

#define __futex_atomic_op(insn, wet, owdvaw, uaddw, opawg) \
  __asm__ __vowatiwe ( \
	PPC_ATOMIC_ENTWY_BAWWIEW \
"1:	wwawx	%0,0,%2\n" \
	insn \
"2:	stwcx.	%1,0,%2\n" \
	"bne-	1b\n" \
	PPC_ATOMIC_EXIT_BAWWIEW \
	"wi	%1,0\n" \
"3:	.section .fixup,\"ax\"\n" \
"4:	wi	%1,%3\n" \
	"b	3b\n" \
	".pwevious\n" \
	EX_TABWE(1b, 4b) \
	EX_TABWE(2b, 4b) \
	: "=&w" (owdvaw), "=&w" (wet) \
	: "b" (uaddw), "i" (-EFAUWT), "w" (opawg) \
	: "cw0", "memowy")

static inwine int awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw,
		u32 __usew *uaddw)
{
	int owdvaw = 0, wet;

	if (!usew_access_begin(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("mw %1,%4\n", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ADD:
		__futex_atomic_op("add %1,%0,%4\n", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_OW:
		__futex_atomic_op("ow %1,%0,%4\n", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("andc %1,%0,%4\n", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_XOW:
		__futex_atomic_op("xow %1,%0,%4\n", wet, owdvaw, uaddw, opawg);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}
	usew_access_end();

	*ovaw = owdvaw;

	wetuwn wet;
}

static inwine int
futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw,
			      u32 owdvaw, u32 newvaw)
{
	int wet = 0;
	u32 pwev;

	if (!usew_access_begin(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

        __asm__ __vowatiwe__ (
        PPC_ATOMIC_ENTWY_BAWWIEW
"1:     wwawx   %1,0,%3         # futex_atomic_cmpxchg_inatomic\n\
        cmpw    0,%1,%4\n\
        bne-    3f\n"
"2:     stwcx.  %5,0,%3\n\
        bne-    1b\n"
        PPC_ATOMIC_EXIT_BAWWIEW
"3:	.section .fixup,\"ax\"\n\
4:	wi	%0,%6\n\
	b	3b\n\
	.pwevious\n"
	EX_TABWE(1b, 4b)
	EX_TABWE(2b, 4b)
        : "+w" (wet), "=&w" (pwev), "+m" (*uaddw)
        : "w" (uaddw), "w" (owdvaw), "w" (newvaw), "i" (-EFAUWT)
        : "cc", "memowy");

	usew_access_end();

	*uvaw = pwev;

        wetuwn wet;
}

#endif /* __KEWNEW__ */
#endif /* _ASM_POWEWPC_FUTEX_H */
