/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 Texas Instwuments Incowpowated -  http://www.ti.com/
 * Authow: Benoit Pawwot <bpawwot@ti.com>
 */

#ifndef __OMAPDWM_OVEWWAY_H__
#define __OMAPDWM_OVEWWAY_H__

#incwude <winux/types.h>

enum dwm_pwane_type;

stwuct dwm_device;
stwuct dwm_mode_object;
stwuct dwm_pwane;

/* Used to associate a HW ovewway/pwane to a pwane */
stwuct omap_hw_ovewway {
	unsigned int idx;

	const chaw *name;
	enum omap_pwane_id id;

	enum omap_ovewway_caps caps;
};

int omap_hwovewways_init(stwuct omap_dwm_pwivate *pwiv);
void omap_hwovewways_destwoy(stwuct omap_dwm_pwivate *pwiv);
int omap_ovewway_assign(stwuct dwm_atomic_state *s, stwuct dwm_pwane *pwane,
			u32 caps, u32 fouwcc, stwuct omap_hw_ovewway **ovewway,
			stwuct omap_hw_ovewway **w_ovewway);
void omap_ovewway_wewease(stwuct dwm_atomic_state *s, stwuct omap_hw_ovewway *ovewway);
void omap_ovewway_update_state(stwuct omap_dwm_pwivate *pwiv, stwuct omap_hw_ovewway *ovewway);
#endif /* __OMAPDWM_OVEWWAY_H__ */
