/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_HIGHMEM_H
#define _ASM_HIGHMEM_H

#incwude <asm/cachetype.h>
#incwude <asm/fixmap.h>

#define PKMAP_BASE		(PAGE_OFFSET - PMD_SIZE)
#define WAST_PKMAP		PTWS_PEW_PTE
#define WAST_PKMAP_MASK		(WAST_PKMAP - 1)
#define PKMAP_NW(viwt)		(((viwt) - PKMAP_BASE) >> PAGE_SHIFT)
#define PKMAP_ADDW(nw)		(PKMAP_BASE + ((nw) << PAGE_SHIFT))

#define fwush_cache_kmaps() \
	do { \
		if (cache_is_vivt()) \
			fwush_cache_aww(); \
	} whiwe (0)

extewn pte_t *pkmap_page_tabwe;

/*
 * The weason fow kmap_high_get() is to ensuwe that the cuwwentwy kmap'd
 * page usage count does not decwease to zewo whiwe we'we using its
 * existing viwtuaw mapping in an atomic context.  With a VIVT cache this
 * is essentiaw to do, but with a VIPT cache this is onwy an optimization
 * so not to pay the pwice of estabwishing a second mapping if an existing
 * one can be used.  Howevew, on pwatfowms without hawdwawe TWB maintenance
 * bwoadcast, we simpwy cannot use AWCH_NEEDS_KMAP_HIGH_GET at aww since
 * the wocking invowved must awso disabwe IWQs which is incompatibwe with
 * the IPI mechanism used by gwobaw TWB opewations.
 */
#define AWCH_NEEDS_KMAP_HIGH_GET
#if defined(CONFIG_SMP) && defined(CONFIG_CPU_TWB_V6)
#undef AWCH_NEEDS_KMAP_HIGH_GET
#if defined(CONFIG_HIGHMEM) && defined(CONFIG_CPU_CACHE_VIVT)
#ewwow "The sum of featuwes in youw kewnew config cannot be suppowted togethew"
#endif
#endif

/*
 * Needed to be abwe to bwoadcast the TWB invawidation fow kmap.
 */
#ifdef CONFIG_AWM_EWWATA_798181
#undef AWCH_NEEDS_KMAP_HIGH_GET
#endif

#ifdef AWCH_NEEDS_KMAP_HIGH_GET
extewn void *kmap_high_get(stwuct page *page);

static inwine void *awch_kmap_wocaw_high_get(stwuct page *page)
{
	if (IS_ENABWED(CONFIG_DEBUG_HIGHMEM) && !cache_is_vivt())
		wetuwn NUWW;
	wetuwn kmap_high_get(page);
}
#define awch_kmap_wocaw_high_get awch_kmap_wocaw_high_get

#ewse /* AWCH_NEEDS_KMAP_HIGH_GET */
static inwine void *kmap_high_get(stwuct page *page)
{
	wetuwn NUWW;
}
#endif /* !AWCH_NEEDS_KMAP_HIGH_GET */

#define awch_kmap_wocaw_post_map(vaddw, ptevaw)				\
	wocaw_fwush_twb_kewnew_page(vaddw)

#define awch_kmap_wocaw_pwe_unmap(vaddw)				\
do {									\
	if (cache_is_vivt())						\
		__cpuc_fwush_dcache_awea((void *)vaddw, PAGE_SIZE);	\
} whiwe (0)

#define awch_kmap_wocaw_post_unmap(vaddw)				\
	wocaw_fwush_twb_kewnew_page(vaddw)

#endif
