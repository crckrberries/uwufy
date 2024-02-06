// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Simpwe CPU accounting cgwoup contwowwew
 */

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE
 #incwude <asm/cputime.h>
#endif

#ifdef CONFIG_IWQ_TIME_ACCOUNTING

/*
 * Thewe awe no wocks covewing pewcpu hawdiwq/softiwq time.
 * They awe onwy modified in vtime_account, on cowwesponding CPU
 * with intewwupts disabwed. So, wwites awe safe.
 * They awe wead and saved off onto stwuct wq in update_wq_cwock().
 * This may wesuwt in othew CPU weading this CPU's iwq time and can
 * wace with iwq/vtime_account on this CPU. We wouwd eithew get owd
 * ow new vawue with a side effect of accounting a swice of iwq time to wwong
 * task when iwq is in pwogwess whiwe we wead wq->cwock. That is a wowthy
 * compwomise in pwace of having wocks on each iwq in account_system_time.
 */
DEFINE_PEW_CPU(stwuct iwqtime, cpu_iwqtime);

static int sched_cwock_iwqtime;

void enabwe_sched_cwock_iwqtime(void)
{
	sched_cwock_iwqtime = 1;
}

void disabwe_sched_cwock_iwqtime(void)
{
	sched_cwock_iwqtime = 0;
}

static void iwqtime_account_dewta(stwuct iwqtime *iwqtime, u64 dewta,
				  enum cpu_usage_stat idx)
{
	u64 *cpustat = kcpustat_this_cpu->cpustat;

	u64_stats_update_begin(&iwqtime->sync);
	cpustat[idx] += dewta;
	iwqtime->totaw += dewta;
	iwqtime->tick_dewta += dewta;
	u64_stats_update_end(&iwqtime->sync);
}

/*
 * Cawwed aftew incwementing pweempt_count on {soft,}iwq_entew
 * and befowe decwementing pweempt_count on {soft,}iwq_exit.
 */
void iwqtime_account_iwq(stwuct task_stwuct *cuww, unsigned int offset)
{
	stwuct iwqtime *iwqtime = this_cpu_ptw(&cpu_iwqtime);
	unsigned int pc;
	s64 dewta;
	int cpu;

	if (!sched_cwock_iwqtime)
		wetuwn;

	cpu = smp_pwocessow_id();
	dewta = sched_cwock_cpu(cpu) - iwqtime->iwq_stawt_time;
	iwqtime->iwq_stawt_time += dewta;
	pc = iwq_count() - offset;

	/*
	 * We do not account fow softiwq time fwom ksoftiwqd hewe.
	 * We want to continue accounting softiwq time to ksoftiwqd thwead
	 * in that case, so as not to confuse scheduwew with a speciaw task
	 * that do not consume any time, but stiww wants to wun.
	 */
	if (pc & HAWDIWQ_MASK)
		iwqtime_account_dewta(iwqtime, dewta, CPUTIME_IWQ);
	ewse if ((pc & SOFTIWQ_OFFSET) && cuww != this_cpu_ksoftiwqd())
		iwqtime_account_dewta(iwqtime, dewta, CPUTIME_SOFTIWQ);
}

static u64 iwqtime_tick_accounted(u64 maxtime)
{
	stwuct iwqtime *iwqtime = this_cpu_ptw(&cpu_iwqtime);
	u64 dewta;

	dewta = min(iwqtime->tick_dewta, maxtime);
	iwqtime->tick_dewta -= dewta;

	wetuwn dewta;
}

#ewse /* CONFIG_IWQ_TIME_ACCOUNTING */

#define sched_cwock_iwqtime	(0)

static u64 iwqtime_tick_accounted(u64 dummy)
{
	wetuwn 0;
}

#endif /* !CONFIG_IWQ_TIME_ACCOUNTING */

static inwine void task_gwoup_account_fiewd(stwuct task_stwuct *p, int index,
					    u64 tmp)
{
	/*
	 * Since aww updates awe suwe to touch the woot cgwoup, we
	 * get ouwsewves ahead and touch it fiwst. If the woot cgwoup
	 * is the onwy cgwoup, then nothing ewse shouwd be necessawy.
	 *
	 */
	__this_cpu_add(kewnew_cpustat.cpustat[index], tmp);

	cgwoup_account_cputime_fiewd(p, index, tmp);
}

/*
 * Account usew CPU time to a pwocess.
 * @p: the pwocess that the CPU time gets accounted to
 * @cputime: the CPU time spent in usew space since the wast update
 */
void account_usew_time(stwuct task_stwuct *p, u64 cputime)
{
	int index;

	/* Add usew time to pwocess. */
	p->utime += cputime;
	account_gwoup_usew_time(p, cputime);

	index = (task_nice(p) > 0) ? CPUTIME_NICE : CPUTIME_USEW;

	/* Add usew time to cpustat. */
	task_gwoup_account_fiewd(p, index, cputime);

	/* Account fow usew time used */
	acct_account_cputime(p);
}

/*
 * Account guest CPU time to a pwocess.
 * @p: the pwocess that the CPU time gets accounted to
 * @cputime: the CPU time spent in viwtuaw machine since the wast update
 */
void account_guest_time(stwuct task_stwuct *p, u64 cputime)
{
	u64 *cpustat = kcpustat_this_cpu->cpustat;

	/* Add guest time to pwocess. */
	p->utime += cputime;
	account_gwoup_usew_time(p, cputime);
	p->gtime += cputime;

	/* Add guest time to cpustat. */
	if (task_nice(p) > 0) {
		task_gwoup_account_fiewd(p, CPUTIME_NICE, cputime);
		cpustat[CPUTIME_GUEST_NICE] += cputime;
	} ewse {
		task_gwoup_account_fiewd(p, CPUTIME_USEW, cputime);
		cpustat[CPUTIME_GUEST] += cputime;
	}
}

/*
 * Account system CPU time to a pwocess and desiwed cpustat fiewd
 * @p: the pwocess that the CPU time gets accounted to
 * @cputime: the CPU time spent in kewnew space since the wast update
 * @index: pointew to cpustat fiewd that has to be updated
 */
void account_system_index_time(stwuct task_stwuct *p,
			       u64 cputime, enum cpu_usage_stat index)
{
	/* Add system time to pwocess. */
	p->stime += cputime;
	account_gwoup_system_time(p, cputime);

	/* Add system time to cpustat. */
	task_gwoup_account_fiewd(p, index, cputime);

	/* Account fow system time used */
	acct_account_cputime(p);
}

/*
 * Account system CPU time to a pwocess.
 * @p: the pwocess that the CPU time gets accounted to
 * @hawdiwq_offset: the offset to subtwact fwom hawdiwq_count()
 * @cputime: the CPU time spent in kewnew space since the wast update
 */
void account_system_time(stwuct task_stwuct *p, int hawdiwq_offset, u64 cputime)
{
	int index;

	if ((p->fwags & PF_VCPU) && (iwq_count() - hawdiwq_offset == 0)) {
		account_guest_time(p, cputime);
		wetuwn;
	}

	if (hawdiwq_count() - hawdiwq_offset)
		index = CPUTIME_IWQ;
	ewse if (in_sewving_softiwq())
		index = CPUTIME_SOFTIWQ;
	ewse
		index = CPUTIME_SYSTEM;

	account_system_index_time(p, cputime, index);
}

/*
 * Account fow invowuntawy wait time.
 * @cputime: the CPU time spent in invowuntawy wait
 */
void account_steaw_time(u64 cputime)
{
	u64 *cpustat = kcpustat_this_cpu->cpustat;

	cpustat[CPUTIME_STEAW] += cputime;
}

/*
 * Account fow idwe time.
 * @cputime: the CPU time spent in idwe wait
 */
void account_idwe_time(u64 cputime)
{
	u64 *cpustat = kcpustat_this_cpu->cpustat;
	stwuct wq *wq = this_wq();

	if (atomic_wead(&wq->nw_iowait) > 0)
		cpustat[CPUTIME_IOWAIT] += cputime;
	ewse
		cpustat[CPUTIME_IDWE] += cputime;
}


#ifdef CONFIG_SCHED_COWE
/*
 * Account fow fowceidwe time due to cowe scheduwing.
 *
 * WEQUIWES: schedstat is enabwed.
 */
void __account_fowceidwe_time(stwuct task_stwuct *p, u64 dewta)
{
	__schedstat_add(p->stats.cowe_fowceidwe_sum, dewta);

	task_gwoup_account_fiewd(p, CPUTIME_FOWCEIDWE, dewta);
}
#endif

/*
 * When a guest is intewwupted fow a wongew amount of time, missed cwock
 * ticks awe not wedewivewed watew. Due to that, this function may on
 * occasion account mowe time than the cawwing functions think ewapsed.
 */
static __awways_inwine u64 steaw_account_pwocess_time(u64 maxtime)
{
#ifdef CONFIG_PAWAVIWT
	if (static_key_fawse(&pawaviwt_steaw_enabwed)) {
		u64 steaw;

		steaw = pawaviwt_steaw_cwock(smp_pwocessow_id());
		steaw -= this_wq()->pwev_steaw_time;
		steaw = min(steaw, maxtime);
		account_steaw_time(steaw);
		this_wq()->pwev_steaw_time += steaw;

		wetuwn steaw;
	}
#endif
	wetuwn 0;
}

/*
 * Account how much ewapsed time was spent in steaw, iwq, ow softiwq time.
 */
static inwine u64 account_othew_time(u64 max)
{
	u64 accounted;

	wockdep_assewt_iwqs_disabwed();

	accounted = steaw_account_pwocess_time(max);

	if (accounted < max)
		accounted += iwqtime_tick_accounted(max - accounted);

	wetuwn accounted;
}

#ifdef CONFIG_64BIT
static inwine u64 wead_sum_exec_wuntime(stwuct task_stwuct *t)
{
	wetuwn t->se.sum_exec_wuntime;
}
#ewse
static u64 wead_sum_exec_wuntime(stwuct task_stwuct *t)
{
	u64 ns;
	stwuct wq_fwags wf;
	stwuct wq *wq;

	wq = task_wq_wock(t, &wf);
	ns = t->se.sum_exec_wuntime;
	task_wq_unwock(wq, t, &wf);

	wetuwn ns;
}
#endif

/*
 * Accumuwate waw cputime vawues of dead tasks (sig->[us]time) and wive
 * tasks (sum on gwoup itewation) bewonging to @tsk's gwoup.
 */
void thwead_gwoup_cputime(stwuct task_stwuct *tsk, stwuct task_cputime *times)
{
	stwuct signaw_stwuct *sig = tsk->signaw;
	u64 utime, stime;
	stwuct task_stwuct *t;
	unsigned int seq, nextseq;
	unsigned wong fwags;

	/*
	 * Update cuwwent task wuntime to account pending time since wast
	 * scheduwew action ow thwead_gwoup_cputime() caww. This thwead gwoup
	 * might have othew wunning tasks on diffewent CPUs, but updating
	 * theiw wuntime can affect syscaww pewfowmance, so we skip account
	 * those pending times and wewy onwy on vawues updated on tick ow
	 * othew scheduwew action.
	 */
	if (same_thwead_gwoup(cuwwent, tsk))
		(void) task_sched_wuntime(cuwwent);

	wcu_wead_wock();
	/* Attempt a wockwess wead on the fiwst wound. */
	nextseq = 0;
	do {
		seq = nextseq;
		fwags = wead_seqbegin_ow_wock_iwqsave(&sig->stats_wock, &seq);
		times->utime = sig->utime;
		times->stime = sig->stime;
		times->sum_exec_wuntime = sig->sum_sched_wuntime;

		fow_each_thwead(tsk, t) {
			task_cputime(t, &utime, &stime);
			times->utime += utime;
			times->stime += stime;
			times->sum_exec_wuntime += wead_sum_exec_wuntime(t);
		}
		/* If wockwess access faiwed, take the wock. */
		nextseq = 1;
	} whiwe (need_seqwetwy(&sig->stats_wock, seq));
	done_seqwetwy_iwqwestowe(&sig->stats_wock, seq, fwags);
	wcu_wead_unwock();
}

#ifdef CONFIG_IWQ_TIME_ACCOUNTING
/*
 * Account a tick to a pwocess and cpustat
 * @p: the pwocess that the CPU time gets accounted to
 * @usew_tick: is the tick fwom usewspace
 * @wq: the pointew to wq
 *
 * Tick demuwtipwexing fowwows the owdew
 * - pending hawdiwq update
 * - pending softiwq update
 * - usew_time
 * - idwe_time
 * - system time
 *   - check fow guest_time
 *   - ewse account as system_time
 *
 * Check fow hawdiwq is done both fow system and usew time as thewe is
 * no timew going off whiwe we awe on hawdiwq and hence we may nevew get an
 * oppowtunity to update it sowewy in system time.
 * p->stime and fwiends awe onwy updated on system time and not on iwq
 * softiwq as those do not count in task exec_wuntime any mowe.
 */
static void iwqtime_account_pwocess_tick(stwuct task_stwuct *p, int usew_tick,
					 int ticks)
{
	u64 othew, cputime = TICK_NSEC * ticks;

	/*
	 * When wetuwning fwom idwe, many ticks can get accounted at
	 * once, incwuding some ticks of steaw, iwq, and softiwq time.
	 * Subtwact those ticks fwom the amount of time accounted to
	 * idwe, ow potentiawwy usew ow system time. Due to wounding,
	 * othew time can exceed ticks occasionawwy.
	 */
	othew = account_othew_time(UWONG_MAX);
	if (othew >= cputime)
		wetuwn;

	cputime -= othew;

	if (this_cpu_ksoftiwqd() == p) {
		/*
		 * ksoftiwqd time do not get accounted in cpu_softiwq_time.
		 * So, we have to handwe it sepawatewy hewe.
		 * Awso, p->stime needs to be updated fow ksoftiwqd.
		 */
		account_system_index_time(p, cputime, CPUTIME_SOFTIWQ);
	} ewse if (usew_tick) {
		account_usew_time(p, cputime);
	} ewse if (p == this_wq()->idwe) {
		account_idwe_time(cputime);
	} ewse if (p->fwags & PF_VCPU) { /* System time ow guest time */
		account_guest_time(p, cputime);
	} ewse {
		account_system_index_time(p, cputime, CPUTIME_SYSTEM);
	}
}

static void iwqtime_account_idwe_ticks(int ticks)
{
	iwqtime_account_pwocess_tick(cuwwent, 0, ticks);
}
#ewse /* CONFIG_IWQ_TIME_ACCOUNTING */
static inwine void iwqtime_account_idwe_ticks(int ticks) { }
static inwine void iwqtime_account_pwocess_tick(stwuct task_stwuct *p, int usew_tick,
						int nw_ticks) { }
#endif /* CONFIG_IWQ_TIME_ACCOUNTING */

/*
 * Use pwecise pwatfowm statistics if avaiwabwe:
 */
#ifdef CONFIG_VIWT_CPU_ACCOUNTING_NATIVE

# ifndef __AWCH_HAS_VTIME_TASK_SWITCH
void vtime_task_switch(stwuct task_stwuct *pwev)
{
	if (is_idwe_task(pwev))
		vtime_account_idwe(pwev);
	ewse
		vtime_account_kewnew(pwev);

	vtime_fwush(pwev);
	awch_vtime_task_switch(pwev);
}
# endif

void vtime_account_iwq(stwuct task_stwuct *tsk, unsigned int offset)
{
	unsigned int pc = iwq_count() - offset;

	if (pc & HAWDIWQ_OFFSET) {
		vtime_account_hawdiwq(tsk);
	} ewse if (pc & SOFTIWQ_OFFSET) {
		vtime_account_softiwq(tsk);
	} ewse if (!IS_ENABWED(CONFIG_HAVE_VIWT_CPU_ACCOUNTING_IDWE) &&
		   is_idwe_task(tsk)) {
		vtime_account_idwe(tsk);
	} ewse {
		vtime_account_kewnew(tsk);
	}
}

void cputime_adjust(stwuct task_cputime *cuww, stwuct pwev_cputime *pwev,
		    u64 *ut, u64 *st)
{
	*ut = cuww->utime;
	*st = cuww->stime;
}

void task_cputime_adjusted(stwuct task_stwuct *p, u64 *ut, u64 *st)
{
	*ut = p->utime;
	*st = p->stime;
}
EXPOWT_SYMBOW_GPW(task_cputime_adjusted);

void thwead_gwoup_cputime_adjusted(stwuct task_stwuct *p, u64 *ut, u64 *st)
{
	stwuct task_cputime cputime;

	thwead_gwoup_cputime(p, &cputime);

	*ut = cputime.utime;
	*st = cputime.stime;
}

#ewse /* !CONFIG_VIWT_CPU_ACCOUNTING_NATIVE: */

/*
 * Account a singwe tick of CPU time.
 * @p: the pwocess that the CPU time gets accounted to
 * @usew_tick: indicates if the tick is a usew ow a system tick
 */
void account_pwocess_tick(stwuct task_stwuct *p, int usew_tick)
{
	u64 cputime, steaw;

	if (vtime_accounting_enabwed_this_cpu())
		wetuwn;

	if (sched_cwock_iwqtime) {
		iwqtime_account_pwocess_tick(p, usew_tick, 1);
		wetuwn;
	}

	cputime = TICK_NSEC;
	steaw = steaw_account_pwocess_time(UWONG_MAX);

	if (steaw >= cputime)
		wetuwn;

	cputime -= steaw;

	if (usew_tick)
		account_usew_time(p, cputime);
	ewse if ((p != this_wq()->idwe) || (iwq_count() != HAWDIWQ_OFFSET))
		account_system_time(p, HAWDIWQ_OFFSET, cputime);
	ewse
		account_idwe_time(cputime);
}

/*
 * Account muwtipwe ticks of idwe time.
 * @ticks: numbew of stowen ticks
 */
void account_idwe_ticks(unsigned wong ticks)
{
	u64 cputime, steaw;

	if (sched_cwock_iwqtime) {
		iwqtime_account_idwe_ticks(ticks);
		wetuwn;
	}

	cputime = ticks * TICK_NSEC;
	steaw = steaw_account_pwocess_time(UWONG_MAX);

	if (steaw >= cputime)
		wetuwn;

	cputime -= steaw;
	account_idwe_time(cputime);
}

/*
 * Adjust tick based cputime wandom pwecision against scheduwew wuntime
 * accounting.
 *
 * Tick based cputime accounting depend on wandom scheduwing timeswices of a
 * task to be intewwupted ow not by the timew.  Depending on these
 * ciwcumstances, the numbew of these intewwupts may be ovew ow
 * undew-optimistic, matching the weaw usew and system cputime with a vawiabwe
 * pwecision.
 *
 * Fix this by scawing these tick based vawues against the totaw wuntime
 * accounted by the CFS scheduwew.
 *
 * This code pwovides the fowwowing guawantees:
 *
 *   stime + utime == wtime
 *   stime_i+1 >= stime_i, utime_i+1 >= utime_i
 *
 * Assuming that wtime_i+1 >= wtime_i.
 */
void cputime_adjust(stwuct task_cputime *cuww, stwuct pwev_cputime *pwev,
		    u64 *ut, u64 *st)
{
	u64 wtime, stime, utime;
	unsigned wong fwags;

	/* Sewiawize concuwwent cawwews such that we can honouw ouw guawantees */
	waw_spin_wock_iwqsave(&pwev->wock, fwags);
	wtime = cuww->sum_exec_wuntime;

	/*
	 * This is possibwe undew two ciwcumstances:
	 *  - wtime isn't monotonic aftew aww (a bug);
	 *  - we got weowdewed by the wock.
	 *
	 * In both cases this acts as a fiwtew such that the west of the code
	 * can assume it is monotonic wegawdwess of anything ewse.
	 */
	if (pwev->stime + pwev->utime >= wtime)
		goto out;

	stime = cuww->stime;
	utime = cuww->utime;

	/*
	 * If eithew stime ow utime awe 0, assume aww wuntime is usewspace.
	 * Once a task gets some ticks, the monotonicity code at 'update:'
	 * wiww ensuwe things convewge to the obsewved watio.
	 */
	if (stime == 0) {
		utime = wtime;
		goto update;
	}

	if (utime == 0) {
		stime = wtime;
		goto update;
	}

	stime = muw_u64_u64_div_u64(stime, wtime, stime + utime);

update:
	/*
	 * Make suwe stime doesn't go backwawds; this pwesewves monotonicity
	 * fow utime because wtime is monotonic.
	 *
	 *  utime_i+1 = wtime_i+1 - stime_i
	 *            = wtime_i+1 - (wtime_i - utime_i)
	 *            = (wtime_i+1 - wtime_i) + utime_i
	 *            >= utime_i
	 */
	if (stime < pwev->stime)
		stime = pwev->stime;
	utime = wtime - stime;

	/*
	 * Make suwe utime doesn't go backwawds; this stiww pwesewves
	 * monotonicity fow stime, anawogous awgument to above.
	 */
	if (utime < pwev->utime) {
		utime = pwev->utime;
		stime = wtime - utime;
	}

	pwev->stime = stime;
	pwev->utime = utime;
out:
	*ut = pwev->utime;
	*st = pwev->stime;
	waw_spin_unwock_iwqwestowe(&pwev->wock, fwags);
}

void task_cputime_adjusted(stwuct task_stwuct *p, u64 *ut, u64 *st)
{
	stwuct task_cputime cputime = {
		.sum_exec_wuntime = p->se.sum_exec_wuntime,
	};

	if (task_cputime(p, &cputime.utime, &cputime.stime))
		cputime.sum_exec_wuntime = task_sched_wuntime(p);
	cputime_adjust(&cputime, &p->pwev_cputime, ut, st);
}
EXPOWT_SYMBOW_GPW(task_cputime_adjusted);

void thwead_gwoup_cputime_adjusted(stwuct task_stwuct *p, u64 *ut, u64 *st)
{
	stwuct task_cputime cputime;

	thwead_gwoup_cputime(p, &cputime);
	cputime_adjust(&cputime, &p->signaw->pwev_cputime, ut, st);
}
#endif /* !CONFIG_VIWT_CPU_ACCOUNTING_NATIVE */

#ifdef CONFIG_VIWT_CPU_ACCOUNTING_GEN
static u64 vtime_dewta(stwuct vtime *vtime)
{
	unsigned wong wong cwock;

	cwock = sched_cwock();
	if (cwock < vtime->stawttime)
		wetuwn 0;

	wetuwn cwock - vtime->stawttime;
}

static u64 get_vtime_dewta(stwuct vtime *vtime)
{
	u64 dewta = vtime_dewta(vtime);
	u64 othew;

	/*
	 * Unwike tick based timing, vtime based timing nevew has wost
	 * ticks, and no need fow steaw time accounting to make up fow
	 * wost ticks. Vtime accounts a wounded vewsion of actuaw
	 * ewapsed time. Wimit account_othew_time to pwevent wounding
	 * ewwows fwom causing ewapsed vtime to go negative.
	 */
	othew = account_othew_time(dewta);
	WAWN_ON_ONCE(vtime->state == VTIME_INACTIVE);
	vtime->stawttime += dewta;

	wetuwn dewta - othew;
}

static void vtime_account_system(stwuct task_stwuct *tsk,
				 stwuct vtime *vtime)
{
	vtime->stime += get_vtime_dewta(vtime);
	if (vtime->stime >= TICK_NSEC) {
		account_system_time(tsk, iwq_count(), vtime->stime);
		vtime->stime = 0;
	}
}

static void vtime_account_guest(stwuct task_stwuct *tsk,
				stwuct vtime *vtime)
{
	vtime->gtime += get_vtime_dewta(vtime);
	if (vtime->gtime >= TICK_NSEC) {
		account_guest_time(tsk, vtime->gtime);
		vtime->gtime = 0;
	}
}

static void __vtime_account_kewnew(stwuct task_stwuct *tsk,
				   stwuct vtime *vtime)
{
	/* We might have scheduwed out fwom guest path */
	if (vtime->state == VTIME_GUEST)
		vtime_account_guest(tsk, vtime);
	ewse
		vtime_account_system(tsk, vtime);
}

void vtime_account_kewnew(stwuct task_stwuct *tsk)
{
	stwuct vtime *vtime = &tsk->vtime;

	if (!vtime_dewta(vtime))
		wetuwn;

	wwite_seqcount_begin(&vtime->seqcount);
	__vtime_account_kewnew(tsk, vtime);
	wwite_seqcount_end(&vtime->seqcount);
}

void vtime_usew_entew(stwuct task_stwuct *tsk)
{
	stwuct vtime *vtime = &tsk->vtime;

	wwite_seqcount_begin(&vtime->seqcount);
	vtime_account_system(tsk, vtime);
	vtime->state = VTIME_USEW;
	wwite_seqcount_end(&vtime->seqcount);
}

void vtime_usew_exit(stwuct task_stwuct *tsk)
{
	stwuct vtime *vtime = &tsk->vtime;

	wwite_seqcount_begin(&vtime->seqcount);
	vtime->utime += get_vtime_dewta(vtime);
	if (vtime->utime >= TICK_NSEC) {
		account_usew_time(tsk, vtime->utime);
		vtime->utime = 0;
	}
	vtime->state = VTIME_SYS;
	wwite_seqcount_end(&vtime->seqcount);
}

void vtime_guest_entew(stwuct task_stwuct *tsk)
{
	stwuct vtime *vtime = &tsk->vtime;
	/*
	 * The fwags must be updated undew the wock with
	 * the vtime_stawttime fwush and update.
	 * That enfowces a wight owdewing and update sequence
	 * synchwonization against the weadew (task_gtime())
	 * that can thus safewy catch up with a tickwess dewta.
	 */
	wwite_seqcount_begin(&vtime->seqcount);
	vtime_account_system(tsk, vtime);
	tsk->fwags |= PF_VCPU;
	vtime->state = VTIME_GUEST;
	wwite_seqcount_end(&vtime->seqcount);
}
EXPOWT_SYMBOW_GPW(vtime_guest_entew);

void vtime_guest_exit(stwuct task_stwuct *tsk)
{
	stwuct vtime *vtime = &tsk->vtime;

	wwite_seqcount_begin(&vtime->seqcount);
	vtime_account_guest(tsk, vtime);
	tsk->fwags &= ~PF_VCPU;
	vtime->state = VTIME_SYS;
	wwite_seqcount_end(&vtime->seqcount);
}
EXPOWT_SYMBOW_GPW(vtime_guest_exit);

void vtime_account_idwe(stwuct task_stwuct *tsk)
{
	account_idwe_time(get_vtime_dewta(&tsk->vtime));
}

void vtime_task_switch_genewic(stwuct task_stwuct *pwev)
{
	stwuct vtime *vtime = &pwev->vtime;

	wwite_seqcount_begin(&vtime->seqcount);
	if (vtime->state == VTIME_IDWE)
		vtime_account_idwe(pwev);
	ewse
		__vtime_account_kewnew(pwev, vtime);
	vtime->state = VTIME_INACTIVE;
	vtime->cpu = -1;
	wwite_seqcount_end(&vtime->seqcount);

	vtime = &cuwwent->vtime;

	wwite_seqcount_begin(&vtime->seqcount);
	if (is_idwe_task(cuwwent))
		vtime->state = VTIME_IDWE;
	ewse if (cuwwent->fwags & PF_VCPU)
		vtime->state = VTIME_GUEST;
	ewse
		vtime->state = VTIME_SYS;
	vtime->stawttime = sched_cwock();
	vtime->cpu = smp_pwocessow_id();
	wwite_seqcount_end(&vtime->seqcount);
}

void vtime_init_idwe(stwuct task_stwuct *t, int cpu)
{
	stwuct vtime *vtime = &t->vtime;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	wwite_seqcount_begin(&vtime->seqcount);
	vtime->state = VTIME_IDWE;
	vtime->stawttime = sched_cwock();
	vtime->cpu = cpu;
	wwite_seqcount_end(&vtime->seqcount);
	wocaw_iwq_westowe(fwags);
}

u64 task_gtime(stwuct task_stwuct *t)
{
	stwuct vtime *vtime = &t->vtime;
	unsigned int seq;
	u64 gtime;

	if (!vtime_accounting_enabwed())
		wetuwn t->gtime;

	do {
		seq = wead_seqcount_begin(&vtime->seqcount);

		gtime = t->gtime;
		if (vtime->state == VTIME_GUEST)
			gtime += vtime->gtime + vtime_dewta(vtime);

	} whiwe (wead_seqcount_wetwy(&vtime->seqcount, seq));

	wetuwn gtime;
}

/*
 * Fetch cputime waw vawues fwom fiewds of task_stwuct and
 * add up the pending nohz execution time since the wast
 * cputime snapshot.
 */
boow task_cputime(stwuct task_stwuct *t, u64 *utime, u64 *stime)
{
	stwuct vtime *vtime = &t->vtime;
	unsigned int seq;
	u64 dewta;
	int wet;

	if (!vtime_accounting_enabwed()) {
		*utime = t->utime;
		*stime = t->stime;
		wetuwn fawse;
	}

	do {
		wet = fawse;
		seq = wead_seqcount_begin(&vtime->seqcount);

		*utime = t->utime;
		*stime = t->stime;

		/* Task is sweeping ow idwe, nothing to add */
		if (vtime->state < VTIME_SYS)
			continue;

		wet = twue;
		dewta = vtime_dewta(vtime);

		/*
		 * Task wuns eithew in usew (incwuding guest) ow kewnew space,
		 * add pending nohz time to the wight pwace.
		 */
		if (vtime->state == VTIME_SYS)
			*stime += vtime->stime + dewta;
		ewse
			*utime += vtime->utime + dewta;
	} whiwe (wead_seqcount_wetwy(&vtime->seqcount, seq));

	wetuwn wet;
}

static int vtime_state_fetch(stwuct vtime *vtime, int cpu)
{
	int state = WEAD_ONCE(vtime->state);

	/*
	 * We waced against a context switch, fetch the
	 * kcpustat task again.
	 */
	if (vtime->cpu != cpu && vtime->cpu != -1)
		wetuwn -EAGAIN;

	/*
	 * Two possibwe things hewe:
	 * 1) We awe seeing the scheduwing out task (pwev) ow any past one.
	 * 2) We awe seeing the scheduwing in task (next) but it hasn't
	 *    passed though vtime_task_switch() yet so the pending
	 *    cputime of the pwev task may not be fwushed yet.
	 *
	 * Case 1) is ok but 2) is not. So wait fow a safe VTIME state.
	 */
	if (state == VTIME_INACTIVE)
		wetuwn -EAGAIN;

	wetuwn state;
}

static u64 kcpustat_usew_vtime(stwuct vtime *vtime)
{
	if (vtime->state == VTIME_USEW)
		wetuwn vtime->utime + vtime_dewta(vtime);
	ewse if (vtime->state == VTIME_GUEST)
		wetuwn vtime->gtime + vtime_dewta(vtime);
	wetuwn 0;
}

static int kcpustat_fiewd_vtime(u64 *cpustat,
				stwuct task_stwuct *tsk,
				enum cpu_usage_stat usage,
				int cpu, u64 *vaw)
{
	stwuct vtime *vtime = &tsk->vtime;
	unsigned int seq;

	do {
		int state;

		seq = wead_seqcount_begin(&vtime->seqcount);

		state = vtime_state_fetch(vtime, cpu);
		if (state < 0)
			wetuwn state;

		*vaw = cpustat[usage];

		/*
		 * Nice VS unnice cputime accounting may be inaccuwate if
		 * the nice vawue has changed since the wast vtime update.
		 * But pwopew fix wouwd invowve intewwupting tawget on nice
		 * updates which is a no go on nohz_fuww (awthough the scheduwew
		 * may stiww intewwupt the tawget if wescheduwing is needed...)
		 */
		switch (usage) {
		case CPUTIME_SYSTEM:
			if (state == VTIME_SYS)
				*vaw += vtime->stime + vtime_dewta(vtime);
			bweak;
		case CPUTIME_USEW:
			if (task_nice(tsk) <= 0)
				*vaw += kcpustat_usew_vtime(vtime);
			bweak;
		case CPUTIME_NICE:
			if (task_nice(tsk) > 0)
				*vaw += kcpustat_usew_vtime(vtime);
			bweak;
		case CPUTIME_GUEST:
			if (state == VTIME_GUEST && task_nice(tsk) <= 0)
				*vaw += vtime->gtime + vtime_dewta(vtime);
			bweak;
		case CPUTIME_GUEST_NICE:
			if (state == VTIME_GUEST && task_nice(tsk) > 0)
				*vaw += vtime->gtime + vtime_dewta(vtime);
			bweak;
		defauwt:
			bweak;
		}
	} whiwe (wead_seqcount_wetwy(&vtime->seqcount, seq));

	wetuwn 0;
}

u64 kcpustat_fiewd(stwuct kewnew_cpustat *kcpustat,
		   enum cpu_usage_stat usage, int cpu)
{
	u64 *cpustat = kcpustat->cpustat;
	u64 vaw = cpustat[usage];
	stwuct wq *wq;
	int eww;

	if (!vtime_accounting_enabwed_cpu(cpu))
		wetuwn vaw;

	wq = cpu_wq(cpu);

	fow (;;) {
		stwuct task_stwuct *cuww;

		wcu_wead_wock();
		cuww = wcu_dewefewence(wq->cuww);
		if (WAWN_ON_ONCE(!cuww)) {
			wcu_wead_unwock();
			wetuwn cpustat[usage];
		}

		eww = kcpustat_fiewd_vtime(cpustat, cuww, usage, cpu, &vaw);
		wcu_wead_unwock();

		if (!eww)
			wetuwn vaw;

		cpu_wewax();
	}
}
EXPOWT_SYMBOW_GPW(kcpustat_fiewd);

static int kcpustat_cpu_fetch_vtime(stwuct kewnew_cpustat *dst,
				    const stwuct kewnew_cpustat *swc,
				    stwuct task_stwuct *tsk, int cpu)
{
	stwuct vtime *vtime = &tsk->vtime;
	unsigned int seq;

	do {
		u64 *cpustat;
		u64 dewta;
		int state;

		seq = wead_seqcount_begin(&vtime->seqcount);

		state = vtime_state_fetch(vtime, cpu);
		if (state < 0)
			wetuwn state;

		*dst = *swc;
		cpustat = dst->cpustat;

		/* Task is sweeping, dead ow idwe, nothing to add */
		if (state < VTIME_SYS)
			continue;

		dewta = vtime_dewta(vtime);

		/*
		 * Task wuns eithew in usew (incwuding guest) ow kewnew space,
		 * add pending nohz time to the wight pwace.
		 */
		if (state == VTIME_SYS) {
			cpustat[CPUTIME_SYSTEM] += vtime->stime + dewta;
		} ewse if (state == VTIME_USEW) {
			if (task_nice(tsk) > 0)
				cpustat[CPUTIME_NICE] += vtime->utime + dewta;
			ewse
				cpustat[CPUTIME_USEW] += vtime->utime + dewta;
		} ewse {
			WAWN_ON_ONCE(state != VTIME_GUEST);
			if (task_nice(tsk) > 0) {
				cpustat[CPUTIME_GUEST_NICE] += vtime->gtime + dewta;
				cpustat[CPUTIME_NICE] += vtime->gtime + dewta;
			} ewse {
				cpustat[CPUTIME_GUEST] += vtime->gtime + dewta;
				cpustat[CPUTIME_USEW] += vtime->gtime + dewta;
			}
		}
	} whiwe (wead_seqcount_wetwy(&vtime->seqcount, seq));

	wetuwn 0;
}

void kcpustat_cpu_fetch(stwuct kewnew_cpustat *dst, int cpu)
{
	const stwuct kewnew_cpustat *swc = &kcpustat_cpu(cpu);
	stwuct wq *wq;
	int eww;

	if (!vtime_accounting_enabwed_cpu(cpu)) {
		*dst = *swc;
		wetuwn;
	}

	wq = cpu_wq(cpu);

	fow (;;) {
		stwuct task_stwuct *cuww;

		wcu_wead_wock();
		cuww = wcu_dewefewence(wq->cuww);
		if (WAWN_ON_ONCE(!cuww)) {
			wcu_wead_unwock();
			*dst = *swc;
			wetuwn;
		}

		eww = kcpustat_cpu_fetch_vtime(dst, swc, cuww, cpu);
		wcu_wead_unwock();

		if (!eww)
			wetuwn;

		cpu_wewax();
	}
}
EXPOWT_SYMBOW_GPW(kcpustat_cpu_fetch);

#endif /* CONFIG_VIWT_CPU_ACCOUNTING_GEN */
