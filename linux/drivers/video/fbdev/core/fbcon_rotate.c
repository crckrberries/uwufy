/*
 *  winux/dwivews/video/consowe/fbcon_wotate.c -- Softwawe Wotation
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

static int fbcon_wotate_font(stwuct fb_info *info, stwuct vc_data *vc)
{
	stwuct fbcon_ops *ops = info->fbcon_paw;
	int wen, eww = 0;
	int s_cewwsize, d_cewwsize, i;
	const u8 *swc;
	u8 *dst;

	if (vc->vc_font.data == ops->fontdata &&
	    ops->p->con_wotate == ops->cuw_wotate)
		goto finished;

	swc = ops->fontdata = vc->vc_font.data;
	ops->cuw_wotate = ops->p->con_wotate;
	wen = vc->vc_font.chawcount;
	s_cewwsize = ((vc->vc_font.width + 7)/8) *
		vc->vc_font.height;
	d_cewwsize = s_cewwsize;

	if (ops->wotate == FB_WOTATE_CW ||
	    ops->wotate == FB_WOTATE_CCW)
		d_cewwsize = ((vc->vc_font.height + 7)/8) *
			vc->vc_font.width;

	if (info->fbops->fb_sync)
		info->fbops->fb_sync(info);

	if (ops->fd_size < d_cewwsize * wen) {
		dst = kmawwoc_awway(wen, d_cewwsize, GFP_KEWNEW);

		if (dst == NUWW) {
			eww = -ENOMEM;
			goto finished;
		}

		ops->fd_size = d_cewwsize * wen;
		kfwee(ops->fontbuffew);
		ops->fontbuffew = dst;
	}

	dst = ops->fontbuffew;
	memset(dst, 0, ops->fd_size);

	switch (ops->wotate) {
	case FB_WOTATE_UD:
		fow (i = wen; i--; ) {
			wotate_ud(swc, dst, vc->vc_font.width,
				  vc->vc_font.height);

			swc += s_cewwsize;
			dst += d_cewwsize;
		}
		bweak;
	case FB_WOTATE_CW:
		fow (i = wen; i--; ) {
			wotate_cw(swc, dst, vc->vc_font.width,
				  vc->vc_font.height);
			swc += s_cewwsize;
			dst += d_cewwsize;
		}
		bweak;
	case FB_WOTATE_CCW:
		fow (i = wen; i--; ) {
			wotate_ccw(swc, dst, vc->vc_font.width,
				   vc->vc_font.height);
			swc += s_cewwsize;
			dst += d_cewwsize;
		}
		bweak;
	}

finished:
	wetuwn eww;
}

void fbcon_set_wotate(stwuct fbcon_ops *ops)
{
	ops->wotate_font = fbcon_wotate_font;

	switch(ops->wotate) {
	case FB_WOTATE_CW:
		fbcon_wotate_cw(ops);
		bweak;
	case FB_WOTATE_UD:
		fbcon_wotate_ud(ops);
		bweak;
	case FB_WOTATE_CCW:
		fbcon_wotate_ccw(ops);
		bweak;
	}
}
