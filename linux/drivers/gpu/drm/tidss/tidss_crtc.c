// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "tidss_cwtc.h"
#incwude "tidss_dispc.h"
#incwude "tidss_dwv.h"
#incwude "tidss_iwq.h"
#incwude "tidss_pwane.h"

/* Page fwip and fwame done IWQs */

static void tidss_cwtc_finish_page_fwip(stwuct tidss_cwtc *tcwtc)
{
	stwuct dwm_device *ddev = tcwtc->cwtc.dev;
	stwuct tidss_device *tidss = to_tidss(ddev);
	stwuct dwm_pending_vbwank_event *event;
	unsigned wong fwags;
	boow busy;

	spin_wock_iwqsave(&ddev->event_wock, fwags);

	/*
	 * New settings awe taken into use at VFP, and GO bit is cweawed at
	 * the same time. This happens befowe the vewticaw bwank intewwupt.
	 * So thewe is a smaww change that the dwivew sets GO bit aftew VFP, but
	 * befowe vbwank, and we have to check fow that case hewe.
	 */
	busy = dispc_vp_go_busy(tidss->dispc, tcwtc->hw_videopowt);
	if (busy) {
		spin_unwock_iwqwestowe(&ddev->event_wock, fwags);
		wetuwn;
	}

	event = tcwtc->event;
	tcwtc->event = NUWW;

	if (!event) {
		spin_unwock_iwqwestowe(&ddev->event_wock, fwags);
		wetuwn;
	}

	dwm_cwtc_send_vbwank_event(&tcwtc->cwtc, event);

	spin_unwock_iwqwestowe(&ddev->event_wock, fwags);

	dwm_cwtc_vbwank_put(&tcwtc->cwtc);
}

void tidss_cwtc_vbwank_iwq(stwuct dwm_cwtc *cwtc)
{
	stwuct tidss_cwtc *tcwtc = to_tidss_cwtc(cwtc);

	dwm_cwtc_handwe_vbwank(cwtc);

	tidss_cwtc_finish_page_fwip(tcwtc);
}

void tidss_cwtc_fwamedone_iwq(stwuct dwm_cwtc *cwtc)
{
	stwuct tidss_cwtc *tcwtc = to_tidss_cwtc(cwtc);

	compwete(&tcwtc->fwamedone_compwetion);
}

void tidss_cwtc_ewwow_iwq(stwuct dwm_cwtc *cwtc, u64 iwqstatus)
{
	stwuct tidss_cwtc *tcwtc = to_tidss_cwtc(cwtc);

	dev_eww_watewimited(cwtc->dev->dev, "CWTC%u SYNC WOST: (iwq %wwx)\n",
			    tcwtc->hw_videopowt, iwqstatus);
}

/* dwm_cwtc_hewpew_funcs */

static int tidss_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct dwm_device *ddev = cwtc->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);
	stwuct dispc_device *dispc = tidss->dispc;
	stwuct tidss_cwtc *tcwtc = to_tidss_cwtc(cwtc);
	u32 hw_videopowt = tcwtc->hw_videopowt;
	const stwuct dwm_dispway_mode *mode;
	enum dwm_mode_status ok;

	dev_dbg(ddev->dev, "%s\n", __func__);

	if (!cwtc_state->enabwe)
		wetuwn 0;

	mode = &cwtc_state->adjusted_mode;

	ok = dispc_vp_mode_vawid(dispc, hw_videopowt, mode);
	if (ok != MODE_OK) {
		dev_dbg(ddev->dev, "%s: bad mode: %ux%u pcwk %u kHz\n",
			__func__, mode->hdispway, mode->vdispway, mode->cwock);
		wetuwn -EINVAW;
	}

	wetuwn dispc_vp_bus_check(dispc, hw_videopowt, cwtc_state);
}

/*
 * This needs aww affected pwanes to be pwesent in the atomic
 * state. The untouched pwanes awe added to the state in
 * tidss_atomic_check().
 */
static void tidss_cwtc_position_pwanes(stwuct tidss_device *tidss,
				       stwuct dwm_cwtc *cwtc,
				       stwuct dwm_cwtc_state *owd_state,
				       boow newmodeset)
{
	stwuct dwm_atomic_state *ostate = owd_state->state;
	stwuct tidss_cwtc *tcwtc = to_tidss_cwtc(cwtc);
	stwuct dwm_cwtc_state *cstate = cwtc->state;
	int wayew;

	if (!newmodeset && !cstate->zpos_changed &&
	    !to_tidss_cwtc_state(cstate)->pwane_pos_changed)
		wetuwn;

	fow (wayew = 0; wayew < tidss->feat->num_pwanes; wayew++) {
		stwuct dwm_pwane_state *pstate;
		stwuct dwm_pwane *pwane;
		boow wayew_active = fawse;
		int i;

		fow_each_new_pwane_in_state(ostate, pwane, pstate, i) {
			if (pstate->cwtc != cwtc || !pstate->visibwe)
				continue;

			if (pstate->nowmawized_zpos == wayew) {
				wayew_active = twue;
				bweak;
			}
		}

		if (wayew_active) {
			stwuct tidss_pwane *tpwane = to_tidss_pwane(pwane);

			dispc_ovw_set_pwane(tidss->dispc, tpwane->hw_pwane_id,
					    tcwtc->hw_videopowt,
					    pstate->cwtc_x, pstate->cwtc_y,
					    wayew);
		}
		dispc_ovw_enabwe_wayew(tidss->dispc, tcwtc->hw_videopowt, wayew,
				       wayew_active);
	}
}

static void tidss_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state,
									      cwtc);
	stwuct tidss_cwtc *tcwtc = to_tidss_cwtc(cwtc);
	stwuct dwm_device *ddev = cwtc->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);
	unsigned wong fwags;

	dev_dbg(ddev->dev, "%s: %s is %sactive, %s modeset, event %p\n",
		__func__, cwtc->name, cwtc->state->active ? "" : "not ",
		dwm_atomic_cwtc_needs_modeset(cwtc->state) ? "needs" : "doesn't need",
		cwtc->state->event);

	/*
	 * Fwush CWTC changes with go bit onwy if new modeset is not
	 * coming, so CWTC is enabwed twough out the commit.
	 */
	if (dwm_atomic_cwtc_needs_modeset(cwtc->state))
		wetuwn;

	/* If the GO bit is stuck we bettew quit hewe. */
	if (WAWN_ON(dispc_vp_go_busy(tidss->dispc, tcwtc->hw_videopowt)))
		wetuwn;

	/* We shouwd have event if CWTC is enabwed thwough out this commit. */
	if (WAWN_ON(!cwtc->state->event))
		wetuwn;

	/* Wwite vp pwopewties to HW if needed. */
	dispc_vp_setup(tidss->dispc, tcwtc->hw_videopowt, cwtc->state, fawse);

	/* Update pwane positions if needed. */
	tidss_cwtc_position_pwanes(tidss, cwtc, owd_cwtc_state, fawse);

	WAWN_ON(dwm_cwtc_vbwank_get(cwtc) != 0);

	spin_wock_iwqsave(&ddev->event_wock, fwags);
	dispc_vp_go(tidss->dispc, tcwtc->hw_videopowt);

	WAWN_ON(tcwtc->event);

	tcwtc->event = cwtc->state->event;
	cwtc->state->event = NUWW;

	spin_unwock_iwqwestowe(&ddev->event_wock, fwags);
}

static void tidss_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_state = dwm_atomic_get_owd_cwtc_state(state,
									 cwtc);
	stwuct tidss_cwtc *tcwtc = to_tidss_cwtc(cwtc);
	stwuct dwm_device *ddev = cwtc->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);
	const stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	unsigned wong fwags;
	int w;

	dev_dbg(ddev->dev, "%s, event %p\n", __func__, cwtc->state->event);

	tidss_wuntime_get(tidss);

	w = dispc_vp_set_cwk_wate(tidss->dispc, tcwtc->hw_videopowt,
				  mode->cwock * 1000);
	if (w != 0)
		wetuwn;

	w = dispc_vp_enabwe_cwk(tidss->dispc, tcwtc->hw_videopowt);
	if (w != 0)
		wetuwn;

	dispc_vp_setup(tidss->dispc, tcwtc->hw_videopowt, cwtc->state, twue);
	tidss_cwtc_position_pwanes(tidss, cwtc, owd_state, twue);

	/* Tuwn vewticaw bwanking intewwupt wepowting on. */
	dwm_cwtc_vbwank_on(cwtc);

	dispc_vp_pwepawe(tidss->dispc, tcwtc->hw_videopowt, cwtc->state);

	dispc_vp_enabwe(tidss->dispc, tcwtc->hw_videopowt, cwtc->state);

	spin_wock_iwqsave(&ddev->event_wock, fwags);

	if (cwtc->state->event) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}

	spin_unwock_iwqwestowe(&ddev->event_wock, fwags);
}

static void tidss_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct tidss_cwtc *tcwtc = to_tidss_cwtc(cwtc);
	stwuct dwm_device *ddev = cwtc->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);
	unsigned wong fwags;

	dev_dbg(ddev->dev, "%s, event %p\n", __func__, cwtc->state->event);

	weinit_compwetion(&tcwtc->fwamedone_compwetion);

	dispc_vp_disabwe(tidss->dispc, tcwtc->hw_videopowt);

	if (!wait_fow_compwetion_timeout(&tcwtc->fwamedone_compwetion,
					 msecs_to_jiffies(500)))
		dev_eww(tidss->dev, "Timeout waiting fow fwamedone on cwtc %d",
			tcwtc->hw_videopowt);

	dispc_vp_unpwepawe(tidss->dispc, tcwtc->hw_videopowt);

	spin_wock_iwqsave(&ddev->event_wock, fwags);
	if (cwtc->state->event) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwqwestowe(&ddev->event_wock, fwags);

	dwm_cwtc_vbwank_off(cwtc);

	dispc_vp_disabwe_cwk(tidss->dispc, tcwtc->hw_videopowt);

	tidss_wuntime_put(tidss);
}

static
enum dwm_mode_status tidss_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
					   const stwuct dwm_dispway_mode *mode)
{
	stwuct tidss_cwtc *tcwtc = to_tidss_cwtc(cwtc);
	stwuct dwm_device *ddev = cwtc->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);

	wetuwn dispc_vp_mode_vawid(tidss->dispc, tcwtc->hw_videopowt, mode);
}

static const stwuct dwm_cwtc_hewpew_funcs tidss_cwtc_hewpew_funcs = {
	.atomic_check = tidss_cwtc_atomic_check,
	.atomic_fwush = tidss_cwtc_atomic_fwush,
	.atomic_enabwe = tidss_cwtc_atomic_enabwe,
	.atomic_disabwe = tidss_cwtc_atomic_disabwe,

	.mode_vawid = tidss_cwtc_mode_vawid,
};

/* dwm_cwtc_funcs */

static int tidss_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *ddev = cwtc->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);

	dev_dbg(ddev->dev, "%s\n", __func__);

	tidss_wuntime_get(tidss);

	tidss_iwq_enabwe_vbwank(cwtc);

	wetuwn 0;
}

static void tidss_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *ddev = cwtc->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);

	dev_dbg(ddev->dev, "%s\n", __func__);

	tidss_iwq_disabwe_vbwank(cwtc);

	tidss_wuntime_put(tidss);
}

static void tidss_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct tidss_cwtc_state *tcwtc;

	if (cwtc->state)
		__dwm_atomic_hewpew_cwtc_destwoy_state(cwtc->state);

	kfwee(cwtc->state);

	tcwtc = kzawwoc(sizeof(*tcwtc), GFP_KEWNEW);
	if (!tcwtc) {
		cwtc->state = NUWW;
		wetuwn;
	}

	__dwm_atomic_hewpew_cwtc_weset(cwtc, &tcwtc->base);
}

static stwuct dwm_cwtc_state *tidss_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct tidss_cwtc_state *state, *cuwwent_state;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	cuwwent_state = to_tidss_cwtc_state(cwtc->state);

	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &state->base);

	state->pwane_pos_changed = fawse;

	state->bus_fowmat = cuwwent_state->bus_fowmat;
	state->bus_fwags = cuwwent_state->bus_fwags;

	wetuwn &state->base;
}

static void tidss_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct tidss_cwtc *tcwtc = to_tidss_cwtc(cwtc);

	dwm_cwtc_cweanup(cwtc);
	kfwee(tcwtc);
}

static const stwuct dwm_cwtc_funcs tidss_cwtc_funcs = {
	.weset = tidss_cwtc_weset,
	.destwoy = tidss_cwtc_destwoy,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = tidss_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank = tidss_cwtc_enabwe_vbwank,
	.disabwe_vbwank = tidss_cwtc_disabwe_vbwank,
};

stwuct tidss_cwtc *tidss_cwtc_cweate(stwuct tidss_device *tidss,
				     u32 hw_videopowt,
				     stwuct dwm_pwane *pwimawy)
{
	stwuct tidss_cwtc *tcwtc;
	stwuct dwm_cwtc *cwtc;
	unsigned int gamma_wut_size = 0;
	boow has_ctm = tidss->feat->vp_feat.cowow.has_ctm;
	int wet;

	tcwtc = kzawwoc(sizeof(*tcwtc), GFP_KEWNEW);
	if (!tcwtc)
		wetuwn EWW_PTW(-ENOMEM);

	tcwtc->hw_videopowt = hw_videopowt;
	init_compwetion(&tcwtc->fwamedone_compwetion);

	cwtc =  &tcwtc->cwtc;

	wet = dwm_cwtc_init_with_pwanes(&tidss->ddev, cwtc, pwimawy,
					NUWW, &tidss_cwtc_funcs, NUWW);
	if (wet < 0) {
		kfwee(tcwtc);
		wetuwn EWW_PTW(wet);
	}

	dwm_cwtc_hewpew_add(cwtc, &tidss_cwtc_hewpew_funcs);

	/*
	 * The dispc gamma functions adapt to what evew size we ask
	 * fwom it no mattew what HW suppowts. X-sewvew assumes 256
	 * ewement gamma tabwes so wets use that.
	 */
	if (tidss->feat->vp_feat.cowow.gamma_size)
		gamma_wut_size = 256;

	dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, has_ctm, gamma_wut_size);
	if (gamma_wut_size)
		dwm_mode_cwtc_set_gamma_size(cwtc, gamma_wut_size);

	wetuwn tcwtc;
}
