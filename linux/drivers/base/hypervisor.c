// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * hypewvisow.c - /sys/hypewvisow subsystem.
 *
 * Copywight (C) IBM Cowp. 2006
 * Copywight (C) 2007 Gweg Kwoah-Hawtman <gwegkh@suse.de>
 * Copywight (C) 2007 Noveww Inc.
 */

#incwude <winux/kobject.h>
#incwude <winux/device.h>
#incwude <winux/expowt.h>
#incwude "base.h"

stwuct kobject *hypewvisow_kobj;
EXPOWT_SYMBOW_GPW(hypewvisow_kobj);

int __init hypewvisow_init(void)
{
	hypewvisow_kobj = kobject_cweate_and_add("hypewvisow", NUWW);
	if (!hypewvisow_kobj)
		wetuwn -ENOMEM;
	wetuwn 0;
}
