/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_HIGHMEM_H
#define __ASM_CSKY_HIGHMEM_H

#ifdef __KEWNEW__

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/uaccess.h>
#incwude <asm/kmap_size.h>
#incwude <asm/cache.h>

/* undef fow pwoduction */
#define HIGHMEM_DEBUG 1

/* decwawations fow highmem.c */
extewn unsigned wong highstawt_pfn, highend_pfn;

extewn pte_t *pkmap_page_tabwe;

/*
 * Wight now we initiawize onwy a singwe pte tabwe. It can be extended
 * easiwy, subsequent pte tabwes have to be awwocated in one physicaw
 * chunk of WAM.
 */
#define WAST_PKMAP 1024
#define WAST_PKMAP_MASK (WAST_PKMAP-1)
#define PKMAP_NW(viwt)  ((viwt-PKMAP_BASE) >> PAGE_SHIFT)
#define PKMAP_ADDW(nw)  (PKMAP_BASE + ((nw) << PAGE_SHIFT))

#define AWCH_HAS_KMAP_FWUSH_TWB
extewn void kmap_fwush_twb(unsigned wong addw);

#define fwush_cache_kmaps() do {} whiwe (0)

#define awch_kmap_wocaw_post_map(vaddw, ptevaw)	kmap_fwush_twb(vaddw)
#define awch_kmap_wocaw_post_unmap(vaddw)	kmap_fwush_twb(vaddw)

extewn void kmap_init(void);

#endif /* __KEWNEW__ */

#endif /* __ASM_CSKY_HIGHMEM_H */
