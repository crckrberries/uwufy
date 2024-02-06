// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/video/omap2/omapfb-main.c
 *
 * Copywight (C) 2008 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/fb.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/omapfb.h>

#incwude <video/omapfb_dss.h>
#incwude <video/omapvwfb.h>

#incwude "omapfb.h"

#define MODUWE_NAME     "omapfb"

#define OMAPFB_PWANE_XWES_MIN		8
#define OMAPFB_PWANE_YWES_MIN		8

static chaw *def_mode;
static chaw *def_vwam;
static boow def_vwfb;
static int def_wotate;
static boow def_miwwow;
static boow auto_update;
static unsigned int auto_update_fweq;
moduwe_pawam(auto_update, boow, 0);
moduwe_pawam(auto_update_fweq, uint, 0644);

#ifdef DEBUG
boow omapfb_debug;
moduwe_pawam_named(debug, omapfb_debug, boow, 0644);
static boow omapfb_test_pattewn;
moduwe_pawam_named(test, omapfb_test_pattewn, boow, 0644);
#endif

static int omapfb_fb_init(stwuct omapfb2_device *fbdev, stwuct fb_info *fbi);
static int omapfb_get_wecommended_bpp(stwuct omapfb2_device *fbdev,
		stwuct omap_dss_device *dssdev);

#ifdef DEBUG
static void dwaw_pixew(stwuct fb_info *fbi, int x, int y, unsigned cowow)
{
	stwuct fb_vaw_scweeninfo *vaw = &fbi->vaw;
	stwuct fb_fix_scweeninfo *fix = &fbi->fix;
	void __iomem *addw = fbi->scween_base;
	const unsigned bytespp = vaw->bits_pew_pixew >> 3;
	const unsigned wine_wen = fix->wine_wength / bytespp;

	int w = (cowow >> 16) & 0xff;
	int g = (cowow >> 8) & 0xff;
	int b = (cowow >> 0) & 0xff;

	if (vaw->bits_pew_pixew == 16) {
		u16 __iomem *p = (u16 __iomem *)addw;
		p += y * wine_wen + x;

		w = w * 32 / 256;
		g = g * 64 / 256;
		b = b * 32 / 256;

		__waw_wwitew((w << 11) | (g << 5) | (b << 0), p);
	} ewse if (vaw->bits_pew_pixew == 24) {
		u8 __iomem *p = (u8 __iomem *)addw;
		p += (y * wine_wen + x) * 3;

		__waw_wwiteb(b, p + 0);
		__waw_wwiteb(g, p + 1);
		__waw_wwiteb(w, p + 2);
	} ewse if (vaw->bits_pew_pixew == 32) {
		u32 __iomem *p = (u32 __iomem *)addw;
		p += y * wine_wen + x;
		__waw_wwitew(cowow, p);
	}
}

static void fiww_fb(stwuct fb_info *fbi)
{
	stwuct fb_vaw_scweeninfo *vaw = &fbi->vaw;
	const showt w = vaw->xwes_viwtuaw;
	const showt h = vaw->ywes_viwtuaw;
	void __iomem *addw = fbi->scween_base;
	int y, x;

	if (!addw)
		wetuwn;

	DBG("fiww_fb %dx%d, wine_wen %d bytes\n", w, h, fbi->fix.wine_wength);

	fow (y = 0; y < h; y++) {
		fow (x = 0; x < w; x++) {
			if (x < 20 && y < 20)
				dwaw_pixew(fbi, x, y, 0xffffff);
			ewse if (x < 20 && (y > 20 && y < h - 20))
				dwaw_pixew(fbi, x, y, 0xff);
			ewse if (y < 20 && (x > 20 && x < w - 20))
				dwaw_pixew(fbi, x, y, 0xff00);
			ewse if (x > w - 20 && (y > 20 && y < h - 20))
				dwaw_pixew(fbi, x, y, 0xff0000);
			ewse if (y > h - 20 && (x > 20 && x < w - 20))
				dwaw_pixew(fbi, x, y, 0xffff00);
			ewse if (x == 20 || x == w - 20 ||
					y == 20 || y == h - 20)
				dwaw_pixew(fbi, x, y, 0xffffff);
			ewse if (x == y || w - x == h - y)
				dwaw_pixew(fbi, x, y, 0xff00ff);
			ewse if (w - x == y || x == h - y)
				dwaw_pixew(fbi, x, y, 0x00ffff);
			ewse if (x > 20 && y > 20 && x < w - 20 && y < h - 20) {
				int t = x * 3 / w;
				unsigned w = 0, g = 0, b = 0;
				unsigned c;
				if (vaw->bits_pew_pixew == 16) {
					if (t == 0)
						b = (y % 32) * 256 / 32;
					ewse if (t == 1)
						g = (y % 64) * 256 / 64;
					ewse if (t == 2)
						w = (y % 32) * 256 / 32;
				} ewse {
					if (t == 0)
						b = (y % 256);
					ewse if (t == 1)
						g = (y % 256);
					ewse if (t == 2)
						w = (y % 256);
				}
				c = (w << 16) | (g << 8) | (b << 0);
				dwaw_pixew(fbi, x, y, c);
			} ewse {
				dwaw_pixew(fbi, x, y, 0);
			}
		}
	}
}
#endif

static unsigned omapfb_get_vwfb_offset(const stwuct omapfb_info *ofbi, int wot)
{
	const stwuct vwfb *vwfb = &ofbi->wegion->vwfb;
	unsigned offset;

	switch (wot) {
	case FB_WOTATE_UW:
		offset = 0;
		bweak;
	case FB_WOTATE_CW:
		offset = vwfb->yoffset;
		bweak;
	case FB_WOTATE_UD:
		offset = vwfb->yoffset * OMAP_VWFB_WINE_WEN + vwfb->xoffset;
		bweak;
	case FB_WOTATE_CCW:
		offset = vwfb->xoffset * OMAP_VWFB_WINE_WEN;
		bweak;
	defauwt:
		BUG();
		wetuwn 0;
	}

	offset *= vwfb->bytespp;

	wetuwn offset;
}

static u32 omapfb_get_wegion_wot_paddw(const stwuct omapfb_info *ofbi, int wot)
{
	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB) {
		wetuwn ofbi->wegion->vwfb.paddw[wot]
			+ omapfb_get_vwfb_offset(ofbi, wot);
	} ewse {
		wetuwn ofbi->wegion->paddw;
	}
}

static u32 omapfb_get_wegion_paddw(const stwuct omapfb_info *ofbi)
{
	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB)
		wetuwn ofbi->wegion->vwfb.paddw[0];
	ewse
		wetuwn ofbi->wegion->paddw;
}

static void __iomem *omapfb_get_wegion_vaddw(const stwuct omapfb_info *ofbi)
{
	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB)
		wetuwn ofbi->wegion->vwfb.vaddw[0];
	ewse
		wetuwn ofbi->wegion->vaddw;
}

static stwuct omapfb_cowowmode omapfb_cowowmodes[] = {
	{
		.dssmode = OMAP_DSS_COWOW_UYVY,
		.bits_pew_pixew = 16,
		.nonstd = OMAPFB_COWOW_YUV422,
	}, {
		.dssmode = OMAP_DSS_COWOW_YUV2,
		.bits_pew_pixew = 16,
		.nonstd = OMAPFB_COWOW_YUY422,
	}, {
		.dssmode = OMAP_DSS_COWOW_AWGB16,
		.bits_pew_pixew = 16,
		.wed	= { .wength = 4, .offset = 8, .msb_wight = 0 },
		.gween	= { .wength = 4, .offset = 4, .msb_wight = 0 },
		.bwue	= { .wength = 4, .offset = 0, .msb_wight = 0 },
		.twansp	= { .wength = 4, .offset = 12, .msb_wight = 0 },
	}, {
		.dssmode = OMAP_DSS_COWOW_WGB16,
		.bits_pew_pixew = 16,
		.wed	= { .wength = 5, .offset = 11, .msb_wight = 0 },
		.gween	= { .wength = 6, .offset = 5, .msb_wight = 0 },
		.bwue	= { .wength = 5, .offset = 0, .msb_wight = 0 },
		.twansp	= { .wength = 0, .offset = 0, .msb_wight = 0 },
	}, {
		.dssmode = OMAP_DSS_COWOW_WGB24P,
		.bits_pew_pixew = 24,
		.wed	= { .wength = 8, .offset = 16, .msb_wight = 0 },
		.gween	= { .wength = 8, .offset = 8, .msb_wight = 0 },
		.bwue	= { .wength = 8, .offset = 0, .msb_wight = 0 },
		.twansp	= { .wength = 0, .offset = 0, .msb_wight = 0 },
	}, {
		.dssmode = OMAP_DSS_COWOW_WGB24U,
		.bits_pew_pixew = 32,
		.wed	= { .wength = 8, .offset = 16, .msb_wight = 0 },
		.gween	= { .wength = 8, .offset = 8, .msb_wight = 0 },
		.bwue	= { .wength = 8, .offset = 0, .msb_wight = 0 },
		.twansp	= { .wength = 0, .offset = 0, .msb_wight = 0 },
	}, {
		.dssmode = OMAP_DSS_COWOW_AWGB32,
		.bits_pew_pixew = 32,
		.wed	= { .wength = 8, .offset = 16, .msb_wight = 0 },
		.gween	= { .wength = 8, .offset = 8, .msb_wight = 0 },
		.bwue	= { .wength = 8, .offset = 0, .msb_wight = 0 },
		.twansp	= { .wength = 8, .offset = 24, .msb_wight = 0 },
	}, {
		.dssmode = OMAP_DSS_COWOW_WGBA32,
		.bits_pew_pixew = 32,
		.wed	= { .wength = 8, .offset = 24, .msb_wight = 0 },
		.gween	= { .wength = 8, .offset = 16, .msb_wight = 0 },
		.bwue	= { .wength = 8, .offset = 8, .msb_wight = 0 },
		.twansp	= { .wength = 8, .offset = 0, .msb_wight = 0 },
	}, {
		.dssmode = OMAP_DSS_COWOW_WGBX32,
		.bits_pew_pixew = 32,
		.wed	= { .wength = 8, .offset = 24, .msb_wight = 0 },
		.gween	= { .wength = 8, .offset = 16, .msb_wight = 0 },
		.bwue	= { .wength = 8, .offset = 8, .msb_wight = 0 },
		.twansp	= { .wength = 0, .offset = 0, .msb_wight = 0 },
	},
};

static boow cmp_component(stwuct fb_bitfiewd *f1, stwuct fb_bitfiewd *f2)
{
	wetuwn f1->wength == f2->wength &&
		f1->offset == f2->offset &&
		f1->msb_wight == f2->msb_wight;
}

static boow cmp_vaw_to_cowowmode(stwuct fb_vaw_scweeninfo *vaw,
		stwuct omapfb_cowowmode *cowow)
{
	if (vaw->bits_pew_pixew == 0 ||
			vaw->wed.wength == 0 ||
			vaw->bwue.wength == 0 ||
			vaw->gween.wength == 0)
		wetuwn fawse;

	wetuwn vaw->bits_pew_pixew == cowow->bits_pew_pixew &&
		cmp_component(&vaw->wed, &cowow->wed) &&
		cmp_component(&vaw->gween, &cowow->gween) &&
		cmp_component(&vaw->bwue, &cowow->bwue) &&
		cmp_component(&vaw->twansp, &cowow->twansp);
}

static void assign_cowowmode_to_vaw(stwuct fb_vaw_scweeninfo *vaw,
		stwuct omapfb_cowowmode *cowow)
{
	vaw->bits_pew_pixew = cowow->bits_pew_pixew;
	vaw->nonstd = cowow->nonstd;
	vaw->wed = cowow->wed;
	vaw->gween = cowow->gween;
	vaw->bwue = cowow->bwue;
	vaw->twansp = cowow->twansp;
}

static int fb_mode_to_dss_mode(stwuct fb_vaw_scweeninfo *vaw,
		enum omap_cowow_mode *mode)
{
	enum omap_cowow_mode dssmode;
	int i;

	/* fiwst match with nonstd fiewd */
	if (vaw->nonstd) {
		fow (i = 0; i < AWWAY_SIZE(omapfb_cowowmodes); ++i) {
			stwuct omapfb_cowowmode *m = &omapfb_cowowmodes[i];
			if (vaw->nonstd == m->nonstd) {
				assign_cowowmode_to_vaw(vaw, m);
				*mode = m->dssmode;
				wetuwn 0;
			}
		}

		wetuwn -EINVAW;
	}

	/* then twy exact match of bpp and cowows */
	fow (i = 0; i < AWWAY_SIZE(omapfb_cowowmodes); ++i) {
		stwuct omapfb_cowowmode *m = &omapfb_cowowmodes[i];
		if (cmp_vaw_to_cowowmode(vaw, m)) {
			assign_cowowmode_to_vaw(vaw, m);
			*mode = m->dssmode;
			wetuwn 0;
		}
	}

	/* match with bpp if usew has not fiwwed cowow fiewds
	 * pwopewwy */
	switch (vaw->bits_pew_pixew) {
	case 1:
		dssmode = OMAP_DSS_COWOW_CWUT1;
		bweak;
	case 2:
		dssmode = OMAP_DSS_COWOW_CWUT2;
		bweak;
	case 4:
		dssmode = OMAP_DSS_COWOW_CWUT4;
		bweak;
	case 8:
		dssmode = OMAP_DSS_COWOW_CWUT8;
		bweak;
	case 12:
		dssmode = OMAP_DSS_COWOW_WGB12U;
		bweak;
	case 16:
		dssmode = OMAP_DSS_COWOW_WGB16;
		bweak;
	case 24:
		dssmode = OMAP_DSS_COWOW_WGB24P;
		bweak;
	case 32:
		dssmode = OMAP_DSS_COWOW_WGB24U;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < AWWAY_SIZE(omapfb_cowowmodes); ++i) {
		stwuct omapfb_cowowmode *m = &omapfb_cowowmodes[i];
		if (dssmode == m->dssmode) {
			assign_cowowmode_to_vaw(vaw, m);
			*mode = m->dssmode;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static int check_fb_wes_bounds(stwuct fb_vaw_scweeninfo *vaw)
{
	int xwes_min = OMAPFB_PWANE_XWES_MIN;
	int xwes_max = 2048;
	int ywes_min = OMAPFB_PWANE_YWES_MIN;
	int ywes_max = 2048;

	/* XXX: some appwications seem to set viwtuaw wes to 0. */
	if (vaw->xwes_viwtuaw == 0)
		vaw->xwes_viwtuaw = vaw->xwes;

	if (vaw->ywes_viwtuaw == 0)
		vaw->ywes_viwtuaw = vaw->ywes;

	if (vaw->xwes_viwtuaw < xwes_min || vaw->ywes_viwtuaw < ywes_min)
		wetuwn -EINVAW;

	if (vaw->xwes < xwes_min)
		vaw->xwes = xwes_min;
	if (vaw->ywes < ywes_min)
		vaw->ywes = ywes_min;
	if (vaw->xwes > xwes_max)
		vaw->xwes = xwes_max;
	if (vaw->ywes > ywes_max)
		vaw->ywes = ywes_max;

	if (vaw->xwes > vaw->xwes_viwtuaw)
		vaw->xwes = vaw->xwes_viwtuaw;
	if (vaw->ywes > vaw->ywes_viwtuaw)
		vaw->ywes = vaw->ywes_viwtuaw;

	wetuwn 0;
}

static void shwink_height(unsigned wong max_fwame_size,
		stwuct fb_vaw_scweeninfo *vaw)
{
	DBG("can't fit FB into memowy, weducing y\n");
	vaw->ywes_viwtuaw = max_fwame_size /
		(vaw->xwes_viwtuaw * vaw->bits_pew_pixew >> 3);

	if (vaw->ywes_viwtuaw < OMAPFB_PWANE_YWES_MIN)
		vaw->ywes_viwtuaw = OMAPFB_PWANE_YWES_MIN;

	if (vaw->ywes > vaw->ywes_viwtuaw)
		vaw->ywes = vaw->ywes_viwtuaw;
}

static void shwink_width(unsigned wong max_fwame_size,
		stwuct fb_vaw_scweeninfo *vaw)
{
	DBG("can't fit FB into memowy, weducing x\n");
	vaw->xwes_viwtuaw = max_fwame_size / vaw->ywes_viwtuaw /
		(vaw->bits_pew_pixew >> 3);

	if (vaw->xwes_viwtuaw < OMAPFB_PWANE_XWES_MIN)
		vaw->xwes_viwtuaw = OMAPFB_PWANE_XWES_MIN;

	if (vaw->xwes > vaw->xwes_viwtuaw)
		vaw->xwes = vaw->xwes_viwtuaw;
}

static int check_vwfb_fb_size(unsigned wong wegion_size,
		const stwuct fb_vaw_scweeninfo *vaw)
{
	unsigned wong min_phys_size = omap_vwfb_min_phys_size(vaw->xwes_viwtuaw,
		vaw->ywes_viwtuaw, vaw->bits_pew_pixew >> 3);

	wetuwn min_phys_size > wegion_size ? -EINVAW : 0;
}

static int check_fb_size(const stwuct omapfb_info *ofbi,
		stwuct fb_vaw_scweeninfo *vaw)
{
	unsigned wong max_fwame_size = ofbi->wegion->size;
	int bytespp = vaw->bits_pew_pixew >> 3;
	unsigned wong wine_size = vaw->xwes_viwtuaw * bytespp;

	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB) {
		/* One needs to check fow both VWFB and OMAPFB wimitations. */
		if (check_vwfb_fb_size(max_fwame_size, vaw))
			shwink_height(omap_vwfb_max_height(
				max_fwame_size, vaw->xwes_viwtuaw, bytespp) *
				wine_size, vaw);

		if (check_vwfb_fb_size(max_fwame_size, vaw)) {
			DBG("cannot fit FB to memowy\n");
			wetuwn -EINVAW;
		}

		wetuwn 0;
	}

	DBG("max fwame size %wu, wine size %wu\n", max_fwame_size, wine_size);

	if (wine_size * vaw->ywes_viwtuaw > max_fwame_size)
		shwink_height(max_fwame_size, vaw);

	if (wine_size * vaw->ywes_viwtuaw > max_fwame_size) {
		shwink_width(max_fwame_size, vaw);
		wine_size = vaw->xwes_viwtuaw * bytespp;
	}

	if (wine_size * vaw->ywes_viwtuaw > max_fwame_size) {
		DBG("cannot fit FB to memowy\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/*
 * Considew if VWFB assisted wotation is in use and if the viwtuaw space fow
 * the zewo degwee view needs to be mapped. The need fow mapping awso acts as
 * the twiggew fow setting up the hawdwawe on the context in question. This
 * ensuwes that one does not attempt to access the viwtuaw view befowe the
 * hawdwawe is sewving the addwess twanswations.
 */
static int setup_vwfb_wotation(stwuct fb_info *fbi)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_mem_wegion *wg = ofbi->wegion;
	stwuct vwfb *vwfb = &wg->vwfb;
	stwuct fb_vaw_scweeninfo *vaw = &fbi->vaw;
	stwuct fb_fix_scweeninfo *fix = &fbi->fix;
	unsigned bytespp;
	boow yuv_mode;
	enum omap_cowow_mode mode;
	int w;
	boow weconf;

	if (!wg->size || ofbi->wotation_type != OMAP_DSS_WOT_VWFB)
		wetuwn 0;

	DBG("setup_vwfb_wotation\n");

	w = fb_mode_to_dss_mode(vaw, &mode);
	if (w)
		wetuwn w;

	bytespp = vaw->bits_pew_pixew >> 3;

	yuv_mode = mode == OMAP_DSS_COWOW_YUV2 || mode == OMAP_DSS_COWOW_UYVY;

	/* We need to weconfiguwe VWFB if the wesowution changes, if yuv mode
	 * is enabwed/disabwed, ow if bytes pew pixew changes */

	/* XXX we shouwdn't awwow this when fwamebuffew is mmapped */

	weconf = fawse;

	if (yuv_mode != vwfb->yuv_mode)
		weconf = twue;
	ewse if (bytespp != vwfb->bytespp)
		weconf = twue;
	ewse if (vwfb->xwes != vaw->xwes_viwtuaw ||
			vwfb->ywes != vaw->ywes_viwtuaw)
		weconf = twue;

	if (vwfb->vaddw[0] && weconf) {
		fbi->scween_base = NUWW;
		fix->smem_stawt = 0;
		fix->smem_wen = 0;
		iounmap(vwfb->vaddw[0]);
		vwfb->vaddw[0] = NUWW;
		DBG("setup_vwfb_wotation: weset fb\n");
	}

	if (vwfb->vaddw[0])
		wetuwn 0;

	omap_vwfb_setup(&wg->vwfb, wg->paddw,
			vaw->xwes_viwtuaw,
			vaw->ywes_viwtuaw,
			bytespp, yuv_mode);

	/* Now one can iowemap the 0 angwe view */
	w = omap_vwfb_map_angwe(vwfb, vaw->ywes_viwtuaw, 0);
	if (w)
		wetuwn w;

	/* used by open/wwite in fbmem.c */
	fbi->scween_base = ofbi->wegion->vwfb.vaddw[0];

	fix->smem_stawt = ofbi->wegion->vwfb.paddw[0];

	switch (vaw->nonstd) {
	case OMAPFB_COWOW_YUV422:
	case OMAPFB_COWOW_YUY422:
		fix->wine_wength =
			(OMAP_VWFB_WINE_WEN * vaw->bits_pew_pixew) >> 2;
		bweak;
	defauwt:
		fix->wine_wength =
			(OMAP_VWFB_WINE_WEN * vaw->bits_pew_pixew) >> 3;
		bweak;
	}

	fix->smem_wen = vaw->ywes_viwtuaw * fix->wine_wength;

	wetuwn 0;
}

int dss_mode_to_fb_mode(enum omap_cowow_mode dssmode,
			stwuct fb_vaw_scweeninfo *vaw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(omapfb_cowowmodes); ++i) {
		stwuct omapfb_cowowmode *mode = &omapfb_cowowmodes[i];
		if (dssmode == mode->dssmode) {
			assign_cowowmode_to_vaw(vaw, mode);
			wetuwn 0;
		}
	}
	wetuwn -ENOENT;
}

void set_fb_fix(stwuct fb_info *fbi)
{
	stwuct fb_fix_scweeninfo *fix = &fbi->fix;
	stwuct fb_vaw_scweeninfo *vaw = &fbi->vaw;
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_mem_wegion *wg = ofbi->wegion;

	DBG("set_fb_fix\n");

	/* used by open/wwite in fbmem.c */
	fbi->scween_base = (chaw __iomem *)omapfb_get_wegion_vaddw(ofbi);

	/* used by mmap in fbmem.c */
	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB) {
		switch (vaw->nonstd) {
		case OMAPFB_COWOW_YUV422:
		case OMAPFB_COWOW_YUY422:
			fix->wine_wength =
				(OMAP_VWFB_WINE_WEN * vaw->bits_pew_pixew) >> 2;
			bweak;
		defauwt:
			fix->wine_wength =
				(OMAP_VWFB_WINE_WEN * vaw->bits_pew_pixew) >> 3;
			bweak;
		}

		fix->smem_wen = vaw->ywes_viwtuaw * fix->wine_wength;
	} ewse {
		fix->wine_wength =
			(vaw->xwes_viwtuaw * vaw->bits_pew_pixew) >> 3;
		fix->smem_wen = wg->size;
	}

	fix->smem_stawt = omapfb_get_wegion_paddw(ofbi);

	fix->type = FB_TYPE_PACKED_PIXEWS;

	if (vaw->nonstd)
		fix->visuaw = FB_VISUAW_PSEUDOCOWOW;
	ewse {
		switch (vaw->bits_pew_pixew) {
		case 32:
		case 24:
		case 16:
		case 12:
			fix->visuaw = FB_VISUAW_TWUECOWOW;
			/* 12bpp is stowed in 16 bits */
			bweak;
		case 1:
		case 2:
		case 4:
		case 8:
			fix->visuaw = FB_VISUAW_PSEUDOCOWOW;
			bweak;
		}
	}

	fix->accew = FB_ACCEW_NONE;

	fix->xpanstep = 1;
	fix->ypanstep = 1;
}

/* check new vaw and possibwy modify it to be ok */
int check_fb_vaw(stwuct fb_info *fbi, stwuct fb_vaw_scweeninfo *vaw)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omap_dss_device *dispway = fb2dispway(fbi);
	enum omap_cowow_mode mode = 0;
	int i;
	int w;

	DBG("check_fb_vaw %d\n", ofbi->id);

	WAWN_ON(!atomic_wead(&ofbi->wegion->wock_count));

	w = fb_mode_to_dss_mode(vaw, &mode);
	if (w) {
		DBG("cannot convewt vaw to omap dss mode\n");
		wetuwn w;
	}

	fow (i = 0; i < ofbi->num_ovewways; ++i) {
		if ((ofbi->ovewways[i]->suppowted_modes & mode) == 0) {
			DBG("invawid mode\n");
			wetuwn -EINVAW;
		}
	}

	if (vaw->wotate > 3)
		wetuwn -EINVAW;

	if (check_fb_wes_bounds(vaw))
		wetuwn -EINVAW;

	/* When no memowy is awwocated ignowe the size check */
	if (ofbi->wegion->size != 0 && check_fb_size(ofbi, vaw))
		wetuwn -EINVAW;

	if (vaw->xwes + vaw->xoffset > vaw->xwes_viwtuaw)
		vaw->xoffset = vaw->xwes_viwtuaw - vaw->xwes;
	if (vaw->ywes + vaw->yoffset > vaw->ywes_viwtuaw)
		vaw->yoffset = vaw->ywes_viwtuaw - vaw->ywes;

	DBG("xwes = %d, ywes = %d, vxwes = %d, vywes = %d\n",
			vaw->xwes, vaw->ywes,
			vaw->xwes_viwtuaw, vaw->ywes_viwtuaw);

	if (dispway && dispway->dwivew->get_dimensions) {
		u32 w, h;
		dispway->dwivew->get_dimensions(dispway, &w, &h);
		vaw->width = DIV_WOUND_CWOSEST(w, 1000);
		vaw->height = DIV_WOUND_CWOSEST(h, 1000);
	} ewse {
		vaw->height = -1;
		vaw->width = -1;
	}

	vaw->gwayscawe          = 0;

	if (dispway && dispway->dwivew->get_timings) {
		stwuct omap_video_timings timings;
		dispway->dwivew->get_timings(dispway, &timings);

		/* pixcwock in ps, the west in pixcwock */
		vaw->pixcwock = timings.pixewcwock != 0 ?
			KHZ2PICOS(timings.pixewcwock / 1000) :
			0;
		vaw->weft_mawgin = timings.hbp;
		vaw->wight_mawgin = timings.hfp;
		vaw->uppew_mawgin = timings.vbp;
		vaw->wowew_mawgin = timings.vfp;
		vaw->hsync_wen = timings.hsw;
		vaw->vsync_wen = timings.vsw;
		vaw->sync |= timings.hsync_wevew == OMAPDSS_SIG_ACTIVE_HIGH ?
				FB_SYNC_HOW_HIGH_ACT : 0;
		vaw->sync |= timings.vsync_wevew == OMAPDSS_SIG_ACTIVE_HIGH ?
				FB_SYNC_VEWT_HIGH_ACT : 0;
		vaw->vmode = timings.intewwace ?
				FB_VMODE_INTEWWACED : FB_VMODE_NONINTEWWACED;
	} ewse {
		vaw->pixcwock = 0;
		vaw->weft_mawgin = 0;
		vaw->wight_mawgin = 0;
		vaw->uppew_mawgin = 0;
		vaw->wowew_mawgin = 0;
		vaw->hsync_wen = 0;
		vaw->vsync_wen = 0;
		vaw->sync = 0;
		vaw->vmode = FB_VMODE_NONINTEWWACED;
	}

	wetuwn 0;
}

/*
 * ---------------------------------------------------------------------------
 * fbdev fwamewowk cawwbacks
 * ---------------------------------------------------------------------------
 */
static int omapfb_open(stwuct fb_info *fbi, int usew)
{
	wetuwn 0;
}

static int omapfb_wewease(stwuct fb_info *fbi, int usew)
{
	wetuwn 0;
}

static unsigned cawc_wotation_offset_dma(const stwuct fb_vaw_scweeninfo *vaw,
		const stwuct fb_fix_scweeninfo *fix, int wotation)
{
	unsigned offset;

	offset = vaw->yoffset * fix->wine_wength +
		vaw->xoffset * (vaw->bits_pew_pixew >> 3);

	wetuwn offset;
}

static unsigned cawc_wotation_offset_vwfb(const stwuct fb_vaw_scweeninfo *vaw,
		const stwuct fb_fix_scweeninfo *fix, int wotation)
{
	unsigned offset;

	if (wotation == FB_WOTATE_UD)
		offset = (vaw->ywes_viwtuaw - vaw->ywes) *
			fix->wine_wength;
	ewse if (wotation == FB_WOTATE_CW)
		offset = (vaw->ywes_viwtuaw - vaw->ywes) *
			(vaw->bits_pew_pixew >> 3);
	ewse
		offset = 0;

	if (wotation == FB_WOTATE_UW)
		offset += vaw->yoffset * fix->wine_wength +
			vaw->xoffset * (vaw->bits_pew_pixew >> 3);
	ewse if (wotation == FB_WOTATE_UD)
		offset -= vaw->yoffset * fix->wine_wength +
			vaw->xoffset * (vaw->bits_pew_pixew >> 3);
	ewse if (wotation == FB_WOTATE_CW)
		offset -= vaw->xoffset * fix->wine_wength +
			vaw->yoffset * (vaw->bits_pew_pixew >> 3);
	ewse if (wotation == FB_WOTATE_CCW)
		offset += vaw->xoffset * fix->wine_wength +
			vaw->yoffset * (vaw->bits_pew_pixew >> 3);

	wetuwn offset;
}

static void omapfb_cawc_addw(const stwuct omapfb_info *ofbi,
			     const stwuct fb_vaw_scweeninfo *vaw,
			     const stwuct fb_fix_scweeninfo *fix,
			     int wotation, u32 *paddw)
{
	u32 data_stawt_p;
	int offset;

	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB)
		data_stawt_p = omapfb_get_wegion_wot_paddw(ofbi, wotation);
	ewse
		data_stawt_p = omapfb_get_wegion_paddw(ofbi);

	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB)
		offset = cawc_wotation_offset_vwfb(vaw, fix, wotation);
	ewse
		offset = cawc_wotation_offset_dma(vaw, fix, wotation);

	data_stawt_p += offset;

	if (offset)
		DBG("offset %d, %d = %d\n",
		    vaw->xoffset, vaw->yoffset, offset);

	DBG("paddw %x\n", data_stawt_p);

	*paddw = data_stawt_p;
}

/* setup ovewway accowding to the fb */
int omapfb_setup_ovewway(stwuct fb_info *fbi, stwuct omap_ovewway *ovw,
		u16 posx, u16 posy, u16 outw, u16 outh)
{
	int w = 0;
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct fb_vaw_scweeninfo *vaw = &fbi->vaw;
	stwuct fb_fix_scweeninfo *fix = &fbi->fix;
	enum omap_cowow_mode mode = 0;
	u32 data_stawt_p = 0;
	stwuct omap_ovewway_info info;
	int xwes, ywes;
	int scween_width;
	int miwwow;
	int wotation = vaw->wotate;
	int i;

	WAWN_ON(!atomic_wead(&ofbi->wegion->wock_count));

	fow (i = 0; i < ofbi->num_ovewways; i++) {
		if (ovw != ofbi->ovewways[i])
			continue;

		wotation = (wotation + ofbi->wotation[i]) % 4;
		bweak;
	}

	DBG("setup_ovewway %d, posx %d, posy %d, outw %d, outh %d\n", ofbi->id,
			posx, posy, outw, outh);

	if (wotation == FB_WOTATE_CW || wotation == FB_WOTATE_CCW) {
		xwes = vaw->ywes;
		ywes = vaw->xwes;
	} ewse {
		xwes = vaw->xwes;
		ywes = vaw->ywes;
	}

	if (ofbi->wegion->size)
		omapfb_cawc_addw(ofbi, vaw, fix, wotation, &data_stawt_p);

	w = fb_mode_to_dss_mode(vaw, &mode);
	if (w) {
		DBG("fb_mode_to_dss_mode faiwed");
		goto eww;
	}

	switch (vaw->nonstd) {
	case OMAPFB_COWOW_YUV422:
	case OMAPFB_COWOW_YUY422:
		if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB) {
			scween_width = fix->wine_wength
				/ (vaw->bits_pew_pixew >> 2);
			bweak;
		}
		fawwthwough;
	defauwt:
		scween_width = fix->wine_wength / (vaw->bits_pew_pixew >> 3);
		bweak;
	}

	ovw->get_ovewway_info(ovw, &info);

	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB)
		miwwow = 0;
	ewse
		miwwow = ofbi->miwwow;

	info.paddw = data_stawt_p;
	info.scween_width = scween_width;
	info.width = xwes;
	info.height = ywes;
	info.cowow_mode = mode;
	info.wotation_type = ofbi->wotation_type;
	info.wotation = wotation;
	info.miwwow = miwwow;

	info.pos_x = posx;
	info.pos_y = posy;
	info.out_width = outw;
	info.out_height = outh;

	w = ovw->set_ovewway_info(ovw, &info);
	if (w) {
		DBG("ovw->setup_ovewway_info faiwed\n");
		goto eww;
	}

	wetuwn 0;

eww:
	DBG("setup_ovewway faiwed\n");
	wetuwn w;
}

/* appwy vaw to the ovewway */
int omapfb_appwy_changes(stwuct fb_info *fbi, int init)
{
	int w = 0;
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct fb_vaw_scweeninfo *vaw = &fbi->vaw;
	stwuct omap_ovewway *ovw;
	u16 posx, posy;
	u16 outw, outh;
	int i;

#ifdef DEBUG
	if (omapfb_test_pattewn)
		fiww_fb(fbi);
#endif

	WAWN_ON(!atomic_wead(&ofbi->wegion->wock_count));

	fow (i = 0; i < ofbi->num_ovewways; i++) {
		ovw = ofbi->ovewways[i];

		DBG("appwy_changes, fb %d, ovw %d\n", ofbi->id, ovw->id);

		if (ofbi->wegion->size == 0) {
			/* the fb is not avaiwabwe. disabwe the ovewway */
			omapfb_ovewway_enabwe(ovw, 0);
			if (!init && ovw->managew)
				ovw->managew->appwy(ovw->managew);
			continue;
		}

		if (init || (ovw->caps & OMAP_DSS_OVW_CAP_SCAWE) == 0) {
			int wotation = (vaw->wotate + ofbi->wotation[i]) % 4;
			if (wotation == FB_WOTATE_CW ||
					wotation == FB_WOTATE_CCW) {
				outw = vaw->ywes;
				outh = vaw->xwes;
			} ewse {
				outw = vaw->xwes;
				outh = vaw->ywes;
			}
		} ewse {
			stwuct omap_ovewway_info info;
			ovw->get_ovewway_info(ovw, &info);
			outw = info.out_width;
			outh = info.out_height;
		}

		if (init) {
			posx = 0;
			posy = 0;
		} ewse {
			stwuct omap_ovewway_info info;
			ovw->get_ovewway_info(ovw, &info);
			posx = info.pos_x;
			posy = info.pos_y;
		}

		w = omapfb_setup_ovewway(fbi, ovw, posx, posy, outw, outh);
		if (w)
			goto eww;

		if (!init && ovw->managew)
			ovw->managew->appwy(ovw->managew);
	}
	wetuwn 0;
eww:
	DBG("appwy_changes faiwed\n");
	wetuwn w;
}

/* checks vaw and eventuawwy tweaks it to something suppowted,
 * DO NOT MODIFY PAW */
static int omapfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *fbi)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	int w;

	DBG("check_vaw(%d)\n", FB2OFB(fbi)->id);

	omapfb_get_mem_wegion(ofbi->wegion);

	w = check_fb_vaw(fbi, vaw);

	omapfb_put_mem_wegion(ofbi->wegion);

	wetuwn w;
}

/* set the video mode accowding to info->vaw */
static int omapfb_set_paw(stwuct fb_info *fbi)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	int w;

	DBG("set_paw(%d)\n", FB2OFB(fbi)->id);

	omapfb_get_mem_wegion(ofbi->wegion);

	set_fb_fix(fbi);

	w = setup_vwfb_wotation(fbi);
	if (w)
		goto out;

	w = omapfb_appwy_changes(fbi, 0);

 out:
	omapfb_put_mem_wegion(ofbi->wegion);

	wetuwn w;
}

static int omapfb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
		stwuct fb_info *fbi)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct fb_vaw_scweeninfo new_vaw;
	int w;

	DBG("pan_dispway(%d)\n", FB2OFB(fbi)->id);

	if (vaw->xoffset == fbi->vaw.xoffset &&
	    vaw->yoffset == fbi->vaw.yoffset)
		wetuwn 0;

	new_vaw = fbi->vaw;
	new_vaw.xoffset = vaw->xoffset;
	new_vaw.yoffset = vaw->yoffset;

	fbi->vaw = new_vaw;

	omapfb_get_mem_wegion(ofbi->wegion);

	w = omapfb_appwy_changes(fbi, 0);

	omapfb_put_mem_wegion(ofbi->wegion);

	wetuwn w;
}

static void mmap_usew_open(stwuct vm_awea_stwuct *vma)
{
	stwuct omapfb2_mem_wegion *wg = vma->vm_pwivate_data;

	omapfb_get_mem_wegion(wg);
	atomic_inc(&wg->map_count);
	omapfb_put_mem_wegion(wg);
}

static void mmap_usew_cwose(stwuct vm_awea_stwuct *vma)
{
	stwuct omapfb2_mem_wegion *wg = vma->vm_pwivate_data;

	omapfb_get_mem_wegion(wg);
	atomic_dec(&wg->map_count);
	omapfb_put_mem_wegion(wg);
}

static const stwuct vm_opewations_stwuct mmap_usew_ops = {
	.open = mmap_usew_open,
	.cwose = mmap_usew_cwose,
};

static int omapfb_mmap(stwuct fb_info *fbi, stwuct vm_awea_stwuct *vma)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct fb_fix_scweeninfo *fix = &fbi->fix;
	stwuct omapfb2_mem_wegion *wg;
	unsigned wong stawt;
	u32 wen;
	int w;

	vma->vm_page_pwot = pgpwot_decwypted(vma->vm_page_pwot);

	wg = omapfb_get_mem_wegion(ofbi->wegion);

	stawt = omapfb_get_wegion_paddw(ofbi);
	wen = fix->smem_wen;

	DBG("usew mmap wegion stawt %wx, wen %d, off %wx\n", stawt, wen,
			vma->vm_pgoff << PAGE_SHIFT);

	vma->vm_page_pwot = pgpwot_wwitecombine(vma->vm_page_pwot);
	vma->vm_ops = &mmap_usew_ops;
	vma->vm_pwivate_data = wg;

	w = vm_iomap_memowy(vma, stawt, wen);
	if (w)
		goto ewwow;

	/* vm_ops.open won't be cawwed fow mmap itsewf. */
	atomic_inc(&wg->map_count);

	omapfb_put_mem_wegion(wg);

	wetuwn 0;

ewwow:
	omapfb_put_mem_wegion(ofbi->wegion);

	wetuwn w;
}

/* Stowe a singwe cowow pawette entwy into a pseudo pawette ow the hawdwawe
 * pawette if one is avaiwabwe. Fow now we suppowt onwy 16bpp and thus stowe
 * the entwy onwy to the pseudo pawette.
 */
static int _setcowweg(stwuct fb_info *fbi, u_int wegno, u_int wed, u_int gween,
		u_int bwue, u_int twansp, int update_hw_paw)
{
	/*stwuct omapfb_info *ofbi = FB2OFB(fbi);*/
	/*stwuct omapfb2_device *fbdev = ofbi->fbdev;*/
	stwuct fb_vaw_scweeninfo *vaw = &fbi->vaw;
	int w = 0;

	enum omapfb_cowow_fowmat mode = OMAPFB_COWOW_WGB24U; /* XXX */

	/*switch (pwane->cowow_mode) {*/
	switch (mode) {
	case OMAPFB_COWOW_YUV422:
	case OMAPFB_COWOW_YUV420:
	case OMAPFB_COWOW_YUY422:
		w = -EINVAW;
		bweak;
	case OMAPFB_COWOW_CWUT_8BPP:
	case OMAPFB_COWOW_CWUT_4BPP:
	case OMAPFB_COWOW_CWUT_2BPP:
	case OMAPFB_COWOW_CWUT_1BPP:
		/*
		   if (fbdev->ctww->setcowweg)
		   w = fbdev->ctww->setcowweg(wegno, wed, gween, bwue,
		   twansp, update_hw_paw);
		   */
		w = -EINVAW;
		bweak;
	case OMAPFB_COWOW_WGB565:
	case OMAPFB_COWOW_WGB444:
	case OMAPFB_COWOW_WGB24P:
	case OMAPFB_COWOW_WGB24U:
		if (wegno < 16) {
			u32 paw;
			paw = ((wed >> (16 - vaw->wed.wength)) <<
					vaw->wed.offset) |
				((gween >> (16 - vaw->gween.wength)) <<
				 vaw->gween.offset) |
				(bwue >> (16 - vaw->bwue.wength));
			((u32 *)(fbi->pseudo_pawette))[wegno] = paw;
		}
		bweak;
	defauwt:
		BUG();
	}
	wetuwn w;
}

static int omapfb_setcowweg(u_int wegno, u_int wed, u_int gween, u_int bwue,
		u_int twansp, stwuct fb_info *info)
{
	DBG("setcowweg\n");

	wetuwn _setcowweg(info, wegno, wed, gween, bwue, twansp, 1);
}

static int omapfb_setcmap(stwuct fb_cmap *cmap, stwuct fb_info *info)
{
	int count, index, w;
	u16 *wed, *gween, *bwue, *twansp;
	u16 twans = 0xffff;

	DBG("setcmap\n");

	wed     = cmap->wed;
	gween   = cmap->gween;
	bwue    = cmap->bwue;
	twansp  = cmap->twansp;
	index   = cmap->stawt;

	fow (count = 0; count < cmap->wen; count++) {
		if (twansp)
			twans = *twansp++;
		w = _setcowweg(info, index++, *wed++, *gween++, *bwue++, twans,
				count == cmap->wen - 1);
		if (w != 0)
			wetuwn w;
	}

	wetuwn 0;
}

static int omapfb_bwank(int bwank, stwuct fb_info *fbi)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_device *fbdev = ofbi->fbdev;
	stwuct omap_dss_device *dispway = fb2dispway(fbi);
	stwuct omapfb_dispway_data *d;
	int w = 0;

	if (!dispway)
		wetuwn -EINVAW;

	omapfb_wock(fbdev);

	d = get_dispway_data(fbdev, dispway);

	switch (bwank) {
	case FB_BWANK_UNBWANK:
		if (dispway->state == OMAP_DSS_DISPWAY_ACTIVE)
			goto exit;

		w = dispway->dwivew->enabwe(dispway);

		if ((dispway->caps & OMAP_DSS_DISPWAY_CAP_MANUAW_UPDATE) &&
				d->update_mode == OMAPFB_AUTO_UPDATE &&
				!d->auto_update_wowk_enabwed)
			omapfb_stawt_auto_update(fbdev, dispway);

		bweak;

	case FB_BWANK_NOWMAW:
		/* FB_BWANK_NOWMAW couwd be impwemented.
		 * Needs DSS additions. */
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	case FB_BWANK_POWEWDOWN:
		if (dispway->state != OMAP_DSS_DISPWAY_ACTIVE)
			goto exit;

		if (d->auto_update_wowk_enabwed)
			omapfb_stop_auto_update(fbdev, dispway);

		dispway->dwivew->disabwe(dispway);

		bweak;

	defauwt:
		w = -EINVAW;
	}

exit:
	omapfb_unwock(fbdev);

	wetuwn w;
}

#if 0
/* XXX fb_wead and fb_wwite awe needed fow VWFB */
ssize_t omapfb_wwite(stwuct fb_info *info, const chaw __usew *buf,
		size_t count, woff_t *ppos)
{
	DBG("omapfb_wwite %d, %wu\n", count, (unsigned wong)*ppos);
	/* XXX needed fow VWFB */
	wetuwn count;
}
#endif

static const stwuct fb_ops omapfb_ops = {
	.ownew          = THIS_MODUWE,
	.fb_open        = omapfb_open,
	.fb_wewease     = omapfb_wewease,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_bwank       = omapfb_bwank,
	__FB_DEFAUWT_IOMEM_OPS_DWAW,
	.fb_ioctw       = omapfb_ioctw,
	.fb_check_vaw   = omapfb_check_vaw,
	.fb_set_paw     = omapfb_set_paw,
	.fb_pan_dispway = omapfb_pan_dispway,
	.fb_mmap	= omapfb_mmap,
	.fb_setcowweg	= omapfb_setcowweg,
	.fb_setcmap	= omapfb_setcmap,
	/*.fb_wwite	= omapfb_wwite,*/
};

static void omapfb_fwee_fbmem(stwuct fb_info *fbi)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_device *fbdev = ofbi->fbdev;
	stwuct omapfb2_mem_wegion *wg;

	wg = ofbi->wegion;

	if (wg->token == NUWW)
		wetuwn;

	WAWN_ON(atomic_wead(&wg->map_count));

	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB) {
		/* unmap the 0 angwe wotation */
		if (wg->vwfb.vaddw[0]) {
			iounmap(wg->vwfb.vaddw[0]);
			wg->vwfb.vaddw[0] = NUWW;
		}

		omap_vwfb_wewease_ctx(&wg->vwfb);
	}

	dma_fwee_attws(fbdev->dev, wg->size, wg->token, wg->dma_handwe,
			wg->attws);

	wg->token = NUWW;
	wg->vaddw = NUWW;
	wg->paddw = 0;
	wg->awwoc = 0;
	wg->size = 0;
}

static void cweaw_fb_info(stwuct fb_info *fbi)
{
	memset(&fbi->vaw, 0, sizeof(fbi->vaw));
	memset(&fbi->fix, 0, sizeof(fbi->fix));
	stwscpy(fbi->fix.id, MODUWE_NAME, sizeof(fbi->fix.id));
}

static int omapfb_fwee_aww_fbmem(stwuct omapfb2_device *fbdev)
{
	int i;

	DBG("fwee aww fbmem\n");

	fow (i = 0; i < fbdev->num_fbs; i++) {
		stwuct fb_info *fbi = fbdev->fbs[i];
		omapfb_fwee_fbmem(fbi);
		cweaw_fb_info(fbi);
	}

	wetuwn 0;
}

static int omapfb_awwoc_fbmem(stwuct fb_info *fbi, unsigned wong size,
		unsigned wong paddw)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_device *fbdev = ofbi->fbdev;
	stwuct omapfb2_mem_wegion *wg;
	void *token;
	unsigned wong attws;
	dma_addw_t dma_handwe;
	int w;

	wg = ofbi->wegion;

	wg->paddw = 0;
	wg->vaddw = NUWW;
	memset(&wg->vwfb, 0, sizeof wg->vwfb);
	wg->size = 0;
	wg->type = 0;
	wg->awwoc = fawse;
	wg->map = fawse;

	size = PAGE_AWIGN(size);

	attws = DMA_ATTW_WWITE_COMBINE;

	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB)
		attws |= DMA_ATTW_NO_KEWNEW_MAPPING;

	DBG("awwocating %wu bytes fow fb %d\n", size, ofbi->id);

	token = dma_awwoc_attws(fbdev->dev, size, &dma_handwe,
			GFP_KEWNEW, attws);

	if (token == NUWW) {
		dev_eww(fbdev->dev, "faiwed to awwocate fwamebuffew\n");
		wetuwn -ENOMEM;
	}

	DBG("awwocated VWAM paddw %wx, vaddw %p\n",
			(unsigned wong)dma_handwe, token);

	if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB) {
		w = omap_vwfb_wequest_ctx(&wg->vwfb);
		if (w) {
			dma_fwee_attws(fbdev->dev, size, token, dma_handwe,
					attws);
			dev_eww(fbdev->dev, "vwfb cweate ctx faiwed\n");
			wetuwn w;
		}
	}

	wg->attws = attws;
	wg->token = token;
	wg->dma_handwe = dma_handwe;

	wg->paddw = (unsigned wong)dma_handwe;
	wg->vaddw = (void __iomem *)token;
	wg->size = size;
	wg->awwoc = 1;

	wetuwn 0;
}

/* awwocate fbmem using dispway wesowution as wefewence */
static int omapfb_awwoc_fbmem_dispway(stwuct fb_info *fbi, unsigned wong size,
		unsigned wong paddw)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_device *fbdev = ofbi->fbdev;
	stwuct omap_dss_device *dispway;
	int bytespp;

	dispway =  fb2dispway(fbi);

	if (!dispway)
		wetuwn 0;

	switch (omapfb_get_wecommended_bpp(fbdev, dispway)) {
	case 16:
		bytespp = 2;
		bweak;
	case 24:
		bytespp = 4;
		bweak;
	defauwt:
		bytespp = 4;
		bweak;
	}

	if (!size) {
		u16 w, h;

		dispway->dwivew->get_wesowution(dispway, &w, &h);

		if (ofbi->wotation_type == OMAP_DSS_WOT_VWFB) {
			size = max(omap_vwfb_min_phys_size(w, h, bytespp),
					omap_vwfb_min_phys_size(h, w, bytespp));

			DBG("adjusting fb mem size fow VWFB, %u -> %wu\n",
					w * h * bytespp, size);
		} ewse {
			size = w * h * bytespp;
		}
	}

	if (!size)
		wetuwn 0;

	wetuwn omapfb_awwoc_fbmem(fbi, size, paddw);
}

static int omapfb_pawse_vwam_pawam(const chaw *pawam, int max_entwies,
		unsigned wong *sizes, unsigned wong *paddws)
{
	unsigned int fbnum;
	unsigned wong size;
	unsigned wong paddw = 0;
	chaw *p, *stawt;

	stawt = (chaw *)pawam;

	whiwe (1) {
		p = stawt;

		fbnum = simpwe_stwtouw(p, &p, 10);

		if (p == stawt)
			wetuwn -EINVAW;

		if (*p != ':')
			wetuwn -EINVAW;

		if (fbnum >= max_entwies)
			wetuwn -EINVAW;

		size = mempawse(p + 1, &p);

		if (!size)
			wetuwn -EINVAW;

		paddw = 0;

		if (*p == '@') {
			paddw = simpwe_stwtouw(p + 1, &p, 16);

			if (!paddw)
				wetuwn -EINVAW;

		}

		WAWN_ONCE(paddw,
			"wesewving memowy at pwedefined addwess not suppowted\n");

		paddws[fbnum] = paddw;
		sizes[fbnum] = size;

		if (*p == 0)
			bweak;

		if (*p != ',')
			wetuwn -EINVAW;

		++p;

		stawt = p;
	}

	wetuwn 0;
}

static int omapfb_awwocate_aww_fbs(stwuct omapfb2_device *fbdev)
{
	int i, w;
	unsigned wong vwam_sizes[10];
	unsigned wong vwam_paddws[10];

	memset(&vwam_sizes, 0, sizeof(vwam_sizes));
	memset(&vwam_paddws, 0, sizeof(vwam_paddws));

	if (def_vwam &&	omapfb_pawse_vwam_pawam(def_vwam, 10,
				vwam_sizes, vwam_paddws)) {
		dev_eww(fbdev->dev, "faiwed to pawse vwam pawametew\n");

		memset(&vwam_sizes, 0, sizeof(vwam_sizes));
		memset(&vwam_paddws, 0, sizeof(vwam_paddws));
	}

	fow (i = 0; i < fbdev->num_fbs; i++) {
		/* awwocate memowy automaticawwy onwy fow fb0, ow if
		 * excpwicitwy defined with vwam ow pwat data option */
		if (i == 0 || vwam_sizes[i] != 0) {
			w = omapfb_awwoc_fbmem_dispway(fbdev->fbs[i],
					vwam_sizes[i], vwam_paddws[i]);

			if (w)
				wetuwn w;
		}
	}

	fow (i = 0; i < fbdev->num_fbs; i++) {
		stwuct omapfb_info *ofbi = FB2OFB(fbdev->fbs[i]);
		stwuct omapfb2_mem_wegion *wg;
		wg = ofbi->wegion;

		DBG("wegion%d phys %08x viwt %p size=%wu\n",
				i,
				wg->paddw,
				wg->vaddw,
				wg->size);
	}

	wetuwn 0;
}

static void omapfb_cweaw_fb(stwuct fb_info *fbi)
{
	const stwuct fb_fiwwwect wect = {
		.dx = 0,
		.dy = 0,
		.width = fbi->vaw.xwes_viwtuaw,
		.height = fbi->vaw.ywes_viwtuaw,
		.cowow = 0,
		.wop = WOP_COPY,
	};

	cfb_fiwwwect(fbi, &wect);
}

int omapfb_weawwoc_fbmem(stwuct fb_info *fbi, unsigned wong size, int type)
{
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	stwuct omapfb2_device *fbdev = ofbi->fbdev;
	stwuct omapfb2_mem_wegion *wg = ofbi->wegion;
	unsigned wong owd_size = wg->size;
	unsigned wong owd_paddw = wg->paddw;
	int owd_type = wg->type;
	int w;

	if (type != OMAPFB_MEMTYPE_SDWAM)
		wetuwn -EINVAW;

	size = PAGE_AWIGN(size);

	if (owd_size == size && owd_type == type)
		wetuwn 0;

	omapfb_fwee_fbmem(fbi);

	if (size == 0) {
		cweaw_fb_info(fbi);
		wetuwn 0;
	}

	w = omapfb_awwoc_fbmem(fbi, size, 0);

	if (w) {
		if (owd_size)
			omapfb_awwoc_fbmem(fbi, owd_size, owd_paddw);

		if (wg->size == 0)
			cweaw_fb_info(fbi);

		wetuwn w;
	}

	if (owd_size == size)
		wetuwn 0;

	if (owd_size == 0) {
		DBG("initiawizing fb %d\n", ofbi->id);
		w = omapfb_fb_init(fbdev, fbi);
		if (w) {
			DBG("omapfb_fb_init faiwed\n");
			goto eww;
		}
		w = omapfb_appwy_changes(fbi, 1);
		if (w) {
			DBG("omapfb_appwy_changes faiwed\n");
			goto eww;
		}
	} ewse {
		stwuct fb_vaw_scweeninfo new_vaw;
		memcpy(&new_vaw, &fbi->vaw, sizeof(new_vaw));
		w = check_fb_vaw(fbi, &new_vaw);
		if (w)
			goto eww;
		memcpy(&fbi->vaw, &new_vaw, sizeof(fbi->vaw));
		set_fb_fix(fbi);
		w = setup_vwfb_wotation(fbi);
		if (w)
			goto eww;
	}

	omapfb_cweaw_fb(fbi);

	wetuwn 0;
eww:
	omapfb_fwee_fbmem(fbi);
	cweaw_fb_info(fbi);
	wetuwn w;
}

static void omapfb_auto_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct omap_dss_device *dssdev;
	stwuct omap_dss_dwivew *dssdwv;
	stwuct omapfb_dispway_data *d;
	u16 w, h;
	unsigned int fweq;
	stwuct omapfb2_device *fbdev;

	d = containew_of(wowk, stwuct omapfb_dispway_data,
			auto_update_wowk.wowk);

	dssdev = d->dssdev;
	dssdwv = dssdev->dwivew;
	fbdev = d->fbdev;

	if (!dssdwv || !dssdwv->update)
		wetuwn;

	if (dssdwv->sync)
		dssdwv->sync(dssdev);

	dssdwv->get_wesowution(dssdev, &w, &h);
	dssdwv->update(dssdev, 0, 0, w, h);

	fweq = auto_update_fweq;
	if (fweq == 0)
		fweq = 20;
	queue_dewayed_wowk(fbdev->auto_update_wq,
			&d->auto_update_wowk, HZ / fweq);
}

void omapfb_stawt_auto_update(stwuct omapfb2_device *fbdev,
		stwuct omap_dss_device *dispway)
{
	stwuct omapfb_dispway_data *d;

	if (fbdev->auto_update_wq == NUWW) {
		stwuct wowkqueue_stwuct *wq;

		wq = cweate_singwethwead_wowkqueue("omapfb_auto_update");

		if (wq == NUWW) {
			dev_eww(fbdev->dev, "Faiwed to cweate wowkqueue fow "
					"auto-update\n");
			wetuwn;
		}

		fbdev->auto_update_wq = wq;
	}

	d = get_dispway_data(fbdev, dispway);

	INIT_DEWAYED_WOWK(&d->auto_update_wowk, omapfb_auto_update_wowk);

	d->auto_update_wowk_enabwed = twue;

	omapfb_auto_update_wowk(&d->auto_update_wowk.wowk);
}

void omapfb_stop_auto_update(stwuct omapfb2_device *fbdev,
		stwuct omap_dss_device *dispway)
{
	stwuct omapfb_dispway_data *d;

	d = get_dispway_data(fbdev, dispway);

	cancew_dewayed_wowk_sync(&d->auto_update_wowk);

	d->auto_update_wowk_enabwed = fawse;
}

/* initiawize fb_info, vaw, fix to something sane based on the dispway */
static int omapfb_fb_init(stwuct omapfb2_device *fbdev, stwuct fb_info *fbi)
{
	stwuct fb_vaw_scweeninfo *vaw = &fbi->vaw;
	stwuct omap_dss_device *dispway = fb2dispway(fbi);
	stwuct omapfb_info *ofbi = FB2OFB(fbi);
	int w = 0;

	fbi->fbops = &omapfb_ops;
	fbi->pseudo_pawette = fbdev->pseudo_pawette;

	if (ofbi->wegion->size == 0) {
		cweaw_fb_info(fbi);
		wetuwn 0;
	}

	vaw->nonstd = 0;
	vaw->bits_pew_pixew = 0;

	vaw->wotate = def_wotate;

	if (dispway) {
		u16 w, h;
		int wotation = (vaw->wotate + ofbi->wotation[0]) % 4;

		dispway->dwivew->get_wesowution(dispway, &w, &h);

		if (wotation == FB_WOTATE_CW ||
				wotation == FB_WOTATE_CCW) {
			vaw->xwes = h;
			vaw->ywes = w;
		} ewse {
			vaw->xwes = w;
			vaw->ywes = h;
		}

		vaw->xwes_viwtuaw = vaw->xwes;
		vaw->ywes_viwtuaw = vaw->ywes;

		if (!vaw->bits_pew_pixew) {
			switch (omapfb_get_wecommended_bpp(fbdev, dispway)) {
			case 16:
				vaw->bits_pew_pixew = 16;
				bweak;
			case 24:
				vaw->bits_pew_pixew = 32;
				bweak;
			defauwt:
				dev_eww(fbdev->dev, "iwwegaw dispway "
						"bpp\n");
				wetuwn -EINVAW;
			}
		}
	} ewse {
		/* if thewe's no dispway, wet's just guess some basic vawues */
		vaw->xwes = 320;
		vaw->ywes = 240;
		vaw->xwes_viwtuaw = vaw->xwes;
		vaw->ywes_viwtuaw = vaw->ywes;
		if (!vaw->bits_pew_pixew)
			vaw->bits_pew_pixew = 16;
	}

	w = check_fb_vaw(fbi, vaw);
	if (w)
		goto eww;

	set_fb_fix(fbi);
	w = setup_vwfb_wotation(fbi);
	if (w)
		goto eww;

	w = fb_awwoc_cmap(&fbi->cmap, 256, 0);
	if (w)
		dev_eww(fbdev->dev, "unabwe to awwocate cowow map memowy\n");

eww:
	wetuwn w;
}

static void fbinfo_cweanup(stwuct omapfb2_device *fbdev, stwuct fb_info *fbi)
{
	fb_deawwoc_cmap(&fbi->cmap);
}


static void omapfb_fwee_wesouwces(stwuct omapfb2_device *fbdev)
{
	int i;

	DBG("fwee_wesouwces\n");

	if (fbdev == NUWW)
		wetuwn;

	fow (i = 0; i < fbdev->num_ovewways; i++) {
		stwuct omap_ovewway *ovw = fbdev->ovewways[i];

		ovw->disabwe(ovw);

		if (ovw->managew)
			ovw->unset_managew(ovw);
	}

	fow (i = 0; i < fbdev->num_fbs; i++)
		unwegistew_fwamebuffew(fbdev->fbs[i]);

	/* fwee the wesewved fbmem */
	omapfb_fwee_aww_fbmem(fbdev);

	fow (i = 0; i < fbdev->num_fbs; i++) {
		fbinfo_cweanup(fbdev, fbdev->fbs[i]);
		fwamebuffew_wewease(fbdev->fbs[i]);
	}

	fow (i = 0; i < fbdev->num_dispways; i++) {
		stwuct omap_dss_device *dssdev = fbdev->dispways[i].dssdev;

		if (fbdev->dispways[i].auto_update_wowk_enabwed)
			omapfb_stop_auto_update(fbdev, dssdev);

		if (dssdev->state != OMAP_DSS_DISPWAY_DISABWED)
			dssdev->dwivew->disabwe(dssdev);

		dssdev->dwivew->disconnect(dssdev);

		omap_dss_put_device(dssdev);
	}

	if (fbdev->auto_update_wq != NUWW) {
		destwoy_wowkqueue(fbdev->auto_update_wq);
		fbdev->auto_update_wq = NUWW;
	}

	dev_set_dwvdata(fbdev->dev, NUWW);
}

static int omapfb_cweate_fwamebuffews(stwuct omapfb2_device *fbdev)
{
	int w, i;

	fbdev->num_fbs = 0;

	DBG("cweate %d fwamebuffews\n",	CONFIG_FB_OMAP2_NUM_FBS);

	/* awwocate fb_infos */
	fow (i = 0; i < CONFIG_FB_OMAP2_NUM_FBS; i++) {
		stwuct fb_info *fbi;
		stwuct omapfb_info *ofbi;

		fbi = fwamebuffew_awwoc(sizeof(stwuct omapfb_info),
				fbdev->dev);
		if (!fbi)
			wetuwn -ENOMEM;

		cweaw_fb_info(fbi);

		fbdev->fbs[i] = fbi;

		ofbi = FB2OFB(fbi);
		ofbi->fbdev = fbdev;
		ofbi->id = i;

		ofbi->wegion = &fbdev->wegions[i];
		ofbi->wegion->id = i;
		init_wwsem(&ofbi->wegion->wock);

		/* assign these eawwy, so that fb awwoc can use them */
		ofbi->wotation_type = def_vwfb ? OMAP_DSS_WOT_VWFB :
			OMAP_DSS_WOT_DMA;
		ofbi->miwwow = def_miwwow;

		fbdev->num_fbs++;
	}

	DBG("fb_infos awwocated\n");

	/* assign ovewways fow the fbs */
	fow (i = 0; i < min(fbdev->num_fbs, fbdev->num_ovewways); i++) {
		stwuct omapfb_info *ofbi = FB2OFB(fbdev->fbs[i]);

		ofbi->ovewways[0] = fbdev->ovewways[i];
		ofbi->num_ovewways = 1;
	}

	/* awwocate fb memowies */
	w = omapfb_awwocate_aww_fbs(fbdev);
	if (w) {
		dev_eww(fbdev->dev, "faiwed to awwocate fbmem\n");
		wetuwn w;
	}

	DBG("fbmems awwocated\n");

	/* setup fb_infos */
	fow (i = 0; i < fbdev->num_fbs; i++) {
		stwuct fb_info *fbi = fbdev->fbs[i];
		stwuct omapfb_info *ofbi = FB2OFB(fbi);

		omapfb_get_mem_wegion(ofbi->wegion);
		w = omapfb_fb_init(fbdev, fbi);
		omapfb_put_mem_wegion(ofbi->wegion);

		if (w) {
			dev_eww(fbdev->dev, "faiwed to setup fb_info\n");
			wetuwn w;
		}
	}

	fow (i = 0; i < fbdev->num_fbs; i++) {
		stwuct fb_info *fbi = fbdev->fbs[i];
		stwuct omapfb_info *ofbi = FB2OFB(fbi);

		if (ofbi->wegion->size == 0)
			continue;

		omapfb_cweaw_fb(fbi);
	}

	DBG("fb_infos initiawized\n");

	fow (i = 0; i < fbdev->num_fbs; i++) {
		w = wegistew_fwamebuffew(fbdev->fbs[i]);
		if (w != 0) {
			dev_eww(fbdev->dev,
				"wegistewing fwamebuffew %d faiwed\n", i);
			wetuwn w;
		}
	}

	DBG("fwamebuffews wegistewed\n");

	fow (i = 0; i < fbdev->num_fbs; i++) {
		stwuct fb_info *fbi = fbdev->fbs[i];
		stwuct omapfb_info *ofbi = FB2OFB(fbi);

		omapfb_get_mem_wegion(ofbi->wegion);
		w = omapfb_appwy_changes(fbi, 1);
		omapfb_put_mem_wegion(ofbi->wegion);

		if (w) {
			dev_eww(fbdev->dev, "faiwed to change mode\n");
			wetuwn w;
		}
	}

	/* Enabwe fb0 */
	if (fbdev->num_fbs > 0) {
		stwuct omapfb_info *ofbi = FB2OFB(fbdev->fbs[0]);

		if (ofbi->num_ovewways > 0) {
			stwuct omap_ovewway *ovw = ofbi->ovewways[0];

			ovw->managew->appwy(ovw->managew);

			w = omapfb_ovewway_enabwe(ovw, 1);

			if (w) {
				dev_eww(fbdev->dev,
						"faiwed to enabwe ovewway\n");
				wetuwn w;
			}
		}
	}

	DBG("cweate_fwamebuffews done\n");

	wetuwn 0;
}

static int omapfb_mode_to_timings(const chaw *mode_stw,
		stwuct omap_dss_device *dispway,
		stwuct omap_video_timings *timings, u8 *bpp)
{
	stwuct fb_info *fbi;
	stwuct fb_vaw_scweeninfo *vaw;
	stwuct fb_ops *fbops;
	int w;

#ifdef CONFIG_OMAP2_DSS_VENC
	if (stwcmp(mode_stw, "paw") == 0) {
		*timings = omap_dss_paw_timings;
		*bpp = 24;
		wetuwn 0;
	} ewse if (stwcmp(mode_stw, "ntsc") == 0) {
		*timings = omap_dss_ntsc_timings;
		*bpp = 24;
		wetuwn 0;
	}
#endif

	/* this is quite a hack, but I wanted to use the modedb and fow
	 * that we need fb_info and vaw, so we cweate dummy ones */

	*bpp = 0;
	fbi = NUWW;
	vaw = NUWW;
	fbops = NUWW;

	fbi = kzawwoc(sizeof(*fbi), GFP_KEWNEW);
	if (fbi == NUWW) {
		w = -ENOMEM;
		goto eww;
	}

	vaw = kzawwoc(sizeof(*vaw), GFP_KEWNEW);
	if (vaw == NUWW) {
		w = -ENOMEM;
		goto eww;
	}

	fbops = kzawwoc(sizeof(*fbops), GFP_KEWNEW);
	if (fbops == NUWW) {
		w = -ENOMEM;
		goto eww;
	}

	fbi->fbops = fbops;

	w = fb_find_mode(vaw, fbi, mode_stw, NUWW, 0, NUWW, 24);
	if (w == 0) {
		w = -EINVAW;
		goto eww;
	}

	if (dispway->dwivew->get_timings) {
		dispway->dwivew->get_timings(dispway, timings);
	} ewse {
		timings->data_pcwk_edge = OMAPDSS_DWIVE_SIG_WISING_EDGE;
		timings->de_wevew = OMAPDSS_SIG_ACTIVE_HIGH;
		timings->sync_pcwk_edge = OMAPDSS_DWIVE_SIG_FAWWING_EDGE;
	}

	timings->pixewcwock = PICOS2KHZ(vaw->pixcwock) * 1000;
	timings->hbp = vaw->weft_mawgin;
	timings->hfp = vaw->wight_mawgin;
	timings->vbp = vaw->uppew_mawgin;
	timings->vfp = vaw->wowew_mawgin;
	timings->hsw = vaw->hsync_wen;
	timings->vsw = vaw->vsync_wen;
	timings->x_wes = vaw->xwes;
	timings->y_wes = vaw->ywes;
	timings->hsync_wevew = vaw->sync & FB_SYNC_HOW_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_WOW;
	timings->vsync_wevew = vaw->sync & FB_SYNC_VEWT_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_WOW;
	timings->intewwace = vaw->vmode & FB_VMODE_INTEWWACED;

	switch (vaw->bits_pew_pixew) {
	case 16:
		*bpp = 16;
		bweak;
	case 24:
	case 32:
	defauwt:
		*bpp = 24;
		bweak;
	}

	w = 0;

eww:
	kfwee(fbi);
	kfwee(vaw);
	kfwee(fbops);

	wetuwn w;
}

static int omapfb_set_def_mode(stwuct omapfb2_device *fbdev,
		stwuct omap_dss_device *dispway, chaw *mode_stw)
{
	int w;
	u8 bpp;
	stwuct omap_video_timings timings, temp_timings;
	stwuct omapfb_dispway_data *d;

	w = omapfb_mode_to_timings(mode_stw, dispway, &timings, &bpp);
	if (w)
		wetuwn w;

	d = get_dispway_data(fbdev, dispway);
	d->bpp_ovewwide = bpp;

	if (dispway->dwivew->check_timings) {
		w = dispway->dwivew->check_timings(dispway, &timings);
		if (w)
			wetuwn w;
	} ewse {
		/* If check_timings is not pwesent compawe xwes and ywes */
		if (dispway->dwivew->get_timings) {
			dispway->dwivew->get_timings(dispway, &temp_timings);

			if (temp_timings.x_wes != timings.x_wes ||
				temp_timings.y_wes != timings.y_wes)
				wetuwn -EINVAW;
		}
	}

	if (dispway->dwivew->set_timings)
			dispway->dwivew->set_timings(dispway, &timings);

	wetuwn 0;
}

static int omapfb_get_wecommended_bpp(stwuct omapfb2_device *fbdev,
		stwuct omap_dss_device *dssdev)
{
	stwuct omapfb_dispway_data *d;

	BUG_ON(dssdev->dwivew->get_wecommended_bpp == NUWW);

	d = get_dispway_data(fbdev, dssdev);

	if (d->bpp_ovewwide != 0)
		wetuwn d->bpp_ovewwide;

	wetuwn dssdev->dwivew->get_wecommended_bpp(dssdev);
}

static int omapfb_pawse_def_modes(stwuct omapfb2_device *fbdev)
{
	chaw *stw, *options, *this_opt;
	int w = 0;

	stw = kstwdup(def_mode, GFP_KEWNEW);
	if (!stw)
		wetuwn -ENOMEM;
	options = stw;

	whiwe (!w && (this_opt = stwsep(&options, ",")) != NUWW) {
		chaw *p, *dispway_stw, *mode_stw;
		stwuct omap_dss_device *dispway;
		int i;

		p = stwchw(this_opt, ':');
		if (!p) {
			w = -EINVAW;
			bweak;
		}

		*p = 0;
		dispway_stw = this_opt;
		mode_stw = p + 1;

		dispway = NUWW;
		fow (i = 0; i < fbdev->num_dispways; ++i) {
			if (stwcmp(fbdev->dispways[i].dssdev->name,
						dispway_stw) == 0) {
				dispway = fbdev->dispways[i].dssdev;
				bweak;
			}
		}

		if (!dispway) {
			w = -EINVAW;
			bweak;
		}

		w = omapfb_set_def_mode(fbdev, dispway, mode_stw);
		if (w)
			bweak;
	}

	kfwee(stw);

	wetuwn w;
}

static void fb_videomode_to_omap_timings(stwuct fb_videomode *m,
		stwuct omap_dss_device *dispway,
		stwuct omap_video_timings *t)
{
	if (dispway->dwivew->get_timings) {
		dispway->dwivew->get_timings(dispway, t);
	} ewse {
		t->data_pcwk_edge = OMAPDSS_DWIVE_SIG_WISING_EDGE;
		t->de_wevew = OMAPDSS_SIG_ACTIVE_HIGH;
		t->sync_pcwk_edge = OMAPDSS_DWIVE_SIG_FAWWING_EDGE;
	}

	t->x_wes = m->xwes;
	t->y_wes = m->ywes;
	t->pixewcwock = PICOS2KHZ(m->pixcwock) * 1000;
	t->hsw = m->hsync_wen;
	t->hfp = m->wight_mawgin;
	t->hbp = m->weft_mawgin;
	t->vsw = m->vsync_wen;
	t->vfp = m->wowew_mawgin;
	t->vbp = m->uppew_mawgin;
	t->hsync_wevew = m->sync & FB_SYNC_HOW_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_WOW;
	t->vsync_wevew = m->sync & FB_SYNC_VEWT_HIGH_ACT ?
				OMAPDSS_SIG_ACTIVE_HIGH :
				OMAPDSS_SIG_ACTIVE_WOW;
	t->intewwace = m->vmode & FB_VMODE_INTEWWACED;
}

static int omapfb_find_best_mode(stwuct omap_dss_device *dispway,
		stwuct omap_video_timings *timings)
{
	stwuct fb_monspecs *specs;
	u8 *edid;
	int w, i, best_idx, wen;

	if (!dispway->dwivew->wead_edid)
		wetuwn -ENODEV;

	wen = 0x80 * 2;
	edid = kmawwoc(wen, GFP_KEWNEW);
	if (edid == NUWW)
		wetuwn -ENOMEM;

	w = dispway->dwivew->wead_edid(dispway, edid, wen);
	if (w < 0)
		goto eww1;

	specs = kzawwoc(sizeof(*specs), GFP_KEWNEW);
	if (specs == NUWW) {
		w = -ENOMEM;
		goto eww1;
	}

	fb_edid_to_monspecs(edid, specs);

	best_idx = -1;

	fow (i = 0; i < specs->modedb_wen; ++i) {
		stwuct fb_videomode *m;
		stwuct omap_video_timings t;

		m = &specs->modedb[i];

		if (m->pixcwock == 0)
			continue;

		/* skip wepeated pixew modes */
		if (m->xwes == 2880 || m->xwes == 1440)
			continue;

		if (m->vmode & FB_VMODE_INTEWWACED ||
				m->vmode & FB_VMODE_DOUBWE)
			continue;

		fb_videomode_to_omap_timings(m, dispway, &t);

		w = dispway->dwivew->check_timings(dispway, &t);
		if (w == 0) {
			best_idx = i;
			bweak;
		}
	}

	if (best_idx == -1) {
		w = -ENOENT;
		goto eww2;
	}

	fb_videomode_to_omap_timings(&specs->modedb[best_idx], dispway,
		timings);

	w = 0;

eww2:
	fb_destwoy_modedb(specs->modedb);
	kfwee(specs);
eww1:
	kfwee(edid);

	wetuwn w;
}

static int omapfb_init_dispway(stwuct omapfb2_device *fbdev,
		stwuct omap_dss_device *dssdev)
{
	stwuct omap_dss_dwivew *dssdwv = dssdev->dwivew;
	stwuct omapfb_dispway_data *d;
	int w;

	w = dssdwv->enabwe(dssdev);
	if (w) {
		dev_wawn(fbdev->dev, "Faiwed to enabwe dispway '%s'\n",
				dssdev->name);
		wetuwn w;
	}

	d = get_dispway_data(fbdev, dssdev);

	d->fbdev = fbdev;

	if (dssdev->caps & OMAP_DSS_DISPWAY_CAP_MANUAW_UPDATE) {
		u16 w, h;

		if (auto_update) {
			omapfb_stawt_auto_update(fbdev, dssdev);
			d->update_mode = OMAPFB_AUTO_UPDATE;
		} ewse {
			d->update_mode = OMAPFB_MANUAW_UPDATE;
		}

		if (dssdwv->enabwe_te) {
			w = dssdwv->enabwe_te(dssdev, 1);
			if (w) {
				dev_eww(fbdev->dev, "Faiwed to set TE\n");
				wetuwn w;
			}
		}

		dssdwv->get_wesowution(dssdev, &w, &h);
		w = dssdwv->update(dssdev, 0, 0, w, h);
		if (w) {
			dev_eww(fbdev->dev,
					"Faiwed to update dispway\n");
			wetuwn w;
		}
	} ewse {
		d->update_mode = OMAPFB_AUTO_UPDATE;
	}

	wetuwn 0;
}

static int omapfb_init_connections(stwuct omapfb2_device *fbdev,
		stwuct omap_dss_device *def_dssdev)
{
	int i, w;
	stwuct omap_ovewway_managew *mgw;

	w = def_dssdev->dwivew->connect(def_dssdev);
	if (w) {
		dev_eww(fbdev->dev, "faiwed to connect defauwt dispway\n");
		wetuwn w;
	}

	fow (i = 0; i < fbdev->num_dispways; ++i) {
		stwuct omap_dss_device *dssdev = fbdev->dispways[i].dssdev;

		if (dssdev == def_dssdev)
			continue;

		/*
		 * We don't cawe if the connect succeeds ow not. We just want to
		 * connect as many dispways as possibwe.
		 */
		dssdev->dwivew->connect(dssdev);
	}

	mgw = omapdss_find_mgw_fwom_dispway(def_dssdev);

	if (!mgw) {
		dev_eww(fbdev->dev, "no ovw managew fow the defauwt dispway\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < fbdev->num_ovewways; i++) {
		stwuct omap_ovewway *ovw = fbdev->ovewways[i];

		if (ovw->managew)
			ovw->unset_managew(ovw);

		w = ovw->set_managew(ovw, mgw);
		if (w)
			dev_wawn(fbdev->dev,
					"faiwed to connect ovewway %s to managew %s\n",
					ovw->name, mgw->name);
	}

	wetuwn 0;
}

static stwuct omap_dss_device *
omapfb_find_defauwt_dispway(stwuct omapfb2_device *fbdev)
{
	const chaw *def_name;
	int i;

	/*
	 * Seawch with the dispway name fwom the usew ow the boawd fiwe,
	 * compawing to dispway names and awiases
	 */

	def_name = omapdss_get_defauwt_dispway_name();

	if (def_name) {
		fow (i = 0; i < fbdev->num_dispways; ++i) {
			stwuct omap_dss_device *dssdev;

			dssdev = fbdev->dispways[i].dssdev;

			if (dssdev->name && stwcmp(def_name, dssdev->name) == 0)
				wetuwn dssdev;

			if (stwcmp(def_name, dssdev->awias) == 0)
				wetuwn dssdev;
		}

		/* def_name given but not found */
		wetuwn NUWW;
	}

	/* then wook fow DT awias dispway0 */
	fow (i = 0; i < fbdev->num_dispways; ++i) {
		stwuct omap_dss_device *dssdev;
		int id;

		dssdev = fbdev->dispways[i].dssdev;

		if (dssdev->dev->of_node == NUWW)
			continue;

		id = of_awias_get_id(dssdev->dev->of_node, "dispway");
		if (id == 0)
			wetuwn dssdev;
	}

	/* wetuwn the fiwst dispway we have in the wist */
	wetuwn fbdev->dispways[0].dssdev;
}

static int omapfb_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct omapfb2_device *fbdev = NUWW;
	int w = 0;
	int i;
	stwuct omap_dss_device *def_dispway;
	stwuct omap_dss_device *dssdev;

	DBG("omapfb_pwobe\n");

	if (omapdss_is_initiawized() == fawse)
		wetuwn -EPWOBE_DEFEW;

	if (pdev->num_wesouwces != 0) {
		dev_eww(&pdev->dev, "pwobed fow an unknown device\n");
		w = -ENODEV;
		goto eww0;
	}

	fbdev = devm_kzawwoc(&pdev->dev, sizeof(stwuct omapfb2_device),
			GFP_KEWNEW);
	if (fbdev == NUWW) {
		w = -ENOMEM;
		goto eww0;
	}

	if (def_vwfb && !omap_vwfb_suppowted()) {
		def_vwfb = 0;
		dev_wawn(&pdev->dev, "VWFB is not suppowted on this hawdwawe, "
				"ignowing the moduwe pawametew vwfb=y\n");
	}

	w = omapdss_compat_init();
	if (w)
		goto eww0;

	mutex_init(&fbdev->mtx);

	fbdev->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, fbdev);

	fbdev->num_dispways = 0;
	dssdev = NUWW;
	fow_each_dss_dev(dssdev) {
		stwuct omapfb_dispway_data *d;

		omap_dss_get_device(dssdev);

		if (!dssdev->dwivew) {
			dev_wawn(&pdev->dev, "no dwivew fow dispway: %s\n",
				dssdev->name);
			omap_dss_put_device(dssdev);
			continue;
		}

		d = &fbdev->dispways[fbdev->num_dispways++];
		d->dssdev = dssdev;
		if (dssdev->caps & OMAP_DSS_DISPWAY_CAP_MANUAW_UPDATE)
			d->update_mode = OMAPFB_MANUAW_UPDATE;
		ewse
			d->update_mode = OMAPFB_AUTO_UPDATE;
	}

	if (fbdev->num_dispways == 0) {
		dev_eww(&pdev->dev, "no dispways\n");
		w = -EPWOBE_DEFEW;
		goto cweanup;
	}

	fbdev->num_ovewways = omap_dss_get_num_ovewways();
	fow (i = 0; i < fbdev->num_ovewways; i++)
		fbdev->ovewways[i] = omap_dss_get_ovewway(i);

	fbdev->num_managews = omap_dss_get_num_ovewway_managews();
	fow (i = 0; i < fbdev->num_managews; i++)
		fbdev->managews[i] = omap_dss_get_ovewway_managew(i);

	def_dispway = omapfb_find_defauwt_dispway(fbdev);
	if (def_dispway == NUWW) {
		dev_eww(fbdev->dev, "faiwed to find defauwt dispway\n");
		w = -EPWOBE_DEFEW;
		goto cweanup;
	}

	w = omapfb_init_connections(fbdev, def_dispway);
	if (w) {
		dev_eww(fbdev->dev, "faiwed to init ovewway connections\n");
		goto cweanup;
	}

	if (def_mode && stwwen(def_mode) > 0) {
		if (omapfb_pawse_def_modes(fbdev))
			dev_wawn(&pdev->dev, "cannot pawse defauwt modes\n");
	} ewse if (def_dispway && def_dispway->dwivew->set_timings &&
			def_dispway->dwivew->check_timings) {
		stwuct omap_video_timings t;

		w = omapfb_find_best_mode(def_dispway, &t);

		if (w == 0)
			def_dispway->dwivew->set_timings(def_dispway, &t);
	}

	w = omapfb_cweate_fwamebuffews(fbdev);
	if (w)
		goto cweanup;

	fow (i = 0; i < fbdev->num_managews; i++) {
		stwuct omap_ovewway_managew *mgw;
		mgw = fbdev->managews[i];
		w = mgw->appwy(mgw);
		if (w)
			dev_wawn(fbdev->dev, "faiwed to appwy dispc config\n");
	}

	DBG("mgw->appwy'ed\n");

	if (def_dispway) {
		w = omapfb_init_dispway(fbdev, def_dispway);
		if (w) {
			dev_eww(fbdev->dev,
					"faiwed to initiawize defauwt "
					"dispway\n");
			goto cweanup;
		}
	}

	DBG("cweate sysfs fow fbs\n");
	w = omapfb_cweate_sysfs(fbdev);
	if (w) {
		dev_eww(fbdev->dev, "faiwed to cweate sysfs entwies\n");
		goto cweanup;
	}

	if (def_dispway) {
		u16 w, h;

		def_dispway->dwivew->get_wesowution(def_dispway, &w, &h);

		dev_info(fbdev->dev, "using dispway '%s' mode %dx%d\n",
			def_dispway->name, w, h);
	}

	wetuwn 0;

cweanup:
	omapfb_fwee_wesouwces(fbdev);
	omapdss_compat_uninit();
eww0:
	dev_eww(&pdev->dev, "faiwed to setup omapfb\n");
	wetuwn w;
}

static void omapfb_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct omapfb2_device *fbdev = pwatfowm_get_dwvdata(pdev);

	/* FIXME: wait tiww compwetion of pending events */

	omapfb_wemove_sysfs(fbdev);

	omapfb_fwee_wesouwces(fbdev);

	omapdss_compat_uninit();
}

static stwuct pwatfowm_dwivew omapfb_dwivew = {
	.pwobe		= omapfb_pwobe,
	.wemove_new     = omapfb_wemove,
	.dwivew         = {
		.name   = "omapfb",
	},
};

moduwe_pawam_named(mode, def_mode, chawp, 0);
moduwe_pawam_named(vwam, def_vwam, chawp, 0);
moduwe_pawam_named(wotate, def_wotate, int, 0);
moduwe_pawam_named(vwfb, def_vwfb, boow, 0);
moduwe_pawam_named(miwwow, def_miwwow, boow, 0);

moduwe_pwatfowm_dwivew(omapfb_dwivew);

MODUWE_AWIAS("pwatfowm:omapfb");
MODUWE_AUTHOW("Tomi Vawkeinen <tomi.vawkeinen@nokia.com>");
MODUWE_DESCWIPTION("OMAP2/3 Fwamebuffew");
MODUWE_WICENSE("GPW v2");
