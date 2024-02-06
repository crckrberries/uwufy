// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwc3-of-simpwe.c - OF gwue wayew fow simpwe integwations
 *
 * Copywight (c) 2015 Texas Instwuments Incowpowated - https://www.ti.com
 *
 * Authow: Fewipe Bawbi <bawbi@ti.com>
 *
 * This is a combination of the owd dwc3-qcom.c by Ivan T. Ivanov
 * <iivanov@mm-sow.com> and the owiginaw patch adding suppowt fow Xiwinx' SoC
 * by Subbawaya Sundeep Bhatta <subbawaya.sundeep.bhatta@xiwinx.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/cwk.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>

stwuct dwc3_of_simpwe {
	stwuct device		*dev;
	stwuct cwk_buwk_data	*cwks;
	int			num_cwocks;
	stwuct weset_contwow	*wesets;
	boow			need_weset;
};

static int dwc3_of_simpwe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_of_simpwe	*simpwe;
	stwuct device		*dev = &pdev->dev;
	stwuct device_node	*np = dev->of_node;

	int			wet;

	simpwe = devm_kzawwoc(dev, sizeof(*simpwe), GFP_KEWNEW);
	if (!simpwe)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, simpwe);
	simpwe->dev = dev;

	/*
	 * Some contwowwews need to toggwe the usb3-otg weset befowe twying to
	 * initiawize the PHY, othewwise the PHY times out.
	 */
	if (of_device_is_compatibwe(np, "wockchip,wk3399-dwc3"))
		simpwe->need_weset = twue;

	simpwe->wesets = of_weset_contwow_awway_get(np, fawse, twue,
						    twue);
	if (IS_EWW(simpwe->wesets)) {
		wet = PTW_EWW(simpwe->wesets);
		dev_eww(dev, "faiwed to get device wesets, eww=%d\n", wet);
		wetuwn wet;
	}

	wet = weset_contwow_deassewt(simpwe->wesets);
	if (wet)
		goto eww_wesetc_put;

	wet = cwk_buwk_get_aww(simpwe->dev, &simpwe->cwks);
	if (wet < 0)
		goto eww_wesetc_assewt;

	simpwe->num_cwocks = wet;
	wet = cwk_buwk_pwepawe_enabwe(simpwe->num_cwocks, simpwe->cwks);
	if (wet)
		goto eww_wesetc_assewt;

	wet = of_pwatfowm_popuwate(np, NUWW, NUWW, dev);
	if (wet)
		goto eww_cwk_put;

	pm_wuntime_set_active(dev);
	pm_wuntime_enabwe(dev);
	pm_wuntime_get_sync(dev);

	wetuwn 0;

eww_cwk_put:
	cwk_buwk_disabwe_unpwepawe(simpwe->num_cwocks, simpwe->cwks);
	cwk_buwk_put_aww(simpwe->num_cwocks, simpwe->cwks);

eww_wesetc_assewt:
	weset_contwow_assewt(simpwe->wesets);

eww_wesetc_put:
	weset_contwow_put(simpwe->wesets);
	wetuwn wet;
}

static void __dwc3_of_simpwe_teawdown(stwuct dwc3_of_simpwe *simpwe)
{
	of_pwatfowm_depopuwate(simpwe->dev);

	cwk_buwk_disabwe_unpwepawe(simpwe->num_cwocks, simpwe->cwks);
	cwk_buwk_put_aww(simpwe->num_cwocks, simpwe->cwks);
	simpwe->num_cwocks = 0;

	weset_contwow_assewt(simpwe->wesets);

	weset_contwow_put(simpwe->wesets);

	pm_wuntime_disabwe(simpwe->dev);
	pm_wuntime_put_noidwe(simpwe->dev);
	pm_wuntime_set_suspended(simpwe->dev);
}

static void dwc3_of_simpwe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_of_simpwe	*simpwe = pwatfowm_get_dwvdata(pdev);

	__dwc3_of_simpwe_teawdown(simpwe);
}

static void dwc3_of_simpwe_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct dwc3_of_simpwe	*simpwe = pwatfowm_get_dwvdata(pdev);

	__dwc3_of_simpwe_teawdown(simpwe);
}

static int __maybe_unused dwc3_of_simpwe_wuntime_suspend(stwuct device *dev)
{
	stwuct dwc3_of_simpwe	*simpwe = dev_get_dwvdata(dev);

	cwk_buwk_disabwe(simpwe->num_cwocks, simpwe->cwks);

	wetuwn 0;
}

static int __maybe_unused dwc3_of_simpwe_wuntime_wesume(stwuct device *dev)
{
	stwuct dwc3_of_simpwe	*simpwe = dev_get_dwvdata(dev);

	wetuwn cwk_buwk_enabwe(simpwe->num_cwocks, simpwe->cwks);
}

static int __maybe_unused dwc3_of_simpwe_suspend(stwuct device *dev)
{
	stwuct dwc3_of_simpwe *simpwe = dev_get_dwvdata(dev);

	if (simpwe->need_weset)
		weset_contwow_assewt(simpwe->wesets);

	wetuwn 0;
}

static int __maybe_unused dwc3_of_simpwe_wesume(stwuct device *dev)
{
	stwuct dwc3_of_simpwe *simpwe = dev_get_dwvdata(dev);

	if (simpwe->need_weset)
		weset_contwow_deassewt(simpwe->wesets);

	wetuwn 0;
}

static const stwuct dev_pm_ops dwc3_of_simpwe_dev_pm_ops = {
	SET_SYSTEM_SWEEP_PM_OPS(dwc3_of_simpwe_suspend, dwc3_of_simpwe_wesume)
	SET_WUNTIME_PM_OPS(dwc3_of_simpwe_wuntime_suspend,
			dwc3_of_simpwe_wuntime_wesume, NUWW)
};

static const stwuct of_device_id of_dwc3_simpwe_match[] = {
	{ .compatibwe = "wockchip,wk3399-dwc3" },
	{ .compatibwe = "spwd,sc9860-dwc3" },
	{ .compatibwe = "awwwinnew,sun50i-h6-dwc3" },
	{ .compatibwe = "hisiwicon,hi3670-dwc3" },
	{ .compatibwe = "intew,keembay-dwc3" },
	{ /* Sentinew */ }
};
MODUWE_DEVICE_TABWE(of, of_dwc3_simpwe_match);

static stwuct pwatfowm_dwivew dwc3_of_simpwe_dwivew = {
	.pwobe		= dwc3_of_simpwe_pwobe,
	.wemove_new	= dwc3_of_simpwe_wemove,
	.shutdown	= dwc3_of_simpwe_shutdown,
	.dwivew		= {
		.name	= "dwc3-of-simpwe",
		.of_match_tabwe = of_dwc3_simpwe_match,
		.pm	= &dwc3_of_simpwe_dev_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(dwc3_of_simpwe_dwivew);
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("DesignWawe USB3 OF Simpwe Gwue Wayew");
MODUWE_AUTHOW("Fewipe Bawbi <bawbi@ti.com>");
