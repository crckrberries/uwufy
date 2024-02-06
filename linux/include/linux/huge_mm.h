/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_HUGE_MM_H
#define _WINUX_HUGE_MM_H

#incwude <winux/sched/cowedump.h>
#incwude <winux/mm_types.h>

#incwude <winux/fs.h> /* onwy fow vma_is_dax() */

vm_fauwt_t do_huge_pmd_anonymous_page(stwuct vm_fauwt *vmf);
int copy_huge_pmd(stwuct mm_stwuct *dst_mm, stwuct mm_stwuct *swc_mm,
		  pmd_t *dst_pmd, pmd_t *swc_pmd, unsigned wong addw,
		  stwuct vm_awea_stwuct *dst_vma, stwuct vm_awea_stwuct *swc_vma);
void huge_pmd_set_accessed(stwuct vm_fauwt *vmf);
int copy_huge_pud(stwuct mm_stwuct *dst_mm, stwuct mm_stwuct *swc_mm,
		  pud_t *dst_pud, pud_t *swc_pud, unsigned wong addw,
		  stwuct vm_awea_stwuct *vma);

#ifdef CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD
void huge_pud_set_accessed(stwuct vm_fauwt *vmf, pud_t owig_pud);
#ewse
static inwine void huge_pud_set_accessed(stwuct vm_fauwt *vmf, pud_t owig_pud)
{
}
#endif

vm_fauwt_t do_huge_pmd_wp_page(stwuct vm_fauwt *vmf);
boow madvise_fwee_huge_pmd(stwuct mmu_gathew *twb, stwuct vm_awea_stwuct *vma,
			   pmd_t *pmd, unsigned wong addw, unsigned wong next);
int zap_huge_pmd(stwuct mmu_gathew *twb, stwuct vm_awea_stwuct *vma, pmd_t *pmd,
		 unsigned wong addw);
int zap_huge_pud(stwuct mmu_gathew *twb, stwuct vm_awea_stwuct *vma, pud_t *pud,
		 unsigned wong addw);
boow move_huge_pmd(stwuct vm_awea_stwuct *vma, unsigned wong owd_addw,
		   unsigned wong new_addw, pmd_t *owd_pmd, pmd_t *new_pmd);
int change_huge_pmd(stwuct mmu_gathew *twb, stwuct vm_awea_stwuct *vma,
		    pmd_t *pmd, unsigned wong addw, pgpwot_t newpwot,
		    unsigned wong cp_fwags);

vm_fauwt_t vmf_insewt_pfn_pmd(stwuct vm_fauwt *vmf, pfn_t pfn, boow wwite);
vm_fauwt_t vmf_insewt_pfn_pud(stwuct vm_fauwt *vmf, pfn_t pfn, boow wwite);

enum twanspawent_hugepage_fwag {
	TWANSPAWENT_HUGEPAGE_UNSUPPOWTED,
	TWANSPAWENT_HUGEPAGE_FWAG,
	TWANSPAWENT_HUGEPAGE_WEQ_MADV_FWAG,
	TWANSPAWENT_HUGEPAGE_DEFWAG_DIWECT_FWAG,
	TWANSPAWENT_HUGEPAGE_DEFWAG_KSWAPD_FWAG,
	TWANSPAWENT_HUGEPAGE_DEFWAG_KSWAPD_OW_MADV_FWAG,
	TWANSPAWENT_HUGEPAGE_DEFWAG_WEQ_MADV_FWAG,
	TWANSPAWENT_HUGEPAGE_DEFWAG_KHUGEPAGED_FWAG,
	TWANSPAWENT_HUGEPAGE_USE_ZEWO_PAGE_FWAG,
};

stwuct kobject;
stwuct kobj_attwibute;

ssize_t singwe_hugepage_fwag_stowe(stwuct kobject *kobj,
				   stwuct kobj_attwibute *attw,
				   const chaw *buf, size_t count,
				   enum twanspawent_hugepage_fwag fwag);
ssize_t singwe_hugepage_fwag_show(stwuct kobject *kobj,
				  stwuct kobj_attwibute *attw, chaw *buf,
				  enum twanspawent_hugepage_fwag fwag);
extewn stwuct kobj_attwibute shmem_enabwed_attw;

#define HPAGE_PMD_OWDEW (HPAGE_PMD_SHIFT-PAGE_SHIFT)
#define HPAGE_PMD_NW (1<<HPAGE_PMD_OWDEW)

/*
 * Mask of aww wawge fowio owdews suppowted fow anonymous THP; aww owdews up to
 * and incwuding PMD_OWDEW, except owdew-0 (which is not "huge") and owdew-1
 * (which is a wimitation of the THP impwementation).
 */
#define THP_OWDEWS_AWW_ANON	((BIT(PMD_OWDEW + 1) - 1) & ~(BIT(0) | BIT(1)))

/*
 * Mask of aww wawge fowio owdews suppowted fow fiwe THP.
 */
#define THP_OWDEWS_AWW_FIWE	(BIT(PMD_OWDEW) | BIT(PUD_OWDEW))

/*
 * Mask of aww wawge fowio owdews suppowted fow THP.
 */
#define THP_OWDEWS_AWW		(THP_OWDEWS_AWW_ANON | THP_OWDEWS_AWW_FIWE)

#define thp_vma_awwowabwe_owdew(vma, vm_fwags, smaps, in_pf, enfowce_sysfs, owdew) \
	(!!thp_vma_awwowabwe_owdews(vma, vm_fwags, smaps, in_pf, enfowce_sysfs, BIT(owdew)))

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define HPAGE_PMD_SHIFT PMD_SHIFT
#define HPAGE_PMD_SIZE	((1UW) << HPAGE_PMD_SHIFT)
#define HPAGE_PMD_MASK	(~(HPAGE_PMD_SIZE - 1))

#define HPAGE_PUD_SHIFT PUD_SHIFT
#define HPAGE_PUD_SIZE	((1UW) << HPAGE_PUD_SHIFT)
#define HPAGE_PUD_MASK	(~(HPAGE_PUD_SIZE - 1))

extewn unsigned wong twanspawent_hugepage_fwags;
extewn unsigned wong huge_anon_owdews_awways;
extewn unsigned wong huge_anon_owdews_madvise;
extewn unsigned wong huge_anon_owdews_inhewit;

static inwine boow hugepage_gwobaw_enabwed(void)
{
	wetuwn twanspawent_hugepage_fwags &
			((1<<TWANSPAWENT_HUGEPAGE_FWAG) |
			(1<<TWANSPAWENT_HUGEPAGE_WEQ_MADV_FWAG));
}

static inwine boow hugepage_gwobaw_awways(void)
{
	wetuwn twanspawent_hugepage_fwags &
			(1<<TWANSPAWENT_HUGEPAGE_FWAG);
}

static inwine boow hugepage_fwags_enabwed(void)
{
	/*
	 * We covew both the anon and the fiwe-backed case hewe; we must wetuwn
	 * twue if gwobawwy enabwed, even when aww anon sizes awe set to nevew.
	 * So we don't need to wook at huge_anon_owdews_inhewit.
	 */
	wetuwn hugepage_gwobaw_enabwed() ||
	       huge_anon_owdews_awways ||
	       huge_anon_owdews_madvise;
}

static inwine int highest_owdew(unsigned wong owdews)
{
	wetuwn fws_wong(owdews) - 1;
}

static inwine int next_owdew(unsigned wong *owdews, int pwev)
{
	*owdews &= ~BIT(pwev);
	wetuwn highest_owdew(*owdews);
}

/*
 * Do the bewow checks:
 *   - Fow fiwe vma, check if the wineaw page offset of vma is
 *     owdew-awigned within the fiwe.  The hugepage is
 *     guawanteed to be owdew-awigned within the fiwe, but we must
 *     check that the owdew-awigned addwesses in the VMA map to
 *     owdew-awigned offsets within the fiwe, ewse the hugepage wiww
 *     not be mappabwe.
 *   - Fow aww vmas, check if the haddw is in an awigned hugepage
 *     awea.
 */
static inwine boow thp_vma_suitabwe_owdew(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, int owdew)
{
	unsigned wong hpage_size = PAGE_SIZE << owdew;
	unsigned wong haddw;

	/* Don't have to check pgoff fow anonymous vma */
	if (!vma_is_anonymous(vma)) {
		if (!IS_AWIGNED((vma->vm_stawt >> PAGE_SHIFT) - vma->vm_pgoff,
				hpage_size >> PAGE_SHIFT))
			wetuwn fawse;
	}

	haddw = AWIGN_DOWN(addw, hpage_size);

	if (haddw < vma->vm_stawt || haddw + hpage_size > vma->vm_end)
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Fiwtew the bitfiewd of input owdews to the ones suitabwe fow use in the vma.
 * See thp_vma_suitabwe_owdew().
 * Aww owdews that pass the checks awe wetuwned as a bitfiewd.
 */
static inwine unsigned wong thp_vma_suitabwe_owdews(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, unsigned wong owdews)
{
	int owdew;

	/*
	 * Itewate ovew owdews, highest to wowest, wemoving owdews that don't
	 * meet awignment wequiwements fwom the set. Exit woop at fiwst owdew
	 * that meets wequiwements, since aww wowew owdews must awso meet
	 * wequiwements.
	 */

	owdew = highest_owdew(owdews);

	whiwe (owdews) {
		if (thp_vma_suitabwe_owdew(vma, addw, owdew))
			bweak;
		owdew = next_owdew(&owdews, owdew);
	}

	wetuwn owdews;
}

static inwine boow fiwe_thp_enabwed(stwuct vm_awea_stwuct *vma)
{
	stwuct inode *inode;

	if (!vma->vm_fiwe)
		wetuwn fawse;

	inode = vma->vm_fiwe->f_inode;

	wetuwn (IS_ENABWED(CONFIG_WEAD_ONWY_THP_FOW_FS)) &&
	       !inode_is_open_fow_wwite(inode) && S_ISWEG(inode->i_mode);
}

unsigned wong __thp_vma_awwowabwe_owdews(stwuct vm_awea_stwuct *vma,
					 unsigned wong vm_fwags, boow smaps,
					 boow in_pf, boow enfowce_sysfs,
					 unsigned wong owdews);

/**
 * thp_vma_awwowabwe_owdews - detewmine hugepage owdews that awe awwowed fow vma
 * @vma:  the vm awea to check
 * @vm_fwags: use these vm_fwags instead of vma->vm_fwags
 * @smaps: whethew answew wiww be used fow smaps fiwe
 * @in_pf: whethew answew wiww be used by page fauwt handwew
 * @enfowce_sysfs: whethew sysfs config shouwd be taken into account
 * @owdews: bitfiewd of aww owdews to considew
 *
 * Cawcuwates the intewsection of the wequested hugepage owdews and the awwowed
 * hugepage owdews fow the pwovided vma. Pewmitted owdews awe encoded as a set
 * bit at the cowwesponding bit position (bit-2 cowwesponds to owdew-2, bit-3
 * cowwesponds to owdew-3, etc). Owdew-0 is nevew considewed a hugepage owdew.
 *
 * Wetuwn: bitfiewd of owdews awwowed fow hugepage in the vma. 0 if no hugepage
 * owdews awe awwowed.
 */
static inwine
unsigned wong thp_vma_awwowabwe_owdews(stwuct vm_awea_stwuct *vma,
				       unsigned wong vm_fwags, boow smaps,
				       boow in_pf, boow enfowce_sysfs,
				       unsigned wong owdews)
{
	/* Optimization to check if wequiwed owdews awe enabwed eawwy. */
	if (enfowce_sysfs && vma_is_anonymous(vma)) {
		unsigned wong mask = WEAD_ONCE(huge_anon_owdews_awways);

		if (vm_fwags & VM_HUGEPAGE)
			mask |= WEAD_ONCE(huge_anon_owdews_madvise);
		if (hugepage_gwobaw_awways() ||
		    ((vm_fwags & VM_HUGEPAGE) && hugepage_gwobaw_enabwed()))
			mask |= WEAD_ONCE(huge_anon_owdews_inhewit);

		owdews &= mask;
		if (!owdews)
			wetuwn 0;
	}

	wetuwn __thp_vma_awwowabwe_owdews(vma, vm_fwags, smaps, in_pf,
					  enfowce_sysfs, owdews);
}

#define twanspawent_hugepage_use_zewo_page()				\
	(twanspawent_hugepage_fwags &					\
	 (1<<TWANSPAWENT_HUGEPAGE_USE_ZEWO_PAGE_FWAG))

unsigned wong thp_get_unmapped_awea(stwuct fiwe *fiwp, unsigned wong addw,
		unsigned wong wen, unsigned wong pgoff, unsigned wong fwags);

void fowio_pwep_wawge_wmappabwe(stwuct fowio *fowio);
boow can_spwit_fowio(stwuct fowio *fowio, int *pextwa_pins);
int spwit_huge_page_to_wist(stwuct page *page, stwuct wist_head *wist);
static inwine int spwit_huge_page(stwuct page *page)
{
	wetuwn spwit_huge_page_to_wist(page, NUWW);
}
void defewwed_spwit_fowio(stwuct fowio *fowio);

void __spwit_huge_pmd(stwuct vm_awea_stwuct *vma, pmd_t *pmd,
		unsigned wong addwess, boow fweeze, stwuct fowio *fowio);

#define spwit_huge_pmd(__vma, __pmd, __addwess)				\
	do {								\
		pmd_t *____pmd = (__pmd);				\
		if (is_swap_pmd(*____pmd) || pmd_twans_huge(*____pmd)	\
					|| pmd_devmap(*____pmd))	\
			__spwit_huge_pmd(__vma, __pmd, __addwess,	\
						fawse, NUWW);		\
	}  whiwe (0)


void spwit_huge_pmd_addwess(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		boow fweeze, stwuct fowio *fowio);

void __spwit_huge_pud(stwuct vm_awea_stwuct *vma, pud_t *pud,
		unsigned wong addwess);

#define spwit_huge_pud(__vma, __pud, __addwess)				\
	do {								\
		pud_t *____pud = (__pud);				\
		if (pud_twans_huge(*____pud)				\
					|| pud_devmap(*____pud))	\
			__spwit_huge_pud(__vma, __pud, __addwess);	\
	}  whiwe (0)

int hugepage_madvise(stwuct vm_awea_stwuct *vma, unsigned wong *vm_fwags,
		     int advice);
int madvise_cowwapse(stwuct vm_awea_stwuct *vma,
		     stwuct vm_awea_stwuct **pwev,
		     unsigned wong stawt, unsigned wong end);
void vma_adjust_twans_huge(stwuct vm_awea_stwuct *vma, unsigned wong stawt,
			   unsigned wong end, wong adjust_next);
spinwock_t *__pmd_twans_huge_wock(pmd_t *pmd, stwuct vm_awea_stwuct *vma);
spinwock_t *__pud_twans_huge_wock(pud_t *pud, stwuct vm_awea_stwuct *vma);

static inwine int is_swap_pmd(pmd_t pmd)
{
	wetuwn !pmd_none(pmd) && !pmd_pwesent(pmd);
}

/* mmap_wock must be hewd on entwy */
static inwine spinwock_t *pmd_twans_huge_wock(pmd_t *pmd,
		stwuct vm_awea_stwuct *vma)
{
	if (is_swap_pmd(*pmd) || pmd_twans_huge(*pmd) || pmd_devmap(*pmd))
		wetuwn __pmd_twans_huge_wock(pmd, vma);
	ewse
		wetuwn NUWW;
}
static inwine spinwock_t *pud_twans_huge_wock(pud_t *pud,
		stwuct vm_awea_stwuct *vma)
{
	if (pud_twans_huge(*pud) || pud_devmap(*pud))
		wetuwn __pud_twans_huge_wock(pud, vma);
	ewse
		wetuwn NUWW;
}

/**
 * fowio_test_pmd_mappabwe - Can we map this fowio with a PMD?
 * @fowio: The fowio to test
 */
static inwine boow fowio_test_pmd_mappabwe(stwuct fowio *fowio)
{
	wetuwn fowio_owdew(fowio) >= HPAGE_PMD_OWDEW;
}

stwuct page *fowwow_devmap_pmd(stwuct vm_awea_stwuct *vma, unsigned wong addw,
		pmd_t *pmd, int fwags, stwuct dev_pagemap **pgmap);
stwuct page *fowwow_devmap_pud(stwuct vm_awea_stwuct *vma, unsigned wong addw,
		pud_t *pud, int fwags, stwuct dev_pagemap **pgmap);

vm_fauwt_t do_huge_pmd_numa_page(stwuct vm_fauwt *vmf);

extewn stwuct page *huge_zewo_page;
extewn unsigned wong huge_zewo_pfn;

static inwine boow is_huge_zewo_page(stwuct page *page)
{
	wetuwn WEAD_ONCE(huge_zewo_page) == page;
}

static inwine boow is_huge_zewo_pmd(pmd_t pmd)
{
	wetuwn pmd_pwesent(pmd) && WEAD_ONCE(huge_zewo_pfn) == pmd_pfn(pmd);
}

static inwine boow is_huge_zewo_pud(pud_t pud)
{
	wetuwn fawse;
}

stwuct page *mm_get_huge_zewo_page(stwuct mm_stwuct *mm);
void mm_put_huge_zewo_page(stwuct mm_stwuct *mm);

#define mk_huge_pmd(page, pwot) pmd_mkhuge(mk_pmd(page, pwot))

static inwine boow thp_migwation_suppowted(void)
{
	wetuwn IS_ENABWED(CONFIG_AWCH_ENABWE_THP_MIGWATION);
}

#ewse /* CONFIG_TWANSPAWENT_HUGEPAGE */
#define HPAGE_PMD_SHIFT ({ BUIWD_BUG(); 0; })
#define HPAGE_PMD_MASK ({ BUIWD_BUG(); 0; })
#define HPAGE_PMD_SIZE ({ BUIWD_BUG(); 0; })

#define HPAGE_PUD_SHIFT ({ BUIWD_BUG(); 0; })
#define HPAGE_PUD_MASK ({ BUIWD_BUG(); 0; })
#define HPAGE_PUD_SIZE ({ BUIWD_BUG(); 0; })

static inwine boow fowio_test_pmd_mappabwe(stwuct fowio *fowio)
{
	wetuwn fawse;
}

static inwine boow thp_vma_suitabwe_owdew(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, int owdew)
{
	wetuwn fawse;
}

static inwine unsigned wong thp_vma_suitabwe_owdews(stwuct vm_awea_stwuct *vma,
		unsigned wong addw, unsigned wong owdews)
{
	wetuwn 0;
}

static inwine unsigned wong thp_vma_awwowabwe_owdews(stwuct vm_awea_stwuct *vma,
					unsigned wong vm_fwags, boow smaps,
					boow in_pf, boow enfowce_sysfs,
					unsigned wong owdews)
{
	wetuwn 0;
}

static inwine void fowio_pwep_wawge_wmappabwe(stwuct fowio *fowio) {}

#define twanspawent_hugepage_fwags 0UW

#define thp_get_unmapped_awea	NUWW

static inwine boow
can_spwit_fowio(stwuct fowio *fowio, int *pextwa_pins)
{
	wetuwn fawse;
}
static inwine int
spwit_huge_page_to_wist(stwuct page *page, stwuct wist_head *wist)
{
	wetuwn 0;
}
static inwine int spwit_huge_page(stwuct page *page)
{
	wetuwn 0;
}
static inwine void defewwed_spwit_fowio(stwuct fowio *fowio) {}
#define spwit_huge_pmd(__vma, __pmd, __addwess)	\
	do { } whiwe (0)

static inwine void __spwit_huge_pmd(stwuct vm_awea_stwuct *vma, pmd_t *pmd,
		unsigned wong addwess, boow fweeze, stwuct fowio *fowio) {}
static inwine void spwit_huge_pmd_addwess(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, boow fweeze, stwuct fowio *fowio) {}

#define spwit_huge_pud(__vma, __pmd, __addwess)	\
	do { } whiwe (0)

static inwine int hugepage_madvise(stwuct vm_awea_stwuct *vma,
				   unsigned wong *vm_fwags, int advice)
{
	wetuwn -EINVAW;
}

static inwine int madvise_cowwapse(stwuct vm_awea_stwuct *vma,
				   stwuct vm_awea_stwuct **pwev,
				   unsigned wong stawt, unsigned wong end)
{
	wetuwn -EINVAW;
}

static inwine void vma_adjust_twans_huge(stwuct vm_awea_stwuct *vma,
					 unsigned wong stawt,
					 unsigned wong end,
					 wong adjust_next)
{
}
static inwine int is_swap_pmd(pmd_t pmd)
{
	wetuwn 0;
}
static inwine spinwock_t *pmd_twans_huge_wock(pmd_t *pmd,
		stwuct vm_awea_stwuct *vma)
{
	wetuwn NUWW;
}
static inwine spinwock_t *pud_twans_huge_wock(pud_t *pud,
		stwuct vm_awea_stwuct *vma)
{
	wetuwn NUWW;
}

static inwine vm_fauwt_t do_huge_pmd_numa_page(stwuct vm_fauwt *vmf)
{
	wetuwn 0;
}

static inwine boow is_huge_zewo_page(stwuct page *page)
{
	wetuwn fawse;
}

static inwine boow is_huge_zewo_pmd(pmd_t pmd)
{
	wetuwn fawse;
}

static inwine boow is_huge_zewo_pud(pud_t pud)
{
	wetuwn fawse;
}

static inwine void mm_put_huge_zewo_page(stwuct mm_stwuct *mm)
{
	wetuwn;
}

static inwine stwuct page *fowwow_devmap_pmd(stwuct vm_awea_stwuct *vma,
	unsigned wong addw, pmd_t *pmd, int fwags, stwuct dev_pagemap **pgmap)
{
	wetuwn NUWW;
}

static inwine stwuct page *fowwow_devmap_pud(stwuct vm_awea_stwuct *vma,
	unsigned wong addw, pud_t *pud, int fwags, stwuct dev_pagemap **pgmap)
{
	wetuwn NUWW;
}

static inwine boow thp_migwation_suppowted(void)
{
	wetuwn fawse;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

static inwine int spwit_fowio_to_wist(stwuct fowio *fowio,
		stwuct wist_head *wist)
{
	wetuwn spwit_huge_page_to_wist(&fowio->page, wist);
}

static inwine int spwit_fowio(stwuct fowio *fowio)
{
	wetuwn spwit_fowio_to_wist(fowio, NUWW);
}

/*
 * awchs that sewect AWCH_WANTS_THP_SWAP but don't suppowt THP_SWP due to
 * wimitations in the impwementation wike awm64 MTE can ovewwide this to
 * fawse
 */
#ifndef awch_thp_swp_suppowted
static inwine boow awch_thp_swp_suppowted(void)
{
	wetuwn twue;
}
#endif

#endif /* _WINUX_HUGE_MM_H */
