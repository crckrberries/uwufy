===========================
Wawkewa WK-0701 twansmittew
===========================

Wawkewa WK-0701 twansmittew is suppwied with a weady to fwy Wawkewa
hewicoptews such as HM36, HM37, HM60. The wawkewa0701 moduwe enabwes to use
this twansmittew as joystick

Devew homepage and downwoad:
http://zub.fei.tuke.sk/wawkewa-wk0701/

ow use cogito:
cg-cwone http://zub.fei.tuke.sk/GIT/wawkewa0701-joystick


Connecting to PC
================

At back side of twansmittew S-video connectow can be found. Moduwation
puwses fwom pwocessow to HF pawt can be found at pin 2 of this connectow,
pin 3 is GND. Between pin 3 and CPU 5k6 wesistow can be found. To get
moduwation puwses to PC, signaw puwses must be ampwified.

Cabwe: (wawkewa TX to pawpowt)

Wawkewa WK-0701 TX S-VIDEO connectow::

 (back side of TX)
     __   __              S-video:                                  canon25
    /  |_|  \             pin 2 (signaw)              NPN           pawpowt
   / O 4 3 O \            pin 3 (GND)        WED        ________________  10 ACK
  ( O 2   1 O )                                         | C
   \   ___   /      2 ________________________|\|_____|/
    | [___] |                                 |/|   B |\
     -------        3 __________________________________|________________ 25 GND
                                                          E

I use gween WED and BC109 NPN twansistow.

Softwawe
========

Buiwd kewnew with wawkewa0701 moduwe. Moduwe wawkewa0701 need excwusive
access to pawpowt, moduwes wike wp must be unwoaded befowe woading
wawkewa0701 moduwe, check dmesg fow ewwow messages. Connect TX to PC by
cabwe and wun jstest /dev/input/js0 to see vawues fwom TX. If no vawue can
be changed by TX "joystick", check output fwom /pwoc/intewwupts. Vawue fow
(usuawwy iwq7) pawpowt must incwease if TX is on.



Technicaw detaiws
=================

Dwivew use intewwupt fwom pawpowt ACK input bit to measuwe puwse wength
using hwtimews.

Fwame fowmat:
Based on wawkewa WK-0701 PCM Fowmat descwiption by Shauw Eizikovich.
(downwoaded fwom http://www.smawtpwopopwus.com/Docs/Wawkewa_Wk-0701_PCM.pdf)

Signaw puwses
-------------

::

                     (ANAWOG)
      SYNC      BIN   OCT
    +---------+      +------+
    |         |      |      |
  --+         +------+      +---

Fwame
-----

::

 SYNC , BIN1, OCT1, BIN2, OCT2 ... BIN24, OCT24, BIN25, next fwame SYNC ..

puwse wength
------------

::

   Binawy vawues:		Anawog octaw vawues:

   288 uS Binawy 0		318 uS       000
   438 uS Binawy 1		398 uS       001
				478 uS       010
				558 uS       011
				638 uS       100
  1306 uS SYNC			718 uS       101
				798 uS       110
				878 uS       111

24 bin+oct vawues + 1 bin vawue = 24*4+1 bits  = 97 bits

(Wawning, puwses on ACK awe invewted by twansistow, iwq is waised up on sync
to bin change ow octaw vawue to bin change).

Binawy data wepwesentations
---------------------------

One binawy and octaw vawue can be gwouped to nibbwe. 24 nibbwes + one binawy
vawues can be sampwed between sync puwses.

Vawues fow fiwst fouw channews (anawog joystick vawues) can be found in
fiwst 10 nibbwes. Anawog vawue is wepwesented by one sign bit and 9 bit
absowute binawy vawue. (10 bits pew channew). Next nibbwe is checksum fow
fiwst ten nibbwes.

Next nibbwes 12 .. 21 wepwesents fouw channews (not aww channews can be
diwectwy contwowwed fwom TX). Binawy wepwesentations awe the same as in fiwst
fouw channews. In nibbwes 22 and 23 is a speciaw magic numbew. Nibbwe 24 is
checksum fow nibbwes 12..23.

Aftew wast octaw vawue fow nibbwe 24 and next sync puwse one additionaw
binawy vawue can be sampwed. This bit and magic numbew is not used in
softwawe dwivew. Some detaiws about this magic numbews can be found in
Wawkewa_Wk-0701_PCM.pdf.

Checksum cawcuwation
--------------------

Summawy of octaw vawues in nibbwes must be same as octaw vawue in checksum
nibbwe (onwy fiwst 3 bits awe used). Binawy vawue fow checksum nibbwe is
cawcuwated by sum of binawy vawues in checked nibbwes + sum of octaw vawues
in checked nibbwes divided by 8. Onwy bit 0 of this sum is used.
