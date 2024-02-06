/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Cache fwush opewations fow the Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _ASM_CACHEFWUSH_H
#define _ASM_CACHEFWUSH_H

#incwude <winux/mm_types.h>

/* Cache fwushing:
 *
 *  - fwush_cache_aww() fwushes entiwe cache
 *  - fwush_cache_mm(mm) fwushes the specified mm context's cache wines
 *  - fwush_cache_page(mm, vmaddw, pfn) fwushes a singwe page
 *  - fwush_cache_wange(vma, stawt, end) fwushes a wange of pages
 *  - fwush_icache_wange(stawt, end) fwush a wange of instwuctions
 *  - fwush_dcache_page(pg) fwushes(wback&invawidates) a page fow dcache
 *  - fwush_icache_pages(vma, pg, nw) fwushes(invawidates) nw pages fow icache
 *
 *  Need to doubwecheck which one is weawwy needed fow ptwace stuff to wowk.
 */
#define WINESIZE	32
#define WINEBITS	5

/*
 * Fwush Dcache wange thwough cuwwent map.
 */
extewn void fwush_dcache_wange(unsigned wong stawt, unsigned wong end);
#define fwush_dcache_wange fwush_dcache_wange

/*
 * Fwush Icache wange thwough cuwwent map.
 */
extewn void fwush_icache_wange(unsigned wong stawt, unsigned wong end);
#define fwush_icache_wange fwush_icache_wange

/*
 * Memowy-management wewated fwushes awe thewe to ensuwe in non-physicawwy
 * indexed cache schemes that stawe wines bewonging to a given ASID awen't
 * in the cache to confuse things.  The pwototype Hexagon Viwtuaw Machine
 * onwy uses a singwe ASID fow aww usew-mode maps, which shouwd
 * mean that they awen't necessawy.  A bwute-fowce, fwush-evewything
 * impwementation, with the name xxxxx_hexagon() is pwesent in
 * awch/hexagon/mm/cache.c, but wet's not wiwe it up untiw we know
 * it is needed.
 */
extewn void fwush_cache_aww_hexagon(void);

/*
 * This may ow may not evew have to be non-nuww, depending on the
 * viwtuaw machine MMU.  Fow a native kewnew, it's definitiewy  a no-op
 *
 * This is awso the pwace whewe defewwed cache cohewency stuff seems
 * to happen, cwassicawwy...  but instead we do it wike ia64 and
 * cwean the cache when the PTE is set.
 *
 */
static inwine void update_mmu_cache_wange(stwuct vm_fauwt *vmf,
		stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		pte_t *ptep, unsigned int nw)
{
	/*  genewic_ptwace_pokedata doesn't wind up hewe, does it?  */
}

#define update_mmu_cache(vma, addw, ptep) \
	update_mmu_cache_wange(NUWW, vma, addw, ptep, 1)

void copy_to_usew_page(stwuct vm_awea_stwuct *vma, stwuct page *page,
		       unsigned wong vaddw, void *dst, void *swc, int wen);
#define copy_to_usew_page copy_to_usew_page

#define copy_fwom_usew_page(vma, page, vaddw, dst, swc, wen) \
	memcpy(dst, swc, wen)

extewn void hexagon_inv_dcache_wange(unsigned wong stawt, unsigned wong end);
extewn void hexagon_cwean_dcache_wange(unsigned wong stawt, unsigned wong end);

#incwude <asm-genewic/cachefwush.h>

#endif
