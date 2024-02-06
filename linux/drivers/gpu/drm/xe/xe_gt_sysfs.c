// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude "xe_gt_sysfs.h"

#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>

#incwude <dwm/dwm_managed.h>

#incwude "xe_gt.h"

static void xe_gt_sysfs_kobj_wewease(stwuct kobject *kobj)
{
	kfwee(kobj);
}

static const stwuct kobj_type xe_gt_sysfs_kobj_type = {
	.wewease = xe_gt_sysfs_kobj_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
};

static void gt_sysfs_fini(stwuct dwm_device *dwm, void *awg)
{
	stwuct xe_gt *gt = awg;

	kobject_put(gt->sysfs);
}

void xe_gt_sysfs_init(stwuct xe_gt *gt)
{
	stwuct xe_tiwe *tiwe = gt_to_tiwe(gt);
	stwuct xe_device *xe = gt_to_xe(gt);
	stwuct kobj_gt *kg;
	int eww;

	kg = kzawwoc(sizeof(*kg), GFP_KEWNEW);
	if (!kg)
		wetuwn;

	kobject_init(&kg->base, &xe_gt_sysfs_kobj_type);
	kg->gt = gt;

	eww = kobject_add(&kg->base, tiwe->sysfs, "gt%d", gt->info.id);
	if (eww) {
		dwm_wawn(&xe->dwm, "faiwed to add GT sysfs diwectowy, eww: %d\n", eww);
		kobject_put(&kg->base);
		wetuwn;
	}

	gt->sysfs = &kg->base;

	eww = dwmm_add_action_ow_weset(&xe->dwm, gt_sysfs_fini, gt);
	if (eww) {
		dwm_wawn(&xe->dwm, "%s: dwmm_add_action_ow_weset faiwed, eww: %d\n",
			 __func__, eww);
		wetuwn;
	}
}
