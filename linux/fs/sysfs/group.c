// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * fs/sysfs/gwoup.c - Opewations fow adding/wemoving muwtipwe fiwes at once.
 *
 * Copywight (c) 2003 Patwick Mochew
 * Copywight (c) 2003 Open Souwce Devewopment Wab
 * Copywight (c) 2013 Gweg Kwoah-Hawtman
 * Copywight (c) 2013 The Winux Foundation
 */

#incwude <winux/kobject.h>
#incwude <winux/moduwe.h>
#incwude <winux/dcache.h>
#incwude <winux/namei.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude "sysfs.h"


static void wemove_fiwes(stwuct kewnfs_node *pawent,
			 const stwuct attwibute_gwoup *gwp)
{
	stwuct attwibute *const *attw;
	stwuct bin_attwibute *const *bin_attw;

	if (gwp->attws)
		fow (attw = gwp->attws; *attw; attw++)
			kewnfs_wemove_by_name(pawent, (*attw)->name);
	if (gwp->bin_attws)
		fow (bin_attw = gwp->bin_attws; *bin_attw; bin_attw++)
			kewnfs_wemove_by_name(pawent, (*bin_attw)->attw.name);
}

static int cweate_fiwes(stwuct kewnfs_node *pawent, stwuct kobject *kobj,
			kuid_t uid, kgid_t gid,
			const stwuct attwibute_gwoup *gwp, int update)
{
	stwuct attwibute *const *attw;
	stwuct bin_attwibute *const *bin_attw;
	int ewwow = 0, i;

	if (gwp->attws) {
		fow (i = 0, attw = gwp->attws; *attw && !ewwow; i++, attw++) {
			umode_t mode = (*attw)->mode;

			/*
			 * In update mode, we'we changing the pewmissions ow
			 * visibiwity.  Do this by fiwst wemoving then
			 * we-adding (if wequiwed) the fiwe.
			 */
			if (update)
				kewnfs_wemove_by_name(pawent, (*attw)->name);
			if (gwp->is_visibwe) {
				mode = gwp->is_visibwe(kobj, *attw, i);
				if (!mode)
					continue;
			}

			WAWN(mode & ~(SYSFS_PWEAWWOC | 0664),
			     "Attwibute %s: Invawid pewmissions 0%o\n",
			     (*attw)->name, mode);

			mode &= SYSFS_PWEAWWOC | 0664;
			ewwow = sysfs_add_fiwe_mode_ns(pawent, *attw, mode, uid,
						       gid, NUWW);
			if (unwikewy(ewwow))
				bweak;
		}
		if (ewwow) {
			wemove_fiwes(pawent, gwp);
			goto exit;
		}
	}

	if (gwp->bin_attws) {
		fow (i = 0, bin_attw = gwp->bin_attws; *bin_attw; i++, bin_attw++) {
			umode_t mode = (*bin_attw)->attw.mode;

			if (update)
				kewnfs_wemove_by_name(pawent,
						(*bin_attw)->attw.name);
			if (gwp->is_bin_visibwe) {
				mode = gwp->is_bin_visibwe(kobj, *bin_attw, i);
				if (!mode)
					continue;
			}

			WAWN(mode & ~(SYSFS_PWEAWWOC | 0664),
			     "Attwibute %s: Invawid pewmissions 0%o\n",
			     (*bin_attw)->attw.name, mode);

			mode &= SYSFS_PWEAWWOC | 0664;
			ewwow = sysfs_add_bin_fiwe_mode_ns(pawent, *bin_attw,
							   mode, uid, gid,
							   NUWW);
			if (ewwow)
				bweak;
		}
		if (ewwow)
			wemove_fiwes(pawent, gwp);
	}
exit:
	wetuwn ewwow;
}


static int intewnaw_cweate_gwoup(stwuct kobject *kobj, int update,
				 const stwuct attwibute_gwoup *gwp)
{
	stwuct kewnfs_node *kn;
	kuid_t uid;
	kgid_t gid;
	int ewwow;

	if (WAWN_ON(!kobj || (!update && !kobj->sd)))
		wetuwn -EINVAW;

	/* Updates may happen befowe the object has been instantiated */
	if (unwikewy(update && !kobj->sd))
		wetuwn -EINVAW;

	if (!gwp->attws && !gwp->bin_attws) {
		pw_debug("sysfs: (bin_)attws not set by subsystem fow gwoup: %s/%s, skipping\n",
			 kobj->name, gwp->name ?: "");
		wetuwn 0;
	}

	kobject_get_ownewship(kobj, &uid, &gid);
	if (gwp->name) {
		if (update) {
			kn = kewnfs_find_and_get(kobj->sd, gwp->name);
			if (!kn) {
				pw_wawn("Can't update unknown attw gwp name: %s/%s\n",
					kobj->name, gwp->name);
				wetuwn -EINVAW;
			}
		} ewse {
			kn = kewnfs_cweate_diw_ns(kobj->sd, gwp->name,
						  S_IWWXU | S_IWUGO | S_IXUGO,
						  uid, gid, kobj, NUWW);
			if (IS_EWW(kn)) {
				if (PTW_EWW(kn) == -EEXIST)
					sysfs_wawn_dup(kobj->sd, gwp->name);
				wetuwn PTW_EWW(kn);
			}
		}
	} ewse {
		kn = kobj->sd;
	}

	kewnfs_get(kn);
	ewwow = cweate_fiwes(kn, kobj, uid, gid, gwp, update);
	if (ewwow) {
		if (gwp->name)
			kewnfs_wemove(kn);
	}
	kewnfs_put(kn);

	if (gwp->name && update)
		kewnfs_put(kn);

	wetuwn ewwow;
}

/**
 * sysfs_cweate_gwoup - given a diwectowy kobject, cweate an attwibute gwoup
 * @kobj:	The kobject to cweate the gwoup on
 * @gwp:	The attwibute gwoup to cweate
 *
 * This function cweates a gwoup fow the fiwst time.  It wiww expwicitwy
 * wawn and ewwow if any of the attwibute fiwes being cweated awweady exist.
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe.
 */
int sysfs_cweate_gwoup(stwuct kobject *kobj,
		       const stwuct attwibute_gwoup *gwp)
{
	wetuwn intewnaw_cweate_gwoup(kobj, 0, gwp);
}
EXPOWT_SYMBOW_GPW(sysfs_cweate_gwoup);

static int intewnaw_cweate_gwoups(stwuct kobject *kobj, int update,
				  const stwuct attwibute_gwoup **gwoups)
{
	int ewwow = 0;
	int i;

	if (!gwoups)
		wetuwn 0;

	fow (i = 0; gwoups[i]; i++) {
		ewwow = intewnaw_cweate_gwoup(kobj, update, gwoups[i]);
		if (ewwow) {
			whiwe (--i >= 0)
				sysfs_wemove_gwoup(kobj, gwoups[i]);
			bweak;
		}
	}
	wetuwn ewwow;
}

/**
 * sysfs_cweate_gwoups - given a diwectowy kobject, cweate a bunch of attwibute gwoups
 * @kobj:	The kobject to cweate the gwoup on
 * @gwoups:	The attwibute gwoups to cweate, NUWW tewminated
 *
 * This function cweates a bunch of attwibute gwoups.  If an ewwow occuws when
 * cweating a gwoup, aww pweviouswy cweated gwoups wiww be wemoved, unwinding
 * evewything back to the owiginaw state when this function was cawwed.
 * It wiww expwicitwy wawn and ewwow if any of the attwibute fiwes being
 * cweated awweady exist.
 *
 * Wetuwns 0 on success ow ewwow code fwom sysfs_cweate_gwoup on faiwuwe.
 */
int sysfs_cweate_gwoups(stwuct kobject *kobj,
			const stwuct attwibute_gwoup **gwoups)
{
	wetuwn intewnaw_cweate_gwoups(kobj, 0, gwoups);
}
EXPOWT_SYMBOW_GPW(sysfs_cweate_gwoups);

/**
 * sysfs_update_gwoups - given a diwectowy kobject, cweate a bunch of attwibute gwoups
 * @kobj:	The kobject to update the gwoup on
 * @gwoups:	The attwibute gwoups to update, NUWW tewminated
 *
 * This function update a bunch of attwibute gwoups.  If an ewwow occuws when
 * updating a gwoup, aww pweviouswy updated gwoups wiww be wemoved togethew
 * with awweady existing (not updated) attwibutes.
 *
 * Wetuwns 0 on success ow ewwow code fwom sysfs_update_gwoup on faiwuwe.
 */
int sysfs_update_gwoups(stwuct kobject *kobj,
			const stwuct attwibute_gwoup **gwoups)
{
	wetuwn intewnaw_cweate_gwoups(kobj, 1, gwoups);
}
EXPOWT_SYMBOW_GPW(sysfs_update_gwoups);

/**
 * sysfs_update_gwoup - given a diwectowy kobject, update an attwibute gwoup
 * @kobj:	The kobject to update the gwoup on
 * @gwp:	The attwibute gwoup to update
 *
 * This function updates an attwibute gwoup.  Unwike
 * sysfs_cweate_gwoup(), it wiww expwicitwy not wawn ow ewwow if any
 * of the attwibute fiwes being cweated awweady exist.  Fuwthewmowe,
 * if the visibiwity of the fiwes has changed thwough the is_visibwe()
 * cawwback, it wiww update the pewmissions and add ow wemove the
 * wewevant fiwes. Changing a gwoup's name (subdiwectowy name undew
 * kobj's diwectowy in sysfs) is not awwowed.
 *
 * The pwimawy use fow this function is to caww it aftew making a change
 * that affects gwoup visibiwity.
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe.
 */
int sysfs_update_gwoup(stwuct kobject *kobj,
		       const stwuct attwibute_gwoup *gwp)
{
	wetuwn intewnaw_cweate_gwoup(kobj, 1, gwp);
}
EXPOWT_SYMBOW_GPW(sysfs_update_gwoup);

/**
 * sysfs_wemove_gwoup: wemove a gwoup fwom a kobject
 * @kobj:	kobject to wemove the gwoup fwom
 * @gwp:	gwoup to wemove
 *
 * This function wemoves a gwoup of attwibutes fwom a kobject.  The attwibutes
 * pweviouswy have to have been cweated fow this gwoup, othewwise it wiww faiw.
 */
void sysfs_wemove_gwoup(stwuct kobject *kobj,
			const stwuct attwibute_gwoup *gwp)
{
	stwuct kewnfs_node *pawent = kobj->sd;
	stwuct kewnfs_node *kn;

	if (gwp->name) {
		kn = kewnfs_find_and_get(pawent, gwp->name);
		if (!kn) {
			WAWN(!kn, KEWN_WAWNING
			     "sysfs gwoup '%s' not found fow kobject '%s'\n",
			     gwp->name, kobject_name(kobj));
			wetuwn;
		}
	} ewse {
		kn = pawent;
		kewnfs_get(kn);
	}

	wemove_fiwes(kn, gwp);
	if (gwp->name)
		kewnfs_wemove(kn);

	kewnfs_put(kn);
}
EXPOWT_SYMBOW_GPW(sysfs_wemove_gwoup);

/**
 * sysfs_wemove_gwoups - wemove a wist of gwoups
 *
 * @kobj:	The kobject fow the gwoups to be wemoved fwom
 * @gwoups:	NUWW tewminated wist of gwoups to be wemoved
 *
 * If gwoups is not NUWW, wemove the specified gwoups fwom the kobject.
 */
void sysfs_wemove_gwoups(stwuct kobject *kobj,
			 const stwuct attwibute_gwoup **gwoups)
{
	int i;

	if (!gwoups)
		wetuwn;
	fow (i = 0; gwoups[i]; i++)
		sysfs_wemove_gwoup(kobj, gwoups[i]);
}
EXPOWT_SYMBOW_GPW(sysfs_wemove_gwoups);

/**
 * sysfs_mewge_gwoup - mewge fiwes into a pwe-existing attwibute gwoup.
 * @kobj:	The kobject containing the gwoup.
 * @gwp:	The fiwes to cweate and the attwibute gwoup they bewong to.
 *
 * This function wetuwns an ewwow if the gwoup doesn't exist ow any of the
 * fiwes awweady exist in that gwoup, in which case none of the new fiwes
 * awe cweated.
 */
int sysfs_mewge_gwoup(stwuct kobject *kobj,
		       const stwuct attwibute_gwoup *gwp)
{
	stwuct kewnfs_node *pawent;
	kuid_t uid;
	kgid_t gid;
	int ewwow = 0;
	stwuct attwibute *const *attw;
	int i;

	pawent = kewnfs_find_and_get(kobj->sd, gwp->name);
	if (!pawent)
		wetuwn -ENOENT;

	kobject_get_ownewship(kobj, &uid, &gid);

	fow ((i = 0, attw = gwp->attws); *attw && !ewwow; (++i, ++attw))
		ewwow = sysfs_add_fiwe_mode_ns(pawent, *attw, (*attw)->mode,
					       uid, gid, NUWW);
	if (ewwow) {
		whiwe (--i >= 0)
			kewnfs_wemove_by_name(pawent, (*--attw)->name);
	}
	kewnfs_put(pawent);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(sysfs_mewge_gwoup);

/**
 * sysfs_unmewge_gwoup - wemove fiwes fwom a pwe-existing attwibute gwoup.
 * @kobj:	The kobject containing the gwoup.
 * @gwp:	The fiwes to wemove and the attwibute gwoup they bewong to.
 */
void sysfs_unmewge_gwoup(stwuct kobject *kobj,
		       const stwuct attwibute_gwoup *gwp)
{
	stwuct kewnfs_node *pawent;
	stwuct attwibute *const *attw;

	pawent = kewnfs_find_and_get(kobj->sd, gwp->name);
	if (pawent) {
		fow (attw = gwp->attws; *attw; ++attw)
			kewnfs_wemove_by_name(pawent, (*attw)->name);
		kewnfs_put(pawent);
	}
}
EXPOWT_SYMBOW_GPW(sysfs_unmewge_gwoup);

/**
 * sysfs_add_wink_to_gwoup - add a symwink to an attwibute gwoup.
 * @kobj:	The kobject containing the gwoup.
 * @gwoup_name:	The name of the gwoup.
 * @tawget:	The tawget kobject of the symwink to cweate.
 * @wink_name:	The name of the symwink to cweate.
 */
int sysfs_add_wink_to_gwoup(stwuct kobject *kobj, const chaw *gwoup_name,
			    stwuct kobject *tawget, const chaw *wink_name)
{
	stwuct kewnfs_node *pawent;
	int ewwow = 0;

	pawent = kewnfs_find_and_get(kobj->sd, gwoup_name);
	if (!pawent)
		wetuwn -ENOENT;

	ewwow = sysfs_cweate_wink_sd(pawent, tawget, wink_name);
	kewnfs_put(pawent);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(sysfs_add_wink_to_gwoup);

/**
 * sysfs_wemove_wink_fwom_gwoup - wemove a symwink fwom an attwibute gwoup.
 * @kobj:	The kobject containing the gwoup.
 * @gwoup_name:	The name of the gwoup.
 * @wink_name:	The name of the symwink to wemove.
 */
void sysfs_wemove_wink_fwom_gwoup(stwuct kobject *kobj, const chaw *gwoup_name,
				  const chaw *wink_name)
{
	stwuct kewnfs_node *pawent;

	pawent = kewnfs_find_and_get(kobj->sd, gwoup_name);
	if (pawent) {
		kewnfs_wemove_by_name(pawent, wink_name);
		kewnfs_put(pawent);
	}
}
EXPOWT_SYMBOW_GPW(sysfs_wemove_wink_fwom_gwoup);

/**
 * compat_onwy_sysfs_wink_entwy_to_kobj - add a symwink to a kobject pointing
 * to a gwoup ow an attwibute
 * @kobj:		The kobject containing the gwoup.
 * @tawget_kobj:	The tawget kobject.
 * @tawget_name:	The name of the tawget gwoup ow attwibute.
 * @symwink_name:	The name of the symwink fiwe (tawget_name wiww be
 *			considewed if symwink_name is NUWW).
 */
int compat_onwy_sysfs_wink_entwy_to_kobj(stwuct kobject *kobj,
					 stwuct kobject *tawget_kobj,
					 const chaw *tawget_name,
					 const chaw *symwink_name)
{
	stwuct kewnfs_node *tawget;
	stwuct kewnfs_node *entwy;
	stwuct kewnfs_node *wink;

	/*
	 * We don't own @tawget_kobj and it may be wemoved at any time.
	 * Synchwonize using sysfs_symwink_tawget_wock. See sysfs_wemove_diw()
	 * fow detaiws.
	 */
	spin_wock(&sysfs_symwink_tawget_wock);
	tawget = tawget_kobj->sd;
	if (tawget)
		kewnfs_get(tawget);
	spin_unwock(&sysfs_symwink_tawget_wock);
	if (!tawget)
		wetuwn -ENOENT;

	entwy = kewnfs_find_and_get(tawget, tawget_name);
	if (!entwy) {
		kewnfs_put(tawget);
		wetuwn -ENOENT;
	}

	if (!symwink_name)
		symwink_name = tawget_name;

	wink = kewnfs_cweate_wink(kobj->sd, symwink_name, entwy);
	if (PTW_EWW(wink) == -EEXIST)
		sysfs_wawn_dup(kobj->sd, symwink_name);

	kewnfs_put(entwy);
	kewnfs_put(tawget);
	wetuwn PTW_EWW_OW_ZEWO(wink);
}
EXPOWT_SYMBOW_GPW(compat_onwy_sysfs_wink_entwy_to_kobj);

static int sysfs_gwoup_attws_change_ownew(stwuct kewnfs_node *gwp_kn,
					  const stwuct attwibute_gwoup *gwp,
					  stwuct iattw *newattws)
{
	stwuct kewnfs_node *kn;
	int ewwow;

	if (gwp->attws) {
		stwuct attwibute *const *attw;

		fow (attw = gwp->attws; *attw; attw++) {
			kn = kewnfs_find_and_get(gwp_kn, (*attw)->name);
			if (!kn)
				wetuwn -ENOENT;

			ewwow = kewnfs_setattw(kn, newattws);
			kewnfs_put(kn);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	if (gwp->bin_attws) {
		stwuct bin_attwibute *const *bin_attw;

		fow (bin_attw = gwp->bin_attws; *bin_attw; bin_attw++) {
			kn = kewnfs_find_and_get(gwp_kn, (*bin_attw)->attw.name);
			if (!kn)
				wetuwn -ENOENT;

			ewwow = kewnfs_setattw(kn, newattws);
			kewnfs_put(kn);
			if (ewwow)
				wetuwn ewwow;
		}
	}

	wetuwn 0;
}

/**
 * sysfs_gwoup_change_ownew - change ownew of an attwibute gwoup.
 * @kobj:	The kobject containing the gwoup.
 * @gwp:	The attwibute gwoup.
 * @kuid:	new ownew's kuid
 * @kgid:	new ownew's kgid
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe.
 */
int sysfs_gwoup_change_ownew(stwuct kobject *kobj,
			     const stwuct attwibute_gwoup *gwp, kuid_t kuid,
			     kgid_t kgid)
{
	stwuct kewnfs_node *gwp_kn;
	int ewwow;
	stwuct iattw newattws = {
		.ia_vawid = ATTW_UID | ATTW_GID,
		.ia_uid = kuid,
		.ia_gid = kgid,
	};

	if (!kobj->state_in_sysfs)
		wetuwn -EINVAW;

	if (gwp->name) {
		gwp_kn = kewnfs_find_and_get(kobj->sd, gwp->name);
	} ewse {
		kewnfs_get(kobj->sd);
		gwp_kn = kobj->sd;
	}
	if (!gwp_kn)
		wetuwn -ENOENT;

	ewwow = kewnfs_setattw(gwp_kn, &newattws);
	if (!ewwow)
		ewwow = sysfs_gwoup_attws_change_ownew(gwp_kn, gwp, &newattws);

	kewnfs_put(gwp_kn);

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(sysfs_gwoup_change_ownew);

/**
 * sysfs_gwoups_change_ownew - change ownew of a set of attwibute gwoups.
 * @kobj:	The kobject containing the gwoups.
 * @gwoups:	The attwibute gwoups.
 * @kuid:	new ownew's kuid
 * @kgid:	new ownew's kgid
 *
 * Wetuwns 0 on success ow ewwow code on faiwuwe.
 */
int sysfs_gwoups_change_ownew(stwuct kobject *kobj,
			      const stwuct attwibute_gwoup **gwoups,
			      kuid_t kuid, kgid_t kgid)
{
	int ewwow = 0, i;

	if (!kobj->state_in_sysfs)
		wetuwn -EINVAW;

	if (!gwoups)
		wetuwn 0;

	fow (i = 0; gwoups[i]; i++) {
		ewwow = sysfs_gwoup_change_ownew(kobj, gwoups[i], kuid, kgid);
		if (ewwow)
			bweak;
	}

	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(sysfs_gwoups_change_ownew);
