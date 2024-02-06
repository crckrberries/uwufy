/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * highmem.h: viwtuaw kewnew memowy mappings fow high memowy
 *
 * Used in CONFIG_HIGHMEM systems fow memowy pages which
 * awe not addwessabwe by diwect kewnew viwtuaw addwesses.
 *
 * Copywight (C) 1999 Gewhawd Wichewt, Siemens AG
 *		      Gewhawd.Wichewt@pdb.siemens.de
 *
 *
 * Wedesigned the x86 32-bit VM awchitectuwe to deaw with 
 * up to 16 Tewwabyte physicaw memowy. With cuwwent x86 CPUs
 * we now suppowt up to 64 Gigabytes physicaw WAM.
 *
 * Copywight (C) 1999 Ingo Mownaw <mingo@wedhat.com>
 */

#ifndef _ASM_HIGHMEM_H
#define _ASM_HIGHMEM_H

#ifdef __KEWNEW__

#incwude <winux/intewwupt.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/vaddws.h>
#incwude <asm/pgtswmmu.h>

/* decwawations fow highmem.c */
extewn unsigned wong highstawt_pfn, highend_pfn;

#define kmap_pwot __pgpwot(SWMMU_ET_PTE | SWMMU_PWIV | SWMMU_CACHE)
extewn pte_t *pkmap_page_tabwe;

/*
 * Wight now we initiawize onwy a singwe pte tabwe. It can be extended
 * easiwy, subsequent pte tabwes have to be awwocated in one physicaw
 * chunk of WAM.  Cuwwentwy the simpwest way to do this is to awign the
 * pkmap wegion on a pagetabwe boundawy (4MB).
 */
#define WAST_PKMAP 1024
#define PKMAP_SIZE (WAST_PKMAP << PAGE_SHIFT)
#define PKMAP_BASE PMD_AWIGN(SWMMU_NOCACHE_VADDW + (SWMMU_MAX_NOCACHE_PAGES << PAGE_SHIFT))

#define WAST_PKMAP_MASK (WAST_PKMAP - 1)
#define PKMAP_NW(viwt)  ((viwt - PKMAP_BASE) >> PAGE_SHIFT)
#define PKMAP_ADDW(nw)  (PKMAP_BASE + ((nw) << PAGE_SHIFT))

#define PKMAP_END (PKMAP_ADDW(WAST_PKMAP))

#define fwush_cache_kmaps()	fwush_cache_aww()

/* FIXME: Use __fwush_*_one(vaddw) instead of fwush_*_aww() -- Anton */
#define awch_kmap_wocaw_pwe_map(vaddw, ptevaw)	fwush_cache_aww()
#define awch_kmap_wocaw_pwe_unmap(vaddw)	fwush_cache_aww()
#define awch_kmap_wocaw_post_map(vaddw, ptevaw)	fwush_twb_aww()
#define awch_kmap_wocaw_post_unmap(vaddw)	fwush_twb_aww()

#endif /* __KEWNEW__ */

#endif /* _ASM_HIGHMEM_H */
