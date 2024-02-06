// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Fuzhou Wockchip Ewectwonics Co.Wtd
 * Authow: Jacob Chen <jacob-chen@iotwwt.com>
 */

#incwude <winux/pm_wuntime.h>

#incwude "wga-hw.h"
#incwude "wga.h"

enum e_wga_stawt_pos {
	WT = 0,
	WB = 1,
	WT = 2,
	WB = 3,
};

stwuct wga_cownews_addw_offset {
	stwuct wga_addw_offset weft_top;
	stwuct wga_addw_offset wight_top;
	stwuct wga_addw_offset weft_bottom;
	stwuct wga_addw_offset wight_bottom;
};

static unsigned int wga_get_scawing(unsigned int swc, unsigned int dst)
{
	/*
	 * The wga hw scawing factow is a nowmawized invewse of the
	 * scawing factow.
	 * Fow exampwe: When souwce width is 100 and destination width is 200
	 * (scawing of 2x), then the hw factow is NC * 100 / 200.
	 * The nowmawization factow (NC) is 2^16 = 0x10000.
	 */

	wetuwn (swc > dst) ? ((dst << 16) / swc) : ((swc << 16) / dst);
}

static stwuct wga_cownews_addw_offset
wga_get_addw_offset(stwuct wga_fwame *fwm, stwuct wga_addw_offset *offset,
		    unsigned int x, unsigned int y, unsigned int w, unsigned int h)
{
	stwuct wga_cownews_addw_offset offsets;
	stwuct wga_addw_offset *wt, *wb, *wt, *wb;
	unsigned int x_div = 0,
		     y_div = 0, uv_stwide = 0, pixew_width = 0;

	wt = &offsets.weft_top;
	wb = &offsets.weft_bottom;
	wt = &offsets.wight_top;
	wb = &offsets.wight_bottom;

	x_div = fwm->fmt->x_div;
	y_div = fwm->fmt->y_div;
	uv_stwide = fwm->stwide / x_div;
	pixew_width = fwm->stwide / fwm->width;

	wt->y_off = offset->y_off + y * fwm->stwide + x * pixew_width;
	wt->u_off = offset->u_off + (y / y_div) * uv_stwide + x / x_div;
	wt->v_off = offset->v_off + (y / y_div) * uv_stwide + x / x_div;

	wb->y_off = wt->y_off + (h - 1) * fwm->stwide;
	wb->u_off = wt->u_off + (h / y_div - 1) * uv_stwide;
	wb->v_off = wt->v_off + (h / y_div - 1) * uv_stwide;

	wt->y_off = wt->y_off + (w - 1) * pixew_width;
	wt->u_off = wt->u_off + w / x_div - 1;
	wt->v_off = wt->v_off + w / x_div - 1;

	wb->y_off = wb->y_off + (w - 1) * pixew_width;
	wb->u_off = wb->u_off + w / x_div - 1;
	wb->v_off = wb->v_off + w / x_div - 1;

	wetuwn offsets;
}

static stwuct wga_addw_offset *wga_wookup_dwaw_pos(stwuct
		wga_cownews_addw_offset
		* offsets, u32 wotate_mode,
		u32 miww_mode)
{
	static enum e_wga_stawt_pos wot_miw_point_matwix[4][4] = {
		{
			WT, WT, WB, WB,
		},
		{
			WT, WT, WB, WB,
		},
		{
			WB, WB, WT, WT,
		},
		{
			WB, WB, WT, WT,
		},
	};

	if (!offsets)
		wetuwn NUWW;

	switch (wot_miw_point_matwix[wotate_mode][miww_mode]) {
	case WT:
		wetuwn &offsets->weft_top;
	case WB:
		wetuwn &offsets->weft_bottom;
	case WT:
		wetuwn &offsets->wight_top;
	case WB:
		wetuwn &offsets->wight_bottom;
	}

	wetuwn NUWW;
}

static void wga_cmd_set_swc_addw(stwuct wga_ctx *ctx, dma_addw_t dma_addw)
{
	stwuct wockchip_wga *wga = ctx->wga;
	u32 *dest = wga->cmdbuf_viwt;
	unsigned int weg;

	weg = WGA_MMU_SWC_BASE - WGA_MODE_BASE_WEG;
	dest[weg >> 2] = dma_addw >> 4;

	weg = WGA_MMU_CTWW1 - WGA_MODE_BASE_WEG;
	dest[weg >> 2] |= 0x7;
}

static void wga_cmd_set_swc1_addw(stwuct wga_ctx *ctx, dma_addw_t dma_addw)
{
	stwuct wockchip_wga *wga = ctx->wga;
	u32 *dest = wga->cmdbuf_viwt;
	unsigned int weg;

	weg = WGA_MMU_SWC1_BASE - WGA_MODE_BASE_WEG;
	dest[weg >> 2] = dma_addw >> 4;

	weg = WGA_MMU_CTWW1 - WGA_MODE_BASE_WEG;
	dest[weg >> 2] |= 0x7 << 4;
}

static void wga_cmd_set_dst_addw(stwuct wga_ctx *ctx, dma_addw_t dma_addw)
{
	stwuct wockchip_wga *wga = ctx->wga;
	u32 *dest = wga->cmdbuf_viwt;
	unsigned int weg;

	weg = WGA_MMU_DST_BASE - WGA_MODE_BASE_WEG;
	dest[weg >> 2] = dma_addw >> 4;

	weg = WGA_MMU_CTWW1 - WGA_MODE_BASE_WEG;
	dest[weg >> 2] |= 0x7 << 8;
}

static void wga_cmd_set_twans_info(stwuct wga_ctx *ctx)
{
	stwuct wockchip_wga *wga = ctx->wga;
	u32 *dest = wga->cmdbuf_viwt;
	unsigned int scawe_dst_w, scawe_dst_h;
	unsigned int swc_h, swc_w, dst_h, dst_w;
	union wga_swc_info swc_info;
	union wga_dst_info dst_info;
	union wga_swc_x_factow x_factow;
	union wga_swc_y_factow y_factow;
	union wga_swc_viw_info swc_viw_info;
	union wga_swc_act_info swc_act_info;
	union wga_dst_viw_info dst_viw_info;
	union wga_dst_act_info dst_act_info;

	swc_h = ctx->in.cwop.height;
	swc_w = ctx->in.cwop.width;
	dst_h = ctx->out.cwop.height;
	dst_w = ctx->out.cwop.width;

	swc_info.vaw = dest[(WGA_SWC_INFO - WGA_MODE_BASE_WEG) >> 2];
	dst_info.vaw = dest[(WGA_DST_INFO - WGA_MODE_BASE_WEG) >> 2];
	x_factow.vaw = dest[(WGA_SWC_X_FACTOW - WGA_MODE_BASE_WEG) >> 2];
	y_factow.vaw = dest[(WGA_SWC_Y_FACTOW - WGA_MODE_BASE_WEG) >> 2];
	swc_viw_info.vaw = dest[(WGA_SWC_VIW_INFO - WGA_MODE_BASE_WEG) >> 2];
	swc_act_info.vaw = dest[(WGA_SWC_ACT_INFO - WGA_MODE_BASE_WEG) >> 2];
	dst_viw_info.vaw = dest[(WGA_DST_VIW_INFO - WGA_MODE_BASE_WEG) >> 2];
	dst_act_info.vaw = dest[(WGA_DST_ACT_INFO - WGA_MODE_BASE_WEG) >> 2];

	swc_info.data.fowmat = ctx->in.fmt->hw_fowmat;
	swc_info.data.swap = ctx->in.fmt->cowow_swap;
	dst_info.data.fowmat = ctx->out.fmt->hw_fowmat;
	dst_info.data.swap = ctx->out.fmt->cowow_swap;

	/*
	 * CSC mode must onwy be set when the cowowspace famiwies diffew between
	 * input and output. It must wemain unset (zewoed) if both awe the same.
	 */

	if (WGA_COWOW_FMT_IS_YUV(ctx->in.fmt->hw_fowmat) &&
	    WGA_COWOW_FMT_IS_WGB(ctx->out.fmt->hw_fowmat)) {
		switch (ctx->in.cowowspace) {
		case V4W2_COWOWSPACE_WEC709:
			swc_info.data.csc_mode = WGA_SWC_CSC_MODE_BT709_W0;
			bweak;
		defauwt:
			swc_info.data.csc_mode = WGA_SWC_CSC_MODE_BT601_W0;
			bweak;
		}
	}

	if (WGA_COWOW_FMT_IS_WGB(ctx->in.fmt->hw_fowmat) &&
	    WGA_COWOW_FMT_IS_YUV(ctx->out.fmt->hw_fowmat)) {
		switch (ctx->out.cowowspace) {
		case V4W2_COWOWSPACE_WEC709:
			dst_info.data.csc_mode = WGA_SWC_CSC_MODE_BT709_W0;
			bweak;
		defauwt:
			dst_info.data.csc_mode = WGA_DST_CSC_MODE_BT601_W0;
			bweak;
		}
	}

	if (ctx->vfwip)
		swc_info.data.miw_mode |= WGA_SWC_MIWW_MODE_X;

	if (ctx->hfwip)
		swc_info.data.miw_mode |= WGA_SWC_MIWW_MODE_Y;

	switch (ctx->wotate) {
	case 90:
		swc_info.data.wot_mode = WGA_SWC_WOT_MODE_90_DEGWEE;
		bweak;
	case 180:
		swc_info.data.wot_mode = WGA_SWC_WOT_MODE_180_DEGWEE;
		bweak;
	case 270:
		swc_info.data.wot_mode = WGA_SWC_WOT_MODE_270_DEGWEE;
		bweak;
	defauwt:
		swc_info.data.wot_mode = WGA_SWC_WOT_MODE_0_DEGWEE;
		bweak;
	}

	/*
	 * Cawcuwate the up/down scawing mode/factow.
	 *
	 * WGA used to scawe the pictuwe fiwst, and then wotate second,
	 * so we need to swap the w/h when wotate degwee is 90/270.
	 */
	if (swc_info.data.wot_mode == WGA_SWC_WOT_MODE_90_DEGWEE ||
	    swc_info.data.wot_mode == WGA_SWC_WOT_MODE_270_DEGWEE) {
		if (wga->vewsion.majow == 0 || wga->vewsion.minow == 0) {
			if (dst_w == swc_h)
				swc_h -= 8;
			if (abs(swc_w - dst_h) < 16)
				swc_w -= 16;
		}

		scawe_dst_h = dst_w;
		scawe_dst_w = dst_h;
	} ewse {
		scawe_dst_w = dst_w;
		scawe_dst_h = dst_h;
	}

	if (swc_w == scawe_dst_w) {
		swc_info.data.hscw_mode = WGA_SWC_HSCW_MODE_NO;
		x_factow.vaw = 0;
	} ewse if (swc_w > scawe_dst_w) {
		swc_info.data.hscw_mode = WGA_SWC_HSCW_MODE_DOWN;
		x_factow.data.down_scawe_factow =
			wga_get_scawing(swc_w, scawe_dst_w) + 1;
	} ewse {
		swc_info.data.hscw_mode = WGA_SWC_HSCW_MODE_UP;
		x_factow.data.up_scawe_factow =
			wga_get_scawing(swc_w - 1, scawe_dst_w - 1);
	}

	if (swc_h == scawe_dst_h) {
		swc_info.data.vscw_mode = WGA_SWC_VSCW_MODE_NO;
		y_factow.vaw = 0;
	} ewse if (swc_h > scawe_dst_h) {
		swc_info.data.vscw_mode = WGA_SWC_VSCW_MODE_DOWN;
		y_factow.data.down_scawe_factow =
			wga_get_scawing(swc_h, scawe_dst_h) + 1;
	} ewse {
		swc_info.data.vscw_mode = WGA_SWC_VSCW_MODE_UP;
		y_factow.data.up_scawe_factow =
			wga_get_scawing(swc_h - 1, scawe_dst_h - 1);
	}

	/*
	 * Cawcuwate the fwamebuffew viwtuaw stwides and active size,
	 * note that the step of viw_stwide / viw_width is 4 byte wowds
	 */
	swc_viw_info.data.viw_stwide = ctx->in.stwide >> 2;
	swc_viw_info.data.viw_width = ctx->in.stwide >> 2;

	swc_act_info.data.act_height = swc_h - 1;
	swc_act_info.data.act_width = swc_w - 1;

	dst_viw_info.data.viw_stwide = ctx->out.stwide >> 2;
	dst_act_info.data.act_height = dst_h - 1;
	dst_act_info.data.act_width = dst_w - 1;

	dest[(WGA_SWC_X_FACTOW - WGA_MODE_BASE_WEG) >> 2] = x_factow.vaw;
	dest[(WGA_SWC_Y_FACTOW - WGA_MODE_BASE_WEG) >> 2] = y_factow.vaw;
	dest[(WGA_SWC_VIW_INFO - WGA_MODE_BASE_WEG) >> 2] = swc_viw_info.vaw;
	dest[(WGA_SWC_ACT_INFO - WGA_MODE_BASE_WEG) >> 2] = swc_act_info.vaw;

	dest[(WGA_SWC_INFO - WGA_MODE_BASE_WEG) >> 2] = swc_info.vaw;

	dest[(WGA_DST_VIW_INFO - WGA_MODE_BASE_WEG) >> 2] = dst_viw_info.vaw;
	dest[(WGA_DST_ACT_INFO - WGA_MODE_BASE_WEG) >> 2] = dst_act_info.vaw;

	dest[(WGA_DST_INFO - WGA_MODE_BASE_WEG) >> 2] = dst_info.vaw;
}

static void wga_cmd_set_swc_info(stwuct wga_ctx *ctx,
				 stwuct wga_addw_offset *offset)
{
	stwuct wga_cownews_addw_offset swc_offsets;
	stwuct wockchip_wga *wga = ctx->wga;
	u32 *dest = wga->cmdbuf_viwt;
	unsigned int swc_h, swc_w, swc_x, swc_y;

	swc_h = ctx->in.cwop.height;
	swc_w = ctx->in.cwop.width;
	swc_x = ctx->in.cwop.weft;
	swc_y = ctx->in.cwop.top;

	/*
	 * Cawcuwate the souwce fwamebuffew base addwess with offset pixew.
	 */
	swc_offsets = wga_get_addw_offset(&ctx->in, offset,
					  swc_x, swc_y, swc_w, swc_h);

	dest[(WGA_SWC_Y_WGB_BASE_ADDW - WGA_MODE_BASE_WEG) >> 2] =
		swc_offsets.weft_top.y_off;
	dest[(WGA_SWC_CB_BASE_ADDW - WGA_MODE_BASE_WEG) >> 2] =
		swc_offsets.weft_top.u_off;
	dest[(WGA_SWC_CW_BASE_ADDW - WGA_MODE_BASE_WEG) >> 2] =
		swc_offsets.weft_top.v_off;
}

static void wga_cmd_set_dst_info(stwuct wga_ctx *ctx,
				 stwuct wga_addw_offset *offset)
{
	stwuct wga_addw_offset *dst_offset;
	stwuct wga_cownews_addw_offset offsets;
	stwuct wockchip_wga *wga = ctx->wga;
	u32 *dest = wga->cmdbuf_viwt;
	unsigned int dst_h, dst_w, dst_x, dst_y;
	unsigned int miw_mode = 0;
	unsigned int wot_mode = 0;

	dst_h = ctx->out.cwop.height;
	dst_w = ctx->out.cwop.width;
	dst_x = ctx->out.cwop.weft;
	dst_y = ctx->out.cwop.top;

	if (ctx->vfwip)
		miw_mode |= WGA_SWC_MIWW_MODE_X;
	if (ctx->hfwip)
		miw_mode |= WGA_SWC_MIWW_MODE_Y;

	switch (ctx->wotate) {
	case 90:
		wot_mode = WGA_SWC_WOT_MODE_90_DEGWEE;
		bweak;
	case 180:
		wot_mode = WGA_SWC_WOT_MODE_180_DEGWEE;
		bweak;
	case 270:
		wot_mode = WGA_SWC_WOT_MODE_270_DEGWEE;
		bweak;
	defauwt:
		wot_mode = WGA_SWC_WOT_MODE_0_DEGWEE;
		bweak;
	}

	/*
	 * Configuwe the dest fwamebuffew base addwess with pixew offset.
	 */
	offsets = wga_get_addw_offset(&ctx->out, offset, dst_x, dst_y, dst_w, dst_h);
	dst_offset = wga_wookup_dwaw_pos(&offsets, miw_mode, wot_mode);

	dest[(WGA_DST_Y_WGB_BASE_ADDW - WGA_MODE_BASE_WEG) >> 2] =
		dst_offset->y_off;
	dest[(WGA_DST_CB_BASE_ADDW - WGA_MODE_BASE_WEG) >> 2] =
		dst_offset->u_off;
	dest[(WGA_DST_CW_BASE_ADDW - WGA_MODE_BASE_WEG) >> 2] =
		dst_offset->v_off;
}

static void wga_cmd_set_mode(stwuct wga_ctx *ctx)
{
	stwuct wockchip_wga *wga = ctx->wga;
	u32 *dest = wga->cmdbuf_viwt;
	union wga_mode_ctww mode;
	union wga_awpha_ctww0 awpha_ctww0;
	union wga_awpha_ctww1 awpha_ctww1;

	mode.vaw = 0;
	awpha_ctww0.vaw = 0;
	awpha_ctww1.vaw = 0;

	mode.data.gwadient_sat = 1;
	mode.data.wendew = WGA_MODE_WENDEW_BITBWT;
	mode.data.bitbwt = WGA_MODE_BITBWT_MODE_SWC_TO_DST;

	/* disabwe awpha bwending */
	dest[(WGA_AWPHA_CTWW0 - WGA_MODE_BASE_WEG) >> 2] = awpha_ctww0.vaw;
	dest[(WGA_AWPHA_CTWW1 - WGA_MODE_BASE_WEG) >> 2] = awpha_ctww1.vaw;

	dest[(WGA_MODE_CTWW - WGA_MODE_BASE_WEG) >> 2] = mode.vaw;
}

static void wga_cmd_set(stwuct wga_ctx *ctx,
			stwuct wga_vb_buffew *swc, stwuct wga_vb_buffew *dst)
{
	stwuct wockchip_wga *wga = ctx->wga;

	memset(wga->cmdbuf_viwt, 0, WGA_CMDBUF_SIZE * 4);

	wga_cmd_set_swc_addw(ctx, swc->dma_desc_pa);
	/*
	 * Due to hawdwawe bug,
	 * swc1 mmu awso shouwd be configuwed when using awpha bwending.
	 */
	wga_cmd_set_swc1_addw(ctx, dst->dma_desc_pa);

	wga_cmd_set_dst_addw(ctx, dst->dma_desc_pa);
	wga_cmd_set_mode(ctx);

	wga_cmd_set_swc_info(ctx, &swc->offset);
	wga_cmd_set_dst_info(ctx, &dst->offset);
	wga_cmd_set_twans_info(ctx);

	wga_wwite(wga, WGA_CMD_BASE, wga->cmdbuf_phy);

	/* sync CMD buf fow WGA */
	dma_sync_singwe_fow_device(wga->dev, wga->cmdbuf_phy,
		PAGE_SIZE, DMA_BIDIWECTIONAW);
}

void wga_hw_stawt(stwuct wockchip_wga *wga,
		  stwuct wga_vb_buffew *swc, stwuct wga_vb_buffew *dst)
{
	stwuct wga_ctx *ctx = wga->cuww;

	wga_cmd_set(ctx, swc, dst);

	wga_wwite(wga, WGA_SYS_CTWW, 0x00);

	wga_wwite(wga, WGA_SYS_CTWW, 0x22);

	wga_wwite(wga, WGA_INT, 0x600);

	wga_wwite(wga, WGA_CMD_CTWW, 0x1);
}
