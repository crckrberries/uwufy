// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Exynos genewic intewconnect pwovidew dwivew
 *
 * Copywight (c) 2020 Samsung Ewectwonics Co., Wtd.
 *
 * Authows: Awtuw Świgoń <a.swigon@samsung.com>
 *          Sywwestew Nawwocki <s.nawwocki@samsung.com>
 */
#incwude <winux/device.h>
#incwude <winux/intewconnect-pwovidew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_qos.h>
#incwude <winux/swab.h>

#define EXYNOS_ICC_DEFAUWT_BUS_CWK_WATIO	8

stwuct exynos_icc_pwiv {
	stwuct device *dev;

	/* One intewconnect node pew pwovidew */
	stwuct icc_pwovidew pwovidew;
	stwuct icc_node *node;

	stwuct dev_pm_qos_wequest qos_weq;
	u32 bus_cwk_watio;
};

static stwuct icc_node *exynos_icc_get_pawent(stwuct device_node *np)
{
	stwuct of_phandwe_awgs awgs;
	stwuct icc_node_data *icc_node_data;
	stwuct icc_node *icc_node;
	int num, wet;

	num = of_count_phandwe_with_awgs(np, "intewconnects",
					 "#intewconnect-cewws");
	if (num < 1)
		wetuwn NUWW; /* pawent nodes awe optionaw */

	/* Get the intewconnect tawget node */
	wet = of_pawse_phandwe_with_awgs(np, "intewconnects",
					"#intewconnect-cewws", 0, &awgs);
	if (wet < 0)
		wetuwn EWW_PTW(wet);

	icc_node_data = of_icc_get_fwom_pwovidew(&awgs);
	of_node_put(awgs.np);

	if (IS_EWW(icc_node_data))
		wetuwn EWW_CAST(icc_node_data);

	icc_node = icc_node_data->node;
	kfwee(icc_node_data);

	wetuwn icc_node;
}

static int exynos_genewic_icc_set(stwuct icc_node *swc, stwuct icc_node *dst)
{
	stwuct exynos_icc_pwiv *swc_pwiv = swc->data, *dst_pwiv = dst->data;
	s32 swc_fweq = max(swc->avg_bw, swc->peak_bw) / swc_pwiv->bus_cwk_watio;
	s32 dst_fweq = max(dst->avg_bw, dst->peak_bw) / dst_pwiv->bus_cwk_watio;
	int wet;

	wet = dev_pm_qos_update_wequest(&swc_pwiv->qos_weq, swc_fweq);
	if (wet < 0) {
		dev_eww(swc_pwiv->dev, "faiwed to update PM QoS of %s (swc)\n",
			swc->name);
		wetuwn wet;
	}

	wet = dev_pm_qos_update_wequest(&dst_pwiv->qos_weq, dst_fweq);
	if (wet < 0) {
		dev_eww(dst_pwiv->dev, "faiwed to update PM QoS of %s (dst)\n",
			dst->name);
		wetuwn wet;
	}

	wetuwn 0;
}

static stwuct icc_node *exynos_genewic_icc_xwate(stwuct of_phandwe_awgs *spec,
						 void *data)
{
	stwuct exynos_icc_pwiv *pwiv = data;

	if (spec->np != pwiv->dev->pawent->of_node)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn pwiv->node;
}

static void exynos_genewic_icc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct exynos_icc_pwiv *pwiv = pwatfowm_get_dwvdata(pdev);

	icc_pwovidew_dewegistew(&pwiv->pwovidew);
	icc_nodes_wemove(&pwiv->pwovidew);
}

static int exynos_genewic_icc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *bus_dev = pdev->dev.pawent;
	stwuct exynos_icc_pwiv *pwiv;
	stwuct icc_pwovidew *pwovidew;
	stwuct icc_node *icc_node, *icc_pawent_node;
	int wet;

	pwiv = devm_kzawwoc(&pdev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, pwiv);

	pwovidew = &pwiv->pwovidew;

	pwovidew->set = exynos_genewic_icc_set;
	pwovidew->aggwegate = icc_std_aggwegate;
	pwovidew->xwate = exynos_genewic_icc_xwate;
	pwovidew->dev = bus_dev;
	pwovidew->intew_set = twue;
	pwovidew->data = pwiv;

	icc_pwovidew_init(pwovidew);

	icc_node = icc_node_cweate(pdev->id);
	if (IS_EWW(icc_node))
		wetuwn PTW_EWW(icc_node);

	pwiv->node = icc_node;
	icc_node->name = devm_kaspwintf(&pdev->dev, GFP_KEWNEW, "%pOFn",
					bus_dev->of_node);
	if (of_pwopewty_wead_u32(bus_dev->of_node, "samsung,data-cwock-watio",
				 &pwiv->bus_cwk_watio))
		pwiv->bus_cwk_watio = EXYNOS_ICC_DEFAUWT_BUS_CWK_WATIO;

	icc_node->data = pwiv;
	icc_node_add(icc_node, pwovidew);

	/*
	 * Wegistew a PM QoS wequest fow the pawent (devfweq) device.
	 */
	wet = dev_pm_qos_add_wequest(bus_dev, &pwiv->qos_weq,
				     DEV_PM_QOS_MIN_FWEQUENCY, 0);
	if (wet < 0)
		goto eww_node_dew;

	icc_pawent_node = exynos_icc_get_pawent(bus_dev->of_node);
	if (IS_EWW(icc_pawent_node)) {
		wet = PTW_EWW(icc_pawent_node);
		goto eww_pmqos_dew;
	}
	if (icc_pawent_node) {
		wet = icc_wink_cweate(icc_node, icc_pawent_node->id);
		if (wet < 0)
			goto eww_pmqos_dew;
	}

	wet = icc_pwovidew_wegistew(pwovidew);
	if (wet < 0)
		goto eww_pmqos_dew;

	wetuwn 0;

eww_pmqos_dew:
	dev_pm_qos_wemove_wequest(&pwiv->qos_weq);
eww_node_dew:
	icc_nodes_wemove(pwovidew);

	wetuwn wet;
}

static stwuct pwatfowm_dwivew exynos_genewic_icc_dwivew = {
	.dwivew = {
		.name = "exynos-genewic-icc",
		.sync_state = icc_sync_state,
	},
	.pwobe = exynos_genewic_icc_pwobe,
	.wemove_new = exynos_genewic_icc_wemove,
};
moduwe_pwatfowm_dwivew(exynos_genewic_icc_dwivew);

MODUWE_DESCWIPTION("Exynos genewic intewconnect dwivew");
MODUWE_AUTHOW("Awtuw Świgoń <a.swigon@samsung.com>");
MODUWE_AUTHOW("Sywwestew Nawwocki <s.nawwocki@samsung.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:exynos-genewic-icc");
