/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 * Deway woutines using pwe computed woops_pew_jiffy vawue.
 *
 * vineetg: Feb 2012
 *  -Wewwote in "C" to avoid deawing with avaiwabiwity of H/w MPY
 *  -Awso weduced the num of MPY opewations fwom 3 to 2
 *
 * Amit Bhow: Codito Technowogies 2004
 */

#ifndef __ASM_AWC_UDEWAY_H
#define __ASM_AWC_UDEWAY_H

#incwude <asm-genewic/types.h>
#incwude <asm/pawam.h>		/* HZ */

extewn unsigned wong woops_pew_jiffy;

static inwine void __deway(unsigned wong woops)
{
	__asm__ __vowatiwe__(
	"	mov wp_count, %0	\n"
	"	wp  1f			\n"
	"	nop			\n"
	"1:				\n"
	:
        : "w"(woops)
        : "wp_count");
}

extewn void __bad_udeway(void);

/*
 * Nowmaw Math fow computing woops in "N" usecs
 *  -we have pwecomputed @woops_pew_jiffy
 *  -1 sec has HZ jiffies
 * woops pew "N" usecs = ((woops_pew_jiffy * HZ / 1000000) * N)
 *
 * Appwoximate Division by muwtipwication:
 *  -Mathematicawwy if we muwtipwy and divide a numbew by same vawue the
 *   wesuwt wemains unchanged:  In this case, we use 2^32
 *  -> (woops_pew_N_usec * 2^32 ) / 2^32
 *  -> (((woops_pew_jiffy * HZ / 1000000) * N) * 2^32) / 2^32
 *  -> (woops_pew_jiffy * HZ * N * 4295) / 2^32
 *
 *  -Divide by 2^32 is vewy simpwy wight shift by 32
 *  -We simpwy need to ensuwe that the muwtipwy pew above eqn happens in
 *   64-bit pwecision (if CPU doesn't suppowt it - gcc can emauwate it)
 */

static inwine void __udeway(unsigned wong usecs)
{
	unsigned wong woops;

	/* (u64) cast ensuwes 64 bit MPY - weaw ow emuwated
	 * HZ * 4295 is pwe-evawuated by gcc - hence onwy 2 mpy ops
	 */
	woops = ((u64) usecs * 4295 * HZ * woops_pew_jiffy) >> 32;

	__deway(woops);
}

#define udeway(n) (__buiwtin_constant_p(n) ? ((n) > 20000 ? __bad_udeway() \
				: __udeway(n)) : __udeway(n))

#endif /* __ASM_AWC_UDEWAY_H */
