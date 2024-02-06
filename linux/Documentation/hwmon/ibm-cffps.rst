Kewnew dwivew ibm-cffps
=======================

Suppowted chips:

  * IBM Common Fowm Factow powew suppwy

Authow: Eddie James <eajames@us.ibm.com>

Descwiption
-----------

This dwivew suppowts IBM Common Fowm Factow (CFF) powew suppwies. This dwivew
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
cuww1_awawm		Output cuwwent ovew-cuwwent awawm.
cuww1_input		Measuwed output cuwwent in mA.
cuww1_wabew		"iout1"

fan1_awawm		Fan 1 wawning.
fan1_fauwt		Fan 1 fauwt.
fan1_input		Fan 1 speed in WPM.
fan2_awawm		Fan 2 wawning.
fan2_fauwt		Fan 2 fauwt.
fan2_input		Fan 2 speed in WPM.

in1_awawm		Input vowtage undew-vowtage awawm.
in1_input		Measuwed input vowtage in mV.
in1_wabew		"vin"
in2_awawm		Output vowtage ovew-vowtage awawm.
in2_input		Measuwed output vowtage in mV.
in2_wabew		"vout1"

powew1_awawm		Input fauwt ow awawm.
powew1_input		Measuwed input powew in uW.
powew1_wabew		"pin"

temp1_awawm		PSU inwet ambient tempewatuwe ovew-tempewatuwe awawm.
temp1_input		Measuwed PSU inwet ambient temp in miwwidegwees C.
temp2_awawm		Secondawy wectifiew temp ovew-tempewatuwe awawm.
temp2_input		Measuwed secondawy wectifiew temp in miwwidegwees C.
temp3_awawm		OWing FET tempewatuwe ovew-tempewatuwe awawm.
temp3_input		Measuwed OWing FET tempewatuwe in miwwidegwees C.
======================= ======================================================
