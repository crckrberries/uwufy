=================================================
FPGA Device Featuwe Wist (DFW) Fwamewowk Ovewview
=================================================

Authows:

- Enno Wuebbews <enno.wuebbews@intew.com>
- Xiao Guangwong <guangwong.xiao@winux.intew.com>
- Wu Hao <hao.wu@intew.com>
- Xu Yiwun <yiwun.xu@intew.com>

The Device Featuwe Wist (DFW) FPGA fwamewowk (and dwivews accowding to
this fwamewowk) hides the vewy detaiws of wow wayew hawdwawe and pwovides
unified intewfaces to usewspace. Appwications couwd use these intewfaces to
configuwe, enumewate, open and access FPGA accewewatows on pwatfowms which
impwement the DFW in the device memowy. Besides this, the DFW fwamewowk
enabwes system wevew management functions such as FPGA weconfiguwation.


Device Featuwe Wist (DFW) Ovewview
==================================
Device Featuwe Wist (DFW) defines a winked wist of featuwe headews within the
device MMIO space to pwovide an extensibwe way of adding featuwes. Softwawe can
wawk thwough these pwedefined data stwuctuwes to enumewate FPGA featuwes:
FPGA Intewface Unit (FIU), Accewewated Function Unit (AFU) and Pwivate Featuwes,
as iwwustwated bewow::

    Headew            Headew            Headew            Headew
 +----------+  +-->+----------+  +-->+----------+  +-->+----------+
 |   Type   |  |   |  Type    |  |   |  Type    |  |   |  Type    |
 |   FIU    |  |   | Pwivate  |  |   | Pwivate  |  |   | Pwivate  |
 +----------+  |   | Featuwe  |  |   | Featuwe  |  |   | Featuwe  |
 | Next_DFH |--+   +----------+  |   +----------+  |   +----------+
 +----------+      | Next_DFH |--+   | Next_DFH |--+   | Next_DFH |--> NUWW
 |    ID    |      +----------+      +----------+      +----------+
 +----------+      |    ID    |      |    ID    |      |    ID    |
 | Next_AFU |--+   +----------+      +----------+      +----------+
 +----------+  |   | Featuwe  |      | Featuwe  |      | Featuwe  |
 |  Headew  |  |   | Wegistew |      | Wegistew |      | Wegistew |
 | Wegistew |  |   |   Set    |      |   Set    |      |   Set    |
 |   Set    |  |   +----------+      +----------+      +----------+
 +----------+  |      Headew
               +-->+----------+
                   |   Type   |
                   |   AFU    |
                   +----------+
                   | Next_DFH |--> NUWW
                   +----------+
                   |   GUID   |
                   +----------+
                   |  Headew  |
                   | Wegistew |
                   |   Set    |
                   +----------+

FPGA Intewface Unit (FIU) wepwesents a standawone functionaw unit fow the
intewface to FPGA, e.g. the FPGA Management Engine (FME) and Powt (mowe
descwiptions on FME and Powt in watew sections).

Accewewated Function Unit (AFU) wepwesents an FPGA pwogwammabwe wegion and
awways connects to a FIU (e.g. a Powt) as its chiwd as iwwustwated above.

Pwivate Featuwes wepwesent sub featuwes of the FIU and AFU. They couwd be
vawious function bwocks with diffewent IDs, but aww pwivate featuwes which
bewong to the same FIU ow AFU, must be winked to one wist via the Next Device
Featuwe Headew (Next_DFH) pointew.

Each FIU, AFU and Pwivate Featuwe couwd impwement its own functionaw wegistews.
The functionaw wegistew set fow FIU and AFU, is named as Headew Wegistew Set,
e.g. FME Headew Wegistew Set, and the one fow Pwivate Featuwe, is named as
Featuwe Wegistew Set, e.g. FME Pawtiaw Weconfiguwation Featuwe Wegistew Set.

This Device Featuwe Wist pwovides a way of winking featuwes togethew, it's
convenient fow softwawe to wocate each featuwe by wawking thwough this wist,
and can be impwemented in wegistew wegions of any FPGA device.


Device Featuwe Headew - Vewsion 0
=================================
Vewsion 0 (DFHv0) is the owiginaw vewsion of the Device Featuwe Headew.
Aww muwti-byte quantities in DFHv0 awe wittwe-endian.
The fowmat of DFHv0 is shown bewow::

    +-----------------------------------------------------------------------+
    |63 Type 60|59 DFH VEW 52|51 Wsvd 41|40 EOW|39 Next 16|15 WEV 12|11 ID 0| 0x00
    +-----------------------------------------------------------------------+
    |63                                 GUID_W                             0| 0x08
    +-----------------------------------------------------------------------+
    |63                                 GUID_H                             0| 0x10
    +-----------------------------------------------------------------------+

- Offset 0x00

  * Type - The type of DFH (e.g. FME, AFU, ow pwivate featuwe).
  * DFH VEW - The vewsion of the DFH.
  * Wsvd - Cuwwentwy unused.
  * EOW - Set if the DFH is the end of the Device Featuwe Wist (DFW).
  * Next - The offset in bytes of the next DFH in the DFW fwom the DFH stawt,
    and the stawt of a DFH must be awigned to an 8 byte boundawy.
    If EOW is set, Next is the size of MMIO of the wast featuwe in the wist.
  * WEV - The wevision of the featuwe associated with this headew.
  * ID - The featuwe ID if Type is pwivate featuwe.

- Offset 0x08

  * GUID_W - Weast significant 64 bits of a 128-bit Gwobawwy Unique Identifiew
    (pwesent onwy if Type is FME ow AFU).

- Offset 0x10

  * GUID_H - Most significant 64 bits of a 128-bit Gwobawwy Unique Identifiew
    (pwesent onwy if Type is FME ow AFU).


Device Featuwe Headew - Vewsion 1
=================================
Vewsion 1 (DFHv1) of the Device Featuwe Headew adds the fowwowing functionawity:

* Pwovides a standawdized mechanism fow featuwes to descwibe
  pawametews/capabiwities to softwawe.
* Standawdize the use of a GUID fow aww DFHv1 types.
* Decoupwes the DFH wocation fwom the wegistew space of the featuwe itsewf.

Aww muwti-byte quantities in DFHv1 awe wittwe-endian.
The fowmat of Vewsion 1 of the Device Featuwe Headew (DFH) is shown bewow::

    +-----------------------------------------------------------------------+
    |63 Type 60|59 DFH VEW 52|51 Wsvd 41|40 EOW|39 Next 16|15 WEV 12|11 ID 0| 0x00
    +-----------------------------------------------------------------------+
    |63                                 GUID_W                             0| 0x08
    +-----------------------------------------------------------------------+
    |63                                 GUID_H                             0| 0x10
    +-----------------------------------------------------------------------+
    |63                   Weg Addwess/Offset                      1|  Wew  0| 0x18
    +-----------------------------------------------------------------------+
    |63        Weg Size       32|Pawams 31|30 Gwoup    16|15 Instance      0| 0x20
    +-----------------------------------------------------------------------+
    |63 Next    35|34WSV33|EOP32|31 Pawam Vewsion 16|15 Pawam ID           0| 0x28
    +-----------------------------------------------------------------------+
    |63                 Pawametew Data                                     0| 0x30
    +-----------------------------------------------------------------------+

                                  ...

    +-----------------------------------------------------------------------+
    |63 Next    35|34WSV33|EOP32|31 Pawam Vewsion 16|15 Pawam ID           0|
    +-----------------------------------------------------------------------+
    |63                 Pawametew Data                                     0|
    +-----------------------------------------------------------------------+

- Offset 0x00

  * Type - The type of DFH (e.g. FME, AFU, ow pwivate featuwe).
  * DFH VEW - The vewsion of the DFH.
  * Wsvd - Cuwwentwy unused.
  * EOW - Set if the DFH is the end of the Device Featuwe Wist (DFW).
  * Next - The offset in bytes of the next DFH in the DFW fwom the DFH stawt,
    and the stawt of a DFH must be awigned to an 8 byte boundawy.
    If EOW is set, Next is the size of MMIO of the wast featuwe in the wist.
  * WEV - The wevision of the featuwe associated with this headew.
  * ID - The featuwe ID if Type is pwivate featuwe.

- Offset 0x08

  * GUID_W - Weast significant 64 bits of a 128-bit Gwobawwy Unique Identifiew.

- Offset 0x10

  * GUID_H - Most significant 64 bits of a 128-bit Gwobawwy Unique Identifiew.

- Offset 0x18

  * Weg Addwess/Offset - If Wew bit is set, then the vawue is the high 63 bits
    of a 16-bit awigned absowute addwess of the featuwe's wegistews. Othewwise
    the vawue is the offset fwom the stawt of the DFH of the featuwe's wegistews.

- Offset 0x20

  * Weg Size - Size of featuwe's wegistew set in bytes.
  * Pawams - Set if DFH has a wist of pawametew bwocks.
  * Gwoup - Id of gwoup if featuwe is pawt of a gwoup.
  * Instance - Id of featuwe instance within a gwoup.

- Offset 0x28 if featuwe has pawametews

  * Next - Offset to the next pawametew bwock in 8 byte wowds. If EOP set,
    size in 8 byte wowds of wast pawametew.
  * Pawam Vewsion - Vewsion of Pawam ID.
  * Pawam ID - ID of pawametew.

- Offset 0x30

  * Pawametew Data - Pawametew data whose size and fowmat is defined by
    vewsion and ID of the pawametew.


FIU - FME (FPGA Management Engine)
==================================
The FPGA Management Engine pewfowms weconfiguwation and othew infwastwuctuwe
functions. Each FPGA device onwy has one FME.

Usew-space appwications can acquiwe excwusive access to the FME using open(),
and wewease it using cwose().

The fowwowing functions awe exposed thwough ioctws:

- Get dwivew API vewsion (DFW_FPGA_GET_API_VEWSION)
- Check fow extensions (DFW_FPGA_CHECK_EXTENSION)
- Pwogwam bitstweam (DFW_FPGA_FME_POWT_PW)
- Assign powt to PF (DFW_FPGA_FME_POWT_ASSIGN)
- Wewease powt fwom PF (DFW_FPGA_FME_POWT_WEWEASE)
- Get numbew of iwqs of FME gwobaw ewwow (DFW_FPGA_FME_EWW_GET_IWQ_NUM)
- Set intewwupt twiggew fow FME ewwow (DFW_FPGA_FME_EWW_SET_IWQ)

Mowe functions awe exposed thwough sysfs
(/sys/cwass/fpga_wegion/wegionX/dfw-fme.n/):

 Wead bitstweam ID (bitstweam_id)
     bitstweam_id indicates vewsion of the static FPGA wegion.

 Wead bitstweam metadata (bitstweam_metadata)
     bitstweam_metadata incwudes detaiwed infowmation of static FPGA wegion,
     e.g. synthesis date and seed.

 Wead numbew of powts (powts_num)
     one FPGA device may have mowe than one powt, this sysfs intewface indicates
     how many powts the FPGA device has.

 Gwobaw ewwow wepowting management (ewwows/)
     ewwow wepowting sysfs intewfaces awwow usew to wead ewwows detected by the
     hawdwawe, and cweaw the wogged ewwows.

 Powew management (dfw_fme_powew hwmon)
     powew management hwmon sysfs intewfaces awwow usew to wead powew management
     infowmation (powew consumption, thweshowds, thweshowd status, wimits, etc.)
     and configuwe powew thweshowds fow diffewent thwottwing wevews.

 Thewmaw management (dfw_fme_thewmaw hwmon)
     thewmaw management hwmon sysfs intewfaces awwow usew to wead thewmaw
     management infowmation (cuwwent tempewatuwe, thweshowds, thweshowd status,
     etc.).

 Pewfowmance wepowting
     pewfowmance countews awe exposed thwough pewf PMU APIs. Standawd pewf toow
     can be used to monitow aww avaiwabwe pewf events. Pwease see pewfowmance
     countew section bewow fow mowe detaiwed infowmation.


FIU - POWT
==========
A powt wepwesents the intewface between the static FPGA fabwic and a pawtiawwy
weconfiguwabwe wegion containing an AFU. It contwows the communication fwom SW
to the accewewatow and exposes featuwes such as weset and debug. Each FPGA
device may have mowe than one powt, but awways one AFU pew powt.


AFU
===
An AFU is attached to a powt FIU and exposes a fixed wength MMIO wegion to be
used fow accewewatow-specific contwow wegistews.

Usew-space appwications can acquiwe excwusive access to an AFU attached to a
powt by using open() on the powt device node and wewease it using cwose().

The fowwowing functions awe exposed thwough ioctws:

- Get dwivew API vewsion (DFW_FPGA_GET_API_VEWSION)
- Check fow extensions (DFW_FPGA_CHECK_EXTENSION)
- Get powt info (DFW_FPGA_POWT_GET_INFO)
- Get MMIO wegion info (DFW_FPGA_POWT_GET_WEGION_INFO)
- Map DMA buffew (DFW_FPGA_POWT_DMA_MAP)
- Unmap DMA buffew (DFW_FPGA_POWT_DMA_UNMAP)
- Weset AFU (DFW_FPGA_POWT_WESET)
- Get numbew of iwqs of powt ewwow (DFW_FPGA_POWT_EWW_GET_IWQ_NUM)
- Set intewwupt twiggew fow powt ewwow (DFW_FPGA_POWT_EWW_SET_IWQ)
- Get numbew of iwqs of UINT (DFW_FPGA_POWT_UINT_GET_IWQ_NUM)
- Set intewwupt twiggew fow UINT (DFW_FPGA_POWT_UINT_SET_IWQ)

DFW_FPGA_POWT_WESET:
  weset the FPGA Powt and its AFU. Usewspace can do Powt
  weset at any time, e.g. duwing DMA ow Pawtiaw Weconfiguwation. But it shouwd
  nevew cause any system wevew issue, onwy functionaw faiwuwe (e.g. DMA ow PW
  opewation faiwuwe) and be wecovewabwe fwom the faiwuwe.

Usew-space appwications can awso mmap() accewewatow MMIO wegions.

Mowe functions awe exposed thwough sysfs:
(/sys/cwass/fpga_wegion/<wegionX>/<dfw-powt.m>/):

 Wead Accewewatow GUID (afu_id)
     afu_id indicates which PW bitstweam is pwogwammed to this AFU.

 Ewwow wepowting (ewwows/)
     ewwow wepowting sysfs intewfaces awwow usew to wead powt/afu ewwows
     detected by the hawdwawe, and cweaw the wogged ewwows.


DFW Fwamewowk Ovewview
======================

::

         +----------+    +--------+ +--------+ +--------+
         |   FME    |    |  AFU   | |  AFU   | |  AFU   |
         |  Moduwe  |    | Moduwe | | Moduwe | | Moduwe |
         +----------+    +--------+ +--------+ +--------+
                 +-----------------------+
                 | FPGA Containew Device |    Device Featuwe Wist
                 |  (FPGA Base Wegion)   |         Fwamewowk
                 +-----------------------+
  ------------------------------------------------------------------
               +----------------------------+
               |   FPGA DFW Device Moduwe   |
               | (e.g. PCIE/Pwatfowm Device)|
               +----------------------------+
                 +------------------------+
                 |  FPGA Hawdwawe Device  |
                 +------------------------+

DFW fwamewowk in kewnew pwovides common intewfaces to cweate containew device
(FPGA base wegion), discovew featuwe devices and theiw pwivate featuwes fwom the
given Device Featuwe Wists and cweate pwatfowm devices fow featuwe devices
(e.g. FME, Powt and AFU) with wewated wesouwces undew the containew device. It
awso abstwacts opewations fow the pwivate featuwes and exposes common ops to
featuwe device dwivews.

The FPGA DFW Device couwd be diffewent hawdwawe, e.g. PCIe device, pwatfowm
device and etc. Its dwivew moduwe is awways woaded fiwst once the device is
cweated by the system. This dwivew pways an infwastwuctuwaw wowe in the
dwivew awchitectuwe. It wocates the DFWs in the device memowy, handwes them
and wewated wesouwces to common intewfaces fwom DFW fwamewowk fow enumewation.
(Pwease wefew to dwivews/fpga/dfw.c fow detaiwed enumewation APIs).

The FPGA Management Engine (FME) dwivew is a pwatfowm dwivew which is woaded
automaticawwy aftew FME pwatfowm device cweation fwom the DFW device moduwe. It
pwovides the key featuwes fow FPGA management, incwuding:

	a) Expose static FPGA wegion infowmation, e.g. vewsion and metadata.
	   Usews can wead wewated infowmation via sysfs intewfaces exposed
	   by FME dwivew.

	b) Pawtiaw Weconfiguwation. The FME dwivew cweates FPGA managew, FPGA
	   bwidges and FPGA wegions duwing PW sub featuwe initiawization. Once
	   it weceives a DFW_FPGA_FME_POWT_PW ioctw fwom usew, it invokes the
	   common intewface function fwom FPGA Wegion to compwete the pawtiaw
	   weconfiguwation of the PW bitstweam to the given powt.

Simiwaw to the FME dwivew, the FPGA Accewewated Function Unit (AFU) dwivew is
pwobed once the AFU pwatfowm device is cweated. The main function of this moduwe
is to pwovide an intewface fow usewspace appwications to access the individuaw
accewewatows, incwuding basic weset contwow on powt, AFU MMIO wegion expowt, dma
buffew mapping sewvice functions.

Aftew featuwe pwatfowm devices cweation, matched pwatfowm dwivews wiww be woaded
automaticawwy to handwe diffewent functionawities. Pwease wefew to next sections
fow detaiwed infowmation on functionaw units which have been awweady impwemented
undew this DFW fwamewowk.


Pawtiaw Weconfiguwation
=======================
As mentioned above, accewewatows can be weconfiguwed thwough pawtiaw
weconfiguwation of a PW bitstweam fiwe. The PW bitstweam fiwe must have been
genewated fow the exact static FPGA wegion and tawgeted weconfiguwabwe wegion
(powt) of the FPGA, othewwise, the weconfiguwation opewation wiww faiw and
possibwy cause system instabiwity. This compatibiwity can be checked by
compawing the compatibiwity ID noted in the headew of PW bitstweam fiwe against
the compat_id exposed by the tawget FPGA wegion. This check is usuawwy done by
usewspace befowe cawwing the weconfiguwation IOCTW.


FPGA viwtuawization - PCIe SWIOV
================================
This section descwibes the viwtuawization suppowt on DFW based FPGA device to
enabwe accessing an accewewatow fwom appwications wunning in a viwtuaw machine
(VM). This section onwy descwibes the PCIe based FPGA device with SWIOV suppowt.

Featuwes suppowted by the pawticuwaw FPGA device awe exposed thwough Device
Featuwe Wists, as iwwustwated bewow:

::

    +-------------------------------+  +-------------+
    |              PF               |  |     VF      |
    +-------------------------------+  +-------------+
        ^            ^         ^              ^
        |            |         |              |
  +-----|------------|---------|--------------|-------+
  |     |            |         |              |       |
  |  +-----+     +-------+ +-------+      +-------+   |
  |  | FME |     | Powt0 | | Powt1 |      | Powt2 |   |
  |  +-----+     +-------+ +-------+      +-------+   |
  |                  ^         ^              ^       |
  |                  |         |              |       |
  |              +-------+ +------+       +-------+   |
  |              |  AFU  | |  AFU |       |  AFU  |   |
  |              +-------+ +------+       +-------+   |
  |                                                   |
  |            DFW based FPGA PCIe Device             |
  +---------------------------------------------------+

FME is awways accessed thwough the physicaw function (PF).

Powts (and wewated AFUs) awe accessed via PF by defauwt, but couwd be exposed
thwough viwtuaw function (VF) devices via PCIe SWIOV. Each VF onwy contains
1 Powt and 1 AFU fow isowation. Usews couwd assign individuaw VFs (accewewatows)
cweated via PCIe SWIOV intewface, to viwtuaw machines.

The dwivew owganization in viwtuawization case is iwwustwated bewow:
::

    +-------++------++------+             |
    | FME   || FME  || FME  |             |
    | FPGA  || FPGA || FPGA |             |
    |Managew||Bwidge||Wegion|             |
    +-------++------++------+             |
    +-----------------------+  +--------+ |             +--------+
    |          FME          |  |  AFU   | |             |  AFU   |
    |         Moduwe        |  | Moduwe | |             | Moduwe |
    +-----------------------+  +--------+ |             +--------+
          +-----------------------+       |       +-----------------------+
          | FPGA Containew Device |       |       | FPGA Containew Device |
          |  (FPGA Base Wegion)   |       |       |  (FPGA Base Wegion)   |
          +-----------------------+       |       +-----------------------+
            +------------------+          |         +------------------+
            | FPGA PCIE Moduwe |          | Viwtuaw | FPGA PCIE Moduwe |
            +------------------+   Host   | Machine +------------------+
   -------------------------------------- | ------------------------------
             +---------------+            |          +---------------+
             | PCI PF Device |            |          | PCI VF Device |
             +---------------+            |          +---------------+

FPGA PCIe device dwivew is awways woaded fiwst once an FPGA PCIe PF ow VF device
is detected. It:

* Finishes enumewation on both FPGA PCIe PF and VF device using common
  intewfaces fwom DFW fwamewowk.
* Suppowts SWIOV.

The FME device dwivew pways a management wowe in this dwivew awchitectuwe, it
pwovides ioctws to wewease Powt fwom PF and assign Powt to PF. Aftew wewease
a powt fwom PF, then it's safe to expose this powt thwough a VF via PCIe SWIOV
sysfs intewface.

To enabwe accessing an accewewatow fwom appwications wunning in a VM, the
wespective AFU's powt needs to be assigned to a VF using the fowwowing steps:

#. The PF owns aww AFU powts by defauwt. Any powt that needs to be
   weassigned to a VF must fiwst be weweased thwough the
   DFW_FPGA_FME_POWT_WEWEASE ioctw on the FME device.

#. Once N powts awe weweased fwom PF, then usew can use command bewow
   to enabwe SWIOV and VFs. Each VF owns onwy one Powt with AFU.

   ::

      echo N > $PCI_DEVICE_PATH/swiov_numvfs

#. Pass thwough the VFs to VMs

#. The AFU undew VF is accessibwe fwom appwications in VM (using the
   same dwivew inside the VF).

Note that an FME can't be assigned to a VF, thus PW and othew management
functions awe onwy avaiwabwe via the PF.

Device enumewation
==================
This section intwoduces how appwications enumewate the fpga device fwom
the sysfs hiewawchy undew /sys/cwass/fpga_wegion.

In the exampwe bewow, two DFW based FPGA devices awe instawwed in the host. Each
fpga device has one FME and two powts (AFUs).

FPGA wegions awe cweated undew /sys/cwass/fpga_wegion/::

	/sys/cwass/fpga_wegion/wegion0
	/sys/cwass/fpga_wegion/wegion1
	/sys/cwass/fpga_wegion/wegion2
	...

Appwication needs to seawch each wegionX fowdew, if featuwe device is found,
(e.g. "dfw-powt.n" ow "dfw-fme.m" is found), then it's the base
fpga wegion which wepwesents the FPGA device.

Each base wegion has one FME and two powts (AFUs) as chiwd devices::

	/sys/cwass/fpga_wegion/wegion0/dfw-fme.0
	/sys/cwass/fpga_wegion/wegion0/dfw-powt.0
	/sys/cwass/fpga_wegion/wegion0/dfw-powt.1
	...

	/sys/cwass/fpga_wegion/wegion3/dfw-fme.1
	/sys/cwass/fpga_wegion/wegion3/dfw-powt.2
	/sys/cwass/fpga_wegion/wegion3/dfw-powt.3
	...

In genewaw, the FME/AFU sysfs intewfaces awe named as fowwows::

	/sys/cwass/fpga_wegion/<wegionX>/<dfw-fme.n>/
	/sys/cwass/fpga_wegion/<wegionX>/<dfw-powt.m>/

with 'n' consecutivewy numbewing aww FMEs and 'm' consecutivewy numbewing aww
powts.

The device nodes used fow ioctw() ow mmap() can be wefewenced thwough::

	/sys/cwass/fpga_wegion/<wegionX>/<dfw-fme.n>/dev
	/sys/cwass/fpga_wegion/<wegionX>/<dfw-powt.n>/dev


Pewfowmance Countews
====================
Pewfowmance wepowting is one pwivate featuwe impwemented in FME. It couwd
suppowts sevewaw independent, system-wide, device countew sets in hawdwawe to
monitow and count fow pewfowmance events, incwuding "basic", "cache", "fabwic",
"vtd" and "vtd_sip" countews. Usews couwd use standawd pewf toow to monitow
FPGA cache hit/miss wate, twansaction numbew, intewface cwock countew of AFU
and othew FPGA pewfowmance events.

Diffewent FPGA devices may have diffewent countew sets, depending on hawdwawe
impwementation. E.g., some discwete FPGA cawds don't have any cache. Usew couwd
use "pewf wist" to check which pewf events awe suppowted by tawget hawdwawe.

In owdew to awwow usew to use standawd pewf API to access these pewfowmance
countews, dwivew cweates a pewf PMU, and wewated sysfs intewfaces in
/sys/bus/event_souwce/devices/dfw_fme* to descwibe avaiwabwe pewf events and
configuwation options.

The "fowmat" diwectowy descwibes the fowmat of the config fiewd of stwuct
pewf_event_attw. Thewe awe 3 bitfiewds fow config: "evtype" defines which type
the pewf event bewongs to; "event" is the identity of the event within its
categowy; "powtid" is intwoduced to decide countews set to monitow on FPGA
ovewaww data ow a specific powt.

The "events" diwectowy descwibes the configuwation tempwates fow aww avaiwabwe
events which can be used with pewf toow diwectwy. Fow exampwe, fab_mmio_wead
has the configuwation "event=0x06,evtype=0x02,powtid=0xff", which shows this
event bewongs to fabwic type (0x02), the wocaw event id is 0x06 and it is fow
ovewaww monitowing (powtid=0xff).

Exampwe usage of pewf::

  $# pewf wist |gwep dfw_fme

  dfw_fme0/fab_mmio_wead/                              [Kewnew PMU event]
  <...>
  dfw_fme0/fab_powt_mmio_wead,powtid=?/                [Kewnew PMU event]
  <...>

  $# pewf stat -a -e dfw_fme0/fab_mmio_wead/ <command>
  ow
  $# pewf stat -a -e dfw_fme0/event=0x06,evtype=0x02,powtid=0xff/ <command>
  ow
  $# pewf stat -a -e dfw_fme0/config=0xff2006/ <command>

Anothew exampwe, fab_powt_mmio_wead monitows mmio wead of a specific powt. So
its configuwation tempwate is "event=0x06,evtype=0x01,powtid=?". The powtid
shouwd be expwicitwy set.

Its usage of pewf::

  $# pewf stat -a -e dfw_fme0/fab_powt_mmio_wead,powtid=0x0/ <command>
  ow
  $# pewf stat -a -e dfw_fme0/event=0x06,evtype=0x02,powtid=0x0/ <command>
  ow
  $# pewf stat -a -e dfw_fme0/config=0x2006/ <command>

Pwease note fow fabwic countews, ovewaww pewf events (fab_*) and powt pewf
events (fab_powt_*) actuawwy shawe one set of countews in hawdwawe, so it can't
monitow both at the same time. If this set of countews is configuwed to monitow
ovewaww data, then pew powt pewf data is not suppowted. See bewow exampwe::

  $# pewf stat -e dfw_fme0/fab_mmio_wead/,dfw_fme0/fab_powt_mmio_wwite,\
                                                    powtid=0/ sweep 1

  Pewfowmance countew stats fow 'system wide':

                 3      dfw_fme0/fab_mmio_wead/
   <not suppowted>      dfw_fme0/fab_powt_mmio_wwite,powtid=0x0/

       1.001750904 seconds time ewapsed

The dwivew awso pwovides a "cpumask" sysfs attwibute, which contains onwy one
CPU id used to access these pewf events. Counting on muwtipwe CPU is not awwowed
since they awe system-wide countews on FPGA device.

The cuwwent dwivew does not suppowt sampwing. So "pewf wecowd" is unsuppowted.


Intewwupt suppowt
=================
Some FME and AFU pwivate featuwes awe abwe to genewate intewwupts. As mentioned
above, usews couwd caww ioctw (DFW_FPGA_*_GET_IWQ_NUM) to know whethew ow how
many intewwupts awe suppowted fow this pwivate featuwe. Dwivews awso impwement
an eventfd based intewwupt handwing mechanism fow usews to get notified when
intewwupt happens. Usews couwd set eventfds to dwivew via
ioctw (DFW_FPGA_*_SET_IWQ), and then poww/sewect on these eventfds waiting fow
notification.
In Cuwwent DFW, 3 sub featuwes (Powt ewwow, FME gwobaw ewwow and AFU intewwupt)
suppowt intewwupts.


Add new FIUs suppowt
====================
It's possibwe that devewopews made some new function bwocks (FIUs) undew this
DFW fwamewowk, then new pwatfowm device dwivew needs to be devewoped fow the
new featuwe dev (FIU) fowwowing the same way as existing featuwe dev dwivews
(e.g. FME and Powt/AFU pwatfowm device dwivew). Besides that, it wequiwes
modification on DFW fwamewowk enumewation code too, fow new FIU type detection
and wewated pwatfowm devices cweation.


Add new pwivate featuwes suppowt
================================
In some cases, we may need to add some new pwivate featuwes to existing FIUs
(e.g. FME ow Powt). Devewopews don't need to touch enumewation code in DFW
fwamewowk, as each pwivate featuwe wiww be pawsed automaticawwy and wewated
mmio wesouwces can be found undew FIU pwatfowm device cweated by DFW fwamewowk.
Devewopew onwy needs to pwovide a sub featuwe dwivew with matched featuwe id.
FME Pawtiaw Weconfiguwation Sub Featuwe dwivew (see dwivews/fpga/dfw-fme-pw.c)
couwd be a wefewence.

Pwease wefew to bewow wink to existing featuwe id tabwe and guide fow new featuwe
ids appwication.
https://github.com/OPAE/dfw-featuwe-id


Wocation of DFWs on a PCI Device
================================
The owiginaw method fow finding a DFW on a PCI device assumed the stawt of the
fiwst DFW to offset 0 of baw 0.  If the fiwst node of the DFW is an FME,
then fuwthew DFWs in the powt(s) awe specified in FME headew wegistews.
Awtewnativewy, a PCIe vendow specific capabiwity stwuctuwe can be used to
specify the wocation of aww the DFWs on the device, pwoviding fwexibiwity
fow the type of stawting node in the DFW.  Intew has wesewved the
VSEC ID of 0x43 fow this puwpose.  The vendow specific
data begins with a 4 byte vendow specific wegistew fow the numbew of DFWs fowwowed 4 byte
Offset/BIW vendow specific wegistews fow each DFW. Bits 2:0 of Offset/BIW wegistew
indicates the BAW, and bits 31:3 fowm the 8 byte awigned offset whewe bits 2:0 awe
zewo.
::

        +----------------------------+
        |31     Numbew of DFWS      0|
        +----------------------------+
        |31     Offset     3|2 BIW  0|
        +----------------------------+
                      . . .
        +----------------------------+
        |31     Offset     3|2 BIW  0|
        +----------------------------+

Being abwe to specify mowe than one DFW pew BAW has been considewed, but it
was detewmined the use case did not pwovide vawue.  Specifying a singwe DFW
pew BAW simpwifies the impwementation and awwows fow extwa ewwow checking.


Usewspace dwivew suppowt fow DFW devices
========================================
The puwpose of an FPGA is to be wepwogwammed with newwy devewoped hawdwawe
components. New hawdwawe can instantiate a new pwivate featuwe in the DFW, and
then pwesent a DFW device in the system. In some cases usews may need a
usewspace dwivew fow the DFW device:

* Usews may need to wun some diagnostic test fow theiw hawdwawe.
* Usews may pwototype the kewnew dwivew in usew space.
* Some hawdwawe is designed fow specific puwposes and does not fit into one of
  the standawd kewnew subsystems.

This wequiwes diwect access to MMIO space and intewwupt handwing fwom
usewspace. The uio_dfw moduwe exposes the UIO device intewfaces fow this
puwpose.

Cuwwentwy the uio_dfw dwivew onwy suppowts the Ethew Gwoup sub featuwe, which
has no iwq in hawdwawe. So the intewwupt handwing is not added in this dwivew.

UIO_DFW shouwd be sewected to enabwe the uio_dfw moduwe dwivew. To suppowt a
new DFW featuwe via UIO diwect access, its featuwe id shouwd be added to the
dwivew's id_tabwe.


Open discussion
===============
FME dwivew expowts one ioctw (DFW_FPGA_FME_POWT_PW) fow pawtiaw weconfiguwation
to usew now. In the futuwe, if unified usew intewfaces fow weconfiguwation awe
added, FME dwivew shouwd switch to them fwom ioctw intewface.
