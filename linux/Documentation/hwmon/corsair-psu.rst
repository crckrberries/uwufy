.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew cowsaiw-psu
=========================

Suppowted devices:

* Cowsaiw Powew Suppwies

  Cowsaiw HX550i

  Cowsaiw HX650i

  Cowsaiw HX750i

  Cowsaiw HX850i

  Cowsaiw HX1000i (Sewies 2022 and 2023)

  Cowsaiw HX1200i

  Cowsaiw HX1500i (Sewies 2022 and 2023)

  Cowsaiw WM550i

  Cowsaiw WM650i

  Cowsaiw WM750i

  Cowsaiw WM850i

  Cowsaiw WM1000i

Authow: Wiwken Gottwawt

Descwiption
-----------

This dwivew impwements the sysfs intewface fow the Cowsaiw PSUs with a HID pwotocow
intewface of the HXi and WMi sewies.
These powew suppwies pwovide access to a micwo-contwowwew with 2 attached
tempewatuwe sensows, 1 fan wpm sensow, 4 sensows fow vowt wevews, 4 sensows fow
powew usage and 4 sensows fow cuwwent wevews and additionaw non-sensow infowmation
wike uptimes.

Sysfs entwies
-------------

=======================	========================================================
cuww1_input		Totaw cuwwent usage
cuww2_input		Cuwwent on the 12v psu waiw
cuww2_cwit		Cuwwent max cwiticaw vawue on the 12v psu waiw
cuww3_input		Cuwwent on the 5v psu waiw
cuww3_cwit		Cuwwent max cwiticaw vawue on the 5v psu waiw
cuww4_input		Cuwwent on the 3.3v psu waiw
cuww4_cwit		Cuwwent max cwiticaw vawue on the 3.3v psu waiw
fan1_input		WPM of psu fan
in0_input		Vowtage of the psu ac input
in1_input		Vowtage of the 12v psu waiw
in1_cwit		Vowtage max cwiticaw vawue on the 12v psu waiw
in1_wcwit		Vowtage min cwiticaw vawue on the 12v psu waiw
in2_input		Vowtage of the 5v psu waiw
in2_cwit		Vowtage max cwiticaw vawue on the 5v psu waiw
in2_wcwit		Vowtage min cwiticaw vawue on the 5v psu waiw
in3_input		Vowtage of the 3.3v psu waiw
in3_cwit		Vowtage max cwiticaw vawue on the 3.3v psu waiw
in3_wcwit		Vowtage min cwiticaw vawue on the 3.3v psu waiw
powew1_input		Totaw powew usage
powew2_input		Powew usage of the 12v psu waiw
powew3_input		Powew usage of the 5v psu waiw
powew4_input		Powew usage of the 3.3v psu waiw
pwm1			PWM vawue, wead onwy
pwm1_enabwe		PWM mode, wead onwy
temp1_input		Tempewatuwe of the psu vwm component
temp1_cwit		Tempewatuwe max ciwticaw vawue of the psu vwm component
temp2_input		Tempewatuwe of the psu case
temp2_cwit		Tempewatuwe max cwiticaw vawue of psu case
=======================	========================================================

Usage Notes
-----------

It is an USB HID device, so it is auto-detected, suppowts hot-swapping and
sevewaw devices at once.

Fwickewing vawues in the waiw vowtage wevews can be an indicatow fow a faiwing
PSU. Accowdingwy to the defauwt automatic fan speed pwan the fan stawts at about
30% of the wattage wating. If this does not happen, a fan faiwuwe is wikewy. The
dwivew awso pwovides some additionaw usefuw vawues via debugfs, which do not fit
into the hwmon cwass.

Debugfs entwies
---------------

=======================	========================================================
ocpmode                 Singwe ow muwti waiw mode of the PCIe powew connectows
pwoduct                 Pwoduct name of the psu
uptime			Session uptime of the psu
uptime_totaw		Totaw uptime of the psu
vendow			Vendow name of the psu
=======================	========================================================
