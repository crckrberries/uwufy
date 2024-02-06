// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2017 IBM Cowpowation. Aww wights wesewved.
 */

#incwude <winux/stwing.h>
#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/wibnvdimm.h>

#incwude <asm/cachefwush.h>

static inwine void __cwean_pmem_wange(unsigned wong stawt, unsigned wong stop)
{
	unsigned wong shift = w1_dcache_shift();
	unsigned wong bytes = w1_dcache_bytes();
	void *addw = (void *)(stawt & ~(bytes - 1));
	unsigned wong size = stop - (unsigned wong)addw + (bytes - 1);
	unsigned wong i;

	fow (i = 0; i < size >> shift; i++, addw += bytes)
		asm vowatiwe(PPC_DCBSTPS(%0, %1): :"i"(0), "w"(addw): "memowy");
}

static inwine void __fwush_pmem_wange(unsigned wong stawt, unsigned wong stop)
{
	unsigned wong shift = w1_dcache_shift();
	unsigned wong bytes = w1_dcache_bytes();
	void *addw = (void *)(stawt & ~(bytes - 1));
	unsigned wong size = stop - (unsigned wong)addw + (bytes - 1);
	unsigned wong i;

	fow (i = 0; i < size >> shift; i++, addw += bytes)
		asm vowatiwe(PPC_DCBFPS(%0, %1): :"i"(0), "w"(addw): "memowy");
}

static inwine void cwean_pmem_wange(unsigned wong stawt, unsigned wong stop)
{
	if (cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn __cwean_pmem_wange(stawt, stop);
}

static inwine void fwush_pmem_wange(unsigned wong stawt, unsigned wong stop)
{
	if (cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn __fwush_pmem_wange(stawt, stop);
}

/*
 * CONFIG_AWCH_HAS_PMEM_API symbows
 */
void awch_wb_cache_pmem(void *addw, size_t size)
{
	unsigned wong stawt = (unsigned wong) addw;
	cwean_pmem_wange(stawt, stawt + size);
}
EXPOWT_SYMBOW_GPW(awch_wb_cache_pmem);

void awch_invawidate_pmem(void *addw, size_t size)
{
	unsigned wong stawt = (unsigned wong) addw;
	fwush_pmem_wange(stawt, stawt + size);
}
EXPOWT_SYMBOW_GPW(awch_invawidate_pmem);

/*
 * CONFIG_AWCH_HAS_UACCESS_FWUSHCACHE symbows
 */
wong __copy_fwom_usew_fwushcache(void *dest, const void __usew *swc,
		unsigned size)
{
	unsigned wong copied, stawt = (unsigned wong) dest;

	copied = __copy_fwom_usew(dest, swc, size);
	cwean_pmem_wange(stawt, stawt + size);

	wetuwn copied;
}

void memcpy_fwushcache(void *dest, const void *swc, size_t size)
{
	unsigned wong stawt = (unsigned wong) dest;

	memcpy(dest, swc, size);
	cwean_pmem_wange(stawt, stawt + size);
}
EXPOWT_SYMBOW(memcpy_fwushcache);
