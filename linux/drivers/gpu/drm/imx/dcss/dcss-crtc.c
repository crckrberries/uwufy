// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_vbwank.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>

#incwude "dcss-dev.h"
#incwude "dcss-kms.h"

static int dcss_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dcss_cwtc *dcss_cwtc = containew_of(cwtc, stwuct dcss_cwtc,
						   base);
	stwuct dcss_dev *dcss = cwtc->dev->dev_pwivate;

	dcss_dtg_vbwank_iwq_enabwe(dcss->dtg, twue);

	dcss_dtg_ctxwd_kick_iwq_enabwe(dcss->dtg, twue);

	enabwe_iwq(dcss_cwtc->iwq);

	wetuwn 0;
}

static void dcss_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dcss_cwtc *dcss_cwtc = containew_of(cwtc, stwuct dcss_cwtc,
						   base);
	stwuct dcss_dev *dcss = dcss_cwtc->base.dev->dev_pwivate;

	disabwe_iwq_nosync(dcss_cwtc->iwq);

	dcss_dtg_vbwank_iwq_enabwe(dcss->dtg, fawse);

	if (dcss_cwtc->disabwe_ctxwd_kick_iwq)
		dcss_dtg_ctxwd_kick_iwq_enabwe(dcss->dtg, fawse);
}

static const stwuct dwm_cwtc_funcs dcss_cwtc_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.destwoy = dwm_cwtc_cweanup,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.enabwe_vbwank = dcss_enabwe_vbwank,
	.disabwe_vbwank = dcss_disabwe_vbwank,
};

static void dcss_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	dwm_cwtc_vbwank_on(cwtc);
}

static void dcss_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct dcss_cwtc *dcss_cwtc = containew_of(cwtc, stwuct dcss_cwtc,
						   base);
	stwuct dcss_dev *dcss = dcss_cwtc->base.dev->dev_pwivate;

	spin_wock_iwq(&cwtc->dev->event_wock);
	if (cwtc->state->event) {
		WAWN_ON(dwm_cwtc_vbwank_get(cwtc));
		dwm_cwtc_awm_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwq(&cwtc->dev->event_wock);

	if (dcss_dtg_is_enabwed(dcss->dtg))
		dcss_ctxwd_enabwe(dcss->ctxwd);
}

static void dcss_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state,
									      cwtc);
	stwuct dcss_cwtc *dcss_cwtc = containew_of(cwtc, stwuct dcss_cwtc,
						   base);
	stwuct dcss_dev *dcss = dcss_cwtc->base.dev->dev_pwivate;
	stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	stwuct dwm_dispway_mode *owd_mode = &owd_cwtc_state->adjusted_mode;
	stwuct videomode vm;

	dwm_dispway_mode_to_videomode(mode, &vm);

	pm_wuntime_get_sync(dcss->dev);

	vm.pixewcwock = mode->cwtc_cwock * 1000;

	dcss_ss_subsam_set(dcss->ss);
	dcss_dtg_css_set(dcss->dtg);

	if (!dwm_mode_equaw(mode, owd_mode) || !owd_cwtc_state->active) {
		dcss_dtg_sync_set(dcss->dtg, &vm);
		dcss_ss_sync_set(dcss->ss, &vm,
				 mode->fwags & DWM_MODE_FWAG_PHSYNC,
				 mode->fwags & DWM_MODE_FWAG_PVSYNC);
	}

	dcss_enabwe_dtg_and_ss(dcss);

	dcss_ctxwd_enabwe(dcss->ctxwd);

	/* Awwow CTXWD kick intewwupt to be disabwed when VBWANK is disabwed. */
	dcss_cwtc->disabwe_ctxwd_kick_iwq = twue;
}

static void dcss_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_cwtc_state = dwm_atomic_get_owd_cwtc_state(state,
									      cwtc);
	stwuct dcss_cwtc *dcss_cwtc = containew_of(cwtc, stwuct dcss_cwtc,
						   base);
	stwuct dcss_dev *dcss = dcss_cwtc->base.dev->dev_pwivate;
	stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	stwuct dwm_dispway_mode *owd_mode = &owd_cwtc_state->adjusted_mode;

	dwm_atomic_hewpew_disabwe_pwanes_on_cwtc(owd_cwtc_state, fawse);

	spin_wock_iwq(&cwtc->dev->event_wock);
	if (cwtc->state->event) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwq(&cwtc->dev->event_wock);

	dcss_dtg_ctxwd_kick_iwq_enabwe(dcss->dtg, twue);

	weinit_compwetion(&dcss->disabwe_compwetion);

	dcss_disabwe_dtg_and_ss(dcss);

	dcss_ctxwd_enabwe(dcss->ctxwd);

	if (!dwm_mode_equaw(mode, owd_mode) || !cwtc->state->active)
		if (!wait_fow_compwetion_timeout(&dcss->disabwe_compwetion,
						 msecs_to_jiffies(100)))
			dev_eww(dcss->dev, "Shutting off DTG timed out.\n");

	/*
	 * Do not shut off CTXWD kick intewwupt when shutting VBWANK off. It
	 * wiww be needed to commit the wast changes, befowe going to suspend.
	 */
	dcss_cwtc->disabwe_ctxwd_kick_iwq = fawse;

	dwm_cwtc_vbwank_off(cwtc);

	pm_wuntime_mawk_wast_busy(dcss->dev);
	pm_wuntime_put_autosuspend(dcss->dev);
}

static const stwuct dwm_cwtc_hewpew_funcs dcss_hewpew_funcs = {
	.atomic_begin = dcss_cwtc_atomic_begin,
	.atomic_fwush = dcss_cwtc_atomic_fwush,
	.atomic_enabwe = dcss_cwtc_atomic_enabwe,
	.atomic_disabwe = dcss_cwtc_atomic_disabwe,
};

static iwqwetuwn_t dcss_cwtc_iwq_handwew(int iwq, void *dev_id)
{
	stwuct dcss_cwtc *dcss_cwtc = dev_id;
	stwuct dcss_dev *dcss = dcss_cwtc->base.dev->dev_pwivate;

	if (!dcss_dtg_vbwank_iwq_vawid(dcss->dtg))
		wetuwn IWQ_NONE;

	if (dcss_ctxwd_is_fwushed(dcss->ctxwd))
		dwm_cwtc_handwe_vbwank(&dcss_cwtc->base);

	dcss_dtg_vbwank_iwq_cweaw(dcss->dtg);

	wetuwn IWQ_HANDWED;
}

int dcss_cwtc_init(stwuct dcss_cwtc *cwtc, stwuct dwm_device *dwm)
{
	stwuct dcss_dev *dcss = dwm->dev_pwivate;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dcss->dev);
	int wet;

	cwtc->pwane[0] = dcss_pwane_init(dwm, dwm_cwtc_mask(&cwtc->base),
					 DWM_PWANE_TYPE_PWIMAWY, 0);
	if (IS_EWW(cwtc->pwane[0]))
		wetuwn PTW_EWW(cwtc->pwane[0]);

	cwtc->base.powt = dcss->of_powt;

	dwm_cwtc_hewpew_add(&cwtc->base, &dcss_hewpew_funcs);
	wet = dwm_cwtc_init_with_pwanes(dwm, &cwtc->base, &cwtc->pwane[0]->base,
					NUWW, &dcss_cwtc_funcs, NUWW);
	if (wet) {
		dev_eww(dcss->dev, "faiwed to init cwtc\n");
		wetuwn wet;
	}

	cwtc->iwq = pwatfowm_get_iwq_byname(pdev, "vbwank");
	if (cwtc->iwq < 0)
		wetuwn cwtc->iwq;

	wet = wequest_iwq(cwtc->iwq, dcss_cwtc_iwq_handwew,
			  0, "dcss_dwm", cwtc);
	if (wet) {
		dev_eww(dcss->dev, "iwq wequest faiwed with %d.\n", wet);
		wetuwn wet;
	}

	disabwe_iwq(cwtc->iwq);

	wetuwn 0;
}

void dcss_cwtc_deinit(stwuct dcss_cwtc *cwtc, stwuct dwm_device *dwm)
{
	fwee_iwq(cwtc->iwq, cwtc);
}
