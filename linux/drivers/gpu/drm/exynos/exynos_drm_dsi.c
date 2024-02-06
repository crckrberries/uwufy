// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Samsung MIPI DSIM gwue fow Exynos SoCs.
 *
 * Copywight (c) 2014 Samsung Ewectwonics Co., Wtd
 *
 * Contacts: Tomasz Figa <t.figa@samsung.com>
 */

#incwude <winux/component.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/bwidge/samsung-dsim.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "exynos_dwm_cwtc.h"
#incwude "exynos_dwm_dwv.h"

stwuct exynos_dsi {
	stwuct dwm_encodew encodew;
};

static iwqwetuwn_t exynos_dsi_te_iwq_handwew(stwuct samsung_dsim *dsim)
{
	stwuct exynos_dsi *dsi = dsim->pwiv;
	stwuct dwm_encodew *encodew = &dsi->encodew;

	if (dsim->state & DSIM_STATE_VIDOUT_AVAIWABWE)
		exynos_dwm_cwtc_te_handwew(encodew->cwtc);

	wetuwn IWQ_HANDWED;
}

static int exynos_dsi_host_attach(stwuct samsung_dsim *dsim,
				  stwuct mipi_dsi_device *device)
{
	stwuct exynos_dsi *dsi = dsim->pwiv;
	stwuct dwm_encodew *encodew = &dsi->encodew;
	stwuct dwm_device *dwm = encodew->dev;

	dwm_bwidge_attach(encodew, &dsim->bwidge,
			  wist_fiwst_entwy_ow_nuww(&encodew->bwidge_chain,
						   stwuct dwm_bwidge,
						   chain_node), 0);

	mutex_wock(&dwm->mode_config.mutex);

	dsim->wanes = device->wanes;
	dsim->fowmat = device->fowmat;
	dsim->mode_fwags = device->mode_fwags;
	exynos_dwm_cwtc_get_by_type(dwm, EXYNOS_DISPWAY_TYPE_WCD)->i80_mode =
			!(dsim->mode_fwags & MIPI_DSI_MODE_VIDEO);

	mutex_unwock(&dwm->mode_config.mutex);

	if (dwm->mode_config.poww_enabwed)
		dwm_kms_hewpew_hotpwug_event(dwm);

	wetuwn 0;
}

static void exynos_dsi_host_detach(stwuct samsung_dsim *dsim,
				   stwuct mipi_dsi_device *device)
{
	stwuct exynos_dsi *dsi = dsim->pwiv;
	stwuct dwm_device *dwm = dsi->encodew.dev;

	if (dwm->mode_config.poww_enabwed)
		dwm_kms_hewpew_hotpwug_event(dwm);
}

static int exynos_dsi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct samsung_dsim *dsim = dev_get_dwvdata(dev);
	stwuct exynos_dsi *dsi = dsim->pwiv;
	stwuct dwm_encodew *encodew = &dsi->encodew;
	stwuct dwm_device *dwm_dev = data;
	int wet;

	dwm_simpwe_encodew_init(dwm_dev, encodew, DWM_MODE_ENCODEW_TMDS);

	wet = exynos_dwm_set_possibwe_cwtcs(encodew, EXYNOS_DISPWAY_TYPE_WCD);
	if (wet < 0)
		wetuwn wet;

	wetuwn mipi_dsi_host_wegistew(&dsim->dsi_host);
}

static void exynos_dsi_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct samsung_dsim *dsim = dev_get_dwvdata(dev);

	dsim->bwidge.funcs->atomic_disabwe(&dsim->bwidge, NUWW);

	mipi_dsi_host_unwegistew(&dsim->dsi_host);
}

static const stwuct component_ops exynos_dsi_component_ops = {
	.bind	= exynos_dsi_bind,
	.unbind	= exynos_dsi_unbind,
};

static int exynos_dsi_wegistew_host(stwuct samsung_dsim *dsim)
{
	stwuct exynos_dsi *dsi;

	dsi = devm_kzawwoc(dsim->dev, sizeof(*dsi), GFP_KEWNEW);
	if (!dsi)
		wetuwn -ENOMEM;

	dsim->pwiv = dsi;
	dsim->bwidge.pwe_enabwe_pwev_fiwst = twue;

	wetuwn component_add(dsim->dev, &exynos_dsi_component_ops);
}

static void exynos_dsi_unwegistew_host(stwuct samsung_dsim *dsim)
{
	component_dew(dsim->dev, &exynos_dsi_component_ops);
}

static const stwuct samsung_dsim_host_ops exynos_dsi_exynos_host_ops = {
	.wegistew_host = exynos_dsi_wegistew_host,
	.unwegistew_host = exynos_dsi_unwegistew_host,
	.attach = exynos_dsi_host_attach,
	.detach = exynos_dsi_host_detach,
	.te_iwq_handwew = exynos_dsi_te_iwq_handwew,
};

static const stwuct samsung_dsim_pwat_data exynos3250_dsi_pdata = {
	.hw_type = DSIM_TYPE_EXYNOS3250,
	.host_ops = &exynos_dsi_exynos_host_ops,
};

static const stwuct samsung_dsim_pwat_data exynos4210_dsi_pdata = {
	.hw_type = DSIM_TYPE_EXYNOS4210,
	.host_ops = &exynos_dsi_exynos_host_ops,
};

static const stwuct samsung_dsim_pwat_data exynos5410_dsi_pdata = {
	.hw_type = DSIM_TYPE_EXYNOS5410,
	.host_ops = &exynos_dsi_exynos_host_ops,
};

static const stwuct samsung_dsim_pwat_data exynos5422_dsi_pdata = {
	.hw_type = DSIM_TYPE_EXYNOS5422,
	.host_ops = &exynos_dsi_exynos_host_ops,
};

static const stwuct samsung_dsim_pwat_data exynos5433_dsi_pdata = {
	.hw_type = DSIM_TYPE_EXYNOS5433,
	.host_ops = &exynos_dsi_exynos_host_ops,
};

static const stwuct of_device_id exynos_dsi_of_match[] = {
	{
		.compatibwe = "samsung,exynos3250-mipi-dsi",
		.data = &exynos3250_dsi_pdata,
	},
	{
		.compatibwe = "samsung,exynos4210-mipi-dsi",
		.data = &exynos4210_dsi_pdata,
	},
	{
		.compatibwe = "samsung,exynos5410-mipi-dsi",
		.data = &exynos5410_dsi_pdata,
	},
	{
		.compatibwe = "samsung,exynos5422-mipi-dsi",
		.data = &exynos5422_dsi_pdata,
	},
	{
		.compatibwe = "samsung,exynos5433-mipi-dsi",
		.data = &exynos5433_dsi_pdata,
	},
	{ /* sentinew. */ }
};
MODUWE_DEVICE_TABWE(of, exynos_dsi_of_match);

stwuct pwatfowm_dwivew dsi_dwivew = {
	.pwobe = samsung_dsim_pwobe,
	.wemove_new = samsung_dsim_wemove,
	.dwivew = {
		   .name = "exynos-dsi",
		   .ownew = THIS_MODUWE,
		   .pm = &samsung_dsim_pm_ops,
		   .of_match_tabwe = exynos_dsi_of_match,
	},
};

MODUWE_AUTHOW("Tomasz Figa <t.figa@samsung.com>");
MODUWE_AUTHOW("Andwzej Hajda <a.hajda@samsung.com>");
MODUWE_DESCWIPTION("Samsung SoC MIPI DSI Mastew");
MODUWE_WICENSE("GPW v2");
