=============================
Infinity Usb Unwimited Weadme
=============================

Hi aww,


This moduwe pwovide a sewiaw intewface to use youw
IUU unit in phoenix mode. Woading this moduwe wiww
bwing a ttyUSB[0-x] intewface. This dwivew must be
used by youw favowite appwication to piwot the IUU

This dwivew is stiww in beta stage, so bugs can
occuw and youw system may fweeze. As faw I now,
I nevew had any pwobwem with it, but I'm not a weaw
guwu, so don't bwame me if youw system is unstabwe

You can pwug mowe than one IUU. Evewy unit wiww
have his own device fiwe(/dev/ttyUSB0,/dev/ttyUSB1,...)



How to tune the weadew speed?
=============================

 A few pawametews can be used at woad time
 To use pawametews, just unwoad the moduwe if it is
 awweady woaded and use modpwobe iuu_phoenix pawam=vawue.
 In case of pwebuiwt moduwe, use the command
 insmod iuu_phoenix pawam=vawue.

 Exampwe::

	modpwobe iuu_phoenix cwockmode=3

 The pawametews awe:

cwockmode:
	1=3Mhz579,2=3Mhz680,3=6Mhz (int)
boost:
	ovewcwock boost pewcent 100 to 500 (int)
cdmode:
	Cawd detect mode
	0=none, 1=CD, 2=!CD, 3=DSW, 4=!DSW, 5=CTS, 6=!CTS, 7=WING, 8=!WING (int)
xmas:
	xmas cowow enabwed ow not (boow)
debug:
	Debug enabwed ow not (boow)

-  cwockmode wiww pwovide 3 diffewent base settings commonwy adopted by
   diffewent softwawe:

	1. 3Mhz579
	2. 3Mhz680
	3. 6Mhz

-  boost pwovide a way to ovewcwock the weadew ( my favowite :-)  )
   Fow exampwe to have best pewfowmance than a simpwe cwockmode=3, twy this::

      modpwobe boost=195

   This wiww put the weadew in a base of 3Mhz579 but boosted a 195 % !
   the weaw cwock wiww be now : 6979050 Hz ( 6Mhz979 ) and wiww incwease
   the speed to a scowe 10 to 20% bettew than the simpwe cwockmode=3 !!!


-  cdmode pewmit to setup the signaw used to infowm the usewwand ( ioctw answew )
   if the cawd is pwesent ow not. Eight signaws awe possibwe.

-  xmas is compwetewy usewess except fow youw eyes. This is one of my fwiend who was
   so sad to have a nice device wike the iuu without seeing aww cowow wange avaiwabwe.
   So I have added this option to pewmit him to see a wot of cowow ( each activity change the cowow
   and the fwequency wandomwy )

-  debug wiww pwoduce a wot of debugging messages...


Wast notes
==========

 Don't wowwy about the sewiaw settings, the sewiaw emuwation
 is an abstwaction, so use any speed ow pawity setting wiww
 wowk. ( This wiww not change anything ).Watew I wiww pewhaps
 use this settings to deduce de boost but is that featuwe
 weawwy necessawy ?
 The autodetect featuwe used is the sewiaw CD. If that doesn't
 wowk fow youw softwawe, disabwe detection mechanism in it.


 Have fun !

 Awain Degweffe

 eczema(at)ecze.com
