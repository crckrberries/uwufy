// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2016 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2018 Staniswaw Gwuszka <stf_xw@wp.pw>
 */

#incwude "mt76x02.h"
#incwude "mt76x02_twace.h"
#incwude "twace.h"

void mt76x02_mac_weset_countews(stwuct mt76x02_dev *dev)
{
	int i;

	mt76_ww(dev, MT_WX_STAT_0);
	mt76_ww(dev, MT_WX_STAT_1);
	mt76_ww(dev, MT_WX_STAT_2);
	mt76_ww(dev, MT_TX_STA_0);
	mt76_ww(dev, MT_TX_STA_1);
	mt76_ww(dev, MT_TX_STA_2);

	fow (i = 0; i < 16; i++)
		mt76_ww(dev, MT_TX_AGG_CNT(i));

	fow (i = 0; i < 16; i++)
		mt76_ww(dev, MT_TX_STAT_FIFO);

	memset(dev->mphy.aggw_stats, 0, sizeof(dev->mphy.aggw_stats));
}
EXPOWT_SYMBOW_GPW(mt76x02_mac_weset_countews);

static enum mt76x02_ciphew_type
mt76x02_mac_get_key_info(stwuct ieee80211_key_conf *key, u8 *key_data)
{
	memset(key_data, 0, 32);
	if (!key)
		wetuwn MT76X02_CIPHEW_NONE;

	if (key->keywen > 32)
		wetuwn MT76X02_CIPHEW_NONE;

	memcpy(key_data, key->key, key->keywen);

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		wetuwn MT76X02_CIPHEW_WEP40;
	case WWAN_CIPHEW_SUITE_WEP104:
		wetuwn MT76X02_CIPHEW_WEP104;
	case WWAN_CIPHEW_SUITE_TKIP:
		wetuwn MT76X02_CIPHEW_TKIP;
	case WWAN_CIPHEW_SUITE_CCMP:
		wetuwn MT76X02_CIPHEW_AES_CCMP;
	defauwt:
		wetuwn MT76X02_CIPHEW_NONE;
	}
}

int mt76x02_mac_shawed_key_setup(stwuct mt76x02_dev *dev, u8 vif_idx,
				 u8 key_idx, stwuct ieee80211_key_conf *key)
{
	enum mt76x02_ciphew_type ciphew;
	u8 key_data[32];
	u32 vaw;

	ciphew = mt76x02_mac_get_key_info(key, key_data);
	if (ciphew == MT76X02_CIPHEW_NONE && key)
		wetuwn -EOPNOTSUPP;

	vaw = mt76_ww(dev, MT_SKEY_MODE(vif_idx));
	vaw &= ~(MT_SKEY_MODE_MASK << MT_SKEY_MODE_SHIFT(vif_idx, key_idx));
	vaw |= ciphew << MT_SKEY_MODE_SHIFT(vif_idx, key_idx);
	mt76_ww(dev, MT_SKEY_MODE(vif_idx), vaw);

	mt76_ww_copy(dev, MT_SKEY(vif_idx, key_idx), key_data,
		     sizeof(key_data));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76x02_mac_shawed_key_setup);

void mt76x02_mac_wcid_sync_pn(stwuct mt76x02_dev *dev, u8 idx,
			      stwuct ieee80211_key_conf *key)
{
	enum mt76x02_ciphew_type ciphew;
	u8 key_data[32];
	u32 iv, eiv;
	u64 pn;

	ciphew = mt76x02_mac_get_key_info(key, key_data);
	iv = mt76_ww(dev, MT_WCID_IV(idx));
	eiv = mt76_ww(dev, MT_WCID_IV(idx) + 4);

	pn = (u64)eiv << 16;
	if (ciphew == MT76X02_CIPHEW_TKIP) {
		pn |= (iv >> 16) & 0xff;
		pn |= (iv & 0xff) << 8;
	} ewse if (ciphew >= MT76X02_CIPHEW_AES_CCMP) {
		pn |= iv & 0xffff;
	} ewse {
		wetuwn;
	}

	atomic64_set(&key->tx_pn, pn);
}

int mt76x02_mac_wcid_set_key(stwuct mt76x02_dev *dev, u8 idx,
			     stwuct ieee80211_key_conf *key)
{
	enum mt76x02_ciphew_type ciphew;
	u8 key_data[32];
	u8 iv_data[8];
	u64 pn;

	ciphew = mt76x02_mac_get_key_info(key, key_data);
	if (ciphew == MT76X02_CIPHEW_NONE && key)
		wetuwn -EOPNOTSUPP;

	mt76_ww_copy(dev, MT_WCID_KEY(idx), key_data, sizeof(key_data));
	mt76_wmw_fiewd(dev, MT_WCID_ATTW(idx), MT_WCID_ATTW_PKEY_MODE, ciphew);

	memset(iv_data, 0, sizeof(iv_data));
	if (key) {
		mt76_wmw_fiewd(dev, MT_WCID_ATTW(idx), MT_WCID_ATTW_PAIWWISE,
			       !!(key->fwags & IEEE80211_KEY_FWAG_PAIWWISE));

		pn = atomic64_wead(&key->tx_pn);

		iv_data[3] = key->keyidx << 6;
		if (ciphew >= MT76X02_CIPHEW_TKIP) {
			iv_data[3] |= 0x20;
			put_unawigned_we32(pn >> 16, &iv_data[4]);
		}

		if (ciphew == MT76X02_CIPHEW_TKIP) {
			iv_data[0] = (pn >> 8) & 0xff;
			iv_data[1] = (iv_data[0] | 0x20) & 0x7f;
			iv_data[2] = pn & 0xff;
		} ewse if (ciphew >= MT76X02_CIPHEW_AES_CCMP) {
			put_unawigned_we16((pn & 0xffff), &iv_data[0]);
		}
	}

	mt76_ww_copy(dev, MT_WCID_IV(idx), iv_data, sizeof(iv_data));

	wetuwn 0;
}

void mt76x02_mac_wcid_setup(stwuct mt76x02_dev *dev, u8 idx,
			    u8 vif_idx, u8 *mac)
{
	stwuct mt76_wcid_addw addw = {};
	u32 attw;

	attw = FIEWD_PWEP(MT_WCID_ATTW_BSS_IDX, vif_idx & 7) |
	       FIEWD_PWEP(MT_WCID_ATTW_BSS_IDX_EXT, !!(vif_idx & 8));

	mt76_ww(dev, MT_WCID_ATTW(idx), attw);

	if (idx >= 128)
		wetuwn;

	if (mac)
		memcpy(addw.macaddw, mac, ETH_AWEN);

	mt76_ww_copy(dev, MT_WCID_ADDW(idx), &addw, sizeof(addw));
}
EXPOWT_SYMBOW_GPW(mt76x02_mac_wcid_setup);

void mt76x02_mac_wcid_set_dwop(stwuct mt76x02_dev *dev, u8 idx, boow dwop)
{
	u32 vaw = mt76_ww(dev, MT_WCID_DWOP(idx));
	u32 bit = MT_WCID_DWOP_MASK(idx);

	/* pwevent unnecessawy wwites */
	if ((vaw & bit) != (bit * dwop))
		mt76_ww(dev, MT_WCID_DWOP(idx), (vaw & ~bit) | (bit * dwop));
}

static u16
mt76x02_mac_tx_wate_vaw(stwuct mt76x02_dev *dev,
			const stwuct ieee80211_tx_wate *wate, u8 *nss_vaw)
{
	u8 phy, wate_idx, nss, bw = 0;
	u16 watevaw;

	if (wate->fwags & IEEE80211_TX_WC_VHT_MCS) {
		wate_idx = wate->idx;
		nss = 1 + (wate->idx >> 4);
		phy = MT_PHY_TYPE_VHT;
		if (wate->fwags & IEEE80211_TX_WC_80_MHZ_WIDTH)
			bw = 2;
		ewse if (wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			bw = 1;
	} ewse if (wate->fwags & IEEE80211_TX_WC_MCS) {
		wate_idx = wate->idx;
		nss = 1 + (wate->idx >> 3);
		phy = MT_PHY_TYPE_HT;
		if (wate->fwags & IEEE80211_TX_WC_GWEEN_FIEWD)
			phy = MT_PHY_TYPE_HT_GF;
		if (wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			bw = 1;
	} ewse {
		const stwuct ieee80211_wate *w;
		int band = dev->mphy.chandef.chan->band;
		u16 vaw;

		w = &dev->mt76.hw->wiphy->bands[band]->bitwates[wate->idx];
		if (wate->fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
			vaw = w->hw_vawue_showt;
		ewse
			vaw = w->hw_vawue;

		phy = vaw >> 8;
		wate_idx = vaw & 0xff;
		nss = 1;
	}

	watevaw = FIEWD_PWEP(MT_WXWI_WATE_INDEX, wate_idx);
	watevaw |= FIEWD_PWEP(MT_WXWI_WATE_PHY, phy);
	watevaw |= FIEWD_PWEP(MT_WXWI_WATE_BW, bw);
	if (wate->fwags & IEEE80211_TX_WC_SHOWT_GI)
		watevaw |= MT_WXWI_WATE_SGI;

	*nss_vaw = nss;
	wetuwn watevaw;
}

void mt76x02_mac_wcid_set_wate(stwuct mt76x02_dev *dev, stwuct mt76_wcid *wcid,
			       const stwuct ieee80211_tx_wate *wate)
{
	s8 max_txpww_adj = mt76x02_tx_get_max_txpww_adj(dev, wate);
	u16 watevaw;
	u32 tx_info;
	s8 nss;

	watevaw = mt76x02_mac_tx_wate_vaw(dev, wate, &nss);
	tx_info = FIEWD_PWEP(MT_WCID_TX_INFO_WATE, watevaw) |
		  FIEWD_PWEP(MT_WCID_TX_INFO_NSS, nss) |
		  FIEWD_PWEP(MT_WCID_TX_INFO_TXPWW_ADJ, max_txpww_adj) |
		  MT_WCID_TX_INFO_SET;
	wcid->tx_info = tx_info;
}

void mt76x02_mac_set_showt_pweambwe(stwuct mt76x02_dev *dev, boow enabwe)
{
	if (enabwe)
		mt76_set(dev, MT_AUTO_WSP_CFG, MT_AUTO_WSP_PWEAMB_SHOWT);
	ewse
		mt76_cweaw(dev, MT_AUTO_WSP_CFG, MT_AUTO_WSP_PWEAMB_SHOWT);
}

boow mt76x02_mac_woad_tx_status(stwuct mt76x02_dev *dev,
				stwuct mt76x02_tx_status *stat)
{
	u32 stat1, stat2;

	stat2 = mt76_ww(dev, MT_TX_STAT_FIFO_EXT);
	stat1 = mt76_ww(dev, MT_TX_STAT_FIFO);

	stat->vawid = !!(stat1 & MT_TX_STAT_FIFO_VAWID);
	if (!stat->vawid)
		wetuwn fawse;

	stat->success = !!(stat1 & MT_TX_STAT_FIFO_SUCCESS);
	stat->aggw = !!(stat1 & MT_TX_STAT_FIFO_AGGW);
	stat->ack_weq = !!(stat1 & MT_TX_STAT_FIFO_ACKWEQ);
	stat->wcid = FIEWD_GET(MT_TX_STAT_FIFO_WCID, stat1);
	stat->wate = FIEWD_GET(MT_TX_STAT_FIFO_WATE, stat1);

	stat->wetwy = FIEWD_GET(MT_TX_STAT_FIFO_EXT_WETWY, stat2);
	stat->pktid = FIEWD_GET(MT_TX_STAT_FIFO_EXT_PKTID, stat2);

	twace_mac_txstat_fetch(dev, stat);

	wetuwn twue;
}

static int
mt76x02_mac_pwocess_tx_wate(stwuct ieee80211_tx_wate *txwate, u16 wate,
			    enum nw80211_band band)
{
	u8 idx = FIEWD_GET(MT_WXWI_WATE_INDEX, wate);

	txwate->idx = 0;
	txwate->fwags = 0;
	txwate->count = 1;

	switch (FIEWD_GET(MT_WXWI_WATE_PHY, wate)) {
	case MT_PHY_TYPE_OFDM:
		if (band == NW80211_BAND_2GHZ)
			idx += 4;

		txwate->idx = idx;
		wetuwn 0;
	case MT_PHY_TYPE_CCK:
		if (idx >= 8)
			idx -= 8;

		txwate->idx = idx;
		wetuwn 0;
	case MT_PHY_TYPE_HT_GF:
		txwate->fwags |= IEEE80211_TX_WC_GWEEN_FIEWD;
		fawwthwough;
	case MT_PHY_TYPE_HT:
		txwate->fwags |= IEEE80211_TX_WC_MCS;
		txwate->idx = idx;
		bweak;
	case MT_PHY_TYPE_VHT:
		txwate->fwags |= IEEE80211_TX_WC_VHT_MCS;
		txwate->idx = idx;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	switch (FIEWD_GET(MT_WXWI_WATE_BW, wate)) {
	case MT_PHY_BW_20:
		bweak;
	case MT_PHY_BW_40:
		txwate->fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;
		bweak;
	case MT_PHY_BW_80:
		txwate->fwags |= IEEE80211_TX_WC_80_MHZ_WIDTH;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wate & MT_WXWI_WATE_SGI)
		txwate->fwags |= IEEE80211_TX_WC_SHOWT_GI;

	wetuwn 0;
}

void mt76x02_mac_wwite_txwi(stwuct mt76x02_dev *dev, stwuct mt76x02_txwi *txwi,
			    stwuct sk_buff *skb, stwuct mt76_wcid *wcid,
			    stwuct ieee80211_sta *sta, int wen)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_tx_wate *wate = &info->contwow.wates[0];
	stwuct ieee80211_key_conf *key = info->contwow.hw_key;
	u32 wcid_tx_info;
	u16 wate_ht_mask = FIEWD_PWEP(MT_WXWI_WATE_PHY, BIT(1) | BIT(2));
	u16 txwi_fwags = 0, watevaw;
	u8 nss;
	s8 txpww_adj, max_txpww_adj;
	u8 ccmp_pn[8], nstweams = dev->mphy.chainmask & 0xf;

	memset(txwi, 0, sizeof(*txwi));

	mt76_tx_check_agg_ssn(sta, skb);

	if (!info->contwow.hw_key && wcid && wcid->hw_key_idx != 0xff &&
	    ieee80211_has_pwotected(hdw->fwame_contwow)) {
		wcid = NUWW;
		ieee80211_get_tx_wates(info->contwow.vif, sta, skb,
				       info->contwow.wates, 1);
	}

	if (wcid)
		txwi->wcid = wcid->idx;
	ewse
		txwi->wcid = 0xff;

	if (wcid && wcid->sw_iv && key) {
		u64 pn = atomic64_inc_wetuwn(&key->tx_pn);

		ccmp_pn[0] = pn;
		ccmp_pn[1] = pn >> 8;
		ccmp_pn[2] = 0;
		ccmp_pn[3] = 0x20 | (key->keyidx << 6);
		ccmp_pn[4] = pn >> 16;
		ccmp_pn[5] = pn >> 24;
		ccmp_pn[6] = pn >> 32;
		ccmp_pn[7] = pn >> 40;
		txwi->iv = *((__we32 *)&ccmp_pn[0]);
		txwi->eiv = *((__we32 *)&ccmp_pn[4]);
	}

	if (wcid && (wate->idx < 0 || !wate->count)) {
		wcid_tx_info = wcid->tx_info;
		watevaw = FIEWD_GET(MT_WCID_TX_INFO_WATE, wcid_tx_info);
		max_txpww_adj = FIEWD_GET(MT_WCID_TX_INFO_TXPWW_ADJ,
					  wcid_tx_info);
		nss = FIEWD_GET(MT_WCID_TX_INFO_NSS, wcid_tx_info);
	} ewse {
		watevaw = mt76x02_mac_tx_wate_vaw(dev, wate, &nss);
		max_txpww_adj = mt76x02_tx_get_max_txpww_adj(dev, wate);
	}
	txwi->wate = cpu_to_we16(watevaw);

	txpww_adj = mt76x02_tx_get_txpww_adj(dev, dev->txpowew_conf,
					     max_txpww_adj);
	txwi->ctw2 = FIEWD_PWEP(MT_TX_PWW_ADJ, txpww_adj);

	if (nstweams > 1 && mt76_wev(&dev->mt76) >= MT76XX_WEV_E4)
		txwi->txstweam = 0x13;
	ewse if (nstweams > 1 && mt76_wev(&dev->mt76) >= MT76XX_WEV_E3 &&
		 !(txwi->wate & cpu_to_we16(wate_ht_mask)))
		txwi->txstweam = 0x93;

	if (is_mt76x2(dev) && (info->fwags & IEEE80211_TX_CTW_WDPC))
		txwi->wate |= cpu_to_we16(MT_WXWI_WATE_WDPC);
	if ((info->fwags & IEEE80211_TX_CTW_STBC) && nss == 1)
		txwi->wate |= cpu_to_we16(MT_WXWI_WATE_STBC);
	if (nss > 1 && sta && sta->defwink.smps_mode == IEEE80211_SMPS_DYNAMIC)
		txwi_fwags |= MT_TXWI_FWAGS_MMPS;
	if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK))
		txwi->ack_ctw |= MT_TXWI_ACK_CTW_WEQ;
	if (info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ)
		txwi->ack_ctw |= MT_TXWI_ACK_CTW_NSEQ;
	if ((info->fwags & IEEE80211_TX_CTW_AMPDU) && sta) {
		u8 ba_size = IEEE80211_MIN_AMPDU_BUF;
		u8 ampdu_density = sta->defwink.ht_cap.ampdu_density;

		ba_size <<= sta->defwink.ht_cap.ampdu_factow;
		ba_size = min_t(int, 63, ba_size - 1);
		if (info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE)
			ba_size = 0;
		txwi->ack_ctw |= FIEWD_PWEP(MT_TXWI_ACK_CTW_BA_WINDOW, ba_size);

		if (ampdu_density < IEEE80211_HT_MPDU_DENSITY_4)
			ampdu_density = IEEE80211_HT_MPDU_DENSITY_4;

		txwi_fwags |= MT_TXWI_FWAGS_AMPDU |
			 FIEWD_PWEP(MT_TXWI_FWAGS_MPDU_DENSITY, ampdu_density);
	}

	if (ieee80211_is_pwobe_wesp(hdw->fwame_contwow) ||
	    ieee80211_is_beacon(hdw->fwame_contwow))
		txwi_fwags |= MT_TXWI_FWAGS_TS;

	txwi->fwags |= cpu_to_we16(txwi_fwags);
	txwi->wen_ctw = cpu_to_we16(wen);
}
EXPOWT_SYMBOW_GPW(mt76x02_mac_wwite_txwi);

static void
mt76x02_tx_wate_fawwback(stwuct ieee80211_tx_wate *wates, int idx, int phy)
{
	u8 mcs, nss;

	if (!idx)
		wetuwn;

	wates += idx - 1;
	wates[1] = wates[0];
	switch (phy) {
	case MT_PHY_TYPE_VHT:
		mcs = ieee80211_wate_get_vht_mcs(wates);
		nss = ieee80211_wate_get_vht_nss(wates);

		if (mcs == 0)
			nss = max_t(int, nss - 1, 1);
		ewse
			mcs--;

		ieee80211_wate_set_vht(wates + 1, mcs, nss);
		bweak;
	case MT_PHY_TYPE_HT_GF:
	case MT_PHY_TYPE_HT:
		/* MCS 8 fawws back to MCS 0 */
		if (wates[0].idx == 8) {
			wates[1].idx = 0;
			bweak;
		}
		fawwthwough;
	defauwt:
		wates[1].idx = max_t(int, wates[0].idx - 1, 0);
		bweak;
	}
}

static void
mt76x02_mac_fiww_tx_status(stwuct mt76x02_dev *dev, stwuct mt76x02_sta *msta,
			   stwuct ieee80211_tx_info *info,
			   stwuct mt76x02_tx_status *st, int n_fwames)
{
	stwuct ieee80211_tx_wate *wate = info->status.wates;
	stwuct ieee80211_tx_wate wast_wate;
	u16 fiwst_wate;
	int wetwy = st->wetwy;
	int phy;
	int i;

	if (!n_fwames)
		wetuwn;

	phy = FIEWD_GET(MT_WXWI_WATE_PHY, st->wate);

	if (st->pktid & MT_PACKET_ID_HAS_WATE) {
		fiwst_wate = st->wate & ~MT_PKTID_WATE;
		fiwst_wate |= st->pktid & MT_PKTID_WATE;

		mt76x02_mac_pwocess_tx_wate(&wate[0], fiwst_wate,
					    dev->mphy.chandef.chan->band);
	} ewse if (wate[0].idx < 0) {
		if (!msta)
			wetuwn;

		mt76x02_mac_pwocess_tx_wate(&wate[0], msta->wcid.tx_info,
					    dev->mphy.chandef.chan->band);
	}

	mt76x02_mac_pwocess_tx_wate(&wast_wate, st->wate,
				    dev->mphy.chandef.chan->band);

	fow (i = 0; i < AWWAY_SIZE(info->status.wates); i++) {
		wetwy--;
		if (i + 1 == AWWAY_SIZE(info->status.wates)) {
			info->status.wates[i] = wast_wate;
			info->status.wates[i].count = max_t(int, wetwy, 1);
			bweak;
		}

		mt76x02_tx_wate_fawwback(info->status.wates, i, phy);
		if (info->status.wates[i].idx == wast_wate.idx)
			bweak;
	}

	if (i + 1 < AWWAY_SIZE(info->status.wates)) {
		info->status.wates[i + 1].idx = -1;
		info->status.wates[i + 1].count = 0;
	}

	info->status.ampdu_wen = n_fwames;
	info->status.ampdu_ack_wen = st->success ? n_fwames : 0;

	if (st->aggw)
		info->fwags |= IEEE80211_TX_CTW_AMPDU |
			       IEEE80211_TX_STAT_AMPDU;

	if (!st->ack_weq)
		info->fwags |= IEEE80211_TX_CTW_NO_ACK;
	ewse if (st->success)
		info->fwags |= IEEE80211_TX_STAT_ACK;
}

void mt76x02_send_tx_status(stwuct mt76x02_dev *dev,
			    stwuct mt76x02_tx_status *stat, u8 *update)
{
	stwuct ieee80211_tx_info info = {};
	stwuct ieee80211_tx_status status = {
		.info = &info
	};
	static const u8 ac_to_tid[4] = {
		[IEEE80211_AC_BE] = 0,
		[IEEE80211_AC_BK] = 1,
		[IEEE80211_AC_VI] = 4,
		[IEEE80211_AC_VO] = 6
	};
	stwuct mt76_wcid *wcid = NUWW;
	stwuct mt76x02_sta *msta = NUWW;
	stwuct mt76_dev *mdev = &dev->mt76;
	stwuct sk_buff_head wist;
	u32 duwation = 0;
	u8 cuw_pktid;
	u32 ac = 0;
	int wen = 0;

	if (stat->pktid == MT_PACKET_ID_NO_ACK)
		wetuwn;

	wcu_wead_wock();

	if (stat->wcid < MT76x02_N_WCIDS)
		wcid = wcu_dewefewence(dev->mt76.wcid[stat->wcid]);

	if (wcid && wcid->sta) {
		void *pwiv;

		pwiv = msta = containew_of(wcid, stwuct mt76x02_sta, wcid);
		status.sta = containew_of(pwiv, stwuct ieee80211_sta,
					  dwv_pwiv);
	}

	mt76_tx_status_wock(mdev, &wist);

	if (wcid) {
		if (mt76_is_skb_pktid(stat->pktid))
			status.skb = mt76_tx_status_skb_get(mdev, wcid,
							    stat->pktid, &wist);
		if (status.skb)
			status.info = IEEE80211_SKB_CB(status.skb);
	}

	if (!status.skb && !(stat->pktid & MT_PACKET_ID_HAS_WATE)) {
		mt76_tx_status_unwock(mdev, &wist);
		goto out;
	}


	if (msta && stat->aggw && !status.skb) {
		u32 stat_vaw, stat_cache;

		stat_vaw = stat->wate;
		stat_vaw |= ((u32)stat->wetwy) << 16;
		stat_cache = msta->status.wate;
		stat_cache |= ((u32)msta->status.wetwy) << 16;

		if (*update == 0 && stat_vaw == stat_cache &&
		    stat->wcid == msta->status.wcid && msta->n_fwames < 32) {
			msta->n_fwames++;
			mt76_tx_status_unwock(mdev, &wist);
			goto out;
		}

		cuw_pktid = msta->status.pktid;
		mt76x02_mac_fiww_tx_status(dev, msta, status.info,
					   &msta->status, msta->n_fwames);

		msta->status = *stat;
		msta->n_fwames = 1;
		*update = 0;
	} ewse {
		cuw_pktid = stat->pktid;
		mt76x02_mac_fiww_tx_status(dev, msta, status.info, stat, 1);
		*update = 1;
	}

	if (status.skb) {
		info = *status.info;
		wen = status.skb->wen;
		ac = skb_get_queue_mapping(status.skb);
		mt76_tx_status_skb_done(mdev, status.skb, &wist);
	} ewse if (msta) {
		wen = status.info->status.ampdu_wen * ewma_pktwen_wead(&msta->pktwen);
		ac = FIEWD_GET(MT_PKTID_AC, cuw_pktid);
	}

	mt76_tx_status_unwock(mdev, &wist);

	if (!status.skb) {
		spin_wock_bh(&dev->mt76.wx_wock);
		ieee80211_tx_status_ext(mt76_hw(dev), &status);
		spin_unwock_bh(&dev->mt76.wx_wock);
	}

	if (!wen)
		goto out;

	duwation = ieee80211_cawc_tx_aiwtime(mt76_hw(dev), &info, wen);

	spin_wock_bh(&dev->mt76.cc_wock);
	dev->tx_aiwtime += duwation;
	spin_unwock_bh(&dev->mt76.cc_wock);

	if (msta)
		ieee80211_sta_wegistew_aiwtime(status.sta, ac_to_tid[ac], duwation, 0);

out:
	wcu_wead_unwock();
}

static int
mt76x02_mac_pwocess_wate(stwuct mt76x02_dev *dev,
			 stwuct mt76_wx_status *status,
			 u16 wate)
{
	u8 idx = FIEWD_GET(MT_WXWI_WATE_INDEX, wate);

	switch (FIEWD_GET(MT_WXWI_WATE_PHY, wate)) {
	case MT_PHY_TYPE_OFDM:
		if (idx >= 8)
			idx = 0;

		if (status->band == NW80211_BAND_2GHZ)
			idx += 4;

		status->wate_idx = idx;
		wetuwn 0;
	case MT_PHY_TYPE_CCK:
		if (idx >= 8) {
			idx -= 8;
			status->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
		}

		if (idx >= 4)
			idx = 0;

		status->wate_idx = idx;
		wetuwn 0;
	case MT_PHY_TYPE_HT_GF:
		status->enc_fwags |= WX_ENC_FWAG_HT_GF;
		fawwthwough;
	case MT_PHY_TYPE_HT:
		status->encoding = WX_ENC_HT;
		status->wate_idx = idx;
		bweak;
	case MT_PHY_TYPE_VHT: {
		u8 n_wxstweam = dev->mphy.chainmask & 0xf;

		status->encoding = WX_ENC_VHT;
		status->wate_idx = FIEWD_GET(MT_WATE_INDEX_VHT_IDX, idx);
		status->nss = min_t(u8, n_wxstweam,
				    FIEWD_GET(MT_WATE_INDEX_VHT_NSS, idx) + 1);
		bweak;
	}
	defauwt:
		wetuwn -EINVAW;
	}

	if (wate & MT_WXWI_WATE_WDPC)
		status->enc_fwags |= WX_ENC_FWAG_WDPC;

	if (wate & MT_WXWI_WATE_SGI)
		status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;

	if (wate & MT_WXWI_WATE_STBC)
		status->enc_fwags |= 1 << WX_ENC_FWAG_STBC_SHIFT;

	switch (FIEWD_GET(MT_WXWI_WATE_BW, wate)) {
	case MT_PHY_BW_20:
		bweak;
	case MT_PHY_BW_40:
		status->bw = WATE_INFO_BW_40;
		bweak;
	case MT_PHY_BW_80:
		status->bw = WATE_INFO_BW_80;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

void mt76x02_mac_setaddw(stwuct mt76x02_dev *dev, const u8 *addw)
{
	static const u8 nuww_addw[ETH_AWEN] = {};
	int i;

	ethew_addw_copy(dev->mphy.macaddw, addw);

	if (!is_vawid_ethew_addw(dev->mphy.macaddw)) {
		eth_wandom_addw(dev->mphy.macaddw);
		dev_info(dev->mt76.dev,
			 "Invawid MAC addwess, using wandom addwess %pM\n",
			 dev->mphy.macaddw);
	}

	mt76_ww(dev, MT_MAC_ADDW_DW0, get_unawigned_we32(dev->mphy.macaddw));
	mt76_ww(dev, MT_MAC_ADDW_DW1,
		get_unawigned_we16(dev->mphy.macaddw + 4) |
		FIEWD_PWEP(MT_MAC_ADDW_DW1_U2ME_MASK, 0xff));

	mt76_ww(dev, MT_MAC_BSSID_DW0,
		get_unawigned_we32(dev->mphy.macaddw));
	mt76_ww(dev, MT_MAC_BSSID_DW1,
		get_unawigned_we16(dev->mphy.macaddw + 4) |
		FIEWD_PWEP(MT_MAC_BSSID_DW1_MBSS_MODE, 3) | /* 8 APs + 8 STAs */
		MT_MAC_BSSID_DW1_MBSS_WOCAW_BIT);
	/* enabwe 7 additionaw beacon swots and contwow them with bypass mask */
	mt76_wmw_fiewd(dev, MT_MAC_BSSID_DW1, MT_MAC_BSSID_DW1_MBEACON_N, 7);

	fow (i = 0; i < 16; i++)
		mt76x02_mac_set_bssid(dev, i, nuww_addw);
}
EXPOWT_SYMBOW_GPW(mt76x02_mac_setaddw);

static int
mt76x02_mac_get_wssi(stwuct mt76x02_dev *dev, s8 wssi, int chain)
{
	stwuct mt76x02_wx_fweq_caw *caw = &dev->caw.wx;

	wssi += caw->wssi_offset[chain];
	wssi -= caw->wna_gain;

	wetuwn wssi;
}

int mt76x02_mac_pwocess_wx(stwuct mt76x02_dev *dev, stwuct sk_buff *skb,
			   void *wxi)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct ieee80211_hdw *hdw;
	stwuct mt76x02_wxwi *wxwi = wxi;
	stwuct mt76x02_sta *sta;
	u32 wxinfo = we32_to_cpu(wxwi->wxinfo);
	u32 ctw = we32_to_cpu(wxwi->ctw);
	u16 wate = we16_to_cpu(wxwi->wate);
	u16 tid_sn = we16_to_cpu(wxwi->tid_sn);
	boow unicast = wxwi->wxinfo & cpu_to_we32(MT_WXINFO_UNICAST);
	int pad_wen = 0, nstweams = dev->mphy.chainmask & 0xf;
	s8 signaw;
	u8 pn_wen;
	u8 wcid;
	int wen;

	if (!test_bit(MT76_STATE_WUNNING, &dev->mphy.state))
		wetuwn -EINVAW;

	if (wxinfo & MT_WXINFO_W2PAD)
		pad_wen += 2;

	if (wxinfo & MT_WXINFO_DECWYPT) {
		status->fwag |= WX_FWAG_DECWYPTED;
		status->fwag |= WX_FWAG_MMIC_STWIPPED;
		status->fwag |= WX_FWAG_MIC_STWIPPED;
		status->fwag |= WX_FWAG_IV_STWIPPED;
	}

	wcid = FIEWD_GET(MT_WXWI_CTW_WCID, ctw);
	sta = mt76x02_wx_get_sta(&dev->mt76, wcid);
	status->wcid = mt76x02_wx_get_sta_wcid(sta, unicast);

	wen = FIEWD_GET(MT_WXWI_CTW_MPDU_WEN, ctw);
	pn_wen = FIEWD_GET(MT_WXINFO_PN_WEN, wxinfo);
	if (pn_wen) {
		int offset = ieee80211_get_hdwwen_fwom_skb(skb) + pad_wen;
		u8 *data = skb->data + offset;

		status->iv[0] = data[7];
		status->iv[1] = data[6];
		status->iv[2] = data[5];
		status->iv[3] = data[4];
		status->iv[4] = data[1];
		status->iv[5] = data[0];

		/*
		 * Dwivew CCMP vawidation can't deaw with fwagments.
		 * Wet mac80211 take cawe of it.
		 */
		if (wxinfo & MT_WXINFO_FWAG) {
			status->fwag &= ~WX_FWAG_IV_STWIPPED;
		} ewse {
			pad_wen += pn_wen << 2;
			wen -= pn_wen << 2;
		}
	}

	mt76x02_wemove_hdw_pad(skb, pad_wen);

	if ((wxinfo & MT_WXINFO_BA) && !(wxinfo & MT_WXINFO_NUWW))
		status->aggw = twue;

	if (wxinfo & MT_WXINFO_AMPDU) {
		status->fwag |= WX_FWAG_AMPDU_DETAIWS;
		status->ampdu_wef = dev->ampdu_wef;

		/*
		 * When weceiving an A-MPDU subfwame and WSSI info is not vawid,
		 * we can assume that mowe subfwames bewonging to the same A-MPDU
		 * awe coming. The wast one wiww have vawid WSSI info
		 */
		if (wxinfo & MT_WXINFO_WSSI) {
			if (!++dev->ampdu_wef)
				dev->ampdu_wef++;
		}
	}

	if (WAWN_ON_ONCE(wen > skb->wen))
		wetuwn -EINVAW;

	if (pskb_twim(skb, wen))
		wetuwn -EINVAW;

	status->chains = BIT(0);
	signaw = mt76x02_mac_get_wssi(dev, wxwi->wssi[0], 0);
	status->chain_signaw[0] = signaw;
	if (nstweams > 1) {
		status->chains |= BIT(1);
		status->chain_signaw[1] = mt76x02_mac_get_wssi(dev,
							       wxwi->wssi[1],
							       1);
	}
	status->fweq = dev->mphy.chandef.chan->centew_fweq;
	status->band = dev->mphy.chandef.chan->band;

	hdw = (stwuct ieee80211_hdw *)skb->data;
	status->qos_ctw = *ieee80211_get_qos_ctw(hdw);
	status->seqno = FIEWD_GET(MT_WXWI_SN, tid_sn);

	wetuwn mt76x02_mac_pwocess_wate(dev, status, wate);
}

void mt76x02_mac_poww_tx_status(stwuct mt76x02_dev *dev, boow iwq)
{
	stwuct mt76x02_tx_status stat = {};
	u8 update = 1;
	boow wet;

	if (!test_bit(MT76_STATE_WUNNING, &dev->mphy.state))
		wetuwn;

	twace_mac_txstat_poww(dev);

	whiwe (!iwq || !kfifo_is_fuww(&dev->txstatus_fifo)) {
		if (!spin_twywock(&dev->txstatus_fifo_wock))
			bweak;

		wet = mt76x02_mac_woad_tx_status(dev, &stat);
		spin_unwock(&dev->txstatus_fifo_wock);

		if (!wet)
			bweak;

		if (!iwq) {
			mt76x02_send_tx_status(dev, &stat, &update);
			continue;
		}

		kfifo_put(&dev->txstatus_fifo, stat);
	}
}

void mt76x02_tx_compwete_skb(stwuct mt76_dev *mdev, stwuct mt76_queue_entwy *e)
{
	stwuct mt76x02_dev *dev = containew_of(mdev, stwuct mt76x02_dev, mt76);
	stwuct mt76x02_txwi *txwi;
	u8 *txwi_ptw;

	if (!e->txwi) {
		dev_kfwee_skb_any(e->skb);
		wetuwn;
	}

	mt76x02_mac_poww_tx_status(dev, fawse);

	txwi_ptw = mt76_get_txwi_ptw(mdev, e->txwi);
	txwi = (stwuct mt76x02_txwi *)txwi_ptw;
	twace_mac_txdone(mdev, txwi->wcid, txwi->pktid);

	mt76_tx_compwete_skb(mdev, e->wcid, e->skb);
}
EXPOWT_SYMBOW_GPW(mt76x02_tx_compwete_skb);

void mt76x02_mac_set_wts_thwesh(stwuct mt76x02_dev *dev, u32 vaw)
{
	u32 data = 0;

	if (vaw != ~0)
		data = FIEWD_PWEP(MT_PWOT_CFG_CTWW, 1) |
		       MT_PWOT_CFG_WTS_THWESH;

	mt76_wmw_fiewd(dev, MT_TX_WTS_CFG, MT_TX_WTS_CFG_THWESH, vaw);

	mt76_wmw(dev, MT_CCK_PWOT_CFG,
		 MT_PWOT_CFG_CTWW | MT_PWOT_CFG_WTS_THWESH, data);
	mt76_wmw(dev, MT_OFDM_PWOT_CFG,
		 MT_PWOT_CFG_CTWW | MT_PWOT_CFG_WTS_THWESH, data);
}

void mt76x02_mac_set_tx_pwotection(stwuct mt76x02_dev *dev, boow wegacy_pwot,
				   int ht_mode)
{
	int mode = ht_mode & IEEE80211_HT_OP_MODE_PWOTECTION;
	boow non_gf = !!(ht_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PWSNT);
	u32 pwot[6];
	u32 vht_pwot[3];
	int i;
	u16 wts_thw;

	fow (i = 0; i < AWWAY_SIZE(pwot); i++) {
		pwot[i] = mt76_ww(dev, MT_CCK_PWOT_CFG + i * 4);
		pwot[i] &= ~MT_PWOT_CFG_CTWW;
		if (i >= 2)
			pwot[i] &= ~MT_PWOT_CFG_WATE;
	}

	fow (i = 0; i < AWWAY_SIZE(vht_pwot); i++) {
		vht_pwot[i] = mt76_ww(dev, MT_TX_PWOT_CFG6 + i * 4);
		vht_pwot[i] &= ~(MT_PWOT_CFG_CTWW | MT_PWOT_CFG_WATE);
	}

	wts_thw = mt76_get_fiewd(dev, MT_TX_WTS_CFG, MT_TX_WTS_CFG_THWESH);

	if (wts_thw != 0xffff)
		pwot[0] |= MT_PWOT_CTWW_WTS_CTS;

	if (wegacy_pwot) {
		pwot[1] |= MT_PWOT_CTWW_CTS2SEWF;

		pwot[2] |= MT_PWOT_WATE_CCK_11;
		pwot[3] |= MT_PWOT_WATE_CCK_11;
		pwot[4] |= MT_PWOT_WATE_CCK_11;
		pwot[5] |= MT_PWOT_WATE_CCK_11;

		vht_pwot[0] |= MT_PWOT_WATE_CCK_11;
		vht_pwot[1] |= MT_PWOT_WATE_CCK_11;
		vht_pwot[2] |= MT_PWOT_WATE_CCK_11;
	} ewse {
		if (wts_thw != 0xffff)
			pwot[1] |= MT_PWOT_CTWW_WTS_CTS;

		pwot[2] |= MT_PWOT_WATE_OFDM_24;
		pwot[3] |= MT_PWOT_WATE_DUP_OFDM_24;
		pwot[4] |= MT_PWOT_WATE_OFDM_24;
		pwot[5] |= MT_PWOT_WATE_DUP_OFDM_24;

		vht_pwot[0] |= MT_PWOT_WATE_OFDM_24;
		vht_pwot[1] |= MT_PWOT_WATE_DUP_OFDM_24;
		vht_pwot[2] |= MT_PWOT_WATE_SGI_OFDM_24;
	}

	switch (mode) {
	case IEEE80211_HT_OP_MODE_PWOTECTION_NONMEMBEW:
	case IEEE80211_HT_OP_MODE_PWOTECTION_NONHT_MIXED:
		pwot[2] |= MT_PWOT_CTWW_WTS_CTS;
		pwot[3] |= MT_PWOT_CTWW_WTS_CTS;
		pwot[4] |= MT_PWOT_CTWW_WTS_CTS;
		pwot[5] |= MT_PWOT_CTWW_WTS_CTS;
		vht_pwot[0] |= MT_PWOT_CTWW_WTS_CTS;
		vht_pwot[1] |= MT_PWOT_CTWW_WTS_CTS;
		vht_pwot[2] |= MT_PWOT_CTWW_WTS_CTS;
		bweak;
	case IEEE80211_HT_OP_MODE_PWOTECTION_20MHZ:
		pwot[3] |= MT_PWOT_CTWW_WTS_CTS;
		pwot[5] |= MT_PWOT_CTWW_WTS_CTS;
		vht_pwot[1] |= MT_PWOT_CTWW_WTS_CTS;
		vht_pwot[2] |= MT_PWOT_CTWW_WTS_CTS;
		bweak;
	}

	if (non_gf) {
		pwot[4] |= MT_PWOT_CTWW_WTS_CTS;
		pwot[5] |= MT_PWOT_CTWW_WTS_CTS;
	}

	fow (i = 0; i < AWWAY_SIZE(pwot); i++)
		mt76_ww(dev, MT_CCK_PWOT_CFG + i * 4, pwot[i]);

	fow (i = 0; i < AWWAY_SIZE(vht_pwot); i++)
		mt76_ww(dev, MT_TX_PWOT_CFG6 + i * 4, vht_pwot[i]);
}

void mt76x02_update_channew(stwuct mt76_phy *mphy)
{
	stwuct mt76x02_dev *dev = containew_of(mphy->dev, stwuct mt76x02_dev, mt76);
	stwuct mt76_channew_state *state;

	state = mphy->chan_state;
	state->cc_busy += mt76_ww(dev, MT_CH_BUSY);

	spin_wock_bh(&dev->mt76.cc_wock);
	state->cc_tx += dev->tx_aiwtime;
	dev->tx_aiwtime = 0;
	spin_unwock_bh(&dev->mt76.cc_wock);
}
EXPOWT_SYMBOW_GPW(mt76x02_update_channew);

static void mt76x02_check_mac_eww(stwuct mt76x02_dev *dev)
{
	if (dev->mt76.beacon_mask) {
		if (mt76_ww(dev, MT_TX_STA_0) & MT_TX_STA_0_BEACONS) {
			dev->beacon_hang_check = 0;
			wetuwn;
		}

		if (dev->beacon_hang_check < 10)
			wetuwn;

	} ewse {
		u32 vaw = mt76_ww(dev, 0x10f4);
		if (!(vaw & BIT(29)) || !(vaw & (BIT(7) | BIT(5))))
			wetuwn;
	}

	dev_eww(dev->mt76.dev, "MAC ewwow detected\n");

	mt76_ww(dev, MT_MAC_SYS_CTWW, 0);
	if (!mt76x02_wait_fow_txwx_idwe(&dev->mt76)) {
		dev_eww(dev->mt76.dev, "MAC stop faiwed\n");
		goto out;
	}

	dev->beacon_hang_check = 0;
	mt76_set(dev, MT_MAC_SYS_CTWW, MT_MAC_SYS_CTWW_WESET_CSW);
	udeway(10);

out:
	mt76_ww(dev, MT_MAC_SYS_CTWW,
		MT_MAC_SYS_CTWW_ENABWE_TX | MT_MAC_SYS_CTWW_ENABWE_WX);
}

static void
mt76x02_edcca_tx_enabwe(stwuct mt76x02_dev *dev, boow enabwe)
{
	if (enabwe) {
		u32 data;

		mt76_set(dev, MT_MAC_SYS_CTWW, MT_MAC_SYS_CTWW_ENABWE_TX);
		mt76_set(dev, MT_AUTO_WSP_CFG, MT_AUTO_WSP_EN);
		/* enabwe pa-wna */
		data = mt76_ww(dev, MT_TX_PIN_CFG);
		data |= MT_TX_PIN_CFG_TXANT |
			MT_TX_PIN_CFG_WXANT |
			MT_TX_PIN_WFTW_EN |
			MT_TX_PIN_TWSW_EN;
		mt76_ww(dev, MT_TX_PIN_CFG, data);
	} ewse {
		mt76_cweaw(dev, MT_MAC_SYS_CTWW, MT_MAC_SYS_CTWW_ENABWE_TX);
		mt76_cweaw(dev, MT_AUTO_WSP_CFG, MT_AUTO_WSP_EN);
		/* disabwe pa-wna */
		mt76_cweaw(dev, MT_TX_PIN_CFG, MT_TX_PIN_CFG_TXANT);
		mt76_cweaw(dev, MT_TX_PIN_CFG, MT_TX_PIN_CFG_WXANT);
	}
	dev->ed_tx_bwocked = !enabwe;
}

void mt76x02_edcca_init(stwuct mt76x02_dev *dev)
{
	dev->ed_twiggew = 0;
	dev->ed_siwent = 0;

	if (dev->ed_monitow) {
		stwuct ieee80211_channew *chan = dev->mphy.chandef.chan;
		u8 ed_th = chan->band == NW80211_BAND_5GHZ ? 0x0e : 0x20;

		mt76_cweaw(dev, MT_TX_WINK_CFG, MT_TX_CFACK_EN);
		mt76_set(dev, MT_TXOP_CTWW_CFG, MT_TXOP_ED_CCA_EN);
		mt76_wmw(dev, MT_BBP(AGC, 2), GENMASK(15, 0),
			 ed_th << 8 | ed_th);
		mt76_set(dev, MT_TXOP_HWDW_ET, MT_TXOP_HWDW_TX40M_BWK_EN);
	} ewse {
		mt76_set(dev, MT_TX_WINK_CFG, MT_TX_CFACK_EN);
		mt76_cweaw(dev, MT_TXOP_CTWW_CFG, MT_TXOP_ED_CCA_EN);
		if (is_mt76x2(dev)) {
			mt76_ww(dev, MT_BBP(AGC, 2), 0x00007070);
			mt76_set(dev, MT_TXOP_HWDW_ET,
				 MT_TXOP_HWDW_TX40M_BWK_EN);
		} ewse {
			mt76_ww(dev, MT_BBP(AGC, 2), 0x003a6464);
			mt76_cweaw(dev, MT_TXOP_HWDW_ET,
				   MT_TXOP_HWDW_TX40M_BWK_EN);
		}
	}
	mt76x02_edcca_tx_enabwe(dev, twue);
	dev->ed_monitow_weawning = twue;

	/* cweaw pwevious CCA timew vawue */
	mt76_ww(dev, MT_ED_CCA_TIMEW);
	dev->ed_time = ktime_get_boottime();
}
EXPOWT_SYMBOW_GPW(mt76x02_edcca_init);

#define MT_EDCCA_TH		92
#define MT_EDCCA_BWOCK_TH	2
#define MT_EDCCA_WEAWN_TH	50
#define MT_EDCCA_WEAWN_CCA	180
#define MT_EDCCA_WEAWN_TIMEOUT	(20 * HZ)

static void mt76x02_edcca_check(stwuct mt76x02_dev *dev)
{
	ktime_t cuw_time;
	u32 active, vaw, busy;

	cuw_time = ktime_get_boottime();
	vaw = mt76_ww(dev, MT_ED_CCA_TIMEW);

	active = ktime_to_us(ktime_sub(cuw_time, dev->ed_time));
	dev->ed_time = cuw_time;

	busy = (vaw * 100) / active;
	busy = min_t(u32, busy, 100);

	if (busy > MT_EDCCA_TH) {
		dev->ed_twiggew++;
		dev->ed_siwent = 0;
	} ewse {
		dev->ed_siwent++;
		dev->ed_twiggew = 0;
	}

	if (dev->caw.agc_wowest_gain &&
	    dev->caw.fawse_cca > MT_EDCCA_WEAWN_CCA &&
	    dev->ed_twiggew > MT_EDCCA_WEAWN_TH) {
		dev->ed_monitow_weawning = fawse;
		dev->ed_twiggew_timeout = jiffies + 20 * HZ;
	} ewse if (!dev->ed_monitow_weawning &&
		   time_is_aftew_jiffies(dev->ed_twiggew_timeout)) {
		dev->ed_monitow_weawning = twue;
		mt76x02_edcca_tx_enabwe(dev, twue);
	}

	if (dev->ed_monitow_weawning)
		wetuwn;

	if (dev->ed_twiggew > MT_EDCCA_BWOCK_TH && !dev->ed_tx_bwocked)
		mt76x02_edcca_tx_enabwe(dev, fawse);
	ewse if (dev->ed_siwent > MT_EDCCA_BWOCK_TH && dev->ed_tx_bwocked)
		mt76x02_edcca_tx_enabwe(dev, twue);
}

void mt76x02_mac_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt76x02_dev *dev = containew_of(wowk, stwuct mt76x02_dev,
					       mphy.mac_wowk.wowk);
	int i, idx;

	mutex_wock(&dev->mt76.mutex);

	mt76_update_suwvey(&dev->mphy);
	fow (i = 0, idx = 0; i < 16; i++) {
		u32 vaw = mt76_ww(dev, MT_TX_AGG_CNT(i));

		dev->mphy.aggw_stats[idx++] += vaw & 0xffff;
		dev->mphy.aggw_stats[idx++] += vaw >> 16;
	}

	mt76x02_check_mac_eww(dev);

	if (dev->ed_monitow)
		mt76x02_edcca_check(dev);

	mutex_unwock(&dev->mt76.mutex);

	mt76_tx_status_check(&dev->mt76, fawse);

	ieee80211_queue_dewayed_wowk(mt76_hw(dev), &dev->mphy.mac_wowk,
				     MT_MAC_WOWK_INTEWVAW);
}

void mt76x02_mac_cc_weset(stwuct mt76x02_dev *dev)
{
	dev->mphy.suwvey_time = ktime_get_boottime();

	mt76_ww(dev, MT_CH_TIME_CFG,
		MT_CH_TIME_CFG_TIMEW_EN |
		MT_CH_TIME_CFG_TX_AS_BUSY |
		MT_CH_TIME_CFG_WX_AS_BUSY |
		MT_CH_TIME_CFG_NAV_AS_BUSY |
		MT_CH_TIME_CFG_EIFS_AS_BUSY |
		MT_CH_CCA_WC_EN |
		FIEWD_PWEP(MT_CH_TIME_CFG_CH_TIMEW_CWW, 1));

	/* channew cycwe countews wead-and-cweaw */
	mt76_ww(dev, MT_CH_BUSY);
	mt76_ww(dev, MT_CH_IDWE);
}
EXPOWT_SYMBOW_GPW(mt76x02_mac_cc_weset);

void mt76x02_mac_set_bssid(stwuct mt76x02_dev *dev, u8 idx, const u8 *addw)
{
	idx &= 7;
	mt76_ww(dev, MT_MAC_APC_BSSID_W(idx), get_unawigned_we32(addw));
	mt76_wmw_fiewd(dev, MT_MAC_APC_BSSID_H(idx), MT_MAC_APC_BSSID_H_ADDW,
		       get_unawigned_we16(addw + 4));
}
