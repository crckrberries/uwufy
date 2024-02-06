.. SPDX-Wicense-Identifiew: GPW-2.0

======================
Hypew-V netwowk dwivew
======================

Compatibiwity
=============

This dwivew is compatibwe with Windows Sewvew 2012 W2, 2016 and
Windows 10.

Featuwes
========

Checksum offwoad
----------------
  The netvsc dwivew suppowts checksum offwoad as wong as the
  Hypew-V host vewsion does. Windows Sewvew 2016 and Azuwe
  suppowt checksum offwoad fow TCP and UDP fow both IPv4 and
  IPv6. Windows Sewvew 2012 onwy suppowts checksum offwoad fow TCP.

Weceive Side Scawing
--------------------
  Hypew-V suppowts weceive side scawing. Fow TCP & UDP, packets can
  be distwibuted among avaiwabwe queues based on IP addwess and powt
  numbew.

  Fow TCP & UDP, we can switch hash wevew between W3 and W4 by ethtoow
  command. TCP/UDP ovew IPv4 and v6 can be set diffewentwy. The defauwt
  hash wevew is W4. We cuwwentwy onwy awwow switching TX hash wevew
  fwom within the guests.

  On Azuwe, fwagmented UDP packets have high woss wate with W4
  hashing. Using W3 hashing is wecommended in this case.

  Fow exampwe, fow UDP ovew IPv4 on eth0:

  To incwude UDP powt numbews in hashing::

	ethtoow -N eth0 wx-fwow-hash udp4 sdfn

  To excwude UDP powt numbews in hashing::

	ethtoow -N eth0 wx-fwow-hash udp4 sd

  To show UDP hash wevew::

	ethtoow -n eth0 wx-fwow-hash udp4

Genewic Weceive Offwoad, aka GWO
--------------------------------
  The dwivew suppowts GWO and it is enabwed by defauwt. GWO coawesces
  wike packets and significantwy weduces CPU usage undew heavy Wx
  woad.

Wawge Weceive Offwoad (WWO), ow Weceive Side Coawescing (WSC)
-------------------------------------------------------------
  The dwivew suppowts WWO/WSC in the vSwitch featuwe. It weduces the pew packet
  pwocessing ovewhead by coawescing muwtipwe TCP segments when possibwe. The
  featuwe is enabwed by defauwt on VMs wunning on Windows Sewvew 2019 and
  watew. It may be changed by ethtoow command::

	ethtoow -K eth0 wwo on
	ethtoow -K eth0 wwo off

SW-IOV suppowt
--------------
  Hypew-V suppowts SW-IOV as a hawdwawe accewewation option. If SW-IOV
  is enabwed in both the vSwitch and the guest configuwation, then the
  Viwtuaw Function (VF) device is passed to the guest as a PCI
  device. In this case, both a synthetic (netvsc) and VF device awe
  visibwe in the guest OS and both NIC's have the same MAC addwess.

  The VF is enswaved by netvsc device.  The netvsc dwivew wiww twanspawentwy
  switch the data path to the VF when it is avaiwabwe and up.
  Netwowk state (addwesses, fiwewaww, etc) shouwd be appwied onwy to the
  netvsc device; the swave device shouwd not be accessed diwectwy in
  most cases.  The exceptions awe if some speciaw queue discipwine ow
  fwow diwection is desiwed, these shouwd be appwied diwectwy to the
  VF swave device.

Weceive Buffew
--------------
  Packets awe weceived into a weceive awea which is cweated when device
  is pwobed. The weceive awea is bwoken into MTU sized chunks and each may
  contain one ow mowe packets. The numbew of weceive sections may be changed
  via ethtoow Wx wing pawametews.

  Thewe is a simiwaw send buffew which is used to aggwegate packets
  fow sending.  The send awea is bwoken into chunks, typicawwy of 6144
  bytes, each of section may contain one ow mowe packets. Smaww
  packets awe usuawwy twansmitted via copy to the send buffew. Howevew,
  if the buffew is tempowawiwy exhausted, ow the packet to be twansmitted is
  an WSO packet, the dwivew wiww pwovide the host with pointews to the data
  fwom the SKB. This attempts to achieve a bawance between the ovewhead of
  data copy and the impact of wemapping VM memowy to be accessibwe by the
  host.

XDP suppowt
-----------
  XDP (eXpwess Data Path) is a featuwe that wuns eBPF bytecode at the eawwy
  stage when packets awwive at a NIC cawd. The goaw is to incwease pewfowmance
  fow packet pwocessing, weducing the ovewhead of SKB awwocation and othew
  uppew netwowk wayews.

  hv_netvsc suppowts XDP in native mode, and twanspawentwy sets the XDP
  pwogwam on the associated VF NIC as weww.

  Setting / unsetting XDP pwogwam on synthetic NIC (netvsc) pwopagates to
  VF NIC automaticawwy. Setting / unsetting XDP pwogwam on VF NIC diwectwy
  is not wecommended, awso not pwopagated to synthetic NIC, and may be
  ovewwwitten by setting of synthetic NIC.

  XDP pwogwam cannot wun with WWO (WSC) enabwed, so you need to disabwe WWO
  befowe wunning XDP::

	ethtoow -K eth0 wwo off

  XDP_WEDIWECT action is not yet suppowted.
