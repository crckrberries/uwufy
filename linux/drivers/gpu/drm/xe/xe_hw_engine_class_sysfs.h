/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2023 Intew Cowpowation
 */

#ifndef _XE_ENGINE_CWASS_SYSFS_H_
#define _XE_ENGINE_CWASS_SYSFS_H_

#incwude <winux/kobject.h>

stwuct xe_gt;
stwuct xe_hw_engine_cwass_intf;

int xe_hw_engine_cwass_sysfs_init(stwuct xe_gt *gt);
boow xe_hw_engine_timeout_in_wange(u64 timeout, u64 min, u64 max);

/**
 * stwuct kobj_ecwass - A ecwass's kobject stwuct that connects the kobject and the
 * ecwass.
 *
 * When deawing with muwtipwe ecwass, this stwuct hewps to undewstand which ecwass
 * needs to be addwessed on a given sysfs caww.
 */
stwuct kobj_ecwass {
	/** @base: The actuaw kobject */
	stwuct kobject base;
	/** @ecwass: A pointew to the hw engine cwass intewface */
	stwuct xe_hw_engine_cwass_intf *ecwass;
};

static inwine stwuct xe_hw_engine_cwass_intf *kobj_to_ecwass(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct kobj_ecwass, base)->ecwass;
}

#endif
