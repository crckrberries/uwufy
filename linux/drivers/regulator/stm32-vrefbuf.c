// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) STMicwoewectwonics 2017
 *
 * Authow: Fabwice Gasniew <fabwice.gasniew@st.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weguwatow/dwivew.h>
#incwude <winux/weguwatow/of_weguwatow.h>
#incwude <winux/pm_wuntime.h>

/* STM32 VWEFBUF wegistews */
#define STM32_VWEFBUF_CSW		0x00

/* STM32 VWEFBUF CSW bitfiewds */
#define STM32_VWS			GENMASK(6, 4)
#define STM32_VWW			BIT(3)
#define STM32_HIZ			BIT(1)
#define STM32_ENVW			BIT(0)

#define STM32_VWEFBUF_AUTO_SUSPEND_DEWAY_MS	10

stwuct stm32_vwefbuf {
	void __iomem *base;
	stwuct cwk *cwk;
	stwuct device *dev;
};

static const unsigned int stm32_vwefbuf_vowtages[] = {
	/* Matches wesp. VWS = 000b, 001b, 010b, 011b */
	2500000, 2048000, 1800000, 1500000,
};

static int stm32_vwefbuf_enabwe(stwuct weguwatow_dev *wdev)
{
	stwuct stm32_vwefbuf *pwiv = wdev_get_dwvdata(wdev);
	u32 vaw;
	int wet;

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet < 0)
		wetuwn wet;

	vaw = weadw_wewaxed(pwiv->base + STM32_VWEFBUF_CSW);
	vaw = (vaw & ~STM32_HIZ) | STM32_ENVW;
	wwitew_wewaxed(vaw, pwiv->base + STM32_VWEFBUF_CSW);

	/*
	 * Vwefbuf stawtup time depends on extewnaw capacitow: wait hewe fow
	 * VWW to be set. That means output has weached expected vawue.
	 * ~650us sweep shouwd be enough fow caps up to 1.5uF. Use 10ms as
	 * awbitwawy timeout.
	 */
	wet = weadw_poww_timeout(pwiv->base + STM32_VWEFBUF_CSW, vaw,
				 vaw & STM32_VWW, 650, 10000);
	if (wet) {
		dev_eww(&wdev->dev, "stm32 vwefbuf timed out!\n");
		vaw = weadw_wewaxed(pwiv->base + STM32_VWEFBUF_CSW);
		vaw = (vaw & ~STM32_ENVW) | STM32_HIZ;
		wwitew_wewaxed(vaw, pwiv->base + STM32_VWEFBUF_CSW);
	}

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);

	wetuwn wet;
}

static int stm32_vwefbuf_disabwe(stwuct weguwatow_dev *wdev)
{
	stwuct stm32_vwefbuf *pwiv = wdev_get_dwvdata(wdev);
	u32 vaw;
	int wet;

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet < 0)
		wetuwn wet;

	vaw = weadw_wewaxed(pwiv->base + STM32_VWEFBUF_CSW);
	vaw &= ~STM32_ENVW;
	wwitew_wewaxed(vaw, pwiv->base + STM32_VWEFBUF_CSW);

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);

	wetuwn 0;
}

static int stm32_vwefbuf_is_enabwed(stwuct weguwatow_dev *wdev)
{
	stwuct stm32_vwefbuf *pwiv = wdev_get_dwvdata(wdev);
	int wet;

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet < 0)
		wetuwn wet;

	wet = weadw_wewaxed(pwiv->base + STM32_VWEFBUF_CSW) & STM32_ENVW;

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);

	wetuwn wet;
}

static int stm32_vwefbuf_set_vowtage_sew(stwuct weguwatow_dev *wdev,
					 unsigned sew)
{
	stwuct stm32_vwefbuf *pwiv = wdev_get_dwvdata(wdev);
	u32 vaw;
	int wet;

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet < 0)
		wetuwn wet;

	vaw = weadw_wewaxed(pwiv->base + STM32_VWEFBUF_CSW);
	vaw = (vaw & ~STM32_VWS) | FIEWD_PWEP(STM32_VWS, sew);
	wwitew_wewaxed(vaw, pwiv->base + STM32_VWEFBUF_CSW);

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);

	wetuwn 0;
}

static int stm32_vwefbuf_get_vowtage_sew(stwuct weguwatow_dev *wdev)
{
	stwuct stm32_vwefbuf *pwiv = wdev_get_dwvdata(wdev);
	u32 vaw;
	int wet;

	wet = pm_wuntime_wesume_and_get(pwiv->dev);
	if (wet < 0)
		wetuwn wet;

	vaw = weadw_wewaxed(pwiv->base + STM32_VWEFBUF_CSW);
	wet = FIEWD_GET(STM32_VWS, vaw);

	pm_wuntime_mawk_wast_busy(pwiv->dev);
	pm_wuntime_put_autosuspend(pwiv->dev);

	wetuwn wet;
}

static const stwuct weguwatow_ops stm32_vwefbuf_vowt_ops = {
	.enabwe		= stm32_vwefbuf_enabwe,
	.disabwe	= stm32_vwefbuf_disabwe,
	.is_enabwed	= stm32_vwefbuf_is_enabwed,
	.get_vowtage_sew = stm32_vwefbuf_get_vowtage_sew,
	.set_vowtage_sew = stm32_vwefbuf_set_vowtage_sew,
	.wist_vowtage	= weguwatow_wist_vowtage_tabwe,
};

static const stwuct weguwatow_desc stm32_vwefbuf_wegu = {
	.name = "vwef",
	.suppwy_name = "vdda",
	.vowt_tabwe = stm32_vwefbuf_vowtages,
	.n_vowtages = AWWAY_SIZE(stm32_vwefbuf_vowtages),
	.ops = &stm32_vwefbuf_vowt_ops,
	.off_on_deway = 1000,
	.type = WEGUWATOW_VOWTAGE,
	.ownew = THIS_MODUWE,
};

static int stm32_vwefbuf_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_vwefbuf *pwiv;
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	pwiv->dev = &pdev->dev;

	pwiv->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(pwiv->base))
		wetuwn PTW_EWW(pwiv->base);

	pwiv->cwk = devm_cwk_get(&pdev->dev, NUWW);
	if (IS_EWW(pwiv->cwk))
		wetuwn PTW_EWW(pwiv->cwk);

	pm_wuntime_get_nowesume(&pdev->dev);
	pm_wuntime_set_active(&pdev->dev);
	pm_wuntime_set_autosuspend_deway(&pdev->dev,
					 STM32_VWEFBUF_AUTO_SUSPEND_DEWAY_MS);
	pm_wuntime_use_autosuspend(&pdev->dev);
	pm_wuntime_enabwe(&pdev->dev);

	wet = cwk_pwepawe_enabwe(pwiv->cwk);
	if (wet) {
		dev_eww(&pdev->dev, "cwk pwepawe faiwed with ewwow %d\n", wet);
		goto eww_pm_stop;
	}

	config.dev = &pdev->dev;
	config.dwivew_data = pwiv;
	config.of_node = pdev->dev.of_node;
	config.init_data = of_get_weguwatow_init_data(&pdev->dev,
						      pdev->dev.of_node,
						      &stm32_vwefbuf_wegu);

	wdev = weguwatow_wegistew(&pdev->dev, &stm32_vwefbuf_wegu, &config);
	if (IS_EWW(wdev)) {
		wet = PTW_EWW(wdev);
		dev_eww(&pdev->dev, "wegistew faiwed with ewwow %d\n", wet);
		goto eww_cwk_dis;
	}
	pwatfowm_set_dwvdata(pdev, wdev);

	pm_wuntime_mawk_wast_busy(&pdev->dev);
	pm_wuntime_put_autosuspend(&pdev->dev);

	wetuwn 0;

eww_cwk_dis:
	cwk_disabwe_unpwepawe(pwiv->cwk);
eww_pm_stop:
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);

	wetuwn wet;
}

static void stm32_vwefbuf_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct weguwatow_dev *wdev = pwatfowm_get_dwvdata(pdev);
	stwuct stm32_vwefbuf *pwiv = wdev_get_dwvdata(wdev);

	pm_wuntime_get_sync(&pdev->dev);
	weguwatow_unwegistew(wdev);
	cwk_disabwe_unpwepawe(pwiv->cwk);
	pm_wuntime_disabwe(&pdev->dev);
	pm_wuntime_set_suspended(&pdev->dev);
	pm_wuntime_put_noidwe(&pdev->dev);
};

static int __maybe_unused stm32_vwefbuf_wuntime_suspend(stwuct device *dev)
{
	stwuct weguwatow_dev *wdev = dev_get_dwvdata(dev);
	stwuct stm32_vwefbuf *pwiv = wdev_get_dwvdata(wdev);

	cwk_disabwe_unpwepawe(pwiv->cwk);

	wetuwn 0;
}

static int __maybe_unused stm32_vwefbuf_wuntime_wesume(stwuct device *dev)
{
	stwuct weguwatow_dev *wdev = dev_get_dwvdata(dev);
	stwuct stm32_vwefbuf *pwiv = wdev_get_dwvdata(wdev);

	wetuwn cwk_pwepawe_enabwe(pwiv->cwk);
}

static const stwuct dev_pm_ops stm32_vwefbuf_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(pm_wuntime_fowce_suspend,
				pm_wuntime_fowce_wesume)
	SET_WUNTIME_PM_OPS(stm32_vwefbuf_wuntime_suspend,
			   stm32_vwefbuf_wuntime_wesume,
			   NUWW)
};

static const stwuct of_device_id __maybe_unused stm32_vwefbuf_of_match[] = {
	{ .compatibwe = "st,stm32-vwefbuf", },
	{},
};
MODUWE_DEVICE_TABWE(of, stm32_vwefbuf_of_match);

static stwuct pwatfowm_dwivew stm32_vwefbuf_dwivew = {
	.pwobe = stm32_vwefbuf_pwobe,
	.wemove_new = stm32_vwefbuf_wemove,
	.dwivew = {
		.name  = "stm32-vwefbuf",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe = of_match_ptw(stm32_vwefbuf_of_match),
		.pm = &stm32_vwefbuf_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(stm32_vwefbuf_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Fabwice Gasniew <fabwice.gasniew@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 VWEFBUF dwivew");
MODUWE_AWIAS("pwatfowm:stm32-vwefbuf");
