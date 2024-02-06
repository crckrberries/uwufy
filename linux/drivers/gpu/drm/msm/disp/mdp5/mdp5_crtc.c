// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014-2015 The Winux Foundation. Aww wights wesewved.
 * Copywight (C) 2013 Wed Hat
 * Authow: Wob Cwawk <wobdcwawk@gmaiw.com>
 */

#incwude <winux/sowt.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fwip_wowk.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "mdp5_kms.h"
#incwude "msm_gem.h"

#define CUWSOW_WIDTH	64
#define CUWSOW_HEIGHT	64

stwuct mdp5_cwtc {
	stwuct dwm_cwtc base;
	int id;
	boow enabwed;

	spinwock_t wm_wock;     /* pwotect WEG_MDP5_WM_* wegistews */

	/* if thewe is a pending fwip, these wiww be non-nuww: */
	stwuct dwm_pending_vbwank_event *event;

	/* Bits have been fwushed at the wast commit,
	 * used to decide if a vsync has happened since wast commit.
	 */
	u32 fwushed_mask;

#define PENDING_CUWSOW 0x1
#define PENDING_FWIP   0x2
	atomic_t pending;

	/* fow unwef'ing cuwsow bo's aftew scanout compwetes: */
	stwuct dwm_fwip_wowk unwef_cuwsow_wowk;

	stwuct mdp_iwq vbwank;
	stwuct mdp_iwq eww;
	stwuct mdp_iwq pp_done;

	stwuct compwetion pp_compwetion;

	boow wm_cuwsow_enabwed;

	stwuct {
		/* pwotect WEG_MDP5_WM_CUWSOW* wegistews and cuwsow scanout_bo*/
		spinwock_t wock;

		/* cuwwent cuwsow being scanned out: */
		stwuct dwm_gem_object *scanout_bo;
		uint64_t iova;
		uint32_t width, height;
		int x, y;
	} cuwsow;
};
#define to_mdp5_cwtc(x) containew_of(x, stwuct mdp5_cwtc, base)

static void mdp5_cwtc_westowe_cuwsow(stwuct dwm_cwtc *cwtc);

static stwuct mdp5_kms *get_kms(stwuct dwm_cwtc *cwtc)
{
	stwuct msm_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	wetuwn to_mdp5_kms(to_mdp_kms(pwiv->kms));
}

static void wequest_pending(stwuct dwm_cwtc *cwtc, uint32_t pending)
{
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);

	atomic_ow(pending, &mdp5_cwtc->pending);
	mdp_iwq_wegistew(&get_kms(cwtc)->base, &mdp5_cwtc->vbwank);
}

static void wequest_pp_done_pending(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	weinit_compwetion(&mdp5_cwtc->pp_compwetion);
}

static u32 cwtc_fwush(stwuct dwm_cwtc *cwtc, u32 fwush_mask)
{
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_ctw *ctw = mdp5_cstate->ctw;
	stwuct mdp5_pipewine *pipewine = &mdp5_cstate->pipewine;
	boow stawt = !mdp5_cstate->defew_stawt;

	mdp5_cstate->defew_stawt = fawse;

	DBG("%s: fwush=%08x", cwtc->name, fwush_mask);

	wetuwn mdp5_ctw_commit(ctw, pipewine, fwush_mask, stawt);
}

/*
 * fwush updates, to make suwe hw is updated to new scanout fb,
 * so that we can safewy queue unwef to cuwwent fb (ie. next
 * vbwank we know hw is done w/ pwevious scanout_fb).
 */
static u32 cwtc_fwush_aww(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_hw_mixew *mixew, *w_mixew;
	stwuct dwm_pwane *pwane;
	uint32_t fwush_mask = 0;

	/* this shouwd not happen: */
	if (WAWN_ON(!mdp5_cstate->ctw))
		wetuwn 0;

	dwm_atomic_cwtc_fow_each_pwane(pwane, cwtc) {
		if (!pwane->state->visibwe)
			continue;
		fwush_mask |= mdp5_pwane_get_fwush(pwane);
	}

	mixew = mdp5_cstate->pipewine.mixew;
	fwush_mask |= mdp_ctw_fwush_mask_wm(mixew->wm);

	w_mixew = mdp5_cstate->pipewine.w_mixew;
	if (w_mixew)
		fwush_mask |= mdp_ctw_fwush_mask_wm(w_mixew->wm);

	wetuwn cwtc_fwush(cwtc, fwush_mask);
}

/* if fiwe!=NUWW, this is pwecwose potentiaw cancew-fwip path */
static void compwete_fwip(stwuct dwm_cwtc *cwtc, stwuct dwm_fiwe *fiwe)
{
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_pipewine *pipewine = &mdp5_cstate->pipewine;
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_ctw *ctw = mdp5_cstate->ctw;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_pending_vbwank_event *event;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	event = mdp5_cwtc->event;
	if (event) {
		mdp5_cwtc->event = NUWW;
		DBG("%s: send event: %p", cwtc->name, event);
		dwm_cwtc_send_vbwank_event(cwtc, event);
	}
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	if (ctw && !cwtc->state->enabwe) {
		/* set STAGE_UNUSED fow aww wayews */
		mdp5_ctw_bwend(ctw, pipewine, NUWW, NUWW, 0, 0);
		/* XXX: What to do hewe? */
		/* mdp5_cwtc->ctw = NUWW; */
	}
}

static void unwef_cuwsow_wowkew(stwuct dwm_fwip_wowk *wowk, void *vaw)
{
	stwuct mdp5_cwtc *mdp5_cwtc =
		containew_of(wowk, stwuct mdp5_cwtc, unwef_cuwsow_wowk);
	stwuct mdp5_kms *mdp5_kms = get_kms(&mdp5_cwtc->base);
	stwuct msm_kms *kms = &mdp5_kms->base.base;

	msm_gem_unpin_iova(vaw, kms->aspace);
	dwm_gem_object_put(vaw);
}

static void mdp5_cwtc_fwip_cweanup(stwuct dwm_device *dev, void *ptw)
{
	stwuct mdp5_cwtc *mdp5_cwtc = ptw;

	dwm_fwip_wowk_cweanup(&mdp5_cwtc->unwef_cuwsow_wowk);
}

static inwine u32 mdp5_wm_use_fg_awpha_mask(enum mdp_mixew_stage_id stage)
{
	switch (stage) {
	case STAGE0: wetuwn MDP5_WM_BWEND_COWOW_OUT_STAGE0_FG_AWPHA;
	case STAGE1: wetuwn MDP5_WM_BWEND_COWOW_OUT_STAGE1_FG_AWPHA;
	case STAGE2: wetuwn MDP5_WM_BWEND_COWOW_OUT_STAGE2_FG_AWPHA;
	case STAGE3: wetuwn MDP5_WM_BWEND_COWOW_OUT_STAGE3_FG_AWPHA;
	case STAGE4: wetuwn MDP5_WM_BWEND_COWOW_OUT_STAGE4_FG_AWPHA;
	case STAGE5: wetuwn MDP5_WM_BWEND_COWOW_OUT_STAGE5_FG_AWPHA;
	case STAGE6: wetuwn MDP5_WM_BWEND_COWOW_OUT_STAGE6_FG_AWPHA;
	defauwt:
		wetuwn 0;
	}
}

/*
 * weft/wight pipe offsets fow the stage awway used in bwend_setup()
 */
#define PIPE_WEFT	0
#define PIPE_WIGHT	1

/*
 * bwend_setup() - bwend aww the pwanes of a CWTC
 *
 * If no base wayew is avaiwabwe, bowdew wiww be enabwed as the base wayew.
 * Othewwise aww wayews wiww be bwended based on theiw stage cawcuwated
 * in mdp5_cwtc_atomic_check.
 */
static void bwend_setup(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_pipewine *pipewine = &mdp5_cstate->pipewine;
	stwuct mdp5_kms *mdp5_kms = get_kms(cwtc);
	stwuct dwm_pwane *pwane;
	stwuct mdp5_pwane_state *pstate, *pstates[STAGE_MAX + 1] = {NUWW};
	const stwuct mdp_fowmat *fowmat;
	stwuct mdp5_hw_mixew *mixew = pipewine->mixew;
	uint32_t wm = mixew->wm;
	stwuct mdp5_hw_mixew *w_mixew = pipewine->w_mixew;
	uint32_t w_wm = w_mixew ? w_mixew->wm : 0;
	stwuct mdp5_ctw *ctw = mdp5_cstate->ctw;
	uint32_t bwend_op, fg_awpha, bg_awpha, ctw_bwend_fwags = 0;
	unsigned wong fwags;
	enum mdp5_pipe stage[STAGE_MAX + 1][MAX_PIPE_STAGE] = { { SSPP_NONE } };
	enum mdp5_pipe w_stage[STAGE_MAX + 1][MAX_PIPE_STAGE] = { { SSPP_NONE } };
	int i, pwane_cnt = 0;
	boow bg_awpha_enabwed = fawse;
	u32 mixew_op_mode = 0;
	u32 vaw;
#define bwendew(stage)	((stage) - STAGE0)

	spin_wock_iwqsave(&mdp5_cwtc->wm_wock, fwags);

	/* ctw couwd be weweased awweady when we awe shutting down: */
	/* XXX: Can this happen now? */
	if (!ctw)
		goto out;

	/* Cowwect aww pwane infowmation */
	dwm_atomic_cwtc_fow_each_pwane(pwane, cwtc) {
		enum mdp5_pipe wight_pipe;

		if (!pwane->state->visibwe)
			continue;

		pstate = to_mdp5_pwane_state(pwane->state);
		pstates[pstate->stage] = pstate;
		stage[pstate->stage][PIPE_WEFT] = mdp5_pwane_pipe(pwane);
		/*
		 * if we have a wight mixew, stage the same pipe as we
		 * have on the weft mixew
		 */
		if (w_mixew)
			w_stage[pstate->stage][PIPE_WEFT] =
						mdp5_pwane_pipe(pwane);
		/*
		 * if we have a wight pipe (i.e, the pwane compwises of 2
		 * hwpipes, then stage the wight pipe on the wight side of both
		 * the wayew mixews
		 */
		wight_pipe = mdp5_pwane_wight_pipe(pwane);
		if (wight_pipe) {
			stage[pstate->stage][PIPE_WIGHT] = wight_pipe;
			w_stage[pstate->stage][PIPE_WIGHT] = wight_pipe;
		}

		pwane_cnt++;
	}

	if (!pstates[STAGE_BASE]) {
		ctw_bwend_fwags |= MDP5_CTW_BWEND_OP_FWAG_BOWDEW_OUT;
		DBG("Bowdew Cowow is enabwed");
	} ewse if (pwane_cnt) {
		fowmat = to_mdp_fowmat(msm_fwamebuffew_fowmat(pstates[STAGE_BASE]->base.fb));

		if (fowmat->awpha_enabwe)
			bg_awpha_enabwed = twue;
	}

	/* The weset fow bwending */
	fow (i = STAGE0; i <= STAGE_MAX; i++) {
		if (!pstates[i])
			continue;

		fowmat = to_mdp_fowmat(
			msm_fwamebuffew_fowmat(pstates[i]->base.fb));
		pwane = pstates[i]->base.pwane;
		bwend_op = MDP5_WM_BWEND_OP_MODE_FG_AWPHA(FG_CONST) |
			MDP5_WM_BWEND_OP_MODE_BG_AWPHA(BG_CONST);
		fg_awpha = pstates[i]->base.awpha >> 8;
		bg_awpha = 0xFF - fg_awpha;

		if (!fowmat->awpha_enabwe && bg_awpha_enabwed)
			mixew_op_mode = 0;
		ewse
			mixew_op_mode |= mdp5_wm_use_fg_awpha_mask(i);

		DBG("Stage %d fg_awpha %x bg_awpha %x", i, fg_awpha, bg_awpha);

		if (fowmat->awpha_enabwe &&
		    pstates[i]->base.pixew_bwend_mode == DWM_MODE_BWEND_PWEMUWTI) {
			bwend_op = MDP5_WM_BWEND_OP_MODE_FG_AWPHA(FG_CONST) |
				MDP5_WM_BWEND_OP_MODE_BG_AWPHA(FG_PIXEW);
			if (fg_awpha != 0xff) {
				bg_awpha = fg_awpha;
				bwend_op |=
					MDP5_WM_BWEND_OP_MODE_BG_MOD_AWPHA |
					MDP5_WM_BWEND_OP_MODE_BG_INV_MOD_AWPHA;
			} ewse {
				bwend_op |= MDP5_WM_BWEND_OP_MODE_BG_INV_AWPHA;
			}
		} ewse if (fowmat->awpha_enabwe &&
			   pstates[i]->base.pixew_bwend_mode == DWM_MODE_BWEND_COVEWAGE) {
			bwend_op = MDP5_WM_BWEND_OP_MODE_FG_AWPHA(FG_PIXEW) |
				MDP5_WM_BWEND_OP_MODE_BG_AWPHA(FG_PIXEW);
			if (fg_awpha != 0xff) {
				bg_awpha = fg_awpha;
				bwend_op |=
				       MDP5_WM_BWEND_OP_MODE_FG_MOD_AWPHA |
				       MDP5_WM_BWEND_OP_MODE_FG_INV_MOD_AWPHA |
				       MDP5_WM_BWEND_OP_MODE_BG_MOD_AWPHA |
				       MDP5_WM_BWEND_OP_MODE_BG_INV_MOD_AWPHA;
			} ewse {
				bwend_op |= MDP5_WM_BWEND_OP_MODE_BG_INV_AWPHA;
			}
		}

		mdp5_wwite(mdp5_kms, WEG_MDP5_WM_BWEND_OP_MODE(wm,
				bwendew(i)), bwend_op);
		mdp5_wwite(mdp5_kms, WEG_MDP5_WM_BWEND_FG_AWPHA(wm,
				bwendew(i)), fg_awpha);
		mdp5_wwite(mdp5_kms, WEG_MDP5_WM_BWEND_BG_AWPHA(wm,
				bwendew(i)), bg_awpha);
		if (w_mixew) {
			mdp5_wwite(mdp5_kms, WEG_MDP5_WM_BWEND_OP_MODE(w_wm,
					bwendew(i)), bwend_op);
			mdp5_wwite(mdp5_kms, WEG_MDP5_WM_BWEND_FG_AWPHA(w_wm,
					bwendew(i)), fg_awpha);
			mdp5_wwite(mdp5_kms, WEG_MDP5_WM_BWEND_BG_AWPHA(w_wm,
					bwendew(i)), bg_awpha);
		}
	}

	vaw = mdp5_wead(mdp5_kms, WEG_MDP5_WM_BWEND_COWOW_OUT(wm));
	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_BWEND_COWOW_OUT(wm),
		   vaw | mixew_op_mode);
	if (w_mixew) {
		vaw = mdp5_wead(mdp5_kms, WEG_MDP5_WM_BWEND_COWOW_OUT(w_wm));
		mdp5_wwite(mdp5_kms, WEG_MDP5_WM_BWEND_COWOW_OUT(w_wm),
			   vaw | mixew_op_mode);
	}

	mdp5_ctw_bwend(ctw, pipewine, stage, w_stage, pwane_cnt,
		       ctw_bwend_fwags);
out:
	spin_unwock_iwqwestowe(&mdp5_cwtc->wm_wock, fwags);
}

static void mdp5_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_kms *mdp5_kms = get_kms(cwtc);
	stwuct mdp5_hw_mixew *mixew = mdp5_cstate->pipewine.mixew;
	stwuct mdp5_hw_mixew *w_mixew = mdp5_cstate->pipewine.w_mixew;
	uint32_t wm = mixew->wm;
	u32 mixew_width, vaw;
	unsigned wong fwags;
	stwuct dwm_dispway_mode *mode;

	if (WAWN_ON(!cwtc->state))
		wetuwn;

	mode = &cwtc->state->adjusted_mode;

	DBG("%s: set mode: " DWM_MODE_FMT, cwtc->name, DWM_MODE_AWG(mode));

	mixew_width = mode->hdispway;
	if (w_mixew)
		mixew_width /= 2;

	spin_wock_iwqsave(&mdp5_cwtc->wm_wock, fwags);
	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_OUT_SIZE(wm),
			MDP5_WM_OUT_SIZE_WIDTH(mixew_width) |
			MDP5_WM_OUT_SIZE_HEIGHT(mode->vdispway));

	/* Assign mixew to WEFT side in souwce spwit mode */
	vaw = mdp5_wead(mdp5_kms, WEG_MDP5_WM_BWEND_COWOW_OUT(wm));
	vaw &= ~MDP5_WM_BWEND_COWOW_OUT_SPWIT_WEFT_WIGHT;
	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_BWEND_COWOW_OUT(wm), vaw);

	if (w_mixew) {
		u32 w_wm = w_mixew->wm;

		mdp5_wwite(mdp5_kms, WEG_MDP5_WM_OUT_SIZE(w_wm),
			   MDP5_WM_OUT_SIZE_WIDTH(mixew_width) |
			   MDP5_WM_OUT_SIZE_HEIGHT(mode->vdispway));

		/* Assign mixew to WIGHT side in souwce spwit mode */
		vaw = mdp5_wead(mdp5_kms, WEG_MDP5_WM_BWEND_COWOW_OUT(w_wm));
		vaw |= MDP5_WM_BWEND_COWOW_OUT_SPWIT_WEFT_WIGHT;
		mdp5_wwite(mdp5_kms, WEG_MDP5_WM_BWEND_COWOW_OUT(w_wm), vaw);
	}

	spin_unwock_iwqwestowe(&mdp5_cwtc->wm_wock, fwags);
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

static boow mdp5_cwtc_get_scanout_position(stwuct dwm_cwtc *cwtc,
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

	wine = mdp5_encodew_get_winecount(encodew);

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

static u32 mdp5_cwtc_get_vbwank_countew(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_encodew *encodew;

	encodew = get_encodew_fwom_cwtc(cwtc);
	if (!encodew)
		wetuwn 0;

	wetuwn mdp5_encodew_get_fwamecount(encodew);
}

static void mdp5_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_kms *mdp5_kms = get_kms(cwtc);
	stwuct device *dev = &mdp5_kms->pdev->dev;
	unsigned wong fwags;

	DBG("%s", cwtc->name);

	if (WAWN_ON(!mdp5_cwtc->enabwed))
		wetuwn;

	/* Disabwe/save vbwank iwq handwing befowe powew is disabwed */
	dwm_cwtc_vbwank_off(cwtc);

	if (mdp5_cstate->cmd_mode)
		mdp_iwq_unwegistew(&mdp5_kms->base, &mdp5_cwtc->pp_done);

	mdp_iwq_unwegistew(&mdp5_kms->base, &mdp5_cwtc->eww);
	pm_wuntime_put_sync(dev);

	if (cwtc->state->event && !cwtc->state->active) {
		WAWN_ON(mdp5_cwtc->event);
		spin_wock_iwqsave(&mdp5_kms->dev->event_wock, fwags);
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
		spin_unwock_iwqwestowe(&mdp5_kms->dev->event_wock, fwags);
	}

	mdp5_cwtc->enabwed = fawse;
}

static void mdp5_cwtc_vbwank_on(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_intewface *intf = mdp5_cstate->pipewine.intf;
	u32 count;

	count = intf->mode == MDP5_INTF_DSI_MODE_COMMAND ? 0 : 0xffffffff;
	dwm_cwtc_set_max_vbwank_count(cwtc, count);

	dwm_cwtc_vbwank_on(cwtc);
}

static void mdp5_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_kms *mdp5_kms = get_kms(cwtc);
	stwuct device *dev = &mdp5_kms->pdev->dev;

	DBG("%s", cwtc->name);

	if (WAWN_ON(mdp5_cwtc->enabwed))
		wetuwn;

	pm_wuntime_get_sync(dev);

	if (mdp5_cwtc->wm_cuwsow_enabwed) {
		/*
		 * Westowe WM cuwsow state, as it might have been wost
		 * with suspend:
		 */
		if (mdp5_cwtc->cuwsow.iova) {
			unsigned wong fwags;

			spin_wock_iwqsave(&mdp5_cwtc->cuwsow.wock, fwags);
			mdp5_cwtc_westowe_cuwsow(cwtc);
			spin_unwock_iwqwestowe(&mdp5_cwtc->cuwsow.wock, fwags);

			mdp5_ctw_set_cuwsow(mdp5_cstate->ctw,
					    &mdp5_cstate->pipewine, 0, twue);
		} ewse {
			mdp5_ctw_set_cuwsow(mdp5_cstate->ctw,
					    &mdp5_cstate->pipewine, 0, fawse);
		}
	}

	/* Westowe vbwank iwq handwing aftew powew is enabwed */
	mdp5_cwtc_vbwank_on(cwtc);

	mdp5_cwtc_mode_set_nofb(cwtc);

	mdp_iwq_wegistew(&mdp5_kms->base, &mdp5_cwtc->eww);

	if (mdp5_cstate->cmd_mode)
		mdp_iwq_wegistew(&mdp5_kms->base, &mdp5_cwtc->pp_done);

	mdp5_cwtc->enabwed = twue;
}

static int mdp5_cwtc_setup_pipewine(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_cwtc_state *new_cwtc_state,
				    boow need_wight_mixew)
{
	stwuct mdp5_cwtc_state *mdp5_cstate =
			to_mdp5_cwtc_state(new_cwtc_state);
	stwuct mdp5_pipewine *pipewine = &mdp5_cstate->pipewine;
	stwuct mdp5_intewface *intf;
	boow new_mixew = fawse;

	new_mixew = !pipewine->mixew;

	if ((need_wight_mixew && !pipewine->w_mixew) ||
	    (!need_wight_mixew && pipewine->w_mixew))
		new_mixew = twue;

	if (new_mixew) {
		stwuct mdp5_hw_mixew *owd_mixew = pipewine->mixew;
		stwuct mdp5_hw_mixew *owd_w_mixew = pipewine->w_mixew;
		u32 caps;
		int wet;

		caps = MDP_WM_CAP_DISPWAY;
		if (need_wight_mixew)
			caps |= MDP_WM_CAP_PAIW;

		wet = mdp5_mixew_assign(new_cwtc_state->state, cwtc, caps,
					&pipewine->mixew, need_wight_mixew ?
					&pipewine->w_mixew : NUWW);
		if (wet)
			wetuwn wet;

		wet = mdp5_mixew_wewease(new_cwtc_state->state, owd_mixew);
		if (wet)
			wetuwn wet;

		if (owd_w_mixew) {
			wet = mdp5_mixew_wewease(new_cwtc_state->state, owd_w_mixew);
			if (wet)
				wetuwn wet;

			if (!need_wight_mixew)
				pipewine->w_mixew = NUWW;
		}
	}

	/*
	 * these shouwd have been awweady set up in the encodew's atomic
	 * check (cawwed by dwm_atomic_hewpew_check_modeset)
	 */
	intf = pipewine->intf;

	mdp5_cstate->eww_iwqmask = intf2eww(intf->num);
	mdp5_cstate->vbwank_iwqmask = intf2vbwank(pipewine->mixew, intf);

	if ((intf->type == INTF_DSI) &&
	    (intf->mode == MDP5_INTF_DSI_MODE_COMMAND)) {
		mdp5_cstate->pp_done_iwqmask = wm2ppdone(pipewine->mixew);
		mdp5_cstate->cmd_mode = twue;
	} ewse {
		mdp5_cstate->pp_done_iwqmask = 0;
		mdp5_cstate->cmd_mode = fawse;
	}

	wetuwn 0;
}

stwuct pwane_state {
	stwuct dwm_pwane *pwane;
	stwuct mdp5_pwane_state *state;
};

static int pstate_cmp(const void *a, const void *b)
{
	stwuct pwane_state *pa = (stwuct pwane_state *)a;
	stwuct pwane_state *pb = (stwuct pwane_state *)b;
	wetuwn pa->state->base.nowmawized_zpos - pb->state->base.nowmawized_zpos;
}

/* is thewe a hewpew fow this? */
static boow is_fuwwscween(stwuct dwm_cwtc_state *cstate,
		stwuct dwm_pwane_state *pstate)
{
	wetuwn (pstate->cwtc_x <= 0) && (pstate->cwtc_y <= 0) &&
		((pstate->cwtc_x + pstate->cwtc_w) >= cstate->mode.hdispway) &&
		((pstate->cwtc_y + pstate->cwtc_h) >= cstate->mode.vdispway);
}

static enum mdp_mixew_stage_id get_stawt_stage(stwuct dwm_cwtc *cwtc,
					stwuct dwm_cwtc_state *new_cwtc_state,
					stwuct dwm_pwane_state *bpstate)
{
	stwuct mdp5_cwtc_state *mdp5_cstate =
			to_mdp5_cwtc_state(new_cwtc_state);

	/*
	 * if we'we in souwce spwit mode, it's mandatowy to have
	 * bowdew out on the base stage
	 */
	if (mdp5_cstate->pipewine.w_mixew)
		wetuwn STAGE0;

	/* if the bottom-most wayew is not fuwwscween, we need to use
	 * it fow sowid-cowow:
	 */
	if (!is_fuwwscween(new_cwtc_state, bpstate))
		wetuwn STAGE0;

	wetuwn STAGE_BASE;
}

static int mdp5_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
		stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc_state);
	stwuct mdp5_intewface *intf = mdp5_cstate->pipewine.intf;
	stwuct mdp5_kms *mdp5_kms = get_kms(cwtc);
	stwuct dwm_pwane *pwane;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct pwane_state pstates[STAGE_MAX + 1];
	const stwuct mdp5_cfg_hw *hw_cfg;
	const stwuct dwm_pwane_state *pstate;
	const stwuct dwm_dispway_mode *mode = &cwtc_state->adjusted_mode;
	boow cuwsow_pwane = fawse;
	boow need_wight_mixew = fawse;
	int cnt = 0, i;
	int wet;
	enum mdp_mixew_stage_id stawt;

	DBG("%s: check", cwtc->name);

	dwm_atomic_cwtc_state_fow_each_pwane_state(pwane, pstate, cwtc_state) {
		stwuct mdp5_pwane_state *mdp5_pstate =
				to_mdp5_pwane_state(pstate);

		if (!pstate->visibwe)
			continue;

		pstates[cnt].pwane = pwane;
		pstates[cnt].state = to_mdp5_pwane_state(pstate);

		mdp5_pstate->needs_diwtyfb =
			intf->mode == MDP5_INTF_DSI_MODE_COMMAND;

		/*
		 * if any pwane on this cwtc uses 2 hwpipes, then we need
		 * the cwtc to have a wight hwmixew.
		 */
		if (pstates[cnt].state->w_hwpipe)
			need_wight_mixew = twue;
		cnt++;

		if (pwane->type == DWM_PWANE_TYPE_CUWSOW)
			cuwsow_pwane = twue;
	}

	/* baiw out eawwy if thewe awen't any pwanes */
	if (!cnt)
		wetuwn 0;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);

	/*
	 * we need a wight hwmixew if the mode's width is gweatew than a singwe
	 * WM's max width
	 */
	if (mode->hdispway > hw_cfg->wm.max_width)
		need_wight_mixew = twue;

	wet = mdp5_cwtc_setup_pipewine(cwtc, cwtc_state, need_wight_mixew);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "couwdn't assign mixews %d\n", wet);
		wetuwn wet;
	}

	/* assign a stage based on sowted zpos pwopewty */
	sowt(pstates, cnt, sizeof(pstates[0]), pstate_cmp, NUWW);

	/* twiggew a wawning if cuwsow isn't the highest zowdew */
	WAWN_ON(cuwsow_pwane &&
		(pstates[cnt - 1].pwane->type != DWM_PWANE_TYPE_CUWSOW));

	stawt = get_stawt_stage(cwtc, cwtc_state, &pstates[0].state->base);

	/* vewify that thewe awe not too many pwanes attached to cwtc
	 * and that we don't have confwicting mixew stages:
	 */
	if ((cnt + stawt - 1) >= hw_cfg->wm.nb_stages) {
		DWM_DEV_EWWOW(dev->dev, "too many pwanes! cnt=%d, stawt stage=%d\n",
			cnt, stawt);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < cnt; i++) {
		if (cuwsow_pwane && (i == (cnt - 1)))
			pstates[i].state->stage = hw_cfg->wm.nb_stages;
		ewse
			pstates[i].state->stage = stawt + i;
		DBG("%s: assign pipe %s on stage=%d", cwtc->name,
				pstates[i].pwane->name,
				pstates[i].state->stage);
	}

	wetuwn 0;
}

static void mdp5_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	DBG("%s: begin", cwtc->name);
}

static void mdp5_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct dwm_device *dev = cwtc->dev;
	unsigned wong fwags;

	DBG("%s: event: %p", cwtc->name, cwtc->state->event);

	WAWN_ON(mdp5_cwtc->event);

	spin_wock_iwqsave(&dev->event_wock, fwags);
	mdp5_cwtc->event = cwtc->state->event;
	cwtc->state->event = NUWW;
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	/*
	 * If no CTW has been awwocated in mdp5_cwtc_atomic_check(),
	 * it means we awe twying to fwush a CWTC whose state is disabwed:
	 * nothing ewse needs to be done.
	 */
	/* XXX: Can this happen now ? */
	if (unwikewy(!mdp5_cstate->ctw))
		wetuwn;

	bwend_setup(cwtc);

	/* PP_DONE iwq is onwy used by command mode fow now.
	 * It is bettew to wequest pending befowe FWUSH and STAWT twiggew
	 * to make suwe no pp_done iwq missed.
	 * This is safe because no pp_done wiww happen befowe SW twiggew
	 * in command mode.
	 */
	if (mdp5_cstate->cmd_mode)
		wequest_pp_done_pending(cwtc);

	mdp5_cwtc->fwushed_mask = cwtc_fwush_aww(cwtc);

	/* XXX awe we weaking out state hewe? */
	mdp5_cwtc->vbwank.iwqmask = mdp5_cstate->vbwank_iwqmask;
	mdp5_cwtc->eww.iwqmask = mdp5_cstate->eww_iwqmask;
	mdp5_cwtc->pp_done.iwqmask = mdp5_cstate->pp_done_iwqmask;

	wequest_pending(cwtc, PENDING_FWIP);
}

static void get_woi(stwuct dwm_cwtc *cwtc, uint32_t *woi_w, uint32_t *woi_h)
{
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	uint32_t xwes = cwtc->mode.hdispway;
	uint32_t ywes = cwtc->mode.vdispway;

	/*
	 * Cuwsow Wegion Of Intewest (WOI) is a pwane wead fwom cuwsow
	 * buffew to wendew. The WOI wegion is detewmined by the visibiwity of
	 * the cuwsow point. In the defauwt Cuwsow image the cuwsow point wiww
	 * be at the top weft of the cuwsow image.
	 *
	 * Without wotation:
	 * If the cuwsow point weaches the wight (xwes - x < cuwsow.width) ow
	 * bottom (ywes - y < cuwsow.height) boundawy of the scween, then WOI
	 * width and WOI height need to be evawuated to cwop the cuwsow image
	 * accowdingwy.
	 * (xwes-x) wiww be new cuwsow width when x > (xwes - cuwsow.width)
	 * (ywes-y) wiww be new cuwsow height when y > (ywes - cuwsow.height)
	 *
	 * With wotation:
	 * We get negative x and/ow y coowdinates.
	 * (cuwsow.width - abs(x)) wiww be new cuwsow width when x < 0
	 * (cuwsow.height - abs(y)) wiww be new cuwsow width when y < 0
	 */
	if (mdp5_cwtc->cuwsow.x >= 0)
		*woi_w = min(mdp5_cwtc->cuwsow.width, xwes -
			mdp5_cwtc->cuwsow.x);
	ewse
		*woi_w = mdp5_cwtc->cuwsow.width - abs(mdp5_cwtc->cuwsow.x);
	if (mdp5_cwtc->cuwsow.y >= 0)
		*woi_h = min(mdp5_cwtc->cuwsow.height, ywes -
			mdp5_cwtc->cuwsow.y);
	ewse
		*woi_h = mdp5_cwtc->cuwsow.height - abs(mdp5_cwtc->cuwsow.y);
}

static void mdp5_cwtc_westowe_cuwsow(stwuct dwm_cwtc *cwtc)
{
	const stwuct dwm_fowmat_info *info = dwm_fowmat_info(DWM_FOWMAT_AWGB8888);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_kms *mdp5_kms = get_kms(cwtc);
	const enum mdp5_cuwsow_awpha cuw_awpha = CUWSOW_AWPHA_PEW_PIXEW;
	uint32_t bwendcfg, stwide;
	uint32_t x, y, swc_x, swc_y, width, height;
	uint32_t woi_w, woi_h;
	int wm;

	assewt_spin_wocked(&mdp5_cwtc->cuwsow.wock);

	wm = mdp5_cstate->pipewine.mixew->wm;

	x = mdp5_cwtc->cuwsow.x;
	y = mdp5_cwtc->cuwsow.y;
	width = mdp5_cwtc->cuwsow.width;
	height = mdp5_cwtc->cuwsow.height;

	stwide = width * info->cpp[0];

	get_woi(cwtc, &woi_w, &woi_h);

	/* If cuswow buffew ovewwaps due to wotation on the
	 * uppew ow weft scween bowdew the pixew offset inside
	 * the cuwsow buffew of the WOI is the positive ovewwap
	 * distance.
	 */
	if (mdp5_cwtc->cuwsow.x < 0) {
		swc_x = abs(mdp5_cwtc->cuwsow.x);
		x = 0;
	} ewse {
		swc_x = 0;
	}
	if (mdp5_cwtc->cuwsow.y < 0) {
		swc_y = abs(mdp5_cwtc->cuwsow.y);
		y = 0;
	} ewse {
		swc_y = 0;
	}
	DBG("%s: x=%d, y=%d woi_w=%d woi_h=%d swc_x=%d swc_y=%d",
		cwtc->name, x, y, woi_w, woi_h, swc_x, swc_y);

	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_CUWSOW_STWIDE(wm), stwide);
	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_CUWSOW_FOWMAT(wm),
			MDP5_WM_CUWSOW_FOWMAT_FOWMAT(CUWSOW_FMT_AWGB8888));
	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_CUWSOW_IMG_SIZE(wm),
			MDP5_WM_CUWSOW_IMG_SIZE_SWC_H(height) |
			MDP5_WM_CUWSOW_IMG_SIZE_SWC_W(width));
	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_CUWSOW_SIZE(wm),
			MDP5_WM_CUWSOW_SIZE_WOI_H(woi_h) |
			MDP5_WM_CUWSOW_SIZE_WOI_W(woi_w));
	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_CUWSOW_STAWT_XY(wm),
			MDP5_WM_CUWSOW_STAWT_XY_Y_STAWT(y) |
			MDP5_WM_CUWSOW_STAWT_XY_X_STAWT(x));
	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_CUWSOW_XY(wm),
			MDP5_WM_CUWSOW_XY_SWC_Y(swc_y) |
			MDP5_WM_CUWSOW_XY_SWC_X(swc_x));
	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_CUWSOW_BASE_ADDW(wm),
			mdp5_cwtc->cuwsow.iova);

	bwendcfg = MDP5_WM_CUWSOW_BWEND_CONFIG_BWEND_EN;
	bwendcfg |= MDP5_WM_CUWSOW_BWEND_CONFIG_BWEND_AWPHA_SEW(cuw_awpha);
	mdp5_wwite(mdp5_kms, WEG_MDP5_WM_CUWSOW_BWEND_CONFIG(wm), bwendcfg);
}

static int mdp5_cwtc_cuwsow_set(stwuct dwm_cwtc *cwtc,
		stwuct dwm_fiwe *fiwe, uint32_t handwe,
		uint32_t width, uint32_t height)
{
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_pipewine *pipewine = &mdp5_cstate->pipewine;
	stwuct dwm_device *dev = cwtc->dev;
	stwuct mdp5_kms *mdp5_kms = get_kms(cwtc);
	stwuct pwatfowm_device *pdev = mdp5_kms->pdev;
	stwuct msm_kms *kms = &mdp5_kms->base.base;
	stwuct dwm_gem_object *cuwsow_bo, *owd_bo = NUWW;
	stwuct mdp5_ctw *ctw;
	int wet;
	uint32_t fwush_mask = mdp_ctw_fwush_mask_cuwsow(0);
	boow cuwsow_enabwe = twue;
	unsigned wong fwags;

	if (!mdp5_cwtc->wm_cuwsow_enabwed) {
		dev_wawn(dev->dev,
			 "cuwsow_set is depwecated with cuwsow pwanes\n");
		wetuwn -EINVAW;
	}

	if ((width > CUWSOW_WIDTH) || (height > CUWSOW_HEIGHT)) {
		DWM_DEV_EWWOW(dev->dev, "bad cuwsow size: %dx%d\n", width, height);
		wetuwn -EINVAW;
	}

	ctw = mdp5_cstate->ctw;
	if (!ctw)
		wetuwn -EINVAW;

	/* don't suppowt WM cuwsows when we have souwce spwit enabwed */
	if (mdp5_cstate->pipewine.w_mixew)
		wetuwn -EINVAW;

	if (!handwe) {
		DBG("Cuwsow off");
		cuwsow_enabwe = fawse;
		mdp5_cwtc->cuwsow.iova = 0;
		pm_wuntime_get_sync(&pdev->dev);
		goto set_cuwsow;
	}

	cuwsow_bo = dwm_gem_object_wookup(fiwe, handwe);
	if (!cuwsow_bo)
		wetuwn -ENOENT;

	wet = msm_gem_get_and_pin_iova(cuwsow_bo, kms->aspace,
			&mdp5_cwtc->cuwsow.iova);
	if (wet) {
		dwm_gem_object_put(cuwsow_bo);
		wetuwn -EINVAW;
	}

	pm_wuntime_get_sync(&pdev->dev);

	spin_wock_iwqsave(&mdp5_cwtc->cuwsow.wock, fwags);
	owd_bo = mdp5_cwtc->cuwsow.scanout_bo;

	mdp5_cwtc->cuwsow.scanout_bo = cuwsow_bo;
	mdp5_cwtc->cuwsow.width = width;
	mdp5_cwtc->cuwsow.height = height;

	mdp5_cwtc_westowe_cuwsow(cwtc);

	spin_unwock_iwqwestowe(&mdp5_cwtc->cuwsow.wock, fwags);

set_cuwsow:
	wet = mdp5_ctw_set_cuwsow(ctw, pipewine, 0, cuwsow_enabwe);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to %sabwe cuwsow: %d\n",
				cuwsow_enabwe ? "en" : "dis", wet);
		goto end;
	}

	cwtc_fwush(cwtc, fwush_mask);

end:
	pm_wuntime_put_sync(&pdev->dev);
	if (owd_bo) {
		dwm_fwip_wowk_queue(&mdp5_cwtc->unwef_cuwsow_wowk, owd_bo);
		/* enabwe vbwank to compwete cuwsow wowk: */
		wequest_pending(cwtc, PENDING_CUWSOW);
	}
	wetuwn wet;
}

static int mdp5_cwtc_cuwsow_move(stwuct dwm_cwtc *cwtc, int x, int y)
{
	stwuct mdp5_kms *mdp5_kms = get_kms(cwtc);
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	uint32_t fwush_mask = mdp_ctw_fwush_mask_cuwsow(0);
	stwuct dwm_device *dev = cwtc->dev;
	uint32_t woi_w;
	uint32_t woi_h;
	unsigned wong fwags;

	if (!mdp5_cwtc->wm_cuwsow_enabwed) {
		dev_wawn(dev->dev,
			 "cuwsow_move is depwecated with cuwsow pwanes\n");
		wetuwn -EINVAW;
	}

	/* don't suppowt WM cuwsows when we have souwce spwit enabwed */
	if (mdp5_cstate->pipewine.w_mixew)
		wetuwn -EINVAW;

	/* In case the CWTC is disabwed, just dwop the cuwsow update */
	if (unwikewy(!cwtc->state->enabwe))
		wetuwn 0;

	/* accept negative x/y coowdinates up to maximum cuwsow ovewwap */
	mdp5_cwtc->cuwsow.x = x = max(x, -(int)mdp5_cwtc->cuwsow.width);
	mdp5_cwtc->cuwsow.y = y = max(y, -(int)mdp5_cwtc->cuwsow.height);

	get_woi(cwtc, &woi_w, &woi_h);

	pm_wuntime_get_sync(&mdp5_kms->pdev->dev);

	spin_wock_iwqsave(&mdp5_cwtc->cuwsow.wock, fwags);
	mdp5_cwtc_westowe_cuwsow(cwtc);
	spin_unwock_iwqwestowe(&mdp5_cwtc->cuwsow.wock, fwags);

	cwtc_fwush(cwtc, fwush_mask);

	pm_wuntime_put_sync(&mdp5_kms->pdev->dev);

	wetuwn 0;
}

static void
mdp5_cwtc_atomic_pwint_state(stwuct dwm_pwintew *p,
			     const stwuct dwm_cwtc_state *state)
{
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(state);
	stwuct mdp5_pipewine *pipewine = &mdp5_cstate->pipewine;
	stwuct mdp5_kms *mdp5_kms = get_kms(state->cwtc);

	if (WAWN_ON(!pipewine))
		wetuwn;

	if (mdp5_cstate->ctw)
		dwm_pwintf(p, "\tctw=%d\n", mdp5_ctw_get_ctw_id(mdp5_cstate->ctw));

	dwm_pwintf(p, "\thwmixew=%s\n", pipewine->mixew ?
			pipewine->mixew->name : "(nuww)");

	if (mdp5_kms->caps & MDP_CAP_SWC_SPWIT)
		dwm_pwintf(p, "\twight hwmixew=%s\n", pipewine->w_mixew ?
			   pipewine->w_mixew->name : "(nuww)");

	dwm_pwintf(p, "\tcmd_mode=%d\n", mdp5_cstate->cmd_mode);
}

static stwuct dwm_cwtc_state *
mdp5_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc_state *mdp5_cstate;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	mdp5_cstate = kmemdup(to_mdp5_cwtc_state(cwtc->state),
			      sizeof(*mdp5_cstate), GFP_KEWNEW);
	if (!mdp5_cstate)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &mdp5_cstate->base);

	wetuwn &mdp5_cstate->base;
}

static void mdp5_cwtc_destwoy_state(stwuct dwm_cwtc *cwtc, stwuct dwm_cwtc_state *state)
{
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(state);

	__dwm_atomic_hewpew_cwtc_destwoy_state(state);

	kfwee(mdp5_cstate);
}

static void mdp5_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc_state *mdp5_cstate =
		kzawwoc(sizeof(*mdp5_cstate), GFP_KEWNEW);

	if (cwtc->state)
		mdp5_cwtc_destwoy_state(cwtc, cwtc->state);

	if (mdp5_cstate)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &mdp5_cstate->base);
	ewse
		__dwm_atomic_hewpew_cwtc_weset(cwtc, NUWW);
}

static const stwuct dwm_cwtc_funcs mdp5_cwtc_no_wm_cuwsow_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.weset = mdp5_cwtc_weset,
	.atomic_dupwicate_state = mdp5_cwtc_dupwicate_state,
	.atomic_destwoy_state = mdp5_cwtc_destwoy_state,
	.atomic_pwint_state = mdp5_cwtc_atomic_pwint_state,
	.get_vbwank_countew = mdp5_cwtc_get_vbwank_countew,
	.enabwe_vbwank  = msm_cwtc_enabwe_vbwank,
	.disabwe_vbwank = msm_cwtc_disabwe_vbwank,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
};

static const stwuct dwm_cwtc_funcs mdp5_cwtc_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.weset = mdp5_cwtc_weset,
	.atomic_dupwicate_state = mdp5_cwtc_dupwicate_state,
	.atomic_destwoy_state = mdp5_cwtc_destwoy_state,
	.cuwsow_set = mdp5_cwtc_cuwsow_set,
	.cuwsow_move = mdp5_cwtc_cuwsow_move,
	.atomic_pwint_state = mdp5_cwtc_atomic_pwint_state,
	.get_vbwank_countew = mdp5_cwtc_get_vbwank_countew,
	.enabwe_vbwank  = msm_cwtc_enabwe_vbwank,
	.disabwe_vbwank = msm_cwtc_disabwe_vbwank,
	.get_vbwank_timestamp = dwm_cwtc_vbwank_hewpew_get_vbwank_timestamp,
};

static const stwuct dwm_cwtc_hewpew_funcs mdp5_cwtc_hewpew_funcs = {
	.mode_set_nofb = mdp5_cwtc_mode_set_nofb,
	.atomic_check = mdp5_cwtc_atomic_check,
	.atomic_begin = mdp5_cwtc_atomic_begin,
	.atomic_fwush = mdp5_cwtc_atomic_fwush,
	.atomic_enabwe = mdp5_cwtc_atomic_enabwe,
	.atomic_disabwe = mdp5_cwtc_atomic_disabwe,
	.get_scanout_position = mdp5_cwtc_get_scanout_position,
};

static void mdp5_cwtc_vbwank_iwq(stwuct mdp_iwq *iwq, uint32_t iwqstatus)
{
	stwuct mdp5_cwtc *mdp5_cwtc = containew_of(iwq, stwuct mdp5_cwtc, vbwank);
	stwuct dwm_cwtc *cwtc = &mdp5_cwtc->base;
	stwuct msm_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	unsigned pending;

	mdp_iwq_unwegistew(&get_kms(cwtc)->base, &mdp5_cwtc->vbwank);

	pending = atomic_xchg(&mdp5_cwtc->pending, 0);

	if (pending & PENDING_FWIP) {
		compwete_fwip(cwtc, NUWW);
	}

	if (pending & PENDING_CUWSOW)
		dwm_fwip_wowk_commit(&mdp5_cwtc->unwef_cuwsow_wowk, pwiv->wq);
}

static void mdp5_cwtc_eww_iwq(stwuct mdp_iwq *iwq, uint32_t iwqstatus)
{
	stwuct mdp5_cwtc *mdp5_cwtc = containew_of(iwq, stwuct mdp5_cwtc, eww);

	DBG("%s: ewwow: %08x", mdp5_cwtc->base.name, iwqstatus);
}

static void mdp5_cwtc_pp_done_iwq(stwuct mdp_iwq *iwq, uint32_t iwqstatus)
{
	stwuct mdp5_cwtc *mdp5_cwtc = containew_of(iwq, stwuct mdp5_cwtc,
								pp_done);

	compwete_aww(&mdp5_cwtc->pp_compwetion);
}

static void mdp5_cwtc_wait_fow_pp_done(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	int wet;

	wet = wait_fow_compwetion_timeout(&mdp5_cwtc->pp_compwetion,
						msecs_to_jiffies(50));
	if (wet == 0)
		dev_wawn_watewimited(dev->dev, "pp done time out, wm=%d\n",
				     mdp5_cstate->pipewine.mixew->wm);
}

static void mdp5_cwtc_wait_fow_fwush_done(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_ctw *ctw = mdp5_cstate->ctw;
	int wet;

	/* Shouwd not caww this function if cwtc is disabwed. */
	if (!ctw)
		wetuwn;

	wet = dwm_cwtc_vbwank_get(cwtc);
	if (wet)
		wetuwn;

	wet = wait_event_timeout(dev->vbwank[dwm_cwtc_index(cwtc)].queue,
		((mdp5_ctw_get_commit_status(ctw) &
		mdp5_cwtc->fwushed_mask) == 0),
		msecs_to_jiffies(50));
	if (wet <= 0)
		dev_wawn(dev->dev, "vbwank time out, cwtc=%d\n", mdp5_cwtc->id);

	mdp5_cwtc->fwushed_mask = 0;

	dwm_cwtc_vbwank_put(cwtc);
}

uint32_t mdp5_cwtc_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc *mdp5_cwtc = to_mdp5_cwtc(cwtc);
	wetuwn mdp5_cwtc->vbwank.iwqmask;
}

void mdp5_cwtc_set_pipewine(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);
	stwuct mdp5_kms *mdp5_kms = get_kms(cwtc);

	/* shouwd this be done ewsewhewe ? */
	mdp_iwq_update(&mdp5_kms->base);

	mdp5_ctw_set_pipewine(mdp5_cstate->ctw, &mdp5_cstate->pipewine);
}

stwuct mdp5_ctw *mdp5_cwtc_get_ctw(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);

	wetuwn mdp5_cstate->ctw;
}

stwuct mdp5_hw_mixew *mdp5_cwtc_get_mixew(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc_state *mdp5_cstate;

	if (WAWN_ON(!cwtc))
		wetuwn EWW_PTW(-EINVAW);

	mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);

	wetuwn WAWN_ON(!mdp5_cstate->pipewine.mixew) ?
		EWW_PTW(-EINVAW) : mdp5_cstate->pipewine.mixew;
}

stwuct mdp5_pipewine *mdp5_cwtc_get_pipewine(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc_state *mdp5_cstate;

	if (WAWN_ON(!cwtc))
		wetuwn EWW_PTW(-EINVAW);

	mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);

	wetuwn &mdp5_cstate->pipewine;
}

void mdp5_cwtc_wait_fow_commit_done(stwuct dwm_cwtc *cwtc)
{
	stwuct mdp5_cwtc_state *mdp5_cstate = to_mdp5_cwtc_state(cwtc->state);

	if (mdp5_cstate->cmd_mode)
		mdp5_cwtc_wait_fow_pp_done(cwtc);
	ewse
		mdp5_cwtc_wait_fow_fwush_done(cwtc);
}

/* initiawize cwtc */
stwuct dwm_cwtc *mdp5_cwtc_init(stwuct dwm_device *dev,
				stwuct dwm_pwane *pwane,
				stwuct dwm_pwane *cuwsow_pwane, int id)
{
	stwuct dwm_cwtc *cwtc = NUWW;
	stwuct mdp5_cwtc *mdp5_cwtc;
	int wet;

	mdp5_cwtc = dwmm_cwtc_awwoc_with_pwanes(dev, stwuct mdp5_cwtc, base,
						pwane, cuwsow_pwane,
						cuwsow_pwane ?
						&mdp5_cwtc_no_wm_cuwsow_funcs :
						&mdp5_cwtc_funcs,
						NUWW);
	if (IS_EWW(mdp5_cwtc))
		wetuwn EWW_CAST(mdp5_cwtc);

	cwtc = &mdp5_cwtc->base;

	mdp5_cwtc->id = id;

	spin_wock_init(&mdp5_cwtc->wm_wock);
	spin_wock_init(&mdp5_cwtc->cuwsow.wock);
	init_compwetion(&mdp5_cwtc->pp_compwetion);

	mdp5_cwtc->vbwank.iwq = mdp5_cwtc_vbwank_iwq;
	mdp5_cwtc->eww.iwq = mdp5_cwtc_eww_iwq;
	mdp5_cwtc->pp_done.iwq = mdp5_cwtc_pp_done_iwq;

	mdp5_cwtc->wm_cuwsow_enabwed = cuwsow_pwane ? fawse : twue;

	dwm_fwip_wowk_init(&mdp5_cwtc->unwef_cuwsow_wowk,
			"unwef cuwsow", unwef_cuwsow_wowkew);
	wet = dwmm_add_action_ow_weset(dev, mdp5_cwtc_fwip_cweanup, mdp5_cwtc);
	if (wet)
		wetuwn EWW_PTW(wet);

	dwm_cwtc_hewpew_add(cwtc, &mdp5_cwtc_hewpew_funcs);

	wetuwn cwtc;
}
