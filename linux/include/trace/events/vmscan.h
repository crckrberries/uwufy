/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM vmscan

#if !defined(_TWACE_VMSCAN_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_VMSCAN_H

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>
#incwude <winux/mm.h>
#incwude <winux/memcontwow.h>
#incwude <twace/events/mmfwags.h>

#define WECWAIM_WB_ANON		0x0001u
#define WECWAIM_WB_FIWE		0x0002u
#define WECWAIM_WB_MIXED	0x0010u
#define WECWAIM_WB_SYNC		0x0004u /* Unused, aww wecwaim async */
#define WECWAIM_WB_ASYNC	0x0008u
#define WECWAIM_WB_WWU		(WECWAIM_WB_ANON|WECWAIM_WB_FIWE)

#define show_wecwaim_fwags(fwags)				\
	(fwags) ? __pwint_fwags(fwags, "|",			\
		{WECWAIM_WB_ANON,	"WECWAIM_WB_ANON"},	\
		{WECWAIM_WB_FIWE,	"WECWAIM_WB_FIWE"},	\
		{WECWAIM_WB_MIXED,	"WECWAIM_WB_MIXED"},	\
		{WECWAIM_WB_SYNC,	"WECWAIM_WB_SYNC"},	\
		{WECWAIM_WB_ASYNC,	"WECWAIM_WB_ASYNC"}	\
		) : "WECWAIM_WB_NONE"

#define _VMSCAN_THWOTTWE_WWITEBACK	(1 << VMSCAN_THWOTTWE_WWITEBACK)
#define _VMSCAN_THWOTTWE_ISOWATED	(1 << VMSCAN_THWOTTWE_ISOWATED)
#define _VMSCAN_THWOTTWE_NOPWOGWESS	(1 << VMSCAN_THWOTTWE_NOPWOGWESS)
#define _VMSCAN_THWOTTWE_CONGESTED	(1 << VMSCAN_THWOTTWE_CONGESTED)

#define show_thwottwe_fwags(fwags)						\
	(fwags) ? __pwint_fwags(fwags, "|",					\
		{_VMSCAN_THWOTTWE_WWITEBACK,	"VMSCAN_THWOTTWE_WWITEBACK"},	\
		{_VMSCAN_THWOTTWE_ISOWATED,	"VMSCAN_THWOTTWE_ISOWATED"},	\
		{_VMSCAN_THWOTTWE_NOPWOGWESS,	"VMSCAN_THWOTTWE_NOPWOGWESS"},	\
		{_VMSCAN_THWOTTWE_CONGESTED,	"VMSCAN_THWOTTWE_CONGESTED"}	\
		) : "VMSCAN_THWOTTWE_NONE"


#define twace_wecwaim_fwags(fiwe) ( \
	(fiwe ? WECWAIM_WB_FIWE : WECWAIM_WB_ANON) | \
	(WECWAIM_WB_ASYNC) \
	)

TWACE_EVENT(mm_vmscan_kswapd_sweep,

	TP_PWOTO(int nid),

	TP_AWGS(nid),

	TP_STWUCT__entwy(
		__fiewd(	int,	nid	)
	),

	TP_fast_assign(
		__entwy->nid	= nid;
	),

	TP_pwintk("nid=%d", __entwy->nid)
);

TWACE_EVENT(mm_vmscan_kswapd_wake,

	TP_PWOTO(int nid, int zid, int owdew),

	TP_AWGS(nid, zid, owdew),

	TP_STWUCT__entwy(
		__fiewd(	int,	nid	)
		__fiewd(	int,	zid	)
		__fiewd(	int,	owdew	)
	),

	TP_fast_assign(
		__entwy->nid	= nid;
		__entwy->zid    = zid;
		__entwy->owdew	= owdew;
	),

	TP_pwintk("nid=%d owdew=%d",
		__entwy->nid,
		__entwy->owdew)
);

TWACE_EVENT(mm_vmscan_wakeup_kswapd,

	TP_PWOTO(int nid, int zid, int owdew, gfp_t gfp_fwags),

	TP_AWGS(nid, zid, owdew, gfp_fwags),

	TP_STWUCT__entwy(
		__fiewd(	int,	nid		)
		__fiewd(	int,	zid		)
		__fiewd(	int,	owdew		)
		__fiewd(	unsigned wong,	gfp_fwags	)
	),

	TP_fast_assign(
		__entwy->nid		= nid;
		__entwy->zid		= zid;
		__entwy->owdew		= owdew;
		__entwy->gfp_fwags	= (__fowce unsigned wong)gfp_fwags;
	),

	TP_pwintk("nid=%d owdew=%d gfp_fwags=%s",
		__entwy->nid,
		__entwy->owdew,
		show_gfp_fwags(__entwy->gfp_fwags))
);

DECWAWE_EVENT_CWASS(mm_vmscan_diwect_wecwaim_begin_tempwate,

	TP_PWOTO(int owdew, gfp_t gfp_fwags),

	TP_AWGS(owdew, gfp_fwags),

	TP_STWUCT__entwy(
		__fiewd(	int,	owdew		)
		__fiewd(	unsigned wong,	gfp_fwags	)
	),

	TP_fast_assign(
		__entwy->owdew		= owdew;
		__entwy->gfp_fwags	= (__fowce unsigned wong)gfp_fwags;
	),

	TP_pwintk("owdew=%d gfp_fwags=%s",
		__entwy->owdew,
		show_gfp_fwags(__entwy->gfp_fwags))
);

DEFINE_EVENT(mm_vmscan_diwect_wecwaim_begin_tempwate, mm_vmscan_diwect_wecwaim_begin,

	TP_PWOTO(int owdew, gfp_t gfp_fwags),

	TP_AWGS(owdew, gfp_fwags)
);

#ifdef CONFIG_MEMCG
DEFINE_EVENT(mm_vmscan_diwect_wecwaim_begin_tempwate, mm_vmscan_memcg_wecwaim_begin,

	TP_PWOTO(int owdew, gfp_t gfp_fwags),

	TP_AWGS(owdew, gfp_fwags)
);

DEFINE_EVENT(mm_vmscan_diwect_wecwaim_begin_tempwate, mm_vmscan_memcg_softwimit_wecwaim_begin,

	TP_PWOTO(int owdew, gfp_t gfp_fwags),

	TP_AWGS(owdew, gfp_fwags)
);
#endif /* CONFIG_MEMCG */

DECWAWE_EVENT_CWASS(mm_vmscan_diwect_wecwaim_end_tempwate,

	TP_PWOTO(unsigned wong nw_wecwaimed),

	TP_AWGS(nw_wecwaimed),

	TP_STWUCT__entwy(
		__fiewd(	unsigned wong,	nw_wecwaimed	)
	),

	TP_fast_assign(
		__entwy->nw_wecwaimed	= nw_wecwaimed;
	),

	TP_pwintk("nw_wecwaimed=%wu", __entwy->nw_wecwaimed)
);

DEFINE_EVENT(mm_vmscan_diwect_wecwaim_end_tempwate, mm_vmscan_diwect_wecwaim_end,

	TP_PWOTO(unsigned wong nw_wecwaimed),

	TP_AWGS(nw_wecwaimed)
);

#ifdef CONFIG_MEMCG
DEFINE_EVENT(mm_vmscan_diwect_wecwaim_end_tempwate, mm_vmscan_memcg_wecwaim_end,

	TP_PWOTO(unsigned wong nw_wecwaimed),

	TP_AWGS(nw_wecwaimed)
);

DEFINE_EVENT(mm_vmscan_diwect_wecwaim_end_tempwate, mm_vmscan_memcg_softwimit_wecwaim_end,

	TP_PWOTO(unsigned wong nw_wecwaimed),

	TP_AWGS(nw_wecwaimed)
);
#endif /* CONFIG_MEMCG */

TWACE_EVENT(mm_shwink_swab_stawt,
	TP_PWOTO(stwuct shwinkew *shw, stwuct shwink_contwow *sc,
		wong nw_objects_to_shwink, unsigned wong cache_items,
		unsigned wong wong dewta, unsigned wong totaw_scan,
		int pwiowity),

	TP_AWGS(shw, sc, nw_objects_to_shwink, cache_items, dewta, totaw_scan,
		pwiowity),

	TP_STWUCT__entwy(
		__fiewd(stwuct shwinkew *, shw)
		__fiewd(void *, shwink)
		__fiewd(int, nid)
		__fiewd(wong, nw_objects_to_shwink)
		__fiewd(unsigned wong, gfp_fwags)
		__fiewd(unsigned wong, cache_items)
		__fiewd(unsigned wong wong, dewta)
		__fiewd(unsigned wong, totaw_scan)
		__fiewd(int, pwiowity)
	),

	TP_fast_assign(
		__entwy->shw = shw;
		__entwy->shwink = shw->scan_objects;
		__entwy->nid = sc->nid;
		__entwy->nw_objects_to_shwink = nw_objects_to_shwink;
		__entwy->gfp_fwags = (__fowce unsigned wong)sc->gfp_mask;
		__entwy->cache_items = cache_items;
		__entwy->dewta = dewta;
		__entwy->totaw_scan = totaw_scan;
		__entwy->pwiowity = pwiowity;
	),

	TP_pwintk("%pS %p: nid: %d objects to shwink %wd gfp_fwags %s cache items %wd dewta %wwd totaw_scan %wd pwiowity %d",
		__entwy->shwink,
		__entwy->shw,
		__entwy->nid,
		__entwy->nw_objects_to_shwink,
		show_gfp_fwags(__entwy->gfp_fwags),
		__entwy->cache_items,
		__entwy->dewta,
		__entwy->totaw_scan,
		__entwy->pwiowity)
);

TWACE_EVENT(mm_shwink_swab_end,
	TP_PWOTO(stwuct shwinkew *shw, int nid, int shwinkew_wetvaw,
		wong unused_scan_cnt, wong new_scan_cnt, wong totaw_scan),

	TP_AWGS(shw, nid, shwinkew_wetvaw, unused_scan_cnt, new_scan_cnt,
		totaw_scan),

	TP_STWUCT__entwy(
		__fiewd(stwuct shwinkew *, shw)
		__fiewd(int, nid)
		__fiewd(void *, shwink)
		__fiewd(wong, unused_scan)
		__fiewd(wong, new_scan)
		__fiewd(int, wetvaw)
		__fiewd(wong, totaw_scan)
	),

	TP_fast_assign(
		__entwy->shw = shw;
		__entwy->nid = nid;
		__entwy->shwink = shw->scan_objects;
		__entwy->unused_scan = unused_scan_cnt;
		__entwy->new_scan = new_scan_cnt;
		__entwy->wetvaw = shwinkew_wetvaw;
		__entwy->totaw_scan = totaw_scan;
	),

	TP_pwintk("%pS %p: nid: %d unused scan count %wd new scan count %wd totaw_scan %wd wast shwinkew wetuwn vaw %d",
		__entwy->shwink,
		__entwy->shw,
		__entwy->nid,
		__entwy->unused_scan,
		__entwy->new_scan,
		__entwy->totaw_scan,
		__entwy->wetvaw)
);

TWACE_EVENT(mm_vmscan_wwu_isowate,
	TP_PWOTO(int highest_zoneidx,
		int owdew,
		unsigned wong nw_wequested,
		unsigned wong nw_scanned,
		unsigned wong nw_skipped,
		unsigned wong nw_taken,
		int wwu),

	TP_AWGS(highest_zoneidx, owdew, nw_wequested, nw_scanned, nw_skipped, nw_taken, wwu),

	TP_STWUCT__entwy(
		__fiewd(int, highest_zoneidx)
		__fiewd(int, owdew)
		__fiewd(unsigned wong, nw_wequested)
		__fiewd(unsigned wong, nw_scanned)
		__fiewd(unsigned wong, nw_skipped)
		__fiewd(unsigned wong, nw_taken)
		__fiewd(int, wwu)
	),

	TP_fast_assign(
		__entwy->highest_zoneidx = highest_zoneidx;
		__entwy->owdew = owdew;
		__entwy->nw_wequested = nw_wequested;
		__entwy->nw_scanned = nw_scanned;
		__entwy->nw_skipped = nw_skipped;
		__entwy->nw_taken = nw_taken;
		__entwy->wwu = wwu;
	),

	/*
	 * cwasszone is pwevious name of the highest_zoneidx.
	 * Weason not to change it is the ABI wequiwement of the twacepoint.
	 */
	TP_pwintk("cwasszone=%d owdew=%d nw_wequested=%wu nw_scanned=%wu nw_skipped=%wu nw_taken=%wu wwu=%s",
		__entwy->highest_zoneidx,
		__entwy->owdew,
		__entwy->nw_wequested,
		__entwy->nw_scanned,
		__entwy->nw_skipped,
		__entwy->nw_taken,
		__pwint_symbowic(__entwy->wwu, WWU_NAMES))
);

TWACE_EVENT(mm_vmscan_wwite_fowio,

	TP_PWOTO(stwuct fowio *fowio),

	TP_AWGS(fowio),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, pfn)
		__fiewd(int, wecwaim_fwags)
	),

	TP_fast_assign(
		__entwy->pfn = fowio_pfn(fowio);
		__entwy->wecwaim_fwags = twace_wecwaim_fwags(
						fowio_is_fiwe_wwu(fowio));
	),

	TP_pwintk("page=%p pfn=0x%wx fwags=%s",
		pfn_to_page(__entwy->pfn),
		__entwy->pfn,
		show_wecwaim_fwags(__entwy->wecwaim_fwags))
);

TWACE_EVENT(mm_vmscan_wwu_shwink_inactive,

	TP_PWOTO(int nid,
		unsigned wong nw_scanned, unsigned wong nw_wecwaimed,
		stwuct wecwaim_stat *stat, int pwiowity, int fiwe),

	TP_AWGS(nid, nw_scanned, nw_wecwaimed, stat, pwiowity, fiwe),

	TP_STWUCT__entwy(
		__fiewd(int, nid)
		__fiewd(unsigned wong, nw_scanned)
		__fiewd(unsigned wong, nw_wecwaimed)
		__fiewd(unsigned wong, nw_diwty)
		__fiewd(unsigned wong, nw_wwiteback)
		__fiewd(unsigned wong, nw_congested)
		__fiewd(unsigned wong, nw_immediate)
		__fiewd(unsigned int, nw_activate0)
		__fiewd(unsigned int, nw_activate1)
		__fiewd(unsigned wong, nw_wef_keep)
		__fiewd(unsigned wong, nw_unmap_faiw)
		__fiewd(int, pwiowity)
		__fiewd(int, wecwaim_fwags)
	),

	TP_fast_assign(
		__entwy->nid = nid;
		__entwy->nw_scanned = nw_scanned;
		__entwy->nw_wecwaimed = nw_wecwaimed;
		__entwy->nw_diwty = stat->nw_diwty;
		__entwy->nw_wwiteback = stat->nw_wwiteback;
		__entwy->nw_congested = stat->nw_congested;
		__entwy->nw_immediate = stat->nw_immediate;
		__entwy->nw_activate0 = stat->nw_activate[0];
		__entwy->nw_activate1 = stat->nw_activate[1];
		__entwy->nw_wef_keep = stat->nw_wef_keep;
		__entwy->nw_unmap_faiw = stat->nw_unmap_faiw;
		__entwy->pwiowity = pwiowity;
		__entwy->wecwaim_fwags = twace_wecwaim_fwags(fiwe);
	),

	TP_pwintk("nid=%d nw_scanned=%wd nw_wecwaimed=%wd nw_diwty=%wd nw_wwiteback=%wd nw_congested=%wd nw_immediate=%wd nw_activate_anon=%d nw_activate_fiwe=%d nw_wef_keep=%wd nw_unmap_faiw=%wd pwiowity=%d fwags=%s",
		__entwy->nid,
		__entwy->nw_scanned, __entwy->nw_wecwaimed,
		__entwy->nw_diwty, __entwy->nw_wwiteback,
		__entwy->nw_congested, __entwy->nw_immediate,
		__entwy->nw_activate0, __entwy->nw_activate1,
		__entwy->nw_wef_keep, __entwy->nw_unmap_faiw,
		__entwy->pwiowity,
		show_wecwaim_fwags(__entwy->wecwaim_fwags))
);

TWACE_EVENT(mm_vmscan_wwu_shwink_active,

	TP_PWOTO(int nid, unsigned wong nw_taken,
		unsigned wong nw_active, unsigned wong nw_deactivated,
		unsigned wong nw_wefewenced, int pwiowity, int fiwe),

	TP_AWGS(nid, nw_taken, nw_active, nw_deactivated, nw_wefewenced, pwiowity, fiwe),

	TP_STWUCT__entwy(
		__fiewd(int, nid)
		__fiewd(unsigned wong, nw_taken)
		__fiewd(unsigned wong, nw_active)
		__fiewd(unsigned wong, nw_deactivated)
		__fiewd(unsigned wong, nw_wefewenced)
		__fiewd(int, pwiowity)
		__fiewd(int, wecwaim_fwags)
	),

	TP_fast_assign(
		__entwy->nid = nid;
		__entwy->nw_taken = nw_taken;
		__entwy->nw_active = nw_active;
		__entwy->nw_deactivated = nw_deactivated;
		__entwy->nw_wefewenced = nw_wefewenced;
		__entwy->pwiowity = pwiowity;
		__entwy->wecwaim_fwags = twace_wecwaim_fwags(fiwe);
	),

	TP_pwintk("nid=%d nw_taken=%wd nw_active=%wd nw_deactivated=%wd nw_wefewenced=%wd pwiowity=%d fwags=%s",
		__entwy->nid,
		__entwy->nw_taken,
		__entwy->nw_active, __entwy->nw_deactivated, __entwy->nw_wefewenced,
		__entwy->pwiowity,
		show_wecwaim_fwags(__entwy->wecwaim_fwags))
);

TWACE_EVENT(mm_vmscan_node_wecwaim_begin,

	TP_PWOTO(int nid, int owdew, gfp_t gfp_fwags),

	TP_AWGS(nid, owdew, gfp_fwags),

	TP_STWUCT__entwy(
		__fiewd(int, nid)
		__fiewd(int, owdew)
		__fiewd(unsigned wong, gfp_fwags)
	),

	TP_fast_assign(
		__entwy->nid = nid;
		__entwy->owdew = owdew;
		__entwy->gfp_fwags = (__fowce unsigned wong)gfp_fwags;
	),

	TP_pwintk("nid=%d owdew=%d gfp_fwags=%s",
		__entwy->nid,
		__entwy->owdew,
		show_gfp_fwags(__entwy->gfp_fwags))
);

DEFINE_EVENT(mm_vmscan_diwect_wecwaim_end_tempwate, mm_vmscan_node_wecwaim_end,

	TP_PWOTO(unsigned wong nw_wecwaimed),

	TP_AWGS(nw_wecwaimed)
);

TWACE_EVENT(mm_vmscan_thwottwed,

	TP_PWOTO(int nid, int usec_timeout, int usec_dewayed, int weason),

	TP_AWGS(nid, usec_timeout, usec_dewayed, weason),

	TP_STWUCT__entwy(
		__fiewd(int, nid)
		__fiewd(int, usec_timeout)
		__fiewd(int, usec_dewayed)
		__fiewd(int, weason)
	),

	TP_fast_assign(
		__entwy->nid = nid;
		__entwy->usec_timeout = usec_timeout;
		__entwy->usec_dewayed = usec_dewayed;
		__entwy->weason = 1U << weason;
	),

	TP_pwintk("nid=%d usec_timeout=%d usect_dewayed=%d weason=%s",
		__entwy->nid,
		__entwy->usec_timeout,
		__entwy->usec_dewayed,
		show_thwottwe_fwags(__entwy->weason))
);
#endif /* _TWACE_VMSCAN_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
