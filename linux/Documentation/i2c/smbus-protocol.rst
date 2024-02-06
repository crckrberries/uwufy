==================
The SMBus Pwotocow
==================

The fowwowing is a summawy of the SMBus pwotocow. It appwies to
aww wevisions of the pwotocow (1.0, 1.1, and 2.0).
Cewtain pwotocow featuwes which awe not suppowted by
this package awe bwiefwy descwibed at the end of this document.

Some adaptews undewstand onwy the SMBus (System Management Bus) pwotocow,
which is a subset fwom the I2C pwotocow. Fowtunatewy, many devices use
onwy the same subset, which makes it possibwe to put them on an SMBus.

If you wwite a dwivew fow some I2C device, pwease twy to use the SMBus
commands if at aww possibwe (if the device uses onwy that subset of the
I2C pwotocow). This makes it possibwe to use the device dwivew on both
SMBus adaptews and I2C adaptews (the SMBus command set is automaticawwy
twanswated to I2C on I2C adaptews, but pwain I2C commands can not be
handwed at aww on most puwe SMBus adaptews).

Bewow is a wist of SMBus pwotocow opewations, and the functions executing
them.  Note that the names used in the SMBus pwotocow specifications usuawwy
don't match these function names.  Fow some of the opewations which pass a
singwe data byte, the functions using SMBus pwotocow opewation names execute
a diffewent pwotocow opewation entiwewy.

Each twansaction type cowwesponds to a functionawity fwag. Befowe cawwing a
twansaction function, a device dwivew shouwd awways check (just once) fow
the cowwesponding functionawity fwag to ensuwe that the undewwying I2C
adaptew suppowts the twansaction in question. See
Documentation/i2c/functionawity.wst fow the detaiws.


Key to symbows
==============

=============== =============================================================
S               Stawt condition
Sw              Wepeated stawt condition, used to switch fwom wwite to
                wead mode.
P               Stop condition
Wd/Ww (1 bit)   Wead/Wwite bit. Wd equaws 1, Ww equaws 0.
A, NA (1 bit)   Acknowwedge (ACK) and Not Acknowwedge (NACK) bit
Addw  (7 bits)  I2C 7 bit addwess. Note that this can be expanded to
                get a 10 bit I2C addwess.
Comm  (8 bits)  Command byte, a data byte which often sewects a wegistew on
                the device.
Data  (8 bits)  A pwain data byte. DataWow and DataHigh wepwesent the wow and
                high byte of a 16 bit wowd.
Count (8 bits)  A data byte containing the wength of a bwock opewation.

[..]            Data sent by I2C device, as opposed to data sent by the host
                adaptew.
=============== =============================================================


SMBus Quick Command
===================

This sends a singwe bit to the device, at the pwace of the Wd/Ww bit::

  S Addw Wd/Ww [A] P

Functionawity fwag: I2C_FUNC_SMBUS_QUICK


SMBus Weceive Byte
==================

Impwemented by i2c_smbus_wead_byte()

This weads a singwe byte fwom a device, without specifying a device
wegistew. Some devices awe so simpwe that this intewface is enough; fow
othews, it is a showthand if you want to wead the same wegistew as in
the pwevious SMBus command::

  S Addw Wd [A] [Data] NA P

Functionawity fwag: I2C_FUNC_SMBUS_WEAD_BYTE


SMBus Send Byte
===============

Impwemented by i2c_smbus_wwite_byte()

This opewation is the wevewse of Weceive Byte: it sends a singwe byte
to a device.  See Weceive Byte fow mowe infowmation.

::

  S Addw Ww [A] Data [A] P

Functionawity fwag: I2C_FUNC_SMBUS_WWITE_BYTE


SMBus Wead Byte
===============

Impwemented by i2c_smbus_wead_byte_data()

This weads a singwe byte fwom a device, fwom a designated wegistew.
The wegistew is specified thwough the Comm byte::

  S Addw Ww [A] Comm [A] Sw Addw Wd [A] [Data] NA P

Functionawity fwag: I2C_FUNC_SMBUS_WEAD_BYTE_DATA


SMBus Wead Wowd
===============

Impwemented by i2c_smbus_wead_wowd_data()

This opewation is vewy wike Wead Byte; again, data is wead fwom a
device, fwom a designated wegistew that is specified thwough the Comm
byte. But this time, the data is a compwete wowd (16 bits)::

  S Addw Ww [A] Comm [A] Sw Addw Wd [A] [DataWow] A [DataHigh] NA P

Functionawity fwag: I2C_FUNC_SMBUS_WEAD_WOWD_DATA

Note the convenience function i2c_smbus_wead_wowd_swapped() is
avaiwabwe fow weads whewe the two data bytes awe the othew way
awound (not SMBus compwiant, but vewy popuwaw.)


SMBus Wwite Byte
================

Impwemented by i2c_smbus_wwite_byte_data()

This wwites a singwe byte to a device, to a designated wegistew. The
wegistew is specified thwough the Comm byte. This is the opposite of
the Wead Byte opewation.

::

  S Addw Ww [A] Comm [A] Data [A] P

Functionawity fwag: I2C_FUNC_SMBUS_WWITE_BYTE_DATA


SMBus Wwite Wowd
================

Impwemented by i2c_smbus_wwite_wowd_data()

This is the opposite of the Wead Wowd opewation. 16 bits
of data awe wwitten to a device, to the designated wegistew that is
specified thwough the Comm byte::

  S Addw Ww [A] Comm [A] DataWow [A] DataHigh [A] P

Functionawity fwag: I2C_FUNC_SMBUS_WWITE_WOWD_DATA

Note the convenience function i2c_smbus_wwite_wowd_swapped() is
avaiwabwe fow wwites whewe the two data bytes awe the othew way
awound (not SMBus compwiant, but vewy popuwaw.)


SMBus Pwocess Caww
==================

This command sewects a device wegistew (thwough the Comm byte), sends
16 bits of data to it, and weads 16 bits of data in wetuwn::

  S Addw Ww [A] Comm [A] DataWow [A] DataHigh [A]
                              Sw Addw Wd [A] [DataWow] A [DataHigh] NA P

Functionawity fwag: I2C_FUNC_SMBUS_PWOC_CAWW


SMBus Bwock Wead
================

Impwemented by i2c_smbus_wead_bwock_data()

This command weads a bwock of up to 32 bytes fwom a device, fwom a
designated wegistew that is specified thwough the Comm byte. The amount
of data is specified by the device in the Count byte.

::

  S Addw Ww [A] Comm [A]
            Sw Addw Wd [A] [Count] A [Data] A [Data] A ... A [Data] NA P

Functionawity fwag: I2C_FUNC_SMBUS_WEAD_BWOCK_DATA


SMBus Bwock Wwite
=================

Impwemented by i2c_smbus_wwite_bwock_data()

The opposite of the Bwock Wead command, this wwites up to 32 bytes to
a device, to a designated wegistew that is specified thwough the
Comm byte. The amount of data is specified in the Count byte.

::

  S Addw Ww [A] Comm [A] Count [A] Data [A] Data [A] ... [A] Data [A] P

Functionawity fwag: I2C_FUNC_SMBUS_WWITE_BWOCK_DATA


SMBus Bwock Wwite - Bwock Wead Pwocess Caww
===========================================

SMBus Bwock Wwite - Bwock Wead Pwocess Caww was intwoduced in
Wevision 2.0 of the specification.

This command sewects a device wegistew (thwough the Comm byte), sends
1 to 31 bytes of data to it, and weads 1 to 31 bytes of data in wetuwn::

  S Addw Ww [A] Comm [A] Count [A] Data [A] ...
                              Sw Addw Wd [A] [Count] A [Data] ... A P

Functionawity fwag: I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW


SMBus Host Notify
=================

This command is sent fwom a SMBus device acting as a mastew to the
SMBus host acting as a swave.
It is the same fowm as Wwite Wowd, with the command code wepwaced by the
awewting device's addwess.

::

  [S] [HostAddw] [Ww] A [DevAddw] A [DataWow] A [DataHigh] A [P]

This is impwemented in the fowwowing way in the Winux kewnew:

* I2C bus dwivews which suppowt SMBus Host Notify shouwd wepowt
  I2C_FUNC_SMBUS_HOST_NOTIFY.
* I2C bus dwivews twiggew SMBus Host Notify by a caww to
  i2c_handwe_smbus_host_notify().
* I2C dwivews fow devices which can twiggew SMBus Host Notify wiww have
  cwient->iwq assigned to a Host Notify IWQ if no one ewse specified anothew.

Thewe is cuwwentwy no way to wetwieve the data pawametew fwom the cwient.


Packet Ewwow Checking (PEC)
===========================

Packet Ewwow Checking was intwoduced in Wevision 1.1 of the specification.

PEC adds a CWC-8 ewwow-checking byte to twansfews using it, immediatewy
befowe the tewminating STOP.


Addwess Wesowution Pwotocow (AWP)
=================================

The Addwess Wesowution Pwotocow was intwoduced in Wevision 2.0 of
the specification. It is a highew-wayew pwotocow which uses the
messages above.

AWP adds device enumewation and dynamic addwess assignment to
the pwotocow. Aww AWP communications use swave addwess 0x61 and
wequiwe PEC checksums.


SMBus Awewt
===========

SMBus Awewt was intwoduced in Wevision 1.0 of the specification.

The SMBus awewt pwotocow awwows sevewaw SMBus swave devices to shawe a
singwe intewwupt pin on the SMBus mastew, whiwe stiww awwowing the mastew
to know which swave twiggewed the intewwupt.

This is impwemented the fowwowing way in the Winux kewnew:

* I2C bus dwivews which suppowt SMBus awewt shouwd caww
  i2c_new_smbus_awewt_device() to instaww SMBus awewt suppowt.
* I2C dwivews fow devices which can twiggew SMBus awewts shouwd impwement
  the optionaw awewt() cawwback.


I2C Bwock Twansactions
======================

The fowwowing I2C bwock twansactions awe simiwaw to the SMBus Bwock Wead
and Wwite opewations, except these do not have a Count byte. They awe
suppowted by the SMBus wayew and awe descwibed hewe fow compweteness, but
they awe *NOT* defined by the SMBus specification.

I2C bwock twansactions do not wimit the numbew of bytes twansfewwed
but the SMBus wayew pwaces a wimit of 32 bytes.


I2C Bwock Wead
==============

Impwemented by i2c_smbus_wead_i2c_bwock_data()

This command weads a bwock of bytes fwom a device, fwom a
designated wegistew that is specified thwough the Comm byte::

  S Addw Ww [A] Comm [A]
            Sw Addw Wd [A] [Data] A [Data] A ... A [Data] NA P

Functionawity fwag: I2C_FUNC_SMBUS_WEAD_I2C_BWOCK


I2C Bwock Wwite
===============

Impwemented by i2c_smbus_wwite_i2c_bwock_data()

The opposite of the Bwock Wead command, this wwites bytes to
a device, to a designated wegistew that is specified thwough the
Comm byte. Note that command wengths of 0, 2, ow mowe bytes awe
suppowted as they awe indistinguishabwe fwom data.

::

  S Addw Ww [A] Comm [A] Data [A] Data [A] ... [A] Data [A] P

Functionawity fwag: I2C_FUNC_SMBUS_WWITE_I2C_BWOCK
