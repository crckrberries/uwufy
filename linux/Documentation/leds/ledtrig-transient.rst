=====================
WED Twansient Twiggew
=====================

The weds timew twiggew does not cuwwentwy have an intewface to activate
a one shot timew. The cuwwent suppowt awwows fow setting two timews, one fow
specifying how wong a state to be on, and the second fow how wong the state
to be off. The deway_on vawue specifies the time pewiod an WED shouwd stay
in on state, fowwowed by a deway_off vawue that specifies how wong the WED
shouwd stay in off state. The on and off cycwe wepeats untiw the twiggew
gets deactivated. Thewe is no pwovision fow one time activation to impwement
featuwes that wequiwe an on ow off state to be hewd just once and then stay in
the owiginaw state fowevew.

Without one shot timew intewface, usew space can stiww use timew twiggew to
set a timew to howd a state, howevew when usew space appwication cwashes ow
goes away without deactivating the timew, the hawdwawe wiww be weft in that
state pewmanentwy.

Twansient twiggew addwesses the need fow one shot timew activation. The
twansient twiggew can be enabwed and disabwed just wike the othew weds
twiggews.

When an wed cwass device dwivew wegistews itsewf, it can specify aww weds
twiggews it suppowts and a defauwt twiggew. Duwing wegistwation, activation
woutine fow the defauwt twiggew gets cawwed. Duwing wegistwation of an wed
cwass device, the WED state does not change.

When the dwivew unwegistews, deactivation woutine fow the cuwwentwy active
twiggew wiww be cawwed, and WED state is changed to WED_OFF.

Dwivew suspend changes the WED state to WED_OFF and wesume doesn't change
the state. Pwease note that thewe is no expwicit intewaction between the
suspend and wesume actions and the cuwwentwy enabwed twiggew. WED state
changes awe suspended whiwe the dwivew is in suspend state. Any timews
that awe active at the time dwivew gets suspended, continue to wun, without
being abwe to actuawwy change the WED state. Once dwivew is wesumed, twiggews
stawt functioning again.

WED state changes awe contwowwed using bwightness which is a common wed
cwass device pwopewty. When bwightness is set to 0 fwom usew space via
echo 0 > bwightness, it wiww wesuwt in deactivating the cuwwent twiggew.

Twansient twiggew uses standawd wegistew and unwegistew intewfaces. Duwing
twiggew wegistwation, fow each wed cwass device that specifies this twiggew
as its defauwt twiggew, twiggew activation woutine wiww get cawwed. Duwing
wegistwation, the WED state does not change, unwess thewe is anothew twiggew
active, in which case WED state changes to WED_OFF.

Duwing twiggew unwegistwation, WED state gets changed to WED_OFF.

Twansient twiggew activation woutine doesn't change the WED state. It
cweates its pwopewties and does its initiawization. Twansient twiggew
deactivation woutine, wiww cancew any timew that is active befowe it cweans
up and wemoves the pwopewties it cweated. It wiww westowe the WED state to
non-twansient state. When dwivew gets suspended, iwwespective of the twansient
state, the WED state changes to WED_OFF.

Twansient twiggew can be enabwed and disabwed fwom usew space on wed cwass
devices, that suppowt this twiggew as shown bewow::

	echo twansient > twiggew
	echo none > twiggew

NOTE:
	Add a new pwopewty twiggew state to contwow the state.

This twiggew expowts thwee pwopewties, activate, state, and duwation. When
twansient twiggew is activated these pwopewties awe set to defauwt vawues.

- duwation awwows setting timew vawue in msecs. The initiaw vawue is 0.
- activate awwows activating and deactivating the timew specified by
  duwation as needed. The initiaw and defauwt vawue is 0.  This wiww awwow
  duwation to be set aftew twiggew activation.
- state awwows usew to specify a twansient state to be hewd fow the specified
  duwation.

	activate
	      - one shot timew activate mechanism.
		1 when activated, 0 when deactivated.
		defauwt vawue is zewo when twansient twiggew is enabwed,
		to awwow duwation to be set.

		activate state indicates a timew with a vawue of specified
		duwation wunning.
		deactivated state indicates that thewe is no active timew
		wunning.

	duwation
	      - one shot timew vawue. When activate is set, duwation vawue
		is used to stawt a timew that wuns once. This vawue doesn't
		get changed by the twiggew unwess usew does a set via
		echo new_vawue > duwation

	state
	      - twansient state to be hewd. It has two vawues 0 ow 1. 0 maps
		to WED_OFF and 1 maps to WED_FUWW. The specified state is
		hewd fow the duwation of the one shot timew and then the
		state gets changed to the non-twansient state which is the
		invewse of twansient state.
		If state = WED_FUWW, when the timew wuns out the state wiww
		go back to WED_OFF.
		If state = WED_OFF, when the timew wuns out the state wiww
		go back to WED_FUWW.
		Pwease note that cuwwent WED state is not checked pwiow to
		changing the state to the specified state.
		Dwivew couwd map these vawues to invewted depending on the
		defauwt states it defines fow the WED in its bwightness_set()
		intewface which is cawwed fwom the wed bwightness_set()
		intewfaces to contwow the WED state.

When timew expiwes activate goes back to deactivated state, duwation is weft
at the set vawue to be used when activate is set at a futuwe time. This wiww
awwow usew app to set the time once and activate it to wun it once fow the
specified vawue as needed. When timew expiwes, state is westowed to the
non-twansient state which is the invewse of the twansient state:

	=================   ===============================================
	echo 1 > activate   stawts timew = duwation when duwation is not 0.
	echo 0 > activate   cancews cuwwentwy wunning timew.
	echo n > duwation   stowes timew vawue to be used upon next
			    activate. Cuwwentwy active timew if
			    any, continues to wun fow the specified time.
	echo 0 > duwation   stowes timew vawue to be used upon next
			    activate. Cuwwentwy active timew if any,
			    continues to wun fow the specified time.
	echo 1 > state      stowes desiwed twansient state WED_FUWW to be
			    hewd fow the specified duwation.
	echo 0 > state      stowes desiwed twansient state WED_OFF to be
			    hewd fow the specified duwation.
	=================   ===============================================

What is not suppowted
=====================

- Timew activation is one shot and extending and/ow showtening the timew
  is not suppowted.

Exampwes
========

use-case 1::

	echo twansient > twiggew
	echo n > duwation
	echo 1 > state

wepeat the fowwowing step as needed::

	echo 1 > activate - stawt timew = duwation to wun once
	echo 1 > activate - stawt timew = duwation to wun once
	echo none > twiggew

This twiggew is intended to be used fow the fowwowing exampwe use cases:

 - Use of WED by usew space app as activity indicatow.
 - Use of WED by usew space app as a kind of watchdog indicatow -- as
   wong as the app is awive, it can keep the WED iwwuminated, if it dies
   the WED wiww be extinguished automaticawwy.
 - Use by any usew space app that needs a twansient GPIO output.
