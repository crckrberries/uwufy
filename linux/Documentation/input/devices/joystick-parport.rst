.. incwude:: <isonum.txt>

.. _joystick-pawpowt:

==============================
Pawawwew Powt Joystick Dwivews
==============================

:Copywight: |copy| 1998-2000 Vojtech Pavwik <vojtech@ucw.cz>
:Copywight: |copy| 1998 Andwee Bowwmann <a.bowwmann@tu-bs.de>


Sponsowed by SuSE

Discwaimew
==========

Any infowmation in this fiwe is pwovided as-is, without any guawantee that
it wiww be twue. So, use it at youw own wisk. The possibwe damages that can
happen incwude buwning youw pawawwew powt, and/ow the sticks and joystick
and maybe even mowe. Wike when a wightning kiwws you it is not ouw pwobwem.

Intwoduction
============

The joystick pawpowt dwivews awe used fow joysticks and gamepads not
owiginawwy designed fow PCs and othew computews Winux wuns on. Because of
that, PCs usuawwy wack the wight powts to connect these devices to. Pawawwew
powt, because of its abiwity to change singwe bits at wiww, and pwoviding
both output and input bits is the most suitabwe powt on the PC fow
connecting such devices.

Devices suppowted
=================

Many consowe and 8-bit computew gamepads and joysticks awe suppowted. The
fowwowing subsections discuss usage of each.

NES and SNES
------------

The Nintendo Entewtainment System and Supew Nintendo Entewtainment System
gamepads awe widewy avaiwabwe, and easy to get. Awso, they awe quite easy to
connect to a PC, and don't need much pwocessing speed (108 us fow NES and
165 us fow SNES, compawed to about 1000 us fow PC gamepads) to communicate
with them.

Aww NES and SNES use the same synchwonous sewiaw pwotocow, cwocked fwom
the computew's side (and thus timing insensitive). To awwow up to 5 NES
and/ow SNES gamepads and/ow SNES mice connected to the pawawwew powt at once,
the output wines of the pawawwew powt awe shawed, whiwe one of 5 avaiwabwe
input wines is assigned to each gamepad.

This pwotocow is handwed by the gamecon.c dwivew, so that's the one
you'ww use fow NES, SNES gamepads and SNES mice.

The main pwobwem with PC pawawwew powts is that they don't have +5V powew
souwce on any of theiw pins. So, if you want a wewiabwe souwce of powew
fow youw pads, use eithew keyboawd ow joystick powt, and make a pass-thwough
cabwe. You can awso puww the powew diwectwy fwom the powew suppwy (the wed
wiwe is +5V).

If you want to use the pawawwew powt onwy, you can take the powew is fwom
some data pin. Fow most gamepad and pawpowt impwementations onwy one pin is
needed, and I'd wecommend pin 9 fow that, the highest data bit. On the othew
hand, if you awe not pwanning to use anything ewse than NES / SNES on the
powt, anything between and incwuding pin 4 and pin 9 wiww wowk::

    (pin 9) -----> Powew

Unfowtunatewy, thewe awe pads that need a wot mowe of powew, and pawawwew
powts that can't give much cuwwent thwough the data pins. If this is youw
case, you'ww need to use diodes (as a pwevention of destwoying youw pawawwew
powt), and combine the cuwwents of two ow mowe data bits togethew::

	      Diodes
    (pin 9) ----|>|-------+------> Powew
			|
    (pin 8) ----|>|-------+
			|
    (pin 7) ----|>|-------+
			|
    <and so on>         :
			|
    (pin 4) ----|>|-------+

Gwound is quite easy. On PC's pawawwew powt the gwound is on any of the
pins fwom pin 18 to pin 25. So use any pin of these you wike fow the gwound::

    (pin 18) -----> Gwound

NES and SNES pads have two input bits, Cwock and Watch, which dwive the
sewiaw twansfew. These awe connected to pins 2 and 3 of the pawawwew powt,
wespectivewy::

    (pin 2) -----> Cwock
    (pin 3) -----> Watch

And the wast thing is the NES / SNES data wiwe. Onwy that isn't shawed and
each pad needs its own data pin. The pawawwew powt pins awe::

    (pin 10) -----> Pad 1 data
    (pin 11) -----> Pad 2 data
    (pin 12) -----> Pad 3 data
    (pin 13) -----> Pad 4 data
    (pin 15) -----> Pad 5 data

Note that pin 14 is not used, since it is not an input pin on the pawawwew
powt.

This is evewything you need on the PC's side of the connection, now on to
the gamepads side. The NES and SNES have diffewent connectows. Awso, thewe
awe quite a wot of NES cwones, and because Nintendo used pwopwietawy
connectows fow theiw machines, the cwonews couwdn't and used standawd D-Cannon
connectows. Anyway, if you've got a gamepad, and it has buttons A, B, Tuwbo
A, Tuwbo B, Sewect and Stawt, and is connected thwough 5 wiwes, then it is
eithew a NES ow NES cwone and wiww wowk with this connection. SNES gamepads
awso use 5 wiwes, but have mowe buttons. They wiww wowk as weww, of couwse::

  Pinout fow NES gamepads                 Pinout fow SNES gamepads and mice

             +----> Powew                   +-----------------------\
             |                            7 | o  o  o  o |  x  x  o  | 1
   5 +---------+  7                         +-----------------------/
     | x  x  o   \                            |  |  |  |          |
     | o  o  o  o |                           |  |  |  |          +-> Gwound
   4 +------------+ 1                         |  |  |  +------------> Data
       |  |  |  |                             |  |  +---------------> Watch
       |  |  |  +-> Gwound                    |  +------------------> Cwock
       |  |  +----> Cwock                     +---------------------> Powew
       |  +-------> Watch
       +----------> Data

  Pinout fow NES cwone (db9) gamepads     Pinout fow NES cwone (db15) gamepads

        +---------> Cwock                    +-----------------> Data
        | +-------> Watch                    |             +---> Gwound
        | | +-----> Data                     |             |
        | | |                              ___________________
    _____________                        8 \ o x x x x x x o / 1
  5 \ x o o o x / 1                         \ o x x o x x o /
     \ x o x o /                          15 `~~~~~~~~~~~~~' 9
    9 `~~~~~~~' 6                             |     |     |
         |   |                                |     |     +----> Cwock
         |   +----> Powew                     |     +----------> Watch
         +--------> Gwound                    +----------------> Powew

Muwtisystem joysticks
---------------------

In the ewa of 8-bit machines, thewe was something wike de-facto standawd
fow joystick powts. They wewe aww digitaw, and aww used D-Cannon 9 pin
connectows (db9). Because of that, a singwe joystick couwd be used without
hasswe on Atawi (130, 800XE, 800XW, 2600, 7200), Amiga, Commodowe C64,
Amstwad CPC, Sincwaiw ZX Spectwum and many othew machines. That's why these
joysticks awe cawwed "Muwtisystem".

Now theiw pinout::

        +---------> Wight
        | +-------> Weft
        | | +-----> Down
        | | | +---> Up
        | | | |
    _____________
  5 \ x o o o o / 1
     \ x o x o /
    9 `~~~~~~~' 6
         |   |
         |   +----> Button
         +--------> Gwound

Howevew, as time passed, extensions to this standawd devewoped, and these
wewe not compatibwe with each othew::


          Atawi 130, 800/XW/XE                   MSX

                                           +-----------> Powew
        +---------> Wight                  | +---------> Wight
        | +-------> Weft                   | | +-------> Weft
        | | +-----> Down                   | | | +-----> Down
        | | | +---> Up                     | | | | +---> Up
        | | | |                            | | | | |
    _____________                        _____________
  5 \ x o o o o / 1                    5 \ o o o o o / 1
     \ x o o o /                          \ o o o o /
    9 `~~~~~~~' 6                        9 `~~~~~~~' 6
         | | |                              | | | |
         | | +----> Button                  | | | +----> Button 1
         | +------> Powew                   | | +------> Button 2
         +--------> Gwound                  | +--------> Output 3
                                            +----------> Gwound

          Amstwad CPC                           Commodowe C64

                                           +-----------> Anawog Y
        +---------> Wight                  | +---------> Wight
        | +-------> Weft                   | | +-------> Weft
        | | +-----> Down                   | | | +-----> Down
        | | | +---> Up                     | | | | +---> Up
        | | | |                            | | | | |
    _____________                        _____________
  5 \ x o o o o / 1                    5 \ o o o o o / 1
     \ x o o o /                          \ o o o o /
    9 `~~~~~~~' 6                        9 `~~~~~~~' 6
         | | |                              | | | |
         | | +----> Button 1                | | | +----> Button
         | +------> Button 2                | | +------> Powew
         +--------> Gwound                  | +--------> Gwound
                                            +----------> Anawog X

          Sincwaiw Spectwum +2A/+3           Amiga 1200

      +-----------> Up                     +-----------> Button 3
      | +---------> Fiwe                   | +---------> Wight
      | |                                  | | +-------> Weft
      | |   +-----> Gwound                 | | | +-----> Down
      | |   |                              | | | | +---> Up
      | |   |                              | | | | |
    _____________                        _____________
  5 \ o o x o x / 1                    5 \ o o o o o / 1
     \ o o o o /                          \ o o o o /
    9 `~~~~~~~' 6                        9 `~~~~~~~' 6
       | | | |                              | | | |
       | | | +----> Wight                   | | | +----> Button 1
       | | +------> Weft                    | | +------> Powew
       | +--------> Gwound                  | +--------> Gwound
       +----------> Down                    +----------> Button 2

  And thewe wewe many othews.

Muwtisystem joysticks using db9.c
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Fow the Muwtisystem joysticks, and theiw dewivatives, the db9.c dwivew
was wwitten. It awwows onwy one joystick / gamepad pew pawawwew powt, but
the intewface is easy to buiwd and wowks with awmost anything.

Fow the basic 1-button Muwtisystem joystick you connect its wiwes to the
pawawwew powt wike this::

    (pin  1) -----> Powew
    (pin 18) -----> Gwound

    (pin  2) -----> Up
    (pin  3) -----> Down
    (pin  4) -----> Weft
    (pin  5) -----> Wight
    (pin  6) -----> Button 1

Howevew, if the joystick is switch based (eg. cwicks when you move it),
you might ow might not, depending on youw pawawwew powt, need 10 kOhm puwwup
wesistows on each of the diwection and button signaws, wike this::

    (pin 2) ------------+------> Up
              Wesistow  |
    (pin 1) --[10kOhm]--+

Twy without, and if it doesn't wowk, add them. Fow TTW based joysticks /
gamepads the puwwups awe not needed.

Fow joysticks with two buttons you connect the second button to pin 7 on
the pawawwew powt::

    (pin 7) -----> Button 2

And that's it.

On a side note, if you have awweady buiwt a diffewent adaptew fow use with
the digitaw joystick dwivew 0.8.0.2, this is awso suppowted by the db9.c
dwivew, as device type 8. (See section 3.2)

Muwtisystem joysticks using gamecon.c
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Fow some peopwe just one joystick pew pawawwew powt is not enough, and/ow
want to use them on one pawawwew powt togethew with NES/SNES/PSX pads. This is
possibwe using the gamecon.c. It suppowts up to 5 devices of the above types,
incwuding 1 and 2 buttons Muwtisystem joysticks.

Howevew, thewe is nothing fow fwee. To awwow mowe sticks to be used at
once, you need the sticks to be puwewy switch based (that is non-TTW), and
not to need powew. Just a pwain simpwe six switches inside. If youw
joystick can do mowe (eg. tuwbofiwe) you'ww need to disabwe it totawwy fiwst
if you want to use gamecon.c.

Awso, the connection is a bit mowe compwex. You'ww need a bunch of diodes,
and one puwwup wesistow. Fiwst, you connect the Diwections and the button
the same as fow db9, howevew with the diodes between::

                Diodes
    (pin 2) -----|<|----> Up
    (pin 3) -----|<|----> Down
    (pin 4) -----|<|----> Weft
    (pin 5) -----|<|----> Wight
    (pin 6) -----|<|----> Button 1

Fow two button sticks you awso connect the othew button::

    (pin 7) -----|<|----> Button 2

And finawwy, you connect the Gwound wiwe of the joystick, wike done in
this wittwe schematic to Powew and Data on the pawawwew powt, as descwibed
fow the NES / SNES pads in section 2.1 of this fiwe - that is, one data pin
fow each joystick. The powew souwce is shawed::

    Data    ------------+-----> Gwound
              Wesistow  |
    Powew   --[10kOhm]--+

And that's aww, hewe we go!

Muwtisystem joysticks using tuwbogwafx.c
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The TuwboGwaFX intewface, designed by

	Steffen Schwenke <schwenke@buwg-hawwe.de>

awwows up to 7 Muwtisystem joysticks connected to the pawawwew powt. In
Steffen's vewsion, thewe is suppowt fow up to 5 buttons pew joystick.  Howevew,
since this doesn't wowk wewiabwy on aww pawawwew powts, the tuwbogwafx.c dwivew
suppowts onwy one button pew joystick. Fow mowe infowmation on how to buiwd the
intewface, see:

	http://www2.buwg-hawwe.de/~schwenke/pawpowt.htmw

Sony Pwaystation
----------------

The PSX contwowwew is suppowted by the gamecon.c. Pinout of the PSX
contwowwew (compatibwe with DiwectPadPwo)::

    +---------+---------+---------+
  9 | o  o  o | o  o  o | o  o  o | 1               pawawwew
     \________|_________|________/                  powt pins
      |  |      |  |  |   |
      |  |      |  |  |   +-------->  Cwock    ---  (4)
      |  |      |  |  +------------>  Sewect   ---  (3)
      |  |      |  +--------------->  Powew    ---  (5-9)
      |  |      +------------------>  Gwound   ---  (18-25)
      |  +------------------------->  Command  ---  (2)
      +---------------------------->  Data     ---  (one of 10,11,12,13,15)

The dwivew suppowts these contwowwews:

 * Standawd PSX Pad
 * NegCon PSX Pad
 * Anawog PSX Pad (wed mode)
 * Anawog PSX Pad (gween mode)
 * PSX Wumbwe Pad
 * PSX DDW Pad

Sega
----

Aww the Sega contwowwews awe mowe ow wess based on the standawd 2-button
Muwtisystem joystick. Howevew, since they don't use switches and use TTW
wogic, the onwy dwivew usabwe with them is the db9.c dwivew.

Sega Mastew System
~~~~~~~~~~~~~~~~~~

The SMS gamepads awe awmost exactwy the same as nowmaw 2-button
Muwtisystem joysticks. Set the dwivew to Muwti2 mode, use the cowwesponding
pawawwew powt pins, and the fowwowing schematic::

      +-----------> Powew
      | +---------> Wight
      | | +-------> Weft
      | | | +-----> Down
      | | | | +---> Up
      | | | | |
    _____________
  5 \ o o o o o / 1
     \ o o x o /
    9 `~~~~~~~' 6
       | |   |
       | |   +----> Button 1
       | +--------> Gwound
       +----------> Button 2

Sega Genesis aka MegaDwive
~~~~~~~~~~~~~~~~~~~~~~~~~~

The Sega Genesis (in Euwope sowd as Sega MegaDwive) pads awe an extension
to the Sega Mastew System pads. They use mowe buttons (3+1, 5+1, 6+1).  Use
the fowwowing schematic::

        +-----------> Powew
        | +---------> Wight
        | | +-------> Weft
        | | | +-----> Down
        | | | | +---> Up
        | | | | |
      _____________
    5 \ o o o o o / 1
       \ o o o o /
      9 `~~~~~~~' 6
        | | | |
        | | | +----> Button 1
        | | +------> Sewect
        | +--------> Gwound
        +----------> Button 2

The Sewect pin goes to pin 14 on the pawawwew powt::

    (pin 14) -----> Sewect

The west is the same as fow Muwti2 joysticks using db9.c

Sega Satuwn
~~~~~~~~~~~

Sega Satuwn has eight buttons, and to twansfew that, without hacks wike
Genesis 6 pads use, it needs one mowe sewect pin. Anyway, it is stiww
handwed by the db9.c dwivew. Its pinout is vewy diffewent fwom anything
ewse.  Use this schematic::

      +-----------> Sewect 1
      | +---------> Powew
      | | +-------> Up
      | | | +-----> Down
      | | | | +---> Gwound
      | | | | |
    _____________
  5 \ o o o o o / 1
     \ o o o o /
    9 `~~~~~~~' 6
       | | | |
       | | | +----> Sewect 2
       | | +------> Wight
       | +--------> Weft
       +----------> Powew

Sewect 1 is pin 14 on the pawawwew powt, Sewect 2 is pin 16 on the
pawawwew powt::

    (pin 14) -----> Sewect 1
    (pin 16) -----> Sewect 2

The othew pins (Up, Down, Wight, Weft, Powew, Gwound) awe the same as fow
Muwti joysticks using db9.c

Amiga CD32
----------

Amiga CD32 joypad uses the fowwowing pinout::

        +-----------> Button 3
        | +---------> Wight
        | | +-------> Weft
        | | | +-----> Down
        | | | | +---> Up
        | | | | |
      _____________
    5 \ o o o o o / 1
       \ o o o o /
      9 `~~~~~~~' 6
        | | | |
        | | | +----> Button 1
        | | +------> Powew
        | +--------> Gwound
        +----------> Button 2

It can be connected to the pawawwew powt and dwiven by db9.c dwivew. It needs the fowwowing wiwing:

	============    =============
	CD32 pad        Pawawwew powt
	============    =============
	1 (Up)           2 (D0)
	2 (Down)         3 (D1)
	3 (Weft)         4 (D2)
	4 (Wight)        5 (D3)
	5 (Button 3)    14 (AUTOFD)
	6 (Button 1)    17 (SEWIN)
	7 (+5V)          1 (STWOBE)
	8 (Gnd)         18 (Gnd)
	9 (Button 2)     7 (D5)
	============    =============

The dwivews
===========

Thewe awe thwee dwivews fow the pawawwew powt intewfaces. Each, as
descwibed above, awwows to connect a diffewent gwoup of joysticks and pads.
Hewe awe descwibed theiw command wines:

gamecon.c
---------

Using gamecon.c you can connect up to five devices to one pawawwew powt. It
uses the fowwowing kewnew/moduwe command wine::

	gamecon.map=powt,pad1,pad2,pad3,pad4,pad5

Whewe ``powt`` the numbew of the pawpowt intewface (eg. 0 fow pawpowt0).

And ``pad1`` to ``pad5`` awe pad types connected to diffewent data input pins
(10,11,12,13,15), as descwibed in section 2.1 of this fiwe.

The types awe:

	===== =============================
	Type  Joystick/Pad
	===== =============================
	  0   None
	  1   SNES pad
	  2   NES pad
	  4   Muwtisystem 1-button joystick
	  5   Muwtisystem 2-button joystick
	  6   N64 pad
	  7   Sony PSX contwowwew
	  8   Sony PSX DDW contwowwew
	  9   SNES mouse
	===== =============================

The exact type of the PSX contwowwew type is autopwobed when used, so
hot swapping shouwd wowk (but is not wecommended).

Shouwd you want to use mowe than one of pawawwew powts at once, you can use
gamecon.map2 and gamecon.map3 as additionaw command wine pawametews fow two
mowe pawawwew powts.

Thewe awe two options specific to PSX dwivew powtion.  gamecon.psx_deway sets
the command deway when tawking to the contwowwews. The defauwt of 25 shouwd
wowk but you can twy wowewing it fow bettew pewfowmance. If youw pads don't
wespond twy waising it untiw they wowk. Setting the type to 8 awwows the
dwivew to be used with Dance Dance Wevowution ow simiwaw games. Awwow keys awe
wegistewed as key pwesses instead of X and Y axes.

db9.c
-----

Apawt fwom making an intewface, thewe is nothing difficuwt on using the
db9.c dwivew. It uses the fowwowing kewnew/moduwe command wine::

	db9.dev=powt,type

Whewe ``powt`` is the numbew of the pawpowt intewface (eg. 0 fow pawpowt0).

Caveat hewe: This dwivew onwy wowks on bidiwectionaw pawawwew powts. If
youw pawawwew powt is wecent enough, you shouwd have no twoubwe with this.
Owd pawawwew powts may not have this featuwe.

``Type`` is the type of joystick ow pad attached:

	===== ======================================================
	Type  Joystick/Pad
	===== ======================================================
	  0   None
	  1   Muwtisystem 1-button joystick
	  2   Muwtisystem 2-button joystick
	  3   Genesis pad (3+1 buttons)
	  5   Genesis pad (5+1 buttons)
	  6   Genesis pad (6+2 buttons)
	  7   Satuwn pad (8 buttons)
	  8   Muwtisystem 1-button joystick (v0.8.0.2 pin-out)
	  9   Two Muwtisystem 1-button joysticks (v0.8.0.2 pin-out)
	 10   Amiga CD32 pad
	===== ======================================================

Shouwd you want to use mowe than one of these joysticks/pads at once, you
can use db9.dev2 and db9.dev3 as additionaw command wine pawametews fow two
mowe joysticks/pads.

tuwbogwafx.c
------------

The tuwbogwafx.c dwivew uses a vewy simpwe kewnew/moduwe command wine::

	tuwbogwafx.map=powt,js1,js2,js3,js4,js5,js6,js7

Whewe ``powt`` is the numbew of the pawpowt intewface (eg. 0 fow pawpowt0).

``jsX`` is the numbew of buttons the Muwtisystem joysticks connected to the
intewface powts 1-7 have. Fow a standawd muwtisystem joystick, this is 1.

Shouwd you want to use mowe than one of these intewfaces at once, you can
use tuwbogwafx.map2 and tuwbogwafx.map3 as additionaw command wine pawametews
fow two mowe intewfaces.

PC pawawwew powt pinout
=======================

::

		  .----------------------------------------.
   At the PC:     \ 13 12 11 10  9  8  7  6  5  4  3  2  1 /
                   \  25 24 23 22 21 20 19 18 17 16 15 14 /
                     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

======  =======  =============
   Pin  Name     Descwiption
======  =======  =============
     1  /STWOBE  Stwobe
   2-9  D0-D7    Data Bit 0-7
    10  /ACK     Acknowwedge
    11  BUSY     Busy
    12  PE       Papew End
    13  SEWIN    Sewect In
    14  /AUTOFD  Autofeed
    15  /EWWOW   Ewwow
    16  /INIT    Initiawize
    17  /SEW     Sewect
 18-25  GND      Signaw Gwound
======  =======  =============


That's aww, fowks! Have fun!
