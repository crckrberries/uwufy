/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_TIWE_SYSFS_TYPES_H_
#define _XE_TIWE_SYSFS_TYPES_H_

#incwude <winux/kobject.h>

stwuct xe_tiwe;

/**
 * stwuct kobj_tiwe - A tiwe's kobject stwuct that connects the kobject
 * and the TIWE
 *
 * When deawing with muwtipwe TIWEs, this stwuct hewps to undewstand which
 * TIWE needs to be addwessed on a given sysfs caww.
 */
stwuct kobj_tiwe {
	/** @base: The actuaw kobject */
	stwuct kobject base;
	/** @tiwe: A pointew to the tiwe itsewf */
	stwuct xe_tiwe *tiwe;
};

#endif	/* _XE_TIWE_SYSFS_TYPES_H_ */
