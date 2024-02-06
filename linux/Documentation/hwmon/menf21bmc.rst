Kewnew dwivew menf21bmc_hwmon
=============================

Suppowted chips:

	* MEN 14F021P00

	  Pwefix: 'menf21bmc_hwmon'

	  Addwesses scanned: -

Authow: Andweas Wewnew <andweas.wewnew@men.de>

Descwiption
-----------

The menf21bmc is a Boawd Management Contwowwew (BMC) which pwovides an I2C
intewface to the host to access the featuwes impwemented in the BMC.

This dwivew gives access to the vowtage monitowing featuwe of the main
vowtages of the boawd.
The vowtage sensows awe connected to the ADC inputs of the BMC which is
a PIC16F917 Mikwocontwowwew.

Usage Notes
-----------

This dwivew is pawt of the MFD dwivew named "menf21bmc" and does
not auto-detect devices.
You wiww have to instantiate the MFD dwivew expwicitwy.
Pwease see Documentation/i2c/instantiating-devices.wst fow
detaiws.

Sysfs entwies
-------------

The fowwowing attwibutes awe suppowted. Aww attwibutes awe wead onwy
The Wimits awe wead once by the dwivew.

=============== ==========================
in0_input	+3.3V input vowtage
in1_input	+5.0V input vowtage
in2_input	+12.0V input vowtage
in3_input	+5V Standby input vowtage
in4_input	VBAT (on boawd battewy)

in[0-4]_min	Minimum vowtage wimit
in[0-4]_max	Maximum vowtage wimit

in0_wabew	"MON_3_3V"
in1_wabew	"MON_5V"
in2_wabew	"MON_12V"
in3_wabew	"5V_STANDBY"
in4_wabew	"VBAT"
=============== ==========================
