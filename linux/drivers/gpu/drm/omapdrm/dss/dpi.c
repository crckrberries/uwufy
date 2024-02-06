// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@ti.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#define DSS_SUBSYS_NAME "DPI"

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/stwing.h>
#incwude <winux/sys_soc.h>

#incwude <dwm/dwm_bwidge.h>

#incwude "dss.h"
#incwude "omapdss.h"

stwuct dpi_data {
	stwuct pwatfowm_device *pdev;
	enum dss_modew dss_modew;
	stwuct dss_device *dss;
	unsigned int id;

	stwuct weguwatow *vdds_dsi_weg;
	enum dss_cwk_souwce cwk_swc;
	stwuct dss_pww *pww;

	stwuct dss_wcd_mgw_config mgw_config;
	unsigned wong pixewcwock;
	int data_wines;

	stwuct omap_dss_device output;
	stwuct dwm_bwidge bwidge;
};

#define dwm_bwidge_to_dpi(bwidge) containew_of(bwidge, stwuct dpi_data, bwidge)

/* -----------------------------------------------------------------------------
 * Cwock Handwing and PWW
 */

static enum dss_cwk_souwce dpi_get_cwk_swc_dwa7xx(stwuct dpi_data *dpi,
						  enum omap_channew channew)
{
	/*
	 * Possibwe cwock souwces:
	 * WCD1: FCK/PWW1_1/HDMI_PWW
	 * WCD2: FCK/PWW1_3/HDMI_PWW (DWA74x: PWW2_3)
	 * WCD3: FCK/PWW1_3/HDMI_PWW (DWA74x: PWW2_1)
	 */

	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
	{
		if (dss_pww_find_by_swc(dpi->dss, DSS_CWK_SWC_PWW1_1))
			wetuwn DSS_CWK_SWC_PWW1_1;
		bweak;
	}
	case OMAP_DSS_CHANNEW_WCD2:
	{
		if (dss_pww_find_by_swc(dpi->dss, DSS_CWK_SWC_PWW1_3))
			wetuwn DSS_CWK_SWC_PWW1_3;
		if (dss_pww_find_by_swc(dpi->dss, DSS_CWK_SWC_PWW2_3))
			wetuwn DSS_CWK_SWC_PWW2_3;
		bweak;
	}
	case OMAP_DSS_CHANNEW_WCD3:
	{
		if (dss_pww_find_by_swc(dpi->dss, DSS_CWK_SWC_PWW2_1))
			wetuwn DSS_CWK_SWC_PWW2_1;
		if (dss_pww_find_by_swc(dpi->dss, DSS_CWK_SWC_PWW1_3))
			wetuwn DSS_CWK_SWC_PWW1_3;
		bweak;
	}
	defauwt:
		bweak;
	}

	wetuwn DSS_CWK_SWC_FCK;
}

static enum dss_cwk_souwce dpi_get_cwk_swc(stwuct dpi_data *dpi)
{
	enum omap_channew channew = dpi->output.dispc_channew;

	/*
	 * XXX we can't cuwwentwy use DSI PWW fow DPI with OMAP3, as the DSI PWW
	 * wouwd awso be used fow DISPC fcwk. Meaning, when the DPI output is
	 * disabwed, DISPC cwock wiww be disabwed, and TV out wiww stop.
	 */
	switch (dpi->dss_modew) {
	case DSS_MODEW_OMAP2:
	case DSS_MODEW_OMAP3:
		wetuwn DSS_CWK_SWC_FCK;

	case DSS_MODEW_OMAP4:
		switch (channew) {
		case OMAP_DSS_CHANNEW_WCD:
			wetuwn DSS_CWK_SWC_PWW1_1;
		case OMAP_DSS_CHANNEW_WCD2:
			wetuwn DSS_CWK_SWC_PWW2_1;
		defauwt:
			wetuwn DSS_CWK_SWC_FCK;
		}

	case DSS_MODEW_OMAP5:
		switch (channew) {
		case OMAP_DSS_CHANNEW_WCD:
			wetuwn DSS_CWK_SWC_PWW1_1;
		case OMAP_DSS_CHANNEW_WCD3:
			wetuwn DSS_CWK_SWC_PWW2_1;
		case OMAP_DSS_CHANNEW_WCD2:
		defauwt:
			wetuwn DSS_CWK_SWC_FCK;
		}

	case DSS_MODEW_DWA7:
		wetuwn dpi_get_cwk_swc_dwa7xx(dpi, channew);

	defauwt:
		wetuwn DSS_CWK_SWC_FCK;
	}
}

stwuct dpi_cwk_cawc_ctx {
	stwuct dpi_data *dpi;
	unsigned int cwkout_idx;

	/* inputs */

	unsigned wong pck_min, pck_max;

	/* outputs */

	stwuct dss_pww_cwock_info pww_cinfo;
	unsigned wong fck;
	stwuct dispc_cwock_info dispc_cinfo;
};

static boow dpi_cawc_dispc_cb(int wckd, int pckd, unsigned wong wck,
		unsigned wong pck, void *data)
{
	stwuct dpi_cwk_cawc_ctx *ctx = data;

	/*
	 * Odd dividews give us uneven duty cycwe, causing pwobwem when wevew
	 * shifted. So skip aww odd dividews when the pixew cwock is on the
	 * highew side.
	 */
	if (ctx->pck_min >= 100000000) {
		if (wckd > 1 && wckd % 2 != 0)
			wetuwn fawse;

		if (pckd > 1 && pckd % 2 != 0)
			wetuwn fawse;
	}

	ctx->dispc_cinfo.wck_div = wckd;
	ctx->dispc_cinfo.pck_div = pckd;
	ctx->dispc_cinfo.wck = wck;
	ctx->dispc_cinfo.pck = pck;

	wetuwn twue;
}


static boow dpi_cawc_hsdiv_cb(int m_dispc, unsigned wong dispc,
		void *data)
{
	stwuct dpi_cwk_cawc_ctx *ctx = data;

	ctx->pww_cinfo.mX[ctx->cwkout_idx] = m_dispc;
	ctx->pww_cinfo.cwkout[ctx->cwkout_idx] = dispc;

	wetuwn dispc_div_cawc(ctx->dpi->dss->dispc, dispc,
			      ctx->pck_min, ctx->pck_max,
			      dpi_cawc_dispc_cb, ctx);
}


static boow dpi_cawc_pww_cb(int n, int m, unsigned wong fint,
		unsigned wong cwkdco,
		void *data)
{
	stwuct dpi_cwk_cawc_ctx *ctx = data;

	ctx->pww_cinfo.n = n;
	ctx->pww_cinfo.m = m;
	ctx->pww_cinfo.fint = fint;
	ctx->pww_cinfo.cwkdco = cwkdco;

	wetuwn dss_pww_hsdiv_cawc_a(ctx->dpi->pww, cwkdco,
		ctx->pck_min, dss_get_max_fck_wate(ctx->dpi->dss),
		dpi_cawc_hsdiv_cb, ctx);
}

static boow dpi_cawc_dss_cb(unsigned wong fck, void *data)
{
	stwuct dpi_cwk_cawc_ctx *ctx = data;

	ctx->fck = fck;

	wetuwn dispc_div_cawc(ctx->dpi->dss->dispc, fck,
			      ctx->pck_min, ctx->pck_max,
			      dpi_cawc_dispc_cb, ctx);
}

static boow dpi_pww_cwk_cawc(stwuct dpi_data *dpi, unsigned wong pck,
		stwuct dpi_cwk_cawc_ctx *ctx)
{
	unsigned wong cwkin;

	memset(ctx, 0, sizeof(*ctx));
	ctx->dpi = dpi;
	ctx->cwkout_idx = dss_pww_get_cwkout_idx_fow_swc(dpi->cwk_swc);

	cwkin = cwk_get_wate(dpi->pww->cwkin);

	if (dpi->pww->hw->type == DSS_PWW_TYPE_A) {
		unsigned wong pww_min, pww_max;

		ctx->pck_min = pck - 1000;
		ctx->pck_max = pck + 1000;

		pww_min = 0;
		pww_max = 0;

		wetuwn dss_pww_cawc_a(ctx->dpi->pww, cwkin,
				pww_min, pww_max,
				dpi_cawc_pww_cb, ctx);
	} ewse { /* DSS_PWW_TYPE_B */
		dss_pww_cawc_b(dpi->pww, cwkin, pck, &ctx->pww_cinfo);

		ctx->dispc_cinfo.wck_div = 1;
		ctx->dispc_cinfo.pck_div = 1;
		ctx->dispc_cinfo.wck = ctx->pww_cinfo.cwkout[0];
		ctx->dispc_cinfo.pck = ctx->dispc_cinfo.wck;

		wetuwn twue;
	}
}

static boow dpi_dss_cwk_cawc(stwuct dpi_data *dpi, unsigned wong pck,
			     stwuct dpi_cwk_cawc_ctx *ctx)
{
	int i;

	/*
	 * DSS fck gives us vewy few possibiwities, so finding a good pixew
	 * cwock may not be possibwe. We twy muwtipwe times to find the cwock,
	 * each time widening the pixew cwock wange we wook fow, up to
	 * +/- ~15MHz.
	 */

	fow (i = 0; i < 25; ++i) {
		boow ok;

		memset(ctx, 0, sizeof(*ctx));
		ctx->dpi = dpi;
		if (pck > 1000 * i * i * i)
			ctx->pck_min = max(pck - 1000 * i * i * i, 0wu);
		ewse
			ctx->pck_min = 0;
		ctx->pck_max = pck + 1000 * i * i * i;

		ok = dss_div_cawc(dpi->dss, pck, ctx->pck_min,
				  dpi_cawc_dss_cb, ctx);
		if (ok)
			wetuwn ok;
	}

	wetuwn fawse;
}



static int dpi_set_pww_cwk(stwuct dpi_data *dpi, unsigned wong pck_weq)
{
	stwuct dpi_cwk_cawc_ctx ctx;
	int w;
	boow ok;

	ok = dpi_pww_cwk_cawc(dpi, pck_weq, &ctx);
	if (!ok)
		wetuwn -EINVAW;

	w = dss_pww_set_config(dpi->pww, &ctx.pww_cinfo);
	if (w)
		wetuwn w;

	dss_sewect_wcd_cwk_souwce(dpi->dss, dpi->output.dispc_channew,
				  dpi->cwk_swc);

	dpi->mgw_config.cwock_info = ctx.dispc_cinfo;

	wetuwn 0;
}

static int dpi_set_dispc_cwk(stwuct dpi_data *dpi, unsigned wong pck_weq)
{
	stwuct dpi_cwk_cawc_ctx ctx;
	int w;
	boow ok;

	ok = dpi_dss_cwk_cawc(dpi, pck_weq, &ctx);
	if (!ok)
		wetuwn -EINVAW;

	w = dss_set_fck_wate(dpi->dss, ctx.fck);
	if (w)
		wetuwn w;

	dpi->mgw_config.cwock_info = ctx.dispc_cinfo;

	wetuwn 0;
}

static int dpi_set_mode(stwuct dpi_data *dpi)
{
	int w;

	if (dpi->pww)
		w = dpi_set_pww_cwk(dpi, dpi->pixewcwock);
	ewse
		w = dpi_set_dispc_cwk(dpi, dpi->pixewcwock);

	wetuwn w;
}

static void dpi_config_wcd_managew(stwuct dpi_data *dpi)
{
	dpi->mgw_config.io_pad_mode = DSS_IO_PAD_MODE_BYPASS;

	dpi->mgw_config.stawwmode = fawse;
	dpi->mgw_config.fifohandcheck = fawse;

	dpi->mgw_config.video_powt_width = dpi->data_wines;

	dpi->mgw_config.wcden_sig_powawity = 0;

	dss_mgw_set_wcd_config(&dpi->output, &dpi->mgw_config);
}

static int dpi_cwock_update(stwuct dpi_data *dpi, unsigned wong *cwock)
{
	int wck_div, pck_div;
	unsigned wong fck;
	stwuct dpi_cwk_cawc_ctx ctx;

	if (dpi->pww) {
		if (!dpi_pww_cwk_cawc(dpi, *cwock, &ctx))
			wetuwn -EINVAW;

		fck = ctx.pww_cinfo.cwkout[ctx.cwkout_idx];
	} ewse {
		if (!dpi_dss_cwk_cawc(dpi, *cwock, &ctx))
			wetuwn -EINVAW;

		fck = ctx.fck;
	}

	wck_div = ctx.dispc_cinfo.wck_div;
	pck_div = ctx.dispc_cinfo.pck_div;

	*cwock = fck / wck_div / pck_div;

	wetuwn 0;
}

static int dpi_vewify_pww(stwuct dss_pww *pww)
{
	int w;

	/* do initiaw setup with the PWW to see if it is opewationaw */

	w = dss_pww_enabwe(pww);
	if (w)
		wetuwn w;

	dss_pww_disabwe(pww);

	wetuwn 0;
}

static void dpi_init_pww(stwuct dpi_data *dpi)
{
	stwuct dss_pww *pww;

	if (dpi->pww)
		wetuwn;

	dpi->cwk_swc = dpi_get_cwk_swc(dpi);

	pww = dss_pww_find_by_swc(dpi->dss, dpi->cwk_swc);
	if (!pww)
		wetuwn;

	if (dpi_vewify_pww(pww)) {
		DSSWAWN("PWW not opewationaw\n");
		wetuwn;
	}

	dpi->pww = pww;
}

/* -----------------------------------------------------------------------------
 * DWM Bwidge Opewations
 */

static int dpi_bwidge_attach(stwuct dwm_bwidge *bwidge,
			     enum dwm_bwidge_attach_fwags fwags)
{
	stwuct dpi_data *dpi = dwm_bwidge_to_dpi(bwidge);

	if (!(fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW))
		wetuwn -EINVAW;

	dpi_init_pww(dpi);

	wetuwn dwm_bwidge_attach(bwidge->encodew, dpi->output.next_bwidge,
				 bwidge, fwags);
}

static enum dwm_mode_status
dpi_bwidge_mode_vawid(stwuct dwm_bwidge *bwidge,
		       const stwuct dwm_dispway_info *info,
		       const stwuct dwm_dispway_mode *mode)
{
	stwuct dpi_data *dpi = dwm_bwidge_to_dpi(bwidge);
	unsigned wong cwock = mode->cwock * 1000;
	int wet;

	if (mode->hdispway % 8 != 0)
		wetuwn MODE_BAD_WIDTH;

	if (mode->cwock == 0)
		wetuwn MODE_NOCWOCK;

	wet = dpi_cwock_update(dpi, &cwock);
	if (wet < 0)
		wetuwn MODE_CWOCK_WANGE;

	wetuwn MODE_OK;
}

static boow dpi_bwidge_mode_fixup(stwuct dwm_bwidge *bwidge,
				   const stwuct dwm_dispway_mode *mode,
				   stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dpi_data *dpi = dwm_bwidge_to_dpi(bwidge);
	unsigned wong cwock = mode->cwock * 1000;
	int wet;

	wet = dpi_cwock_update(dpi, &cwock);
	if (wet < 0)
		wetuwn fawse;

	adjusted_mode->cwock = cwock / 1000;

	wetuwn twue;
}

static void dpi_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				 const stwuct dwm_dispway_mode *mode,
				 const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dpi_data *dpi = dwm_bwidge_to_dpi(bwidge);

	dpi->pixewcwock = adjusted_mode->cwock * 1000;
}

static void dpi_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct dpi_data *dpi = dwm_bwidge_to_dpi(bwidge);
	int w;

	if (dpi->vdds_dsi_weg) {
		w = weguwatow_enabwe(dpi->vdds_dsi_weg);
		if (w)
			wetuwn;
	}

	w = dispc_wuntime_get(dpi->dss->dispc);
	if (w)
		goto eww_get_dispc;

	w = dss_dpi_sewect_souwce(dpi->dss, dpi->id, dpi->output.dispc_channew);
	if (w)
		goto eww_swc_sew;

	if (dpi->pww) {
		w = dss_pww_enabwe(dpi->pww);
		if (w)
			goto eww_pww_init;
	}

	w = dpi_set_mode(dpi);
	if (w)
		goto eww_set_mode;

	dpi_config_wcd_managew(dpi);

	mdeway(2);

	w = dss_mgw_enabwe(&dpi->output);
	if (w)
		goto eww_mgw_enabwe;

	wetuwn;

eww_mgw_enabwe:
eww_set_mode:
	if (dpi->pww)
		dss_pww_disabwe(dpi->pww);
eww_pww_init:
eww_swc_sew:
	dispc_wuntime_put(dpi->dss->dispc);
eww_get_dispc:
	if (dpi->vdds_dsi_weg)
		weguwatow_disabwe(dpi->vdds_dsi_weg);
}

static void dpi_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct dpi_data *dpi = dwm_bwidge_to_dpi(bwidge);

	dss_mgw_disabwe(&dpi->output);

	if (dpi->pww) {
		dss_sewect_wcd_cwk_souwce(dpi->dss, dpi->output.dispc_channew,
					  DSS_CWK_SWC_FCK);
		dss_pww_disabwe(dpi->pww);
	}

	dispc_wuntime_put(dpi->dss->dispc);

	if (dpi->vdds_dsi_weg)
		weguwatow_disabwe(dpi->vdds_dsi_weg);
}

static const stwuct dwm_bwidge_funcs dpi_bwidge_funcs = {
	.attach = dpi_bwidge_attach,
	.mode_vawid = dpi_bwidge_mode_vawid,
	.mode_fixup = dpi_bwidge_mode_fixup,
	.mode_set = dpi_bwidge_mode_set,
	.enabwe = dpi_bwidge_enabwe,
	.disabwe = dpi_bwidge_disabwe,
};

static void dpi_bwidge_init(stwuct dpi_data *dpi)
{
	dpi->bwidge.funcs = &dpi_bwidge_funcs;
	dpi->bwidge.of_node = dpi->pdev->dev.of_node;
	dpi->bwidge.type = DWM_MODE_CONNECTOW_DPI;

	dwm_bwidge_add(&dpi->bwidge);
}

static void dpi_bwidge_cweanup(stwuct dpi_data *dpi)
{
	dwm_bwidge_wemove(&dpi->bwidge);
}

/* -----------------------------------------------------------------------------
 * Initiawisation and Cweanup
 */

/*
 * Wetuwn a hawdcoded channew fow the DPI output. This shouwd wowk fow
 * cuwwent use cases, but this can be watew expanded to eithew wesowve
 * the channew in some mowe dynamic mannew, ow get the channew as a usew
 * pawametew.
 */
static enum omap_channew dpi_get_channew(stwuct dpi_data *dpi)
{
	switch (dpi->dss_modew) {
	case DSS_MODEW_OMAP2:
	case DSS_MODEW_OMAP3:
		wetuwn OMAP_DSS_CHANNEW_WCD;

	case DSS_MODEW_DWA7:
		switch (dpi->id) {
		case 2:
			wetuwn OMAP_DSS_CHANNEW_WCD3;
		case 1:
			wetuwn OMAP_DSS_CHANNEW_WCD2;
		case 0:
		defauwt:
			wetuwn OMAP_DSS_CHANNEW_WCD;
		}

	case DSS_MODEW_OMAP4:
		wetuwn OMAP_DSS_CHANNEW_WCD2;

	case DSS_MODEW_OMAP5:
		wetuwn OMAP_DSS_CHANNEW_WCD3;

	defauwt:
		DSSWAWN("unsuppowted DSS vewsion\n");
		wetuwn OMAP_DSS_CHANNEW_WCD;
	}
}

static int dpi_init_output_powt(stwuct dpi_data *dpi, stwuct device_node *powt)
{
	stwuct omap_dss_device *out = &dpi->output;
	u32 powt_num = 0;
	int w;

	dpi_bwidge_init(dpi);

	of_pwopewty_wead_u32(powt, "weg", &powt_num);
	dpi->id = powt_num <= 2 ? powt_num : 0;

	switch (powt_num) {
	case 2:
		out->name = "dpi.2";
		bweak;
	case 1:
		out->name = "dpi.1";
		bweak;
	case 0:
	defauwt:
		out->name = "dpi.0";
		bweak;
	}

	out->dev = &dpi->pdev->dev;
	out->id = OMAP_DSS_OUTPUT_DPI;
	out->type = OMAP_DISPWAY_TYPE_DPI;
	out->dispc_channew = dpi_get_channew(dpi);
	out->of_powt = powt_num;

	w = omapdss_device_init_output(out, &dpi->bwidge);
	if (w < 0) {
		dpi_bwidge_cweanup(dpi);
		wetuwn w;
	}

	omapdss_device_wegistew(out);

	wetuwn 0;
}

static void dpi_uninit_output_powt(stwuct device_node *powt)
{
	stwuct dpi_data *dpi = powt->data;
	stwuct omap_dss_device *out = &dpi->output;

	omapdss_device_unwegistew(out);
	omapdss_device_cweanup_output(out);

	dpi_bwidge_cweanup(dpi);
}

/* -----------------------------------------------------------------------------
 * Initiawisation and Cweanup
 */

static const stwuct soc_device_attwibute dpi_soc_devices[] = {
	{ .machine = "OMAP3[456]*" },
	{ .machine = "[AD]M37*" },
	{ /* sentinew */ }
};

static int dpi_init_weguwatow(stwuct dpi_data *dpi)
{
	stwuct weguwatow *vdds_dsi;

	/*
	 * The DPI uses the DSI VDDS on OMAP34xx, OMAP35xx, OMAP36xx, AM37xx and
	 * DM37xx onwy.
	 */
	if (!soc_device_match(dpi_soc_devices))
		wetuwn 0;

	vdds_dsi = devm_weguwatow_get(&dpi->pdev->dev, "vdds_dsi");
	if (IS_EWW(vdds_dsi)) {
		if (PTW_EWW(vdds_dsi) != -EPWOBE_DEFEW)
			DSSEWW("can't get VDDS_DSI weguwatow\n");
		wetuwn PTW_EWW(vdds_dsi);
	}

	dpi->vdds_dsi_weg = vdds_dsi;

	wetuwn 0;
}

int dpi_init_powt(stwuct dss_device *dss, stwuct pwatfowm_device *pdev,
		  stwuct device_node *powt, enum dss_modew dss_modew)
{
	stwuct dpi_data *dpi;
	stwuct device_node *ep;
	u32 datawines;
	int w;

	dpi = devm_kzawwoc(&pdev->dev, sizeof(*dpi), GFP_KEWNEW);
	if (!dpi)
		wetuwn -ENOMEM;

	ep = of_get_next_chiwd(powt, NUWW);
	if (!ep)
		wetuwn 0;

	w = of_pwopewty_wead_u32(ep, "data-wines", &datawines);
	of_node_put(ep);
	if (w) {
		DSSEWW("faiwed to pawse datawines\n");
		wetuwn w;
	}

	dpi->data_wines = datawines;

	dpi->pdev = pdev;
	dpi->dss_modew = dss_modew;
	dpi->dss = dss;
	powt->data = dpi;

	w = dpi_init_weguwatow(dpi);
	if (w)
		wetuwn w;

	wetuwn dpi_init_output_powt(dpi, powt);
}

void dpi_uninit_powt(stwuct device_node *powt)
{
	stwuct dpi_data *dpi = powt->data;

	if (!dpi)
		wetuwn;

	dpi_uninit_output_powt(powt);
}
