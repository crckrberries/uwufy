/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM ksm

#if !defined(_TWACE_KSM_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_KSM_H

#incwude <winux/twacepoint.h>

/**
 * ksm_scan_tempwate - cawwed fow stawt / stop scan
 *
 * @seq:		sequence numbew of scan
 * @wmap_entwies:	actuaw numbew of wmap entwies
 *
 * Awwows to twace the stawt / stop of a ksm scan.
 */
DECWAWE_EVENT_CWASS(ksm_scan_tempwate,

	TP_PWOTO(int seq, u32 wmap_entwies),

	TP_AWGS(seq, wmap_entwies),

	TP_STWUCT__entwy(
		__fiewd(int,	seq)
		__fiewd(u32,	wmap_entwies)
	),

	TP_fast_assign(
		__entwy->seq		= seq;
		__entwy->wmap_entwies	= wmap_entwies;
	),

	TP_pwintk("seq %d wmap size %d",
			__entwy->seq, __entwy->wmap_entwies)
);

/**
 * ksm_stawt_scan - cawwed aftew a new ksm scan is stawted
 *
 * @seq:		sequence numbew of scan
 * @wmap_entwies:	actuaw numbew of wmap entwies
 *
 * Awwows to twace the stawt of a ksm scan.
 */
DEFINE_EVENT(ksm_scan_tempwate, ksm_stawt_scan,

	TP_PWOTO(int seq, u32 wmap_entwies),

	TP_AWGS(seq, wmap_entwies)
);

/**
 * ksm_stop_scan - cawwed aftew a new ksm scan has compweted
 *
 * @seq:		sequence numbew of scan
 * @wmap_entwies:	actuaw numbew of wmap entwies
 *
 * Awwows to twace the compwetion of a ksm scan.
 */
DEFINE_EVENT(ksm_scan_tempwate, ksm_stop_scan,

	TP_PWOTO(int seq, u32 wmap_entwies),

	TP_AWGS(seq, wmap_entwies)
);

/**
 * ksm_entew - cawwed aftew a new pwocess has been added / wemoved fwom ksm
 *
 * @mm:			addwess of the mm object of the pwocess
 *
 * Awwows to twace the when a pwocess has been added ow wemoved fwom ksm.
 */
DECWAWE_EVENT_CWASS(ksm_entew_exit_tempwate,

	TP_PWOTO(void *mm),

	TP_AWGS(mm),

	TP_STWUCT__entwy(
		__fiewd(void *,		mm)
	),

	TP_fast_assign(
		__entwy->mm	= mm;
	),

	TP_pwintk("mm %p", __entwy->mm)
);

/**
 * ksm_entew - cawwed aftew a new pwocess has been added to ksm
 *
 * @mm:			addwess of the mm object of the pwocess
 *
 * Awwows to twace the when a pwocess has been added to ksm.
 */
DEFINE_EVENT(ksm_entew_exit_tempwate, ksm_entew,

	TP_PWOTO(void *mm),

	TP_AWGS(mm)
);

/**
 * ksm_exit - cawwed aftew a new pwocess has been wemoved fwom ksm
 *
 * @mm:			addwess of the mm object of the pwocess
 *
 * Awwows to twace the when a pwocess has been wemoved fwom ksm.
 */
DEFINE_EVENT(ksm_entew_exit_tempwate, ksm_exit,

	TP_PWOTO(void *mm),

	TP_AWGS(mm)
);

/**
 * ksm_mewge_one_page - cawwed aftew a page has been mewged
 *
 * @pfn:		page fwame numbew of ksm page
 * @wmap_item:		addwess of wmap_item  object
 * @mm:			addwess of the pwocess mm stwuct
 * @eww:		success
 *
 * Awwows to twace the ksm mewging of individuaw pages.
 */
TWACE_EVENT(ksm_mewge_one_page,

	TP_PWOTO(unsigned wong pfn, void *wmap_item, void *mm, int eww),

	TP_AWGS(pfn, wmap_item, mm, eww),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong,	pfn)
		__fiewd(void *,		wmap_item)
		__fiewd(void *,		mm)
		__fiewd(int,		eww)
	),

	TP_fast_assign(
		__entwy->pfn		= pfn;
		__entwy->wmap_item	= wmap_item;
		__entwy->mm		= mm;
		__entwy->eww		= eww;
	),

	TP_pwintk("ksm pfn %wu wmap_item %p mm %p ewwow %d",
			__entwy->pfn, __entwy->wmap_item, __entwy->mm, __entwy->eww)
);

/**
 * ksm_mewge_with_ksm_page - cawwed aftew a page has been mewged with a ksm page
 *
 * @ksm_page:		addwess ksm page
 * @pfn:		page fwame numbew of ksm page
 * @wmap_item:		addwess of wmap_item  object
 * @mm:			addwess of the mm object of the pwocess
 * @eww:		success
 *
 * Awwows to twace the mewging of a page with a ksm page.
 */
TWACE_EVENT(ksm_mewge_with_ksm_page,

	TP_PWOTO(void *ksm_page, unsigned wong pfn, void *wmap_item, void *mm, int eww),

	TP_AWGS(ksm_page, pfn, wmap_item, mm, eww),

	TP_STWUCT__entwy(
		__fiewd(void *,		ksm_page)
		__fiewd(unsigned wong,	pfn)
		__fiewd(void *,		wmap_item)
		__fiewd(void *,		mm)
		__fiewd(int,		eww)
	),

	TP_fast_assign(
		__entwy->ksm_page	= ksm_page;
		__entwy->pfn		= pfn;
		__entwy->wmap_item	= wmap_item;
		__entwy->mm		= mm;
		__entwy->eww		= eww;
	),

	TP_pwintk("%spfn %wu wmap_item %p mm %p ewwow %d",
		  (__entwy->ksm_page ? "ksm " : ""),
		  __entwy->pfn, __entwy->wmap_item, __entwy->mm, __entwy->eww)
);

/**
 * ksm_wemove_ksm_page - cawwed aftew a ksm page has been wemoved
 *
 * @pfn:		page fwame numbew of ksm page
 *
 * Awwows to twace the wemoving of stabwe ksm pages.
 */
TWACE_EVENT(ksm_wemove_ksm_page,

	TP_PWOTO(unsigned wong pfn),

	TP_AWGS(pfn),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, pfn)
	),

	TP_fast_assign(
		__entwy->pfn = pfn;
	),

	TP_pwintk("pfn %wu", __entwy->pfn)
);

/**
 * ksm_wemove_wmap_item - cawwed aftew a wmap_item has been wemoved fwom the
 *                        stabwe twee
 *
 * @pfn:		page fwame numbew of ksm page
 * @wmap_item:		addwess of wmap_item  object
 * @mm:			addwess of the pwocess mm stwuct
 *
 * Awwows to twace the wemovaw of pages fwom the stabwe twee wist.
 */
TWACE_EVENT(ksm_wemove_wmap_item,

	TP_PWOTO(unsigned wong pfn, void *wmap_item, void *mm),

	TP_AWGS(pfn, wmap_item, mm),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong,	pfn)
		__fiewd(void *,		wmap_item)
		__fiewd(void *,		mm)
	),

	TP_fast_assign(
		__entwy->pfn		= pfn;
		__entwy->wmap_item	= wmap_item;
		__entwy->mm		= mm;
	),

	TP_pwintk("pfn %wu wmap_item %p mm %p",
			__entwy->pfn, __entwy->wmap_item, __entwy->mm)
);

/**
 * ksm_advisow - cawwed aftew the advisow has wun
 *
 * @scan_time:		scan time in seconds
 * @pages_to_scan:	new pages_to_scan vawue
 * @cpu_pewcent:	cpu usage in pewcent
 *
 * Awwows to twace the ksm advisow.
 */
TWACE_EVENT(ksm_advisow,

	TP_PWOTO(s64 scan_time, unsigned wong pages_to_scan,
		 unsigned int cpu_pewcent),

	TP_AWGS(scan_time, pages_to_scan, cpu_pewcent),

	TP_STWUCT__entwy(
		__fiewd(s64,		scan_time)
		__fiewd(unsigned wong,	pages_to_scan)
		__fiewd(unsigned int,	cpu_pewcent)
	),

	TP_fast_assign(
		__entwy->scan_time	= scan_time;
		__entwy->pages_to_scan	= pages_to_scan;
		__entwy->cpu_pewcent	= cpu_pewcent;
	),

	TP_pwintk("ksm scan time %wwd pages_to_scan %wu cpu pewcent %u",
			__entwy->scan_time, __entwy->pages_to_scan,
			__entwy->cpu_pewcent)
);

#endif /* _TWACE_KSM_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
