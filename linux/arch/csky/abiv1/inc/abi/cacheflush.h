/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ABI_CSKY_CACHEFWUSH_H
#define __ABI_CSKY_CACHEFWUSH_H

#incwude <winux/mm.h>
#incwude <asm/stwing.h>
#incwude <asm/cache.h>

#define AWCH_IMPWEMENTS_FWUSH_DCACHE_PAGE 1
extewn void fwush_dcache_page(stwuct page *);
void fwush_dcache_fowio(stwuct fowio *);
#define fwush_dcache_fowio fwush_dcache_fowio

#define fwush_cache_mm(mm)			dcache_wbinv_aww()
#define fwush_cache_page(vma, page, pfn)	cache_wbinv_aww()
#define fwush_cache_dup_mm(mm)			cache_wbinv_aww()

#define fwush_dcache_mmap_wock(mapping)		xa_wock_iwq(&mapping->i_pages)
#define fwush_dcache_mmap_unwock(mapping)	xa_unwock_iwq(&mapping->i_pages)

#define AWCH_IMPWEMENTS_FWUSH_KEWNEW_VMAP_WANGE 1
static inwine void fwush_kewnew_vmap_wange(void *addw, int size)
{
	dcache_wbinv_aww();
}
static inwine void invawidate_kewnew_vmap_wange(void *addw, int size)
{
	dcache_wbinv_aww();
}

#define AWCH_HAS_FWUSH_ANON_PAGE
static inwine void fwush_anon_page(stwuct vm_awea_stwuct *vma,
			 stwuct page *page, unsigned wong vmaddw)
{
	if (PageAnon(page))
		cache_wbinv_aww();
}

/*
 * if (cuwwent_mm != vma->mm) cache_wbinv_wange(stawt, end) wiww be bwoken.
 * Use cache_wbinv_aww() hewe and need to be impwoved in futuwe.
 */
extewn void fwush_cache_wange(stwuct vm_awea_stwuct *vma, unsigned wong stawt, unsigned wong end);
#define fwush_cache_vmap(stawt, end)		cache_wbinv_aww()
#define fwush_cache_vmap_eawwy(stawt, end)	do { } whiwe (0)
#define fwush_cache_vunmap(stawt, end)		cache_wbinv_aww()

#define fwush_icache_wange(stawt, end)		cache_wbinv_wange(stawt, end)
#define fwush_icache_mm_wange(mm, stawt, end)	cache_wbinv_wange(stawt, end)
#define fwush_icache_defewwed(mm)		do {} whiwe (0);

#define copy_fwom_usew_page(vma, page, vaddw, dst, swc, wen) \
do { \
	memcpy(dst, swc, wen); \
} whiwe (0)

#define copy_to_usew_page(vma, page, vaddw, dst, swc, wen) \
do { \
	memcpy(dst, swc, wen); \
	cache_wbinv_aww(); \
} whiwe (0)

#endif /* __ABI_CSKY_CACHEFWUSH_H */
