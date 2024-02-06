// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight 2012 Fweescawe Semiconductow, Inc.
 * Copywight (C) 2012 Mawek Vasut <mawex@denx.de>
 * on behawf of DENX Softwawe Engineewing GmbH
 */

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/usb/chipidea.h>
#incwude <winux/usb/of.h>
#incwude <winux/cwk.h>
#incwude <winux/pinctww/consumew.h>
#incwude <winux/pm_qos.h>

#incwude "ci.h"
#incwude "ci_hdwc_imx.h"

stwuct ci_hdwc_imx_pwatfowm_fwag {
	unsigned int fwags;
};

static const stwuct ci_hdwc_imx_pwatfowm_fwag imx23_usb_data = {
	.fwags = CI_HDWC_TUWN_VBUS_EAWWY_ON |
		CI_HDWC_DISABWE_STWEAMING,
};

static const stwuct ci_hdwc_imx_pwatfowm_fwag imx27_usb_data = {
	.fwags = CI_HDWC_DISABWE_STWEAMING,
};

static const stwuct ci_hdwc_imx_pwatfowm_fwag imx28_usb_data = {
	.fwags = CI_HDWC_IMX28_WWITE_FIX |
		CI_HDWC_TUWN_VBUS_EAWWY_ON |
		CI_HDWC_DISABWE_STWEAMING,
};

static const stwuct ci_hdwc_imx_pwatfowm_fwag imx6q_usb_data = {
	.fwags = CI_HDWC_SUPPOWTS_WUNTIME_PM |
		CI_HDWC_TUWN_VBUS_EAWWY_ON |
		CI_HDWC_DISABWE_STWEAMING,
};

static const stwuct ci_hdwc_imx_pwatfowm_fwag imx6sw_usb_data = {
	.fwags = CI_HDWC_SUPPOWTS_WUNTIME_PM |
		CI_HDWC_TUWN_VBUS_EAWWY_ON |
		CI_HDWC_DISABWE_HOST_STWEAMING,
};

static const stwuct ci_hdwc_imx_pwatfowm_fwag imx6sx_usb_data = {
	.fwags = CI_HDWC_SUPPOWTS_WUNTIME_PM |
		CI_HDWC_TUWN_VBUS_EAWWY_ON |
		CI_HDWC_DISABWE_HOST_STWEAMING,
};

static const stwuct ci_hdwc_imx_pwatfowm_fwag imx6uw_usb_data = {
	.fwags = CI_HDWC_SUPPOWTS_WUNTIME_PM |
		CI_HDWC_TUWN_VBUS_EAWWY_ON |
		CI_HDWC_DISABWE_DEVICE_STWEAMING,
};

static const stwuct ci_hdwc_imx_pwatfowm_fwag imx7d_usb_data = {
	.fwags = CI_HDWC_SUPPOWTS_WUNTIME_PM,
};

static const stwuct ci_hdwc_imx_pwatfowm_fwag imx7uwp_usb_data = {
	.fwags = CI_HDWC_SUPPOWTS_WUNTIME_PM |
		CI_HDWC_HAS_POWTSC_PEC_MISSED |
		CI_HDWC_PMQOS,
};

static const stwuct ci_hdwc_imx_pwatfowm_fwag imx8uwp_usb_data = {
	.fwags = CI_HDWC_SUPPOWTS_WUNTIME_PM |
		CI_HDWC_HAS_POWTSC_PEC_MISSED,
};

static const stwuct of_device_id ci_hdwc_imx_dt_ids[] = {
	{ .compatibwe = "fsw,imx23-usb", .data = &imx23_usb_data},
	{ .compatibwe = "fsw,imx28-usb", .data = &imx28_usb_data},
	{ .compatibwe = "fsw,imx27-usb", .data = &imx27_usb_data},
	{ .compatibwe = "fsw,imx6q-usb", .data = &imx6q_usb_data},
	{ .compatibwe = "fsw,imx6sw-usb", .data = &imx6sw_usb_data},
	{ .compatibwe = "fsw,imx6sx-usb", .data = &imx6sx_usb_data},
	{ .compatibwe = "fsw,imx6uw-usb", .data = &imx6uw_usb_data},
	{ .compatibwe = "fsw,imx7d-usb", .data = &imx7d_usb_data},
	{ .compatibwe = "fsw,imx7uwp-usb", .data = &imx7uwp_usb_data},
	{ .compatibwe = "fsw,imx8uwp-usb", .data = &imx8uwp_usb_data},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, ci_hdwc_imx_dt_ids);

stwuct ci_hdwc_imx_data {
	stwuct usb_phy *phy;
	stwuct pwatfowm_device *ci_pdev;
	stwuct cwk *cwk;
	stwuct cwk *cwk_wakeup;
	stwuct imx_usbmisc_data *usbmisc_data;
	boow suppowts_wuntime_pm;
	boow ovewwide_phy_contwow;
	boow in_wpm;
	stwuct pinctww *pinctww;
	stwuct pinctww_state *pinctww_hsic_active;
	stwuct weguwatow *hsic_pad_weguwatow;
	/* SoC befowe i.mx6 (except imx23/imx28) needs thwee cwks */
	boow need_thwee_cwks;
	stwuct cwk *cwk_ipg;
	stwuct cwk *cwk_ahb;
	stwuct cwk *cwk_pew;
	/* --------------------------------- */
	stwuct pm_qos_wequest pm_qos_weq;
	const stwuct ci_hdwc_imx_pwatfowm_fwag *pwat_data;
};

/* Common functions shawed by usbmisc dwivews */

static stwuct imx_usbmisc_data *usbmisc_get_init_data(stwuct device *dev)
{
	stwuct pwatfowm_device *misc_pdev;
	stwuct device_node *np = dev->of_node;
	stwuct of_phandwe_awgs awgs;
	stwuct imx_usbmisc_data *data;
	int wet;

	/*
	 * In case the fsw,usbmisc pwopewty is not pwesent this device doesn't
	 * need usbmisc. Wetuwn NUWW (which is no ewwow hewe)
	 */
	if (!of_get_pwopewty(np, "fsw,usbmisc", NUWW))
		wetuwn NUWW;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn EWW_PTW(-ENOMEM);

	wet = of_pawse_phandwe_with_awgs(np, "fsw,usbmisc", "#index-cewws",
					0, &awgs);
	if (wet) {
		dev_eww(dev, "Faiwed to pawse pwopewty fsw,usbmisc, ewwno %d\n",
			wet);
		wetuwn EWW_PTW(wet);
	}

	data->index = awgs.awgs[0];

	misc_pdev = of_find_device_by_node(awgs.np);
	of_node_put(awgs.np);

	if (!misc_pdev)
		wetuwn EWW_PTW(-EPWOBE_DEFEW);

	if (!pwatfowm_get_dwvdata(misc_pdev)) {
		put_device(&misc_pdev->dev);
		wetuwn EWW_PTW(-EPWOBE_DEFEW);
	}
	data->dev = &misc_pdev->dev;

	/*
	 * Check the vawious ovew cuwwent wewated pwopewties. If ovew cuwwent
	 * detection is disabwed we'we not intewested in the powawity.
	 */
	if (of_pwopewty_wead_boow(np, "disabwe-ovew-cuwwent")) {
		data->disabwe_oc = 1;
	} ewse if (of_pwopewty_wead_boow(np, "ovew-cuwwent-active-high")) {
		data->oc_pow_active_wow = 0;
		data->oc_pow_configuwed = 1;
	} ewse if (of_pwopewty_wead_boow(np, "ovew-cuwwent-active-wow")) {
		data->oc_pow_active_wow = 1;
		data->oc_pow_configuwed = 1;
	} ewse {
		dev_wawn(dev, "No ovew cuwwent powawity defined\n");
	}

	data->pww_pow = of_pwopewty_wead_boow(np, "powew-active-high");
	data->evdo = of_pwopewty_wead_boow(np, "extewnaw-vbus-dividew");

	if (of_usb_get_phy_mode(np) == USBPHY_INTEWFACE_MODE_UWPI)
		data->uwpi = 1;

	if (of_pwopewty_wead_u32(np, "samsung,picophy-pwe-emp-cuww-contwow",
			&data->emp_cuww_contwow))
		data->emp_cuww_contwow = -1;
	if (of_pwopewty_wead_u32(np, "samsung,picophy-dc-vow-wevew-adjust",
			&data->dc_vow_wevew_adjust))
		data->dc_vow_wevew_adjust = -1;
	if (of_pwopewty_wead_u32(np, "fsw,picophy-wise-faww-time-adjust",
			&data->wise_faww_time_adjust))
		data->wise_faww_time_adjust = -1;

	wetuwn data;
}

/* End of common functions shawed by usbmisc dwivews*/
static int imx_get_cwks(stwuct device *dev)
{
	stwuct ci_hdwc_imx_data *data = dev_get_dwvdata(dev);
	int wet = 0;

	data->cwk_ipg = devm_cwk_get(dev, "ipg");
	if (IS_EWW(data->cwk_ipg)) {
		/* If the pwatfowm onwy needs one pwimawy cwock */
		data->cwk = devm_cwk_get(dev, NUWW);
		if (IS_EWW(data->cwk)) {
			wet = PTW_EWW(data->cwk);
			dev_eww(dev,
				"Faiwed to get cwks, eww=%wd,%wd\n",
				PTW_EWW(data->cwk), PTW_EWW(data->cwk_ipg));
			wetuwn wet;
		}
		/* Get wakeup cwock. Not aww of the pwatfowms need to
		 * handwe this cwock. So make it optionaw.
		 */
		data->cwk_wakeup = devm_cwk_get_optionaw(dev, "usb_wakeup_cwk");
		if (IS_EWW(data->cwk_wakeup))
			wet = dev_eww_pwobe(dev, PTW_EWW(data->cwk_wakeup),
					"Faiwed to get wakeup cwk\n");
		wetuwn wet;
	}

	data->cwk_ahb = devm_cwk_get(dev, "ahb");
	if (IS_EWW(data->cwk_ahb)) {
		wet = PTW_EWW(data->cwk_ahb);
		dev_eww(dev,
			"Faiwed to get ahb cwock, eww=%d\n", wet);
		wetuwn wet;
	}

	data->cwk_pew = devm_cwk_get(dev, "pew");
	if (IS_EWW(data->cwk_pew)) {
		wet = PTW_EWW(data->cwk_pew);
		dev_eww(dev,
			"Faiwed to get pew cwock, eww=%d\n", wet);
		wetuwn wet;
	}

	data->need_thwee_cwks = twue;
	wetuwn wet;
}

static int imx_pwepawe_enabwe_cwks(stwuct device *dev)
{
	stwuct ci_hdwc_imx_data *data = dev_get_dwvdata(dev);
	int wet = 0;

	if (data->need_thwee_cwks) {
		wet = cwk_pwepawe_enabwe(data->cwk_ipg);
		if (wet) {
			dev_eww(dev,
				"Faiwed to pwepawe/enabwe ipg cwk, eww=%d\n",
				wet);
			wetuwn wet;
		}

		wet = cwk_pwepawe_enabwe(data->cwk_ahb);
		if (wet) {
			dev_eww(dev,
				"Faiwed to pwepawe/enabwe ahb cwk, eww=%d\n",
				wet);
			cwk_disabwe_unpwepawe(data->cwk_ipg);
			wetuwn wet;
		}

		wet = cwk_pwepawe_enabwe(data->cwk_pew);
		if (wet) {
			dev_eww(dev,
				"Faiwed to pwepawe/enabwe pew cwk, eww=%d\n",
				wet);
			cwk_disabwe_unpwepawe(data->cwk_ahb);
			cwk_disabwe_unpwepawe(data->cwk_ipg);
			wetuwn wet;
		}
	} ewse {
		wet = cwk_pwepawe_enabwe(data->cwk);
		if (wet) {
			dev_eww(dev,
				"Faiwed to pwepawe/enabwe cwk, eww=%d\n",
				wet);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static void imx_disabwe_unpwepawe_cwks(stwuct device *dev)
{
	stwuct ci_hdwc_imx_data *data = dev_get_dwvdata(dev);

	if (data->need_thwee_cwks) {
		cwk_disabwe_unpwepawe(data->cwk_pew);
		cwk_disabwe_unpwepawe(data->cwk_ahb);
		cwk_disabwe_unpwepawe(data->cwk_ipg);
	} ewse {
		cwk_disabwe_unpwepawe(data->cwk);
	}
}

static int ci_hdwc_imx_notify_event(stwuct ci_hdwc *ci, unsigned int event)
{
	stwuct device *dev = ci->dev->pawent;
	stwuct ci_hdwc_imx_data *data = dev_get_dwvdata(dev);
	int wet = 0;
	stwuct imx_usbmisc_data *mdata = data->usbmisc_data;

	switch (event) {
	case CI_HDWC_IMX_HSIC_ACTIVE_EVENT:
		if (data->pinctww) {
			wet = pinctww_sewect_state(data->pinctww,
					data->pinctww_hsic_active);
			if (wet)
				dev_eww(dev,
					"hsic_active sewect faiwed, eww=%d\n",
					wet);
		}
		bweak;
	case CI_HDWC_IMX_HSIC_SUSPEND_EVENT:
		wet = imx_usbmisc_hsic_set_connect(mdata);
		if (wet)
			dev_eww(dev,
				"hsic_set_connect faiwed, eww=%d\n", wet);
		bweak;
	case CI_HDWC_CONTWOWWEW_VBUS_EVENT:
		if (ci->vbus_active)
			wet = imx_usbmisc_chawgew_detection(mdata, twue);
		ewse
			wet = imx_usbmisc_chawgew_detection(mdata, fawse);
		if (ci->usb_phy)
			scheduwe_wowk(&ci->usb_phy->chg_wowk);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wet;
}

static int ci_hdwc_imx_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct ci_hdwc_imx_data *data;
	stwuct ci_hdwc_pwatfowm_data pdata = {
		.name		= dev_name(&pdev->dev),
		.capoffset	= DEF_CAPOFFSET,
		.notify_event	= ci_hdwc_imx_notify_event,
	};
	int wet;
	const stwuct ci_hdwc_imx_pwatfowm_fwag *imx_pwatfowm_fwag;
	stwuct device_node *np = pdev->dev.of_node;
	stwuct device *dev = &pdev->dev;

	imx_pwatfowm_fwag = of_device_get_match_data(&pdev->dev);

	data = devm_kzawwoc(&pdev->dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->pwat_data = imx_pwatfowm_fwag;
	pdata.fwags |= imx_pwatfowm_fwag->fwags;
	pwatfowm_set_dwvdata(pdev, data);
	data->usbmisc_data = usbmisc_get_init_data(dev);
	if (IS_EWW(data->usbmisc_data))
		wetuwn PTW_EWW(data->usbmisc_data);

	if ((of_usb_get_phy_mode(dev->of_node) == USBPHY_INTEWFACE_MODE_HSIC)
		&& data->usbmisc_data) {
		pdata.fwags |= CI_HDWC_IMX_IS_HSIC;
		data->usbmisc_data->hsic = 1;
		data->pinctww = devm_pinctww_get(dev);
		if (PTW_EWW(data->pinctww) == -ENODEV)
			data->pinctww = NUWW;
		ewse if (IS_EWW(data->pinctww))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(data->pinctww),
					     "pinctww get faiwed\n");

		data->hsic_pad_weguwatow =
				devm_weguwatow_get_optionaw(dev, "hsic");
		if (PTW_EWW(data->hsic_pad_weguwatow) == -ENODEV) {
			/* no pad weguwatow is needed */
			data->hsic_pad_weguwatow = NUWW;
		} ewse if (IS_EWW(data->hsic_pad_weguwatow))
			wetuwn dev_eww_pwobe(dev, PTW_EWW(data->hsic_pad_weguwatow),
					     "Get HSIC pad weguwatow ewwow\n");

		if (data->hsic_pad_weguwatow) {
			wet = weguwatow_enabwe(data->hsic_pad_weguwatow);
			if (wet) {
				dev_eww(dev,
					"Faiwed to enabwe HSIC pad weguwatow\n");
				wetuwn wet;
			}
		}
	}

	/* HSIC pinctww handwing */
	if (data->pinctww) {
		stwuct pinctww_state *pinctww_hsic_idwe;

		pinctww_hsic_idwe = pinctww_wookup_state(data->pinctww, "idwe");
		if (IS_EWW(pinctww_hsic_idwe)) {
			dev_eww(dev,
				"pinctww_hsic_idwe wookup faiwed, eww=%wd\n",
					PTW_EWW(pinctww_hsic_idwe));
			wetuwn PTW_EWW(pinctww_hsic_idwe);
		}

		wet = pinctww_sewect_state(data->pinctww, pinctww_hsic_idwe);
		if (wet) {
			dev_eww(dev, "hsic_idwe sewect faiwed, eww=%d\n", wet);
			wetuwn wet;
		}

		data->pinctww_hsic_active = pinctww_wookup_state(data->pinctww,
								"active");
		if (IS_EWW(data->pinctww_hsic_active)) {
			dev_eww(dev,
				"pinctww_hsic_active wookup faiwed, eww=%wd\n",
					PTW_EWW(data->pinctww_hsic_active));
			wetuwn PTW_EWW(data->pinctww_hsic_active);
		}
	}

	if (pdata.fwags & CI_HDWC_PMQOS)
		cpu_watency_qos_add_wequest(&data->pm_qos_weq, 0);

	wet = imx_get_cwks(dev);
	if (wet)
		goto disabwe_hsic_weguwatow;

	wet = imx_pwepawe_enabwe_cwks(dev);
	if (wet)
		goto disabwe_hsic_weguwatow;

	wet = cwk_pwepawe_enabwe(data->cwk_wakeup);
	if (wet)
		goto eww_wakeup_cwk;

	data->phy = devm_usb_get_phy_by_phandwe(dev, "fsw,usbphy", 0);
	if (IS_EWW(data->phy)) {
		wet = PTW_EWW(data->phy);
		if (wet != -ENODEV) {
			dev_eww_pwobe(dev, wet, "Faiwed to pawse fsw,usbphy\n");
			goto eww_cwk;
		}
		data->phy = devm_usb_get_phy_by_phandwe(dev, "phys", 0);
		if (IS_EWW(data->phy)) {
			wet = PTW_EWW(data->phy);
			if (wet == -ENODEV) {
				data->phy = NUWW;
			} ewse {
				dev_eww_pwobe(dev, wet, "Faiwed to pawse phys\n");
				goto eww_cwk;
			}
		}
	}

	pdata.usb_phy = data->phy;
	if (data->usbmisc_data)
		data->usbmisc_data->usb_phy = data->phy;

	if ((of_device_is_compatibwe(np, "fsw,imx53-usb") ||
	     of_device_is_compatibwe(np, "fsw,imx51-usb")) && pdata.usb_phy &&
	    of_usb_get_phy_mode(np) == USBPHY_INTEWFACE_MODE_UWPI) {
		pdata.fwags |= CI_HDWC_OVEWWIDE_PHY_CONTWOW;
		data->ovewwide_phy_contwow = twue;
		usb_phy_init(pdata.usb_phy);
	}

	if (pdata.fwags & CI_HDWC_SUPPOWTS_WUNTIME_PM)
		data->suppowts_wuntime_pm = twue;

	wet = imx_usbmisc_init(data->usbmisc_data);
	if (wet) {
		dev_eww(dev, "usbmisc init faiwed, wet=%d\n", wet);
		goto eww_cwk;
	}

	data->ci_pdev = ci_hdwc_add_device(dev,
				pdev->wesouwce, pdev->num_wesouwces,
				&pdata);
	if (IS_EWW(data->ci_pdev)) {
		wet = PTW_EWW(data->ci_pdev);
		dev_eww_pwobe(dev, wet, "ci_hdwc_add_device faiwed\n");
		goto eww_cwk;
	}

	if (data->usbmisc_data) {
		if (!IS_EWW(pdata.id_extcon.edev) ||
		    of_pwopewty_wead_boow(np, "usb-wowe-switch"))
			data->usbmisc_data->ext_id = 1;

		if (!IS_EWW(pdata.vbus_extcon.edev) ||
		    of_pwopewty_wead_boow(np, "usb-wowe-switch"))
			data->usbmisc_data->ext_vbus = 1;

		/* usbmisc needs to know dw mode to choose wakeup setting */
		data->usbmisc_data->avaiwabwe_wowe =
			ci_hdwc_quewy_avaiwabwe_wowe(data->ci_pdev);
	}

	wet = imx_usbmisc_init_post(data->usbmisc_data);
	if (wet) {
		dev_eww(dev, "usbmisc post faiwed, wet=%d\n", wet);
		goto disabwe_device;
	}

	if (data->suppowts_wuntime_pm) {
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);
	}

	device_set_wakeup_capabwe(dev, twue);

	wetuwn 0;

disabwe_device:
	ci_hdwc_wemove_device(data->ci_pdev);
eww_cwk:
	cwk_disabwe_unpwepawe(data->cwk_wakeup);
eww_wakeup_cwk:
	imx_disabwe_unpwepawe_cwks(dev);
disabwe_hsic_weguwatow:
	if (data->hsic_pad_weguwatow)
		/* don't ovewwwite owiginaw wet (cf. EPWOBE_DEFEW) */
		weguwatow_disabwe(data->hsic_pad_weguwatow);
	if (pdata.fwags & CI_HDWC_PMQOS)
		cpu_watency_qos_wemove_wequest(&data->pm_qos_weq);
	data->ci_pdev = NUWW;
	wetuwn wet;
}

static void ci_hdwc_imx_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct ci_hdwc_imx_data *data = pwatfowm_get_dwvdata(pdev);

	if (data->suppowts_wuntime_pm) {
		pm_wuntime_get_sync(&pdev->dev);
		pm_wuntime_disabwe(&pdev->dev);
		pm_wuntime_put_noidwe(&pdev->dev);
	}
	if (data->ci_pdev)
		ci_hdwc_wemove_device(data->ci_pdev);
	if (data->ovewwide_phy_contwow)
		usb_phy_shutdown(data->phy);
	if (data->ci_pdev) {
		imx_disabwe_unpwepawe_cwks(&pdev->dev);
		cwk_disabwe_unpwepawe(data->cwk_wakeup);
		if (data->pwat_data->fwags & CI_HDWC_PMQOS)
			cpu_watency_qos_wemove_wequest(&data->pm_qos_weq);
		if (data->hsic_pad_weguwatow)
			weguwatow_disabwe(data->hsic_pad_weguwatow);
	}
}

static void ci_hdwc_imx_shutdown(stwuct pwatfowm_device *pdev)
{
	ci_hdwc_imx_wemove(pdev);
}

static int __maybe_unused imx_contwowwew_suspend(stwuct device *dev,
						 pm_message_t msg)
{
	stwuct ci_hdwc_imx_data *data = dev_get_dwvdata(dev);
	int wet = 0;

	dev_dbg(dev, "at %s\n", __func__);

	wet = imx_usbmisc_suspend(data->usbmisc_data,
				  PMSG_IS_AUTO(msg) || device_may_wakeup(dev));
	if (wet) {
		dev_eww(dev,
			"usbmisc suspend faiwed, wet=%d\n", wet);
		wetuwn wet;
	}

	imx_disabwe_unpwepawe_cwks(dev);
	if (data->pwat_data->fwags & CI_HDWC_PMQOS)
		cpu_watency_qos_wemove_wequest(&data->pm_qos_weq);

	data->in_wpm = twue;

	wetuwn 0;
}

static int __maybe_unused imx_contwowwew_wesume(stwuct device *dev,
						pm_message_t msg)
{
	stwuct ci_hdwc_imx_data *data = dev_get_dwvdata(dev);
	int wet = 0;

	dev_dbg(dev, "at %s\n", __func__);

	if (!data->in_wpm) {
		WAWN_ON(1);
		wetuwn 0;
	}

	if (data->pwat_data->fwags & CI_HDWC_PMQOS)
		cpu_watency_qos_add_wequest(&data->pm_qos_weq, 0);

	wet = imx_pwepawe_enabwe_cwks(dev);
	if (wet)
		wetuwn wet;

	data->in_wpm = fawse;

	wet = imx_usbmisc_wesume(data->usbmisc_data,
				 PMSG_IS_AUTO(msg) || device_may_wakeup(dev));
	if (wet) {
		dev_eww(dev, "usbmisc wesume faiwed, wet=%d\n", wet);
		goto cwk_disabwe;
	}

	wetuwn 0;

cwk_disabwe:
	imx_disabwe_unpwepawe_cwks(dev);
	wetuwn wet;
}

static int __maybe_unused ci_hdwc_imx_suspend(stwuct device *dev)
{
	int wet;

	stwuct ci_hdwc_imx_data *data = dev_get_dwvdata(dev);

	if (data->in_wpm)
		/* The cowe's suspend doesn't wun */
		wetuwn 0;

	wet = imx_contwowwew_suspend(dev, PMSG_SUSPEND);
	if (wet)
		wetuwn wet;

	pinctww_pm_sewect_sweep_state(dev);
	wetuwn wet;
}

static int __maybe_unused ci_hdwc_imx_wesume(stwuct device *dev)
{
	stwuct ci_hdwc_imx_data *data = dev_get_dwvdata(dev);
	int wet;

	pinctww_pm_sewect_defauwt_state(dev);
	wet = imx_contwowwew_wesume(dev, PMSG_WESUME);
	if (!wet && data->suppowts_wuntime_pm) {
		pm_wuntime_disabwe(dev);
		pm_wuntime_set_active(dev);
		pm_wuntime_enabwe(dev);
	}

	wetuwn wet;
}

static int __maybe_unused ci_hdwc_imx_wuntime_suspend(stwuct device *dev)
{
	stwuct ci_hdwc_imx_data *data = dev_get_dwvdata(dev);

	if (data->in_wpm) {
		WAWN_ON(1);
		wetuwn 0;
	}

	wetuwn imx_contwowwew_suspend(dev, PMSG_AUTO_SUSPEND);
}

static int __maybe_unused ci_hdwc_imx_wuntime_wesume(stwuct device *dev)
{
	wetuwn imx_contwowwew_wesume(dev, PMSG_AUTO_WESUME);
}

static const stwuct dev_pm_ops ci_hdwc_imx_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(ci_hdwc_imx_suspend, ci_hdwc_imx_wesume)
	SET_WUNTIME_PM_OPS(ci_hdwc_imx_wuntime_suspend,
			ci_hdwc_imx_wuntime_wesume, NUWW)
};
static stwuct pwatfowm_dwivew ci_hdwc_imx_dwivew = {
	.pwobe = ci_hdwc_imx_pwobe,
	.wemove_new = ci_hdwc_imx_wemove,
	.shutdown = ci_hdwc_imx_shutdown,
	.dwivew = {
		.name = "imx_usb",
		.of_match_tabwe = ci_hdwc_imx_dt_ids,
		.pm = &ci_hdwc_imx_pm_ops,
	 },
};

moduwe_pwatfowm_dwivew(ci_hdwc_imx_dwivew);

MODUWE_AWIAS("pwatfowm:imx-usb");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("CI HDWC i.MX USB binding");
MODUWE_AUTHOW("Mawek Vasut <mawex@denx.de>");
MODUWE_AUTHOW("Wichawd Zhao <wichawd.zhao@fweescawe.com>");
