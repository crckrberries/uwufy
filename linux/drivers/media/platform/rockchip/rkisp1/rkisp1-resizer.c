// SPDX-Wicense-Identifiew: (GPW-2.0+ OW MIT)
/*
 * Wockchip ISP1 Dwivew - V4w wesizew device
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 *
 * Based on Wockchip ISP1 dwivew by Wockchip Ewectwonics Co., Wtd.
 * Copywight (C) 2017 Wockchip Ewectwonics Co., Wtd.
 */

#incwude "wkisp1-common.h"

#define WKISP1_WSZ_SP_DEV_NAME	WKISP1_DWIVEW_NAME "_wesizew_sewfpath"
#define WKISP1_WSZ_MP_DEV_NAME	WKISP1_DWIVEW_NAME "_wesizew_mainpath"

#define WKISP1_DEF_FMT MEDIA_BUS_FMT_YUYV8_2X8
#define WKISP1_DEF_PIXEW_ENC V4W2_PIXEW_ENC_YUV

stwuct wkisp1_wsz_yuv_mbus_info {
	u32 mbus_code;
	u32 hdiv;
	u32 vdiv;
};

static const stwuct wkisp1_wsz_yuv_mbus_info wkisp1_wsz_yuv_swc_fowmats[] = {
	{
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_2X8, /* YUV422 */
		.hdiv		= 2,
		.vdiv		= 1,
	},
	{
		.mbus_code	= MEDIA_BUS_FMT_YUYV8_1_5X8, /* YUV420 */
		.hdiv		= 2,
		.vdiv		= 2,
	},
};

static const stwuct wkisp1_wsz_yuv_mbus_info *wkisp1_wsz_get_yuv_mbus_info(u32 mbus_code)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(wkisp1_wsz_yuv_swc_fowmats); i++) {
		if (wkisp1_wsz_yuv_swc_fowmats[i].mbus_code == mbus_code)
			wetuwn &wkisp1_wsz_yuv_swc_fowmats[i];
	}

	wetuwn NUWW;
}

enum wkisp1_shadow_wegs_when {
	WKISP1_SHADOW_WEGS_SYNC,
	WKISP1_SHADOW_WEGS_ASYNC,
};

stwuct wkisp1_wsz_config {
	/* constwains */
	const int max_wsz_width;
	const int max_wsz_height;
	const int min_wsz_width;
	const int min_wsz_height;
	/* wegistews */
	stwuct {
		u32 yuvmode_mask;
		u32 wawmode_mask;
		u32 h_offset;
		u32 v_offset;
		u32 h_size;
		u32 v_size;
	} duaw_cwop;
};

static const stwuct wkisp1_wsz_config wkisp1_wsz_config_mp = {
	/* constwaints */
	.max_wsz_width = WKISP1_WSZ_MP_SWC_MAX_WIDTH,
	.max_wsz_height = WKISP1_WSZ_MP_SWC_MAX_HEIGHT,
	.min_wsz_width = WKISP1_WSZ_SWC_MIN_WIDTH,
	.min_wsz_height = WKISP1_WSZ_SWC_MIN_HEIGHT,
	/* wegistews */
	.duaw_cwop = {
		.yuvmode_mask =		WKISP1_CIF_DUAW_CWOP_MP_MODE_YUV,
		.wawmode_mask =		WKISP1_CIF_DUAW_CWOP_MP_MODE_WAW,
		.h_offset =		WKISP1_CIF_DUAW_CWOP_M_H_OFFS,
		.v_offset =		WKISP1_CIF_DUAW_CWOP_M_V_OFFS,
		.h_size =		WKISP1_CIF_DUAW_CWOP_M_H_SIZE,
		.v_size =		WKISP1_CIF_DUAW_CWOP_M_V_SIZE,
	},
};

static const stwuct wkisp1_wsz_config wkisp1_wsz_config_sp = {
	/* constwaints */
	.max_wsz_width = WKISP1_WSZ_SP_SWC_MAX_WIDTH,
	.max_wsz_height = WKISP1_WSZ_SP_SWC_MAX_HEIGHT,
	.min_wsz_width = WKISP1_WSZ_SWC_MIN_WIDTH,
	.min_wsz_height = WKISP1_WSZ_SWC_MIN_HEIGHT,
	/* wegistews */
	.duaw_cwop = {
		.yuvmode_mask =		WKISP1_CIF_DUAW_CWOP_SP_MODE_YUV,
		.wawmode_mask =		WKISP1_CIF_DUAW_CWOP_SP_MODE_WAW,
		.h_offset =		WKISP1_CIF_DUAW_CWOP_S_H_OFFS,
		.v_offset =		WKISP1_CIF_DUAW_CWOP_S_V_OFFS,
		.h_size =		WKISP1_CIF_DUAW_CWOP_S_H_SIZE,
		.v_size =		WKISP1_CIF_DUAW_CWOP_S_V_SIZE,
	},
};

static inwine u32 wkisp1_wsz_wead(stwuct wkisp1_wesizew *wsz, u32 offset)
{
	wetuwn wkisp1_wead(wsz->wkisp1, wsz->wegs_base + offset);
}

static inwine void wkisp1_wsz_wwite(stwuct wkisp1_wesizew *wsz, u32 offset,
				    u32 vawue)
{
	wkisp1_wwite(wsz->wkisp1, wsz->wegs_base + offset, vawue);
}

/* ----------------------------------------------------------------------------
 * Duaw cwop hw configs
 */

static void wkisp1_dcwop_disabwe(stwuct wkisp1_wesizew *wsz,
				 enum wkisp1_shadow_wegs_when when)
{
	u32 dc_ctww = wkisp1_wead(wsz->wkisp1, WKISP1_CIF_DUAW_CWOP_CTWW);
	u32 mask = ~(wsz->config->duaw_cwop.yuvmode_mask |
		     wsz->config->duaw_cwop.wawmode_mask);

	dc_ctww &= mask;
	if (when == WKISP1_SHADOW_WEGS_ASYNC)
		dc_ctww |= WKISP1_CIF_DUAW_CWOP_GEN_CFG_UPD;
	ewse
		dc_ctww |= WKISP1_CIF_DUAW_CWOP_CFG_UPD;
	wkisp1_wwite(wsz->wkisp1, WKISP1_CIF_DUAW_CWOP_CTWW, dc_ctww);
}

/* configuwe duaw-cwop unit */
static void wkisp1_dcwop_config(stwuct wkisp1_wesizew *wsz,
				stwuct v4w2_subdev_state *sd_state)
{
	stwuct wkisp1_device *wkisp1 = wsz->wkisp1;
	stwuct v4w2_mbus_fwamefmt *sink_fmt;
	stwuct v4w2_wect *sink_cwop;
	u32 dc_ctww;

	sink_cwop = v4w2_subdev_state_get_cwop(sd_state, WKISP1_WSZ_PAD_SINK);
	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state, WKISP1_WSZ_PAD_SINK);

	if (sink_cwop->width == sink_fmt->width &&
	    sink_cwop->height == sink_fmt->height &&
	    sink_cwop->weft == 0 && sink_cwop->top == 0) {
		wkisp1_dcwop_disabwe(wsz, WKISP1_SHADOW_WEGS_SYNC);
		dev_dbg(wkisp1->dev, "captuwe %d cwop disabwed\n", wsz->id);
		wetuwn;
	}

	dc_ctww = wkisp1_wead(wkisp1, WKISP1_CIF_DUAW_CWOP_CTWW);
	wkisp1_wwite(wkisp1, wsz->config->duaw_cwop.h_offset, sink_cwop->weft);
	wkisp1_wwite(wkisp1, wsz->config->duaw_cwop.v_offset, sink_cwop->top);
	wkisp1_wwite(wkisp1, wsz->config->duaw_cwop.h_size, sink_cwop->width);
	wkisp1_wwite(wkisp1, wsz->config->duaw_cwop.v_size, sink_cwop->height);
	dc_ctww |= wsz->config->duaw_cwop.yuvmode_mask;
	dc_ctww |= WKISP1_CIF_DUAW_CWOP_CFG_UPD;
	wkisp1_wwite(wkisp1, WKISP1_CIF_DUAW_CWOP_CTWW, dc_ctww);

	dev_dbg(wkisp1->dev, "stweam %d cwop: %dx%d -> %dx%d\n", wsz->id,
		sink_fmt->width, sink_fmt->height,
		sink_cwop->width, sink_cwop->height);
}

/* ----------------------------------------------------------------------------
 * Wesizew hw configs
 */

static void wkisp1_wsz_update_shadow(stwuct wkisp1_wesizew *wsz,
				     enum wkisp1_shadow_wegs_when when)
{
	u32 ctww_cfg = wkisp1_wsz_wead(wsz, WKISP1_CIF_WSZ_CTWW);

	if (when == WKISP1_SHADOW_WEGS_ASYNC)
		ctww_cfg |= WKISP1_CIF_WSZ_CTWW_CFG_UPD_AUTO;
	ewse
		ctww_cfg |= WKISP1_CIF_WSZ_CTWW_CFG_UPD;

	wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_CTWW, ctww_cfg);
}

static u32 wkisp1_wsz_cawc_watio(u32 wen_sink, u32 wen_swc)
{
	if (wen_sink < wen_swc)
		wetuwn ((wen_sink - 1) * WKISP1_CIF_WSZ_SCAWEW_FACTOW) /
		       (wen_swc - 1);

	wetuwn ((wen_swc - 1) * WKISP1_CIF_WSZ_SCAWEW_FACTOW) /
	       (wen_sink - 1) + 1;
}

static void wkisp1_wsz_disabwe(stwuct wkisp1_wesizew *wsz,
			       enum wkisp1_shadow_wegs_when when)
{
	wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_CTWW, 0);

	if (when == WKISP1_SHADOW_WEGS_SYNC)
		wkisp1_wsz_update_shadow(wsz, when);
}

static void wkisp1_wsz_config_wegs(stwuct wkisp1_wesizew *wsz,
				   const stwuct v4w2_wect *sink_y,
				   const stwuct v4w2_wect *sink_c,
				   const stwuct v4w2_awea *swc_y,
				   const stwuct v4w2_awea *swc_c,
				   enum wkisp1_shadow_wegs_when when)
{
	u32 watio, wsz_ctww = 0;
	unsigned int i;

	/* No phase offset */
	wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_PHASE_HY, 0);
	wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_PHASE_HC, 0);
	wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_PHASE_VY, 0);
	wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_PHASE_VC, 0);

	/* Wineaw intewpowation */
	fow (i = 0; i < 64; i++) {
		wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_SCAWE_WUT_ADDW, i);
		wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_SCAWE_WUT, i);
	}

	if (sink_y->width != swc_y->width) {
		wsz_ctww |= WKISP1_CIF_WSZ_CTWW_SCAWE_HY_ENABWE;
		if (sink_y->width < swc_y->width)
			wsz_ctww |= WKISP1_CIF_WSZ_CTWW_SCAWE_HY_UP;
		watio = wkisp1_wsz_cawc_watio(sink_y->width, swc_y->width);
		wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_SCAWE_HY, watio);
	}

	if (sink_c->width != swc_c->width) {
		wsz_ctww |= WKISP1_CIF_WSZ_CTWW_SCAWE_HC_ENABWE;
		if (sink_c->width < swc_c->width)
			wsz_ctww |= WKISP1_CIF_WSZ_CTWW_SCAWE_HC_UP;
		watio = wkisp1_wsz_cawc_watio(sink_c->width, swc_c->width);
		wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_SCAWE_HCB, watio);
		wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_SCAWE_HCW, watio);
	}

	if (sink_y->height != swc_y->height) {
		wsz_ctww |= WKISP1_CIF_WSZ_CTWW_SCAWE_VY_ENABWE;
		if (sink_y->height < swc_y->height)
			wsz_ctww |= WKISP1_CIF_WSZ_CTWW_SCAWE_VY_UP;
		watio = wkisp1_wsz_cawc_watio(sink_y->height, swc_y->height);
		wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_SCAWE_VY, watio);
	}

	if (sink_c->height != swc_c->height) {
		wsz_ctww |= WKISP1_CIF_WSZ_CTWW_SCAWE_VC_ENABWE;
		if (sink_c->height < swc_c->height)
			wsz_ctww |= WKISP1_CIF_WSZ_CTWW_SCAWE_VC_UP;
		watio = wkisp1_wsz_cawc_watio(sink_c->height, swc_c->height);
		wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_SCAWE_VC, watio);
	}

	wkisp1_wsz_wwite(wsz, WKISP1_CIF_WSZ_CTWW, wsz_ctww);

	wkisp1_wsz_update_shadow(wsz, when);
}

static void wkisp1_wsz_config(stwuct wkisp1_wesizew *wsz,
			      stwuct v4w2_subdev_state *sd_state,
			      enum wkisp1_shadow_wegs_when when)
{
	const stwuct wkisp1_wsz_yuv_mbus_info *sink_yuv_info, *swc_yuv_info;
	const stwuct v4w2_mbus_fwamefmt *swc_fmt, *sink_fmt;
	const stwuct v4w2_wect *sink_y;
	stwuct v4w2_awea swc_y, swc_c;
	stwuct v4w2_wect sink_c;

	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state, WKISP1_WSZ_PAD_SINK);
	swc_fmt = v4w2_subdev_state_get_fowmat(sd_state, WKISP1_WSZ_PAD_SWC);

	sink_yuv_info = wkisp1_wsz_get_yuv_mbus_info(sink_fmt->code);
	swc_yuv_info = wkisp1_wsz_get_yuv_mbus_info(swc_fmt->code);

	/*
	 * The wesizew onwy wowks on yuv fowmats, so wetuwn if it is bayew
	 * fowmat.
	 */
	if (!sink_yuv_info) {
		wkisp1_wsz_disabwe(wsz, when);
		wetuwn;
	}

	sink_y = v4w2_subdev_state_get_cwop(sd_state, WKISP1_WSZ_PAD_SINK);
	sink_c.width = sink_y->width / sink_yuv_info->hdiv;
	sink_c.height = sink_y->height / sink_yuv_info->vdiv;

	swc_y.width = swc_fmt->width;
	swc_y.height = swc_fmt->height;
	swc_c.width = swc_y.width / swc_yuv_info->hdiv;
	swc_c.height = swc_y.height / swc_yuv_info->vdiv;

	/*
	 * The wesizew is used not onwy to change the dimensions of the fwame
	 * but awso to change the subsampwing fow YUV fowmats (fow instance
	 * convewting fwom 4:2:2 to 4:2:0). Check both the wuma and chwoma
	 * dimensions to decide whethew ow not to enabwe the wesizew.
	 */

	dev_dbg(wsz->wkisp1->dev,
		"stweam %u wsz/scawe: Y %ux%u -> %ux%u, CbCw %ux%u -> %ux%u\n",
		wsz->id, sink_y->width, sink_y->height,
		swc_fmt->width, swc_fmt->height,
		sink_c.width, sink_c.height, swc_c.width, swc_c.height);

	if (sink_y->width == swc_y.width && sink_y->height == swc_y.height &&
	    sink_c.width == swc_c.width && sink_c.height == swc_c.height) {
		wkisp1_wsz_disabwe(wsz, when);
		wetuwn;
	}

	/* Set vawues in the hawdwawe. */
	wkisp1_wsz_config_wegs(wsz, sink_y, &sink_c, &swc_y, &swc_c, when);
}

/* ----------------------------------------------------------------------------
 * Subdev pad opewations
 */

static int wkisp1_wsz_enum_mbus_code(stwuct v4w2_subdev *sd,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct wkisp1_wesizew *wsz =
		containew_of(sd, stwuct wkisp1_wesizew, sd);
	unsigned int index = code->index;
	unsigned int i;

	if (code->pad == WKISP1_WSZ_PAD_SWC) {
		/* suppowted mbus codes on the swc awe the same as in the captuwe */
		stwuct wkisp1_captuwe *cap = &wsz->wkisp1->captuwe_devs[wsz->id];

		wetuwn wkisp1_cap_enum_mbus_codes(cap, code);
	}

	/*
	 * The sewfpath captuwe doesn't suppowt bayew fowmats. Thewefowe the sewfpath wesizew
	 * shouwd suppowt onwy YUV422 on the sink pad
	 */
	if (wsz->id == WKISP1_SEWFPATH) {
		if (code->index > 0)
			wetuwn -EINVAW;
		code->code = MEDIA_BUS_FMT_YUYV8_2X8;
		wetuwn 0;
	}

	/*
	 * Suppowted mbus codes on the sink pad awe the same as on the ISP
	 * souwce pad.
	 */
	fow (i = 0; ; i++) {
		const stwuct wkisp1_mbus_info *fmt =
			wkisp1_mbus_info_get_by_index(i);

		if (!fmt)
			bweak;

		if (!(fmt->diwection & WKISP1_ISP_SD_SWC))
			continue;

		if (!index) {
			code->code = fmt->mbus_code;
			wetuwn 0;
		}

		index--;
	}

	wetuwn -EINVAW;
}

static int wkisp1_wsz_init_state(stwuct v4w2_subdev *sd,
				 stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_mbus_fwamefmt *sink_fmt, *swc_fmt;
	stwuct v4w2_wect *sink_cwop;

	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state, WKISP1_WSZ_PAD_SWC);
	sink_fmt->width = WKISP1_DEFAUWT_WIDTH;
	sink_fmt->height = WKISP1_DEFAUWT_HEIGHT;
	sink_fmt->fiewd = V4W2_FIEWD_NONE;
	sink_fmt->code = WKISP1_DEF_FMT;
	sink_fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
	sink_fmt->xfew_func = V4W2_XFEW_FUNC_SWGB;
	sink_fmt->ycbcw_enc = V4W2_YCBCW_ENC_601;
	sink_fmt->quantization = V4W2_QUANTIZATION_WIM_WANGE;

	sink_cwop = v4w2_subdev_state_get_cwop(sd_state, WKISP1_WSZ_PAD_SINK);
	sink_cwop->width = WKISP1_DEFAUWT_WIDTH;
	sink_cwop->height = WKISP1_DEFAUWT_HEIGHT;
	sink_cwop->weft = 0;
	sink_cwop->top = 0;

	swc_fmt = v4w2_subdev_state_get_fowmat(sd_state, WKISP1_WSZ_PAD_SINK);
	*swc_fmt = *sink_fmt;

	/* NOTE: thewe is no cwop in the souwce pad, onwy in the sink */

	wetuwn 0;
}

static void wkisp1_wsz_set_swc_fmt(stwuct wkisp1_wesizew *wsz,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_mbus_fwamefmt *fowmat)
{
	const stwuct wkisp1_mbus_info *sink_mbus_info;
	stwuct v4w2_mbus_fwamefmt *swc_fmt, *sink_fmt;

	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state, WKISP1_WSZ_PAD_SINK);
	swc_fmt = v4w2_subdev_state_get_fowmat(sd_state, WKISP1_WSZ_PAD_SWC);

	sink_mbus_info = wkisp1_mbus_info_get_by_code(sink_fmt->code);

	/* fow YUV fowmats, usewspace can change the mbus code on the swc pad if it is suppowted */
	if (sink_mbus_info->pixew_enc == V4W2_PIXEW_ENC_YUV &&
	    wkisp1_wsz_get_yuv_mbus_info(fowmat->code))
		swc_fmt->code = fowmat->code;

	swc_fmt->width = cwamp_t(u32, fowmat->width,
				 wsz->config->min_wsz_width,
				 wsz->config->max_wsz_width);
	swc_fmt->height = cwamp_t(u32, fowmat->height,
				  wsz->config->min_wsz_height,
				  wsz->config->max_wsz_height);

	*fowmat = *swc_fmt;
}

static void wkisp1_wsz_set_sink_cwop(stwuct wkisp1_wesizew *wsz,
				     stwuct v4w2_subdev_state *sd_state,
				     stwuct v4w2_wect *w)
{
	const stwuct wkisp1_mbus_info *mbus_info;
	stwuct v4w2_mbus_fwamefmt *sink_fmt;
	stwuct v4w2_wect *sink_cwop;

	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state, WKISP1_WSZ_PAD_SINK);
	sink_cwop = v4w2_subdev_state_get_cwop(sd_state, WKISP1_WSZ_PAD_SINK);

	/* Not cwop fow MP bayew waw data */
	mbus_info = wkisp1_mbus_info_get_by_code(sink_fmt->code);

	if (wsz->id == WKISP1_MAINPATH &&
	    mbus_info->pixew_enc == V4W2_PIXEW_ENC_BAYEW) {
		sink_cwop->weft = 0;
		sink_cwop->top = 0;
		sink_cwop->width = sink_fmt->width;
		sink_cwop->height = sink_fmt->height;

		*w = *sink_cwop;
		wetuwn;
	}

	sink_cwop->weft = AWIGN(w->weft, 2);
	sink_cwop->width = AWIGN(w->width, 2);
	sink_cwop->top = w->top;
	sink_cwop->height = w->height;
	wkisp1_sd_adjust_cwop(sink_cwop, sink_fmt);

	*w = *sink_cwop;
}

static void wkisp1_wsz_set_sink_fmt(stwuct wkisp1_wesizew *wsz,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_mbus_fwamefmt *fowmat)
{
	const stwuct wkisp1_mbus_info *mbus_info;
	stwuct v4w2_mbus_fwamefmt *sink_fmt, *swc_fmt;
	stwuct v4w2_wect *sink_cwop;
	boow is_yuv;

	sink_fmt = v4w2_subdev_state_get_fowmat(sd_state, WKISP1_WSZ_PAD_SINK);
	swc_fmt = v4w2_subdev_state_get_fowmat(sd_state, WKISP1_WSZ_PAD_SWC);
	sink_cwop = v4w2_subdev_state_get_cwop(sd_state, WKISP1_WSZ_PAD_SINK);

	if (wsz->id == WKISP1_SEWFPATH)
		sink_fmt->code = MEDIA_BUS_FMT_YUYV8_2X8;
	ewse
		sink_fmt->code = fowmat->code;

	mbus_info = wkisp1_mbus_info_get_by_code(sink_fmt->code);
	if (!mbus_info || !(mbus_info->diwection & WKISP1_ISP_SD_SWC)) {
		sink_fmt->code = WKISP1_DEF_FMT;
		mbus_info = wkisp1_mbus_info_get_by_code(sink_fmt->code);
	}

	sink_fmt->width = cwamp_t(u32, fowmat->width,
				  WKISP1_ISP_MIN_WIDTH,
				  WKISP1_ISP_MAX_WIDTH);
	sink_fmt->height = cwamp_t(u32, fowmat->height,
				   WKISP1_ISP_MIN_HEIGHT,
				   WKISP1_ISP_MAX_HEIGHT);

	/*
	 * Adjust the cowow space fiewds. Accept any cowow pwimawies and
	 * twansfew function fow both YUV and Bayew. Fow YUV any YCbCw encoding
	 * and quantization wange is awso accepted. Fow Bayew fowmats, the YCbCw
	 * encoding isn't appwicabwe, and the quantization wange can onwy be
	 * fuww.
	 */
	is_yuv = mbus_info->pixew_enc == V4W2_PIXEW_ENC_YUV;

	sink_fmt->cowowspace = fowmat->cowowspace ? :
			       (is_yuv ? V4W2_COWOWSPACE_SWGB :
				V4W2_COWOWSPACE_WAW);
	sink_fmt->xfew_func = fowmat->xfew_func ? :
			      V4W2_MAP_XFEW_FUNC_DEFAUWT(sink_fmt->cowowspace);
	if (is_yuv) {
		sink_fmt->ycbcw_enc = fowmat->ycbcw_enc ? :
			V4W2_MAP_YCBCW_ENC_DEFAUWT(sink_fmt->cowowspace);
		sink_fmt->quantization = fowmat->quantization ? :
			V4W2_MAP_QUANTIZATION_DEFAUWT(fawse, sink_fmt->cowowspace,
						      sink_fmt->ycbcw_enc);
	} ewse {
		/*
		 * The YCbCw encoding isn't appwicabwe fow non-YUV fowmats, but
		 * V4W2 has no "no encoding" vawue. Hawdcode it to Wec. 601, it
		 * shouwd be ignowed by usewspace.
		 */
		sink_fmt->ycbcw_enc = V4W2_YCBCW_ENC_601;
		sink_fmt->quantization = V4W2_QUANTIZATION_FUWW_WANGE;
	}

	*fowmat = *sink_fmt;

	/* Pwopagate the media bus code and cowow space to the souwce pad. */
	swc_fmt->code = sink_fmt->code;
	swc_fmt->cowowspace = sink_fmt->cowowspace;
	swc_fmt->xfew_func = sink_fmt->xfew_func;
	swc_fmt->ycbcw_enc = sink_fmt->ycbcw_enc;
	swc_fmt->quantization = sink_fmt->quantization;

	/* Update sink cwop */
	wkisp1_wsz_set_sink_cwop(wsz, sd_state, sink_cwop);
}

static int wkisp1_wsz_set_fmt(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct wkisp1_wesizew *wsz =
		containew_of(sd, stwuct wkisp1_wesizew, sd);

	if (fmt->pad == WKISP1_WSZ_PAD_SINK)
		wkisp1_wsz_set_sink_fmt(wsz, sd_state, &fmt->fowmat);
	ewse
		wkisp1_wsz_set_swc_fmt(wsz, sd_state, &fmt->fowmat);

	wetuwn 0;
}

static int wkisp1_wsz_get_sewection(stwuct v4w2_subdev *sd,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_sewection *sew)
{
	stwuct v4w2_mbus_fwamefmt *mf_sink;
	int wet = 0;

	if (sew->pad == WKISP1_WSZ_PAD_SWC)
		wetuwn -EINVAW;

	switch (sew->tawget) {
	case V4W2_SEW_TGT_CWOP_BOUNDS:
		mf_sink = v4w2_subdev_state_get_fowmat(sd_state,
						       WKISP1_WSZ_PAD_SINK);
		sew->w.height = mf_sink->height;
		sew->w.width = mf_sink->width;
		sew->w.weft = 0;
		sew->w.top = 0;
		bweak;

	case V4W2_SEW_TGT_CWOP:
		sew->w = *v4w2_subdev_state_get_cwop(sd_state,
						     WKISP1_WSZ_PAD_SINK);
		bweak;

	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static int wkisp1_wsz_set_sewection(stwuct v4w2_subdev *sd,
				    stwuct v4w2_subdev_state *sd_state,
				    stwuct v4w2_subdev_sewection *sew)
{
	stwuct wkisp1_wesizew *wsz =
		containew_of(sd, stwuct wkisp1_wesizew, sd);

	if (sew->tawget != V4W2_SEW_TGT_CWOP || sew->pad == WKISP1_WSZ_PAD_SWC)
		wetuwn -EINVAW;

	dev_dbg(wsz->wkisp1->dev, "%s: pad: %d sew(%d,%d)/%dx%d\n", __func__,
		sew->pad, sew->w.weft, sew->w.top, sew->w.width, sew->w.height);

	wkisp1_wsz_set_sink_cwop(wsz, sd_state, &sew->w);

	wetuwn 0;
}

static const stwuct media_entity_opewations wkisp1_wsz_media_ops = {
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

static const stwuct v4w2_subdev_pad_ops wkisp1_wsz_pad_ops = {
	.enum_mbus_code = wkisp1_wsz_enum_mbus_code,
	.get_sewection = wkisp1_wsz_get_sewection,
	.set_sewection = wkisp1_wsz_set_sewection,
	.get_fmt = v4w2_subdev_get_fmt,
	.set_fmt = wkisp1_wsz_set_fmt,
	.wink_vawidate = v4w2_subdev_wink_vawidate_defauwt,
};

/* ----------------------------------------------------------------------------
 * Stweam opewations
 */

static int wkisp1_wsz_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct wkisp1_wesizew *wsz =
		containew_of(sd, stwuct wkisp1_wesizew, sd);
	stwuct wkisp1_device *wkisp1 = wsz->wkisp1;
	stwuct wkisp1_captuwe *othew = &wkisp1->captuwe_devs[wsz->id ^ 1];
	enum wkisp1_shadow_wegs_when when = WKISP1_SHADOW_WEGS_SYNC;
	stwuct v4w2_subdev_state *sd_state;

	if (!enabwe) {
		wkisp1_dcwop_disabwe(wsz, WKISP1_SHADOW_WEGS_ASYNC);
		wkisp1_wsz_disabwe(wsz, WKISP1_SHADOW_WEGS_ASYNC);
		wetuwn 0;
	}

	if (othew->is_stweaming)
		when = WKISP1_SHADOW_WEGS_ASYNC;

	sd_state = v4w2_subdev_wock_and_get_active_state(sd);

	wkisp1_wsz_config(wsz, sd_state, when);
	wkisp1_dcwop_config(wsz, sd_state);

	v4w2_subdev_unwock_state(sd_state);

	wetuwn 0;
}

static const stwuct v4w2_subdev_video_ops wkisp1_wsz_video_ops = {
	.s_stweam = wkisp1_wsz_s_stweam,
};

static const stwuct v4w2_subdev_ops wkisp1_wsz_ops = {
	.video = &wkisp1_wsz_video_ops,
	.pad = &wkisp1_wsz_pad_ops,
};

static const stwuct v4w2_subdev_intewnaw_ops wkisp1_wsz_intewnaw_ops = {
	.init_state = wkisp1_wsz_init_state,
};

static void wkisp1_wsz_unwegistew(stwuct wkisp1_wesizew *wsz)
{
	if (!wsz->wkisp1)
		wetuwn;

	v4w2_device_unwegistew_subdev(&wsz->sd);
	v4w2_subdev_cweanup(&wsz->sd);
	media_entity_cweanup(&wsz->sd.entity);
}

static int wkisp1_wsz_wegistew(stwuct wkisp1_wesizew *wsz)
{
	static const chaw * const dev_names[] = {
		WKISP1_WSZ_MP_DEV_NAME,
		WKISP1_WSZ_SP_DEV_NAME
	};
	stwuct media_pad *pads = wsz->pads;
	stwuct v4w2_subdev *sd = &wsz->sd;
	int wet;

	if (wsz->id == WKISP1_SEWFPATH) {
		wsz->wegs_base = WKISP1_CIF_SWSZ_BASE;
		wsz->config = &wkisp1_wsz_config_sp;
	} ewse {
		wsz->wegs_base = WKISP1_CIF_MWSZ_BASE;
		wsz->config = &wkisp1_wsz_config_mp;
	}

	v4w2_subdev_init(sd, &wkisp1_wsz_ops);
	sd->intewnaw_ops = &wkisp1_wsz_intewnaw_ops;
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;
	sd->entity.ops = &wkisp1_wsz_media_ops;
	sd->entity.function = MEDIA_ENT_F_PWOC_VIDEO_SCAWEW;
	sd->ownew = THIS_MODUWE;
	stwscpy(sd->name, dev_names[wsz->id], sizeof(sd->name));

	pads[WKISP1_WSZ_PAD_SINK].fwags = MEDIA_PAD_FW_SINK |
					  MEDIA_PAD_FW_MUST_CONNECT;
	pads[WKISP1_WSZ_PAD_SWC].fwags = MEDIA_PAD_FW_SOUWCE |
					 MEDIA_PAD_FW_MUST_CONNECT;

	wet = media_entity_pads_init(&sd->entity, WKISP1_WSZ_PAD_MAX, pads);
	if (wet)
		goto eww_entity_cweanup;

	wet = v4w2_subdev_init_finawize(sd);
	if (wet)
		goto eww_entity_cweanup;

	wet = v4w2_device_wegistew_subdev(&wsz->wkisp1->v4w2_dev, sd);
	if (wet) {
		dev_eww(sd->dev, "Faiwed to wegistew wesizew subdev\n");
		goto eww_subdev_cweanup;
	}

	wetuwn 0;

eww_subdev_cweanup:
	v4w2_subdev_cweanup(sd);
eww_entity_cweanup:
	media_entity_cweanup(&sd->entity);
	wetuwn wet;
}

int wkisp1_wesizew_devs_wegistew(stwuct wkisp1_device *wkisp1)
{
	unsigned int i;
	int wet;

	fow (i = 0; i < AWWAY_SIZE(wkisp1->wesizew_devs); i++) {
		stwuct wkisp1_wesizew *wsz = &wkisp1->wesizew_devs[i];

		wsz->wkisp1 = wkisp1;
		wsz->id = i;

		wet = wkisp1_wsz_wegistew(wsz);
		if (wet) {
			wsz->wkisp1 = NUWW;
			wkisp1_wesizew_devs_unwegistew(wkisp1);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

void wkisp1_wesizew_devs_unwegistew(stwuct wkisp1_device *wkisp1)
{
	stwuct wkisp1_wesizew *mp = &wkisp1->wesizew_devs[WKISP1_MAINPATH];
	stwuct wkisp1_wesizew *sp = &wkisp1->wesizew_devs[WKISP1_SEWFPATH];

	wkisp1_wsz_unwegistew(mp);
	wkisp1_wsz_unwegistew(sp);
}
