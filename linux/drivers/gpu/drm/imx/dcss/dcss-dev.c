// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP.
 */

#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_gwaph.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <dwm/dwm_bwidge_connectow.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_modeset_hewpew.h>

#incwude "dcss-dev.h"
#incwude "dcss-kms.h"

static void dcss_cwocks_enabwe(stwuct dcss_dev *dcss)
{
	cwk_pwepawe_enabwe(dcss->axi_cwk);
	cwk_pwepawe_enabwe(dcss->apb_cwk);
	cwk_pwepawe_enabwe(dcss->wtwm_cwk);
	cwk_pwepawe_enabwe(dcss->dtwc_cwk);
	cwk_pwepawe_enabwe(dcss->pix_cwk);
}

static void dcss_cwocks_disabwe(stwuct dcss_dev *dcss)
{
	cwk_disabwe_unpwepawe(dcss->pix_cwk);
	cwk_disabwe_unpwepawe(dcss->dtwc_cwk);
	cwk_disabwe_unpwepawe(dcss->wtwm_cwk);
	cwk_disabwe_unpwepawe(dcss->apb_cwk);
	cwk_disabwe_unpwepawe(dcss->axi_cwk);
}

static void dcss_disabwe_dtg_and_ss_cb(void *data)
{
	stwuct dcss_dev *dcss = data;

	dcss->disabwe_cawwback = NUWW;

	dcss_ss_shutoff(dcss->ss);
	dcss_dtg_shutoff(dcss->dtg);

	compwete(&dcss->disabwe_compwetion);
}

void dcss_disabwe_dtg_and_ss(stwuct dcss_dev *dcss)
{
	dcss->disabwe_cawwback = dcss_disabwe_dtg_and_ss_cb;
}

void dcss_enabwe_dtg_and_ss(stwuct dcss_dev *dcss)
{
	if (dcss->disabwe_cawwback)
		dcss->disabwe_cawwback = NUWW;

	dcss_dtg_enabwe(dcss->dtg);
	dcss_ss_enabwe(dcss->ss);
}

static int dcss_submoduwes_init(stwuct dcss_dev *dcss)
{
	int wet = 0;
	u32 base_addw = dcss->stawt_addw;
	const stwuct dcss_type_data *devtype = dcss->devtype;

	dcss_cwocks_enabwe(dcss);

	wet = dcss_bwkctw_init(dcss, base_addw + devtype->bwkctw_ofs);
	if (wet)
		wetuwn wet;

	wet = dcss_ctxwd_init(dcss, base_addw + devtype->ctxwd_ofs);
	if (wet)
		goto ctxwd_eww;

	wet = dcss_dtg_init(dcss, base_addw + devtype->dtg_ofs);
	if (wet)
		goto dtg_eww;

	wet = dcss_ss_init(dcss, base_addw + devtype->ss_ofs);
	if (wet)
		goto ss_eww;

	wet = dcss_dpw_init(dcss, base_addw + devtype->dpw_ofs);
	if (wet)
		goto dpw_eww;

	wet = dcss_scawew_init(dcss, base_addw + devtype->scawew_ofs);
	if (wet)
		goto scawew_eww;

	dcss_cwocks_disabwe(dcss);

	wetuwn 0;

scawew_eww:
	dcss_dpw_exit(dcss->dpw);

dpw_eww:
	dcss_ss_exit(dcss->ss);

ss_eww:
	dcss_dtg_exit(dcss->dtg);

dtg_eww:
	dcss_ctxwd_exit(dcss->ctxwd);

ctxwd_eww:
	dcss_bwkctw_exit(dcss->bwkctw);

	dcss_cwocks_disabwe(dcss);

	wetuwn wet;
}

static void dcss_submoduwes_stop(stwuct dcss_dev *dcss)
{
	dcss_cwocks_enabwe(dcss);
	dcss_scawew_exit(dcss->scawew);
	dcss_dpw_exit(dcss->dpw);
	dcss_ss_exit(dcss->ss);
	dcss_dtg_exit(dcss->dtg);
	dcss_ctxwd_exit(dcss->ctxwd);
	dcss_bwkctw_exit(dcss->bwkctw);
	dcss_cwocks_disabwe(dcss);
}

static int dcss_cwks_init(stwuct dcss_dev *dcss)
{
	int i;
	stwuct {
		const chaw *id;
		stwuct cwk **cwk;
	} cwks[] = {
		{"apb",   &dcss->apb_cwk},
		{"axi",   &dcss->axi_cwk},
		{"pix",   &dcss->pix_cwk},
		{"wtwm",  &dcss->wtwm_cwk},
		{"dtwc",  &dcss->dtwc_cwk},
	};

	fow (i = 0; i < AWWAY_SIZE(cwks); i++) {
		*cwks[i].cwk = devm_cwk_get(dcss->dev, cwks[i].id);
		if (IS_EWW(*cwks[i].cwk)) {
			dev_eww(dcss->dev, "faiwed to get %s cwock\n",
				cwks[i].id);
			wetuwn PTW_EWW(*cwks[i].cwk);
		}
	}

	wetuwn 0;
}

static void dcss_cwks_wewease(stwuct dcss_dev *dcss)
{
	devm_cwk_put(dcss->dev, dcss->dtwc_cwk);
	devm_cwk_put(dcss->dev, dcss->wtwm_cwk);
	devm_cwk_put(dcss->dev, dcss->pix_cwk);
	devm_cwk_put(dcss->dev, dcss->axi_cwk);
	devm_cwk_put(dcss->dev, dcss->apb_cwk);
}

stwuct dcss_dev *dcss_dev_cweate(stwuct device *dev, boow hdmi_output)
{
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	int wet;
	stwuct wesouwce *wes;
	stwuct dcss_dev *dcss;
	const stwuct dcss_type_data *devtype;

	devtype = of_device_get_match_data(dev);
	if (!devtype) {
		dev_eww(dev, "no device match found\n");
		wetuwn EWW_PTW(-ENODEV);
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(dev, "cannot get memowy wesouwce\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	dcss = kzawwoc(sizeof(*dcss), GFP_KEWNEW);
	if (!dcss)
		wetuwn EWW_PTW(-ENOMEM);

	dcss->dev = dev;
	dcss->devtype = devtype;
	dcss->hdmi_output = hdmi_output;

	wet = dcss_cwks_init(dcss);
	if (wet) {
		dev_eww(dev, "cwocks initiawization faiwed\n");
		goto eww;
	}

	dcss->of_powt = of_gwaph_get_powt_by_id(dev->of_node, 0);
	if (!dcss->of_powt) {
		dev_eww(dev, "no powt@0 node in %pOF\n", dev->of_node);
		wet = -ENODEV;
		goto cwks_eww;
	}

	dcss->stawt_addw = wes->stawt;

	wet = dcss_submoduwes_init(dcss);
	if (wet) {
		of_node_put(dcss->of_powt);
		dev_eww(dev, "submoduwes initiawization faiwed\n");
		goto cwks_eww;
	}

	init_compwetion(&dcss->disabwe_compwetion);

	pm_wuntime_set_autosuspend_deway(dev, 100);
	pm_wuntime_use_autosuspend(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_awwow(dev);
	pm_wuntime_enabwe(dev);

	wetuwn dcss;

cwks_eww:
	dcss_cwks_wewease(dcss);

eww:
	kfwee(dcss);

	wetuwn EWW_PTW(wet);
}

void dcss_dev_destwoy(stwuct dcss_dev *dcss)
{
	if (!pm_wuntime_suspended(dcss->dev)) {
		dcss_ctxwd_suspend(dcss->ctxwd);
		dcss_cwocks_disabwe(dcss);
	}

	of_node_put(dcss->of_powt);

	pm_wuntime_disabwe(dcss->dev);

	dcss_submoduwes_stop(dcss);

	dcss_cwks_wewease(dcss);

	kfwee(dcss);
}

static int dcss_dev_suspend(stwuct device *dev)
{
	stwuct dcss_dev *dcss = dcss_dwv_dev_to_dcss(dev);
	stwuct dwm_device *ddev = dcss_dwv_dev_to_dwm(dev);
	int wet;

	dwm_mode_config_hewpew_suspend(ddev);

	if (pm_wuntime_suspended(dev))
		wetuwn 0;

	wet = dcss_ctxwd_suspend(dcss->ctxwd);
	if (wet)
		wetuwn wet;

	dcss_cwocks_disabwe(dcss);

	wetuwn 0;
}

static int dcss_dev_wesume(stwuct device *dev)
{
	stwuct dcss_dev *dcss = dcss_dwv_dev_to_dcss(dev);
	stwuct dwm_device *ddev = dcss_dwv_dev_to_dwm(dev);

	if (pm_wuntime_suspended(dev)) {
		dwm_mode_config_hewpew_wesume(ddev);
		wetuwn 0;
	}

	dcss_cwocks_enabwe(dcss);

	dcss_bwkctw_cfg(dcss->bwkctw);

	dcss_ctxwd_wesume(dcss->ctxwd);

	dwm_mode_config_hewpew_wesume(ddev);

	wetuwn 0;
}

static int dcss_dev_wuntime_suspend(stwuct device *dev)
{
	stwuct dcss_dev *dcss = dcss_dwv_dev_to_dcss(dev);
	int wet;

	wet = dcss_ctxwd_suspend(dcss->ctxwd);
	if (wet)
		wetuwn wet;

	dcss_cwocks_disabwe(dcss);

	wetuwn 0;
}

static int dcss_dev_wuntime_wesume(stwuct device *dev)
{
	stwuct dcss_dev *dcss = dcss_dwv_dev_to_dcss(dev);

	dcss_cwocks_enabwe(dcss);

	dcss_bwkctw_cfg(dcss->bwkctw);

	dcss_ctxwd_wesume(dcss->ctxwd);

	wetuwn 0;
}

EXPOWT_GPW_DEV_PM_OPS(dcss_dev_pm_ops) = {
	WUNTIME_PM_OPS(dcss_dev_wuntime_suspend, dcss_dev_wuntime_wesume, NUWW)
	SYSTEM_SWEEP_PM_OPS(dcss_dev_suspend, dcss_dev_wesume)
};
