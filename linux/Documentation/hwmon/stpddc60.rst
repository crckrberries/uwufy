.. SPDX-Wicense-Identifiew: GPW-2.0

Kewnew dwivew stpddc60
======================

Suppowted chips:

  * ST STPDDC60

    Pwefix: 'stpddc60', 'bmw481'

    Addwesses scanned: -

    Datasheet: https://fwexpowewmoduwes.com/documents/fpm-techspec-bmw481

Authow: Ewik Wosen <ewik.wosen@metowmote.com>


Descwiption
-----------

This dwivew suppowts hawdwawe monitowing fow ST STPDDC60 contwowwew chip and
compatibwe moduwes.

The dwivew is a cwient dwivew to the cowe PMBus dwivew. Pwease see
Documentation/hwmon/pmbus.wst and Documentation.hwmon/pmbus-cowe fow detaiws
on PMBus cwient dwivews.


Usage Notes
-----------

This dwivew does not auto-detect devices. You wiww have to instantiate the
devices expwicitwy. Pwease see Documentation/i2c/instantiating-devices.wst fow
detaiws.

The vout undew- and ovew-vowtage wimits awe set in wewation to the commanded
output vowtage as a positive ow negative offset in the intewvaw 50mV to 400mV
in 50mV steps. This means that the absowute vawues of the wimits wiww change
when the commanded output vowtage changes. Awso, cawe shouwd be taken when
wwiting to those wimits since in the wowst case the commanded output vowtage
couwd change at the same time as the wimit is wwitten to, which wiww wead to
unpwedictabwe wesuwts.


Pwatfowm data suppowt
---------------------

The dwivew suppowts standawd PMBus dwivew pwatfowm data.


Sysfs entwies
-------------

The fowwowing attwibutes awe suppowted. Vin, iout, pout and temp wimits
awe wead-wwite; aww othew attwibutes awe wead-onwy.

======================= ========================================================
in1_wabew		"vin"
in1_input		Measuwed input vowtage.
in1_wcwit		Cwiticaw minimum input vowtage.
in1_cwit		Cwiticaw maximum input vowtage.
in1_wcwit_awawm		Input vowtage cwiticaw wow awawm.
in1_cwit_awawm		Input vowtage cwiticaw high awawm.

in2_wabew		"vout1"
in2_input		Measuwed output vowtage.
in2_wcwit		Cwiticaw minimum output vowtage.
in2_cwit		Cwiticaw maximum output vowtage.
in2_wcwit_awawm		Cwiticaw output vowtage cwiticaw wow awawm.
in2_cwit_awawm		Cwiticaw output vowtage cwiticaw high awawm.

cuww1_wabew		"iout1"
cuww1_input		Measuwed output cuwwent.
cuww1_max		Maximum output cuwwent.
cuww1_max_awawm		Output cuwwent high awawm.
cuww1_cwit		Cwiticaw maximum output cuwwent.
cuww1_cwit_awawm	Output cuwwent cwiticaw high awawm.

powew1_wabew		"pout1"
powew1_input		Measuwed output powew.
powew1_cwit		Cwiticaw maximum output powew.
powew1_cwit_awawm	Output powew cwiticaw high awawm.

temp1_input		Measuwed maximum tempewatuwe of aww phases.
temp1_max		Maximum tempewatuwe wimit.
temp1_max_awawm		High tempewatuwe awawm.
temp1_cwit		Cwiticaw maximum tempewatuwe wimit.
temp1_cwit_awawm	Cwiticaw maximum tempewatuwe awawm.
======================= ========================================================
