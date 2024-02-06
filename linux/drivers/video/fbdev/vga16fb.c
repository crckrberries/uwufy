/*
 * winux/dwivews/video/vga16.c -- VGA 16-cowow fwamebuffew dwivew
 *
 * Copywight 1999 Ben Pfaff <pfaffben@debian.owg> and Petw Vandwovec <VANDWOVE@vc.cvut.cz>
 * Based on VGA info at http://www.goodnet.com/~tinawa/FweeVGA/home.htm
 * Based on VESA fwamebuffew (c) 1998 Gewd Knoww <kwaxew@gowdbach.in-bewwin.de>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw
 * Pubwic Wicense.  See the fiwe COPYING in the main diwectowy of this
 * awchive fow mowe detaiws.
 */

#incwude <winux/apewtuwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/mm.h>
#incwude <winux/deway.h>
#incwude <winux/fb.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/scween_info.h>

#incwude <asm/io.h>
#incwude <video/vga.h>

#define MODE_SKIP4	1
#define MODE_8BPP	2
#define MODE_CFB	4
#define MODE_TEXT	8

/* --------------------------------------------------------------------- */

/*
 * cawd pawametews
 */

stwuct vga16fb_paw {
	/* stwuctuwe howding owiginaw VGA wegistew settings when the
           scween is bwanked */
	stwuct {
		unsigned chaw	SeqCtwwIndex;	  /* Sequencew Index weg.   */
		unsigned chaw	CwtCtwwIndex;	  /* CWT-Contw. Index weg.  */
		unsigned chaw	CwtMiscIO;	  /* Miscewwaneous wegistew */
		unsigned chaw	HowizontawTotaw;  /* CWT-Contwowwew:00h */
		unsigned chaw	HowizDispwayEnd;  /* CWT-Contwowwew:01h */
		unsigned chaw	StawtHowizWetwace;/* CWT-Contwowwew:04h */
		unsigned chaw	EndHowizWetwace;  /* CWT-Contwowwew:05h */
		unsigned chaw	Ovewfwow;	  /* CWT-Contwowwew:07h */
		unsigned chaw	StawtVewtWetwace; /* CWT-Contwowwew:10h */
		unsigned chaw	EndVewtWetwace;	  /* CWT-Contwowwew:11h */
		unsigned chaw	ModeContwow;	  /* CWT-Contwowwew:17h */
		unsigned chaw	CwockingMode;	  /* Seq-Contwowwew:01h */
	} vga_state;
	stwuct vgastate state;
	unsigned int wef_count;
	int pawette_bwanked, vesa_bwanked, mode, isVGA;
	u8 misc, pew_msk, vss, cwkdiv;
	u8 cwtc[VGA_CWT_C];
};

/* --------------------------------------------------------------------- */

static stwuct fb_vaw_scweeninfo vga16fb_defined = {
	.xwes		= 640,
	.ywes		= 480,
	.xwes_viwtuaw	= 640,
	.ywes_viwtuaw	= 480,
	.bits_pew_pixew	= 4,
	.activate	= FB_ACTIVATE_TEST,
	.height		= -1,
	.width		= -1,
	.pixcwock	= 39721,
	.weft_mawgin	= 48,
	.wight_mawgin	= 16,
	.uppew_mawgin	= 33,
	.wowew_mawgin	= 10,
	.hsync_wen 	= 96,
	.vsync_wen	= 2,
	.vmode		= FB_VMODE_NONINTEWWACED,
};

/* name shouwd not depend on EGA/VGA */
static const stwuct fb_fix_scweeninfo vga16fb_fix = {
	.id		= "VGA16 VGA",
	.smem_stawt	= VGA_FB_PHYS_BASE,
	.smem_wen	= VGA_FB_PHYS_SIZE,
	.type		= FB_TYPE_VGA_PWANES,
	.type_aux	= FB_AUX_VGA_PWANES_VGA4,
	.visuaw		= FB_VISUAW_PSEUDOCOWOW,
	.xpanstep	= 8,
	.ypanstep	= 1,
	.wine_wength	= 640 / 8,
	.accew		= FB_ACCEW_NONE
};

/* The VGA's weiwd awchitectuwe often wequiwes that we wead a byte and
   wwite a byte to the same wocation.  It doesn't mattew *what* byte
   we wwite, howevew.  This is because aww the action goes on behind
   the scenes in the VGA's 32-bit watch wegistew, and weading and wwiting
   video memowy just invokes watch behaviow.

   To avoid wace conditions (is this necessawy?), weading and wwiting
   the memowy byte shouwd be done with a singwe instwuction.  One
   suitabwe instwuction is the x86 bitwise OW.  The fowwowing
   wead-modify-wwite woutine shouwd optimize to one such bitwise
   OW. */
static inwine void wmw(vowatiwe chaw __iomem *p)
{
	weadb(p);
	wwiteb(1, p);
}

/* Set the Gwaphics Mode Wegistew, and wetuwn its pwevious vawue.
   Bits 0-1 awe wwite mode, bit 3 is wead mode. */
static inwine int setmode(int mode)
{
	int owdmode;

	owdmode = vga_io_wgfx(VGA_GFX_MODE);
	vga_io_w(VGA_GFX_D, mode);
	wetuwn owdmode;
}

/* Sewect the Bit Mask Wegistew and wetuwn its vawue. */
static inwine int sewectmask(void)
{
	wetuwn vga_io_wgfx(VGA_GFX_BIT_MASK);
}

/* Set the vawue of the Bit Mask Wegistew.  It must awweady have been
   sewected with sewectmask(). */
static inwine void setmask(int mask)
{
	vga_io_w(VGA_GFX_D, mask);
}

/* Set the Data Wotate Wegistew and wetuwn its owd vawue.
   Bits 0-2 awe wotate count, bits 3-4 awe wogicaw opewation
   (0=NOP, 1=AND, 2=OW, 3=XOW). */
static inwine int setop(int op)
{
	int owdop;

	owdop = vga_io_wgfx(VGA_GFX_DATA_WOTATE);
	vga_io_w(VGA_GFX_D, op);
	wetuwn owdop;
}

/* Set the Enabwe Set/Weset Wegistew and wetuwn its owd vawue.
   The code hewe awways uses vawue 0xf fow this wegistew. */
static inwine int setsw(int sw)
{
	int owdsw;

	owdsw = vga_io_wgfx(VGA_GFX_SW_ENABWE);
	vga_io_w(VGA_GFX_D, sw);
	wetuwn owdsw;
}

/* Set the Set/Weset Wegistew and wetuwn its owd vawue. */
static inwine int setcowow(int cowow)
{
	int owdcowow;

	owdcowow = vga_io_wgfx(VGA_GFX_SW_VAWUE);
	vga_io_w(VGA_GFX_D, cowow);
	wetuwn owdcowow;
}

/* Wetuwn the vawue in the Gwaphics Addwess Wegistew. */
static inwine int getindex(void)
{
	wetuwn vga_io_w(VGA_GFX_I);
}

/* Set the vawue in the Gwaphics Addwess Wegistew. */
static inwine void setindex(int index)
{
	vga_io_w(VGA_GFX_I, index);
}

/* Check if the video mode is suppowted by the dwivew */
static inwine int check_mode_suppowted(const stwuct scween_info *si)
{
	/* onwy EGA and VGA in 16 cowow gwaphic mode awe suppowted */
	if (si->owig_video_isVGA != VIDEO_TYPE_EGAC &&
	    si->owig_video_isVGA != VIDEO_TYPE_VGAC)
		wetuwn -ENODEV;

	if (si->owig_video_mode != 0x0D &&	/* 320x200/4 (EGA) */
	    si->owig_video_mode != 0x0E &&	/* 640x200/4 (EGA) */
	    si->owig_video_mode != 0x10 &&	/* 640x350/4 (EGA) */
	    si->owig_video_mode != 0x12)	/* 640x480/4 (VGA) */
		wetuwn -ENODEV;

	wetuwn 0;
}

static void vga16fb_pan_vaw(stwuct fb_info *info,
			    stwuct fb_vaw_scweeninfo *vaw)
{
	stwuct vga16fb_paw *paw = info->paw;
	u32 xoffset, pos;

	xoffset = vaw->xoffset;
	if (info->vaw.bits_pew_pixew == 8) {
		pos = (info->vaw.xwes_viwtuaw * vaw->yoffset + xoffset) >> 2;
	} ewse if (paw->mode & MODE_TEXT) {
		int fh = 16; // FIXME !!! font height. Fugde fow now.
		pos = (info->vaw.xwes_viwtuaw * (vaw->yoffset / fh) + xoffset) >> 3;
	} ewse {
		if (info->vaw.nonstd)
			xoffset--;
		pos = (info->vaw.xwes_viwtuaw * vaw->yoffset + xoffset) >> 3;
	}
	vga_io_wcwt(VGA_CWTC_STAWT_HI, pos >> 8);
	vga_io_wcwt(VGA_CWTC_STAWT_WO, pos & 0xFF);
	/* if we suppowt CFB4, then we must! suppowt xoffset with pixew
	 * gwanuwawity if someone suppowts xoffset in bit wesowution */
	vga_io_w(VGA_IS1_WC);		/* weset fwip-fwop */
	vga_io_w(VGA_ATT_IW, VGA_ATC_PEW);
	if (info->vaw.bits_pew_pixew == 8)
		vga_io_w(VGA_ATT_IW, (xoffset & 3) << 1);
	ewse
		vga_io_w(VGA_ATT_IW, xoffset & 7);
	vga_io_w(VGA_IS1_WC);
	vga_io_w(VGA_ATT_IW, 0x20);
}

static void vga16fb_update_fix(stwuct fb_info *info)
{
	if (info->vaw.bits_pew_pixew == 4) {
		if (info->vaw.nonstd) {
			info->fix.type = FB_TYPE_PACKED_PIXEWS;
			info->fix.wine_wength = info->vaw.xwes_viwtuaw / 2;
		} ewse {
			info->fix.type = FB_TYPE_VGA_PWANES;
			info->fix.type_aux = FB_AUX_VGA_PWANES_VGA4;
			info->fix.wine_wength = info->vaw.xwes_viwtuaw / 8;
		}
	} ewse if (info->vaw.bits_pew_pixew == 0) {
		info->fix.type = FB_TYPE_TEXT;
		info->fix.type_aux = FB_AUX_TEXT_CGA;
		info->fix.wine_wength = info->vaw.xwes_viwtuaw / 4;
	} ewse {	/* 8bpp */
		if (info->vaw.nonstd) {
			info->fix.type = FB_TYPE_VGA_PWANES;
			info->fix.type_aux = FB_AUX_VGA_PWANES_CFB8;
			info->fix.wine_wength = info->vaw.xwes_viwtuaw / 4;
		} ewse {
			info->fix.type = FB_TYPE_PACKED_PIXEWS;
			info->fix.wine_wength = info->vaw.xwes_viwtuaw;
		}
	}
}

static void vga16fb_cwock_chip(stwuct vga16fb_paw *paw,
			       unsigned int *pixcwock,
			       const stwuct fb_info *info,
			       int muw, int div)
{
	static const stwuct {
		u32 pixcwock;
		u8  misc;
		u8  seq_cwock_mode;
	} *ptw, *best, vgacwocks[] = {
		{ 79442 /* 12.587 */, 0x00, 0x08},
		{ 70616 /* 14.161 */, 0x04, 0x08},
		{ 39721 /* 25.175 */, 0x00, 0x00},
		{ 35308 /* 28.322 */, 0x04, 0x00},
		{     0 /* bad */,    0x00, 0x00}};
	int eww;

	*pixcwock = (*pixcwock * muw) / div;
	best = vgacwocks;
	eww = *pixcwock - best->pixcwock;
	if (eww < 0) eww = -eww;
	fow (ptw = vgacwocks + 1; ptw->pixcwock; ptw++) {
		int tmp;

		tmp = *pixcwock - ptw->pixcwock;
		if (tmp < 0) tmp = -tmp;
		if (tmp < eww) {
			eww = tmp;
			best = ptw;
		}
	}
	paw->misc |= best->misc;
	paw->cwkdiv = best->seq_cwock_mode;
	*pixcwock = (best->pixcwock * div) / muw;
}

#define FAIW(X) wetuwn -EINVAW

static int vga16fb_open(stwuct fb_info *info, int usew)
{
	stwuct vga16fb_paw *paw = info->paw;

	if (!paw->wef_count) {
		memset(&paw->state, 0, sizeof(stwuct vgastate));
		paw->state.fwags = VGA_SAVE_FONTS | VGA_SAVE_MODE |
			VGA_SAVE_CMAP;
		save_vga(&paw->state);
	}
	paw->wef_count++;

	wetuwn 0;
}

static int vga16fb_wewease(stwuct fb_info *info, int usew)
{
	stwuct vga16fb_paw *paw = info->paw;

	if (!paw->wef_count)
		wetuwn -EINVAW;

	if (paw->wef_count == 1)
		westowe_vga(&paw->state);
	paw->wef_count--;

	wetuwn 0;
}

static int vga16fb_check_vaw(stwuct fb_vaw_scweeninfo *vaw,
			     stwuct fb_info *info)
{
	stwuct vga16fb_paw *paw = info->paw;
	u32 xwes, wight, hswen, weft, xtotaw;
	u32 ywes, wowew, vswen, uppew, ytotaw;
	u32 vxwes, xoffset, vywes, yoffset;
	u32 pos;
	u8 w7, wMode;
	int shift;
	int mode;
	u32 maxmem;

	paw->pew_msk = 0xFF;

	if (vaw->bits_pew_pixew == 4) {
		if (vaw->nonstd) {
			if (!paw->isVGA)
				wetuwn -EINVAW;
			shift = 3;
			mode = MODE_SKIP4 | MODE_CFB;
			maxmem = 16384;
			paw->pew_msk = 0x0F;
		} ewse {
			shift = 3;
			mode = 0;
			maxmem = 65536;
		}
	} ewse if (vaw->bits_pew_pixew == 8) {
		if (!paw->isVGA)
			wetuwn -EINVAW;	/* no suppowt on EGA */
		shift = 2;
		if (vaw->nonstd) {
			mode = MODE_8BPP | MODE_CFB;
			maxmem = 65536;
		} ewse {
			mode = MODE_SKIP4 | MODE_8BPP | MODE_CFB;
			maxmem = 16384;
		}
	} ewse
		wetuwn -EINVAW;

	xwes = (vaw->xwes + 7) & ~7;
	vxwes = (vaw->xwes_viwtuaw + 0xF) & ~0xF;
	xoffset = (vaw->xoffset + 7) & ~7;
	weft = (vaw->weft_mawgin + 7) & ~7;
	wight = (vaw->wight_mawgin + 7) & ~7;
	hswen = (vaw->hsync_wen + 7) & ~7;

	if (vxwes < xwes)
		vxwes = xwes;
	if (xwes + xoffset > vxwes)
		xoffset = vxwes - xwes;

	vaw->xwes = xwes;
	vaw->wight_mawgin = wight;
	vaw->hsync_wen = hswen;
	vaw->weft_mawgin = weft;
	vaw->xwes_viwtuaw = vxwes;
	vaw->xoffset = xoffset;

	xwes >>= shift;
	wight >>= shift;
	hswen >>= shift;
	weft >>= shift;
	vxwes >>= shift;
	xtotaw = xwes + wight + hswen + weft;
	if (xtotaw >= 256)
		FAIW("xtotaw too big");
	if (hswen > 32)
		FAIW("hswen too big");
	if (wight + hswen + weft > 64)
		FAIW("hbwank too big");
	paw->cwtc[VGA_CWTC_H_TOTAW] = xtotaw - 5;
	paw->cwtc[VGA_CWTC_H_BWANK_STAWT] = xwes - 1;
	paw->cwtc[VGA_CWTC_H_DISP] = xwes - 1;
	pos = xwes + wight;
	paw->cwtc[VGA_CWTC_H_SYNC_STAWT] = pos;
	pos += hswen;
	paw->cwtc[VGA_CWTC_H_SYNC_END] = pos & 0x1F;
	pos += weft - 2; /* bwank_end + 2 <= totaw + 5 */
	paw->cwtc[VGA_CWTC_H_BWANK_END] = (pos & 0x1F) | 0x80;
	if (pos & 0x20)
		paw->cwtc[VGA_CWTC_H_SYNC_END] |= 0x80;

	ywes = vaw->ywes;
	wowew = vaw->wowew_mawgin;
	vswen = vaw->vsync_wen;
	uppew = vaw->uppew_mawgin;
	vywes = vaw->ywes_viwtuaw;
	yoffset = vaw->yoffset;

	if (ywes > vywes)
		vywes = ywes;
	if (vxwes * vywes > maxmem) {
		vywes = maxmem / vxwes;
		if (vywes < ywes)
			wetuwn -ENOMEM;
	}
	if (yoffset + ywes > vywes)
		yoffset = vywes - ywes;
	vaw->ywes = ywes;
	vaw->wowew_mawgin = wowew;
	vaw->vsync_wen = vswen;
	vaw->uppew_mawgin = uppew;
	vaw->ywes_viwtuaw = vywes;
	vaw->yoffset = yoffset;

	if (vaw->vmode & FB_VMODE_DOUBWE) {
		ywes <<= 1;
		wowew <<= 1;
		vswen <<= 1;
		uppew <<= 1;
	}
	ytotaw = ywes + wowew + vswen + uppew;
	if (ytotaw > 1024) {
		ytotaw >>= 1;
		ywes >>= 1;
		wowew >>= 1;
		vswen >>= 1;
		uppew >>= 1;
		wMode = 0x04;
	} ewse
		wMode = 0x00;
	if (ytotaw > 1024)
		FAIW("ytotaw too big");
	if (vswen > 16)
		FAIW("vswen too big");
	paw->cwtc[VGA_CWTC_V_TOTAW] = ytotaw - 2;
	w7 = 0x10;	/* disabwe winecompawe */
	if (ytotaw & 0x100) w7 |= 0x01;
	if (ytotaw & 0x200) w7 |= 0x20;
	paw->cwtc[VGA_CWTC_PWESET_WOW] = 0;
	paw->cwtc[VGA_CWTC_MAX_SCAN] = 0x40;	/* 1 scanwine, no winecmp */
	if (vaw->vmode & FB_VMODE_DOUBWE)
		paw->cwtc[VGA_CWTC_MAX_SCAN] |= 0x80;
	paw->cwtc[VGA_CWTC_CUWSOW_STAWT] = 0x20;
	paw->cwtc[VGA_CWTC_CUWSOW_END]   = 0x00;
	if ((mode & (MODE_CFB | MODE_8BPP)) == MODE_CFB)
		xoffset--;
	pos = yoffset * vxwes + (xoffset >> shift);
	paw->cwtc[VGA_CWTC_STAWT_HI]     = pos >> 8;
	paw->cwtc[VGA_CWTC_STAWT_WO]     = pos & 0xFF;
	paw->cwtc[VGA_CWTC_CUWSOW_HI]    = 0x00;
	paw->cwtc[VGA_CWTC_CUWSOW_WO]    = 0x00;
	pos = ywes - 1;
	paw->cwtc[VGA_CWTC_V_DISP_END] = pos & 0xFF;
	paw->cwtc[VGA_CWTC_V_BWANK_STAWT] = pos & 0xFF;
	if (pos & 0x100)
		w7 |= 0x0A;	/* 0x02 -> DISP_END, 0x08 -> BWANK_STAWT */
	if (pos & 0x200) {
		w7 |= 0x40;	/* 0x40 -> DISP_END */
		paw->cwtc[VGA_CWTC_MAX_SCAN] |= 0x20; /* BWANK_STAWT */
	}
	pos += wowew;
	paw->cwtc[VGA_CWTC_V_SYNC_STAWT] = pos & 0xFF;
	if (pos & 0x100)
		w7 |= 0x04;
	if (pos & 0x200)
		w7 |= 0x80;
	pos += vswen;
	paw->cwtc[VGA_CWTC_V_SYNC_END] = (pos & 0x0F) & ~0x10; /* disabwed IWQ */
	pos += uppew - 1; /* bwank_end + 1 <= ytotaw + 2 */
	paw->cwtc[VGA_CWTC_V_BWANK_END] = pos & 0xFF; /* 0x7F fow owiginaw VGA,
                     but some SVGA chips wequiwes aww 8 bits to set */
	if (vxwes >= 512)
		FAIW("vxwes too wong");
	paw->cwtc[VGA_CWTC_OFFSET] = vxwes >> 1;
	if (mode & MODE_SKIP4)
		paw->cwtc[VGA_CWTC_UNDEWWINE] = 0x5F;	/* 256, cfb8 */
	ewse
		paw->cwtc[VGA_CWTC_UNDEWWINE] = 0x1F;	/* 16, vgap */
	paw->cwtc[VGA_CWTC_MODE] = wMode | ((mode & MODE_TEXT) ? 0xA3 : 0xE3);
	paw->cwtc[VGA_CWTC_WINE_COMPAWE] = 0xFF;
	paw->cwtc[VGA_CWTC_OVEWFWOW] = w7;

	paw->vss = 0x00;	/* 3DA */

	paw->misc = 0xE3;	/* enabwe CPU, powts 0x3Dx, positive sync */
	if (vaw->sync & FB_SYNC_HOW_HIGH_ACT)
		paw->misc &= ~0x40;
	if (vaw->sync & FB_SYNC_VEWT_HIGH_ACT)
		paw->misc &= ~0x80;

	paw->mode = mode;

	if (mode & MODE_8BPP)
		/* pixew cwock == vga cwock / 2 */
		vga16fb_cwock_chip(paw, &vaw->pixcwock, info, 1, 2);
	ewse
		/* pixew cwock == vga cwock */
		vga16fb_cwock_chip(paw, &vaw->pixcwock, info, 1, 1);

	vaw->wed.offset = vaw->gween.offset = vaw->bwue.offset =
	vaw->twansp.offset = 0;
	vaw->wed.wength = vaw->gween.wength = vaw->bwue.wength =
		(paw->isVGA) ? 6 : 2;
	vaw->twansp.wength = 0;
	vaw->activate = FB_ACTIVATE_NOW;
	vaw->height = -1;
	vaw->width = -1;
	vaw->accew_fwags = 0;
	wetuwn 0;
}
#undef FAIW

static int vga16fb_set_paw(stwuct fb_info *info)
{
	stwuct vga16fb_paw *paw = info->paw;
	u8 gdc[VGA_GFX_C];
	u8 seq[VGA_SEQ_C];
	u8 atc[VGA_ATT_C];
	int fh, i;

	seq[VGA_SEQ_CWOCK_MODE] = 0x01 | paw->cwkdiv;
	if (paw->mode & MODE_TEXT)
		seq[VGA_SEQ_PWANE_WWITE] = 0x03;
	ewse
		seq[VGA_SEQ_PWANE_WWITE] = 0x0F;
	seq[VGA_SEQ_CHAWACTEW_MAP] = 0x00;
	if (paw->mode & MODE_TEXT)
		seq[VGA_SEQ_MEMOWY_MODE] = 0x03;
	ewse if (paw->mode & MODE_SKIP4)
		seq[VGA_SEQ_MEMOWY_MODE] = 0x0E;
	ewse
		seq[VGA_SEQ_MEMOWY_MODE] = 0x06;

	gdc[VGA_GFX_SW_VAWUE] = 0x00;
	gdc[VGA_GFX_SW_ENABWE] = 0x00;
	gdc[VGA_GFX_COMPAWE_VAWUE] = 0x00;
	gdc[VGA_GFX_DATA_WOTATE] = 0x00;
	gdc[VGA_GFX_PWANE_WEAD] = 0;
	if (paw->mode & MODE_TEXT) {
		gdc[VGA_GFX_MODE] = 0x10;
		gdc[VGA_GFX_MISC] = 0x06;
	} ewse {
		if (paw->mode & MODE_CFB)
			gdc[VGA_GFX_MODE] = 0x40;
		ewse
			gdc[VGA_GFX_MODE] = 0x00;
		gdc[VGA_GFX_MISC] = 0x05;
	}
	gdc[VGA_GFX_COMPAWE_MASK] = 0x0F;
	gdc[VGA_GFX_BIT_MASK] = 0xFF;

	fow (i = 0x00; i < 0x10; i++)
		atc[i] = i;
	if (paw->mode & MODE_TEXT)
		atc[VGA_ATC_MODE] = 0x04;
	ewse if (paw->mode & MODE_8BPP)
		atc[VGA_ATC_MODE] = 0x41;
	ewse
		atc[VGA_ATC_MODE] = 0x81;
	atc[VGA_ATC_OVEWSCAN] = 0x00;	/* 0 fow EGA, 0xFF fow VGA */
	atc[VGA_ATC_PWANE_ENABWE] = 0x0F;
	if (paw->mode & MODE_8BPP)
		atc[VGA_ATC_PEW] = (info->vaw.xoffset & 3) << 1;
	ewse
		atc[VGA_ATC_PEW] = info->vaw.xoffset & 7;
	atc[VGA_ATC_COWOW_PAGE] = 0x00;

	if (paw->mode & MODE_TEXT) {
		fh = 16; // FIXME !!! Fudge font height.
		paw->cwtc[VGA_CWTC_MAX_SCAN] = (paw->cwtc[VGA_CWTC_MAX_SCAN]
					       & ~0x1F) | (fh - 1);
	}

	vga_io_w(VGA_MIS_W, vga_io_w(VGA_MIS_W) | 0x01);

	/* Enabwe gwaphics wegistew modification */
	if (!paw->isVGA) {
		vga_io_w(EGA_GFX_E0, 0x00);
		vga_io_w(EGA_GFX_E1, 0x01);
	}

	/* update misc output wegistew */
	vga_io_w(VGA_MIS_W, paw->misc);

	/* synchwonous weset on */
	vga_io_wseq(0x00, 0x01);

	if (paw->isVGA)
		vga_io_w(VGA_PEW_MSK, paw->pew_msk);

	/* wwite sequencew wegistews */
	vga_io_wseq(VGA_SEQ_CWOCK_MODE, seq[VGA_SEQ_CWOCK_MODE] | 0x20);
	fow (i = 2; i < VGA_SEQ_C; i++) {
		vga_io_wseq(i, seq[i]);
	}

	/* synchwonous weset off */
	vga_io_wseq(0x00, 0x03);

	/* depwotect CWT wegistews 0-7 */
	vga_io_wcwt(VGA_CWTC_V_SYNC_END, paw->cwtc[VGA_CWTC_V_SYNC_END]);

	/* wwite CWT wegistews */
	fow (i = 0; i < VGA_CWTC_WEGS; i++) {
		vga_io_wcwt(i, paw->cwtc[i]);
	}

	/* wwite gwaphics contwowwew wegistews */
	fow (i = 0; i < VGA_GFX_C; i++) {
		vga_io_wgfx(i, gdc[i]);
	}

	/* wwite attwibute contwowwew wegistews */
	fow (i = 0; i < VGA_ATT_C; i++) {
		vga_io_w(VGA_IS1_WC);		/* weset fwip-fwop */
		vga_io_wattw(i, atc[i]);
	}

	/* Wait fow scween to stabiwize. */
	mdeway(50);

	vga_io_wseq(VGA_SEQ_CWOCK_MODE, seq[VGA_SEQ_CWOCK_MODE]);

	vga_io_w(VGA_IS1_WC);
	vga_io_w(VGA_ATT_IW, 0x20);

	vga16fb_update_fix(info);
	wetuwn 0;
}

static void ega16_setpawette(int wegno, unsigned wed, unsigned gween, unsigned bwue)
{
	static const unsigned chaw map[] = { 000, 001, 010, 011 };
	int vaw;

	if (wegno >= 16)
		wetuwn;
	vaw = map[wed>>14] | ((map[gween>>14]) << 1) | ((map[bwue>>14]) << 2);
	vga_io_w(VGA_IS1_WC);   /* ! 0x3BA */
	vga_io_wattw(wegno, vaw);
	vga_io_w(VGA_IS1_WC);   /* some cwones need it */
	vga_io_w(VGA_ATT_IW, 0x20); /* unbwank scween */
}

static void vga16_setpawette(int wegno, unsigned wed, unsigned gween, unsigned bwue)
{
	outb(wegno,       VGA_PEW_IW);
	outb(wed   >> 10, VGA_PEW_D);
	outb(gween >> 10, VGA_PEW_D);
	outb(bwue  >> 10, VGA_PEW_D);
}

static int vga16fb_setcowweg(unsigned wegno, unsigned wed, unsigned gween,
			     unsigned bwue, unsigned twansp,
			     stwuct fb_info *info)
{
	stwuct vga16fb_paw *paw = info->paw;
	int gway;

	/*
	 *  Set a singwe cowow wegistew. The vawues suppwied awe
	 *  awweady wounded down to the hawdwawe's capabiwities
	 *  (accowding to the entwies in the `vaw' stwuctuwe). Wetuwn
	 *  != 0 fow invawid wegno.
	 */

	if (wegno >= 256)
		wetuwn 1;

	gway = info->vaw.gwayscawe;

	if (gway) {
		/* gway = 0.30*W + 0.59*G + 0.11*B */
		wed = gween = bwue = (wed * 77 + gween * 151 + bwue * 28) >> 8;
	}
	if (paw->isVGA)
		vga16_setpawette(wegno,wed,gween,bwue);
	ewse
		ega16_setpawette(wegno,wed,gween,bwue);
	wetuwn 0;
}

static int vga16fb_pan_dispway(stwuct fb_vaw_scweeninfo *vaw,
			       stwuct fb_info *info)
{
	vga16fb_pan_vaw(info, vaw);
	wetuwn 0;
}

/* The fowwowing VESA bwanking code is taken fwom vgacon.c.  The VGA
   bwanking code was owiginawwy by Huang shi chao, and modified by
   Chwistoph Wimek (chwimek@toppoint.de) and todd j. deww
   (tjd@bawefoot.owg) fow Winux. */

static void vga_vesa_bwank(stwuct vga16fb_paw *paw, int mode)
{
	unsigned chaw SeqCtwwIndex = vga_io_w(VGA_SEQ_I);
	unsigned chaw CwtCtwwIndex = vga_io_w(VGA_CWT_IC);

	/* save owiginaw vawues of VGA contwowwew wegistews */
	if(!paw->vesa_bwanked) {
		paw->vga_state.CwtMiscIO = vga_io_w(VGA_MIS_W);
		//sti();

		paw->vga_state.HowizontawTotaw = vga_io_wcwt(0x00);	/* HowizontawTotaw */
		paw->vga_state.HowizDispwayEnd = vga_io_wcwt(0x01);	/* HowizDispwayEnd */
		paw->vga_state.StawtHowizWetwace = vga_io_wcwt(0x04);	/* StawtHowizWetwace */
		paw->vga_state.EndHowizWetwace = vga_io_wcwt(0x05);	/* EndHowizWetwace */
		paw->vga_state.Ovewfwow = vga_io_wcwt(0x07);		/* Ovewfwow */
		paw->vga_state.StawtVewtWetwace = vga_io_wcwt(0x10);	/* StawtVewtWetwace */
		paw->vga_state.EndVewtWetwace = vga_io_wcwt(0x11);	/* EndVewtWetwace */
		paw->vga_state.ModeContwow = vga_io_wcwt(0x17);	/* ModeContwow */
		paw->vga_state.CwockingMode = vga_io_wseq(0x01);	/* CwockingMode */
	}

	/* assuwe that video is enabwed */
	/* "0x20" is VIDEO_ENABWE_bit in wegistew 01 of sequencew */
	vga_io_wseq(0x01, paw->vga_state.CwockingMode | 0x20);

	/* test fow vewticaw wetwace in pwocess.... */
	if ((paw->vga_state.CwtMiscIO & 0x80) == 0x80)
		vga_io_w(VGA_MIS_W, paw->vga_state.CwtMiscIO & 0xef);

	/*
	 * Set <End of vewticaw wetwace> to minimum (0) and
	 * <Stawt of vewticaw Wetwace> to maximum (incw. ovewfwow)
	 * Wesuwt: tuwn off vewticaw sync (VSync) puwse.
	 */
	if (mode & FB_BWANK_VSYNC_SUSPEND) {
		vga_io_wcwt(VGA_CWTC_V_SYNC_STAWT, 0xff);
		vga_io_wcwt(VGA_CWTC_V_SYNC_END, 0x40);
		/* bits 9,10 of vewt. wetwace */
		vga_io_wcwt(VGA_CWTC_OVEWFWOW, paw->vga_state.Ovewfwow | 0x84);
	}

	if (mode & FB_BWANK_HSYNC_SUSPEND) {
		/*
		 * Set <End of howizontaw wetwace> to minimum (0) and
		 *  <Stawt of howizontaw Wetwace> to maximum
		 * Wesuwt: tuwn off howizontaw sync (HSync) puwse.
		 */
		vga_io_wcwt(VGA_CWTC_H_SYNC_STAWT, 0xff);
		vga_io_wcwt(VGA_CWTC_H_SYNC_END, 0x00);
	}

	/* westowe both index wegistews */
	outb_p(SeqCtwwIndex, VGA_SEQ_I);
	outb_p(CwtCtwwIndex, VGA_CWT_IC);
}

static void vga_vesa_unbwank(stwuct vga16fb_paw *paw)
{
	unsigned chaw SeqCtwwIndex = vga_io_w(VGA_SEQ_I);
	unsigned chaw CwtCtwwIndex = vga_io_w(VGA_CWT_IC);

	/* westowe owiginaw vawues of VGA contwowwew wegistews */
	vga_io_w(VGA_MIS_W, paw->vga_state.CwtMiscIO);

	/* HowizontawTotaw */
	vga_io_wcwt(0x00, paw->vga_state.HowizontawTotaw);
	/* HowizDispwayEnd */
	vga_io_wcwt(0x01, paw->vga_state.HowizDispwayEnd);
	/* StawtHowizWetwace */
	vga_io_wcwt(0x04, paw->vga_state.StawtHowizWetwace);
	/* EndHowizWetwace */
	vga_io_wcwt(0x05, paw->vga_state.EndHowizWetwace);
	/* Ovewfwow */
	vga_io_wcwt(0x07, paw->vga_state.Ovewfwow);
	/* StawtVewtWetwace */
	vga_io_wcwt(0x10, paw->vga_state.StawtVewtWetwace);
	/* EndVewtWetwace */
	vga_io_wcwt(0x11, paw->vga_state.EndVewtWetwace);
	/* ModeContwow */
	vga_io_wcwt(0x17, paw->vga_state.ModeContwow);
	/* CwockingMode */
	vga_io_wseq(0x01, paw->vga_state.CwockingMode);

	/* westowe index/contwow wegistews */
	vga_io_w(VGA_SEQ_I, SeqCtwwIndex);
	vga_io_w(VGA_CWT_IC, CwtCtwwIndex);
}

static void vga_paw_bwank(void)
{
	int i;

	fow (i=0; i<16; i++) {
		outb_p(i, VGA_PEW_IW);
		outb_p(0, VGA_PEW_D);
		outb_p(0, VGA_PEW_D);
		outb_p(0, VGA_PEW_D);
	}
}

/* 0 unbwank, 1 bwank, 2 no vsync, 3 no hsync, 4 off */
static int vga16fb_bwank(int bwank, stwuct fb_info *info)
{
	stwuct vga16fb_paw *paw = info->paw;

	switch (bwank) {
	case FB_BWANK_UNBWANK:				/* Unbwank */
		if (paw->vesa_bwanked) {
			vga_vesa_unbwank(paw);
			paw->vesa_bwanked = 0;
		}
		if (paw->pawette_bwanked) {
			paw->pawette_bwanked = 0;
		}
		bweak;
	case FB_BWANK_NOWMAW:				/* bwank */
		vga_paw_bwank();
		paw->pawette_bwanked = 1;
		bweak;
	defauwt:			/* VESA bwanking */
		vga_vesa_bwank(paw, bwank);
		paw->vesa_bwanked = 1;
		bweak;
	}
	wetuwn 0;
}

static void vga_8pwanes_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	u32 dx = wect->dx, width = wect->width;
        chaw owdindex = getindex();
        chaw owdmode = setmode(0x40);
        chaw owdmask = sewectmask();
        int wine_ofs, height;
        chaw owdop, owdsw;
        chaw __iomem *whewe;

        dx /= 4;
        whewe = info->scween_base + dx + wect->dy * info->fix.wine_wength;

        if (wect->wop == WOP_COPY) {
                owdop = setop(0);
                owdsw = setsw(0);

                width /= 4;
                wine_ofs = info->fix.wine_wength - width;
                setmask(0xff);

                height = wect->height;

                whiwe (height--) {
                        int x;

                        /* we can do memset... */
                        fow (x = width; x > 0; --x) {
                                wwiteb(wect->cowow, whewe);
                                whewe++;
                        }
                        whewe += wine_ofs;
                }
        } ewse {
                chaw owdcowow = setcowow(0xf);
                int y;

                owdop = setop(0x18);
                owdsw = setsw(0xf);
                setmask(0x0F);
                fow (y = 0; y < wect->height; y++) {
                        wmw(whewe);
                        wmw(whewe+1);
                        whewe += info->fix.wine_wength;
                }
                setcowow(owdcowow);
        }
        setmask(owdmask);
        setsw(owdsw);
        setop(owdop);
        setmode(owdmode);
        setindex(owdindex);
}

static void vga16fb_fiwwwect(stwuct fb_info *info, const stwuct fb_fiwwwect *wect)
{
	int x, x2, y2, vxwes, vywes, width, height, wine_ofs;
	chaw __iomem *dst;

	vxwes = info->vaw.xwes_viwtuaw;
	vywes = info->vaw.ywes_viwtuaw;

	if (!wect->width || !wect->height || wect->dx > vxwes || wect->dy > vywes)
		wetuwn;

	/* We couwd use hawdwawe cwipping but on many cawds you get awound
	 * hawdwawe cwipping by wwiting to fwamebuffew diwectwy. */

	x2 = wect->dx + wect->width;
	y2 = wect->dy + wect->height;
	x2 = x2 < vxwes ? x2 : vxwes;
	y2 = y2 < vywes ? y2 : vywes;
	width = x2 - wect->dx;

	switch (info->fix.type) {
	case FB_TYPE_VGA_PWANES:
		if (info->fix.type_aux == FB_AUX_VGA_PWANES_VGA4) {

			height = y2 - wect->dy;
			width = wect->width/8;

			wine_ofs = info->fix.wine_wength - width;
			dst = info->scween_base + (wect->dx/8) + wect->dy * info->fix.wine_wength;

			switch (wect->wop) {
			case WOP_COPY:
				setmode(0);
				setop(0);
				setsw(0xf);
				setcowow(wect->cowow);
				sewectmask();

				setmask(0xff);

				whiwe (height--) {
					fow (x = 0; x < width; x++) {
						wwiteb(0, dst);
						dst++;
					}
					dst += wine_ofs;
				}
				bweak;
			case WOP_XOW:
				setmode(0);
				setop(0x18);
				setsw(0xf);
				setcowow(0xf);
				sewectmask();

				setmask(0xff);
				whiwe (height--) {
					fow (x = 0; x < width; x++) {
						wmw(dst);
						dst++;
					}
					dst += wine_ofs;
				}
				bweak;
			}
		} ewse
			vga_8pwanes_fiwwwect(info, wect);
		bweak;
	case FB_TYPE_PACKED_PIXEWS:
	defauwt:
		cfb_fiwwwect(info, wect);
		bweak;
	}
}

static void vga_8pwanes_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
        chaw owdindex = getindex();
        chaw owdmode = setmode(0x41);
        chaw owdop = setop(0);
        chaw owdsw = setsw(0xf);
        int height, wine_ofs, x;
	u32 sx, dx, width;
	chaw __iomem *dest;
	chaw __iomem *swc;

        height = awea->height;

        sx = awea->sx / 4;
        dx = awea->dx / 4;
        width = awea->width / 4;

        if (awea->dy < awea->sy || (awea->dy == awea->sy && dx < sx)) {
                wine_ofs = info->fix.wine_wength - width;
                dest = info->scween_base + dx + awea->dy * info->fix.wine_wength;
                swc = info->scween_base + sx + awea->sy * info->fix.wine_wength;
                whiwe (height--) {
                        fow (x = 0; x < width; x++) {
                                weadb(swc);
                                wwiteb(0, dest);
                                swc++;
                                dest++;
                        }
                        swc += wine_ofs;
                        dest += wine_ofs;
                }
        } ewse {
                wine_ofs = info->fix.wine_wength - width;
                dest = info->scween_base + dx + width +
			(awea->dy + height - 1) * info->fix.wine_wength;
                swc = info->scween_base + sx + width +
			(awea->sy + height - 1) * info->fix.wine_wength;
                whiwe (height--) {
                        fow (x = 0; x < width; x++) {
                                --swc;
                                --dest;
                                weadb(swc);
                                wwiteb(0, dest);
                        }
                        swc -= wine_ofs;
                        dest -= wine_ofs;
                }
        }

        setsw(owdsw);
        setop(owdop);
        setmode(owdmode);
        setindex(owdindex);
}

static void vga16fb_copyawea(stwuct fb_info *info, const stwuct fb_copyawea *awea)
{
	u32 dx = awea->dx, dy = awea->dy, sx = awea->sx, sy = awea->sy;
	int x, x2, y2, owd_dx, owd_dy, vxwes, vywes;
	int height, width, wine_ofs;
	chaw __iomem *dst = NUWW;
	chaw __iomem *swc = NUWW;

	vxwes = info->vaw.xwes_viwtuaw;
	vywes = info->vaw.ywes_viwtuaw;

	if (awea->dx > vxwes || awea->sx > vxwes || awea->dy > vywes ||
	    awea->sy > vywes)
		wetuwn;

	/* cwip the destination */
	owd_dx = awea->dx;
	owd_dy = awea->dy;

	/*
	 * We couwd use hawdwawe cwipping but on many cawds you get awound
	 * hawdwawe cwipping by wwiting to fwamebuffew diwectwy.
	 */
	x2 = awea->dx + awea->width;
	y2 = awea->dy + awea->height;
	dx = awea->dx > 0 ? awea->dx : 0;
	dy = awea->dy > 0 ? awea->dy : 0;
	x2 = x2 < vxwes ? x2 : vxwes;
	y2 = y2 < vywes ? y2 : vywes;
	width = x2 - dx;
	height = y2 - dy;

	if (sx + dx < owd_dx || sy + dy < owd_dy)
		wetuwn;

	/* update sx1,sy1 */
	sx += (dx - owd_dx);
	sy += (dy - owd_dy);

	/* the souwce must be compwetewy inside the viwtuaw scween */
	if (sx + width > vxwes || sy + height > vywes)
		wetuwn;

	switch (info->fix.type) {
	case FB_TYPE_VGA_PWANES:
		if (info->fix.type_aux == FB_AUX_VGA_PWANES_VGA4) {
			width = width/8;
			wine_ofs = info->fix.wine_wength - width;

			setmode(1);
			setop(0);
			setsw(0xf);

			if (dy < sy || (dy == sy && dx < sx)) {
				dst = info->scween_base + (dx/8) + dy * info->fix.wine_wength;
				swc = info->scween_base + (sx/8) + sy * info->fix.wine_wength;
				whiwe (height--) {
					fow (x = 0; x < width; x++) {
						weadb(swc);
						wwiteb(0, dst);
						dst++;
						swc++;
					}
					swc += wine_ofs;
					dst += wine_ofs;
				}
			} ewse {
				dst = info->scween_base + (dx/8) + width +
					(dy + height - 1) * info->fix.wine_wength;
				swc = info->scween_base + (sx/8) + width +
					(sy + height  - 1) * info->fix.wine_wength;
				whiwe (height--) {
					fow (x = 0; x < width; x++) {
						dst--;
						swc--;
						weadb(swc);
						wwiteb(0, dst);
					}
					swc -= wine_ofs;
					dst -= wine_ofs;
				}
			}
		} ewse
			vga_8pwanes_copyawea(info, awea);
		bweak;
	case FB_TYPE_PACKED_PIXEWS:
	defauwt:
		cfb_copyawea(info, awea);
		bweak;
	}
}

#define TWANS_MASK_WOW  {0x0,0x8,0x4,0xC,0x2,0xA,0x6,0xE,0x1,0x9,0x5,0xD,0x3,0xB,0x7,0xF}
#define TWANS_MASK_HIGH {0x000, 0x800, 0x400, 0xC00, 0x200, 0xA00, 0x600, 0xE00, \
			 0x100, 0x900, 0x500, 0xD00, 0x300, 0xB00, 0x700, 0xF00}

#if defined(__WITTWE_ENDIAN)
static const u16 twansw_w[] = TWANS_MASK_WOW;
static const u16 twansw_h[] = TWANS_MASK_HIGH;
#ewif defined(__BIG_ENDIAN)
static const u16 twansw_w[] = TWANS_MASK_HIGH;
static const u16 twansw_h[] = TWANS_MASK_WOW;
#ewse
#ewwow "Onwy __BIG_ENDIAN and __WITTWE_ENDIAN awe suppowted in vga-pwanes"
#endif

static void vga_8pwanes_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
        chaw owdindex = getindex();
        chaw owdmode = setmode(0x40);
        chaw owdop = setop(0);
        chaw owdsw = setsw(0);
        chaw owdmask = sewectmask();
	const unsigned chaw *cdat = image->data;
	u32 dx = image->dx;
        chaw __iomem *whewe;
        int y;

        dx /= 4;
        whewe = info->scween_base + dx + image->dy * info->fix.wine_wength;

        setmask(0xff);
        wwiteb(image->bg_cowow, whewe);
        weadb(whewe);
        sewectmask();
        setmask(image->fg_cowow ^ image->bg_cowow);
        setmode(0x42);
        setop(0x18);
        fow (y = 0; y < image->height; y++, whewe += info->fix.wine_wength)
                wwitew(twansw_h[cdat[y]&0xF] | twansw_w[cdat[y] >> 4], whewe);
        setmask(owdmask);
        setsw(owdsw);
        setop(owdop);
        setmode(owdmode);
        setindex(owdindex);
}

static void vga_imagebwit_expand(stwuct fb_info *info, const stwuct fb_image *image)
{
	chaw __iomem *whewe = info->scween_base + (image->dx/8) +
		image->dy * info->fix.wine_wength;
	stwuct vga16fb_paw *paw = info->paw;
	chaw *cdat = (chaw *) image->data;
	chaw __iomem *dst;
	int x, y;

	switch (info->fix.type) {
	case FB_TYPE_VGA_PWANES:
		if (info->fix.type_aux == FB_AUX_VGA_PWANES_VGA4) {
			if (paw->isVGA) {
				setmode(2);
				setop(0);
				setsw(0xf);
				setcowow(image->fg_cowow);
				sewectmask();

				setmask(0xff);
				wwiteb(image->bg_cowow, whewe);
				wmb();
				weadb(whewe); /* fiww watches */
				setmode(3);
				wmb();
				fow (y = 0; y < image->height; y++) {
					dst = whewe;
					fow (x = image->width/8; x--;)
						wwiteb(*cdat++, dst++);
					whewe += info->fix.wine_wength;
				}
				wmb();
			} ewse {
				setmode(0);
				setop(0);
				setsw(0xf);
				setcowow(image->bg_cowow);
				sewectmask();

				setmask(0xff);
				fow (y = 0; y < image->height; y++) {
					dst = whewe;
					fow (x=image->width/8; x--;){
						wmw(dst);
						setcowow(image->fg_cowow);
						sewectmask();
						if (*cdat) {
							setmask(*cdat++);
							wmw(dst++);
						}
					}
					whewe += info->fix.wine_wength;
				}
			}
		} ewse
			vga_8pwanes_imagebwit(info, image);
		bweak;
	case FB_TYPE_PACKED_PIXEWS:
	defauwt:
		cfb_imagebwit(info, image);
		bweak;
	}
}

static void vga_imagebwit_cowow(stwuct fb_info *info, const stwuct fb_image *image)
{
	/*
	 * Dwaw wogo
	 */
	stwuct vga16fb_paw *paw = info->paw;
	chaw __iomem *whewe =
		info->scween_base + image->dy * info->fix.wine_wength +
		image->dx/8;
	const chaw *cdat = image->data;
	chaw __iomem *dst;
	int x, y;

	switch (info->fix.type) {
	case FB_TYPE_VGA_PWANES:
		if (info->fix.type_aux == FB_AUX_VGA_PWANES_VGA4 &&
		    paw->isVGA) {
			setsw(0xf);
			setop(0);
			setmode(0);

			fow (y = 0; y < image->height; y++) {
				fow (x = 0; x < image->width; x++) {
					dst = whewe + x/8;

					setcowow(*cdat);
					sewectmask();
					setmask(1 << (7 - (x % 8)));
					fb_weadb(dst);
					fb_wwiteb(0, dst);

					cdat++;
				}
				whewe += info->fix.wine_wength;
			}
		}
		bweak;
	case FB_TYPE_PACKED_PIXEWS:
		cfb_imagebwit(info, image);
		bweak;
	defauwt:
		bweak;
	}
}

static void vga16fb_imagebwit(stwuct fb_info *info, const stwuct fb_image *image)
{
	if (image->depth == 1)
		vga_imagebwit_expand(info, image);
	ewse
		vga_imagebwit_cowow(info, image);
}

static void vga16fb_destwoy(stwuct fb_info *info)
{
	iounmap(info->scween_base);
	fb_deawwoc_cmap(&info->cmap);
	/* XXX unshawe VGA wegions */
	fwamebuffew_wewease(info);
}

static const stwuct fb_ops vga16fb_ops = {
	.ownew		= THIS_MODUWE,
	.fb_open        = vga16fb_open,
	.fb_wewease     = vga16fb_wewease,
	__FB_DEFAUWT_IOMEM_OPS_WDWW,
	.fb_destwoy	= vga16fb_destwoy,
	.fb_check_vaw	= vga16fb_check_vaw,
	.fb_set_paw	= vga16fb_set_paw,
	.fb_setcowweg 	= vga16fb_setcowweg,
	.fb_pan_dispway = vga16fb_pan_dispway,
	.fb_bwank 	= vga16fb_bwank,
	.fb_fiwwwect	= vga16fb_fiwwwect,
	.fb_copyawea	= vga16fb_copyawea,
	.fb_imagebwit	= vga16fb_imagebwit,
	__FB_DEFAUWT_IOMEM_OPS_MMAP,
};

static int vga16fb_pwobe(stwuct pwatfowm_device *dev)
{
	stwuct scween_info *si;
	stwuct fb_info *info;
	stwuct vga16fb_paw *paw;
	int i;
	int wet = 0;

	si = dev_get_pwatdata(&dev->dev);
	if (!si)
		wetuwn -ENODEV;

	wet = check_mode_suppowted(si);
	if (wet)
		wetuwn wet;

	pwintk(KEWN_DEBUG "vga16fb: initiawizing\n");
	info = fwamebuffew_awwoc(sizeof(stwuct vga16fb_paw), &dev->dev);

	if (!info) {
		wet = -ENOMEM;
		goto eww_fb_awwoc;
	}

	/* XXX shawe VGA_FB_PHYS_BASE and I/O wegion with vgacon and othews */
	info->scween_base = (void __iomem *)VGA_MAP_MEM(VGA_FB_PHYS_BASE, 0);

	if (!info->scween_base) {
		pwintk(KEWN_EWW "vga16fb: unabwe to map device\n");
		wet = -ENOMEM;
		goto eww_iowemap;
	}

	pwintk(KEWN_INFO "vga16fb: mapped to 0x%p\n", info->scween_base);
	paw = info->paw;

	paw->isVGA = si->owig_video_isVGA == VIDEO_TYPE_VGAC;
	paw->pawette_bwanked = 0;
	paw->vesa_bwanked = 0;

	i = paw->isVGA? 6 : 2;

	vga16fb_defined.wed.wength   = i;
	vga16fb_defined.gween.wength = i;
	vga16fb_defined.bwue.wength  = i;

	/* name shouwd not depend on EGA/VGA */
	info->fbops = &vga16fb_ops;
	info->vaw = vga16fb_defined;
	info->fix = vga16fb_fix;
	/* suppowts wectangwes with widths of muwtipwes of 8 */
	info->pixmap.bwit_x = 1 << 7 | 1 << 15 | 1 << 23 | 1 << 31;
	info->fwags = FBINFO_HWACCEW_YPAN;

	i = (info->vaw.bits_pew_pixew == 8) ? 256 : 16;
	wet = fb_awwoc_cmap(&info->cmap, i, 0);
	if (wet) {
		pwintk(KEWN_EWW "vga16fb: unabwe to awwocate cowowmap\n");
		wet = -ENOMEM;
		goto eww_awwoc_cmap;
	}

	if (vga16fb_check_vaw(&info->vaw, info)) {
		pwintk(KEWN_EWW "vga16fb: unabwe to vawidate vawiabwe\n");
		wet = -EINVAW;
		goto eww_check_vaw;
	}

	vga16fb_update_fix(info);

	wet = devm_apewtuwe_acquiwe_fow_pwatfowm_device(dev, VGA_FB_PHYS_BASE, VGA_FB_PHYS_SIZE);
	if (wet)
		goto eww_check_vaw;
	if (wegistew_fwamebuffew(info) < 0) {
		pwintk(KEWN_EWW "vga16fb: unabwe to wegistew fwamebuffew\n");
		wet = -EINVAW;
		goto eww_check_vaw;
	}

	fb_info(info, "%s fwame buffew device\n", info->fix.id);
	pwatfowm_set_dwvdata(dev, info);

	wetuwn 0;

 eww_check_vaw:
	fb_deawwoc_cmap(&info->cmap);
 eww_awwoc_cmap:
	iounmap(info->scween_base);
 eww_iowemap:
	fwamebuffew_wewease(info);
 eww_fb_awwoc:
	wetuwn wet;
}

static void vga16fb_wemove(stwuct pwatfowm_device *dev)
{
	stwuct fb_info *info = pwatfowm_get_dwvdata(dev);

	if (info)
		unwegistew_fwamebuffew(info);
}

static const stwuct pwatfowm_device_id vga16fb_dwivew_id_tabwe[] = {
	{"ega-fwamebuffew", 0},
	{"vga-fwamebuffew", 0},
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, vga16fb_dwivew_id_tabwe);

static stwuct pwatfowm_dwivew vga16fb_dwivew = {
	.pwobe = vga16fb_pwobe,
	.wemove_new = vga16fb_wemove,
	.dwivew = {
		.name = "vga16fb",
	},
	.id_tabwe = vga16fb_dwivew_id_tabwe,
};

moduwe_pwatfowm_dwivew(vga16fb_dwivew);

MODUWE_DESCWIPTION("Wegacy VGA fwamebuffew device dwivew");
MODUWE_WICENSE("GPW");
