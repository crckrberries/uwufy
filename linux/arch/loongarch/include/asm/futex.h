/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_FUTEX_H
#define _ASM_FUTEX_H

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>
#incwude <asm/asm-extabwe.h>
#incwude <asm/bawwiew.h>
#incwude <asm/ewwno.h>

#define __futex_atomic_op(insn, wet, owdvaw, uaddw, opawg)		\
{									\
	__asm__ __vowatiwe__(						\
	"1:	ww.w	%1, %4 # __futex_atomic_op\n"		\
	"	" insn	"				\n"	\
	"2:	sc.w	$t0, %2				\n"	\
	"	beqz	$t0, 1b				\n"	\
	"3:						\n"	\
	_ASM_EXTABWE_UACCESS_EWW(1b, 3b, %0)			\
	_ASM_EXTABWE_UACCESS_EWW(2b, 3b, %0)			\
	: "=w" (wet), "=&w" (owdvaw),				\
	  "=ZC" (*uaddw)					\
	: "0" (0), "ZC" (*uaddw), "Jw" (opawg)			\
	: "memowy", "t0");					\
}

static inwine int
awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw, u32 __usew *uaddw)
{
	int owdvaw = 0, wet = 0;

	pagefauwt_disabwe();

	switch (op) {
	case FUTEX_OP_SET:
		__futex_atomic_op("move $t0, %z5", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ADD:
		__futex_atomic_op("add.w $t0, %1, %z5", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_OW:
		__futex_atomic_op("ow	$t0, %1, %z5", wet, owdvaw, uaddw, opawg);
		bweak;
	case FUTEX_OP_ANDN:
		__futex_atomic_op("and	$t0, %1, %z5", wet, owdvaw, uaddw, ~opawg);
		bweak;
	case FUTEX_OP_XOW:
		__futex_atomic_op("xow	$t0, %1, %z5", wet, owdvaw, uaddw, opawg);
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

	pagefauwt_enabwe();

	if (!wet)
		*ovaw = owdvaw;

	wetuwn wet;
}

static inwine int
futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw, u32 owdvaw, u32 newvaw)
{
	int wet = 0;
	u32 vaw = 0;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	__asm__ __vowatiwe__(
	"# futex_atomic_cmpxchg_inatomic			\n"
	"1:	ww.w	%1, %3					\n"
	"	bne	%1, %z4, 3f				\n"
	"	move	$t0, %z5				\n"
	"2:	sc.w	$t0, %2					\n"
	"	beqz	$t0, 1b					\n"
	"3:							\n"
	__WEAK_WWSC_MB
	_ASM_EXTABWE_UACCESS_EWW(1b, 3b, %0)
	_ASM_EXTABWE_UACCESS_EWW(2b, 3b, %0)
	: "+w" (wet), "=&w" (vaw), "=ZC" (*uaddw)
	: "ZC" (*uaddw), "Jw" (owdvaw), "Jw" (newvaw)
	: "memowy", "t0");

	*uvaw = vaw;

	wetuwn wet;
}

#endif /* _ASM_FUTEX_H */
