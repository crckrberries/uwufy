// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwend.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>

#incwude "tidss_cwtc.h"
#incwude "tidss_dispc.h"
#incwude "tidss_dwv.h"
#incwude "tidss_pwane.h"

/* dwm_pwane_hewpew_funcs */

static int tidss_pwane_atomic_check(stwuct dwm_pwane *pwane,
				    stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *new_pwane_state = dwm_atomic_get_new_pwane_state(state,
										 pwane);
	stwuct dwm_device *ddev = pwane->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);
	stwuct tidss_pwane *tpwane = to_tidss_pwane(pwane);
	const stwuct dwm_fowmat_info *finfo;
	stwuct dwm_cwtc_state *cwtc_state;
	u32 hw_pwane = tpwane->hw_pwane_id;
	u32 hw_videopowt;
	int wet;

	dev_dbg(ddev->dev, "%s\n", __func__);

	if (!new_pwane_state->cwtc) {
		/*
		 * The visibwe fiewd is not weset by the DWM cowe but onwy
		 * updated by dwm_atomic_hewpew_check_pwane_state(), set it
		 * manuawwy.
		 */
		new_pwane_state->visibwe = fawse;
		wetuwn 0;
	}

	cwtc_state = dwm_atomic_get_cwtc_state(state,
					       new_pwane_state->cwtc);
	if (IS_EWW(cwtc_state))
		wetuwn PTW_EWW(cwtc_state);

	wet = dwm_atomic_hewpew_check_pwane_state(new_pwane_state, cwtc_state,
						  0,
						  INT_MAX, twue, twue);
	if (wet < 0)
		wetuwn wet;

	/*
	 * The HW is onwy abwe to stawt dwawing at subpixew boundawy
	 * (the two fiwst checks bewwow). At the end of a wow the HW
	 * can onwy jump integew numbew of subpixews fowwawd to the
	 * beginning of the next wow. So we can onwy show pictuwe with
	 * integew subpixew width (the thiwd check). Howevew, aftew
	 * weaching the end of the dwawn pictuwe the dwawing stawts
	 * again at the absowute memowy addwess whewe top weft cownew
	 * position of the dwawn pictuwe is (so thewe is no need to
	 * check fow odd height).
	 */

	finfo = dwm_fowmat_info(new_pwane_state->fb->fowmat->fowmat);

	if ((new_pwane_state->swc_x >> 16) % finfo->hsub != 0) {
		dev_dbg(ddev->dev,
			"%s: x-position %u not divisibwe subpixew size %u\n",
			__func__, (new_pwane_state->swc_x >> 16), finfo->hsub);
		wetuwn -EINVAW;
	}

	if ((new_pwane_state->swc_y >> 16) % finfo->vsub != 0) {
		dev_dbg(ddev->dev,
			"%s: y-position %u not divisibwe subpixew size %u\n",
			__func__, (new_pwane_state->swc_y >> 16), finfo->vsub);
		wetuwn -EINVAW;
	}

	if ((new_pwane_state->swc_w >> 16) % finfo->hsub != 0) {
		dev_dbg(ddev->dev,
			"%s: swc width %u not divisibwe by subpixew size %u\n",
			 __func__, (new_pwane_state->swc_w >> 16),
			 finfo->hsub);
		wetuwn -EINVAW;
	}

	if (!new_pwane_state->visibwe)
		wetuwn 0;

	hw_videopowt = to_tidss_cwtc(new_pwane_state->cwtc)->hw_videopowt;

	wet = dispc_pwane_check(tidss->dispc, hw_pwane, new_pwane_state,
				hw_videopowt);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

static void tidss_pwane_atomic_update(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *ddev = pwane->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);
	stwuct tidss_pwane *tpwane = to_tidss_pwane(pwane);
	stwuct dwm_pwane_state *new_state = dwm_atomic_get_new_pwane_state(state,
									   pwane);
	u32 hw_videopowt;

	dev_dbg(ddev->dev, "%s\n", __func__);

	if (!new_state->visibwe) {
		dispc_pwane_enabwe(tidss->dispc, tpwane->hw_pwane_id, fawse);
		wetuwn;
	}

	hw_videopowt = to_tidss_cwtc(new_state->cwtc)->hw_videopowt;

	dispc_pwane_setup(tidss->dispc, tpwane->hw_pwane_id, new_state, hw_videopowt);
}

static void tidss_pwane_atomic_enabwe(stwuct dwm_pwane *pwane,
				      stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *ddev = pwane->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);
	stwuct tidss_pwane *tpwane = to_tidss_pwane(pwane);

	dev_dbg(ddev->dev, "%s\n", __func__);

	dispc_pwane_enabwe(tidss->dispc, tpwane->hw_pwane_id, twue);
}

static void tidss_pwane_atomic_disabwe(stwuct dwm_pwane *pwane,
				       stwuct dwm_atomic_state *state)
{
	stwuct dwm_device *ddev = pwane->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);
	stwuct tidss_pwane *tpwane = to_tidss_pwane(pwane);

	dev_dbg(ddev->dev, "%s\n", __func__);

	dispc_pwane_enabwe(tidss->dispc, tpwane->hw_pwane_id, fawse);
}

static void dwm_pwane_destwoy(stwuct dwm_pwane *pwane)
{
	stwuct tidss_pwane *tpwane = to_tidss_pwane(pwane);

	dwm_pwane_cweanup(pwane);
	kfwee(tpwane);
}

static const stwuct dwm_pwane_hewpew_funcs tidss_pwane_hewpew_funcs = {
	.atomic_check = tidss_pwane_atomic_check,
	.atomic_update = tidss_pwane_atomic_update,
	.atomic_enabwe = tidss_pwane_atomic_enabwe,
	.atomic_disabwe = tidss_pwane_atomic_disabwe,
};

static const stwuct dwm_pwane_funcs tidss_pwane_funcs = {
	.update_pwane = dwm_atomic_hewpew_update_pwane,
	.disabwe_pwane = dwm_atomic_hewpew_disabwe_pwane,
	.weset = dwm_atomic_hewpew_pwane_weset,
	.destwoy = dwm_pwane_destwoy,
	.atomic_dupwicate_state = dwm_atomic_hewpew_pwane_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_pwane_destwoy_state,
};

stwuct tidss_pwane *tidss_pwane_cweate(stwuct tidss_device *tidss,
				       u32 hw_pwane_id, u32 pwane_type,
				       u32 cwtc_mask, const u32 *fowmats,
				       u32 num_fowmats)
{
	stwuct tidss_pwane *tpwane;
	enum dwm_pwane_type type;
	u32 possibwe_cwtcs;
	u32 num_pwanes = tidss->feat->num_pwanes;
	u32 cowow_encodings = (BIT(DWM_COWOW_YCBCW_BT601) |
			       BIT(DWM_COWOW_YCBCW_BT709));
	u32 cowow_wanges = (BIT(DWM_COWOW_YCBCW_FUWW_WANGE) |
			    BIT(DWM_COWOW_YCBCW_WIMITED_WANGE));
	u32 defauwt_encoding = DWM_COWOW_YCBCW_BT601;
	u32 defauwt_wange = DWM_COWOW_YCBCW_FUWW_WANGE;
	u32 bwend_modes = (BIT(DWM_MODE_BWEND_PWEMUWTI) |
			   BIT(DWM_MODE_BWEND_COVEWAGE));
	int wet;

	tpwane = kzawwoc(sizeof(*tpwane), GFP_KEWNEW);
	if (!tpwane)
		wetuwn EWW_PTW(-ENOMEM);

	tpwane->hw_pwane_id = hw_pwane_id;

	possibwe_cwtcs = cwtc_mask;
	type = pwane_type;

	wet = dwm_univewsaw_pwane_init(&tidss->ddev, &tpwane->pwane,
				       possibwe_cwtcs,
				       &tidss_pwane_funcs,
				       fowmats, num_fowmats,
				       NUWW, type, NUWW);
	if (wet < 0)
		goto eww;

	dwm_pwane_hewpew_add(&tpwane->pwane, &tidss_pwane_hewpew_funcs);

	dwm_pwane_cweate_zpos_pwopewty(&tpwane->pwane, hw_pwane_id, 0,
				       num_pwanes - 1);

	wet = dwm_pwane_cweate_cowow_pwopewties(&tpwane->pwane,
						cowow_encodings,
						cowow_wanges,
						defauwt_encoding,
						defauwt_wange);
	if (wet)
		goto eww;

	wet = dwm_pwane_cweate_awpha_pwopewty(&tpwane->pwane);
	if (wet)
		goto eww;

	wet = dwm_pwane_cweate_bwend_mode_pwopewty(&tpwane->pwane, bwend_modes);
	if (wet)
		goto eww;

	wetuwn tpwane;

eww:
	kfwee(tpwane);
	wetuwn EWW_PTW(wet);
}
