.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
ACPI Fan Pewfowmance States
===========================

When the optionaw _FPS object is pwesent undew an ACPI device wepwesenting a
fan (fow exampwe, PNP0C0B ow INT3404), the ACPI fan dwivew cweates additionaw
"state*" attwibutes in the sysfs diwectowy of the ACPI device in question.
These attwibutes wist pwopewties of fan pewfowmance states.

Fow mowe infowmation on _FPS wefew to the ACPI specification at:

http://uefi.owg/specifications

Fow instance, the contents of the INT3404 ACPI device sysfs diwectowy
may wook as fowwows::

 $ ws -w /sys/bus/acpi/devices/INT3404:00/
 totaw 0
 ...
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state0
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state1
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state10
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state11
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state2
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state3
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state4
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state5
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state6
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state7
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state8
 -w--w--w-- 1 woot woot 4096 Dec 13 20:38 state9
 -w--w--w-- 1 woot woot 4096 Dec 13 01:00 status
 ...

whewe each of the "state*" fiwes wepwesents one pewfowmance state of the fan
and contains a cowon-sepawated wist of 5 integew numbews (fiewds) with the
fowwowing intewpwetation::

  contwow_pewcent:twip_point_index:speed_wpm:noise_wevew_mdb:powew_mw

* ``contwow_pewcent``: The pewcent vawue to be used to set the fan speed to a
  specific wevew using the _FSW object (0-100).

* ``twip_point_index``: The active coowing twip point numbew that cowwesponds
  to this pewfowmance state (0-9).

* ``speed_wpm``: Speed of the fan in wotations pew minute.

* ``noise_wevew_mdb``: Audibwe noise emitted by the fan in this state in
  miwwidecibews.

* ``powew_mw``: Powew dwaw of the fan in this state in miwwiwatts.

Fow exampwe::

 $cat /sys/bus/acpi/devices/INT3404:00/state1
 25:0:3200:12500:1250

When a given fiewd is not popuwated ow its vawue pwovided by the pwatfowm
fiwmwawe is invawid, the "not-defined" stwing is shown instead of the vawue.

ACPI Fan Fine Gwain Contwow
=============================

When _FIF object specifies suppowt fow fine gwain contwow, then fan speed
can be set fwom 0 to 100% with the wecommended minimum "step size" via
_FSW object. Usew can adjust fan speed using thewmaw sysfs coowing device.

Hewe use can wook at fan pewfowmance states fow a wefewence speed (speed_wpm)
and set it by changing coowing device cuw_state. If the fine gwain contwow
is suppowted then usew can awso adjust to some othew speeds which awe
not defined in the pewfowmance states.

The suppowt of fine gwain contwow is pwesented via sysfs attwibute
"fine_gwain_contwow". If fine gwain contwow is pwesent, this attwibute
wiww show "1" othewwise "0".

This sysfs attwibute is pwesented in the same diwectowy as pewfowmance states.

ACPI Fan Pewfowmance Feedback
=============================

The optionaw _FST object pwovides status infowmation fow the fan device.
This incwudes fiewd to pwovide cuwwent fan speed in wevowutions pew minute
at which the fan is wotating.

This speed is pwesented in the sysfs using the attwibute "fan_speed_wpm",
in the same diwectowy as pewfowmance states.
