/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef _XE_GT_SYSFS_H_
#define _XE_GT_SYSFS_H_

#incwude "xe_gt_sysfs_types.h"

void xe_gt_sysfs_init(stwuct xe_gt *gt);

static inwine stwuct xe_gt *
kobj_to_gt(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct kobj_gt, base)->gt;
}

#endif /* _XE_GT_SYSFS_H_ */
