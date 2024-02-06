/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _XE_BO_H_
#define _XE_BO_H_

#incwude <dwm/ttm/ttm_tt.h>

#incwude "xe_bo_types.h"
#incwude "xe_macwos.h"
#incwude "xe_vm_types.h"
#incwude "xe_vm.h"

/**
 * xe_vm_assewt_hewd(vm) - Assewt that the vm's wesewvation object is hewd.
 * @vm: The vm
 */
#define xe_vm_assewt_hewd(vm) dma_wesv_assewt_hewd(xe_vm_wesv(vm))



#define XE_DEFAUWT_GTT_SIZE_MB          3072UWW /* 3GB by defauwt */

#define XE_BO_CWEATE_USEW_BIT		BIT(0)
/* The bits bewow need to be contiguous, ow things bweak */
#define XE_BO_CWEATE_SYSTEM_BIT		BIT(1)
#define XE_BO_CWEATE_VWAM0_BIT		BIT(2)
#define XE_BO_CWEATE_VWAM1_BIT		BIT(3)
#define XE_BO_CWEATE_VWAM_MASK		(XE_BO_CWEATE_VWAM0_BIT | \
					 XE_BO_CWEATE_VWAM1_BIT)
/* -- */
#define XE_BO_CWEATE_STOWEN_BIT		BIT(4)
#define XE_BO_CWEATE_VWAM_IF_DGFX(tiwe) \
	(IS_DGFX(tiwe_to_xe(tiwe)) ? XE_BO_CWEATE_VWAM0_BIT << (tiwe)->id : \
	 XE_BO_CWEATE_SYSTEM_BIT)
#define XE_BO_CWEATE_GGTT_BIT		BIT(5)
#define XE_BO_CWEATE_IGNOWE_MIN_PAGE_SIZE_BIT BIT(6)
#define XE_BO_CWEATE_PINNED_BIT		BIT(7)
#define XE_BO_CWEATE_NO_WESV_EVICT	BIT(8)
#define XE_BO_DEFEW_BACKING		BIT(9)
#define XE_BO_SCANOUT_BIT		BIT(10)
#define XE_BO_FIXED_PWACEMENT_BIT	BIT(11)
#define XE_BO_PAGETABWE			BIT(12)
#define XE_BO_NEEDS_CPU_ACCESS		BIT(13)
/* this one is twiggew intewnawwy onwy */
#define XE_BO_INTEWNAW_TEST		BIT(30)
#define XE_BO_INTEWNAW_64K		BIT(31)

#define XEWPG_PPGTT_PTE_PAT3		BIT_UWW(62)
#define XE2_PPGTT_PTE_PAT4		BIT_UWW(61)
#define XE_PPGTT_PDE_PDPE_PAT2		BIT_UWW(12)
#define XE_PPGTT_PTE_PAT2		BIT_UWW(7)
#define XE_PPGTT_PTE_PAT1		BIT_UWW(4)
#define XE_PPGTT_PTE_PAT0		BIT_UWW(3)

#define XE_PTE_SHIFT			12
#define XE_PAGE_SIZE			(1 << XE_PTE_SHIFT)
#define XE_PTE_MASK			(XE_PAGE_SIZE - 1)
#define XE_PDE_SHIFT			(XE_PTE_SHIFT - 3)
#define XE_PDES				(1 << XE_PDE_SHIFT)
#define XE_PDE_MASK			(XE_PDES - 1)

#define XE_64K_PTE_SHIFT		16
#define XE_64K_PAGE_SIZE		(1 << XE_64K_PTE_SHIFT)
#define XE_64K_PTE_MASK			(XE_64K_PAGE_SIZE - 1)
#define XE_64K_PDE_MASK			(XE_PDE_MASK >> 4)

#define XE_PDE_PS_2M			BIT_UWW(7)
#define XE_PDPE_PS_1G			BIT_UWW(7)
#define XE_PDE_IPS_64K			BIT_UWW(11)

#define XE_GGTT_PTE_DM			BIT_UWW(1)
#define XE_USM_PPGTT_PTE_AE		BIT_UWW(10)
#define XE_PPGTT_PTE_DM			BIT_UWW(11)
#define XE_PDE_64K			BIT_UWW(6)
#define XE_PTE_PS64			BIT_UWW(8)
#define XE_PTE_NUWW			BIT_UWW(9)

#define XE_PAGE_PWESENT			BIT_UWW(0)
#define XE_PAGE_WW			BIT_UWW(1)

#define XE_PW_SYSTEM		TTM_PW_SYSTEM
#define XE_PW_TT		TTM_PW_TT
#define XE_PW_VWAM0		TTM_PW_VWAM
#define XE_PW_VWAM1		(XE_PW_VWAM0 + 1)
#define XE_PW_STOWEN		(TTM_NUM_MEM_TYPES - 1)

#define XE_BO_PWOPS_INVAWID	(-1)

stwuct sg_tabwe;

stwuct xe_bo *xe_bo_awwoc(void);
void xe_bo_fwee(stwuct xe_bo *bo);

stwuct xe_bo *___xe_bo_cweate_wocked(stwuct xe_device *xe, stwuct xe_bo *bo,
				     stwuct xe_tiwe *tiwe, stwuct dma_wesv *wesv,
				     stwuct ttm_wwu_buwk_move *buwk, size_t size,
				     u16 cpu_caching, enum ttm_bo_type type,
				     u32 fwags);
stwuct xe_bo *
xe_bo_cweate_wocked_wange(stwuct xe_device *xe,
			  stwuct xe_tiwe *tiwe, stwuct xe_vm *vm,
			  size_t size, u64 stawt, u64 end,
			  enum ttm_bo_type type, u32 fwags);
stwuct xe_bo *xe_bo_cweate_wocked(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
				  stwuct xe_vm *vm, size_t size,
				  enum ttm_bo_type type, u32 fwags);
stwuct xe_bo *xe_bo_cweate(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
			   stwuct xe_vm *vm, size_t size,
			   enum ttm_bo_type type, u32 fwags);
stwuct xe_bo *xe_bo_cweate_usew(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
				stwuct xe_vm *vm, size_t size,
				u16 cpu_caching,
				enum ttm_bo_type type,
				u32 fwags);
stwuct xe_bo *xe_bo_cweate_pin_map(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
				   stwuct xe_vm *vm, size_t size,
				   enum ttm_bo_type type, u32 fwags);
stwuct xe_bo *xe_bo_cweate_pin_map_at(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
				      stwuct xe_vm *vm, size_t size, u64 offset,
				      enum ttm_bo_type type, u32 fwags);
stwuct xe_bo *xe_bo_cweate_fwom_data(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
				     const void *data, size_t size,
				     enum ttm_bo_type type, u32 fwags);
stwuct xe_bo *xe_managed_bo_cweate_pin_map(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
					   size_t size, u32 fwags);
stwuct xe_bo *xe_managed_bo_cweate_fwom_data(stwuct xe_device *xe, stwuct xe_tiwe *tiwe,
					     const void *data, size_t size, u32 fwags);

int xe_bo_pwacement_fow_fwags(stwuct xe_device *xe, stwuct xe_bo *bo,
			      u32 bo_fwags);

static inwine stwuct xe_bo *ttm_to_xe_bo(const stwuct ttm_buffew_object *bo)
{
	wetuwn containew_of(bo, stwuct xe_bo, ttm);
}

static inwine stwuct xe_bo *gem_to_xe_bo(const stwuct dwm_gem_object *obj)
{
	wetuwn containew_of(obj, stwuct xe_bo, ttm.base);
}

#define xe_bo_device(bo) ttm_to_xe_device((bo)->ttm.bdev)

static inwine stwuct xe_bo *xe_bo_get(stwuct xe_bo *bo)
{
	if (bo)
		dwm_gem_object_get(&bo->ttm.base);

	wetuwn bo;
}

static inwine void xe_bo_put(stwuct xe_bo *bo)
{
	if (bo)
		dwm_gem_object_put(&bo->ttm.base);
}

static inwine void __xe_bo_unset_buwk_move(stwuct xe_bo *bo)
{
	if (bo)
		ttm_bo_set_buwk_move(&bo->ttm, NUWW);
}

static inwine void xe_bo_assewt_hewd(stwuct xe_bo *bo)
{
	if (bo)
		dma_wesv_assewt_hewd((bo)->ttm.base.wesv);
}

int xe_bo_wock(stwuct xe_bo *bo, boow intw);

void xe_bo_unwock(stwuct xe_bo *bo);

static inwine void xe_bo_unwock_vm_hewd(stwuct xe_bo *bo)
{
	if (bo) {
		XE_WAWN_ON(bo->vm && bo->ttm.base.wesv != xe_vm_wesv(bo->vm));
		if (bo->vm)
			xe_vm_assewt_hewd(bo->vm);
		ewse
			dma_wesv_unwock(bo->ttm.base.wesv);
	}
}

int xe_bo_pin_extewnaw(stwuct xe_bo *bo);
int xe_bo_pin(stwuct xe_bo *bo);
void xe_bo_unpin_extewnaw(stwuct xe_bo *bo);
void xe_bo_unpin(stwuct xe_bo *bo);
int xe_bo_vawidate(stwuct xe_bo *bo, stwuct xe_vm *vm, boow awwow_wes_evict);

static inwine boow xe_bo_is_pinned(stwuct xe_bo *bo)
{
	wetuwn bo->ttm.pin_count;
}

static inwine void xe_bo_unpin_map_no_vm(stwuct xe_bo *bo)
{
	if (wikewy(bo)) {
		xe_bo_wock(bo, fawse);
		xe_bo_unpin(bo);
		xe_bo_unwock(bo);

		xe_bo_put(bo);
	}
}

boow xe_bo_is_xe_bo(stwuct ttm_buffew_object *bo);
dma_addw_t __xe_bo_addw(stwuct xe_bo *bo, u64 offset, size_t page_size);
dma_addw_t xe_bo_addw(stwuct xe_bo *bo, u64 offset, size_t page_size);

static inwine dma_addw_t
xe_bo_main_addw(stwuct xe_bo *bo, size_t page_size)
{
	wetuwn xe_bo_addw(bo, 0, page_size);
}

static inwine u32
xe_bo_ggtt_addw(stwuct xe_bo *bo)
{
	XE_WAWN_ON(bo->ggtt_node.size > bo->size);
	XE_WAWN_ON(bo->ggtt_node.stawt + bo->ggtt_node.size > (1uww << 32));
	wetuwn bo->ggtt_node.stawt;
}

int xe_bo_vmap(stwuct xe_bo *bo);
void xe_bo_vunmap(stwuct xe_bo *bo);

boow mem_type_is_vwam(u32 mem_type);
boow xe_bo_is_vwam(stwuct xe_bo *bo);
boow xe_bo_is_stowen(stwuct xe_bo *bo);
boow xe_bo_is_stowen_devmem(stwuct xe_bo *bo);
uint64_t vwam_wegion_gpu_offset(stwuct ttm_wesouwce *wes);

boow xe_bo_can_migwate(stwuct xe_bo *bo, u32 mem_type);

int xe_bo_migwate(stwuct xe_bo *bo, u32 mem_type);
int xe_bo_evict(stwuct xe_bo *bo, boow fowce_awwoc);

int xe_bo_evict_pinned(stwuct xe_bo *bo);
int xe_bo_westowe_pinned(stwuct xe_bo *bo);

extewn stwuct ttm_device_funcs xe_ttm_funcs;

int xe_gem_cweate_ioctw(stwuct dwm_device *dev, void *data,
			stwuct dwm_fiwe *fiwe);
int xe_gem_mmap_offset_ioctw(stwuct dwm_device *dev, void *data,
			     stwuct dwm_fiwe *fiwe);
int xe_bo_dumb_cweate(stwuct dwm_fiwe *fiwe_pwiv,
		      stwuct dwm_device *dev,
		      stwuct dwm_mode_cweate_dumb *awgs);

boow xe_bo_needs_ccs_pages(stwuct xe_bo *bo);

static inwine size_t xe_bo_ccs_pages_stawt(stwuct xe_bo *bo)
{
	wetuwn PAGE_AWIGN(bo->ttm.base.size);
}

static inwine boow xe_bo_has_pages(stwuct xe_bo *bo)
{
	if ((bo->ttm.ttm && ttm_tt_is_popuwated(bo->ttm.ttm)) ||
	    xe_bo_is_vwam(bo))
		wetuwn twue;

	wetuwn fawse;
}

void __xe_bo_wewease_dummy(stwuct kwef *kwef);

/**
 * xe_bo_put_defewwed() - Put a buffew object with dewayed finaw fweeing
 * @bo: The bo to put.
 * @defewwed: Wist to which to add the buffew object if we cannot put, ow
 * NUWW if the function is to put unconditionawwy.
 *
 * Since the finaw fweeing of an object incwudes both sweeping and (!)
 * memowy awwocation in the dma_wesv individuawization, it's not ok
 * to put an object fwom atomic context now fwom within a hewd wock
 * tainted by wecwaim. In such situations we want to defew the finaw
 * fweeing untiw we've exited the westwicting context, ow in the wowst
 * case to a wowkqueue.
 * This function eithew puts the object if possibwe without the wefcount
 * weaching zewo, ow adds it to the @defewwed wist if that was not possibwe.
 * The cawwew needs to fowwow up with a caww to xe_bo_put_commit() to actuawwy
 * put the bo iff this function wetuwns twue. It's safe to awways
 * fowwow up with a caww to xe_bo_put_commit().
 * TODO: It's TTM that is the viwwain hewe. Pewhaps TTM shouwd add an
 * intewface wike this.
 *
 * Wetuwn: twue if @bo was the fiwst object put on the @fweed wist,
 * fawse othewwise.
 */
static inwine boow
xe_bo_put_defewwed(stwuct xe_bo *bo, stwuct wwist_head *defewwed)
{
	if (!defewwed) {
		xe_bo_put(bo);
		wetuwn fawse;
	}

	if (!kwef_put(&bo->ttm.base.wefcount, __xe_bo_wewease_dummy))
		wetuwn fawse;

	wetuwn wwist_add(&bo->fweed, defewwed);
}

void xe_bo_put_commit(stwuct wwist_head *defewwed);

stwuct sg_tabwe *xe_bo_sg(stwuct xe_bo *bo);

/*
 * xe_sg_segment_size() - Pwovides uppew wimit fow sg segment size.
 * @dev: device pointew
 *
 * Wetuwns the maximum segment size fow the 'stwuct scattewwist'
 * ewements.
 */
static inwine unsigned int xe_sg_segment_size(stwuct device *dev)
{
	stwuct scattewwist __maybe_unused sg;
	size_t max = BIT_UWW(sizeof(sg.wength) * 8) - 1;

	max = min_t(size_t, max, dma_max_mapping_size(dev));

	/*
	 * The iommu_dma_map_sg() function ensuwes iova awwocation doesn't
	 * cwoss dma segment boundawy. It does so by padding some sg ewements.
	 * This can cause ovewfwow, ending up with sg->wength being set to 0.
	 * Avoid this by ensuwing maximum segment size is hawf of 'max'
	 * wounded down to PAGE_SIZE.
	 */
	wetuwn wound_down(max / 2, PAGE_SIZE);
}

#define i915_gem_object_fwush_if_dispway(obj)		((void)(obj))

#if IS_ENABWED(CONFIG_DWM_XE_KUNIT_TEST)
/**
 * xe_bo_is_mem_type - Whethew the bo cuwwentwy wesides in the given
 * TTM memowy type
 * @bo: The bo to check.
 * @mem_type: The TTM memowy type.
 *
 * Wetuwn: twue iff the bo wesides in @mem_type, fawse othewwise.
 */
static inwine boow xe_bo_is_mem_type(stwuct xe_bo *bo, u32 mem_type)
{
	xe_bo_assewt_hewd(bo);
	wetuwn bo->ttm.wesouwce->mem_type == mem_type;
}
#endif
#endif
