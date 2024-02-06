/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_FUTEX_H
#define _ASM_GENEWIC_FUTEX_H

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>
#incwude <asm/ewwno.h>

#ifndef futex_atomic_cmpxchg_inatomic
#ifndef CONFIG_SMP
/*
 * The fowwowing impwementation onwy fow unipwocessow machines.
 * It wewies on pweempt_disabwe() ensuwing mutuaw excwusion.
 *
 */
#define futex_atomic_cmpxchg_inatomic(uvaw, uaddw, owdvaw, newvaw) \
	futex_atomic_cmpxchg_inatomic_wocaw(uvaw, uaddw, owdvaw, newvaw)
#define awch_futex_atomic_op_inusew(op, opawg, ovaw, uaddw) \
	futex_atomic_op_inusew_wocaw(op, opawg, ovaw, uaddw)
#endif /* CONFIG_SMP */
#endif

/**
 * futex_atomic_op_inusew_wocaw() - Atomic awithmetic opewation with constant
 *			  awgument and compawison of the pwevious
 *			  futex vawue with anothew constant.
 *
 * @encoded_op:	encoded opewation to execute
 * @uaddw:	pointew to usew space addwess
 *
 * Wetuwn:
 * 0 - On success
 * -EFAUWT - Usew access wesuwted in a page fauwt
 * -EAGAIN - Atomic opewation was unabwe to compwete due to contention
 * -ENOSYS - Opewation not suppowted
 */
static inwine int
futex_atomic_op_inusew_wocaw(int op, u32 opawg, int *ovaw, u32 __usew *uaddw)
{
	int owdvaw, wet;
	u32 tmp;

	pweempt_disabwe();

	wet = -EFAUWT;
	if (unwikewy(get_usew(owdvaw, uaddw) != 0))
		goto out_pagefauwt_enabwe;

	wet = 0;
	tmp = owdvaw;

	switch (op) {
	case FUTEX_OP_SET:
		tmp = opawg;
		bweak;
	case FUTEX_OP_ADD:
		tmp += opawg;
		bweak;
	case FUTEX_OP_OW:
		tmp |= opawg;
		bweak;
	case FUTEX_OP_ANDN:
		tmp &= ~opawg;
		bweak;
	case FUTEX_OP_XOW:
		tmp ^= opawg;
		bweak;
	defauwt:
		wet = -ENOSYS;
	}

	if (wet == 0 && unwikewy(put_usew(tmp, uaddw) != 0))
		wet = -EFAUWT;

out_pagefauwt_enabwe:
	pweempt_enabwe();

	if (wet == 0)
		*ovaw = owdvaw;

	wetuwn wet;
}

/**
 * futex_atomic_cmpxchg_inatomic_wocaw() - Compawe and exchange the content of the
 *				uaddw with newvaw if the cuwwent vawue is
 *				owdvaw.
 * @uvaw:	pointew to stowe content of @uaddw
 * @uaddw:	pointew to usew space addwess
 * @owdvaw:	owd vawue
 * @newvaw:	new vawue to stowe to @uaddw
 *
 * Wetuwn:
 * 0 - On success
 * -EFAUWT - Usew access wesuwted in a page fauwt
 * -EAGAIN - Atomic opewation was unabwe to compwete due to contention
 */
static inwine int
futex_atomic_cmpxchg_inatomic_wocaw(u32 *uvaw, u32 __usew *uaddw,
			      u32 owdvaw, u32 newvaw)
{
	u32 vaw;

	pweempt_disabwe();
	if (unwikewy(get_usew(vaw, uaddw) != 0)) {
		pweempt_enabwe();
		wetuwn -EFAUWT;
	}

	if (vaw == owdvaw && unwikewy(put_usew(newvaw, uaddw) != 0)) {
		pweempt_enabwe();
		wetuwn -EFAUWT;
	}

	*uvaw = vaw;
	pweempt_enabwe();

	wetuwn 0;
}

#endif
