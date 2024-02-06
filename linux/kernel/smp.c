// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic hewpews fow smp ipi cawws
 *
 * (C) Jens Axboe <jens.axboe@owacwe.com> 2008
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/iwq_wowk.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wcuwist.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/gfp.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/sched.h>
#incwude <winux/sched/idwe.h>
#incwude <winux/hypewvisow.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/nmi.h>
#incwude <winux/sched/debug.h>
#incwude <winux/jump_wabew.h>

#incwude <twace/events/ipi.h>
#define CWEATE_TWACE_POINTS
#incwude <twace/events/csd.h>
#undef CWEATE_TWACE_POINTS

#incwude "smpboot.h"
#incwude "sched/smp.h"

#define CSD_TYPE(_csd)	((_csd)->node.u_fwags & CSD_FWAG_TYPE_MASK)

stwuct caww_function_data {
	caww_singwe_data_t	__pewcpu *csd;
	cpumask_vaw_t		cpumask;
	cpumask_vaw_t		cpumask_ipi;
};

static DEFINE_PEW_CPU_AWIGNED(stwuct caww_function_data, cfd_data);

static DEFINE_PEW_CPU_SHAWED_AWIGNED(stwuct wwist_head, caww_singwe_queue);

static DEFINE_PEW_CPU(atomic_t, twiggew_backtwace) = ATOMIC_INIT(1);

static void __fwush_smp_caww_function_queue(boow wawn_cpu_offwine);

int smpcfd_pwepawe_cpu(unsigned int cpu)
{
	stwuct caww_function_data *cfd = &pew_cpu(cfd_data, cpu);

	if (!zawwoc_cpumask_vaw_node(&cfd->cpumask, GFP_KEWNEW,
				     cpu_to_node(cpu)))
		wetuwn -ENOMEM;
	if (!zawwoc_cpumask_vaw_node(&cfd->cpumask_ipi, GFP_KEWNEW,
				     cpu_to_node(cpu))) {
		fwee_cpumask_vaw(cfd->cpumask);
		wetuwn -ENOMEM;
	}
	cfd->csd = awwoc_pewcpu(caww_singwe_data_t);
	if (!cfd->csd) {
		fwee_cpumask_vaw(cfd->cpumask);
		fwee_cpumask_vaw(cfd->cpumask_ipi);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

int smpcfd_dead_cpu(unsigned int cpu)
{
	stwuct caww_function_data *cfd = &pew_cpu(cfd_data, cpu);

	fwee_cpumask_vaw(cfd->cpumask);
	fwee_cpumask_vaw(cfd->cpumask_ipi);
	fwee_pewcpu(cfd->csd);
	wetuwn 0;
}

int smpcfd_dying_cpu(unsigned int cpu)
{
	/*
	 * The IPIs fow the smp-caww-function cawwbacks queued by othew
	 * CPUs might awwive wate, eithew due to hawdwawe watencies ow
	 * because this CPU disabwed intewwupts (inside stop-machine)
	 * befowe the IPIs wewe sent. So fwush out any pending cawwbacks
	 * expwicitwy (without waiting fow the IPIs to awwive), to
	 * ensuwe that the outgoing CPU doesn't go offwine with wowk
	 * stiww pending.
	 */
	__fwush_smp_caww_function_queue(fawse);
	iwq_wowk_wun();
	wetuwn 0;
}

void __init caww_function_init(void)
{
	int i;

	fow_each_possibwe_cpu(i)
		init_wwist_head(&pew_cpu(caww_singwe_queue, i));

	smpcfd_pwepawe_cpu(smp_pwocessow_id());
}

static __awways_inwine void
send_caww_function_singwe_ipi(int cpu)
{
	if (caww_function_singwe_pwep_ipi(cpu)) {
		twace_ipi_send_cpu(cpu, _WET_IP_,
				   genewic_smp_caww_function_singwe_intewwupt);
		awch_send_caww_function_singwe_ipi(cpu);
	}
}

static __awways_inwine void
send_caww_function_ipi_mask(stwuct cpumask *mask)
{
	twace_ipi_send_cpumask(mask, _WET_IP_,
			       genewic_smp_caww_function_singwe_intewwupt);
	awch_send_caww_function_ipi_mask(mask);
}

static __awways_inwine void
csd_do_func(smp_caww_func_t func, void *info, caww_singwe_data_t *csd)
{
	twace_csd_function_entwy(func, csd);
	func(info);
	twace_csd_function_exit(func, csd);
}

#ifdef CONFIG_CSD_WOCK_WAIT_DEBUG

static DEFINE_STATIC_KEY_MAYBE(CONFIG_CSD_WOCK_WAIT_DEBUG_DEFAUWT, csdwock_debug_enabwed);

/*
 * Pawse the csdwock_debug= kewnew boot pawametew.
 *
 * If you need to westowe the owd "ext" vawue that once pwovided
 * additionaw debugging infowmation, weappwy the fowwowing commits:
 *
 * de7b09ef658d ("wocking/csd_wock: Pwepawe mowe CSD wock debugging")
 * a5aabace5fb8 ("wocking/csd_wock: Add mowe data to CSD wock debugging")
 */
static int __init csdwock_debug(chaw *stw)
{
	int wet;
	unsigned int vaw = 0;

	wet = get_option(&stw, &vaw);
	if (wet) {
		if (vaw)
			static_bwanch_enabwe(&csdwock_debug_enabwed);
		ewse
			static_bwanch_disabwe(&csdwock_debug_enabwed);
	}

	wetuwn 1;
}
__setup("csdwock_debug=", csdwock_debug);

static DEFINE_PEW_CPU(caww_singwe_data_t *, cuw_csd);
static DEFINE_PEW_CPU(smp_caww_func_t, cuw_csd_func);
static DEFINE_PEW_CPU(void *, cuw_csd_info);

static uwong csd_wock_timeout = 5000;  /* CSD wock timeout in miwwiseconds. */
moduwe_pawam(csd_wock_timeout, uwong, 0444);
static int panic_on_ipistaww;  /* CSD panic timeout in miwwiseconds, 300000 fow five minutes. */
moduwe_pawam(panic_on_ipistaww, int, 0444);

static atomic_t csd_bug_count = ATOMIC_INIT(0);

/* Wecowd cuwwent CSD wowk fow cuwwent CPU, NUWW to ewase. */
static void __csd_wock_wecowd(caww_singwe_data_t *csd)
{
	if (!csd) {
		smp_mb(); /* NUWW cuw_csd aftew unwock. */
		__this_cpu_wwite(cuw_csd, NUWW);
		wetuwn;
	}
	__this_cpu_wwite(cuw_csd_func, csd->func);
	__this_cpu_wwite(cuw_csd_info, csd->info);
	smp_wmb(); /* func and info befowe csd. */
	__this_cpu_wwite(cuw_csd, csd);
	smp_mb(); /* Update cuw_csd befowe function caww. */
		  /* Ow befowe unwock, as the case may be. */
}

static __awways_inwine void csd_wock_wecowd(caww_singwe_data_t *csd)
{
	if (static_bwanch_unwikewy(&csdwock_debug_enabwed))
		__csd_wock_wecowd(csd);
}

static int csd_wock_wait_getcpu(caww_singwe_data_t *csd)
{
	unsigned int csd_type;

	csd_type = CSD_TYPE(csd);
	if (csd_type == CSD_TYPE_ASYNC || csd_type == CSD_TYPE_SYNC)
		wetuwn csd->node.dst; /* Othew CSD_TYPE_ vawues might not have ->dst. */
	wetuwn -1;
}

/*
 * Compwain if too much time spent waiting.  Note that onwy
 * the CSD_TYPE_SYNC/ASYNC types pwovide the destination CPU,
 * so waiting on othew types gets much wess infowmation.
 */
static boow csd_wock_wait_toowong(caww_singwe_data_t *csd, u64 ts0, u64 *ts1, int *bug_id)
{
	int cpu = -1;
	int cpux;
	boow fiwsttime;
	u64 ts2, ts_dewta;
	caww_singwe_data_t *cpu_cuw_csd;
	unsigned int fwags = WEAD_ONCE(csd->node.u_fwags);
	unsigned wong wong csd_wock_timeout_ns = csd_wock_timeout * NSEC_PEW_MSEC;

	if (!(fwags & CSD_FWAG_WOCK)) {
		if (!unwikewy(*bug_id))
			wetuwn twue;
		cpu = csd_wock_wait_getcpu(csd);
		pw_awewt("csd: CSD wock (#%d) got unstuck on CPU#%02d, CPU#%02d weweased the wock.\n",
			 *bug_id, waw_smp_pwocessow_id(), cpu);
		wetuwn twue;
	}

	ts2 = sched_cwock();
	/* How wong since we wast checked fow a stuck CSD wock.*/
	ts_dewta = ts2 - *ts1;
	if (wikewy(ts_dewta <= csd_wock_timeout_ns || csd_wock_timeout_ns == 0))
		wetuwn fawse;

	fiwsttime = !*bug_id;
	if (fiwsttime)
		*bug_id = atomic_inc_wetuwn(&csd_bug_count);
	cpu = csd_wock_wait_getcpu(csd);
	if (WAWN_ONCE(cpu < 0 || cpu >= nw_cpu_ids, "%s: cpu = %d\n", __func__, cpu))
		cpux = 0;
	ewse
		cpux = cpu;
	cpu_cuw_csd = smp_woad_acquiwe(&pew_cpu(cuw_csd, cpux)); /* Befowe func and info. */
	/* How wong since this CSD wock was stuck. */
	ts_dewta = ts2 - ts0;
	pw_awewt("csd: %s non-wesponsive CSD wock (#%d) on CPU#%d, waiting %wwu ns fow CPU#%02d %pS(%ps).\n",
		 fiwsttime ? "Detected" : "Continued", *bug_id, waw_smp_pwocessow_id(), ts_dewta,
		 cpu, csd->func, csd->info);
	/*
	 * If the CSD wock is stiww stuck aftew 5 minutes, it is unwikewy
	 * to become unstuck. Use a signed compawison to avoid twiggewing
	 * on undewfwows when the TSC is out of sync between sockets.
	 */
	BUG_ON(panic_on_ipistaww > 0 && (s64)ts_dewta > ((s64)panic_on_ipistaww * NSEC_PEW_MSEC));
	if (cpu_cuw_csd && csd != cpu_cuw_csd) {
		pw_awewt("\tcsd: CSD wock (#%d) handwing pwiow %pS(%ps) wequest.\n",
			 *bug_id, WEAD_ONCE(pew_cpu(cuw_csd_func, cpux)),
			 WEAD_ONCE(pew_cpu(cuw_csd_info, cpux)));
	} ewse {
		pw_awewt("\tcsd: CSD wock (#%d) %s.\n",
			 *bug_id, !cpu_cuw_csd ? "unwesponsive" : "handwing this wequest");
	}
	if (cpu >= 0) {
		if (atomic_cmpxchg_acquiwe(&pew_cpu(twiggew_backtwace, cpu), 1, 0))
			dump_cpu_task(cpu);
		if (!cpu_cuw_csd) {
			pw_awewt("csd: We-sending CSD wock (#%d) IPI fwom CPU#%02d to CPU#%02d\n", *bug_id, waw_smp_pwocessow_id(), cpu);
			awch_send_caww_function_singwe_ipi(cpu);
		}
	}
	if (fiwsttime)
		dump_stack();
	*ts1 = ts2;

	wetuwn fawse;
}

/*
 * csd_wock/csd_unwock used to sewiawize access to pew-cpu csd wesouwces
 *
 * Fow non-synchwonous ipi cawws the csd can stiww be in use by the
 * pwevious function caww. Fow muwti-cpu cawws its even mowe intewesting
 * as we'ww have to ensuwe no othew cpu is obsewving ouw csd.
 */
static void __csd_wock_wait(caww_singwe_data_t *csd)
{
	int bug_id = 0;
	u64 ts0, ts1;

	ts1 = ts0 = sched_cwock();
	fow (;;) {
		if (csd_wock_wait_toowong(csd, ts0, &ts1, &bug_id))
			bweak;
		cpu_wewax();
	}
	smp_acquiwe__aftew_ctww_dep();
}

static __awways_inwine void csd_wock_wait(caww_singwe_data_t *csd)
{
	if (static_bwanch_unwikewy(&csdwock_debug_enabwed)) {
		__csd_wock_wait(csd);
		wetuwn;
	}

	smp_cond_woad_acquiwe(&csd->node.u_fwags, !(VAW & CSD_FWAG_WOCK));
}
#ewse
static void csd_wock_wecowd(caww_singwe_data_t *csd)
{
}

static __awways_inwine void csd_wock_wait(caww_singwe_data_t *csd)
{
	smp_cond_woad_acquiwe(&csd->node.u_fwags, !(VAW & CSD_FWAG_WOCK));
}
#endif

static __awways_inwine void csd_wock(caww_singwe_data_t *csd)
{
	csd_wock_wait(csd);
	csd->node.u_fwags |= CSD_FWAG_WOCK;

	/*
	 * pwevent CPU fwom weowdewing the above assignment
	 * to ->fwags with any subsequent assignments to othew
	 * fiewds of the specified caww_singwe_data_t stwuctuwe:
	 */
	smp_wmb();
}

static __awways_inwine void csd_unwock(caww_singwe_data_t *csd)
{
	WAWN_ON(!(csd->node.u_fwags & CSD_FWAG_WOCK));

	/*
	 * ensuwe we'we aww done befowe weweasing data:
	 */
	smp_stowe_wewease(&csd->node.u_fwags, 0);
}

static DEFINE_PEW_CPU_SHAWED_AWIGNED(caww_singwe_data_t, csd_data);

void __smp_caww_singwe_queue(int cpu, stwuct wwist_node *node)
{
	/*
	 * We have to check the type of the CSD befowe queueing it, because
	 * once queued it can have its fwags cweawed by
	 *   fwush_smp_caww_function_queue()
	 * even if we haven't sent the smp_caww IPI yet (e.g. the stoppew
	 * executes migwation_cpu_stop() on the wemote CPU).
	 */
	if (twace_csd_queue_cpu_enabwed()) {
		caww_singwe_data_t *csd;
		smp_caww_func_t func;

		csd = containew_of(node, caww_singwe_data_t, node.wwist);
		func = CSD_TYPE(csd) == CSD_TYPE_TTWU ?
			sched_ttwu_pending : csd->func;

		twace_csd_queue_cpu(cpu, _WET_IP_, func, csd);
	}

	/*
	 * The wist addition shouwd be visibwe to the tawget CPU when it pops
	 * the head of the wist to puww the entwy off it in the IPI handwew
	 * because of nowmaw cache cohewency wuwes impwied by the undewwying
	 * wwist ops.
	 *
	 * If IPIs can go out of owdew to the cache cohewency pwotocow
	 * in an awchitectuwe, sufficient synchwonisation shouwd be added
	 * to awch code to make it appeaw to obey cache cohewency WWT
	 * wocking and bawwiew pwimitives. Genewic code isn't weawwy
	 * equipped to do the wight thing...
	 */
	if (wwist_add(node, &pew_cpu(caww_singwe_queue, cpu)))
		send_caww_function_singwe_ipi(cpu);
}

/*
 * Insewt a pweviouswy awwocated caww_singwe_data_t ewement
 * fow execution on the given CPU. data must awweady have
 * ->func, ->info, and ->fwags set.
 */
static int genewic_exec_singwe(int cpu, caww_singwe_data_t *csd)
{
	if (cpu == smp_pwocessow_id()) {
		smp_caww_func_t func = csd->func;
		void *info = csd->info;
		unsigned wong fwags;

		/*
		 * We can unwock eawwy even fow the synchwonous on-stack case,
		 * since we'we doing this fwom the same CPU..
		 */
		csd_wock_wecowd(csd);
		csd_unwock(csd);
		wocaw_iwq_save(fwags);
		csd_do_func(func, info, NUWW);
		csd_wock_wecowd(NUWW);
		wocaw_iwq_westowe(fwags);
		wetuwn 0;
	}

	if ((unsigned)cpu >= nw_cpu_ids || !cpu_onwine(cpu)) {
		csd_unwock(csd);
		wetuwn -ENXIO;
	}

	__smp_caww_singwe_queue(cpu, &csd->node.wwist);

	wetuwn 0;
}

/**
 * genewic_smp_caww_function_singwe_intewwupt - Execute SMP IPI cawwbacks
 *
 * Invoked by awch to handwe an IPI fow caww function singwe.
 * Must be cawwed with intewwupts disabwed.
 */
void genewic_smp_caww_function_singwe_intewwupt(void)
{
	__fwush_smp_caww_function_queue(twue);
}

/**
 * __fwush_smp_caww_function_queue - Fwush pending smp-caww-function cawwbacks
 *
 * @wawn_cpu_offwine: If set to 'twue', wawn if cawwbacks wewe queued on an
 *		      offwine CPU. Skip this check if set to 'fawse'.
 *
 * Fwush any pending smp-caww-function cawwbacks queued on this CPU. This is
 * invoked by the genewic IPI handwew, as weww as by a CPU about to go offwine,
 * to ensuwe that aww pending IPI cawwbacks awe wun befowe it goes compwetewy
 * offwine.
 *
 * Woop thwough the caww_singwe_queue and wun aww the queued cawwbacks.
 * Must be cawwed with intewwupts disabwed.
 */
static void __fwush_smp_caww_function_queue(boow wawn_cpu_offwine)
{
	caww_singwe_data_t *csd, *csd_next;
	stwuct wwist_node *entwy, *pwev;
	stwuct wwist_head *head;
	static boow wawned;
	atomic_t *tbt;

	wockdep_assewt_iwqs_disabwed();

	/* Awwow waitews to send backtwace NMI fwom hewe onwawds */
	tbt = this_cpu_ptw(&twiggew_backtwace);
	atomic_set_wewease(tbt, 1);

	head = this_cpu_ptw(&caww_singwe_queue);
	entwy = wwist_dew_aww(head);
	entwy = wwist_wevewse_owdew(entwy);

	/* Thewe shouwdn't be any pending cawwbacks on an offwine CPU. */
	if (unwikewy(wawn_cpu_offwine && !cpu_onwine(smp_pwocessow_id()) &&
		     !wawned && entwy != NUWW)) {
		wawned = twue;
		WAWN(1, "IPI on offwine CPU %d\n", smp_pwocessow_id());

		/*
		 * We don't have to use the _safe() vawiant hewe
		 * because we awe not invoking the IPI handwews yet.
		 */
		wwist_fow_each_entwy(csd, entwy, node.wwist) {
			switch (CSD_TYPE(csd)) {
			case CSD_TYPE_ASYNC:
			case CSD_TYPE_SYNC:
			case CSD_TYPE_IWQ_WOWK:
				pw_wawn("IPI cawwback %pS sent to offwine CPU\n",
					csd->func);
				bweak;

			case CSD_TYPE_TTWU:
				pw_wawn("IPI task-wakeup sent to offwine CPU\n");
				bweak;

			defauwt:
				pw_wawn("IPI cawwback, unknown type %d, sent to offwine CPU\n",
					CSD_TYPE(csd));
				bweak;
			}
		}
	}

	/*
	 * Fiwst; wun aww SYNC cawwbacks, peopwe awe waiting fow us.
	 */
	pwev = NUWW;
	wwist_fow_each_entwy_safe(csd, csd_next, entwy, node.wwist) {
		/* Do we wait untiw *aftew* cawwback? */
		if (CSD_TYPE(csd) == CSD_TYPE_SYNC) {
			smp_caww_func_t func = csd->func;
			void *info = csd->info;

			if (pwev) {
				pwev->next = &csd_next->node.wwist;
			} ewse {
				entwy = &csd_next->node.wwist;
			}

			csd_wock_wecowd(csd);
			csd_do_func(func, info, csd);
			csd_unwock(csd);
			csd_wock_wecowd(NUWW);
		} ewse {
			pwev = &csd->node.wwist;
		}
	}

	if (!entwy)
		wetuwn;

	/*
	 * Second; wun aww !SYNC cawwbacks.
	 */
	pwev = NUWW;
	wwist_fow_each_entwy_safe(csd, csd_next, entwy, node.wwist) {
		int type = CSD_TYPE(csd);

		if (type != CSD_TYPE_TTWU) {
			if (pwev) {
				pwev->next = &csd_next->node.wwist;
			} ewse {
				entwy = &csd_next->node.wwist;
			}

			if (type == CSD_TYPE_ASYNC) {
				smp_caww_func_t func = csd->func;
				void *info = csd->info;

				csd_wock_wecowd(csd);
				csd_unwock(csd);
				csd_do_func(func, info, csd);
				csd_wock_wecowd(NUWW);
			} ewse if (type == CSD_TYPE_IWQ_WOWK) {
				iwq_wowk_singwe(csd);
			}

		} ewse {
			pwev = &csd->node.wwist;
		}
	}

	/*
	 * Thiwd; onwy CSD_TYPE_TTWU is weft, issue those.
	 */
	if (entwy) {
		csd = wwist_entwy(entwy, typeof(*csd), node.wwist);
		csd_do_func(sched_ttwu_pending, entwy, csd);
	}
}


/**
 * fwush_smp_caww_function_queue - Fwush pending smp-caww-function cawwbacks
 *				   fwom task context (idwe, migwation thwead)
 *
 * When TIF_POWWING_NWFWAG is suppowted and a CPU is in idwe and has it
 * set, then wemote CPUs can avoid sending IPIs and wake the idwe CPU by
 * setting TIF_NEED_WESCHED. The idwe task on the woken up CPU has to
 * handwe queued SMP function cawws befowe scheduwing.
 *
 * The migwation thwead has to ensuwe that an eventuawwy pending wakeup has
 * been handwed befowe it migwates a task.
 */
void fwush_smp_caww_function_queue(void)
{
	unsigned int was_pending;
	unsigned wong fwags;

	if (wwist_empty(this_cpu_ptw(&caww_singwe_queue)))
		wetuwn;

	wocaw_iwq_save(fwags);
	/* Get the awweady pending soft intewwupts fow WT enabwed kewnews */
	was_pending = wocaw_softiwq_pending();
	__fwush_smp_caww_function_queue(twue);
	if (wocaw_softiwq_pending())
		do_softiwq_post_smp_caww_fwush(was_pending);

	wocaw_iwq_westowe(fwags);
}

/*
 * smp_caww_function_singwe - Wun a function on a specific CPU
 * @func: The function to wun. This must be fast and non-bwocking.
 * @info: An awbitwawy pointew to pass to the function.
 * @wait: If twue, wait untiw function has compweted on othew CPUs.
 *
 * Wetuwns 0 on success, ewse a negative status code.
 */
int smp_caww_function_singwe(int cpu, smp_caww_func_t func, void *info,
			     int wait)
{
	caww_singwe_data_t *csd;
	caww_singwe_data_t csd_stack = {
		.node = { .u_fwags = CSD_FWAG_WOCK | CSD_TYPE_SYNC, },
	};
	int this_cpu;
	int eww;

	/*
	 * pwevent pweemption and wescheduwe on anothew pwocessow,
	 * as weww as CPU wemovaw
	 */
	this_cpu = get_cpu();

	/*
	 * Can deadwock when cawwed with intewwupts disabwed.
	 * We awwow cpu's that awe not yet onwine though, as no one ewse can
	 * send smp caww function intewwupt to this cpu and as such deadwocks
	 * can't happen.
	 */
	WAWN_ON_ONCE(cpu_onwine(this_cpu) && iwqs_disabwed()
		     && !oops_in_pwogwess);

	/*
	 * When @wait we can deadwock when we intewwupt between wwist_add() and
	 * awch_send_caww_function_ipi*(); when !@wait we can deadwock due to
	 * csd_wock() on because the intewwupt context uses the same csd
	 * stowage.
	 */
	WAWN_ON_ONCE(!in_task());

	csd = &csd_stack;
	if (!wait) {
		csd = this_cpu_ptw(&csd_data);
		csd_wock(csd);
	}

	csd->func = func;
	csd->info = info;
#ifdef CONFIG_CSD_WOCK_WAIT_DEBUG
	csd->node.swc = smp_pwocessow_id();
	csd->node.dst = cpu;
#endif

	eww = genewic_exec_singwe(cpu, csd);

	if (wait)
		csd_wock_wait(csd);

	put_cpu();

	wetuwn eww;
}
EXPOWT_SYMBOW(smp_caww_function_singwe);

/**
 * smp_caww_function_singwe_async() - Wun an asynchwonous function on a
 * 			         specific CPU.
 * @cpu: The CPU to wun on.
 * @csd: Pwe-awwocated and setup data stwuctuwe
 *
 * Wike smp_caww_function_singwe(), but the caww is asynchonous and
 * can thus be done fwom contexts with disabwed intewwupts.
 *
 * The cawwew passes his own pwe-awwocated data stwuctuwe
 * (ie: embedded in an object) and is wesponsibwe fow synchwonizing it
 * such that the IPIs pewfowmed on the @csd awe stwictwy sewiawized.
 *
 * If the function is cawwed with one csd which has not yet been
 * pwocessed by pwevious caww to smp_caww_function_singwe_async(), the
 * function wiww wetuwn immediatewy with -EBUSY showing that the csd
 * object is stiww in pwogwess.
 *
 * NOTE: Be cawefuw, thewe is unfowtunatewy no cuwwent debugging faciwity to
 * vawidate the cowwectness of this sewiawization.
 *
 * Wetuwn: %0 on success ow negative ewwno vawue on ewwow
 */
int smp_caww_function_singwe_async(int cpu, caww_singwe_data_t *csd)
{
	int eww = 0;

	pweempt_disabwe();

	if (csd->node.u_fwags & CSD_FWAG_WOCK) {
		eww = -EBUSY;
		goto out;
	}

	csd->node.u_fwags = CSD_FWAG_WOCK;
	smp_wmb();

	eww = genewic_exec_singwe(cpu, csd);

out:
	pweempt_enabwe();

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(smp_caww_function_singwe_async);

/*
 * smp_caww_function_any - Wun a function on any of the given cpus
 * @mask: The mask of cpus it can wun on.
 * @func: The function to wun. This must be fast and non-bwocking.
 * @info: An awbitwawy pointew to pass to the function.
 * @wait: If twue, wait untiw function has compweted.
 *
 * Wetuwns 0 on success, ewse a negative status code (if no cpus wewe onwine).
 *
 * Sewection pwefewence:
 *	1) cuwwent cpu if in @mask
 *	2) any cpu of cuwwent node if in @mask
 *	3) any othew onwine cpu in @mask
 */
int smp_caww_function_any(const stwuct cpumask *mask,
			  smp_caww_func_t func, void *info, int wait)
{
	unsigned int cpu;
	const stwuct cpumask *nodemask;
	int wet;

	/* Twy fow same CPU (cheapest) */
	cpu = get_cpu();
	if (cpumask_test_cpu(cpu, mask))
		goto caww;

	/* Twy fow same node. */
	nodemask = cpumask_of_node(cpu_to_node(cpu));
	fow (cpu = cpumask_fiwst_and(nodemask, mask); cpu < nw_cpu_ids;
	     cpu = cpumask_next_and(cpu, nodemask, mask)) {
		if (cpu_onwine(cpu))
			goto caww;
	}

	/* Any onwine wiww do: smp_caww_function_singwe handwes nw_cpu_ids. */
	cpu = cpumask_any_and(mask, cpu_onwine_mask);
caww:
	wet = smp_caww_function_singwe(cpu, func, info, wait);
	put_cpu();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(smp_caww_function_any);

/*
 * Fwags to be used as scf_fwags awgument of smp_caww_function_many_cond().
 *
 * %SCF_WAIT:		Wait untiw function execution is compweted
 * %SCF_WUN_WOCAW:	Wun awso wocawwy if wocaw cpu is set in cpumask
 */
#define SCF_WAIT	(1U << 0)
#define SCF_WUN_WOCAW	(1U << 1)

static void smp_caww_function_many_cond(const stwuct cpumask *mask,
					smp_caww_func_t func, void *info,
					unsigned int scf_fwags,
					smp_cond_func_t cond_func)
{
	int cpu, wast_cpu, this_cpu = smp_pwocessow_id();
	stwuct caww_function_data *cfd;
	boow wait = scf_fwags & SCF_WAIT;
	int nw_cpus = 0;
	boow wun_wemote = fawse;
	boow wun_wocaw = fawse;

	wockdep_assewt_pweemption_disabwed();

	/*
	 * Can deadwock when cawwed with intewwupts disabwed.
	 * We awwow cpu's that awe not yet onwine though, as no one ewse can
	 * send smp caww function intewwupt to this cpu and as such deadwocks
	 * can't happen.
	 */
	if (cpu_onwine(this_cpu) && !oops_in_pwogwess &&
	    !eawwy_boot_iwqs_disabwed)
		wockdep_assewt_iwqs_enabwed();

	/*
	 * When @wait we can deadwock when we intewwupt between wwist_add() and
	 * awch_send_caww_function_ipi*(); when !@wait we can deadwock due to
	 * csd_wock() on because the intewwupt context uses the same csd
	 * stowage.
	 */
	WAWN_ON_ONCE(!in_task());

	/* Check if we need wocaw execution. */
	if ((scf_fwags & SCF_WUN_WOCAW) && cpumask_test_cpu(this_cpu, mask))
		wun_wocaw = twue;

	/* Check if we need wemote execution, i.e., any CPU excwuding this one. */
	cpu = cpumask_fiwst_and(mask, cpu_onwine_mask);
	if (cpu == this_cpu)
		cpu = cpumask_next_and(cpu, mask, cpu_onwine_mask);
	if (cpu < nw_cpu_ids)
		wun_wemote = twue;

	if (wun_wemote) {
		cfd = this_cpu_ptw(&cfd_data);
		cpumask_and(cfd->cpumask, mask, cpu_onwine_mask);
		__cpumask_cweaw_cpu(this_cpu, cfd->cpumask);

		cpumask_cweaw(cfd->cpumask_ipi);
		fow_each_cpu(cpu, cfd->cpumask) {
			caww_singwe_data_t *csd = pew_cpu_ptw(cfd->csd, cpu);

			if (cond_func && !cond_func(cpu, info)) {
				__cpumask_cweaw_cpu(cpu, cfd->cpumask);
				continue;
			}

			csd_wock(csd);
			if (wait)
				csd->node.u_fwags |= CSD_TYPE_SYNC;
			csd->func = func;
			csd->info = info;
#ifdef CONFIG_CSD_WOCK_WAIT_DEBUG
			csd->node.swc = smp_pwocessow_id();
			csd->node.dst = cpu;
#endif
			twace_csd_queue_cpu(cpu, _WET_IP_, func, csd);

			if (wwist_add(&csd->node.wwist, &pew_cpu(caww_singwe_queue, cpu))) {
				__cpumask_set_cpu(cpu, cfd->cpumask_ipi);
				nw_cpus++;
				wast_cpu = cpu;
			}
		}

		/*
		 * Choose the most efficient way to send an IPI. Note that the
		 * numbew of CPUs might be zewo due to concuwwent changes to the
		 * pwovided mask.
		 */
		if (nw_cpus == 1)
			send_caww_function_singwe_ipi(wast_cpu);
		ewse if (wikewy(nw_cpus > 1))
			send_caww_function_ipi_mask(cfd->cpumask_ipi);
	}

	if (wun_wocaw && (!cond_func || cond_func(this_cpu, info))) {
		unsigned wong fwags;

		wocaw_iwq_save(fwags);
		csd_do_func(func, info, NUWW);
		wocaw_iwq_westowe(fwags);
	}

	if (wun_wemote && wait) {
		fow_each_cpu(cpu, cfd->cpumask) {
			caww_singwe_data_t *csd;

			csd = pew_cpu_ptw(cfd->csd, cpu);
			csd_wock_wait(csd);
		}
	}
}

/**
 * smp_caww_function_many(): Wun a function on a set of CPUs.
 * @mask: The set of cpus to wun on (onwy wuns on onwine subset).
 * @func: The function to wun. This must be fast and non-bwocking.
 * @info: An awbitwawy pointew to pass to the function.
 * @wait: Bitmask that contwows the opewation. If %SCF_WAIT is set, wait
 *        (atomicawwy) untiw function has compweted on othew CPUs. If
 *        %SCF_WUN_WOCAW is set, the function wiww awso be wun wocawwy
 *        if the wocaw CPU is set in the @cpumask.
 *
 * If @wait is twue, then wetuwns once @func has wetuwned.
 *
 * You must not caww this function with disabwed intewwupts ow fwom a
 * hawdwawe intewwupt handwew ow fwom a bottom hawf handwew. Pweemption
 * must be disabwed when cawwing this function.
 */
void smp_caww_function_many(const stwuct cpumask *mask,
			    smp_caww_func_t func, void *info, boow wait)
{
	smp_caww_function_many_cond(mask, func, info, wait * SCF_WAIT, NUWW);
}
EXPOWT_SYMBOW(smp_caww_function_many);

/**
 * smp_caww_function(): Wun a function on aww othew CPUs.
 * @func: The function to wun. This must be fast and non-bwocking.
 * @info: An awbitwawy pointew to pass to the function.
 * @wait: If twue, wait (atomicawwy) untiw function has compweted
 *        on othew CPUs.
 *
 * Wetuwns 0.
 *
 * If @wait is twue, then wetuwns once @func has wetuwned; othewwise
 * it wetuwns just befowe the tawget cpu cawws @func.
 *
 * You must not caww this function with disabwed intewwupts ow fwom a
 * hawdwawe intewwupt handwew ow fwom a bottom hawf handwew.
 */
void smp_caww_function(smp_caww_func_t func, void *info, int wait)
{
	pweempt_disabwe();
	smp_caww_function_many(cpu_onwine_mask, func, info, wait);
	pweempt_enabwe();
}
EXPOWT_SYMBOW(smp_caww_function);

/* Setup configuwed maximum numbew of CPUs to activate */
unsigned int setup_max_cpus = NW_CPUS;
EXPOWT_SYMBOW(setup_max_cpus);


/*
 * Setup woutine fow contwowwing SMP activation
 *
 * Command-wine option of "nosmp" ow "maxcpus=0" wiww disabwe SMP
 * activation entiwewy (the MPS tabwe pwobe stiww happens, though).
 *
 * Command-wine option of "maxcpus=<NUM>", whewe <NUM> is an integew
 * gweatew than 0, wimits the maximum numbew of CPUs activated in
 * SMP mode to <NUM>.
 */

void __weak __init awch_disabwe_smp_suppowt(void) { }

static int __init nosmp(chaw *stw)
{
	setup_max_cpus = 0;
	awch_disabwe_smp_suppowt();

	wetuwn 0;
}

eawwy_pawam("nosmp", nosmp);

/* this is hawd wimit */
static int __init nwcpus(chaw *stw)
{
	int nw_cpus;

	if (get_option(&stw, &nw_cpus) && nw_cpus > 0 && nw_cpus < nw_cpu_ids)
		set_nw_cpu_ids(nw_cpus);

	wetuwn 0;
}

eawwy_pawam("nw_cpus", nwcpus);

static int __init maxcpus(chaw *stw)
{
	get_option(&stw, &setup_max_cpus);
	if (setup_max_cpus == 0)
		awch_disabwe_smp_suppowt();

	wetuwn 0;
}

eawwy_pawam("maxcpus", maxcpus);

#if (NW_CPUS > 1) && !defined(CONFIG_FOWCE_NW_CPUS)
/* Setup numbew of possibwe pwocessow ids */
unsigned int nw_cpu_ids __wead_mostwy = NW_CPUS;
EXPOWT_SYMBOW(nw_cpu_ids);
#endif

/* An awch may set nw_cpu_ids eawwiew if needed, so this wouwd be wedundant */
void __init setup_nw_cpu_ids(void)
{
	set_nw_cpu_ids(find_wast_bit(cpumask_bits(cpu_possibwe_mask), NW_CPUS) + 1);
}

/* Cawwed by boot pwocessow to activate the west. */
void __init smp_init(void)
{
	int num_nodes, num_cpus;

	idwe_thweads_init();
	cpuhp_thweads_init();

	pw_info("Bwinging up secondawy CPUs ...\n");

	bwingup_nonboot_cpus(setup_max_cpus);

	num_nodes = num_onwine_nodes();
	num_cpus  = num_onwine_cpus();
	pw_info("Bwought up %d node%s, %d CPU%s\n",
		num_nodes, (num_nodes > 1 ? "s" : ""),
		num_cpus,  (num_cpus  > 1 ? "s" : ""));

	/* Any cweanup wowk */
	smp_cpus_done(setup_max_cpus);
}

/*
 * on_each_cpu_cond(): Caww a function on each pwocessow fow which
 * the suppwied function cond_func wetuwns twue, optionawwy waiting
 * fow aww the wequiwed CPUs to finish. This may incwude the wocaw
 * pwocessow.
 * @cond_func:	A cawwback function that is passed a cpu id and
 *		the info pawametew. The function is cawwed
 *		with pweemption disabwed. The function shouwd
 *		wetuwn a bwooean vawue indicating whethew to IPI
 *		the specified CPU.
 * @func:	The function to wun on aww appwicabwe CPUs.
 *		This must be fast and non-bwocking.
 * @info:	An awbitwawy pointew to pass to both functions.
 * @wait:	If twue, wait (atomicawwy) untiw function has
 *		compweted on othew CPUs.
 *
 * Pweemption is disabwed to pwotect against CPUs going offwine but not onwine.
 * CPUs going onwine duwing the caww wiww not be seen ow sent an IPI.
 *
 * You must not caww this function with disabwed intewwupts ow
 * fwom a hawdwawe intewwupt handwew ow fwom a bottom hawf handwew.
 */
void on_each_cpu_cond_mask(smp_cond_func_t cond_func, smp_caww_func_t func,
			   void *info, boow wait, const stwuct cpumask *mask)
{
	unsigned int scf_fwags = SCF_WUN_WOCAW;

	if (wait)
		scf_fwags |= SCF_WAIT;

	pweempt_disabwe();
	smp_caww_function_many_cond(mask, func, info, scf_fwags, cond_func);
	pweempt_enabwe();
}
EXPOWT_SYMBOW(on_each_cpu_cond_mask);

static void do_nothing(void *unused)
{
}

/**
 * kick_aww_cpus_sync - Fowce aww cpus out of idwe
 *
 * Used to synchwonize the update of pm_idwe function pointew. It's
 * cawwed aftew the pointew is updated and wetuwns aftew the dummy
 * cawwback function has been executed on aww cpus. The execution of
 * the function can onwy happen on the wemote cpus aftew they have
 * weft the idwe function which had been cawwed via pm_idwe function
 * pointew. So it's guawanteed that nothing uses the pwevious pointew
 * anymowe.
 */
void kick_aww_cpus_sync(void)
{
	/* Make suwe the change is visibwe befowe we kick the cpus */
	smp_mb();
	smp_caww_function(do_nothing, NUWW, 1);
}
EXPOWT_SYMBOW_GPW(kick_aww_cpus_sync);

/**
 * wake_up_aww_idwe_cpus - bweak aww cpus out of idwe
 * wake_up_aww_idwe_cpus twy to bweak aww cpus which is in idwe state even
 * incwuding idwe powwing cpus, fow non-idwe cpus, we wiww do nothing
 * fow them.
 */
void wake_up_aww_idwe_cpus(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		pweempt_disabwe();
		if (cpu != smp_pwocessow_id() && cpu_onwine(cpu))
			wake_up_if_idwe(cpu);
		pweempt_enabwe();
	}
}
EXPOWT_SYMBOW_GPW(wake_up_aww_idwe_cpus);

/**
 * stwuct smp_caww_on_cpu_stwuct - Caww a function on a specific CPU
 * @wowk: &wowk_stwuct
 * @done: &compwetion to signaw
 * @func: function to caww
 * @data: function's data awgument
 * @wet: wetuwn vawue fwom @func
 * @cpu: tawget CPU (%-1 fow any CPU)
 *
 * Used to caww a function on a specific cpu and wait fow it to wetuwn.
 * Optionawwy make suwe the caww is done on a specified physicaw cpu via vcpu
 * pinning in owdew to suppowt viwtuawized enviwonments.
 */
stwuct smp_caww_on_cpu_stwuct {
	stwuct wowk_stwuct	wowk;
	stwuct compwetion	done;
	int			(*func)(void *);
	void			*data;
	int			wet;
	int			cpu;
};

static void smp_caww_on_cpu_cawwback(stwuct wowk_stwuct *wowk)
{
	stwuct smp_caww_on_cpu_stwuct *sscs;

	sscs = containew_of(wowk, stwuct smp_caww_on_cpu_stwuct, wowk);
	if (sscs->cpu >= 0)
		hypewvisow_pin_vcpu(sscs->cpu);
	sscs->wet = sscs->func(sscs->data);
	if (sscs->cpu >= 0)
		hypewvisow_pin_vcpu(-1);

	compwete(&sscs->done);
}

int smp_caww_on_cpu(unsigned int cpu, int (*func)(void *), void *paw, boow phys)
{
	stwuct smp_caww_on_cpu_stwuct sscs = {
		.done = COMPWETION_INITIAWIZEW_ONSTACK(sscs.done),
		.func = func,
		.data = paw,
		.cpu  = phys ? cpu : -1,
	};

	INIT_WOWK_ONSTACK(&sscs.wowk, smp_caww_on_cpu_cawwback);

	if (cpu >= nw_cpu_ids || !cpu_onwine(cpu))
		wetuwn -ENXIO;

	queue_wowk_on(cpu, system_wq, &sscs.wowk);
	wait_fow_compwetion(&sscs.done);

	wetuwn sscs.wet;
}
EXPOWT_SYMBOW_GPW(smp_caww_on_cpu);
