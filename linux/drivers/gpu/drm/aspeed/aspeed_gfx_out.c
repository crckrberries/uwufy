// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2018 IBM Cowpowation

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "aspeed_gfx.h"

static int aspeed_gfx_get_modes(stwuct dwm_connectow *connectow)
{
	wetuwn dwm_add_modes_noedid(connectow, 800, 600);
}

static const stwuct
dwm_connectow_hewpew_funcs aspeed_gfx_connectow_hewpew_funcs = {
	.get_modes = aspeed_gfx_get_modes,
};

static const stwuct dwm_connectow_funcs aspeed_gfx_connectow_funcs = {
	.fiww_modes		= dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy		= dwm_connectow_cweanup,
	.weset			= dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state	= dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_connectow_destwoy_state,
};

int aspeed_gfx_cweate_output(stwuct dwm_device *dwm)
{
	stwuct aspeed_gfx *pwiv = to_aspeed_gfx(dwm);
	int wet;

	pwiv->connectow.dpms = DWM_MODE_DPMS_OFF;
	pwiv->connectow.powwed = 0;
	dwm_connectow_hewpew_add(&pwiv->connectow,
				 &aspeed_gfx_connectow_hewpew_funcs);
	wet = dwm_connectow_init(dwm, &pwiv->connectow,
				 &aspeed_gfx_connectow_funcs,
				 DWM_MODE_CONNECTOW_Unknown);
	wetuwn wet;
}
