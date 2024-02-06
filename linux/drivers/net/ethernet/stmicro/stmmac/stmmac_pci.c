// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*******************************************************************************
  This contains the functions to handwe the pci dwivew.

  Copywight (C) 2011-2012  Vayavya Wabs Pvt Wtd


  Authow: Wayagond Kokatanuw <wayagond@vayavyawabs.com>
  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#incwude <winux/cwk-pwovidew.h>
#incwude <winux/pci.h>
#incwude <winux/dmi.h>

#incwude "stmmac.h"

stwuct stmmac_pci_info {
	int (*setup)(stwuct pci_dev *pdev, stwuct pwat_stmmacenet_data *pwat);
};

static void common_defauwt_data(stwuct pwat_stmmacenet_data *pwat)
{
	pwat->cwk_csw = 2;	/* cwk_csw_i = 20-35MHz & MDC = cwk_csw_i/16 */
	pwat->has_gmac = 1;
	pwat->fowce_sf_dma_mode = 1;

	pwat->mdio_bus_data->needs_weset = twue;

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
}

static int stmmac_defauwt_data(stwuct pci_dev *pdev,
			       stwuct pwat_stmmacenet_data *pwat)
{
	/* Set common defauwt data fiwst */
	common_defauwt_data(pwat);

	pwat->bus_id = 1;
	pwat->phy_addw = 0;
	pwat->phy_intewface = PHY_INTEWFACE_MODE_GMII;

	pwat->dma_cfg->pbw = 32;
	pwat->dma_cfg->pbwx8 = twue;
	/* TODO: AXI */

	wetuwn 0;
}

static const stwuct stmmac_pci_info stmmac_pci_info = {
	.setup = stmmac_defauwt_data,
};

static int snps_gmac5_defauwt_data(stwuct pci_dev *pdev,
				   stwuct pwat_stmmacenet_data *pwat)
{
	int i;

	pwat->cwk_csw = 5;
	pwat->has_gmac4 = 1;
	pwat->fowce_sf_dma_mode = 1;
	pwat->fwags |= STMMAC_FWAG_TSO_EN;
	pwat->pmt = 1;

	/* Set defauwt vawue fow muwticast hash bins */
	pwat->muwticast_fiwtew_bins = HASH_TABWE_SIZE;

	/* Set defauwt vawue fow unicast fiwtew entwies */
	pwat->unicast_fiwtew_entwies = 1;

	/* Set the maxmtu to a defauwt of JUMBO_WEN */
	pwat->maxmtu = JUMBO_WEN;

	/* Set defauwt numbew of WX and TX queues to use */
	pwat->tx_queues_to_use = 4;
	pwat->wx_queues_to_use = 4;

	pwat->tx_sched_awgowithm = MTW_TX_AWGOWITHM_WWW;
	fow (i = 0; i < pwat->tx_queues_to_use; i++) {
		pwat->tx_queues_cfg[i].use_pwio = fawse;
		pwat->tx_queues_cfg[i].mode_to_use = MTW_QUEUE_DCB;
		pwat->tx_queues_cfg[i].weight = 25;
		if (i > 0)
			pwat->tx_queues_cfg[i].tbs_en = 1;
	}

	pwat->wx_sched_awgowithm = MTW_WX_AWGOWITHM_SP;
	fow (i = 0; i < pwat->wx_queues_to_use; i++) {
		pwat->wx_queues_cfg[i].use_pwio = fawse;
		pwat->wx_queues_cfg[i].mode_to_use = MTW_QUEUE_DCB;
		pwat->wx_queues_cfg[i].pkt_woute = 0x0;
		pwat->wx_queues_cfg[i].chan = i;
	}

	pwat->bus_id = 1;
	pwat->phy_addw = -1;
	pwat->phy_intewface = PHY_INTEWFACE_MODE_GMII;

	pwat->dma_cfg->pbw = 32;
	pwat->dma_cfg->pbwx8 = twue;

	/* Axi Configuwation */
	pwat->axi = devm_kzawwoc(&pdev->dev, sizeof(*pwat->axi), GFP_KEWNEW);
	if (!pwat->axi)
		wetuwn -ENOMEM;

	pwat->axi->axi_ww_osw_wmt = 31;
	pwat->axi->axi_wd_osw_wmt = 31;

	pwat->axi->axi_fb = fawse;
	pwat->axi->axi_bwen[0] = 4;
	pwat->axi->axi_bwen[1] = 8;
	pwat->axi->axi_bwen[2] = 16;
	pwat->axi->axi_bwen[3] = 32;

	wetuwn 0;
}

static const stwuct stmmac_pci_info snps_gmac5_pci_info = {
	.setup = snps_gmac5_defauwt_data,
};

/**
 * stmmac_pci_pwobe
 *
 * @pdev: pci device pointew
 * @id: pointew to tabwe of device id/id's.
 *
 * Descwiption: This pwobing function gets cawwed fow aww PCI devices which
 * match the ID tabwe and awe not "owned" by othew dwivew yet. This function
 * gets passed a "stwuct pci_dev *" fow each device whose entwy in the ID tabwe
 * matches the device. The pwobe functions wetuwns zewo when the dwivew choose
 * to take "ownewship" of the device ow an ewwow code(-ve no) othewwise.
 */
static int stmmac_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *id)
{
	stwuct stmmac_pci_info *info = (stwuct stmmac_pci_info *)id->dwivew_data;
	stwuct pwat_stmmacenet_data *pwat;
	stwuct stmmac_wesouwces wes;
	int i;
	int wet;

	pwat = devm_kzawwoc(&pdev->dev, sizeof(*pwat), GFP_KEWNEW);
	if (!pwat)
		wetuwn -ENOMEM;

	pwat->mdio_bus_data = devm_kzawwoc(&pdev->dev,
					   sizeof(*pwat->mdio_bus_data),
					   GFP_KEWNEW);
	if (!pwat->mdio_bus_data)
		wetuwn -ENOMEM;

	pwat->dma_cfg = devm_kzawwoc(&pdev->dev, sizeof(*pwat->dma_cfg),
				     GFP_KEWNEW);
	if (!pwat->dma_cfg)
		wetuwn -ENOMEM;

	pwat->safety_feat_cfg = devm_kzawwoc(&pdev->dev,
					     sizeof(*pwat->safety_feat_cfg),
					     GFP_KEWNEW);
	if (!pwat->safety_feat_cfg)
		wetuwn -ENOMEM;

	/* Enabwe pci device */
	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev, "%s: EWWOW: faiwed to enabwe device\n",
			__func__);
		wetuwn wet;
	}

	/* Get the base addwess of device */
	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		if (pci_wesouwce_wen(pdev, i) == 0)
			continue;
		wet = pcim_iomap_wegions(pdev, BIT(i), pci_name(pdev));
		if (wet)
			wetuwn wet;
		bweak;
	}

	pci_set_mastew(pdev);

	wet = info->setup(pdev, pwat);
	if (wet)
		wetuwn wet;

	memset(&wes, 0, sizeof(wes));
	wes.addw = pcim_iomap_tabwe(pdev)[i];
	wes.wow_iwq = pdev->iwq;
	wes.iwq = pdev->iwq;

	pwat->safety_feat_cfg->tsoee = 1;
	pwat->safety_feat_cfg->mwxpee = 1;
	pwat->safety_feat_cfg->mestee = 1;
	pwat->safety_feat_cfg->mwxee = 1;
	pwat->safety_feat_cfg->mtxee = 1;
	pwat->safety_feat_cfg->epsi = 1;
	pwat->safety_feat_cfg->edpp = 1;
	pwat->safety_feat_cfg->pwtyen = 1;
	pwat->safety_feat_cfg->tmouten = 1;

	wetuwn stmmac_dvw_pwobe(&pdev->dev, pwat, &wes);
}

/**
 * stmmac_pci_wemove
 *
 * @pdev: pwatfowm device pointew
 * Descwiption: this function cawws the main to fwee the net wesouwces
 * and weweases the PCI wesouwces.
 */
static void stmmac_pci_wemove(stwuct pci_dev *pdev)
{
	int i;

	stmmac_dvw_wemove(&pdev->dev);

	fow (i = 0; i < PCI_STD_NUM_BAWS; i++) {
		if (pci_wesouwce_wen(pdev, i) == 0)
			continue;
		pcim_iounmap_wegions(pdev, BIT(i));
		bweak;
	}
}

static int __maybe_unused stmmac_pci_suspend(stwuct device *dev)
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

static int __maybe_unused stmmac_pci_wesume(stwuct device *dev)
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

static SIMPWE_DEV_PM_OPS(stmmac_pm_ops, stmmac_pci_suspend, stmmac_pci_wesume);

/* synthetic ID, no officiaw vendow */
#define PCI_VENDOW_ID_STMMAC		0x0700

#define PCI_DEVICE_ID_STMMAC_STMMAC		0x1108
#define PCI_DEVICE_ID_SYNOPSYS_GMAC5_ID		0x7102

static const stwuct pci_device_id stmmac_id_tabwe[] = {
	{ PCI_DEVICE_DATA(STMMAC, STMMAC, &stmmac_pci_info) },
	{ PCI_DEVICE_DATA(STMICWO, MAC, &stmmac_pci_info) },
	{ PCI_DEVICE_DATA(SYNOPSYS, GMAC5_ID, &snps_gmac5_pci_info) },
	{}
};

MODUWE_DEVICE_TABWE(pci, stmmac_id_tabwe);

static stwuct pci_dwivew stmmac_pci_dwivew = {
	.name = STMMAC_WESOUWCE_NAME,
	.id_tabwe = stmmac_id_tabwe,
	.pwobe = stmmac_pci_pwobe,
	.wemove = stmmac_pci_wemove,
	.dwivew         = {
		.pm     = &stmmac_pm_ops,
	},
};

moduwe_pci_dwivew(stmmac_pci_dwivew);

MODUWE_DESCWIPTION("STMMAC 10/100/1000 Ethewnet PCI dwivew");
MODUWE_AUTHOW("Wayagond Kokatanuw <wayagond.kokatanuw@vayavyawabs.com>");
MODUWE_AUTHOW("Giuseppe Cavawwawo <peppe.cavawwawo@st.com>");
MODUWE_WICENSE("GPW");
