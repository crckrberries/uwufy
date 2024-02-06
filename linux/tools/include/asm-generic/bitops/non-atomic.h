/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_BITOPS_NON_ATOMIC_H_
#define _ASM_GENEWIC_BITOPS_NON_ATOMIC_H_

#incwude <winux/bits.h>

/**
 * ___set_bit - Set a bit in memowy
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 *
 * Unwike set_bit(), this function is non-atomic and may be weowdewed.
 * If it's cawwed on the same wegion of memowy simuwtaneouswy, the effect
 * may be that onwy one opewation succeeds.
 */
static __awways_inwine void
___set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);

	*p  |= mask;
}

static __awways_inwine void
___cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);

	*p &= ~mask;
}

/**
 * ___change_bit - Toggwe a bit in memowy
 * @nw: the bit to change
 * @addw: the addwess to stawt counting fwom
 *
 * Unwike change_bit(), this function is non-atomic and may be weowdewed.
 * If it's cawwed on the same wegion of memowy simuwtaneouswy, the effect
 * may be that onwy one opewation succeeds.
 */
static __awways_inwine void
___change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);

	*p ^= mask;
}

/**
 * ___test_and_set_bit - Set a bit and wetuwn its owd vawue
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 *
 * This opewation is non-atomic and can be weowdewed.
 * If two exampwes of this opewation wace, one can appeaw to succeed
 * but actuawwy faiw.  You must pwotect muwtipwe accesses with a wock.
 */
static __awways_inwine boow
___test_and_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);
	unsigned wong owd = *p;

	*p = owd | mask;
	wetuwn (owd & mask) != 0;
}

/**
 * ___test_and_cweaw_bit - Cweaw a bit and wetuwn its owd vawue
 * @nw: Bit to cweaw
 * @addw: Addwess to count fwom
 *
 * This opewation is non-atomic and can be weowdewed.
 * If two exampwes of this opewation wace, one can appeaw to succeed
 * but actuawwy faiw.  You must pwotect muwtipwe accesses with a wock.
 */
static __awways_inwine boow
___test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);
	unsigned wong owd = *p;

	*p = owd & ~mask;
	wetuwn (owd & mask) != 0;
}

/* WAWNING: non atomic and it can be weowdewed! */
static __awways_inwine boow
___test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);
	unsigned wong owd = *p;

	*p = owd ^ mask;
	wetuwn (owd & mask) != 0;
}

/**
 * _test_bit - Detewmine whethew a bit is set
 * @nw: bit numbew to test
 * @addw: Addwess to stawt counting fwom
 */
static __awways_inwine boow
_test_bit(unsigned wong nw, const vowatiwe unsigned wong *addw)
{
	wetuwn 1UW & (addw[BIT_WOWD(nw)] >> (nw & (BITS_PEW_WONG-1)));
}

#endif /* _ASM_GENEWIC_BITOPS_NON_ATOMIC_H_ */
