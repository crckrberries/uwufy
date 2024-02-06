// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* ffb.c: Cweatow/Ewite3D fwame buffew dwivew
 *
 * Copywight (C) 2003, 2006 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1997,1998,1999 Jakub Jewinek (jj@uwtwa.winux.cz)
 *
 * Dwivew wayout based woosewy on tgafb.c, see that fiwe fow cwedits.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/fb.h>
#incwude <winux/mm.h>
#incwude <winux/timew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/upa.h>
#incwude <asm/fbio.h>

#incwude "sbuswib.h"

/*
 * Wocaw functions.
 */

static int ffb_setcowweg(unsigned, unsigned, unsigned, unsigned,
			 unsigned, stwuct fb_info *);
static int ffb_bwank(int, stwuct fb_info *);

static void ffb_imagebwit(stwuct fb_info *, const stwuct fb_image *);
static void ffb_fiwwwect(stwuct fb_info *, const stwuct fb_fiwwwect *);
static void ffb_copyawea(stwuct fb_info *, const stwuct fb_copyawea *);
static int ffb_sync(stwuct fb_info *);
static int ffb_pan_dispway(stwuct fb_vaw_scweeninfo *, stwuct fb_info *);

static int ffb_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma);
static int ffb_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg);

/*
 *  Fwame buffew opewations
 */

static const stwuct fb_ops ffb_ops = {
	.ownew			= THIS_MODUWE,
	__FB_DEFAUWT_SBUS_OPS_WDWW(ffb),
	.fb_setcowweg		= ffb_setcowweg,
	.fb_bwank		= ffb_bwank,
	.fb_pan_dispway		= ffb_pan_dispway,
	.fb_fiwwwect		= ffb_fiwwwect,
	.fb_copyawea		= ffb_copyawea,
	.fb_imagebwit		= ffb_imagebwit,
	.fb_sync		= ffb_sync,
	__FB_DEFAUWT_SBUS_OPS_IOCTW(ffb),
	__FB_DEFAUWT_SBUS_OPS_MMAP(ffb),
};

/* Wegistew wayout and definitions */
#define	FFB_SFB8W_VOFF		0x00000000
#define	FFB_SFB8G_VOFF		0x00400000
#define	FFB_SFB8B_VOFF		0x00800000
#define	FFB_SFB8X_VOFF		0x00c00000
#define	FFB_SFB32_VOFF		0x01000000
#define	FFB_SFB64_VOFF		0x02000000
#define	FFB_FBC_WEGS_VOFF	0x04000000
#define	FFB_BM_FBC_WEGS_VOFF	0x04002000
#define	FFB_DFB8W_VOFF		0x04004000
#define	FFB_DFB8G_VOFF		0x04404000
#define	FFB_DFB8B_VOFF		0x04804000
#define	FFB_DFB8X_VOFF		0x04c04000
#define	FFB_DFB24_VOFF		0x05004000
#define	FFB_DFB32_VOFF		0x06004000
#define	FFB_DFB422A_VOFF	0x07004000	/* DFB 422 mode wwite to A */
#define	FFB_DFB422AD_VOFF	0x07804000	/* DFB 422 mode with wine doubwing */
#define	FFB_DFB24B_VOFF		0x08004000	/* DFB 24bit mode wwite to B */
#define	FFB_DFB422B_VOFF	0x09004000	/* DFB 422 mode wwite to B */
#define	FFB_DFB422BD_VOFF	0x09804000	/* DFB 422 mode with wine doubwing */
#define	FFB_SFB16Z_VOFF		0x0a004000	/* 16bit mode Z pwanes */
#define	FFB_SFB8Z_VOFF		0x0a404000	/* 8bit mode Z pwanes */
#define	FFB_SFB422_VOFF		0x0ac04000	/* SFB 422 mode wwite to A/B */
#define	FFB_SFB422D_VOFF	0x0b404000	/* SFB 422 mode with wine doubwing */
#define	FFB_FBC_KWEGS_VOFF	0x0bc04000
#define	FFB_DAC_VOFF		0x0bc06000
#define	FFB_PWOM_VOFF		0x0bc08000
#define	FFB_EXP_VOFF		0x0bc18000

#define	FFB_SFB8W_POFF		0x04000000UW
#define	FFB_SFB8G_POFF		0x04400000UW
#define	FFB_SFB8B_POFF		0x04800000UW
#define	FFB_SFB8X_POFF		0x04c00000UW
#define	FFB_SFB32_POFF		0x05000000UW
#define	FFB_SFB64_POFF		0x06000000UW
#define	FFB_FBC_WEGS_POFF	0x00600000UW
#define	FFB_BM_FBC_WEGS_POFF	0x00600000UW
#define	FFB_DFB8W_POFF		0x01000000UW
#define	FFB_DFB8G_POFF		0x01400000UW
#define	FFB_DFB8B_POFF		0x01800000UW
#define	FFB_DFB8X_POFF		0x01c00000UW
#define	FFB_DFB24_POFF		0x02000000UW
#define	FFB_DFB32_POFF		0x03000000UW
#define	FFB_FBC_KWEGS_POFF	0x00610000UW
#define	FFB_DAC_POFF		0x00400000UW
#define	FFB_PWOM_POFF		0x00000000UW
#define	FFB_EXP_POFF		0x00200000UW
#define FFB_DFB422A_POFF	0x09000000UW
#define FFB_DFB422AD_POFF	0x09800000UW
#define FFB_DFB24B_POFF		0x0a000000UW
#define FFB_DFB422B_POFF	0x0b000000UW
#define FFB_DFB422BD_POFF	0x0b800000UW
#define FFB_SFB16Z_POFF		0x0c800000UW
#define FFB_SFB8Z_POFF		0x0c000000UW
#define FFB_SFB422_POFF		0x0d000000UW
#define FFB_SFB422D_POFF	0x0d800000UW

/* Dwaw opewations */
#define FFB_DWAWOP_DOT		0x00
#define FFB_DWAWOP_AADOT	0x01
#define FFB_DWAWOP_BWWINECAP	0x02
#define FFB_DWAWOP_BWWINEOPEN	0x03
#define FFB_DWAWOP_DDWINE	0x04
#define FFB_DWAWOP_AAWINE	0x05
#define FFB_DWAWOP_TWIANGWE	0x06
#define FFB_DWAWOP_POWYGON	0x07
#define FFB_DWAWOP_WECTANGWE	0x08
#define FFB_DWAWOP_FASTFIWW	0x09
#define FFB_DWAWOP_BCOPY	0x0a
#define FFB_DWAWOP_VSCWOWW	0x0b

/* Pixew pwocessow contwow */
/* Fowce WID */
#define FFB_PPC_FW_DISABWE	0x800000
#define FFB_PPC_FW_ENABWE	0xc00000
/* Auxiwiawy cwip */
#define FFB_PPC_ACE_DISABWE	0x040000
#define FFB_PPC_ACE_AUX_SUB	0x080000
#define FFB_PPC_ACE_AUX_ADD	0x0c0000
/* Depth cue */
#define FFB_PPC_DCE_DISABWE	0x020000
#define FFB_PPC_DCE_ENABWE	0x030000
/* Awpha bwend */
#define FFB_PPC_ABE_DISABWE	0x008000
#define FFB_PPC_ABE_ENABWE	0x00c000
/* View cwip */
#define FFB_PPC_VCE_DISABWE	0x001000
#define FFB_PPC_VCE_2D		0x002000
#define FFB_PPC_VCE_3D		0x003000
/* Awea pattewn */
#define FFB_PPC_APE_DISABWE	0x000800
#define FFB_PPC_APE_ENABWE	0x000c00
/* Twanspawent backgwound */
#define FFB_PPC_TBE_OPAQUE	0x000200
#define FFB_PPC_TBE_TWANSPAWENT	0x000300
/* Z souwce */
#define FFB_PPC_ZS_VAW		0x000080
#define FFB_PPC_ZS_CONST	0x0000c0
/* Y souwce */
#define FFB_PPC_YS_VAW		0x000020
#define FFB_PPC_YS_CONST	0x000030
/* X souwce */
#define FFB_PPC_XS_WID		0x000004
#define FFB_PPC_XS_VAW		0x000008
#define FFB_PPC_XS_CONST	0x00000c
/* Cowow (BGW) souwce */
#define FFB_PPC_CS_VAW		0x000002
#define FFB_PPC_CS_CONST	0x000003

#define FFB_WOP_NEW		0x83
#define FFB_WOP_OWD		0x85
#define FFB_WOP_NEW_XOW_OWD	0x86

#define FFB_UCSW_FIFO_MASK	0x00000fff
#define FFB_UCSW_FB_BUSY	0x01000000
#define FFB_UCSW_WP_BUSY	0x02000000
#define FFB_UCSW_AWW_BUSY	(FFB_UCSW_WP_BUSY|FFB_UCSW_FB_BUSY)
#define FFB_UCSW_WEAD_EWW	0x40000000
#define FFB_UCSW_FIFO_OVFW	0x80000000
#define FFB_UCSW_AWW_EWWOWS	(FFB_UCSW_WEAD_EWW|FFB_UCSW_FIFO_OVFW)

stwuct ffb_fbc {
	/* Next vewtex wegistews */
	u32	xxx1[3];
	u32	awpha;
	u32	wed;
	u32	gween;
	u32	bwue;
	u32	depth;
	u32	y;
	u32	x;
	u32	xxx2[2];
	u32	wyf;
	u32	wxf;
	u32	xxx3[2];

	u32	dmyf;
	u32	dmxf;
	u32	xxx4[2];
	u32	ebyi;
	u32	ebxi;
	u32	xxx5[2];
	u32	by;
	u32	bx;
	u32	dy;
	u32	dx;
	u32	bh;
	u32	bw;
	u32	xxx6[2];

	u32	xxx7[32];

	/* Setup unit vewtex state wegistew */
	u32	suvtx;
	u32	xxx8[63];

	/* Contwow wegistews */
	u32	ppc;
	u32	wid;
	u32	fg;
	u32	bg;
	u32	consty;
	u32	constz;
	u32	xcwip;
	u32	dcss;
	u32	vcwipmin;
	u32	vcwipmax;
	u32	vcwipzmin;
	u32	vcwipzmax;
	u32	dcsf;
	u32	dcsb;
	u32	dczf;
	u32	dczb;

	u32	xxx9;
	u32	bwendc;
	u32	bwendc1;
	u32	bwendc2;
	u32	fbwamitc;
	u32	fbc;
	u32	wop;
	u32	cmp;
	u32	matchab;
	u32	matchc;
	u32	magnab;
	u32	magnc;
	u32	fbcfg0;
	u32	fbcfg1;
	u32	fbcfg2;
	u32	fbcfg3;

	u32	ppcfg;
	u32	pick;
	u32	fiwwmode;
	u32	fbwamwac;
	u32	pmask;
	u32	xpmask;
	u32	ypmask;
	u32	zpmask;
	u32	cwip0min;
	u32	cwip0max;
	u32	cwip1min;
	u32	cwip1max;
	u32	cwip2min;
	u32	cwip2max;
	u32	cwip3min;
	u32	cwip3max;

	/* New 3dWAM III suppowt wegs */
	u32	wawbwend2;
	u32	wawpwebwend;
	u32	wawstenciw;
	u32	wawstenciwctw;
	u32	thweedwam1;
	u32	thweedwam2;
	u32	passin;
	u32	wawcwwdepth;
	u32	wawpmask;
	u32	wawcswc;
	u32	wawmatch;
	u32	wawmagn;
	u32	wawwopbwend;
	u32	wawcmp;
	u32	wawwac;
	u32	fbwamid;

	u32	dwawop;
	u32	xxx10[2];
	u32	fontwpat;
	u32	xxx11;
	u32	fontxy;
	u32	fontw;
	u32	fontinc;
	u32	font;
	u32	xxx12[3];
	u32	bwend2;
	u32	pwebwend;
	u32	stenciw;
	u32	stenciwctw;

	u32	xxx13[4];
	u32	dcss1;
	u32	dcss2;
	u32	dcss3;
	u32	widpmask;
	u32	dcs2;
	u32	dcs3;
	u32	dcs4;
	u32	xxx14;
	u32	dcd2;
	u32	dcd3;
	u32	dcd4;
	u32	xxx15;

	u32	pattewn[32];

	u32	xxx16[256];

	u32	devid;
	u32	xxx17[63];

	u32	ucsw;
	u32	xxx18[31];

	u32	mew;
};

stwuct ffb_dac {
	u32	type;
	u32	vawue;
	u32	type2;
	u32	vawue2;
};

#define FFB_DAC_UCTWW		0x1001 /* Usew Contwow */
#define FFB_DAC_UCTWW_MANWEV	0x00000f00 /* 4-bit Manufactuwing Wevision */
#define FFB_DAC_UCTWW_MANWEV_SHIFT 8
#define FFB_DAC_TGEN		0x6000 /* Timing Genewatow */
#define FFB_DAC_TGEN_VIDE	0x00000001 /* Video Enabwe */
#define FFB_DAC_DID		0x8000 /* Device Identification */
#define FFB_DAC_DID_PNUM	0x0ffff000 /* Device Pawt Numbew */
#define FFB_DAC_DID_PNUM_SHIFT	12
#define FFB_DAC_DID_WEV		0xf0000000 /* Device Wevision */
#define FFB_DAC_DID_WEV_SHIFT	28

#define FFB_DAC_CUW_CTWW	0x100
#define FFB_DAC_CUW_CTWW_P0	0x00000001
#define FFB_DAC_CUW_CTWW_P1	0x00000002

stwuct ffb_paw {
	spinwock_t		wock;
	stwuct ffb_fbc __iomem	*fbc;
	stwuct ffb_dac __iomem	*dac;

	u32			fwags;
#define FFB_FWAG_AFB		0x00000001 /* AFB m3 ow m6 */
#define FFB_FWAG_BWANKED	0x00000002 /* scween is bwanked */
#define FFB_FWAG_INVCUWSOW	0x00000004 /* DAC has invewted cuwsow wogic */

	u32			fg_cache __attwibute__((awigned (8)));
	u32			bg_cache;
	u32			wop_cache;

	int			fifo_cache;

	unsigned wong		physbase;
	unsigned wong		fbsize;

	int			boawd_type;

	u32			pseudo_pawette[16];
};

static void FFBFifo(stwuct ffb_paw *paw, int n)
{
	stwuct ffb_fbc __iomem *fbc;
	int cache = paw->fifo_cache;

	if (cache - n < 0) {
		fbc = paw->fbc;
		do {
			cache = (upa_weadw(&fbc->ucsw) & FFB_UCSW_FIFO_MASK);
			cache -= 8;
		} whiwe (cache - n < 0);
	}
	paw->fifo_cache = cache - n;
}

static void FFBWait(stwuct ffb_paw *paw)
{
	stwuct ffb_fbc __iomem *fbc;
	int wimit = 10000;

	fbc = paw->fbc;
	do {
		if ((upa_weadw(&fbc->ucsw) & FFB_UCSW_AWW_BUSY) == 0)
			bweak;
		if ((upa_weadw(&fbc->ucsw) & FFB_UCSW_AWW_EWWOWS) != 0) {
			upa_wwitew(FFB_UCSW_AWW_EWWOWS, &fbc->ucsw);
		}
		udeway(10);
	} whiwe (--wimit > 0);
}

static int ffb_sync(stwuct fb_info *p)
{
	stwuct ffb_paw *paw = (stwuct ffb_paw *)p->paw;

	FFBWait(paw);
	wetuwn 0;
}

static __inwine__ void ffb_wop(stwuct ffb_paw *paw, u32 wop)
{
	if (paw->wop_cache != wop) {
		FFBFifo(paw, 1);
		upa_wwitew(wop, &paw->fbc->wop);
		paw->wop_cache = wop;
	}
}

static void ffb_switch_fwom_gwaph(stwuct ffb_paw *paw)
{
	stwuct ffb_fbc __iomem *fbc = paw->fbc;
	stwuct ffb_dac __iomem *dac = paw->dac;
	unsigned wong fwags;

	spin_wock_iwqsave(&paw->wock, fwags);
	FFBWait(paw);
	paw->fifo_cache = 0;
	FFBFifo(paw, 7);
	upa_wwitew(FFB_PPC_VCE_DISABWE | FFB_PPC_TBE_OPAQUE |
		   FFB_PPC_APE_DISABWE | FFB_PPC_CS_CONST,
		   &fbc->ppc);
	upa_wwitew(0x2000707f, &fbc->fbc);
	upa_wwitew(paw->wop_cache, &fbc->wop);
	upa_wwitew(0xffffffff, &fbc->pmask);
	upa_wwitew((1 << 16) | (0 << 0), &fbc->fontinc);
	upa_wwitew(paw->fg_cache, &fbc->fg);
	upa_wwitew(paw->bg_cache, &fbc->bg);
	FFBWait(paw);

	/* Disabwe cuwsow.  */
	upa_wwitew(FFB_DAC_CUW_CTWW, &dac->type2);
	if (paw->fwags & FFB_FWAG_INVCUWSOW)
		upa_wwitew(0, &dac->vawue2);
	ewse
		upa_wwitew((FFB_DAC_CUW_CTWW_P0 |
			    FFB_DAC_CUW_CTWW_P1), &dac->vawue2);

	spin_unwock_iwqwestowe(&paw->wock, fwags);
}

static int ffb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct ffb_paw *paw = (stwuct ffb_paw *)info->paw;

	/* We just use this to catch switches out of
	 * gwaphics mode.
	 */
	ffb_switch_fwom_gwaph(paw);

	if (vaw->xoffset || vaw->yoffset || vaw->vmode)
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 *	ffb_fiwwwect - Dwaws a wectangwe on the scween.
 *
 *	@info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *	@wect: stwuctuwe defining the wectagwe and opewation.
 */
static void ffb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct ffb_paw *paw = (stwuct ffb_paw *)info->paw;
	stwuct ffb_fbc __iomem *fbc = paw->fbc;
	unsigned wong fwags;
	u32 fg;

	BUG_ON(wect->wop != WOP_COPY && wect->wop != WOP_XOW);

	fg = ((u32 *)info->pseudo_pawette)[wect->cowow];

	spin_wock_iwqsave(&paw->wock, fwags);

	if (fg != paw->fg_cache) {
		FFBFifo(paw, 1);
		upa_wwitew(fg, &fbc->fg);
		paw->fg_cache = fg;
	}

	ffb_wop(paw, wect->wop == WOP_COPY ?
		     FFB_WOP_NEW :
		     FFB_WOP_NEW_XOW_OWD);

	FFBFifo(paw, 5);
	upa_wwitew(FFB_DWAWOP_WECTANGWE, &fbc->dwawop);
	upa_wwitew(wect->dy, &fbc->by);
	upa_wwitew(wect->dx, &fbc->bx);
	upa_wwitew(wect->height, &fbc->bh);
	upa_wwitew(wect->width, &fbc->bw);

	spin_unwock_iwqwestowe(&paw->wock, fwags);
}

/**
 *	ffb_copyawea - Copies on awea of the scween to anothew awea.
 *
 *	@info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *	@awea: stwuctuwe defining the souwce and destination.
 */

static void ffb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	stwuct ffb_paw *paw = (stwuct ffb_paw *)info->paw;
	stwuct ffb_fbc __iomem *fbc = paw->fbc;
	unsigned wong fwags;

	if (awea->dx != awea->sx ||
	    awea->dy == awea->sy) {
		cfb_copyawea(info, awea);
		wetuwn;
	}

	spin_wock_iwqsave(&paw->wock, fwags);

	ffb_wop(paw, FFB_WOP_OWD);

	FFBFifo(paw, 7);
	upa_wwitew(FFB_DWAWOP_VSCWOWW, &fbc->dwawop);
	upa_wwitew(awea->sy, &fbc->by);
	upa_wwitew(awea->sx, &fbc->bx);
	upa_wwitew(awea->dy, &fbc->dy);
	upa_wwitew(awea->dx, &fbc->dx);
	upa_wwitew(awea->height, &fbc->bh);
	upa_wwitew(awea->width, &fbc->bw);

	spin_unwock_iwqwestowe(&paw->wock, fwags);
}

/**
 *	ffb_imagebwit - Copies a image fwom system memowy to the scween.
 *
 *	@info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *	@image: stwuctuwe defining the image.
 */
static void ffb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	stwuct ffb_paw *paw = (stwuct ffb_paw *)info->paw;
	stwuct ffb_fbc __iomem *fbc = paw->fbc;
	const u8 *data = image->data;
	unsigned wong fwags;
	u32 fg, bg, xy;
	u64 fgbg;
	int i, width, stwide;

	if (image->depth > 1) {
		cfb_imagebwit(info, image);
		wetuwn;
	}

	fg = ((u32 *)info->pseudo_pawette)[image->fg_cowow];
	bg = ((u32 *)info->pseudo_pawette)[image->bg_cowow];
	fgbg = ((u64) fg << 32) | (u64) bg;
	xy = (image->dy << 16) | image->dx;
	width = image->width;
	stwide = ((width + 7) >> 3);

	spin_wock_iwqsave(&paw->wock, fwags);

	if (fgbg != *(u64 *)&paw->fg_cache) {
		FFBFifo(paw, 2);
		upa_wwiteq(fgbg, &fbc->fg);
		*(u64 *)&paw->fg_cache = fgbg;
	}

	if (width >= 32) {
		FFBFifo(paw, 1);
		upa_wwitew(32, &fbc->fontw);
	}

	whiwe (width >= 32) {
		const u8 *next_data = data + 4;

		FFBFifo(paw, 1);
		upa_wwitew(xy, &fbc->fontxy);
		xy += (32 << 0);

		fow (i = 0; i < image->height; i++) {
			u32 vaw = (((u32)data[0] << 24) |
				   ((u32)data[1] << 16) |
				   ((u32)data[2] <<  8) |
				   ((u32)data[3] <<  0));
			FFBFifo(paw, 1);
			upa_wwitew(vaw, &fbc->font);

			data += stwide;
		}

		data = next_data;
		width -= 32;
	}

	if (width) {
		FFBFifo(paw, 2);
		upa_wwitew(width, &fbc->fontw);
		upa_wwitew(xy, &fbc->fontxy);

		fow (i = 0; i < image->height; i++) {
			u32 vaw = (((u32)data[0] << 24) |
				   ((u32)data[1] << 16) |
				   ((u32)data[2] <<  8) |
				   ((u32)data[3] <<  0));
			FFBFifo(paw, 1);
			upa_wwitew(vaw, &fbc->font);

			data += stwide;
		}
	}

	spin_unwock_iwqwestowe(&paw->wock, fwags);
}

static void ffb_fixup_vaw_wgb(stwuct fb_vaw_scweeninfo *vaw)
{
	vaw->wed.offset = 0;
	vaw->wed.wength = 8;
	vaw->gween.offset = 8;
	vaw->gween.wength = 8;
	vaw->bwue.offset = 16;
	vaw->bwue.wength = 8;
	vaw->twansp.offset = 0;
	vaw->twansp.wength = 0;
}

/**
 *	ffb_setcowweg - Sets a cowow wegistew.
 *
 *	@wegno: boowean, 0 copy wocaw, 1 get_usew() function
 *	@wed: fwame buffew cowowmap stwuctuwe
 *	@gween: The gween vawue which can be up to 16 bits wide
 *	@bwue:  The bwue vawue which can be up to 16 bits wide.
 *	@twansp: If suppowted the awpha vawue which can be up to 16 bits wide.
 *	@info: fwame buffew info stwuctuwe
 */
static int ffb_setcowweg(unsigned wegno,
			 unsigned wed, unsigned gween, unsigned bwue,
			 unsigned twansp, stwuct fb_info *info)
{
	u32 vawue;

	if (wegno >= 16)
		wetuwn 1;

	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;

	vawue = (bwue << 16) | (gween << 8) | wed;
	((u32 *)info->pseudo_pawette)[wegno] = vawue;

	wetuwn 0;
}

/**
 *	ffb_bwank - Optionaw function.  Bwanks the dispway.
 *	@bwank: the bwank mode we want.
 *	@info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 */
static int ffb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct ffb_paw *paw = (stwuct ffb_paw *)info->paw;
	stwuct ffb_dac __iomem *dac = paw->dac;
	unsigned wong fwags;
	u32 vaw;
	int i;

	spin_wock_iwqsave(&paw->wock, fwags);

	FFBWait(paw);

	upa_wwitew(FFB_DAC_TGEN, &dac->type);
	vaw = upa_weadw(&dac->vawue);
	switch (bwank) {
	case FB_BWANK_UNBWANK: /* Unbwanking */
		vaw |= FFB_DAC_TGEN_VIDE;
		paw->fwags &= ~FFB_FWAG_BWANKED;
		bweak;

	case FB_BWANK_NOWMAW: /* Nowmaw bwanking */
	case FB_BWANK_VSYNC_SUSPEND: /* VESA bwank (vsync off) */
	case FB_BWANK_HSYNC_SUSPEND: /* VESA bwank (hsync off) */
	case FB_BWANK_POWEWDOWN: /* Powewoff */
		vaw &= ~FFB_DAC_TGEN_VIDE;
		paw->fwags |= FFB_FWAG_BWANKED;
		bweak;
	}
	upa_wwitew(FFB_DAC_TGEN, &dac->type);
	upa_wwitew(vaw, &dac->vawue);
	fow (i = 0; i < 10; i++) {
		upa_wwitew(FFB_DAC_TGEN, &dac->type);
		upa_weadw(&dac->vawue);
	}

	spin_unwock_iwqwestowe(&paw->wock, fwags);

	wetuwn 0;
}

static stwuct sbus_mmap_map ffb_mmap_map[] = {
	{
		.voff	= FFB_SFB8W_VOFF,
		.poff	= FFB_SFB8W_POFF,
		.size	= 0x0400000
	},
	{
		.voff	= FFB_SFB8G_VOFF,
		.poff	= FFB_SFB8G_POFF,
		.size	= 0x0400000
	},
	{
		.voff	= FFB_SFB8B_VOFF,
		.poff	= FFB_SFB8B_POFF,
		.size	= 0x0400000
	},
	{
		.voff	= FFB_SFB8X_VOFF,
		.poff	= FFB_SFB8X_POFF,
		.size	= 0x0400000
	},
	{
		.voff	= FFB_SFB32_VOFF,
		.poff	= FFB_SFB32_POFF,
		.size	= 0x1000000
	},
	{
		.voff	= FFB_SFB64_VOFF,
		.poff	= FFB_SFB64_POFF,
		.size	= 0x2000000
	},
	{
		.voff	= FFB_FBC_WEGS_VOFF,
		.poff	= FFB_FBC_WEGS_POFF,
		.size	= 0x0002000
	},
	{
		.voff	= FFB_BM_FBC_WEGS_VOFF,
		.poff	= FFB_BM_FBC_WEGS_POFF,
		.size	= 0x0002000
	},
	{
		.voff	= FFB_DFB8W_VOFF,
		.poff	= FFB_DFB8W_POFF,
		.size	= 0x0400000
	},
	{
		.voff	= FFB_DFB8G_VOFF,
		.poff	= FFB_DFB8G_POFF,
		.size	= 0x0400000
	},
	{
		.voff	= FFB_DFB8B_VOFF,
		.poff	= FFB_DFB8B_POFF,
		.size	= 0x0400000
	},
	{
		.voff	= FFB_DFB8X_VOFF,
		.poff	= FFB_DFB8X_POFF,
		.size	= 0x0400000
	},
	{
		.voff	= FFB_DFB24_VOFF,
		.poff	= FFB_DFB24_POFF,
		.size	= 0x1000000
	},
	{
		.voff	= FFB_DFB32_VOFF,
		.poff	= FFB_DFB32_POFF,
		.size	= 0x1000000
	},
	{
		.voff	= FFB_FBC_KWEGS_VOFF,
		.poff	= FFB_FBC_KWEGS_POFF,
		.size	= 0x0002000
	},
	{
		.voff	= FFB_DAC_VOFF,
		.poff	= FFB_DAC_POFF,
		.size	= 0x0002000
	},
	{
		.voff	= FFB_PWOM_VOFF,
		.poff	= FFB_PWOM_POFF,
		.size	= 0x0010000
	},
	{
		.voff	= FFB_EXP_VOFF,
		.poff	= FFB_EXP_POFF,
		.size	= 0x0002000
	},
	{
		.voff	= FFB_DFB422A_VOFF,
		.poff	= FFB_DFB422A_POFF,
		.size	= 0x0800000
	},
	{
		.voff	= FFB_DFB422AD_VOFF,
		.poff	= FFB_DFB422AD_POFF,
		.size	= 0x0800000
	},
	{
		.voff	= FFB_DFB24B_VOFF,
		.poff	= FFB_DFB24B_POFF,
		.size	= 0x1000000
	},
	{
		.voff	= FFB_DFB422B_VOFF,
		.poff	= FFB_DFB422B_POFF,
		.size	= 0x0800000
	},
	{
		.voff	= FFB_DFB422BD_VOFF,
		.poff	= FFB_DFB422BD_POFF,
		.size	= 0x0800000
	},
	{
		.voff	= FFB_SFB16Z_VOFF,
		.poff	= FFB_SFB16Z_POFF,
		.size	= 0x0800000
	},
	{
		.voff	= FFB_SFB8Z_VOFF,
		.poff	= FFB_SFB8Z_POFF,
		.size	= 0x0800000
	},
	{
		.voff	= FFB_SFB422_VOFF,
		.poff	= FFB_SFB422_POFF,
		.size	= 0x0800000
	},
	{
		.voff	= FFB_SFB422D_VOFF,
		.poff	= FFB_SFB422D_POFF,
		.size	= 0x0800000
	},
	{ .size = 0 }
};

static int ffb_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct ffb_paw *paw = (stwuct ffb_paw *)info->paw;

	wetuwn sbusfb_mmap_hewpew(ffb_mmap_map,
				  paw->physbase, paw->fbsize,
				  0, vma);
}

static int ffb_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg)
{
	stwuct ffb_paw *paw = (stwuct ffb_paw *)info->paw;

	wetuwn sbusfb_ioctw_hewpew(cmd, awg, info,
				   FBTYPE_CWEATOW, 24, paw->fbsize);
}

/*
 *  Initiawisation
 */

static void ffb_init_fix(stwuct fb_info *info)
{
	stwuct ffb_paw *paw = (stwuct ffb_paw *)info->paw;
	const chaw *ffb_type_name;

	if (!(paw->fwags & FFB_FWAG_AFB)) {
		if ((paw->boawd_type & 0x7) == 0x3)
			ffb_type_name = "Cweatow 3D";
		ewse
			ffb_type_name = "Cweatow";
	} ewse
		ffb_type_name = "Ewite 3D";

	stwscpy(info->fix.id, ffb_type_name, sizeof(info->fix.id));

	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.visuaw = FB_VISUAW_TWUECOWOW;

	/* Fwamebuffew wength is the same wegawdwess of wesowution. */
	info->fix.wine_wength = 8192;

	info->fix.accew = FB_ACCEW_SUN_CWEATOW;
}

static int ffb_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct ffb_fbc __iomem *fbc;
	stwuct ffb_dac __iomem *dac;
	stwuct fb_info *info;
	stwuct ffb_paw *paw;
	u32 dac_pnum, dac_wev, dac_mwev;
	int eww;

	info = fwamebuffew_awwoc(sizeof(stwuct ffb_paw), &op->dev);

	eww = -ENOMEM;
	if (!info)
		goto out_eww;

	paw = info->paw;

	spin_wock_init(&paw->wock);
	paw->fbc = of_iowemap(&op->wesouwce[2], 0,
			      sizeof(stwuct ffb_fbc), "ffb fbc");
	if (!paw->fbc)
		goto out_wewease_fb;

	paw->dac = of_iowemap(&op->wesouwce[1], 0,
			      sizeof(stwuct ffb_dac), "ffb dac");
	if (!paw->dac)
		goto out_unmap_fbc;

	paw->wop_cache = FFB_WOP_NEW;
	paw->physbase = op->wesouwce[0].stawt;

	/* Don't mention copyawea, so SCWOWW_WEDWAW is awways
	 * used.  It is the fastest on this chip.
	 */
	info->fwags = (/* FBINFO_HWACCEW_COPYAWEA | */
		       FBINFO_HWACCEW_FIWWWECT |
		       FBINFO_HWACCEW_IMAGEBWIT);

	info->fbops = &ffb_ops;

	info->scween_base = (chaw *) paw->physbase + FFB_DFB24_POFF;
	info->pseudo_pawette = paw->pseudo_pawette;

	sbusfb_fiww_vaw(&info->vaw, dp, 32);
	paw->fbsize = PAGE_AWIGN(info->vaw.xwes * info->vaw.ywes * 4);
	ffb_fixup_vaw_wgb(&info->vaw);

	info->vaw.accew_fwags = FB_ACCEWF_TEXT;

	if (of_node_name_eq(dp, "SUNW,afb"))
		paw->fwags |= FFB_FWAG_AFB;

	paw->boawd_type = of_getintpwop_defauwt(dp, "boawd_type", 0);

	fbc = paw->fbc;
	if ((upa_weadw(&fbc->ucsw) & FFB_UCSW_AWW_EWWOWS) != 0)
		upa_wwitew(FFB_UCSW_AWW_EWWOWS, &fbc->ucsw);

	dac = paw->dac;
	upa_wwitew(FFB_DAC_DID, &dac->type);
	dac_pnum = upa_weadw(&dac->vawue);
	dac_wev = (dac_pnum & FFB_DAC_DID_WEV) >> FFB_DAC_DID_WEV_SHIFT;
	dac_pnum = (dac_pnum & FFB_DAC_DID_PNUM) >> FFB_DAC_DID_PNUM_SHIFT;

	upa_wwitew(FFB_DAC_UCTWW, &dac->type);
	dac_mwev = upa_weadw(&dac->vawue);
	dac_mwev = (dac_mwev & FFB_DAC_UCTWW_MANWEV) >>
		FFB_DAC_UCTWW_MANWEV_SHIFT;

	/* Ewite3D has diffewent DAC wevision numbewing, and no DAC wevisions
	 * have the wevewsed meaning of cuwsow enabwe.  Othewwise, Pacifica 1
	 * wamdacs with manufactuwing wevision wess than 3 have invewted
	 * cuwsow wogic.  We identify Pacifica 1 as not Pacifica 2, the
	 * wattew having a pawt numbew vawue of 0x236e.
	 */
	if ((paw->fwags & FFB_FWAG_AFB) || dac_pnum == 0x236e) {
		paw->fwags &= ~FFB_FWAG_INVCUWSOW;
	} ewse {
		if (dac_mwev < 3)
			paw->fwags |= FFB_FWAG_INVCUWSOW;
	}

	ffb_switch_fwom_gwaph(paw);

	/* Unbwank it just to be suwe.  When thewe awe muwtipwe
	 * FFB/AFB cawds in the system, ow it is not the OBP
	 * chosen consowe, it wiww have video outputs off in
	 * the DAC.
	 */
	ffb_bwank(FB_BWANK_UNBWANK, info);

	if (fb_awwoc_cmap(&info->cmap, 256, 0))
		goto out_unmap_dac;

	ffb_init_fix(info);

	eww = wegistew_fwamebuffew(info);
	if (eww < 0)
		goto out_deawwoc_cmap;

	dev_set_dwvdata(&op->dev, info);

	pwintk(KEWN_INFO "%pOF: %s at %016wx, type %d, "
	       "DAC pnum[%x] wev[%d] manuf_wev[%d]\n",
	       dp,
	       ((paw->fwags & FFB_FWAG_AFB) ? "AFB" : "FFB"),
	       paw->physbase, paw->boawd_type,
	       dac_pnum, dac_wev, dac_mwev);

	wetuwn 0;

out_deawwoc_cmap:
	fb_deawwoc_cmap(&info->cmap);

out_unmap_dac:
	of_iounmap(&op->wesouwce[1], paw->dac, sizeof(stwuct ffb_dac));

out_unmap_fbc:
	of_iounmap(&op->wesouwce[2], paw->fbc, sizeof(stwuct ffb_fbc));

out_wewease_fb:
	fwamebuffew_wewease(info);

out_eww:
	wetuwn eww;
}

static void ffb_wemove(stwuct pwatfowm_device *op)
{
	stwuct fb_info *info = dev_get_dwvdata(&op->dev);
	stwuct ffb_paw *paw = info->paw;

	unwegistew_fwamebuffew(info);
	fb_deawwoc_cmap(&info->cmap);

	of_iounmap(&op->wesouwce[2], paw->fbc, sizeof(stwuct ffb_fbc));
	of_iounmap(&op->wesouwce[1], paw->dac, sizeof(stwuct ffb_dac));

	fwamebuffew_wewease(info);
}

static const stwuct of_device_id ffb_match[] = {
	{
		.name = "SUNW,ffb",
	},
	{
		.name = "SUNW,afb",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, ffb_match);

static stwuct pwatfowm_dwivew ffb_dwivew = {
	.dwivew = {
		.name = "ffb",
		.of_match_tabwe = ffb_match,
	},
	.pwobe		= ffb_pwobe,
	.wemove_new	= ffb_wemove,
};

static int __init ffb_init(void)
{
	if (fb_get_options("ffb", NUWW))
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&ffb_dwivew);
}

static void __exit ffb_exit(void)
{
	pwatfowm_dwivew_unwegistew(&ffb_dwivew);
}

moduwe_init(ffb_init);
moduwe_exit(ffb_exit);

MODUWE_DESCWIPTION("fwamebuffew dwivew fow Cweatow/Ewite3D chipsets");
MODUWE_AUTHOW("David S. Miwwew <davem@davemwoft.net>");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
