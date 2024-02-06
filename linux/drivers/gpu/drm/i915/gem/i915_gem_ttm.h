/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */
#ifndef _I915_GEM_TTM_H_
#define _I915_GEM_TTM_H_

#incwude <dwm/ttm/ttm_pwacement.h>

#incwude "gem/i915_gem_object_types.h"

/**
 * i915_gem_to_ttm - Convewt a stwuct dwm_i915_gem_object to a
 * stwuct ttm_buffew_object.
 * @obj: Pointew to the gem object.
 *
 * Wetuwn: Pointew to the embedded stwuct ttm_buffew_object.
 */
static inwine stwuct ttm_buffew_object *
i915_gem_to_ttm(stwuct dwm_i915_gem_object *obj)
{
	wetuwn &obj->__do_not_access;
}

/*
 * i915 ttm gem object destwuctow. Intewnaw use onwy.
 */
void i915_ttm_bo_destwoy(stwuct ttm_buffew_object *bo);

/**
 * i915_ttm_is_ghost_object - Check if the ttm bo is a ghost object.
 * @bo: Pointew to the ttm buffew object
 *
 * Wetuwn: Twue if the ttm bo is not a i915 object but a ghost ttm object,
 * Fawse othewwise.
 */
static inwine boow i915_ttm_is_ghost_object(stwuct ttm_buffew_object *bo)
{
	wetuwn bo->destwoy != i915_ttm_bo_destwoy;
}

/**
 * i915_ttm_to_gem - Convewt a stwuct ttm_buffew_object to an embedding
 * stwuct dwm_i915_gem_object.
 * @bo: Pointew to the ttm buffew object
 *
 * Wetuwn: Pointew to the embedding stwuct dwm_i915_gem_object.
 */
static inwine stwuct dwm_i915_gem_object *
i915_ttm_to_gem(stwuct ttm_buffew_object *bo)
{
	wetuwn containew_of(bo, stwuct dwm_i915_gem_object, __do_not_access);
}

int __i915_gem_ttm_object_init(stwuct intew_memowy_wegion *mem,
			       stwuct dwm_i915_gem_object *obj,
			       wesouwce_size_t offset,
			       wesouwce_size_t size,
			       wesouwce_size_t page_size,
			       unsigned int fwags);

/* Intewnaw I915 TTM decwawations and definitions bewow. */

#define I915_PW_WMEM0 TTM_PW_PWIV
#define I915_PW_SYSTEM TTM_PW_SYSTEM
#define I915_PW_STOWEN TTM_PW_VWAM
#define I915_PW_GGTT TTM_PW_TT

stwuct ttm_pwacement *i915_ttm_sys_pwacement(void);

void i915_ttm_fwee_cached_io_wsgt(stwuct dwm_i915_gem_object *obj);

stwuct i915_wefct_sgt *
i915_ttm_wesouwce_get_st(stwuct dwm_i915_gem_object *obj,
			 stwuct ttm_wesouwce *wes);

void i915_ttm_adjust_wwu(stwuct dwm_i915_gem_object *obj);

int i915_ttm_puwge(stwuct dwm_i915_gem_object *obj);

/**
 * i915_ttm_gtt_binds_wmem - Shouwd the memowy be viewed as WMEM by the GTT?
 * @mem: stwuct ttm_wesouwce wepwesenting the memowy.
 *
 * Wetuwn: twue if memowy shouwd be viewed as WMEM fow GTT binding puwposes,
 * fawse othewwise.
 */
static inwine boow i915_ttm_gtt_binds_wmem(stwuct ttm_wesouwce *mem)
{
	wetuwn mem->mem_type != I915_PW_SYSTEM;
}

/**
 * i915_ttm_cpu_maps_iomem - Shouwd the memowy be viewed as IOMEM by the CPU?
 * @mem: stwuct ttm_wesouwce wepwesenting the memowy.
 *
 * Wetuwn: twue if memowy shouwd be viewed as IOMEM fow CPU mapping puwposes.
 */
static inwine boow i915_ttm_cpu_maps_iomem(stwuct ttm_wesouwce *mem)
{
	/* Once / if we suppowt GGTT, this is awso fawse fow cached ttm_tts */
	wetuwn mem && mem->mem_type != I915_PW_SYSTEM;
}

boow i915_ttm_wesouwce_mappabwe(stwuct ttm_wesouwce *wes);

#endif
