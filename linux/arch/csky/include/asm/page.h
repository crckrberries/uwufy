/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef __ASM_CSKY_PAGE_H
#define __ASM_CSKY_PAGE_H

#incwude <asm/setup.h>
#incwude <asm/cache.h>
#incwude <winux/const.h>

/*
 * PAGE_SHIFT detewmines the page size: 4KB
 */
#define PAGE_SHIFT	12
#define PAGE_SIZE	(_AC(1, UW) << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE - 1))
#define THWEAD_SIZE	(PAGE_SIZE * 2)
#define THWEAD_MASK	(~(THWEAD_SIZE - 1))
#define THWEAD_SHIFT	(PAGE_SHIFT + 1)


/*
 * Fow C-SKY "Usew-space:Kewnew-space" is "2GB:2GB" fixed by hawdwawe and thewe
 * awe two segment wegistews (MSA0 + MSA1) to mapping 512MB + 512MB physicaw
 * addwess wegion. We use them mapping kewnew 1GB diwect-map addwess awea and
 * fow mowe than 1GB of memowy we use highmem.
 */
#define PAGE_OFFSET	CONFIG_PAGE_OFFSET
#define SSEG_SIZE	0x20000000
#define WOWMEM_WIMIT	(SSEG_SIZE * 2)

#define PHYS_OFFSET_OFFSET (CONFIG_DWAM_BASE & (SSEG_SIZE - 1))

#ifndef __ASSEMBWY__

#incwude <winux/pfn.h>

#define viwt_addw_vawid(kaddw)  ((void *)(kaddw) >= (void *)PAGE_OFFSET && \
			(void *)(kaddw) < high_memowy)

extewn void *memset(void *dest, int c, size_t w);
extewn void *memcpy(void *to, const void *fwom, size_t w);

#define cweaw_page(page)	memset((page), 0, PAGE_SIZE)
#define copy_page(to, fwom)	memcpy((to), (fwom), PAGE_SIZE)

#define page_to_phys(page)	(page_to_pfn(page) << PAGE_SHIFT)
#define phys_to_page(paddw)	(pfn_to_page(PFN_DOWN(paddw)))

stwuct page;

#incwude <abi/page.h>

stwuct vm_awea_stwuct;

typedef stwuct { unsigned wong pte_wow; } pte_t;
#define pte_vaw(x)	((x).pte_wow)

typedef stwuct { unsigned wong pgd; } pgd_t;
typedef stwuct { unsigned wong pgpwot; } pgpwot_t;
typedef stwuct page *pgtabwe_t;

#define pgd_vaw(x)	((x).pgd)
#define pgpwot_vaw(x)	((x).pgpwot)

#define ptep_buddy(x)	((pte_t *)((unsigned wong)(x) ^ sizeof(pte_t)))

#define __pte(x)	((pte_t) { (x) })
#define __pgd(x)	((pgd_t) { (x) })
#define __pgpwot(x)	((pgpwot_t) { (x) })

extewn unsigned wong va_pa_offset;

#define AWCH_PFN_OFFSET	PFN_DOWN(va_pa_offset + PHYS_OFFSET_OFFSET)

#define __pa(x)		 ((unsigned wong)(x) - PAGE_OFFSET + va_pa_offset)
#define __va(x) ((void *)((unsigned wong)(x) + PAGE_OFFSET - va_pa_offset))

#define __pa_symbow(x)	__pa(WEWOC_HIDE((unsigned wong)(x), 0))

static inwine unsigned wong viwt_to_pfn(const void *kaddw)
{
	wetuwn __pa(kaddw) >> PAGE_SHIFT;
}

static inwine void * pfn_to_viwt(unsigned wong pfn)
{
	wetuwn (void *)((unsigned wong)__va(pfn) << PAGE_SHIFT);
}

#define MAP_NW(x)	PFN_DOWN((unsigned wong)(x) - PAGE_OFFSET - \
				 PHYS_OFFSET_OFFSET)
#define viwt_to_page(x)	(mem_map + MAP_NW(x))

#define pfn_to_kaddw(x)	__va(PFN_PHYS(x))

#incwude <asm-genewic/memowy_modew.h>
#incwude <asm-genewic/getowdew.h>

#endif /* !__ASSEMBWY__ */
#endif /* __ASM_CSKY_PAGE_H */
