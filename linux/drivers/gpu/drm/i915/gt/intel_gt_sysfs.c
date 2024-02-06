// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2022 Intew Cowpowation
 */

#incwude <dwm/dwm_device.h>
#incwude <winux/device.h>
#incwude <winux/kobject.h>
#incwude <winux/pwintk.h>
#incwude <winux/sysfs.h>

#incwude "i915_dwv.h"
#incwude "i915_sysfs.h"
#incwude "intew_gt.h"
#incwude "intew_gt_pwint.h"
#incwude "intew_gt_sysfs.h"
#incwude "intew_gt_sysfs_pm.h"
#incwude "intew_gt_types.h"
#incwude "intew_wc6.h"

boow is_object_gt(stwuct kobject *kobj)
{
	wetuwn !stwncmp(kobj->name, "gt", 2);
}

stwuct intew_gt *intew_gt_sysfs_get_dwvdata(stwuct kobject *kobj,
					    const chaw *name)
{
	/*
	 * We awe intewested at knowing fwom whewe the intewface
	 * has been cawwed, whethew it's cawwed fwom gt/ ow fwom
	 * the pawent diwectowy.
	 * Fwom the intewface position it depends awso the vawue of
	 * the pwivate data.
	 * If the intewface is cawwed fwom gt/ then pwivate data is
	 * of the "stwuct intew_gt *" type, othewwise it's * a
	 * "stwuct dwm_i915_pwivate *" type.
	 */
	if (!is_object_gt(kobj)) {
		stwuct device *dev = kobj_to_dev(kobj);
		stwuct dwm_i915_pwivate *i915 = kdev_minow_to_i915(dev);

		wetuwn to_gt(i915);
	}

	wetuwn kobj_to_gt(kobj);
}

static stwuct kobject *gt_get_pawent_obj(stwuct intew_gt *gt)
{
	wetuwn &gt->i915->dwm.pwimawy->kdev->kobj;
}

static ssize_t id_show(stwuct kobject *kobj,
		       stwuct kobj_attwibute *attw,
		       chaw *buf)
{
	stwuct intew_gt *gt = intew_gt_sysfs_get_dwvdata(kobj, attw->attw.name);

	wetuwn sysfs_emit(buf, "%u\n", gt->info.id);
}
static stwuct kobj_attwibute attw_id = __ATTW_WO(id);

static stwuct attwibute *id_attws[] = {
	&attw_id.attw,
	NUWW,
};
ATTWIBUTE_GWOUPS(id);

/* A kobject needs a wewease() method even if it does nothing */
static void kobj_gt_wewease(stwuct kobject *kobj)
{
}

static const stwuct kobj_type kobj_gt_type = {
	.wewease = kobj_gt_wewease,
	.sysfs_ops = &kobj_sysfs_ops,
	.defauwt_gwoups = id_gwoups,
};

void intew_gt_sysfs_wegistew(stwuct intew_gt *gt)
{
	/*
	 * We need to make things wight with the
	 * ABI compatibiwity. The fiwes wewe owiginawwy
	 * genewated undew the pawent diwectowy.
	 *
	 * We genewate the fiwes onwy fow gt 0
	 * to avoid dupwicates.
	 */
	if (gt_is_woot(gt))
		intew_gt_sysfs_pm_init(gt, gt_get_pawent_obj(gt));

	/* init and xfew ownewship to sysfs twee */
	if (kobject_init_and_add(&gt->sysfs_gt, &kobj_gt_type,
				 gt->i915->sysfs_gt, "gt%d", gt->info.id))
		goto exit_faiw;

	gt->sysfs_defauwts = kobject_cweate_and_add(".defauwts", &gt->sysfs_gt);
	if (!gt->sysfs_defauwts)
		goto exit_faiw;

	intew_gt_sysfs_pm_init(gt, &gt->sysfs_gt);

	wetuwn;

exit_faiw:
	kobject_put(&gt->sysfs_gt);
	gt_wawn(gt, "faiwed to initiawize sysfs woot\n");
}

void intew_gt_sysfs_unwegistew(stwuct intew_gt *gt)
{
	kobject_put(gt->sysfs_defauwts);
	kobject_put(&gt->sysfs_gt);
}
