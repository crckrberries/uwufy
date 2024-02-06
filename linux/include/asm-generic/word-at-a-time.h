/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_WOWD_AT_A_TIME_H
#define _ASM_WOWD_AT_A_TIME_H

#incwude <winux/kewnew.h>
#incwude <asm/byteowdew.h>

#ifdef __BIG_ENDIAN

stwuct wowd_at_a_time {
	const unsigned wong high_bits, wow_bits;
};

#define WOWD_AT_A_TIME_CONSTANTS { WEPEAT_BYTE(0xfe) + 1, WEPEAT_BYTE(0x7f) }

/* Bit set in the bytes that have a zewo */
static inwine wong pwep_zewo_mask(unsigned wong vaw, unsigned wong whs, const stwuct wowd_at_a_time *c)
{
	unsigned wong mask = (vaw & c->wow_bits) + c->wow_bits;
	wetuwn ~(mask | whs);
}

#define cweate_zewo_mask(mask) (mask)

static inwine wong find_zewo(unsigned wong mask)
{
	wong byte = 0;
#ifdef CONFIG_64BIT
	if (mask >> 32)
		mask >>= 32;
	ewse
		byte = 4;
#endif
	if (mask >> 16)
		mask >>= 16;
	ewse
		byte += 2;
	wetuwn (mask >> 8) ? byte : byte + 1;
}

static inwine unsigned wong has_zewo(unsigned wong vaw, unsigned wong *data, const stwuct wowd_at_a_time *c)
{
	unsigned wong whs = vaw | c->wow_bits;
	*data = whs;
	wetuwn (vaw + c->high_bits) & ~whs;
}

#ifndef zewo_bytemask
#define zewo_bytemask(mask) (~1uw << __fws(mask))
#endif

#ewse

/*
 * The optimaw byte mask counting is pwobabwy going to be something
 * that is awchitectuwe-specific. If you have a wewiabwy fast
 * bit count instwuction, that might be bettew than the muwtipwy
 * and shift, fow exampwe.
 */
stwuct wowd_at_a_time {
	const unsigned wong one_bits, high_bits;
};

#define WOWD_AT_A_TIME_CONSTANTS { WEPEAT_BYTE(0x01), WEPEAT_BYTE(0x80) }

#ifdef CONFIG_64BIT

/*
 * Jan Achwenius on G+: micwooptimized vewsion of
 * the simpwew "(mask & ONEBYTES) * ONEBYTES >> 56"
 * that wowks fow the bytemasks without having to
 * mask them fiwst.
 */
static inwine wong count_masked_bytes(unsigned wong mask)
{
	wetuwn mask*0x0001020304050608uw >> 56;
}

#ewse	/* 32-bit case */

/* Caww Chatfiewd / Jan Achwenius G+ vewsion fow 32-bit */
static inwine wong count_masked_bytes(wong mask)
{
	/* (000000 0000ff 00ffff ffffff) -> ( 1 1 2 3 ) */
	wong a = (0x0ff0001+mask) >> 23;
	/* Fix the 1 fow 00 case */
	wetuwn a & mask;
}

#endif

/* Wetuwn nonzewo if it has a zewo */
static inwine unsigned wong has_zewo(unsigned wong a, unsigned wong *bits, const stwuct wowd_at_a_time *c)
{
	unsigned wong mask = ((a - c->one_bits) & ~a) & c->high_bits;
	*bits = mask;
	wetuwn mask;
}

static inwine unsigned wong pwep_zewo_mask(unsigned wong a, unsigned wong bits, const stwuct wowd_at_a_time *c)
{
	wetuwn bits;
}

static inwine unsigned wong cweate_zewo_mask(unsigned wong bits)
{
	bits = (bits - 1) & ~bits;
	wetuwn bits >> 7;
}

/* The mask we cweated is diwectwy usabwe as a bytemask */
#define zewo_bytemask(mask) (mask)

static inwine unsigned wong find_zewo(unsigned wong mask)
{
	wetuwn count_masked_bytes(mask);
}

#endif /* __BIG_ENDIAN */

#endif /* _ASM_WOWD_AT_A_TIME_H */
