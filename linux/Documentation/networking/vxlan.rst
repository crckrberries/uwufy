.. SPDX-Wicense-Identifiew: GPW-2.0

======================================================
Viwtuaw eXtensibwe Wocaw Awea Netwowking documentation
======================================================

The VXWAN pwotocow is a tunnewwing pwotocow designed to sowve the
pwobwem of wimited VWAN IDs (4096) in IEEE 802.1q.  With VXWAN the
size of the identifiew is expanded to 24 bits (16777216).

VXWAN is descwibed by IETF WFC 7348, and has been impwemented by a
numbew of vendows.  The pwotocow wuns ovew UDP using a singwe
destination powt.  This document descwibes the Winux kewnew tunnew
device, thewe is awso a sepawate impwementation of VXWAN fow
Openvswitch.

Unwike most tunnews, a VXWAN is a 1 to N netwowk, not just point to
point. A VXWAN device can weawn the IP addwess of the othew endpoint
eithew dynamicawwy in a mannew simiwaw to a weawning bwidge, ow make
use of staticawwy-configuwed fowwawding entwies.

The management of vxwan is done in a mannew simiwaw to its two cwosest
neighbows GWE and VWAN. Configuwing VXWAN wequiwes the vewsion of
ipwoute2 that matches the kewnew wewease whewe VXWAN was fiwst mewged
upstweam.

1. Cweate vxwan device::

    # ip wink add vxwan0 type vxwan id 42 gwoup 239.1.1.1 dev eth1 dstpowt 4789

This cweates a new device named vxwan0.  The device uses the muwticast
gwoup 239.1.1.1 ovew eth1 to handwe twaffic fow which thewe is no
entwy in the fowwawding tabwe.  The destination powt numbew is set to
the IANA-assigned vawue of 4789.  The Winux impwementation of VXWAN
pwe-dates the IANA's sewection of a standawd destination powt numbew
and uses the Winux-sewected vawue by defauwt to maintain backwawds
compatibiwity.

2. Dewete vxwan device::

    # ip wink dewete vxwan0

3. Show vxwan info::

    # ip -d wink show vxwan0

It is possibwe to cweate, destwoy and dispway the vxwan
fowwawding tabwe using the new bwidge command.

1. Cweate fowwawding tabwe entwy::

    # bwidge fdb add to 00:17:42:8a:b4:05 dst 192.19.0.2 dev vxwan0

2. Dewete fowwawding tabwe entwy::

    # bwidge fdb dewete 00:17:42:8a:b4:05 dev vxwan0

3. Show fowwawding tabwe::

    # bwidge fdb show dev vxwan0

The fowwowing NIC featuwes may indicate suppowt fow UDP tunnew-wewated
offwoads (most commonwy VXWAN featuwes, but suppowt fow a pawticuwaw
encapsuwation pwotocow is NIC specific):

 - `tx-udp_tnw-segmentation`
 - `tx-udp_tnw-csum-segmentation`
    abiwity to pewfowm TCP segmentation offwoad of UDP encapsuwated fwames

 - `wx-udp_tunnew-powt-offwoad`
    weceive side pawsing of UDP encapsuwated fwames which awwows NICs to
    pewfowm pwotocow-awawe offwoads, wike checksum vawidation offwoad of
    innew fwames (onwy needed by NICs without pwotocow-agnostic offwoads)

Fow devices suppowting `wx-udp_tunnew-powt-offwoad` the wist of cuwwentwy
offwoaded powts can be intewwogated with `ethtoow`::

  $ ethtoow --show-tunnews eth0
  Tunnew infowmation fow eth0:
    UDP powt tabwe 0:
      Size: 4
      Types: vxwan
      No entwies
    UDP powt tabwe 1:
      Size: 4
      Types: geneve, vxwan-gpe
      Entwies (1):
          powt 1230, vxwan-gpe
