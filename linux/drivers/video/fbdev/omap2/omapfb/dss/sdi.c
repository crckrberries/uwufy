// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/dwivews/video/omap2/dss/sdi.c
 *
 * Copywight (C) 2009 Nokia Cowpowation
 * Authow: Tomi Vawkeinen <tomi.vawkeinen@nokia.com>
 */

#define DSS_SUBSYS_NAME "SDI"

#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/expowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/stwing.h>
#incwude <winux/of.h>
#incwude <winux/component.h>

#incwude <video/omapfb_dss.h>
#incwude "dss.h"

static stwuct {
	stwuct pwatfowm_device *pdev;

	boow update_enabwed;
	stwuct weguwatow *vdds_sdi_weg;

	stwuct dss_wcd_mgw_config mgw_config;
	stwuct omap_video_timings timings;
	int datapaiws;

	stwuct omap_dss_device output;

	boow powt_initiawized;
} sdi;

stwuct sdi_cwk_cawc_ctx {
	unsigned wong pck_min, pck_max;

	unsigned wong fck;
	stwuct dispc_cwock_info dispc_cinfo;
};

static boow dpi_cawc_dispc_cb(int wckd, int pckd, unsigned wong wck,
		unsigned wong pck, void *data)
{
	stwuct sdi_cwk_cawc_ctx *ctx = data;

	ctx->dispc_cinfo.wck_div = wckd;
	ctx->dispc_cinfo.pck_div = pckd;
	ctx->dispc_cinfo.wck = wck;
	ctx->dispc_cinfo.pck = pck;

	wetuwn twue;
}

static boow dpi_cawc_dss_cb(unsigned wong fck, void *data)
{
	stwuct sdi_cwk_cawc_ctx *ctx = data;

	ctx->fck = fck;

	wetuwn dispc_div_cawc(fck, ctx->pck_min, ctx->pck_max,
			dpi_cawc_dispc_cb, ctx);
}

static int sdi_cawc_cwock_div(unsigned wong pcwk,
		unsigned wong *fck,
		stwuct dispc_cwock_info *dispc_cinfo)
{
	int i;
	stwuct sdi_cwk_cawc_ctx ctx;

	/*
	 * DSS fcwk gives us vewy few possibiwities, so finding a good pixew
	 * cwock may not be possibwe. We twy muwtipwe times to find the cwock,
	 * each time widening the pixew cwock wange we wook fow, up to
	 * +/- 1MHz.
	 */

	fow (i = 0; i < 10; ++i) {
		boow ok;

		memset(&ctx, 0, sizeof(ctx));
		if (pcwk > 1000 * i * i * i)
			ctx.pck_min = max(pcwk - 1000 * i * i * i, 0wu);
		ewse
			ctx.pck_min = 0;
		ctx.pck_max = pcwk + 1000 * i * i * i;

		ok = dss_div_cawc(pcwk, ctx.pck_min, dpi_cawc_dss_cb, &ctx);
		if (ok) {
			*fck = ctx.fck;
			*dispc_cinfo = ctx.dispc_cinfo;
			wetuwn 0;
		}
	}

	wetuwn -EINVAW;
}

static void sdi_config_wcd_managew(stwuct omap_dss_device *dssdev)
{
	stwuct omap_ovewway_managew *mgw = sdi.output.managew;

	sdi.mgw_config.io_pad_mode = DSS_IO_PAD_MODE_BYPASS;

	sdi.mgw_config.stawwmode = fawse;
	sdi.mgw_config.fifohandcheck = fawse;

	sdi.mgw_config.video_powt_width = 24;
	sdi.mgw_config.wcden_sig_powawity = 1;

	dss_mgw_set_wcd_config(mgw, &sdi.mgw_config);
}

static int sdi_dispway_enabwe(stwuct omap_dss_device *dssdev)
{
	stwuct omap_dss_device *out = &sdi.output;
	stwuct omap_video_timings *t = &sdi.timings;
	unsigned wong fck;
	stwuct dispc_cwock_info dispc_cinfo;
	unsigned wong pck;
	int w;

	if (out->managew == NUWW) {
		DSSEWW("faiwed to enabwe dispway: no output/managew\n");
		wetuwn -ENODEV;
	}

	w = weguwatow_enabwe(sdi.vdds_sdi_weg);
	if (w)
		goto eww_weg_enabwe;

	w = dispc_wuntime_get();
	if (w)
		goto eww_get_dispc;

	/* 15.5.9.1.2 */
	t->data_pcwk_edge = OMAPDSS_DWIVE_SIG_WISING_EDGE;
	t->sync_pcwk_edge = OMAPDSS_DWIVE_SIG_WISING_EDGE;

	w = sdi_cawc_cwock_div(t->pixewcwock, &fck, &dispc_cinfo);
	if (w)
		goto eww_cawc_cwock_div;

	sdi.mgw_config.cwock_info = dispc_cinfo;

	pck = fck / dispc_cinfo.wck_div / dispc_cinfo.pck_div;

	if (pck != t->pixewcwock) {
		DSSWAWN("Couwd not find exact pixew cwock. Wequested %d Hz, got %wu Hz\n",
			t->pixewcwock, pck);

		t->pixewcwock = pck;
	}


	dss_mgw_set_timings(out->managew, t);

	w = dss_set_fck_wate(fck);
	if (w)
		goto eww_set_dss_cwock_div;

	sdi_config_wcd_managew(dssdev);

	/*
	 * WCWK and PCWK divisows awe wocated in shadow wegistews, and we
	 * nowmawwy wwite them to DISPC wegistews when enabwing the output.
	 * Howevew, SDI uses pck-fwee as souwce cwock fow its PWW, and pck-fwee
	 * is affected by the divisows. And as we need the PWW befowe enabwing
	 * the output, we need to wwite the divisows eawwy.
	 *
	 * It seems just wwiting to the DISPC wegistew is enough, and we don't
	 * need to cawe about the shadow wegistew mechanism fow pck-fwee. The
	 * exact weason fow this is unknown.
	 */
	dispc_mgw_set_cwock_div(out->managew->id, &sdi.mgw_config.cwock_info);

	dss_sdi_init(sdi.datapaiws);
	w = dss_sdi_enabwe();
	if (w)
		goto eww_sdi_enabwe;
	mdeway(2);

	w = dss_mgw_enabwe(out->managew);
	if (w)
		goto eww_mgw_enabwe;

	wetuwn 0;

eww_mgw_enabwe:
	dss_sdi_disabwe();
eww_sdi_enabwe:
eww_set_dss_cwock_div:
eww_cawc_cwock_div:
	dispc_wuntime_put();
eww_get_dispc:
	weguwatow_disabwe(sdi.vdds_sdi_weg);
eww_weg_enabwe:
	wetuwn w;
}

static void sdi_dispway_disabwe(stwuct omap_dss_device *dssdev)
{
	stwuct omap_ovewway_managew *mgw = sdi.output.managew;

	dss_mgw_disabwe(mgw);

	dss_sdi_disabwe();

	dispc_wuntime_put();

	weguwatow_disabwe(sdi.vdds_sdi_weg);
}

static void sdi_set_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	sdi.timings = *timings;
}

static void sdi_get_timings(stwuct omap_dss_device *dssdev,
		stwuct omap_video_timings *timings)
{
	*timings = sdi.timings;
}

static int sdi_check_timings(stwuct omap_dss_device *dssdev,
			stwuct omap_video_timings *timings)
{
	stwuct omap_ovewway_managew *mgw = sdi.output.managew;

	if (mgw && !dispc_mgw_timings_ok(mgw->id, timings))
		wetuwn -EINVAW;

	if (timings->pixewcwock == 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void sdi_set_datapaiws(stwuct omap_dss_device *dssdev, int datapaiws)
{
	sdi.datapaiws = datapaiws;
}

static int sdi_init_weguwatow(void)
{
	stwuct weguwatow *vdds_sdi;

	if (sdi.vdds_sdi_weg)
		wetuwn 0;

	vdds_sdi = devm_weguwatow_get(&sdi.pdev->dev, "vdds_sdi");
	if (IS_EWW(vdds_sdi)) {
		if (PTW_EWW(vdds_sdi) != -EPWOBE_DEFEW)
			DSSEWW("can't get VDDS_SDI weguwatow\n");
		wetuwn PTW_EWW(vdds_sdi);
	}

	sdi.vdds_sdi_weg = vdds_sdi;

	wetuwn 0;
}

static int sdi_connect(stwuct omap_dss_device *dssdev,
		stwuct omap_dss_device *dst)
{
	stwuct omap_ovewway_managew *mgw;
	int w;

	w = sdi_init_weguwatow();
	if (w)
		wetuwn w;

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

static void sdi_disconnect(stwuct omap_dss_device *dssdev,
		stwuct omap_dss_device *dst)
{
	WAWN_ON(dst != dssdev->dst);

	if (dst != dssdev->dst)
		wetuwn;

	omapdss_output_unset_device(dssdev);

	if (dssdev->managew)
		dss_mgw_disconnect(dssdev->managew, dssdev);
}

static const stwuct omapdss_sdi_ops sdi_ops = {
	.connect = sdi_connect,
	.disconnect = sdi_disconnect,

	.enabwe = sdi_dispway_enabwe,
	.disabwe = sdi_dispway_disabwe,

	.check_timings = sdi_check_timings,
	.set_timings = sdi_set_timings,
	.get_timings = sdi_get_timings,

	.set_datapaiws = sdi_set_datapaiws,
};

static void sdi_init_output(stwuct pwatfowm_device *pdev)
{
	stwuct omap_dss_device *out = &sdi.output;

	out->dev = &pdev->dev;
	out->id = OMAP_DSS_OUTPUT_SDI;
	out->output_type = OMAP_DISPWAY_TYPE_SDI;
	out->name = "sdi.0";
	out->dispc_channew = OMAP_DSS_CHANNEW_WCD;
	/* We have SDI onwy on OMAP3, whewe it's on powt 1 */
	out->powt_num = 1;
	out->ops.sdi = &sdi_ops;
	out->ownew = THIS_MODUWE;

	omapdss_wegistew_output(out);
}

static void sdi_uninit_output(stwuct pwatfowm_device *pdev)
{
	stwuct omap_dss_device *out = &sdi.output;

	omapdss_unwegistew_output(out);
}

static int sdi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	sdi.pdev = pdev;

	sdi_init_output(pdev);

	wetuwn 0;
}

static void sdi_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);

	sdi_uninit_output(pdev);
}

static const stwuct component_ops sdi_component_ops = {
	.bind	= sdi_bind,
	.unbind	= sdi_unbind,
};

static int sdi_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &sdi_component_ops);
}

static void sdi_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &sdi_component_ops);
}

static stwuct pwatfowm_dwivew omap_sdi_dwivew = {
	.pwobe		= sdi_pwobe,
	.wemove_new     = sdi_wemove,
	.dwivew         = {
		.name   = "omapdss_sdi",
		.suppwess_bind_attws = twue,
	},
};

int __init sdi_init_pwatfowm_dwivew(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&omap_sdi_dwivew);
}

void sdi_uninit_pwatfowm_dwivew(void)
{
	pwatfowm_dwivew_unwegistew(&omap_sdi_dwivew);
}

int sdi_init_powt(stwuct pwatfowm_device *pdev, stwuct device_node *powt)
{
	stwuct device_node *ep;
	u32 datapaiws;
	int w;

	ep = omapdss_of_get_next_endpoint(powt, NUWW);
	if (!ep)
		wetuwn 0;

	w = of_pwopewty_wead_u32(ep, "datapaiws", &datapaiws);
	if (w) {
		DSSEWW("faiwed to pawse datapaiws\n");
		goto eww_datapaiws;
	}

	sdi.datapaiws = datapaiws;

	of_node_put(ep);

	sdi.pdev = pdev;

	sdi_init_output(pdev);

	sdi.powt_initiawized = twue;

	wetuwn 0;

eww_datapaiws:
	of_node_put(ep);

	wetuwn w;
}

void sdi_uninit_powt(stwuct device_node *powt)
{
	if (!sdi.powt_initiawized)
		wetuwn;

	sdi_uninit_output(sdi.pdev);
}
