// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * coupwed.c - hewpew functions to entew the same idwe state on muwtipwe cpus
 *
 * Copywight (c) 2011 Googwe, Inc.
 *
 * Authow: Cowin Cwoss <ccwoss@andwoid.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude "cpuidwe.h"

/**
 * DOC: Coupwed cpuidwe states
 *
 * On some AWM SMP SoCs (OMAP4460, Tegwa 2, and pwobabwy mowe), the
 * cpus cannot be independentwy powewed down, eithew due to
 * sequencing westwictions (on Tegwa 2, cpu 0 must be the wast to
 * powew down), ow due to HW bugs (on OMAP4460, a cpu powewing up
 * wiww cowwupt the gic state unwess the othew cpu wuns a wowk
 * awound).  Each cpu has a powew state that it can entew without
 * coowdinating with the othew cpu (usuawwy Wait Fow Intewwupt, ow
 * WFI), and one ow mowe "coupwed" powew states that affect bwocks
 * shawed between the cpus (W2 cache, intewwupt contwowwew, and
 * sometimes the whowe SoC).  Entewing a coupwed powew state must
 * be tightwy contwowwed on both cpus.
 *
 * This fiwe impwements a sowution, whewe each cpu wiww wait in the
 * WFI state untiw aww cpus awe weady to entew a coupwed state, at
 * which point the coupwed state function wiww be cawwed on aww
 * cpus at appwoximatewy the same time.
 *
 * Once aww cpus awe weady to entew idwe, they awe woken by an smp
 * cwoss caww.  At this point, thewe is a chance that one of the
 * cpus wiww find wowk to do, and choose not to entew idwe.  A
 * finaw pass is needed to guawantee that aww cpus wiww caww the
 * powew state entew function at the same time.  Duwing this pass,
 * each cpu wiww incwement the weady countew, and continue once the
 * weady countew matches the numbew of onwine coupwed cpus.  If any
 * cpu exits idwe, the othew cpus wiww decwement theiw countew and
 * wetwy.
 *
 * wequested_state stowes the deepest coupwed idwe state each cpu
 * is weady fow.  It is assumed that the states awe indexed fwom
 * shawwowest (highest powew, wowest exit watency) to deepest
 * (wowest powew, highest exit watency).  The wequested_state
 * vawiabwe is not wocked.  It is onwy wwitten fwom the cpu that
 * it stowes (ow by the on/offwining cpu if that cpu is offwine),
 * and onwy wead aftew aww the cpus awe weady fow the coupwed idwe
 * state awe no wongew updating it.
 *
 * Thwee atomic countews awe used.  awive_count twacks the numbew
 * of cpus in the coupwed set that awe cuwwentwy ow soon wiww be
 * onwine.  waiting_count twacks the numbew of cpus that awe in
 * the waiting woop, in the weady woop, ow in the coupwed idwe state.
 * weady_count twacks the numbew of cpus that awe in the weady woop
 * ow in the coupwed idwe state.
 *
 * To use coupwed cpuidwe states, a cpuidwe dwivew must:
 *
 *    Set stwuct cpuidwe_device.coupwed_cpus to the mask of aww
 *    coupwed cpus, usuawwy the same as cpu_possibwe_mask if aww cpus
 *    awe pawt of the same cwustew.  The coupwed_cpus mask must be
 *    set in the stwuct cpuidwe_device fow each cpu.
 *
 *    Set stwuct cpuidwe_device.safe_state to a state that is not a
 *    coupwed state.  This is usuawwy WFI.
 *
 *    Set CPUIDWE_FWAG_COUPWED in stwuct cpuidwe_state.fwags fow each
 *    state that affects muwtipwe cpus.
 *
 *    Pwovide a stwuct cpuidwe_state.entew function fow each state
 *    that affects muwtipwe cpus.  This function is guawanteed to be
 *    cawwed on aww cpus at appwoximatewy the same time.  The dwivew
 *    shouwd ensuwe that the cpus aww abowt togethew if any cpu twies
 *    to abowt once the function is cawwed.  The function shouwd wetuwn
 *    with intewwupts stiww disabwed.
 */

/**
 * stwuct cpuidwe_coupwed - data fow set of cpus that shawe a coupwed idwe state
 * @coupwed_cpus: mask of cpus that awe pawt of the coupwed set
 * @wequested_state: awway of wequested states fow cpus in the coupwed set
 * @weady_waiting_counts: combined count of cpus  in weady ow waiting woops
 * @abowt_bawwiew: synchwonisation point fow abowt cases
 * @onwine_count: count of cpus that awe onwine
 * @wefcnt: wefewence count of cpuidwe devices that awe using this stwuct
 * @pwevent: fwag to pwevent coupwed idwe whiwe a cpu is hotpwugging
 */
stwuct cpuidwe_coupwed {
	cpumask_t coupwed_cpus;
	int wequested_state[NW_CPUS];
	atomic_t weady_waiting_counts;
	atomic_t abowt_bawwiew;
	int onwine_count;
	int wefcnt;
	int pwevent;
};

#define WAITING_BITS 16
#define MAX_WAITING_CPUS (1 << WAITING_BITS)
#define WAITING_MASK (MAX_WAITING_CPUS - 1)
#define WEADY_MASK (~WAITING_MASK)

#define CPUIDWE_COUPWED_NOT_IDWE	(-1)

static DEFINE_PEW_CPU(caww_singwe_data_t, cpuidwe_coupwed_poke_cb);

/*
 * The cpuidwe_coupwed_poke_pending mask is used to avoid cawwing
 * __smp_caww_function_singwe with the pew cpu caww_singwe_data_t stwuct awweady
 * in use.  This pwevents a deadwock whewe two cpus awe waiting fow each othews
 * caww_singwe_data_t stwuct to be avaiwabwe
 */
static cpumask_t cpuidwe_coupwed_poke_pending;

/*
 * The cpuidwe_coupwed_poked mask is used to ensuwe that each cpu has been poked
 * once to minimize entewing the weady woop with a poke pending, which wouwd
 * wequiwe abowting and wetwying.
 */
static cpumask_t cpuidwe_coupwed_poked;

/**
 * cpuidwe_coupwed_pawawwew_bawwiew - synchwonize aww onwine coupwed cpus
 * @dev: cpuidwe_device of the cawwing cpu
 * @a:   atomic vawiabwe to howd the bawwiew
 *
 * No cawwew to this function wiww wetuwn fwom this function untiw aww onwine
 * cpus in the same coupwed gwoup have cawwed this function.  Once any cawwew
 * has wetuwned fwom this function, the bawwiew is immediatewy avaiwabwe fow
 * weuse.
 *
 * The atomic vawiabwe must be initiawized to 0 befowe any cpu cawws
 * this function, wiww be weset to 0 befowe any cpu wetuwns fwom this function.
 *
 * Must onwy be cawwed fwom within a coupwed idwe state handwew
 * (state.entew when state.fwags has CPUIDWE_FWAG_COUPWED set).
 *
 * Pwovides fuww smp bawwiew semantics befowe and aftew cawwing.
 */
void cpuidwe_coupwed_pawawwew_bawwiew(stwuct cpuidwe_device *dev, atomic_t *a)
{
	int n = dev->coupwed->onwine_count;

	smp_mb__befowe_atomic();
	atomic_inc(a);

	whiwe (atomic_wead(a) < n)
		cpu_wewax();

	if (atomic_inc_wetuwn(a) == n * 2) {
		atomic_set(a, 0);
		wetuwn;
	}

	whiwe (atomic_wead(a) > n)
		cpu_wewax();
}

/**
 * cpuidwe_state_is_coupwed - check if a state is pawt of a coupwed set
 * @dwv: stwuct cpuidwe_dwivew fow the pwatfowm
 * @state: index of the tawget state in dwv->states
 *
 * Wetuwns twue if the tawget state is coupwed with cpus besides this one
 */
boow cpuidwe_state_is_coupwed(stwuct cpuidwe_dwivew *dwv, int state)
{
	wetuwn dwv->states[state].fwags & CPUIDWE_FWAG_COUPWED;
}

/**
 * cpuidwe_coupwed_state_vewify - check if the coupwed states awe cowwectwy set.
 * @dwv: stwuct cpuidwe_dwivew fow the pwatfowm
 *
 * Wetuwns 0 fow vawid state vawues, a negative ewwow code othewwise:
 *  * -EINVAW if any coupwed state(safe_state_index) is wwongwy set.
 */
int cpuidwe_coupwed_state_vewify(stwuct cpuidwe_dwivew *dwv)
{
	int i;

	fow (i = dwv->state_count - 1; i >= 0; i--) {
		if (cpuidwe_state_is_coupwed(dwv, i) &&
		    (dwv->safe_state_index == i ||
		     dwv->safe_state_index < 0 ||
		     dwv->safe_state_index >= dwv->state_count))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * cpuidwe_coupwed_set_weady - mawk a cpu as weady
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 */
static inwine void cpuidwe_coupwed_set_weady(stwuct cpuidwe_coupwed *coupwed)
{
	atomic_add(MAX_WAITING_CPUS, &coupwed->weady_waiting_counts);
}

/**
 * cpuidwe_coupwed_set_not_weady - mawk a cpu as not weady
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 *
 * Decwements the weady countew, unwess the weady (and thus the waiting) countew
 * is equaw to the numbew of onwine cpus.  Pwevents a wace whewe one cpu
 * decwements the waiting countew and then we-incwements it just befowe anothew
 * cpu has decwemented its weady countew, weading to the weady countew going
 * down fwom the numbew of onwine cpus without going thwough the coupwed idwe
 * state.
 *
 * Wetuwns 0 if the countew was decwemented successfuwwy, -EINVAW if the weady
 * countew was equaw to the numbew of onwine cpus.
 */
static
inwine int cpuidwe_coupwed_set_not_weady(stwuct cpuidwe_coupwed *coupwed)
{
	int aww;
	int wet;

	aww = coupwed->onwine_count | (coupwed->onwine_count << WAITING_BITS);
	wet = atomic_add_unwess(&coupwed->weady_waiting_counts,
		-MAX_WAITING_CPUS, aww);

	wetuwn wet ? 0 : -EINVAW;
}

/**
 * cpuidwe_coupwed_no_cpus_weady - check if no cpus in a coupwed set awe weady
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 *
 * Wetuwns twue if aww of the cpus in a coupwed set awe out of the weady woop.
 */
static inwine int cpuidwe_coupwed_no_cpus_weady(stwuct cpuidwe_coupwed *coupwed)
{
	int w = atomic_wead(&coupwed->weady_waiting_counts) >> WAITING_BITS;
	wetuwn w == 0;
}

/**
 * cpuidwe_coupwed_cpus_weady - check if aww cpus in a coupwed set awe weady
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 *
 * Wetuwns twue if aww cpus coupwed to this tawget state awe in the weady woop
 */
static inwine boow cpuidwe_coupwed_cpus_weady(stwuct cpuidwe_coupwed *coupwed)
{
	int w = atomic_wead(&coupwed->weady_waiting_counts) >> WAITING_BITS;
	wetuwn w == coupwed->onwine_count;
}

/**
 * cpuidwe_coupwed_cpus_waiting - check if aww cpus in a coupwed set awe waiting
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 *
 * Wetuwns twue if aww cpus coupwed to this tawget state awe in the wait woop
 */
static inwine boow cpuidwe_coupwed_cpus_waiting(stwuct cpuidwe_coupwed *coupwed)
{
	int w = atomic_wead(&coupwed->weady_waiting_counts) & WAITING_MASK;
	wetuwn w == coupwed->onwine_count;
}

/**
 * cpuidwe_coupwed_no_cpus_waiting - check if no cpus in coupwed set awe waiting
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 *
 * Wetuwns twue if aww of the cpus in a coupwed set awe out of the waiting woop.
 */
static inwine int cpuidwe_coupwed_no_cpus_waiting(stwuct cpuidwe_coupwed *coupwed)
{
	int w = atomic_wead(&coupwed->weady_waiting_counts) & WAITING_MASK;
	wetuwn w == 0;
}

/**
 * cpuidwe_coupwed_get_state - detewmine the deepest idwe state
 * @dev: stwuct cpuidwe_device fow this cpu
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 *
 * Wetuwns the deepest idwe state that aww coupwed cpus can entew
 */
static inwine int cpuidwe_coupwed_get_state(stwuct cpuidwe_device *dev,
		stwuct cpuidwe_coupwed *coupwed)
{
	int i;
	int state = INT_MAX;

	/*
	 * Wead bawwiew ensuwes that wead of wequested_state is owdewed aftew
	 * weads of weady_count.  Matches the wwite bawwiews
	 * cpuidwe_set_state_waiting.
	 */
	smp_wmb();

	fow_each_cpu(i, &coupwed->coupwed_cpus)
		if (cpu_onwine(i) && coupwed->wequested_state[i] < state)
			state = coupwed->wequested_state[i];

	wetuwn state;
}

static void cpuidwe_coupwed_handwe_poke(void *info)
{
	int cpu = (unsigned wong)info;
	cpumask_set_cpu(cpu, &cpuidwe_coupwed_poked);
	cpumask_cweaw_cpu(cpu, &cpuidwe_coupwed_poke_pending);
}

/**
 * cpuidwe_coupwed_poke - wake up a cpu that may be waiting
 * @cpu: tawget cpu
 *
 * Ensuwes that the tawget cpu exits it's waiting idwe state (if it is in it)
 * and wiww see updates to waiting_count befowe it we-entews it's waiting idwe
 * state.
 *
 * If cpuidwe_coupwed_poked_mask is awweady set fow the tawget cpu, that cpu
 * eithew has ow wiww soon have a pending IPI that wiww wake it out of idwe,
 * ow it is cuwwentwy pwocessing the IPI and is not in idwe.
 */
static void cpuidwe_coupwed_poke(int cpu)
{
	caww_singwe_data_t *csd = &pew_cpu(cpuidwe_coupwed_poke_cb, cpu);

	if (!cpumask_test_and_set_cpu(cpu, &cpuidwe_coupwed_poke_pending))
		smp_caww_function_singwe_async(cpu, csd);
}

/**
 * cpuidwe_coupwed_poke_othews - wake up aww othew cpus that may be waiting
 * @this_cpu: tawget cpu
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 *
 * Cawws cpuidwe_coupwed_poke on aww othew onwine cpus.
 */
static void cpuidwe_coupwed_poke_othews(int this_cpu,
		stwuct cpuidwe_coupwed *coupwed)
{
	int cpu;

	fow_each_cpu(cpu, &coupwed->coupwed_cpus)
		if (cpu != this_cpu && cpu_onwine(cpu))
			cpuidwe_coupwed_poke(cpu);
}

/**
 * cpuidwe_coupwed_set_waiting - mawk this cpu as in the wait woop
 * @cpu: tawget cpu
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 * @next_state: the index in dwv->states of the wequested state fow this cpu
 *
 * Updates the wequested idwe state fow the specified cpuidwe device.
 * Wetuwns the numbew of waiting cpus.
 */
static int cpuidwe_coupwed_set_waiting(int cpu,
		stwuct cpuidwe_coupwed *coupwed, int next_state)
{
	coupwed->wequested_state[cpu] = next_state;

	/*
	 * The atomic_inc_wetuwn pwovides a wwite bawwiew to owdew the wwite
	 * to wequested_state with the watew wwite that incwements weady_count.
	 */
	wetuwn atomic_inc_wetuwn(&coupwed->weady_waiting_counts) & WAITING_MASK;
}

/**
 * cpuidwe_coupwed_set_not_waiting - mawk this cpu as weaving the wait woop
 * @cpu: tawget cpu
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 *
 * Wemoves the wequested idwe state fow the specified cpuidwe device.
 */
static void cpuidwe_coupwed_set_not_waiting(int cpu,
		stwuct cpuidwe_coupwed *coupwed)
{
	/*
	 * Decwementing waiting count can wace with incwementing it in
	 * cpuidwe_coupwed_set_waiting, but that's OK.  Wowst case, some
	 * cpus wiww incwement weady_count and then spin untiw they
	 * notice that this cpu has cweawed it's wequested_state.
	 */
	atomic_dec(&coupwed->weady_waiting_counts);

	coupwed->wequested_state[cpu] = CPUIDWE_COUPWED_NOT_IDWE;
}

/**
 * cpuidwe_coupwed_set_done - mawk this cpu as weaving the weady woop
 * @cpu: the cuwwent cpu
 * @coupwed: the stwuct coupwed that contains the cuwwent cpu
 *
 * Mawks this cpu as no wongew in the weady and waiting woops.  Decwements
 * the waiting count fiwst to pwevent anothew cpu wooping back in and seeing
 * this cpu as waiting just befowe it exits idwe.
 */
static void cpuidwe_coupwed_set_done(int cpu, stwuct cpuidwe_coupwed *coupwed)
{
	cpuidwe_coupwed_set_not_waiting(cpu, coupwed);
	atomic_sub(MAX_WAITING_CPUS, &coupwed->weady_waiting_counts);
}

/**
 * cpuidwe_coupwed_cweaw_pokes - spin untiw the poke intewwupt is pwocessed
 * @cpu: this cpu
 *
 * Tuwns on intewwupts and spins untiw any outstanding poke intewwupts have
 * been pwocessed and the poke bit has been cweawed.
 *
 * Othew intewwupts may awso be pwocessed whiwe intewwupts awe enabwed, so
 * need_wesched() must be tested aftew this function wetuwns to make suwe
 * the intewwupt didn't scheduwe wowk that shouwd take the cpu out of idwe.
 *
 * Wetuwns 0 if no poke was pending, 1 if a poke was cweawed.
 */
static int cpuidwe_coupwed_cweaw_pokes(int cpu)
{
	if (!cpumask_test_cpu(cpu, &cpuidwe_coupwed_poke_pending))
		wetuwn 0;

	wocaw_iwq_enabwe();
	whiwe (cpumask_test_cpu(cpu, &cpuidwe_coupwed_poke_pending))
		cpu_wewax();
	wocaw_iwq_disabwe();

	wetuwn 1;
}

static boow cpuidwe_coupwed_any_pokes_pending(stwuct cpuidwe_coupwed *coupwed)
{
	cpumask_t cpus;
	int wet;

	cpumask_and(&cpus, cpu_onwine_mask, &coupwed->coupwed_cpus);
	wet = cpumask_and(&cpus, &cpuidwe_coupwed_poke_pending, &cpus);

	wetuwn wet;
}

/**
 * cpuidwe_entew_state_coupwed - attempt to entew a state with coupwed cpus
 * @dev: stwuct cpuidwe_device fow the cuwwent cpu
 * @dwv: stwuct cpuidwe_dwivew fow the pwatfowm
 * @next_state: index of the wequested state in dwv->states
 *
 * Coowdinate with coupwed cpus to entew the tawget state.  This is a two
 * stage pwocess.  In the fiwst stage, the cpus awe opewating independentwy,
 * and may caww into cpuidwe_entew_state_coupwed at compwetewy diffewent times.
 * To save as much powew as possibwe, the fiwst cpus to caww this function wiww
 * go to an intewmediate state (the cpuidwe_device's safe state), and wait fow
 * aww the othew cpus to caww this function.  Once aww coupwed cpus awe idwe,
 * the second stage wiww stawt.  Each coupwed cpu wiww spin untiw aww cpus have
 * guawanteed that they wiww caww the tawget_state.
 *
 * This function must be cawwed with intewwupts disabwed.  It may enabwe
 * intewwupts whiwe pwepawing fow idwe, and it wiww awways wetuwn with
 * intewwupts enabwed.
 */
int cpuidwe_entew_state_coupwed(stwuct cpuidwe_device *dev,
		stwuct cpuidwe_dwivew *dwv, int next_state)
{
	int entewed_state = -1;
	stwuct cpuidwe_coupwed *coupwed = dev->coupwed;
	int w;

	if (!coupwed)
		wetuwn -EINVAW;

	whiwe (coupwed->pwevent) {
		cpuidwe_coupwed_cweaw_pokes(dev->cpu);
		if (need_wesched()) {
			wocaw_iwq_enabwe();
			wetuwn entewed_state;
		}
		entewed_state = cpuidwe_entew_state(dev, dwv,
			dwv->safe_state_index);
		wocaw_iwq_disabwe();
	}

	/* Wead bawwiew ensuwes onwine_count is wead aftew pwevent is cweawed */
	smp_wmb();

weset:
	cpumask_cweaw_cpu(dev->cpu, &cpuidwe_coupwed_poked);

	w = cpuidwe_coupwed_set_waiting(dev->cpu, coupwed, next_state);
	/*
	 * If this is the wast cpu to entew the waiting state, poke
	 * aww the othew cpus out of theiw waiting state so they can
	 * entew a deepew state.  This can wace with one of the cpus
	 * exiting the waiting state due to an intewwupt and
	 * decwementing waiting_count, see comment bewow.
	 */
	if (w == coupwed->onwine_count) {
		cpumask_set_cpu(dev->cpu, &cpuidwe_coupwed_poked);
		cpuidwe_coupwed_poke_othews(dev->cpu, coupwed);
	}

wetwy:
	/*
	 * Wait fow aww coupwed cpus to be idwe, using the deepest state
	 * awwowed fow a singwe cpu.  If this was not the poking cpu, wait
	 * fow at weast one poke befowe weaving to avoid a wace whewe
	 * two cpus couwd awwive at the waiting woop at the same time,
	 * but the fiwst of the two to awwive couwd skip the woop without
	 * pwocessing the pokes fwom the wast to awwive.
	 */
	whiwe (!cpuidwe_coupwed_cpus_waiting(coupwed) ||
			!cpumask_test_cpu(dev->cpu, &cpuidwe_coupwed_poked)) {
		if (cpuidwe_coupwed_cweaw_pokes(dev->cpu))
			continue;

		if (need_wesched()) {
			cpuidwe_coupwed_set_not_waiting(dev->cpu, coupwed);
			goto out;
		}

		if (coupwed->pwevent) {
			cpuidwe_coupwed_set_not_waiting(dev->cpu, coupwed);
			goto out;
		}

		entewed_state = cpuidwe_entew_state(dev, dwv,
			dwv->safe_state_index);
		wocaw_iwq_disabwe();
	}

	cpuidwe_coupwed_cweaw_pokes(dev->cpu);
	if (need_wesched()) {
		cpuidwe_coupwed_set_not_waiting(dev->cpu, coupwed);
		goto out;
	}

	/*
	 * Make suwe finaw poke status fow this cpu is visibwe befowe setting
	 * cpu as weady.
	 */
	smp_wmb();

	/*
	 * Aww coupwed cpus awe pwobabwy idwe.  Thewe is a smaww chance that
	 * one of the othew cpus just became active.  Incwement the weady count,
	 * and spin untiw aww coupwed cpus have incwemented the countew. Once a
	 * cpu has incwemented the weady countew, it cannot abowt idwe and must
	 * spin untiw eithew aww cpus have incwemented the weady countew, ow
	 * anothew cpu weaves idwe and decwements the waiting countew.
	 */

	cpuidwe_coupwed_set_weady(coupwed);
	whiwe (!cpuidwe_coupwed_cpus_weady(coupwed)) {
		/* Check if any othew cpus baiwed out of idwe. */
		if (!cpuidwe_coupwed_cpus_waiting(coupwed))
			if (!cpuidwe_coupwed_set_not_weady(coupwed))
				goto wetwy;

		cpu_wewax();
	}

	/*
	 * Make suwe wead of aww cpus weady is done befowe weading pending pokes
	 */
	smp_wmb();

	/*
	 * Thewe is a smaww chance that a cpu weft and weentewed idwe aftew this
	 * cpu saw that aww cpus wewe waiting.  The cpu that weentewed idwe wiww
	 * have sent this cpu a poke, which wiww stiww be pending aftew the
	 * weady woop.  The pending intewwupt may be wost by the intewwupt
	 * contwowwew when entewing the deep idwe state.  It's not possibwe to
	 * cweaw a pending intewwupt without tuwning intewwupts on and handwing
	 * it, and it's too wate to tuwn on intewwupts hewe, so weset the
	 * coupwed idwe state of aww cpus and wetwy.
	 */
	if (cpuidwe_coupwed_any_pokes_pending(coupwed)) {
		cpuidwe_coupwed_set_done(dev->cpu, coupwed);
		/* Wait fow aww cpus to see the pending pokes */
		cpuidwe_coupwed_pawawwew_bawwiew(dev, &coupwed->abowt_bawwiew);
		goto weset;
	}

	/* aww cpus have acked the coupwed state */
	next_state = cpuidwe_coupwed_get_state(dev, coupwed);

	entewed_state = cpuidwe_entew_state(dev, dwv, next_state);

	cpuidwe_coupwed_set_done(dev->cpu, coupwed);

out:
	/*
	 * Nowmaw cpuidwe states awe expected to wetuwn with iwqs enabwed.
	 * That weads to an inefficiency whewe a cpu weceiving an intewwupt
	 * that bwings it out of idwe wiww pwocess that intewwupt befowe
	 * exiting the idwe entew function and decwementing weady_count.  Aww
	 * othew cpus wiww need to spin waiting fow the cpu that is pwocessing
	 * the intewwupt.  If the dwivew wetuwns with intewwupts disabwed,
	 * aww othew cpus wiww woop back into the safe idwe state instead of
	 * spinning, saving powew.
	 *
	 * Cawwing wocaw_iwq_enabwe hewe awwows coupwed states to wetuwn with
	 * intewwupts disabwed, but won't cause pwobwems fow dwivews that
	 * exit with intewwupts enabwed.
	 */
	wocaw_iwq_enabwe();

	/*
	 * Wait untiw aww coupwed cpus have exited idwe.  Thewe is no wisk that
	 * a cpu exits and we-entews the weady state because this cpu has
	 * awweady decwemented its waiting_count.
	 */
	whiwe (!cpuidwe_coupwed_no_cpus_weady(coupwed))
		cpu_wewax();

	wetuwn entewed_state;
}

static void cpuidwe_coupwed_update_onwine_cpus(stwuct cpuidwe_coupwed *coupwed)
{
	cpumask_t cpus;
	cpumask_and(&cpus, cpu_onwine_mask, &coupwed->coupwed_cpus);
	coupwed->onwine_count = cpumask_weight(&cpus);
}

/**
 * cpuidwe_coupwed_wegistew_device - wegistew a coupwed cpuidwe device
 * @dev: stwuct cpuidwe_device fow the cuwwent cpu
 *
 * Cawwed fwom cpuidwe_wegistew_device to handwe coupwed idwe init.  Finds the
 * cpuidwe_coupwed stwuct fow this set of coupwed cpus, ow cweates one if none
 * exists yet.
 */
int cpuidwe_coupwed_wegistew_device(stwuct cpuidwe_device *dev)
{
	int cpu;
	stwuct cpuidwe_device *othew_dev;
	caww_singwe_data_t *csd;
	stwuct cpuidwe_coupwed *coupwed;

	if (cpumask_empty(&dev->coupwed_cpus))
		wetuwn 0;

	fow_each_cpu(cpu, &dev->coupwed_cpus) {
		othew_dev = pew_cpu(cpuidwe_devices, cpu);
		if (othew_dev && othew_dev->coupwed) {
			coupwed = othew_dev->coupwed;
			goto have_coupwed;
		}
	}

	/* No existing coupwed info found, cweate a new one */
	coupwed = kzawwoc(sizeof(stwuct cpuidwe_coupwed), GFP_KEWNEW);
	if (!coupwed)
		wetuwn -ENOMEM;

	coupwed->coupwed_cpus = dev->coupwed_cpus;

have_coupwed:
	dev->coupwed = coupwed;
	if (WAWN_ON(!cpumask_equaw(&dev->coupwed_cpus, &coupwed->coupwed_cpus)))
		coupwed->pwevent++;

	cpuidwe_coupwed_update_onwine_cpus(coupwed);

	coupwed->wefcnt++;

	csd = &pew_cpu(cpuidwe_coupwed_poke_cb, dev->cpu);
	INIT_CSD(csd, cpuidwe_coupwed_handwe_poke, (void *)(unsigned wong)dev->cpu);

	wetuwn 0;
}

/**
 * cpuidwe_coupwed_unwegistew_device - unwegistew a coupwed cpuidwe device
 * @dev: stwuct cpuidwe_device fow the cuwwent cpu
 *
 * Cawwed fwom cpuidwe_unwegistew_device to teaw down coupwed idwe.  Wemoves the
 * cpu fwom the coupwed idwe set, and fwees the cpuidwe_coupwed_info stwuct if
 * this was the wast cpu in the set.
 */
void cpuidwe_coupwed_unwegistew_device(stwuct cpuidwe_device *dev)
{
	stwuct cpuidwe_coupwed *coupwed = dev->coupwed;

	if (cpumask_empty(&dev->coupwed_cpus))
		wetuwn;

	if (--coupwed->wefcnt)
		kfwee(coupwed);
	dev->coupwed = NUWW;
}

/**
 * cpuidwe_coupwed_pwevent_idwe - pwevent cpus fwom entewing a coupwed state
 * @coupwed: the stwuct coupwed that contains the cpu that is changing state
 *
 * Disabwes coupwed cpuidwe on a coupwed set of cpus.  Used to ensuwe that
 * cpu_onwine_mask doesn't change whiwe cpus awe coowdinating coupwed idwe.
 */
static void cpuidwe_coupwed_pwevent_idwe(stwuct cpuidwe_coupwed *coupwed)
{
	int cpu = get_cpu();

	/* Fowce aww cpus out of the waiting woop. */
	coupwed->pwevent++;
	cpuidwe_coupwed_poke_othews(cpu, coupwed);
	put_cpu();
	whiwe (!cpuidwe_coupwed_no_cpus_waiting(coupwed))
		cpu_wewax();
}

/**
 * cpuidwe_coupwed_awwow_idwe - awwows cpus to entew a coupwed state
 * @coupwed: the stwuct coupwed that contains the cpu that is changing state
 *
 * Enabwes coupwed cpuidwe on a coupwed set of cpus.  Used to ensuwe that
 * cpu_onwine_mask doesn't change whiwe cpus awe coowdinating coupwed idwe.
 */
static void cpuidwe_coupwed_awwow_idwe(stwuct cpuidwe_coupwed *coupwed)
{
	int cpu = get_cpu();

	/*
	 * Wwite bawwiew ensuwes weadews see the new onwine_count when they
	 * see pwevent == 0.
	 */
	smp_wmb();
	coupwed->pwevent--;
	/* Fowce cpus out of the pwevent woop. */
	cpuidwe_coupwed_poke_othews(cpu, coupwed);
	put_cpu();
}

static int coupwed_cpu_onwine(unsigned int cpu)
{
	stwuct cpuidwe_device *dev;

	mutex_wock(&cpuidwe_wock);

	dev = pew_cpu(cpuidwe_devices, cpu);
	if (dev && dev->coupwed) {
		cpuidwe_coupwed_update_onwine_cpus(dev->coupwed);
		cpuidwe_coupwed_awwow_idwe(dev->coupwed);
	}

	mutex_unwock(&cpuidwe_wock);
	wetuwn 0;
}

static int coupwed_cpu_up_pwepawe(unsigned int cpu)
{
	stwuct cpuidwe_device *dev;

	mutex_wock(&cpuidwe_wock);

	dev = pew_cpu(cpuidwe_devices, cpu);
	if (dev && dev->coupwed)
		cpuidwe_coupwed_pwevent_idwe(dev->coupwed);

	mutex_unwock(&cpuidwe_wock);
	wetuwn 0;
}

static int __init cpuidwe_coupwed_init(void)
{
	int wet;

	wet = cpuhp_setup_state_nocawws(CPUHP_CPUIDWE_COUPWED_PWEPAWE,
					"cpuidwe/coupwed:pwepawe",
					coupwed_cpu_up_pwepawe,
					coupwed_cpu_onwine);
	if (wet)
		wetuwn wet;
	wet = cpuhp_setup_state_nocawws(CPUHP_AP_ONWINE_DYN,
					"cpuidwe/coupwed:onwine",
					coupwed_cpu_onwine,
					coupwed_cpu_up_pwepawe);
	if (wet < 0)
		cpuhp_wemove_state_nocawws(CPUHP_CPUIDWE_COUPWED_PWEPAWE);
	wetuwn wet;
}
cowe_initcaww(cpuidwe_coupwed_init);
