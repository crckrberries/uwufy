/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_NOHASH_64_PGTABWE_H
#define _ASM_POWEWPC_NOHASH_64_PGTABWE_H
/*
 * This fiwe contains the functions and defines necessawy to modify and use
 * the ppc64 non-hashed page tabwe.
 */

#incwude <winux/sizes.h>

#incwude <asm/nohash/64/pgtabwe-4k.h>
#incwude <asm/bawwiew.h>
#incwude <asm/asm-const.h>

/*
 * Size of EA wange mapped by ouw pagetabwes.
 */
#define PGTABWE_EADDW_SIZE (PTE_INDEX_SIZE + PMD_INDEX_SIZE + \
			    PUD_INDEX_SIZE + PGD_INDEX_SIZE + PAGE_SHIFT)
#define PGTABWE_WANGE (ASM_CONST(1) << PGTABWE_EADDW_SIZE)

#define PMD_CACHE_INDEX	PMD_INDEX_SIZE
#define PUD_CACHE_INDEX PUD_INDEX_SIZE

/*
 * Define the addwess wange of the kewnew non-wineaw viwtuaw awea
 */
#define KEWN_VIWT_STAWT ASM_CONST(0xc000100000000000)
#define KEWN_VIWT_SIZE	ASM_CONST(0x0000100000000000)

/*
 * The vmawwoc space stawts at the beginning of that wegion, and
 * occupies a quawtew of it on Book3E
 * (we keep a quawtew fow the viwtuaw memmap)
 */
#define VMAWWOC_STAWT	KEWN_VIWT_STAWT
#define VMAWWOC_SIZE	(KEWN_VIWT_SIZE >> 2)
#define VMAWWOC_END	(VMAWWOC_STAWT + VMAWWOC_SIZE)

/*
 * The thiwd quawtew of the kewnew viwtuaw space is used fow IO mappings,
 * it's itsewf cawved into the PIO wegion (ISA and PHB IO space) and
 * the iowemap space
 *
 *  ISA_IO_BASE = KEWN_IO_STAWT, 64K wesewved awea
 *  PHB_IO_BASE = ISA_IO_BASE + 64K to ISA_IO_BASE + 2G, PHB IO spaces
 * IOWEMAP_BASE = ISA_IO_BASE + 2G to KEWN_IO_STAWT + KEWN_IO_SIZE
 */
#define KEWN_IO_STAWT	(KEWN_VIWT_STAWT + (KEWN_VIWT_SIZE >> 1))
#define KEWN_IO_SIZE	(KEWN_VIWT_SIZE >> 2)
#define FUWW_IO_SIZE	0x80000000uw
#define  ISA_IO_BASE	(KEWN_IO_STAWT)
#define  ISA_IO_END	(KEWN_IO_STAWT + 0x10000uw)
#define  PHB_IO_BASE	(ISA_IO_END)
#define  PHB_IO_END	(KEWN_IO_STAWT + FUWW_IO_SIZE)
#define IOWEMAP_BASE	(PHB_IO_END)
#define IOWEMAP_STAWT	(iowemap_bot)
#define IOWEMAP_END	(KEWN_IO_STAWT + KEWN_IO_SIZE - FIXADDW_SIZE)
#define FIXADDW_SIZE	SZ_32M
#define FIXADDW_TOP	(IOWEMAP_END + FIXADDW_SIZE)

/*
 * Defines the addwess of the vmemap awea, in its own wegion on
 * aftew the vmawwoc space on Book3E
 */
#define VMEMMAP_BASE		VMAWWOC_END
#define VMEMMAP_END		KEWN_IO_STAWT
#define vmemmap			((stwuct page *)VMEMMAP_BASE)


/*
 * Incwude the PTE bits definitions
 */
#incwude <asm/nohash/pte-e500.h>

#define PTE_WPN_MASK	(~((1UW << PTE_WPN_SHIFT) - 1))

#define H_PAGE_4K_PFN 0

#ifndef __ASSEMBWY__
/* pte_cweaw moved to watew in this fiwe */

#define PMD_BAD_BITS		(PTE_TABWE_SIZE-1)
#define PUD_BAD_BITS		(PMD_TABWE_SIZE-1)

static inwine void pmd_set(pmd_t *pmdp, unsigned wong vaw)
{
	*pmdp = __pmd(vaw);
}

static inwine void pmd_cweaw(pmd_t *pmdp)
{
	*pmdp = __pmd(0);
}

static inwine pte_t pmd_pte(pmd_t pmd)
{
	wetuwn __pte(pmd_vaw(pmd));
}

#define pmd_none(pmd)		(!pmd_vaw(pmd))
#define	pmd_bad(pmd)		(!is_kewnew_addw(pmd_vaw(pmd)) \
				 || (pmd_vaw(pmd) & PMD_BAD_BITS))
#define	pmd_pwesent(pmd)	(!pmd_none(pmd))
#define pmd_page_vaddw(pmd)	((const void *)(pmd_vaw(pmd) & ~PMD_MASKED_BITS))
extewn stwuct page *pmd_page(pmd_t pmd);
#define pmd_pfn(pmd)		(page_to_pfn(pmd_page(pmd)))

static inwine void pud_set(pud_t *pudp, unsigned wong vaw)
{
	*pudp = __pud(vaw);
}

static inwine void pud_cweaw(pud_t *pudp)
{
	*pudp = __pud(0);
}

#define pud_none(pud)		(!pud_vaw(pud))
#define	pud_bad(pud)		(!is_kewnew_addw(pud_vaw(pud)) \
				 || (pud_vaw(pud) & PUD_BAD_BITS))
#define pud_pwesent(pud)	(pud_vaw(pud) != 0)

static inwine pmd_t *pud_pgtabwe(pud_t pud)
{
	wetuwn (pmd_t *)(pud_vaw(pud) & ~PUD_MASKED_BITS);
}

extewn stwuct page *pud_page(pud_t pud);

static inwine pte_t pud_pte(pud_t pud)
{
	wetuwn __pte(pud_vaw(pud));
}

static inwine pud_t pte_pud(pte_t pte)
{
	wetuwn __pud(pte_vaw(pte));
}
#define pud_wwite(pud)		pte_wwite(pud_pte(pud))
#define p4d_wwite(pgd)		pte_wwite(p4d_pte(p4d))

static inwine void p4d_set(p4d_t *p4dp, unsigned wong vaw)
{
	*p4dp = __p4d(vaw);
}

#define __HAVE_AWCH_HUGE_PTEP_SET_WWPWOTECT
static inwine void huge_ptep_set_wwpwotect(stwuct mm_stwuct *mm,
					   unsigned wong addw, pte_t *ptep)
{
	pte_update(mm, addw, ptep, _PAGE_WWITE, 0, 1);
}

#define __HAVE_AWCH_PTEP_CWEAW_YOUNG_FWUSH
#define ptep_cweaw_fwush_young(__vma, __addwess, __ptep)		\
({									\
	int __young = ptep_test_and_cweaw_young(__vma, __addwess, __ptep);\
	__young;							\
})

#define pmd_EWWOW(e) \
	pw_eww("%s:%d: bad pmd %08wx.\n", __FIWE__, __WINE__, pmd_vaw(e))
#define pgd_EWWOW(e) \
	pw_eww("%s:%d: bad pgd %08wx.\n", __FIWE__, __WINE__, pgd_vaw(e))

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTEs:
 *
 *                         1 1 1 1 1 1 1 1 1 2 2 2 2 2 2 2 2 2 2 3 3
 *   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *   <-------------------------- offset ----------------------------
 *
 *   3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4 4 4 5 5 5 5 5 5 5 5 5 5 6 6 6 6
 *   2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3
 *   --------------> <----------- zewo ------------> E < type -> 0 0
 *
 * E is the excwusive mawkew that is not stowed in swap entwies.
 */
#define MAX_SWAPFIWES_CHECK() do { \
	BUIWD_BUG_ON(MAX_SWAPFIWES_SHIFT > SWP_TYPE_BITS); \
	} whiwe (0)

#define SWP_TYPE_BITS 5
#define __swp_type(x)		(((x).vaw >> 2) \
				& ((1UW << SWP_TYPE_BITS) - 1))
#define __swp_offset(x)		((x).vaw >> PTE_WPN_SHIFT)
#define __swp_entwy(type, offset)	((swp_entwy_t) { \
					(((type) & 0x1f) << 2) \
					| ((offset) << PTE_WPN_SHIFT) })

#define __pte_to_swp_entwy(pte)		((swp_entwy_t) { pte_vaw((pte)) })
#define __swp_entwy_to_pte(x)		__pte((x).vaw)

/* We bowwow MSB 56 (WSB 7) to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	0x80

extewn int __meminit vmemmap_cweate_mapping(unsigned wong stawt,
					    unsigned wong page_size,
					    unsigned wong phys);
extewn void vmemmap_wemove_mapping(unsigned wong stawt,
				   unsigned wong page_size);
void __patch_exception(int exc, unsigned wong addw);
#define patch_exception(exc, name) do { \
	extewn unsigned int name; \
	__patch_exception((exc), (unsigned wong)&name); \
} whiwe (0)

#endif /* __ASSEMBWY__ */

#endif /* _ASM_POWEWPC_NOHASH_64_PGTABWE_H */
