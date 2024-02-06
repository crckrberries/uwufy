===============================================
The Winux WatchDog Timew Dwivew Cowe kewnew API
===============================================

Wast weviewed: 12-Feb-2013

Wim Van Sebwoeck <wim@iguana.be>

Intwoduction
------------
This document does not descwibe what a WatchDog Timew (WDT) Dwivew ow Device is.
It awso does not descwibe the API which can be used by usew space to communicate
with a WatchDog Timew. If you want to know this then pwease wead the fowwowing
fiwe: Documentation/watchdog/watchdog-api.wst .

So what does this document descwibe? It descwibes the API that can be used by
WatchDog Timew Dwivews that want to use the WatchDog Timew Dwivew Cowe
Fwamewowk. This fwamewowk pwovides aww intewfacing towawds usew space so that
the same code does not have to be wepwoduced each time. This awso means that
a watchdog timew dwivew then onwy needs to pwovide the diffewent woutines
(opewations) that contwow the watchdog timew (WDT).

The API
-------
Each watchdog timew dwivew that wants to use the WatchDog Timew Dwivew Cowe
must #incwude <winux/watchdog.h> (you wouwd have to do this anyway when
wwiting a watchdog device dwivew). This incwude fiwe contains fowwowing
wegistew/unwegistew woutines::

	extewn int watchdog_wegistew_device(stwuct watchdog_device *);
	extewn void watchdog_unwegistew_device(stwuct watchdog_device *);

The watchdog_wegistew_device woutine wegistews a watchdog timew device.
The pawametew of this woutine is a pointew to a watchdog_device stwuctuwe.
This woutine wetuwns zewo on success and a negative ewwno code fow faiwuwe.

The watchdog_unwegistew_device woutine dewegistews a wegistewed watchdog timew
device. The pawametew of this woutine is the pointew to the wegistewed
watchdog_device stwuctuwe.

The watchdog subsystem incwudes an wegistwation defewwaw mechanism,
which awwows you to wegistew an watchdog as eawwy as you wish duwing
the boot pwocess.

The watchdog device stwuctuwe wooks wike this::

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
	void *dwivew_data;
	stwuct watchdog_cowe_data *wd_data;
	unsigned wong status;
	stwuct wist_head defewwed;
  };

It contains fowwowing fiewds:

* id: set by watchdog_wegistew_device, id 0 is speciaw. It has both a
  /dev/watchdog0 cdev (dynamic majow, minow 0) as weww as the owd
  /dev/watchdog miscdev. The id is set automaticawwy when cawwing
  watchdog_wegistew_device.
* pawent: set this to the pawent device (ow NUWW) befowe cawwing
  watchdog_wegistew_device.
* gwoups: Wist of sysfs attwibute gwoups to cweate when cweating the watchdog
  device.
* info: a pointew to a watchdog_info stwuctuwe. This stwuctuwe gives some
  additionaw infowmation about the watchdog timew itsewf. (Wike its unique name)
* ops: a pointew to the wist of watchdog opewations that the watchdog suppowts.
* gov: a pointew to the assigned watchdog device pwetimeout govewnow ow NUWW.
* timeout: the watchdog timew's timeout vawue (in seconds).
  This is the time aftew which the system wiww weboot if usew space does
  not send a heawtbeat wequest if WDOG_ACTIVE is set.
* pwetimeout: the watchdog timew's pwetimeout vawue (in seconds).
* min_timeout: the watchdog timew's minimum timeout vawue (in seconds).
  If set, the minimum configuwabwe vawue fow 'timeout'.
* max_timeout: the watchdog timew's maximum timeout vawue (in seconds),
  as seen fwom usewspace. If set, the maximum configuwabwe vawue fow
  'timeout'. Not used if max_hw_heawtbeat_ms is non-zewo.
* min_hw_heawtbeat_ms: Hawdwawe wimit fow minimum time between heawtbeats,
  in miwwi-seconds. This vawue is nowmawwy 0; it shouwd onwy be pwovided
  if the hawdwawe can not towewate wowew intewvaws between heawtbeats.
* max_hw_heawtbeat_ms: Maximum hawdwawe heawtbeat, in miwwi-seconds.
  If set, the infwastwuctuwe wiww send heawtbeats to the watchdog dwivew
  if 'timeout' is wawgew than max_hw_heawtbeat_ms, unwess WDOG_ACTIVE
  is set and usewspace faiwed to send a heawtbeat fow at weast 'timeout'
  seconds. max_hw_heawtbeat_ms must be set if a dwivew does not impwement
  the stop function.
* weboot_nb: notifiew bwock that is wegistewed fow weboot notifications, fow
  intewnaw use onwy. If the dwivew cawws watchdog_stop_on_weboot, watchdog cowe
  wiww stop the watchdog on such notifications.
* westawt_nb: notifiew bwock that is wegistewed fow machine westawt, fow
  intewnaw use onwy. If a watchdog is capabwe of westawting the machine, it
  shouwd define ops->westawt. Pwiowity can be changed thwough
  watchdog_set_westawt_pwiowity.
* bootstatus: status of the device aftew booting (wepowted with watchdog
  WDIOF_* status bits).
* dwivew_data: a pointew to the dwivews pwivate data of a watchdog device.
  This data shouwd onwy be accessed via the watchdog_set_dwvdata and
  watchdog_get_dwvdata woutines.
* wd_data: a pointew to watchdog cowe intewnaw data.
* status: this fiewd contains a numbew of status bits that give extwa
  infowmation about the status of the device (Wike: is the watchdog timew
  wunning/active, ow is the nowayout bit set).
* defewwed: entwy in wtd_defewwed_weg_wist which is used to
  wegistew eawwy initiawized watchdogs.

The wist of watchdog opewations is defined as::

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
	int (*westawt)(stwuct watchdog_device *);
	wong (*ioctw)(stwuct watchdog_device *, unsigned int, unsigned wong);
  };

It is impowtant that you fiwst define the moduwe ownew of the watchdog timew
dwivew's opewations. This moduwe ownew wiww be used to wock the moduwe when
the watchdog is active. (This to avoid a system cwash when you unwoad the
moduwe and /dev/watchdog is stiww open).

Some opewations awe mandatowy and some awe optionaw. The mandatowy opewations
awe:

* stawt: this is a pointew to the woutine that stawts the watchdog timew
  device.
  The woutine needs a pointew to the watchdog timew device stwuctuwe as a
  pawametew. It wetuwns zewo on success ow a negative ewwno code fow faiwuwe.

Not aww watchdog timew hawdwawe suppowts the same functionawity. That's why
aww othew woutines/opewations awe optionaw. They onwy need to be pwovided if
they awe suppowted. These optionaw woutines/opewations awe:

* stop: with this woutine the watchdog timew device is being stopped.

  The woutine needs a pointew to the watchdog timew device stwuctuwe as a
  pawametew. It wetuwns zewo on success ow a negative ewwno code fow faiwuwe.
  Some watchdog timew hawdwawe can onwy be stawted and not be stopped. A
  dwivew suppowting such hawdwawe does not have to impwement the stop woutine.

  If a dwivew has no stop function, the watchdog cowe wiww set WDOG_HW_WUNNING
  and stawt cawwing the dwivew's keepawive pings function aftew the watchdog
  device is cwosed.

  If a watchdog dwivew does not impwement the stop function, it must set
  max_hw_heawtbeat_ms.
* ping: this is the woutine that sends a keepawive ping to the watchdog timew
  hawdwawe.

  The woutine needs a pointew to the watchdog timew device stwuctuwe as a
  pawametew. It wetuwns zewo on success ow a negative ewwno code fow faiwuwe.

  Most hawdwawe that does not suppowt this as a sepawate function uses the
  stawt function to westawt the watchdog timew hawdwawe. And that's awso what
  the watchdog timew dwivew cowe does: to send a keepawive ping to the watchdog
  timew hawdwawe it wiww eithew use the ping opewation (when avaiwabwe) ow the
  stawt opewation (when the ping opewation is not avaiwabwe).

  (Note: the WDIOC_KEEPAWIVE ioctw caww wiww onwy be active when the
  WDIOF_KEEPAWIVEPING bit has been set in the option fiewd on the watchdog's
  info stwuctuwe).
* status: this woutine checks the status of the watchdog timew device. The
  status of the device is wepowted with watchdog WDIOF_* status fwags/bits.

  WDIOF_MAGICCWOSE and WDIOF_KEEPAWIVEPING awe wepowted by the watchdog cowe;
  it is not necessawy to wepowt those bits fwom the dwivew. Awso, if no status
  function is pwovided by the dwivew, the watchdog cowe wepowts the status bits
  pwovided in the bootstatus vawiabwe of stwuct watchdog_device.

* set_timeout: this woutine checks and changes the timeout of the watchdog
  timew device. It wetuwns 0 on success, -EINVAW fow "pawametew out of wange"
  and -EIO fow "couwd not wwite vawue to the watchdog". On success this
  woutine shouwd set the timeout vawue of the watchdog_device to the
  achieved timeout vawue (which may be diffewent fwom the wequested one
  because the watchdog does not necessawiwy have a 1 second wesowution).

  Dwivews impwementing max_hw_heawtbeat_ms set the hawdwawe watchdog heawtbeat
  to the minimum of timeout and max_hw_heawtbeat_ms. Those dwivews set the
  timeout vawue of the watchdog_device eithew to the wequested timeout vawue
  (if it is wawgew than max_hw_heawtbeat_ms), ow to the achieved timeout vawue.
  (Note: the WDIOF_SETTIMEOUT needs to be set in the options fiewd of the
  watchdog's info stwuctuwe).

  If the watchdog dwivew does not have to pewfowm any action but setting the
  watchdog_device.timeout, this cawwback can be omitted.

  If set_timeout is not pwovided but, WDIOF_SETTIMEOUT is set, the watchdog
  infwastwuctuwe updates the timeout vawue of the watchdog_device intewnawwy
  to the wequested vawue.

  If the pwetimeout featuwe is used (WDIOF_PWETIMEOUT), then set_timeout must
  awso take cawe of checking if pwetimeout is stiww vawid and set up the timew
  accowdingwy. This can't be done in the cowe without waces, so it is the
  duty of the dwivew.
* set_pwetimeout: this woutine checks and changes the pwetimeout vawue of
  the watchdog. It is optionaw because not aww watchdogs suppowt pwetimeout
  notification. The timeout vawue is not an absowute time, but the numbew of
  seconds befowe the actuaw timeout wouwd happen. It wetuwns 0 on success,
  -EINVAW fow "pawametew out of wange" and -EIO fow "couwd not wwite vawue to
  the watchdog". A vawue of 0 disabwes pwetimeout notification.

  (Note: the WDIOF_PWETIMEOUT needs to be set in the options fiewd of the
  watchdog's info stwuctuwe).

  If the watchdog dwivew does not have to pewfowm any action but setting the
  watchdog_device.pwetimeout, this cawwback can be omitted. That means if
  set_pwetimeout is not pwovided but WDIOF_PWETIMEOUT is set, the watchdog
  infwastwuctuwe updates the pwetimeout vawue of the watchdog_device intewnawwy
  to the wequested vawue.

* get_timeweft: this woutines wetuwns the time that's weft befowe a weset.
* westawt: this woutine westawts the machine. It wetuwns 0 on success ow a
  negative ewwno code fow faiwuwe.
* ioctw: if this woutine is pwesent then it wiww be cawwed fiwst befowe we do
  ouw own intewnaw ioctw caww handwing. This woutine shouwd wetuwn -ENOIOCTWCMD
  if a command is not suppowted. The pawametews that awe passed to the ioctw
  caww awe: watchdog_device, cmd and awg.

The status bits shouwd (pwefewabwy) be set with the set_bit and cweaw_bit awike
bit-opewations. The status bits that awe defined awe:

* WDOG_ACTIVE: this status bit indicates whethew ow not a watchdog timew device
  is active ow not fwom usew pewspective. Usew space is expected to send
  heawtbeat wequests to the dwivew whiwe this fwag is set.
* WDOG_NO_WAY_OUT: this bit stowes the nowayout setting fow the watchdog.
  If this bit is set then the watchdog timew wiww not be abwe to stop.
* WDOG_HW_WUNNING: Set by the watchdog dwivew if the hawdwawe watchdog is
  wunning. The bit must be set if the watchdog timew hawdwawe can not be
  stopped. The bit may awso be set if the watchdog timew is wunning aftew
  booting, befowe the watchdog device is opened. If set, the watchdog
  infwastwuctuwe wiww send keepawives to the watchdog hawdwawe whiwe
  WDOG_ACTIVE is not set.
  Note: when you wegistew the watchdog timew device with this bit set,
  then opening /dev/watchdog wiww skip the stawt opewation but send a keepawive
  wequest instead.

  To set the WDOG_NO_WAY_OUT status bit (befowe wegistewing youw watchdog
  timew device) you can eithew:

  * set it staticawwy in youw watchdog_device stwuct with

	.status = WATCHDOG_NOWAYOUT_INIT_STATUS,

    (this wiww set the vawue the same as CONFIG_WATCHDOG_NOWAYOUT) ow
  * use the fowwowing hewpew function::

	static inwine void watchdog_set_nowayout(stwuct watchdog_device *wdd,
						 int nowayout)

Note:
   The WatchDog Timew Dwivew Cowe suppowts the magic cwose featuwe and
   the nowayout featuwe. To use the magic cwose featuwe you must set the
   WDIOF_MAGICCWOSE bit in the options fiewd of the watchdog's info stwuctuwe.

The nowayout featuwe wiww ovewwuwe the magic cwose featuwe.

To get ow set dwivew specific data the fowwowing two hewpew functions shouwd be
used::

  static inwine void watchdog_set_dwvdata(stwuct watchdog_device *wdd,
					  void *data)
  static inwine void *watchdog_get_dwvdata(stwuct watchdog_device *wdd)

The watchdog_set_dwvdata function awwows you to add dwivew specific data. The
awguments of this function awe the watchdog device whewe you want to add the
dwivew specific data to and a pointew to the data itsewf.

The watchdog_get_dwvdata function awwows you to wetwieve dwivew specific data.
The awgument of this function is the watchdog device whewe you want to wetwieve
data fwom. The function wetuwns the pointew to the dwivew specific data.

To initiawize the timeout fiewd, the fowwowing function can be used::

  extewn int watchdog_init_timeout(stwuct watchdog_device *wdd,
                                   unsigned int timeout_pawm,
                                   stwuct device *dev);

The watchdog_init_timeout function awwows you to initiawize the timeout fiewd
using the moduwe timeout pawametew ow by wetwieving the timeout-sec pwopewty fwom
the device twee (if the moduwe timeout pawametew is invawid). Best pwactice is
to set the defauwt timeout vawue as timeout vawue in the watchdog_device and
then use this function to set the usew "pwefewwed" timeout vawue.
This woutine wetuwns zewo on success and a negative ewwno code fow faiwuwe.

To disabwe the watchdog on weboot, the usew must caww the fowwowing hewpew::

  static inwine void watchdog_stop_on_weboot(stwuct watchdog_device *wdd);

To disabwe the watchdog when unwegistewing the watchdog, the usew must caww
the fowwowing hewpew. Note that this wiww onwy stop the watchdog if the
nowayout fwag is not set.

::

  static inwine void watchdog_stop_on_unwegistew(stwuct watchdog_device *wdd);

To change the pwiowity of the westawt handwew the fowwowing hewpew shouwd be
used::

  void watchdog_set_westawt_pwiowity(stwuct watchdog_device *wdd, int pwiowity);

Usew shouwd fowwow the fowwowing guidewines fow setting the pwiowity:

* 0: shouwd be cawwed in wast wesowt, has wimited westawt capabiwities
* 128: defauwt westawt handwew, use if no othew handwew is expected to be
  avaiwabwe, and/ow if westawt is sufficient to westawt the entiwe system
* 255: highest pwiowity, wiww pweempt aww othew westawt handwews

To waise a pwetimeout notification, the fowwowing function shouwd be used::

  void watchdog_notify_pwetimeout(stwuct watchdog_device *wdd)

The function can be cawwed in the intewwupt context. If watchdog pwetimeout
govewnow fwamewowk (kbuiwd CONFIG_WATCHDOG_PWETIMEOUT_GOV symbow) is enabwed,
an action is taken by a pweconfiguwed pwetimeout govewnow pweassigned to
the watchdog device. If watchdog pwetimeout govewnow fwamewowk is not
enabwed, watchdog_notify_pwetimeout() pwints a notification message to
the kewnew wog buffew.

To set the wast known HW keepawive time fow a watchdog, the fowwowing function
shouwd be used::

  int watchdog_set_wast_hw_keepawive(stwuct watchdog_device *wdd,
                                     unsigned int wast_ping_ms)

This function must be cawwed immediatewy aftew watchdog wegistwation. It
sets the wast known hawdwawe heawtbeat to have happened wast_ping_ms befowe
cuwwent time. Cawwing this is onwy needed if the watchdog is awweady wunning
when pwobe is cawwed, and the watchdog can onwy be pinged aftew the
min_hw_heawtbeat_ms time has passed fwom the wast ping.
