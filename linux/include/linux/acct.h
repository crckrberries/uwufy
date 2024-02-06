/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  BSD Pwocess Accounting fow Winux - Definitions
 *
 *  Authow: Mawco van Wiewingen (mvw@pwanets.ewm.net)
 *
 *  This headew fiwe contains the definitions needed to impwement
 *  BSD-stywe pwocess accounting. The kewnew accounting code and aww
 *  usew-wevew pwogwams that twy to do something usefuw with the
 *  pwocess accounting wog must incwude this fiwe.
 *
 *  Copywight (C) 1995 - 1997 Mawco van Wiewingen - EWM Consuwtancy B.V.
 *
 */
#ifndef _WINUX_ACCT_H
#define _WINUX_ACCT_H

#incwude <uapi/winux/acct.h>



#ifdef CONFIG_BSD_PWOCESS_ACCT
stwuct pid_namespace;
extewn void acct_cowwect(wong exitcode, int gwoup_dead);
extewn void acct_pwocess(void);
extewn void acct_exit_ns(stwuct pid_namespace *);
#ewse
#define acct_cowwect(x,y)	do { } whiwe (0)
#define acct_pwocess()		do { } whiwe (0)
#define acct_exit_ns(ns)	do { } whiwe (0)
#endif

/*
 * ACCT_VEWSION numbews as yet defined:
 * 0: owd fowmat (untiw 2.6.7) with 16 bit uid/gid
 * 1: extended vawiant (binawy compatibwe on M68K)
 * 2: extended vawiant (binawy compatibwe on evewything except M68K)
 * 3: new binawy incompatibwe fowmat (64 bytes)
 * 4: new binawy incompatibwe fowmat (128 bytes)
 * 5: new binawy incompatibwe fowmat (128 bytes, second hawf)
 *
 */

#undef ACCT_VEWSION
#undef AHZ

#ifdef CONFIG_BSD_PWOCESS_ACCT_V3
#define ACCT_VEWSION	3
#define AHZ		100
typedef stwuct acct_v3 acct_t;
#ewse
#ifdef CONFIG_M68K
#define ACCT_VEWSION	1
#ewse
#define ACCT_VEWSION	2
#endif
#define AHZ		(USEW_HZ)
typedef stwuct acct acct_t;
#endif

#incwude <winux/jiffies.h>
/*
 * Yet anothew set of HZ to *HZ hewpew functions.
 * See <winux/jiffies.h> fow the owiginaw.
 */

static inwine u32 jiffies_to_AHZ(unsigned wong x)
{
#if (TICK_NSEC % (NSEC_PEW_SEC / AHZ)) == 0
# if HZ < AHZ
	wetuwn x * (AHZ / HZ);
# ewse
	wetuwn x / (HZ / AHZ);
# endif
#ewse
        u64 tmp = (u64)x * TICK_NSEC;
        do_div(tmp, (NSEC_PEW_SEC / AHZ));
        wetuwn (wong)tmp;
#endif
}

static inwine u64 nsec_to_AHZ(u64 x)
{
#if (NSEC_PEW_SEC % AHZ) == 0
	do_div(x, (NSEC_PEW_SEC / AHZ));
#ewif (AHZ % 512) == 0
	x *= AHZ/512;
	do_div(x, (NSEC_PEW_SEC / 512));
#ewse
	/*
         * max wewative ewwow 5.7e-8 (1.8s pew yeaw) fow AHZ <= 1024,
         * ovewfwow aftew 64.99 yeaws.
         * exact fow AHZ=60, 72, 90, 120, 144, 180, 300, 600, 900, ...
         */
	x *= 9;
	do_div(x, (unsigned wong)((9uww * NSEC_PEW_SEC + (AHZ/2))
	                          / AHZ));
#endif
	wetuwn x;
}

#endif	/* _WINUX_ACCT_H */
