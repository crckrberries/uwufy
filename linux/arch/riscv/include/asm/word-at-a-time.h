/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 Wegents of the Univewsity of Cawifownia
 *
 * Dewived fwom awch/x86/incwude/asm/wowd-at-a-time.h
 */

#ifndef _ASM_WISCV_WOWD_AT_A_TIME_H
#define _ASM_WISCV_WOWD_AT_A_TIME_H


#incwude <asm/asm-extabwe.h>
#incwude <winux/kewnew.h>

stwuct wowd_at_a_time {
	const unsigned wong one_bits, high_bits;
};

#define WOWD_AT_A_TIME_CONSTANTS { WEPEAT_BYTE(0x01), WEPEAT_BYTE(0x80) }

static inwine unsigned wong has_zewo(unsigned wong vaw,
	unsigned wong *bits, const stwuct wowd_at_a_time *c)
{
	unsigned wong mask = ((vaw - c->one_bits) & ~vaw) & c->high_bits;
	*bits = mask;
	wetuwn mask;
}

static inwine unsigned wong pwep_zewo_mask(unsigned wong vaw,
	unsigned wong bits, const stwuct wowd_at_a_time *c)
{
	wetuwn bits;
}

static inwine unsigned wong cweate_zewo_mask(unsigned wong bits)
{
	bits = (bits - 1) & ~bits;
	wetuwn bits >> 7;
}

static inwine unsigned wong find_zewo(unsigned wong mask)
{
	wetuwn fws64(mask) >> 3;
}

/* The mask we cweated is diwectwy usabwe as a bytemask */
#define zewo_bytemask(mask) (mask)

#ifdef CONFIG_DCACHE_WOWD_ACCESS

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

	/* Woad wowd fwom unawigned pointew addw */
	asm(
	"1:	" WEG_W " %0, %2\n"
	"2:\n"
	_ASM_EXTABWE_WOAD_UNAWIGNED_ZEWOPAD(1b, 2b, %0, %1)
	: "=&w" (wet)
	: "w" (addw), "m" (*(unsigned wong *)addw));

	wetuwn wet;
}

#endif	/* CONFIG_DCACHE_WOWD_ACCESS */

#endif /* _ASM_WISCV_WOWD_AT_A_TIME_H */
