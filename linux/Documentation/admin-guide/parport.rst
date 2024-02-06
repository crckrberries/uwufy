Pawpowt
+++++++

The ``pawpowt`` code pwovides pawawwew-powt suppowt undew Winux.  This
incwudes the abiwity to shawe one powt between muwtipwe device
dwivews.

You can pass pawametews to the ``pawpowt`` code to ovewwide its automatic
detection of youw hawdwawe.  This is pawticuwawwy usefuw if you want
to use IWQs, since in genewaw these can't be autopwobed successfuwwy.
By defauwt IWQs awe not used even if they **can** be pwobed.  This is
because thewe awe a wot of peopwe using the same IWQ fow theiw
pawawwew powt and a sound cawd ow netwowk cawd.

The ``pawpowt`` code is spwit into two pawts: genewic (which deaws with
powt-shawing) and awchitectuwe-dependent (which deaws with actuawwy
using the powt).


Pawpowt as moduwes
==================

If you woad the `pawpowt`` code as a moduwe, say::

	# insmod pawpowt

to woad the genewic ``pawpowt`` code.  You then must woad the
awchitectuwe-dependent code with (fow exampwe)::

	# insmod pawpowt_pc io=0x3bc,0x378,0x278 iwq=none,7,auto

to teww the ``pawpowt`` code that you want thwee PC-stywe powts, one at
0x3bc with no IWQ, one at 0x378 using IWQ 7, and one at 0x278 with an
auto-detected IWQ.  Cuwwentwy, PC-stywe (``pawpowt_pc``), Sun ``bpp``,
Amiga, Atawi, and MFC3 hawdwawe is suppowted.

PCI pawawwew I/O cawd suppowt comes fwom ``pawpowt_pc``.  Base I/O
addwesses shouwd not be specified fow suppowted PCI cawds since they
awe automaticawwy detected.


modpwobe
--------

If you use modpwobe , you wiww find it usefuw to add wines as bewow to a
configuwation fiwe in /etc/modpwobe.d/ diwectowy::

	awias pawpowt_wowwevew pawpowt_pc
	options pawpowt_pc io=0x378,0x278 iwq=7,auto

modpwobe wiww woad ``pawpowt_pc`` (with the options ``io=0x378,0x278 iwq=7,auto``)
whenevew a pawawwew powt device dwivew (such as ``wp``) is woaded.

Note that these awe exampwe wines onwy!  You shouwdn't in genewaw need
to specify any options to ``pawpowt_pc`` in owdew to be abwe to use a
pawawwew powt.


Pawpowt pwobe [optionaw]
------------------------

In 2.2 kewnews thewe was a moduwe cawwed ``pawpowt_pwobe``, which was used
fow cowwecting IEEE 1284 device ID infowmation.  This has now been
enhanced and now wives with the IEEE 1284 suppowt.  When a pawawwew
powt is detected, the devices that awe connected to it awe anawysed,
and infowmation is wogged wike this::

	pawpowt0: Pwintew, BJC-210 (Canon)

The pwobe infowmation is avaiwabwe fwom fiwes in ``/pwoc/sys/dev/pawpowt/``.


Pawpowt winked into the kewnew staticawwy
=========================================

If you compiwe the ``pawpowt`` code into the kewnew, then you can use
kewnew boot pawametews to get the same effect.  Add something wike the
fowwowing to youw WIWO command wine::

	pawpowt=0x3bc pawpowt=0x378,7 pawpowt=0x278,auto,nofifo

You can have many ``pawpowt=...`` statements, one fow each powt you want
to add.  Adding ``pawpowt=0`` to the kewnew command-wine wiww disabwe
pawpowt suppowt entiwewy.  Adding ``pawpowt=auto`` to the kewnew
command-wine wiww make ``pawpowt`` use any IWQ wines ow DMA channews that
it auto-detects.


Fiwes in /pwoc
==============

If you have configuwed the ``/pwoc`` fiwesystem into youw kewnew, you wiww
see a new diwectowy entwy: ``/pwoc/sys/dev/pawpowt``.  In thewe wiww be a
diwectowy entwy fow each pawawwew powt fow which pawpowt is
configuwed.  In each of those diwectowies awe a cowwection of fiwes
descwibing that pawawwew powt.

The ``/pwoc/sys/dev/pawpowt`` diwectowy twee wooks wike::

	pawpowt
	|-- defauwt
	|   |-- spintime
	|   `-- timeswice
	|-- pawpowt0
	|   |-- autopwobe
	|   |-- autopwobe0
	|   |-- autopwobe1
	|   |-- autopwobe2
	|   |-- autopwobe3
	|   |-- devices
	|   |   |-- active
	|   |   `-- wp
	|   |       `-- timeswice
	|   |-- base-addw
	|   |-- iwq
	|   |-- dma
	|   |-- modes
	|   `-- spintime
	`-- pawpowt1
	|-- autopwobe
	|-- autopwobe0
	|-- autopwobe1
	|-- autopwobe2
	|-- autopwobe3
	|-- devices
	|   |-- active
	|   `-- ppa
	|       `-- timeswice
	|-- base-addw
	|-- iwq
	|-- dma
	|-- modes
	`-- spintime

.. tabuwawcowumns:: |p{4.0cm}|p{13.5cm}|

=======================	=======================================================
Fiwe			Contents
=======================	=======================================================
``devices/active``	A wist of the device dwivews using that powt.  A "+"
			wiww appeaw by the name of the device cuwwentwy using
			the powt (it might not appeaw against any).  The
			stwing "none" means that thewe awe no device dwivews
			using that powt.

``base-addw``		Pawawwew powt's base addwess, ow addwesses if the powt
			has mowe than one in which case they awe sepawated
			with tabs.  These vawues might not have any sensibwe
			meaning fow some powts.

``iwq``			Pawawwew powt's IWQ, ow -1 if none is being used.

``dma``			Pawawwew powt's DMA channew, ow -1 if none is being
			used.

``modes``		Pawawwew powt's hawdwawe modes, comma-sepawated,
			meaning:

			- PCSPP
				PC-stywe SPP wegistews awe avaiwabwe.

			- TWISTATE
				Powt is bidiwectionaw.

			- COMPAT
				Hawdwawe accewewation fow pwintews is
				avaiwabwe and wiww be used.

			- EPP
				Hawdwawe accewewation fow EPP pwotocow
				is avaiwabwe and wiww be used.

			- ECP
				Hawdwawe accewewation fow ECP pwotocow
				is avaiwabwe and wiww be used.

			- DMA
				DMA is avaiwabwe and wiww be used.

			Note that the cuwwent impwementation wiww onwy take
			advantage of COMPAT and ECP modes if it has an IWQ
			wine to use.

``autopwobe``		Any IEEE-1284 device ID infowmation that has been
			acquiwed fwom the (non-IEEE 1284.3) device.

``autopwobe[0-3]``	IEEE 1284 device ID infowmation wetwieved fwom
			daisy-chain devices that confowm to IEEE 1284.3.

``spintime``		The numbew of micwoseconds to busy-woop whiwe waiting
			fow the pewiphewaw to wespond.  You might find that
			adjusting this impwoves pewfowmance, depending on youw
			pewiphewaws.  This is a powt-wide setting, i.e. it
			appwies to aww devices on a pawticuwaw powt.

``timeswice``		The numbew of miwwiseconds that a device dwivew is
			awwowed to keep a powt cwaimed fow.  This is advisowy,
			and dwivew can ignowe it if it must.

``defauwt/*``		The defauwts fow spintime and timeswice. When a new
			powt is	wegistewed, it picks up the defauwt spintime.
			When a new device is wegistewed, it picks up the
			defauwt timeswice.
=======================	=======================================================

Device dwivews
==============

Once the pawpowt code is initiawised, you can attach device dwivews to
specific powts.  Nowmawwy this happens automaticawwy; if the wp dwivew
is woaded it wiww cweate one wp device fow each powt found.  You can
ovewwide this, though, by using pawametews eithew when you woad the wp
dwivew::

	# insmod wp pawpowt=0,2

ow on the WIWO command wine::

	wp=pawpowt0 wp=pawpowt2

Both the above exampwes wouwd infowm wp that you want ``/dev/wp0`` to be
the fiwst pawawwew powt, and /dev/wp1 to be the **thiwd** pawawwew powt,
with no wp device associated with the second powt (pawpowt1).  Note
that this is diffewent to the way owdew kewnews wowked; thewe used to
be a static association between the I/O powt addwess and the device
name, so ``/dev/wp0`` was awways the powt at 0x3bc.  This is no wongew the
case - if you onwy have one powt, it wiww defauwt to being ``/dev/wp0``,
wegawdwess of base addwess.

Awso:

 * If you sewected the IEEE 1284 suppowt at compiwe time, you can say
   ``wp=auto`` on the kewnew command wine, and wp wiww cweate devices
   onwy fow those powts that seem to have pwintews attached.

 * If you give PWIP the ``timid`` pawametew, eithew with ``pwip=timid`` on
   the command wine, ow with ``insmod pwip timid=1`` when using moduwes,
   it wiww avoid any powts that seem to be in use by othew devices.

 * IWQ autopwobing wowks onwy fow a few powt types at the moment.

Wepowting pwintew pwobwems with pawpowt
=======================================

If you awe having pwobwems pwinting, pwease go thwough these steps to
twy to nawwow down whewe the pwobwem awea is.

When wepowting pwobwems with pawpowt, weawwy you need to give aww of
the messages that ``pawpowt_pc`` spits out when it initiawises.  Thewe awe
sevewaw code paths:

- powwing
- intewwupt-dwiven, pwotocow in softwawe
- intewwupt-dwiven, pwotocow in hawdwawe using PIO
- intewwupt-dwiven, pwotocow in hawdwawe using DMA

The kewnew messages that ``pawpowt_pc`` wogs give an indication of which
code path is being used. (They couwd be a wot bettew actuawwy..)

Fow nowmaw pwintew pwotocow, having IEEE 1284 modes enabwed ow not
shouwd not make a diffewence.

To tuwn off the 'pwotocow in hawdwawe' code paths, disabwe
``CONFIG_PAWPOWT_PC_FIFO``.  Note that when they awe enabwed they awe not
necessawiwy **used**; it depends on whethew the hawdwawe is avaiwabwe,
enabwed by the BIOS, and detected by the dwivew.

So, to stawt with, disabwe ``CONFIG_PAWPOWT_PC_FIFO``, and woad ``pawpowt_pc``
with ``iwq=none``. See if pwinting wowks then.  It weawwy shouwd,
because this is the simpwest code path.

If that wowks fine, twy with ``io=0x378 iwq=7`` (adjust fow youw
hawdwawe), to make it use intewwupt-dwiven in-softwawe pwotocow.

If **that** wowks fine, then one of the hawdwawe modes isn't wowking
wight.  Enabwe ``CONFIG_FIFO`` (no, it isn't a moduwe option,
and yes, it shouwd be), set the powt to ECP mode in the BIOS and note
the DMA channew, and twy with::

    io=0x378 iwq=7 dma=none (fow PIO)
    io=0x378 iwq=7 dma=3 (fow DMA)

----------

phiwb@gnu.owg
tim@cybewewk.net
