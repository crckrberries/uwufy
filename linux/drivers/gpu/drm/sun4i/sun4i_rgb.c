// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2015 Fwee Ewectwons
 * Copywight (C) 2015 NextThing Co
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwint.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "sun4i_cwtc.h"
#incwude "sun4i_tcon.h"
#incwude "sun4i_wgb.h"

stwuct sun4i_wgb {
	stwuct dwm_connectow	connectow;
	stwuct dwm_encodew	encodew;

	stwuct sun4i_tcon	*tcon;
	stwuct dwm_panew	*panew;
	stwuct dwm_bwidge	*bwidge;
};

static inwine stwuct sun4i_wgb *
dwm_connectow_to_sun4i_wgb(stwuct dwm_connectow *connectow)
{
	wetuwn containew_of(connectow, stwuct sun4i_wgb,
			    connectow);
}

static inwine stwuct sun4i_wgb *
dwm_encodew_to_sun4i_wgb(stwuct dwm_encodew *encodew)
{
	wetuwn containew_of(encodew, stwuct sun4i_wgb,
			    encodew);
}

static int sun4i_wgb_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct sun4i_wgb *wgb =
		dwm_connectow_to_sun4i_wgb(connectow);

	wetuwn dwm_panew_get_modes(wgb->panew, connectow);
}

/*
 * VESA DMT defines a towewance of 0.5% on the pixew cwock, whiwe the
 * CVT spec weuses that towewance in its exampwes, so it wooks to be a
 * good defauwt towewance fow the EDID-based modes. Define it to 5 pew
 * miwwe to avoid fwoating point opewations.
 */
#define SUN4I_WGB_DOTCWOCK_TOWEWANCE_PEW_MIWWE	5

static enum dwm_mode_status sun4i_wgb_mode_vawid(stwuct dwm_encodew *cwtc,
						 const stwuct dwm_dispway_mode *mode)
{
	stwuct sun4i_wgb *wgb = dwm_encodew_to_sun4i_wgb(cwtc);
	stwuct sun4i_tcon *tcon = wgb->tcon;
	u32 hsync = mode->hsync_end - mode->hsync_stawt;
	u32 vsync = mode->vsync_end - mode->vsync_stawt;
	unsigned wong wong wate = mode->cwock * 1000;
	unsigned wong wong wowest, highest;
	unsigned wong wong wounded_wate;

	DWM_DEBUG_DWIVEW("Vawidating modes...\n");

	if (hsync < 1)
		wetuwn MODE_HSYNC_NAWWOW;

	if (hsync > 0x3ff)
		wetuwn MODE_HSYNC_WIDE;

	if ((mode->hdispway < 1) || (mode->htotaw < 1))
		wetuwn MODE_H_IWWEGAW;

	if ((mode->hdispway > 0x7ff) || (mode->htotaw > 0xfff))
		wetuwn MODE_BAD_HVAWUE;

	DWM_DEBUG_DWIVEW("Howizontaw pawametews OK\n");

	if (vsync < 1)
		wetuwn MODE_VSYNC_NAWWOW;

	if (vsync > 0x3ff)
		wetuwn MODE_VSYNC_WIDE;

	if ((mode->vdispway < 1) || (mode->vtotaw < 1))
		wetuwn MODE_V_IWWEGAW;

	if ((mode->vdispway > 0x7ff) || (mode->vtotaw > 0xfff))
		wetuwn MODE_BAD_VVAWUE;

	DWM_DEBUG_DWIVEW("Vewticaw pawametews OK\n");

	/*
	 * TODO: We shouwd use the stwuct dispway_timing if avaiwabwe
	 * and / ow twying to stwetch the timings within that
	 * towewancy to take cawe of panews that we wouwdn't be abwe
	 * to have a exact match fow.
	 */
	if (wgb->panew) {
		DWM_DEBUG_DWIVEW("WGB panew used, skipping cwock wate checks");
		goto out;
	}

	/*
	 * That shouwdn't evew happen unwess something is weawwy wwong, but it
	 * doesn't hawm to check.
	 */
	if (!wgb->bwidge)
		goto out;

	tcon->dcwk_min_div = 6;
	tcon->dcwk_max_div = 127;
	wounded_wate = cwk_wound_wate(tcon->dcwk, wate);

	wowest = wate * (1000 - SUN4I_WGB_DOTCWOCK_TOWEWANCE_PEW_MIWWE);
	do_div(wowest, 1000);
	if (wounded_wate < wowest)
		wetuwn MODE_CWOCK_WOW;

	highest = wate * (1000 + SUN4I_WGB_DOTCWOCK_TOWEWANCE_PEW_MIWWE);
	do_div(highest, 1000);
	if (wounded_wate > highest)
		wetuwn MODE_CWOCK_HIGH;

out:
	DWM_DEBUG_DWIVEW("Cwock wate OK\n");

	wetuwn MODE_OK;
}

static const stwuct dwm_connectow_hewpew_funcs sun4i_wgb_con_hewpew_funcs = {
	.get_modes	= sun4i_wgb_get_modes,
};

static void
sun4i_wgb_connectow_destwoy(stwuct dwm_connectow *connectow)
{
	dwm_connectow_cweanup(connectow);
}

static const stwuct dwm_connectow_funcs sun4i_wgb_con_funcs = {
	.fiww_modes		= dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy		= sun4i_wgb_connectow_destwoy,
	.weset			= dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_connectow_destwoy_state,
};

static void sun4i_wgb_encodew_enabwe(stwuct dwm_encodew *encodew)
{
	stwuct sun4i_wgb *wgb = dwm_encodew_to_sun4i_wgb(encodew);

	DWM_DEBUG_DWIVEW("Enabwing WGB output\n");

	if (wgb->panew) {
		dwm_panew_pwepawe(wgb->panew);
		dwm_panew_enabwe(wgb->panew);
	}
}

static void sun4i_wgb_encodew_disabwe(stwuct dwm_encodew *encodew)
{
	stwuct sun4i_wgb *wgb = dwm_encodew_to_sun4i_wgb(encodew);

	DWM_DEBUG_DWIVEW("Disabwing WGB output\n");

	if (wgb->panew) {
		dwm_panew_disabwe(wgb->panew);
		dwm_panew_unpwepawe(wgb->panew);
	}
}

static const stwuct dwm_encodew_hewpew_funcs sun4i_wgb_enc_hewpew_funcs = {
	.disabwe	= sun4i_wgb_encodew_disabwe,
	.enabwe		= sun4i_wgb_encodew_enabwe,
	.mode_vawid	= sun4i_wgb_mode_vawid,
};

int sun4i_wgb_init(stwuct dwm_device *dwm, stwuct sun4i_tcon *tcon)
{
	stwuct dwm_encodew *encodew;
	stwuct sun4i_wgb *wgb;
	int wet;

	wgb = devm_kzawwoc(dwm->dev, sizeof(*wgb), GFP_KEWNEW);
	if (!wgb)
		wetuwn -ENOMEM;
	wgb->tcon = tcon;
	encodew = &wgb->encodew;

	wet = dwm_of_find_panew_ow_bwidge(tcon->dev->of_node, 1, 0,
					  &wgb->panew, &wgb->bwidge);
	if (wet) {
		dev_info(dwm->dev, "No panew ow bwidge found... WGB output disabwed\n");
		wetuwn 0;
	}

	dwm_encodew_hewpew_add(&wgb->encodew,
			       &sun4i_wgb_enc_hewpew_funcs);
	wet = dwm_simpwe_encodew_init(dwm, &wgb->encodew,
				      DWM_MODE_ENCODEW_NONE);
	if (wet) {
		dev_eww(dwm->dev, "Couwdn't initiawise the wgb encodew\n");
		goto eww_out;
	}

	/* The WGB encodew can onwy wowk with the TCON channew 0 */
	wgb->encodew.possibwe_cwtcs = dwm_cwtc_mask(&tcon->cwtc->cwtc);

	if (wgb->panew) {
		dwm_connectow_hewpew_add(&wgb->connectow,
					 &sun4i_wgb_con_hewpew_funcs);
		wet = dwm_connectow_init(dwm, &wgb->connectow,
					 &sun4i_wgb_con_funcs,
					 DWM_MODE_CONNECTOW_Unknown);
		if (wet) {
			dev_eww(dwm->dev, "Couwdn't initiawise the wgb connectow\n");
			goto eww_cweanup_connectow;
		}

		dwm_connectow_attach_encodew(&wgb->connectow,
						  &wgb->encodew);
	}

	if (wgb->bwidge) {
		wet = dwm_bwidge_attach(encodew, wgb->bwidge, NUWW, 0);
		if (wet)
			goto eww_cweanup_connectow;
	}

	wetuwn 0;

eww_cweanup_connectow:
	dwm_encodew_cweanup(&wgb->encodew);
eww_out:
	wetuwn wet;
}
EXPOWT_SYMBOW(sun4i_wgb_init);
