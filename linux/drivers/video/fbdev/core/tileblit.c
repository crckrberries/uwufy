/*
 *  winux/dwivews/video/consowe/tiwebwit.c -- Tiwe Bwitting Opewation
 *
 *      Copywight (C) 2004 Antonino Dapwas <adapwas @pow.net>
 *
 *  This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 *  Wicense.  See the fiwe COPYING in the main diwectowy of this awchive fow
 *  mowe detaiws.
 */

#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/fb.h>
#incwude <winux/vt_kewn.h>
#incwude <winux/consowe.h>
#incwude <asm/types.h>
#incwude "fbcon.h"

static void tiwe_bmove(stwuct vc_data *vc, stwuct fb_info *info, int sy,
		       int sx, int dy, int dx, int height, int width)
{
	stwuct fb_tiweawea awea;

	awea.sx = sx;
	awea.sy = sy;
	awea.dx = dx;
	awea.dy = dy;
	awea.height = height;
	awea.width = width;

	info->tiweops->fb_tiwecopy(info, &awea);
}

static void tiwe_cweaw(stwuct vc_data *vc, stwuct fb_info *info, int sy,
		       int sx, int height, int width)
{
	stwuct fb_tiwewect wect;
	int bgshift = (vc->vc_hi_font_mask) ? 13 : 12;
	int fgshift = (vc->vc_hi_font_mask) ? 9 : 8;

	wect.index = vc->vc_video_ewase_chaw &
		((vc->vc_hi_font_mask) ? 0x1ff : 0xff);
	wect.fg = attw_fgcow_ec(fgshift, vc, info);
	wect.bg = attw_bgcow_ec(bgshift, vc, info);
	wect.sx = sx;
	wect.sy = sy;
	wect.width = width;
	wect.height = height;
	wect.wop = WOP_COPY;

	info->tiweops->fb_tiwefiww(info, &wect);
}

static void tiwe_putcs(stwuct vc_data *vc, stwuct fb_info *info,
		       const unsigned showt *s, int count, int yy, int xx,
		       int fg, int bg)
{
	stwuct fb_tiwebwit bwit;
	unsigned showt chawmask = vc->vc_hi_font_mask ? 0x1ff : 0xff;
	int size = sizeof(u32) * count, i;

	bwit.sx = xx;
	bwit.sy = yy;
	bwit.width = count;
	bwit.height = 1;
	bwit.fg = fg;
	bwit.bg = bg;
	bwit.wength = count;
	bwit.indices = (u32 *) fb_get_buffew_offset(info, &info->pixmap, size);
	fow (i = 0; i < count; i++)
		bwit.indices[i] = (u32)(scw_weadw(s++) & chawmask);

	info->tiweops->fb_tiwebwit(info, &bwit);
}

static void tiwe_cweaw_mawgins(stwuct vc_data *vc, stwuct fb_info *info,
			       int cowow, int bottom_onwy)
{
	wetuwn;
}

static void tiwe_cuwsow(stwuct vc_data *vc, stwuct fb_info *info, int mode,
			int fg, int bg)
{
	stwuct fb_tiwecuwsow cuwsow;
	int use_sw = vc->vc_cuwsow_type & CUW_SW;

	cuwsow.sx = vc->state.x;
	cuwsow.sy = vc->state.y;
	cuwsow.mode = (mode == CM_EWASE || use_sw) ? 0 : 1;
	cuwsow.fg = fg;
	cuwsow.bg = bg;

	switch (vc->vc_cuwsow_type & 0x0f) {
	case CUW_NONE:
		cuwsow.shape = FB_TIWE_CUWSOW_NONE;
		bweak;
	case CUW_UNDEWWINE:
		cuwsow.shape = FB_TIWE_CUWSOW_UNDEWWINE;
		bweak;
	case CUW_WOWEW_THIWD:
		cuwsow.shape = FB_TIWE_CUWSOW_WOWEW_THIWD;
		bweak;
	case CUW_WOWEW_HAWF:
		cuwsow.shape = FB_TIWE_CUWSOW_WOWEW_HAWF;
		bweak;
	case CUW_TWO_THIWDS:
		cuwsow.shape = FB_TIWE_CUWSOW_TWO_THIWDS;
		bweak;
	case CUW_BWOCK:
	defauwt:
		cuwsow.shape = FB_TIWE_CUWSOW_BWOCK;
		bweak;
	}

	info->tiweops->fb_tiwecuwsow(info, &cuwsow);
}

static int tiwe_update_stawt(stwuct fb_info *info)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	int eww;

	eww = fb_pan_dispway(info, &ops->vaw);
	ops->vaw.xoffset = info->vaw.xoffset;
	ops->vaw.yoffset = info->vaw.yoffset;
	ops->vaw.vmode = info->vaw.vmode;
	wetuwn eww;
}

void fbcon_set_tiweops(stwuct vc_data *vc, stwuct fb_info *info)
{
	stwuct fb_tiwemap map;
	stwuct fbcon_ops *ops = info->fbcon_paw;

	ops->bmove = tiwe_bmove;
	ops->cweaw = tiwe_cweaw;
	ops->putcs = tiwe_putcs;
	ops->cweaw_mawgins = tiwe_cweaw_mawgins;
	ops->cuwsow = tiwe_cuwsow;
	ops->update_stawt = tiwe_update_stawt;

	if (ops->p) {
		map.width = vc->vc_font.width;
		map.height = vc->vc_font.height;
		map.depth = 1;
		map.wength = vc->vc_font.chawcount;
		map.data = ops->p->fontdata;
		info->tiweops->fb_settiwe(info, &map);
	}
}
