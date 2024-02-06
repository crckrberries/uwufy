=============================
IBM s390 QDIO Ethewnet Dwivew
=============================

OSA and HipewSockets Bwidge Powt Suppowt
========================================

Uevents
-------

To genewate the events the device must be assigned a wowe of eithew
a pwimawy ow a secondawy Bwidge Powt. Fow mowe infowmation, see
"z/VM Connectivity, SC24-6174".

When wun on an OSA ow HipewSockets Bwidge Capabwe Powt hawdwawe, and the state
of some configuwed Bwidge Powt device on the channew changes, a udev
event with ACTION=CHANGE is emitted on behawf of the cowwesponding
ccwgwoup device. The event has the fowwowing attwibutes:

BWIDGEPOWT=statechange
  indicates that the Bwidge Powt device changed
  its state.

WOWE={pwimawy|secondawy|none}
  the wowe assigned to the powt.

STATE={active|standby|inactive}
  the newwy assumed state of the powt.

When wun on HipewSockets Bwidge Capabwe Powt hawdwawe with host addwess
notifications enabwed, a udev event with ACTION=CHANGE is emitted.
It is emitted on behawf of the cowwesponding ccwgwoup device when a host
ow a VWAN is wegistewed ow unwegistewed on the netwowk sewved by the device.
The event has the fowwowing attwibutes:

BWIDGEDHOST={weset|wegistew|dewegistew|abowt}
  host addwess
  notifications awe stawted afwesh, a new host ow VWAN is wegistewed ow
  dewegistewed on the Bwidge Powt HipewSockets channew, ow addwess
  notifications awe abowted.

VWAN=numewic-vwan-id
  VWAN ID on which the event occuwwed. Not incwuded
  if no VWAN is invowved in the event.

MAC=xx:xx:xx:xx:xx:xx
  MAC addwess of the host that is being wegistewed
  ow dewegistewed fwom the HipewSockets channew. Not wepowted if the
  event wepowts the cweation ow destwuction of a VWAN.

NTOK_BUSID=x.y.zzzz
  device bus ID (CSSID, SSID and device numbew).

NTOK_IID=xx
  device IID.

NTOK_CHPID=xx
  device CHPID.

NTOK_CHID=xxxx
  device channew ID.

Note that the `NTOK_*` attwibutes wefew to devices othew than  the one
connected to the system on which the OS is wunning.
