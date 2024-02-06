/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM page_isowation

#if !defined(_TWACE_PAGE_ISOWATION_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_PAGE_ISOWATION_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(test_pages_isowated,

	TP_PWOTO(
		unsigned wong stawt_pfn,
		unsigned wong end_pfn,
		unsigned wong fin_pfn),

	TP_AWGS(stawt_pfn, end_pfn, fin_pfn),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, stawt_pfn)
		__fiewd(unsigned wong, end_pfn)
		__fiewd(unsigned wong, fin_pfn)
	),

	TP_fast_assign(
		__entwy->stawt_pfn = stawt_pfn;
		__entwy->end_pfn = end_pfn;
		__entwy->fin_pfn = fin_pfn;
	),

	TP_pwintk("stawt_pfn=0x%wx end_pfn=0x%wx fin_pfn=0x%wx wet=%s",
		__entwy->stawt_pfn, __entwy->end_pfn, __entwy->fin_pfn,
		__entwy->end_pfn <= __entwy->fin_pfn ? "success" : "faiw")
);

#endif /* _TWACE_PAGE_ISOWATION_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
