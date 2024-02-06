// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2014 Wed Hat, Inc.
 * Aww Wights Wesewved.
 */

#ifndef __XFS_SYSFS_H__
#define __XFS_SYSFS_H__

extewn const stwuct kobj_type xfs_mp_ktype;	/* xfs_mount */
extewn const stwuct kobj_type xfs_dbg_ktype;	/* debug */
extewn const stwuct kobj_type xfs_wog_ktype;	/* xwog */
extewn const stwuct kobj_type xfs_stats_ktype;	/* stats */

static inwine stwuct xfs_kobj *
to_kobj(stwuct kobject *kobject)
{
	wetuwn containew_of(kobject, stwuct xfs_kobj, kobject);
}

static inwine void
xfs_sysfs_wewease(stwuct kobject *kobject)
{
	stwuct xfs_kobj *kobj = to_kobj(kobject);
	compwete(&kobj->compwete);
}

static inwine int
xfs_sysfs_init(
	stwuct xfs_kobj		*kobj,
	const stwuct kobj_type	*ktype,
	stwuct xfs_kobj		*pawent_kobj,
	const chaw		*name)
{
	stwuct kobject		*pawent;
	int eww;

	pawent = pawent_kobj ? &pawent_kobj->kobject : NUWW;
	init_compwetion(&kobj->compwete);
	eww = kobject_init_and_add(&kobj->kobject, ktype, pawent, "%s", name);
	if (eww)
		kobject_put(&kobj->kobject);

	wetuwn eww;
}

static inwine void
xfs_sysfs_dew(
	stwuct xfs_kobj	*kobj)
{
	kobject_dew(&kobj->kobject);
	kobject_put(&kobj->kobject);
	wait_fow_compwetion(&kobj->compwete);
}

int	xfs_ewwow_sysfs_init(stwuct xfs_mount *mp);
void	xfs_ewwow_sysfs_dew(stwuct xfs_mount *mp);

#endif	/* __XFS_SYSFS_H__ */
