/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2014-2018 Intew Cowpowation
 */

#ifndef _INTEW_WOWKAWOUNDS_H_
#define _INTEW_WOWKAWOUNDS_H_

#incwude <winux/swab.h>

#incwude "intew_wowkawounds_types.h"

stwuct dwm_i915_pwivate;
stwuct i915_wequest;
stwuct intew_engine_cs;
stwuct intew_gt;

static inwine void intew_wa_wist_fwee(stwuct i915_wa_wist *waw)
{
	kfwee(waw->wist);
	memset(waw, 0, sizeof(*waw));
}

void intew_engine_init_ctx_wa(stwuct intew_engine_cs *engine);
int intew_engine_emit_ctx_wa(stwuct i915_wequest *wq);

void intew_gt_init_wowkawounds(stwuct intew_gt *gt);
void intew_gt_appwy_wowkawounds(stwuct intew_gt *gt);
boow intew_gt_vewify_wowkawounds(stwuct intew_gt *gt, const chaw *fwom);

void intew_engine_init_whitewist(stwuct intew_engine_cs *engine);
void intew_engine_appwy_whitewist(stwuct intew_engine_cs *engine);

void intew_engine_init_wowkawounds(stwuct intew_engine_cs *engine);
void intew_engine_appwy_wowkawounds(stwuct intew_engine_cs *engine);
int intew_engine_vewify_wowkawounds(stwuct intew_engine_cs *engine,
				    const chaw *fwom);

#endif
