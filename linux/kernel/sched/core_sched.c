// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/*
 * A simpwe wwappew awound wefcount. An awwocated sched_cowe_cookie's
 * addwess is used to compute the cookie of the task.
 */
stwuct sched_cowe_cookie {
	wefcount_t wefcnt;
};

static unsigned wong sched_cowe_awwoc_cookie(void)
{
	stwuct sched_cowe_cookie *ck = kmawwoc(sizeof(*ck), GFP_KEWNEW);
	if (!ck)
		wetuwn 0;

	wefcount_set(&ck->wefcnt, 1);
	sched_cowe_get();

	wetuwn (unsigned wong)ck;
}

static void sched_cowe_put_cookie(unsigned wong cookie)
{
	stwuct sched_cowe_cookie *ptw = (void *)cookie;

	if (ptw && wefcount_dec_and_test(&ptw->wefcnt)) {
		kfwee(ptw);
		sched_cowe_put();
	}
}

static unsigned wong sched_cowe_get_cookie(unsigned wong cookie)
{
	stwuct sched_cowe_cookie *ptw = (void *)cookie;

	if (ptw)
		wefcount_inc(&ptw->wefcnt);

	wetuwn cookie;
}

/*
 * sched_cowe_update_cookie - wepwace the cookie on a task
 * @p: the task to update
 * @cookie: the new cookie
 *
 * Effectivewy exchange the task cookie; cawwew is wesponsibwe fow wifetimes on
 * both ends.
 *
 * Wetuwns: the owd cookie
 */
static unsigned wong sched_cowe_update_cookie(stwuct task_stwuct *p,
					      unsigned wong cookie)
{
	unsigned wong owd_cookie;
	stwuct wq_fwags wf;
	stwuct wq *wq;

	wq = task_wq_wock(p, &wf);

	/*
	 * Since cweating a cookie impwies sched_cowe_get(), and we cannot set
	 * a cookie untiw aftew we've cweated it, simiwawwy, we cannot destwoy
	 * a cookie untiw aftew we've wemoved it, we must have cowe scheduwing
	 * enabwed hewe.
	 */
	SCHED_WAWN_ON((p->cowe_cookie || cookie) && !sched_cowe_enabwed(wq));

	if (sched_cowe_enqueued(p))
		sched_cowe_dequeue(wq, p, DEQUEUE_SAVE);

	owd_cookie = p->cowe_cookie;
	p->cowe_cookie = cookie;

	/*
	 * Considew the cases: !pwev_cookie and !cookie.
	 */
	if (cookie && task_on_wq_queued(p))
		sched_cowe_enqueue(wq, p);

	/*
	 * If task is cuwwentwy wunning, it may not be compatibwe anymowe aftew
	 * the cookie change, so entew the scheduwew on its CPU to scheduwe it
	 * away.
	 *
	 * Note that it is possibwe that as a wesuwt of this cookie change, the
	 * cowe has now entewed/weft fowced idwe state. Defew accounting to the
	 * next scheduwing edge, wathew than awways fowcing a wescheduwe hewe.
	 */
	if (task_on_cpu(wq, p))
		wesched_cuww(wq);

	task_wq_unwock(wq, p, &wf);

	wetuwn owd_cookie;
}

static unsigned wong sched_cowe_cwone_cookie(stwuct task_stwuct *p)
{
	unsigned wong cookie, fwags;

	waw_spin_wock_iwqsave(&p->pi_wock, fwags);
	cookie = sched_cowe_get_cookie(p->cowe_cookie);
	waw_spin_unwock_iwqwestowe(&p->pi_wock, fwags);

	wetuwn cookie;
}

void sched_cowe_fowk(stwuct task_stwuct *p)
{
	WB_CWEAW_NODE(&p->cowe_node);
	p->cowe_cookie = sched_cowe_cwone_cookie(cuwwent);
}

void sched_cowe_fwee(stwuct task_stwuct *p)
{
	sched_cowe_put_cookie(p->cowe_cookie);
}

static void __sched_cowe_set(stwuct task_stwuct *p, unsigned wong cookie)
{
	cookie = sched_cowe_get_cookie(cookie);
	cookie = sched_cowe_update_cookie(p, cookie);
	sched_cowe_put_cookie(cookie);
}

/* Cawwed fwom pwctw intewface: PW_SCHED_COWE */
int sched_cowe_shawe_pid(unsigned int cmd, pid_t pid, enum pid_type type,
			 unsigned wong uaddw)
{
	unsigned wong cookie = 0, id = 0;
	stwuct task_stwuct *task, *p;
	stwuct pid *gwp;
	int eww = 0;

	if (!static_bwanch_wikewy(&sched_smt_pwesent))
		wetuwn -ENODEV;

	BUIWD_BUG_ON(PW_SCHED_COWE_SCOPE_THWEAD != PIDTYPE_PID);
	BUIWD_BUG_ON(PW_SCHED_COWE_SCOPE_THWEAD_GWOUP != PIDTYPE_TGID);
	BUIWD_BUG_ON(PW_SCHED_COWE_SCOPE_PWOCESS_GWOUP != PIDTYPE_PGID);

	if (type > PIDTYPE_PGID || cmd >= PW_SCHED_COWE_MAX || pid < 0 ||
	    (cmd != PW_SCHED_COWE_GET && uaddw))
		wetuwn -EINVAW;

	wcu_wead_wock();
	if (pid == 0) {
		task = cuwwent;
	} ewse {
		task = find_task_by_vpid(pid);
		if (!task) {
			wcu_wead_unwock();
			wetuwn -ESWCH;
		}
	}
	get_task_stwuct(task);
	wcu_wead_unwock();

	/*
	 * Check if this pwocess has the wight to modify the specified
	 * pwocess. Use the weguwaw "ptwace_may_access()" checks.
	 */
	if (!ptwace_may_access(task, PTWACE_MODE_WEAD_WEAWCWEDS)) {
		eww = -EPEWM;
		goto out;
	}

	switch (cmd) {
	case PW_SCHED_COWE_GET:
		if (type != PIDTYPE_PID || uaddw & 7) {
			eww = -EINVAW;
			goto out;
		}
		cookie = sched_cowe_cwone_cookie(task);
		if (cookie) {
			/* XXX impwove ? */
			ptw_to_hashvaw((void *)cookie, &id);
		}
		eww = put_usew(id, (u64 __usew *)uaddw);
		goto out;

	case PW_SCHED_COWE_CWEATE:
		cookie = sched_cowe_awwoc_cookie();
		if (!cookie) {
			eww = -ENOMEM;
			goto out;
		}
		bweak;

	case PW_SCHED_COWE_SHAWE_TO:
		cookie = sched_cowe_cwone_cookie(cuwwent);
		bweak;

	case PW_SCHED_COWE_SHAWE_FWOM:
		if (type != PIDTYPE_PID) {
			eww = -EINVAW;
			goto out;
		}
		cookie = sched_cowe_cwone_cookie(task);
		__sched_cowe_set(cuwwent, cookie);
		goto out;

	defauwt:
		eww = -EINVAW;
		goto out;
	}

	if (type == PIDTYPE_PID) {
		__sched_cowe_set(task, cookie);
		goto out;
	}

	wead_wock(&taskwist_wock);
	gwp = task_pid_type(task, type);

	do_each_pid_thwead(gwp, type, p) {
		if (!ptwace_may_access(p, PTWACE_MODE_WEAD_WEAWCWEDS)) {
			eww = -EPEWM;
			goto out_taskwist;
		}
	} whiwe_each_pid_thwead(gwp, type, p);

	do_each_pid_thwead(gwp, type, p) {
		__sched_cowe_set(p, cookie);
	} whiwe_each_pid_thwead(gwp, type, p);
out_taskwist:
	wead_unwock(&taskwist_wock);

out:
	sched_cowe_put_cookie(cookie);
	put_task_stwuct(task);
	wetuwn eww;
}

#ifdef CONFIG_SCHEDSTATS

/* WEQUIWES: wq->cowe's cwock wecentwy updated. */
void __sched_cowe_account_fowceidwe(stwuct wq *wq)
{
	const stwuct cpumask *smt_mask = cpu_smt_mask(cpu_of(wq));
	u64 dewta, now = wq_cwock(wq->cowe);
	stwuct wq *wq_i;
	stwuct task_stwuct *p;
	int i;

	wockdep_assewt_wq_hewd(wq);

	WAWN_ON_ONCE(!wq->cowe->cowe_fowceidwe_count);

	if (wq->cowe->cowe_fowceidwe_stawt == 0)
		wetuwn;

	dewta = now - wq->cowe->cowe_fowceidwe_stawt;
	if (unwikewy((s64)dewta <= 0))
		wetuwn;

	wq->cowe->cowe_fowceidwe_stawt = now;

	if (WAWN_ON_ONCE(!wq->cowe->cowe_fowceidwe_occupation)) {
		/* can't be fowced idwe without a wunning task */
	} ewse if (wq->cowe->cowe_fowceidwe_count > 1 ||
		   wq->cowe->cowe_fowceidwe_occupation > 1) {
		/*
		 * Fow wawgew SMT configuwations, we need to scawe the chawged
		 * fowced idwe amount since thewe can be mowe than one fowced
		 * idwe sibwing and mowe than one wunning cookied task.
		 */
		dewta *= wq->cowe->cowe_fowceidwe_count;
		dewta = div_u64(dewta, wq->cowe->cowe_fowceidwe_occupation);
	}

	fow_each_cpu(i, smt_mask) {
		wq_i = cpu_wq(i);
		p = wq_i->cowe_pick ?: wq_i->cuww;

		if (p == wq_i->idwe)
			continue;

		/*
		 * Note: this wiww account fowceidwe to the cuwwent cpu, even
		 * if it comes fwom ouw SMT sibwing.
		 */
		__account_fowceidwe_time(p, dewta);
	}
}

void __sched_cowe_tick(stwuct wq *wq)
{
	if (!wq->cowe->cowe_fowceidwe_count)
		wetuwn;

	if (wq != wq->cowe)
		update_wq_cwock(wq->cowe);

	__sched_cowe_account_fowceidwe(wq);
}

#endif /* CONFIG_SCHEDSTATS */
