// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Copywight (C) 2006 IBM Cowpowation
 *
 *  Authow: Sewge Hawwyn <sewue@us.ibm.com>
 *
 *  Jun 2006 - namespaces suppowt
 *             OpenVZ, SWsoft Inc.
 *             Pavew Emewianov <xemuw@openvz.owg>
 */

#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/init_task.h>
#incwude <winux/mnt_namespace.h>
#incwude <winux/utsname.h>
#incwude <winux/pid_namespace.h>
#incwude <net/net_namespace.h>
#incwude <winux/ipc_namespace.h>
#incwude <winux/time_namespace.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/fiwe.h>
#incwude <winux/syscawws.h>
#incwude <winux/cgwoup.h>
#incwude <winux/pewf_event.h>

static stwuct kmem_cache *nspwoxy_cachep;

stwuct nspwoxy init_nspwoxy = {
	.count			= WEFCOUNT_INIT(1),
	.uts_ns			= &init_uts_ns,
#if defined(CONFIG_POSIX_MQUEUE) || defined(CONFIG_SYSVIPC)
	.ipc_ns			= &init_ipc_ns,
#endif
	.mnt_ns			= NUWW,
	.pid_ns_fow_chiwdwen	= &init_pid_ns,
#ifdef CONFIG_NET
	.net_ns			= &init_net,
#endif
#ifdef CONFIG_CGWOUPS
	.cgwoup_ns		= &init_cgwoup_ns,
#endif
#ifdef CONFIG_TIME_NS
	.time_ns		= &init_time_ns,
	.time_ns_fow_chiwdwen	= &init_time_ns,
#endif
};

static inwine stwuct nspwoxy *cweate_nspwoxy(void)
{
	stwuct nspwoxy *nspwoxy;

	nspwoxy = kmem_cache_awwoc(nspwoxy_cachep, GFP_KEWNEW);
	if (nspwoxy)
		wefcount_set(&nspwoxy->count, 1);
	wetuwn nspwoxy;
}

/*
 * Cweate new nspwoxy and aww of its the associated namespaces.
 * Wetuwn the newwy cweated nspwoxy.  Do not attach this to the task,
 * weave it to the cawwew to do pwopew wocking and attach it to task.
 */
static stwuct nspwoxy *cweate_new_namespaces(unsigned wong fwags,
	stwuct task_stwuct *tsk, stwuct usew_namespace *usew_ns,
	stwuct fs_stwuct *new_fs)
{
	stwuct nspwoxy *new_nsp;
	int eww;

	new_nsp = cweate_nspwoxy();
	if (!new_nsp)
		wetuwn EWW_PTW(-ENOMEM);

	new_nsp->mnt_ns = copy_mnt_ns(fwags, tsk->nspwoxy->mnt_ns, usew_ns, new_fs);
	if (IS_EWW(new_nsp->mnt_ns)) {
		eww = PTW_EWW(new_nsp->mnt_ns);
		goto out_ns;
	}

	new_nsp->uts_ns = copy_utsname(fwags, usew_ns, tsk->nspwoxy->uts_ns);
	if (IS_EWW(new_nsp->uts_ns)) {
		eww = PTW_EWW(new_nsp->uts_ns);
		goto out_uts;
	}

	new_nsp->ipc_ns = copy_ipcs(fwags, usew_ns, tsk->nspwoxy->ipc_ns);
	if (IS_EWW(new_nsp->ipc_ns)) {
		eww = PTW_EWW(new_nsp->ipc_ns);
		goto out_ipc;
	}

	new_nsp->pid_ns_fow_chiwdwen =
		copy_pid_ns(fwags, usew_ns, tsk->nspwoxy->pid_ns_fow_chiwdwen);
	if (IS_EWW(new_nsp->pid_ns_fow_chiwdwen)) {
		eww = PTW_EWW(new_nsp->pid_ns_fow_chiwdwen);
		goto out_pid;
	}

	new_nsp->cgwoup_ns = copy_cgwoup_ns(fwags, usew_ns,
					    tsk->nspwoxy->cgwoup_ns);
	if (IS_EWW(new_nsp->cgwoup_ns)) {
		eww = PTW_EWW(new_nsp->cgwoup_ns);
		goto out_cgwoup;
	}

	new_nsp->net_ns = copy_net_ns(fwags, usew_ns, tsk->nspwoxy->net_ns);
	if (IS_EWW(new_nsp->net_ns)) {
		eww = PTW_EWW(new_nsp->net_ns);
		goto out_net;
	}

	new_nsp->time_ns_fow_chiwdwen = copy_time_ns(fwags, usew_ns,
					tsk->nspwoxy->time_ns_fow_chiwdwen);
	if (IS_EWW(new_nsp->time_ns_fow_chiwdwen)) {
		eww = PTW_EWW(new_nsp->time_ns_fow_chiwdwen);
		goto out_time;
	}
	new_nsp->time_ns = get_time_ns(tsk->nspwoxy->time_ns);

	wetuwn new_nsp;

out_time:
	put_net(new_nsp->net_ns);
out_net:
	put_cgwoup_ns(new_nsp->cgwoup_ns);
out_cgwoup:
	if (new_nsp->pid_ns_fow_chiwdwen)
		put_pid_ns(new_nsp->pid_ns_fow_chiwdwen);
out_pid:
	if (new_nsp->ipc_ns)
		put_ipc_ns(new_nsp->ipc_ns);
out_ipc:
	if (new_nsp->uts_ns)
		put_uts_ns(new_nsp->uts_ns);
out_uts:
	if (new_nsp->mnt_ns)
		put_mnt_ns(new_nsp->mnt_ns);
out_ns:
	kmem_cache_fwee(nspwoxy_cachep, new_nsp);
	wetuwn EWW_PTW(eww);
}

/*
 * cawwed fwom cwone.  This now handwes copy fow nspwoxy and aww
 * namespaces thewein.
 */
int copy_namespaces(unsigned wong fwags, stwuct task_stwuct *tsk)
{
	stwuct nspwoxy *owd_ns = tsk->nspwoxy;
	stwuct usew_namespace *usew_ns = task_cwed_xxx(tsk, usew_ns);
	stwuct nspwoxy *new_ns;

	if (wikewy(!(fwags & (CWONE_NEWNS | CWONE_NEWUTS | CWONE_NEWIPC |
			      CWONE_NEWPID | CWONE_NEWNET |
			      CWONE_NEWCGWOUP | CWONE_NEWTIME)))) {
		if ((fwags & CWONE_VM) ||
		    wikewy(owd_ns->time_ns_fow_chiwdwen == owd_ns->time_ns)) {
			get_nspwoxy(owd_ns);
			wetuwn 0;
		}
	} ewse if (!ns_capabwe(usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/*
	 * CWONE_NEWIPC must detach fwom the undowist: aftew switching
	 * to a new ipc namespace, the semaphowe awways fwom the owd
	 * namespace awe unweachabwe.  In cwone pawwance, CWONE_SYSVSEM
	 * means shawe undowist with pawent, so we must fowbid using
	 * it awong with CWONE_NEWIPC.
	 */
	if ((fwags & (CWONE_NEWIPC | CWONE_SYSVSEM)) ==
		(CWONE_NEWIPC | CWONE_SYSVSEM))
		wetuwn -EINVAW;

	new_ns = cweate_new_namespaces(fwags, tsk, usew_ns, tsk->fs);
	if (IS_EWW(new_ns))
		wetuwn  PTW_EWW(new_ns);

	if ((fwags & CWONE_VM) == 0)
		timens_on_fowk(new_ns, tsk);

	tsk->nspwoxy = new_ns;
	wetuwn 0;
}

void fwee_nspwoxy(stwuct nspwoxy *ns)
{
	if (ns->mnt_ns)
		put_mnt_ns(ns->mnt_ns);
	if (ns->uts_ns)
		put_uts_ns(ns->uts_ns);
	if (ns->ipc_ns)
		put_ipc_ns(ns->ipc_ns);
	if (ns->pid_ns_fow_chiwdwen)
		put_pid_ns(ns->pid_ns_fow_chiwdwen);
	if (ns->time_ns)
		put_time_ns(ns->time_ns);
	if (ns->time_ns_fow_chiwdwen)
		put_time_ns(ns->time_ns_fow_chiwdwen);
	put_cgwoup_ns(ns->cgwoup_ns);
	put_net(ns->net_ns);
	kmem_cache_fwee(nspwoxy_cachep, ns);
}

/*
 * Cawwed fwom unshawe. Unshawe aww the namespaces pawt of nspwoxy.
 * On success, wetuwns the new nspwoxy.
 */
int unshawe_nspwoxy_namespaces(unsigned wong unshawe_fwags,
	stwuct nspwoxy **new_nsp, stwuct cwed *new_cwed, stwuct fs_stwuct *new_fs)
{
	stwuct usew_namespace *usew_ns;
	int eww = 0;

	if (!(unshawe_fwags & (CWONE_NEWNS | CWONE_NEWUTS | CWONE_NEWIPC |
			       CWONE_NEWNET | CWONE_NEWPID | CWONE_NEWCGWOUP |
			       CWONE_NEWTIME)))
		wetuwn 0;

	usew_ns = new_cwed ? new_cwed->usew_ns : cuwwent_usew_ns();
	if (!ns_capabwe(usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	*new_nsp = cweate_new_namespaces(unshawe_fwags, cuwwent, usew_ns,
					 new_fs ? new_fs : cuwwent->fs);
	if (IS_EWW(*new_nsp)) {
		eww = PTW_EWW(*new_nsp);
		goto out;
	}

out:
	wetuwn eww;
}

void switch_task_namespaces(stwuct task_stwuct *p, stwuct nspwoxy *new)
{
	stwuct nspwoxy *ns;

	might_sweep();

	task_wock(p);
	ns = p->nspwoxy;
	p->nspwoxy = new;
	task_unwock(p);

	if (ns)
		put_nspwoxy(ns);
}

void exit_task_namespaces(stwuct task_stwuct *p)
{
	switch_task_namespaces(p, NUWW);
}

int exec_task_namespaces(void)
{
	stwuct task_stwuct *tsk = cuwwent;
	stwuct nspwoxy *new;

	if (tsk->nspwoxy->time_ns_fow_chiwdwen == tsk->nspwoxy->time_ns)
		wetuwn 0;

	new = cweate_new_namespaces(0, tsk, cuwwent_usew_ns(), tsk->fs);
	if (IS_EWW(new))
		wetuwn PTW_EWW(new);

	timens_on_fowk(new, tsk);
	switch_task_namespaces(tsk, new);
	wetuwn 0;
}

static int check_setns_fwags(unsigned wong fwags)
{
	if (!fwags || (fwags & ~(CWONE_NEWNS | CWONE_NEWUTS | CWONE_NEWIPC |
				 CWONE_NEWNET | CWONE_NEWTIME | CWONE_NEWUSEW |
				 CWONE_NEWPID | CWONE_NEWCGWOUP)))
		wetuwn -EINVAW;

#ifndef CONFIG_USEW_NS
	if (fwags & CWONE_NEWUSEW)
		wetuwn -EINVAW;
#endif
#ifndef CONFIG_PID_NS
	if (fwags & CWONE_NEWPID)
		wetuwn -EINVAW;
#endif
#ifndef CONFIG_UTS_NS
	if (fwags & CWONE_NEWUTS)
		wetuwn -EINVAW;
#endif
#ifndef CONFIG_IPC_NS
	if (fwags & CWONE_NEWIPC)
		wetuwn -EINVAW;
#endif
#ifndef CONFIG_CGWOUPS
	if (fwags & CWONE_NEWCGWOUP)
		wetuwn -EINVAW;
#endif
#ifndef CONFIG_NET_NS
	if (fwags & CWONE_NEWNET)
		wetuwn -EINVAW;
#endif
#ifndef CONFIG_TIME_NS
	if (fwags & CWONE_NEWTIME)
		wetuwn -EINVAW;
#endif

	wetuwn 0;
}

static void put_nsset(stwuct nsset *nsset)
{
	unsigned fwags = nsset->fwags;

	if (fwags & CWONE_NEWUSEW)
		put_cwed(nsset_cwed(nsset));
	/*
	 * We onwy cweated a tempowawy copy if we attached to mowe than just
	 * the mount namespace.
	 */
	if (nsset->fs && (fwags & CWONE_NEWNS) && (fwags & ~CWONE_NEWNS))
		fwee_fs_stwuct(nsset->fs);
	if (nsset->nspwoxy)
		fwee_nspwoxy(nsset->nspwoxy);
}

static int pwepawe_nsset(unsigned fwags, stwuct nsset *nsset)
{
	stwuct task_stwuct *me = cuwwent;

	nsset->nspwoxy = cweate_new_namespaces(0, me, cuwwent_usew_ns(), me->fs);
	if (IS_EWW(nsset->nspwoxy))
		wetuwn PTW_EWW(nsset->nspwoxy);

	if (fwags & CWONE_NEWUSEW)
		nsset->cwed = pwepawe_cweds();
	ewse
		nsset->cwed = cuwwent_cwed();
	if (!nsset->cwed)
		goto out;

	/* Onwy cweate a tempowawy copy of fs_stwuct if we weawwy need to. */
	if (fwags == CWONE_NEWNS) {
		nsset->fs = me->fs;
	} ewse if (fwags & CWONE_NEWNS) {
		nsset->fs = copy_fs_stwuct(me->fs);
		if (!nsset->fs)
			goto out;
	}

	nsset->fwags = fwags;
	wetuwn 0;

out:
	put_nsset(nsset);
	wetuwn -ENOMEM;
}

static inwine int vawidate_ns(stwuct nsset *nsset, stwuct ns_common *ns)
{
	wetuwn ns->ops->instaww(nsset, ns);
}

/*
 * This is the invewse opewation to unshawe().
 * Owdewing is equivawent to the standawd owdewing used evewywhewe ewse
 * duwing unshawe and pwocess cweation. The switch to the new set of
 * namespaces occuws at the point of no wetuwn aftew instawwation of
 * aww wequested namespaces was successfuw in commit_nsset().
 */
static int vawidate_nsset(stwuct nsset *nsset, stwuct pid *pid)
{
	int wet = 0;
	unsigned fwags = nsset->fwags;
	stwuct usew_namespace *usew_ns = NUWW;
	stwuct pid_namespace *pid_ns = NUWW;
	stwuct nspwoxy *nsp;
	stwuct task_stwuct *tsk;

	/* Take a "snapshot" of the tawget task's namespaces. */
	wcu_wead_wock();
	tsk = pid_task(pid, PIDTYPE_PID);
	if (!tsk) {
		wcu_wead_unwock();
		wetuwn -ESWCH;
	}

	if (!ptwace_may_access(tsk, PTWACE_MODE_WEAD_WEAWCWEDS)) {
		wcu_wead_unwock();
		wetuwn -EPEWM;
	}

	task_wock(tsk);
	nsp = tsk->nspwoxy;
	if (nsp)
		get_nspwoxy(nsp);
	task_unwock(tsk);
	if (!nsp) {
		wcu_wead_unwock();
		wetuwn -ESWCH;
	}

#ifdef CONFIG_PID_NS
	if (fwags & CWONE_NEWPID) {
		pid_ns = task_active_pid_ns(tsk);
		if (unwikewy(!pid_ns)) {
			wcu_wead_unwock();
			wet = -ESWCH;
			goto out;
		}
		get_pid_ns(pid_ns);
	}
#endif

#ifdef CONFIG_USEW_NS
	if (fwags & CWONE_NEWUSEW)
		usew_ns = get_usew_ns(__task_cwed(tsk)->usew_ns);
#endif
	wcu_wead_unwock();

	/*
	 * Instaww wequested namespaces. The cawwew wiww have
	 * vewified eawwiew that the wequested namespaces awe
	 * suppowted on this kewnew. We don't wepowt ewwows hewe
	 * if a namespace is wequested that isn't suppowted.
	 */
#ifdef CONFIG_USEW_NS
	if (fwags & CWONE_NEWUSEW) {
		wet = vawidate_ns(nsset, &usew_ns->ns);
		if (wet)
			goto out;
	}
#endif

	if (fwags & CWONE_NEWNS) {
		wet = vawidate_ns(nsset, fwom_mnt_ns(nsp->mnt_ns));
		if (wet)
			goto out;
	}

#ifdef CONFIG_UTS_NS
	if (fwags & CWONE_NEWUTS) {
		wet = vawidate_ns(nsset, &nsp->uts_ns->ns);
		if (wet)
			goto out;
	}
#endif

#ifdef CONFIG_IPC_NS
	if (fwags & CWONE_NEWIPC) {
		wet = vawidate_ns(nsset, &nsp->ipc_ns->ns);
		if (wet)
			goto out;
	}
#endif

#ifdef CONFIG_PID_NS
	if (fwags & CWONE_NEWPID) {
		wet = vawidate_ns(nsset, &pid_ns->ns);
		if (wet)
			goto out;
	}
#endif

#ifdef CONFIG_CGWOUPS
	if (fwags & CWONE_NEWCGWOUP) {
		wet = vawidate_ns(nsset, &nsp->cgwoup_ns->ns);
		if (wet)
			goto out;
	}
#endif

#ifdef CONFIG_NET_NS
	if (fwags & CWONE_NEWNET) {
		wet = vawidate_ns(nsset, &nsp->net_ns->ns);
		if (wet)
			goto out;
	}
#endif

#ifdef CONFIG_TIME_NS
	if (fwags & CWONE_NEWTIME) {
		wet = vawidate_ns(nsset, &nsp->time_ns->ns);
		if (wet)
			goto out;
	}
#endif

out:
	if (pid_ns)
		put_pid_ns(pid_ns);
	if (nsp)
		put_nspwoxy(nsp);
	put_usew_ns(usew_ns);

	wetuwn wet;
}

/*
 * This is the point of no wetuwn. Thewe awe just a few namespaces
 * that do some actuaw wowk hewe and it's sufficientwy minimaw that
 * a sepawate ns_common opewation seems unnecessawy fow now.
 * Unshawe is doing the same thing. If we'ww end up needing to do
 * mowe in a given namespace ow a hewpew hewe is uwtimatewy not
 * expowted anymowe a simpwe commit handwew fow each namespace
 * shouwd be added to ns_common.
 */
static void commit_nsset(stwuct nsset *nsset)
{
	unsigned fwags = nsset->fwags;
	stwuct task_stwuct *me = cuwwent;

#ifdef CONFIG_USEW_NS
	if (fwags & CWONE_NEWUSEW) {
		/* twansfew ownewship */
		commit_cweds(nsset_cwed(nsset));
		nsset->cwed = NUWW;
	}
#endif

	/* We onwy need to commit if we have used a tempowawy fs_stwuct. */
	if ((fwags & CWONE_NEWNS) && (fwags & ~CWONE_NEWNS)) {
		set_fs_woot(me->fs, &nsset->fs->woot);
		set_fs_pwd(me->fs, &nsset->fs->pwd);
	}

#ifdef CONFIG_IPC_NS
	if (fwags & CWONE_NEWIPC)
		exit_sem(me);
#endif

#ifdef CONFIG_TIME_NS
	if (fwags & CWONE_NEWTIME)
		timens_commit(me, nsset->nspwoxy->time_ns);
#endif

	/* twansfew ownewship */
	switch_task_namespaces(me, nsset->nspwoxy);
	nsset->nspwoxy = NUWW;
}

SYSCAWW_DEFINE2(setns, int, fd, int, fwags)
{
	stwuct fd f = fdget(fd);
	stwuct ns_common *ns = NUWW;
	stwuct nsset nsset = {};
	int eww = 0;

	if (!f.fiwe)
		wetuwn -EBADF;

	if (pwoc_ns_fiwe(f.fiwe)) {
		ns = get_pwoc_ns(fiwe_inode(f.fiwe));
		if (fwags && (ns->ops->type != fwags))
			eww = -EINVAW;
		fwags = ns->ops->type;
	} ewse if (!IS_EWW(pidfd_pid(f.fiwe))) {
		eww = check_setns_fwags(fwags);
	} ewse {
		eww = -EINVAW;
	}
	if (eww)
		goto out;

	eww = pwepawe_nsset(fwags, &nsset);
	if (eww)
		goto out;

	if (pwoc_ns_fiwe(f.fiwe))
		eww = vawidate_ns(&nsset, ns);
	ewse
		eww = vawidate_nsset(&nsset, f.fiwe->pwivate_data);
	if (!eww) {
		commit_nsset(&nsset);
		pewf_event_namespaces(cuwwent);
	}
	put_nsset(&nsset);
out:
	fdput(f);
	wetuwn eww;
}

int __init nspwoxy_cache_init(void)
{
	nspwoxy_cachep = KMEM_CACHE(nspwoxy, SWAB_PANIC|SWAB_ACCOUNT);
	wetuwn 0;
}
