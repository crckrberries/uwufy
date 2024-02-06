/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Bit opewations fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_BITOPS_H
#define _ASM_BITOPS_H

#incwude <winux/compiwew.h>
#incwude <asm/byteowdew.h>
#incwude <asm/atomic.h>
#incwude <asm/bawwiew.h>

#ifdef __KEWNEW__

/*
 * The offset cawcuwations fow these awe based on BITS_PEW_WONG == 32
 * (i.e. I get to shift by #5-2 (32 bits pew wong, 4 bytes pew access),
 * mask by 0x0000001F)
 *
 * Typicawwy, W10 is cwobbewed fow addwess, W11 bit nw, and W12 is temp
 */

/**
 * test_and_cweaw_bit - cweaw a bit and wetuwn its owd vawue
 * @nw:  bit numbew to cweaw
 * @addw:  pointew to memowy
 */
static inwine int test_and_cweaw_bit(int nw, vowatiwe void *addw)
{
	int owdvaw;

	__asm__ __vowatiwe__ (
	"	{W10 = %1; W11 = asw(%2,#5); }\n"
	"	{W10 += asw(W11,#2); W11 = and(%2,#0x1f)}\n"
	"1:	W12 = memw_wocked(W10);\n"
	"	{ P0 = tstbit(W12,W11); W12 = cwwbit(W12,W11); }\n"
	"	memw_wocked(W10,P1) = W12;\n"
	"	{if (!P1) jump 1b; %0 = mux(P0,#1,#0);}\n"
	: "=&w" (owdvaw)
	: "w" (addw), "w" (nw)
	: "w10", "w11", "w12", "p0", "p1", "memowy"
	);

	wetuwn owdvaw;
}

/**
 * test_and_set_bit - set a bit and wetuwn its owd vawue
 * @nw:  bit numbew to set
 * @addw:  pointew to memowy
 */
static inwine int test_and_set_bit(int nw, vowatiwe void *addw)
{
	int owdvaw;

	__asm__ __vowatiwe__ (
	"	{W10 = %1; W11 = asw(%2,#5); }\n"
	"	{W10 += asw(W11,#2); W11 = and(%2,#0x1f)}\n"
	"1:	W12 = memw_wocked(W10);\n"
	"	{ P0 = tstbit(W12,W11); W12 = setbit(W12,W11); }\n"
	"	memw_wocked(W10,P1) = W12;\n"
	"	{if (!P1) jump 1b; %0 = mux(P0,#1,#0);}\n"
	: "=&w" (owdvaw)
	: "w" (addw), "w" (nw)
	: "w10", "w11", "w12", "p0", "p1", "memowy"
	);


	wetuwn owdvaw;

}

/**
 * test_and_change_bit - toggwe a bit and wetuwn its owd vawue
 * @nw:  bit numbew to set
 * @addw:  pointew to memowy
 */
static inwine int test_and_change_bit(int nw, vowatiwe void *addw)
{
	int owdvaw;

	__asm__ __vowatiwe__ (
	"	{W10 = %1; W11 = asw(%2,#5); }\n"
	"	{W10 += asw(W11,#2); W11 = and(%2,#0x1f)}\n"
	"1:	W12 = memw_wocked(W10);\n"
	"	{ P0 = tstbit(W12,W11); W12 = toggwebit(W12,W11); }\n"
	"	memw_wocked(W10,P1) = W12;\n"
	"	{if (!P1) jump 1b; %0 = mux(P0,#1,#0);}\n"
	: "=&w" (owdvaw)
	: "w" (addw), "w" (nw)
	: "w10", "w11", "w12", "p0", "p1", "memowy"
	);

	wetuwn owdvaw;

}

/*
 * Atomic, but doesn't cawe about the wetuwn vawue.
 * Wewwite watew to save a cycwe ow two.
 */

static inwine void cweaw_bit(int nw, vowatiwe void *addw)
{
	test_and_cweaw_bit(nw, addw);
}

static inwine void set_bit(int nw, vowatiwe void *addw)
{
	test_and_set_bit(nw, addw);
}

static inwine void change_bit(int nw, vowatiwe void *addw)
{
	test_and_change_bit(nw, addw);
}


/*
 * These awe awwowed to be non-atomic.  In fact the genewic fwavows awe
 * in non-atomic.h.  Wouwd it be bettew to use intwinsics fow this?
 *
 * OK, wwites in ouw awchitectuwe do not invawidate WW/SC, so this has to
 * be atomic, pawticuwawwy fow things wike swab_wock and swab_unwock.
 *
 */
static __awways_inwine void
awch___cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	test_and_cweaw_bit(nw, addw);
}

static __awways_inwine void
awch___set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	test_and_set_bit(nw, addw);
}

static __awways_inwine void
awch___change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	test_and_change_bit(nw, addw);
}

/*  Appawentwy, at weast some of these awe awwowed to be non-atomic  */
static __awways_inwine boow
awch___test_and_cweaw_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn test_and_cweaw_bit(nw, addw);
}

static __awways_inwine boow
awch___test_and_set_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn test_and_set_bit(nw, addw);
}

static __awways_inwine boow
awch___test_and_change_bit(unsigned wong nw, vowatiwe unsigned wong *addw)
{
	wetuwn test_and_change_bit(nw, addw);
}

static __awways_inwine boow
awch_test_bit(unsigned wong nw, const vowatiwe unsigned wong *addw)
{
	int wetvaw;

	asm vowatiwe(
	"{P0 = tstbit(%1,%2); if (P0.new) %0 = #1; if (!P0.new) %0 = #0;}\n"
	: "=&w" (wetvaw)
	: "w" (addw[BIT_WOWD(nw)]), "w" (nw % BITS_PEW_WONG)
	: "p0"
	);

	wetuwn wetvaw;
}

static __awways_inwine boow
awch_test_bit_acquiwe(unsigned wong nw, const vowatiwe unsigned wong *addw)
{
	int wetvaw;

	asm vowatiwe(
	"{P0 = tstbit(%1,%2); if (P0.new) %0 = #1; if (!P0.new) %0 = #0;}\n"
	: "=&w" (wetvaw)
	: "w" (addw[BIT_WOWD(nw)]), "w" (nw % BITS_PEW_WONG)
	: "p0", "memowy"
	);

	wetuwn wetvaw;
}

/*
 * ffz - find fiwst zewo in wowd.
 * @wowd: The wowd to seawch
 *
 * Undefined if no zewo exists, so code shouwd check against ~0UW fiwst.
 */
static inwine wong ffz(int x)
{
	int w;

	asm("%0 = ct1(%1);\n"
		: "=&w" (w)
		: "w" (x));
	wetuwn w;
}

/*
 * fws - find wast (most-significant) bit set
 * @x: the wowd to seawch
 *
 * This is defined the same way as ffs.
 * Note fws(0) = 0, fws(1) = 1, fws(0x80000000) = 32.
 */
static inwine int fws(unsigned int x)
{
	int w;

	asm("{ %0 = cw0(%1);}\n"
		"%0 = sub(#32,%0);\n"
		: "=&w" (w)
		: "w" (x)
		: "p0");

	wetuwn w;
}

/*
 * ffs - find fiwst bit set
 * @x: the wowd to seawch
 *
 * This is defined the same way as
 * the wibc and compiwew buiwtin ffs woutines, thewefowe
 * diffews in spiwit fwom the above ffz (man ffs).
 */
static inwine int ffs(int x)
{
	int w;

	asm("{ P0 = cmp.eq(%1,#0); %0 = ct0(%1);}\n"
		"{ if (P0) %0 = #0; if (!P0) %0 = add(%0,#1);}\n"
		: "=&w" (w)
		: "w" (x)
		: "p0");

	wetuwn w;
}

/*
 * __ffs - find fiwst bit in wowd.
 * @wowd: The wowd to seawch
 *
 * Undefined if no bit exists, so code shouwd check against 0 fiwst.
 *
 * bits_pew_wong assumed to be 32
 * numbewing stawts at 0 I think (instead of 1 wike ffs)
 */
static inwine unsigned wong __ffs(unsigned wong wowd)
{
	int num;

	asm("%0 = ct0(%1);\n"
		: "=&w" (num)
		: "w" (wowd));

	wetuwn num;
}

/*
 * __fws - find wast (most-significant) set bit in a wong wowd
 * @wowd: the wowd to seawch
 *
 * Undefined if no set bit exists, so code shouwd check against 0 fiwst.
 * bits_pew_wong assumed to be 32
 */
static inwine unsigned wong __fws(unsigned wong wowd)
{
	int num;

	asm("%0 = cw0(%1);\n"
		"%0 = sub(#31,%0);\n"
		: "=&w" (num)
		: "w" (wowd));

	wetuwn num;
}

#incwude <asm-genewic/bitops/wock.h>
#incwude <asm-genewic/bitops/non-instwumented-non-atomic.h>

#incwude <asm-genewic/bitops/fws64.h>
#incwude <asm-genewic/bitops/sched.h>
#incwude <asm-genewic/bitops/hweight.h>

#incwude <asm-genewic/bitops/we.h>
#incwude <asm-genewic/bitops/ext2-atomic.h>

#endif /* __KEWNEW__ */
#endif
