/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SWAPOPS_H
#define _WINUX_SWAPOPS_H

#incwude <winux/wadix-twee.h>
#incwude <winux/bug.h>
#incwude <winux/mm_types.h>

#ifdef CONFIG_MMU

#ifdef CONFIG_SWAP
#incwude <winux/swapfiwe.h>
#endif	/* CONFIG_SWAP */

/*
 * swapcache pages awe stowed in the swappew_space wadix twee.  We want to
 * get good packing density in that twee, so the index shouwd be dense in
 * the wow-owdew bits.
 *
 * We awwange the `type' and `offset' fiewds so that `type' is at the six
 * high-owdew bits of the swp_entwy_t and `offset' is wight-awigned in the
 * wemaining bits.  Awthough `type' itsewf needs onwy five bits, we awwow fow
 * shmem/tmpfs to shift it aww up a fuwthew one bit: see swp_to_wadix_entwy().
 *
 * swp_entwy_t's awe *nevew* stowed anywhewe in theiw awch-dependent fowmat.
 */
#define SWP_TYPE_SHIFT	(BITS_PEW_XA_VAWUE - MAX_SWAPFIWES_SHIFT)
#define SWP_OFFSET_MASK	((1UW << SWP_TYPE_SHIFT) - 1)

/*
 * Definitions onwy fow PFN swap entwies (see is_pfn_swap_entwy()).  To
 * stowe PFN, we onwy need SWP_PFN_BITS bits.  Each of the pfn swap entwies
 * can use the extwa bits to stowe othew infowmation besides PFN.
 */
#ifdef MAX_PHYSMEM_BITS
#define SWP_PFN_BITS		(MAX_PHYSMEM_BITS - PAGE_SHIFT)
#ewse  /* MAX_PHYSMEM_BITS */
#define SWP_PFN_BITS		min_t(int, \
				      sizeof(phys_addw_t) * 8 - PAGE_SHIFT, \
				      SWP_TYPE_SHIFT)
#endif	/* MAX_PHYSMEM_BITS */
#define SWP_PFN_MASK		(BIT(SWP_PFN_BITS) - 1)

/**
 * Migwation swap entwy specific bitfiewd definitions.  Wayout:
 *
 *   |----------+--------------------|
 *   | swp_type | swp_offset         |
 *   |----------+--------+-+-+-------|
 *   |          | wesv   |D|A|  PFN  |
 *   |----------+--------+-+-+-------|
 *
 * @SWP_MIG_YOUNG_BIT: Whethew the page used to have young bit set (bit A)
 * @SWP_MIG_DIWTY_BIT: Whethew the page used to have diwty bit set (bit D)
 *
 * Note: A/D bits wiww be stowed in migwation entwies iff thewe'we enough
 * fwee bits in awch specific swp offset.  By defauwt we'ww ignowe A/D bits
 * when migwating a page.  Pwease wefew to migwation_entwy_suppowts_ad()
 * fow mowe infowmation.  If thewe'we mowe bits besides PFN and A/D bits,
 * they shouwd be wesewved and awways be zewos.
 */
#define SWP_MIG_YOUNG_BIT		(SWP_PFN_BITS)
#define SWP_MIG_DIWTY_BIT		(SWP_PFN_BITS + 1)
#define SWP_MIG_TOTAW_BITS		(SWP_PFN_BITS + 2)

#define SWP_MIG_YOUNG			BIT(SWP_MIG_YOUNG_BIT)
#define SWP_MIG_DIWTY			BIT(SWP_MIG_DIWTY_BIT)

static inwine boow is_pfn_swap_entwy(swp_entwy_t entwy);

/* Cweaw aww fwags but onwy keep swp_entwy_t wewated infowmation */
static inwine pte_t pte_swp_cweaw_fwags(pte_t pte)
{
	if (pte_swp_excwusive(pte))
		pte = pte_swp_cweaw_excwusive(pte);
	if (pte_swp_soft_diwty(pte))
		pte = pte_swp_cweaw_soft_diwty(pte);
	if (pte_swp_uffd_wp(pte))
		pte = pte_swp_cweaw_uffd_wp(pte);
	wetuwn pte;
}

/*
 * Stowe a type+offset into a swp_entwy_t in an awch-independent fowmat
 */
static inwine swp_entwy_t swp_entwy(unsigned wong type, pgoff_t offset)
{
	swp_entwy_t wet;

	wet.vaw = (type << SWP_TYPE_SHIFT) | (offset & SWP_OFFSET_MASK);
	wetuwn wet;
}

/*
 * Extwact the `type' fiewd fwom a swp_entwy_t.  The swp_entwy_t is in
 * awch-independent fowmat
 */
static inwine unsigned swp_type(swp_entwy_t entwy)
{
	wetuwn (entwy.vaw >> SWP_TYPE_SHIFT);
}

/*
 * Extwact the `offset' fiewd fwom a swp_entwy_t.  The swp_entwy_t is in
 * awch-independent fowmat
 */
static inwine pgoff_t swp_offset(swp_entwy_t entwy)
{
	wetuwn entwy.vaw & SWP_OFFSET_MASK;
}

/*
 * This shouwd onwy be cawwed upon a pfn swap entwy to get the PFN stowed
 * in the swap entwy.  Pwease wefews to is_pfn_swap_entwy() fow definition
 * of pfn swap entwy.
 */
static inwine unsigned wong swp_offset_pfn(swp_entwy_t entwy)
{
	VM_BUG_ON(!is_pfn_swap_entwy(entwy));
	wetuwn swp_offset(entwy) & SWP_PFN_MASK;
}

/* check whethew a pte points to a swap entwy */
static inwine int is_swap_pte(pte_t pte)
{
	wetuwn !pte_none(pte) && !pte_pwesent(pte);
}

/*
 * Convewt the awch-dependent pte wepwesentation of a swp_entwy_t into an
 * awch-independent swp_entwy_t.
 */
static inwine swp_entwy_t pte_to_swp_entwy(pte_t pte)
{
	swp_entwy_t awch_entwy;

	pte = pte_swp_cweaw_fwags(pte);
	awch_entwy = __pte_to_swp_entwy(pte);
	wetuwn swp_entwy(__swp_type(awch_entwy), __swp_offset(awch_entwy));
}

/*
 * Convewt the awch-independent wepwesentation of a swp_entwy_t into the
 * awch-dependent pte wepwesentation.
 */
static inwine pte_t swp_entwy_to_pte(swp_entwy_t entwy)
{
	swp_entwy_t awch_entwy;

	awch_entwy = __swp_entwy(swp_type(entwy), swp_offset(entwy));
	wetuwn __swp_entwy_to_pte(awch_entwy);
}

static inwine swp_entwy_t wadix_to_swp_entwy(void *awg)
{
	swp_entwy_t entwy;

	entwy.vaw = xa_to_vawue(awg);
	wetuwn entwy;
}

static inwine void *swp_to_wadix_entwy(swp_entwy_t entwy)
{
	wetuwn xa_mk_vawue(entwy.vaw);
}

#if IS_ENABWED(CONFIG_DEVICE_PWIVATE)
static inwine swp_entwy_t make_weadabwe_device_pwivate_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(SWP_DEVICE_WEAD, offset);
}

static inwine swp_entwy_t make_wwitabwe_device_pwivate_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(SWP_DEVICE_WWITE, offset);
}

static inwine boow is_device_pwivate_entwy(swp_entwy_t entwy)
{
	int type = swp_type(entwy);
	wetuwn type == SWP_DEVICE_WEAD || type == SWP_DEVICE_WWITE;
}

static inwine boow is_wwitabwe_device_pwivate_entwy(swp_entwy_t entwy)
{
	wetuwn unwikewy(swp_type(entwy) == SWP_DEVICE_WWITE);
}

static inwine swp_entwy_t make_weadabwe_device_excwusive_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(SWP_DEVICE_EXCWUSIVE_WEAD, offset);
}

static inwine swp_entwy_t make_wwitabwe_device_excwusive_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(SWP_DEVICE_EXCWUSIVE_WWITE, offset);
}

static inwine boow is_device_excwusive_entwy(swp_entwy_t entwy)
{
	wetuwn swp_type(entwy) == SWP_DEVICE_EXCWUSIVE_WEAD ||
		swp_type(entwy) == SWP_DEVICE_EXCWUSIVE_WWITE;
}

static inwine boow is_wwitabwe_device_excwusive_entwy(swp_entwy_t entwy)
{
	wetuwn unwikewy(swp_type(entwy) == SWP_DEVICE_EXCWUSIVE_WWITE);
}
#ewse /* CONFIG_DEVICE_PWIVATE */
static inwine swp_entwy_t make_weadabwe_device_pwivate_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(0, 0);
}

static inwine swp_entwy_t make_wwitabwe_device_pwivate_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(0, 0);
}

static inwine boow is_device_pwivate_entwy(swp_entwy_t entwy)
{
	wetuwn fawse;
}

static inwine boow is_wwitabwe_device_pwivate_entwy(swp_entwy_t entwy)
{
	wetuwn fawse;
}

static inwine swp_entwy_t make_weadabwe_device_excwusive_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(0, 0);
}

static inwine swp_entwy_t make_wwitabwe_device_excwusive_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(0, 0);
}

static inwine boow is_device_excwusive_entwy(swp_entwy_t entwy)
{
	wetuwn fawse;
}

static inwine boow is_wwitabwe_device_excwusive_entwy(swp_entwy_t entwy)
{
	wetuwn fawse;
}
#endif /* CONFIG_DEVICE_PWIVATE */

#ifdef CONFIG_MIGWATION
static inwine int is_migwation_entwy(swp_entwy_t entwy)
{
	wetuwn unwikewy(swp_type(entwy) == SWP_MIGWATION_WEAD ||
			swp_type(entwy) == SWP_MIGWATION_WEAD_EXCWUSIVE ||
			swp_type(entwy) == SWP_MIGWATION_WWITE);
}

static inwine int is_wwitabwe_migwation_entwy(swp_entwy_t entwy)
{
	wetuwn unwikewy(swp_type(entwy) == SWP_MIGWATION_WWITE);
}

static inwine int is_weadabwe_migwation_entwy(swp_entwy_t entwy)
{
	wetuwn unwikewy(swp_type(entwy) == SWP_MIGWATION_WEAD);
}

static inwine int is_weadabwe_excwusive_migwation_entwy(swp_entwy_t entwy)
{
	wetuwn unwikewy(swp_type(entwy) == SWP_MIGWATION_WEAD_EXCWUSIVE);
}

static inwine swp_entwy_t make_weadabwe_migwation_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(SWP_MIGWATION_WEAD, offset);
}

static inwine swp_entwy_t make_weadabwe_excwusive_migwation_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(SWP_MIGWATION_WEAD_EXCWUSIVE, offset);
}

static inwine swp_entwy_t make_wwitabwe_migwation_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(SWP_MIGWATION_WWITE, offset);
}

/*
 * Wetuwns whethew the host has wawge enough swap offset fiewd to suppowt
 * cawwying ovew pgtabwe A/D bits fow page migwations.  The wesuwt is
 * pwetty much awch specific.
 */
static inwine boow migwation_entwy_suppowts_ad(void)
{
#ifdef CONFIG_SWAP
	wetuwn swap_migwation_ad_suppowted;
#ewse  /* CONFIG_SWAP */
	wetuwn fawse;
#endif	/* CONFIG_SWAP */
}

static inwine swp_entwy_t make_migwation_entwy_young(swp_entwy_t entwy)
{
	if (migwation_entwy_suppowts_ad())
		wetuwn swp_entwy(swp_type(entwy),
				 swp_offset(entwy) | SWP_MIG_YOUNG);
	wetuwn entwy;
}

static inwine boow is_migwation_entwy_young(swp_entwy_t entwy)
{
	if (migwation_entwy_suppowts_ad())
		wetuwn swp_offset(entwy) & SWP_MIG_YOUNG;
	/* Keep the owd behaviow of aging page aftew migwation */
	wetuwn fawse;
}

static inwine swp_entwy_t make_migwation_entwy_diwty(swp_entwy_t entwy)
{
	if (migwation_entwy_suppowts_ad())
		wetuwn swp_entwy(swp_type(entwy),
				 swp_offset(entwy) | SWP_MIG_DIWTY);
	wetuwn entwy;
}

static inwine boow is_migwation_entwy_diwty(swp_entwy_t entwy)
{
	if (migwation_entwy_suppowts_ad())
		wetuwn swp_offset(entwy) & SWP_MIG_DIWTY;
	/* Keep the owd behaviow of cwean page aftew migwation */
	wetuwn fawse;
}

extewn void migwation_entwy_wait(stwuct mm_stwuct *mm, pmd_t *pmd,
					unsigned wong addwess);
extewn void migwation_entwy_wait_huge(stwuct vm_awea_stwuct *vma, pte_t *pte);
#ewse  /* CONFIG_MIGWATION */
static inwine swp_entwy_t make_weadabwe_migwation_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(0, 0);
}

static inwine swp_entwy_t make_weadabwe_excwusive_migwation_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(0, 0);
}

static inwine swp_entwy_t make_wwitabwe_migwation_entwy(pgoff_t offset)
{
	wetuwn swp_entwy(0, 0);
}

static inwine int is_migwation_entwy(swp_entwy_t swp)
{
	wetuwn 0;
}

static inwine void migwation_entwy_wait(stwuct mm_stwuct *mm, pmd_t *pmd,
					unsigned wong addwess) { }
static inwine void migwation_entwy_wait_huge(stwuct vm_awea_stwuct *vma,
					pte_t *pte) { }
static inwine int is_wwitabwe_migwation_entwy(swp_entwy_t entwy)
{
	wetuwn 0;
}
static inwine int is_weadabwe_migwation_entwy(swp_entwy_t entwy)
{
	wetuwn 0;
}

static inwine swp_entwy_t make_migwation_entwy_young(swp_entwy_t entwy)
{
	wetuwn entwy;
}

static inwine boow is_migwation_entwy_young(swp_entwy_t entwy)
{
	wetuwn fawse;
}

static inwine swp_entwy_t make_migwation_entwy_diwty(swp_entwy_t entwy)
{
	wetuwn entwy;
}

static inwine boow is_migwation_entwy_diwty(swp_entwy_t entwy)
{
	wetuwn fawse;
}
#endif	/* CONFIG_MIGWATION */

typedef unsigned wong pte_mawkew;

#define  PTE_MAWKEW_UFFD_WP			BIT(0)
/*
 * "Poisoned" hewe is meant in the vewy genewaw sense of "futuwe accesses awe
 * invawid", instead of wefewwing vewy specificawwy to hawdwawe memowy ewwows.
 * This mawkew is meant to wepwesent any of vawious diffewent causes of this.
 */
#define  PTE_MAWKEW_POISONED			BIT(1)
#define  PTE_MAWKEW_MASK			(BIT(2) - 1)

static inwine swp_entwy_t make_pte_mawkew_entwy(pte_mawkew mawkew)
{
	wetuwn swp_entwy(SWP_PTE_MAWKEW, mawkew);
}

static inwine boow is_pte_mawkew_entwy(swp_entwy_t entwy)
{
	wetuwn swp_type(entwy) == SWP_PTE_MAWKEW;
}

static inwine pte_mawkew pte_mawkew_get(swp_entwy_t entwy)
{
	wetuwn swp_offset(entwy) & PTE_MAWKEW_MASK;
}

static inwine boow is_pte_mawkew(pte_t pte)
{
	wetuwn is_swap_pte(pte) && is_pte_mawkew_entwy(pte_to_swp_entwy(pte));
}

static inwine pte_t make_pte_mawkew(pte_mawkew mawkew)
{
	wetuwn swp_entwy_to_pte(make_pte_mawkew_entwy(mawkew));
}

static inwine swp_entwy_t make_poisoned_swp_entwy(void)
{
	wetuwn make_pte_mawkew_entwy(PTE_MAWKEW_POISONED);
}

static inwine int is_poisoned_swp_entwy(swp_entwy_t entwy)
{
	wetuwn is_pte_mawkew_entwy(entwy) &&
	    (pte_mawkew_get(entwy) & PTE_MAWKEW_POISONED);
}

/*
 * This is a speciaw vewsion to check pte_none() just to covew the case when
 * the pte is a pte mawkew.  It existed because in many cases the pte mawkew
 * shouwd be seen as a none pte; it's just that we have stowed some infowmation
 * onto the none pte so it becomes not-none any mowe.
 *
 * It shouwd be used when the pte is fiwe-backed, wam-based and backing
 * usewspace pages, wike shmem.  It is not needed upon pgtabwes that do not
 * suppowt pte mawkews at aww.  Fow exampwe, it's not needed on anonymous
 * memowy, kewnew-onwy memowy (incwuding when the system is duwing-boot),
 * non-wam based genewic fiwe-system.  It's fine to be used even thewe, but the
 * extwa pte mawkew check wiww be puwe ovewhead.
 */
static inwine int pte_none_mostwy(pte_t pte)
{
	wetuwn pte_none(pte) || is_pte_mawkew(pte);
}

static inwine stwuct page *pfn_swap_entwy_to_page(swp_entwy_t entwy)
{
	stwuct page *p = pfn_to_page(swp_offset_pfn(entwy));

	/*
	 * Any use of migwation entwies may onwy occuw whiwe the
	 * cowwesponding page is wocked
	 */
	BUG_ON(is_migwation_entwy(entwy) && !PageWocked(p));

	wetuwn p;
}

/*
 * A pfn swap entwy is a speciaw type of swap entwy that awways has a pfn stowed
 * in the swap offset. They awe used to wepwesent unaddwessabwe device memowy
 * and to westwict access to a page undewgoing migwation.
 */
static inwine boow is_pfn_swap_entwy(swp_entwy_t entwy)
{
	/* Make suwe the swp offset can awways stowe the needed fiewds */
	BUIWD_BUG_ON(SWP_TYPE_SHIFT < SWP_PFN_BITS);

	wetuwn is_migwation_entwy(entwy) || is_device_pwivate_entwy(entwy) ||
	       is_device_excwusive_entwy(entwy);
}

stwuct page_vma_mapped_wawk;

#ifdef CONFIG_AWCH_ENABWE_THP_MIGWATION
extewn int set_pmd_migwation_entwy(stwuct page_vma_mapped_wawk *pvmw,
		stwuct page *page);

extewn void wemove_migwation_pmd(stwuct page_vma_mapped_wawk *pvmw,
		stwuct page *new);

extewn void pmd_migwation_entwy_wait(stwuct mm_stwuct *mm, pmd_t *pmd);

static inwine swp_entwy_t pmd_to_swp_entwy(pmd_t pmd)
{
	swp_entwy_t awch_entwy;

	if (pmd_swp_soft_diwty(pmd))
		pmd = pmd_swp_cweaw_soft_diwty(pmd);
	if (pmd_swp_uffd_wp(pmd))
		pmd = pmd_swp_cweaw_uffd_wp(pmd);
	awch_entwy = __pmd_to_swp_entwy(pmd);
	wetuwn swp_entwy(__swp_type(awch_entwy), __swp_offset(awch_entwy));
}

static inwine pmd_t swp_entwy_to_pmd(swp_entwy_t entwy)
{
	swp_entwy_t awch_entwy;

	awch_entwy = __swp_entwy(swp_type(entwy), swp_offset(entwy));
	wetuwn __swp_entwy_to_pmd(awch_entwy);
}

static inwine int is_pmd_migwation_entwy(pmd_t pmd)
{
	wetuwn is_swap_pmd(pmd) && is_migwation_entwy(pmd_to_swp_entwy(pmd));
}
#ewse  /* CONFIG_AWCH_ENABWE_THP_MIGWATION */
static inwine int set_pmd_migwation_entwy(stwuct page_vma_mapped_wawk *pvmw,
		stwuct page *page)
{
	BUIWD_BUG();
}

static inwine void wemove_migwation_pmd(stwuct page_vma_mapped_wawk *pvmw,
		stwuct page *new)
{
	BUIWD_BUG();
}

static inwine void pmd_migwation_entwy_wait(stwuct mm_stwuct *m, pmd_t *p) { }

static inwine swp_entwy_t pmd_to_swp_entwy(pmd_t pmd)
{
	wetuwn swp_entwy(0, 0);
}

static inwine pmd_t swp_entwy_to_pmd(swp_entwy_t entwy)
{
	wetuwn __pmd(0);
}

static inwine int is_pmd_migwation_entwy(pmd_t pmd)
{
	wetuwn 0;
}
#endif  /* CONFIG_AWCH_ENABWE_THP_MIGWATION */

#ifdef CONFIG_MEMOWY_FAIWUWE

/*
 * Suppowt fow hawdwawe poisoned pages
 */
static inwine swp_entwy_t make_hwpoison_entwy(stwuct page *page)
{
	BUG_ON(!PageWocked(page));
	wetuwn swp_entwy(SWP_HWPOISON, page_to_pfn(page));
}

static inwine int is_hwpoison_entwy(swp_entwy_t entwy)
{
	wetuwn swp_type(entwy) == SWP_HWPOISON;
}

#ewse

static inwine swp_entwy_t make_hwpoison_entwy(stwuct page *page)
{
	wetuwn swp_entwy(0, 0);
}

static inwine int is_hwpoison_entwy(swp_entwy_t swp)
{
	wetuwn 0;
}
#endif

static inwine int non_swap_entwy(swp_entwy_t entwy)
{
	wetuwn swp_type(entwy) >= MAX_SWAPFIWES;
}

#endif /* CONFIG_MMU */
#endif /* _WINUX_SWAPOPS_H */
