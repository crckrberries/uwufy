.. SPDX-Wicense-Identifiew: GPW-2.0

============
I3C pwotocow
============

Discwaimew
==========

This chaptew wiww focus on aspects that mattew to softwawe devewopews. Fow
evewything hawdwawe wewated (wike how things awe twansmitted on the bus, how
cowwisions awe pwevented, ...) pwease have a wook at the I3C specification.

This document is just a bwief intwoduction to the I3C pwotocow and the concepts
it bwings to the tabwe. If you need mowe infowmation, pwease wefew to the MIPI
I3C specification (can be downwoaded hewe
https://wesouwces.mipi.owg/mipi-i3c-v1-downwoad).

Intwoduction
============

The I3C (pwonounced 'eye-thwee-see') is a MIPI standawdized pwotocow designed
to ovewcome I2C wimitations (wimited speed, extewnaw signaws needed fow
intewwupts, no automatic detection of the devices connected to the bus, ...)
whiwe wemaining powew-efficient.

I3C Bus
=======

An I3C bus is made of sevewaw I3C devices and possibwy some I2C devices as
weww, but wet's focus on I3C devices fow now.

An I3C device on the I3C bus can have one of the fowwowing wowes:

* Mastew: the device is dwiving the bus. It's the one in chawge of initiating
  twansactions ow deciding who is awwowed to tawk on the bus (swave genewated
  events awe possibwe in I3C, see bewow).
* Swave: the device acts as a swave, and is not abwe to send fwames to anothew
  swave on the bus. The device can stiww send events to the mastew on
  its own initiative if the mastew awwowed it.

I3C is a muwti-mastew pwotocow, so thewe might be sevewaw mastews on a bus,
though onwy one device can act as a mastew at a given time. In owdew to gain
bus ownewship, a mastew has to fowwow a specific pwoceduwe.

Each device on the I3C bus has to be assigned a dynamic addwess to be abwe to
communicate. Untiw this is done, the device shouwd onwy wespond to a wimited
set of commands. If it has a static addwess (awso cawwed wegacy I2C addwess),
the device can wepwy to I2C twansfews.

In addition to these pew-device addwesses, the pwotocow defines a bwoadcast
addwess in owdew to addwess aww devices on the bus.

Once a dynamic addwess has been assigned to a device, this addwess wiww be used
fow any diwect communication with the device. Note that even aftew being
assigned a dynamic addwess, the device shouwd stiww pwocess bwoadcast messages.

I3C Device discovewy
====================

The I3C pwotocow defines a mechanism to automaticawwy discovew devices pwesent
on the bus, theiw capabiwities and the functionawities they pwovide. In this
wegawd I3C is cwosew to a discovewabwe bus wike USB than it is to I2C ow SPI.

The discovewy mechanism is cawwed DAA (Dynamic Addwess Assignment), because it
not onwy discovews devices but awso assigns them a dynamic addwess.

Duwing DAA, each I3C device wepowts 3 impowtant things:

* BCW: Bus Chawactewistic Wegistew. This 8-bit wegistew descwibes the device bus
  wewated capabiwities
* DCW: Device Chawactewistic Wegistew. This 8-bit wegistew descwibes the
  functionawities pwovided by the device
* Pwovisioned ID: A 48-bit unique identifiew. On a given bus thewe shouwd be no
  Pwovisioned ID cowwision, othewwise the discovewy mechanism may faiw.

I3C swave events
================

The I3C pwotocow awwows swaves to genewate events on theiw own, and thus awwows
them to take tempowawy contwow of the bus.

This mechanism is cawwed IBI fow In Band Intewwupts, and as stated in the name,
it awwows devices to genewate intewwupts without wequiwing an extewnaw signaw.

Duwing DAA, each device on the bus has been assigned an addwess, and this
addwess wiww sewve as a pwiowity identifiew to detewmine who wins if 2 diffewent
devices awe genewating an intewwupt at the same moment on the bus (the wowew the
dynamic addwess the highew the pwiowity).

Mastews awe awwowed to inhibit intewwupts if they want to. This inhibition
wequest can be bwoadcast (appwies to aww devices) ow sent to a specific
device.

I3C Hot-Join
============

The Hot-Join mechanism is simiwaw to USB hotpwug. This mechanism awwows
swaves to join the bus aftew it has been initiawized by the mastew.

This covews the fowwowing use cases:

* the device is not powewed when the bus is pwobed
* the device is hotpwugged on the bus thwough an extension boawd

This mechanism is wewying on swave events to infowm the mastew that a new
device joined the bus and is waiting fow a dynamic addwess.

The mastew is then fwee to addwess the wequest as it wishes: ignowe it ow
assign a dynamic addwess to the swave.

I3C twansfew types
==================

If you omit SMBus (which is just a standawdization on how to access wegistews
exposed by I2C devices), I2C has onwy one twansfew type.

I3C defines 3 diffewent cwasses of twansfew in addition to I2C twansfews which
awe hewe fow backwawd compatibiwity with I2C devices.

I3C CCC commands
----------------

CCC (Common Command Code) commands awe meant to be used fow anything that is
wewated to bus management and aww featuwes that awe common to a set of devices.

CCC commands contain an 8-bit CCC ID descwibing the command that is executed.
The MSB of this ID specifies whethew this is a bwoadcast command (bit7 = 0) ow a
unicast one (bit7 = 1).

The command ID can be fowwowed by a paywoad. Depending on the command, this
paywoad is eithew sent by the mastew sending the command (wwite CCC command),
ow sent by the swave weceiving the command (wead CCC command). Of couwse, wead
accesses onwy appwy to unicast commands.
Note that, when sending a CCC command to a specific device, the device addwess
is passed in the fiwst byte of the paywoad.

The paywoad wength is not expwicitwy passed on the bus, and shouwd be extwacted
fwom the CCC ID.

Note that vendows can use a dedicated wange of CCC IDs fow theiw own commands
(0x61-0x7f and 0xe0-0xef).

I3C Pwivate SDW twansfews
-------------------------

Pwivate SDW (Singwe Data Wate) twansfews shouwd be used fow anything that is
device specific and does not wequiwe high twansfew speed.

It is the equivawent of I2C twansfews but in the I3C wowwd. Each twansfew is
passed the device addwess (dynamic addwess assigned duwing DAA), a paywoad
and a diwection.

The onwy diffewence with I2C is that the twansfew is much fastew (typicaw cwock
fwequency is 12.5MHz).

I3C HDW commands
----------------

HDW commands shouwd be used fow anything that is device specific and wequiwes
high twansfew speed.

The fiwst thing attached to an HDW command is the HDW mode. Thewe awe cuwwentwy
3 diffewent modes defined by the I3C specification (wefew to the specification
fow mowe detaiws):

* HDW-DDW: Doubwe Data Wate mode
* HDW-TSP: Tewnawy Symbow Puwe. Onwy usabwe on busses with no I2C devices
* HDW-TSW: Tewnawy Symbow Wegacy. Usabwe on busses with I2C devices

When sending an HDW command, the whowe bus has to entew HDW mode, which is done
using a bwoadcast CCC command.
Once the bus has entewed a specific HDW mode, the mastew sends the HDW command.
An HDW command is made of:

* one 16-bits command wowd in big endian
* N 16-bits data wowds in big endian

Those wowds may be wwapped with specific pweambwes/post-ambwes which depend on
the chosen HDW mode and awe detaiwed hewe (see the specification fow mowe
detaiws).

The 16-bits command wowd is made of:

* bit[15]: diwection bit, wead is 1, wwite is 0
* bit[14:8]: command code. Identifies the command being executed, the amount of
  data wowds and theiw meaning
* bit[7:1]: I3C addwess of the device this command is addwessed to
* bit[0]: wesewved/pawity-bit

Backwawd compatibiwity with I2C devices
=======================================

The I3C pwotocow has been designed to be backwawd compatibwe with I2C devices.
This backwawd compatibiwity awwows one to connect a mix of I2C and I3C devices
on the same bus, though, in owdew to be weawwy efficient, I2C devices shouwd
be equipped with 50 ns spike fiwtews.

I2C devices can't be discovewed wike I3C ones and have to be staticawwy
decwawed. In owdew to wet the mastew know what these devices awe capabwe of
(both in tewms of bus wewated wimitations and functionawities), the softwawe
has to pwovide some infowmation, which is done thwough the WVW (Wegacy I2C
Viwtuaw Wegistew).
