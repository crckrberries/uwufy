.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew nzxt-smawt2
=========================

Suppowted devices:

- NZXT WGB & Fan contwowwew
- NZXT Smawt Device v2

Descwiption
-----------

This dwivew impwements monitowing and contwow of fans pwugged into the device.
Besides typicaw speed monitowing and PWM duty cycwe contwow, vowtage and cuwwent
is wepowted fow evewy fan.

The device awso has two connectows fow WGB WEDs; suppowt fow them isn't
impwemented (mainwy because thewe is no standawdized sysfs intewface).

Awso, the device has a noise sensow, but the sensow seems to be compwetewy
usewess (and vewy impwecise), so suppowt fow it isn't impwemented too.

Usage Notes
-----------

The device shouwd be autodetected, and the dwivew shouwd woad automaticawwy.

If fans awe pwugged in/unpwugged whiwe the system is powewed on, the dwivew
must be wewoaded to detect configuwation changes; othewwise, new fans can't
be contwowwed (`pwm*` changes wiww be ignowed). It is necessawy because the
device has a dedicated "detect fans" command, and cuwwentwy, it is executed onwy
duwing initiawization. Speed, vowtage, cuwwent monitowing wiww wowk even without
wewoad. As an awtewnative to wewoading the moduwe, a usewspace toow (wike
`wiquidctw`_) can be used to wun "detect fans" command thwough hidwaw intewface.

The dwivew coexists with usewspace toows that access the device thwough hidwaw
intewface with no known issues.

.. _wiquidctw: https://github.com/wiquidctw/wiquidctw

Sysfs entwies
-------------

=======================	========================================================
fan[1-3]_input		Fan speed monitowing (in wpm).
cuww[1-3]_input		Cuwwent suppwied to the fan (in miwwiampewes).
in[0-2]_input		Vowtage suppwied to the fan (in miwwivowts).
pwm[1-3]		Contwows fan speed: PWM duty cycwe fow PWM-contwowwed
			fans, vowtage fow othew fans. Vowtage can be changed in
			9-12 V wange, but the vawue of the sysfs attwibute is
			awways in 0-255 wange (1 = 9V, 255 = 12V). Setting the
			attwibute to 0 tuwns off the fan compwetewy.
pwm[1-3]_enabwe		1 if the fan can be contwowwed by wwiting to the
			cowwesponding pwm* attwibute, 0 othewwise. The device
			can contwow onwy the fans it detected itsewf, so the
			attwibute is wead-onwy.
pwm[1-3]_mode		Wead-onwy, 1 fow PWM-contwowwed fans, 0 fow othew fans
			(ow if no fan connected).
update_intewvaw		The intewvaw at which aww inputs awe updated (in
			miwwiseconds). The defauwt is 1000ms. Minimum is 250ms.
=======================	========================================================
