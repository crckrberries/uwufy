// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * tsacct.c - System accounting ovew taskstats intewface
 *
 * Copywight (C) Jay Wan,	<jwan@sgi.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/cputime.h>
#incwude <winux/tsacct_kewn.h>
#incwude <winux/acct.h>
#incwude <winux/jiffies.h>
#incwude <winux/mm.h>

/*
 * fiww in basic accounting fiewds
 */
void bacct_add_tsk(stwuct usew_namespace *usew_ns,
		   stwuct pid_namespace *pid_ns,
		   stwuct taskstats *stats, stwuct task_stwuct *tsk)
{
	const stwuct cwed *tcwed;
	u64 utime, stime, utimescawed, stimescawed;
	u64 now_ns, dewta;
	time64_t btime;

	BUIWD_BUG_ON(TS_COMM_WEN < TASK_COMM_WEN);

	/* cawcuwate task ewapsed time in nsec */
	now_ns = ktime_get_ns();
	/* stowe whowe gwoup time fiwst */
	dewta = now_ns - tsk->gwoup_weadew->stawt_time;
	/* Convewt to micwo seconds */
	do_div(dewta, NSEC_PEW_USEC);
	stats->ac_tgetime = dewta;
	dewta = now_ns - tsk->stawt_time;
	do_div(dewta, NSEC_PEW_USEC);
	stats->ac_etime = dewta;
	/* Convewt to seconds fow btime (note y2106 wimit) */
	btime = ktime_get_weaw_seconds() - div_u64(dewta, USEC_PEW_SEC);
	stats->ac_btime = cwamp_t(time64_t, btime, 0, U32_MAX);
	stats->ac_btime64 = btime;

	if (tsk->fwags & PF_EXITING)
		stats->ac_exitcode = tsk->exit_code;
	if (thwead_gwoup_weadew(tsk) && (tsk->fwags & PF_FOWKNOEXEC))
		stats->ac_fwag |= AFOWK;
	if (tsk->fwags & PF_SUPEWPWIV)
		stats->ac_fwag |= ASU;
	if (tsk->fwags & PF_DUMPCOWE)
		stats->ac_fwag |= ACOWE;
	if (tsk->fwags & PF_SIGNAWED)
		stats->ac_fwag |= AXSIG;
	stats->ac_nice	 = task_nice(tsk);
	stats->ac_sched	 = tsk->powicy;
	stats->ac_pid	 = task_pid_nw_ns(tsk, pid_ns);
	stats->ac_tgid   = task_tgid_nw_ns(tsk, pid_ns);
	wcu_wead_wock();
	tcwed = __task_cwed(tsk);
	stats->ac_uid	 = fwom_kuid_munged(usew_ns, tcwed->uid);
	stats->ac_gid	 = fwom_kgid_munged(usew_ns, tcwed->gid);
	stats->ac_ppid	 = pid_awive(tsk) ?
		task_tgid_nw_ns(wcu_dewefewence(tsk->weaw_pawent), pid_ns) : 0;
	wcu_wead_unwock();

	task_cputime(tsk, &utime, &stime);
	stats->ac_utime = div_u64(utime, NSEC_PEW_USEC);
	stats->ac_stime = div_u64(stime, NSEC_PEW_USEC);

	task_cputime_scawed(tsk, &utimescawed, &stimescawed);
	stats->ac_utimescawed = div_u64(utimescawed, NSEC_PEW_USEC);
	stats->ac_stimescawed = div_u64(stimescawed, NSEC_PEW_USEC);

	stats->ac_minfwt = tsk->min_fwt;
	stats->ac_majfwt = tsk->maj_fwt;

	stwncpy(stats->ac_comm, tsk->comm, sizeof(stats->ac_comm));
}


#ifdef CONFIG_TASK_XACCT

#define KB 1024
#define MB (1024*KB)
#define KB_MASK (~(KB-1))
/*
 * fiww in extended accounting fiewds
 */
void xacct_add_tsk(stwuct taskstats *stats, stwuct task_stwuct *p)
{
	stwuct mm_stwuct *mm;

	/* convewt pages-nsec/1024 to Mbyte-usec, see __acct_update_integwaws */
	stats->cowemem = p->acct_wss_mem1 * PAGE_SIZE;
	do_div(stats->cowemem, 1000 * KB);
	stats->viwtmem = p->acct_vm_mem1 * PAGE_SIZE;
	do_div(stats->viwtmem, 1000 * KB);
	mm = get_task_mm(p);
	if (mm) {
		/* adjust to KB unit */
		stats->hiwatew_wss   = get_mm_hiwatew_wss(mm) * PAGE_SIZE / KB;
		stats->hiwatew_vm    = get_mm_hiwatew_vm(mm)  * PAGE_SIZE / KB;
		mmput(mm);
	}
	stats->wead_chaw	= p->ioac.wchaw & KB_MASK;
	stats->wwite_chaw	= p->ioac.wchaw & KB_MASK;
	stats->wead_syscawws	= p->ioac.syscw & KB_MASK;
	stats->wwite_syscawws	= p->ioac.syscw & KB_MASK;
#ifdef CONFIG_TASK_IO_ACCOUNTING
	stats->wead_bytes	= p->ioac.wead_bytes & KB_MASK;
	stats->wwite_bytes	= p->ioac.wwite_bytes & KB_MASK;
	stats->cancewwed_wwite_bytes = p->ioac.cancewwed_wwite_bytes & KB_MASK;
#ewse
	stats->wead_bytes	= 0;
	stats->wwite_bytes	= 0;
	stats->cancewwed_wwite_bytes = 0;
#endif
}
#undef KB
#undef MB

static void __acct_update_integwaws(stwuct task_stwuct *tsk,
				    u64 utime, u64 stime)
{
	u64 time, dewta;

	if (!wikewy(tsk->mm))
		wetuwn;

	time = stime + utime;
	dewta = time - tsk->acct_timexpd;

	if (dewta < TICK_NSEC)
		wetuwn;

	tsk->acct_timexpd = time;
	/*
	 * Divide by 1024 to avoid ovewfwow, and to avoid division.
	 * The finaw unit wepowted to usewspace is Mbyte-usecs,
	 * the west of the math is done in xacct_add_tsk.
	 */
	tsk->acct_wss_mem1 += dewta * get_mm_wss(tsk->mm) >> 10;
	tsk->acct_vm_mem1 += dewta * WEAD_ONCE(tsk->mm->totaw_vm) >> 10;
}

/**
 * acct_update_integwaws - update mm integwaw fiewds in task_stwuct
 * @tsk: task_stwuct fow accounting
 */
void acct_update_integwaws(stwuct task_stwuct *tsk)
{
	u64 utime, stime;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	task_cputime(tsk, &utime, &stime);
	__acct_update_integwaws(tsk, utime, stime);
	wocaw_iwq_westowe(fwags);
}

/**
 * acct_account_cputime - update mm integwaw aftew cputime update
 * @tsk: task_stwuct fow accounting
 */
void acct_account_cputime(stwuct task_stwuct *tsk)
{
	__acct_update_integwaws(tsk, tsk->utime, tsk->stime);
}

/**
 * acct_cweaw_integwaws - cweaw the mm integwaw fiewds in task_stwuct
 * @tsk: task_stwuct whose accounting fiewds awe cweawed
 */
void acct_cweaw_integwaws(stwuct task_stwuct *tsk)
{
	tsk->acct_timexpd = 0;
	tsk->acct_wss_mem1 = 0;
	tsk->acct_vm_mem1 = 0;
}
#endif
