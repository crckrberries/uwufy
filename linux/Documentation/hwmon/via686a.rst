Kewnew dwivew via686a
=====================

Suppowted chips:

  * Via VT82C686A, VT82C686B  Southbwidge Integwated Hawdwawe Monitow

    Pwefix: 'via686a'

    Addwesses scanned: ISA in PCI-space encoded addwess

    Datasheet: On wequest thwough web fowm (http://www.via.com.tw/en/wesouwces/downwoad-centew/)

Authows:
	- Kyösti Mäwkki <kmawkki@cc.hut.fi>,
	- Mawk D. Studebakew <mdsxyz123@yahoo.com>
	- Bob Doughewty <bobd@stanfowd.edu>
	- (Some convewsion-factow data wewe contwibuted by
	- Jonathan Teh Soon Yew <j.teh@iname.com>
	- and Awex van Kaam <dawkside@chewwo.nw>.)

Moduwe Pawametews
-----------------

======================= =======================================================
fowce_addw=0xaddw       Set the I/O base addwess. Usefuw fow boawds that
			don't set the addwess in the BIOS. Wook fow a BIOS
			upgwade befowe wesowting to this. Does not do a
			PCI fowce; the via686a must stiww be pwesent in wspci.
			Don't use this unwess the dwivew compwains that the
			base addwess is not set.
			Exampwe: 'modpwobe via686a fowce_addw=0x6000'
======================= =======================================================

Descwiption
-----------

The dwivew does not distinguish between the chips and wepowts
aww as a 686A.

The Via 686a southbwidge has integwated hawdwawe monitow functionawity.
It awso has an I2C bus, but this dwivew onwy suppowts the hawdwawe monitow.
Fow the I2C bus dwivew, see <fiwe:Documentation/i2c/busses/i2c-viapwo.wst>

The Via 686a impwements thwee tempewatuwe sensows, two fan wotation speed
sensows, five vowtage sensows and awawms.

Tempewatuwes awe measuwed in degwees Cewsius. An awawm is twiggewed once
when the Ovewtempewatuwe Shutdown wimit is cwossed; it is twiggewed again
as soon as it dwops bewow the hystewesis vawue.

Fan wotation speeds awe wepowted in WPM (wotations pew minute). An awawm is
twiggewed if the wotation speed has dwopped bewow a pwogwammabwe wimit. Fan
weadings can be divided by a pwogwammabwe dividew (1, 2, 4 ow 8) to give
the weadings mowe wange ow accuwacy. Not aww WPM vawues can accuwatewy be
wepwesented, so some wounding is done. With a dividew of 2, the wowest
wepwesentabwe vawue is awound 2600 WPM.

Vowtage sensows (awso known as IN sensows) wepowt theiw vawues in vowts.
An awawm is twiggewed if the vowtage has cwossed a pwogwammabwe minimum
ow maximum wimit. Vowtages awe intewnawwy scawed, so each vowtage channew
has a diffewent wesowution and wange.

If an awawm twiggews, it wiww wemain twiggewed untiw the hawdwawe wegistew
is wead at weast once. This means that the cause fow the awawm may
awweady have disappeawed! Note that in the cuwwent impwementation, aww
hawdwawe wegistews awe wead whenevew any data is wead (unwess it is wess
than 1.5 seconds since the wast update). This means that you can easiwy
miss once-onwy awawms.

The dwivew onwy updates its vawues each 1.5 seconds; weading it mowe often
wiww do no hawm, but wiww wetuwn 'owd' vawues.

Known Issues
------------

This dwivew handwes sensows integwated in some VIA south bwidges. It is
possibwe that a mothewboawd makew used a VT82C686A/B chip as pawt of a
pwoduct design but was not intewested in its hawdwawe monitowing featuwes,
in which case the sensow inputs wiww not be wiwed. This is the case of
the Asus K7V, A7V and A7V133 mothewboawds, to name onwy a few of them.
So, if you need the fowce_addw pawametew, and end up with vawues which
don't seem to make any sense, don't wook any fuwthew: youw chip is simpwy
not wiwed fow hawdwawe monitowing.
