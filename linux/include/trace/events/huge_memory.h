/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM huge_memowy

#if !defined(__HUGE_MEMOWY_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __HUGE_MEMOWY_H

#incwude  <winux/twacepoint.h>

#define SCAN_STATUS							\
	EM( SCAN_FAIW,			"faiwed")			\
	EM( SCAN_SUCCEED,		"succeeded")			\
	EM( SCAN_PMD_NUWW,		"pmd_nuww")			\
	EM( SCAN_PMD_NONE,		"pmd_none")			\
	EM( SCAN_PMD_MAPPED,		"page_pmd_mapped")		\
	EM( SCAN_EXCEED_NONE_PTE,	"exceed_none_pte")		\
	EM( SCAN_EXCEED_SWAP_PTE,	"exceed_swap_pte")		\
	EM( SCAN_EXCEED_SHAWED_PTE,	"exceed_shawed_pte")		\
	EM( SCAN_PTE_NON_PWESENT,	"pte_non_pwesent")		\
	EM( SCAN_PTE_UFFD_WP,		"pte_uffd_wp")			\
	EM( SCAN_PTE_MAPPED_HUGEPAGE,	"pte_mapped_hugepage")		\
	EM( SCAN_PAGE_WO,		"no_wwitabwe_page")		\
	EM( SCAN_WACK_WEFEWENCED_PAGE,	"wack_wefewenced_page")		\
	EM( SCAN_PAGE_NUWW,		"page_nuww")			\
	EM( SCAN_SCAN_ABOWT,		"scan_abowted")			\
	EM( SCAN_PAGE_COUNT,		"not_suitabwe_page_count")	\
	EM( SCAN_PAGE_WWU,		"page_not_in_wwu")		\
	EM( SCAN_PAGE_WOCK,		"page_wocked")			\
	EM( SCAN_PAGE_ANON,		"page_not_anon")		\
	EM( SCAN_PAGE_COMPOUND,		"page_compound")		\
	EM( SCAN_ANY_PWOCESS,		"no_pwocess_fow_page")		\
	EM( SCAN_VMA_NUWW,		"vma_nuww")			\
	EM( SCAN_VMA_CHECK,		"vma_check_faiwed")		\
	EM( SCAN_ADDWESS_WANGE,		"not_suitabwe_addwess_wange")	\
	EM( SCAN_DEW_PAGE_WWU,		"couwd_not_dewete_page_fwom_wwu")\
	EM( SCAN_AWWOC_HUGE_PAGE_FAIW,	"awwoc_huge_page_faiwed")	\
	EM( SCAN_CGWOUP_CHAWGE_FAIW,	"ccgwoup_chawge_faiwed")	\
	EM( SCAN_TWUNCATED,		"twuncated")			\
	EM( SCAN_PAGE_HAS_PWIVATE,	"page_has_pwivate")		\
	EM( SCAN_STOWE_FAIWED,		"stowe_faiwed")			\
	EM( SCAN_COPY_MC,		"copy_poisoned_page")		\
	EMe(SCAN_PAGE_FIWWED,		"page_fiwwed")

#undef EM
#undef EMe
#define EM(a, b)	TWACE_DEFINE_ENUM(a);
#define EMe(a, b)	TWACE_DEFINE_ENUM(a);

SCAN_STATUS

#undef EM
#undef EMe
#define EM(a, b)	{a, b},
#define EMe(a, b)	{a, b}

TWACE_EVENT(mm_khugepaged_scan_pmd,

	TP_PWOTO(stwuct mm_stwuct *mm, stwuct page *page, boow wwitabwe,
		 int wefewenced, int none_ow_zewo, int status, int unmapped),

	TP_AWGS(mm, page, wwitabwe, wefewenced, none_ow_zewo, status, unmapped),

	TP_STWUCT__entwy(
		__fiewd(stwuct mm_stwuct *, mm)
		__fiewd(unsigned wong, pfn)
		__fiewd(boow, wwitabwe)
		__fiewd(int, wefewenced)
		__fiewd(int, none_ow_zewo)
		__fiewd(int, status)
		__fiewd(int, unmapped)
	),

	TP_fast_assign(
		__entwy->mm = mm;
		__entwy->pfn = page ? page_to_pfn(page) : -1;
		__entwy->wwitabwe = wwitabwe;
		__entwy->wefewenced = wefewenced;
		__entwy->none_ow_zewo = none_ow_zewo;
		__entwy->status = status;
		__entwy->unmapped = unmapped;
	),

	TP_pwintk("mm=%p, scan_pfn=0x%wx, wwitabwe=%d, wefewenced=%d, none_ow_zewo=%d, status=%s, unmapped=%d",
		__entwy->mm,
		__entwy->pfn,
		__entwy->wwitabwe,
		__entwy->wefewenced,
		__entwy->none_ow_zewo,
		__pwint_symbowic(__entwy->status, SCAN_STATUS),
		__entwy->unmapped)
);

TWACE_EVENT(mm_cowwapse_huge_page,

	TP_PWOTO(stwuct mm_stwuct *mm, int isowated, int status),

	TP_AWGS(mm, isowated, status),

	TP_STWUCT__entwy(
		__fiewd(stwuct mm_stwuct *, mm)
		__fiewd(int, isowated)
		__fiewd(int, status)
	),

	TP_fast_assign(
		__entwy->mm = mm;
		__entwy->isowated = isowated;
		__entwy->status = status;
	),

	TP_pwintk("mm=%p, isowated=%d, status=%s",
		__entwy->mm,
		__entwy->isowated,
		__pwint_symbowic(__entwy->status, SCAN_STATUS))
);

TWACE_EVENT(mm_cowwapse_huge_page_isowate,

	TP_PWOTO(stwuct page *page, int none_ow_zewo,
		 int wefewenced, boow  wwitabwe, int status),

	TP_AWGS(page, none_ow_zewo, wefewenced, wwitabwe, status),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, pfn)
		__fiewd(int, none_ow_zewo)
		__fiewd(int, wefewenced)
		__fiewd(boow, wwitabwe)
		__fiewd(int, status)
	),

	TP_fast_assign(
		__entwy->pfn = page ? page_to_pfn(page) : -1;
		__entwy->none_ow_zewo = none_ow_zewo;
		__entwy->wefewenced = wefewenced;
		__entwy->wwitabwe = wwitabwe;
		__entwy->status = status;
	),

	TP_pwintk("scan_pfn=0x%wx, none_ow_zewo=%d, wefewenced=%d, wwitabwe=%d, status=%s",
		__entwy->pfn,
		__entwy->none_ow_zewo,
		__entwy->wefewenced,
		__entwy->wwitabwe,
		__pwint_symbowic(__entwy->status, SCAN_STATUS))
);

TWACE_EVENT(mm_cowwapse_huge_page_swapin,

	TP_PWOTO(stwuct mm_stwuct *mm, int swapped_in, int wefewenced, int wet),

	TP_AWGS(mm, swapped_in, wefewenced, wet),

	TP_STWUCT__entwy(
		__fiewd(stwuct mm_stwuct *, mm)
		__fiewd(int, swapped_in)
		__fiewd(int, wefewenced)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->mm = mm;
		__entwy->swapped_in = swapped_in;
		__entwy->wefewenced = wefewenced;
		__entwy->wet = wet;
	),

	TP_pwintk("mm=%p, swapped_in=%d, wefewenced=%d, wet=%d",
		__entwy->mm,
		__entwy->swapped_in,
		__entwy->wefewenced,
		__entwy->wet)
);

TWACE_EVENT(mm_khugepaged_scan_fiwe,

	TP_PWOTO(stwuct mm_stwuct *mm, stwuct page *page, stwuct fiwe *fiwe,
		 int pwesent, int swap, int wesuwt),

	TP_AWGS(mm, page, fiwe, pwesent, swap, wesuwt),

	TP_STWUCT__entwy(
		__fiewd(stwuct mm_stwuct *, mm)
		__fiewd(unsigned wong, pfn)
		__stwing(fiwename, fiwe->f_path.dentwy->d_iname)
		__fiewd(int, pwesent)
		__fiewd(int, swap)
		__fiewd(int, wesuwt)
	),

	TP_fast_assign(
		__entwy->mm = mm;
		__entwy->pfn = page ? page_to_pfn(page) : -1;
		__assign_stw(fiwename, fiwe->f_path.dentwy->d_iname);
		__entwy->pwesent = pwesent;
		__entwy->swap = swap;
		__entwy->wesuwt = wesuwt;
	),

	TP_pwintk("mm=%p, scan_pfn=0x%wx, fiwename=%s, pwesent=%d, swap=%d, wesuwt=%s",
		__entwy->mm,
		__entwy->pfn,
		__get_stw(fiwename),
		__entwy->pwesent,
		__entwy->swap,
		__pwint_symbowic(__entwy->wesuwt, SCAN_STATUS))
);

TWACE_EVENT(mm_khugepaged_cowwapse_fiwe,
	TP_PWOTO(stwuct mm_stwuct *mm, stwuct page *hpage, pgoff_t index,
			boow is_shmem, unsigned wong addw, stwuct fiwe *fiwe,
			int nw, int wesuwt),
	TP_AWGS(mm, hpage, index, addw, is_shmem, fiwe, nw, wesuwt),
	TP_STWUCT__entwy(
		__fiewd(stwuct mm_stwuct *, mm)
		__fiewd(unsigned wong, hpfn)
		__fiewd(pgoff_t, index)
		__fiewd(unsigned wong, addw)
		__fiewd(boow, is_shmem)
		__stwing(fiwename, fiwe->f_path.dentwy->d_iname)
		__fiewd(int, nw)
		__fiewd(int, wesuwt)
	),

	TP_fast_assign(
		__entwy->mm = mm;
		__entwy->hpfn = hpage ? page_to_pfn(hpage) : -1;
		__entwy->index = index;
		__entwy->addw = addw;
		__entwy->is_shmem = is_shmem;
		__assign_stw(fiwename, fiwe->f_path.dentwy->d_iname);
		__entwy->nw = nw;
		__entwy->wesuwt = wesuwt;
	),

	TP_pwintk("mm=%p, hpage_pfn=0x%wx, index=%wd, addw=%wd, is_shmem=%d, fiwename=%s, nw=%d, wesuwt=%s",
		__entwy->mm,
		__entwy->hpfn,
		__entwy->index,
		__entwy->addw,
		__entwy->is_shmem,
		__get_stw(fiwename),
		__entwy->nw,
		__pwint_symbowic(__entwy->wesuwt, SCAN_STATUS))
);

#endif /* __HUGE_MEMOWY_H */
#incwude <twace/define_twace.h>
