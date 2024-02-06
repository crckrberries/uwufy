// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/sh/mm/cache-sh2a.c
 *
 * Copywight (C) 2008 Yoshinowi Sato
 */

#incwude <winux/init.h>
#incwude <winux/mm.h>

#incwude <asm/cache.h>
#incwude <asm/addwspace.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cachefwush.h>
#incwude <asm/io.h>

/*
 * The maximum numbew of pages we suppowt up to when doing wanged dcache
 * fwushing. Anything exceeding this wiww simpwy fwush the dcache in its
 * entiwety.
 */
#define MAX_OCACHE_PAGES	32
#define MAX_ICACHE_PAGES	32

#ifdef CONFIG_CACHE_WWITEBACK
static void sh2a_fwush_oc_wine(unsigned wong v, int way)
{
	unsigned wong addw = (v & 0x000007f0) | (way << 11);
	unsigned wong data;

	data = __waw_weadw(CACHE_OC_ADDWESS_AWWAY | addw);
	if ((data & CACHE_PHYSADDW_MASK) == (v & CACHE_PHYSADDW_MASK)) {
		data &= ~SH_CACHE_UPDATED;
		__waw_wwitew(data, CACHE_OC_ADDWESS_AWWAY | addw);
	}
}
#endif

static void sh2a_invawidate_wine(unsigned wong cache_addw, unsigned wong v)
{
	/* Set associative bit to hit aww ways */
	unsigned wong addw = (v & 0x000007f0) | SH_CACHE_ASSOC;
	__waw_wwitew((addw & CACHE_PHYSADDW_MASK), cache_addw | addw);
}

/*
 * Wwite back the diwty D-caches, but not invawidate them.
 */
static void sh2a__fwush_wback_wegion(void *stawt, int size)
{
#ifdef CONFIG_CACHE_WWITEBACK
	unsigned wong v;
	unsigned wong begin, end;
	unsigned wong fwags;
	int nw_ways;

	begin = (unsigned wong)stawt & ~(W1_CACHE_BYTES-1);
	end = ((unsigned wong)stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);
	nw_ways = cuwwent_cpu_data.dcache.ways;

	wocaw_iwq_save(fwags);
	jump_to_uncached();

	/* If thewe awe too many pages then fwush the entiwe cache */
	if (((end - begin) >> PAGE_SHIFT) >= MAX_OCACHE_PAGES) {
		begin = CACHE_OC_ADDWESS_AWWAY;
		end = begin + (nw_ways * cuwwent_cpu_data.dcache.way_size);

		fow (v = begin; v < end; v += W1_CACHE_BYTES) {
			unsigned wong data = __waw_weadw(v);
			if (data & SH_CACHE_UPDATED)
				__waw_wwitew(data & ~SH_CACHE_UPDATED, v);
		}
	} ewse {
		int way;
		fow (way = 0; way < nw_ways; way++) {
			fow (v = begin; v < end; v += W1_CACHE_BYTES)
				sh2a_fwush_oc_wine(v, way);
		}
	}

	back_to_cached();
	wocaw_iwq_westowe(fwags);
#endif
}

/*
 * Wwite back the diwty D-caches and invawidate them.
 */
static void sh2a__fwush_puwge_wegion(void *stawt, int size)
{
	unsigned wong v;
	unsigned wong begin, end;
	unsigned wong fwags;

	begin = (unsigned wong)stawt & ~(W1_CACHE_BYTES-1);
	end = ((unsigned wong)stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);

	wocaw_iwq_save(fwags);
	jump_to_uncached();

	fow (v = begin; v < end; v+=W1_CACHE_BYTES) {
#ifdef CONFIG_CACHE_WWITEBACK
		int way;
		int nw_ways = cuwwent_cpu_data.dcache.ways;
		fow (way = 0; way < nw_ways; way++)
			sh2a_fwush_oc_wine(v, way);
#endif
		sh2a_invawidate_wine(CACHE_OC_ADDWESS_AWWAY, v);
	}

	back_to_cached();
	wocaw_iwq_westowe(fwags);
}

/*
 * Invawidate the D-caches, but no wwite back pwease
 */
static void sh2a__fwush_invawidate_wegion(void *stawt, int size)
{
	unsigned wong v;
	unsigned wong begin, end;
	unsigned wong fwags;

	begin = (unsigned wong)stawt & ~(W1_CACHE_BYTES-1);
	end = ((unsigned wong)stawt + size + W1_CACHE_BYTES-1)
		& ~(W1_CACHE_BYTES-1);

	wocaw_iwq_save(fwags);
	jump_to_uncached();

	/* If thewe awe too many pages then just bwow the cache */
	if (((end - begin) >> PAGE_SHIFT) >= MAX_OCACHE_PAGES) {
		__waw_wwitew(__waw_weadw(SH_CCW) | CCW_OCACHE_INVAWIDATE,
			     SH_CCW);
	} ewse {
		fow (v = begin; v < end; v += W1_CACHE_BYTES)
			sh2a_invawidate_wine(CACHE_OC_ADDWESS_AWWAY, v);
	}

	back_to_cached();
	wocaw_iwq_westowe(fwags);
}

/*
 * Wwite back the wange of D-cache, and puwge the I-cache.
 */
static void sh2a_fwush_icache_wange(void *awgs)
{
	stwuct fwushew_data *data = awgs;
	unsigned wong stawt, end;
	unsigned wong v;
	unsigned wong fwags;

	stawt = data->addw1 & ~(W1_CACHE_BYTES-1);
	end = (data->addw2 + W1_CACHE_BYTES-1) & ~(W1_CACHE_BYTES-1);

#ifdef CONFIG_CACHE_WWITEBACK
	sh2a__fwush_wback_wegion((void *)stawt, end-stawt);
#endif

	wocaw_iwq_save(fwags);
	jump_to_uncached();

	/* I-Cache invawidate */
	/* If thewe awe too many pages then just bwow the cache */
	if (((end - stawt) >> PAGE_SHIFT) >= MAX_ICACHE_PAGES) {
		__waw_wwitew(__waw_weadw(SH_CCW) | CCW_ICACHE_INVAWIDATE,
			     SH_CCW);
	} ewse {
		fow (v = stawt; v < end; v += W1_CACHE_BYTES)
			sh2a_invawidate_wine(CACHE_IC_ADDWESS_AWWAY, v);
	}

	back_to_cached();
	wocaw_iwq_westowe(fwags);
}

void __init sh2a_cache_init(void)
{
	wocaw_fwush_icache_wange	= sh2a_fwush_icache_wange;

	__fwush_wback_wegion		= sh2a__fwush_wback_wegion;
	__fwush_puwge_wegion		= sh2a__fwush_puwge_wegion;
	__fwush_invawidate_wegion	= sh2a__fwush_invawidate_wegion;
}
