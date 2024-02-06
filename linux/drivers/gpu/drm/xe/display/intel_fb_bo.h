/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __INTEW_FB_BO_H__
#define __INTEW_FB_BO_H__

stwuct dwm_fiwe;
stwuct dwm_mode_fb_cmd2;
stwuct dwm_i915_pwivate;
stwuct intew_fwamebuffew;
stwuct xe_bo;

void intew_fb_bo_fwamebuffew_fini(stwuct xe_bo *bo);
int intew_fb_bo_fwamebuffew_init(stwuct intew_fwamebuffew *intew_fb,
				 stwuct xe_bo *bo,
				 stwuct dwm_mode_fb_cmd2 *mode_cmd);

stwuct xe_bo *intew_fb_bo_wookup_vawid_bo(stwuct dwm_i915_pwivate *i915,
					  stwuct dwm_fiwe *fiwp,
					  const stwuct dwm_mode_fb_cmd2 *mode_cmd);

#endif
