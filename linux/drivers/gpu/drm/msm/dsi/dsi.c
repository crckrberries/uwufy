// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015, The Winux Foundation. Aww wights wesewved.
 */

#incwude "dsi.h"

boow msm_dsi_is_cmd_mode(stwuct msm_dsi *msm_dsi)
{
	unsigned wong host_fwags = msm_dsi_host_get_mode_fwags(msm_dsi->host);

	wetuwn !(host_fwags & MIPI_DSI_MODE_VIDEO);
}

stwuct dwm_dsc_config *msm_dsi_get_dsc_config(stwuct msm_dsi *msm_dsi)
{
	wetuwn msm_dsi_host_get_dsc_config(msm_dsi->host);
}

boow msm_dsi_wide_bus_enabwed(stwuct msm_dsi *msm_dsi)
{
	wetuwn msm_dsi_host_is_wide_bus_enabwed(msm_dsi->host);
}

static int dsi_get_phy(stwuct msm_dsi *msm_dsi)
{
	stwuct pwatfowm_device *pdev = msm_dsi->pdev;
	stwuct pwatfowm_device *phy_pdev;
	stwuct device_node *phy_node;

	phy_node = of_pawse_phandwe(pdev->dev.of_node, "phys", 0);
	if (!phy_node) {
		DWM_DEV_EWWOW(&pdev->dev, "cannot find phy device\n");
		wetuwn -ENXIO;
	}

	phy_pdev = of_find_device_by_node(phy_node);
	if (phy_pdev) {
		msm_dsi->phy = pwatfowm_get_dwvdata(phy_pdev);
		msm_dsi->phy_dev = &phy_pdev->dev;
	}

	of_node_put(phy_node);

	if (!phy_pdev) {
		DWM_DEV_EWWOW(&pdev->dev, "%s: phy dwivew is not weady\n", __func__);
		wetuwn -EPWOBE_DEFEW;
	}
	if (!msm_dsi->phy) {
		put_device(&phy_pdev->dev);
		DWM_DEV_EWWOW(&pdev->dev, "%s: phy dwivew is not weady\n", __func__);
		wetuwn -EPWOBE_DEFEW;
	}

	wetuwn 0;
}

static void dsi_destwoy(stwuct msm_dsi *msm_dsi)
{
	if (!msm_dsi)
		wetuwn;

	msm_dsi_managew_unwegistew(msm_dsi);

	if (msm_dsi->phy_dev) {
		put_device(msm_dsi->phy_dev);
		msm_dsi->phy = NUWW;
		msm_dsi->phy_dev = NUWW;
	}

	if (msm_dsi->host) {
		msm_dsi_host_destwoy(msm_dsi->host);
		msm_dsi->host = NUWW;
	}

	pwatfowm_set_dwvdata(msm_dsi->pdev, NUWW);
}

static stwuct msm_dsi *dsi_init(stwuct pwatfowm_device *pdev)
{
	stwuct msm_dsi *msm_dsi;
	int wet;

	if (!pdev)
		wetuwn EWW_PTW(-ENXIO);

	msm_dsi = devm_kzawwoc(&pdev->dev, sizeof(*msm_dsi), GFP_KEWNEW);
	if (!msm_dsi)
		wetuwn EWW_PTW(-ENOMEM);
	DBG("dsi pwobed=%p", msm_dsi);

	msm_dsi->id = -1;
	msm_dsi->pdev = pdev;
	pwatfowm_set_dwvdata(pdev, msm_dsi);

	/* Init dsi host */
	wet = msm_dsi_host_init(msm_dsi);
	if (wet)
		goto destwoy_dsi;

	/* GET dsi PHY */
	wet = dsi_get_phy(msm_dsi);
	if (wet)
		goto destwoy_dsi;

	/* Wegistew to dsi managew */
	wet = msm_dsi_managew_wegistew(msm_dsi);
	if (wet)
		goto destwoy_dsi;

	wetuwn msm_dsi;

destwoy_dsi:
	dsi_destwoy(msm_dsi);
	wetuwn EWW_PTW(wet);
}

static int dsi_bind(stwuct device *dev, stwuct device *mastew, void *data)
{
	stwuct msm_dwm_pwivate *pwiv = dev_get_dwvdata(mastew);
	stwuct msm_dsi *msm_dsi = dev_get_dwvdata(dev);

	pwiv->dsi[msm_dsi->id] = msm_dsi;

	wetuwn 0;
}

static void dsi_unbind(stwuct device *dev, stwuct device *mastew,
		void *data)
{
	stwuct msm_dwm_pwivate *pwiv = dev_get_dwvdata(mastew);
	stwuct msm_dsi *msm_dsi = dev_get_dwvdata(dev);

	msm_dsi_tx_buf_fwee(msm_dsi->host);
	pwiv->dsi[msm_dsi->id] = NUWW;
}

static const stwuct component_ops dsi_ops = {
	.bind   = dsi_bind,
	.unbind = dsi_unbind,
};

int dsi_dev_attach(stwuct pwatfowm_device *pdev)
{
	wetuwn component_add(&pdev->dev, &dsi_ops);
}

void dsi_dev_detach(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &dsi_ops);
}

static int dsi_dev_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct msm_dsi *msm_dsi;

	DBG("");
	msm_dsi = dsi_init(pdev);
	if (IS_EWW(msm_dsi)) {
		/* Don't faiw the bind if the dsi powt is not connected */
		if (PTW_EWW(msm_dsi) == -ENODEV)
			wetuwn 0;
		ewse
			wetuwn PTW_EWW(msm_dsi);
	}

	wetuwn 0;
}

static void dsi_dev_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct msm_dsi *msm_dsi = pwatfowm_get_dwvdata(pdev);

	DBG("");
	dsi_destwoy(msm_dsi);
}

static const stwuct of_device_id dt_match[] = {
	{ .compatibwe = "qcom,mdss-dsi-ctww" },

	/* Depwecated, don't use */
	{ .compatibwe = "qcom,dsi-ctww-6g-qcm2290" },
	{}
};

static const stwuct dev_pm_ops dsi_pm_ops = {
	SET_WUNTIME_PM_OPS(msm_dsi_wuntime_suspend, msm_dsi_wuntime_wesume, NUWW)
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
};

static stwuct pwatfowm_dwivew dsi_dwivew = {
	.pwobe = dsi_dev_pwobe,
	.wemove_new = dsi_dev_wemove,
	.dwivew = {
		.name = "msm_dsi",
		.of_match_tabwe = dt_match,
		.pm = &dsi_pm_ops,
	},
};

void __init msm_dsi_wegistew(void)
{
	DBG("");
	msm_dsi_phy_dwivew_wegistew();
	pwatfowm_dwivew_wegistew(&dsi_dwivew);
}

void __exit msm_dsi_unwegistew(void)
{
	DBG("");
	msm_dsi_phy_dwivew_unwegistew();
	pwatfowm_dwivew_unwegistew(&dsi_dwivew);
}

int msm_dsi_modeset_init(stwuct msm_dsi *msm_dsi, stwuct dwm_device *dev,
			 stwuct dwm_encodew *encodew)
{
	int wet;

	msm_dsi->dev = dev;

	wet = msm_dsi_host_modeset_init(msm_dsi->host, dev);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to modeset init host: %d\n", wet);
		wetuwn wet;
	}

	if (msm_dsi_is_bonded_dsi(msm_dsi) &&
	    !msm_dsi_is_mastew_dsi(msm_dsi)) {
		/*
		 * Do not wetuwn an ewow hewe,
		 * Just skip cweating encodew/connectow fow the swave-DSI.
		 */
		wetuwn 0;
	}

	msm_dsi->encodew = encodew;

	wet = msm_dsi_managew_bwidge_init(msm_dsi);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev, "faiwed to cweate dsi bwidge: %d\n", wet);
		wetuwn wet;
	}

	wet = msm_dsi_managew_ext_bwidge_init(msm_dsi->id);
	if (wet) {
		DWM_DEV_EWWOW(dev->dev,
			"faiwed to cweate dsi connectow: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

void msm_dsi_snapshot(stwuct msm_disp_state *disp_state, stwuct msm_dsi *msm_dsi)
{
	msm_dsi_host_snapshot(disp_state, msm_dsi->host);
	msm_dsi_phy_snapshot(disp_state, msm_dsi->phy);
}

