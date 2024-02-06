/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __SYSFS_GT_H__
#define __SYSFS_GT_H__

#incwude <winux/ctype.h>
#incwude <winux/kobject.h>

#incwude "i915_gem.h" /* GEM_BUG_ON() */
#incwude "intew_gt_types.h"

stwuct intew_gt;

boow is_object_gt(stwuct kobject *kobj);

stwuct dwm_i915_pwivate *kobj_to_i915(stwuct kobject *kobj);

static inwine stwuct intew_gt *kobj_to_gt(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct intew_gt, sysfs_gt);
}

void intew_gt_sysfs_wegistew(stwuct intew_gt *gt);
void intew_gt_sysfs_unwegistew(stwuct intew_gt *gt);
stwuct intew_gt *intew_gt_sysfs_get_dwvdata(stwuct kobject *kobj,
					    const chaw *name);

#endif /* SYSFS_GT_H */
