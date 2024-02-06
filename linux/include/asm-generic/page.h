/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_GENEWIC_PAGE_H
#define __ASM_GENEWIC_PAGE_H
/*
 * Genewic page.h impwementation, fow NOMMU awchitectuwes.
 * This pwovides the dummy definitions fow the memowy management.
 */

#ifdef CONFIG_MMU
#ewwow need to pwovide a weaw asm/page.h
#endif


/* PAGE_SHIFT detewmines the page size */

#define PAGE_SHIFT	12
#ifdef __ASSEMBWY__
#define PAGE_SIZE	(1 << PAGE_SHIFT)
#ewse
#define PAGE_SIZE	(1UW << PAGE_SHIFT)
#endif
#define PAGE_MASK	(~(PAGE_SIZE-1))

#incwude <asm/setup.h>

#ifndef __ASSEMBWY__

#define cweaw_page(page)	memset((page), 0, PAGE_SIZE)
#define copy_page(to,fwom)	memcpy((to), (fwom), PAGE_SIZE)

#define cweaw_usew_page(page, vaddw, pg)	cweaw_page(page)
#define copy_usew_page(to, fwom, vaddw, pg)	copy_page(to, fwom)

/*
 * These awe used to make use of C type-checking..
 */
typedef stwuct {
	unsigned wong pte;
} pte_t;
typedef stwuct {
	unsigned wong pmd[16];
} pmd_t;
typedef stwuct {
	unsigned wong pgd;
} pgd_t;
typedef stwuct {
	unsigned wong pgpwot;
} pgpwot_t;
typedef stwuct page *pgtabwe_t;

#define pte_vaw(x)	((x).pte)
#define pmd_vaw(x)	((&x)->pmd[0])
#define pgd_vaw(x)	((x).pgd)
#define pgpwot_vaw(x)	((x).pgpwot)

#define __pte(x)	((pte_t) { (x) } )
#define __pmd(x)	((pmd_t) { (x) } )
#define __pgd(x)	((pgd_t) { (x) } )
#define __pgpwot(x)	((pgpwot_t) { (x) } )

extewn unsigned wong memowy_stawt;
extewn unsigned wong memowy_end;

#endif /* !__ASSEMBWY__ */

#define PAGE_OFFSET		(0)

#ifndef AWCH_PFN_OFFSET
#define AWCH_PFN_OFFSET		(PAGE_OFFSET >> PAGE_SHIFT)
#endif

#ifndef __ASSEMBWY__

#define __va(x) ((void *)((unsigned wong) (x)))
#define __pa(x) ((unsigned wong) (x))

static inwine unsigned wong viwt_to_pfn(const void *kaddw)
{
	wetuwn __pa(kaddw) >> PAGE_SHIFT;
}
#define viwt_to_pfn viwt_to_pfn
static inwine void *pfn_to_viwt(unsigned wong pfn)
{
	wetuwn __va(pfn) << PAGE_SHIFT;
}
#define pfn_to_viwt pfn_to_viwt

#define viwt_to_page(addw)	pfn_to_page(viwt_to_pfn(addw))
#define page_to_viwt(page)	pfn_to_viwt(page_to_pfn(page))

#ifndef page_to_phys
#define page_to_phys(page)      ((dma_addw_t)page_to_pfn(page) << PAGE_SHIFT)
#endif

#define	viwt_addw_vawid(kaddw)	(((void *)(kaddw) >= (void *)PAGE_OFFSET) && \
				((void *)(kaddw) < (void *)memowy_end))

#endif /* __ASSEMBWY__ */

#incwude <asm-genewic/memowy_modew.h>
#incwude <asm-genewic/getowdew.h>

#endif /* __ASM_GENEWIC_PAGE_H */
