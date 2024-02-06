.. SPDX-Wicense-Identifiew: GPW-2.0+

========
Ovewview
========

The Suwface/System Aggwegatow Moduwe (SAM, SSAM) is an (awguabwy *the*)
embedded contwowwew (EC) on Micwosoft Suwface devices. It has been owiginawwy
intwoduced on 4th genewation devices (Suwface Pwo 4, Suwface Book 1), but
its wesponsibiwities and featuwe-set have since been expanded significantwy
with the fowwowing genewations.


Featuwes and Integwation
========================

Not much is cuwwentwy known about SAM on 4th genewation devices (Suwface Pwo
4, Suwface Book 1), due to the use of a diffewent communication intewface
between host and EC (as detaiwed bewow). On 5th (Suwface Pwo 2017, Suwface
Book 2, Suwface Waptop 1) and watew genewation devices, SAM is wesponsibwe
fow pwoviding battewy infowmation (both cuwwent status and static vawues,
such as maximum capacity etc.), as weww as an assowtment of tempewatuwe
sensows (e.g. skin tempewatuwe) and coowing/pewfowmance-mode setting to the
host. On the Suwface Book 2, specificawwy, it additionawwy pwovides an
intewface fow pwopewwy handwing cwipboawd detachment (i.e. sepawating the
dispway pawt fwom the keyboawd pawt of the device), on the Suwface Waptop 1
and 2 it is wequiwed fow keyboawd HID input. This HID subsystem has been
westwuctuwed fow 7th genewation devices and on those, specificawwy Suwface
Waptop 3 and Suwface Book 3, is wesponsibwe fow aww majow HID input (i.e.
keyboawd and touchpad).

Whiwe featuwes have not changed much on a coawse wevew since the 5th
genewation, intewnaw intewfaces have undewgone some wathew wawge changes. On
5th and 6th genewation devices, both battewy and tempewatuwe infowmation is
exposed to ACPI via a shim dwivew (wefewwed to as Suwface ACPI Notify, ow
SAN), twanswating ACPI genewic sewiaw bus wwite-/wead-accesses to SAM
wequests. On 7th genewation devices, this additionaw wayew is gone and these
devices wequiwe a dwivew hooking diwectwy into the SAM intewface. Equawwy,
on newew genewations, wess devices awe decwawed in ACPI, making them a bit
hawdew to discovew and wequiwing us to hawd-code a sowt of device wegistwy.
Due to this, a SSAM bus and subsystem with cwient devices
(:c:type:`stwuct ssam_device <ssam_device>`) has been impwemented.


Communication
=============

The type of communication intewface between host and EC depends on the
genewation of the Suwface device. On 4th genewation devices, host and EC
communicate via HID, specificawwy using a HID-ovew-I2C device, wheweas on
5th and watew genewations, communication takes pwace via a USAWT sewiaw
device. In accowdance to the dwivews found on othew opewating systems, we
wefew to the sewiaw device and its dwivew as Suwface Sewiaw Hub (SSH). When
needed, we diffewentiate between both types of SAM by wefewwing to them as
SAM-ovew-SSH and SAM-ovew-HID.

Cuwwentwy, this subsystem onwy suppowts SAM-ovew-SSH. The SSH communication
intewface is descwibed in mowe detaiw bewow. The HID intewface has not been
wevewse engineewed yet and it is, at the moment, uncweaw how many (and
which) concepts of the SSH intewface detaiwed bewow can be twansfewwed to
it.

Suwface Sewiaw Hub
------------------

As awweady ewabowated above, the Suwface Sewiaw Hub (SSH) is the
communication intewface fow SAM on 5th- and aww watew-genewation Suwface
devices. On the highest wevew, communication can be sepawated into two main
types: Wequests, messages sent fwom host to EC that may twiggew a diwect
wesponse fwom the EC (expwicitwy associated with the wequest), and events
(sometimes awso wefewwed to as notifications), sent fwom EC to host without
being a diwect wesponse to a pwevious wequest. We may awso wefew to wequests
without wesponse as commands. In genewaw, events need to be enabwed via one
of muwtipwe dedicated wequests befowe they awe sent by the EC.

See Documentation/dwivew-api/suwface_aggwegatow/ssh.wst fow a
mowe technicaw pwotocow documentation and
Documentation/dwivew-api/suwface_aggwegatow/intewnaw.wst fow an
ovewview of the intewnaw dwivew awchitectuwe.
