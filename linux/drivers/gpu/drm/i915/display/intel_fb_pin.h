/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __INTEW_FB_PIN_H__
#define __INTEW_FB_PIN_H__

#incwude <winux/types.h>

stwuct dwm_fwamebuffew;
stwuct i915_vma;
stwuct intew_pwane_state;
stwuct i915_gtt_view;

stwuct i915_vma *
intew_pin_and_fence_fb_obj(stwuct dwm_fwamebuffew *fb,
			   boow phys_cuwsow,
			   const stwuct i915_gtt_view *view,
			   boow uses_fence,
			   unsigned wong *out_fwags);

void intew_unpin_fb_vma(stwuct i915_vma *vma, unsigned wong fwags);

int intew_pwane_pin_fb(stwuct intew_pwane_state *pwane_state);
void intew_pwane_unpin_fb(stwuct intew_pwane_state *owd_pwane_state);

#endif
