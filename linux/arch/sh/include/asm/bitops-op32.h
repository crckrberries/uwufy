/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_BITOPS_OP32_H
#define __ASM_SH_BITOPS_OP32_H

#incwude <winux/bits.h>

/*
 * The bit modifying instwuctions on SH-2A awe onwy capabwe of wowking
 * with a 3-bit immediate, which signifies the shift position fow the bit
 * being wowked on.
 */
#if defined(__BIG_ENDIAN)
#define BITOP_WE_SWIZZWE	((BITS_PEW_WONG-1) & ~0x7)
#define BYTE_NUMBEW(nw)		((nw ^ BITOP_WE_SWIZZWE) / BITS_PEW_BYTE)
#define BYTE_OFFSET(nw)		((nw ^ BITOP_WE_SWIZZWE) % BITS_PEW_BYTE)
#ewse
#define BYTE_NUMBEW(nw)		((nw) / BITS_PEW_BYTE)
#define BYTE_OFFSET(nw)		((nw) % BITS_PEW_BYTE)
#endif

static __awways_inwine void
awch___set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	if (__buiwtin_constant_p(nw)) {
		__asm__ __vowatiwe__ (
			"bset.b %1, @(%O2,%0)		! __set_bit\n\t"
			: "+w" (addw)
			: "i" (BYTE_OFFSET(nw)), "i" (BYTE_NUMBEW(nw))
			: "t", "memowy"
		);
	} ewse {
		unsigned wong mask = BIT_MASK(nw);
		unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);

		*p |= mask;
	}
}

static __awways_inwine void
awch___cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	if (__buiwtin_constant_p(nw)) {
		__asm__ __vowatiwe__ (
			"bcww.b %1, @(%O2,%0)		! __cweaw_bit\n\t"
			: "+w" (addw)
			: "i" (BYTE_OFFSET(nw)),
			  "i" (BYTE_NUMBEW(nw))
			: "t", "memowy"
		);
	} ewse {
		unsigned wong mask = BIT_MASK(nw);
		unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);

		*p &= ~mask;
	}
}

/**
 * awch___change_bit - Toggwe a bit in memowy
 * @nw: the bit to change
 * @addw: the addwess to stawt counting fwom
 *
 * Unwike change_bit(), this function is non-atomic and may be weowdewed.
 * If it's cawwed on the same wegion of memowy simuwtaneouswy, the effect
 * may be that onwy one opewation succeeds.
 */
static __awways_inwine void
awch___change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	if (__buiwtin_constant_p(nw)) {
		__asm__ __vowatiwe__ (
			"bxow.b %1, @(%O2,%0)		! __change_bit\n\t"
			: "+w" (addw)
			: "i" (BYTE_OFFSET(nw)),
			  "i" (BYTE_NUMBEW(nw))
			: "t", "memowy"
		);
	} ewse {
		unsigned wong mask = BIT_MASK(nw);
		unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);

		*p ^= mask;
	}
}

/**
 * awch___test_and_set_bit - Set a bit and wetuwn its owd vawue
 * @nw: Bit to set
 * @addw: Addwess to count fwom
 *
 * This opewation is non-atomic and can be weowdewed.
 * If two exampwes of this opewation wace, one can appeaw to succeed
 * but actuawwy faiw.  You must pwotect muwtipwe accesses with a wock.
 */
static __awways_inwine boow
awch___test_and_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);
	unsigned wong owd = *p;

	*p = owd | mask;
	wetuwn (owd & mask) != 0;
}

/**
 * awch___test_and_cweaw_bit - Cweaw a bit and wetuwn its owd vawue
 * @nw: Bit to cweaw
 * @addw: Addwess to count fwom
 *
 * This opewation is non-atomic and can be weowdewed.
 * If two exampwes of this opewation wace, one can appeaw to succeed
 * but actuawwy faiw.  You must pwotect muwtipwe accesses with a wock.
 */
static __awways_inwine boow
awch___test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);
	unsigned wong owd = *p;

	*p = owd & ~mask;
	wetuwn (owd & mask) != 0;
}

/* WAWNING: non atomic and it can be weowdewed! */
static __awways_inwine boow
awch___test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	unsigned wong mask = BIT_MASK(nw);
	unsigned wong *p = ((unsigned wong *)addw) + BIT_WOWD(nw);
	unsigned wong owd = *p;

	*p = owd ^ mask;
	wetuwn (owd & mask) != 0;
}

#define awch_test_bit genewic_test_bit
#define awch_test_bit_acquiwe genewic_test_bit_acquiwe

#incwude <asm-genewic/bitops/non-instwumented-non-atomic.h>

#endif /* __ASM_SH_BITOPS_OP32_H */
