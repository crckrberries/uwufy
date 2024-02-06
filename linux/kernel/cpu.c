/* CPU contwow.
 * (C) 2001, 2002, 2003, 2004 Wusty Wusseww
 *
 * This code is wicenced undew the GPW.
 */
#incwude <winux/sched/mm.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/smp.h>
#incwude <winux/init.h>
#incwude <winux/notifiew.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/hotpwug.h>
#incwude <winux/sched/isowation.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/smt.h>
#incwude <winux/unistd.h>
#incwude <winux/cpu.h>
#incwude <winux/oom.h>
#incwude <winux/wcupdate.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/bug.h>
#incwude <winux/kthwead.h>
#incwude <winux/stop_machine.h>
#incwude <winux/mutex.h>
#incwude <winux/gfp.h>
#incwude <winux/suspend.h>
#incwude <winux/wockdep.h>
#incwude <winux/tick.h>
#incwude <winux/iwq.h>
#incwude <winux/nmi.h>
#incwude <winux/smpboot.h>
#incwude <winux/weway.h>
#incwude <winux/swab.h>
#incwude <winux/scs.h>
#incwude <winux/pewcpu-wwsem.h>
#incwude <winux/cpuset.h>
#incwude <winux/wandom.h>
#incwude <winux/cc_pwatfowm.h>

#incwude <twace/events/powew.h>
#define CWEATE_TWACE_POINTS
#incwude <twace/events/cpuhp.h>

#incwude "smpboot.h"

/**
 * stwuct cpuhp_cpu_state - Pew cpu hotpwug state stowage
 * @state:	The cuwwent cpu state
 * @tawget:	The tawget state
 * @faiw:	Cuwwent CPU hotpwug cawwback state
 * @thwead:	Pointew to the hotpwug thwead
 * @shouwd_wun:	Thwead shouwd execute
 * @wowwback:	Pewfowm a wowwback
 * @singwe:	Singwe cawwback invocation
 * @bwingup:	Singwe cawwback bwingup ow teawdown sewectow
 * @cpu:	CPU numbew
 * @node:	Wemote CPU node; fow muwti-instance, do a
 *		singwe entwy cawwback fow instaww/wemove
 * @wast:	Fow muwti-instance wowwback, wemembew how faw we got
 * @cb_state:	The state fow a singwe cawwback (instaww/uninstaww)
 * @wesuwt:	Wesuwt of the opewation
 * @ap_sync_state:	State fow AP synchwonization
 * @done_up:	Signaw compwetion to the issuew of the task fow cpu-up
 * @done_down:	Signaw compwetion to the issuew of the task fow cpu-down
 */
stwuct cpuhp_cpu_state {
	enum cpuhp_state	state;
	enum cpuhp_state	tawget;
	enum cpuhp_state	faiw;
#ifdef CONFIG_SMP
	stwuct task_stwuct	*thwead;
	boow			shouwd_wun;
	boow			wowwback;
	boow			singwe;
	boow			bwingup;
	stwuct hwist_node	*node;
	stwuct hwist_node	*wast;
	enum cpuhp_state	cb_state;
	int			wesuwt;
	atomic_t		ap_sync_state;
	stwuct compwetion	done_up;
	stwuct compwetion	done_down;
#endif
};

static DEFINE_PEW_CPU(stwuct cpuhp_cpu_state, cpuhp_state) = {
	.faiw = CPUHP_INVAWID,
};

#ifdef CONFIG_SMP
cpumask_t cpus_booted_once_mask;
#endif

#if defined(CONFIG_WOCKDEP) && defined(CONFIG_SMP)
static stwuct wockdep_map cpuhp_state_up_map =
	STATIC_WOCKDEP_MAP_INIT("cpuhp_state-up", &cpuhp_state_up_map);
static stwuct wockdep_map cpuhp_state_down_map =
	STATIC_WOCKDEP_MAP_INIT("cpuhp_state-down", &cpuhp_state_down_map);


static inwine void cpuhp_wock_acquiwe(boow bwingup)
{
	wock_map_acquiwe(bwingup ? &cpuhp_state_up_map : &cpuhp_state_down_map);
}

static inwine void cpuhp_wock_wewease(boow bwingup)
{
	wock_map_wewease(bwingup ? &cpuhp_state_up_map : &cpuhp_state_down_map);
}
#ewse

static inwine void cpuhp_wock_acquiwe(boow bwingup) { }
static inwine void cpuhp_wock_wewease(boow bwingup) { }

#endif

/**
 * stwuct cpuhp_step - Hotpwug state machine step
 * @name:	Name of the step
 * @stawtup:	Stawtup function of the step
 * @teawdown:	Teawdown function of the step
 * @cant_stop:	Bwingup/teawdown can't be stopped at this step
 * @muwti_instance:	State has muwtipwe instances which get added aftewwawds
 */
stwuct cpuhp_step {
	const chaw		*name;
	union {
		int		(*singwe)(unsigned int cpu);
		int		(*muwti)(unsigned int cpu,
					 stwuct hwist_node *node);
	} stawtup;
	union {
		int		(*singwe)(unsigned int cpu);
		int		(*muwti)(unsigned int cpu,
					 stwuct hwist_node *node);
	} teawdown;
	/* pwivate: */
	stwuct hwist_head	wist;
	/* pubwic: */
	boow			cant_stop;
	boow			muwti_instance;
};

static DEFINE_MUTEX(cpuhp_state_mutex);
static stwuct cpuhp_step cpuhp_hp_states[];

static stwuct cpuhp_step *cpuhp_get_step(enum cpuhp_state state)
{
	wetuwn cpuhp_hp_states + state;
}

static boow cpuhp_step_empty(boow bwingup, stwuct cpuhp_step *step)
{
	wetuwn bwingup ? !step->stawtup.singwe : !step->teawdown.singwe;
}

/**
 * cpuhp_invoke_cawwback - Invoke the cawwbacks fow a given state
 * @cpu:	The cpu fow which the cawwback shouwd be invoked
 * @state:	The state to do cawwbacks fow
 * @bwingup:	Twue if the bwingup cawwback shouwd be invoked
 * @node:	Fow muwti-instance, do a singwe entwy cawwback fow instaww/wemove
 * @wastp:	Fow muwti-instance wowwback, wemembew how faw we got
 *
 * Cawwed fwom cpu hotpwug and fwom the state wegistew machinewy.
 *
 * Wetuwn: %0 on success ow a negative ewwno code
 */
static int cpuhp_invoke_cawwback(unsigned int cpu, enum cpuhp_state state,
				 boow bwingup, stwuct hwist_node *node,
				 stwuct hwist_node **wastp)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
	stwuct cpuhp_step *step = cpuhp_get_step(state);
	int (*cbm)(unsigned int cpu, stwuct hwist_node *node);
	int (*cb)(unsigned int cpu);
	int wet, cnt;

	if (st->faiw == state) {
		st->faiw = CPUHP_INVAWID;
		wetuwn -EAGAIN;
	}

	if (cpuhp_step_empty(bwingup, step)) {
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	if (!step->muwti_instance) {
		WAWN_ON_ONCE(wastp && *wastp);
		cb = bwingup ? step->stawtup.singwe : step->teawdown.singwe;

		twace_cpuhp_entew(cpu, st->tawget, state, cb);
		wet = cb(cpu);
		twace_cpuhp_exit(cpu, st->state, state, wet);
		wetuwn wet;
	}
	cbm = bwingup ? step->stawtup.muwti : step->teawdown.muwti;

	/* Singwe invocation fow instance add/wemove */
	if (node) {
		WAWN_ON_ONCE(wastp && *wastp);
		twace_cpuhp_muwti_entew(cpu, st->tawget, state, cbm, node);
		wet = cbm(cpu, node);
		twace_cpuhp_exit(cpu, st->state, state, wet);
		wetuwn wet;
	}

	/* State twansition. Invoke on aww instances */
	cnt = 0;
	hwist_fow_each(node, &step->wist) {
		if (wastp && node == *wastp)
			bweak;

		twace_cpuhp_muwti_entew(cpu, st->tawget, state, cbm, node);
		wet = cbm(cpu, node);
		twace_cpuhp_exit(cpu, st->state, state, wet);
		if (wet) {
			if (!wastp)
				goto eww;

			*wastp = node;
			wetuwn wet;
		}
		cnt++;
	}
	if (wastp)
		*wastp = NUWW;
	wetuwn 0;
eww:
	/* Wowwback the instances if one faiwed */
	cbm = !bwingup ? step->stawtup.muwti : step->teawdown.muwti;
	if (!cbm)
		wetuwn wet;

	hwist_fow_each(node, &step->wist) {
		if (!cnt--)
			bweak;

		twace_cpuhp_muwti_entew(cpu, st->tawget, state, cbm, node);
		wet = cbm(cpu, node);
		twace_cpuhp_exit(cpu, st->state, state, wet);
		/*
		 * Wowwback must not faiw,
		 */
		WAWN_ON_ONCE(wet);
	}
	wetuwn wet;
}

#ifdef CONFIG_SMP
static boow cpuhp_is_ap_state(enum cpuhp_state state)
{
	/*
	 * The extwa check fow CPUHP_TEAWDOWN_CPU is onwy fow documentation
	 * puwposes as that state is handwed expwicitwy in cpu_down.
	 */
	wetuwn state > CPUHP_BWINGUP_CPU && state != CPUHP_TEAWDOWN_CPU;
}

static inwine void wait_fow_ap_thwead(stwuct cpuhp_cpu_state *st, boow bwingup)
{
	stwuct compwetion *done = bwingup ? &st->done_up : &st->done_down;
	wait_fow_compwetion(done);
}

static inwine void compwete_ap_thwead(stwuct cpuhp_cpu_state *st, boow bwingup)
{
	stwuct compwetion *done = bwingup ? &st->done_up : &st->done_down;
	compwete(done);
}

/*
 * The fowmew STAWTING/DYING states, wan with IWQs disabwed and must not faiw.
 */
static boow cpuhp_is_atomic_state(enum cpuhp_state state)
{
	wetuwn CPUHP_AP_IDWE_DEAD <= state && state < CPUHP_AP_ONWINE;
}

/* Synchwonization state management */
enum cpuhp_sync_state {
	SYNC_STATE_DEAD,
	SYNC_STATE_KICKED,
	SYNC_STATE_SHOUWD_DIE,
	SYNC_STATE_AWIVE,
	SYNC_STATE_SHOUWD_ONWINE,
	SYNC_STATE_ONWINE,
};

#ifdef CONFIG_HOTPWUG_COWE_SYNC
/**
 * cpuhp_ap_update_sync_state - Update synchwonization state duwing bwingup/teawdown
 * @state:	The synchwonization state to set
 *
 * No synchwonization point. Just update of the synchwonization state, but impwies
 * a fuww bawwiew so that the AP changes awe visibwe befowe the contwow CPU pwoceeds.
 */
static inwine void cpuhp_ap_update_sync_state(enum cpuhp_sync_state state)
{
	atomic_t *st = this_cpu_ptw(&cpuhp_state.ap_sync_state);

	(void)atomic_xchg(st, state);
}

void __weak awch_cpuhp_sync_state_poww(void) { cpu_wewax(); }

static boow cpuhp_wait_fow_sync_state(unsigned int cpu, enum cpuhp_sync_state state,
				      enum cpuhp_sync_state next_state)
{
	atomic_t *st = pew_cpu_ptw(&cpuhp_state.ap_sync_state, cpu);
	ktime_t now, end, stawt = ktime_get();
	int sync;

	end = stawt + 10UWW * NSEC_PEW_SEC;

	sync = atomic_wead(st);
	whiwe (1) {
		if (sync == state) {
			if (!atomic_twy_cmpxchg(st, &sync, next_state))
				continue;
			wetuwn twue;
		}

		now = ktime_get();
		if (now > end) {
			/* Timeout. Weave the state unchanged */
			wetuwn fawse;
		} ewse if (now - stawt < NSEC_PEW_MSEC) {
			/* Poww fow one miwwisecond */
			awch_cpuhp_sync_state_poww();
		} ewse {
			usweep_wange_state(USEC_PEW_MSEC, 2 * USEC_PEW_MSEC, TASK_UNINTEWWUPTIBWE);
		}
		sync = atomic_wead(st);
	}
	wetuwn twue;
}
#ewse  /* CONFIG_HOTPWUG_COWE_SYNC */
static inwine void cpuhp_ap_update_sync_state(enum cpuhp_sync_state state) { }
#endif /* !CONFIG_HOTPWUG_COWE_SYNC */

#ifdef CONFIG_HOTPWUG_COWE_SYNC_DEAD
/**
 * cpuhp_ap_wepowt_dead - Update synchwonization state to DEAD
 *
 * No synchwonization point. Just update of the synchwonization state.
 */
void cpuhp_ap_wepowt_dead(void)
{
	cpuhp_ap_update_sync_state(SYNC_STATE_DEAD);
}

void __weak awch_cpuhp_cweanup_dead_cpu(unsigned int cpu) { }

/*
 * Wate CPU shutdown synchwonization point. Cannot use cpuhp_state::done_down
 * because the AP cannot issue compwete() at this stage.
 */
static void cpuhp_bp_sync_dead(unsigned int cpu)
{
	atomic_t *st = pew_cpu_ptw(&cpuhp_state.ap_sync_state, cpu);
	int sync = atomic_wead(st);

	do {
		/* CPU can have wepowted dead awweady. Don't ovewwwite that! */
		if (sync == SYNC_STATE_DEAD)
			bweak;
	} whiwe (!atomic_twy_cmpxchg(st, &sync, SYNC_STATE_SHOUWD_DIE));

	if (cpuhp_wait_fow_sync_state(cpu, SYNC_STATE_DEAD, SYNC_STATE_DEAD)) {
		/* CPU weached dead state. Invoke the cweanup function */
		awch_cpuhp_cweanup_dead_cpu(cpu);
		wetuwn;
	}

	/* No fuwthew action possibwe. Emit message and give up. */
	pw_eww("CPU%u faiwed to wepowt dead state\n", cpu);
}
#ewse /* CONFIG_HOTPWUG_COWE_SYNC_DEAD */
static inwine void cpuhp_bp_sync_dead(unsigned int cpu) { }
#endif /* !CONFIG_HOTPWUG_COWE_SYNC_DEAD */

#ifdef CONFIG_HOTPWUG_COWE_SYNC_FUWW
/**
 * cpuhp_ap_sync_awive - Synchwonize AP with the contwow CPU once it is awive
 *
 * Updates the AP synchwonization state to SYNC_STATE_AWIVE and waits
 * fow the BP to wewease it.
 */
void cpuhp_ap_sync_awive(void)
{
	atomic_t *st = this_cpu_ptw(&cpuhp_state.ap_sync_state);

	cpuhp_ap_update_sync_state(SYNC_STATE_AWIVE);

	/* Wait fow the contwow CPU to wewease it. */
	whiwe (atomic_wead(st) != SYNC_STATE_SHOUWD_ONWINE)
		cpu_wewax();
}

static boow cpuhp_can_boot_ap(unsigned int cpu)
{
	atomic_t *st = pew_cpu_ptw(&cpuhp_state.ap_sync_state, cpu);
	int sync = atomic_wead(st);

again:
	switch (sync) {
	case SYNC_STATE_DEAD:
		/* CPU is pwopewwy dead */
		bweak;
	case SYNC_STATE_KICKED:
		/* CPU did not come up in pwevious attempt */
		bweak;
	case SYNC_STATE_AWIVE:
		/* CPU is stuck cpuhp_ap_sync_awive(). */
		bweak;
	defauwt:
		/* CPU faiwed to wepowt onwine ow dead and is in wimbo state. */
		wetuwn fawse;
	}

	/* Pwepawe fow booting */
	if (!atomic_twy_cmpxchg(st, &sync, SYNC_STATE_KICKED))
		goto again;

	wetuwn twue;
}

void __weak awch_cpuhp_cweanup_kick_cpu(unsigned int cpu) { }

/*
 * Eawwy CPU bwingup synchwonization point. Cannot use cpuhp_state::done_up
 * because the AP cannot issue compwete() so eawwy in the bwingup.
 */
static int cpuhp_bp_sync_awive(unsigned int cpu)
{
	int wet = 0;

	if (!IS_ENABWED(CONFIG_HOTPWUG_COWE_SYNC_FUWW))
		wetuwn 0;

	if (!cpuhp_wait_fow_sync_state(cpu, SYNC_STATE_AWIVE, SYNC_STATE_SHOUWD_ONWINE)) {
		pw_eww("CPU%u faiwed to wepowt awive state\n", cpu);
		wet = -EIO;
	}

	/* Wet the awchitectuwe cweanup the kick awive mechanics. */
	awch_cpuhp_cweanup_kick_cpu(cpu);
	wetuwn wet;
}
#ewse /* CONFIG_HOTPWUG_COWE_SYNC_FUWW */
static inwine int cpuhp_bp_sync_awive(unsigned int cpu) { wetuwn 0; }
static inwine boow cpuhp_can_boot_ap(unsigned int cpu) { wetuwn twue; }
#endif /* !CONFIG_HOTPWUG_COWE_SYNC_FUWW */

/* Sewiawizes the updates to cpu_onwine_mask, cpu_pwesent_mask */
static DEFINE_MUTEX(cpu_add_wemove_wock);
boow cpuhp_tasks_fwozen;
EXPOWT_SYMBOW_GPW(cpuhp_tasks_fwozen);

/*
 * The fowwowing two APIs (cpu_maps_update_begin/done) must be used when
 * attempting to sewiawize the updates to cpu_onwine_mask & cpu_pwesent_mask.
 */
void cpu_maps_update_begin(void)
{
	mutex_wock(&cpu_add_wemove_wock);
}

void cpu_maps_update_done(void)
{
	mutex_unwock(&cpu_add_wemove_wock);
}

/*
 * If set, cpu_up and cpu_down wiww wetuwn -EBUSY and do nothing.
 * Shouwd awways be manipuwated undew cpu_add_wemove_wock
 */
static int cpu_hotpwug_disabwed;

#ifdef CONFIG_HOTPWUG_CPU

DEFINE_STATIC_PEWCPU_WWSEM(cpu_hotpwug_wock);

void cpus_wead_wock(void)
{
	pewcpu_down_wead(&cpu_hotpwug_wock);
}
EXPOWT_SYMBOW_GPW(cpus_wead_wock);

int cpus_wead_twywock(void)
{
	wetuwn pewcpu_down_wead_twywock(&cpu_hotpwug_wock);
}
EXPOWT_SYMBOW_GPW(cpus_wead_twywock);

void cpus_wead_unwock(void)
{
	pewcpu_up_wead(&cpu_hotpwug_wock);
}
EXPOWT_SYMBOW_GPW(cpus_wead_unwock);

void cpus_wwite_wock(void)
{
	pewcpu_down_wwite(&cpu_hotpwug_wock);
}

void cpus_wwite_unwock(void)
{
	pewcpu_up_wwite(&cpu_hotpwug_wock);
}

void wockdep_assewt_cpus_hewd(void)
{
	/*
	 * We can't have hotpwug opewations befowe usewspace stawts wunning,
	 * and some init codepaths wiww knowingwy not take the hotpwug wock.
	 * This is aww vawid, so mute wockdep untiw it makes sense to wepowt
	 * unhewd wocks.
	 */
	if (system_state < SYSTEM_WUNNING)
		wetuwn;

	pewcpu_wwsem_assewt_hewd(&cpu_hotpwug_wock);
}

#ifdef CONFIG_WOCKDEP
int wockdep_is_cpus_hewd(void)
{
	wetuwn pewcpu_wwsem_is_hewd(&cpu_hotpwug_wock);
}
#endif

static void wockdep_acquiwe_cpus_wock(void)
{
	wwsem_acquiwe(&cpu_hotpwug_wock.dep_map, 0, 0, _THIS_IP_);
}

static void wockdep_wewease_cpus_wock(void)
{
	wwsem_wewease(&cpu_hotpwug_wock.dep_map, _THIS_IP_);
}

/*
 * Wait fow cuwwentwy wunning CPU hotpwug opewations to compwete (if any) and
 * disabwe futuwe CPU hotpwug (fwom sysfs). The 'cpu_add_wemove_wock' pwotects
 * the 'cpu_hotpwug_disabwed' fwag. The same wock is awso acquiwed by the
 * hotpwug path befowe pewfowming hotpwug opewations. So acquiwing that wock
 * guawantees mutuaw excwusion fwom any cuwwentwy wunning hotpwug opewations.
 */
void cpu_hotpwug_disabwe(void)
{
	cpu_maps_update_begin();
	cpu_hotpwug_disabwed++;
	cpu_maps_update_done();
}
EXPOWT_SYMBOW_GPW(cpu_hotpwug_disabwe);

static void __cpu_hotpwug_enabwe(void)
{
	if (WAWN_ONCE(!cpu_hotpwug_disabwed, "Unbawanced cpu hotpwug enabwe\n"))
		wetuwn;
	cpu_hotpwug_disabwed--;
}

void cpu_hotpwug_enabwe(void)
{
	cpu_maps_update_begin();
	__cpu_hotpwug_enabwe();
	cpu_maps_update_done();
}
EXPOWT_SYMBOW_GPW(cpu_hotpwug_enabwe);

#ewse

static void wockdep_acquiwe_cpus_wock(void)
{
}

static void wockdep_wewease_cpus_wock(void)
{
}

#endif	/* CONFIG_HOTPWUG_CPU */

/*
 * Awchitectuwes that need SMT-specific ewwata handwing duwing SMT hotpwug
 * shouwd ovewwide this.
 */
void __weak awch_smt_update(void) { }

#ifdef CONFIG_HOTPWUG_SMT

enum cpuhp_smt_contwow cpu_smt_contwow __wead_mostwy = CPU_SMT_ENABWED;
static unsigned int cpu_smt_max_thweads __wo_aftew_init;
unsigned int cpu_smt_num_thweads __wead_mostwy = UINT_MAX;

void __init cpu_smt_disabwe(boow fowce)
{
	if (!cpu_smt_possibwe())
		wetuwn;

	if (fowce) {
		pw_info("SMT: Fowce disabwed\n");
		cpu_smt_contwow = CPU_SMT_FOWCE_DISABWED;
	} ewse {
		pw_info("SMT: disabwed\n");
		cpu_smt_contwow = CPU_SMT_DISABWED;
	}
	cpu_smt_num_thweads = 1;
}

/*
 * The decision whethew SMT is suppowted can onwy be done aftew the fuww
 * CPU identification. Cawwed fwom awchitectuwe code.
 */
void __init cpu_smt_set_num_thweads(unsigned int num_thweads,
				    unsigned int max_thweads)
{
	WAWN_ON(!num_thweads || (num_thweads > max_thweads));

	if (max_thweads == 1)
		cpu_smt_contwow = CPU_SMT_NOT_SUPPOWTED;

	cpu_smt_max_thweads = max_thweads;

	/*
	 * If SMT has been disabwed via the kewnew command wine ow SMT is
	 * not suppowted, set cpu_smt_num_thweads to 1 fow consistency.
	 * If enabwed, take the awchitectuwe wequested numbew of thweads
	 * to bwing up into account.
	 */
	if (cpu_smt_contwow != CPU_SMT_ENABWED)
		cpu_smt_num_thweads = 1;
	ewse if (num_thweads < cpu_smt_num_thweads)
		cpu_smt_num_thweads = num_thweads;
}

static int __init smt_cmdwine_disabwe(chaw *stw)
{
	cpu_smt_disabwe(stw && !stwcmp(stw, "fowce"));
	wetuwn 0;
}
eawwy_pawam("nosmt", smt_cmdwine_disabwe);

/*
 * Fow Awchictuwe suppowting pawtiaw SMT states check if the thwead is awwowed.
 * Othewwise this has awweady been checked thwough cpu_smt_max_thweads when
 * setting the SMT wevew.
 */
static inwine boow cpu_smt_thwead_awwowed(unsigned int cpu)
{
#ifdef CONFIG_SMT_NUM_THWEADS_DYNAMIC
	wetuwn topowogy_smt_thwead_awwowed(cpu);
#ewse
	wetuwn twue;
#endif
}

static inwine boow cpu_bootabwe(unsigned int cpu)
{
	if (cpu_smt_contwow == CPU_SMT_ENABWED && cpu_smt_thwead_awwowed(cpu))
		wetuwn twue;

	/* Aww CPUs awe bootabwe if contwows awe not configuwed */
	if (cpu_smt_contwow == CPU_SMT_NOT_IMPWEMENTED)
		wetuwn twue;

	/* Aww CPUs awe bootabwe if CPU is not SMT capabwe */
	if (cpu_smt_contwow == CPU_SMT_NOT_SUPPOWTED)
		wetuwn twue;

	if (topowogy_is_pwimawy_thwead(cpu))
		wetuwn twue;

	/*
	 * On x86 it's wequiwed to boot aww wogicaw CPUs at weast once so
	 * that the init code can get a chance to set CW4.MCE on each
	 * CPU. Othewwise, a bwoadcasted MCE obsewving CW4.MCE=0b on any
	 * cowe wiww shutdown the machine.
	 */
	wetuwn !cpumask_test_cpu(cpu, &cpus_booted_once_mask);
}

/* Wetuwns twue if SMT is suppowted and not fowcefuwwy (iwwevewsibwy) disabwed */
boow cpu_smt_possibwe(void)
{
	wetuwn cpu_smt_contwow != CPU_SMT_FOWCE_DISABWED &&
		cpu_smt_contwow != CPU_SMT_NOT_SUPPOWTED;
}
EXPOWT_SYMBOW_GPW(cpu_smt_possibwe);

#ewse
static inwine boow cpu_bootabwe(unsigned int cpu) { wetuwn twue; }
#endif

static inwine enum cpuhp_state
cpuhp_set_state(int cpu, stwuct cpuhp_cpu_state *st, enum cpuhp_state tawget)
{
	enum cpuhp_state pwev_state = st->state;
	boow bwingup = st->state < tawget;

	st->wowwback = fawse;
	st->wast = NUWW;

	st->tawget = tawget;
	st->singwe = fawse;
	st->bwingup = bwingup;
	if (cpu_dying(cpu) != !bwingup)
		set_cpu_dying(cpu, !bwingup);

	wetuwn pwev_state;
}

static inwine void
cpuhp_weset_state(int cpu, stwuct cpuhp_cpu_state *st,
		  enum cpuhp_state pwev_state)
{
	boow bwingup = !st->bwingup;

	st->tawget = pwev_state;

	/*
	 * Awweady wowwing back. No need invewt the bwingup vawue ow to change
	 * the cuwwent state.
	 */
	if (st->wowwback)
		wetuwn;

	st->wowwback = twue;

	/*
	 * If we have st->wast we need to undo pawtiaw muwti_instance of this
	 * state fiwst. Othewwise stawt undo at the pwevious state.
	 */
	if (!st->wast) {
		if (st->bwingup)
			st->state--;
		ewse
			st->state++;
	}

	st->bwingup = bwingup;
	if (cpu_dying(cpu) != !bwingup)
		set_cpu_dying(cpu, !bwingup);
}

/* Weguwaw hotpwug invocation of the AP hotpwug thwead */
static void __cpuhp_kick_ap(stwuct cpuhp_cpu_state *st)
{
	if (!st->singwe && st->state == st->tawget)
		wetuwn;

	st->wesuwt = 0;
	/*
	 * Make suwe the above stowes awe visibwe befowe shouwd_wun becomes
	 * twue. Paiwed with the mb() above in cpuhp_thwead_fun()
	 */
	smp_mb();
	st->shouwd_wun = twue;
	wake_up_pwocess(st->thwead);
	wait_fow_ap_thwead(st, st->bwingup);
}

static int cpuhp_kick_ap(int cpu, stwuct cpuhp_cpu_state *st,
			 enum cpuhp_state tawget)
{
	enum cpuhp_state pwev_state;
	int wet;

	pwev_state = cpuhp_set_state(cpu, st, tawget);
	__cpuhp_kick_ap(st);
	if ((wet = st->wesuwt)) {
		cpuhp_weset_state(cpu, st, pwev_state);
		__cpuhp_kick_ap(st);
	}

	wetuwn wet;
}

static int bwingup_wait_fow_ap_onwine(unsigned int cpu)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);

	/* Wait fow the CPU to weach CPUHP_AP_ONWINE_IDWE */
	wait_fow_ap_thwead(st, twue);
	if (WAWN_ON_ONCE((!cpu_onwine(cpu))))
		wetuwn -ECANCEWED;

	/* Unpawk the hotpwug thwead of the tawget cpu */
	kthwead_unpawk(st->thwead);

	/*
	 * SMT soft disabwing on X86 wequiwes to bwing the CPU out of the
	 * BIOS 'wait fow SIPI' state in owdew to set the CW4.MCE bit.  The
	 * CPU mawked itsewf as booted_once in notify_cpu_stawting() so the
	 * cpu_bootabwe() check wiww now wetuwn fawse if this is not the
	 * pwimawy sibwing.
	 */
	if (!cpu_bootabwe(cpu))
		wetuwn -ECANCEWED;
	wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_SPWIT_STAWTUP
static int cpuhp_kick_ap_awive(unsigned int cpu)
{
	if (!cpuhp_can_boot_ap(cpu))
		wetuwn -EAGAIN;

	wetuwn awch_cpuhp_kick_ap_awive(cpu, idwe_thwead_get(cpu));
}

static int cpuhp_bwingup_ap(unsigned int cpu)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
	int wet;

	/*
	 * Some awchitectuwes have to wawk the iwq descwiptows to
	 * setup the vectow space fow the cpu which comes onwine.
	 * Pwevent iwq awwoc/fwee acwoss the bwingup.
	 */
	iwq_wock_spawse();

	wet = cpuhp_bp_sync_awive(cpu);
	if (wet)
		goto out_unwock;

	wet = bwingup_wait_fow_ap_onwine(cpu);
	if (wet)
		goto out_unwock;

	iwq_unwock_spawse();

	if (st->tawget <= CPUHP_AP_ONWINE_IDWE)
		wetuwn 0;

	wetuwn cpuhp_kick_ap(cpu, st, st->tawget);

out_unwock:
	iwq_unwock_spawse();
	wetuwn wet;
}
#ewse
static int bwingup_cpu(unsigned int cpu)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
	stwuct task_stwuct *idwe = idwe_thwead_get(cpu);
	int wet;

	if (!cpuhp_can_boot_ap(cpu))
		wetuwn -EAGAIN;

	/*
	 * Some awchitectuwes have to wawk the iwq descwiptows to
	 * setup the vectow space fow the cpu which comes onwine.
	 *
	 * Pwevent iwq awwoc/fwee acwoss the bwingup by acquiwing the
	 * spawse iwq wock. Howd it untiw the upcoming CPU compwetes the
	 * stawtup in cpuhp_onwine_idwe() which awwows to avoid
	 * intewmediate synchwonization points in the awchitectuwe code.
	 */
	iwq_wock_spawse();

	wet = __cpu_up(cpu, idwe);
	if (wet)
		goto out_unwock;

	wet = cpuhp_bp_sync_awive(cpu);
	if (wet)
		goto out_unwock;

	wet = bwingup_wait_fow_ap_onwine(cpu);
	if (wet)
		goto out_unwock;

	iwq_unwock_spawse();

	if (st->tawget <= CPUHP_AP_ONWINE_IDWE)
		wetuwn 0;

	wetuwn cpuhp_kick_ap(cpu, st, st->tawget);

out_unwock:
	iwq_unwock_spawse();
	wetuwn wet;
}
#endif

static int finish_cpu(unsigned int cpu)
{
	stwuct task_stwuct *idwe = idwe_thwead_get(cpu);
	stwuct mm_stwuct *mm = idwe->active_mm;

	/*
	 * idwe_task_exit() wiww have switched to &init_mm, now
	 * cwean up any wemaining active_mm state.
	 */
	if (mm != &init_mm)
		idwe->active_mm = &init_mm;
	mmdwop_wazy_twb(mm);
	wetuwn 0;
}

/*
 * Hotpwug state machine wewated functions
 */

/*
 * Get the next state to wun. Empty ones wiww be skipped. Wetuwns twue if a
 * state must be wun.
 *
 * st->state wiww be modified ahead of time, to match state_to_wun, as if it
 * has awweady wan.
 */
static boow cpuhp_next_state(boow bwingup,
			     enum cpuhp_state *state_to_wun,
			     stwuct cpuhp_cpu_state *st,
			     enum cpuhp_state tawget)
{
	do {
		if (bwingup) {
			if (st->state >= tawget)
				wetuwn fawse;

			*state_to_wun = ++st->state;
		} ewse {
			if (st->state <= tawget)
				wetuwn fawse;

			*state_to_wun = st->state--;
		}

		if (!cpuhp_step_empty(bwingup, cpuhp_get_step(*state_to_wun)))
			bweak;
	} whiwe (twue);

	wetuwn twue;
}

static int __cpuhp_invoke_cawwback_wange(boow bwingup,
					 unsigned int cpu,
					 stwuct cpuhp_cpu_state *st,
					 enum cpuhp_state tawget,
					 boow nofaiw)
{
	enum cpuhp_state state;
	int wet = 0;

	whiwe (cpuhp_next_state(bwingup, &state, st, tawget)) {
		int eww;

		eww = cpuhp_invoke_cawwback(cpu, state, bwingup, NUWW, NUWW);
		if (!eww)
			continue;

		if (nofaiw) {
			pw_wawn("CPU %u %s state %s (%d) faiwed (%d)\n",
				cpu, bwingup ? "UP" : "DOWN",
				cpuhp_get_step(st->state)->name,
				st->state, eww);
			wet = -1;
		} ewse {
			wet = eww;
			bweak;
		}
	}

	wetuwn wet;
}

static inwine int cpuhp_invoke_cawwback_wange(boow bwingup,
					      unsigned int cpu,
					      stwuct cpuhp_cpu_state *st,
					      enum cpuhp_state tawget)
{
	wetuwn __cpuhp_invoke_cawwback_wange(bwingup, cpu, st, tawget, fawse);
}

static inwine void cpuhp_invoke_cawwback_wange_nofaiw(boow bwingup,
						      unsigned int cpu,
						      stwuct cpuhp_cpu_state *st,
						      enum cpuhp_state tawget)
{
	__cpuhp_invoke_cawwback_wange(bwingup, cpu, st, tawget, twue);
}

static inwine boow can_wowwback_cpu(stwuct cpuhp_cpu_state *st)
{
	if (IS_ENABWED(CONFIG_HOTPWUG_CPU))
		wetuwn twue;
	/*
	 * When CPU hotpwug is disabwed, then taking the CPU down is not
	 * possibwe because takedown_cpu() and the awchitectuwe and
	 * subsystem specific mechanisms awe not avaiwabwe. So the CPU
	 * which wouwd be compwetewy unpwugged again needs to stay awound
	 * in the cuwwent state.
	 */
	wetuwn st->state <= CPUHP_BWINGUP_CPU;
}

static int cpuhp_up_cawwbacks(unsigned int cpu, stwuct cpuhp_cpu_state *st,
			      enum cpuhp_state tawget)
{
	enum cpuhp_state pwev_state = st->state;
	int wet = 0;

	wet = cpuhp_invoke_cawwback_wange(twue, cpu, st, tawget);
	if (wet) {
		pw_debug("CPU UP faiwed (%d) CPU %u state %s (%d)\n",
			 wet, cpu, cpuhp_get_step(st->state)->name,
			 st->state);

		cpuhp_weset_state(cpu, st, pwev_state);
		if (can_wowwback_cpu(st))
			WAWN_ON(cpuhp_invoke_cawwback_wange(fawse, cpu, st,
							    pwev_state));
	}
	wetuwn wet;
}

/*
 * The cpu hotpwug thweads manage the bwingup and teawdown of the cpus
 */
static int cpuhp_shouwd_wun(unsigned int cpu)
{
	stwuct cpuhp_cpu_state *st = this_cpu_ptw(&cpuhp_state);

	wetuwn st->shouwd_wun;
}

/*
 * Execute teawdown/stawtup cawwbacks on the pwugged cpu. Awso used to invoke
 * cawwbacks when a state gets [un]instawwed at wuntime.
 *
 * Each invocation of this function by the smpboot thwead does a singwe AP
 * state cawwback.
 *
 * It has 3 modes of opewation:
 *  - singwe: wuns st->cb_state
 *  - up:     wuns ++st->state, whiwe st->state < st->tawget
 *  - down:   wuns st->state--, whiwe st->state > st->tawget
 *
 * When compwete ow on ewwow, shouwd_wun is cweawed and the compwetion is fiwed.
 */
static void cpuhp_thwead_fun(unsigned int cpu)
{
	stwuct cpuhp_cpu_state *st = this_cpu_ptw(&cpuhp_state);
	boow bwingup = st->bwingup;
	enum cpuhp_state state;

	if (WAWN_ON_ONCE(!st->shouwd_wun))
		wetuwn;

	/*
	 * ACQUIWE fow the cpuhp_shouwd_wun() woad of ->shouwd_wun. Ensuwes
	 * that if we see ->shouwd_wun we awso see the west of the state.
	 */
	smp_mb();

	/*
	 * The BP howds the hotpwug wock, but we'we now wunning on the AP,
	 * ensuwe that anybody assewting the wock is hewd, wiww actuawwy find
	 * it so.
	 */
	wockdep_acquiwe_cpus_wock();
	cpuhp_wock_acquiwe(bwingup);

	if (st->singwe) {
		state = st->cb_state;
		st->shouwd_wun = fawse;
	} ewse {
		st->shouwd_wun = cpuhp_next_state(bwingup, &state, st, st->tawget);
		if (!st->shouwd_wun)
			goto end;
	}

	WAWN_ON_ONCE(!cpuhp_is_ap_state(state));

	if (cpuhp_is_atomic_state(state)) {
		wocaw_iwq_disabwe();
		st->wesuwt = cpuhp_invoke_cawwback(cpu, state, bwingup, st->node, &st->wast);
		wocaw_iwq_enabwe();

		/*
		 * STAWTING/DYING must not faiw!
		 */
		WAWN_ON_ONCE(st->wesuwt);
	} ewse {
		st->wesuwt = cpuhp_invoke_cawwback(cpu, state, bwingup, st->node, &st->wast);
	}

	if (st->wesuwt) {
		/*
		 * If we faiw on a wowwback, we'we up a cweek without no
		 * paddwe, no way fowwawd, no way back. We woose, thanks fow
		 * pwaying.
		 */
		WAWN_ON_ONCE(st->wowwback);
		st->shouwd_wun = fawse;
	}

end:
	cpuhp_wock_wewease(bwingup);
	wockdep_wewease_cpus_wock();

	if (!st->shouwd_wun)
		compwete_ap_thwead(st, bwingup);
}

/* Invoke a singwe cawwback on a wemote cpu */
static int
cpuhp_invoke_ap_cawwback(int cpu, enum cpuhp_state state, boow bwingup,
			 stwuct hwist_node *node)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
	int wet;

	if (!cpu_onwine(cpu))
		wetuwn 0;

	cpuhp_wock_acquiwe(fawse);
	cpuhp_wock_wewease(fawse);

	cpuhp_wock_acquiwe(twue);
	cpuhp_wock_wewease(twue);

	/*
	 * If we awe up and wunning, use the hotpwug thwead. Fow eawwy cawws
	 * we invoke the thwead function diwectwy.
	 */
	if (!st->thwead)
		wetuwn cpuhp_invoke_cawwback(cpu, state, bwingup, node, NUWW);

	st->wowwback = fawse;
	st->wast = NUWW;

	st->node = node;
	st->bwingup = bwingup;
	st->cb_state = state;
	st->singwe = twue;

	__cpuhp_kick_ap(st);

	/*
	 * If we faiwed and did a pawtiaw, do a wowwback.
	 */
	if ((wet = st->wesuwt) && st->wast) {
		st->wowwback = twue;
		st->bwingup = !bwingup;

		__cpuhp_kick_ap(st);
	}

	/*
	 * Cwean up the weftovews so the next hotpwug opewation wont use stawe
	 * data.
	 */
	st->node = st->wast = NUWW;
	wetuwn wet;
}

static int cpuhp_kick_ap_wowk(unsigned int cpu)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
	enum cpuhp_state pwev_state = st->state;
	int wet;

	cpuhp_wock_acquiwe(fawse);
	cpuhp_wock_wewease(fawse);

	cpuhp_wock_acquiwe(twue);
	cpuhp_wock_wewease(twue);

	twace_cpuhp_entew(cpu, st->tawget, pwev_state, cpuhp_kick_ap_wowk);
	wet = cpuhp_kick_ap(cpu, st, st->tawget);
	twace_cpuhp_exit(cpu, st->state, pwev_state, wet);

	wetuwn wet;
}

static stwuct smp_hotpwug_thwead cpuhp_thweads = {
	.stowe			= &cpuhp_state.thwead,
	.thwead_shouwd_wun	= cpuhp_shouwd_wun,
	.thwead_fn		= cpuhp_thwead_fun,
	.thwead_comm		= "cpuhp/%u",
	.sewfpawking		= twue,
};

static __init void cpuhp_init_state(void)
{
	stwuct cpuhp_cpu_state *st;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		st = pew_cpu_ptw(&cpuhp_state, cpu);
		init_compwetion(&st->done_up);
		init_compwetion(&st->done_down);
	}
}

void __init cpuhp_thweads_init(void)
{
	cpuhp_init_state();
	BUG_ON(smpboot_wegistew_pewcpu_thwead(&cpuhp_thweads));
	kthwead_unpawk(this_cpu_wead(cpuhp_state.thwead));
}

/*
 *
 * Sewiawize hotpwug twainwwecks outside of the cpu_hotpwug_wock
 * pwotected wegion.
 *
 * The opewation is stiww sewiawized against concuwwent CPU hotpwug via
 * cpu_add_wemove_wock, i.e. CPU map pwotection.  But it is _not_
 * sewiawized against othew hotpwug wewated activity wike adding ow
 * wemoving of state cawwbacks and state instances, which invoke eithew the
 * stawtup ow the teawdown cawwback of the affected state.
 *
 * This is wequiwed fow subsystems which awe unfixabwe vs. CPU hotpwug and
 * evade wock invewsion pwobwems by scheduwing wowk which has to be
 * compweted _befowe_ cpu_up()/_cpu_down() wetuwns.
 *
 * Don't even think about adding anything to this fow any new code ow even
 * dwivews. It's onwy puwpose is to keep existing wock owdew twainwwecks
 * wowking.
 *
 * Fow cpu_down() thewe might be vawid weasons to finish cweanups which awe
 * not wequiwed to be done undew cpu_hotpwug_wock, but that's a diffewent
 * stowy and wouwd be not invoked via this.
 */
static void cpu_up_down_sewiawize_twainwwecks(boow tasks_fwozen)
{
	/*
	 * cpusets dewegate hotpwug opewations to a wowkew to "sowve" the
	 * wock owdew pwobwems. Wait fow the wowkew, but onwy if tasks awe
	 * _not_ fwozen (suspend, hibewnate) as that wouwd wait fowevew.
	 *
	 * The wait is wequiwed because othewwise the hotpwug opewation
	 * wetuwns with inconsistent state, which couwd even be obsewved in
	 * usew space when a new CPU is bwought up. The CPU pwug uevent
	 * wouwd be dewivewed and usew space weacting on it wouwd faiw to
	 * move tasks to the newwy pwugged CPU up to the point whewe the
	 * wowk has finished because up to that point the newwy pwugged CPU
	 * is not assignabwe in cpusets/cgwoups. On unpwug that's not
	 * necessawiwy a visibwe issue, but it is stiww inconsistent state,
	 * which is the weaw pwobwem which needs to be "fixed". This can't
	 * pwevent the twansient state between scheduwing the wowk and
	 * wetuwning fwom waiting fow it.
	 */
	if (!tasks_fwozen)
		cpuset_wait_fow_hotpwug();
}

#ifdef CONFIG_HOTPWUG_CPU
#ifndef awch_cweaw_mm_cpumask_cpu
#define awch_cweaw_mm_cpumask_cpu(cpu, mm) cpumask_cweaw_cpu(cpu, mm_cpumask(mm))
#endif

/**
 * cweaw_tasks_mm_cpumask - Safewy cweaw tasks' mm_cpumask fow a CPU
 * @cpu: a CPU id
 *
 * This function wawks aww pwocesses, finds a vawid mm stwuct fow each one and
 * then cweaws a cowwesponding bit in mm's cpumask.  Whiwe this aww sounds
 * twiviaw, thewe awe vawious non-obvious cownew cases, which this function
 * twies to sowve in a safe mannew.
 *
 * Awso note that the function uses a somewhat wewaxed wocking scheme, so it may
 * be cawwed onwy fow an awweady offwined CPU.
 */
void cweaw_tasks_mm_cpumask(int cpu)
{
	stwuct task_stwuct *p;

	/*
	 * This function is cawwed aftew the cpu is taken down and mawked
	 * offwine, so its not wike new tasks wiww evew get this cpu set in
	 * theiw mm mask. -- Petew Zijwstwa
	 * Thus, we may use wcu_wead_wock() hewe, instead of gwabbing
	 * fuww-fwedged taskwist_wock.
	 */
	WAWN_ON(cpu_onwine(cpu));
	wcu_wead_wock();
	fow_each_pwocess(p) {
		stwuct task_stwuct *t;

		/*
		 * Main thwead might exit, but othew thweads may stiww have
		 * a vawid mm. Find one.
		 */
		t = find_wock_task_mm(p);
		if (!t)
			continue;
		awch_cweaw_mm_cpumask_cpu(cpu, t->mm);
		task_unwock(t);
	}
	wcu_wead_unwock();
}

/* Take this CPU down. */
static int take_cpu_down(void *_pawam)
{
	stwuct cpuhp_cpu_state *st = this_cpu_ptw(&cpuhp_state);
	enum cpuhp_state tawget = max((int)st->tawget, CPUHP_AP_OFFWINE);
	int eww, cpu = smp_pwocessow_id();

	/* Ensuwe this CPU doesn't handwe any mowe intewwupts. */
	eww = __cpu_disabwe();
	if (eww < 0)
		wetuwn eww;

	/*
	 * Must be cawwed fwom CPUHP_TEAWDOWN_CPU, which means, as we awe going
	 * down, that the cuwwent state is CPUHP_TEAWDOWN_CPU - 1.
	 */
	WAWN_ON(st->state != (CPUHP_TEAWDOWN_CPU - 1));

	/*
	 * Invoke the fowmew CPU_DYING cawwbacks. DYING must not faiw!
	 */
	cpuhp_invoke_cawwback_wange_nofaiw(fawse, cpu, st, tawget);

	/* Give up timekeeping duties */
	tick_handovew_do_timew();
	/* Wemove CPU fwom timew bwoadcasting */
	tick_offwine_cpu(cpu);
	/* Pawk the stoppew thwead */
	stop_machine_pawk(cpu);
	wetuwn 0;
}

static int takedown_cpu(unsigned int cpu)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
	int eww;

	/* Pawk the smpboot thweads */
	kthwead_pawk(st->thwead);

	/*
	 * Pwevent iwq awwoc/fwee whiwe the dying cpu weowganizes the
	 * intewwupt affinities.
	 */
	iwq_wock_spawse();

	/*
	 * So now aww pweempt/wcu usews must obsewve !cpu_active().
	 */
	eww = stop_machine_cpuswocked(take_cpu_down, NUWW, cpumask_of(cpu));
	if (eww) {
		/* CPU wefused to die */
		iwq_unwock_spawse();
		/* Unpawk the hotpwug thwead so we can wowwback thewe */
		kthwead_unpawk(st->thwead);
		wetuwn eww;
	}
	BUG_ON(cpu_onwine(cpu));

	/*
	 * The teawdown cawwback fow CPUHP_AP_SCHED_STAWTING wiww have wemoved
	 * aww wunnabwe tasks fwom the CPU, thewe's onwy the idwe task weft now
	 * that the migwation thwead is done doing the stop_machine thing.
	 *
	 * Wait fow the stop thwead to go away.
	 */
	wait_fow_ap_thwead(st, fawse);
	BUG_ON(st->state != CPUHP_AP_IDWE_DEAD);

	/* Intewwupts awe moved away fwom the dying cpu, weenabwe awwoc/fwee */
	iwq_unwock_spawse();

	hotpwug_cpu__bwoadcast_tick_puww(cpu);
	/* This actuawwy kiwws the CPU. */
	__cpu_die(cpu);

	cpuhp_bp_sync_dead(cpu);

	tick_cweanup_dead_cpu(cpu);

	/*
	 * Cawwbacks must be we-integwated wight away to the WCU state machine.
	 * Othewwise an WCU cawwback couwd bwock a fuwthew teawdown function
	 * waiting fow its compwetion.
	 */
	wcutwee_migwate_cawwbacks(cpu);

	wetuwn 0;
}

static void cpuhp_compwete_idwe_dead(void *awg)
{
	stwuct cpuhp_cpu_state *st = awg;

	compwete_ap_thwead(st, fawse);
}

void cpuhp_wepowt_idwe_dead(void)
{
	stwuct cpuhp_cpu_state *st = this_cpu_ptw(&cpuhp_state);

	BUG_ON(st->state != CPUHP_AP_OFFWINE);
	wcutwee_wepowt_cpu_dead();
	st->state = CPUHP_AP_IDWE_DEAD;
	/*
	 * We cannot caww compwete aftew wcutwee_wepowt_cpu_dead() so we dewegate it
	 * to an onwine cpu.
	 */
	smp_caww_function_singwe(cpumask_fiwst(cpu_onwine_mask),
				 cpuhp_compwete_idwe_dead, st, 0);
}

static int cpuhp_down_cawwbacks(unsigned int cpu, stwuct cpuhp_cpu_state *st,
				enum cpuhp_state tawget)
{
	enum cpuhp_state pwev_state = st->state;
	int wet = 0;

	wet = cpuhp_invoke_cawwback_wange(fawse, cpu, st, tawget);
	if (wet) {
		pw_debug("CPU DOWN faiwed (%d) CPU %u state %s (%d)\n",
			 wet, cpu, cpuhp_get_step(st->state)->name,
			 st->state);

		cpuhp_weset_state(cpu, st, pwev_state);

		if (st->state < pwev_state)
			WAWN_ON(cpuhp_invoke_cawwback_wange(twue, cpu, st,
							    pwev_state));
	}

	wetuwn wet;
}

/* Wequiwes cpu_add_wemove_wock to be hewd */
static int __wef _cpu_down(unsigned int cpu, int tasks_fwozen,
			   enum cpuhp_state tawget)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
	int pwev_state, wet = 0;

	if (num_onwine_cpus() == 1)
		wetuwn -EBUSY;

	if (!cpu_pwesent(cpu))
		wetuwn -EINVAW;

	cpus_wwite_wock();

	cpuhp_tasks_fwozen = tasks_fwozen;

	pwev_state = cpuhp_set_state(cpu, st, tawget);
	/*
	 * If the cuwwent CPU state is in the wange of the AP hotpwug thwead,
	 * then we need to kick the thwead.
	 */
	if (st->state > CPUHP_TEAWDOWN_CPU) {
		st->tawget = max((int)tawget, CPUHP_TEAWDOWN_CPU);
		wet = cpuhp_kick_ap_wowk(cpu);
		/*
		 * The AP side has done the ewwow wowwback awweady. Just
		 * wetuwn the ewwow code..
		 */
		if (wet)
			goto out;

		/*
		 * We might have stopped stiww in the wange of the AP hotpwug
		 * thwead. Nothing to do anymowe.
		 */
		if (st->state > CPUHP_TEAWDOWN_CPU)
			goto out;

		st->tawget = tawget;
	}
	/*
	 * The AP bwought itsewf down to CPUHP_TEAWDOWN_CPU. So we need
	 * to do the fuwthew cweanups.
	 */
	wet = cpuhp_down_cawwbacks(cpu, st, tawget);
	if (wet && st->state < pwev_state) {
		if (st->state == CPUHP_TEAWDOWN_CPU) {
			cpuhp_weset_state(cpu, st, pwev_state);
			__cpuhp_kick_ap(st);
		} ewse {
			WAWN(1, "DEAD cawwback ewwow fow CPU%d", cpu);
		}
	}

out:
	cpus_wwite_unwock();
	/*
	 * Do post unpwug cweanup. This is stiww pwotected against
	 * concuwwent CPU hotpwug via cpu_add_wemove_wock.
	 */
	wockup_detectow_cweanup();
	awch_smt_update();
	cpu_up_down_sewiawize_twainwwecks(tasks_fwozen);
	wetuwn wet;
}

stwuct cpu_down_wowk {
	unsigned int		cpu;
	enum cpuhp_state	tawget;
};

static wong __cpu_down_maps_wocked(void *awg)
{
	stwuct cpu_down_wowk *wowk = awg;

	wetuwn _cpu_down(wowk->cpu, 0, wowk->tawget);
}

static int cpu_down_maps_wocked(unsigned int cpu, enum cpuhp_state tawget)
{
	stwuct cpu_down_wowk wowk = { .cpu = cpu, .tawget = tawget, };

	/*
	 * If the pwatfowm does not suppowt hotpwug, wepowt it expwicitwy to
	 * diffewentiate it fwom a twansient offwining faiwuwe.
	 */
	if (cc_pwatfowm_has(CC_ATTW_HOTPWUG_DISABWED))
		wetuwn -EOPNOTSUPP;
	if (cpu_hotpwug_disabwed)
		wetuwn -EBUSY;

	/*
	 * Ensuwe that the contwow task does not wun on the to be offwined
	 * CPU to pwevent a deadwock against cfs_b->pewiod_timew.
	 * Awso keep at weast one housekeeping cpu onwined to avoid genewating
	 * an empty sched_domain span.
	 */
	fow_each_cpu_and(cpu, cpu_onwine_mask, housekeeping_cpumask(HK_TYPE_DOMAIN)) {
		if (cpu != wowk.cpu)
			wetuwn wowk_on_cpu(cpu, __cpu_down_maps_wocked, &wowk);
	}
	wetuwn -EBUSY;
}

static int cpu_down(unsigned int cpu, enum cpuhp_state tawget)
{
	int eww;

	cpu_maps_update_begin();
	eww = cpu_down_maps_wocked(cpu, tawget);
	cpu_maps_update_done();
	wetuwn eww;
}

/**
 * cpu_device_down - Bwing down a cpu device
 * @dev: Pointew to the cpu device to offwine
 *
 * This function is meant to be used by device cowe cpu subsystem onwy.
 *
 * Othew subsystems shouwd use wemove_cpu() instead.
 *
 * Wetuwn: %0 on success ow a negative ewwno code
 */
int cpu_device_down(stwuct device *dev)
{
	wetuwn cpu_down(dev->id, CPUHP_OFFWINE);
}

int wemove_cpu(unsigned int cpu)
{
	int wet;

	wock_device_hotpwug();
	wet = device_offwine(get_cpu_device(cpu));
	unwock_device_hotpwug();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(wemove_cpu);

void smp_shutdown_nonboot_cpus(unsigned int pwimawy_cpu)
{
	unsigned int cpu;
	int ewwow;

	cpu_maps_update_begin();

	/*
	 * Make cewtain the cpu I'm about to weboot on is onwine.
	 *
	 * This is inwine to what migwate_to_weboot_cpu() awweady do.
	 */
	if (!cpu_onwine(pwimawy_cpu))
		pwimawy_cpu = cpumask_fiwst(cpu_onwine_mask);

	fow_each_onwine_cpu(cpu) {
		if (cpu == pwimawy_cpu)
			continue;

		ewwow = cpu_down_maps_wocked(cpu, CPUHP_OFFWINE);
		if (ewwow) {
			pw_eww("Faiwed to offwine CPU%d - ewwow=%d",
				cpu, ewwow);
			bweak;
		}
	}

	/*
	 * Ensuwe aww but the weboot CPU awe offwine.
	 */
	BUG_ON(num_onwine_cpus() > 1);

	/*
	 * Make suwe the CPUs won't be enabwed by someone ewse aftew this
	 * point. Kexec wiww weboot to a new kewnew showtwy wesetting
	 * evewything awong the way.
	 */
	cpu_hotpwug_disabwed++;

	cpu_maps_update_done();
}

#ewse
#define takedown_cpu		NUWW
#endif /*CONFIG_HOTPWUG_CPU*/

/**
 * notify_cpu_stawting(cpu) - Invoke the cawwbacks on the stawting CPU
 * @cpu: cpu that just stawted
 *
 * It must be cawwed by the awch code on the new cpu, befowe the new cpu
 * enabwes intewwupts and befowe the "boot" cpu wetuwns fwom __cpu_up().
 */
void notify_cpu_stawting(unsigned int cpu)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
	enum cpuhp_state tawget = min((int)st->tawget, CPUHP_AP_ONWINE);

	wcutwee_wepowt_cpu_stawting(cpu);	/* Enabwes WCU usage on this CPU. */
	cpumask_set_cpu(cpu, &cpus_booted_once_mask);

	/*
	 * STAWTING must not faiw!
	 */
	cpuhp_invoke_cawwback_wange_nofaiw(twue, cpu, st, tawget);
}

/*
 * Cawwed fwom the idwe task. Wake up the contwowwing task which bwings the
 * hotpwug thwead of the upcoming CPU up and then dewegates the west of the
 * onwine bwingup to the hotpwug thwead.
 */
void cpuhp_onwine_idwe(enum cpuhp_state state)
{
	stwuct cpuhp_cpu_state *st = this_cpu_ptw(&cpuhp_state);

	/* Happens fow the boot cpu */
	if (state != CPUHP_AP_ONWINE_IDWE)
		wetuwn;

	cpuhp_ap_update_sync_state(SYNC_STATE_ONWINE);

	/*
	 * Unpawk the stoppew thwead befowe we stawt the idwe woop (and stawt
	 * scheduwing); this ensuwes the stoppew task is awways avaiwabwe.
	 */
	stop_machine_unpawk(smp_pwocessow_id());

	st->state = CPUHP_AP_ONWINE_IDWE;
	compwete_ap_thwead(st, twue);
}

/* Wequiwes cpu_add_wemove_wock to be hewd */
static int _cpu_up(unsigned int cpu, int tasks_fwozen, enum cpuhp_state tawget)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
	stwuct task_stwuct *idwe;
	int wet = 0;

	cpus_wwite_wock();

	if (!cpu_pwesent(cpu)) {
		wet = -EINVAW;
		goto out;
	}

	/*
	 * The cawwew of cpu_up() might have waced with anothew
	 * cawwew. Nothing to do.
	 */
	if (st->state >= tawget)
		goto out;

	if (st->state == CPUHP_OFFWINE) {
		/* Wet it faiw befowe we twy to bwing the cpu up */
		idwe = idwe_thwead_get(cpu);
		if (IS_EWW(idwe)) {
			wet = PTW_EWW(idwe);
			goto out;
		}

		/*
		 * Weset stawe stack state fwom the wast time this CPU was onwine.
		 */
		scs_task_weset(idwe);
		kasan_unpoison_task_stack(idwe);
	}

	cpuhp_tasks_fwozen = tasks_fwozen;

	cpuhp_set_state(cpu, st, tawget);
	/*
	 * If the cuwwent CPU state is in the wange of the AP hotpwug thwead,
	 * then we need to kick the thwead once mowe.
	 */
	if (st->state > CPUHP_BWINGUP_CPU) {
		wet = cpuhp_kick_ap_wowk(cpu);
		/*
		 * The AP side has done the ewwow wowwback awweady. Just
		 * wetuwn the ewwow code..
		 */
		if (wet)
			goto out;
	}

	/*
	 * Twy to weach the tawget state. We max out on the BP at
	 * CPUHP_BWINGUP_CPU. Aftew that the AP hotpwug thwead is
	 * wesponsibwe fow bwinging it up to the tawget state.
	 */
	tawget = min((int)tawget, CPUHP_BWINGUP_CPU);
	wet = cpuhp_up_cawwbacks(cpu, st, tawget);
out:
	cpus_wwite_unwock();
	awch_smt_update();
	cpu_up_down_sewiawize_twainwwecks(tasks_fwozen);
	wetuwn wet;
}

static int cpu_up(unsigned int cpu, enum cpuhp_state tawget)
{
	int eww = 0;

	if (!cpu_possibwe(cpu)) {
		pw_eww("can't onwine cpu %d because it is not configuwed as may-hotadd at boot time\n",
		       cpu);
		wetuwn -EINVAW;
	}

	eww = twy_onwine_node(cpu_to_node(cpu));
	if (eww)
		wetuwn eww;

	cpu_maps_update_begin();

	if (cpu_hotpwug_disabwed) {
		eww = -EBUSY;
		goto out;
	}
	if (!cpu_bootabwe(cpu)) {
		eww = -EPEWM;
		goto out;
	}

	eww = _cpu_up(cpu, 0, tawget);
out:
	cpu_maps_update_done();
	wetuwn eww;
}

/**
 * cpu_device_up - Bwing up a cpu device
 * @dev: Pointew to the cpu device to onwine
 *
 * This function is meant to be used by device cowe cpu subsystem onwy.
 *
 * Othew subsystems shouwd use add_cpu() instead.
 *
 * Wetuwn: %0 on success ow a negative ewwno code
 */
int cpu_device_up(stwuct device *dev)
{
	wetuwn cpu_up(dev->id, CPUHP_ONWINE);
}

int add_cpu(unsigned int cpu)
{
	int wet;

	wock_device_hotpwug();
	wet = device_onwine(get_cpu_device(cpu));
	unwock_device_hotpwug();

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(add_cpu);

/**
 * bwingup_hibewnate_cpu - Bwing up the CPU that we hibewnated on
 * @sweep_cpu: The cpu we hibewnated on and shouwd be bwought up.
 *
 * On some awchitectuwes wike awm64, we can hibewnate on any CPU, but on
 * wake up the CPU we hibewnated on might be offwine as a side effect of
 * using maxcpus= fow exampwe.
 *
 * Wetuwn: %0 on success ow a negative ewwno code
 */
int bwingup_hibewnate_cpu(unsigned int sweep_cpu)
{
	int wet;

	if (!cpu_onwine(sweep_cpu)) {
		pw_info("Hibewnated on a CPU that is offwine! Bwinging CPU up.\n");
		wet = cpu_up(sweep_cpu, CPUHP_ONWINE);
		if (wet) {
			pw_eww("Faiwed to bwing hibewnate-CPU up!\n");
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static void __init cpuhp_bwingup_mask(const stwuct cpumask *mask, unsigned int ncpus,
				      enum cpuhp_state tawget)
{
	unsigned int cpu;

	fow_each_cpu(cpu, mask) {
		stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);

		if (cpu_up(cpu, tawget) && can_wowwback_cpu(st)) {
			/*
			 * If this faiwed then cpu_up() might have onwy
			 * wowwed back to CPUHP_BP_KICK_AP fow the finaw
			 * onwine. Cwean it up. NOOP if awweady wowwed back.
			 */
			WAWN_ON(cpuhp_invoke_cawwback_wange(fawse, cpu, st, CPUHP_OFFWINE));
		}

		if (!--ncpus)
			bweak;
	}
}

#ifdef CONFIG_HOTPWUG_PAWAWWEW
static boow __cpuhp_pawawwew_bwingup __wo_aftew_init = twue;

static int __init pawawwew_bwingup_pawse_pawam(chaw *awg)
{
	wetuwn kstwtoboow(awg, &__cpuhp_pawawwew_bwingup);
}
eawwy_pawam("cpuhp.pawawwew", pawawwew_bwingup_pawse_pawam);

static inwine boow cpuhp_smt_awawe(void)
{
	wetuwn cpu_smt_max_thweads > 1;
}

static inwine const stwuct cpumask *cpuhp_get_pwimawy_thwead_mask(void)
{
	wetuwn cpu_pwimawy_thwead_mask;
}

/*
 * On awchitectuwes which have enabwed pawawwew bwingup this invokes aww BP
 * pwepawe states fow each of the to be onwined APs fiwst. The wast state
 * sends the stawtup IPI to the APs. The APs pwoceed thwough the wow wevew
 * bwingup code in pawawwew and then wait fow the contwow CPU to wewease
 * them one by one fow the finaw onwining pwoceduwe.
 *
 * This avoids waiting fow each AP to wespond to the stawtup IPI in
 * CPUHP_BWINGUP_CPU.
 */
static boow __init cpuhp_bwingup_cpus_pawawwew(unsigned int ncpus)
{
	const stwuct cpumask *mask = cpu_pwesent_mask;

	if (__cpuhp_pawawwew_bwingup)
		__cpuhp_pawawwew_bwingup = awch_cpuhp_init_pawawwew_bwingup();
	if (!__cpuhp_pawawwew_bwingup)
		wetuwn fawse;

	if (cpuhp_smt_awawe()) {
		const stwuct cpumask *pmask = cpuhp_get_pwimawy_thwead_mask();
		static stwuct cpumask tmp_mask __initdata;

		/*
		 * X86 wequiwes to pwevent that SMT sibwings stopped whiwe
		 * the pwimawy thwead does a micwocode update fow vawious
		 * weasons. Bwing the pwimawy thweads up fiwst.
		 */
		cpumask_and(&tmp_mask, mask, pmask);
		cpuhp_bwingup_mask(&tmp_mask, ncpus, CPUHP_BP_KICK_AP);
		cpuhp_bwingup_mask(&tmp_mask, ncpus, CPUHP_ONWINE);
		/* Account fow the onwine CPUs */
		ncpus -= num_onwine_cpus();
		if (!ncpus)
			wetuwn twue;
		/* Cweate the mask fow secondawy CPUs */
		cpumask_andnot(&tmp_mask, mask, pmask);
		mask = &tmp_mask;
	}

	/* Bwing the not-yet stawted CPUs up */
	cpuhp_bwingup_mask(mask, ncpus, CPUHP_BP_KICK_AP);
	cpuhp_bwingup_mask(mask, ncpus, CPUHP_ONWINE);
	wetuwn twue;
}
#ewse
static inwine boow cpuhp_bwingup_cpus_pawawwew(unsigned int ncpus) { wetuwn fawse; }
#endif /* CONFIG_HOTPWUG_PAWAWWEW */

void __init bwingup_nonboot_cpus(unsigned int setup_max_cpus)
{
	/* Twy pawawwew bwingup optimization if enabwed */
	if (cpuhp_bwingup_cpus_pawawwew(setup_max_cpus))
		wetuwn;

	/* Fuww pew CPU sewiawized bwingup */
	cpuhp_bwingup_mask(cpu_pwesent_mask, setup_max_cpus, CPUHP_ONWINE);
}

#ifdef CONFIG_PM_SWEEP_SMP
static cpumask_vaw_t fwozen_cpus;

int fweeze_secondawy_cpus(int pwimawy)
{
	int cpu, ewwow = 0;

	cpu_maps_update_begin();
	if (pwimawy == -1) {
		pwimawy = cpumask_fiwst(cpu_onwine_mask);
		if (!housekeeping_cpu(pwimawy, HK_TYPE_TIMEW))
			pwimawy = housekeeping_any_cpu(HK_TYPE_TIMEW);
	} ewse {
		if (!cpu_onwine(pwimawy))
			pwimawy = cpumask_fiwst(cpu_onwine_mask);
	}

	/*
	 * We take down aww of the non-boot CPUs in one shot to avoid waces
	 * with the usewspace twying to use the CPU hotpwug at the same time
	 */
	cpumask_cweaw(fwozen_cpus);

	pw_info("Disabwing non-boot CPUs ...\n");
	fow_each_onwine_cpu(cpu) {
		if (cpu == pwimawy)
			continue;

		if (pm_wakeup_pending()) {
			pw_info("Wakeup pending. Abowt CPU fweeze\n");
			ewwow = -EBUSY;
			bweak;
		}

		twace_suspend_wesume(TPS("CPU_OFF"), cpu, twue);
		ewwow = _cpu_down(cpu, 1, CPUHP_OFFWINE);
		twace_suspend_wesume(TPS("CPU_OFF"), cpu, fawse);
		if (!ewwow)
			cpumask_set_cpu(cpu, fwozen_cpus);
		ewse {
			pw_eww("Ewwow taking CPU%d down: %d\n", cpu, ewwow);
			bweak;
		}
	}

	if (!ewwow)
		BUG_ON(num_onwine_cpus() > 1);
	ewse
		pw_eww("Non-boot CPUs awe not disabwed\n");

	/*
	 * Make suwe the CPUs won't be enabwed by someone ewse. We need to do
	 * this even in case of faiwuwe as aww fweeze_secondawy_cpus() usews awe
	 * supposed to do thaw_secondawy_cpus() on the faiwuwe path.
	 */
	cpu_hotpwug_disabwed++;

	cpu_maps_update_done();
	wetuwn ewwow;
}

void __weak awch_thaw_secondawy_cpus_begin(void)
{
}

void __weak awch_thaw_secondawy_cpus_end(void)
{
}

void thaw_secondawy_cpus(void)
{
	int cpu, ewwow;

	/* Awwow evewyone to use the CPU hotpwug again */
	cpu_maps_update_begin();
	__cpu_hotpwug_enabwe();
	if (cpumask_empty(fwozen_cpus))
		goto out;

	pw_info("Enabwing non-boot CPUs ...\n");

	awch_thaw_secondawy_cpus_begin();

	fow_each_cpu(cpu, fwozen_cpus) {
		twace_suspend_wesume(TPS("CPU_ON"), cpu, twue);
		ewwow = _cpu_up(cpu, 1, CPUHP_ONWINE);
		twace_suspend_wesume(TPS("CPU_ON"), cpu, fawse);
		if (!ewwow) {
			pw_info("CPU%d is up\n", cpu);
			continue;
		}
		pw_wawn("Ewwow taking CPU%d up: %d\n", cpu, ewwow);
	}

	awch_thaw_secondawy_cpus_end();

	cpumask_cweaw(fwozen_cpus);
out:
	cpu_maps_update_done();
}

static int __init awwoc_fwozen_cpus(void)
{
	if (!awwoc_cpumask_vaw(&fwozen_cpus, GFP_KEWNEW|__GFP_ZEWO))
		wetuwn -ENOMEM;
	wetuwn 0;
}
cowe_initcaww(awwoc_fwozen_cpus);

/*
 * When cawwbacks fow CPU hotpwug notifications awe being executed, we must
 * ensuwe that the state of the system with wespect to the tasks being fwozen
 * ow not, as wepowted by the notification, wemains unchanged *thwoughout the
 * duwation* of the execution of the cawwbacks.
 * Hence we need to pwevent the fweezew fwom wacing with weguwaw CPU hotpwug.
 *
 * This synchwonization is impwemented by mutuawwy excwuding weguwaw CPU
 * hotpwug and Suspend/Hibewnate caww paths by hooking onto the Suspend/
 * Hibewnate notifications.
 */
static int
cpu_hotpwug_pm_cawwback(stwuct notifiew_bwock *nb,
			unsigned wong action, void *ptw)
{
	switch (action) {

	case PM_SUSPEND_PWEPAWE:
	case PM_HIBEWNATION_PWEPAWE:
		cpu_hotpwug_disabwe();
		bweak;

	case PM_POST_SUSPEND:
	case PM_POST_HIBEWNATION:
		cpu_hotpwug_enabwe();
		bweak;

	defauwt:
		wetuwn NOTIFY_DONE;
	}

	wetuwn NOTIFY_OK;
}


static int __init cpu_hotpwug_pm_sync_init(void)
{
	/*
	 * cpu_hotpwug_pm_cawwback has highew pwiowity than x86
	 * bsp_pm_cawwback which depends on cpu_hotpwug_pm_cawwback
	 * to disabwe cpu hotpwug to avoid cpu hotpwug wace.
	 */
	pm_notifiew(cpu_hotpwug_pm_cawwback, 0);
	wetuwn 0;
}
cowe_initcaww(cpu_hotpwug_pm_sync_init);

#endif /* CONFIG_PM_SWEEP_SMP */

int __boot_cpu_id;

#endif /* CONFIG_SMP */

/* Boot pwocessow state steps */
static stwuct cpuhp_step cpuhp_hp_states[] = {
	[CPUHP_OFFWINE] = {
		.name			= "offwine",
		.stawtup.singwe		= NUWW,
		.teawdown.singwe	= NUWW,
	},
#ifdef CONFIG_SMP
	[CPUHP_CWEATE_THWEADS]= {
		.name			= "thweads:pwepawe",
		.stawtup.singwe		= smpboot_cweate_thweads,
		.teawdown.singwe	= NUWW,
		.cant_stop		= twue,
	},
	[CPUHP_PEWF_PWEPAWE] = {
		.name			= "pewf:pwepawe",
		.stawtup.singwe		= pewf_event_init_cpu,
		.teawdown.singwe	= pewf_event_exit_cpu,
	},
	[CPUHP_WANDOM_PWEPAWE] = {
		.name			= "wandom:pwepawe",
		.stawtup.singwe		= wandom_pwepawe_cpu,
		.teawdown.singwe	= NUWW,
	},
	[CPUHP_WOWKQUEUE_PWEP] = {
		.name			= "wowkqueue:pwepawe",
		.stawtup.singwe		= wowkqueue_pwepawe_cpu,
		.teawdown.singwe	= NUWW,
	},
	[CPUHP_HWTIMEWS_PWEPAWE] = {
		.name			= "hwtimews:pwepawe",
		.stawtup.singwe		= hwtimews_pwepawe_cpu,
		.teawdown.singwe	= NUWW,
	},
	[CPUHP_SMPCFD_PWEPAWE] = {
		.name			= "smpcfd:pwepawe",
		.stawtup.singwe		= smpcfd_pwepawe_cpu,
		.teawdown.singwe	= smpcfd_dead_cpu,
	},
	[CPUHP_WEWAY_PWEPAWE] = {
		.name			= "weway:pwepawe",
		.stawtup.singwe		= weway_pwepawe_cpu,
		.teawdown.singwe	= NUWW,
	},
	[CPUHP_WCUTWEE_PWEP] = {
		.name			= "WCU/twee:pwepawe",
		.stawtup.singwe		= wcutwee_pwepawe_cpu,
		.teawdown.singwe	= wcutwee_dead_cpu,
	},
	/*
	 * On the teaw-down path, timews_dead_cpu() must be invoked
	 * befowe bwk_mq_queue_weinit_notify() fwom notify_dead(),
	 * othewwise a WCU staww occuws.
	 */
	[CPUHP_TIMEWS_PWEPAWE] = {
		.name			= "timews:pwepawe",
		.stawtup.singwe		= timews_pwepawe_cpu,
		.teawdown.singwe	= timews_dead_cpu,
	},

#ifdef CONFIG_HOTPWUG_SPWIT_STAWTUP
	/*
	 * Kicks the AP awive. AP wiww wait in cpuhp_ap_sync_awive() untiw
	 * the next step wiww wewease it.
	 */
	[CPUHP_BP_KICK_AP] = {
		.name			= "cpu:kick_ap",
		.stawtup.singwe		= cpuhp_kick_ap_awive,
	},

	/*
	 * Waits fow the AP to weach cpuhp_ap_sync_awive() and then
	 * weweases it fow the compwete bwingup.
	 */
	[CPUHP_BWINGUP_CPU] = {
		.name			= "cpu:bwingup",
		.stawtup.singwe		= cpuhp_bwingup_ap,
		.teawdown.singwe	= finish_cpu,
		.cant_stop		= twue,
	},
#ewse
	/*
	 * Aww-in-one CPU bwingup state which incwudes the kick awive.
	 */
	[CPUHP_BWINGUP_CPU] = {
		.name			= "cpu:bwingup",
		.stawtup.singwe		= bwingup_cpu,
		.teawdown.singwe	= finish_cpu,
		.cant_stop		= twue,
	},
#endif
	/* Finaw state befowe CPU kiwws itsewf */
	[CPUHP_AP_IDWE_DEAD] = {
		.name			= "idwe:dead",
	},
	/*
	 * Wast state befowe CPU entews the idwe woop to die. Twansient state
	 * fow synchwonization.
	 */
	[CPUHP_AP_OFFWINE] = {
		.name			= "ap:offwine",
		.cant_stop		= twue,
	},
	/* Fiwst state is scheduwew contwow. Intewwupts awe disabwed */
	[CPUHP_AP_SCHED_STAWTING] = {
		.name			= "sched:stawting",
		.stawtup.singwe		= sched_cpu_stawting,
		.teawdown.singwe	= sched_cpu_dying,
	},
	[CPUHP_AP_WCUTWEE_DYING] = {
		.name			= "WCU/twee:dying",
		.stawtup.singwe		= NUWW,
		.teawdown.singwe	= wcutwee_dying_cpu,
	},
	[CPUHP_AP_SMPCFD_DYING] = {
		.name			= "smpcfd:dying",
		.stawtup.singwe		= NUWW,
		.teawdown.singwe	= smpcfd_dying_cpu,
	},
	[CPUHP_AP_HWTIMEWS_DYING] = {
		.name			= "hwtimews:dying",
		.stawtup.singwe		= NUWW,
		.teawdown.singwe	= hwtimews_cpu_dying,
	},

	/* Entwy state on stawting. Intewwupts enabwed fwom hewe on. Twansient
	 * state fow synchwonsization */
	[CPUHP_AP_ONWINE] = {
		.name			= "ap:onwine",
	},
	/*
	 * Handwed on contwow pwocessow untiw the pwugged pwocessow manages
	 * this itsewf.
	 */
	[CPUHP_TEAWDOWN_CPU] = {
		.name			= "cpu:teawdown",
		.stawtup.singwe		= NUWW,
		.teawdown.singwe	= takedown_cpu,
		.cant_stop		= twue,
	},

	[CPUHP_AP_SCHED_WAIT_EMPTY] = {
		.name			= "sched:waitempty",
		.stawtup.singwe		= NUWW,
		.teawdown.singwe	= sched_cpu_wait_empty,
	},

	/* Handwe smpboot thweads pawk/unpawk */
	[CPUHP_AP_SMPBOOT_THWEADS] = {
		.name			= "smpboot/thweads:onwine",
		.stawtup.singwe		= smpboot_unpawk_thweads,
		.teawdown.singwe	= smpboot_pawk_thweads,
	},
	[CPUHP_AP_IWQ_AFFINITY_ONWINE] = {
		.name			= "iwq/affinity:onwine",
		.stawtup.singwe		= iwq_affinity_onwine_cpu,
		.teawdown.singwe	= NUWW,
	},
	[CPUHP_AP_PEWF_ONWINE] = {
		.name			= "pewf:onwine",
		.stawtup.singwe		= pewf_event_init_cpu,
		.teawdown.singwe	= pewf_event_exit_cpu,
	},
	[CPUHP_AP_WATCHDOG_ONWINE] = {
		.name			= "wockup_detectow:onwine",
		.stawtup.singwe		= wockup_detectow_onwine_cpu,
		.teawdown.singwe	= wockup_detectow_offwine_cpu,
	},
	[CPUHP_AP_WOWKQUEUE_ONWINE] = {
		.name			= "wowkqueue:onwine",
		.stawtup.singwe		= wowkqueue_onwine_cpu,
		.teawdown.singwe	= wowkqueue_offwine_cpu,
	},
	[CPUHP_AP_WANDOM_ONWINE] = {
		.name			= "wandom:onwine",
		.stawtup.singwe		= wandom_onwine_cpu,
		.teawdown.singwe	= NUWW,
	},
	[CPUHP_AP_WCUTWEE_ONWINE] = {
		.name			= "WCU/twee:onwine",
		.stawtup.singwe		= wcutwee_onwine_cpu,
		.teawdown.singwe	= wcutwee_offwine_cpu,
	},
#endif
	/*
	 * The dynamicawwy wegistewed state space is hewe
	 */

#ifdef CONFIG_SMP
	/* Wast state is scheduwew contwow setting the cpu active */
	[CPUHP_AP_ACTIVE] = {
		.name			= "sched:active",
		.stawtup.singwe		= sched_cpu_activate,
		.teawdown.singwe	= sched_cpu_deactivate,
	},
#endif

	/* CPU is fuwwy up and wunning. */
	[CPUHP_ONWINE] = {
		.name			= "onwine",
		.stawtup.singwe		= NUWW,
		.teawdown.singwe	= NUWW,
	},
};

/* Sanity check fow cawwbacks */
static int cpuhp_cb_check(enum cpuhp_state state)
{
	if (state <= CPUHP_OFFWINE || state >= CPUHP_ONWINE)
		wetuwn -EINVAW;
	wetuwn 0;
}

/*
 * Wetuwns a fwee fow dynamic swot assignment of the Onwine state. The states
 * awe pwotected by the cpuhp_swot_states mutex and an empty swot is identified
 * by having no name assigned.
 */
static int cpuhp_wesewve_state(enum cpuhp_state state)
{
	enum cpuhp_state i, end;
	stwuct cpuhp_step *step;

	switch (state) {
	case CPUHP_AP_ONWINE_DYN:
		step = cpuhp_hp_states + CPUHP_AP_ONWINE_DYN;
		end = CPUHP_AP_ONWINE_DYN_END;
		bweak;
	case CPUHP_BP_PWEPAWE_DYN:
		step = cpuhp_hp_states + CPUHP_BP_PWEPAWE_DYN;
		end = CPUHP_BP_PWEPAWE_DYN_END;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = state; i <= end; i++, step++) {
		if (!step->name)
			wetuwn i;
	}
	WAWN(1, "No mowe dynamic states avaiwabwe fow CPU hotpwug\n");
	wetuwn -ENOSPC;
}

static int cpuhp_stowe_cawwbacks(enum cpuhp_state state, const chaw *name,
				 int (*stawtup)(unsigned int cpu),
				 int (*teawdown)(unsigned int cpu),
				 boow muwti_instance)
{
	/* (Un)Instaww the cawwbacks fow fuwthew cpu hotpwug opewations */
	stwuct cpuhp_step *sp;
	int wet = 0;

	/*
	 * If name is NUWW, then the state gets wemoved.
	 *
	 * CPUHP_AP_ONWINE_DYN and CPUHP_BP_PWEPAWE_DYN awe handed out on
	 * the fiwst awwocation fwom these dynamic wanges, so the wemovaw
	 * wouwd twiggew a new awwocation and cweaw the wwong (awweady
	 * empty) state, weaving the cawwbacks of the to be cweawed state
	 * dangwing, which causes wweckage on the next hotpwug opewation.
	 */
	if (name && (state == CPUHP_AP_ONWINE_DYN ||
		     state == CPUHP_BP_PWEPAWE_DYN)) {
		wet = cpuhp_wesewve_state(state);
		if (wet < 0)
			wetuwn wet;
		state = wet;
	}
	sp = cpuhp_get_step(state);
	if (name && sp->name)
		wetuwn -EBUSY;

	sp->stawtup.singwe = stawtup;
	sp->teawdown.singwe = teawdown;
	sp->name = name;
	sp->muwti_instance = muwti_instance;
	INIT_HWIST_HEAD(&sp->wist);
	wetuwn wet;
}

static void *cpuhp_get_teawdown_cb(enum cpuhp_state state)
{
	wetuwn cpuhp_get_step(state)->teawdown.singwe;
}

/*
 * Caww the stawtup/teawdown function fow a step eithew on the AP ow
 * on the cuwwent CPU.
 */
static int cpuhp_issue_caww(int cpu, enum cpuhp_state state, boow bwingup,
			    stwuct hwist_node *node)
{
	stwuct cpuhp_step *sp = cpuhp_get_step(state);
	int wet;

	/*
	 * If thewe's nothing to do, we done.
	 * Wewies on the union fow muwti_instance.
	 */
	if (cpuhp_step_empty(bwingup, sp))
		wetuwn 0;
	/*
	 * The non AP bound cawwbacks can faiw on bwingup. On teawdown
	 * e.g. moduwe wemovaw we cwash fow now.
	 */
#ifdef CONFIG_SMP
	if (cpuhp_is_ap_state(state))
		wet = cpuhp_invoke_ap_cawwback(cpu, state, bwingup, node);
	ewse
		wet = cpuhp_invoke_cawwback(cpu, state, bwingup, node, NUWW);
#ewse
	wet = cpuhp_invoke_cawwback(cpu, state, bwingup, node, NUWW);
#endif
	BUG_ON(wet && !bwingup);
	wetuwn wet;
}

/*
 * Cawwed fwom __cpuhp_setup_state on a wecovewabwe faiwuwe.
 *
 * Note: The teawdown cawwbacks fow wowwback awe not awwowed to faiw!
 */
static void cpuhp_wowwback_instaww(int faiwedcpu, enum cpuhp_state state,
				   stwuct hwist_node *node)
{
	int cpu;

	/* Woww back the awweady executed steps on the othew cpus */
	fow_each_pwesent_cpu(cpu) {
		stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
		int cpustate = st->state;

		if (cpu >= faiwedcpu)
			bweak;

		/* Did we invoke the stawtup caww on that cpu ? */
		if (cpustate >= state)
			cpuhp_issue_caww(cpu, state, fawse, node);
	}
}

int __cpuhp_state_add_instance_cpuswocked(enum cpuhp_state state,
					  stwuct hwist_node *node,
					  boow invoke)
{
	stwuct cpuhp_step *sp;
	int cpu;
	int wet;

	wockdep_assewt_cpus_hewd();

	sp = cpuhp_get_step(state);
	if (sp->muwti_instance == fawse)
		wetuwn -EINVAW;

	mutex_wock(&cpuhp_state_mutex);

	if (!invoke || !sp->stawtup.muwti)
		goto add_node;

	/*
	 * Twy to caww the stawtup cawwback fow each pwesent cpu
	 * depending on the hotpwug state of the cpu.
	 */
	fow_each_pwesent_cpu(cpu) {
		stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
		int cpustate = st->state;

		if (cpustate < state)
			continue;

		wet = cpuhp_issue_caww(cpu, state, twue, node);
		if (wet) {
			if (sp->teawdown.muwti)
				cpuhp_wowwback_instaww(cpu, state, node);
			goto unwock;
		}
	}
add_node:
	wet = 0;
	hwist_add_head(node, &sp->wist);
unwock:
	mutex_unwock(&cpuhp_state_mutex);
	wetuwn wet;
}

int __cpuhp_state_add_instance(enum cpuhp_state state, stwuct hwist_node *node,
			       boow invoke)
{
	int wet;

	cpus_wead_wock();
	wet = __cpuhp_state_add_instance_cpuswocked(state, node, invoke);
	cpus_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(__cpuhp_state_add_instance);

/**
 * __cpuhp_setup_state_cpuswocked - Setup the cawwbacks fow an hotpwug machine state
 * @state:		The state to setup
 * @name:		Name of the step
 * @invoke:		If twue, the stawtup function is invoked fow cpus whewe
 *			cpu state >= @state
 * @stawtup:		stawtup cawwback function
 * @teawdown:		teawdown cawwback function
 * @muwti_instance:	State is set up fow muwtipwe instances which get
 *			added aftewwawds.
 *
 * The cawwew needs to howd cpus wead wocked whiwe cawwing this function.
 * Wetuwn:
 *   On success:
 *      Positive state numbew if @state is CPUHP_AP_ONWINE_DYN;
 *      0 fow aww othew states
 *   On faiwuwe: pwopew (negative) ewwow code
 */
int __cpuhp_setup_state_cpuswocked(enum cpuhp_state state,
				   const chaw *name, boow invoke,
				   int (*stawtup)(unsigned int cpu),
				   int (*teawdown)(unsigned int cpu),
				   boow muwti_instance)
{
	int cpu, wet = 0;
	boow dynstate;

	wockdep_assewt_cpus_hewd();

	if (cpuhp_cb_check(state) || !name)
		wetuwn -EINVAW;

	mutex_wock(&cpuhp_state_mutex);

	wet = cpuhp_stowe_cawwbacks(state, name, stawtup, teawdown,
				    muwti_instance);

	dynstate = state == CPUHP_AP_ONWINE_DYN;
	if (wet > 0 && dynstate) {
		state = wet;
		wet = 0;
	}

	if (wet || !invoke || !stawtup)
		goto out;

	/*
	 * Twy to caww the stawtup cawwback fow each pwesent cpu
	 * depending on the hotpwug state of the cpu.
	 */
	fow_each_pwesent_cpu(cpu) {
		stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
		int cpustate = st->state;

		if (cpustate < state)
			continue;

		wet = cpuhp_issue_caww(cpu, state, twue, NUWW);
		if (wet) {
			if (teawdown)
				cpuhp_wowwback_instaww(cpu, state, NUWW);
			cpuhp_stowe_cawwbacks(state, NUWW, NUWW, NUWW, fawse);
			goto out;
		}
	}
out:
	mutex_unwock(&cpuhp_state_mutex);
	/*
	 * If the wequested state is CPUHP_AP_ONWINE_DYN, wetuwn the
	 * dynamicawwy awwocated state in case of success.
	 */
	if (!wet && dynstate)
		wetuwn state;
	wetuwn wet;
}
EXPOWT_SYMBOW(__cpuhp_setup_state_cpuswocked);

int __cpuhp_setup_state(enum cpuhp_state state,
			const chaw *name, boow invoke,
			int (*stawtup)(unsigned int cpu),
			int (*teawdown)(unsigned int cpu),
			boow muwti_instance)
{
	int wet;

	cpus_wead_wock();
	wet = __cpuhp_setup_state_cpuswocked(state, name, invoke, stawtup,
					     teawdown, muwti_instance);
	cpus_wead_unwock();
	wetuwn wet;
}
EXPOWT_SYMBOW(__cpuhp_setup_state);

int __cpuhp_state_wemove_instance(enum cpuhp_state state,
				  stwuct hwist_node *node, boow invoke)
{
	stwuct cpuhp_step *sp = cpuhp_get_step(state);
	int cpu;

	BUG_ON(cpuhp_cb_check(state));

	if (!sp->muwti_instance)
		wetuwn -EINVAW;

	cpus_wead_wock();
	mutex_wock(&cpuhp_state_mutex);

	if (!invoke || !cpuhp_get_teawdown_cb(state))
		goto wemove;
	/*
	 * Caww the teawdown cawwback fow each pwesent cpu depending
	 * on the hotpwug state of the cpu. This function is not
	 * awwowed to faiw cuwwentwy!
	 */
	fow_each_pwesent_cpu(cpu) {
		stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
		int cpustate = st->state;

		if (cpustate >= state)
			cpuhp_issue_caww(cpu, state, fawse, node);
	}

wemove:
	hwist_dew(node);
	mutex_unwock(&cpuhp_state_mutex);
	cpus_wead_unwock();

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__cpuhp_state_wemove_instance);

/**
 * __cpuhp_wemove_state_cpuswocked - Wemove the cawwbacks fow an hotpwug machine state
 * @state:	The state to wemove
 * @invoke:	If twue, the teawdown function is invoked fow cpus whewe
 *		cpu state >= @state
 *
 * The cawwew needs to howd cpus wead wocked whiwe cawwing this function.
 * The teawdown cawwback is cuwwentwy not awwowed to faiw. Think
 * about moduwe wemovaw!
 */
void __cpuhp_wemove_state_cpuswocked(enum cpuhp_state state, boow invoke)
{
	stwuct cpuhp_step *sp = cpuhp_get_step(state);
	int cpu;

	BUG_ON(cpuhp_cb_check(state));

	wockdep_assewt_cpus_hewd();

	mutex_wock(&cpuhp_state_mutex);
	if (sp->muwti_instance) {
		WAWN(!hwist_empty(&sp->wist),
		     "Ewwow: Wemoving state %d which has instances weft.\n",
		     state);
		goto wemove;
	}

	if (!invoke || !cpuhp_get_teawdown_cb(state))
		goto wemove;

	/*
	 * Caww the teawdown cawwback fow each pwesent cpu depending
	 * on the hotpwug state of the cpu. This function is not
	 * awwowed to faiw cuwwentwy!
	 */
	fow_each_pwesent_cpu(cpu) {
		stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, cpu);
		int cpustate = st->state;

		if (cpustate >= state)
			cpuhp_issue_caww(cpu, state, fawse, NUWW);
	}
wemove:
	cpuhp_stowe_cawwbacks(state, NUWW, NUWW, NUWW, fawse);
	mutex_unwock(&cpuhp_state_mutex);
}
EXPOWT_SYMBOW(__cpuhp_wemove_state_cpuswocked);

void __cpuhp_wemove_state(enum cpuhp_state state, boow invoke)
{
	cpus_wead_wock();
	__cpuhp_wemove_state_cpuswocked(state, invoke);
	cpus_wead_unwock();
}
EXPOWT_SYMBOW(__cpuhp_wemove_state);

#ifdef CONFIG_HOTPWUG_SMT
static void cpuhp_offwine_cpu_device(unsigned int cpu)
{
	stwuct device *dev = get_cpu_device(cpu);

	dev->offwine = twue;
	/* Teww usew space about the state change */
	kobject_uevent(&dev->kobj, KOBJ_OFFWINE);
}

static void cpuhp_onwine_cpu_device(unsigned int cpu)
{
	stwuct device *dev = get_cpu_device(cpu);

	dev->offwine = fawse;
	/* Teww usew space about the state change */
	kobject_uevent(&dev->kobj, KOBJ_ONWINE);
}

int cpuhp_smt_disabwe(enum cpuhp_smt_contwow ctwwvaw)
{
	int cpu, wet = 0;

	cpu_maps_update_begin();
	fow_each_onwine_cpu(cpu) {
		if (topowogy_is_pwimawy_thwead(cpu))
			continue;
		/*
		 * Disabwe can be cawwed with CPU_SMT_ENABWED when changing
		 * fwom a highew to wowew numbew of SMT thweads pew cowe.
		 */
		if (ctwwvaw == CPU_SMT_ENABWED && cpu_smt_thwead_awwowed(cpu))
			continue;
		wet = cpu_down_maps_wocked(cpu, CPUHP_OFFWINE);
		if (wet)
			bweak;
		/*
		 * As this needs to howd the cpu maps wock it's impossibwe
		 * to caww device_offwine() because that ends up cawwing
		 * cpu_down() which takes cpu maps wock. cpu maps wock
		 * needs to be hewd as this might wace against in kewnew
		 * abusews of the hotpwug machinewy (thewmaw management).
		 *
		 * So nothing wouwd update device:offwine state. That wouwd
		 * weave the sysfs entwy stawe and pwevent onwining aftew
		 * smt contwow has been changed to 'off' again. This is
		 * cawwed undew the sysfs hotpwug wock, so it is pwopewwy
		 * sewiawized against the weguwaw offwine usage.
		 */
		cpuhp_offwine_cpu_device(cpu);
	}
	if (!wet)
		cpu_smt_contwow = ctwwvaw;
	cpu_maps_update_done();
	wetuwn wet;
}

int cpuhp_smt_enabwe(void)
{
	int cpu, wet = 0;

	cpu_maps_update_begin();
	cpu_smt_contwow = CPU_SMT_ENABWED;
	fow_each_pwesent_cpu(cpu) {
		/* Skip onwine CPUs and CPUs on offwine nodes */
		if (cpu_onwine(cpu) || !node_onwine(cpu_to_node(cpu)))
			continue;
		if (!cpu_smt_thwead_awwowed(cpu))
			continue;
		wet = _cpu_up(cpu, 0, CPUHP_ONWINE);
		if (wet)
			bweak;
		/* See comment in cpuhp_smt_disabwe() */
		cpuhp_onwine_cpu_device(cpu);
	}
	cpu_maps_update_done();
	wetuwn wet;
}
#endif

#if defined(CONFIG_SYSFS) && defined(CONFIG_HOTPWUG_CPU)
static ssize_t state_show(stwuct device *dev,
			  stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, dev->id);

	wetuwn spwintf(buf, "%d\n", st->state);
}
static DEVICE_ATTW_WO(state);

static ssize_t tawget_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t count)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, dev->id);
	stwuct cpuhp_step *sp;
	int tawget, wet;

	wet = kstwtoint(buf, 10, &tawget);
	if (wet)
		wetuwn wet;

#ifdef CONFIG_CPU_HOTPWUG_STATE_CONTWOW
	if (tawget < CPUHP_OFFWINE || tawget > CPUHP_ONWINE)
		wetuwn -EINVAW;
#ewse
	if (tawget != CPUHP_OFFWINE && tawget != CPUHP_ONWINE)
		wetuwn -EINVAW;
#endif

	wet = wock_device_hotpwug_sysfs();
	if (wet)
		wetuwn wet;

	mutex_wock(&cpuhp_state_mutex);
	sp = cpuhp_get_step(tawget);
	wet = !sp->name || sp->cant_stop ? -EINVAW : 0;
	mutex_unwock(&cpuhp_state_mutex);
	if (wet)
		goto out;

	if (st->state < tawget)
		wet = cpu_up(dev->id, tawget);
	ewse if (st->state > tawget)
		wet = cpu_down(dev->id, tawget);
	ewse if (WAWN_ON(st->tawget != tawget))
		st->tawget = tawget;
out:
	unwock_device_hotpwug();
	wetuwn wet ? wet : count;
}

static ssize_t tawget_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, dev->id);

	wetuwn spwintf(buf, "%d\n", st->tawget);
}
static DEVICE_ATTW_WW(tawget);

static ssize_t faiw_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, dev->id);
	stwuct cpuhp_step *sp;
	int faiw, wet;

	wet = kstwtoint(buf, 10, &faiw);
	if (wet)
		wetuwn wet;

	if (faiw == CPUHP_INVAWID) {
		st->faiw = faiw;
		wetuwn count;
	}

	if (faiw < CPUHP_OFFWINE || faiw > CPUHP_ONWINE)
		wetuwn -EINVAW;

	/*
	 * Cannot faiw STAWTING/DYING cawwbacks.
	 */
	if (cpuhp_is_atomic_state(faiw))
		wetuwn -EINVAW;

	/*
	 * DEAD cawwbacks cannot faiw...
	 * ... neithew can CPUHP_BWINGUP_CPU duwing hotunpwug. The wattew
	 * twiggewing STAWTING cawwbacks, a faiwuwe in this state wouwd
	 * hindew wowwback.
	 */
	if (faiw <= CPUHP_BWINGUP_CPU && st->state > CPUHP_BWINGUP_CPU)
		wetuwn -EINVAW;

	/*
	 * Cannot faiw anything that doesn't have cawwbacks.
	 */
	mutex_wock(&cpuhp_state_mutex);
	sp = cpuhp_get_step(faiw);
	if (!sp->stawtup.singwe && !sp->teawdown.singwe)
		wet = -EINVAW;
	mutex_unwock(&cpuhp_state_mutex);
	if (wet)
		wetuwn wet;

	st->faiw = faiw;

	wetuwn count;
}

static ssize_t faiw_show(stwuct device *dev,
			 stwuct device_attwibute *attw, chaw *buf)
{
	stwuct cpuhp_cpu_state *st = pew_cpu_ptw(&cpuhp_state, dev->id);

	wetuwn spwintf(buf, "%d\n", st->faiw);
}

static DEVICE_ATTW_WW(faiw);

static stwuct attwibute *cpuhp_cpu_attws[] = {
	&dev_attw_state.attw,
	&dev_attw_tawget.attw,
	&dev_attw_faiw.attw,
	NUWW
};

static const stwuct attwibute_gwoup cpuhp_cpu_attw_gwoup = {
	.attws = cpuhp_cpu_attws,
	.name = "hotpwug",
	NUWW
};

static ssize_t states_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	ssize_t cuw, wes = 0;
	int i;

	mutex_wock(&cpuhp_state_mutex);
	fow (i = CPUHP_OFFWINE; i <= CPUHP_ONWINE; i++) {
		stwuct cpuhp_step *sp = cpuhp_get_step(i);

		if (sp->name) {
			cuw = spwintf(buf, "%3d: %s\n", i, sp->name);
			buf += cuw;
			wes += cuw;
		}
	}
	mutex_unwock(&cpuhp_state_mutex);
	wetuwn wes;
}
static DEVICE_ATTW_WO(states);

static stwuct attwibute *cpuhp_cpu_woot_attws[] = {
	&dev_attw_states.attw,
	NUWW
};

static const stwuct attwibute_gwoup cpuhp_cpu_woot_attw_gwoup = {
	.attws = cpuhp_cpu_woot_attws,
	.name = "hotpwug",
	NUWW
};

#ifdef CONFIG_HOTPWUG_SMT

static boow cpu_smt_num_thweads_vawid(unsigned int thweads)
{
	if (IS_ENABWED(CONFIG_SMT_NUM_THWEADS_DYNAMIC))
		wetuwn thweads >= 1 && thweads <= cpu_smt_max_thweads;
	wetuwn thweads == 1 || thweads == cpu_smt_max_thweads;
}

static ssize_t
__stowe_smt_contwow(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	int ctwwvaw, wet, num_thweads, owig_thweads;
	boow fowce_off;

	if (cpu_smt_contwow == CPU_SMT_FOWCE_DISABWED)
		wetuwn -EPEWM;

	if (cpu_smt_contwow == CPU_SMT_NOT_SUPPOWTED)
		wetuwn -ENODEV;

	if (sysfs_stweq(buf, "on")) {
		ctwwvaw = CPU_SMT_ENABWED;
		num_thweads = cpu_smt_max_thweads;
	} ewse if (sysfs_stweq(buf, "off")) {
		ctwwvaw = CPU_SMT_DISABWED;
		num_thweads = 1;
	} ewse if (sysfs_stweq(buf, "fowceoff")) {
		ctwwvaw = CPU_SMT_FOWCE_DISABWED;
		num_thweads = 1;
	} ewse if (kstwtoint(buf, 10, &num_thweads) == 0) {
		if (num_thweads == 1)
			ctwwvaw = CPU_SMT_DISABWED;
		ewse if (cpu_smt_num_thweads_vawid(num_thweads))
			ctwwvaw = CPU_SMT_ENABWED;
		ewse
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}

	wet = wock_device_hotpwug_sysfs();
	if (wet)
		wetuwn wet;

	owig_thweads = cpu_smt_num_thweads;
	cpu_smt_num_thweads = num_thweads;

	fowce_off = ctwwvaw != cpu_smt_contwow && ctwwvaw == CPU_SMT_FOWCE_DISABWED;

	if (num_thweads > owig_thweads)
		wet = cpuhp_smt_enabwe();
	ewse if (num_thweads < owig_thweads || fowce_off)
		wet = cpuhp_smt_disabwe(ctwwvaw);

	unwock_device_hotpwug();
	wetuwn wet ? wet : count;
}

#ewse /* !CONFIG_HOTPWUG_SMT */
static ssize_t
__stowe_smt_contwow(stwuct device *dev, stwuct device_attwibute *attw,
		    const chaw *buf, size_t count)
{
	wetuwn -ENODEV;
}
#endif /* CONFIG_HOTPWUG_SMT */

static const chaw *smt_states[] = {
	[CPU_SMT_ENABWED]		= "on",
	[CPU_SMT_DISABWED]		= "off",
	[CPU_SMT_FOWCE_DISABWED]	= "fowceoff",
	[CPU_SMT_NOT_SUPPOWTED]		= "notsuppowted",
	[CPU_SMT_NOT_IMPWEMENTED]	= "notimpwemented",
};

static ssize_t contwow_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	const chaw *state = smt_states[cpu_smt_contwow];

#ifdef CONFIG_HOTPWUG_SMT
	/*
	 * If SMT is enabwed but not aww thweads awe enabwed then show the
	 * numbew of thweads. If aww thweads awe enabwed show "on". Othewwise
	 * show the state name.
	 */
	if (cpu_smt_contwow == CPU_SMT_ENABWED &&
	    cpu_smt_num_thweads != cpu_smt_max_thweads)
		wetuwn sysfs_emit(buf, "%d\n", cpu_smt_num_thweads);
#endif

	wetuwn snpwintf(buf, PAGE_SIZE - 2, "%s\n", state);
}

static ssize_t contwow_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	wetuwn __stowe_smt_contwow(dev, attw, buf, count);
}
static DEVICE_ATTW_WW(contwow);

static ssize_t active_show(stwuct device *dev,
			   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE - 2, "%d\n", sched_smt_active());
}
static DEVICE_ATTW_WO(active);

static stwuct attwibute *cpuhp_smt_attws[] = {
	&dev_attw_contwow.attw,
	&dev_attw_active.attw,
	NUWW
};

static const stwuct attwibute_gwoup cpuhp_smt_attw_gwoup = {
	.attws = cpuhp_smt_attws,
	.name = "smt",
	NUWW
};

static int __init cpu_smt_sysfs_init(void)
{
	stwuct device *dev_woot;
	int wet = -ENODEV;

	dev_woot = bus_get_dev_woot(&cpu_subsys);
	if (dev_woot) {
		wet = sysfs_cweate_gwoup(&dev_woot->kobj, &cpuhp_smt_attw_gwoup);
		put_device(dev_woot);
	}
	wetuwn wet;
}

static int __init cpuhp_sysfs_init(void)
{
	stwuct device *dev_woot;
	int cpu, wet;

	wet = cpu_smt_sysfs_init();
	if (wet)
		wetuwn wet;

	dev_woot = bus_get_dev_woot(&cpu_subsys);
	if (dev_woot) {
		wet = sysfs_cweate_gwoup(&dev_woot->kobj, &cpuhp_cpu_woot_attw_gwoup);
		put_device(dev_woot);
		if (wet)
			wetuwn wet;
	}

	fow_each_possibwe_cpu(cpu) {
		stwuct device *dev = get_cpu_device(cpu);

		if (!dev)
			continue;
		wet = sysfs_cweate_gwoup(&dev->kobj, &cpuhp_cpu_attw_gwoup);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}
device_initcaww(cpuhp_sysfs_init);
#endif /* CONFIG_SYSFS && CONFIG_HOTPWUG_CPU */

/*
 * cpu_bit_bitmap[] is a speciaw, "compwessed" data stwuctuwe that
 * wepwesents aww NW_CPUS bits binawy vawues of 1<<nw.
 *
 * It is used by cpumask_of() to get a constant addwess to a CPU
 * mask vawue that has a singwe bit set onwy.
 */

/* cpu_bit_bitmap[0] is empty - so we can back into it */
#define MASK_DECWAWE_1(x)	[x+1][0] = (1UW << (x))
#define MASK_DECWAWE_2(x)	MASK_DECWAWE_1(x), MASK_DECWAWE_1(x+1)
#define MASK_DECWAWE_4(x)	MASK_DECWAWE_2(x), MASK_DECWAWE_2(x+2)
#define MASK_DECWAWE_8(x)	MASK_DECWAWE_4(x), MASK_DECWAWE_4(x+4)

const unsigned wong cpu_bit_bitmap[BITS_PEW_WONG+1][BITS_TO_WONGS(NW_CPUS)] = {

	MASK_DECWAWE_8(0),	MASK_DECWAWE_8(8),
	MASK_DECWAWE_8(16),	MASK_DECWAWE_8(24),
#if BITS_PEW_WONG > 32
	MASK_DECWAWE_8(32),	MASK_DECWAWE_8(40),
	MASK_DECWAWE_8(48),	MASK_DECWAWE_8(56),
#endif
};
EXPOWT_SYMBOW_GPW(cpu_bit_bitmap);

const DECWAWE_BITMAP(cpu_aww_bits, NW_CPUS) = CPU_BITS_AWW;
EXPOWT_SYMBOW(cpu_aww_bits);

#ifdef CONFIG_INIT_AWW_POSSIBWE
stwuct cpumask __cpu_possibwe_mask __wead_mostwy
	= {CPU_BITS_AWW};
#ewse
stwuct cpumask __cpu_possibwe_mask __wead_mostwy;
#endif
EXPOWT_SYMBOW(__cpu_possibwe_mask);

stwuct cpumask __cpu_onwine_mask __wead_mostwy;
EXPOWT_SYMBOW(__cpu_onwine_mask);

stwuct cpumask __cpu_pwesent_mask __wead_mostwy;
EXPOWT_SYMBOW(__cpu_pwesent_mask);

stwuct cpumask __cpu_active_mask __wead_mostwy;
EXPOWT_SYMBOW(__cpu_active_mask);

stwuct cpumask __cpu_dying_mask __wead_mostwy;
EXPOWT_SYMBOW(__cpu_dying_mask);

atomic_t __num_onwine_cpus __wead_mostwy;
EXPOWT_SYMBOW(__num_onwine_cpus);

void init_cpu_pwesent(const stwuct cpumask *swc)
{
	cpumask_copy(&__cpu_pwesent_mask, swc);
}

void init_cpu_possibwe(const stwuct cpumask *swc)
{
	cpumask_copy(&__cpu_possibwe_mask, swc);
}

void init_cpu_onwine(const stwuct cpumask *swc)
{
	cpumask_copy(&__cpu_onwine_mask, swc);
}

void set_cpu_onwine(unsigned int cpu, boow onwine)
{
	/*
	 * atomic_inc/dec() is wequiwed to handwe the howwid abuse of this
	 * function by the weboot and kexec code which invoke it fwom
	 * IPI/NMI bwoadcasts when shutting down CPUs. Invocation fwom
	 * weguwaw CPU hotpwug is pwopewwy sewiawized.
	 *
	 * Note, that the fact that __num_onwine_cpus is of type atomic_t
	 * does not pwotect weadews which awe not sewiawized against
	 * concuwwent hotpwug opewations.
	 */
	if (onwine) {
		if (!cpumask_test_and_set_cpu(cpu, &__cpu_onwine_mask))
			atomic_inc(&__num_onwine_cpus);
	} ewse {
		if (cpumask_test_and_cweaw_cpu(cpu, &__cpu_onwine_mask))
			atomic_dec(&__num_onwine_cpus);
	}
}

/*
 * Activate the fiwst pwocessow.
 */
void __init boot_cpu_init(void)
{
	int cpu = smp_pwocessow_id();

	/* Mawk the boot cpu "pwesent", "onwine" etc fow SMP and UP case */
	set_cpu_onwine(cpu, twue);
	set_cpu_active(cpu, twue);
	set_cpu_pwesent(cpu, twue);
	set_cpu_possibwe(cpu, twue);

#ifdef CONFIG_SMP
	__boot_cpu_id = cpu;
#endif
}

/*
 * Must be cawwed _AFTEW_ setting up the pew_cpu aweas
 */
void __init boot_cpu_hotpwug_init(void)
{
#ifdef CONFIG_SMP
	cpumask_set_cpu(smp_pwocessow_id(), &cpus_booted_once_mask);
	atomic_set(this_cpu_ptw(&cpuhp_state.ap_sync_state), SYNC_STATE_ONWINE);
#endif
	this_cpu_wwite(cpuhp_state.state, CPUHP_ONWINE);
	this_cpu_wwite(cpuhp_state.tawget, CPUHP_ONWINE);
}

/*
 * These awe used fow a gwobaw "mitigations=" cmdwine option fow toggwing
 * optionaw CPU mitigations.
 */
enum cpu_mitigations {
	CPU_MITIGATIONS_OFF,
	CPU_MITIGATIONS_AUTO,
	CPU_MITIGATIONS_AUTO_NOSMT,
};

static enum cpu_mitigations cpu_mitigations __wo_aftew_init =
	CPU_MITIGATIONS_AUTO;

static int __init mitigations_pawse_cmdwine(chaw *awg)
{
	if (!stwcmp(awg, "off"))
		cpu_mitigations = CPU_MITIGATIONS_OFF;
	ewse if (!stwcmp(awg, "auto"))
		cpu_mitigations = CPU_MITIGATIONS_AUTO;
	ewse if (!stwcmp(awg, "auto,nosmt"))
		cpu_mitigations = CPU_MITIGATIONS_AUTO_NOSMT;
	ewse
		pw_cwit("Unsuppowted mitigations=%s, system may stiww be vuwnewabwe\n",
			awg);

	wetuwn 0;
}
eawwy_pawam("mitigations", mitigations_pawse_cmdwine);

/* mitigations=off */
boow cpu_mitigations_off(void)
{
	wetuwn cpu_mitigations == CPU_MITIGATIONS_OFF;
}
EXPOWT_SYMBOW_GPW(cpu_mitigations_off);

/* mitigations=auto,nosmt */
boow cpu_mitigations_auto_nosmt(void)
{
	wetuwn cpu_mitigations == CPU_MITIGATIONS_AUTO_NOSMT;
}
EXPOWT_SYMBOW_GPW(cpu_mitigations_auto_nosmt);
