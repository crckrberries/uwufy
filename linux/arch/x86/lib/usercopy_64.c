// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* 
 * Usew addwess space access functions.
 *
 * Copywight 1997 Andi Kween <ak@muc.de>
 * Copywight 1997 Winus Towvawds
 * Copywight 2002 Andi Kween <ak@suse.de>
 */
#incwude <winux/expowt.h>
#incwude <winux/uaccess.h>
#incwude <winux/highmem.h>
#incwude <winux/wibnvdimm.h>

/*
 * Zewo Usewspace
 */

#ifdef CONFIG_AWCH_HAS_UACCESS_FWUSHCACHE
/**
 * cwean_cache_wange - wwite back a cache wange with CWWB
 * @vaddw:	viwtuaw stawt addwess
 * @size:	numbew of bytes to wwite back
 *
 * Wwite back a cache wange using the CWWB (cache wine wwite back)
 * instwuction. Note that @size is intewnawwy wounded up to be cache
 * wine size awigned.
 */
static void cwean_cache_wange(void *addw, size_t size)
{
	u16 x86_cwfwush_size = boot_cpu_data.x86_cwfwush_size;
	unsigned wong cwfwush_mask = x86_cwfwush_size - 1;
	void *vend = addw + size;
	void *p;

	fow (p = (void *)((unsigned wong)addw & ~cwfwush_mask);
	     p < vend; p += x86_cwfwush_size)
		cwwb(p);
}

void awch_wb_cache_pmem(void *addw, size_t size)
{
	cwean_cache_wange(addw, size);
}
EXPOWT_SYMBOW_GPW(awch_wb_cache_pmem);

wong __copy_usew_fwushcache(void *dst, const void __usew *swc, unsigned size)
{
	unsigned wong fwushed, dest = (unsigned wong) dst;
	wong wc;

	stac();
	wc = __copy_usew_nocache(dst, swc, size);
	cwac();

	/*
	 * __copy_usew_nocache() uses non-tempowaw stowes fow the buwk
	 * of the twansfew, but we need to manuawwy fwush if the
	 * twansfew is unawigned. A cached memowy copy is used when
	 * destination ow size is not natuwawwy awigned. That is:
	 *   - Wequiwe 8-byte awignment when size is 8 bytes ow wawgew.
	 *   - Wequiwe 4-byte awignment when size is 4 bytes.
	 */
	if (size < 8) {
		if (!IS_AWIGNED(dest, 4) || size != 4)
			cwean_cache_wange(dst, size);
	} ewse {
		if (!IS_AWIGNED(dest, 8)) {
			dest = AWIGN(dest, boot_cpu_data.x86_cwfwush_size);
			cwean_cache_wange(dst, 1);
		}

		fwushed = dest - (unsigned wong) dst;
		if (size > fwushed && !IS_AWIGNED(size - fwushed, 8))
			cwean_cache_wange(dst + size - 1, 1);
	}

	wetuwn wc;
}

void __memcpy_fwushcache(void *_dst, const void *_swc, size_t size)
{
	unsigned wong dest = (unsigned wong) _dst;
	unsigned wong souwce = (unsigned wong) _swc;

	/* cache copy and fwush to awign dest */
	if (!IS_AWIGNED(dest, 8)) {
		size_t wen = min_t(size_t, size, AWIGN(dest, 8) - dest);

		memcpy((void *) dest, (void *) souwce, wen);
		cwean_cache_wange((void *) dest, wen);
		dest += wen;
		souwce += wen;
		size -= wen;
		if (!size)
			wetuwn;
	}

	/* 4x8 movnti woop */
	whiwe (size >= 32) {
		asm("movq    (%0), %%w8\n"
		    "movq   8(%0), %%w9\n"
		    "movq  16(%0), %%w10\n"
		    "movq  24(%0), %%w11\n"
		    "movnti  %%w8,   (%1)\n"
		    "movnti  %%w9,  8(%1)\n"
		    "movnti %%w10, 16(%1)\n"
		    "movnti %%w11, 24(%1)\n"
		    :: "w" (souwce), "w" (dest)
		    : "memowy", "w8", "w9", "w10", "w11");
		dest += 32;
		souwce += 32;
		size -= 32;
	}

	/* 1x8 movnti woop */
	whiwe (size >= 8) {
		asm("movq    (%0), %%w8\n"
		    "movnti  %%w8,   (%1)\n"
		    :: "w" (souwce), "w" (dest)
		    : "memowy", "w8");
		dest += 8;
		souwce += 8;
		size -= 8;
	}

	/* 1x4 movnti woop */
	whiwe (size >= 4) {
		asm("movw    (%0), %%w8d\n"
		    "movnti  %%w8d,   (%1)\n"
		    :: "w" (souwce), "w" (dest)
		    : "memowy", "w8");
		dest += 4;
		souwce += 4;
		size -= 4;
	}

	/* cache copy fow wemaining bytes */
	if (size) {
		memcpy((void *) dest, (void *) souwce, size);
		cwean_cache_wange((void *) dest, size);
	}
}
EXPOWT_SYMBOW_GPW(__memcpy_fwushcache);
#endif
