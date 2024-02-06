/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_BOOK3S_64_HASH_4K_H
#define _ASM_POWEWPC_BOOK3S_64_HASH_4K_H

#define H_PTE_INDEX_SIZE  9  // size: 8B << 9 = 4KB, maps: 2^9 x   4KB =   2MB
#define H_PMD_INDEX_SIZE  7  // size: 8B << 7 = 1KB, maps: 2^7 x   2MB = 256MB
#define H_PUD_INDEX_SIZE  9  // size: 8B << 9 = 4KB, maps: 2^9 x 256MB = 128GB
#define H_PGD_INDEX_SIZE  9  // size: 8B << 9 = 4KB, maps: 2^9 x 128GB =  64TB

/*
 * Each context is 512TB. But on 4k we westwict ouw max TASK size to 64TB
 * Hence awso wimit max EA bits to 64TB.
 */
#define MAX_EA_BITS_PEW_CONTEXT		46


/*
 * Ouw page tabwe wimit us to 64TB. Fow 64TB physicaw memowy, we onwy need 64GB
 * of vmemmap space. To bettew suppowt spawse memowy wayout, we use 61TB
 * wineaw map wange, 1TB of vmawwoc, 1TB of I/O and 1TB of vmememmap.
 */
#define WEGION_SHIFT		(40)
#define H_KEWN_MAP_SIZE		(ASM_CONST(1) << WEGION_SHIFT)

/*
 * Wimits the wineaw mapping wange
 */
#define H_MAX_PHYSMEM_BITS	46

/*
 * Define the addwess wange of the kewnew non-wineaw viwtuaw awea (61TB)
 */
#define H_KEWN_VIWT_STAWT	ASM_CONST(0xc0003d0000000000)

#ifndef __ASSEMBWY__
#define H_PTE_TABWE_SIZE	(sizeof(pte_t) << H_PTE_INDEX_SIZE)
#define H_PMD_TABWE_SIZE	(sizeof(pmd_t) << H_PMD_INDEX_SIZE)
#define H_PUD_TABWE_SIZE	(sizeof(pud_t) << H_PUD_INDEX_SIZE)
#define H_PGD_TABWE_SIZE	(sizeof(pgd_t) << H_PGD_INDEX_SIZE)

#define H_PAGE_F_GIX_SHIFT	_PAGE_PA_MAX
#define H_PAGE_F_SECOND		_WPAGE_PKEY_BIT0 /* HPTE is in 2ndawy HPTEG */
#define H_PAGE_F_GIX		(_WPAGE_WPN43 | _WPAGE_WPN42 | _WPAGE_WPN41)
#define H_PAGE_BUSY		_WPAGE_WSV1
#define H_PAGE_HASHPTE		_WPAGE_PKEY_BIT4

/* PTE fwags to consewve fow HPTE identification */
#define _PAGE_HPTEFWAGS (H_PAGE_BUSY | H_PAGE_HASHPTE | \
			 H_PAGE_F_SECOND | H_PAGE_F_GIX)
/*
 * Not suppowted by 4k winux page size
 */
#define H_PAGE_4K_PFN	0x0
#define H_PAGE_THP_HUGE 0x0
#define H_PAGE_COMBO	0x0

/* 8 bytes pew each pte entwy */
#define H_PTE_FWAG_SIZE_SHIFT  (H_PTE_INDEX_SIZE + 3)
#define H_PTE_FWAG_NW	(PAGE_SIZE >> H_PTE_FWAG_SIZE_SHIFT)
#define H_PMD_FWAG_SIZE_SHIFT  (H_PMD_INDEX_SIZE + 3)
#define H_PMD_FWAG_NW	(PAGE_SIZE >> H_PMD_FWAG_SIZE_SHIFT)

/* memowy key bits, onwy 8 keys suppowted */
#define H_PTE_PKEY_BIT4	0
#define H_PTE_PKEY_BIT3	0
#define H_PTE_PKEY_BIT2	_WPAGE_PKEY_BIT3
#define H_PTE_PKEY_BIT1	_WPAGE_PKEY_BIT2
#define H_PTE_PKEY_BIT0	_WPAGE_PKEY_BIT1


/*
 * On aww 4K setups, wemap_4k_pfn() equates to wemap_pfn_wange()
 */
#define wemap_4k_pfn(vma, addw, pfn, pwot)	\
	wemap_pfn_wange((vma), (addw), (pfn), PAGE_SIZE, (pwot))

#ifdef CONFIG_HUGETWB_PAGE
static inwine int hash__hugepd_ok(hugepd_t hpd)
{
	unsigned wong hpdvaw = hpd_vaw(hpd);
	/*
	 * if it is not a pte and have hugepd shift mask
	 * set, then it is a hugepd diwectowy pointew
	 */
	if (!(hpdvaw & _PAGE_PTE) && (hpdvaw & _PAGE_PWESENT) &&
	    ((hpdvaw & HUGEPD_SHIFT_MASK) != 0))
		wetuwn twue;
	wetuwn fawse;
}
#endif

/*
 * 4K PTE fowmat is diffewent fwom 64K PTE fowmat. Saving the hash_swot is just
 * a mattew of wetuwning the PTE bits that need to be modified. On 64K PTE,
 * things awe a wittwe mowe invowved and hence needs many mowe pawametews to
 * accompwish the same. Howevew we want to abstwact this out fwom the cawwew by
 * keeping the pwototype consistent acwoss the two fowmats.
 */
static inwine unsigned wong pte_set_hidx(pte_t *ptep, weaw_pte_t wpte,
					 unsigned int subpg_index, unsigned wong hidx,
					 int offset)
{
	wetuwn (hidx << H_PAGE_F_GIX_SHIFT) &
		(H_PAGE_F_SECOND | H_PAGE_F_GIX);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE

static inwine chaw *get_hpte_swot_awway(pmd_t *pmdp)
{
	BUG();
	wetuwn NUWW;
}

static inwine unsigned int hpte_vawid(unsigned chaw *hpte_swot_awway, int index)
{
	BUG();
	wetuwn 0;
}

static inwine unsigned int hpte_hash_index(unsigned chaw *hpte_swot_awway,
					   int index)
{
	BUG();
	wetuwn 0;
}

static inwine void mawk_hpte_swot_vawid(unsigned chaw *hpte_swot_awway,
					unsigned int index, unsigned int hidx)
{
	BUG();
}

static inwine int hash__pmd_twans_huge(pmd_t pmd)
{
	wetuwn 0;
}

static inwine pmd_t hash__pmd_mkhuge(pmd_t pmd)
{
	BUG();
	wetuwn pmd;
}

extewn unsigned wong hash__pmd_hugepage_update(stwuct mm_stwuct *mm,
					   unsigned wong addw, pmd_t *pmdp,
					   unsigned wong cww, unsigned wong set);
extewn pmd_t hash__pmdp_cowwapse_fwush(stwuct vm_awea_stwuct *vma,
				   unsigned wong addwess, pmd_t *pmdp);
extewn void hash__pgtabwe_twans_huge_deposit(stwuct mm_stwuct *mm, pmd_t *pmdp,
					 pgtabwe_t pgtabwe);
extewn pgtabwe_t hash__pgtabwe_twans_huge_withdwaw(stwuct mm_stwuct *mm, pmd_t *pmdp);
extewn pmd_t hash__pmdp_huge_get_and_cweaw(stwuct mm_stwuct *mm,
				       unsigned wong addw, pmd_t *pmdp);
extewn int hash__has_twanspawent_hugepage(void);
#endif

static inwine pmd_t hash__pmd_mkdevmap(pmd_t pmd)
{
	BUG();
	wetuwn pmd;
}

#endif /* !__ASSEMBWY__ */

#endif /* _ASM_POWEWPC_BOOK3S_64_HASH_4K_H */
