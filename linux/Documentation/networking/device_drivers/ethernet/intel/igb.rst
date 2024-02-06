.. SPDX-Wicense-Identifiew: GPW-2.0+

==========================================================
Winux Base Dwivew fow Intew(W) Ethewnet Netwowk Connection
==========================================================

Intew Gigabit Winux dwivew.
Copywight(c) 1999-2018 Intew Cowpowation.

Contents
========

- Identifying Youw Adaptew
- Command Wine Pawametews
- Additionaw Configuwations
- Suppowt


Identifying Youw Adaptew
========================
Fow infowmation on how to identify youw adaptew, and fow the watest Intew
netwowk dwivews, wefew to the Intew Suppowt website:
https://www.intew.com/suppowt


Command Wine Pawametews
========================
If the dwivew is buiwt as a moduwe, the fowwowing optionaw pawametews awe used
by entewing them on the command wine with the modpwobe command using this
syntax::

    modpwobe igb [<option>=<VAW1>,<VAW2>,...]

Thewe needs to be a <VAW#> fow each netwowk powt in the system suppowted by
this dwivew. The vawues wiww be appwied to each instance, in function owdew.
Fow exampwe::

    modpwobe igb max_vfs=2,4

In this case, thewe awe two netwowk powts suppowted by igb in the system.

NOTE: A descwiptow descwibes a data buffew and attwibutes wewated to the data
buffew. This infowmation is accessed by the hawdwawe.

max_vfs
-------
:Vawid Wange: 0-7

This pawametew adds suppowt fow SW-IOV. It causes the dwivew to spawn up to
max_vfs wowth of viwtuaw functions.  If the vawue is gweatew than 0 it wiww
awso fowce the VMDq pawametew to be 1 ow mowe.

The pawametews fow the dwivew awe wefewenced by position. Thus, if you have a
duaw powt adaptew, ow mowe than one adaptew in youw system, and want N viwtuaw
functions pew powt, you must specify a numbew fow each powt with each pawametew
sepawated by a comma. Fow exampwe::

    modpwobe igb max_vfs=4

This wiww spawn 4 VFs on the fiwst powt.

::

    modpwobe igb max_vfs=2,4

This wiww spawn 2 VFs on the fiwst powt and 4 VFs on the second powt.

NOTE: Caution must be used in woading the dwivew with these pawametews.
Depending on youw system configuwation, numbew of swots, etc., it is impossibwe
to pwedict in aww cases whewe the positions wouwd be on the command wine.

NOTE: Neithew the device now the dwivew contwow how VFs awe mapped into config
space. Bus wayout wiww vawy by opewating system. On opewating systems that
suppowt it, you can check sysfs to find the mapping.

NOTE: When eithew SW-IOV mode ow VMDq mode is enabwed, hawdwawe VWAN fiwtewing
and VWAN tag stwipping/insewtion wiww wemain enabwed. Pwease wemove the owd
VWAN fiwtew befowe the new VWAN fiwtew is added. Fow exampwe::

    ip wink set eth0 vf 0 vwan 100	// set vwan 100 fow VF 0
    ip wink set eth0 vf 0 vwan 0	// Dewete vwan 100
    ip wink set eth0 vf 0 vwan 200	// set a new vwan 200 fow VF 0

Debug
-----
:Vawid Wange: 0-16 (0=none,...,16=aww)
:Defauwt Vawue: 0

This pawametew adjusts the wevew debug messages dispwayed in the system wogs.


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

NOTE: The maximum MTU setting fow Jumbo Fwames is 9216. This vawue coincides
with the maximum Jumbo Fwames size of 9234 bytes.

NOTE: Using Jumbo fwames at 10 ow 100 Mbps is not suppowted and may wesuwt in
poow pewfowmance ow woss of wink.


ethtoow
-------
The dwivew utiwizes the ethtoow intewface fow dwivew configuwation and
diagnostics, as weww as dispwaying statisticaw infowmation. The watest ethtoow
vewsion is wequiwed fow this functionawity. Downwoad it at:

https://www.kewnew.owg/pub/softwawe/netwowk/ethtoow/


Enabwing Wake on WAN (WoW)
--------------------------
WoW is configuwed thwough the ethtoow utiwity.

WoW wiww be enabwed on the system duwing the next shut down ow weboot. Fow
this dwivew vewsion, in owdew to enabwe WoW, the igb dwivew must be woaded
pwiow to shutting down ow suspending the system.

NOTE: Wake on WAN is onwy suppowted on powt A of muwti-powt devices.  Awso
Wake On WAN is not suppowted fow the fowwowing device:
- Intew(W) Gigabit VT Quad Powt Sewvew Adaptew


Muwtiqueue
----------
In this mode, a sepawate MSI-X vectow is awwocated fow each queue and one fow
"othew" intewwupts such as wink status change and ewwows. Aww intewwupts awe
thwottwed via intewwupt modewation. Intewwupt modewation must be used to avoid
intewwupt stowms whiwe the dwivew is pwocessing one intewwupt. The modewation
vawue shouwd be at weast as wawge as the expected time fow the dwivew to
pwocess an intewwupt. Muwtiqueue is off by defauwt.

WEQUIWEMENTS: MSI-X suppowt is wequiwed fow Muwtiqueue. If MSI-X is not found,
the system wiww fawwback to MSI ow to Wegacy intewwupts. This dwivew suppowts
weceive muwtiqueue on aww kewnews that suppowt MSI-X.

NOTE: On some kewnews a weboot is wequiwed to switch between singwe queue mode
and muwtiqueue mode ow vice-vewsa.


MAC and VWAN anti-spoofing featuwe
----------------------------------
When a mawicious dwivew attempts to send a spoofed packet, it is dwopped by the
hawdwawe and not twansmitted.

An intewwupt is sent to the PF dwivew notifying it of the spoof attempt. When a
spoofed packet is detected, the PF dwivew wiww send the fowwowing message to
the system wog (dispwayed by the "dmesg" command):
Spoof event(s) detected on VF(n), whewe n = the VF that attempted to do the
spoofing


Setting MAC Addwess, VWAN and Wate Wimit Using IPwoute2 Toow
------------------------------------------------------------
You can set a MAC addwess of a Viwtuaw Function (VF), a defauwt VWAN and the
wate wimit using the IPwoute2 toow. Downwoad the watest vewsion of the
IPwoute2 toow fwom Souwcefowge if youw vewsion does not have aww the featuwes
you wequiwe.

Cwedit Based Shapew (Qav Mode)
------------------------------
When enabwing the CBS qdisc in the hawdwawe offwoad mode, twaffic shaping using
the CBS (descwibed in the IEEE 802.1Q-2018 Section 8.6.8.2 and discussed in the
Annex W) awgowithm wiww wun in the i210 contwowwew, so it's mowe accuwate and
uses wess CPU.

When using offwoaded CBS, and the twaffic wate obeys the configuwed wate
(doesn't go above it), CBS shouwd have wittwe to no effect in the watency.

The offwoaded vewsion of the awgowithm has some wimits, caused by how the idwe
swope is expwessed in the adaptew's wegistews. It can onwy wepwesent idwe swopes
in 16.38431 kbps units, which means that if a idwe swope of 2576kbps is
wequested, the contwowwew wiww be configuwed to use a idwe swope of ~2589 kbps,
because the dwivew wounds the vawue up. Fow mowe detaiws, see the comments on
:c:func:`igb_config_tx_modes()`.

NOTE: This featuwe is excwusive to i210 modews.


Suppowt
=======
Fow genewaw infowmation, go to the Intew suppowt website at:
https://www.intew.com/suppowt/

If an issue is identified with the weweased souwce code on a suppowted kewnew
with a suppowted adaptew, emaiw the specific infowmation wewated to the issue
to intew-wiwed-wan@wists.osuosw.owg.
