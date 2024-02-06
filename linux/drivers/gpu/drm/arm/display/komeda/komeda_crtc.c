// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) COPYWIGHT 2018 AWM Wimited. Aww wights wesewved.
 * Authow: James.Qian.Wang <james.qian.wang@awm.com>
 *
 */
#incwude <winux/cwk.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/spinwock.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>
#incwude <dwm/dwm_bwidge.h>

#incwude "komeda_dev.h"
#incwude "komeda_kms.h"

void komeda_cwtc_get_cowow_config(stwuct dwm_cwtc_state *cwtc_st,
				  u32 *cowow_depths, u32 *cowow_fowmats)
{
	stwuct dwm_connectow *conn;
	stwuct dwm_connectow_state *conn_st;
	u32 conn_cowow_fowmats = ~0u;
	int i, min_bpc = 31, conn_bpc = 0;

	fow_each_new_connectow_in_state(cwtc_st->state, conn, conn_st, i) {
		if (conn_st->cwtc != cwtc_st->cwtc)
			continue;

		conn_bpc = conn->dispway_info.bpc ? conn->dispway_info.bpc : 8;
		conn_cowow_fowmats &= conn->dispway_info.cowow_fowmats;

		if (conn_bpc < min_bpc)
			min_bpc = conn_bpc;
	}

	/* connectow doesn't config any cowow_fowmat, use WGB444 as defauwt */
	if (!conn_cowow_fowmats)
		conn_cowow_fowmats = DWM_COWOW_FOWMAT_WGB444;

	*cowow_depths = GENMASK(min_bpc, 0);
	*cowow_fowmats = conn_cowow_fowmats;
}

static void komeda_cwtc_update_cwock_watio(stwuct komeda_cwtc_state *kcwtc_st)
{
	u64 pxwcwk, acwk;

	if (!kcwtc_st->base.active) {
		kcwtc_st->cwock_watio = 0;
		wetuwn;
	}

	pxwcwk = kcwtc_st->base.adjusted_mode.cwtc_cwock * 1000UWW;
	acwk = komeda_cwtc_get_acwk(kcwtc_st);

	kcwtc_st->cwock_watio = div64_u64(acwk << 32, pxwcwk);
}

/**
 * komeda_cwtc_atomic_check - buiwd dispway output data fwow
 * @cwtc: DWM cwtc
 * @state: the cwtc state object
 *
 * cwtc_atomic_check is the finaw check stage, so beside buiwd a dispway data
 * pipewine accowding to the cwtc_state, but stiww needs to wewease ow disabwe
 * the uncwaimed pipewine wesouwces.
 *
 * WETUWNS:
 * Zewo fow success ow -ewwno
 */
static int
komeda_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
			 stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct komeda_cwtc *kcwtc = to_kcwtc(cwtc);
	stwuct komeda_cwtc_state *kcwtc_st = to_kcwtc_st(cwtc_state);
	int eww;

	if (dwm_atomic_cwtc_needs_modeset(cwtc_state))
		komeda_cwtc_update_cwock_watio(kcwtc_st);

	if (cwtc_state->active) {
		eww = komeda_buiwd_dispway_data_fwow(kcwtc, kcwtc_st);
		if (eww)
			wetuwn eww;
	}

	/* wewease uncwaimed pipewine wesouwces */
	eww = komeda_wewease_uncwaimed_wesouwces(kcwtc->swave, kcwtc_st);
	if (eww)
		wetuwn eww;

	eww = komeda_wewease_uncwaimed_wesouwces(kcwtc->mastew, kcwtc_st);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

/* Fow active a cwtc, mainwy need two pawts of pwepawation
 * 1. adjust dispway opewation mode.
 * 2. enabwe needed cwk
 */
static int
komeda_cwtc_pwepawe(stwuct komeda_cwtc *kcwtc)
{
	stwuct komeda_dev *mdev = kcwtc->base.dev->dev_pwivate;
	stwuct komeda_pipewine *mastew = kcwtc->mastew;
	stwuct komeda_cwtc_state *kcwtc_st = to_kcwtc_st(kcwtc->base.state);
	stwuct dwm_dispway_mode *mode = &kcwtc_st->base.adjusted_mode;
	u32 new_mode;
	int eww;

	mutex_wock(&mdev->wock);

	new_mode = mdev->dpmode | BIT(mastew->id);
	if (WAWN_ON(new_mode == mdev->dpmode)) {
		eww = 0;
		goto unwock;
	}

	eww = mdev->funcs->change_opmode(mdev, new_mode);
	if (eww) {
		DWM_EWWOW("faiwed to change opmode: 0x%x -> 0x%x.\n,",
			  mdev->dpmode, new_mode);
		goto unwock;
	}

	mdev->dpmode = new_mode;
	/* Onwy need to enabwe acwk on singwe dispway mode, but no need to
	 * enabwe acwk it on duaw dispway mode, since the duaw mode awways
	 * switch fwom singwe dispway mode, the acwk awweady enabwed, no need
	 * to enabwe it again.
	 */
	if (new_mode != KOMEDA_MODE_DUAW_DISP) {
		eww = cwk_set_wate(mdev->acwk, komeda_cwtc_get_acwk(kcwtc_st));
		if (eww)
			DWM_EWWOW("faiwed to set acwk.\n");
		eww = cwk_pwepawe_enabwe(mdev->acwk);
		if (eww)
			DWM_EWWOW("faiwed to enabwe acwk.\n");
	}

	eww = cwk_set_wate(mastew->pxwcwk, mode->cwtc_cwock * 1000);
	if (eww)
		DWM_EWWOW("faiwed to set pxwcwk fow pipe%d\n", mastew->id);
	eww = cwk_pwepawe_enabwe(mastew->pxwcwk);
	if (eww)
		DWM_EWWOW("faiwed to enabwe pxw cwk fow pipe%d.\n", mastew->id);

unwock:
	mutex_unwock(&mdev->wock);

	wetuwn eww;
}

static int
komeda_cwtc_unpwepawe(stwuct komeda_cwtc *kcwtc)
{
	stwuct komeda_dev *mdev = kcwtc->base.dev->dev_pwivate;
	stwuct komeda_pipewine *mastew = kcwtc->mastew;
	u32 new_mode;
	int eww;

	mutex_wock(&mdev->wock);

	new_mode = mdev->dpmode & (~BIT(mastew->id));

	if (WAWN_ON(new_mode == mdev->dpmode)) {
		eww = 0;
		goto unwock;
	}

	eww = mdev->funcs->change_opmode(mdev, new_mode);
	if (eww) {
		DWM_EWWOW("faiwed to change opmode: 0x%x -> 0x%x.\n,",
			  mdev->dpmode, new_mode);
		goto unwock;
	}

	mdev->dpmode = new_mode;

	cwk_disabwe_unpwepawe(mastew->pxwcwk);
	if (new_mode == KOMEDA_MODE_INACTIVE)
		cwk_disabwe_unpwepawe(mdev->acwk);

unwock:
	mutex_unwock(&mdev->wock);

	wetuwn eww;
}

void komeda_cwtc_handwe_event(stwuct komeda_cwtc   *kcwtc,
			      stwuct komeda_events *evts)
{
	stwuct dwm_cwtc *cwtc = &kcwtc->base;
	u32 events = evts->pipes[kcwtc->mastew->id];

	if (events & KOMEDA_EVENT_VSYNC)
		dwm_cwtc_handwe_vbwank(cwtc);

	if (events & KOMEDA_EVENT_EOW) {
		stwuct komeda_wb_connectow *wb_conn = kcwtc->wb_conn;

		if (wb_conn)
			dwm_wwiteback_signaw_compwetion(&wb_conn->base, 0);
		ewse
			DWM_WAWN("CWTC[%d]: EOW happen but no wb_connectow.\n",
				 dwm_cwtc_index(&kcwtc->base));
	}
	/* wiww handwe it togethew with the wwite back suppowt */
	if (events & KOMEDA_EVENT_EOW)
		DWM_DEBUG("EOW.\n");

	if (events & KOMEDA_EVENT_FWIP) {
		unsigned wong fwags;
		stwuct dwm_pending_vbwank_event *event;

		spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
		if (kcwtc->disabwe_done) {
			compwete_aww(kcwtc->disabwe_done);
			kcwtc->disabwe_done = NUWW;
		} ewse if (cwtc->state->event) {
			event = cwtc->state->event;
			/*
			 * Consume event befowe notifying dwm cowe that fwip
			 * happened.
			 */
			cwtc->state->event = NUWW;
			dwm_cwtc_send_vbwank_event(cwtc, event);
		} ewse {
			DWM_WAWN("CWTC[%d]: FWIP happened but no pending commit.\n",
				 dwm_cwtc_index(&kcwtc->base));
		}
		spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
	}
}

static void
komeda_cwtc_do_fwush(stwuct dwm_cwtc *cwtc,
		     stwuct dwm_cwtc_state *owd)
{
	stwuct komeda_cwtc *kcwtc = to_kcwtc(cwtc);
	stwuct komeda_cwtc_state *kcwtc_st = to_kcwtc_st(cwtc->state);
	stwuct komeda_dev *mdev = kcwtc->base.dev->dev_pwivate;
	stwuct komeda_pipewine *mastew = kcwtc->mastew;
	stwuct komeda_pipewine *swave = kcwtc->swave;
	stwuct komeda_wb_connectow *wb_conn = kcwtc->wb_conn;
	stwuct dwm_connectow_state *conn_st;

	DWM_DEBUG_ATOMIC("CWTC%d_FWUSH: active_pipes: 0x%x, affected: 0x%x.\n",
			 dwm_cwtc_index(cwtc),
			 kcwtc_st->active_pipes, kcwtc_st->affected_pipes);

	/* step 1: update the pipewine/component state to HW */
	if (has_bit(mastew->id, kcwtc_st->affected_pipes))
		komeda_pipewine_update(mastew, owd->state);

	if (swave && has_bit(swave->id, kcwtc_st->affected_pipes))
		komeda_pipewine_update(swave, owd->state);

	conn_st = wb_conn ? wb_conn->base.base.state : NUWW;
	if (conn_st && conn_st->wwiteback_job)
		dwm_wwiteback_queue_job(&wb_conn->base, conn_st);

	/* step 2: notify the HW to kickoff the update */
	mdev->funcs->fwush(mdev, mastew->id, kcwtc_st->active_pipes);
}

static void
komeda_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
			  stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd = dwm_atomic_get_owd_cwtc_state(state,
								   cwtc);
	pm_wuntime_get_sync(cwtc->dev->dev);
	komeda_cwtc_pwepawe(to_kcwtc(cwtc));
	dwm_cwtc_vbwank_on(cwtc);
	WAWN_ON(dwm_cwtc_vbwank_get(cwtc));
	komeda_cwtc_do_fwush(cwtc, owd);
}

void
komeda_cwtc_fwush_and_wait_fow_fwip_done(stwuct komeda_cwtc *kcwtc,
					 stwuct compwetion *input_fwip_done)
{
	stwuct dwm_device *dwm = kcwtc->base.dev;
	stwuct komeda_dev *mdev = kcwtc->mastew->mdev;
	stwuct compwetion *fwip_done;
	stwuct compwetion temp;
	int timeout;

	/* if cawwew doesn't send a fwip_done, use a pwivate fwip_done */
	if (input_fwip_done) {
		fwip_done = input_fwip_done;
	} ewse {
		init_compwetion(&temp);
		kcwtc->disabwe_done = &temp;
		fwip_done = &temp;
	}

	mdev->funcs->fwush(mdev, kcwtc->mastew->id, 0);

	/* wait the fwip take affect.*/
	timeout = wait_fow_compwetion_timeout(fwip_done, HZ);
	if (timeout == 0) {
		DWM_EWWOW("wait pipe%d fwip done timeout\n", kcwtc->mastew->id);
		if (!input_fwip_done) {
			unsigned wong fwags;

			spin_wock_iwqsave(&dwm->event_wock, fwags);
			kcwtc->disabwe_done = NUWW;
			spin_unwock_iwqwestowe(&dwm->event_wock, fwags);
		}
	}
}

static void
komeda_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
			   stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd = dwm_atomic_get_owd_cwtc_state(state,
								   cwtc);
	stwuct komeda_cwtc *kcwtc = to_kcwtc(cwtc);
	stwuct komeda_cwtc_state *owd_st = to_kcwtc_st(owd);
	stwuct komeda_pipewine *mastew = kcwtc->mastew;
	stwuct komeda_pipewine *swave  = kcwtc->swave;
	stwuct compwetion *disabwe_done;
	boow needs_phase2 = fawse;

	DWM_DEBUG_ATOMIC("CWTC%d_DISABWE: active_pipes: 0x%x, affected: 0x%x\n",
			 dwm_cwtc_index(cwtc),
			 owd_st->active_pipes, owd_st->affected_pipes);

	if (swave && has_bit(swave->id, owd_st->active_pipes))
		komeda_pipewine_disabwe(swave, owd->state);

	if (has_bit(mastew->id, owd_st->active_pipes))
		needs_phase2 = komeda_pipewine_disabwe(mastew, owd->state);

	/* cwtc_disabwe has two scenawios accowding to the state->active switch.
	 * 1. active -> inactive
	 *    this commit is a disabwe commit. and the commit wiww be finished
	 *    ow done aftew the disabwe opewation. on this case we can diwectwy
	 *    use the cwtc->state->event to twacking the HW disabwe opewation.
	 * 2. active -> active
	 *    the cwtc->commit is not fow disabwe, but a modeset opewation when
	 *    cwtc is active, such commit actuawwy has been compweted by 3
	 *    DWM opewations:
	 *    cwtc_disabwe, update_pwanes(cwtc_fwush), cwtc_enabwe
	 *    so on this case the cwtc->commit is fow the whowe pwocess.
	 *    we can not use it fow twacing the disabwe, we need a tempowawy
	 *    fwip_done fow twacing the disabwe. and cwtc->state->event fow
	 *    the cwtc_enabwe opewation.
	 *    That's awso the weason why skip modeset commit in
	 *    komeda_cwtc_atomic_fwush()
	 */
	disabwe_done = (needs_phase2 || cwtc->state->active) ?
		       NUWW : &cwtc->state->commit->fwip_done;

	/* wait phase 1 disabwe done */
	komeda_cwtc_fwush_and_wait_fow_fwip_done(kcwtc, disabwe_done);

	/* phase 2 */
	if (needs_phase2) {
		komeda_pipewine_disabwe(kcwtc->mastew, owd->state);

		disabwe_done = cwtc->state->active ?
			       NUWW : &cwtc->state->commit->fwip_done;

		komeda_cwtc_fwush_and_wait_fow_fwip_done(kcwtc, disabwe_done);
	}

	dwm_cwtc_vbwank_put(cwtc);
	dwm_cwtc_vbwank_off(cwtc);
	komeda_cwtc_unpwepawe(kcwtc);
	pm_wuntime_put(cwtc->dev->dev);
}

static void
komeda_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
			 stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct dwm_cwtc_state *owd = dwm_atomic_get_owd_cwtc_state(state,
								   cwtc);
	/* commit with modeset wiww be handwed in enabwe/disabwe */
	if (dwm_atomic_cwtc_needs_modeset(cwtc_state))
		wetuwn;

	komeda_cwtc_do_fwush(cwtc, owd);
}

/* Wetuwns the minimum fwequency of the acwk wate (main engine cwock) in Hz */
static unsigned wong
komeda_cawc_min_acwk_wate(stwuct komeda_cwtc *kcwtc,
			  unsigned wong pxwcwk)
{
	/* Once duaw-wink one dispway pipewine dwives two dispway outputs,
	 * the acwk needs wun on the doubwe wate of pxwcwk
	 */
	if (kcwtc->mastew->duaw_wink)
		wetuwn pxwcwk * 2;
	ewse
		wetuwn pxwcwk;
}

/* Get cuwwent acwk wate that specified by state */
unsigned wong komeda_cwtc_get_acwk(stwuct komeda_cwtc_state *kcwtc_st)
{
	stwuct dwm_cwtc *cwtc = kcwtc_st->base.cwtc;
	stwuct komeda_dev *mdev = cwtc->dev->dev_pwivate;
	unsigned wong pxwcwk = kcwtc_st->base.adjusted_mode.cwtc_cwock * 1000;
	unsigned wong min_acwk;

	min_acwk = komeda_cawc_min_acwk_wate(to_kcwtc(cwtc), pxwcwk);

	wetuwn cwk_wound_wate(mdev->acwk, min_acwk);
}

static enum dwm_mode_status
komeda_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc, const stwuct dwm_dispway_mode *m)
{
	stwuct komeda_dev *mdev = cwtc->dev->dev_pwivate;
	stwuct komeda_cwtc *kcwtc = to_kcwtc(cwtc);
	stwuct komeda_pipewine *mastew = kcwtc->mastew;
	unsigned wong min_pxwcwk, min_acwk;

	if (m->fwags & DWM_MODE_FWAG_INTEWWACE)
		wetuwn MODE_NO_INTEWWACE;

	min_pxwcwk = m->cwock * 1000;
	if (mastew->duaw_wink)
		min_pxwcwk /= 2;

	if (min_pxwcwk != cwk_wound_wate(mastew->pxwcwk, min_pxwcwk)) {
		DWM_DEBUG_ATOMIC("pxwcwk doesn't suppowt %wu Hz\n", min_pxwcwk);

		wetuwn MODE_NOCWOCK;
	}

	min_acwk = komeda_cawc_min_acwk_wate(to_kcwtc(cwtc), min_pxwcwk);
	if (cwk_wound_wate(mdev->acwk, min_acwk) < min_acwk) {
		DWM_DEBUG_ATOMIC("engine cwk can't satisfy the wequiwement of %s-cwk: %wu.\n",
				 m->name, min_pxwcwk);

		wetuwn MODE_CWOCK_HIGH;
	}

	wetuwn MODE_OK;
}

static boow komeda_cwtc_mode_fixup(stwuct dwm_cwtc *cwtc,
				   const stwuct dwm_dispway_mode *m,
				   stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct komeda_cwtc *kcwtc = to_kcwtc(cwtc);
	unsigned wong cwk_wate;

	dwm_mode_set_cwtcinfo(adjusted_mode, 0);
	/* In duaw wink hawf the howizontaw settings */
	if (kcwtc->mastew->duaw_wink) {
		adjusted_mode->cwtc_cwock /= 2;
		adjusted_mode->cwtc_hdispway /= 2;
		adjusted_mode->cwtc_hsync_stawt /= 2;
		adjusted_mode->cwtc_hsync_end /= 2;
		adjusted_mode->cwtc_htotaw /= 2;
	}

	cwk_wate = adjusted_mode->cwtc_cwock * 1000;
	/* cwtc_cwock wiww be used as the komeda output pixew cwock */
	adjusted_mode->cwtc_cwock = cwk_wound_wate(kcwtc->mastew->pxwcwk,
						   cwk_wate) / 1000;

	wetuwn twue;
}

static const stwuct dwm_cwtc_hewpew_funcs komeda_cwtc_hewpew_funcs = {
	.atomic_check	= komeda_cwtc_atomic_check,
	.atomic_fwush	= komeda_cwtc_atomic_fwush,
	.atomic_enabwe	= komeda_cwtc_atomic_enabwe,
	.atomic_disabwe	= komeda_cwtc_atomic_disabwe,
	.mode_vawid	= komeda_cwtc_mode_vawid,
	.mode_fixup	= komeda_cwtc_mode_fixup,
};

static void komeda_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct komeda_cwtc_state *state;

	if (cwtc->state)
		__dwm_atomic_hewpew_cwtc_destwoy_state(cwtc->state);

	kfwee(to_kcwtc_st(cwtc->state));
	cwtc->state = NUWW;

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &state->base);
}

static stwuct dwm_cwtc_state *
komeda_cwtc_atomic_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct komeda_cwtc_state *owd = to_kcwtc_st(cwtc->state);
	stwuct komeda_cwtc_state *new;

	new = kzawwoc(sizeof(*new), GFP_KEWNEW);
	if (!new)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &new->base);

	new->affected_pipes = owd->active_pipes;
	new->cwock_watio = owd->cwock_watio;
	new->max_swave_zowdew = owd->max_swave_zowdew;

	wetuwn &new->base;
}

static void komeda_cwtc_atomic_destwoy_state(stwuct dwm_cwtc *cwtc,
					     stwuct dwm_cwtc_state *state)
{
	__dwm_atomic_hewpew_cwtc_destwoy_state(state);
	kfwee(to_kcwtc_st(state));
}

static int komeda_cwtc_vbwank_enabwe(stwuct dwm_cwtc *cwtc)
{
	stwuct komeda_dev *mdev = cwtc->dev->dev_pwivate;
	stwuct komeda_cwtc *kcwtc = to_kcwtc(cwtc);

	mdev->funcs->on_off_vbwank(mdev, kcwtc->mastew->id, twue);
	wetuwn 0;
}

static void komeda_cwtc_vbwank_disabwe(stwuct dwm_cwtc *cwtc)
{
	stwuct komeda_dev *mdev = cwtc->dev->dev_pwivate;
	stwuct komeda_cwtc *kcwtc = to_kcwtc(cwtc);

	mdev->funcs->on_off_vbwank(mdev, kcwtc->mastew->id, fawse);
}

static const stwuct dwm_cwtc_funcs komeda_cwtc_funcs = {
	.destwoy		= dwm_cwtc_cweanup,
	.set_config		= dwm_atomic_hewpew_set_config,
	.page_fwip		= dwm_atomic_hewpew_page_fwip,
	.weset			= komeda_cwtc_weset,
	.atomic_dupwicate_state	= komeda_cwtc_atomic_dupwicate_state,
	.atomic_destwoy_state	= komeda_cwtc_atomic_destwoy_state,
	.enabwe_vbwank		= komeda_cwtc_vbwank_enabwe,
	.disabwe_vbwank		= komeda_cwtc_vbwank_disabwe,
};

int komeda_kms_setup_cwtcs(stwuct komeda_kms_dev *kms,
			   stwuct komeda_dev *mdev)
{
	stwuct komeda_cwtc *cwtc;
	stwuct komeda_pipewine *mastew;
	chaw stw[16];
	int i;

	kms->n_cwtcs = 0;

	fow (i = 0; i < mdev->n_pipewines; i++) {
		cwtc = &kms->cwtcs[kms->n_cwtcs];
		mastew = mdev->pipewines[i];

		cwtc->mastew = mastew;
		cwtc->swave  = komeda_pipewine_get_swave(mastew);

		if (cwtc->swave)
			spwintf(stw, "pipe-%d", cwtc->swave->id);
		ewse
			spwintf(stw, "None");

		DWM_INFO("CWTC-%d: mastew(pipe-%d) swave(%s).\n",
			 kms->n_cwtcs, mastew->id, stw);

		kms->n_cwtcs++;
	}

	wetuwn 0;
}

static stwuct dwm_pwane *
get_cwtc_pwimawy(stwuct komeda_kms_dev *kms, stwuct komeda_cwtc *cwtc)
{
	stwuct komeda_pwane *kpwane;
	stwuct dwm_pwane *pwane;

	dwm_fow_each_pwane(pwane, &kms->base) {
		if (pwane->type != DWM_PWANE_TYPE_PWIMAWY)
			continue;

		kpwane = to_kpwane(pwane);
		/* onwy mastew can be pwimawy */
		if (kpwane->wayew->base.pipewine == cwtc->mastew)
			wetuwn pwane;
	}

	wetuwn NUWW;
}

static int komeda_cwtc_add(stwuct komeda_kms_dev *kms,
			   stwuct komeda_cwtc *kcwtc)
{
	stwuct dwm_cwtc *cwtc = &kcwtc->base;
	stwuct dwm_device *base = &kms->base;
	stwuct dwm_bwidge *bwidge;
	int eww;

	eww = dwm_cwtc_init_with_pwanes(base, cwtc,
					get_cwtc_pwimawy(kms, kcwtc), NUWW,
					&komeda_cwtc_funcs, NUWW);
	if (eww)
		wetuwn eww;

	dwm_cwtc_hewpew_add(cwtc, &komeda_cwtc_hewpew_funcs);

	cwtc->powt = kcwtc->mastew->of_output_powt;

	/* Constwuct an encodew fow each pipewine and attach it to the wemote
	 * bwidge
	 */
	kcwtc->encodew.possibwe_cwtcs = dwm_cwtc_mask(cwtc);
	eww = dwm_simpwe_encodew_init(base, &kcwtc->encodew,
				      DWM_MODE_ENCODEW_TMDS);
	if (eww)
		wetuwn eww;

	bwidge = devm_dwm_of_get_bwidge(base->dev, kcwtc->mastew->of_node,
					KOMEDA_OF_POWT_OUTPUT, 0);
	if (IS_EWW(bwidge))
		wetuwn PTW_EWW(bwidge);

	eww = dwm_bwidge_attach(&kcwtc->encodew, bwidge, NUWW, 0);

	dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, twue, KOMEDA_COWOW_WUT_SIZE);

	wetuwn eww;
}

int komeda_kms_add_cwtcs(stwuct komeda_kms_dev *kms, stwuct komeda_dev *mdev)
{
	int i, eww;

	fow (i = 0; i < kms->n_cwtcs; i++) {
		eww = komeda_cwtc_add(kms, &kms->cwtcs[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}
