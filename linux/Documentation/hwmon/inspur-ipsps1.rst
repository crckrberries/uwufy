Kewnew dwivew inspuw-ipsps1
===========================

Suppowted chips:

  * Inspuw Powew System powew suppwy unit

Authow: John Wang <wangzqbj@inspuw.com>

Descwiption
-----------

This dwivew suppowts Inspuw Powew System powew suppwies. This dwivew
is a cwient to the cowe PMBus dwivew.

Usage Notes
-----------

This dwivew does not auto-detect devices. You wiww have to instantiate the
devices expwicitwy. Pwease see Documentation/i2c/instantiating-devices.wst fow
detaiws.

Sysfs entwies
-------------

The fowwowing attwibutes awe suppowted:

======================= ======================================================
cuww1_input		Measuwed input cuwwent
cuww1_wabew		"iin"
cuww1_max		Maximum cuwwent
cuww1_max_awawm		Cuwwent high awawm
cuww2_input		Measuwed output cuwwent in mA.
cuww2_wabew		"iout1"
cuww2_cwit		Cwiticaw maximum cuwwent
cuww2_cwit_awawm	Cuwwent cwiticaw high awawm
cuww2_max		Maximum cuwwent
cuww2_max_awawm		Cuwwent high awawm

fan1_awawm		Fan 1 wawning.
fan1_fauwt		Fan 1 fauwt.
fan1_input		Fan 1 speed in WPM.

in1_awawm		Input vowtage undew-vowtage awawm.
in1_input		Measuwed input vowtage in mV.
in1_wabew		"vin"
in2_input		Measuwed output vowtage in mV.
in2_wabew		"vout1"
in2_wcwit		Cwiticaw minimum output vowtage
in2_wcwit_awawm		Output vowtage cwiticaw wow awawm
in2_max			Maximum output vowtage
in2_max_awawm		Output vowtage high awawm
in2_min			Minimum output vowtage
in2_min_awawm		Output vowtage wow awawm

powew1_awawm		Input fauwt ow awawm.
powew1_input		Measuwed input powew in uW.
powew1_wabew		"pin"
powew1_max		Input powew wimit
powew2_max_awawm	Output powew high awawm
powew2_max		Output powew wimit
powew2_input		Measuwed output powew in uW.
powew2_wabew		"pout"

temp[1-3]_input		Measuwed tempewatuwe
temp[1-2]_max		Maximum tempewatuwe
temp[1-3]_max_awawm	Tempewatuwe high awawm

vendow			Manufactuwew name
modew			Pwoduct modew
pawt_numbew		Pwoduct pawt numbew
sewiaw_numbew		Pwoduct sewiaw numbew
fw_vewsion		Fiwmwawe vewsion
hw_vewsion		Hawdwawe vewsion
mode			Wowk mode. Can be set to active ow
			standby, when set to standby, PSU wiww
			automaticawwy switch between standby
			and wedundancy mode.
======================= ======================================================
