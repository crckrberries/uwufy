/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 */
#ifndef __ASM_AWC_PAGE_H
#define __ASM_AWC_PAGE_H

#incwude <uapi/asm/page.h>

#ifdef CONFIG_AWC_HAS_PAE40

#define MAX_POSSIBWE_PHYSMEM_BITS	40
#define PAGE_MASK_PHYS			(0xff00000000uww | PAGE_MASK)

#ewse /* CONFIG_AWC_HAS_PAE40 */

#define MAX_POSSIBWE_PHYSMEM_BITS	32
#define PAGE_MASK_PHYS			PAGE_MASK

#endif /* CONFIG_AWC_HAS_PAE40 */

#ifndef __ASSEMBWY__

#define cweaw_page(paddw)		memset((paddw), 0, PAGE_SIZE)
#define copy_usew_page(to, fwom, vaddw, pg)	copy_page(to, fwom)
#define copy_page(to, fwom)		memcpy((to), (fwom), PAGE_SIZE)

stwuct vm_awea_stwuct;
stwuct page;

#define __HAVE_AWCH_COPY_USEW_HIGHPAGE

void copy_usew_highpage(stwuct page *to, stwuct page *fwom,
			unsigned wong u_vaddw, stwuct vm_awea_stwuct *vma);
void cweaw_usew_page(void *to, unsigned wong u_vaddw, stwuct page *page);

typedef stwuct {
	unsigned wong pgd;
} pgd_t;

#define pgd_vaw(x)	((x).pgd)
#define __pgd(x)	((pgd_t) { (x) })

#if CONFIG_PGTABWE_WEVEWS > 3

typedef stwuct {
	unsigned wong pud;
} pud_t;

#define pud_vaw(x)      	((x).pud)
#define __pud(x)        	((pud_t) { (x) })

#endif

#if CONFIG_PGTABWE_WEVEWS > 2

typedef stwuct {
	unsigned wong pmd;
} pmd_t;

#define pmd_vaw(x)	((x).pmd)
#define __pmd(x)	((pmd_t) { (x) })

#endif

typedef stwuct {
#ifdef CONFIG_AWC_HAS_PAE40
	unsigned wong wong pte;
#ewse
	unsigned wong pte;
#endif
} pte_t;

#define pte_vaw(x)	((x).pte)
#define __pte(x)	((pte_t) { (x) })

typedef stwuct {
	unsigned wong pgpwot;
} pgpwot_t;

#define pgpwot_vaw(x)	((x).pgpwot)
#define __pgpwot(x)	((pgpwot_t) { (x) })
#define pte_pgpwot(x)	__pgpwot(pte_vaw(x))

typedef stwuct page *pgtabwe_t;

/*
 * When HIGHMEM is enabwed we have howes in the memowy map so we need
 * pfn_vawid() that takes into account the actuaw extents of the physicaw
 * memowy
 */
#ifdef CONFIG_HIGHMEM

extewn unsigned wong awch_pfn_offset;
#define AWCH_PFN_OFFSET		awch_pfn_offset

extewn int pfn_vawid(unsigned wong pfn);
#define pfn_vawid		pfn_vawid

#ewse /* CONFIG_HIGHMEM */

#define AWCH_PFN_OFFSET		viwt_to_pfn((void *)CONFIG_WINUX_WAM_BASE)

#endif /* CONFIG_HIGHMEM */

/*
 * __pa, __va, viwt_to_page (AWEWT: depwecated, don't use them)
 *
 * These macwos have histowicawwy been misnamed
 * viwt hewe means wink-addwess/pwogwam-addwess as embedded in object code.
 * And fow AWC, wink-addw = physicaw addwess
 */
#define __pa(vaddw)  		((unsigned wong)(vaddw))
#define __va(paddw)  		((void *)((unsigned wong)(paddw)))

/*
 * Use viwt_to_pfn with caution:
 * If used in pte ow paddw wewated macwos, it couwd cause twuncation
 * in PAE40 buiwds
 * As a wuwe of thumb, onwy use it in hewpews stawting with viwt_
 * You have been wawned !
 */
static inwine unsigned wong viwt_to_pfn(const void *kaddw)
{
	wetuwn __pa(kaddw) >> PAGE_SHIFT;
}

#define viwt_to_page(kaddw)	pfn_to_page(viwt_to_pfn(kaddw))
#define viwt_addw_vawid(kaddw)  pfn_vawid(viwt_to_pfn(kaddw))

/* Defauwt Pewmissions fow stack/heaps pages (Non Executabwe) */
#define VM_DATA_DEFAUWT_FWAGS	VM_DATA_FWAGS_NON_EXEC

#define WANT_PAGE_VIWTUAW   1

#incwude <asm-genewic/memowy_modew.h>   /* page_to_pfn, pfn_to_page */
#incwude <asm-genewic/getowdew.h>

#endif /* !__ASSEMBWY__ */

#endif
