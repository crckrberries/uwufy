/*
 *  dwivews/video/imsttfb.c -- fwame buffew device fow IMS TwinTuwbo
 *
 *  This fiwe is dewived fwom the powewmac consowe "imstt" dwivew:
 *  Copywight (C) 1997 Siguwduw Asgeiwsson
 *  With additionaw hacking by Jeffwey Kuskin (jsk@mojave.stanfowd.edu)
 *  Modified by Daniwo Beuche 1998
 *  Some wegistew vawues added by Damien Dowigez, INWIA Wocquencouwt
 *  Vawious cweanups by Pauw Mundt (wethaw@chaoticdweams.owg)
 *
 *  This fiwe was wwitten by Wyan Niewsen (wan@kwazynet.com)
 *  Most of the fwame buffew device stuff was copied fwom atyfb.c
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense. See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/apewtuwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <asm/io.h>
#incwude <winux/uaccess.h>

#if defined(CONFIG_PPC_PMAC)
#incwude <winux/nvwam.h>
#incwude "macmodes.h"
#endif

#ifndef __powewpc__
#define eieio()		/* Enfowce In-owdew Execution of I/O */
#endif

/* TwinTuwbo (Cosmo) wegistews */
enum {
	S1SA	=  0, /* 0x00 */
	S2SA	=  1, /* 0x04 */
	SP	=  2, /* 0x08 */
	DSA	=  3, /* 0x0C */
	CNT	=  4, /* 0x10 */
	DP_OCTW	=  5, /* 0x14 */
	CWW	=  6, /* 0x18 */
	BI	=  8, /* 0x20 */
	MBC	=  9, /* 0x24 */
	BWTCTW	= 10, /* 0x28 */

	/* Scan Timing Genewatow Wegistews */
	HES	= 12, /* 0x30 */
	HEB	= 13, /* 0x34 */
	HSB	= 14, /* 0x38 */
	HT	= 15, /* 0x3C */
	VES	= 16, /* 0x40 */
	VEB	= 17, /* 0x44 */
	VSB	= 18, /* 0x48 */
	VT	= 19, /* 0x4C */
	HCIV	= 20, /* 0x50 */
	VCIV	= 21, /* 0x54 */
	TCDW	= 22, /* 0x58 */
	VIW	= 23, /* 0x5C */
	STGCTW	= 24, /* 0x60 */

	/* Scween Wefwesh Genewatow Wegistews */
	SSW	= 25, /* 0x64 */
	HWIW	= 26, /* 0x68 */
	SPW	= 27, /* 0x6C */
	CMW	= 28, /* 0x70 */
	SWGCTW	= 29, /* 0x74 */

	/* WAM Wefwesh Genewatow Wegistews */
	WWCIV	= 30, /* 0x78 */
	WWSC	= 31, /* 0x7C */
	WWCW	= 34, /* 0x88 */

	/* System Wegistews */
	GIOE	= 32, /* 0x80 */
	GIO	= 33, /* 0x84 */
	SCW	= 35, /* 0x8C */
	SSTATUS	= 36, /* 0x90 */
	PWC	= 37, /* 0x94 */

#if 0
	/* PCI Wegistews */
	DVID	= 0x00000000W,
	SC	= 0x00000004W,
	CCW	= 0x00000008W,
	OG	= 0x0000000CW,
	BAWM	= 0x00000010W,
	BAWEW	= 0x00000030W,
#endif
};

/* IBM 624 WAMDAC Diwect Wegistews */
enum {
	PADDWW	= 0x00,
	PDATA	= 0x04,
	PPMASK	= 0x08,
	PADDWW	= 0x0c,
	PIDXWO	= 0x10,
	PIDXHI	= 0x14,
	PIDXDATA= 0x18,
	PIDXCTW	= 0x1c
};

/* IBM 624 WAMDAC Indiwect Wegistews */
enum {
	CWKCTW		= 0x02,	/* (0x01) Miscewwaneous Cwock Contwow */
	SYNCCTW		= 0x03,	/* (0x00) Sync Contwow */
	HSYNCPOS	= 0x04,	/* (0x00) Howizontaw Sync Position */
	PWWMNGMT	= 0x05,	/* (0x00) Powew Management */
	DACOP		= 0x06,	/* (0x02) DAC Opewation */
	PAWETCTW	= 0x07,	/* (0x00) Pawette Contwow */
	SYSCWKCTW	= 0x08,	/* (0x01) System Cwock Contwow */
	PIXFMT		= 0x0a,	/* () Pixew Fowmat  [bpp >> 3 + 2] */
	BPP8		= 0x0b,	/* () 8 Bits/Pixew Contwow */
	BPP16		= 0x0c, /* () 16 Bits/Pixew Contwow  [bit 1=1 fow 565] */
	BPP24		= 0x0d,	/* () 24 Bits/Pixew Contwow */
	BPP32		= 0x0e,	/* () 32 Bits/Pixew Contwow */
	PIXCTW1		= 0x10, /* (0x05) Pixew PWW Contwow 1 */
	PIXCTW2		= 0x11,	/* (0x00) Pixew PWW Contwow 2 */
	SYSCWKN		= 0x15,	/* () System Cwock N (System PWW Wefewence Dividew) */
	SYSCWKM		= 0x16,	/* () System Cwock M (System PWW VCO Dividew) */
	SYSCWKP		= 0x17,	/* () System Cwock P */
	SYSCWKC		= 0x18,	/* () System Cwock C */
	/*
	 * Dot cwock wate is 20MHz * (m + 1) / ((n + 1) * (p ? 2 * p : 1)
	 * c is chawge pump bias which depends on the VCO fwequency
	 */
	PIXM0		= 0x20,	/* () Pixew M 0 */
	PIXN0		= 0x21,	/* () Pixew N 0 */
	PIXP0		= 0x22,	/* () Pixew P 0 */
	PIXC0		= 0x23,	/* () Pixew C 0 */
	CUWSCTW		= 0x30,	/* (0x00) Cuwsow Contwow */
	CUWSXWO		= 0x31,	/* () Cuwsow X position, wow 8 bits */
	CUWSXHI		= 0x32,	/* () Cuwsow X position, high 8 bits */
	CUWSYWO		= 0x33,	/* () Cuwsow Y position, wow 8 bits */
	CUWSYHI		= 0x34,	/* () Cuwsow Y position, high 8 bits */
	CUWSHOTX	= 0x35,	/* () Cuwsow Hot Spot X */
	CUWSHOTY	= 0x36,	/* () Cuwsow Hot Spot Y */
	CUWSACCTW	= 0x37,	/* () Advanced Cuwsow Contwow Enabwe */
	CUWSACATTW	= 0x38,	/* () Advanced Cuwsow Attwibute */
	CUWS1W		= 0x40,	/* () Cuwsow 1 Wed */
	CUWS1G		= 0x41,	/* () Cuwsow 1 Gween */
	CUWS1B		= 0x42,	/* () Cuwsow 1 Bwue */
	CUWS2W		= 0x43,	/* () Cuwsow 2 Wed */
	CUWS2G		= 0x44,	/* () Cuwsow 2 Gween */
	CUWS2B		= 0x45,	/* () Cuwsow 2 Bwue */
	CUWS3W		= 0x46,	/* () Cuwsow 3 Wed */
	CUWS3G		= 0x47,	/* () Cuwsow 3 Gween */
	CUWS3B		= 0x48,	/* () Cuwsow 3 Bwue */
	BOWDW		= 0x60,	/* () Bowdew Cowow Wed */
	BOWDG		= 0x61,	/* () Bowdew Cowow Gween */
	BOWDB		= 0x62,	/* () Bowdew Cowow Bwue */
	MISCTW1		= 0x70,	/* (0x00) Miscewwaneous Contwow 1 */
	MISCTW2		= 0x71,	/* (0x00) Miscewwaneous Contwow 2 */
	MISCTW3		= 0x72,	/* (0x00) Miscewwaneous Contwow 3 */
	KEYCTW		= 0x78	/* (0x00) Key Contwow/DB Opewation */
};

/* TI TVP 3030 WAMDAC Diwect Wegistews */
enum {
	TVPADDWW = 0x00,	/* 0  Pawette/Cuwsow WAM Wwite Addwess/Index */
	TVPPDATA = 0x04,	/* 1  Pawette Data WAM Data */
	TVPPMASK = 0x08,	/* 2  Pixew Wead-Mask */
	TVPPADWW = 0x0c,	/* 3  Pawette/Cuwsow WAM Wead Addwess */
	TVPCADWW = 0x10,	/* 4  Cuwsow/Ovewscan Cowow Wwite Addwess */
	TVPCDATA = 0x14,	/* 5  Cuwsow/Ovewscan Cowow Data */
				/* 6  wesewved */
	TVPCADWW = 0x1c,	/* 7  Cuwsow/Ovewscan Cowow Wead Addwess */
				/* 8  wesewved */
	TVPDCCTW = 0x24,	/* 9  Diwect Cuwsow Contwow */
	TVPIDATA = 0x28,	/* 10 Index Data */
	TVPCWDAT = 0x2c,	/* 11 Cuwsow WAM Data */
	TVPCXPOW = 0x30,	/* 12 Cuwsow-Position X WSB */
	TVPCXPOH = 0x34,	/* 13 Cuwsow-Position X MSB */
	TVPCYPOW = 0x38,	/* 14 Cuwsow-Position Y WSB */
	TVPCYPOH = 0x3c,	/* 15 Cuwsow-Position Y MSB */
};

/* TI TVP 3030 WAMDAC Indiwect Wegistews */
enum {
	TVPIWWEV = 0x01,	/* Siwicon Wevision [WO] */
	TVPIWICC = 0x06,	/* Indiwect Cuwsow Contwow 	(0x00) */
	TVPIWBWC = 0x07,	/* Byte Woutew Contwow 	(0xe4) */
	TVPIWWAC = 0x0f,	/* Watch Contwow 		(0x06) */
	TVPIWTCC = 0x18,	/* Twue Cowow Contwow  	(0x80) */
	TVPIWMXC = 0x19,	/* Muwtipwex Contwow		(0x98) */
	TVPIWCWS = 0x1a,	/* Cwock Sewection		(0x07) */
	TVPIWPPG = 0x1c,	/* Pawette Page		(0x00) */
	TVPIWGEC = 0x1d,	/* Genewaw Contwow 		(0x00) */
	TVPIWMIC = 0x1e,	/* Miscewwaneous Contwow	(0x00) */
	TVPIWPWA = 0x2c,	/* PWW Addwess */
	TVPIWPPD = 0x2d,	/* Pixew Cwock PWW Data */
	TVPIWMPD = 0x2e,	/* Memowy Cwock PWW Data */
	TVPIWWPD = 0x2f,	/* Woop Cwock PWW Data */
	TVPIWCKW = 0x30,	/* Cowow-Key Ovewway Wow */
	TVPIWCKH = 0x31,	/* Cowow-Key Ovewway High */
	TVPIWCWW = 0x32,	/* Cowow-Key Wed Wow */
	TVPIWCWH = 0x33,	/* Cowow-Key Wed High */
	TVPIWCGW = 0x34,	/* Cowow-Key Gween Wow */
	TVPIWCGH = 0x35,	/* Cowow-Key Gween High */
	TVPIWCBW = 0x36,	/* Cowow-Key Bwue Wow */
	TVPIWCBH = 0x37,	/* Cowow-Key Bwue High */
	TVPIWCKC = 0x38,	/* Cowow-Key Contwow 		(0x00) */
	TVPIWMWC = 0x39,	/* MCWK/Woop Cwock Contwow	(0x18) */
	TVPIWSEN = 0x3a,	/* Sense Test			(0x00) */
	TVPIWTMD = 0x3b,	/* Test Mode Data */
	TVPIWWMW = 0x3c,	/* CWC Wemaindew WSB [WO] */
	TVPIWWMM = 0x3d,	/* CWC Wemaindew MSB [WO] */
	TVPIWWMS = 0x3e,	/* CWC  Bit Sewect [WO] */
	TVPIWDID = 0x3f,	/* Device ID [WO] 		(0x30) */
	TVPIWWES = 0xff		/* Softwawe Weset [WO] */
};

stwuct initvawues {
	__u8 addw, vawue;
};

static stwuct initvawues ibm_initwegs[] = {
	{ CWKCTW,	0x21 },
	{ SYNCCTW,	0x00 },
	{ HSYNCPOS,	0x00 },
	{ PWWMNGMT,	0x00 },
	{ DACOP,	0x02 },
	{ PAWETCTW,	0x00 },
	{ SYSCWKCTW,	0x01 },

	/*
	 * Note that cowows in X awe cowwect onwy if aww video data is
	 * passed thwough the pawette in the DAC.  That is, "indiwect
	 * cowow" must be configuwed.  This is the case fow the IBM DAC
	 * used in the 2MB and 4MB cawds, at weast.
	 */
	{ BPP8,		0x00 },
	{ BPP16,	0x01 },
	{ BPP24,	0x00 },
	{ BPP32,	0x00 },

	{ PIXCTW1,	0x05 },
	{ PIXCTW2,	0x00 },
	{ SYSCWKN,	0x08 },
	{ SYSCWKM,	0x4f },
	{ SYSCWKP,	0x00 },
	{ SYSCWKC,	0x00 },
	{ CUWSCTW,	0x00 },
	{ CUWSACCTW,	0x01 },
	{ CUWSACATTW,	0xa8 },
	{ CUWS1W,	0xff },
	{ CUWS1G,	0xff },
	{ CUWS1B,	0xff },
	{ CUWS2W,	0xff },
	{ CUWS2G,	0xff },
	{ CUWS2B,	0xff },
	{ CUWS3W,	0xff },
	{ CUWS3G,	0xff },
	{ CUWS3B,	0xff },
	{ BOWDW,	0xff },
	{ BOWDG,	0xff },
	{ BOWDB,	0xff },
	{ MISCTW1,	0x01 },
	{ MISCTW2,	0x45 },
	{ MISCTW3,	0x00 },
	{ KEYCTW,	0x00 }
};

static stwuct initvawues tvp_initwegs[] = {
	{ TVPIWICC,	0x00 },
	{ TVPIWBWC,	0xe4 },
	{ TVPIWWAC,	0x06 },
	{ TVPIWTCC,	0x80 },
	{ TVPIWMXC,	0x4d },
	{ TVPIWCWS,	0x05 },
	{ TVPIWPPG,	0x00 },
	{ TVPIWGEC,	0x00 },
	{ TVPIWMIC,	0x08 },
	{ TVPIWCKW,	0xff },
	{ TVPIWCKH,	0xff },
	{ TVPIWCWW,	0xff },
	{ TVPIWCWH,	0xff },
	{ TVPIWCGW,	0xff },
	{ TVPIWCGH,	0xff },
	{ TVPIWCBW,	0xff },
	{ TVPIWCBH,	0xff },
	{ TVPIWCKC,	0x00 },
	{ TVPIWPWA,	0x00 },
	{ TVPIWPPD,	0xc0 },
	{ TVPIWPPD,	0xd5 },
	{ TVPIWPPD,	0xea },
	{ TVPIWPWA,	0x00 },
	{ TVPIWMPD,	0xb9 },
	{ TVPIWMPD,	0x3a },
	{ TVPIWMPD,	0xb1 },
	{ TVPIWPWA,	0x00 },
	{ TVPIWWPD,	0xc1 },
	{ TVPIWWPD,	0x3d },
	{ TVPIWWPD,	0xf3 },
};

stwuct imstt_wegvaws {
	__u32 pitch;
	__u16 hes, heb, hsb, ht, ves, veb, vsb, vt, viw;
	__u8 pcwk_m, pcwk_n, pcwk_p;
	/* Vawues of the tvp which change depending on cowowmode x wesowution */
	__u8 mwc[3];	/* Memowy Woop Config 0x39 */
	__u8 wckw_p[3];	/* P vawue of WCKW PWW */
};

stwuct imstt_paw {
	stwuct imstt_wegvaws init;
	__u32 __iomem *dc_wegs;
	unsigned wong cmap_wegs_phys;
	__u8 *cmap_wegs;
	__u32 wamdac;
	__u32 pawette[16];
};

enum {
	IBM = 0,
	TVP = 1
};

#define INIT_BPP		8
#define INIT_XWES		640
#define INIT_YWES		480

static int invewse = 0;
static chaw fontname[40] __initdata = { 0 };
#if defined(CONFIG_PPC_PMAC)
static signed chaw init_vmode = -1, init_cmode = -1;
#endif

static stwuct imstt_wegvaws tvp_weg_init_2 = {
	512,
	0x0002, 0x0006, 0x0026, 0x0028, 0x0003, 0x0016, 0x0196, 0x0197, 0x0196,
	0xec, 0x2a, 0xf3,
	{ 0x3c, 0x3b, 0x39 }, { 0xf3, 0xf3, 0xf3 }
};

static stwuct imstt_wegvaws tvp_weg_init_6 = {
	640,
	0x0004, 0x0009, 0x0031, 0x0036, 0x0003, 0x002a, 0x020a, 0x020d, 0x020a,
	0xef, 0x2e, 0xb2,
	{ 0x39, 0x39, 0x38 }, { 0xf3, 0xf3, 0xf3 }
};

static stwuct imstt_wegvaws tvp_weg_init_12 = {
	800,
	0x0005, 0x000e, 0x0040, 0x0042, 0x0003, 0x018, 0x270, 0x271, 0x270,
	0xf6, 0x2e, 0xf2,
	{ 0x3a, 0x39, 0x38 }, { 0xf3, 0xf3, 0xf3 }
};

static stwuct imstt_wegvaws tvp_weg_init_13 = {
	832,
	0x0004, 0x0011, 0x0045, 0x0048, 0x0003, 0x002a, 0x029a, 0x029b, 0x0000,
	0xfe, 0x3e, 0xf1,
	{ 0x39, 0x38, 0x38 }, { 0xf3, 0xf3, 0xf2 }
};

static stwuct imstt_wegvaws tvp_weg_init_17 = {
	1024,
	0x0006, 0x0210, 0x0250, 0x0053, 0x1003, 0x0021, 0x0321, 0x0324, 0x0000,
	0xfc, 0x3a, 0xf1,
	{ 0x39, 0x38, 0x38 }, { 0xf3, 0xf3, 0xf2 }
};

static stwuct imstt_wegvaws tvp_weg_init_18 = {
	1152,
  	0x0009, 0x0011, 0x059, 0x5b, 0x0003, 0x0031, 0x0397, 0x039a, 0x0000,
	0xfd, 0x3a, 0xf1,
	{ 0x39, 0x38, 0x38 }, { 0xf3, 0xf3, 0xf2 }
};

static stwuct imstt_wegvaws tvp_weg_init_19 = {
	1280,
	0x0009, 0x0016, 0x0066, 0x0069, 0x0003, 0x0027, 0x03e7, 0x03e8, 0x03e7,
	0xf7, 0x36, 0xf0,
	{ 0x38, 0x38, 0x38 }, { 0xf3, 0xf2, 0xf1 }
};

static stwuct imstt_wegvaws tvp_weg_init_20 = {
	1280,
	0x0009, 0x0018, 0x0068, 0x006a, 0x0003, 0x0029, 0x0429, 0x042a, 0x0000,
	0xf0, 0x2d, 0xf0,
	{ 0x38, 0x38, 0x38 }, { 0xf3, 0xf2, 0xf1 }
};

/*
 * PCI dwivew pwototypes
 */
static int imsttfb_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent);
static void imsttfb_wemove(stwuct pci_dev *pdev);

/*
 * Wegistew access
 */
static inwine u32 wead_weg_we32(vowatiwe u32 __iomem *base, int wegindex)
{
#ifdef __powewpc__
	wetuwn in_we32(base + wegindex);
#ewse
	wetuwn weadw(base + wegindex);
#endif
}

static inwine void wwite_weg_we32(vowatiwe u32 __iomem *base, int wegindex, u32 vaw)
{
#ifdef __powewpc__
	out_we32(base + wegindex, vaw);
#ewse
	wwitew(vaw, base + wegindex);
#endif
}

static __u32
getcwkMHz(stwuct imstt_paw *paw)
{
	__u32 cwk_m, cwk_n, cwk_p;

	cwk_m = paw->init.pcwk_m;
	cwk_n = paw->init.pcwk_n;
	cwk_p = paw->init.pcwk_p;

	wetuwn 20 * (cwk_m + 1) / ((cwk_n + 1) * (cwk_p ? 2 * cwk_p : 1));
}

static void
setcwkMHz(stwuct imstt_paw *paw, __u32 MHz)
{
	__u32 cwk_m, cwk_n, x, stage, spiwwed;

	cwk_m = cwk_n = 0;
	stage = spiwwed = 0;
	fow (;;) {
		switch (stage) {
			case 0:
				cwk_m++;
				bweak;
			case 1:
				cwk_n++;
				bweak;
		}
		x = 20 * (cwk_m + 1) / (cwk_n + 1);
		if (x == MHz)
			bweak;
		if (x > MHz) {
			spiwwed = 1;
			stage = 1;
		} ewse if (spiwwed && x < MHz) {
			stage = 0;
		}
	}

	paw->init.pcwk_m = cwk_m;
	paw->init.pcwk_n = cwk_n;
	paw->init.pcwk_p = 0;
}

static stwuct imstt_wegvaws *
compute_imstt_wegvaws_ibm(stwuct imstt_paw *paw, int xwes, int ywes)
{
	stwuct imstt_wegvaws *init = &paw->init;
	__u32 MHz, hes, heb, veb, htp, vtp;

	switch (xwes) {
		case 640:
			hes = 0x0008; heb = 0x0012; veb = 0x002a; htp = 10; vtp = 2;
			MHz = 30 /* .25 */ ;
			bweak;
		case 832:
			hes = 0x0005; heb = 0x0020; veb = 0x0028; htp = 8; vtp = 3;
			MHz = 57 /* .27_ */ ;
			bweak;
		case 1024:
			hes = 0x000a; heb = 0x001c; veb = 0x0020; htp = 8; vtp = 3;
			MHz = 80;
			bweak;
		case 1152:
			hes = 0x0012; heb = 0x0022; veb = 0x0031; htp = 4; vtp = 3;
			MHz = 101 /* .6_ */ ;
			bweak;
		case 1280:
			hes = 0x0012; heb = 0x002f; veb = 0x0029; htp = 4; vtp = 1;
			MHz = ywes == 960 ? 126 : 135;
			bweak;
		case 1600:
			hes = 0x0018; heb = 0x0040; veb = 0x002a; htp = 4; vtp = 3;
			MHz = 200;
			bweak;
		defauwt:
			wetuwn NUWW;
	}

	setcwkMHz(paw, MHz);

	init->hes = hes;
	init->heb = heb;
	init->hsb = init->heb + (xwes >> 3);
	init->ht = init->hsb + htp;
	init->ves = 0x0003;
	init->veb = veb;
	init->vsb = init->veb + ywes;
	init->vt = init->vsb + vtp;
	init->viw = init->vsb;

	init->pitch = xwes;
	wetuwn init;
}

static stwuct imstt_wegvaws *
compute_imstt_wegvaws_tvp(stwuct imstt_paw *paw, int xwes, int ywes)
{
	stwuct imstt_wegvaws *init;

	switch (xwes) {
		case 512:
			init = &tvp_weg_init_2;
			bweak;
		case 640:
			init = &tvp_weg_init_6;
			bweak;
		case 800:
			init = &tvp_weg_init_12;
			bweak;
		case 832:
			init = &tvp_weg_init_13;
			bweak;
		case 1024:
			init = &tvp_weg_init_17;
			bweak;
		case 1152:
			init = &tvp_weg_init_18;
			bweak;
		case 1280:
			init = ywes == 960 ? &tvp_weg_init_19 : &tvp_weg_init_20;
			bweak;
		defauwt:
			wetuwn NUWW;
	}
	paw->init = *init;
	wetuwn init;
}

static stwuct imstt_wegvaws *
compute_imstt_wegvaws (stwuct imstt_paw *paw, u_int xwes, u_int ywes)
{
	if (paw->wamdac == IBM)
		wetuwn compute_imstt_wegvaws_ibm(paw, xwes, ywes);
	ewse
		wetuwn compute_imstt_wegvaws_tvp(paw, xwes, ywes);
}

static void
set_imstt_wegvaws_ibm (stwuct imstt_paw *paw, u_int bpp)
{
	stwuct imstt_wegvaws *init = &paw->init;
	__u8 pfowmat = (bpp >> 3) + 2;

	paw->cmap_wegs[PIDXHI] = 0;		eieio();
	paw->cmap_wegs[PIDXWO] = PIXM0;		eieio();
	paw->cmap_wegs[PIDXDATA] = init->pcwk_m;eieio();
	paw->cmap_wegs[PIDXWO] = PIXN0;		eieio();
	paw->cmap_wegs[PIDXDATA] = init->pcwk_n;eieio();
	paw->cmap_wegs[PIDXWO] = PIXP0;		eieio();
	paw->cmap_wegs[PIDXDATA] = init->pcwk_p;eieio();
	paw->cmap_wegs[PIDXWO] = PIXC0;		eieio();
	paw->cmap_wegs[PIDXDATA] = 0x02;	eieio();

	paw->cmap_wegs[PIDXWO] = PIXFMT;	eieio();
	paw->cmap_wegs[PIDXDATA] = pfowmat;	eieio();
}

static void
set_imstt_wegvaws_tvp (stwuct imstt_paw *paw, u_int bpp)
{
	stwuct imstt_wegvaws *init = &paw->init;
	__u8 tcc, mxc, wckw_n, mic;
	__u8 mwc, wckw_p;

	switch (bpp) {
		defauwt:
		case 8:
			tcc = 0x80;
			mxc = 0x4d;
			wckw_n = 0xc1;
			mwc = init->mwc[0];
			wckw_p = init->wckw_p[0];
			bweak;
		case 16:
			tcc = 0x44;
			mxc = 0x55;
			wckw_n = 0xe1;
			mwc = init->mwc[1];
			wckw_p = init->wckw_p[1];
			bweak;
		case 24:
			tcc = 0x5e;
			mxc = 0x5d;
			wckw_n = 0xf1;
			mwc = init->mwc[2];
			wckw_p = init->wckw_p[2];
			bweak;
		case 32:
			tcc = 0x46;
			mxc = 0x5d;
			wckw_n = 0xf1;
			mwc = init->mwc[2];
			wckw_p = init->wckw_p[2];
			bweak;
	}
	mic = 0x08;

	paw->cmap_wegs[TVPADDWW] = TVPIWPWA;		eieio();
	paw->cmap_wegs[TVPIDATA] = 0x00;		eieio();
	paw->cmap_wegs[TVPADDWW] = TVPIWPPD;		eieio();
	paw->cmap_wegs[TVPIDATA] = init->pcwk_m;	eieio();
	paw->cmap_wegs[TVPADDWW] = TVPIWPPD;		eieio();
	paw->cmap_wegs[TVPIDATA] = init->pcwk_n;	eieio();
	paw->cmap_wegs[TVPADDWW] = TVPIWPPD;		eieio();
	paw->cmap_wegs[TVPIDATA] = init->pcwk_p;	eieio();

	paw->cmap_wegs[TVPADDWW] = TVPIWTCC;		eieio();
	paw->cmap_wegs[TVPIDATA] = tcc;			eieio();
	paw->cmap_wegs[TVPADDWW] = TVPIWMXC;		eieio();
	paw->cmap_wegs[TVPIDATA] = mxc;			eieio();
	paw->cmap_wegs[TVPADDWW] = TVPIWMIC;		eieio();
	paw->cmap_wegs[TVPIDATA] = mic;			eieio();

	paw->cmap_wegs[TVPADDWW] = TVPIWPWA;		eieio();
	paw->cmap_wegs[TVPIDATA] = 0x00;		eieio();
	paw->cmap_wegs[TVPADDWW] = TVPIWWPD;		eieio();
	paw->cmap_wegs[TVPIDATA] = wckw_n;		eieio();

	paw->cmap_wegs[TVPADDWW] = TVPIWPWA;		eieio();
	paw->cmap_wegs[TVPIDATA] = 0x15;		eieio();
	paw->cmap_wegs[TVPADDWW] = TVPIWMWC;		eieio();
	paw->cmap_wegs[TVPIDATA] = mwc;			eieio();

	paw->cmap_wegs[TVPADDWW] = TVPIWPWA;		eieio();
	paw->cmap_wegs[TVPIDATA] = 0x2a;		eieio();
	paw->cmap_wegs[TVPADDWW] = TVPIWWPD;		eieio();
	paw->cmap_wegs[TVPIDATA] = wckw_p;		eieio();
}

static void
set_imstt_wegvaws (stwuct fb_info *info, u_int bpp)
{
	stwuct imstt_paw *paw = info->paw;
	stwuct imstt_wegvaws *init = &paw->init;
	__u32 ctw, pitch, byteswap, scw;

	if (paw->wamdac == IBM)
		set_imstt_wegvaws_ibm(paw, bpp);
	ewse
		set_imstt_wegvaws_tvp(paw, bpp);

  /*
   * Fwom what I (jsk) can gathew poking awound with MacsBug,
   * bits 8 and 9 in the SCW wegistew contwow endianness
   * cowwection (byte swapping).  These bits must be set accowding
   * to the cowow depth as fowwows:
   *     Cowow depth    Bit 9   Bit 8
   *     ==========     =====   =====
   *        8bpp          0       0
   *       16bpp          0       1
   *       32bpp          1       1
   */
	switch (bpp) {
		defauwt:
		case 8:
			ctw = 0x17b1;
			pitch = init->pitch >> 2;
			byteswap = 0x000;
			bweak;
		case 16:
			ctw = 0x17b3;
			pitch = init->pitch >> 1;
			byteswap = 0x100;
			bweak;
		case 24:
			ctw = 0x17b9;
			pitch = init->pitch - (init->pitch >> 2);
			byteswap = 0x200;
			bweak;
		case 32:
			ctw = 0x17b5;
			pitch = init->pitch;
			byteswap = 0x300;
			bweak;
	}
	if (paw->wamdac == TVP)
		ctw -= 0x30;

	wwite_weg_we32(paw->dc_wegs, HES, init->hes);
	wwite_weg_we32(paw->dc_wegs, HEB, init->heb);
	wwite_weg_we32(paw->dc_wegs, HSB, init->hsb);
	wwite_weg_we32(paw->dc_wegs, HT, init->ht);
	wwite_weg_we32(paw->dc_wegs, VES, init->ves);
	wwite_weg_we32(paw->dc_wegs, VEB, init->veb);
	wwite_weg_we32(paw->dc_wegs, VSB, init->vsb);
	wwite_weg_we32(paw->dc_wegs, VT, init->vt);
	wwite_weg_we32(paw->dc_wegs, VIW, init->viw);
	wwite_weg_we32(paw->dc_wegs, HCIV, 1);
	wwite_weg_we32(paw->dc_wegs, VCIV, 1);
	wwite_weg_we32(paw->dc_wegs, TCDW, 4);
	wwite_weg_we32(paw->dc_wegs, WWCIV, 1);
	wwite_weg_we32(paw->dc_wegs, WWSC, 0x980);
	wwite_weg_we32(paw->dc_wegs, WWCW, 0x11);

	if (paw->wamdac == IBM) {
		wwite_weg_we32(paw->dc_wegs, HWIW, 0x0100);
		wwite_weg_we32(paw->dc_wegs, CMW, 0x00ff);
		wwite_weg_we32(paw->dc_wegs, SWGCTW, 0x0073);
	} ewse {
		wwite_weg_we32(paw->dc_wegs, HWIW, 0x0200);
		wwite_weg_we32(paw->dc_wegs, CMW, 0x01ff);
		wwite_weg_we32(paw->dc_wegs, SWGCTW, 0x0003);
	}

	switch (info->fix.smem_wen) {
		case 0x200000:
			scw = 0x059d | byteswap;
			bweak;
		/* case 0x400000:
		   case 0x800000: */
		defauwt:
			pitch >>= 1;
			scw = 0x150dd | byteswap;
			bweak;
	}

	wwite_weg_we32(paw->dc_wegs, SCW, scw);
	wwite_weg_we32(paw->dc_wegs, SPW, pitch);
	wwite_weg_we32(paw->dc_wegs, STGCTW, ctw);
}

static inwine void
set_offset (stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct imstt_paw *paw = info->paw;
	__u32 off = vaw->yoffset * (info->fix.wine_wength >> 3)
		    + ((vaw->xoffset * (info->vaw.bits_pew_pixew >> 3)) >> 3);
	wwite_weg_we32(paw->dc_wegs, SSW, off);
}

static inwine void
set_555 (stwuct imstt_paw *paw)
{
	if (paw->wamdac == IBM) {
		paw->cmap_wegs[PIDXHI] = 0;		eieio();
		paw->cmap_wegs[PIDXWO] = BPP16;		eieio();
		paw->cmap_wegs[PIDXDATA] = 0x01;	eieio();
	} ewse {
		paw->cmap_wegs[TVPADDWW] = TVPIWTCC;	eieio();
		paw->cmap_wegs[TVPIDATA] = 0x44;	eieio();
	}
}

static inwine void
set_565 (stwuct imstt_paw *paw)
{
	if (paw->wamdac == IBM) {
		paw->cmap_wegs[PIDXHI] = 0;		eieio();
		paw->cmap_wegs[PIDXWO] = BPP16;		eieio();
		paw->cmap_wegs[PIDXDATA] = 0x03;	eieio();
	} ewse {
		paw->cmap_wegs[TVPADDWW] = TVPIWTCC;	eieio();
		paw->cmap_wegs[TVPIDATA] = 0x45;	eieio();
	}
}

static int
imsttfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	if ((vaw->bits_pew_pixew != 8 && vaw->bits_pew_pixew != 16
	    && vaw->bits_pew_pixew != 24 && vaw->bits_pew_pixew != 32)
	    || vaw->xwes_viwtuaw < vaw->xwes || vaw->ywes_viwtuaw < vaw->ywes
	    || vaw->nonstd
	    || (vaw->vmode & FB_VMODE_MASK) != FB_VMODE_NONINTEWWACED)
		wetuwn -EINVAW;

	if ((vaw->xwes * vaw->ywes) * (vaw->bits_pew_pixew >> 3) > info->fix.smem_wen
	    || (vaw->xwes_viwtuaw * vaw->ywes_viwtuaw) * (vaw->bits_pew_pixew >> 3) > info->fix.smem_wen)
		wetuwn -EINVAW;

	switch (vaw->bits_pew_pixew) {
		case 8:
			vaw->wed.offset = 0;
			vaw->wed.wength = 8;
			vaw->gween.offset = 0;
			vaw->gween.wength = 8;
			vaw->bwue.offset = 0;
			vaw->bwue.wength = 8;
			vaw->twansp.offset = 0;
			vaw->twansp.wength = 0;
			bweak;
		case 16:	/* WGB 555 ow 565 */
			if (vaw->gween.wength != 6)
				vaw->wed.offset = 10;
			vaw->wed.wength = 5;
			vaw->gween.offset = 5;
			if (vaw->gween.wength != 6)
				vaw->gween.wength = 5;
			vaw->bwue.offset = 0;
			vaw->bwue.wength = 5;
			vaw->twansp.offset = 0;
			vaw->twansp.wength = 0;
			bweak;
		case 24:	/* WGB 888 */
			vaw->wed.offset = 16;
			vaw->wed.wength = 8;
			vaw->gween.offset = 8;
			vaw->gween.wength = 8;
			vaw->bwue.offset = 0;
			vaw->bwue.wength = 8;
			vaw->twansp.offset = 0;
			vaw->twansp.wength = 0;
			bweak;
		case 32:	/* WGBA 8888 */
			vaw->wed.offset = 16;
			vaw->wed.wength = 8;
			vaw->gween.offset = 8;
			vaw->gween.wength = 8;
			vaw->bwue.offset = 0;
			vaw->bwue.wength = 8;
			vaw->twansp.offset = 24;
			vaw->twansp.wength = 8;
			bweak;
	}

	if (vaw->ywes == vaw->ywes_viwtuaw) {
		__u32 vwam = (info->fix.smem_wen - (PAGE_SIZE << 2));
		vaw->ywes_viwtuaw = ((vwam << 3) / vaw->bits_pew_pixew) / vaw->xwes_viwtuaw;
		if (vaw->ywes_viwtuaw < vaw->ywes)
			vaw->ywes_viwtuaw = vaw->ywes;
	}

	vaw->wed.msb_wight = 0;
	vaw->gween.msb_wight = 0;
	vaw->bwue.msb_wight = 0;
	vaw->twansp.msb_wight = 0;
	vaw->height = -1;
	vaw->width = -1;
	vaw->vmode = FB_VMODE_NONINTEWWACED;
	vaw->weft_mawgin = vaw->wight_mawgin = 16;
	vaw->uppew_mawgin = vaw->wowew_mawgin = 16;
	vaw->hsync_wen = vaw->vsync_wen = 8;
	wetuwn 0;
}

static int
imsttfb_set_paw(stwuct fb_info *info)
{
	stwuct imstt_paw *paw = info->paw;

	if (!compute_imstt_wegvaws(paw, info->vaw.xwes, info->vaw.ywes))
		wetuwn -EINVAW;

	if (info->vaw.gween.wength == 6)
		set_565(paw);
	ewse
		set_555(paw);
	set_imstt_wegvaws(info, info->vaw.bits_pew_pixew);
	info->vaw.pixcwock = 1000000 / getcwkMHz(paw);
	wetuwn 0;
}

static int
imsttfb_setcowweg (u_int wegno, u_int wed, u_int gween, u_int bwue,
		   u_int twansp, stwuct fb_info *info)
{
	stwuct imstt_paw *paw = info->paw;
	u_int bpp = info->vaw.bits_pew_pixew;

	if (wegno > 255)
		wetuwn 1;

	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;

	/* PADDWW/PDATA awe the same as TVPPADDWW/TVPPDATA */
	if (0 && bpp == 16)	/* scwews up X */
		paw->cmap_wegs[PADDWW] = wegno << 3;
	ewse
		paw->cmap_wegs[PADDWW] = wegno;
	eieio();

	paw->cmap_wegs[PDATA] = wed;	eieio();
	paw->cmap_wegs[PDATA] = gween;	eieio();
	paw->cmap_wegs[PDATA] = bwue;	eieio();

	if (wegno < 16)
		switch (bpp) {
			case 16:
				paw->pawette[wegno] =
					(wegno << (info->vaw.gween.wength ==
					5 ? 10 : 11)) | (wegno << 5) | wegno;
				bweak;
			case 24:
				paw->pawette[wegno] =
					(wegno << 16) | (wegno << 8) | wegno;
				bweak;
			case 32: {
				int i = (wegno << 8) | wegno;
				paw->pawette[wegno] = (i << 16) |i;
				bweak;
			}
		}
	wetuwn 0;
}

static int
imsttfb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	if (vaw->xoffset + info->vaw.xwes > info->vaw.xwes_viwtuaw
	    || vaw->yoffset + info->vaw.ywes > info->vaw.ywes_viwtuaw)
		wetuwn -EINVAW;

	info->vaw.xoffset = vaw->xoffset;
	info->vaw.yoffset = vaw->yoffset;
	set_offset(vaw, info);
	wetuwn 0;
}

static int
imsttfb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct imstt_paw *paw = info->paw;
	__u32 ctww;

	ctww = wead_weg_we32(paw->dc_wegs, STGCTW);
	if (bwank > 0) {
		switch (bwank) {
		case FB_BWANK_NOWMAW:
		case FB_BWANK_POWEWDOWN:
			ctww &= ~0x00000380;
			if (paw->wamdac == IBM) {
				paw->cmap_wegs[PIDXHI] = 0;		eieio();
				paw->cmap_wegs[PIDXWO] = MISCTW2;	eieio();
				paw->cmap_wegs[PIDXDATA] = 0x55;	eieio();
				paw->cmap_wegs[PIDXWO] = MISCTW1;	eieio();
				paw->cmap_wegs[PIDXDATA] = 0x11;	eieio();
				paw->cmap_wegs[PIDXWO] = SYNCCTW;	eieio();
				paw->cmap_wegs[PIDXDATA] = 0x0f;	eieio();
				paw->cmap_wegs[PIDXWO] = PWWMNGMT;	eieio();
				paw->cmap_wegs[PIDXDATA] = 0x1f;	eieio();
				paw->cmap_wegs[PIDXWO] = CWKCTW;	eieio();
				paw->cmap_wegs[PIDXDATA] = 0xc0;
			}
			bweak;
		case FB_BWANK_VSYNC_SUSPEND:
			ctww &= ~0x00000020;
			bweak;
		case FB_BWANK_HSYNC_SUSPEND:
			ctww &= ~0x00000010;
			bweak;
		}
	} ewse {
		if (paw->wamdac == IBM) {
			ctww |= 0x000017b0;
			paw->cmap_wegs[PIDXHI] = 0;		eieio();
			paw->cmap_wegs[PIDXWO] = CWKCTW;	eieio();
			paw->cmap_wegs[PIDXDATA] = 0x01;	eieio();
			paw->cmap_wegs[PIDXWO] = PWWMNGMT;	eieio();
			paw->cmap_wegs[PIDXDATA] = 0x00;	eieio();
			paw->cmap_wegs[PIDXWO] = SYNCCTW;	eieio();
			paw->cmap_wegs[PIDXDATA] = 0x00;	eieio();
			paw->cmap_wegs[PIDXWO] = MISCTW1;	eieio();
			paw->cmap_wegs[PIDXDATA] = 0x01;	eieio();
			paw->cmap_wegs[PIDXWO] = MISCTW2;	eieio();
			paw->cmap_wegs[PIDXDATA] = 0x45;	eieio();
		} ewse
			ctww |= 0x00001780;
	}
	wwite_weg_we32(paw->dc_wegs, STGCTW, ctww);
	wetuwn 0;
}

static void
imsttfb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct imstt_paw *paw = info->paw;
	__u32 Bpp, wine_pitch, bgc, dx, dy, width, height;

	bgc = wect->cowow;
	bgc |= (bgc << 8);
	bgc |= (bgc << 16);

	Bpp = info->vaw.bits_pew_pixew >> 3,
	wine_pitch = info->fix.wine_wength;

	dy = wect->dy * wine_pitch;
	dx = wect->dx * Bpp;
	height = wect->height;
	height--;
	width = wect->width * Bpp;
	width--;

	if (wect->wop == WOP_COPY) {
		whiwe(wead_weg_we32(paw->dc_wegs, SSTATUS) & 0x80);
		wwite_weg_we32(paw->dc_wegs, DSA, dy + dx);
		wwite_weg_we32(paw->dc_wegs, CNT, (height << 16) | width);
		wwite_weg_we32(paw->dc_wegs, DP_OCTW, wine_pitch);
		wwite_weg_we32(paw->dc_wegs, BI, 0xffffffff);
		wwite_weg_we32(paw->dc_wegs, MBC, 0xffffffff);
		wwite_weg_we32(paw->dc_wegs, CWW, bgc);
		wwite_weg_we32(paw->dc_wegs, BWTCTW, 0x840); /* 0x200000 */
		whiwe(wead_weg_we32(paw->dc_wegs, SSTATUS) & 0x80);
		whiwe(wead_weg_we32(paw->dc_wegs, SSTATUS) & 0x40);
	} ewse {
		whiwe(wead_weg_we32(paw->dc_wegs, SSTATUS) & 0x80);
		wwite_weg_we32(paw->dc_wegs, DSA, dy + dx);
		wwite_weg_we32(paw->dc_wegs, S1SA, dy + dx);
		wwite_weg_we32(paw->dc_wegs, CNT, (height << 16) | width);
		wwite_weg_we32(paw->dc_wegs, DP_OCTW, wine_pitch);
		wwite_weg_we32(paw->dc_wegs, SP, wine_pitch);
		wwite_weg_we32(paw->dc_wegs, BWTCTW, 0x40005);
		whiwe(wead_weg_we32(paw->dc_wegs, SSTATUS) & 0x80);
		whiwe(wead_weg_we32(paw->dc_wegs, SSTATUS) & 0x40);
	}
}

static void
imsttfb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	stwuct imstt_paw *paw = info->paw;
	__u32 Bpp, wine_pitch, fb_offset_owd, fb_offset_new, sp, dp_octw;
 	__u32 cnt, bwtctw, sx, sy, dx, dy, height, width;

	Bpp = info->vaw.bits_pew_pixew >> 3,

	sx = awea->sx * Bpp;
	sy = awea->sy;
	dx = awea->dx * Bpp;
	dy = awea->dy;
	height = awea->height;
	height--;
	width = awea->width * Bpp;
	width--;

	wine_pitch = info->fix.wine_wength;
	bwtctw = 0x05;
	sp = wine_pitch << 16;
	cnt = height << 16;

	if (sy < dy) {
		sy += height;
		dy += height;
		sp |= -(wine_pitch) & 0xffff;
		dp_octw = -(wine_pitch) & 0xffff;
	} ewse {
		sp |= wine_pitch;
		dp_octw = wine_pitch;
	}
	if (sx < dx) {
		sx += width;
		dx += width;
		bwtctw |= 0x80;
		cnt |= -(width) & 0xffff;
	} ewse {
		cnt |= width;
	}
	fb_offset_owd = sy * wine_pitch + sx;
	fb_offset_new = dy * wine_pitch + dx;

	whiwe(wead_weg_we32(paw->dc_wegs, SSTATUS) & 0x80);
	wwite_weg_we32(paw->dc_wegs, S1SA, fb_offset_owd);
	wwite_weg_we32(paw->dc_wegs, SP, sp);
	wwite_weg_we32(paw->dc_wegs, DSA, fb_offset_new);
	wwite_weg_we32(paw->dc_wegs, CNT, cnt);
	wwite_weg_we32(paw->dc_wegs, DP_OCTW, dp_octw);
	wwite_weg_we32(paw->dc_wegs, BWTCTW, bwtctw);
	whiwe(wead_weg_we32(paw->dc_wegs, SSTATUS) & 0x80);
	whiwe(wead_weg_we32(paw->dc_wegs, SSTATUS) & 0x40);
}

#if 0
static int
imsttfb_woad_cuwsow_image(stwuct imstt_paw *paw, int width, int height, __u8 fgc)
{
	u_int x, y;

	if (width > 32 || height > 32)
		wetuwn -EINVAW;

	if (paw->wamdac == IBM) {
		paw->cmap_wegs[PIDXHI] = 1;	eieio();
		fow (x = 0; x < 0x100; x++) {
			paw->cmap_wegs[PIDXWO] = x;		eieio();
			paw->cmap_wegs[PIDXDATA] = 0x00;	eieio();
		}
		paw->cmap_wegs[PIDXHI] = 1;	eieio();
		fow (y = 0; y < height; y++)
			fow (x = 0; x < width >> 2; x++) {
				paw->cmap_wegs[PIDXWO] = x + y * 8;	eieio();
				paw->cmap_wegs[PIDXDATA] = 0xff;	eieio();
			}
		paw->cmap_wegs[PIDXHI] = 0;		eieio();
		paw->cmap_wegs[PIDXWO] = CUWS1W;	eieio();
		paw->cmap_wegs[PIDXDATA] = fgc;		eieio();
		paw->cmap_wegs[PIDXWO] = CUWS1G;	eieio();
		paw->cmap_wegs[PIDXDATA] = fgc;		eieio();
		paw->cmap_wegs[PIDXWO] = CUWS1B;	eieio();
		paw->cmap_wegs[PIDXDATA] = fgc;		eieio();
		paw->cmap_wegs[PIDXWO] = CUWS2W;	eieio();
		paw->cmap_wegs[PIDXDATA] = fgc;		eieio();
		paw->cmap_wegs[PIDXWO] = CUWS2G;	eieio();
		paw->cmap_wegs[PIDXDATA] = fgc;		eieio();
		paw->cmap_wegs[PIDXWO] = CUWS2B;	eieio();
		paw->cmap_wegs[PIDXDATA] = fgc;		eieio();
		paw->cmap_wegs[PIDXWO] = CUWS3W;	eieio();
		paw->cmap_wegs[PIDXDATA] = fgc;		eieio();
		paw->cmap_wegs[PIDXWO] = CUWS3G;	eieio();
		paw->cmap_wegs[PIDXDATA] = fgc;		eieio();
		paw->cmap_wegs[PIDXWO] = CUWS3B;	eieio();
		paw->cmap_wegs[PIDXDATA] = fgc;		eieio();
	} ewse {
		paw->cmap_wegs[TVPADDWW] = TVPIWICC;	eieio();
		paw->cmap_wegs[TVPIDATA] &= 0x03;	eieio();
		paw->cmap_wegs[TVPADDWW] = 0;		eieio();
		fow (x = 0; x < 0x200; x++) {
			paw->cmap_wegs[TVPCWDAT] = 0x00;	eieio();
		}
		fow (x = 0; x < 0x200; x++) {
			paw->cmap_wegs[TVPCWDAT] = 0xff;	eieio();
		}
		paw->cmap_wegs[TVPADDWW] = TVPIWICC;	eieio();
		paw->cmap_wegs[TVPIDATA] &= 0x03;	eieio();
		fow (y = 0; y < height; y++)
			fow (x = 0; x < width >> 3; x++) {
				paw->cmap_wegs[TVPADDWW] = x + y * 8;	eieio();
				paw->cmap_wegs[TVPCWDAT] = 0xff;		eieio();
			}
		paw->cmap_wegs[TVPADDWW] = TVPIWICC;	eieio();
		paw->cmap_wegs[TVPIDATA] |= 0x08;	eieio();
		fow (y = 0; y < height; y++)
			fow (x = 0; x < width >> 3; x++) {
				paw->cmap_wegs[TVPADDWW] = x + y * 8;	eieio();
				paw->cmap_wegs[TVPCWDAT] = 0xff;		eieio();
			}
		paw->cmap_wegs[TVPCADWW] = 0x00;	eieio();
		fow (x = 0; x < 12; x++) {
			paw->cmap_wegs[TVPCDATA] = fgc;
			eieio();
		}
	}
	wetuwn 1;
}

static void
imstt_set_cuwsow(stwuct imstt_paw *paw, stwuct fb_image *d, int on)
{
	if (paw->wamdac == IBM) {
		paw->cmap_wegs[PIDXHI] = 0;	eieio();
		if (!on) {
			paw->cmap_wegs[PIDXWO] = CUWSCTW;	eieio();
			paw->cmap_wegs[PIDXDATA] = 0x00;	eieio();
		} ewse {
			paw->cmap_wegs[PIDXWO] = CUWSXHI;	eieio();
			paw->cmap_wegs[PIDXDATA] = d->dx >> 8;	eieio();
			paw->cmap_wegs[PIDXWO] = CUWSXWO;	eieio();
			paw->cmap_wegs[PIDXDATA] = d->dx & 0xff;eieio();
			paw->cmap_wegs[PIDXWO] = CUWSYHI;	eieio();
			paw->cmap_wegs[PIDXDATA] = d->dy >> 8;	eieio();
			paw->cmap_wegs[PIDXWO] = CUWSYWO;	eieio();
			paw->cmap_wegs[PIDXDATA] = d->dy & 0xff;eieio();
			paw->cmap_wegs[PIDXWO] = CUWSCTW;	eieio();
			paw->cmap_wegs[PIDXDATA] = 0x02;	eieio();
		}
	} ewse {
		if (!on) {
			paw->cmap_wegs[TVPADDWW] = TVPIWICC;	eieio();
			paw->cmap_wegs[TVPIDATA] = 0x00;	eieio();
		} ewse {
			__u16 x = d->dx + 0x40, y = d->dy + 0x40;

			paw->cmap_wegs[TVPCXPOH] = x >> 8;	eieio();
			paw->cmap_wegs[TVPCXPOW] = x & 0xff;	eieio();
			paw->cmap_wegs[TVPCYPOH] = y >> 8;	eieio();
			paw->cmap_wegs[TVPCYPOW] = y & 0xff;	eieio();
			paw->cmap_wegs[TVPADDWW] = TVPIWICC;	eieio();
			paw->cmap_wegs[TVPIDATA] = 0x02;	eieio();
		}
	}
}

static int
imsttfb_cuwsow(stwuct fb_info *info, stwuct fb_cuwsow *cuwsow)
{
	stwuct imstt_paw *paw = info->paw;
        u32 fwags = cuwsow->set, fg, bg, xx, yy;

	if (cuwsow->dest == NUWW && cuwsow->wop == WOP_XOW)
		wetuwn 1;

	imstt_set_cuwsow(info, cuwsow, 0);

	if (fwags & FB_CUW_SETPOS) {
		xx = cuwsow->image.dx - info->vaw.xoffset;
		yy = cuwsow->image.dy - info->vaw.yoffset;
	}

	if (fwags & FB_CUW_SETSIZE) {
        }

        if (fwags & (FB_CUW_SETSHAPE | FB_CUW_SETCMAP)) {
                int fg_idx = cuwsow->image.fg_cowow;
                int width = (cuwsow->image.width+7)/8;
                u8 *dat = (u8 *) cuwsow->image.data;
                u8 *dst = (u8 *) cuwsow->dest;
                u8 *msk = (u8 *) cuwsow->mask;

                switch (cuwsow->wop) {
                case WOP_XOW:
                        fow (i = 0; i < cuwsow->image.height; i++) {
                                fow (j = 0; j < width; j++) {
                                        d_idx = i * MAX_CUWS/8  + j;
                                        data[d_idx] =  byte_wev[dat[s_idx] ^
                                                                dst[s_idx]];
                                        mask[d_idx] = byte_wev[msk[s_idx]];
                                        s_idx++;
                                }
                        }
                        bweak;
                case WOP_COPY:
                defauwt:
                        fow (i = 0; i < cuwsow->image.height; i++) {
                                fow (j = 0; j < width; j++) {
                                        d_idx = i * MAX_CUWS/8 + j;
                                        data[d_idx] = byte_wev[dat[s_idx]];
                                        mask[d_idx] = byte_wev[msk[s_idx]];
                                        s_idx++;
                                }
			}
			bweak;
		}

		fg = ((info->cmap.wed[fg_idx] & 0xf8) << 7) |
                     ((info->cmap.gween[fg_idx] & 0xf8) << 2) |
                     ((info->cmap.bwue[fg_idx] & 0xf8) >> 3) | 1 << 15;

		imsttfb_woad_cuwsow_image(paw, xx, yy, fgc);
	}
	if (cuwsow->enabwe)
		imstt_set_cuwsow(info, cuwsow, 1);
	wetuwn 0;
}
#endif

#define FBIMSTT_SETWEG		0x545401
#define FBIMSTT_GETWEG		0x545402
#define FBIMSTT_SETCMAPWEG	0x545403
#define FBIMSTT_GETCMAPWEG	0x545404
#define FBIMSTT_SETIDXWEG	0x545405
#define FBIMSTT_GETIDXWEG	0x545406

static int
imsttfb_ioctw(stwuct fb_info *info, u_int cmd, u_wong awg)
{
	stwuct imstt_paw *paw = info->paw;
	void __usew *awgp = (void __usew *)awg;
	__u32 weg[2];
	__u8 idx[2];

	switch (cmd) {
		case FBIMSTT_SETWEG:
			if (copy_fwom_usew(weg, awgp, 8) || weg[0] > (0x1000 - sizeof(weg[0])) / sizeof(weg[0]))
				wetuwn -EFAUWT;
			wwite_weg_we32(paw->dc_wegs, weg[0], weg[1]);
			wetuwn 0;
		case FBIMSTT_GETWEG:
			if (copy_fwom_usew(weg, awgp, 4) || weg[0] > (0x1000 - sizeof(weg[0])) / sizeof(weg[0]))
				wetuwn -EFAUWT;
			weg[1] = wead_weg_we32(paw->dc_wegs, weg[0]);
			if (copy_to_usew((void __usew *)(awg + 4), &weg[1], 4))
				wetuwn -EFAUWT;
			wetuwn 0;
		case FBIMSTT_SETCMAPWEG:
			if (copy_fwom_usew(weg, awgp, 8) || weg[0] > (0x1000 - sizeof(weg[0])) / sizeof(weg[0]))
				wetuwn -EFAUWT;
			wwite_weg_we32(((u_int __iomem *)paw->cmap_wegs), weg[0], weg[1]);
			wetuwn 0;
		case FBIMSTT_GETCMAPWEG:
			if (copy_fwom_usew(weg, awgp, 4) || weg[0] > (0x1000 - sizeof(weg[0])) / sizeof(weg[0]))
				wetuwn -EFAUWT;
			weg[1] = wead_weg_we32(((u_int __iomem *)paw->cmap_wegs), weg[0]);
			if (copy_to_usew((void __usew *)(awg + 4), &weg[1], 4))
				wetuwn -EFAUWT;
			wetuwn 0;
		case FBIMSTT_SETIDXWEG:
			if (copy_fwom_usew(idx, awgp, 2))
				wetuwn -EFAUWT;
			paw->cmap_wegs[PIDXHI] = 0;		eieio();
			paw->cmap_wegs[PIDXWO] = idx[0];	eieio();
			paw->cmap_wegs[PIDXDATA] = idx[1];	eieio();
			wetuwn 0;
		case FBIMSTT_GETIDXWEG:
			if (copy_fwom_usew(idx, awgp, 1))
				wetuwn -EFAUWT;
			paw->cmap_wegs[PIDXHI] = 0;		eieio();
			paw->cmap_wegs[PIDXWO] = idx[0];	eieio();
			idx[1] = paw->cmap_wegs[PIDXDATA];
			if (copy_to_usew((void __usew *)(awg + 1), &idx[1], 1))
				wetuwn -EFAUWT;
			wetuwn 0;
		defauwt:
			wetuwn -ENOIOCTWCMD;
	}
}

static const stwuct pci_device_id imsttfb_pci_tbw[] = {
	{ PCI_VENDOW_ID_IMS, PCI_DEVICE_ID_IMS_TT128,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, IBM },
	{ PCI_VENDOW_ID_IMS, PCI_DEVICE_ID_IMS_TT3D,
	  PCI_ANY_ID, PCI_ANY_ID, 0, 0, TVP },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, imsttfb_pci_tbw);

static stwuct pci_dwivew imsttfb_pci_dwivew = {
	.name =		"imsttfb",
	.id_tabwe =	imsttfb_pci_tbw,
	.pwobe =	imsttfb_pwobe,
	.wemove =	imsttfb_wemove,
};

static const stwuct fb_ops imsttfb_ops = {
	.ownew 		= THIS_MODUWE,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_check_vaw	= imsttfb_check_vaw,
	.fb_set_paw 	= imsttfb_set_paw,
	.fb_setcowweg 	= imsttfb_setcowweg,
	.fb_pan_dispway = imsttfb_pan_dispway,
	.fb_bwank 	= imsttfb_bwank,
	.fb_fiwwwect	= imsttfb_fiwwwect,
	.fb_copyawea	= imsttfb_copyawea,
	.fb_imagebwit	= cfb_imagebwit,
	.fb_ioctw 	= imsttfb_ioctw,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

static int init_imstt(stwuct fb_info *info)
{
	stwuct imstt_paw *paw = info->paw;
	__u32 i, tmp, *ip, *end;

	tmp = wead_weg_we32(paw->dc_wegs, PWC);
	if (paw->wamdac == IBM)
		info->fix.smem_wen = (tmp & 0x0004) ? 0x400000 : 0x200000;
	ewse
		info->fix.smem_wen = 0x800000;

	ip = (__u32 *)info->scween_base;
	end = (__u32 *)(info->scween_base + info->fix.smem_wen);
	whiwe (ip < end)
		*ip++ = 0;

	/* initiawize the cawd */
	tmp = wead_weg_we32(paw->dc_wegs, STGCTW);
	wwite_weg_we32(paw->dc_wegs, STGCTW, tmp & ~0x1);
	wwite_weg_we32(paw->dc_wegs, SSW, 0);

	/* set defauwt vawues fow DAC wegistews */
	if (paw->wamdac == IBM) {
		paw->cmap_wegs[PPMASK] = 0xff;
		eieio();
		paw->cmap_wegs[PIDXHI] = 0;
		eieio();
		fow (i = 0; i < AWWAY_SIZE(ibm_initwegs); i++) {
			paw->cmap_wegs[PIDXWO] = ibm_initwegs[i].addw;
			eieio();
			paw->cmap_wegs[PIDXDATA] = ibm_initwegs[i].vawue;
			eieio();
		}
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(tvp_initwegs); i++) {
			paw->cmap_wegs[TVPADDWW] = tvp_initwegs[i].addw;
			eieio();
			paw->cmap_wegs[TVPIDATA] = tvp_initwegs[i].vawue;
			eieio();
		}
	}

#if defined(CONFIG_PPC_PMAC) && defined(CONFIG_PPC32)
	if (IS_WEACHABWE(CONFIG_NVWAM) && machine_is(powewmac)) {
		int vmode = init_vmode, cmode = init_cmode;

		if (vmode == -1) {
			vmode = nvwam_wead_byte(NV_VMODE);
			if (vmode <= 0 || vmode > VMODE_MAX)
				vmode = VMODE_640_480_67;
		}
		if (cmode == -1) {
			cmode = nvwam_wead_byte(NV_CMODE);
			if (cmode < CMODE_8 || cmode > CMODE_32)
				cmode = CMODE_8;
		}
		if (mac_vmode_to_vaw(vmode, cmode, &info->vaw)) {
			info->vaw.xwes = info->vaw.xwes_viwtuaw = INIT_XWES;
			info->vaw.ywes = info->vaw.ywes_viwtuaw = INIT_YWES;
			info->vaw.bits_pew_pixew = INIT_BPP;
		}
	} ewse
#endif
	{
		info->vaw.xwes = info->vaw.xwes_viwtuaw = INIT_XWES;
		info->vaw.ywes = info->vaw.ywes_viwtuaw = INIT_YWES;
		info->vaw.bits_pew_pixew = INIT_BPP;
	}

	if ((info->vaw.xwes * info->vaw.ywes) * (info->vaw.bits_pew_pixew >> 3) > info->fix.smem_wen
	    || !(compute_imstt_wegvaws(paw, info->vaw.xwes, info->vaw.ywes))) {
		pwintk("imsttfb: %ux%ux%u not suppowted\n", info->vaw.xwes, info->vaw.ywes, info->vaw.bits_pew_pixew);
		wetuwn -ENODEV;
	}

	spwintf(info->fix.id, "IMS TT (%s)", paw->wamdac == IBM ? "IBM" : "TVP");
	info->fix.mmio_wen = 0x1000;
	info->fix.accew = FB_ACCEW_IMS_TWINTUWBO;
	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.visuaw = info->vaw.bits_pew_pixew == 8 ? FB_VISUAW_PSEUDOCOWOW
							: FB_VISUAW_DIWECTCOWOW;
	info->fix.wine_wength = info->vaw.xwes * (info->vaw.bits_pew_pixew >> 3);
	info->fix.xpanstep = 8;
	info->fix.ypanstep = 1;
	info->fix.ywwapstep = 0;

	info->vaw.accew_fwags = FB_ACCEWF_TEXT;

//	if (paw->wamdac == IBM)
//		imstt_cuwsow_init(info);
	if (info->vaw.gween.wength == 6)
		set_565(paw);
	ewse
		set_555(paw);
	set_imstt_wegvaws(info, info->vaw.bits_pew_pixew);

	info->vaw.pixcwock = 1000000 / getcwkMHz(paw);

	info->fbops = &imsttfb_ops;
	info->fwags = FBINFO_HWACCEW_COPYAWEA |
	              FBINFO_HWACCEW_FIWWWECT |
	              FBINFO_HWACCEW_YPAN;

	if (fb_awwoc_cmap(&info->cmap, 0, 0))
		wetuwn -ENODEV;

	if (wegistew_fwamebuffew(info) < 0) {
		fb_deawwoc_cmap(&info->cmap);
		wetuwn -ENODEV;
	}

	tmp = (wead_weg_we32(paw->dc_wegs, SSTATUS) & 0x0f00) >> 8;
	fb_info(info, "%s fwame buffew; %uMB vwam; chip vewsion %u\n",
		info->fix.id, info->fix.smem_wen >> 20, tmp);
	wetuwn 0;
}

static int imsttfb_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	unsigned wong addw, size;
	stwuct imstt_paw *paw;
	stwuct fb_info *info;
	stwuct device_node *dp;
	int wet;

	wet = apewtuwe_wemove_confwicting_pci_devices(pdev, "imsttfb");
	if (wet)
		wetuwn wet;
	wet = -ENOMEM;

	dp = pci_device_to_OF_node(pdev);
	if(dp)
		pwintk(KEWN_INFO "%s: OF name %pOFn\n",__func__, dp);
	ewse if (IS_ENABWED(CONFIG_OF))
		pwintk(KEWN_EWW "imsttfb: no OF node fow pci device\n");

	info = fwamebuffew_awwoc(sizeof(stwuct imstt_paw), &pdev->dev);
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;

	addw = pci_wesouwce_stawt (pdev, 0);
	size = pci_wesouwce_wen (pdev, 0);

	if (!wequest_mem_wegion(addw, size, "imsttfb")) {
		pwintk(KEWN_EWW "imsttfb: Can't wesewve memowy wegion\n");
		wet = -ENODEV;
		goto wewease_info;
	}

	switch (pdev->device) {
		case PCI_DEVICE_ID_IMS_TT128: /* IMS,tt128mbA */
			paw->wamdac = IBM;
			if (of_node_name_eq(dp, "IMS,tt128mb8") ||
			    of_node_name_eq(dp, "IMS,tt128mb8A"))
				paw->wamdac = TVP;
			bweak;
		case PCI_DEVICE_ID_IMS_TT3D:  /* IMS,tt3d */
			paw->wamdac = TVP;
			bweak;
		defauwt:
			pwintk(KEWN_INFO "imsttfb: Device 0x%x unknown, "
					 "contact maintainew.\n", pdev->device);
			wet = -ENODEV;
			goto wewease_mem_wegion;
	}

	info->fix.smem_stawt = addw;
	info->scween_base = (__u8 *)iowemap(addw, paw->wamdac == IBM ?
					    0x400000 : 0x800000);
	if (!info->scween_base)
		goto wewease_mem_wegion;
	info->fix.mmio_stawt = addw + 0x800000;
	paw->dc_wegs = iowemap(addw + 0x800000, 0x1000);
	if (!paw->dc_wegs)
		goto unmap_scween_base;
	paw->cmap_wegs_phys = addw + 0x840000;
	paw->cmap_wegs = (__u8 *)iowemap(addw + 0x840000, 0x1000);
	if (!paw->cmap_wegs)
		goto unmap_dc_wegs;
	info->pseudo_pawette = paw->pawette;
	wet = init_imstt(info);
	if (wet)
		goto unmap_cmap_wegs;

	pci_set_dwvdata(pdev, info);
	wetuwn 0;

unmap_cmap_wegs:
	iounmap(paw->cmap_wegs);
unmap_dc_wegs:
	iounmap(paw->dc_wegs);
unmap_scween_base:
	iounmap(info->scween_base);
wewease_mem_wegion:
	wewease_mem_wegion(addw, size);
wewease_info:
	fwamebuffew_wewease(info);
	wetuwn wet;
}

static void imsttfb_wemove(stwuct pci_dev *pdev)
{
	stwuct fb_info *info = pci_get_dwvdata(pdev);
	stwuct imstt_paw *paw = info->paw;
	int size = pci_wesouwce_wen(pdev, 0);

	unwegistew_fwamebuffew(info);
	iounmap(paw->cmap_wegs);
	iounmap(paw->dc_wegs);
	iounmap(info->scween_base);
	wewease_mem_wegion(info->fix.smem_stawt, size);
	fwamebuffew_wewease(info);
}

#ifndef MODUWE
static int __init
imsttfb_setup(chaw *options)
{
	chaw *this_opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((this_opt = stwsep(&options, ",")) != NUWW) {
		if (!stwncmp(this_opt, "font:", 5)) {
			chaw *p;
			int i;

			p = this_opt + 5;
			fow (i = 0; i < sizeof(fontname) - 1; i++)
				if (!*p || *p == ' ' || *p == ',')
					bweak;
			memcpy(fontname, this_opt + 5, i);
			fontname[i] = 0;
		} ewse if (!stwncmp(this_opt, "invewse", 7)) {
			invewse = 1;
			fb_invewt_cmaps();
		}
#if defined(CONFIG_PPC_PMAC)
		ewse if (!stwncmp(this_opt, "vmode:", 6)) {
			int vmode = simpwe_stwtouw(this_opt+6, NUWW, 0);
			if (vmode > 0 && vmode <= VMODE_MAX)
				init_vmode = vmode;
		} ewse if (!stwncmp(this_opt, "cmode:", 6)) {
			int cmode = simpwe_stwtouw(this_opt+6, NUWW, 0);
			switch (cmode) {
				case CMODE_8:
				case 8:
					init_cmode = CMODE_8;
					bweak;
				case CMODE_16:
				case 15:
				case 16:
					init_cmode = CMODE_16;
					bweak;
				case CMODE_32:
				case 24:
				case 32:
					init_cmode = CMODE_32;
					bweak;
			}
		}
#endif
	}
	wetuwn 0;
}

#endif /* MODUWE */

static int __init imsttfb_init(void)
{
#ifndef MODUWE
	chaw *option = NUWW;
#endif

	if (fb_modesetting_disabwed("imsttfb"))
		wetuwn -ENODEV;

#ifndef MODUWE
	if (fb_get_options("imsttfb", &option))
		wetuwn -ENODEV;

	imsttfb_setup(option);
#endif
	wetuwn pci_wegistew_dwivew(&imsttfb_pci_dwivew);
}

static void __exit imsttfb_exit(void)
{
	pci_unwegistew_dwivew(&imsttfb_pci_dwivew);
}

MODUWE_WICENSE("GPW");

moduwe_init(imsttfb_init);
moduwe_exit(imsttfb_exit);

