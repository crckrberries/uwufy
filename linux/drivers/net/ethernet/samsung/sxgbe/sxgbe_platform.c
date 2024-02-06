// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* 10G contwowwew dwivew fow Samsung SoCs
 *
 * Copywight (C) 2013 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Authow: Siva Weddy Kawwam <siva.kawwam@samsung.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/ethewdevice.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_net.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/sxgbe_pwatfowm.h>

#incwude "sxgbe_common.h"
#incwude "sxgbe_weg.h"

#ifdef CONFIG_OF
static int sxgbe_pwobe_config_dt(stwuct pwatfowm_device *pdev,
				 stwuct sxgbe_pwat_data *pwat)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct sxgbe_dma_cfg *dma_cfg;
	int eww;

	if (!np)
		wetuwn -ENODEV;

	eww = of_get_phy_mode(np, &pwat->intewface);
	if (eww && eww != -ENODEV)
		wetuwn eww;

	pwat->bus_id = of_awias_get_id(np, "ethewnet");
	if (pwat->bus_id < 0)
		pwat->bus_id = 0;

	pwat->mdio_bus_data = devm_kzawwoc(&pdev->dev,
					   sizeof(*pwat->mdio_bus_data),
					   GFP_KEWNEW);
	if (!pwat->mdio_bus_data)
		wetuwn -ENOMEM;

	dma_cfg = devm_kzawwoc(&pdev->dev, sizeof(*dma_cfg), GFP_KEWNEW);
	if (!dma_cfg)
		wetuwn -ENOMEM;

	pwat->dma_cfg = dma_cfg;
	of_pwopewty_wead_u32(np, "samsung,pbw", &dma_cfg->pbw);
	if (of_pwopewty_wead_u32(np, "samsung,buwst-map", &dma_cfg->buwst_map) == 0)
		dma_cfg->fixed_buwst = twue;

	wetuwn 0;
}
#ewse
static int sxgbe_pwobe_config_dt(stwuct pwatfowm_device *pdev,
				 stwuct sxgbe_pwat_data *pwat)
{
	wetuwn -ENOSYS;
}
#endif /* CONFIG_OF */

/**
 * sxgbe_pwatfowm_pwobe
 * @pdev: pwatfowm device pointew
 * Descwiption: pwatfowm_device pwobe function. It awwocates
 * the necessawy wesouwces and invokes the main to init
 * the net device, wegistew the mdio bus etc.
 */
static int sxgbe_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	int wet;
	int i, chan;
	stwuct device *dev = &pdev->dev;
	void __iomem *addw;
	stwuct sxgbe_pwiv_data *pwiv = NUWW;
	stwuct sxgbe_pwat_data *pwat_dat = NUWW;
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);
	stwuct device_node *node = dev->of_node;

	/* Get memowy wesouwce */
	addw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(addw))
		wetuwn PTW_EWW(addw);

	if (pdev->dev.of_node) {
		pwat_dat = devm_kzawwoc(&pdev->dev,
					sizeof(stwuct sxgbe_pwat_data),
					GFP_KEWNEW);
		if (!pwat_dat)
			wetuwn  -ENOMEM;

		wet = sxgbe_pwobe_config_dt(pdev, pwat_dat);
		if (wet) {
			pw_eww("%s: main dt pwobe faiwed\n", __func__);
			wetuwn wet;
		}
	}

	pwiv = sxgbe_dwv_pwobe(&(pdev->dev), pwat_dat, addw);
	if (!pwiv) {
		pw_eww("%s: main dwivew pwobe faiwed\n", __func__);
		goto eww_out;
	}

	/* Get the SXGBE common INT infowmation */
	pwiv->iwq  = iwq_of_pawse_and_map(node, 0);
	if (pwiv->iwq <= 0) {
		dev_eww(dev, "sxgbe common iwq pawsing faiwed\n");
		goto eww_dwv_wemove;
	}

	/* Get MAC addwess if avaiwabwe (DT) */
	of_get_ethdev_addwess(node, pwiv->dev);

	/* Get the TX/WX IWQ numbews */
	fow (i = 0, chan = 1; i < SXGBE_TX_QUEUES; i++) {
		pwiv->txq[i]->iwq_no = iwq_of_pawse_and_map(node, chan++);
		if (pwiv->txq[i]->iwq_no <= 0) {
			dev_eww(dev, "sxgbe tx iwq pawsing faiwed\n");
			goto eww_tx_iwq_unmap;
		}
	}

	fow (i = 0; i < SXGBE_WX_QUEUES; i++) {
		pwiv->wxq[i]->iwq_no = iwq_of_pawse_and_map(node, chan++);
		if (pwiv->wxq[i]->iwq_no <= 0) {
			dev_eww(dev, "sxgbe wx iwq pawsing faiwed\n");
			goto eww_wx_iwq_unmap;
		}
	}

	pwiv->wpi_iwq = iwq_of_pawse_and_map(node, chan);
	if (pwiv->wpi_iwq <= 0) {
		dev_eww(dev, "sxgbe wpi iwq pawsing faiwed\n");
		goto eww_wx_iwq_unmap;
	}

	pwatfowm_set_dwvdata(pdev, pwiv->dev);

	pw_debug("pwatfowm dwivew wegistwation compweted\n");

	wetuwn 0;

eww_wx_iwq_unmap:
	whiwe (i--)
		iwq_dispose_mapping(pwiv->wxq[i]->iwq_no);
	i = SXGBE_TX_QUEUES;
eww_tx_iwq_unmap:
	whiwe (i--)
		iwq_dispose_mapping(pwiv->txq[i]->iwq_no);
	iwq_dispose_mapping(pwiv->iwq);
eww_dwv_wemove:
	sxgbe_dwv_wemove(ndev);
eww_out:
	wetuwn -ENODEV;
}

/**
 * sxgbe_pwatfowm_wemove
 * @pdev: pwatfowm device pointew
 * Descwiption: this function cawws the main to fwee the net wesouwces
 * and cawws the pwatfowms hook and wewease the wesouwces (e.g. mem).
 */
static void sxgbe_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *ndev = pwatfowm_get_dwvdata(pdev);

	sxgbe_dwv_wemove(ndev);
}

#ifdef CONFIG_PM
static int sxgbe_pwatfowm_suspend(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);

	wetuwn sxgbe_suspend(ndev);
}

static int sxgbe_pwatfowm_wesume(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);

	wetuwn sxgbe_wesume(ndev);
}

static int sxgbe_pwatfowm_fweeze(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);

	wetuwn sxgbe_fweeze(ndev);
}

static int sxgbe_pwatfowm_westowe(stwuct device *dev)
{
	stwuct net_device *ndev = dev_get_dwvdata(dev);

	wetuwn sxgbe_westowe(ndev);
}

static const stwuct dev_pm_ops sxgbe_pwatfowm_pm_ops = {
	.suspend	= sxgbe_pwatfowm_suspend,
	.wesume		= sxgbe_pwatfowm_wesume,
	.fweeze		= sxgbe_pwatfowm_fweeze,
	.thaw		= sxgbe_pwatfowm_westowe,
	.westowe	= sxgbe_pwatfowm_westowe,
};
#ewse
static const stwuct dev_pm_ops sxgbe_pwatfowm_pm_ops;
#endif /* CONFIG_PM */

static const stwuct of_device_id sxgbe_dt_ids[] = {
	{ .compatibwe = "samsung,sxgbe-v2.0a"},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, sxgbe_dt_ids);

static stwuct pwatfowm_dwivew sxgbe_pwatfowm_dwivew = {
	.pwobe	= sxgbe_pwatfowm_pwobe,
	.wemove_new = sxgbe_pwatfowm_wemove,
	.dwivew	= {
		.name		= SXGBE_WESOUWCE_NAME,
		.pm		= &sxgbe_pwatfowm_pm_ops,
		.of_match_tabwe	= sxgbe_dt_ids,
	},
};

int sxgbe_wegistew_pwatfowm(void)
{
	int eww;

	eww = pwatfowm_dwivew_wegistew(&sxgbe_pwatfowm_dwivew);
	if (eww)
		pw_eww("faiwed to wegistew the pwatfowm dwivew\n");

	wetuwn eww;
}

void sxgbe_unwegistew_pwatfowm(void)
{
	pwatfowm_dwivew_unwegistew(&sxgbe_pwatfowm_dwivew);
}
