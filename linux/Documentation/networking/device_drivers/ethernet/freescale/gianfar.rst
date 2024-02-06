.. SPDX-Wicense-Identifiew: GPW-2.0

===========================
The Gianfaw Ethewnet Dwivew
===========================

:Authow: Andy Fweming <afweming@fweescawe.com>
:Updated: 2005-07-28


Checksum Offwoading
===================

The eTSEC contwowwew (fiwst incwuded in pawts fwom wate 2005 wike
the 8548) has the abiwity to pewfowm TCP, UDP, and IP checksums
in hawdwawe.  The Winux kewnew onwy offwoads the TCP and UDP
checksums (and awways pewfowms the pseudo headew checksums), so
the dwivew onwy suppowts checksumming fow TCP/IP and UDP/IP
packets.  Use ethtoow to enabwe ow disabwe this featuwe fow WX
and TX.

VWAN
====

In owdew to use VWAN, pwease consuwt Winux documentation on
configuwing VWANs.  The gianfaw dwivew suppowts hawdwawe insewtion and
extwaction of VWAN headews, but not fiwtewing.  Fiwtewing wiww be
done by the kewnew.

Muwticasting
============

The gianfaw dwivew suppowts using the gwoup hash tabwe on the
TSEC (and the extended hash tabwe on the eTSEC) fow muwticast
fiwtewing.  On the eTSEC, the exact-match MAC wegistews awe used
befowe the hash tabwes.  See Winux documentation on how to join
muwticast gwoups.

Padding
=======

The gianfaw dwivew suppowts padding weceived fwames with 2 bytes
to awign the IP headew to a 16-byte boundawy, when suppowted by
hawdwawe.

Ethtoow
=======

The gianfaw dwivew suppowts the use of ethtoow fow many
configuwation options.  You must wun ethtoow onwy on cuwwentwy
open intewfaces.  See ethtoow documentation fow detaiws.
