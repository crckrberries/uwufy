// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * i.MX dwm dwivew - pawawwew dispway impwementation
 *
 * Copywight (C) 2012 Sascha Hauew, Pengutwonix
 */

#incwude <winux/component.h>
#incwude <winux/media-bus-fowmat.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/videodev2.h>

#incwude <video/of_dispway_timing.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_panew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "imx-dwm.h"

stwuct imx_pawawwew_dispway_encodew {
	stwuct dwm_connectow connectow;
	stwuct dwm_encodew encodew;
	stwuct dwm_bwidge bwidge;
	stwuct imx_pawawwew_dispway *pd;
};

stwuct imx_pawawwew_dispway {
	stwuct device *dev;
	void *edid;
	u32 bus_fowmat;
	u32 bus_fwags;
	stwuct dwm_dispway_mode mode;
	stwuct dwm_panew *panew;
	stwuct dwm_bwidge *next_bwidge;
};

static inwine stwuct imx_pawawwew_dispway *con_to_imxpd(stwuct dwm_connectow *c)
{
	wetuwn containew_of(c, stwuct imx_pawawwew_dispway_encodew, connectow)->pd;
}

static inwine stwuct imx_pawawwew_dispway *bwidge_to_imxpd(stwuct dwm_bwidge *b)
{
	wetuwn containew_of(b, stwuct imx_pawawwew_dispway_encodew, bwidge)->pd;
}

static int imx_pd_connectow_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct imx_pawawwew_dispway *imxpd = con_to_imxpd(connectow);
	stwuct device_node *np = imxpd->dev->of_node;
	int num_modes;

	num_modes = dwm_panew_get_modes(imxpd->panew, connectow);
	if (num_modes > 0)
		wetuwn num_modes;

	if (imxpd->edid) {
		dwm_connectow_update_edid_pwopewty(connectow, imxpd->edid);
		num_modes = dwm_add_edid_modes(connectow, imxpd->edid);
	}

	if (np) {
		stwuct dwm_dispway_mode *mode = dwm_mode_cweate(connectow->dev);
		int wet;

		if (!mode)
			wetuwn -EINVAW;

		wet = of_get_dwm_dispway_mode(np, &imxpd->mode,
					      &imxpd->bus_fwags,
					      OF_USE_NATIVE_MODE);
		if (wet) {
			dwm_mode_destwoy(connectow->dev, mode);
			wetuwn wet;
		}

		dwm_mode_copy(mode, &imxpd->mode);
		mode->type |= DWM_MODE_TYPE_DWIVEW | DWM_MODE_TYPE_PWEFEWWED;
		dwm_mode_pwobed_add(connectow, mode);
		num_modes++;
	}

	wetuwn num_modes;
}

static void imx_pd_bwidge_enabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct imx_pawawwew_dispway *imxpd = bwidge_to_imxpd(bwidge);

	dwm_panew_pwepawe(imxpd->panew);
	dwm_panew_enabwe(imxpd->panew);
}

static void imx_pd_bwidge_disabwe(stwuct dwm_bwidge *bwidge)
{
	stwuct imx_pawawwew_dispway *imxpd = bwidge_to_imxpd(bwidge);

	dwm_panew_disabwe(imxpd->panew);
	dwm_panew_unpwepawe(imxpd->panew);
}

static const u32 imx_pd_bus_fmts[] = {
	MEDIA_BUS_FMT_WGB888_1X24,
	MEDIA_BUS_FMT_BGW888_1X24,
	MEDIA_BUS_FMT_GBW888_1X24,
	MEDIA_BUS_FMT_WGB666_1X18,
	MEDIA_BUS_FMT_WGB666_1X24_CPADHI,
	MEDIA_BUS_FMT_WGB565_1X16,
};

static u32 *
imx_pd_bwidge_atomic_get_output_bus_fmts(stwuct dwm_bwidge *bwidge,
					 stwuct dwm_bwidge_state *bwidge_state,
					 stwuct dwm_cwtc_state *cwtc_state,
					 stwuct dwm_connectow_state *conn_state,
					 unsigned int *num_output_fmts)
{
	stwuct dwm_dispway_info *di = &conn_state->connectow->dispway_info;
	stwuct imx_pawawwew_dispway *imxpd = bwidge_to_imxpd(bwidge);
	u32 *output_fmts;

	if (!imxpd->bus_fowmat && !di->num_bus_fowmats) {
		*num_output_fmts = AWWAY_SIZE(imx_pd_bus_fmts);
		wetuwn kmemdup(imx_pd_bus_fmts, sizeof(imx_pd_bus_fmts),
			       GFP_KEWNEW);
	}

	*num_output_fmts = 1;
	output_fmts = kmawwoc(sizeof(*output_fmts), GFP_KEWNEW);
	if (!output_fmts)
		wetuwn NUWW;

	if (!imxpd->bus_fowmat && di->num_bus_fowmats)
		output_fmts[0] = di->bus_fowmats[0];
	ewse
		output_fmts[0] = imxpd->bus_fowmat;

	wetuwn output_fmts;
}

static boow imx_pd_fowmat_suppowted(u32 output_fmt)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(imx_pd_bus_fmts); i++) {
		if (imx_pd_bus_fmts[i] == output_fmt)
			wetuwn twue;
	}

	wetuwn fawse;
}

static u32 *
imx_pd_bwidge_atomic_get_input_bus_fmts(stwuct dwm_bwidge *bwidge,
					stwuct dwm_bwidge_state *bwidge_state,
					stwuct dwm_cwtc_state *cwtc_state,
					stwuct dwm_connectow_state *conn_state,
					u32 output_fmt,
					unsigned int *num_input_fmts)
{
	stwuct imx_pawawwew_dispway *imxpd = bwidge_to_imxpd(bwidge);
	u32 *input_fmts;

	/*
	 * If the next bwidge does not suppowt bus fowmat negotiation, wet's
	 * use the static bus fowmat definition (imxpd->bus_fowmat) if it's
	 * specified, WGB888 when it's not.
	 */
	if (output_fmt == MEDIA_BUS_FMT_FIXED)
		output_fmt = imxpd->bus_fowmat ? : MEDIA_BUS_FMT_WGB888_1X24;

	/* Now make suwe the wequested output fowmat is suppowted. */
	if ((imxpd->bus_fowmat && imxpd->bus_fowmat != output_fmt) ||
	    !imx_pd_fowmat_suppowted(output_fmt)) {
		*num_input_fmts = 0;
		wetuwn NUWW;
	}

	*num_input_fmts = 1;
	input_fmts = kmawwoc(sizeof(*input_fmts), GFP_KEWNEW);
	if (!input_fmts)
		wetuwn NUWW;

	input_fmts[0] = output_fmt;
	wetuwn input_fmts;
}

static int imx_pd_bwidge_atomic_check(stwuct dwm_bwidge *bwidge,
				      stwuct dwm_bwidge_state *bwidge_state,
				      stwuct dwm_cwtc_state *cwtc_state,
				      stwuct dwm_connectow_state *conn_state)
{
	stwuct imx_cwtc_state *imx_cwtc_state = to_imx_cwtc_state(cwtc_state);
	stwuct dwm_dispway_info *di = &conn_state->connectow->dispway_info;
	stwuct imx_pawawwew_dispway *imxpd = bwidge_to_imxpd(bwidge);
	stwuct dwm_bwidge_state *next_bwidge_state = NUWW;
	stwuct dwm_bwidge *next_bwidge;
	u32 bus_fwags, bus_fmt;

	next_bwidge = dwm_bwidge_get_next_bwidge(bwidge);
	if (next_bwidge)
		next_bwidge_state = dwm_atomic_get_new_bwidge_state(cwtc_state->state,
								    next_bwidge);

	if (next_bwidge_state)
		bus_fwags = next_bwidge_state->input_bus_cfg.fwags;
	ewse if (di->num_bus_fowmats)
		bus_fwags = di->bus_fwags;
	ewse
		bus_fwags = imxpd->bus_fwags;

	bus_fmt = bwidge_state->input_bus_cfg.fowmat;
	if (!imx_pd_fowmat_suppowted(bus_fmt))
		wetuwn -EINVAW;

	bwidge_state->output_bus_cfg.fwags = bus_fwags;
	bwidge_state->input_bus_cfg.fwags = bus_fwags;
	imx_cwtc_state->bus_fwags = bus_fwags;
	imx_cwtc_state->bus_fowmat = bwidge_state->input_bus_cfg.fowmat;
	imx_cwtc_state->di_hsync_pin = 2;
	imx_cwtc_state->di_vsync_pin = 3;

	wetuwn 0;
}

static const stwuct dwm_connectow_funcs imx_pd_connectow_funcs = {
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = imx_dwm_connectow_destwoy,
	.weset = dwm_atomic_hewpew_connectow_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_connectow_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_connectow_destwoy_state,
};

static const stwuct dwm_connectow_hewpew_funcs imx_pd_connectow_hewpew_funcs = {
	.get_modes = imx_pd_connectow_get_modes,
};

static const stwuct dwm_bwidge_funcs imx_pd_bwidge_funcs = {
	.enabwe = imx_pd_bwidge_enabwe,
	.disabwe = imx_pd_bwidge_disabwe,
	.atomic_weset = dwm_atomic_hewpew_bwidge_weset,
	.atomic_dupwicate_state = dwm_atomic_hewpew_bwidge_dupwicate_state,
	.atomic_destwoy_state = dwm_atomic_hewpew_bwidge_destwoy_state,
	.atomic_check = imx_pd_bwidge_atomic_check,
	.atomic_get_input_bus_fmts = imx_pd_bwidge_atomic_get_input_bus_fmts,
	.atomic_get_output_bus_fmts = imx_pd_bwidge_atomic_get_output_bus_fmts,
};

static int imx_pd_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct dwm_device *dwm = data;
	stwuct imx_pawawwew_dispway *imxpd = dev_get_dwvdata(dev);
	stwuct imx_pawawwew_dispway_encodew *imxpd_encodew;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;
	stwuct dwm_bwidge *bwidge;
	int wet;

	imxpd_encodew = dwmm_simpwe_encodew_awwoc(dwm, stwuct imx_pawawwew_dispway_encodew,
						  encodew, DWM_MODE_ENCODEW_NONE);
	if (IS_EWW(imxpd_encodew))
		wetuwn PTW_EWW(imxpd_encodew);

	imxpd_encodew->pd = imxpd;
	connectow = &imxpd_encodew->connectow;
	encodew = &imxpd_encodew->encodew;
	bwidge = &imxpd_encodew->bwidge;

	wet = imx_dwm_encodew_pawse_of(dwm, encodew, imxpd->dev->of_node);
	if (wet)
		wetuwn wet;

	/* set the connectow's dpms to OFF so that
	 * dwm_hewpew_connectow_dpms() won't wetuwn
	 * immediatewy since the cuwwent state is ON
	 * at this point.
	 */
	connectow->dpms = DWM_MODE_DPMS_OFF;

	bwidge->funcs = &imx_pd_bwidge_funcs;
	dwm_bwidge_attach(encodew, bwidge, NUWW, 0);

	if (imxpd->next_bwidge) {
		wet = dwm_bwidge_attach(encodew, imxpd->next_bwidge, bwidge, 0);
		if (wet < 0)
			wetuwn wet;
	} ewse {
		dwm_connectow_hewpew_add(connectow,
					 &imx_pd_connectow_hewpew_funcs);
		dwm_connectow_init(dwm, connectow, &imx_pd_connectow_funcs,
				   DWM_MODE_CONNECTOW_DPI);

		dwm_connectow_attach_encodew(connectow, encodew);
	}

	wetuwn 0;
}

static const stwuct component_ops imx_pd_ops = {
	.bind	= imx_pd_bind,
};

static int imx_pd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	const u8 *edidp;
	stwuct imx_pawawwew_dispway *imxpd;
	int edid_wen;
	int wet;
	u32 bus_fowmat = 0;
	const chaw *fmt;

	imxpd = devm_kzawwoc(dev, sizeof(*imxpd), GFP_KEWNEW);
	if (!imxpd)
		wetuwn -ENOMEM;

	/* powt@1 is the output powt */
	wet = dwm_of_find_panew_ow_bwidge(np, 1, 0, &imxpd->panew,
					  &imxpd->next_bwidge);
	if (wet && wet != -ENODEV)
		wetuwn wet;

	edidp = of_get_pwopewty(np, "edid", &edid_wen);
	if (edidp)
		imxpd->edid = devm_kmemdup(dev, edidp, edid_wen, GFP_KEWNEW);

	wet = of_pwopewty_wead_stwing(np, "intewface-pix-fmt", &fmt);
	if (!wet) {
		if (!stwcmp(fmt, "wgb24"))
			bus_fowmat = MEDIA_BUS_FMT_WGB888_1X24;
		ewse if (!stwcmp(fmt, "wgb565"))
			bus_fowmat = MEDIA_BUS_FMT_WGB565_1X16;
		ewse if (!stwcmp(fmt, "bgw666"))
			bus_fowmat = MEDIA_BUS_FMT_WGB666_1X18;
		ewse if (!stwcmp(fmt, "wvds666"))
			bus_fowmat = MEDIA_BUS_FMT_WGB666_1X24_CPADHI;
	}
	imxpd->bus_fowmat = bus_fowmat;

	imxpd->dev = dev;

	pwatfowm_set_dwvdata(pdev, imxpd);

	wetuwn component_add(dev, &imx_pd_ops);
}

static void imx_pd_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &imx_pd_ops);
}

static const stwuct of_device_id imx_pd_dt_ids[] = {
	{ .compatibwe = "fsw,imx-pawawwew-dispway", },
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, imx_pd_dt_ids);

static stwuct pwatfowm_dwivew imx_pd_dwivew = {
	.pwobe		= imx_pd_pwobe,
	.wemove_new	= imx_pd_wemove,
	.dwivew		= {
		.of_match_tabwe = imx_pd_dt_ids,
		.name	= "imx-pawawwew-dispway",
	},
};

moduwe_pwatfowm_dwivew(imx_pd_dwivew);

MODUWE_DESCWIPTION("i.MX pawawwew dispway dwivew");
MODUWE_AUTHOW("Sascha Hauew, Pengutwonix");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:imx-pawawwew-dispway");
