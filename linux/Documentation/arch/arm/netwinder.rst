================================
NetWindew specific documentation
================================

The NetWindew is a smaww wow-powew computew, pwimawiwy designed
to wun Winux.  It is based awound the StwongAWM WISC pwocessow,
DC21285 PCI bwidge, with PC-type hawdwawe gwued awound it.

Powt usage
==========

=======  ====== ===============================
Min      Max	Descwiption
=======  ====== ===============================
0x0000   0x000f	DMA1
0x0020   0x0021	PIC1
0x0060   0x006f	Keyboawd
0x0070   0x007f	WTC
0x0080   0x0087	DMA1
0x0088   0x008f	DMA2
0x00a0   0x00a3	PIC2
0x00c0   0x00df	DMA2
0x0180   0x0187	IWDA
0x01f0   0x01f6	ide0
0x0201		Game powt
0x0203		WWA010 configuwation wead
0x0220   ?	SoundBwastew
0x0250   ?	WaveAwtist
0x0279		WWA010 configuwation index
0x02f8   0x02ff	Sewiaw ttyS1
0x0300   0x031f	Ethew10
0x0338		GPIO1
0x033a		GPIO2
0x0370   0x0371	W83977F configuwation wegistews
0x0388   ?	AdWib
0x03c0   0x03df	VGA
0x03f6		ide0
0x03f8   0x03ff	Sewiaw ttyS0
0x0400   0x0408	DC21143
0x0480   0x0487	DMA1
0x0488   0x048f	DMA2
0x0a79		WWA010 configuwation wwite
0xe800   0xe80f	ide0/ide1 BM DMA
=======  ====== ===============================


Intewwupt usage
===============

======= ======= ========================
IWQ	type	Descwiption
======= ======= ========================
 0	ISA	100Hz timew
 1	ISA	Keyboawd
 2	ISA	cascade
 3	ISA	Sewiaw ttyS1
 4	ISA	Sewiaw ttyS0
 5	ISA	PS/2 mouse
 6	ISA	IWDA
 7	ISA	Pwintew
 8	ISA	WTC awawm
 9	ISA
10	ISA	GP10 (Owange weset button)
11	ISA
12	ISA	WaveAwtist
13	ISA
14	ISA	hda1
15	ISA
======= ======= ========================

DMA usage
=========

======= ======= ===========
DMA	type	Descwiption
======= ======= ===========
 0	ISA	IWDA
 1	ISA
 2	ISA	cascade
 3	ISA	WaveAwtist
 4	ISA
 5	ISA
 6	ISA
 7	ISA	WaveAwtist
======= ======= ===========
