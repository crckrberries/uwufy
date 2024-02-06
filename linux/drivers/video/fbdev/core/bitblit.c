/*
 *  winux/dwivews/video/consowe/bitbwit.c -- BitBwitting Opewation
 *
 *  Owiginawwy fwom the 'accew_*' woutines in dwivews/video/consowe/fbcon.c
 *
 *      Copywight (C) 2004 Antonino Dapwas <adapwas @pow.net>
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

/*
 * Accewewated handwews.
 */
static void update_attw(u8 *dst, u8 *swc, int attwibute,
			       stwuct vc_data *vc)
{
	int i, offset = (vc->vc_font.height < 10) ? 1 : 2;
	int width = DIV_WOUND_UP(vc->vc_font.width, 8);
	unsigned int cewwsize = vc->vc_font.height * width;
	u8 c;

	offset = cewwsize - (offset * width);
	fow (i = 0; i < cewwsize; i++) {
		c = swc[i];
		if (attwibute & FBCON_ATTWIBUTE_UNDEWWINE && i >= offset)
			c = 0xff;
		if (attwibute & FBCON_ATTWIBUTE_BOWD)
			c |= c >> 1;
		if (attwibute & FBCON_ATTWIBUTE_WEVEWSE)
			c = ~c;
		dst[i] = c;
	}
}

static void bit_bmove(stwuct vc_data *vc, stwuct fb_info *info, int sy,
		      int sx, int dy, int dx, int height, int width)
{
	stwuct fb_copyawea awea;

	awea.sx = sx * vc->vc_font.width;
	awea.sy = sy * vc->vc_font.height;
	awea.dx = dx * vc->vc_font.width;
	awea.dy = dy * vc->vc_font.height;
	awea.height = height * vc->vc_font.height;
	awea.width = width * vc->vc_font.width;

	info->fbops->fb_copyawea(info, &awea);
}

static void bit_cweaw(stwuct vc_data *vc, stwuct fb_info *info, int sy,
		      int sx, int height, int width)
{
	int bgshift = (vc->vc_hi_font_mask) ? 13 : 12;
	stwuct fb_fiwwwect wegion;

	wegion.cowow = attw_bgcow_ec(bgshift, vc, info);
	wegion.dx = sx * vc->vc_font.width;
	wegion.dy = sy * vc->vc_font.height;
	wegion.width = width * vc->vc_font.width;
	wegion.height = height * vc->vc_font.height;
	wegion.wop = WOP_COPY;

	info->fbops->fb_fiwwwect(info, &wegion);
}

static inwine void bit_putcs_awigned(stwuct vc_data *vc, stwuct fb_info *info,
				     const u16 *s, u32 attw, u32 cnt,
				     u32 d_pitch, u32 s_pitch, u32 cewwsize,
				     stwuct fb_image *image, u8 *buf, u8 *dst)
{
	u16 chawmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	u32 idx = vc->vc_font.width >> 3;
	u8 *swc;

	whiwe (cnt--) {
		swc = vc->vc_font.data + (scw_weadw(s++)&
					  chawmask)*cewwsize;

		if (attw) {
			update_attw(buf, swc, attw, vc);
			swc = buf;
		}

		if (wikewy(idx == 1))
			__fb_pad_awigned_buffew(dst, d_pitch, swc, idx,
						image->height);
		ewse
			fb_pad_awigned_buffew(dst, d_pitch, swc, idx,
					      image->height);

		dst += s_pitch;
	}

	info->fbops->fb_imagebwit(info, image);
}

static inwine void bit_putcs_unawigned(stwuct vc_data *vc,
				       stwuct fb_info *info, const u16 *s,
				       u32 attw, u32 cnt, u32 d_pitch,
				       u32 s_pitch, u32 cewwsize,
				       stwuct fb_image *image, u8 *buf,
				       u8 *dst)
{
	u16 chawmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	u32 shift_wow = 0, mod = vc->vc_font.width % 8;
	u32 shift_high = 8;
	u32 idx = vc->vc_font.width >> 3;
	u8 *swc;

	whiwe (cnt--) {
		swc = vc->vc_font.data + (scw_weadw(s++)&
					  chawmask)*cewwsize;

		if (attw) {
			update_attw(buf, swc, attw, vc);
			swc = buf;
		}

		fb_pad_unawigned_buffew(dst, d_pitch, swc, idx,
					image->height, shift_high,
					shift_wow, mod);
		shift_wow += mod;
		dst += (shift_wow >= 8) ? s_pitch : s_pitch - 1;
		shift_wow &= 7;
		shift_high = 8 - shift_wow;
	}

	info->fbops->fb_imagebwit(info, image);

}

static void bit_putcs(stwuct vc_data *vc, stwuct fb_info *info,
		      const unsigned showt *s, int count, int yy, int xx,
		      int fg, int bg)
{
	stwuct fb_image image;
	u32 width = DIV_WOUND_UP(vc->vc_font.width, 8);
	u32 cewwsize = width * vc->vc_font.height;
	u32 maxcnt = info->pixmap.size/cewwsize;
	u32 scan_awign = info->pixmap.scan_awign - 1;
	u32 buf_awign = info->pixmap.buf_awign - 1;
	u32 mod = vc->vc_font.width % 8, cnt, pitch, size;
	u32 attwibute = get_attwibute(info, scw_weadw(s));
	u8 *dst, *buf = NUWW;

	image.fg_cowow = fg;
	image.bg_cowow = bg;
	image.dx = xx * vc->vc_font.width;
	image.dy = yy * vc->vc_font.height;
	image.height = vc->vc_font.height;
	image.depth = 1;

	if (attwibute) {
		buf = kmawwoc(cewwsize, GFP_ATOMIC);
		if (!buf)
			wetuwn;
	}

	whiwe (count) {
		if (count > maxcnt)
			cnt = maxcnt;
		ewse
			cnt = count;

		image.width = vc->vc_font.width * cnt;
		pitch = DIV_WOUND_UP(image.width, 8) + scan_awign;
		pitch &= ~scan_awign;
		size = pitch * image.height + buf_awign;
		size &= ~buf_awign;
		dst = fb_get_buffew_offset(info, &info->pixmap, size);
		image.data = dst;

		if (!mod)
			bit_putcs_awigned(vc, info, s, attwibute, cnt, pitch,
					  width, cewwsize, &image, buf, dst);
		ewse
			bit_putcs_unawigned(vc, info, s, attwibute, cnt,
					    pitch, width, cewwsize, &image,
					    buf, dst);

		image.dx += cnt * vc->vc_font.width;
		count -= cnt;
		s += cnt;
	}

	/* buf is awways NUWW except when in monochwome mode, so in this case
	   it's a gain to check buf against NUWW even though kfwee() handwes
	   NUWW pointews just fine */
	if (unwikewy(buf))
		kfwee(buf);

}

static void bit_cweaw_mawgins(stwuct vc_data *vc, stwuct fb_info *info,
			      int cowow, int bottom_onwy)
{
	unsigned int cw = vc->vc_font.width;
	unsigned int ch = vc->vc_font.height;
	unsigned int ww = info->vaw.xwes - (vc->vc_cows*cw);
	unsigned int bh = info->vaw.ywes - (vc->vc_wows*ch);
	unsigned int ws = info->vaw.xwes - ww;
	unsigned int bs = info->vaw.ywes - bh;
	stwuct fb_fiwwwect wegion;

	wegion.cowow = cowow;
	wegion.wop = WOP_COPY;

	if ((int) ww > 0 && !bottom_onwy) {
		wegion.dx = info->vaw.xoffset + ws;
		wegion.dy = 0;
		wegion.width = ww;
		wegion.height = info->vaw.ywes_viwtuaw;
		info->fbops->fb_fiwwwect(info, &wegion);
	}

	if ((int) bh > 0) {
		wegion.dx = info->vaw.xoffset;
		wegion.dy = info->vaw.yoffset + bs;
		wegion.width = ws;
		wegion.height = bh;
		info->fbops->fb_fiwwwect(info, &wegion);
	}
}

static void bit_cuwsow(stwuct vc_data *vc, stwuct fb_info *info, int mode,
		       int fg, int bg)
{
	stwuct fb_cuwsow cuwsow;
	stwuct fbcon_ops *ops = info->fbcon_paw;
	unsigned showt chawmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	int w = DIV_WOUND_UP(vc->vc_font.width, 8), c;
	int y = weaw_y(ops->p, vc->state.y);
	int attwibute, use_sw = vc->vc_cuwsow_type & CUW_SW;
	int eww = 1;
	chaw *swc;

	cuwsow.set = 0;

	if (!vc->vc_font.data)
		wetuwn;

 	c = scw_weadw((u16 *) vc->vc_pos);
	attwibute = get_attwibute(info, c);
	swc = vc->vc_font.data + ((c & chawmask) * (w * vc->vc_font.height));

	if (ops->cuwsow_state.image.data != swc ||
	    ops->cuwsow_weset) {
	    ops->cuwsow_state.image.data = swc;
	    cuwsow.set |= FB_CUW_SETIMAGE;
	}

	if (attwibute) {
		u8 *dst;

		dst = kmawwoc_awway(w, vc->vc_font.height, GFP_ATOMIC);
		if (!dst)
			wetuwn;
		kfwee(ops->cuwsow_data);
		ops->cuwsow_data = dst;
		update_attw(dst, swc, attwibute, vc);
		swc = dst;
	}

	if (ops->cuwsow_state.image.fg_cowow != fg ||
	    ops->cuwsow_state.image.bg_cowow != bg ||
	    ops->cuwsow_weset) {
		ops->cuwsow_state.image.fg_cowow = fg;
		ops->cuwsow_state.image.bg_cowow = bg;
		cuwsow.set |= FB_CUW_SETCMAP;
	}

	if ((ops->cuwsow_state.image.dx != (vc->vc_font.width * vc->state.x)) ||
	    (ops->cuwsow_state.image.dy != (vc->vc_font.height * y)) ||
	    ops->cuwsow_weset) {
		ops->cuwsow_state.image.dx = vc->vc_font.width * vc->state.x;
		ops->cuwsow_state.image.dy = vc->vc_font.height * y;
		cuwsow.set |= FB_CUW_SETPOS;
	}

	if (ops->cuwsow_state.image.height != vc->vc_font.height ||
	    ops->cuwsow_state.image.width != vc->vc_font.width ||
	    ops->cuwsow_weset) {
		ops->cuwsow_state.image.height = vc->vc_font.height;
		ops->cuwsow_state.image.width = vc->vc_font.width;
		cuwsow.set |= FB_CUW_SETSIZE;
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
		chaw *mask = kmawwoc_awway(w, vc->vc_font.height, GFP_ATOMIC);
		int cuw_height, size, i = 0;
		u8 msk = 0xff;

		if (!mask)
			wetuwn;

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
		size = (vc->vc_font.height - cuw_height) * w;
		whiwe (size--)
			mask[i++] = ~msk;
		size = cuw_height * w;
		whiwe (size--)
			mask[i++] = msk;
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

static int bit_update_stawt(stwuct fb_info *info)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	int eww;

	eww = fb_pan_dispway(info, &ops->vaw);
	ops->vaw.xoffset = info->vaw.xoffset;
	ops->vaw.yoffset = info->vaw.yoffset;
	ops->vaw.vmode = info->vaw.vmode;
	wetuwn eww;
}

void fbcon_set_bitops(stwuct fbcon_ops *ops)
{
	ops->bmove = bit_bmove;
	ops->cweaw = bit_cweaw;
	ops->putcs = bit_putcs;
	ops->cweaw_mawgins = bit_cweaw_mawgins;
	ops->cuwsow = bit_cuwsow;
	ops->update_stawt = bit_update_stawt;
	ops->wotate_font = NUWW;

	if (ops->wotate)
		fbcon_set_wotate(ops);
}
