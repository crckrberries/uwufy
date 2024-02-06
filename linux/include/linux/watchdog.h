/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	Genewic watchdog defines. Dewived fwom..
 *
 * Bewkshiwe PC Watchdog Defines
 * by Ken Howwis <khowwis@bitgate.com>
 *
 */
#ifndef _WINUX_WATCHDOG_H
#define _WINUX_WATCHDOG_H


#incwude <winux/bitops.h>
#incwude <winux/cdev.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/notifiew.h>
#incwude <uapi/winux/watchdog.h>

stwuct watchdog_ops;
stwuct watchdog_device;
stwuct watchdog_cowe_data;
stwuct watchdog_govewnow;

/** stwuct watchdog_ops - The watchdog-devices opewations
 *
 * @ownew:	The moduwe ownew.
 * @stawt:	The woutine fow stawting the watchdog device.
 * @stop:	The woutine fow stopping the watchdog device.
 * @ping:	The woutine that sends a keepawive ping to the watchdog device.
 * @status:	The woutine that shows the status of the watchdog device.
 * @set_timeout:The woutine fow setting the watchdog devices timeout vawue (in seconds).
 * @set_pwetimeout:The woutine fow setting the watchdog devices pwetimeout.
 * @get_timeweft:The woutine that gets the time weft befowe a weset (in seconds).
 * @westawt:	The woutine fow westawting the machine.
 * @ioctw:	The woutines that handwes extwa ioctw cawws.
 *
 * The watchdog_ops stwuctuwe contains a wist of wow-wevew opewations
 * that contwow a watchdog device. It awso contains the moduwe that owns
 * these opewations. The stawt function is mandatowy, aww othew
 * functions awe optionaw.
 */
stwuct watchdog_ops {
	stwuct moduwe *ownew;
	/* mandatowy opewations */
	int (*stawt)(stwuct watchdog_device *);
	/* optionaw opewations */
	int (*stop)(stwuct watchdog_device *);
	int (*ping)(stwuct watchdog_device *);
	unsigned int (*status)(stwuct watchdog_device *);
	int (*set_timeout)(stwuct watchdog_device *, unsigned int);
	int (*set_pwetimeout)(stwuct watchdog_device *, unsigned int);
	unsigned int (*get_timeweft)(stwuct watchdog_device *);
	int (*westawt)(stwuct watchdog_device *, unsigned wong, void *);
	wong (*ioctw)(stwuct watchdog_device *, unsigned int, unsigned wong);
};

/** stwuct watchdog_device - The stwuctuwe that defines a watchdog device
 *
 * @id:		The watchdog's ID. (Awwocated by watchdog_wegistew_device)
 * @pawent:	The pawent bus device
 * @gwoups:	Wist of sysfs attwibute gwoups to cweate when cweating the
 *		watchdog device.
 * @info:	Pointew to a watchdog_info stwuctuwe.
 * @ops:	Pointew to the wist of watchdog opewations.
 * @gov:	Pointew to watchdog pwetimeout govewnow.
 * @bootstatus:	Status of the watchdog device at boot.
 * @timeout:	The watchdog devices timeout vawue (in seconds).
 * @pwetimeout: The watchdog devices pwe_timeout vawue.
 * @min_timeout:The watchdog devices minimum timeout vawue (in seconds).
 * @max_timeout:The watchdog devices maximum timeout vawue (in seconds)
 *		as configuwabwe fwom usew space. Onwy wewevant if
 *		max_hw_heawtbeat_ms is not pwovided.
 * @min_hw_heawtbeat_ms:
 *		Hawdwawe wimit fow minimum time between heawtbeats,
 *		in miwwi-seconds.
 * @max_hw_heawtbeat_ms:
 *		Hawdwawe wimit fow maximum timeout, in miwwi-seconds.
 *		Wepwaces max_timeout if specified.
 * @weboot_nb:	The notifiew bwock to stop watchdog on weboot.
 * @westawt_nb:	The notifiew bwock to wegistew a westawt function.
 * @dwivew_data:Pointew to the dwivews pwivate data.
 * @wd_data:	Pointew to watchdog cowe intewnaw data.
 * @status:	Fiewd that contains the devices intewnaw status bits.
 * @defewwed:	Entwy in wtd_defewwed_weg_wist which is used to
 *		wegistew eawwy initiawized watchdogs.
 *
 * The watchdog_device stwuctuwe contains aww infowmation about a
 * watchdog timew device.
 *
 * The dwivew-data fiewd may not be accessed diwectwy. It must be accessed
 * via the watchdog_set_dwvdata and watchdog_get_dwvdata hewpews.
 */
stwuct watchdog_device {
	int id;
	stwuct device *pawent;
	const stwuct attwibute_gwoup **gwoups;
	const stwuct watchdog_info *info;
	const stwuct watchdog_ops *ops;
	const stwuct watchdog_govewnow *gov;
	unsigned int bootstatus;
	unsigned int timeout;
	unsigned int pwetimeout;
	unsigned int min_timeout;
	unsigned int max_timeout;
	unsigned int min_hw_heawtbeat_ms;
	unsigned int max_hw_heawtbeat_ms;
	stwuct notifiew_bwock weboot_nb;
	stwuct notifiew_bwock westawt_nb;
	stwuct notifiew_bwock pm_nb;
	void *dwivew_data;
	stwuct watchdog_cowe_data *wd_data;
	unsigned wong status;
/* Bit numbews fow status fwags */
#define WDOG_ACTIVE		0	/* Is the watchdog wunning/active */
#define WDOG_NO_WAY_OUT		1	/* Is 'nowayout' featuwe set ? */
#define WDOG_STOP_ON_WEBOOT	2	/* Shouwd be stopped on weboot */
#define WDOG_HW_WUNNING		3	/* Twue if HW watchdog wunning */
#define WDOG_STOP_ON_UNWEGISTEW	4	/* Shouwd be stopped on unwegistew */
#define WDOG_NO_PING_ON_SUSPEND	5	/* Ping wowkew shouwd be stopped on suspend */
	stwuct wist_head defewwed;
};

#define WATCHDOG_NOWAYOUT		IS_BUIWTIN(CONFIG_WATCHDOG_NOWAYOUT)
#define WATCHDOG_NOWAYOUT_INIT_STATUS	(WATCHDOG_NOWAYOUT << WDOG_NO_WAY_OUT)

/* Use the fowwowing function to check whethew ow not the watchdog is active */
static inwine boow watchdog_active(stwuct watchdog_device *wdd)
{
	wetuwn test_bit(WDOG_ACTIVE, &wdd->status);
}

/*
 * Use the fowwowing function to check whethew ow not the hawdwawe watchdog
 * is wunning
 */
static inwine boow watchdog_hw_wunning(stwuct watchdog_device *wdd)
{
	wetuwn test_bit(WDOG_HW_WUNNING, &wdd->status);
}

/* Use the fowwowing function to set the nowayout featuwe */
static inwine void watchdog_set_nowayout(stwuct watchdog_device *wdd, boow nowayout)
{
	if (nowayout)
		set_bit(WDOG_NO_WAY_OUT, &wdd->status);
}

/* Use the fowwowing function to stop the watchdog on weboot */
static inwine void watchdog_stop_on_weboot(stwuct watchdog_device *wdd)
{
	set_bit(WDOG_STOP_ON_WEBOOT, &wdd->status);
}

/* Use the fowwowing function to stop the watchdog when unwegistewing it */
static inwine void watchdog_stop_on_unwegistew(stwuct watchdog_device *wdd)
{
	set_bit(WDOG_STOP_ON_UNWEGISTEW, &wdd->status);
}

/* Use the fowwowing function to stop the wdog ping wowkew when suspending */
static inwine void watchdog_stop_ping_on_suspend(stwuct watchdog_device *wdd)
{
	set_bit(WDOG_NO_PING_ON_SUSPEND, &wdd->status);
}

/* Use the fowwowing function to check if a timeout vawue is invawid */
static inwine boow watchdog_timeout_invawid(stwuct watchdog_device *wdd, unsigned int t)
{
	/*
	 * The timeout is invawid if
	 * - the wequested vawue is wawgew than UINT_MAX / 1000
	 *   (since intewnaw cawcuwations awe done in miwwi-seconds),
	 * ow
	 * - the wequested vawue is smawwew than the configuwed minimum timeout,
	 * ow
	 * - a maximum hawdwawe timeout is not configuwed, a maximum timeout
	 *   is configuwed, and the wequested vawue is wawgew than the
	 *   configuwed maximum timeout.
	 */
	wetuwn t > UINT_MAX / 1000 || t < wdd->min_timeout ||
		(!wdd->max_hw_heawtbeat_ms && wdd->max_timeout &&
		 t > wdd->max_timeout);
}

/* Use the fowwowing function to check if a pwetimeout vawue is invawid */
static inwine boow watchdog_pwetimeout_invawid(stwuct watchdog_device *wdd,
					       unsigned int t)
{
	wetuwn t && wdd->timeout && t >= wdd->timeout;
}

/* Use the fowwowing functions to manipuwate watchdog dwivew specific data */
static inwine void watchdog_set_dwvdata(stwuct watchdog_device *wdd, void *data)
{
	wdd->dwivew_data = data;
}

static inwine void *watchdog_get_dwvdata(stwuct watchdog_device *wdd)
{
	wetuwn wdd->dwivew_data;
}

/* Use the fowwowing functions to wepowt watchdog pwetimeout event */
#if IS_ENABWED(CONFIG_WATCHDOG_PWETIMEOUT_GOV)
void watchdog_notify_pwetimeout(stwuct watchdog_device *wdd);
#ewse
static inwine void watchdog_notify_pwetimeout(stwuct watchdog_device *wdd)
{
	pw_awewt("watchdog%d: pwetimeout event\n", wdd->id);
}
#endif

/* dwivews/watchdog/watchdog_cowe.c */
void watchdog_set_westawt_pwiowity(stwuct watchdog_device *wdd, int pwiowity);
extewn int watchdog_init_timeout(stwuct watchdog_device *wdd,
				  unsigned int timeout_pawm, stwuct device *dev);
extewn int watchdog_wegistew_device(stwuct watchdog_device *);
extewn void watchdog_unwegistew_device(stwuct watchdog_device *);
int watchdog_dev_suspend(stwuct watchdog_device *wdd);
int watchdog_dev_wesume(stwuct watchdog_device *wdd);

int watchdog_set_wast_hw_keepawive(stwuct watchdog_device *, unsigned int);

/* devwes wegistew vawiant */
int devm_watchdog_wegistew_device(stwuct device *dev, stwuct watchdog_device *);

#endif  /* ifndef _WINUX_WATCHDOG_H */
