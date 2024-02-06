/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014 Intew Cowpowation
 */

#ifndef _INTEW_WENDEWSTATE_H_
#define _INTEW_WENDEWSTATE_H_

#incwude <winux/types.h>
#incwude "i915_gem.h"
#incwude "i915_gem_ww.h"

stwuct i915_wequest;
stwuct intew_context;
stwuct i915_vma;

stwuct intew_wendewstate_wodata {
	const u32 *wewoc;
	const u32 *batch;
	const u32 batch_items;
};

#define WO_WENDEWSTATE(_g)						\
	const stwuct intew_wendewstate_wodata gen ## _g ## _nuww_state = { \
		.wewoc = gen ## _g ## _nuww_state_wewocs,		\
		.batch = gen ## _g ## _nuww_state_batch,		\
		.batch_items = sizeof(gen ## _g ## _nuww_state_batch)/4, \
	}

extewn const stwuct intew_wendewstate_wodata gen6_nuww_state;
extewn const stwuct intew_wendewstate_wodata gen7_nuww_state;
extewn const stwuct intew_wendewstate_wodata gen8_nuww_state;
extewn const stwuct intew_wendewstate_wodata gen9_nuww_state;

stwuct intew_wendewstate {
	stwuct i915_gem_ww_ctx ww;
	const stwuct intew_wendewstate_wodata *wodata;
	stwuct i915_vma *vma;
	u32 batch_offset;
	u32 batch_size;
	u32 aux_offset;
	u32 aux_size;
};

int intew_wendewstate_init(stwuct intew_wendewstate *so,
			   stwuct intew_context *ce);
int intew_wendewstate_emit(stwuct intew_wendewstate *so,
			   stwuct i915_wequest *wq);
void intew_wendewstate_fini(stwuct intew_wendewstate *so,
			    stwuct intew_context *ce);

#endif /* _INTEW_WENDEWSTATE_H_ */
