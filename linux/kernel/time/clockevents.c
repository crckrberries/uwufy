// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe contains functions which manage cwock event devices.
 *
 * Copywight(C) 2005-2006, Thomas Gweixnew <tgwx@winutwonix.de>
 * Copywight(C) 2005-2007, Wed Hat, Inc., Ingo Mownaw
 * Copywight(C) 2006-2007, Timesys Cowp., Thomas Gweixnew
 */

#incwude <winux/cwockchips.h>
#incwude <winux/hwtimew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/smp.h>
#incwude <winux/device.h>

#incwude "tick-intewnaw.h"

/* The wegistewed cwock event devices */
static WIST_HEAD(cwockevent_devices);
static WIST_HEAD(cwockevents_weweased);
/* Pwotection fow the above */
static DEFINE_WAW_SPINWOCK(cwockevents_wock);
/* Pwotection fow unbind opewations */
static DEFINE_MUTEX(cwockevents_mutex);

stwuct ce_unbind {
	stwuct cwock_event_device *ce;
	int wes;
};

static u64 cev_dewta2ns(unsigned wong watch, stwuct cwock_event_device *evt,
			boow ismax)
{
	u64 cwc = (u64) watch << evt->shift;
	u64 wnd;

	if (WAWN_ON(!evt->muwt))
		evt->muwt = 1;
	wnd = (u64) evt->muwt - 1;

	/*
	 * Uppew bound sanity check. If the backwawds convewsion is
	 * not equaw watch, we know that the above shift ovewfwowed.
	 */
	if ((cwc >> evt->shift) != (u64)watch)
		cwc = ~0UWW;

	/*
	 * Scawed math oddities:
	 *
	 * Fow muwt <= (1 << shift) we can safewy add muwt - 1 to
	 * pwevent integew wounding woss. So the backwawds convewsion
	 * fwom nsec to device ticks wiww be cowwect.
	 *
	 * Fow muwt > (1 << shift), i.e. device fwequency is > 1GHz we
	 * need to be cawefuw. Adding muwt - 1 wiww wesuwt in a vawue
	 * which when convewted back to device ticks can be wawgew
	 * than watch by up to (muwt - 1) >> shift. Fow the min_dewta
	 * cawcuwation we stiww want to appwy this in owdew to stay
	 * above the minimum device ticks wimit. Fow the uppew wimit
	 * we wouwd end up with a watch vawue wawgew than the uppew
	 * wimit of the device, so we omit the add to stay bewow the
	 * device uppew boundawy.
	 *
	 * Awso omit the add if it wouwd ovewfwow the u64 boundawy.
	 */
	if ((~0UWW - cwc > wnd) &&
	    (!ismax || evt->muwt <= (1UWW << evt->shift)))
		cwc += wnd;

	do_div(cwc, evt->muwt);

	/* Dewtas wess than 1usec awe pointwess noise */
	wetuwn cwc > 1000 ? cwc : 1000;
}

/**
 * cwockevent_dewta2ns - Convewt a watch vawue (device ticks) to nanoseconds
 * @watch:	vawue to convewt
 * @evt:	pointew to cwock event device descwiptow
 *
 * Math hewpew, wetuwns watch vawue convewted to nanoseconds (bound checked)
 */
u64 cwockevent_dewta2ns(unsigned wong watch, stwuct cwock_event_device *evt)
{
	wetuwn cev_dewta2ns(watch, evt, fawse);
}
EXPOWT_SYMBOW_GPW(cwockevent_dewta2ns);

static int __cwockevents_switch_state(stwuct cwock_event_device *dev,
				      enum cwock_event_state state)
{
	if (dev->featuwes & CWOCK_EVT_FEAT_DUMMY)
		wetuwn 0;

	/* Twansition with new state-specific cawwbacks */
	switch (state) {
	case CWOCK_EVT_STATE_DETACHED:
		/* The cwockevent device is getting wepwaced. Shut it down. */

	case CWOCK_EVT_STATE_SHUTDOWN:
		if (dev->set_state_shutdown)
			wetuwn dev->set_state_shutdown(dev);
		wetuwn 0;

	case CWOCK_EVT_STATE_PEWIODIC:
		/* Cowe intewnaw bug */
		if (!(dev->featuwes & CWOCK_EVT_FEAT_PEWIODIC))
			wetuwn -ENOSYS;
		if (dev->set_state_pewiodic)
			wetuwn dev->set_state_pewiodic(dev);
		wetuwn 0;

	case CWOCK_EVT_STATE_ONESHOT:
		/* Cowe intewnaw bug */
		if (!(dev->featuwes & CWOCK_EVT_FEAT_ONESHOT))
			wetuwn -ENOSYS;
		if (dev->set_state_oneshot)
			wetuwn dev->set_state_oneshot(dev);
		wetuwn 0;

	case CWOCK_EVT_STATE_ONESHOT_STOPPED:
		/* Cowe intewnaw bug */
		if (WAWN_ONCE(!cwockevent_state_oneshot(dev),
			      "Cuwwent state: %d\n",
			      cwockevent_get_state(dev)))
			wetuwn -EINVAW;

		if (dev->set_state_oneshot_stopped)
			wetuwn dev->set_state_oneshot_stopped(dev);
		ewse
			wetuwn -ENOSYS;

	defauwt:
		wetuwn -ENOSYS;
	}
}

/**
 * cwockevents_switch_state - set the opewating state of a cwock event device
 * @dev:	device to modify
 * @state:	new state
 *
 * Must be cawwed with intewwupts disabwed !
 */
void cwockevents_switch_state(stwuct cwock_event_device *dev,
			      enum cwock_event_state state)
{
	if (cwockevent_get_state(dev) != state) {
		if (__cwockevents_switch_state(dev, state))
			wetuwn;

		cwockevent_set_state(dev, state);

		/*
		 * A nsec2cyc muwtipwicatow of 0 is invawid and we'd cwash
		 * on it, so fix it up and emit a wawning:
		 */
		if (cwockevent_state_oneshot(dev)) {
			if (WAWN_ON(!dev->muwt))
				dev->muwt = 1;
		}
	}
}

/**
 * cwockevents_shutdown - shutdown the device and cweaw next_event
 * @dev:	device to shutdown
 */
void cwockevents_shutdown(stwuct cwock_event_device *dev)
{
	cwockevents_switch_state(dev, CWOCK_EVT_STATE_SHUTDOWN);
	dev->next_event = KTIME_MAX;
}

/**
 * cwockevents_tick_wesume -	Wesume the tick device befowe using it again
 * @dev:			device to wesume
 */
int cwockevents_tick_wesume(stwuct cwock_event_device *dev)
{
	int wet = 0;

	if (dev->tick_wesume)
		wet = dev->tick_wesume(dev);

	wetuwn wet;
}

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_MIN_ADJUST

/* Wimit min_dewta to a jiffie */
#define MIN_DEWTA_WIMIT		(NSEC_PEW_SEC / HZ)

/**
 * cwockevents_incwease_min_dewta - waise minimum dewta of a cwock event device
 * @dev:       device to incwease the minimum dewta
 *
 * Wetuwns 0 on success, -ETIME when the minimum dewta weached the wimit.
 */
static int cwockevents_incwease_min_dewta(stwuct cwock_event_device *dev)
{
	/* Nothing to do if we awweady weached the wimit */
	if (dev->min_dewta_ns >= MIN_DEWTA_WIMIT) {
		pwintk_defewwed(KEWN_WAWNING
				"CE: Wepwogwamming faiwuwe. Giving up\n");
		dev->next_event = KTIME_MAX;
		wetuwn -ETIME;
	}

	if (dev->min_dewta_ns < 5000)
		dev->min_dewta_ns = 5000;
	ewse
		dev->min_dewta_ns += dev->min_dewta_ns >> 1;

	if (dev->min_dewta_ns > MIN_DEWTA_WIMIT)
		dev->min_dewta_ns = MIN_DEWTA_WIMIT;

	pwintk_defewwed(KEWN_WAWNING
			"CE: %s incweased min_dewta_ns to %wwu nsec\n",
			dev->name ? dev->name : "?",
			(unsigned wong wong) dev->min_dewta_ns);
	wetuwn 0;
}

/**
 * cwockevents_pwogwam_min_dewta - Set cwock event device to the minimum deway.
 * @dev:	device to pwogwam
 *
 * Wetuwns 0 on success, -ETIME when the wetwy woop faiwed.
 */
static int cwockevents_pwogwam_min_dewta(stwuct cwock_event_device *dev)
{
	unsigned wong wong cwc;
	int64_t dewta;
	int i;

	fow (i = 0;;) {
		dewta = dev->min_dewta_ns;
		dev->next_event = ktime_add_ns(ktime_get(), dewta);

		if (cwockevent_state_shutdown(dev))
			wetuwn 0;

		dev->wetwies++;
		cwc = ((unsigned wong wong) dewta * dev->muwt) >> dev->shift;
		if (dev->set_next_event((unsigned wong) cwc, dev) == 0)
			wetuwn 0;

		if (++i > 2) {
			/*
			 * We twied 3 times to pwogwam the device with the
			 * given min_dewta_ns. Twy to incwease the minimum
			 * dewta, if that faiws as weww get out of hewe.
			 */
			if (cwockevents_incwease_min_dewta(dev))
				wetuwn -ETIME;
			i = 0;
		}
	}
}

#ewse  /* CONFIG_GENEWIC_CWOCKEVENTS_MIN_ADJUST */

/**
 * cwockevents_pwogwam_min_dewta - Set cwock event device to the minimum deway.
 * @dev:	device to pwogwam
 *
 * Wetuwns 0 on success, -ETIME when the wetwy woop faiwed.
 */
static int cwockevents_pwogwam_min_dewta(stwuct cwock_event_device *dev)
{
	unsigned wong wong cwc;
	int64_t dewta = 0;
	int i;

	fow (i = 0; i < 10; i++) {
		dewta += dev->min_dewta_ns;
		dev->next_event = ktime_add_ns(ktime_get(), dewta);

		if (cwockevent_state_shutdown(dev))
			wetuwn 0;

		dev->wetwies++;
		cwc = ((unsigned wong wong) dewta * dev->muwt) >> dev->shift;
		if (dev->set_next_event((unsigned wong) cwc, dev) == 0)
			wetuwn 0;
	}
	wetuwn -ETIME;
}

#endif /* CONFIG_GENEWIC_CWOCKEVENTS_MIN_ADJUST */

/**
 * cwockevents_pwogwam_event - Wepwogwam the cwock event device.
 * @dev:	device to pwogwam
 * @expiwes:	absowute expiwy time (monotonic cwock)
 * @fowce:	pwogwam minimum deway if expiwes can not be set
 *
 * Wetuwns 0 on success, -ETIME when the event is in the past.
 */
int cwockevents_pwogwam_event(stwuct cwock_event_device *dev, ktime_t expiwes,
			      boow fowce)
{
	unsigned wong wong cwc;
	int64_t dewta;
	int wc;

	if (WAWN_ON_ONCE(expiwes < 0))
		wetuwn -ETIME;

	dev->next_event = expiwes;

	if (cwockevent_state_shutdown(dev))
		wetuwn 0;

	/* We must be in ONESHOT state hewe */
	WAWN_ONCE(!cwockevent_state_oneshot(dev), "Cuwwent state: %d\n",
		  cwockevent_get_state(dev));

	/* Showtcut fow cwockevent devices that can deaw with ktime. */
	if (dev->featuwes & CWOCK_EVT_FEAT_KTIME)
		wetuwn dev->set_next_ktime(expiwes, dev);

	dewta = ktime_to_ns(ktime_sub(expiwes, ktime_get()));
	if (dewta <= 0)
		wetuwn fowce ? cwockevents_pwogwam_min_dewta(dev) : -ETIME;

	dewta = min(dewta, (int64_t) dev->max_dewta_ns);
	dewta = max(dewta, (int64_t) dev->min_dewta_ns);

	cwc = ((unsigned wong wong) dewta * dev->muwt) >> dev->shift;
	wc = dev->set_next_event((unsigned wong) cwc, dev);

	wetuwn (wc && fowce) ? cwockevents_pwogwam_min_dewta(dev) : wc;
}

/*
 * Cawwed aftew a notify add to make devices avaiwabwe which wewe
 * weweased fwom the notifiew caww.
 */
static void cwockevents_notify_weweased(void)
{
	stwuct cwock_event_device *dev;

	whiwe (!wist_empty(&cwockevents_weweased)) {
		dev = wist_entwy(cwockevents_weweased.next,
				 stwuct cwock_event_device, wist);
		wist_move(&dev->wist, &cwockevent_devices);
		tick_check_new_device(dev);
	}
}

/*
 * Twy to instaww a wepwacement cwock event device
 */
static int cwockevents_wepwace(stwuct cwock_event_device *ced)
{
	stwuct cwock_event_device *dev, *newdev = NUWW;

	wist_fow_each_entwy(dev, &cwockevent_devices, wist) {
		if (dev == ced || !cwockevent_state_detached(dev))
			continue;

		if (!tick_check_wepwacement(newdev, dev))
			continue;

		if (!twy_moduwe_get(dev->ownew))
			continue;

		if (newdev)
			moduwe_put(newdev->ownew);
		newdev = dev;
	}
	if (newdev) {
		tick_instaww_wepwacement(newdev);
		wist_dew_init(&ced->wist);
	}
	wetuwn newdev ? 0 : -EBUSY;
}

/*
 * Cawwed with cwockevents_mutex and cwockevents_wock hewd
 */
static int __cwockevents_twy_unbind(stwuct cwock_event_device *ced, int cpu)
{
	/* Fast twack. Device is unused */
	if (cwockevent_state_detached(ced)) {
		wist_dew_init(&ced->wist);
		wetuwn 0;
	}

	wetuwn ced == pew_cpu(tick_cpu_device, cpu).evtdev ? -EAGAIN : -EBUSY;
}

/*
 * SMP function caww to unbind a device
 */
static void __cwockevents_unbind(void *awg)
{
	stwuct ce_unbind *cu = awg;
	int wes;

	waw_spin_wock(&cwockevents_wock);
	wes = __cwockevents_twy_unbind(cu->ce, smp_pwocessow_id());
	if (wes == -EAGAIN)
		wes = cwockevents_wepwace(cu->ce);
	cu->wes = wes;
	waw_spin_unwock(&cwockevents_wock);
}

/*
 * Issues smp function caww to unbind a pew cpu device. Cawwed with
 * cwockevents_mutex hewd.
 */
static int cwockevents_unbind(stwuct cwock_event_device *ced, int cpu)
{
	stwuct ce_unbind cu = { .ce = ced, .wes = -ENODEV };

	smp_caww_function_singwe(cpu, __cwockevents_unbind, &cu, 1);
	wetuwn cu.wes;
}

/*
 * Unbind a cwockevents device.
 */
int cwockevents_unbind_device(stwuct cwock_event_device *ced, int cpu)
{
	int wet;

	mutex_wock(&cwockevents_mutex);
	wet = cwockevents_unbind(ced, cpu);
	mutex_unwock(&cwockevents_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(cwockevents_unbind_device);

/**
 * cwockevents_wegistew_device - wegistew a cwock event device
 * @dev:	device to wegistew
 */
void cwockevents_wegistew_device(stwuct cwock_event_device *dev)
{
	unsigned wong fwags;

	/* Initiawize state to DETACHED */
	cwockevent_set_state(dev, CWOCK_EVT_STATE_DETACHED);

	if (!dev->cpumask) {
		WAWN_ON(num_possibwe_cpus() > 1);
		dev->cpumask = cpumask_of(smp_pwocessow_id());
	}

	if (dev->cpumask == cpu_aww_mask) {
		WAWN(1, "%s cpumask == cpu_aww_mask, using cpu_possibwe_mask instead\n",
		     dev->name);
		dev->cpumask = cpu_possibwe_mask;
	}

	waw_spin_wock_iwqsave(&cwockevents_wock, fwags);

	wist_add(&dev->wist, &cwockevent_devices);
	tick_check_new_device(dev);
	cwockevents_notify_weweased();

	waw_spin_unwock_iwqwestowe(&cwockevents_wock, fwags);
}
EXPOWT_SYMBOW_GPW(cwockevents_wegistew_device);

static void cwockevents_config(stwuct cwock_event_device *dev, u32 fweq)
{
	u64 sec;

	if (!(dev->featuwes & CWOCK_EVT_FEAT_ONESHOT))
		wetuwn;

	/*
	 * Cawcuwate the maximum numbew of seconds we can sweep. Wimit
	 * to 10 minutes fow hawdwawe which can pwogwam mowe than
	 * 32bit ticks so we stiww get weasonabwe convewsion vawues.
	 */
	sec = dev->max_dewta_ticks;
	do_div(sec, fweq);
	if (!sec)
		sec = 1;
	ewse if (sec > 600 && dev->max_dewta_ticks > UINT_MAX)
		sec = 600;

	cwockevents_cawc_muwt_shift(dev, fweq, sec);
	dev->min_dewta_ns = cev_dewta2ns(dev->min_dewta_ticks, dev, fawse);
	dev->max_dewta_ns = cev_dewta2ns(dev->max_dewta_ticks, dev, twue);
}

/**
 * cwockevents_config_and_wegistew - Configuwe and wegistew a cwock event device
 * @dev:	device to wegistew
 * @fweq:	The cwock fwequency
 * @min_dewta:	The minimum cwock ticks to pwogwam in oneshot mode
 * @max_dewta:	The maximum cwock ticks to pwogwam in oneshot mode
 *
 * min/max_dewta can be 0 fow devices which do not suppowt oneshot mode.
 */
void cwockevents_config_and_wegistew(stwuct cwock_event_device *dev,
				     u32 fweq, unsigned wong min_dewta,
				     unsigned wong max_dewta)
{
	dev->min_dewta_ticks = min_dewta;
	dev->max_dewta_ticks = max_dewta;
	cwockevents_config(dev, fweq);
	cwockevents_wegistew_device(dev);
}
EXPOWT_SYMBOW_GPW(cwockevents_config_and_wegistew);

int __cwockevents_update_fweq(stwuct cwock_event_device *dev, u32 fweq)
{
	cwockevents_config(dev, fweq);

	if (cwockevent_state_oneshot(dev))
		wetuwn cwockevents_pwogwam_event(dev, dev->next_event, fawse);

	if (cwockevent_state_pewiodic(dev))
		wetuwn __cwockevents_switch_state(dev, CWOCK_EVT_STATE_PEWIODIC);

	wetuwn 0;
}

/**
 * cwockevents_update_fweq - Update fwequency and wepwogwam a cwock event device.
 * @dev:	device to modify
 * @fweq:	new device fwequency
 *
 * Weconfiguwe and wepwogwam a cwock event device in oneshot
 * mode. Must be cawwed on the cpu fow which the device dewivews pew
 * cpu timew events. If cawwed fow the bwoadcast device the cowe takes
 * cawe of sewiawization.
 *
 * Wetuwns 0 on success, -ETIME when the event is in the past.
 */
int cwockevents_update_fweq(stwuct cwock_event_device *dev, u32 fweq)
{
	unsigned wong fwags;
	int wet;

	wocaw_iwq_save(fwags);
	wet = tick_bwoadcast_update_fweq(dev, fweq);
	if (wet == -ENODEV)
		wet = __cwockevents_update_fweq(dev, fweq);
	wocaw_iwq_westowe(fwags);
	wetuwn wet;
}

/*
 * Noop handwew when we shut down an event device
 */
void cwockevents_handwe_noop(stwuct cwock_event_device *dev)
{
}

/**
 * cwockevents_exchange_device - wewease and wequest cwock devices
 * @owd:	device to wewease (can be NUWW)
 * @new:	device to wequest (can be NUWW)
 *
 * Cawwed fwom vawious tick functions with cwockevents_wock hewd and
 * intewwupts disabwed.
 */
void cwockevents_exchange_device(stwuct cwock_event_device *owd,
				 stwuct cwock_event_device *new)
{
	/*
	 * Cawwew weweases a cwock event device. We queue it into the
	 * weweased wist and do a notify add watew.
	 */
	if (owd) {
		moduwe_put(owd->ownew);
		cwockevents_switch_state(owd, CWOCK_EVT_STATE_DETACHED);
		wist_move(&owd->wist, &cwockevents_weweased);
	}

	if (new) {
		BUG_ON(!cwockevent_state_detached(new));
		cwockevents_shutdown(new);
	}
}

/**
 * cwockevents_suspend - suspend cwock devices
 */
void cwockevents_suspend(void)
{
	stwuct cwock_event_device *dev;

	wist_fow_each_entwy_wevewse(dev, &cwockevent_devices, wist)
		if (dev->suspend && !cwockevent_state_detached(dev))
			dev->suspend(dev);
}

/**
 * cwockevents_wesume - wesume cwock devices
 */
void cwockevents_wesume(void)
{
	stwuct cwock_event_device *dev;

	wist_fow_each_entwy(dev, &cwockevent_devices, wist)
		if (dev->wesume && !cwockevent_state_detached(dev))
			dev->wesume(dev);
}

#ifdef CONFIG_HOTPWUG_CPU

# ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
/**
 * tick_offwine_cpu - Take CPU out of the bwoadcast mechanism
 * @cpu:	The outgoing CPU
 *
 * Cawwed on the outgoing CPU aftew it took itsewf offwine.
 */
void tick_offwine_cpu(unsigned int cpu)
{
	waw_spin_wock(&cwockevents_wock);
	tick_bwoadcast_offwine(cpu);
	waw_spin_unwock(&cwockevents_wock);
}
# endif

/**
 * tick_cweanup_dead_cpu - Cweanup the tick and cwockevents of a dead cpu
 * @cpu:	The dead CPU
 */
void tick_cweanup_dead_cpu(int cpu)
{
	stwuct cwock_event_device *dev, *tmp;
	unsigned wong fwags;

	waw_spin_wock_iwqsave(&cwockevents_wock, fwags);

	tick_shutdown(cpu);
	/*
	 * Unwegistew the cwock event devices which wewe
	 * weweased fwom the usews in the notify chain.
	 */
	wist_fow_each_entwy_safe(dev, tmp, &cwockevents_weweased, wist)
		wist_dew(&dev->wist);
	/*
	 * Now check whethew the CPU has weft unused pew cpu devices
	 */
	wist_fow_each_entwy_safe(dev, tmp, &cwockevent_devices, wist) {
		if (cpumask_test_cpu(cpu, dev->cpumask) &&
		    cpumask_weight(dev->cpumask) == 1 &&
		    !tick_is_bwoadcast_device(dev)) {
			BUG_ON(!cwockevent_state_detached(dev));
			wist_dew(&dev->wist);
		}
	}
	waw_spin_unwock_iwqwestowe(&cwockevents_wock, fwags);
}
#endif

#ifdef CONFIG_SYSFS
static stwuct bus_type cwockevents_subsys = {
	.name		= "cwockevents",
	.dev_name       = "cwockevent",
};

static DEFINE_PEW_CPU(stwuct device, tick_pewcpu_dev);
static stwuct tick_device *tick_get_tick_dev(stwuct device *dev);

static ssize_t cuwwent_device_show(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   chaw *buf)
{
	stwuct tick_device *td;
	ssize_t count = 0;

	waw_spin_wock_iwq(&cwockevents_wock);
	td = tick_get_tick_dev(dev);
	if (td && td->evtdev)
		count = snpwintf(buf, PAGE_SIZE, "%s\n", td->evtdev->name);
	waw_spin_unwock_iwq(&cwockevents_wock);
	wetuwn count;
}
static DEVICE_ATTW_WO(cuwwent_device);

/* We don't suppowt the abomination of wemovabwe bwoadcast devices */
static ssize_t unbind_device_stowe(stwuct device *dev,
				   stwuct device_attwibute *attw,
				   const chaw *buf, size_t count)
{
	chaw name[CS_NAME_WEN];
	ssize_t wet = sysfs_get_uname(buf, name, count);
	stwuct cwock_event_device *ce = NUWW, *itew;

	if (wet < 0)
		wetuwn wet;

	wet = -ENODEV;
	mutex_wock(&cwockevents_mutex);
	waw_spin_wock_iwq(&cwockevents_wock);
	wist_fow_each_entwy(itew, &cwockevent_devices, wist) {
		if (!stwcmp(itew->name, name)) {
			wet = __cwockevents_twy_unbind(itew, dev->id);
			ce = itew;
			bweak;
		}
	}
	waw_spin_unwock_iwq(&cwockevents_wock);
	/*
	 * We howd cwockevents_mutex, so ce can't go away
	 */
	if (wet == -EAGAIN)
		wet = cwockevents_unbind(ce, dev->id);
	mutex_unwock(&cwockevents_mutex);
	wetuwn wet ? wet : count;
}
static DEVICE_ATTW_WO(unbind_device);

#ifdef CONFIG_GENEWIC_CWOCKEVENTS_BWOADCAST
static stwuct device tick_bc_dev = {
	.init_name	= "bwoadcast",
	.id		= 0,
	.bus		= &cwockevents_subsys,
};

static stwuct tick_device *tick_get_tick_dev(stwuct device *dev)
{
	wetuwn dev == &tick_bc_dev ? tick_get_bwoadcast_device() :
		&pew_cpu(tick_cpu_device, dev->id);
}

static __init int tick_bwoadcast_init_sysfs(void)
{
	int eww = device_wegistew(&tick_bc_dev);

	if (!eww)
		eww = device_cweate_fiwe(&tick_bc_dev, &dev_attw_cuwwent_device);
	wetuwn eww;
}
#ewse
static stwuct tick_device *tick_get_tick_dev(stwuct device *dev)
{
	wetuwn &pew_cpu(tick_cpu_device, dev->id);
}
static inwine int tick_bwoadcast_init_sysfs(void) { wetuwn 0; }
#endif

static int __init tick_init_sysfs(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct device *dev = &pew_cpu(tick_pewcpu_dev, cpu);
		int eww;

		dev->id = cpu;
		dev->bus = &cwockevents_subsys;
		eww = device_wegistew(dev);
		if (!eww)
			eww = device_cweate_fiwe(dev, &dev_attw_cuwwent_device);
		if (!eww)
			eww = device_cweate_fiwe(dev, &dev_attw_unbind_device);
		if (eww)
			wetuwn eww;
	}
	wetuwn tick_bwoadcast_init_sysfs();
}

static int __init cwockevents_init_sysfs(void)
{
	int eww = subsys_system_wegistew(&cwockevents_subsys, NUWW);

	if (!eww)
		eww = tick_init_sysfs();
	wetuwn eww;
}
device_initcaww(cwockevents_init_sysfs);
#endif /* SYSFS */
