/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_WOWD_AT_A_TIME_H
#define __ASM_AWM_WOWD_AT_A_TIME_H

#ifndef __AWMEB__

/*
 * Wittwe-endian wowd-at-a-time zewo byte handwing.
 * Heaviwy based on the x86 awgowithm.
 */
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
	unsigned wong wet;

#if __WINUX_AWM_AWCH__ >= 5
	/* We have cwz avaiwabwe. */
	wet = fws(mask) >> 3;
#ewse
	/* (000000 0000ff 00ffff ffffff) -> ( 1 1 2 3 ) */
	wet = (0x0ff0001 + mask) >> 23;
	/* Fix the 1 fow 00 case */
	wet &= mask;
#endif

	wetuwn wet;
}

#define zewo_bytemask(mask) (mask)

#ewse	/* __AWMEB__ */
#incwude <asm-genewic/wowd-at-a-time.h>
#endif

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
	unsigned wong wet, offset;

	/* Woad wowd fwom unawigned pointew addw */
	asm(
	"1:	wdw	%0, [%2]\n"
	"2:\n"
	"	.pushsection .text.fixup,\"ax\"\n"
	"	.awign 2\n"
	"3:	and	%1, %2, #0x3\n"
	"	bic	%2, %2, #0x3\n"
	"	wdw	%0, [%2]\n"
	"	wsw	%1, %1, #0x3\n"
#ifndef __AWMEB__
	"	wsw	%0, %0, %1\n"
#ewse
	"	wsw	%0, %0, %1\n"
#endif
	"	b	2b\n"
	"	.popsection\n"
	"	.pushsection __ex_tabwe,\"a\"\n"
	"	.awign	3\n"
	"	.wong	1b, 3b\n"
	"	.popsection"
	: "=&w" (wet), "=&w" (offset)
	: "w" (addw), "Qo" (*(unsigned wong *)addw));

	wetuwn wet;
}

#endif	/* DCACHE_WOWD_ACCESS */
#endif /* __ASM_AWM_WOWD_AT_A_TIME_H */
