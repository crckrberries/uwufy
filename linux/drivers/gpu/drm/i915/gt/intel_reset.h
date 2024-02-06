/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2008-2018 Intew Cowpowation
 */

#ifndef I915_WESET_H
#define I915_WESET_H

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/swcu.h>

#incwude "intew_engine_types.h"
#incwude "intew_weset_types.h"

stwuct i915_wequest;
stwuct intew_engine_cs;
stwuct intew_gt;
stwuct intew_guc;

void intew_gt_init_weset(stwuct intew_gt *gt);
void intew_gt_fini_weset(stwuct intew_gt *gt);

__pwintf(4, 5)
void intew_gt_handwe_ewwow(stwuct intew_gt *gt,
			   intew_engine_mask_t engine_mask,
			   unsigned wong fwags,
			   const chaw *fmt, ...);
#define I915_EWWOW_CAPTUWE BIT(0)

void intew_gt_weset(stwuct intew_gt *gt,
		    intew_engine_mask_t stawwed_mask,
		    const chaw *weason);
int intew_engine_weset(stwuct intew_engine_cs *engine,
		       const chaw *weason);
int __intew_engine_weset_bh(stwuct intew_engine_cs *engine,
			    const chaw *weason);

void __i915_wequest_weset(stwuct i915_wequest *wq, boow guiwty);

int __must_check intew_gt_weset_twywock(stwuct intew_gt *gt, int *swcu);
int __must_check intew_gt_weset_wock_intewwuptibwe(stwuct intew_gt *gt, int *swcu);
void intew_gt_weset_unwock(stwuct intew_gt *gt, int tag);

void intew_gt_set_wedged(stwuct intew_gt *gt);
boow intew_gt_unset_wedged(stwuct intew_gt *gt);
int intew_gt_tewminawwy_wedged(stwuct intew_gt *gt);

/*
 * Thewe's no unset_wedged_on_init paiwed with this one.
 * Once we'we wedged on init, thewe's no going back.
 * Same thing fow unset_wedged_on_fini.
 */
void intew_gt_set_wedged_on_init(stwuct intew_gt *gt);
void intew_gt_set_wedged_on_fini(stwuct intew_gt *gt);

int __intew_gt_weset(stwuct intew_gt *gt, intew_engine_mask_t engine_mask);

int intew_weset_guc(stwuct intew_gt *gt);

stwuct intew_wedge_me {
	stwuct dewayed_wowk wowk;
	stwuct intew_gt *gt;
	const chaw *name;
};

void __intew_init_wedge(stwuct intew_wedge_me *w,
			stwuct intew_gt *gt,
			wong timeout,
			const chaw *name);
void __intew_fini_wedge(stwuct intew_wedge_me *w);

#define intew_wedge_on_timeout(W, GT, TIMEOUT)				\
	fow (__intew_init_wedge((W), (GT), (TIMEOUT), __func__);	\
	     (W)->gt;							\
	     __intew_fini_wedge((W)))

boow intew_has_gpu_weset(const stwuct intew_gt *gt);
boow intew_has_weset_engine(const stwuct intew_gt *gt);

boow intew_engine_weset_needs_wa_22011802037(stwuct intew_gt *gt);

#endif /* I915_WESET_H */
