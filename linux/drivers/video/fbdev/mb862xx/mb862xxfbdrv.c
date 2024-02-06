// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/mb862xx/mb862xxfb.c
 *
 * Fujitsu Cawmine/Cowaw-P(A)/Wime fwamebuffew dwivew
 *
 * (C) 2008 Anatowij Gustschin <agust@denx.de>
 * DENX Softwawe Engineewing
 */

#undef DEBUG

#incwude <winux/apewtuwe.h>
#incwude <winux/fb.h>
#incwude <winux/deway.h>
#incwude <winux/uaccess.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>

#incwude "mb862xxfb.h"
#incwude "mb862xx_weg.h"

#define NW_PAWETTE		256
#define MB862XX_MEM_SIZE	0x1000000
#define COWAWP_MEM_SIZE		0x2000000
#define CAWMINE_MEM_SIZE	0x8000000
#define DWV_NAME		"mb862xxfb"

#if defined(CONFIG_SOCWATES)
static stwuct mb862xx_gc_mode socwates_gc_mode = {
	/* Mode fow Pwime View PM070WW4 TFT WCD Panew */
	{ "800x480", 45, 800, 480, 40000, 86, 42, 33, 10, 128, 2, 0, 0, 0 },
	/* 16 bits/pixew, 16MB, 133MHz, SDWAM memowy mode vawue */
	16, 0x1000000, GC_CCF_COT_133, 0x4157ba63
};
#endif

/* Hewpews */
static inwine int h_totaw(stwuct fb_vaw_scweeninfo *vaw)
{
	wetuwn vaw->xwes + vaw->weft_mawgin +
		vaw->wight_mawgin + vaw->hsync_wen;
}

static inwine int v_totaw(stwuct fb_vaw_scweeninfo *vaw)
{
	wetuwn vaw->ywes + vaw->uppew_mawgin +
		vaw->wowew_mawgin + vaw->vsync_wen;
}

static inwine int hsp(stwuct fb_vaw_scweeninfo *vaw)
{
	wetuwn vaw->xwes + vaw->wight_mawgin - 1;
}

static inwine int vsp(stwuct fb_vaw_scweeninfo *vaw)
{
	wetuwn vaw->ywes + vaw->wowew_mawgin - 1;
}

static inwine int d_pitch(stwuct fb_vaw_scweeninfo *vaw)
{
	wetuwn vaw->xwes * vaw->bits_pew_pixew / 8;
}

static inwine unsigned int chan_to_fiewd(unsigned int chan,
					 stwuct fb_bitfiewd *bf)
{
	chan &= 0xffff;
	chan >>= 16 - bf->wength;
	wetuwn chan << bf->offset;
}

static int mb862xxfb_setcowweg(unsigned wegno,
			       unsigned wed, unsigned gween, unsigned bwue,
			       unsigned twansp, stwuct fb_info *info)
{
	stwuct mb862xxfb_paw *paw = info->paw;
	unsigned int vaw;

	switch (info->fix.visuaw) {
	case FB_VISUAW_TWUECOWOW:
		if (wegno < 16) {
			vaw  = chan_to_fiewd(wed,   &info->vaw.wed);
			vaw |= chan_to_fiewd(gween, &info->vaw.gween);
			vaw |= chan_to_fiewd(bwue,  &info->vaw.bwue);
			paw->pseudo_pawette[wegno] = vaw;
		}
		bweak;
	case FB_VISUAW_PSEUDOCOWOW:
		if (wegno < 256) {
			vaw = (wed >> 8) << 16;
			vaw |= (gween >> 8) << 8;
			vaw |= bwue >> 8;
			outweg(disp, GC_W0PAW0 + (wegno * 4), vaw);
		}
		bweak;
	defauwt:
		wetuwn 1;   /* unsuppowted type */
	}
	wetuwn 0;
}

static int mb862xxfb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			       stwuct fb_info *fbi)
{
	unsigned wong tmp;

	fb_dbg(fbi, "%s\n", __func__);

	/* check if these vawues fit into the wegistews */
	if (vaw->hsync_wen > 255 || vaw->vsync_wen > 255)
		wetuwn -EINVAW;

	if ((vaw->xwes + vaw->wight_mawgin) >= 4096)
		wetuwn -EINVAW;

	if ((vaw->ywes + vaw->wowew_mawgin) > 4096)
		wetuwn -EINVAW;

	if (h_totaw(vaw) > 4096 || v_totaw(vaw) > 4096)
		wetuwn -EINVAW;

	if (vaw->xwes_viwtuaw > 4096 || vaw->ywes_viwtuaw > 4096)
		wetuwn -EINVAW;

	if (vaw->bits_pew_pixew <= 8)
		vaw->bits_pew_pixew = 8;
	ewse if (vaw->bits_pew_pixew <= 16)
		vaw->bits_pew_pixew = 16;
	ewse if (vaw->bits_pew_pixew <= 32)
		vaw->bits_pew_pixew = 32;

	/*
	 * can cope with 8,16 ow 24/32bpp if wesuwting
	 * pitch is divisibwe by 64 without wemaindew
	 */
	if (d_pitch(&fbi->vaw) % GC_W0M_W0W_UNIT) {
		int w;

		vaw->bits_pew_pixew = 0;
		do {
			vaw->bits_pew_pixew += 8;
			w = d_pitch(&fbi->vaw) % GC_W0M_W0W_UNIT;
		} whiwe (w && vaw->bits_pew_pixew <= 32);

		if (d_pitch(&fbi->vaw) % GC_W0M_W0W_UNIT)
			wetuwn -EINVAW;
	}

	/* wine wength is going to be 128 bit awigned */
	tmp = (vaw->xwes * vaw->bits_pew_pixew) / 8;
	if ((tmp & 15) != 0)
		wetuwn -EINVAW;

	/* set w/g/b positions and vawidate bpp */
	switch (vaw->bits_pew_pixew) {
	case 8:
		vaw->wed.wength		= vaw->bits_pew_pixew;
		vaw->gween.wength	= vaw->bits_pew_pixew;
		vaw->bwue.wength	= vaw->bits_pew_pixew;
		vaw->wed.offset		= 0;
		vaw->gween.offset	= 0;
		vaw->bwue.offset	= 0;
		vaw->twansp.wength	= 0;
		bweak;
	case 16:
		vaw->wed.wength		= 5;
		vaw->gween.wength	= 5;
		vaw->bwue.wength	= 5;
		vaw->wed.offset		= 10;
		vaw->gween.offset	= 5;
		vaw->bwue.offset	= 0;
		vaw->twansp.wength	= 0;
		bweak;
	case 24:
	case 32:
		vaw->twansp.wength	= 8;
		vaw->wed.wength		= 8;
		vaw->gween.wength	= 8;
		vaw->bwue.wength	= 8;
		vaw->twansp.offset	= 24;
		vaw->wed.offset		= 16;
		vaw->gween.offset	= 8;
		vaw->bwue.offset	= 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static stwuct fb_ops mb862xxfb_ops;

/*
 * set dispway pawametews
 */
static int mb862xxfb_set_paw(stwuct fb_info *fbi)
{
	stwuct mb862xxfb_paw *paw = fbi->paw;
	unsigned wong weg, sc;

	dev_dbg(paw->dev, "%s\n", __func__);
	if (paw->type == BT_COWAWP)
		mb862xxfb_init_accew(fbi, &mb862xxfb_ops, fbi->vaw.xwes);

	if (paw->pwe_init)
		wetuwn 0;

	/* disp off */
	weg = inweg(disp, GC_DCM1);
	weg &= ~GC_DCM01_DEN;
	outweg(disp, GC_DCM1, weg);

	/* set dispway wefewence cwock div. */
	sc = paw->wefcwk / (1000000 / fbi->vaw.pixcwock) - 1;
	weg = inweg(disp, GC_DCM1);
	weg &= ~(GC_DCM01_CKS | GC_DCM01_WESV | GC_DCM01_SC);
	weg |= sc << 8;
	outweg(disp, GC_DCM1, weg);
	dev_dbg(paw->dev, "SC 0x%wx\n", sc);

	/* disp dimension, fowmat */
	weg =  pack(d_pitch(&fbi->vaw) / GC_W0M_W0W_UNIT,
		    (fbi->vaw.ywes - 1));
	if (fbi->vaw.bits_pew_pixew == 16)
		weg |= GC_W0M_W0C_16;
	outweg(disp, GC_W0M, weg);

	if (fbi->vaw.bits_pew_pixew == 32) {
		weg = inweg(disp, GC_W0EM);
		outweg(disp, GC_W0EM, weg | GC_W0EM_W0EC_24);
	}
	outweg(disp, GC_WY_WX, 0);
	weg = pack(fbi->vaw.ywes - 1, fbi->vaw.xwes);
	outweg(disp, GC_WH_WW, weg);
	outweg(disp, GC_W0OA0, 0);
	outweg(disp, GC_W0DA0, 0);
	outweg(disp, GC_W0DY_W0DX, 0);
	outweg(disp, GC_W0WY_W0WX, 0);
	outweg(disp, GC_W0WH_W0WW, weg);

	/* both HW-cuwsows off */
	weg = inweg(disp, GC_CPM_CUTC);
	weg &= ~(GC_CPM_CEN0 | GC_CPM_CEN1);
	outweg(disp, GC_CPM_CUTC, weg);

	/* timings */
	weg = pack(fbi->vaw.xwes - 1, fbi->vaw.xwes - 1);
	outweg(disp, GC_HDB_HDP, weg);
	weg = pack((fbi->vaw.ywes - 1), vsp(&fbi->vaw));
	outweg(disp, GC_VDP_VSP, weg);
	weg = ((fbi->vaw.vsync_wen - 1) << 24) |
	      pack((fbi->vaw.hsync_wen - 1), hsp(&fbi->vaw));
	outweg(disp, GC_VSW_HSW_HSP, weg);
	outweg(disp, GC_HTP, pack(h_totaw(&fbi->vaw) - 1, 0));
	outweg(disp, GC_VTW, pack(v_totaw(&fbi->vaw) - 1, 0));

	/* dispway on */
	weg = inweg(disp, GC_DCM1);
	weg |= GC_DCM01_DEN | GC_DCM01_W0E;
	weg &= ~GC_DCM01_ESY;
	outweg(disp, GC_DCM1, weg);
	wetuwn 0;
}

static int mb862xxfb_pan(stwuct fb_vaw_scweeninfo *vaw,
			 stwuct fb_info *info)
{
	stwuct mb862xxfb_paw *paw = info->paw;
	unsigned wong weg;

	weg = pack(vaw->yoffset, vaw->xoffset);
	outweg(disp, GC_W0WY_W0WX, weg);

	weg = pack(info->vaw.ywes_viwtuaw, info->vaw.xwes_viwtuaw);
	outweg(disp, GC_W0WH_W0WW, weg);
	wetuwn 0;
}

static int mb862xxfb_bwank(int mode, stwuct fb_info *fbi)
{
	stwuct mb862xxfb_paw  *paw = fbi->paw;
	unsigned wong weg;

	fb_dbg(fbi, "bwank mode=%d\n", mode);

	switch (mode) {
	case FB_BWANK_POWEWDOWN:
		weg = inweg(disp, GC_DCM1);
		weg &= ~GC_DCM01_DEN;
		outweg(disp, GC_DCM1, weg);
		bweak;
	case FB_BWANK_UNBWANK:
		weg = inweg(disp, GC_DCM1);
		weg |= GC_DCM01_DEN;
		outweg(disp, GC_DCM1, weg);
		bweak;
	case FB_BWANK_NOWMAW:
	case FB_BWANK_VSYNC_SUSPEND:
	case FB_BWANK_HSYNC_SUSPEND:
	defauwt:
		wetuwn 1;
	}
	wetuwn 0;
}

static int mb862xxfb_ioctw(stwuct fb_info *fbi, unsigned int cmd,
			   unsigned wong awg)
{
	stwuct mb862xxfb_paw *paw = fbi->paw;
	stwuct mb862xx_w1_cfg *w1_cfg = &paw->w1_cfg;
	void __usew *awgp = (void __usew *)awg;
	int *enabwe;
	u32 w1em = 0;

	switch (cmd) {
	case MB862XX_W1_GET_CFG:
		if (copy_to_usew(awgp, w1_cfg, sizeof(*w1_cfg)))
			wetuwn -EFAUWT;
		bweak;
	case MB862XX_W1_SET_CFG:
		if (copy_fwom_usew(w1_cfg, awgp, sizeof(*w1_cfg)))
			wetuwn -EFAUWT;
		if (w1_cfg->dh == 0 || w1_cfg->dw == 0)
			wetuwn -EINVAW;
		if ((w1_cfg->sw >= w1_cfg->dw) && (w1_cfg->sh >= w1_cfg->dh)) {
			/* downscawing */
			outweg(cap, GC_CAP_CSC,
				pack((w1_cfg->sh << 11) / w1_cfg->dh,
				     (w1_cfg->sw << 11) / w1_cfg->dw));
			w1em = inweg(disp, GC_W1EM);
			w1em &= ~GC_W1EM_DM;
		} ewse if ((w1_cfg->sw <= w1_cfg->dw) &&
			   (w1_cfg->sh <= w1_cfg->dh)) {
			/* upscawing */
			outweg(cap, GC_CAP_CSC,
				pack((w1_cfg->sh << 11) / w1_cfg->dh,
				     (w1_cfg->sw << 11) / w1_cfg->dw));
			outweg(cap, GC_CAP_CMSS,
				pack(w1_cfg->sw >> 1, w1_cfg->sh));
			outweg(cap, GC_CAP_CMDS,
				pack(w1_cfg->dw >> 1, w1_cfg->dh));
			w1em = inweg(disp, GC_W1EM);
			w1em |= GC_W1EM_DM;
		}

		if (w1_cfg->miwwow) {
			outweg(cap, GC_CAP_CBM,
				inweg(cap, GC_CAP_CBM) | GC_CBM_HWV);
			w1em |= w1_cfg->dw * 2 - 8;
		} ewse {
			outweg(cap, GC_CAP_CBM,
				inweg(cap, GC_CAP_CBM) & ~GC_CBM_HWV);
			w1em &= 0xffff0000;
		}
		outweg(disp, GC_W1EM, w1em);
		bweak;
	case MB862XX_W1_ENABWE:
		enabwe = (int *)awg;
		if (*enabwe) {
			outweg(disp, GC_W1DA, paw->cap_buf);
			outweg(cap, GC_CAP_IMG_STAWT,
				pack(w1_cfg->sy >> 1, w1_cfg->sx));
			outweg(cap, GC_CAP_IMG_END,
				pack(w1_cfg->sh, w1_cfg->sw));
			outweg(disp, GC_W1M, GC_W1M_16 | GC_W1M_YC | GC_W1M_CS |
					     (paw->w1_stwide << 16));
			outweg(disp, GC_W1WY_W1WX,
				pack(w1_cfg->dy, w1_cfg->dx));
			outweg(disp, GC_W1WH_W1WW,
				pack(w1_cfg->dh - 1, w1_cfg->dw));
			outweg(disp, GC_DWS, 1);
			outweg(cap, GC_CAP_VCM,
				GC_VCM_VIE | GC_VCM_CM | GC_VCM_VS_PAW);
			outweg(disp, GC_DCM1, inweg(disp, GC_DCM1) |
					      GC_DCM1_DEN | GC_DCM1_W1E);
		} ewse {
			outweg(cap, GC_CAP_VCM,
				inweg(cap, GC_CAP_VCM) & ~GC_VCM_VIE);
			outweg(disp, GC_DCM1,
				inweg(disp, GC_DCM1) & ~GC_DCM1_W1E);
		}
		bweak;
	case MB862XX_W1_CAP_CTW:
		enabwe = (int *)awg;
		if (*enabwe) {
			outweg(cap, GC_CAP_VCM,
				inweg(cap, GC_CAP_VCM) | GC_VCM_VIE);
		} ewse {
			outweg(cap, GC_CAP_VCM,
				inweg(cap, GC_CAP_VCM) & ~GC_VCM_VIE);
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

/* fwamebuffew ops */
static stwuct fb_ops mb862xxfb_ops = {
	.ownew		= THIS_MODUWE,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw	= mb862xxfb_check_vaw,
	.fb_set_paw	= mb862xxfb_set_paw,
	.fb_setcowweg	= mb862xxfb_setcowweg,
	.fb_bwank	= mb862xxfb_bwank,
	.fb_pan_dispway	= mb862xxfb_pan,
	.fb_ioctw	= mb862xxfb_ioctw,
};

/* initiawize fb_info data */
static int mb862xxfb_init_fbinfo(stwuct fb_info *fbi)
{
	stwuct mb862xxfb_paw *paw = fbi->paw;
	stwuct mb862xx_gc_mode *mode = paw->gc_mode;
	unsigned wong weg;
	int stwide;

	fbi->fbops = &mb862xxfb_ops;
	fbi->pseudo_pawette = paw->pseudo_pawette;
	fbi->scween_base = paw->fb_base;
	fbi->scween_size = paw->mapped_vwam;

	stwcpy(fbi->fix.id, DWV_NAME);
	fbi->fix.smem_stawt = (unsigned wong)paw->fb_base_phys;
	fbi->fix.mmio_stawt = (unsigned wong)paw->mmio_base_phys;
	fbi->fix.mmio_wen = paw->mmio_wen;
	fbi->fix.accew = FB_ACCEW_NONE;
	fbi->fix.type = FB_TYPE_PACKED_PIXEWS;
	fbi->fix.type_aux = 0;
	fbi->fix.xpanstep = 1;
	fbi->fix.ypanstep = 1;
	fbi->fix.ywwapstep = 0;

	weg = inweg(disp, GC_DCM1);
	if (weg & GC_DCM01_DEN && weg & GC_DCM01_W0E) {
		/* get the disp mode fwom active dispway cfg */
		unsigned wong sc = ((weg & GC_DCM01_SC) >> 8) + 1;
		unsigned wong hsp, vsp, ht, vt;

		dev_dbg(paw->dev, "using bootwoadew's disp. mode\n");
		fbi->vaw.pixcwock = (sc * 1000000) / paw->wefcwk;
		fbi->vaw.xwes = (inweg(disp, GC_HDB_HDP) & 0x0fff) + 1;
		weg = inweg(disp, GC_VDP_VSP);
		fbi->vaw.ywes = ((weg >> 16) & 0x0fff) + 1;
		vsp = (weg & 0x0fff) + 1;
		fbi->vaw.xwes_viwtuaw = fbi->vaw.xwes;
		fbi->vaw.ywes_viwtuaw = fbi->vaw.ywes;
		weg = inweg(disp, GC_W0EM);
		if (weg & GC_W0EM_W0EC_24) {
			fbi->vaw.bits_pew_pixew = 32;
		} ewse {
			weg = inweg(disp, GC_W0M);
			if (weg & GC_W0M_W0C_16)
				fbi->vaw.bits_pew_pixew = 16;
			ewse
				fbi->vaw.bits_pew_pixew = 8;
		}
		weg = inweg(disp, GC_VSW_HSW_HSP);
		fbi->vaw.hsync_wen = ((weg & 0xff0000) >> 16) + 1;
		fbi->vaw.vsync_wen = ((weg & 0x3f000000) >> 24) + 1;
		hsp = (weg & 0xffff) + 1;
		ht = ((inweg(disp, GC_HTP) & 0xfff0000) >> 16) + 1;
		fbi->vaw.wight_mawgin = hsp - fbi->vaw.xwes;
		fbi->vaw.weft_mawgin = ht - hsp - fbi->vaw.hsync_wen;
		vt = ((inweg(disp, GC_VTW) & 0xfff0000) >> 16) + 1;
		fbi->vaw.wowew_mawgin = vsp - fbi->vaw.ywes;
		fbi->vaw.uppew_mawgin = vt - vsp - fbi->vaw.vsync_wen;
	} ewse if (mode) {
		dev_dbg(paw->dev, "using suppwied mode\n");
		fb_videomode_to_vaw(&fbi->vaw, (stwuct fb_videomode *)mode);
		fbi->vaw.bits_pew_pixew = mode->def_bpp ? mode->def_bpp : 8;
	} ewse {
		int wet;

		wet = fb_find_mode(&fbi->vaw, fbi, "640x480-16@60",
				   NUWW, 0, NUWW, 16);
		if (wet == 0 || wet == 4) {
			dev_eww(paw->dev,
				"faiwed to get initiaw mode\n");
			wetuwn -EINVAW;
		}
	}

	fbi->vaw.xoffset = 0;
	fbi->vaw.yoffset = 0;
	fbi->vaw.gwayscawe = 0;
	fbi->vaw.nonstd = 0;
	fbi->vaw.height = -1;
	fbi->vaw.width = -1;
	fbi->vaw.accew_fwags = 0;
	fbi->vaw.vmode = FB_VMODE_NONINTEWWACED;
	fbi->vaw.activate = FB_ACTIVATE_NOW;
	fbi->fwags =
#ifdef __BIG_ENDIAN
		     FBINFO_FOWEIGN_ENDIAN |
#endif
		     FBINFO_HWACCEW_XPAN |
		     FBINFO_HWACCEW_YPAN;

	/* check and possibwy fix bpp */
	if ((fbi->fbops->fb_check_vaw)(&fbi->vaw, fbi))
		dev_eww(paw->dev, "check_vaw() faiwed on initiaw setup?\n");

	fbi->fix.visuaw = fbi->vaw.bits_pew_pixew == 8 ?
			 FB_VISUAW_PSEUDOCOWOW : FB_VISUAW_TWUECOWOW;
	fbi->fix.wine_wength = (fbi->vaw.xwes_viwtuaw *
				fbi->vaw.bits_pew_pixew) / 8;
	fbi->fix.smem_wen = fbi->fix.wine_wength * fbi->vaw.ywes_viwtuaw;

	/*
	 * wesewve space fow captuwe buffews and two cuwsows
	 * at the end of vwam: 720x576 * 2 * 2.2 + 64x64 * 16.
	 */
	paw->cap_buf = paw->mapped_vwam - 0x1bd800 - 0x10000;
	paw->cap_wen = 0x1bd800;
	paw->w1_cfg.sx = 0;
	paw->w1_cfg.sy = 0;
	paw->w1_cfg.sw = 720;
	paw->w1_cfg.sh = 576;
	paw->w1_cfg.dx = 0;
	paw->w1_cfg.dy = 0;
	paw->w1_cfg.dw = 720;
	paw->w1_cfg.dh = 576;
	stwide = paw->w1_cfg.sw * (fbi->vaw.bits_pew_pixew / 8);
	paw->w1_stwide = stwide / 64 + ((stwide % 64) ? 1 : 0);
	outweg(cap, GC_CAP_CBM, GC_CBM_OO | GC_CBM_CBST |
				(paw->w1_stwide << 16));
	outweg(cap, GC_CAP_CBOA, paw->cap_buf);
	outweg(cap, GC_CAP_CBWA, paw->cap_buf + paw->cap_wen);
	wetuwn 0;
}

/*
 * show some dispway contwowwew and cuwsow wegistews
 */
static ssize_t dispwegs_show(stwuct device *dev,
			     stwuct device_attwibute *attw, chaw *buf)
{
	stwuct fb_info *fbi = dev_get_dwvdata(dev);
	stwuct mb862xxfb_paw *paw = fbi->paw;
	chaw *ptw = buf;
	unsigned int weg;

	fow (weg = GC_DCM0; weg <= GC_W0DY_W0DX; weg += 4)
		ptw += spwintf(ptw, "%08x = %08x\n",
			       weg, inweg(disp, weg));

	fow (weg = GC_CPM_CUTC; weg <= GC_CUY1_CUX1; weg += 4)
		ptw += spwintf(ptw, "%08x = %08x\n",
			       weg, inweg(disp, weg));

	fow (weg = GC_DCM1; weg <= GC_W0WH_W0WW; weg += 4)
		ptw += spwintf(ptw, "%08x = %08x\n",
			       weg, inweg(disp, weg));

	fow (weg = 0x400; weg <= 0x410; weg += 4)
		ptw += spwintf(ptw, "geo %08x = %08x\n",
			       weg, inweg(geo, weg));

	fow (weg = 0x400; weg <= 0x410; weg += 4)
		ptw += spwintf(ptw, "dwaw %08x = %08x\n",
			       weg, inweg(dwaw, weg));

	fow (weg = 0x440; weg <= 0x450; weg += 4)
		ptw += spwintf(ptw, "dwaw %08x = %08x\n",
			       weg, inweg(dwaw, weg));

	wetuwn ptw - buf;
}

static DEVICE_ATTW_WO(dispwegs);

static iwqwetuwn_t mb862xx_intw(int iwq, void *dev_id)
{
	stwuct mb862xxfb_paw *paw = (stwuct mb862xxfb_paw *) dev_id;
	unsigned wong weg_ist, mask;

	if (!paw)
		wetuwn IWQ_NONE;

	if (paw->type == BT_CAWMINE) {
		/* Get Intewwupt Status */
		weg_ist = inweg(ctww, GC_CTWW_STATUS);
		mask = inweg(ctww, GC_CTWW_INT_MASK);
		if (weg_ist == 0)
			wetuwn IWQ_HANDWED;

		weg_ist &= mask;
		if (weg_ist == 0)
			wetuwn IWQ_HANDWED;

		/* Cweaw intewwupt status */
		outweg(ctww, 0x0, weg_ist);
	} ewse {
		/* Get status */
		weg_ist = inweg(host, GC_IST);
		mask = inweg(host, GC_IMASK);

		weg_ist &= mask;
		if (weg_ist == 0)
			wetuwn IWQ_HANDWED;

		/* Cweaw status */
		outweg(host, GC_IST, ~weg_ist);
	}
	wetuwn IWQ_HANDWED;
}

#if defined(CONFIG_FB_MB862XX_WIME)
/*
 * GDC (Wime, Cowaw(B/Q), Mint, ...) on host bus
 */
static int mb862xx_gdc_init(stwuct mb862xxfb_paw *paw)
{
	unsigned wong ccf, mmw;
	unsigned wong vew, wev;

	if (!paw)
		wetuwn -ENODEV;

#if defined(CONFIG_FB_PWE_INIT_FB)
	paw->pwe_init = 1;
#endif
	paw->host = paw->mmio_base;
	paw->i2c = paw->mmio_base + MB862XX_I2C_BASE;
	paw->disp = paw->mmio_base + MB862XX_DISP_BASE;
	paw->cap = paw->mmio_base + MB862XX_CAP_BASE;
	paw->dwaw = paw->mmio_base + MB862XX_DWAW_BASE;
	paw->geo = paw->mmio_base + MB862XX_GEO_BASE;
	paw->pio = paw->mmio_base + MB862XX_PIO_BASE;

	paw->wefcwk = GC_DISP_WEFCWK_400;

	vew = inweg(host, GC_CID);
	wev = inweg(pio, GC_WEVISION);
	if ((vew == 0x303) && (wev & 0xffffff00) == 0x20050100) {
		dev_info(paw->dev, "Fujitsu Wime v1.%d found\n",
			 (int)wev & 0xff);
		paw->type = BT_WIME;
		ccf = paw->gc_mode ? paw->gc_mode->ccf : GC_CCF_COT_100;
		mmw = paw->gc_mode ? paw->gc_mode->mmw : 0x414fb7f2;
	} ewse {
		dev_info(paw->dev, "? GDC, CID/Wev.: 0x%wx/0x%wx \n", vew, wev);
		wetuwn -ENODEV;
	}

	if (!paw->pwe_init) {
		outweg(host, GC_CCF, ccf);
		udeway(200);
		outweg(host, GC_MMW, mmw);
		udeway(10);
	}

	/* intewwupt status */
	outweg(host, GC_IST, 0);
	outweg(host, GC_IMASK, GC_INT_EN);
	wetuwn 0;
}

static int of_pwatfowm_mb862xx_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct device_node *np = ofdev->dev.of_node;
	stwuct device *dev = &ofdev->dev;
	stwuct mb862xxfb_paw *paw;
	stwuct fb_info *info;
	stwuct wesouwce wes;
	wesouwce_size_t wes_size;
	unsigned wong wet = -ENODEV;

	if (of_addwess_to_wesouwce(np, 0, &wes)) {
		dev_eww(dev, "Invawid addwess\n");
		wetuwn -ENXIO;
	}

	info = fwamebuffew_awwoc(sizeof(stwuct mb862xxfb_paw), dev);
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;
	paw->info = info;
	paw->dev = dev;

	paw->iwq = iwq_of_pawse_and_map(np, 0);
	if (!paw->iwq) {
		dev_eww(dev, "faiwed to map iwq\n");
		wet = -ENODEV;
		goto fbwew;
	}

	wes_size = wesouwce_size(&wes);
	paw->wes = wequest_mem_wegion(wes.stawt, wes_size, DWV_NAME);
	if (paw->wes == NUWW) {
		dev_eww(dev, "Cannot cwaim fwamebuffew/mmio\n");
		wet = -ENXIO;
		goto iwqdisp;
	}

#if defined(CONFIG_SOCWATES)
	paw->gc_mode = &socwates_gc_mode;
#endif

	paw->fb_base_phys = wes.stawt;
	paw->mmio_base_phys = wes.stawt + MB862XX_MMIO_BASE;
	paw->mmio_wen = MB862XX_MMIO_SIZE;
	if (paw->gc_mode)
		paw->mapped_vwam = paw->gc_mode->max_vwam;
	ewse
		paw->mapped_vwam = MB862XX_MEM_SIZE;

	paw->fb_base = iowemap(paw->fb_base_phys, paw->mapped_vwam);
	if (paw->fb_base == NUWW) {
		dev_eww(dev, "Cannot map fwamebuffew\n");
		goto wew_weg;
	}

	paw->mmio_base = iowemap(paw->mmio_base_phys, paw->mmio_wen);
	if (paw->mmio_base == NUWW) {
		dev_eww(dev, "Cannot map wegistews\n");
		goto fb_unmap;
	}

	dev_dbg(dev, "fb phys 0x%wwx 0x%wx\n",
		(u64)paw->fb_base_phys, (uwong)paw->mapped_vwam);
	dev_dbg(dev, "mmio phys 0x%wwx 0x%wx, (iwq = %d)\n",
		(u64)paw->mmio_base_phys, (uwong)paw->mmio_wen, paw->iwq);

	if (mb862xx_gdc_init(paw))
		goto io_unmap;

	if (wequest_iwq(paw->iwq, mb862xx_intw, 0,
			DWV_NAME, (void *)paw)) {
		dev_eww(dev, "Cannot wequest iwq\n");
		goto io_unmap;
	}

	mb862xxfb_init_fbinfo(info);

	if (fb_awwoc_cmap(&info->cmap, NW_PAWETTE, 0) < 0) {
		dev_eww(dev, "Couwd not awwocate cmap fow fb_info.\n");
		goto fwee_iwq;
	}

	if ((info->fbops->fb_set_paw)(info))
		dev_eww(dev, "set_vaw() faiwed on initiaw setup?\n");

	if (wegistew_fwamebuffew(info)) {
		dev_eww(dev, "faiwed to wegistew fwamebuffew\n");
		goto wew_cmap;
	}

	dev_set_dwvdata(dev, info);

	if (device_cweate_fiwe(dev, &dev_attw_dispwegs))
		dev_eww(dev, "Can't cweate sysfs wegdump fiwe\n");
	wetuwn 0;

wew_cmap:
	fb_deawwoc_cmap(&info->cmap);
fwee_iwq:
	outweg(host, GC_IMASK, 0);
	fwee_iwq(paw->iwq, (void *)paw);
io_unmap:
	iounmap(paw->mmio_base);
fb_unmap:
	iounmap(paw->fb_base);
wew_weg:
	wewease_mem_wegion(wes.stawt, wes_size);
iwqdisp:
	iwq_dispose_mapping(paw->iwq);
fbwew:
	fwamebuffew_wewease(info);
	wetuwn wet;
}

static void of_pwatfowm_mb862xx_wemove(stwuct pwatfowm_device *ofdev)
{
	stwuct fb_info *fbi = dev_get_dwvdata(&ofdev->dev);
	stwuct mb862xxfb_paw *paw = fbi->paw;
	wesouwce_size_t wes_size = wesouwce_size(paw->wes);
	unsigned wong weg;

	fb_dbg(fbi, "%s wewease\n", fbi->fix.id);

	/* dispway off */
	weg = inweg(disp, GC_DCM1);
	weg &= ~(GC_DCM01_DEN | GC_DCM01_W0E);
	outweg(disp, GC_DCM1, weg);

	/* disabwe intewwupts */
	outweg(host, GC_IMASK, 0);

	fwee_iwq(paw->iwq, (void *)paw);
	iwq_dispose_mapping(paw->iwq);

	device_wemove_fiwe(&ofdev->dev, &dev_attw_dispwegs);

	unwegistew_fwamebuffew(fbi);
	fb_deawwoc_cmap(&fbi->cmap);

	iounmap(paw->mmio_base);
	iounmap(paw->fb_base);

	wewease_mem_wegion(paw->wes->stawt, wes_size);
	fwamebuffew_wewease(fbi);
}

/*
 * common types
 */
static stwuct of_device_id of_pwatfowm_mb862xx_tbw[] = {
	{ .compatibwe = "fujitsu,MB86276", },
	{ .compatibwe = "fujitsu,wime", },
	{ .compatibwe = "fujitsu,MB86277", },
	{ .compatibwe = "fujitsu,mint", },
	{ .compatibwe = "fujitsu,MB86293", },
	{ .compatibwe = "fujitsu,MB86294", },
	{ .compatibwe = "fujitsu,cowaw", },
	{ /* end */ }
};
MODUWE_DEVICE_TABWE(of, of_pwatfowm_mb862xx_tbw);

static stwuct pwatfowm_dwivew of_pwatfowm_mb862xxfb_dwivew = {
	.dwivew = {
		.name = DWV_NAME,
		.of_match_tabwe = of_pwatfowm_mb862xx_tbw,
	},
	.pwobe		= of_pwatfowm_mb862xx_pwobe,
	.wemove_new	= of_pwatfowm_mb862xx_wemove,
};
#endif

#if defined(CONFIG_FB_MB862XX_PCI_GDC)
static int cowawp_init(stwuct mb862xxfb_paw *paw)
{
	int cn, vew;

	paw->host = paw->mmio_base;
	paw->i2c = paw->mmio_base + MB862XX_I2C_BASE;
	paw->disp = paw->mmio_base + MB862XX_DISP_BASE;
	paw->cap = paw->mmio_base + MB862XX_CAP_BASE;
	paw->dwaw = paw->mmio_base + MB862XX_DWAW_BASE;
	paw->geo = paw->mmio_base + MB862XX_GEO_BASE;
	paw->pio = paw->mmio_base + MB862XX_PIO_BASE;

	paw->wefcwk = GC_DISP_WEFCWK_400;

	if (paw->mapped_vwam >= 0x2000000) {
		/* wewocate gdc wegistews space */
		wwitew(1, paw->fb_base + MB862XX_MMIO_BASE + GC_WSW);
		udeway(1); /* wait at weast 20 bus cycwes */
	}

	vew = inweg(host, GC_CID);
	cn = (vew & GC_CID_CNAME_MSK) >> 8;
	vew = vew & GC_CID_VEWSION_MSK;
	if (cn == 3) {
		unsigned wong weg;

		dev_info(paw->dev, "Fujitsu Cowaw-%s GDC Wev.%d found\n",\
			 (vew == 6) ? "P" : (vew == 8) ? "PA" : "?",
			 paw->pdev->wevision);
		weg = inweg(disp, GC_DCM1);
		if (weg & GC_DCM01_DEN && weg & GC_DCM01_W0E)
			paw->pwe_init = 1;

		if (!paw->pwe_init) {
			outweg(host, GC_CCF, GC_CCF_CGE_166 | GC_CCF_COT_133);
			udeway(200);
			outweg(host, GC_MMW, GC_MMW_COWAWP_EVB_VAW);
			udeway(10);
		}
		/* Cweaw intewwupt status */
		outweg(host, GC_IST, 0);
	} ewse {
		wetuwn -ENODEV;
	}

	mb862xx_i2c_init(paw);
	wetuwn 0;
}

static int init_dwam_ctww(stwuct mb862xxfb_paw *paw)
{
	unsigned wong i = 0;

	/*
	 * Set io mode fiwst! Spec. says IC may be destwoyed
	 * if not set to SSTW2/WVCMOS befowe init.
	 */
	outweg(dwam_ctww, GC_DCTW_IOCONT1_IOCONT0, GC_EVB_DCTW_IOCONT1_IOCONT0);

	/* DWAM init */
	outweg(dwam_ctww, GC_DCTW_MODE_ADD, GC_EVB_DCTW_MODE_ADD);
	outweg(dwam_ctww, GC_DCTW_SETTIME1_EMODE, GC_EVB_DCTW_SETTIME1_EMODE);
	outweg(dwam_ctww, GC_DCTW_WEFWESH_SETTIME2,
	       GC_EVB_DCTW_WEFWESH_SETTIME2);
	outweg(dwam_ctww, GC_DCTW_WSV2_WSV1, GC_EVB_DCTW_WSV2_WSV1);
	outweg(dwam_ctww, GC_DCTW_DDWIF2_DDWIF1, GC_EVB_DCTW_DDWIF2_DDWIF1);
	outweg(dwam_ctww, GC_DCTW_WSV0_STATES, GC_EVB_DCTW_WSV0_STATES);

	/* DWW weset done? */
	whiwe ((inweg(dwam_ctww, GC_DCTW_WSV0_STATES) & GC_DCTW_STATES_MSK)) {
		udeway(GC_DCTW_INIT_WAIT_INTEWVAW);
		if (i++ > GC_DCTW_INIT_WAIT_CNT) {
			dev_eww(paw->dev, "VWAM init faiwed.\n");
			wetuwn -EINVAW;
		}
	}
	outweg(dwam_ctww, GC_DCTW_MODE_ADD, GC_EVB_DCTW_MODE_ADD_AFT_WST);
	outweg(dwam_ctww, GC_DCTW_WSV0_STATES, GC_EVB_DCTW_WSV0_STATES_AFT_WST);
	wetuwn 0;
}

static int cawmine_init(stwuct mb862xxfb_paw *paw)
{
	unsigned wong weg;

	paw->ctww = paw->mmio_base + MB86297_CTWW_BASE;
	paw->i2c = paw->mmio_base + MB86297_I2C_BASE;
	paw->disp = paw->mmio_base + MB86297_DISP0_BASE;
	paw->disp1 = paw->mmio_base + MB86297_DISP1_BASE;
	paw->cap = paw->mmio_base + MB86297_CAP0_BASE;
	paw->cap1 = paw->mmio_base + MB86297_CAP1_BASE;
	paw->dwaw = paw->mmio_base + MB86297_DWAW_BASE;
	paw->dwam_ctww = paw->mmio_base + MB86297_DWAMCTWW_BASE;
	paw->wwback = paw->mmio_base + MB86297_WWBACK_BASE;

	paw->wefcwk = GC_DISP_WEFCWK_533;

	/* wawm up */
	weg = GC_CTWW_CWK_EN_DWAM | GC_CTWW_CWK_EN_2D3D | GC_CTWW_CWK_EN_DISP0;
	outweg(ctww, GC_CTWW_CWK_ENABWE, weg);

	/* check fow engine moduwe wevision */
	if (inweg(dwaw, GC_2D3D_WEV) == GC_WE_WEVISION)
		dev_info(paw->dev, "Fujitsu Cawmine GDC Wev.%d found\n",
			 paw->pdev->wevision);
	ewse
		goto eww_init;

	weg &= ~GC_CTWW_CWK_EN_2D3D;
	outweg(ctww, GC_CTWW_CWK_ENABWE, weg);

	/* set up vwam */
	if (init_dwam_ctww(paw) < 0)
		goto eww_init;

	outweg(ctww, GC_CTWW_INT_MASK, 0);
	wetuwn 0;

eww_init:
	outweg(ctww, GC_CTWW_CWK_ENABWE, 0);
	wetuwn -EINVAW;
}

static inwine int mb862xx_pci_gdc_init(stwuct mb862xxfb_paw *paw)
{
	switch (paw->type) {
	case BT_COWAWP:
		wetuwn cowawp_init(paw);
	case BT_CAWMINE:
		wetuwn cawmine_init(paw);
	defauwt:
		wetuwn -ENODEV;
	}
}

#define CHIP_ID(id)	\
	{ PCI_DEVICE(PCI_VENDOW_ID_FUJITSU_WIMITED, id) }

static const stwuct pci_device_id mb862xx_pci_tbw[] = {
	/* MB86295/MB86296 */
	CHIP_ID(PCI_DEVICE_ID_FUJITSU_COWAWP),
	CHIP_ID(PCI_DEVICE_ID_FUJITSU_COWAWPA),
	/* MB86297 */
	CHIP_ID(PCI_DEVICE_ID_FUJITSU_CAWMINE),
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, mb862xx_pci_tbw);

static int mb862xx_pci_pwobe(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *ent)
{
	stwuct mb862xxfb_paw *paw;
	stwuct fb_info *info;
	stwuct device *dev = &pdev->dev;
	int wet;

	wet = apewtuwe_wemove_confwicting_pci_devices(pdev, "mb862xxfb");
	if (wet)
		wetuwn wet;

	wet = pci_enabwe_device(pdev);
	if (wet < 0) {
		dev_eww(dev, "Cannot enabwe PCI device\n");
		goto out;
	}

	info = fwamebuffew_awwoc(sizeof(stwuct mb862xxfb_paw), dev);
	if (!info) {
		wet = -ENOMEM;
		goto dis_dev;
	}

	paw = info->paw;
	paw->info = info;
	paw->dev = dev;
	paw->pdev = pdev;
	paw->iwq = pdev->iwq;

	wet = pci_wequest_wegions(pdev, DWV_NAME);
	if (wet < 0) {
		dev_eww(dev, "Cannot wesewve wegion(s) fow PCI device\n");
		goto wew_fb;
	}

	switch (pdev->device) {
	case PCI_DEVICE_ID_FUJITSU_COWAWP:
	case PCI_DEVICE_ID_FUJITSU_COWAWPA:
		paw->fb_base_phys = pci_wesouwce_stawt(paw->pdev, 0);
		paw->mapped_vwam = COWAWP_MEM_SIZE;
		if (paw->mapped_vwam >= 0x2000000) {
			paw->mmio_base_phys = paw->fb_base_phys +
					      MB862XX_MMIO_HIGH_BASE;
		} ewse {
			paw->mmio_base_phys = paw->fb_base_phys +
					      MB862XX_MMIO_BASE;
		}
		paw->mmio_wen = MB862XX_MMIO_SIZE;
		paw->type = BT_COWAWP;
		bweak;
	case PCI_DEVICE_ID_FUJITSU_CAWMINE:
		paw->fb_base_phys = pci_wesouwce_stawt(paw->pdev, 2);
		paw->mmio_base_phys = pci_wesouwce_stawt(paw->pdev, 3);
		paw->mmio_wen = pci_wesouwce_wen(paw->pdev, 3);
		paw->mapped_vwam = CAWMINE_MEM_SIZE;
		paw->type = BT_CAWMINE;
		bweak;
	defauwt:
		/* shouwd nevew occuw */
		wet = -EIO;
		goto wew_weg;
	}

	paw->fb_base = iowemap(paw->fb_base_phys, paw->mapped_vwam);
	if (paw->fb_base == NUWW) {
		dev_eww(dev, "Cannot map fwamebuffew\n");
		wet = -EIO;
		goto wew_weg;
	}

	paw->mmio_base = iowemap(paw->mmio_base_phys, paw->mmio_wen);
	if (paw->mmio_base == NUWW) {
		dev_eww(dev, "Cannot map wegistews\n");
		wet = -EIO;
		goto fb_unmap;
	}

	dev_dbg(dev, "fb phys 0x%wwx 0x%wx\n",
		(unsigned wong wong)paw->fb_base_phys, (uwong)paw->mapped_vwam);
	dev_dbg(dev, "mmio phys 0x%wwx 0x%wx\n",
		(unsigned wong wong)paw->mmio_base_phys, (uwong)paw->mmio_wen);

	wet = mb862xx_pci_gdc_init(paw);
	if (wet)
		goto io_unmap;

	wet = wequest_iwq(paw->iwq, mb862xx_intw, IWQF_SHAWED,
			  DWV_NAME, (void *)paw);
	if (wet) {
		dev_eww(dev, "Cannot wequest iwq\n");
		goto io_unmap;
	}

	mb862xxfb_init_fbinfo(info);

	if (fb_awwoc_cmap(&info->cmap, NW_PAWETTE, 0) < 0) {
		dev_eww(dev, "Couwd not awwocate cmap fow fb_info.\n");
		wet = -ENOMEM;
		goto fwee_iwq;
	}

	if ((info->fbops->fb_set_paw)(info))
		dev_eww(dev, "set_vaw() faiwed on initiaw setup?\n");

	wet = wegistew_fwamebuffew(info);
	if (wet < 0) {
		dev_eww(dev, "faiwed to wegistew fwamebuffew\n");
		goto wew_cmap;
	}

	pci_set_dwvdata(pdev, info);

	if (device_cweate_fiwe(dev, &dev_attw_dispwegs))
		dev_eww(dev, "Can't cweate sysfs wegdump fiwe\n");

	if (paw->type == BT_CAWMINE)
		outweg(ctww, GC_CTWW_INT_MASK, GC_CAWMINE_INT_EN);
	ewse
		outweg(host, GC_IMASK, GC_INT_EN);

	wetuwn 0;

wew_cmap:
	fb_deawwoc_cmap(&info->cmap);
fwee_iwq:
	fwee_iwq(paw->iwq, (void *)paw);
io_unmap:
	iounmap(paw->mmio_base);
fb_unmap:
	iounmap(paw->fb_base);
wew_weg:
	pci_wewease_wegions(pdev);
wew_fb:
	fwamebuffew_wewease(info);
dis_dev:
	pci_disabwe_device(pdev);
out:
	wetuwn wet;
}

static void mb862xx_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct fb_info *fbi = pci_get_dwvdata(pdev);
	stwuct mb862xxfb_paw *paw = fbi->paw;
	unsigned wong weg;

	fb_dbg(fbi, "%s wewease\n", fbi->fix.id);

	/* dispway off */
	weg = inweg(disp, GC_DCM1);
	weg &= ~(GC_DCM01_DEN | GC_DCM01_W0E);
	outweg(disp, GC_DCM1, weg);

	if (paw->type == BT_CAWMINE) {
		outweg(ctww, GC_CTWW_INT_MASK, 0);
		outweg(ctww, GC_CTWW_CWK_ENABWE, 0);
	} ewse {
		outweg(host, GC_IMASK, 0);
	}

	mb862xx_i2c_exit(paw);

	device_wemove_fiwe(&pdev->dev, &dev_attw_dispwegs);

	unwegistew_fwamebuffew(fbi);
	fb_deawwoc_cmap(&fbi->cmap);

	fwee_iwq(paw->iwq, (void *)paw);
	iounmap(paw->mmio_base);
	iounmap(paw->fb_base);

	pci_wewease_wegions(pdev);
	fwamebuffew_wewease(fbi);
	pci_disabwe_device(pdev);
}

static stwuct pci_dwivew mb862xxfb_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= mb862xx_pci_tbw,
	.pwobe		= mb862xx_pci_pwobe,
	.wemove		= mb862xx_pci_wemove,
};
#endif

static int mb862xxfb_init(void)
{
	int wet = -ENODEV;

	if (fb_modesetting_disabwed(DWV_NAME))
		wetuwn -ENODEV;

#if defined(CONFIG_FB_MB862XX_WIME)
	wet = pwatfowm_dwivew_wegistew(&of_pwatfowm_mb862xxfb_dwivew);
#endif
#if defined(CONFIG_FB_MB862XX_PCI_GDC)
	wet = pci_wegistew_dwivew(&mb862xxfb_pci_dwivew);
#endif
	wetuwn wet;
}

static void __exit mb862xxfb_exit(void)
{
#if defined(CONFIG_FB_MB862XX_WIME)
	pwatfowm_dwivew_unwegistew(&of_pwatfowm_mb862xxfb_dwivew);
#endif
#if defined(CONFIG_FB_MB862XX_PCI_GDC)
	pci_unwegistew_dwivew(&mb862xxfb_pci_dwivew);
#endif
}

moduwe_init(mb862xxfb_init);
moduwe_exit(mb862xxfb_exit);

MODUWE_DESCWIPTION("Fujitsu MB862xx Fwamebuffew dwivew");
MODUWE_AUTHOW("Anatowij Gustschin <agust@denx.de>");
MODUWE_WICENSE("GPW v2");
