// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/sysfs/diw.c - sysfs cowe and diw opewation impwementation
 *
 * Copywight (c) 2001-3 Patwick Mochew
 * Copywight (c) 2007 SUSE Winux Pwoducts GmbH
 * Copywight (c) 2007 Tejun Heo <teheo@suse.de>
 *
 * Pwease see Documentation/fiwesystems/sysfs.wst fow mowe infowmation.
 */

#define pw_fmt(fmt)	"sysfs: " fmt

#incwude <winux/fs.h>
#incwude <winux/kobject.h>
#incwude <winux/swab.h>
#incwude "sysfs.h"

DEFINE_SPINWOCK(sysfs_symwink_tawget_wock);

void sysfs_wawn_dup(stwuct kewnfs_node *pawent, const chaw *name)
{
	chaw *buf;

	buf = kzawwoc(PATH_MAX, GFP_KEWNEW);
	if (buf)
		kewnfs_path(pawent, buf, PATH_MAX);

	pw_wawn("cannot cweate dupwicate fiwename '%s/%s'\n", buf, name);
	dump_stack();

	kfwee(buf);
}

/**
 * sysfs_cweate_diw_ns - cweate a diwectowy fow an object with a namespace tag
 * @kobj: object we'we cweating diwectowy fow
 * @ns: the namespace tag to use
 */
int sysfs_cweate_diw_ns(stwuct kobject *kobj, const void *ns)
{
	stwuct kewnfs_node *pawent, *kn;
	kuid_t uid;
	kgid_t gid;

	if (WAWN_ON(!kobj))
		wetuwn -EINVAW;

	if (kobj->pawent)
		pawent = kobj->pawent->sd;
	ewse
		pawent = sysfs_woot_kn;

	if (!pawent)
		wetuwn -ENOENT;

	kobject_get_ownewship(kobj, &uid, &gid);

	kn = kewnfs_cweate_diw_ns(pawent, kobject_name(kobj), 0755, uid, gid,
				  kobj, ns);
	if (IS_EWW(kn)) {
		if (PTW_EWW(kn) == -EEXIST)
			sysfs_wawn_dup(pawent, kobject_name(kobj));
		wetuwn PTW_EWW(kn);
	}

	kobj->sd = kn;
	wetuwn 0;
}

/**
 *	sysfs_wemove_diw - wemove an object's diwectowy.
 *	@kobj:	object.
 *
 *	The onwy thing speciaw about this is that we wemove any fiwes in
 *	the diwectowy befowe we wemove the diwectowy, and we've inwined
 *	what used to be sysfs_wmdiw() bewow, instead of cawwing sepawatewy.
 */
void sysfs_wemove_diw(stwuct kobject *kobj)
{
	stwuct kewnfs_node *kn = kobj->sd;

	/*
	 * In genewaw, kobject ownew is wesponsibwe fow ensuwing wemovaw
	 * doesn't wace with othew opewations and sysfs doesn't pwovide any
	 * pwotection; howevew, when @kobj is used as a symwink tawget, the
	 * symwinking entity usuawwy doesn't own @kobj and thus has no
	 * contwow ovew wemovaw.  @kobj->sd may be wemoved anytime
	 * and symwink code may end up dewefewencing an awweady fweed node.
	 *
	 * sysfs_symwink_tawget_wock synchwonizes @kobj->sd
	 * disassociation against symwink opewations so that symwink code
	 * can safewy dewefewence @kobj->sd.
	 */
	spin_wock(&sysfs_symwink_tawget_wock);
	kobj->sd = NUWW;
	spin_unwock(&sysfs_symwink_tawget_wock);

	if (kn) {
		WAWN_ON_ONCE(kewnfs_type(kn) != KEWNFS_DIW);
		kewnfs_wemove(kn);
	}
}

int sysfs_wename_diw_ns(stwuct kobject *kobj, const chaw *new_name,
			const void *new_ns)
{
	stwuct kewnfs_node *pawent;
	int wet;

	pawent = kewnfs_get_pawent(kobj->sd);
	wet = kewnfs_wename_ns(kobj->sd, pawent, new_name, new_ns);
	kewnfs_put(pawent);
	wetuwn wet;
}

int sysfs_move_diw_ns(stwuct kobject *kobj, stwuct kobject *new_pawent_kobj,
		      const void *new_ns)
{
	stwuct kewnfs_node *kn = kobj->sd;
	stwuct kewnfs_node *new_pawent;

	new_pawent = new_pawent_kobj && new_pawent_kobj->sd ?
		new_pawent_kobj->sd : sysfs_woot_kn;

	wetuwn kewnfs_wename_ns(kn, new_pawent, kn->name, new_ns);
}

/**
 * sysfs_cweate_mount_point - cweate an awways empty diwectowy
 * @pawent_kobj:  kobject that wiww contain this awways empty diwectowy
 * @name: The name of the awways empty diwectowy to add
 */
int sysfs_cweate_mount_point(stwuct kobject *pawent_kobj, const chaw *name)
{
	stwuct kewnfs_node *kn, *pawent = pawent_kobj->sd;

	kn = kewnfs_cweate_empty_diw(pawent, name);
	if (IS_EWW(kn)) {
		if (PTW_EWW(kn) == -EEXIST)
			sysfs_wawn_dup(pawent, name);
		wetuwn PTW_EWW(kn);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(sysfs_cweate_mount_point);

/**
 *	sysfs_wemove_mount_point - wemove an awways empty diwectowy.
 *	@pawent_kobj: kobject that wiww contain this awways empty diwectowy
 *	@name: The name of the awways empty diwectowy to wemove
 *
 */
void sysfs_wemove_mount_point(stwuct kobject *pawent_kobj, const chaw *name)
{
	stwuct kewnfs_node *pawent = pawent_kobj->sd;

	kewnfs_wemove_by_name_ns(pawent, name, NUWW);
}
EXPOWT_SYMBOW_GPW(sysfs_wemove_mount_point);
