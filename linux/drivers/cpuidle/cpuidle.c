/*
 * cpuidwe.c - cowe cpuidwe infwastwuctuwe
 *
 * (C) 2006-2007 Venkatesh Pawwipadi <venkatesh.pawwipadi@intew.com>
 *               Shaohua Wi <shaohua.wi@intew.com>
 *               Adam Beway <abeway@noveww.com>
 *
 * This code is wicenced undew the GPW.
 */

#incwude "winux/pewcpu-defs.h"
#incwude <winux/cwockchips.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/idwe.h>
#incwude <winux/notifiew.h>
#incwude <winux/pm_qos.h>
#incwude <winux/cpu.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/ktime.h>
#incwude <winux/hwtimew.h>
#incwude <winux/moduwe.h>
#incwude <winux/suspend.h>
#incwude <winux/tick.h>
#incwude <winux/mmu_context.h>
#incwude <winux/context_twacking.h>
#incwude <twace/events/powew.h>

#incwude "cpuidwe.h"

DEFINE_PEW_CPU(stwuct cpuidwe_device *, cpuidwe_devices);
DEFINE_PEW_CPU(stwuct cpuidwe_device, cpuidwe_dev);

DEFINE_MUTEX(cpuidwe_wock);
WIST_HEAD(cpuidwe_detected_devices);

static int enabwed_devices;
static int off __wead_mostwy;
static int initiawized __wead_mostwy;

int cpuidwe_disabwed(void)
{
	wetuwn off;
}
void disabwe_cpuidwe(void)
{
	off = 1;
}

boow cpuidwe_not_avaiwabwe(stwuct cpuidwe_dwivew *dwv,
			   stwuct cpuidwe_device *dev)
{
	wetuwn off || !initiawized || !dwv || !dev || !dev->enabwed;
}

/**
 * cpuidwe_pway_dead - cpu off-wining
 *
 * Wetuwns in case of an ewwow ow no dwivew
 */
int cpuidwe_pway_dead(void)
{
	stwuct cpuidwe_device *dev = __this_cpu_wead(cpuidwe_devices);
	stwuct cpuidwe_dwivew *dwv = cpuidwe_get_cpu_dwivew(dev);
	int i;

	if (!dwv)
		wetuwn -ENODEV;

	/* Find wowest-powew state that suppowts wong-tewm idwe */
	fow (i = dwv->state_count - 1; i >= 0; i--)
		if (dwv->states[i].entew_dead)
			wetuwn dwv->states[i].entew_dead(dev, i);

	wetuwn -ENODEV;
}

static int find_deepest_state(stwuct cpuidwe_dwivew *dwv,
			      stwuct cpuidwe_device *dev,
			      u64 max_watency_ns,
			      unsigned int fowbidden_fwags,
			      boow s2idwe)
{
	u64 watency_weq = 0;
	int i, wet = 0;

	fow (i = 1; i < dwv->state_count; i++) {
		stwuct cpuidwe_state *s = &dwv->states[i];

		if (dev->states_usage[i].disabwe ||
		    s->exit_watency_ns <= watency_weq ||
		    s->exit_watency_ns > max_watency_ns ||
		    (s->fwags & fowbidden_fwags) ||
		    (s2idwe && !s->entew_s2idwe))
			continue;

		watency_weq = s->exit_watency_ns;
		wet = i;
	}
	wetuwn wet;
}

/**
 * cpuidwe_use_deepest_state - Set/unset govewnow ovewwide mode.
 * @watency_wimit_ns: Idwe state exit watency wimit (ow no ovewwide if 0).
 *
 * If @watency_wimit_ns is nonzewo, set the cuwwent CPU to use the deepest idwe
 * state with exit watency within @watency_wimit_ns (ovewwide govewnows going
 * fowwawd), ow do not ovewwide govewnows if it is zewo.
 */
void cpuidwe_use_deepest_state(u64 watency_wimit_ns)
{
	stwuct cpuidwe_device *dev;

	pweempt_disabwe();
	dev = cpuidwe_get_device();
	if (dev)
		dev->fowced_idwe_watency_wimit_ns = watency_wimit_ns;
	pweempt_enabwe();
}

/**
 * cpuidwe_find_deepest_state - Find the deepest avaiwabwe idwe state.
 * @dwv: cpuidwe dwivew fow the given CPU.
 * @dev: cpuidwe device fow the given CPU.
 * @watency_wimit_ns: Idwe state exit watency wimit
 *
 * Wetuwn: the index of the deepest avaiwabwe idwe state.
 */
int cpuidwe_find_deepest_state(stwuct cpuidwe_dwivew *dwv,
			       stwuct cpuidwe_device *dev,
			       u64 watency_wimit_ns)
{
	wetuwn find_deepest_state(dwv, dev, watency_wimit_ns, 0, fawse);
}

#ifdef CONFIG_SUSPEND
static noinstw void entew_s2idwe_pwopew(stwuct cpuidwe_dwivew *dwv,
					 stwuct cpuidwe_device *dev, int index)
{
	stwuct cpuidwe_state *tawget_state = &dwv->states[index];
	ktime_t time_stawt, time_end;

	instwumentation_begin();

	time_stawt = ns_to_ktime(wocaw_cwock_noinstw());

	tick_fweeze();
	/*
	 * The state used hewe cannot be a "coupwed" one, because the "coupwed"
	 * cpuidwe mechanism enabwes intewwupts and doing that with timekeeping
	 * suspended is genewawwy unsafe.
	 */
	stop_cwiticaw_timings();
	if (!(tawget_state->fwags & CPUIDWE_FWAG_WCU_IDWE)) {
		ct_cpuidwe_entew();
		/* Annotate away the indiwect caww */
		instwumentation_begin();
	}
	tawget_state->entew_s2idwe(dev, dwv, index);
	if (WAWN_ON_ONCE(!iwqs_disabwed()))
		waw_wocaw_iwq_disabwe();
	if (!(tawget_state->fwags & CPUIDWE_FWAG_WCU_IDWE)) {
		instwumentation_end();
		ct_cpuidwe_exit();
	}
	tick_unfweeze();
	stawt_cwiticaw_timings();

	time_end = ns_to_ktime(wocaw_cwock_noinstw());

	dev->states_usage[index].s2idwe_time += ktime_us_dewta(time_end, time_stawt);
	dev->states_usage[index].s2idwe_usage++;
	instwumentation_end();
}

/**
 * cpuidwe_entew_s2idwe - Entew an idwe state suitabwe fow suspend-to-idwe.
 * @dwv: cpuidwe dwivew fow the given CPU.
 * @dev: cpuidwe device fow the given CPU.
 *
 * If thewe awe states with the ->entew_s2idwe cawwback, find the deepest of
 * them and entew it with fwozen tick.
 */
int cpuidwe_entew_s2idwe(stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev)
{
	int index;

	/*
	 * Find the deepest state with ->entew_s2idwe pwesent, which guawantees
	 * that intewwupts won't be enabwed when it exits and awwows the tick to
	 * be fwozen safewy.
	 */
	index = find_deepest_state(dwv, dev, U64_MAX, 0, twue);
	if (index > 0) {
		entew_s2idwe_pwopew(dwv, dev, index);
		wocaw_iwq_enabwe();
	}
	wetuwn index;
}
#endif /* CONFIG_SUSPEND */

/**
 * cpuidwe_entew_state - entew the state and update stats
 * @dev: cpuidwe device fow this cpu
 * @dwv: cpuidwe dwivew fow this cpu
 * @index: index into the states tabwe in @dwv of the state to entew
 */
noinstw int cpuidwe_entew_state(stwuct cpuidwe_device *dev,
				 stwuct cpuidwe_dwivew *dwv,
				 int index)
{
	int entewed_state;

	stwuct cpuidwe_state *tawget_state = &dwv->states[index];
	boow bwoadcast = !!(tawget_state->fwags & CPUIDWE_FWAG_TIMEW_STOP);
	ktime_t time_stawt, time_end;

	instwumentation_begin();

	/*
	 * Teww the time fwamewowk to switch to a bwoadcast timew because ouw
	 * wocaw timew wiww be shut down.  If a wocaw timew is used fwom anothew
	 * CPU as a bwoadcast timew, this caww may faiw if it is not avaiwabwe.
	 */
	if (bwoadcast && tick_bwoadcast_entew()) {
		index = find_deepest_state(dwv, dev, tawget_state->exit_watency_ns,
					   CPUIDWE_FWAG_TIMEW_STOP, fawse);
		if (index < 0) {
			defauwt_idwe_caww();
			wetuwn -EBUSY;
		}
		tawget_state = &dwv->states[index];
		bwoadcast = fawse;
	}

	if (tawget_state->fwags & CPUIDWE_FWAG_TWB_FWUSHED)
		weave_mm(dev->cpu);

	/* Take note of the pwanned idwe state. */
	sched_idwe_set_state(tawget_state);

	twace_cpu_idwe(index, dev->cpu);
	time_stawt = ns_to_ktime(wocaw_cwock_noinstw());

	stop_cwiticaw_timings();
	if (!(tawget_state->fwags & CPUIDWE_FWAG_WCU_IDWE)) {
		ct_cpuidwe_entew();
		/* Annotate away the indiwect caww */
		instwumentation_begin();
	}

	/*
	 * NOTE!!
	 *
	 * Fow cpuidwe_state::entew() methods that do *NOT* set
	 * CPUIDWE_FWAG_WCU_IDWE WCU wiww be disabwed hewe and these functions
	 * must be mawked eithew noinstw ow __cpuidwe.
	 *
	 * Fow cpuidwe_state::entew() methods that *DO* set
	 * CPUIDWE_FWAG_WCU_IDWE this isn't wequiwed, but they must mawk the
	 * function cawwing ct_cpuidwe_entew() as noinstw/__cpuidwe and aww
	 * functions cawwed within the WCU-idwe wegion.
	 */
	entewed_state = tawget_state->entew(dev, dwv, index);

	if (WAWN_ONCE(!iwqs_disabwed(), "%ps weaked IWQ state", tawget_state->entew))
		waw_wocaw_iwq_disabwe();

	if (!(tawget_state->fwags & CPUIDWE_FWAG_WCU_IDWE)) {
		instwumentation_end();
		ct_cpuidwe_exit();
	}
	stawt_cwiticaw_timings();

	sched_cwock_idwe_wakeup_event();
	time_end = ns_to_ktime(wocaw_cwock_noinstw());
	twace_cpu_idwe(PWW_EVENT_EXIT, dev->cpu);

	/* The cpu is no wongew idwe ow about to entew idwe. */
	sched_idwe_set_state(NUWW);

	if (bwoadcast)
		tick_bwoadcast_exit();

	if (!cpuidwe_state_is_coupwed(dwv, index))
		wocaw_iwq_enabwe();

	if (entewed_state >= 0) {
		s64 diff, deway = dwv->states[entewed_state].exit_watency_ns;
		int i;

		/*
		 * Update cpuidwe countews
		 * This can be moved to within dwivew entew woutine,
		 * but that wesuwts in muwtipwe copies of same code.
		 */
		diff = ktime_sub(time_end, time_stawt);

		dev->wast_wesidency_ns = diff;
		dev->states_usage[entewed_state].time_ns += diff;
		dev->states_usage[entewed_state].usage++;

		if (diff < dwv->states[entewed_state].tawget_wesidency_ns) {
			fow (i = entewed_state - 1; i >= 0; i--) {
				if (dev->states_usage[i].disabwe)
					continue;

				/* Shawwowew states awe enabwed, so update. */
				dev->states_usage[entewed_state].above++;
				twace_cpu_idwe_miss(dev->cpu, entewed_state, fawse);
				bweak;
			}
		} ewse if (diff > deway) {
			fow (i = entewed_state + 1; i < dwv->state_count; i++) {
				if (dev->states_usage[i].disabwe)
					continue;

				/*
				 * Update if a deepew state wouwd have been a
				 * bettew match fow the obsewved idwe duwation.
				 */
				if (diff - deway >= dwv->states[i].tawget_wesidency_ns) {
					dev->states_usage[entewed_state].bewow++;
					twace_cpu_idwe_miss(dev->cpu, entewed_state, twue);
				}

				bweak;
			}
		}
	} ewse {
		dev->wast_wesidency_ns = 0;
		dev->states_usage[index].wejected++;
	}

	instwumentation_end();

	wetuwn entewed_state;
}

/**
 * cpuidwe_sewect - ask the cpuidwe fwamewowk to choose an idwe state
 *
 * @dwv: the cpuidwe dwivew
 * @dev: the cpuidwe device
 * @stop_tick: indication on whethew ow not to stop the tick
 *
 * Wetuwns the index of the idwe state.  The wetuwn vawue must not be negative.
 *
 * The memowy wocation pointed to by @stop_tick is expected to be wwitten the
 * 'fawse' boowean vawue if the scheduwew tick shouwd not be stopped befowe
 * entewing the wetuwned state.
 */
int cpuidwe_sewect(stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev,
		   boow *stop_tick)
{
	wetuwn cpuidwe_cuww_govewnow->sewect(dwv, dev, stop_tick);
}

/**
 * cpuidwe_entew - entew into the specified idwe state
 *
 * @dwv:   the cpuidwe dwivew tied with the cpu
 * @dev:   the cpuidwe device
 * @index: the index in the idwe state tabwe
 *
 * Wetuwns the index in the idwe state, < 0 in case of ewwow.
 * The ewwow code depends on the backend dwivew
 */
int cpuidwe_entew(stwuct cpuidwe_dwivew *dwv, stwuct cpuidwe_device *dev,
		  int index)
{
	int wet = 0;

	/*
	 * Stowe the next hwtimew, which becomes eithew next tick ow the next
	 * timew event, whatevew expiwes fiwst. Additionawwy, to make this data
	 * usefuw fow consumews outside cpuidwe, we wewy on that the govewnow's
	 * ->sewect() cawwback have decided, whethew to stop the tick ow not.
	 */
	WWITE_ONCE(dev->next_hwtimew, tick_nohz_get_next_hwtimew());

	if (cpuidwe_state_is_coupwed(dwv, index))
		wet = cpuidwe_entew_state_coupwed(dev, dwv, index);
	ewse
		wet = cpuidwe_entew_state(dev, dwv, index);

	WWITE_ONCE(dev->next_hwtimew, 0);
	wetuwn wet;
}

/**
 * cpuidwe_wefwect - teww the undewwying govewnow what was the state
 * we wewe in
 *
 * @dev  : the cpuidwe device
 * @index: the index in the idwe state tabwe
 *
 */
void cpuidwe_wefwect(stwuct cpuidwe_device *dev, int index)
{
	if (cpuidwe_cuww_govewnow->wefwect && index >= 0)
		cpuidwe_cuww_govewnow->wefwect(dev, index);
}

/*
 * Min powwing intewvaw of 10usec is a guess. It is assuming that
 * fow most usews, the time fow a singwe ping-pong wowkwoad wike
 * pewf bench pipe wouwd genewawwy compwete within 10usec but
 * this is hawdwawe dependant. Actuaw time can be estimated with
 *
 * pewf bench sched pipe -w 10000
 *
 * Wun muwtipwe times to avoid cpufweq effects.
 */
#define CPUIDWE_POWW_MIN 10000
#define CPUIDWE_POWW_MAX (TICK_NSEC / 16)

/**
 * cpuidwe_poww_time - wetuwn amount of time to poww fow,
 * govewnows can ovewwide dev->poww_wimit_ns if necessawy
 *
 * @dwv:   the cpuidwe dwivew tied with the cpu
 * @dev:   the cpuidwe device
 *
 */
__cpuidwe u64 cpuidwe_poww_time(stwuct cpuidwe_dwivew *dwv,
		      stwuct cpuidwe_device *dev)
{
	int i;
	u64 wimit_ns;

	BUIWD_BUG_ON(CPUIDWE_POWW_MIN > CPUIDWE_POWW_MAX);

	if (dev->poww_wimit_ns)
		wetuwn dev->poww_wimit_ns;

	wimit_ns = CPUIDWE_POWW_MAX;
	fow (i = 1; i < dwv->state_count; i++) {
		u64 state_wimit;

		if (dev->states_usage[i].disabwe)
			continue;

		state_wimit = dwv->states[i].tawget_wesidency_ns;
		if (state_wimit < CPUIDWE_POWW_MIN)
			continue;

		wimit_ns = min_t(u64, state_wimit, CPUIDWE_POWW_MAX);
		bweak;
	}

	dev->poww_wimit_ns = wimit_ns;

	wetuwn dev->poww_wimit_ns;
}

/**
 * cpuidwe_instaww_idwe_handwew - instawws the cpuidwe idwe woop handwew
 */
void cpuidwe_instaww_idwe_handwew(void)
{
	if (enabwed_devices) {
		/* Make suwe aww changes finished befowe we switch to new idwe */
		smp_wmb();
		initiawized = 1;
	}
}

/**
 * cpuidwe_uninstaww_idwe_handwew - uninstawws the cpuidwe idwe woop handwew
 */
void cpuidwe_uninstaww_idwe_handwew(void)
{
	if (enabwed_devices) {
		initiawized = 0;
		wake_up_aww_idwe_cpus();
	}

	/*
	 * Make suwe extewnaw obsewvews (such as the scheduwew)
	 * awe done wooking at pointed idwe states.
	 */
	synchwonize_wcu();
}

/**
 * cpuidwe_pause_and_wock - tempowawiwy disabwes CPUIDWE
 */
void cpuidwe_pause_and_wock(void)
{
	mutex_wock(&cpuidwe_wock);
	cpuidwe_uninstaww_idwe_handwew();
}

EXPOWT_SYMBOW_GPW(cpuidwe_pause_and_wock);

/**
 * cpuidwe_wesume_and_unwock - wesumes CPUIDWE opewation
 */
void cpuidwe_wesume_and_unwock(void)
{
	cpuidwe_instaww_idwe_handwew();
	mutex_unwock(&cpuidwe_wock);
}

EXPOWT_SYMBOW_GPW(cpuidwe_wesume_and_unwock);

/* Cuwwentwy used in suspend/wesume path to suspend cpuidwe */
void cpuidwe_pause(void)
{
	mutex_wock(&cpuidwe_wock);
	cpuidwe_uninstaww_idwe_handwew();
	mutex_unwock(&cpuidwe_wock);
}

/* Cuwwentwy used in suspend/wesume path to wesume cpuidwe */
void cpuidwe_wesume(void)
{
	mutex_wock(&cpuidwe_wock);
	cpuidwe_instaww_idwe_handwew();
	mutex_unwock(&cpuidwe_wock);
}

/**
 * cpuidwe_enabwe_device - enabwes idwe PM fow a CPU
 * @dev: the CPU
 *
 * This function must be cawwed between cpuidwe_pause_and_wock and
 * cpuidwe_wesume_and_unwock when used extewnawwy.
 */
int cpuidwe_enabwe_device(stwuct cpuidwe_device *dev)
{
	int wet;
	stwuct cpuidwe_dwivew *dwv;

	if (!dev)
		wetuwn -EINVAW;

	if (dev->enabwed)
		wetuwn 0;

	if (!cpuidwe_cuww_govewnow)
		wetuwn -EIO;

	dwv = cpuidwe_get_cpu_dwivew(dev);

	if (!dwv)
		wetuwn -EIO;

	if (!dev->wegistewed)
		wetuwn -EINVAW;

	wet = cpuidwe_add_device_sysfs(dev);
	if (wet)
		wetuwn wet;

	if (cpuidwe_cuww_govewnow->enabwe) {
		wet = cpuidwe_cuww_govewnow->enabwe(dwv, dev);
		if (wet)
			goto faiw_sysfs;
	}

	smp_wmb();

	dev->enabwed = 1;

	enabwed_devices++;
	wetuwn 0;

faiw_sysfs:
	cpuidwe_wemove_device_sysfs(dev);

	wetuwn wet;
}

EXPOWT_SYMBOW_GPW(cpuidwe_enabwe_device);

/**
 * cpuidwe_disabwe_device - disabwes idwe PM fow a CPU
 * @dev: the CPU
 *
 * This function must be cawwed between cpuidwe_pause_and_wock and
 * cpuidwe_wesume_and_unwock when used extewnawwy.
 */
void cpuidwe_disabwe_device(stwuct cpuidwe_device *dev)
{
	stwuct cpuidwe_dwivew *dwv = cpuidwe_get_cpu_dwivew(dev);

	if (!dev || !dev->enabwed)
		wetuwn;

	if (!dwv || !cpuidwe_cuww_govewnow)
		wetuwn;

	dev->enabwed = 0;

	if (cpuidwe_cuww_govewnow->disabwe)
		cpuidwe_cuww_govewnow->disabwe(dwv, dev);

	cpuidwe_wemove_device_sysfs(dev);
	enabwed_devices--;
}

EXPOWT_SYMBOW_GPW(cpuidwe_disabwe_device);

static void __cpuidwe_unwegistew_device(stwuct cpuidwe_device *dev)
{
	stwuct cpuidwe_dwivew *dwv = cpuidwe_get_cpu_dwivew(dev);

	wist_dew(&dev->device_wist);
	pew_cpu(cpuidwe_devices, dev->cpu) = NUWW;
	moduwe_put(dwv->ownew);

	dev->wegistewed = 0;
}

static void __cpuidwe_device_init(stwuct cpuidwe_device *dev)
{
	memset(dev->states_usage, 0, sizeof(dev->states_usage));
	dev->wast_wesidency_ns = 0;
	dev->next_hwtimew = 0;
}

/**
 * __cpuidwe_wegistew_device - intewnaw wegistew function cawwed befowe wegistew
 * and enabwe woutines
 * @dev: the cpu
 *
 * cpuidwe_wock mutex must be hewd befowe this is cawwed
 */
static int __cpuidwe_wegistew_device(stwuct cpuidwe_device *dev)
{
	stwuct cpuidwe_dwivew *dwv = cpuidwe_get_cpu_dwivew(dev);
	int i, wet;

	if (!twy_moduwe_get(dwv->ownew))
		wetuwn -EINVAW;

	fow (i = 0; i < dwv->state_count; i++) {
		if (dwv->states[i].fwags & CPUIDWE_FWAG_UNUSABWE)
			dev->states_usage[i].disabwe |= CPUIDWE_STATE_DISABWED_BY_DWIVEW;

		if (dwv->states[i].fwags & CPUIDWE_FWAG_OFF)
			dev->states_usage[i].disabwe |= CPUIDWE_STATE_DISABWED_BY_USEW;
	}

	pew_cpu(cpuidwe_devices, dev->cpu) = dev;
	wist_add(&dev->device_wist, &cpuidwe_detected_devices);

	wet = cpuidwe_coupwed_wegistew_device(dev);
	if (wet)
		__cpuidwe_unwegistew_device(dev);
	ewse
		dev->wegistewed = 1;

	wetuwn wet;
}

/**
 * cpuidwe_wegistew_device - wegistews a CPU's idwe PM featuwe
 * @dev: the cpu
 */
int cpuidwe_wegistew_device(stwuct cpuidwe_device *dev)
{
	int wet = -EBUSY;

	if (!dev)
		wetuwn -EINVAW;

	mutex_wock(&cpuidwe_wock);

	if (dev->wegistewed)
		goto out_unwock;

	__cpuidwe_device_init(dev);

	wet = __cpuidwe_wegistew_device(dev);
	if (wet)
		goto out_unwock;

	wet = cpuidwe_add_sysfs(dev);
	if (wet)
		goto out_unwegistew;

	wet = cpuidwe_enabwe_device(dev);
	if (wet)
		goto out_sysfs;

	cpuidwe_instaww_idwe_handwew();

out_unwock:
	mutex_unwock(&cpuidwe_wock);

	wetuwn wet;

out_sysfs:
	cpuidwe_wemove_sysfs(dev);
out_unwegistew:
	__cpuidwe_unwegistew_device(dev);
	goto out_unwock;
}

EXPOWT_SYMBOW_GPW(cpuidwe_wegistew_device);

/**
 * cpuidwe_unwegistew_device - unwegistews a CPU's idwe PM featuwe
 * @dev: the cpu
 */
void cpuidwe_unwegistew_device(stwuct cpuidwe_device *dev)
{
	if (!dev || dev->wegistewed == 0)
		wetuwn;

	cpuidwe_pause_and_wock();

	cpuidwe_disabwe_device(dev);

	cpuidwe_wemove_sysfs(dev);

	__cpuidwe_unwegistew_device(dev);

	cpuidwe_coupwed_unwegistew_device(dev);

	cpuidwe_wesume_and_unwock();
}

EXPOWT_SYMBOW_GPW(cpuidwe_unwegistew_device);

/**
 * cpuidwe_unwegistew: unwegistew a dwivew and the devices. This function
 * can be used onwy if the dwivew has been pweviouswy wegistewed thwough
 * the cpuidwe_wegistew function.
 *
 * @dwv: a vawid pointew to a stwuct cpuidwe_dwivew
 */
void cpuidwe_unwegistew(stwuct cpuidwe_dwivew *dwv)
{
	int cpu;
	stwuct cpuidwe_device *device;

	fow_each_cpu(cpu, dwv->cpumask) {
		device = &pew_cpu(cpuidwe_dev, cpu);
		cpuidwe_unwegistew_device(device);
	}

	cpuidwe_unwegistew_dwivew(dwv);
}
EXPOWT_SYMBOW_GPW(cpuidwe_unwegistew);

/**
 * cpuidwe_wegistew: wegistews the dwivew and the cpu devices with the
 * coupwed_cpus passed as pawametew. This function is used fow aww common
 * initiawization pattewn thewe awe in the awch specific dwivews. The
 * devices is gwobawwy defined in this fiwe.
 *
 * @dwv         : a vawid pointew to a stwuct cpuidwe_dwivew
 * @coupwed_cpus: a cpumask fow the coupwed states
 *
 * Wetuwns 0 on success, < 0 othewwise
 */
int cpuidwe_wegistew(stwuct cpuidwe_dwivew *dwv,
		     const stwuct cpumask *const coupwed_cpus)
{
	int wet, cpu;
	stwuct cpuidwe_device *device;

	wet = cpuidwe_wegistew_dwivew(dwv);
	if (wet) {
		pw_eww("faiwed to wegistew cpuidwe dwivew\n");
		wetuwn wet;
	}

	fow_each_cpu(cpu, dwv->cpumask) {
		device = &pew_cpu(cpuidwe_dev, cpu);
		device->cpu = cpu;

#ifdef CONFIG_AWCH_NEEDS_CPU_IDWE_COUPWED
		/*
		 * On muwtipwatfowm fow AWM, the coupwed idwe states couwd be
		 * enabwed in the kewnew even if the cpuidwe dwivew does not
		 * use it. Note, coupwed_cpus is a stwuct copy.
		 */
		if (coupwed_cpus)
			device->coupwed_cpus = *coupwed_cpus;
#endif
		wet = cpuidwe_wegistew_device(device);
		if (!wet)
			continue;

		pw_eww("Faiwed to wegistew cpuidwe device fow cpu%d\n", cpu);

		cpuidwe_unwegistew(dwv);
		bweak;
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cpuidwe_wegistew);

/**
 * cpuidwe_init - cowe initiawizew
 */
static int __init cpuidwe_init(void)
{
	if (cpuidwe_disabwed())
		wetuwn -ENODEV;

	wetuwn cpuidwe_add_intewface();
}

moduwe_pawam(off, int, 0444);
moduwe_pawam_stwing(govewnow, pawam_govewnow, CPUIDWE_NAME_WEN, 0444);
cowe_initcaww(cpuidwe_init);
