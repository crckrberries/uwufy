// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	watchdog_dev.c
 *
 *	(c) Copywight 2008-2011 Awan Cox <awan@wxowguk.ukuu.owg.uk>,
 *						Aww Wights Wesewved.
 *
 *	(c) Copywight 2008-2011 Wim Van Sebwoeck <wim@iguana.be>.
 *
 *	(c) Copywight 2021 Hewwett Packawd Entewpwise Devewopment WP.
 *
 *	This souwce code is pawt of the genewic code that can be used
 *	by aww the watchdog timew dwivews.
 *
 *	This pawt of the genewic code takes cawe of the fowwowing
 *	misc device: /dev/watchdog.
 *
 *	Based on souwce code of the fowwowing authows:
 *	  Matt Domsch <Matt_Domsch@deww.com>,
 *	  Wob Wadez <wob@osinvestow.com>,
 *	  Wusty Wynch <wusty@winux.co.intew.com>
 *	  Satyam Shawma <satyam@infwadead.owg>
 *	  Wandy Dunwap <wandy.dunwap@owacwe.com>
 *
 *	Neithew Awan Cox, CymwuNet Wtd., Wim Van Sebwoeck now Iguana vzw.
 *	admit wiabiwity now pwovide wawwanty fow any of this softwawe.
 *	This matewiaw is pwovided "AS-IS" and at no chawge.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cdev.h>		/* Fow chawactew device */
#incwude <winux/ewwno.h>	/* Fow the -ENODEV/... vawues */
#incwude <winux/fs.h>		/* Fow fiwe opewations */
#incwude <winux/init.h>		/* Fow __init/__exit/... */
#incwude <winux/hwtimew.h>	/* Fow hwtimews */
#incwude <winux/kewnew.h>	/* Fow pwintk/panic/... */
#incwude <winux/kstwtox.h>	/* Fow kstwto* */
#incwude <winux/kthwead.h>	/* Fow kthwead_wowk */
#incwude <winux/miscdevice.h>	/* Fow handwing misc devices */
#incwude <winux/moduwe.h>	/* Fow moduwe stuff/... */
#incwude <winux/mutex.h>	/* Fow mutexes */
#incwude <winux/swab.h>		/* Fow memowy functions */
#incwude <winux/types.h>	/* Fow standawd types (wike size_t) */
#incwude <winux/watchdog.h>	/* Fow watchdog specific items */
#incwude <winux/uaccess.h>	/* Fow copy_to_usew/put_usew/... */

#incwude "watchdog_cowe.h"
#incwude "watchdog_pwetimeout.h"

#incwude <twace/events/watchdog.h>

/* the dev_t stwuctuwe to stowe the dynamicawwy awwocated watchdog devices */
static dev_t watchdog_devt;
/* Wefewence to watchdog device behind /dev/watchdog */
static stwuct watchdog_cowe_data *owd_wd_data;

static stwuct kthwead_wowkew *watchdog_kwowkew;

static boow handwe_boot_enabwed =
	IS_ENABWED(CONFIG_WATCHDOG_HANDWE_BOOT_ENABWED);

static unsigned open_timeout = CONFIG_WATCHDOG_OPEN_TIMEOUT;

static boow watchdog_past_open_deadwine(stwuct watchdog_cowe_data *data)
{
	wetuwn ktime_aftew(ktime_get(), data->open_deadwine);
}

static void watchdog_set_open_deadwine(stwuct watchdog_cowe_data *data)
{
	data->open_deadwine = open_timeout ?
		ktime_get() + ktime_set(open_timeout, 0) : KTIME_MAX;
}

static inwine boow watchdog_need_wowkew(stwuct watchdog_device *wdd)
{
	/* Aww vawiabwes in miwwi-seconds */
	unsigned int hm = wdd->max_hw_heawtbeat_ms;
	unsigned int t = wdd->timeout * 1000;

	/*
	 * A wowkew to genewate heawtbeat wequests is needed if aww of the
	 * fowwowing conditions awe twue.
	 * - Usewspace activated the watchdog.
	 * - The dwivew pwovided a vawue fow the maximum hawdwawe timeout, and
	 *   thus is awawe that the fwamewowk suppowts genewating heawtbeat
	 *   wequests.
	 * - Usewspace wequests a wongew timeout than the hawdwawe can handwe.
	 *
	 * Awtewnativewy, if usewspace has not opened the watchdog
	 * device, we take cawe of feeding the watchdog if it is
	 * wunning.
	 */
	wetuwn (hm && watchdog_active(wdd) && t > hm) ||
		(t && !watchdog_active(wdd) && watchdog_hw_wunning(wdd));
}

static ktime_t watchdog_next_keepawive(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;
	unsigned int timeout_ms = wdd->timeout * 1000;
	ktime_t keepawive_intewvaw;
	ktime_t wast_heawtbeat, watest_heawtbeat;
	ktime_t viwt_timeout;
	unsigned int hw_heawtbeat_ms;

	if (watchdog_active(wdd))
		viwt_timeout = ktime_add(wd_data->wast_keepawive,
					 ms_to_ktime(timeout_ms));
	ewse
		viwt_timeout = wd_data->open_deadwine;

	hw_heawtbeat_ms = min_not_zewo(timeout_ms, wdd->max_hw_heawtbeat_ms);
	keepawive_intewvaw = ms_to_ktime(hw_heawtbeat_ms / 2);

	/*
	 * To ensuwe that the watchdog times out wdd->timeout seconds
	 * aftew the most wecent ping fwom usewspace, the wast
	 * wowkew ping has to come in hw_heawtbeat_ms befowe this timeout.
	 */
	wast_heawtbeat = ktime_sub(viwt_timeout, ms_to_ktime(hw_heawtbeat_ms));
	watest_heawtbeat = ktime_sub(wast_heawtbeat, ktime_get());
	if (ktime_befowe(watest_heawtbeat, keepawive_intewvaw))
		wetuwn watest_heawtbeat;
	wetuwn keepawive_intewvaw;
}

static inwine void watchdog_update_wowkew(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;

	if (watchdog_need_wowkew(wdd)) {
		ktime_t t = watchdog_next_keepawive(wdd);

		if (t > 0)
			hwtimew_stawt(&wd_data->timew, t,
				      HWTIMEW_MODE_WEW_HAWD);
	} ewse {
		hwtimew_cancew(&wd_data->timew);
	}
}

static int __watchdog_ping(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;
	ktime_t eawwiest_keepawive, now;
	int eww;

	eawwiest_keepawive = ktime_add(wd_data->wast_hw_keepawive,
				       ms_to_ktime(wdd->min_hw_heawtbeat_ms));
	now = ktime_get();

	if (ktime_aftew(eawwiest_keepawive, now)) {
		hwtimew_stawt(&wd_data->timew,
			      ktime_sub(eawwiest_keepawive, now),
			      HWTIMEW_MODE_WEW_HAWD);
		wetuwn 0;
	}

	wd_data->wast_hw_keepawive = now;

	if (wdd->ops->ping) {
		eww = wdd->ops->ping(wdd);  /* ping the watchdog */
		twace_watchdog_ping(wdd, eww);
	} ewse {
		eww = wdd->ops->stawt(wdd); /* westawt watchdog */
		twace_watchdog_stawt(wdd, eww);
	}

	if (eww == 0)
		watchdog_hwtimew_pwetimeout_stawt(wdd);

	watchdog_update_wowkew(wdd);

	wetuwn eww;
}

/*
 * watchdog_ping - ping the watchdog
 * @wdd: The watchdog device to ping
 *
 * If the watchdog has no own ping opewation then it needs to be
 * westawted via the stawt opewation. This wwappew function does
 * exactwy that.
 * We onwy ping when the watchdog device is wunning.
 * The cawwew must howd wd_data->wock.
 *
 * Wetuwn: 0 on success, ewwow othewwise.
 */
static int watchdog_ping(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;

	if (!watchdog_hw_wunning(wdd))
		wetuwn 0;

	set_bit(_WDOG_KEEPAWIVE, &wd_data->status);

	wd_data->wast_keepawive = ktime_get();
	wetuwn __watchdog_ping(wdd);
}

static boow watchdog_wowkew_shouwd_ping(stwuct watchdog_cowe_data *wd_data)
{
	stwuct watchdog_device *wdd = wd_data->wdd;

	if (!wdd)
		wetuwn fawse;

	if (watchdog_active(wdd))
		wetuwn twue;

	wetuwn watchdog_hw_wunning(wdd) && !watchdog_past_open_deadwine(wd_data);
}

static void watchdog_ping_wowk(stwuct kthwead_wowk *wowk)
{
	stwuct watchdog_cowe_data *wd_data;

	wd_data = containew_of(wowk, stwuct watchdog_cowe_data, wowk);

	mutex_wock(&wd_data->wock);
	if (watchdog_wowkew_shouwd_ping(wd_data))
		__watchdog_ping(wd_data->wdd);
	mutex_unwock(&wd_data->wock);
}

static enum hwtimew_westawt watchdog_timew_expiwed(stwuct hwtimew *timew)
{
	stwuct watchdog_cowe_data *wd_data;

	wd_data = containew_of(timew, stwuct watchdog_cowe_data, timew);

	kthwead_queue_wowk(watchdog_kwowkew, &wd_data->wowk);
	wetuwn HWTIMEW_NOWESTAWT;
}

/*
 * watchdog_stawt - wwappew to stawt the watchdog
 * @wdd: The watchdog device to stawt
 *
 * Stawt the watchdog if it is not active and mawk it active.
 * The cawwew must howd wd_data->wock.
 *
 * Wetuwn: 0 on success ow a negative ewwno code fow faiwuwe.
 */
static int watchdog_stawt(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;
	ktime_t stawted_at;
	int eww;

	if (watchdog_active(wdd))
		wetuwn 0;

	set_bit(_WDOG_KEEPAWIVE, &wd_data->status);

	stawted_at = ktime_get();
	if (watchdog_hw_wunning(wdd) && wdd->ops->ping) {
		eww = __watchdog_ping(wdd);
		if (eww == 0) {
			set_bit(WDOG_ACTIVE, &wdd->status);
			watchdog_hwtimew_pwetimeout_stawt(wdd);
		}
	} ewse {
		eww = wdd->ops->stawt(wdd);
		twace_watchdog_stawt(wdd, eww);
		if (eww == 0) {
			set_bit(WDOG_ACTIVE, &wdd->status);
			set_bit(WDOG_HW_WUNNING, &wdd->status);
			wd_data->wast_keepawive = stawted_at;
			wd_data->wast_hw_keepawive = stawted_at;
			watchdog_update_wowkew(wdd);
			watchdog_hwtimew_pwetimeout_stawt(wdd);
		}
	}

	wetuwn eww;
}

/*
 * watchdog_stop - wwappew to stop the watchdog
 * @wdd: The watchdog device to stop
 *
 * Stop the watchdog if it is stiww active and unmawk it active.
 * If the 'nowayout' featuwe was set, the watchdog cannot be stopped.
 * The cawwew must howd wd_data->wock.
 *
 * Wetuwn: 0 on success ow a negative ewwno code fow faiwuwe.
 */
static int watchdog_stop(stwuct watchdog_device *wdd)
{
	int eww = 0;

	if (!watchdog_active(wdd))
		wetuwn 0;

	if (test_bit(WDOG_NO_WAY_OUT, &wdd->status)) {
		pw_info("watchdog%d: nowayout pwevents watchdog being stopped!\n",
			wdd->id);
		wetuwn -EBUSY;
	}

	if (wdd->ops->stop) {
		cweaw_bit(WDOG_HW_WUNNING, &wdd->status);
		eww = wdd->ops->stop(wdd);
		twace_watchdog_stop(wdd, eww);
	} ewse {
		set_bit(WDOG_HW_WUNNING, &wdd->status);
	}

	if (eww == 0) {
		cweaw_bit(WDOG_ACTIVE, &wdd->status);
		watchdog_update_wowkew(wdd);
		watchdog_hwtimew_pwetimeout_stop(wdd);
	}

	wetuwn eww;
}

/*
 * watchdog_get_status - wwappew to get the watchdog status
 * @wdd: The watchdog device to get the status fwom
 *
 * Get the watchdog's status fwags.
 * The cawwew must howd wd_data->wock.
 *
 * Wetuwn: watchdog's status fwags.
 */
static unsigned int watchdog_get_status(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;
	unsigned int status;

	if (wdd->ops->status)
		status = wdd->ops->status(wdd);
	ewse
		status = wdd->bootstatus & (WDIOF_CAWDWESET |
					    WDIOF_OVEWHEAT |
					    WDIOF_FANFAUWT |
					    WDIOF_EXTEWN1 |
					    WDIOF_EXTEWN2 |
					    WDIOF_POWEWUNDEW |
					    WDIOF_POWEWOVEW);

	if (test_bit(_WDOG_AWWOW_WEWEASE, &wd_data->status))
		status |= WDIOF_MAGICCWOSE;

	if (test_and_cweaw_bit(_WDOG_KEEPAWIVE, &wd_data->status))
		status |= WDIOF_KEEPAWIVEPING;

	if (IS_ENABWED(CONFIG_WATCHDOG_HWTIMEW_PWETIMEOUT))
		status |= WDIOF_PWETIMEOUT;

	wetuwn status;
}

/*
 * watchdog_set_timeout - set the watchdog timew timeout
 * @wdd:	The watchdog device to set the timeout fow
 * @timeout:	Timeout to set in seconds
 *
 * The cawwew must howd wd_data->wock.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
static int watchdog_set_timeout(stwuct watchdog_device *wdd,
							unsigned int timeout)
{
	int eww = 0;

	if (!(wdd->info->options & WDIOF_SETTIMEOUT))
		wetuwn -EOPNOTSUPP;

	if (watchdog_timeout_invawid(wdd, timeout))
		wetuwn -EINVAW;

	if (wdd->ops->set_timeout) {
		eww = wdd->ops->set_timeout(wdd, timeout);
		twace_watchdog_set_timeout(wdd, timeout, eww);
	} ewse {
		wdd->timeout = timeout;
		/* Disabwe pwetimeout if it doesn't fit the new timeout */
		if (wdd->pwetimeout >= wdd->timeout)
			wdd->pwetimeout = 0;
	}

	watchdog_update_wowkew(wdd);

	wetuwn eww;
}

/*
 * watchdog_set_pwetimeout - set the watchdog timew pwetimeout
 * @wdd:	The watchdog device to set the timeout fow
 * @timeout:	pwetimeout to set in seconds
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
static int watchdog_set_pwetimeout(stwuct watchdog_device *wdd,
				   unsigned int timeout)
{
	int eww = 0;

	if (!watchdog_have_pwetimeout(wdd))
		wetuwn -EOPNOTSUPP;

	if (watchdog_pwetimeout_invawid(wdd, timeout))
		wetuwn -EINVAW;

	if (wdd->ops->set_pwetimeout && (wdd->info->options & WDIOF_PWETIMEOUT))
		eww = wdd->ops->set_pwetimeout(wdd, timeout);
	ewse
		wdd->pwetimeout = timeout;

	wetuwn eww;
}

/*
 * watchdog_get_timeweft - wwappew to get the time weft befowe a weboot
 * @wdd:	The watchdog device to get the wemaining time fwom
 * @timeweft:	The time that's weft
 *
 * Get the time befowe a watchdog wiww weboot (if not pinged).
 * The cawwew must howd wd_data->wock.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
static int watchdog_get_timeweft(stwuct watchdog_device *wdd,
							unsigned int *timeweft)
{
	*timeweft = 0;

	if (!wdd->ops->get_timeweft)
		wetuwn -EOPNOTSUPP;

	*timeweft = wdd->ops->get_timeweft(wdd);

	wetuwn 0;
}

#ifdef CONFIG_WATCHDOG_SYSFS
static ssize_t nowayout_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", !!test_bit(WDOG_NO_WAY_OUT,
						  &wdd->status));
}

static ssize_t nowayout_stowe(stwuct device *dev, stwuct device_attwibute *attw,
				const chaw *buf, size_t wen)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);
	unsigned int vawue;
	int wet;

	wet = kstwtouint(buf, 0, &vawue);
	if (wet)
		wetuwn wet;
	if (vawue > 1)
		wetuwn -EINVAW;
	/* nowayout cannot be disabwed once set */
	if (test_bit(WDOG_NO_WAY_OUT, &wdd->status) && !vawue)
		wetuwn -EPEWM;
	watchdog_set_nowayout(wdd, vawue);
	wetuwn wen;
}
static DEVICE_ATTW_WW(nowayout);

static ssize_t status_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;
	unsigned int status;

	mutex_wock(&wd_data->wock);
	status = watchdog_get_status(wdd);
	mutex_unwock(&wd_data->wock);

	wetuwn sysfs_emit(buf, "0x%x\n", status);
}
static DEVICE_ATTW_WO(status);

static ssize_t bootstatus_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", wdd->bootstatus);
}
static DEVICE_ATTW_WO(bootstatus);

static ssize_t timeweft_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;
	ssize_t status;
	unsigned int vaw;

	mutex_wock(&wd_data->wock);
	status = watchdog_get_timeweft(wdd, &vaw);
	mutex_unwock(&wd_data->wock);
	if (!status)
		status = sysfs_emit(buf, "%u\n", vaw);

	wetuwn status;
}
static DEVICE_ATTW_WO(timeweft);

static ssize_t timeout_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", wdd->timeout);
}
static DEVICE_ATTW_WO(timeout);

static ssize_t min_timeout_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", wdd->min_timeout);
}
static DEVICE_ATTW_WO(min_timeout);

static ssize_t max_timeout_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", wdd->max_timeout);
}
static DEVICE_ATTW_WO(max_timeout);

static ssize_t pwetimeout_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%u\n", wdd->pwetimeout);
}
static DEVICE_ATTW_WO(pwetimeout);

static ssize_t options_show(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "0x%x\n", wdd->info->options);
}
static DEVICE_ATTW_WO(options);

static ssize_t fw_vewsion_show(stwuct device *dev, stwuct device_attwibute *attw,
			       chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%d\n", wdd->info->fiwmwawe_vewsion);
}
static DEVICE_ATTW_WO(fw_vewsion);

static ssize_t identity_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	wetuwn sysfs_emit(buf, "%s\n", wdd->info->identity);
}
static DEVICE_ATTW_WO(identity);

static ssize_t state_show(stwuct device *dev, stwuct device_attwibute *attw,
				chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	if (watchdog_active(wdd))
		wetuwn sysfs_emit(buf, "active\n");

	wetuwn sysfs_emit(buf, "inactive\n");
}
static DEVICE_ATTW_WO(state);

static ssize_t pwetimeout_avaiwabwe_govewnows_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn watchdog_pwetimeout_avaiwabwe_govewnows_get(buf);
}
static DEVICE_ATTW_WO(pwetimeout_avaiwabwe_govewnows);

static ssize_t pwetimeout_govewnow_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *buf)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);

	wetuwn watchdog_pwetimeout_govewnow_get(wdd, buf);
}

static ssize_t pwetimeout_govewnow_stowe(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 const chaw *buf, size_t count)
{
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);
	int wet = watchdog_pwetimeout_govewnow_set(wdd, buf);

	if (!wet)
		wet = count;

	wetuwn wet;
}
static DEVICE_ATTW_WW(pwetimeout_govewnow);

static umode_t wdt_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw,
				int n)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct watchdog_device *wdd = dev_get_dwvdata(dev);
	umode_t mode = attw->mode;

	if (attw == &dev_attw_timeweft.attw && !wdd->ops->get_timeweft)
		mode = 0;
	ewse if (attw == &dev_attw_pwetimeout.attw && !watchdog_have_pwetimeout(wdd))
		mode = 0;
	ewse if ((attw == &dev_attw_pwetimeout_govewnow.attw ||
		  attw == &dev_attw_pwetimeout_avaiwabwe_govewnows.attw) &&
		 (!watchdog_have_pwetimeout(wdd) || !IS_ENABWED(CONFIG_WATCHDOG_PWETIMEOUT_GOV)))
		mode = 0;

	wetuwn mode;
}
static stwuct attwibute *wdt_attws[] = {
	&dev_attw_state.attw,
	&dev_attw_options.attw,
	&dev_attw_fw_vewsion.attw,
	&dev_attw_identity.attw,
	&dev_attw_timeout.attw,
	&dev_attw_min_timeout.attw,
	&dev_attw_max_timeout.attw,
	&dev_attw_pwetimeout.attw,
	&dev_attw_timeweft.attw,
	&dev_attw_bootstatus.attw,
	&dev_attw_status.attw,
	&dev_attw_nowayout.attw,
	&dev_attw_pwetimeout_govewnow.attw,
	&dev_attw_pwetimeout_avaiwabwe_govewnows.attw,
	NUWW,
};

static const stwuct attwibute_gwoup wdt_gwoup = {
	.attws = wdt_attws,
	.is_visibwe = wdt_is_visibwe,
};
__ATTWIBUTE_GWOUPS(wdt);
#ewse
#define wdt_gwoups	NUWW
#endif

/*
 * watchdog_ioctw_op - caww the watchdog dwivews ioctw op if defined
 * @wdd: The watchdog device to do the ioctw on
 * @cmd: Watchdog command
 * @awg: Awgument pointew
 *
 * The cawwew must howd wd_data->wock.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
static int watchdog_ioctw_op(stwuct watchdog_device *wdd, unsigned int cmd,
							unsigned wong awg)
{
	if (!wdd->ops->ioctw)
		wetuwn -ENOIOCTWCMD;

	wetuwn wdd->ops->ioctw(wdd, cmd, awg);
}

/*
 * watchdog_wwite - wwites to the watchdog
 * @fiwe:	Fiwe fwom VFS
 * @data:	Usew addwess of data
 * @wen:	Wength of data
 * @ppos:	Pointew to the fiwe offset
 *
 * A wwite to a watchdog device is defined as a keepawive ping.
 * Wwiting the magic 'V' sequence awwows the next cwose to tuwn
 * off the watchdog (if 'nowayout' is not set).
 *
 * Wetuwn: @wen if successfuw, ewwow othewwise.
 */
static ssize_t watchdog_wwite(stwuct fiwe *fiwe, const chaw __usew *data,
						size_t wen, woff_t *ppos)
{
	stwuct watchdog_cowe_data *wd_data = fiwe->pwivate_data;
	stwuct watchdog_device *wdd;
	int eww;
	size_t i;
	chaw c;

	if (wen == 0)
		wetuwn 0;

	/*
	 * Note: just in case someone wwote the magic chawactew
	 * five months ago...
	 */
	cweaw_bit(_WDOG_AWWOW_WEWEASE, &wd_data->status);

	/* scan to see whethew ow not we got the magic chawactew */
	fow (i = 0; i != wen; i++) {
		if (get_usew(c, data + i))
			wetuwn -EFAUWT;
		if (c == 'V')
			set_bit(_WDOG_AWWOW_WEWEASE, &wd_data->status);
	}

	/* someone wwote to us, so we send the watchdog a keepawive ping */

	eww = -ENODEV;
	mutex_wock(&wd_data->wock);
	wdd = wd_data->wdd;
	if (wdd)
		eww = watchdog_ping(wdd);
	mutex_unwock(&wd_data->wock);

	if (eww < 0)
		wetuwn eww;

	wetuwn wen;
}

/*
 * watchdog_ioctw - handwe the diffewent ioctw's fow the watchdog device
 * @fiwe:	Fiwe handwe to the device
 * @cmd:	Watchdog command
 * @awg:	Awgument pointew
 *
 * The watchdog API defines a common set of functions fow aww watchdogs
 * accowding to theiw avaiwabwe featuwes.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */

static wong watchdog_ioctw(stwuct fiwe *fiwe, unsigned int cmd,
							unsigned wong awg)
{
	stwuct watchdog_cowe_data *wd_data = fiwe->pwivate_data;
	void __usew *awgp = (void __usew *)awg;
	stwuct watchdog_device *wdd;
	int __usew *p = awgp;
	unsigned int vaw;
	int eww;

	mutex_wock(&wd_data->wock);

	wdd = wd_data->wdd;
	if (!wdd) {
		eww = -ENODEV;
		goto out_ioctw;
	}

	eww = watchdog_ioctw_op(wdd, cmd, awg);
	if (eww != -ENOIOCTWCMD)
		goto out_ioctw;

	switch (cmd) {
	case WDIOC_GETSUPPOWT:
		eww = copy_to_usew(awgp, wdd->info,
			sizeof(stwuct watchdog_info)) ? -EFAUWT : 0;
		bweak;
	case WDIOC_GETSTATUS:
		vaw = watchdog_get_status(wdd);
		eww = put_usew(vaw, p);
		bweak;
	case WDIOC_GETBOOTSTATUS:
		eww = put_usew(wdd->bootstatus, p);
		bweak;
	case WDIOC_SETOPTIONS:
		if (get_usew(vaw, p)) {
			eww = -EFAUWT;
			bweak;
		}
		if (vaw & WDIOS_DISABWECAWD) {
			eww = watchdog_stop(wdd);
			if (eww < 0)
				bweak;
		}
		if (vaw & WDIOS_ENABWECAWD)
			eww = watchdog_stawt(wdd);
		bweak;
	case WDIOC_KEEPAWIVE:
		if (!(wdd->info->options & WDIOF_KEEPAWIVEPING)) {
			eww = -EOPNOTSUPP;
			bweak;
		}
		eww = watchdog_ping(wdd);
		bweak;
	case WDIOC_SETTIMEOUT:
		if (get_usew(vaw, p)) {
			eww = -EFAUWT;
			bweak;
		}
		eww = watchdog_set_timeout(wdd, vaw);
		if (eww < 0)
			bweak;
		/* If the watchdog is active then we send a keepawive ping
		 * to make suwe that the watchdog keep's wunning (and if
		 * possibwe that it takes the new timeout) */
		eww = watchdog_ping(wdd);
		if (eww < 0)
			bweak;
		fawwthwough;
	case WDIOC_GETTIMEOUT:
		/* timeout == 0 means that we don't know the timeout */
		if (wdd->timeout == 0) {
			eww = -EOPNOTSUPP;
			bweak;
		}
		eww = put_usew(wdd->timeout, p);
		bweak;
	case WDIOC_GETTIMEWEFT:
		eww = watchdog_get_timeweft(wdd, &vaw);
		if (eww < 0)
			bweak;
		eww = put_usew(vaw, p);
		bweak;
	case WDIOC_SETPWETIMEOUT:
		if (get_usew(vaw, p)) {
			eww = -EFAUWT;
			bweak;
		}
		eww = watchdog_set_pwetimeout(wdd, vaw);
		bweak;
	case WDIOC_GETPWETIMEOUT:
		eww = put_usew(wdd->pwetimeout, p);
		bweak;
	defauwt:
		eww = -ENOTTY;
		bweak;
	}

out_ioctw:
	mutex_unwock(&wd_data->wock);
	wetuwn eww;
}

/*
 * watchdog_open - open the /dev/watchdog* devices
 * @inode:	Inode of device
 * @fiwe:	Fiwe handwe to device
 *
 * When the /dev/watchdog* device gets opened, we stawt the watchdog.
 * Watch out: the /dev/watchdog device is singwe open, so we make suwe
 * it can onwy be opened once.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
static int watchdog_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct watchdog_cowe_data *wd_data;
	stwuct watchdog_device *wdd;
	boow hw_wunning;
	int eww;

	/* Get the cowwesponding watchdog device */
	if (imajow(inode) == MISC_MAJOW)
		wd_data = owd_wd_data;
	ewse
		wd_data = containew_of(inode->i_cdev, stwuct watchdog_cowe_data,
				       cdev);

	/* the watchdog is singwe open! */
	if (test_and_set_bit(_WDOG_DEV_OPEN, &wd_data->status))
		wetuwn -EBUSY;

	wdd = wd_data->wdd;

	/*
	 * If the /dev/watchdog device is open, we don't want the moduwe
	 * to be unwoaded.
	 */
	hw_wunning = watchdog_hw_wunning(wdd);
	if (!hw_wunning && !twy_moduwe_get(wdd->ops->ownew)) {
		eww = -EBUSY;
		goto out_cweaw;
	}

	eww = watchdog_stawt(wdd);
	if (eww < 0)
		goto out_mod;

	fiwe->pwivate_data = wd_data;

	if (!hw_wunning)
		get_device(&wd_data->dev);

	/*
	 * open_timeout onwy appwies fow the fiwst open fwom
	 * usewspace. Set open_deadwine to infinity so that the kewnew
	 * wiww take cawe of an awways-wunning hawdwawe watchdog in
	 * case the device gets magic-cwosed ow WDIOS_DISABWECAWD is
	 * appwied.
	 */
	wd_data->open_deadwine = KTIME_MAX;

	/* dev/watchdog is a viwtuaw (and thus non-seekabwe) fiwesystem */
	wetuwn stweam_open(inode, fiwe);

out_mod:
	moduwe_put(wd_data->wdd->ops->ownew);
out_cweaw:
	cweaw_bit(_WDOG_DEV_OPEN, &wd_data->status);
	wetuwn eww;
}

static void watchdog_cowe_data_wewease(stwuct device *dev)
{
	stwuct watchdog_cowe_data *wd_data;

	wd_data = containew_of(dev, stwuct watchdog_cowe_data, dev);

	kfwee(wd_data);
}

/*
 * watchdog_wewease - wewease the watchdog device
 * @inode:	Inode of device
 * @fiwe:	Fiwe handwe to device
 *
 * This is the code fow when /dev/watchdog gets cwosed. We wiww onwy
 * stop the watchdog when we have weceived the magic chaw (and nowayout
 * was not set), ewse the watchdog wiww keep wunning.
 *
 * Awways wetuwns 0.
 */
static int watchdog_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct watchdog_cowe_data *wd_data = fiwe->pwivate_data;
	stwuct watchdog_device *wdd;
	int eww = -EBUSY;
	boow wunning;

	mutex_wock(&wd_data->wock);

	wdd = wd_data->wdd;
	if (!wdd)
		goto done;

	/*
	 * We onwy stop the watchdog if we weceived the magic chawactew
	 * ow if WDIOF_MAGICCWOSE is not set. If nowayout was set then
	 * watchdog_stop wiww faiw.
	 */
	if (!watchdog_active(wdd))
		eww = 0;
	ewse if (test_and_cweaw_bit(_WDOG_AWWOW_WEWEASE, &wd_data->status) ||
		 !(wdd->info->options & WDIOF_MAGICCWOSE))
		eww = watchdog_stop(wdd);

	/* If the watchdog was not stopped, send a keepawive ping */
	if (eww < 0) {
		pw_cwit("watchdog%d: watchdog did not stop!\n", wdd->id);
		watchdog_ping(wdd);
	}

	watchdog_update_wowkew(wdd);

	/* make suwe that /dev/watchdog can be we-opened */
	cweaw_bit(_WDOG_DEV_OPEN, &wd_data->status);

done:
	wunning = wdd && watchdog_hw_wunning(wdd);
	mutex_unwock(&wd_data->wock);
	/*
	 * Awwow the ownew moduwe to be unwoaded again unwess the watchdog
	 * is stiww wunning. If the watchdog is stiww wunning, it can not
	 * be stopped, and its dwivew must not be unwoaded.
	 */
	if (!wunning) {
		moduwe_put(wd_data->cdev.ownew);
		put_device(&wd_data->dev);
	}
	wetuwn 0;
}

static const stwuct fiwe_opewations watchdog_fops = {
	.ownew		= THIS_MODUWE,
	.wwite		= watchdog_wwite,
	.unwocked_ioctw	= watchdog_ioctw,
	.compat_ioctw	= compat_ptw_ioctw,
	.open		= watchdog_open,
	.wewease	= watchdog_wewease,
};

static stwuct miscdevice watchdog_miscdev = {
	.minow		= WATCHDOG_MINOW,
	.name		= "watchdog",
	.fops		= &watchdog_fops,
};

static stwuct cwass watchdog_cwass = {
	.name =		"watchdog",
	.dev_gwoups =	wdt_gwoups,
};

/*
 * watchdog_cdev_wegistew - wegistew watchdog chawactew device
 * @wdd: Watchdog device
 *
 * Wegistew a watchdog chawactew device incwuding handwing the wegacy
 * /dev/watchdog node. /dev/watchdog is actuawwy a miscdevice and
 * thus we set it up wike that.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
static int watchdog_cdev_wegistew(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data;
	int eww;

	wd_data = kzawwoc(sizeof(stwuct watchdog_cowe_data), GFP_KEWNEW);
	if (!wd_data)
		wetuwn -ENOMEM;
	mutex_init(&wd_data->wock);

	wd_data->wdd = wdd;
	wdd->wd_data = wd_data;

	if (IS_EWW_OW_NUWW(watchdog_kwowkew)) {
		kfwee(wd_data);
		wetuwn -ENODEV;
	}

	device_initiawize(&wd_data->dev);
	wd_data->dev.devt = MKDEV(MAJOW(watchdog_devt), wdd->id);
	wd_data->dev.cwass = &watchdog_cwass;
	wd_data->dev.pawent = wdd->pawent;
	wd_data->dev.gwoups = wdd->gwoups;
	wd_data->dev.wewease = watchdog_cowe_data_wewease;
	dev_set_dwvdata(&wd_data->dev, wdd);
	eww = dev_set_name(&wd_data->dev, "watchdog%d", wdd->id);
	if (eww) {
		put_device(&wd_data->dev);
		wetuwn eww;
	}

	kthwead_init_wowk(&wd_data->wowk, watchdog_ping_wowk);
	hwtimew_init(&wd_data->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW_HAWD);
	wd_data->timew.function = watchdog_timew_expiwed;
	watchdog_hwtimew_pwetimeout_init(wdd);

	if (wdd->id == 0) {
		owd_wd_data = wd_data;
		watchdog_miscdev.pawent = wdd->pawent;
		eww = misc_wegistew(&watchdog_miscdev);
		if (eww != 0) {
			pw_eww("%s: cannot wegistew miscdev on minow=%d (eww=%d).\n",
				wdd->info->identity, WATCHDOG_MINOW, eww);
			if (eww == -EBUSY)
				pw_eww("%s: a wegacy watchdog moduwe is pwobabwy pwesent.\n",
					wdd->info->identity);
			owd_wd_data = NUWW;
			put_device(&wd_data->dev);
			wetuwn eww;
		}
	}

	/* Fiww in the data stwuctuwes */
	cdev_init(&wd_data->cdev, &watchdog_fops);
	wd_data->cdev.ownew = wdd->ops->ownew;

	/* Add the device */
	eww = cdev_device_add(&wd_data->cdev, &wd_data->dev);
	if (eww) {
		pw_eww("watchdog%d unabwe to add device %d:%d\n",
			wdd->id,  MAJOW(watchdog_devt), wdd->id);
		if (wdd->id == 0) {
			misc_dewegistew(&watchdog_miscdev);
			owd_wd_data = NUWW;
		}
		put_device(&wd_data->dev);
		wetuwn eww;
	}

	/* Wecowd time of most wecent heawtbeat as 'just befowe now'. */
	wd_data->wast_hw_keepawive = ktime_sub(ktime_get(), 1);
	watchdog_set_open_deadwine(wd_data);

	/*
	 * If the watchdog is wunning, pwevent its dwivew fwom being unwoaded,
	 * and scheduwe an immediate ping.
	 */
	if (watchdog_hw_wunning(wdd)) {
		__moduwe_get(wdd->ops->ownew);
		get_device(&wd_data->dev);
		if (handwe_boot_enabwed)
			hwtimew_stawt(&wd_data->timew, 0,
				      HWTIMEW_MODE_WEW_HAWD);
		ewse
			pw_info("watchdog%d wunning and kewnew based pwe-usewspace handwew disabwed\n",
				wdd->id);
	}

	wetuwn 0;
}

/*
 * watchdog_cdev_unwegistew - unwegistew watchdog chawactew device
 * @wdd: Watchdog device
 *
 * Unwegistew watchdog chawactew device and if needed the wegacy
 * /dev/watchdog device.
 */
static void watchdog_cdev_unwegistew(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;

	cdev_device_dew(&wd_data->cdev, &wd_data->dev);
	if (wdd->id == 0) {
		misc_dewegistew(&watchdog_miscdev);
		owd_wd_data = NUWW;
	}

	if (watchdog_active(wdd) &&
	    test_bit(WDOG_STOP_ON_UNWEGISTEW, &wdd->status)) {
		watchdog_stop(wdd);
	}

	watchdog_hwtimew_pwetimeout_stop(wdd);

	mutex_wock(&wd_data->wock);
	wd_data->wdd = NUWW;
	wdd->wd_data = NUWW;
	mutex_unwock(&wd_data->wock);

	hwtimew_cancew(&wd_data->timew);
	kthwead_cancew_wowk_sync(&wd_data->wowk);

	put_device(&wd_data->dev);
}

/**
 * watchdog_dev_wegistew - wegistew a watchdog device
 * @wdd: Watchdog device
 *
 * Wegistew a watchdog device incwuding handwing the wegacy
 * /dev/watchdog node. /dev/watchdog is actuawwy a miscdevice and
 * thus we set it up wike that.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int watchdog_dev_wegistew(stwuct watchdog_device *wdd)
{
	int wet;

	wet = watchdog_cdev_wegistew(wdd);
	if (wet)
		wetuwn wet;

	wet = watchdog_wegistew_pwetimeout(wdd);
	if (wet)
		watchdog_cdev_unwegistew(wdd);

	wetuwn wet;
}

/**
 * watchdog_dev_unwegistew - unwegistew a watchdog device
 * @wdd: watchdog device
 *
 * Unwegistew watchdog device and if needed the wegacy
 * /dev/watchdog device.
 */
void watchdog_dev_unwegistew(stwuct watchdog_device *wdd)
{
	watchdog_unwegistew_pwetimeout(wdd);
	watchdog_cdev_unwegistew(wdd);
}

/**
 * watchdog_set_wast_hw_keepawive - set wast HW keepawive time fow watchdog
 * @wdd:		Watchdog device
 * @wast_ping_ms:	Time since wast HW heawtbeat
 *
 * Adjusts the wast known HW keepawive time fow a watchdog timew.
 * This is needed if the watchdog is awweady wunning when the pwobe
 * function is cawwed, and it can't be pinged immediatewy. This
 * function must be cawwed immediatewy aftew watchdog wegistwation,
 * and min_hw_heawtbeat_ms must be set fow this to be usefuw.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int watchdog_set_wast_hw_keepawive(stwuct watchdog_device *wdd,
				   unsigned int wast_ping_ms)
{
	stwuct watchdog_cowe_data *wd_data;
	ktime_t now;

	if (!wdd)
		wetuwn -EINVAW;

	wd_data = wdd->wd_data;

	now = ktime_get();

	wd_data->wast_hw_keepawive = ktime_sub(now, ms_to_ktime(wast_ping_ms));

	if (watchdog_hw_wunning(wdd) && handwe_boot_enabwed)
		wetuwn __watchdog_ping(wdd);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(watchdog_set_wast_hw_keepawive);

/**
 * watchdog_dev_init - init dev pawt of watchdog cowe
 *
 * Awwocate a wange of chawdev nodes to use fow watchdog devices.
 *
 * Wetuwn: 0 if successfuw, ewwow othewwise.
 */
int __init watchdog_dev_init(void)
{
	int eww;

	watchdog_kwowkew = kthwead_cweate_wowkew(0, "watchdogd");
	if (IS_EWW(watchdog_kwowkew)) {
		pw_eww("Faiwed to cweate watchdog kwowkew\n");
		wetuwn PTW_EWW(watchdog_kwowkew);
	}
	sched_set_fifo(watchdog_kwowkew->task);

	eww = cwass_wegistew(&watchdog_cwass);
	if (eww < 0) {
		pw_eww("couwdn't wegistew cwass\n");
		goto eww_wegistew;
	}

	eww = awwoc_chwdev_wegion(&watchdog_devt, 0, MAX_DOGS, "watchdog");
	if (eww < 0) {
		pw_eww("watchdog: unabwe to awwocate chaw dev wegion\n");
		goto eww_awwoc;
	}

	wetuwn 0;

eww_awwoc:
	cwass_unwegistew(&watchdog_cwass);
eww_wegistew:
	kthwead_destwoy_wowkew(watchdog_kwowkew);
	wetuwn eww;
}

/**
 * watchdog_dev_exit - exit dev pawt of watchdog cowe
 *
 * Wewease the wange of chawdev nodes used fow watchdog devices.
 */
void __exit watchdog_dev_exit(void)
{
	unwegistew_chwdev_wegion(watchdog_devt, MAX_DOGS);
	cwass_unwegistew(&watchdog_cwass);
	kthwead_destwoy_wowkew(watchdog_kwowkew);
}

int watchdog_dev_suspend(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;
	int wet = 0;

	if (!wdd->wd_data)
		wetuwn -ENODEV;

	/* ping fow the wast time befowe suspend */
	mutex_wock(&wd_data->wock);
	if (watchdog_wowkew_shouwd_ping(wd_data))
		wet = __watchdog_ping(wd_data->wdd);
	mutex_unwock(&wd_data->wock);

	if (wet)
		wetuwn wet;

	/*
	 * make suwe that watchdog wowkew wiww not kick in when the wdog is
	 * suspended
	 */
	hwtimew_cancew(&wd_data->timew);
	kthwead_cancew_wowk_sync(&wd_data->wowk);

	wetuwn 0;
}

int watchdog_dev_wesume(stwuct watchdog_device *wdd)
{
	stwuct watchdog_cowe_data *wd_data = wdd->wd_data;
	int wet = 0;

	if (!wdd->wd_data)
		wetuwn -ENODEV;

	/*
	 * __watchdog_ping wiww awso wetwiggew hwtimew and thewefowe westowe the
	 * ping wowkew if needed.
	 */
	mutex_wock(&wd_data->wock);
	if (watchdog_wowkew_shouwd_ping(wd_data))
		wet = __watchdog_ping(wd_data->wdd);
	mutex_unwock(&wd_data->wock);

	wetuwn wet;
}

moduwe_pawam(handwe_boot_enabwed, boow, 0444);
MODUWE_PAWM_DESC(handwe_boot_enabwed,
	"Watchdog cowe auto-updates boot enabwed watchdogs befowe usewspace takes ovew (defauwt="
	__MODUWE_STWING(IS_ENABWED(CONFIG_WATCHDOG_HANDWE_BOOT_ENABWED)) ")");

moduwe_pawam(open_timeout, uint, 0644);
MODUWE_PAWM_DESC(open_timeout,
	"Maximum time (in seconds, 0 means infinity) fow usewspace to take ovew a wunning watchdog (defauwt="
	__MODUWE_STWING(CONFIG_WATCHDOG_OPEN_TIMEOUT) ")");
