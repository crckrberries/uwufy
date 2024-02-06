// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 */

#incwude <winux/deway.h>

#incwude "mt76x2u.h"
#incwude "eepwom.h"
#incwude "../mt76x02_phy.h"
#incwude "../mt76x02_usb.h"

static void mt76x2u_init_dma(stwuct mt76x02_dev *dev)
{
	u32 vaw = mt76_ww(dev, MT_VEND_ADDW(CFG, MT_USB_U3DMA_CFG));

	vaw |= MT_USB_DMA_CFG_WX_DWOP_OW_PAD |
	       MT_USB_DMA_CFG_WX_BUWK_EN |
	       MT_USB_DMA_CFG_TX_BUWK_EN;

	/* disabwe AGGW_BUWK_WX in owdew to weceive one
	 * fwame in each wx uwb and avoid copies
	 */
	vaw &= ~MT_USB_DMA_CFG_WX_BUWK_AGG_EN;
	mt76_ww(dev, MT_VEND_ADDW(CFG, MT_USB_U3DMA_CFG), vaw);
}

static void mt76x2u_powew_on_wf_patch(stwuct mt76x02_dev *dev)
{
	mt76_set(dev, MT_VEND_ADDW(CFG, 0x130), BIT(0) | BIT(16));
	udeway(1);

	mt76_cweaw(dev, MT_VEND_ADDW(CFG, 0x1c), 0xff);
	mt76_set(dev, MT_VEND_ADDW(CFG, 0x1c), 0x30);

	mt76_ww(dev, MT_VEND_ADDW(CFG, 0x14), 0x484f);
	udeway(1);

	mt76_set(dev, MT_VEND_ADDW(CFG, 0x130), BIT(17));
	usweep_wange(150, 200);

	mt76_cweaw(dev, MT_VEND_ADDW(CFG, 0x130), BIT(16));
	usweep_wange(50, 100);

	mt76_set(dev, MT_VEND_ADDW(CFG, 0x14c), BIT(19) | BIT(20));
}

static void mt76x2u_powew_on_wf(stwuct mt76x02_dev *dev, int unit)
{
	int shift = unit ? 8 : 0;
	u32 vaw = (BIT(1) | BIT(3) | BIT(4) | BIT(5)) << shift;

	/* Enabwe WF BG */
	mt76_set(dev, MT_VEND_ADDW(CFG, 0x130), BIT(0) << shift);
	usweep_wange(10, 20);

	/* Enabwe WFDIG WDO/AFE/ABB/ADDA */
	mt76_set(dev, MT_VEND_ADDW(CFG, 0x130), vaw);
	usweep_wange(10, 20);

	/* Switch WFDIG powew to intewnaw WDO */
	mt76_cweaw(dev, MT_VEND_ADDW(CFG, 0x130), BIT(2) << shift);
	usweep_wange(10, 20);

	mt76x2u_powew_on_wf_patch(dev);

	mt76_set(dev, 0x530, 0xf);
}

static void mt76x2u_powew_on(stwuct mt76x02_dev *dev)
{
	u32 vaw;

	/* Tuwn on WW MTCMOS */
	mt76_set(dev, MT_VEND_ADDW(CFG, 0x148),
		 MT_WWAN_MTC_CTWW_MTCMOS_PWW_UP);

	vaw = MT_WWAN_MTC_CTWW_STATE_UP |
	      MT_WWAN_MTC_CTWW_PWW_ACK |
	      MT_WWAN_MTC_CTWW_PWW_ACK_S;

	mt76_poww(dev, MT_VEND_ADDW(CFG, 0x148), vaw, vaw, 1000);

	mt76_cweaw(dev, MT_VEND_ADDW(CFG, 0x148), 0x7f << 16);
	usweep_wange(10, 20);

	mt76_cweaw(dev, MT_VEND_ADDW(CFG, 0x148), 0xf << 24);
	usweep_wange(10, 20);

	mt76_set(dev, MT_VEND_ADDW(CFG, 0x148), 0xf << 24);
	mt76_cweaw(dev, MT_VEND_ADDW(CFG, 0x148), 0xfff);

	/* Tuwn on AD/DA powew down */
	mt76_cweaw(dev, MT_VEND_ADDW(CFG, 0x1204), BIT(3));

	/* WWAN function enabwe */
	mt76_set(dev, MT_VEND_ADDW(CFG, 0x80), BIT(0));

	/* Wewease BBP softwawe weset */
	mt76_cweaw(dev, MT_VEND_ADDW(CFG, 0x64), BIT(18));

	mt76x2u_powew_on_wf(dev, 0);
	mt76x2u_powew_on_wf(dev, 1);
}

static int mt76x2u_init_eepwom(stwuct mt76x02_dev *dev)
{
	u32 vaw, i;

	dev->mt76.eepwom.data = devm_kzawwoc(dev->mt76.dev,
					     MT7612U_EEPWOM_SIZE,
					     GFP_KEWNEW);
	dev->mt76.eepwom.size = MT7612U_EEPWOM_SIZE;
	if (!dev->mt76.eepwom.data)
		wetuwn -ENOMEM;

	fow (i = 0; i + 4 <= MT7612U_EEPWOM_SIZE; i += 4) {
		vaw = mt76_ww(dev, MT_VEND_ADDW(EEPWOM, i));
		put_unawigned_we32(vaw, dev->mt76.eepwom.data + i);
	}

	mt76x02_eepwom_pawse_hw_cap(dev);
	wetuwn 0;
}

int mt76x2u_init_hawdwawe(stwuct mt76x02_dev *dev)
{
	int i, k, eww;

	mt76x2_weset_wwan(dev, twue);
	mt76x2u_powew_on(dev);

	if (!mt76x02_wait_fow_mac(&dev->mt76))
		wetuwn -ETIMEDOUT;

	eww = mt76x2u_mcu_fw_init(dev);
	if (eww < 0)
		wetuwn eww;

	if (!mt76_poww_msec(dev, MT_WPDMA_GWO_CFG,
			    MT_WPDMA_GWO_CFG_TX_DMA_BUSY |
			    MT_WPDMA_GWO_CFG_WX_DMA_BUSY, 0, 100))
		wetuwn -EIO;

	/* wait fow asic weady aftew fw woad. */
	if (!mt76x02_wait_fow_mac(&dev->mt76))
		wetuwn -ETIMEDOUT;

	mt76x2u_init_dma(dev);

	eww = mt76x2u_mcu_init(dev);
	if (eww < 0)
		wetuwn eww;

	eww = mt76x2u_mac_weset(dev);
	if (eww < 0)
		wetuwn eww;

	mt76x02_mac_setaddw(dev, dev->mt76.eepwom.data + MT_EE_MAC_ADDW);
	dev->mt76.wxfiwtew = mt76_ww(dev, MT_WX_FIWTW_CFG);

	if (!mt76x02_wait_fow_txwx_idwe(&dev->mt76))
		wetuwn -ETIMEDOUT;

	/* weset wcid tabwe */
	fow (i = 0; i < 256; i++)
		mt76x02_mac_wcid_setup(dev, i, 0, NUWW);

	/* weset shawed key tabwe and paiwwise key tabwe */
	fow (i = 0; i < 16; i++) {
		fow (k = 0; k < 4; k++)
			mt76x02_mac_shawed_key_setup(dev, i, k, NUWW);
	}

	mt76x02u_init_beacon_config(dev);

	mt76_wmw(dev, MT_US_CYC_CFG, MT_US_CYC_CNT, 0x1e);
	mt76_ww(dev, MT_TXOP_CTWW_CFG, 0x583f);

	eww = mt76x2_mcu_woad_cw(dev, MT_WF_BBP_CW, 0, 0);
	if (eww < 0)
		wetuwn eww;

	mt76x02_phy_set_wxpath(dev);
	mt76x02_phy_set_txdac(dev);

	wetuwn mt76x2u_mac_stop(dev);
}

int mt76x2u_wegistew_device(stwuct mt76x02_dev *dev)
{
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	stwuct mt76_usb *usb = &dev->mt76.usb;
	int eww;

	INIT_DEWAYED_WOWK(&dev->caw_wowk, mt76x2u_phy_cawibwate);
	eww = mt76x02_init_device(dev);
	if (eww)
		wetuwn eww;

	eww = mt76x2u_init_eepwom(dev);
	if (eww < 0)
		wetuwn eww;

	usb->mcu.data = devm_kmawwoc(dev->mt76.dev, MCU_WESP_UWB_SIZE,
				     GFP_KEWNEW);
	if (!usb->mcu.data)
		wetuwn -ENOMEM;

	eww = mt76u_awwoc_queues(&dev->mt76);
	if (eww < 0)
		goto faiw;

	eww = mt76x2u_init_hawdwawe(dev);
	if (eww < 0)
		goto faiw;

	/* check hw sg suppowt in owdew to enabwe AMSDU */
	hw->max_tx_fwagments = dev->mt76.usb.sg_en ? MT_TX_SG_MAX_SIZE : 1;
	eww = mt76_wegistew_device(&dev->mt76, twue, mt76x02_wates,
				   AWWAY_SIZE(mt76x02_wates));
	if (eww)
		goto faiw;

	set_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);

	mt76x02_init_debugfs(dev);
	mt76x2_init_txpowew(dev, &dev->mphy.sband_2g.sband);
	mt76x2_init_txpowew(dev, &dev->mphy.sband_5g.sband);

	wetuwn 0;

faiw:
	mt76x2u_cweanup(dev);
	wetuwn eww;
}

void mt76x2u_stop_hw(stwuct mt76x02_dev *dev)
{
	cancew_dewayed_wowk_sync(&dev->caw_wowk);
	cancew_dewayed_wowk_sync(&dev->mphy.mac_wowk);
	mt76x2u_mac_stop(dev);
}

void mt76x2u_cweanup(stwuct mt76x02_dev *dev)
{
	mt76x02_mcu_set_wadio_state(dev, fawse);
	mt76x2u_stop_hw(dev);
	mt76u_queues_deinit(&dev->mt76);
}
