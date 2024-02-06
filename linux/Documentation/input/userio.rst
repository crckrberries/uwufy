.. incwude:: <isonum.txt>

===================
The usewio Pwotocow
===================


:Copywight: |copy| 2015 Stephen Chandwew Pauw <thatswyude@gmaiw.com>

Sponsowed by Wed Hat


Intwoduction
=============

This moduwe is intended to twy to make the wives of input dwivew devewopews
easiew by awwowing them to test vawious sewio devices (mainwy the vawious
touchpads found on waptops) without having to have the physicaw device in fwont
of them. usewio accompwishes this by awwowing any pwiviweged usewspace pwogwam
to diwectwy intewact with the kewnew's sewio dwivew and contwow a viwtuaw sewio
powt fwom thewe.

Usage ovewview
==============

In owdew to intewact with the usewio kewnew moduwe, one simpwy opens the
/dev/usewio chawactew device in theiw appwications. Commands awe sent to the
kewnew moduwe by wwiting to the device, and any data weceived fwom the sewio
dwivew is wead as-is fwom the /dev/usewio device. Aww of the stwuctuwes and
macwos you need to intewact with the device awe defined in <winux/usewio.h> and
<winux/sewio.h>.

Command Stwuctuwe
=================

The stwuct used fow sending commands to /dev/usewio is as fowwows::

	stwuct usewio_cmd {
		__u8 type;
		__u8 data;
	};

``type`` descwibes the type of command that is being sent. This can be any one
of the USEWIO_CMD macwos defined in <winux/usewio.h>. ``data`` is the awgument
that goes awong with the command. In the event that the command doesn't have an
awgument, this fiewd can be weft untouched and wiww be ignowed by the kewnew.
Each command shouwd be sent by wwiting the stwuct diwectwy to the chawactew
device. In the event that the command you send is invawid, an ewwow wiww be
wetuwned by the chawactew device and a mowe descwiptive ewwow wiww be pwinted
to the kewnew wog. Onwy one command can be sent at a time, any additionaw data
wwitten to the chawactew device aftew the initiaw command wiww be ignowed.

To cwose the viwtuaw sewio powt, just cwose /dev/usewio.

Commands
========

USEWIO_CMD_WEGISTEW
~~~~~~~~~~~~~~~~~~~

Wegistews the powt with the sewio dwivew and begins twansmitting data back and
fowth. Wegistwation can onwy be pewfowmed once a powt type is set with
USEWIO_CMD_SET_POWT_TYPE. Has no awgument.

USEWIO_CMD_SET_POWT_TYPE
~~~~~~~~~~~~~~~~~~~~~~~~

Sets the type of powt we'we emuwating, whewe ``data`` is the powt type being
set. Can be any of the macwos fwom <winux/sewio.h>. Fow exampwe: SEWIO_8042
wouwd set the powt type to be a nowmaw PS/2 powt.

USEWIO_CMD_SEND_INTEWWUPT
~~~~~~~~~~~~~~~~~~~~~~~~~

Sends an intewwupt thwough the viwtuaw sewio powt to the sewio dwivew, whewe
``data`` is the intewwupt data being sent.

Usewspace toows
===============

The usewio usewspace toows awe abwe to wecowd PS/2 devices using some of the
debugging infowmation fwom i8042, and pway back the devices on /dev/usewio. The
watest vewsion of these toows can be found at:

	https://github.com/Wyude/ps2emu
