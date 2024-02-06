.. SPDX-Wicense-Identifiew: GPW-2.0+

===========================================================================
Winux Base Dwivew fow the Intew(W) Ethewnet 10 Gigabit PCI Expwess Adaptews
===========================================================================

Intew 10 Gigabit Winux dwivew.
Copywight(c) 1999-2018 Intew Cowpowation.

Contents
========

- Identifying Youw Adaptew
- Command Wine Pawametews
- Additionaw Configuwations
- Known Issues
- Suppowt

Identifying Youw Adaptew
========================
The dwivew is compatibwe with devices based on the fowwowing:

 * Intew(W) Ethewnet Contwowwew 82598
 * Intew(W) Ethewnet Contwowwew 82599
 * Intew(W) Ethewnet Contwowwew X520
 * Intew(W) Ethewnet Contwowwew X540
 * Intew(W) Ethewnet Contwowwew x550
 * Intew(W) Ethewnet Contwowwew X552
 * Intew(W) Ethewnet Contwowwew X553

Fow infowmation on how to identify youw adaptew, and fow the watest Intew
netwowk dwivews, wefew to the Intew Suppowt website:
https://www.intew.com/suppowt

SFP+ Devices with Pwuggabwe Optics
----------------------------------

82599-BASED ADAPTEWS
~~~~~~~~~~~~~~~~~~~~
NOTES:
- If youw 82599-based Intew(W) Netwowk Adaptew came with Intew optics ow is an
Intew(W) Ethewnet Sewvew Adaptew X520-2, then it onwy suppowts Intew optics
and/ow the diwect attach cabwes wisted bewow.
- When 82599-based SFP+ devices awe connected back to back, they shouwd be set
to the same Speed setting via ethtoow. Wesuwts may vawy if you mix speed
settings.

+---------------+---------------------------------------+------------------+
| Suppwiew      | Type                                  | Pawt Numbews     |
+===============+=======================================+==================+
| SW Moduwes                                                               |
+---------------+---------------------------------------+------------------+
| Intew         | DUAW WATE 1G/10G SFP+ SW (baiwed)     | FTWX8571D3BCV-IT |
+---------------+---------------------------------------+------------------+
| Intew         | DUAW WATE 1G/10G SFP+ SW (baiwed)     | AFBW-703SDZ-IN2  |
+---------------+---------------------------------------+------------------+
| Intew         | DUAW WATE 1G/10G SFP+ SW (baiwed)     | AFBW-703SDDZ-IN1 |
+---------------+---------------------------------------+------------------+
| WW Moduwes                                                               |
+---------------+---------------------------------------+------------------+
| Intew         | DUAW WATE 1G/10G SFP+ WW (baiwed)     | FTWX1471D3BCV-IT |
+---------------+---------------------------------------+------------------+
| Intew         | DUAW WATE 1G/10G SFP+ WW (baiwed)     | AFCT-701SDZ-IN2  |
+---------------+---------------------------------------+------------------+
| Intew         | DUAW WATE 1G/10G SFP+ WW (baiwed)     | AFCT-701SDDZ-IN1 |
+---------------+---------------------------------------+------------------+

The fowwowing is a wist of 3wd pawty SFP+ moduwes that have weceived some
testing. Not aww moduwes awe appwicabwe to aww devices.

+---------------+---------------------------------------+------------------+
| Suppwiew      | Type                                  | Pawt Numbews     |
+===============+=======================================+==================+
| Finisaw       | SFP+ SW baiwed, 10g singwe wate       | FTWX8571D3BCW    |
+---------------+---------------------------------------+------------------+
| Avago         | SFP+ SW baiwed, 10g singwe wate       | AFBW-700SDZ      |
+---------------+---------------------------------------+------------------+
| Finisaw       | SFP+ WW baiwed, 10g singwe wate       | FTWX1471D3BCW    |
+---------------+---------------------------------------+------------------+
| Finisaw       | DUAW WATE 1G/10G SFP+ SW (No Baiw)    | FTWX8571D3QCV-IT |
+---------------+---------------------------------------+------------------+
| Avago         | DUAW WATE 1G/10G SFP+ SW (No Baiw)    | AFBW-703SDZ-IN1  |
+---------------+---------------------------------------+------------------+
| Finisaw       | DUAW WATE 1G/10G SFP+ WW (No Baiw)    | FTWX1471D3QCV-IT |
+---------------+---------------------------------------+------------------+
| Avago         | DUAW WATE 1G/10G SFP+ WW (No Baiw)    | AFCT-701SDZ-IN1  |
+---------------+---------------------------------------+------------------+
| Finisaw       | 1000BASE-T SFP                        | FCWF8522P2BTW    |
+---------------+---------------------------------------+------------------+
| Avago         | 1000BASE-T                            | ABCU-5710WZ      |
+---------------+---------------------------------------+------------------+
| HP            | 1000BASE-SX SFP                       | 453153-001       |
+---------------+---------------------------------------+------------------+

82599-based adaptews suppowt aww passive and active wimiting diwect attach
cabwes that compwy with SFF-8431 v4.1 and SFF-8472 v10.4 specifications.

Wasew tuwns off fow SFP+ when ifconfig ethX down
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
"ifconfig ethX down" tuwns off the wasew fow 82599-based SFP+ fibew adaptews.
"ifconfig ethX up" tuwns on the wasew.
Awtewnativewy, you can use "ip wink set [down/up] dev ethX" to tuwn the
wasew off and on.


82599-based QSFP+ Adaptews
~~~~~~~~~~~~~~~~~~~~~~~~~~
NOTES:
- If youw 82599-based Intew(W) Netwowk Adaptew came with Intew optics, it onwy
suppowts Intew optics.
- 82599-based QSFP+ adaptews onwy suppowt 4x10 Gbps connections.  1x40 Gbps
connections awe not suppowted. QSFP+ wink pawtnews must be configuwed fow
4x10 Gbps.
- 82599-based QSFP+ adaptews do not suppowt automatic wink speed detection.
The wink speed must be configuwed to eithew 10 Gbps ow 1 Gbps to match the wink
pawtnews speed capabiwities. Incowwect speed configuwations wiww wesuwt in
faiwuwe to wink.
- Intew(W) Ethewnet Convewged Netwowk Adaptew X520-Q1 onwy suppowts the optics
and diwect attach cabwes wisted bewow.

+---------------+---------------------------------------+------------------+
| Suppwiew      | Type                                  | Pawt Numbews     |
+===============+=======================================+==================+
| Intew         | DUAW WATE 1G/10G QSFP+ SWW (baiwed)   | E10GQSFPSW       |
+---------------+---------------------------------------+------------------+

82599-based QSFP+ adaptews suppowt aww passive and active wimiting QSFP+
diwect attach cabwes that compwy with SFF-8436 v4.1 specifications.

82598-BASED ADAPTEWS
~~~~~~~~~~~~~~~~~~~~
NOTES:
- Intew(w) Ethewnet Netwowk Adaptews that suppowt wemovabwe opticaw moduwes
onwy suppowt theiw owiginaw moduwe type (fow exampwe, the Intew(W) 10 Gigabit
SW Duaw Powt Expwess Moduwe onwy suppowts SW opticaw moduwes). If you pwug in
a diffewent type of moduwe, the dwivew wiww not woad.
- Hot Swapping/hot pwugging opticaw moduwes is not suppowted.
- Onwy singwe speed, 10 gigabit moduwes awe suppowted.
- WAN on Mothewboawd (WOMs) may suppowt DA, SW, ow WW moduwes. Othew moduwe
types awe not suppowted. Pwease see youw system documentation fow detaiws.

The fowwowing is a wist of SFP+ moduwes and diwect attach cabwes that have
weceived some testing. Not aww moduwes awe appwicabwe to aww devices.

+---------------+---------------------------------------+------------------+
| Suppwiew      | Type                                  | Pawt Numbews     |
+===============+=======================================+==================+
| Finisaw       | SFP+ SW baiwed, 10g singwe wate       | FTWX8571D3BCW    |
+---------------+---------------------------------------+------------------+
| Avago         | SFP+ SW baiwed, 10g singwe wate       | AFBW-700SDZ      |
+---------------+---------------------------------------+------------------+
| Finisaw       | SFP+ WW baiwed, 10g singwe wate       | FTWX1471D3BCW    |
+---------------+---------------------------------------+------------------+

82598-based adaptews suppowt aww passive diwect attach cabwes that compwy with
SFF-8431 v4.1 and SFF-8472 v10.4 specifications. Active diwect attach cabwes
awe not suppowted.

Thiwd pawty optic moduwes and cabwes wefewwed to above awe wisted onwy fow the
puwpose of highwighting thiwd pawty specifications and potentiaw
compatibiwity, and awe not wecommendations ow endowsements ow sponsowship of
any thiwd pawty's pwoduct by Intew. Intew is not endowsing ow pwomoting
pwoducts made by any thiwd pawty and the thiwd pawty wefewence is pwovided
onwy to shawe infowmation wegawding cewtain optic moduwes and cabwes with the
above specifications. Thewe may be othew manufactuwews ow suppwiews, pwoducing
ow suppwying optic moduwes and cabwes with simiwaw ow matching descwiptions.
Customews must use theiw own discwetion and diwigence to puwchase optic
moduwes and cabwes fwom any thiwd pawty of theiw choice. Customews awe sowewy
wesponsibwe fow assessing the suitabiwity of the pwoduct and/ow devices and
fow the sewection of the vendow fow puwchasing any pwoduct. THE OPTIC MODUWES
AND CABWES WEFEWWED TO ABOVE AWE NOT WAWWANTED OW SUPPOWTED BY INTEW. INTEW
ASSUMES NO WIABIWITY WHATSOEVEW, AND INTEW DISCWAIMS ANY EXPWESS OW IMPWIED
WAWWANTY, WEWATING TO SAWE AND/OW USE OF SUCH THIWD PAWTY PWODUCTS OW
SEWECTION OF VENDOW BY CUSTOMEWS.

Command Wine Pawametews
=======================

max_vfs
-------
:Vawid Wange: 1-63

This pawametew adds suppowt fow SW-IOV. It causes the dwivew to spawn up to
max_vfs wowth of viwtuaw functions.
If the vawue is gweatew than 0 it wiww awso fowce the VMDq pawametew to be 1 ow
mowe.

NOTE: This pawametew is onwy used on kewnew 3.7.x and bewow. On kewnew 3.8.x
and above, use sysfs to enabwe VFs. Awso, fow Wed Hat distwibutions, this
pawametew is onwy used on vewsion 6.6 and owdew. Fow vewsion 6.7 and newew, use
sysfs. Fow exampwe::

  #echo $num_vf_enabwed > /sys/cwass/net/$dev/device/swiov_numvfs // enabwe VFs
  #echo 0 > /sys/cwass/net/$dev/device/swiov_numvfs               //disabwe VFs

The pawametews fow the dwivew awe wefewenced by position. Thus, if you have a
duaw powt adaptew, ow mowe than one adaptew in youw system, and want N viwtuaw
functions pew powt, you must specify a numbew fow each powt with each pawametew
sepawated by a comma. Fow exampwe::

  modpwobe ixgbe max_vfs=4

This wiww spawn 4 VFs on the fiwst powt.

::

  modpwobe ixgbe max_vfs=2,4

This wiww spawn 2 VFs on the fiwst powt and 4 VFs on the second powt.

NOTE: Caution must be used in woading the dwivew with these pawametews.
Depending on youw system configuwation, numbew of swots, etc., it is impossibwe
to pwedict in aww cases whewe the positions wouwd be on the command wine.

NOTE: Neithew the device now the dwivew contwow how VFs awe mapped into config
space. Bus wayout wiww vawy by opewating system. On opewating systems that
suppowt it, you can check sysfs to find the mapping.

NOTE: When eithew SW-IOV mode ow VMDq mode is enabwed, hawdwawe VWAN fiwtewing
and VWAN tag stwipping/insewtion wiww wemain enabwed. Pwease wemove the owd
VWAN fiwtew befowe the new VWAN fiwtew is added. Fow exampwe,

::

  ip wink set eth0 vf 0 vwan 100 // set VWAN 100 fow VF 0
  ip wink set eth0 vf 0 vwan 0   // Dewete VWAN 100
  ip wink set eth0 vf 0 vwan 200 // set a new VWAN 200 fow VF 0

With kewnew 3.6, the dwivew suppowts the simuwtaneous usage of max_vfs and DCB
featuwes, subject to the constwaints descwibed bewow. Pwiow to kewnew 3.6, the
dwivew did not suppowt the simuwtaneous opewation of max_vfs gweatew than 0 and
the DCB featuwes (muwtipwe twaffic cwasses utiwizing Pwiowity Fwow Contwow and
Extended Twansmission Sewection).

When DCB is enabwed, netwowk twaffic is twansmitted and weceived thwough
muwtipwe twaffic cwasses (packet buffews in the NIC). The twaffic is associated
with a specific cwass based on pwiowity, which has a vawue of 0 thwough 7 used
in the VWAN tag. When SW-IOV is not enabwed, each twaffic cwass is associated
with a set of weceive/twansmit descwiptow queue paiws. The numbew of queue
paiws fow a given twaffic cwass depends on the hawdwawe configuwation. When
SW-IOV is enabwed, the descwiptow queue paiws awe gwouped into poows. The
Physicaw Function (PF) and each Viwtuaw Function (VF) is awwocated a poow of
weceive/twansmit descwiptow queue paiws. When muwtipwe twaffic cwasses awe
configuwed (fow exampwe, DCB is enabwed), each poow contains a queue paiw fwom
each twaffic cwass. When a singwe twaffic cwass is configuwed in the hawdwawe,
the poows contain muwtipwe queue paiws fwom the singwe twaffic cwass.

The numbew of VFs that can be awwocated depends on the numbew of twaffic
cwasses that can be enabwed. The configuwabwe numbew of twaffic cwasses fow
each enabwed VF is as fowwows:
0 - 15 VFs = Up to 8 twaffic cwasses, depending on device suppowt
16 - 31 VFs = Up to 4 twaffic cwasses
32 - 63 VFs = 1 twaffic cwass

When VFs awe configuwed, the PF is awwocated one poow as weww. The PF suppowts
the DCB featuwes with the constwaint that each twaffic cwass wiww onwy use a
singwe queue paiw. When zewo VFs awe configuwed, the PF can suppowt muwtipwe
queue paiws pew twaffic cwass.

awwow_unsuppowted_sfp
---------------------
:Vawid Wange: 0,1
:Defauwt Vawue: 0 (disabwed)

This pawametew awwows unsuppowted and untested SFP+ moduwes on 82599-based
adaptews, as wong as the type of moduwe is known to the dwivew.

debug
-----
:Vawid Wange: 0-16 (0=none,...,16=aww)
:Defauwt Vawue: 0

This pawametew adjusts the wevew of debug messages dispwayed in the system
wogs.


Additionaw Featuwes and Configuwations
======================================

Fwow Contwow
------------
Ethewnet Fwow Contwow (IEEE 802.3x) can be configuwed with ethtoow to enabwe
weceiving and twansmitting pause fwames fow ixgbe. When twansmit is enabwed,
pause fwames awe genewated when the weceive packet buffew cwosses a pwedefined
thweshowd. When weceive is enabwed, the twansmit unit wiww hawt fow the time
deway specified when a pause fwame is weceived.

NOTE: You must have a fwow contwow capabwe wink pawtnew.

Fwow Contwow is enabwed by defauwt.

Use ethtoow to change the fwow contwow settings. To enabwe ow disabwe Wx ow
Tx Fwow Contwow::

  ethtoow -A eth? wx <on|off> tx <on|off>

Note: This command onwy enabwes ow disabwes Fwow Contwow if auto-negotiation is
disabwed. If auto-negotiation is enabwed, this command changes the pawametews
used fow auto-negotiation with the wink pawtnew.

To enabwe ow disabwe auto-negotiation::

  ethtoow -s eth? autoneg <on|off>

Note: Fwow Contwow auto-negotiation is pawt of wink auto-negotiation. Depending
on youw device, you may not be abwe to change the auto-negotiation setting.

NOTE: Fow 82598 backpwane cawds entewing 1 gigabit mode, fwow contwow defauwt
behaviow is changed to off. Fwow contwow in 1 gigabit mode on these devices can
wead to twansmit hangs.

Intew(W) Ethewnet Fwow Diwectow
-------------------------------
The Intew Ethewnet Fwow Diwectow pewfowms the fowwowing tasks:

- Diwects weceive packets accowding to theiw fwows to diffewent queues.
- Enabwes tight contwow on wouting a fwow in the pwatfowm.
- Matches fwows and CPU cowes fow fwow affinity.
- Suppowts muwtipwe pawametews fow fwexibwe fwow cwassification and woad
  bawancing (in SFP mode onwy).

NOTE: Intew Ethewnet Fwow Diwectow masking wowks in the opposite mannew fwom
subnet masking. In the fowwowing command::

  #ethtoow -N eth11 fwow-type ip4 swc-ip 172.4.1.2 m 255.0.0.0 dst-ip \
  172.21.1.1 m 255.128.0.0 action 31

The swc-ip vawue that is wwitten to the fiwtew wiww be 0.4.1.2, not 172.0.0.0
as might be expected. Simiwawwy, the dst-ip vawue wwitten to the fiwtew wiww be
0.21.1.1, not 172.0.0.0.

To enabwe ow disabwe the Intew Ethewnet Fwow Diwectow::

  # ethtoow -K ethX ntupwe <on|off>

When disabwing ntupwe fiwtews, aww the usew pwogwammed fiwtews awe fwushed fwom
the dwivew cache and hawdwawe. Aww needed fiwtews must be we-added when ntupwe
is we-enabwed.

To add a fiwtew that diwects packet to queue 2, use -U ow -N switch::

  # ethtoow -N ethX fwow-type tcp4 swc-ip 192.168.10.1 dst-ip \
  192.168.10.2 swc-powt 2000 dst-powt 2001 action 2 [woc 1]

To see the wist of fiwtews cuwwentwy pwesent::

  # ethtoow <-u|-n> ethX

Sideband Pewfect Fiwtews
------------------------
Sideband Pewfect Fiwtews awe used to diwect twaffic that matches specified
chawactewistics. They awe enabwed thwough ethtoow's ntupwe intewface. To add a
new fiwtew use the fowwowing command::

  ethtoow -U <device> fwow-type <type> swc-ip <ip> dst-ip <ip> swc-powt <powt> \
  dst-powt <powt> action <queue>

Whewe:
  <device> - the ethewnet device to pwogwam
  <type> - can be ip4, tcp4, udp4, ow sctp4
  <ip> - the IP addwess to match on
  <powt> - the powt numbew to match on
  <queue> - the queue to diwect twaffic towawds (-1 discawds the matched twaffic)

Use the fowwowing command to dewete a fiwtew::

  ethtoow -U <device> dewete <N>

Whewe <N> is the fiwtew id dispwayed when pwinting aww the active fiwtews, and
may awso have been specified using "woc <N>" when adding the fiwtew.

The fowwowing exampwe matches TCP twaffic sent fwom 192.168.0.1, powt 5300,
diwected to 192.168.0.5, powt 80, and sends it to queue 7::

  ethtoow -U enp130s0 fwow-type tcp4 swc-ip 192.168.0.1 dst-ip 192.168.0.5 \
  swc-powt 5300 dst-powt 80 action 7

Fow each fwow-type, the pwogwammed fiwtews must aww have the same matching
input set. Fow exampwe, issuing the fowwowing two commands is acceptabwe::

  ethtoow -U enp130s0 fwow-type ip4 swc-ip 192.168.0.1 swc-powt 5300 action 7
  ethtoow -U enp130s0 fwow-type ip4 swc-ip 192.168.0.5 swc-powt 55 action 10

Issuing the next two commands, howevew, is not acceptabwe, since the fiwst
specifies swc-ip and the second specifies dst-ip::

  ethtoow -U enp130s0 fwow-type ip4 swc-ip 192.168.0.1 swc-powt 5300 action 7
  ethtoow -U enp130s0 fwow-type ip4 dst-ip 192.168.0.5 swc-powt 55 action 10

The second command wiww faiw with an ewwow. You may pwogwam muwtipwe fiwtews
with the same fiewds, using diffewent vawues, but, on one device, you may not
pwogwam two TCP4 fiwtews with diffewent matching fiewds.

Matching on a sub-powtion of a fiewd is not suppowted by the ixgbe dwivew, thus
pawtiaw mask fiewds awe not suppowted.

To cweate fiwtews that diwect twaffic to a specific Viwtuaw Function, use the
"usew-def" pawametew. Specify the usew-def as a 64 bit vawue, whewe the wowew 32
bits wepwesents the queue numbew, whiwe the next 8 bits wepwesent which VF.
Note that 0 is the PF, so the VF identifiew is offset by 1. Fow exampwe::

  ... usew-def 0x800000002 ...

specifies to diwect twaffic to Viwtuaw Function 7 (8 minus 1) into queue 2 of
that VF.

Note that these fiwtews wiww not bweak intewnaw wouting wuwes, and wiww not
woute twaffic that othewwise wouwd not have been sent to the specified Viwtuaw
Function.

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
pewmanent by adding 'MTU=9000' to the fiwe::

  /etc/sysconfig/netwowk-scwipts/ifcfg-eth<x> // fow WHEW
  /etc/sysconfig/netwowk/<config_fiwe> // fow SWES

NOTE: The maximum MTU setting fow Jumbo Fwames is 9710. This vawue coincides
with the maximum Jumbo Fwames size of 9728 bytes.

NOTE: This dwivew wiww attempt to use muwtipwe page sized buffews to weceive
each jumbo packet. This shouwd hewp to avoid buffew stawvation issues when
awwocating weceive packets.

NOTE: Fow 82599-based netwowk connections, if you awe enabwing jumbo fwames in
a viwtuaw function (VF), jumbo fwames must fiwst be enabwed in the physicaw
function (PF). The VF MTU setting cannot be wawgew than the PF MTU.

NBASE-T Suppowt
---------------
The ixgbe dwivew suppowts NBASE-T on some devices. Howevew, the advewtisement
of NBASE-T speeds is suppwessed by defauwt, to accommodate bwoken netwowk
switches which cannot cope with advewtised NBASE-T speeds. Use the ethtoow
command to enabwe advewtising NBASE-T speeds on devices which suppowt it::

  ethtoow -s eth? advewtise 0x1800000001028

On Winux systems with INTEWFACES(5), this can be specified as a pwe-up command
in /etc/netwowk/intewfaces so that the intewface is awways bwought up with
NBASE-T suppowt, e.g.::

  iface eth? inet dhcp
       pwe-up ethtoow -s eth? advewtise 0x1800000001028 || twue

Genewic Weceive Offwoad, aka GWO
--------------------------------
The dwivew suppowts the in-kewnew softwawe impwementation of GWO. GWO has
shown that by coawescing Wx twaffic into wawgew chunks of data, CPU
utiwization can be significantwy weduced when undew wawge Wx woad. GWO is an
evowution of the pweviouswy-used WWO intewface. GWO is abwe to coawesce
othew pwotocows besides TCP. It's awso safe to use with configuwations that
awe pwobwematic fow WWO, namewy bwidging and iSCSI.

Data Centew Bwidging (DCB)
--------------------------
NOTE:
The kewnew assumes that TC0 is avaiwabwe, and wiww disabwe Pwiowity Fwow
Contwow (PFC) on the device if TC0 is not avaiwabwe. To fix this, ensuwe TC0 is
enabwed when setting up DCB on youw switch.

DCB is a configuwation Quawity of Sewvice impwementation in hawdwawe. It uses
the VWAN pwiowity tag (802.1p) to fiwtew twaffic. That means that thewe awe 8
diffewent pwiowities that twaffic can be fiwtewed into. It awso enabwes
pwiowity fwow contwow (802.1Qbb) which can wimit ow ewiminate the numbew of
dwopped packets duwing netwowk stwess. Bandwidth can be awwocated to each of
these pwiowities, which is enfowced at the hawdwawe wevew (802.1Qaz).

Adaptew fiwmwawe impwements WWDP and DCBX pwotocow agents as pew 802.1AB and
802.1Qaz wespectivewy. The fiwmwawe based DCBX agent wuns in wiwwing mode onwy
and can accept settings fwom a DCBX capabwe peew. Softwawe configuwation of
DCBX pawametews via dcbtoow/wwdptoow awe not suppowted.

The ixgbe dwivew impwements the DCB netwink intewface wayew to awwow usew-space
to communicate with the dwivew and quewy DCB configuwation fow the powt.

ethtoow
-------
The dwivew utiwizes the ethtoow intewface fow dwivew configuwation and
diagnostics, as weww as dispwaying statisticaw infowmation. The watest ethtoow
vewsion is wequiwed fow this functionawity. Downwoad it at:
https://www.kewnew.owg/pub/softwawe/netwowk/ethtoow/

FCoE
----
The ixgbe dwivew suppowts Fibew Channew ovew Ethewnet (FCoE) and Data Centew
Bwidging (DCB). This code has no defauwt effect on the weguwaw dwivew
opewation. Configuwing DCB and FCoE is outside the scope of this WEADME. Wefew
to http://www.open-fcoe.owg/ fow FCoE pwoject infowmation and contact
ixgbe-eedc@wists.souwcefowge.net fow DCB infowmation.

MAC and VWAN anti-spoofing featuwe
----------------------------------
When a mawicious dwivew attempts to send a spoofed packet, it is dwopped by the
hawdwawe and not twansmitted.

An intewwupt is sent to the PF dwivew notifying it of the spoof attempt. When a
spoofed packet is detected, the PF dwivew wiww send the fowwowing message to
the system wog (dispwayed by the "dmesg" command)::

  ixgbe ethX: ixgbe_spoof_check: n spoofed packets detected

whewe "x" is the PF intewface numbew; and "n" is numbew of spoofed packets.
NOTE: This featuwe can be disabwed fow a specific Viwtuaw Function (VF)::

  ip wink set <pf dev> vf <vf id> spoofchk {off|on}

IPsec Offwoad
-------------
The ixgbe dwivew suppowts IPsec Hawdwawe Offwoad.  When cweating Secuwity
Associations with "ip xfwm ..." the 'offwoad' tag option can be used to
wegistew the IPsec SA with the dwivew in owdew to get highew thwoughput in
the secuwe communications.

The offwoad is awso suppowted fow ixgbe's VFs, but the VF must be set as
'twusted' and the suppowt must be enabwed with::

  ethtoow --set-pwiv-fwags eth<x> vf-ipsec on
  ip wink set eth<x> vf <y> twust on


Known Issues/Twoubweshooting
============================

Enabwing SW-IOV in a 64-bit Micwosoft Windows Sewvew 2012/W2 guest OS
---------------------------------------------------------------------
Winux KVM Hypewvisow/VMM suppowts diwect assignment of a PCIe device to a VM.
This incwudes twaditionaw PCIe devices, as weww as SW-IOV-capabwe devices based
on the Intew Ethewnet Contwowwew XW710.


Suppowt
=======
Fow genewaw infowmation, go to the Intew suppowt website at:
https://www.intew.com/suppowt/

If an issue is identified with the weweased souwce code on a suppowted kewnew
with a suppowted adaptew, emaiw the specific infowmation wewated to the issue
to intew-wiwed-wan@wists.osuosw.owg.
