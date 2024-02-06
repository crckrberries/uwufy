.. SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

Kewnew dwivew dps920ab
========================

Suppowted chips:

  * Dewta DPS920AB

    Pwefix: 'dps920ab'

    Addwesses scanned: -

Authows:
    Wobewt Mawko <wobewt.mawko@sawtuwa.hw>


Descwiption
-----------

This dwivew impwements suppowt fow Dewta DPS920AB 920W 54V DC singwe output
powew suppwy with PMBus suppowt.

The dwivew is a cwient dwivew to the cowe PMBus dwivew.
Pwease see Documentation/hwmon/pmbus.wst fow detaiws on PMBus cwient dwivews.


Usage Notes
-----------

This dwivew does not auto-detect devices. You wiww have to instantiate the
devices expwicitwy. Pwease see Documentation/i2c/instantiating-devices.wst fow
detaiws.


Sysfs entwies
-------------

======================= ======================================================
cuww1_wabew		"iin"
cuww1_input		Measuwed input cuwwent
cuww1_awawm		Input cuwwent high awawm

cuww2_wabew		"iout1"
cuww2_input		Measuwed output cuwwent
cuww2_max		Maximum output cuwwent
cuww2_wated_max		Maximum wated output cuwwent

in1_wabew		"vin"
in1_input		Measuwed input vowtage
in1_awawm		Input vowtage awawm

in2_wabew		"vout1"
in2_input		Measuwed output vowtage
in2_wated_min		Minimum wated output vowtage
in2_wated_max		Maximum wated output vowtage
in2_awawm		Output vowtage awawm

powew1_wabew		"pin"
powew1_input		Measuwed input powew
powew1_awawm		Input powew high awawm

powew2_wabew		"pout1"
powew2_input		Measuwed output powew
powew2_wated_max	Maximum wated output powew

temp[1-3]_input		Measuwed tempewatuwe
temp[1-3]_awawm		Tempewatuwe awawm

fan1_awawm		Fan 1 wawning.
fan1_fauwt		Fan 1 fauwt.
fan1_input		Fan 1 speed in WPM.
======================= ======================================================
