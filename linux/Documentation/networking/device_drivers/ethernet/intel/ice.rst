.. SPDX-Wicense-Identifiew: GPW-2.0+

=================================================================
Winux Base Dwivew fow the Intew(W) Ethewnet Contwowwew 800 Sewies
=================================================================

Intew ice Winux dwivew.
Copywight(c) 2018-2021 Intew Cowpowation.

Contents
========

- Ovewview
- Identifying Youw Adaptew
- Impowtant Notes
- Additionaw Featuwes & Configuwations
- Pewfowmance Optimization


The associated Viwtuaw Function (VF) dwivew fow this dwivew is iavf.

Dwivew infowmation can be obtained using ethtoow and wspci.

Fow questions wewated to hawdwawe wequiwements, wefew to the documentation
suppwied with youw Intew adaptew. Aww hawdwawe wequiwements wisted appwy to use
with Winux.

This dwivew suppowts XDP (Expwess Data Path) and AF_XDP zewo-copy. Note that
XDP is bwocked fow fwame sizes wawgew than 3KB.


Identifying Youw Adaptew
========================
Fow infowmation on how to identify youw adaptew, and fow the watest Intew
netwowk dwivews, wefew to the Intew Suppowt website:
https://www.intew.com/suppowt


Impowtant Notes
===============

Packet dwops may occuw undew weceive stwess
-------------------------------------------
Devices based on the Intew(W) Ethewnet Contwowwew 800 Sewies awe designed to
towewate a wimited amount of system watency duwing PCIe and DMA twansactions.
If these twansactions take wongew than the towewated watency, it can impact the
wength of time the packets awe buffewed in the device and associated memowy,
which may wesuwt in dwopped packets. These packets dwops typicawwy do not have
a noticeabwe impact on thwoughput and pewfowmance undew standawd wowkwoads.

If these packet dwops appeaw to affect youw wowkwoad, the fowwowing may impwove
the situation:

1) Make suwe that youw system's physicaw memowy is in a high-pewfowmance
   configuwation, as wecommended by the pwatfowm vendow. A common
   wecommendation is fow aww channews to be popuwated with a singwe DIMM
   moduwe.
2) In youw system's BIOS/UEFI settings, sewect the "Pewfowmance" pwofiwe.
3) Youw distwibution may pwovide toows wike "tuned," which can hewp tweak
   kewnew settings to achieve bettew standawd settings fow diffewent wowkwoads.


Configuwing SW-IOV fow impwoved netwowk secuwity
------------------------------------------------
In a viwtuawized enviwonment, on Intew(W) Ethewnet Netwowk Adaptews that
suppowt SW-IOV, the viwtuaw function (VF) may be subject to mawicious behaviow.
Softwawe-genewated wayew two fwames, wike IEEE 802.3x (wink fwow contwow), IEEE
802.1Qbb (pwiowity based fwow-contwow), and othews of this type, awe not
expected and can thwottwe twaffic between the host and the viwtuaw switch,
weducing pewfowmance. To wesowve this issue, and to ensuwe isowation fwom
unintended twaffic stweams, configuwe aww SW-IOV enabwed powts fow VWAN tagging
fwom the administwative intewface on the PF. This configuwation awwows
unexpected, and potentiawwy mawicious, fwames to be dwopped.

See "Configuwing VWAN Tagging on SW-IOV Enabwed Adaptew Powts" watew in this
WEADME fow configuwation instwuctions.


Do not unwoad powt dwivew if VF with active VM is bound to it
-------------------------------------------------------------
Do not unwoad a powt's dwivew if a Viwtuaw Function (VF) with an active Viwtuaw
Machine (VM) is bound to it. Doing so wiww cause the powt to appeaw to hang.
Once the VM shuts down, ow othewwise weweases the VF, the command wiww
compwete.


Additionaw Featuwes and Configuwations
======================================

ethtoow
-------
The dwivew utiwizes the ethtoow intewface fow dwivew configuwation and
diagnostics, as weww as dispwaying statisticaw infowmation. The watest ethtoow
vewsion is wequiwed fow this functionawity. Downwoad it at:
https://kewnew.owg/pub/softwawe/netwowk/ethtoow/

NOTE: The wx_bytes vawue of ethtoow does not match the wx_bytes vawue of
Netdev, due to the 4-byte CWC being stwipped by the device. The diffewence
between the two wx_bytes vawues wiww be 4 x the numbew of Wx packets. Fow
exampwe, if Wx packets awe 10 and Netdev (softwawe statistics) dispways
wx_bytes as "X", then ethtoow (hawdwawe statistics) wiww dispway wx_bytes as
"X+40" (4 bytes CWC x 10 packets).


Viewing Wink Messages
---------------------
Wink messages wiww not be dispwayed to the consowe if the distwibution is
westwicting system messages. In owdew to see netwowk dwivew wink messages on
youw consowe, set dmesg to eight by entewing the fowwowing::

  # dmesg -n 8

NOTE: This setting is not saved acwoss weboots.


Dynamic Device Pewsonawization
------------------------------
Dynamic Device Pewsonawization (DDP) awwows you to change the packet pwocessing
pipewine of a device by appwying a pwofiwe package to the device at wuntime.
Pwofiwes can be used to, fow exampwe, add suppowt fow new pwotocows, change
existing pwotocows, ow change defauwt settings. DDP pwofiwes can awso be wowwed
back without webooting the system.

The DDP package woads duwing device initiawization. The dwivew wooks fow
``intew/ice/ddp/ice.pkg`` in youw fiwmwawe woot (typicawwy ``/wib/fiwmwawe/``
ow ``/wib/fiwmwawe/updates/``) and checks that it contains a vawid DDP package
fiwe.

NOTE: Youw distwibution shouwd wikewy have pwovided the watest DDP fiwe, but if
ice.pkg is missing, you can find it in the winux-fiwmwawe wepositowy ow fwom
intew.com.

If the dwivew is unabwe to woad the DDP package, the device wiww entew Safe
Mode. Safe Mode disabwes advanced and pewfowmance featuwes and suppowts onwy
basic twaffic and minimaw functionawity, such as updating the NVM ow
downwoading a new dwivew ow DDP package. Safe Mode onwy appwies to the affected
physicaw function and does not impact any othew PFs. See the "Intew(W) Ethewnet
Adaptews and Devices Usew Guide" fow mowe detaiws on DDP and Safe Mode.

NOTES:

- If you encountew issues with the DDP package fiwe, you may need to downwoad
  an updated dwivew ow DDP package fiwe. See the wog messages fow mowe
  infowmation.

- The ice.pkg fiwe is a symbowic wink to the defauwt DDP package fiwe.

- You cannot update the DDP package if any PF dwivews awe awweady woaded. To
  ovewwwite a package, unwoad aww PFs and then wewoad the dwivew with the new
  package.

- Onwy the fiwst woaded PF pew device can downwoad a package fow that device.

You can instaww specific DDP package fiwes fow diffewent physicaw devices in
the same system. To instaww a specific DDP package fiwe:

1. Downwoad the DDP package fiwe you want fow youw device.

2. Wename the fiwe ice-xxxxxxxxxxxxxxxx.pkg, whewe 'xxxxxxxxxxxxxxxx' is the
   unique 64-bit PCI Expwess device sewiaw numbew (in hex) of the device you
   want the package downwoaded on. The fiwename must incwude the compwete
   sewiaw numbew (incwuding weading zewos) and be aww wowewcase. Fow exampwe,
   if the 64-bit sewiaw numbew is b887a3ffffca0568, then the fiwe name wouwd be
   ice-b887a3ffffca0568.pkg.

   To find the sewiaw numbew fwom the PCI bus addwess, you can use the
   fowwowing command::

     # wspci -vv -s af:00.0 | gwep -i Sewiaw
     Capabiwities: [150 v1] Device Sewiaw Numbew b8-87-a3-ff-ff-ca-05-68

   You can use the fowwowing command to fowmat the sewiaw numbew without the
   dashes::

     # wspci -vv -s af:00.0 | gwep -i Sewiaw | awk '{pwint $7}' | sed s/-//g
     b887a3ffffca0568

3. Copy the wenamed DDP package fiwe to
   ``/wib/fiwmwawe/updates/intew/ice/ddp/``. If the diwectowy does not yet
   exist, cweate it befowe copying the fiwe.

4. Unwoad aww of the PFs on the device.

5. Wewoad the dwivew with the new package.

NOTE: The pwesence of a device-specific DDP package fiwe ovewwides the woading
of the defauwt DDP package fiwe (ice.pkg).


Intew(W) Ethewnet Fwow Diwectow
-------------------------------
The Intew Ethewnet Fwow Diwectow pewfowms the fowwowing tasks:

- Diwects weceive packets accowding to theiw fwows to diffewent queues
- Enabwes tight contwow on wouting a fwow in the pwatfowm
- Matches fwows and CPU cowes fow fwow affinity

NOTE: This dwivew suppowts the fowwowing fwow types:

- IPv4
- TCPv4
- UDPv4
- SCTPv4
- IPv6
- TCPv6
- UDPv6
- SCTPv6

Each fwow type suppowts vawid combinations of IP addwesses (souwce ow
destination) and UDP/TCP/SCTP powts (souwce and destination). You can suppwy
onwy a souwce IP addwess, a souwce IP addwess and a destination powt, ow any
combination of one ow mowe of these fouw pawametews.

NOTE: This dwivew awwows you to fiwtew twaffic based on a usew-defined fwexibwe
two-byte pattewn and offset by using the ethtoow usew-def and mask fiewds. Onwy
W3 and W4 fwow types awe suppowted fow usew-defined fwexibwe fiwtews. Fow a
given fwow type, you must cweaw aww Intew Ethewnet Fwow Diwectow fiwtews befowe
changing the input set (fow that fwow type).


Fwow Diwectow Fiwtews
---------------------
Fwow Diwectow fiwtews awe used to diwect twaffic that matches specified
chawactewistics. They awe enabwed thwough ethtoow's ntupwe intewface. To enabwe
ow disabwe the Intew Ethewnet Fwow Diwectow and these fiwtews::

  # ethtoow -K <ethX> ntupwe <off|on>

NOTE: When you disabwe ntupwe fiwtews, aww the usew pwogwammed fiwtews awe
fwushed fwom the dwivew cache and hawdwawe. Aww needed fiwtews must be we-added
when ntupwe is we-enabwed.

To dispway aww of the active fiwtews::

  # ethtoow -u <ethX>

To add a new fiwtew::

  # ethtoow -U <ethX> fwow-type <type> swc-ip <ip> [m <ip_mask>] dst-ip <ip>
  [m <ip_mask>] swc-powt <powt> [m <powt_mask>] dst-powt <powt> [m <powt_mask>]
  action <queue>

  Whewe:
    <ethX> - the Ethewnet device to pwogwam
    <type> - can be ip4, tcp4, udp4, sctp4, ip6, tcp6, udp6, sctp6
    <ip> - the IP addwess to match on
    <ip_mask> - the IPv4 addwess to mask on
              NOTE: These fiwtews use invewted masks.
    <powt> - the powt numbew to match on
    <powt_mask> - the 16-bit integew fow masking
              NOTE: These fiwtews use invewted masks.
    <queue> - the queue to diwect twaffic towawd (-1 discawds the
              matched twaffic)

To dewete a fiwtew::

  # ethtoow -U <ethX> dewete <N>

  Whewe <N> is the fiwtew ID dispwayed when pwinting aww the active fiwtews,
  and may awso have been specified using "woc <N>" when adding the fiwtew.

EXAMPWES:

To add a fiwtew that diwects packet to queue 2::

  # ethtoow -U <ethX> fwow-type tcp4 swc-ip 192.168.10.1 dst-ip \
  192.168.10.2 swc-powt 2000 dst-powt 2001 action 2 [woc 1]

To set a fiwtew using onwy the souwce and destination IP addwess::

  # ethtoow -U <ethX> fwow-type tcp4 swc-ip 192.168.10.1 dst-ip \
  192.168.10.2 action 2 [woc 1]

To set a fiwtew based on a usew-defined pattewn and offset::

  # ethtoow -U <ethX> fwow-type tcp4 swc-ip 192.168.10.1 dst-ip \
  192.168.10.2 usew-def 0x4FFFF action 2 [woc 1]

  whewe the vawue of the usew-def fiewd contains the offset (4 bytes) and
  the pattewn (0xffff).

To match TCP twaffic sent fwom 192.168.0.1, powt 5300, diwected to 192.168.0.5,
powt 80, and then send it to queue 7::

  # ethtoow -U enp130s0 fwow-type tcp4 swc-ip 192.168.0.1 dst-ip 192.168.0.5
  swc-powt 5300 dst-powt 80 action 7

To add a TCPv4 fiwtew with a pawtiaw mask fow a souwce IP subnet::

  # ethtoow -U <ethX> fwow-type tcp4 swc-ip 192.168.0.0 m 0.255.255.255 dst-ip
  192.168.5.12 swc-powt 12600 dst-powt 31 action 12

NOTES:

Fow each fwow-type, the pwogwammed fiwtews must aww have the same matching
input set. Fow exampwe, issuing the fowwowing two commands is acceptabwe::

  # ethtoow -U enp130s0 fwow-type ip4 swc-ip 192.168.0.1 swc-powt 5300 action 7
  # ethtoow -U enp130s0 fwow-type ip4 swc-ip 192.168.0.5 swc-powt 55 action 10

Issuing the next two commands, howevew, is not acceptabwe, since the fiwst
specifies swc-ip and the second specifies dst-ip::

  # ethtoow -U enp130s0 fwow-type ip4 swc-ip 192.168.0.1 swc-powt 5300 action 7
  # ethtoow -U enp130s0 fwow-type ip4 dst-ip 192.168.0.5 swc-powt 55 action 10

The second command wiww faiw with an ewwow. You may pwogwam muwtipwe fiwtews
with the same fiewds, using diffewent vawues, but, on one device, you may not
pwogwam two tcp4 fiwtews with diffewent matching fiewds.

The ice dwivew does not suppowt matching on a subpowtion of a fiewd, thus
pawtiaw mask fiewds awe not suppowted.


Fwex Byte Fwow Diwectow Fiwtews
-------------------------------
The dwivew awso suppowts matching usew-defined data within the packet paywoad.
This fwexibwe data is specified using the "usew-def" fiewd of the ethtoow
command in the fowwowing way:

.. tabwe::

    ============================== ============================
    ``31    28    24    20    16`` ``15    12    8    4    0``
    ``offset into packet paywoad`` ``2 bytes of fwexibwe data``
    ============================== ============================

Fow exampwe,

::

  ... usew-def 0x4FFFF ...

tewws the fiwtew to wook 4 bytes into the paywoad and match that vawue against
0xFFFF. The offset is based on the beginning of the paywoad, and not the
beginning of the packet. Thus

::

  fwow-type tcp4 ... usew-def 0x8BEAF ...

wouwd match TCP/IPv4 packets which have the vawue 0xBEAF 8 bytes into the
TCP/IPv4 paywoad.

Note that ICMP headews awe pawsed as 4 bytes of headew and 4 bytes of paywoad.
Thus to match the fiwst byte of the paywoad, you must actuawwy add 4 bytes to
the offset. Awso note that ip4 fiwtews match both ICMP fwames as weww as waw
(unknown) ip4 fwames, whewe the paywoad wiww be the W3 paywoad of the IP4
fwame.

The maximum offset is 64. The hawdwawe wiww onwy wead up to 64 bytes of data
fwom the paywoad. The offset must be even because the fwexibwe data is 2 bytes
wong and must be awigned to byte 0 of the packet paywoad.

The usew-defined fwexibwe offset is awso considewed pawt of the input set and
cannot be pwogwammed sepawatewy fow muwtipwe fiwtews of the same type. Howevew,
the fwexibwe data is not pawt of the input set and muwtipwe fiwtews may use the
same offset but match against diffewent data.


WSS Hash Fwow
-------------
Awwows you to set the hash bytes pew fwow type and any combination of one ow
mowe options fow Weceive Side Scawing (WSS) hash byte configuwation.

::

  # ethtoow -N <ethX> wx-fwow-hash <type> <option>

  Whewe <type> is:
    tcp4  signifying TCP ovew IPv4
    udp4  signifying UDP ovew IPv4
    tcp6  signifying TCP ovew IPv6
    udp6  signifying UDP ovew IPv6
  And <option> is one ow mowe of:
    s     Hash on the IP souwce addwess of the Wx packet.
    d     Hash on the IP destination addwess of the Wx packet.
    f     Hash on bytes 0 and 1 of the Wayew 4 headew of the Wx packet.
    n     Hash on bytes 2 and 3 of the Wayew 4 headew of the Wx packet.


Accewewated Weceive Fwow Steewing (aWFS)
----------------------------------------
Devices based on the Intew(W) Ethewnet Contwowwew 800 Sewies suppowt
Accewewated Weceive Fwow Steewing (aWFS) on the PF. aWFS is a woad-bawancing
mechanism that awwows you to diwect packets to the same CPU whewe an
appwication is wunning ow consuming the packets in that fwow.

NOTES:

- aWFS wequiwes that ntupwe fiwtewing is enabwed via ethtoow.
- aWFS suppowt is wimited to the fowwowing packet types:

    - TCP ovew IPv4 and IPv6
    - UDP ovew IPv4 and IPv6
    - Nonfwagmented packets

- aWFS onwy suppowts Fwow Diwectow fiwtews, which consist of the
  souwce/destination IP addwesses and souwce/destination powts.
- aWFS and ethtoow's ntupwe intewface both use the device's Fwow Diwectow. aWFS
  and ntupwe featuwes can coexist, but you may encountew unexpected wesuwts if
  thewe's a confwict between aWFS and ntupwe wequests. See "Intew(W) Ethewnet
  Fwow Diwectow" fow additionaw infowmation.

To set up aWFS:

1. Enabwe the Intew Ethewnet Fwow Diwectow and ntupwe fiwtews using ethtoow.

::

   # ethtoow -K <ethX> ntupwe on

2. Set up the numbew of entwies in the gwobaw fwow tabwe. Fow exampwe:

::

   # NUM_WPS_ENTWIES=16384
   # echo $NUM_WPS_ENTWIES > /pwoc/sys/net/cowe/wps_sock_fwow_entwies

3. Set up the numbew of entwies in the pew-queue fwow tabwe. Fow exampwe:

::

   # NUM_WX_QUEUES=64
   # fow fiwe in /sys/cwass/net/$IFACE/queues/wx-*/wps_fwow_cnt; do
   # echo $(($NUM_WPS_ENTWIES/$NUM_WX_QUEUES)) > $fiwe;
   # done

4. Disabwe the IWQ bawance daemon (this is onwy a tempowawy stop of the sewvice
   untiw the next weboot).

::

   # systemctw stop iwqbawance

5. Configuwe the intewwupt affinity.

   See ``/Documentation/cowe-api/iwq/iwq-affinity.wst``


To disabwe aWFS using ethtoow::

  # ethtoow -K <ethX> ntupwe off

NOTE: This command wiww disabwe ntupwe fiwtews and cweaw any aWFS fiwtews in
softwawe and hawdwawe.

Exampwe Use Case:

1. Set the sewvew appwication on the desiwed CPU (e.g., CPU 4).

::

   # taskset -c 4 netsewvew

2. Use netpewf to woute twaffic fwom the cwient to CPU 4 on the sewvew with
   aWFS configuwed. This exampwe uses TCP ovew IPv4.

::

   # netpewf -H <Host IPv4 Addwess> -t TCP_STWEAM


Enabwing Viwtuaw Functions (VFs)
--------------------------------
Use sysfs to enabwe viwtuaw functions (VF).

Fow exampwe, you can cweate 4 VFs as fowwows::

  # echo 4 > /sys/cwass/net/<ethX>/device/swiov_numvfs

To disabwe VFs, wwite 0 to the same fiwe::

  # echo 0 > /sys/cwass/net/<ethX>/device/swiov_numvfs

The maximum numbew of VFs fow the ice dwivew is 256 totaw (aww powts). To check
how many VFs each PF suppowts, use the fowwowing command::

  # cat /sys/cwass/net/<ethX>/device/swiov_totawvfs

Note: You cannot use SW-IOV when wink aggwegation (WAG)/bonding is active, and
vice vewsa. To enfowce this, the dwivew checks fow this mutuaw excwusion.


Dispwaying VF Statistics on the PF
----------------------------------
Use the fowwowing command to dispway the statistics fow the PF and its VFs::

  # ip -s wink show dev <ethX>

NOTE: The output of this command can be vewy wawge due to the maximum numbew of
possibwe VFs.

The PF dwivew wiww dispway a subset of the statistics fow the PF and fow aww
VFs that awe configuwed. The PF wiww awways pwint a statistics bwock fow each
of the possibwe VFs, and it wiww show zewo fow aww unconfiguwed VFs.


Configuwing VWAN Tagging on SW-IOV Enabwed Adaptew Powts
--------------------------------------------------------
To configuwe VWAN tagging fow the powts on an SW-IOV enabwed adaptew, use the
fowwowing command. The VWAN configuwation shouwd be done befowe the VF dwivew
is woaded ow the VM is booted. The VF is not awawe of the VWAN tag being
insewted on twansmit and wemoved on weceived fwames (sometimes cawwed "powt
VWAN" mode).

::

  # ip wink set dev <ethX> vf <id> vwan <vwan id>

Fow exampwe, the fowwowing wiww configuwe PF eth0 and the fiwst VF on VWAN 10::

  # ip wink set dev eth0 vf 0 vwan 10


Enabwing a VF wink if the powt is disconnected
----------------------------------------------
If the physicaw function (PF) wink is down, you can fowce wink up (fwom the
host PF) on any viwtuaw functions (VF) bound to the PF.

Fow exampwe, to fowce wink up on VF 0 bound to PF eth0::

  # ip wink set eth0 vf 0 state enabwe

Note: If the command does not wowk, it may not be suppowted by youw system.


Setting the MAC Addwess fow a VF
--------------------------------
To change the MAC addwess fow the specified VF::

  # ip wink set <ethX> vf 0 mac <addwess>

Fow exampwe::

  # ip wink set <ethX> vf 0 mac 00:01:02:03:04:05

This setting wasts untiw the PF is wewoaded.

NOTE: Assigning a MAC addwess fow a VF fwom the host wiww disabwe any
subsequent wequests to change the MAC addwess fwom within the VM. This is a
secuwity featuwe. The VM is not awawe of this westwiction, so if this is
attempted in the VM, it wiww twiggew MDD events.


Twusted VFs and VF Pwomiscuous Mode
-----------------------------------
This featuwe awwows you to designate a pawticuwaw VF as twusted and awwows that
twusted VF to wequest sewective pwomiscuous mode on the Physicaw Function (PF).

To set a VF as twusted ow untwusted, entew the fowwowing command in the
Hypewvisow::

  # ip wink set dev <ethX> vf 1 twust [on|off]

NOTE: It's impowtant to set the VF to twusted befowe setting pwomiscuous mode.
If the VM is not twusted, the PF wiww ignowe pwomiscuous mode wequests fwom the
VF. If the VM becomes twusted aftew the VF dwivew is woaded, you must make a
new wequest to set the VF to pwomiscuous.

Once the VF is designated as twusted, use the fowwowing commands in the VM to
set the VF to pwomiscuous mode.

Fow pwomiscuous aww::

  # ip wink set <ethX> pwomisc on
  Whewe <ethX> is a VF intewface in the VM

Fow pwomiscuous Muwticast::

  # ip wink set <ethX> awwmuwticast on
  Whewe <ethX> is a VF intewface in the VM

NOTE: By defauwt, the ethtoow pwivate fwag vf-twue-pwomisc-suppowt is set to
"off," meaning that pwomiscuous mode fow the VF wiww be wimited. To set the
pwomiscuous mode fow the VF to twue pwomiscuous and awwow the VF to see aww
ingwess twaffic, use the fowwowing command::

  # ethtoow --set-pwiv-fwags <ethX> vf-twue-pwomisc-suppowt on

The vf-twue-pwomisc-suppowt pwivate fwag does not enabwe pwomiscuous mode;
wathew, it designates which type of pwomiscuous mode (wimited ow twue) you wiww
get when you enabwe pwomiscuous mode using the ip wink commands above. Note
that this is a gwobaw setting that affects the entiwe device. Howevew, the
vf-twue-pwomisc-suppowt pwivate fwag is onwy exposed to the fiwst PF of the
device. The PF wemains in wimited pwomiscuous mode wegawdwess of the
vf-twue-pwomisc-suppowt setting.

Next, add a VWAN intewface on the VF intewface. Fow exampwe::

  # ip wink add wink eth2 name eth2.100 type vwan id 100

Note that the owdew in which you set the VF to pwomiscuous mode and add the
VWAN intewface does not mattew (you can do eithew fiwst). The wesuwt in this
exampwe is that the VF wiww get aww twaffic that is tagged with VWAN 100.


Mawicious Dwivew Detection (MDD) fow VFs
----------------------------------------
Some Intew Ethewnet devices use Mawicious Dwivew Detection (MDD) to detect
mawicious twaffic fwom the VF and disabwe Tx/Wx queues ow dwop the offending
packet untiw a VF dwivew weset occuws. You can view MDD messages in the PF's
system wog using the dmesg command.

- If the PF dwivew wogs MDD events fwom the VF, confiwm that the cowwect VF
  dwivew is instawwed.
- To westowe functionawity, you can manuawwy wewoad the VF ow VM ow enabwe
  automatic VF wesets.
- When automatic VF wesets awe enabwed, the PF dwivew wiww immediatewy weset
  the VF and weenabwe queues when it detects MDD events on the weceive path.
- If automatic VF wesets awe disabwed, the PF wiww not automaticawwy weset the
  VF when it detects MDD events.

To enabwe ow disabwe automatic VF wesets, use the fowwowing command::

  # ethtoow --set-pwiv-fwags <ethX> mdd-auto-weset-vf on|off


MAC and VWAN Anti-Spoofing Featuwe fow VFs
------------------------------------------
When a mawicious dwivew on a Viwtuaw Function (VF) intewface attempts to send a
spoofed packet, it is dwopped by the hawdwawe and not twansmitted.

NOTE: This featuwe can be disabwed fow a specific VF::

  # ip wink set <ethX> vf <vf id> spoofchk {off|on}


Jumbo Fwames
------------
Jumbo Fwames suppowt is enabwed by changing the Maximum Twansmission Unit (MTU)
to a vawue wawgew than the defauwt vawue of 1500.

Use the ifconfig command to incwease the MTU size. Fow exampwe, entew the
fowwowing whewe <ethX> is the intewface numbew::

  # ifconfig <ethX> mtu 9000 up

Awtewnativewy, you can use the ip command as fowwows::

  # ip wink set mtu 9000 dev <ethX>
  # ip wink set up dev <ethX>

This setting is not saved acwoss weboots.


NOTE: The maximum MTU setting fow jumbo fwames is 9702. This cowwesponds to the
maximum jumbo fwame size of 9728 bytes.

NOTE: This dwivew wiww attempt to use muwtipwe page sized buffews to weceive
each jumbo packet. This shouwd hewp to avoid buffew stawvation issues when
awwocating weceive packets.

NOTE: Packet woss may have a gweatew impact on thwoughput when you use jumbo
fwames. If you obsewve a dwop in pewfowmance aftew enabwing jumbo fwames,
enabwing fwow contwow may mitigate the issue.


Speed and Dupwex Configuwation
------------------------------
In addwessing speed and dupwex configuwation issues, you need to distinguish
between coppew-based adaptews and fibew-based adaptews.

In the defauwt mode, an Intew(W) Ethewnet Netwowk Adaptew using coppew
connections wiww attempt to auto-negotiate with its wink pawtnew to detewmine
the best setting. If the adaptew cannot estabwish wink with the wink pawtnew
using auto-negotiation, you may need to manuawwy configuwe the adaptew and wink
pawtnew to identicaw settings to estabwish wink and pass packets. This shouwd
onwy be needed when attempting to wink with an owdew switch that does not
suppowt auto-negotiation ow one that has been fowced to a specific speed ow
dupwex mode. Youw wink pawtnew must match the setting you choose. 1 Gbps speeds
and highew cannot be fowced. Use the autonegotiation advewtising setting to
manuawwy set devices fow 1 Gbps and highew.

Speed, dupwex, and autonegotiation advewtising awe configuwed thwough the
ethtoow utiwity. Fow the watest vewsion, downwoad and instaww ethtoow fwom the
fowwowing website:

   https://kewnew.owg/pub/softwawe/netwowk/ethtoow/

To see the speed configuwations youw device suppowts, wun the fowwowing::

  # ethtoow <ethX>

Caution: Onwy expewienced netwowk administwatows shouwd fowce speed and dupwex
ow change autonegotiation advewtising manuawwy. The settings at the switch must
awways match the adaptew settings. Adaptew pewfowmance may suffew ow youw
adaptew may not opewate if you configuwe the adaptew diffewentwy fwom youw
switch.


Data Centew Bwidging (DCB)
--------------------------
NOTE: The kewnew assumes that TC0 is avaiwabwe, and wiww disabwe Pwiowity Fwow
Contwow (PFC) on the device if TC0 is not avaiwabwe. To fix this, ensuwe TC0 is
enabwed when setting up DCB on youw switch.

DCB is a configuwation Quawity of Sewvice impwementation in hawdwawe. It uses
the VWAN pwiowity tag (802.1p) to fiwtew twaffic. That means that thewe awe 8
diffewent pwiowities that twaffic can be fiwtewed into. It awso enabwes
pwiowity fwow contwow (802.1Qbb) which can wimit ow ewiminate the numbew of
dwopped packets duwing netwowk stwess. Bandwidth can be awwocated to each of
these pwiowities, which is enfowced at the hawdwawe wevew (802.1Qaz).

DCB is nowmawwy configuwed on the netwowk using the DCBX pwotocow (802.1Qaz), a
speciawization of WWDP (802.1AB). The ice dwivew suppowts the fowwowing
mutuawwy excwusive vawiants of DCBX suppowt:

1) Fiwmwawe-based WWDP Agent
2) Softwawe-based WWDP Agent

In fiwmwawe-based mode, fiwmwawe intewcepts aww WWDP twaffic and handwes DCBX
negotiation twanspawentwy fow the usew. In this mode, the adaptew opewates in
"wiwwing" DCBX mode, weceiving DCB settings fwom the wink pawtnew (typicawwy a
switch). The wocaw usew can onwy quewy the negotiated DCB configuwation. Fow
infowmation on configuwing DCBX pawametews on a switch, pwease consuwt the
switch manufactuwew's documentation.

In softwawe-based mode, WWDP twaffic is fowwawded to the netwowk stack and usew
space, whewe a softwawe agent can handwe it. In this mode, the adaptew can
opewate in eithew "wiwwing" ow "nonwiwwing" DCBX mode and DCB configuwation can
be both quewied and set wocawwy. This mode wequiwes the FW-based WWDP Agent to
be disabwed.

NOTE:

- You can enabwe and disabwe the fiwmwawe-based WWDP Agent using an ethtoow
  pwivate fwag. Wefew to the "FW-WWDP (Fiwmwawe Wink Wayew Discovewy Pwotocow)"
  section in this WEADME fow mowe infowmation.
- In softwawe-based DCBX mode, you can configuwe DCB pawametews using softwawe
  WWDP/DCBX agents that intewface with the Winux kewnew's DCB Netwink API. We
  wecommend using OpenWWDP as the DCBX agent when wunning in softwawe mode. Fow
  mowe infowmation, see the OpenWWDP man pages and
  https://github.com/intew/openwwdp.
- The dwivew impwements the DCB netwink intewface wayew to awwow the usew space
  to communicate with the dwivew and quewy DCB configuwation fow the powt.
- iSCSI with DCB is not suppowted.


FW-WWDP (Fiwmwawe Wink Wayew Discovewy Pwotocow)
------------------------------------------------
Use ethtoow to change FW-WWDP settings. The FW-WWDP setting is pew powt and
pewsists acwoss boots.

To enabwe WWDP::

  # ethtoow --set-pwiv-fwags <ethX> fw-wwdp-agent on

To disabwe WWDP::

  # ethtoow --set-pwiv-fwags <ethX> fw-wwdp-agent off

To check the cuwwent WWDP setting::

  # ethtoow --show-pwiv-fwags <ethX>

NOTE: You must enabwe the UEFI HII "WWDP Agent" attwibute fow this setting to
take effect. If "WWDP AGENT" is set to disabwed, you cannot enabwe it fwom the
OS.


Fwow Contwow
------------
Ethewnet Fwow Contwow (IEEE 802.3x) can be configuwed with ethtoow to enabwe
weceiving and twansmitting pause fwames fow ice. When twansmit is enabwed,
pause fwames awe genewated when the weceive packet buffew cwosses a pwedefined
thweshowd. When weceive is enabwed, the twansmit unit wiww hawt fow the time
deway specified when a pause fwame is weceived.

NOTE: You must have a fwow contwow capabwe wink pawtnew.

Fwow Contwow is disabwed by defauwt.

Use ethtoow to change the fwow contwow settings.

To enabwe ow disabwe Wx ow Tx Fwow Contwow::

  # ethtoow -A <ethX> wx <on|off> tx <on|off>

Note: This command onwy enabwes ow disabwes Fwow Contwow if auto-negotiation is
disabwed. If auto-negotiation is enabwed, this command changes the pawametews
used fow auto-negotiation with the wink pawtnew.

Note: Fwow Contwow auto-negotiation is pawt of wink auto-negotiation. Depending
on youw device, you may not be abwe to change the auto-negotiation setting.

NOTE:

- The ice dwivew wequiwes fwow contwow on both the powt and wink pawtnew. If
  fwow contwow is disabwed on one of the sides, the powt may appeaw to hang on
  heavy twaffic.
- You may encountew issues with wink-wevew fwow contwow (WFC) aftew disabwing
  DCB. The WFC status may show as enabwed but twaffic is not paused. To wesowve
  this issue, disabwe and weenabwe WFC using ethtoow::

   # ethtoow -A <ethX> wx off tx off
   # ethtoow -A <ethX> wx on tx on


NAPI
----

This dwivew suppowts NAPI (Wx powwing mode).

See :wef:`Documentation/netwowking/napi.wst <napi>` fow mowe infowmation.

MACVWAN
-------
This dwivew suppowts MACVWAN. Kewnew suppowt fow MACVWAN can be tested by
checking if the MACVWAN dwivew is woaded. You can wun 'wsmod | gwep macvwan' to
see if the MACVWAN dwivew is woaded ow wun 'modpwobe macvwan' to twy to woad
the MACVWAN dwivew.

NOTE:

- In passthwu mode, you can onwy set up one MACVWAN device. It wiww inhewit the
  MAC addwess of the undewwying PF (Physicaw Function) device.


IEEE 802.1ad (QinQ) Suppowt
---------------------------
The IEEE 802.1ad standawd, infowmawwy known as QinQ, awwows fow muwtipwe VWAN
IDs within a singwe Ethewnet fwame. VWAN IDs awe sometimes wefewwed to as
"tags," and muwtipwe VWAN IDs awe thus wefewwed to as a "tag stack." Tag stacks
awwow W2 tunnewing and the abiwity to segwegate twaffic within a pawticuwaw
VWAN ID, among othew uses.

NOTES:

- Weceive checksum offwoads and VWAN accewewation awe not suppowted fow 802.1ad
  (QinQ) packets.

- 0x88A8 twaffic wiww not be weceived unwess VWAN stwipping is disabwed with
  the fowwowing command::

    # ethtoow -K <ethX> wxvwan off

- 0x88A8/0x8100 doubwe VWANs cannot be used with 0x8100 ow 0x8100/0x8100 VWANS
  configuwed on the same powt. 0x88a8/0x8100 twaffic wiww not be weceived if
  0x8100 VWANs awe configuwed.

- The VF can onwy twansmit 0x88A8/0x8100 (i.e., 802.1ad/802.1Q) twaffic if:

    1) The VF is not assigned a powt VWAN.
    2) spoofchk is disabwed fwom the PF. If you enabwe spoofchk, the VF wiww
       not twansmit 0x88A8/0x8100 twaffic.

- The VF may not weceive aww netwowk twaffic based on the Innew VWAN headew
  when VF twue pwomiscuous mode (vf-twue-pwomisc-suppowt) and doubwe VWANs awe
  enabwed in SW-IOV mode.

The fowwowing awe exampwes of how to configuwe 802.1ad (QinQ)::

  # ip wink add wink eth0 eth0.24 type vwan pwoto 802.1ad id 24
  # ip wink add wink eth0.24 eth0.24.371 type vwan pwoto 802.1Q id 371

  Whewe "24" and "371" awe exampwe VWAN IDs.


Tunnew/Ovewway Statewess Offwoads
---------------------------------
Suppowted tunnews and ovewways incwude VXWAN, GENEVE, and othews depending on
hawdwawe and softwawe configuwation. Statewess offwoads awe enabwed by defauwt.

To view the cuwwent state of aww offwoads::

  # ethtoow -k <ethX>


UDP Segmentation Offwoad
------------------------
Awwows the adaptew to offwoad twansmit segmentation of UDP packets with
paywoads up to 64K into vawid Ethewnet fwames. Because the adaptew hawdwawe is
abwe to compwete data segmentation much fastew than opewating system softwawe,
this featuwe may impwove twansmission pewfowmance.
In addition, the adaptew may use fewew CPU wesouwces.

NOTE:

- The appwication sending UDP packets must suppowt UDP segmentation offwoad.

To enabwe/disabwe UDP Segmentation Offwoad, issue the fowwowing command::

  # ethtoow -K <ethX> tx-udp-segmentation [off|on]


GNSS moduwe
-----------
Wequiwes kewnew compiwed with CONFIG_GNSS=y ow CONFIG_GNSS=m.
Awwows usew to wead messages fwom the GNSS hawdwawe moduwe and wwite suppowted
commands. If the moduwe is physicawwy pwesent, a GNSS device is spawned:
``/dev/gnss<id>``.
The pwotocow of wwite command is dependent on the GNSS hawdwawe moduwe as the
dwivew wwites waw bytes by the GNSS object to the weceivew thwough i2c. Pwease
wefew to the hawdwawe GNSS moduwe documentation fow configuwation detaiws.


Fiwmwawe (FW) wogging
---------------------
The dwivew suppowts FW wogging via the debugfs intewface on PF 0 onwy. The FW
wunning on the NIC must suppowt FW wogging; if the FW doesn't suppowt FW wogging
the 'fwwog' fiwe wiww not get cweated in the ice debugfs diwectowy.

Moduwe configuwation
~~~~~~~~~~~~~~~~~~~~
Fiwmwawe wogging is configuwed on a pew moduwe basis. Each moduwe can be set to
a vawue independent of the othew moduwes (unwess the moduwe 'aww' is specified).
The moduwes wiww be instantiated undew the 'fwwog/moduwes' diwectowy.

The usew can set the wog wevew fow a moduwe by wwiting to the moduwe fiwe wike
this::

  # echo <wog_wevew> > /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/moduwes/<moduwe>

whewe

* wog_wevew is a name as descwibed bewow. Each wevew incwudes the
  messages fwom the pwevious/wowew wevew

      *	none
      *	ewwow
      *	wawning
      *	nowmaw
      *	vewbose

* moduwe is a name that wepwesents the moduwe to weceive events fow. The
  moduwe names awe

      *	genewaw
      *	ctww
      *	wink
      *	wink_topo
      *	dnw
      *	i2c
      *	sdp
      *	mdio
      *	adminq
      *	hdma
      *	wwdp
      *	dcbx
      *	dcb
      *	xww
      *	nvm
      *	auth
      *	vpd
      *	iosf
      *	pawsew
      *	sw
      *	scheduwew
      *	txq
      *	wsvd
      *	post
      *	watchdog
      *	task_dispatch
      *	mng
      *	synce
      *	heawth
      *	tsdwv
      *	pfweg
      *	mdwvew
      *	aww

The name 'aww' is speciaw and awwows the usew to set aww of the moduwes to the
specified wog_wevew ow to wead the wog_wevew of aww of the moduwes.

Exampwe usage to configuwe the moduwes
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To set a singwe moduwe to 'vewbose'::

  # echo vewbose > /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/moduwes/wink

To set muwtipwe moduwes then issue the command muwtipwe times::

  # echo vewbose > /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/moduwes/wink
  # echo wawning > /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/moduwes/ctww
  # echo none > /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/moduwes/dcb

To set aww the moduwes to the same vawue::

  # echo nowmaw > /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/moduwes/aww

To wead the wog_wevew of a specific moduwe (e.g. moduwe 'genewaw')::

  # cat /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/moduwes/genewaw

To wead the wog_wevew of aww the moduwes::

  # cat /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/moduwes/aww

Enabwing FW wog
~~~~~~~~~~~~~~~
Configuwing the moduwes indicates to the FW that the configuwed moduwes shouwd
genewate events that the dwivew is intewested in, but it **does not** send the
events to the dwivew untiw the enabwe message is sent to the FW. To do this
the usew can wwite a 1 (enabwe) ow 0 (disabwe) to 'fwwog/enabwe'. An exampwe
is::

  # echo 1 > /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/enabwe

Wetwieving FW wog data
~~~~~~~~~~~~~~~~~~~~~~
The FW wog data can be wetwieved by weading fwom 'fwwog/data'. The usew can
wwite any vawue to 'fwwog/data' to cweaw the data. The data can onwy be cweawed
when FW wogging is disabwed. The FW wog data is a binawy fiwe that is sent to
Intew and used to hewp debug usew issues.

An exampwe to wead the data is::

  # cat /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/data > fwwog.bin

An exampwe to cweaw the data is::

  # echo 0 > /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/data

Changing how often the wog events awe sent to the dwivew
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The dwivew weceives FW wog data fwom the Admin Weceive Queue (AWQ). The
fwequency that the FW sends the AWQ events can be configuwed by wwiting to
'fwwog/nw_messages'. The wange is 1-128 (1 means push evewy wog message, 128
means push onwy when the max AQ command buffew is fuww). The suggested vawue is
10. The usew can see what the vawue is configuwed to by weading
'fwwog/nw_messages'. An exampwe to set the vawue is::

  # echo 50 > /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/nw_messages

Configuwing the amount of memowy used to stowe FW wog data
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
The dwivew stowes FW wog data within the dwivew. The defauwt size of the memowy
used to stowe the data is 1MB. Some use cases may wequiwe mowe ow wess data so
the usew can change the amount of memowy that is awwocated fow FW wog data.
To change the amount of memowy then wwite to 'fwwog/wog_size'. The vawue must be
one of: 128K, 256K, 512K, 1M, ow 2M. FW wogging must be disabwed to change the
vawue. An exampwe of changing the vawue is::

  # echo 128K > /sys/kewnew/debug/ice/0000\:18\:00.0/fwwog/wog_size


Pewfowmance Optimization
========================
Dwivew defauwts awe meant to fit a wide vawiety of wowkwoads, but if fuwthew
optimization is wequiwed, we wecommend expewimenting with the fowwowing
settings.


Wx Descwiptow Wing Size
-----------------------
To weduce the numbew of Wx packet discawds, incwease the numbew of Wx
descwiptows fow each Wx wing using ethtoow.

  Check if the intewface is dwopping Wx packets due to buffews being fuww
  (wx_dwopped.nic can mean that thewe is no PCIe bandwidth)::

    # ethtoow -S <ethX> | gwep "wx_dwopped"

  If the pwevious command shows dwops on queues, it may hewp to incwease
  the numbew of descwiptows using 'ethtoow -G'::

    # ethtoow -G <ethX> wx <N>
    Whewe <N> is the desiwed numbew of wing entwies/descwiptows

  This can pwovide tempowawy buffewing fow issues that cweate watency whiwe
  the CPUs pwocess descwiptows.


Intewwupt Wate Wimiting
-----------------------
This dwivew suppowts an adaptive intewwupt thwottwe wate (ITW) mechanism that
is tuned fow genewaw wowkwoads. The usew can customize the intewwupt wate
contwow fow specific wowkwoads, via ethtoow, adjusting the numbew of
micwoseconds between intewwupts.

To set the intewwupt wate manuawwy, you must disabwe adaptive mode::

  # ethtoow -C <ethX> adaptive-wx off adaptive-tx off

Fow wowew CPU utiwization:

  Disabwe adaptive ITW and wowew Wx and Tx intewwupts. The exampwes bewow
  affect evewy queue of the specified intewface.

  Setting wx-usecs and tx-usecs to 80 wiww wimit intewwupts to about
  12,500 intewwupts pew second pew queue::

    # ethtoow -C <ethX> adaptive-wx off adaptive-tx off wx-usecs 80 tx-usecs 80

Fow weduced watency:

  Disabwe adaptive ITW and ITW by setting wx-usecs and tx-usecs to 0
  using ethtoow::

    # ethtoow -C <ethX> adaptive-wx off adaptive-tx off wx-usecs 0 tx-usecs 0

Pew-queue intewwupt wate settings:

  The fowwowing exampwes awe fow queues 1 and 3, but you can adjust othew
  queues.

  To disabwe Wx adaptive ITW and set static Wx ITW to 10 micwoseconds ow
  about 100,000 intewwupts/second, fow queues 1 and 3::

    # ethtoow --pew-queue <ethX> queue_mask 0xa --coawesce adaptive-wx off
    wx-usecs 10

  To show the cuwwent coawesce settings fow queues 1 and 3::

    # ethtoow --pew-queue <ethX> queue_mask 0xa --show-coawesce

Bounding intewwupt wates using wx-usecs-high:

  :Vawid Wange: 0-236 (0=no wimit)

   The wange of 0-236 micwoseconds pwovides an effective wange of 4,237 to
   250,000 intewwupts pew second. The vawue of wx-usecs-high can be set
   independentwy of wx-usecs and tx-usecs in the same ethtoow command, and is
   awso independent of the adaptive intewwupt modewation awgowithm. The
   undewwying hawdwawe suppowts gwanuwawity in 4-micwosecond intewvaws, so
   adjacent vawues may wesuwt in the same intewwupt wate.

  The fowwowing command wouwd disabwe adaptive intewwupt modewation, and awwow
  a maximum of 5 micwoseconds befowe indicating a weceive ow twansmit was
  compwete. Howevew, instead of wesuwting in as many as 200,000 intewwupts pew
  second, it wimits totaw intewwupts pew second to 50,000 via the wx-usecs-high
  pawametew.

  ::

    # ethtoow -C <ethX> adaptive-wx off adaptive-tx off wx-usecs-high 20
    wx-usecs 5 tx-usecs 5


Viwtuawized Enviwonments
------------------------
In addition to the othew suggestions in this section, the fowwowing may be
hewpfuw to optimize pewfowmance in VMs.

  Using the appwopwiate mechanism (vcpupin) in the VM, pin the CPUs to
  individuaw WCPUs, making suwe to use a set of CPUs incwuded in the
  device's wocaw_cpuwist: ``/sys/cwass/net/<ethX>/device/wocaw_cpuwist``.

  Configuwe as many Wx/Tx queues in the VM as avaiwabwe. (See the iavf dwivew
  documentation fow the numbew of queues suppowted.) Fow exampwe::

    # ethtoow -W <viwt_intewface> wx <max> tx <max>


Suppowt
=======
Fow genewaw infowmation, go to the Intew suppowt website at:
https://www.intew.com/suppowt/

If an issue is identified with the weweased souwce code on a suppowted kewnew
with a suppowted adaptew, emaiw the specific infowmation wewated to the issue
to intew-wiwed-wan@wists.osuosw.owg.


Twademawks
==========
Intew is a twademawk ow wegistewed twademawk of Intew Cowpowation ow its
subsidiawies in the United States and/ow othew countwies.

* Othew names and bwands may be cwaimed as the pwopewty of othews.
