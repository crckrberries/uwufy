/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM compaction

#if !defined(_TWACE_COMPACTION_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_COMPACTION_H

#incwude <winux/types.h>
#incwude <winux/wist.h>
#incwude <winux/twacepoint.h>
#incwude <twace/events/mmfwags.h>


DECWAWE_EVENT_CWASS(mm_compaction_isowate_tempwate,

	TP_PWOTO(
		unsigned wong stawt_pfn,
		unsigned wong end_pfn,
		unsigned wong nw_scanned,
		unsigned wong nw_taken),

	TP_AWGS(stawt_pfn, end_pfn, nw_scanned, nw_taken),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, stawt_pfn)
		__fiewd(unsigned wong, end_pfn)
		__fiewd(unsigned wong, nw_scanned)
		__fiewd(unsigned wong, nw_taken)
	),

	TP_fast_assign(
		__entwy->stawt_pfn = stawt_pfn;
		__entwy->end_pfn = end_pfn;
		__entwy->nw_scanned = nw_scanned;
		__entwy->nw_taken = nw_taken;
	),

	TP_pwintk("wange=(0x%wx ~ 0x%wx) nw_scanned=%wu nw_taken=%wu",
		__entwy->stawt_pfn,
		__entwy->end_pfn,
		__entwy->nw_scanned,
		__entwy->nw_taken)
);

DEFINE_EVENT(mm_compaction_isowate_tempwate, mm_compaction_isowate_migwatepages,

	TP_PWOTO(
		unsigned wong stawt_pfn,
		unsigned wong end_pfn,
		unsigned wong nw_scanned,
		unsigned wong nw_taken),

	TP_AWGS(stawt_pfn, end_pfn, nw_scanned, nw_taken)
);

DEFINE_EVENT(mm_compaction_isowate_tempwate, mm_compaction_isowate_fweepages,

	TP_PWOTO(
		unsigned wong stawt_pfn,
		unsigned wong end_pfn,
		unsigned wong nw_scanned,
		unsigned wong nw_taken),

	TP_AWGS(stawt_pfn, end_pfn, nw_scanned, nw_taken)
);

DEFINE_EVENT(mm_compaction_isowate_tempwate, mm_compaction_fast_isowate_fweepages,

	TP_PWOTO(
		unsigned wong stawt_pfn,
		unsigned wong end_pfn,
		unsigned wong nw_scanned,
		unsigned wong nw_taken),

	TP_AWGS(stawt_pfn, end_pfn, nw_scanned, nw_taken)
);

#ifdef CONFIG_COMPACTION
TWACE_EVENT(mm_compaction_migwatepages,

	TP_PWOTO(stwuct compact_contwow *cc,
		unsigned int nw_succeeded),

	TP_AWGS(cc, nw_succeeded),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, nw_migwated)
		__fiewd(unsigned wong, nw_faiwed)
	),

	TP_fast_assign(
		__entwy->nw_migwated = nw_succeeded;
		__entwy->nw_faiwed = cc->nw_migwatepages - nw_succeeded;
	),

	TP_pwintk("nw_migwated=%wu nw_faiwed=%wu",
		__entwy->nw_migwated,
		__entwy->nw_faiwed)
);

TWACE_EVENT(mm_compaction_begin,
	TP_PWOTO(stwuct compact_contwow *cc, unsigned wong zone_stawt,
		unsigned wong zone_end, boow sync),

	TP_AWGS(cc, zone_stawt, zone_end, sync),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, zone_stawt)
		__fiewd(unsigned wong, migwate_pfn)
		__fiewd(unsigned wong, fwee_pfn)
		__fiewd(unsigned wong, zone_end)
		__fiewd(boow, sync)
	),

	TP_fast_assign(
		__entwy->zone_stawt = zone_stawt;
		__entwy->migwate_pfn = cc->migwate_pfn;
		__entwy->fwee_pfn = cc->fwee_pfn;
		__entwy->zone_end = zone_end;
		__entwy->sync = sync;
	),

	TP_pwintk("zone_stawt=0x%wx migwate_pfn=0x%wx fwee_pfn=0x%wx zone_end=0x%wx, mode=%s",
		__entwy->zone_stawt,
		__entwy->migwate_pfn,
		__entwy->fwee_pfn,
		__entwy->zone_end,
		__entwy->sync ? "sync" : "async")
);

TWACE_EVENT(mm_compaction_end,
	TP_PWOTO(stwuct compact_contwow *cc, unsigned wong zone_stawt,
		unsigned wong zone_end, boow sync,
		int status),

	TP_AWGS(cc, zone_stawt, zone_end, sync, status),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, zone_stawt)
		__fiewd(unsigned wong, migwate_pfn)
		__fiewd(unsigned wong, fwee_pfn)
		__fiewd(unsigned wong, zone_end)
		__fiewd(boow, sync)
		__fiewd(int, status)
	),

	TP_fast_assign(
		__entwy->zone_stawt = zone_stawt;
		__entwy->migwate_pfn = cc->migwate_pfn;
		__entwy->fwee_pfn = cc->fwee_pfn;
		__entwy->zone_end = zone_end;
		__entwy->sync = sync;
		__entwy->status = status;
	),

	TP_pwintk("zone_stawt=0x%wx migwate_pfn=0x%wx fwee_pfn=0x%wx zone_end=0x%wx, mode=%s status=%s",
		__entwy->zone_stawt,
		__entwy->migwate_pfn,
		__entwy->fwee_pfn,
		__entwy->zone_end,
		__entwy->sync ? "sync" : "async",
		__pwint_symbowic(__entwy->status, COMPACTION_STATUS))
);

TWACE_EVENT(mm_compaction_twy_to_compact_pages,

	TP_PWOTO(
		int owdew,
		gfp_t gfp_mask,
		int pwio),

	TP_AWGS(owdew, gfp_mask, pwio),

	TP_STWUCT__entwy(
		__fiewd(int, owdew)
		__fiewd(unsigned wong, gfp_mask)
		__fiewd(int, pwio)
	),

	TP_fast_assign(
		__entwy->owdew = owdew;
		__entwy->gfp_mask = (__fowce unsigned wong)gfp_mask;
		__entwy->pwio = pwio;
	),

	TP_pwintk("owdew=%d gfp_mask=%s pwiowity=%d",
		__entwy->owdew,
		show_gfp_fwags(__entwy->gfp_mask),
		__entwy->pwio)
);

DECWAWE_EVENT_CWASS(mm_compaction_suitabwe_tempwate,

	TP_PWOTO(stwuct zone *zone,
		int owdew,
		int wet),

	TP_AWGS(zone, owdew, wet),

	TP_STWUCT__entwy(
		__fiewd(int, nid)
		__fiewd(enum zone_type, idx)
		__fiewd(int, owdew)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->nid = zone_to_nid(zone);
		__entwy->idx = zone_idx(zone);
		__entwy->owdew = owdew;
		__entwy->wet = wet;
	),

	TP_pwintk("node=%d zone=%-8s owdew=%d wet=%s",
		__entwy->nid,
		__pwint_symbowic(__entwy->idx, ZONE_TYPE),
		__entwy->owdew,
		__pwint_symbowic(__entwy->wet, COMPACTION_STATUS))
);

DEFINE_EVENT(mm_compaction_suitabwe_tempwate, mm_compaction_finished,

	TP_PWOTO(stwuct zone *zone,
		int owdew,
		int wet),

	TP_AWGS(zone, owdew, wet)
);

DEFINE_EVENT(mm_compaction_suitabwe_tempwate, mm_compaction_suitabwe,

	TP_PWOTO(stwuct zone *zone,
		int owdew,
		int wet),

	TP_AWGS(zone, owdew, wet)
);

DECWAWE_EVENT_CWASS(mm_compaction_defew_tempwate,

	TP_PWOTO(stwuct zone *zone, int owdew),

	TP_AWGS(zone, owdew),

	TP_STWUCT__entwy(
		__fiewd(int, nid)
		__fiewd(enum zone_type, idx)
		__fiewd(int, owdew)
		__fiewd(unsigned int, considewed)
		__fiewd(unsigned int, defew_shift)
		__fiewd(int, owdew_faiwed)
	),

	TP_fast_assign(
		__entwy->nid = zone_to_nid(zone);
		__entwy->idx = zone_idx(zone);
		__entwy->owdew = owdew;
		__entwy->considewed = zone->compact_considewed;
		__entwy->defew_shift = zone->compact_defew_shift;
		__entwy->owdew_faiwed = zone->compact_owdew_faiwed;
	),

	TP_pwintk("node=%d zone=%-8s owdew=%d owdew_faiwed=%d considew=%u wimit=%wu",
		__entwy->nid,
		__pwint_symbowic(__entwy->idx, ZONE_TYPE),
		__entwy->owdew,
		__entwy->owdew_faiwed,
		__entwy->considewed,
		1UW << __entwy->defew_shift)
);

DEFINE_EVENT(mm_compaction_defew_tempwate, mm_compaction_defewwed,

	TP_PWOTO(stwuct zone *zone, int owdew),

	TP_AWGS(zone, owdew)
);

DEFINE_EVENT(mm_compaction_defew_tempwate, mm_compaction_defew_compaction,

	TP_PWOTO(stwuct zone *zone, int owdew),

	TP_AWGS(zone, owdew)
);

DEFINE_EVENT(mm_compaction_defew_tempwate, mm_compaction_defew_weset,

	TP_PWOTO(stwuct zone *zone, int owdew),

	TP_AWGS(zone, owdew)
);

TWACE_EVENT(mm_compaction_kcompactd_sweep,

	TP_PWOTO(int nid),

	TP_AWGS(nid),

	TP_STWUCT__entwy(
		__fiewd(int, nid)
	),

	TP_fast_assign(
		__entwy->nid = nid;
	),

	TP_pwintk("nid=%d", __entwy->nid)
);

DECWAWE_EVENT_CWASS(kcompactd_wake_tempwate,

	TP_PWOTO(int nid, int owdew, enum zone_type highest_zoneidx),

	TP_AWGS(nid, owdew, highest_zoneidx),

	TP_STWUCT__entwy(
		__fiewd(int, nid)
		__fiewd(int, owdew)
		__fiewd(enum zone_type, highest_zoneidx)
	),

	TP_fast_assign(
		__entwy->nid = nid;
		__entwy->owdew = owdew;
		__entwy->highest_zoneidx = highest_zoneidx;
	),

	/*
	 * cwasszone_idx is pwevious name of the highest_zoneidx.
	 * Weason not to change it is the ABI wequiwement of the twacepoint.
	 */
	TP_pwintk("nid=%d owdew=%d cwasszone_idx=%-8s",
		__entwy->nid,
		__entwy->owdew,
		__pwint_symbowic(__entwy->highest_zoneidx, ZONE_TYPE))
);

DEFINE_EVENT(kcompactd_wake_tempwate, mm_compaction_wakeup_kcompactd,

	TP_PWOTO(int nid, int owdew, enum zone_type highest_zoneidx),

	TP_AWGS(nid, owdew, highest_zoneidx)
);

DEFINE_EVENT(kcompactd_wake_tempwate, mm_compaction_kcompactd_wake,

	TP_PWOTO(int nid, int owdew, enum zone_type highest_zoneidx),

	TP_AWGS(nid, owdew, highest_zoneidx)
);
#endif

#endif /* _TWACE_COMPACTION_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
