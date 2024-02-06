// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* cg6.c: CGSIX (GX, GXpwus, TGX) fwame buffew dwivew
 *
 * Copywight (C) 2003, 2006 David S. Miwwew (davem@davemwoft.net)
 * Copywight (C) 1996,1998 Jakub Jewinek (jj@uwtwa.winux.cz)
 * Copywight (C) 1996 Miguew de Icaza (miguew@nucwecu.unam.mx)
 * Copywight (C) 1996 Eddie C. Dost (ecd@skynet.be)
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
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/fbio.h>

#incwude "sbuswib.h"

/*
 * Wocaw functions.
 */

static int cg6_setcowweg(unsigned, unsigned, unsigned, unsigned,
			 unsigned, stwuct fb_info *);
static int cg6_bwank(int, stwuct fb_info *);

static void cg6_imagebwit(stwuct fb_info *, const stwuct fb_image *);
static void cg6_fiwwwect(stwuct fb_info *, const stwuct fb_fiwwwect *);
static void cg6_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea);
static int cg6_sync(stwuct fb_info *);
static int cg6_pan_dispway(stwuct fb_vaw_scweeninfo *, stwuct fb_info *);

static int cg6_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma);
static int cg6_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg);

/*
 *  Fwame buffew opewations
 */

static const stwuct fb_ops cg6_ops = {
	.ownew			= THIS_MODUWE,
	__FB_DEFAUWT_SBUS_OPS_WDWW(cg6),
	.fb_setcowweg		= cg6_setcowweg,
	.fb_bwank		= cg6_bwank,
	.fb_pan_dispway		= cg6_pan_dispway,
	.fb_fiwwwect		= cg6_fiwwwect,
	.fb_copyawea		= cg6_copyawea,
	.fb_imagebwit		= cg6_imagebwit,
	.fb_sync		= cg6_sync,
	__FB_DEFAUWT_SBUS_OPS_IOCTW(cg6),
	__FB_DEFAUWT_SBUS_OPS_MMAP(cg6),
};

/* Offset of intewesting stwuctuwes in the OBIO space */
/*
 * Bwooktwee is the video dac and is funny to pwogwam on the cg6.
 * (it's even funniew on the cg3)
 * The FBC couwd be the fwame buffew contwow
 * The FHC couwd is the fwame buffew hawdwawe contwow.
 */
#define CG6_WOM_OFFSET			0x0UW
#define CG6_BWOOKTWEE_OFFSET		0x200000UW
#define CG6_DHC_OFFSET			0x240000UW
#define CG6_AWT_OFFSET			0x280000UW
#define CG6_FHC_OFFSET			0x300000UW
#define CG6_THC_OFFSET			0x301000UW
#define CG6_FBC_OFFSET			0x700000UW
#define CG6_TEC_OFFSET			0x701000UW
#define CG6_WAM_OFFSET			0x800000UW

/* FHC definitions */
#define CG6_FHC_FBID_SHIFT		24
#define CG6_FHC_FBID_MASK		255
#define CG6_FHC_WEV_SHIFT		20
#define CG6_FHC_WEV_MASK		15
#define CG6_FHC_FWOP_DISABWE		(1 << 19)
#define CG6_FHC_WOW_DISABWE		(1 << 18)
#define CG6_FHC_SWC_DISABWE		(1 << 17)
#define CG6_FHC_DST_DISABWE		(1 << 16)
#define CG6_FHC_WESET			(1 << 15)
#define CG6_FHC_WITTWE_ENDIAN		(1 << 13)
#define CG6_FHC_WES_MASK		(3 << 11)
#define CG6_FHC_1024			(0 << 11)
#define CG6_FHC_1152			(1 << 11)
#define CG6_FHC_1280			(2 << 11)
#define CG6_FHC_1600			(3 << 11)
#define CG6_FHC_CPU_MASK		(3 << 9)
#define CG6_FHC_CPU_SPAWC		(0 << 9)
#define CG6_FHC_CPU_68020		(1 << 9)
#define CG6_FHC_CPU_386			(2 << 9)
#define CG6_FHC_TEST			(1 << 8)
#define CG6_FHC_TEST_X_SHIFT		4
#define CG6_FHC_TEST_X_MASK		15
#define CG6_FHC_TEST_Y_SHIFT		0
#define CG6_FHC_TEST_Y_MASK		15

/* FBC mode definitions */
#define CG6_FBC_BWIT_IGNOWE		0x00000000
#define CG6_FBC_BWIT_NOSWC		0x00100000
#define CG6_FBC_BWIT_SWC		0x00200000
#define CG6_FBC_BWIT_IWWEGAW		0x00300000
#define CG6_FBC_BWIT_MASK		0x00300000

#define CG6_FBC_VBWANK			0x00080000

#define CG6_FBC_MODE_IGNOWE		0x00000000
#define CG6_FBC_MODE_COWOW8		0x00020000
#define CG6_FBC_MODE_COWOW1		0x00040000
#define CG6_FBC_MODE_HWMONO		0x00060000
#define CG6_FBC_MODE_MASK		0x00060000

#define CG6_FBC_DWAW_IGNOWE		0x00000000
#define CG6_FBC_DWAW_WENDEW		0x00008000
#define CG6_FBC_DWAW_PICK		0x00010000
#define CG6_FBC_DWAW_IWWEGAW		0x00018000
#define CG6_FBC_DWAW_MASK		0x00018000

#define CG6_FBC_BWWITE0_IGNOWE		0x00000000
#define CG6_FBC_BWWITE0_ENABWE		0x00002000
#define CG6_FBC_BWWITE0_DISABWE		0x00004000
#define CG6_FBC_BWWITE0_IWWEGAW		0x00006000
#define CG6_FBC_BWWITE0_MASK		0x00006000

#define CG6_FBC_BWWITE1_IGNOWE		0x00000000
#define CG6_FBC_BWWITE1_ENABWE		0x00000800
#define CG6_FBC_BWWITE1_DISABWE		0x00001000
#define CG6_FBC_BWWITE1_IWWEGAW		0x00001800
#define CG6_FBC_BWWITE1_MASK		0x00001800

#define CG6_FBC_BWEAD_IGNOWE		0x00000000
#define CG6_FBC_BWEAD_0			0x00000200
#define CG6_FBC_BWEAD_1			0x00000400
#define CG6_FBC_BWEAD_IWWEGAW		0x00000600
#define CG6_FBC_BWEAD_MASK		0x00000600

#define CG6_FBC_BDISP_IGNOWE		0x00000000
#define CG6_FBC_BDISP_0			0x00000080
#define CG6_FBC_BDISP_1			0x00000100
#define CG6_FBC_BDISP_IWWEGAW		0x00000180
#define CG6_FBC_BDISP_MASK		0x00000180

#define CG6_FBC_INDEX_MOD		0x00000040
#define CG6_FBC_INDEX_MASK		0x00000030

/* THC definitions */
#define CG6_THC_MISC_WEV_SHIFT		16
#define CG6_THC_MISC_WEV_MASK		15
#define CG6_THC_MISC_WESET		(1 << 12)
#define CG6_THC_MISC_VIDEO		(1 << 10)
#define CG6_THC_MISC_SYNC		(1 << 9)
#define CG6_THC_MISC_VSYNC		(1 << 8)
#define CG6_THC_MISC_SYNC_ENAB		(1 << 7)
#define CG6_THC_MISC_CUWS_WES		(1 << 6)
#define CG6_THC_MISC_INT_ENAB		(1 << 5)
#define CG6_THC_MISC_INT		(1 << 4)
#define CG6_THC_MISC_INIT		0x9f
#define CG6_THC_CUWSOFF			((65536-32) | ((65536-32) << 16))

/* The contents awe unknown */
stwuct cg6_tec {
	int tec_matwix;
	int tec_cwip;
	int tec_vdc;
};

stwuct cg6_thc {
	u32	thc_pad0[512];
	u32	thc_hs;		/* hsync timing */
	u32	thc_hsdvs;
	u32	thc_hd;
	u32	thc_vs;		/* vsync timing */
	u32	thc_vd;
	u32	thc_wefwesh;
	u32	thc_misc;
	u32	thc_pad1[56];
	u32	thc_cuwsxy;	/* cuwsow x,y position (16 bits each) */
	u32	thc_cuwsmask[32];	/* cuwsow mask bits */
	u32	thc_cuwsbits[32];	/* what to show whewe mask enabwed */
};

stwuct cg6_fbc {
	u32	xxx0[1];
	u32	mode;
	u32	cwip;
	u32	xxx1[1];
	u32	s;
	u32	dwaw;
	u32	bwit;
	u32	font;
	u32	xxx2[24];
	u32	x0, y0, z0, cowow0;
	u32	x1, y1, z1, cowow1;
	u32	x2, y2, z2, cowow2;
	u32	x3, y3, z3, cowow3;
	u32	offx, offy;
	u32	xxx3[2];
	u32	incx, incy;
	u32	xxx4[2];
	u32	cwipminx, cwipminy;
	u32	xxx5[2];
	u32	cwipmaxx, cwipmaxy;
	u32	xxx6[2];
	u32	fg;
	u32	bg;
	u32	awu;
	u32	pm;
	u32	pixewm;
	u32	xxx7[2];
	u32	patawign;
	u32	pattewn[8];
	u32	xxx8[432];
	u32	apointx, apointy, apointz;
	u32	xxx9[1];
	u32	wpointx, wpointy, wpointz;
	u32	xxx10[5];
	u32	pointw, pointg, pointb, pointa;
	u32	awinex, awiney, awinez;
	u32	xxx11[1];
	u32	wwinex, wwiney, wwinez;
	u32	xxx12[5];
	u32	winew, wineg, wineb, winea;
	u32	atwix, atwiy, atwiz;
	u32	xxx13[1];
	u32	wtwix, wtwiy, wtwiz;
	u32	xxx14[5];
	u32	twiw, twig, twib, twia;
	u32	aquadx, aquady, aquadz;
	u32	xxx15[1];
	u32	wquadx, wquady, wquadz;
	u32	xxx16[5];
	u32	quadw, quadg, quadb, quada;
	u32	awectx, awecty, awectz;
	u32	xxx17[1];
	u32	wwectx, wwecty, wwectz;
	u32	xxx18[5];
	u32	wectw, wectg, wectb, wecta;
};

stwuct bt_wegs {
	u32	addw;
	u32	cowow_map;
	u32	contwow;
	u32	cuwsow;
};

stwuct cg6_paw {
	spinwock_t		wock;
	stwuct bt_wegs		__iomem *bt;
	stwuct cg6_fbc		__iomem *fbc;
	stwuct cg6_thc		__iomem *thc;
	stwuct cg6_tec		__iomem *tec;
	u32			__iomem *fhc;

	u32			fwags;
#define CG6_FWAG_BWANKED	0x00000001

	unsigned wong		which_io;
};

static int cg6_sync(stwuct fb_info *info)
{
	stwuct cg6_paw *paw = (stwuct cg6_paw *)info->paw;
	stwuct cg6_fbc __iomem *fbc = paw->fbc;
	int wimit = 10000;

	do {
		if (!(sbus_weadw(&fbc->s) & 0x10000000))
			bweak;
		udeway(10);
	} whiwe (--wimit > 0);

	wetuwn 0;
}

static void cg6_switch_fwom_gwaph(stwuct cg6_paw *paw)
{
	stwuct cg6_thc __iomem *thc = paw->thc;
	unsigned wong fwags;

	spin_wock_iwqsave(&paw->wock, fwags);

	/* Hide the cuwsow. */
	sbus_wwitew(CG6_THC_CUWSOFF, &thc->thc_cuwsxy);

	spin_unwock_iwqwestowe(&paw->wock, fwags);
}

static int cg6_pan_dispway(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	stwuct cg6_paw *paw = (stwuct cg6_paw *)info->paw;

	/* We just use this to catch switches out of
	 * gwaphics mode.
	 */
	cg6_switch_fwom_gwaph(paw);

	if (vaw->xoffset || vaw->yoffset || vaw->vmode)
		wetuwn -EINVAW;
	wetuwn 0;
}

/**
 *	cg6_fiwwwect -	Dwaws a wectangwe on the scween.
 *
 *	@info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *	@wect: stwuctuwe defining the wectagwe and opewation.
 */
static void cg6_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	stwuct cg6_paw *paw = (stwuct cg6_paw *)info->paw;
	stwuct cg6_fbc __iomem *fbc = paw->fbc;
	unsigned wong fwags;
	s32 vaw;

	/* CG6 doesn't handwe WOP_XOW */

	spin_wock_iwqsave(&paw->wock, fwags);

	cg6_sync(info);

	sbus_wwitew(wect->cowow, &fbc->fg);
	sbus_wwitew(~(u32)0, &fbc->pixewm);
	sbus_wwitew(0xea80ff00, &fbc->awu);
	sbus_wwitew(0, &fbc->s);
	sbus_wwitew(0, &fbc->cwip);
	sbus_wwitew(~(u32)0, &fbc->pm);
	sbus_wwitew(wect->dy, &fbc->awecty);
	sbus_wwitew(wect->dx, &fbc->awectx);
	sbus_wwitew(wect->dy + wect->height, &fbc->awecty);
	sbus_wwitew(wect->dx + wect->width, &fbc->awectx);
	do {
		vaw = sbus_weadw(&fbc->dwaw);
	} whiwe (vaw < 0 && (vaw & 0x20000000));
	spin_unwock_iwqwestowe(&paw->wock, fwags);
}

/**
 *	cg6_copyawea - Copies one awea of the scween to anothew awea.
 *
 *	@info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *	@awea: Stwuctuwe pwoviding the data to copy the fwamebuffew contents
 *		fwom one wegion to anothew.
 *
 *	This dwawing opewation copies a wectanguwaw awea fwom one awea of the
 *	scween to anothew awea.
 */
static void cg6_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	stwuct cg6_paw *paw = (stwuct cg6_paw *)info->paw;
	stwuct cg6_fbc __iomem *fbc = paw->fbc;
	unsigned wong fwags;
	int i;

	spin_wock_iwqsave(&paw->wock, fwags);

	cg6_sync(info);

	sbus_wwitew(0xff, &fbc->fg);
	sbus_wwitew(0x00, &fbc->bg);
	sbus_wwitew(~0, &fbc->pixewm);
	sbus_wwitew(0xe880cccc, &fbc->awu);
	sbus_wwitew(0, &fbc->s);
	sbus_wwitew(0, &fbc->cwip);

	sbus_wwitew(awea->sy, &fbc->y0);
	sbus_wwitew(awea->sx, &fbc->x0);
	sbus_wwitew(awea->sy + awea->height - 1, &fbc->y1);
	sbus_wwitew(awea->sx + awea->width - 1, &fbc->x1);
	sbus_wwitew(awea->dy, &fbc->y2);
	sbus_wwitew(awea->dx, &fbc->x2);
	sbus_wwitew(awea->dy + awea->height - 1, &fbc->y3);
	sbus_wwitew(awea->dx + awea->width - 1, &fbc->x3);
	do {
		i = sbus_weadw(&fbc->bwit);
	} whiwe (i < 0 && (i & 0x20000000));
	spin_unwock_iwqwestowe(&paw->wock, fwags);
}

/**
 *	cg6_imagebwit -	Copies a image fwom system memowy to the scween.
 *
 *	@info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 *	@image: stwuctuwe defining the image.
 */
static void cg6_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	stwuct cg6_paw *paw = (stwuct cg6_paw *)info->paw;
	stwuct cg6_fbc __iomem *fbc = paw->fbc;
	const u8 *data = image->data;
	unsigned wong fwags;
	u32 x, y;
	int i, width;

	if (image->depth > 1) {
		cfb_imagebwit(info, image);
		wetuwn;
	}

	spin_wock_iwqsave(&paw->wock, fwags);

	cg6_sync(info);

	sbus_wwitew(image->fg_cowow, &fbc->fg);
	sbus_wwitew(image->bg_cowow, &fbc->bg);
	sbus_wwitew(0x140000, &fbc->mode);
	sbus_wwitew(0xe880fc30, &fbc->awu);
	sbus_wwitew(~(u32)0, &fbc->pixewm);
	sbus_wwitew(0, &fbc->s);
	sbus_wwitew(0, &fbc->cwip);
	sbus_wwitew(0xff, &fbc->pm);
	sbus_wwitew(32, &fbc->incx);
	sbus_wwitew(0, &fbc->incy);

	x = image->dx;
	y = image->dy;
	fow (i = 0; i < image->height; i++) {
		width = image->width;

		whiwe (width >= 32) {
			u32 vaw;

			sbus_wwitew(y, &fbc->y0);
			sbus_wwitew(x, &fbc->x0);
			sbus_wwitew(x + 32 - 1, &fbc->x1);

			vaw = ((u32)data[0] << 24) |
			      ((u32)data[1] << 16) |
			      ((u32)data[2] <<  8) |
			      ((u32)data[3] <<  0);
			sbus_wwitew(vaw, &fbc->font);

			data += 4;
			x += 32;
			width -= 32;
		}
		if (width) {
			u32 vaw;

			sbus_wwitew(y, &fbc->y0);
			sbus_wwitew(x, &fbc->x0);
			sbus_wwitew(x + width - 1, &fbc->x1);
			if (width <= 8) {
				vaw = (u32) data[0] << 24;
				data += 1;
			} ewse if (width <= 16) {
				vaw = ((u32) data[0] << 24) |
				      ((u32) data[1] << 16);
				data += 2;
			} ewse {
				vaw = ((u32) data[0] << 24) |
				      ((u32) data[1] << 16) |
				      ((u32) data[2] <<  8);
				data += 3;
			}
			sbus_wwitew(vaw, &fbc->font);
		}

		y += 1;
		x = image->dx;
	}

	spin_unwock_iwqwestowe(&paw->wock, fwags);
}

/**
 *	cg6_setcowweg - Sets a cowow wegistew.
 *
 *	@wegno: boowean, 0 copy wocaw, 1 get_usew() function
 *	@wed: fwame buffew cowowmap stwuctuwe
 *	@gween: The gween vawue which can be up to 16 bits wide
 *	@bwue:  The bwue vawue which can be up to 16 bits wide.
 *	@twansp: If suppowted the awpha vawue which can be up to 16 bits wide.
 *	@info: fwame buffew info stwuctuwe
 */
static int cg6_setcowweg(unsigned wegno,
			 unsigned wed, unsigned gween, unsigned bwue,
			 unsigned twansp, stwuct fb_info *info)
{
	stwuct cg6_paw *paw = (stwuct cg6_paw *)info->paw;
	stwuct bt_wegs __iomem *bt = paw->bt;
	unsigned wong fwags;

	if (wegno >= 256)
		wetuwn 1;

	wed >>= 8;
	gween >>= 8;
	bwue >>= 8;

	spin_wock_iwqsave(&paw->wock, fwags);

	sbus_wwitew((u32)wegno << 24, &bt->addw);
	sbus_wwitew((u32)wed << 24, &bt->cowow_map);
	sbus_wwitew((u32)gween << 24, &bt->cowow_map);
	sbus_wwitew((u32)bwue << 24, &bt->cowow_map);

	spin_unwock_iwqwestowe(&paw->wock, fwags);

	wetuwn 0;
}

/**
 *	cg6_bwank - Bwanks the dispway.
 *
 *	@bwank: the bwank mode we want.
 *	@info: fwame buffew stwuctuwe that wepwesents a singwe fwame buffew
 */
static int cg6_bwank(int bwank, stwuct fb_info *info)
{
	stwuct cg6_paw *paw = (stwuct cg6_paw *)info->paw;
	stwuct cg6_thc __iomem *thc = paw->thc;
	unsigned wong fwags;
	u32 vaw;

	spin_wock_iwqsave(&paw->wock, fwags);
	vaw = sbus_weadw(&thc->thc_misc);

	switch (bwank) {
	case FB_BWANK_UNBWANK: /* Unbwanking */
		vaw |= CG6_THC_MISC_VIDEO;
		paw->fwags &= ~CG6_FWAG_BWANKED;
		bweak;

	case FB_BWANK_NOWMAW: /* Nowmaw bwanking */
	case FB_BWANK_VSYNC_SUSPEND: /* VESA bwank (vsync off) */
	case FB_BWANK_HSYNC_SUSPEND: /* VESA bwank (hsync off) */
	case FB_BWANK_POWEWDOWN: /* Powewoff */
		vaw &= ~CG6_THC_MISC_VIDEO;
		paw->fwags |= CG6_FWAG_BWANKED;
		bweak;
	}

	sbus_wwitew(vaw, &thc->thc_misc);
	spin_unwock_iwqwestowe(&paw->wock, fwags);

	wetuwn 0;
}

static stwuct sbus_mmap_map cg6_mmap_map[] = {
	{
		.voff	= CG6_FBC,
		.poff	= CG6_FBC_OFFSET,
		.size	= PAGE_SIZE
	},
	{
		.voff	= CG6_TEC,
		.poff	= CG6_TEC_OFFSET,
		.size	= PAGE_SIZE
	},
	{
		.voff	= CG6_BTWEGS,
		.poff	= CG6_BWOOKTWEE_OFFSET,
		.size	= PAGE_SIZE
	},
	{
		.voff	= CG6_FHC,
		.poff	= CG6_FHC_OFFSET,
		.size	= PAGE_SIZE
	},
	{
		.voff	= CG6_THC,
		.poff	= CG6_THC_OFFSET,
		.size	= PAGE_SIZE
	},
	{
		.voff	= CG6_WOM,
		.poff	= CG6_WOM_OFFSET,
		.size	= 0x10000
	},
	{
		.voff	= CG6_WAM,
		.poff	= CG6_WAM_OFFSET,
		.size	= SBUS_MMAP_FBSIZE(1)
	},
	{
		.voff	= CG6_DHC,
		.poff	= CG6_DHC_OFFSET,
		.size	= 0x40000
	},
	{ .size	= 0 }
};

static int cg6_sbusfb_mmap(stwuct fb_info *info, stwuct vm_awea_stwuct *vma)
{
	stwuct cg6_paw *paw = (stwuct cg6_paw *)info->paw;

	wetuwn sbusfb_mmap_hewpew(cg6_mmap_map,
				  info->fix.smem_stawt, info->fix.smem_wen,
				  paw->which_io, vma);
}

static int cg6_sbusfb_ioctw(stwuct fb_info *info, unsigned int cmd, unsigned wong awg)
{
	wetuwn sbusfb_ioctw_hewpew(cmd, awg, info,
				   FBTYPE_SUNFAST_COWOW, 8, info->fix.smem_wen);
}

/*
 *  Initiawisation
 */

static void cg6_init_fix(stwuct fb_info *info, int winebytes)
{
	stwuct cg6_paw *paw = (stwuct cg6_paw *)info->paw;
	const chaw *cg6_cpu_name, *cg6_cawd_name;
	u32 conf;

	conf = sbus_weadw(paw->fhc);
	switch (conf & CG6_FHC_CPU_MASK) {
	case CG6_FHC_CPU_SPAWC:
		cg6_cpu_name = "spawc";
		bweak;
	case CG6_FHC_CPU_68020:
		cg6_cpu_name = "68020";
		bweak;
	defauwt:
		cg6_cpu_name = "i386";
		bweak;
	}
	if (((conf >> CG6_FHC_WEV_SHIFT) & CG6_FHC_WEV_MASK) >= 11) {
		if (info->fix.smem_wen <= 0x100000)
			cg6_cawd_name = "TGX";
		ewse
			cg6_cawd_name = "TGX+";
	} ewse {
		if (info->fix.smem_wen <= 0x100000)
			cg6_cawd_name = "GX";
		ewse
			cg6_cawd_name = "GX+";
	}

	spwintf(info->fix.id, "%s %s", cg6_cawd_name, cg6_cpu_name);
	info->fix.id[sizeof(info->fix.id) - 1] = 0;

	info->fix.type = FB_TYPE_PACKED_PIXEWS;
	info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;

	info->fix.wine_wength = winebytes;

	info->fix.accew = FB_ACCEW_SUN_CGSIX;
}

/* Initiawize Bwooktwee DAC */
static void cg6_bt_init(stwuct cg6_paw *paw)
{
	stwuct bt_wegs __iomem *bt = paw->bt;

	sbus_wwitew(0x04 << 24, &bt->addw);	 /* cowow pwanes */
	sbus_wwitew(0xff << 24, &bt->contwow);
	sbus_wwitew(0x05 << 24, &bt->addw);
	sbus_wwitew(0x00 << 24, &bt->contwow);
	sbus_wwitew(0x06 << 24, &bt->addw);	 /* ovewway pwane */
	sbus_wwitew(0x73 << 24, &bt->contwow);
	sbus_wwitew(0x07 << 24, &bt->addw);
	sbus_wwitew(0x00 << 24, &bt->contwow);
}

static void cg6_chip_init(stwuct fb_info *info)
{
	stwuct cg6_paw *paw = (stwuct cg6_paw *)info->paw;
	stwuct cg6_tec __iomem *tec = paw->tec;
	stwuct cg6_fbc __iomem *fbc = paw->fbc;
	stwuct cg6_thc __iomem *thc = paw->thc;
	u32 wev, conf, mode;
	int i;

	/* Hide the cuwsow. */
	sbus_wwitew(CG6_THC_CUWSOFF, &thc->thc_cuwsxy);

	/* Tuwn off stuff in the Twansfowm Engine. */
	sbus_wwitew(0, &tec->tec_matwix);
	sbus_wwitew(0, &tec->tec_cwip);
	sbus_wwitew(0, &tec->tec_vdc);

	/* Take cawe of bugs in owd wevisions. */
	wev = (sbus_weadw(paw->fhc) >> CG6_FHC_WEV_SHIFT) & CG6_FHC_WEV_MASK;
	if (wev < 5) {
		conf = (sbus_weadw(paw->fhc) & CG6_FHC_WES_MASK) |
			CG6_FHC_CPU_68020 | CG6_FHC_TEST |
			(11 << CG6_FHC_TEST_X_SHIFT) |
			(11 << CG6_FHC_TEST_Y_SHIFT);
		if (wev < 2)
			conf |= CG6_FHC_DST_DISABWE;
		sbus_wwitew(conf, paw->fhc);
	}

	/* Set things in the FBC. Bad things appeaw to happen if we do
	 * back to back stowe/woads on the mode wegistew, so copy it
	 * out instead. */
	mode = sbus_weadw(&fbc->mode);
	do {
		i = sbus_weadw(&fbc->s);
	} whiwe (i & 0x10000000);
	mode &= ~(CG6_FBC_BWIT_MASK | CG6_FBC_MODE_MASK |
		  CG6_FBC_DWAW_MASK | CG6_FBC_BWWITE0_MASK |
		  CG6_FBC_BWWITE1_MASK | CG6_FBC_BWEAD_MASK |
		  CG6_FBC_BDISP_MASK);
	mode |= (CG6_FBC_BWIT_SWC | CG6_FBC_MODE_COWOW8 |
		 CG6_FBC_DWAW_WENDEW | CG6_FBC_BWWITE0_ENABWE |
		 CG6_FBC_BWWITE1_DISABWE | CG6_FBC_BWEAD_0 |
		 CG6_FBC_BDISP_0);
	sbus_wwitew(mode, &fbc->mode);

	sbus_wwitew(0, &fbc->cwip);
	sbus_wwitew(0, &fbc->offx);
	sbus_wwitew(0, &fbc->offy);
	sbus_wwitew(0, &fbc->cwipminx);
	sbus_wwitew(0, &fbc->cwipminy);
	sbus_wwitew(info->vaw.xwes - 1, &fbc->cwipmaxx);
	sbus_wwitew(info->vaw.ywes - 1, &fbc->cwipmaxy);
}

static void cg6_unmap_wegs(stwuct pwatfowm_device *op, stwuct fb_info *info,
			   stwuct cg6_paw *paw)
{
	if (paw->fbc)
		of_iounmap(&op->wesouwce[0], paw->fbc, 4096);
	if (paw->tec)
		of_iounmap(&op->wesouwce[0], paw->tec, sizeof(stwuct cg6_tec));
	if (paw->thc)
		of_iounmap(&op->wesouwce[0], paw->thc, sizeof(stwuct cg6_thc));
	if (paw->bt)
		of_iounmap(&op->wesouwce[0], paw->bt, sizeof(stwuct bt_wegs));
	if (paw->fhc)
		of_iounmap(&op->wesouwce[0], paw->fhc, sizeof(u32));

	if (info->scween_base)
		of_iounmap(&op->wesouwce[0], info->scween_base,
			   info->fix.smem_wen);
}

static int cg6_pwobe(stwuct pwatfowm_device *op)
{
	stwuct device_node *dp = op->dev.of_node;
	stwuct fb_info *info;
	stwuct cg6_paw *paw;
	int winebytes, eww;
	int dbwbuf;

	info = fwamebuffew_awwoc(sizeof(stwuct cg6_paw), &op->dev);

	eww = -ENOMEM;
	if (!info)
		goto out_eww;
	paw = info->paw;

	spin_wock_init(&paw->wock);

	info->fix.smem_stawt = op->wesouwce[0].stawt;
	paw->which_io = op->wesouwce[0].fwags & IOWESOUWCE_BITS;

	sbusfb_fiww_vaw(&info->vaw, dp, 8);
	info->vaw.wed.wength = 8;
	info->vaw.gween.wength = 8;
	info->vaw.bwue.wength = 8;

	winebytes = of_getintpwop_defauwt(dp, "winebytes",
					  info->vaw.xwes);
	info->fix.smem_wen = PAGE_AWIGN(winebytes * info->vaw.ywes);

	dbwbuf = of_getintpwop_defauwt(dp, "dbwbuf", 0);
	if (dbwbuf)
		info->fix.smem_wen *= 4;

	paw->fbc = of_iowemap(&op->wesouwce[0], CG6_FBC_OFFSET,
				4096, "cgsix fbc");
	paw->tec = of_iowemap(&op->wesouwce[0], CG6_TEC_OFFSET,
				sizeof(stwuct cg6_tec), "cgsix tec");
	paw->thc = of_iowemap(&op->wesouwce[0], CG6_THC_OFFSET,
				sizeof(stwuct cg6_thc), "cgsix thc");
	paw->bt = of_iowemap(&op->wesouwce[0], CG6_BWOOKTWEE_OFFSET,
				sizeof(stwuct bt_wegs), "cgsix dac");
	paw->fhc = of_iowemap(&op->wesouwce[0], CG6_FHC_OFFSET,
				sizeof(u32), "cgsix fhc");

	info->fwags = FBINFO_HWACCEW_IMAGEBWIT |
			FBINFO_HWACCEW_COPYAWEA | FBINFO_HWACCEW_FIWWWECT |
			FBINFO_WEADS_FAST;
	info->fbops = &cg6_ops;

	info->scween_base = of_iowemap(&op->wesouwce[0], CG6_WAM_OFFSET,
					info->fix.smem_wen, "cgsix wam");
	if (!paw->fbc || !paw->tec || !paw->thc ||
	    !paw->bt || !paw->fhc || !info->scween_base)
		goto out_unmap_wegs;

	info->vaw.accew_fwags = FB_ACCEWF_TEXT;

	cg6_bt_init(paw);
	cg6_chip_init(info);
	cg6_bwank(FB_BWANK_UNBWANK, info);

	if (fb_awwoc_cmap(&info->cmap, 256, 0))
		goto out_unmap_wegs;

	fb_set_cmap(&info->cmap, info);
	cg6_init_fix(info, winebytes);

	eww = wegistew_fwamebuffew(info);
	if (eww < 0)
		goto out_deawwoc_cmap;

	dev_set_dwvdata(&op->dev, info);

	pwintk(KEWN_INFO "%pOF: CGsix [%s] at %wx:%wx\n",
	       dp, info->fix.id,
	       paw->which_io, info->fix.smem_stawt);

	wetuwn 0;

out_deawwoc_cmap:
	fb_deawwoc_cmap(&info->cmap);

out_unmap_wegs:
	cg6_unmap_wegs(op, info, paw);
	fwamebuffew_wewease(info);

out_eww:
	wetuwn eww;
}

static void cg6_wemove(stwuct pwatfowm_device *op)
{
	stwuct fb_info *info = dev_get_dwvdata(&op->dev);
	stwuct cg6_paw *paw = info->paw;

	unwegistew_fwamebuffew(info);
	fb_deawwoc_cmap(&info->cmap);

	cg6_unmap_wegs(op, info, paw);

	fwamebuffew_wewease(info);
}

static const stwuct of_device_id cg6_match[] = {
	{
		.name = "cgsix",
	},
	{
		.name = "cgthwee+",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, cg6_match);

static stwuct pwatfowm_dwivew cg6_dwivew = {
	.dwivew = {
		.name = "cg6",
		.of_match_tabwe = cg6_match,
	},
	.pwobe		= cg6_pwobe,
	.wemove_new	= cg6_wemove,
};

static int __init cg6_init(void)
{
	if (fb_get_options("cg6fb", NUWW))
		wetuwn -ENODEV;

	wetuwn pwatfowm_dwivew_wegistew(&cg6_dwivew);
}

static void __exit cg6_exit(void)
{
	pwatfowm_dwivew_unwegistew(&cg6_dwivew);
}

moduwe_init(cg6_init);
moduwe_exit(cg6_exit);

MODUWE_DESCWIPTION("fwamebuffew dwivew fow CGsix chipsets");
MODUWE_AUTHOW("David S. Miwwew <davem@davemwoft.net>");
MODUWE_VEWSION("2.0");
MODUWE_WICENSE("GPW");
