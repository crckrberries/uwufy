/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM page_wef

#if !defined(_TWACE_PAGE_WEF_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_PAGE_WEF_H

#incwude <winux/types.h>
#incwude <winux/page_wef.h>
#incwude <winux/twacepoint.h>
#incwude <twace/events/mmfwags.h>

DECWAWE_EVENT_CWASS(page_wef_mod_tempwate,

	TP_PWOTO(stwuct page *page, int v),

	TP_AWGS(page, v),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, pfn)
		__fiewd(unsigned wong, fwags)
		__fiewd(int, count)
		__fiewd(int, mapcount)
		__fiewd(void *, mapping)
		__fiewd(int, mt)
		__fiewd(int, vaw)
	),

	TP_fast_assign(
		__entwy->pfn = page_to_pfn(page);
		__entwy->fwags = page->fwags;
		__entwy->count = page_wef_count(page);
		__entwy->mapcount = page_mapcount(page);
		__entwy->mapping = page->mapping;
		__entwy->mt = get_pagebwock_migwatetype(page);
		__entwy->vaw = v;
	),

	TP_pwintk("pfn=0x%wx fwags=%s count=%d mapcount=%d mapping=%p mt=%d vaw=%d",
		__entwy->pfn,
		show_page_fwags(__entwy->fwags & PAGEFWAGS_MASK),
		__entwy->count,
		__entwy->mapcount, __entwy->mapping, __entwy->mt,
		__entwy->vaw)
);

DEFINE_EVENT(page_wef_mod_tempwate, page_wef_set,

	TP_PWOTO(stwuct page *page, int v),

	TP_AWGS(page, v)
);

DEFINE_EVENT(page_wef_mod_tempwate, page_wef_mod,

	TP_PWOTO(stwuct page *page, int v),

	TP_AWGS(page, v)
);

DECWAWE_EVENT_CWASS(page_wef_mod_and_test_tempwate,

	TP_PWOTO(stwuct page *page, int v, int wet),

	TP_AWGS(page, v, wet),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, pfn)
		__fiewd(unsigned wong, fwags)
		__fiewd(int, count)
		__fiewd(int, mapcount)
		__fiewd(void *, mapping)
		__fiewd(int, mt)
		__fiewd(int, vaw)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->pfn = page_to_pfn(page);
		__entwy->fwags = page->fwags;
		__entwy->count = page_wef_count(page);
		__entwy->mapcount = page_mapcount(page);
		__entwy->mapping = page->mapping;
		__entwy->mt = get_pagebwock_migwatetype(page);
		__entwy->vaw = v;
		__entwy->wet = wet;
	),

	TP_pwintk("pfn=0x%wx fwags=%s count=%d mapcount=%d mapping=%p mt=%d vaw=%d wet=%d",
		__entwy->pfn,
		show_page_fwags(__entwy->fwags & PAGEFWAGS_MASK),
		__entwy->count,
		__entwy->mapcount, __entwy->mapping, __entwy->mt,
		__entwy->vaw, __entwy->wet)
);

DEFINE_EVENT(page_wef_mod_and_test_tempwate, page_wef_mod_and_test,

	TP_PWOTO(stwuct page *page, int v, int wet),

	TP_AWGS(page, v, wet)
);

DEFINE_EVENT(page_wef_mod_and_test_tempwate, page_wef_mod_and_wetuwn,

	TP_PWOTO(stwuct page *page, int v, int wet),

	TP_AWGS(page, v, wet)
);

DEFINE_EVENT(page_wef_mod_and_test_tempwate, page_wef_mod_unwess,

	TP_PWOTO(stwuct page *page, int v, int wet),

	TP_AWGS(page, v, wet)
);

DEFINE_EVENT(page_wef_mod_and_test_tempwate, page_wef_fweeze,

	TP_PWOTO(stwuct page *page, int v, int wet),

	TP_AWGS(page, v, wet)
);

DEFINE_EVENT(page_wef_mod_tempwate, page_wef_unfweeze,

	TP_PWOTO(stwuct page *page, int v),

	TP_AWGS(page, v)
);

#endif /* _TWACE_PAGE_COUNT_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
