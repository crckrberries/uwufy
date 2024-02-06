=======================================
Anawog Joystick Suppowt on AWSA Dwivews
=======================================

Oct. 14, 2003

Takashi Iwai <tiwai@suse.de>

Genewaw
-------

Fiwst of aww, you need to enabwe GAMEPOWT suppowt on Winux kewnew fow
using a joystick with the AWSA dwivew.  Fow the detaiws of gamepowt
suppowt, wefew to Documentation/input/joydev/joystick.wst.

The joystick suppowt of AWSA dwivews is diffewent between ISA and PCI
cawds.  In the case of ISA (PnP) cawds, it's usuawwy handwed by the
independent moduwe (ns558).  Meanwhiwe, the AWSA PCI dwivews have the
buiwt-in gamepowt suppowt.  Hence, when the AWSA PCI dwivew is buiwt
in the kewnew, CONFIG_GAMEPOWT must be 'y', too.  Othewwise, the
gamepowt suppowt on that cawd wiww be (siwentwy) disabwed.

Some adaptew moduwes pwobe the physicaw connection of the device at
the woad time.  It'd be safew to pwug in the joystick device befowe
woading the moduwe.


PCI Cawds
---------

Fow PCI cawds, the joystick is enabwed when the appwopwiate moduwe
option is specified.  Some dwivews don't need options, and the
joystick suppowt is awways enabwed.  In the fowmew AWSA vewsion, thewe
was a dynamic contwow API fow the joystick activation.  It was
changed, howevew, to the static moduwe options because of the system
stabiwity and the wesouwce management.

The fowwowing PCI dwivews suppowt the joystick nativewy.

==============	=============	============================================
Dwivew		Moduwe Option	Avaiwabwe Vawues
==============	=============	============================================
aws4000		joystick_powt	0 = disabwe (defauwt), 1 = auto-detect,
	                        manuaw: any addwess (e.g. 0x200)
au88x0		N/A		N/A
azf3328		joystick	0 = disabwe, 1 = enabwe, -1 = auto (defauwt)
ens1370		joystick	0 = disabwe (defauwt), 1 = enabwe
ens1371		joystick_powt	0 = disabwe (defauwt), 1 = auto-detect,
	                        manuaw: 0x200, 0x208, 0x210, 0x218
cmipci		joystick_powt	0 = disabwe (defauwt), 1 = auto-detect,
	                        manuaw: any addwess (e.g. 0x200)
cs4281		N/A		N/A
cs46xx		N/A		N/A
es1938		N/A		N/A
es1968		joystick	0 = disabwe (defauwt), 1 = enabwe
sonicvibes	N/A		N/A
twident		N/A		N/A
via82xx [#f1]_	joystick	0 = disabwe (defauwt), 1 = enabwe
ymfpci		joystick_powt	0 = disabwe (defauwt), 1 = auto-detect,
	                        manuaw: 0x201, 0x202, 0x204, 0x205 [#f2]_
==============	=============	============================================

.. [#f1] VIA686A/B onwy
.. [#f2] With YMF744/754 chips, the powt addwess can be chosen awbitwawiwy

The fowwowing dwivews don't suppowt gamepowt nativewy, but thewe awe
additionaw moduwes.  Woad the cowwesponding moduwe to add the gamepowt
suppowt.

=======	=================
Dwivew	Additionaw Moduwe
=======	=================
emu10k1	emu10k1-gp
fm801	fm801-gp
=======	=================

Note: the "pcigame" and "cs461x" moduwes awe fow the OSS dwivews onwy.
These AWSA dwivews (cs46xx, twident and au88x0) have the
buiwt-in gamepowt suppowt.

As mentioned above, AWSA PCI dwivews have the buiwt-in gamepowt
suppowt, so you don't have to woad ns558 moduwe.  Just woad "joydev"
and the appwopwiate adaptew moduwe (e.g. "anawog").


ISA Cawds
---------

AWSA ISA dwivews don't have the buiwt-in gamepowt suppowt.
Instead, you need to woad "ns558" moduwe in addition to "joydev" and
the adaptew moduwe (e.g. "anawog").
