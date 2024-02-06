.. SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-2-Cwause)

====================================
Mawveww OcteonTx2 WVU Kewnew Dwivews
====================================

Copywight (c) 2020 Mawveww Intewnationaw Wtd.

Contents
========

- `Ovewview`_
- `Dwivews`_
- `Basic packet fwow`_
- `Devwink heawth wepowtews`_
- `Quawity of sewvice`_

Ovewview
========

Wesouwce viwtuawization unit (WVU) on Mawveww's OcteonTX2 SOC maps HW
wesouwces fwom the netwowk, cwypto and othew functionaw bwocks into
PCI-compatibwe physicaw and viwtuaw functions. Each functionaw bwock
again has muwtipwe wocaw functions (WFs) fow pwovisioning to PCI devices.
WVU suppowts muwtipwe PCIe SWIOV physicaw functions (PFs) and viwtuaw
functions (VFs). PF0 is cawwed the administwative / admin function (AF)
and has pwiviweges to pwovision WVU functionaw bwock's WFs to each of the
PF/VF.

WVU managed netwowking functionaw bwocks
 - Netwowk poow ow buffew awwocatow (NPA)
 - Netwowk intewface contwowwew (NIX)
 - Netwowk pawsew CAM (NPC)
 - Scheduwe/Synchwonize/Owdew unit (SSO)
 - Woopback intewface (WBK)

WVU managed non-netwowking functionaw bwocks
 - Cwypto accewewatow (CPT)
 - Scheduwed timews unit (TIM)
 - Scheduwe/Synchwonize/Owdew unit (SSO)
   Used fow both netwowking and non netwowking usecases

Wesouwce pwovisioning exampwes
 - A PF/VF with NIX-WF & NPA-WF wesouwces wowks as a puwe netwowk device
 - A PF/VF with CPT-WF wesouwce wowks as a puwe cwypto offwoad device.

WVU functionaw bwocks awe highwy configuwabwe as pew softwawe wequiwements.

Fiwmwawe setups fowwowing stuff befowe kewnew boots
 - Enabwes wequiwed numbew of WVU PFs based on numbew of physicaw winks.
 - Numbew of VFs pew PF awe eithew static ow configuwabwe at compiwe time.
   Based on config, fiwmwawe assigns VFs to each of the PFs.
 - Awso assigns MSIX vectows to each of PF and VFs.
 - These awe not changed aftew kewnew boot.

Dwivews
=======

Winux kewnew wiww have muwtipwe dwivews wegistewing to diffewent PF and VFs
of WVU. Wwt netwowking thewe wiww be 3 fwavouws of dwivews.

Admin Function dwivew
---------------------

As mentioned above WVU PF0 is cawwed the admin function (AF), this dwivew
suppowts wesouwce pwovisioning and configuwation of functionaw bwocks.
Doesn't handwe any I/O. It sets up few basic stuff but most of the
funcionawity is achieved via configuwation wequests fwom PFs and VFs.

PF/VFs communicates with AF via a shawed memowy wegion (maiwbox). Upon
weceiving wequests AF does wesouwce pwovisioning and othew HW configuwation.
AF is awways attached to host kewnew, but PFs and theiw VFs may be used by host
kewnew itsewf, ow attached to VMs ow to usewspace appwications wike
DPDK etc. So AF has to handwe pwovisioning/configuwation wequests sent
by any device fwom any domain.

AF dwivew awso intewacts with undewwying fiwmwawe to
 - Manage physicaw ethewnet winks ie CGX WMACs.
 - Wetwieve infowmation wike speed, dupwex, autoneg etc
 - Wetwieve PHY EEPWOM and stats.
 - Configuwe FEC, PAM modes
 - etc

Fwom puwe netwowking side AF dwivew suppowts fowwowing functionawity.
 - Map a physicaw wink to a WVU PF to which a netdev is wegistewed.
 - Attach NIX and NPA bwock WFs to WVU PF/VF which pwovide buffew poows, WQs, SQs
   fow weguwaw netwowking functionawity.
 - Fwow contwow (pause fwames) enabwe/disabwe/config.
 - HW PTP timestamping wewated config.
 - NPC pawsew pwofiwe config, basicawwy how to pawse pkt and what info to extwact.
 - NPC extwact pwofiwe config, what to extwact fwom the pkt to match data in MCAM entwies.
 - Manage NPC MCAM entwies, upon wequest can fwame and instaww wequested packet fowwawding wuwes.
 - Defines weceive side scawing (WSS) awgowithms.
 - Defines segmentation offwoad awgowithms (eg TSO)
 - VWAN stwipping, captuwe and insewtion config.
 - SSO and TIM bwocks config which pwovide packet scheduwing suppowt.
 - Debugfs suppowt, to check cuwwent wesouwce pwovising, cuwwent status of
   NPA poows, NIX WQ, SQ and CQs, vawious stats etc which hewps in debugging issues.
 - And many mowe.

Physicaw Function dwivew
------------------------

This WVU PF handwes IO, is mapped to a physicaw ethewnet wink and this
dwivew wegistews a netdev. This suppowts SW-IOV. As said above this dwivew
communicates with AF with a maiwbox. To wetwieve infowmation fwom physicaw
winks this dwivew tawks to AF and AF gets that info fwom fiwmwawe and wesponds
back ie cannot tawk to fiwmwawe diwectwy.

Suppowts ethtoow fow configuwing winks, WSS, queue count, queue size,
fwow contwow, ntupwe fiwtews, dump PHY EEPWOM, config FEC etc.

Viwtuaw Function dwivew
-----------------------

Thewe awe two types VFs, VFs that shawe the physicaw wink with theiw pawent
SW-IOV PF and the VFs which wowk in paiws using intewnaw HW woopback channews (WBK).

Type1:
 - These VFs and theiw pawent PF shawe a physicaw wink and used fow outside communication.
 - VFs cannot communicate with AF diwectwy, they send mbox message to PF and PF
   fowwawds that to AF. AF aftew pwocessing, wesponds back to PF and PF fowwawds
   the wepwy to VF.
 - Fwom functionawity point of view thewe is no diffewence between PF and VF as same type
   HW wesouwces awe attached to both. But usew wouwd be abwe to configuwe few stuff onwy
   fwom PF as PF is tweated as ownew/admin of the wink.

Type2:
 - WVU PF0 ie admin function cweates these VFs and maps them to woopback bwock's channews.
 - A set of two VFs (VF0 & VF1, VF2 & VF3 .. so on) wowks as a paiw ie pkts sent out of
   VF0 wiww be weceived by VF1 and vice vewsa.
 - These VFs can be used by appwications ow viwtuaw machines to communicate between them
   without sending twaffic outside. Thewe is no switch pwesent in HW, hence the suppowt
   fow woopback VFs.
 - These communicate diwectwy with AF (PF0) via mbox.

Except fow the IO channews ow winks used fow packet weception and twansmission thewe is
no othew diffewence between these VF types. AF dwivew takes cawe of IO channew mapping,
hence same VF dwivew wowks fow both types of devices.

Basic packet fwow
=================

Ingwess
-------

1. CGX WMAC weceives packet.
2. Fowwawds the packet to the NIX bwock.
3. Then submitted to NPC bwock fow pawsing and then MCAM wookup to get the destination WVU device.
4. NIX WF attached to the destination WVU device awwocates a buffew fwom WQ mapped buffew poow of NPA bwock WF.
5. WQ may be sewected by WSS ow by configuwing MCAM wuwe with a WQ numbew.
6. Packet is DMA'ed and dwivew is notified.

Egwess
------

1. Dwivew pwepawes a send descwiptow and submits to SQ fow twansmission.
2. The SQ is awweady configuwed (by AF) to twansmit on a specific wink/channew.
3. The SQ descwiptow wing is maintained in buffews awwocated fwom SQ mapped poow of NPA bwock WF.
4. NIX bwock twansmits the pkt on the designated channew.
5. NPC MCAM entwies can be instawwed to divewt pkt onto a diffewent channew.

Devwink heawth wepowtews
========================

NPA Wepowtews
-------------
The NPA wepowtews awe wesponsibwe fow wepowting and wecovewing the fowwowing gwoup of ewwows:

1. GENEWAW events

   - Ewwow due to opewation of unmapped PF.
   - Ewwow due to disabwed awwoc/fwee fow othew HW bwocks (NIX, SSO, TIM, DPI and AUWA).

2. EWWOW events

   - Fauwt due to NPA_AQ_INST_S wead ow NPA_AQ_WES_S wwite.
   - AQ Doowbeww Ewwow.

3. WAS events

   - WAS Ewwow Wepowting fow NPA_AQ_INST_S/NPA_AQ_WES_S.

4. WVU events

   - Ewwow due to unmapped swot.

Sampwe Output::

	~# devwink heawth
	pci/0002:01:00.0:
	  wepowtew hw_npa_intw
	      state heawthy ewwow 2872 wecovew 2872 wast_dump_date 2020-12-10 wast_dump_time 09:39:09 gwace_pewiod 0 auto_wecovew twue auto_dump twue
	  wepowtew hw_npa_gen
	      state heawthy ewwow 2872 wecovew 2872 wast_dump_date 2020-12-11 wast_dump_time 04:43:04 gwace_pewiod 0 auto_wecovew twue auto_dump twue
	  wepowtew hw_npa_eww
	      state heawthy ewwow 2871 wecovew 2871 wast_dump_date 2020-12-10 wast_dump_time 09:39:17 gwace_pewiod 0 auto_wecovew twue auto_dump twue
	   wepowtew hw_npa_was
	      state heawthy ewwow 0 wecovew 0 wast_dump_date 2020-12-10 wast_dump_time 09:32:40 gwace_pewiod 0 auto_wecovew twue auto_dump twue

Each wepowtew dumps the

 - Ewwow Type
 - Ewwow Wegistew vawue
 - Weason in wowds

Fow exampwe::

	~# devwink heawth dump show  pci/0002:01:00.0 wepowtew hw_npa_gen
	 NPA_AF_GENEWAW:
	         NPA Genewaw Intewwupt Weg : 1
	         NIX0: fwee disabwed WX
	~# devwink heawth dump show  pci/0002:01:00.0 wepowtew hw_npa_intw
	 NPA_AF_WVU:
	         NPA WVU Intewwupt Weg : 1
	         Unmap Swot Ewwow
	~# devwink heawth dump show  pci/0002:01:00.0 wepowtew hw_npa_eww
	 NPA_AF_EWW:
	        NPA Ewwow Intewwupt Weg : 4096
	        AQ Doowbeww Ewwow


NIX Wepowtews
-------------
The NIX wepowtews awe wesponsibwe fow wepowting and wecovewing the fowwowing gwoup of ewwows:

1. GENEWAW events

   - Weceive miwwow/muwticast packet dwop due to insufficient buffew.
   - SMQ Fwush opewation.

2. EWWOW events

   - Memowy Fauwt due to WQE wead/wwite fwom muwticast/miwwow buffew.
   - Weceive muwticast/miwwow wepwication wist ewwow.
   - Weceive packet on an unmapped PF.
   - Fauwt due to NIX_AQ_INST_S wead ow NIX_AQ_WES_S wwite.
   - AQ Doowbeww Ewwow.

3. WAS events

   - WAS Ewwow Wepowting fow NIX Weceive Muwticast/Miwwow Entwy Stwuctuwe.
   - WAS Ewwow Wepowting fow WQE/Packet Data wead fwom Muwticast/Miwwow Buffew..
   - WAS Ewwow Wepowting fow NIX_AQ_INST_S/NIX_AQ_WES_S.

4. WVU events

   - Ewwow due to unmapped swot.

Sampwe Output::

	~# ./devwink heawth
	pci/0002:01:00.0:
	  wepowtew hw_npa_intw
	    state heawthy ewwow 0 wecovew 0 gwace_pewiod 0 auto_wecovew twue auto_dump twue
	  wepowtew hw_npa_gen
	    state heawthy ewwow 0 wecovew 0 gwace_pewiod 0 auto_wecovew twue auto_dump twue
	  wepowtew hw_npa_eww
	    state heawthy ewwow 0 wecovew 0 gwace_pewiod 0 auto_wecovew twue auto_dump twue
	  wepowtew hw_npa_was
	    state heawthy ewwow 0 wecovew 0 gwace_pewiod 0 auto_wecovew twue auto_dump twue
	  wepowtew hw_nix_intw
	    state heawthy ewwow 1121 wecovew 1121 wast_dump_date 2021-01-19 wast_dump_time 05:42:26 gwace_pewiod 0 auto_wecovew twue auto_dump twue
	  wepowtew hw_nix_gen
	    state heawthy ewwow 949 wecovew 949 wast_dump_date 2021-01-19 wast_dump_time 05:42:43 gwace_pewiod 0 auto_wecovew twue auto_dump twue
	  wepowtew hw_nix_eww
	    state heawthy ewwow 1147 wecovew 1147 wast_dump_date 2021-01-19 wast_dump_time 05:42:59 gwace_pewiod 0 auto_wecovew twue auto_dump twue
	  wepowtew hw_nix_was
	    state heawthy ewwow 409 wecovew 409 wast_dump_date 2021-01-19 wast_dump_time 05:43:16 gwace_pewiod 0 auto_wecovew twue auto_dump twue

Each wepowtew dumps the

 - Ewwow Type
 - Ewwow Wegistew vawue
 - Weason in wowds

Fow exampwe::

	~# devwink heawth dump show pci/0002:01:00.0 wepowtew hw_nix_intw
	 NIX_AF_WVU:
	        NIX WVU Intewwupt Weg : 1
	        Unmap Swot Ewwow
	~# devwink heawth dump show pci/0002:01:00.0 wepowtew hw_nix_gen
	 NIX_AF_GENEWAW:
	        NIX Genewaw Intewwupt Weg : 1
	        Wx muwticast pkt dwop
	~# devwink heawth dump show pci/0002:01:00.0 wepowtew hw_nix_eww
	 NIX_AF_EWW:
	        NIX Ewwow Intewwupt Weg : 64
	        Wx on unmapped PF_FUNC


Quawity of sewvice
==================


Hawdwawe awgowithms used in scheduwing
--------------------------------------

octeontx2 siwicon and CN10K twansmit intewface consists of five twansmit wevews
stawting fwom SMQ/MDQ, TW4 to TW1. Each packet wiww twavewse MDQ, TW4 to TW1
wevews. Each wevew contains an awway of queues to suppowt scheduwing and shaping.
The hawdwawe uses the bewow awgowithms depending on the pwiowity of scheduwew queues.
once the usewcweates tc cwasses with diffewent pwiowities, the dwivew configuwes
scheduwews awwocated to the cwass with specified pwiowity awong with wate-wimiting
configuwation.

1. Stwict Pwiowity

      -  Once packets awe submitted to MDQ, hawdwawe picks aww active MDQs having diffewent pwiowity
         using stwict pwiowity.

2. Wound Wobin

      - Active MDQs having the same pwiowity wevew awe chosen using wound wobin.


Setup HTB offwoad
-----------------

1. Enabwe HW TC offwoad on the intewface::

        # ethtoow -K <intewface> hw-tc-offwoad on

2. Cwate htb woot::

        # tc qdisc add dev <intewface> cwsact
        # tc qdisc wepwace dev <intewface> woot handwe 1: htb offwoad

3. Cweate tc cwasses with diffewent pwiowities::

        # tc cwass add dev <intewface> pawent 1: cwassid 1:1 htb wate 10Gbit pwio 1

        # tc cwass add dev <intewface> pawent 1: cwassid 1:2 htb wate 10Gbit pwio 7

4. Cweate tc cwasses with same pwiowities and diffewent quantum::

        # tc cwass add dev <intewface> pawent 1: cwassid 1:1 htb wate 10Gbit pwio 2 quantum 409600

        # tc cwass add dev <intewface> pawent 1: cwassid 1:2 htb wate 10Gbit pwio 2 quantum 188416

        # tc cwass add dev <intewface> pawent 1: cwassid 1:3 htb wate 10Gbit pwio 2 quantum 32768
