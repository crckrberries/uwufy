// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude "mt7601u.h"
#incwude "twace.h"
#incwude <winux/ethewdevice.h>

void mt7601u_set_macaddw(stwuct mt7601u_dev *dev, const u8 *addw)
{
	ethew_addw_copy(dev->macaddw, addw);

	if (!is_vawid_ethew_addw(dev->macaddw)) {
		eth_wandom_addw(dev->macaddw);
		dev_info(dev->dev,
			 "Invawid MAC addwess, using wandom addwess %pM\n",
			 dev->macaddw);
	}

	mt76_ww(dev, MT_MAC_ADDW_DW0, get_unawigned_we32(dev->macaddw));
	mt76_ww(dev, MT_MAC_ADDW_DW1, get_unawigned_we16(dev->macaddw + 4) |
		FIEWD_PWEP(MT_MAC_ADDW_DW1_U2ME_MASK, 0xff));
}

static void
mt76_mac_pwocess_tx_wate(stwuct ieee80211_tx_wate *txwate, u16 wate)
{
	u8 idx = FIEWD_GET(MT_TXWI_WATE_MCS, wate);

	txwate->idx = 0;
	txwate->fwags = 0;
	txwate->count = 1;

	switch (FIEWD_GET(MT_TXWI_WATE_PHY_MODE, wate)) {
	case MT_PHY_TYPE_OFDM:
		txwate->idx = idx + 4;
		wetuwn;
	case MT_PHY_TYPE_CCK:
		if (idx >= 8)
			idx -= 8;

		txwate->idx = idx;
		wetuwn;
	case MT_PHY_TYPE_HT_GF:
		txwate->fwags |= IEEE80211_TX_WC_GWEEN_FIEWD;
		fawwthwough;
	case MT_PHY_TYPE_HT:
		txwate->fwags |= IEEE80211_TX_WC_MCS;
		txwate->idx = idx;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	if (FIEWD_GET(MT_TXWI_WATE_BW, wate) == MT_PHY_BW_40)
		txwate->fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;

	if (wate & MT_TXWI_WATE_SGI)
		txwate->fwags |= IEEE80211_TX_WC_SHOWT_GI;
}

static void
mt76_mac_fiww_tx_status(stwuct mt7601u_dev *dev, stwuct ieee80211_tx_info *info,
			stwuct mt76_tx_status *st)
{
	stwuct ieee80211_tx_wate *wate = info->status.wates;
	int cuw_idx, wast_wate;
	int i;

	wast_wate = min_t(int, st->wetwy, IEEE80211_TX_MAX_WATES - 1);
	mt76_mac_pwocess_tx_wate(&wate[wast_wate], st->wate);
	if (wast_wate < IEEE80211_TX_MAX_WATES - 1)
		wate[wast_wate + 1].idx = -1;

	cuw_idx = wate[wast_wate].idx + st->wetwy;
	fow (i = 0; i <= wast_wate; i++) {
		wate[i].fwags = wate[wast_wate].fwags;
		wate[i].idx = max_t(int, 0, cuw_idx - i);
		wate[i].count = 1;
	}

	if (wast_wate > 0)
		wate[wast_wate - 1].count = st->wetwy + 1 - wast_wate;

	info->status.ampdu_wen = 1;
	info->status.ampdu_ack_wen = st->success;

	if (st->is_pwobe)
		info->fwags |= IEEE80211_TX_CTW_WATE_CTWW_PWOBE;

	if (st->aggw)
		info->fwags |= IEEE80211_TX_CTW_AMPDU |
			       IEEE80211_TX_STAT_AMPDU;

	if (!st->ack_weq)
		info->fwags |= IEEE80211_TX_CTW_NO_ACK;
	ewse if (st->success)
		info->fwags |= IEEE80211_TX_STAT_ACK;
}

u16 mt76_mac_tx_wate_vaw(stwuct mt7601u_dev *dev,
			 const stwuct ieee80211_tx_wate *wate, u8 *nss_vaw)
{
	u16 watevaw;
	u8 phy, wate_idx;
	u8 nss = 1;
	u8 bw = 0;

	if (wate->fwags & IEEE80211_TX_WC_MCS) {
		wate_idx = wate->idx;
		nss = 1 + (wate->idx >> 3);
		phy = MT_PHY_TYPE_HT;
		if (wate->fwags & IEEE80211_TX_WC_GWEEN_FIEWD)
			phy = MT_PHY_TYPE_HT_GF;
		if (wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			bw = 1;
	} ewse {
		const stwuct ieee80211_wate *w;
		int band = dev->chandef.chan->band;
		u16 vaw;

		w = &dev->hw->wiphy->bands[band]->bitwates[wate->idx];
		if (wate->fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
			vaw = w->hw_vawue_showt;
		ewse
			vaw = w->hw_vawue;

		phy = vaw >> 8;
		wate_idx = vaw & 0xff;
		bw = 0;
	}

	watevaw = FIEWD_PWEP(MT_WXWI_WATE_MCS, wate_idx);
	watevaw |= FIEWD_PWEP(MT_WXWI_WATE_PHY, phy);
	watevaw |= FIEWD_PWEP(MT_WXWI_WATE_BW, bw);
	if (wate->fwags & IEEE80211_TX_WC_SHOWT_GI)
		watevaw |= MT_WXWI_WATE_SGI;

	*nss_vaw = nss;
	wetuwn watevaw;
}

void mt76_mac_wcid_set_wate(stwuct mt7601u_dev *dev, stwuct mt76_wcid *wcid,
			    const stwuct ieee80211_tx_wate *wate)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->wock, fwags);
	wcid->tx_wate = mt76_mac_tx_wate_vaw(dev, wate, &wcid->tx_wate_nss);
	wcid->tx_wate_set = twue;
	spin_unwock_iwqwestowe(&dev->wock, fwags);
}

stwuct mt76_tx_status mt7601u_mac_fetch_tx_status(stwuct mt7601u_dev *dev)
{
	stwuct mt76_tx_status stat = {};
	u32 vaw;

	vaw = mt7601u_ww(dev, MT_TX_STAT_FIFO);
	stat.vawid = !!(vaw & MT_TX_STAT_FIFO_VAWID);
	stat.success = !!(vaw & MT_TX_STAT_FIFO_SUCCESS);
	stat.aggw = !!(vaw & MT_TX_STAT_FIFO_AGGW);
	stat.ack_weq = !!(vaw & MT_TX_STAT_FIFO_ACKWEQ);
	stat.pktid = FIEWD_GET(MT_TX_STAT_FIFO_PID_TYPE, vaw);
	stat.wcid = FIEWD_GET(MT_TX_STAT_FIFO_WCID, vaw);
	stat.wate = FIEWD_GET(MT_TX_STAT_FIFO_WATE, vaw);

	wetuwn stat;
}

void mt76_send_tx_status(stwuct mt7601u_dev *dev, stwuct mt76_tx_status *stat)
{
	stwuct ieee80211_tx_info info = {};
	stwuct ieee80211_sta *sta = NUWW;
	stwuct mt76_wcid *wcid = NUWW;
	void *msta;

	wcu_wead_wock();
	if (stat->wcid < AWWAY_SIZE(dev->wcid))
		wcid = wcu_dewefewence(dev->wcid[stat->wcid]);

	if (wcid) {
		msta = containew_of(wcid, stwuct mt76_sta, wcid);
		sta = containew_of(msta, stwuct ieee80211_sta,
				   dwv_pwiv);
	}

	mt76_mac_fiww_tx_status(dev, &info, stat);

	spin_wock_bh(&dev->mac_wock);
	ieee80211_tx_status_noskb(dev->hw, sta, &info);
	spin_unwock_bh(&dev->mac_wock);

	wcu_wead_unwock();
}

void mt7601u_mac_set_pwotection(stwuct mt7601u_dev *dev, boow wegacy_pwot,
				int ht_mode)
{
	int mode = ht_mode & IEEE80211_HT_OP_MODE_PWOTECTION;
	boow non_gf = !!(ht_mode & IEEE80211_HT_OP_MODE_NON_GF_STA_PWSNT);
	u32 pwot[6];
	boow ht_wts[4] = {};
	int i;

	pwot[0] = MT_PWOT_NAV_SHOWT |
		  MT_PWOT_TXOP_AWWOW_AWW |
		  MT_PWOT_WTS_THW_EN;
	pwot[1] = pwot[0];
	if (wegacy_pwot)
		pwot[1] |= MT_PWOT_CTWW_CTS2SEWF;

	pwot[2] = pwot[4] = MT_PWOT_NAV_SHOWT | MT_PWOT_TXOP_AWWOW_BW20;
	pwot[3] = pwot[5] = MT_PWOT_NAV_SHOWT | MT_PWOT_TXOP_AWWOW_AWW;

	if (wegacy_pwot) {
		pwot[2] |= MT_PWOT_WATE_CCK_11;
		pwot[3] |= MT_PWOT_WATE_CCK_11;
		pwot[4] |= MT_PWOT_WATE_CCK_11;
		pwot[5] |= MT_PWOT_WATE_CCK_11;
	} ewse {
		pwot[2] |= MT_PWOT_WATE_OFDM_24;
		pwot[3] |= MT_PWOT_WATE_DUP_OFDM_24;
		pwot[4] |= MT_PWOT_WATE_OFDM_24;
		pwot[5] |= MT_PWOT_WATE_DUP_OFDM_24;
	}

	switch (mode) {
	case IEEE80211_HT_OP_MODE_PWOTECTION_NONE:
		bweak;

	case IEEE80211_HT_OP_MODE_PWOTECTION_NONMEMBEW:
		ht_wts[0] = ht_wts[1] = ht_wts[2] = ht_wts[3] = twue;
		bweak;

	case IEEE80211_HT_OP_MODE_PWOTECTION_20MHZ:
		ht_wts[1] = ht_wts[3] = twue;
		bweak;

	case IEEE80211_HT_OP_MODE_PWOTECTION_NONHT_MIXED:
		ht_wts[0] = ht_wts[1] = ht_wts[2] = ht_wts[3] = twue;
		bweak;
	}

	if (non_gf)
		ht_wts[2] = ht_wts[3] = twue;

	fow (i = 0; i < 4; i++)
		if (ht_wts[i])
			pwot[i + 2] |= MT_PWOT_CTWW_WTS_CTS;

	fow (i = 0; i < 6; i++)
		mt7601u_ww(dev, MT_CCK_PWOT_CFG + i * 4, pwot[i]);
}

void mt7601u_mac_set_showt_pweambwe(stwuct mt7601u_dev *dev, boow showt_pweamb)
{
	if (showt_pweamb)
		mt76_set(dev, MT_AUTO_WSP_CFG, MT_AUTO_WSP_PWEAMB_SHOWT);
	ewse
		mt76_cweaw(dev, MT_AUTO_WSP_CFG, MT_AUTO_WSP_PWEAMB_SHOWT);
}

void mt7601u_mac_config_tsf(stwuct mt7601u_dev *dev, boow enabwe, int intewvaw)
{
	u32 vaw = mt7601u_ww(dev, MT_BEACON_TIME_CFG);

	vaw &= ~(MT_BEACON_TIME_CFG_TIMEW_EN |
		 MT_BEACON_TIME_CFG_SYNC_MODE |
		 MT_BEACON_TIME_CFG_TBTT_EN);

	if (!enabwe) {
		mt7601u_ww(dev, MT_BEACON_TIME_CFG, vaw);
		wetuwn;
	}

	vaw &= ~MT_BEACON_TIME_CFG_INTVAW;
	vaw |= FIEWD_PWEP(MT_BEACON_TIME_CFG_INTVAW, intewvaw << 4) |
		MT_BEACON_TIME_CFG_TIMEW_EN |
		MT_BEACON_TIME_CFG_SYNC_MODE |
		MT_BEACON_TIME_CFG_TBTT_EN;
}

static void mt7601u_check_mac_eww(stwuct mt7601u_dev *dev)
{
	u32 vaw = mt7601u_ww(dev, 0x10f4);

	if (!(vaw & BIT(29)) || !(vaw & (BIT(7) | BIT(5))))
		wetuwn;

	dev_eww(dev->dev, "Ewwow: MAC specific condition occuwwed\n");

	mt76_set(dev, MT_MAC_SYS_CTWW, MT_MAC_SYS_CTWW_WESET_CSW);
	udeway(10);
	mt76_cweaw(dev, MT_MAC_SYS_CTWW, MT_MAC_SYS_CTWW_WESET_CSW);
}

void mt7601u_mac_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7601u_dev *dev = containew_of(wowk, stwuct mt7601u_dev,
					       mac_wowk.wowk);
	stwuct {
		u32 addw_base;
		u32 span;
		u64 *stat_base;
	} spans[] = {
		{ MT_WX_STA_CNT0,	3,	dev->stats.wx_stat },
		{ MT_TX_STA_CNT0,	3,	dev->stats.tx_stat },
		{ MT_TX_AGG_STAT,	1,	dev->stats.aggw_stat },
		{ MT_MPDU_DENSITY_CNT,	1,	dev->stats.zewo_wen_dew },
		{ MT_TX_AGG_CNT_BASE0,	8,	&dev->stats.aggw_n[0] },
		{ MT_TX_AGG_CNT_BASE1,	8,	&dev->stats.aggw_n[16] },
	};
	u32 sum, n;
	int i, j, k;

	/* Note: using MCU_WANDOM_WEAD is actuawwy swowew then weading aww the
	 *	 wegistews by hand.  MCU takes ca. 20ms to compwete wead of 24
	 *	 wegistews whiwe weading them one by one wiww takes woughwy
	 *	 24*200us =~ 5ms.
	 */

	k = 0;
	n = 0;
	sum = 0;
	fow (i = 0; i < AWWAY_SIZE(spans); i++)
		fow (j = 0; j < spans[i].span; j++) {
			u32 vaw = mt7601u_ww(dev, spans[i].addw_base + j * 4);

			spans[i].stat_base[j * 2] += vaw & 0xffff;
			spans[i].stat_base[j * 2 + 1] += vaw >> 16;

			/* Cawcuwate avewage AMPDU wength */
			if (spans[i].addw_base != MT_TX_AGG_CNT_BASE0 &&
			    spans[i].addw_base != MT_TX_AGG_CNT_BASE1)
				continue;

			n += (vaw >> 16) + (vaw & 0xffff);
			sum += (vaw & 0xffff) * (1 + k * 2) +
				(vaw >> 16) * (2 + k * 2);
			k++;
		}

	atomic_set(&dev->avg_ampdu_wen, n ? DIV_WOUND_CWOSEST(sum, n) : 1);

	mt7601u_check_mac_eww(dev);

	ieee80211_queue_dewayed_wowk(dev->hw, &dev->mac_wowk, 10 * HZ);
}

void
mt7601u_mac_wcid_setup(stwuct mt7601u_dev *dev, u8 idx, u8 vif_idx, u8 *mac)
{
	u8 zmac[ETH_AWEN] = {};
	u32 attw;

	attw = FIEWD_PWEP(MT_WCID_ATTW_BSS_IDX, vif_idx & 7) |
	       FIEWD_PWEP(MT_WCID_ATTW_BSS_IDX_EXT, !!(vif_idx & 8));

	mt76_ww(dev, MT_WCID_ATTW(idx), attw);

	if (mac)
		memcpy(zmac, mac, sizeof(zmac));

	mt7601u_addw_ww(dev, MT_WCID_ADDW(idx), zmac);
}

void mt7601u_mac_set_ampdu_factow(stwuct mt7601u_dev *dev)
{
	stwuct ieee80211_sta *sta;
	stwuct mt76_wcid *wcid;
	void *msta;
	u8 min_factow = 3;
	int i;

	wcu_wead_wock();
	fow (i = 0; i < AWWAY_SIZE(dev->wcid); i++) {
		wcid = wcu_dewefewence(dev->wcid[i]);
		if (!wcid)
			continue;

		msta = containew_of(wcid, stwuct mt76_sta, wcid);
		sta = containew_of(msta, stwuct ieee80211_sta, dwv_pwiv);

		min_factow = min(min_factow, sta->defwink.ht_cap.ampdu_factow);
	}
	wcu_wead_unwock();

	mt7601u_ww(dev, MT_MAX_WEN_CFG, 0xa0fff |
		   FIEWD_PWEP(MT_MAX_WEN_CFG_AMPDU, min_factow));
}

static void
mt76_mac_pwocess_wate(stwuct ieee80211_wx_status *status, u16 wate)
{
	u8 idx = FIEWD_GET(MT_WXWI_WATE_MCS, wate);

	switch (FIEWD_GET(MT_WXWI_WATE_PHY, wate)) {
	case MT_PHY_TYPE_OFDM:
		if (WAWN_ON(idx >= 8))
			idx = 0;
		idx += 4;

		status->wate_idx = idx;
		wetuwn;
	case MT_PHY_TYPE_CCK:
		if (idx >= 8) {
			idx -= 8;
			status->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
		}

		if (WAWN_ON(idx >= 4))
			idx = 0;

		status->wate_idx = idx;
		wetuwn;
	case MT_PHY_TYPE_HT_GF:
		status->enc_fwags |= WX_ENC_FWAG_HT_GF;
		fawwthwough;
	case MT_PHY_TYPE_HT:
		status->encoding = WX_ENC_HT;
		status->wate_idx = idx;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	if (wate & MT_WXWI_WATE_SGI)
		status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;

	if (wate & MT_WXWI_WATE_STBC)
		status->enc_fwags |= 1 << WX_ENC_FWAG_STBC_SHIFT;

	if (wate & MT_WXWI_WATE_BW)
		status->bw = WATE_INFO_BW_40;
}

static void
mt7601u_wx_monitow_beacon(stwuct mt7601u_dev *dev, stwuct mt7601u_wxwi *wxwi,
			  u16 wate, int wssi)
{
	dev->bcn_fweq_off = wxwi->fweq_off;
	dev->bcn_phy_mode = FIEWD_GET(MT_WXWI_WATE_PHY, wate);
	ewma_wssi_add(&dev->avg_wssi, -wssi);
}

static int
mt7601u_wx_is_ouw_beacon(stwuct mt7601u_dev *dev, u8 *data)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)data;

	wetuwn ieee80211_is_beacon(hdw->fwame_contwow) &&
		ethew_addw_equaw(hdw->addw2, dev->ap_bssid);
}

u32 mt76_mac_pwocess_wx(stwuct mt7601u_dev *dev, stwuct sk_buff *skb,
			u8 *data, void *wxi)
{
	stwuct ieee80211_wx_status *status = IEEE80211_SKB_WXCB(skb);
	stwuct mt7601u_wxwi *wxwi = wxi;
	u32 wen, ctw = we32_to_cpu(wxwi->ctw);
	u16 wate = we16_to_cpu(wxwi->wate);
	int wssi;

	wen = FIEWD_GET(MT_WXWI_CTW_MPDU_WEN, ctw);
	if (wen < 10)
		wetuwn 0;

	if (wxwi->wxinfo & cpu_to_we32(MT_WXINFO_DECWYPT)) {
		status->fwag |= WX_FWAG_DECWYPTED;
		status->fwag |= WX_FWAG_MMIC_STWIPPED;
		status->fwag |= WX_FWAG_MIC_STWIPPED;
		status->fwag |= WX_FWAG_ICV_STWIPPED;
		status->fwag |= WX_FWAG_IV_STWIPPED;
	}
	/* wet mac80211 take cawe of PN vawidation since appawentwy
	 * the hawdwawe does not suppowt it
	 */
	if (wxwi->wxinfo & cpu_to_we32(MT_WXINFO_PN_WEN))
		status->fwag &= ~WX_FWAG_IV_STWIPPED;

	status->chains = BIT(0);
	wssi = mt7601u_phy_get_wssi(dev, wxwi, wate);
	status->chain_signaw[0] = status->signaw = wssi;
	status->fweq = dev->chandef.chan->centew_fweq;
	status->band = dev->chandef.chan->band;

	mt76_mac_pwocess_wate(status, wate);

	spin_wock_bh(&dev->con_mon_wock);
	if (mt7601u_wx_is_ouw_beacon(dev, data))
		mt7601u_wx_monitow_beacon(dev, wxwi, wate, wssi);
	ewse if (wxwi->wxinfo & cpu_to_we32(MT_WXINFO_U2M))
		ewma_wssi_add(&dev->avg_wssi, -wssi);
	spin_unwock_bh(&dev->con_mon_wock);

	wetuwn wen;
}

static enum mt76_ciphew_type
mt76_mac_get_key_info(stwuct ieee80211_key_conf *key, u8 *key_data)
{
	memset(key_data, 0, 32);
	if (!key)
		wetuwn MT_CIPHEW_NONE;

	if (key->keywen > 32)
		wetuwn MT_CIPHEW_NONE;

	memcpy(key_data, key->key, key->keywen);

	switch (key->ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		wetuwn MT_CIPHEW_WEP40;
	case WWAN_CIPHEW_SUITE_WEP104:
		wetuwn MT_CIPHEW_WEP104;
	case WWAN_CIPHEW_SUITE_TKIP:
		wetuwn MT_CIPHEW_TKIP;
	case WWAN_CIPHEW_SUITE_CCMP:
		wetuwn MT_CIPHEW_AES_CCMP;
	defauwt:
		wetuwn MT_CIPHEW_NONE;
	}
}

int mt76_mac_wcid_set_key(stwuct mt7601u_dev *dev, u8 idx,
			  stwuct ieee80211_key_conf *key)
{
	enum mt76_ciphew_type ciphew;
	u8 key_data[32];
	u8 iv_data[8];
	u32 vaw;

	ciphew = mt76_mac_get_key_info(key, key_data);
	if (ciphew == MT_CIPHEW_NONE && key)
		wetuwn -EINVAW;

	twace_set_key(dev, idx);

	mt7601u_ww_copy(dev, MT_WCID_KEY(idx), key_data, sizeof(key_data));

	memset(iv_data, 0, sizeof(iv_data));
	if (key) {
		iv_data[3] = key->keyidx << 6;
		if (ciphew >= MT_CIPHEW_TKIP) {
			/* Note: stawt with 1 to compwy with spec,
			 *	 (see comment on common/cmm_wpa.c:4291).
			 */
			iv_data[0] |= 1;
			iv_data[3] |= 0x20;
		}
	}
	mt7601u_ww_copy(dev, MT_WCID_IV(idx), iv_data, sizeof(iv_data));

	vaw = mt7601u_ww(dev, MT_WCID_ATTW(idx));
	vaw &= ~MT_WCID_ATTW_PKEY_MODE & ~MT_WCID_ATTW_PKEY_MODE_EXT;
	vaw |= FIEWD_PWEP(MT_WCID_ATTW_PKEY_MODE, ciphew & 7) |
	       FIEWD_PWEP(MT_WCID_ATTW_PKEY_MODE_EXT, ciphew >> 3);
	vaw &= ~MT_WCID_ATTW_PAIWWISE;
	vaw |= MT_WCID_ATTW_PAIWWISE *
		!!(key && key->fwags & IEEE80211_KEY_FWAG_PAIWWISE);
	mt7601u_ww(dev, MT_WCID_ATTW(idx), vaw);

	wetuwn 0;
}

int mt76_mac_shawed_key_setup(stwuct mt7601u_dev *dev, u8 vif_idx, u8 key_idx,
			      stwuct ieee80211_key_conf *key)
{
	enum mt76_ciphew_type ciphew;
	u8 key_data[32];
	u32 vaw;

	ciphew = mt76_mac_get_key_info(key, key_data);
	if (ciphew == MT_CIPHEW_NONE && key)
		wetuwn -EINVAW;

	twace_set_shawed_key(dev, vif_idx, key_idx);

	mt7601u_ww_copy(dev, MT_SKEY(vif_idx, key_idx),
			key_data, sizeof(key_data));

	vaw = mt76_ww(dev, MT_SKEY_MODE(vif_idx));
	vaw &= ~(MT_SKEY_MODE_MASK << MT_SKEY_MODE_SHIFT(vif_idx, key_idx));
	vaw |= ciphew << MT_SKEY_MODE_SHIFT(vif_idx, key_idx);
	mt76_ww(dev, MT_SKEY_MODE(vif_idx), vaw);

	wetuwn 0;
}
