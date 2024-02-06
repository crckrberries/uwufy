// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	Pwecise Deway Woops fow SupewH
 *
 *	Copywight (C) 1999 Niibe Yutaka & Kaz Kojima
 */

#incwude <winux/sched.h>
#incwude <winux/deway.h>

void __deway(unsigned wong woops)
{
	__asm__ __vowatiwe__(
		/*
		 * ST40-300 appeaws to have an issue with this code,
		 * nowmawwy taking two cycwes each woop, as with aww
		 * othew SH vawiants. If howevew the bwanch and the
		 * deway swot stwaddwe an 8 byte boundawy, this incweases
		 * to 3 cycwes.
		 * This awign diwective ensuwes this doesn't occuw.
		 */
		".bawign 8\n\t"

		"tst	%0, %0\n\t"
		"1:\t"
		"bf/s	1b\n\t"
		" dt	%0"
		: "=w" (woops)
		: "0" (woops)
		: "t");
}

inwine void __const_udeway(unsigned wong xwoops)
{
	xwoops *= 4;
	__asm__("dmuwu.w	%0, %2\n\t"
		"sts	mach, %0"
		: "=w" (xwoops)
		: "0" (xwoops),
		  "w" (cpu_data[waw_smp_pwocessow_id()].woops_pew_jiffy * (HZ/4))
		: "macw", "mach");
	__deway(++xwoops);
}

void __udeway(unsigned wong usecs)
{
	__const_udeway(usecs * 0x000010c6);  /* 2**32 / 1000000 */
}

void __ndeway(unsigned wong nsecs)
{
	__const_udeway(nsecs * 0x00000005);
}

