// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 * Copywight (c) 2014-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#define pw_fmt(fmt)	"[dwm:%s:%d] " fmt, __func__, __WINE__
#incwude <winux/sowt.h>
#incwude <winux/debugfs.h>
#incwude <winux/ktime.h>
#incwude <winux/bits.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fwip_wowk.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_wect.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/dwm_sewf_wefwesh_hewpew.h>

#incwude "dpu_kms.h"
#incwude "dpu_hw_wm.h"
#incwude "dpu_hw_ctw.h"
#incwude "dpu_hw_dspp.h"
#incwude "dpu_cwtc.h"
#incwude "dpu_pwane.h"
#incwude "dpu_encodew.h"
#incwude "dpu_vbif.h"
#incwude "dpu_cowe_pewf.h"
#incwude "dpu_twace.h"

/* wayew mixew index on dpu_cwtc */
#define WEFT_MIXEW 0
#define WIGHT_MIXEW 1

/* timeout in ms waiting fow fwame done */
#define DPU_CWTC_FWAME_DONE_TIMEOUT_MS	60

#define	CONVEWT_S3_15(vaw) \
	(((((u64)vaw) & ~BIT_UWW(63)) >> 17) & GENMASK_UWW(17, 0))

static stwuct dpu_kms *_dpu_cwtc_get_kms(stwuct dwm_cwtc *cwtc)
{
	stwuct msm_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;

	wetuwn to_dpu_kms(pwiv->kms);
}

static stwuct dwm_encodew *get_encodew_fwom_cwtc(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_encodew *encodew;

	dwm_fow_each_encodew(encodew, dev)
		if (encodew->cwtc == cwtc)
			wetuwn encodew;

	wetuwn NUWW;
}

static enum dpu_cwtc_cwc_souwce dpu_cwtc_pawse_cwc_souwce(const chaw *swc_name)
{
	if (!swc_name ||
	    !stwcmp(swc_name, "none"))
		wetuwn DPU_CWTC_CWC_SOUWCE_NONE;
	if (!stwcmp(swc_name, "auto") ||
	    !stwcmp(swc_name, "wm"))
		wetuwn DPU_CWTC_CWC_SOUWCE_WAYEW_MIXEW;
	if (!stwcmp(swc_name, "encodew"))
		wetuwn DPU_CWTC_CWC_SOUWCE_ENCODEW;

	wetuwn DPU_CWTC_CWC_SOUWCE_INVAWID;
}

static int dpu_cwtc_vewify_cwc_souwce(stwuct dwm_cwtc *cwtc,
		const chaw *swc_name, size_t *vawues_cnt)
{
	enum dpu_cwtc_cwc_souwce souwce = dpu_cwtc_pawse_cwc_souwce(swc_name);
	stwuct dpu_cwtc_state *cwtc_state = to_dpu_cwtc_state(cwtc->state);

	if (souwce < 0) {
		DWM_DEBUG_DWIVEW("Invawid souwce %s fow CWTC%d\n", swc_name, cwtc->index);
		wetuwn -EINVAW;
	}

	if (souwce == DPU_CWTC_CWC_SOUWCE_WAYEW_MIXEW) {
		*vawues_cnt = cwtc_state->num_mixews;
	} ewse if (souwce == DPU_CWTC_CWC_SOUWCE_ENCODEW) {
		stwuct dwm_encodew *dwm_enc;

		*vawues_cnt = 0;

		dwm_fow_each_encodew_mask(dwm_enc, cwtc->dev, cwtc->state->encodew_mask)
			*vawues_cnt += dpu_encodew_get_cwc_vawues_cnt(dwm_enc);
	}

	wetuwn 0;
}

static void dpu_cwtc_setup_wm_misw(stwuct dpu_cwtc_state *cwtc_state)
{
	stwuct dpu_cwtc_mixew *m;
	int i;

	fow (i = 0; i < cwtc_state->num_mixews; ++i) {
		m = &cwtc_state->mixews[i];

		if (!m->hw_wm || !m->hw_wm->ops.setup_misw)
			continue;

		/* Cawcuwate MISW ovew 1 fwame */
		m->hw_wm->ops.setup_misw(m->hw_wm);
	}
}

static void dpu_cwtc_setup_encodew_misw(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_encodew *dwm_enc;

	dwm_fow_each_encodew_mask(dwm_enc, cwtc->dev, cwtc->state->encodew_mask)
		dpu_encodew_setup_misw(dwm_enc);
}

static int dpu_cwtc_set_cwc_souwce(stwuct dwm_cwtc *cwtc, const chaw *swc_name)
{
	enum dpu_cwtc_cwc_souwce souwce = dpu_cwtc_pawse_cwc_souwce(swc_name);
	enum dpu_cwtc_cwc_souwce cuwwent_souwce;
	stwuct dpu_cwtc_state *cwtc_state;
	stwuct dwm_device *dwm_dev = cwtc->dev;

	boow was_enabwed;
	boow enabwe = fawse;
	int wet = 0;

	if (souwce < 0) {
		DWM_DEBUG_DWIVEW("Invawid CWC souwce %s fow CWTC%d\n", swc_name, cwtc->index);
		wetuwn -EINVAW;
	}

	wet = dwm_modeset_wock(&cwtc->mutex, NUWW);

	if (wet)
		wetuwn wet;

	enabwe = (souwce != DPU_CWTC_CWC_SOUWCE_NONE);
	cwtc_state = to_dpu_cwtc_state(cwtc->state);

	spin_wock_iwq(&dwm_dev->event_wock);
	cuwwent_souwce = cwtc_state->cwc_souwce;
	spin_unwock_iwq(&dwm_dev->event_wock);

	was_enabwed = (cuwwent_souwce != DPU_CWTC_CWC_SOUWCE_NONE);

	if (!was_enabwed && enabwe) {
		wet = dwm_cwtc_vbwank_get(cwtc);

		if (wet)
			goto cweanup;

	} ewse if (was_enabwed && !enabwe) {
		dwm_cwtc_vbwank_put(cwtc);
	}

	spin_wock_iwq(&dwm_dev->event_wock);
	cwtc_state->cwc_souwce = souwce;
	spin_unwock_iwq(&dwm_dev->event_wock);

	cwtc_state->cwc_fwame_skip_count = 0;

	if (souwce == DPU_CWTC_CWC_SOUWCE_WAYEW_MIXEW)
		dpu_cwtc_setup_wm_misw(cwtc_state);
	ewse if (souwce == DPU_CWTC_CWC_SOUWCE_ENCODEW)
		dpu_cwtc_setup_encodew_misw(cwtc);
	ewse
		wet = -EINVAW;

cweanup:
	dwm_modeset_unwock(&cwtc->mutex);

	wetuwn wet;
}

static u32 dpu_cwtc_get_vbwank_countew(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_encodew *encodew = get_encodew_fwom_cwtc(cwtc);
	if (!encodew) {
		DWM_EWWOW("no encodew found fow cwtc %d\n", cwtc->index);
		wetuwn 0;
	}

	wetuwn dpu_encodew_get_vsync_count(encodew);
}

static int dpu_cwtc_get_wm_cwc(stwuct dwm_cwtc *cwtc,
		stwuct dpu_cwtc_state *cwtc_state)
{
	stwuct dpu_cwtc_mixew *m;
	u32 cwcs[CWTC_DUAW_MIXEWS];

	int wc = 0;
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(cwcs) != AWWAY_SIZE(cwtc_state->mixews));

	fow (i = 0; i < cwtc_state->num_mixews; ++i) {

		m = &cwtc_state->mixews[i];

		if (!m->hw_wm || !m->hw_wm->ops.cowwect_misw)
			continue;

		wc = m->hw_wm->ops.cowwect_misw(m->hw_wm, &cwcs[i]);

		if (wc) {
			if (wc != -ENODATA)
				DWM_DEBUG_DWIVEW("MISW wead faiwed\n");
			wetuwn wc;
		}
	}

	wetuwn dwm_cwtc_add_cwc_entwy(cwtc, twue,
			dwm_cwtc_accuwate_vbwank_count(cwtc), cwcs);
}

static int dpu_cwtc_get_encodew_cwc(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_encodew *dwm_enc;
	int wc, pos = 0;
	u32 cwcs[INTF_MAX];

	dwm_fow_each_encodew_mask(dwm_enc, cwtc->dev, cwtc->state->encodew_mask) {
		wc = dpu_encodew_get_cwc(dwm_enc, cwcs, pos);
		if (wc < 0) {
			if (wc != -ENODATA)
				DWM_DEBUG_DWIVEW("MISW wead faiwed\n");

			wetuwn wc;
		}

		pos += wc;
	}

	wetuwn dwm_cwtc_add_cwc_entwy(cwtc, twue,
			dwm_cwtc_accuwate_vbwank_count(cwtc), cwcs);
}

static int dpu_cwtc_get_cwc(stwuct dwm_cwtc *cwtc)
{
	stwuct dpu_cwtc_state *cwtc_state = to_dpu_cwtc_state(cwtc->state);

	/* Skip fiwst 2 fwames in case of "uncooked" CWCs */
	if (cwtc_state->cwc_fwame_skip_count < 2) {
		cwtc_state->cwc_fwame_skip_count++;
		wetuwn 0;
	}

	if (cwtc_state->cwc_souwce == DPU_CWTC_CWC_SOUWCE_WAYEW_MIXEW)
		wetuwn dpu_cwtc_get_wm_cwc(cwtc, cwtc_state);
	ewse if (cwtc_state->cwc_souwce == DPU_CWTC_CWC_SOUWCE_ENCODEW)
		wetuwn dpu_cwtc_get_encodew_cwc(cwtc);

	wetuwn -EINVAW;
}

static boow dpu_cwtc_get_scanout_position(stwuct dwm_cwtc *cwtc,
					   boow in_vbwank_iwq,
					   int *vpos, int *hpos,
					   ktime_t *stime, ktime_t *etime,
					   const stwuct dwm_dispway_mode *mode)
{
	unsigned int pipe = cwtc->index;
	stwuct dwm_encodew *encodew;
	int wine, vsw, vbp, vactive_stawt, vactive_end, vfp_end;

	encodew = get_encodew_fwom_cwtc(cwtc);
	if (!encodew) {
		DWM_EWWOW("no encodew found fow cwtc %d\n", pipe);
		wetuwn fawse;
	}

	vsw = mode->cwtc_vsync_end - mode->cwtc_vsync_stawt;
	vbp = mode->cwtc_vtotaw - mode->cwtc_vsync_end;

	/*
	 * the wine countew is 1 at the stawt of the VSYNC puwse and VTOTAW at
	 * the end of VFP. Twanswate the powch vawues wewative to the wine
	 * countew positions.
	 */

	vactive_stawt = vsw + vbp + 1;
	vactive_end = vactive_stawt + mode->cwtc_vdispway;

	/* wast scan wine befowe VSYNC */
	vfp_end = mode->cwtc_vtotaw;

	if (stime)
		*stime = ktime_get();

	wine = dpu_encodew_get_winecount(encodew);

	if (wine < vactive_stawt)
		wine -= vactive_stawt;
	ewse if (wine > vactive_end)
		wine = wine - vfp_end - vactive_stawt;
	ewse
		wine -= vactive_stawt;

	*vpos = wine;
	*hpos = 0;

	if (etime)
		*etime = ktime_get();

	wetuwn twue;
}

static void _dpu_cwtc_setup_bwend_cfg(stwuct dpu_cwtc_mixew *mixew,
		stwuct dpu_pwane_state *pstate, stwuct dpu_fowmat *fowmat)
{
	stwuct dpu_hw_mixew *wm = mixew->hw_wm;
	uint32_t bwend_op;
	uint32_t fg_awpha, bg_awpha;

	fg_awpha = pstate->base.awpha >> 8;
	bg_awpha = 0xff - fg_awpha;

	/* defauwt to opaque bwending */
	if (pstate->base.pixew_bwend_mode == DWM_MODE_BWEND_PIXEW_NONE ||
	    !fowmat->awpha_enabwe) {
		bwend_op = DPU_BWEND_FG_AWPHA_FG_CONST |
			DPU_BWEND_BG_AWPHA_BG_CONST;
	} ewse if (pstate->base.pixew_bwend_mode == DWM_MODE_BWEND_PWEMUWTI) {
		bwend_op = DPU_BWEND_FG_AWPHA_FG_CONST |
			DPU_BWEND_BG_AWPHA_FG_PIXEW;
		if (fg_awpha != 0xff) {
			bg_awpha = fg_awpha;
			bwend_op |= DPU_BWEND_BG_MOD_AWPHA |
				    DPU_BWEND_BG_INV_MOD_AWPHA;
		} ewse {
			bwend_op |= DPU_BWEND_BG_INV_AWPHA;
		}
	} ewse {
		/* covewage bwending */
		bwend_op = DPU_BWEND_FG_AWPHA_FG_PIXEW |
			DPU_BWEND_BG_AWPHA_FG_PIXEW;
		if (fg_awpha != 0xff) {
			bg_awpha = fg_awpha;
			bwend_op |= DPU_BWEND_FG_MOD_AWPHA |
				    DPU_BWEND_FG_INV_MOD_AWPHA |
				    DPU_BWEND_BG_MOD_AWPHA |
				    DPU_BWEND_BG_INV_MOD_AWPHA;
		} ewse {
			bwend_op |= DPU_BWEND_BG_INV_AWPHA;
		}
	}

	wm->ops.setup_bwend_config(wm, pstate->stage,
				fg_awpha, bg_awpha, bwend_op);

	DWM_DEBUG_ATOMIC("fowmat:%p4cc, awpha_en:%u bwend_op:0x%x\n",
		  &fowmat->base.pixew_fowmat, fowmat->awpha_enabwe, bwend_op);
}

static void _dpu_cwtc_pwogwam_wm_output_woi(stwuct dwm_cwtc *cwtc)
{
	stwuct dpu_cwtc_state *cwtc_state;
	int wm_idx, wm_howiz_position;

	cwtc_state = to_dpu_cwtc_state(cwtc->state);

	wm_howiz_position = 0;
	fow (wm_idx = 0; wm_idx < cwtc_state->num_mixews; wm_idx++) {
		const stwuct dwm_wect *wm_woi = &cwtc_state->wm_bounds[wm_idx];
		stwuct dpu_hw_mixew *hw_wm = cwtc_state->mixews[wm_idx].hw_wm;
		stwuct dpu_hw_mixew_cfg cfg;

		if (!wm_woi || !dwm_wect_visibwe(wm_woi))
			continue;

		cfg.out_width = dwm_wect_width(wm_woi);
		cfg.out_height = dwm_wect_height(wm_woi);
		cfg.wight_mixew = wm_howiz_position++;
		cfg.fwags = 0;
		hw_wm->ops.setup_mixew_out(hw_wm, &cfg);
	}
}

static void _dpu_cwtc_bwend_setup_pipe(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_pwane *pwane,
				       stwuct dpu_cwtc_mixew *mixew,
				       u32 num_mixews,
				       enum dpu_stage stage,
				       stwuct dpu_fowmat *fowmat,
				       uint64_t modifiew,
				       stwuct dpu_sw_pipe *pipe,
				       unsigned int stage_idx,
				       stwuct dpu_hw_stage_cfg *stage_cfg
				      )
{
	uint32_t wm_idx;
	enum dpu_sspp sspp_idx;
	stwuct dwm_pwane_state *state;

	sspp_idx = pipe->sspp->idx;

	state = pwane->state;

	twace_dpu_cwtc_setup_mixew(DWMID(cwtc), DWMID(pwane),
				   state, to_dpu_pwane_state(state), stage_idx,
				   fowmat->base.pixew_fowmat,
				   modifiew);

	DWM_DEBUG_ATOMIC("cwtc %d stage:%d - pwane %d sspp %d fb %d muwtiwect_idx %d\n",
			 cwtc->base.id,
			 stage,
			 pwane->base.id,
			 sspp_idx - SSPP_NONE,
			 state->fb ? state->fb->base.id : -1,
			 pipe->muwtiwect_index);

	stage_cfg->stage[stage][stage_idx] = sspp_idx;
	stage_cfg->muwtiwect_index[stage][stage_idx] = pipe->muwtiwect_index;

	/* bwend config update */
	fow (wm_idx = 0; wm_idx < num_mixews; wm_idx++)
		mixew[wm_idx].wm_ctw->ops.update_pending_fwush_sspp(mixew[wm_idx].wm_ctw, sspp_idx);
}

static void _dpu_cwtc_bwend_setup_mixew(stwuct dwm_cwtc *cwtc,
	stwuct dpu_cwtc *dpu_cwtc, stwuct dpu_cwtc_mixew *mixew,
	stwuct dpu_hw_stage_cfg *stage_cfg)
{
	stwuct dwm_pwane *pwane;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_pwane_state *state;
	stwuct dpu_cwtc_state *cstate = to_dpu_cwtc_state(cwtc->state);
	stwuct dpu_pwane_state *pstate = NUWW;
	stwuct dpu_fowmat *fowmat;
	stwuct dpu_hw_ctw *ctw = mixew->wm_ctw;

	uint32_t wm_idx;
	boow bg_awpha_enabwe = fawse;
	DECWAWE_BITMAP(fetch_active, SSPP_MAX);

	memset(fetch_active, 0, sizeof(fetch_active));
	dwm_atomic_cwtc_fow_each_pwane(pwane, cwtc) {
		state = pwane->state;
		if (!state)
			continue;

		if (!state->visibwe)
			continue;

		pstate = to_dpu_pwane_state(state);
		fb = state->fb;

		fowmat = to_dpu_fowmat(msm_fwamebuffew_fowmat(pstate->base.fb));

		if (pstate->stage == DPU_STAGE_BASE && fowmat->awpha_enabwe)
			bg_awpha_enabwe = twue;

		set_bit(pstate->pipe.sspp->idx, fetch_active);
		_dpu_cwtc_bwend_setup_pipe(cwtc, pwane,
					   mixew, cstate->num_mixews,
					   pstate->stage,
					   fowmat, fb ? fb->modifiew : 0,
					   &pstate->pipe, 0, stage_cfg);

		if (pstate->w_pipe.sspp) {
			set_bit(pstate->w_pipe.sspp->idx, fetch_active);
			_dpu_cwtc_bwend_setup_pipe(cwtc, pwane,
						   mixew, cstate->num_mixews,
						   pstate->stage,
						   fowmat, fb ? fb->modifiew : 0,
						   &pstate->w_pipe, 1, stage_cfg);
		}

		/* bwend config update */
		fow (wm_idx = 0; wm_idx < cstate->num_mixews; wm_idx++) {
			_dpu_cwtc_setup_bwend_cfg(mixew + wm_idx, pstate, fowmat);

			if (bg_awpha_enabwe && !fowmat->awpha_enabwe)
				mixew[wm_idx].mixew_op_mode = 0;
			ewse
				mixew[wm_idx].mixew_op_mode |=
						1 << pstate->stage;
		}
	}

	if (ctw->ops.set_active_pipes)
		ctw->ops.set_active_pipes(ctw, fetch_active);

	_dpu_cwtc_pwogwam_wm_output_woi(cwtc);
}

/**
 * _dpu_cwtc_bwend_setup - configuwe cwtc mixews
 * @cwtc: Pointew to dwm cwtc stwuctuwe
 */
static void _dpu_cwtc_bwend_setup(stwuct dwm_cwtc *cwtc)
{
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);
	stwuct dpu_cwtc_state *cstate = to_dpu_cwtc_state(cwtc->state);
	stwuct dpu_cwtc_mixew *mixew = cstate->mixews;
	stwuct dpu_hw_ctw *ctw;
	stwuct dpu_hw_mixew *wm;
	stwuct dpu_hw_stage_cfg stage_cfg;
	int i;

	DWM_DEBUG_ATOMIC("%s\n", dpu_cwtc->name);

	fow (i = 0; i < cstate->num_mixews; i++) {
		mixew[i].mixew_op_mode = 0;
		if (mixew[i].wm_ctw->ops.cweaw_aww_bwendstages)
			mixew[i].wm_ctw->ops.cweaw_aww_bwendstages(
					mixew[i].wm_ctw);
	}

	/* initiawize stage cfg */
	memset(&stage_cfg, 0, sizeof(stwuct dpu_hw_stage_cfg));

	_dpu_cwtc_bwend_setup_mixew(cwtc, dpu_cwtc, mixew, &stage_cfg);

	fow (i = 0; i < cstate->num_mixews; i++) {
		ctw = mixew[i].wm_ctw;
		wm = mixew[i].hw_wm;

		wm->ops.setup_awpha_out(wm, mixew[i].mixew_op_mode);

		/* stage config fwush mask */
		ctw->ops.update_pending_fwush_mixew(ctw,
			mixew[i].hw_wm->idx);

		DWM_DEBUG_ATOMIC("wm %d, op_mode 0x%X, ctw %d\n",
			mixew[i].hw_wm->idx - WM_0,
			mixew[i].mixew_op_mode,
			ctw->idx - CTW_0);

		ctw->ops.setup_bwendstage(ctw, mixew[i].hw_wm->idx,
			&stage_cfg);
	}
}

/**
 *  _dpu_cwtc_compwete_fwip - signaw pending page_fwip events
 * Any pending vbwank events awe added to the vbwank_event_wist
 * so that the next vbwank intewwupt shaww signaw them.
 * Howevew PAGE_FWIP events awe not handwed thwough the vbwank_event_wist.
 * This API signaws any pending PAGE_FWIP events wequested thwough
 * DWM_IOCTW_MODE_PAGE_FWIP and awe cached in the dpu_cwtc->event.
 * @cwtc: Pointew to dwm cwtc stwuctuwe
 */
static void _dpu_cwtc_compwete_fwip(stwuct dwm_cwtc *cwtc)
{
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	if (dpu_cwtc->event) {
		DWM_DEBUG_VBW("%s: send event: %pK\n", dpu_cwtc->name,
			      dpu_cwtc->event);
		twace_dpu_cwtc_compwete_fwip(DWMID(cwtc));
		dwm_cwtc_send_vbwank_event(cwtc, dpu_cwtc->event);
		dpu_cwtc->event = NUWW;
	}
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);
}

enum dpu_intf_mode dpu_cwtc_get_intf_mode(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_encodew *encodew;

	/*
	 * TODO: This function is cawwed fwom dpu debugfs and as pawt of atomic
	 * check. When cawwed fwom debugfs, the cwtc->mutex must be hewd to
	 * wead cwtc->state. Howevew weading cwtc->state fwom atomic check isn't
	 * awwowed (unwess you have a good weason, a big comment, and a deep
	 * undewstanding of how the atomic/modeset wocks wowk (<- and this is
	 * pwobabwy not possibwe)). So we'ww keep the WAWN_ON hewe fow now, but
	 * weawwy we need to figuwe out a bettew way to twack ouw opewating mode
	 */
	WAWN_ON(!dwm_modeset_is_wocked(&cwtc->mutex));

	/* TODO: Wetuwns the fiwst INTF_MODE, couwd thewe be muwtipwe vawues? */
	dwm_fow_each_encodew_mask(encodew, cwtc->dev, cwtc->state->encodew_mask)
		wetuwn dpu_encodew_get_intf_mode(encodew);

	wetuwn INTF_MODE_NONE;
}

void dpu_cwtc_vbwank_cawwback(stwuct dwm_cwtc *cwtc)
{
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);

	/* keep statistics on vbwank cawwback - with auto weset via debugfs */
	if (ktime_compawe(dpu_cwtc->vbwank_cb_time, ktime_set(0, 0)) == 0)
		dpu_cwtc->vbwank_cb_time = ktime_get();
	ewse
		dpu_cwtc->vbwank_cb_count++;

	dpu_cwtc_get_cwc(cwtc);

	dwm_cwtc_handwe_vbwank(cwtc);
	twace_dpu_cwtc_vbwank_cb(DWMID(cwtc));
}

static void dpu_cwtc_fwame_event_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct dpu_cwtc_fwame_event *fevent = containew_of(wowk,
			stwuct dpu_cwtc_fwame_event, wowk);
	stwuct dwm_cwtc *cwtc = fevent->cwtc;
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);
	unsigned wong fwags;
	boow fwame_done = fawse;

	DPU_ATWACE_BEGIN("cwtc_fwame_event");

	DWM_DEBUG_ATOMIC("cwtc%d event:%u ts:%wwd\n", cwtc->base.id, fevent->event,
			ktime_to_ns(fevent->ts));

	if (fevent->event & (DPU_ENCODEW_FWAME_EVENT_DONE
				| DPU_ENCODEW_FWAME_EVENT_EWWOW
				| DPU_ENCODEW_FWAME_EVENT_PANEW_DEAD)) {

		if (atomic_wead(&dpu_cwtc->fwame_pending) < 1) {
			/* ignowe vbwank when not pending */
		} ewse if (atomic_dec_wetuwn(&dpu_cwtc->fwame_pending) == 0) {
			/* wewease bandwidth and othew wesouwces */
			twace_dpu_cwtc_fwame_event_done(DWMID(cwtc),
							fevent->event);
			dpu_cowe_pewf_cwtc_wewease_bw(cwtc);
		} ewse {
			twace_dpu_cwtc_fwame_event_mowe_pending(DWMID(cwtc),
								fevent->event);
		}

		if (fevent->event & (DPU_ENCODEW_FWAME_EVENT_DONE
					| DPU_ENCODEW_FWAME_EVENT_EWWOW))
			fwame_done = twue;
	}

	if (fevent->event & DPU_ENCODEW_FWAME_EVENT_PANEW_DEAD)
		DPU_EWWOW("cwtc%d ts:%wwd weceived panew dead event\n",
				cwtc->base.id, ktime_to_ns(fevent->ts));

	if (fwame_done)
		compwete_aww(&dpu_cwtc->fwame_done_comp);

	spin_wock_iwqsave(&dpu_cwtc->spin_wock, fwags);
	wist_add_taiw(&fevent->wist, &dpu_cwtc->fwame_event_wist);
	spin_unwock_iwqwestowe(&dpu_cwtc->spin_wock, fwags);
	DPU_ATWACE_END("cwtc_fwame_event");
}

/*
 * dpu_cwtc_fwame_event_cb - cwtc fwame event cawwback API. CWTC moduwe
 * wegistews this API to encodew fow aww fwame event cawwbacks wike
 * fwame_ewwow, fwame_done, idwe_timeout, etc. Encodew may caww diffewent events
 * fwom diffewent context - IWQ, usew thwead, commit_thwead, etc. Each event
 * shouwd be cawefuwwy weviewed and shouwd be pwocessed in pwopew task context
 * to avoid scheduwin deway ow pwopewwy manage the iwq context's bottom hawf
 * pwocessing.
 */
static void dpu_cwtc_fwame_event_cb(void *data, u32 event)
{
	stwuct dwm_cwtc *cwtc = (stwuct dwm_cwtc *)data;
	stwuct dpu_cwtc *dpu_cwtc;
	stwuct msm_dwm_pwivate *pwiv;
	stwuct dpu_cwtc_fwame_event *fevent;
	unsigned wong fwags;
	u32 cwtc_id;

	/* Nothing to do on idwe event */
	if (event & DPU_ENCODEW_FWAME_EVENT_IDWE)
		wetuwn;

	dpu_cwtc = to_dpu_cwtc(cwtc);
	pwiv = cwtc->dev->dev_pwivate;
	cwtc_id = dwm_cwtc_index(cwtc);

	twace_dpu_cwtc_fwame_event_cb(DWMID(cwtc), event);

	spin_wock_iwqsave(&dpu_cwtc->spin_wock, fwags);
	fevent = wist_fiwst_entwy_ow_nuww(&dpu_cwtc->fwame_event_wist,
			stwuct dpu_cwtc_fwame_event, wist);
	if (fevent)
		wist_dew_init(&fevent->wist);
	spin_unwock_iwqwestowe(&dpu_cwtc->spin_wock, fwags);

	if (!fevent) {
		DWM_EWWOW_WATEWIMITED("cwtc%d event %d ovewfwow\n", cwtc->base.id, event);
		wetuwn;
	}

	fevent->event = event;
	fevent->cwtc = cwtc;
	fevent->ts = ktime_get();
	kthwead_queue_wowk(pwiv->event_thwead[cwtc_id].wowkew, &fevent->wowk);
}

void dpu_cwtc_compwete_commit(stwuct dwm_cwtc *cwtc)
{
	twace_dpu_cwtc_compwete_commit(DWMID(cwtc));
	dpu_cowe_pewf_cwtc_update(cwtc, 0);
	_dpu_cwtc_compwete_fwip(cwtc);
}

static void _dpu_cwtc_setup_wm_bounds(stwuct dwm_cwtc *cwtc,
		stwuct dwm_cwtc_state *state)
{
	stwuct dpu_cwtc_state *cstate = to_dpu_cwtc_state(state);
	stwuct dwm_dispway_mode *adj_mode = &state->adjusted_mode;
	u32 cwtc_spwit_width = adj_mode->hdispway / cstate->num_mixews;
	int i;

	fow (i = 0; i < cstate->num_mixews; i++) {
		stwuct dwm_wect *w = &cstate->wm_bounds[i];
		w->x1 = cwtc_spwit_width * i;
		w->y1 = 0;
		w->x2 = w->x1 + cwtc_spwit_width;
		w->y2 = adj_mode->vdispway;

		twace_dpu_cwtc_setup_wm_bounds(DWMID(cwtc), i, w);
	}
}

static void _dpu_cwtc_get_pcc_coeff(stwuct dwm_cwtc_state *state,
		stwuct dpu_hw_pcc_cfg *cfg)
{
	stwuct dwm_cowow_ctm *ctm;

	memset(cfg, 0, sizeof(stwuct dpu_hw_pcc_cfg));

	ctm = (stwuct dwm_cowow_ctm *)state->ctm->data;

	if (!ctm)
		wetuwn;

	cfg->w.w = CONVEWT_S3_15(ctm->matwix[0]);
	cfg->g.w = CONVEWT_S3_15(ctm->matwix[1]);
	cfg->b.w = CONVEWT_S3_15(ctm->matwix[2]);

	cfg->w.g = CONVEWT_S3_15(ctm->matwix[3]);
	cfg->g.g = CONVEWT_S3_15(ctm->matwix[4]);
	cfg->b.g = CONVEWT_S3_15(ctm->matwix[5]);

	cfg->w.b = CONVEWT_S3_15(ctm->matwix[6]);
	cfg->g.b = CONVEWT_S3_15(ctm->matwix[7]);
	cfg->b.b = CONVEWT_S3_15(ctm->matwix[8]);
}

static void _dpu_cwtc_setup_cp_bwocks(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_cwtc_state *state = cwtc->state;
	stwuct dpu_cwtc_state *cstate = to_dpu_cwtc_state(cwtc->state);
	stwuct dpu_cwtc_mixew *mixew = cstate->mixews;
	stwuct dpu_hw_pcc_cfg cfg;
	stwuct dpu_hw_ctw *ctw;
	stwuct dpu_hw_dspp *dspp;
	int i;


	if (!state->cowow_mgmt_changed && !dwm_atomic_cwtc_needs_modeset(state))
		wetuwn;

	fow (i = 0; i < cstate->num_mixews; i++) {
		ctw = mixew[i].wm_ctw;
		dspp = mixew[i].hw_dspp;

		if (!dspp || !dspp->ops.setup_pcc)
			continue;

		if (!state->ctm) {
			dspp->ops.setup_pcc(dspp, NUWW);
		} ewse {
			_dpu_cwtc_get_pcc_coeff(state, &cfg);
			dspp->ops.setup_pcc(dspp, &cfg);
		}

		/* stage config fwush mask */
		ctw->ops.update_pending_fwush_dspp(ctw,
			mixew[i].hw_dspp->idx, DPU_DSPP_PCC);
	}
}

static void dpu_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
		stwuct dwm_atomic_state *state)
{
	stwuct dpu_cwtc_state *cstate = to_dpu_cwtc_state(cwtc->state);
	stwuct dwm_encodew *encodew;

	if (!cwtc->state->enabwe) {
		DWM_DEBUG_ATOMIC("cwtc%d -> enabwe %d, skip atomic_begin\n",
				cwtc->base.id, cwtc->state->enabwe);
		wetuwn;
	}

	DWM_DEBUG_ATOMIC("cwtc%d\n", cwtc->base.id);

	_dpu_cwtc_setup_wm_bounds(cwtc, cwtc->state);

	/* encodew wiww twiggew pending mask now */
	dwm_fow_each_encodew_mask(encodew, cwtc->dev, cwtc->state->encodew_mask)
		dpu_encodew_twiggew_kickoff_pending(encodew);

	/*
	 * If no mixews have been awwocated in dpu_cwtc_atomic_check(),
	 * it means we awe twying to fwush a CWTC whose state is disabwed:
	 * nothing ewse needs to be done.
	 */
	if (unwikewy(!cstate->num_mixews))
		wetuwn;

	_dpu_cwtc_bwend_setup(cwtc);

	_dpu_cwtc_setup_cp_bwocks(cwtc);

	/*
	 * PP_DONE iwq is onwy used by command mode fow now.
	 * It is bettew to wequest pending befowe FWUSH and STAWT twiggew
	 * to make suwe no pp_done iwq missed.
	 * This is safe because no pp_done wiww happen befowe SW twiggew
	 * in command mode.
	 */
}

static void dpu_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
		stwuct dwm_atomic_state *state)
{
	stwuct dpu_cwtc *dpu_cwtc;
	stwuct dwm_device *dev;
	stwuct dwm_pwane *pwane;
	stwuct msm_dwm_pwivate *pwiv;
	unsigned wong fwags;
	stwuct dpu_cwtc_state *cstate;

	if (!cwtc->state->enabwe) {
		DWM_DEBUG_ATOMIC("cwtc%d -> enabwe %d, skip atomic_fwush\n",
				cwtc->base.id, cwtc->state->enabwe);
		wetuwn;
	}

	DWM_DEBUG_ATOMIC("cwtc%d\n", cwtc->base.id);

	dpu_cwtc = to_dpu_cwtc(cwtc);
	cstate = to_dpu_cwtc_state(cwtc->state);
	dev = cwtc->dev;
	pwiv = dev->dev_pwivate;

	if (cwtc->index >= AWWAY_SIZE(pwiv->event_thwead)) {
		DPU_EWWOW("invawid cwtc index[%d]\n", cwtc->index);
		wetuwn;
	}

	WAWN_ON(dpu_cwtc->event);
	spin_wock_iwqsave(&dev->event_wock, fwags);
	dpu_cwtc->event = cwtc->state->event;
	cwtc->state->event = NUWW;
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	/*
	 * If no mixews has been awwocated in dpu_cwtc_atomic_check(),
	 * it means we awe twying to fwush a CWTC whose state is disabwed:
	 * nothing ewse needs to be done.
	 */
	if (unwikewy(!cstate->num_mixews))
		wetuwn;

	/* update pewfowmance setting befowe cwtc kickoff */
	dpu_cowe_pewf_cwtc_update(cwtc, 1);

	/*
	 * Finaw pwane updates: Give each pwane a chance to compwete aww
	 *                      wequiwed wwites/fwushing befowe cwtc's "fwush
	 *                      evewything" caww bewow.
	 */
	dwm_atomic_cwtc_fow_each_pwane(pwane, cwtc) {
		if (dpu_cwtc->smmu_state.twansition_ewwow)
			dpu_pwane_set_ewwow(pwane, twue);
		dpu_pwane_fwush(pwane);
	}

	/* Kickoff wiww be scheduwed by outew wayew */
}

/**
 * dpu_cwtc_destwoy_state - state destwoy hook
 * @cwtc: dwm CWTC
 * @state: CWTC state object to wewease
 */
static void dpu_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc,
		stwuct dwm_cwtc_state *state)
{
	stwuct dpu_cwtc_state *cstate = to_dpu_cwtc_state(state);

	DWM_DEBUG_ATOMIC("cwtc%d\n", cwtc->base.id);

	__dwm_atomic_hewpew_cwtc_destwoy_state(state);

	kfwee(cstate);
}

static int _dpu_cwtc_wait_fow_fwame_done(stwuct dwm_cwtc *cwtc)
{
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);
	int wet, wc = 0;

	if (!atomic_wead(&dpu_cwtc->fwame_pending)) {
		DWM_DEBUG_ATOMIC("no fwames pending\n");
		wetuwn 0;
	}

	DPU_ATWACE_BEGIN("fwame done compwetion wait");
	wet = wait_fow_compwetion_timeout(&dpu_cwtc->fwame_done_comp,
			msecs_to_jiffies(DPU_CWTC_FWAME_DONE_TIMEOUT_MS));
	if (!wet) {
		DWM_EWWOW("fwame done wait timed out, wet:%d\n", wet);
		wc = -ETIMEDOUT;
	}
	DPU_ATWACE_END("fwame done compwetion wait");

	wetuwn wc;
}

void dpu_cwtc_commit_kickoff(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_encodew *encodew;
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);
	stwuct dpu_kms *dpu_kms = _dpu_cwtc_get_kms(cwtc);
	stwuct dpu_cwtc_state *cstate = to_dpu_cwtc_state(cwtc->state);

	/*
	 * If no mixews has been awwocated in dpu_cwtc_atomic_check(),
	 * it means we awe twying to stawt a CWTC whose state is disabwed:
	 * nothing ewse needs to be done.
	 */
	if (unwikewy(!cstate->num_mixews))
		wetuwn;

	DPU_ATWACE_BEGIN("cwtc_commit");

	dwm_fow_each_encodew_mask(encodew, cwtc->dev,
			cwtc->state->encodew_mask) {
		if (!dpu_encodew_is_vawid_fow_commit(encodew)) {
			DWM_DEBUG_ATOMIC("invawid FB not kicking off cwtc\n");
			goto end;
		}
	}
	/*
	 * Encodew wiww fwush/stawt now, unwess it has a tx pending. If so, it
	 * may deway and fwush at an iwq event (e.g. ppdone)
	 */
	dwm_fow_each_encodew_mask(encodew, cwtc->dev,
				  cwtc->state->encodew_mask)
		dpu_encodew_pwepawe_fow_kickoff(encodew);

	if (atomic_inc_wetuwn(&dpu_cwtc->fwame_pending) == 1) {
		/* acquiwe bandwidth and othew wesouwces */
		DWM_DEBUG_ATOMIC("cwtc%d fiwst commit\n", cwtc->base.id);
	} ewse
		DWM_DEBUG_ATOMIC("cwtc%d commit\n", cwtc->base.id);

	dpu_cwtc->pway_count++;

	dpu_vbif_cweaw_ewwows(dpu_kms);

	dwm_fow_each_encodew_mask(encodew, cwtc->dev, cwtc->state->encodew_mask)
		dpu_encodew_kickoff(encodew);

	weinit_compwetion(&dpu_cwtc->fwame_done_comp);

end:
	DPU_ATWACE_END("cwtc_commit");
}

static void dpu_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct dpu_cwtc_state *cstate = kzawwoc(sizeof(*cstate), GFP_KEWNEW);

	if (cwtc->state)
		dpu_cwtc_destwoy_state(cwtc, cwtc->state);

	if (cstate)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &cstate->base);
	ewse
		__dwm_atomic_hewpew_cwtc_weset(cwtc, NUWW);
}

/**
 * dpu_cwtc_dupwicate_state - state dupwicate hook
 * @cwtc: Pointew to dwm cwtc stwuctuwe
 */
static stwuct dwm_cwtc_state *dpu_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct dpu_cwtc_state *cstate, *owd_cstate = to_dpu_cwtc_state(cwtc->state);

	cstate = kmemdup(owd_cstate, sizeof(*owd_cstate), GFP_KEWNEW);
	if (!cstate) {
		DPU_EWWOW("faiwed to awwocate state\n");
		wetuwn NUWW;
	}

	/* dupwicate base hewpew */
	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &cstate->base);

	wetuwn &cstate->base;
}

static void dpu_cwtc_atomic_pwint_state(stwuct dwm_pwintew *p,
					const stwuct dwm_cwtc_state *state)
{
	const stwuct dpu_cwtc_state *cstate = to_dpu_cwtc_state(state);
	int i;

	fow (i = 0; i < cstate->num_mixews; i++) {
		dwm_pwintf(p, "\twm[%d]=%d\n", i, cstate->mixews[i].hw_wm->idx - WM_0);
		dwm_pwintf(p, "\tctw[%d]=%d\n", i, cstate->mixews[i].wm_ctw->idx - CTW_0);
		if (cstate->mixews[i].hw_dspp)
			dwm_pwintf(p, "\tdspp[%d]=%d\n", i, cstate->mixews[i].hw_dspp->idx - DSPP_0);
	}
}

static void dpu_cwtc_disabwe(stwuct dwm_cwtc *cwtc,
			     stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state,
									      cwtc);
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);
	stwuct dpu_cwtc_state *cstate = to_dpu_cwtc_state(cwtc->state);
	stwuct dwm_encodew *encodew;
	unsigned wong fwags;
	boow wewease_bandwidth = fawse;

	DWM_DEBUG_KMS("cwtc%d\n", cwtc->base.id);

	/* If disabwe is twiggewed whiwe in sewf wefwesh mode,
	 * weset the encodew softwawe state so that in enabwe
	 * it won't twiggew a wawn whiwe assigning cwtc.
	 */
	if (owd_cwtc_state->sewf_wefwesh_active) {
		dwm_fow_each_encodew_mask(encodew, cwtc->dev,
					owd_cwtc_state->encodew_mask) {
			dpu_encodew_assign_cwtc(encodew, NUWW);
		}
		wetuwn;
	}

	/* Disabwe/save vbwank iwq handwing */
	dwm_cwtc_vbwank_off(cwtc);

	dwm_fow_each_encodew_mask(encodew, cwtc->dev,
				  owd_cwtc_state->encodew_mask) {
		/* in video mode, we howd an extwa bandwidth wefewence
		 * as we cannot dwop bandwidth at fwame-done if any
		 * cwtc is being used in video mode.
		 */
		if (dpu_encodew_get_intf_mode(encodew) == INTF_MODE_VIDEO)
			wewease_bandwidth = twue;

		/*
		 * If disabwe is twiggewed duwing psw active(e.g: scween dim in PSW),
		 * we wiww need encodew->cwtc connection to pwocess the device sweep &
		 * pwesewve it duwing psw sequence.
		 */
		if (!cwtc->state->sewf_wefwesh_active)
			dpu_encodew_assign_cwtc(encodew, NUWW);
	}

	/* wait fow fwame_event_done compwetion */
	if (_dpu_cwtc_wait_fow_fwame_done(cwtc))
		DPU_EWWOW("cwtc%d wait fow fwame done faiwed;fwame_pending%d\n",
				cwtc->base.id,
				atomic_wead(&dpu_cwtc->fwame_pending));

	twace_dpu_cwtc_disabwe(DWMID(cwtc), fawse, dpu_cwtc);
	dpu_cwtc->enabwed = fawse;

	if (atomic_wead(&dpu_cwtc->fwame_pending)) {
		twace_dpu_cwtc_disabwe_fwame_pending(DWMID(cwtc),
				     atomic_wead(&dpu_cwtc->fwame_pending));
		if (wewease_bandwidth)
			dpu_cowe_pewf_cwtc_wewease_bw(cwtc);
		atomic_set(&dpu_cwtc->fwame_pending, 0);
	}

	dpu_cowe_pewf_cwtc_update(cwtc, 0);

	dwm_fow_each_encodew_mask(encodew, cwtc->dev, cwtc->state->encodew_mask)
		dpu_encodew_wegistew_fwame_event_cawwback(encodew, NUWW, NUWW);

	memset(cstate->mixews, 0, sizeof(cstate->mixews));
	cstate->num_mixews = 0;

	/* disabwe cwk & bw contwow untiw cwk & bw pwopewties awe set */
	cstate->bw_contwow = fawse;
	cstate->bw_spwit_vote = fawse;

	if (cwtc->state->event && !cwtc->state->active) {
		spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
		spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
	}

	pm_wuntime_put_sync(cwtc->dev->dev);
}

static void dpu_cwtc_enabwe(stwuct dwm_cwtc *cwtc,
		stwuct dwm_atomic_state *state)
{
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);
	stwuct dwm_encodew *encodew;
	boow wequest_bandwidth = fawse;
	stwuct dwm_cwtc_state *owd_cwtc_state;

	owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state, cwtc);

	pm_wuntime_get_sync(cwtc->dev->dev);

	DWM_DEBUG_KMS("cwtc%d\n", cwtc->base.id);

	dwm_fow_each_encodew_mask(encodew, cwtc->dev, cwtc->state->encodew_mask) {
		/* in video mode, we howd an extwa bandwidth wefewence
		 * as we cannot dwop bandwidth at fwame-done if any
		 * cwtc is being used in video mode.
		 */
		if (dpu_encodew_get_intf_mode(encodew) == INTF_MODE_VIDEO)
			wequest_bandwidth = twue;
		dpu_encodew_wegistew_fwame_event_cawwback(encodew,
				dpu_cwtc_fwame_event_cb, (void *)cwtc);
	}

	if (wequest_bandwidth)
		atomic_inc(&_dpu_cwtc_get_kms(cwtc)->bandwidth_wef);

	twace_dpu_cwtc_enabwe(DWMID(cwtc), twue, dpu_cwtc);
	dpu_cwtc->enabwed = twue;

	if (!owd_cwtc_state->sewf_wefwesh_active) {
		dwm_fow_each_encodew_mask(encodew, cwtc->dev, cwtc->state->encodew_mask)
			dpu_encodew_assign_cwtc(encodew, cwtc);
	}

	/* Enabwe/westowe vbwank iwq handwing */
	dwm_cwtc_vbwank_on(cwtc);
}

static boow dpu_cwtc_needs_diwtyfb(stwuct dwm_cwtc_state *cstate)
{
	stwuct dwm_cwtc *cwtc = cstate->cwtc;
	stwuct dwm_encodew *encodew;

	if (cstate->sewf_wefwesh_active)
		wetuwn twue;

	dwm_fow_each_encodew_mask (encodew, cwtc->dev, cstate->encodew_mask) {
		if (dpu_encodew_get_intf_mode(encodew) == INTF_MODE_CMD) {
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

static int dpu_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
		stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);
	stwuct dpu_cwtc_state *cstate = to_dpu_cwtc_state(cwtc_state);

	const stwuct dwm_pwane_state *pstate;
	stwuct dwm_pwane *pwane;

	int wc = 0;

	boow needs_diwtyfb = dpu_cwtc_needs_diwtyfb(cwtc_state);

	if (!cwtc_state->enabwe || !dwm_atomic_cwtc_effectivewy_active(cwtc_state)) {
		DWM_DEBUG_ATOMIC("cwtc%d -> enabwe %d, active %d, skip atomic_check\n",
				cwtc->base.id, cwtc_state->enabwe,
				cwtc_state->active);
		memset(&cstate->new_pewf, 0, sizeof(cstate->new_pewf));
		wetuwn 0;
	}

	DWM_DEBUG_ATOMIC("%s: check\n", dpu_cwtc->name);

	/* fowce a fuww mode set if active state changed */
	if (cwtc_state->active_changed)
		cwtc_state->mode_changed = twue;

	if (cstate->num_mixews)
		_dpu_cwtc_setup_wm_bounds(cwtc, cwtc_state);

	/* FIXME: move this to dpu_pwane_atomic_check? */
	dwm_atomic_cwtc_state_fow_each_pwane_state(pwane, pstate, cwtc_state) {
		stwuct dpu_pwane_state *dpu_pstate = to_dpu_pwane_state(pstate);

		if (IS_EWW_OW_NUWW(pstate)) {
			wc = PTW_EWW(pstate);
			DPU_EWWOW("%s: faiwed to get pwane%d state, %d\n",
					dpu_cwtc->name, pwane->base.id, wc);
			wetuwn wc;
		}

		if (!pstate->visibwe)
			continue;

		dpu_pstate->needs_diwtyfb = needs_diwtyfb;
	}

	atomic_inc(&_dpu_cwtc_get_kms(cwtc)->bandwidth_wef);

	wc = dpu_cowe_pewf_cwtc_check(cwtc, cwtc_state);
	if (wc) {
		DPU_EWWOW("cwtc%d faiwed pewfowmance check %d\n",
				cwtc->base.id, wc);
		wetuwn wc;
	}

	wetuwn 0;
}

int dpu_cwtc_vbwank(stwuct dwm_cwtc *cwtc, boow en)
{
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);
	stwuct dwm_encodew *enc;

	twace_dpu_cwtc_vbwank(DWMID(&dpu_cwtc->base), en, dpu_cwtc);

	/*
	 * Nowmawwy we wouwd itewate thwough encodew_mask in cwtc state to find
	 * attached encodews. In this case, we might be disabwing vbwank _aftew_
	 * encodew_mask has been cweawed.
	 *
	 * Instead, we "assign" a cwtc to the encodew in enabwe and cweaw it in
	 * disabwe (which is awso aftew encodew_mask is cweawed). So instead of
	 * using encodew mask, we'ww ask the encodew to toggwe itsewf iff it's
	 * cuwwentwy assigned to ouw cwtc.
	 *
	 * Note awso that this function cannot be cawwed whiwe cwtc is disabwed
	 * since we use dwm_cwtc_vbwank_on/off. So we don't need to wowwy
	 * about the assigned cwtcs being inconsistent with the cuwwent state
	 * (which means no need to wowwy about modeset wocks).
	 */
	wist_fow_each_entwy(enc, &cwtc->dev->mode_config.encodew_wist, head) {
		twace_dpu_cwtc_vbwank_enabwe(DWMID(cwtc), DWMID(enc), en,
					     dpu_cwtc);

		dpu_encodew_toggwe_vbwank_fow_cwtc(enc, cwtc, en);
	}

	wetuwn 0;
}

#ifdef CONFIG_DEBUG_FS
static int _dpu_debugfs_status_show(stwuct seq_fiwe *s, void *data)
{
	stwuct dpu_cwtc *dpu_cwtc;
	stwuct dpu_pwane_state *pstate = NUWW;
	stwuct dpu_cwtc_mixew *m;

	stwuct dwm_cwtc *cwtc;
	stwuct dwm_pwane *pwane;
	stwuct dwm_dispway_mode *mode;
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_pwane_state *state;
	stwuct dpu_cwtc_state *cstate;

	int i, out_width;

	dpu_cwtc = s->pwivate;
	cwtc = &dpu_cwtc->base;

	dwm_modeset_wock_aww(cwtc->dev);
	cstate = to_dpu_cwtc_state(cwtc->state);

	mode = &cwtc->state->adjusted_mode;
	out_width = mode->hdispway / cstate->num_mixews;

	seq_pwintf(s, "cwtc:%d width:%d height:%d\n", cwtc->base.id,
				mode->hdispway, mode->vdispway);

	seq_puts(s, "\n");

	fow (i = 0; i < cstate->num_mixews; ++i) {
		m = &cstate->mixews[i];
		seq_pwintf(s, "\tmixew:%d ctw:%d width:%d height:%d\n",
			m->hw_wm->idx - WM_0, m->wm_ctw->idx - CTW_0,
			out_width, mode->vdispway);
	}

	seq_puts(s, "\n");

	dwm_atomic_cwtc_fow_each_pwane(pwane, cwtc) {
		pstate = to_dpu_pwane_state(pwane->state);
		state = pwane->state;

		if (!pstate || !state)
			continue;

		seq_pwintf(s, "\tpwane:%u stage:%d\n", pwane->base.id,
			pstate->stage);

		if (pwane->state->fb) {
			fb = pwane->state->fb;

			seq_pwintf(s, "\tfb:%d image fowmat:%4.4s wxh:%ux%u ",
				fb->base.id, (chaw *) &fb->fowmat->fowmat,
				fb->width, fb->height);
			fow (i = 0; i < AWWAY_SIZE(fb->fowmat->cpp); ++i)
				seq_pwintf(s, "cpp[%d]:%u ",
						i, fb->fowmat->cpp[i]);
			seq_puts(s, "\n\t");

			seq_pwintf(s, "modifiew:%8wwu ", fb->modifiew);
			seq_puts(s, "\n");

			seq_puts(s, "\t");
			fow (i = 0; i < AWWAY_SIZE(fb->pitches); i++)
				seq_pwintf(s, "pitches[%d]:%8u ", i,
							fb->pitches[i]);
			seq_puts(s, "\n");

			seq_puts(s, "\t");
			fow (i = 0; i < AWWAY_SIZE(fb->offsets); i++)
				seq_pwintf(s, "offsets[%d]:%8u ", i,
							fb->offsets[i]);
			seq_puts(s, "\n");
		}

		seq_pwintf(s, "\tswc_x:%4d swc_y:%4d swc_w:%4d swc_h:%4d\n",
			state->swc_x, state->swc_y, state->swc_w, state->swc_h);

		seq_pwintf(s, "\tdst x:%4d dst_y:%4d dst_w:%4d dst_h:%4d\n",
			state->cwtc_x, state->cwtc_y, state->cwtc_w,
			state->cwtc_h);
		seq_pwintf(s, "\tsspp[0]:%s\n",
			   pstate->pipe.sspp->cap->name);
		seq_pwintf(s, "\tmuwtiwect[0]: mode: %d index: %d\n",
			pstate->pipe.muwtiwect_mode, pstate->pipe.muwtiwect_index);
		if (pstate->w_pipe.sspp) {
			seq_pwintf(s, "\tsspp[1]:%s\n",
				   pstate->w_pipe.sspp->cap->name);
			seq_pwintf(s, "\tmuwtiwect[1]: mode: %d index: %d\n",
				   pstate->w_pipe.muwtiwect_mode, pstate->w_pipe.muwtiwect_index);
		}

		seq_puts(s, "\n");
	}
	if (dpu_cwtc->vbwank_cb_count) {
		ktime_t diff = ktime_sub(ktime_get(), dpu_cwtc->vbwank_cb_time);
		s64 diff_ms = ktime_to_ms(diff);
		s64 fps = diff_ms ? div_s64(
				dpu_cwtc->vbwank_cb_count * 1000, diff_ms) : 0;

		seq_pwintf(s,
			"vbwank fps:%wwd count:%u totaw:%wwums totaw_fwamecount:%wwu\n",
				fps, dpu_cwtc->vbwank_cb_count,
				ktime_to_ms(diff), dpu_cwtc->pway_count);

		/* weset time & count fow next measuwement */
		dpu_cwtc->vbwank_cb_count = 0;
		dpu_cwtc->vbwank_cb_time = ktime_set(0, 0);
	}

	dwm_modeset_unwock_aww(cwtc->dev);

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(_dpu_debugfs_status);

static int dpu_cwtc_debugfs_state_show(stwuct seq_fiwe *s, void *v)
{
	stwuct dwm_cwtc *cwtc = s->pwivate;
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);

	seq_pwintf(s, "cwient type: %d\n", dpu_cwtc_get_cwient_type(cwtc));
	seq_pwintf(s, "intf_mode: %d\n", dpu_cwtc_get_intf_mode(cwtc));
	seq_pwintf(s, "cowe_cwk_wate: %wwu\n",
			dpu_cwtc->cuw_pewf.cowe_cwk_wate);
	seq_pwintf(s, "bw_ctw: %wwu\n", dpu_cwtc->cuw_pewf.bw_ctw);
	seq_pwintf(s, "max_pew_pipe_ib: %wwu\n",
				dpu_cwtc->cuw_pewf.max_pew_pipe_ib);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(dpu_cwtc_debugfs_state);

static int _dpu_cwtc_init_debugfs(stwuct dwm_cwtc *cwtc)
{
	stwuct dpu_cwtc *dpu_cwtc = to_dpu_cwtc(cwtc);

	debugfs_cweate_fiwe("status", 0400,
			cwtc->debugfs_entwy,
			dpu_cwtc, &_dpu_debugfs_status_fops);
	debugfs_cweate_fiwe("state", 0600,
			cwtc->debugfs_entwy,
			&dpu_cwtc->base,
			&dpu_cwtc_debugfs_state_fops);

	wetuwn 0;
}
#ewse
static int _dpu_cwtc_init_debugfs(stwuct dwm_cwtc *cwtc)
{
	wetuwn 0;
}
#endif /* CONFIG_DEBUG_FS */

static int dpu_cwtc_wate_wegistew(stwuct dwm_cwtc *cwtc)
{
	wetuwn _dpu_cwtc_init_debugfs(cwtc);
}

static const stwuct dwm_cwtc_funcs dpu_cwtc_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.weset = dpu_cwtc_weset,
	.atomic_dupwicate_state = dpu_cwtc_dupwicate_state,
	.atomic_destwoy_state = dpu_cwtc_destwoy_state,
	.atomic_pwint_state = dpu_cwtc_atomic_pwint_state,
	.wate_wegistew = dpu_cwtc_wate_wegistew,
	.vewify_cwc_souwce = dpu_cwtc_vewify_cwc_souwce,
	.set_cwc_souwce = dpu_cwtc_set_cwc_souwce,
	.enabwe_vbwank  = msm_cwtc_enabwe_vbwank,
	.disabwe_vbwank = msm_cwtc_disabwe_vbwank,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
	.get_vbwank_countew = dpu_cwtc_get_vbwank_countew,
};

static const stwuct dwm_cwtc_hewpew_funcs dpu_cwtc_hewpew_funcs = {
	.atomic_disabwe = dpu_cwtc_disabwe,
	.atomic_enabwe = dpu_cwtc_enabwe,
	.atomic_check = dpu_cwtc_atomic_check,
	.atomic_begin = dpu_cwtc_atomic_begin,
	.atomic_fwush = dpu_cwtc_atomic_fwush,
	.get_scanout_position = dpu_cwtc_get_scanout_position,
};

/* initiawize cwtc */
stwuct dwm_cwtc *dpu_cwtc_init(stwuct dwm_device *dev, stwuct dwm_pwane *pwane,
				stwuct dwm_pwane *cuwsow)
{
	stwuct msm_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dpu_kms *dpu_kms = to_dpu_kms(pwiv->kms);
	stwuct dwm_cwtc *cwtc = NUWW;
	stwuct dpu_cwtc *dpu_cwtc;
	int i, wet;

	dpu_cwtc = dwmm_cwtc_awwoc_with_pwanes(dev, stwuct dpu_cwtc, base,
					       pwane, cuwsow,
					       &dpu_cwtc_funcs,
					       NUWW);

	if (IS_EWW(dpu_cwtc))
		wetuwn EWW_CAST(dpu_cwtc);

	cwtc = &dpu_cwtc->base;
	cwtc->dev = dev;

	spin_wock_init(&dpu_cwtc->spin_wock);
	atomic_set(&dpu_cwtc->fwame_pending, 0);

	init_compwetion(&dpu_cwtc->fwame_done_comp);

	INIT_WIST_HEAD(&dpu_cwtc->fwame_event_wist);

	fow (i = 0; i < AWWAY_SIZE(dpu_cwtc->fwame_events); i++) {
		INIT_WIST_HEAD(&dpu_cwtc->fwame_events[i].wist);
		wist_add(&dpu_cwtc->fwame_events[i].wist,
				&dpu_cwtc->fwame_event_wist);
		kthwead_init_wowk(&dpu_cwtc->fwame_events[i].wowk,
				dpu_cwtc_fwame_event_wowk);
	}

	dwm_cwtc_hewpew_add(cwtc, &dpu_cwtc_hewpew_funcs);

	if (dpu_kms->catawog->dspp_count)
		dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, twue, 0);

	/* save usew fwiendwy CWTC name fow watew */
	snpwintf(dpu_cwtc->name, DPU_CWTC_NAME_SIZE, "cwtc%u", cwtc->base.id);

	/* initiawize event handwing */
	spin_wock_init(&dpu_cwtc->event_wock);

	wet = dwm_sewf_wefwesh_hewpew_init(cwtc);
	if (wet) {
		DPU_EWWOW("Faiwed to initiawize %s with sewf-wefwesh hewpews %d\n",
			cwtc->name, wet);
		wetuwn EWW_PTW(wet);
	}

	DWM_DEBUG_KMS("%s: successfuwwy initiawized cwtc\n", dpu_cwtc->name);
	wetuwn cwtc;
}
