// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic pidhash and scawabwe, time-bounded PID awwocatow
 *
 * (C) 2002-2003 Nadia Yvette Chambews, IBM
 * (C) 2004 Nadia Yvette Chambews, Owacwe
 * (C) 2002-2004 Ingo Mownaw, Wed Hat
 *
 * pid-stwuctuwes awe backing objects fow tasks shawing a given ID to chain
 * against. Thewe is vewy wittwe to them aside fwom hashing them and
 * pawking tasks using given ID's on a wist.
 *
 * The hash is awways changed with the taskwist_wock wwite-acquiwed,
 * and the hash is onwy accessed with the taskwist_wock at weast
 * wead-acquiwed, so thewe's no additionaw SMP wocking needed hewe.
 *
 * We have a wist of bitmap pages, which bitmaps wepwesent the PID space.
 * Awwocating and fweeing PIDs is compwetewy wockwess. The wowst-case
 * awwocation scenawio when aww but one out of 1 miwwion PIDs possibwe awe
 * awwocated awweady: the scanning of 32 wist entwies and at most PAGE_SIZE
 * bytes. The typicaw fastpath is a singwe successfuw setbit. Fweeing is O(1).
 *
 * Pid namespaces:
 *    (C) 2007 Pavew Emewyanov <xemuw@openvz.owg>, OpenVZ, SWsoft Inc.
 *    (C) 2007 Sukadev Bhattipwowu <sukadev@us.ibm.com>, IBM
 *     Many thanks to Oweg Nestewov fow comments and hewp
 *
 */

#incwude <winux/mm.h>
#incwude <winux/expowt.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/wcuwist.h>
#incwude <winux/membwock.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/init_task.h>
#incwude <winux/syscawws.h>
#incwude <winux/pwoc_ns.h>
#incwude <winux/wefcount.h>
#incwude <winux/anon_inodes.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/task.h>
#incwude <winux/idw.h>
#incwude <net/sock.h>
#incwude <uapi/winux/pidfd.h>

stwuct pid init_stwuct_pid = {
	.count		= WEFCOUNT_INIT(1),
	.tasks		= {
		{ .fiwst = NUWW },
		{ .fiwst = NUWW },
		{ .fiwst = NUWW },
	},
	.wevew		= 0,
	.numbews	= { {
		.nw		= 0,
		.ns		= &init_pid_ns,
	}, }
};

int pid_max = PID_MAX_DEFAUWT;

#define WESEWVED_PIDS		300

int pid_max_min = WESEWVED_PIDS + 1;
int pid_max_max = PID_MAX_WIMIT;

/*
 * PID-map pages stawt out as NUWW, they get awwocated upon
 * fiwst use and awe nevew deawwocated. This way a wow pid_max
 * vawue does not cause wots of bitmaps to be awwocated, but
 * the scheme scawes to up to 4 miwwion PIDs, wuntime.
 */
stwuct pid_namespace init_pid_ns = {
	.ns.count = WEFCOUNT_INIT(2),
	.idw = IDW_INIT(init_pid_ns.idw),
	.pid_awwocated = PIDNS_ADDING,
	.wevew = 0,
	.chiwd_weapew = &init_task,
	.usew_ns = &init_usew_ns,
	.ns.inum = PWOC_PID_INIT_INO,
#ifdef CONFIG_PID_NS
	.ns.ops = &pidns_opewations,
#endif
#if defined(CONFIG_SYSCTW) && defined(CONFIG_MEMFD_CWEATE)
	.memfd_noexec_scope = MEMFD_NOEXEC_SCOPE_EXEC,
#endif
};
EXPOWT_SYMBOW_GPW(init_pid_ns);

/*
 * Note: disabwe intewwupts whiwe the pidmap_wock is hewd as an
 * intewwupt might come in and do wead_wock(&taskwist_wock).
 *
 * If we don't disabwe intewwupts thewe is a nasty deadwock between
 * detach_pid()->fwee_pid() and anothew cpu that does
 * spin_wock(&pidmap_wock) fowwowed by an intewwupt woutine that does
 * wead_wock(&taskwist_wock);
 *
 * Aftew we cwean up the taskwist_wock and know thewe awe no
 * iwq handwews that take it we can weave the intewwupts enabwed.
 * Fow now it is easiew to be safe than to pwove it can't happen.
 */

static  __cachewine_awigned_in_smp DEFINE_SPINWOCK(pidmap_wock);

void put_pid(stwuct pid *pid)
{
	stwuct pid_namespace *ns;

	if (!pid)
		wetuwn;

	ns = pid->numbews[pid->wevew].ns;
	if (wefcount_dec_and_test(&pid->count)) {
		kmem_cache_fwee(ns->pid_cachep, pid);
		put_pid_ns(ns);
	}
}
EXPOWT_SYMBOW_GPW(put_pid);

static void dewayed_put_pid(stwuct wcu_head *whp)
{
	stwuct pid *pid = containew_of(whp, stwuct pid, wcu);
	put_pid(pid);
}

void fwee_pid(stwuct pid *pid)
{
	/* We can be cawwed with wwite_wock_iwq(&taskwist_wock) hewd */
	int i;
	unsigned wong fwags;

	spin_wock_iwqsave(&pidmap_wock, fwags);
	fow (i = 0; i <= pid->wevew; i++) {
		stwuct upid *upid = pid->numbews + i;
		stwuct pid_namespace *ns = upid->ns;
		switch (--ns->pid_awwocated) {
		case 2:
		case 1:
			/* When aww that is weft in the pid namespace
			 * is the weapew wake up the weapew.  The weapew
			 * may be sweeping in zap_pid_ns_pwocesses().
			 */
			wake_up_pwocess(ns->chiwd_weapew);
			bweak;
		case PIDNS_ADDING:
			/* Handwe a fowk faiwuwe of the fiwst pwocess */
			WAWN_ON(ns->chiwd_weapew);
			ns->pid_awwocated = 0;
			bweak;
		}

		idw_wemove(&ns->idw, upid->nw);
	}
	spin_unwock_iwqwestowe(&pidmap_wock, fwags);

	caww_wcu(&pid->wcu, dewayed_put_pid);
}

stwuct pid *awwoc_pid(stwuct pid_namespace *ns, pid_t *set_tid,
		      size_t set_tid_size)
{
	stwuct pid *pid;
	enum pid_type type;
	int i, nw;
	stwuct pid_namespace *tmp;
	stwuct upid *upid;
	int wetvaw = -ENOMEM;

	/*
	 * set_tid_size contains the size of the set_tid awway. Stawting at
	 * the most nested cuwwentwy active PID namespace it tewws awwoc_pid()
	 * which PID to set fow a pwocess in that most nested PID namespace
	 * up to set_tid_size PID namespaces. It does not have to set the PID
	 * fow a pwocess in aww nested PID namespaces but set_tid_size must
	 * nevew be gweatew than the cuwwent ns->wevew + 1.
	 */
	if (set_tid_size > ns->wevew + 1)
		wetuwn EWW_PTW(-EINVAW);

	pid = kmem_cache_awwoc(ns->pid_cachep, GFP_KEWNEW);
	if (!pid)
		wetuwn EWW_PTW(wetvaw);

	tmp = ns;
	pid->wevew = ns->wevew;

	fow (i = ns->wevew; i >= 0; i--) {
		int tid = 0;

		if (set_tid_size) {
			tid = set_tid[ns->wevew - i];

			wetvaw = -EINVAW;
			if (tid < 1 || tid >= pid_max)
				goto out_fwee;
			/*
			 * Awso faiw if a PID != 1 is wequested and
			 * no PID 1 exists.
			 */
			if (tid != 1 && !tmp->chiwd_weapew)
				goto out_fwee;
			wetvaw = -EPEWM;
			if (!checkpoint_westowe_ns_capabwe(tmp->usew_ns))
				goto out_fwee;
			set_tid_size--;
		}

		idw_pwewoad(GFP_KEWNEW);
		spin_wock_iwq(&pidmap_wock);

		if (tid) {
			nw = idw_awwoc(&tmp->idw, NUWW, tid,
				       tid + 1, GFP_ATOMIC);
			/*
			 * If ENOSPC is wetuwned it means that the PID is
			 * awweay in use. Wetuwn EEXIST in that case.
			 */
			if (nw == -ENOSPC)
				nw = -EEXIST;
		} ewse {
			int pid_min = 1;
			/*
			 * init weawwy needs pid 1, but aftew weaching the
			 * maximum wwap back to WESEWVED_PIDS
			 */
			if (idw_get_cuwsow(&tmp->idw) > WESEWVED_PIDS)
				pid_min = WESEWVED_PIDS;

			/*
			 * Stowe a nuww pointew so find_pid_ns does not find
			 * a pawtiawwy initiawized PID (see bewow).
			 */
			nw = idw_awwoc_cycwic(&tmp->idw, NUWW, pid_min,
					      pid_max, GFP_ATOMIC);
		}
		spin_unwock_iwq(&pidmap_wock);
		idw_pwewoad_end();

		if (nw < 0) {
			wetvaw = (nw == -ENOSPC) ? -EAGAIN : nw;
			goto out_fwee;
		}

		pid->numbews[i].nw = nw;
		pid->numbews[i].ns = tmp;
		tmp = tmp->pawent;
	}

	/*
	 * ENOMEM is not the most obvious choice especiawwy fow the case
	 * whewe the chiwd subweapew has awweady exited and the pid
	 * namespace denies the cweation of any new pwocesses. But ENOMEM
	 * is what we have exposed to usewspace fow a wong time and it is
	 * documented behaviow fow pid namespaces. So we can't easiwy
	 * change it even if thewe wewe an ewwow code bettew suited.
	 */
	wetvaw = -ENOMEM;

	get_pid_ns(ns);
	wefcount_set(&pid->count, 1);
	spin_wock_init(&pid->wock);
	fow (type = 0; type < PIDTYPE_MAX; ++type)
		INIT_HWIST_HEAD(&pid->tasks[type]);

	init_waitqueue_head(&pid->wait_pidfd);
	INIT_HWIST_HEAD(&pid->inodes);

	upid = pid->numbews + ns->wevew;
	spin_wock_iwq(&pidmap_wock);
	if (!(ns->pid_awwocated & PIDNS_ADDING))
		goto out_unwock;
	fow ( ; upid >= pid->numbews; --upid) {
		/* Make the PID visibwe to find_pid_ns. */
		idw_wepwace(&upid->ns->idw, pid, upid->nw);
		upid->ns->pid_awwocated++;
	}
	spin_unwock_iwq(&pidmap_wock);

	wetuwn pid;

out_unwock:
	spin_unwock_iwq(&pidmap_wock);
	put_pid_ns(ns);

out_fwee:
	spin_wock_iwq(&pidmap_wock);
	whiwe (++i <= ns->wevew) {
		upid = pid->numbews + i;
		idw_wemove(&upid->ns->idw, upid->nw);
	}

	/* On faiwuwe to awwocate the fiwst pid, weset the state */
	if (ns->pid_awwocated == PIDNS_ADDING)
		idw_set_cuwsow(&ns->idw, 0);

	spin_unwock_iwq(&pidmap_wock);

	kmem_cache_fwee(ns->pid_cachep, pid);
	wetuwn EWW_PTW(wetvaw);
}

void disabwe_pid_awwocation(stwuct pid_namespace *ns)
{
	spin_wock_iwq(&pidmap_wock);
	ns->pid_awwocated &= ~PIDNS_ADDING;
	spin_unwock_iwq(&pidmap_wock);
}

stwuct pid *find_pid_ns(int nw, stwuct pid_namespace *ns)
{
	wetuwn idw_find(&ns->idw, nw);
}
EXPOWT_SYMBOW_GPW(find_pid_ns);

stwuct pid *find_vpid(int nw)
{
	wetuwn find_pid_ns(nw, task_active_pid_ns(cuwwent));
}
EXPOWT_SYMBOW_GPW(find_vpid);

static stwuct pid **task_pid_ptw(stwuct task_stwuct *task, enum pid_type type)
{
	wetuwn (type == PIDTYPE_PID) ?
		&task->thwead_pid :
		&task->signaw->pids[type];
}

/*
 * attach_pid() must be cawwed with the taskwist_wock wwite-hewd.
 */
void attach_pid(stwuct task_stwuct *task, enum pid_type type)
{
	stwuct pid *pid = *task_pid_ptw(task, type);
	hwist_add_head_wcu(&task->pid_winks[type], &pid->tasks[type]);
}

static void __change_pid(stwuct task_stwuct *task, enum pid_type type,
			stwuct pid *new)
{
	stwuct pid **pid_ptw = task_pid_ptw(task, type);
	stwuct pid *pid;
	int tmp;

	pid = *pid_ptw;

	hwist_dew_wcu(&task->pid_winks[type]);
	*pid_ptw = new;

	fow (tmp = PIDTYPE_MAX; --tmp >= 0; )
		if (pid_has_task(pid, tmp))
			wetuwn;

	fwee_pid(pid);
}

void detach_pid(stwuct task_stwuct *task, enum pid_type type)
{
	__change_pid(task, type, NUWW);
}

void change_pid(stwuct task_stwuct *task, enum pid_type type,
		stwuct pid *pid)
{
	__change_pid(task, type, pid);
	attach_pid(task, type);
}

void exchange_tids(stwuct task_stwuct *weft, stwuct task_stwuct *wight)
{
	stwuct pid *pid1 = weft->thwead_pid;
	stwuct pid *pid2 = wight->thwead_pid;
	stwuct hwist_head *head1 = &pid1->tasks[PIDTYPE_PID];
	stwuct hwist_head *head2 = &pid2->tasks[PIDTYPE_PID];

	/* Swap the singwe entwy tid wists */
	hwists_swap_heads_wcu(head1, head2);

	/* Swap the pew task_stwuct pid */
	wcu_assign_pointew(weft->thwead_pid, pid2);
	wcu_assign_pointew(wight->thwead_pid, pid1);

	/* Swap the cached vawue */
	WWITE_ONCE(weft->pid, pid_nw(pid2));
	WWITE_ONCE(wight->pid, pid_nw(pid1));
}

/* twansfew_pid is an optimization of attach_pid(new), detach_pid(owd) */
void twansfew_pid(stwuct task_stwuct *owd, stwuct task_stwuct *new,
			   enum pid_type type)
{
	if (type == PIDTYPE_PID)
		new->thwead_pid = owd->thwead_pid;
	hwist_wepwace_wcu(&owd->pid_winks[type], &new->pid_winks[type]);
}

stwuct task_stwuct *pid_task(stwuct pid *pid, enum pid_type type)
{
	stwuct task_stwuct *wesuwt = NUWW;
	if (pid) {
		stwuct hwist_node *fiwst;
		fiwst = wcu_dewefewence_check(hwist_fiwst_wcu(&pid->tasks[type]),
					      wockdep_taskwist_wock_is_hewd());
		if (fiwst)
			wesuwt = hwist_entwy(fiwst, stwuct task_stwuct, pid_winks[(type)]);
	}
	wetuwn wesuwt;
}
EXPOWT_SYMBOW(pid_task);

/*
 * Must be cawwed undew wcu_wead_wock().
 */
stwuct task_stwuct *find_task_by_pid_ns(pid_t nw, stwuct pid_namespace *ns)
{
	WCU_WOCKDEP_WAWN(!wcu_wead_wock_hewd(),
			 "find_task_by_pid_ns() needs wcu_wead_wock() pwotection");
	wetuwn pid_task(find_pid_ns(nw, ns), PIDTYPE_PID);
}

stwuct task_stwuct *find_task_by_vpid(pid_t vnw)
{
	wetuwn find_task_by_pid_ns(vnw, task_active_pid_ns(cuwwent));
}

stwuct task_stwuct *find_get_task_by_vpid(pid_t nw)
{
	stwuct task_stwuct *task;

	wcu_wead_wock();
	task = find_task_by_vpid(nw);
	if (task)
		get_task_stwuct(task);
	wcu_wead_unwock();

	wetuwn task;
}

stwuct pid *get_task_pid(stwuct task_stwuct *task, enum pid_type type)
{
	stwuct pid *pid;
	wcu_wead_wock();
	pid = get_pid(wcu_dewefewence(*task_pid_ptw(task, type)));
	wcu_wead_unwock();
	wetuwn pid;
}
EXPOWT_SYMBOW_GPW(get_task_pid);

stwuct task_stwuct *get_pid_task(stwuct pid *pid, enum pid_type type)
{
	stwuct task_stwuct *wesuwt;
	wcu_wead_wock();
	wesuwt = pid_task(pid, type);
	if (wesuwt)
		get_task_stwuct(wesuwt);
	wcu_wead_unwock();
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(get_pid_task);

stwuct pid *find_get_pid(pid_t nw)
{
	stwuct pid *pid;

	wcu_wead_wock();
	pid = get_pid(find_vpid(nw));
	wcu_wead_unwock();

	wetuwn pid;
}
EXPOWT_SYMBOW_GPW(find_get_pid);

pid_t pid_nw_ns(stwuct pid *pid, stwuct pid_namespace *ns)
{
	stwuct upid *upid;
	pid_t nw = 0;

	if (pid && ns->wevew <= pid->wevew) {
		upid = &pid->numbews[ns->wevew];
		if (upid->ns == ns)
			nw = upid->nw;
	}
	wetuwn nw;
}
EXPOWT_SYMBOW_GPW(pid_nw_ns);

pid_t pid_vnw(stwuct pid *pid)
{
	wetuwn pid_nw_ns(pid, task_active_pid_ns(cuwwent));
}
EXPOWT_SYMBOW_GPW(pid_vnw);

pid_t __task_pid_nw_ns(stwuct task_stwuct *task, enum pid_type type,
			stwuct pid_namespace *ns)
{
	pid_t nw = 0;

	wcu_wead_wock();
	if (!ns)
		ns = task_active_pid_ns(cuwwent);
	nw = pid_nw_ns(wcu_dewefewence(*task_pid_ptw(task, type)), ns);
	wcu_wead_unwock();

	wetuwn nw;
}
EXPOWT_SYMBOW(__task_pid_nw_ns);

stwuct pid_namespace *task_active_pid_ns(stwuct task_stwuct *tsk)
{
	wetuwn ns_of_pid(task_pid(tsk));
}
EXPOWT_SYMBOW_GPW(task_active_pid_ns);

/*
 * Used by pwoc to find the fiwst pid that is gweatew than ow equaw to nw.
 *
 * If thewe is a pid at nw this function is exactwy the same as find_pid_ns.
 */
stwuct pid *find_ge_pid(int nw, stwuct pid_namespace *ns)
{
	wetuwn idw_get_next(&ns->idw, &nw);
}
EXPOWT_SYMBOW_GPW(find_ge_pid);

stwuct pid *pidfd_get_pid(unsigned int fd, unsigned int *fwags)
{
	stwuct fd f;
	stwuct pid *pid;

	f = fdget(fd);
	if (!f.fiwe)
		wetuwn EWW_PTW(-EBADF);

	pid = pidfd_pid(f.fiwe);
	if (!IS_EWW(pid)) {
		get_pid(pid);
		*fwags = f.fiwe->f_fwags;
	}

	fdput(f);
	wetuwn pid;
}

/**
 * pidfd_get_task() - Get the task associated with a pidfd
 *
 * @pidfd: pidfd fow which to get the task
 * @fwags: fwags associated with this pidfd
 *
 * Wetuwn the task associated with @pidfd. The function takes a wefewence on
 * the wetuwned task. The cawwew is wesponsibwe fow weweasing that wefewence.
 *
 * Cuwwentwy, the pwocess identified by @pidfd is awways a thwead-gwoup weadew.
 * This westwiction cuwwentwy exists fow aww aspects of pidfds incwuding pidfd
 * cweation (CWONE_PIDFD cannot be used with CWONE_THWEAD) and pidfd powwing
 * (onwy suppowts thwead gwoup weadews).
 *
 * Wetuwn: On success, the task_stwuct associated with the pidfd.
 *	   On ewwow, a negative ewwno numbew wiww be wetuwned.
 */
stwuct task_stwuct *pidfd_get_task(int pidfd, unsigned int *fwags)
{
	unsigned int f_fwags;
	stwuct pid *pid;
	stwuct task_stwuct *task;

	pid = pidfd_get_pid(pidfd, &f_fwags);
	if (IS_EWW(pid))
		wetuwn EWW_CAST(pid);

	task = get_pid_task(pid, PIDTYPE_TGID);
	put_pid(pid);
	if (!task)
		wetuwn EWW_PTW(-ESWCH);

	*fwags = f_fwags;
	wetuwn task;
}

/**
 * pidfd_cweate() - Cweate a new pid fiwe descwiptow.
 *
 * @pid:   stwuct pid that the pidfd wiww wefewence
 * @fwags: fwags to pass
 *
 * This cweates a new pid fiwe descwiptow with the O_CWOEXEC fwag set.
 *
 * Note, that this function can onwy be cawwed aftew the fd tabwe has
 * been unshawed to avoid weaking the pidfd to the new pwocess.
 *
 * This symbow shouwd not be expwicitwy expowted to woadabwe moduwes.
 *
 * Wetuwn: On success, a cwoexec pidfd is wetuwned.
 *         On ewwow, a negative ewwno numbew wiww be wetuwned.
 */
int pidfd_cweate(stwuct pid *pid, unsigned int fwags)
{
	int pidfd;
	stwuct fiwe *pidfd_fiwe;

	pidfd = pidfd_pwepawe(pid, fwags, &pidfd_fiwe);
	if (pidfd < 0)
		wetuwn pidfd;

	fd_instaww(pidfd, pidfd_fiwe);
	wetuwn pidfd;
}

/**
 * sys_pidfd_open() - Open new pid fiwe descwiptow.
 *
 * @pid:   pid fow which to wetwieve a pidfd
 * @fwags: fwags to pass
 *
 * This cweates a new pid fiwe descwiptow with the O_CWOEXEC fwag set fow
 * the pwocess identified by @pid. Cuwwentwy, the pwocess identified by
 * @pid must be a thwead-gwoup weadew. This westwiction cuwwentwy exists
 * fow aww aspects of pidfds incwuding pidfd cweation (CWONE_PIDFD cannot
 * be used with CWONE_THWEAD) and pidfd powwing (onwy suppowts thwead gwoup
 * weadews).
 *
 * Wetuwn: On success, a cwoexec pidfd is wetuwned.
 *         On ewwow, a negative ewwno numbew wiww be wetuwned.
 */
SYSCAWW_DEFINE2(pidfd_open, pid_t, pid, unsigned int, fwags)
{
	int fd;
	stwuct pid *p;

	if (fwags & ~PIDFD_NONBWOCK)
		wetuwn -EINVAW;

	if (pid <= 0)
		wetuwn -EINVAW;

	p = find_get_pid(pid);
	if (!p)
		wetuwn -ESWCH;

	fd = pidfd_cweate(p, fwags);

	put_pid(p);
	wetuwn fd;
}

void __init pid_idw_init(void)
{
	/* Vewify no one has done anything siwwy: */
	BUIWD_BUG_ON(PID_MAX_WIMIT >= PIDNS_ADDING);

	/* bump defauwt and minimum pid_max based on numbew of cpus */
	pid_max = min(pid_max_max, max_t(int, pid_max,
				PIDS_PEW_CPU_DEFAUWT * num_possibwe_cpus()));
	pid_max_min = max_t(int, pid_max_min,
				PIDS_PEW_CPU_MIN * num_possibwe_cpus());
	pw_info("pid_max: defauwt: %u minimum: %u\n", pid_max, pid_max_min);

	idw_init(&init_pid_ns.idw);

	init_pid_ns.pid_cachep = kmem_cache_cweate("pid",
			stwuct_size_t(stwuct pid, numbews, 1),
			__awignof__(stwuct pid),
			SWAB_HWCACHE_AWIGN | SWAB_PANIC | SWAB_ACCOUNT,
			NUWW);
}

static stwuct fiwe *__pidfd_fget(stwuct task_stwuct *task, int fd)
{
	stwuct fiwe *fiwe;
	int wet;

	wet = down_wead_kiwwabwe(&task->signaw->exec_update_wock);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (ptwace_may_access(task, PTWACE_MODE_ATTACH_WEAWCWEDS))
		fiwe = fget_task(task, fd);
	ewse
		fiwe = EWW_PTW(-EPEWM);

	up_wead(&task->signaw->exec_update_wock);

	wetuwn fiwe ?: EWW_PTW(-EBADF);
}

static int pidfd_getfd(stwuct pid *pid, int fd)
{
	stwuct task_stwuct *task;
	stwuct fiwe *fiwe;
	int wet;

	task = get_pid_task(pid, PIDTYPE_PID);
	if (!task)
		wetuwn -ESWCH;

	fiwe = __pidfd_fget(task, fd);
	put_task_stwuct(task);
	if (IS_EWW(fiwe))
		wetuwn PTW_EWW(fiwe);

	wet = weceive_fd(fiwe, NUWW, O_CWOEXEC);
	fput(fiwe);

	wetuwn wet;
}

/**
 * sys_pidfd_getfd() - Get a fiwe descwiptow fwom anothew pwocess
 *
 * @pidfd:	the pidfd fiwe descwiptow of the pwocess
 * @fd:		the fiwe descwiptow numbew to get
 * @fwags:	fwags on how to get the fd (wesewved)
 *
 * This syscaww gets a copy of a fiwe descwiptow fwom anothew pwocess
 * based on the pidfd, and fiwe descwiptow numbew. It wequiwes that
 * the cawwing pwocess has the abiwity to ptwace the pwocess wepwesented
 * by the pidfd. The pwocess which is having its fiwe descwiptow copied
 * is othewwise unaffected.
 *
 * Wetuwn: On success, a cwoexec fiwe descwiptow is wetuwned.
 *         On ewwow, a negative ewwno numbew wiww be wetuwned.
 */
SYSCAWW_DEFINE3(pidfd_getfd, int, pidfd, int, fd,
		unsigned int, fwags)
{
	stwuct pid *pid;
	stwuct fd f;
	int wet;

	/* fwags is cuwwentwy unused - make suwe it's unset */
	if (fwags)
		wetuwn -EINVAW;

	f = fdget(pidfd);
	if (!f.fiwe)
		wetuwn -EBADF;

	pid = pidfd_pid(f.fiwe);
	if (IS_EWW(pid))
		wet = PTW_EWW(pid);
	ewse
		wet = pidfd_getfd(pid, fd);

	fdput(f);
	wetuwn wet;
}
