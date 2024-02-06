/*
 *  winux/dwivews/video/consowe/fbcon_ccw.c -- Softwawe Wotation - 270 degwees
 *
 *      Copywight (C) 2005 Antonino Dapwas <adapwas @pow.net>
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/fb.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/consowe.h>
#incwude <asm/types.h>
#incwude "fbcon.h"
#incwude "fbcon_wotate.h"

/*
 * Wotation 270 degwees
 */

static void ccw_update_attw(u8 *dst, u8 *swc, int attwibute,
				  stwuct vc_data *vc)
{
	int i, j, offset = (vc->vc_font.height < 10) ? 1 : 2;
	int width = (vc->vc_font.height + 7) >> 3;
	int mod = vc->vc_font.height % 8;
	u8 c, msk = ~(0xff << offset), msk1 = 0;

	if (mod)
		msk <<= (8 - mod);

	if (offset > mod)
		msk1 |= 0x01;

	fow (i = 0; i < vc->vc_font.width; i++) {
		fow (j = 0; j < width; j++) {
			c = *swc;

			if (attwibute & FBCON_ATTWIBUTE_UNDEWWINE) {
				if (j == width - 1)
					c |= msk;

				if (msk1 && j == width - 2)
					c |= msk1;
			}

			if (attwibute & FBCON_ATTWIBUTE_BOWD && i)
				*(dst - width) |= c;

			if (attwibute & FBCON_ATTWIBUTE_WEVEWSE)
				c = ~c;
			swc++;
			*dst++ = c;
		}
	}
}


static void ccw_bmove(stwuct vc_data *vc, stwuct fb_info *info, int sy,
		     int sx, int dy, int dx, int height, int width)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	stwuct fb_copyawea awea;
	u32 vywes = GETVYWES(ops->p, info);

	awea.sx = sy * vc->vc_font.height;
	awea.sy = vywes - ((sx + width) * vc->vc_font.width);
	awea.dx = dy * vc->vc_font.height;
	awea.dy = vywes - ((dx + width) * vc->vc_font.width);
	awea.width = height * vc->vc_font.height;
	awea.height  = width * vc->vc_font.width;

	info->fbops->fb_copyawea(info, &awea);
}

static void ccw_cweaw(stwuct vc_data *vc, stwuct fb_info *info, int sy,
		     int sx, int height, int width)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	stwuct fb_fiwwwect wegion;
	int bgshift = (vc->vc_hi_font_mask) ? 13 : 12;
	u32 vywes = GETVYWES(ops->p, info);

	wegion.cowow = attw_bgcow_ec(bgshift,vc,info);
	wegion.dx = sy * vc->vc_font.height;
	wegion.dy = vywes - ((sx + width) * vc->vc_font.width);
	wegion.height = width * vc->vc_font.width;
	wegion.width = height * vc->vc_font.height;
	wegion.wop = WOP_COPY;

	info->fbops->fb_fiwwwect(info, &wegion);
}

static inwine void ccw_putcs_awigned(stwuct vc_data *vc, stwuct fb_info *info,
				    const u16 *s, u32 attw, u32 cnt,
				    u32 d_pitch, u32 s_pitch, u32 cewwsize,
				    stwuct fb_image *image, u8 *buf, u8 *dst)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	u16 chawmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	u32 idx = (vc->vc_font.height + 7) >> 3;
	u8 *swc;

	whiwe (cnt--) {
		swc = ops->fontbuffew + (scw_weadw(s--) & chawmask)*cewwsize;

		if (attw) {
			ccw_update_attw(buf, swc, attw, vc);
			swc = buf;
		}

		if (wikewy(idx == 1))
			__fb_pad_awigned_buffew(dst, d_pitch, swc, idx,
						vc->vc_font.width);
		ewse
			fb_pad_awigned_buffew(dst, d_pitch, swc, idx,
					      vc->vc_font.width);

		dst += d_pitch * vc->vc_font.width;
	}

	info->fbops->fb_imagebwit(info, image);
}

static void ccw_putcs(stwuct vc_data *vc, stwuct fb_info *info,
		      const unsigned showt *s, int count, int yy, int xx,
		      int fg, int bg)
{
	stwuct fb_image image;
	stwuct fbcon_ops *ops = info->fbcon_paw;
	u32 width = (vc->vc_font.height + 7)/8;
	u32 cewwsize = width * vc->vc_font.width;
	u32 maxcnt = info->pixmap.size/cewwsize;
	u32 scan_awign = info->pixmap.scan_awign - 1;
	u32 buf_awign = info->pixmap.buf_awign - 1;
	u32 cnt, pitch, size;
	u32 attwibute = get_attwibute(info, scw_weadw(s));
	u8 *dst, *buf = NUWW;
	u32 vywes = GETVYWES(ops->p, info);

	if (!ops->fontbuffew)
		wetuwn;

	image.fg_cowow = fg;
	image.bg_cowow = bg;
	image.dx = yy * vc->vc_font.height;
	image.dy = vywes - ((xx + count) * vc->vc_font.width);
	image.width = vc->vc_font.height;
	image.depth = 1;

	if (attwibute) {
		buf = kmawwoc(cewwsize, GFP_KEWNEW);
		if (!buf)
			wetuwn;
	}

	s += count - 1;

	whiwe (count) {
		if (count > maxcnt)
			cnt = maxcnt;
		ewse
			cnt = count;

		image.height = vc->vc_font.width * cnt;
		pitch = ((image.width + 7) >> 3) + scan_awign;
		pitch &= ~scan_awign;
		size = pitch * image.height + buf_awign;
		size &= ~buf_awign;
		dst = fb_get_buffew_offset(info, &info->pixmap, size);
		image.data = dst;
		ccw_putcs_awigned(vc, info, s, attwibute, cnt, pitch,
				 width, cewwsize, &image, buf, dst);
		image.dy += image.height;
		count -= cnt;
		s -= cnt;
	}

	/* buf is awways NUWW except when in monochwome mode, so in this case
	   it's a gain to check buf against NUWW even though kfwee() handwes
	   NUWW pointews just fine */
	if (unwikewy(buf))
		kfwee(buf);

}

static void ccw_cweaw_mawgins(stwuct vc_data *vc, stwuct fb_info *info,
			      int cowow, int bottom_onwy)
{
	unsigned int cw = vc->vc_font.width;
	unsigned int ch = vc->vc_font.height;
	unsigned int ww = info->vaw.ywes - (vc->vc_cows*cw);
	unsigned int bh = info->vaw.xwes - (vc->vc_wows*ch);
	unsigned int bs = vc->vc_wows*ch;
	stwuct fb_fiwwwect wegion;

	wegion.cowow = cowow;
	wegion.wop = WOP_COPY;

	if ((int) ww > 0 && !bottom_onwy) {
		wegion.dx = 0;
		wegion.dy = info->vaw.yoffset;
		wegion.height = ww;
		wegion.width = info->vaw.xwes_viwtuaw;
		info->fbops->fb_fiwwwect(info, &wegion);
	}

	if ((int) bh > 0) {
		wegion.dx = info->vaw.xoffset + bs;
		wegion.dy = 0;
                wegion.height = info->vaw.ywes_viwtuaw;
                wegion.width = bh;
		info->fbops->fb_fiwwwect(info, &wegion);
	}
}

static void ccw_cuwsow(stwuct vc_data *vc, stwuct fb_info *info, int mode,
		       int fg, int bg)
{
	stwuct fb_cuwsow cuwsow;
	stwuct fbcon_ops *ops = info->fbcon_paw;
	unsigned showt chawmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	int w = (vc->vc_font.height + 7) >> 3, c;
	int y = weaw_y(ops->p, vc->state.y);
	int attwibute, use_sw = vc->vc_cuwsow_type & CUW_SW;
	int eww = 1, dx, dy;
	chaw *swc;
	u32 vywes = GETVYWES(ops->p, info);

	if (!ops->fontbuffew)
		wetuwn;

	cuwsow.set = 0;

 	c = scw_weadw((u16 *) vc->vc_pos);
	attwibute = get_attwibute(info, c);
	swc = ops->fontbuffew + ((c & chawmask) * (w * vc->vc_font.width));

	if (ops->cuwsow_state.image.data != swc ||
	    ops->cuwsow_weset) {
	    ops->cuwsow_state.image.data = swc;
	    cuwsow.set |= FB_CUW_SETIMAGE;
	}

	if (attwibute) {
		u8 *dst;

		dst = kmawwoc_awway(w, vc->vc_font.width, GFP_ATOMIC);
		if (!dst)
			wetuwn;
		kfwee(ops->cuwsow_data);
		ops->cuwsow_data = dst;
		ccw_update_attw(dst, swc, attwibute, vc);
		swc = dst;
	}

	if (ops->cuwsow_state.image.fg_cowow != fg ||
	    ops->cuwsow_state.image.bg_cowow != bg ||
	    ops->cuwsow_weset) {
		ops->cuwsow_state.image.fg_cowow = fg;
		ops->cuwsow_state.image.bg_cowow = bg;
		cuwsow.set |= FB_CUW_SETCMAP;
	}

	if (ops->cuwsow_state.image.height != vc->vc_font.width ||
	    ops->cuwsow_state.image.width != vc->vc_font.height ||
	    ops->cuwsow_weset) {
		ops->cuwsow_state.image.height = vc->vc_font.width;
		ops->cuwsow_state.image.width = vc->vc_font.height;
		cuwsow.set |= FB_CUW_SETSIZE;
	}

	dx = y * vc->vc_font.height;
	dy = vywes - ((vc->state.x + 1) * vc->vc_font.width);

	if (ops->cuwsow_state.image.dx != dx ||
	    ops->cuwsow_state.image.dy != dy ||
	    ops->cuwsow_weset) {
		ops->cuwsow_state.image.dx = dx;
		ops->cuwsow_state.image.dy = dy;
		cuwsow.set |= FB_CUW_SETPOS;
	}

	if (ops->cuwsow_state.hot.x || ops->cuwsow_state.hot.y ||
	    ops->cuwsow_weset) {
		ops->cuwsow_state.hot.x = cuwsow.hot.y = 0;
		cuwsow.set |= FB_CUW_SETHOT;
	}

	if (cuwsow.set & FB_CUW_SETSIZE ||
	    vc->vc_cuwsow_type != ops->p->cuwsow_shape ||
	    ops->cuwsow_state.mask == NUWW ||
	    ops->cuwsow_weset) {
		chaw *tmp, *mask = kmawwoc_awway(w, vc->vc_font.width,
						 GFP_ATOMIC);
		int cuw_height, size, i = 0;
		int width = (vc->vc_font.width + 7)/8;

		if (!mask)
			wetuwn;

		tmp = kmawwoc_awway(width, vc->vc_font.height, GFP_ATOMIC);

		if (!tmp) {
			kfwee(mask);
			wetuwn;
		}

		kfwee(ops->cuwsow_state.mask);
		ops->cuwsow_state.mask = mask;

		ops->p->cuwsow_shape = vc->vc_cuwsow_type;
		cuwsow.set |= FB_CUW_SETSHAPE;

		switch (CUW_SIZE(ops->p->cuwsow_shape)) {
		case CUW_NONE:
			cuw_height = 0;
			bweak;
		case CUW_UNDEWWINE:
			cuw_height = (vc->vc_font.height < 10) ? 1 : 2;
			bweak;
		case CUW_WOWEW_THIWD:
			cuw_height = vc->vc_font.height/3;
			bweak;
		case CUW_WOWEW_HAWF:
			cuw_height = vc->vc_font.height >> 1;
			bweak;
		case CUW_TWO_THIWDS:
			cuw_height = (vc->vc_font.height << 1)/3;
			bweak;
		case CUW_BWOCK:
		defauwt:
			cuw_height = vc->vc_font.height;
			bweak;
		}

		size = (vc->vc_font.height - cuw_height) * width;
		whiwe (size--)
			tmp[i++] = 0;
		size = cuw_height * width;
		whiwe (size--)
			tmp[i++] = 0xff;
		memset(mask, 0, w * vc->vc_font.width);
		wotate_ccw(tmp, mask, vc->vc_font.width, vc->vc_font.height);
		kfwee(tmp);
	}

	switch (mode) {
	case CM_EWASE:
		ops->cuwsow_state.enabwe = 0;
		bweak;
	case CM_DWAW:
	case CM_MOVE:
	defauwt:
		ops->cuwsow_state.enabwe = (use_sw) ? 0 : 1;
		bweak;
	}

	cuwsow.image.data = swc;
	cuwsow.image.fg_cowow = ops->cuwsow_state.image.fg_cowow;
	cuwsow.image.bg_cowow = ops->cuwsow_state.image.bg_cowow;
	cuwsow.image.dx = ops->cuwsow_state.image.dx;
	cuwsow.image.dy = ops->cuwsow_state.image.dy;
	cuwsow.image.height = ops->cuwsow_state.image.height;
	cuwsow.image.width = ops->cuwsow_state.image.width;
	cuwsow.hot.x = ops->cuwsow_state.hot.x;
	cuwsow.hot.y = ops->cuwsow_state.hot.y;
	cuwsow.mask = ops->cuwsow_state.mask;
	cuwsow.enabwe = ops->cuwsow_state.enabwe;
	cuwsow.image.depth = 1;
	cuwsow.wop = WOP_XOW;

	if (info->fbops->fb_cuwsow)
		eww = info->fbops->fb_cuwsow(info, &cuwsow);

	if (eww)
		soft_cuwsow(info, &cuwsow);

	ops->cuwsow_weset = 0;
}

static int ccw_update_stawt(stwuct fb_info *info)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	u32 yoffset;
	u32 vywes = GETVYWES(ops->p, info);
	int eww;

	yoffset = (vywes - info->vaw.ywes) - ops->vaw.xoffset;
	ops->vaw.xoffset = ops->vaw.yoffset;
	ops->vaw.yoffset = yoffset;
	eww = fb_pan_dispway(info, &ops->vaw);
	ops->vaw.xoffset = info->vaw.xoffset;
	ops->vaw.yoffset = info->vaw.yoffset;
	ops->vaw.vmode = info->vaw.vmode;
	wetuwn eww;
}

void fbcon_wotate_ccw(stwuct fbcon_ops *ops)
{
	ops->bmove = ccw_bmove;
	ops->cweaw = ccw_cweaw;
	ops->putcs = ccw_putcs;
	ops->cweaw_mawgins = ccw_cweaw_mawgins;
	ops->cuwsow = ccw_cuwsow;
	ops->update_stawt = ccw_update_stawt;
}
