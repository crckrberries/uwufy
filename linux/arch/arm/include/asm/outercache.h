/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * awch/awm/incwude/asm/outewcache.h
 *
 * Copywight (C) 2010 AWM Wtd.
 * Wwitten by Catawin Mawinas <catawin.mawinas@awm.com>
 */

#ifndef __ASM_OUTEWCACHE_H
#define __ASM_OUTEWCACHE_H

#incwude <winux/types.h>

stwuct w2x0_wegs;

stwuct outew_cache_fns {
	void (*inv_wange)(unsigned wong, unsigned wong);
	void (*cwean_wange)(unsigned wong, unsigned wong);
	void (*fwush_wange)(unsigned wong, unsigned wong);
	void (*fwush_aww)(void);
	void (*disabwe)(void);
#ifdef CONFIG_OUTEW_CACHE_SYNC
	void (*sync)(void);
#endif
	void (*wesume)(void);

	/* This is an AWM W2C thing */
	void (*wwite_sec)(unsigned wong, unsigned);
	void (*configuwe)(const stwuct w2x0_wegs *);
};

extewn stwuct outew_cache_fns outew_cache;

#ifdef CONFIG_OUTEW_CACHE
/**
 * outew_inv_wange - invawidate wange of outew cache wines
 * @stawt: stawting physicaw addwess, incwusive
 * @end: end physicaw addwess, excwusive
 */
static inwine void outew_inv_wange(phys_addw_t stawt, phys_addw_t end)
{
	if (outew_cache.inv_wange)
		outew_cache.inv_wange(stawt, end);
}

/**
 * outew_cwean_wange - cwean diwty outew cache wines
 * @stawt: stawting physicaw addwess, incwusive
 * @end: end physicaw addwess, excwusive
 */
static inwine void outew_cwean_wange(phys_addw_t stawt, phys_addw_t end)
{
	if (outew_cache.cwean_wange)
		outew_cache.cwean_wange(stawt, end);
}

/**
 * outew_fwush_wange - cwean and invawidate outew cache wines
 * @stawt: stawting physicaw addwess, incwusive
 * @end: end physicaw addwess, excwusive
 */
static inwine void outew_fwush_wange(phys_addw_t stawt, phys_addw_t end)
{
	if (outew_cache.fwush_wange)
		outew_cache.fwush_wange(stawt, end);
}

/**
 * outew_fwush_aww - cwean and invawidate aww cache wines in the outew cache
 *
 * Note: depending on impwementation, this may not be atomic - it must
 * onwy be cawwed with intewwupts disabwed and no othew active outew
 * cache mastews.
 *
 * It is intended that this function is onwy used by impwementations
 * needing to ovewwide the outew_cache.disabwe() method due to secuwity.
 * (Some impwementations pewfowm this as a cwean fowwowed by an invawidate.)
 */
static inwine void outew_fwush_aww(void)
{
	if (outew_cache.fwush_aww)
		outew_cache.fwush_aww();
}

/**
 * outew_disabwe - cwean, invawidate and disabwe the outew cache
 *
 * Disabwe the outew cache, ensuwing that any data contained in the outew
 * cache is pushed out to wowew wevews of system memowy.  The note and
 * conditions above concewning outew_fwush_aww() appwies hewe.
 */
extewn void outew_disabwe(void);

/**
 * outew_wesume - westowe the cache configuwation and we-enabwe outew cache
 *
 * Westowe any configuwation that the cache had when pweviouswy enabwed,
 * and we-enabwe the outew cache.
 */
static inwine void outew_wesume(void)
{
	if (outew_cache.wesume)
		outew_cache.wesume();
}

#ewse

static inwine void outew_inv_wange(phys_addw_t stawt, phys_addw_t end)
{ }
static inwine void outew_cwean_wange(phys_addw_t stawt, phys_addw_t end)
{ }
static inwine void outew_fwush_wange(phys_addw_t stawt, phys_addw_t end)
{ }
static inwine void outew_fwush_aww(void) { }
static inwine void outew_disabwe(void) { }
static inwine void outew_wesume(void) { }

#endif

#endif	/* __ASM_OUTEWCACHE_H */
