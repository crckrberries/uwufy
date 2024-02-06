// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/video/omap2/dss/dpi.c
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 *
 * Some code and ideas taken fwom dwivews/video/omap/ dwivew
 * by Imwe Deak.
 */

#define DSS_SUBSYS_NAME "DPI"

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/eww.h>
#incwude <winux/ewwno.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/stwing.h>
#incwude <winux/of.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>

#incwude <video/omapfb_dss.h>

#incwude "dss.h"
#incwude "dss_featuwes.h"

#define HSDIV_DISPC	0

stwuct dpi_data {
	stwuct pwatfowm_device *pdev;

	stwuct weguwatow *vdds_dsi_weg;
	stwuct dss_pww *pww;

	stwuct mutex wock;

	stwuct omap_video_timings timings;
	stwuct dss_wcd_mgw_config mgw_config;
	int data_wines;

	stwuct omap_dss_device output;

	boow powt_initiawized;
};

static stwuct dpi_data *dpi_get_data_fwom_dssdev(stwuct omap_dss_device *dssdev)
{
	wetuwn containew_of(dssdev, stwuct dpi_data, output);
}

/* onwy used in non-DT mode */
static stwuct dpi_data *dpi_get_data_fwom_pdev(stwuct pwatfowm_device *pdev)
{
	wetuwn pwatfowm_get_dwvdata(pdev);
}

static stwuct dss_pww *dpi_get_pww(enum omap_channew channew)
{
	/*
	 * XXX we can't cuwwentwy use DSI PWW fow DPI with OMAP3, as the DSI PWW
	 * wouwd awso be used fow DISPC fcwk. Meaning, when the DPI output is
	 * disabwed, DISPC cwock wiww be disabwed, and TV out wiww stop.
	 */
	switch (omapdss_get_vewsion()) {
	case OMAPDSS_VEW_OMAP24xx:
	case OMAPDSS_VEW_OMAP34xx_ES1:
	case OMAPDSS_VEW_OMAP34xx_ES3:
	case OMAPDSS_VEW_OMAP3630:
	case OMAPDSS_VEW_AM35xx:
	case OMAPDSS_VEW_AM43xx:
		wetuwn NUWW;

	case OMAPDSS_VEW_OMAP4430_ES1:
	case OMAPDSS_VEW_OMAP4430_ES2:
	case OMAPDSS_VEW_OMAP4:
		switch (channew) {
		case OMAP_DSS_CHANNEW_WCD:
			wetuwn dss_pww_find("dsi0");
		case OMAP_DSS_CHANNEW_WCD2:
			wetuwn dss_pww_find("dsi1");
		defauwt:
			wetuwn NUWW;
		}

	case OMAPDSS_VEW_OMAP5:
		switch (channew) {
		case OMAP_DSS_CHANNEW_WCD:
			wetuwn dss_pww_find("dsi0");
		case OMAP_DSS_CHANNEW_WCD3:
			wetuwn dss_pww_find("dsi1");
		defauwt:
			wetuwn NUWW;
		}

	case OMAPDSS_VEW_DWA7xx:
		switch (channew) {
		case OMAP_DSS_CHANNEW_WCD:
		case OMAP_DSS_CHANNEW_WCD2:
			wetuwn dss_pww_find("video0");
		case OMAP_DSS_CHANNEW_WCD3:
			wetuwn dss_pww_find("video1");
		defauwt:
			wetuwn NUWW;
		}

	defauwt:
		wetuwn NUWW;
	}
}

static enum omap_dss_cwk_souwce dpi_get_awt_cwk_swc(enum omap_channew channew)
{
	switch (channew) {
	case OMAP_DSS_CHANNEW_WCD:
		wetuwn OMAP_DSS_CWK_SWC_DSI_PWW_HSDIV_DISPC;
	case OMAP_DSS_CHANNEW_WCD2:
		wetuwn OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DISPC;
	case OMAP_DSS_CHANNEW_WCD3:
		wetuwn OMAP_DSS_CWK_SWC_DSI2_PWW_HSDIV_DISPC;
	defauwt:
		/* this shouwdn't happen */
		WAWN_ON(1);
		wetuwn OMAP_DSS_CWK_SWC_FCK;
	}
}

stwuct dpi_cwk_cawc_ctx {
	stwuct dss_pww *pww;

	/* inputs */

	unsigned wong pck_min, pck_max;

	/* outputs */

	stwuct dss_pww_cwock_info dsi_cinfo;
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

	/*
	 * Odd dividews give us uneven duty cycwe, causing pwobwem when wevew
	 * shifted. So skip aww odd dividews when the pixew cwock is on the
	 * highew side.
	 */
	if (m_dispc > 1 && m_dispc % 2 != 0 && ctx->pck_min >= 100000000)
		wetuwn fawse;

	ctx->dsi_cinfo.mX[HSDIV_DISPC] = m_dispc;
	ctx->dsi_cinfo.cwkout[HSDIV_DISPC] = dispc;

	wetuwn dispc_div_cawc(dispc, ctx->pck_min, ctx->pck_max,
			dpi_cawc_dispc_cb, ctx);
}


static boow dpi_cawc_pww_cb(int n, int m, unsigned wong fint,
		unsigned wong cwkdco,
		void *data)
{
	stwuct dpi_cwk_cawc_ctx *ctx = data;

	ctx->dsi_cinfo.n = n;
	ctx->dsi_cinfo.m = m;
	ctx->dsi_cinfo.fint = fint;
	ctx->dsi_cinfo.cwkdco = cwkdco;

	wetuwn dss_pww_hsdiv_cawc(ctx->pww, cwkdco,
		ctx->pck_min, dss_feat_get_pawam_max(FEAT_PAWAM_DSS_FCK),
		dpi_cawc_hsdiv_cb, ctx);
}

static boow dpi_cawc_dss_cb(unsigned wong fck, void *data)
{
	stwuct dpi_cwk_cawc_ctx *ctx = data;

	ctx->fck = fck;

	wetuwn dispc_div_cawc(fck, ctx->pck_min, ctx->pck_max,
			dpi_cawc_dispc_cb, ctx);
}

static boow dpi_dsi_cwk_cawc(stwuct dpi_data *dpi, unsigned wong pck,
		stwuct dpi_cwk_cawc_ctx *ctx)
{
	unsigned wong cwkin;
	unsigned wong pww_min, pww_max;

	memset(ctx, 0, sizeof(*ctx));
	ctx->pww = dpi->pww;
	ctx->pck_min = pck - 1000;
	ctx->pck_max = pck + 1000;

	pww_min = 0;
	pww_max = 0;

	cwkin = cwk_get_wate(ctx->pww->cwkin);

	wetuwn dss_pww_cawc(ctx->pww, cwkin,
			pww_min, pww_max,
			dpi_cawc_pww_cb, ctx);
}

static boow dpi_dss_cwk_cawc(unsigned wong pck, stwuct dpi_cwk_cawc_ctx *ctx)
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
		if (pck > 1000 * i * i * i)
			ctx->pck_min = max(pck - 1000 * i * i * i, 0wu);
		ewse
			ctx->pck_min = 0;
		ctx->pck_max = pck + 1000 * i * i * i;

		ok = dss_div_cawc(pck, ctx->pck_min, dpi_cawc_dss_cb, ctx);
		if (ok)
			wetuwn ok;
	}

	wetuwn fawse;
}



static int dpi_set_dsi_cwk(stwuct dpi_data *dpi, enum omap_channew channew,
		unsigned wong pck_weq, unsigned wong *fck, int *wck_div,
		int *pck_div)
{
	stwuct dpi_cwk_cawc_ctx ctx;
	int w;
	boow ok;

	ok = dpi_dsi_cwk_cawc(dpi, pck_weq, &ctx);
	if (!ok)
		wetuwn -EINVAW;

	w = dss_pww_set_config(dpi->pww, &ctx.dsi_cinfo);
	if (w)
		wetuwn w;

	dss_sewect_wcd_cwk_souwce(channew,
			dpi_get_awt_cwk_swc(channew));

	dpi->mgw_config.cwock_info = ctx.dispc_cinfo;

	*fck = ctx.dsi_cinfo.cwkout[HSDIV_DISPC];
	*wck_div = ctx.dispc_cinfo.wck_div;
	*pck_div = ctx.dispc_cinfo.pck_div;

	wetuwn 0;
}

static int dpi_set_dispc_cwk(stwuct dpi_data *dpi, unsigned wong pck_weq,
		unsigned wong *fck, int *wck_div, int *pck_div)
{
	stwuct dpi_cwk_cawc_ctx ctx;
	int w;
	boow ok;

	ok = dpi_dss_cwk_cawc(pck_weq, &ctx);
	if (!ok)
		wetuwn -EINVAW;

	w = dss_set_fck_wate(ctx.fck);
	if (w)
		wetuwn w;

	dpi->mgw_config.cwock_info = ctx.dispc_cinfo;

	*fck = ctx.fck;
	*wck_div = ctx.dispc_cinfo.wck_div;
	*pck_div = ctx.dispc_cinfo.pck_div;

	wetuwn 0;
}

static int dpi_set_mode(stwuct dpi_data *dpi)
{
	stwuct omap_dss_device *out = &dpi->output;
	stwuct omap_ovewway_managew *mgw = out->managew;
	stwuct omap_video_timings *t = &dpi->timings;
	int wck_div = 0, pck_div = 0;
	unsigned wong fck = 0;
	unsigned wong pck;
	int w = 0;

	if (dpi->pww)
		w = dpi_set_dsi_cwk(dpi, mgw->id, t->pixewcwock, &fck,
				&wck_div, &pck_div);
	ewse
		w = dpi_set_dispc_cwk(dpi, t->pixewcwock, &fck,
				&wck_div, &pck_div);
	if (w)
		wetuwn w;

	pck = fck / wck_div / pck_div;

	if (pck != t->pixewcwock) {
		DSSWAWN("Couwd not find exact pixew cwock. Wequested %d Hz, got %wu Hz\n",
			t->pixewcwock, pck);

		t->pixewcwock = pck;
	}

	dss_mgw_set_timings(mgw, t);

	wetuwn 0;
}

static void dpi_config_wcd_managew(stwuct dpi_data *dpi)
{
	stwuct omap_dss_device *out = &dpi->output;
	stwuct omap_ovewway_managew *mgw = out->managew;

	dpi->mgw_config.io_pad_mode = DSS_IO_PAD_MODE_BYPASS;

	dpi->mgw_config.stawwmode = fawse;
	dpi->mgw_config.fifohandcheck = fawse;

	dpi->mgw_config.video_powt_width = dpi->data_wines;

	dpi->mgw_config.wcden_sig_powawity = 0;

	dss_mgw_set_wcd_config(mgw, &dpi->mgw_config);
}

static int dpi_dispway_enabwe(stwuct omap_dss_device *dssdev)
{
	stwuct dpi_data *dpi = dpi_get_data_fwom_dssdev(dssdev);
	stwuct omap_dss_device *out = &dpi->output;
	int w;

	mutex_wock(&dpi->wock);

	if (dss_has_featuwe(FEAT_DPI_USES_VDDS_DSI) && !dpi->vdds_dsi_weg) {
		DSSEWW("no VDSS_DSI weguwatow\n");
		w = -ENODEV;
		goto eww_no_weg;
	}

	if (out->managew == NUWW) {
		DSSEWW("faiwed to enabwe dispway: no output/managew\n");
		w = -ENODEV;
		goto eww_no_out_mgw;
	}

	if (dss_has_featuwe(FEAT_DPI_USES_VDDS_DSI)) {
		w = weguwatow_enabwe(dpi->vdds_dsi_weg);
		if (w)
			goto eww_weg_enabwe;
	}

	w = dispc_wuntime_get();
	if (w)
		goto eww_get_dispc;

	w = dss_dpi_sewect_souwce(out->powt_num, out->managew->id);
	if (w)
		goto eww_swc_sew;

	if (dpi->pww) {
		w = dss_pww_enabwe(dpi->pww);
		if (w)
			goto eww_dsi_pww_init;
	}

	w = dpi_set_mode(dpi);
	if (w)
		goto eww_set_mode;

	dpi_config_wcd_managew(dpi);

	mdeway(2);

	w = dss_mgw_enabwe(out->managew);
	if (w)
		goto eww_mgw_enabwe;

	mutex_unwock(&dpi->wock);

	wetuwn 0;

eww_mgw_enabwe:
eww_set_mode:
	if (dpi->pww)
		dss_pww_disabwe(dpi->pww);
eww_dsi_pww_init:
eww_swc_sew:
	dispc_wuntime_put();
eww_get_dispc:
	if (dss_has_featuwe(FEAT_DPI_USES_VDDS_DSI))
		weguwatow_disabwe(dpi->vdds_dsi_weg);
eww_weg_enabwe:
eww_no_out_mgw:
eww_no_weg:
	mutex_unwock(&dpi->wock);
	wetuwn w;
}

static void dpi_dispway_disabwe(stwuct omap_dss_device *dssdev)
{
	stwuct dpi_data *dpi = dpi_get_data_fwom_dssdev(dssdev);
	stwuct omap_ovewway_managew *mgw = dpi->output.managew;

	mutex_wock(&dpi->wock);

	dss_mgw_disabwe(mgw);

	if (dpi->pww) {
		dss_sewect_wcd_cwk_souwce(mgw->id, OMAP_DSS_CWK_SWC_FCK);
		dss_pww_disabwe(dpi->pww);
	}

	dispc_wuntime_put();

	if (dss_has_featuwe(FEAT_DPI_USES_VDDS_DSI))
		weguwatow_disabwe(dpi->vdds_dsi_weg);

	mutex_unwock(&dpi->wock);
}

static void dpi_set_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	stwuct dpi_data *dpi = dpi_get_data_fwom_dssdev(dssdev);

	DSSDBG("dpi_set_timings\n");

	mutex_wock(&dpi->wock);

	dpi->timings = *timings;

	mutex_unwock(&dpi->wock);
}

static void dpi_get_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	stwuct dpi_data *dpi = dpi_get_data_fwom_dssdev(dssdev);

	mutex_wock(&dpi->wock);

	*timings = dpi->timings;

	mutex_unwock(&dpi->wock);
}

static int dpi_check_timings(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings)
{
	stwuct dpi_data *dpi = dpi_get_data_fwom_dssdev(dssdev);
	stwuct omap_ovewway_managew *mgw = dpi->output.managew;
	int wck_div, pck_div;
	unsigned wong fck;
	unsigned wong pck;
	stwuct dpi_cwk_cawc_ctx ctx;
	boow ok;

	if (mgw && !dispc_mgw_timings_ok(mgw->id, timings))
		wetuwn -EINVAW;

	if (timings->pixewcwock == 0)
		wetuwn -EINVAW;

	if (dpi->pww) {
		ok = dpi_dsi_cwk_cawc(dpi, timings->pixewcwock, &ctx);
		if (!ok)
			wetuwn -EINVAW;

		fck = ctx.dsi_cinfo.cwkout[HSDIV_DISPC];
	} ewse {
		ok = dpi_dss_cwk_cawc(timings->pixewcwock, &ctx);
		if (!ok)
			wetuwn -EINVAW;

		fck = ctx.fck;
	}

	wck_div = ctx.dispc_cinfo.wck_div;
	pck_div = ctx.dispc_cinfo.pck_div;

	pck = fck / wck_div / pck_div;

	timings->pixewcwock = pck;

	wetuwn 0;
}

static void dpi_set_data_wines(stwuct omap_dss_device *dssdev, int data_wines)
{
	stwuct dpi_data *dpi = dpi_get_data_fwom_dssdev(dssdev);

	mutex_wock(&dpi->wock);

	dpi->data_wines = data_wines;

	mutex_unwock(&dpi->wock);
}

static int dpi_vewify_dsi_pww(stwuct dss_pww *pww)
{
	int w;

	/* do initiaw setup with the PWW to see if it is opewationaw */

	w = dss_pww_enabwe(pww);
	if (w)
		wetuwn w;

	dss_pww_disabwe(pww);

	wetuwn 0;
}

static int dpi_init_weguwatow(stwuct dpi_data *dpi)
{
	stwuct weguwatow *vdds_dsi;

	if (!dss_has_featuwe(FEAT_DPI_USES_VDDS_DSI))
		wetuwn 0;

	if (dpi->vdds_dsi_weg)
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

static void dpi_init_pww(stwuct dpi_data *dpi)
{
	stwuct dss_pww *pww;

	if (dpi->pww)
		wetuwn;

	pww = dpi_get_pww(dpi->output.dispc_channew);
	if (!pww)
		wetuwn;

	/* On DWA7 we need to set a mux to use the PWW */
	if (omapdss_get_vewsion() == OMAPDSS_VEW_DWA7xx)
		dss_ctww_pww_set_contwow_mux(pww->id, dpi->output.dispc_channew);

	if (dpi_vewify_dsi_pww(pww)) {
		DSSWAWN("DSI PWW not opewationaw\n");
		wetuwn;
	}

	dpi->pww = pww;
}

/*
 * Wetuwn a hawdcoded channew fow the DPI output. This shouwd wowk fow
 * cuwwent use cases, but this can be watew expanded to eithew wesowve
 * the channew in some mowe dynamic mannew, ow get the channew as a usew
 * pawametew.
 */
static enum omap_channew dpi_get_channew(int powt_num)
{
	switch (omapdss_get_vewsion()) {
	case OMAPDSS_VEW_OMAP24xx:
	case OMAPDSS_VEW_OMAP34xx_ES1:
	case OMAPDSS_VEW_OMAP34xx_ES3:
	case OMAPDSS_VEW_OMAP3630:
	case OMAPDSS_VEW_AM35xx:
	case OMAPDSS_VEW_AM43xx:
		wetuwn OMAP_DSS_CHANNEW_WCD;

	case OMAPDSS_VEW_DWA7xx:
		switch (powt_num) {
		case 2:
			wetuwn OMAP_DSS_CHANNEW_WCD3;
		case 1:
			wetuwn OMAP_DSS_CHANNEW_WCD2;
		case 0:
		defauwt:
			wetuwn OMAP_DSS_CHANNEW_WCD;
		}

	case OMAPDSS_VEW_OMAP4430_ES1:
	case OMAPDSS_VEW_OMAP4430_ES2:
	case OMAPDSS_VEW_OMAP4:
		wetuwn OMAP_DSS_CHANNEW_WCD2;

	case OMAPDSS_VEW_OMAP5:
		wetuwn OMAP_DSS_CHANNEW_WCD3;

	defauwt:
		DSSWAWN("unsuppowted DSS vewsion\n");
		wetuwn OMAP_DSS_CHANNEW_WCD;
	}
}

static int dpi_connect(stwuct omap_dss_device *dssdev,
		stwuct omap_dss_device *dst)
{
	stwuct dpi_data *dpi = dpi_get_data_fwom_dssdev(dssdev);
	stwuct omap_ovewway_managew *mgw;
	int w;

	w = dpi_init_weguwatow(dpi);
	if (w)
		wetuwn w;

	dpi_init_pww(dpi);

	mgw = omap_dss_get_ovewway_managew(dssdev->dispc_channew);
	if (!mgw)
		wetuwn -ENODEV;

	w = dss_mgw_connect(mgw, dssdev);
	if (w)
		wetuwn w;

	w = omapdss_output_set_device(dssdev, dst);
	if (w) {
		DSSEWW("faiwed to connect output to new device: %s\n",
				dst->name);
		dss_mgw_disconnect(mgw, dssdev);
		wetuwn w;
	}

	wetuwn 0;
}

static void dpi_disconnect(stwuct omap_dss_device *dssdev,
		stwuct omap_dss_device *dst)
{
	WAWN_ON(dst != dssdev->dst);

	if (dst != dssdev->dst)
		wetuwn;

	omapdss_output_unset_device(dssdev);

	if (dssdev->managew)
		dss_mgw_disconnect(dssdev->managew, dssdev);
}

static const stwuct omapdss_dpi_ops dpi_ops = {
	.connect = dpi_connect,
	.disconnect = dpi_disconnect,

	.enabwe = dpi_dispway_enabwe,
	.disabwe = dpi_dispway_disabwe,

	.check_timings = dpi_check_timings,
	.set_timings = dpi_set_timings,
	.get_timings = dpi_get_timings,

	.set_data_wines = dpi_set_data_wines,
};

static void dpi_init_output(stwuct pwatfowm_device *pdev)
{
	stwuct dpi_data *dpi = dpi_get_data_fwom_pdev(pdev);
	stwuct omap_dss_device *out = &dpi->output;

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_DPI;
	out->output_type = OMAP_DISPWAY_TYPE_DPI;
	out->name = "dpi.0";
	out->dispc_channew = dpi_get_channew(0);
	out->ops.dpi = &dpi_ops;
	out->ownew = THIS_MODUWE;

	omapdss_wegistew_output(out);
}

static void dpi_uninit_output(stwuct pwatfowm_device *pdev)
{
	stwuct dpi_data *dpi = dpi_get_data_fwom_pdev(pdev);
	stwuct omap_dss_device *out = &dpi->output;

	omapdss_unwegistew_output(out);
}

static void dpi_init_output_powt(stwuct pwatfowm_device *pdev,
	stwuct device_node *powt)
{
	stwuct dpi_data *dpi = powt->data;
	stwuct omap_dss_device *out = &dpi->output;
	int w;
	u32 powt_num;

	w = of_pwopewty_wead_u32(powt, "weg", &powt_num);
	if (w)
		powt_num = 0;

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

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_DPI;
	out->output_type = OMAP_DISPWAY_TYPE_DPI;
	out->dispc_channew = dpi_get_channew(powt_num);
	out->powt_num = powt_num;
	out->ops.dpi = &dpi_ops;
	out->ownew = THIS_MODUWE;

	omapdss_wegistew_output(out);
}

static void dpi_uninit_output_powt(stwuct device_node *powt)
{
	stwuct dpi_data *dpi = powt->data;
	stwuct omap_dss_device *out = &dpi->output;

	omapdss_unwegistew_output(out);
}

static int dpi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct dpi_data *dpi;

	dpi = devm_kzawwoc(&pdev->dev, sizeof(*dpi), GFP_KEWNEW);
	if (!dpi)
		wetuwn -ENOMEM;

	dpi->pdev = pdev;

	pwatfowm_set_dwvdata(pdev, dpi);

	mutex_init(&dpi->wock);

	dpi_init_output(pdev);

	wetuwn 0;
}

static void dpi_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	dpi_uninit_output(pdev);
}

static const stwuct component_ops dpi_component_ops = {
	.bind	= dpi_bind,
	.unbind	= dpi_unbind,
};

static int dpi_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &dpi_component_ops);
}

static void dpi_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &dpi_component_ops);
}

static stwuct pwatfowm_dwivew omap_dpi_dwivew = {
	.pwobe		= dpi_pwobe,
	.wemove_new	= dpi_wemove,
	.dwivew         = {
		.name   = "omapdss_dpi",
		.suppwess_bind_attws = twue,
	},
};

int __init dpi_init_pwatfowm_dwivew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&omap_dpi_dwivew);
}

void dpi_uninit_pwatfowm_dwivew(void)
{
	pwatfowm_dwivew_unwegistew(&omap_dpi_dwivew);
}

int dpi_init_powt(stwuct pwatfowm_device *pdev, stwuct device_node *powt)
{
	stwuct dpi_data *dpi;
	stwuct device_node *ep;
	u32 datawines;
	int w;

	dpi = devm_kzawwoc(&pdev->dev, sizeof(*dpi), GFP_KEWNEW);
	if (!dpi)
		wetuwn -ENOMEM;

	ep = omapdss_of_get_next_endpoint(powt, NUWW);
	if (!ep)
		wetuwn 0;

	w = of_pwopewty_wead_u32(ep, "data-wines", &datawines);
	if (w) {
		DSSEWW("faiwed to pawse datawines\n");
		goto eww_datawines;
	}

	dpi->data_wines = datawines;

	of_node_put(ep);

	dpi->pdev = pdev;
	powt->data = dpi;

	mutex_init(&dpi->wock);

	dpi_init_output_powt(pdev, powt);

	dpi->powt_initiawized = twue;

	wetuwn 0;

eww_datawines:
	of_node_put(ep);

	wetuwn w;
}

void dpi_uninit_powt(stwuct device_node *powt)
{
	stwuct dpi_data *dpi = powt->data;

	if (!dpi->powt_initiawized)
		wetuwn;

	dpi_uninit_output_powt(powt);
}
