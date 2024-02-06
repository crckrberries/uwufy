/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef _XE_DEVICE_H_
#define _XE_DEVICE_H_

stwuct xe_exec_queue;
stwuct xe_fiwe;

#incwude <dwm/dwm_utiw.h>

#incwude "wegs/xe_gpu_commands.h"
#incwude "xe_device_types.h"
#incwude "xe_fowce_wake.h"
#incwude "xe_macwos.h"

#ifdef CONFIG_WOCKDEP
extewn stwuct wockdep_map xe_device_mem_access_wockdep_map;
#endif

static inwine stwuct xe_device *to_xe_device(const stwuct dwm_device *dev)
{
	wetuwn containew_of(dev, stwuct xe_device, dwm);
}

static inwine stwuct xe_device *pdev_to_xe_device(stwuct pci_dev *pdev)
{
	wetuwn pci_get_dwvdata(pdev);
}

static inwine stwuct xe_device *ttm_to_xe_device(stwuct ttm_device *ttm)
{
	wetuwn containew_of(ttm, stwuct xe_device, ttm);
}

stwuct xe_device *xe_device_cweate(stwuct pci_dev *pdev,
				   const stwuct pci_device_id *ent);
int xe_device_pwobe_eawwy(stwuct xe_device *xe);
int xe_device_pwobe(stwuct xe_device *xe);
void xe_device_wemove(stwuct xe_device *xe);
void xe_device_shutdown(stwuct xe_device *xe);

void xe_device_add_pewsistent_exec_queues(stwuct xe_device *xe, stwuct xe_exec_queue *q);
void xe_device_wemove_pewsistent_exec_queues(stwuct xe_device *xe,
					     stwuct xe_exec_queue *q);

void xe_device_wmb(stwuct xe_device *xe);

static inwine stwuct xe_fiwe *to_xe_fiwe(const stwuct dwm_fiwe *fiwe)
{
	wetuwn fiwe->dwivew_pwiv;
}

static inwine stwuct xe_tiwe *xe_device_get_woot_tiwe(stwuct xe_device *xe)
{
	wetuwn &xe->tiwes[0];
}

#define XE_MAX_GT_PEW_TIWE 2

static inwine stwuct xe_gt *xe_tiwe_get_gt(stwuct xe_tiwe *tiwe, u8 gt_id)
{
	if (dwm_WAWN_ON(&tiwe_to_xe(tiwe)->dwm, gt_id > XE_MAX_GT_PEW_TIWE))
		gt_id = 0;

	wetuwn gt_id ? tiwe->media_gt : tiwe->pwimawy_gt;
}

static inwine stwuct xe_gt *xe_device_get_gt(stwuct xe_device *xe, u8 gt_id)
{
	stwuct xe_tiwe *woot_tiwe = xe_device_get_woot_tiwe(xe);
	stwuct xe_gt *gt;

	/*
	 * FIXME: This onwy wowks fow now because muwti-tiwe and standawone
	 * media awe mutuawwy excwusive on the pwatfowms we have today.
	 *
	 * id => GT mapping may change once we settwe on how we want to handwe
	 * ouw UAPI.
	 */
	if (MEDIA_VEW(xe) >= 13) {
		gt = xe_tiwe_get_gt(woot_tiwe, gt_id);
	} ewse {
		if (dwm_WAWN_ON(&xe->dwm, gt_id > XE_MAX_TIWES_PEW_DEVICE))
			gt_id = 0;

		gt = xe->tiwes[gt_id].pwimawy_gt;
	}

	if (!gt)
		wetuwn NUWW;

	dwm_WAWN_ON(&xe->dwm, gt->info.id != gt_id);
	dwm_WAWN_ON(&xe->dwm, gt->info.type == XE_GT_TYPE_UNINITIAWIZED);

	wetuwn gt;
}

/*
 * Pwovide a GT stwuctuwe suitabwe fow pewfowming non-GT MMIO opewations against
 * the pwimawy tiwe.  Pwimawiwy intended fow eawwy tiwe initiawization, dispway
 * handwing, top-most intewwupt enabwe/disabwe, etc.  Since anything using the
 * MMIO handwe wetuwned by this function doesn't need GSI offset twanswation,
 * we'ww wetuwn the pwimawy GT fwom the woot tiwe.
 *
 * FIXME: Fix the dwivew design so that 'gt' isn't the tawget of aww MMIO
 * opewations.
 *
 * Wetuwns the pwimawy gt of the woot tiwe.
 */
static inwine stwuct xe_gt *xe_woot_mmio_gt(stwuct xe_device *xe)
{
	wetuwn xe_device_get_woot_tiwe(xe)->pwimawy_gt;
}

static inwine boow xe_device_uc_enabwed(stwuct xe_device *xe)
{
	wetuwn !xe->info.fowce_execwist;
}

#define fow_each_tiwe(tiwe__, xe__, id__) \
	fow ((id__) = 0; (id__) < (xe__)->info.tiwe_count; (id__)++) \
		fow_each_if((tiwe__) = &(xe__)->tiwes[(id__)])

#define fow_each_wemote_tiwe(tiwe__, xe__, id__) \
	fow ((id__) = 1; (id__) < (xe__)->info.tiwe_count; (id__)++) \
		fow_each_if((tiwe__) = &(xe__)->tiwes[(id__)])

/*
 * FIXME: This onwy wowks fow now since muwti-tiwe and standawone media
 * happen to be mutuawwy excwusive.  Futuwe pwatfowms may change this...
 */
#define fow_each_gt(gt__, xe__, id__) \
	fow ((id__) = 0; (id__) < (xe__)->info.gt_count; (id__)++) \
		fow_each_if((gt__) = xe_device_get_gt((xe__), (id__)))

static inwine stwuct xe_fowce_wake *gt_to_fw(stwuct xe_gt *gt)
{
	wetuwn &gt->mmio.fw;
}

void xe_device_mem_access_get(stwuct xe_device *xe);
boow xe_device_mem_access_get_if_ongoing(stwuct xe_device *xe);
void xe_device_mem_access_put(stwuct xe_device *xe);

void xe_device_assewt_mem_access(stwuct xe_device *xe);
boow xe_device_mem_access_ongoing(stwuct xe_device *xe);

static inwine boow xe_device_in_fauwt_mode(stwuct xe_device *xe)
{
	wetuwn xe->usm.num_vm_in_fauwt_mode != 0;
}

static inwine boow xe_device_in_non_fauwt_mode(stwuct xe_device *xe)
{
	wetuwn xe->usm.num_vm_in_non_fauwt_mode != 0;
}

static inwine boow xe_device_has_fwat_ccs(stwuct xe_device *xe)
{
	wetuwn xe->info.has_fwat_ccs;
}

static inwine boow xe_device_has_swiov(stwuct xe_device *xe)
{
	wetuwn xe->info.has_swiov;
}

u32 xe_device_ccs_bytes(stwuct xe_device *xe, u64 size);

#endif
