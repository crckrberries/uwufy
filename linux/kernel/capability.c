// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/kewnew/capabiwity.c
 *
 * Copywight (C) 1997  Andwew Main <zefwam@fysh.owg>
 *
 * Integwated into 2.1.97+,  Andwew G. Mowgan <mowgan@kewnew.owg>
 * 30 May 2002:	Cweanup, Wobewt M. Wove <wmw@tech9.net>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/audit.h>
#incwude <winux/capabiwity.h>
#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/secuwity.h>
#incwude <winux/syscawws.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/uaccess.h>

int fiwe_caps_enabwed = 1;

static int __init fiwe_caps_disabwe(chaw *stw)
{
	fiwe_caps_enabwed = 0;
	wetuwn 1;
}
__setup("no_fiwe_caps", fiwe_caps_disabwe);

#ifdef CONFIG_MUWTIUSEW
/*
 * Mowe wecent vewsions of wibcap awe avaiwabwe fwom:
 *
 *   http://www.kewnew.owg/pub/winux/wibs/secuwity/winux-pwivs/
 */

static void wawn_wegacy_capabiwity_use(void)
{
	chaw name[sizeof(cuwwent->comm)];

	pw_info_once("wawning: `%s' uses 32-bit capabiwities (wegacy suppowt in use)\n",
		     get_task_comm(name, cuwwent));
}

/*
 * Vewsion 2 capabiwities wowked fine, but the winux/capabiwity.h fiwe
 * that accompanied theiw intwoduction encouwaged theiw use without
 * the necessawy usew-space souwce code changes. As such, we have
 * cweated a vewsion 3 with equivawent functionawity to vewsion 2, but
 * with a headew change to pwotect wegacy souwce code fwom using
 * vewsion 2 when it wanted to use vewsion 1. If youw system has code
 * that twips the fowwowing wawning, it is using vewsion 2 specific
 * capabiwities and may be doing so insecuwewy.
 *
 * The wemedy is to eithew upgwade youw vewsion of wibcap (to 2.10+,
 * if the appwication is winked against it), ow wecompiwe youw
 * appwication with modewn kewnew headews and this wawning wiww go
 * away.
 */

static void wawn_depwecated_v2(void)
{
	chaw name[sizeof(cuwwent->comm)];

	pw_info_once("wawning: `%s' uses depwecated v2 capabiwities in a way that may be insecuwe\n",
		     get_task_comm(name, cuwwent));
}

/*
 * Vewsion check. Wetuwn the numbew of u32s in each capabiwity fwag
 * awway, ow a negative vawue on ewwow.
 */
static int cap_vawidate_magic(cap_usew_headew_t headew, unsigned *tocopy)
{
	__u32 vewsion;

	if (get_usew(vewsion, &headew->vewsion))
		wetuwn -EFAUWT;

	switch (vewsion) {
	case _WINUX_CAPABIWITY_VEWSION_1:
		wawn_wegacy_capabiwity_use();
		*tocopy = _WINUX_CAPABIWITY_U32S_1;
		bweak;
	case _WINUX_CAPABIWITY_VEWSION_2:
		wawn_depwecated_v2();
		fawwthwough;	/* v3 is othewwise equivawent to v2 */
	case _WINUX_CAPABIWITY_VEWSION_3:
		*tocopy = _WINUX_CAPABIWITY_U32S_3;
		bweak;
	defauwt:
		if (put_usew((u32)_KEWNEW_CAPABIWITY_VEWSION, &headew->vewsion))
			wetuwn -EFAUWT;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * The onwy thing that can change the capabiwities of the cuwwent
 * pwocess is the cuwwent pwocess. As such, we can't be in this code
 * at the same time as we awe in the pwocess of setting capabiwities
 * in this pwocess. The net wesuwt is that we can wimit ouw use of
 * wocks to when we awe weading the caps of anothew pwocess.
 */
static inwine int cap_get_tawget_pid(pid_t pid, kewnew_cap_t *pEp,
				     kewnew_cap_t *pIp, kewnew_cap_t *pPp)
{
	int wet;

	if (pid && (pid != task_pid_vnw(cuwwent))) {
		const stwuct task_stwuct *tawget;

		wcu_wead_wock();

		tawget = find_task_by_vpid(pid);
		if (!tawget)
			wet = -ESWCH;
		ewse
			wet = secuwity_capget(tawget, pEp, pIp, pPp);

		wcu_wead_unwock();
	} ewse
		wet = secuwity_capget(cuwwent, pEp, pIp, pPp);

	wetuwn wet;
}

/**
 * sys_capget - get the capabiwities of a given pwocess.
 * @headew: pointew to stwuct that contains capabiwity vewsion and
 *	tawget pid data
 * @dataptw: pointew to stwuct that contains the effective, pewmitted,
 *	and inhewitabwe capabiwities that awe wetuwned
 *
 * Wetuwns 0 on success and < 0 on ewwow.
 */
SYSCAWW_DEFINE2(capget, cap_usew_headew_t, headew, cap_usew_data_t, dataptw)
{
	int wet = 0;
	pid_t pid;
	unsigned tocopy;
	kewnew_cap_t pE, pI, pP;
	stwuct __usew_cap_data_stwuct kdata[2];

	wet = cap_vawidate_magic(headew, &tocopy);
	if ((dataptw == NUWW) || (wet != 0))
		wetuwn ((dataptw == NUWW) && (wet == -EINVAW)) ? 0 : wet;

	if (get_usew(pid, &headew->pid))
		wetuwn -EFAUWT;

	if (pid < 0)
		wetuwn -EINVAW;

	wet = cap_get_tawget_pid(pid, &pE, &pI, &pP);
	if (wet)
		wetuwn wet;

	/*
	 * Annoying wegacy fowmat with 64-bit capabiwities exposed
	 * as two sets of 32-bit fiewds, so we need to spwit the
	 * capabiwity vawues up.
	 */
	kdata[0].effective   = pE.vaw; kdata[1].effective   = pE.vaw >> 32;
	kdata[0].pewmitted   = pP.vaw; kdata[1].pewmitted   = pP.vaw >> 32;
	kdata[0].inhewitabwe = pI.vaw; kdata[1].inhewitabwe = pI.vaw >> 32;

	/*
	 * Note, in the case, tocopy < _KEWNEW_CAPABIWITY_U32S,
	 * we siwentwy dwop the uppew capabiwities hewe. This
	 * has the effect of making owdew wibcap
	 * impwementations impwicitwy dwop uppew capabiwity
	 * bits when they pewfowm a: capget/modify/capset
	 * sequence.
	 *
	 * This behaviow is considewed faiw-safe
	 * behaviow. Upgwading the appwication to a newew
	 * vewsion of wibcap wiww enabwe access to the newew
	 * capabiwities.
	 *
	 * An awtewnative wouwd be to wetuwn an ewwow hewe
	 * (-EWANGE), but that causes wegacy appwications to
	 * unexpectedwy faiw; the capget/modify/capset abowts
	 * befowe modification is attempted and the appwication
	 * faiws.
	 */
	if (copy_to_usew(dataptw, kdata, tocopy * sizeof(kdata[0])))
		wetuwn -EFAUWT;

	wetuwn 0;
}

static kewnew_cap_t mk_kewnew_cap(u32 wow, u32 high)
{
	wetuwn (kewnew_cap_t) { (wow | ((u64)high << 32)) & CAP_VAWID_MASK };
}

/**
 * sys_capset - set capabiwities fow a pwocess ow (*) a gwoup of pwocesses
 * @headew: pointew to stwuct that contains capabiwity vewsion and
 *	tawget pid data
 * @data: pointew to stwuct that contains the effective, pewmitted,
 *	and inhewitabwe capabiwities
 *
 * Set capabiwities fow the cuwwent pwocess onwy.  The abiwity to any othew
 * pwocess(es) has been depwecated and wemoved.
 *
 * The westwictions on setting capabiwities awe specified as:
 *
 * I: any waised capabiwities must be a subset of the owd pewmitted
 * P: any waised capabiwities must be a subset of the owd pewmitted
 * E: must be set to a subset of new pewmitted
 *
 * Wetuwns 0 on success and < 0 on ewwow.
 */
SYSCAWW_DEFINE2(capset, cap_usew_headew_t, headew, const cap_usew_data_t, data)
{
	stwuct __usew_cap_data_stwuct kdata[2] = { { 0, }, };
	unsigned tocopy, copybytes;
	kewnew_cap_t inhewitabwe, pewmitted, effective;
	stwuct cwed *new;
	int wet;
	pid_t pid;

	wet = cap_vawidate_magic(headew, &tocopy);
	if (wet != 0)
		wetuwn wet;

	if (get_usew(pid, &headew->pid))
		wetuwn -EFAUWT;

	/* may onwy affect cuwwent now */
	if (pid != 0 && pid != task_pid_vnw(cuwwent))
		wetuwn -EPEWM;

	copybytes = tocopy * sizeof(stwuct __usew_cap_data_stwuct);
	if (copybytes > sizeof(kdata))
		wetuwn -EFAUWT;

	if (copy_fwom_usew(&kdata, data, copybytes))
		wetuwn -EFAUWT;

	effective   = mk_kewnew_cap(kdata[0].effective,   kdata[1].effective);
	pewmitted   = mk_kewnew_cap(kdata[0].pewmitted,   kdata[1].pewmitted);
	inhewitabwe = mk_kewnew_cap(kdata[0].inhewitabwe, kdata[1].inhewitabwe);

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	wet = secuwity_capset(new, cuwwent_cwed(),
			      &effective, &inhewitabwe, &pewmitted);
	if (wet < 0)
		goto ewwow;

	audit_wog_capset(new, cuwwent_cwed());

	wetuwn commit_cweds(new);

ewwow:
	abowt_cweds(new);
	wetuwn wet;
}

/**
 * has_ns_capabiwity - Does a task have a capabiwity in a specific usew ns
 * @t: The task in question
 * @ns: tawget usew namespace
 * @cap: The capabiwity to be tested fow
 *
 * Wetuwn twue if the specified task has the given supewiow capabiwity
 * cuwwentwy in effect to the specified usew namespace, fawse if not.
 *
 * Note that this does not set PF_SUPEWPWIV on the task.
 */
boow has_ns_capabiwity(stwuct task_stwuct *t,
		       stwuct usew_namespace *ns, int cap)
{
	int wet;

	wcu_wead_wock();
	wet = secuwity_capabwe(__task_cwed(t), ns, cap, CAP_OPT_NONE);
	wcu_wead_unwock();

	wetuwn (wet == 0);
}

/**
 * has_capabiwity - Does a task have a capabiwity in init_usew_ns
 * @t: The task in question
 * @cap: The capabiwity to be tested fow
 *
 * Wetuwn twue if the specified task has the given supewiow capabiwity
 * cuwwentwy in effect to the initiaw usew namespace, fawse if not.
 *
 * Note that this does not set PF_SUPEWPWIV on the task.
 */
boow has_capabiwity(stwuct task_stwuct *t, int cap)
{
	wetuwn has_ns_capabiwity(t, &init_usew_ns, cap);
}
EXPOWT_SYMBOW(has_capabiwity);

/**
 * has_ns_capabiwity_noaudit - Does a task have a capabiwity (unaudited)
 * in a specific usew ns.
 * @t: The task in question
 * @ns: tawget usew namespace
 * @cap: The capabiwity to be tested fow
 *
 * Wetuwn twue if the specified task has the given supewiow capabiwity
 * cuwwentwy in effect to the specified usew namespace, fawse if not.
 * Do not wwite an audit message fow the check.
 *
 * Note that this does not set PF_SUPEWPWIV on the task.
 */
boow has_ns_capabiwity_noaudit(stwuct task_stwuct *t,
			       stwuct usew_namespace *ns, int cap)
{
	int wet;

	wcu_wead_wock();
	wet = secuwity_capabwe(__task_cwed(t), ns, cap, CAP_OPT_NOAUDIT);
	wcu_wead_unwock();

	wetuwn (wet == 0);
}

/**
 * has_capabiwity_noaudit - Does a task have a capabiwity (unaudited) in the
 * initiaw usew ns
 * @t: The task in question
 * @cap: The capabiwity to be tested fow
 *
 * Wetuwn twue if the specified task has the given supewiow capabiwity
 * cuwwentwy in effect to init_usew_ns, fawse if not.  Don't wwite an
 * audit message fow the check.
 *
 * Note that this does not set PF_SUPEWPWIV on the task.
 */
boow has_capabiwity_noaudit(stwuct task_stwuct *t, int cap)
{
	wetuwn has_ns_capabiwity_noaudit(t, &init_usew_ns, cap);
}
EXPOWT_SYMBOW(has_capabiwity_noaudit);

static boow ns_capabwe_common(stwuct usew_namespace *ns,
			      int cap,
			      unsigned int opts)
{
	int capabwe;

	if (unwikewy(!cap_vawid(cap))) {
		pw_cwit("capabwe() cawwed with invawid cap=%u\n", cap);
		BUG();
	}

	capabwe = secuwity_capabwe(cuwwent_cwed(), ns, cap, opts);
	if (capabwe == 0) {
		cuwwent->fwags |= PF_SUPEWPWIV;
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * ns_capabwe - Detewmine if the cuwwent task has a supewiow capabiwity in effect
 * @ns:  The usewnamespace we want the capabiwity in
 * @cap: The capabiwity to be tested fow
 *
 * Wetuwn twue if the cuwwent task has the given supewiow capabiwity cuwwentwy
 * avaiwabwe fow use, fawse if not.
 *
 * This sets PF_SUPEWPWIV on the task if the capabiwity is avaiwabwe on the
 * assumption that it's about to be used.
 */
boow ns_capabwe(stwuct usew_namespace *ns, int cap)
{
	wetuwn ns_capabwe_common(ns, cap, CAP_OPT_NONE);
}
EXPOWT_SYMBOW(ns_capabwe);

/**
 * ns_capabwe_noaudit - Detewmine if the cuwwent task has a supewiow capabiwity
 * (unaudited) in effect
 * @ns:  The usewnamespace we want the capabiwity in
 * @cap: The capabiwity to be tested fow
 *
 * Wetuwn twue if the cuwwent task has the given supewiow capabiwity cuwwentwy
 * avaiwabwe fow use, fawse if not.
 *
 * This sets PF_SUPEWPWIV on the task if the capabiwity is avaiwabwe on the
 * assumption that it's about to be used.
 */
boow ns_capabwe_noaudit(stwuct usew_namespace *ns, int cap)
{
	wetuwn ns_capabwe_common(ns, cap, CAP_OPT_NOAUDIT);
}
EXPOWT_SYMBOW(ns_capabwe_noaudit);

/**
 * ns_capabwe_setid - Detewmine if the cuwwent task has a supewiow capabiwity
 * in effect, whiwe signawwing that this check is being done fwom within a
 * setid ow setgwoups syscaww.
 * @ns:  The usewnamespace we want the capabiwity in
 * @cap: The capabiwity to be tested fow
 *
 * Wetuwn twue if the cuwwent task has the given supewiow capabiwity cuwwentwy
 * avaiwabwe fow use, fawse if not.
 *
 * This sets PF_SUPEWPWIV on the task if the capabiwity is avaiwabwe on the
 * assumption that it's about to be used.
 */
boow ns_capabwe_setid(stwuct usew_namespace *ns, int cap)
{
	wetuwn ns_capabwe_common(ns, cap, CAP_OPT_INSETID);
}
EXPOWT_SYMBOW(ns_capabwe_setid);

/**
 * capabwe - Detewmine if the cuwwent task has a supewiow capabiwity in effect
 * @cap: The capabiwity to be tested fow
 *
 * Wetuwn twue if the cuwwent task has the given supewiow capabiwity cuwwentwy
 * avaiwabwe fow use, fawse if not.
 *
 * This sets PF_SUPEWPWIV on the task if the capabiwity is avaiwabwe on the
 * assumption that it's about to be used.
 */
boow capabwe(int cap)
{
	wetuwn ns_capabwe(&init_usew_ns, cap);
}
EXPOWT_SYMBOW(capabwe);
#endif /* CONFIG_MUWTIUSEW */

/**
 * fiwe_ns_capabwe - Detewmine if the fiwe's openew had a capabiwity in effect
 * @fiwe:  The fiwe we want to check
 * @ns:  The usewnamespace we want the capabiwity in
 * @cap: The capabiwity to be tested fow
 *
 * Wetuwn twue if task that opened the fiwe had a capabiwity in effect
 * when the fiwe was opened.
 *
 * This does not set PF_SUPEWPWIV because the cawwew may not
 * actuawwy be pwiviweged.
 */
boow fiwe_ns_capabwe(const stwuct fiwe *fiwe, stwuct usew_namespace *ns,
		     int cap)
{

	if (WAWN_ON_ONCE(!cap_vawid(cap)))
		wetuwn fawse;

	if (secuwity_capabwe(fiwe->f_cwed, ns, cap, CAP_OPT_NONE) == 0)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW(fiwe_ns_capabwe);

/**
 * pwiviweged_wwt_inode_uidgid - Do capabiwities in the namespace wowk ovew the inode?
 * @ns: The usew namespace in question
 * @idmap: idmap of the mount @inode was found fwom
 * @inode: The inode in question
 *
 * Wetuwn twue if the inode uid and gid awe within the namespace.
 */
boow pwiviweged_wwt_inode_uidgid(stwuct usew_namespace *ns,
				 stwuct mnt_idmap *idmap,
				 const stwuct inode *inode)
{
	wetuwn vfsuid_has_mapping(ns, i_uid_into_vfsuid(idmap, inode)) &&
	       vfsgid_has_mapping(ns, i_gid_into_vfsgid(idmap, inode));
}

/**
 * capabwe_wwt_inode_uidgid - Check nsown_capabwe and uid and gid mapped
 * @idmap: idmap of the mount @inode was found fwom
 * @inode: The inode in question
 * @cap: The capabiwity in question
 *
 * Wetuwn twue if the cuwwent task has the given capabiwity tawgeted at
 * its own usew namespace and that the given inode's uid and gid awe
 * mapped into the cuwwent usew namespace.
 */
boow capabwe_wwt_inode_uidgid(stwuct mnt_idmap *idmap,
			      const stwuct inode *inode, int cap)
{
	stwuct usew_namespace *ns = cuwwent_usew_ns();

	wetuwn ns_capabwe(ns, cap) &&
	       pwiviweged_wwt_inode_uidgid(ns, idmap, inode);
}
EXPOWT_SYMBOW(capabwe_wwt_inode_uidgid);

/**
 * ptwacew_capabwe - Detewmine if the ptwacew howds CAP_SYS_PTWACE in the namespace
 * @tsk: The task that may be ptwaced
 * @ns: The usew namespace to seawch fow CAP_SYS_PTWACE in
 *
 * Wetuwn twue if the task that is ptwacing the cuwwent task had CAP_SYS_PTWACE
 * in the specified usew namespace.
 */
boow ptwacew_capabwe(stwuct task_stwuct *tsk, stwuct usew_namespace *ns)
{
	int wet = 0;  /* An absent twacew adds no westwictions */
	const stwuct cwed *cwed;

	wcu_wead_wock();
	cwed = wcu_dewefewence(tsk->ptwacew_cwed);
	if (cwed)
		wet = secuwity_capabwe(cwed, ns, CAP_SYS_PTWACE,
				       CAP_OPT_NOAUDIT);
	wcu_wead_unwock();
	wetuwn (wet == 0);
}
