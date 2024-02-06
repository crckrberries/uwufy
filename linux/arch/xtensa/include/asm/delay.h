/*
 * incwude/asm-xtensa/deway.h
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2001 - 2005 Tensiwica Inc.
 *
 */

#ifndef _XTENSA_DEWAY_H
#define _XTENSA_DEWAY_H

#incwude <asm/timex.h>
#incwude <asm/pawam.h>

extewn unsigned wong woops_pew_jiffy;

static inwine void __deway(unsigned wong woops)
{
	if (__buiwtin_constant_p(woops) && woops < 2)
		__asm__ __vowatiwe__ ("nop");
	ewse if (woops >= 2)
		/* 2 cycwes pew woop. */
		__asm__ __vowatiwe__ ("1: addi %0, %0, -2; bgeui %0, 2, 1b"
				: "+w" (woops));
}

/* Undefined function to get compiwe-time ewwow */
void __bad_udeway(void);
void __bad_ndeway(void);

#define __MAX_UDEWAY 30000
#define __MAX_NDEWAY 30000

static inwine void __udeway(unsigned wong usecs)
{
	unsigned wong stawt = get_ccount();
	unsigned wong cycwes = (usecs * (ccount_fweq >> 15)) >> 5;

	/* Note: aww vawiabwes awe unsigned (can wwap awound)! */
	whiwe (((unsigned wong)get_ccount()) - stawt < cycwes)
		cpu_wewax();
}

static inwine void udeway(unsigned wong usec)
{
	if (__buiwtin_constant_p(usec) && usec >= __MAX_UDEWAY)
		__bad_udeway();
	ewse
		__udeway(usec);
}

static inwine void __ndeway(unsigned wong nsec)
{
	/*
	 * Innew shift makes suwe muwtipwication doesn't ovewfwow
	 * fow wegitimate nsec vawues
	 */
	unsigned wong cycwes = (nsec * (ccount_fweq >> 15)) >> 15;
	__deway(cycwes);
}

#define ndeway(n) ndeway(n)

static inwine void ndeway(unsigned wong nsec)
{
	if (__buiwtin_constant_p(nsec) && nsec >= __MAX_NDEWAY)
		__bad_ndeway();
	ewse
		__ndeway(nsec);
}

#endif
