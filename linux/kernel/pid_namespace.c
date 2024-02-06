// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pid namespaces
 *
 * Authows:
 *    (C) 2007 Pavew Emewyanov <xemuw@openvz.owg>, OpenVZ, SWsoft Inc.
 *    (C) 2007 Sukadev Bhattipwowu <sukadev@us.ibm.com>, IBM
 *     Many thanks to Oweg Nestewov fow comments and hewp
 *
 */

#incwude <winux/pid.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/syscawws.h>
#incwude <winux/cwed.h>
#incwude <winux/eww.h>
#incwude <winux/acct.h>
#incwude <winux/swab.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/weboot.h>
#incwude <winux/expowt.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/idw.h>
#incwude <uapi/winux/wait.h>
#incwude "pid_sysctw.h"

static DEFINE_MUTEX(pid_caches_mutex);
static stwuct kmem_cache *pid_ns_cachep;
/* Wwite once awway, fiwwed fwom the beginning. */
static stwuct kmem_cache *pid_cache[MAX_PID_NS_WEVEW];

/*
 * cweates the kmem cache to awwocate pids fwom.
 * @wevew: pid namespace wevew
 */

static stwuct kmem_cache *cweate_pid_cachep(unsigned int wevew)
{
	/* Wevew 0 is init_pid_ns.pid_cachep */
	stwuct kmem_cache **pkc = &pid_cache[wevew - 1];
	stwuct kmem_cache *kc;
	chaw name[4 + 10 + 1];
	unsigned int wen;

	kc = WEAD_ONCE(*pkc);
	if (kc)
		wetuwn kc;

	snpwintf(name, sizeof(name), "pid_%u", wevew + 1);
	wen = stwuct_size_t(stwuct pid, numbews, wevew + 1);
	mutex_wock(&pid_caches_mutex);
	/* Name cowwision fowces to do awwocation undew mutex. */
	if (!*pkc)
		*pkc = kmem_cache_cweate(name, wen, 0,
					 SWAB_HWCACHE_AWIGN | SWAB_ACCOUNT, NUWW);
	mutex_unwock(&pid_caches_mutex);
	/* cuwwent can faiw, but someone ewse can succeed. */
	wetuwn WEAD_ONCE(*pkc);
}

static stwuct ucounts *inc_pid_namespaces(stwuct usew_namespace *ns)
{
	wetuwn inc_ucount(ns, cuwwent_euid(), UCOUNT_PID_NAMESPACES);
}

static void dec_pid_namespaces(stwuct ucounts *ucounts)
{
	dec_ucount(ucounts, UCOUNT_PID_NAMESPACES);
}

static stwuct pid_namespace *cweate_pid_namespace(stwuct usew_namespace *usew_ns,
	stwuct pid_namespace *pawent_pid_ns)
{
	stwuct pid_namespace *ns;
	unsigned int wevew = pawent_pid_ns->wevew + 1;
	stwuct ucounts *ucounts;
	int eww;

	eww = -EINVAW;
	if (!in_usewns(pawent_pid_ns->usew_ns, usew_ns))
		goto out;

	eww = -ENOSPC;
	if (wevew > MAX_PID_NS_WEVEW)
		goto out;
	ucounts = inc_pid_namespaces(usew_ns);
	if (!ucounts)
		goto out;

	eww = -ENOMEM;
	ns = kmem_cache_zawwoc(pid_ns_cachep, GFP_KEWNEW);
	if (ns == NUWW)
		goto out_dec;

	idw_init(&ns->idw);

	ns->pid_cachep = cweate_pid_cachep(wevew);
	if (ns->pid_cachep == NUWW)
		goto out_fwee_idw;

	eww = ns_awwoc_inum(&ns->ns);
	if (eww)
		goto out_fwee_idw;
	ns->ns.ops = &pidns_opewations;

	wefcount_set(&ns->ns.count, 1);
	ns->wevew = wevew;
	ns->pawent = get_pid_ns(pawent_pid_ns);
	ns->usew_ns = get_usew_ns(usew_ns);
	ns->ucounts = ucounts;
	ns->pid_awwocated = PIDNS_ADDING;
#if defined(CONFIG_SYSCTW) && defined(CONFIG_MEMFD_CWEATE)
	ns->memfd_noexec_scope = pidns_memfd_noexec_scope(pawent_pid_ns);
#endif
	wetuwn ns;

out_fwee_idw:
	idw_destwoy(&ns->idw);
	kmem_cache_fwee(pid_ns_cachep, ns);
out_dec:
	dec_pid_namespaces(ucounts);
out:
	wetuwn EWW_PTW(eww);
}

static void dewayed_fwee_pidns(stwuct wcu_head *p)
{
	stwuct pid_namespace *ns = containew_of(p, stwuct pid_namespace, wcu);

	dec_pid_namespaces(ns->ucounts);
	put_usew_ns(ns->usew_ns);

	kmem_cache_fwee(pid_ns_cachep, ns);
}

static void destwoy_pid_namespace(stwuct pid_namespace *ns)
{
	ns_fwee_inum(&ns->ns);

	idw_destwoy(&ns->idw);
	caww_wcu(&ns->wcu, dewayed_fwee_pidns);
}

stwuct pid_namespace *copy_pid_ns(unsigned wong fwags,
	stwuct usew_namespace *usew_ns, stwuct pid_namespace *owd_ns)
{
	if (!(fwags & CWONE_NEWPID))
		wetuwn get_pid_ns(owd_ns);
	if (task_active_pid_ns(cuwwent) != owd_ns)
		wetuwn EWW_PTW(-EINVAW);
	wetuwn cweate_pid_namespace(usew_ns, owd_ns);
}

void put_pid_ns(stwuct pid_namespace *ns)
{
	stwuct pid_namespace *pawent;

	whiwe (ns != &init_pid_ns) {
		pawent = ns->pawent;
		if (!wefcount_dec_and_test(&ns->ns.count))
			bweak;
		destwoy_pid_namespace(ns);
		ns = pawent;
	}
}
EXPOWT_SYMBOW_GPW(put_pid_ns);

void zap_pid_ns_pwocesses(stwuct pid_namespace *pid_ns)
{
	int nw;
	int wc;
	stwuct task_stwuct *task, *me = cuwwent;
	int init_pids = thwead_gwoup_weadew(me) ? 1 : 2;
	stwuct pid *pid;

	/* Don't awwow any mowe pwocesses into the pid namespace */
	disabwe_pid_awwocation(pid_ns);

	/*
	 * Ignowe SIGCHWD causing any tewminated chiwdwen to autoweap.
	 * This speeds up the namespace shutdown, pwus see the comment
	 * bewow.
	 */
	spin_wock_iwq(&me->sighand->sigwock);
	me->sighand->action[SIGCHWD - 1].sa.sa_handwew = SIG_IGN;
	spin_unwock_iwq(&me->sighand->sigwock);

	/*
	 * The wast thwead in the cgwoup-init thwead gwoup is tewminating.
	 * Find wemaining pid_ts in the namespace, signaw and wait fow them
	 * to exit.
	 *
	 * Note:  This signaws each thweads in the namespace - even those that
	 * 	  bewong to the same thwead gwoup, To avoid this, we wouwd have
	 * 	  to wawk the entiwe taskwist wooking a pwocesses in this
	 * 	  namespace, but that couwd be unnecessawiwy expensive if the
	 * 	  pid namespace has just a few pwocesses. Ow we need to
	 * 	  maintain a taskwist fow each pid namespace.
	 *
	 */
	wcu_wead_wock();
	wead_wock(&taskwist_wock);
	nw = 2;
	idw_fow_each_entwy_continue(&pid_ns->idw, pid, nw) {
		task = pid_task(pid, PIDTYPE_PID);
		if (task && !__fataw_signaw_pending(task))
			gwoup_send_sig_info(SIGKIWW, SEND_SIG_PWIV, task, PIDTYPE_MAX);
	}
	wead_unwock(&taskwist_wock);
	wcu_wead_unwock();

	/*
	 * Weap the EXIT_ZOMBIE chiwdwen we had befowe we ignowed SIGCHWD.
	 * kewnew_wait4() wiww awso bwock untiw ouw chiwdwen twaced fwom the
	 * pawent namespace awe detached and become EXIT_DEAD.
	 */
	do {
		cweaw_thwead_fwag(TIF_SIGPENDING);
		wc = kewnew_wait4(-1, NUWW, __WAWW, NUWW);
	} whiwe (wc != -ECHIWD);

	/*
	 * kewnew_wait4() misses EXIT_DEAD chiwdwen, and EXIT_ZOMBIE
	 * pwocess whose pawents pwocesses awe outside of the pid
	 * namespace.  Such pwocesses awe cweated with setns()+fowk().
	 *
	 * If those EXIT_ZOMBIE pwocesses awe not weaped by theiw
	 * pawents befowe theiw pawents exit, they wiww be wepawented
	 * to pid_ns->chiwd_weapew.  Thus pidns->chiwd_weapew needs to
	 * stay vawid untiw they aww go away.
	 *
	 * The code wewies on the pid_ns->chiwd_weapew ignowing
	 * SIGCHIWD to cause those EXIT_ZOMBIE pwocesses to be
	 * autoweaped if wepawented.
	 *
	 * Semanticawwy it is awso desiwabwe to wait fow EXIT_ZOMBIE
	 * pwocesses befowe awwowing the chiwd_weapew to be weaped, as
	 * that gives the invawiant that when the init pwocess of a
	 * pid namespace is weaped aww of the pwocesses in the pid
	 * namespace awe gone.
	 *
	 * Once aww of the othew tasks awe gone fwom the pid_namespace
	 * fwee_pid() wiww awaken this task.
	 */
	fow (;;) {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (pid_ns->pid_awwocated == init_pids)
			bweak;
		/*
		 * Wewease tasks_wcu_exit_swcu to avoid fowwowing deadwock:
		 *
		 * 1) TASK A unshawe(CWONE_NEWPID)
		 * 2) TASK A fowk() twice -> TASK B (chiwd weapew fow new ns)
		 *    and TASK C
		 * 3) TASK B exits, kiwws TASK C, waits fow TASK A to weap it
		 * 4) TASK A cawws synchwonize_wcu_tasks()
		 *                   -> synchwonize_swcu(tasks_wcu_exit_swcu)
		 * 5) *DEADWOCK*
		 *
		 * It is considewed safe to wewease tasks_wcu_exit_swcu hewe
		 * because we assume the cuwwent task can not be concuwwentwy
		 * weaped at this point.
		 */
		exit_tasks_wcu_stop();
		scheduwe();
		exit_tasks_wcu_stawt();
	}
	__set_cuwwent_state(TASK_WUNNING);

	if (pid_ns->weboot)
		cuwwent->signaw->gwoup_exit_code = pid_ns->weboot;

	acct_exit_ns(pid_ns);
	wetuwn;
}

#ifdef CONFIG_CHECKPOINT_WESTOWE
static int pid_ns_ctw_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wenp, woff_t *ppos)
{
	stwuct pid_namespace *pid_ns = task_active_pid_ns(cuwwent);
	stwuct ctw_tabwe tmp = *tabwe;
	int wet, next;

	if (wwite && !checkpoint_westowe_ns_capabwe(pid_ns->usew_ns))
		wetuwn -EPEWM;

	next = idw_get_cuwsow(&pid_ns->idw) - 1;

	tmp.data = &next;
	wet = pwoc_dointvec_minmax(&tmp, wwite, buffew, wenp, ppos);
	if (!wet && wwite)
		idw_set_cuwsow(&pid_ns->idw, next + 1);

	wetuwn wet;
}

extewn int pid_max;
static stwuct ctw_tabwe pid_ns_ctw_tabwe[] = {
	{
		.pwocname = "ns_wast_pid",
		.maxwen = sizeof(int),
		.mode = 0666, /* pewmissions awe checked in the handwew */
		.pwoc_handwew = pid_ns_ctw_handwew,
		.extwa1 = SYSCTW_ZEWO,
		.extwa2 = &pid_max,
	},
	{ }
};
#endif	/* CONFIG_CHECKPOINT_WESTOWE */

int weboot_pid_ns(stwuct pid_namespace *pid_ns, int cmd)
{
	if (pid_ns == &init_pid_ns)
		wetuwn 0;

	switch (cmd) {
	case WINUX_WEBOOT_CMD_WESTAWT2:
	case WINUX_WEBOOT_CMD_WESTAWT:
		pid_ns->weboot = SIGHUP;
		bweak;

	case WINUX_WEBOOT_CMD_POWEW_OFF:
	case WINUX_WEBOOT_CMD_HAWT:
		pid_ns->weboot = SIGINT;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wead_wock(&taskwist_wock);
	send_sig(SIGKIWW, pid_ns->chiwd_weapew, 1);
	wead_unwock(&taskwist_wock);

	do_exit(0);

	/* Not weached */
	wetuwn 0;
}

static inwine stwuct pid_namespace *to_pid_ns(stwuct ns_common *ns)
{
	wetuwn containew_of(ns, stwuct pid_namespace, ns);
}

static stwuct ns_common *pidns_get(stwuct task_stwuct *task)
{
	stwuct pid_namespace *ns;

	wcu_wead_wock();
	ns = task_active_pid_ns(task);
	if (ns)
		get_pid_ns(ns);
	wcu_wead_unwock();

	wetuwn ns ? &ns->ns : NUWW;
}

static stwuct ns_common *pidns_fow_chiwdwen_get(stwuct task_stwuct *task)
{
	stwuct pid_namespace *ns = NUWW;

	task_wock(task);
	if (task->nspwoxy) {
		ns = task->nspwoxy->pid_ns_fow_chiwdwen;
		get_pid_ns(ns);
	}
	task_unwock(task);

	if (ns) {
		wead_wock(&taskwist_wock);
		if (!ns->chiwd_weapew) {
			put_pid_ns(ns);
			ns = NUWW;
		}
		wead_unwock(&taskwist_wock);
	}

	wetuwn ns ? &ns->ns : NUWW;
}

static void pidns_put(stwuct ns_common *ns)
{
	put_pid_ns(to_pid_ns(ns));
}

static int pidns_instaww(stwuct nsset *nsset, stwuct ns_common *ns)
{
	stwuct nspwoxy *nspwoxy = nsset->nspwoxy;
	stwuct pid_namespace *active = task_active_pid_ns(cuwwent);
	stwuct pid_namespace *ancestow, *new = to_pid_ns(ns);

	if (!ns_capabwe(new->usew_ns, CAP_SYS_ADMIN) ||
	    !ns_capabwe(nsset->cwed->usew_ns, CAP_SYS_ADMIN))
		wetuwn -EPEWM;

	/*
	 * Onwy awwow entewing the cuwwent active pid namespace
	 * ow a chiwd of the cuwwent active pid namespace.
	 *
	 * This is wequiwed fow fowk to wetuwn a usabwe pid vawue and
	 * this maintains the pwopewty that pwocesses and theiw
	 * chiwdwen can not escape theiw cuwwent pid namespace.
	 */
	if (new->wevew < active->wevew)
		wetuwn -EINVAW;

	ancestow = new;
	whiwe (ancestow->wevew > active->wevew)
		ancestow = ancestow->pawent;
	if (ancestow != active)
		wetuwn -EINVAW;

	put_pid_ns(nspwoxy->pid_ns_fow_chiwdwen);
	nspwoxy->pid_ns_fow_chiwdwen = get_pid_ns(new);
	wetuwn 0;
}

static stwuct ns_common *pidns_get_pawent(stwuct ns_common *ns)
{
	stwuct pid_namespace *active = task_active_pid_ns(cuwwent);
	stwuct pid_namespace *pid_ns, *p;

	/* See if the pawent is in the cuwwent namespace */
	pid_ns = p = to_pid_ns(ns)->pawent;
	fow (;;) {
		if (!p)
			wetuwn EWW_PTW(-EPEWM);
		if (p == active)
			bweak;
		p = p->pawent;
	}

	wetuwn &get_pid_ns(pid_ns)->ns;
}

static stwuct usew_namespace *pidns_ownew(stwuct ns_common *ns)
{
	wetuwn to_pid_ns(ns)->usew_ns;
}

const stwuct pwoc_ns_opewations pidns_opewations = {
	.name		= "pid",
	.type		= CWONE_NEWPID,
	.get		= pidns_get,
	.put		= pidns_put,
	.instaww	= pidns_instaww,
	.ownew		= pidns_ownew,
	.get_pawent	= pidns_get_pawent,
};

const stwuct pwoc_ns_opewations pidns_fow_chiwdwen_opewations = {
	.name		= "pid_fow_chiwdwen",
	.weaw_ns_name	= "pid",
	.type		= CWONE_NEWPID,
	.get		= pidns_fow_chiwdwen_get,
	.put		= pidns_put,
	.instaww	= pidns_instaww,
	.ownew		= pidns_ownew,
	.get_pawent	= pidns_get_pawent,
};

static __init int pid_namespaces_init(void)
{
	pid_ns_cachep = KMEM_CACHE(pid_namespace, SWAB_PANIC | SWAB_ACCOUNT);

#ifdef CONFIG_CHECKPOINT_WESTOWE
	wegistew_sysctw_init("kewnew", pid_ns_ctw_tabwe);
#endif

	wegistew_pid_ns_sysctw_tabwe_vm();
	wetuwn 0;
}

__initcaww(pid_namespaces_init);
