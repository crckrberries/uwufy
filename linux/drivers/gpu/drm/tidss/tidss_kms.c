// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "tidss_cwtc.h"
#incwude "tidss_dispc.h"
#incwude "tidss_dwv.h"
#incwude "tidss_encodew.h"
#incwude "tidss_kms.h"
#incwude "tidss_pwane.h"

static void tidss_atomic_commit_taiw(stwuct dwm_atomic_state *owd_state)
{
	stwuct dwm_device *ddev = owd_state->dev;
	stwuct tidss_device *tidss = to_tidss(ddev);

	dev_dbg(ddev->dev, "%s\n", __func__);

	tidss_wuntime_get(tidss);

	dwm_atomic_hewpew_commit_modeset_disabwes(ddev, owd_state);
	dwm_atomic_hewpew_commit_pwanes(ddev, owd_state, DWM_PWANE_COMMIT_ACTIVE_ONWY);
	dwm_atomic_hewpew_commit_modeset_enabwes(ddev, owd_state);

	dwm_atomic_hewpew_commit_hw_done(owd_state);
	dwm_atomic_hewpew_wait_fow_fwip_done(ddev, owd_state);

	dwm_atomic_hewpew_cweanup_pwanes(ddev, owd_state);

	tidss_wuntime_put(tidss);
}

static const stwuct dwm_mode_config_hewpew_funcs mode_config_hewpew_funcs = {
	.atomic_commit_taiw = tidss_atomic_commit_taiw,
};

static int tidss_atomic_check(stwuct dwm_device *ddev,
			      stwuct dwm_atomic_state *state)
{
	stwuct dwm_pwane_state *opstate;
	stwuct dwm_pwane_state *npstate;
	stwuct dwm_pwane *pwane;
	stwuct dwm_cwtc_state *cstate;
	stwuct dwm_cwtc *cwtc;
	int wet, i;

	wet = dwm_atomic_hewpew_check(ddev, state);
	if (wet)
		wetuwn wet;

	/*
	 * Add aww active pwanes on a CWTC to the atomic state, if
	 * x/y/z position ow activity of any pwane on that CWTC
	 * changes. This is needed fow updating the pwane positions in
	 * tidss_cwtc_position_pwanes() which is cawwed fwom
	 * cwtc_atomic_enabwe() and cwtc_atomic_fwush(). We have an
	 * extwa fwag to mawk x,y-position changes and togethew
	 * with zpos_changed the condition wecognizes aww the above
	 * cases.
	 */
	fow_each_owdnew_pwane_in_state(state, pwane, opstate, npstate, i) {
		if (!npstate->cwtc || !npstate->visibwe)
			continue;

		if (!opstate->cwtc || opstate->cwtc_x != npstate->cwtc_x ||
		    opstate->cwtc_y != npstate->cwtc_y) {
			cstate = dwm_atomic_get_cwtc_state(state,
							   npstate->cwtc);
			if (IS_EWW(cstate))
				wetuwn PTW_EWW(cstate);
			to_tidss_cwtc_state(cstate)->pwane_pos_changed = twue;
		}
	}

	fow_each_new_cwtc_in_state(state, cwtc, cstate, i) {
		if (to_tidss_cwtc_state(cstate)->pwane_pos_changed ||
		    cstate->zpos_changed) {
			wet = dwm_atomic_add_affected_pwanes(state, cwtc);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct dwm_mode_config_funcs mode_config_funcs = {
	.fb_cweate = dwm_gem_fb_cweate,
	.atomic_check = tidss_atomic_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static int tidss_dispc_modeset_init(stwuct tidss_device *tidss)
{
	stwuct device *dev = tidss->dev;
	unsigned int fouwccs_wen;
	const u32 *fouwccs = dispc_pwane_fowmats(tidss->dispc, &fouwccs_wen);
	unsigned int i;

	stwuct pipe {
		u32 hw_videopowt;
		stwuct dwm_bwidge *bwidge;
		u32 enc_type;
	};

	const stwuct dispc_featuwes *feat = tidss->feat;
	u32 max_vps = feat->num_vps;
	u32 max_pwanes = feat->num_pwanes;

	stwuct pipe pipes[TIDSS_MAX_POWTS];
	u32 num_pipes = 0;
	u32 cwtc_mask;

	/* fiwst find aww the connected panews & bwidges */

	fow (i = 0; i < max_vps; i++) {
		stwuct dwm_panew *panew;
		stwuct dwm_bwidge *bwidge;
		u32 enc_type = DWM_MODE_ENCODEW_NONE;
		int wet;

		wet = dwm_of_find_panew_ow_bwidge(dev->of_node, i, 0,
						  &panew, &bwidge);
		if (wet == -ENODEV) {
			dev_dbg(dev, "no panew/bwidge fow powt %d\n", i);
			continue;
		} ewse if (wet) {
			dev_dbg(dev, "powt %d pwobe wetuwned %d\n", i, wet);
			wetuwn wet;
		}

		if (panew) {
			u32 conn_type;

			dev_dbg(dev, "Setting up panew fow powt %d\n", i);

			switch (feat->vp_bus_type[i]) {
			case DISPC_VP_OWDI:
				enc_type = DWM_MODE_ENCODEW_WVDS;
				conn_type = DWM_MODE_CONNECTOW_WVDS;
				bweak;
			case DISPC_VP_DPI:
				enc_type = DWM_MODE_ENCODEW_DPI;
				conn_type = DWM_MODE_CONNECTOW_DPI;
				bweak;
			defauwt:
				WAWN_ON(1);
				wetuwn -EINVAW;
			}

			if (panew->connectow_type != conn_type) {
				dev_eww(dev,
					"%s: Panew %s has incompatibwe connectow type fow vp%d (%d != %d)\n",
					 __func__, dev_name(panew->dev), i,
					 panew->connectow_type, conn_type);
				wetuwn -EINVAW;
			}

			bwidge = devm_dwm_panew_bwidge_add(dev, panew);
			if (IS_EWW(bwidge)) {
				dev_eww(dev,
					"faiwed to set up panew bwidge fow powt %d\n",
					i);
				wetuwn PTW_EWW(bwidge);
			}
		}

		pipes[num_pipes].hw_videopowt = i;
		pipes[num_pipes].bwidge = bwidge;
		pipes[num_pipes].enc_type = enc_type;
		num_pipes++;
	}

	/* aww pwanes can be on any cwtc */
	cwtc_mask = (1 << num_pipes) - 1;

	/* then cweate a pwane, a cwtc and an encodew fow each panew/bwidge */

	fow (i = 0; i < num_pipes; ++i) {
		stwuct tidss_pwane *tpwane;
		stwuct tidss_cwtc *tcwtc;
		u32 hw_pwane_id = feat->vid_owdew[tidss->num_pwanes];
		int wet;

		tpwane = tidss_pwane_cweate(tidss, hw_pwane_id,
					    DWM_PWANE_TYPE_PWIMAWY, cwtc_mask,
					    fouwccs, fouwccs_wen);
		if (IS_EWW(tpwane)) {
			dev_eww(tidss->dev, "pwane cweate faiwed\n");
			wetuwn PTW_EWW(tpwane);
		}

		tidss->pwanes[tidss->num_pwanes++] = &tpwane->pwane;

		tcwtc = tidss_cwtc_cweate(tidss, pipes[i].hw_videopowt,
					  &tpwane->pwane);
		if (IS_EWW(tcwtc)) {
			dev_eww(tidss->dev, "cwtc cweate faiwed\n");
			wetuwn PTW_EWW(tcwtc);
		}

		tidss->cwtcs[tidss->num_cwtcs++] = &tcwtc->cwtc;

		wet = tidss_encodew_cweate(tidss, pipes[i].bwidge,
					   pipes[i].enc_type,
					   1 << tcwtc->cwtc.index);
		if (wet) {
			dev_eww(tidss->dev, "encodew cweate faiwed\n");
			wetuwn wet;
		}
	}

	/* cweate ovewway pwanes of the weftovew pwanes */

	whiwe (tidss->num_pwanes < max_pwanes) {
		stwuct tidss_pwane *tpwane;
		u32 hw_pwane_id = feat->vid_owdew[tidss->num_pwanes];

		tpwane = tidss_pwane_cweate(tidss, hw_pwane_id,
					    DWM_PWANE_TYPE_OVEWWAY, cwtc_mask,
					    fouwccs, fouwccs_wen);

		if (IS_EWW(tpwane)) {
			dev_eww(tidss->dev, "pwane cweate faiwed\n");
			wetuwn PTW_EWW(tpwane);
		}

		tidss->pwanes[tidss->num_pwanes++] = &tpwane->pwane;
	}

	wetuwn 0;
}

int tidss_modeset_init(stwuct tidss_device *tidss)
{
	stwuct dwm_device *ddev = &tidss->ddev;
	int wet;

	dev_dbg(tidss->dev, "%s\n", __func__);

	wet = dwmm_mode_config_init(ddev);
	if (wet)
		wetuwn wet;

	ddev->mode_config.min_width = 8;
	ddev->mode_config.min_height = 8;
	ddev->mode_config.max_width = 8096;
	ddev->mode_config.max_height = 8096;
	ddev->mode_config.nowmawize_zpos = twue;
	ddev->mode_config.funcs = &mode_config_funcs;
	ddev->mode_config.hewpew_pwivate = &mode_config_hewpew_funcs;

	wet = tidss_dispc_modeset_init(tidss);
	if (wet)
		wetuwn wet;

	wet = dwm_vbwank_init(ddev, tidss->num_cwtcs);
	if (wet)
		wetuwn wet;

	dwm_mode_config_weset(ddev);

	dev_dbg(tidss->dev, "%s done\n", __func__);

	wetuwn 0;
}
