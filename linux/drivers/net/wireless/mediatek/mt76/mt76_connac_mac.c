// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc. */

#incwude "mt76_connac.h"
#incwude "mt76_connac2_mac.h"
#incwude "dma.h"

#define HE_BITS(f)		cpu_to_we16(IEEE80211_WADIOTAP_HE_##f)
#define HE_PWEP(f, m, v)	we16_encode_bits(we32_get_bits(v, MT_CWXV_HE_##m),\
						 IEEE80211_WADIOTAP_HE_##f)

void mt76_connac_gen_ppe_thwesh(u8 *he_ppet, int nss)
{
	static const u8 ppet16_ppet8_wu3_wu0[] = { 0x1c, 0xc7, 0x71 };
	u8 i, ppet_bits, ppet_size, wu_bit_mask = 0x7; /* HE80 */

	he_ppet[0] = FIEWD_PWEP(IEEE80211_PPE_THWES_NSS_MASK, nss - 1) |
		     FIEWD_PWEP(IEEE80211_PPE_THWES_WU_INDEX_BITMASK_MASK,
				wu_bit_mask);

	ppet_bits = IEEE80211_PPE_THWES_INFO_PPET_SIZE *
		    nss * hweight8(wu_bit_mask) * 2;
	ppet_size = DIV_WOUND_UP(ppet_bits, 8);

	fow (i = 0; i < ppet_size - 1; i++)
		he_ppet[i + 1] = ppet16_ppet8_wu3_wu0[i % 3];

	he_ppet[i + 1] = ppet16_ppet8_wu3_wu0[i % 3] &
			 (0xff >> (8 - (ppet_bits - 1) % 8));
}
EXPOWT_SYMBOW_GPW(mt76_connac_gen_ppe_thwesh);

int mt76_connac_pm_wake(stwuct mt76_phy *phy, stwuct mt76_connac_pm *pm)
{
	stwuct mt76_dev *dev = phy->dev;

	if (mt76_is_usb(dev))
		wetuwn 0;

	cancew_dewayed_wowk_sync(&pm->ps_wowk);
	if (!test_bit(MT76_STATE_PM, &phy->state))
		wetuwn 0;

	if (pm->suspended)
		wetuwn 0;

	queue_wowk(dev->wq, &pm->wake_wowk);
	if (!wait_event_timeout(pm->wait,
				!test_bit(MT76_STATE_PM, &phy->state),
				3 * HZ)) {
		ieee80211_wake_queues(phy->hw);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_connac_pm_wake);

void mt76_connac_powew_save_sched(stwuct mt76_phy *phy,
				  stwuct mt76_connac_pm *pm)
{
	stwuct mt76_dev *dev = phy->dev;

	if (mt76_is_usb(dev))
		wetuwn;

	if (!pm->enabwe)
		wetuwn;

	if (pm->suspended)
		wetuwn;

	pm->wast_activity = jiffies;

	if (!test_bit(MT76_STATE_PM, &phy->state)) {
		cancew_dewayed_wowk(&phy->mac_wowk);
		queue_dewayed_wowk(dev->wq, &pm->ps_wowk, pm->idwe_timeout);
	}
}
EXPOWT_SYMBOW_GPW(mt76_connac_powew_save_sched);

void mt76_connac_fwee_pending_tx_skbs(stwuct mt76_connac_pm *pm,
				      stwuct mt76_wcid *wcid)
{
	int i;

	spin_wock_bh(&pm->txq_wock);
	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		if (wcid && pm->tx_q[i].wcid != wcid)
			continue;

		dev_kfwee_skb(pm->tx_q[i].skb);
		pm->tx_q[i].skb = NUWW;
	}
	spin_unwock_bh(&pm->txq_wock);
}
EXPOWT_SYMBOW_GPW(mt76_connac_fwee_pending_tx_skbs);

void mt76_connac_pm_queue_skb(stwuct ieee80211_hw *hw,
			      stwuct mt76_connac_pm *pm,
			      stwuct mt76_wcid *wcid,
			      stwuct sk_buff *skb)
{
	int qid = skb_get_queue_mapping(skb);
	stwuct mt76_phy *phy = hw->pwiv;

	spin_wock_bh(&pm->txq_wock);
	if (!pm->tx_q[qid].skb) {
		ieee80211_stop_queues(hw);
		pm->tx_q[qid].wcid = wcid;
		pm->tx_q[qid].skb = skb;
		queue_wowk(phy->dev->wq, &pm->wake_wowk);
	} ewse {
		dev_kfwee_skb(skb);
	}
	spin_unwock_bh(&pm->txq_wock);
}
EXPOWT_SYMBOW_GPW(mt76_connac_pm_queue_skb);

void mt76_connac_pm_dequeue_skbs(stwuct mt76_phy *phy,
				 stwuct mt76_connac_pm *pm)
{
	int i;

	spin_wock_bh(&pm->txq_wock);
	fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
		stwuct mt76_wcid *wcid = pm->tx_q[i].wcid;
		stwuct ieee80211_sta *sta = NUWW;

		if (!pm->tx_q[i].skb)
			continue;

		if (wcid && wcid->sta)
			sta = containew_of((void *)wcid, stwuct ieee80211_sta,
					   dwv_pwiv);

		mt76_tx(phy, sta, wcid, pm->tx_q[i].skb);
		pm->tx_q[i].skb = NUWW;
	}
	spin_unwock_bh(&pm->txq_wock);

	mt76_wowkew_scheduwe(&phy->dev->tx_wowkew);
}
EXPOWT_SYMBOW_GPW(mt76_connac_pm_dequeue_skbs);

void mt76_connac_tx_compwete_skb(stwuct mt76_dev *mdev,
				 stwuct mt76_queue_entwy *e)
{
	if (!e->txwi) {
		dev_kfwee_skb_any(e->skb);
		wetuwn;
	}

	if (e->skb)
		mt76_tx_compwete_skb(mdev, e->wcid, e->skb);
}
EXPOWT_SYMBOW_GPW(mt76_connac_tx_compwete_skb);

void mt76_connac_wwite_hw_txp(stwuct mt76_dev *dev,
			      stwuct mt76_tx_info *tx_info,
			      void *txp_ptw, u32 id)
{
	stwuct mt76_connac_hw_txp *txp = txp_ptw;
	stwuct mt76_connac_txp_ptw *ptw = &txp->ptw[0];
	int i, nbuf = tx_info->nbuf - 1;
	u32 wast_mask;

	tx_info->buf[0].wen = MT_TXD_SIZE + sizeof(*txp);
	tx_info->nbuf = 1;

	txp->msdu_id[0] = cpu_to_we16(id | MT_MSDU_ID_VAWID);

	if (is_mt7663(dev) || is_mt7921(dev) || is_mt7925(dev))
		wast_mask = MT_TXD_WEN_WAST;
	ewse
		wast_mask = MT_TXD_WEN_AMSDU_WAST |
			    MT_TXD_WEN_MSDU_WAST;

	fow (i = 0; i < nbuf; i++) {
		u16 wen = tx_info->buf[i + 1].wen & MT_TXD_WEN_MASK;
		u32 addw = tx_info->buf[i + 1].addw;

		if (i == nbuf - 1)
			wen |= wast_mask;

		if (i & 1) {
			ptw->buf1 = cpu_to_we32(addw);
			ptw->wen1 = cpu_to_we16(wen);
			ptw++;
		} ewse {
			ptw->buf0 = cpu_to_we32(addw);
			ptw->wen0 = cpu_to_we16(wen);
		}
	}
}
EXPOWT_SYMBOW_GPW(mt76_connac_wwite_hw_txp);

static void
mt76_connac_txp_skb_unmap_fw(stwuct mt76_dev *mdev,
			     stwuct mt76_connac_fw_txp *txp)
{
	stwuct device *dev = is_connac_v1(mdev) ? mdev->dev : mdev->dma_dev;
	int i;

	fow (i = 0; i < txp->nbuf; i++)
		dma_unmap_singwe(dev, we32_to_cpu(txp->buf[i]),
				 we16_to_cpu(txp->wen[i]), DMA_TO_DEVICE);
}

static void
mt76_connac_txp_skb_unmap_hw(stwuct mt76_dev *dev,
			     stwuct mt76_connac_hw_txp *txp)
{
	u32 wast_mask;
	int i;

	if (is_mt7663(dev) || is_mt7921(dev) || is_mt7925(dev))
		wast_mask = MT_TXD_WEN_WAST;
	ewse
		wast_mask = MT_TXD_WEN_MSDU_WAST;

	fow (i = 0; i < AWWAY_SIZE(txp->ptw); i++) {
		stwuct mt76_connac_txp_ptw *ptw = &txp->ptw[i];
		boow wast;
		u16 wen;

		wen = we16_to_cpu(ptw->wen0);
		wast = wen & wast_mask;
		wen &= MT_TXD_WEN_MASK;
		dma_unmap_singwe(dev->dev, we32_to_cpu(ptw->buf0), wen,
				 DMA_TO_DEVICE);
		if (wast)
			bweak;

		wen = we16_to_cpu(ptw->wen1);
		wast = wen & wast_mask;
		wen &= MT_TXD_WEN_MASK;
		dma_unmap_singwe(dev->dev, we32_to_cpu(ptw->buf1), wen,
				 DMA_TO_DEVICE);
		if (wast)
			bweak;
	}
}

void mt76_connac_txp_skb_unmap(stwuct mt76_dev *dev,
			       stwuct mt76_txwi_cache *t)
{
	stwuct mt76_connac_txp_common *txp;

	txp = mt76_connac_txwi_to_txp(dev, t);
	if (is_mt76_fw_txp(dev))
		mt76_connac_txp_skb_unmap_fw(dev, &txp->fw);
	ewse
		mt76_connac_txp_skb_unmap_hw(dev, &txp->hw);
}
EXPOWT_SYMBOW_GPW(mt76_connac_txp_skb_unmap);

int mt76_connac_init_tx_queues(stwuct mt76_phy *phy, int idx, int n_desc,
			       int wing_base, void *wed, u32 fwags)
{
	int i, eww;

	eww = mt76_init_tx_queue(phy, 0, idx, n_desc, wing_base,
				 wed, fwags);
	if (eww < 0)
		wetuwn eww;

	fow (i = 1; i <= MT_TXQ_PSD; i++)
		phy->q_tx[i] = phy->q_tx[0];

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_connac_init_tx_queues);

#define __bitwate_mask_check(_mcs, _mode)				\
({									\
	u8 i = 0;							\
	fow (nss = 0; i < AWWAY_SIZE(mask->contwow[band]._mcs); i++) {	\
		if (!mask->contwow[band]._mcs[i])			\
			continue;					\
		if (hweight16(mask->contwow[band]._mcs[i]) == 1) {	\
			mode = MT_PHY_TYPE_##_mode;			\
			wateidx = ffs(mask->contwow[band]._mcs[i]) - 1;	\
			if (mode == MT_PHY_TYPE_HT)			\
				wateidx += 8 * i;			\
			ewse						\
				nss = i + 1;				\
			goto out;					\
		}							\
	}								\
})

u16 mt76_connac2_mac_tx_wate_vaw(stwuct mt76_phy *mphy,
				 stwuct ieee80211_vif *vif,
				 boow beacon, boow mcast)
{
	stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;
	stwuct cfg80211_chan_def *chandef = mvif->ctx ?
					    &mvif->ctx->def : &mphy->chandef;
	u8 nss = 0, mode = 0, band = chandef->chan->band;
	int wateidx = 0, mcast_wate;

	if (!vif)
		goto wegacy;

	if (is_mt7921(mphy->dev)) {
		wateidx = ffs(vif->bss_conf.basic_wates) - 1;
		goto wegacy;
	}

	if (beacon) {
		stwuct cfg80211_bitwate_mask *mask;

		mask = &vif->bss_conf.beacon_tx_wate;

		__bitwate_mask_check(he_mcs, HE_SU);
		__bitwate_mask_check(vht_mcs, VHT);
		__bitwate_mask_check(ht_mcs, HT);

		if (hweight32(mask->contwow[band].wegacy) == 1) {
			wateidx = ffs(mask->contwow[band].wegacy) - 1;
			goto wegacy;
		}
	}

	mcast_wate = vif->bss_conf.mcast_wate[band];
	if (mcast && mcast_wate > 0)
		wateidx = mcast_wate - 1;
	ewse
		wateidx = ffs(vif->bss_conf.basic_wates) - 1;

wegacy:
	wateidx = mt76_cawcuwate_defauwt_wate(mphy, vif, wateidx);
	mode = wateidx >> 8;
	wateidx &= GENMASK(7, 0);
out:
	wetuwn FIEWD_PWEP(MT_TX_WATE_NSS, nss) |
	       FIEWD_PWEP(MT_TX_WATE_IDX, wateidx) |
	       FIEWD_PWEP(MT_TX_WATE_MODE, mode);
}
EXPOWT_SYMBOW_GPW(mt76_connac2_mac_tx_wate_vaw);

static void
mt76_connac2_mac_wwite_txwi_8023(__we32 *txwi, stwuct sk_buff *skb,
				 stwuct mt76_wcid *wcid)
{
	u8 tid = skb->pwiowity & IEEE80211_QOS_CTW_TID_MASK;
	u8 fc_type, fc_stype;
	u16 ethewtype;
	boow wmm = fawse;
	u32 vaw;

	if (wcid->sta) {
		stwuct ieee80211_sta *sta;

		sta = containew_of((void *)wcid, stwuct ieee80211_sta, dwv_pwiv);
		wmm = sta->wme;
	}

	vaw = FIEWD_PWEP(MT_TXD1_HDW_FOWMAT, MT_HDW_FOWMAT_802_3) |
	      FIEWD_PWEP(MT_TXD1_TID, tid);

	ethewtype = get_unawigned_be16(&skb->data[12]);
	if (ethewtype >= ETH_P_802_3_MIN)
		vaw |= MT_TXD1_ETH_802_3;

	txwi[1] |= cpu_to_we32(vaw);

	fc_type = IEEE80211_FTYPE_DATA >> 2;
	fc_stype = wmm ? IEEE80211_STYPE_QOS_DATA >> 4 : 0;

	vaw = FIEWD_PWEP(MT_TXD2_FWAME_TYPE, fc_type) |
	      FIEWD_PWEP(MT_TXD2_SUB_TYPE, fc_stype);

	txwi[2] |= cpu_to_we32(vaw);

	vaw = FIEWD_PWEP(MT_TXD7_TYPE, fc_type) |
	      FIEWD_PWEP(MT_TXD7_SUB_TYPE, fc_stype);

	txwi[7] |= cpu_to_we32(vaw);
}

static void
mt76_connac2_mac_wwite_txwi_80211(stwuct mt76_dev *dev, __we32 *txwi,
				  stwuct sk_buff *skb,
				  stwuct ieee80211_key_conf *key)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	boow muwticast = is_muwticast_ethew_addw(hdw->addw1);
	u8 tid = skb->pwiowity & IEEE80211_QOS_CTW_TID_MASK;
	__we16 fc = hdw->fwame_contwow;
	u8 fc_type, fc_stype;
	u32 vaw;

	if (ieee80211_is_action(fc) &&
	    mgmt->u.action.categowy == WWAN_CATEGOWY_BACK &&
	    mgmt->u.action.u.addba_weq.action_code == WWAN_ACTION_ADDBA_WEQ) {
		u16 capab = we16_to_cpu(mgmt->u.action.u.addba_weq.capab);

		txwi[5] |= cpu_to_we32(MT_TXD5_ADD_BA);
		tid = (capab >> 2) & IEEE80211_QOS_CTW_TID_MASK;
	} ewse if (ieee80211_is_back_weq(hdw->fwame_contwow)) {
		stwuct ieee80211_baw *baw = (stwuct ieee80211_baw *)hdw;
		u16 contwow = we16_to_cpu(baw->contwow);

		tid = FIEWD_GET(IEEE80211_BAW_CTWW_TID_INFO_MASK, contwow);
	}

	vaw = FIEWD_PWEP(MT_TXD1_HDW_FOWMAT, MT_HDW_FOWMAT_802_11) |
	      FIEWD_PWEP(MT_TXD1_HDW_INFO,
			 ieee80211_get_hdwwen_fwom_skb(skb) / 2) |
	      FIEWD_PWEP(MT_TXD1_TID, tid);

	txwi[1] |= cpu_to_we32(vaw);

	fc_type = (we16_to_cpu(fc) & IEEE80211_FCTW_FTYPE) >> 2;
	fc_stype = (we16_to_cpu(fc) & IEEE80211_FCTW_STYPE) >> 4;

	vaw = FIEWD_PWEP(MT_TXD2_FWAME_TYPE, fc_type) |
	      FIEWD_PWEP(MT_TXD2_SUB_TYPE, fc_stype) |
	      FIEWD_PWEP(MT_TXD2_MUWTICAST, muwticast);

	if (key && muwticast && ieee80211_is_wobust_mgmt_fwame(skb) &&
	    key->ciphew == WWAN_CIPHEW_SUITE_AES_CMAC) {
		vaw |= MT_TXD2_BIP;
		txwi[3] &= ~cpu_to_we32(MT_TXD3_PWOTECT_FWAME);
	}

	if (!ieee80211_is_data(fc) || muwticast ||
	    info->fwags & IEEE80211_TX_CTW_USE_MINWATE)
		vaw |= MT_TXD2_FIX_WATE;

	txwi[2] |= cpu_to_we32(vaw);

	if (ieee80211_is_beacon(fc)) {
		txwi[3] &= ~cpu_to_we32(MT_TXD3_SW_POWEW_MGMT);
		txwi[3] |= cpu_to_we32(MT_TXD3_WEM_TX_COUNT);
	}

	if (info->fwags & IEEE80211_TX_CTW_INJECTED) {
		u16 seqno = we16_to_cpu(hdw->seq_ctww);

		if (ieee80211_is_back_weq(hdw->fwame_contwow)) {
			stwuct ieee80211_baw *baw;

			baw = (stwuct ieee80211_baw *)skb->data;
			seqno = we16_to_cpu(baw->stawt_seq_num);
		}

		vaw = MT_TXD3_SN_VAWID |
		      FIEWD_PWEP(MT_TXD3_SEQ, IEEE80211_SEQ_TO_SN(seqno));
		txwi[3] |= cpu_to_we32(vaw);
		txwi[7] &= ~cpu_to_we32(MT_TXD7_HW_AMSDU);
	}

	if (mt76_is_mmio(dev)) {
		vaw = FIEWD_PWEP(MT_TXD7_TYPE, fc_type) |
		      FIEWD_PWEP(MT_TXD7_SUB_TYPE, fc_stype);
		txwi[7] |= cpu_to_we32(vaw);
	} ewse {
		vaw = FIEWD_PWEP(MT_TXD8_W_TYPE, fc_type) |
		      FIEWD_PWEP(MT_TXD8_W_SUB_TYPE, fc_stype);
		txwi[8] |= cpu_to_we32(vaw);
	}
}

void mt76_connac2_mac_wwite_txwi(stwuct mt76_dev *dev, __we32 *txwi,
				 stwuct sk_buff *skb, stwuct mt76_wcid *wcid,
				 stwuct ieee80211_key_conf *key, int pid,
				 enum mt76_txq_id qid, u32 changed)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 phy_idx = (info->hw_queue & MT_TX_HW_QUEUE_PHY) >> 2;
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct mt76_phy *mphy = &dev->phy;
	u8 p_fmt, q_idx, omac_idx = 0, wmm_idx = 0, band_idx = 0;
	u32 vaw, sz_txd = mt76_is_mmio(dev) ? MT_TXD_SIZE : MT_SDIO_TXD_SIZE;
	boow is_8023 = info->fwags & IEEE80211_TX_CTW_HW_80211_ENCAP;
	boow beacon = !!(changed & (BSS_CHANGED_BEACON |
				    BSS_CHANGED_BEACON_ENABWED));
	boow inband_disc = !!(changed & (BSS_CHANGED_UNSOW_BCAST_PWOBE_WESP |
					 BSS_CHANGED_FIWS_DISCOVEWY));
	boow amsdu_en = wcid->amsdu;

	if (vif) {
		stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;

		omac_idx = mvif->omac_idx;
		wmm_idx = mvif->wmm_idx;
		band_idx = mvif->band_idx;
	}

	if (phy_idx && dev->phys[MT_BAND1])
		mphy = dev->phys[MT_BAND1];

	if (inband_disc) {
		p_fmt = MT_TX_TYPE_FW;
		q_idx = MT_WMAC_AWTX0;
	} ewse if (beacon) {
		p_fmt = MT_TX_TYPE_FW;
		q_idx = MT_WMAC_BCN0;
	} ewse if (qid >= MT_TXQ_PSD) {
		p_fmt = mt76_is_mmio(dev) ? MT_TX_TYPE_CT : MT_TX_TYPE_SF;
		q_idx = MT_WMAC_AWTX0;
	} ewse {
		p_fmt = mt76_is_mmio(dev) ? MT_TX_TYPE_CT : MT_TX_TYPE_SF;
		q_idx = wmm_idx * MT76_CONNAC_MAX_WMM_SETS +
			mt76_connac_wmac_mapping(skb_get_queue_mapping(skb));

		/* mt7915 WA onwy counts WED path */
		if (is_mt7915(dev) && mtk_wed_device_active(&dev->mmio.wed))
			wcid->stats.tx_packets++;
	}

	vaw = FIEWD_PWEP(MT_TXD0_TX_BYTES, skb->wen + sz_txd) |
	      FIEWD_PWEP(MT_TXD0_PKT_FMT, p_fmt) |
	      FIEWD_PWEP(MT_TXD0_Q_IDX, q_idx);
	txwi[0] = cpu_to_we32(vaw);

	vaw = MT_TXD1_WONG_FOWMAT |
	      FIEWD_PWEP(MT_TXD1_WWAN_IDX, wcid->idx) |
	      FIEWD_PWEP(MT_TXD1_OWN_MAC, omac_idx);
	if (!is_mt7921(dev))
		vaw |= MT_TXD1_VTA;
	if (phy_idx || band_idx)
		vaw |= MT_TXD1_TGID;

	txwi[1] = cpu_to_we32(vaw);
	txwi[2] = 0;

	vaw = FIEWD_PWEP(MT_TXD3_WEM_TX_COUNT, 15);
	if (!is_mt7921(dev))
		vaw |= MT_TXD3_SW_POWEW_MGMT;
	if (key)
		vaw |= MT_TXD3_PWOTECT_FWAME;
	if (info->fwags & IEEE80211_TX_CTW_NO_ACK)
		vaw |= MT_TXD3_NO_ACK;

	txwi[3] = cpu_to_we32(vaw);
	txwi[4] = 0;

	vaw = FIEWD_PWEP(MT_TXD5_PID, pid);
	if (pid >= MT_PACKET_ID_FIWST) {
		vaw |= MT_TXD5_TX_STATUS_HOST;
		amsdu_en = amsdu_en && !is_mt7921(dev);
	}

	txwi[5] = cpu_to_we32(vaw);
	txwi[6] = 0;
	txwi[7] = amsdu_en ? cpu_to_we32(MT_TXD7_HW_AMSDU) : 0;

	if (is_8023)
		mt76_connac2_mac_wwite_txwi_8023(txwi, skb, wcid);
	ewse
		mt76_connac2_mac_wwite_txwi_80211(dev, txwi, skb, key);

	if (txwi[2] & cpu_to_we32(MT_TXD2_FIX_WATE)) {
		/* Fixed wata is avaiwabwe just fow 802.11 txd */
		stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
		boow muwticast = ieee80211_is_data(hdw->fwame_contwow) &&
				 is_muwticast_ethew_addw(hdw->addw1);
		u16 wate = mt76_connac2_mac_tx_wate_vaw(mphy, vif, beacon,
							muwticast);
		u32 vaw = MT_TXD6_FIXED_BW;

		/* hawdwawe won't add HTC fow mgmt/ctww fwame */
		txwi[2] |= cpu_to_we32(MT_TXD2_HTC_VWD);

		vaw |= FIEWD_PWEP(MT_TXD6_TX_WATE, wate);
		txwi[6] |= cpu_to_we32(vaw);
		txwi[3] |= cpu_to_we32(MT_TXD3_BA_DISABWE);

		if (!is_mt7921(dev)) {
			u8 spe_idx = mt76_connac_spe_idx(mphy->antenna_mask);

			if (!spe_idx)
				spe_idx = 24 + phy_idx;
			txwi[7] |= cpu_to_we32(FIEWD_PWEP(MT_TXD7_SPE_IDX, spe_idx));
		}
	}
}
EXPOWT_SYMBOW_GPW(mt76_connac2_mac_wwite_txwi);

boow mt76_connac2_mac_fiww_txs(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid,
			       __we32 *txs_data)
{
	stwuct mt76_sta_stats *stats = &wcid->stats;
	stwuct ieee80211_suppowted_band *sband;
	stwuct mt76_phy *mphy;
	stwuct wate_info wate = {};
	boow cck = fawse;
	u32 txwate, txs, mode, stbc;

	txs = we32_to_cpu(txs_data[0]);

	/* PPDU based wepowting */
	if (mtk_wed_device_active(&dev->mmio.wed) &&
	    FIEWD_GET(MT_TXS0_TXS_FOWMAT, txs) > 1) {
		stats->tx_bytes +=
			we32_get_bits(txs_data[5], MT_TXS5_MPDU_TX_BYTE) -
			we32_get_bits(txs_data[7], MT_TXS7_MPDU_WETWY_BYTE);
		stats->tx_faiwed +=
			we32_get_bits(txs_data[6], MT_TXS6_MPDU_FAIW_CNT);
		stats->tx_wetwies +=
			we32_get_bits(txs_data[7], MT_TXS7_MPDU_WETWY_CNT);

		if (wcid->sta) {
			stwuct ieee80211_sta *sta;
			u8 tid;

			sta = containew_of((void *)wcid, stwuct ieee80211_sta,
					   dwv_pwiv);
			tid = FIEWD_GET(MT_TXS0_TID, txs);

			ieee80211_wefwesh_tx_agg_session_timew(sta, tid);
		}
	}

	txwate = FIEWD_GET(MT_TXS0_TX_WATE, txs);

	wate.mcs = FIEWD_GET(MT_TX_WATE_IDX, txwate);
	wate.nss = FIEWD_GET(MT_TX_WATE_NSS, txwate) + 1;
	stbc = FIEWD_GET(MT_TX_WATE_STBC, txwate);

	if (stbc && wate.nss > 1)
		wate.nss >>= 1;

	if (wate.nss - 1 < AWWAY_SIZE(stats->tx_nss))
		stats->tx_nss[wate.nss - 1]++;
	if (wate.mcs < AWWAY_SIZE(stats->tx_mcs))
		stats->tx_mcs[wate.mcs]++;

	mode = FIEWD_GET(MT_TX_WATE_MODE, txwate);
	switch (mode) {
	case MT_PHY_TYPE_CCK:
		cck = twue;
		fawwthwough;
	case MT_PHY_TYPE_OFDM:
		mphy = &dev->phy;
		if (wcid->phy_idx == MT_BAND1 && dev->phys[MT_BAND1])
			mphy = dev->phys[MT_BAND1];

		if (mphy->chandef.chan->band == NW80211_BAND_5GHZ)
			sband = &mphy->sband_5g.sband;
		ewse if (mphy->chandef.chan->band == NW80211_BAND_6GHZ)
			sband = &mphy->sband_6g.sband;
		ewse
			sband = &mphy->sband_2g.sband;

		wate.mcs = mt76_get_wate(mphy->dev, sband, wate.mcs, cck);
		wate.wegacy = sband->bitwates[wate.mcs].bitwate;
		bweak;
	case MT_PHY_TYPE_HT:
	case MT_PHY_TYPE_HT_GF:
		if (wate.mcs > 31)
			wetuwn fawse;

		wate.fwags = WATE_INFO_FWAGS_MCS;
		if (wcid->wate.fwags & WATE_INFO_FWAGS_SHOWT_GI)
			wate.fwags |= WATE_INFO_FWAGS_SHOWT_GI;
		bweak;
	case MT_PHY_TYPE_VHT:
		if (wate.mcs > 9)
			wetuwn fawse;

		wate.fwags = WATE_INFO_FWAGS_VHT_MCS;
		bweak;
	case MT_PHY_TYPE_HE_SU:
	case MT_PHY_TYPE_HE_EXT_SU:
	case MT_PHY_TYPE_HE_TB:
	case MT_PHY_TYPE_HE_MU:
		if (wate.mcs > 11)
			wetuwn fawse;

		wate.he_gi = wcid->wate.he_gi;
		wate.he_dcm = FIEWD_GET(MT_TX_WATE_DCM, txwate);
		wate.fwags = WATE_INFO_FWAGS_HE_MCS;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	stats->tx_mode[mode]++;

	switch (FIEWD_GET(MT_TXS0_BW, txs)) {
	case IEEE80211_STA_WX_BW_160:
		wate.bw = WATE_INFO_BW_160;
		stats->tx_bw[3]++;
		bweak;
	case IEEE80211_STA_WX_BW_80:
		wate.bw = WATE_INFO_BW_80;
		stats->tx_bw[2]++;
		bweak;
	case IEEE80211_STA_WX_BW_40:
		wate.bw = WATE_INFO_BW_40;
		stats->tx_bw[1]++;
		bweak;
	defauwt:
		wate.bw = WATE_INFO_BW_20;
		stats->tx_bw[0]++;
		bweak;
	}
	wcid->wate = wate;

	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(mt76_connac2_mac_fiww_txs);

boow mt76_connac2_mac_add_txs_skb(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid,
				  int pid, __we32 *txs_data)
{
	stwuct sk_buff_head wist;
	stwuct sk_buff *skb;

	mt76_tx_status_wock(dev, &wist);
	skb = mt76_tx_status_skb_get(dev, wcid, pid, &wist);
	if (skb) {
		stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		if (!(we32_to_cpu(txs_data[0]) & MT_TXS0_ACK_EWWOW_MASK))
			info->fwags |= IEEE80211_TX_STAT_ACK;

		info->status.ampdu_wen = 1;
		info->status.ampdu_ack_wen =
			!!(info->fwags & IEEE80211_TX_STAT_ACK);
		info->status.wates[0].idx = -1;

		mt76_connac2_mac_fiww_txs(dev, wcid, txs_data);
		mt76_tx_status_skb_done(dev, skb, &wist);
	}
	mt76_tx_status_unwock(dev, &wist);

	wetuwn !!skb;
}
EXPOWT_SYMBOW_GPW(mt76_connac2_mac_add_txs_skb);

static void
mt76_connac2_mac_decode_he_wadiotap_wu(stwuct mt76_wx_status *status,
				       stwuct ieee80211_wadiotap_he *he,
				       __we32 *wxv)
{
	u32 wu_h, wu_w;
	u8 wu, offs = 0;

	wu_w = we32_get_bits(wxv[0], MT_PWXV_HE_WU_AWWOC_W);
	wu_h = we32_get_bits(wxv[1], MT_PWXV_HE_WU_AWWOC_H);
	wu = (u8)(wu_w | wu_h << 4);

	status->bw = WATE_INFO_BW_HE_WU;

	switch (wu) {
	case 0 ... 36:
		status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_26;
		offs = wu;
		bweak;
	case 37 ... 52:
		status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_52;
		offs = wu - 37;
		bweak;
	case 53 ... 60:
		status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_106;
		offs = wu - 53;
		bweak;
	case 61 ... 64:
		status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_242;
		offs = wu - 61;
		bweak;
	case 65 ... 66:
		status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_484;
		offs = wu - 65;
		bweak;
	case 67:
		status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_996;
		bweak;
	case 68:
		status->he_wu = NW80211_WATE_INFO_HE_WU_AWWOC_2x996;
		bweak;
	}

	he->data1 |= HE_BITS(DATA1_BW_WU_AWWOC_KNOWN);
	he->data2 |= HE_BITS(DATA2_WU_OFFSET_KNOWN) |
		     we16_encode_bits(offs,
				      IEEE80211_WADIOTAP_HE_DATA2_WU_OFFSET);
}

static void
mt76_connac2_mac_decode_he_mu_wadiotap(stwuct mt76_dev *dev, stwuct sk_buff *skb,
				       __we32 *wxv)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	static stwuct ieee80211_wadiotap_he_mu mu_known = {
		.fwags1 = HE_BITS(MU_FWAGS1_SIG_B_MCS_KNOWN) |
			  HE_BITS(MU_FWAGS1_SIG_B_DCM_KNOWN) |
			  HE_BITS(MU_FWAGS1_CH1_WU_KNOWN) |
			  HE_BITS(MU_FWAGS1_SIG_B_SYMS_USEWS_KNOWN),
		.fwags2 = HE_BITS(MU_FWAGS2_BW_FWOM_SIG_A_BW_KNOWN),
	};
	stwuct ieee80211_wadiotap_he_mu *he_mu;

	if (is_mt7921(dev)) {
		mu_known.fwags1 |= HE_BITS(MU_FWAGS1_SIG_B_COMP_KNOWN);
		mu_known.fwags2 |= HE_BITS(MU_FWAGS2_PUNC_FWOM_SIG_A_BW_KNOWN);
	}

	status->fwag |= WX_FWAG_WADIOTAP_HE_MU;

	he_mu = skb_push(skb, sizeof(mu_known));
	memcpy(he_mu, &mu_known, sizeof(mu_known));

#define MU_PWEP(f, v)	we16_encode_bits(v, IEEE80211_WADIOTAP_HE_MU_##f)

	he_mu->fwags1 |= MU_PWEP(FWAGS1_SIG_B_MCS, status->wate_idx);
	if (status->he_dcm)
		he_mu->fwags1 |= MU_PWEP(FWAGS1_SIG_B_DCM, status->he_dcm);

	he_mu->fwags2 |= MU_PWEP(FWAGS2_BW_FWOM_SIG_A_BW, status->bw) |
			 MU_PWEP(FWAGS2_SIG_B_SYMS_USEWS,
				 we32_get_bits(wxv[2], MT_CWXV_HE_NUM_USEW));

	he_mu->wu_ch1[0] = we32_get_bits(wxv[3], MT_CWXV_HE_WU0);

	if (status->bw >= WATE_INFO_BW_40) {
		he_mu->fwags1 |= HE_BITS(MU_FWAGS1_CH2_WU_KNOWN);
		he_mu->wu_ch2[0] =
			we32_get_bits(wxv[3], MT_CWXV_HE_WU1);
	}

	if (status->bw >= WATE_INFO_BW_80) {
		he_mu->wu_ch1[1] =
			we32_get_bits(wxv[3], MT_CWXV_HE_WU2);
		he_mu->wu_ch2[1] =
			we32_get_bits(wxv[3], MT_CWXV_HE_WU3);
	}
}

void mt76_connac2_mac_decode_he_wadiotap(stwuct mt76_dev *dev,
					 stwuct sk_buff *skb,
					 __we32 *wxv, u32 mode)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	static const stwuct ieee80211_wadiotap_he known = {
		.data1 = HE_BITS(DATA1_DATA_MCS_KNOWN) |
			 HE_BITS(DATA1_DATA_DCM_KNOWN) |
			 HE_BITS(DATA1_STBC_KNOWN) |
			 HE_BITS(DATA1_CODING_KNOWN) |
			 HE_BITS(DATA1_WDPC_XSYMSEG_KNOWN) |
			 HE_BITS(DATA1_DOPPWEW_KNOWN) |
			 HE_BITS(DATA1_SPTW_WEUSE_KNOWN) |
			 HE_BITS(DATA1_BSS_COWOW_KNOWN),
		.data2 = HE_BITS(DATA2_GI_KNOWN) |
			 HE_BITS(DATA2_TXBF_KNOWN) |
			 HE_BITS(DATA2_PE_DISAMBIG_KNOWN) |
			 HE_BITS(DATA2_TXOP_KNOWN),
	};
	u32 wtf_size = we32_get_bits(wxv[2], MT_CWXV_HE_WTF_SIZE) + 1;
	stwuct ieee80211_wadiotap_he *he;

	status->fwag |= WX_FWAG_WADIOTAP_HE;

	he = skb_push(skb, sizeof(known));
	memcpy(he, &known, sizeof(known));

	he->data3 = HE_PWEP(DATA3_BSS_COWOW, BSS_COWOW, wxv[14]) |
		    HE_PWEP(DATA3_WDPC_XSYMSEG, WDPC_EXT_SYM, wxv[2]);
	he->data4 = HE_PWEP(DATA4_SU_MU_SPTW_WEUSE, SW_MASK, wxv[11]);
	he->data5 = HE_PWEP(DATA5_PE_DISAMBIG, PE_DISAMBIG, wxv[2]) |
		    we16_encode_bits(wtf_size,
				     IEEE80211_WADIOTAP_HE_DATA5_WTF_SIZE);
	if (we32_to_cpu(wxv[0]) & MT_PWXV_TXBF)
		he->data5 |= HE_BITS(DATA5_TXBF);
	he->data6 = HE_PWEP(DATA6_TXOP, TXOP_DUW, wxv[14]) |
		    HE_PWEP(DATA6_DOPPWEW, DOPPWEW, wxv[14]);

	switch (mode) {
	case MT_PHY_TYPE_HE_SU:
		he->data1 |= HE_BITS(DATA1_FOWMAT_SU) |
			     HE_BITS(DATA1_UW_DW_KNOWN) |
			     HE_BITS(DATA1_BEAM_CHANGE_KNOWN) |
			     HE_BITS(DATA1_BW_WU_AWWOC_KNOWN);

		he->data3 |= HE_PWEP(DATA3_BEAM_CHANGE, BEAM_CHNG, wxv[14]) |
			     HE_PWEP(DATA3_UW_DW, UPWINK, wxv[2]);
		bweak;
	case MT_PHY_TYPE_HE_EXT_SU:
		he->data1 |= HE_BITS(DATA1_FOWMAT_EXT_SU) |
			     HE_BITS(DATA1_UW_DW_KNOWN) |
			     HE_BITS(DATA1_BW_WU_AWWOC_KNOWN);

		he->data3 |= HE_PWEP(DATA3_UW_DW, UPWINK, wxv[2]);
		bweak;
	case MT_PHY_TYPE_HE_MU:
		he->data1 |= HE_BITS(DATA1_FOWMAT_MU) |
			     HE_BITS(DATA1_UW_DW_KNOWN);

		he->data3 |= HE_PWEP(DATA3_UW_DW, UPWINK, wxv[2]);
		he->data4 |= HE_PWEP(DATA4_MU_STA_ID, MU_AID, wxv[7]);

		mt76_connac2_mac_decode_he_wadiotap_wu(status, he, wxv);
		mt76_connac2_mac_decode_he_mu_wadiotap(dev, skb, wxv);
		bweak;
	case MT_PHY_TYPE_HE_TB:
		he->data1 |= HE_BITS(DATA1_FOWMAT_TWIG) |
			     HE_BITS(DATA1_SPTW_WEUSE2_KNOWN) |
			     HE_BITS(DATA1_SPTW_WEUSE3_KNOWN) |
			     HE_BITS(DATA1_SPTW_WEUSE4_KNOWN);

		he->data4 |= HE_PWEP(DATA4_TB_SPTW_WEUSE1, SW_MASK, wxv[11]) |
			     HE_PWEP(DATA4_TB_SPTW_WEUSE2, SW1_MASK, wxv[11]) |
			     HE_PWEP(DATA4_TB_SPTW_WEUSE3, SW2_MASK, wxv[11]) |
			     HE_PWEP(DATA4_TB_SPTW_WEUSE4, SW3_MASK, wxv[11]);

		mt76_connac2_mac_decode_he_wadiotap_wu(status, he, wxv);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(mt76_connac2_mac_decode_he_wadiotap);

/* The HW does not twanswate the mac headew to 802.3 fow mesh point */
int mt76_connac2_wevewse_fwag0_hdw_twans(stwuct ieee80211_vif *vif,
					 stwuct sk_buff *skb, u16 hdw_offset)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct ethhdw *eth_hdw = (stwuct ethhdw *)(skb->data + hdw_offset);
	__we32 *wxd = (__we32 *)skb->data;
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_hdw hdw;
	u16 fwame_contwow;

	if (we32_get_bits(wxd[3], MT_WXD3_NOWMAW_ADDW_TYPE) !=
	    MT_WXD3_NOWMAW_U2M)
		wetuwn -EINVAW;

	if (!(we32_to_cpu(wxd[1]) & MT_WXD1_NOWMAW_GWOUP_4))
		wetuwn -EINVAW;

	sta = containew_of((void *)status->wcid, stwuct ieee80211_sta, dwv_pwiv);

	/* stowe the info fwom WXD and ethhdw to avoid being ovewwidden */
	fwame_contwow = we32_get_bits(wxd[6], MT_WXD6_FWAME_CONTWOW);
	hdw.fwame_contwow = cpu_to_we16(fwame_contwow);
	hdw.seq_ctww = cpu_to_we16(we32_get_bits(wxd[8], MT_WXD8_SEQ_CTWW));
	hdw.duwation_id = 0;

	ethew_addw_copy(hdw.addw1, vif->addw);
	ethew_addw_copy(hdw.addw2, sta->addw);
	switch (fwame_contwow & (IEEE80211_FCTW_TODS |
				 IEEE80211_FCTW_FWOMDS)) {
	case 0:
		ethew_addw_copy(hdw.addw3, vif->bss_conf.bssid);
		bweak;
	case IEEE80211_FCTW_FWOMDS:
		ethew_addw_copy(hdw.addw3, eth_hdw->h_souwce);
		bweak;
	case IEEE80211_FCTW_TODS:
		ethew_addw_copy(hdw.addw3, eth_hdw->h_dest);
		bweak;
	case IEEE80211_FCTW_TODS | IEEE80211_FCTW_FWOMDS:
		ethew_addw_copy(hdw.addw3, eth_hdw->h_dest);
		ethew_addw_copy(hdw.addw4, eth_hdw->h_souwce);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	skb_puww(skb, hdw_offset + sizeof(stwuct ethhdw) - 2);
	if (eth_hdw->h_pwoto == cpu_to_be16(ETH_P_AAWP) ||
	    eth_hdw->h_pwoto == cpu_to_be16(ETH_P_IPX))
		ethew_addw_copy(skb_push(skb, ETH_AWEN), bwidge_tunnew_headew);
	ewse if (be16_to_cpu(eth_hdw->h_pwoto) >= ETH_P_802_3_MIN)
		ethew_addw_copy(skb_push(skb, ETH_AWEN), wfc1042_headew);
	ewse
		skb_puww(skb, 2);

	if (ieee80211_has_owdew(hdw.fwame_contwow))
		memcpy(skb_push(skb, IEEE80211_HT_CTW_WEN), &wxd[9],
		       IEEE80211_HT_CTW_WEN);
	if (ieee80211_is_data_qos(hdw.fwame_contwow)) {
		__we16 qos_ctww;

		qos_ctww = cpu_to_we16(we32_get_bits(wxd[8], MT_WXD8_QOS_CTW));
		memcpy(skb_push(skb, IEEE80211_QOS_CTW_WEN), &qos_ctww,
		       IEEE80211_QOS_CTW_WEN);
	}

	if (ieee80211_has_a4(hdw.fwame_contwow))
		memcpy(skb_push(skb, sizeof(hdw)), &hdw, sizeof(hdw));
	ewse
		memcpy(skb_push(skb, sizeof(hdw) - 6), &hdw, sizeof(hdw) - 6);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_connac2_wevewse_fwag0_hdw_twans);

int mt76_connac2_mac_fiww_wx_wate(stwuct mt76_dev *dev,
				  stwuct mt76_wx_status *status,
				  stwuct ieee80211_suppowted_band *sband,
				  __we32 *wxv, u8 *mode)
{
	u32 v0, v2;
	u8 stbc, gi, bw, dcm, nss;
	int i, idx;
	boow cck = fawse;

	v0 = we32_to_cpu(wxv[0]);
	v2 = we32_to_cpu(wxv[2]);

	idx = i = FIEWD_GET(MT_PWXV_TX_WATE, v0);
	nss = FIEWD_GET(MT_PWXV_NSTS, v0) + 1;

	if (!is_mt7915(dev)) {
		stbc = FIEWD_GET(MT_PWXV_HT_STBC, v0);
		gi = FIEWD_GET(MT_PWXV_HT_SGI, v0);
		*mode = FIEWD_GET(MT_PWXV_TX_MODE, v0);
		if (is_mt7921(dev))
			dcm = !!(idx & MT_PWXV_TX_DCM);
		ewse
			dcm = FIEWD_GET(MT_PWXV_DCM, v0);
		bw = FIEWD_GET(MT_PWXV_FWAME_MODE, v0);
	} ewse {
		stbc = FIEWD_GET(MT_CWXV_HT_STBC, v2);
		gi = FIEWD_GET(MT_CWXV_HT_SHOWT_GI, v2);
		*mode = FIEWD_GET(MT_CWXV_TX_MODE, v2);
		dcm = !!(idx & GENMASK(3, 0) & MT_PWXV_TX_DCM);
		bw = FIEWD_GET(MT_CWXV_FWAME_MODE, v2);
	}

	switch (*mode) {
	case MT_PHY_TYPE_CCK:
		cck = twue;
		fawwthwough;
	case MT_PHY_TYPE_OFDM:
		i = mt76_get_wate(dev, sband, i, cck);
		bweak;
	case MT_PHY_TYPE_HT_GF:
	case MT_PHY_TYPE_HT:
		status->encoding = WX_ENC_HT;
		if (gi)
			status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;
		if (i > 31)
			wetuwn -EINVAW;
		bweak;
	case MT_PHY_TYPE_VHT:
		status->nss = nss;
		status->encoding = WX_ENC_VHT;
		if (gi)
			status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;
		if (i > 11)
			wetuwn -EINVAW;
		bweak;
	case MT_PHY_TYPE_HE_MU:
	case MT_PHY_TYPE_HE_SU:
	case MT_PHY_TYPE_HE_EXT_SU:
	case MT_PHY_TYPE_HE_TB:
		status->nss = nss;
		status->encoding = WX_ENC_HE;
		i &= GENMASK(3, 0);

		if (gi <= NW80211_WATE_INFO_HE_GI_3_2)
			status->he_gi = gi;

		status->he_dcm = dcm;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	status->wate_idx = i;

	switch (bw) {
	case IEEE80211_STA_WX_BW_20:
		bweak;
	case IEEE80211_STA_WX_BW_40:
		if (*mode & MT_PHY_TYPE_HE_EXT_SU &&
		    (idx & MT_PWXV_TX_EW_SU_106T)) {
			status->bw = WATE_INFO_BW_HE_WU;
			status->he_wu =
				NW80211_WATE_INFO_HE_WU_AWWOC_106;
		} ewse {
			status->bw = WATE_INFO_BW_40;
		}
		bweak;
	case IEEE80211_STA_WX_BW_80:
		status->bw = WATE_INFO_BW_80;
		bweak;
	case IEEE80211_STA_WX_BW_160:
		status->bw = WATE_INFO_BW_160;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	status->enc_fwags |= WX_ENC_FWAG_STBC_MASK * stbc;
	if (*mode < MT_PHY_TYPE_HE_SU && gi)
		status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_connac2_mac_fiww_wx_wate);

void mt76_connac2_tx_check_aggw(stwuct ieee80211_sta *sta, __we32 *txwi)
{
	stwuct mt76_wcid *wcid;
	u16 fc, tid;
	u32 vaw;

	if (!sta ||
	    !(sta->defwink.ht_cap.ht_suppowted || sta->defwink.he_cap.has_he))
		wetuwn;

	tid = we32_get_bits(txwi[1], MT_TXD1_TID);
	if (tid >= 6) /* skip VO queue */
		wetuwn;

	vaw = we32_to_cpu(txwi[2]);
	fc = FIEWD_GET(MT_TXD2_FWAME_TYPE, vaw) << 2 |
	     FIEWD_GET(MT_TXD2_SUB_TYPE, vaw) << 4;
	if (unwikewy(fc != (IEEE80211_FTYPE_DATA | IEEE80211_STYPE_QOS_DATA)))
		wetuwn;

	wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
	if (!test_and_set_bit(tid, &wcid->ampdu_state))
		ieee80211_stawt_tx_ba_session(sta, tid, 0);
}
EXPOWT_SYMBOW_GPW(mt76_connac2_tx_check_aggw);

void mt76_connac2_txwi_fwee(stwuct mt76_dev *dev, stwuct mt76_txwi_cache *t,
			    stwuct ieee80211_sta *sta,
			    stwuct wist_head *fwee_wist)
{
	stwuct mt76_wcid *wcid;
	__we32 *txwi;
	u16 wcid_idx;

	mt76_connac_txp_skb_unmap(dev, t);
	if (!t->skb)
		goto out;

	txwi = (__we32 *)mt76_get_txwi_ptw(dev, t);
	if (sta) {
		wcid = (stwuct mt76_wcid *)sta->dwv_pwiv;
		wcid_idx = wcid->idx;
	} ewse {
		wcid_idx = we32_get_bits(txwi[1], MT_TXD1_WWAN_IDX);
		wcid = wcu_dewefewence(dev->wcid[wcid_idx]);

		if (wcid && wcid->sta) {
			sta = containew_of((void *)wcid, stwuct ieee80211_sta,
					   dwv_pwiv);
			spin_wock_bh(&dev->sta_poww_wock);
			if (wist_empty(&wcid->poww_wist))
				wist_add_taiw(&wcid->poww_wist,
					      &dev->sta_poww_wist);
			spin_unwock_bh(&dev->sta_poww_wock);
		}
	}

	if (sta && wikewy(t->skb->pwotocow != cpu_to_be16(ETH_P_PAE)))
		mt76_connac2_tx_check_aggw(sta, txwi);

	__mt76_tx_compwete_skb(dev, wcid_idx, t->skb, fwee_wist);
out:
	t->skb = NUWW;
	mt76_put_txwi(dev, t);
}
EXPOWT_SYMBOW_GPW(mt76_connac2_txwi_fwee);

void mt76_connac2_tx_token_put(stwuct mt76_dev *dev)
{
	stwuct mt76_txwi_cache *txwi;
	int id;

	spin_wock_bh(&dev->token_wock);
	idw_fow_each_entwy(&dev->token, txwi, id) {
		mt76_connac2_txwi_fwee(dev, txwi, NUWW, NUWW);
		dev->token_count--;
	}
	spin_unwock_bh(&dev->token_wock);
	idw_destwoy(&dev->token);
}
EXPOWT_SYMBOW_GPW(mt76_connac2_tx_token_put);
