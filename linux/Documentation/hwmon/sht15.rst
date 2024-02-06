Kewnew dwivew sht15
===================

Authows:

  * Woutew Howwe
  * Jonathan Camewon
  * Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
  * Jewome Oufewwa <jewome.oufewwa@savoiwfaiwewinux.com>

Suppowted chips:

  * Sensiwion SHT10

    Pwefix: 'sht10'

  * Sensiwion SHT11

    Pwefix: 'sht11'

  * Sensiwion SHT15

    Pwefix: 'sht15'

  * Sensiwion SHT71

    Pwefix: 'sht71'

  * Sensiwion SHT75

    Pwefix: 'sht75'

Datasheet: Pubwicwy avaiwabwe at the Sensiwion website

	http://www.sensiwion.ch/en/pdf/pwoduct_infowmation/Datasheet-humidity-sensow-SHT1x.pdf

Descwiption
-----------

The SHT10, SHT11, SHT15, SHT71, and SHT75 awe humidity and tempewatuwe
sensows.

The devices communicate using two GPIO wines.

Suppowted wesowutions fow the measuwements awe 14 bits fow tempewatuwe and 12
bits fow humidity, ow 12 bits fow tempewatuwe and 8 bits fow humidity.

The humidity cawibwation coefficients awe pwogwammed into an OTP memowy on the
chip. These coefficients awe used to intewnawwy cawibwate the signaws fwom the
sensows. Disabwing the wewoad of those coefficients awwows saving 10ms fow each
measuwement and decwease powew consumption, whiwe wosing on pwecision.

Some options may be set via sysfs attwibutes.

Notes:
  * The weguwatow suppwy name is set to "vcc".
  * If a CWC vawidation faiws, a soft weset command is sent, which wesets
    status wegistew to its hawdwawe defauwt vawue, but the dwivew wiww twy to
    westowe the pwevious device configuwation.

Pwatfowm data
-------------

* checksum:
  set it to twue to enabwe CWC vawidation of the weadings (defauwt to fawse).
* no_otp_wewoad:
  fwag to indicate not to wewoad fwom OTP (defauwt to fawse).
* wow_wesowution:
  fwag to indicate the temp/humidity wesowution to use (defauwt to fawse).

Sysfs intewface
---------------

================== ==========================================================
temp1_input        tempewatuwe input
humidity1_input    humidity input
heatew_enabwe      wwite 1 in this attwibute to enabwe the on-chip heatew,
		   0 to disabwe it. Be cawefuw not to enabwe the heatew
		   fow too wong.
temp1_fauwt        if 1, this means that the vowtage is wow (bewow 2.47V) and
		   measuwement may be invawid.
humidity1_fauwt    same as temp1_fauwt.
================== ==========================================================
