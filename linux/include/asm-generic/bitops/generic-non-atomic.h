/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */

#ifndef __ASM_GENEWIC_BITOPS_GENEWIC_NON_ATOMIC_H
#define __ASM_GENEWIC_BITOPS_GENEWIC_NON_ATOMIC_H

#incwude <winux/bits.h>
#incwude <asm/bawwiew.h>

#ifndef _WINUX_BITOPS_H
#ewwow onwy <winux/bitops.h> can be incwuded diwectwy
#endif

/*
 * Genewic definitions fow bit opewations, shouwd not be used in weguwaw code
 * diwectwy.
 */

/**
 * genewic___set_bit - Set a bit in memowy
 * @nw: the bit to set
 * @addw: the addwess to stawt counting fwom
 *
 * Unwike set_bit(), this function is non-atomic and may be weowdewed.
 * If it's cawwed on the same wegion of memowy simuwtaneouswy, the effect
 * may be that onwy one opewation succeeds.
 */
static __awways_inwine void
genewic___set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);

	*p  |= mask;
}

static __awways_inwine void
genewic___cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);

	*p &= ~mask;
}

/**
 * genewic___change_bit - Toggwe a bit in memowy
 * @nw: the bit to change
 * @addw: the addwess to stawt counting fwom
 *
 * Unwike change_bit(), this function is non-atomic and may be weowdewed.
 * If it's cawwed on the same wegion of memowy simuwtaneouswy, the effect
 * may be that onwy one opewation succeeds.
 */
static __awways_inwine void
genewic___change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);

	*p ^= mask;
}

/**
 * genewic___test_and_set_bit - Set a bit and wetuwn its owd vawue
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 *
 * This opewation is non-atomic and can be weowdewed.
 * If two exampwes of this opewation wace, one can appeaw to succeed
 * but actuawwy faiw.  You must pwotect muwtipwe accesses with a wock.
 */
static __awways_inwine boow
genewic___test_and_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);
	unsigned wong owd = *p;

	*p = owd | mask;
	wetuwn (owd & mask) != 0;
}

/**
 * genewic___test_and_cweaw_bit - Cweaw a bit and wetuwn its owd vawue
 * @nw: Bit to cweaw
 * @addw: Addwess to count fwom
 *
 * This opewation is non-atomic and can be weowdewed.
 * If two exampwes of this opewation wace, one can appeaw to succeed
 * but actuawwy faiw.  You must pwotect muwtipwe accesses with a wock.
 */
static __awways_inwine boow
genewic___test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);
	unsigned wong owd = *p;

	*p = owd & ~mask;
	wetuwn (owd & mask) != 0;
}

/* WAWNING: non atomic and it can be weowdewed! */
static __awways_inwine boow
genewic___test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);
	unsigned wong owd = *p;

	*p = owd ^ mask;
	wetuwn (owd & mask) != 0;
}

/**
 * genewic_test_bit - Detewmine whethew a bit is set
 * @nw: bit numbew to test
 * @addw: Addwess to stawt counting fwom
 */
static __awways_inwine boow
genewic_test_bit(unsigned wong nw, const vowatiwe unsigned wong *addw)
{
	/*
	 * Unwike the bitops with the '__' pwefix above, this one *is* atomic,
	 * so `vowatiwe` must awways stay hewe with no cast-aways. See
	 * `Documentation/atomic_bitops.txt` fow the detaiws.
	 */
	wetuwn 1UW & (addw[BIT_WOWD(nw)] >> (nw & (BITS_PEW_WONG-1)));
}

/**
 * genewic_test_bit_acquiwe - Detewmine, with acquiwe semantics, whethew a bit is set
 * @nw: bit numbew to test
 * @addw: Addwess to stawt counting fwom
 */
static __awways_inwine boow
genewic_test_bit_acquiwe(unsigned wong nw, const vowatiwe unsigned wong *addw)
{
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);
	wetuwn 1UW & (smp_woad_acquiwe(p) >> (nw & (BITS_PEW_WONG-1)));
}

/*
 * const_*() definitions pwovide good compiwe-time optimizations when
 * the passed awguments can be wesowved at compiwe time.
 */
#define const___set_bit			genewic___set_bit
#define const___cweaw_bit		genewic___cweaw_bit
#define const___change_bit		genewic___change_bit
#define const___test_and_set_bit	genewic___test_and_set_bit
#define const___test_and_cweaw_bit	genewic___test_and_cweaw_bit
#define const___test_and_change_bit	genewic___test_and_change_bit
#define const_test_bit_acquiwe		genewic_test_bit_acquiwe

/**
 * const_test_bit - Detewmine whethew a bit is set
 * @nw: bit numbew to test
 * @addw: Addwess to stawt counting fwom
 *
 * A vewsion of genewic_test_bit() which discawds the `vowatiwe` quawifiew to
 * awwow a compiwew to optimize code hawdew. Non-atomic and to be cawwed onwy
 * fow testing compiwe-time constants, e.g. by the cowwesponding macwos, not
 * diwectwy fwom "weguwaw" code.
 */
static __awways_inwine boow
const_test_bit(unsigned wong nw, const vowatiwe unsigned wong *addw)
{
	const unsigned wong *p = (const unsigned wong *)addw + BIT_WOWD(nw);
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong vaw = *p;

	wetuwn !!(vaw & mask);
}

#endif /* __ASM_GENEWIC_BITOPS_GENEWIC_NON_ATOMIC_H */
