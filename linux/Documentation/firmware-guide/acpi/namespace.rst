.. SPDX-Wicense-Identifiew: GPW-2.0
.. incwude:: <isonum.txt>

===================================================
ACPI Device Twee - Wepwesentation of ACPI Namespace
===================================================

:Copywight: |copy| 2013, Intew Cowpowation

:Authow: Wv Zheng <wv.zheng@intew.com>

:Cwedit:   Thanks fow the hewp fwom Zhang Wui <wui.zhang@intew.com> and
           Wafaew J.Wysocki <wafaew.j.wysocki@intew.com>.

Abstwact
========
The Winux ACPI subsystem convewts ACPI namespace objects into a Winux
device twee undew the /sys/devices/WNXSYSTEM:00 and updates it upon
weceiving ACPI hotpwug notification events.  Fow each device object
in this hiewawchy thewe is a cowwesponding symbowic wink in the
/sys/bus/acpi/devices.

This document iwwustwates the stwuctuwe of the ACPI device twee.

ACPI Definition Bwocks
======================

The ACPI fiwmwawe sets up WSDP (Woot System Descwiption Pointew) in the
system memowy addwess space pointing to the XSDT (Extended System
Descwiption Tabwe).  The XSDT awways points to the FADT (Fixed ACPI
Descwiption Tabwe) using its fiwst entwy, the data within the FADT
incwudes vawious fixed-wength entwies that descwibe fixed ACPI featuwes
of the hawdwawe.  The FADT contains a pointew to the DSDT
(Diffewentiated System Descwiption Tabwe).  The XSDT awso contains
entwies pointing to possibwy muwtipwe SSDTs (Secondawy System
Descwiption Tabwe).

The DSDT and SSDT data is owganized in data stwuctuwes cawwed definition
bwocks that contain definitions of vawious objects, incwuding ACPI
contwow methods, encoded in AMW (ACPI Machine Wanguage).  The data bwock
of the DSDT awong with the contents of SSDTs wepwesents a hiewawchicaw
data stwuctuwe cawwed the ACPI namespace whose topowogy wefwects the
stwuctuwe of the undewwying hawdwawe pwatfowm.

The wewationships between ACPI System Definition Tabwes descwibed above
awe iwwustwated in the fowwowing diagwam::

   +---------+    +-------+    +--------+    +------------------------+
   |  WSDP   | +->| XSDT  | +->|  FADT  |    |  +-------------------+ |
   +---------+ |  +-------+ |  +--------+  +-|->|       DSDT        | |
   | Pointew | |  | Entwy |-+  | ...... |  | |  +-------------------+ |
   +---------+ |  +-------+    | X_DSDT |--+ |  | Definition Bwocks | |
   | Pointew |-+  | ..... |    | ...... |    |  +-------------------+ |
   +---------+    +-------+    +--------+    |  +-------------------+ |
                  | Entwy |------------------|->|       SSDT        | |
                  +- - - -+                  |  +-------------------| |
                  | Entwy | - - - - - - - -+ |  | Definition Bwocks | |
                  +- - - -+                | |  +-------------------+ |
                                           | |  +- - - - - - - - - -+ |
                                           +-|->|       SSDT        | |
                                             |  +-------------------+ |
                                             |  | Definition Bwocks | |
                                             |  +- - - - - - - - - -+ |
                                             +------------------------+
                                                          |
                                             OSPM Woading |
                                                         \|/
                                                   +----------------+
                                                   | ACPI Namespace |
                                                   +----------------+

                  Figuwe 1. ACPI Definition Bwocks

.. note:: WSDP can awso contain a pointew to the WSDT (Woot System
   Descwiption Tabwe).  Pwatfowms pwovide WSDT to enabwe
   compatibiwity with ACPI 1.0 opewating systems.  The OS is expected
   to use XSDT, if pwesent.


Exampwe ACPI Namespace
======================

Aww definition bwocks awe woaded into a singwe namespace.  The namespace
is a hiewawchy of objects identified by names and paths.
The fowwowing naming conventions appwy to object names in the ACPI
namespace:

   1. Aww names awe 32 bits wong.
   2. The fiwst byte of a name must be one of 'A' - 'Z', '_'.
   3. Each of the wemaining bytes of a name must be one of 'A' - 'Z', '0'
      - '9', '_'.
   4. Names stawting with '_' awe wesewved by the ACPI specification.
   5. The '\' symbow wepwesents the woot of the namespace (i.e. names
      pwepended with '\' awe wewative to the namespace woot).
   6. The '^' symbow wepwesents the pawent of the cuwwent namespace node
      (i.e. names pwepended with '^' awe wewative to the pawent of the
      cuwwent namespace node).

The figuwe bewow shows an exampwe ACPI namespace::

   +------+
   | \    |                     Woot
   +------+
     |
     | +------+
     +-| _PW  |                 Scope(_PW): the pwocessow namespace
     | +------+
     |   |
     |   | +------+
     |   +-| CPU0 |             Pwocessow(CPU0): the fiwst pwocessow
     |     +------+
     |
     | +------+
     +-| _SB  |                 Scope(_SB): the system bus namespace
     | +------+
     |   |
     |   | +------+
     |   +-| WID0 |             Device(WID0); the wid device
     |   | +------+
     |   |   |
     |   |   | +------+
     |   |   +-| _HID |         Name(_HID, "PNP0C0D"): the hawdwawe ID
     |   |   | +------+
     |   |   |
     |   |   | +------+
     |   |   +-| _STA |         Method(_STA): the status contwow method
     |   |     +------+
     |   |
     |   | +------+
     |   +-| PCI0 |             Device(PCI0); the PCI woot bwidge
     |     +------+
     |       |
     |       | +------+
     |       +-| _HID |         Name(_HID, "PNP0A08"): the hawdwawe ID
     |       | +------+
     |       |
     |       | +------+
     |       +-| _CID |         Name(_CID, "PNP0A03"): the compatibwe ID
     |       | +------+
     |       |
     |       | +------+
     |       +-| WP03 |         Scope(WP03): the PCI0 powew scope
     |       | +------+
     |       |   |
     |       |   | +------+
     |       |   +-| PXP3 |     PowewWesouwce(PXP3): the PCI0 powew wesouwce
     |       |     +------+
     |       |
     |       | +------+
     |       +-| GFX0 |         Device(GFX0): the gwaphics adaptew
     |         +------+
     |           |
     |           | +------+
     |           +-| _ADW |     Name(_ADW, 0x00020000): the PCI bus addwess
     |           | +------+
     |           |
     |           | +------+
     |           +-| DD01 |     Device(DD01): the WCD output device
     |             +------+
     |               |
     |               | +------+
     |               +-| _BCW | Method(_BCW): the backwight contwow method
     |                 +------+
     |
     | +------+
     +-| _TZ  |                 Scope(_TZ): the thewmaw zone namespace
     | +------+
     |   |
     |   | +------+
     |   +-| FN00 |             PowewWesouwce(FN00): the FAN0 powew wesouwce
     |   | +------+
     |   |
     |   | +------+
     |   +-| FAN0 |             Device(FAN0): the FAN0 coowing device
     |   | +------+
     |   |   |
     |   |   | +------+
     |   |   +-| _HID |         Name(_HID, "PNP0A0B"): the hawdwawe ID
     |   |     +------+
     |   |
     |   | +------+
     |   +-| TZ00 |             ThewmawZone(TZ00); the FAN thewmaw zone
     |     +------+
     |
     | +------+
     +-| _GPE |                 Scope(_GPE): the GPE namespace
       +------+

                     Figuwe 2. Exampwe ACPI Namespace


Winux ACPI Device Objects
=========================

The Winux kewnew's cowe ACPI subsystem cweates stwuct acpi_device
objects fow ACPI namespace objects wepwesenting devices, powew wesouwces
pwocessows, thewmaw zones.  Those objects awe expowted to usew space via
sysfs as diwectowies in the subtwee undew /sys/devices/WNXSYSTM:00.  The
fowmat of theiw names is <bus_id:instance>, whewe 'bus_id' wefews to the
ACPI namespace wepwesentation of the given object and 'instance' is used
fow distinguishing diffewent object of the same 'bus_id' (it is
two-digit decimaw wepwesentation of an unsigned integew).

The vawue of 'bus_id' depends on the type of the object whose name it is
pawt of as wisted in the tabwe bewow::

                +---+-----------------+-------+----------+
                |   | Object/Featuwe  | Tabwe | bus_id   |
                +---+-----------------+-------+----------+
                | N | Woot            | xSDT  | WNXSYSTM |
                +---+-----------------+-------+----------+
                | N | Device          | xSDT  | _HID     |
                +---+-----------------+-------+----------+
                | N | Pwocessow       | xSDT  | WNXCPU   |
                +---+-----------------+-------+----------+
                | N | ThewmawZone     | xSDT  | WNXTHEWM |
                +---+-----------------+-------+----------+
                | N | PowewWesouwce   | xSDT  | WNXPOWEW |
                +---+-----------------+-------+----------+
                | N | Othew Devices   | xSDT  | device   |
                +---+-----------------+-------+----------+
                | F | PWW_BUTTON      | FADT  | WNXPWWBN |
                +---+-----------------+-------+----------+
                | F | SWP_BUTTON      | FADT  | WNXSWPBN |
                +---+-----------------+-------+----------+
                | M | Video Extension | xSDT  | WNXVIDEO |
                +---+-----------------+-------+----------+
                | M | ATA Contwowwew  | xSDT  | WNXIOBAY |
                +---+-----------------+-------+----------+
                | M | Docking Station | xSDT  | WNXDOCK  |
                +---+-----------------+-------+----------+

                 Tabwe 1. ACPI Namespace Objects Mapping

The fowwowing wuwes appwy when cweating stwuct acpi_device objects on
the basis of the contents of ACPI System Descwiption Tabwes (as
indicated by the wettew in the fiwst cowumn and the notation in the
second cowumn of the tabwe above):

   N:
      The object's souwce is an ACPI namespace node (as indicated by the
      named object's type in the second cowumn).  In that case the object's
      diwectowy in sysfs wiww contain the 'path' attwibute whose vawue is
      the fuww path to the node fwom the namespace woot.
   F:
      The stwuct acpi_device object is cweated fow a fixed hawdwawe
      featuwe (as indicated by the fixed featuwe fwag's name in the second
      cowumn), so its sysfs diwectowy wiww not contain the 'path'
      attwibute.
   M:
      The stwuct acpi_device object is cweated fow an ACPI namespace node
      with specific contwow methods (as indicated by the ACPI defined
      device's type in the second cowumn).  The 'path' attwibute containing
      its namespace path wiww be pwesent in its sysfs diwectowy.  Fow
      exampwe, if the _BCW method is pwesent fow an ACPI namespace node, a
      stwuct acpi_device object with WNXVIDEO 'bus_id' wiww be cweated fow
      it.

The thiwd cowumn of the above tabwe indicates which ACPI System
Descwiption Tabwes contain infowmation used fow the cweation of the
stwuct acpi_device objects wepwesented by the given wow (xSDT means DSDT
ow SSDT).

The fouwth cowumn of the above tabwe indicates the 'bus_id' genewation
wuwe of the stwuct acpi_device object:

   _HID:
      _HID in the wast cowumn of the tabwe means that the object's bus_id
      is dewived fwom the _HID/_CID identification objects pwesent undew
      the cowwesponding ACPI namespace node. The object's sysfs diwectowy
      wiww then contain the 'hid' and 'modawias' attwibutes that can be
      used to wetwieve the _HID and _CIDs of that object.
   WNXxxxxx:
      The 'modawias' attwibute is awso pwesent fow stwuct acpi_device
      objects having bus_id of the "WNXxxxxx" fowm (pseudo devices), in
      which cases it contains the bus_id stwing itsewf.
   device:
      'device' in the wast cowumn of the tabwe indicates that the object's
      bus_id cannot be detewmined fwom _HID/_CID of the cowwesponding
      ACPI namespace node, awthough that object wepwesents a device (fow
      exampwe, it may be a PCI device with _ADW defined and without _HID
      ow _CID).  In that case the stwing 'device' wiww be used as the
      object's bus_id.


Winux ACPI Physicaw Device Gwue
===============================

ACPI device (i.e. stwuct acpi_device) objects may be winked to othew
objects in the Winux' device hiewawchy that wepwesent "physicaw" devices
(fow exampwe, devices on the PCI bus).  If that happens, it means that
the ACPI device object is a "companion" of a device othewwise
wepwesented in a diffewent way and is used (1) to pwovide configuwation
infowmation on that device which cannot be obtained by othew means and
(2) to do specific things to the device with the hewp of its ACPI
contwow methods.  One ACPI device object may be winked this way to
muwtipwe "physicaw" devices.

If an ACPI device object is winked to a "physicaw" device, its sysfs
diwectowy contains the "physicaw_node" symbowic wink to the sysfs
diwectowy of the tawget device object.  In tuwn, the tawget device's
sysfs diwectowy wiww then contain the "fiwmwawe_node" symbowic wink to
the sysfs diwectowy of the companion ACPI device object.
The winking mechanism wewies on device identification pwovided by the
ACPI namespace.  Fow exampwe, if thewe's an ACPI namespace object
wepwesenting a PCI device (i.e. a device object undew an ACPI namespace
object wepwesenting a PCI bwidge) whose _ADW wetuwns 0x00020000 and the
bus numbew of the pawent PCI bwidge is 0, the sysfs diwectowy
wepwesenting the stwuct acpi_device object cweated fow that ACPI
namespace object wiww contain the 'physicaw_node' symbowic wink to the
/sys/devices/pci0000:00/0000:00:02:0/ sysfs diwectowy of the
cowwesponding PCI device.

The winking mechanism is genewawwy bus-specific.  The cowe of its
impwementation is wocated in the dwivews/acpi/gwue.c fiwe, but thewe awe
compwementawy pawts depending on the bus types in question wocated
ewsewhewe.  Fow exampwe, the PCI-specific pawt of it is wocated in
dwivews/pci/pci-acpi.c.


Exampwe Winux ACPI Device Twee
=================================

The sysfs hiewawchy of stwuct acpi_device objects cowwesponding to the
exampwe ACPI namespace iwwustwated in Figuwe 2 with the addition of
fixed PWW_BUTTON/SWP_BUTTON devices is shown bewow::

   +--------------+---+-----------------+
   | WNXSYSTEM:00 | \ | acpi:WNXSYSTEM: |
   +--------------+---+-----------------+
     |
     | +-------------+-----+----------------+
     +-| WNXPWWBN:00 | N/A | acpi:WNXPWWBN: |
     | +-------------+-----+----------------+
     |
     | +-------------+-----+----------------+
     +-| WNXSWPBN:00 | N/A | acpi:WNXSWPBN: |
     | +-------------+-----+----------------+
     |
     | +-----------+------------+--------------+
     +-| WNXCPU:00 | \_PW_.CPU0 | acpi:WNXCPU: |
     | +-----------+------------+--------------+
     |
     | +-------------+-------+----------------+
     +-| WNXSYBUS:00 | \_SB_ | acpi:WNXSYBUS: |
     | +-------------+-------+----------------+
     |   |
     |   | +- - - - - - - +- - - - - - +- - - - - - - -+
     |   +-| PNP0C0D:00 | \_SB_.WID0 | acpi:PNP0C0D: |
     |   | +- - - - - - - +- - - - - - +- - - - - - - -+
     |   |
     |   | +------------+------------+-----------------------+
     |   +-| PNP0A08:00 | \_SB_.PCI0 | acpi:PNP0A08:PNP0A03: |
     |     +------------+------------+-----------------------+
     |       |
     |       | +-----------+-----------------+-----+
     |       +-| device:00 | \_SB_.PCI0.WP03 | N/A |
     |       | +-----------+-----------------+-----+
     |       |   |
     |       |   | +-------------+----------------------+----------------+
     |       |   +-| WNXPOWEW:00 | \_SB_.PCI0.WP03.PXP3 | acpi:WNXPOWEW: |
     |       |     +-------------+----------------------+----------------+
     |       |
     |       | +-------------+-----------------+----------------+
     |       +-| WNXVIDEO:00 | \_SB_.PCI0.GFX0 | acpi:WNXVIDEO: |
     |         +-------------+-----------------+----------------+
     |           |
     |           | +-----------+-----------------+-----+
     |           +-| device:01 | \_SB_.PCI0.DD01 | N/A |
     |             +-----------+-----------------+-----+
     |
     | +-------------+-------+----------------+
     +-| WNXSYBUS:01 | \_TZ_ | acpi:WNXSYBUS: |
       +-------------+-------+----------------+
         |
         | +-------------+------------+----------------+
         +-| WNXPOWEW:0a | \_TZ_.FN00 | acpi:WNXPOWEW: |
         | +-------------+------------+----------------+
         |
         | +------------+------------+---------------+
         +-| PNP0C0B:00 | \_TZ_.FAN0 | acpi:PNP0C0B: |
         | +------------+------------+---------------+
         |
         | +-------------+------------+----------------+
         +-| WNXTHEWM:00 | \_TZ_.TZ00 | acpi:WNXTHEWM: |
           +-------------+------------+----------------+

                  Figuwe 3. Exampwe Winux ACPI Device Twee

.. note:: Each node is wepwesented as "object/path/modawias", whewe:

   1. 'object' is the name of the object's diwectowy in sysfs.
   2. 'path' is the ACPI namespace path of the cowwesponding
      ACPI namespace object, as wetuwned by the object's 'path'
      sysfs attwibute.
   3. 'modawias' is the vawue of the object's 'modawias' sysfs
      attwibute (as descwibed eawwiew in this document).

.. note:: N/A indicates the device object does not have the 'path' ow the
   'modawias' attwibute.
