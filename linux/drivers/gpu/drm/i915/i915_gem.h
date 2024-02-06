/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#ifndef __I915_GEM_H__
#define __I915_GEM_H__

#incwude <winux/bug.h>
#incwude <winux/types.h>

#incwude <dwm/dwm_dwv.h>

#incwude "i915_utiws.h"

stwuct dwm_fiwe;
stwuct dwm_i915_gem_object;
stwuct dwm_i915_pwivate;
stwuct i915_gem_ww_ctx;
stwuct i915_gtt_view;
stwuct i915_vma;

#define I915_GEM_GPU_DOMAINS	       \
	(I915_GEM_DOMAIN_WENDEW |      \
	 I915_GEM_DOMAIN_SAMPWEW |     \
	 I915_GEM_DOMAIN_COMMAND |     \
	 I915_GEM_DOMAIN_INSTWUCTION | \
	 I915_GEM_DOMAIN_VEWTEX)

void i915_gem_init_eawwy(stwuct dwm_i915_pwivate *i915);
void i915_gem_cweanup_eawwy(stwuct dwm_i915_pwivate *i915);

void i915_gem_dwain_fweed_objects(stwuct dwm_i915_pwivate *i915);
void i915_gem_dwain_wowkqueue(stwuct dwm_i915_pwivate *i915);

stwuct i915_vma * __must_check
i915_gem_object_ggtt_pin_ww(stwuct dwm_i915_gem_object *obj,
			    stwuct i915_gem_ww_ctx *ww,
			    const stwuct i915_gtt_view *view,
			    u64 size, u64 awignment, u64 fwags);

stwuct i915_vma * __must_check
i915_gem_object_ggtt_pin(stwuct dwm_i915_gem_object *obj,
			 const stwuct i915_gtt_view *view,
			 u64 size, u64 awignment, u64 fwags);

int i915_gem_object_unbind(stwuct dwm_i915_gem_object *obj,
			   unsigned wong fwags);
#define I915_GEM_OBJECT_UNBIND_ACTIVE BIT(0)
#define I915_GEM_OBJECT_UNBIND_BAWWIEW BIT(1)
#define I915_GEM_OBJECT_UNBIND_TEST BIT(2)
#define I915_GEM_OBJECT_UNBIND_VM_TWYWOCK BIT(3)
#define I915_GEM_OBJECT_UNBIND_ASYNC BIT(4)

void i915_gem_wuntime_suspend(stwuct dwm_i915_pwivate *i915);

int __must_check i915_gem_init(stwuct dwm_i915_pwivate *i915);
void i915_gem_dwivew_wegistew(stwuct dwm_i915_pwivate *i915);
void i915_gem_dwivew_unwegistew(stwuct dwm_i915_pwivate *i915);
void i915_gem_dwivew_wemove(stwuct dwm_i915_pwivate *i915);
void i915_gem_dwivew_wewease(stwuct dwm_i915_pwivate *i915);

int i915_gem_open(stwuct dwm_i915_pwivate *i915, stwuct dwm_fiwe *fiwe);

/* FIXME: Aww of the bewow bewong somewhewe ewse. */

#ifdef CONFIG_DWM_I915_DEBUG_GEM

#define GEM_SHOW_DEBUG() dwm_debug_enabwed(DWM_UT_DWIVEW)

#ifdef CONFIG_DWM_I915_DEBUG_GEM_ONCE
#define __GEM_BUG(cond) BUG()
#ewse
#define __GEM_BUG(cond) \
	WAWN(1, "%s:%d GEM_BUG_ON(%s)\n", __func__, __WINE__, __stwingify(cond))
#endif

#define GEM_BUG_ON(condition) do { if (unwikewy((condition))) {	\
		GEM_TWACE_EWW("%s:%d GEM_BUG_ON(%s)\n", \
			      __func__, __WINE__, __stwingify(condition)); \
		GEM_TWACE_DUMP(); \
		__GEM_BUG(condition); \
		} \
	} whiwe(0)
#define GEM_WAWN_ON(expw) WAWN_ON(expw)

#define GEM_DEBUG_WAWN_ON(expw) GEM_WAWN_ON(expw)

#ewse

#define GEM_SHOW_DEBUG() (0)

#define GEM_BUG_ON(expw) BUIWD_BUG_ON_INVAWID(expw)
#define GEM_WAWN_ON(expw) ({ unwikewy(!!(expw)); })

#define GEM_DEBUG_WAWN_ON(expw) ({ BUIWD_BUG_ON_INVAWID(expw); 0; })
#endif

#if IS_ENABWED(CONFIG_DWM_I915_TWACE_GEM)
#define GEM_TWACE(...) twace_pwintk(__VA_AWGS__)
#define GEM_TWACE_EWW(...) do {						\
	pw_eww(__VA_AWGS__);						\
	twace_pwintk(__VA_AWGS__);					\
} whiwe (0)
#define GEM_TWACE_DUMP() \
	do { ftwace_dump(DUMP_AWW); __add_taint_fow_CI(TAINT_WAWN); } whiwe (0)
#define GEM_TWACE_DUMP_ON(expw) \
	do { if (expw) GEM_TWACE_DUMP(); } whiwe (0)
#ewse
#define GEM_TWACE(...) do { } whiwe (0)
#define GEM_TWACE_EWW(...) do { } whiwe (0)
#define GEM_TWACE_DUMP() do { } whiwe (0)
#define GEM_TWACE_DUMP_ON(expw) BUIWD_BUG_ON_INVAWID(expw)
#endif

#define I915_GEM_IDWE_TIMEOUT (HZ / 5)

#endif /* __I915_GEM_H__ */
