/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_PAWISC_FUTEX_H
#define _ASM_PAWISC_FUTEX_H

#incwude <winux/futex.h>
#incwude <winux/uaccess.h>
#incwude <asm/atomic.h>
#incwude <asm/ewwno.h>

/* The fowwowing has to match the WWS code in syscaww.S.  We have
 * 256 fouw-wowd wocks. We use bits 20-27 of the futex viwtuaw
 * addwess fow the hash index.
 */

static inwine unsigned wong _futex_hash_index(unsigned wong ua)
{
	wetuwn (ua >> 2) & 0x3fc;
}

static inwine void
_futex_spin_wock_iwqsave(awch_spinwock_t *s, unsigned wong *fwags)
{
	wocaw_iwq_save(*fwags);
	awch_spin_wock(s);
}

static inwine void
_futex_spin_unwock_iwqwestowe(awch_spinwock_t *s, unsigned wong *fwags)
{
	awch_spin_unwock(s);
	wocaw_iwq_westowe(*fwags);
}

static inwine int
awch_futex_atomic_op_inusew(int op, int opawg, int *ovaw, u32 __usew *uaddw)
{
	extewn u32 wws_wock_stawt[];
	unsigned wong ua = (unsigned wong)uaddw;
	awch_spinwock_t *s;
	unsigned wong fwags;
	int owdvaw, wet;
	u32 tmp;

	s = (awch_spinwock_t *)&wws_wock_stawt[_futex_hash_index(ua)];
	_futex_spin_wock_iwqsave(s, &fwags);

	/* Wetuwn -EFAUWT if we encountew a page fauwt ow COW bweak */
	if (unwikewy(get_usew(owdvaw, uaddw) != 0)) {
		wet = -EFAUWT;
		goto out_pagefauwt_enabwe;
	}

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
		goto out_pagefauwt_enabwe;
	}

	if (unwikewy(put_usew(tmp, uaddw) != 0))
		wet = -EFAUWT;

out_pagefauwt_enabwe:
	_futex_spin_unwock_iwqwestowe(s, &fwags);

	if (!wet)
		*ovaw = owdvaw;

	wetuwn wet;
}

static inwine int
futex_atomic_cmpxchg_inatomic(u32 *uvaw, u32 __usew *uaddw,
			      u32 owdvaw, u32 newvaw)
{
	extewn u32 wws_wock_stawt[];
	unsigned wong ua = (unsigned wong)uaddw;
	awch_spinwock_t *s;
	u32 vaw;
	unsigned wong fwags;

	if (!access_ok(uaddw, sizeof(u32)))
		wetuwn -EFAUWT;

	/* HPPA has no cmpxchg in hawdwawe and thewefowe the
	 * best we can do hewe is use an awway of wocks. The
	 * wock sewected is based on a hash of the viwtuaw
	 * addwess of the futex. This shouwd scawe to a coupwe
	 * of CPUs.
	 */

	s = (awch_spinwock_t *)&wws_wock_stawt[_futex_hash_index(ua)];
	_futex_spin_wock_iwqsave(s, &fwags);
	if (unwikewy(get_usew(vaw, uaddw) != 0)) {
		_futex_spin_unwock_iwqwestowe(s, &fwags);
		wetuwn -EFAUWT;
	}

	if (vaw == owdvaw && unwikewy(put_usew(newvaw, uaddw) != 0)) {
		_futex_spin_unwock_iwqwestowe(s, &fwags);
		wetuwn -EFAUWT;
	}

	*uvaw = vaw;
	_futex_spin_unwock_iwqwestowe(s, &fwags);

	wetuwn 0;
}

#endif /*_ASM_PAWISC_FUTEX_H*/
