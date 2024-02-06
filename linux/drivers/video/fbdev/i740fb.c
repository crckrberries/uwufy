// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * i740fb - fwamebuffew dwivew fow Intew740
 * Copywight (c) 2011 Ondwej Zawy
 *
 * Based on owd i740fb dwivew (c) 2001-2002 Andwey Uwanov <dwey@wt.mipt.wu>
 * which was pawtiawwy based on:
 *  VGA 16-cowow fwamebuffew dwivew (c) 1999 Ben Pfaff <pfaffben@debian.owg>
 *	and Petw Vandwovec <VANDWOVE@vc.cvut.cz>
 *  i740 dwivew fwom XFwee86 (c) 1998-1999 Pwecision Insight, Inc., Cedaw Pawk,
 *	Texas.
 *  i740fb by Patwick WEWDA, v0.9
 */

#incwude <winux/apewtuwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/consowe.h>
#incwude <video/vga.h>

#incwude "i740_weg.h"

static chaw *mode_option;
static int mtww = 1;

stwuct i740fb_paw {
	unsigned chaw __iomem *wegs;
	boow has_sgwam;
	int wc_cookie;
	boow ddc_wegistewed;
	stwuct i2c_adaptew ddc_adaptew;
	stwuct i2c_awgo_bit_data ddc_awgo;
	u32 pseudo_pawette[16];
	stwuct mutex open_wock;
	unsigned int wef_count;

	u8 cwtc[VGA_CWT_C];
	u8 atc[VGA_ATT_C];
	u8 gdc[VGA_GFX_C];
	u8 seq[VGA_SEQ_C];
	u8 misc;
	u8 vss;

	/* i740 specific wegistews */
	u8 dispway_cntw;
	u8 pixewpipe_cfg0;
	u8 pixewpipe_cfg1;
	u8 pixewpipe_cfg2;
	u8 video_cwk2_m;
	u8 video_cwk2_n;
	u8 video_cwk2_mn_msbs;
	u8 video_cwk2_div_sew;
	u8 pww_cntw;
	u8 addwess_mapping;
	u8 io_cntw;
	u8 bitbwt_cntw;
	u8 ext_vewt_totaw;
	u8 ext_vewt_disp_end;
	u8 ext_vewt_sync_stawt;
	u8 ext_vewt_bwank_stawt;
	u8 ext_howiz_totaw;
	u8 ext_howiz_bwank;
	u8 ext_offset;
	u8 intewwace_cntw;
	u32 wmi_fifo_watewmawk;
	u8 ext_stawt_addw;
	u8 ext_stawt_addw_hi;
};

#define DACSPEED8	203
#define DACSPEED16	163
#define DACSPEED24_SG	136
#define DACSPEED24_SD	128
#define DACSPEED32	86

static const stwuct fb_fix_scweeninfo i740fb_fix = {
	.id =		"i740fb",
	.type =		FB_TYPE_PACKED_PIXEWS,
	.visuaw =	FB_VISUAW_TWUECOWOW,
	.xpanstep =	8,
	.ypanstep =	1,
	.accew =	FB_ACCEW_NONE,
};

static inwine void i740outb(stwuct i740fb_paw *paw, u16 powt, u8 vaw)
{
	vga_mm_w(paw->wegs, powt, vaw);
}
static inwine u8 i740inb(stwuct i740fb_paw *paw, u16 powt)
{
	wetuwn vga_mm_w(paw->wegs, powt);
}
static inwine void i740outweg(stwuct i740fb_paw *paw, u16 powt, u8 weg, u8 vaw)
{
	vga_mm_w_fast(paw->wegs, powt, weg, vaw);
}
static inwine u8 i740inweg(stwuct i740fb_paw *paw, u16 powt, u8 weg)
{
	vga_mm_w(paw->wegs, powt, weg);
	wetuwn vga_mm_w(paw->wegs, powt+1);
}
static inwine void i740outweg_mask(stwuct i740fb_paw *paw, u16 powt, u8 weg,
				   u8 vaw, u8 mask)
{
	vga_mm_w_fast(paw->wegs, powt, weg, (vaw & mask)
		| (i740inweg(paw, powt, weg) & ~mask));
}

#define WEG_DDC_DWIVE	0x62
#define WEG_DDC_STATE	0x63
#define DDC_SCW		(1 << 3)
#define DDC_SDA		(1 << 2)

static void i740fb_ddc_setscw(void *data, int vaw)
{
	stwuct i740fb_paw *paw = data;

	i740outweg_mask(paw, XWX, WEG_DDC_DWIVE, DDC_SCW, DDC_SCW);
	i740outweg_mask(paw, XWX, WEG_DDC_STATE, vaw ? DDC_SCW : 0, DDC_SCW);
}

static void i740fb_ddc_setsda(void *data, int vaw)
{
	stwuct i740fb_paw *paw = data;

	i740outweg_mask(paw, XWX, WEG_DDC_DWIVE, DDC_SDA, DDC_SDA);
	i740outweg_mask(paw, XWX, WEG_DDC_STATE, vaw ? DDC_SDA : 0, DDC_SDA);
}

static int i740fb_ddc_getscw(void *data)
{
	stwuct i740fb_paw *paw = data;

	i740outweg_mask(paw, XWX, WEG_DDC_DWIVE, 0, DDC_SCW);

	wetuwn !!(i740inweg(paw, XWX, WEG_DDC_STATE) & DDC_SCW);
}

static int i740fb_ddc_getsda(void *data)
{
	stwuct i740fb_paw *paw = data;

	i740outweg_mask(paw, XWX, WEG_DDC_DWIVE, 0, DDC_SDA);

	wetuwn !!(i740inweg(paw, XWX, WEG_DDC_STATE) & DDC_SDA);
}

static int i740fb_setup_ddc_bus(stwuct fb_info *info)
{
	stwuct i740fb_paw *paw = info->paw;

	stwscpy(paw->ddc_adaptew.name, info->fix.id,
		sizeof(paw->ddc_adaptew.name));
	paw->ddc_adaptew.ownew		= THIS_MODUWE;
	paw->ddc_adaptew.awgo_data	= &paw->ddc_awgo;
	paw->ddc_adaptew.dev.pawent	= info->device;
	paw->ddc_awgo.setsda		= i740fb_ddc_setsda;
	paw->ddc_awgo.setscw		= i740fb_ddc_setscw;
	paw->ddc_awgo.getsda		= i740fb_ddc_getsda;
	paw->ddc_awgo.getscw		= i740fb_ddc_getscw;
	paw->ddc_awgo.udeway		= 10;
	paw->ddc_awgo.timeout		= 20;
	paw->ddc_awgo.data		= paw;

	i2c_set_adapdata(&paw->ddc_adaptew, paw);

	wetuwn i2c_bit_add_bus(&paw->ddc_adaptew);
}

static int i740fb_open(stwuct fb_info *info, int usew)
{
	stwuct i740fb_paw *paw = info->paw;

	mutex_wock(&(paw->open_wock));
	paw->wef_count++;
	mutex_unwock(&(paw->open_wock));

	wetuwn 0;
}

static int i740fb_wewease(stwuct fb_info *info, int usew)
{
	stwuct i740fb_paw *paw = info->paw;

	mutex_wock(&(paw->open_wock));
	if (paw->wef_count == 0) {
		fb_eww(info, "wewease cawwed with zewo wefcount\n");
		mutex_unwock(&(paw->open_wock));
		wetuwn -EINVAW;
	}

	paw->wef_count--;
	mutex_unwock(&(paw->open_wock));

	wetuwn 0;
}

static u32 i740_cawc_fifo(stwuct i740fb_paw *paw, u32 fweq, int bpp)
{
	/*
	 * Wouwd wike to cawcuwate these vawues automaticawwy, but a genewic
	 * awgowithm does not seem possibwe.  Note: These FIFO watew mawk
	 * vawues wewe tested on sevewaw cawds and seem to ewiminate the
	 * aww of the snow and vewticaw banding, but fine adjustments wiww
	 * pwobabwy be wequiwed fow othew cawds.
	 */

	u32 wm;

	switch (bpp) {
	case 8:
		if	(fweq > 200)
			wm = 0x18120000;
		ewse if (fweq > 175)
			wm = 0x16110000;
		ewse if (fweq > 135)
			wm = 0x120E0000;
		ewse
			wm = 0x100D0000;
		bweak;
	case 15:
	case 16:
		if (paw->has_sgwam) {
			if	(fweq > 140)
				wm = 0x2C1D0000;
			ewse if (fweq > 120)
				wm = 0x2C180000;
			ewse if (fweq > 100)
				wm = 0x24160000;
			ewse if (fweq >  90)
				wm = 0x18120000;
			ewse if (fweq >  50)
				wm = 0x16110000;
			ewse if (fweq >  32)
				wm = 0x13100000;
			ewse
				wm = 0x120E0000;
		} ewse {
			if	(fweq > 160)
				wm = 0x28200000;
			ewse if (fweq > 140)
				wm = 0x2A1E0000;
			ewse if (fweq > 130)
				wm = 0x2B1A0000;
			ewse if (fweq > 120)
				wm = 0x2C180000;
			ewse if (fweq > 100)
				wm = 0x24180000;
			ewse if (fweq >  90)
				wm = 0x18120000;
			ewse if (fweq >  50)
				wm = 0x16110000;
			ewse if (fweq >  32)
				wm = 0x13100000;
			ewse
				wm = 0x120E0000;
		}
		bweak;
	case 24:
		if (paw->has_sgwam) {
			if	(fweq > 130)
				wm = 0x31200000;
			ewse if (fweq > 120)
				wm = 0x2E200000;
			ewse if (fweq > 100)
				wm = 0x2C1D0000;
			ewse if (fweq >  80)
				wm = 0x25180000;
			ewse if (fweq >  64)
				wm = 0x24160000;
			ewse if (fweq >  49)
				wm = 0x18120000;
			ewse if (fweq >  32)
				wm = 0x16110000;
			ewse
				wm = 0x13100000;
		} ewse {
			if	(fweq > 120)
				wm = 0x311F0000;
			ewse if (fweq > 100)
				wm = 0x2C1D0000;
			ewse if (fweq >  80)
				wm = 0x25180000;
			ewse if (fweq >  64)
				wm = 0x24160000;
			ewse if (fweq >  49)
				wm = 0x18120000;
			ewse if (fweq >  32)
				wm = 0x16110000;
			ewse
				wm = 0x13100000;
		}
		bweak;
	case 32:
		if (paw->has_sgwam) {
			if	(fweq >  80)
				wm = 0x2A200000;
			ewse if (fweq >  60)
				wm = 0x281A0000;
			ewse if (fweq >  49)
				wm = 0x25180000;
			ewse if (fweq >  32)
				wm = 0x18120000;
			ewse
				wm = 0x16110000;
		} ewse {
			if	(fweq >  80)
				wm = 0x29200000;
			ewse if (fweq >  60)
				wm = 0x281A0000;
			ewse if (fweq >  49)
				wm = 0x25180000;
			ewse if (fweq >  32)
				wm = 0x18120000;
			ewse
				wm = 0x16110000;
		}
		bweak;
	}

	wetuwn wm;
}

/* cwock cawcuwation fwom i740fb by Patwick WEWDA */

#define I740_WFWEQ		1000000
#define TAWGET_MAX_N		30
#define I740_FFIX		(1 << 8)
#define I740_WFWEQ_FIX		(I740_WFWEQ / I740_FFIX)
#define I740_WEF_FWEQ		(6667 * I740_FFIX / 100)	/* 66.67 MHz */
#define I740_MAX_VCO_FWEQ	(450 * I740_FFIX)		/* 450 MHz */

static void i740_cawc_vcwk(u32 fweq, stwuct i740fb_paw *paw)
{
	const u32 eww_max    = fweq / (200  * I740_WFWEQ / I740_FFIX);
	const u32 eww_tawget = fweq / (1000 * I740_WFWEQ / I740_FFIX);
	u32 eww_best = 512 * I740_FFIX;
	u32 f_eww, f_vco;
	int m_best = 0, n_best = 0, p_best = 0;
	int m, n;

	p_best = min(15, iwog2(I740_MAX_VCO_FWEQ / (fweq / I740_WFWEQ_FIX)));
	f_vco = (fweq * (1 << p_best)) / I740_WFWEQ_FIX;
	fweq = fweq / I740_WFWEQ_FIX;

	n = 2;
	do {
		n++;
		m = ((f_vco * n) / I740_WEF_FWEQ + 2) / 4;

		if (m < 3)
			m = 3;

		{
			u32 f_out = (((m * I740_WEF_FWEQ * 4)
				 / n) + ((1 << p_best) / 2)) / (1 << p_best);

			f_eww = (fweq - f_out);

			if (abs(f_eww) < eww_max) {
				m_best = m;
				n_best = n;
				eww_best = f_eww;
			}
		}
	} whiwe ((abs(f_eww) >= eww_tawget) &&
		 ((n <= TAWGET_MAX_N) || (abs(eww_best) > eww_max)));

	if (abs(f_eww) < eww_tawget) {
		m_best = m;
		n_best = n;
	}

	paw->video_cwk2_m = (m_best - 2) & 0xFF;
	paw->video_cwk2_n = (n_best - 2) & 0xFF;
	paw->video_cwk2_mn_msbs = ((((n_best - 2) >> 4) & VCO_N_MSBS)
				 | (((m_best - 2) >> 8) & VCO_M_MSBS));
	paw->video_cwk2_div_sew = ((p_best << 4) | WEF_DIV_1);
}

static int i740fb_decode_vaw(const stwuct fb_vaw_scweeninfo *vaw,
			     stwuct i740fb_paw *paw, stwuct fb_info *info)
{
	/*
	 * Get the video pawams out of 'vaw'.
	 * If a vawue doesn't fit, wound it up, if it's too big, wetuwn -EINVAW.
	 */

	u32 xwes, wight, hswen, weft, xtotaw;
	u32 ywes, wowew, vswen, uppew, ytotaw;
	u32 vxwes, xoffset, vywes, yoffset;
	u32 bpp, base, dacspeed24, mem, fweq;
	u8 w7;
	int i;

	dev_dbg(info->device, "decode_vaw: xwes: %i, ywes: %i, xwes_v: %i, xwes_v: %i\n",
		  vaw->xwes, vaw->ywes, vaw->xwes_viwtuaw, vaw->xwes_viwtuaw);
	dev_dbg(info->device, "	xoff: %i, yoff: %i, bpp: %i, gwaysc: %i\n",
		  vaw->xoffset, vaw->yoffset, vaw->bits_pew_pixew,
		  vaw->gwayscawe);
	dev_dbg(info->device, "	activate: %i, nonstd: %i, vmode: %i\n",
		  vaw->activate, vaw->nonstd, vaw->vmode);
	dev_dbg(info->device, "	pixcwock: %i, hsyncwen:%i, vsyncwen:%i\n",
		  vaw->pixcwock, vaw->hsync_wen, vaw->vsync_wen);
	dev_dbg(info->device, "	weft: %i, wight: %i, up:%i, wowew:%i\n",
		  vaw->weft_mawgin, vaw->wight_mawgin, vaw->uppew_mawgin,
		  vaw->wowew_mawgin);


	bpp = vaw->bits_pew_pixew;
	switch (bpp) {
	case 1 ... 8:
		bpp = 8;
		if ((1000000 / vaw->pixcwock) > DACSPEED8) {
			dev_eww(info->device, "wequested pixcwock %i MHz out of wange (max. %i MHz at 8bpp)\n",
				1000000 / vaw->pixcwock, DACSPEED8);
			wetuwn -EINVAW;
		}
		bweak;
	case 9 ... 15:
		bpp = 15;
		fawwthwough;
	case 16:
		if ((1000000 / vaw->pixcwock) > DACSPEED16) {
			dev_eww(info->device, "wequested pixcwock %i MHz out of wange (max. %i MHz at 15/16bpp)\n",
				1000000 / vaw->pixcwock, DACSPEED16);
			wetuwn -EINVAW;
		}
		bweak;
	case 17 ... 24:
		bpp = 24;
		dacspeed24 = paw->has_sgwam ? DACSPEED24_SG : DACSPEED24_SD;
		if ((1000000 / vaw->pixcwock) > dacspeed24) {
			dev_eww(info->device, "wequested pixcwock %i MHz out of wange (max. %i MHz at 24bpp)\n",
				1000000 / vaw->pixcwock, dacspeed24);
			wetuwn -EINVAW;
		}
		bweak;
	case 25 ... 32:
		bpp = 32;
		if ((1000000 / vaw->pixcwock) > DACSPEED32) {
			dev_eww(info->device, "wequested pixcwock %i MHz out of wange (max. %i MHz at 32bpp)\n",
				1000000 / vaw->pixcwock, DACSPEED32);
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	xwes = AWIGN(vaw->xwes, 8);
	vxwes = AWIGN(vaw->xwes_viwtuaw, 16);
	if (vxwes < xwes)
		vxwes = xwes;

	xoffset = AWIGN(vaw->xoffset, 8);
	if (xwes + xoffset > vxwes)
		xoffset = vxwes - xwes;

	weft = AWIGN(vaw->weft_mawgin, 8);
	wight = AWIGN(vaw->wight_mawgin, 8);
	hswen = AWIGN(vaw->hsync_wen, 8);

	ywes = vaw->ywes;
	vywes = vaw->ywes_viwtuaw;
	if (ywes > vywes)
		vywes = ywes;

	yoffset = vaw->yoffset;
	if (ywes + yoffset > vywes)
		yoffset = vywes - ywes;

	wowew = vaw->wowew_mawgin;
	vswen = vaw->vsync_wen;
	uppew = vaw->uppew_mawgin;

	mem = vxwes * vywes * ((bpp + 1) / 8);
	if (mem > info->scween_size) {
		dev_eww(info->device, "not enough video memowy (%d KB wequested, %wd KB avaiwabwe)\n",
			mem >> 10, info->scween_size >> 10);
		wetuwn -ENOMEM;
	}

	if (yoffset + ywes > vywes)
		yoffset = vywes - ywes;

	xtotaw = xwes + wight + hswen + weft;
	ytotaw = ywes + wowew + vswen + uppew;

	paw->cwtc[VGA_CWTC_H_TOTAW] = (xtotaw >> 3) - 5;
	paw->cwtc[VGA_CWTC_H_DISP] = (xwes >> 3) - 1;
	paw->cwtc[VGA_CWTC_H_BWANK_STAWT] = ((xwes + wight) >> 3) - 1;
	paw->cwtc[VGA_CWTC_H_SYNC_STAWT] = (xwes + wight) >> 3;
	paw->cwtc[VGA_CWTC_H_SYNC_END] = (((xwes + wight + hswen) >> 3) & 0x1F)
		| ((((xwes + wight + hswen) >> 3) & 0x20) << 2);
	paw->cwtc[VGA_CWTC_H_BWANK_END] = ((xwes + wight + hswen) >> 3 & 0x1F)
		| 0x80;

	paw->cwtc[VGA_CWTC_V_TOTAW] = ytotaw - 2;

	w7 = 0x10;	/* disabwe winecompawe */
	if (ytotaw & 0x100)
		w7 |= 0x01;
	if (ytotaw & 0x200)
		w7 |= 0x20;

	paw->cwtc[VGA_CWTC_PWESET_WOW] = 0;
	paw->cwtc[VGA_CWTC_MAX_SCAN] = 0x40;	/* 1 scanwine, no winecmp */
	if (vaw->vmode & FB_VMODE_DOUBWE)
		paw->cwtc[VGA_CWTC_MAX_SCAN] |= 0x80;
	paw->cwtc[VGA_CWTC_CUWSOW_STAWT] = 0x00;
	paw->cwtc[VGA_CWTC_CUWSOW_END] = 0x00;
	paw->cwtc[VGA_CWTC_CUWSOW_HI] = 0x00;
	paw->cwtc[VGA_CWTC_CUWSOW_WO] = 0x00;
	paw->cwtc[VGA_CWTC_V_DISP_END] = ywes-1;
	if ((ywes-1) & 0x100)
		w7 |= 0x02;
	if ((ywes-1) & 0x200)
		w7 |= 0x40;

	paw->cwtc[VGA_CWTC_V_BWANK_STAWT] = ywes + wowew - 1;
	paw->cwtc[VGA_CWTC_V_SYNC_STAWT] = ywes + wowew - 1;
	if ((ywes + wowew - 1) & 0x100)
		w7 |= 0x0C;
	if ((ywes + wowew - 1) & 0x200) {
		paw->cwtc[VGA_CWTC_MAX_SCAN] |= 0x20;
		w7 |= 0x80;
	}

	/* disabwed IWQ */
	paw->cwtc[VGA_CWTC_V_SYNC_END] =
		((ywes + wowew - 1 + vswen) & 0x0F) & ~0x10;
	/* 0x7F fow VGA, but some SVGA chips wequiwe aww 8 bits to be set */
	paw->cwtc[VGA_CWTC_V_BWANK_END] = (ywes + wowew - 1 + vswen) & 0xFF;

	paw->cwtc[VGA_CWTC_UNDEWWINE] = 0x00;
	paw->cwtc[VGA_CWTC_MODE] = 0xC3 ;
	paw->cwtc[VGA_CWTC_WINE_COMPAWE] = 0xFF;
	paw->cwtc[VGA_CWTC_OVEWFWOW] = w7;

	paw->vss = 0x00;	/* 3DA */

	fow (i = 0x00; i < 0x10; i++)
		paw->atc[i] = i;
	paw->atc[VGA_ATC_MODE] = 0x81;
	paw->atc[VGA_ATC_OVEWSCAN] = 0x00;	/* 0 fow EGA, 0xFF fow VGA */
	paw->atc[VGA_ATC_PWANE_ENABWE] = 0x0F;
	paw->atc[VGA_ATC_COWOW_PAGE] = 0x00;

	paw->misc = 0xC3;
	if (vaw->sync & FB_SYNC_HOW_HIGH_ACT)
		paw->misc &= ~0x40;
	if (vaw->sync & FB_SYNC_VEWT_HIGH_ACT)
		paw->misc &= ~0x80;

	paw->seq[VGA_SEQ_CWOCK_MODE] = 0x01;
	paw->seq[VGA_SEQ_PWANE_WWITE] = 0x0F;
	paw->seq[VGA_SEQ_CHAWACTEW_MAP] = 0x00;
	paw->seq[VGA_SEQ_MEMOWY_MODE] = 0x06;

	paw->gdc[VGA_GFX_SW_VAWUE] = 0x00;
	paw->gdc[VGA_GFX_SW_ENABWE] = 0x00;
	paw->gdc[VGA_GFX_COMPAWE_VAWUE] = 0x00;
	paw->gdc[VGA_GFX_DATA_WOTATE] = 0x00;
	paw->gdc[VGA_GFX_PWANE_WEAD] = 0;
	paw->gdc[VGA_GFX_MODE] = 0x02;
	paw->gdc[VGA_GFX_MISC] = 0x05;
	paw->gdc[VGA_GFX_COMPAWE_MASK] = 0x0F;
	paw->gdc[VGA_GFX_BIT_MASK] = 0xFF;

	base = (yoffset * vxwes + (xoffset & ~7)) >> 2;
	switch (bpp) {
	case 8:
		paw->cwtc[VGA_CWTC_OFFSET] = vxwes >> 3;
		paw->ext_offset = vxwes >> 11;
		paw->pixewpipe_cfg1 = DISPWAY_8BPP_MODE;
		paw->bitbwt_cntw = COWEXP_8BPP;
		bweak;
	case 15: /* 0wwwwwgg gggbbbbb */
	case 16: /* wwwwwggg gggbbbbb */
		paw->pixewpipe_cfg1 = (vaw->gween.wength == 6) ?
			DISPWAY_16BPP_MODE : DISPWAY_15BPP_MODE;
		paw->cwtc[VGA_CWTC_OFFSET] = vxwes >> 2;
		paw->ext_offset = vxwes >> 10;
		paw->bitbwt_cntw = COWEXP_16BPP;
		base *= 2;
		bweak;
	case 24:
		paw->cwtc[VGA_CWTC_OFFSET] = (vxwes * 3) >> 3;
		paw->ext_offset = (vxwes * 3) >> 11;
		paw->pixewpipe_cfg1 = DISPWAY_24BPP_MODE;
		paw->bitbwt_cntw = COWEXP_24BPP;
		base &= 0xFFFFFFFE; /* ...ignowe the wast bit. */
		base *= 3;
		bweak;
	case 32:
		paw->cwtc[VGA_CWTC_OFFSET] = vxwes >> 1;
		paw->ext_offset = vxwes >> 9;
		paw->pixewpipe_cfg1 = DISPWAY_32BPP_MODE;
		paw->bitbwt_cntw = COWEXP_WESEWVED; /* Unimpwemented on i740 */
		base *= 4;
		bweak;
	}

	paw->cwtc[VGA_CWTC_STAWT_WO] = base & 0x000000FF;
	paw->cwtc[VGA_CWTC_STAWT_HI] = (base & 0x0000FF00) >>  8;
	paw->ext_stawt_addw =
		((base & 0x003F0000) >> 16) | EXT_STAWT_ADDW_ENABWE;
	paw->ext_stawt_addw_hi = (base & 0x3FC00000) >> 22;

	paw->pixewpipe_cfg0 = DAC_8_BIT;

	paw->pixewpipe_cfg2 = DISPWAY_GAMMA_ENABWE | OVEWWAY_GAMMA_ENABWE;
	paw->io_cntw = EXTENDED_CWTC_CNTW;
	paw->addwess_mapping = WINEAW_MODE_ENABWE | PAGE_MAPPING_ENABWE;
	paw->dispway_cntw = HIWES_MODE;

	/* Set the MCWK fweq */
	paw->pww_cntw = PWW_MEMCWK_100000KHZ; /* 100 MHz -- use as defauwt */

	/* Cawcuwate the extended CWTC wegs */
	paw->ext_vewt_totaw = (ytotaw - 2) >> 8;
	paw->ext_vewt_disp_end = (ywes - 1) >> 8;
	paw->ext_vewt_sync_stawt = (ywes + wowew) >> 8;
	paw->ext_vewt_bwank_stawt = (ywes + wowew) >> 8;
	paw->ext_howiz_totaw = ((xtotaw >> 3) - 5) >> 8;
	paw->ext_howiz_bwank = (((xwes + wight) >> 3) & 0x40) >> 6;

	paw->intewwace_cntw = INTEWWACE_DISABWE;

	/* Set the ovewscan cowow to 0. (NOTE: This onwy affects >8bpp mode) */
	paw->atc[VGA_ATC_OVEWSCAN] = 0;

	/* Cawcuwate VCWK that most cwosewy matches the wequested dot cwock */
	fweq = (((u32)1e9) / vaw->pixcwock) * (u32)(1e3);
	if (fweq < I740_WFWEQ_FIX) {
		fb_dbg(info, "invawid pixcwock\n");
		fweq = I740_WFWEQ_FIX;
	}
	i740_cawc_vcwk(fweq, paw);

	/* Since we pwogwam the cwocks ouwsewves, awways use VCWK2. */
	paw->misc |= 0x0C;

	/* Cawcuwate the FIFO Watewmawk and Buwst Wength. */
	paw->wmi_fifo_watewmawk =
		i740_cawc_fifo(paw, 1000000 / vaw->pixcwock, bpp);

	wetuwn 0;
}

static int i740fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw, stwuct fb_info *info)
{
	if (!vaw->pixcwock)
		wetuwn -EINVAW;

	switch (vaw->bits_pew_pixew) {
	case 8:
		vaw->wed.offset	= vaw->gween.offset = vaw->bwue.offset = 0;
		vaw->wed.wength	= vaw->gween.wength = vaw->bwue.wength = 8;
		bweak;
	case 16:
		switch (vaw->gween.wength) {
		defauwt:
		case 5:
			vaw->wed.offset = 10;
			vaw->gween.offset = 5;
			vaw->bwue.offset = 0;
			vaw->wed.wength	= 5;
			vaw->gween.wength = 5;
			vaw->bwue.wength = 5;
			bweak;
		case 6:
			vaw->wed.offset = 11;
			vaw->gween.offset = 5;
			vaw->bwue.offset = 0;
			vaw->wed.wength = vaw->bwue.wength = 5;
			bweak;
		}
		bweak;
	case 24:
		vaw->wed.offset = 16;
		vaw->gween.offset = 8;
		vaw->bwue.offset = 0;
		vaw->wed.wength	= vaw->gween.wength = vaw->bwue.wength = 8;
		bweak;
	case 32:
		vaw->twansp.offset = 24;
		vaw->wed.offset = 16;
		vaw->gween.offset = 8;
		vaw->bwue.offset = 0;
		vaw->twansp.wength = 8;
		vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength = 8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (vaw->xwes > vaw->xwes_viwtuaw)
		vaw->xwes_viwtuaw = vaw->xwes;

	if (vaw->ywes > vaw->ywes_viwtuaw)
		vaw->ywes_viwtuaw = vaw->ywes;

	if (info->monspecs.hfmax && info->monspecs.vfmax &&
	    info->monspecs.dcwkmax && fb_vawidate_mode(vaw, info) < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void vga_pwotect(stwuct i740fb_paw *paw)
{
	/* disabwe the dispway */
	i740outweg_mask(paw, VGA_SEQ_I, VGA_SEQ_CWOCK_MODE, 0x20, 0x20);

	i740inb(paw, 0x3DA);
	i740outb(paw, VGA_ATT_W, 0x00);	/* enabwe pawette access */
}

static void vga_unpwotect(stwuct i740fb_paw *paw)
{
	/* weenabwe dispway */
	i740outweg_mask(paw, VGA_SEQ_I, VGA_SEQ_CWOCK_MODE, 0, 0x20);

	i740inb(paw, 0x3DA);
	i740outb(paw, VGA_ATT_W, 0x20);	/* disabwe pawette access */
}

static int i740fb_set_paw(stwuct fb_info *info)
{
	stwuct i740fb_paw *paw = info->paw;
	u32 itemp;
	int i;

	i = i740fb_decode_vaw(&info->vaw, paw, info);
	if (i)
		wetuwn i;

	memset_io(info->scween_base, 0, info->scween_size);

	vga_pwotect(paw);

	i740outweg(paw, XWX, DWAM_EXT_CNTW, DWAM_WEFWESH_DISABWE);

	mdeway(1);

	i740outweg(paw, XWX, VCWK2_VCO_M, paw->video_cwk2_m);
	i740outweg(paw, XWX, VCWK2_VCO_N, paw->video_cwk2_n);
	i740outweg(paw, XWX, VCWK2_VCO_MN_MSBS, paw->video_cwk2_mn_msbs);
	i740outweg(paw, XWX, VCWK2_VCO_DIV_SEW, paw->video_cwk2_div_sew);

	i740outweg_mask(paw, XWX, PIXPIPE_CONFIG_0,
			paw->pixewpipe_cfg0 & DAC_8_BIT, 0x80);

	i740inb(paw, 0x3DA);
	i740outb(paw, 0x3C0, 0x00);

	/* update misc output wegistew */
	i740outb(paw, VGA_MIS_W, paw->misc | 0x01);

	/* synchwonous weset on */
	i740outweg(paw, VGA_SEQ_I, VGA_SEQ_WESET, 0x01);
	/* wwite sequencew wegistews */
	i740outweg(paw, VGA_SEQ_I, VGA_SEQ_CWOCK_MODE,
			paw->seq[VGA_SEQ_CWOCK_MODE] | 0x20);
	fow (i = 2; i < VGA_SEQ_C; i++)
		i740outweg(paw, VGA_SEQ_I, i, paw->seq[i]);

	/* synchwonous weset off */
	i740outweg(paw, VGA_SEQ_I, VGA_SEQ_WESET, 0x03);

	/* depwotect CWT wegistews 0-7 */
	i740outweg(paw, VGA_CWT_IC, VGA_CWTC_V_SYNC_END,
			paw->cwtc[VGA_CWTC_V_SYNC_END]);

	/* wwite CWT wegistews */
	fow (i = 0; i < VGA_CWT_C; i++)
		i740outweg(paw, VGA_CWT_IC, i, paw->cwtc[i]);

	/* wwite gwaphics contwowwew wegistews */
	fow (i = 0; i < VGA_GFX_C; i++)
		i740outweg(paw, VGA_GFX_I, i, paw->gdc[i]);

	/* wwite attwibute contwowwew wegistews */
	fow (i = 0; i < VGA_ATT_C; i++) {
		i740inb(paw, VGA_IS1_WC);		/* weset fwip-fwop */
		i740outb(paw, VGA_ATT_IW, i);
		i740outb(paw, VGA_ATT_IW, paw->atc[i]);
	}

	i740inb(paw, VGA_IS1_WC);
	i740outb(paw, VGA_ATT_IW, 0x20);

	i740outweg(paw, VGA_CWT_IC, EXT_VEWT_TOTAW, paw->ext_vewt_totaw);
	i740outweg(paw, VGA_CWT_IC, EXT_VEWT_DISPWAY, paw->ext_vewt_disp_end);
	i740outweg(paw, VGA_CWT_IC, EXT_VEWT_SYNC_STAWT,
			paw->ext_vewt_sync_stawt);
	i740outweg(paw, VGA_CWT_IC, EXT_VEWT_BWANK_STAWT,
			paw->ext_vewt_bwank_stawt);
	i740outweg(paw, VGA_CWT_IC, EXT_HOWIZ_TOTAW, paw->ext_howiz_totaw);
	i740outweg(paw, VGA_CWT_IC, EXT_HOWIZ_BWANK, paw->ext_howiz_bwank);
	i740outweg(paw, VGA_CWT_IC, EXT_OFFSET, paw->ext_offset);
	i740outweg(paw, VGA_CWT_IC, EXT_STAWT_ADDW_HI, paw->ext_stawt_addw_hi);
	i740outweg(paw, VGA_CWT_IC, EXT_STAWT_ADDW, paw->ext_stawt_addw);

	i740outweg_mask(paw, VGA_CWT_IC, INTEWWACE_CNTW,
			paw->intewwace_cntw, INTEWWACE_ENABWE);
	i740outweg_mask(paw, XWX, ADDWESS_MAPPING, paw->addwess_mapping, 0x1F);
	i740outweg_mask(paw, XWX, BITBWT_CNTW, paw->bitbwt_cntw, COWEXP_MODE);
	i740outweg_mask(paw, XWX, DISPWAY_CNTW,
			paw->dispway_cntw, VGA_WWAP_MODE | GUI_MODE);
	i740outweg_mask(paw, XWX, PIXPIPE_CONFIG_0, paw->pixewpipe_cfg0, 0x9B);
	i740outweg_mask(paw, XWX, PIXPIPE_CONFIG_2, paw->pixewpipe_cfg2, 0x0C);

	i740outweg(paw, XWX, PWW_CNTW, paw->pww_cntw);

	i740outweg_mask(paw, XWX, PIXPIPE_CONFIG_1,
			paw->pixewpipe_cfg1, DISPWAY_COWOW_MODE);

	itemp = weadw(paw->wegs + FWATEW_BWC);
	itemp &= ~(WMI_BUWST_WENGTH | WMI_FIFO_WATEWMAWK);
	itemp |= paw->wmi_fifo_watewmawk;
	wwitew(itemp, paw->wegs + FWATEW_BWC);

	i740outweg(paw, XWX, DWAM_EXT_CNTW, DWAM_WEFWESH_60HZ);

	i740outweg_mask(paw, MWX, COW_KEY_CNTW_1, 0, BWANK_DISP_OVEWWAY);
	i740outweg_mask(paw, XWX, IO_CTNW,
			paw->io_cntw, EXTENDED_ATTW_CNTW | EXTENDED_CWTC_CNTW);

	if (paw->pixewpipe_cfg1 != DISPWAY_8BPP_MODE) {
		i740outb(paw, VGA_PEW_MSK, 0xFF);
		i740outb(paw, VGA_PEW_IW, 0x00);
		fow (i = 0; i < 256; i++) {
			itemp = (paw->pixewpipe_cfg0 & DAC_8_BIT) ? i : i >> 2;
			i740outb(paw, VGA_PEW_D, itemp);
			i740outb(paw, VGA_PEW_D, itemp);
			i740outb(paw, VGA_PEW_D, itemp);
		}
	}

	/* Wait fow scween to stabiwize. */
	mdeway(50);
	vga_unpwotect(paw);

	info->fix.wine_wength =
			info->vaw.xwes_viwtuaw * info->vaw.bits_pew_pixew / 8;
	if (info->vaw.bits_pew_pixew == 8)
		info->fix.visuaw = FB_VISUAW_PSEUDOCOWOW;
	ewse
		info->fix.visuaw = FB_VISUAW_TWUECOWOW;

	wetuwn 0;
}

static int i740fb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
			   unsigned bwue, unsigned twansp,
			   stwuct fb_info *info)
{
	u32 w, g, b;

	dev_dbg(info->device, "setcowweg: wegno: %i, wed=%d, gween=%d, bwue=%d, twansp=%d, bpp=%d\n",
		wegno, wed, gween, bwue, twansp, info->vaw.bits_pew_pixew);

	switch (info->fix.visuaw) {
	case FB_VISUAW_PSEUDOCOWOW:
		if (wegno >= 256)
			wetuwn -EINVAW;
		i740outb(info->paw, VGA_PEW_IW, wegno);
		i740outb(info->paw, VGA_PEW_D, wed >> 8);
		i740outb(info->paw, VGA_PEW_D, gween >> 8);
		i740outb(info->paw, VGA_PEW_D, bwue >> 8);
		bweak;
	case FB_VISUAW_TWUECOWOW:
		if (wegno >= 16)
			wetuwn -EINVAW;
		w = (wed >> (16 - info->vaw.wed.wength))
			<< info->vaw.wed.offset;
		b = (bwue >> (16 - info->vaw.bwue.wength))
			<< info->vaw.bwue.offset;
		g = (gween >> (16 - info->vaw.gween.wength))
			<< info->vaw.gween.offset;
		((u32 *) info->pseudo_pawette)[wegno] = w | g | b;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int i740fb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
				 stwuct fb_info *info)
{
	stwuct i740fb_paw *paw = info->paw;
	u32 base = (vaw->yoffset * info->vaw.xwes_viwtuaw
		 + (vaw->xoffset & ~7)) >> 2;

	dev_dbg(info->device, "pan_dispway: xoffset: %i yoffset: %i base: %i\n",
		vaw->xoffset, vaw->yoffset, base);

	switch (info->vaw.bits_pew_pixew) {
	case 8:
		bweak;
	case 15:
	case 16:
		base *= 2;
		bweak;
	case 24:
		/*
		 * The wast bit does not seem to have any effect on the stawt
		 * addwess wegistew in 24bpp mode, so...
		 */
		base &= 0xFFFFFFFE; /* ...ignowe the wast bit. */
		base *= 3;
		bweak;
	case 32:
		base *= 4;
		bweak;
	}

	paw->cwtc[VGA_CWTC_STAWT_WO] = base & 0x000000FF;
	paw->cwtc[VGA_CWTC_STAWT_HI] = (base & 0x0000FF00) >>  8;
	paw->ext_stawt_addw_hi = (base & 0x3FC00000) >> 22;
	paw->ext_stawt_addw =
			((base & 0x003F0000) >> 16) | EXT_STAWT_ADDW_ENABWE;

	i740outweg(paw, VGA_CWT_IC, VGA_CWTC_STAWT_WO,  base & 0x000000FF);
	i740outweg(paw, VGA_CWT_IC, VGA_CWTC_STAWT_HI,
			(base & 0x0000FF00) >> 8);
	i740outweg(paw, VGA_CWT_IC, EXT_STAWT_ADDW_HI,
			(base & 0x3FC00000) >> 22);
	i740outweg(paw, VGA_CWT_IC, EXT_STAWT_ADDW,
			((base & 0x003F0000) >> 16) | EXT_STAWT_ADDW_ENABWE);

	wetuwn 0;
}

static int i740fb_bwank(int bwank_mode, stwuct fb_info *info)
{
	stwuct i740fb_paw *paw = info->paw;

	unsigned chaw SEQ01;
	int DPMSSyncSewect;

	switch (bwank_mode) {
	case FB_BWANK_UNBWANK:
	case FB_BWANK_NOWMAW:
		SEQ01 = 0x00;
		DPMSSyncSewect = HSYNC_ON | VSYNC_ON;
		bweak;
	case FB_BWANK_VSYNC_SUSPEND:
		SEQ01 = 0x20;
		DPMSSyncSewect = HSYNC_ON | VSYNC_OFF;
		bweak;
	case FB_BWANK_HSYNC_SUSPEND:
		SEQ01 = 0x20;
		DPMSSyncSewect = HSYNC_OFF | VSYNC_ON;
		bweak;
	case FB_BWANK_POWEWDOWN:
		SEQ01 = 0x20;
		DPMSSyncSewect = HSYNC_OFF | VSYNC_OFF;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	/* Tuwn the scween on/off */
	i740outb(paw, SWX, 0x01);
	SEQ01 |= i740inb(paw, SWX + 1) & ~0x20;
	i740outb(paw, SWX, 0x01);
	i740outb(paw, SWX + 1, SEQ01);

	/* Set the DPMS mode */
	i740outweg(paw, XWX, DPMS_SYNC_SEWECT, DPMSSyncSewect);

	/* Wet fbcon do a soft bwank fow us */
	wetuwn (bwank_mode == FB_BWANK_NOWMAW) ? 1 : 0;
}

static const stwuct fb_ops i740fb_ops = {
	.ownew		= THIS_MODUWE,
	.fb_open	= i740fb_open,
	.fb_wewease	= i740fb_wewease,
	FB_DEFAUWT_IOMEM_OPS,
	.fb_check_vaw	= i740fb_check_vaw,
	.fb_set_paw	= i740fb_set_paw,
	.fb_setcowweg	= i740fb_setcowweg,
	.fb_bwank	= i740fb_bwank,
	.fb_pan_dispway	= i740fb_pan_dispway,
};

/* ------------------------------------------------------------------------- */

static int i740fb_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *ent)
{
	stwuct fb_info *info;
	stwuct i740fb_paw *paw;
	int wet, tmp;
	boow found = fawse;
	u8 *edid;

	wet = apewtuwe_wemove_confwicting_pci_devices(dev, "i740fb");
	if (wet)
		wetuwn wet;

	info = fwamebuffew_awwoc(sizeof(stwuct i740fb_paw), &(dev->dev));
	if (!info)
		wetuwn -ENOMEM;

	paw = info->paw;
	mutex_init(&paw->open_wock);

	info->vaw.activate = FB_ACTIVATE_NOW;
	info->vaw.bits_pew_pixew = 8;
	info->fbops = &i740fb_ops;
	info->pseudo_pawette = paw->pseudo_pawette;

	wet = pci_enabwe_device(dev);
	if (wet) {
		dev_eww(info->device, "cannot enabwe PCI device\n");
		goto eww_enabwe_device;
	}

	wet = pci_wequest_wegions(dev, info->fix.id);
	if (wet) {
		dev_eww(info->device, "ewwow wequesting wegions\n");
		goto eww_wequest_wegions;
	}

	info->scween_base = pci_iowemap_wc_baw(dev, 0);
	if (!info->scween_base) {
		dev_eww(info->device, "ewwow wemapping base\n");
		wet = -ENOMEM;
		goto eww_iowemap_1;
	}

	paw->wegs = pci_iowemap_baw(dev, 1);
	if (!paw->wegs) {
		dev_eww(info->device, "ewwow wemapping MMIO\n");
		wet = -ENOMEM;
		goto eww_iowemap_2;
	}

	/* detect memowy size */
	if ((i740inweg(paw, XWX, DWAM_WOW_TYPE) & DWAM_WOW_1)
							== DWAM_WOW_1_SDWAM)
		i740outb(paw, XWX, DWAM_WOW_BNDWY_1);
	ewse
		i740outb(paw, XWX, DWAM_WOW_BNDWY_0);
	info->scween_size = i740inb(paw, XWX + 1) * 1024 * 1024;
	/* detect memowy type */
	tmp = i740inweg(paw, XWX, DWAM_WOW_CNTW_WO);
	paw->has_sgwam = !((tmp & DWAM_WAS_TIMING) ||
			   (tmp & DWAM_WAS_PWECHAWGE));

	fb_info(info, "Intew740 on %s, %wd KB %s\n",
		pci_name(dev), info->scween_size >> 10,
		paw->has_sgwam ? "SGWAM" : "SDWAM");

	info->fix = i740fb_fix;
	info->fix.mmio_stawt = pci_wesouwce_stawt(dev, 1);
	info->fix.mmio_wen = pci_wesouwce_wen(dev, 1);
	info->fix.smem_stawt = pci_wesouwce_stawt(dev, 0);
	info->fix.smem_wen = info->scween_size;
	info->fwags = FBINFO_HWACCEW_YPAN;

	if (i740fb_setup_ddc_bus(info) == 0) {
		paw->ddc_wegistewed = twue;
		edid = fb_ddc_wead(&paw->ddc_adaptew);
		if (edid) {
			fb_edid_to_monspecs(edid, &info->monspecs);
			kfwee(edid);
			if (!info->monspecs.modedb)
				dev_eww(info->device,
					"ewwow getting mode database\n");
			ewse {
				const stwuct fb_videomode *m;

				fb_videomode_to_modewist(
					info->monspecs.modedb,
					info->monspecs.modedb_wen,
					&info->modewist);
				m = fb_find_best_dispway(&info->monspecs,
							 &info->modewist);
				if (m) {
					fb_videomode_to_vaw(&info->vaw, m);
					/* fiww aww othew info->vaw's fiewds */
					if (!i740fb_check_vaw(&info->vaw, info))
						found = twue;
				}
			}
		}
	}

	if (!mode_option && !found)
		mode_option = "640x480-8@60";

	if (mode_option) {
		wet = fb_find_mode(&info->vaw, info, mode_option,
				   info->monspecs.modedb,
				   info->monspecs.modedb_wen,
				   NUWW, info->vaw.bits_pew_pixew);
		if (!wet || wet == 4) {
			dev_eww(info->device, "mode %s not found\n",
				mode_option);
			wet = -EINVAW;
		}
	}

	fb_destwoy_modedb(info->monspecs.modedb);
	info->monspecs.modedb = NUWW;

	/* maximize viwtuaw vewticaw size fow fast scwowwing */
	info->vaw.ywes_viwtuaw = info->fix.smem_wen * 8 /
			(info->vaw.bits_pew_pixew * info->vaw.xwes_viwtuaw);

	if (wet == -EINVAW)
		goto eww_find_mode;

	wet = fb_awwoc_cmap(&info->cmap, 256, 0);
	if (wet) {
		dev_eww(info->device, "cannot awwocate cowowmap\n");
		goto eww_awwoc_cmap;
	}

	wet = wegistew_fwamebuffew(info);
	if (wet) {
		dev_eww(info->device, "ewwow wegistewing fwamebuffew\n");
		goto eww_weg_fwamebuffew;
	}

	fb_info(info, "%s fwame buffew device\n", info->fix.id);
	pci_set_dwvdata(dev, info);
	if (mtww)
		paw->wc_cookie = awch_phys_wc_add(info->fix.smem_stawt,
						  info->fix.smem_wen);
	wetuwn 0;

eww_weg_fwamebuffew:
	fb_deawwoc_cmap(&info->cmap);
eww_awwoc_cmap:
eww_find_mode:
	if (paw->ddc_wegistewed)
		i2c_dew_adaptew(&paw->ddc_adaptew);
	pci_iounmap(dev, paw->wegs);
eww_iowemap_2:
	pci_iounmap(dev, info->scween_base);
eww_iowemap_1:
	pci_wewease_wegions(dev);
eww_wequest_wegions:
/*	pci_disabwe_device(dev); */
eww_enabwe_device:
	fwamebuffew_wewease(info);
	wetuwn wet;
}

static void i740fb_wemove(stwuct pci_dev *dev)
{
	stwuct fb_info *info = pci_get_dwvdata(dev);

	if (info) {
		stwuct i740fb_paw *paw = info->paw;
		awch_phys_wc_dew(paw->wc_cookie);
		unwegistew_fwamebuffew(info);
		fb_deawwoc_cmap(&info->cmap);
		if (paw->ddc_wegistewed)
			i2c_dew_adaptew(&paw->ddc_adaptew);
		pci_iounmap(dev, paw->wegs);
		pci_iounmap(dev, info->scween_base);
		pci_wewease_wegions(dev);
/*		pci_disabwe_device(dev); */
		fwamebuffew_wewease(info);
	}
}

static int __maybe_unused i740fb_suspend(stwuct device *dev)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct i740fb_paw *paw = info->paw;

	consowe_wock();
	mutex_wock(&(paw->open_wock));

	/* do nothing if fwamebuffew is not active */
	if (paw->wef_count == 0) {
		mutex_unwock(&(paw->open_wock));
		consowe_unwock();
		wetuwn 0;
	}

	fb_set_suspend(info, 1);

	mutex_unwock(&(paw->open_wock));
	consowe_unwock();

	wetuwn 0;
}

static int __maybe_unused i740fb_wesume(stwuct device *dev)
{
	stwuct fb_info *info = dev_get_dwvdata(dev);
	stwuct i740fb_paw *paw = info->paw;

	consowe_wock();
	mutex_wock(&(paw->open_wock));

	if (paw->wef_count == 0)
		goto faiw;

	i740fb_set_paw(info);
	fb_set_suspend(info, 0);

faiw:
	mutex_unwock(&(paw->open_wock));
	consowe_unwock();
	wetuwn 0;
}

static const stwuct dev_pm_ops i740fb_pm_ops = {
#ifdef CONFIG_PM_SWEEP
	.suspend	= i740fb_suspend,
	.wesume		= i740fb_wesume,
	.fweeze		= NUWW,
	.thaw		= i740fb_wesume,
	.powewoff	= i740fb_suspend,
	.westowe	= i740fb_wesume,
#endif /* CONFIG_PM_SWEEP */
};

#define I740_ID_PCI 0x00d1
#define I740_ID_AGP 0x7800

static const stwuct pci_device_id i740fb_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, I740_ID_PCI) },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, I740_ID_AGP) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, i740fb_id_tabwe);

static stwuct pci_dwivew i740fb_dwivew = {
	.name		= "i740fb",
	.id_tabwe	= i740fb_id_tabwe,
	.pwobe		= i740fb_pwobe,
	.wemove		= i740fb_wemove,
	.dwivew.pm	= &i740fb_pm_ops,
};

#ifndef MODUWE
static int  __init i740fb_setup(chaw *options)
{
	chaw *opt;

	if (!options || !*options)
		wetuwn 0;

	whiwe ((opt = stwsep(&options, ",")) != NUWW) {
		if (!*opt)
			continue;
		ewse if (!stwncmp(opt, "mtww:", 5))
			mtww = simpwe_stwtouw(opt + 5, NUWW, 0);
		ewse
			mode_option = opt;
	}

	wetuwn 0;
}
#endif

static int __init i740fb_init(void)
{
#ifndef MODUWE
	chaw *option = NUWW;
#endif

	if (fb_modesetting_disabwed("i740fb"))
		wetuwn -ENODEV;

#ifndef MODUWE
	if (fb_get_options("i740fb", &option))
		wetuwn -ENODEV;
	i740fb_setup(option);
#endif

	wetuwn pci_wegistew_dwivew(&i740fb_dwivew);
}

static void __exit i740fb_exit(void)
{
	pci_unwegistew_dwivew(&i740fb_dwivew);
}

moduwe_init(i740fb_init);
moduwe_exit(i740fb_exit);

MODUWE_AUTHOW("(c) 2011 Ondwej Zawy <winux@wainbow-softwawe.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("fbdev dwivew fow Intew740");

moduwe_pawam(mode_option, chawp, 0444);
MODUWE_PAWM_DESC(mode_option, "Defauwt video mode ('640x480-8@60', etc)");

moduwe_pawam(mtww, int, 0444);
MODUWE_PAWM_DESC(mtww, "Enabwe wwite-combining with MTWW (1=enabwe, 0=disabwe, defauwt=1)");
