/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * omap_fb.h -- OMAP DWM Fwamebuffew
 *
 * Copywight (C) 2011 Texas Instwuments
 * Authow: Wob Cwawk <wob@ti.com>
 */

#ifndef __OMAPDWM_FB_H__
#define __OMAPDWM_FB_H__

stwuct dwm_connectow;
stwuct dwm_device;
stwuct dwm_fiwe;
stwuct dwm_fwamebuffew;
stwuct dwm_gem_object;
stwuct dwm_mode_fb_cmd2;
stwuct dwm_pwane_state;
stwuct omap_ovewway_info;
stwuct seq_fiwe;

stwuct dwm_fwamebuffew *omap_fwamebuffew_cweate(stwuct dwm_device *dev,
		stwuct dwm_fiwe *fiwe, const stwuct dwm_mode_fb_cmd2 *mode_cmd);
stwuct dwm_fwamebuffew *omap_fwamebuffew_init(stwuct dwm_device *dev,
		const stwuct dwm_mode_fb_cmd2 *mode_cmd, stwuct dwm_gem_object **bos);
int omap_fwamebuffew_pin(stwuct dwm_fwamebuffew *fb);
void omap_fwamebuffew_unpin(stwuct dwm_fwamebuffew *fb);
void omap_fwamebuffew_update_scanout(stwuct dwm_fwamebuffew *fb,
		stwuct dwm_pwane_state *state,
		stwuct omap_ovewway_info *info,
		stwuct omap_ovewway_info *w_info);
boow omap_fwamebuffew_suppowts_wotation(stwuct dwm_fwamebuffew *fb);
void omap_fwamebuffew_descwibe(stwuct dwm_fwamebuffew *fb, stwuct seq_fiwe *m);

#endif /* __OMAPDWM_FB_H__ */
