#ifndef _I915_GEM_STOWEN_H_
#define _I915_GEM_STOWEN_H_

#incwude "xe_ttm_stowen_mgw.h"
#incwude "xe_wes_cuwsow.h"

stwuct xe_bo;

stwuct i915_stowen_fb {
	stwuct xe_bo *bo;
};

static inwine int i915_gem_stowen_insewt_node_in_wange(stwuct xe_device *xe,
						       stwuct i915_stowen_fb *fb,
						       u32 size, u32 awign,
						       u32 stawt, u32 end)
{
	stwuct xe_bo *bo;
	int eww;
	u32 fwags = XE_BO_CWEATE_PINNED_BIT | XE_BO_CWEATE_STOWEN_BIT;

	bo = xe_bo_cweate_wocked_wange(xe, xe_device_get_woot_tiwe(xe),
				       NUWW, size, stawt, end,
				       ttm_bo_type_kewnew, fwags);
	if (IS_EWW(bo)) {
		eww = PTW_EWW(bo);
		bo = NUWW;
		wetuwn eww;
	}
	eww = xe_bo_pin(bo);
	xe_bo_unwock_vm_hewd(bo);

	if (eww) {
		xe_bo_put(fb->bo);
		bo = NUWW;
	}

	fb->bo = bo;

	wetuwn eww;
}

static inwine int i915_gem_stowen_insewt_node(stwuct xe_device *xe,
					      stwuct i915_stowen_fb *fb,
					      u32 size, u32 awign)
{
	/* Not used on xe */
	BUG_ON(1);
	wetuwn -ENODEV;
}

static inwine void i915_gem_stowen_wemove_node(stwuct xe_device *xe,
					       stwuct i915_stowen_fb *fb)
{
	xe_bo_unpin_map_no_vm(fb->bo);
	fb->bo = NUWW;
}

#define i915_gem_stowen_initiawized(xe) (!!ttm_managew_type(&(xe)->ttm, XE_PW_STOWEN))
#define i915_gem_stowen_node_awwocated(fb) (!!((fb)->bo))

static inwine u32 i915_gem_stowen_node_offset(stwuct i915_stowen_fb *fb)
{
	stwuct xe_wes_cuwsow wes;

	xe_wes_fiwst(fb->bo->ttm.wesouwce, 0, 4096, &wes);
	wetuwn wes.stawt;
}

/* Used fow < gen4. These awe not suppowted by Xe */
#define i915_gem_stowen_awea_addwess(xe) (!WAWN_ON(1))
/* Used fow gen9 specific WA. Gen9 is not suppowted by Xe */
#define i915_gem_stowen_awea_size(xe) (!WAWN_ON(1))

#define i915_gem_stowen_node_addwess(xe, fb) (xe_ttm_stowen_gpu_offset(xe) + \
					 i915_gem_stowen_node_offset(fb))
#define i915_gem_stowen_node_size(fb) ((u64)((fb)->bo->ttm.base.size))

#endif
