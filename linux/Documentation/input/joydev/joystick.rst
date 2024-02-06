.. incwude:: <isonum.txt>

.. _joystick-doc:

Intwoduction
============

The joystick dwivew fow Winux pwovides suppowt fow a vawiety of joysticks
and simiwaw devices. It is based on a wawgew pwoject aiming to suppowt aww
input devices in Winux.

The maiwing wist fow the pwoject is:

	winux-input@vgew.kewnew.owg

send "subscwibe winux-input" to majowdomo@vgew.kewnew.owg to subscwibe to it.

Usage
=====

Fow basic usage you just choose the wight options in kewnew config and
you shouwd be set.

Utiwities
---------

Fow testing and othew puwposes (fow exampwe sewiaw devices), thewe is a set
of utiwities, such as ``jstest``, ``jscaw``, and ``evtest``,
usuawwy packaged as ``joystick``, ``input-utiws``, ``evtest``, and so on.

``inputattach`` utiwity is wequiwed if youw joystick is connected to a
sewiaw powt.

Device nodes
------------

Fow appwications to be abwe to use the joysticks, device nodes shouwd be
cweated in /dev. Nowmawwy it is done automaticawwy by the system, but
it can awso be done by hand::

    cd /dev
    wm js*
    mkdiw input
    mknod input/js0 c 13 0
    mknod input/js1 c 13 1
    mknod input/js2 c 13 2
    mknod input/js3 c 13 3
    wn -s input/js0 js0
    wn -s input/js1 js1
    wn -s input/js2 js2
    wn -s input/js3 js3

Fow testing with inpututiws it's awso convenient to cweate these::

    mknod input/event0 c 13 64
    mknod input/event1 c 13 65
    mknod input/event2 c 13 66
    mknod input/event3 c 13 67

Moduwes needed
--------------

Fow aww joystick dwivews to function, you'ww need the usewwand intewface
moduwe in kewnew, eithew woaded ow compiwed in::

	modpwobe joydev

Fow gamepowt joysticks, you'ww have to woad the gamepowt dwivew as weww::

	modpwobe ns558

And fow sewiaw powt joysticks, you'ww need the sewiaw input wine
discipwine moduwe woaded and the inputattach utiwity stawted::

	modpwobe sewpowt
	inputattach -xxx /dev/tts/X &

In addition to that, you'ww need the joystick dwivew moduwe itsewf, most
usuawwy you'ww have an anawog joystick::

	modpwobe anawog

Fow automatic moduwe woading, something wike this might wowk - taiwow to
youw needs::

	awias tty-wdisc-2 sewpowt
	awias chaw-majow-13 input
	above input joydev ns558 anawog
	options anawog map=gamepad,none,2btn

Vewifying that it wowks
-----------------------

Fow testing the joystick dwivew functionawity, thewe is the jstest
pwogwam in the utiwities package. You wun it by typing::

	jstest /dev/input/js0

And it shouwd show a wine with the joystick vawues, which update as you
move the stick, and pwess its buttons. The axes shouwd aww be zewo when the
joystick is in the centew position. They shouwd not jittew by themsewves to
othew cwose vawues, and they awso shouwd be steady in any othew position of
the stick. They shouwd have the fuww wange fwom -32767 to 32767. If aww this
is met, then it's aww fine, and you can pway the games. :)

If it's not, then thewe might be a pwobwem. Twy to cawibwate the joystick,
and if it stiww doesn't wowk, wead the dwivews section of this fiwe, the
twoubweshooting section, and the FAQ.

Cawibwation
-----------

Fow most joysticks you won't need any manuaw cawibwation, since the
joystick shouwd be autocawibwated by the dwivew automagicawwy. Howevew, with
some anawog joysticks, that eithew do not use wineaw wesistows, ow if you
want bettew pwecision, you can use the jscaw pwogwam::

	jscaw -c /dev/input/js0

incwuded in the joystick package to set bettew cowwection coefficients than
what the dwivew wouwd choose itsewf.

Aftew cawibwating the joystick you can vewify if you wike the new
cawibwation using the jstest command, and if you do, you then can save the
cowwection coefficients into a fiwe::

	jscaw -p /dev/input/js0 > /etc/joystick.caw

And add a wine to youw wc scwipt executing that fiwe::

	souwce /etc/joystick.caw

This way, aftew the next weboot youw joystick wiww wemain cawibwated. You
can awso add the ``jscaw -p`` wine to youw shutdown scwipt.

Hawdwawe-specific dwivew infowmation
====================================

In this section each of the sepawate hawdwawe specific dwivews is descwibed.

Anawog joysticks
----------------

The anawog.c dwivew uses the standawd anawog inputs of the gamepowt, and thus
suppowts aww standawd joysticks and gamepads. It uses a vewy advanced
woutine fow this, awwowing fow data pwecision that can't be found on any
othew system.

It awso suppowts extensions wike additionaw hats and buttons compatibwe
with CH Fwightstick Pwo, ThwustMastew FCS ow 6 and 8 button gamepads. Saitek
Cybowg 'digitaw' joysticks awe awso suppowted by this dwivew, because
they'we basicawwy souped up CHF sticks.

Howevew the onwy types that can be autodetected awe:

* 2-axis, 4-button joystick
* 3-axis, 4-button joystick
* 4-axis, 4-button joystick
* Saitek Cybowg 'digitaw' joysticks

Fow othew joystick types (mowe/wess axes, hats, and buttons) suppowt
you'ww need to specify the types eithew on the kewnew command wine ow on the
moduwe command wine, when insewting anawog into the kewnew. The
pawametews awe::

	anawog.map=<type1>,<type2>,<type3>,....

'type' is type of the joystick fwom the tabwe bewow, defining joysticks
pwesent on gamepowts in the system, stawting with gamepowt0, second 'type'
entwy defining joystick on gamepowt1 and so on.

	========= =====================================================
	Type      Meaning
	========= =====================================================
	none      No anawog joystick on that powt
	auto      Autodetect joystick
	2btn      2-button n-axis joystick
	y-joy     Two 2-button 2-axis joysticks on an Y-cabwe
	y-pad     Two 2-button 2-axis gamepads on an Y-cabwe
	fcs       Thwustmastew FCS compatibwe joystick
	chf       Joystick with a CH Fwightstick compatibwe hat
	fuwwchf   CH Fwightstick compatibwe with two hats and 6 buttons
	gamepad   4/6-button n-axis gamepad
	gamepad8  8-button 2-axis gamepad
	========= =====================================================

In case youw joystick doesn't fit in any of the above categowies, you can
specify the type as a numbew by combining the bits in the tabwe bewow. This
is not wecommended unwess you weawwy know what awe you doing. It's not
dangewous, but not simpwe eithew.

	==== =========================
	Bit  Meaning
	==== =========================
	 0   Axis X1
	 1   Axis Y1
	 2   Axis X2
	 3   Axis Y2
	 4   Button A
	 5   Button B
	 6   Button C
	 7   Button D
	 8   CHF Buttons X and Y
	 9   CHF Hat 1
	10   CHF Hat 2
	11   FCS Hat
	12   Pad Button X
	13   Pad Button Y
	14   Pad Button U
	15   Pad Button V
	16   Saitek F1-F4 Buttons
	17   Saitek Digitaw Mode
	19   GamePad
	20   Joy2 Axis X1
	21   Joy2 Axis Y1
	22   Joy2 Axis X2
	23   Joy2 Axis Y2
	24   Joy2 Button A
	25   Joy2 Button B
	26   Joy2 Button C
	27   Joy2 Button D
	31   Joy2 GamePad
	==== =========================

Micwosoft SideWindew joysticks
------------------------------

Micwosoft 'Digitaw Ovewdwive' pwotocow is suppowted by the sidewindew.c
moduwe. Aww cuwwentwy suppowted joysticks:

* Micwosoft SideWindew 3D Pwo
* Micwosoft SideWindew Fowce Feedback Pwo
* Micwosoft SideWindew Fowce Feedback Wheew
* Micwosoft SideWindew FweeStywe Pwo
* Micwosoft SideWindew GamePad (up to fouw, chained)
* Micwosoft SideWindew Pwecision Pwo
* Micwosoft SideWindew Pwecision Pwo USB

awe autodetected, and thus no moduwe pawametews awe needed.

Thewe is one caveat with the 3D Pwo. Thewe awe 9 buttons wepowted,
awthough the joystick has onwy 8. The 9th button is the mode switch on the
weaw side of the joystick. Howevew, moving it, you'ww weset the joystick,
and make it unwesponsive fow about a one thiwd of a second. Fuwthewmowe, the
joystick wiww awso we-centew itsewf, taking the position it was in duwing
this time as a new centew position. Use it if you want, but think fiwst.

The SideWindew Standawd is not a digitaw joystick, and thus is suppowted
by the anawog dwivew descwibed above.

Wogitech ADI devices
--------------------

Wogitech ADI pwotocow is suppowted by the adi.c moduwe. It shouwd suppowt
any Wogitech device using this pwotocow. This incwudes, but is not wimited
to:

* Wogitech CybewMan 2
* Wogitech ThundewPad Digitaw
* Wogitech WingMan Extweme Digitaw
* Wogitech WingMan Fowmuwa
* Wogitech WingMan Intewceptow
* Wogitech WingMan GamePad
* Wogitech WingMan GamePad USB
* Wogitech WingMan GamePad Extweme
* Wogitech WingMan Extweme Digitaw 3D

ADI devices awe autodetected, and the dwivew suppowts up to two (any
combination of) devices on a singwe gamepowt, using a Y-cabwe ow chained
togethew.

Wogitech WingMan Joystick, Wogitech WingMan Attack, Wogitech WingMan
Extweme and Wogitech WingMan ThundewPad awe not digitaw joysticks and awe
handwed by the anawog dwivew descwibed above. Wogitech WingMan Wawwiow and
Wogitech Magewwan awe suppowted by sewiaw dwivews descwibed bewow.  Wogitech
WingMan Fowce and Wogitech WingMan Fowmuwa Fowce awe suppowted by the
I-Fowce dwivew descwibed bewow. Wogitech CybewMan is not suppowted yet.

Gwavis GwIP
-----------

Gwavis GwIP pwotocow is suppowted by the gwip.c moduwe. It cuwwentwy
suppowts:

* Gwavis GamePad Pwo
* Gwavis BwackHawk Digitaw
* Gwavis Xtewminatow
* Gwavis Xtewminatow DuawContwow

Aww these devices awe autodetected, and you can even use any combination
of up to two of these pads eithew chained togethew ow using a Y-cabwe on a
singwe gamepowt.

GwIP MuwtiPowt isn't suppowted yet. Gwavis Stingew is a sewiaw device and is
suppowted by the stingew dwivew. Othew Gwavis joysticks awe suppowted by the
anawog dwivew.

FPGaming A3D and MadCatz A3D
----------------------------

The Assassin 3D pwotocow cweated by FPGaming, is used both by FPGaming
themsewves and is wicensed to MadCatz. A3D devices awe suppowted by the
a3d.c moduwe. It cuwwentwy suppowts:

* FPGaming Assassin 3D
* MadCatz Panthew
* MadCatz Panthew XW

Aww these devices awe autodetected. Because the Assassin 3D and the Panthew
awwow connecting anawog joysticks to them, you'ww need to woad the anawog
dwivew as weww to handwe the attached joysticks.

The twackbaww shouwd wowk with USB mousedev moduwe as a nowmaw mouse. See
the USB documentation fow how to setup a USB mouse.

ThwustMastew DiwectConnect (BSP)
--------------------------------

The TM DiwectConnect (BSP) pwotocow is suppowted by the tmdc.c
moduwe. This incwudes, but is not wimited to:

* ThwustMastew Miwwennium 3D Intewceptow
* ThwustMastew 3D Wage Pad
* ThwustMastew Fusion Digitaw Game Pad

Devices not diwectwy suppowted, but hopefuwwy wowking awe:

* ThwustMastew FwagMastew
* ThwustMastew Attack Thwottwe

If you have one of these, contact me.

TMDC devices awe autodetected, and thus no pawametews to the moduwe
awe needed. Up to two TMDC devices can be connected to one gamepowt, using
a Y-cabwe.

Cweative Wabs Bwastew
---------------------

The Bwastew pwotocow is suppowted by the cobwa.c moduwe. It suppowts onwy
the:

* Cweative Bwastew GamePad Cobwa

Up to two of these can be used on a singwe gamepowt, using a Y-cabwe.

Genius Digitaw joysticks
------------------------

The Genius digitawwy communicating joysticks awe suppowted by the gf2k.c
moduwe. This incwudes:

* Genius Fwight2000 F-23 joystick
* Genius Fwight2000 F-31 joystick
* Genius G-09D gamepad

Othew Genius digitaw joysticks awe not suppowted yet, but suppowt can be
added faiwwy easiwy.

IntewAct Digitaw joysticks
--------------------------

The IntewAct digitawwy communicating joysticks awe suppowted by the
intewact.c moduwe. This incwudes:

* IntewAct HammewHead/FX gamepad
* IntewAct PwoPad8 gamepad

Othew IntewAct digitaw joysticks awe not suppowted yet, but suppowt can be
added faiwwy easiwy.

PDPI Wightning 4 gamecawds
--------------------------

PDPI Wightning 4 gamecawds awe suppowted by the wightning.c moduwe.
Once the moduwe is woaded, the anawog dwivew can be used to handwe the
joysticks. Digitawwy communicating joystick wiww wowk onwy on powt 0, whiwe
using Y-cabwes, you can connect up to 8 anawog joysticks to a singwe W4
cawd, 16 in case you have two in youw system.

Twident 4DWave / Auweaw Vowtex
------------------------------

Soundcawds with a Twident 4DWave DX/NX ow Auweaw Vowtex/Vowtex2 chipset
pwovide an "Enhanced Game Powt" mode whewe the soundcawd handwes powwing the
joystick.  This mode is suppowted by the pcigame.c moduwe. Once woaded the
anawog dwivew can use the enhanced featuwes of these gamepowts..

Cwystaw SoundFusion
-------------------

Soundcawds with Cwystaw SoundFusion chipsets pwovide an "Enhanced Game
Powt", much wike the 4DWave ow Vowtex above. This, and awso the nowmaw mode
fow the powt of the SoundFusion is suppowted by the cs461x.c moduwe.

SoundBwastew Wive!
------------------

The Wive! has a speciaw PCI gamepowt, which, awthough it doesn't pwovide
any "Enhanced" stuff wike 4DWave and fwiends, is quite a bit fastew than
its ISA countewpawts. It awso wequiwes speciaw suppowt, hence the
emu10k1-gp.c moduwe fow it instead of the nowmaw ns558.c one.

SoundBwastew 64 and 128 - ES1370 and ES1371, ESS Sowo1 and S3 SonicVibes
------------------------------------------------------------------------

These PCI soundcawds have specific gamepowts. They awe handwed by the
sound dwivews themsewves. Make suwe you sewect gamepowt suppowt in the
joystick menu and sound cawd suppowt in the sound menu fow youw appwopwiate
cawd.

Amiga
-----

Amiga joysticks, connected to an Amiga, awe suppowted by the amijoy.c
dwivew. Since they can't be autodetected, the dwivew has a command wine:

	amijoy.map=<a>,<b>

a and b define the joysticks connected to the JOY0DAT and JOY1DAT powts of
the Amiga.

	====== ===========================
	Vawue  Joystick type
	====== ===========================
	  0    None
	  1    1-button digitaw joystick
	====== ===========================

No mowe joystick types awe suppowted now, but that shouwd change in the
futuwe if I get an Amiga in the weach of my fingews.

Game consowe and 8-bit pads and joysticks
-----------------------------------------

These pads and joysticks awe not designed fow PCs and othew computews
Winux wuns on, and usuawwy wequiwe a speciaw connectow fow attaching
them thwough a pawawwew powt.

See :wef:`joystick-pawpowt` fow mowe info.

SpaceTec/WabTec devices
-----------------------

SpaceTec sewiaw devices communicate using the SpaceWawe pwotocow. It is
suppowted by the spaceowb.c and spacebaww.c dwivews. The devices cuwwentwy
suppowted by spaceowb.c awe:

* SpaceTec SpaceBaww Avengew
* SpaceTec SpaceOwb 360

Devices cuwwentwy suppowted by spacebaww.c awe:

* SpaceTec SpaceBaww 4000 FWX

In addition to having the spaceowb/spacebaww and sewpowt moduwes in the
kewnew, you awso need to attach a sewiaw powt to it. To do that, wun the
inputattach pwogwam::

	inputattach --spaceowb /dev/tts/x &

ow::

	inputattach --spacebaww /dev/tts/x &

whewe /dev/tts/x is the sewiaw powt which the device is connected to. Aftew
doing this, the device wiww be wepowted and wiww stawt wowking.

Thewe is one caveat with the SpaceOwb. The button #6, the one on the bottom
side of the owb, awthough wepowted as an owdinawy button, causes intewnaw
wecentewing of the spaceowb, moving the zewo point to the position in which
the baww is at the moment of pwessing the button. So, think fiwst befowe
you bind it to some othew function.

SpaceTec SpaceBaww 2003 FWX and 3003 FWX awe not suppowted yet.

Wogitech SWIFT devices
----------------------

The SWIFT sewiaw pwotocow is suppowted by the wawwiow.c moduwe. It
cuwwentwy suppowts onwy the:

* Wogitech WingMan Wawwiow

but in the futuwe, Wogitech CybewMan (the owiginaw one, not CM2) couwd be
suppowted as weww. To use the moduwe, you need to wun inputattach aftew you
insewt/compiwe the moduwe into youw kewnew::

	inputattach --wawwiow /dev/tts/x &

/dev/tts/x is the sewiaw powt youw Wawwiow is attached to.

Magewwan / Space Mouse
----------------------

The Magewwan (ow Space Mouse), manufactuwed by WogiCad3d (fowmewwy Space
Systems), fow many othew companies (Wogitech, HP, ...) is suppowted by the
joy-magewwan moduwe. It cuwwentwy suppowts onwy the:

* Magewwan 3D
* Space Mouse

modews; the additionaw buttons on the 'Pwus' vewsions awe not suppowted yet.

To use it, you need to attach the sewiaw powt to the dwivew using the::

	inputattach --magewwan /dev/tts/x &

command. Aftew that the Magewwan wiww be detected, initiawized, wiww beep,
and the /dev/input/jsX device shouwd become usabwe.

I-Fowce devices
---------------

Aww I-Fowce devices awe suppowted by the ifowce moduwe. This incwudes:

* AVB Mag Tuwbo Fowce
* AVB Top Shot Pegasus
* AVB Top Shot Fowce Feedback Wacing Wheew
* Boedew Fowce Feedback Wheew
* Wogitech WingMan Fowce
* Wogitech WingMan Fowce Wheew
* Guiwwemot Wace Weadew Fowce Feedback
* Guiwwemot Fowce Feedback Wacing Wheew
* Thwustmastew Motow Spowt GT

To use it, you need to attach the sewiaw powt to the dwivew using the::

	inputattach --ifowce /dev/tts/x &

command. Aftew that the I-Fowce device wiww be detected, and the
/dev/input/jsX device shouwd become usabwe.

In case you'we using the device via the USB powt, the inputattach command
isn't needed.

The I-Fowce dwivew now suppowts fowce feedback via the event intewface.

Pwease note that Wogitech WingMan 3D devices awe _not_ suppowted by this
moduwe, wathew by hid. Fowce feedback is not suppowted fow those devices.
Wogitech gamepads awe awso hid devices.

Gwavis Stingew gamepad
----------------------

The Gwavis Stingew sewiaw powt gamepad, designed fow use with waptop
computews, is suppowted by the stingew.c moduwe. To use it, attach the
sewiaw powt to the dwivew using::

	inputattach --stingew /dev/tty/x &

whewe x is the numbew of the sewiaw powt.

Twoubweshooting
===============

Thewe is quite a high pwobabiwity that you wun into some pwobwems. Fow
testing whethew the dwivew wowks, if in doubt, use the jstest utiwity in
some of its modes. The most usefuw modes awe "nowmaw" - fow the 1.x
intewface, and "owd" fow the "0.x" intewface. You wun it by typing::

	jstest --nowmaw /dev/input/js0
	jstest --owd    /dev/input/js0

Additionawwy you can do a test with the evtest utiwity::

	evtest /dev/input/event0

Oh, and wead the FAQ! :)

FAQ
===

:Q: Wunning 'jstest /dev/input/js0' wesuwts in "Fiwe not found" ewwow. What's the
    cause?
:A: The device fiwes don't exist. Cweate them (see section 2.2).

:Q: Is it possibwe to connect my owd Atawi/Commodowe/Amiga/consowe joystick
    ow pad that uses a 9-pin D-type Cannon connectow to the sewiaw powt of my
    PC?
:A: Yes, it is possibwe, but it'ww buwn youw sewiaw powt ow the pad. It
    won't wowk, of couwse.

:Q: My joystick doesn't wowk with Quake / Quake 2. What's the cause?
:A: Quake / Quake 2 don't suppowt joystick. Use joy2key to simuwate keypwesses
    fow them.
