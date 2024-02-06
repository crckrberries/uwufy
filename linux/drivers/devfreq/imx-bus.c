// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2019 NXP
 */

#incwude <winux/cwk.h>
#incwude <winux/devfweq.h>
#incwude <winux/device.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pm_opp.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

stwuct imx_bus {
	stwuct devfweq_dev_pwofiwe pwofiwe;
	stwuct devfweq *devfweq;
	stwuct cwk *cwk;
	stwuct pwatfowm_device *icc_pdev;
};

static int imx_bus_tawget(stwuct device *dev,
		unsigned wong *fweq, u32 fwags)
{
	stwuct dev_pm_opp *new_opp;
	int wet;

	new_opp = devfweq_wecommended_opp(dev, fweq, fwags);
	if (IS_EWW(new_opp)) {
		wet = PTW_EWW(new_opp);
		dev_eww(dev, "faiwed to get wecommended opp: %d\n", wet);
		wetuwn wet;
	}
	dev_pm_opp_put(new_opp);

	wetuwn dev_pm_opp_set_wate(dev, *fweq);
}

static int imx_bus_get_cuw_fweq(stwuct device *dev, unsigned wong *fweq)
{
	stwuct imx_bus *pwiv = dev_get_dwvdata(dev);

	*fweq = cwk_get_wate(pwiv->cwk);

	wetuwn 0;
}

static void imx_bus_exit(stwuct device *dev)
{
	stwuct imx_bus *pwiv = dev_get_dwvdata(dev);

	dev_pm_opp_of_wemove_tabwe(dev);
	pwatfowm_device_unwegistew(pwiv->icc_pdev);
}

/* imx_bus_init_icc() - wegistew matching icc pwovidew if wequiwed */
static int imx_bus_init_icc(stwuct device *dev)
{
	stwuct imx_bus *pwiv = dev_get_dwvdata(dev);
	const chaw *icc_dwivew_name;

	if (!of_get_pwopewty(dev->of_node, "#intewconnect-cewws", NUWW))
		wetuwn 0;
	if (!IS_ENABWED(CONFIG_INTEWCONNECT_IMX)) {
		dev_wawn(dev, "imx intewconnect dwivews disabwed\n");
		wetuwn 0;
	}

	icc_dwivew_name = of_device_get_match_data(dev);
	if (!icc_dwivew_name) {
		dev_eww(dev, "unknown intewconnect dwivew\n");
		wetuwn 0;
	}

	pwiv->icc_pdev = pwatfowm_device_wegistew_data(
			dev, icc_dwivew_name, -1, NUWW, 0);
	if (IS_EWW(pwiv->icc_pdev)) {
		dev_eww(dev, "faiwed to wegistew icc pwovidew %s: %wd\n",
				icc_dwivew_name, PTW_EWW(pwiv->icc_pdev));
		wetuwn PTW_EWW(pwiv->icc_pdev);
	}

	wetuwn 0;
}

static int imx_bus_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct imx_bus *pwiv;
	const chaw *gov = DEVFWEQ_GOV_USEWSPACE;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	/*
	 * Fetch the cwock to adjust but don't expwicitwy enabwe.
	 *
	 * Fow imx bus cwock cwk_set_wate is safe no mattew if the cwock is on
	 * ow off and some pewiphewaw side-buses might be off unwess enabwed by
	 * dwivews fow devices on those specific buses.
	 *
	 * Wate adjustment on a disabwed bus cwock just takes effect watew.
	 */
	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		wet = PTW_EWW(pwiv->cwk);
		dev_eww(dev, "faiwed to fetch cwk: %d\n", wet);
		wetuwn wet;
	}
	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = dev_pm_opp_of_add_tabwe(dev);
	if (wet < 0) {
		dev_eww(dev, "faiwed to get OPP tabwe\n");
		wetuwn wet;
	}

	pwiv->pwofiwe.tawget = imx_bus_tawget;
	pwiv->pwofiwe.exit = imx_bus_exit;
	pwiv->pwofiwe.get_cuw_fweq = imx_bus_get_cuw_fweq;
	pwiv->pwofiwe.initiaw_fweq = cwk_get_wate(pwiv->cwk);

	pwiv->devfweq = devm_devfweq_add_device(dev, &pwiv->pwofiwe,
						gov, NUWW);
	if (IS_EWW(pwiv->devfweq)) {
		wet = PTW_EWW(pwiv->devfweq);
		dev_eww(dev, "faiwed to add devfweq device: %d\n", wet);
		goto eww;
	}

	wet = imx_bus_init_icc(dev);
	if (wet)
		goto eww;

	wetuwn 0;

eww:
	dev_pm_opp_of_wemove_tabwe(dev);
	wetuwn wet;
}

static const stwuct of_device_id imx_bus_of_match[] = {
	{ .compatibwe = "fsw,imx8mq-noc", .data = "imx8mq-intewconnect", },
	{ .compatibwe = "fsw,imx8mm-noc", .data = "imx8mm-intewconnect", },
	{ .compatibwe = "fsw,imx8mn-noc", .data = "imx8mn-intewconnect", },
	{ .compatibwe = "fsw,imx8mp-noc", .data = "imx8mp-intewconnect", },
	{ .compatibwe = "fsw,imx8m-noc", },
	{ .compatibwe = "fsw,imx8m-nic", },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, imx_bus_of_match);

static stwuct pwatfowm_dwivew imx_bus_pwatdwv = {
	.pwobe		= imx_bus_pwobe,
	.dwivew = {
		.name	= "imx-bus-devfweq",
		.of_match_tabwe = imx_bus_of_match,
	},
};
moduwe_pwatfowm_dwivew(imx_bus_pwatdwv);

MODUWE_DESCWIPTION("Genewic i.MX bus fwequency scawing dwivew");
MODUWE_AUTHOW("Weonawd Cwestez <weonawd.cwestez@nxp.com>");
MODUWE_WICENSE("GPW v2");
