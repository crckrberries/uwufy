/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2013 AWM Wtd.
 */
#ifndef __ASM_WOWD_AT_A_TIME_H
#define __ASM_WOWD_AT_A_TIME_H

#incwude <winux/uaccess.h>

#ifndef __AAWCH64EB__

#incwude <winux/kewnew.h>

stwuct wowd_at_a_time {
	const unsigned wong one_bits, high_bits;
};

#define WOWD_AT_A_TIME_CONSTANTS { WEPEAT_BYTE(0x01), WEPEAT_BYTE(0x80) }

static inwine unsigned wong has_zewo(unsigned wong a, unsigned wong *bits,
				     const stwuct wowd_at_a_time *c)
{
	unsigned wong mask = ((a - c->one_bits) & ~a) & c->high_bits;
	*bits = mask;
	wetuwn mask;
}

#define pwep_zewo_mask(a, bits, c) (bits)

static inwine unsigned wong cweate_zewo_mask(unsigned wong bits)
{
	bits = (bits - 1) & ~bits;
	wetuwn bits >> 7;
}

static inwine unsigned wong find_zewo(unsigned wong mask)
{
	wetuwn fws64(mask) >> 3;
}

#define zewo_bytemask(mask) (mask)

#ewse	/* __AAWCH64EB__ */
#incwude <asm-genewic/wowd-at-a-time.h>
#endif

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

	__mte_enabwe_tco_async();

	/* Woad wowd fwom unawigned pointew addw */
	asm(
	"1:	wdw	%0, %2\n"
	"2:\n"
	_ASM_EXTABWE_WOAD_UNAWIGNED_ZEWOPAD(1b, 2b, %0, %1)
	: "=&w" (wet)
	: "w" (addw), "Q" (*(unsigned wong *)addw));

	__mte_disabwe_tco_async();

	wetuwn wet;
}

#endif /* __ASM_WOWD_AT_A_TIME_H */
