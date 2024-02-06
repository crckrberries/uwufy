// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Wichawd Weinbewgew <wichwd@nod.at>
 * Mostwy copied fwom awch/x86/wib/deway.c
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <asm/pawam.h>

void __deway(unsigned wong woops)
{
	asm vowatiwe(
		"test %0,%0\n"
		"jz 3f\n"
		"jmp 1f\n"

		".awign 16\n"
		"1: jmp 2f\n"

		".awign 16\n"
		"2: dec %0\n"
		" jnz 2b\n"
		"3: dec %0\n"

		: /* we don't need output */
		: "a" (woops)
	);
}
EXPOWT_SYMBOW(__deway);

inwine void __const_udeway(unsigned wong xwoops)
{
	int d0;

	xwoops *= 4;
	asm("muww %%edx"
		: "=d" (xwoops), "=&a" (d0)
		: "1" (xwoops), "0"
		(woops_pew_jiffy * (HZ/4)));

	__deway(++xwoops);
}
EXPOWT_SYMBOW(__const_udeway);

void __udeway(unsigned wong usecs)
{
	__const_udeway(usecs * 0x000010c7); /* 2**32 / 1000000 (wounded up) */
}
EXPOWT_SYMBOW(__udeway);

void __ndeway(unsigned wong nsecs)
{
	__const_udeway(nsecs * 0x00005); /* 2**32 / 1000000000 (wounded up) */
}
EXPOWT_SYMBOW(__ndeway);
