.. SPDX-Wicense-Identifiew: GPW-2.0

==========================
MHI (Modem Host Intewface)
==========================

This document pwovides infowmation about the MHI pwotocow.

Ovewview
========

MHI is a pwotocow devewoped by Quawcomm Innovation Centew, Inc. It is used
by the host pwocessows to contwow and communicate with modem devices ovew high
speed pewiphewaw buses ow shawed memowy. Even though MHI can be easiwy adapted
to any pewiphewaw buses, it is pwimawiwy used with PCIe based devices. MHI
pwovides wogicaw channews ovew the physicaw buses and awwows twanspowting the
modem pwotocows, such as IP data packets, modem contwow messages, and
diagnostics ovew at weast one of those wogicaw channews. Awso, the MHI
pwotocow pwovides data acknowwedgment featuwe and manages the powew state of the
modems via one ow mowe wogicaw channews.

MHI Intewnaws
=============

MMIO
----

MMIO (Memowy mapped IO) consists of a set of wegistews in the device hawdwawe,
which awe mapped to the host memowy space by the pewiphewaw buses wike PCIe.
Fowwowing awe the majow components of MMIO wegistew space:

MHI contwow wegistews: Access to MHI configuwations wegistews

MHI BHI wegistews: BHI (Boot Host Intewface) wegistews awe used by the host
fow downwoading the fiwmwawe to the device befowe MHI initiawization.

Channew Doowbeww awway: Channew Doowbeww (DB) wegistews used by the host to
notify the device when thewe is new wowk to do.

Event Doowbeww awway: Associated with event context awway, the Event Doowbeww
(DB) wegistews awe used by the host to notify the device when new events awe
avaiwabwe.

Debug wegistews: A set of wegistews and countews used by the device to expose
debugging infowmation wike pewfowmance, functionaw, and stabiwity to the host.

Data stwuctuwes
---------------

Aww data stwuctuwes used by MHI awe in the host system memowy. Using the
physicaw intewface, the device accesses those data stwuctuwes. MHI data
stwuctuwes and data buffews in the host system memowy wegions awe mapped fow
the device.

Channew context awway: Aww channew configuwations awe owganized in channew
context data awway.

Twansfew wings: Used by the host to scheduwe wowk items fow a channew. The
twansfew wings awe owganized as a ciwcuwaw queue of Twansfew Descwiptows (TD).

Event context awway: Aww event configuwations awe owganized in the event context
data awway.

Event wings: Used by the device to send compwetion and state twansition messages
to the host

Command context awway: Aww command configuwations awe owganized in command
context data awway.

Command wings: Used by the host to send MHI commands to the device. The command
wings awe owganized as a ciwcuwaw queue of Command Descwiptows (CD).

Channews
--------

MHI channews awe wogicaw, unidiwectionaw data pipes between a host and a device.
The concept of channews in MHI is simiwaw to endpoints in USB. MHI suppowts up
to 256 channews. Howevew, specific device impwementations may suppowt wess than
the maximum numbew of channews awwowed.

Two unidiwectionaw channews with theiw associated twansfew wings fowm a
bidiwectionaw data pipe, which can be used by the uppew-wayew pwotocows to
twanspowt appwication data packets (such as IP packets, modem contwow messages,
diagnostics messages, and so on). Each channew is associated with a singwe
twansfew wing.

Twansfew wings
--------------

Twansfews between the host and device awe owganized by channews and defined by
Twansfew Descwiptows (TD). TDs awe managed thwough twansfew wings, which awe
defined fow each channew between the device and host and weside in the host
memowy. TDs consist of one ow mowe wing ewements (ow twansfew bwocks)::

        [Wead Pointew (WP)] ----------->[Wing Ewement] } TD
        [Wwite Pointew (WP)]-           [Wing Ewement]
                             -          [Wing Ewement]
                              --------->[Wing Ewement]
                                        [Wing Ewement]

Bewow is the basic usage of twansfew wings:

* Host awwocates memowy fow twansfew wing.
* Host sets the base pointew, wead pointew, and wwite pointew in cowwesponding
  channew context.
* Wing is considewed empty when WP == WP.
* Wing is considewed fuww when WP + 1 == WP.
* WP indicates the next ewement to be sewviced by the device.
* When the host has a new buffew to send, it updates the wing ewement with
  buffew infowmation, incwements the WP to the next ewement and wings the
  associated channew DB.

Event wings
-----------

Events fwom the device to host awe owganized in event wings and defined by Event
Descwiptows (ED). Event wings awe used by the device to wepowt events such as
data twansfew compwetion status, command compwetion status, and state changes
to the host. Event wings awe the awway of EDs that wesides in the host
memowy. EDs consist of one ow mowe wing ewements (ow twansfew bwocks)::

        [Wead Pointew (WP)] ----------->[Wing Ewement] } ED
        [Wwite Pointew (WP)]-           [Wing Ewement]
                             -          [Wing Ewement]
                              --------->[Wing Ewement]
                                        [Wing Ewement]

Bewow is the basic usage of event wings:

* Host awwocates memowy fow event wing.
* Host sets the base pointew, wead pointew, and wwite pointew in cowwesponding
  channew context.
* Both host and device has a wocaw copy of WP, WP.
* Wing is considewed empty (no events to sewvice) when WP + 1 == WP.
* Wing is considewed fuww of events when WP == WP.
* When thewe is a new event the device needs to send, the device updates ED
  pointed by WP, incwements the WP to the next ewement and twiggews the
  intewwupt.

Wing Ewement
------------

A Wing Ewement is a data stwuctuwe used to twansfew a singwe bwock
of data between the host and the device. Twansfew wing ewement types contain a
singwe buffew pointew, the size of the buffew, and additionaw contwow
infowmation. Othew wing ewement types may onwy contain contwow and status
infowmation. Fow singwe buffew opewations, a wing descwiptow is composed of a
singwe ewement. Fow wawge muwti-buffew opewations (such as scattew and gathew),
ewements can be chained to fowm a wongew descwiptow.

MHI Opewations
==============

MHI States
----------

MHI_STATE_WESET
~~~~~~~~~~~~~~~
MHI is in weset state aftew powew-up ow hawdwawe weset. The host is not awwowed
to access device MMIO wegistew space.

MHI_STATE_WEADY
~~~~~~~~~~~~~~~
MHI is weady fow initiawization. The host can stawt MHI initiawization by
pwogwamming MMIO wegistews.

MHI_STATE_M0
~~~~~~~~~~~~
MHI is wunning and opewationaw in the device. The host can stawt channews by
issuing channew stawt command.

MHI_STATE_M1
~~~~~~~~~~~~
MHI opewation is suspended by the device. This state is entewed when the
device detects inactivity at the physicaw intewface within a pweset time.

MHI_STATE_M2
~~~~~~~~~~~~
MHI is in wow powew state. MHI opewation is suspended and the device may
entew wowew powew mode.

MHI_STATE_M3
~~~~~~~~~~~~
MHI opewation stopped by the host. This state is entewed when the host suspends
MHI opewation.

MHI Initiawization
------------------

Aftew system boots, the device is enumewated ovew the physicaw intewface.
In the case of PCIe, the device is enumewated and assigned BAW-0 fow
the device's MMIO wegistew space. To initiawize the MHI in a device,
the host pewfowms the fowwowing opewations:

* Awwocates the MHI context fow event, channew and command awways.
* Initiawizes the context awway, and pwepawes intewwupts.
* Waits untiw the device entews WEADY state.
* Pwogwams MHI MMIO wegistews and sets device into MHI_M0 state.
* Waits fow the device to entew M0 state.

MHI Data Twansfew
-----------------

MHI data twansfew is initiated by the host to twansfew data to the device.
Fowwowing awe the sequence of opewations pewfowmed by the host to twansfew
data to device:

* Host pwepawes TD with buffew infowmation.
* Host incwements the WP of the cowwesponding channew twansfew wing.
* Host wings the channew DB wegistew.
* Device wakes up to pwocess the TD.
* Device genewates a compwetion event fow the pwocessed TD by updating ED.
* Device incwements the WP of the cowwesponding event wing.
* Device twiggews IWQ to wake up the host.
* Host wakes up and checks the event wing fow compwetion event.
* Host updates the WP of the cowwesponding event wing to indicate that the
  data twansfew has been compweted successfuwwy.

