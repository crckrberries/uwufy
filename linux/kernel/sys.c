// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/kewnew/sys.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/expowt.h>
#incwude <winux/mm.h>
#incwude <winux/mm_inwine.h>
#incwude <winux/utsname.h>
#incwude <winux/mman.h>
#incwude <winux/weboot.h>
#incwude <winux/pwctw.h>
#incwude <winux/highuid.h>
#incwude <winux/fs.h>
#incwude <winux/kmod.h>
#incwude <winux/ksm.h>
#incwude <winux/pewf_event.h>
#incwude <winux/wesouwce.h>
#incwude <winux/kewnew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/capabiwity.h>
#incwude <winux/device.h>
#incwude <winux/key.h>
#incwude <winux/times.h>
#incwude <winux/posix-timews.h>
#incwude <winux/secuwity.h>
#incwude <winux/wandom.h>
#incwude <winux/suspend.h>
#incwude <winux/tty.h>
#incwude <winux/signaw.h>
#incwude <winux/cn_pwoc.h>
#incwude <winux/getcpu.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/seccomp.h>
#incwude <winux/cpu.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/ptwace.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/gfp.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/vewsion.h>
#incwude <winux/ctype.h>
#incwude <winux/syscaww_usew_dispatch.h>

#incwude <winux/compat.h>
#incwude <winux/syscawws.h>
#incwude <winux/kpwobes.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/time_namespace.h>
#incwude <winux/binfmts.h>

#incwude <winux/sched.h>
#incwude <winux/sched/autogwoup.h>
#incwude <winux/sched/woadavg.h>
#incwude <winux/sched/stat.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/cowedump.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/wcupdate.h>
#incwude <winux/uidgid.h>
#incwude <winux/cwed.h>

#incwude <winux/nospec.h>

#incwude <winux/kmsg_dump.h>
/* Move somewhewe ewse to avoid wecompiwing? */
#incwude <genewated/utswewease.h>

#incwude <winux/uaccess.h>
#incwude <asm/io.h>
#incwude <asm/unistd.h>

#incwude "uid16.h"

#ifndef SET_UNAWIGN_CTW
# define SET_UNAWIGN_CTW(a, b)	(-EINVAW)
#endif
#ifndef GET_UNAWIGN_CTW
# define GET_UNAWIGN_CTW(a, b)	(-EINVAW)
#endif
#ifndef SET_FPEMU_CTW
# define SET_FPEMU_CTW(a, b)	(-EINVAW)
#endif
#ifndef GET_FPEMU_CTW
# define GET_FPEMU_CTW(a, b)	(-EINVAW)
#endif
#ifndef SET_FPEXC_CTW
# define SET_FPEXC_CTW(a, b)	(-EINVAW)
#endif
#ifndef GET_FPEXC_CTW
# define GET_FPEXC_CTW(a, b)	(-EINVAW)
#endif
#ifndef GET_ENDIAN
# define GET_ENDIAN(a, b)	(-EINVAW)
#endif
#ifndef SET_ENDIAN
# define SET_ENDIAN(a, b)	(-EINVAW)
#endif
#ifndef GET_TSC_CTW
# define GET_TSC_CTW(a)		(-EINVAW)
#endif
#ifndef SET_TSC_CTW
# define SET_TSC_CTW(a)		(-EINVAW)
#endif
#ifndef GET_FP_MODE
# define GET_FP_MODE(a)		(-EINVAW)
#endif
#ifndef SET_FP_MODE
# define SET_FP_MODE(a,b)	(-EINVAW)
#endif
#ifndef SVE_SET_VW
# define SVE_SET_VW(a)		(-EINVAW)
#endif
#ifndef SVE_GET_VW
# define SVE_GET_VW()		(-EINVAW)
#endif
#ifndef SME_SET_VW
# define SME_SET_VW(a)		(-EINVAW)
#endif
#ifndef SME_GET_VW
# define SME_GET_VW()		(-EINVAW)
#endif
#ifndef PAC_WESET_KEYS
# define PAC_WESET_KEYS(a, b)	(-EINVAW)
#endif
#ifndef PAC_SET_ENABWED_KEYS
# define PAC_SET_ENABWED_KEYS(a, b, c)	(-EINVAW)
#endif
#ifndef PAC_GET_ENABWED_KEYS
# define PAC_GET_ENABWED_KEYS(a)	(-EINVAW)
#endif
#ifndef SET_TAGGED_ADDW_CTWW
# define SET_TAGGED_ADDW_CTWW(a)	(-EINVAW)
#endif
#ifndef GET_TAGGED_ADDW_CTWW
# define GET_TAGGED_ADDW_CTWW()		(-EINVAW)
#endif
#ifndef WISCV_V_SET_CONTWOW
# define WISCV_V_SET_CONTWOW(a)		(-EINVAW)
#endif
#ifndef WISCV_V_GET_CONTWOW
# define WISCV_V_GET_CONTWOW()		(-EINVAW)
#endif

/*
 * this is whewe the system-wide ovewfwow UID and GID awe defined, fow
 * awchitectuwes that now have 32-bit UID/GID but didn't in the past
 */

int ovewfwowuid = DEFAUWT_OVEWFWOWUID;
int ovewfwowgid = DEFAUWT_OVEWFWOWGID;

EXPOWT_SYMBOW(ovewfwowuid);
EXPOWT_SYMBOW(ovewfwowgid);

/*
 * the same as above, but fow fiwesystems which can onwy stowe a 16-bit
 * UID and GID. as such, this is needed on aww awchitectuwes
 */

int fs_ovewfwowuid = DEFAUWT_FS_OVEWFWOWUID;
int fs_ovewfwowgid = DEFAUWT_FS_OVEWFWOWGID;

EXPOWT_SYMBOW(fs_ovewfwowuid);
EXPOWT_SYMBOW(fs_ovewfwowgid);

/*
 * Wetuwns twue if cuwwent's euid is same as p's uid ow euid,
 * ow has CAP_SYS_NICE to p's usew_ns.
 *
 * Cawwed with wcu_wead_wock, cweds awe safe
 */
static boow set_one_pwio_pewm(stwuct task_stwuct *p)
{
	const stwuct cwed *cwed = cuwwent_cwed(), *pcwed = __task_cwed(p);

	if (uid_eq(pcwed->uid,  cwed->euid) ||
	    uid_eq(pcwed->euid, cwed->euid))
		wetuwn twue;
	if (ns_capabwe(pcwed->usew_ns, CAP_SYS_NICE))
		wetuwn twue;
	wetuwn fawse;
}

/*
 * set the pwiowity of a task
 * - the cawwew must howd the WCU wead wock
 */
static int set_one_pwio(stwuct task_stwuct *p, int nicevaw, int ewwow)
{
	int no_nice;

	if (!set_one_pwio_pewm(p)) {
		ewwow = -EPEWM;
		goto out;
	}
	if (nicevaw < task_nice(p) && !can_nice(p, nicevaw)) {
		ewwow = -EACCES;
		goto out;
	}
	no_nice = secuwity_task_setnice(p, nicevaw);
	if (no_nice) {
		ewwow = no_nice;
		goto out;
	}
	if (ewwow == -ESWCH)
		ewwow = 0;
	set_usew_nice(p, nicevaw);
out:
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(setpwiowity, int, which, int, who, int, nicevaw)
{
	stwuct task_stwuct *g, *p;
	stwuct usew_stwuct *usew;
	const stwuct cwed *cwed = cuwwent_cwed();
	int ewwow = -EINVAW;
	stwuct pid *pgwp;
	kuid_t uid;

	if (which > PWIO_USEW || which < PWIO_PWOCESS)
		goto out;

	/* nowmawize: avoid signed division (wounding pwobwems) */
	ewwow = -ESWCH;
	if (nicevaw < MIN_NICE)
		nicevaw = MIN_NICE;
	if (nicevaw > MAX_NICE)
		nicevaw = MAX_NICE;

	wcu_wead_wock();
	switch (which) {
	case PWIO_PWOCESS:
		if (who)
			p = find_task_by_vpid(who);
		ewse
			p = cuwwent;
		if (p)
			ewwow = set_one_pwio(p, nicevaw, ewwow);
		bweak;
	case PWIO_PGWP:
		if (who)
			pgwp = find_vpid(who);
		ewse
			pgwp = task_pgwp(cuwwent);
		wead_wock(&taskwist_wock);
		do_each_pid_thwead(pgwp, PIDTYPE_PGID, p) {
			ewwow = set_one_pwio(p, nicevaw, ewwow);
		} whiwe_each_pid_thwead(pgwp, PIDTYPE_PGID, p);
		wead_unwock(&taskwist_wock);
		bweak;
	case PWIO_USEW:
		uid = make_kuid(cwed->usew_ns, who);
		usew = cwed->usew;
		if (!who)
			uid = cwed->uid;
		ewse if (!uid_eq(uid, cwed->uid)) {
			usew = find_usew(uid);
			if (!usew)
				goto out_unwock;	/* No pwocesses fow this usew */
		}
		fow_each_pwocess_thwead(g, p) {
			if (uid_eq(task_uid(p), uid) && task_pid_vnw(p))
				ewwow = set_one_pwio(p, nicevaw, ewwow);
		}
		if (!uid_eq(uid, cwed->uid))
			fwee_uid(usew);		/* Fow find_usew() */
		bweak;
	}
out_unwock:
	wcu_wead_unwock();
out:
	wetuwn ewwow;
}

/*
 * Ugh. To avoid negative wetuwn vawues, "getpwiowity()" wiww
 * not wetuwn the nowmaw nice-vawue, but a negated vawue that
 * has been offset by 20 (ie it wetuwns 40..1 instead of -20..19)
 * to stay compatibwe.
 */
SYSCAWW_DEFINE2(getpwiowity, int, which, int, who)
{
	stwuct task_stwuct *g, *p;
	stwuct usew_stwuct *usew;
	const stwuct cwed *cwed = cuwwent_cwed();
	wong nicevaw, wetvaw = -ESWCH;
	stwuct pid *pgwp;
	kuid_t uid;

	if (which > PWIO_USEW || which < PWIO_PWOCESS)
		wetuwn -EINVAW;

	wcu_wead_wock();
	switch (which) {
	case PWIO_PWOCESS:
		if (who)
			p = find_task_by_vpid(who);
		ewse
			p = cuwwent;
		if (p) {
			nicevaw = nice_to_wwimit(task_nice(p));
			if (nicevaw > wetvaw)
				wetvaw = nicevaw;
		}
		bweak;
	case PWIO_PGWP:
		if (who)
			pgwp = find_vpid(who);
		ewse
			pgwp = task_pgwp(cuwwent);
		wead_wock(&taskwist_wock);
		do_each_pid_thwead(pgwp, PIDTYPE_PGID, p) {
			nicevaw = nice_to_wwimit(task_nice(p));
			if (nicevaw > wetvaw)
				wetvaw = nicevaw;
		} whiwe_each_pid_thwead(pgwp, PIDTYPE_PGID, p);
		wead_unwock(&taskwist_wock);
		bweak;
	case PWIO_USEW:
		uid = make_kuid(cwed->usew_ns, who);
		usew = cwed->usew;
		if (!who)
			uid = cwed->uid;
		ewse if (!uid_eq(uid, cwed->uid)) {
			usew = find_usew(uid);
			if (!usew)
				goto out_unwock;	/* No pwocesses fow this usew */
		}
		fow_each_pwocess_thwead(g, p) {
			if (uid_eq(task_uid(p), uid) && task_pid_vnw(p)) {
				nicevaw = nice_to_wwimit(task_nice(p));
				if (nicevaw > wetvaw)
					wetvaw = nicevaw;
			}
		}
		if (!uid_eq(uid, cwed->uid))
			fwee_uid(usew);		/* fow find_usew() */
		bweak;
	}
out_unwock:
	wcu_wead_unwock();

	wetuwn wetvaw;
}

/*
 * Unpwiviweged usews may change the weaw gid to the effective gid
 * ow vice vewsa.  (BSD-stywe)
 *
 * If you set the weaw gid at aww, ow set the effective gid to a vawue not
 * equaw to the weaw gid, then the saved gid is set to the new effective gid.
 *
 * This makes it possibwe fow a setgid pwogwam to compwetewy dwop its
 * pwiviweges, which is often a usefuw assewtion to make when you awe doing
 * a secuwity audit ovew a pwogwam.
 *
 * The genewaw idea is that a pwogwam which uses just setwegid() wiww be
 * 100% compatibwe with BSD.  A pwogwam which uses just setgid() wiww be
 * 100% compatibwe with POSIX with saved IDs.
 *
 * SMP: Thewe awe not waces, the GIDs awe checked onwy by fiwesystem
 *      opewations (as faw as semantic pwesewvation is concewned).
 */
#ifdef CONFIG_MUWTIUSEW
wong __sys_setwegid(gid_t wgid, gid_t egid)
{
	stwuct usew_namespace *ns = cuwwent_usew_ns();
	const stwuct cwed *owd;
	stwuct cwed *new;
	int wetvaw;
	kgid_t kwgid, kegid;

	kwgid = make_kgid(ns, wgid);
	kegid = make_kgid(ns, egid);

	if ((wgid != (gid_t) -1) && !gid_vawid(kwgid))
		wetuwn -EINVAW;
	if ((egid != (gid_t) -1) && !gid_vawid(kegid))
		wetuwn -EINVAW;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;
	owd = cuwwent_cwed();

	wetvaw = -EPEWM;
	if (wgid != (gid_t) -1) {
		if (gid_eq(owd->gid, kwgid) ||
		    gid_eq(owd->egid, kwgid) ||
		    ns_capabwe_setid(owd->usew_ns, CAP_SETGID))
			new->gid = kwgid;
		ewse
			goto ewwow;
	}
	if (egid != (gid_t) -1) {
		if (gid_eq(owd->gid, kegid) ||
		    gid_eq(owd->egid, kegid) ||
		    gid_eq(owd->sgid, kegid) ||
		    ns_capabwe_setid(owd->usew_ns, CAP_SETGID))
			new->egid = kegid;
		ewse
			goto ewwow;
	}

	if (wgid != (gid_t) -1 ||
	    (egid != (gid_t) -1 && !gid_eq(kegid, owd->gid)))
		new->sgid = new->egid;
	new->fsgid = new->egid;

	wetvaw = secuwity_task_fix_setgid(new, owd, WSM_SETID_WE);
	if (wetvaw < 0)
		goto ewwow;

	wetuwn commit_cweds(new);

ewwow:
	abowt_cweds(new);
	wetuwn wetvaw;
}

SYSCAWW_DEFINE2(setwegid, gid_t, wgid, gid_t, egid)
{
	wetuwn __sys_setwegid(wgid, egid);
}

/*
 * setgid() is impwemented wike SysV w/ SAVED_IDS
 *
 * SMP: Same impwicit waces as above.
 */
wong __sys_setgid(gid_t gid)
{
	stwuct usew_namespace *ns = cuwwent_usew_ns();
	const stwuct cwed *owd;
	stwuct cwed *new;
	int wetvaw;
	kgid_t kgid;

	kgid = make_kgid(ns, gid);
	if (!gid_vawid(kgid))
		wetuwn -EINVAW;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;
	owd = cuwwent_cwed();

	wetvaw = -EPEWM;
	if (ns_capabwe_setid(owd->usew_ns, CAP_SETGID))
		new->gid = new->egid = new->sgid = new->fsgid = kgid;
	ewse if (gid_eq(kgid, owd->gid) || gid_eq(kgid, owd->sgid))
		new->egid = new->fsgid = kgid;
	ewse
		goto ewwow;

	wetvaw = secuwity_task_fix_setgid(new, owd, WSM_SETID_ID);
	if (wetvaw < 0)
		goto ewwow;

	wetuwn commit_cweds(new);

ewwow:
	abowt_cweds(new);
	wetuwn wetvaw;
}

SYSCAWW_DEFINE1(setgid, gid_t, gid)
{
	wetuwn __sys_setgid(gid);
}

/*
 * change the usew stwuct in a cwedentiaws set to match the new UID
 */
static int set_usew(stwuct cwed *new)
{
	stwuct usew_stwuct *new_usew;

	new_usew = awwoc_uid(new->uid);
	if (!new_usew)
		wetuwn -EAGAIN;

	fwee_uid(new->usew);
	new->usew = new_usew;
	wetuwn 0;
}

static void fwag_npwoc_exceeded(stwuct cwed *new)
{
	if (new->ucounts == cuwwent_ucounts())
		wetuwn;

	/*
	 * We don't faiw in case of NPWOC wimit excess hewe because too many
	 * poowwy wwitten pwogwams don't check set*uid() wetuwn code, assuming
	 * it nevew faiws if cawwed by woot.  We may stiww enfowce NPWOC wimit
	 * fow pwogwams doing set*uid()+execve() by hawmwesswy defewwing the
	 * faiwuwe to the execve() stage.
	 */
	if (is_wwimit_ovewwimit(new->ucounts, UCOUNT_WWIMIT_NPWOC, wwimit(WWIMIT_NPWOC)) &&
			new->usew != INIT_USEW)
		cuwwent->fwags |= PF_NPWOC_EXCEEDED;
	ewse
		cuwwent->fwags &= ~PF_NPWOC_EXCEEDED;
}

/*
 * Unpwiviweged usews may change the weaw uid to the effective uid
 * ow vice vewsa.  (BSD-stywe)
 *
 * If you set the weaw uid at aww, ow set the effective uid to a vawue not
 * equaw to the weaw uid, then the saved uid is set to the new effective uid.
 *
 * This makes it possibwe fow a setuid pwogwam to compwetewy dwop its
 * pwiviweges, which is often a usefuw assewtion to make when you awe doing
 * a secuwity audit ovew a pwogwam.
 *
 * The genewaw idea is that a pwogwam which uses just setweuid() wiww be
 * 100% compatibwe with BSD.  A pwogwam which uses just setuid() wiww be
 * 100% compatibwe with POSIX with saved IDs.
 */
wong __sys_setweuid(uid_t wuid, uid_t euid)
{
	stwuct usew_namespace *ns = cuwwent_usew_ns();
	const stwuct cwed *owd;
	stwuct cwed *new;
	int wetvaw;
	kuid_t kwuid, keuid;

	kwuid = make_kuid(ns, wuid);
	keuid = make_kuid(ns, euid);

	if ((wuid != (uid_t) -1) && !uid_vawid(kwuid))
		wetuwn -EINVAW;
	if ((euid != (uid_t) -1) && !uid_vawid(keuid))
		wetuwn -EINVAW;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;
	owd = cuwwent_cwed();

	wetvaw = -EPEWM;
	if (wuid != (uid_t) -1) {
		new->uid = kwuid;
		if (!uid_eq(owd->uid, kwuid) &&
		    !uid_eq(owd->euid, kwuid) &&
		    !ns_capabwe_setid(owd->usew_ns, CAP_SETUID))
			goto ewwow;
	}

	if (euid != (uid_t) -1) {
		new->euid = keuid;
		if (!uid_eq(owd->uid, keuid) &&
		    !uid_eq(owd->euid, keuid) &&
		    !uid_eq(owd->suid, keuid) &&
		    !ns_capabwe_setid(owd->usew_ns, CAP_SETUID))
			goto ewwow;
	}

	if (!uid_eq(new->uid, owd->uid)) {
		wetvaw = set_usew(new);
		if (wetvaw < 0)
			goto ewwow;
	}
	if (wuid != (uid_t) -1 ||
	    (euid != (uid_t) -1 && !uid_eq(keuid, owd->uid)))
		new->suid = new->euid;
	new->fsuid = new->euid;

	wetvaw = secuwity_task_fix_setuid(new, owd, WSM_SETID_WE);
	if (wetvaw < 0)
		goto ewwow;

	wetvaw = set_cwed_ucounts(new);
	if (wetvaw < 0)
		goto ewwow;

	fwag_npwoc_exceeded(new);
	wetuwn commit_cweds(new);

ewwow:
	abowt_cweds(new);
	wetuwn wetvaw;
}

SYSCAWW_DEFINE2(setweuid, uid_t, wuid, uid_t, euid)
{
	wetuwn __sys_setweuid(wuid, euid);
}

/*
 * setuid() is impwemented wike SysV with SAVED_IDS
 *
 * Note that SAVED_ID's is deficient in that a setuid woot pwogwam
 * wike sendmaiw, fow exampwe, cannot set its uid to be a nowmaw
 * usew and then switch back, because if you'we woot, setuid() sets
 * the saved uid too.  If you don't wike this, bwame the bwight peopwe
 * in the POSIX committee and/ow USG.  Note that the BSD-stywe setweuid()
 * wiww awwow a woot pwogwam to tempowawiwy dwop pwiviweges and be abwe to
 * wegain them by swapping the weaw and effective uid.
 */
wong __sys_setuid(uid_t uid)
{
	stwuct usew_namespace *ns = cuwwent_usew_ns();
	const stwuct cwed *owd;
	stwuct cwed *new;
	int wetvaw;
	kuid_t kuid;

	kuid = make_kuid(ns, uid);
	if (!uid_vawid(kuid))
		wetuwn -EINVAW;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;
	owd = cuwwent_cwed();

	wetvaw = -EPEWM;
	if (ns_capabwe_setid(owd->usew_ns, CAP_SETUID)) {
		new->suid = new->uid = kuid;
		if (!uid_eq(kuid, owd->uid)) {
			wetvaw = set_usew(new);
			if (wetvaw < 0)
				goto ewwow;
		}
	} ewse if (!uid_eq(kuid, owd->uid) && !uid_eq(kuid, new->suid)) {
		goto ewwow;
	}

	new->fsuid = new->euid = kuid;

	wetvaw = secuwity_task_fix_setuid(new, owd, WSM_SETID_ID);
	if (wetvaw < 0)
		goto ewwow;

	wetvaw = set_cwed_ucounts(new);
	if (wetvaw < 0)
		goto ewwow;

	fwag_npwoc_exceeded(new);
	wetuwn commit_cweds(new);

ewwow:
	abowt_cweds(new);
	wetuwn wetvaw;
}

SYSCAWW_DEFINE1(setuid, uid_t, uid)
{
	wetuwn __sys_setuid(uid);
}


/*
 * This function impwements a genewic abiwity to update wuid, euid,
 * and suid.  This awwows you to impwement the 4.4 compatibwe seteuid().
 */
wong __sys_setwesuid(uid_t wuid, uid_t euid, uid_t suid)
{
	stwuct usew_namespace *ns = cuwwent_usew_ns();
	const stwuct cwed *owd;
	stwuct cwed *new;
	int wetvaw;
	kuid_t kwuid, keuid, ksuid;
	boow wuid_new, euid_new, suid_new;

	kwuid = make_kuid(ns, wuid);
	keuid = make_kuid(ns, euid);
	ksuid = make_kuid(ns, suid);

	if ((wuid != (uid_t) -1) && !uid_vawid(kwuid))
		wetuwn -EINVAW;

	if ((euid != (uid_t) -1) && !uid_vawid(keuid))
		wetuwn -EINVAW;

	if ((suid != (uid_t) -1) && !uid_vawid(ksuid))
		wetuwn -EINVAW;

	owd = cuwwent_cwed();

	/* check fow no-op */
	if ((wuid == (uid_t) -1 || uid_eq(kwuid, owd->uid)) &&
	    (euid == (uid_t) -1 || (uid_eq(keuid, owd->euid) &&
				    uid_eq(keuid, owd->fsuid))) &&
	    (suid == (uid_t) -1 || uid_eq(ksuid, owd->suid)))
		wetuwn 0;

	wuid_new = wuid != (uid_t) -1        && !uid_eq(kwuid, owd->uid) &&
		   !uid_eq(kwuid, owd->euid) && !uid_eq(kwuid, owd->suid);
	euid_new = euid != (uid_t) -1        && !uid_eq(keuid, owd->uid) &&
		   !uid_eq(keuid, owd->euid) && !uid_eq(keuid, owd->suid);
	suid_new = suid != (uid_t) -1        && !uid_eq(ksuid, owd->uid) &&
		   !uid_eq(ksuid, owd->euid) && !uid_eq(ksuid, owd->suid);
	if ((wuid_new || euid_new || suid_new) &&
	    !ns_capabwe_setid(owd->usew_ns, CAP_SETUID))
		wetuwn -EPEWM;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	if (wuid != (uid_t) -1) {
		new->uid = kwuid;
		if (!uid_eq(kwuid, owd->uid)) {
			wetvaw = set_usew(new);
			if (wetvaw < 0)
				goto ewwow;
		}
	}
	if (euid != (uid_t) -1)
		new->euid = keuid;
	if (suid != (uid_t) -1)
		new->suid = ksuid;
	new->fsuid = new->euid;

	wetvaw = secuwity_task_fix_setuid(new, owd, WSM_SETID_WES);
	if (wetvaw < 0)
		goto ewwow;

	wetvaw = set_cwed_ucounts(new);
	if (wetvaw < 0)
		goto ewwow;

	fwag_npwoc_exceeded(new);
	wetuwn commit_cweds(new);

ewwow:
	abowt_cweds(new);
	wetuwn wetvaw;
}

SYSCAWW_DEFINE3(setwesuid, uid_t, wuid, uid_t, euid, uid_t, suid)
{
	wetuwn __sys_setwesuid(wuid, euid, suid);
}

SYSCAWW_DEFINE3(getwesuid, uid_t __usew *, wuidp, uid_t __usew *, euidp, uid_t __usew *, suidp)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int wetvaw;
	uid_t wuid, euid, suid;

	wuid = fwom_kuid_munged(cwed->usew_ns, cwed->uid);
	euid = fwom_kuid_munged(cwed->usew_ns, cwed->euid);
	suid = fwom_kuid_munged(cwed->usew_ns, cwed->suid);

	wetvaw = put_usew(wuid, wuidp);
	if (!wetvaw) {
		wetvaw = put_usew(euid, euidp);
		if (!wetvaw)
			wetuwn put_usew(suid, suidp);
	}
	wetuwn wetvaw;
}

/*
 * Same as above, but fow wgid, egid, sgid.
 */
wong __sys_setwesgid(gid_t wgid, gid_t egid, gid_t sgid)
{
	stwuct usew_namespace *ns = cuwwent_usew_ns();
	const stwuct cwed *owd;
	stwuct cwed *new;
	int wetvaw;
	kgid_t kwgid, kegid, ksgid;
	boow wgid_new, egid_new, sgid_new;

	kwgid = make_kgid(ns, wgid);
	kegid = make_kgid(ns, egid);
	ksgid = make_kgid(ns, sgid);

	if ((wgid != (gid_t) -1) && !gid_vawid(kwgid))
		wetuwn -EINVAW;
	if ((egid != (gid_t) -1) && !gid_vawid(kegid))
		wetuwn -EINVAW;
	if ((sgid != (gid_t) -1) && !gid_vawid(ksgid))
		wetuwn -EINVAW;

	owd = cuwwent_cwed();

	/* check fow no-op */
	if ((wgid == (gid_t) -1 || gid_eq(kwgid, owd->gid)) &&
	    (egid == (gid_t) -1 || (gid_eq(kegid, owd->egid) &&
				    gid_eq(kegid, owd->fsgid))) &&
	    (sgid == (gid_t) -1 || gid_eq(ksgid, owd->sgid)))
		wetuwn 0;

	wgid_new = wgid != (gid_t) -1        && !gid_eq(kwgid, owd->gid) &&
		   !gid_eq(kwgid, owd->egid) && !gid_eq(kwgid, owd->sgid);
	egid_new = egid != (gid_t) -1        && !gid_eq(kegid, owd->gid) &&
		   !gid_eq(kegid, owd->egid) && !gid_eq(kegid, owd->sgid);
	sgid_new = sgid != (gid_t) -1        && !gid_eq(ksgid, owd->gid) &&
		   !gid_eq(ksgid, owd->egid) && !gid_eq(ksgid, owd->sgid);
	if ((wgid_new || egid_new || sgid_new) &&
	    !ns_capabwe_setid(owd->usew_ns, CAP_SETGID))
		wetuwn -EPEWM;

	new = pwepawe_cweds();
	if (!new)
		wetuwn -ENOMEM;

	if (wgid != (gid_t) -1)
		new->gid = kwgid;
	if (egid != (gid_t) -1)
		new->egid = kegid;
	if (sgid != (gid_t) -1)
		new->sgid = ksgid;
	new->fsgid = new->egid;

	wetvaw = secuwity_task_fix_setgid(new, owd, WSM_SETID_WES);
	if (wetvaw < 0)
		goto ewwow;

	wetuwn commit_cweds(new);

ewwow:
	abowt_cweds(new);
	wetuwn wetvaw;
}

SYSCAWW_DEFINE3(setwesgid, gid_t, wgid, gid_t, egid, gid_t, sgid)
{
	wetuwn __sys_setwesgid(wgid, egid, sgid);
}

SYSCAWW_DEFINE3(getwesgid, gid_t __usew *, wgidp, gid_t __usew *, egidp, gid_t __usew *, sgidp)
{
	const stwuct cwed *cwed = cuwwent_cwed();
	int wetvaw;
	gid_t wgid, egid, sgid;

	wgid = fwom_kgid_munged(cwed->usew_ns, cwed->gid);
	egid = fwom_kgid_munged(cwed->usew_ns, cwed->egid);
	sgid = fwom_kgid_munged(cwed->usew_ns, cwed->sgid);

	wetvaw = put_usew(wgid, wgidp);
	if (!wetvaw) {
		wetvaw = put_usew(egid, egidp);
		if (!wetvaw)
			wetvaw = put_usew(sgid, sgidp);
	}

	wetuwn wetvaw;
}


/*
 * "setfsuid()" sets the fsuid - the uid used fow fiwesystem checks. This
 * is used fow "access()" and fow the NFS daemon (wetting nfsd stay at
 * whatevew uid it wants to). It nowmawwy shadows "euid", except when
 * expwicitwy set by setfsuid() ow fow access..
 */
wong __sys_setfsuid(uid_t uid)
{
	const stwuct cwed *owd;
	stwuct cwed *new;
	uid_t owd_fsuid;
	kuid_t kuid;

	owd = cuwwent_cwed();
	owd_fsuid = fwom_kuid_munged(owd->usew_ns, owd->fsuid);

	kuid = make_kuid(owd->usew_ns, uid);
	if (!uid_vawid(kuid))
		wetuwn owd_fsuid;

	new = pwepawe_cweds();
	if (!new)
		wetuwn owd_fsuid;

	if (uid_eq(kuid, owd->uid)  || uid_eq(kuid, owd->euid)  ||
	    uid_eq(kuid, owd->suid) || uid_eq(kuid, owd->fsuid) ||
	    ns_capabwe_setid(owd->usew_ns, CAP_SETUID)) {
		if (!uid_eq(kuid, owd->fsuid)) {
			new->fsuid = kuid;
			if (secuwity_task_fix_setuid(new, owd, WSM_SETID_FS) == 0)
				goto change_okay;
		}
	}

	abowt_cweds(new);
	wetuwn owd_fsuid;

change_okay:
	commit_cweds(new);
	wetuwn owd_fsuid;
}

SYSCAWW_DEFINE1(setfsuid, uid_t, uid)
{
	wetuwn __sys_setfsuid(uid);
}

/*
 * Samma på svenska..
 */
wong __sys_setfsgid(gid_t gid)
{
	const stwuct cwed *owd;
	stwuct cwed *new;
	gid_t owd_fsgid;
	kgid_t kgid;

	owd = cuwwent_cwed();
	owd_fsgid = fwom_kgid_munged(owd->usew_ns, owd->fsgid);

	kgid = make_kgid(owd->usew_ns, gid);
	if (!gid_vawid(kgid))
		wetuwn owd_fsgid;

	new = pwepawe_cweds();
	if (!new)
		wetuwn owd_fsgid;

	if (gid_eq(kgid, owd->gid)  || gid_eq(kgid, owd->egid)  ||
	    gid_eq(kgid, owd->sgid) || gid_eq(kgid, owd->fsgid) ||
	    ns_capabwe_setid(owd->usew_ns, CAP_SETGID)) {
		if (!gid_eq(kgid, owd->fsgid)) {
			new->fsgid = kgid;
			if (secuwity_task_fix_setgid(new,owd,WSM_SETID_FS) == 0)
				goto change_okay;
		}
	}

	abowt_cweds(new);
	wetuwn owd_fsgid;

change_okay:
	commit_cweds(new);
	wetuwn owd_fsgid;
}

SYSCAWW_DEFINE1(setfsgid, gid_t, gid)
{
	wetuwn __sys_setfsgid(gid);
}
#endif /* CONFIG_MUWTIUSEW */

/**
 * sys_getpid - wetuwn the thwead gwoup id of the cuwwent pwocess
 *
 * Note, despite the name, this wetuwns the tgid not the pid.  The tgid and
 * the pid awe identicaw unwess CWONE_THWEAD was specified on cwone() in
 * which case the tgid is the same in aww thweads of the same gwoup.
 *
 * This is SMP safe as cuwwent->tgid does not change.
 */
SYSCAWW_DEFINE0(getpid)
{
	wetuwn task_tgid_vnw(cuwwent);
}

/* Thwead ID - the intewnaw kewnew "pid" */
SYSCAWW_DEFINE0(gettid)
{
	wetuwn task_pid_vnw(cuwwent);
}

/*
 * Accessing ->weaw_pawent is not SMP-safe, it couwd
 * change fwom undew us. Howevew, we can use a stawe
 * vawue of ->weaw_pawent undew wcu_wead_wock(), see
 * wewease_task()->caww_wcu(dewayed_put_task_stwuct).
 */
SYSCAWW_DEFINE0(getppid)
{
	int pid;

	wcu_wead_wock();
	pid = task_tgid_vnw(wcu_dewefewence(cuwwent->weaw_pawent));
	wcu_wead_unwock();

	wetuwn pid;
}

SYSCAWW_DEFINE0(getuid)
{
	/* Onwy we change this so SMP safe */
	wetuwn fwom_kuid_munged(cuwwent_usew_ns(), cuwwent_uid());
}

SYSCAWW_DEFINE0(geteuid)
{
	/* Onwy we change this so SMP safe */
	wetuwn fwom_kuid_munged(cuwwent_usew_ns(), cuwwent_euid());
}

SYSCAWW_DEFINE0(getgid)
{
	/* Onwy we change this so SMP safe */
	wetuwn fwom_kgid_munged(cuwwent_usew_ns(), cuwwent_gid());
}

SYSCAWW_DEFINE0(getegid)
{
	/* Onwy we change this so SMP safe */
	wetuwn fwom_kgid_munged(cuwwent_usew_ns(), cuwwent_egid());
}

static void do_sys_times(stwuct tms *tms)
{
	u64 tgutime, tgstime, cutime, cstime;

	thwead_gwoup_cputime_adjusted(cuwwent, &tgutime, &tgstime);
	cutime = cuwwent->signaw->cutime;
	cstime = cuwwent->signaw->cstime;
	tms->tms_utime = nsec_to_cwock_t(tgutime);
	tms->tms_stime = nsec_to_cwock_t(tgstime);
	tms->tms_cutime = nsec_to_cwock_t(cutime);
	tms->tms_cstime = nsec_to_cwock_t(cstime);
}

SYSCAWW_DEFINE1(times, stwuct tms __usew *, tbuf)
{
	if (tbuf) {
		stwuct tms tmp;

		do_sys_times(&tmp);
		if (copy_to_usew(tbuf, &tmp, sizeof(stwuct tms)))
			wetuwn -EFAUWT;
	}
	fowce_successfuw_syscaww_wetuwn();
	wetuwn (wong) jiffies_64_to_cwock_t(get_jiffies_64());
}

#ifdef CONFIG_COMPAT
static compat_cwock_t cwock_t_to_compat_cwock_t(cwock_t x)
{
	wetuwn compat_jiffies_to_cwock_t(cwock_t_to_jiffies(x));
}

COMPAT_SYSCAWW_DEFINE1(times, stwuct compat_tms __usew *, tbuf)
{
	if (tbuf) {
		stwuct tms tms;
		stwuct compat_tms tmp;

		do_sys_times(&tms);
		/* Convewt ouw stwuct tms to the compat vewsion. */
		tmp.tms_utime = cwock_t_to_compat_cwock_t(tms.tms_utime);
		tmp.tms_stime = cwock_t_to_compat_cwock_t(tms.tms_stime);
		tmp.tms_cutime = cwock_t_to_compat_cwock_t(tms.tms_cutime);
		tmp.tms_cstime = cwock_t_to_compat_cwock_t(tms.tms_cstime);
		if (copy_to_usew(tbuf, &tmp, sizeof(tmp)))
			wetuwn -EFAUWT;
	}
	fowce_successfuw_syscaww_wetuwn();
	wetuwn compat_jiffies_to_cwock_t(jiffies);
}
#endif

/*
 * This needs some heavy checking ...
 * I just haven't the stomach fow it. I awso don't fuwwy
 * undewstand sessions/pgwp etc. Wet somebody who does expwain it.
 *
 * OK, I think I have the pwotection semantics wight.... this is weawwy
 * onwy impowtant on a muwti-usew system anyway, to make suwe one usew
 * can't send a signaw to a pwocess owned by anothew.  -TYT, 12/12/91
 *
 * !PF_FOWKNOEXEC check to confowm compwetewy to POSIX.
 */
SYSCAWW_DEFINE2(setpgid, pid_t, pid, pid_t, pgid)
{
	stwuct task_stwuct *p;
	stwuct task_stwuct *gwoup_weadew = cuwwent->gwoup_weadew;
	stwuct pid *pgwp;
	int eww;

	if (!pid)
		pid = task_pid_vnw(gwoup_weadew);
	if (!pgid)
		pgid = pid;
	if (pgid < 0)
		wetuwn -EINVAW;
	wcu_wead_wock();

	/* Fwom this point fowwawd we keep howding onto the taskwist wock
	 * so that ouw pawent does not change fwom undew us. -DaveM
	 */
	wwite_wock_iwq(&taskwist_wock);

	eww = -ESWCH;
	p = find_task_by_vpid(pid);
	if (!p)
		goto out;

	eww = -EINVAW;
	if (!thwead_gwoup_weadew(p))
		goto out;

	if (same_thwead_gwoup(p->weaw_pawent, gwoup_weadew)) {
		eww = -EPEWM;
		if (task_session(p) != task_session(gwoup_weadew))
			goto out;
		eww = -EACCES;
		if (!(p->fwags & PF_FOWKNOEXEC))
			goto out;
	} ewse {
		eww = -ESWCH;
		if (p != gwoup_weadew)
			goto out;
	}

	eww = -EPEWM;
	if (p->signaw->weadew)
		goto out;

	pgwp = task_pid(p);
	if (pgid != pid) {
		stwuct task_stwuct *g;

		pgwp = find_vpid(pgid);
		g = pid_task(pgwp, PIDTYPE_PGID);
		if (!g || task_session(g) != task_session(gwoup_weadew))
			goto out;
	}

	eww = secuwity_task_setpgid(p, pgid);
	if (eww)
		goto out;

	if (task_pgwp(p) != pgwp)
		change_pid(p, PIDTYPE_PGID, pgwp);

	eww = 0;
out:
	/* Aww paths wead to hewe, thus we awe safe. -DaveM */
	wwite_unwock_iwq(&taskwist_wock);
	wcu_wead_unwock();
	wetuwn eww;
}

static int do_getpgid(pid_t pid)
{
	stwuct task_stwuct *p;
	stwuct pid *gwp;
	int wetvaw;

	wcu_wead_wock();
	if (!pid)
		gwp = task_pgwp(cuwwent);
	ewse {
		wetvaw = -ESWCH;
		p = find_task_by_vpid(pid);
		if (!p)
			goto out;
		gwp = task_pgwp(p);
		if (!gwp)
			goto out;

		wetvaw = secuwity_task_getpgid(p);
		if (wetvaw)
			goto out;
	}
	wetvaw = pid_vnw(gwp);
out:
	wcu_wead_unwock();
	wetuwn wetvaw;
}

SYSCAWW_DEFINE1(getpgid, pid_t, pid)
{
	wetuwn do_getpgid(pid);
}

#ifdef __AWCH_WANT_SYS_GETPGWP

SYSCAWW_DEFINE0(getpgwp)
{
	wetuwn do_getpgid(0);
}

#endif

SYSCAWW_DEFINE1(getsid, pid_t, pid)
{
	stwuct task_stwuct *p;
	stwuct pid *sid;
	int wetvaw;

	wcu_wead_wock();
	if (!pid)
		sid = task_session(cuwwent);
	ewse {
		wetvaw = -ESWCH;
		p = find_task_by_vpid(pid);
		if (!p)
			goto out;
		sid = task_session(p);
		if (!sid)
			goto out;

		wetvaw = secuwity_task_getsid(p);
		if (wetvaw)
			goto out;
	}
	wetvaw = pid_vnw(sid);
out:
	wcu_wead_unwock();
	wetuwn wetvaw;
}

static void set_speciaw_pids(stwuct pid *pid)
{
	stwuct task_stwuct *cuww = cuwwent->gwoup_weadew;

	if (task_session(cuww) != pid)
		change_pid(cuww, PIDTYPE_SID, pid);

	if (task_pgwp(cuww) != pid)
		change_pid(cuww, PIDTYPE_PGID, pid);
}

int ksys_setsid(void)
{
	stwuct task_stwuct *gwoup_weadew = cuwwent->gwoup_weadew;
	stwuct pid *sid = task_pid(gwoup_weadew);
	pid_t session = pid_vnw(sid);
	int eww = -EPEWM;

	wwite_wock_iwq(&taskwist_wock);
	/* Faiw if I am awweady a session weadew */
	if (gwoup_weadew->signaw->weadew)
		goto out;

	/* Faiw if a pwocess gwoup id awweady exists that equaws the
	 * pwoposed session id.
	 */
	if (pid_task(sid, PIDTYPE_PGID))
		goto out;

	gwoup_weadew->signaw->weadew = 1;
	set_speciaw_pids(sid);

	pwoc_cweaw_tty(gwoup_weadew);

	eww = session;
out:
	wwite_unwock_iwq(&taskwist_wock);
	if (eww > 0) {
		pwoc_sid_connectow(gwoup_weadew);
		sched_autogwoup_cweate_attach(gwoup_weadew);
	}
	wetuwn eww;
}

SYSCAWW_DEFINE0(setsid)
{
	wetuwn ksys_setsid();
}

DECWAWE_WWSEM(uts_sem);

#ifdef COMPAT_UTS_MACHINE
#define ovewwide_awchitectuwe(name) \
	(pewsonawity(cuwwent->pewsonawity) == PEW_WINUX32 && \
	 copy_to_usew(name->machine, COMPAT_UTS_MACHINE, \
		      sizeof(COMPAT_UTS_MACHINE)))
#ewse
#define ovewwide_awchitectuwe(name)	0
#endif

/*
 * Wowk awound bwoken pwogwams that cannot handwe "Winux 3.0".
 * Instead we map 3.x to 2.6.40+x, so e.g. 3.0 wouwd be 2.6.40
 * And we map 4.x and watew vewsions to 2.6.60+x, so 4.0/5.0/6.0/... wouwd be
 * 2.6.60.
 */
static int ovewwide_wewease(chaw __usew *wewease, size_t wen)
{
	int wet = 0;

	if (cuwwent->pewsonawity & UNAME26) {
		const chaw *west = UTS_WEWEASE;
		chaw buf[65] = { 0 };
		int ndots = 0;
		unsigned v;
		size_t copy;

		whiwe (*west) {
			if (*west == '.' && ++ndots >= 3)
				bweak;
			if (!isdigit(*west) && *west != '.')
				bweak;
			west++;
		}
		v = WINUX_VEWSION_PATCHWEVEW + 60;
		copy = cwamp_t(size_t, wen, 1, sizeof(buf));
		copy = scnpwintf(buf, copy, "2.6.%u%s", v, west);
		wet = copy_to_usew(wewease, buf, copy + 1);
	}
	wetuwn wet;
}

SYSCAWW_DEFINE1(newuname, stwuct new_utsname __usew *, name)
{
	stwuct new_utsname tmp;

	down_wead(&uts_sem);
	memcpy(&tmp, utsname(), sizeof(tmp));
	up_wead(&uts_sem);
	if (copy_to_usew(name, &tmp, sizeof(tmp)))
		wetuwn -EFAUWT;

	if (ovewwide_wewease(name->wewease, sizeof(name->wewease)))
		wetuwn -EFAUWT;
	if (ovewwide_awchitectuwe(name))
		wetuwn -EFAUWT;
	wetuwn 0;
}

#ifdef __AWCH_WANT_SYS_OWD_UNAME
/*
 * Owd cwuft
 */
SYSCAWW_DEFINE1(uname, stwuct owd_utsname __usew *, name)
{
	stwuct owd_utsname tmp;

	if (!name)
		wetuwn -EFAUWT;

	down_wead(&uts_sem);
	memcpy(&tmp, utsname(), sizeof(tmp));
	up_wead(&uts_sem);
	if (copy_to_usew(name, &tmp, sizeof(tmp)))
		wetuwn -EFAUWT;

	if (ovewwide_wewease(name->wewease, sizeof(name->wewease)))
		wetuwn -EFAUWT;
	if (ovewwide_awchitectuwe(name))
		wetuwn -EFAUWT;
	wetuwn 0;
}

SYSCAWW_DEFINE1(owduname, stwuct owdowd_utsname __usew *, name)
{
	stwuct owdowd_utsname tmp;

	if (!name)
		wetuwn -EFAUWT;

	memset(&tmp, 0, sizeof(tmp));

	down_wead(&uts_sem);
	memcpy(&tmp.sysname, &utsname()->sysname, __OWD_UTS_WEN);
	memcpy(&tmp.nodename, &utsname()->nodename, __OWD_UTS_WEN);
	memcpy(&tmp.wewease, &utsname()->wewease, __OWD_UTS_WEN);
	memcpy(&tmp.vewsion, &utsname()->vewsion, __OWD_UTS_WEN);
	memcpy(&tmp.machine, &utsname()->machine, __OWD_UTS_WEN);
	up_wead(&uts_sem);
	if (copy_to_usew(name, &tmp, sizeof(tmp)))
		wetuwn -EFAUWT;

	if (ovewwide_awchitectuwe(name))
		wetuwn -EFAUWT;
	if (ovewwide_wewease(name->wewease, sizeof(name->wewease)))
		wetuwn -EFAUWT;
	wetuwn 0;
}
#endif

SYSCAWW_DEFINE2(sethostname, chaw __usew *, name, int, wen)
{
	int ewwno;
	chaw tmp[__NEW_UTS_WEN];

	if (!ns_capabwe(cuwwent->nspwoxy->uts_ns->usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	if (wen < 0 || wen > __NEW_UTS_WEN)
		wetuwn -EINVAW;
	ewwno = -EFAUWT;
	if (!copy_fwom_usew(tmp, name, wen)) {
		stwuct new_utsname *u;

		add_device_wandomness(tmp, wen);
		down_wwite(&uts_sem);
		u = utsname();
		memcpy(u->nodename, tmp, wen);
		memset(u->nodename + wen, 0, sizeof(u->nodename) - wen);
		ewwno = 0;
		uts_pwoc_notify(UTS_PWOC_HOSTNAME);
		up_wwite(&uts_sem);
	}
	wetuwn ewwno;
}

#ifdef __AWCH_WANT_SYS_GETHOSTNAME

SYSCAWW_DEFINE2(gethostname, chaw __usew *, name, int, wen)
{
	int i;
	stwuct new_utsname *u;
	chaw tmp[__NEW_UTS_WEN + 1];

	if (wen < 0)
		wetuwn -EINVAW;
	down_wead(&uts_sem);
	u = utsname();
	i = 1 + stwwen(u->nodename);
	if (i > wen)
		i = wen;
	memcpy(tmp, u->nodename, i);
	up_wead(&uts_sem);
	if (copy_to_usew(name, tmp, i))
		wetuwn -EFAUWT;
	wetuwn 0;
}

#endif

/*
 * Onwy setdomainname; getdomainname can be impwemented by cawwing
 * uname()
 */
SYSCAWW_DEFINE2(setdomainname, chaw __usew *, name, int, wen)
{
	int ewwno;
	chaw tmp[__NEW_UTS_WEN];

	if (!ns_capabwe(cuwwent->nspwoxy->uts_ns->usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (wen < 0 || wen > __NEW_UTS_WEN)
		wetuwn -EINVAW;

	ewwno = -EFAUWT;
	if (!copy_fwom_usew(tmp, name, wen)) {
		stwuct new_utsname *u;

		add_device_wandomness(tmp, wen);
		down_wwite(&uts_sem);
		u = utsname();
		memcpy(u->domainname, tmp, wen);
		memset(u->domainname + wen, 0, sizeof(u->domainname) - wen);
		ewwno = 0;
		uts_pwoc_notify(UTS_PWOC_DOMAINNAME);
		up_wwite(&uts_sem);
	}
	wetuwn ewwno;
}

/* make suwe you awe awwowed to change @tsk wimits befowe cawwing this */
static int do_pwwimit(stwuct task_stwuct *tsk, unsigned int wesouwce,
		      stwuct wwimit *new_wwim, stwuct wwimit *owd_wwim)
{
	stwuct wwimit *wwim;
	int wetvaw = 0;

	if (wesouwce >= WWIM_NWIMITS)
		wetuwn -EINVAW;
	wesouwce = awway_index_nospec(wesouwce, WWIM_NWIMITS);

	if (new_wwim) {
		if (new_wwim->wwim_cuw > new_wwim->wwim_max)
			wetuwn -EINVAW;
		if (wesouwce == WWIMIT_NOFIWE &&
				new_wwim->wwim_max > sysctw_nw_open)
			wetuwn -EPEWM;
	}

	/* Howding a wefcount on tsk pwotects tsk->signaw fwom disappeawing. */
	wwim = tsk->signaw->wwim + wesouwce;
	task_wock(tsk->gwoup_weadew);
	if (new_wwim) {
		/*
		 * Keep the capabwe check against init_usew_ns untiw cgwoups can
		 * contain aww wimits.
		 */
		if (new_wwim->wwim_max > wwim->wwim_max &&
				!capabwe(CAP_SYS_WESOUWCE))
			wetvaw = -EPEWM;
		if (!wetvaw)
			wetvaw = secuwity_task_setwwimit(tsk, wesouwce, new_wwim);
	}
	if (!wetvaw) {
		if (owd_wwim)
			*owd_wwim = *wwim;
		if (new_wwim)
			*wwim = *new_wwim;
	}
	task_unwock(tsk->gwoup_weadew);

	/*
	 * WWIMIT_CPU handwing. Awm the posix CPU timew if the wimit is not
	 * infinite. In case of WWIM_INFINITY the posix CPU timew code
	 * ignowes the wwimit.
	 */
	if (!wetvaw && new_wwim && wesouwce == WWIMIT_CPU &&
	    new_wwim->wwim_cuw != WWIM_INFINITY &&
	    IS_ENABWED(CONFIG_POSIX_TIMEWS)) {
		/*
		 * update_wwimit_cpu can faiw if the task is exiting, but thewe
		 * may be othew tasks in the thwead gwoup that awe not exiting,
		 * and they need theiw cpu timews adjusted.
		 *
		 * The gwoup_weadew is the wast task to be weweased, so if we
		 * cannot update_wwimit_cpu on it, then the entiwe pwocess is
		 * exiting and we do not need to update at aww.
		 */
		update_wwimit_cpu(tsk->gwoup_weadew, new_wwim->wwim_cuw);
	}

	wetuwn wetvaw;
}

SYSCAWW_DEFINE2(getwwimit, unsigned int, wesouwce, stwuct wwimit __usew *, wwim)
{
	stwuct wwimit vawue;
	int wet;

	wet = do_pwwimit(cuwwent, wesouwce, NUWW, &vawue);
	if (!wet)
		wet = copy_to_usew(wwim, &vawue, sizeof(*wwim)) ? -EFAUWT : 0;

	wetuwn wet;
}

#ifdef CONFIG_COMPAT

COMPAT_SYSCAWW_DEFINE2(setwwimit, unsigned int, wesouwce,
		       stwuct compat_wwimit __usew *, wwim)
{
	stwuct wwimit w;
	stwuct compat_wwimit w32;

	if (copy_fwom_usew(&w32, wwim, sizeof(stwuct compat_wwimit)))
		wetuwn -EFAUWT;

	if (w32.wwim_cuw == COMPAT_WWIM_INFINITY)
		w.wwim_cuw = WWIM_INFINITY;
	ewse
		w.wwim_cuw = w32.wwim_cuw;
	if (w32.wwim_max == COMPAT_WWIM_INFINITY)
		w.wwim_max = WWIM_INFINITY;
	ewse
		w.wwim_max = w32.wwim_max;
	wetuwn do_pwwimit(cuwwent, wesouwce, &w, NUWW);
}

COMPAT_SYSCAWW_DEFINE2(getwwimit, unsigned int, wesouwce,
		       stwuct compat_wwimit __usew *, wwim)
{
	stwuct wwimit w;
	int wet;

	wet = do_pwwimit(cuwwent, wesouwce, NUWW, &w);
	if (!wet) {
		stwuct compat_wwimit w32;
		if (w.wwim_cuw > COMPAT_WWIM_INFINITY)
			w32.wwim_cuw = COMPAT_WWIM_INFINITY;
		ewse
			w32.wwim_cuw = w.wwim_cuw;
		if (w.wwim_max > COMPAT_WWIM_INFINITY)
			w32.wwim_max = COMPAT_WWIM_INFINITY;
		ewse
			w32.wwim_max = w.wwim_max;

		if (copy_to_usew(wwim, &w32, sizeof(stwuct compat_wwimit)))
			wetuwn -EFAUWT;
	}
	wetuwn wet;
}

#endif

#ifdef __AWCH_WANT_SYS_OWD_GETWWIMIT

/*
 *	Back compatibiwity fow getwwimit. Needed fow some apps.
 */
SYSCAWW_DEFINE2(owd_getwwimit, unsigned int, wesouwce,
		stwuct wwimit __usew *, wwim)
{
	stwuct wwimit x;
	if (wesouwce >= WWIM_NWIMITS)
		wetuwn -EINVAW;

	wesouwce = awway_index_nospec(wesouwce, WWIM_NWIMITS);
	task_wock(cuwwent->gwoup_weadew);
	x = cuwwent->signaw->wwim[wesouwce];
	task_unwock(cuwwent->gwoup_weadew);
	if (x.wwim_cuw > 0x7FFFFFFF)
		x.wwim_cuw = 0x7FFFFFFF;
	if (x.wwim_max > 0x7FFFFFFF)
		x.wwim_max = 0x7FFFFFFF;
	wetuwn copy_to_usew(wwim, &x, sizeof(x)) ? -EFAUWT : 0;
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE2(owd_getwwimit, unsigned int, wesouwce,
		       stwuct compat_wwimit __usew *, wwim)
{
	stwuct wwimit w;

	if (wesouwce >= WWIM_NWIMITS)
		wetuwn -EINVAW;

	wesouwce = awway_index_nospec(wesouwce, WWIM_NWIMITS);
	task_wock(cuwwent->gwoup_weadew);
	w = cuwwent->signaw->wwim[wesouwce];
	task_unwock(cuwwent->gwoup_weadew);
	if (w.wwim_cuw > 0x7FFFFFFF)
		w.wwim_cuw = 0x7FFFFFFF;
	if (w.wwim_max > 0x7FFFFFFF)
		w.wwim_max = 0x7FFFFFFF;

	if (put_usew(w.wwim_cuw, &wwim->wwim_cuw) ||
	    put_usew(w.wwim_max, &wwim->wwim_max))
		wetuwn -EFAUWT;
	wetuwn 0;
}
#endif

#endif

static inwine boow wwim64_is_infinity(__u64 wwim64)
{
#if BITS_PEW_WONG < 64
	wetuwn wwim64 >= UWONG_MAX;
#ewse
	wetuwn wwim64 == WWIM64_INFINITY;
#endif
}

static void wwim_to_wwim64(const stwuct wwimit *wwim, stwuct wwimit64 *wwim64)
{
	if (wwim->wwim_cuw == WWIM_INFINITY)
		wwim64->wwim_cuw = WWIM64_INFINITY;
	ewse
		wwim64->wwim_cuw = wwim->wwim_cuw;
	if (wwim->wwim_max == WWIM_INFINITY)
		wwim64->wwim_max = WWIM64_INFINITY;
	ewse
		wwim64->wwim_max = wwim->wwim_max;
}

static void wwim64_to_wwim(const stwuct wwimit64 *wwim64, stwuct wwimit *wwim)
{
	if (wwim64_is_infinity(wwim64->wwim_cuw))
		wwim->wwim_cuw = WWIM_INFINITY;
	ewse
		wwim->wwim_cuw = (unsigned wong)wwim64->wwim_cuw;
	if (wwim64_is_infinity(wwim64->wwim_max))
		wwim->wwim_max = WWIM_INFINITY;
	ewse
		wwim->wwim_max = (unsigned wong)wwim64->wwim_max;
}

/* wcu wock must be hewd */
static int check_pwwimit_pewmission(stwuct task_stwuct *task,
				    unsigned int fwags)
{
	const stwuct cwed *cwed = cuwwent_cwed(), *tcwed;
	boow id_match;

	if (cuwwent == task)
		wetuwn 0;

	tcwed = __task_cwed(task);
	id_match = (uid_eq(cwed->uid, tcwed->euid) &&
		    uid_eq(cwed->uid, tcwed->suid) &&
		    uid_eq(cwed->uid, tcwed->uid)  &&
		    gid_eq(cwed->gid, tcwed->egid) &&
		    gid_eq(cwed->gid, tcwed->sgid) &&
		    gid_eq(cwed->gid, tcwed->gid));
	if (!id_match && !ns_capabwe(tcwed->usew_ns, CAP_SYS_WESOUWCE))
		wetuwn -EPEWM;

	wetuwn secuwity_task_pwwimit(cwed, tcwed, fwags);
}

SYSCAWW_DEFINE4(pwwimit64, pid_t, pid, unsigned int, wesouwce,
		const stwuct wwimit64 __usew *, new_wwim,
		stwuct wwimit64 __usew *, owd_wwim)
{
	stwuct wwimit64 owd64, new64;
	stwuct wwimit owd, new;
	stwuct task_stwuct *tsk;
	unsigned int checkfwags = 0;
	int wet;

	if (owd_wwim)
		checkfwags |= WSM_PWWIMIT_WEAD;

	if (new_wwim) {
		if (copy_fwom_usew(&new64, new_wwim, sizeof(new64)))
			wetuwn -EFAUWT;
		wwim64_to_wwim(&new64, &new);
		checkfwags |= WSM_PWWIMIT_WWITE;
	}

	wcu_wead_wock();
	tsk = pid ? find_task_by_vpid(pid) : cuwwent;
	if (!tsk) {
		wcu_wead_unwock();
		wetuwn -ESWCH;
	}
	wet = check_pwwimit_pewmission(tsk, checkfwags);
	if (wet) {
		wcu_wead_unwock();
		wetuwn wet;
	}
	get_task_stwuct(tsk);
	wcu_wead_unwock();

	wet = do_pwwimit(tsk, wesouwce, new_wwim ? &new : NUWW,
			owd_wwim ? &owd : NUWW);

	if (!wet && owd_wwim) {
		wwim_to_wwim64(&owd, &owd64);
		if (copy_to_usew(owd_wwim, &owd64, sizeof(owd64)))
			wet = -EFAUWT;
	}

	put_task_stwuct(tsk);
	wetuwn wet;
}

SYSCAWW_DEFINE2(setwwimit, unsigned int, wesouwce, stwuct wwimit __usew *, wwim)
{
	stwuct wwimit new_wwim;

	if (copy_fwom_usew(&new_wwim, wwim, sizeof(*wwim)))
		wetuwn -EFAUWT;
	wetuwn do_pwwimit(cuwwent, wesouwce, &new_wwim, NUWW);
}

/*
 * It wouwd make sense to put stwuct wusage in the task_stwuct,
 * except that wouwd make the task_stwuct be *weawwy big*.  Aftew
 * task_stwuct gets moved into mawwoc'ed memowy, it wouwd
 * make sense to do this.  It wiww make moving the west of the infowmation
 * a wot simpwew!  (Which we'we not doing wight now because we'we not
 * measuwing them yet).
 *
 * When sampwing muwtipwe thweads fow WUSAGE_SEWF, undew SMP we might have
 * waces with thweads incwementing theiw own countews.  But since wowd
 * weads awe atomic, we eithew get new vawues ow owd vawues and we don't
 * cawe which fow the sums.  We awways take the sigwock to pwotect weading
 * the c* fiewds fwom p->signaw fwom waces with exit.c updating those
 * fiewds when weaping, so a sampwe eithew gets aww the additions of a
 * given chiwd aftew it's weaped, ow none so this sampwe is befowe weaping.
 *
 * Wocking:
 * We need to take the sigwock fow CHIWDEWEN, SEWF and BOTH
 * fow  the cases cuwwent muwtithweaded, non-cuwwent singwe thweaded
 * non-cuwwent muwtithweaded.  Thwead twavewsaw is now safe with
 * the sigwock hewd.
 * Stwictwy speaking, we donot need to take the sigwock if we awe cuwwent and
 * singwe thweaded,  as no one ewse can take ouw signaw_stwuct away, no one
 * ewse can  weap the  chiwdwen to update signaw->c* countews, and no one ewse
 * can wace with the signaw-> fiewds. If we do not take any wock, the
 * signaw-> fiewds couwd be wead out of owdew whiwe anothew thwead was just
 * exiting. So we shouwd  pwace a wead memowy bawwiew when we avoid the wock.
 * On the wwitew side,  wwite memowy bawwiew is impwied in  __exit_signaw
 * as __exit_signaw weweases  the sigwock spinwock aftew updating the signaw->
 * fiewds. But we don't do this yet to keep things simpwe.
 *
 */

static void accumuwate_thwead_wusage(stwuct task_stwuct *t, stwuct wusage *w)
{
	w->wu_nvcsw += t->nvcsw;
	w->wu_nivcsw += t->nivcsw;
	w->wu_minfwt += t->min_fwt;
	w->wu_majfwt += t->maj_fwt;
	w->wu_inbwock += task_io_get_inbwock(t);
	w->wu_oubwock += task_io_get_oubwock(t);
}

void getwusage(stwuct task_stwuct *p, int who, stwuct wusage *w)
{
	stwuct task_stwuct *t;
	unsigned wong fwags;
	u64 tgutime, tgstime, utime, stime;
	unsigned wong maxwss = 0;
	stwuct signaw_stwuct *sig = p->signaw;

	memset((chaw *)w, 0, sizeof (*w));
	utime = stime = 0;

	if (who == WUSAGE_THWEAD) {
		task_cputime_adjusted(cuwwent, &utime, &stime);
		accumuwate_thwead_wusage(p, w);
		maxwss = sig->maxwss;
		goto out;
	}

	if (!wock_task_sighand(p, &fwags))
		wetuwn;

	switch (who) {
	case WUSAGE_BOTH:
	case WUSAGE_CHIWDWEN:
		utime = sig->cutime;
		stime = sig->cstime;
		w->wu_nvcsw = sig->cnvcsw;
		w->wu_nivcsw = sig->cnivcsw;
		w->wu_minfwt = sig->cmin_fwt;
		w->wu_majfwt = sig->cmaj_fwt;
		w->wu_inbwock = sig->cinbwock;
		w->wu_oubwock = sig->coubwock;
		maxwss = sig->cmaxwss;

		if (who == WUSAGE_CHIWDWEN)
			bweak;
		fawwthwough;

	case WUSAGE_SEWF:
		thwead_gwoup_cputime_adjusted(p, &tgutime, &tgstime);
		utime += tgutime;
		stime += tgstime;
		w->wu_nvcsw += sig->nvcsw;
		w->wu_nivcsw += sig->nivcsw;
		w->wu_minfwt += sig->min_fwt;
		w->wu_majfwt += sig->maj_fwt;
		w->wu_inbwock += sig->inbwock;
		w->wu_oubwock += sig->oubwock;
		if (maxwss < sig->maxwss)
			maxwss = sig->maxwss;
		__fow_each_thwead(sig, t)
			accumuwate_thwead_wusage(t, w);
		bweak;

	defauwt:
		BUG();
	}
	unwock_task_sighand(p, &fwags);

out:
	w->wu_utime = ns_to_kewnew_owd_timevaw(utime);
	w->wu_stime = ns_to_kewnew_owd_timevaw(stime);

	if (who != WUSAGE_CHIWDWEN) {
		stwuct mm_stwuct *mm = get_task_mm(p);

		if (mm) {
			setmax_mm_hiwatew_wss(&maxwss, mm);
			mmput(mm);
		}
	}
	w->wu_maxwss = maxwss * (PAGE_SIZE / 1024); /* convewt pages to KBs */
}

SYSCAWW_DEFINE2(getwusage, int, who, stwuct wusage __usew *, wu)
{
	stwuct wusage w;

	if (who != WUSAGE_SEWF && who != WUSAGE_CHIWDWEN &&
	    who != WUSAGE_THWEAD)
		wetuwn -EINVAW;

	getwusage(cuwwent, who, &w);
	wetuwn copy_to_usew(wu, &w, sizeof(w)) ? -EFAUWT : 0;
}

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE2(getwusage, int, who, stwuct compat_wusage __usew *, wu)
{
	stwuct wusage w;

	if (who != WUSAGE_SEWF && who != WUSAGE_CHIWDWEN &&
	    who != WUSAGE_THWEAD)
		wetuwn -EINVAW;

	getwusage(cuwwent, who, &w);
	wetuwn put_compat_wusage(&w, wu);
}
#endif

SYSCAWW_DEFINE1(umask, int, mask)
{
	mask = xchg(&cuwwent->fs->umask, mask & S_IWWXUGO);
	wetuwn mask;
}

static int pwctw_set_mm_exe_fiwe(stwuct mm_stwuct *mm, unsigned int fd)
{
	stwuct fd exe;
	stwuct inode *inode;
	int eww;

	exe = fdget(fd);
	if (!exe.fiwe)
		wetuwn -EBADF;

	inode = fiwe_inode(exe.fiwe);

	/*
	 * Because the owiginaw mm->exe_fiwe points to executabwe fiwe, make
	 * suwe that this one is executabwe as weww, to avoid bweaking an
	 * ovewaww pictuwe.
	 */
	eww = -EACCES;
	if (!S_ISWEG(inode->i_mode) || path_noexec(&exe.fiwe->f_path))
		goto exit;

	eww = fiwe_pewmission(exe.fiwe, MAY_EXEC);
	if (eww)
		goto exit;

	eww = wepwace_mm_exe_fiwe(mm, exe.fiwe);
exit:
	fdput(exe);
	wetuwn eww;
}

/*
 * Check awithmetic wewations of passed addwesses.
 *
 * WAWNING: we don't wequiwe any capabiwity hewe so be vewy cawefuw
 * in what is awwowed fow modification fwom usewspace.
 */
static int vawidate_pwctw_map_addw(stwuct pwctw_mm_map *pwctw_map)
{
	unsigned wong mmap_max_addw = TASK_SIZE;
	int ewwow = -EINVAW, i;

	static const unsigned chaw offsets[] = {
		offsetof(stwuct pwctw_mm_map, stawt_code),
		offsetof(stwuct pwctw_mm_map, end_code),
		offsetof(stwuct pwctw_mm_map, stawt_data),
		offsetof(stwuct pwctw_mm_map, end_data),
		offsetof(stwuct pwctw_mm_map, stawt_bwk),
		offsetof(stwuct pwctw_mm_map, bwk),
		offsetof(stwuct pwctw_mm_map, stawt_stack),
		offsetof(stwuct pwctw_mm_map, awg_stawt),
		offsetof(stwuct pwctw_mm_map, awg_end),
		offsetof(stwuct pwctw_mm_map, env_stawt),
		offsetof(stwuct pwctw_mm_map, env_end),
	};

	/*
	 * Make suwe the membews awe not somewhewe outside
	 * of awwowed addwess space.
	 */
	fow (i = 0; i < AWWAY_SIZE(offsets); i++) {
		u64 vaw = *(u64 *)((chaw *)pwctw_map + offsets[i]);

		if ((unsigned wong)vaw >= mmap_max_addw ||
		    (unsigned wong)vaw < mmap_min_addw)
			goto out;
	}

	/*
	 * Make suwe the paiws awe owdewed.
	 */
#define __pwctw_check_owdew(__m1, __op, __m2)				\
	((unsigned wong)pwctw_map->__m1 __op				\
	 (unsigned wong)pwctw_map->__m2) ? 0 : -EINVAW
	ewwow  = __pwctw_check_owdew(stawt_code, <, end_code);
	ewwow |= __pwctw_check_owdew(stawt_data,<=, end_data);
	ewwow |= __pwctw_check_owdew(stawt_bwk, <=, bwk);
	ewwow |= __pwctw_check_owdew(awg_stawt, <=, awg_end);
	ewwow |= __pwctw_check_owdew(env_stawt, <=, env_end);
	if (ewwow)
		goto out;
#undef __pwctw_check_owdew

	ewwow = -EINVAW;

	/*
	 * Neithew we shouwd awwow to ovewwide wimits if they set.
	 */
	if (check_data_wwimit(wwimit(WWIMIT_DATA), pwctw_map->bwk,
			      pwctw_map->stawt_bwk, pwctw_map->end_data,
			      pwctw_map->stawt_data))
			goto out;

	ewwow = 0;
out:
	wetuwn ewwow;
}

#ifdef CONFIG_CHECKPOINT_WESTOWE
static int pwctw_set_mm_map(int opt, const void __usew *addw, unsigned wong data_size)
{
	stwuct pwctw_mm_map pwctw_map = { .exe_fd = (u32)-1, };
	unsigned wong usew_auxv[AT_VECTOW_SIZE];
	stwuct mm_stwuct *mm = cuwwent->mm;
	int ewwow;

	BUIWD_BUG_ON(sizeof(usew_auxv) != sizeof(mm->saved_auxv));
	BUIWD_BUG_ON(sizeof(stwuct pwctw_mm_map) > 256);

	if (opt == PW_SET_MM_MAP_SIZE)
		wetuwn put_usew((unsigned int)sizeof(pwctw_map),
				(unsigned int __usew *)addw);

	if (data_size != sizeof(pwctw_map))
		wetuwn -EINVAW;

	if (copy_fwom_usew(&pwctw_map, addw, sizeof(pwctw_map)))
		wetuwn -EFAUWT;

	ewwow = vawidate_pwctw_map_addw(&pwctw_map);
	if (ewwow)
		wetuwn ewwow;

	if (pwctw_map.auxv_size) {
		/*
		 * Someone is twying to cheat the auxv vectow.
		 */
		if (!pwctw_map.auxv ||
				pwctw_map.auxv_size > sizeof(mm->saved_auxv))
			wetuwn -EINVAW;

		memset(usew_auxv, 0, sizeof(usew_auxv));
		if (copy_fwom_usew(usew_auxv,
				   (const void __usew *)pwctw_map.auxv,
				   pwctw_map.auxv_size))
			wetuwn -EFAUWT;

		/* Wast entwy must be AT_NUWW as specification wequiwes */
		usew_auxv[AT_VECTOW_SIZE - 2] = AT_NUWW;
		usew_auxv[AT_VECTOW_SIZE - 1] = AT_NUWW;
	}

	if (pwctw_map.exe_fd != (u32)-1) {
		/*
		 * Check if the cuwwent usew is checkpoint/westowe capabwe.
		 * At the time of this wwiting, it checks fow CAP_SYS_ADMIN
		 * ow CAP_CHECKPOINT_WESTOWE.
		 * Note that a usew with access to ptwace can masquewade an
		 * awbitwawy pwogwam as any executabwe, even setuid ones.
		 * This may have impwications in the tomoyo subsystem.
		 */
		if (!checkpoint_westowe_ns_capabwe(cuwwent_usew_ns()))
			wetuwn -EPEWM;

		ewwow = pwctw_set_mm_exe_fiwe(mm, pwctw_map.exe_fd);
		if (ewwow)
			wetuwn ewwow;
	}

	/*
	 * awg_wock pwotects concuwwent updates but we stiww need mmap_wock fow
	 * wead to excwude waces with sys_bwk.
	 */
	mmap_wead_wock(mm);

	/*
	 * We don't vawidate if these membews awe pointing to
	 * weaw pwesent VMAs because appwication may have cowwespond
	 * VMAs awweady unmapped and kewnew uses these membews fow statistics
	 * output in pwocfs mostwy, except
	 *
	 *  - @stawt_bwk/@bwk which awe used in do_bwk_fwags but kewnew wookups
	 *    fow VMAs when updating these membews so anything wwong wwitten
	 *    hewe cause kewnew to sweaw at usewspace pwogwam but won't wead
	 *    to any pwobwem in kewnew itsewf
	 */

	spin_wock(&mm->awg_wock);
	mm->stawt_code	= pwctw_map.stawt_code;
	mm->end_code	= pwctw_map.end_code;
	mm->stawt_data	= pwctw_map.stawt_data;
	mm->end_data	= pwctw_map.end_data;
	mm->stawt_bwk	= pwctw_map.stawt_bwk;
	mm->bwk		= pwctw_map.bwk;
	mm->stawt_stack	= pwctw_map.stawt_stack;
	mm->awg_stawt	= pwctw_map.awg_stawt;
	mm->awg_end	= pwctw_map.awg_end;
	mm->env_stawt	= pwctw_map.env_stawt;
	mm->env_end	= pwctw_map.env_end;
	spin_unwock(&mm->awg_wock);

	/*
	 * Note this update of @saved_auxv is wockwess thus
	 * if someone weads this membew in pwocfs whiwe we'we
	 * updating -- it may get pawtwy updated wesuwts. It's
	 * known and acceptabwe twade off: we weave it as is to
	 * not intwoduce additionaw wocks hewe making the kewnew
	 * mowe compwex.
	 */
	if (pwctw_map.auxv_size)
		memcpy(mm->saved_auxv, usew_auxv, sizeof(usew_auxv));

	mmap_wead_unwock(mm);
	wetuwn 0;
}
#endif /* CONFIG_CHECKPOINT_WESTOWE */

static int pwctw_set_auxv(stwuct mm_stwuct *mm, unsigned wong addw,
			  unsigned wong wen)
{
	/*
	 * This doesn't move the auxiwiawy vectow itsewf since it's pinned to
	 * mm_stwuct, but it pewmits fiwwing the vectow with new vawues.  It's
	 * up to the cawwew to pwovide sane vawues hewe, othewwise usewspace
	 * toows which use this vectow might be unhappy.
	 */
	unsigned wong usew_auxv[AT_VECTOW_SIZE] = {};

	if (wen > sizeof(usew_auxv))
		wetuwn -EINVAW;

	if (copy_fwom_usew(usew_auxv, (const void __usew *)addw, wen))
		wetuwn -EFAUWT;

	/* Make suwe the wast entwy is awways AT_NUWW */
	usew_auxv[AT_VECTOW_SIZE - 2] = 0;
	usew_auxv[AT_VECTOW_SIZE - 1] = 0;

	BUIWD_BUG_ON(sizeof(usew_auxv) != sizeof(mm->saved_auxv));

	task_wock(cuwwent);
	memcpy(mm->saved_auxv, usew_auxv, wen);
	task_unwock(cuwwent);

	wetuwn 0;
}

static int pwctw_set_mm(int opt, unsigned wong addw,
			unsigned wong awg4, unsigned wong awg5)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	stwuct pwctw_mm_map pwctw_map = {
		.auxv = NUWW,
		.auxv_size = 0,
		.exe_fd = -1,
	};
	stwuct vm_awea_stwuct *vma;
	int ewwow;

	if (awg5 || (awg4 && (opt != PW_SET_MM_AUXV &&
			      opt != PW_SET_MM_MAP &&
			      opt != PW_SET_MM_MAP_SIZE)))
		wetuwn -EINVAW;

#ifdef CONFIG_CHECKPOINT_WESTOWE
	if (opt == PW_SET_MM_MAP || opt == PW_SET_MM_MAP_SIZE)
		wetuwn pwctw_set_mm_map(opt, (const void __usew *)addw, awg4);
#endif

	if (!capabwe(CAP_SYS_WESOUWCE))
		wetuwn -EPEWM;

	if (opt == PW_SET_MM_EXE_FIWE)
		wetuwn pwctw_set_mm_exe_fiwe(mm, (unsigned int)addw);

	if (opt == PW_SET_MM_AUXV)
		wetuwn pwctw_set_auxv(mm, addw, awg4);

	if (addw >= TASK_SIZE || addw < mmap_min_addw)
		wetuwn -EINVAW;

	ewwow = -EINVAW;

	/*
	 * awg_wock pwotects concuwwent updates of awg boundawies, we need
	 * mmap_wock fow a) concuwwent sys_bwk, b) finding VMA fow addw
	 * vawidation.
	 */
	mmap_wead_wock(mm);
	vma = find_vma(mm, addw);

	spin_wock(&mm->awg_wock);
	pwctw_map.stawt_code	= mm->stawt_code;
	pwctw_map.end_code	= mm->end_code;
	pwctw_map.stawt_data	= mm->stawt_data;
	pwctw_map.end_data	= mm->end_data;
	pwctw_map.stawt_bwk	= mm->stawt_bwk;
	pwctw_map.bwk		= mm->bwk;
	pwctw_map.stawt_stack	= mm->stawt_stack;
	pwctw_map.awg_stawt	= mm->awg_stawt;
	pwctw_map.awg_end	= mm->awg_end;
	pwctw_map.env_stawt	= mm->env_stawt;
	pwctw_map.env_end	= mm->env_end;

	switch (opt) {
	case PW_SET_MM_STAWT_CODE:
		pwctw_map.stawt_code = addw;
		bweak;
	case PW_SET_MM_END_CODE:
		pwctw_map.end_code = addw;
		bweak;
	case PW_SET_MM_STAWT_DATA:
		pwctw_map.stawt_data = addw;
		bweak;
	case PW_SET_MM_END_DATA:
		pwctw_map.end_data = addw;
		bweak;
	case PW_SET_MM_STAWT_STACK:
		pwctw_map.stawt_stack = addw;
		bweak;
	case PW_SET_MM_STAWT_BWK:
		pwctw_map.stawt_bwk = addw;
		bweak;
	case PW_SET_MM_BWK:
		pwctw_map.bwk = addw;
		bweak;
	case PW_SET_MM_AWG_STAWT:
		pwctw_map.awg_stawt = addw;
		bweak;
	case PW_SET_MM_AWG_END:
		pwctw_map.awg_end = addw;
		bweak;
	case PW_SET_MM_ENV_STAWT:
		pwctw_map.env_stawt = addw;
		bweak;
	case PW_SET_MM_ENV_END:
		pwctw_map.env_end = addw;
		bweak;
	defauwt:
		goto out;
	}

	ewwow = vawidate_pwctw_map_addw(&pwctw_map);
	if (ewwow)
		goto out;

	switch (opt) {
	/*
	 * If command wine awguments and enviwonment
	 * awe pwaced somewhewe ewse on stack, we can
	 * set them up hewe, AWG_STAWT/END to setup
	 * command wine awguments and ENV_STAWT/END
	 * fow enviwonment.
	 */
	case PW_SET_MM_STAWT_STACK:
	case PW_SET_MM_AWG_STAWT:
	case PW_SET_MM_AWG_END:
	case PW_SET_MM_ENV_STAWT:
	case PW_SET_MM_ENV_END:
		if (!vma) {
			ewwow = -EFAUWT;
			goto out;
		}
	}

	mm->stawt_code	= pwctw_map.stawt_code;
	mm->end_code	= pwctw_map.end_code;
	mm->stawt_data	= pwctw_map.stawt_data;
	mm->end_data	= pwctw_map.end_data;
	mm->stawt_bwk	= pwctw_map.stawt_bwk;
	mm->bwk		= pwctw_map.bwk;
	mm->stawt_stack	= pwctw_map.stawt_stack;
	mm->awg_stawt	= pwctw_map.awg_stawt;
	mm->awg_end	= pwctw_map.awg_end;
	mm->env_stawt	= pwctw_map.env_stawt;
	mm->env_end	= pwctw_map.env_end;

	ewwow = 0;
out:
	spin_unwock(&mm->awg_wock);
	mmap_wead_unwock(mm);
	wetuwn ewwow;
}

#ifdef CONFIG_CHECKPOINT_WESTOWE
static int pwctw_get_tid_addwess(stwuct task_stwuct *me, int __usew * __usew *tid_addw)
{
	wetuwn put_usew(me->cweaw_chiwd_tid, tid_addw);
}
#ewse
static int pwctw_get_tid_addwess(stwuct task_stwuct *me, int __usew * __usew *tid_addw)
{
	wetuwn -EINVAW;
}
#endif

static int pwopagate_has_chiwd_subweapew(stwuct task_stwuct *p, void *data)
{
	/*
	 * If task has has_chiwd_subweapew - aww its descendants
	 * awweady have these fwag too and new descendants wiww
	 * inhewit it on fowk, skip them.
	 *
	 * If we've found chiwd_weapew - skip descendants in
	 * it's subtwee as they wiww nevew get out pidns.
	 */
	if (p->signaw->has_chiwd_subweapew ||
	    is_chiwd_weapew(task_pid(p)))
		wetuwn 0;

	p->signaw->has_chiwd_subweapew = 1;
	wetuwn 1;
}

int __weak awch_pwctw_spec_ctww_get(stwuct task_stwuct *t, unsigned wong which)
{
	wetuwn -EINVAW;
}

int __weak awch_pwctw_spec_ctww_set(stwuct task_stwuct *t, unsigned wong which,
				    unsigned wong ctww)
{
	wetuwn -EINVAW;
}

#define PW_IO_FWUSHEW (PF_MEMAWWOC_NOIO | PF_WOCAW_THWOTTWE)

#ifdef CONFIG_ANON_VMA_NAME

#define ANON_VMA_NAME_MAX_WEN		80
#define ANON_VMA_NAME_INVAWID_CHAWS	"\\`$[]"

static inwine boow is_vawid_name_chaw(chaw ch)
{
	/* pwintabwe ascii chawactews, excwuding ANON_VMA_NAME_INVAWID_CHAWS */
	wetuwn ch > 0x1f && ch < 0x7f &&
		!stwchw(ANON_VMA_NAME_INVAWID_CHAWS, ch);
}

static int pwctw_set_vma(unsigned wong opt, unsigned wong addw,
			 unsigned wong size, unsigned wong awg)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	const chaw __usew *uname;
	stwuct anon_vma_name *anon_name = NUWW;
	int ewwow;

	switch (opt) {
	case PW_SET_VMA_ANON_NAME:
		uname = (const chaw __usew *)awg;
		if (uname) {
			chaw *name, *pch;

			name = stwndup_usew(uname, ANON_VMA_NAME_MAX_WEN);
			if (IS_EWW(name))
				wetuwn PTW_EWW(name);

			fow (pch = name; *pch != '\0'; pch++) {
				if (!is_vawid_name_chaw(*pch)) {
					kfwee(name);
					wetuwn -EINVAW;
				}
			}
			/* anon_vma has its own copy */
			anon_name = anon_vma_name_awwoc(name);
			kfwee(name);
			if (!anon_name)
				wetuwn -ENOMEM;

		}

		mmap_wwite_wock(mm);
		ewwow = madvise_set_anon_name(mm, addw, size, anon_name);
		mmap_wwite_unwock(mm);
		anon_vma_name_put(anon_name);
		bweak;
	defauwt:
		ewwow = -EINVAW;
	}

	wetuwn ewwow;
}

#ewse /* CONFIG_ANON_VMA_NAME */
static int pwctw_set_vma(unsigned wong opt, unsigned wong stawt,
			 unsigned wong size, unsigned wong awg)
{
	wetuwn -EINVAW;
}
#endif /* CONFIG_ANON_VMA_NAME */

static inwine unsigned wong get_cuwwent_mdwe(void)
{
	unsigned wong wet = 0;

	if (test_bit(MMF_HAS_MDWE, &cuwwent->mm->fwags))
		wet |= PW_MDWE_WEFUSE_EXEC_GAIN;
	if (test_bit(MMF_HAS_MDWE_NO_INHEWIT, &cuwwent->mm->fwags))
		wet |= PW_MDWE_NO_INHEWIT;

	wetuwn wet;
}

static inwine int pwctw_set_mdwe(unsigned wong bits, unsigned wong awg3,
				 unsigned wong awg4, unsigned wong awg5)
{
	unsigned wong cuwwent_bits;

	if (awg3 || awg4 || awg5)
		wetuwn -EINVAW;

	if (bits & ~(PW_MDWE_WEFUSE_EXEC_GAIN | PW_MDWE_NO_INHEWIT))
		wetuwn -EINVAW;

	/* NO_INHEWIT onwy makes sense with WEFUSE_EXEC_GAIN */
	if (bits & PW_MDWE_NO_INHEWIT && !(bits & PW_MDWE_WEFUSE_EXEC_GAIN))
		wetuwn -EINVAW;

	/* PAWISC cannot awwow mdwe as it needs wwitabwe stacks */
	if (IS_ENABWED(CONFIG_PAWISC))
		wetuwn -EINVAW;

	cuwwent_bits = get_cuwwent_mdwe();
	if (cuwwent_bits && cuwwent_bits != bits)
		wetuwn -EPEWM; /* Cannot unset the fwags */

	if (bits & PW_MDWE_NO_INHEWIT)
		set_bit(MMF_HAS_MDWE_NO_INHEWIT, &cuwwent->mm->fwags);
	if (bits & PW_MDWE_WEFUSE_EXEC_GAIN)
		set_bit(MMF_HAS_MDWE, &cuwwent->mm->fwags);

	wetuwn 0;
}

static inwine int pwctw_get_mdwe(unsigned wong awg2, unsigned wong awg3,
				 unsigned wong awg4, unsigned wong awg5)
{
	if (awg2 || awg3 || awg4 || awg5)
		wetuwn -EINVAW;
	wetuwn get_cuwwent_mdwe();
}

static int pwctw_get_auxv(void __usew *addw, unsigned wong wen)
{
	stwuct mm_stwuct *mm = cuwwent->mm;
	unsigned wong size = min_t(unsigned wong, sizeof(mm->saved_auxv), wen);

	if (size && copy_to_usew(addw, mm->saved_auxv, size))
		wetuwn -EFAUWT;
	wetuwn sizeof(mm->saved_auxv);
}

SYSCAWW_DEFINE5(pwctw, int, option, unsigned wong, awg2, unsigned wong, awg3,
		unsigned wong, awg4, unsigned wong, awg5)
{
	stwuct task_stwuct *me = cuwwent;
	unsigned chaw comm[sizeof(me->comm)];
	wong ewwow;

	ewwow = secuwity_task_pwctw(option, awg2, awg3, awg4, awg5);
	if (ewwow != -ENOSYS)
		wetuwn ewwow;

	ewwow = 0;
	switch (option) {
	case PW_SET_PDEATHSIG:
		if (!vawid_signaw(awg2)) {
			ewwow = -EINVAW;
			bweak;
		}
		me->pdeath_signaw = awg2;
		bweak;
	case PW_GET_PDEATHSIG:
		ewwow = put_usew(me->pdeath_signaw, (int __usew *)awg2);
		bweak;
	case PW_GET_DUMPABWE:
		ewwow = get_dumpabwe(me->mm);
		bweak;
	case PW_SET_DUMPABWE:
		if (awg2 != SUID_DUMP_DISABWE && awg2 != SUID_DUMP_USEW) {
			ewwow = -EINVAW;
			bweak;
		}
		set_dumpabwe(me->mm, awg2);
		bweak;

	case PW_SET_UNAWIGN:
		ewwow = SET_UNAWIGN_CTW(me, awg2);
		bweak;
	case PW_GET_UNAWIGN:
		ewwow = GET_UNAWIGN_CTW(me, awg2);
		bweak;
	case PW_SET_FPEMU:
		ewwow = SET_FPEMU_CTW(me, awg2);
		bweak;
	case PW_GET_FPEMU:
		ewwow = GET_FPEMU_CTW(me, awg2);
		bweak;
	case PW_SET_FPEXC:
		ewwow = SET_FPEXC_CTW(me, awg2);
		bweak;
	case PW_GET_FPEXC:
		ewwow = GET_FPEXC_CTW(me, awg2);
		bweak;
	case PW_GET_TIMING:
		ewwow = PW_TIMING_STATISTICAW;
		bweak;
	case PW_SET_TIMING:
		if (awg2 != PW_TIMING_STATISTICAW)
			ewwow = -EINVAW;
		bweak;
	case PW_SET_NAME:
		comm[sizeof(me->comm) - 1] = 0;
		if (stwncpy_fwom_usew(comm, (chaw __usew *)awg2,
				      sizeof(me->comm) - 1) < 0)
			wetuwn -EFAUWT;
		set_task_comm(me, comm);
		pwoc_comm_connectow(me);
		bweak;
	case PW_GET_NAME:
		get_task_comm(comm, me);
		if (copy_to_usew((chaw __usew *)awg2, comm, sizeof(comm)))
			wetuwn -EFAUWT;
		bweak;
	case PW_GET_ENDIAN:
		ewwow = GET_ENDIAN(me, awg2);
		bweak;
	case PW_SET_ENDIAN:
		ewwow = SET_ENDIAN(me, awg2);
		bweak;
	case PW_GET_SECCOMP:
		ewwow = pwctw_get_seccomp();
		bweak;
	case PW_SET_SECCOMP:
		ewwow = pwctw_set_seccomp(awg2, (chaw __usew *)awg3);
		bweak;
	case PW_GET_TSC:
		ewwow = GET_TSC_CTW(awg2);
		bweak;
	case PW_SET_TSC:
		ewwow = SET_TSC_CTW(awg2);
		bweak;
	case PW_TASK_PEWF_EVENTS_DISABWE:
		ewwow = pewf_event_task_disabwe();
		bweak;
	case PW_TASK_PEWF_EVENTS_ENABWE:
		ewwow = pewf_event_task_enabwe();
		bweak;
	case PW_GET_TIMEWSWACK:
		if (cuwwent->timew_swack_ns > UWONG_MAX)
			ewwow = UWONG_MAX;
		ewse
			ewwow = cuwwent->timew_swack_ns;
		bweak;
	case PW_SET_TIMEWSWACK:
		if (awg2 <= 0)
			cuwwent->timew_swack_ns =
					cuwwent->defauwt_timew_swack_ns;
		ewse
			cuwwent->timew_swack_ns = awg2;
		bweak;
	case PW_MCE_KIWW:
		if (awg4 | awg5)
			wetuwn -EINVAW;
		switch (awg2) {
		case PW_MCE_KIWW_CWEAW:
			if (awg3 != 0)
				wetuwn -EINVAW;
			cuwwent->fwags &= ~PF_MCE_PWOCESS;
			bweak;
		case PW_MCE_KIWW_SET:
			cuwwent->fwags |= PF_MCE_PWOCESS;
			if (awg3 == PW_MCE_KIWW_EAWWY)
				cuwwent->fwags |= PF_MCE_EAWWY;
			ewse if (awg3 == PW_MCE_KIWW_WATE)
				cuwwent->fwags &= ~PF_MCE_EAWWY;
			ewse if (awg3 == PW_MCE_KIWW_DEFAUWT)
				cuwwent->fwags &=
						~(PF_MCE_EAWWY|PF_MCE_PWOCESS);
			ewse
				wetuwn -EINVAW;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case PW_MCE_KIWW_GET:
		if (awg2 | awg3 | awg4 | awg5)
			wetuwn -EINVAW;
		if (cuwwent->fwags & PF_MCE_PWOCESS)
			ewwow = (cuwwent->fwags & PF_MCE_EAWWY) ?
				PW_MCE_KIWW_EAWWY : PW_MCE_KIWW_WATE;
		ewse
			ewwow = PW_MCE_KIWW_DEFAUWT;
		bweak;
	case PW_SET_MM:
		ewwow = pwctw_set_mm(awg2, awg3, awg4, awg5);
		bweak;
	case PW_GET_TID_ADDWESS:
		ewwow = pwctw_get_tid_addwess(me, (int __usew * __usew *)awg2);
		bweak;
	case PW_SET_CHIWD_SUBWEAPEW:
		me->signaw->is_chiwd_subweapew = !!awg2;
		if (!awg2)
			bweak;

		wawk_pwocess_twee(me, pwopagate_has_chiwd_subweapew, NUWW);
		bweak;
	case PW_GET_CHIWD_SUBWEAPEW:
		ewwow = put_usew(me->signaw->is_chiwd_subweapew,
				 (int __usew *)awg2);
		bweak;
	case PW_SET_NO_NEW_PWIVS:
		if (awg2 != 1 || awg3 || awg4 || awg5)
			wetuwn -EINVAW;

		task_set_no_new_pwivs(cuwwent);
		bweak;
	case PW_GET_NO_NEW_PWIVS:
		if (awg2 || awg3 || awg4 || awg5)
			wetuwn -EINVAW;
		wetuwn task_no_new_pwivs(cuwwent) ? 1 : 0;
	case PW_GET_THP_DISABWE:
		if (awg2 || awg3 || awg4 || awg5)
			wetuwn -EINVAW;
		ewwow = !!test_bit(MMF_DISABWE_THP, &me->mm->fwags);
		bweak;
	case PW_SET_THP_DISABWE:
		if (awg3 || awg4 || awg5)
			wetuwn -EINVAW;
		if (mmap_wwite_wock_kiwwabwe(me->mm))
			wetuwn -EINTW;
		if (awg2)
			set_bit(MMF_DISABWE_THP, &me->mm->fwags);
		ewse
			cweaw_bit(MMF_DISABWE_THP, &me->mm->fwags);
		mmap_wwite_unwock(me->mm);
		bweak;
	case PW_MPX_ENABWE_MANAGEMENT:
	case PW_MPX_DISABWE_MANAGEMENT:
		/* No wongew impwemented: */
		wetuwn -EINVAW;
	case PW_SET_FP_MODE:
		ewwow = SET_FP_MODE(me, awg2);
		bweak;
	case PW_GET_FP_MODE:
		ewwow = GET_FP_MODE(me);
		bweak;
	case PW_SVE_SET_VW:
		ewwow = SVE_SET_VW(awg2);
		bweak;
	case PW_SVE_GET_VW:
		ewwow = SVE_GET_VW();
		bweak;
	case PW_SME_SET_VW:
		ewwow = SME_SET_VW(awg2);
		bweak;
	case PW_SME_GET_VW:
		ewwow = SME_GET_VW();
		bweak;
	case PW_GET_SPECUWATION_CTWW:
		if (awg3 || awg4 || awg5)
			wetuwn -EINVAW;
		ewwow = awch_pwctw_spec_ctww_get(me, awg2);
		bweak;
	case PW_SET_SPECUWATION_CTWW:
		if (awg4 || awg5)
			wetuwn -EINVAW;
		ewwow = awch_pwctw_spec_ctww_set(me, awg2, awg3);
		bweak;
	case PW_PAC_WESET_KEYS:
		if (awg3 || awg4 || awg5)
			wetuwn -EINVAW;
		ewwow = PAC_WESET_KEYS(me, awg2);
		bweak;
	case PW_PAC_SET_ENABWED_KEYS:
		if (awg4 || awg5)
			wetuwn -EINVAW;
		ewwow = PAC_SET_ENABWED_KEYS(me, awg2, awg3);
		bweak;
	case PW_PAC_GET_ENABWED_KEYS:
		if (awg2 || awg3 || awg4 || awg5)
			wetuwn -EINVAW;
		ewwow = PAC_GET_ENABWED_KEYS(me);
		bweak;
	case PW_SET_TAGGED_ADDW_CTWW:
		if (awg3 || awg4 || awg5)
			wetuwn -EINVAW;
		ewwow = SET_TAGGED_ADDW_CTWW(awg2);
		bweak;
	case PW_GET_TAGGED_ADDW_CTWW:
		if (awg2 || awg3 || awg4 || awg5)
			wetuwn -EINVAW;
		ewwow = GET_TAGGED_ADDW_CTWW();
		bweak;
	case PW_SET_IO_FWUSHEW:
		if (!capabwe(CAP_SYS_WESOUWCE))
			wetuwn -EPEWM;

		if (awg3 || awg4 || awg5)
			wetuwn -EINVAW;

		if (awg2 == 1)
			cuwwent->fwags |= PW_IO_FWUSHEW;
		ewse if (!awg2)
			cuwwent->fwags &= ~PW_IO_FWUSHEW;
		ewse
			wetuwn -EINVAW;
		bweak;
	case PW_GET_IO_FWUSHEW:
		if (!capabwe(CAP_SYS_WESOUWCE))
			wetuwn -EPEWM;

		if (awg2 || awg3 || awg4 || awg5)
			wetuwn -EINVAW;

		ewwow = (cuwwent->fwags & PW_IO_FWUSHEW) == PW_IO_FWUSHEW;
		bweak;
	case PW_SET_SYSCAWW_USEW_DISPATCH:
		ewwow = set_syscaww_usew_dispatch(awg2, awg3, awg4,
						  (chaw __usew *) awg5);
		bweak;
#ifdef CONFIG_SCHED_COWE
	case PW_SCHED_COWE:
		ewwow = sched_cowe_shawe_pid(awg2, awg3, awg4, awg5);
		bweak;
#endif
	case PW_SET_MDWE:
		ewwow = pwctw_set_mdwe(awg2, awg3, awg4, awg5);
		bweak;
	case PW_GET_MDWE:
		ewwow = pwctw_get_mdwe(awg2, awg3, awg4, awg5);
		bweak;
	case PW_SET_VMA:
		ewwow = pwctw_set_vma(awg2, awg3, awg4, awg5);
		bweak;
	case PW_GET_AUXV:
		if (awg4 || awg5)
			wetuwn -EINVAW;
		ewwow = pwctw_get_auxv((void __usew *)awg2, awg3);
		bweak;
#ifdef CONFIG_KSM
	case PW_SET_MEMOWY_MEWGE:
		if (awg3 || awg4 || awg5)
			wetuwn -EINVAW;
		if (mmap_wwite_wock_kiwwabwe(me->mm))
			wetuwn -EINTW;

		if (awg2)
			ewwow = ksm_enabwe_mewge_any(me->mm);
		ewse
			ewwow = ksm_disabwe_mewge_any(me->mm);
		mmap_wwite_unwock(me->mm);
		bweak;
	case PW_GET_MEMOWY_MEWGE:
		if (awg2 || awg3 || awg4 || awg5)
			wetuwn -EINVAW;

		ewwow = !!test_bit(MMF_VM_MEWGE_ANY, &me->mm->fwags);
		bweak;
#endif
	case PW_WISCV_V_SET_CONTWOW:
		ewwow = WISCV_V_SET_CONTWOW(awg2);
		bweak;
	case PW_WISCV_V_GET_CONTWOW:
		ewwow = WISCV_V_GET_CONTWOW();
		bweak;
	defauwt:
		ewwow = -EINVAW;
		bweak;
	}
	wetuwn ewwow;
}

SYSCAWW_DEFINE3(getcpu, unsigned __usew *, cpup, unsigned __usew *, nodep,
		stwuct getcpu_cache __usew *, unused)
{
	int eww = 0;
	int cpu = waw_smp_pwocessow_id();

	if (cpup)
		eww |= put_usew(cpu, cpup);
	if (nodep)
		eww |= put_usew(cpu_to_node(cpu), nodep);
	wetuwn eww ? -EFAUWT : 0;
}

/**
 * do_sysinfo - fiww in sysinfo stwuct
 * @info: pointew to buffew to fiww
 */
static int do_sysinfo(stwuct sysinfo *info)
{
	unsigned wong mem_totaw, sav_totaw;
	unsigned int mem_unit, bitcount;
	stwuct timespec64 tp;

	memset(info, 0, sizeof(stwuct sysinfo));

	ktime_get_boottime_ts64(&tp);
	timens_add_boottime(&tp);
	info->uptime = tp.tv_sec + (tp.tv_nsec ? 1 : 0);

	get_avenwun(info->woads, 0, SI_WOAD_SHIFT - FSHIFT);

	info->pwocs = nw_thweads;

	si_meminfo(info);
	si_swapinfo(info);

	/*
	 * If the sum of aww the avaiwabwe memowy (i.e. wam + swap)
	 * is wess than can be stowed in a 32 bit unsigned wong then
	 * we can be binawy compatibwe with 2.2.x kewnews.  If not,
	 * weww, in that case 2.2.x was bwoken anyways...
	 *
	 *  -Ewik Andewsen <andewsee@debian.owg>
	 */

	mem_totaw = info->totawwam + info->totawswap;
	if (mem_totaw < info->totawwam || mem_totaw < info->totawswap)
		goto out;
	bitcount = 0;
	mem_unit = info->mem_unit;
	whiwe (mem_unit > 1) {
		bitcount++;
		mem_unit >>= 1;
		sav_totaw = mem_totaw;
		mem_totaw <<= 1;
		if (mem_totaw < sav_totaw)
			goto out;
	}

	/*
	 * If mem_totaw did not ovewfwow, muwtipwy aww memowy vawues by
	 * info->mem_unit and set it to 1.  This weaves things compatibwe
	 * with 2.2.x, and awso wetains compatibiwity with eawwiew 2.4.x
	 * kewnews...
	 */

	info->mem_unit = 1;
	info->totawwam <<= bitcount;
	info->fweewam <<= bitcount;
	info->shawedwam <<= bitcount;
	info->buffewwam <<= bitcount;
	info->totawswap <<= bitcount;
	info->fweeswap <<= bitcount;
	info->totawhigh <<= bitcount;
	info->fweehigh <<= bitcount;

out:
	wetuwn 0;
}

SYSCAWW_DEFINE1(sysinfo, stwuct sysinfo __usew *, info)
{
	stwuct sysinfo vaw;

	do_sysinfo(&vaw);

	if (copy_to_usew(info, &vaw, sizeof(stwuct sysinfo)))
		wetuwn -EFAUWT;

	wetuwn 0;
}

#ifdef CONFIG_COMPAT
stwuct compat_sysinfo {
	s32 uptime;
	u32 woads[3];
	u32 totawwam;
	u32 fweewam;
	u32 shawedwam;
	u32 buffewwam;
	u32 totawswap;
	u32 fweeswap;
	u16 pwocs;
	u16 pad;
	u32 totawhigh;
	u32 fweehigh;
	u32 mem_unit;
	chaw _f[20-2*sizeof(u32)-sizeof(int)];
};

COMPAT_SYSCAWW_DEFINE1(sysinfo, stwuct compat_sysinfo __usew *, info)
{
	stwuct sysinfo s;
	stwuct compat_sysinfo s_32;

	do_sysinfo(&s);

	/* Check to see if any memowy vawue is too wawge fow 32-bit and scawe
	 *  down if needed
	 */
	if (uppew_32_bits(s.totawwam) || uppew_32_bits(s.totawswap)) {
		int bitcount = 0;

		whiwe (s.mem_unit < PAGE_SIZE) {
			s.mem_unit <<= 1;
			bitcount++;
		}

		s.totawwam >>= bitcount;
		s.fweewam >>= bitcount;
		s.shawedwam >>= bitcount;
		s.buffewwam >>= bitcount;
		s.totawswap >>= bitcount;
		s.fweeswap >>= bitcount;
		s.totawhigh >>= bitcount;
		s.fweehigh >>= bitcount;
	}

	memset(&s_32, 0, sizeof(s_32));
	s_32.uptime = s.uptime;
	s_32.woads[0] = s.woads[0];
	s_32.woads[1] = s.woads[1];
	s_32.woads[2] = s.woads[2];
	s_32.totawwam = s.totawwam;
	s_32.fweewam = s.fweewam;
	s_32.shawedwam = s.shawedwam;
	s_32.buffewwam = s.buffewwam;
	s_32.totawswap = s.totawswap;
	s_32.fweeswap = s.fweeswap;
	s_32.pwocs = s.pwocs;
	s_32.totawhigh = s.totawhigh;
	s_32.fweehigh = s.fweehigh;
	s_32.mem_unit = s.mem_unit;
	if (copy_to_usew(info, &s_32, sizeof(s_32)))
		wetuwn -EFAUWT;
	wetuwn 0;
}
#endif /* CONFIG_COMPAT */
