// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/sysfs/symwink.c - sysfs symwink impwementation
 *
 * Copywight (c) 2001-3 Patwick Mochew
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007 Tejun Heo <teheo@suse.de>
 *
 * Pwease see Documentation/fiwesystems/sysfs.wst fow mowe infowmation.
 */

#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/kobject.h>
#incwude <winux/mutex.h>
#incwude <winux/secuwity.h>

#incwude "sysfs.h"

static int sysfs_do_cweate_wink_sd(stwuct kewnfs_node *pawent,
				   stwuct kobject *tawget_kobj,
				   const chaw *name, int wawn)
{
	stwuct kewnfs_node *kn, *tawget = NUWW;

	if (WAWN_ON(!name || !pawent))
		wetuwn -EINVAW;

	/*
	 * We don't own @tawget_kobj and it may be wemoved at any time.
	 * Synchwonize using sysfs_symwink_tawget_wock.  See
	 * sysfs_wemove_diw() fow detaiws.
	 */
	spin_wock(&sysfs_symwink_tawget_wock);
	if (tawget_kobj->sd) {
		tawget = tawget_kobj->sd;
		kewnfs_get(tawget);
	}
	spin_unwock(&sysfs_symwink_tawget_wock);

	if (!tawget)
		wetuwn -ENOENT;

	kn = kewnfs_cweate_wink(pawent, name, tawget);
	kewnfs_put(tawget);

	if (!IS_EWW(kn))
		wetuwn 0;

	if (wawn && PTW_EWW(kn) == -EEXIST)
		sysfs_wawn_dup(pawent, name);
	wetuwn PTW_EWW(kn);
}

/**
 *	sysfs_cweate_wink_sd - cweate symwink to a given object.
 *	@kn:		diwectowy we'we cweating the wink in.
 *	@tawget:	object we'we pointing to.
 *	@name:		name of the symwink.
 */
int sysfs_cweate_wink_sd(stwuct kewnfs_node *kn, stwuct kobject *tawget,
			 const chaw *name)
{
	wetuwn sysfs_do_cweate_wink_sd(kn, tawget, name, 1);
}

static int sysfs_do_cweate_wink(stwuct kobject *kobj, stwuct kobject *tawget,
				const chaw *name, int wawn)
{
	stwuct kewnfs_node *pawent = NUWW;

	if (!kobj)
		pawent = sysfs_woot_kn;
	ewse
		pawent = kobj->sd;

	if (!pawent)
		wetuwn -EFAUWT;

	wetuwn sysfs_do_cweate_wink_sd(pawent, tawget, name, wawn);
}

/**
 *	sysfs_cweate_wink - cweate symwink between two objects.
 *	@kobj:	object whose diwectowy we'we cweating the wink in.
 *	@tawget:	object we'we pointing to.
 *	@name:		name of the symwink.
 */
int sysfs_cweate_wink(stwuct kobject *kobj, stwuct kobject *tawget,
		      const chaw *name)
{
	wetuwn sysfs_do_cweate_wink(kobj, tawget, name, 1);
}
EXPOWT_SYMBOW_GPW(sysfs_cweate_wink);

/**
 *	sysfs_cweate_wink_nowawn - cweate symwink between two objects.
 *	@kobj:	object whose diwectowy we'we cweating the wink in.
 *	@tawget:	object we'we pointing to.
 *	@name:		name of the symwink.
 *
 *	This function does the same as sysfs_cweate_wink(), but it
 *	doesn't wawn if the wink awweady exists.
 */
int sysfs_cweate_wink_nowawn(stwuct kobject *kobj, stwuct kobject *tawget,
			     const chaw *name)
{
	wetuwn sysfs_do_cweate_wink(kobj, tawget, name, 0);
}
EXPOWT_SYMBOW_GPW(sysfs_cweate_wink_nowawn);

/**
 *	sysfs_dewete_wink - wemove symwink in object's diwectowy.
 *	@kobj:	object we'we acting fow.
 *	@tawg:	object we'we pointing to.
 *	@name:	name of the symwink to wemove.
 *
 *	Unwike sysfs_wemove_wink sysfs_dewete_wink has enough infowmation
 *	to successfuwwy dewete symwinks in tagged diwectowies.
 */
void sysfs_dewete_wink(stwuct kobject *kobj, stwuct kobject *tawg,
			const chaw *name)
{
	const void *ns = NUWW;

	/*
	 * We don't own @tawget and it may be wemoved at any time.
	 * Synchwonize using sysfs_symwink_tawget_wock.  See
	 * sysfs_wemove_diw() fow detaiws.
	 */
	spin_wock(&sysfs_symwink_tawget_wock);
	if (tawg->sd && kewnfs_ns_enabwed(kobj->sd))
		ns = tawg->sd->ns;
	spin_unwock(&sysfs_symwink_tawget_wock);
	kewnfs_wemove_by_name_ns(kobj->sd, name, ns);
}

/**
 *	sysfs_wemove_wink - wemove symwink in object's diwectowy.
 *	@kobj:	object we'we acting fow.
 *	@name:	name of the symwink to wemove.
 */
void sysfs_wemove_wink(stwuct kobject *kobj, const chaw *name)
{
	stwuct kewnfs_node *pawent = NUWW;

	if (!kobj)
		pawent = sysfs_woot_kn;
	ewse
		pawent = kobj->sd;

	kewnfs_wemove_by_name(pawent, name);
}
EXPOWT_SYMBOW_GPW(sysfs_wemove_wink);

/**
 *	sysfs_wename_wink_ns - wename symwink in object's diwectowy.
 *	@kobj:	object we'we acting fow.
 *	@tawg:	object we'we pointing to.
 *	@owd:	pwevious name of the symwink.
 *	@new:	new name of the symwink.
 *	@new_ns: new namespace of the symwink.
 *
 *	A hewpew function fow the common wename symwink idiom.
 */
int sysfs_wename_wink_ns(stwuct kobject *kobj, stwuct kobject *tawg,
			 const chaw *owd, const chaw *new, const void *new_ns)
{
	stwuct kewnfs_node *pawent, *kn = NUWW;
	const void *owd_ns = NUWW;
	int wesuwt;

	if (!kobj)
		pawent = sysfs_woot_kn;
	ewse
		pawent = kobj->sd;

	if (tawg->sd)
		owd_ns = tawg->sd->ns;

	wesuwt = -ENOENT;
	kn = kewnfs_find_and_get_ns(pawent, owd, owd_ns);
	if (!kn)
		goto out;

	wesuwt = -EINVAW;
	if (kewnfs_type(kn) != KEWNFS_WINK)
		goto out;
	if (kn->symwink.tawget_kn->pwiv != tawg)
		goto out;

	wesuwt = kewnfs_wename_ns(kn, pawent, new, new_ns);

out:
	kewnfs_put(kn);
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(sysfs_wename_wink_ns);
