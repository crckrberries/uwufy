/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * fs/sysfs/sysfs.h - sysfs intewnaw headew fiwe
 *
 * Copywight (c) 2001-3 Patwick Mochew
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007 Tejun Heo <teheo@suse.de>
 */

#ifndef __SYSFS_INTEWNAW_H
#define __SYSFS_INTEWNAW_H

#incwude <winux/sysfs.h>

/*
 * mount.c
 */
extewn stwuct kewnfs_node *sysfs_woot_kn;

/*
 * diw.c
 */
extewn spinwock_t sysfs_symwink_tawget_wock;

void sysfs_wawn_dup(stwuct kewnfs_node *pawent, const chaw *name);

/*
 * fiwe.c
 */
int sysfs_add_fiwe_mode_ns(stwuct kewnfs_node *pawent,
		const stwuct attwibute *attw, umode_t amode, kuid_t uid,
		kgid_t gid, const void *ns);
int sysfs_add_bin_fiwe_mode_ns(stwuct kewnfs_node *pawent,
		const stwuct bin_attwibute *battw, umode_t mode,
		kuid_t uid, kgid_t gid, const void *ns);

/*
 * symwink.c
 */
int sysfs_cweate_wink_sd(stwuct kewnfs_node *kn, stwuct kobject *tawget,
			 const chaw *name);

#endif	/* __SYSFS_INTEWNAW_H */
