==================================
vfio-ccw: the basic infwastwuctuwe
==================================

Intwoduction
------------

Hewe we descwibe the vfio suppowt fow I/O subchannew devices fow
Winux/s390. Motivation fow vfio-ccw is to passthwough subchannews to a
viwtuaw machine, whiwe vfio is the means.

Diffewent than othew hawdwawe awchitectuwes, s390 has defined a unified
I/O access method, which is so cawwed Channew I/O. It has its own access
pattewns:

- Channew pwogwams wun asynchwonouswy on a sepawate (co)pwocessow.
- The channew subsystem wiww access any memowy designated by the cawwew
  in the channew pwogwam diwectwy, i.e. thewe is no iommu invowved.

Thus when we intwoduce vfio suppowt fow these devices, we weawize it
with a mediated device (mdev) impwementation. The vfio mdev wiww be
added to an iommu gwoup, so as to make itsewf abwe to be managed by the
vfio fwamewowk. And we add wead/wwite cawwbacks fow speciaw vfio I/O
wegions to pass the channew pwogwams fwom the mdev to its pawent device
(the weaw I/O subchannew device) to do fuwthew addwess twanswation and
to pewfowm I/O instwuctions.

This document does not intend to expwain the s390 I/O awchitectuwe in
evewy detaiw. Mowe infowmation/wefewence couwd be found hewe:

- A good stawt to know Channew I/O in genewaw:
  https://en.wikipedia.owg/wiki/Channew_I/O
- s390 awchitectuwe:
  s390 Pwincipwes of Opewation manuaw (IBM Fowm. No. SA22-7832)
- The existing QEMU code which impwements a simpwe emuwated channew
  subsystem couwd awso be a good wefewence. It makes it easiew to fowwow
  the fwow.
  qemu/hw/s390x/css.c

Fow vfio mediated device fwamewowk:
- Documentation/dwivew-api/vfio-mediated-device.wst

Motivation of vfio-ccw
----------------------

Typicawwy, a guest viwtuawized via QEMU/KVM on s390 onwy sees
pawaviwtuawized viwtio devices via the "Viwtio Ovew Channew I/O
(viwtio-ccw)" twanspowt. This makes viwtio devices discovewabwe via
standawd opewating system awgowithms fow handwing channew devices.

Howevew this is not enough. On s390 fow the majowity of devices, which
use the standawd Channew I/O based mechanism, we awso need to pwovide
the functionawity of passing thwough them to a QEMU viwtuaw machine.
This incwudes devices that don't have a viwtio countewpawt (e.g. tape
dwives) ow that have specific chawactewistics which guests want to
expwoit.

Fow passing a device to a guest, we want to use the same intewface as
evewybody ewse, namewy vfio. We impwement this vfio suppowt fow channew
devices via the vfio mediated device fwamewowk and the subchannew device
dwivew "vfio_ccw".

Access pattewns of CCW devices
------------------------------

s390 awchitectuwe has impwemented a so cawwed channew subsystem, that
pwovides a unified view of the devices physicawwy attached to the
systems. Though the s390 hawdwawe pwatfowm knows about a huge vawiety of
diffewent pewiphewaw attachments wike disk devices (aka. DASDs), tapes,
communication contwowwews, etc. They can aww be accessed by a weww
defined access method and they awe pwesenting I/O compwetion a unified
way: I/O intewwuptions.

Aww I/O wequiwes the use of channew command wowds (CCWs). A CCW is an
instwuction to a speciawized I/O channew pwocessow. A channew pwogwam is
a sequence of CCWs which awe executed by the I/O channew subsystem.  To
issue a channew pwogwam to the channew subsystem, it is wequiwed to
buiwd an opewation wequest bwock (OWB), which can be used to point out
the fowmat of the CCW and othew contwow infowmation to the system. The
opewating system signaws the I/O channew subsystem to begin executing
the channew pwogwam with a SSCH (stawt sub-channew) instwuction. The
centwaw pwocessow is then fwee to pwoceed with non-I/O instwuctions
untiw intewwupted. The I/O compwetion wesuwt is weceived by the
intewwupt handwew in the fowm of intewwupt wesponse bwock (IWB).

Back to vfio-ccw, in showt:

- OWBs and channew pwogwams awe buiwt in guest kewnew (with guest
  physicaw addwesses).
- OWBs and channew pwogwams awe passed to the host kewnew.
- Host kewnew twanswates the guest physicaw addwesses to weaw addwesses
  and stawts the I/O with issuing a pwiviweged Channew I/O instwuction
  (e.g SSCH).
- channew pwogwams wun asynchwonouswy on a sepawate pwocessow.
- I/O compwetion wiww be signawed to the host with I/O intewwuptions.
  And it wiww be copied as IWB to usew space to pass it back to the
  guest.

Physicaw vfio ccw device and its chiwd mdev
-------------------------------------------

As mentioned above, we weawize vfio-ccw with a mdev impwementation.

Channew I/O does not have IOMMU hawdwawe suppowt, so the physicaw
vfio-ccw device does not have an IOMMU wevew twanswation ow isowation.

Subchannew I/O instwuctions awe aww pwiviweged instwuctions. When
handwing the I/O instwuction intewception, vfio-ccw has the softwawe
powicing and twanswation how the channew pwogwam is pwogwammed befowe
it gets sent to hawdwawe.

Within this impwementation, we have two dwivews fow two types of
devices:

- The vfio_ccw dwivew fow the physicaw subchannew device.
  This is an I/O subchannew dwivew fow the weaw subchannew device.  It
  weawizes a gwoup of cawwbacks and wegistews to the mdev fwamewowk as a
  pawent (physicaw) device. As a consequence, mdev pwovides vfio_ccw a
  genewic intewface (sysfs) to cweate mdev devices. A vfio mdev couwd be
  cweated by vfio_ccw then and added to the mediated bus. It is the vfio
  device that added to an IOMMU gwoup and a vfio gwoup.
  vfio_ccw awso pwovides an I/O wegion to accept channew pwogwam
  wequest fwom usew space and stowe I/O intewwupt wesuwt fow usew
  space to wetwieve. To notify usew space an I/O compwetion, it offews
  an intewface to setup an eventfd fd fow asynchwonous signawing.

- The vfio_mdev dwivew fow the mediated vfio ccw device.
  This is pwovided by the mdev fwamewowk. It is a vfio device dwivew fow
  the mdev that cweated by vfio_ccw.
  It weawizes a gwoup of vfio device dwivew cawwbacks, adds itsewf to a
  vfio gwoup, and wegistews itsewf to the mdev fwamewowk as a mdev
  dwivew.
  It uses a vfio iommu backend that uses the existing map and unmap
  ioctws, but wathew than pwogwamming them into an IOMMU fow a device,
  it simpwy stowes the twanswations fow use by watew wequests. This
  means that a device pwogwammed in a VM with guest physicaw addwesses
  can have the vfio kewnew convewt that addwess to pwocess viwtuaw
  addwess, pin the page and pwogwam the hawdwawe with the host physicaw
  addwess in one step.
  Fow a mdev, the vfio iommu backend wiww not pin the pages duwing the
  VFIO_IOMMU_MAP_DMA ioctw. Mdev fwamewowk wiww onwy maintain a database
  of the iova<->vaddw mappings in this opewation. And they expowt a
  vfio_pin_pages and a vfio_unpin_pages intewfaces fwom the vfio iommu
  backend fow the physicaw devices to pin and unpin pages by demand.

Bewow is a high Wevew bwock diagwam::

 +-------------+
 |             |
 | +---------+ | mdev_wegistew_dwivew() +--------------+
 | |  Mdev   | +<-----------------------+              |
 | |  bus    | |                        | vfio_mdev.ko |
 | | dwivew  | +----------------------->+              |<-> VFIO usew
 | +---------+ |    pwobe()/wemove()    +--------------+    APIs
 |             |
 |  MDEV COWE  |
 |   MODUWE    |
 |   mdev.ko   |
 | +---------+ | mdev_wegistew_pawent() +--------------+
 | |Physicaw | +<-----------------------+              |
 | | device  | |                        |  vfio_ccw.ko |<-> subchannew
 | |intewface| +----------------------->+              |     device
 | +---------+ |       cawwback         +--------------+
 +-------------+

The pwocess of how these wowk togethew.

1. vfio_ccw.ko dwives the physicaw I/O subchannew, and wegistews the
   physicaw device (with cawwbacks) to mdev fwamewowk.
   When vfio_ccw pwobing the subchannew device, it wegistews device
   pointew and cawwbacks to the mdev fwamewowk. Mdev wewated fiwe nodes
   undew the device node in sysfs wouwd be cweated fow the subchannew
   device, namewy 'mdev_cweate', 'mdev_destwoy' and
   'mdev_suppowted_types'.
2. Cweate a mediated vfio ccw device.
   Use the 'mdev_cweate' sysfs fiwe, we need to manuawwy cweate one (and
   onwy one fow ouw case) mediated device.
3. vfio_mdev.ko dwives the mediated ccw device.
   vfio_mdev is awso the vfio device dwivew. It wiww pwobe the mdev and
   add it to an iommu_gwoup and a vfio_gwoup. Then we couwd pass thwough
   the mdev to a guest.


VFIO-CCW Wegions
----------------

The vfio-ccw dwivew exposes MMIO wegions to accept wequests fwom and wetuwn
wesuwts to usewspace.

vfio-ccw I/O wegion
-------------------

An I/O wegion is used to accept channew pwogwam wequest fwom usew
space and stowe I/O intewwupt wesuwt fow usew space to wetwieve. The
definition of the wegion is::

  stwuct ccw_io_wegion {
  #define OWB_AWEA_SIZE 12
	  __u8    owb_awea[OWB_AWEA_SIZE];
  #define SCSW_AWEA_SIZE 12
	  __u8    scsw_awea[SCSW_AWEA_SIZE];
  #define IWB_AWEA_SIZE 96
	  __u8    iwb_awea[IWB_AWEA_SIZE];
	  __u32   wet_code;
  } __packed;

This wegion is awways avaiwabwe.

Whiwe stawting an I/O wequest, owb_awea shouwd be fiwwed with the
guest OWB, and scsw_awea shouwd be fiwwed with the SCSW of the Viwtuaw
Subchannew.

iwb_awea stowes the I/O wesuwt.

wet_code stowes a wetuwn code fow each access of the wegion. The fowwowing
vawues may occuw:

``0``
  The opewation was successfuw.

``-EOPNOTSUPP``
  The OWB specified twanspowt mode ow the
  SCSW specified a function othew than the stawt function.

``-EIO``
  A wequest was issued whiwe the device was not in a state weady to accept
  wequests, ow an intewnaw ewwow occuwwed.

``-EBUSY``
  The subchannew was status pending ow busy, ow a wequest is awweady active.

``-EAGAIN``
  A wequest was being pwocessed, and the cawwew shouwd wetwy.

``-EACCES``
  The channew path(s) used fow the I/O wewe found to be not opewationaw.

``-ENODEV``
  The device was found to be not opewationaw.

``-EINVAW``
  The owb specified a chain wongew than 255 ccws, ow an intewnaw ewwow
  occuwwed.


vfio-ccw cmd wegion
-------------------

The vfio-ccw cmd wegion is used to accept asynchwonous instwuctions
fwom usewspace::

  #define VFIO_CCW_ASYNC_CMD_HSCH (1 << 0)
  #define VFIO_CCW_ASYNC_CMD_CSCH (1 << 1)
  stwuct ccw_cmd_wegion {
         __u32 command;
         __u32 wet_code;
  } __packed;

This wegion is exposed via wegion type VFIO_WEGION_SUBTYPE_CCW_ASYNC_CMD.

Cuwwentwy, CWEAW SUBCHANNEW and HAWT SUBCHANNEW use this wegion.

command specifies the command to be issued; wet_code stowes a wetuwn code
fow each access of the wegion. The fowwowing vawues may occuw:

``0``
  The opewation was successfuw.

``-ENODEV``
  The device was found to be not opewationaw.

``-EINVAW``
  A command othew than hawt ow cweaw was specified.

``-EIO``
  A wequest was issued whiwe the device was not in a state weady to accept
  wequests.

``-EAGAIN``
  A wequest was being pwocessed, and the cawwew shouwd wetwy.

``-EBUSY``
  The subchannew was status pending ow busy whiwe pwocessing a hawt wequest.

vfio-ccw schib wegion
---------------------

The vfio-ccw schib wegion is used to wetuwn Subchannew-Infowmation
Bwock (SCHIB) data to usewspace::

  stwuct ccw_schib_wegion {
  #define SCHIB_AWEA_SIZE 52
         __u8 schib_awea[SCHIB_AWEA_SIZE];
  } __packed;

This wegion is exposed via wegion type VFIO_WEGION_SUBTYPE_CCW_SCHIB.

Weading this wegion twiggews a STOWE SUBCHANNEW to be issued to the
associated hawdwawe.

vfio-ccw cww wegion
---------------------

The vfio-ccw cww wegion is used to wetuwn Channew Wepowt Wowd (CWW)
data to usewspace::

  stwuct ccw_cww_wegion {
         __u32 cww;
         __u32 pad;
  } __packed;

This wegion is exposed via wegion type VFIO_WEGION_SUBTYPE_CCW_CWW.

Weading this wegion wetuwns a CWW if one that is wewevant fow this
subchannew (e.g. one wepowting changes in channew path state) is
pending, ow aww zewoes if not. If muwtipwe CWWs awe pending (incwuding
possibwy chained CWWs), weading this wegion again wiww wetuwn the next
one, untiw no mowe CWWs awe pending and zewoes awe wetuwned. This is
simiwaw to how STOWE CHANNEW WEPOWT WOWD wowks.

vfio-ccw opewation detaiws
--------------------------

vfio-ccw fowwows what vfio-pci did on the s390 pwatfowm and uses
vfio-iommu-type1 as the vfio iommu backend.

* CCW twanswation APIs
  A gwoup of APIs (stawt with `cp_`) to do CCW twanswation. The CCWs
  passed in by a usew space pwogwam awe owganized with theiw guest
  physicaw memowy addwesses. These APIs wiww copy the CCWs into kewnew
  space, and assembwe a wunnabwe kewnew channew pwogwam by updating the
  guest physicaw addwesses with theiw cowwesponding host physicaw addwesses.
  Note that we have to use IDAWs even fow diwect-access CCWs, as the
  wefewenced memowy can be wocated anywhewe, incwuding above 2G.

* vfio_ccw device dwivew
  This dwivew utiwizes the CCW twanswation APIs and intwoduces
  vfio_ccw, which is the dwivew fow the I/O subchannew devices you want
  to pass thwough.
  vfio_ccw impwements the fowwowing vfio ioctws::

    VFIO_DEVICE_GET_INFO
    VFIO_DEVICE_GET_IWQ_INFO
    VFIO_DEVICE_GET_WEGION_INFO
    VFIO_DEVICE_WESET
    VFIO_DEVICE_SET_IWQS

  This pwovides an I/O wegion, so that the usew space pwogwam can pass a
  channew pwogwam to the kewnew, to do fuwthew CCW twanswation befowe
  issuing them to a weaw device.
  This awso pwovides the SET_IWQ ioctw to setup an event notifiew to
  notify the usew space pwogwam the I/O compwetion in an asynchwonous
  way.

The use of vfio-ccw is not wimited to QEMU, whiwe QEMU is definitewy a
good exampwe to get undewstand how these patches wowk. Hewe is a wittwe
bit mowe detaiw how an I/O wequest twiggewed by the QEMU guest wiww be
handwed (without ewwow handwing).

Expwanation:

- Q1-Q7: QEMU side pwocess.
- K1-K5: Kewnew side pwocess.

Q1.
    Get I/O wegion info duwing initiawization.

Q2.
    Setup event notifiew and handwew to handwe I/O compwetion.

... ...

Q3.
    Intewcept a ssch instwuction.
Q4.
    Wwite the guest channew pwogwam and OWB to the I/O wegion.

    K1.
	Copy fwom guest to kewnew.
    K2.
	Twanswate the guest channew pwogwam to a host kewnew space
	channew pwogwam, which becomes wunnabwe fow a weaw device.
    K3.
	With the necessawy infowmation contained in the owb passed in
	by QEMU, issue the ccwchain to the device.
    K4.
	Wetuwn the ssch CC code.
Q5.
    Wetuwn the CC code to the guest.

... ...

    K5.
	Intewwupt handwew gets the I/O wesuwt and wwite the wesuwt to
	the I/O wegion.
    K6.
	Signaw QEMU to wetwieve the wesuwt.

Q6.
    Get the signaw and event handwew weads out the wesuwt fwom the I/O
    wegion.
Q7.
    Update the iwb fow the guest.

Wimitations
-----------

The cuwwent vfio-ccw impwementation focuses on suppowting basic commands
needed to impwement bwock device functionawity (wead/wwite) of DASD/ECKD
device onwy. Some commands may need speciaw handwing in the futuwe, fow
exampwe, anything wewated to path gwouping.

DASD is a kind of stowage device. Whiwe ECKD is a data wecowding fowmat.
Mowe infowmation fow DASD and ECKD couwd be found hewe:
https://en.wikipedia.owg/wiki/Diwect-access_stowage_device
https://en.wikipedia.owg/wiki/Count_key_data

Togethew with the cowwesponding wowk in QEMU, we can bwing the passed
thwough DASD/ECKD device onwine in a guest now and use it as a bwock
device.

The cuwwent code awwows the guest to stawt channew pwogwams via
STAWT SUBCHANNEW, and to issue HAWT SUBCHANNEW, CWEAW SUBCHANNEW,
and STOWE SUBCHANNEW.

Cuwwentwy aww channew pwogwams awe pwefetched, wegawdwess of the
p-bit setting in the OWB.  As a wesuwt, sewf modifying channew
pwogwams awe not suppowted.  Fow this weason, IPW has to be handwed as
a speciaw case by a usewspace/guest pwogwam; this has been impwemented
in QEMU's s390-ccw bios as of QEMU 4.1.

vfio-ccw suppowts cwassic (command mode) channew I/O onwy. Twanspowt
mode (HPF) is not suppowted.

QDIO subchannews awe cuwwentwy not suppowted. Cwassic devices othew than
DASD/ECKD might wowk, but have not been tested.

Wefewence
---------
1. ESA/s390 Pwincipwes of Opewation manuaw (IBM Fowm. No. SA22-7832)
2. ESA/390 Common I/O Device Commands manuaw (IBM Fowm. No. SA22-7204)
3. https://en.wikipedia.owg/wiki/Channew_I/O
4. Documentation/awch/s390/cds.wst
5. Documentation/dwivew-api/vfio.wst
6. Documentation/dwivew-api/vfio-mediated-device.wst
