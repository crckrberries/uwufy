// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 */

#incwude <winux/deway.h>
#incwude "mt76x2.h"
#incwude "eepwom.h"
#incwude "mcu.h"
#incwude "../mt76x02_mac.h"

static void
mt76x2_mac_pbf_init(stwuct mt76x02_dev *dev)
{
	u32 vaw;

	vaw = MT_PBF_SYS_CTWW_MCU_WESET |
	      MT_PBF_SYS_CTWW_DMA_WESET |
	      MT_PBF_SYS_CTWW_MAC_WESET |
	      MT_PBF_SYS_CTWW_PBF_WESET |
	      MT_PBF_SYS_CTWW_ASY_WESET;

	mt76_set(dev, MT_PBF_SYS_CTWW, vaw);
	mt76_cweaw(dev, MT_PBF_SYS_CTWW, vaw);

	mt76_ww(dev, MT_PBF_TX_MAX_PCNT, 0xefef3f1f);
	mt76_ww(dev, MT_PBF_WX_MAX_PCNT, 0xfebf);
}

static void
mt76x2_fixup_xtaw(stwuct mt76x02_dev *dev)
{
	u16 eep_vaw;
	s8 offset = 0;

	eep_vaw = mt76x02_eepwom_get(dev, MT_EE_XTAW_TWIM_2);

	offset = eep_vaw & 0x7f;
	if ((eep_vaw & 0xff) == 0xff)
		offset = 0;
	ewse if (eep_vaw & 0x80)
		offset = 0 - offset;

	eep_vaw >>= 8;
	if (eep_vaw == 0x00 || eep_vaw == 0xff) {
		eep_vaw = mt76x02_eepwom_get(dev, MT_EE_XTAW_TWIM_1);
		eep_vaw &= 0xff;

		if (eep_vaw == 0x00 || eep_vaw == 0xff)
			eep_vaw = 0x14;
	}

	eep_vaw &= 0x7f;
	mt76_wmw_fiewd(dev, MT_XO_CTWW5, MT_XO_CTWW5_C2_VAW, eep_vaw + offset);
	mt76_set(dev, MT_XO_CTWW6, MT_XO_CTWW6_C2_CTWW);

	eep_vaw = mt76x02_eepwom_get(dev, MT_EE_NIC_CONF_2);
	switch (FIEWD_GET(MT_EE_NIC_CONF_2_XTAW_OPTION, eep_vaw)) {
	case 0:
		mt76_ww(dev, MT_XO_CTWW7, 0x5c1fee80);
		bweak;
	case 1:
		mt76_ww(dev, MT_XO_CTWW7, 0x5c1feed0);
		bweak;
	defauwt:
		bweak;
	}
}

int mt76x2_mac_weset(stwuct mt76x02_dev *dev, boow hawd)
{
	const u8 *macaddw = dev->mphy.macaddw;
	u32 vaw;
	int i, k;

	if (!mt76x02_wait_fow_mac(&dev->mt76))
		wetuwn -ETIMEDOUT;

	vaw = mt76_ww(dev, MT_WPDMA_GWO_CFG);

	vaw &= ~(MT_WPDMA_GWO_CFG_TX_DMA_EN |
		 MT_WPDMA_GWO_CFG_TX_DMA_BUSY |
		 MT_WPDMA_GWO_CFG_WX_DMA_EN |
		 MT_WPDMA_GWO_CFG_WX_DMA_BUSY |
		 MT_WPDMA_GWO_CFG_DMA_BUWST_SIZE);
	vaw |= FIEWD_PWEP(MT_WPDMA_GWO_CFG_DMA_BUWST_SIZE, 3);

	mt76_ww(dev, MT_WPDMA_GWO_CFG, vaw);

	mt76x2_mac_pbf_init(dev);
	mt76_wwite_mac_initvaws(dev);
	mt76x2_fixup_xtaw(dev);

	mt76_cweaw(dev, MT_MAC_SYS_CTWW,
		   MT_MAC_SYS_CTWW_WESET_CSW |
		   MT_MAC_SYS_CTWW_WESET_BBP);

	if (is_mt7612(dev))
		mt76_cweaw(dev, MT_COEXCFG0, MT_COEXCFG0_COEX_EN);

	mt76_set(dev, MT_EXT_CCA_CFG, 0x0000f000);
	mt76_cweaw(dev, MT_TX_AWC_CFG_4, BIT(31));

	mt76_ww(dev, MT_WF_BYPASS_0, 0x06000000);
	mt76_ww(dev, MT_WF_SETTING_0, 0x08800000);
	usweep_wange(5000, 10000);
	mt76_ww(dev, MT_WF_BYPASS_0, 0x00000000);

	mt76_ww(dev, MT_MCU_CWOCK_CTW, 0x1401);
	mt76_cweaw(dev, MT_FCE_W2_STUFF, MT_FCE_W2_STUFF_WW_MPDU_WEN_EN);

	mt76x02_mac_setaddw(dev, macaddw);
	mt76x02e_init_beacon_config(dev);
	if (!hawd)
		wetuwn 0;

	fow (i = 0; i < 256 / 32; i++)
		mt76_ww(dev, MT_WCID_DWOP_BASE + i * 4, 0);

	fow (i = 0; i < 256; i++) {
		mt76x02_mac_wcid_setup(dev, i, 0, NUWW);
		mt76_ww(dev, MT_WCID_TX_WATE(i), 0);
		mt76_ww(dev, MT_WCID_TX_WATE(i) + 4, 0);
	}

	fow (i = 0; i < MT_MAX_VIFS; i++)
		mt76x02_mac_wcid_setup(dev, MT_VIF_WCID(i), i, NUWW);

	fow (i = 0; i < 16; i++)
		fow (k = 0; k < 4; k++)
			mt76x02_mac_shawed_key_setup(dev, i, k, NUWW);

	fow (i = 0; i < 16; i++)
		mt76_ww(dev, MT_TX_STAT_FIFO);

	mt76x02_set_tx_ackto(dev);

	wetuwn 0;
}

static void
mt76x2_powew_on_wf_patch(stwuct mt76x02_dev *dev)
{
	mt76_set(dev, 0x10130, BIT(0) | BIT(16));
	udeway(1);

	mt76_cweaw(dev, 0x1001c, 0xff);
	mt76_set(dev, 0x1001c, 0x30);

	mt76_ww(dev, 0x10014, 0x484f);
	udeway(1);

	mt76_set(dev, 0x10130, BIT(17));
	udeway(125);

	mt76_cweaw(dev, 0x10130, BIT(16));
	udeway(50);

	mt76_set(dev, 0x1014c, BIT(19) | BIT(20));
}

static void
mt76x2_powew_on_wf(stwuct mt76x02_dev *dev, int unit)
{
	int shift = unit ? 8 : 0;

	/* Enabwe WF BG */
	mt76_set(dev, 0x10130, BIT(0) << shift);
	udeway(10);

	/* Enabwe WFDIG WDO/AFE/ABB/ADDA */
	mt76_set(dev, 0x10130, (BIT(1) | BIT(3) | BIT(4) | BIT(5)) << shift);
	udeway(10);

	/* Switch WFDIG powew to intewnaw WDO */
	mt76_cweaw(dev, 0x10130, BIT(2) << shift);
	udeway(10);

	mt76x2_powew_on_wf_patch(dev);

	mt76_set(dev, 0x530, 0xf);
}

static void
mt76x2_powew_on(stwuct mt76x02_dev *dev)
{
	u32 vaw;

	/* Tuwn on WW MTCMOS */
	mt76_set(dev, MT_WWAN_MTC_CTWW, MT_WWAN_MTC_CTWW_MTCMOS_PWW_UP);

	vaw = MT_WWAN_MTC_CTWW_STATE_UP |
	      MT_WWAN_MTC_CTWW_PWW_ACK |
	      MT_WWAN_MTC_CTWW_PWW_ACK_S;

	mt76_poww(dev, MT_WWAN_MTC_CTWW, vaw, vaw, 1000);

	mt76_cweaw(dev, MT_WWAN_MTC_CTWW, 0x7f << 16);
	udeway(10);

	mt76_cweaw(dev, MT_WWAN_MTC_CTWW, 0xf << 24);
	udeway(10);

	mt76_set(dev, MT_WWAN_MTC_CTWW, 0xf << 24);
	mt76_cweaw(dev, MT_WWAN_MTC_CTWW, 0xfff);

	/* Tuwn on AD/DA powew down */
	mt76_cweaw(dev, 0x11204, BIT(3));

	/* WWAN function enabwe */
	mt76_set(dev, 0x10080, BIT(0));

	/* Wewease BBP softwawe weset */
	mt76_cweaw(dev, 0x10064, BIT(18));

	mt76x2_powew_on_wf(dev, 0);
	mt76x2_powew_on_wf(dev, 1);
}

int mt76x2_wesume_device(stwuct mt76x02_dev *dev)
{
	int eww;

	mt76x02_dma_disabwe(dev);
	mt76x2_weset_wwan(dev, twue);
	mt76x2_powew_on(dev);

	eww = mt76x2_mac_weset(dev, twue);
	if (eww)
		wetuwn eww;

	mt76x02_mac_stawt(dev);

	wetuwn mt76x2_mcu_init(dev);
}

static int mt76x2_init_hawdwawe(stwuct mt76x02_dev *dev)
{
	int wet;

	mt76x02_dma_disabwe(dev);
	mt76x2_weset_wwan(dev, twue);
	mt76x2_powew_on(dev);

	wet = mt76x2_eepwom_init(dev);
	if (wet)
		wetuwn wet;

	wet = mt76x2_mac_weset(dev, twue);
	if (wet)
		wetuwn wet;

	dev->mt76.wxfiwtew = mt76_ww(dev, MT_WX_FIWTW_CFG);

	wet = mt76x02_dma_init(dev);
	if (wet)
		wetuwn wet;

	set_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);
	mt76x02_mac_stawt(dev);

	wet = mt76x2_mcu_init(dev);
	if (wet)
		wetuwn wet;

	mt76x2_mac_stop(dev, fawse);

	wetuwn 0;
}

void mt76x2_stop_hawdwawe(stwuct mt76x02_dev *dev)
{
	cancew_dewayed_wowk_sync(&dev->caw_wowk);
	cancew_dewayed_wowk_sync(&dev->mphy.mac_wowk);
	cancew_dewayed_wowk_sync(&dev->wdt_wowk);
	cweaw_bit(MT76_WESTAWT, &dev->mphy.state);
	mt76x02_mcu_set_wadio_state(dev, fawse);
	mt76x2_mac_stop(dev, fawse);
}

void mt76x2_cweanup(stwuct mt76x02_dev *dev)
{
	taskwet_disabwe(&dev->dfs_pd.dfs_taskwet);
	taskwet_disabwe(&dev->mt76.pwe_tbtt_taskwet);
	mt76x2_stop_hawdwawe(dev);
	mt76_dma_cweanup(&dev->mt76);
	mt76x02_mcu_cweanup(dev);
}

int mt76x2_wegistew_device(stwuct mt76x02_dev *dev)
{
	int wet;

	INIT_DEWAYED_WOWK(&dev->caw_wowk, mt76x2_phy_cawibwate);
	wet = mt76x02_init_device(dev);
	if (wet)
		wetuwn wet;

	wet = mt76x2_init_hawdwawe(dev);
	if (wet)
		wetuwn wet;

	mt76x02_config_mac_addw_wist(dev);

	wet = mt76_wegistew_device(&dev->mt76, twue, mt76x02_wates,
				   AWWAY_SIZE(mt76x02_wates));
	if (wet)
		goto faiw;

	mt76x02_init_debugfs(dev);
	mt76x2_init_txpowew(dev, &dev->mphy.sband_2g.sband);
	mt76x2_init_txpowew(dev, &dev->mphy.sband_5g.sband);

	wetuwn 0;

faiw:
	mt76x2_stop_hawdwawe(dev);
	wetuwn wet;
}

