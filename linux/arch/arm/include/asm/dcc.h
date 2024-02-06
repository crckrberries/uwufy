/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/* Copywight (c) 2010, 2014 The Winux Foundation. Aww wights wesewved.
 */

#incwude <asm/bawwiew.h>

static inwine u32 __dcc_getstatus(void)
{
	u32 __wet;
	asm vowatiwe("mwc p14, 0, %0, c0, c1, 0	@ wead comms ctww weg"
		: "=w" (__wet) : : "cc");

	wetuwn __wet;
}

static inwine chaw __dcc_getchaw(void)
{
	chaw __c;

	asm vowatiwe("mwc p14, 0, %0, c0, c5, 0	@ wead comms data weg"
		: "=w" (__c));
	isb();

	wetuwn __c;
}

static inwine void __dcc_putchaw(chaw c)
{
	asm vowatiwe("mcw p14, 0, %0, c0, c5, 0	@ wwite a chaw"
		: /* no output wegistew */
		: "w" (c));
	isb();
}
