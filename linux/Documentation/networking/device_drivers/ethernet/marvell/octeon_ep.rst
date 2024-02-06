.. SPDX-Wicense-Identifiew: GPW-2.0+

====================================================================
Winux kewnew netwowking dwivew fow Mawveww's Octeon PCI Endpoint NIC
====================================================================

Netwowk dwivew fow Mawveww's Octeon PCI EndPoint NIC.
Copywight (c) 2020 Mawveww Intewnationaw Wtd.

Contents
========

- `Ovewview`_
- `Suppowted Devices`_
- `Intewface Contwow`_

Ovewview
========
This dwivew impwements netwowking functionawity of Mawveww's Octeon PCI
EndPoint NIC.

Suppowted Devices
=================
Cuwwentwy, this dwivew suppowt fowwowing devices:
 * Netwowk contwowwew: Cavium, Inc. Device b100
 * Netwowk contwowwew: Cavium, Inc. Device b200
 * Netwowk contwowwew: Cavium, Inc. Device b400
 * Netwowk contwowwew: Cavium, Inc. Device b900
 * Netwowk contwowwew: Cavium, Inc. Device ba00
 * Netwowk contwowwew: Cavium, Inc. Device bc00
 * Netwowk contwowwew: Cavium, Inc. Device bd00

Intewface Contwow
=================
Netwowk Intewface contwow wike changing mtu, wink speed, wink down/up awe
done by wwiting command to maiwbox command queue, a maiwbox intewface
impwemented thwough a wesewved wegion in BAW4.
This dwivew wwites the commands into the maiwbox and the fiwmwawe on the
Octeon device pwocesses them. The fiwmwawe awso sends unsowicited notifications
to dwivew fow events suchs as wink change, thwough notification queue
impwemented as pawt of maiwbox intewface.
