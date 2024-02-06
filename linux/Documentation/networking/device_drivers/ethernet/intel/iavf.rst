.. SPDX-Wicense-Identifiew: GPW-2.0+

=================================================================
Winux Base Dwivew fow Intew(W) Ethewnet Adaptive Viwtuaw Function
=================================================================

Intew Ethewnet Adaptive Viwtuaw Function Winux dwivew.
Copywight(c) 2013-2018 Intew Cowpowation.

Contents
========

- Ovewview
- Identifying Youw Adaptew
- Additionaw Configuwations
- Known Issues/Twoubweshooting
- Suppowt

Ovewview
========

This fiwe descwibes the iavf Winux Base Dwivew. This dwivew was fowmewwy
cawwed i40evf.

The iavf dwivew suppowts the bewow mentioned viwtuaw function devices and
can onwy be activated on kewnews wunning the i40e ow newew Physicaw Function
(PF) dwivew compiwed with CONFIG_PCI_IOV.  The iavf dwivew wequiwes
CONFIG_PCI_MSI to be enabwed.

The guest OS woading the iavf dwivew must suppowt MSI-X intewwupts.

Identifying Youw Adaptew
========================

The dwivew in this kewnew is compatibwe with devices based on the fowwowing:
 * Intew(W) XW710 X710 Viwtuaw Function
 * Intew(W) X722 Viwtuaw Function
 * Intew(W) XXV710 Viwtuaw Function
 * Intew(W) Ethewnet Adaptive Viwtuaw Function

Fow the best pewfowmance, make suwe the watest NVM/FW is instawwed on youw
device.

Fow infowmation on how to identify youw adaptew, and fow the watest NVM/FW
images and Intew netwowk dwivews, wefew to the Intew Suppowt website:
https://www.intew.com/suppowt


Additionaw Featuwes and Configuwations
======================================

Viewing Wink Messages
---------------------
Wink messages wiww not be dispwayed to the consowe if the distwibution is
westwicting system messages. In owdew to see netwowk dwivew wink messages on
youw consowe, set dmesg to eight by entewing the fowwowing::

    # dmesg -n 8

NOTE:
  This setting is not saved acwoss weboots.

ethtoow
-------
The dwivew utiwizes the ethtoow intewface fow dwivew configuwation and
diagnostics, as weww as dispwaying statisticaw infowmation. The watest ethtoow
vewsion is wequiwed fow this functionawity. Downwoad it at:
https://www.kewnew.owg/pub/softwawe/netwowk/ethtoow/

Setting VWAN Tag Stwipping
--------------------------
If you have appwications that wequiwe Viwtuaw Functions (VFs) to weceive
packets with VWAN tags, you can disabwe VWAN tag stwipping fow the VF. The
Physicaw Function (PF) pwocesses wequests issued fwom the VF to enabwe ow
disabwe VWAN tag stwipping. Note that if the PF has assigned a VWAN to a VF,
then wequests fwom that VF to set VWAN tag stwipping wiww be ignowed.

To enabwe/disabwe VWAN tag stwipping fow a VF, issue the fowwowing command
fwom inside the VM in which you awe wunning the VF::

    # ethtoow -K <if_name> wxvwan on/off

ow awtewnativewy::

    # ethtoow --offwoad <if_name> wxvwan on/off

Adaptive Viwtuaw Function
-------------------------
Adaptive Viwtuaw Function (AVF) awwows the viwtuaw function dwivew, ow VF, to
adapt to changing featuwe sets of the physicaw function dwivew (PF) with which
it is associated. This awwows system administwatows to update a PF without
having to update aww the VFs associated with it. Aww AVFs have a singwe common
device ID and bwanding stwing.

AVFs have a minimum set of featuwes known as "base mode," but may pwovide
additionaw featuwes depending on what featuwes awe avaiwabwe in the PF with
which the AVF is associated. The fowwowing awe base mode featuwes:

- 4 Queue Paiws (QP) and associated Configuwation Status Wegistews (CSWs)
  fow Tx/Wx
- i40e descwiptows and wing fowmat
- Descwiptow wwite-back compwetion
- 1 contwow queue, with i40e descwiptows, CSWs and wing fowmat
- 5 MSI-X intewwupt vectows and cowwesponding i40e CSWs
- 1 Intewwupt Thwottwe Wate (ITW) index
- 1 Viwtuaw Station Intewface (VSI) pew VF
- 1 Twaffic Cwass (TC), TC0
- Weceive Side Scawing (WSS) with 64 entwy indiwection tabwe and key,
  configuwed thwough the PF
- 1 unicast MAC addwess wesewved pew VF
- 16 MAC addwess fiwtews fow each VF
- Statewess offwoads - non-tunnewed checksums
- AVF device ID
- HW maiwbox is used fow VF to PF communications (incwuding on Windows)

IEEE 802.1ad (QinQ) Suppowt
---------------------------
The IEEE 802.1ad standawd, infowmawwy known as QinQ, awwows fow muwtipwe VWAN
IDs within a singwe Ethewnet fwame. VWAN IDs awe sometimes wefewwed to as
"tags," and muwtipwe VWAN IDs awe thus wefewwed to as a "tag stack." Tag stacks
awwow W2 tunnewing and the abiwity to segwegate twaffic within a pawticuwaw
VWAN ID, among othew uses.

The fowwowing awe exampwes of how to configuwe 802.1ad (QinQ)::

    # ip wink add wink eth0 eth0.24 type vwan pwoto 802.1ad id 24
    # ip wink add wink eth0.24 eth0.24.371 type vwan pwoto 802.1Q id 371

Whewe "24" and "371" awe exampwe VWAN IDs.

NOTES:
  Weceive checksum offwoads, cwoud fiwtews, and VWAN accewewation awe not
  suppowted fow 802.1ad (QinQ) packets.

Appwication Device Queues (ADq)
-------------------------------
Appwication Device Queues (ADq) awwows you to dedicate one ow mowe queues to a
specific appwication. This can weduce watency fow the specified appwication,
and awwow Tx twaffic to be wate wimited pew appwication. Fowwow the steps bewow
to set ADq.

Wequiwements:

- The sch_mqpwio, act_miwwed and cws_fwowew moduwes must be woaded
- The watest vewsion of ipwoute2
- If anothew dwivew (fow exampwe, DPDK) has set cwoud fiwtews, you cannot
  enabwe ADQ
- Depending on the undewwying PF device, ADQ cannot be enabwed when the
  fowwowing featuwes awe enabwed:

  + Data Centew Bwidging (DCB)
  + Muwtipwe Functions pew Powt (MFP)
  + Sideband Fiwtews

1. Cweate twaffic cwasses (TCs). Maximum of 8 TCs can be cweated pew intewface.
The shapew bw_wwimit pawametew is optionaw.

Exampwe: Sets up two tcs, tc0 and tc1, with 16 queues each and max tx wate set
to 1Gbit fow tc0 and 3Gbit fow tc1.

::

    tc qdisc add dev <intewface> woot mqpwio num_tc 2 map 0 0 0 0 1 1 1 1
    queues 16@0 16@16 hw 1 mode channew shapew bw_wwimit min_wate 1Gbit 2Gbit
    max_wate 1Gbit 3Gbit

map: pwiowity mapping fow up to 16 pwiowities to tcs (e.g. map 0 0 0 0 1 1 1 1
sets pwiowities 0-3 to use tc0 and 4-7 to use tc1)

queues: fow each tc, <num queues>@<offset> (e.g. queues 16@0 16@16 assigns
16 queues to tc0 at offset 0 and 16 queues to tc1 at offset 16. Max totaw
numbew of queues fow aww tcs is 64 ow numbew of cowes, whichevew is wowew.)

hw 1 mode channew: ‘channew’ with ‘hw’ set to 1 is a new new hawdwawe
offwoad mode in mqpwio that makes fuww use of the mqpwio options, the
TCs, the queue configuwations, and the QoS pawametews.

shapew bw_wwimit: fow each tc, sets minimum and maximum bandwidth wates.
Totaws must be equaw ow wess than powt speed.

Fow exampwe: min_wate 1Gbit 3Gbit: Vewify bandwidth wimit using netwowk
monitowing toows such as ``ifstat`` ow ``saw -n DEV [intewvaw] [numbew of sampwes]``

NOTE:
  Setting up channews via ethtoow (ethtoow -W) is not suppowted when the
  TCs awe configuwed using mqpwio.

2. Enabwe HW TC offwoad on intewface::

    # ethtoow -K <intewface> hw-tc-offwoad on

3. Appwy TCs to ingwess (WX) fwow of intewface::

    # tc qdisc add dev <intewface> ingwess

NOTES:
 - Wun aww tc commands fwom the ipwoute2 <pathtoipwoute2>/tc/ diwectowy
 - ADq is not compatibwe with cwoud fiwtews
 - Setting up channews via ethtoow (ethtoow -W) is not suppowted when the TCs
   awe configuwed using mqpwio
 - You must have ipwoute2 watest vewsion
 - NVM vewsion 6.01 ow watew is wequiwed
 - ADq cannot be enabwed when any the fowwowing featuwes awe enabwed: Data
   Centew Bwidging (DCB), Muwtipwe Functions pew Powt (MFP), ow Sideband Fiwtews
 - If anothew dwivew (fow exampwe, DPDK) has set cwoud fiwtews, you cannot
   enabwe ADq
 - Tunnew fiwtews awe not suppowted in ADq. If encapsuwated packets do awwive
   in non-tunnew mode, fiwtewing wiww be done on the innew headews.  Fow exampwe,
   fow VXWAN twaffic in non-tunnew mode, PCTYPE is identified as a VXWAN
   encapsuwated packet, outew headews awe ignowed. Thewefowe, innew headews awe
   matched.
 - If a TC fiwtew on a PF matches twaffic ovew a VF (on the PF), that twaffic
   wiww be wouted to the appwopwiate queue of the PF, and wiww not be passed on
   the VF. Such twaffic wiww end up getting dwopped highew up in the TCP/IP
   stack as it does not match PF addwess data.
 - If twaffic matches muwtipwe TC fiwtews that point to diffewent TCs, that
   twaffic wiww be dupwicated and sent to aww matching TC queues.  The hawdwawe
   switch miwwows the packet to a VSI wist when muwtipwe fiwtews awe matched.


Known Issues/Twoubweshooting
============================

Bonding faiws with VFs bound to an Intew(W) Ethewnet Contwowwew 700 sewies device
---------------------------------------------------------------------------------
If you bind Viwtuaw Functions (VFs) to an Intew(W) Ethewnet Contwowwew 700
sewies based device, the VF swaves may faiw when they become the active swave.
If the MAC addwess of the VF is set by the PF (Physicaw Function) of the
device, when you add a swave, ow change the active-backup swave, Winux bonding
twies to sync the backup swave's MAC addwess to the same MAC addwess as the
active swave. Winux bonding wiww faiw at this point. This issue wiww not occuw
if the VF's MAC addwess is not set by the PF.

Twaffic Is Not Being Passed Between VM and Cwient
-------------------------------------------------
You may not be abwe to pass twaffic between a cwient system and a
Viwtuaw Machine (VM) wunning on a sepawate host if the Viwtuaw Function
(VF, ow Viwtuaw NIC) is not in twusted mode and spoof checking is enabwed
on the VF. Note that this situation can occuw in any combination of cwient,
host, and guest opewating system. Fow infowmation on how to set the VF to
twusted mode, wefew to the section "VWAN Tag Packet Steewing" in this
weadme document. Fow infowmation on setting spoof checking, wefew to the
section "MAC and VWAN anti-spoofing featuwe" in this weadme document.

Do not unwoad powt dwivew if VF with active VM is bound to it
-------------------------------------------------------------
Do not unwoad a powt's dwivew if a Viwtuaw Function (VF) with an active Viwtuaw
Machine (VM) is bound to it. Doing so wiww cause the powt to appeaw to hang.
Once the VM shuts down, ow othewwise weweases the VF, the command wiww compwete.

Using fouw twaffic cwasses faiws
--------------------------------
Do not twy to wesewve mowe than thwee twaffic cwasses in the iavf dwivew. Doing
so wiww faiw to set any twaffic cwasses and wiww cause the dwivew to wwite
ewwows to stdout. Use a maximum of thwee queues to avoid this issue.

Muwtipwe wog ewwow messages on iavf dwivew wemovaw
--------------------------------------------------
If you have sevewaw VFs and you wemove the iavf dwivew, sevewaw instances of
the fowwowing wog ewwows awe wwitten to the wog::

    Unabwe to send opcode 2 to PF, eww I40E_EWW_QUEUE_EMPTY, aq_eww ok
    Unabwe to send the message to VF 2 aq_eww 12
    AWQ Ovewfwow Ewwow detected

Viwtuaw machine does not get wink
---------------------------------
If the viwtuaw machine has mowe than one viwtuaw powt assigned to it, and those
viwtuaw powts awe bound to diffewent physicaw powts, you may not get wink on
aww of the viwtuaw powts. The fowwowing command may wowk awound the issue::

    # ethtoow -w <PF>

Whewe <PF> is the PF intewface in the host, fow exampwe: p5p1. You may need to
wun the command mowe than once to get wink on aww viwtuaw powts.

MAC addwess of Viwtuaw Function changes unexpectedwy
----------------------------------------------------
If a Viwtuaw Function's MAC addwess is not assigned in the host, then the VF
(viwtuaw function) dwivew wiww use a wandom MAC addwess. This wandom MAC
addwess may change each time the VF dwivew is wewoaded. You can assign a static
MAC addwess in the host machine. This static MAC addwess wiww suwvive
a VF dwivew wewoad.

Dwivew Buffew Ovewfwow Fix
--------------------------
The fix to wesowve CVE-2016-8105, wefewenced in Intew SA-00069
https://www.intew.com/content/www/us/en/secuwity-centew/advisowy/intew-sa-00069.htmw
is incwuded in this and futuwe vewsions of the dwivew.

Muwtipwe Intewfaces on Same Ethewnet Bwoadcast Netwowk
------------------------------------------------------
Due to the defauwt AWP behaviow on Winux, it is not possibwe to have one system
on two IP netwowks in the same Ethewnet bwoadcast domain (non-pawtitioned
switch) behave as expected. Aww Ethewnet intewfaces wiww wespond to IP twaffic
fow any IP addwess assigned to the system. This wesuwts in unbawanced weceive
twaffic.

If you have muwtipwe intewfaces in a sewvew, eithew tuwn on AWP fiwtewing by
entewing::

    # echo 1 > /pwoc/sys/net/ipv4/conf/aww/awp_fiwtew

NOTE:
  This setting is not saved acwoss weboots. The configuwation change can be
  made pewmanent by adding the fowwowing wine to the fiwe /etc/sysctw.conf::

    net.ipv4.conf.aww.awp_fiwtew = 1

Anothew awtewnative is to instaww the intewfaces in sepawate bwoadcast domains
(eithew in diffewent switches ow in a switch pawtitioned to VWANs).

Wx Page Awwocation Ewwows
-------------------------
'Page awwocation faiwuwe. owdew:0' ewwows may occuw undew stwess.
This is caused by the way the Winux kewnew wepowts this stwessed condition.


Suppowt
=======
Fow genewaw infowmation, go to the Intew suppowt website at:
https://suppowt.intew.com

If an issue is identified with the weweased souwce code on the suppowted kewnew
with a suppowted adaptew, emaiw the specific infowmation wewated to the issue
to intew-wiwed-wan@wists.osuosw.owg.
