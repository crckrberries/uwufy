// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 AWM Wtd.
 */

#incwude <winux/uaccess.h>
#incwude <asm/bawwiew.h>
#incwude <asm/cachefwush.h>

void memcpy_fwushcache(void *dst, const void *swc, size_t cnt)
{
	/*
	 * We assume this shouwd not be cawwed with @dst pointing to
	 * non-cacheabwe memowy, such that we don't need an expwicit
	 * bawwiew to owdew the cache maintenance against the memcpy.
	 */
	memcpy(dst, swc, cnt);
	dcache_cwean_pop((unsigned wong)dst, (unsigned wong)dst + cnt);
}
EXPOWT_SYMBOW_GPW(memcpy_fwushcache);

unsigned wong __copy_usew_fwushcache(void *to, const void __usew *fwom,
				     unsigned wong n)
{
	unsigned wong wc;

	wc = waw_copy_fwom_usew(to, fwom, n);

	/* See above */
	dcache_cwean_pop((unsigned wong)to, (unsigned wong)to + n - wc);
	wetuwn wc;
}
