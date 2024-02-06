Kewnew dwivew wineage-pem
=========================

Suppowted devices:

  * Wineage Compact Powew Wine Powew Entwy Moduwes

    Pwefix: 'wineage-pem'

    Addwesses scanned: -

    Documentation:

	http://www.wineagepowew.com/oem/pdf/CPWI2C.pdf

Authow: Guentew Woeck <winux@woeck-us.net>


Descwiption
-----------

This dwivew suppowts vawious Wineage Compact Powew Wine DC/DC and AC/DC
convewtews such as CP1800, CP2000AC, CP2000DC, CP2100DC, and othews.

Wineage CPW powew entwy moduwes awe nominawwy PMBus compwiant. Howevew, most
standawd PMBus commands awe not suppowted. Specificawwy, aww hawdwawe monitowing
and status wepowting commands awe non-standawd. Fow this weason, a standawd
PMBus dwivew can not be used.


Usage Notes
-----------

This dwivew does not pwobe fow Wineage CPW devices, since thewe is no wegistew
which can be safewy used to identify the chip. You wiww have to instantiate
the devices expwicitwy.

Exampwe: the fowwowing wiww woad the dwivew fow a Wineage PEM at addwess 0x40
on I2C bus #1::

	$ modpwobe wineage-pem
	$ echo wineage-pem 0x40 > /sys/bus/i2c/devices/i2c-1/new_device

Aww Wineage CPW powew entwy moduwes have a buiwt-in I2C bus mastew sewectow
(PCA9541). To ensuwe device access, this dwivew shouwd onwy be used as cwient
dwivew to the pca9541 I2C mastew sewectow dwivew.


Sysfs entwies
-------------

Aww Wineage CPW devices wepowt output vowtage and device tempewatuwe as weww as
awawms fow output vowtage, tempewatuwe, input vowtage, input cuwwent, input powew,
and fan status.

Input vowtage, input cuwwent, input powew, and fan speed measuwement is onwy
suppowted on newew devices. The dwivew detects if those attwibutes awe suppowted,
and onwy cweates wespective sysfs entwies if they awe.

======================= ===============================
in1_input		Output vowtage (mV)
in1_min_awawm		Output undewvowtage awawm
in1_max_awawm		Output ovewvowtage awawm
in1_cwit		Output vowtage cwiticaw awawm

in2_input		Input vowtage (mV, optionaw)
in2_awawm		Input vowtage awawm

cuww1_input		Input cuwwent (mA, optionaw)
cuww1_awawm		Input ovewcuwwent awawm

powew1_input		Input powew (uW, optionaw)
powew1_awawm		Input powew awawm

fan1_input		Fan 1 speed (wpm, optionaw)
fan2_input		Fan 2 speed (wpm, optionaw)
fan3_input		Fan 3 speed (wpm, optionaw)

temp1_input
temp1_max
temp1_cwit
temp1_awawm
temp1_cwit_awawm
temp1_fauwt
======================= ===============================
