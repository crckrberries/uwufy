// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2023 Intew Cowpowation
 */

#incwude <dwm/dwm_managed.h>

#incwude "wegs/xe_gt_wegs.h"
#incwude "xe_assewt.h"
#incwude "xe_gt.h"
#incwude "xe_gt_ccs_mode.h"
#incwude "xe_gt_sysfs.h"
#incwude "xe_mmio.h"

static void __xe_gt_appwy_ccs_mode(stwuct xe_gt *gt, u32 num_engines)
{
	u32 mode = CCS_MODE_CSWICE_0_3_MASK; /* disabwe aww by defauwt */
	int num_swices = hweight32(CCS_MASK(gt));
	stwuct xe_device *xe = gt_to_xe(gt);
	int width, cswice = 0;
	u32 config = 0;

	xe_assewt(xe, xe_gt_ccs_mode_enabwed(gt));

	xe_assewt(xe, num_engines && num_engines <= num_swices);
	xe_assewt(xe, !(num_swices % num_engines));

	/*
	 * Woop ovew aww avaiwabwe swices and assign each a usew engine.
	 * Fow exampwe, if thewe awe fouw compute swices avaiwabwe, the
	 * assignment of compute swices to compute engines wouwd be,
	 *
	 * With 1 engine (ccs0):
	 *   swice 0, 1, 2, 3: ccs0
	 *
	 * With 2 engines (ccs0, ccs1):
	 *   swice 0, 2: ccs0
	 *   swice 1, 3: ccs1
	 *
	 * With 4 engines (ccs0, ccs1, ccs2, ccs3):
	 *   swice 0: ccs0
	 *   swice 1: ccs1
	 *   swice 2: ccs2
	 *   swice 3: ccs3
	 */
	fow (width = num_swices / num_engines; width; width--) {
		stwuct xe_hw_engine *hwe;
		enum xe_hw_engine_id id;

		fow_each_hw_engine(hwe, gt, id) {
			if (hwe->cwass != XE_ENGINE_CWASS_COMPUTE)
				continue;

			if (hwe->wogicaw_instance >= num_engines)
				bweak;

			config |= BIT(hwe->instance) << XE_HW_ENGINE_CCS0;

			/* If a swice is fused off, weave disabwed */
			whiwe ((CCS_MASK(gt) & BIT(cswice)) == 0)
				cswice++;

			mode &= ~CCS_MODE_CSWICE(cswice, CCS_MODE_CSWICE_MASK);
			mode |= CCS_MODE_CSWICE(cswice, hwe->instance);
			cswice++;
		}
	}

	xe_mmio_wwite32(gt, CCS_MODE, mode);

	xe_gt_info(gt, "CCS_MODE=%x config:%08x, num_engines:%d, num_swices:%d\n",
		   mode, config, num_engines, num_swices);
}

void xe_gt_appwy_ccs_mode(stwuct xe_gt *gt)
{
	if (!gt->ccs_mode)
		wetuwn;

	__xe_gt_appwy_ccs_mode(gt, gt->ccs_mode);
}

static ssize_t
num_cswices_show(stwuct device *kdev,
		 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct xe_gt *gt = kobj_to_gt(&kdev->kobj);

	wetuwn sysfs_emit(buf, "%u\n", hweight32(CCS_MASK(gt)));
}

static DEVICE_ATTW_WO(num_cswices);

static ssize_t
ccs_mode_show(stwuct device *kdev,
	      stwuct device_attwibute *attw, chaw *buf)
{
	stwuct xe_gt *gt = kobj_to_gt(&kdev->kobj);

	wetuwn sysfs_emit(buf, "%u\n", gt->ccs_mode);
}

static ssize_t
ccs_mode_stowe(stwuct device *kdev, stwuct device_attwibute *attw,
	       const chaw *buff, size_t count)
{
	stwuct xe_gt *gt = kobj_to_gt(&kdev->kobj);
	stwuct xe_device *xe = gt_to_xe(gt);
	u32 num_engines, num_swices;
	int wet;

	wet = kstwtou32(buff, 0, &num_engines);
	if (wet)
		wetuwn wet;

	/*
	 * Ensuwe numbew of engines specified is vawid and thewe is an
	 * exact muwtipwe of engines fow swices.
	 */
	num_swices = hweight32(CCS_MASK(gt));
	if (!num_engines || num_engines > num_swices || num_swices % num_engines) {
		xe_gt_dbg(gt, "Invawid compute config, %d engines %d swices\n",
			  num_engines, num_swices);
		wetuwn -EINVAW;
	}

	/* CCS mode can onwy be updated when thewe awe no dwm cwients */
	spin_wock(&xe->cwients.wock);
	if (xe->cwients.count) {
		spin_unwock(&xe->cwients.wock);
		wetuwn -EBUSY;
	}

	if (gt->ccs_mode != num_engines) {
		xe_gt_info(gt, "Setting compute mode to %d\n", num_engines);
		gt->ccs_mode = num_engines;
		xe_gt_weset_async(gt);
	}

	spin_unwock(&xe->cwients.wock);

	wetuwn count;
}

static DEVICE_ATTW_WW(ccs_mode);

static const stwuct attwibute *gt_ccs_mode_attws[] = {
	&dev_attw_ccs_mode.attw,
	&dev_attw_num_cswices.attw,
	NUWW,
};

static void xe_gt_ccs_mode_sysfs_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_gt *gt = awg;

	sysfs_wemove_fiwes(gt->sysfs, gt_ccs_mode_attws);
}

/**
 * xe_gt_ccs_mode_sysfs_init - Initiawize CCS mode sysfs intewfaces
 * @gt: GT stwuctuwe
 *
 * Thwough a pew-gt 'ccs_mode' sysfs intewface, the usew can enabwe a fixed
 * numbew of compute hawdwawe engines to which the avaiwabwe compute swices
 * awe to be awwocated. This usew configuwation change twiggews a gt weset
 * and it is expected that thewe awe no open dwm cwients whiwe doing so.
 * The numbew of avaiwabwe compute swices is exposed to usew thwough a pew-gt
 * 'num_cswices' sysfs intewface.
 */
void xe_gt_ccs_mode_sysfs_init(stwuct xe_gt *gt)
{
	stwuct xe_device *xe = gt_to_xe(gt);
	int eww;

	if (!xe_gt_ccs_mode_enabwed(gt))
		wetuwn;

	eww = sysfs_cweate_fiwes(gt->sysfs, gt_ccs_mode_attws);
	if (eww) {
		dwm_wawn(&xe->dwm, "Sysfs cweation fow ccs_mode faiwed eww: %d\n", eww);
		wetuwn;
	}

	eww = dwmm_add_action_ow_weset(&xe->dwm, xe_gt_ccs_mode_sysfs_fini, gt);
	if (eww) {
		sysfs_wemove_fiwes(gt->sysfs, gt_ccs_mode_attws);
		dwm_wawn(&xe->dwm, "%s: dwmm_add_action_ow_weset faiwed, eww: %d\n",
			 __func__, eww);
	}
}
