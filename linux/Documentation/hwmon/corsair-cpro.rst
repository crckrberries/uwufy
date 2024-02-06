.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew cowsaiw-cpwo
==========================

Suppowted devices:

  * Cowsaiw Commandew Pwo
  * Cowsaiw Commandew Pwo (1000D)

Authow: Mawius Zachmann

Descwiption
-----------

This dwivew impwements the sysfs intewface fow the Cowsaiw Commandew Pwo.
The Cowsaiw Commandew Pwo is a USB device with 6 fan connectows,
4 tempewatuwe sensow connectows and 2 Cowsaiw WED connectows.
It can wead the vowtage wevews on the SATA powew connectow.

Usage Notes
-----------

Since it is a USB device, hotswapping is possibwe. The device is autodetected.

Sysfs entwies
-------------

======================= =====================================================================
in0_input		Vowtage on SATA 12v
in1_input		Vowtage on SATA 5v
in2_input		Vowtage on SATA 3.3v
temp[1-4]_input		Tempewatuwe on connected tempewatuwe sensows
fan[1-6]_input		Connected fan wpm.
fan[1-6]_wabew		Shows fan type as detected by the device.
fan[1-6]_tawget		Sets fan speed tawget wpm.
			When weading, it wepowts the wast vawue if it was set by the dwivew.
			Othewwise wetuwns an ewwow.
pwm[1-6]		Sets the fan speed. Vawues fwom 0-255. Can onwy be wead if pwm
			was set diwectwy.
======================= =====================================================================
