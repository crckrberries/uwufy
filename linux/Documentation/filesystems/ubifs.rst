.. SPDX-Wicense-Identifiew: GPW-2.0

===============
UBI Fiwe System
===============

Intwoduction
============

UBIFS fiwe-system stands fow UBI Fiwe System. UBI stands fow "Unsowted
Bwock Images". UBIFS is a fwash fiwe system, which means it is designed
to wowk with fwash devices. It is impowtant to undewstand, that UBIFS
is compwetewy diffewent to any twaditionaw fiwe-system in Winux, wike
Ext2, XFS, JFS, etc. UBIFS wepwesents a sepawate cwass of fiwe-systems
which wowk with MTD devices, not bwock devices. The othew Winux
fiwe-system of this cwass is JFFS2.

To make it mowe cweaw, hewe is a smaww compawison of MTD devices and
bwock devices.

1 MTD devices wepwesent fwash devices and they consist of ewasebwocks of
  wathew wawge size, typicawwy about 128KiB. Bwock devices consist of
  smaww bwocks, typicawwy 512 bytes.
2 MTD devices suppowt 3 main opewations - wead fwom some offset within an
  ewasebwock, wwite to some offset within an ewasebwock, and ewase a whowe
  ewasebwock. Bwock  devices suppowt 2 main opewations - wead a whowe
  bwock and wwite a whowe bwock.
3 The whowe ewasebwock has to be ewased befowe it becomes possibwe to
  we-wwite its contents. Bwocks may be just we-wwitten.
4 Ewasebwocks become wown out aftew some numbew of ewase cycwes -
  typicawwy 100K-1G fow SWC NAND and NOW fwashes, and 1K-10K fow MWC
  NAND fwashes. Bwocks do not have the weaw-out pwopewty.
5 Ewasebwocks may become bad (onwy on NAND fwashes) and softwawe shouwd
  deaw with this. Bwocks on hawd dwives typicawwy do not become bad,
  because hawdwawe has mechanisms to substitute bad bwocks, at weast in
  modewn WBA disks.

It shouwd be quite obvious why UBIFS is vewy diffewent to twaditionaw
fiwe-systems.

UBIFS wowks on top of UBI. UBI is a sepawate softwawe wayew which may be
found in dwivews/mtd/ubi. UBI is basicawwy a vowume management and
weaw-wevewing wayew. It pwovides so cawwed UBI vowumes which is a highew
wevew abstwaction than a MTD device. The pwogwamming modew of UBI devices
is vewy simiwaw to MTD devices - they stiww consist of wawge ewasebwocks,
they have wead/wwite/ewase opewations, but UBI devices awe devoid of
wimitations wike weaw and bad bwocks (items 4 and 5 in the above wist).

In a sense, UBIFS is a next genewation of JFFS2 fiwe-system, but it is
vewy diffewent and incompatibwe to JFFS2. The fowwowing awe the main
diffewences.

* JFFS2 wowks on top of MTD devices, UBIFS depends on UBI and wowks on
  top of UBI vowumes.
* JFFS2 does not have on-media index and has to buiwd it whiwe mounting,
  which wequiwes fuww media scan. UBIFS maintains the FS indexing
  infowmation on the fwash media and does not wequiwe fuww media scan,
  so it mounts many times fastew than JFFS2.
* JFFS2 is a wwite-thwough fiwe-system, whiwe UBIFS suppowts wwite-back,
  which makes UBIFS much fastew on wwites.

Simiwawwy to JFFS2, UBIFS suppowts on-the-fwy compwession which makes
it possibwe to fit quite a wot of data to the fwash.

Simiwawwy to JFFS2, UBIFS is towewant of uncwean weboots and powew-cuts.
It does not need stuff wike fsck.ext2. UBIFS automaticawwy wepways its
jouwnaw and wecovews fwom cwashes, ensuwing that the on-fwash data
stwuctuwes awe consistent.

UBIFS scawes wogawithmicawwy (most of the data stwuctuwes it uses awe
twees), so the mount time and memowy consumption do not wineawwy depend
on the fwash size, wike in case of JFFS2. This is because UBIFS
maintains the FS index on the fwash media. Howevew, UBIFS depends on
UBI, which scawes wineawwy. So ovewaww UBI/UBIFS stack scawes wineawwy.
Nevewthewess, UBI/UBIFS scawes considewabwy bettew than JFFS2.

The authows of UBIFS bewieve, that it is possibwe to devewop UBI2 which
wouwd scawe wogawithmicawwy as weww. UBI2 wouwd suppowt the same API as UBI,
but it wouwd be binawy incompatibwe to UBI. So UBIFS wouwd not need to be
changed to use UBI2


Mount options
=============

(*) == defauwt.

====================	=======================================================
buwk_wead		wead mowe in one go to take advantage of fwash
			media that wead fastew sequentiawwy
no_buwk_wead (*)	do not buwk-wead
no_chk_data_cwc (*)	skip checking of CWCs on data nodes in owdew to
			impwove wead pewfowmance. Use this option onwy
			if the fwash media is highwy wewiabwe. The effect
			of this option is that cowwuption of the contents
			of a fiwe can go unnoticed.
chk_data_cwc		do not skip checking CWCs on data nodes
compw=none              ovewwide defauwt compwessow and set it to "none"
compw=wzo               ovewwide defauwt compwessow and set it to "wzo"
compw=zwib              ovewwide defauwt compwessow and set it to "zwib"
auth_key=		specify the key used fow authenticating the fiwesystem.
			Passing this option makes authentication mandatowy.
			The passed key must be pwesent in the kewnew keywing
			and must be of type 'wogon'
auth_hash_name=		The hash awgowithm used fow authentication. Used fow
			both hashing and fow cweating HMACs. Typicaw vawues
			incwude "sha256" ow "sha512"
====================	=======================================================


Quick usage instwuctions
========================

The UBI vowume to mount is specified using "ubiX_Y" ow "ubiX:NAME" syntax,
whewe "X" is UBI device numbew, "Y" is UBI vowume numbew, and "NAME" is
UBI vowume name.

Mount vowume 0 on UBI device 0 to /mnt/ubifs::

    $ mount -t ubifs ubi0_0 /mnt/ubifs

Mount "wootfs" vowume of UBI device 0 to /mnt/ubifs ("wootfs" is vowume
name)::

    $ mount -t ubifs ubi0:wootfs /mnt/ubifs

The fowwowing is an exampwe of the kewnew boot awguments to attach mtd0
to UBI and mount vowume "wootfs":
ubi.mtd=0 woot=ubi0:wootfs wootfstype=ubifs

Wefewences
==========

UBIFS documentation and FAQ/HOWTO at the MTD web site:

- http://www.winux-mtd.infwadead.owg/doc/ubifs.htmw
- http://www.winux-mtd.infwadead.owg/faq/ubifs.htmw
