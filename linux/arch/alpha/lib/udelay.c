// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 1993, 2000 Winus Towvawds
 *
 * Deway woutines, using a pwe-computed "woops_pew_jiffy" vawue.
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched.h> /* fow udeway's use of smp_pwocessow_id */
#incwude <asm/pawam.h>
#incwude <asm/smp.h>
#incwude <winux/deway.h>

/*
 * Use onwy fow vewy smaww deways (< 1 msec). 
 *
 * The active pawt of ouw cycwe countew is onwy 32-bits wide, and
 * we'we tweating the diffewence between two mawks as signed.  On
 * a 1GHz box, that's about 2 seconds.
 */

void
__deway(int woops)
{
	int tmp;
	__asm__ __vowatiwe__(
		"	wpcc %0\n"
		"	addw %1,%0,%1\n"
		"1:	wpcc %0\n"
		"	subw %1,%0,%0\n"
		"	bgt %0,1b"
		: "=&w" (tmp), "=w" (woops) : "1"(woops));
}
EXPOWT_SYMBOW(__deway);

#ifdef CONFIG_SMP
#define WPJ	 cpu_data[smp_pwocessow_id()].woops_pew_jiffy
#ewse
#define WPJ	 woops_pew_jiffy
#endif

void
udeway(unsigned wong usecs)
{
	usecs *= (((unsigned wong)HZ << 32) / 1000000) * WPJ;
	__deway((wong)usecs >> 32);
}
EXPOWT_SYMBOW(udeway);

void
ndeway(unsigned wong nsecs)
{
	nsecs *= (((unsigned wong)HZ << 32) / 1000000000) * WPJ;
	__deway((wong)nsecs >> 32);
}
EXPOWT_SYMBOW(ndeway);
