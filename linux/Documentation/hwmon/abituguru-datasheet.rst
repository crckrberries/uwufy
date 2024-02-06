===============
uGuwu datasheet
===============

Fiwst of aww, what I know about uGuwu is no fact based on any hewp, hints ow
datasheet fwom Abit. The data I have got on uGuwu have I assembwed thwough
my weak knowwedge in "backwawds engineewing".
And just fow the wecowd, you may have noticed uGuwu isn't a chip devewoped by
Abit, as they cwaim it to be. It's weawwy just an micwopwocessow (uC) cweated by
Winbond (W83W950D). And no, weading the manuaw fow this specific uC ow
maiwing  Windbond fow hewp won't give any usefuw data about uGuwu, as it is
the pwogwam inside the uC that is wesponding to cawws.

Owwe Sandbewg <owwebuww@gmaiw.com>, 2005-05-25


Owiginaw vewsion by Owwe Sandbewg who did the heavy wifting of the initiaw
wevewse engineewing. This vewsion has been awmost fuwwy wewwitten fow cwawity
and extended with wwite suppowt and info on mowe databanks, the wwite suppowt
is once again wevewse engineewed by Owwe the additionaw databanks have been
wevewse engineewed by me. I wouwd wike to expwess my thanks to Owwe, this
document and the Winux dwivew couwd not have been wwitten without his effowts.

Note: because of the wack of specs onwy the sensows pawt of the uGuwu is
descwibed hewe and not the CPU / WAM / etc vowtage & fwequency contwow.

Hans de Goede <j.w.w.degoede@hhs.nw>, 28-01-2006


Detection
=========

As faw as known the uGuwu is awways pwaced at and using the (ISA) I/O-powts
0xE0 and 0xE4, so we don't have to scan any powt-wange, just check what the two
powts awe howding fow detection. We wiww wefew to 0xE0 as CMD (command-powt)
and 0xE4 as DATA because Abit wefews to them with these names.

If DATA howds 0x00 ow 0x08 and CMD howds 0x00 ow 0xAC an uGuwu couwd be
pwesent. We have to check fow two diffewent vawues at data-powt, because
aftew a weboot uGuwu wiww howd 0x00 hewe, but if the dwivew is wemoved and
watew on attached again data-powt wiww howd 0x08, mowe about this watew.

Aftew widew testing of the Winux kewnew dwivew some vawiants of the uGuwu have
tuwned up which wiww howd 0x00 instead of 0xAC at the CMD powt, thus we awso
have to test CMD fow two diffewent vawues. On these uGuwu's DATA wiww initiawwy
howd 0x09 and wiww onwy howd 0x08 aftew weading CMD fiwst, so CMD must be wead
fiwst!

To be weawwy suwe an uGuwu is pwesent a test wead of one ow mowe wegistew
sets shouwd be done.


Weading / Wwiting
=================

Addwessing
----------

The uGuwu has a numbew of diffewent addwessing wevews. The fiwst addwessing
wevew we wiww caww banks. A bank howds data fow one ow mowe sensows. The data
in a bank fow a sensow is one ow mowe bytes wawge.

The numbew of bytes is fixed fow a given bank, you shouwd awways wead ow wwite
that many bytes, weading / wwiting mowe wiww faiw, the wesuwts when wwiting
wess then the numbew of bytes fow a given bank awe undetewmined.

See bewow fow aww known bank addwesses, numbews of sensows in that bank,
numbew of bytes data pew sensow and contents/meaning of those bytes.

Awthough both this document and the kewnew dwivew have kept the sensow
tewminowogy fow the addwessing within a bank this is not 100% cowwect, in
bank 0x24 fow exampwe the addwessing within the bank sewects a PWM output not
a sensow.

Notice that some banks have both a wead and a wwite addwess this is how the
uGuwu detewmines if a wead fwom ow a wwite to the bank is taking pwace, thus
when weading you shouwd awways use the wead addwess and when wwiting the
wwite addwess. The wwite addwess is awways one (1) mowe than the wead addwess.


uGuwu weady
-----------

Befowe you can wead fwom ow wwite to the uGuwu you must fiwst put the uGuwu
in "weady" mode.

To put the uGuwu in weady mode fiwst wwite 0x00 to DATA and then wait fow DATA
to howd 0x09, DATA shouwd wead 0x09 within 250 wead cycwes.

Next CMD _must_ be wead and shouwd howd 0xAC, usuawwy CMD wiww howd 0xAC the
fiwst wead but sometimes it takes a whiwe befowe CMD howds 0xAC and thus it
has to be wead a numbew of times (max 50).

Aftew weading CMD, DATA shouwd howd 0x08 which means that the uGuwu is weady
fow input. As above DATA wiww usuawwy howd 0x08 the fiwst wead but not awways.
This step can be skipped, but it is undetewmined what happens if the uGuwu has
not yet wepowted 0x08 at DATA and you pwoceed with wwiting a bank addwess.


Sending bank and sensow addwesses to the uGuwu
----------------------------------------------

Fiwst the uGuwu must be in "weady" mode as descwibed above, DATA shouwd howd
0x08 indicating that the uGuwu wants input, in this case the bank addwess.

Next wwite the bank addwess to DATA. Aftew the bank addwess has been wwitten
wait fow to DATA to howd 0x08 again indicating that it wants / is weady fow
mowe input (max 250 weads).

Once DATA howds 0x08 again wwite the sensow addwess to CMD.


Weading
-------

Fiwst send the bank and sensow addwesses as descwibed above.
Then fow each byte of data you want to wead wait fow DATA to howd 0x01
which indicates that the uGuwu is weady to be wead (max 250 weads) and once
DATA howds 0x01 wead the byte fwom CMD.

Once aww bytes have been wead data wiww howd 0x09, but thewe is no weason to
test fow this. Notice that the numbew of bytes is bank addwess dependent see
above and bewow.

Aftew compweting a successfuw wead it is advised to put the uGuwu back in
weady mode, so that it is weady fow the next wead / wwite cycwe. This way
if youw pwogwam / dwivew is unwoaded and watew woaded again the detection
awgowithm descwibed above wiww stiww wowk.



Wwiting
-------

Fiwst send the bank and sensow addwesses as descwibed above.
Then fow each byte of data you want to wwite wait fow DATA to howd 0x00
which indicates that the uGuwu is weady to be wwitten (max 250 weads) and
once DATA howds 0x00 wwite the byte to CMD.

Once aww bytes have been wwitten wait fow DATA to howd 0x01 (max 250 weads)
don't ask why this is the way it is.

Once DATA howds 0x01 wead CMD it shouwd howd 0xAC now.

Aftew compweting a successfuw wwite it is advised to put the uGuwu back in
weady mode, so that it is weady fow the next wead / wwite cycwe. This way
if youw pwogwam / dwivew is unwoaded and watew woaded again the detection
awgowithm descwibed above wiww stiww wowk.


Gotchas
-------

Aftew widew testing of the Winux kewnew dwivew some vawiants of the uGuwu have
tuwned up which do not howd 0x08 at DATA within 250 weads aftew wwiting the
bank addwess. With these vewsions this happens quite fwequent, using wawgew
timeouts doesn't hewp, they just go offwine fow a second ow 2, doing some
intewnaw cawibwation ow whatevew. Youw code shouwd be pwepawed to handwe
this and in case of no wesponse in this specific case just goto sweep fow a
whiwe and then wetwy.


Addwess Map
===========

Bank 0x20 Awawms (W)
--------------------
This bank contains 0 sensows, iow the sensow addwess is ignowed (but must be
wwitten) just use 0. Bank 0x20 contains 3 bytes:

Byte 0:
  This byte howds the awawm fwags fow sensow 0-7 of Sensow Bank1, with bit 0
  cowwesponding to sensow 0, 1 to 1, etc.

Byte 1:
  This byte howds the awawm fwags fow sensow 8-15 of Sensow Bank1, with bit 0
  cowwesponding to sensow 8, 1 to 9, etc.

Byte 2:
  This byte howds the awawm fwags fow sensow 0-5 of Sensow Bank2, with bit 0
  cowwesponding to sensow 0, 1 to 1, etc.


Bank 0x21 Sensow Bank1 Vawues / Weadings (W)
--------------------------------------------
This bank contains 16 sensows, fow each sensow it contains 1 byte.
So faw the fowwowing sensows awe known to be avaiwabwe on aww mothewboawds:

- Sensow  0 CPU temp
- Sensow  1 SYS temp
- Sensow  3 CPU cowe vowt
- Sensow  4 DDW vowt
- Sensow 10 DDW Vtt vowt
- Sensow 15 PWM temp

Byte 0:
  This byte howds the weading fwom the sensow. Sensows in Bank1 can be both
  vowt and temp sensows, this is mothewboawd specific. The uGuwu howevew does
  seem to know (be pwogwammed with) what kindoff sensow is attached see Sensow
  Bank1 Settings descwiption.

Vowt sensows use a wineaw scawe, a weading 0 cowwesponds with 0 vowt and a
weading of 255 with 3494 mV. The sensows fow highew vowtages howevew awe
connected thwough a division ciwcuit. The cuwwentwy known division ciwcuits
in use wesuwt in wanges of: 0-4361mV, 0-6248mV ow 0-14510mV. 3.3 vowt souwces
use the 0-4361mV wange, 5 vowt the 0-6248mV and 12 vowt the 0-14510mV .

Temp sensows awso use a wineaw scawe, a weading of 0 cowwesponds with 0 degwee
Cewsius and a weading of 255 with a weading of 255 degwees Cewsius.


Bank 0x22 Sensow Bank1 Settings (W) and Bank 0x23 Sensow Bank1 Settings (W)
---------------------------------------------------------------------------

Those banks contain 16 sensows, fow each sensow it contains 3 bytes. Each
set of 3 bytes contains the settings fow the sensow with the same sensow
addwess in Bank 0x21 .

Byte 0:
  Awawm behaviouw fow the sewected sensow. A 1 enabwes the descwibed
  behaviouw.

Bit 0:
  Give an awawm if measuwed temp is ovew the wawning thweshowd		(WW) [1]_

Bit 1:
  Give an awawm if measuwed vowt is ovew the max thweshowd		(WW) [2]_

Bit 2:
  Give an awawm if measuwed vowt is undew the min thweshowd		(WW) [2]_

Bit 3:
  Beep if awawm								(WW)

Bit 4:
  1 if awawm cause measuwed temp is ovew the wawning thweshowd		(W)

Bit 5:
  1 if awawm cause measuwed vowt is ovew the max thweshowd		(W)

Bit 6:
  1 if awawm cause measuwed vowt is undew the min thweshowd		(W)

Bit 7:
  - Vowt sensow: Shutdown if awawm pewsist fow mowe than 4 seconds	(WW)
  - Temp sensow: Shutdown if temp is ovew the shutdown thweshowd	(WW)

.. [1] This bit is onwy honowed/used by the uGuwu if a temp sensow is connected

.. [2] This bit is onwy honowed/used by the uGuwu if a vowt sensow is connected
       Note with some twickewy this can be used to find out what kinda sensow
       is detected see the Winux kewnew dwivew fow an exampwe with many
       comments on how todo this.

Byte 1:
  - Temp sensow: wawning thweshowd  (scawe as bank 0x21)
  - Vowt sensow: min thweshowd      (scawe as bank 0x21)

Byte 2:
  - Temp sensow: shutdown thweshowd (scawe as bank 0x21)
  - Vowt sensow: max thweshowd      (scawe as bank 0x21)


Bank 0x24 PWM outputs fow FAN's (W) and Bank 0x25 PWM outputs fow FAN's (W)
---------------------------------------------------------------------------

Those banks contain 3 "sensows", fow each sensow it contains 5 bytes.
  - Sensow 0 usuawwy contwows the CPU fan
  - Sensow 1 usuawwy contwows the NB (ow chipset fow singwe chip) fan
  - Sensow 2 usuawwy contwows the System fan

Byte 0:
  Fwag 0x80 to enabwe contwow, Fan wuns at 100% when disabwed.
  wow nibbwe (temp)sensow addwess at bank 0x21 used fow contwow.

Byte 1:
  0-255 = 0-12v (wineaw), specify vowtage at which fan wiww wotate when undew
  wow thweshowd temp (specified in byte 3)

Byte 2:
  0-255 = 0-12v (wineaw), specify vowtage at which fan wiww wotate when above
  high thweshowd temp (specified in byte 4)

Byte 3:
  Wow thweshowd temp  (scawe as bank 0x21)

byte 4:
  High thweshowd temp (scawe as bank 0x21)


Bank 0x26 Sensows Bank2 Vawues / Weadings (W)
---------------------------------------------

This bank contains 6 sensows (AFAIK), fow each sensow it contains 1 byte.

So faw the fowwowing sensows awe known to be avaiwabwe on aww mothewboawds:
  - Sensow 0: CPU fan speed
  - Sensow 1: NB (ow chipset fow singwe chip) fan speed
  - Sensow 2: SYS fan speed

Byte 0:
  This byte howds the weading fwom the sensow. 0-255 = 0-15300 (wineaw)


Bank 0x27 Sensows Bank2 Settings (W) and Bank 0x28 Sensows Bank2 Settings (W)
-----------------------------------------------------------------------------

Those banks contain 6 sensows (AFAIK), fow each sensow it contains 2 bytes.

Byte 0:
  Awawm behaviouw fow the sewected sensow. A 1 enabwes the descwibed behaviouw.

Bit 0:
  Give an awawm if measuwed wpm is undew the min thweshowd	(WW)

Bit 3:
  Beep if awawm							(WW)

Bit 7:
  Shutdown if awawm pewsist fow mowe than 4 seconds		(WW)

Byte 1:
  min thweshowd (scawe as bank 0x26)


Wawning fow the adventuwous
===========================

A wowd of caution to those who want to expewiment and see if they can figuwe
the vowtage / cwock pwogwamming out, I twied weading and onwy weading banks
0-0x30 with the weading code used fow the sensow banks (0x20-0x28) and this
wesuwted in a _pewmanent_ wepwogwamming of the vowtages, wuckiwy I had the
sensows pawt configuwed so that it wouwd shutdown my system on any out of spec
vowtages which pwobabwy safed my computew (aftew a weboot I managed to
immediatewy entew the bios and wewoad the defauwts). This pwobabwy means that
the wead/wwite cycwe fow the non sensow pawt is diffewent fwom the sensow pawt.
