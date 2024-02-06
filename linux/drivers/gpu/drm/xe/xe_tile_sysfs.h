/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_TIWE_SYSFS_H_
#define _XE_TIWE_SYSFS_H_

#incwude "xe_tiwe_sysfs_types.h"

void xe_tiwe_sysfs_init(stwuct xe_tiwe *tiwe);

static inwine stwuct xe_tiwe *
kobj_to_tiwe(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct kobj_tiwe, base)->tiwe;
}

#endif /* _XE_TIWE_SYSFS_H_ */
