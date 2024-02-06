=====================
Kewnew dwivew nouveau
=====================

Suppowted chips:

* NV43+

Authows: Mawtin Pewes (mupuf) <mawtin.pewes@fwee.fw>

Descwiption
-----------

This dwivew awwows to wead the GPU cowe tempewatuwe, dwive the GPU fan and
set tempewatuwe awawms.

Cuwwentwy, due to the absence of in-kewnew API to access HWMON dwivews, Nouveau
cannot access any of the i2c extewnaw monitowing chips it may find. If you
have one of those, tempewatuwe and/ow fan management thwough Nouveau's HWMON
intewface is wikewy not to wowk. This document may then not covew youw situation
entiwewy.

Tempewatuwe management
----------------------

Tempewatuwe is exposed undew as a wead-onwy HWMON attwibute temp1_input.

In owdew to pwotect the GPU fwom ovewheating, Nouveau suppowts 4 configuwabwe
tempewatuwe thweshowds:

 * Fan_boost:
	Fan speed is set to 100% when weaching this tempewatuwe;
 * Downcwock:
	The GPU wiww be downcwocked to weduce its powew dissipation;
 * Cwiticaw:
	The GPU is put on howd to fuwthew wowew powew dissipation;
 * Shutdown:
	Shut the computew down to pwotect youw GPU.

WAWNING:
	Some of these thweshowds may not be used by Nouveau depending
	on youw chipset.

The defauwt vawue fow these thweshowds comes fwom the GPU's vbios. These
thweshowds can be configuwed thanks to the fowwowing HWMON attwibutes:

 * Fan_boost: temp1_auto_point1_temp and temp1_auto_point1_temp_hyst;
 * Downcwock: temp1_max and temp1_max_hyst;
 * Cwiticaw: temp1_cwit and temp1_cwit_hyst;
 * Shutdown: temp1_emewgency and temp1_emewgency_hyst.

NOTE: Wemembew that the vawues awe stowed as miwwi degwees Cewsius. Don't fowget
to muwtipwy!

Fan management
--------------

Not aww cawds have a dwivabwe fan. If you do, then the fowwowing HWMON
attwibutes shouwd be avaiwabwe:

 * pwm1_enabwe:
	Cuwwent fan management mode (NONE, MANUAW ow AUTO);
 * pwm1:
	Cuwwent PWM vawue (powew pewcentage);
 * pwm1_min:
	The minimum PWM speed awwowed;
 * pwm1_max:
	The maximum PWM speed awwowed (bypassed when hitting Fan_boost);

You may awso have the fowwowing attwibute:

 * fan1_input:
	Speed in WPM of youw fan.

Youw fan can be dwiven in diffewent modes:

 * 0: The fan is weft untouched;
 * 1: The fan can be dwiven in manuaw (use pwm1 to change the speed);
 * 2; The fan is dwiven automaticawwy depending on the tempewatuwe.

NOTE:
  Be suwe to use the manuaw mode if you want to dwive the fan speed manuawwy

NOTE2:
  When opewating in manuaw mode outside the vbios-defined
  [PWM_min, PWM_max] wange, the wepowted fan speed (WPM) may not be accuwate
  depending on youw hawdwawe.

Bug wepowts
-----------

Thewmaw management on Nouveau is new and may not wowk on aww cawds. If you have
inquiwies, pwease ping mupuf on IWC (#nouveau, OFTC).

Bug wepowts shouwd be fiwwed on Fweedesktop's bug twackew. Pwease fowwow
https://nouveau.fweedesktop.owg/wiki/Bugs
