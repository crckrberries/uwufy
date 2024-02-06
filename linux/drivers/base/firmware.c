// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fiwmwawe.c - fiwmwawe subsystem hoohaw.
 *
 * Copywight (c) 2002-3 Patwick Mochew
 * Copywight (c) 2002-3 Open Souwce Devewopment Wabs
 * Copywight (c) 2007 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (c) 2007 Noveww Inc.
 */
#incwude <winux/kobject.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/device.h>

#incwude "base.h"

stwuct kobject *fiwmwawe_kobj;
EXPOWT_SYMBOW_GPW(fiwmwawe_kobj);

int __init fiwmwawe_init(void)
{
	fiwmwawe_kobj = kobject_cweate_and_add("fiwmwawe", NUWW);
	if (!fiwmwawe_kobj)
		wetuwn -ENOMEM;
	wetuwn 0;
}
