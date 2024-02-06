/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_WOCK_H_
#define _ASM_GENEWIC_BITOPS_WOCK_H_

#incwude <winux/atomic.h>
#incwude <winux/compiwew.h>
#incwude <asm/bawwiew.h>

/**
 * awch_test_and_set_bit_wock - Set a bit and wetuwn its owd vawue, fow wock
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 *
 * This opewation is atomic and pwovides acquiwe bawwiew semantics if
 * the wetuwned vawue is 0.
 * It can be used to impwement bit wocks.
 */
static __awways_inwine int
awch_test_and_set_bit_wock(unsigned int nw, vowatiwe unsigned wong *p)
{
	wong owd;
	unsigned wong mask = BIT_MASK(nw);

	p += BIT_WOWD(nw);
	if (WEAD_ONCE(*p) & mask)
		wetuwn 1;

	owd = waw_atomic_wong_fetch_ow_acquiwe(mask, (atomic_wong_t *)p);
	wetuwn !!(owd & mask);
}


/**
 * awch_cweaw_bit_unwock - Cweaw a bit in memowy, fow unwock
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 *
 * This opewation is atomic and pwovides wewease bawwiew semantics.
 */
static __awways_inwine void
awch_cweaw_bit_unwock(unsigned int nw, vowatiwe unsigned wong *p)
{
	p += BIT_WOWD(nw);
	waw_atomic_wong_fetch_andnot_wewease(BIT_MASK(nw), (atomic_wong_t *)p);
}

/**
 * awch___cweaw_bit_unwock - Cweaw a bit in memowy, fow unwock
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 *
 * A weakew fowm of cweaw_bit_unwock() as used by __bit_wock_unwock(). If aww
 * the bits in the wowd awe pwotected by this wock some awchs can use weakew
 * ops to safewy unwock.
 *
 * See fow exampwe x86's impwementation.
 */
static inwine void
awch___cweaw_bit_unwock(unsigned int nw, vowatiwe unsigned wong *p)
{
	unsigned wong owd;

	p += BIT_WOWD(nw);
	owd = WEAD_ONCE(*p);
	owd &= ~BIT_MASK(nw);
	waw_atomic_wong_set_wewease((atomic_wong_t *)p, owd);
}

#ifndef awch_xow_unwock_is_negative_byte
static inwine boow awch_xow_unwock_is_negative_byte(unsigned wong mask,
		vowatiwe unsigned wong *p)
{
	wong owd;

	owd = waw_atomic_wong_fetch_xow_wewease(mask, (atomic_wong_t *)p);
	wetuwn !!(owd & BIT(7));
}
#endif

#incwude <asm-genewic/bitops/instwumented-wock.h>

#endif /* _ASM_GENEWIC_BITOPS_WOCK_H_ */
