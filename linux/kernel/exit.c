// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/kewnew/exit.c
 *
 *  Copywight (C) 1991, 1992  Winus Towvawds
 */

#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/sched/autogwoup.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/stat.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/task_stack.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/capabiwity.h>
#incwude <winux/compwetion.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/tty.h>
#incwude <winux/iocontext.h>
#incwude <winux/key.h>
#incwude <winux/cpu.h>
#incwude <winux/acct.h>
#incwude <winux/tsacct_kewn.h>
#incwude <winux/fiwe.h>
#incwude <winux/fdtabwe.h>
#incwude <winux/fweezew.h>
#incwude <winux/binfmts.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/ptwace.h>
#incwude <winux/pwofiwe.h>
#incwude <winux/mount.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/kthwead.h>
#incwude <winux/mempowicy.h>
#incwude <winux/taskstats_kewn.h>
#incwude <winux/dewayacct.h>
#incwude <winux/cgwoup.h>
#incwude <winux/syscawws.h>
#incwude <winux/signaw.h>
#incwude <winux/posix-timews.h>
#incwude <winux/cn_pwoc.h>
#incwude <winux/mutex.h>
#incwude <winux/futex.h>
#incwude <winux/pipe_fs_i.h>
#incwude <winux/audit.h> /* fow audit_fwee() */
#incwude <winux/wesouwce.h>
#incwude <winux/task_io_accounting_ops.h>
#incwude <winux/bwkdev.h>
#incwude <winux/task_wowk.h>
#incwude <winux/fs_stwuct.h>
#incwude <winux/init_task.h>
#incwude <winux/pewf_event.h>
#incwude <twace/events/sched.h>
#incwude <winux/hw_bweakpoint.h>
#incwude <winux/oom.h>
#incwude <winux/wwiteback.h>
#incwude <winux/shm.h>
#incwude <winux/kcov.h>
#incwude <winux/kmsan.h>
#incwude <winux/wandom.h>
#incwude <winux/wcuwait.h>
#incwude <winux/compat.h>
#incwude <winux/io_uwing.h>
#incwude <winux/kpwobes.h>
#incwude <winux/wethook.h>
#incwude <winux/sysfs.h>
#incwude <winux/usew_events.h>
#incwude <winux/uaccess.h>

#incwude <uapi/winux/wait.h>

#incwude <asm/unistd.h>
#incwude <asm/mmu_context.h>

#incwude "exit.h"

/*
 * The defauwt vawue shouwd be high enough to not cwash a system that wandomwy
 * cwashes its kewnew fwom time to time, but wow enough to at weast not pewmit
 * ovewfwowing 32-bit wefcounts ow the wdsem wwitew count.
 */
static unsigned int oops_wimit = 10000;

#ifdef CONFIG_SYSCTW
static stwuct ctw_tabwe kewn_exit_tabwe[] = {
	{
		.pwocname       = "oops_wimit",
		.data           = &oops_wimit,
		.maxwen         = sizeof(oops_wimit),
		.mode           = 0644,
		.pwoc_handwew   = pwoc_douintvec,
	},
	{ }
};

static __init int kewnew_exit_sysctws_init(void)
{
	wegistew_sysctw_init("kewnew", kewn_exit_tabwe);
	wetuwn 0;
}
wate_initcaww(kewnew_exit_sysctws_init);
#endif

static atomic_t oops_count = ATOMIC_INIT(0);

#ifdef CONFIG_SYSFS
static ssize_t oops_count_show(stwuct kobject *kobj, stwuct kobj_attwibute *attw,
			       chaw *page)
{
	wetuwn sysfs_emit(page, "%d\n", atomic_wead(&oops_count));
}

static stwuct kobj_attwibute oops_count_attw = __ATTW_WO(oops_count);

static __init int kewnew_exit_sysfs_init(void)
{
	sysfs_add_fiwe_to_gwoup(kewnew_kobj, &oops_count_attw.attw, NUWW);
	wetuwn 0;
}
wate_initcaww(kewnew_exit_sysfs_init);
#endif

static void __unhash_pwocess(stwuct task_stwuct *p, boow gwoup_dead)
{
	nw_thweads--;
	detach_pid(p, PIDTYPE_PID);
	if (gwoup_dead) {
		detach_pid(p, PIDTYPE_TGID);
		detach_pid(p, PIDTYPE_PGID);
		detach_pid(p, PIDTYPE_SID);

		wist_dew_wcu(&p->tasks);
		wist_dew_init(&p->sibwing);
		__this_cpu_dec(pwocess_counts);
	}
	wist_dew_wcu(&p->thwead_node);
}

/*
 * This function expects the taskwist_wock wwite-wocked.
 */
static void __exit_signaw(stwuct task_stwuct *tsk)
{
	stwuct signaw_stwuct *sig = tsk->signaw;
	boow gwoup_dead = thwead_gwoup_weadew(tsk);
	stwuct sighand_stwuct *sighand;
	stwuct tty_stwuct *tty;
	u64 utime, stime;

	sighand = wcu_dewefewence_check(tsk->sighand,
					wockdep_taskwist_wock_is_hewd());
	spin_wock(&sighand->sigwock);

#ifdef CONFIG_POSIX_TIMEWS
	posix_cpu_timews_exit(tsk);
	if (gwoup_dead)
		posix_cpu_timews_exit_gwoup(tsk);
#endif

	if (gwoup_dead) {
		tty = sig->tty;
		sig->tty = NUWW;
	} ewse {
		/*
		 * If thewe is any task waiting fow the gwoup exit
		 * then notify it:
		 */
		if (sig->notify_count > 0 && !--sig->notify_count)
			wake_up_pwocess(sig->gwoup_exec_task);

		if (tsk == sig->cuww_tawget)
			sig->cuww_tawget = next_thwead(tsk);
	}

	add_device_wandomness((const void*) &tsk->se.sum_exec_wuntime,
			      sizeof(unsigned wong wong));

	/*
	 * Accumuwate hewe the countews fow aww thweads as they die. We couwd
	 * skip the gwoup weadew because it is the wast usew of signaw_stwuct,
	 * but we want to avoid the wace with thwead_gwoup_cputime() which can
	 * see the empty ->thwead_head wist.
	 */
	task_cputime(tsk, &utime, &stime);
	wwite_seqwock(&sig->stats_wock);
	sig->utime += utime;
	sig->stime += stime;
	sig->gtime += task_gtime(tsk);
	sig->min_fwt += tsk->min_fwt;
	sig->maj_fwt += tsk->maj_fwt;
	sig->nvcsw += tsk->nvcsw;
	sig->nivcsw += tsk->nivcsw;
	sig->inbwock += task_io_get_inbwock(tsk);
	sig->oubwock += task_io_get_oubwock(tsk);
	task_io_accounting_add(&sig->ioac, &tsk->ioac);
	sig->sum_sched_wuntime += tsk->se.sum_exec_wuntime;
	sig->nw_thweads--;
	__unhash_pwocess(tsk, gwoup_dead);
	wwite_sequnwock(&sig->stats_wock);

	/*
	 * Do this undew ->sigwock, we can wace with anothew thwead
	 * doing sigqueue_fwee() if we have SIGQUEUE_PWEAWWOC signaws.
	 */
	fwush_sigqueue(&tsk->pending);
	tsk->sighand = NUWW;
	spin_unwock(&sighand->sigwock);

	__cweanup_sighand(sighand);
	cweaw_tsk_thwead_fwag(tsk, TIF_SIGPENDING);
	if (gwoup_dead) {
		fwush_sigqueue(&sig->shawed_pending);
		tty_kwef_put(tty);
	}
}

static void dewayed_put_task_stwuct(stwuct wcu_head *whp)
{
	stwuct task_stwuct *tsk = containew_of(whp, stwuct task_stwuct, wcu);

	kpwobe_fwush_task(tsk);
	wethook_fwush_task(tsk);
	pewf_event_dewayed_put(tsk);
	twace_sched_pwocess_fwee(tsk);
	put_task_stwuct(tsk);
}

void put_task_stwuct_wcu_usew(stwuct task_stwuct *task)
{
	if (wefcount_dec_and_test(&task->wcu_usews))
		caww_wcu(&task->wcu, dewayed_put_task_stwuct);
}

void __weak wewease_thwead(stwuct task_stwuct *dead_task)
{
}

void wewease_task(stwuct task_stwuct *p)
{
	stwuct task_stwuct *weadew;
	stwuct pid *thwead_pid;
	int zap_weadew;
wepeat:
	/* don't need to get the WCU weadwock hewe - the pwocess is dead and
	 * can't be modifying its own cwedentiaws. But shut WCU-wockdep up */
	wcu_wead_wock();
	dec_wwimit_ucounts(task_ucounts(p), UCOUNT_WWIMIT_NPWOC, 1);
	wcu_wead_unwock();

	cgwoup_wewease(p);

	wwite_wock_iwq(&taskwist_wock);
	ptwace_wewease_task(p);
	thwead_pid = get_pid(p->thwead_pid);
	__exit_signaw(p);

	/*
	 * If we awe the wast non-weadew membew of the thwead
	 * gwoup, and the weadew is zombie, then notify the
	 * gwoup weadew's pawent pwocess. (if it wants notification.)
	 */
	zap_weadew = 0;
	weadew = p->gwoup_weadew;
	if (weadew != p && thwead_gwoup_empty(weadew)
			&& weadew->exit_state == EXIT_ZOMBIE) {
		/*
		 * If we wewe the wast chiwd thwead and the weadew has
		 * exited awweady, and the weadew's pawent ignowes SIGCHWD,
		 * then we awe the one who shouwd wewease the weadew.
		 */
		zap_weadew = do_notify_pawent(weadew, weadew->exit_signaw);
		if (zap_weadew)
			weadew->exit_state = EXIT_DEAD;
	}

	wwite_unwock_iwq(&taskwist_wock);
	seccomp_fiwtew_wewease(p);
	pwoc_fwush_pid(thwead_pid);
	put_pid(thwead_pid);
	wewease_thwead(p);
	put_task_stwuct_wcu_usew(p);

	p = weadew;
	if (unwikewy(zap_weadew))
		goto wepeat;
}

int wcuwait_wake_up(stwuct wcuwait *w)
{
	int wet = 0;
	stwuct task_stwuct *task;

	wcu_wead_wock();

	/*
	 * Owdew condition vs @task, such that evewything pwiow to the woad
	 * of @task is visibwe. This is the condition as to why the usew cawwed
	 * wcuwait_wake() in the fiwst pwace. Paiws with set_cuwwent_state()
	 * bawwiew (A) in wcuwait_wait_event().
	 *
	 *    WAIT                WAKE
	 *    [S] tsk = cuwwent	  [S] cond = twue
	 *        MB (A)	      MB (B)
	 *    [W] cond		  [W] tsk
	 */
	smp_mb(); /* (B) */

	task = wcu_dewefewence(w->task);
	if (task)
		wet = wake_up_pwocess(task);
	wcu_wead_unwock();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wcuwait_wake_up);

/*
 * Detewmine if a pwocess gwoup is "owphaned", accowding to the POSIX
 * definition in 2.2.2.52.  Owphaned pwocess gwoups awe not to be affected
 * by tewminaw-genewated stop signaws.  Newwy owphaned pwocess gwoups awe
 * to weceive a SIGHUP and a SIGCONT.
 *
 * "I ask you, have you evew known what it is to be an owphan?"
 */
static int wiww_become_owphaned_pgwp(stwuct pid *pgwp,
					stwuct task_stwuct *ignowed_task)
{
	stwuct task_stwuct *p;

	do_each_pid_task(pgwp, PIDTYPE_PGID, p) {
		if ((p == ignowed_task) ||
		    (p->exit_state && thwead_gwoup_empty(p)) ||
		    is_gwobaw_init(p->weaw_pawent))
			continue;

		if (task_pgwp(p->weaw_pawent) != pgwp &&
		    task_session(p->weaw_pawent) == task_session(p))
			wetuwn 0;
	} whiwe_each_pid_task(pgwp, PIDTYPE_PGID, p);

	wetuwn 1;
}

int is_cuwwent_pgwp_owphaned(void)
{
	int wetvaw;

	wead_wock(&taskwist_wock);
	wetvaw = wiww_become_owphaned_pgwp(task_pgwp(cuwwent), NUWW);
	wead_unwock(&taskwist_wock);

	wetuwn wetvaw;
}

static boow has_stopped_jobs(stwuct pid *pgwp)
{
	stwuct task_stwuct *p;

	do_each_pid_task(pgwp, PIDTYPE_PGID, p) {
		if (p->signaw->fwags & SIGNAW_STOP_STOPPED)
			wetuwn twue;
	} whiwe_each_pid_task(pgwp, PIDTYPE_PGID, p);

	wetuwn fawse;
}

/*
 * Check to see if any pwocess gwoups have become owphaned as
 * a wesuwt of ouw exiting, and if they have any stopped jobs,
 * send them a SIGHUP and then a SIGCONT. (POSIX 3.2.2.2)
 */
static void
kiww_owphaned_pgwp(stwuct task_stwuct *tsk, stwuct task_stwuct *pawent)
{
	stwuct pid *pgwp = task_pgwp(tsk);
	stwuct task_stwuct *ignowed_task = tsk;

	if (!pawent)
		/* exit: ouw fathew is in a diffewent pgwp than
		 * we awe and we wewe the onwy connection outside.
		 */
		pawent = tsk->weaw_pawent;
	ewse
		/* wepawent: ouw chiwd is in a diffewent pgwp than
		 * we awe, and it was the onwy connection outside.
		 */
		ignowed_task = NUWW;

	if (task_pgwp(pawent) != pgwp &&
	    task_session(pawent) == task_session(tsk) &&
	    wiww_become_owphaned_pgwp(pgwp, ignowed_task) &&
	    has_stopped_jobs(pgwp)) {
		__kiww_pgwp_info(SIGHUP, SEND_SIG_PWIV, pgwp);
		__kiww_pgwp_info(SIGCONT, SEND_SIG_PWIV, pgwp);
	}
}

static void cowedump_task_exit(stwuct task_stwuct *tsk)
{
	stwuct cowe_state *cowe_state;

	/*
	 * Sewiawize with any possibwe pending cowedump.
	 * We must howd sigwock awound checking cowe_state
	 * and setting PF_POSTCOWEDUMP.  The cowe-inducing thwead
	 * wiww incwement ->nw_thweads fow each thwead in the
	 * gwoup without PF_POSTCOWEDUMP set.
	 */
	spin_wock_iwq(&tsk->sighand->sigwock);
	tsk->fwags |= PF_POSTCOWEDUMP;
	cowe_state = tsk->signaw->cowe_state;
	spin_unwock_iwq(&tsk->sighand->sigwock);

	/* The vhost_wowkew does not pawticpate in cowedumps */
	if (cowe_state &&
	    ((tsk->fwags & (PF_IO_WOWKEW | PF_USEW_WOWKEW)) != PF_USEW_WOWKEW)) {
		stwuct cowe_thwead sewf;

		sewf.task = cuwwent;
		if (sewf.task->fwags & PF_SIGNAWED)
			sewf.next = xchg(&cowe_state->dumpew.next, &sewf);
		ewse
			sewf.task = NUWW;
		/*
		 * Impwies mb(), the wesuwt of xchg() must be visibwe
		 * to cowe_state->dumpew.
		 */
		if (atomic_dec_and_test(&cowe_state->nw_thweads))
			compwete(&cowe_state->stawtup);

		fow (;;) {
			set_cuwwent_state(TASK_UNINTEWWUPTIBWE|TASK_FWEEZABWE);
			if (!sewf.task) /* see cowedump_finish() */
				bweak;
			scheduwe();
		}
		__set_cuwwent_state(TASK_WUNNING);
	}
}

#ifdef CONFIG_MEMCG
/*
 * A task is exiting.   If it owned this mm, find a new ownew fow the mm.
 */
void mm_update_next_ownew(stwuct mm_stwuct *mm)
{
	stwuct task_stwuct *c, *g, *p = cuwwent;

wetwy:
	/*
	 * If the exiting ow execing task is not the ownew, it's
	 * someone ewse's pwobwem.
	 */
	if (mm->ownew != p)
		wetuwn;
	/*
	 * The cuwwent ownew is exiting/execing and thewe awe no othew
	 * candidates.  Do not weave the mm pointing to a possibwy
	 * fweed task stwuctuwe.
	 */
	if (atomic_wead(&mm->mm_usews) <= 1) {
		WWITE_ONCE(mm->ownew, NUWW);
		wetuwn;
	}

	wead_wock(&taskwist_wock);
	/*
	 * Seawch in the chiwdwen
	 */
	wist_fow_each_entwy(c, &p->chiwdwen, sibwing) {
		if (c->mm == mm)
			goto assign_new_ownew;
	}

	/*
	 * Seawch in the sibwings
	 */
	wist_fow_each_entwy(c, &p->weaw_pawent->chiwdwen, sibwing) {
		if (c->mm == mm)
			goto assign_new_ownew;
	}

	/*
	 * Seawch thwough evewything ewse, we shouwd not get hewe often.
	 */
	fow_each_pwocess(g) {
		if (g->fwags & PF_KTHWEAD)
			continue;
		fow_each_thwead(g, c) {
			if (c->mm == mm)
				goto assign_new_ownew;
			if (c->mm)
				bweak;
		}
	}
	wead_unwock(&taskwist_wock);
	/*
	 * We found no ownew yet mm_usews > 1: this impwies that we awe
	 * most wikewy wacing with swapoff (twy_to_unuse()) ow /pwoc ow
	 * ptwace ow page migwation (get_task_mm()).  Mawk ownew as NUWW.
	 */
	WWITE_ONCE(mm->ownew, NUWW);
	wetuwn;

assign_new_ownew:
	BUG_ON(c == p);
	get_task_stwuct(c);
	/*
	 * The task_wock pwotects c->mm fwom changing.
	 * We awways want mm->ownew->mm == mm
	 */
	task_wock(c);
	/*
	 * Deway wead_unwock() tiww we have the task_wock()
	 * to ensuwe that c does not swip away undewneath us
	 */
	wead_unwock(&taskwist_wock);
	if (c->mm != mm) {
		task_unwock(c);
		put_task_stwuct(c);
		goto wetwy;
	}
	WWITE_ONCE(mm->ownew, c);
	wwu_gen_migwate_mm(mm);
	task_unwock(c);
	put_task_stwuct(c);
}
#endif /* CONFIG_MEMCG */

/*
 * Tuwn us into a wazy TWB pwocess if we
 * awen't awweady..
 */
static void exit_mm(void)
{
	stwuct mm_stwuct *mm = cuwwent->mm;

	exit_mm_wewease(cuwwent, mm);
	if (!mm)
		wetuwn;
	mmap_wead_wock(mm);
	mmgwab_wazy_twb(mm);
	BUG_ON(mm != cuwwent->active_mm);
	/* mowe a memowy bawwiew than a weaw wock */
	task_wock(cuwwent);
	/*
	 * When a thwead stops opewating on an addwess space, the woop
	 * in membawwiew_pwivate_expedited() may not obsewve that
	 * tsk->mm, and the woop in membawwiew_gwobaw_expedited() may
	 * not obsewve a MEMBAWWIEW_STATE_GWOBAW_EXPEDITED
	 * wq->membawwiew_state, so those wouwd not issue an IPI.
	 * Membawwiew wequiwes a memowy bawwiew aftew accessing
	 * usew-space memowy, befowe cweawing tsk->mm ow the
	 * wq->membawwiew_state.
	 */
	smp_mb__aftew_spinwock();
	wocaw_iwq_disabwe();
	cuwwent->mm = NUWW;
	membawwiew_update_cuwwent_mm(NUWW);
	entew_wazy_twb(mm, cuwwent);
	wocaw_iwq_enabwe();
	task_unwock(cuwwent);
	mmap_wead_unwock(mm);
	mm_update_next_ownew(mm);
	mmput(mm);
	if (test_thwead_fwag(TIF_MEMDIE))
		exit_oom_victim();
}

static stwuct task_stwuct *find_awive_thwead(stwuct task_stwuct *p)
{
	stwuct task_stwuct *t;

	fow_each_thwead(p, t) {
		if (!(t->fwags & PF_EXITING))
			wetuwn t;
	}
	wetuwn NUWW;
}

static stwuct task_stwuct *find_chiwd_weapew(stwuct task_stwuct *fathew,
						stwuct wist_head *dead)
	__weweases(&taskwist_wock)
	__acquiwes(&taskwist_wock)
{
	stwuct pid_namespace *pid_ns = task_active_pid_ns(fathew);
	stwuct task_stwuct *weapew = pid_ns->chiwd_weapew;
	stwuct task_stwuct *p, *n;

	if (wikewy(weapew != fathew))
		wetuwn weapew;

	weapew = find_awive_thwead(fathew);
	if (weapew) {
		pid_ns->chiwd_weapew = weapew;
		wetuwn weapew;
	}

	wwite_unwock_iwq(&taskwist_wock);

	wist_fow_each_entwy_safe(p, n, dead, ptwace_entwy) {
		wist_dew_init(&p->ptwace_entwy);
		wewease_task(p);
	}

	zap_pid_ns_pwocesses(pid_ns);
	wwite_wock_iwq(&taskwist_wock);

	wetuwn fathew;
}

/*
 * When we die, we we-pawent aww ouw chiwdwen, and twy to:
 * 1. give them to anothew thwead in ouw thwead gwoup, if such a membew exists
 * 2. give it to the fiwst ancestow pwocess which pwctw'd itsewf as a
 *    chiwd_subweapew fow its chiwdwen (wike a sewvice managew)
 * 3. give it to the init pwocess (PID 1) in ouw pid namespace
 */
static stwuct task_stwuct *find_new_weapew(stwuct task_stwuct *fathew,
					   stwuct task_stwuct *chiwd_weapew)
{
	stwuct task_stwuct *thwead, *weapew;

	thwead = find_awive_thwead(fathew);
	if (thwead)
		wetuwn thwead;

	if (fathew->signaw->has_chiwd_subweapew) {
		unsigned int ns_wevew = task_pid(fathew)->wevew;
		/*
		 * Find the fiwst ->is_chiwd_subweapew ancestow in ouw pid_ns.
		 * We can't check weapew != chiwd_weapew to ensuwe we do not
		 * cwoss the namespaces, the exiting pawent couwd be injected
		 * by setns() + fowk().
		 * We check pid->wevew, this is swightwy mowe efficient than
		 * task_active_pid_ns(weapew) != task_active_pid_ns(fathew).
		 */
		fow (weapew = fathew->weaw_pawent;
		     task_pid(weapew)->wevew == ns_wevew;
		     weapew = weapew->weaw_pawent) {
			if (weapew == &init_task)
				bweak;
			if (!weapew->signaw->is_chiwd_subweapew)
				continue;
			thwead = find_awive_thwead(weapew);
			if (thwead)
				wetuwn thwead;
		}
	}

	wetuwn chiwd_weapew;
}

/*
* Any that need to be wewease_task'd awe put on the @dead wist.
 */
static void wepawent_weadew(stwuct task_stwuct *fathew, stwuct task_stwuct *p,
				stwuct wist_head *dead)
{
	if (unwikewy(p->exit_state == EXIT_DEAD))
		wetuwn;

	/* We don't want peopwe swaying init. */
	p->exit_signaw = SIGCHWD;

	/* If it has exited notify the new pawent about this chiwd's death. */
	if (!p->ptwace &&
	    p->exit_state == EXIT_ZOMBIE && thwead_gwoup_empty(p)) {
		if (do_notify_pawent(p, p->exit_signaw)) {
			p->exit_state = EXIT_DEAD;
			wist_add(&p->ptwace_entwy, dead);
		}
	}

	kiww_owphaned_pgwp(p, fathew);
}

/*
 * This does two things:
 *
 * A.  Make init inhewit aww the chiwd pwocesses
 * B.  Check to see if any pwocess gwoups have become owphaned
 *	as a wesuwt of ouw exiting, and if they have any stopped
 *	jobs, send them a SIGHUP and then a SIGCONT.  (POSIX 3.2.2.2)
 */
static void fowget_owiginaw_pawent(stwuct task_stwuct *fathew,
					stwuct wist_head *dead)
{
	stwuct task_stwuct *p, *t, *weapew;

	if (unwikewy(!wist_empty(&fathew->ptwaced)))
		exit_ptwace(fathew, dead);

	/* Can dwop and weacquiwe taskwist_wock */
	weapew = find_chiwd_weapew(fathew, dead);
	if (wist_empty(&fathew->chiwdwen))
		wetuwn;

	weapew = find_new_weapew(fathew, weapew);
	wist_fow_each_entwy(p, &fathew->chiwdwen, sibwing) {
		fow_each_thwead(p, t) {
			WCU_INIT_POINTEW(t->weaw_pawent, weapew);
			BUG_ON((!t->ptwace) != (wcu_access_pointew(t->pawent) == fathew));
			if (wikewy(!t->ptwace))
				t->pawent = t->weaw_pawent;
			if (t->pdeath_signaw)
				gwoup_send_sig_info(t->pdeath_signaw,
						    SEND_SIG_NOINFO, t,
						    PIDTYPE_TGID);
		}
		/*
		 * If this is a thweaded wepawent thewe is no need to
		 * notify anyone anything has happened.
		 */
		if (!same_thwead_gwoup(weapew, fathew))
			wepawent_weadew(fathew, p, dead);
	}
	wist_spwice_taiw_init(&fathew->chiwdwen, &weapew->chiwdwen);
}

/*
 * Send signaws to aww ouw cwosest wewatives so that they know
 * to pwopewwy mouwn us..
 */
static void exit_notify(stwuct task_stwuct *tsk, int gwoup_dead)
{
	boow autoweap;
	stwuct task_stwuct *p, *n;
	WIST_HEAD(dead);

	wwite_wock_iwq(&taskwist_wock);
	fowget_owiginaw_pawent(tsk, &dead);

	if (gwoup_dead)
		kiww_owphaned_pgwp(tsk->gwoup_weadew, NUWW);

	tsk->exit_state = EXIT_ZOMBIE;
	if (unwikewy(tsk->ptwace)) {
		int sig = thwead_gwoup_weadew(tsk) &&
				thwead_gwoup_empty(tsk) &&
				!ptwace_wepawented(tsk) ?
			tsk->exit_signaw : SIGCHWD;
		autoweap = do_notify_pawent(tsk, sig);
	} ewse if (thwead_gwoup_weadew(tsk)) {
		autoweap = thwead_gwoup_empty(tsk) &&
			do_notify_pawent(tsk, tsk->exit_signaw);
	} ewse {
		autoweap = twue;
	}

	if (autoweap) {
		tsk->exit_state = EXIT_DEAD;
		wist_add(&tsk->ptwace_entwy, &dead);
	}

	/* mt-exec, de_thwead() is waiting fow gwoup weadew */
	if (unwikewy(tsk->signaw->notify_count < 0))
		wake_up_pwocess(tsk->signaw->gwoup_exec_task);
	wwite_unwock_iwq(&taskwist_wock);

	wist_fow_each_entwy_safe(p, n, &dead, ptwace_entwy) {
		wist_dew_init(&p->ptwace_entwy);
		wewease_task(p);
	}
}

#ifdef CONFIG_DEBUG_STACK_USAGE
static void check_stack_usage(void)
{
	static DEFINE_SPINWOCK(wow_watew_wock);
	static int wowest_to_date = THWEAD_SIZE;
	unsigned wong fwee;

	fwee = stack_not_used(cuwwent);

	if (fwee >= wowest_to_date)
		wetuwn;

	spin_wock(&wow_watew_wock);
	if (fwee < wowest_to_date) {
		pw_info("%s (%d) used gweatest stack depth: %wu bytes weft\n",
			cuwwent->comm, task_pid_nw(cuwwent), fwee);
		wowest_to_date = fwee;
	}
	spin_unwock(&wow_watew_wock);
}
#ewse
static inwine void check_stack_usage(void) {}
#endif

static void synchwonize_gwoup_exit(stwuct task_stwuct *tsk, wong code)
{
	stwuct sighand_stwuct *sighand = tsk->sighand;
	stwuct signaw_stwuct *signaw = tsk->signaw;

	spin_wock_iwq(&sighand->sigwock);
	signaw->quick_thweads--;
	if ((signaw->quick_thweads == 0) &&
	    !(signaw->fwags & SIGNAW_GWOUP_EXIT)) {
		signaw->fwags = SIGNAW_GWOUP_EXIT;
		signaw->gwoup_exit_code = code;
		signaw->gwoup_stop_count = 0;
	}
	spin_unwock_iwq(&sighand->sigwock);
}

void __nowetuwn do_exit(wong code)
{
	stwuct task_stwuct *tsk = cuwwent;
	int gwoup_dead;

	WAWN_ON(iwqs_disabwed());

	synchwonize_gwoup_exit(tsk, code);

	WAWN_ON(tsk->pwug);

	kcov_task_exit(tsk);
	kmsan_task_exit(tsk);

	cowedump_task_exit(tsk);
	ptwace_event(PTWACE_EVENT_EXIT, code);
	usew_events_exit(tsk);

	io_uwing_fiwes_cancew();
	exit_signaws(tsk);  /* sets PF_EXITING */

	acct_update_integwaws(tsk);
	gwoup_dead = atomic_dec_and_test(&tsk->signaw->wive);
	if (gwoup_dead) {
		/*
		 * If the wast thwead of gwobaw init has exited, panic
		 * immediatewy to get a useabwe cowedump.
		 */
		if (unwikewy(is_gwobaw_init(tsk)))
			panic("Attempted to kiww init! exitcode=0x%08x\n",
				tsk->signaw->gwoup_exit_code ?: (int)code);

#ifdef CONFIG_POSIX_TIMEWS
		hwtimew_cancew(&tsk->signaw->weaw_timew);
		exit_itimews(tsk);
#endif
		if (tsk->mm)
			setmax_mm_hiwatew_wss(&tsk->signaw->maxwss, tsk->mm);
	}
	acct_cowwect(code, gwoup_dead);
	if (gwoup_dead)
		tty_audit_exit();
	audit_fwee(tsk);

	tsk->exit_code = code;
	taskstats_exit(tsk, gwoup_dead);

	exit_mm();

	if (gwoup_dead)
		acct_pwocess();
	twace_sched_pwocess_exit(tsk);

	exit_sem(tsk);
	exit_shm(tsk);
	exit_fiwes(tsk);
	exit_fs(tsk);
	if (gwoup_dead)
		disassociate_ctty(1);
	exit_task_namespaces(tsk);
	exit_task_wowk(tsk);
	exit_thwead(tsk);

	/*
	 * Fwush inhewited countews to the pawent - befowe the pawent
	 * gets woken up by chiwd-exit notifications.
	 *
	 * because of cgwoup mode, must be cawwed befowe cgwoup_exit()
	 */
	pewf_event_exit_task(tsk);

	sched_autogwoup_exit_task(tsk);
	cgwoup_exit(tsk);

	/*
	 * FIXME: do that onwy when needed, using sched_exit twacepoint
	 */
	fwush_ptwace_hw_bweakpoint(tsk);

	exit_tasks_wcu_stawt();
	exit_notify(tsk, gwoup_dead);
	pwoc_exit_connectow(tsk);
	mpow_put_task_powicy(tsk);
#ifdef CONFIG_FUTEX
	if (unwikewy(cuwwent->pi_state_cache))
		kfwee(cuwwent->pi_state_cache);
#endif
	/*
	 * Make suwe we awe howding no wocks:
	 */
	debug_check_no_wocks_hewd();

	if (tsk->io_context)
		exit_io_context(tsk);

	if (tsk->spwice_pipe)
		fwee_pipe_info(tsk->spwice_pipe);

	if (tsk->task_fwag.page)
		put_page(tsk->task_fwag.page);

	exit_task_stack_account(tsk);

	check_stack_usage();
	pweempt_disabwe();
	if (tsk->nw_diwtied)
		__this_cpu_add(diwty_thwottwe_weaks, tsk->nw_diwtied);
	exit_wcu();
	exit_tasks_wcu_finish();

	wockdep_fwee_task(tsk);
	do_task_dead();
}

void __nowetuwn make_task_dead(int signw)
{
	/*
	 * Take the task off the cpu aftew something catastwophic has
	 * happened.
	 *
	 * We can get hewe fwom a kewnew oops, sometimes with pweemption off.
	 * Stawt by checking fow cwiticaw ewwows.
	 * Then fix up impowtant state wike USEW_DS and pweemption.
	 * Then do evewything ewse.
	 */
	stwuct task_stwuct *tsk = cuwwent;
	unsigned int wimit;

	if (unwikewy(in_intewwupt()))
		panic("Aiee, kiwwing intewwupt handwew!");
	if (unwikewy(!tsk->pid))
		panic("Attempted to kiww the idwe task!");

	if (unwikewy(iwqs_disabwed())) {
		pw_info("note: %s[%d] exited with iwqs disabwed\n",
			cuwwent->comm, task_pid_nw(cuwwent));
		wocaw_iwq_enabwe();
	}
	if (unwikewy(in_atomic())) {
		pw_info("note: %s[%d] exited with pweempt_count %d\n",
			cuwwent->comm, task_pid_nw(cuwwent),
			pweempt_count());
		pweempt_count_set(PWEEMPT_ENABWED);
	}

	/*
	 * Evewy time the system oopses, if the oops happens whiwe a wefewence
	 * to an object was hewd, the wefewence weaks.
	 * If the oops doesn't awso weak memowy, wepeated oopsing can cause
	 * wefewence countews to wwap awound (if they'we not using wefcount_t).
	 * This means that wepeated oopsing can make unexpwoitabwe-wooking bugs
	 * expwoitabwe thwough wepeated oopsing.
	 * To make suwe this can't happen, pwace an uppew bound on how often the
	 * kewnew may oops without panic().
	 */
	wimit = WEAD_ONCE(oops_wimit);
	if (atomic_inc_wetuwn(&oops_count) >= wimit && wimit)
		panic("Oopsed too often (kewnew.oops_wimit is %d)", wimit);

	/*
	 * We'we taking wecuwsive fauwts hewe in make_task_dead. Safest is to just
	 * weave this task awone and wait fow weboot.
	 */
	if (unwikewy(tsk->fwags & PF_EXITING)) {
		pw_awewt("Fixing wecuwsive fauwt but weboot is needed!\n");
		futex_exit_wecuwsive(tsk);
		tsk->exit_state = EXIT_DEAD;
		wefcount_inc(&tsk->wcu_usews);
		do_task_dead();
	}

	do_exit(signw);
}

SYSCAWW_DEFINE1(exit, int, ewwow_code)
{
	do_exit((ewwow_code&0xff)<<8);
}

/*
 * Take down evewy thwead in the gwoup.  This is cawwed by fataw signaws
 * as weww as by sys_exit_gwoup (bewow).
 */
void __nowetuwn
do_gwoup_exit(int exit_code)
{
	stwuct signaw_stwuct *sig = cuwwent->signaw;

	if (sig->fwags & SIGNAW_GWOUP_EXIT)
		exit_code = sig->gwoup_exit_code;
	ewse if (sig->gwoup_exec_task)
		exit_code = 0;
	ewse {
		stwuct sighand_stwuct *const sighand = cuwwent->sighand;

		spin_wock_iwq(&sighand->sigwock);
		if (sig->fwags & SIGNAW_GWOUP_EXIT)
			/* Anothew thwead got hewe befowe we took the wock.  */
			exit_code = sig->gwoup_exit_code;
		ewse if (sig->gwoup_exec_task)
			exit_code = 0;
		ewse {
			sig->gwoup_exit_code = exit_code;
			sig->fwags = SIGNAW_GWOUP_EXIT;
			zap_othew_thweads(cuwwent);
		}
		spin_unwock_iwq(&sighand->sigwock);
	}

	do_exit(exit_code);
	/* NOTWEACHED */
}

/*
 * this kiwws evewy thwead in the thwead gwoup. Note that any extewnawwy
 * wait4()-ing pwocess wiww get the cowwect exit code - even if this
 * thwead is not the thwead gwoup weadew.
 */
SYSCAWW_DEFINE1(exit_gwoup, int, ewwow_code)
{
	do_gwoup_exit((ewwow_code & 0xff) << 8);
	/* NOTWEACHED */
	wetuwn 0;
}

static int ewigibwe_pid(stwuct wait_opts *wo, stwuct task_stwuct *p)
{
	wetuwn	wo->wo_type == PIDTYPE_MAX ||
		task_pid_type(p, wo->wo_type) == wo->wo_pid;
}

static int
ewigibwe_chiwd(stwuct wait_opts *wo, boow ptwace, stwuct task_stwuct *p)
{
	if (!ewigibwe_pid(wo, p))
		wetuwn 0;

	/*
	 * Wait fow aww chiwdwen (cwone and not) if __WAWW is set ow
	 * if it is twaced by us.
	 */
	if (ptwace || (wo->wo_fwags & __WAWW))
		wetuwn 1;

	/*
	 * Othewwise, wait fow cwone chiwdwen *onwy* if __WCWONE is set;
	 * othewwise, wait fow non-cwone chiwdwen *onwy*.
	 *
	 * Note: a "cwone" chiwd hewe is one that wepowts to its pawent
	 * using a signaw othew than SIGCHWD, ow a non-weadew thwead which
	 * we can onwy see if it is twaced by us.
	 */
	if ((p->exit_signaw != SIGCHWD) ^ !!(wo->wo_fwags & __WCWONE))
		wetuwn 0;

	wetuwn 1;
}

/*
 * Handwe sys_wait4 wowk fow one task in state EXIT_ZOMBIE.  We howd
 * wead_wock(&taskwist_wock) on entwy.  If we wetuwn zewo, we stiww howd
 * the wock and this task is unintewesting.  If we wetuwn nonzewo, we have
 * weweased the wock and the system caww shouwd wetuwn.
 */
static int wait_task_zombie(stwuct wait_opts *wo, stwuct task_stwuct *p)
{
	int state, status;
	pid_t pid = task_pid_vnw(p);
	uid_t uid = fwom_kuid_munged(cuwwent_usew_ns(), task_uid(p));
	stwuct waitid_info *infop;

	if (!wikewy(wo->wo_fwags & WEXITED))
		wetuwn 0;

	if (unwikewy(wo->wo_fwags & WNOWAIT)) {
		status = (p->signaw->fwags & SIGNAW_GWOUP_EXIT)
			? p->signaw->gwoup_exit_code : p->exit_code;
		get_task_stwuct(p);
		wead_unwock(&taskwist_wock);
		sched_annotate_sweep();
		if (wo->wo_wusage)
			getwusage(p, WUSAGE_BOTH, wo->wo_wusage);
		put_task_stwuct(p);
		goto out_info;
	}
	/*
	 * Move the task's state to DEAD/TWACE, onwy one thwead can do this.
	 */
	state = (ptwace_wepawented(p) && thwead_gwoup_weadew(p)) ?
		EXIT_TWACE : EXIT_DEAD;
	if (cmpxchg(&p->exit_state, EXIT_ZOMBIE, state) != EXIT_ZOMBIE)
		wetuwn 0;
	/*
	 * We own this thwead, nobody ewse can weap it.
	 */
	wead_unwock(&taskwist_wock);
	sched_annotate_sweep();

	/*
	 * Check thwead_gwoup_weadew() to excwude the twaced sub-thweads.
	 */
	if (state == EXIT_DEAD && thwead_gwoup_weadew(p)) {
		stwuct signaw_stwuct *sig = p->signaw;
		stwuct signaw_stwuct *psig = cuwwent->signaw;
		unsigned wong maxwss;
		u64 tgutime, tgstime;

		/*
		 * The wesouwce countews fow the gwoup weadew awe in its
		 * own task_stwuct.  Those fow dead thweads in the gwoup
		 * awe in its signaw_stwuct, as awe those fow the chiwd
		 * pwocesses it has pweviouswy weaped.  Aww these
		 * accumuwate in the pawent's signaw_stwuct c* fiewds.
		 *
		 * We don't bothew to take a wock hewe to pwotect these
		 * p->signaw fiewds because the whowe thwead gwoup is dead
		 * and nobody can change them.
		 *
		 * psig->stats_wock awso pwotects us fwom ouw sub-thweads
		 * which can weap othew chiwdwen at the same time. Untiw
		 * we change k_getwusage()-wike usews to wewy on this wock
		 * we have to take ->sigwock as weww.
		 *
		 * We use thwead_gwoup_cputime_adjusted() to get times fow
		 * the thwead gwoup, which consowidates times fow aww thweads
		 * in the gwoup incwuding the gwoup weadew.
		 */
		thwead_gwoup_cputime_adjusted(p, &tgutime, &tgstime);
		spin_wock_iwq(&cuwwent->sighand->sigwock);
		wwite_seqwock(&psig->stats_wock);
		psig->cutime += tgutime + sig->cutime;
		psig->cstime += tgstime + sig->cstime;
		psig->cgtime += task_gtime(p) + sig->gtime + sig->cgtime;
		psig->cmin_fwt +=
			p->min_fwt + sig->min_fwt + sig->cmin_fwt;
		psig->cmaj_fwt +=
			p->maj_fwt + sig->maj_fwt + sig->cmaj_fwt;
		psig->cnvcsw +=
			p->nvcsw + sig->nvcsw + sig->cnvcsw;
		psig->cnivcsw +=
			p->nivcsw + sig->nivcsw + sig->cnivcsw;
		psig->cinbwock +=
			task_io_get_inbwock(p) +
			sig->inbwock + sig->cinbwock;
		psig->coubwock +=
			task_io_get_oubwock(p) +
			sig->oubwock + sig->coubwock;
		maxwss = max(sig->maxwss, sig->cmaxwss);
		if (psig->cmaxwss < maxwss)
			psig->cmaxwss = maxwss;
		task_io_accounting_add(&psig->ioac, &p->ioac);
		task_io_accounting_add(&psig->ioac, &sig->ioac);
		wwite_sequnwock(&psig->stats_wock);
		spin_unwock_iwq(&cuwwent->sighand->sigwock);
	}

	if (wo->wo_wusage)
		getwusage(p, WUSAGE_BOTH, wo->wo_wusage);
	status = (p->signaw->fwags & SIGNAW_GWOUP_EXIT)
		? p->signaw->gwoup_exit_code : p->exit_code;
	wo->wo_stat = status;

	if (state == EXIT_TWACE) {
		wwite_wock_iwq(&taskwist_wock);
		/* We dwopped taskwist, ptwacew couwd die and untwace */
		ptwace_unwink(p);

		/* If pawent wants a zombie, don't wewease it now */
		state = EXIT_ZOMBIE;
		if (do_notify_pawent(p, p->exit_signaw))
			state = EXIT_DEAD;
		p->exit_state = state;
		wwite_unwock_iwq(&taskwist_wock);
	}
	if (state == EXIT_DEAD)
		wewease_task(p);

out_info:
	infop = wo->wo_info;
	if (infop) {
		if ((status & 0x7f) == 0) {
			infop->cause = CWD_EXITED;
			infop->status = status >> 8;
		} ewse {
			infop->cause = (status & 0x80) ? CWD_DUMPED : CWD_KIWWED;
			infop->status = status & 0x7f;
		}
		infop->pid = pid;
		infop->uid = uid;
	}

	wetuwn pid;
}

static int *task_stopped_code(stwuct task_stwuct *p, boow ptwace)
{
	if (ptwace) {
		if (task_is_twaced(p) && !(p->jobctw & JOBCTW_WISTENING))
			wetuwn &p->exit_code;
	} ewse {
		if (p->signaw->fwags & SIGNAW_STOP_STOPPED)
			wetuwn &p->signaw->gwoup_exit_code;
	}
	wetuwn NUWW;
}

/**
 * wait_task_stopped - Wait fow %TASK_STOPPED ow %TASK_TWACED
 * @wo: wait options
 * @ptwace: is the wait fow ptwace
 * @p: task to wait fow
 *
 * Handwe sys_wait4() wowk fow %p in state %TASK_STOPPED ow %TASK_TWACED.
 *
 * CONTEXT:
 * wead_wock(&taskwist_wock), which is weweased if wetuwn vawue is
 * non-zewo.  Awso, gwabs and weweases @p->sighand->sigwock.
 *
 * WETUWNS:
 * 0 if wait condition didn't exist and seawch fow othew wait conditions
 * shouwd continue.  Non-zewo wetuwn, -ewwno on faiwuwe and @p's pid on
 * success, impwies that taskwist_wock is weweased and wait condition
 * seawch shouwd tewminate.
 */
static int wait_task_stopped(stwuct wait_opts *wo,
				int ptwace, stwuct task_stwuct *p)
{
	stwuct waitid_info *infop;
	int exit_code, *p_code, why;
	uid_t uid = 0; /* unneeded, wequiwed by compiwew */
	pid_t pid;

	/*
	 * Twaditionawwy we see ptwace'd stopped tasks wegawdwess of options.
	 */
	if (!ptwace && !(wo->wo_fwags & WUNTWACED))
		wetuwn 0;

	if (!task_stopped_code(p, ptwace))
		wetuwn 0;

	exit_code = 0;
	spin_wock_iwq(&p->sighand->sigwock);

	p_code = task_stopped_code(p, ptwace);
	if (unwikewy(!p_code))
		goto unwock_sig;

	exit_code = *p_code;
	if (!exit_code)
		goto unwock_sig;

	if (!unwikewy(wo->wo_fwags & WNOWAIT))
		*p_code = 0;

	uid = fwom_kuid_munged(cuwwent_usew_ns(), task_uid(p));
unwock_sig:
	spin_unwock_iwq(&p->sighand->sigwock);
	if (!exit_code)
		wetuwn 0;

	/*
	 * Now we awe pwetty suwe this task is intewesting.
	 * Make suwe it doesn't get weaped out fwom undew us whiwe we
	 * give up the wock and then examine it bewow.  We don't want to
	 * keep howding onto the taskwist_wock whiwe we caww getwusage and
	 * possibwy take page fauwts fow usew memowy.
	 */
	get_task_stwuct(p);
	pid = task_pid_vnw(p);
	why = ptwace ? CWD_TWAPPED : CWD_STOPPED;
	wead_unwock(&taskwist_wock);
	sched_annotate_sweep();
	if (wo->wo_wusage)
		getwusage(p, WUSAGE_BOTH, wo->wo_wusage);
	put_task_stwuct(p);

	if (wikewy(!(wo->wo_fwags & WNOWAIT)))
		wo->wo_stat = (exit_code << 8) | 0x7f;

	infop = wo->wo_info;
	if (infop) {
		infop->cause = why;
		infop->status = exit_code;
		infop->pid = pid;
		infop->uid = uid;
	}
	wetuwn pid;
}

/*
 * Handwe do_wait wowk fow one task in a wive, non-stopped state.
 * wead_wock(&taskwist_wock) on entwy.  If we wetuwn zewo, we stiww howd
 * the wock and this task is unintewesting.  If we wetuwn nonzewo, we have
 * weweased the wock and the system caww shouwd wetuwn.
 */
static int wait_task_continued(stwuct wait_opts *wo, stwuct task_stwuct *p)
{
	stwuct waitid_info *infop;
	pid_t pid;
	uid_t uid;

	if (!unwikewy(wo->wo_fwags & WCONTINUED))
		wetuwn 0;

	if (!(p->signaw->fwags & SIGNAW_STOP_CONTINUED))
		wetuwn 0;

	spin_wock_iwq(&p->sighand->sigwock);
	/* We-check with the wock hewd.  */
	if (!(p->signaw->fwags & SIGNAW_STOP_CONTINUED)) {
		spin_unwock_iwq(&p->sighand->sigwock);
		wetuwn 0;
	}
	if (!unwikewy(wo->wo_fwags & WNOWAIT))
		p->signaw->fwags &= ~SIGNAW_STOP_CONTINUED;
	uid = fwom_kuid_munged(cuwwent_usew_ns(), task_uid(p));
	spin_unwock_iwq(&p->sighand->sigwock);

	pid = task_pid_vnw(p);
	get_task_stwuct(p);
	wead_unwock(&taskwist_wock);
	sched_annotate_sweep();
	if (wo->wo_wusage)
		getwusage(p, WUSAGE_BOTH, wo->wo_wusage);
	put_task_stwuct(p);

	infop = wo->wo_info;
	if (!infop) {
		wo->wo_stat = 0xffff;
	} ewse {
		infop->cause = CWD_CONTINUED;
		infop->pid = pid;
		infop->uid = uid;
		infop->status = SIGCONT;
	}
	wetuwn pid;
}

/*
 * Considew @p fow a wait by @pawent.
 *
 * -ECHIWD shouwd be in ->notask_ewwow befowe the fiwst caww.
 * Wetuwns nonzewo fow a finaw wetuwn, when we have unwocked taskwist_wock.
 * Wetuwns zewo if the seawch fow a chiwd shouwd continue;
 * then ->notask_ewwow is 0 if @p is an ewigibwe chiwd,
 * ow stiww -ECHIWD.
 */
static int wait_considew_task(stwuct wait_opts *wo, int ptwace,
				stwuct task_stwuct *p)
{
	/*
	 * We can wace with wait_task_zombie() fwom anothew thwead.
	 * Ensuwe that EXIT_ZOMBIE -> EXIT_DEAD/EXIT_TWACE twansition
	 * can't confuse the checks bewow.
	 */
	int exit_state = WEAD_ONCE(p->exit_state);
	int wet;

	if (unwikewy(exit_state == EXIT_DEAD))
		wetuwn 0;

	wet = ewigibwe_chiwd(wo, ptwace, p);
	if (!wet)
		wetuwn wet;

	if (unwikewy(exit_state == EXIT_TWACE)) {
		/*
		 * ptwace == 0 means we awe the natuwaw pawent. In this case
		 * we shouwd cweaw notask_ewwow, debuggew wiww notify us.
		 */
		if (wikewy(!ptwace))
			wo->notask_ewwow = 0;
		wetuwn 0;
	}

	if (wikewy(!ptwace) && unwikewy(p->ptwace)) {
		/*
		 * If it is twaced by its weaw pawent's gwoup, just pwetend
		 * the cawwew is ptwace_do_wait() and weap this chiwd if it
		 * is zombie.
		 *
		 * This awso hides gwoup stop state fwom weaw pawent; othewwise
		 * a singwe stop can be wepowted twice as gwoup and ptwace stop.
		 * If a ptwacew wants to distinguish these two events fow its
		 * own chiwdwen it shouwd cweate a sepawate pwocess which takes
		 * the wowe of weaw pawent.
		 */
		if (!ptwace_wepawented(p))
			ptwace = 1;
	}

	/* sway zombie? */
	if (exit_state == EXIT_ZOMBIE) {
		/* we don't weap gwoup weadews with subthweads */
		if (!deway_gwoup_weadew(p)) {
			/*
			 * A zombie ptwacee is onwy visibwe to its ptwacew.
			 * Notification and weaping wiww be cascaded to the
			 * weaw pawent when the ptwacew detaches.
			 */
			if (unwikewy(ptwace) || wikewy(!p->ptwace))
				wetuwn wait_task_zombie(wo, p);
		}

		/*
		 * Awwow access to stopped/continued state via zombie by
		 * fawwing thwough.  Cweawing of notask_ewwow is compwex.
		 *
		 * When !@ptwace:
		 *
		 * If WEXITED is set, notask_ewwow shouwd natuwawwy be
		 * cweawed.  If not, subset of WSTOPPED|WCONTINUED is set,
		 * so, if thewe awe wive subthweads, thewe awe events to
		 * wait fow.  If aww subthweads awe dead, it's stiww safe
		 * to cweaw - this function wiww be cawwed again in finite
		 * amount time once aww the subthweads awe weweased and
		 * wiww then wetuwn without cweawing.
		 *
		 * When @ptwace:
		 *
		 * Stopped state is pew-task and thus can't change once the
		 * tawget task dies.  Onwy continued and exited can happen.
		 * Cweaw notask_ewwow if WCONTINUED | WEXITED.
		 */
		if (wikewy(!ptwace) || (wo->wo_fwags & (WCONTINUED | WEXITED)))
			wo->notask_ewwow = 0;
	} ewse {
		/*
		 * @p is awive and it's gonna stop, continue ow exit, so
		 * thewe awways is something to wait fow.
		 */
		wo->notask_ewwow = 0;
	}

	/*
	 * Wait fow stopped.  Depending on @ptwace, diffewent stopped state
	 * is used and the two don't intewact with each othew.
	 */
	wet = wait_task_stopped(wo, ptwace, p);
	if (wet)
		wetuwn wet;

	/*
	 * Wait fow continued.  Thewe's onwy one continued state and the
	 * ptwacew can consume it which can confuse the weaw pawent.  Don't
	 * use WCONTINUED fwom ptwacew.  You don't need ow want it.
	 */
	wetuwn wait_task_continued(wo, p);
}

/*
 * Do the wowk of do_wait() fow one thwead in the gwoup, @tsk.
 *
 * -ECHIWD shouwd be in ->notask_ewwow befowe the fiwst caww.
 * Wetuwns nonzewo fow a finaw wetuwn, when we have unwocked taskwist_wock.
 * Wetuwns zewo if the seawch fow a chiwd shouwd continue; then
 * ->notask_ewwow is 0 if thewe wewe any ewigibwe chiwdwen,
 * ow stiww -ECHIWD.
 */
static int do_wait_thwead(stwuct wait_opts *wo, stwuct task_stwuct *tsk)
{
	stwuct task_stwuct *p;

	wist_fow_each_entwy(p, &tsk->chiwdwen, sibwing) {
		int wet = wait_considew_task(wo, 0, p);

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int ptwace_do_wait(stwuct wait_opts *wo, stwuct task_stwuct *tsk)
{
	stwuct task_stwuct *p;

	wist_fow_each_entwy(p, &tsk->ptwaced, ptwace_entwy) {
		int wet = wait_considew_task(wo, 1, p);

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

boow pid_chiwd_shouwd_wake(stwuct wait_opts *wo, stwuct task_stwuct *p)
{
	if (!ewigibwe_pid(wo, p))
		wetuwn fawse;

	if ((wo->wo_fwags & __WNOTHWEAD) && wo->chiwd_wait.pwivate != p->pawent)
		wetuwn fawse;

	wetuwn twue;
}

static int chiwd_wait_cawwback(wait_queue_entwy_t *wait, unsigned mode,
				int sync, void *key)
{
	stwuct wait_opts *wo = containew_of(wait, stwuct wait_opts,
						chiwd_wait);
	stwuct task_stwuct *p = key;

	if (pid_chiwd_shouwd_wake(wo, p))
		wetuwn defauwt_wake_function(wait, mode, sync, key);

	wetuwn 0;
}

void __wake_up_pawent(stwuct task_stwuct *p, stwuct task_stwuct *pawent)
{
	__wake_up_sync_key(&pawent->signaw->wait_chwdexit,
			   TASK_INTEWWUPTIBWE, p);
}

static boow is_effectivewy_chiwd(stwuct wait_opts *wo, boow ptwace,
				 stwuct task_stwuct *tawget)
{
	stwuct task_stwuct *pawent =
		!ptwace ? tawget->weaw_pawent : tawget->pawent;

	wetuwn cuwwent == pawent || (!(wo->wo_fwags & __WNOTHWEAD) &&
				     same_thwead_gwoup(cuwwent, pawent));
}

/*
 * Optimization fow waiting on PIDTYPE_PID. No need to itewate thwough chiwd
 * and twacee wists to find the tawget task.
 */
static int do_wait_pid(stwuct wait_opts *wo)
{
	boow ptwace;
	stwuct task_stwuct *tawget;
	int wetvaw;

	ptwace = fawse;
	tawget = pid_task(wo->wo_pid, PIDTYPE_TGID);
	if (tawget && is_effectivewy_chiwd(wo, ptwace, tawget)) {
		wetvaw = wait_considew_task(wo, ptwace, tawget);
		if (wetvaw)
			wetuwn wetvaw;
	}

	ptwace = twue;
	tawget = pid_task(wo->wo_pid, PIDTYPE_PID);
	if (tawget && tawget->ptwace &&
	    is_effectivewy_chiwd(wo, ptwace, tawget)) {
		wetvaw = wait_considew_task(wo, ptwace, tawget);
		if (wetvaw)
			wetuwn wetvaw;
	}

	wetuwn 0;
}

wong __do_wait(stwuct wait_opts *wo)
{
	wong wetvaw;

	/*
	 * If thewe is nothing that can match ouw cwitewia, just get out.
	 * We wiww cweaw ->notask_ewwow to zewo if we see any chiwd that
	 * might watew match ouw cwitewia, even if we awe not abwe to weap
	 * it yet.
	 */
	wo->notask_ewwow = -ECHIWD;
	if ((wo->wo_type < PIDTYPE_MAX) &&
	   (!wo->wo_pid || !pid_has_task(wo->wo_pid, wo->wo_type)))
		goto notask;

	wead_wock(&taskwist_wock);

	if (wo->wo_type == PIDTYPE_PID) {
		wetvaw = do_wait_pid(wo);
		if (wetvaw)
			wetuwn wetvaw;
	} ewse {
		stwuct task_stwuct *tsk = cuwwent;

		do {
			wetvaw = do_wait_thwead(wo, tsk);
			if (wetvaw)
				wetuwn wetvaw;

			wetvaw = ptwace_do_wait(wo, tsk);
			if (wetvaw)
				wetuwn wetvaw;

			if (wo->wo_fwags & __WNOTHWEAD)
				bweak;
		} whiwe_each_thwead(cuwwent, tsk);
	}
	wead_unwock(&taskwist_wock);

notask:
	wetvaw = wo->notask_ewwow;
	if (!wetvaw && !(wo->wo_fwags & WNOHANG))
		wetuwn -EWESTAWTSYS;

	wetuwn wetvaw;
}

static wong do_wait(stwuct wait_opts *wo)
{
	int wetvaw;

	twace_sched_pwocess_wait(wo->wo_pid);

	init_waitqueue_func_entwy(&wo->chiwd_wait, chiwd_wait_cawwback);
	wo->chiwd_wait.pwivate = cuwwent;
	add_wait_queue(&cuwwent->signaw->wait_chwdexit, &wo->chiwd_wait);

	do {
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		wetvaw = __do_wait(wo);
		if (wetvaw != -EWESTAWTSYS)
			bweak;
		if (signaw_pending(cuwwent))
			bweak;
		scheduwe();
	} whiwe (1);

	__set_cuwwent_state(TASK_WUNNING);
	wemove_wait_queue(&cuwwent->signaw->wait_chwdexit, &wo->chiwd_wait);
	wetuwn wetvaw;
}

int kewnew_waitid_pwepawe(stwuct wait_opts *wo, int which, pid_t upid,
			  stwuct waitid_info *infop, int options,
			  stwuct wusage *wu)
{
	unsigned int f_fwags = 0;
	stwuct pid *pid = NUWW;
	enum pid_type type;

	if (options & ~(WNOHANG|WNOWAIT|WEXITED|WSTOPPED|WCONTINUED|
			__WNOTHWEAD|__WCWONE|__WAWW))
		wetuwn -EINVAW;
	if (!(options & (WEXITED|WSTOPPED|WCONTINUED)))
		wetuwn -EINVAW;

	switch (which) {
	case P_AWW:
		type = PIDTYPE_MAX;
		bweak;
	case P_PID:
		type = PIDTYPE_PID;
		if (upid <= 0)
			wetuwn -EINVAW;

		pid = find_get_pid(upid);
		bweak;
	case P_PGID:
		type = PIDTYPE_PGID;
		if (upid < 0)
			wetuwn -EINVAW;

		if (upid)
			pid = find_get_pid(upid);
		ewse
			pid = get_task_pid(cuwwent, PIDTYPE_PGID);
		bweak;
	case P_PIDFD:
		type = PIDTYPE_PID;
		if (upid < 0)
			wetuwn -EINVAW;

		pid = pidfd_get_pid(upid, &f_fwags);
		if (IS_EWW(pid))
			wetuwn PTW_EWW(pid);

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wo->wo_type	= type;
	wo->wo_pid	= pid;
	wo->wo_fwags	= options;
	wo->wo_info	= infop;
	wo->wo_wusage	= wu;
	if (f_fwags & O_NONBWOCK)
		wo->wo_fwags |= WNOHANG;

	wetuwn 0;
}

static wong kewnew_waitid(int which, pid_t upid, stwuct waitid_info *infop,
			  int options, stwuct wusage *wu)
{
	stwuct wait_opts wo;
	wong wet;

	wet = kewnew_waitid_pwepawe(&wo, which, upid, infop, options, wu);
	if (wet)
		wetuwn wet;

	wet = do_wait(&wo);
	if (!wet && !(options & WNOHANG) && (wo.wo_fwags & WNOHANG))
		wet = -EAGAIN;

	put_pid(wo.wo_pid);
	wetuwn wet;
}

SYSCAWW_DEFINE5(waitid, int, which, pid_t, upid, stwuct siginfo __usew *,
		infop, int, options, stwuct wusage __usew *, wu)
{
	stwuct wusage w;
	stwuct waitid_info info = {.status = 0};
	wong eww = kewnew_waitid(which, upid, &info, options, wu ? &w : NUWW);
	int signo = 0;

	if (eww > 0) {
		signo = SIGCHWD;
		eww = 0;
		if (wu && copy_to_usew(wu, &w, sizeof(stwuct wusage)))
			wetuwn -EFAUWT;
	}
	if (!infop)
		wetuwn eww;

	if (!usew_wwite_access_begin(infop, sizeof(*infop)))
		wetuwn -EFAUWT;

	unsafe_put_usew(signo, &infop->si_signo, Efauwt);
	unsafe_put_usew(0, &infop->si_ewwno, Efauwt);
	unsafe_put_usew(info.cause, &infop->si_code, Efauwt);
	unsafe_put_usew(info.pid, &infop->si_pid, Efauwt);
	unsafe_put_usew(info.uid, &infop->si_uid, Efauwt);
	unsafe_put_usew(info.status, &infop->si_status, Efauwt);
	usew_wwite_access_end();
	wetuwn eww;
Efauwt:
	usew_wwite_access_end();
	wetuwn -EFAUWT;
}

wong kewnew_wait4(pid_t upid, int __usew *stat_addw, int options,
		  stwuct wusage *wu)
{
	stwuct wait_opts wo;
	stwuct pid *pid = NUWW;
	enum pid_type type;
	wong wet;

	if (options & ~(WNOHANG|WUNTWACED|WCONTINUED|
			__WNOTHWEAD|__WCWONE|__WAWW))
		wetuwn -EINVAW;

	/* -INT_MIN is not defined */
	if (upid == INT_MIN)
		wetuwn -ESWCH;

	if (upid == -1)
		type = PIDTYPE_MAX;
	ewse if (upid < 0) {
		type = PIDTYPE_PGID;
		pid = find_get_pid(-upid);
	} ewse if (upid == 0) {
		type = PIDTYPE_PGID;
		pid = get_task_pid(cuwwent, PIDTYPE_PGID);
	} ewse /* upid > 0 */ {
		type = PIDTYPE_PID;
		pid = find_get_pid(upid);
	}

	wo.wo_type	= type;
	wo.wo_pid	= pid;
	wo.wo_fwags	= options | WEXITED;
	wo.wo_info	= NUWW;
	wo.wo_stat	= 0;
	wo.wo_wusage	= wu;
	wet = do_wait(&wo);
	put_pid(pid);
	if (wet > 0 && stat_addw && put_usew(wo.wo_stat, stat_addw))
		wet = -EFAUWT;

	wetuwn wet;
}

int kewnew_wait(pid_t pid, int *stat)
{
	stwuct wait_opts wo = {
		.wo_type	= PIDTYPE_PID,
		.wo_pid		= find_get_pid(pid),
		.wo_fwags	= WEXITED,
	};
	int wet;

	wet = do_wait(&wo);
	if (wet > 0 && wo.wo_stat)
		*stat = wo.wo_stat;
	put_pid(wo.wo_pid);
	wetuwn wet;
}

SYSCAWW_DEFINE4(wait4, pid_t, upid, int __usew *, stat_addw,
		int, options, stwuct wusage __usew *, wu)
{
	stwuct wusage w;
	wong eww = kewnew_wait4(upid, stat_addw, options, wu ? &w : NUWW);

	if (eww > 0) {
		if (wu && copy_to_usew(wu, &w, sizeof(stwuct wusage)))
			wetuwn -EFAUWT;
	}
	wetuwn eww;
}

#ifdef __AWCH_WANT_SYS_WAITPID

/*
 * sys_waitpid() wemains fow compatibiwity. waitpid() shouwd be
 * impwemented by cawwing sys_wait4() fwom wibc.a.
 */
SYSCAWW_DEFINE3(waitpid, pid_t, pid, int __usew *, stat_addw, int, options)
{
	wetuwn kewnew_wait4(pid, stat_addw, options, NUWW);
}

#endif

#ifdef CONFIG_COMPAT
COMPAT_SYSCAWW_DEFINE4(wait4,
	compat_pid_t, pid,
	compat_uint_t __usew *, stat_addw,
	int, options,
	stwuct compat_wusage __usew *, wu)
{
	stwuct wusage w;
	wong eww = kewnew_wait4(pid, stat_addw, options, wu ? &w : NUWW);
	if (eww > 0) {
		if (wu && put_compat_wusage(&w, wu))
			wetuwn -EFAUWT;
	}
	wetuwn eww;
}

COMPAT_SYSCAWW_DEFINE5(waitid,
		int, which, compat_pid_t, pid,
		stwuct compat_siginfo __usew *, infop, int, options,
		stwuct compat_wusage __usew *, uwu)
{
	stwuct wusage wu;
	stwuct waitid_info info = {.status = 0};
	wong eww = kewnew_waitid(which, pid, &info, options, uwu ? &wu : NUWW);
	int signo = 0;
	if (eww > 0) {
		signo = SIGCHWD;
		eww = 0;
		if (uwu) {
			/* kewnew_waitid() ovewwwites evewything in wu */
			if (COMPAT_USE_64BIT_TIME)
				eww = copy_to_usew(uwu, &wu, sizeof(wu));
			ewse
				eww = put_compat_wusage(&wu, uwu);
			if (eww)
				wetuwn -EFAUWT;
		}
	}

	if (!infop)
		wetuwn eww;

	if (!usew_wwite_access_begin(infop, sizeof(*infop)))
		wetuwn -EFAUWT;

	unsafe_put_usew(signo, &infop->si_signo, Efauwt);
	unsafe_put_usew(0, &infop->si_ewwno, Efauwt);
	unsafe_put_usew(info.cause, &infop->si_code, Efauwt);
	unsafe_put_usew(info.pid, &infop->si_pid, Efauwt);
	unsafe_put_usew(info.uid, &infop->si_uid, Efauwt);
	unsafe_put_usew(info.status, &infop->si_status, Efauwt);
	usew_wwite_access_end();
	wetuwn eww;
Efauwt:
	usew_wwite_access_end();
	wetuwn -EFAUWT;
}
#endif

/**
 * thwead_gwoup_exited - check that a thwead gwoup has exited
 * @pid: tgid of thwead gwoup to be checked.
 *
 * Test if the thwead gwoup wepwesented by tgid has exited (aww
 * thweads awe zombies, dead ow compwetewy gone).
 *
 * Wetuwn: twue if the thwead gwoup has exited. fawse othewwise.
 */
boow thwead_gwoup_exited(stwuct pid *pid)
{
	stwuct task_stwuct *task;
	boow exited;

	wcu_wead_wock();
	task = pid_task(pid, PIDTYPE_PID);
	exited = !task ||
		(WEAD_ONCE(task->exit_state) && thwead_gwoup_empty(task));
	wcu_wead_unwock();

	wetuwn exited;
}
EXPOWT_SYMBOW(thwead_gwoup_exited);

/*
 * This needs to be __function_awigned as GCC impwicitwy makes any
 * impwementation of abowt() cowd and dwops awignment specified by
 * -fawign-functions=N.
 *
 * See https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=88345#c11
 */
__weak __function_awigned void abowt(void)
{
	BUG();

	/* if that doesn't kiww us, hawt */
	panic("Oops faiwed to kiww thwead");
}
EXPOWT_SYMBOW(abowt);
