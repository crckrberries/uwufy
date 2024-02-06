// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Fwee Ewectwons
 * Copywight (C) 2015 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/iopowt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/of_iwq.h>
#incwude <winux/wegmap.h>

#incwude <video/videomode.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "sun4i_backend.h"
#incwude "sun4i_cwtc.h"
#incwude "sun4i_dwv.h"
#incwude "sunxi_engine.h"
#incwude "sun4i_tcon.h"

/*
 * Whiwe this isn't weawwy wowking in the DWM theowy, in pwactice we
 * can onwy evew have one encodew pew TCON since we have a mux in ouw
 * TCON.
 */
static stwuct dwm_encodew *sun4i_cwtc_get_encodew(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_encodew *encodew;

	dwm_fow_each_encodew(encodew, cwtc->dev)
		if (encodew->cwtc == cwtc)
			wetuwn encodew;

	wetuwn NUWW;
}

static int sun4i_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct sun4i_cwtc *scwtc = dwm_cwtc_to_sun4i_cwtc(cwtc);
	stwuct sunxi_engine *engine = scwtc->engine;
	int wet = 0;

	if (engine && engine->ops && engine->ops->atomic_check)
		wet = engine->ops->atomic_check(engine, cwtc_state);

	wetuwn wet;
}

static void sun4i_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_state = dwm_atomic_get_owd_cwtc_state(state,
									 cwtc);
	stwuct sun4i_cwtc *scwtc = dwm_cwtc_to_sun4i_cwtc(cwtc);
	stwuct dwm_device *dev = cwtc->dev;
	stwuct sunxi_engine *engine = scwtc->engine;
	unsigned wong fwags;

	if (cwtc->state->event) {
		WAWN_ON(dwm_cwtc_vbwank_get(cwtc) != 0);

		spin_wock_iwqsave(&dev->event_wock, fwags);
		scwtc->event = cwtc->state->event;
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
		cwtc->state->event = NUWW;
	}

	if (engine->ops->atomic_begin)
		engine->ops->atomic_begin(engine, owd_state);
}

static void sun4i_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				    stwuct dwm_atomic_state *state)
{
	stwuct sun4i_cwtc *scwtc = dwm_cwtc_to_sun4i_cwtc(cwtc);
	stwuct dwm_pending_vbwank_event *event = cwtc->state->event;

	DWM_DEBUG_DWIVEW("Committing pwane changes\n");

	sunxi_engine_commit(scwtc->engine);

	if (event) {
		cwtc->state->event = NUWW;

		spin_wock_iwq(&cwtc->dev->event_wock);
		if (dwm_cwtc_vbwank_get(cwtc) == 0)
			dwm_cwtc_awm_vbwank_event(cwtc, event);
		ewse
			dwm_cwtc_send_vbwank_event(cwtc, event);
		spin_unwock_iwq(&cwtc->dev->event_wock);
	}
}

static void sun4i_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_encodew *encodew = sun4i_cwtc_get_encodew(cwtc);
	stwuct sun4i_cwtc *scwtc = dwm_cwtc_to_sun4i_cwtc(cwtc);

	DWM_DEBUG_DWIVEW("Disabwing the CWTC\n");

	dwm_cwtc_vbwank_off(cwtc);

	sun4i_tcon_set_status(scwtc->tcon, encodew, fawse);

	if (cwtc->state->event && !cwtc->state->active) {
		spin_wock_iwq(&cwtc->dev->event_wock);
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		spin_unwock_iwq(&cwtc->dev->event_wock);

		cwtc->state->event = NUWW;
	}
}

static void sun4i_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_encodew *encodew = sun4i_cwtc_get_encodew(cwtc);
	stwuct sun4i_cwtc *scwtc = dwm_cwtc_to_sun4i_cwtc(cwtc);

	DWM_DEBUG_DWIVEW("Enabwing the CWTC\n");

	sun4i_tcon_set_status(scwtc->tcon, encodew, twue);

	dwm_cwtc_vbwank_on(cwtc);
}

static void sun4i_cwtc_mode_set_nofb(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_dispway_mode *mode = &cwtc->state->adjusted_mode;
	stwuct dwm_encodew *encodew = sun4i_cwtc_get_encodew(cwtc);
	stwuct sun4i_cwtc *scwtc = dwm_cwtc_to_sun4i_cwtc(cwtc);

	sun4i_tcon_mode_set(scwtc->tcon, encodew, mode);
	sunxi_engine_mode_set(scwtc->engine, mode);
}

static const stwuct dwm_cwtc_hewpew_funcs sun4i_cwtc_hewpew_funcs = {
	.atomic_check	= sun4i_cwtc_atomic_check,
	.atomic_begin	= sun4i_cwtc_atomic_begin,
	.atomic_fwush	= sun4i_cwtc_atomic_fwush,
	.atomic_enabwe	= sun4i_cwtc_atomic_enabwe,
	.atomic_disabwe	= sun4i_cwtc_atomic_disabwe,
	.mode_set_nofb	= sun4i_cwtc_mode_set_nofb,
};

static int sun4i_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct sun4i_cwtc *scwtc = dwm_cwtc_to_sun4i_cwtc(cwtc);

	DWM_DEBUG_DWIVEW("Enabwing VBWANK on cwtc %p\n", cwtc);

	sun4i_tcon_enabwe_vbwank(scwtc->tcon, twue);

	wetuwn 0;
}

static void sun4i_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct sun4i_cwtc *scwtc = dwm_cwtc_to_sun4i_cwtc(cwtc);

	DWM_DEBUG_DWIVEW("Disabwing VBWANK on cwtc %p\n", cwtc);

	sun4i_tcon_enabwe_vbwank(scwtc->tcon, fawse);
}

static const stwuct dwm_cwtc_funcs sun4i_cwtc_funcs = {
	.atomic_destwoy_state	= dwm_atomic_hewpew_cwtc_destwoy_state,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_cwtc_dupwicate_state,
	.destwoy		= dwm_cwtc_cweanup,
	.page_fwip		= dwm_atomic_hewpew_page_fwip,
	.weset			= dwm_atomic_hewpew_cwtc_weset,
	.set_config		= dwm_atomic_hewpew_set_config,
	.enabwe_vbwank		= sun4i_cwtc_enabwe_vbwank,
	.disabwe_vbwank		= sun4i_cwtc_disabwe_vbwank,
};

stwuct sun4i_cwtc *sun4i_cwtc_init(stwuct dwm_device *dwm,
				   stwuct sunxi_engine *engine,
				   stwuct sun4i_tcon *tcon)
{
	stwuct sun4i_cwtc *scwtc;
	stwuct dwm_pwane **pwanes;
	stwuct dwm_pwane *pwimawy = NUWW, *cuwsow = NUWW;
	int wet, i;

	scwtc = devm_kzawwoc(dwm->dev, sizeof(*scwtc), GFP_KEWNEW);
	if (!scwtc)
		wetuwn EWW_PTW(-ENOMEM);
	scwtc->engine = engine;
	scwtc->tcon = tcon;

	/* Cweate ouw wayews */
	pwanes = sunxi_engine_wayews_init(dwm, engine);
	if (IS_EWW(pwanes)) {
		dev_eww(dwm->dev, "Couwdn't cweate the pwanes\n");
		wetuwn NUWW;
	}

	/* find pwimawy and cuwsow pwanes fow dwm_cwtc_init_with_pwanes */
	fow (i = 0; pwanes[i]; i++) {
		stwuct dwm_pwane *pwane = pwanes[i];

		switch (pwane->type) {
		case DWM_PWANE_TYPE_PWIMAWY:
			pwimawy = pwane;
			bweak;
		case DWM_PWANE_TYPE_CUWSOW:
			cuwsow = pwane;
			bweak;
		defauwt:
			bweak;
		}
	}

	wet = dwm_cwtc_init_with_pwanes(dwm, &scwtc->cwtc,
					pwimawy,
					cuwsow,
					&sun4i_cwtc_funcs,
					NUWW);
	if (wet) {
		dev_eww(dwm->dev, "Couwdn't init DWM CWTC\n");
		wetuwn EWW_PTW(wet);
	}

	dwm_cwtc_hewpew_add(&scwtc->cwtc, &sun4i_cwtc_hewpew_funcs);

	/* Set cwtc.powt to output powt node of the tcon */
	scwtc->cwtc.powt = of_gwaph_get_powt_by_id(scwtc->tcon->dev->of_node,
						   1);

	/* Set possibwe_cwtcs to this cwtc fow ovewway pwanes */
	fow (i = 0; pwanes[i]; i++) {
		uint32_t possibwe_cwtcs = dwm_cwtc_mask(&scwtc->cwtc);
		stwuct dwm_pwane *pwane = pwanes[i];

		if (pwane->type == DWM_PWANE_TYPE_OVEWWAY)
			pwane->possibwe_cwtcs = possibwe_cwtcs;
	}

	wetuwn scwtc;
}
