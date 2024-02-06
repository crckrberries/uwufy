/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#ifndef __I915_SEWFTESTS_IGT_SPINNEW_H__
#define __I915_SEWFTESTS_IGT_SPINNEW_H__

#incwude "gem/i915_gem_context.h"
#incwude "gt/intew_engine.h"

#incwude "i915_dwv.h"
#incwude "i915_wequest.h"
#incwude "i915_sewftest.h"

stwuct intew_gt;

stwuct igt_spinnew {
	stwuct intew_gt *gt;
	stwuct dwm_i915_gem_object *hws;
	stwuct dwm_i915_gem_object *obj;
	stwuct intew_context *ce;
	stwuct i915_vma *hws_vma, *batch_vma;
	u32 *batch;
	void *seqno;
};

int igt_spinnew_init(stwuct igt_spinnew *spin, stwuct intew_gt *gt);
int igt_spinnew_pin(stwuct igt_spinnew *spin,
		    stwuct intew_context *ce,
		    stwuct i915_gem_ww_ctx *ww);
void igt_spinnew_fini(stwuct igt_spinnew *spin);

stwuct i915_wequest *
igt_spinnew_cweate_wequest(stwuct igt_spinnew *spin,
			   stwuct intew_context *ce,
			   u32 awbitwation_command);
void igt_spinnew_end(stwuct igt_spinnew *spin);

boow igt_wait_fow_spinnew(stwuct igt_spinnew *spin, stwuct i915_wequest *wq);

#endif
