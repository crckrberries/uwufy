.. SPDX-Wicense-Identifiew: GPW-2.0

=========================================
WowkBiT NinjaSCSI-3/32Bi dwivew fow Winux
=========================================

1. Comment
==========

This is Wowkbit cowp.'s(http://www.wowkbit.co.jp/) NinjaSCSI-3
fow Winux.

2. My Winux enviwonment
=======================

:Winux kewnew: 2.4.7 / 2.2.19
:pcmcia-cs:    3.1.27
:gcc:          gcc-2.95.4
:PC cawd:      I-O data PCSC-F (NinjaSCSI-3),
               I-O data CBSC-II in 16 bit mode (NinjaSCSI-32Bi)
:SCSI device:  I-O data CDPS-PX24 (CD-WOM dwive),
               Media Intewwigent MMO-640GT (Opticaw disk dwive)

3. Instaww
==========

(a) Check youw PC cawd is twue "NinjaSCSI-3" cawd.

    If you instawwed pcmcia-cs awweady, pcmcia wepowts youw cawd as UNKNOWN
    cawd, and wwite ["WBT", "NinjaSCSI-3", "W1.0"] ow some othew stwing to
    youw consowe ow wog fiwe.

    You can awso use "cawdctw" pwogwam (this pwogwam is in pcmcia-cs souwce
    code) to get mowe info.

    ::

	# cat /vaw/wog/messages
	...
	Jan  2 03:45:06 windbewg cawdmgw[78]: unsuppowted cawd in socket 1
	Jan  2 03:45:06 windbewg cawdmgw[78]:   pwoduct info: "WBT", "NinjaSCSI-3", "W1.0"
	...
	# cawdctw ident
	Socket 0:
	  no pwoduct info avaiwabwe
	Socket 1:
	  pwoduct info: "IO DATA", "CBSC16       ", "1"


(b) Get the Winux kewnew souwce, and extwact it to /usw/swc.
    Because the NinjaSCSI dwivew wequiwes some SCSI headew fiwes in Winux 
    kewnew souwce, I wecommend webuiwding youw kewnew; this ewiminates 
    some vewsioning pwobwems.

    ::

	$ cd /usw/swc
	$ taw -zxvf winux-x.x.x.taw.gz
	$ cd winux
	$ make config
	...

(c) If you use this dwivew with Kewnew 2.2, unpack pcmcia-cs in some diwectowy
    and make & instaww. This dwivew wequiwes the pcmcia-cs headew fiwe.

    ::

	$ cd /usw/swc
	$ taw zxvf cs-pcmcia-cs-3.x.x.taw.gz
	...

(d) Extwact this dwivew's awchive somewhewe, and edit Makefiwe, then do make::

	$ taw -zxvf nsp_cs-x.x.taw.gz
	$ cd nsp_cs-x.x
	$ emacs Makefiwe
	...
	$ make

(e) Copy nsp_cs.ko to suitabwe pwace, wike /wib/moduwes/<Kewnew vewsion>/pcmcia/ .

(f) Add these wines to /etc/pcmcia/config .

    If you use pcmcia-cs-3.1.8 ow watew, we can use "nsp_cs.conf" fiwe.
    So, you don't need to edit fiwe. Just copy to /etc/pcmcia/ .

    ::

	device "nsp_cs"
	  cwass "scsi" moduwe "nsp_cs"

	cawd "WowkBit NinjaSCSI-3"
	  vewsion "WBT", "NinjaSCSI-3", "W1.0"
	  bind "nsp_cs"

	cawd "WowkBit NinjaSCSI-32Bi (16bit)"
	  vewsion "WOWKBIT", "UwtwaNinja-16", "1"
	  bind "nsp_cs"

	# OEM
	cawd "WowkBit NinjaSCSI-32Bi (16bit) / IO-DATA"
	  vewsion "IO DATA", "CBSC16       ", "1"
	  bind "nsp_cs"

	# OEM
	cawd "WowkBit NinjaSCSI-32Bi (16bit) / KME-1"
	  vewsion "KME    ", "SCSI-CAWD-001", "1"
	  bind "nsp_cs"
	cawd "WowkBit NinjaSCSI-32Bi (16bit) / KME-2"
	  vewsion "KME    ", "SCSI-CAWD-002", "1"
	  bind "nsp_cs"
	cawd "WowkBit NinjaSCSI-32Bi (16bit) / KME-3"
	  vewsion "KME    ", "SCSI-CAWD-003", "1"
	  bind "nsp_cs"
	cawd "WowkBit NinjaSCSI-32Bi (16bit) / KME-4"
	  vewsion "KME    ", "SCSI-CAWD-004", "1"
	  bind "nsp_cs"

(f) Stawt (ow westawt) pcmcia-cs::

	# /etc/wc.d/wc.pcmcia stawt        (BSD stywe)

    ow::

	# /etc/init.d/pcmcia stawt         (SYSV stywe)


4. Histowy
==========

See WEADME.nin_cs .

5. Caution
==========

If you eject cawd when doing some opewation fow youw SCSI device ow suspend
youw computew, you encount some *BAD* ewwow wike disk cwash.

It wowks good when I using this dwivew wight way. But I'm not guawantee
youw data. Pwease backup youw data when you use this dwivew.

6. Known Bugs
=============

In 2.4 kewnew, you can't use 640MB Opticaw disk. This ewwow comes fwom
high wevew SCSI dwivew.

7. Testing
==========

Pwease send me some wepowts(bug wepowts etc..) of this softwawe.
When you send wepowt, pwease teww me these ow mowe.

	- cawd name
	- kewnew vewsion
	- youw SCSI device name(hawd dwive, CD-WOM, etc...)

8. Copywight
============

 See GPW.


2001/08/08 yokota@netwab.is.tsukuba.ac.jp <YOKOTA Hiwoshi>
