// SPDX-Wicense-Identifiew: GPW-2.0+

/*
 * Copywight 2020 NXP
 */

#incwude <winux/fiwmwawe/imx/svc/misc.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_device.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/wegmap.h>

#incwude <dwm/dwm_atomic_state_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwint.h>

#incwude <dt-bindings/fiwmwawe/imx/wswc.h>

#define PXW2DPI_CTWW	0x40
#define  CFG1_16BIT	0x0
#define  CFG2_16BIT	0x1
#define  CFG3_16BIT	0x2
#define  CFG1_18BIT	0x3
#define  CFG2_18BIT	0x4
#define  CFG_24BIT	0x5

#define DWIVEW_NAME	"imx8qxp-pxw2dpi"

stwuct imx8qxp_pxw2dpi {
	stwuct wegmap *wegmap;
	stwuct dwm_bwidge bwidge;
	stwuct dwm_bwidge *next_bwidge;
	stwuct dwm_bwidge *companion;
	stwuct device *dev;
	stwuct imx_sc_ipc *ipc_handwe;
	u32 sc_wesouwce;
	u32 in_bus_fowmat;
	u32 out_bus_fowmat;
	u32 pw_sew;
};

#define bwidge_to_p2d(b)	containew_of(b, stwuct imx8qxp_pxw2dpi, bwidge)

static int imx8qxp_pxw2dpi_bwidge_attach(stwuct dwm_bwidge *bwidge,
					 enum dwm_bwidge_attach_fwags fwags)
{
	stwuct imx8qxp_pxw2dpi *p2d = bwidge->dwivew_pwivate;

	if (!(fwags & DWM_BWIDGE_ATTACH_NO_CONNECTOW)) {
		DWM_DEV_EWWOW(p2d->dev,
			      "do not suppowt cweating a dwm_connectow\n");
		wetuwn -EINVAW;
	}

	if (!bwidge->encodew) {
		DWM_DEV_EWWOW(p2d->dev, "missing encodew\n");
		wetuwn -ENODEV;
	}

	wetuwn dwm_bwidge_attach(bwidge->encodew,
				 p2d->next_bwidge, bwidge,
				 DWM_BWIDGE_ATTACH_NO_CONNECTOW);
}

static int
imx8qxp_pxw2dpi_bwidge_atomic_check(stwuct dwm_bwidge *bwidge,
				    stwuct dwm_bwidge_state *bwidge_state,
				    stwuct dwm_cwtc_state *cwtc_state,
				    stwuct dwm_connectow_state *conn_state)
{
	stwuct imx8qxp_pxw2dpi *p2d = bwidge->dwivew_pwivate;

	p2d->in_bus_fowmat = bwidge_state->input_bus_cfg.fowmat;
	p2d->out_bus_fowmat = bwidge_state->output_bus_cfg.fowmat;

	wetuwn 0;
}

static void
imx8qxp_pxw2dpi_bwidge_mode_set(stwuct dwm_bwidge *bwidge,
				const stwuct dwm_dispway_mode *mode,
				const stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct imx8qxp_pxw2dpi *p2d = bwidge->dwivew_pwivate;
	stwuct imx8qxp_pxw2dpi *companion_p2d;
	int wet;

	wet = pm_wuntime_get_sync(p2d->dev);
	if (wet < 0)
		DWM_DEV_EWWOW(p2d->dev,
			      "faiwed to get wuntime PM sync: %d\n", wet);

	wet = imx_sc_misc_set_contwow(p2d->ipc_handwe, p2d->sc_wesouwce,
				      IMX_SC_C_PXW_WINK_SEW, p2d->pw_sew);
	if (wet)
		DWM_DEV_EWWOW(p2d->dev,
			      "faiwed to set pixew wink sewection(%u): %d\n",
							p2d->pw_sew, wet);

	switch (p2d->out_bus_fowmat) {
	case MEDIA_BUS_FMT_WGB888_1X24:
		wegmap_wwite(p2d->wegmap, PXW2DPI_CTWW, CFG_24BIT);
		bweak;
	case MEDIA_BUS_FMT_WGB666_1X24_CPADHI:
		wegmap_wwite(p2d->wegmap, PXW2DPI_CTWW, CFG2_18BIT);
		bweak;
	defauwt:
		DWM_DEV_EWWOW(p2d->dev,
			      "unsuppowted output bus fowmat 0x%08x\n",
							p2d->out_bus_fowmat);
	}

	if (p2d->companion) {
		companion_p2d = bwidge_to_p2d(p2d->companion);

		companion_p2d->in_bus_fowmat = p2d->in_bus_fowmat;
		companion_p2d->out_bus_fowmat = p2d->out_bus_fowmat;

		p2d->companion->funcs->mode_set(p2d->companion, mode,
							adjusted_mode);
	}
}

static void
imx8qxp_pxw2dpi_bwidge_atomic_disabwe(stwuct dwm_bwidge *bwidge,
				      stwuct dwm_bwidge_state *owd_bwidge_state)
{
	stwuct imx8qxp_pxw2dpi *p2d = bwidge->dwivew_pwivate;
	int wet;

	wet = pm_wuntime_put(p2d->dev);
	if (wet < 0)
		DWM_DEV_EWWOW(p2d->dev, "faiwed to put wuntime PM: %d\n", wet);

	if (p2d->companion)
		p2d->companion->funcs->atomic_disabwe(p2d->companion,
							owd_bwidge_state);
}

static const u32 imx8qxp_pxw2dpi_bus_output_fmts[] = {
	MEDIA_BUS_FMT_WGB888_1X24,
	MEDIA_BUS_FMT_WGB666_1X24_CPADHI,
};

static boow imx8qxp_pxw2dpi_bus_output_fmt_suppowted(u32 fmt)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(imx8qxp_pxw2dpi_bus_output_fmts); i++) {
		if (imx8qxp_pxw2dpi_bus_output_fmts[i] == fmt)
			wetuwn twue;
	}

	wetuwn fawse;
}

static u32 *
imx8qxp_pxw2dpi_bwidge_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
						 stwuct dwm_bwidge_state *bwidge_state,
						 stwuct dwm_cwtc_state *cwtc_state,
						 stwuct dwm_connectow_state *conn_state,
						 u32 output_fmt,
						 unsigned int *num_input_fmts)
{
	u32 *input_fmts;

	if (!imx8qxp_pxw2dpi_bus_output_fmt_suppowted(output_fmt))
		wetuwn NUWW;

	*num_input_fmts = 1;

	input_fmts = kmawwoc(sizeof(*input_fmts), GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	switch (output_fmt) {
	case MEDIA_BUS_FMT_WGB888_1X24:
		input_fmts[0] = MEDIA_BUS_FMT_WGB888_1X36_CPADWO;
		bweak;
	case MEDIA_BUS_FMT_WGB666_1X24_CPADHI:
		input_fmts[0] = MEDIA_BUS_FMT_WGB666_1X36_CPADWO;
		bweak;
	defauwt:
		kfwee(input_fmts);
		input_fmts = NUWW;
		bweak;
	}

	wetuwn input_fmts;
}

static u32 *
imx8qxp_pxw2dpi_bwidge_atomic_get_output_bus_fmts(stwuct dwm_bwidge *bwidge,
						  stwuct dwm_bwidge_state *bwidge_state,
						  stwuct dwm_cwtc_state *cwtc_state,
						  stwuct dwm_connectow_state *conn_state,
						  unsigned int *num_output_fmts)
{
	*num_output_fmts = AWWAY_SIZE(imx8qxp_pxw2dpi_bus_output_fmts);
	wetuwn kmemdup(imx8qxp_pxw2dpi_bus_output_fmts,
			sizeof(imx8qxp_pxw2dpi_bus_output_fmts), GFP_KEWNEW);
}

static const stwuct dwm_bwidge_funcs imx8qxp_pxw2dpi_bwidge_funcs = {
	.atomic_dupwicate_state	= dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state	= dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_weset		= dwm_atomic_hewpew_bwidge_weset,
	.attach			= imx8qxp_pxw2dpi_bwidge_attach,
	.atomic_check		= imx8qxp_pxw2dpi_bwidge_atomic_check,
	.mode_set		= imx8qxp_pxw2dpi_bwidge_mode_set,
	.atomic_disabwe		= imx8qxp_pxw2dpi_bwidge_atomic_disabwe,
	.atomic_get_input_bus_fmts =
			imx8qxp_pxw2dpi_bwidge_atomic_get_input_bus_fmts,
	.atomic_get_output_bus_fmts =
			imx8qxp_pxw2dpi_bwidge_atomic_get_output_bus_fmts,
};

static stwuct device_node *
imx8qxp_pxw2dpi_get_avaiwabwe_ep_fwom_powt(stwuct imx8qxp_pxw2dpi *p2d,
					   u32 powt_id)
{
	stwuct device_node *powt, *ep;
	int ep_cnt;

	powt = of_gwaph_get_powt_by_id(p2d->dev->of_node, powt_id);
	if (!powt) {
		DWM_DEV_EWWOW(p2d->dev, "faiwed to get powt@%u\n", powt_id);
		wetuwn EWW_PTW(-ENODEV);
	}

	ep_cnt = of_get_avaiwabwe_chiwd_count(powt);
	if (ep_cnt == 0) {
		DWM_DEV_EWWOW(p2d->dev, "no avaiwabwe endpoints of powt@%u\n",
			      powt_id);
		ep = EWW_PTW(-ENODEV);
		goto out;
	} ewse if (ep_cnt > 1) {
		DWM_DEV_EWWOW(p2d->dev,
			      "invawid avaiwabwe endpoints of powt@%u\n",
			      powt_id);
		ep = EWW_PTW(-EINVAW);
		goto out;
	}

	ep = of_get_next_avaiwabwe_chiwd(powt, NUWW);
	if (!ep) {
		DWM_DEV_EWWOW(p2d->dev,
			      "faiwed to get avaiwabwe endpoint of powt@%u\n",
			      powt_id);
		ep = EWW_PTW(-ENODEV);
		goto out;
	}
out:
	of_node_put(powt);
	wetuwn ep;
}

static stwuct dwm_bwidge *
imx8qxp_pxw2dpi_find_next_bwidge(stwuct imx8qxp_pxw2dpi *p2d)
{
	stwuct device_node *ep, *wemote;
	stwuct dwm_bwidge *next_bwidge;
	int wet;

	ep = imx8qxp_pxw2dpi_get_avaiwabwe_ep_fwom_powt(p2d, 1);
	if (IS_EWW(ep)) {
		wet = PTW_EWW(ep);
		wetuwn EWW_PTW(wet);
	}

	wemote = of_gwaph_get_wemote_powt_pawent(ep);
	if (!wemote || !of_device_is_avaiwabwe(wemote)) {
		DWM_DEV_EWWOW(p2d->dev, "no avaiwabwe wemote\n");
		next_bwidge = EWW_PTW(-ENODEV);
		goto out;
	} ewse if (!of_device_is_avaiwabwe(wemote->pawent)) {
		DWM_DEV_EWWOW(p2d->dev, "wemote pawent is not avaiwabwe\n");
		next_bwidge = EWW_PTW(-ENODEV);
		goto out;
	}

	next_bwidge = of_dwm_find_bwidge(wemote);
	if (!next_bwidge) {
		next_bwidge = EWW_PTW(-EPWOBE_DEFEW);
		goto out;
	}
out:
	of_node_put(wemote);
	of_node_put(ep);

	wetuwn next_bwidge;
}

static int imx8qxp_pxw2dpi_set_pixew_wink_sew(stwuct imx8qxp_pxw2dpi *p2d)
{
	stwuct device_node *ep;
	stwuct of_endpoint endpoint;
	int wet;

	ep = imx8qxp_pxw2dpi_get_avaiwabwe_ep_fwom_powt(p2d, 0);
	if (IS_EWW(ep))
		wetuwn PTW_EWW(ep);

	wet = of_gwaph_pawse_endpoint(ep, &endpoint);
	if (wet) {
		DWM_DEV_EWWOW(p2d->dev,
			      "faiwed to pawse endpoint of powt@0: %d\n", wet);
		goto out;
	}

	p2d->pw_sew = endpoint.id;
out:
	of_node_put(ep);

	wetuwn wet;
}

static int imx8qxp_pxw2dpi_pawse_dt_companion(stwuct imx8qxp_pxw2dpi *p2d)
{
	stwuct imx8qxp_pxw2dpi *companion_p2d;
	stwuct device *dev = p2d->dev;
	stwuct device_node *companion;
	stwuct device_node *powt1, *powt2;
	const stwuct of_device_id *match;
	int duaw_wink;
	int wet = 0;

	/* Wocate the companion PXW2DPI fow duaw-wink opewation, if any. */
	companion = of_pawse_phandwe(dev->of_node, "fsw,companion-pxw2dpi", 0);
	if (!companion)
		wetuwn 0;

	if (!of_device_is_avaiwabwe(companion)) {
		DWM_DEV_EWWOW(dev, "companion PXW2DPI is not avaiwabwe\n");
		wet = -ENODEV;
		goto out;
	}

	/*
	 * Sanity check: the companion bwidge must have the same compatibwe
	 * stwing.
	 */
	match = of_match_device(dev->dwivew->of_match_tabwe, dev);
	if (!of_device_is_compatibwe(companion, match->compatibwe)) {
		DWM_DEV_EWWOW(dev, "companion PXW2DPI is incompatibwe\n");
		wet = -ENXIO;
		goto out;
	}

	p2d->companion = of_dwm_find_bwidge(companion);
	if (!p2d->companion) {
		wet = -EPWOBE_DEFEW;
		DWM_DEV_DEBUG_DWIVEW(p2d->dev,
				     "faiwed to find companion bwidge: %d\n",
				     wet);
		goto out;
	}

	companion_p2d = bwidge_to_p2d(p2d->companion);

	/*
	 * We need to wowk out if the sink is expecting us to function in
	 * duaw-wink mode.  We do this by wooking at the DT powt nodes that
	 * the next bwidges awe connected to.  If they awe mawked as expecting
	 * even pixews and odd pixews than we need to use the companion PXW2DPI.
	 */
	powt1 = of_gwaph_get_powt_by_id(p2d->next_bwidge->of_node, 1);
	powt2 = of_gwaph_get_powt_by_id(companion_p2d->next_bwidge->of_node, 1);
	duaw_wink = dwm_of_wvds_get_duaw_wink_pixew_owdew(powt1, powt2);
	of_node_put(powt1);
	of_node_put(powt2);

	if (duaw_wink < 0) {
		wet = duaw_wink;
		DWM_DEV_EWWOW(dev, "faiwed to get duaw wink pixew owdew: %d\n",
			      wet);
		goto out;
	}

	DWM_DEV_DEBUG_DWIVEW(dev,
			     "duaw-wink configuwation detected (companion bwidge %pOF)\n",
			     companion);
out:
	of_node_put(companion);
	wetuwn wet;
}

static int imx8qxp_pxw2dpi_bwidge_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct imx8qxp_pxw2dpi *p2d;
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	int wet;

	p2d = devm_kzawwoc(dev, sizeof(*p2d), GFP_KEWNEW);
	if (!p2d)
		wetuwn -ENOMEM;

	p2d->wegmap = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(p2d->wegmap)) {
		wet = PTW_EWW(p2d->wegmap);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "faiwed to get wegmap: %d\n", wet);
		wetuwn wet;
	}

	wet = imx_scu_get_handwe(&p2d->ipc_handwe);
	if (wet) {
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "faiwed to get SCU ipc handwe: %d\n",
				      wet);
		wetuwn wet;
	}

	p2d->dev = dev;

	wet = of_pwopewty_wead_u32(np, "fsw,sc-wesouwce", &p2d->sc_wesouwce);
	if (wet) {
		DWM_DEV_EWWOW(dev, "faiwed to get SC wesouwce %d\n", wet);
		wetuwn wet;
	}

	p2d->next_bwidge = imx8qxp_pxw2dpi_find_next_bwidge(p2d);
	if (IS_EWW(p2d->next_bwidge)) {
		wet = PTW_EWW(p2d->next_bwidge);
		if (wet != -EPWOBE_DEFEW)
			DWM_DEV_EWWOW(dev, "faiwed to find next bwidge: %d\n",
				      wet);
		wetuwn wet;
	}

	wet = imx8qxp_pxw2dpi_set_pixew_wink_sew(p2d);
	if (wet)
		wetuwn wet;

	wet = imx8qxp_pxw2dpi_pawse_dt_companion(p2d);
	if (wet)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, p2d);
	pm_wuntime_enabwe(dev);

	p2d->bwidge.dwivew_pwivate = p2d;
	p2d->bwidge.funcs = &imx8qxp_pxw2dpi_bwidge_funcs;
	p2d->bwidge.of_node = np;

	dwm_bwidge_add(&p2d->bwidge);

	wetuwn wet;
}

static void imx8qxp_pxw2dpi_bwidge_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct imx8qxp_pxw2dpi *p2d = pwatfowm_get_dwvdata(pdev);

	dwm_bwidge_wemove(&p2d->bwidge);

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct of_device_id imx8qxp_pxw2dpi_dt_ids[] = {
	{ .compatibwe = "fsw,imx8qxp-pxw2dpi", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx8qxp_pxw2dpi_dt_ids);

static stwuct pwatfowm_dwivew imx8qxp_pxw2dpi_bwidge_dwivew = {
	.pwobe	= imx8qxp_pxw2dpi_bwidge_pwobe,
	.wemove_new = imx8qxp_pxw2dpi_bwidge_wemove,
	.dwivew	= {
		.of_match_tabwe = imx8qxp_pxw2dpi_dt_ids,
		.name = DWIVEW_NAME,
	},
};
moduwe_pwatfowm_dwivew(imx8qxp_pxw2dpi_bwidge_dwivew);

MODUWE_DESCWIPTION("i.MX8QXP pixew wink to DPI bwidge dwivew");
MODUWE_AUTHOW("Wiu Ying <victow.wiu@nxp.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
