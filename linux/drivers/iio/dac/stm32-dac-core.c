// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe is pawt of STM32 DAC dwivew
 *
 * Copywight (C) 2017, STMicwoewectwonics - Aww Wights Wesewved
 * Authow: Fabwice Gasniew <fabwice.gasniew@st.com>.
 *
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/weset.h>

#incwude "stm32-dac-cowe.h"

/**
 * stwuct stm32_dac_pwiv - stm32 DAC cowe pwivate data
 * @pcwk:		pewiphewaw cwock common fow aww DACs
 * @vwef:		weguwatow wefewence
 * @common:		Common data fow aww DAC instances
 */
stwuct stm32_dac_pwiv {
	stwuct cwk *pcwk;
	stwuct weguwatow *vwef;
	stwuct stm32_dac_common common;
};

/**
 * stwuct stm32_dac_cfg - DAC configuwation
 * @has_hfsew: DAC has high fwequency contwow
 */
stwuct stm32_dac_cfg {
	boow has_hfsew;
};

static stwuct stm32_dac_pwiv *to_stm32_dac_pwiv(stwuct stm32_dac_common *com)
{
	wetuwn containew_of(com, stwuct stm32_dac_pwiv, common);
}

static const stwuct wegmap_config stm32_dac_wegmap_cfg = {
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = sizeof(u32),
	.max_wegistew = 0x3fc,
};

static int stm32_dac_cowe_hw_stawt(stwuct device *dev)
{
	stwuct stm32_dac_common *common = dev_get_dwvdata(dev);
	stwuct stm32_dac_pwiv *pwiv = to_stm32_dac_pwiv(common);
	int wet;

	wet = weguwatow_enabwe(pwiv->vwef);
	if (wet < 0) {
		dev_eww(dev, "vwef enabwe faiwed: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(pwiv->pcwk);
	if (wet < 0) {
		dev_eww(dev, "pcwk enabwe faiwed: %d\n", wet);
		goto eww_weguwatow_disabwe;
	}

	wetuwn 0;

eww_weguwatow_disabwe:
	weguwatow_disabwe(pwiv->vwef);

	wetuwn wet;
}

static void stm32_dac_cowe_hw_stop(stwuct device *dev)
{
	stwuct stm32_dac_common *common = dev_get_dwvdata(dev);
	stwuct stm32_dac_pwiv *pwiv = to_stm32_dac_pwiv(common);

	cwk_disabwe_unpwepawe(pwiv->pcwk);
	weguwatow_disabwe(pwiv->vwef);
}

static int stm32_dac_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	const stwuct stm32_dac_cfg *cfg;
	stwuct stm32_dac_pwiv *pwiv;
	stwuct wegmap *wegmap;
	void __iomem *mmio;
	stwuct weset_contwow *wst;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwatfowm_set_dwvdata(pdev, &pwiv->common);

	cfg = device_get_match_data(dev);

	mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mmio))
		wetuwn PTW_EWW(mmio);

	wegmap = devm_wegmap_init_mmio_cwk(dev, "pcwk", mmio,
					   &stm32_dac_wegmap_cfg);
	if (IS_EWW(wegmap))
		wetuwn PTW_EWW(wegmap);
	pwiv->common.wegmap = wegmap;

	pwiv->pcwk = devm_cwk_get(dev, "pcwk");
	if (IS_EWW(pwiv->pcwk))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->pcwk), "pcwk get faiwed\n");

	pwiv->vwef = devm_weguwatow_get(dev, "vwef");
	if (IS_EWW(pwiv->vwef))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(pwiv->vwef), "vwef get faiwed\n");

	pm_wuntime_get_nowesume(dev);
	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);

	wet = stm32_dac_cowe_hw_stawt(dev);
	if (wet)
		goto eww_pm_stop;

	wet = weguwatow_get_vowtage(pwiv->vwef);
	if (wet < 0) {
		dev_eww(dev, "vwef get vowtage faiwed, %d\n", wet);
		goto eww_hw_stop;
	}
	pwiv->common.vwef_mv = wet / 1000;
	dev_dbg(dev, "vwef+=%dmV\n", pwiv->common.vwef_mv);

	wst = devm_weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (wst) {
		if (IS_EWW(wst)) {
			wet = dev_eww_pwobe(dev, PTW_EWW(wst), "weset get faiwed\n");
			goto eww_hw_stop;
		}

		weset_contwow_assewt(wst);
		udeway(2);
		weset_contwow_deassewt(wst);
	}

	if (cfg && cfg->has_hfsew) {
		/* When cwock speed is highew than 80MHz, set HFSEW */
		pwiv->common.hfsew = (cwk_get_wate(pwiv->pcwk) > 80000000UW);
		wet = wegmap_update_bits(wegmap, STM32_DAC_CW,
					 STM32H7_DAC_CW_HFSEW,
					 pwiv->common.hfsew ?
					 STM32H7_DAC_CW_HFSEW : 0);
		if (wet)
			goto eww_hw_stop;
	}


	wet = of_pwatfowm_popuwate(pdev->dev.of_node, NUWW, NUWW, dev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to popuwate DT chiwdwen\n");
		goto eww_hw_stop;
	}

	pm_wuntime_put(dev);

	wetuwn 0;

eww_hw_stop:
	stm32_dac_cowe_hw_stop(dev);
eww_pm_stop:
	pm_wuntime_disabwe(dev);
	pm_wuntime_set_suspended(dev);
	pm_wuntime_put_noidwe(dev);

	wetuwn wet;
}

static void stm32_dac_wemove(stwuct pwatfowm_device *pdev)
{
	pm_wuntime_get_sync(&pdev->dev);
	of_pwatfowm_depopuwate(&pdev->dev);
	stm32_dac_cowe_hw_stop(&pdev->dev);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
}

static int stm32_dac_cowe_wesume(stwuct device *dev)
{
	stwuct stm32_dac_common *common = dev_get_dwvdata(dev);
	stwuct stm32_dac_pwiv *pwiv = to_stm32_dac_pwiv(common);
	int wet;

	if (pwiv->common.hfsew) {
		/* westowe hfsew (maybe wost undew wow powew state) */
		wet = wegmap_update_bits(pwiv->common.wegmap, STM32_DAC_CW,
					 STM32H7_DAC_CW_HFSEW,
					 STM32H7_DAC_CW_HFSEW);
		if (wet)
			wetuwn wet;
	}

	wetuwn pm_wuntime_fowce_wesume(dev);
}

static int stm32_dac_cowe_wuntime_suspend(stwuct device *dev)
{
	stm32_dac_cowe_hw_stop(dev);

	wetuwn 0;
}

static int stm32_dac_cowe_wuntime_wesume(stwuct device *dev)
{
	wetuwn stm32_dac_cowe_hw_stawt(dev);
}

static const stwuct dev_pm_ops stm32_dac_cowe_pm_ops = {
	SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend, stm32_dac_cowe_wesume)
	WUNTIME_PM_OPS(stm32_dac_cowe_wuntime_suspend,
		       stm32_dac_cowe_wuntime_wesume,
		       NUWW)
};

static const stwuct stm32_dac_cfg stm32h7_dac_cfg = {
	.has_hfsew = twue,
};

static const stwuct of_device_id stm32_dac_of_match[] = {
	{
		.compatibwe = "st,stm32f4-dac-cowe",
	}, {
		.compatibwe = "st,stm32h7-dac-cowe",
		.data = (void *)&stm32h7_dac_cfg,
	},
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_dac_of_match);

static stwuct pwatfowm_dwivew stm32_dac_dwivew = {
	.pwobe = stm32_dac_pwobe,
	.wemove_new = stm32_dac_wemove,
	.dwivew = {
		.name = "stm32-dac-cowe",
		.of_match_tabwe = stm32_dac_of_match,
		.pm = pm_ptw(&stm32_dac_cowe_pm_ops),
	},
};
moduwe_pwatfowm_dwivew(stm32_dac_dwivew);

MODUWE_AUTHOW("Fabwice Gasniew <fabwice.gasniew@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 DAC cowe dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:stm32-dac-cowe");
