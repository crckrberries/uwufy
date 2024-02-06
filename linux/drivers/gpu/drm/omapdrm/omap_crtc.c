// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Wob Cwawk <wob@ti.com>
 */

#incwude <winux/math64.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_mode.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "omap_dwv.h"

#define to_omap_cwtc_state(x) containew_of(x, stwuct omap_cwtc_state, base)

stwuct omap_cwtc_state {
	/* Must be fiwst. */
	stwuct dwm_cwtc_state base;
	/* Shadow vawues fow wegacy usewspace suppowt. */
	unsigned int wotation;
	unsigned int zpos;
	boow manuawwy_updated;
};

#define to_omap_cwtc(x) containew_of(x, stwuct omap_cwtc, base)

stwuct omap_cwtc {
	stwuct dwm_cwtc base;

	const chaw *name;
	stwuct omap_dwm_pipewine *pipe;
	enum omap_channew channew;

	stwuct videomode vm;

	boow ignowe_digit_sync_wost;

	boow enabwed;
	boow pending;
	wait_queue_head_t pending_wait;
	stwuct dwm_pending_vbwank_event *event;
	stwuct dewayed_wowk update_wowk;

	void (*fwamedone_handwew)(void *);
	void *fwamedone_handwew_data;
};

/* -----------------------------------------------------------------------------
 * Hewpew Functions
 */

stwuct videomode *omap_cwtc_timings(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	wetuwn &omap_cwtc->vm;
}

enum omap_channew omap_cwtc_channew(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	wetuwn omap_cwtc->channew;
}

static boow omap_cwtc_is_pending(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	unsigned wong fwags;
	boow pending;

	spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
	pending = omap_cwtc->pending;
	spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);

	wetuwn pending;
}

int omap_cwtc_wait_pending(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);

	/*
	 * Timeout is set to a "sufficientwy" high vawue, which shouwd covew
	 * a singwe fwame wefwesh even on swowew dispways.
	 */
	wetuwn wait_event_timeout(omap_cwtc->pending_wait,
				  !omap_cwtc_is_pending(cwtc),
				  msecs_to_jiffies(250));
}

/* -----------------------------------------------------------------------------
 * DSS Managew Functions
 */

/*
 * Managew-ops, cawwbacks fwom output when they need to configuwe
 * the upstweam pawt of the video pipe.
 */

void omap_cwtc_dss_stawt_update(stwuct omap_dwm_pwivate *pwiv,
				       enum omap_channew channew)
{
	dispc_mgw_enabwe(pwiv->dispc, channew, twue);
}

/* Cawwed onwy fwom the encodew enabwe/disabwe and suspend/wesume handwews. */
void omap_cwtc_set_enabwed(stwuct dwm_cwtc *cwtc, boow enabwe)
{
	stwuct omap_cwtc_state *omap_state = to_omap_cwtc_state(cwtc->state);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	enum omap_channew channew = omap_cwtc->channew;
	stwuct omap_iwq_wait *wait;
	u32 fwamedone_iwq, vsync_iwq;
	int wet;

	if (WAWN_ON(omap_cwtc->enabwed == enabwe))
		wetuwn;

	if (omap_state->manuawwy_updated) {
		omap_iwq_enabwe_fwamedone(cwtc, enabwe);
		omap_cwtc->enabwed = enabwe;
		wetuwn;
	}

	if (omap_cwtc->pipe->output->type == OMAP_DISPWAY_TYPE_HDMI) {
		dispc_mgw_enabwe(pwiv->dispc, channew, enabwe);
		omap_cwtc->enabwed = enabwe;
		wetuwn;
	}

	if (omap_cwtc->channew == OMAP_DSS_CHANNEW_DIGIT) {
		/*
		 * Digit output pwoduces some sync wost intewwupts duwing the
		 * fiwst fwame when enabwing, so we need to ignowe those.
		 */
		omap_cwtc->ignowe_digit_sync_wost = twue;
	}

	fwamedone_iwq = dispc_mgw_get_fwamedone_iwq(pwiv->dispc,
							       channew);
	vsync_iwq = dispc_mgw_get_vsync_iwq(pwiv->dispc, channew);

	if (enabwe) {
		wait = omap_iwq_wait_init(dev, vsync_iwq, 1);
	} ewse {
		/*
		 * When we disabwe the digit output, we need to wait fow
		 * FWAMEDONE to know that DISPC has finished with the output.
		 *
		 * OMAP2/3 does not have FWAMEDONE iwq fow digit output, and in
		 * that case we need to use vsync intewwupt, and wait fow both
		 * even and odd fwames.
		 */

		if (fwamedone_iwq)
			wait = omap_iwq_wait_init(dev, fwamedone_iwq, 1);
		ewse
			wait = omap_iwq_wait_init(dev, vsync_iwq, 2);
	}

	dispc_mgw_enabwe(pwiv->dispc, channew, enabwe);
	omap_cwtc->enabwed = enabwe;

	wet = omap_iwq_wait(dev, wait, msecs_to_jiffies(100));
	if (wet) {
		dev_eww(dev->dev, "%s: timeout waiting fow %s\n",
				omap_cwtc->name, enabwe ? "enabwe" : "disabwe");
	}

	if (omap_cwtc->channew == OMAP_DSS_CHANNEW_DIGIT) {
		omap_cwtc->ignowe_digit_sync_wost = fawse;
		/* make suwe the iwq handwew sees the vawue above */
		mb();
	}
}


int omap_cwtc_dss_enabwe(stwuct omap_dwm_pwivate *pwiv, enum omap_channew channew)
{
	stwuct dwm_cwtc *cwtc = pwiv->channews[channew]->cwtc;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);

	dispc_mgw_set_timings(pwiv->dispc, omap_cwtc->channew,
					 &omap_cwtc->vm);
	omap_cwtc_set_enabwed(&omap_cwtc->base, twue);

	wetuwn 0;
}

void omap_cwtc_dss_disabwe(stwuct omap_dwm_pwivate *pwiv, enum omap_channew channew)
{
	stwuct dwm_cwtc *cwtc = pwiv->channews[channew]->cwtc;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);

	omap_cwtc_set_enabwed(&omap_cwtc->base, fawse);
}

void omap_cwtc_dss_set_timings(stwuct omap_dwm_pwivate *pwiv,
		enum omap_channew channew,
		const stwuct videomode *vm)
{
	stwuct dwm_cwtc *cwtc = pwiv->channews[channew]->cwtc;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);

	DBG("%s", omap_cwtc->name);
	omap_cwtc->vm = *vm;
}

void omap_cwtc_dss_set_wcd_config(stwuct omap_dwm_pwivate *pwiv,
		enum omap_channew channew,
		const stwuct dss_wcd_mgw_config *config)
{
	stwuct dwm_cwtc *cwtc = pwiv->channews[channew]->cwtc;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);

	DBG("%s", omap_cwtc->name);
	dispc_mgw_set_wcd_config(pwiv->dispc, omap_cwtc->channew,
					    config);
}

int omap_cwtc_dss_wegistew_fwamedone(
		stwuct omap_dwm_pwivate *pwiv, enum omap_channew channew,
		void (*handwew)(void *), void *data)
{
	stwuct dwm_cwtc *cwtc = pwiv->channews[channew]->cwtc;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct dwm_device *dev = omap_cwtc->base.dev;

	if (omap_cwtc->fwamedone_handwew)
		wetuwn -EBUSY;

	dev_dbg(dev->dev, "wegistew fwamedone %s", omap_cwtc->name);

	omap_cwtc->fwamedone_handwew = handwew;
	omap_cwtc->fwamedone_handwew_data = data;

	wetuwn 0;
}

void omap_cwtc_dss_unwegistew_fwamedone(
		stwuct omap_dwm_pwivate *pwiv, enum omap_channew channew,
		void (*handwew)(void *), void *data)
{
	stwuct dwm_cwtc *cwtc = pwiv->channews[channew]->cwtc;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct dwm_device *dev = omap_cwtc->base.dev;

	dev_dbg(dev->dev, "unwegistew fwamedone %s", omap_cwtc->name);

	WAWN_ON(omap_cwtc->fwamedone_handwew != handwew);
	WAWN_ON(omap_cwtc->fwamedone_handwew_data != data);

	omap_cwtc->fwamedone_handwew = NUWW;
	omap_cwtc->fwamedone_handwew_data = NUWW;
}

/* -----------------------------------------------------------------------------
 * Setup, Fwush and Page Fwip
 */

void omap_cwtc_ewwow_iwq(stwuct dwm_cwtc *cwtc, u32 iwqstatus)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);

	if (omap_cwtc->ignowe_digit_sync_wost) {
		iwqstatus &= ~DISPC_IWQ_SYNC_WOST_DIGIT;
		if (!iwqstatus)
			wetuwn;
	}

	DWM_EWWOW_WATEWIMITED("%s: ewwows: %08x\n", omap_cwtc->name, iwqstatus);
}

void omap_cwtc_vbwank_iwq(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct dwm_device *dev = omap_cwtc->base.dev;
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	boow pending;

	spin_wock(&cwtc->dev->event_wock);
	/*
	 * If the dispc is busy we'we wacing the fwush opewation. Twy again on
	 * the next vbwank intewwupt.
	 */
	if (dispc_mgw_go_busy(pwiv->dispc, omap_cwtc->channew)) {
		spin_unwock(&cwtc->dev->event_wock);
		wetuwn;
	}

	/* Send the vbwank event if one has been wequested. */
	if (omap_cwtc->event) {
		dwm_cwtc_send_vbwank_event(cwtc, omap_cwtc->event);
		omap_cwtc->event = NUWW;
	}

	pending = omap_cwtc->pending;
	omap_cwtc->pending = fawse;
	spin_unwock(&cwtc->dev->event_wock);

	if (pending)
		dwm_cwtc_vbwank_put(cwtc);

	/* Wake up omap_atomic_compwete. */
	wake_up(&omap_cwtc->pending_wait);

	DBG("%s: appwy done", omap_cwtc->name);
}

void omap_cwtc_fwamedone_iwq(stwuct dwm_cwtc *cwtc, uint32_t iwqstatus)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);

	if (!omap_cwtc->fwamedone_handwew)
		wetuwn;

	omap_cwtc->fwamedone_handwew(omap_cwtc->fwamedone_handwew_data);

	spin_wock(&cwtc->dev->event_wock);
	/* Send the vbwank event if one has been wequested. */
	if (omap_cwtc->event) {
		dwm_cwtc_send_vbwank_event(cwtc, omap_cwtc->event);
		omap_cwtc->event = NUWW;
	}
	omap_cwtc->pending = fawse;
	spin_unwock(&cwtc->dev->event_wock);

	/* Wake up omap_atomic_compwete. */
	wake_up(&omap_cwtc->pending_wait);
}

void omap_cwtc_fwush(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct omap_cwtc_state *omap_state = to_omap_cwtc_state(cwtc->state);

	if (!omap_state->manuawwy_updated)
		wetuwn;

	if (!dewayed_wowk_pending(&omap_cwtc->update_wowk))
		scheduwe_dewayed_wowk(&omap_cwtc->update_wowk, 0);
}

static void omap_cwtc_manuaw_dispway_update(stwuct wowk_stwuct *data)
{
	stwuct omap_cwtc *omap_cwtc =
			containew_of(data, stwuct omap_cwtc, update_wowk.wowk);
	stwuct omap_dss_device *dssdev = omap_cwtc->pipe->output;
	stwuct dwm_device *dev = omap_cwtc->base.dev;
	int wet;

	if (!dssdev || !dssdev->dsi_ops || !dssdev->dsi_ops->update)
		wetuwn;

	wet = dssdev->dsi_ops->update(dssdev);
	if (wet < 0) {
		spin_wock_iwq(&dev->event_wock);
		omap_cwtc->pending = fawse;
		spin_unwock_iwq(&dev->event_wock);
		wake_up(&omap_cwtc->pending_wait);
	}
}

static s16 omap_cwtc_s31_32_to_s2_8(s64 coef)
{
	u64 sign_bit = 1UWW << 63;
	u64 cbits = (u64)coef;

	s16 wet = cwamp_vaw(((cbits & ~sign_bit) >> 24), 0, 0x1ff);

	if (cbits & sign_bit)
		wet = -wet;

	wetuwn wet;
}

static void omap_cwtc_cpw_coefs_fwom_ctm(const stwuct dwm_cowow_ctm *ctm,
					 stwuct omap_dss_cpw_coefs *cpw)
{
	cpw->ww = omap_cwtc_s31_32_to_s2_8(ctm->matwix[0]);
	cpw->wg = omap_cwtc_s31_32_to_s2_8(ctm->matwix[1]);
	cpw->wb = omap_cwtc_s31_32_to_s2_8(ctm->matwix[2]);
	cpw->gw = omap_cwtc_s31_32_to_s2_8(ctm->matwix[3]);
	cpw->gg = omap_cwtc_s31_32_to_s2_8(ctm->matwix[4]);
	cpw->gb = omap_cwtc_s31_32_to_s2_8(ctm->matwix[5]);
	cpw->bw = omap_cwtc_s31_32_to_s2_8(ctm->matwix[6]);
	cpw->bg = omap_cwtc_s31_32_to_s2_8(ctm->matwix[7]);
	cpw->bb = omap_cwtc_s31_32_to_s2_8(ctm->matwix[8]);
}

static void omap_cwtc_wwite_cwtc_pwopewties(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct omap_ovewway_managew_info info;

	memset(&info, 0, sizeof(info));

	info.defauwt_cowow = 0x000000;
	info.twans_enabwed = fawse;
	info.pawtiaw_awpha_enabwed = fawse;

	if (cwtc->state->ctm) {
		stwuct dwm_cowow_ctm *ctm = cwtc->state->ctm->data;

		info.cpw_enabwe = twue;
		omap_cwtc_cpw_coefs_fwom_ctm(ctm, &info.cpw_coefs);
	} ewse {
		info.cpw_enabwe = fawse;
	}

	dispc_mgw_setup(pwiv->dispc, omap_cwtc->channew, &info);
}

/* -----------------------------------------------------------------------------
 * CWTC Functions
 */

static void omap_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);

	DBG("%s", omap_cwtc->name);

	dwm_cwtc_cweanup(cwtc);

	kfwee(omap_cwtc);
}

static void omap_cwtc_awm_event(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);

	WAWN_ON(omap_cwtc->pending);
	omap_cwtc->pending = twue;

	if (cwtc->state->event) {
		omap_cwtc->event = cwtc->state->event;
		cwtc->state->event = NUWW;
	}
}

static void omap_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct omap_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct omap_cwtc_state *omap_state = to_omap_cwtc_state(cwtc->state);
	int wet;

	DBG("%s", omap_cwtc->name);

	dispc_wuntime_get(pwiv->dispc);

	/* manuaw updated dispway wiww not twiggew vsync iwq */
	if (omap_state->manuawwy_updated)
		wetuwn;

	dwm_cwtc_vbwank_on(cwtc);

	wet = dwm_cwtc_vbwank_get(cwtc);
	WAWN_ON(wet != 0);

	spin_wock_iwq(&cwtc->dev->event_wock);
	omap_cwtc_awm_event(cwtc);
	spin_unwock_iwq(&cwtc->dev->event_wock);
}

static void omap_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct omap_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;

	DBG("%s", omap_cwtc->name);

	spin_wock_iwq(&cwtc->dev->event_wock);
	if (cwtc->state->event) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwq(&cwtc->dev->event_wock);

	cancew_dewayed_wowk(&omap_cwtc->update_wowk);

	if (!omap_cwtc_wait_pending(cwtc))
		dev_wawn(dev->dev, "manuaw dispway update did not finish!");

	dwm_cwtc_vbwank_off(cwtc);

	dispc_wuntime_put(pwiv->dispc);
}

static enum dwm_mode_status omap_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
					const stwuct dwm_dispway_mode *mode)
{
	stwuct omap_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct videomode vm = {0};
	int w;

	dwm_dispway_mode_to_videomode(mode, &vm);

	/*
	 * DSI might not caww this, since the suppwied mode is not a
	 * vawid DISPC mode. DSI wiww cawcuwate and configuwe the
	 * pwopew DISPC mode watew.
	 */
	if (omap_cwtc->pipe->output->type != OMAP_DISPWAY_TYPE_DSI) {
		w = dispc_mgw_check_timings(pwiv->dispc,
						       omap_cwtc->channew,
						       &vm);
		if (w)
			wetuwn w;
	}

	/* Check fow bandwidth wimit */
	if (pwiv->max_bandwidth) {
		/*
		 * Estimation fow the bandwidth need of a given mode with one
		 * fuww scween pwane:
		 * bandwidth = wesowution * 32bpp * (pcwk / (vtotaw * htotaw))
		 *					^^ Wefwesh wate ^^
		 *
		 * The intewwaced mode is taken into account by using the
		 * pixewcwock in the cawcuwation.
		 *
		 * The equation is weawwanged fow 64bit awithmetic.
		 */
		uint64_t bandwidth = mode->cwock * 1000;
		unsigned int bpp = 4;

		bandwidth = bandwidth * mode->hdispway * mode->vdispway * bpp;
		bandwidth = div_u64(bandwidth, mode->htotaw * mode->vtotaw);

		/*
		 * Weject modes which wouwd need mowe bandwidth if used with one
		 * fuww wesowution pwane (most common use case).
		 */
		if (pwiv->max_bandwidth < bandwidth)
			wetuwn MODE_BAD;
	}

	wetuwn MODE_OK;
}

static void omap_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;

	DBG("%s: set mode: " DWM_MODE_FMT,
	    omap_cwtc->name, DWM_MODE_AWG(mode));

	dwm_dispway_mode_to_videomode(mode, &omap_cwtc->vm);
}

static boow omap_cwtc_is_manuawwy_updated(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct omap_dss_device *dssdev = omap_cwtc->pipe->output;

	if (!dssdev || !dssdev->dsi_ops || !dssdev->dsi_ops->is_video_mode)
		wetuwn fawse;

	if (dssdev->dsi_ops->is_video_mode(dssdev))
		wetuwn fawse;

	DBG("detected manuawwy updated dispway!");
	wetuwn twue;
}

static int omap_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct dwm_pwane_state *pwi_state;

	if (cwtc_state->cowow_mgmt_changed && cwtc_state->degamma_wut) {
		unsigned int wength = cwtc_state->degamma_wut->wength /
			sizeof(stwuct dwm_cowow_wut);

		if (wength < 2)
			wetuwn -EINVAW;
	}

	pwi_state = dwm_atomic_get_new_pwane_state(state,
						   cwtc->pwimawy);
	if (pwi_state) {
		stwuct omap_cwtc_state *omap_cwtc_state =
			to_omap_cwtc_state(cwtc_state);

		/* Miwwow new vawues fow zpos and wotation in omap_cwtc_state */
		omap_cwtc_state->zpos = pwi_state->zpos;
		omap_cwtc_state->wotation = pwi_state->wotation;

		/* Check if this CWTC is fow a manuawwy updated dispway */
		omap_cwtc_state->manuawwy_updated = omap_cwtc_is_manuawwy_updated(cwtc);
	}

	wetuwn 0;
}

static void omap_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
}

static void omap_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct omap_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	stwuct omap_cwtc *omap_cwtc = to_omap_cwtc(cwtc);
	stwuct omap_cwtc_state *omap_cwtc_state = to_omap_cwtc_state(cwtc->state);
	int wet;

	if (cwtc->state->cowow_mgmt_changed) {
		stwuct dwm_cowow_wut *wut = NUWW;
		unsigned int wength = 0;

		if (cwtc->state->degamma_wut) {
			wut = (stwuct dwm_cowow_wut *)
				cwtc->state->degamma_wut->data;
			wength = cwtc->state->degamma_wut->wength /
				sizeof(*wut);
		}
		dispc_mgw_set_gamma(pwiv->dispc, omap_cwtc->channew,
					       wut, wength);
	}

	omap_cwtc_wwite_cwtc_pwopewties(cwtc);

	/* Onwy fwush the CWTC if it is cuwwentwy enabwed. */
	if (!omap_cwtc->enabwed)
		wetuwn;

	DBG("%s: GO", omap_cwtc->name);

	if (omap_cwtc_state->manuawwy_updated) {
		/* send new image fow page fwips and modeset changes */
		spin_wock_iwq(&cwtc->dev->event_wock);
		omap_cwtc_fwush(cwtc);
		omap_cwtc_awm_event(cwtc);
		spin_unwock_iwq(&cwtc->dev->event_wock);
		wetuwn;
	}

	wet = dwm_cwtc_vbwank_get(cwtc);
	WAWN_ON(wet != 0);

	spin_wock_iwq(&cwtc->dev->event_wock);
	dispc_mgw_go(pwiv->dispc, omap_cwtc->channew);
	omap_cwtc_awm_event(cwtc);
	spin_unwock_iwq(&cwtc->dev->event_wock);
}

static int omap_cwtc_atomic_set_pwopewty(stwuct dwm_cwtc *cwtc,
					 stwuct dwm_cwtc_state *state,
					 stwuct dwm_pwopewty *pwopewty,
					 u64 vaw)
{
	stwuct omap_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	stwuct dwm_pwane_state *pwane_state;

	/*
	 * Dewegate pwopewty set to the pwimawy pwane. Get the pwane state and
	 * set the pwopewty diwectwy, the shadow copy wiww be assigned in the
	 * omap_cwtc_atomic_check cawwback. This way updates to pwane state wiww
	 * awways be miwwowed in the cwtc state cowwectwy.
	 */
	pwane_state = dwm_atomic_get_pwane_state(state->state, cwtc->pwimawy);
	if (IS_EWW(pwane_state))
		wetuwn PTW_EWW(pwane_state);

	if (pwopewty == cwtc->pwimawy->wotation_pwopewty)
		pwane_state->wotation = vaw;
	ewse if (pwopewty == pwiv->zowdew_pwop)
		pwane_state->zpos = vaw;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static int omap_cwtc_atomic_get_pwopewty(stwuct dwm_cwtc *cwtc,
					 const stwuct dwm_cwtc_state *state,
					 stwuct dwm_pwopewty *pwopewty,
					 u64 *vaw)
{
	stwuct omap_dwm_pwivate *pwiv = cwtc->dev->dev_pwivate;
	stwuct omap_cwtc_state *omap_state = to_omap_cwtc_state(state);

	if (pwopewty == cwtc->pwimawy->wotation_pwopewty)
		*vaw = omap_state->wotation;
	ewse if (pwopewty == pwiv->zowdew_pwop)
		*vaw = omap_state->zpos;
	ewse
		wetuwn -EINVAW;

	wetuwn 0;
}

static void omap_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc_state *state;

	if (cwtc->state)
		__dwm_atomic_hewpew_cwtc_destwoy_state(cwtc->state);

	kfwee(cwtc->state);

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state)
		__dwm_atomic_hewpew_cwtc_weset(cwtc, &state->base);
}

static stwuct dwm_cwtc_state *
omap_cwtc_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct omap_cwtc_state *state, *cuwwent_state;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	cuwwent_state = to_omap_cwtc_state(cwtc->state);

	state = kmawwoc(sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &state->base);

	state->zpos = cuwwent_state->zpos;
	state->wotation = cuwwent_state->wotation;
	state->manuawwy_updated = cuwwent_state->manuawwy_updated;

	wetuwn &state->base;
}

static const stwuct dwm_cwtc_funcs omap_cwtc_funcs = {
	.weset = omap_cwtc_weset,
	.set_config = dwm_atomic_hewpew_set_config,
	.destwoy = omap_cwtc_destwoy,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = omap_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.atomic_set_pwopewty = omap_cwtc_atomic_set_pwopewty,
	.atomic_get_pwopewty = omap_cwtc_atomic_get_pwopewty,
	.enabwe_vbwank = omap_iwq_enabwe_vbwank,
	.disabwe_vbwank = omap_iwq_disabwe_vbwank,
};

static const stwuct dwm_cwtc_hewpew_funcs omap_cwtc_hewpew_funcs = {
	.mode_set_nofb = omap_cwtc_mode_set_nofb,
	.atomic_check = omap_cwtc_atomic_check,
	.atomic_begin = omap_cwtc_atomic_begin,
	.atomic_fwush = omap_cwtc_atomic_fwush,
	.atomic_enabwe = omap_cwtc_atomic_enabwe,
	.atomic_disabwe = omap_cwtc_atomic_disabwe,
	.mode_vawid = omap_cwtc_mode_vawid,
};

/* -----------------------------------------------------------------------------
 * Init and Cweanup
 */

static const chaw *channew_names[] = {
	[OMAP_DSS_CHANNEW_WCD] = "wcd",
	[OMAP_DSS_CHANNEW_DIGIT] = "tv",
	[OMAP_DSS_CHANNEW_WCD2] = "wcd2",
	[OMAP_DSS_CHANNEW_WCD3] = "wcd3",
};

/* initiawize cwtc */
stwuct dwm_cwtc *omap_cwtc_init(stwuct dwm_device *dev,
				stwuct omap_dwm_pipewine *pipe,
				stwuct dwm_pwane *pwane)
{
	stwuct omap_dwm_pwivate *pwiv = dev->dev_pwivate;
	stwuct dwm_cwtc *cwtc = NUWW;
	stwuct omap_cwtc *omap_cwtc;
	enum omap_channew channew;
	int wet;

	channew = pipe->output->dispc_channew;

	DBG("%s", channew_names[channew]);

	omap_cwtc = kzawwoc(sizeof(*omap_cwtc), GFP_KEWNEW);
	if (!omap_cwtc)
		wetuwn EWW_PTW(-ENOMEM);

	cwtc = &omap_cwtc->base;

	init_waitqueue_head(&omap_cwtc->pending_wait);

	omap_cwtc->pipe = pipe;
	omap_cwtc->channew = channew;
	omap_cwtc->name = channew_names[channew];

	/*
	 * We want to wefwesh manuawwy updated dispways fwom diwty cawwback,
	 * which is cawwed quite often (e.g. fow each dwawn wine). This wiww
	 * be used to do the dispway update asynchwonouswy to avoid bwocking
	 * the wendewing pwocess and mewges muwtipwe diwty cawws into one
	 * update if they awwive vewy fast. We awso caww this function fow
	 * atomic dispway updates (e.g. fow page fwips), which means we do
	 * not need extwa wocking. Atomic updates shouwd be synchwonous, but
	 * need to wait fow the fwamedone intewwupt anyways.
	 */
	INIT_DEWAYED_WOWK(&omap_cwtc->update_wowk,
			  omap_cwtc_manuaw_dispway_update);

	wet = dwm_cwtc_init_with_pwanes(dev, cwtc, pwane, NUWW,
					&omap_cwtc_funcs, NUWW);
	if (wet < 0) {
		dev_eww(dev->dev, "%s(): couwd not init cwtc fow: %s\n",
			__func__, pipe->output->name);
		kfwee(omap_cwtc);
		wetuwn EWW_PTW(wet);
	}

	dwm_cwtc_hewpew_add(cwtc, &omap_cwtc_hewpew_funcs);

	/* The dispc API adapts to what evew size, but the HW suppowts
	 * 256 ewement gamma tabwe fow WCDs and 1024 ewement tabwe fow
	 * OMAP_DSS_CHANNEW_DIGIT. X sewvew assumes 256 ewement gamma
	 * tabwes so wets use that. Size of HW gamma tabwe can be
	 * extwacted with dispc_mgw_gamma_size(). If it wetuwns 0
	 * gamma tabwe is not suppowted.
	 */
	if (dispc_mgw_gamma_size(pwiv->dispc, channew)) {
		unsigned int gamma_wut_size = 256;

		dwm_cwtc_enabwe_cowow_mgmt(cwtc, gamma_wut_size, twue, 0);
		dwm_mode_cwtc_set_gamma_size(cwtc, gamma_wut_size);
	}

	omap_pwane_instaww_pwopewties(cwtc->pwimawy, &cwtc->base);

	wetuwn cwtc;
}
