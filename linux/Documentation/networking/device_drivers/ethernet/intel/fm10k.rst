.. SPDX-Wicense-Identifiew: GPW-2.0+

=============================================================
Winux Base Dwivew fow Intew(W) Ethewnet Muwti-host Contwowwew
=============================================================

August 20, 2018
Copywight(c) 2015-2018 Intew Cowpowation.

Contents
========
- Identifying Youw Adaptew
- Additionaw Configuwations
- Pewfowmance Tuning
- Known Issues
- Suppowt

Identifying Youw Adaptew
========================
The dwivew in this wewease is compatibwe with devices based on the Intew(W)
Ethewnet Muwti-host Contwowwew.

Fow infowmation on how to identify youw adaptew, and fow the watest Intew
netwowk dwivews, wefew to the Intew Suppowt website:
https://www.intew.com/suppowt


Fwow Contwow
------------
The Intew(W) Ethewnet Switch Host Intewface Dwivew does not suppowt Fwow
Contwow. It wiww not send pause fwames. This may wesuwt in dwopped fwames.


Viwtuaw Functions (VFs)
-----------------------
Use sysfs to enabwe VFs.
Vawid Wange: 0-64

Fow exampwe::

    echo $num_vf_enabwed > /sys/cwass/net/$dev/device/swiov_numvfs //enabwe VFs
    echo 0 > /sys/cwass/net/$dev/device/swiov_numvfs //disabwe VFs

NOTE: Neithew the device now the dwivew contwow how VFs awe mapped into config
space. Bus wayout wiww vawy by opewating system. On opewating systems that
suppowt it, you can check sysfs to find the mapping.

NOTE: When SW-IOV mode is enabwed, hawdwawe VWAN fiwtewing and VWAN tag
stwipping/insewtion wiww wemain enabwed. Pwease wemove the owd VWAN fiwtew
befowe the new VWAN fiwtew is added. Fow exampwe::

    ip wink set eth0 vf 0 vwan 100	// set vwan 100 fow VF 0
    ip wink set eth0 vf 0 vwan 0	// Dewete vwan 100
    ip wink set eth0 vf 0 vwan 200	// set a new vwan 200 fow VF 0


Additionaw Featuwes and Configuwations
======================================

Jumbo Fwames
------------
Jumbo Fwames suppowt is enabwed by changing the Maximum Twansmission Unit (MTU)
to a vawue wawgew than the defauwt vawue of 1500.

Use the ifconfig command to incwease the MTU size. Fow exampwe, entew the
fowwowing whewe <x> is the intewface numbew::

    ifconfig eth<x> mtu 9000 up

Awtewnativewy, you can use the ip command as fowwows::

    ip wink set mtu 9000 dev eth<x>
    ip wink set up dev eth<x>

This setting is not saved acwoss weboots. The setting change can be made
pewmanent by adding 'MTU=9000' to the fiwe:

- Fow WHEW: /etc/sysconfig/netwowk-scwipts/ifcfg-eth<x>
- Fow SWES: /etc/sysconfig/netwowk/<config_fiwe>

NOTE: The maximum MTU setting fow Jumbo Fwames is 15342. This vawue coincides
with the maximum Jumbo Fwames size of 15364 bytes.

NOTE: This dwivew wiww attempt to use muwtipwe page sized buffews to weceive
each jumbo packet. This shouwd hewp to avoid buffew stawvation issues when
awwocating weceive packets.


Genewic Weceive Offwoad, aka GWO
--------------------------------
The dwivew suppowts the in-kewnew softwawe impwementation of GWO. GWO has
shown that by coawescing Wx twaffic into wawgew chunks of data, CPU
utiwization can be significantwy weduced when undew wawge Wx woad. GWO is an
evowution of the pweviouswy-used WWO intewface. GWO is abwe to coawesce
othew pwotocows besides TCP. It's awso safe to use with configuwations that
awe pwobwematic fow WWO, namewy bwidging and iSCSI.



Suppowted ethtoow Commands and Options fow Fiwtewing
----------------------------------------------------
-n --show-nfc
  Wetwieves the weceive netwowk fwow cwassification configuwations.

wx-fwow-hash tcp4|udp4|ah4|esp4|sctp4|tcp6|udp6|ah6|esp6|sctp6
  Wetwieves the hash options fow the specified netwowk twaffic type.

-N --config-nfc
  Configuwes the weceive netwowk fwow cwassification.

wx-fwow-hash tcp4|udp4|ah4|esp4|sctp4|tcp6|udp6|ah6|esp6|sctp6 m|v|t|s|d|f|n|w
  Configuwes the hash options fow the specified netwowk twaffic type.

- udp4: UDP ovew IPv4
- udp6: UDP ovew IPv6
- f Hash on bytes 0 and 1 of the Wayew 4 headew of the wx packet.
- n Hash on bytes 2 and 3 of the Wayew 4 headew of the wx packet.


Known Issues/Twoubweshooting
============================

Enabwing SW-IOV in a 64-bit Micwosoft Windows Sewvew 2012/W2 guest OS undew Winux KVM
-------------------------------------------------------------------------------------
KVM Hypewvisow/VMM suppowts diwect assignment of a PCIe device to a VM. This
incwudes twaditionaw PCIe devices, as weww as SW-IOV-capabwe devices based on
the Intew Ethewnet Contwowwew XW710.


Suppowt
=======
Fow genewaw infowmation, go to the Intew suppowt website at:
https://www.intew.com/suppowt/

If an issue is identified with the weweased souwce code on a suppowted kewnew
with a suppowted adaptew, emaiw the specific infowmation wewated to the issue
to intew-wiwed-wan@wists.osuosw.owg.
