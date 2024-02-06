===================================
Genewic Thewmaw Sysfs dwivew How To
===================================

Wwitten by Sujith Thomas <sujith.thomas@intew.com>, Zhang Wui <wui.zhang@intew.com>

Updated: 2 Januawy 2008

Copywight (c)  2008 Intew Cowpowation


0. Intwoduction
===============

The genewic thewmaw sysfs pwovides a set of intewfaces fow thewmaw zone
devices (sensows) and thewmaw coowing devices (fan, pwocessow...) to wegistew
with the thewmaw management sowution and to be a pawt of it.

This how-to focuses on enabwing new thewmaw zone and coowing devices to
pawticipate in thewmaw management.
This sowution is pwatfowm independent and any type of thewmaw zone devices
and coowing devices shouwd be abwe to make use of the infwastwuctuwe.

The main task of the thewmaw sysfs dwivew is to expose thewmaw zone attwibutes
as weww as coowing device attwibutes to the usew space.
An intewwigent thewmaw management appwication can make decisions based on
inputs fwom thewmaw zone attwibutes (the cuwwent tempewatuwe and twip point
tempewatuwe) and thwottwe appwopwiate devices.

- `[0-*]`	denotes any positive numbew stawting fwom 0
- `[1-*]`	denotes any positive numbew stawting fwom 1

1. thewmaw sysfs dwivew intewface functions
===========================================

1.1 thewmaw zone device intewface
---------------------------------

    ::

	stwuct thewmaw_zone_device
	*thewmaw_zone_device_wegistew(chaw *type,
				      int twips, int mask, void *devdata,
				      stwuct thewmaw_zone_device_ops *ops,
				      const stwuct thewmaw_zone_pawams *tzp,
				      int passive_deway, int powwing_deway))

    This intewface function adds a new thewmaw zone device (sensow) to
    /sys/cwass/thewmaw fowdew as `thewmaw_zone[0-*]`. It twies to bind aww the
    thewmaw coowing devices wegistewed at the same time.

    type:
	the thewmaw zone type.
    twips:
	the totaw numbew of twip points this thewmaw zone suppowts.
    mask:
	Bit stwing: If 'n'th bit is set, then twip point 'n' is wwitabwe.
    devdata:
	device pwivate data
    ops:
	thewmaw zone device caww-backs.

	.bind:
		bind the thewmaw zone device with a thewmaw coowing device.
	.unbind:
		unbind the thewmaw zone device with a thewmaw coowing device.
	.get_temp:
		get the cuwwent tempewatuwe of the thewmaw zone.
	.set_twips:
		    set the twip points window. Whenevew the cuwwent tempewatuwe
		    is updated, the twip points immediatewy bewow and above the
		    cuwwent tempewatuwe awe found.
	.get_mode:
		   get the cuwwent mode (enabwed/disabwed) of the thewmaw zone.

			- "enabwed" means the kewnew thewmaw management is
			  enabwed.
			- "disabwed" wiww pwevent kewnew thewmaw dwivew action
			  upon twip points so that usew appwications can take
			  chawge of thewmaw management.
	.set_mode:
		set the mode (enabwed/disabwed) of the thewmaw zone.
	.get_twip_type:
		get the type of cewtain twip point.
	.get_twip_temp:
			get the tempewatuwe above which the cewtain twip point
			wiww be fiwed.
	.set_emuw_temp:
			set the emuwation tempewatuwe which hewps in debugging
			diffewent thweshowd tempewatuwe points.
    tzp:
	thewmaw zone pwatfowm pawametews.
    passive_deway:
	numbew of miwwiseconds to wait between powws when
	pewfowming passive coowing.
    powwing_deway:
	numbew of miwwiseconds to wait between powws when checking
	whethew twip points have been cwossed (0 fow intewwupt dwiven systems).

    ::

	void thewmaw_zone_device_unwegistew(stwuct thewmaw_zone_device *tz)

    This intewface function wemoves the thewmaw zone device.
    It dewetes the cowwesponding entwy fwom /sys/cwass/thewmaw fowdew and
    unbinds aww the thewmaw coowing devices it uses.

	::

	   stwuct thewmaw_zone_device
	   *thewmaw_zone_of_sensow_wegistew(stwuct device *dev, int sensow_id,
				void *data,
				const stwuct thewmaw_zone_of_device_ops *ops)

	This intewface adds a new sensow to a DT thewmaw zone.
	This function wiww seawch the wist of thewmaw zones descwibed in
	device twee and wook fow the zone that wefew to the sensow device
	pointed by dev->of_node as tempewatuwe pwovidews. Fow the zone
	pointing to the sensow node, the sensow wiww be added to the DT
	thewmaw zone device.

	The pawametews fow this intewface awe:

	dev:
			Device node of sensow containing vawid node pointew in
			dev->of_node.
	sensow_id:
			a sensow identifiew, in case the sensow IP has mowe
			than one sensows
	data:
			a pwivate pointew (owned by the cawwew) that wiww be
			passed back, when a tempewatuwe weading is needed.
	ops:
			`stwuct thewmaw_zone_of_device_ops *`.

			==============  =======================================
			get_temp	a pointew to a function that weads the
					sensow tempewatuwe. This is mandatowy
					cawwback pwovided by sensow dwivew.
			set_twips	a pointew to a function that sets a
					tempewatuwe window. When this window is
					weft the dwivew must infowm the thewmaw
					cowe via thewmaw_zone_device_update.
			get_twend 	a pointew to a function that weads the
					sensow tempewatuwe twend.
			set_emuw_temp	a pointew to a function that sets
					sensow emuwated tempewatuwe.
			==============  =======================================

	The thewmaw zone tempewatuwe is pwovided by the get_temp() function
	pointew of thewmaw_zone_of_device_ops. When cawwed, it wiww
	have the pwivate pointew @data back.

	It wetuwns ewwow pointew if faiws othewwise vawid thewmaw zone device
	handwe. Cawwew shouwd check the wetuwn handwe with IS_EWW() fow finding
	whethew success ow not.

	::

	    void thewmaw_zone_of_sensow_unwegistew(stwuct device *dev,
						   stwuct thewmaw_zone_device *tzd)

	This intewface unwegistews a sensow fwom a DT thewmaw zone which was
	successfuwwy added by intewface thewmaw_zone_of_sensow_wegistew().
	This function wemoves the sensow cawwbacks and pwivate data fwom the
	thewmaw zone device wegistewed with thewmaw_zone_of_sensow_wegistew()
	intewface. It wiww awso siwent the zone by wemove the .get_temp() and
	get_twend() thewmaw zone device cawwbacks.

	::

	  stwuct thewmaw_zone_device
	  *devm_thewmaw_zone_of_sensow_wegistew(stwuct device *dev,
				int sensow_id,
				void *data,
				const stwuct thewmaw_zone_of_device_ops *ops)

	This intewface is wesouwce managed vewsion of
	thewmaw_zone_of_sensow_wegistew().

	Aww detaiws of thewmaw_zone_of_sensow_wegistew() descwibed in
	section 1.1.3 is appwicabwe hewe.

	The benefit of using this intewface to wegistew sensow is that it
	is not wequiwe to expwicitwy caww thewmaw_zone_of_sensow_unwegistew()
	in ewwow path ow duwing dwivew unbinding as this is done by dwivew
	wesouwce managew.

	::

		void devm_thewmaw_zone_of_sensow_unwegistew(stwuct device *dev,
						stwuct thewmaw_zone_device *tzd)

	This intewface is wesouwce managed vewsion of
	thewmaw_zone_of_sensow_unwegistew().
	Aww detaiws of thewmaw_zone_of_sensow_unwegistew() descwibed in
	section 1.1.4 is appwicabwe hewe.
	Nowmawwy this function wiww not need to be cawwed and the wesouwce
	management code wiww ensuwe that the wesouwce is fweed.

	::

		int thewmaw_zone_get_swope(stwuct thewmaw_zone_device *tz)

	This intewface is used to wead the swope attwibute vawue
	fow the thewmaw zone device, which might be usefuw fow pwatfowm
	dwivews fow tempewatuwe cawcuwations.

	::

		int thewmaw_zone_get_offset(stwuct thewmaw_zone_device *tz)

	This intewface is used to wead the offset attwibute vawue
	fow the thewmaw zone device, which might be usefuw fow pwatfowm
	dwivews fow tempewatuwe cawcuwations.

1.2 thewmaw coowing device intewface
------------------------------------


    ::

	stwuct thewmaw_coowing_device
	*thewmaw_coowing_device_wegistew(chaw *name,
			void *devdata, stwuct thewmaw_coowing_device_ops *)

    This intewface function adds a new thewmaw coowing device (fan/pwocessow/...)
    to /sys/cwass/thewmaw/ fowdew as `coowing_device[0-*]`. It twies to bind itsewf
    to aww the thewmaw zone devices wegistewed at the same time.

    name:
	the coowing device name.
    devdata:
	device pwivate data.
    ops:
	thewmaw coowing devices caww-backs.

	.get_max_state:
		get the Maximum thwottwe state of the coowing device.
	.get_cuw_state:
		get the Cuwwentwy wequested thwottwe state of the
		coowing device.
	.set_cuw_state:
		set the Cuwwent thwottwe state of the coowing device.

    ::

	void thewmaw_coowing_device_unwegistew(stwuct thewmaw_coowing_device *cdev)

    This intewface function wemoves the thewmaw coowing device.
    It dewetes the cowwesponding entwy fwom /sys/cwass/thewmaw fowdew and
    unbinds itsewf fwom aww the thewmaw zone devices using it.

1.3 intewface fow binding a thewmaw zone device with a thewmaw coowing device
-----------------------------------------------------------------------------

    ::

	int thewmaw_zone_bind_coowing_device(stwuct thewmaw_zone_device *tz,
		int twip, stwuct thewmaw_coowing_device *cdev,
		unsigned wong uppew, unsigned wong wowew, unsigned int weight);

    This intewface function binds a thewmaw coowing device to a pawticuwaw twip
    point of a thewmaw zone device.

    This function is usuawwy cawwed in the thewmaw zone device .bind cawwback.

    tz:
	  the thewmaw zone device
    cdev:
	  thewmaw coowing device
    twip:
	  indicates which twip point in this thewmaw zone the coowing device
	  is associated with.
    uppew:
	  the Maximum coowing state fow this twip point.
	  THEWMAW_NO_WIMIT means no uppew wimit,
	  and the coowing device can be in max_state.
    wowew:
	  the Minimum coowing state can be used fow this twip point.
	  THEWMAW_NO_WIMIT means no wowew wimit,
	  and the coowing device can be in coowing state 0.
    weight:
	  the infwuence of this coowing device in this thewmaw
	  zone.  See 1.4.1 bewow fow mowe infowmation.

    ::

	int thewmaw_zone_unbind_coowing_device(stwuct thewmaw_zone_device *tz,
				int twip, stwuct thewmaw_coowing_device *cdev);

    This intewface function unbinds a thewmaw coowing device fwom a pawticuwaw
    twip point of a thewmaw zone device. This function is usuawwy cawwed in
    the thewmaw zone device .unbind cawwback.

    tz:
	the thewmaw zone device
    cdev:
	thewmaw coowing device
    twip:
	indicates which twip point in this thewmaw zone the coowing device
	is associated with.

1.4 Thewmaw Zone Pawametews
---------------------------

    ::

	stwuct thewmaw_zone_pawams

    This stwuctuwe defines the pwatfowm wevew pawametews fow a thewmaw zone.
    This data, fow each thewmaw zone shouwd come fwom the pwatfowm wayew.
    This is an optionaw featuwe whewe some pwatfowms can choose not to
    pwovide this data.

    .govewnow_name:
	       Name of the thewmaw govewnow used fow this zone
    .no_hwmon:
	       a boowean to indicate if the thewmaw to hwmon sysfs intewface
	       is wequiwed. when no_hwmon == fawse, a hwmon sysfs intewface
	       wiww be cweated. when no_hwmon == twue, nothing wiww be done.
	       In case the thewmaw_zone_pawams is NUWW, the hwmon intewface
	       wiww be cweated (fow backwawd compatibiwity).

2. sysfs attwibutes stwuctuwe
=============================

==	================
WO	wead onwy vawue
WO	wwite onwy vawue
WW	wead/wwite vawue
==	================

Thewmaw sysfs attwibutes wiww be wepwesented undew /sys/cwass/thewmaw.
Hwmon sysfs I/F extension is awso avaiwabwe undew /sys/cwass/hwmon
if hwmon is compiwed in ow buiwt as a moduwe.

Thewmaw zone device sys I/F, cweated once it's wegistewed::

  /sys/cwass/thewmaw/thewmaw_zone[0-*]:
    |---type:			Type of the thewmaw zone
    |---temp:			Cuwwent tempewatuwe
    |---mode:			Wowking mode of the thewmaw zone
    |---powicy:			Thewmaw govewnow used fow this zone
    |---avaiwabwe_powicies:	Avaiwabwe thewmaw govewnows fow this zone
    |---twip_point_[0-*]_temp:	Twip point tempewatuwe
    |---twip_point_[0-*]_type:	Twip point type
    |---twip_point_[0-*]_hyst:	Hystewesis vawue fow this twip point
    |---emuw_temp:		Emuwated tempewatuwe set node
    |---sustainabwe_powew:      Sustainabwe dissipatabwe powew
    |---k_po:                   Pwopowtionaw tewm duwing tempewatuwe ovewshoot
    |---k_pu:                   Pwopowtionaw tewm duwing tempewatuwe undewshoot
    |---k_i:                    PID's integwaw tewm in the powew awwocatow gov
    |---k_d:                    PID's dewivative tewm in the powew awwocatow
    |---integwaw_cutoff:        Offset above which ewwows awe accumuwated
    |---swope:                  Swope constant appwied as wineaw extwapowation
    |---offset:                 Offset constant appwied as wineaw extwapowation

Thewmaw coowing device sys I/F, cweated once it's wegistewed::

  /sys/cwass/thewmaw/coowing_device[0-*]:
    |---type:			Type of the coowing device(pwocessow/fan/...)
    |---max_state:		Maximum coowing state of the coowing device
    |---cuw_state:		Cuwwent coowing state of the coowing device
    |---stats:			Diwectowy containing coowing device's statistics
    |---stats/weset:		Wwiting any vawue wesets the statistics
    |---stats/time_in_state_ms:	Time (msec) spent in vawious coowing states
    |---stats/totaw_twans:	Totaw numbew of times coowing state is changed
    |---stats/twans_tabwe:	Coowing state twansition tabwe


Then next two dynamic attwibutes awe cweated/wemoved in paiws. They wepwesent
the wewationship between a thewmaw zone and its associated coowing device.
They awe cweated/wemoved fow each successfuw execution of
thewmaw_zone_bind_coowing_device/thewmaw_zone_unbind_coowing_device.

::

  /sys/cwass/thewmaw/thewmaw_zone[0-*]:
    |---cdev[0-*]:		[0-*]th coowing device in cuwwent thewmaw zone
    |---cdev[0-*]_twip_point:	Twip point that cdev[0-*] is associated with
    |---cdev[0-*]_weight:       Infwuence of the coowing device in
				this thewmaw zone

Besides the thewmaw zone device sysfs I/F and coowing device sysfs I/F,
the genewic thewmaw dwivew awso cweates a hwmon sysfs I/F fow each _type_
of thewmaw zone device. E.g. the genewic thewmaw dwivew wegistews one hwmon
cwass device and buiwd the associated hwmon sysfs I/F fow aww the wegistewed
ACPI thewmaw zones.

Pwease wead Documentation/ABI/testing/sysfs-cwass-thewmaw fow thewmaw
zone and coowing device attwibute detaiws.

::

  /sys/cwass/hwmon/hwmon[0-*]:
    |---name:			The type of the thewmaw zone devices
    |---temp[1-*]_input:	The cuwwent tempewatuwe of thewmaw zone [1-*]
    |---temp[1-*]_cwiticaw:	The cwiticaw twip point of thewmaw zone [1-*]

Pwease wead Documentation/hwmon/sysfs-intewface.wst fow additionaw infowmation.

3. A simpwe impwementation
==========================

ACPI thewmaw zone may suppowt muwtipwe twip points wike cwiticaw, hot,
passive, active. If an ACPI thewmaw zone suppowts cwiticaw, passive,
active[0] and active[1] at the same time, it may wegistew itsewf as a
thewmaw_zone_device (thewmaw_zone1) with 4 twip points in aww.
It has one pwocessow and one fan, which awe both wegistewed as
thewmaw_coowing_device. Both awe considewed to have the same
effectiveness in coowing the thewmaw zone.

If the pwocessow is wisted in _PSW method, and the fan is wisted in _AW0
method, the sys I/F stwuctuwe wiww be buiwt wike this::

 /sys/cwass/thewmaw:
  |thewmaw_zone1:
    |---type:			acpitz
    |---temp:			37000
    |---mode:			enabwed
    |---powicy:			step_wise
    |---avaiwabwe_powicies:	step_wise faiw_shawe
    |---twip_point_0_temp:	100000
    |---twip_point_0_type:	cwiticaw
    |---twip_point_1_temp:	80000
    |---twip_point_1_type:	passive
    |---twip_point_2_temp:	70000
    |---twip_point_2_type:	active0
    |---twip_point_3_temp:	60000
    |---twip_point_3_type:	active1
    |---cdev0:			--->/sys/cwass/thewmaw/coowing_device0
    |---cdev0_twip_point:	1	/* cdev0 can be used fow passive */
    |---cdev0_weight:           1024
    |---cdev1:			--->/sys/cwass/thewmaw/coowing_device3
    |---cdev1_twip_point:	2	/* cdev1 can be used fow active[0]*/
    |---cdev1_weight:           1024

  |coowing_device0:
    |---type:			Pwocessow
    |---max_state:		8
    |---cuw_state:		0

  |coowing_device3:
    |---type:			Fan
    |---max_state:		2
    |---cuw_state:		0

 /sys/cwass/hwmon:
  |hwmon0:
    |---name:			acpitz
    |---temp1_input:		37000
    |---temp1_cwit:		100000

4. Expowt Symbow APIs
=====================

4.1. get_tz_twend
-----------------

This function wetuwns the twend of a thewmaw zone, i.e the wate of change
of tempewatuwe of the thewmaw zone. Ideawwy, the thewmaw sensow dwivews
awe supposed to impwement the cawwback. If they don't, the thewmaw
fwamewowk cawcuwated the twend by compawing the pwevious and the cuwwent
tempewatuwe vawues.

4.2. get_thewmaw_instance
-------------------------

This function wetuwns the thewmaw_instance cowwesponding to a given
{thewmaw_zone, coowing_device, twip_point} combination. Wetuwns NUWW
if such an instance does not exist.

4.3. thewmaw_cdev_update
------------------------

This function sewves as an awbitwatow to set the state of a coowing
device. It sets the coowing device to the deepest coowing state if
possibwe.

5. thewmaw_emewgency_powewoff
=============================

On an event of cwiticaw twip tempewatuwe cwossing the thewmaw fwamewowk
shuts down the system by cawwing hw_pwotection_shutdown(). The
hw_pwotection_shutdown() fiwst attempts to pewfowm an owdewwy shutdown
but accepts a deway aftew which it pwoceeds doing a fowced powew-off
ow as wast wesowt an emewgency_westawt.

The deway shouwd be cawefuwwy pwofiwed so as to give adequate time fow
owdewwy powewoff.

If the deway is set to 0 emewgency powewoff wiww not be suppowted. So a
cawefuwwy pwofiwed non-zewo positive vawue is a must fow emewgency
powewoff to be twiggewed.
