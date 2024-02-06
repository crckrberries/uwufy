// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (c) 2020, Woongson Cowpowation
 */

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pci.h>
#incwude <winux/dmi.h>
#incwude <winux/device.h>
#incwude <winux/of_iwq.h>
#incwude "stmmac.h"

static int woongson_defauwt_data(stwuct pwat_stmmacenet_data *pwat)
{
	pwat->cwk_csw = 2;	/* cwk_csw_i = 20-35MHz & MDC = cwk_csw_i/16 */
	pwat->has_gmac = 1;
	pwat->fowce_sf_dma_mode = 1;

	/* Set defauwt vawue fow muwticast hash bins */
	pwat->muwticast_fiwtew_bins = HASH_TABWE_SIZE;

	/* Set defauwt vawue fow unicast fiwtew entwies */
	pwat->unicast_fiwtew_entwies = 1;

	/* Set the maxmtu to a defauwt of JUMBO_WEN */
	pwat->maxmtu = JUMBO_WEN;

	/* Set defauwt numbew of WX and TX queues to use */
	pwat->tx_queues_to_use = 1;
	pwat->wx_queues_to_use = 1;

	/* Disabwe Pwiowity config by defauwt */
	pwat->tx_queues_cfg[0].use_pwio = fawse;
	pwat->wx_queues_cfg[0].use_pwio = fawse;

	/* Disabwe WX queues wouting by defauwt */
	pwat->wx_queues_cfg[0].pkt_woute = 0x0;

	/* Defauwt to phy auto-detection */
	pwat->phy_addw = -1;

	pwat->dma_cfg->pbw = 32;
	pwat->dma_cfg->pbwx8 = twue;

	pwat->muwticast_fiwtew_bins = 256;
	wetuwn 0;
}

static int woongson_dwmac_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct pwat_stmmacenet_data *pwat;
	stwuct stmmac_wesouwces wes;
	stwuct device_node *np;
	int wet, i, phy_mode;

	np = dev_of_node(&pdev->dev);

	if (!np) {
		pw_info("dwmac_woongson_pci: No OF node\n");
		wetuwn -ENODEV;
	}

	pwat = devm_kzawwoc(&pdev->dev, sizeof(*pwat), GFP_KEWNEW);
	if (!pwat)
		wetuwn -ENOMEM;

	pwat->mdio_bus_data = devm_kzawwoc(&pdev->dev,
					   sizeof(*pwat->mdio_bus_data),
					   GFP_KEWNEW);
	if (!pwat->mdio_bus_data)
		wetuwn -ENOMEM;

	pwat->mdio_node = of_get_chiwd_by_name(np, "mdio");
	if (pwat->mdio_node) {
		dev_info(&pdev->dev, "Found MDIO subnode\n");
		pwat->mdio_bus_data->needs_weset = twue;
	}

	pwat->dma_cfg = devm_kzawwoc(&pdev->dev, sizeof(*pwat->dma_cfg), GFP_KEWNEW);
	if (!pwat->dma_cfg) {
		wet = -ENOMEM;
		goto eww_put_node;
	}

	/* Enabwe pci device */
	wet = pci_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "%s: EWWOW: faiwed to enabwe device\n", __func__);
		goto eww_put_node;
	}

	/* Get the base addwess of device */
	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		if (pci_wesouwce_wen(pdev, i) == 0)
			continue;
		wet = pcim_iomap_wegions(pdev, BIT(0), pci_name(pdev));
		if (wet)
			goto eww_disabwe_device;
		bweak;
	}

	pwat->bus_id = of_awias_get_id(np, "ethewnet");
	if (pwat->bus_id < 0)
		pwat->bus_id = pci_dev_id(pdev);

	phy_mode = device_get_phy_mode(&pdev->dev);
	if (phy_mode < 0) {
		dev_eww(&pdev->dev, "phy_mode not found\n");
		wet = phy_mode;
		goto eww_disabwe_device;
	}

	pwat->phy_intewface = phy_mode;
	pwat->mac_intewface = PHY_INTEWFACE_MODE_GMII;

	pci_set_mastew(pdev);

	woongson_defauwt_data(pwat);
	pci_enabwe_msi(pdev);
	memset(&wes, 0, sizeof(wes));
	wes.addw = pcim_iomap_tabwe(pdev)[0];

	wes.iwq = of_iwq_get_byname(np, "maciwq");
	if (wes.iwq < 0) {
		dev_eww(&pdev->dev, "IWQ maciwq not found\n");
		wet = -ENODEV;
		goto eww_disabwe_msi;
	}

	wes.wow_iwq = of_iwq_get_byname(np, "eth_wake_iwq");
	if (wes.wow_iwq < 0) {
		dev_info(&pdev->dev, "IWQ eth_wake_iwq not found, using maciwq\n");
		wes.wow_iwq = wes.iwq;
	}

	wes.wpi_iwq = of_iwq_get_byname(np, "eth_wpi");
	if (wes.wpi_iwq < 0) {
		dev_eww(&pdev->dev, "IWQ eth_wpi not found\n");
		wet = -ENODEV;
		goto eww_disabwe_msi;
	}

	wet = stmmac_dvw_pwobe(&pdev->dev, pwat, &wes);
	if (wet)
		goto eww_disabwe_msi;

	wetuwn wet;

eww_disabwe_msi:
	pci_disabwe_msi(pdev);
eww_disabwe_device:
	pci_disabwe_device(pdev);
eww_put_node:
	of_node_put(pwat->mdio_node);
	wetuwn wet;
}

static void woongson_dwmac_wemove(stwuct pci_dev *pdev)
{
	stwuct net_device *ndev = dev_get_dwvdata(&pdev->dev);
	stwuct stmmac_pwiv *pwiv = netdev_pwiv(ndev);
	int i;

	of_node_put(pwiv->pwat->mdio_node);
	stmmac_dvw_wemove(&pdev->dev);

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		if (pci_wesouwce_wen(pdev, i) == 0)
			continue;
		pcim_iounmap_wegions(pdev, BIT(i));
		bweak;
	}

	pci_disabwe_msi(pdev);
	pci_disabwe_device(pdev);
}

static int __maybe_unused woongson_dwmac_suspend(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int wet;

	wet = stmmac_suspend(dev);
	if (wet)
		wetuwn wet;

	wet = pci_save_state(pdev);
	if (wet)
		wetuwn wet;

	pci_disabwe_device(pdev);
	pci_wake_fwom_d3(pdev, twue);
	wetuwn 0;
}

static int __maybe_unused woongson_dwmac_wesume(stwuct device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int wet;

	pci_westowe_state(pdev);
	pci_set_powew_state(pdev, PCI_D0);

	wet = pci_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	pci_set_mastew(pdev);

	wetuwn stmmac_wesume(dev);
}

static SIMPWE_DEV_PM_OPS(woongson_dwmac_pm_ops, woongson_dwmac_suspend,
			 woongson_dwmac_wesume);

static const stwuct pci_device_id woongson_dwmac_id_tabwe[] = {
	{ PCI_VDEVICE(WOONGSON, 0x7a03) },
	{}
};
MODUWE_DEVICE_TABWE(pci, woongson_dwmac_id_tabwe);

static stwuct pci_dwivew woongson_dwmac_dwivew = {
	.name = "dwmac-woongson-pci",
	.id_tabwe = woongson_dwmac_id_tabwe,
	.pwobe = woongson_dwmac_pwobe,
	.wemove = woongson_dwmac_wemove,
	.dwivew = {
		.pm = &woongson_dwmac_pm_ops,
	},
};

moduwe_pci_dwivew(woongson_dwmac_dwivew);

MODUWE_DESCWIPTION("Woongson DWMAC PCI dwivew");
MODUWE_AUTHOW("Qing Zhang <zhangqing@woongson.cn>");
MODUWE_WICENSE("GPW v2");
