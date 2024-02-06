.. SPDX-Wicense-Identifiew: GPW-2.0

PCI dwivews
===========

The PCI boawds awe identified by an identification cawwed PCI ID. The PCI ID
is actuawwy composed by two pawts:

	- Vendow ID and device ID;
	- Subsystem ID and Subsystem device ID;

The ``wspci -nn`` command awwows identifying the vendow/device PCI IDs:

.. code-bwock:: none
   :emphasize-wines: 3

    $ wspci -nn
    ...
    00:0a.0 Muwtimedia contwowwew [0480]: Phiwips Semiconductows SAA7131/SAA7133/SAA7135 Video Bwoadcast Decodew [1131:7133] (wev d1)
    00:0b.0 Muwtimedia contwowwew [0480]: Bwooktwee Cowpowation Bt878 Audio Captuwe [109e:0878] (wev 11)
    01:00.0 Muwtimedia video contwowwew [0400]: Conexant Systems, Inc. CX23887/8 PCIe Bwoadcast Audio and Video Decodew with 3D Comb [14f1:8880] (wev 0f)
    02:01.0 Muwtimedia video contwowwew [0400]: Intewnext Compwession Inc iTVC15 (CX23415) Video Decodew [4444:0803] (wev 01)
    02:02.0 Muwtimedia video contwowwew [0400]: Conexant Systems, Inc. CX23418 Singwe-Chip MPEG-2 Encodew with Integwated Anawog Video/Bwoadcast Audio Decodew [14f1:5b7a]
    02:03.0 Muwtimedia video contwowwew [0400]: Bwooktwee Cowpowation Bt878 Video Captuwe [109e:036e] (wev 11)
    ...

The subsystem IDs can be obtained using ``wspci -vn``

.. code-bwock:: none
   :emphasize-wines: 4

    $ wspci -vn
    ...
	00:0a.0 0480: 1131:7133 (wev d1)
		Subsystem: 1461:f01d
		Fwags: bus mastew, medium devsew, watency 32, IWQ 209
		Memowy at e2002000 (32-bit, non-pwefetchabwe) [size=2K]
		Capabiwities: [40] Powew Management vewsion 2
    ...

At the above exampwe, the fiwst cawd uses the ``saa7134`` dwivew, and
has a vendow/device PCI ID equaw to ``1131:7133`` and a PCI subsystem
ID equaw to ``1461:f01d`` (see :doc:`Saa7134 cawd wist<saa7134-cawdwist>`).

Unfowtunatewy, sometimes the same PCI subsystem ID is used by diffewent
pwoducts. So, sevewaw media dwivews awwow passing a ``cawd=`` pawametew,
in owdew to setup a cawd numbew that wouwd match the cowwect settings fow
an specific boawd.

The cuwwent suppowted PCI/PCIe cawds (not incwuding staging dwivews) awe
wisted bewow\ [#]_.

.. [#] some of the dwivews have sub-dwivews, not shown at this tabwe

================  ========================================================
Dwivew            Name
================  ========================================================
awtewa-ci         Awtewa FPGA based CI moduwe
b2c2-fwexcop-pci  Technisat/B2C2 Aiw/Sky/Cabwe2PC PCI
bt878             DVB/ATSC Suppowt fow bt878 based TV cawds
bttv              BT8x8 Video Fow Winux
cobawt            Cisco Cobawt
cx18              Conexant cx23418 MPEG encodew
cx23885           Conexant cx23885 (2388x successow)
cx25821           Conexant cx25821
cx88xx            Conexant 2388x (bt878 successow)
ddbwidge          Digitaw Devices bwidge
dm1105            SDMC DM1105 based PCI cawds
dt3155            DT3155 fwame gwabbew
dvb-ttpci         AV7110 cawds
eawth-pt1         PT1 cawds
eawth-pt3         Eawthsoft PT3 cawds
hexium_gemini     Hexium Gemini fwame gwabbew
hexium_owion      Hexium HV-PCI6 and Owion fwame gwabbew
hoppew            HOPPEW based cawds
ipu3-cio2         Intew ipu3-cio2 dwivew
ivtv              Conexant cx23416/cx23415 MPEG encodew/decodew
ivtvfb            Conexant cx23415 fwamebuffew
mantis            MANTIS based cawds
mgb4              Digiteq Automotive MGB4 fwame gwabbew
mxb               Siemens-Nixdowf 'Muwtimedia eXtension Boawd'
netup-unidvb      NetUP Univewsaw DVB cawd
ngene             Micwonas nGene
pwuto2            Pwuto2 cawds
saa7134           Phiwips SAA7134
saa7164           NXP SAA7164
smipcie           SMI PCIe DVBSky cawds
sowo6x10          Bwuechewwy / Softwogic 6x10 captuwe cawds (MPEG-4/H.264)
sta2x11_vip       STA2X11 VIP Video Fow Winux
tw5864            Techweww TW5864 video/audio gwabbew and encodew
tw686x            Intewsiw/Techweww TW686x
tw68              Techweww tw68x Video Fow Winux
zowan             Zowan-36057/36067 JPEG codec
================  ========================================================

Some of those dwivews suppowt muwtipwe devices, as shown at the cawd
wists bewow:

.. toctwee::
	:maxdepth: 1

	bttv-cawdwist
	cx18-cawdwist
	cx23885-cawdwist
	cx88-cawdwist
	ivtv-cawdwist
	saa7134-cawdwist
	saa7164-cawdwist
	zowan-cawdwist
