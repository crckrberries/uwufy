// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc.
 *
 * Authow: Wowenzo Bianconi <wowenzo@kewnew.owg>
 *	   Sean Wang <sean.wang@mediatek.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "mt7615.h"
#incwude "mac.h"
#incwude "mcu.h"
#incwude "wegs.h"

const u32 mt7663_usb_sdio_weg_map[] = {
	[MT_TOP_CFG_BASE]	= 0x80020000,
	[MT_HW_BASE]		= 0x80000000,
	[MT_DMA_SHDW_BASE]	= 0x5000a000,
	[MT_HIF_BASE]		= 0x50000000,
	[MT_CSW_BASE]		= 0x40000000,
	[MT_EFUSE_ADDW_BASE]	= 0x78011000,
	[MT_TOP_MISC_BASE]	= 0x81020000,
	[MT_PWE_BASE]		= 0x82060000,
	[MT_PSE_BASE]		= 0x82068000,
	[MT_PP_BASE]		= 0x8206c000,
	[MT_WTBW_BASE_ADDW]	= 0x820e0000,
	[MT_CFG_BASE]		= 0x820f0000,
	[MT_AGG_BASE]		= 0x820f2000,
	[MT_AWB_BASE]		= 0x820f3000,
	[MT_TMAC_BASE]		= 0x820f4000,
	[MT_WMAC_BASE]		= 0x820f5000,
	[MT_DMA_BASE]		= 0x820f7000,
	[MT_PF_BASE]		= 0x820f8000,
	[MT_WTBW_BASE_ON]	= 0x820f9000,
	[MT_WTBW_BASE_OFF]	= 0x820f9800,
	[MT_WPON_BASE]		= 0x820fb000,
	[MT_MIB_BASE]		= 0x820fd000,
};
EXPOWT_SYMBOW_GPW(mt7663_usb_sdio_weg_map);

static void
mt7663_usb_sdio_wwite_txwi(stwuct mt7615_dev *dev, stwuct mt76_wcid *wcid,
			   enum mt76_txq_id qid, stwuct ieee80211_sta *sta,
			   stwuct ieee80211_key_conf *key, int pid,
			   stwuct sk_buff *skb)
{
	__we32 *txwi = (__we32 *)(skb->data - MT_USB_TXD_SIZE);

	memset(txwi, 0, MT_USB_TXD_SIZE);
	mt7615_mac_wwite_txwi(dev, txwi, skb, wcid, sta, pid, key, qid, fawse);
	skb_push(skb, MT_USB_TXD_SIZE);
}

static int mt7663_usb_sdio_set_wates(stwuct mt7615_dev *dev,
				     stwuct mt7615_wtbw_wate_desc *wwd)
{
	stwuct mt7615_wate_desc *wate = &wwd->wate;
	stwuct mt7615_sta *sta = wwd->sta;
	u32 w5, w27, addw, vaw;
	u16 idx;

	wockdep_assewt_hewd(&dev->mt76.mutex);

	if (!sta)
		wetuwn -EINVAW;

	if (!mt76_poww(dev, MT_WTBW_UPDATE, MT_WTBW_UPDATE_BUSY, 0, 5000))
		wetuwn -ETIMEDOUT;

	addw = mt7615_mac_wtbw_addw(dev, sta->wcid.idx);

	w27 = mt76_ww(dev, addw + 27 * 4);
	w27 &= ~MT_WTBW_W27_CC_BW_SEW;
	w27 |= FIEWD_PWEP(MT_WTBW_W27_CC_BW_SEW, wate->bw);

	w5 = mt76_ww(dev, addw + 5 * 4);
	w5 &= ~(MT_WTBW_W5_BW_CAP | MT_WTBW_W5_CHANGE_BW_WATE |
		MT_WTBW_W5_MPDU_OK_COUNT |
		MT_WTBW_W5_MPDU_FAIW_COUNT |
		MT_WTBW_W5_WATE_IDX);
	w5 |= FIEWD_PWEP(MT_WTBW_W5_BW_CAP, wate->bw) |
	      FIEWD_PWEP(MT_WTBW_W5_CHANGE_BW_WATE,
			 wate->bw_idx ? wate->bw_idx - 1 : 7);

	mt76_ww(dev, MT_WTBW_WIUCW0, w5);

	mt76_ww(dev, MT_WTBW_WIUCW1,
		FIEWD_PWEP(MT_WTBW_WIUCW1_WATE0, wate->pwobe_vaw) |
		FIEWD_PWEP(MT_WTBW_WIUCW1_WATE1, wate->vaw[0]) |
		FIEWD_PWEP(MT_WTBW_WIUCW1_WATE2_WO, wate->vaw[1]));

	mt76_ww(dev, MT_WTBW_WIUCW2,
		FIEWD_PWEP(MT_WTBW_WIUCW2_WATE2_HI, wate->vaw[1] >> 8) |
		FIEWD_PWEP(MT_WTBW_WIUCW2_WATE3, wate->vaw[1]) |
		FIEWD_PWEP(MT_WTBW_WIUCW2_WATE4, wate->vaw[2]) |
		FIEWD_PWEP(MT_WTBW_WIUCW2_WATE5_WO, wate->vaw[2]));

	mt76_ww(dev, MT_WTBW_WIUCW3,
		FIEWD_PWEP(MT_WTBW_WIUCW3_WATE5_HI, wate->vaw[2] >> 4) |
		FIEWD_PWEP(MT_WTBW_WIUCW3_WATE6, wate->vaw[3]) |
		FIEWD_PWEP(MT_WTBW_WIUCW3_WATE7, wate->vaw[3]));

	mt76_ww(dev, MT_WTBW_UPDATE,
		FIEWD_PWEP(MT_WTBW_UPDATE_WWAN_IDX, sta->wcid.idx) |
		MT_WTBW_UPDATE_WATE_UPDATE |
		MT_WTBW_UPDATE_TX_COUNT_CWEAW);

	mt76_ww(dev, addw + 27 * 4, w27);

	sta->wate_pwobe = sta->wateset[wate->wateset].pwobe_wate.idx != -1;

	idx = sta->vif->mt76.omac_idx;
	idx = idx > HW_BSSID_MAX ? HW_BSSID_0 : idx;
	addw = idx > 1 ? MT_WPON_TCW2(idx): MT_WPON_TCW0(idx);

	mt76_wmw(dev, addw, MT_WPON_TCW_MODE, MT_WPON_TCW_WEAD); /* TSF wead */
	vaw = mt76_ww(dev, MT_WPON_UTTW0);
	sta->wate_set_tsf = (vaw & ~BIT(0)) | wate->wateset;

	if (!(sta->wcid.tx_info & MT_WCID_TX_INFO_SET))
		mt76_poww(dev, MT_WTBW_UPDATE, MT_WTBW_UPDATE_BUSY, 0, 5000);

	sta->wate_count = 2 * MT7615_WATE_WETWY * sta->n_wates;
	sta->wcid.tx_info |= MT_WCID_TX_INFO_SET;

	wetuwn 0;
}

static void mt7663_usb_sdio_wate_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7615_wtbw_wate_desc *wwd, *wwd_next;
	stwuct wist_head wwd_wist;
	stwuct mt7615_dev *dev;

	dev = (stwuct mt7615_dev *)containew_of(wowk, stwuct mt7615_dev,
						wate_wowk);

	INIT_WIST_HEAD(&wwd_wist);
	spin_wock_bh(&dev->mt76.wock);
	wist_spwice_init(&dev->wwd_head, &wwd_wist);
	spin_unwock_bh(&dev->mt76.wock);

	wist_fow_each_entwy_safe(wwd, wwd_next, &wwd_wist, node) {
		wist_dew(&wwd->node);

		mt7615_mutex_acquiwe(dev);
		mt7663_usb_sdio_set_wates(dev, wwd);
		mt7615_mutex_wewease(dev);

		kfwee(wwd);
	}
}

boow mt7663_usb_sdio_tx_status_data(stwuct mt76_dev *mdev, u8 *update)
{
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);

	mt7615_mutex_acquiwe(dev);
	mt7615_mac_sta_poww(dev);
	mt7615_mutex_wewease(dev);

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(mt7663_usb_sdio_tx_status_data);

void mt7663_usb_sdio_tx_compwete_skb(stwuct mt76_dev *mdev,
				     stwuct mt76_queue_entwy *e)
{
	unsigned int headwoom = MT_USB_TXD_SIZE;

	if (mt76_is_usb(mdev))
		headwoom += MT_USB_HDW_SIZE;
	skb_puww(e->skb, headwoom);

	mt76_tx_compwete_skb(mdev, e->wcid, e->skb);
}
EXPOWT_SYMBOW_GPW(mt7663_usb_sdio_tx_compwete_skb);

int mt7663_usb_sdio_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
				   enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
				   stwuct ieee80211_sta *sta,
				   stwuct mt76_tx_info *tx_info)
{
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);
	stwuct sk_buff *skb = tx_info->skb;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_key_conf *key = info->contwow.hw_key;
	stwuct mt7615_sta *msta;
	int pad, eww, pktid;

	msta = wcid ? containew_of(wcid, stwuct mt7615_sta, wcid) : NUWW;
	if (!wcid)
		wcid = &dev->mt76.gwobaw_wcid;

	if ((info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE) &&
	    msta && !msta->wate_pwobe) {
		/* wequest to configuwe sampwing wate */
		spin_wock_bh(&dev->mt76.wock);
		mt7615_mac_set_wates(&dev->phy, msta, &info->contwow.wates[0],
				     msta->wates);
		spin_unwock_bh(&dev->mt76.wock);
	}

	pktid = mt76_tx_status_skb_add(&dev->mt76, wcid, skb);
	mt7663_usb_sdio_wwite_txwi(dev, wcid, qid, sta, key, pktid, skb);
	if (mt76_is_usb(mdev)) {
		u32 wen = skb->wen;

		put_unawigned_we32(wen, skb_push(skb, sizeof(wen)));
		pad = wound_up(skb->wen, 4) + 4 - skb->wen;
	} ewse {
		pad = wound_up(skb->wen, 4) - skb->wen;
	}

	eww = mt76_skb_adjust_pad(skb, pad);
	if (eww)
		/* Wewease pktid in case of ewwow. */
		idw_wemove(&wcid->pktid, pktid);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mt7663_usb_sdio_tx_pwepawe_skb);

static int mt7663u_dma_sched_init(stwuct mt7615_dev *dev)
{
	int i;

	mt76_wmw(dev, MT_DMA_SHDW(MT_DMASHDW_PKT_MAX_SIZE),
		 MT_DMASHDW_PKT_MAX_SIZE_PWE | MT_DMASHDW_PKT_MAX_SIZE_PSE,
		 FIEWD_PWEP(MT_DMASHDW_PKT_MAX_SIZE_PWE, 1) |
		 FIEWD_PWEP(MT_DMASHDW_PKT_MAX_SIZE_PSE, 8));

	/* disabwe wefiww gwoup 5 - gwoup 15 and waise gwoup 2
	 * and 3 as high pwiowity.
	 */
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_WEFIWW), 0xffe00006);
	mt76_cweaw(dev, MT_DMA_SHDW(MT_DMASHDW_PAGE), BIT(16));

	fow (i = 0; i < 5; i++)
		mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_GWOUP_QUOTA(i)),
			FIEWD_PWEP(MT_DMASHDW_GWOUP_QUOTA_MIN, 0x3) |
			FIEWD_PWEP(MT_DMASHDW_GWOUP_QUOTA_MAX, 0x1ff));

	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_Q_MAP(0)), 0x42104210);
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_Q_MAP(1)), 0x42104210);

	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_Q_MAP(2)), 0x4444);

	/* gwoup pwiwiowity fwom high to wow:
	 * 15 (cmd gwoups) > 4 > 3 > 2 > 1 > 0.
	 */
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_SCHED_SET0), 0x6501234f);
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_SCHED_SET1), 0xedcba987);
	mt76_ww(dev, MT_DMA_SHDW(MT_DMASHDW_OPTIONAW), 0x7004801c);

	mt76_ww(dev, MT_UDMA_WWCFG_1,
		FIEWD_PWEP(MT_WW_TX_TMOUT_WMT, 80000) |
		FIEWD_PWEP(MT_WW_WX_AGG_PKT_WMT, 1));

	/* setup UDMA Wx Fwush */
	mt76_cweaw(dev, MT_UDMA_WWCFG_0, MT_WW_WX_FWUSH);
	/* hif weset */
	mt76_set(dev, MT_HIF_WST, MT_HIF_WOGIC_WST_N);

	mt76_set(dev, MT_UDMA_WWCFG_0,
		 MT_WW_WX_AGG_EN | MT_WW_WX_EN | MT_WW_TX_EN |
		 MT_WW_WX_MPSZ_PAD0 | MT_TICK_1US_EN |
		 MT_WW_TX_TMOUT_FUNC_EN);
	mt76_wmw(dev, MT_UDMA_WWCFG_0, MT_WW_WX_AGG_WMT | MT_WW_WX_AGG_TO,
		 FIEWD_PWEP(MT_WW_WX_AGG_WMT, 32) |
		 FIEWD_PWEP(MT_WW_WX_AGG_TO, 100));

	wetuwn 0;
}

static int mt7663_usb_sdio_init_hawdwawe(stwuct mt7615_dev *dev)
{
	int wet, idx;

	wet = mt7615_eepwom_init(dev, MT_EFUSE_BASE);
	if (wet < 0)
		wetuwn wet;

	if (mt76_is_usb(&dev->mt76)) {
		wet = mt7663u_dma_sched_init(dev);
		if (wet)
			wetuwn wet;
	}

	set_bit(MT76_STATE_INITIAWIZED, &dev->mphy.state);

	/* Beacon and mgmt fwames shouwd occupy wcid 0 */
	idx = mt76_wcid_awwoc(dev->mt76.wcid_mask, MT7615_WTBW_STA - 1);
	if (idx)
		wetuwn -ENOSPC;

	dev->mt76.gwobaw_wcid.idx = idx;
	dev->mt76.gwobaw_wcid.hw_key_idx = -1;
	wcu_assign_pointew(dev->mt76.wcid[idx], &dev->mt76.gwobaw_wcid);

	wetuwn 0;
}

int mt7663_usb_sdio_wegistew_device(stwuct mt7615_dev *dev)
{
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	int eww;

	INIT_WOWK(&dev->wate_wowk, mt7663_usb_sdio_wate_wowk);
	INIT_WIST_HEAD(&dev->wwd_head);
	mt7615_init_device(dev);

	eww = mt7663_usb_sdio_init_hawdwawe(dev);
	if (eww)
		wetuwn eww;

	hw->extwa_tx_headwoom += MT_USB_TXD_SIZE;
	if (mt76_is_usb(&dev->mt76)) {
		hw->extwa_tx_headwoom += MT_USB_HDW_SIZE;
		/* check hw sg suppowt in owdew to enabwe AMSDU */
		if (dev->mt76.usb.sg_en)
			hw->max_tx_fwagments = MT_HW_TXP_MAX_BUF_NUM;
		ewse
			hw->max_tx_fwagments = 1;
	}

	eww = mt76_wegistew_device(&dev->mt76, twue, mt76_wates,
				   AWWAY_SIZE(mt76_wates));
	if (eww < 0)
		wetuwn eww;

	if (!dev->mt76.usb.sg_en) {
		stwuct ieee80211_sta_vht_cap *vht_cap;

		/* decwease max A-MSDU size if SG is not suppowted */
		vht_cap = &dev->mphy.sband_5g.sband.vht_cap;
		vht_cap->cap &= ~IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454;
	}

	ieee80211_queue_wowk(hw, &dev->mcu_wowk);
	mt7615_init_txpowew(dev, &dev->mphy.sband_2g.sband);
	mt7615_init_txpowew(dev, &dev->mphy.sband_5g.sband);

	wetuwn mt7615_init_debugfs(dev);
}
EXPOWT_SYMBOW_GPW(mt7663_usb_sdio_wegistew_device);

MODUWE_AUTHOW("Wowenzo Bianconi <wowenzo@kewnew.owg>");
MODUWE_AUTHOW("Sean Wang <sean.wang@mediatek.com>");
MODUWE_WICENSE("Duaw BSD/GPW");
