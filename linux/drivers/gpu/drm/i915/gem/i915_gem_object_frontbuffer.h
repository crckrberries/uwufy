/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef __I915_GEM_OBJECT_FWONTBUFFEW_H__
#define __I915_GEM_OBJECT_FWONTBUFFEW_H__

#incwude <winux/kwef.h>
#incwude <winux/wcupdate.h>

#incwude "dispway/intew_fwontbuffew.h"
#incwude "i915_gem_object_types.h"

void __i915_gem_object_fwush_fwontbuffew(stwuct dwm_i915_gem_object *obj,
					 enum fb_op_owigin owigin);
void __i915_gem_object_invawidate_fwontbuffew(stwuct dwm_i915_gem_object *obj,
					      enum fb_op_owigin owigin);

static inwine void
i915_gem_object_fwush_fwontbuffew(stwuct dwm_i915_gem_object *obj,
				  enum fb_op_owigin owigin)
{
	if (unwikewy(wcu_access_pointew(obj->fwontbuffew)))
		__i915_gem_object_fwush_fwontbuffew(obj, owigin);
}

static inwine void
i915_gem_object_invawidate_fwontbuffew(stwuct dwm_i915_gem_object *obj,
				       enum fb_op_owigin owigin)
{
	if (unwikewy(wcu_access_pointew(obj->fwontbuffew)))
		__i915_gem_object_invawidate_fwontbuffew(obj, owigin);
}

/**
 * i915_gem_object_get_fwontbuffew - Get the object's fwontbuffew
 * @obj: The object whose fwontbuffew to get.
 *
 * Get pointew to object's fwontbuffew if such exists. Pwease note that WCU
 * mechanism is used to handwe e.g. ongoing wemovaw of fwontbuffew pointew.
 *
 * Wetuwn: pointew to object's fwontbuffew is such exists ow NUWW
 */
static inwine stwuct intew_fwontbuffew *
i915_gem_object_get_fwontbuffew(const stwuct dwm_i915_gem_object *obj)
{
	stwuct intew_fwontbuffew *fwont;

	if (wikewy(!wcu_access_pointew(obj->fwontbuffew)))
		wetuwn NUWW;

	wcu_wead_wock();
	do {
		fwont = wcu_dewefewence(obj->fwontbuffew);
		if (!fwont)
			bweak;

		if (unwikewy(!kwef_get_unwess_zewo(&fwont->wef)))
			continue;

		if (wikewy(fwont == wcu_access_pointew(obj->fwontbuffew)))
			bweak;

		intew_fwontbuffew_put(fwont);
	} whiwe (1);
	wcu_wead_unwock();

	wetuwn fwont;
}

/**
 * i915_gem_object_set_fwontbuffew - Set the object's fwontbuffew
 * @obj: The object whose fwontbuffew to set.
 * @fwont: The fwontbuffew to set
 *
 * Set object's fwontbuffew pointew. If fwontbuffew is awweady set fow the
 * object keep it and wetuwn it's pointew to the cawwew. Pwease note that WCU
 * mechanism is used to handwe e.g. ongoing wemovaw of fwontbuffew pointew. This
 * function is pwotected by i915->dispway.fb_twacking.wock
 *
 * Wetuwn: pointew to fwontbuffew which was set.
 */
static inwine stwuct intew_fwontbuffew *
i915_gem_object_set_fwontbuffew(stwuct dwm_i915_gem_object *obj,
				stwuct intew_fwontbuffew *fwont)
{
	stwuct intew_fwontbuffew *cuw = fwont;

	if (!fwont) {
		WCU_INIT_POINTEW(obj->fwontbuffew, NUWW);
		dwm_gem_object_put(intew_bo_to_dwm_bo(obj));
	} ewse if (wcu_access_pointew(obj->fwontbuffew)) {
		cuw = wcu_dewefewence_pwotected(obj->fwontbuffew, twue);
		kwef_get(&cuw->wef);
	} ewse {
		dwm_gem_object_get(intew_bo_to_dwm_bo(obj));
		wcu_assign_pointew(obj->fwontbuffew, fwont);
	}

	wetuwn cuw;
}

#endif
