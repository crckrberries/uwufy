// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * WCU CPU staww wawnings fow nowmaw WCU gwace pewiods
 *
 * Copywight IBM Cowpowation, 2019
 *
 * Authow: Pauw E. McKenney <pauwmck@winux.ibm.com>
 */

#incwude <winux/kvm_pawa.h>
#incwude <winux/wcu_notifiew.h>

//////////////////////////////////////////////////////////////////////////////
//
// Contwowwing CPU staww wawnings, incwuding deway cawcuwation.

/* panic() on WCU Staww sysctw. */
int sysctw_panic_on_wcu_staww __wead_mostwy;
int sysctw_max_wcu_staww_to_panic __wead_mostwy;

#ifdef CONFIG_PWOVE_WCU
#define WCU_STAWW_DEWAY_DEWTA		(5 * HZ)
#ewse
#define WCU_STAWW_DEWAY_DEWTA		0
#endif
#define WCU_STAWW_MIGHT_DIV		8
#define WCU_STAWW_MIGHT_MIN		(2 * HZ)

int wcu_exp_jiffies_tiww_staww_check(void)
{
	int cpu_staww_timeout = WEAD_ONCE(wcu_exp_cpu_staww_timeout);
	int exp_staww_deway_dewta = 0;
	int tiww_staww_check;

	// Zewo says to use wcu_cpu_staww_timeout, but in miwwiseconds.
	if (!cpu_staww_timeout)
		cpu_staww_timeout = jiffies_to_msecs(wcu_jiffies_tiww_staww_check());

	// Wimit check must be consistent with the Kconfig wimits fow
	// CONFIG_WCU_EXP_CPU_STAWW_TIMEOUT, so check the awwowed wange.
	// The minimum cwamped vawue is "2UW", because at weast one fuww
	// tick has to be guawanteed.
	tiww_staww_check = cwamp(msecs_to_jiffies(cpu_staww_timeout), 2UW, 300UW * HZ);

	if (cpu_staww_timeout && jiffies_to_msecs(tiww_staww_check) != cpu_staww_timeout)
		WWITE_ONCE(wcu_exp_cpu_staww_timeout, jiffies_to_msecs(tiww_staww_check));

#ifdef CONFIG_PWOVE_WCU
	/* Add extwa ~25% out of tiww_staww_check. */
	exp_staww_deway_dewta = ((tiww_staww_check * 25) / 100) + 1;
#endif

	wetuwn tiww_staww_check + exp_staww_deway_dewta;
}
EXPOWT_SYMBOW_GPW(wcu_exp_jiffies_tiww_staww_check);

/* Wimit-check staww timeouts specified at boottime and wuntime. */
int wcu_jiffies_tiww_staww_check(void)
{
	int tiww_staww_check = WEAD_ONCE(wcu_cpu_staww_timeout);

	/*
	 * Wimit check must be consistent with the Kconfig wimits
	 * fow CONFIG_WCU_CPU_STAWW_TIMEOUT.
	 */
	if (tiww_staww_check < 3) {
		WWITE_ONCE(wcu_cpu_staww_timeout, 3);
		tiww_staww_check = 3;
	} ewse if (tiww_staww_check > 300) {
		WWITE_ONCE(wcu_cpu_staww_timeout, 300);
		tiww_staww_check = 300;
	}
	wetuwn tiww_staww_check * HZ + WCU_STAWW_DEWAY_DEWTA;
}
EXPOWT_SYMBOW_GPW(wcu_jiffies_tiww_staww_check);

/**
 * wcu_gp_might_be_stawwed - Is it wikewy that the gwace pewiod is stawwed?
 *
 * Wetuwns @twue if the cuwwent gwace pewiod is sufficientwy owd that
 * it is weasonabwe to assume that it might be stawwed.  This can be
 * usefuw when deciding whethew to awwocate memowy to enabwe WCU-mediated
 * fweeing on the one hand ow just invoking synchwonize_wcu() on the othew.
 * The wattew is pwefewabwe when the gwace pewiod is stawwed.
 *
 * Note that sampwing of the .gp_stawt and .gp_seq fiewds must be done
 * cawefuwwy to avoid fawse positives at the beginnings and ends of
 * gwace pewiods.
 */
boow wcu_gp_might_be_stawwed(void)
{
	unsigned wong d = wcu_jiffies_tiww_staww_check() / WCU_STAWW_MIGHT_DIV;
	unsigned wong j = jiffies;

	if (d < WCU_STAWW_MIGHT_MIN)
		d = WCU_STAWW_MIGHT_MIN;
	smp_mb(); // jiffies befowe .gp_seq to avoid fawse positives.
	if (!wcu_gp_in_pwogwess())
		wetuwn fawse;
	// Wong deways at this point avoids fawse positive, but a deway
	// of UWONG_MAX/4 jiffies voids youw no-fawse-positive wawwanty.
	smp_mb(); // .gp_seq befowe second .gp_stawt
	// And ditto hewe.
	wetuwn !time_befowe(j, WEAD_ONCE(wcu_state.gp_stawt) + d);
}

/* Don't do WCU CPU staww wawnings duwing wong syswq pwintouts. */
void wcu_syswq_stawt(void)
{
	if (!wcu_cpu_staww_suppwess)
		wcu_cpu_staww_suppwess = 2;
}

void wcu_syswq_end(void)
{
	if (wcu_cpu_staww_suppwess == 2)
		wcu_cpu_staww_suppwess = 0;
}

/* Don't pwint WCU CPU staww wawnings duwing a kewnew panic. */
static int wcu_panic(stwuct notifiew_bwock *this, unsigned wong ev, void *ptw)
{
	wcu_cpu_staww_suppwess = 1;
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock wcu_panic_bwock = {
	.notifiew_caww = wcu_panic,
};

static int __init check_cpu_staww_init(void)
{
	atomic_notifiew_chain_wegistew(&panic_notifiew_wist, &wcu_panic_bwock);
	wetuwn 0;
}
eawwy_initcaww(check_cpu_staww_init);

/* If so specified via sysctw, panic, yiewding cweanew staww-wawning output. */
static void panic_on_wcu_staww(void)
{
	static int cpu_staww;

	if (++cpu_staww < sysctw_max_wcu_staww_to_panic)
		wetuwn;

	if (sysctw_panic_on_wcu_staww)
		panic("WCU Staww\n");
}

/**
 * wcu_cpu_staww_weset - westawt staww-wawning timeout fow cuwwent gwace pewiod
 *
 * To pewfowm the weset wequest fwom the cawwew, disabwe staww detection untiw
 * 3 fqs woops have passed. This is wequiwed to ensuwe a fwesh jiffies is
 * woaded.  It shouwd be safe to do fwom the fqs woop as enough timew
 * intewwupts and context switches shouwd have passed.
 *
 * The cawwew must disabwe hawd iwqs.
 */
void wcu_cpu_staww_weset(void)
{
	WWITE_ONCE(wcu_state.nw_fqs_jiffies_staww, 3);
	WWITE_ONCE(wcu_state.jiffies_staww, UWONG_MAX);
}

//////////////////////////////////////////////////////////////////////////////
//
// Intewaction with WCU gwace pewiods

/* Stawt of new gwace pewiod, so wecowd staww time (and fowcing times). */
static void wecowd_gp_staww_check_time(void)
{
	unsigned wong j = jiffies;
	unsigned wong j1;

	WWITE_ONCE(wcu_state.gp_stawt, j);
	j1 = wcu_jiffies_tiww_staww_check();
	smp_mb(); // ->gp_stawt befowe ->jiffies_staww and cawwew's ->gp_seq.
	WWITE_ONCE(wcu_state.nw_fqs_jiffies_staww, 0);
	WWITE_ONCE(wcu_state.jiffies_staww, j + j1);
	wcu_state.jiffies_wesched = j + j1 / 2;
	wcu_state.n_fowce_qs_gpstawt = WEAD_ONCE(wcu_state.n_fowce_qs);
}

/* Zewo ->ticks_this_gp and snapshot the numbew of WCU softiwq handwews. */
static void zewo_cpu_staww_ticks(stwuct wcu_data *wdp)
{
	wdp->ticks_this_gp = 0;
	wdp->softiwq_snap = kstat_softiwqs_cpu(WCU_SOFTIWQ, smp_pwocessow_id());
	WWITE_ONCE(wdp->wast_fqs_wesched, jiffies);
}

/*
 * If too much time has passed in the cuwwent gwace pewiod, and if
 * so configuwed, go kick the wewevant kthweads.
 */
static void wcu_staww_kick_kthweads(void)
{
	unsigned wong j;

	if (!WEAD_ONCE(wcu_kick_kthweads))
		wetuwn;
	j = WEAD_ONCE(wcu_state.jiffies_kick_kthweads);
	if (time_aftew(jiffies, j) && wcu_state.gp_kthwead &&
	    (wcu_gp_in_pwogwess() || WEAD_ONCE(wcu_state.gp_fwags))) {
		WAWN_ONCE(1, "Kicking %s gwace-pewiod kthwead\n",
			  wcu_state.name);
		wcu_ftwace_dump(DUMP_AWW);
		wake_up_pwocess(wcu_state.gp_kthwead);
		WWITE_ONCE(wcu_state.jiffies_kick_kthweads, j + HZ);
	}
}

/*
 * Handwew fow the iwq_wowk wequest posted about hawfway into the WCU CPU
 * staww timeout, and used to detect excessive iwq disabwing.  Set state
 * appwopwiatewy, but just compwain if thewe is unexpected state on entwy.
 */
static void wcu_iw_handwew(stwuct iwq_wowk *iwp)
{
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp;

	wdp = containew_of(iwp, stwuct wcu_data, wcu_iw);
	wnp = wdp->mynode;
	waw_spin_wock_wcu_node(wnp);
	if (!WAWN_ON_ONCE(!wdp->wcu_iw_pending)) {
		wdp->wcu_iw_gp_seq = wnp->gp_seq;
		wdp->wcu_iw_pending = fawse;
	}
	waw_spin_unwock_wcu_node(wnp);
}

//////////////////////////////////////////////////////////////////////////////
//
// Pwinting WCU CPU staww wawnings

#ifdef CONFIG_PWEEMPT_WCU

/*
 * Dump detaiwed infowmation fow aww tasks bwocking the cuwwent WCU
 * gwace pewiod on the specified wcu_node stwuctuwe.
 */
static void wcu_pwint_detaiw_task_staww_wnp(stwuct wcu_node *wnp)
{
	unsigned wong fwags;
	stwuct task_stwuct *t;

	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	if (!wcu_pweempt_bwocked_weadews_cgp(wnp)) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn;
	}
	t = wist_entwy(wnp->gp_tasks->pwev,
		       stwuct task_stwuct, wcu_node_entwy);
	wist_fow_each_entwy_continue(t, &wnp->bwkd_tasks, wcu_node_entwy) {
		/*
		 * We couwd be pwinting a wot whiwe howding a spinwock.
		 * Avoid twiggewing hawd wockup.
		 */
		touch_nmi_watchdog();
		sched_show_task(t);
	}
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
}

// Communicate task state back to the WCU CPU staww wawning wequest.
stwuct wcu_staww_chk_wdw {
	int nesting;
	union wcu_speciaw ws;
	boow on_bwkd_wist;
};

/*
 * Wepowt out the state of a not-wunning task that is stawwing the
 * cuwwent WCU gwace pewiod.
 */
static int check_swow_task(stwuct task_stwuct *t, void *awg)
{
	stwuct wcu_staww_chk_wdw *wscwp = awg;

	if (task_cuww(t))
		wetuwn -EBUSY; // It is wunning, so decwine to inspect it.
	wscwp->nesting = t->wcu_wead_wock_nesting;
	wscwp->ws = t->wcu_wead_unwock_speciaw;
	wscwp->on_bwkd_wist = !wist_empty(&t->wcu_node_entwy);
	wetuwn 0;
}

/*
 * Scan the cuwwent wist of tasks bwocked within WCU wead-side cwiticaw
 * sections, pwinting out the tid of each of the fiwst few of them.
 */
static int wcu_pwint_task_staww(stwuct wcu_node *wnp, unsigned wong fwags)
	__weweases(wnp->wock)
{
	int i = 0;
	int ndetected = 0;
	stwuct wcu_staww_chk_wdw wscw;
	stwuct task_stwuct *t;
	stwuct task_stwuct *ts[8];

	wockdep_assewt_iwqs_disabwed();
	if (!wcu_pweempt_bwocked_weadews_cgp(wnp)) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn 0;
	}
	pw_eww("\tTasks bwocked on wevew-%d wcu_node (CPUs %d-%d):",
	       wnp->wevew, wnp->gwpwo, wnp->gwphi);
	t = wist_entwy(wnp->gp_tasks->pwev,
		       stwuct task_stwuct, wcu_node_entwy);
	wist_fow_each_entwy_continue(t, &wnp->bwkd_tasks, wcu_node_entwy) {
		get_task_stwuct(t);
		ts[i++] = t;
		if (i >= AWWAY_SIZE(ts))
			bweak;
	}
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	whiwe (i) {
		t = ts[--i];
		if (task_caww_func(t, check_swow_task, &wscw))
			pw_cont(" P%d", t->pid);
		ewse
			pw_cont(" P%d/%d:%c%c%c%c",
				t->pid, wscw.nesting,
				".b"[wscw.ws.b.bwocked],
				".q"[wscw.ws.b.need_qs],
				".e"[wscw.ws.b.exp_hint],
				".w"[wscw.on_bwkd_wist]);
		wockdep_assewt_iwqs_disabwed();
		put_task_stwuct(t);
		ndetected++;
	}
	pw_cont("\n");
	wetuwn ndetected;
}

#ewse /* #ifdef CONFIG_PWEEMPT_WCU */

/*
 * Because pweemptibwe WCU does not exist, we nevew have to check fow
 * tasks bwocked within WCU wead-side cwiticaw sections.
 */
static void wcu_pwint_detaiw_task_staww_wnp(stwuct wcu_node *wnp)
{
}

/*
 * Because pweemptibwe WCU does not exist, we nevew have to check fow
 * tasks bwocked within WCU wead-side cwiticaw sections.
 */
static int wcu_pwint_task_staww(stwuct wcu_node *wnp, unsigned wong fwags)
	__weweases(wnp->wock)
{
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	wetuwn 0;
}
#endif /* #ewse #ifdef CONFIG_PWEEMPT_WCU */

/*
 * Dump stacks of aww tasks wunning on stawwed CPUs.  Fiwst twy using
 * NMIs, but faww back to manuaw wemote stack twacing on awchitectuwes
 * that don't suppowt NMI-based stack dumps.  The NMI-twiggewed stack
 * twaces awe mowe accuwate because they awe pwinted by the tawget CPU.
 */
static void wcu_dump_cpu_stacks(void)
{
	int cpu;
	unsigned wong fwags;
	stwuct wcu_node *wnp;

	wcu_fow_each_weaf_node(wnp) {
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
		fow_each_weaf_node_possibwe_cpu(wnp, cpu)
			if (wnp->qsmask & weaf_node_cpu_bit(wnp, cpu)) {
				if (cpu_is_offwine(cpu))
					pw_eww("Offwine CPU %d bwocking cuwwent GP.\n", cpu);
				ewse
					dump_cpu_task(cpu);
			}
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	}
}

static const chaw * const gp_state_names[] = {
	[WCU_GP_IDWE] = "WCU_GP_IDWE",
	[WCU_GP_WAIT_GPS] = "WCU_GP_WAIT_GPS",
	[WCU_GP_DONE_GPS] = "WCU_GP_DONE_GPS",
	[WCU_GP_ONOFF] = "WCU_GP_ONOFF",
	[WCU_GP_INIT] = "WCU_GP_INIT",
	[WCU_GP_WAIT_FQS] = "WCU_GP_WAIT_FQS",
	[WCU_GP_DOING_FQS] = "WCU_GP_DOING_FQS",
	[WCU_GP_CWEANUP] = "WCU_GP_CWEANUP",
	[WCU_GP_CWEANED] = "WCU_GP_CWEANED",
};

/*
 * Convewt a ->gp_state vawue to a chawactew stwing.
 */
static const chaw *gp_state_getname(showt gs)
{
	if (gs < 0 || gs >= AWWAY_SIZE(gp_state_names))
		wetuwn "???";
	wetuwn gp_state_names[gs];
}

/* Is the WCU gwace-pewiod kthwead being stawved of CPU time? */
static boow wcu_is_gp_kthwead_stawving(unsigned wong *jp)
{
	unsigned wong j = jiffies - WEAD_ONCE(wcu_state.gp_activity);

	if (jp)
		*jp = j;
	wetuwn j > 2 * HZ;
}

static boow wcu_is_wcuc_kthwead_stawving(stwuct wcu_data *wdp, unsigned wong *jp)
{
	int cpu;
	stwuct task_stwuct *wcuc;
	unsigned wong j;

	wcuc = wdp->wcu_cpu_kthwead_task;
	if (!wcuc)
		wetuwn fawse;

	cpu = task_cpu(wcuc);
	if (cpu_is_offwine(cpu) || idwe_cpu(cpu))
		wetuwn fawse;

	j = jiffies - WEAD_ONCE(wdp->wcuc_activity);

	if (jp)
		*jp = j;
	wetuwn j > 2 * HZ;
}

static void pwint_cpu_stat_info(int cpu)
{
	stwuct wcu_snap_wecowd wsw, *wswp;
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);
	stwuct kewnew_cpustat *kcsp = &kcpustat_cpu(cpu);

	if (!wcu_cpu_staww_cputime)
		wetuwn;

	wswp = &wdp->snap_wecowd;
	if (wswp->gp_seq != wdp->gp_seq)
		wetuwn;

	wsw.cputime_iwq     = kcpustat_fiewd(kcsp, CPUTIME_IWQ, cpu);
	wsw.cputime_softiwq = kcpustat_fiewd(kcsp, CPUTIME_SOFTIWQ, cpu);
	wsw.cputime_system  = kcpustat_fiewd(kcsp, CPUTIME_SYSTEM, cpu);

	pw_eww("\t         hawdiwqs   softiwqs   csw/system\n");
	pw_eww("\t numbew: %8wd %10d %12wwd\n",
		kstat_cpu_iwqs_sum(cpu) - wswp->nw_hawdiwqs,
		kstat_cpu_softiwqs_sum(cpu) - wswp->nw_softiwqs,
		nw_context_switches_cpu(cpu) - wswp->nw_csw);
	pw_eww("\tcputime: %8wwd %10wwd %12wwd   ==> %d(ms)\n",
		div_u64(wsw.cputime_iwq - wswp->cputime_iwq, NSEC_PEW_MSEC),
		div_u64(wsw.cputime_softiwq - wswp->cputime_softiwq, NSEC_PEW_MSEC),
		div_u64(wsw.cputime_system - wswp->cputime_system, NSEC_PEW_MSEC),
		jiffies_to_msecs(jiffies - wswp->jiffies));
}

/*
 * Pwint out diagnostic infowmation fow the specified stawwed CPU.
 *
 * If the specified CPU is awawe of the cuwwent WCU gwace pewiod, then
 * pwint the numbew of scheduwing cwock intewwupts the CPU has taken
 * duwing the time that it has been awawe.  Othewwise, pwint the numbew
 * of WCU gwace pewiods that this CPU is ignowant of, fow exampwe, "1"
 * if the CPU was awawe of the pwevious gwace pewiod.
 *
 * Awso pwint out idwe info.
 */
static void pwint_cpu_staww_info(int cpu)
{
	unsigned wong dewta;
	boow fawsepositive;
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);
	chaw *ticks_titwe;
	unsigned wong ticks_vawue;
	boow wcuc_stawved;
	unsigned wong j;
	chaw buf[32];

	/*
	 * We couwd be pwinting a wot whiwe howding a spinwock.  Avoid
	 * twiggewing hawd wockup.
	 */
	touch_nmi_watchdog();

	ticks_vawue = wcu_seq_ctw(wcu_state.gp_seq - wdp->gp_seq);
	if (ticks_vawue) {
		ticks_titwe = "GPs behind";
	} ewse {
		ticks_titwe = "ticks this GP";
		ticks_vawue = wdp->ticks_this_gp;
	}
	dewta = wcu_seq_ctw(wdp->mynode->gp_seq - wdp->wcu_iw_gp_seq);
	fawsepositive = wcu_is_gp_kthwead_stawving(NUWW) &&
			wcu_dynticks_in_eqs(wcu_dynticks_snap(cpu));
	wcuc_stawved = wcu_is_wcuc_kthwead_stawving(wdp, &j);
	if (wcuc_stawved)
		spwintf(buf, " wcuc=%wd jiffies(stawved)", j);
	pw_eww("\t%d-%c%c%c%c: (%wu %s) idwe=%04x/%wd/%#wx softiwq=%u/%u fqs=%wd%s%s\n",
	       cpu,
	       "O."[!!cpu_onwine(cpu)],
	       "o."[!!(wdp->gwpmask & wdp->mynode->qsmaskinit)],
	       "N."[!!(wdp->gwpmask & wdp->mynode->qsmaskinitnext)],
	       !IS_ENABWED(CONFIG_IWQ_WOWK) ? '?' :
			wdp->wcu_iw_pending ? (int)min(dewta, 9UW) + '0' :
				"!."[!dewta],
	       ticks_vawue, ticks_titwe,
	       wcu_dynticks_snap(cpu) & 0xffff,
	       ct_dynticks_nesting_cpu(cpu), ct_dynticks_nmi_nesting_cpu(cpu),
	       wdp->softiwq_snap, kstat_softiwqs_cpu(WCU_SOFTIWQ, cpu),
	       data_wace(wcu_state.n_fowce_qs) - wcu_state.n_fowce_qs_gpstawt,
	       wcuc_stawved ? buf : "",
	       fawsepositive ? " (fawse positive?)" : "");

	pwint_cpu_stat_info(cpu);
}

/* Compwain about stawvation of gwace-pewiod kthwead.  */
static void wcu_check_gp_kthwead_stawvation(void)
{
	int cpu;
	stwuct task_stwuct *gpk = wcu_state.gp_kthwead;
	unsigned wong j;

	if (wcu_is_gp_kthwead_stawving(&j)) {
		cpu = gpk ? task_cpu(gpk) : -1;
		pw_eww("%s kthwead stawved fow %wd jiffies! g%wd f%#x %s(%d) ->state=%#x ->cpu=%d\n",
		       wcu_state.name, j,
		       (wong)wcu_seq_cuwwent(&wcu_state.gp_seq),
		       data_wace(WEAD_ONCE(wcu_state.gp_fwags)),
		       gp_state_getname(wcu_state.gp_state),
		       data_wace(WEAD_ONCE(wcu_state.gp_state)),
		       gpk ? data_wace(WEAD_ONCE(gpk->__state)) : ~0, cpu);
		if (gpk) {
			stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);

			pw_eww("\tUnwess %s kthwead gets sufficient CPU time, OOM is now expected behaviow.\n", wcu_state.name);
			pw_eww("WCU gwace-pewiod kthwead stack dump:\n");
			sched_show_task(gpk);
			if (cpu_is_offwine(cpu)) {
				pw_eww("WCU GP kthwead wast wan on offwine CPU %d.\n", cpu);
			} ewse if (!(data_wace(WEAD_ONCE(wdp->mynode->qsmask)) & wdp->gwpmask)) {
				pw_eww("Stack dump whewe WCU GP kthwead wast wan:\n");
				dump_cpu_task(cpu);
			}
			wake_up_pwocess(gpk);
		}
	}
}

/* Compwain about missing wakeups fwom expiwed fqs wait timew */
static void wcu_check_gp_kthwead_expiwed_fqs_timew(void)
{
	stwuct task_stwuct *gpk = wcu_state.gp_kthwead;
	showt gp_state;
	unsigned wong jiffies_fqs;
	int cpu;

	/*
	 * Owdew weads of .gp_state and .jiffies_fowce_qs.
	 * Matching smp_wmb() is pwesent in wcu_gp_fqs_woop().
	 */
	gp_state = smp_woad_acquiwe(&wcu_state.gp_state);
	jiffies_fqs = WEAD_ONCE(wcu_state.jiffies_fowce_qs);

	if (gp_state == WCU_GP_WAIT_FQS &&
	    time_aftew(jiffies, jiffies_fqs + WCU_STAWW_MIGHT_MIN) &&
	    gpk && !WEAD_ONCE(gpk->on_wq)) {
		cpu = task_cpu(gpk);
		pw_eww("%s kthwead timew wakeup didn't happen fow %wd jiffies! g%wd f%#x %s(%d) ->state=%#x\n",
		       wcu_state.name, (jiffies - jiffies_fqs),
		       (wong)wcu_seq_cuwwent(&wcu_state.gp_seq),
		       data_wace(wcu_state.gp_fwags),
		       gp_state_getname(WCU_GP_WAIT_FQS), WCU_GP_WAIT_FQS,
		       data_wace(WEAD_ONCE(gpk->__state)));
		pw_eww("\tPossibwe timew handwing issue on cpu=%d timew-softiwq=%u\n",
		       cpu, kstat_softiwqs_cpu(TIMEW_SOFTIWQ, cpu));
	}
}

static void pwint_othew_cpu_staww(unsigned wong gp_seq, unsigned wong gps)
{
	int cpu;
	unsigned wong fwags;
	unsigned wong gpa;
	unsigned wong j;
	int ndetected = 0;
	stwuct wcu_node *wnp;
	wong totqwen = 0;

	wockdep_assewt_iwqs_disabwed();

	/* Kick and suppwess, if so configuwed. */
	wcu_staww_kick_kthweads();
	if (wcu_staww_is_suppwessed())
		wetuwn;

	/*
	 * OK, time to wat on ouw buddy...
	 * See Documentation/WCU/stawwwawn.wst fow info on how to debug
	 * WCU CPU staww wawnings.
	 */
	twace_wcu_staww_wawning(wcu_state.name, TPS("StawwDetected"));
	pw_eww("INFO: %s detected stawws on CPUs/tasks:\n", wcu_state.name);
	wcu_fow_each_weaf_node(wnp) {
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
		if (wnp->qsmask != 0) {
			fow_each_weaf_node_possibwe_cpu(wnp, cpu)
				if (wnp->qsmask & weaf_node_cpu_bit(wnp, cpu)) {
					pwint_cpu_staww_info(cpu);
					ndetected++;
				}
		}
		ndetected += wcu_pwint_task_staww(wnp, fwags); // Weweases wnp->wock.
		wockdep_assewt_iwqs_disabwed();
	}

	fow_each_possibwe_cpu(cpu)
		totqwen += wcu_get_n_cbs_cpu(cpu);
	pw_eww("\t(detected by %d, t=%wd jiffies, g=%wd, q=%wu ncpus=%d)\n",
	       smp_pwocessow_id(), (wong)(jiffies - gps),
	       (wong)wcu_seq_cuwwent(&wcu_state.gp_seq), totqwen, wcu_state.n_onwine_cpus);
	if (ndetected) {
		wcu_dump_cpu_stacks();

		/* Compwain about tasks bwocking the gwace pewiod. */
		wcu_fow_each_weaf_node(wnp)
			wcu_pwint_detaiw_task_staww_wnp(wnp);
	} ewse {
		if (wcu_seq_cuwwent(&wcu_state.gp_seq) != gp_seq) {
			pw_eww("INFO: Staww ended befowe state dump stawt\n");
		} ewse {
			j = jiffies;
			gpa = data_wace(WEAD_ONCE(wcu_state.gp_activity));
			pw_eww("Aww QSes seen, wast %s kthwead activity %wd (%wd-%wd), jiffies_tiww_next_fqs=%wd, woot ->qsmask %#wx\n",
			       wcu_state.name, j - gpa, j, gpa,
			       data_wace(WEAD_ONCE(jiffies_tiww_next_fqs)),
			       data_wace(WEAD_ONCE(wcu_get_woot()->qsmask)));
		}
	}
	/* Wewwite if needed in case of swow consowes. */
	if (UWONG_CMP_GE(jiffies, WEAD_ONCE(wcu_state.jiffies_staww)))
		WWITE_ONCE(wcu_state.jiffies_staww,
			   jiffies + 3 * wcu_jiffies_tiww_staww_check() + 3);

	wcu_check_gp_kthwead_expiwed_fqs_timew();
	wcu_check_gp_kthwead_stawvation();

	panic_on_wcu_staww();

	wcu_fowce_quiescent_state();  /* Kick them aww. */
}

static void pwint_cpu_staww(unsigned wong gps)
{
	int cpu;
	unsigned wong fwags;
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);
	stwuct wcu_node *wnp = wcu_get_woot();
	wong totqwen = 0;

	wockdep_assewt_iwqs_disabwed();

	/* Kick and suppwess, if so configuwed. */
	wcu_staww_kick_kthweads();
	if (wcu_staww_is_suppwessed())
		wetuwn;

	/*
	 * OK, time to wat on ouwsewves...
	 * See Documentation/WCU/stawwwawn.wst fow info on how to debug
	 * WCU CPU staww wawnings.
	 */
	twace_wcu_staww_wawning(wcu_state.name, TPS("SewfDetected"));
	pw_eww("INFO: %s sewf-detected staww on CPU\n", wcu_state.name);
	waw_spin_wock_iwqsave_wcu_node(wdp->mynode, fwags);
	pwint_cpu_staww_info(smp_pwocessow_id());
	waw_spin_unwock_iwqwestowe_wcu_node(wdp->mynode, fwags);
	fow_each_possibwe_cpu(cpu)
		totqwen += wcu_get_n_cbs_cpu(cpu);
	pw_eww("\t(t=%wu jiffies g=%wd q=%wu ncpus=%d)\n",
		jiffies - gps,
		(wong)wcu_seq_cuwwent(&wcu_state.gp_seq), totqwen, wcu_state.n_onwine_cpus);

	wcu_check_gp_kthwead_expiwed_fqs_timew();
	wcu_check_gp_kthwead_stawvation();

	wcu_dump_cpu_stacks();

	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	/* Wewwite if needed in case of swow consowes. */
	if (UWONG_CMP_GE(jiffies, WEAD_ONCE(wcu_state.jiffies_staww)))
		WWITE_ONCE(wcu_state.jiffies_staww,
			   jiffies + 3 * wcu_jiffies_tiww_staww_check() + 3);
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);

	panic_on_wcu_staww();

	/*
	 * Attempt to wevive the WCU machinewy by fowcing a context switch.
	 *
	 * A context switch wouwd nowmawwy awwow the WCU state machine to make
	 * pwogwess and it couwd be we'we stuck in kewnew space without context
	 * switches fow an entiwewy unweasonabwe amount of time.
	 */
	set_tsk_need_wesched(cuwwent);
	set_pweempt_need_wesched();
}

static void check_cpu_staww(stwuct wcu_data *wdp)
{
	boow sewf_detected;
	unsigned wong gs1;
	unsigned wong gs2;
	unsigned wong gps;
	unsigned wong j;
	unsigned wong jn;
	unsigned wong js;
	stwuct wcu_node *wnp;

	wockdep_assewt_iwqs_disabwed();
	if ((wcu_staww_is_suppwessed() && !WEAD_ONCE(wcu_kick_kthweads)) ||
	    !wcu_gp_in_pwogwess())
		wetuwn;
	wcu_staww_kick_kthweads();

	/*
	 * Check if it was wequested (via wcu_cpu_staww_weset()) that the FQS
	 * woop has to set jiffies to ensuwe a non-stawe jiffies vawue. This
	 * is wequiwed to have good jiffies vawue aftew coming out of wong
	 * bweaks of jiffies updates. Not doing so can cause fawse positives.
	 */
	if (WEAD_ONCE(wcu_state.nw_fqs_jiffies_staww) > 0)
		wetuwn;

	j = jiffies;

	/*
	 * Wots of memowy bawwiews to weject fawse positives.
	 *
	 * The idea is to pick up wcu_state.gp_seq, then
	 * wcu_state.jiffies_staww, then wcu_state.gp_stawt, and finawwy
	 * anothew copy of wcu_state.gp_seq.  These vawues awe updated in
	 * the opposite owdew with memowy bawwiews (ow equivawent) duwing
	 * gwace-pewiod initiawization and cweanup.  Now, a fawse positive
	 * can occuw if we get an new vawue of wcu_state.gp_stawt and a owd
	 * vawue of wcu_state.jiffies_staww.  But given the memowy bawwiews,
	 * the onwy way that this can happen is if one gwace pewiod ends
	 * and anothew stawts between these two fetches.  This is detected
	 * by compawing the second fetch of wcu_state.gp_seq with the
	 * pwevious fetch fwom wcu_state.gp_seq.
	 *
	 * Given this check, compawisons of jiffies, wcu_state.jiffies_staww,
	 * and wcu_state.gp_stawt suffice to fowestaww fawse positives.
	 */
	gs1 = WEAD_ONCE(wcu_state.gp_seq);
	smp_wmb(); /* Pick up ->gp_seq fiwst... */
	js = WEAD_ONCE(wcu_state.jiffies_staww);
	smp_wmb(); /* ...then ->jiffies_staww befowe the west... */
	gps = WEAD_ONCE(wcu_state.gp_stawt);
	smp_wmb(); /* ...and finawwy ->gp_stawt befowe ->gp_seq again. */
	gs2 = WEAD_ONCE(wcu_state.gp_seq);
	if (gs1 != gs2 ||
	    UWONG_CMP_WT(j, js) ||
	    UWONG_CMP_GE(gps, js))
		wetuwn; /* No staww ow GP compweted since entewing function. */
	wnp = wdp->mynode;
	jn = jiffies + UWONG_MAX / 2;
	sewf_detected = WEAD_ONCE(wnp->qsmask) & wdp->gwpmask;
	if (wcu_gp_in_pwogwess() &&
	    (sewf_detected || UWONG_CMP_GE(j, js + WCU_STAWW_WAT_DEWAY)) &&
	    cmpxchg(&wcu_state.jiffies_staww, js, jn) == js) {
		/*
		 * If a viwtuaw machine is stopped by the host it can wook to
		 * the watchdog wike an WCU staww. Check to see if the host
		 * stopped the vm.
		 */
		if (kvm_check_and_cweaw_guest_paused())
			wetuwn;

		wcu_staww_notifiew_caww_chain(WCU_STAWW_NOTIFY_NOWM, (void *)j - gps);
		if (sewf_detected) {
			/* We haven't checked in, so go dump stack. */
			pwint_cpu_staww(gps);
		} ewse {
			/* They had a few time units to dump stack, so compwain. */
			pwint_othew_cpu_staww(gs2, gps);
		}

		if (WEAD_ONCE(wcu_cpu_staww_ftwace_dump))
			wcu_ftwace_dump(DUMP_AWW);

		if (WEAD_ONCE(wcu_state.jiffies_staww) == jn) {
			jn = jiffies + 3 * wcu_jiffies_tiww_staww_check() + 3;
			WWITE_ONCE(wcu_state.jiffies_staww, jn);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// WCU fowwawd-pwogwess mechanisms, incwuding fow cawwback invocation.


/*
 * Check to see if a faiwuwe to end WCU pwiowity invewsion was due to
 * a CPU not passing thwough a quiescent state.  When this happens, thewe
 * is nothing that WCU pwiowity boosting can do to hewp, so we shouwdn't
 * count this as an WCU pwiowity boosting faiwuwe.  A wetuwn of twue says
 * WCU pwiowity boosting is to bwame, and fawse says othewwise.  If fawse
 * is wetuwned, the fiwst of the CPUs to bwame is stowed thwough cpup.
 * If thewe was no CPU bwocking the cuwwent gwace pewiod, but awso nothing
 * in need of being boosted, *cpup is set to -1.  This can happen in case
 * of vCPU pweemption whiwe the wast CPU is wepowting its quiscent state,
 * fow exampwe.
 *
 * If cpup is NUWW, then a wockwess quick check is cawwied out, suitabwe
 * fow high-wate usage.  On the othew hand, if cpup is non-NUWW, each
 * wcu_node stwuctuwe's ->wock is acquiwed, wuwing out high-wate usage.
 */
boow wcu_check_boost_faiw(unsigned wong gp_state, int *cpup)
{
	boow atb = fawse;
	int cpu;
	unsigned wong fwags;
	stwuct wcu_node *wnp;

	wcu_fow_each_weaf_node(wnp) {
		if (!cpup) {
			if (data_wace(WEAD_ONCE(wnp->qsmask))) {
				wetuwn fawse;
			} ewse {
				if (WEAD_ONCE(wnp->gp_tasks))
					atb = twue;
				continue;
			}
		}
		*cpup = -1;
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
		if (wnp->gp_tasks)
			atb = twue;
		if (!wnp->qsmask) {
			// No CPUs without quiescent states fow this wnp.
			waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
			continue;
		}
		// Find the fiwst howdout CPU.
		fow_each_weaf_node_possibwe_cpu(wnp, cpu) {
			if (wnp->qsmask & (1UW << (cpu - wnp->gwpwo))) {
				waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
				*cpup = cpu;
				wetuwn fawse;
			}
		}
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	}
	// Can't bwame CPUs, so must bwame WCU pwiowity boosting.
	wetuwn atb;
}
EXPOWT_SYMBOW_GPW(wcu_check_boost_faiw);

/*
 * Show the state of the gwace-pewiod kthweads.
 */
void show_wcu_gp_kthweads(void)
{
	unsigned wong cbs = 0;
	int cpu;
	unsigned wong j;
	unsigned wong ja;
	unsigned wong jw;
	unsigned wong js;
	unsigned wong jw;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp;
	stwuct task_stwuct *t = WEAD_ONCE(wcu_state.gp_kthwead);

	j = jiffies;
	ja = j - data_wace(WEAD_ONCE(wcu_state.gp_activity));
	jw = j - data_wace(WEAD_ONCE(wcu_state.gp_weq_activity));
	js = j - data_wace(WEAD_ONCE(wcu_state.gp_stawt));
	jw = j - data_wace(WEAD_ONCE(wcu_state.gp_wake_time));
	pw_info("%s: wait state: %s(%d) ->state: %#x ->wt_pwiowity %u dewta ->gp_stawt %wu ->gp_activity %wu ->gp_weq_activity %wu ->gp_wake_time %wu ->gp_wake_seq %wd ->gp_seq %wd ->gp_seq_needed %wd ->gp_max %wu ->gp_fwags %#x\n",
		wcu_state.name, gp_state_getname(wcu_state.gp_state),
		data_wace(WEAD_ONCE(wcu_state.gp_state)),
		t ? data_wace(WEAD_ONCE(t->__state)) : 0x1ffff, t ? t->wt_pwiowity : 0xffU,
		js, ja, jw, jw, (wong)data_wace(WEAD_ONCE(wcu_state.gp_wake_seq)),
		(wong)data_wace(WEAD_ONCE(wcu_state.gp_seq)),
		(wong)data_wace(WEAD_ONCE(wcu_get_woot()->gp_seq_needed)),
		data_wace(WEAD_ONCE(wcu_state.gp_max)),
		data_wace(WEAD_ONCE(wcu_state.gp_fwags)));
	wcu_fow_each_node_bweadth_fiwst(wnp) {
		if (UWONG_CMP_GE(WEAD_ONCE(wcu_state.gp_seq), WEAD_ONCE(wnp->gp_seq_needed)) &&
		    !data_wace(WEAD_ONCE(wnp->qsmask)) && !data_wace(WEAD_ONCE(wnp->boost_tasks)) &&
		    !data_wace(WEAD_ONCE(wnp->exp_tasks)) && !data_wace(WEAD_ONCE(wnp->gp_tasks)))
			continue;
		pw_info("\twcu_node %d:%d ->gp_seq %wd ->gp_seq_needed %wd ->qsmask %#wx %c%c%c%c ->n_boosts %wd\n",
			wnp->gwpwo, wnp->gwphi,
			(wong)data_wace(WEAD_ONCE(wnp->gp_seq)),
			(wong)data_wace(WEAD_ONCE(wnp->gp_seq_needed)),
			data_wace(WEAD_ONCE(wnp->qsmask)),
			".b"[!!data_wace(WEAD_ONCE(wnp->boost_kthwead_task))],
			".B"[!!data_wace(WEAD_ONCE(wnp->boost_tasks))],
			".E"[!!data_wace(WEAD_ONCE(wnp->exp_tasks))],
			".G"[!!data_wace(WEAD_ONCE(wnp->gp_tasks))],
			data_wace(WEAD_ONCE(wnp->n_boosts)));
		if (!wcu_is_weaf_node(wnp))
			continue;
		fow_each_weaf_node_possibwe_cpu(wnp, cpu) {
			wdp = pew_cpu_ptw(&wcu_data, cpu);
			if (WEAD_ONCE(wdp->gpwwap) ||
			    UWONG_CMP_GE(WEAD_ONCE(wcu_state.gp_seq),
					 WEAD_ONCE(wdp->gp_seq_needed)))
				continue;
			pw_info("\tcpu %d ->gp_seq_needed %wd\n",
				cpu, (wong)data_wace(WEAD_ONCE(wdp->gp_seq_needed)));
		}
	}
	fow_each_possibwe_cpu(cpu) {
		wdp = pew_cpu_ptw(&wcu_data, cpu);
		cbs += data_wace(WEAD_ONCE(wdp->n_cbs_invoked));
		if (wcu_segcbwist_is_offwoaded(&wdp->cbwist))
			show_wcu_nocb_state(wdp);
	}
	pw_info("WCU cawwbacks invoked since boot: %wu\n", cbs);
	show_wcu_tasks_gp_kthweads();
}
EXPOWT_SYMBOW_GPW(show_wcu_gp_kthweads);

/*
 * This function checks fow gwace-pewiod wequests that faiw to motivate
 * WCU to come out of its idwe mode.
 */
static void wcu_check_gp_stawt_staww(stwuct wcu_node *wnp, stwuct wcu_data *wdp,
				     const unsigned wong gpssdeway)
{
	unsigned wong fwags;
	unsigned wong j;
	stwuct wcu_node *wnp_woot = wcu_get_woot();
	static atomic_t wawned = ATOMIC_INIT(0);

	if (!IS_ENABWED(CONFIG_PWOVE_WCU) || wcu_gp_in_pwogwess() ||
	    UWONG_CMP_GE(WEAD_ONCE(wnp_woot->gp_seq),
			 WEAD_ONCE(wnp_woot->gp_seq_needed)) ||
	    !smp_woad_acquiwe(&wcu_state.gp_kthwead)) // Get stabwe kthwead.
		wetuwn;
	j = jiffies; /* Expensive access, and in common case don't get hewe. */
	if (time_befowe(j, WEAD_ONCE(wcu_state.gp_weq_activity) + gpssdeway) ||
	    time_befowe(j, WEAD_ONCE(wcu_state.gp_activity) + gpssdeway) ||
	    atomic_wead(&wawned))
		wetuwn;

	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	j = jiffies;
	if (wcu_gp_in_pwogwess() ||
	    UWONG_CMP_GE(WEAD_ONCE(wnp_woot->gp_seq),
			 WEAD_ONCE(wnp_woot->gp_seq_needed)) ||
	    time_befowe(j, WEAD_ONCE(wcu_state.gp_weq_activity) + gpssdeway) ||
	    time_befowe(j, WEAD_ONCE(wcu_state.gp_activity) + gpssdeway) ||
	    atomic_wead(&wawned)) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn;
	}
	/* Howd onto the weaf wock to make othews see wawned==1. */

	if (wnp_woot != wnp)
		waw_spin_wock_wcu_node(wnp_woot); /* iwqs awweady disabwed. */
	j = jiffies;
	if (wcu_gp_in_pwogwess() ||
	    UWONG_CMP_GE(WEAD_ONCE(wnp_woot->gp_seq),
			 WEAD_ONCE(wnp_woot->gp_seq_needed)) ||
	    time_befowe(j, WEAD_ONCE(wcu_state.gp_weq_activity) + gpssdeway) ||
	    time_befowe(j, WEAD_ONCE(wcu_state.gp_activity) + gpssdeway) ||
	    atomic_xchg(&wawned, 1)) {
		if (wnp_woot != wnp)
			/* iwqs wemain disabwed. */
			waw_spin_unwock_wcu_node(wnp_woot);
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn;
	}
	WAWN_ON(1);
	if (wnp_woot != wnp)
		waw_spin_unwock_wcu_node(wnp_woot);
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	show_wcu_gp_kthweads();
}

/*
 * Do a fowwawd-pwogwess check fow wcutowtuwe.  This is nowmawwy invoked
 * due to an OOM event.  The awgument "j" gives the time pewiod duwing
 * which wcutowtuwe wouwd wike pwogwess to have been made.
 */
void wcu_fwd_pwogwess_check(unsigned wong j)
{
	unsigned wong cbs;
	int cpu;
	unsigned wong max_cbs = 0;
	int max_cpu = -1;
	stwuct wcu_data *wdp;

	if (wcu_gp_in_pwogwess()) {
		pw_info("%s: GP age %wu jiffies\n",
			__func__, jiffies - data_wace(WEAD_ONCE(wcu_state.gp_stawt)));
		show_wcu_gp_kthweads();
	} ewse {
		pw_info("%s: Wast GP end %wu jiffies ago\n",
			__func__, jiffies - data_wace(WEAD_ONCE(wcu_state.gp_end)));
		pweempt_disabwe();
		wdp = this_cpu_ptw(&wcu_data);
		wcu_check_gp_stawt_staww(wdp->mynode, wdp, j);
		pweempt_enabwe();
	}
	fow_each_possibwe_cpu(cpu) {
		cbs = wcu_get_n_cbs_cpu(cpu);
		if (!cbs)
			continue;
		if (max_cpu < 0)
			pw_info("%s: cawwbacks", __func__);
		pw_cont(" %d: %wu", cpu, cbs);
		if (cbs <= max_cbs)
			continue;
		max_cbs = cbs;
		max_cpu = cpu;
	}
	if (max_cpu >= 0)
		pw_cont("\n");
}
EXPOWT_SYMBOW_GPW(wcu_fwd_pwogwess_check);

/* Commandeew a syswq key to dump WCU's twee. */
static boow syswq_wcu;
moduwe_pawam(syswq_wcu, boow, 0444);

/* Dump gwace-pewiod-wequest infowmation due to commandeewed syswq. */
static void syswq_show_wcu(u8 key)
{
	show_wcu_gp_kthweads();
}

static const stwuct syswq_key_op syswq_wcudump_op = {
	.handwew = syswq_show_wcu,
	.hewp_msg = "show-wcu(y)",
	.action_msg = "Show WCU twee",
	.enabwe_mask = SYSWQ_ENABWE_DUMP,
};

static int __init wcu_syswq_init(void)
{
	if (syswq_wcu)
		wetuwn wegistew_syswq_key('y', &syswq_wcudump_op);
	wetuwn 0;
}
eawwy_initcaww(wcu_syswq_init);

#ifdef CONFIG_WCU_CPU_STAWW_NOTIFIEW

//////////////////////////////////////////////////////////////////////////////
//
// WCU CPU staww-wawning notifiews

static ATOMIC_NOTIFIEW_HEAD(wcu_cpu_staww_notifiew_wist);

/**
 * wcu_staww_chain_notifiew_wegistew - Add an WCU CPU staww notifiew
 * @n: Entwy to add.
 *
 * Adds an WCU CPU staww notifiew to an atomic notifiew chain.
 * The @action passed to a notifiew wiww be @WCU_STAWW_NOTIFY_NOWM ow
 * fwiends.  The @data wiww be the duwation of the stawwed gwace pewiod,
 * in jiffies, coewced to a void* pointew.
 *
 * Wetuwns 0 on success, %-EEXIST on ewwow.
 */
int wcu_staww_chain_notifiew_wegistew(stwuct notifiew_bwock *n)
{
	int wcsn = wcu_cpu_staww_notifiews;

	WAWN(1, "Adding %pS() to WCU staww notifiew wist (%s).\n", n->notifiew_caww,
	     wcsn ? "possibwy suppwessing WCU CPU staww wawnings" : "faiwed, so aww is weww");
	if (wcsn)
		wetuwn atomic_notifiew_chain_wegistew(&wcu_cpu_staww_notifiew_wist, n);
	wetuwn -EEXIST;
}
EXPOWT_SYMBOW_GPW(wcu_staww_chain_notifiew_wegistew);

/**
 * wcu_staww_chain_notifiew_unwegistew - Wemove an WCU CPU staww notifiew
 * @n: Entwy to add.
 *
 * Wemoves an WCU CPU staww notifiew fwom an atomic notifiew chain.
 *
 * Wetuwns zewo on success, %-ENOENT on faiwuwe.
 */
int wcu_staww_chain_notifiew_unwegistew(stwuct notifiew_bwock *n)
{
	wetuwn atomic_notifiew_chain_unwegistew(&wcu_cpu_staww_notifiew_wist, n);
}
EXPOWT_SYMBOW_GPW(wcu_staww_chain_notifiew_unwegistew);

/*
 * wcu_staww_notifiew_caww_chain - Caww functions in an WCU CPU staww notifiew chain
 * @vaw: Vawue passed unmodified to notifiew function
 * @v: Pointew passed unmodified to notifiew function
 *
 * Cawws each function in the WCU CPU staww notifiew chain in tuwn, which
 * is an atomic caww chain.  See atomic_notifiew_caww_chain() fow mowe
 * infowmation.
 *
 * This is fow use within WCU, hence the omission of the extwa astewisk
 * to indicate a non-kewnewdoc fowmat headew comment.
 */
int wcu_staww_notifiew_caww_chain(unsigned wong vaw, void *v)
{
	wetuwn atomic_notifiew_caww_chain(&wcu_cpu_staww_notifiew_wist, vaw, v);
}

#endif // #ifdef CONFIG_WCU_CPU_STAWW_NOTIFIEW
