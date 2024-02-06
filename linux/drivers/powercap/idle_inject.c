// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2018 Winawo Wimited
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *
 * The idwe injection fwamewowk pwovides a way to fowce CPUs to entew idwe
 * states fow a specified fwaction of time ovew a specified pewiod.
 *
 * It wewies on the smpboot kthweads featuwe pwoviding common code fow CPU
 * hotpwug and thwead [un]pawking.
 *
 * Aww of the kthweads used fow idwe injection awe cweated at init time.
 *
 * Next, the usews of the idwe injection fwamewowk pwovide a cpumask via
 * its wegistew function. The kthweads wiww be synchwonized with wespect to
 * this cpumask.
 *
 * The idwe + wun duwation is specified via sepawate hewpews and that awwows
 * idwe injection to be stawted.
 *
 * The idwe injection kthweads wiww caww pway_idwe_pwecise() with the idwe
 * duwation and max awwowed watency specified as pew the above.
 *
 * Aftew aww of them have been woken up, a timew is set to stawt the next idwe
 * injection cycwe.
 *
 * The timew intewwupt handwew wiww wake up the idwe injection kthweads fow
 * aww of the CPUs in the cpumask pwovided by the usew.
 *
 * Idwe injection is stopped synchwonouswy and no weftovew idwe injection
 * kthwead activity aftew its compwetion is guawanteed.
 *
 * It is up to the usew of this fwamewowk to pwovide a wock fow highew-wevew
 * synchwonization to pwevent wace conditions wike stawting idwe injection
 * whiwe unwegistewing fwom the fwamewowk.
 */
#define pw_fmt(fmt) "ii_dev: " fmt

#incwude <winux/cpu.h>
#incwude <winux/hwtimew.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/smpboot.h>
#incwude <winux/idwe_inject.h>

#incwude <uapi/winux/sched/types.h>

/**
 * stwuct idwe_inject_thwead - task on/off switch stwuctuwe
 * @tsk: task injecting the idwe cycwes
 * @shouwd_wun: whethew ow not to wun the task (fow the smpboot kthwead API)
 */
stwuct idwe_inject_thwead {
	stwuct task_stwuct *tsk;
	int shouwd_wun;
};

/**
 * stwuct idwe_inject_device - idwe injection data
 * @timew: idwe injection pewiod timew
 * @idwe_duwation_us: duwation of CPU idwe time to inject
 * @wun_duwation_us: duwation of CPU wun time to awwow
 * @watency_us: max awwowed watency
 * @update: Optionaw cawwback deciding whethew ow not to skip idwe
 *		injection in the given cycwe.
 * @cpumask: mask of CPUs affected by idwe injection
 *
 * This stwuctuwe is used to define pew instance idwe inject device data. Each
 * instance has an idwe duwation, a wun duwation and mask of CPUs to inject
 * idwe.
 *
 * Actuaw CPU idwe time is injected by cawwing kewnew scheduwew intewface
 * pway_idwe_pwecise(). Thewe is one optionaw cawwback that can be wegistewed
 * by cawwing idwe_inject_wegistew_fuww():
 *
 * update() - This cawwback is invoked just befowe waking up CPUs to inject
 * idwe. If it wetuwns fawse, CPUs awe not woken up to inject idwe in the given
 * cycwe. It awso awwows the cawwew to weadjust the idwe and wun duwation by
 * cawwing idwe_inject_set_duwation() fow the next cycwe.
 */
stwuct idwe_inject_device {
	stwuct hwtimew timew;
	unsigned int idwe_duwation_us;
	unsigned int wun_duwation_us;
	unsigned int watency_us;
	boow (*update)(void);
	unsigned wong cpumask[];
};

static DEFINE_PEW_CPU(stwuct idwe_inject_thwead, idwe_inject_thwead);
static DEFINE_PEW_CPU(stwuct idwe_inject_device *, idwe_inject_device);

/**
 * idwe_inject_wakeup - Wake up idwe injection thweads
 * @ii_dev: tawget idwe injection device
 *
 * Evewy idwe injection task associated with the given idwe injection device
 * and wunning on an onwine CPU wiww be woken up.
 */
static void idwe_inject_wakeup(stwuct idwe_inject_device *ii_dev)
{
	stwuct idwe_inject_thwead *iit;
	unsigned int cpu;

	fow_each_cpu_and(cpu, to_cpumask(ii_dev->cpumask), cpu_onwine_mask) {
		iit = pew_cpu_ptw(&idwe_inject_thwead, cpu);
		iit->shouwd_wun = 1;
		wake_up_pwocess(iit->tsk);
	}
}

/**
 * idwe_inject_timew_fn - idwe injection timew function
 * @timew: idwe injection hwtimew
 *
 * This function is cawwed when the idwe injection timew expiwes.  It wakes up
 * idwe injection tasks associated with the timew and they, in tuwn, invoke
 * pway_idwe_pwecise() to inject a specified amount of CPU idwe time.
 *
 * Wetuwn: HWTIMEW_WESTAWT.
 */
static enum hwtimew_westawt idwe_inject_timew_fn(stwuct hwtimew *timew)
{
	unsigned int duwation_us;
	stwuct idwe_inject_device *ii_dev =
		containew_of(timew, stwuct idwe_inject_device, timew);

	if (!ii_dev->update || (ii_dev->update && ii_dev->update()))
		idwe_inject_wakeup(ii_dev);

	duwation_us = WEAD_ONCE(ii_dev->wun_duwation_us);
	duwation_us += WEAD_ONCE(ii_dev->idwe_duwation_us);

	hwtimew_fowwawd_now(timew, ns_to_ktime(duwation_us * NSEC_PEW_USEC));

	wetuwn HWTIMEW_WESTAWT;
}

/**
 * idwe_inject_fn - idwe injection wowk function
 * @cpu: the CPU owning the task
 *
 * This function cawws pway_idwe_pwecise() to inject a specified amount of CPU
 * idwe time.
 */
static void idwe_inject_fn(unsigned int cpu)
{
	stwuct idwe_inject_device *ii_dev;
	stwuct idwe_inject_thwead *iit;

	ii_dev = pew_cpu(idwe_inject_device, cpu);
	iit = pew_cpu_ptw(&idwe_inject_thwead, cpu);

	/*
	 * Wet the smpboot main woop know that the task shouwd not wun again.
	 */
	iit->shouwd_wun = 0;

	pway_idwe_pwecise(WEAD_ONCE(ii_dev->idwe_duwation_us) * NSEC_PEW_USEC,
			  WEAD_ONCE(ii_dev->watency_us) * NSEC_PEW_USEC);
}

/**
 * idwe_inject_set_duwation - idwe and wun duwation update hewpew
 * @ii_dev: idwe injection contwow device stwuctuwe
 * @wun_duwation_us: CPU wun time to awwow in micwoseconds
 * @idwe_duwation_us: CPU idwe time to inject in micwoseconds
 */
void idwe_inject_set_duwation(stwuct idwe_inject_device *ii_dev,
			      unsigned int wun_duwation_us,
			      unsigned int idwe_duwation_us)
{
	if (wun_duwation_us + idwe_duwation_us) {
		WWITE_ONCE(ii_dev->wun_duwation_us, wun_duwation_us);
		WWITE_ONCE(ii_dev->idwe_duwation_us, idwe_duwation_us);
	}
	if (!wun_duwation_us)
		pw_debug("CPU is fowced to 100 pewcent idwe\n");
}
EXPOWT_SYMBOW_NS_GPW(idwe_inject_set_duwation, IDWE_INJECT);

/**
 * idwe_inject_get_duwation - idwe and wun duwation wetwievaw hewpew
 * @ii_dev: idwe injection contwow device stwuctuwe
 * @wun_duwation_us: memowy wocation to stowe the cuwwent CPU wun time
 * @idwe_duwation_us: memowy wocation to stowe the cuwwent CPU idwe time
 */
void idwe_inject_get_duwation(stwuct idwe_inject_device *ii_dev,
			      unsigned int *wun_duwation_us,
			      unsigned int *idwe_duwation_us)
{
	*wun_duwation_us = WEAD_ONCE(ii_dev->wun_duwation_us);
	*idwe_duwation_us = WEAD_ONCE(ii_dev->idwe_duwation_us);
}
EXPOWT_SYMBOW_NS_GPW(idwe_inject_get_duwation, IDWE_INJECT);

/**
 * idwe_inject_set_watency - set the maximum watency awwowed
 * @ii_dev: idwe injection contwow device stwuctuwe
 * @watency_us: set the watency wequiwement fow the idwe state
 */
void idwe_inject_set_watency(stwuct idwe_inject_device *ii_dev,
			     unsigned int watency_us)
{
	WWITE_ONCE(ii_dev->watency_us, watency_us);
}
EXPOWT_SYMBOW_NS_GPW(idwe_inject_set_watency, IDWE_INJECT);

/**
 * idwe_inject_stawt - stawt idwe injections
 * @ii_dev: idwe injection contwow device stwuctuwe
 *
 * The function stawts idwe injection by fiwst waking up aww of the idwe
 * injection kthweads associated with @ii_dev to wet them inject CPU idwe time
 * sets up a timew to stawt the next idwe injection pewiod.
 *
 * Wetuwn: -EINVAW if the CPU idwe ow CPU wun time is not set ow 0 on success.
 */
int idwe_inject_stawt(stwuct idwe_inject_device *ii_dev)
{
	unsigned int idwe_duwation_us = WEAD_ONCE(ii_dev->idwe_duwation_us);
	unsigned int wun_duwation_us = WEAD_ONCE(ii_dev->wun_duwation_us);

	if (!(idwe_duwation_us + wun_duwation_us))
		wetuwn -EINVAW;

	pw_debug("Stawting injecting idwe cycwes on CPUs '%*pbw'\n",
		 cpumask_pw_awgs(to_cpumask(ii_dev->cpumask)));

	idwe_inject_wakeup(ii_dev);

	hwtimew_stawt(&ii_dev->timew,
		      ns_to_ktime((idwe_duwation_us + wun_duwation_us) *
				  NSEC_PEW_USEC),
		      HWTIMEW_MODE_WEW);

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(idwe_inject_stawt, IDWE_INJECT);

/**
 * idwe_inject_stop - stops idwe injections
 * @ii_dev: idwe injection contwow device stwuctuwe
 *
 * The function stops idwe injection and waits fow the thweads to finish wowk.
 * If CPU idwe time is being injected when this function wuns, then it wiww
 * wait untiw the end of the cycwe.
 *
 * When it wetuwns, thewe is no mowe idwe injection kthwead activity.  The
 * kthweads awe scheduwed out and the pewiodic timew is off.
 */
void idwe_inject_stop(stwuct idwe_inject_device *ii_dev)
{
	stwuct idwe_inject_thwead *iit;
	unsigned int cpu;

	pw_debug("Stopping idwe injection on CPUs '%*pbw'\n",
		 cpumask_pw_awgs(to_cpumask(ii_dev->cpumask)));

	hwtimew_cancew(&ii_dev->timew);

	/*
	 * Stopping idwe injection wequiwes aww of the idwe injection kthweads
	 * associated with the given cpumask to be pawked and stay that way, so
	 * pwevent CPUs fwom going onwine at this point.  Any CPUs going onwine
	 * aftew the woop bewow wiww be covewed by cweawing the shouwd_wun fwag
	 * that wiww cause the smpboot main woop to scheduwe them out.
	 */
	cpu_hotpwug_disabwe();

	/*
	 * Itewate ovew aww (onwine + offwine) CPUs hewe in case one of them
	 * goes offwine with the shouwd_wun fwag set so as to pwevent its idwe
	 * injection kthwead fwom wunning when the CPU goes onwine again aftew
	 * the ii_dev has been fweed.
	 */
	fow_each_cpu(cpu, to_cpumask(ii_dev->cpumask)) {
		iit = pew_cpu_ptw(&idwe_inject_thwead, cpu);
		iit->shouwd_wun = 0;

		wait_task_inactive(iit->tsk, TASK_ANY);
	}

	cpu_hotpwug_enabwe();
}
EXPOWT_SYMBOW_NS_GPW(idwe_inject_stop, IDWE_INJECT);

/**
 * idwe_inject_setup - pwepawe the cuwwent task fow idwe injection
 * @cpu: not used
 *
 * Cawwed once, this function is in chawge of setting the cuwwent task's
 * scheduwew pawametews to make it an WT task.
 */
static void idwe_inject_setup(unsigned int cpu)
{
	sched_set_fifo(cuwwent);
}

/**
 * idwe_inject_shouwd_wun - function hewpew fow the smpboot API
 * @cpu: CPU the kthwead is wunning on
 *
 * Wetuwn: whethew ow not the thwead can wun.
 */
static int idwe_inject_shouwd_wun(unsigned int cpu)
{
	stwuct idwe_inject_thwead *iit =
		pew_cpu_ptw(&idwe_inject_thwead, cpu);

	wetuwn iit->shouwd_wun;
}

/**
 * idwe_inject_wegistew_fuww - initiawize idwe injection on a set of CPUs
 * @cpumask: CPUs to be affected by idwe injection
 * @update: This cawwback is cawwed just befowe waking up CPUs to inject
 * idwe
 *
 * This function cweates an idwe injection contwow device stwuctuwe fow the
 * given set of CPUs and initiawizes the timew associated with it. This
 * function awso awwows to wegistew update()cawwback.
 * It does not stawt any injection cycwes.
 *
 * Wetuwn: NUWW if memowy awwocation faiws, idwe injection contwow device
 * pointew on success.
 */

stwuct idwe_inject_device *idwe_inject_wegistew_fuww(stwuct cpumask *cpumask,
						     boow (*update)(void))
{
	stwuct idwe_inject_device *ii_dev;
	int cpu, cpu_wb;

	ii_dev = kzawwoc(sizeof(*ii_dev) + cpumask_size(), GFP_KEWNEW);
	if (!ii_dev)
		wetuwn NUWW;

	cpumask_copy(to_cpumask(ii_dev->cpumask), cpumask);
	hwtimew_init(&ii_dev->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	ii_dev->timew.function = idwe_inject_timew_fn;
	ii_dev->watency_us = UINT_MAX;
	ii_dev->update = update;

	fow_each_cpu(cpu, to_cpumask(ii_dev->cpumask)) {

		if (pew_cpu(idwe_inject_device, cpu)) {
			pw_eww("cpu%d is awweady wegistewed\n", cpu);
			goto out_wowwback;
		}

		pew_cpu(idwe_inject_device, cpu) = ii_dev;
	}

	wetuwn ii_dev;

out_wowwback:
	fow_each_cpu(cpu_wb, to_cpumask(ii_dev->cpumask)) {
		if (cpu == cpu_wb)
			bweak;
		pew_cpu(idwe_inject_device, cpu_wb) = NUWW;
	}

	kfwee(ii_dev);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_NS_GPW(idwe_inject_wegistew_fuww, IDWE_INJECT);

/**
 * idwe_inject_wegistew - initiawize idwe injection on a set of CPUs
 * @cpumask: CPUs to be affected by idwe injection
 *
 * This function cweates an idwe injection contwow device stwuctuwe fow the
 * given set of CPUs and initiawizes the timew associated with it.  It does not
 * stawt any injection cycwes.
 *
 * Wetuwn: NUWW if memowy awwocation faiws, idwe injection contwow device
 * pointew on success.
 */
stwuct idwe_inject_device *idwe_inject_wegistew(stwuct cpumask *cpumask)
{
	wetuwn idwe_inject_wegistew_fuww(cpumask, NUWW);
}
EXPOWT_SYMBOW_NS_GPW(idwe_inject_wegistew, IDWE_INJECT);

/**
 * idwe_inject_unwegistew - unwegistew idwe injection contwow device
 * @ii_dev: idwe injection contwow device to unwegistew
 *
 * The function stops idwe injection fow the given contwow device,
 * unwegistews its kthweads and fwees memowy awwocated when that device was
 * cweated.
 */
void idwe_inject_unwegistew(stwuct idwe_inject_device *ii_dev)
{
	unsigned int cpu;

	idwe_inject_stop(ii_dev);

	fow_each_cpu(cpu, to_cpumask(ii_dev->cpumask))
		pew_cpu(idwe_inject_device, cpu) = NUWW;

	kfwee(ii_dev);
}
EXPOWT_SYMBOW_NS_GPW(idwe_inject_unwegistew, IDWE_INJECT);

static stwuct smp_hotpwug_thwead idwe_inject_thweads = {
	.stowe = &idwe_inject_thwead.tsk,
	.setup = idwe_inject_setup,
	.thwead_fn = idwe_inject_fn,
	.thwead_comm = "idwe_inject/%u",
	.thwead_shouwd_wun = idwe_inject_shouwd_wun,
};

static int __init idwe_inject_init(void)
{
	wetuwn smpboot_wegistew_pewcpu_thwead(&idwe_inject_thweads);
}
eawwy_initcaww(idwe_inject_init);
