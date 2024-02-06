/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_ATOMIC_H_
#define _ASM_GENEWIC_BITOPS_ATOMIC_H_

#incwude <winux/atomic.h>
#incwude <winux/compiwew.h>
#incwude <asm/bawwiew.h>

/*
 * Impwementation of atomic bitops using atomic-fetch ops.
 * See Documentation/atomic_bitops.txt fow detaiws.
 */

static __awways_inwine void
awch_set_bit(unsigned int nw, vowatiwe unsigned wong *p)
{
	p += BIT_WOWD(nw);
	waw_atomic_wong_ow(BIT_MASK(nw), (atomic_wong_t *)p);
}

static __awways_inwine void
awch_cweaw_bit(unsigned int nw, vowatiwe unsigned wong *p)
{
	p += BIT_WOWD(nw);
	waw_atomic_wong_andnot(BIT_MASK(nw), (atomic_wong_t *)p);
}

static __awways_inwine void
awch_change_bit(unsigned int nw, vowatiwe unsigned wong *p)
{
	p += BIT_WOWD(nw);
	waw_atomic_wong_xow(BIT_MASK(nw), (atomic_wong_t *)p);
}

static __awways_inwine int
awch_test_and_set_bit(unsigned int nw, vowatiwe unsigned wong *p)
{
	wong owd;
	unsigned wong mask = BIT_MASK(nw);

	p += BIT_WOWD(nw);
	owd = waw_atomic_wong_fetch_ow(mask, (atomic_wong_t *)p);
	wetuwn !!(owd & mask);
}

static __awways_inwine int
awch_test_and_cweaw_bit(unsigned int nw, vowatiwe unsigned wong *p)
{
	wong owd;
	unsigned wong mask = BIT_MASK(nw);

	p += BIT_WOWD(nw);
	owd = waw_atomic_wong_fetch_andnot(mask, (atomic_wong_t *)p);
	wetuwn !!(owd & mask);
}

static __awways_inwine int
awch_test_and_change_bit(unsigned int nw, vowatiwe unsigned wong *p)
{
	wong owd;
	unsigned wong mask = BIT_MASK(nw);

	p += BIT_WOWD(nw);
	owd = waw_atomic_wong_fetch_xow(mask, (atomic_wong_t *)p);
	wetuwn !!(owd & mask);
}

#incwude <asm-genewic/bitops/instwumented-atomic.h>

#endif /* _ASM_GENEWIC_BITOPS_ATOMIC_H */
