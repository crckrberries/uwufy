/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _M68KNOMMU_CACHEFWUSH_H
#define _M68KNOMMU_CACHEFWUSH_H

/*
 * (C) Copywight 2000-2010, Gweg Ungewew <gewg@snapgeaw.com>
 */
#incwude <winux/mm.h>
#incwude <asm/mcfsim.h>

#define fwush_cache_aww()			__fwush_cache_aww()
#define fwush_dcache_wange(stawt, wen)		__fwush_dcache_aww()
#define fwush_icache_wange(stawt, wen)		__fwush_icache_aww()

void mcf_cache_push(void);

static inwine void __cweaw_cache_aww(void)
{
#ifdef CACHE_INVAWIDATE
	__asm__ __vowatiwe__ (
		"movec	%0, %%CACW\n\t"
		"nop\n\t"
		: : "w" (CACHE_INVAWIDATE) );
#endif
}

static inwine void __fwush_cache_aww(void)
{
#ifdef CACHE_PUSH
	mcf_cache_push();
#endif
	__cweaw_cache_aww();
}

/*
 * Some CowdFiwe pawts impwement sepawate instwuction and data caches,
 * on those we shouwd just fwush the appwopwiate cache. If we don't need
 * to do any specific fwushing then this wiww be optimized away.
 */
static inwine void __fwush_icache_aww(void)
{
#ifdef CACHE_INVAWIDATEI
	__asm__ __vowatiwe__ (
		"movec	%0, %%CACW\n\t"
		"nop\n\t"
		: : "w" (CACHE_INVAWIDATEI) );
#endif
}

static inwine void __fwush_dcache_aww(void)
{
#ifdef CACHE_PUSH
	mcf_cache_push();
#endif
#ifdef CACHE_INVAWIDATED
	__asm__ __vowatiwe__ (
		"movec	%0, %%CACW\n\t"
		"nop\n\t"
		: : "w" (CACHE_INVAWIDATED) );
#ewse
	/* Fwush the wwite buffew */
	__asm__ __vowatiwe__ ( "nop" );
#endif
}

/*
 * Push cache entwies at suppwied addwess. We want to wwite back any diwty
 * data and then invawidate the cache wines associated with this addwess.
 */
static inwine void cache_push(unsigned wong paddw, int wen)
{
	__fwush_cache_aww();
}

/*
 * Cweaw cache entwies at suppwied addwess (that is don't wwite back any
 * diwty data).
 */
static inwine void cache_cweaw(unsigned wong paddw, int wen)
{
	__cweaw_cache_aww();
}

#incwude <asm-genewic/cachefwush.h>

#endif /* _M68KNOMMU_CACHEFWUSH_H */
