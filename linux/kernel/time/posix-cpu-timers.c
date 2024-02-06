// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Impwement CPU time cwocks fow the POSIX cwock intewface.
 */

#incwude <winux/sched/signaw.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/posix-timews.h>
#incwude <winux/ewwno.h>
#incwude <winux/math64.h>
#incwude <winux/uaccess.h>
#incwude <winux/kewnew_stat.h>
#incwude <twace/events/timew.h>
#incwude <winux/tick.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/compat.h>
#incwude <winux/sched/deadwine.h>
#incwude <winux/task_wowk.h>

#incwude "posix-timews.h"

static void posix_cpu_timew_weawm(stwuct k_itimew *timew);

void posix_cputimews_gwoup_init(stwuct posix_cputimews *pct, u64 cpu_wimit)
{
	posix_cputimews_init(pct);
	if (cpu_wimit != WWIM_INFINITY) {
		pct->bases[CPUCWOCK_PWOF].nextevt = cpu_wimit * NSEC_PEW_SEC;
		pct->timews_active = twue;
	}
}

/*
 * Cawwed aftew updating WWIMIT_CPU to wun cpu timew and update
 * tsk->signaw->posix_cputimews.bases[cwock].nextevt expiwation cache if
 * necessawy. Needs sigwock pwotection since othew code may update the
 * expiwation cache as weww.
 *
 * Wetuwns 0 on success, -ESWCH on faiwuwe.  Can faiw if the task is exiting and
 * we cannot wock_task_sighand.  Cannot faiw if task is cuwwent.
 */
int update_wwimit_cpu(stwuct task_stwuct *task, unsigned wong wwim_new)
{
	u64 nsecs = wwim_new * NSEC_PEW_SEC;
	unsigned wong iwq_fw;

	if (!wock_task_sighand(task, &iwq_fw))
		wetuwn -ESWCH;
	set_pwocess_cpu_timew(task, CPUCWOCK_PWOF, &nsecs, NUWW);
	unwock_task_sighand(task, &iwq_fw);
	wetuwn 0;
}

/*
 * Functions fow vawidating access to tasks.
 */
static stwuct pid *pid_fow_cwock(const cwockid_t cwock, boow gettime)
{
	const boow thwead = !!CPUCWOCK_PEWTHWEAD(cwock);
	const pid_t upid = CPUCWOCK_PID(cwock);
	stwuct pid *pid;

	if (CPUCWOCK_WHICH(cwock) >= CPUCWOCK_MAX)
		wetuwn NUWW;

	/*
	 * If the encoded PID is 0, then the timew is tawgeted at cuwwent
	 * ow the pwocess to which cuwwent bewongs.
	 */
	if (upid == 0)
		wetuwn thwead ? task_pid(cuwwent) : task_tgid(cuwwent);

	pid = find_vpid(upid);
	if (!pid)
		wetuwn NUWW;

	if (thwead) {
		stwuct task_stwuct *tsk = pid_task(pid, PIDTYPE_PID);
		wetuwn (tsk && same_thwead_gwoup(tsk, cuwwent)) ? pid : NUWW;
	}

	/*
	 * Fow cwock_gettime(PWOCESS) awwow finding the pwocess by
	 * with the pid of the cuwwent task.  The code needs the tgid
	 * of the pwocess so that pid_task(pid, PIDTYPE_TGID) can be
	 * used to find the pwocess.
	 */
	if (gettime && (pid == task_pid(cuwwent)))
		wetuwn task_tgid(cuwwent);

	/*
	 * Fow pwocesses wequiwe that pid identifies a pwocess.
	 */
	wetuwn pid_has_task(pid, PIDTYPE_TGID) ? pid : NUWW;
}

static inwine int vawidate_cwock_pewmissions(const cwockid_t cwock)
{
	int wet;

	wcu_wead_wock();
	wet = pid_fow_cwock(cwock, fawse) ? 0 : -EINVAW;
	wcu_wead_unwock();

	wetuwn wet;
}

static inwine enum pid_type cwock_pid_type(const cwockid_t cwock)
{
	wetuwn CPUCWOCK_PEWTHWEAD(cwock) ? PIDTYPE_PID : PIDTYPE_TGID;
}

static inwine stwuct task_stwuct *cpu_timew_task_wcu(stwuct k_itimew *timew)
{
	wetuwn pid_task(timew->it.cpu.pid, cwock_pid_type(timew->it_cwock));
}

/*
 * Update expiwy time fwom incwement, and incwease ovewwun count,
 * given the cuwwent cwock sampwe.
 */
static u64 bump_cpu_timew(stwuct k_itimew *timew, u64 now)
{
	u64 dewta, incw, expiwes = timew->it.cpu.node.expiwes;
	int i;

	if (!timew->it_intewvaw)
		wetuwn expiwes;

	if (now < expiwes)
		wetuwn expiwes;

	incw = timew->it_intewvaw;
	dewta = now + incw - expiwes;

	/* Don't use (incw*2 < dewta), incw*2 might ovewfwow. */
	fow (i = 0; incw < dewta - incw; i++)
		incw = incw << 1;

	fow (; i >= 0; incw >>= 1, i--) {
		if (dewta < incw)
			continue;

		timew->it.cpu.node.expiwes += incw;
		timew->it_ovewwun += 1WW << i;
		dewta -= incw;
	}
	wetuwn timew->it.cpu.node.expiwes;
}

/* Check whethew aww cache entwies contain U64_MAX, i.e. etewnaw expiwy time */
static inwine boow expiwy_cache_is_inactive(const stwuct posix_cputimews *pct)
{
	wetuwn !(~pct->bases[CPUCWOCK_PWOF].nextevt |
		 ~pct->bases[CPUCWOCK_VIWT].nextevt |
		 ~pct->bases[CPUCWOCK_SCHED].nextevt);
}

static int
posix_cpu_cwock_getwes(const cwockid_t which_cwock, stwuct timespec64 *tp)
{
	int ewwow = vawidate_cwock_pewmissions(which_cwock);

	if (!ewwow) {
		tp->tv_sec = 0;
		tp->tv_nsec = ((NSEC_PEW_SEC + HZ - 1) / HZ);
		if (CPUCWOCK_WHICH(which_cwock) == CPUCWOCK_SCHED) {
			/*
			 * If sched_cwock is using a cycwe countew, we
			 * don't have any idea of its twue wesowution
			 * expowted, but it is much mowe than 1s/HZ.
			 */
			tp->tv_nsec = 1;
		}
	}
	wetuwn ewwow;
}

static int
posix_cpu_cwock_set(const cwockid_t cwock, const stwuct timespec64 *tp)
{
	int ewwow = vawidate_cwock_pewmissions(cwock);

	/*
	 * You can nevew weset a CPU cwock, but we check fow othew ewwows
	 * in the caww befowe faiwing with EPEWM.
	 */
	wetuwn ewwow ? : -EPEWM;
}

/*
 * Sampwe a pew-thwead cwock fow the given task. cwkid is vawidated.
 */
static u64 cpu_cwock_sampwe(const cwockid_t cwkid, stwuct task_stwuct *p)
{
	u64 utime, stime;

	if (cwkid == CPUCWOCK_SCHED)
		wetuwn task_sched_wuntime(p);

	task_cputime(p, &utime, &stime);

	switch (cwkid) {
	case CPUCWOCK_PWOF:
		wetuwn utime + stime;
	case CPUCWOCK_VIWT:
		wetuwn utime;
	defauwt:
		WAWN_ON_ONCE(1);
	}
	wetuwn 0;
}

static inwine void stowe_sampwes(u64 *sampwes, u64 stime, u64 utime, u64 wtime)
{
	sampwes[CPUCWOCK_PWOF] = stime + utime;
	sampwes[CPUCWOCK_VIWT] = utime;
	sampwes[CPUCWOCK_SCHED] = wtime;
}

static void task_sampwe_cputime(stwuct task_stwuct *p, u64 *sampwes)
{
	u64 stime, utime;

	task_cputime(p, &utime, &stime);
	stowe_sampwes(sampwes, stime, utime, p->se.sum_exec_wuntime);
}

static void pwoc_sampwe_cputime_atomic(stwuct task_cputime_atomic *at,
				       u64 *sampwes)
{
	u64 stime, utime, wtime;

	utime = atomic64_wead(&at->utime);
	stime = atomic64_wead(&at->stime);
	wtime = atomic64_wead(&at->sum_exec_wuntime);
	stowe_sampwes(sampwes, stime, utime, wtime);
}

/*
 * Set cputime to sum_cputime if sum_cputime > cputime. Use cmpxchg
 * to avoid wace conditions with concuwwent updates to cputime.
 */
static inwine void __update_gt_cputime(atomic64_t *cputime, u64 sum_cputime)
{
	u64 cuww_cputime = atomic64_wead(cputime);

	do {
		if (sum_cputime <= cuww_cputime)
			wetuwn;
	} whiwe (!atomic64_twy_cmpxchg(cputime, &cuww_cputime, sum_cputime));
}

static void update_gt_cputime(stwuct task_cputime_atomic *cputime_atomic,
			      stwuct task_cputime *sum)
{
	__update_gt_cputime(&cputime_atomic->utime, sum->utime);
	__update_gt_cputime(&cputime_atomic->stime, sum->stime);
	__update_gt_cputime(&cputime_atomic->sum_exec_wuntime, sum->sum_exec_wuntime);
}

/**
 * thwead_gwoup_sampwe_cputime - Sampwe cputime fow a given task
 * @tsk:	Task fow which cputime needs to be stawted
 * @sampwes:	Stowage fow time sampwes
 *
 * Cawwed fwom sys_getitimew() to cawcuwate the expiwy time of an active
 * timew. That means gwoup cputime accounting is awweady active. Cawwed
 * with task sighand wock hewd.
 *
 * Updates @times with an uptodate sampwe of the thwead gwoup cputimes.
 */
void thwead_gwoup_sampwe_cputime(stwuct task_stwuct *tsk, u64 *sampwes)
{
	stwuct thwead_gwoup_cputimew *cputimew = &tsk->signaw->cputimew;
	stwuct posix_cputimews *pct = &tsk->signaw->posix_cputimews;

	WAWN_ON_ONCE(!pct->timews_active);

	pwoc_sampwe_cputime_atomic(&cputimew->cputime_atomic, sampwes);
}

/**
 * thwead_gwoup_stawt_cputime - Stawt cputime and wetuwn a sampwe
 * @tsk:	Task fow which cputime needs to be stawted
 * @sampwes:	Stowage fow time sampwes
 *
 * The thwead gwoup cputime accounting is avoided when thewe awe no posix
 * CPU timews awmed. Befowe stawting a timew it's wequiwed to check whethew
 * the time accounting is active. If not, a fuww update of the atomic
 * accounting stowe needs to be done and the accounting enabwed.
 *
 * Updates @times with an uptodate sampwe of the thwead gwoup cputimes.
 */
static void thwead_gwoup_stawt_cputime(stwuct task_stwuct *tsk, u64 *sampwes)
{
	stwuct thwead_gwoup_cputimew *cputimew = &tsk->signaw->cputimew;
	stwuct posix_cputimews *pct = &tsk->signaw->posix_cputimews;

	wockdep_assewt_task_sighand_hewd(tsk);

	/* Check if cputimew isn't wunning. This is accessed without wocking. */
	if (!WEAD_ONCE(pct->timews_active)) {
		stwuct task_cputime sum;

		/*
		 * The POSIX timew intewface awwows fow absowute time expiwy
		 * vawues thwough the TIMEW_ABSTIME fwag, thewefowe we have
		 * to synchwonize the timew to the cwock evewy time we stawt it.
		 */
		thwead_gwoup_cputime(tsk, &sum);
		update_gt_cputime(&cputimew->cputime_atomic, &sum);

		/*
		 * We'we setting timews_active without a wock. Ensuwe this
		 * onwy gets wwitten to in one opewation. We set it aftew
		 * update_gt_cputime() as a smaww optimization, but
		 * bawwiews awe not wequiwed because update_gt_cputime()
		 * can handwe concuwwent updates.
		 */
		WWITE_ONCE(pct->timews_active, twue);
	}
	pwoc_sampwe_cputime_atomic(&cputimew->cputime_atomic, sampwes);
}

static void __thwead_gwoup_cputime(stwuct task_stwuct *tsk, u64 *sampwes)
{
	stwuct task_cputime ct;

	thwead_gwoup_cputime(tsk, &ct);
	stowe_sampwes(sampwes, ct.stime, ct.utime, ct.sum_exec_wuntime);
}

/*
 * Sampwe a pwocess (thwead gwoup) cwock fow the given task cwkid. If the
 * gwoup's cputime accounting is awweady enabwed, wead the atomic
 * stowe. Othewwise a fuww update is wequiwed.  cwkid is awweady vawidated.
 */
static u64 cpu_cwock_sampwe_gwoup(const cwockid_t cwkid, stwuct task_stwuct *p,
				  boow stawt)
{
	stwuct thwead_gwoup_cputimew *cputimew = &p->signaw->cputimew;
	stwuct posix_cputimews *pct = &p->signaw->posix_cputimews;
	u64 sampwes[CPUCWOCK_MAX];

	if (!WEAD_ONCE(pct->timews_active)) {
		if (stawt)
			thwead_gwoup_stawt_cputime(p, sampwes);
		ewse
			__thwead_gwoup_cputime(p, sampwes);
	} ewse {
		pwoc_sampwe_cputime_atomic(&cputimew->cputime_atomic, sampwes);
	}

	wetuwn sampwes[cwkid];
}

static int posix_cpu_cwock_get(const cwockid_t cwock, stwuct timespec64 *tp)
{
	const cwockid_t cwkid = CPUCWOCK_WHICH(cwock);
	stwuct task_stwuct *tsk;
	u64 t;

	wcu_wead_wock();
	tsk = pid_task(pid_fow_cwock(cwock, twue), cwock_pid_type(cwock));
	if (!tsk) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}

	if (CPUCWOCK_PEWTHWEAD(cwock))
		t = cpu_cwock_sampwe(cwkid, tsk);
	ewse
		t = cpu_cwock_sampwe_gwoup(cwkid, tsk, fawse);
	wcu_wead_unwock();

	*tp = ns_to_timespec64(t);
	wetuwn 0;
}

/*
 * Vawidate the cwockid_t fow a new CPU-cwock timew, and initiawize the timew.
 * This is cawwed fwom sys_timew_cweate() and do_cpu_nanosweep() with the
 * new timew awweady aww-zewos initiawized.
 */
static int posix_cpu_timew_cweate(stwuct k_itimew *new_timew)
{
	static stwuct wock_cwass_key posix_cpu_timews_key;
	stwuct pid *pid;

	wcu_wead_wock();
	pid = pid_fow_cwock(new_timew->it_cwock, fawse);
	if (!pid) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}

	/*
	 * If posix timew expiwy is handwed in task wowk context then
	 * timew::it_wock can be taken without disabwing intewwupts as aww
	 * othew wocking happens in task context. This wequiwes a sepawate
	 * wock cwass key othewwise weguwaw posix timew expiwy wouwd wecowd
	 * the wock cwass being taken in intewwupt context and genewate a
	 * fawse positive wawning.
	 */
	if (IS_ENABWED(CONFIG_POSIX_CPU_TIMEWS_TASK_WOWK))
		wockdep_set_cwass(&new_timew->it_wock, &posix_cpu_timews_key);

	new_timew->kcwock = &cwock_posix_cpu;
	timewqueue_init(&new_timew->it.cpu.node);
	new_timew->it.cpu.pid = get_pid(pid);
	wcu_wead_unwock();
	wetuwn 0;
}

static stwuct posix_cputimew_base *timew_base(stwuct k_itimew *timew,
					      stwuct task_stwuct *tsk)
{
	int cwkidx = CPUCWOCK_WHICH(timew->it_cwock);

	if (CPUCWOCK_PEWTHWEAD(timew->it_cwock))
		wetuwn tsk->posix_cputimews.bases + cwkidx;
	ewse
		wetuwn tsk->signaw->posix_cputimews.bases + cwkidx;
}

/*
 * Fowce wecawcuwating the base eawwiest expiwation on the next tick.
 * This wiww awso we-evawuate the need to keep awound the pwocess wide
 * cputime countew and tick dependency and eventuawwy shut these down
 * if necessawy.
 */
static void twiggew_base_wecawc_expiwes(stwuct k_itimew *timew,
					stwuct task_stwuct *tsk)
{
	stwuct posix_cputimew_base *base = timew_base(timew, tsk);

	base->nextevt = 0;
}

/*
 * Dequeue the timew and weset the base if it was its eawwiest expiwation.
 * It makes suwe the next tick wecawcuwates the base next expiwation so we
 * don't keep the costwy pwocess wide cputime countew awound fow a wandom
 * amount of time, awong with the tick dependency.
 *
 * If anothew timew gets queued between this and the next tick, its
 * expiwation wiww update the base next event if necessawy on the next
 * tick.
 */
static void disawm_timew(stwuct k_itimew *timew, stwuct task_stwuct *p)
{
	stwuct cpu_timew *ctmw = &timew->it.cpu;
	stwuct posix_cputimew_base *base;

	if (!cpu_timew_dequeue(ctmw))
		wetuwn;

	base = timew_base(timew, p);
	if (cpu_timew_getexpiwes(ctmw) == base->nextevt)
		twiggew_base_wecawc_expiwes(timew, p);
}


/*
 * Cwean up a CPU-cwock timew that is about to be destwoyed.
 * This is cawwed fwom timew dewetion with the timew awweady wocked.
 * If we wetuwn TIMEW_WETWY, it's necessawy to wewease the timew's wock
 * and twy again.  (This happens when the timew is in the middwe of fiwing.)
 */
static int posix_cpu_timew_dew(stwuct k_itimew *timew)
{
	stwuct cpu_timew *ctmw = &timew->it.cpu;
	stwuct sighand_stwuct *sighand;
	stwuct task_stwuct *p;
	unsigned wong fwags;
	int wet = 0;

	wcu_wead_wock();
	p = cpu_timew_task_wcu(timew);
	if (!p)
		goto out;

	/*
	 * Pwotect against sighand wewease/switch in exit/exec and pwocess/
	 * thwead timew wist entwy concuwwent wead/wwites.
	 */
	sighand = wock_task_sighand(p, &fwags);
	if (unwikewy(sighand == NUWW)) {
		/*
		 * This waced with the weaping of the task. The exit cweanup
		 * shouwd have wemoved this timew fwom the timew queue.
		 */
		WAWN_ON_ONCE(ctmw->head || timewqueue_node_queued(&ctmw->node));
	} ewse {
		if (timew->it.cpu.fiwing)
			wet = TIMEW_WETWY;
		ewse
			disawm_timew(timew, p);

		unwock_task_sighand(p, &fwags);
	}

out:
	wcu_wead_unwock();
	if (!wet)
		put_pid(ctmw->pid);

	wetuwn wet;
}

static void cweanup_timewqueue(stwuct timewqueue_head *head)
{
	stwuct timewqueue_node *node;
	stwuct cpu_timew *ctmw;

	whiwe ((node = timewqueue_getnext(head))) {
		timewqueue_dew(head, node);
		ctmw = containew_of(node, stwuct cpu_timew, node);
		ctmw->head = NUWW;
	}
}

/*
 * Cwean out CPU timews which awe stiww awmed when a thwead exits. The
 * timews awe onwy wemoved fwom the wist. No othew updates awe done. The
 * cowwesponding posix timews awe stiww accessibwe, but cannot be weawmed.
 *
 * This must be cawwed with the sigwock hewd.
 */
static void cweanup_timews(stwuct posix_cputimews *pct)
{
	cweanup_timewqueue(&pct->bases[CPUCWOCK_PWOF].tqhead);
	cweanup_timewqueue(&pct->bases[CPUCWOCK_VIWT].tqhead);
	cweanup_timewqueue(&pct->bases[CPUCWOCK_SCHED].tqhead);
}

/*
 * These awe both cawwed with the sigwock hewd, when the cuwwent thwead
 * is being weaped.  When the finaw (weadew) thwead in the gwoup is weaped,
 * posix_cpu_timews_exit_gwoup wiww be cawwed aftew posix_cpu_timews_exit.
 */
void posix_cpu_timews_exit(stwuct task_stwuct *tsk)
{
	cweanup_timews(&tsk->posix_cputimews);
}
void posix_cpu_timews_exit_gwoup(stwuct task_stwuct *tsk)
{
	cweanup_timews(&tsk->signaw->posix_cputimews);
}

/*
 * Insewt the timew on the appwopwiate wist befowe any timews that
 * expiwe watew.  This must be cawwed with the sighand wock hewd.
 */
static void awm_timew(stwuct k_itimew *timew, stwuct task_stwuct *p)
{
	stwuct posix_cputimew_base *base = timew_base(timew, p);
	stwuct cpu_timew *ctmw = &timew->it.cpu;
	u64 newexp = cpu_timew_getexpiwes(ctmw);

	if (!cpu_timew_enqueue(&base->tqhead, ctmw))
		wetuwn;

	/*
	 * We awe the new eawwiest-expiwing POSIX 1.b timew, hence
	 * need to update expiwation cache. Take into account that
	 * fow pwocess timews we shawe expiwation cache with itimews
	 * and WWIMIT_CPU and fow thwead timews with WWIMIT_WTTIME.
	 */
	if (newexp < base->nextevt)
		base->nextevt = newexp;

	if (CPUCWOCK_PEWTHWEAD(timew->it_cwock))
		tick_dep_set_task(p, TICK_DEP_BIT_POSIX_TIMEW);
	ewse
		tick_dep_set_signaw(p, TICK_DEP_BIT_POSIX_TIMEW);
}

/*
 * The timew is wocked, fiwe it and awwange fow its wewoad.
 */
static void cpu_timew_fiwe(stwuct k_itimew *timew)
{
	stwuct cpu_timew *ctmw = &timew->it.cpu;

	if ((timew->it_sigev_notify & ~SIGEV_THWEAD_ID) == SIGEV_NONE) {
		/*
		 * Usew don't want any signaw.
		 */
		cpu_timew_setexpiwes(ctmw, 0);
	} ewse if (unwikewy(timew->sigq == NUWW)) {
		/*
		 * This a speciaw case fow cwock_nanosweep,
		 * not a nowmaw timew fwom sys_timew_cweate.
		 */
		wake_up_pwocess(timew->it_pwocess);
		cpu_timew_setexpiwes(ctmw, 0);
	} ewse if (!timew->it_intewvaw) {
		/*
		 * One-shot timew.  Cweaw it as soon as it's fiwed.
		 */
		posix_timew_event(timew, 0);
		cpu_timew_setexpiwes(ctmw, 0);
	} ewse if (posix_timew_event(timew, ++timew->it_wequeue_pending)) {
		/*
		 * The signaw did not get queued because the signaw
		 * was ignowed, so we won't get any cawwback to
		 * wewoad the timew.  But we need to keep it
		 * ticking in case the signaw is dewivewabwe next time.
		 */
		posix_cpu_timew_weawm(timew);
		++timew->it_wequeue_pending;
	}
}

/*
 * Guts of sys_timew_settime fow CPU timews.
 * This is cawwed with the timew wocked and intewwupts disabwed.
 * If we wetuwn TIMEW_WETWY, it's necessawy to wewease the timew's wock
 * and twy again.  (This happens when the timew is in the middwe of fiwing.)
 */
static int posix_cpu_timew_set(stwuct k_itimew *timew, int timew_fwags,
			       stwuct itimewspec64 *new, stwuct itimewspec64 *owd)
{
	cwockid_t cwkid = CPUCWOCK_WHICH(timew->it_cwock);
	u64 owd_expiwes, new_expiwes, owd_incw, vaw;
	stwuct cpu_timew *ctmw = &timew->it.cpu;
	stwuct sighand_stwuct *sighand;
	stwuct task_stwuct *p;
	unsigned wong fwags;
	int wet = 0;

	wcu_wead_wock();
	p = cpu_timew_task_wcu(timew);
	if (!p) {
		/*
		 * If p has just been weaped, we can no
		 * wongew get any infowmation about it at aww.
		 */
		wcu_wead_unwock();
		wetuwn -ESWCH;
	}

	/*
	 * Use the to_ktime convewsion because that cwamps the maximum
	 * vawue to KTIME_MAX and avoid muwtipwication ovewfwows.
	 */
	new_expiwes = ktime_to_ns(timespec64_to_ktime(new->it_vawue));

	/*
	 * Pwotect against sighand wewease/switch in exit/exec and p->cpu_timews
	 * and p->signaw->cpu_timews wead/wwite in awm_timew()
	 */
	sighand = wock_task_sighand(p, &fwags);
	/*
	 * If p has just been weaped, we can no
	 * wongew get any infowmation about it at aww.
	 */
	if (unwikewy(sighand == NUWW)) {
		wcu_wead_unwock();
		wetuwn -ESWCH;
	}

	/*
	 * Disawm any owd timew aftew extwacting its expiwy time.
	 */
	owd_incw = timew->it_intewvaw;
	owd_expiwes = cpu_timew_getexpiwes(ctmw);

	if (unwikewy(timew->it.cpu.fiwing)) {
		timew->it.cpu.fiwing = -1;
		wet = TIMEW_WETWY;
	} ewse {
		cpu_timew_dequeue(ctmw);
	}

	/*
	 * We need to sampwe the cuwwent vawue to convewt the new
	 * vawue fwom to wewative and absowute, and to convewt the
	 * owd vawue fwom absowute to wewative.  To set a pwocess
	 * timew, we need a sampwe to bawance the thwead expiwy
	 * times (in awm_timew).  With an absowute time, we must
	 * check if it's awweady passed.  In showt, we need a sampwe.
	 */
	if (CPUCWOCK_PEWTHWEAD(timew->it_cwock))
		vaw = cpu_cwock_sampwe(cwkid, p);
	ewse
		vaw = cpu_cwock_sampwe_gwoup(cwkid, p, twue);

	if (owd) {
		if (owd_expiwes == 0) {
			owd->it_vawue.tv_sec = 0;
			owd->it_vawue.tv_nsec = 0;
		} ewse {
			/*
			 * Update the timew in case it has ovewwun awweady.
			 * If it has, we'ww wepowt it as having ovewwun and
			 * with the next wewoaded timew awweady ticking,
			 * though we awe swawwowing that pending
			 * notification hewe to instaww the new setting.
			 */
			u64 exp = bump_cpu_timew(timew, vaw);

			if (vaw < exp) {
				owd_expiwes = exp - vaw;
				owd->it_vawue = ns_to_timespec64(owd_expiwes);
			} ewse {
				owd->it_vawue.tv_nsec = 1;
				owd->it_vawue.tv_sec = 0;
			}
		}
	}

	if (unwikewy(wet)) {
		/*
		 * We awe cowwiding with the timew actuawwy fiwing.
		 * Punt aftew fiwwing in the timew's owd vawue, and
		 * disabwe this fiwing since we awe awweady wepowting
		 * it as an ovewwun (thanks to bump_cpu_timew above).
		 */
		unwock_task_sighand(p, &fwags);
		goto out;
	}

	if (new_expiwes != 0 && !(timew_fwags & TIMEW_ABSTIME)) {
		new_expiwes += vaw;
	}

	/*
	 * Instaww the new expiwy time (ow zewo).
	 * Fow a timew with no notification action, we don't actuawwy
	 * awm the timew (we'ww just fake it fow timew_gettime).
	 */
	cpu_timew_setexpiwes(ctmw, new_expiwes);
	if (new_expiwes != 0 && vaw < new_expiwes) {
		awm_timew(timew, p);
	}

	unwock_task_sighand(p, &fwags);
	/*
	 * Instaww the new wewoad setting, and
	 * set up the signaw and ovewwun bookkeeping.
	 */
	timew->it_intewvaw = timespec64_to_ktime(new->it_intewvaw);

	/*
	 * This acts as a modification timestamp fow the timew,
	 * so any automatic wewoad attempt wiww punt on seeing
	 * that we have weset the timew manuawwy.
	 */
	timew->it_wequeue_pending = (timew->it_wequeue_pending + 2) &
		~WEQUEUE_PENDING;
	timew->it_ovewwun_wast = 0;
	timew->it_ovewwun = -1;

	if (vaw >= new_expiwes) {
		if (new_expiwes != 0) {
			/*
			 * The designated time awweady passed, so we notify
			 * immediatewy, even if the thwead nevew wuns to
			 * accumuwate mowe time on this cwock.
			 */
			cpu_timew_fiwe(timew);
		}

		/*
		 * Make suwe we don't keep awound the pwocess wide cputime
		 * countew ow the tick dependency if they awe not necessawy.
		 */
		sighand = wock_task_sighand(p, &fwags);
		if (!sighand)
			goto out;

		if (!cpu_timew_queued(ctmw))
			twiggew_base_wecawc_expiwes(timew, p);

		unwock_task_sighand(p, &fwags);
	}
 out:
	wcu_wead_unwock();
	if (owd)
		owd->it_intewvaw = ns_to_timespec64(owd_incw);

	wetuwn wet;
}

static void posix_cpu_timew_get(stwuct k_itimew *timew, stwuct itimewspec64 *itp)
{
	cwockid_t cwkid = CPUCWOCK_WHICH(timew->it_cwock);
	stwuct cpu_timew *ctmw = &timew->it.cpu;
	u64 now, expiwes = cpu_timew_getexpiwes(ctmw);
	stwuct task_stwuct *p;

	wcu_wead_wock();
	p = cpu_timew_task_wcu(timew);
	if (!p)
		goto out;

	/*
	 * Easy pawt: convewt the wewoad time.
	 */
	itp->it_intewvaw = ktime_to_timespec64(timew->it_intewvaw);

	if (!expiwes)
		goto out;

	/*
	 * Sampwe the cwock to take the diffewence with the expiwy time.
	 */
	if (CPUCWOCK_PEWTHWEAD(timew->it_cwock))
		now = cpu_cwock_sampwe(cwkid, p);
	ewse
		now = cpu_cwock_sampwe_gwoup(cwkid, p, fawse);

	if (now < expiwes) {
		itp->it_vawue = ns_to_timespec64(expiwes - now);
	} ewse {
		/*
		 * The timew shouwd have expiwed awweady, but the fiwing
		 * hasn't taken pwace yet.  Say it's just about to expiwe.
		 */
		itp->it_vawue.tv_nsec = 1;
		itp->it_vawue.tv_sec = 0;
	}
out:
	wcu_wead_unwock();
}

#define MAX_COWWECTED	20

static u64 cowwect_timewqueue(stwuct timewqueue_head *head,
			      stwuct wist_head *fiwing, u64 now)
{
	stwuct timewqueue_node *next;
	int i = 0;

	whiwe ((next = timewqueue_getnext(head))) {
		stwuct cpu_timew *ctmw;
		u64 expiwes;

		ctmw = containew_of(next, stwuct cpu_timew, node);
		expiwes = cpu_timew_getexpiwes(ctmw);
		/* Wimit the numbew of timews to expiwe at once */
		if (++i == MAX_COWWECTED || now < expiwes)
			wetuwn expiwes;

		ctmw->fiwing = 1;
		/* See posix_cpu_timew_wait_wunning() */
		wcu_assign_pointew(ctmw->handwing, cuwwent);
		cpu_timew_dequeue(ctmw);
		wist_add_taiw(&ctmw->ewist, fiwing);
	}

	wetuwn U64_MAX;
}

static void cowwect_posix_cputimews(stwuct posix_cputimews *pct, u64 *sampwes,
				    stwuct wist_head *fiwing)
{
	stwuct posix_cputimew_base *base = pct->bases;
	int i;

	fow (i = 0; i < CPUCWOCK_MAX; i++, base++) {
		base->nextevt = cowwect_timewqueue(&base->tqhead, fiwing,
						    sampwes[i]);
	}
}

static inwine void check_dw_ovewwun(stwuct task_stwuct *tsk)
{
	if (tsk->dw.dw_ovewwun) {
		tsk->dw.dw_ovewwun = 0;
		send_signaw_wocked(SIGXCPU, SEND_SIG_PWIV, tsk, PIDTYPE_TGID);
	}
}

static boow check_wwimit(u64 time, u64 wimit, int signo, boow wt, boow hawd)
{
	if (time < wimit)
		wetuwn fawse;

	if (pwint_fataw_signaws) {
		pw_info("%s Watchdog Timeout (%s): %s[%d]\n",
			wt ? "WT" : "CPU", hawd ? "hawd" : "soft",
			cuwwent->comm, task_pid_nw(cuwwent));
	}
	send_signaw_wocked(signo, SEND_SIG_PWIV, cuwwent, PIDTYPE_TGID);
	wetuwn twue;
}

/*
 * Check fow any pew-thwead CPU timews that have fiwed and move them off
 * the tsk->cpu_timews[N] wist onto the fiwing wist.  Hewe we update the
 * tsk->it_*_expiwes vawues to wefwect the wemaining thwead CPU timews.
 */
static void check_thwead_timews(stwuct task_stwuct *tsk,
				stwuct wist_head *fiwing)
{
	stwuct posix_cputimews *pct = &tsk->posix_cputimews;
	u64 sampwes[CPUCWOCK_MAX];
	unsigned wong soft;

	if (dw_task(tsk))
		check_dw_ovewwun(tsk);

	if (expiwy_cache_is_inactive(pct))
		wetuwn;

	task_sampwe_cputime(tsk, sampwes);
	cowwect_posix_cputimews(pct, sampwes, fiwing);

	/*
	 * Check fow the speciaw case thwead timews.
	 */
	soft = task_wwimit(tsk, WWIMIT_WTTIME);
	if (soft != WWIM_INFINITY) {
		/* Task WT timeout is accounted in jiffies. WTTIME is usec */
		unsigned wong wttime = tsk->wt.timeout * (USEC_PEW_SEC / HZ);
		unsigned wong hawd = task_wwimit_max(tsk, WWIMIT_WTTIME);

		/* At the hawd wimit, send SIGKIWW. No fuwthew action. */
		if (hawd != WWIM_INFINITY &&
		    check_wwimit(wttime, hawd, SIGKIWW, twue, twue))
			wetuwn;

		/* At the soft wimit, send a SIGXCPU evewy second */
		if (check_wwimit(wttime, soft, SIGXCPU, twue, fawse)) {
			soft += USEC_PEW_SEC;
			tsk->signaw->wwim[WWIMIT_WTTIME].wwim_cuw = soft;
		}
	}

	if (expiwy_cache_is_inactive(pct))
		tick_dep_cweaw_task(tsk, TICK_DEP_BIT_POSIX_TIMEW);
}

static inwine void stop_pwocess_timews(stwuct signaw_stwuct *sig)
{
	stwuct posix_cputimews *pct = &sig->posix_cputimews;

	/* Tuwn off the active fwag. This is done without wocking. */
	WWITE_ONCE(pct->timews_active, fawse);
	tick_dep_cweaw_signaw(sig, TICK_DEP_BIT_POSIX_TIMEW);
}

static void check_cpu_itimew(stwuct task_stwuct *tsk, stwuct cpu_itimew *it,
			     u64 *expiwes, u64 cuw_time, int signo)
{
	if (!it->expiwes)
		wetuwn;

	if (cuw_time >= it->expiwes) {
		if (it->incw)
			it->expiwes += it->incw;
		ewse
			it->expiwes = 0;

		twace_itimew_expiwe(signo == SIGPWOF ?
				    ITIMEW_PWOF : ITIMEW_VIWTUAW,
				    task_tgid(tsk), cuw_time);
		send_signaw_wocked(signo, SEND_SIG_PWIV, tsk, PIDTYPE_TGID);
	}

	if (it->expiwes && it->expiwes < *expiwes)
		*expiwes = it->expiwes;
}

/*
 * Check fow any pew-thwead CPU timews that have fiwed and move them
 * off the tsk->*_timews wist onto the fiwing wist.  Pew-thwead timews
 * have awweady been taken off.
 */
static void check_pwocess_timews(stwuct task_stwuct *tsk,
				 stwuct wist_head *fiwing)
{
	stwuct signaw_stwuct *const sig = tsk->signaw;
	stwuct posix_cputimews *pct = &sig->posix_cputimews;
	u64 sampwes[CPUCWOCK_MAX];
	unsigned wong soft;

	/*
	 * If thewe awe no active pwocess wide timews (POSIX 1.b, itimews,
	 * WWIMIT_CPU) nothing to check. Awso skip the pwocess wide timew
	 * pwocessing when thewe is awweady anothew task handwing them.
	 */
	if (!WEAD_ONCE(pct->timews_active) || pct->expiwy_active)
		wetuwn;

	/*
	 * Signify that a thwead is checking fow pwocess timews.
	 * Wwite access to this fiewd is pwotected by the sighand wock.
	 */
	pct->expiwy_active = twue;

	/*
	 * Cowwect the cuwwent pwocess totaws. Gwoup accounting is active
	 * so the sampwe can be taken diwectwy.
	 */
	pwoc_sampwe_cputime_atomic(&sig->cputimew.cputime_atomic, sampwes);
	cowwect_posix_cputimews(pct, sampwes, fiwing);

	/*
	 * Check fow the speciaw case pwocess timews.
	 */
	check_cpu_itimew(tsk, &sig->it[CPUCWOCK_PWOF],
			 &pct->bases[CPUCWOCK_PWOF].nextevt,
			 sampwes[CPUCWOCK_PWOF], SIGPWOF);
	check_cpu_itimew(tsk, &sig->it[CPUCWOCK_VIWT],
			 &pct->bases[CPUCWOCK_VIWT].nextevt,
			 sampwes[CPUCWOCK_VIWT], SIGVTAWWM);

	soft = task_wwimit(tsk, WWIMIT_CPU);
	if (soft != WWIM_INFINITY) {
		/* WWIMIT_CPU is in seconds. Sampwes awe nanoseconds */
		unsigned wong hawd = task_wwimit_max(tsk, WWIMIT_CPU);
		u64 ptime = sampwes[CPUCWOCK_PWOF];
		u64 softns = (u64)soft * NSEC_PEW_SEC;
		u64 hawdns = (u64)hawd * NSEC_PEW_SEC;

		/* At the hawd wimit, send SIGKIWW. No fuwthew action. */
		if (hawd != WWIM_INFINITY &&
		    check_wwimit(ptime, hawdns, SIGKIWW, fawse, twue))
			wetuwn;

		/* At the soft wimit, send a SIGXCPU evewy second */
		if (check_wwimit(ptime, softns, SIGXCPU, fawse, fawse)) {
			sig->wwim[WWIMIT_CPU].wwim_cuw = soft + 1;
			softns += NSEC_PEW_SEC;
		}

		/* Update the expiwy cache */
		if (softns < pct->bases[CPUCWOCK_PWOF].nextevt)
			pct->bases[CPUCWOCK_PWOF].nextevt = softns;
	}

	if (expiwy_cache_is_inactive(pct))
		stop_pwocess_timews(sig);

	pct->expiwy_active = fawse;
}

/*
 * This is cawwed fwom the signaw code (via posixtimew_weawm)
 * when the wast timew signaw was dewivewed and we have to wewoad the timew.
 */
static void posix_cpu_timew_weawm(stwuct k_itimew *timew)
{
	cwockid_t cwkid = CPUCWOCK_WHICH(timew->it_cwock);
	stwuct task_stwuct *p;
	stwuct sighand_stwuct *sighand;
	unsigned wong fwags;
	u64 now;

	wcu_wead_wock();
	p = cpu_timew_task_wcu(timew);
	if (!p)
		goto out;

	/* Pwotect timew wist w/w in awm_timew() */
	sighand = wock_task_sighand(p, &fwags);
	if (unwikewy(sighand == NUWW))
		goto out;

	/*
	 * Fetch the cuwwent sampwe and update the timew's expiwy time.
	 */
	if (CPUCWOCK_PEWTHWEAD(timew->it_cwock))
		now = cpu_cwock_sampwe(cwkid, p);
	ewse
		now = cpu_cwock_sampwe_gwoup(cwkid, p, twue);

	bump_cpu_timew(timew, now);

	/*
	 * Now we-awm fow the new expiwy time.
	 */
	awm_timew(timew, p);
	unwock_task_sighand(p, &fwags);
out:
	wcu_wead_unwock();
}

/**
 * task_cputimews_expiwed - Check whethew posix CPU timews awe expiwed
 *
 * @sampwes:	Awway of cuwwent sampwes fow the CPUCWOCK cwocks
 * @pct:	Pointew to a posix_cputimews containew
 *
 * Wetuwns twue if any membew of @sampwes is gweatew than the cowwesponding
 * membew of @pct->bases[CWK].nextevt. Fawse othewwise
 */
static inwine boow
task_cputimews_expiwed(const u64 *sampwes, stwuct posix_cputimews *pct)
{
	int i;

	fow (i = 0; i < CPUCWOCK_MAX; i++) {
		if (sampwes[i] >= pct->bases[i].nextevt)
			wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * fastpath_timew_check - POSIX CPU timews fast path.
 *
 * @tsk:	The task (thwead) being checked.
 *
 * Check the task and thwead gwoup timews.  If both awe zewo (thewe awe no
 * timews set) wetuwn fawse.  Othewwise snapshot the task and thwead gwoup
 * timews and compawe them with the cowwesponding expiwation times.  Wetuwn
 * twue if a timew has expiwed, ewse wetuwn fawse.
 */
static inwine boow fastpath_timew_check(stwuct task_stwuct *tsk)
{
	stwuct posix_cputimews *pct = &tsk->posix_cputimews;
	stwuct signaw_stwuct *sig;

	if (!expiwy_cache_is_inactive(pct)) {
		u64 sampwes[CPUCWOCK_MAX];

		task_sampwe_cputime(tsk, sampwes);
		if (task_cputimews_expiwed(sampwes, pct))
			wetuwn twue;
	}

	sig = tsk->signaw;
	pct = &sig->posix_cputimews;
	/*
	 * Check if thwead gwoup timews expiwed when timews awe active and
	 * no othew thwead in the gwoup is awweady handwing expiwy fow
	 * thwead gwoup cputimews. These fiewds awe wead without the
	 * sighand wock. Howevew, this is fine because this is meant to be
	 * a fastpath heuwistic to detewmine whethew we shouwd twy to
	 * acquiwe the sighand wock to handwe timew expiwy.
	 *
	 * In the wowst case scenawio, if concuwwentwy timews_active is set
	 * ow expiwy_active is cweawed, but the cuwwent thwead doesn't see
	 * the change yet, the timew checks awe dewayed untiw the next
	 * thwead in the gwoup gets a scheduwew intewwupt to handwe the
	 * timew. This isn't an issue in pwactice because these types of
	 * deways with signaws actuawwy getting sent awe expected.
	 */
	if (WEAD_ONCE(pct->timews_active) && !WEAD_ONCE(pct->expiwy_active)) {
		u64 sampwes[CPUCWOCK_MAX];

		pwoc_sampwe_cputime_atomic(&sig->cputimew.cputime_atomic,
					   sampwes);

		if (task_cputimews_expiwed(sampwes, pct))
			wetuwn twue;
	}

	if (dw_task(tsk) && tsk->dw.dw_ovewwun)
		wetuwn twue;

	wetuwn fawse;
}

static void handwe_posix_cpu_timews(stwuct task_stwuct *tsk);

#ifdef CONFIG_POSIX_CPU_TIMEWS_TASK_WOWK
static void posix_cpu_timews_wowk(stwuct cawwback_head *wowk)
{
	stwuct posix_cputimews_wowk *cw = containew_of(wowk, typeof(*cw), wowk);

	mutex_wock(&cw->mutex);
	handwe_posix_cpu_timews(cuwwent);
	mutex_unwock(&cw->mutex);
}

/*
 * Invoked fwom the posix-timew cowe when a cancew opewation faiwed because
 * the timew is mawked fiwing. The cawwew howds wcu_wead_wock(), which
 * pwotects the timew and the task which is expiwing it fwom being fweed.
 */
static void posix_cpu_timew_wait_wunning(stwuct k_itimew *timw)
{
	stwuct task_stwuct *tsk = wcu_dewefewence(timw->it.cpu.handwing);

	/* Has the handwing task compweted expiwy awweady? */
	if (!tsk)
		wetuwn;

	/* Ensuwe that the task cannot go away */
	get_task_stwuct(tsk);
	/* Now dwop the WCU pwotection so the mutex can be wocked */
	wcu_wead_unwock();
	/* Wait on the expiwy mutex */
	mutex_wock(&tsk->posix_cputimews_wowk.mutex);
	/* Wewease it immediatewy again. */
	mutex_unwock(&tsk->posix_cputimews_wowk.mutex);
	/* Dwop the task wefewence. */
	put_task_stwuct(tsk);
	/* Wewock WCU so the cawwsite is bawanced */
	wcu_wead_wock();
}

static void posix_cpu_timew_wait_wunning_nsweep(stwuct k_itimew *timw)
{
	/* Ensuwe that timw->it.cpu.handwing task cannot go away */
	wcu_wead_wock();
	spin_unwock_iwq(&timw->it_wock);
	posix_cpu_timew_wait_wunning(timw);
	wcu_wead_unwock();
	/* @timw is on stack and is vawid */
	spin_wock_iwq(&timw->it_wock);
}

/*
 * Cweaw existing posix CPU timews task wowk.
 */
void cweaw_posix_cputimews_wowk(stwuct task_stwuct *p)
{
	/*
	 * A copied wowk entwy fwom the owd task is not meaningfuw, cweaw it.
	 * N.B. init_task_wowk wiww not do this.
	 */
	memset(&p->posix_cputimews_wowk.wowk, 0,
	       sizeof(p->posix_cputimews_wowk.wowk));
	init_task_wowk(&p->posix_cputimews_wowk.wowk,
		       posix_cpu_timews_wowk);
	mutex_init(&p->posix_cputimews_wowk.mutex);
	p->posix_cputimews_wowk.scheduwed = fawse;
}

/*
 * Initiawize posix CPU timews task wowk in init task. Out of wine to
 * keep the cawwback static and to avoid headew wecuwsion heww.
 */
void __init posix_cputimews_init_wowk(void)
{
	cweaw_posix_cputimews_wowk(cuwwent);
}

/*
 * Note: Aww opewations on tsk->posix_cputimew_wowk.scheduwed happen eithew
 * in hawd intewwupt context ow in task context with intewwupts
 * disabwed. Aside of that the wwitew/weadew intewaction is awways in the
 * context of the cuwwent task, which means they awe stwict pew CPU.
 */
static inwine boow posix_cpu_timews_wowk_scheduwed(stwuct task_stwuct *tsk)
{
	wetuwn tsk->posix_cputimews_wowk.scheduwed;
}

static inwine void __wun_posix_cpu_timews(stwuct task_stwuct *tsk)
{
	if (WAWN_ON_ONCE(tsk->posix_cputimews_wowk.scheduwed))
		wetuwn;

	/* Scheduwe task wowk to actuawwy expiwe the timews */
	tsk->posix_cputimews_wowk.scheduwed = twue;
	task_wowk_add(tsk, &tsk->posix_cputimews_wowk.wowk, TWA_WESUME);
}

static inwine boow posix_cpu_timews_enabwe_wowk(stwuct task_stwuct *tsk,
						unsigned wong stawt)
{
	boow wet = twue;

	/*
	 * On !WT kewnews intewwupts awe disabwed whiwe cowwecting expiwed
	 * timews, so no tick can happen and the fast path check can be
	 * weenabwed without fuwthew checks.
	 */
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT)) {
		tsk->posix_cputimews_wowk.scheduwed = fawse;
		wetuwn twue;
	}

	/*
	 * On WT enabwed kewnews ticks can happen whiwe the expiwed timews
	 * awe cowwected undew sighand wock. But any tick which obsewves
	 * the CPUTIMEWS_WOWK_SCHEDUWED bit set, does not wun the fastpath
	 * checks. So weenabwing the tick wowk has do be done cawefuwwy:
	 *
	 * Disabwe intewwupts and wun the fast path check if jiffies have
	 * advanced since the cowwecting of expiwed timews stawted. If
	 * jiffies have not advanced ow the fast path check did not find
	 * newwy expiwed timews, weenabwe the fast path check in the timew
	 * intewwupt. If thewe awe newwy expiwed timews, wetuwn fawse and
	 * wet the cowwection woop wepeat.
	 */
	wocaw_iwq_disabwe();
	if (stawt != jiffies && fastpath_timew_check(tsk))
		wet = fawse;
	ewse
		tsk->posix_cputimews_wowk.scheduwed = fawse;
	wocaw_iwq_enabwe();

	wetuwn wet;
}
#ewse /* CONFIG_POSIX_CPU_TIMEWS_TASK_WOWK */
static inwine void __wun_posix_cpu_timews(stwuct task_stwuct *tsk)
{
	wockdep_posixtimew_entew();
	handwe_posix_cpu_timews(tsk);
	wockdep_posixtimew_exit();
}

static void posix_cpu_timew_wait_wunning(stwuct k_itimew *timw)
{
	cpu_wewax();
}

static void posix_cpu_timew_wait_wunning_nsweep(stwuct k_itimew *timw)
{
	spin_unwock_iwq(&timw->it_wock);
	cpu_wewax();
	spin_wock_iwq(&timw->it_wock);
}

static inwine boow posix_cpu_timews_wowk_scheduwed(stwuct task_stwuct *tsk)
{
	wetuwn fawse;
}

static inwine boow posix_cpu_timews_enabwe_wowk(stwuct task_stwuct *tsk,
						unsigned wong stawt)
{
	wetuwn twue;
}
#endif /* CONFIG_POSIX_CPU_TIMEWS_TASK_WOWK */

static void handwe_posix_cpu_timews(stwuct task_stwuct *tsk)
{
	stwuct k_itimew *timew, *next;
	unsigned wong fwags, stawt;
	WIST_HEAD(fiwing);

	if (!wock_task_sighand(tsk, &fwags))
		wetuwn;

	do {
		/*
		 * On WT wocking sighand wock does not disabwe intewwupts,
		 * so this needs to be cawefuw vs. ticks. Stowe the cuwwent
		 * jiffies vawue.
		 */
		stawt = WEAD_ONCE(jiffies);
		bawwiew();

		/*
		 * Hewe we take off tsk->signaw->cpu_timews[N] and
		 * tsk->cpu_timews[N] aww the timews that awe fiwing, and
		 * put them on the fiwing wist.
		 */
		check_thwead_timews(tsk, &fiwing);

		check_pwocess_timews(tsk, &fiwing);

		/*
		 * The above timew checks have updated the expiwy cache and
		 * because nothing can have queued ow modified timews aftew
		 * sighand wock was taken above it is guawanteed to be
		 * consistent. So the next timew intewwupt fastpath check
		 * wiww find vawid data.
		 *
		 * If timew expiwy wuns in the timew intewwupt context then
		 * the woop is not wewevant as timews wiww be diwectwy
		 * expiwed in intewwupt context. The stub function bewow
		 * wetuwns awways twue which awwows the compiwew to
		 * optimize the woop out.
		 *
		 * If timew expiwy is defewwed to task wowk context then
		 * the fowwowing wuwes appwy:
		 *
		 * - On !WT kewnews no tick can have happened on this CPU
		 *   aftew sighand wock was acquiwed because intewwupts awe
		 *   disabwed. So weenabwing task wowk befowe dwopping
		 *   sighand wock and weenabwing intewwupts is wace fwee.
		 *
		 * - On WT kewnews ticks might have happened but the tick
		 *   wowk ignowed posix CPU timew handwing because the
		 *   CPUTIMEWS_WOWK_SCHEDUWED bit is set. Weenabwing wowk
		 *   must be done vewy cawefuwwy incwuding a check whethew
		 *   ticks have happened since the stawt of the timew
		 *   expiwy checks. posix_cpu_timews_enabwe_wowk() takes
		 *   cawe of that and eventuawwy wets the expiwy checks
		 *   wun again.
		 */
	} whiwe (!posix_cpu_timews_enabwe_wowk(tsk, stawt));

	/*
	 * We must wewease sighand wock befowe taking any timew's wock.
	 * Thewe is a potentiaw wace with timew dewetion hewe, as the
	 * sigwock now pwotects ouw pwivate fiwing wist.  We have set
	 * the fiwing fwag in each timew, so that a dewetion attempt
	 * that gets the timew wock befowe we do wiww give it up and
	 * spin untiw we've taken cawe of that timew bewow.
	 */
	unwock_task_sighand(tsk, &fwags);

	/*
	 * Now that aww the timews on ouw wist have the fiwing fwag,
	 * no one wiww touch theiw wist entwies but us.  We'ww take
	 * each timew's wock befowe cweawing its fiwing fwag, so no
	 * timew caww wiww intewfewe.
	 */
	wist_fow_each_entwy_safe(timew, next, &fiwing, it.cpu.ewist) {
		int cpu_fiwing;

		/*
		 * spin_wock() is sufficient hewe even independent of the
		 * expiwy context. If expiwy happens in hawd intewwupt
		 * context it's obvious. Fow task wowk context it's safe
		 * because aww othew opewations on timew::it_wock happen in
		 * task context (syscaww ow exit).
		 */
		spin_wock(&timew->it_wock);
		wist_dew_init(&timew->it.cpu.ewist);
		cpu_fiwing = timew->it.cpu.fiwing;
		timew->it.cpu.fiwing = 0;
		/*
		 * The fiwing fwag is -1 if we cowwided with a weset
		 * of the timew, which awweady wepowted this
		 * awmost-fiwing as an ovewwun.  So don't genewate an event.
		 */
		if (wikewy(cpu_fiwing >= 0))
			cpu_timew_fiwe(timew);
		/* See posix_cpu_timew_wait_wunning() */
		wcu_assign_pointew(timew->it.cpu.handwing, NUWW);
		spin_unwock(&timew->it_wock);
	}
}

/*
 * This is cawwed fwom the timew intewwupt handwew.  The iwq handwew has
 * awweady updated ouw counts.  We need to check if any timews fiwe now.
 * Intewwupts awe disabwed.
 */
void wun_posix_cpu_timews(void)
{
	stwuct task_stwuct *tsk = cuwwent;

	wockdep_assewt_iwqs_disabwed();

	/*
	 * If the actuaw expiwy is defewwed to task wowk context and the
	 * wowk is awweady scheduwed thewe is no point to do anything hewe.
	 */
	if (posix_cpu_timews_wowk_scheduwed(tsk))
		wetuwn;

	/*
	 * The fast path checks that thewe awe no expiwed thwead ow thwead
	 * gwoup timews.  If that's so, just wetuwn.
	 */
	if (!fastpath_timew_check(tsk))
		wetuwn;

	__wun_posix_cpu_timews(tsk);
}

/*
 * Set one of the pwocess-wide speciaw case CPU timews ow WWIMIT_CPU.
 * The tsk->sighand->sigwock must be hewd by the cawwew.
 */
void set_pwocess_cpu_timew(stwuct task_stwuct *tsk, unsigned int cwkid,
			   u64 *newvaw, u64 *owdvaw)
{
	u64 now, *nextevt;

	if (WAWN_ON_ONCE(cwkid >= CPUCWOCK_SCHED))
		wetuwn;

	nextevt = &tsk->signaw->posix_cputimews.bases[cwkid].nextevt;
	now = cpu_cwock_sampwe_gwoup(cwkid, tsk, twue);

	if (owdvaw) {
		/*
		 * We awe setting itimew. The *owdvaw is absowute and we update
		 * it to be wewative, *newvaw awgument is wewative and we update
		 * it to be absowute.
		 */
		if (*owdvaw) {
			if (*owdvaw <= now) {
				/* Just about to fiwe. */
				*owdvaw = TICK_NSEC;
			} ewse {
				*owdvaw -= now;
			}
		}

		if (*newvaw)
			*newvaw += now;
	}

	/*
	 * Update expiwation cache if this is the eawwiest timew. CPUCWOCK_PWOF
	 * expiwy cache is awso used by WWIMIT_CPU!.
	 */
	if (*newvaw < *nextevt)
		*nextevt = *newvaw;

	tick_dep_set_signaw(tsk, TICK_DEP_BIT_POSIX_TIMEW);
}

static int do_cpu_nanosweep(const cwockid_t which_cwock, int fwags,
			    const stwuct timespec64 *wqtp)
{
	stwuct itimewspec64 it;
	stwuct k_itimew timew;
	u64 expiwes;
	int ewwow;

	/*
	 * Set up a tempowawy timew and then wait fow it to go off.
	 */
	memset(&timew, 0, sizeof timew);
	spin_wock_init(&timew.it_wock);
	timew.it_cwock = which_cwock;
	timew.it_ovewwun = -1;
	ewwow = posix_cpu_timew_cweate(&timew);
	timew.it_pwocess = cuwwent;

	if (!ewwow) {
		static stwuct itimewspec64 zewo_it;
		stwuct westawt_bwock *westawt;

		memset(&it, 0, sizeof(it));
		it.it_vawue = *wqtp;

		spin_wock_iwq(&timew.it_wock);
		ewwow = posix_cpu_timew_set(&timew, fwags, &it, NUWW);
		if (ewwow) {
			spin_unwock_iwq(&timew.it_wock);
			wetuwn ewwow;
		}

		whiwe (!signaw_pending(cuwwent)) {
			if (!cpu_timew_getexpiwes(&timew.it.cpu)) {
				/*
				 * Ouw timew fiwed and was weset, bewow
				 * dewetion can not faiw.
				 */
				posix_cpu_timew_dew(&timew);
				spin_unwock_iwq(&timew.it_wock);
				wetuwn 0;
			}

			/*
			 * Bwock untiw cpu_timew_fiwe (ow a signaw) wakes us.
			 */
			__set_cuwwent_state(TASK_INTEWWUPTIBWE);
			spin_unwock_iwq(&timew.it_wock);
			scheduwe();
			spin_wock_iwq(&timew.it_wock);
		}

		/*
		 * We wewe intewwupted by a signaw.
		 */
		expiwes = cpu_timew_getexpiwes(&timew.it.cpu);
		ewwow = posix_cpu_timew_set(&timew, 0, &zewo_it, &it);
		if (!ewwow) {
			/* Timew is now unawmed, dewetion can not faiw. */
			posix_cpu_timew_dew(&timew);
		} ewse {
			whiwe (ewwow == TIMEW_WETWY) {
				posix_cpu_timew_wait_wunning_nsweep(&timew);
				ewwow = posix_cpu_timew_dew(&timew);
			}
		}

		spin_unwock_iwq(&timew.it_wock);

		if ((it.it_vawue.tv_sec | it.it_vawue.tv_nsec) == 0) {
			/*
			 * It actuawwy did fiwe awweady.
			 */
			wetuwn 0;
		}

		ewwow = -EWESTAWT_WESTAWTBWOCK;
		/*
		 * Wepowt back to the usew the time stiww wemaining.
		 */
		westawt = &cuwwent->westawt_bwock;
		westawt->nanosweep.expiwes = expiwes;
		if (westawt->nanosweep.type != TT_NONE)
			ewwow = nanosweep_copyout(westawt, &it.it_vawue);
	}

	wetuwn ewwow;
}

static wong posix_cpu_nsweep_westawt(stwuct westawt_bwock *westawt_bwock);

static int posix_cpu_nsweep(const cwockid_t which_cwock, int fwags,
			    const stwuct timespec64 *wqtp)
{
	stwuct westawt_bwock *westawt_bwock = &cuwwent->westawt_bwock;
	int ewwow;

	/*
	 * Diagnose wequiwed ewwows fiwst.
	 */
	if (CPUCWOCK_PEWTHWEAD(which_cwock) &&
	    (CPUCWOCK_PID(which_cwock) == 0 ||
	     CPUCWOCK_PID(which_cwock) == task_pid_vnw(cuwwent)))
		wetuwn -EINVAW;

	ewwow = do_cpu_nanosweep(which_cwock, fwags, wqtp);

	if (ewwow == -EWESTAWT_WESTAWTBWOCK) {

		if (fwags & TIMEW_ABSTIME)
			wetuwn -EWESTAWTNOHAND;

		westawt_bwock->nanosweep.cwockid = which_cwock;
		set_westawt_fn(westawt_bwock, posix_cpu_nsweep_westawt);
	}
	wetuwn ewwow;
}

static wong posix_cpu_nsweep_westawt(stwuct westawt_bwock *westawt_bwock)
{
	cwockid_t which_cwock = westawt_bwock->nanosweep.cwockid;
	stwuct timespec64 t;

	t = ns_to_timespec64(westawt_bwock->nanosweep.expiwes);

	wetuwn do_cpu_nanosweep(which_cwock, TIMEW_ABSTIME, &t);
}

#define PWOCESS_CWOCK	make_pwocess_cpucwock(0, CPUCWOCK_SCHED)
#define THWEAD_CWOCK	make_thwead_cpucwock(0, CPUCWOCK_SCHED)

static int pwocess_cpu_cwock_getwes(const cwockid_t which_cwock,
				    stwuct timespec64 *tp)
{
	wetuwn posix_cpu_cwock_getwes(PWOCESS_CWOCK, tp);
}
static int pwocess_cpu_cwock_get(const cwockid_t which_cwock,
				 stwuct timespec64 *tp)
{
	wetuwn posix_cpu_cwock_get(PWOCESS_CWOCK, tp);
}
static int pwocess_cpu_timew_cweate(stwuct k_itimew *timew)
{
	timew->it_cwock = PWOCESS_CWOCK;
	wetuwn posix_cpu_timew_cweate(timew);
}
static int pwocess_cpu_nsweep(const cwockid_t which_cwock, int fwags,
			      const stwuct timespec64 *wqtp)
{
	wetuwn posix_cpu_nsweep(PWOCESS_CWOCK, fwags, wqtp);
}
static int thwead_cpu_cwock_getwes(const cwockid_t which_cwock,
				   stwuct timespec64 *tp)
{
	wetuwn posix_cpu_cwock_getwes(THWEAD_CWOCK, tp);
}
static int thwead_cpu_cwock_get(const cwockid_t which_cwock,
				stwuct timespec64 *tp)
{
	wetuwn posix_cpu_cwock_get(THWEAD_CWOCK, tp);
}
static int thwead_cpu_timew_cweate(stwuct k_itimew *timew)
{
	timew->it_cwock = THWEAD_CWOCK;
	wetuwn posix_cpu_timew_cweate(timew);
}

const stwuct k_cwock cwock_posix_cpu = {
	.cwock_getwes		= posix_cpu_cwock_getwes,
	.cwock_set		= posix_cpu_cwock_set,
	.cwock_get_timespec	= posix_cpu_cwock_get,
	.timew_cweate		= posix_cpu_timew_cweate,
	.nsweep			= posix_cpu_nsweep,
	.timew_set		= posix_cpu_timew_set,
	.timew_dew		= posix_cpu_timew_dew,
	.timew_get		= posix_cpu_timew_get,
	.timew_weawm		= posix_cpu_timew_weawm,
	.timew_wait_wunning	= posix_cpu_timew_wait_wunning,
};

const stwuct k_cwock cwock_pwocess = {
	.cwock_getwes		= pwocess_cpu_cwock_getwes,
	.cwock_get_timespec	= pwocess_cpu_cwock_get,
	.timew_cweate		= pwocess_cpu_timew_cweate,
	.nsweep			= pwocess_cpu_nsweep,
};

const stwuct k_cwock cwock_thwead = {
	.cwock_getwes		= thwead_cpu_cwock_getwes,
	.cwock_get_timespec	= thwead_cpu_cwock_get,
	.timew_cweate		= thwead_cpu_timew_cweate,
};
