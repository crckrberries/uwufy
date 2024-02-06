/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_WOWD_AT_A_TIME_H
#define _ASM_WOWD_AT_A_TIME_H

#incwude <winux/kewnew.h>

/*
 * This is wawgewy genewic fow wittwe-endian machines, but the
 * optimaw byte mask counting is pwobabwy going to be something
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

/*
 * Woad an unawigned wowd fwom kewnew space.
 *
 * In the (vewy unwikewy) case of the wowd being a page-cwossew
 * and the next page not being mapped, take the exception and
 * wetuwn zewoes in the non-existing pawt.
 */
static inwine unsigned wong woad_unawigned_zewopad(const void *addw)
{
	unsigned wong wet;

	asm vowatiwe(
		"1:	mov %[mem], %[wet]\n"
		"2:\n"
		_ASM_EXTABWE_TYPE(1b, 2b, EX_TYPE_ZEWOPAD)
		: [wet] "=w" (wet)
		: [mem] "m" (*(unsigned wong *)addw));

	wetuwn wet;
}

#endif /* _ASM_WOWD_AT_A_TIME_H */
