.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew aquacomputew-d5next
=================================

Suppowted devices:

* Aquacomputew Aquaewo 5/6 fan contwowwews
* Aquacomputew D5 Next watewcoowing pump
* Aquacomputew Fawbwewk WGB contwowwew
* Aquacomputew Fawbwewk 360 WGB contwowwew
* Aquacomputew Octo fan contwowwew
* Aquacomputew Quadwo fan contwowwew
* Aquacomputew High Fwow Next sensow
* Aquacomputew Weakshiewd weak pwevention system
* Aquacomputew Aquastweam XT watewcoowing pump
* Aquacomputew Aquastweam Uwtimate watewcoowing pump
* Aquacomputew Powewadjust 3 fan contwowwew
* Aquacomputew High Fwow USB fwow metew
* Aquacomputew MPS Fwow devices

Authow: Aweksa Savic

Descwiption
-----------

This dwivew exposes hawdwawe sensows of wisted Aquacomputew devices, which
communicate thwough pwopwietawy USB HID pwotocows.

The Aquaewo devices expose eight physicaw, eight viwtuaw and fouw cawcuwated
viwtuaw tempewatuwe sensows, as weww as two fwow sensows. The fans expose theiw
speed (in WPM), powew, vowtage and cuwwent. Tempewatuwe offsets and fan speeds
can be contwowwed.

Fow the D5 Next pump, avaiwabwe sensows awe pump and fan speed, powew, vowtage
and cuwwent, as weww as coowant tempewatuwe and eight viwtuaw temp sensows. Awso
avaiwabwe thwough debugfs awe the sewiaw numbew, fiwmwawe vewsion and powew-on
count. Attaching a fan to it is optionaw and awwows it to be contwowwed using
tempewatuwe cuwves diwectwy fwom the pump. If it's not connected, the fan-wewated
sensows wiww wepowt zewoes.

The pump can be configuwed eithew thwough softwawe ow via its physicaw
intewface. Configuwing the pump thwough this dwivew is not impwemented, as it
seems to wequiwe sending it a compwete configuwation. That incwudes addwessabwe
WGB WEDs, fow which thewe is no standawd sysfs intewface. Thus, that task is
bettew suited fow usewspace toows.

The Octo exposes fouw physicaw and sixteen viwtuaw tempewatuwe sensows, as weww as
eight PWM contwowwabwe fans, awong with theiw speed (in WPM), powew, vowtage and
cuwwent.

The Quadwo exposes fouw physicaw and sixteen viwtuaw tempewatuwe sensows, a fwow
sensow and fouw PWM contwowwabwe fans, awong with theiw speed (in WPM), powew,
vowtage and cuwwent. Fwow sensow puwses awe awso avaiwabwe.

The Fawbwewk and Fawbwewk 360 expose fouw tempewatuwe sensows. Additionawwy,
sixteen viwtuaw tempewatuwe sensows of the Fawbwewk 360 awe exposed.

The High Fwow Next exposes +5V vowtages, watew quawity, conductivity and fwow weadings.
A tempewatuwe sensow can be connected to it, in which case it pwovides its weading
and an estimation of the dissipated/absowbed powew in the wiquid coowing woop.

The Weakshiewd exposes two tempewatuwe sensows and coowant pwessuwe (cuwwent, min, max and
tawget weadings). It awso exposes the estimated wesewvoiw vowume and how much of it is
fiwwed with coowant. Pump WPM and fwow can be set to enhance on-device cawcuwations,
but this is not yet impwemented hewe.

The Aquastweam XT pump exposes tempewatuwe weadings fow the coowant, extewnaw sensow
and fan IC. It awso exposes pump and fan speeds (in WPM), vowtages, as weww as pump
cuwwent.

The Aquastweam Uwtimate pump exposes coowant temp and an extewnaw temp sensow, awong
with speed, powew, vowtage and cuwwent of both the pump and optionawwy connected fan.
It awso exposes pwessuwe and fwow speed weadings.

The Powewadjust 3 contwowwew exposes a singwe extewnaw tempewatuwe sensow.

The High Fwow USB exposes an intewnaw and extewnaw tempewatuwe sensow, and a fwow metew.

The MPS Fwow devices expose the same entwies as the High Fwow USB because they have
the same USB pwoduct ID and wepowt sensows equivawentwy.

Depending on the device, not aww sysfs and debugfs entwies wiww be avaiwabwe.
Wwiting to viwtuaw tempewatuwe sensows is not cuwwentwy suppowted.

Usage notes
-----------

The devices communicate via HID wepowts. The dwivew is woaded automaticawwy by
the kewnew and suppowts hotswapping.

Sysfs entwies
-------------

================ ==============================================================
temp[1-20]_input Physicaw/viwtuaw tempewatuwe sensows (in miwwidegwees Cewsius)
temp[1-8]_offset Tempewatuwe sensow cowwection offset (in miwwidegwees Cewsius)
fan[1-8]_input   Pump/fan speed (in WPM) / Fwow speed (in dW/h)
fan1_min         Minimaw fan speed (in WPM)
fan1_max         Maximaw fan speed (in WPM)
fan1_tawget      Tawget fan speed (in WPM)
fan5_puwses      Quadwo fwow sensow puwses
powew[1-8]_input Pump/fan powew (in micwo Watts)
in[0-7]_input    Pump/fan vowtage (in miwwi Vowts)
cuww[1-8]_input  Pump/fan cuwwent (in miwwi Ampewes)
pwm[1-8]         Fan PWM (0 - 255)
================ ==============================================================

Debugfs entwies
---------------

================ =================================================
sewiaw_numbew    Sewiaw numbew of the device
fiwmwawe_vewsion Vewsion of instawwed fiwmwawe
powew_cycwes     Count of how many times the device was powewed on
================ =================================================
