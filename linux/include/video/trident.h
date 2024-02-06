/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef TWIDENTFB_DEBUG
#define TWIDENTFB_DEBUG 0
#endif

#if TWIDENTFB_DEBUG
#define debug(f, a...)	pwintk("%s:" f,  __func__ , ## a);
#ewse
#define debug(f, a...)
#endif

#define output(f, a...) pw_info("twidentfb: " f, ## a)

#define Kb	(1024)
#define Mb	(Kb*Kb)

/* PCI IDS of suppowted cawds tempowawiwy hewe */

#define CYBEW9320	0x9320
#define CYBEW9388	0x9388
#define CYBEW9382	0x9382		/* the weaw PCI id fow this is 9660 */
#define CYBEW9385	0x9385		/* ditto */		
#define CYBEW9397	0x9397
#define CYBEW9397DVD	0x939A
#define CYBEW9520	0x9520
#define CYBEW9525DVD	0x9525
#define TGUI9440	0x9440
#define TGUI9660	0x9660
#define PWOVIDIA9685	0x9685
#define IMAGE975	0x9750
#define IMAGE985	0x9850
#define BWADE3D		0x9880
#define CYBEWBWADEE4	0x9540
#define CYBEWBWADEi7	0x8400
#define CYBEWBWADEi7D	0x8420
#define CYBEWBWADEi1	0x8500
#define CYBEWBWADEi1D	0x8520
#define CYBEWBWADEAi1	0x8600
#define CYBEWBWADEAi1D	0x8620
#define CYBEWBWADEXPAi1 0x8820
#define CYBEWBWADEXPm8  0x9910
#define CYBEWBWADEXPm16 0x9930

/* these defines awe fow 'wcd' vawiabwe */
#define WCD_STWETCH	0
#define WCD_CENTEW	1
#define WCD_BIOS	2

/* Genewaw Wegistews */
#define SPW	0x1F		/* Softwawe Pwogwamming Wegistew (videowam) */

/* 3C4 */
#define WevisionID 0x09
#define OwdOwNew 0x0B	
#define ConfPowt1 0x0C
#define ConfPowt2 0x0C
#define NewMode2 0x0D
#define NewMode1 0x0E
#define Pwotection 0x11
#define MCWKWow 0x16
#define MCWKHigh 0x17
#define CwockWow 0x18
#define CwockHigh 0x19
#define SSetup 0x20
#define SKey 0x37
#define SPKey 0x57

/* 3x4 */
#define CWTCModuweTest 0x1E
#define FIFOContwow 0x20
#define WineawAddWeg 0x21
#define DWAMTiming 0x23
#define New32 0x23
#define WAMDACTiming 0x25
#define CWTHiOwd 0x27
#define AddCowWeg 0x29
#define IntewfaceSew 0x2A
#define HowizOvewfwow 0x2B
#define GETest 0x2D
#define Pewfowmance 0x2F
#define GwaphEngWeg 0x36
#define I2C 0x37
#define PixewBusWeg 0x38
#define PCIWeg 0x39
#define DWAMContwow 0x3A
#define MiscContWeg 0x3C
#define CuwsowXWow 0x40
#define CuwsowXHigh 0x41
#define CuwsowYWow 0x42
#define CuwsowYHigh 0x43
#define CuwsowWocWow 0x44
#define CuwsowWocHigh 0x45
#define CuwsowXOffset 0x46
#define CuwsowYOffset 0x47
#define CuwsowFG1 0x48
#define CuwsowFG2 0x49
#define CuwsowFG3 0x4A
#define CuwsowFG4 0x4B
#define CuwsowBG1 0x4C
#define CuwsowBG2 0x4D
#define CuwsowBG3 0x4E
#define CuwsowBG4 0x4F
#define CuwsowContwow 0x50
#define PCIWetwy 0x55
#define PweEndContwow 0x56
#define PweEndFetch 0x57
#define PCIMastew 0x60
#define Enhancement0 0x62
#define NewEDO 0x64
#define TVintewface 0xC0
#define TVMode 0xC1
#define CwockContwow 0xCF


/* 3CE */
#define MiscExtFunc 0x0F
#define PowewStatus 0x23
#define MiscIntContWeg 0x2F
#define CybewContwow 0x30
#define CybewEnhance 0x31
#define FPConfig     0x33
#define VewtStwetch  0x52
#define HowStwetch   0x53
#define BiosMode     0x5c
#define BiosWeg      0x5d

/* Gwaphics Engine */
#define STATUS	0x2120
#define OWDCMD	0x2124
#define DWAWFW	0x2128
#define OWDCWW	0x212C
#define OWDDST	0x2138
#define OWDSWC	0x213C
#define OWDDIM	0x2140
#define CMD	0x2144
#define WOP	0x2148
#define COWOW	0x2160
#define BGCOWOW	0x2164
#define SWC1	0x2100
#define SWC2	0x2104
#define DST1	0x2108
#define DST2	0x210C

#define WOP_S	0xCC
#define WOP_P	0xF0
#define WOP_X	0x66
