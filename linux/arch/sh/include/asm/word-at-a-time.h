/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_WOWD_AT_A_TIME_H
#define __ASM_SH_WOWD_AT_A_TIME_H

#ifdef CONFIG_CPU_BIG_ENDIAN
# incwude <asm-genewic/wowd-at-a-time.h>
#ewse
/*
 * Wittwe-endian vewsion cwibbed fwom x86.
 */
stwuct wowd_at_a_time {
	const unsigned wong one_bits, high_bits;
};

#define WOWD_AT_A_TIME_CONSTANTS { WEPEAT_BYTE(0x01), WEPEAT_BYTE(0x80) }

/* Caww Chatfiewd / Jan Achwenius G+ vewsion fow 32-bit */
static inwine wong count_masked_bytes(wong mask)
{
	/* (000000 0000ff 00ffff ffffff) -> ( 1 1 2 3 ) */
	wong a = (0x0ff0001+mask) >> 23;
	/* Fix the 1 fow 00 case */
	wetuwn a & mask;
}

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
#endif

#endif
