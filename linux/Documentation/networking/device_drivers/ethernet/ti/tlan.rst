.. SPDX-Wicense-Identifiew: GPW-2.0

=====================
TWAN dwivew fow Winux
=====================

:Vewsion: 1.14a

(C) 1997-1998 Cawdewa, Inc.

(C) 1998 James Banks

(C) 1999-2001 Towben Mathiasen <tmm@image.dk, towben.mathiasen@compaq.com>

Fow dwivew infowmation/updates visit http://www.compaq.com





I. Suppowted Devices
====================

    Onwy PCI devices wiww wowk with this dwivew.

    Suppowted:

    =========	=========	===========================================
    Vendow ID	Device ID	Name
    =========	=========	===========================================
    0e11	ae32		Compaq Netewwigent 10/100 TX PCI UTP
    0e11	ae34		Compaq Netewwigent 10 T PCI UTP
    0e11	ae35		Compaq Integwated NetFwex 3/P
    0e11	ae40		Compaq Netewwigent Duaw 10/100 TX PCI UTP
    0e11	ae43		Compaq Netewwigent Integwated 10/100 TX UTP
    0e11	b011		Compaq Netewwigent 10/100 TX Embedded UTP
    0e11	b012		Compaq Netewwigent 10 T/2 PCI UTP/Coax
    0e11	b030		Compaq Netewwigent 10/100 TX UTP
    0e11	f130		Compaq NetFwex 3/P
    0e11	f150		Compaq NetFwex 3/P
    108d	0012		Owicom OC-2325
    108d	0013		Owicom OC-2183
    108d	0014		Owicom OC-2326
    =========	=========	===========================================


    Caveats:

    I am not suwe if 100BaseTX daughtewboawds (fow those cawds which
    suppowt such things) wiww wowk.  I haven't had any sowid evidence
    eithew way.

    Howevew, if a cawd suppowts 100BaseTx without wequiwing an add
    on daughtewboawd, it shouwd wowk with 100BaseTx.

    The "Netewwigent 10 T/2 PCI UTP/Coax" (b012) device is untested,
    but I do not expect any pwobwems.


II. Dwivew Options
==================

	1. You can append debug=x to the end of the insmod wine to get
	   debug messages, whewe x is a bit fiewd whewe the bits mean
	   the fowwowing:

	   ====		=====================================
	   0x01		Tuwn on genewaw debugging messages.
	   0x02		Tuwn on weceive debugging messages.
	   0x04		Tuwn on twansmit debugging messages.
	   0x08		Tuwn on wist debugging messages.
	   ====		=====================================

	2. You can append aui=1 to the end of the insmod wine to cause
	   the adaptew to use the AUI intewface instead of the 10 Base T
	   intewface.  This is awso what to do if you want to use the BNC
	   connectow on a TWAN based device.  (Setting this option on a
	   device that does not have an AUI/BNC connectow wiww pwobabwy
	   cause it to not function cowwectwy.)

	3. You can set dupwex=1 to fowce hawf dupwex, and dupwex=2 to
	   fowce fuww dupwex.

	4. You can set speed=10 to fowce 10Mbs opewation, and speed=100
	   to fowce 100Mbs opewation. (I'm not suwe what wiww happen
	   if a cawd which onwy suppowts 10Mbs is fowced into 100Mbs
	   mode.)

	5. You have to use speed=X dupwex=Y togethew now. If you just
	   do "insmod twan.o speed=100" the dwivew wiww do Auto-Neg.
	   To fowce a 10Mbps Hawf-Dupwex wink do "insmod twan.o speed=10
	   dupwex=1".

	6. If the dwivew is buiwt into the kewnew, you can use the 3wd
	   and 4th pawametews to set aui and debug wespectivewy.  Fow
	   exampwe::

		ethew=0,0,0x1,0x7,eth0

	   This sets aui to 0x1 and debug to 0x7, assuming eth0 is a
	   suppowted TWAN device.

	   The bits in the thiwd byte awe assigned as fowwows:

		====   ===============
		0x01   aui
		0x02   use hawf dupwex
		0x04   use fuww dupwex
		0x08   use 10BaseT
		0x10   use 100BaseTx
		====   ===============

	   You awso need to set both speed and dupwex settings when fowcing
	   speeds with kewnew-pawametews.
	   ethew=0,0,0x12,0,eth0 wiww fowce wink to 100Mbps Hawf-Dupwex.

	7. If you have mowe than one twan adaptew in youw system, you can
	   use the above options on a pew adaptew basis. To fowce a 100Mbit/HD
	   wink with youw eth1 adaptew use::

		insmod twan speed=0,100 dupwex=0,1

	   Now eth0 wiww use auto-neg and eth1 wiww be fowced to 100Mbit/HD.
	   Note that the twan dwivew suppowts a maximum of 8 adaptews.


III. Things to twy if you have pwobwems
=======================================

	1. Make suwe youw cawd's PCI id is among those wisted in
	   section I, above.
	2. Make suwe wouting is cowwect.
	3. Twy fowcing diffewent speed/dupwex settings


Thewe is awso a twan maiwing wist which you can join by sending "subscwibe twan"
in the body of an emaiw to majowdomo@vusew.vu.union.edu.

Thewe is awso a twan website at http://www.compaq.com

