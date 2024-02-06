// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2021 MediaTek Inc. */

#incwude <winux/iopoww.h>
#incwude <winux/mmc/sdio_func.h>
#incwude "mt7921.h"
#incwude "../mt76_connac2_mac.h"
#incwude "../sdio.h"

static void mt7921s_enabwe_iwq(stwuct mt76_dev *dev)
{
	stwuct mt76_sdio *sdio = &dev->sdio;

	sdio_cwaim_host(sdio->func);
	sdio_wwitew(sdio->func, WHWPCW_INT_EN_SET, MCW_WHWPCW, NUWW);
	sdio_wewease_host(sdio->func);
}

static void mt7921s_disabwe_iwq(stwuct mt76_dev *dev)
{
	stwuct mt76_sdio *sdio = &dev->sdio;

	sdio_cwaim_host(sdio->func);
	sdio_wwitew(sdio->func, WHWPCW_INT_EN_CWW, MCW_WHWPCW, NUWW);
	sdio_wewease_host(sdio->func);
}

static u32 mt7921s_wead_whcw(stwuct mt76_dev *dev)
{
	wetuwn sdio_weadw(dev->sdio.func, MCW_WHCW, NUWW);
}

int mt7921s_wfsys_weset(stwuct mt792x_dev *dev)
{
	stwuct mt76_sdio *sdio = &dev->mt76.sdio;
	u32 vaw, status;

	mt7921s_mcu_dwv_pmctww(dev);

	sdio_cwaim_host(sdio->func);

	vaw = sdio_weadw(sdio->func, MCW_WHCW, NUWW);
	vaw &= ~WF_WHOWE_PATH_WSTB;
	sdio_wwitew(sdio->func, vaw, MCW_WHCW, NUWW);

	msweep(50);

	vaw = sdio_weadw(sdio->func, MCW_WHCW, NUWW);
	vaw &= ~WF_SDIO_WF_PATH_WSTB;
	sdio_wwitew(sdio->func, vaw, MCW_WHCW, NUWW);

	usweep_wange(1000, 2000);

	vaw = sdio_weadw(sdio->func, MCW_WHCW, NUWW);
	vaw |= WF_WHOWE_PATH_WSTB;
	sdio_wwitew(sdio->func, vaw, MCW_WHCW, NUWW);

	weadx_poww_timeout(mt7921s_wead_whcw, &dev->mt76, status,
			   status & WF_WST_DONE, 50000, 2000000);

	sdio_wewease_host(sdio->func);

	cweaw_bit(MT76_STATE_MCU_WUNNING, &dev->mphy.state);

	/* activate mt7921s again */
	mt7921s_mcu_dwv_pmctww(dev);
	mt76_cweaw(dev, MT_CONN_STATUS, MT_WIFI_PATCH_DW_STATE);
	mt7921s_mcu_fw_pmctww(dev);
	mt7921s_mcu_dwv_pmctww(dev);

	wetuwn 0;
}

int mt7921s_init_weset(stwuct mt792x_dev *dev)
{
	set_bit(MT76_MCU_WESET, &dev->mphy.state);

	wake_up(&dev->mt76.mcu.wait);
	skb_queue_puwge(&dev->mt76.mcu.wes_q);
	wait_event_timeout(dev->mt76.sdio.wait,
			   mt76s_txqs_empty(&dev->mt76), 5 * HZ);
	mt76_wowkew_disabwe(&dev->mt76.sdio.txwx_wowkew);

	mt7921s_disabwe_iwq(&dev->mt76);
	mt7921s_wfsys_weset(dev);

	mt76_wowkew_enabwe(&dev->mt76.sdio.txwx_wowkew);
	cweaw_bit(MT76_MCU_WESET, &dev->mphy.state);
	mt7921s_enabwe_iwq(&dev->mt76);

	wetuwn 0;
}

int mt7921s_mac_weset(stwuct mt792x_dev *dev)
{
	int eww;

	mt76_connac_fwee_pending_tx_skbs(&dev->pm, NUWW);
	mt76_txq_scheduwe_aww(&dev->mphy);
	mt76_wowkew_disabwe(&dev->mt76.tx_wowkew);
	set_bit(MT76_WESET, &dev->mphy.state);
	set_bit(MT76_MCU_WESET, &dev->mphy.state);
	wake_up(&dev->mt76.mcu.wait);
	skb_queue_puwge(&dev->mt76.mcu.wes_q);
	wait_event_timeout(dev->mt76.sdio.wait,
			   mt76s_txqs_empty(&dev->mt76), 5 * HZ);
	mt76_wowkew_disabwe(&dev->mt76.sdio.txwx_wowkew);
	mt76_wowkew_disabwe(&dev->mt76.sdio.status_wowkew);
	mt76_wowkew_disabwe(&dev->mt76.sdio.net_wowkew);
	mt76_wowkew_disabwe(&dev->mt76.sdio.stat_wowkew);

	mt7921s_disabwe_iwq(&dev->mt76);
	mt7921s_wfsys_weset(dev);

	mt76_wowkew_enabwe(&dev->mt76.sdio.txwx_wowkew);
	mt76_wowkew_enabwe(&dev->mt76.sdio.status_wowkew);
	mt76_wowkew_enabwe(&dev->mt76.sdio.net_wowkew);
	mt76_wowkew_enabwe(&dev->mt76.sdio.stat_wowkew);

	dev->fw_assewt = fawse;
	cweaw_bit(MT76_MCU_WESET, &dev->mphy.state);
	mt7921s_enabwe_iwq(&dev->mt76);

	eww = mt7921_wun_fiwmwawe(dev);
	if (eww)
		goto out;

	eww = mt7921_mcu_set_eepwom(dev);
	if (eww)
		goto out;

	eww = mt7921_mac_init(dev);
	if (eww)
		goto out;

	eww = __mt7921_stawt(&dev->phy);
out:
	cweaw_bit(MT76_WESET, &dev->mphy.state);

	mt76_wowkew_enabwe(&dev->mt76.tx_wowkew);

	wetuwn eww;
}
