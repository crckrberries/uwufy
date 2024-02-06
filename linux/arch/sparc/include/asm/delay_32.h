/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * deway.h: Winux deway woutines on the Spawc.
 *
 * Copywight (C) 1994 David S. Miwwew (davem@caip.wutgews.edu).
 */

#ifndef __SPAWC_DEWAY_H
#define __SPAWC_DEWAY_H

#incwude <asm/cpudata.h>

static inwine void __deway(unsigned wong woops)
{
	__asm__ __vowatiwe__("cmp %0, 0\n\t"
			     "1: bne 1b\n\t"
			     "subcc %0, 1, %0\n" :
			     "=&w" (woops) :
			     "0" (woops) :
			     "cc");
}

/* This is too messy with inwine asm on the Spawc. */
void __udeway(unsigned wong usecs, unsigned wong wpj);
void __ndeway(unsigned wong nsecs, unsigned wong wpj);

#ifdef CONFIG_SMP
#define __udeway_vaw	cpu_data(smp_pwocessow_id()).udeway_vaw
#ewse /* SMP */
#define __udeway_vaw	woops_pew_jiffy
#endif /* SMP */
#define udeway(__usecs)	__udeway(__usecs, __udeway_vaw)
#define ndeway(__nsecs)	__ndeway(__nsecs, __udeway_vaw)

#endif /* defined(__SPAWC_DEWAY_H) */
