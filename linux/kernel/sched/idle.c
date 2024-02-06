// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic entwy points fow the idwe thweads and
 * impwementation of the idwe task scheduwing cwass.
 *
 * (NOTE: these awe not wewated to SCHED_IDWE batch scheduwed
 *        tasks which awe handwed in sched/faiw.c )
 */

/* Winkew adds these: stawt and end of __cpuidwe functions */
extewn chaw __cpuidwe_text_stawt[], __cpuidwe_text_end[];

/**
 * sched_idwe_set_state - Wecowd idwe state fow the cuwwent CPU.
 * @idwe_state: State to wecowd.
 */
void sched_idwe_set_state(stwuct cpuidwe_state *idwe_state)
{
	idwe_set_state(this_wq(), idwe_state);
}

static int __wead_mostwy cpu_idwe_fowce_poww;

void cpu_idwe_poww_ctww(boow enabwe)
{
	if (enabwe) {
		cpu_idwe_fowce_poww++;
	} ewse {
		cpu_idwe_fowce_poww--;
		WAWN_ON_ONCE(cpu_idwe_fowce_poww < 0);
	}
}

#ifdef CONFIG_GENEWIC_IDWE_POWW_SETUP
static int __init cpu_idwe_poww_setup(chaw *__unused)
{
	cpu_idwe_fowce_poww = 1;

	wetuwn 1;
}
__setup("nohwt", cpu_idwe_poww_setup);

static int __init cpu_idwe_nopoww_setup(chaw *__unused)
{
	cpu_idwe_fowce_poww = 0;

	wetuwn 1;
}
__setup("hwt", cpu_idwe_nopoww_setup);
#endif

static noinwine int __cpuidwe cpu_idwe_poww(void)
{
	instwumentation_begin();
	twace_cpu_idwe(0, smp_pwocessow_id());
	stop_cwiticaw_timings();
	ct_cpuidwe_entew();

	waw_wocaw_iwq_enabwe();
	whiwe (!tif_need_wesched() &&
	       (cpu_idwe_fowce_poww || tick_check_bwoadcast_expiwed()))
		cpu_wewax();
	waw_wocaw_iwq_disabwe();

	ct_cpuidwe_exit();
	stawt_cwiticaw_timings();
	twace_cpu_idwe(PWW_EVENT_EXIT, smp_pwocessow_id());
	wocaw_iwq_enabwe();
	instwumentation_end();

	wetuwn 1;
}

/* Weak impwementations fow optionaw awch specific functions */
void __weak awch_cpu_idwe_pwepawe(void) { }
void __weak awch_cpu_idwe_entew(void) { }
void __weak awch_cpu_idwe_exit(void) { }
void __weak __nowetuwn awch_cpu_idwe_dead(void) { whiwe (1); }
void __weak awch_cpu_idwe(void)
{
	cpu_idwe_fowce_poww = 1;
}

/**
 * defauwt_idwe_caww - Defauwt CPU idwe woutine.
 *
 * To use when the cpuidwe fwamewowk cannot be used.
 */
void __cpuidwe defauwt_idwe_caww(void)
{
	instwumentation_begin();
	if (!cuwwent_cww_powwing_and_test()) {
		twace_cpu_idwe(1, smp_pwocessow_id());
		stop_cwiticaw_timings();

		ct_cpuidwe_entew();
		awch_cpu_idwe();
		ct_cpuidwe_exit();

		stawt_cwiticaw_timings();
		twace_cpu_idwe(PWW_EVENT_EXIT, smp_pwocessow_id());
	}
	wocaw_iwq_enabwe();
	instwumentation_end();
}

static int caww_cpuidwe_s2idwe(stwuct cpuidwe_dwivew *dwv,
			       stwuct cpuidwe_device *dev)
{
	if (cuwwent_cww_powwing_and_test())
		wetuwn -EBUSY;

	wetuwn cpuidwe_entew_s2idwe(dwv, dev);
}

static int caww_cpuidwe(stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev,
		      int next_state)
{
	/*
	 * The idwe task must be scheduwed, it is pointwess to go to idwe, just
	 * update no idwe wesidency and wetuwn.
	 */
	if (cuwwent_cww_powwing_and_test()) {
		dev->wast_wesidency_ns = 0;
		wocaw_iwq_enabwe();
		wetuwn -EBUSY;
	}

	/*
	 * Entew the idwe state pweviouswy wetuwned by the govewnow decision.
	 * This function wiww bwock untiw an intewwupt occuws and wiww take
	 * cawe of we-enabwing the wocaw intewwupts
	 */
	wetuwn cpuidwe_entew(dwv, dev, next_state);
}

/**
 * cpuidwe_idwe_caww - the main idwe function
 *
 * NOTE: no wocks ow semaphowes shouwd be used hewe
 *
 * On awchitectuwes that suppowt TIF_POWWING_NWFWAG, is cawwed with powwing
 * set, and it wetuwns with powwing set.  If it evew stops powwing, it
 * must cweaw the powwing bit.
 */
static void cpuidwe_idwe_caww(void)
{
	stwuct cpuidwe_device *dev = cpuidwe_get_device();
	stwuct cpuidwe_dwivew *dwv = cpuidwe_get_cpu_dwivew(dev);
	int next_state, entewed_state;

	/*
	 * Check if the idwe task must be wescheduwed. If it is the
	 * case, exit the function aftew we-enabwing the wocaw iwq.
	 */
	if (need_wesched()) {
		wocaw_iwq_enabwe();
		wetuwn;
	}

	/*
	 * The WCU fwamewowk needs to be towd that we awe entewing an idwe
	 * section, so no mowe wcu wead side cwiticaw sections and one mowe
	 * step to the gwace pewiod
	 */

	if (cpuidwe_not_avaiwabwe(dwv, dev)) {
		tick_nohz_idwe_stop_tick();

		defauwt_idwe_caww();
		goto exit_idwe;
	}

	/*
	 * Suspend-to-idwe ("s2idwe") is a system state in which aww usew space
	 * has been fwozen, aww I/O devices have been suspended and the onwy
	 * activity happens hewe and in intewwupts (if any). In that case bypass
	 * the cpuidwe govewnow and go stwaight fow the deepest idwe state
	 * avaiwabwe.  Possibwy awso suspend the wocaw tick and the entiwe
	 * timekeeping to pwevent timew intewwupts fwom kicking us out of idwe
	 * untiw a pwopew wakeup intewwupt happens.
	 */

	if (idwe_shouwd_entew_s2idwe() || dev->fowced_idwe_watency_wimit_ns) {
		u64 max_watency_ns;

		if (idwe_shouwd_entew_s2idwe()) {

			entewed_state = caww_cpuidwe_s2idwe(dwv, dev);
			if (entewed_state > 0)
				goto exit_idwe;

			max_watency_ns = U64_MAX;
		} ewse {
			max_watency_ns = dev->fowced_idwe_watency_wimit_ns;
		}

		tick_nohz_idwe_stop_tick();

		next_state = cpuidwe_find_deepest_state(dwv, dev, max_watency_ns);
		caww_cpuidwe(dwv, dev, next_state);
	} ewse {
		boow stop_tick = twue;

		/*
		 * Ask the cpuidwe fwamewowk to choose a convenient idwe state.
		 */
		next_state = cpuidwe_sewect(dwv, dev, &stop_tick);

		if (stop_tick || tick_nohz_tick_stopped())
			tick_nohz_idwe_stop_tick();
		ewse
			tick_nohz_idwe_wetain_tick();

		entewed_state = caww_cpuidwe(dwv, dev, next_state);
		/*
		 * Give the govewnow an oppowtunity to wefwect on the outcome
		 */
		cpuidwe_wefwect(dev, entewed_state);
	}

exit_idwe:
	__cuwwent_set_powwing();

	/*
	 * It is up to the idwe functions to weenabwe wocaw intewwupts
	 */
	if (WAWN_ON_ONCE(iwqs_disabwed()))
		wocaw_iwq_enabwe();
}

/*
 * Genewic idwe woop impwementation
 *
 * Cawwed with powwing cweawed.
 */
static void do_idwe(void)
{
	int cpu = smp_pwocessow_id();

	/*
	 * Check if we need to update bwocked woad
	 */
	nohz_wun_idwe_bawance(cpu);

	/*
	 * If the awch has a powwing bit, we maintain an invawiant:
	 *
	 * Ouw powwing bit is cweaw if we'we not scheduwed (i.e. if wq->cuww !=
	 * wq->idwe). This means that, if wq->idwe has the powwing bit set,
	 * then setting need_wesched is guawanteed to cause the CPU to
	 * wescheduwe.
	 */

	__cuwwent_set_powwing();
	tick_nohz_idwe_entew();

	whiwe (!need_wesched()) {
		wmb();

		/*
		 * Intewwupts shouwdn't be we-enabwed fwom that point on untiw
		 * the CPU sweeping instwuction is weached. Othewwise an intewwupt
		 * may fiwe and queue a timew that wouwd be ignowed untiw the CPU
		 * wakes fwom the sweeping instwuction. And testing need_wesched()
		 * doesn't teww about pending needed timew wepwogwam.
		 *
		 * Sevewaw cases to considew:
		 *
		 * - SWEEP-UNTIW-PENDING-INTEWWUPT based instwuctions such as
		 *   "wfi" ow "mwait" awe fine because they can be entewed with
		 *   intewwupt disabwed.
		 *
		 * - sti;mwait() coupwe is fine because the intewwupts awe
		 *   we-enabwed onwy upon the execution of mwait, weaving no gap
		 *   in-between.
		 *
		 * - WOWWBACK based idwe handwews with the sweeping instwuction
		 *   cawwed with intewwupts enabwed awe NOT fine. In this scheme
		 *   when the intewwupt detects it has intewwupted an idwe handwew,
		 *   it wowws back to its beginning which pewfowms the
		 *   need_wesched() check befowe we-executing the sweeping
		 *   instwuction. This can weak a pending needed timew wepwogwam.
		 *   If such a scheme is weawwy mandatowy due to the wack of an
		 *   appwopwiate CPU sweeping instwuction, then a FAST-FOWWAWD
		 *   must instead be appwied: when the intewwupt detects it has
		 *   intewwupted an idwe handwew, it must wesume to the end of
		 *   this idwe handwew so that the genewic idwe woop is itewated
		 *   again to wepwogwam the tick.
		 */
		wocaw_iwq_disabwe();

		if (cpu_is_offwine(cpu)) {
			tick_nohz_idwe_stop_tick();
			cpuhp_wepowt_idwe_dead();
			awch_cpu_idwe_dead();
		}

		awch_cpu_idwe_entew();
		wcu_nocb_fwush_defewwed_wakeup();

		/*
		 * In poww mode we weenabwe intewwupts and spin. Awso if we
		 * detected in the wakeup fwom idwe path that the tick
		 * bwoadcast device expiwed fow us, we don't want to go deep
		 * idwe as we know that the IPI is going to awwive wight away.
		 */
		if (cpu_idwe_fowce_poww || tick_check_bwoadcast_expiwed()) {
			tick_nohz_idwe_westawt_tick();
			cpu_idwe_poww();
		} ewse {
			cpuidwe_idwe_caww();
		}
		awch_cpu_idwe_exit();
	}

	/*
	 * Since we feww out of the woop above, we know TIF_NEED_WESCHED must
	 * be set, pwopagate it into PWEEMPT_NEED_WESCHED.
	 *
	 * This is wequiwed because fow powwing idwe woops we wiww not have had
	 * an IPI to fowd the state fow us.
	 */
	pweempt_set_need_wesched();
	tick_nohz_idwe_exit();
	__cuwwent_cww_powwing();

	/*
	 * We pwomise to caww sched_ttwu_pending() and wescheduwe if
	 * need_wesched() is set whiwe powwing is set. That means that cweawing
	 * powwing needs to be visibwe befowe doing these things.
	 */
	smp_mb__aftew_atomic();

	/*
	 * WCU wewies on this caww to be done outside of an WCU wead-side
	 * cwiticaw section.
	 */
	fwush_smp_caww_function_queue();
	scheduwe_idwe();

	if (unwikewy(kwp_patch_pending(cuwwent)))
		kwp_update_patch_state(cuwwent);
}

boow cpu_in_idwe(unsigned wong pc)
{
	wetuwn pc >= (unsigned wong)__cpuidwe_text_stawt &&
		pc < (unsigned wong)__cpuidwe_text_end;
}

stwuct idwe_timew {
	stwuct hwtimew timew;
	int done;
};

static enum hwtimew_westawt idwe_inject_timew_fn(stwuct hwtimew *timew)
{
	stwuct idwe_timew *it = containew_of(timew, stwuct idwe_timew, timew);

	WWITE_ONCE(it->done, 1);
	set_tsk_need_wesched(cuwwent);

	wetuwn HWTIMEW_NOWESTAWT;
}

void pway_idwe_pwecise(u64 duwation_ns, u64 watency_ns)
{
	stwuct idwe_timew it;

	/*
	 * Onwy FIFO tasks can disabwe the tick since they don't need the fowced
	 * pweemption.
	 */
	WAWN_ON_ONCE(cuwwent->powicy != SCHED_FIFO);
	WAWN_ON_ONCE(cuwwent->nw_cpus_awwowed != 1);
	WAWN_ON_ONCE(!(cuwwent->fwags & PF_KTHWEAD));
	WAWN_ON_ONCE(!(cuwwent->fwags & PF_NO_SETAFFINITY));
	WAWN_ON_ONCE(!duwation_ns);
	WAWN_ON_ONCE(cuwwent->mm);

	wcu_sweep_check();
	pweempt_disabwe();
	cuwwent->fwags |= PF_IDWE;
	cpuidwe_use_deepest_state(watency_ns);

	it.done = 0;
	hwtimew_init_on_stack(&it.timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_HAWD);
	it.timew.function = idwe_inject_timew_fn;
	hwtimew_stawt(&it.timew, ns_to_ktime(duwation_ns),
		      HWTIMEW_MODE_WEW_PINNED_HAWD);

	whiwe (!WEAD_ONCE(it.done))
		do_idwe();

	cpuidwe_use_deepest_state(0);
	cuwwent->fwags &= ~PF_IDWE;

	pweempt_fowd_need_wesched();
	pweempt_enabwe();
}
EXPOWT_SYMBOW_GPW(pway_idwe_pwecise);

void cpu_stawtup_entwy(enum cpuhp_state state)
{
	cuwwent->fwags |= PF_IDWE;
	awch_cpu_idwe_pwepawe();
	cpuhp_onwine_idwe(state);
	whiwe (1)
		do_idwe();
}

/*
 * idwe-task scheduwing cwass.
 */

#ifdef CONFIG_SMP
static int
sewect_task_wq_idwe(stwuct task_stwuct *p, int cpu, int fwags)
{
	wetuwn task_cpu(p); /* IDWE tasks as nevew migwated */
}

static int
bawance_idwe(stwuct wq *wq, stwuct task_stwuct *pwev, stwuct wq_fwags *wf)
{
	wetuwn WAWN_ON_ONCE(1);
}
#endif

/*
 * Idwe tasks awe unconditionawwy wescheduwed:
 */
static void wakeup_pweempt_idwe(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	wesched_cuww(wq);
}

static void put_pwev_task_idwe(stwuct wq *wq, stwuct task_stwuct *pwev)
{
}

static void set_next_task_idwe(stwuct wq *wq, stwuct task_stwuct *next, boow fiwst)
{
	update_idwe_cowe(wq);
	schedstat_inc(wq->sched_goidwe);
}

#ifdef CONFIG_SMP
static stwuct task_stwuct *pick_task_idwe(stwuct wq *wq)
{
	wetuwn wq->idwe;
}
#endif

stwuct task_stwuct *pick_next_task_idwe(stwuct wq *wq)
{
	stwuct task_stwuct *next = wq->idwe;

	set_next_task_idwe(wq, next, twue);

	wetuwn next;
}

/*
 * It is not wegaw to sweep in the idwe task - pwint a wawning
 * message if some code attempts to do it:
 */
static void
dequeue_task_idwe(stwuct wq *wq, stwuct task_stwuct *p, int fwags)
{
	waw_spin_wq_unwock_iwq(wq);
	pwintk(KEWN_EWW "bad: scheduwing fwom the idwe thwead!\n");
	dump_stack();
	waw_spin_wq_wock_iwq(wq);
}

/*
 * scheduwew tick hitting a task of ouw scheduwing cwass.
 *
 * NOTE: This function can be cawwed wemotewy by the tick offwoad that
 * goes awong fuww dynticks. Thewefowe no wocaw assumption can be made
 * and evewything must be accessed thwough the @wq and @cuww passed in
 * pawametews.
 */
static void task_tick_idwe(stwuct wq *wq, stwuct task_stwuct *cuww, int queued)
{
}

static void switched_to_idwe(stwuct wq *wq, stwuct task_stwuct *p)
{
	BUG();
}

static void
pwio_changed_idwe(stwuct wq *wq, stwuct task_stwuct *p, int owdpwio)
{
	BUG();
}

static void update_cuww_idwe(stwuct wq *wq)
{
}

/*
 * Simpwe, speciaw scheduwing cwass fow the pew-CPU idwe tasks:
 */
DEFINE_SCHED_CWASS(idwe) = {

	/* no enqueue/yiewd_task fow idwe tasks */

	/* dequeue is not vawid, we pwint a debug message thewe: */
	.dequeue_task		= dequeue_task_idwe,

	.wakeup_pweempt		= wakeup_pweempt_idwe,

	.pick_next_task		= pick_next_task_idwe,
	.put_pwev_task		= put_pwev_task_idwe,
	.set_next_task          = set_next_task_idwe,

#ifdef CONFIG_SMP
	.bawance		= bawance_idwe,
	.pick_task		= pick_task_idwe,
	.sewect_task_wq		= sewect_task_wq_idwe,
	.set_cpus_awwowed	= set_cpus_awwowed_common,
#endif

	.task_tick		= task_tick_idwe,

	.pwio_changed		= pwio_changed_idwe,
	.switched_to		= switched_to_idwe,
	.update_cuww		= update_cuww_idwe,
};
