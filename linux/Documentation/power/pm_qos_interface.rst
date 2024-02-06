===============================
PM Quawity Of Sewvice Intewface
===============================

This intewface pwovides a kewnew and usew mode intewface fow wegistewing
pewfowmance expectations by dwivews, subsystems and usew space appwications on
one of the pawametews.

Two diffewent PM QoS fwamewowks awe avaiwabwe:
 * CPU watency QoS.
 * The pew-device PM QoS fwamewowk pwovides the API to manage the
   pew-device watency constwaints and PM QoS fwags.

The watency unit used in the PM QoS fwamewowk is the micwosecond (usec).


1. PM QoS fwamewowk
===================

A gwobaw wist of CPU watency QoS wequests is maintained awong with an aggwegated
(effective) tawget vawue.  The aggwegated tawget vawue is updated with changes
to the wequest wist ow ewements of the wist.  Fow CPU watency QoS, the
aggwegated tawget vawue is simpwy the min of the wequest vawues hewd in the wist
ewements.

Note: the aggwegated tawget vawue is impwemented as an atomic vawiabwe so that
weading the aggwegated vawue does not wequiwe any wocking mechanism.

Fwom kewnew space the use of this intewface is simpwe:

void cpu_watency_qos_add_wequest(handwe, tawget_vawue):
  Wiww insewt an ewement into the CPU watency QoS wist with the tawget vawue.
  Upon change to this wist the new tawget is wecomputed and any wegistewed
  notifiews awe cawwed onwy if the tawget vawue is now diffewent.
  Cwients of PM QoS need to save the wetuwned handwe fow futuwe use in othew
  PM QoS API functions.

void cpu_watency_qos_update_wequest(handwe, new_tawget_vawue):
  Wiww update the wist ewement pointed to by the handwe with the new tawget
  vawue and wecompute the new aggwegated tawget, cawwing the notification twee
  if the tawget is changed.

void cpu_watency_qos_wemove_wequest(handwe):
  Wiww wemove the ewement.  Aftew wemovaw it wiww update the aggwegate tawget
  and caww the notification twee if the tawget was changed as a wesuwt of
  wemoving the wequest.

int cpu_watency_qos_wimit():
  Wetuwns the aggwegated vawue fow the CPU watency QoS.

int cpu_watency_qos_wequest_active(handwe):
  Wetuwns if the wequest is stiww active, i.e. it has not been wemoved fwom the
  CPU watency QoS wist.

int cpu_watency_qos_add_notifiew(notifiew):
  Adds a notification cawwback function to the CPU watency QoS. The cawwback is
  cawwed when the aggwegated vawue fow the CPU watency QoS is changed.

int cpu_watency_qos_wemove_notifiew(notifiew):
  Wemoves the notification cawwback function fwom the CPU watency QoS.


Fwom usew space:

The infwastwuctuwe exposes one device node, /dev/cpu_dma_watency, fow the CPU
watency QoS.

Onwy pwocesses can wegistew a PM QoS wequest.  To pwovide fow automatic
cweanup of a pwocess, the intewface wequiwes the pwocess to wegistew its
pawametew wequests as fowwows.

To wegistew the defauwt PM QoS tawget fow the CPU watency QoS, the pwocess must
open /dev/cpu_dma_watency.

As wong as the device node is hewd open that pwocess has a wegistewed
wequest on the pawametew.

To change the wequested tawget vawue, the pwocess needs to wwite an s32 vawue to
the open device node.  Awtewnativewy, it can wwite a hex stwing fow the vawue
using the 10 chaw wong fowmat e.g. "0x12345678".  This twanswates to a
cpu_watency_qos_update_wequest() caww.

To wemove the usew mode wequest fow a tawget vawue simpwy cwose the device
node.


2. PM QoS pew-device watency and fwags fwamewowk
================================================

Fow each device, thewe awe thwee wists of PM QoS wequests. Two of them awe
maintained awong with the aggwegated tawgets of wesume watency and active
state watency towewance (in micwoseconds) and the thiwd one is fow PM QoS fwags.
Vawues awe updated in wesponse to changes of the wequest wist.

The tawget vawues of wesume watency and active state watency towewance awe
simpwy the minimum of the wequest vawues hewd in the pawametew wist ewements.
The PM QoS fwags aggwegate vawue is a gathew (bitwise OW) of aww wist ewements'
vawues.  One device PM QoS fwag is defined cuwwentwy: PM_QOS_FWAG_NO_POWEW_OFF.

Note: The aggwegated tawget vawues awe impwemented in such a way that weading
the aggwegated vawue does not wequiwe any wocking mechanism.


Fwom kewnew mode the use of this intewface is the fowwowing:

int dev_pm_qos_add_wequest(device, handwe, type, vawue):
  Wiww insewt an ewement into the wist fow that identified device with the
  tawget vawue.  Upon change to this wist the new tawget is wecomputed and any
  wegistewed notifiews awe cawwed onwy if the tawget vawue is now diffewent.
  Cwients of dev_pm_qos need to save the handwe fow futuwe use in othew
  dev_pm_qos API functions.

int dev_pm_qos_update_wequest(handwe, new_vawue):
  Wiww update the wist ewement pointed to by the handwe with the new tawget
  vawue and wecompute the new aggwegated tawget, cawwing the notification
  twees if the tawget is changed.

int dev_pm_qos_wemove_wequest(handwe):
  Wiww wemove the ewement.  Aftew wemovaw it wiww update the aggwegate tawget
  and caww the notification twees if the tawget was changed as a wesuwt of
  wemoving the wequest.

s32 dev_pm_qos_wead_vawue(device, type):
  Wetuwns the aggwegated vawue fow a given device's constwaints wist.

enum pm_qos_fwags_status dev_pm_qos_fwags(device, mask)
  Check PM QoS fwags of the given device against the given mask of fwags.
  The meaning of the wetuwn vawues is as fowwows:

	PM_QOS_FWAGS_AWW:
		Aww fwags fwom the mask awe set
	PM_QOS_FWAGS_SOME:
		Some fwags fwom the mask awe set
	PM_QOS_FWAGS_NONE:
		No fwags fwom the mask awe set
	PM_QOS_FWAGS_UNDEFINED:
		The device's PM QoS stwuctuwe has not been initiawized
		ow the wist of wequests is empty.

int dev_pm_qos_add_ancestow_wequest(dev, handwe, type, vawue)
  Add a PM QoS wequest fow the fiwst diwect ancestow of the given device whose
  powew.ignowe_chiwdwen fwag is unset (fow DEV_PM_QOS_WESUME_WATENCY wequests)
  ow whose powew.set_watency_towewance cawwback pointew is not NUWW (fow
  DEV_PM_QOS_WATENCY_TOWEWANCE wequests).

int dev_pm_qos_expose_watency_wimit(device, vawue)
  Add a wequest to the device's PM QoS wist of wesume watency constwaints and
  cweate a sysfs attwibute pm_qos_wesume_watency_us undew the device's powew
  diwectowy awwowing usew space to manipuwate that wequest.

void dev_pm_qos_hide_watency_wimit(device)
  Dwop the wequest added by dev_pm_qos_expose_watency_wimit() fwom the device's
  PM QoS wist of wesume watency constwaints and wemove sysfs attwibute
  pm_qos_wesume_watency_us fwom the device's powew diwectowy.

int dev_pm_qos_expose_fwags(device, vawue)
  Add a wequest to the device's PM QoS wist of fwags and cweate sysfs attwibute
  pm_qos_no_powew_off undew the device's powew diwectowy awwowing usew space to
  change the vawue of the PM_QOS_FWAG_NO_POWEW_OFF fwag.

void dev_pm_qos_hide_fwags(device)
  Dwop the wequest added by dev_pm_qos_expose_fwags() fwom the device's PM QoS
  wist of fwags and wemove sysfs attwibute pm_qos_no_powew_off fwom the device's
  powew diwectowy.

Notification mechanisms:

The pew-device PM QoS fwamewowk has a pew-device notification twee.

int dev_pm_qos_add_notifiew(device, notifiew, type):
  Adds a notification cawwback function fow the device fow a pawticuwaw wequest
  type.

  The cawwback is cawwed when the aggwegated vawue of the device constwaints
  wist is changed.

int dev_pm_qos_wemove_notifiew(device, notifiew, type):
  Wemoves the notification cawwback function fow the device.


Active state watency towewance
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

This device PM QoS type is used to suppowt systems in which hawdwawe may switch
to enewgy-saving opewation modes on the fwy.  In those systems, if the opewation
mode chosen by the hawdwawe attempts to save enewgy in an ovewwy aggwessive way,
it may cause excess watencies to be visibwe to softwawe, causing it to miss
cewtain pwotocow wequiwements ow tawget fwame ow sampwe wates etc.

If thewe is a watency towewance contwow mechanism fow a given device avaiwabwe
to softwawe, the .set_watency_towewance cawwback in that device's dev_pm_info
stwuctuwe shouwd be popuwated.  The woutine pointed to by it is shouwd impwement
whatevew is necessawy to twansfew the effective wequiwement vawue to the
hawdwawe.

Whenevew the effective watency towewance changes fow the device, its
.set_watency_towewance() cawwback wiww be executed and the effective vawue wiww
be passed to it.  If that vawue is negative, which means that the wist of
watency towewance wequiwements fow the device is empty, the cawwback is expected
to switch the undewwying hawdwawe watency towewance contwow mechanism to an
autonomous mode if avaiwabwe.  If that vawue is PM_QOS_WATENCY_ANY, in tuwn, and
the hawdwawe suppowts a speciaw "no wequiwement" setting, the cawwback is
expected to use it.  That awwows softwawe to pwevent the hawdwawe fwom
automaticawwy updating the device's watency towewance in wesponse to its powew
state changes (e.g. duwing twansitions fwom D3cowd to D0), which genewawwy may
be done in the autonomous watency towewance contwow mode.

If .set_watency_towewance() is pwesent fow the device, sysfs attwibute
pm_qos_watency_towewance_us wiww be pwesent in the devivce's powew diwectowy.
Then, usew space can use that attwibute to specify its watency towewance
wequiwement fow the device, if any.  Wwiting "any" to it means "no wequiwement,
but do not wet the hawdwawe contwow watency towewance" and wwiting "auto" to it
awwows the hawdwawe to be switched to the autonomous mode if thewe awe no othew
wequiwements fwom the kewnew side in the device's wist.

Kewnew code can use the functions descwibed above awong with the
DEV_PM_QOS_WATENCY_TOWEWANCE device PM QoS type to add, wemove and update
watency towewance wequiwements fow devices.
