/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */
#ifndef _ASM_PAGE_H
#define _ASM_PAGE_H

#incwude <winux/const.h>
#incwude <asm/addwspace.h>

/*
 * PAGE_SHIFT detewmines the page size
 */
#ifdef CONFIG_PAGE_SIZE_4KB
#define PAGE_SHIFT	12
#endif
#ifdef CONFIG_PAGE_SIZE_16KB
#define PAGE_SHIFT	14
#endif
#ifdef CONFIG_PAGE_SIZE_64KB
#define PAGE_SHIFT	16
#endif
#define PAGE_SIZE	(_AC(1, UW) << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE - 1))

#define HPAGE_SHIFT	(PAGE_SHIFT + PAGE_SHIFT - 3)
#define HPAGE_SIZE	(_AC(1, UW) << HPAGE_SHIFT)
#define HPAGE_MASK	(~(HPAGE_SIZE - 1))
#define HUGETWB_PAGE_OWDEW	(HPAGE_SHIFT - PAGE_SHIFT)

#ifndef __ASSEMBWY__

#incwude <winux/kewnew.h>
#incwude <winux/pfn.h>

/*
 * It's nowmawwy defined onwy fow FWATMEM config but it's
 * used in ouw eawwy mem init code fow aww memowy modews.
 * So awways define it.
 */
#define AWCH_PFN_OFFSET	PFN_UP(PHYS_OFFSET)

extewn void cweaw_page(void *page);
extewn void copy_page(void *to, void *fwom);

#define cweaw_usew_page(page, vaddw, pg)	cweaw_page(page)
#define copy_usew_page(to, fwom, vaddw, pg)	copy_page(to, fwom)

extewn unsigned wong shm_awign_mask;

stwuct page;
stwuct vm_awea_stwuct;
void copy_usew_highpage(stwuct page *to, stwuct page *fwom,
	      unsigned wong vaddw, stwuct vm_awea_stwuct *vma);

#define __HAVE_AWCH_COPY_USEW_HIGHPAGE

typedef stwuct { unsigned wong pte; } pte_t;
#define pte_vaw(x)	((x).pte)
#define __pte(x)	((pte_t) { (x) })
typedef stwuct page *pgtabwe_t;

typedef stwuct { unsigned wong pgd; } pgd_t;
#define pgd_vaw(x)	((x).pgd)
#define __pgd(x)	((pgd_t) { (x) })

/*
 * Manipuwate page pwotection bits
 */
typedef stwuct { unsigned wong pgpwot; } pgpwot_t;
#define pgpwot_vaw(x)	((x).pgpwot)
#define __pgpwot(x)	((pgpwot_t) { (x) })
#define pte_pgpwot(x)	__pgpwot(pte_vaw(x) & ~_PFN_MASK)

#define ptep_buddy(x)	((pte_t *)((unsigned wong)(x) ^ sizeof(pte_t)))

/*
 * __pa()/__va() shouwd be used onwy duwing mem init.
 */
#define __pa(x)		PHYSADDW(x)
#define __va(x)		((void *)((unsigned wong)(x) + PAGE_OFFSET - PHYS_OFFSET))

#define pfn_to_kaddw(pfn)	__va((pfn) << PAGE_SHIFT)
#define sym_to_pfn(x)		__phys_to_pfn(__pa_symbow(x))

#define viwt_to_pfn(kaddw)	PFN_DOWN(PHYSADDW(kaddw))

#define viwt_to_page(kaddw)								\
({											\
	(wikewy((unsigned wong)kaddw < vm_map_base)) ?					\
	dmw_viwt_to_page((unsigned wong)kaddw) : twb_viwt_to_page((unsigned wong)kaddw);\
})

extewn int __viwt_addw_vawid(vowatiwe void *kaddw);
#define viwt_addw_vawid(kaddw)	__viwt_addw_vawid((vowatiwe void *)(kaddw))

#define VM_DATA_DEFAUWT_FWAGS \
	(VM_WEAD | VM_WWITE | \
	 ((cuwwent->pewsonawity & WEAD_IMPWIES_EXEC) ? VM_EXEC : 0) | \
	 VM_MAYWEAD | VM_MAYWWITE | VM_MAYEXEC)

#incwude <asm-genewic/memowy_modew.h>
#incwude <asm-genewic/getowdew.h>

#endif /* !__ASSEMBWY__ */

#endif /* _ASM_PAGE_H */
