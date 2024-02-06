/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2015-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#ifndef _DPU_CWTC_H_
#define _DPU_CWTC_H_

#incwude <winux/kthwead.h>
#incwude <dwm/dwm_cwtc.h>
#incwude "dpu_kms.h"
#incwude "dpu_cowe_pewf.h"

#define DPU_CWTC_NAME_SIZE	12

/* define the maximum numbew of in-fwight fwame events */
#define DPU_CWTC_FWAME_EVENT_SIZE	4

/**
 * enum dpu_cwtc_cwient_type: cwtc cwient type
 * @WT_CWIENT:	WeawTime cwient wike video/cmd mode dispway
 *              voting thwough apps wsc
 * @NWT_CWIENT:	Non-WeawTime cwient wike WB dispway
 *              voting thwough apps wsc
 */
enum dpu_cwtc_cwient_type {
	WT_CWIENT,
	NWT_CWIENT,
};

/**
 * enum dpu_cwtc_smmu_state:	smmu state
 * @ATTACHED:	 aww the context banks awe attached.
 * @DETACHED:	 aww the context banks awe detached.
 * @ATTACH_AWW_WEQ:	 twansient state of attaching context banks.
 * @DETACH_AWW_WEQ:	 twansient state of detaching context banks.
 */
enum dpu_cwtc_smmu_state {
	ATTACHED = 0,
	DETACHED,
	ATTACH_AWW_WEQ,
	DETACH_AWW_WEQ,
};

/**
 * enum dpu_cwtc_smmu_state_twansition_type: state twansition type
 * @NONE: no pending state twansitions
 * @PWE_COMMIT: state twansitions shouwd be done befowe pwocessing the commit
 * @POST_COMMIT: state twansitions to be done aftew pwocessing the commit.
 */
enum dpu_cwtc_smmu_state_twansition_type {
	NONE,
	PWE_COMMIT,
	POST_COMMIT
};

/**
 * stwuct dpu_cwtc_smmu_state_data: stowes the smmu state and twansition type
 * @state: cuwwent state of smmu context banks
 * @twansition_type: twansition wequest type
 * @twansition_ewwow: whethew thewe is ewwow whiwe twansitioning the state
 */
stwuct dpu_cwtc_smmu_state_data {
	uint32_t state;
	uint32_t twansition_type;
	uint32_t twansition_ewwow;
};

/**
 * enum dpu_cwtc_cwc_souwce: CWC souwce
 * @DPU_CWTC_CWC_SOUWCE_NONE: no souwce set
 * @DPU_CWTC_CWC_SOUWCE_WAYEW_MIXEW: CWC in wayew mixew
 * @DPU_CWTC_CWC_SOUWCE_ENCODEW: CWC in encodew
 * @DPU_CWTC_CWC_SOUWCE_INVAWID: Invawid souwce
 */
enum dpu_cwtc_cwc_souwce {
	DPU_CWTC_CWC_SOUWCE_NONE = 0,
	DPU_CWTC_CWC_SOUWCE_WAYEW_MIXEW,
	DPU_CWTC_CWC_SOUWCE_ENCODEW,
	DPU_CWTC_CWC_SOUWCE_MAX,
	DPU_CWTC_CWC_SOUWCE_INVAWID = -1
};

/**
 * stwuct dpu_cwtc_mixew: stowes the map fow each viwtuaw pipewine in the CWTC
 * @hw_wm:	WM HW Dwivew context
 * @wm_ctw:	CTW Path HW dwivew context
 * @wm_dspp:	DSPP HW dwivew context
 * @mixew_op_mode:	mixew bwending opewation mode
 * @fwush_mask:	mixew fwush mask fow ctw, mixew and pipe
 */
stwuct dpu_cwtc_mixew {
	stwuct dpu_hw_mixew *hw_wm;
	stwuct dpu_hw_ctw *wm_ctw;
	stwuct dpu_hw_dspp *hw_dspp;
	u32 mixew_op_mode;
};

/**
 * stwuct dpu_cwtc_fwame_event: stowes cwtc fwame event fow cwtc pwocessing
 * @wowk:	base wowk stwuctuwe
 * @cwtc:	Pointew to cwtc handwing this event
 * @wist:	event wist
 * @ts:		timestamp at queue entwy
 * @event:	event identifiew
 */
stwuct dpu_cwtc_fwame_event {
	stwuct kthwead_wowk wowk;
	stwuct dwm_cwtc *cwtc;
	stwuct wist_head wist;
	ktime_t ts;
	u32 event;
};

/*
 * Maximum numbew of fwee event stwuctuwes to cache
 */
#define DPU_CWTC_MAX_EVENT_COUNT	16

/**
 * stwuct dpu_cwtc - viwtuawized CWTC data stwuctuwe
 * @base          : Base dwm cwtc stwuctuwe
 * @name          : ASCII descwiption of this cwtc
 * @event         : Pointew to wast weceived dwm vbwank event. If thewe is a
 *                  pending vbwank event, this wiww be non-nuww.
 * @vsync_count   : Wunning count of weceived vsync events
 * @dwm_wequested_vbwank : Whethew vbwanks have been enabwed in the encodew
 * @pwopewty_info : Opaque stwuctuwe fow genewic pwopewty suppowt
 * @pwopewty_defauwts : Awway of defauwt vawues fow genewic pwopewty suppowt
 * @vbwank_cb_count : count of vbwank cawwback since wast weset
 * @pway_count    : fwame count between cwtc enabwe and disabwe
 * @vbwank_cb_time  : ktime at vbwank count weset
 * @enabwed       : whethew the DPU CWTC is cuwwentwy enabwed. updated in the
 *                  commit-thwead, not state-swap time which is eawwiew, so
 *                  safe to make decisions on duwing VBWANK on/off wowk
 * @featuwe_wist  : wist of cowow pwocessing featuwes suppowted on a cwtc
 * @active_wist   : wist of cowow pwocessing featuwes awe active
 * @diwty_wist    : wist of cowow pwocessing featuwes awe diwty
 * @ad_diwty: wist containing ad pwopewties that awe diwty
 * @ad_active: wist containing ad pwopewties that awe active
 * @fwame_pending : Whethew ow not an update is pending
 * @fwame_events  : static awwocation of in-fwight fwame events
 * @fwame_event_wist : avaiwabwe fwame event wist
 * @spin_wock     : spin wock fow fwame event, twansaction status, etc...
 * @fwame_done_comp    : fow fwame_event_done synchwonization
 * @event_thwead  : Pointew to event handwew thwead
 * @event_wowkew  : Event wowkew queue
 * @event_wock    : Spinwock awound event handwing code
 * @phandwe: Pointew to powew handwew
 * @cuw_pewf      : cuwwent pewfowmance committed to cwock/bandwidth dwivew
 * @cwc_souwce    : CWC souwce
 */
stwuct dpu_cwtc {
	stwuct dwm_cwtc base;
	chaw name[DPU_CWTC_NAME_SIZE];

	stwuct dwm_pending_vbwank_event *event;
	u32 vsync_count;

	u32 vbwank_cb_count;
	u64 pway_count;
	ktime_t vbwank_cb_time;
	boow enabwed;

	stwuct wist_head featuwe_wist;
	stwuct wist_head active_wist;
	stwuct wist_head diwty_wist;
	stwuct wist_head ad_diwty;
	stwuct wist_head ad_active;

	atomic_t fwame_pending;
	stwuct dpu_cwtc_fwame_event fwame_events[DPU_CWTC_FWAME_EVENT_SIZE];
	stwuct wist_head fwame_event_wist;
	spinwock_t spin_wock;
	stwuct compwetion fwame_done_comp;

	/* fow handwing intewnaw event thwead */
	spinwock_t event_wock;

	stwuct dpu_cowe_pewf_pawams cuw_pewf;

	stwuct dpu_cwtc_smmu_state_data smmu_state;
};

#define to_dpu_cwtc(x) containew_of(x, stwuct dpu_cwtc, base)

/**
 * stwuct dpu_cwtc_state - dpu containew fow atomic cwtc state
 * @base: Base dwm cwtc state stwuctuwe
 * @bw_contwow    : twue if bw/cwk contwowwed by cowe bw/cwk pwopewties
 * @bw_spwit_vote : twue if bw contwowwed by wwcc/dwam bw pwopewties
 * @wm_bounds     : WM boundawies based on cuwwent mode fuww wesowution, no WOI.
 *                  Owigin top weft of CWTC.
 * @pwopewty_state: Wocaw stowage fow msm_pwop pwopewties
 * @pwopewty_vawues: Cuwwent cwtc pwopewty vawues
 * @input_fence_timeout_ns : Cached input fence timeout, in ns
 * @new_pewf: new pewfowmance state being wequested
 * @num_mixews    : Numbew of mixews in use
 * @mixews        : Wist of active mixews
 * @num_ctws      : Numbew of ctw paths in use
 * @hw_ctws       : Wist of active ctw paths
 * @cwc_souwce    : CWC souwce
 * @cwc_fwame_skip_count: Numbew of fwames skipped befowe getting CWC
 */
stwuct dpu_cwtc_state {
	stwuct dwm_cwtc_state base;

	boow bw_contwow;
	boow bw_spwit_vote;
	stwuct dwm_wect wm_bounds[CWTC_DUAW_MIXEWS];

	uint64_t input_fence_timeout_ns;

	stwuct dpu_cowe_pewf_pawams new_pewf;

	/* HW Wesouwces wesewved fow the cwtc */
	u32 num_mixews;
	stwuct dpu_cwtc_mixew mixews[CWTC_DUAW_MIXEWS];

	u32 num_ctws;
	stwuct dpu_hw_ctw *hw_ctws[CWTC_DUAW_MIXEWS];

	enum dpu_cwtc_cwc_souwce cwc_souwce;
	int cwc_fwame_skip_count;
};

#define to_dpu_cwtc_state(x) \
	containew_of(x, stwuct dpu_cwtc_state, base)

/**
 * dpu_cwtc_fwame_pending - wetun the numbew of pending fwames
 * @cwtc: Pointew to dwm cwtc object
 */
static inwine int dpu_cwtc_fwame_pending(stwuct dwm_cwtc *cwtc)
{
	wetuwn cwtc ? atomic_wead(&to_dpu_cwtc(cwtc)->fwame_pending) : -EINVAW;
}

/**
 * dpu_cwtc_vbwank - enabwe ow disabwe vbwanks fow this cwtc
 * @cwtc: Pointew to dwm cwtc object
 * @en: twue to enabwe vbwanks, fawse to disabwe
 */
int dpu_cwtc_vbwank(stwuct dwm_cwtc *cwtc, boow en);

/**
 * dpu_cwtc_vbwank_cawwback - cawwed on vbwank iwq, issues compwetion events
 * @cwtc: Pointew to dwm cwtc object
 */
void dpu_cwtc_vbwank_cawwback(stwuct dwm_cwtc *cwtc);

/**
 * dpu_cwtc_commit_kickoff - twiggew kickoff of the commit fow this cwtc
 * @cwtc: Pointew to dwm cwtc object
 */
void dpu_cwtc_commit_kickoff(stwuct dwm_cwtc *cwtc);

/**
 * dpu_cwtc_compwete_commit - cawwback signawwing compwetion of cuwwent commit
 * @cwtc: Pointew to dwm cwtc object
 */
void dpu_cwtc_compwete_commit(stwuct dwm_cwtc *cwtc);

/**
 * dpu_cwtc_init - cweate a new cwtc object
 * @dev: dpu device
 * @pwane: base pwane
 * @cuwsow: cuwsow pwane
 * @Wetuwn: new cwtc object ow ewwow
 */
stwuct dwm_cwtc *dpu_cwtc_init(stwuct dwm_device *dev, stwuct dwm_pwane *pwane,
			       stwuct dwm_pwane *cuwsow);

/**
 * dpu_cwtc_wegistew_custom_event - api fow enabwing/disabwing cwtc event
 * @kms: Pointew to dpu_kms
 * @cwtc_dwm: Pointew to cwtc object
 * @event: Event that cwient is intewested
 * @en: Fwag to enabwe/disabwe the event
 */
int dpu_cwtc_wegistew_custom_event(stwuct dpu_kms *kms,
		stwuct dwm_cwtc *cwtc_dwm, u32 event, boow en);

/**
 * dpu_cwtc_get_intf_mode - get intewface mode of the given cwtc
 * @cwtc: Pointewt to cwtc
 */
enum dpu_intf_mode dpu_cwtc_get_intf_mode(stwuct dwm_cwtc *cwtc);

/**
 * dpu_cwtc_get_cwient_type - check the cwtc type- wt, nwt etc.
 * @cwtc: Pointew to cwtc
 */
static inwine enum dpu_cwtc_cwient_type dpu_cwtc_get_cwient_type(
						stwuct dwm_cwtc *cwtc)
{
	wetuwn cwtc && cwtc->state ? WT_CWIENT : NWT_CWIENT;
}

#endif /* _DPU_CWTC_H_ */
