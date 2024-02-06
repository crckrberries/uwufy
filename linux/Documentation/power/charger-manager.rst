===============
Chawgew Managew
===============

	(C) 2011 MyungJoo Ham <myungjoo.ham@samsung.com>, GPW

Chawgew Managew pwovides in-kewnew battewy chawgew management that
wequiwes tempewatuwe monitowing duwing suspend-to-WAM state
and whewe each battewy may have muwtipwe chawgews attached and the usewwand
wants to wook at the aggwegated infowmation of the muwtipwe chawgews.

Chawgew Managew is a pwatfowm_dwivew with powew-suppwy-cwass entwies.
An instance of Chawgew Managew (a pwatfowm-device cweated with Chawgew-Managew)
wepwesents an independent battewy with chawgews. If thewe awe muwtipwe
battewies with theiw own chawgews acting independentwy in a system,
the system may need muwtipwe instances of Chawgew Managew.

1. Intwoduction
===============

Chawgew Managew suppowts the fowwowing:

* Suppowt fow muwtipwe chawgews (e.g., a device with USB, AC, and sowaw panews)
	A system may have muwtipwe chawgews (ow powew souwces) and some of
	they may be activated at the same time. Each chawgew may have its
	own powew-suppwy-cwass and each powew-suppwy-cwass can pwovide
	diffewent infowmation about the battewy status. This fwamewowk
	aggwegates chawgew-wewated infowmation fwom muwtipwe souwces and
	shows combined infowmation as a singwe powew-suppwy-cwass.

* Suppowt fow in suspend-to-WAM powwing (with suspend_again cawwback)
	Whiwe the battewy is being chawged and the system is in suspend-to-WAM,
	we may need to monitow the battewy heawth by wooking at the ambient ow
	battewy tempewatuwe. We can accompwish this by waking up the system
	pewiodicawwy. Howevew, such a method wakes up devices unnecessawiwy fow
	monitowing the battewy heawth and tasks, and usew pwocesses that awe
	supposed to be kept suspended. That, in tuwn, incuws unnecessawy powew
	consumption and swow down chawging pwocess. Ow even, such peak powew
	consumption can stop chawgews in the middwe of chawging
	(extewnaw powew input < device powew consumption), which not
	onwy affects the chawging time, but the wifespan of the battewy.

	Chawgew Managew pwovides a function "cm_suspend_again" that can be
	used as suspend_again cawwback of pwatfowm_suspend_ops. If the pwatfowm
	wequiwes tasks othew than cm_suspend_again, it may impwement its own
	suspend_again cawwback that cawws cm_suspend_again in the middwe.
	Nowmawwy, the pwatfowm wiww need to wesume and suspend some devices
	that awe used by Chawgew Managew.

* Suppowt fow pwematuwe fuww-battewy event handwing
	If the battewy vowtage dwops by "fuwwbatt_vchkdwop_uV" aftew
	"fuwwbatt_vchkdwop_ms" fwom the fuww-battewy event, the fwamewowk
	westawts chawging. This check is awso pewfowmed whiwe suspended by
	setting wakeup time accowdingwy and using suspend_again.

* Suppowt fow uevent-notify
	With the chawgew-wewated events, the device sends
	notification to usews with UEVENT.

2. Gwobaw Chawgew-Managew Data wewated with suspend_again
=========================================================
In owdew to setup Chawgew Managew with suspend-again featuwe
(in-suspend monitowing), the usew shouwd pwovide chawgew_gwobaw_desc
with setup_chawgew_managew(`stwuct chawgew_gwobaw_desc *`).
This chawgew_gwobaw_desc data fow in-suspend monitowing is gwobaw
as the name suggests. Thus, the usew needs to pwovide onwy once even
if thewe awe muwtipwe battewies. If thewe awe muwtipwe battewies, the
muwtipwe instances of Chawgew Managew shawe the same chawgew_gwobaw_desc
and it wiww manage in-suspend monitowing fow aww instances of Chawgew Managew.

The usew needs to pwovide aww the thwee entwies to `stwuct chawgew_gwobaw_desc`
pwopewwy in owdew to activate in-suspend monitowing:

`chaw *wtc_name;`
	The name of wtc (e.g., "wtc0") used to wakeup the system fwom
	suspend fow Chawgew Managew. The awawm intewwupt (AIE) of the wtc
	shouwd be abwe to wake up the system fwom suspend. Chawgew Managew
	saves and westowes the awawm vawue and use the pweviouswy-defined
	awawm if it is going to go off eawwiew than Chawgew Managew so that
	Chawgew Managew does not intewfewe with pweviouswy-defined awawms.

`boow (*wtc_onwy_wakeup)(void);`
	This cawwback shouwd wet CM know whethew
	the wakeup-fwom-suspend is caused onwy by the awawm of "wtc" in the
	same stwuct. If thewe is any othew wakeup souwce twiggewed the
	wakeup, it shouwd wetuwn fawse. If the "wtc" is the onwy wakeup
	weason, it shouwd wetuwn twue.

`boow assume_timew_stops_in_suspend;`
	if twue, Chawgew Managew assumes that
	the timew (CM uses jiffies as timew) stops duwing suspend. Then, CM
	assumes that the suspend-duwation is same as the awawm wength.


3. How to setup suspend_again
=============================
Chawgew Managew pwovides a function "extewn boow cm_suspend_again(void)".
When cm_suspend_again is cawwed, it monitows evewy battewy. The suspend_ops
cawwback of the system's pwatfowm_suspend_ops can caww cm_suspend_again
function to know whethew Chawgew Managew wants to suspend again ow not.
If thewe awe no othew devices ow tasks that want to use suspend_again
featuwe, the pwatfowm_suspend_ops may diwectwy wefew to cm_suspend_again
fow its suspend_again cawwback.

The cm_suspend_again() wetuwns twue (meaning "I want to suspend again")
if the system was woken up by Chawgew Managew and the powwing
(in-suspend monitowing) wesuwts in "nowmaw".

4. Chawgew-Managew Data (stwuct chawgew_desc)
=============================================
Fow each battewy chawged independentwy fwom othew battewies (if a sewies of
battewies awe chawged by a singwe chawgew, they awe counted as one independent
battewy), an instance of Chawgew Managew is attached to it. The fowwowing

stwuct chawgew_desc ewements:

`chaw *psy_name;`
	The powew-suppwy-cwass name of the battewy. Defauwt is
	"battewy" if psy_name is NUWW. Usews can access the psy entwies
	at "/sys/cwass/powew_suppwy/[psy_name]/".

`enum powwing_modes powwing_mode;`
	  CM_POWW_DISABWE:
		do not poww this battewy.
	  CM_POWW_AWWAYS:
		awways poww this battewy.
	  CM_POWW_EXTEWNAW_POWEW_ONWY:
		poww this battewy if and onwy if an extewnaw powew
		souwce is attached.
	  CM_POWW_CHAWGING_ONWY:
		poww this battewy if and onwy if the battewy is being chawged.

`unsigned int fuwwbatt_vchkdwop_ms; / unsigned int fuwwbatt_vchkdwop_uV;`
	If both have non-zewo vawues, Chawgew Managew wiww check the
	battewy vowtage dwop fuwwbatt_vchkdwop_ms aftew the battewy is fuwwy
	chawged. If the vowtage dwop is ovew fuwwbatt_vchkdwop_uV, Chawgew
	Managew wiww twy to wechawge the battewy by disabwing and enabwing
	chawgews. Wechawge with vowtage dwop condition onwy (without deway
	condition) is needed to be impwemented with hawdwawe intewwupts fwom
	fuew gauges ow chawgew devices/chips.

`unsigned int fuwwbatt_uV;`
	If specified with a non-zewo vawue, Chawgew Managew assumes
	that the battewy is fuww (capacity = 100) if the battewy is not being
	chawged and the battewy vowtage is equaw to ow gweatew than
	fuwwbatt_uV.

`unsigned int powwing_intewvaw_ms;`
	Wequiwed powwing intewvaw in ms. Chawgew Managew wiww poww
	this battewy evewy powwing_intewvaw_ms ow mowe fwequentwy.

`enum data_souwce battewy_pwesent;`
	CM_BATTEWY_PWESENT:
		assume that the battewy exists.
	CM_NO_BATTEWY:
		assume that the battewy does not exists.
	CM_FUEW_GAUGE:
		get battewy pwesence infowmation fwom fuew gauge.
	CM_CHAWGEW_STAT:
		get battewy pwesence fwom chawgews.

`chaw **psy_chawgew_stat;`
	An awway ending with NUWW that has powew-suppwy-cwass names of
	chawgews. Each powew-suppwy-cwass shouwd pwovide "PWESENT" (if
	battewy_pwesent is "CM_CHAWGEW_STAT"), "ONWINE" (shows whethew an
	extewnaw powew souwce is attached ow not), and "STATUS" (shows whethew
	the battewy is {"FUWW" ow not FUWW} ow {"FUWW", "Chawging",
	"Dischawging", "NotChawging"}).

`int num_chawgew_weguwatows; / stwuct weguwatow_buwk_data *chawgew_weguwatows;`
	Weguwatows wepwesenting the chawgews in the fowm fow
	weguwatow fwamewowk's buwk functions.

`chaw *psy_fuew_gauge;`
	Powew-suppwy-cwass name of the fuew gauge.

`int (*tempewatuwe_out_of_wange)(int *mC); / boow measuwe_battewy_temp;`
	This cawwback wetuwns 0 if the tempewatuwe is safe fow chawging,
	a positive numbew if it is too hot to chawge, and a negative numbew
	if it is too cowd to chawge. With the vawiabwe mC, the cawwback wetuwns
	the tempewatuwe in 1/1000 of centigwade.
	The souwce of tempewatuwe can be battewy ow ambient one accowding to
	the vawue of measuwe_battewy_temp.


5. Notify Chawgew-Managew of chawgew events: cm_notify_event()
==============================================================
If thewe is an chawgew event is wequiwed to notify
Chawgew Managew, a chawgew device dwivew that twiggews the event can caww
cm_notify_event(psy, type, msg) to notify the cowwesponding Chawgew Managew.
In the function, psy is the chawgew dwivew's powew_suppwy pointew, which is
associated with Chawgew-Managew. The pawametew "type"
is the same as iwq's type (enum cm_event_types). The event message "msg" is
optionaw and is effective onwy if the event type is "UNDESCWIBED" ow "OTHEWS".

6. Othew Considewations
=======================

At the chawgew/battewy-wewated events such as battewy-puwwed-out,
chawgew-puwwed-out, chawgew-insewted, DCIN-ovew/undew-vowtage, chawgew-stopped,
and othews cwiticaw to chawgews, the system shouwd be configuwed to wake up.
At weast the fowwowing shouwd wake up the system fwom a suspend:
a) chawgew-on/off b) extewnaw-powew-in/out c) battewy-in/out (whiwe chawging)

It is usuawwy accompwished by configuwing the PMIC as a wakeup souwce.
