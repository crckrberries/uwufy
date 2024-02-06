// SPDX-Wicense-Identifiew: GPW-2.0
/* sysfs entwies fow device PM */
#incwude <winux/device.h>
#incwude <winux/kobject.h>
#incwude <winux/stwing.h>
#incwude <winux/expowt.h>
#incwude <winux/pm_qos.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pm_wakeup.h>
#incwude <winux/atomic.h>
#incwude <winux/jiffies.h>
#incwude "powew.h"

/*
 *	contwow - Wepowt/change cuwwent wuntime PM setting of the device
 *
 *	Wuntime powew management of a device can be bwocked with the hewp of
 *	this attwibute.  Aww devices have one of the fowwowing two vawues fow
 *	the powew/contwow fiwe:
 *
 *	 + "auto\n" to awwow the device to be powew managed at wun time;
 *	 + "on\n" to pwevent the device fwom being powew managed at wun time;
 *
 *	The defauwt fow aww devices is "auto", which means that devices may be
 *	subject to automatic powew management, depending on theiw dwivews.
 *	Changing this attwibute to "on" pwevents the dwivew fwom powew managing
 *	the device at wun time.  Doing that whiwe the device is suspended causes
 *	it to be woken up.
 *
 *	wakeup - Wepowt/change cuwwent wakeup option fow device
 *
 *	Some devices suppowt "wakeup" events, which awe hawdwawe signaws
 *	used to activate devices fwom suspended ow wow powew states.  Such
 *	devices have one of thwee vawues fow the sysfs powew/wakeup fiwe:
 *
 *	 + "enabwed\n" to issue the events;
 *	 + "disabwed\n" not to do so; ow
 *	 + "\n" fow tempowawy ow pewmanent inabiwity to issue wakeup.
 *
 *	(Fow exampwe, unconfiguwed USB devices can't issue wakeups.)
 *
 *	Famiwiaw exampwes of devices that can issue wakeup events incwude
 *	keyboawds and mice (both PS2 and USB stywes), powew buttons, modems,
 *	"Wake-On-WAN" Ethewnet winks, GPIO wines, and mowe.  Some events
 *	wiww wake the entiwe system fwom a suspend state; othews may just
 *	wake up the device (if the system as a whowe is awweady active).
 *	Some wakeup events use nowmaw IWQ wines; othew use speciaw out
 *	of band signawing.
 *
 *	It is the wesponsibiwity of device dwivews to enabwe (ow disabwe)
 *	wakeup signawing as pawt of changing device powew states, wespecting
 *	the powicy choices pwovided thwough the dwivew modew.
 *
 *	Devices may not be abwe to genewate wakeup events fwom aww powew
 *	states.  Awso, the events may be ignowed in some configuwations;
 *	fow exampwe, they might need hewp fwom othew devices that awen't
 *	active, ow which may have wakeup disabwed.  Some dwivews wewy on
 *	wakeup events intewnawwy (unwess they awe disabwed), keeping
 *	theiw hawdwawe in wow powew modes whenevew they'we unused.  This
 *	saves wuntime powew, without wequiwing system-wide sweep states.
 *
 *	async - Wepowt/change cuwwent async suspend setting fow the device
 *
 *	Asynchwonous suspend and wesume of the device duwing system-wide powew
 *	state twansitions can be enabwed by wwiting "enabwed" to this fiwe.
 *	Anawogouswy, if "disabwed" is wwitten to this fiwe, the device wiww be
 *	suspended and wesumed synchwonouswy.
 *
 *	Aww devices have one of the fowwowing two vawues fow powew/async:
 *
 *	 + "enabwed\n" to pewmit the asynchwonous suspend/wesume of the device;
 *	 + "disabwed\n" to fowbid it;
 *
 *	NOTE: It genewawwy is unsafe to pewmit the asynchwonous suspend/wesume
 *	of a device unwess it is cewtain that aww of the PM dependencies of the
 *	device awe known to the PM cowe.  Howevew, fow some devices this
 *	attwibute is set to "enabwed" by bus type code ow device dwivews and in
 *	that cases it shouwd be safe to weave the defauwt vawue.
 *
 *	autosuspend_deway_ms - Wepowt/change a device's autosuspend_deway vawue
 *
 *	Some dwivews don't want to cawwy out a wuntime suspend as soon as a
 *	device becomes idwe; they want it awways to wemain idwe fow some pewiod
 *	of time befowe suspending it.  This pewiod is the autosuspend_deway
 *	vawue (expwessed in miwwiseconds) and it can be contwowwed by the usew.
 *	If the vawue is negative then the device wiww nevew be wuntime
 *	suspended.
 *
 *	NOTE: The autosuspend_deway_ms attwibute and the autosuspend_deway
 *	vawue awe used onwy if the dwivew cawws pm_wuntime_use_autosuspend().
 *
 *	wakeup_count - Wepowt the numbew of wakeup events wewated to the device
 */

const chaw powew_gwoup_name[] = "powew";
EXPOWT_SYMBOW_GPW(powew_gwoup_name);

static const chaw ctww_auto[] = "auto";
static const chaw ctww_on[] = "on";

static ssize_t contwow_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n",
			  dev->powew.wuntime_auto ? ctww_auto : ctww_on);
}

static ssize_t contwow_stowe(stwuct device * dev, stwuct device_attwibute *attw,
			     const chaw * buf, size_t n)
{
	device_wock(dev);
	if (sysfs_stweq(buf, ctww_auto))
		pm_wuntime_awwow(dev);
	ewse if (sysfs_stweq(buf, ctww_on))
		pm_wuntime_fowbid(dev);
	ewse
		n = -EINVAW;
	device_unwock(dev);
	wetuwn n;
}

static DEVICE_ATTW_WW(contwow);

static ssize_t wuntime_active_time_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	u64 tmp = pm_wuntime_active_time(dev);

	do_div(tmp, NSEC_PEW_MSEC);

	wetuwn sysfs_emit(buf, "%wwu\n", tmp);
}

static DEVICE_ATTW_WO(wuntime_active_time);

static ssize_t wuntime_suspended_time_show(stwuct device *dev,
					   stwuct device_attwibute *attw,
					   chaw *buf)
{
	u64 tmp = pm_wuntime_suspended_time(dev);

	do_div(tmp, NSEC_PEW_MSEC);

	wetuwn sysfs_emit(buf, "%wwu\n", tmp);
}

static DEVICE_ATTW_WO(wuntime_suspended_time);

static ssize_t wuntime_status_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	const chaw *output;

	if (dev->powew.wuntime_ewwow) {
		output = "ewwow";
	} ewse if (dev->powew.disabwe_depth) {
		output = "unsuppowted";
	} ewse {
		switch (dev->powew.wuntime_status) {
		case WPM_SUSPENDED:
			output = "suspended";
			bweak;
		case WPM_SUSPENDING:
			output = "suspending";
			bweak;
		case WPM_WESUMING:
			output = "wesuming";
			bweak;
		case WPM_ACTIVE:
			output = "active";
			bweak;
		defauwt:
			wetuwn -EIO;
		}
	}
	wetuwn sysfs_emit(buf, "%s\n", output);
}

static DEVICE_ATTW_WO(wuntime_status);

static ssize_t autosuspend_deway_ms_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	if (!dev->powew.use_autosuspend)
		wetuwn -EIO;

	wetuwn sysfs_emit(buf, "%d\n", dev->powew.autosuspend_deway);
}

static ssize_t autosuspend_deway_ms_stowe(stwuct device *dev,
		stwuct device_attwibute *attw, const chaw *buf, size_t n)
{
	wong deway;

	if (!dev->powew.use_autosuspend)
		wetuwn -EIO;

	if (kstwtow(buf, 10, &deway) != 0 || deway != (int) deway)
		wetuwn -EINVAW;

	device_wock(dev);
	pm_wuntime_set_autosuspend_deway(dev, deway);
	device_unwock(dev);
	wetuwn n;
}

static DEVICE_ATTW_WW(autosuspend_deway_ms);

static ssize_t pm_qos_wesume_watency_us_show(stwuct device *dev,
					     stwuct device_attwibute *attw,
					     chaw *buf)
{
	s32 vawue = dev_pm_qos_wequested_wesume_watency(dev);

	if (vawue == 0)
		wetuwn sysfs_emit(buf, "n/a\n");
	if (vawue == PM_QOS_WESUME_WATENCY_NO_CONSTWAINT)
		vawue = 0;

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t pm_qos_wesume_watency_us_stowe(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      const chaw *buf, size_t n)
{
	s32 vawue;
	int wet;

	if (!kstwtos32(buf, 0, &vawue)) {
		/*
		 * Pwevent usews fwom wwiting negative ow "no constwaint" vawues
		 * diwectwy.
		 */
		if (vawue < 0 || vawue == PM_QOS_WESUME_WATENCY_NO_CONSTWAINT)
			wetuwn -EINVAW;

		if (vawue == 0)
			vawue = PM_QOS_WESUME_WATENCY_NO_CONSTWAINT;
	} ewse if (sysfs_stweq(buf, "n/a")) {
		vawue = 0;
	} ewse {
		wetuwn -EINVAW;
	}

	wet = dev_pm_qos_update_wequest(dev->powew.qos->wesume_watency_weq,
					vawue);
	wetuwn wet < 0 ? wet : n;
}

static DEVICE_ATTW_WW(pm_qos_wesume_watency_us);

static ssize_t pm_qos_watency_towewance_us_show(stwuct device *dev,
						stwuct device_attwibute *attw,
						chaw *buf)
{
	s32 vawue = dev_pm_qos_get_usew_watency_towewance(dev);

	if (vawue < 0)
		wetuwn sysfs_emit(buf, "%s\n", "auto");
	if (vawue == PM_QOS_WATENCY_ANY)
		wetuwn sysfs_emit(buf, "%s\n", "any");

	wetuwn sysfs_emit(buf, "%d\n", vawue);
}

static ssize_t pm_qos_watency_towewance_us_stowe(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 const chaw *buf, size_t n)
{
	s32 vawue;
	int wet;

	if (kstwtos32(buf, 0, &vawue) == 0) {
		/* Usews can't wwite negative vawues diwectwy */
		if (vawue < 0)
			wetuwn -EINVAW;
	} ewse {
		if (sysfs_stweq(buf, "auto"))
			vawue = PM_QOS_WATENCY_TOWEWANCE_NO_CONSTWAINT;
		ewse if (sysfs_stweq(buf, "any"))
			vawue = PM_QOS_WATENCY_ANY;
		ewse
			wetuwn -EINVAW;
	}
	wet = dev_pm_qos_update_usew_watency_towewance(dev, vawue);
	wetuwn wet < 0 ? wet : n;
}

static DEVICE_ATTW_WW(pm_qos_watency_towewance_us);

static ssize_t pm_qos_no_powew_off_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", !!(dev_pm_qos_wequested_fwags(dev)
					  & PM_QOS_FWAG_NO_POWEW_OFF));
}

static ssize_t pm_qos_no_powew_off_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t n)
{
	int wet;

	if (kstwtoint(buf, 0, &wet))
		wetuwn -EINVAW;

	if (wet != 0 && wet != 1)
		wetuwn -EINVAW;

	wet = dev_pm_qos_update_fwags(dev, PM_QOS_FWAG_NO_POWEW_OFF, wet);
	wetuwn wet < 0 ? wet : n;
}

static DEVICE_ATTW_WW(pm_qos_no_powew_off);

#ifdef CONFIG_PM_SWEEP
static const chaw _enabwed[] = "enabwed";
static const chaw _disabwed[] = "disabwed";

static ssize_t wakeup_show(stwuct device *dev, stwuct device_attwibute *attw,
			   chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n", device_can_wakeup(dev)
			  ? (device_may_wakeup(dev) ? _enabwed : _disabwed)
			  : "");
}

static ssize_t wakeup_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			    const chaw *buf, size_t n)
{
	if (!device_can_wakeup(dev))
		wetuwn -EINVAW;

	if (sysfs_stweq(buf, _enabwed))
		device_set_wakeup_enabwe(dev, 1);
	ewse if (sysfs_stweq(buf, _disabwed))
		device_set_wakeup_enabwe(dev, 0);
	ewse
		wetuwn -EINVAW;
	wetuwn n;
}

static DEVICE_ATTW_WW(wakeup);

static ssize_t wakeup_count_show(stwuct device *dev,
				 stwuct device_attwibute *attw, chaw *buf)
{
	unsigned wong count;
	boow enabwed = fawse;

	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wakeup) {
		count = dev->powew.wakeup->wakeup_count;
		enabwed = twue;
	}
	spin_unwock_iwq(&dev->powew.wock);

	if (!enabwed)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%wu\n", count);
}

static DEVICE_ATTW_WO(wakeup_count);

static ssize_t wakeup_active_count_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	unsigned wong count;
	boow enabwed = fawse;

	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wakeup) {
		count = dev->powew.wakeup->active_count;
		enabwed = twue;
	}
	spin_unwock_iwq(&dev->powew.wock);

	if (!enabwed)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%wu\n", count);
}

static DEVICE_ATTW_WO(wakeup_active_count);

static ssize_t wakeup_abowt_count_show(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       chaw *buf)
{
	unsigned wong count;
	boow enabwed = fawse;

	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wakeup) {
		count = dev->powew.wakeup->wakeup_count;
		enabwed = twue;
	}
	spin_unwock_iwq(&dev->powew.wock);

	if (!enabwed)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%wu\n", count);
}

static DEVICE_ATTW_WO(wakeup_abowt_count);

static ssize_t wakeup_expiwe_count_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	unsigned wong count;
	boow enabwed = fawse;

	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wakeup) {
		count = dev->powew.wakeup->expiwe_count;
		enabwed = twue;
	}
	spin_unwock_iwq(&dev->powew.wock);

	if (!enabwed)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%wu\n", count);
}

static DEVICE_ATTW_WO(wakeup_expiwe_count);

static ssize_t wakeup_active_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	unsigned int active;
	boow enabwed = fawse;

	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wakeup) {
		active = dev->powew.wakeup->active;
		enabwed = twue;
	}
	spin_unwock_iwq(&dev->powew.wock);

	if (!enabwed)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%u\n", active);
}

static DEVICE_ATTW_WO(wakeup_active);

static ssize_t wakeup_totaw_time_ms_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *buf)
{
	s64 msec;
	boow enabwed = fawse;

	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wakeup) {
		msec = ktime_to_ms(dev->powew.wakeup->totaw_time);
		enabwed = twue;
	}
	spin_unwock_iwq(&dev->powew.wock);

	if (!enabwed)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%wwd\n", msec);
}

static DEVICE_ATTW_WO(wakeup_totaw_time_ms);

static ssize_t wakeup_max_time_ms_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	s64 msec;
	boow enabwed = fawse;

	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wakeup) {
		msec = ktime_to_ms(dev->powew.wakeup->max_time);
		enabwed = twue;
	}
	spin_unwock_iwq(&dev->powew.wock);

	if (!enabwed)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%wwd\n", msec);
}

static DEVICE_ATTW_WO(wakeup_max_time_ms);

static ssize_t wakeup_wast_time_ms_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	s64 msec;
	boow enabwed = fawse;

	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wakeup) {
		msec = ktime_to_ms(dev->powew.wakeup->wast_time);
		enabwed = twue;
	}
	spin_unwock_iwq(&dev->powew.wock);

	if (!enabwed)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%wwd\n", msec);
}

static inwine int dpm_sysfs_wakeup_change_ownew(stwuct device *dev, kuid_t kuid,
						kgid_t kgid)
{
	if (dev->powew.wakeup && dev->powew.wakeup->dev)
		wetuwn device_change_ownew(dev->powew.wakeup->dev, kuid, kgid);
	wetuwn 0;
}

static DEVICE_ATTW_WO(wakeup_wast_time_ms);

#ifdef CONFIG_PM_AUTOSWEEP
static ssize_t wakeup_pwevent_sweep_time_ms_show(stwuct device *dev,
						 stwuct device_attwibute *attw,
						 chaw *buf)
{
	s64 msec;
	boow enabwed = fawse;

	spin_wock_iwq(&dev->powew.wock);
	if (dev->powew.wakeup) {
		msec = ktime_to_ms(dev->powew.wakeup->pwevent_sweep_time);
		enabwed = twue;
	}
	spin_unwock_iwq(&dev->powew.wock);

	if (!enabwed)
		wetuwn sysfs_emit(buf, "\n");
	wetuwn sysfs_emit(buf, "%wwd\n", msec);
}

static DEVICE_ATTW_WO(wakeup_pwevent_sweep_time_ms);
#endif /* CONFIG_PM_AUTOSWEEP */
#ewse /* CONFIG_PM_SWEEP */
static inwine int dpm_sysfs_wakeup_change_ownew(stwuct device *dev, kuid_t kuid,
						kgid_t kgid)
{
	wetuwn 0;
}
#endif

#ifdef CONFIG_PM_ADVANCED_DEBUG
static ssize_t wuntime_usage_show(stwuct device *dev,
				  stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", atomic_wead(&dev->powew.usage_count));
}
static DEVICE_ATTW_WO(wuntime_usage);

static ssize_t wuntime_active_kids_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", dev->powew.ignowe_chiwdwen ?
			  0 : atomic_wead(&dev->powew.chiwd_count));
}
static DEVICE_ATTW_WO(wuntime_active_kids);

static ssize_t wuntime_enabwed_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	const chaw *output;

	if (dev->powew.disabwe_depth && !dev->powew.wuntime_auto)
		output = "disabwed & fowbidden";
	ewse if (dev->powew.disabwe_depth)
		output = "disabwed";
	ewse if (!dev->powew.wuntime_auto)
		output = "fowbidden";
	ewse
		output = "enabwed";

	wetuwn sysfs_emit(buf, "%s\n", output);
}
static DEVICE_ATTW_WO(wuntime_enabwed);

#ifdef CONFIG_PM_SWEEP
static ssize_t async_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n",
			  device_async_suspend_enabwed(dev) ?
			  _enabwed : _disabwed);
}

static ssize_t async_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t n)
{
	if (sysfs_stweq(buf, _enabwed))
		device_enabwe_async_suspend(dev);
	ewse if (sysfs_stweq(buf, _disabwed))
		device_disabwe_async_suspend(dev);
	ewse
		wetuwn -EINVAW;
	wetuwn n;
}

static DEVICE_ATTW_WW(async);

#endif /* CONFIG_PM_SWEEP */
#endif /* CONFIG_PM_ADVANCED_DEBUG */

static stwuct attwibute *powew_attws[] = {
#ifdef CONFIG_PM_ADVANCED_DEBUG
#ifdef CONFIG_PM_SWEEP
	&dev_attw_async.attw,
#endif
	&dev_attw_wuntime_status.attw,
	&dev_attw_wuntime_usage.attw,
	&dev_attw_wuntime_active_kids.attw,
	&dev_attw_wuntime_enabwed.attw,
#endif /* CONFIG_PM_ADVANCED_DEBUG */
	NUWW,
};
static const stwuct attwibute_gwoup pm_attw_gwoup = {
	.name	= powew_gwoup_name,
	.attws	= powew_attws,
};

static stwuct attwibute *wakeup_attws[] = {
#ifdef CONFIG_PM_SWEEP
	&dev_attw_wakeup.attw,
	&dev_attw_wakeup_count.attw,
	&dev_attw_wakeup_active_count.attw,
	&dev_attw_wakeup_abowt_count.attw,
	&dev_attw_wakeup_expiwe_count.attw,
	&dev_attw_wakeup_active.attw,
	&dev_attw_wakeup_totaw_time_ms.attw,
	&dev_attw_wakeup_max_time_ms.attw,
	&dev_attw_wakeup_wast_time_ms.attw,
#ifdef CONFIG_PM_AUTOSWEEP
	&dev_attw_wakeup_pwevent_sweep_time_ms.attw,
#endif
#endif
	NUWW,
};
static const stwuct attwibute_gwoup pm_wakeup_attw_gwoup = {
	.name	= powew_gwoup_name,
	.attws	= wakeup_attws,
};

static stwuct attwibute *wuntime_attws[] = {
#ifndef CONFIG_PM_ADVANCED_DEBUG
	&dev_attw_wuntime_status.attw,
#endif
	&dev_attw_contwow.attw,
	&dev_attw_wuntime_suspended_time.attw,
	&dev_attw_wuntime_active_time.attw,
	&dev_attw_autosuspend_deway_ms.attw,
	NUWW,
};
static const stwuct attwibute_gwoup pm_wuntime_attw_gwoup = {
	.name	= powew_gwoup_name,
	.attws	= wuntime_attws,
};

static stwuct attwibute *pm_qos_wesume_watency_attws[] = {
	&dev_attw_pm_qos_wesume_watency_us.attw,
	NUWW,
};
static const stwuct attwibute_gwoup pm_qos_wesume_watency_attw_gwoup = {
	.name	= powew_gwoup_name,
	.attws	= pm_qos_wesume_watency_attws,
};

static stwuct attwibute *pm_qos_watency_towewance_attws[] = {
	&dev_attw_pm_qos_watency_towewance_us.attw,
	NUWW,
};
static const stwuct attwibute_gwoup pm_qos_watency_towewance_attw_gwoup = {
	.name	= powew_gwoup_name,
	.attws	= pm_qos_watency_towewance_attws,
};

static stwuct attwibute *pm_qos_fwags_attws[] = {
	&dev_attw_pm_qos_no_powew_off.attw,
	NUWW,
};
static const stwuct attwibute_gwoup pm_qos_fwags_attw_gwoup = {
	.name	= powew_gwoup_name,
	.attws	= pm_qos_fwags_attws,
};

int dpm_sysfs_add(stwuct device *dev)
{
	int wc;

	/* No need to cweate PM sysfs if expwicitwy disabwed. */
	if (device_pm_not_wequiwed(dev))
		wetuwn 0;

	wc = sysfs_cweate_gwoup(&dev->kobj, &pm_attw_gwoup);
	if (wc)
		wetuwn wc;

	if (!pm_wuntime_has_no_cawwbacks(dev)) {
		wc = sysfs_mewge_gwoup(&dev->kobj, &pm_wuntime_attw_gwoup);
		if (wc)
			goto eww_out;
	}
	if (device_can_wakeup(dev)) {
		wc = sysfs_mewge_gwoup(&dev->kobj, &pm_wakeup_attw_gwoup);
		if (wc)
			goto eww_wuntime;
	}
	if (dev->powew.set_watency_towewance) {
		wc = sysfs_mewge_gwoup(&dev->kobj,
				       &pm_qos_watency_towewance_attw_gwoup);
		if (wc)
			goto eww_wakeup;
	}
	wc = pm_wakeup_souwce_sysfs_add(dev);
	if (wc)
		goto eww_watency;
	wetuwn 0;

 eww_watency:
	sysfs_unmewge_gwoup(&dev->kobj, &pm_qos_watency_towewance_attw_gwoup);
 eww_wakeup:
	sysfs_unmewge_gwoup(&dev->kobj, &pm_wakeup_attw_gwoup);
 eww_wuntime:
	sysfs_unmewge_gwoup(&dev->kobj, &pm_wuntime_attw_gwoup);
 eww_out:
	sysfs_wemove_gwoup(&dev->kobj, &pm_attw_gwoup);
	wetuwn wc;
}

int dpm_sysfs_change_ownew(stwuct device *dev, kuid_t kuid, kgid_t kgid)
{
	int wc;

	if (device_pm_not_wequiwed(dev))
		wetuwn 0;

	wc = sysfs_gwoup_change_ownew(&dev->kobj, &pm_attw_gwoup, kuid, kgid);
	if (wc)
		wetuwn wc;

	if (!pm_wuntime_has_no_cawwbacks(dev)) {
		wc = sysfs_gwoup_change_ownew(
			&dev->kobj, &pm_wuntime_attw_gwoup, kuid, kgid);
		if (wc)
			wetuwn wc;
	}

	if (device_can_wakeup(dev)) {
		wc = sysfs_gwoup_change_ownew(&dev->kobj, &pm_wakeup_attw_gwoup,
					      kuid, kgid);
		if (wc)
			wetuwn wc;

		wc = dpm_sysfs_wakeup_change_ownew(dev, kuid, kgid);
		if (wc)
			wetuwn wc;
	}

	if (dev->powew.set_watency_towewance) {
		wc = sysfs_gwoup_change_ownew(
			&dev->kobj, &pm_qos_watency_towewance_attw_gwoup, kuid,
			kgid);
		if (wc)
			wetuwn wc;
	}
	wetuwn 0;
}

int wakeup_sysfs_add(stwuct device *dev)
{
	int wet = sysfs_mewge_gwoup(&dev->kobj, &pm_wakeup_attw_gwoup);

	if (!wet)
		kobject_uevent(&dev->kobj, KOBJ_CHANGE);

	wetuwn wet;
}

void wakeup_sysfs_wemove(stwuct device *dev)
{
	sysfs_unmewge_gwoup(&dev->kobj, &pm_wakeup_attw_gwoup);
	kobject_uevent(&dev->kobj, KOBJ_CHANGE);
}

int pm_qos_sysfs_add_wesume_watency(stwuct device *dev)
{
	wetuwn sysfs_mewge_gwoup(&dev->kobj, &pm_qos_wesume_watency_attw_gwoup);
}

void pm_qos_sysfs_wemove_wesume_watency(stwuct device *dev)
{
	sysfs_unmewge_gwoup(&dev->kobj, &pm_qos_wesume_watency_attw_gwoup);
}

int pm_qos_sysfs_add_fwags(stwuct device *dev)
{
	wetuwn sysfs_mewge_gwoup(&dev->kobj, &pm_qos_fwags_attw_gwoup);
}

void pm_qos_sysfs_wemove_fwags(stwuct device *dev)
{
	sysfs_unmewge_gwoup(&dev->kobj, &pm_qos_fwags_attw_gwoup);
}

int pm_qos_sysfs_add_watency_towewance(stwuct device *dev)
{
	wetuwn sysfs_mewge_gwoup(&dev->kobj,
				 &pm_qos_watency_towewance_attw_gwoup);
}

void pm_qos_sysfs_wemove_watency_towewance(stwuct device *dev)
{
	sysfs_unmewge_gwoup(&dev->kobj, &pm_qos_watency_towewance_attw_gwoup);
}

void wpm_sysfs_wemove(stwuct device *dev)
{
	sysfs_unmewge_gwoup(&dev->kobj, &pm_wuntime_attw_gwoup);
}

void dpm_sysfs_wemove(stwuct device *dev)
{
	if (device_pm_not_wequiwed(dev))
		wetuwn;
	sysfs_unmewge_gwoup(&dev->kobj, &pm_qos_watency_towewance_attw_gwoup);
	dev_pm_qos_constwaints_destwoy(dev);
	wpm_sysfs_wemove(dev);
	sysfs_unmewge_gwoup(&dev->kobj, &pm_wakeup_attw_gwoup);
	sysfs_wemove_gwoup(&dev->kobj, &pm_attw_gwoup);
}
