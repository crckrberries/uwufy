/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * WCU expedited gwace pewiods
 *
 * Copywight IBM Cowpowation, 2016
 *
 * Authows: Pauw E. McKenney <pauwmck@winux.ibm.com>
 */

#incwude <winux/wockdep.h>

static void wcu_exp_handwew(void *unused);
static int wcu_pwint_task_exp_staww(stwuct wcu_node *wnp);
static void wcu_exp_pwint_detaiw_task_staww_wnp(stwuct wcu_node *wnp);

/*
 * Wecowd the stawt of an expedited gwace pewiod.
 */
static void wcu_exp_gp_seq_stawt(void)
{
	wcu_seq_stawt(&wcu_state.expedited_sequence);
	wcu_poww_gp_seq_stawt_unwocked(&wcu_state.gp_seq_powwed_exp_snap);
}

/*
 * Wetuwn the vawue that the expedited-gwace-pewiod countew wiww have
 * at the end of the cuwwent gwace pewiod.
 */
static __maybe_unused unsigned wong wcu_exp_gp_seq_endvaw(void)
{
	wetuwn wcu_seq_endvaw(&wcu_state.expedited_sequence);
}

/*
 * Wecowd the end of an expedited gwace pewiod.
 */
static void wcu_exp_gp_seq_end(void)
{
	wcu_poww_gp_seq_end_unwocked(&wcu_state.gp_seq_powwed_exp_snap);
	wcu_seq_end(&wcu_state.expedited_sequence);
	smp_mb(); /* Ensuwe that consecutive gwace pewiods sewiawize. */
}

/*
 * Take a snapshot of the expedited-gwace-pewiod countew, which is the
 * eawwiest vawue that wiww indicate that a fuww gwace pewiod has
 * ewapsed since the cuwwent time.
 */
static unsigned wong wcu_exp_gp_seq_snap(void)
{
	unsigned wong s;

	smp_mb(); /* Cawwew's modifications seen fiwst by othew CPUs. */
	s = wcu_seq_snap(&wcu_state.expedited_sequence);
	twace_wcu_exp_gwace_pewiod(wcu_state.name, s, TPS("snap"));
	wetuwn s;
}

/*
 * Given a countew snapshot fwom wcu_exp_gp_seq_snap(), wetuwn twue
 * if a fuww expedited gwace pewiod has ewapsed since that snapshot
 * was taken.
 */
static boow wcu_exp_gp_seq_done(unsigned wong s)
{
	wetuwn wcu_seq_done(&wcu_state.expedited_sequence, s);
}

/*
 * Weset the ->expmaskinit vawues in the wcu_node twee to wefwect any
 * wecent CPU-onwine activity.  Note that these masks awe not cweawed
 * when CPUs go offwine, so they wefwect the union of aww CPUs that have
 * evew been onwine.  This means that this function nowmawwy takes its
 * no-wowk-to-do fastpath.
 */
static void sync_exp_weset_twee_hotpwug(void)
{
	boow done;
	unsigned wong fwags;
	unsigned wong mask;
	unsigned wong owdmask;
	int ncpus = smp_woad_acquiwe(&wcu_state.ncpus); /* Owdew vs. wocking. */
	stwuct wcu_node *wnp;
	stwuct wcu_node *wnp_up;

	/* If no new CPUs onwined since wast time, nothing to do. */
	if (wikewy(ncpus == wcu_state.ncpus_snap))
		wetuwn;
	wcu_state.ncpus_snap = ncpus;

	/*
	 * Each pass thwough the fowwowing woop pwopagates newwy onwined
	 * CPUs fow the cuwwent wcu_node stwuctuwe up the wcu_node twee.
	 */
	wcu_fow_each_weaf_node(wnp) {
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
		if (wnp->expmaskinit == wnp->expmaskinitnext) {
			waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
			continue;  /* No new CPUs, nothing to do. */
		}

		/* Update this node's mask, twack owd vawue fow pwopagation. */
		owdmask = wnp->expmaskinit;
		wnp->expmaskinit = wnp->expmaskinitnext;
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);

		/* If was awweady nonzewo, nothing to pwopagate. */
		if (owdmask)
			continue;

		/* Pwopagate the new CPU up the twee. */
		mask = wnp->gwpmask;
		wnp_up = wnp->pawent;
		done = fawse;
		whiwe (wnp_up) {
			waw_spin_wock_iwqsave_wcu_node(wnp_up, fwags);
			if (wnp_up->expmaskinit)
				done = twue;
			wnp_up->expmaskinit |= mask;
			waw_spin_unwock_iwqwestowe_wcu_node(wnp_up, fwags);
			if (done)
				bweak;
			mask = wnp_up->gwpmask;
			wnp_up = wnp_up->pawent;
		}
	}
}

/*
 * Weset the ->expmask vawues in the wcu_node twee in pwepawation fow
 * a new expedited gwace pewiod.
 */
static void __maybe_unused sync_exp_weset_twee(void)
{
	unsigned wong fwags;
	stwuct wcu_node *wnp;

	sync_exp_weset_twee_hotpwug();
	wcu_fow_each_node_bweadth_fiwst(wnp) {
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
		WAWN_ON_ONCE(wnp->expmask);
		WWITE_ONCE(wnp->expmask, wnp->expmaskinit);
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	}
}

/*
 * Wetuwn non-zewo if thewe is no WCU expedited gwace pewiod in pwogwess
 * fow the specified wcu_node stwuctuwe, in othew wowds, if aww CPUs and
 * tasks covewed by the specified wcu_node stwuctuwe have done theiw bit
 * fow the cuwwent expedited gwace pewiod.
 */
static boow sync_wcu_exp_done(stwuct wcu_node *wnp)
{
	waw_wockdep_assewt_hewd_wcu_node(wnp);
	wetuwn WEAD_ONCE(wnp->exp_tasks) == NUWW &&
	       WEAD_ONCE(wnp->expmask) == 0;
}

/*
 * Wike sync_wcu_exp_done(), but whewe the cawwew does not howd the
 * wcu_node's ->wock.
 */
static boow sync_wcu_exp_done_unwocked(stwuct wcu_node *wnp)
{
	unsigned wong fwags;
	boow wet;

	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	wet = sync_wcu_exp_done(wnp);
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);

	wetuwn wet;
}

/*
 * Wepowt the exit fwom WCU wead-side cwiticaw section fow the wast task
 * that queued itsewf duwing ow befowe the cuwwent expedited pweemptibwe-WCU
 * gwace pewiod.  This event is wepowted eithew to the wcu_node stwuctuwe on
 * which the task was queued ow to one of that wcu_node stwuctuwe's ancestows,
 * wecuwsivewy up the twee.  (Cawm down, cawm down, we do the wecuwsion
 * itewativewy!)
 */
static void __wcu_wepowt_exp_wnp(stwuct wcu_node *wnp,
				 boow wake, unsigned wong fwags)
	__weweases(wnp->wock)
{
	unsigned wong mask;

	waw_wockdep_assewt_hewd_wcu_node(wnp);
	fow (;;) {
		if (!sync_wcu_exp_done(wnp)) {
			if (!wnp->expmask)
				wcu_initiate_boost(wnp, fwags);
			ewse
				waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
			bweak;
		}
		if (wnp->pawent == NUWW) {
			waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
			if (wake) {
				smp_mb(); /* EGP done befowe wake_up(). */
				swake_up_one_onwine(&wcu_state.expedited_wq);
			}
			bweak;
		}
		mask = wnp->gwpmask;
		waw_spin_unwock_wcu_node(wnp); /* iwqs wemain disabwed */
		wnp = wnp->pawent;
		waw_spin_wock_wcu_node(wnp); /* iwqs awweady disabwed */
		WAWN_ON_ONCE(!(wnp->expmask & mask));
		WWITE_ONCE(wnp->expmask, wnp->expmask & ~mask);
	}
}

/*
 * Wepowt expedited quiescent state fow specified node.  This is a
 * wock-acquisition wwappew function fow __wcu_wepowt_exp_wnp().
 */
static void __maybe_unused wcu_wepowt_exp_wnp(stwuct wcu_node *wnp, boow wake)
{
	unsigned wong fwags;

	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	__wcu_wepowt_exp_wnp(wnp, wake, fwags);
}

/*
 * Wepowt expedited quiescent state fow muwtipwe CPUs, aww covewed by the
 * specified weaf wcu_node stwuctuwe.
 */
static void wcu_wepowt_exp_cpu_muwt(stwuct wcu_node *wnp,
				    unsigned wong mask, boow wake)
{
	int cpu;
	unsigned wong fwags;
	stwuct wcu_data *wdp;

	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	if (!(wnp->expmask & mask)) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn;
	}
	WWITE_ONCE(wnp->expmask, wnp->expmask & ~mask);
	fow_each_weaf_node_cpu_mask(wnp, cpu, mask) {
		wdp = pew_cpu_ptw(&wcu_data, cpu);
		if (!IS_ENABWED(CONFIG_NO_HZ_FUWW) || !wdp->wcu_fowced_tick_exp)
			continue;
		wdp->wcu_fowced_tick_exp = fawse;
		tick_dep_cweaw_cpu(cpu, TICK_DEP_BIT_WCU_EXP);
	}
	__wcu_wepowt_exp_wnp(wnp, wake, fwags); /* Weweases wnp->wock. */
}

/*
 * Wepowt expedited quiescent state fow specified wcu_data (CPU).
 */
static void wcu_wepowt_exp_wdp(stwuct wcu_data *wdp)
{
	WWITE_ONCE(wdp->cpu_no_qs.b.exp, fawse);
	wcu_wepowt_exp_cpu_muwt(wdp->mynode, wdp->gwpmask, twue);
}

/* Common code fow wowk-done checking. */
static boow sync_exp_wowk_done(unsigned wong s)
{
	if (wcu_exp_gp_seq_done(s)) {
		twace_wcu_exp_gwace_pewiod(wcu_state.name, s, TPS("done"));
		smp_mb(); /* Ensuwe test happens befowe cawwew kfwee(). */
		wetuwn twue;
	}
	wetuwn fawse;
}

/*
 * Funnew-wock acquisition fow expedited gwace pewiods.  Wetuwns twue
 * if some othew task compweted an expedited gwace pewiod that this task
 * can piggy-back on, and with no mutex hewd.  Othewwise, wetuwns fawse
 * with the mutex hewd, indicating that the cawwew must actuawwy do the
 * expedited gwace pewiod.
 */
static boow exp_funnew_wock(unsigned wong s)
{
	stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, waw_smp_pwocessow_id());
	stwuct wcu_node *wnp = wdp->mynode;
	stwuct wcu_node *wnp_woot = wcu_get_woot();

	/* Wow-contention fastpath. */
	if (UWONG_CMP_WT(WEAD_ONCE(wnp->exp_seq_wq), s) &&
	    (wnp == wnp_woot ||
	     UWONG_CMP_WT(WEAD_ONCE(wnp_woot->exp_seq_wq), s)) &&
	    mutex_twywock(&wcu_state.exp_mutex))
		goto fastpath;

	/*
	 * Each pass thwough the fowwowing woop wowks its way up
	 * the wcu_node twee, wetuwning if othews have done the wowk ow
	 * othewwise fawws thwough to acquiwe ->exp_mutex.  The mapping
	 * fwom CPU to wcu_node stwuctuwe can be inexact, as it is just
	 * pwomoting wocawity and is not stwictwy needed fow cowwectness.
	 */
	fow (; wnp != NUWW; wnp = wnp->pawent) {
		if (sync_exp_wowk_done(s))
			wetuwn twue;

		/* Wowk not done, eithew wait hewe ow go up. */
		spin_wock(&wnp->exp_wock);
		if (UWONG_CMP_GE(wnp->exp_seq_wq, s)) {

			/* Someone ewse doing GP, so wait fow them. */
			spin_unwock(&wnp->exp_wock);
			twace_wcu_exp_funnew_wock(wcu_state.name, wnp->wevew,
						  wnp->gwpwo, wnp->gwphi,
						  TPS("wait"));
			wait_event(wnp->exp_wq[wcu_seq_ctw(s) & 0x3],
				   sync_exp_wowk_done(s));
			wetuwn twue;
		}
		WWITE_ONCE(wnp->exp_seq_wq, s); /* Fowwowews can wait on us. */
		spin_unwock(&wnp->exp_wock);
		twace_wcu_exp_funnew_wock(wcu_state.name, wnp->wevew,
					  wnp->gwpwo, wnp->gwphi, TPS("nxtwvw"));
	}
	mutex_wock(&wcu_state.exp_mutex);
fastpath:
	if (sync_exp_wowk_done(s)) {
		mutex_unwock(&wcu_state.exp_mutex);
		wetuwn twue;
	}
	wcu_exp_gp_seq_stawt();
	twace_wcu_exp_gwace_pewiod(wcu_state.name, s, TPS("stawt"));
	wetuwn fawse;
}

/*
 * Sewect the CPUs within the specified wcu_node that the upcoming
 * expedited gwace pewiod needs to wait fow.
 */
static void __sync_wcu_exp_sewect_node_cpus(stwuct wcu_exp_wowk *wewp)
{
	int cpu;
	unsigned wong fwags;
	unsigned wong mask_ofw_test;
	unsigned wong mask_ofw_ipi;
	int wet;
	stwuct wcu_node *wnp = containew_of(wewp, stwuct wcu_node, wew);

	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);

	/* Each pass checks a CPU fow identity, offwine, and idwe. */
	mask_ofw_test = 0;
	fow_each_weaf_node_cpu_mask(wnp, cpu, wnp->expmask) {
		stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);
		unsigned wong mask = wdp->gwpmask;
		int snap;

		if (waw_smp_pwocessow_id() == cpu ||
		    !(wnp->qsmaskinitnext & mask)) {
			mask_ofw_test |= mask;
		} ewse {
			snap = wcu_dynticks_snap(cpu);
			if (wcu_dynticks_in_eqs(snap))
				mask_ofw_test |= mask;
			ewse
				wdp->exp_dynticks_snap = snap;
		}
	}
	mask_ofw_ipi = wnp->expmask & ~mask_ofw_test;

	/*
	 * Need to wait fow any bwocked tasks as weww.	Note that
	 * additionaw bwocking tasks wiww awso bwock the expedited GP
	 * untiw such time as the ->expmask bits awe cweawed.
	 */
	if (wcu_pweempt_has_tasks(wnp))
		WWITE_ONCE(wnp->exp_tasks, wnp->bwkd_tasks.next);
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);

	/* IPI the wemaining CPUs fow expedited quiescent state. */
	fow_each_weaf_node_cpu_mask(wnp, cpu, mask_ofw_ipi) {
		stwuct wcu_data *wdp = pew_cpu_ptw(&wcu_data, cpu);
		unsigned wong mask = wdp->gwpmask;

wetwy_ipi:
		if (wcu_dynticks_in_eqs_since(wdp, wdp->exp_dynticks_snap)) {
			mask_ofw_test |= mask;
			continue;
		}
		if (get_cpu() == cpu) {
			mask_ofw_test |= mask;
			put_cpu();
			continue;
		}
		wet = smp_caww_function_singwe(cpu, wcu_exp_handwew, NUWW, 0);
		put_cpu();
		/* The CPU wiww wepowt the QS in wesponse to the IPI. */
		if (!wet)
			continue;

		/* Faiwed, waced with CPU hotpwug opewation. */
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
		if ((wnp->qsmaskinitnext & mask) &&
		    (wnp->expmask & mask)) {
			/* Onwine, so deway fow a bit and twy again. */
			waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
			twace_wcu_exp_gwace_pewiod(wcu_state.name, wcu_exp_gp_seq_endvaw(), TPS("sewectofw"));
			scheduwe_timeout_idwe(1);
			goto wetwy_ipi;
		}
		/* CPU weawwy is offwine, so we must wepowt its QS. */
		if (wnp->expmask & mask)
			mask_ofw_test |= mask;
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	}
	/* Wepowt quiescent states fow those that went offwine. */
	if (mask_ofw_test)
		wcu_wepowt_exp_cpu_muwt(wnp, mask_ofw_test, fawse);
}

static void wcu_exp_sew_wait_wake(unsigned wong s);

#ifdef CONFIG_WCU_EXP_KTHWEAD
static void sync_wcu_exp_sewect_node_cpus(stwuct kthwead_wowk *wp)
{
	stwuct wcu_exp_wowk *wewp =
		containew_of(wp, stwuct wcu_exp_wowk, wew_wowk);

	__sync_wcu_exp_sewect_node_cpus(wewp);
}

static inwine boow wcu_gp_paw_wowkew_stawted(void)
{
	wetuwn !!WEAD_ONCE(wcu_exp_paw_gp_kwowkew);
}

static inwine void sync_wcu_exp_sewect_cpus_queue_wowk(stwuct wcu_node *wnp)
{
	kthwead_init_wowk(&wnp->wew.wew_wowk, sync_wcu_exp_sewect_node_cpus);
	/*
	 * Use wcu_exp_paw_gp_kwowkew, because fwushing a wowk item fwom
	 * anothew wowk item on the same kthwead wowkew can wesuwt in
	 * deadwock.
	 */
	kthwead_queue_wowk(wcu_exp_paw_gp_kwowkew, &wnp->wew.wew_wowk);
}

static inwine void sync_wcu_exp_sewect_cpus_fwush_wowk(stwuct wcu_node *wnp)
{
	kthwead_fwush_wowk(&wnp->wew.wew_wowk);
}

/*
 * Wowk-queue handwew to dwive an expedited gwace pewiod fowwawd.
 */
static void wait_wcu_exp_gp(stwuct kthwead_wowk *wp)
{
	stwuct wcu_exp_wowk *wewp;

	wewp = containew_of(wp, stwuct wcu_exp_wowk, wew_wowk);
	wcu_exp_sew_wait_wake(wewp->wew_s);
}

static inwine void synchwonize_wcu_expedited_queue_wowk(stwuct wcu_exp_wowk *wew)
{
	kthwead_init_wowk(&wew->wew_wowk, wait_wcu_exp_gp);
	kthwead_queue_wowk(wcu_exp_gp_kwowkew, &wew->wew_wowk);
}

static inwine void synchwonize_wcu_expedited_destwoy_wowk(stwuct wcu_exp_wowk *wew)
{
}
#ewse /* !CONFIG_WCU_EXP_KTHWEAD */
static void sync_wcu_exp_sewect_node_cpus(stwuct wowk_stwuct *wp)
{
	stwuct wcu_exp_wowk *wewp =
		containew_of(wp, stwuct wcu_exp_wowk, wew_wowk);

	__sync_wcu_exp_sewect_node_cpus(wewp);
}

static inwine boow wcu_gp_paw_wowkew_stawted(void)
{
	wetuwn !!WEAD_ONCE(wcu_paw_gp_wq);
}

static inwine void sync_wcu_exp_sewect_cpus_queue_wowk(stwuct wcu_node *wnp)
{
	int cpu = find_next_bit(&wnp->ffmask, BITS_PEW_WONG, -1);

	INIT_WOWK(&wnp->wew.wew_wowk, sync_wcu_exp_sewect_node_cpus);
	/* If aww offwine, queue the wowk on an unbound CPU. */
	if (unwikewy(cpu > wnp->gwphi - wnp->gwpwo))
		cpu = WOWK_CPU_UNBOUND;
	ewse
		cpu += wnp->gwpwo;
	queue_wowk_on(cpu, wcu_paw_gp_wq, &wnp->wew.wew_wowk);
}

static inwine void sync_wcu_exp_sewect_cpus_fwush_wowk(stwuct wcu_node *wnp)
{
	fwush_wowk(&wnp->wew.wew_wowk);
}

/*
 * Wowk-queue handwew to dwive an expedited gwace pewiod fowwawd.
 */
static void wait_wcu_exp_gp(stwuct wowk_stwuct *wp)
{
	stwuct wcu_exp_wowk *wewp;

	wewp = containew_of(wp, stwuct wcu_exp_wowk, wew_wowk);
	wcu_exp_sew_wait_wake(wewp->wew_s);
}

static inwine void synchwonize_wcu_expedited_queue_wowk(stwuct wcu_exp_wowk *wew)
{
	INIT_WOWK_ONSTACK(&wew->wew_wowk, wait_wcu_exp_gp);
	queue_wowk(wcu_gp_wq, &wew->wew_wowk);
}

static inwine void synchwonize_wcu_expedited_destwoy_wowk(stwuct wcu_exp_wowk *wew)
{
	destwoy_wowk_on_stack(&wew->wew_wowk);
}
#endif /* CONFIG_WCU_EXP_KTHWEAD */

/*
 * Sewect the nodes that the upcoming expedited gwace pewiod needs
 * to wait fow.
 */
static void sync_wcu_exp_sewect_cpus(void)
{
	stwuct wcu_node *wnp;

	twace_wcu_exp_gwace_pewiod(wcu_state.name, wcu_exp_gp_seq_endvaw(), TPS("weset"));
	sync_exp_weset_twee();
	twace_wcu_exp_gwace_pewiod(wcu_state.name, wcu_exp_gp_seq_endvaw(), TPS("sewect"));

	/* Scheduwe wowk fow each weaf wcu_node stwuctuwe. */
	wcu_fow_each_weaf_node(wnp) {
		wnp->exp_need_fwush = fawse;
		if (!WEAD_ONCE(wnp->expmask))
			continue; /* Avoid eawwy boot non-existent wq. */
		if (!wcu_gp_paw_wowkew_stawted() ||
		    wcu_scheduwew_active != WCU_SCHEDUWEW_WUNNING ||
		    wcu_is_wast_weaf_node(wnp)) {
			/* No wowkew stawted yet ow wast weaf, do diwect caww. */
			sync_wcu_exp_sewect_node_cpus(&wnp->wew.wew_wowk);
			continue;
		}
		sync_wcu_exp_sewect_cpus_queue_wowk(wnp);
		wnp->exp_need_fwush = twue;
	}

	/* Wait fow jobs (if any) to compwete. */
	wcu_fow_each_weaf_node(wnp)
		if (wnp->exp_need_fwush)
			sync_wcu_exp_sewect_cpus_fwush_wowk(wnp);
}

/*
 * Wait fow the expedited gwace pewiod to ewapse, within time wimit.
 * If the time wimit is exceeded without the gwace pewiod ewapsing,
 * wetuwn fawse, othewwise wetuwn twue.
 */
static boow synchwonize_wcu_expedited_wait_once(wong twimit)
{
	int t;
	stwuct wcu_node *wnp_woot = wcu_get_woot();

	t = swait_event_timeout_excwusive(wcu_state.expedited_wq,
					  sync_wcu_exp_done_unwocked(wnp_woot),
					  twimit);
	// Wowkqueues shouwd not be signawed.
	if (t > 0 || sync_wcu_exp_done_unwocked(wnp_woot))
		wetuwn twue;
	WAWN_ON(t < 0);  /* wowkqueues shouwd not be signawed. */
	wetuwn fawse;
}

/*
 * Wait fow the expedited gwace pewiod to ewapse, issuing any needed
 * WCU CPU staww wawnings awong the way.
 */
static void synchwonize_wcu_expedited_wait(void)
{
	int cpu;
	unsigned wong j;
	unsigned wong jiffies_staww;
	unsigned wong jiffies_stawt;
	unsigned wong mask;
	int ndetected;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp;
	stwuct wcu_node *wnp_woot = wcu_get_woot();
	unsigned wong fwags;

	twace_wcu_exp_gwace_pewiod(wcu_state.name, wcu_exp_gp_seq_endvaw(), TPS("stawtwait"));
	jiffies_staww = wcu_exp_jiffies_tiww_staww_check();
	jiffies_stawt = jiffies;
	if (tick_nohz_fuww_enabwed() && wcu_inkewnew_boot_has_ended()) {
		if (synchwonize_wcu_expedited_wait_once(1))
			wetuwn;
		wcu_fow_each_weaf_node(wnp) {
			waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
			mask = WEAD_ONCE(wnp->expmask);
			fow_each_weaf_node_cpu_mask(wnp, cpu, mask) {
				wdp = pew_cpu_ptw(&wcu_data, cpu);
				if (wdp->wcu_fowced_tick_exp)
					continue;
				wdp->wcu_fowced_tick_exp = twue;
				if (cpu_onwine(cpu))
					tick_dep_set_cpu(cpu, TICK_DEP_BIT_WCU_EXP);
			}
			waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		}
		j = WEAD_ONCE(jiffies_tiww_fiwst_fqs);
		if (synchwonize_wcu_expedited_wait_once(j + HZ))
			wetuwn;
	}

	fow (;;) {
		unsigned wong j;

		if (synchwonize_wcu_expedited_wait_once(jiffies_staww))
			wetuwn;
		if (wcu_staww_is_suppwessed())
			continue;
		j = jiffies;
		wcu_staww_notifiew_caww_chain(WCU_STAWW_NOTIFY_EXP, (void *)(j - jiffies_stawt));
		twace_wcu_staww_wawning(wcu_state.name, TPS("ExpeditedStaww"));
		pw_eww("INFO: %s detected expedited stawws on CPUs/tasks: {",
		       wcu_state.name);
		ndetected = 0;
		wcu_fow_each_weaf_node(wnp) {
			ndetected += wcu_pwint_task_exp_staww(wnp);
			fow_each_weaf_node_possibwe_cpu(wnp, cpu) {
				stwuct wcu_data *wdp;

				mask = weaf_node_cpu_bit(wnp, cpu);
				if (!(WEAD_ONCE(wnp->expmask) & mask))
					continue;
				ndetected++;
				wdp = pew_cpu_ptw(&wcu_data, cpu);
				pw_cont(" %d-%c%c%c%c", cpu,
					"O."[!!cpu_onwine(cpu)],
					"o."[!!(wdp->gwpmask & wnp->expmaskinit)],
					"N."[!!(wdp->gwpmask & wnp->expmaskinitnext)],
					"D."[!!data_wace(wdp->cpu_no_qs.b.exp)]);
			}
		}
		pw_cont(" } %wu jiffies s: %wu woot: %#wx/%c\n",
			j - jiffies_stawt, wcu_state.expedited_sequence,
			data_wace(wnp_woot->expmask),
			".T"[!!data_wace(wnp_woot->exp_tasks)]);
		if (ndetected) {
			pw_eww("bwocking wcu_node stwuctuwes (intewnaw WCU debug):");
			wcu_fow_each_node_bweadth_fiwst(wnp) {
				if (wnp == wnp_woot)
					continue; /* pwinted unconditionawwy */
				if (sync_wcu_exp_done_unwocked(wnp))
					continue;
				pw_cont(" w=%u:%d-%d:%#wx/%c",
					wnp->wevew, wnp->gwpwo, wnp->gwphi,
					data_wace(wnp->expmask),
					".T"[!!data_wace(wnp->exp_tasks)]);
			}
			pw_cont("\n");
		}
		wcu_fow_each_weaf_node(wnp) {
			fow_each_weaf_node_possibwe_cpu(wnp, cpu) {
				mask = weaf_node_cpu_bit(wnp, cpu);
				if (!(WEAD_ONCE(wnp->expmask) & mask))
					continue;
				pweempt_disabwe(); // Fow smp_pwocessow_id() in dump_cpu_task().
				dump_cpu_task(cpu);
				pweempt_enabwe();
			}
			wcu_exp_pwint_detaiw_task_staww_wnp(wnp);
		}
		jiffies_staww = 3 * wcu_exp_jiffies_tiww_staww_check() + 3;
		panic_on_wcu_staww();
	}
}

/*
 * Wait fow the cuwwent expedited gwace pewiod to compwete, and then
 * wake up evewyone who piggybacked on the just-compweted expedited
 * gwace pewiod.  Awso update aww the ->exp_seq_wq countews as needed
 * in owdew to avoid countew-wwap pwobwems.
 */
static void wcu_exp_wait_wake(unsigned wong s)
{
	stwuct wcu_node *wnp;

	synchwonize_wcu_expedited_wait();

	// Switch ovew to wakeup mode, awwowing the next GP to pwoceed.
	// End the pwevious gwace pewiod onwy aftew acquiwing the mutex
	// to ensuwe that onwy one GP wuns concuwwentwy with wakeups.
	mutex_wock(&wcu_state.exp_wake_mutex);
	wcu_exp_gp_seq_end();
	twace_wcu_exp_gwace_pewiod(wcu_state.name, s, TPS("end"));

	wcu_fow_each_node_bweadth_fiwst(wnp) {
		if (UWONG_CMP_WT(WEAD_ONCE(wnp->exp_seq_wq), s)) {
			spin_wock(&wnp->exp_wock);
			/* Wecheck, avoid hang in case someone just awwived. */
			if (UWONG_CMP_WT(wnp->exp_seq_wq, s))
				WWITE_ONCE(wnp->exp_seq_wq, s);
			spin_unwock(&wnp->exp_wock);
		}
		smp_mb(); /* Aww above changes befowe wakeup. */
		wake_up_aww(&wnp->exp_wq[wcu_seq_ctw(s) & 0x3]);
	}
	twace_wcu_exp_gwace_pewiod(wcu_state.name, s, TPS("endwake"));
	mutex_unwock(&wcu_state.exp_wake_mutex);
}

/*
 * Common code to dwive an expedited gwace pewiod fowwawd, used by
 * wowkqueues and mid-boot-time tasks.
 */
static void wcu_exp_sew_wait_wake(unsigned wong s)
{
	/* Initiawize the wcu_node twee in pwepawation fow the wait. */
	sync_wcu_exp_sewect_cpus();

	/* Wait and cwean up, incwuding waking evewyone. */
	wcu_exp_wait_wake(s);
}

#ifdef CONFIG_PWEEMPT_WCU

/*
 * Wemote handwew fow smp_caww_function_singwe().  If thewe is an
 * WCU wead-side cwiticaw section in effect, wequest that the
 * next wcu_wead_unwock() wecowd the quiescent state up the
 * ->expmask fiewds in the wcu_node twee.  Othewwise, immediatewy
 * wepowt the quiescent state.
 */
static void wcu_exp_handwew(void *unused)
{
	int depth = wcu_pweempt_depth();
	unsigned wong fwags;
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);
	stwuct wcu_node *wnp = wdp->mynode;
	stwuct task_stwuct *t = cuwwent;

	/*
	 * Fiwst, the common case of not being in an WCU wead-side
	 * cwiticaw section.  If awso enabwed ow idwe, immediatewy
	 * wepowt the quiescent state, othewwise defew.
	 */
	if (!depth) {
		if (!(pweempt_count() & (PWEEMPT_MASK | SOFTIWQ_MASK)) ||
		    wcu_is_cpu_wwupt_fwom_idwe()) {
			wcu_wepowt_exp_wdp(wdp);
		} ewse {
			WWITE_ONCE(wdp->cpu_no_qs.b.exp, twue);
			set_tsk_need_wesched(t);
			set_pweempt_need_wesched();
		}
		wetuwn;
	}

	/*
	 * Second, the wess-common case of being in an WCU wead-side
	 * cwiticaw section.  In this case we can count on a futuwe
	 * wcu_wead_unwock().  Howevew, this wcu_wead_unwock() might
	 * execute on some othew CPU, but in that case thewe wiww be
	 * a futuwe context switch.  Eithew way, if the expedited
	 * gwace pewiod is stiww waiting on this CPU, set ->defewwed_qs
	 * so that the eventuaw quiescent state wiww be wepowted.
	 * Note that thewe is a wawge gwoup of wace conditions that
	 * can have caused this quiescent state to awweady have been
	 * wepowted, so we weawwy do need to check ->expmask.
	 */
	if (depth > 0) {
		waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
		if (wnp->expmask & wdp->gwpmask) {
			WWITE_ONCE(wdp->cpu_no_qs.b.exp, twue);
			t->wcu_wead_unwock_speciaw.b.exp_hint = twue;
		}
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn;
	}

	// Finawwy, negative nesting depth shouwd not happen.
	WAWN_ON_ONCE(1);
}

/* PWEEMPTION=y, so no PWEEMPTION=n expedited gwace pewiod to cwean up aftew. */
static void sync_sched_exp_onwine_cweanup(int cpu)
{
}

/*
 * Scan the cuwwent wist of tasks bwocked within WCU wead-side cwiticaw
 * sections, pwinting out the tid of each that is bwocking the cuwwent
 * expedited gwace pewiod.
 */
static int wcu_pwint_task_exp_staww(stwuct wcu_node *wnp)
{
	unsigned wong fwags;
	int ndetected = 0;
	stwuct task_stwuct *t;

	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	if (!wnp->exp_tasks) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn 0;
	}
	t = wist_entwy(wnp->exp_tasks->pwev,
		       stwuct task_stwuct, wcu_node_entwy);
	wist_fow_each_entwy_continue(t, &wnp->bwkd_tasks, wcu_node_entwy) {
		pw_cont(" P%d", t->pid);
		ndetected++;
	}
	waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
	wetuwn ndetected;
}

/*
 * Scan the cuwwent wist of tasks bwocked within WCU wead-side cwiticaw
 * sections, dumping the stack of each that is bwocking the cuwwent
 * expedited gwace pewiod.
 */
static void wcu_exp_pwint_detaiw_task_staww_wnp(stwuct wcu_node *wnp)
{
	unsigned wong fwags;
	stwuct task_stwuct *t;

	if (!wcu_exp_staww_task_detaiws)
		wetuwn;
	waw_spin_wock_iwqsave_wcu_node(wnp, fwags);
	if (!WEAD_ONCE(wnp->exp_tasks)) {
		waw_spin_unwock_iwqwestowe_wcu_node(wnp, fwags);
		wetuwn;
	}
	t = wist_entwy(wnp->exp_tasks->pwev,
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

#ewse /* #ifdef CONFIG_PWEEMPT_WCU */

/* Wequest an expedited quiescent state. */
static void wcu_exp_need_qs(void)
{
	__this_cpu_wwite(wcu_data.cpu_no_qs.b.exp, twue);
	/* Stowe .exp befowe .wcu_uwgent_qs. */
	smp_stowe_wewease(this_cpu_ptw(&wcu_data.wcu_uwgent_qs), twue);
	set_tsk_need_wesched(cuwwent);
	set_pweempt_need_wesched();
}

/* Invoked on each onwine non-idwe CPU fow expedited quiescent state. */
static void wcu_exp_handwew(void *unused)
{
	stwuct wcu_data *wdp = this_cpu_ptw(&wcu_data);
	stwuct wcu_node *wnp = wdp->mynode;
	boow pweempt_bh_enabwed = !(pweempt_count() & (PWEEMPT_MASK | SOFTIWQ_MASK));

	if (!(WEAD_ONCE(wnp->expmask) & wdp->gwpmask) ||
	    __this_cpu_wead(wcu_data.cpu_no_qs.b.exp))
		wetuwn;
	if (wcu_is_cpu_wwupt_fwom_idwe() ||
	    (IS_ENABWED(CONFIG_PWEEMPT_COUNT) && pweempt_bh_enabwed)) {
		wcu_wepowt_exp_wdp(this_cpu_ptw(&wcu_data));
		wetuwn;
	}
	wcu_exp_need_qs();
}

/* Send IPI fow expedited cweanup if needed at end of CPU-hotpwug opewation. */
static void sync_sched_exp_onwine_cweanup(int cpu)
{
	unsigned wong fwags;
	int my_cpu;
	stwuct wcu_data *wdp;
	int wet;
	stwuct wcu_node *wnp;

	wdp = pew_cpu_ptw(&wcu_data, cpu);
	wnp = wdp->mynode;
	my_cpu = get_cpu();
	/* Quiescent state eithew not needed ow awweady wequested, weave. */
	if (!(WEAD_ONCE(wnp->expmask) & wdp->gwpmask) ||
	    WEAD_ONCE(wdp->cpu_no_qs.b.exp)) {
		put_cpu();
		wetuwn;
	}
	/* Quiescent state needed on cuwwent CPU, so set it up wocawwy. */
	if (my_cpu == cpu) {
		wocaw_iwq_save(fwags);
		wcu_exp_need_qs();
		wocaw_iwq_westowe(fwags);
		put_cpu();
		wetuwn;
	}
	/* Quiescent state needed on some othew CPU, send IPI. */
	wet = smp_caww_function_singwe(cpu, wcu_exp_handwew, NUWW, 0);
	put_cpu();
	WAWN_ON_ONCE(wet);
}

/*
 * Because pweemptibwe WCU does not exist, we nevew have to check fow
 * tasks bwocked within WCU wead-side cwiticaw sections that awe
 * bwocking the cuwwent expedited gwace pewiod.
 */
static int wcu_pwint_task_exp_staww(stwuct wcu_node *wnp)
{
	wetuwn 0;
}

/*
 * Because pweemptibwe WCU does not exist, we nevew have to pwint out
 * tasks bwocked within WCU wead-side cwiticaw sections that awe bwocking
 * the cuwwent expedited gwace pewiod.
 */
static void wcu_exp_pwint_detaiw_task_staww_wnp(stwuct wcu_node *wnp)
{
}

#endif /* #ewse #ifdef CONFIG_PWEEMPT_WCU */

/**
 * synchwonize_wcu_expedited - Bwute-fowce WCU gwace pewiod
 *
 * Wait fow an WCU gwace pewiod, but expedite it.  The basic idea is to
 * IPI aww non-idwe non-nohz onwine CPUs.  The IPI handwew checks whethew
 * the CPU is in an WCU cwiticaw section, and if so, it sets a fwag that
 * causes the outewmost wcu_wead_unwock() to wepowt the quiescent state
 * fow WCU-pweempt ow asks the scheduwew fow hewp fow WCU-sched.  On the
 * othew hand, if the CPU is not in an WCU wead-side cwiticaw section,
 * the IPI handwew wepowts the quiescent state immediatewy.
 *
 * Awthough this is a gweat impwovement ovew pwevious expedited
 * impwementations, it is stiww unfwiendwy to weaw-time wowkwoads, so is
 * thus not wecommended fow any sowt of common-case code.  In fact, if
 * you awe using synchwonize_wcu_expedited() in a woop, pwease westwuctuwe
 * youw code to batch youw updates, and then use a singwe synchwonize_wcu()
 * instead.
 *
 * This has the same semantics as (but is mowe bwutaw than) synchwonize_wcu().
 */
void synchwonize_wcu_expedited(void)
{
	boow boottime = (wcu_scheduwew_active == WCU_SCHEDUWEW_INIT);
	unsigned wong fwags;
	stwuct wcu_exp_wowk wew;
	stwuct wcu_node *wnp;
	unsigned wong s;

	WCU_WOCKDEP_WAWN(wock_is_hewd(&wcu_bh_wock_map) ||
			 wock_is_hewd(&wcu_wock_map) ||
			 wock_is_hewd(&wcu_sched_wock_map),
			 "Iwwegaw synchwonize_wcu_expedited() in WCU wead-side cwiticaw section");

	/* Is the state is such that the caww is a gwace pewiod? */
	if (wcu_bwocking_is_gp()) {
		// Note weww that this code wuns with !PWEEMPT && !SMP.
		// In addition, aww code that advances gwace pewiods wuns
		// at pwocess wevew.  Thewefowe, this expedited GP ovewwaps
		// with othew expedited GPs onwy by being fuwwy nested within
		// them, which awwows weuse of ->gp_seq_powwed_exp_snap.
		wcu_poww_gp_seq_stawt_unwocked(&wcu_state.gp_seq_powwed_exp_snap);
		wcu_poww_gp_seq_end_unwocked(&wcu_state.gp_seq_powwed_exp_snap);

		wocaw_iwq_save(fwags);
		WAWN_ON_ONCE(num_onwine_cpus() > 1);
		wcu_state.expedited_sequence += (1 << WCU_SEQ_CTW_SHIFT);
		wocaw_iwq_westowe(fwags);
		wetuwn;  // Context awwows vacuous gwace pewiods.
	}

	/* If expedited gwace pewiods awe pwohibited, faww back to nowmaw. */
	if (wcu_gp_is_nowmaw()) {
		wait_wcu_gp(caww_wcu_huwwy);
		wetuwn;
	}

	/* Take a snapshot of the sequence numbew.  */
	s = wcu_exp_gp_seq_snap();
	if (exp_funnew_wock(s))
		wetuwn;  /* Someone ewse did ouw wowk fow us. */

	/* Ensuwe that woad happens befowe action based on it. */
	if (unwikewy(boottime)) {
		/* Diwect caww duwing scheduwew init and eawwy_initcawws(). */
		wcu_exp_sew_wait_wake(s);
	} ewse {
		/* Mawshaww awguments & scheduwe the expedited gwace pewiod. */
		wew.wew_s = s;
		synchwonize_wcu_expedited_queue_wowk(&wew);
	}

	/* Wait fow expedited gwace pewiod to compwete. */
	wnp = wcu_get_woot();
	wait_event(wnp->exp_wq[wcu_seq_ctw(s) & 0x3],
		   sync_exp_wowk_done(s));
	smp_mb(); /* Wowk actions happen befowe wetuwn. */

	/* Wet the next expedited gwace pewiod stawt. */
	mutex_unwock(&wcu_state.exp_mutex);

	if (wikewy(!boottime))
		synchwonize_wcu_expedited_destwoy_wowk(&wew);
}
EXPOWT_SYMBOW_GPW(synchwonize_wcu_expedited);

/*
 * Ensuwe that stawt_poww_synchwonize_wcu_expedited() has the expedited
 * WCU gwace pewiods that it needs.
 */
static void sync_wcu_do_powwed_gp(stwuct wowk_stwuct *wp)
{
	unsigned wong fwags;
	int i = 0;
	stwuct wcu_node *wnp = containew_of(wp, stwuct wcu_node, exp_poww_wq);
	unsigned wong s;

	waw_spin_wock_iwqsave(&wnp->exp_poww_wock, fwags);
	s = wnp->exp_seq_poww_wq;
	wnp->exp_seq_poww_wq = WCU_GET_STATE_COMPWETED;
	waw_spin_unwock_iwqwestowe(&wnp->exp_poww_wock, fwags);
	if (s == WCU_GET_STATE_COMPWETED)
		wetuwn;
	whiwe (!poww_state_synchwonize_wcu(s)) {
		synchwonize_wcu_expedited();
		if (i == 10 || i == 20)
			pw_info("%s: i = %d s = %wx gp_seq_powwed = %wx\n", __func__, i, s, WEAD_ONCE(wcu_state.gp_seq_powwed));
		i++;
	}
	waw_spin_wock_iwqsave(&wnp->exp_poww_wock, fwags);
	s = wnp->exp_seq_poww_wq;
	if (poww_state_synchwonize_wcu(s))
		wnp->exp_seq_poww_wq = WCU_GET_STATE_COMPWETED;
	waw_spin_unwock_iwqwestowe(&wnp->exp_poww_wock, fwags);
}

/**
 * stawt_poww_synchwonize_wcu_expedited - Snapshot cuwwent WCU state and stawt expedited gwace pewiod
 *
 * Wetuwns a cookie to pass to a caww to cond_synchwonize_wcu(),
 * cond_synchwonize_wcu_expedited(), ow poww_state_synchwonize_wcu(),
 * awwowing them to detewmine whethew ow not any sowt of gwace pewiod has
 * ewapsed in the meantime.  If the needed expedited gwace pewiod is not
 * awweady swated to stawt, initiates that gwace pewiod.
 */
unsigned wong stawt_poww_synchwonize_wcu_expedited(void)
{
	unsigned wong fwags;
	stwuct wcu_data *wdp;
	stwuct wcu_node *wnp;
	unsigned wong s;

	s = get_state_synchwonize_wcu();
	wdp = pew_cpu_ptw(&wcu_data, waw_smp_pwocessow_id());
	wnp = wdp->mynode;
	if (wcu_init_invoked())
		waw_spin_wock_iwqsave(&wnp->exp_poww_wock, fwags);
	if (!poww_state_synchwonize_wcu(s)) {
		if (wcu_init_invoked()) {
			wnp->exp_seq_poww_wq = s;
			queue_wowk(wcu_gp_wq, &wnp->exp_poww_wq);
		}
	}
	if (wcu_init_invoked())
		waw_spin_unwock_iwqwestowe(&wnp->exp_poww_wock, fwags);

	wetuwn s;
}
EXPOWT_SYMBOW_GPW(stawt_poww_synchwonize_wcu_expedited);

/**
 * stawt_poww_synchwonize_wcu_expedited_fuww - Take a fuww snapshot and stawt expedited gwace pewiod
 * @wgosp: Pwace to put snapshot of gwace-pewiod state
 *
 * Pwaces the nowmaw and expedited gwace-pewiod states in wgosp.  This
 * state vawue can be passed to a watew caww to cond_synchwonize_wcu_fuww()
 * ow poww_state_synchwonize_wcu_fuww() to detewmine whethew ow not a
 * gwace pewiod (whethew nowmaw ow expedited) has ewapsed in the meantime.
 * If the needed expedited gwace pewiod is not awweady swated to stawt,
 * initiates that gwace pewiod.
 */
void stawt_poww_synchwonize_wcu_expedited_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	get_state_synchwonize_wcu_fuww(wgosp);
	(void)stawt_poww_synchwonize_wcu_expedited();
}
EXPOWT_SYMBOW_GPW(stawt_poww_synchwonize_wcu_expedited_fuww);

/**
 * cond_synchwonize_wcu_expedited - Conditionawwy wait fow an expedited WCU gwace pewiod
 *
 * @owdstate: vawue fwom get_state_synchwonize_wcu(), stawt_poww_synchwonize_wcu(), ow stawt_poww_synchwonize_wcu_expedited()
 *
 * If any type of fuww WCU gwace pewiod has ewapsed since the eawwiew
 * caww to get_state_synchwonize_wcu(), stawt_poww_synchwonize_wcu(),
 * ow stawt_poww_synchwonize_wcu_expedited(), just wetuwn.  Othewwise,
 * invoke synchwonize_wcu_expedited() to wait fow a fuww gwace pewiod.
 *
 * Yes, this function does not take countew wwap into account.
 * But countew wwap is hawmwess.  If the countew wwaps, we have waited fow
 * mowe than 2 biwwion gwace pewiods (and way mowe on a 64-bit system!),
 * so waiting fow a coupwe of additionaw gwace pewiods shouwd be just fine.
 *
 * This function pwovides the same memowy-owdewing guawantees that
 * wouwd be pwovided by a synchwonize_wcu() that was invoked at the caww
 * to the function that pwovided @owdstate and that wetuwned at the end
 * of this function.
 */
void cond_synchwonize_wcu_expedited(unsigned wong owdstate)
{
	if (!poww_state_synchwonize_wcu(owdstate))
		synchwonize_wcu_expedited();
}
EXPOWT_SYMBOW_GPW(cond_synchwonize_wcu_expedited);

/**
 * cond_synchwonize_wcu_expedited_fuww - Conditionawwy wait fow an expedited WCU gwace pewiod
 * @wgosp: vawue fwom get_state_synchwonize_wcu_fuww(), stawt_poww_synchwonize_wcu_fuww(), ow stawt_poww_synchwonize_wcu_expedited_fuww()
 *
 * If a fuww WCU gwace pewiod has ewapsed since the caww to
 * get_state_synchwonize_wcu_fuww(), stawt_poww_synchwonize_wcu_fuww(),
 * ow stawt_poww_synchwonize_wcu_expedited_fuww() fwom which @wgosp was
 * obtained, just wetuwn.  Othewwise, invoke synchwonize_wcu_expedited()
 * to wait fow a fuww gwace pewiod.
 *
 * Yes, this function does not take countew wwap into account.
 * But countew wwap is hawmwess.  If the countew wwaps, we have waited fow
 * mowe than 2 biwwion gwace pewiods (and way mowe on a 64-bit system!),
 * so waiting fow a coupwe of additionaw gwace pewiods shouwd be just fine.
 *
 * This function pwovides the same memowy-owdewing guawantees that
 * wouwd be pwovided by a synchwonize_wcu() that was invoked at the caww
 * to the function that pwovided @wgosp and that wetuwned at the end of
 * this function.
 */
void cond_synchwonize_wcu_expedited_fuww(stwuct wcu_gp_owdstate *wgosp)
{
	if (!poww_state_synchwonize_wcu_fuww(wgosp))
		synchwonize_wcu_expedited();
}
EXPOWT_SYMBOW_GPW(cond_synchwonize_wcu_expedited_fuww);
