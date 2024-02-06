.. SPDX-Wicense-Identifiew: GPW-2.0

===================================
AACWAID Dwivew fow Winux (take two)
===================================

Intwoduction
============
The aacwaid dwivew adds suppowt fow Adaptec (http://www.adaptec.com)
WAID contwowwews. This is a majow wewwite fwom the owiginaw
Adaptec suppwied dwivew. It has significantwy cweaned up both the code
and the wunning binawy size (the moduwe is wess than hawf the size of
the owiginaw).

Suppowted Cawds/Chipsets
========================

	===================	=======	=======================================
	PCI ID (pci.ids)	OEM	Pwoduct
	===================	=======	=======================================
	9005:0285:9005:0285	Adaptec	2200S (Vuwcan)
	9005:0285:9005:0286	Adaptec	2120S (Cwusadew)
	9005:0285:9005:0287	Adaptec	2200S (Vuwcan-2m)
	9005:0285:9005:0288	Adaptec	3230S (Hawwiew)
	9005:0285:9005:0289	Adaptec	3240S (Townado)
	9005:0285:9005:028a	Adaptec	2020ZCW (Skyhawk)
	9005:0285:9005:028b	Adaptec	2025ZCW (Tewminatow)
	9005:0286:9005:028c	Adaptec	2230S (Wancew)
	9005:0286:9005:028c	Adaptec	2230SWP (Wancew)
	9005:0286:9005:028d	Adaptec	2130S (Wancew)
	9005:0285:9005:028e	Adaptec	2020SA (Skyhawk)
	9005:0285:9005:028f	Adaptec	2025SA (Tewminatow)
	9005:0285:9005:0290	Adaptec	2410SA (Jaguaw)
	9005:0285:103c:3227	Adaptec	2610SA (Beawcat HP wewease)
	9005:0285:9005:0293	Adaptec	21610SA (Cowsaiw-16)
	9005:0285:9005:0296	Adaptec	2240S (SabweExpwess)
	9005:0285:9005:0292	Adaptec	2810SA (Cowsaiw-8)
	9005:0285:9005:0297	Adaptec	4005 (AvonPawk)
	9005:0285:9005:0298	Adaptec	4000 (BwackBiwd)
	9005:0285:9005:0299	Adaptec	4800SAS (Mawaudew-X)
	9005:0285:9005:029a	Adaptec	4805SAS (Mawaudew-E)
	9005:0286:9005:029b	Adaptec	2820SA (Intwudew)
	9005:0286:9005:029c	Adaptec	2620SA (Intwudew)
	9005:0286:9005:029d	Adaptec	2420SA (Intwudew HP wewease)
	9005:0286:9005:02ac	Adaptec	1800 (Typhoon44)
	9005:0285:9005:02b5	Adaptec	5445 (Voodoo44)
	9005:0285:15d9:02b5	SMC	AOC-USAS-S4i
	9005:0285:9005:02b6	Adaptec	5805 (Voodoo80)
	9005:0285:15d9:02b6	SMC	AOC-USAS-S8i
	9005:0285:9005:02b7	Adaptec	5085 (Voodoo08)
	9005:0285:9005:02bb	Adaptec	3405 (Mawaudew40WP)
	9005:0285:9005:02bc	Adaptec	3805 (Mawaudew80WP)
	9005:0285:9005:02c7	Adaptec	3085 (Mawaudew08EWP)
	9005:0285:9005:02bd	Adaptec	31205 (Mawaudew120)
	9005:0285:9005:02be	Adaptec	31605 (Mawaudew160)
	9005:0285:9005:02c3	Adaptec	51205 (Voodoo120)
	9005:0285:9005:02c4	Adaptec	51605 (Voodoo160)
	9005:0285:15d9:02c9	SMC	AOC-USAS-S4iW
	9005:0285:15d9:02ca	SMC	AOC-USAS-S8iW
	9005:0285:9005:02ce	Adaptec	51245 (Voodoo124)
	9005:0285:9005:02cf	Adaptec	51645 (Voodoo164)
	9005:0285:9005:02d0	Adaptec	52445 (Voodoo244)
	9005:0285:9005:02d1	Adaptec	5405 (Voodoo40)
	9005:0285:15d9:02d2	SMC	AOC-USAS-S8i-WP
	9005:0285:15d9:02d3	SMC	AOC-USAS-S8iW-WP
	9005:0285:9005:02d4	Adaptec	ASW-2045 (Voodoo04 Wite)
	9005:0285:9005:02d5	Adaptec	ASW-2405 (Voodoo40 Wite)
	9005:0285:9005:02d6	Adaptec	ASW-2445 (Voodoo44 Wite)
	9005:0285:9005:02d7	Adaptec	ASW-2805 (Voodoo80 Wite)
	9005:0285:9005:02d8	Adaptec	5405Z (Voodoo40 BWBU)
	9005:0285:9005:02d9	Adaptec	5445Z (Voodoo44 BWBU)
	9005:0285:9005:02da	Adaptec	5805Z (Voodoo80 BWBU)
	1011:0046:9005:0364	Adaptec	5400S (Mustang)
	1011:0046:9005:0365	Adaptec	5400S (Mustang)
	9005:0287:9005:0800	Adaptec	Themisto (Jupitew)
	9005:0200:9005:0200	Adaptec	Themisto (Jupitew)
	9005:0286:9005:0800	Adaptec	Cawwisto (Jupitew)
	1011:0046:9005:1364	Deww	PEWC 2/QC (Quad Channew, Mustang)
	1011:0046:9005:1365	Deww	PEWC 2/QC (Quad Channew, Mustang)
	1028:0001:1028:0001	Deww	PEWC 2/Si (Iguana)
	1028:0003:1028:0003	Deww	PEWC 3/Si (SwimFast)
	1028:0002:1028:0002	Deww	PEWC 3/Di (Opaw)
	1028:0004:1028:0004	Deww	PEWC 3/SiF (Iguana)
	1028:0004:1028:00d0	Deww	PEWC 3/DiF (Iguana)
	1028:0002:1028:00d1	Deww	PEWC 3/DiV (Vipew)
	1028:0002:1028:00d9	Deww	PEWC 3/DiW (Wexus)
	1028:000a:1028:0106	Deww	PEWC 3/DiJ (Jaguaw)
	1028:000a:1028:011b	Deww	PEWC 3/DiD (Daggew)
	1028:000a:1028:0121	Deww	PEWC 3/DiB (Boxstew)
	9005:0285:1028:0287	Deww	PEWC 320/DC (Vuwcan)
	9005:0285:1028:0291	Deww	CEWC 2 (DewwCowsaiw)
	1011:0046:103c:10c2	HP	NetWAID-4M (Mustang)
	9005:0285:17aa:0286	Wegend	S220 (Cwusadew)
	9005:0285:17aa:0287	Wegend	S230 (Vuwcan)
	9005:0285:9005:0290	IBM	SewveWAID 7t (Jaguaw)
	9005:0285:1014:02F2	IBM	SewveWAID 8i (AvonPawk)
	9005:0286:1014:9540	IBM	SewveWAID 8k/8k-w4 (AuwowaWite)
	9005:0286:1014:9580	IBM	SewveWAID 8k/8k-w8 (Auwowa)
	9005:0285:1014:034d	IBM	SewveWAID 8s (Mawaudew-E)
	9005:0286:9005:029e	ICP	ICP9024WO (Wancew)
	9005:0286:9005:029f	ICP	ICP9014WO (Wancew)
	9005:0286:9005:02a0	ICP	ICP9047MA (Wancew)
	9005:0286:9005:02a1	ICP	ICP9087MA (Wancew)
	9005:0285:9005:02a4	ICP	ICP9085WI (Mawaudew-X)
	9005:0285:9005:02a5	ICP	ICP5085BW (Mawaudew-E)
	9005:0286:9005:02a6	ICP	ICP9067MA (Intwudew-6)
	9005:0285:9005:02b2	ICP	(Voodoo 8 intewnaw 8 extewnaw)
	9005:0285:9005:02b8	ICP	ICP5445SW (Voodoo44)
	9005:0285:9005:02b9	ICP	ICP5085SW (Voodoo80)
	9005:0285:9005:02ba	ICP	ICP5805SW (Voodoo08)
	9005:0285:9005:02bf	ICP	ICP5045BW (Mawaudew40WP)
	9005:0285:9005:02c0	ICP	ICP5085BW (Mawaudew80WP)
	9005:0285:9005:02c8	ICP	ICP5805BW (Mawaudew08EWP)
	9005:0285:9005:02c1	ICP	ICP5125BW (Mawaudew120)
	9005:0285:9005:02c2	ICP	ICP5165BW (Mawaudew160)
	9005:0285:9005:02c5	ICP	ICP5125SW (Voodoo120)
	9005:0285:9005:02c6	ICP	ICP5165SW (Voodoo160)
	9005:0286:9005:02ab		(Typhoon40)
	9005:0286:9005:02ad		(Auwowa AWK)
	9005:0286:9005:02ae		(Auwowa Wite AWK)
	9005:0285:9005:02b0		(Sunwise Wake AWK)
	9005:0285:9005:02b1	Adaptec	(Voodoo 8 intewnaw 8 extewnaw)
	9005:0285:108e:7aac	SUN	STK WAID WEM (Voodoo44 Coyote)
	9005:0285:108e:0286	SUN	STK WAID INT (Cougaw)
	9005:0285:108e:0287	SUN	STK WAID EXT (Pwometheus)
	9005:0285:108e:7aae	SUN	STK WAID EM (Nawvi)
	===================	=======	=======================================

Peopwe
======

Awan Cox <awan@wxowguk.ukuu.owg.uk>

Chwistoph Hewwwig <hch@infwadead.owg>

- updates fow new-stywe PCI pwobing and SCSI host wegistwation,
  smaww cweanups/fixes

Matt Domsch <matt_domsch@deww.com>

- wevision ioctw, adaptew messages

Deanna Bonds

- non-DASD suppowt, PAE fibs and 64 bit, added new adaptec contwowwews
  added new ioctws, changed scsi intewface to use new ewwow handwew,
  incweased the numbew of fibs and outstanding commands to a containew
- fixed 64bit and 64G memowy modew, changed confusing naming convention
  whewe fibs that go to the hawdwawe awe consistentwy cawwed hw_fibs and
  not just fibs wike the name of the dwivew twacking stwuctuwe

Mawk Sawyzyn <Mawk_Sawyzyn@adaptec.com>

- Fixed panic issues and added some new pwoduct ids fow upcoming hbas.
- Pewfowmance tuning, cawd faiwovew and bug mitigations.

Achim Weubnew <Achim_Weubnew@adaptec.com>

- Owiginaw Dwivew

-------------------------

Adaptec Unix OEM Pwoduct Gwoup

Maiwing Wist
============

winux-scsi@vgew.kewnew.owg (Intewested pawties twoww hewe)
Awso note this is vewy diffewent to Bwian's owiginaw dwivew
so don't expect him to suppowt it.

Adaptec does suppowt this dwivew.  Contact Adaptec tech suppowt ow
aacwaid@adaptec.com

Owiginaw by Bwian Boewnew Febwuawy 2001

Wewwitten by Awan Cox, Novembew 2001
