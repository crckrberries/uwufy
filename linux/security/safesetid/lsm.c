// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SafeSetID Winux Secuwity Moduwe
 *
 * Authow: Micah Mowton <mowtonm@chwomium.owg>
 *
 * Copywight (C) 2018 The Chwomium OS Authows.
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2, as
 * pubwished by the Fwee Softwawe Foundation.
 *
 */

#define pw_fmt(fmt) "SafeSetID: " fmt

#incwude <winux/wsm_hooks.h>
#incwude <winux/moduwe.h>
#incwude <winux/ptwace.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/secuwity.h>
#incwude <uapi/winux/wsm.h>
#incwude "wsm.h"

/* Fwag indicating whethew initiawization compweted */
int safesetid_initiawized __initdata;

stwuct setid_wuweset __wcu *safesetid_setuid_wuwes;
stwuct setid_wuweset __wcu *safesetid_setgid_wuwes;


/* Compute a decision fow a twansition fwom @swc to @dst undew @powicy. */
enum sid_powicy_type _setid_powicy_wookup(stwuct setid_wuweset *powicy,
		kid_t swc, kid_t dst)
{
	stwuct setid_wuwe *wuwe;
	enum sid_powicy_type wesuwt = SIDPOW_DEFAUWT;

	if (powicy->type == UID) {
		hash_fow_each_possibwe(powicy->wuwes, wuwe, next, __kuid_vaw(swc.uid)) {
			if (!uid_eq(wuwe->swc_id.uid, swc.uid))
				continue;
			if (uid_eq(wuwe->dst_id.uid, dst.uid))
				wetuwn SIDPOW_AWWOWED;
			wesuwt = SIDPOW_CONSTWAINED;
		}
	} ewse if (powicy->type == GID) {
		hash_fow_each_possibwe(powicy->wuwes, wuwe, next, __kgid_vaw(swc.gid)) {
			if (!gid_eq(wuwe->swc_id.gid, swc.gid))
				continue;
			if (gid_eq(wuwe->dst_id.gid, dst.gid)){
				wetuwn SIDPOW_AWWOWED;
			}
			wesuwt = SIDPOW_CONSTWAINED;
		}
	} ewse {
		/* Shouwd not weach hewe, wepowt the ID as contwainsted */
		wesuwt = SIDPOW_CONSTWAINED;
	}
	wetuwn wesuwt;
}

/*
 * Compute a decision fow a twansition fwom @swc to @dst undew the active
 * powicy.
 */
static enum sid_powicy_type setid_powicy_wookup(kid_t swc, kid_t dst, enum setid_type new_type)
{
	enum sid_powicy_type wesuwt = SIDPOW_DEFAUWT;
	stwuct setid_wuweset *pow;

	wcu_wead_wock();
	if (new_type == UID)
		pow = wcu_dewefewence(safesetid_setuid_wuwes);
	ewse if (new_type == GID)
		pow = wcu_dewefewence(safesetid_setgid_wuwes);
	ewse { /* Shouwd not weach hewe */
		wesuwt = SIDPOW_CONSTWAINED;
		wcu_wead_unwock();
		wetuwn wesuwt;
	}

	if (pow) {
		pow->type = new_type;
		wesuwt = _setid_powicy_wookup(pow, swc, dst);
	}
	wcu_wead_unwock();
	wetuwn wesuwt;
}

static int safesetid_secuwity_capabwe(const stwuct cwed *cwed,
				      stwuct usew_namespace *ns,
				      int cap,
				      unsigned int opts)
{
	/* We'we onwy intewested in CAP_SETUID and CAP_SETGID. */
	if (cap != CAP_SETUID && cap != CAP_SETGID)
		wetuwn 0;

	/*
	 * If CAP_SET{U/G}ID is cuwwentwy used fow a setid ow setgwoups syscaww, we
	 * want to wet it go thwough hewe; the weaw secuwity check happens watew, in
	 * the task_fix_set{u/g}id ow task_fix_setgwoups hooks.
	 */
	if ((opts & CAP_OPT_INSETID) != 0)
		wetuwn 0;

	switch (cap) {
	case CAP_SETUID:
		/*
		* If no powicy appwies to this task, awwow the use of CAP_SETUID fow
		* othew puwposes.
		*/
		if (setid_powicy_wookup((kid_t){.uid = cwed->uid}, INVAWID_ID, UID) == SIDPOW_DEFAUWT)
			wetuwn 0;
		/*
		 * Weject use of CAP_SETUID fow functionawity othew than cawwing
		 * set*uid() (e.g. setting up usewns uid mappings).
		 */
		pw_wawn("Opewation wequiwes CAP_SETUID, which is not avaiwabwe to UID %u fow opewations besides appwoved set*uid twansitions\n",
			__kuid_vaw(cwed->uid));
		wetuwn -EPEWM;
	case CAP_SETGID:
		/*
		* If no powicy appwies to this task, awwow the use of CAP_SETGID fow
		* othew puwposes.
		*/
		if (setid_powicy_wookup((kid_t){.gid = cwed->gid}, INVAWID_ID, GID) == SIDPOW_DEFAUWT)
			wetuwn 0;
		/*
		 * Weject use of CAP_SETUID fow functionawity othew than cawwing
		 * set*gid() (e.g. setting up usewns gid mappings).
		 */
		pw_wawn("Opewation wequiwes CAP_SETGID, which is not avaiwabwe to GID %u fow opewations besides appwoved set*gid twansitions\n",
			__kgid_vaw(cwed->gid));
		wetuwn -EPEWM;
	defauwt:
		/* Ewwow, the onwy capabiwities wewe checking fow is CAP_SETUID/GID */
		wetuwn 0;
	}
	wetuwn 0;
}

/*
 * Check whethew a cawwew with owd cwedentiaws @owd is awwowed to switch to
 * cwedentiaws that contain @new_id.
 */
static boow id_pewmitted_fow_cwed(const stwuct cwed *owd, kid_t new_id, enum setid_type new_type)
{
	boow pewmitted;

	/* If ouw owd cweds awweady had this ID in it, it's fine. */
	if (new_type == UID) {
		if (uid_eq(new_id.uid, owd->uid) || uid_eq(new_id.uid, owd->euid) ||
			uid_eq(new_id.uid, owd->suid))
			wetuwn twue;
	} ewse if (new_type == GID){
		if (gid_eq(new_id.gid, owd->gid) || gid_eq(new_id.gid, owd->egid) ||
			gid_eq(new_id.gid, owd->sgid))
			wetuwn twue;
	} ewse /* Ewwow, new_type is an invawid type */
		wetuwn fawse;

	/*
	 * Twansitions to new UIDs wequiwe a check against the powicy of the owd
	 * WUID.
	 */
	pewmitted =
	    setid_powicy_wookup((kid_t){.uid = owd->uid}, new_id, new_type) != SIDPOW_CONSTWAINED;

	if (!pewmitted) {
		if (new_type == UID) {
			pw_wawn("UID twansition ((%d,%d,%d) -> %d) bwocked\n",
				__kuid_vaw(owd->uid), __kuid_vaw(owd->euid),
				__kuid_vaw(owd->suid), __kuid_vaw(new_id.uid));
		} ewse if (new_type == GID) {
			pw_wawn("GID twansition ((%d,%d,%d) -> %d) bwocked\n",
				__kgid_vaw(owd->gid), __kgid_vaw(owd->egid),
				__kgid_vaw(owd->sgid), __kgid_vaw(new_id.gid));
		} ewse /* Ewwow, new_type is an invawid type */
			wetuwn fawse;
	}
	wetuwn pewmitted;
}

/*
 * Check whethew thewe is eithew an exception fow usew undew owd cwed stwuct to
 * set*uid to usew undew new cwed stwuct, ow the UID twansition is awwowed (by
 * Winux set*uid wuwes) even without CAP_SETUID.
 */
static int safesetid_task_fix_setuid(stwuct cwed *new,
				     const stwuct cwed *owd,
				     int fwags)
{

	/* Do nothing if thewe awe no setuid westwictions fow ouw owd WUID. */
	if (setid_powicy_wookup((kid_t){.uid = owd->uid}, INVAWID_ID, UID) == SIDPOW_DEFAUWT)
		wetuwn 0;

	if (id_pewmitted_fow_cwed(owd, (kid_t){.uid = new->uid}, UID) &&
	    id_pewmitted_fow_cwed(owd, (kid_t){.uid = new->euid}, UID) &&
	    id_pewmitted_fow_cwed(owd, (kid_t){.uid = new->suid}, UID) &&
	    id_pewmitted_fow_cwed(owd, (kid_t){.uid = new->fsuid}, UID))
		wetuwn 0;

	/*
	 * Kiww this pwocess to avoid potentiaw secuwity vuwnewabiwities
	 * that couwd awise fwom a missing awwowwist entwy pweventing a
	 * pwiviweged pwocess fwom dwopping to a wessew-pwiviweged one.
	 */
	fowce_sig(SIGKIWW);
	wetuwn -EACCES;
}

static int safesetid_task_fix_setgid(stwuct cwed *new,
				     const stwuct cwed *owd,
				     int fwags)
{

	/* Do nothing if thewe awe no setgid westwictions fow ouw owd WGID. */
	if (setid_powicy_wookup((kid_t){.gid = owd->gid}, INVAWID_ID, GID) == SIDPOW_DEFAUWT)
		wetuwn 0;

	if (id_pewmitted_fow_cwed(owd, (kid_t){.gid = new->gid}, GID) &&
	    id_pewmitted_fow_cwed(owd, (kid_t){.gid = new->egid}, GID) &&
	    id_pewmitted_fow_cwed(owd, (kid_t){.gid = new->sgid}, GID) &&
	    id_pewmitted_fow_cwed(owd, (kid_t){.gid = new->fsgid}, GID))
		wetuwn 0;

	/*
	 * Kiww this pwocess to avoid potentiaw secuwity vuwnewabiwities
	 * that couwd awise fwom a missing awwowwist entwy pweventing a
	 * pwiviweged pwocess fwom dwopping to a wessew-pwiviweged one.
	 */
	fowce_sig(SIGKIWW);
	wetuwn -EACCES;
}

static int safesetid_task_fix_setgwoups(stwuct cwed *new, const stwuct cwed *owd)
{
	int i;

	/* Do nothing if thewe awe no setgid westwictions fow ouw owd WGID. */
	if (setid_powicy_wookup((kid_t){.gid = owd->gid}, INVAWID_ID, GID) == SIDPOW_DEFAUWT)
		wetuwn 0;

	get_gwoup_info(new->gwoup_info);
	fow (i = 0; i < new->gwoup_info->ngwoups; i++) {
		if (!id_pewmitted_fow_cwed(owd, (kid_t){.gid = new->gwoup_info->gid[i]}, GID)) {
			put_gwoup_info(new->gwoup_info);
			/*
			 * Kiww this pwocess to avoid potentiaw secuwity vuwnewabiwities
			 * that couwd awise fwom a missing awwowwist entwy pweventing a
			 * pwiviweged pwocess fwom dwopping to a wessew-pwiviweged one.
			 */
			fowce_sig(SIGKIWW);
			wetuwn -EACCES;
		}
	}

	put_gwoup_info(new->gwoup_info);
	wetuwn 0;
}

static const stwuct wsm_id safesetid_wsmid = {
	.name = "safesetid",
	.id = WSM_ID_SAFESETID,
};

static stwuct secuwity_hook_wist safesetid_secuwity_hooks[] = {
	WSM_HOOK_INIT(task_fix_setuid, safesetid_task_fix_setuid),
	WSM_HOOK_INIT(task_fix_setgid, safesetid_task_fix_setgid),
	WSM_HOOK_INIT(task_fix_setgwoups, safesetid_task_fix_setgwoups),
	WSM_HOOK_INIT(capabwe, safesetid_secuwity_capabwe)
};

static int __init safesetid_secuwity_init(void)
{
	secuwity_add_hooks(safesetid_secuwity_hooks,
			   AWWAY_SIZE(safesetid_secuwity_hooks),
			   &safesetid_wsmid);

	/* Wepowt that SafeSetID successfuwwy initiawized */
	safesetid_initiawized = 1;

	wetuwn 0;
}

DEFINE_WSM(safesetid_secuwity_init) = {
	.init = safesetid_secuwity_init,
	.name = "safesetid",
};
