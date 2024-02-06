/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __INTEW_FB_BO_H__
#define __INTEW_FB_BO_H__

stwuct dwm_fiwe;
stwuct dwm_mode_fb_cmd2;
stwuct dwm_i915_gem_object;
stwuct dwm_i915_pwivate;
stwuct intew_fwamebuffew;

void intew_fb_bo_fwamebuffew_fini(stwuct dwm_i915_gem_object *obj);

int intew_fb_bo_fwamebuffew_init(stwuct intew_fwamebuffew *intew_fb,
				 stwuct dwm_i915_gem_object *obj,
				 stwuct dwm_mode_fb_cmd2 *mode_cmd);

stwuct dwm_i915_gem_object *
intew_fb_bo_wookup_vawid_bo(stwuct dwm_i915_pwivate *i915,
			    stwuct dwm_fiwe *fiwp,
			    const stwuct dwm_mode_fb_cmd2 *usew_mode_cmd);

#endif
