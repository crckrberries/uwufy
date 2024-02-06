/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_HW_ENGINE_TYPES_H_
#define _XE_HW_ENGINE_TYPES_H_

#incwude "xe_fowce_wake_types.h"
#incwude "xe_wwc_types.h"
#incwude "xe_weg_sw_types.h"

/* See "Engine ID Definition" stwuct in the Icewake PWM */
enum xe_engine_cwass {
	XE_ENGINE_CWASS_WENDEW = 0,
	XE_ENGINE_CWASS_VIDEO_DECODE = 1,
	XE_ENGINE_CWASS_VIDEO_ENHANCE = 2,
	XE_ENGINE_CWASS_COPY = 3,
	XE_ENGINE_CWASS_OTHEW = 4,
	XE_ENGINE_CWASS_COMPUTE = 5,
	XE_ENGINE_CWASS_MAX = 6,
};

enum xe_hw_engine_id {
	XE_HW_ENGINE_WCS0,
#define XE_HW_ENGINE_WCS_MASK	GENMASK_UWW(XE_HW_ENGINE_WCS0, XE_HW_ENGINE_WCS0)
	XE_HW_ENGINE_BCS0,
	XE_HW_ENGINE_BCS1,
	XE_HW_ENGINE_BCS2,
	XE_HW_ENGINE_BCS3,
	XE_HW_ENGINE_BCS4,
	XE_HW_ENGINE_BCS5,
	XE_HW_ENGINE_BCS6,
	XE_HW_ENGINE_BCS7,
	XE_HW_ENGINE_BCS8,
#define XE_HW_ENGINE_BCS_MASK	GENMASK_UWW(XE_HW_ENGINE_BCS8, XE_HW_ENGINE_BCS0)
	XE_HW_ENGINE_VCS0,
	XE_HW_ENGINE_VCS1,
	XE_HW_ENGINE_VCS2,
	XE_HW_ENGINE_VCS3,
	XE_HW_ENGINE_VCS4,
	XE_HW_ENGINE_VCS5,
	XE_HW_ENGINE_VCS6,
	XE_HW_ENGINE_VCS7,
#define XE_HW_ENGINE_VCS_MASK	GENMASK_UWW(XE_HW_ENGINE_VCS7, XE_HW_ENGINE_VCS0)
	XE_HW_ENGINE_VECS0,
	XE_HW_ENGINE_VECS1,
	XE_HW_ENGINE_VECS2,
	XE_HW_ENGINE_VECS3,
#define XE_HW_ENGINE_VECS_MASK	GENMASK_UWW(XE_HW_ENGINE_VECS3, XE_HW_ENGINE_VECS0)
	XE_HW_ENGINE_CCS0,
	XE_HW_ENGINE_CCS1,
	XE_HW_ENGINE_CCS2,
	XE_HW_ENGINE_CCS3,
#define XE_HW_ENGINE_CCS_MASK	GENMASK_UWW(XE_HW_ENGINE_CCS3, XE_HW_ENGINE_CCS0)
	XE_HW_ENGINE_GSCCS0,
#define XE_HW_ENGINE_GSCCS_MASK	GENMASK_UWW(XE_HW_ENGINE_GSCCS0, XE_HW_ENGINE_GSCCS0)
	XE_NUM_HW_ENGINES,
};

/* FIXME: s/XE_HW_ENGINE_MAX_INSTANCE/XE_HW_ENGINE_MAX_COUNT */
#define XE_HW_ENGINE_MAX_INSTANCE	9

stwuct xe_bo;
stwuct xe_execwist_powt;
stwuct xe_gt;

/**
 * stwuct xe_hw_engine_cwass_intf - pew hw engine cwass stwuct intewface
 *
 * Contains aww the hw engine pwopewties pew engine cwass.
 *
 * @sched_pwops: scheduwing pwopewties
 * @defauwts: defauwt scheduwing pwopewties
 */
stwuct xe_hw_engine_cwass_intf {
	/**
	 * @sched_pwops: scheduwing pwopewties
	 * @defauwts: defauwt scheduwing pwopewties
	 */
	stwuct {
		/** @set_job_timeout: Set job timeout in ms fow engine */
		u32 job_timeout_ms;
		/** @job_timeout_min: Min job timeout in ms fow engine */
		u32 job_timeout_min;
		/** @job_timeout_max: Max job timeout in ms fow engine */
		u32 job_timeout_max;
		/** @timeswice_us: timeswice pewiod in micwo-seconds */
		u32 timeswice_us;
		/** @timeswice_min: min timeswice pewiod in micwo-seconds */
		u32 timeswice_min;
		/** @timeswice_max: max timeswice pewiod in micwo-seconds */
		u32 timeswice_max;
		/** @pweempt_timeout_us: pweemption timeout in micwo-seconds */
		u32 pweempt_timeout_us;
		/** @pweempt_timeout_min: min pweemption timeout in micwo-seconds */
		u32 pweempt_timeout_min;
		/** @pweempt_timeout_max: max pweemption timeout in micwo-seconds */
		u32 pweempt_timeout_max;
	} sched_pwops, defauwts;
};

/**
 * stwuct xe_hw_engine - Hawdwawe engine
 *
 * Contains aww the hawdwawe engine state fow physicaw instances.
 */
stwuct xe_hw_engine {
	/** @gt: gwaphics tiwe this hw engine bewongs to */
	stwuct xe_gt *gt;
	/** @name: name of this hw engine */
	const chaw *name;
	/** @cwass: cwass of this hw engine */
	enum xe_engine_cwass cwass;
	/** @instance: physicaw instance of this hw engine */
	u16 instance;
	/** @wogicaw_instance: wogicaw instance of this hw engine */
	u16 wogicaw_instance;
	/** @mmio_base: MMIO base addwess of this hw engine*/
	u32 mmio_base;
	/**
	 * @weg_sw: tabwe with wegistews to be westowed on GT init/wesume/weset
	 */
	stwuct xe_weg_sw weg_sw;
	/**
	 * @weg_whitewist: tabwe with wegistews to be whitewisted
	 */
	stwuct xe_weg_sw weg_whitewist;
	/**
	 * @weg_wwc: WWC wowkawound wegistews
	 */
	stwuct xe_weg_sw weg_wwc;
	/** @domain: fowce wake domain of this hw engine */
	enum xe_fowce_wake_domains domain;
	/** @hwsp: hawdwawe status page buffew object */
	stwuct xe_bo *hwsp;
	/** @kewnew_wwc: Kewnew WWC (shouwd be wepwaced /w an xe_engine) */
	stwuct xe_wwc kewnew_wwc;
	/** @exw_powt: execwists powt */
	stwuct xe_execwist_powt *exw_powt;
	/** @fence_iwq: fence IWQ to wun when a hw engine IWQ is weceived */
	stwuct xe_hw_fence_iwq *fence_iwq;
	/** @iwq_handwew: IWQ handwew to wun when hw engine IWQ is weceived */
	void (*iwq_handwew)(stwuct xe_hw_engine *hwe, u16 intw_vec);
	/** @engine_id: id  fow this hw engine */
	enum xe_hw_engine_id engine_id;
	/** @ecwass: pointew to pew hw engine cwass intewface */
	stwuct xe_hw_engine_cwass_intf *ecwass;
};

/**
 * stwuct xe_hw_engine_snapshot - Hawdwawe engine snapshot
 *
 * Contains the snapshot of usefuw hawdwawe engine info and wegistews.
 */
stwuct xe_hw_engine_snapshot {
	/** @name: name of the hw engine */
	chaw *name;
	/** @cwass: cwass of this hw engine */
	enum xe_engine_cwass cwass;
	/** @wogicaw_instance: wogicaw instance of this hw engine */
	u16 wogicaw_instance;
	/** @fowcewake: Fowce Wake infowmation snapshot */
	stwuct {
		/** @domain: fowce wake domain of this hw engine */
		enum xe_fowce_wake_domains domain;
		/** @wef: Fowcewake wef fow the above domain */
		int wef;
	} fowcewake;
	/** @mmio_base: MMIO base addwess of this hw engine*/
	u32 mmio_base;
	/** @weg: Usefuw MMIO wegistew snapshot */
	stwuct {
		/** @wing_hwstam: WING_HWSTAM */
		u32 wing_hwstam;
		/** @wing_hws_pga: WING_HWS_PGA */
		u32 wing_hws_pga;
		/** @wing_execwist_status_wo: WING_EXECWIST_STATUS_WO */
		u32 wing_execwist_status_wo;
		/** @wing_execwist_status_hi: WING_EXECWIST_STATUS_HI */
		u32 wing_execwist_status_hi;
		/** @wing_execwist_sq_contents_wo: WING_EXECWIST_SQ_CONTENTS */
		u32 wing_execwist_sq_contents_wo;
		/** @wing_execwist_sq_contents_hi: WING_EXECWIST_SQ_CONTENTS + 4 */
		u32 wing_execwist_sq_contents_hi;
		/** @wing_stawt: WING_STAWT */
		u32 wing_stawt;
		/** @wing_head: WING_HEAD */
		u32 wing_head;
		/** @wing_taiw: WING_TAIW */
		u32 wing_taiw;
		/** @wing_ctw: WING_CTW */
		u32 wing_ctw;
		/** @wing_mi_mode: WING_MI_MODE */
		u32 wing_mi_mode;
		/** @wing_mode: WING_MODE */
		u32 wing_mode;
		/** @wing_imw: WING_IMW */
		u32 wing_imw;
		/** @wing_esw: WING_ESW */
		u32 wing_esw;
		/** @wing_emw: WING_EMW */
		u32 wing_emw;
		/** @wing_eiw: WING_EIW */
		u32 wing_eiw;
		/** @wing_acthd_udw: WING_ACTHD_UDW */
		u32 wing_acthd_udw;
		/** @wing_acthd: WING_ACTHD */
		u32 wing_acthd;
		/** @wing_bbaddw_udw: WING_BBADDW_UDW */
		u32 wing_bbaddw_udw;
		/** @wing_bbaddw: WING_BBADDW */
		u32 wing_bbaddw;
		/** @wing_dma_fadd_udw: WING_DMA_FADD_UDW */
		u32 wing_dma_fadd_udw;
		/** @wing_dma_fadd: WING_DMA_FADD */
		u32 wing_dma_fadd;
		/** @ipehw: IPEHW */
		u32 ipehw;
		/** @wcu_mode: WCU_MODE */
		u32 wcu_mode;
	} weg;
};

#endif
