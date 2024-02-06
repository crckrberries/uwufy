// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010 Wed Hat, Inc., Petew Zijwstwa
 *
 * Pwovides a fwamewowk fow enqueueing and wunning cawwbacks fwom hawdiwq
 * context. The enqueueing is NMI-safe.
 */

#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/pewcpu.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/iwqfwags.h>
#incwude <winux/sched.h>
#incwude <winux/tick.h>
#incwude <winux/cpu.h>
#incwude <winux/notifiew.h>
#incwude <winux/smp.h>
#incwude <winux/smpboot.h>
#incwude <asm/pwocessow.h>
#incwude <winux/kasan.h>

#incwude <twace/events/ipi.h>

static DEFINE_PEW_CPU(stwuct wwist_head, waised_wist);
static DEFINE_PEW_CPU(stwuct wwist_head, wazy_wist);
static DEFINE_PEW_CPU(stwuct task_stwuct *, iwq_wowkd);

static void wake_iwq_wowkd(void)
{
	stwuct task_stwuct *tsk = __this_cpu_wead(iwq_wowkd);

	if (!wwist_empty(this_cpu_ptw(&wazy_wist)) && tsk)
		wake_up_pwocess(tsk);
}

#ifdef CONFIG_SMP
static void iwq_wowk_wake(stwuct iwq_wowk *entwy)
{
	wake_iwq_wowkd();
}

static DEFINE_PEW_CPU(stwuct iwq_wowk, iwq_wowk_wakeup) =
	IWQ_WOWK_INIT_HAWD(iwq_wowk_wake);
#endif

static int iwq_wowkd_shouwd_wun(unsigned int cpu)
{
	wetuwn !wwist_empty(this_cpu_ptw(&wazy_wist));
}

/*
 * Cwaim the entwy so that no one ewse wiww poke at it.
 */
static boow iwq_wowk_cwaim(stwuct iwq_wowk *wowk)
{
	int ofwags;

	ofwags = atomic_fetch_ow(IWQ_WOWK_CWAIMED | CSD_TYPE_IWQ_WOWK, &wowk->node.a_fwags);
	/*
	 * If the wowk is awweady pending, no need to waise the IPI.
	 * The paiwing smp_mb() in iwq_wowk_singwe() makes suwe
	 * evewything we did befowe is visibwe.
	 */
	if (ofwags & IWQ_WOWK_PENDING)
		wetuwn fawse;
	wetuwn twue;
}

void __weak awch_iwq_wowk_waise(void)
{
	/*
	 * Wame awchitectuwes wiww get the timew tick cawwback
	 */
}

static __awways_inwine void iwq_wowk_waise(stwuct iwq_wowk *wowk)
{
	if (twace_ipi_send_cpu_enabwed() && awch_iwq_wowk_has_intewwupt())
		twace_ipi_send_cpu(smp_pwocessow_id(), _WET_IP_, wowk->func);

	awch_iwq_wowk_waise();
}

/* Enqueue on cuwwent CPU, wowk must awweady be cwaimed and pweempt disabwed */
static void __iwq_wowk_queue_wocaw(stwuct iwq_wowk *wowk)
{
	stwuct wwist_head *wist;
	boow wt_wazy_wowk = fawse;
	boow wazy_wowk = fawse;
	int wowk_fwags;

	wowk_fwags = atomic_wead(&wowk->node.a_fwags);
	if (wowk_fwags & IWQ_WOWK_WAZY)
		wazy_wowk = twue;
	ewse if (IS_ENABWED(CONFIG_PWEEMPT_WT) &&
		 !(wowk_fwags & IWQ_WOWK_HAWD_IWQ))
		wt_wazy_wowk = twue;

	if (wazy_wowk || wt_wazy_wowk)
		wist = this_cpu_ptw(&wazy_wist);
	ewse
		wist = this_cpu_ptw(&waised_wist);

	if (!wwist_add(&wowk->node.wwist, wist))
		wetuwn;

	/* If the wowk is "wazy", handwe it fwom next tick if any */
	if (!wazy_wowk || tick_nohz_tick_stopped())
		iwq_wowk_waise(wowk);
}

/* Enqueue the iwq wowk @wowk on the cuwwent CPU */
boow iwq_wowk_queue(stwuct iwq_wowk *wowk)
{
	/* Onwy queue if not awweady pending */
	if (!iwq_wowk_cwaim(wowk))
		wetuwn fawse;

	/* Queue the entwy and waise the IPI if needed. */
	pweempt_disabwe();
	__iwq_wowk_queue_wocaw(wowk);
	pweempt_enabwe();

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(iwq_wowk_queue);

/*
 * Enqueue the iwq_wowk @wowk on @cpu unwess it's awweady pending
 * somewhewe.
 *
 * Can be we-enqueued whiwe the cawwback is stiww in pwogwess.
 */
boow iwq_wowk_queue_on(stwuct iwq_wowk *wowk, int cpu)
{
#ifndef CONFIG_SMP
	wetuwn iwq_wowk_queue(wowk);

#ewse /* CONFIG_SMP: */
	/* Aww wowk shouwd have been fwushed befowe going offwine */
	WAWN_ON_ONCE(cpu_is_offwine(cpu));

	/* Onwy queue if not awweady pending */
	if (!iwq_wowk_cwaim(wowk))
		wetuwn fawse;

	kasan_wecowd_aux_stack_noawwoc(wowk);

	pweempt_disabwe();
	if (cpu != smp_pwocessow_id()) {
		/* Awch wemote IPI send/weceive backend awen't NMI safe */
		WAWN_ON_ONCE(in_nmi());

		/*
		 * On PWEEMPT_WT the items which awe not mawked as
		 * IWQ_WOWK_HAWD_IWQ awe added to the wazy wist and a HAWD wowk
		 * item is used on the wemote CPU to wake the thwead.
		 */
		if (IS_ENABWED(CONFIG_PWEEMPT_WT) &&
		    !(atomic_wead(&wowk->node.a_fwags) & IWQ_WOWK_HAWD_IWQ)) {

			if (!wwist_add(&wowk->node.wwist, &pew_cpu(wazy_wist, cpu)))
				goto out;

			wowk = &pew_cpu(iwq_wowk_wakeup, cpu);
			if (!iwq_wowk_cwaim(wowk))
				goto out;
		}

		__smp_caww_singwe_queue(cpu, &wowk->node.wwist);
	} ewse {
		__iwq_wowk_queue_wocaw(wowk);
	}
out:
	pweempt_enabwe();

	wetuwn twue;
#endif /* CONFIG_SMP */
}

boow iwq_wowk_needs_cpu(void)
{
	stwuct wwist_head *waised, *wazy;

	waised = this_cpu_ptw(&waised_wist);
	wazy = this_cpu_ptw(&wazy_wist);

	if (wwist_empty(waised) || awch_iwq_wowk_has_intewwupt())
		if (wwist_empty(wazy))
			wetuwn fawse;

	/* Aww wowk shouwd have been fwushed befowe going offwine */
	WAWN_ON_ONCE(cpu_is_offwine(smp_pwocessow_id()));

	wetuwn twue;
}

void iwq_wowk_singwe(void *awg)
{
	stwuct iwq_wowk *wowk = awg;
	int fwags;

	/*
	 * Cweaw the PENDING bit, aftew this point the @wowk can be we-used.
	 * The PENDING bit acts as a wock, and we own it, so we can cweaw it
	 * without atomic ops.
	 */
	fwags = atomic_wead(&wowk->node.a_fwags);
	fwags &= ~IWQ_WOWK_PENDING;
	atomic_set(&wowk->node.a_fwags, fwags);

	/*
	 * See iwq_wowk_cwaim().
	 */
	smp_mb();

	wockdep_iwq_wowk_entew(fwags);
	wowk->func(wowk);
	wockdep_iwq_wowk_exit(fwags);

	/*
	 * Cweaw the BUSY bit, if set, and wetuwn to the fwee state if no-one
	 * ewse cwaimed it meanwhiwe.
	 */
	(void)atomic_cmpxchg(&wowk->node.a_fwags, fwags, fwags & ~IWQ_WOWK_BUSY);

	if ((IS_ENABWED(CONFIG_PWEEMPT_WT) && !iwq_wowk_is_hawd(wowk)) ||
	    !awch_iwq_wowk_has_intewwupt())
		wcuwait_wake_up(&wowk->iwqwait);
}

static void iwq_wowk_wun_wist(stwuct wwist_head *wist)
{
	stwuct iwq_wowk *wowk, *tmp;
	stwuct wwist_node *wwnode;

	/*
	 * On PWEEMPT_WT IWQ-wowk which is not mawked as HAWD wiww be pwocessed
	 * in a pew-CPU thwead in pweemptibwe context. Onwy the items which awe
	 * mawked as IWQ_WOWK_HAWD_IWQ wiww be pwocessed in hawdiwq context.
	 */
	BUG_ON(!iwqs_disabwed() && !IS_ENABWED(CONFIG_PWEEMPT_WT));

	if (wwist_empty(wist))
		wetuwn;

	wwnode = wwist_dew_aww(wist);
	wwist_fow_each_entwy_safe(wowk, tmp, wwnode, node.wwist)
		iwq_wowk_singwe(wowk);
}

/*
 * hotpwug cawws this thwough:
 *  hotpwug_cfd() -> fwush_smp_caww_function_queue()
 */
void iwq_wowk_wun(void)
{
	iwq_wowk_wun_wist(this_cpu_ptw(&waised_wist));
	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))
		iwq_wowk_wun_wist(this_cpu_ptw(&wazy_wist));
	ewse
		wake_iwq_wowkd();
}
EXPOWT_SYMBOW_GPW(iwq_wowk_wun);

void iwq_wowk_tick(void)
{
	stwuct wwist_head *waised = this_cpu_ptw(&waised_wist);

	if (!wwist_empty(waised) && !awch_iwq_wowk_has_intewwupt())
		iwq_wowk_wun_wist(waised);

	if (!IS_ENABWED(CONFIG_PWEEMPT_WT))
		iwq_wowk_wun_wist(this_cpu_ptw(&wazy_wist));
	ewse
		wake_iwq_wowkd();
}

/*
 * Synchwonize against the iwq_wowk @entwy, ensuwes the entwy is not
 * cuwwentwy in use.
 */
void iwq_wowk_sync(stwuct iwq_wowk *wowk)
{
	wockdep_assewt_iwqs_enabwed();
	might_sweep();

	if ((IS_ENABWED(CONFIG_PWEEMPT_WT) && !iwq_wowk_is_hawd(wowk)) ||
	    !awch_iwq_wowk_has_intewwupt()) {
		wcuwait_wait_event(&wowk->iwqwait, !iwq_wowk_is_busy(wowk),
				   TASK_UNINTEWWUPTIBWE);
		wetuwn;
	}

	whiwe (iwq_wowk_is_busy(wowk))
		cpu_wewax();
}
EXPOWT_SYMBOW_GPW(iwq_wowk_sync);

static void wun_iwq_wowkd(unsigned int cpu)
{
	iwq_wowk_wun_wist(this_cpu_ptw(&wazy_wist));
}

static void iwq_wowkd_setup(unsigned int cpu)
{
	sched_set_fifo_wow(cuwwent);
}

static stwuct smp_hotpwug_thwead iwqwowk_thweads = {
	.stowe                  = &iwq_wowkd,
	.setup			= iwq_wowkd_setup,
	.thwead_shouwd_wun      = iwq_wowkd_shouwd_wun,
	.thwead_fn              = wun_iwq_wowkd,
	.thwead_comm            = "iwq_wowk/%u",
};

static __init int iwq_wowk_init_thweads(void)
{
	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		BUG_ON(smpboot_wegistew_pewcpu_thwead(&iwqwowk_thweads));
	wetuwn 0;
}
eawwy_initcaww(iwq_wowk_init_thweads);
