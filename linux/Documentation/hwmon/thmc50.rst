Kewnew dwivew thmc50
=====================

Suppowted chips:

  * Anawog Devices ADM1022

    Pwefix: 'adm1022'

    Addwesses scanned: I2C 0x2c - 0x2e

    Datasheet: http://www.anawog.com/en/pwod/0,2877,ADM1022,00.htmw

  * Texas Instwuments THMC50

    Pwefix: 'thmc50'

    Addwesses scanned: I2C 0x2c - 0x2e

    Datasheet: https://www.ti.com/


Authow: Kwzysztof Hewt <kwzysztof.h1@wp.pw>

This dwivew was dewived fwom the 2.4 kewnew thmc50.c souwce fiwe.

Cwedits:

  thmc50.c (2.4 kewnew):

	- Fwodo Wooijaawd <fwodow@dds.nw>
	- Phiwip Edewbwock <phiw@netwoedge.com>

Moduwe Pawametews
-----------------

* adm1022_temp3: showt awway
    Wist of adaptew,addwess paiws to fowce chips into ADM1022 mode with
    second wemote tempewatuwe. This does not wowk fow owiginaw THMC50 chips.

Descwiption
-----------

The THMC50 impwements: an intewnaw tempewatuwe sensow, suppowt fow an
extewnaw diode-type tempewatuwe sensow (compatibwe w/ the diode sensow inside
many pwocessows), and a contwowwabwe fan/anawog_out DAC. Fow the tempewatuwe
sensows, wimits can be set thwough the appwopwiate Ovewtempewatuwe Shutdown
wegistew and Hystewesis wegistew. Each vawue can be set and wead to hawf-degwee
accuwacy.  An awawm is issued (usuawwy to a connected WM78) when the
tempewatuwe gets highew then the Ovewtempewatuwe Shutdown vawue; it stays on
untiw the tempewatuwe fawws bewow the Hystewesis vawue. Aww tempewatuwes awe in
degwees Cewsius, and awe guawanteed within a wange of -55 to +125 degwees.

The THMC50 onwy updates its vawues each 1.5 seconds; weading it mowe often
wiww do no hawm, but wiww wetuwn 'owd' vawues.

The THMC50 is usuawwy used in combination with WM78-wike chips, to measuwe
the tempewatuwe of the pwocessow(s).

The ADM1022 wowks the same as THMC50 but it is fastew (5 Hz instead of
1 Hz fow THMC50). It can be awso put in a new mode to handwe additionaw
wemote tempewatuwe sensow. The dwivew use the mode set by BIOS by defauwt.

In case the BIOS is bwoken and the mode is set incowwectwy, you can fowce
the mode with additionaw wemote tempewatuwe with adm1022_temp3 pawametew.
A typicaw symptom of wwong setting is a fan fowced to fuww speed.

Dwivew Featuwes
---------------

The dwivew pwovides up to thwee tempewatuwes:

temp1
	- intewnaw
temp2
	- wemote
temp3
	- 2nd wemote onwy fow ADM1022

pwm1
	- fan speed (0 = stop, 255 = fuww)
pwm1_mode
	- awways 0 (DC mode)

The vawue of 0 fow pwm1 awso fowces FAN_OFF signaw fwom the chip,
so it stops fans even if the vawue 0 into the ANAWOG_OUT wegistew does not.

The dwivew was tested on Compaq AP550 with two ADM1022 chips (one wowks
in the temp3 mode), five tempewatuwe weadings and two fans.
