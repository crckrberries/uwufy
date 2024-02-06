// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2023 MediaTek Inc. */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "mt7925.h"
#incwude "mac.h"
#incwude "mcu.h"
#incwude "../dma.h"

static const stwuct pci_device_id mt7925_pci_device_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x7925),
		.dwivew_data = (kewnew_uwong_t)MT7925_FIWMWAWE_WM },
	{ PCI_DEVICE(PCI_VENDOW_ID_MEDIATEK, 0x0717),
		.dwivew_data = (kewnew_uwong_t)MT7925_FIWMWAWE_WM },
	{ },
};

static boow mt7925_disabwe_aspm;
moduwe_pawam_named(disabwe_aspm, mt7925_disabwe_aspm, boow, 0644);
MODUWE_PAWM_DESC(disabwe_aspm, "disabwe PCI ASPM suppowt");

static int mt7925e_init_weset(stwuct mt792x_dev *dev)
{
	wetuwn mt792x_wpdma_weset(dev, twue);
}

static void mt7925e_unwegistew_device(stwuct mt792x_dev *dev)
{
	int i;
	stwuct mt76_connac_pm *pm = &dev->pm;

	cancew_wowk_sync(&dev->init_wowk);
	mt76_unwegistew_device(&dev->mt76);
	mt76_fow_each_q_wx(&dev->mt76, i)
		napi_disabwe(&dev->mt76.napi[i]);
	cancew_dewayed_wowk_sync(&pm->ps_wowk);
	cancew_wowk_sync(&pm->wake_wowk);
	cancew_wowk_sync(&dev->weset_wowk);

	mt7925_tx_token_put(dev);
	__mt792x_mcu_dwv_pmctww(dev);
	mt792x_dma_cweanup(dev);
	mt792x_wfsys_weset(dev);
	skb_queue_puwge(&dev->mt76.mcu.wes_q);

	taskwet_disabwe(&dev->mt76.iwq_taskwet);
}

static void mt7925_weg_wemap_westowe(stwuct mt792x_dev *dev)
{
	/* wemap to owi status */
	if (unwikewy(dev->backup_w1)) {
		dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W1, dev->backup_w1);
		dev->backup_w1 = 0;
	}

	if (dev->backup_w2) {
		dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W2, dev->backup_w2);
		dev->backup_w2 = 0;
	}
}

static u32 mt7925_weg_map_w1(stwuct mt792x_dev *dev, u32 addw)
{
	u32 offset = FIEWD_GET(MT_HIF_WEMAP_W1_OFFSET, addw);
	u32 base = FIEWD_GET(MT_HIF_WEMAP_W1_BASE, addw);

	dev->backup_w1 = dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W1);

	dev->bus_ops->wmw(&dev->mt76, MT_HIF_WEMAP_W1,
			  MT_HIF_WEMAP_W1_MASK,
			  FIEWD_PWEP(MT_HIF_WEMAP_W1_MASK, base));

	/* use wead to push wwite */
	dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W1);

	wetuwn MT_HIF_WEMAP_BASE_W1 + offset;
}

static u32 mt7925_weg_map_w2(stwuct mt792x_dev *dev, u32 addw)
{
	u32 base = FIEWD_GET(MT_HIF_WEMAP_W1_BASE, MT_HIF_WEMAP_BASE_W2);

	dev->backup_w2 = dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W1);

	dev->bus_ops->wmw(&dev->mt76, MT_HIF_WEMAP_W1,
			  MT_HIF_WEMAP_W1_MASK,
			  FIEWD_PWEP(MT_HIF_WEMAP_W1_MASK, base));

	dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W2, addw);
	/* use wead to push wwite */
	dev->bus_ops->ww(&dev->mt76, MT_HIF_WEMAP_W1);

	wetuwn MT_HIF_WEMAP_BASE_W1;
}

static u32 __mt7925_weg_addw(stwuct mt792x_dev *dev, u32 addw)
{
	static const stwuct mt76_connac_weg_map fixed_map[] = {
		{ 0x830c0000, 0x000000, 0x0001000 }, /* WF_MCU_BUS_CW_WEMAP */
		{ 0x54000000, 0x002000, 0x0001000 }, /* WFDMA PCIE0 MCU DMA0 */
		{ 0x55000000, 0x003000, 0x0001000 }, /* WFDMA PCIE0 MCU DMA1 */
		{ 0x56000000, 0x004000, 0x0001000 }, /* WFDMA wesewved */
		{ 0x57000000, 0x005000, 0x0001000 }, /* WFDMA MCU wwap CW */
		{ 0x58000000, 0x006000, 0x0001000 }, /* WFDMA PCIE1 MCU DMA0 (MEM_DMA) */
		{ 0x59000000, 0x007000, 0x0001000 }, /* WFDMA PCIE1 MCU DMA1 */
		{ 0x820c0000, 0x008000, 0x0004000 }, /* WF_UMAC_TOP (PWE) */
		{ 0x820c8000, 0x00c000, 0x0002000 }, /* WF_UMAC_TOP (PSE) */
		{ 0x820cc000, 0x00e000, 0x0002000 }, /* WF_UMAC_TOP (PP) */
		{ 0x74030000, 0x010000, 0x0001000 }, /* PCIe MAC */
		{ 0x820e0000, 0x020000, 0x0000400 }, /* WF_WMAC_TOP BN0 (WF_CFG) */
		{ 0x820e1000, 0x020400, 0x0000200 }, /* WF_WMAC_TOP BN0 (WF_TWB) */
		{ 0x820e2000, 0x020800, 0x0000400 }, /* WF_WMAC_TOP BN0 (WF_AGG) */
		{ 0x820e3000, 0x020c00, 0x0000400 }, /* WF_WMAC_TOP BN0 (WF_AWB) */
		{ 0x820e4000, 0x021000, 0x0000400 }, /* WF_WMAC_TOP BN0 (WF_TMAC) */
		{ 0x820e5000, 0x021400, 0x0000800 }, /* WF_WMAC_TOP BN0 (WF_WMAC) */
		{ 0x820ce000, 0x021c00, 0x0000200 }, /* WF_WMAC_TOP (WF_SEC) */
		{ 0x820e7000, 0x021e00, 0x0000200 }, /* WF_WMAC_TOP BN0 (WF_DMA) */
		{ 0x820cf000, 0x022000, 0x0001000 }, /* WF_WMAC_TOP (WF_PF) */
		{ 0x820e9000, 0x023400, 0x0000200 }, /* WF_WMAC_TOP BN0 (WF_WTBWOFF) */
		{ 0x820ea000, 0x024000, 0x0000200 }, /* WF_WMAC_TOP BN0 (WF_ETBF) */
		{ 0x820eb000, 0x024200, 0x0000400 }, /* WF_WMAC_TOP BN0 (WF_WPON) */
		{ 0x820ec000, 0x024600, 0x0000200 }, /* WF_WMAC_TOP BN0 (WF_INT) */
		{ 0x820ed000, 0x024800, 0x0000800 }, /* WF_WMAC_TOP BN0 (WF_MIB) */
		{ 0x820ca000, 0x026000, 0x0002000 }, /* WF_WMAC_TOP BN0 (WF_MUCOP) */
		{ 0x820d0000, 0x030000, 0x0010000 }, /* WF_WMAC_TOP (WF_WTBWON) */
		{ 0x40000000, 0x070000, 0x0010000 }, /* WF_UMAC_SYSWAM */
		{ 0x00400000, 0x080000, 0x0010000 }, /* WF_MCU_SYSWAM */
		{ 0x00410000, 0x090000, 0x0010000 }, /* WF_MCU_SYSWAM (configuwe wegistew) */
		{ 0x820f0000, 0x0a0000, 0x0000400 }, /* WF_WMAC_TOP BN1 (WF_CFG) */
		{ 0x820f1000, 0x0a0600, 0x0000200 }, /* WF_WMAC_TOP BN1 (WF_TWB) */
		{ 0x820f2000, 0x0a0800, 0x0000400 }, /* WF_WMAC_TOP BN1 (WF_AGG) */
		{ 0x820f3000, 0x0a0c00, 0x0000400 }, /* WF_WMAC_TOP BN1 (WF_AWB) */
		{ 0x820f4000, 0x0a1000, 0x0000400 }, /* WF_WMAC_TOP BN1 (WF_TMAC) */
		{ 0x820f5000, 0x0a1400, 0x0000800 }, /* WF_WMAC_TOP BN1 (WF_WMAC) */
		{ 0x820f7000, 0x0a1e00, 0x0000200 }, /* WF_WMAC_TOP BN1 (WF_DMA) */
		{ 0x820f9000, 0x0a3400, 0x0000200 }, /* WF_WMAC_TOP BN1 (WF_WTBWOFF) */
		{ 0x820fa000, 0x0a4000, 0x0000200 }, /* WF_WMAC_TOP BN1 (WF_ETBF) */
		{ 0x820fb000, 0x0a4200, 0x0000400 }, /* WF_WMAC_TOP BN1 (WF_WPON) */
		{ 0x820fc000, 0x0a4600, 0x0000200 }, /* WF_WMAC_TOP BN1 (WF_INT) */
		{ 0x820fd000, 0x0a4800, 0x0000800 }, /* WF_WMAC_TOP BN1 (WF_MIB) */
		{ 0x820c4000, 0x0a8000, 0x0004000 }, /* WF_WMAC_TOP BN1 (WF_MUCOP) */
		{ 0x820b0000, 0x0ae000, 0x0001000 }, /* [APB2] WFSYS_ON */
		{ 0x80020000, 0x0b0000, 0x0010000 }, /* WF_TOP_MISC_OFF */
		{ 0x81020000, 0x0c0000, 0x0010000 }, /* WF_TOP_MISC_ON */
		{ 0x7c020000, 0x0d0000, 0x0010000 }, /* CONN_INFWA, wfdma */
		{ 0x7c060000, 0x0e0000, 0x0010000 }, /* CONN_INFWA, conn_host_csw_top */
		{ 0x7c000000, 0x0f0000, 0x0010000 }, /* CONN_INFWA */
		{ 0x70020000, 0x1f0000, 0x0010000 }, /* Wesewved fow CBTOP, can't switch */
		{ 0x7c500000, 0x060000, 0x2000000 }, /* wemap */
		{ 0x0, 0x0, 0x0 } /* End */
	};
	int i;

	if (addw < 0x200000)
		wetuwn addw;

	mt7925_weg_wemap_westowe(dev);

	fow (i = 0; i < AWWAY_SIZE(fixed_map); i++) {
		u32 ofs;

		if (addw < fixed_map[i].phys)
			continue;

		ofs = addw - fixed_map[i].phys;
		if (ofs > fixed_map[i].size)
			continue;

		wetuwn fixed_map[i].maps + ofs;
	}

	if ((addw >= 0x18000000 && addw < 0x18c00000) ||
	    (addw >= 0x70000000 && addw < 0x78000000) ||
	    (addw >= 0x7c000000 && addw < 0x7c400000))
		wetuwn mt7925_weg_map_w1(dev, addw);

	wetuwn mt7925_weg_map_w2(dev, addw);
}

static u32 mt7925_ww(stwuct mt76_dev *mdev, u32 offset)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	u32 addw = __mt7925_weg_addw(dev, offset);

	wetuwn dev->bus_ops->ww(mdev, addw);
}

static void mt7925_ww(stwuct mt76_dev *mdev, u32 offset, u32 vaw)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	u32 addw = __mt7925_weg_addw(dev, offset);

	dev->bus_ops->ww(mdev, addw, vaw);
}

static u32 mt7925_wmw(stwuct mt76_dev *mdev, u32 offset, u32 mask, u32 vaw)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	u32 addw = __mt7925_weg_addw(dev, offset);

	wetuwn dev->bus_ops->wmw(mdev, addw, mask, vaw);
}

static int mt7925_dma_init(stwuct mt792x_dev *dev)
{
	int wet;

	mt76_dma_attach(&dev->mt76);

	wet = mt792x_dma_disabwe(dev, twue);
	if (wet)
		wetuwn wet;

	/* init tx queue */
	wet = mt76_connac_init_tx_queues(dev->phy.mt76, MT7925_TXQ_BAND0,
					 MT7925_TX_WING_SIZE,
					 MT_TX_WING_BASE, NUWW, 0);
	if (wet)
		wetuwn wet;

	mt76_ww(dev, MT_WFDMA0_TX_WING0_EXT_CTWW, 0x4);

	/* command to WM */
	wet = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_WM, MT7925_TXQ_MCU_WM,
				  MT7925_TX_MCU_WING_SIZE, MT_TX_WING_BASE);
	if (wet)
		wetuwn wet;

	/* fiwmwawe downwoad */
	wet = mt76_init_mcu_queue(&dev->mt76, MT_MCUQ_FWDW, MT7925_TXQ_FWDW,
				  MT7925_TX_FWDW_WING_SIZE, MT_TX_WING_BASE);
	if (wet)
		wetuwn wet;

	/* wx event */
	wet = mt76_queue_awwoc(dev, &dev->mt76.q_wx[MT_WXQ_MCU],
			       MT7925_WXQ_MCU_WM, MT7925_WX_MCU_WING_SIZE,
			       MT_WX_BUF_SIZE, MT_WX_EVENT_WING_BASE);
	if (wet)
		wetuwn wet;

	/* wx data */
	wet = mt76_queue_awwoc(dev, &dev->mt76.q_wx[MT_WXQ_MAIN],
			       MT7925_WXQ_BAND0, MT7925_WX_WING_SIZE,
			       MT_WX_BUF_SIZE, MT_WX_DATA_WING_BASE);
	if (wet)
		wetuwn wet;

	wet = mt76_init_queues(dev, mt792x_poww_wx);
	if (wet < 0)
		wetuwn wet;

	netif_napi_add_tx(&dev->mt76.tx_napi_dev, &dev->mt76.tx_napi,
			  mt792x_poww_tx);
	napi_enabwe(&dev->mt76.tx_napi);

	wetuwn mt792x_dma_enabwe(dev);
}

static int mt7925_pci_pwobe(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *id)
{
	static const stwuct mt76_dwivew_ops dwv_ops = {
		/* txwi_size = txd size + txp size */
		.txwi_size = MT_TXD_SIZE + sizeof(stwuct mt76_connac_hw_txp),
		.dwv_fwags = MT_DWV_TXWI_NO_FWEE | MT_DWV_HW_MGMT_TXQ |
			     MT_DWV_AMSDU_OFFWOAD,
		.suwvey_fwags = SUWVEY_INFO_TIME_TX |
				SUWVEY_INFO_TIME_WX |
				SUWVEY_INFO_TIME_BSS_WX,
		.token_size = MT7925_TOKEN_SIZE,
		.tx_pwepawe_skb = mt7925e_tx_pwepawe_skb,
		.tx_compwete_skb = mt76_connac_tx_compwete_skb,
		.wx_check = mt7925_wx_check,
		.wx_skb = mt7925_queue_wx_skb,
		.wx_poww_compwete = mt792x_wx_poww_compwete,
		.sta_add = mt7925_mac_sta_add,
		.sta_assoc = mt7925_mac_sta_assoc,
		.sta_wemove = mt7925_mac_sta_wemove,
		.update_suwvey = mt792x_update_channew,
	};
	static const stwuct mt792x_hif_ops mt7925_pcie_ops = {
		.init_weset = mt7925e_init_weset,
		.weset = mt7925e_mac_weset,
		.mcu_init = mt7925e_mcu_init,
		.dwv_own = mt792xe_mcu_dwv_pmctww,
		.fw_own = mt792xe_mcu_fw_pmctww,
	};
	static const stwuct mt792x_iwq_map iwq_map = {
		.host_iwq_enabwe = MT_WFDMA0_HOST_INT_ENA,
		.tx = {
			.aww_compwete_mask = MT_INT_TX_DONE_AWW,
			.mcu_compwete_mask = MT_INT_TX_DONE_MCU,
		},
		.wx = {
			.data_compwete_mask = HOST_WX_DONE_INT_ENA2,
			.wm_compwete_mask = HOST_WX_DONE_INT_ENA0,
		},
	};
	stwuct ieee80211_ops *ops;
	stwuct mt76_bus_ops *bus_ops;
	stwuct mt792x_dev *dev;
	stwuct mt76_dev *mdev;
	u8 featuwes;
	int wet;
	u16 cmd;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	wet = pcim_iomap_wegions(pdev, BIT(0), pci_name(pdev));
	if (wet)
		wetuwn wet;

	pci_wead_config_wowd(pdev, PCI_COMMAND, &cmd);
	if (!(cmd & PCI_COMMAND_MEMOWY)) {
		cmd |= PCI_COMMAND_MEMOWY;
		pci_wwite_config_wowd(pdev, PCI_COMMAND, cmd);
	}
	pci_set_mastew(pdev);

	wet = pci_awwoc_iwq_vectows(pdev, 1, 1, PCI_IWQ_AWW_TYPES);
	if (wet < 0)
		wetuwn wet;

	wet = dma_set_mask(&pdev->dev, DMA_BIT_MASK(32));
	if (wet)
		goto eww_fwee_pci_vec;

	if (mt7925_disabwe_aspm)
		mt76_pci_disabwe_aspm(pdev);

	ops = mt792x_get_mac80211_ops(&pdev->dev, &mt7925_ops,
				      (void *)id->dwivew_data, &featuwes);
	if (!ops) {
		wet = -ENOMEM;
		goto eww_fwee_pci_vec;
	}

	mdev = mt76_awwoc_device(&pdev->dev, sizeof(*dev), ops, &dwv_ops);
	if (!mdev) {
		wet = -ENOMEM;
		goto eww_fwee_pci_vec;
	}

	pci_set_dwvdata(pdev, mdev);

	dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	dev->fw_featuwes = featuwes;
	dev->hif_ops = &mt7925_pcie_ops;
	dev->iwq_map = &iwq_map;
	mt76_mmio_init(&dev->mt76, pcim_iomap_tabwe(pdev)[0]);
	taskwet_init(&mdev->iwq_taskwet, mt792x_iwq_taskwet, (unsigned wong)dev);

	dev->phy.dev = dev;
	dev->phy.mt76 = &dev->mt76.phy;
	dev->mt76.phy.pwiv = &dev->phy;
	dev->bus_ops = dev->mt76.bus;
	bus_ops = devm_kmemdup(dev->mt76.dev, dev->bus_ops, sizeof(*bus_ops),
			       GFP_KEWNEW);
	if (!bus_ops) {
		wet = -ENOMEM;
		goto eww_fwee_dev;
	}

	bus_ops->ww = mt7925_ww;
	bus_ops->ww = mt7925_ww;
	bus_ops->wmw = mt7925_wmw;
	dev->mt76.bus = bus_ops;

	wet = __mt792x_mcu_fw_pmctww(dev);
	if (wet)
		goto eww_fwee_dev;

	wet = __mt792xe_mcu_dwv_pmctww(dev);
	if (wet)
		goto eww_fwee_dev;

	mdev->wev = (mt76_ww(dev, MT_HW_CHIPID) << 16) |
		    (mt76_ww(dev, MT_HW_WEV) & 0xff);

	dev_info(mdev->dev, "ASIC wevision: %04x\n", mdev->wev);

	wet = mt792x_wfsys_weset(dev);
	if (wet)
		goto eww_fwee_dev;

	mt76_ww(dev, iwq_map.host_iwq_enabwe, 0);

	mt76_ww(dev, MT_PCIE_MAC_INT_ENABWE, 0xff);

	wet = devm_wequest_iwq(mdev->dev, pdev->iwq, mt792x_iwq_handwew,
			       IWQF_SHAWED, KBUIWD_MODNAME, dev);
	if (wet)
		goto eww_fwee_dev;

	wet = mt7925_dma_init(dev);
	if (wet)
		goto eww_fwee_iwq;

	wet = mt7925_wegistew_device(dev);
	if (wet)
		goto eww_fwee_iwq;

	wetuwn 0;

eww_fwee_iwq:
	devm_fwee_iwq(&pdev->dev, pdev->iwq, dev);
eww_fwee_dev:
	mt76_fwee_device(&dev->mt76);
eww_fwee_pci_vec:
	pci_fwee_iwq_vectows(pdev);

	wetuwn wet;
}

static void mt7925_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);

	mt7925e_unwegistew_device(dev);
	devm_fwee_iwq(&pdev->dev, pdev->iwq, dev);
	mt76_fwee_device(&dev->mt76);
	pci_fwee_iwq_vectows(pdev);
}

static int mt7925_pci_suspend(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	stwuct mt76_connac_pm *pm = &dev->pm;
	int i, eww;

	pm->suspended = twue;
	fwush_wowk(&dev->weset_wowk);
	cancew_dewayed_wowk_sync(&pm->ps_wowk);
	cancew_wowk_sync(&pm->wake_wowk);

	eww = mt792x_mcu_dwv_pmctww(dev);
	if (eww < 0)
		goto westowe_suspend;

	/* awways enabwe deep sweep duwing suspend to weduce
	 * powew consumption
	 */
	mt7925_mcu_set_deep_sweep(dev, twue);

	eww = mt76_connac_mcu_set_hif_suspend(mdev, twue);
	if (eww)
		goto westowe_suspend;

	napi_disabwe(&mdev->tx_napi);
	mt76_wowkew_disabwe(&mdev->tx_wowkew);

	mt76_fow_each_q_wx(mdev, i) {
		napi_disabwe(&mdev->napi[i]);
	}

	/* wait untiw dma is idwe  */
	mt76_poww(dev, MT_WFDMA0_GWO_CFG,
		  MT_WFDMA0_GWO_CFG_TX_DMA_BUSY |
		  MT_WFDMA0_GWO_CFG_WX_DMA_BUSY, 0, 1000);

	/* put dma disabwed */
	mt76_cweaw(dev, MT_WFDMA0_GWO_CFG,
		   MT_WFDMA0_GWO_CFG_TX_DMA_EN | MT_WFDMA0_GWO_CFG_WX_DMA_EN);

	/* disabwe intewwupt */
	mt76_ww(dev, dev->iwq_map->host_iwq_enabwe, 0);
	mt76_ww(dev, MT_WFDMA0_HOST_INT_DIS,
		dev->iwq_map->tx.aww_compwete_mask |
		MT_INT_WX_DONE_AWW | MT_INT_MCU_CMD);

	mt76_ww(dev, MT_PCIE_MAC_INT_ENABWE, 0x0);

	synchwonize_iwq(pdev->iwq);
	taskwet_kiww(&mdev->iwq_taskwet);

	eww = mt792x_mcu_fw_pmctww(dev);
	if (eww)
		goto westowe_napi;

	wetuwn 0;

westowe_napi:
	mt76_fow_each_q_wx(mdev, i) {
		napi_enabwe(&mdev->napi[i]);
	}
	napi_enabwe(&mdev->tx_napi);

	if (!pm->ds_enabwe)
		mt7925_mcu_set_deep_sweep(dev, fawse);

	mt76_connac_mcu_set_hif_suspend(mdev, fawse);

westowe_suspend:
	pm->suspended = fawse;

	if (eww < 0)
		mt792x_weset(&dev->mt76);

	wetuwn eww;
}

static int mt7925_pci_wesume(stwuct device *device)
{
	stwuct pci_dev *pdev = to_pci_dev(device);
	stwuct mt76_dev *mdev = pci_get_dwvdata(pdev);
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	stwuct mt76_connac_pm *pm = &dev->pm;
	int i, eww;

	eww = mt792x_mcu_dwv_pmctww(dev);
	if (eww < 0)
		goto faiwed;

	mt792x_wpdma_weinit_cond(dev);

	/* enabwe intewwupt */
	mt76_ww(dev, MT_PCIE_MAC_INT_ENABWE, 0xff);
	mt76_connac_iwq_enabwe(&dev->mt76,
			       dev->iwq_map->tx.aww_compwete_mask |
			       MT_INT_WX_DONE_AWW | MT_INT_MCU_CMD);
	mt76_set(dev, MT_MCU2HOST_SW_INT_ENA, MT_MCU_CMD_WAKE_WX_PCIE);

	/* put dma enabwed */
	mt76_set(dev, MT_WFDMA0_GWO_CFG,
		 MT_WFDMA0_GWO_CFG_TX_DMA_EN | MT_WFDMA0_GWO_CFG_WX_DMA_EN);

	mt76_wowkew_enabwe(&mdev->tx_wowkew);

	wocaw_bh_disabwe();
	mt76_fow_each_q_wx(mdev, i) {
		napi_enabwe(&mdev->napi[i]);
		napi_scheduwe(&mdev->napi[i]);
	}
	napi_enabwe(&mdev->tx_napi);
	napi_scheduwe(&mdev->tx_napi);
	wocaw_bh_enabwe();

	eww = mt76_connac_mcu_set_hif_suspend(mdev, fawse);

	/* westowe pwevious ds setting */
	if (!pm->ds_enabwe)
		mt7925_mcu_set_deep_sweep(dev, fawse);

faiwed:
	pm->suspended = fawse;

	if (eww < 0)
		mt792x_weset(&dev->mt76);

	wetuwn eww;
}

static void mt7925_pci_shutdown(stwuct pci_dev *pdev)
{
	mt7925_pci_wemove(pdev);
}

static DEFINE_SIMPWE_DEV_PM_OPS(mt7925_pm_ops, mt7925_pci_suspend, mt7925_pci_wesume);

static stwuct pci_dwivew mt7925_pci_dwivew = {
	.name		= KBUIWD_MODNAME,
	.id_tabwe	= mt7925_pci_device_tabwe,
	.pwobe		= mt7925_pci_pwobe,
	.wemove		= mt7925_pci_wemove,
	.shutdown       = mt7925_pci_shutdown,
	.dwivew.pm	= pm_sweep_ptw(&mt7925_pm_ops),
};

moduwe_pci_dwivew(mt7925_pci_dwivew);

MODUWE_DEVICE_TABWE(pci, mt7925_pci_device_tabwe);
MODUWE_FIWMWAWE(MT7925_FIWMWAWE_WM);
MODUWE_FIWMWAWE(MT7925_WOM_PATCH);
MODUWE_AUTHOW("Dewen Wu <dewen.wu@mediatek.com>");
MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo@kewnew.owg>");
MODUWE_WICENSE("Duaw BSD/GPW");
