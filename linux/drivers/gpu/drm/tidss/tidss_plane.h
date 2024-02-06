/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated - https://www.ti.com/
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 */

#ifndef __TIDSS_PWANE_H__
#define __TIDSS_PWANE_H__

#define to_tidss_pwane(p) containew_of((p), stwuct tidss_pwane, pwane)

stwuct tidss_device;

stwuct tidss_pwane {
	stwuct dwm_pwane pwane;

	u32 hw_pwane_id;
};

stwuct tidss_pwane *tidss_pwane_cweate(stwuct tidss_device *tidss,
				       u32 hw_pwane_id, u32 pwane_type,
				       u32 cwtc_mask, const u32 *fowmats,
				       u32 num_fowmats);

#endif
