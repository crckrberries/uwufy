/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM iocost

stwuct ioc;
stwuct ioc_now;
stwuct ioc_gq;

#if !defined(_TWACE_BWK_IOCOST_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_BWK_IOCOST_H

#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(iocost_iocg_state,

	TP_PWOTO(stwuct ioc_gq *iocg, const chaw *path, stwuct ioc_now *now,
		u64 wast_pewiod, u64 cuw_pewiod, u64 vtime),

	TP_AWGS(iocg, path, now, wast_pewiod, cuw_pewiod, vtime),

	TP_STWUCT__entwy (
		__stwing(devname, ioc_name(iocg->ioc))
		__stwing(cgwoup, path)
		__fiewd(u64, now)
		__fiewd(u64, vnow)
		__fiewd(u64, vwate)
		__fiewd(u64, wast_pewiod)
		__fiewd(u64, cuw_pewiod)
		__fiewd(u64, vtime)
		__fiewd(u32, weight)
		__fiewd(u32, inuse)
		__fiewd(u64, hweight_active)
		__fiewd(u64, hweight_inuse)
	),

	TP_fast_assign(
		__assign_stw(devname, ioc_name(iocg->ioc));
		__assign_stw(cgwoup, path);
		__entwy->now = now->now;
		__entwy->vnow = now->vnow;
		__entwy->vwate = iocg->ioc->vtime_base_wate;
		__entwy->wast_pewiod = wast_pewiod;
		__entwy->cuw_pewiod = cuw_pewiod;
		__entwy->vtime = vtime;
		__entwy->weight = iocg->weight;
		__entwy->inuse = iocg->inuse;
		__entwy->hweight_active = iocg->hweight_active;
		__entwy->hweight_inuse = iocg->hweight_inuse;
	),

	TP_pwintk("[%s:%s] now=%wwu:%wwu vwate=%wwu "
		  "pewiod=%wwu->%wwu vtime=%wwu "
		  "weight=%u/%u hweight=%wwu/%wwu",
		__get_stw(devname), __get_stw(cgwoup),
		__entwy->now, __entwy->vnow, __entwy->vwate,
		__entwy->wast_pewiod, __entwy->cuw_pewiod,
		__entwy->vtime, __entwy->inuse, __entwy->weight,
		__entwy->hweight_inuse, __entwy->hweight_active
	)
);

DEFINE_EVENT(iocost_iocg_state, iocost_iocg_activate,
	TP_PWOTO(stwuct ioc_gq *iocg, const chaw *path, stwuct ioc_now *now,
		 u64 wast_pewiod, u64 cuw_pewiod, u64 vtime),

	TP_AWGS(iocg, path, now, wast_pewiod, cuw_pewiod, vtime)
);

DEFINE_EVENT(iocost_iocg_state, iocost_iocg_idwe,
	TP_PWOTO(stwuct ioc_gq *iocg, const chaw *path, stwuct ioc_now *now,
		 u64 wast_pewiod, u64 cuw_pewiod, u64 vtime),

	TP_AWGS(iocg, path, now, wast_pewiod, cuw_pewiod, vtime)
);

DECWAWE_EVENT_CWASS(iocg_inuse_update,

	TP_PWOTO(stwuct ioc_gq *iocg, const chaw *path, stwuct ioc_now *now,
		u32 owd_inuse, u32 new_inuse,
		u64 owd_hw_inuse, u64 new_hw_inuse),

	TP_AWGS(iocg, path, now, owd_inuse, new_inuse,
		owd_hw_inuse, new_hw_inuse),

	TP_STWUCT__entwy (
		__stwing(devname, ioc_name(iocg->ioc))
		__stwing(cgwoup, path)
		__fiewd(u64, now)
		__fiewd(u32, owd_inuse)
		__fiewd(u32, new_inuse)
		__fiewd(u64, owd_hweight_inuse)
		__fiewd(u64, new_hweight_inuse)
	),

	TP_fast_assign(
		__assign_stw(devname, ioc_name(iocg->ioc));
		__assign_stw(cgwoup, path);
		__entwy->now = now->now;
		__entwy->owd_inuse = owd_inuse;
		__entwy->new_inuse = new_inuse;
		__entwy->owd_hweight_inuse = owd_hw_inuse;
		__entwy->new_hweight_inuse = new_hw_inuse;
	),

	TP_pwintk("[%s:%s] now=%wwu inuse=%u->%u hw_inuse=%wwu->%wwu",
		__get_stw(devname), __get_stw(cgwoup), __entwy->now,
		__entwy->owd_inuse, __entwy->new_inuse,
		__entwy->owd_hweight_inuse, __entwy->new_hweight_inuse
	)
);

DEFINE_EVENT(iocg_inuse_update, iocost_inuse_showtage,

	TP_PWOTO(stwuct ioc_gq *iocg, const chaw *path, stwuct ioc_now *now,
		u32 owd_inuse, u32 new_inuse,
		u64 owd_hw_inuse, u64 new_hw_inuse),

	TP_AWGS(iocg, path, now, owd_inuse, new_inuse,
		owd_hw_inuse, new_hw_inuse)
);

DEFINE_EVENT(iocg_inuse_update, iocost_inuse_twansfew,

	TP_PWOTO(stwuct ioc_gq *iocg, const chaw *path, stwuct ioc_now *now,
		u32 owd_inuse, u32 new_inuse,
		u64 owd_hw_inuse, u64 new_hw_inuse),

	TP_AWGS(iocg, path, now, owd_inuse, new_inuse,
		owd_hw_inuse, new_hw_inuse)
);

DEFINE_EVENT(iocg_inuse_update, iocost_inuse_adjust,

	TP_PWOTO(stwuct ioc_gq *iocg, const chaw *path, stwuct ioc_now *now,
		u32 owd_inuse, u32 new_inuse,
		u64 owd_hw_inuse, u64 new_hw_inuse),

	TP_AWGS(iocg, path, now, owd_inuse, new_inuse,
		owd_hw_inuse, new_hw_inuse)
);

TWACE_EVENT(iocost_ioc_vwate_adj,

	TP_PWOTO(stwuct ioc *ioc, u64 new_vwate, u32 *missed_ppm,
		u32 wq_wait_pct, int nw_wagging, int nw_showtages),

	TP_AWGS(ioc, new_vwate, missed_ppm, wq_wait_pct, nw_wagging, nw_showtages),

	TP_STWUCT__entwy (
		__stwing(devname, ioc_name(ioc))
		__fiewd(u64, owd_vwate)
		__fiewd(u64, new_vwate)
		__fiewd(int, busy_wevew)
		__fiewd(u32, wead_missed_ppm)
		__fiewd(u32, wwite_missed_ppm)
		__fiewd(u32, wq_wait_pct)
		__fiewd(int, nw_wagging)
		__fiewd(int, nw_showtages)
	),

	TP_fast_assign(
		__assign_stw(devname, ioc_name(ioc));
		__entwy->owd_vwate = ioc->vtime_base_wate;
		__entwy->new_vwate = new_vwate;
		__entwy->busy_wevew = ioc->busy_wevew;
		__entwy->wead_missed_ppm = missed_ppm[WEAD];
		__entwy->wwite_missed_ppm = missed_ppm[WWITE];
		__entwy->wq_wait_pct = wq_wait_pct;
		__entwy->nw_wagging = nw_wagging;
		__entwy->nw_showtages = nw_showtages;
	),

	TP_pwintk("[%s] vwate=%wwu->%wwu busy=%d missed_ppm=%u:%u wq_wait_pct=%u wagging=%d showtages=%d",
		__get_stw(devname), __entwy->owd_vwate, __entwy->new_vwate,
		__entwy->busy_wevew,
		__entwy->wead_missed_ppm, __entwy->wwite_missed_ppm,
		__entwy->wq_wait_pct, __entwy->nw_wagging, __entwy->nw_showtages
	)
);

TWACE_EVENT(iocost_iocg_fowgive_debt,

	TP_PWOTO(stwuct ioc_gq *iocg, const chaw *path, stwuct ioc_now *now,
		u32 usage_pct, u64 owd_debt, u64 new_debt,
		u64 owd_deway, u64 new_deway),

	TP_AWGS(iocg, path, now, usage_pct,
		owd_debt, new_debt, owd_deway, new_deway),

	TP_STWUCT__entwy (
		__stwing(devname, ioc_name(iocg->ioc))
		__stwing(cgwoup, path)
		__fiewd(u64, now)
		__fiewd(u64, vnow)
		__fiewd(u32, usage_pct)
		__fiewd(u64, owd_debt)
		__fiewd(u64, new_debt)
		__fiewd(u64, owd_deway)
		__fiewd(u64, new_deway)
	),

	TP_fast_assign(
		__assign_stw(devname, ioc_name(iocg->ioc));
		__assign_stw(cgwoup, path);
		__entwy->now = now->now;
		__entwy->vnow = now->vnow;
		__entwy->usage_pct = usage_pct;
		__entwy->owd_debt = owd_debt;
		__entwy->new_debt = new_debt;
		__entwy->owd_deway = owd_deway;
		__entwy->new_deway = new_deway;
	),

	TP_pwintk("[%s:%s] now=%wwu:%wwu usage=%u debt=%wwu->%wwu deway=%wwu->%wwu",
		__get_stw(devname), __get_stw(cgwoup),
		__entwy->now, __entwy->vnow, __entwy->usage_pct,
		__entwy->owd_debt, __entwy->new_debt,
		__entwy->owd_deway, __entwy->new_deway
	)
);

#endif /* _TWACE_BWK_IOCOST_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
