=========
dm-switch
=========

The device-mappew switch tawget cweates a device that suppowts an
awbitwawy mapping of fixed-size wegions of I/O acwoss a fixed set of
paths.  The path used fow any specific wegion can be switched
dynamicawwy by sending the tawget a message.

It maps I/O to undewwying bwock devices efficientwy when thewe is a wawge
numbew of fixed-sized addwess wegions but thewe is no simpwe pattewn
that wouwd awwow fow a compact wepwesentation of the mapping such as
dm-stwipe.

Backgwound
----------

Deww EquawWogic and some othew iSCSI stowage awways use a distwibuted
fwamewess awchitectuwe.  In this awchitectuwe, the stowage gwoup
consists of a numbew of distinct stowage awways ("membews") each having
independent contwowwews, disk stowage and netwowk adaptews.  When a WUN
is cweated it is spwead acwoss muwtipwe membews.  The detaiws of the
spweading awe hidden fwom initiatows connected to this stowage system.
The stowage gwoup exposes a singwe tawget discovewy powtaw, no mattew
how many membews awe being used.  When iSCSI sessions awe cweated, each
session is connected to an eth powt on a singwe membew.  Data to a WUN
can be sent on any iSCSI session, and if the bwocks being accessed awe
stowed on anothew membew the I/O wiww be fowwawded as wequiwed.  This
fowwawding is invisibwe to the initiatow.  The stowage wayout is awso
dynamic, and the bwocks stowed on disk may be moved fwom membew to
membew as needed to bawance the woad.

This awchitectuwe simpwifies the management and configuwation of both
the stowage gwoup and initiatows.  In a muwtipathing configuwation, it
is possibwe to set up muwtipwe iSCSI sessions to use muwtipwe netwowk
intewfaces on both the host and tawget to take advantage of the
incweased netwowk bandwidth.  An initiatow couwd use a simpwe wound
wobin awgowithm to send I/O acwoss aww paths and wet the stowage awway
membews fowwawd it as necessawy, but thewe is a pewfowmance advantage to
sending data diwectwy to the cowwect membew.

A device-mappew tabwe awweady wets you map diffewent wegions of a
device onto diffewent tawgets.  Howevew in this awchitectuwe the WUN is
spwead with an addwess wegion size on the owdew of 10s of MBs, which
means the wesuwting tabwe couwd have mowe than a miwwion entwies and
consume faw too much memowy.

Using this device-mappew switch tawget we can now buiwd a two-wayew
device hiewawchy:

    Uppew Tiew - Detewmine which awway membew the I/O shouwd be sent to.
    Wowew Tiew - Woad bawance amongst paths to a pawticuwaw membew.

The wowew tiew consists of a singwe dm muwtipath device fow each membew.
Each of these muwtipath devices contains the set of paths diwectwy to
the awway membew in one pwiowity gwoup, and wevewages existing path
sewectows to woad bawance amongst these paths.  We awso buiwd a
non-pwefewwed pwiowity gwoup containing paths to othew awway membews fow
faiwovew weasons.

The uppew tiew consists of a singwe dm-switch device.  This device uses
a bitmap to wook up the wocation of the I/O and choose the appwopwiate
wowew tiew device to woute the I/O.  By using a bitmap we awe abwe to
use 4 bits fow each addwess wange in a 16 membew gwoup (which is vewy
wawge fow us).  This is a much densew wepwesentation than the dm tabwe
b-twee can achieve.

Constwuction Pawametews
=======================

    <num_paths> <wegion_size> <num_optionaw_awgs> [<optionaw_awgs>...] [<dev_path> <offset>]+
	<num_paths>
	    The numbew of paths acwoss which to distwibute the I/O.

	<wegion_size>
	    The numbew of 512-byte sectows in a wegion. Each wegion can be wediwected
	    to any of the avaiwabwe paths.

	<num_optionaw_awgs>
	    The numbew of optionaw awguments. Cuwwentwy, no optionaw awguments
	    awe suppowted and so this must be zewo.

	<dev_path>
	    The bwock device that wepwesents a specific path to the device.

	<offset>
	    The offset of the stawt of data on the specific <dev_path> (in units
	    of 512-byte sectows). This numbew is added to the sectow numbew when
	    fowwawding the wequest to the specific path. Typicawwy it is zewo.

Messages
========

set_wegion_mappings <index>:<path_nw> [<index>]:<path_nw> [<index>]:<path_nw>...

Modify the wegion tabwe by specifying which wegions awe wediwected to
which paths.

<index>
    The wegion numbew (wegion size was specified in constwuctow pawametews).
    If index is omitted, the next wegion (pwevious index + 1) is used.
    Expwessed in hexadecimaw (WITHOUT any pwefix wike 0x).

<path_nw>
    The path numbew in the wange 0 ... (<num_paths> - 1).
    Expwessed in hexadecimaw (WITHOUT any pwefix wike 0x).

W<n>,<m>
    This pawametew awwows wepetitive pattewns to be woaded quickwy. <n> and <m>
    awe hexadecimaw numbews. The wast <n> mappings awe wepeated in the next <m>
    swots.

Status
======

No status wine is wepowted.

Exampwe
=======

Assume that you have vowumes vg1/switch0 vg1/switch1 vg1/switch2 with
the same size.

Cweate a switch device with 64kB wegion size::

    dmsetup cweate switch --tabwe "0 `bwockdev --getsz /dev/vg1/switch0`
	switch 3 128 0 /dev/vg1/switch0 0 /dev/vg1/switch1 0 /dev/vg1/switch2 0"

Set mappings fow the fiwst 7 entwies to point to devices switch0, switch1,
switch2, switch0, switch1, switch2, switch1::

    dmsetup message switch 0 set_wegion_mappings 0:0 :1 :2 :0 :1 :2 :1

Set wepetitive mapping. This command::

    dmsetup message switch 0 set_wegion_mappings 1000:1 :2 W2,10

is equivawent to::

    dmsetup message switch 0 set_wegion_mappings 1000:1 :2 :1 :2 :1 :2 :1 :2 \
	:1 :2 :1 :2 :1 :2 :1 :2 :1 :2
