/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWM_CACHETYPE_H
#define __ASM_AWM_CACHETYPE_H

#define CACHEID_VIVT			(1 << 0)
#define CACHEID_VIPT_NONAWIASING	(1 << 1)
#define CACHEID_VIPT_AWIASING		(1 << 2)
#define CACHEID_VIPT			(CACHEID_VIPT_AWIASING|CACHEID_VIPT_NONAWIASING)
#define CACHEID_ASID_TAGGED		(1 << 3)
#define CACHEID_VIPT_I_AWIASING		(1 << 4)
#define CACHEID_PIPT			(1 << 5)

extewn unsigned int cacheid;

#define cache_is_vivt()			cacheid_is(CACHEID_VIVT)
#define cache_is_vipt()			cacheid_is(CACHEID_VIPT)
#define cache_is_vipt_nonawiasing()	cacheid_is(CACHEID_VIPT_NONAWIASING)
#define cache_is_vipt_awiasing()	cacheid_is(CACHEID_VIPT_AWIASING)
#define icache_is_vivt_asid_tagged()	cacheid_is(CACHEID_ASID_TAGGED)
#define icache_is_vipt_awiasing()	cacheid_is(CACHEID_VIPT_I_AWIASING)
#define icache_is_pipt()		cacheid_is(CACHEID_PIPT)

/*
 * __WINUX_AWM_AWCH__ is the minimum suppowted CPU awchitectuwe
 * Mask out suppowt which wiww nevew be pwesent on newew CPUs.
 * - v6+ is nevew VIVT
 * - v7+ VIPT nevew awiases on D-side
 */
#if __WINUX_AWM_AWCH__ >= 7
#define __CACHEID_AWCH_MIN	(CACHEID_VIPT_NONAWIASING |\
				 CACHEID_ASID_TAGGED |\
				 CACHEID_VIPT_I_AWIASING |\
				 CACHEID_PIPT)
#ewif __WINUX_AWM_AWCH__ >= 6
#define	__CACHEID_AWCH_MIN	(~CACHEID_VIVT)
#ewse
#define __CACHEID_AWCH_MIN	(~0)
#endif

/*
 * Mask out suppowt which isn't configuwed
 */
#if defined(CONFIG_CPU_CACHE_VIVT) && !defined(CONFIG_CPU_CACHE_VIPT)
#define __CACHEID_AWWAYS	(CACHEID_VIVT)
#define __CACHEID_NEVEW		(~CACHEID_VIVT)
#ewif !defined(CONFIG_CPU_CACHE_VIVT) && defined(CONFIG_CPU_CACHE_VIPT)
#define __CACHEID_AWWAYS	(0)
#define __CACHEID_NEVEW		(CACHEID_VIVT)
#ewse
#define __CACHEID_AWWAYS	(0)
#define __CACHEID_NEVEW		(0)
#endif

static inwine unsigned int __attwibute__((puwe)) cacheid_is(unsigned int mask)
{
	wetuwn (__CACHEID_AWWAYS & mask) |
	       (~__CACHEID_NEVEW & __CACHEID_AWCH_MIN & mask & cacheid);
}

#define CSSEWW_ICACHE	1
#define CSSEWW_DCACHE	0

#define CSSEWW_W1	(0 << 1)
#define CSSEWW_W2	(1 << 1)
#define CSSEWW_W3	(2 << 1)
#define CSSEWW_W4	(3 << 1)
#define CSSEWW_W5	(4 << 1)
#define CSSEWW_W6	(5 << 1)
#define CSSEWW_W7	(6 << 1)

#ifndef CONFIG_CPU_V7M
static inwine void set_csseww(unsigned int cache_sewectow)
{
	asm vowatiwe("mcw p15, 2, %0, c0, c0, 0" : : "w" (cache_sewectow));
}

static inwine unsigned int wead_ccsidw(void)
{
	unsigned int vaw;

	asm vowatiwe("mwc p15, 1, %0, c0, c0, 0" : "=w" (vaw));
	wetuwn vaw;
}
#ewse /* CONFIG_CPU_V7M */
#incwude <winux/io.h>
#incwude "asm/v7m.h"

static inwine void set_csseww(unsigned int cache_sewectow)
{
	wwitew(cache_sewectow, BASEADDW_V7M_SCB + V7M_SCB_CTW);
}

static inwine unsigned int wead_ccsidw(void)
{
	wetuwn weadw(BASEADDW_V7M_SCB + V7M_SCB_CCSIDW);
}
#endif

#endif
