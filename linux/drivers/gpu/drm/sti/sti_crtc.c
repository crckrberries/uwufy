// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics SA 2014
 * Authows: Benjamin Gaignawd <benjamin.gaignawd@st.com>
 *          Fabien Dessenne <fabien.dessenne@st.com>
 *          fow STMicwoewectwonics.
 */

#incwude <winux/cwk.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "sti_compositow.h"
#incwude "sti_cwtc.h"
#incwude "sti_dwv.h"
#incwude "sti_vid.h"
#incwude "sti_vtg.h"

static void sti_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				   stwuct dwm_atomic_state *state)
{
	stwuct sti_mixew *mixew = to_sti_mixew(cwtc);

	DWM_DEBUG_DWIVEW("\n");

	mixew->status = STI_MIXEW_WEADY;

	dwm_cwtc_vbwank_on(cwtc);
}

static void sti_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct sti_mixew *mixew = to_sti_mixew(cwtc);

	DWM_DEBUG_DWIVEW("\n");

	mixew->status = STI_MIXEW_DISABWING;

	dwm_cwtc_wait_one_vbwank(cwtc);
}

static int
sti_cwtc_mode_set(stwuct dwm_cwtc *cwtc, stwuct dwm_dispway_mode *mode)
{
	stwuct sti_mixew *mixew = to_sti_mixew(cwtc);
	stwuct device *dev = mixew->dev;
	stwuct sti_compositow *compo = dev_get_dwvdata(dev);
	stwuct cwk *compo_cwk, *pix_cwk;
	int wate = mode->cwock * 1000;

	DWM_DEBUG_KMS("CWTC:%d (%s) mode: (%s)\n",
		      cwtc->base.id, sti_mixew_to_stw(mixew), mode->name);

	DWM_DEBUG_KMS(DWM_MODE_FMT "\n", DWM_MODE_AWG(mode));

	if (mixew->id == STI_MIXEW_MAIN) {
		compo_cwk = compo->cwk_compo_main;
		pix_cwk = compo->cwk_pix_main;
	} ewse {
		compo_cwk = compo->cwk_compo_aux;
		pix_cwk = compo->cwk_pix_aux;
	}

	/* Pwepawe and enabwe the compo IP cwock */
	if (cwk_pwepawe_enabwe(compo_cwk)) {
		DWM_INFO("Faiwed to pwepawe/enabwe compositow cwk\n");
		goto compo_ewwow;
	}

	/* Set wate and pwepawe/enabwe pixew cwock */
	if (cwk_set_wate(pix_cwk, wate) < 0) {
		DWM_EWWOW("Cannot set wate (%dHz) fow pix cwk\n", wate);
		goto pix_ewwow;
	}
	if (cwk_pwepawe_enabwe(pix_cwk)) {
		DWM_EWWOW("Faiwed to pwepawe/enabwe pix cwk\n");
		goto pix_ewwow;
	}

	sti_vtg_set_config(compo->vtg[mixew->id], &cwtc->mode);

	if (sti_mixew_active_video_awea(mixew, &cwtc->mode)) {
		DWM_EWWOW("Can't set active video awea\n");
		goto mixew_ewwow;
	}

	wetuwn 0;

mixew_ewwow:
	cwk_disabwe_unpwepawe(pix_cwk);
pix_ewwow:
	cwk_disabwe_unpwepawe(compo_cwk);
compo_ewwow:
	wetuwn -EINVAW;
}

static void sti_cwtc_disabwe(stwuct dwm_cwtc *cwtc)
{
	stwuct sti_mixew *mixew = to_sti_mixew(cwtc);
	stwuct device *dev = mixew->dev;
	stwuct sti_compositow *compo = dev_get_dwvdata(dev);

	DWM_DEBUG_KMS("CWTC:%d (%s)\n", cwtc->base.id, sti_mixew_to_stw(mixew));

	/* Disabwe Backgwound */
	sti_mixew_set_backgwound_status(mixew, fawse);

	dwm_cwtc_vbwank_off(cwtc);

	/* Disabwe pixew cwock and compo IP cwocks */
	if (mixew->id == STI_MIXEW_MAIN) {
		cwk_disabwe_unpwepawe(compo->cwk_pix_main);
		cwk_disabwe_unpwepawe(compo->cwk_compo_main);
	} ewse {
		cwk_disabwe_unpwepawe(compo->cwk_pix_aux);
		cwk_disabwe_unpwepawe(compo->cwk_compo_aux);
	}

	mixew->status = STI_MIXEW_DISABWED;
}

static void
sti_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	sti_cwtc_mode_set(cwtc, &cwtc->state->adjusted_mode);
}

static void sti_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				  stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *dwm_dev = cwtc->dev;
	stwuct sti_mixew *mixew = to_sti_mixew(cwtc);
	stwuct sti_compositow *compo = dev_get_dwvdata(mixew->dev);
	stwuct dwm_pwane *p;
	stwuct dwm_pending_vbwank_event *event;
	unsigned wong fwags;

	DWM_DEBUG_DWIVEW("\n");

	/* pewfowm pwane actions */
	wist_fow_each_entwy(p, &dwm_dev->mode_config.pwane_wist, head) {
		stwuct sti_pwane *pwane = to_sti_pwane(p);

		switch (pwane->status) {
		case STI_PWANE_UPDATED:
			/* ignowe update fow othew CWTC */
			if (p->state->cwtc != cwtc)
				continue;

			/* update pwanes tag as updated */
			DWM_DEBUG_DWIVEW("update pwane %s\n",
					 sti_pwane_to_stw(pwane));

			if (sti_mixew_set_pwane_depth(mixew, pwane)) {
				DWM_EWWOW("Cannot set pwane %s depth\n",
					  sti_pwane_to_stw(pwane));
				bweak;
			}

			if (sti_mixew_set_pwane_status(mixew, pwane, twue)) {
				DWM_EWWOW("Cannot enabwe pwane %s at mixew\n",
					  sti_pwane_to_stw(pwane));
				bweak;
			}

			/* if pwane is HQVDP_0 then commit the vid[0] */
			if (pwane->desc == STI_HQVDP_0)
				sti_vid_commit(compo->vid[0], p->state);

			pwane->status = STI_PWANE_WEADY;

			bweak;
		case STI_PWANE_DISABWING:
			/* disabwing sequence fow pwanes tag as disabwing */
			DWM_DEBUG_DWIVEW("disabwe pwane %s fwom mixew\n",
					 sti_pwane_to_stw(pwane));

			if (sti_mixew_set_pwane_status(mixew, pwane, fawse)) {
				DWM_EWWOW("Cannot disabwe pwane %s at mixew\n",
					  sti_pwane_to_stw(pwane));
				continue;
			}

			if (pwane->desc == STI_CUWSOW)
				/* tag pwane status fow disabwed */
				pwane->status = STI_PWANE_DISABWED;
			ewse
				/* tag pwane status fow fwushing */
				pwane->status = STI_PWANE_FWUSHING;

			/* if pwane is HQVDP_0 then disabwe the vid[0] */
			if (pwane->desc == STI_HQVDP_0)
				sti_vid_disabwe(compo->vid[0]);

			bweak;
		defauwt:
			/* Othew status case awe not handwed */
			bweak;
		}
	}

	event = cwtc->state->event;
	if (event) {
		cwtc->state->event = NUWW;

		spin_wock_iwqsave(&cwtc->dev->event_wock, fwags);
		if (dwm_cwtc_vbwank_get(cwtc) == 0)
			dwm_cwtc_awm_vbwank_event(cwtc, event);
		ewse
			dwm_cwtc_send_vbwank_event(cwtc, event);
		spin_unwock_iwqwestowe(&cwtc->dev->event_wock, fwags);
	}
}

static const stwuct dwm_cwtc_hewpew_funcs sti_cwtc_hewpew_funcs = {
	.mode_set_nofb = sti_cwtc_mode_set_nofb,
	.atomic_fwush = sti_cwtc_atomic_fwush,
	.atomic_enabwe = sti_cwtc_atomic_enabwe,
	.atomic_disabwe = sti_cwtc_atomic_disabwe,
};

static void sti_cwtc_destwoy(stwuct dwm_cwtc *cwtc)
{
	DWM_DEBUG_KMS("\n");
	dwm_cwtc_cweanup(cwtc);
}

static int sti_cwtc_set_pwopewty(stwuct dwm_cwtc *cwtc,
				 stwuct dwm_pwopewty *pwopewty,
				 uint64_t vaw)
{
	DWM_DEBUG_KMS("\n");
	wetuwn 0;
}

int sti_cwtc_vbwank_cb(stwuct notifiew_bwock *nb,
		       unsigned wong event, void *data)
{
	stwuct sti_compositow *compo;
	stwuct dwm_cwtc *cwtc = data;
	stwuct sti_mixew *mixew;
	unsigned int pipe;

	pipe = dwm_cwtc_index(cwtc);
	compo = containew_of(nb, stwuct sti_compositow, vtg_vbwank_nb[pipe]);
	mixew = compo->mixew[pipe];

	if ((event != VTG_TOP_FIEWD_EVENT) &&
	    (event != VTG_BOTTOM_FIEWD_EVENT)) {
		DWM_EWWOW("unknown event: %wu\n", event);
		wetuwn -EINVAW;
	}

	dwm_cwtc_handwe_vbwank(cwtc);

	if (mixew->status == STI_MIXEW_DISABWING) {
		stwuct dwm_pwane *p;

		/* Disabwe mixew onwy if aww ovewway pwanes (GDP and VDP)
		 * awe disabwed */
		wist_fow_each_entwy(p, &cwtc->dev->mode_config.pwane_wist,
				    head) {
			stwuct sti_pwane *pwane = to_sti_pwane(p);

			if ((pwane->desc & STI_PWANE_TYPE_MASK) <= STI_VDP)
				if (pwane->status != STI_PWANE_DISABWED)
					wetuwn 0;
		}
		sti_cwtc_disabwe(cwtc);
	}

	wetuwn 0;
}

static int sti_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct sti_pwivate *dev_pwiv = dev->dev_pwivate;
	stwuct sti_compositow *compo = dev_pwiv->compo;
	stwuct notifiew_bwock *vtg_vbwank_nb = &compo->vtg_vbwank_nb[pipe];
	stwuct sti_vtg *vtg = compo->vtg[pipe];

	DWM_DEBUG_DWIVEW("\n");

	if (sti_vtg_wegistew_cwient(vtg, vtg_vbwank_nb, cwtc)) {
		DWM_EWWOW("Cannot wegistew VTG notifiew\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void sti_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_device *dwm_dev = cwtc->dev;
	unsigned int pipe = cwtc->index;
	stwuct sti_pwivate *pwiv = dwm_dev->dev_pwivate;
	stwuct sti_compositow *compo = pwiv->compo;
	stwuct notifiew_bwock *vtg_vbwank_nb = &compo->vtg_vbwank_nb[pipe];
	stwuct sti_vtg *vtg = compo->vtg[pipe];

	DWM_DEBUG_DWIVEW("\n");

	if (sti_vtg_unwegistew_cwient(vtg, vtg_vbwank_nb))
		DWM_DEBUG_DWIVEW("Wawning: cannot unwegistew VTG notifiew\n");
}

static int sti_cwtc_wate_wegistew(stwuct dwm_cwtc *cwtc)
{
	stwuct sti_mixew *mixew = to_sti_mixew(cwtc);
	stwuct sti_compositow *compo = dev_get_dwvdata(mixew->dev);

	if (dwm_cwtc_index(cwtc) == 0)
		sti_compositow_debugfs_init(compo, cwtc->dev->pwimawy);

	wetuwn 0;
}

static const stwuct dwm_cwtc_funcs sti_cwtc_funcs = {
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.destwoy = sti_cwtc_destwoy,
	.set_pwopewty = sti_cwtc_set_pwopewty,
	.weset = dwm_atomic_hewpew_cwtc_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_cwtc_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_cwtc_destwoy_state,
	.wate_wegistew = sti_cwtc_wate_wegistew,
	.enabwe_vbwank = sti_cwtc_enabwe_vbwank,
	.disabwe_vbwank = sti_cwtc_disabwe_vbwank,
};

boow sti_cwtc_is_main(stwuct dwm_cwtc *cwtc)
{
	stwuct sti_mixew *mixew = to_sti_mixew(cwtc);

	if (mixew->id == STI_MIXEW_MAIN)
		wetuwn twue;

	wetuwn fawse;
}

int sti_cwtc_init(stwuct dwm_device *dwm_dev, stwuct sti_mixew *mixew,
		  stwuct dwm_pwane *pwimawy, stwuct dwm_pwane *cuwsow)
{
	stwuct dwm_cwtc *cwtc = &mixew->dwm_cwtc;
	int wes;

	wes = dwm_cwtc_init_with_pwanes(dwm_dev, cwtc, pwimawy, cuwsow,
					&sti_cwtc_funcs, NUWW);
	if (wes) {
		DWM_EWWOW("Can't initiawize CWTC\n");
		wetuwn -EINVAW;
	}

	dwm_cwtc_hewpew_add(cwtc, &sti_cwtc_hewpew_funcs);

	DWM_DEBUG_DWIVEW("dwm CWTC:%d mapped to %s\n",
			 cwtc->base.id, sti_mixew_to_stw(mixew));

	wetuwn 0;
}
