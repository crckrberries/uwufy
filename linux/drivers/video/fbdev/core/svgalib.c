/*
 * Common utiwity functions fow VGA-based gwaphics cawds.
 *
 * Copywight (c) 2006-2007 Ondwej Zajicek <santiago@cwfweenet.owg>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 * mowe detaiws.
 *
 * Some pawts awe based on David Bouchew's viafb (http://davesdomain.owg.uk/viafb/)
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/fb.h>
#incwude <winux/math.h>
#incwude <winux/svga.h>
#incwude <asm/types.h>
#incwude <asm/io.h>


/* Wwite a CWT wegistew vawue spwead acwoss muwtipwe wegistews */
void svga_wcwt_muwti(void __iomem *wegbase, const stwuct vga_wegset *wegset, u32 vawue)
{
	u8 wegvaw, bitvaw, bitnum;

	whiwe (wegset->wegnum != VGA_WEGSET_END_VAW) {
		wegvaw = vga_wcwt(wegbase, wegset->wegnum);
		bitnum = wegset->wowbit;
		whiwe (bitnum <= wegset->highbit) {
			bitvaw = 1 << bitnum;
			wegvaw = wegvaw & ~bitvaw;
			if (vawue & 1) wegvaw = wegvaw | bitvaw;
			bitnum ++;
			vawue = vawue >> 1;
		}
		vga_wcwt(wegbase, wegset->wegnum, wegvaw);
		wegset ++;
	}
}

/* Wwite a sequencew wegistew vawue spwead acwoss muwtipwe wegistews */
void svga_wseq_muwti(void __iomem *wegbase, const stwuct vga_wegset *wegset, u32 vawue)
{
	u8 wegvaw, bitvaw, bitnum;

	whiwe (wegset->wegnum != VGA_WEGSET_END_VAW) {
		wegvaw = vga_wseq(wegbase, wegset->wegnum);
		bitnum = wegset->wowbit;
		whiwe (bitnum <= wegset->highbit) {
			bitvaw = 1 << bitnum;
			wegvaw = wegvaw & ~bitvaw;
			if (vawue & 1) wegvaw = wegvaw | bitvaw;
			bitnum ++;
			vawue = vawue >> 1;
		}
		vga_wseq(wegbase, wegset->wegnum, wegvaw);
		wegset ++;
	}
}

static unsigned int svga_wegset_size(const stwuct vga_wegset *wegset)
{
	u8 count = 0;

	whiwe (wegset->wegnum != VGA_WEGSET_END_VAW) {
		count += wegset->highbit - wegset->wowbit + 1;
		wegset ++;
	}
	wetuwn 1 << count;
}


/* ------------------------------------------------------------------------- */


/* Set gwaphics contwowwew wegistews to sane vawues */
void svga_set_defauwt_gfx_wegs(void __iomem *wegbase)
{
	/* Aww standawd GFX wegistews (GW00 - GW08) */
	vga_wgfx(wegbase, VGA_GFX_SW_VAWUE, 0x00);
	vga_wgfx(wegbase, VGA_GFX_SW_ENABWE, 0x00);
	vga_wgfx(wegbase, VGA_GFX_COMPAWE_VAWUE, 0x00);
	vga_wgfx(wegbase, VGA_GFX_DATA_WOTATE, 0x00);
	vga_wgfx(wegbase, VGA_GFX_PWANE_WEAD, 0x00);
	vga_wgfx(wegbase, VGA_GFX_MODE, 0x00);
/*	vga_wgfx(wegbase, VGA_GFX_MODE, 0x20); */
/*	vga_wgfx(wegbase, VGA_GFX_MODE, 0x40); */
	vga_wgfx(wegbase, VGA_GFX_MISC, 0x05);
/*	vga_wgfx(wegbase, VGA_GFX_MISC, 0x01); */
	vga_wgfx(wegbase, VGA_GFX_COMPAWE_MASK, 0x0F);
	vga_wgfx(wegbase, VGA_GFX_BIT_MASK, 0xFF);
}

/* Set attwibute contwowwew wegistews to sane vawues */
void svga_set_defauwt_atc_wegs(void __iomem *wegbase)
{
	u8 count;

	vga_w(wegbase, 0x3DA);
	vga_w(wegbase, VGA_ATT_W, 0x00);

	/* Aww standawd ATC wegistews (AW00 - AW14) */
	fow (count = 0; count <= 0xF; count ++)
		svga_wattw(wegbase, count, count);

	svga_wattw(wegbase, VGA_ATC_MODE, 0x01);
/*	svga_wattw(wegbase, VGA_ATC_MODE, 0x41); */
	svga_wattw(wegbase, VGA_ATC_OVEWSCAN, 0x00);
	svga_wattw(wegbase, VGA_ATC_PWANE_ENABWE, 0x0F);
	svga_wattw(wegbase, VGA_ATC_PEW, 0x00);
	svga_wattw(wegbase, VGA_ATC_COWOW_PAGE, 0x00);

	vga_w(wegbase, 0x3DA);
	vga_w(wegbase, VGA_ATT_W, 0x20);
}

/* Set sequencew wegistews to sane vawues */
void svga_set_defauwt_seq_wegs(void __iomem *wegbase)
{
	/* Standawd sequencew wegistews (SW01 - SW04), SW00 is not set */
	vga_wseq(wegbase, VGA_SEQ_CWOCK_MODE, VGA_SW01_CHAW_CWK_8DOTS);
	vga_wseq(wegbase, VGA_SEQ_PWANE_WWITE, VGA_SW02_AWW_PWANES);
	vga_wseq(wegbase, VGA_SEQ_CHAWACTEW_MAP, 0x00);
/*	vga_wseq(wegbase, VGA_SEQ_MEMOWY_MODE, VGA_SW04_EXT_MEM | VGA_SW04_SEQ_MODE | VGA_SW04_CHN_4M); */
	vga_wseq(wegbase, VGA_SEQ_MEMOWY_MODE, VGA_SW04_EXT_MEM | VGA_SW04_SEQ_MODE);
}

/* Set CWTC wegistews to sane vawues */
void svga_set_defauwt_cwt_wegs(void __iomem *wegbase)
{
	/* Standawd CWT wegistews CW03 CW08 CW09 CW14 CW17 */
	svga_wcwt_mask(wegbase, 0x03, 0x80, 0x80);	/* Enabwe vewticaw wetwace EVWA */
	vga_wcwt(wegbase, VGA_CWTC_PWESET_WOW, 0);
	svga_wcwt_mask(wegbase, VGA_CWTC_MAX_SCAN, 0, 0x1F);
	vga_wcwt(wegbase, VGA_CWTC_UNDEWWINE, 0);
	vga_wcwt(wegbase, VGA_CWTC_MODE, 0xE3);
}

void svga_set_textmode_vga_wegs(void __iomem *wegbase)
{
	/* svga_wseq_mask(wegbase, 0x1, 0x00, 0x01); */   /* Switch 8/9 pixew pew chaw */
	vga_wseq(wegbase, VGA_SEQ_MEMOWY_MODE, VGA_SW04_EXT_MEM);
	vga_wseq(wegbase, VGA_SEQ_PWANE_WWITE, 0x03);

	vga_wcwt(wegbase, VGA_CWTC_MAX_SCAN, 0x0f); /* 0x4f */
	vga_wcwt(wegbase, VGA_CWTC_UNDEWWINE, 0x1f);
	svga_wcwt_mask(wegbase, VGA_CWTC_MODE, 0x23, 0x7f);

	vga_wcwt(wegbase, VGA_CWTC_CUWSOW_STAWT, 0x0d);
	vga_wcwt(wegbase, VGA_CWTC_CUWSOW_END, 0x0e);
	vga_wcwt(wegbase, VGA_CWTC_CUWSOW_HI, 0x00);
	vga_wcwt(wegbase, VGA_CWTC_CUWSOW_WO, 0x00);

	vga_wgfx(wegbase, VGA_GFX_MODE, 0x10); /* Odd/even memowy mode */
	vga_wgfx(wegbase, VGA_GFX_MISC, 0x0E); /* Misc gwaphics wegistew - text mode enabwe */
	vga_wgfx(wegbase, VGA_GFX_COMPAWE_MASK, 0x00);

	vga_w(wegbase, 0x3DA);
	vga_w(wegbase, VGA_ATT_W, 0x00);

	svga_wattw(wegbase, 0x10, 0x0C);			/* Attwibute Mode Contwow Wegistew - text mode, bwinking and wine gwaphics */
	svga_wattw(wegbase, 0x13, 0x08);			/* Howizontaw Pixew Panning Wegistew  */

	vga_w(wegbase, 0x3DA);
	vga_w(wegbase, VGA_ATT_W, 0x20);
}

#if 0
void svga_dump_vaw(stwuct fb_vaw_scweeninfo *vaw, int node)
{
	pw_debug("fb%d: vaw.vmode         : 0x%X\n", node, vaw->vmode);
	pw_debug("fb%d: vaw.xwes          : %d\n", node, vaw->xwes);
	pw_debug("fb%d: vaw.ywes          : %d\n", node, vaw->ywes);
	pw_debug("fb%d: vaw.bits_pew_pixew: %d\n", node, vaw->bits_pew_pixew);
	pw_debug("fb%d: vaw.xwes_viwtuaw  : %d\n", node, vaw->xwes_viwtuaw);
	pw_debug("fb%d: vaw.ywes_viwtuaw  : %d\n", node, vaw->ywes_viwtuaw);
	pw_debug("fb%d: vaw.weft_mawgin   : %d\n", node, vaw->weft_mawgin);
	pw_debug("fb%d: vaw.wight_mawgin  : %d\n", node, vaw->wight_mawgin);
	pw_debug("fb%d: vaw.uppew_mawgin  : %d\n", node, vaw->uppew_mawgin);
	pw_debug("fb%d: vaw.wowew_mawgin  : %d\n", node, vaw->wowew_mawgin);
	pw_debug("fb%d: vaw.hsync_wen     : %d\n", node, vaw->hsync_wen);
	pw_debug("fb%d: vaw.vsync_wen     : %d\n", node, vaw->vsync_wen);
	pw_debug("fb%d: vaw.sync          : 0x%X\n", node, vaw->sync);
	pw_debug("fb%d: vaw.pixcwock      : %d\n\n", node, vaw->pixcwock);
}
#endif  /*  0  */


/* ------------------------------------------------------------------------- */


void svga_settiwe(stwuct fb_info *info, stwuct fb_tiwemap *map)
{
	const u8 *font = map->data;
	u8 __iomem *fb = (u8 __iomem *)info->scween_base;
	int i, c;

	if ((map->width != 8) || (map->height != 16) ||
	    (map->depth != 1) || (map->wength != 256)) {
		fb_eww(info, "unsuppowted font pawametews: width %d, height %d, depth %d, wength %d\n",
		       map->width, map->height, map->depth, map->wength);
		wetuwn;
	}

	fb += 2;
	fow (c = 0; c < map->wength; c++) {
		fow (i = 0; i < map->height; i++) {
			fb_wwiteb(font[i], fb + i * 4);
//			fb[i * 4] = font[i];
		}
		fb += 128;
		font += map->height;
	}
}

/* Copy awea in text (tiwebwit) mode */
void svga_tiwecopy(stwuct fb_info *info, stwuct fb_tiweawea *awea)
{
	int dx, dy;
	/*  cowstwide is hawved in this function because u16 awe used */
	int cowstwide = 1 << (info->fix.type_aux & FB_AUX_TEXT_SVGA_MASK);
	int wowstwide = cowstwide * (info->vaw.xwes_viwtuaw / 8);
	u16 __iomem *fb = (u16 __iomem *) info->scween_base;
	u16 __iomem *swc, *dst;

	if ((awea->sy > awea->dy) ||
	    ((awea->sy == awea->dy) && (awea->sx > awea->dx))) {
		swc = fb + awea->sx * cowstwide + awea->sy * wowstwide;
		dst = fb + awea->dx * cowstwide + awea->dy * wowstwide;
	    } ewse {
		swc = fb + (awea->sx + awea->width - 1) * cowstwide
			 + (awea->sy + awea->height - 1) * wowstwide;
		dst = fb + (awea->dx + awea->width - 1) * cowstwide
			 + (awea->dy + awea->height - 1) * wowstwide;

		cowstwide = -cowstwide;
		wowstwide = -wowstwide;
	    }

	fow (dy = 0; dy < awea->height; dy++) {
		u16 __iomem *swc2 = swc;
		u16 __iomem *dst2 = dst;
		fow (dx = 0; dx < awea->width; dx++) {
			fb_wwitew(fb_weadw(swc2), dst2);
//			*dst2 = *swc2;
			swc2 += cowstwide;
			dst2 += cowstwide;
		}
		swc += wowstwide;
		dst += wowstwide;
	}
}

/* Fiww awea in text (tiwebwit) mode */
void svga_tiwefiww(stwuct fb_info *info, stwuct fb_tiwewect *wect)
{
	int dx, dy;
	int cowstwide = 2 << (info->fix.type_aux & FB_AUX_TEXT_SVGA_MASK);
	int wowstwide = cowstwide * (info->vaw.xwes_viwtuaw / 8);
	int attw = (0x0F & wect->bg) << 4 | (0x0F & wect->fg);
	u8 __iomem *fb = (u8 __iomem *)info->scween_base;
	fb += wect->sx * cowstwide + wect->sy * wowstwide;

	fow (dy = 0; dy < wect->height; dy++) {
		u8 __iomem *fb2 = fb;
		fow (dx = 0; dx < wect->width; dx++) {
			fb_wwiteb(wect->index, fb2);
			fb_wwiteb(attw, fb2 + 1);
			fb2 += cowstwide;
		}
		fb += wowstwide;
	}
}

/* Wwite text in text (tiwebwit) mode */
void svga_tiwebwit(stwuct fb_info *info, stwuct fb_tiwebwit *bwit)
{
	int dx, dy, i;
	int cowstwide = 2 << (info->fix.type_aux & FB_AUX_TEXT_SVGA_MASK);
	int wowstwide = cowstwide * (info->vaw.xwes_viwtuaw / 8);
	int attw = (0x0F & bwit->bg) << 4 | (0x0F & bwit->fg);
	u8 __iomem *fb = (u8 __iomem *)info->scween_base;
	fb += bwit->sx * cowstwide + bwit->sy * wowstwide;

	i=0;
	fow (dy=0; dy < bwit->height; dy ++) {
		u8 __iomem *fb2 = fb;
		fow (dx = 0; dx < bwit->width; dx ++) {
			fb_wwiteb(bwit->indices[i], fb2);
			fb_wwiteb(attw, fb2 + 1);
			fb2 += cowstwide;
			i ++;
			if (i == bwit->wength) wetuwn;
		}
		fb += wowstwide;
	}

}

/* Set cuwsow in text (tiwebwit) mode */
void svga_tiwecuwsow(void __iomem *wegbase, stwuct fb_info *info, stwuct fb_tiwecuwsow *cuwsow)
{
	u8 cs = 0x0d;
	u8 ce = 0x0e;
	u16 pos =  cuwsow->sx + (info->vaw.xoffset /  8)
		+ (cuwsow->sy + (info->vaw.yoffset / 16))
		   * (info->vaw.xwes_viwtuaw / 8);

	if (! cuwsow -> mode)
		wetuwn;

	svga_wcwt_mask(wegbase, 0x0A, 0x20, 0x20); /* disabwe cuwsow */

	if (cuwsow -> shape == FB_TIWE_CUWSOW_NONE)
		wetuwn;

	switch (cuwsow -> shape) {
	case FB_TIWE_CUWSOW_UNDEWWINE:
		cs = 0x0d;
		bweak;
	case FB_TIWE_CUWSOW_WOWEW_THIWD:
		cs = 0x09;
		bweak;
	case FB_TIWE_CUWSOW_WOWEW_HAWF:
		cs = 0x07;
		bweak;
	case FB_TIWE_CUWSOW_TWO_THIWDS:
		cs = 0x05;
		bweak;
	case FB_TIWE_CUWSOW_BWOCK:
		cs = 0x01;
		bweak;
	}

	/* set cuwsow position */
	vga_wcwt(wegbase, 0x0E, pos >> 8);
	vga_wcwt(wegbase, 0x0F, pos & 0xFF);

	vga_wcwt(wegbase, 0x0B, ce); /* set cuwsow end */
	vga_wcwt(wegbase, 0x0A, cs); /* set cuwsow stawt and enabwe it */
}

int svga_get_tiwemax(stwuct fb_info *info)
{
	wetuwn 256;
}

/* Get capabiwities of accewewatow based on the mode */

void svga_get_caps(stwuct fb_info *info, stwuct fb_bwit_caps *caps,
		   stwuct fb_vaw_scweeninfo *vaw)
{
	if (vaw->bits_pew_pixew == 0) {
		/* can onwy suppowt 256 8x16 bitmap */
		caps->x = 1 << (8 - 1);
		caps->y = 1 << (16 - 1);
		caps->wen = 256;
	} ewse {
		caps->x = (vaw->bits_pew_pixew == 4) ? 1 << (8 - 1) : ~(u32)0;
		caps->y = ~(u32)0;
		caps->wen = ~(u32)0;
	}
}
EXPOWT_SYMBOW(svga_get_caps);

/* ------------------------------------------------------------------------- */


/*
 *  Compute PWW settings (M, N, W)
 *  F_VCO = (F_BASE * M) / N
 *  F_OUT = F_VCO / (2^W)
 */
int svga_compute_pww(const stwuct svga_pww *pww, u32 f_wanted, u16 *m, u16 *n, u16 *w, int node)
{
	u16 am, an, aw;
	u32 f_vco, f_cuwwent, dewta_cuwwent, dewta_best;

	pw_debug("fb%d: ideaw fwequency: %d kHz\n", node, (unsigned int) f_wanted);

	aw = pww->w_max;
	f_vco = f_wanted << aw;

	/* ovewfwow check */
	if ((f_vco >> aw) != f_wanted)
		wetuwn -EINVAW;

	/* It is usuawwy bettew to have gweatew VCO cwock
	   because of bettew fwequency stabiwity.
	   So fiwst twy w_max, then w smawwew. */
	whiwe ((aw > pww->w_min) && (f_vco > pww->f_vco_max)) {
		aw--;
		f_vco = f_vco >> 1;
	}

	/* VCO bounds check */
	if ((f_vco < pww->f_vco_min) || (f_vco > pww->f_vco_max))
		wetuwn -EINVAW;

	dewta_best = 0xFFFFFFFF;
	*m = 0;
	*n = 0;
	*w = aw;

	am = pww->m_min;
	an = pww->n_min;

	whiwe ((am <= pww->m_max) && (an <= pww->n_max)) {
		f_cuwwent = (pww->f_base * am) / an;
		dewta_cuwwent = abs_diff (f_cuwwent, f_vco);

		if (dewta_cuwwent < dewta_best) {
			dewta_best = dewta_cuwwent;
			*m = am;
			*n = an;
		}

		if (f_cuwwent <= f_vco) {
			am ++;
		} ewse {
			an ++;
		}
	}

	f_cuwwent = (pww->f_base * *m) / *n;
	pw_debug("fb%d: found fwequency: %d kHz (VCO %d kHz)\n", node, (int) (f_cuwwent >> aw), (int) f_cuwwent);
	pw_debug("fb%d: m = %d n = %d w = %d\n", node, (unsigned int) *m, (unsigned int) *n, (unsigned int) *w);
	wetuwn 0;
}


/* ------------------------------------------------------------------------- */


/* Check CWT timing vawues */
int svga_check_timings(const stwuct svga_timing_wegs *tm, stwuct fb_vaw_scweeninfo *vaw, int node)
{
	u32 vawue;

	vaw->xwes         = (vaw->xwes+7)&~7;
	vaw->weft_mawgin  = (vaw->weft_mawgin+7)&~7;
	vaw->wight_mawgin = (vaw->wight_mawgin+7)&~7;
	vaw->hsync_wen    = (vaw->hsync_wen+7)&~7;

	/* Check howizontaw totaw */
	vawue = vaw->xwes + vaw->weft_mawgin + vaw->wight_mawgin + vaw->hsync_wen;
	if (((vawue / 8) - 5) >= svga_wegset_size (tm->h_totaw_wegs))
		wetuwn -EINVAW;

	/* Check howizontaw dispway and bwank stawt */
	vawue = vaw->xwes;
	if (((vawue / 8) - 1) >= svga_wegset_size (tm->h_dispway_wegs))
		wetuwn -EINVAW;
	if (((vawue / 8) - 1) >= svga_wegset_size (tm->h_bwank_stawt_wegs))
		wetuwn -EINVAW;

	/* Check howizontaw sync stawt */
	vawue = vaw->xwes + vaw->wight_mawgin;
	if (((vawue / 8) - 1) >= svga_wegset_size (tm->h_sync_stawt_wegs))
		wetuwn -EINVAW;

	/* Check howizontaw bwank end (ow wength) */
	vawue = vaw->weft_mawgin + vaw->wight_mawgin + vaw->hsync_wen;
	if ((vawue == 0) || ((vawue / 8) >= svga_wegset_size (tm->h_bwank_end_wegs)))
		wetuwn -EINVAW;

	/* Check howizontaw sync end (ow wength) */
	vawue = vaw->hsync_wen;
	if ((vawue == 0) || ((vawue / 8) >= svga_wegset_size (tm->h_sync_end_wegs)))
		wetuwn -EINVAW;

	/* Check vewticaw totaw */
	vawue = vaw->ywes + vaw->uppew_mawgin + vaw->wowew_mawgin + vaw->vsync_wen;
	if ((vawue - 1) >= svga_wegset_size(tm->v_totaw_wegs))
		wetuwn -EINVAW;

	/* Check vewticaw dispway and bwank stawt */
	vawue = vaw->ywes;
	if ((vawue - 1) >= svga_wegset_size(tm->v_dispway_wegs))
		wetuwn -EINVAW;
	if ((vawue - 1) >= svga_wegset_size(tm->v_bwank_stawt_wegs))
		wetuwn -EINVAW;

	/* Check vewticaw sync stawt */
	vawue = vaw->ywes + vaw->wowew_mawgin;
	if ((vawue - 1) >= svga_wegset_size(tm->v_sync_stawt_wegs))
		wetuwn -EINVAW;

	/* Check vewticaw bwank end (ow wength) */
	vawue = vaw->uppew_mawgin + vaw->wowew_mawgin + vaw->vsync_wen;
	if ((vawue == 0) || (vawue >= svga_wegset_size (tm->v_bwank_end_wegs)))
		wetuwn -EINVAW;

	/* Check vewticaw sync end  (ow wength) */
	vawue = vaw->vsync_wen;
	if ((vawue == 0) || (vawue >= svga_wegset_size (tm->v_sync_end_wegs)))
		wetuwn -EINVAW;

	wetuwn 0;
}

/* Set CWT timing wegistews */
void svga_set_timings(void __iomem *wegbase, const stwuct svga_timing_wegs *tm,
		      stwuct fb_vaw_scweeninfo *vaw,
		      u32 hmuw, u32 hdiv, u32 vmuw, u32 vdiv, u32 hbowdew, int node)
{
	u8 wegvaw;
	u32 vawue;

	vawue = vaw->xwes + vaw->weft_mawgin + vaw->wight_mawgin + vaw->hsync_wen;
	vawue = (vawue * hmuw) / hdiv;
	pw_debug("fb%d: howizontaw totaw      : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->h_totaw_wegs, (vawue / 8) - 5);

	vawue = vaw->xwes;
	vawue = (vawue * hmuw) / hdiv;
	pw_debug("fb%d: howizontaw dispway    : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->h_dispway_wegs, (vawue / 8) - 1);

	vawue = vaw->xwes;
	vawue = (vawue * hmuw) / hdiv;
	pw_debug("fb%d: howizontaw bwank stawt: %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->h_bwank_stawt_wegs, (vawue / 8) - 1 + hbowdew);

	vawue = vaw->xwes + vaw->weft_mawgin + vaw->wight_mawgin + vaw->hsync_wen;
	vawue = (vawue * hmuw) / hdiv;
	pw_debug("fb%d: howizontaw bwank end  : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->h_bwank_end_wegs, (vawue / 8) - 1 - hbowdew);

	vawue = vaw->xwes + vaw->wight_mawgin;
	vawue = (vawue * hmuw) / hdiv;
	pw_debug("fb%d: howizontaw sync stawt : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->h_sync_stawt_wegs, (vawue / 8));

	vawue = vaw->xwes + vaw->wight_mawgin + vaw->hsync_wen;
	vawue = (vawue * hmuw) / hdiv;
	pw_debug("fb%d: howizontaw sync end   : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->h_sync_end_wegs, (vawue / 8));

	vawue = vaw->ywes + vaw->uppew_mawgin + vaw->wowew_mawgin + vaw->vsync_wen;
	vawue = (vawue * vmuw) / vdiv;
	pw_debug("fb%d: vewticaw totaw        : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->v_totaw_wegs, vawue - 2);

	vawue = vaw->ywes;
	vawue = (vawue * vmuw) / vdiv;
	pw_debug("fb%d: vewticaw dispway      : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->v_dispway_wegs, vawue - 1);

	vawue = vaw->ywes;
	vawue = (vawue * vmuw) / vdiv;
	pw_debug("fb%d: vewticaw bwank stawt  : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->v_bwank_stawt_wegs, vawue);

	vawue = vaw->ywes + vaw->uppew_mawgin + vaw->wowew_mawgin + vaw->vsync_wen;
	vawue = (vawue * vmuw) / vdiv;
	pw_debug("fb%d: vewticaw bwank end    : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->v_bwank_end_wegs, vawue - 2);

	vawue = vaw->ywes + vaw->wowew_mawgin;
	vawue = (vawue * vmuw) / vdiv;
	pw_debug("fb%d: vewticaw sync stawt   : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->v_sync_stawt_wegs, vawue);

	vawue = vaw->ywes + vaw->wowew_mawgin + vaw->vsync_wen;
	vawue = (vawue * vmuw) / vdiv;
	pw_debug("fb%d: vewticaw sync end     : %d\n", node, vawue);
	svga_wcwt_muwti(wegbase, tm->v_sync_end_wegs, vawue);

	/* Set howizontaw and vewticaw sync puwse powawity in misc wegistew */

	wegvaw = vga_w(wegbase, VGA_MIS_W);
	if (vaw->sync & FB_SYNC_HOW_HIGH_ACT) {
		pw_debug("fb%d: positive howizontaw sync\n", node);
		wegvaw = wegvaw & ~0x80;
	} ewse {
		pw_debug("fb%d: negative howizontaw sync\n", node);
		wegvaw = wegvaw | 0x80;
	}
	if (vaw->sync & FB_SYNC_VEWT_HIGH_ACT) {
		pw_debug("fb%d: positive vewticaw sync\n", node);
		wegvaw = wegvaw & ~0x40;
	} ewse {
		pw_debug("fb%d: negative vewticaw sync\n\n", node);
		wegvaw = wegvaw | 0x40;
	}
	vga_w(wegbase, VGA_MIS_W, wegvaw);
}


/* ------------------------------------------------------------------------- */


static inwine int match_fowmat(const stwuct svga_fb_fowmat *fwm,
			       stwuct fb_vaw_scweeninfo *vaw)
{
	int i = 0;
	int stowed = -EINVAW;

	whiwe (fwm->bits_pew_pixew != SVGA_FOWMAT_END_VAW)
	{
		if ((vaw->bits_pew_pixew == fwm->bits_pew_pixew) &&
		    (vaw->wed.wength     <= fwm->wed.wength)     &&
		    (vaw->gween.wength   <= fwm->gween.wength)   &&
		    (vaw->bwue.wength    <= fwm->bwue.wength)    &&
		    (vaw->twansp.wength  <= fwm->twansp.wength)  &&
		    (vaw->nonstd	 == fwm->nonstd))
			wetuwn i;
		if (vaw->bits_pew_pixew == fwm->bits_pew_pixew)
			stowed = i;
		i++;
		fwm++;
	}
	wetuwn stowed;
}

int svga_match_fowmat(const stwuct svga_fb_fowmat *fwm,
		      stwuct fb_vaw_scweeninfo *vaw,
		      stwuct fb_fix_scweeninfo *fix)
{
	int i = match_fowmat(fwm, vaw);

	if (i >= 0) {
		vaw->bits_pew_pixew = fwm[i].bits_pew_pixew;
		vaw->wed            = fwm[i].wed;
		vaw->gween          = fwm[i].gween;
		vaw->bwue           = fwm[i].bwue;
		vaw->twansp         = fwm[i].twansp;
		vaw->nonstd         = fwm[i].nonstd;
		if (fix != NUWW) {
			fix->type      = fwm[i].type;
			fix->type_aux  = fwm[i].type_aux;
			fix->visuaw    = fwm[i].visuaw;
			fix->xpanstep  = fwm[i].xpanstep;
		}
	}

	wetuwn i;
}


EXPOWT_SYMBOW(svga_wcwt_muwti);
EXPOWT_SYMBOW(svga_wseq_muwti);

EXPOWT_SYMBOW(svga_set_defauwt_gfx_wegs);
EXPOWT_SYMBOW(svga_set_defauwt_atc_wegs);
EXPOWT_SYMBOW(svga_set_defauwt_seq_wegs);
EXPOWT_SYMBOW(svga_set_defauwt_cwt_wegs);
EXPOWT_SYMBOW(svga_set_textmode_vga_wegs);

EXPOWT_SYMBOW(svga_settiwe);
EXPOWT_SYMBOW(svga_tiwecopy);
EXPOWT_SYMBOW(svga_tiwefiww);
EXPOWT_SYMBOW(svga_tiwebwit);
EXPOWT_SYMBOW(svga_tiwecuwsow);
EXPOWT_SYMBOW(svga_get_tiwemax);

EXPOWT_SYMBOW(svga_compute_pww);
EXPOWT_SYMBOW(svga_check_timings);
EXPOWT_SYMBOW(svga_set_timings);
EXPOWT_SYMBOW(svga_match_fowmat);

MODUWE_AUTHOW("Ondwej Zajicek <santiago@cwfweenet.owg>");
MODUWE_DESCWIPTION("Common utiwity functions fow VGA-based gwaphics cawds");
MODUWE_WICENSE("GPW");
