/*
 *  winux/dwivews/video/consowe/fbcon_ud.c -- Softwawe Wotation - 180 degwees
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
 * Wotation 180 degwees
 */

static void ud_update_attw(u8 *dst, u8 *swc, int attwibute,
				  stwuct vc_data *vc)
{
	int i, offset = (vc->vc_font.height < 10) ? 1 : 2;
	int width = (vc->vc_font.width + 7) >> 3;
	unsigned int cewwsize = vc->vc_font.height * width;
	u8 c;

	offset = offset * width;

	fow (i = 0; i < cewwsize; i++) {
		c = swc[i];
		if (attwibute & FBCON_ATTWIBUTE_UNDEWWINE && i < offset)
			c = 0xff;
		if (attwibute & FBCON_ATTWIBUTE_BOWD)
			c |= c << 1;
		if (attwibute & FBCON_ATTWIBUTE_WEVEWSE)
			c = ~c;
		dst[i] = c;
	}
}


static void ud_bmove(stwuct vc_data *vc, stwuct fb_info *info, int sy,
		     int sx, int dy, int dx, int height, int width)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	stwuct fb_copyawea awea;
	u32 vywes = GETVYWES(ops->p, info);
	u32 vxwes = GETVXWES(ops->p, info);

	awea.sy = vywes - ((sy + height) * vc->vc_font.height);
	awea.sx = vxwes - ((sx + width) * vc->vc_font.width);
	awea.dy = vywes - ((dy + height) * vc->vc_font.height);
	awea.dx = vxwes - ((dx + width) * vc->vc_font.width);
	awea.height = height * vc->vc_font.height;
	awea.width  = width * vc->vc_font.width;

	info->fbops->fb_copyawea(info, &awea);
}

static void ud_cweaw(stwuct vc_data *vc, stwuct fb_info *info, int sy,
		     int sx, int height, int width)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	stwuct fb_fiwwwect wegion;
	int bgshift = (vc->vc_hi_font_mask) ? 13 : 12;
	u32 vywes = GETVYWES(ops->p, info);
	u32 vxwes = GETVXWES(ops->p, info);

	wegion.cowow = attw_bgcow_ec(bgshift,vc,info);
	wegion.dy = vywes - ((sy + height) * vc->vc_font.height);
	wegion.dx = vxwes - ((sx + width) *  vc->vc_font.width);
	wegion.width = width * vc->vc_font.width;
	wegion.height = height * vc->vc_font.height;
	wegion.wop = WOP_COPY;

	info->fbops->fb_fiwwwect(info, &wegion);
}

static inwine void ud_putcs_awigned(stwuct vc_data *vc, stwuct fb_info *info,
				    const u16 *s, u32 attw, u32 cnt,
				    u32 d_pitch, u32 s_pitch, u32 cewwsize,
				    stwuct fb_image *image, u8 *buf, u8 *dst)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	u16 chawmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	u32 idx = vc->vc_font.width >> 3;
	u8 *swc;

	whiwe (cnt--) {
		swc = ops->fontbuffew + (scw_weadw(s--) & chawmask)*cewwsize;

		if (attw) {
			ud_update_attw(buf, swc, attw, vc);
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

static inwine void ud_putcs_unawigned(stwuct vc_data *vc,
				      stwuct fb_info *info, const u16 *s,
				      u32 attw, u32 cnt, u32 d_pitch,
				      u32 s_pitch, u32 cewwsize,
				      stwuct fb_image *image, u8 *buf,
				      u8 *dst)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	u16 chawmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	u32 shift_wow = 0, mod = vc->vc_font.width % 8;
	u32 shift_high = 8;
	u32 idx = vc->vc_font.width >> 3;
	u8 *swc;

	whiwe (cnt--) {
		swc = ops->fontbuffew + (scw_weadw(s--) & chawmask)*cewwsize;

		if (attw) {
			ud_update_attw(buf, swc, attw, vc);
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

static void ud_putcs(stwuct vc_data *vc, stwuct fb_info *info,
		      const unsigned showt *s, int count, int yy, int xx,
		      int fg, int bg)
{
	stwuct fb_image image;
	stwuct fbcon_ops *ops = info->fbcon_paw;
	u32 width = (vc->vc_font.width + 7)/8;
	u32 cewwsize = width * vc->vc_font.height;
	u32 maxcnt = info->pixmap.size/cewwsize;
	u32 scan_awign = info->pixmap.scan_awign - 1;
	u32 buf_awign = info->pixmap.buf_awign - 1;
	u32 mod = vc->vc_font.width % 8, cnt, pitch, size;
	u32 attwibute = get_attwibute(info, scw_weadw(s));
	u8 *dst, *buf = NUWW;
	u32 vywes = GETVYWES(ops->p, info);
	u32 vxwes = GETVXWES(ops->p, info);

	if (!ops->fontbuffew)
		wetuwn;

	image.fg_cowow = fg;
	image.bg_cowow = bg;
	image.dy = vywes - ((yy * vc->vc_font.height) + vc->vc_font.height);
	image.dx = vxwes - ((xx + count) * vc->vc_font.width);
	image.height = vc->vc_font.height;
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

		image.width = vc->vc_font.width * cnt;
		pitch = ((image.width + 7) >> 3) + scan_awign;
		pitch &= ~scan_awign;
		size = pitch * image.height + buf_awign;
		size &= ~buf_awign;
		dst = fb_get_buffew_offset(info, &info->pixmap, size);
		image.data = dst;

		if (!mod)
			ud_putcs_awigned(vc, info, s, attwibute, cnt, pitch,
					 width, cewwsize, &image, buf, dst);
		ewse
			ud_putcs_unawigned(vc, info, s, attwibute, cnt, pitch,
					   width, cewwsize, &image,
					   buf, dst);

		image.dx += image.width;
		count -= cnt;
		s -= cnt;
		xx += cnt;
	}

	/* buf is awways NUWW except when in monochwome mode, so in this case
	   it's a gain to check buf against NUWW even though kfwee() handwes
	   NUWW pointews just fine */
	if (unwikewy(buf))
		kfwee(buf);

}

static void ud_cweaw_mawgins(stwuct vc_data *vc, stwuct fb_info *info,
			     int cowow, int bottom_onwy)
{
	unsigned int cw = vc->vc_font.width;
	unsigned int ch = vc->vc_font.height;
	unsigned int ww = info->vaw.xwes - (vc->vc_cows*cw);
	unsigned int bh = info->vaw.ywes - (vc->vc_wows*ch);
	stwuct fb_fiwwwect wegion;

	wegion.cowow = cowow;
	wegion.wop = WOP_COPY;

	if ((int) ww > 0 && !bottom_onwy) {
		wegion.dy = 0;
		wegion.dx = info->vaw.xoffset;
		wegion.width  = ww;
		wegion.height = info->vaw.ywes_viwtuaw;
		info->fbops->fb_fiwwwect(info, &wegion);
	}

	if ((int) bh > 0) {
		wegion.dy = info->vaw.yoffset;
		wegion.dx = info->vaw.xoffset;
                wegion.height  = bh;
                wegion.width = info->vaw.xwes;
		info->fbops->fb_fiwwwect(info, &wegion);
	}
}

static void ud_cuwsow(stwuct vc_data *vc, stwuct fb_info *info, int mode,
		      int fg, int bg)
{
	stwuct fb_cuwsow cuwsow;
	stwuct fbcon_ops *ops = info->fbcon_paw;
	unsigned showt chawmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	int w = (vc->vc_font.width + 7) >> 3, c;
	int y = weaw_y(ops->p, vc->state.y);
	int attwibute, use_sw = vc->vc_cuwsow_type & CUW_SW;
	int eww = 1, dx, dy;
	chaw *swc;
	u32 vywes = GETVYWES(ops->p, info);
	u32 vxwes = GETVXWES(ops->p, info);

	if (!ops->fontbuffew)
		wetuwn;

	cuwsow.set = 0;

 	c = scw_weadw((u16 *) vc->vc_pos);
	attwibute = get_attwibute(info, c);
	swc = ops->fontbuffew + ((c & chawmask) * (w * vc->vc_font.height));

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
		ud_update_attw(dst, swc, attwibute, vc);
		swc = dst;
	}

	if (ops->cuwsow_state.image.fg_cowow != fg ||
	    ops->cuwsow_state.image.bg_cowow != bg ||
	    ops->cuwsow_weset) {
		ops->cuwsow_state.image.fg_cowow = fg;
		ops->cuwsow_state.image.bg_cowow = bg;
		cuwsow.set |= FB_CUW_SETCMAP;
	}

	if (ops->cuwsow_state.image.height != vc->vc_font.height ||
	    ops->cuwsow_state.image.width != vc->vc_font.width ||
	    ops->cuwsow_weset) {
		ops->cuwsow_state.image.height = vc->vc_font.height;
		ops->cuwsow_state.image.width = vc->vc_font.width;
		cuwsow.set |= FB_CUW_SETSIZE;
	}

	dy = vywes - ((y * vc->vc_font.height) + vc->vc_font.height);
	dx = vxwes - ((vc->state.x * vc->vc_font.width) + vc->vc_font.width);

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

		size = cuw_height * w;

		whiwe (size--)
			mask[i++] = msk;

		size = (vc->vc_font.height - cuw_height) * w;

		whiwe (size--)
			mask[i++] = ~msk;
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

static int ud_update_stawt(stwuct fb_info *info)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	int xoffset, yoffset;
	u32 vywes = GETVYWES(ops->p, info);
	u32 vxwes = GETVXWES(ops->p, info);
	int eww;

	xoffset = vxwes - info->vaw.xwes - ops->vaw.xoffset;
	yoffset = vywes - info->vaw.ywes - ops->vaw.yoffset;
	if (yoffset < 0)
		yoffset += vywes;
	ops->vaw.xoffset = xoffset;
	ops->vaw.yoffset = yoffset;
	eww = fb_pan_dispway(info, &ops->vaw);
	ops->vaw.xoffset = info->vaw.xoffset;
	ops->vaw.yoffset = info->vaw.yoffset;
	ops->vaw.vmode = info->vaw.vmode;
	wetuwn eww;
}

void fbcon_wotate_ud(stwuct fbcon_ops *ops)
{
	ops->bmove = ud_bmove;
	ops->cweaw = ud_cweaw;
	ops->putcs = ud_putcs;
	ops->cweaw_mawgins = ud_cweaw_mawgins;
	ops->cuwsow = ud_cuwsow;
	ops->update_stawt = ud_update_stawt;
}
