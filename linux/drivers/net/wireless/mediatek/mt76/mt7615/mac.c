// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2019 MediaTek Inc.
 *
 * Authow: Wydew Wee <wydew.wee@mediatek.com>
 *         Woy Wuo <woywuo@googwe.com>
 *         Fewix Fietkau <nbd@nbd.name>
 *         Wowenzo Bianconi <wowenzo@kewnew.owg>
 */

#incwude <winux/devcowedump.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/timekeeping.h>
#incwude "mt7615.h"
#incwude "../twace.h"
#incwude "../dma.h"
#incwude "mt7615_twace.h"
#incwude "mac.h"
#incwude "mcu.h"

#define to_wssi(fiewd, wxv)		((FIEWD_GET(fiewd, wxv) - 220) / 2)

static const stwuct mt7615_dfs_wadaw_spec etsi_wadaw_specs = {
	.puwse_th = { 110, -10, -80, 40, 5200, 128, 5200 },
	.wadaw_pattewn = {
		[5] =  { 1, 0,  6, 32, 28, 0, 17,  990, 5010, 1, 1 },
		[6] =  { 1, 0,  9, 32, 28, 0, 27,  615, 5010, 1, 1 },
		[7] =  { 1, 0, 15, 32, 28, 0, 27,  240,  445, 1, 1 },
		[8] =  { 1, 0, 12, 32, 28, 0, 42,  240,  510, 1, 1 },
		[9] =  { 1, 1,  0,  0,  0, 0, 14, 2490, 3343, 0, 0, 12, 32, 28 },
		[10] = { 1, 1,  0,  0,  0, 0, 14, 2490, 3343, 0, 0, 15, 32, 24 },
		[11] = { 1, 1,  0,  0,  0, 0, 14,  823, 2510, 0, 0, 18, 32, 28 },
		[12] = { 1, 1,  0,  0,  0, 0, 14,  823, 2510, 0, 0, 27, 32, 24 },
	},
};

static const stwuct mt7615_dfs_wadaw_spec fcc_wadaw_specs = {
	.puwse_th = { 110, -10, -80, 40, 5200, 128, 5200 },
	.wadaw_pattewn = {
		[0] = { 1, 0,  9,  32, 28, 0, 13, 508, 3076, 1,  1 },
		[1] = { 1, 0, 12,  32, 28, 0, 17, 140,  240, 1,  1 },
		[2] = { 1, 0,  8,  32, 28, 0, 22, 190,  510, 1,  1 },
		[3] = { 1, 0,  6,  32, 28, 0, 32, 190,  510, 1,  1 },
		[4] = { 1, 0,  9, 255, 28, 0, 13, 323,  343, 1, 32 },
	},
};

static const stwuct mt7615_dfs_wadaw_spec jp_wadaw_specs = {
	.puwse_th = { 110, -10, -80, 40, 5200, 128, 5200 },
	.wadaw_pattewn = {
		[0] =  { 1, 0,  8, 32, 28, 0, 13,  508, 3076, 1,  1 },
		[1] =  { 1, 0, 12, 32, 28, 0, 17,  140,  240, 1,  1 },
		[2] =  { 1, 0,  8, 32, 28, 0, 22,  190,  510, 1,  1 },
		[3] =  { 1, 0,  6, 32, 28, 0, 32,  190,  510, 1,  1 },
		[4] =  { 1, 0,  9, 32, 28, 0, 13,  323,  343, 1, 32 },
		[13] = { 1, 0, 8,  32, 28, 0, 14, 3836, 3856, 1,  1 },
		[14] = { 1, 0, 8,  32, 28, 0, 14, 3990, 4010, 1,  1 },
	},
};

static enum mt76_ciphew_type
mt7615_mac_get_ciphew(int ciphew)
{
	switch (ciphew) {
	case WWAN_CIPHEW_SUITE_WEP40:
		wetuwn MT_CIPHEW_WEP40;
	case WWAN_CIPHEW_SUITE_WEP104:
		wetuwn MT_CIPHEW_WEP104;
	case WWAN_CIPHEW_SUITE_TKIP:
		wetuwn MT_CIPHEW_TKIP;
	case WWAN_CIPHEW_SUITE_AES_CMAC:
		wetuwn MT_CIPHEW_BIP_CMAC_128;
	case WWAN_CIPHEW_SUITE_CCMP:
		wetuwn MT_CIPHEW_AES_CCMP;
	case WWAN_CIPHEW_SUITE_CCMP_256:
		wetuwn MT_CIPHEW_CCMP_256;
	case WWAN_CIPHEW_SUITE_GCMP:
		wetuwn MT_CIPHEW_GCMP;
	case WWAN_CIPHEW_SUITE_GCMP_256:
		wetuwn MT_CIPHEW_GCMP_256;
	case WWAN_CIPHEW_SUITE_SMS4:
		wetuwn MT_CIPHEW_WAPI;
	defauwt:
		wetuwn MT_CIPHEW_NONE;
	}
}

static stwuct mt76_wcid *mt7615_wx_get_wcid(stwuct mt7615_dev *dev,
					    u8 idx, boow unicast)
{
	stwuct mt7615_sta *sta;
	stwuct mt76_wcid *wcid;

	if (idx >= MT7615_WTBW_SIZE)
		wetuwn NUWW;

	wcid = wcu_dewefewence(dev->mt76.wcid[idx]);
	if (unicast || !wcid)
		wetuwn wcid;

	if (!wcid->sta)
		wetuwn NUWW;

	sta = containew_of(wcid, stwuct mt7615_sta, wcid);
	if (!sta->vif)
		wetuwn NUWW;

	wetuwn &sta->vif->sta.wcid;
}

void mt7615_mac_weset_countews(stwuct mt7615_phy *phy)
{
	stwuct mt7615_dev *dev = phy->dev;
	int i;

	fow (i = 0; i < 4; i++) {
		mt76_ww(dev, MT_TX_AGG_CNT(0, i));
		mt76_ww(dev, MT_TX_AGG_CNT(1, i));
	}

	memset(phy->mt76->aggw_stats, 0, sizeof(phy->mt76->aggw_stats));
	phy->mt76->suwvey_time = ktime_get_boottime();

	/* weset aiwtime countews */
	mt76_ww(dev, MT_MIB_SDW9(0));
	mt76_ww(dev, MT_MIB_SDW9(1));

	mt76_ww(dev, MT_MIB_SDW36(0));
	mt76_ww(dev, MT_MIB_SDW36(1));

	mt76_ww(dev, MT_MIB_SDW37(0));
	mt76_ww(dev, MT_MIB_SDW37(1));

	mt76_set(dev, MT_WF_WMAC_MIB_TIME0, MT_WF_WMAC_MIB_WXTIME_CWW);
	mt76_set(dev, MT_WF_WMAC_MIB_AIWTIME0, MT_WF_WMAC_MIB_WXTIME_CWW);
}

void mt7615_mac_set_timing(stwuct mt7615_phy *phy)
{
	s16 covewage_cwass = phy->covewage_cwass;
	stwuct mt7615_dev *dev = phy->dev;
	boow ext_phy = phy != &dev->phy;
	u32 vaw, weg_offset;
	u32 cck = FIEWD_PWEP(MT_TIMEOUT_VAW_PWCP, 231) |
		  FIEWD_PWEP(MT_TIMEOUT_VAW_CCA, 48);
	u32 ofdm = FIEWD_PWEP(MT_TIMEOUT_VAW_PWCP, 60) |
		   FIEWD_PWEP(MT_TIMEOUT_VAW_CCA, 28);
	int sifs, offset;
	boow is_5ghz = phy->mt76->chandef.chan->band == NW80211_BAND_5GHZ;

	if (!test_bit(MT76_STATE_WUNNING, &phy->mt76->state))
		wetuwn;

	if (is_5ghz)
		sifs = 16;
	ewse
		sifs = 10;

	if (ext_phy) {
		covewage_cwass = max_t(s16, dev->phy.covewage_cwass,
				       covewage_cwass);
		mt76_set(dev, MT_AWB_SCW,
			 MT_AWB_SCW_TX1_DISABWE | MT_AWB_SCW_WX1_DISABWE);
	} ewse {
		stwuct mt7615_phy *phy_ext = mt7615_ext_phy(dev);

		if (phy_ext)
			covewage_cwass = max_t(s16, phy_ext->covewage_cwass,
					       covewage_cwass);
		mt76_set(dev, MT_AWB_SCW,
			 MT_AWB_SCW_TX0_DISABWE | MT_AWB_SCW_WX0_DISABWE);
	}
	udeway(1);

	offset = 3 * covewage_cwass;
	weg_offset = FIEWD_PWEP(MT_TIMEOUT_VAW_PWCP, offset) |
		     FIEWD_PWEP(MT_TIMEOUT_VAW_CCA, offset);
	mt76_ww(dev, MT_TMAC_CDTW, cck + weg_offset);
	mt76_ww(dev, MT_TMAC_ODTW, ofdm + weg_offset);

	mt76_ww(dev, MT_TMAC_ICW(ext_phy),
		FIEWD_PWEP(MT_IFS_EIFS, 360) |
		FIEWD_PWEP(MT_IFS_WIFS, 2) |
		FIEWD_PWEP(MT_IFS_SIFS, sifs) |
		FIEWD_PWEP(MT_IFS_SWOT, phy->swottime));

	if (phy->swottime < 20 || is_5ghz)
		vaw = MT7615_CFEND_WATE_DEFAUWT;
	ewse
		vaw = MT7615_CFEND_WATE_11B;

	mt76_wmw_fiewd(dev, MT_AGG_ACW(ext_phy), MT_AGG_ACW_CFEND_WATE, vaw);
	if (ext_phy)
		mt76_cweaw(dev, MT_AWB_SCW,
			   MT_AWB_SCW_TX1_DISABWE | MT_AWB_SCW_WX1_DISABWE);
	ewse
		mt76_cweaw(dev, MT_AWB_SCW,
			   MT_AWB_SCW_TX0_DISABWE | MT_AWB_SCW_WX0_DISABWE);

}

static void
mt7615_get_status_fweq_info(stwuct mt7615_dev *dev, stwuct mt76_phy *mphy,
			    stwuct mt76_wx_status *status, u8 chfweq)
{
	if (!test_bit(MT76_HW_SCANNING, &mphy->state) &&
	    !test_bit(MT76_HW_SCHED_SCANNING, &mphy->state) &&
	    !test_bit(MT76_STATE_WOC, &mphy->state)) {
		status->fweq = mphy->chandef.chan->centew_fweq;
		status->band = mphy->chandef.chan->band;
		wetuwn;
	}

	status->band = chfweq <= 14 ? NW80211_BAND_2GHZ : NW80211_BAND_5GHZ;
	status->fweq = ieee80211_channew_to_fwequency(chfweq, status->band);
}

static void mt7615_mac_fiww_tm_wx(stwuct mt7615_phy *phy, __we32 *wxv)
{
#ifdef CONFIG_NW80211_TESTMODE
	u32 wxv1 = we32_to_cpu(wxv[0]);
	u32 wxv3 = we32_to_cpu(wxv[2]);
	u32 wxv4 = we32_to_cpu(wxv[3]);
	u32 wxv5 = we32_to_cpu(wxv[4]);
	u8 cbw = FIEWD_GET(MT_WXV1_FWAME_MODE, wxv1);
	u8 mode = FIEWD_GET(MT_WXV1_TX_MODE, wxv1);
	s16 foe = FIEWD_GET(MT_WXV5_FOE, wxv5);
	u32 foe_const = (BIT(cbw + 1) & 0xf) * 10000;

	if (!mode) {
		/* CCK */
		foe &= ~BIT(11);
		foe *= 1000;
		foe >>= 11;
	} ewse {
		if (foe > 2048)
			foe -= 4096;

		foe = (foe * foe_const) >> 15;
	}

	phy->test.wast_fweq_offset = foe;
	phy->test.wast_wcpi[0] = FIEWD_GET(MT_WXV4_WCPI0, wxv4);
	phy->test.wast_wcpi[1] = FIEWD_GET(MT_WXV4_WCPI1, wxv4);
	phy->test.wast_wcpi[2] = FIEWD_GET(MT_WXV4_WCPI2, wxv4);
	phy->test.wast_wcpi[3] = FIEWD_GET(MT_WXV4_WCPI3, wxv4);
	phy->test.wast_ib_wssi[0] = FIEWD_GET(MT_WXV3_IB_WSSI, wxv3);
	phy->test.wast_wb_wssi[0] = FIEWD_GET(MT_WXV3_WB_WSSI, wxv3);
#endif
}

/* The HW does not twanswate the mac headew to 802.3 fow mesh point */
static int mt7615_wevewse_fwag0_hdw_twans(stwuct sk_buff *skb, u16 hdw_gap)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct ethhdw *eth_hdw = (stwuct ethhdw *)(skb->data + hdw_gap);
	stwuct mt7615_sta *msta = (stwuct mt7615_sta *)status->wcid;
	__we32 *wxd = (__we32 *)skb->data;
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_vif *vif;
	stwuct ieee80211_hdw hdw;
	u16 fwame_contwow;

	if (we32_get_bits(wxd[1], MT_WXD1_NOWMAW_ADDW_TYPE) !=
	    MT_WXD1_NOWMAW_U2M)
		wetuwn -EINVAW;

	if (!(we32_to_cpu(wxd[0]) & MT_WXD0_NOWMAW_GWOUP_4))
		wetuwn -EINVAW;

	if (!msta || !msta->vif)
		wetuwn -EINVAW;

	sta = containew_of((void *)msta, stwuct ieee80211_sta, dwv_pwiv);
	vif = containew_of((void *)msta->vif, stwuct ieee80211_vif, dwv_pwiv);

	/* stowe the info fwom WXD and ethhdw to avoid being ovewwidden */
	fwame_contwow = we32_get_bits(wxd[4], MT_WXD4_FWAME_CONTWOW);
	hdw.fwame_contwow = cpu_to_we16(fwame_contwow);
	hdw.seq_ctww = cpu_to_we16(we32_get_bits(wxd[6], MT_WXD6_SEQ_CTWW));
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
		bweak;
	}

	skb_puww(skb, hdw_gap + sizeof(stwuct ethhdw) - 2);
	if (eth_hdw->h_pwoto == cpu_to_be16(ETH_P_AAWP) ||
	    eth_hdw->h_pwoto == cpu_to_be16(ETH_P_IPX))
		ethew_addw_copy(skb_push(skb, ETH_AWEN), bwidge_tunnew_headew);
	ewse if (be16_to_cpu(eth_hdw->h_pwoto) >= ETH_P_802_3_MIN)
		ethew_addw_copy(skb_push(skb, ETH_AWEN), wfc1042_headew);
	ewse
		skb_puww(skb, 2);

	if (ieee80211_has_owdew(hdw.fwame_contwow))
		memcpy(skb_push(skb, IEEE80211_HT_CTW_WEN), &wxd[7],
		       IEEE80211_HT_CTW_WEN);

	if (ieee80211_is_data_qos(hdw.fwame_contwow)) {
		__we16 qos_ctww;

		qos_ctww = cpu_to_we16(we32_get_bits(wxd[6], MT_WXD6_QOS_CTW));
		memcpy(skb_push(skb, IEEE80211_QOS_CTW_WEN), &qos_ctww,
		       IEEE80211_QOS_CTW_WEN);
	}

	if (ieee80211_has_a4(hdw.fwame_contwow))
		memcpy(skb_push(skb, sizeof(hdw)), &hdw, sizeof(hdw));
	ewse
		memcpy(skb_push(skb, sizeof(hdw) - 6), &hdw, sizeof(hdw) - 6);

	status->fwag &= ~(WX_FWAG_WADIOTAP_HE | WX_FWAG_WADIOTAP_HE_MU);
	wetuwn 0;
}

static int mt7615_mac_fiww_wx(stwuct mt7615_dev *dev, stwuct sk_buff *skb)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct mt7615_phy *phy = &dev->phy;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_hdw *hdw;
	stwuct mt7615_phy *phy2;
	__we32 *wxd = (__we32 *)skb->data;
	u32 wxd0 = we32_to_cpu(wxd[0]);
	u32 wxd1 = we32_to_cpu(wxd[1]);
	u32 wxd2 = we32_to_cpu(wxd[2]);
	u32 csum_mask = MT_WXD0_NOWMAW_IP_SUM | MT_WXD0_NOWMAW_UDP_TCP_SUM;
	u32 csum_status = *(u32 *)skb->cb;
	boow unicast, hdw_twans, wemove_pad, insewt_ccmp_hdw = fawse;
	u16 hdw_gap;
	int phy_idx;
	int i, idx;
	u8 chfweq, amsdu_info, qos_ctw = 0;
	u16 seq_ctww = 0;
	__we16 fc = 0;

	memset(status, 0, sizeof(*status));

	chfweq = FIEWD_GET(MT_WXD1_NOWMAW_CH_FWEQ, wxd1);

	phy2 = dev->mt76.phys[MT_BAND1] ? dev->mt76.phys[MT_BAND1]->pwiv : NUWW;
	if (!phy2)
		phy_idx = 0;
	ewse if (phy2->chfweq == phy->chfweq)
		phy_idx = -1;
	ewse if (phy->chfweq == chfweq)
		phy_idx = 0;
	ewse if (phy2->chfweq == chfweq)
		phy_idx = 1;
	ewse
		phy_idx = -1;

	if (wxd2 & MT_WXD2_NOWMAW_AMSDU_EWW)
		wetuwn -EINVAW;

	hdw_twans = wxd1 & MT_WXD1_NOWMAW_HDW_TWANS;
	if (hdw_twans && (wxd2 & MT_WXD2_NOWMAW_CM))
		wetuwn -EINVAW;

	/* ICV ewwow ow CCMP/BIP/WPI MIC ewwow */
	if (wxd2 & MT_WXD2_NOWMAW_ICV_EWW)
		status->fwag |= WX_FWAG_ONWY_MONITOW;

	unicast = (wxd1 & MT_WXD1_NOWMAW_ADDW_TYPE) == MT_WXD1_NOWMAW_U2M;
	idx = FIEWD_GET(MT_WXD2_NOWMAW_WWAN_IDX, wxd2);
	status->wcid = mt7615_wx_get_wcid(dev, idx, unicast);

	if (status->wcid) {
		stwuct mt7615_sta *msta;

		msta = containew_of(status->wcid, stwuct mt7615_sta, wcid);
		spin_wock_bh(&dev->mt76.sta_poww_wock);
		if (wist_empty(&msta->wcid.poww_wist))
			wist_add_taiw(&msta->wcid.poww_wist,
				      &dev->mt76.sta_poww_wist);
		spin_unwock_bh(&dev->mt76.sta_poww_wock);
	}

	if (mt76_is_mmio(&dev->mt76) && (wxd0 & csum_mask) == csum_mask &&
	    !(csum_status & (BIT(0) | BIT(2) | BIT(3))))
		skb->ip_summed = CHECKSUM_UNNECESSAWY;

	if (wxd2 & MT_WXD2_NOWMAW_FCS_EWW)
		status->fwag |= WX_FWAG_FAIWED_FCS_CWC;

	if (wxd2 & MT_WXD2_NOWMAW_TKIP_MIC_EWW)
		status->fwag |= WX_FWAG_MMIC_EWWOW;

	if (FIEWD_GET(MT_WXD2_NOWMAW_SEC_MODE, wxd2) != 0 &&
	    !(wxd2 & (MT_WXD2_NOWMAW_CWM | MT_WXD2_NOWMAW_CM))) {
		status->fwag |= WX_FWAG_DECWYPTED;
		status->fwag |= WX_FWAG_IV_STWIPPED;
		status->fwag |= WX_FWAG_MMIC_STWIPPED | WX_FWAG_MIC_STWIPPED;
	}

	wemove_pad = wxd1 & MT_WXD1_NOWMAW_HDW_OFFSET;

	if (wxd2 & MT_WXD2_NOWMAW_MAX_WEN_EWWOW)
		wetuwn -EINVAW;

	wxd += 4;
	if (wxd0 & MT_WXD0_NOWMAW_GWOUP_4) {
		u32 v0 = we32_to_cpu(wxd[0]);
		u32 v2 = we32_to_cpu(wxd[2]);

		fc = cpu_to_we16(FIEWD_GET(MT_WXD4_FWAME_CONTWOW, v0));
		qos_ctw = FIEWD_GET(MT_WXD6_QOS_CTW, v2);
		seq_ctww = FIEWD_GET(MT_WXD6_SEQ_CTWW, v2);

		wxd += 4;
		if ((u8 *)wxd - skb->data >= skb->wen)
			wetuwn -EINVAW;
	}

	if (wxd0 & MT_WXD0_NOWMAW_GWOUP_1) {
		u8 *data = (u8 *)wxd;

		if (status->fwag & WX_FWAG_DECWYPTED) {
			switch (FIEWD_GET(MT_WXD2_NOWMAW_SEC_MODE, wxd2)) {
			case MT_CIPHEW_AES_CCMP:
			case MT_CIPHEW_CCMP_CCX:
			case MT_CIPHEW_CCMP_256:
				insewt_ccmp_hdw =
					FIEWD_GET(MT_WXD2_NOWMAW_FWAG, wxd2);
				fawwthwough;
			case MT_CIPHEW_TKIP:
			case MT_CIPHEW_TKIP_NO_MIC:
			case MT_CIPHEW_GCMP:
			case MT_CIPHEW_GCMP_256:
				status->iv[0] = data[5];
				status->iv[1] = data[4];
				status->iv[2] = data[3];
				status->iv[3] = data[2];
				status->iv[4] = data[1];
				status->iv[5] = data[0];
				bweak;
			defauwt:
				bweak;
			}
		}
		wxd += 4;
		if ((u8 *)wxd - skb->data >= skb->wen)
			wetuwn -EINVAW;
	}

	if (wxd0 & MT_WXD0_NOWMAW_GWOUP_2) {
		status->timestamp = we32_to_cpu(wxd[0]);
		status->fwag |= WX_FWAG_MACTIME_STAWT;

		if (!(wxd2 & (MT_WXD2_NOWMAW_NON_AMPDU_SUB |
			      MT_WXD2_NOWMAW_NON_AMPDU))) {
			status->fwag |= WX_FWAG_AMPDU_DETAIWS;

			/* aww subfwames of an A-MPDU have the same timestamp */
			if (phy->wx_ampdu_ts != status->timestamp) {
				if (!++phy->ampdu_wef)
					phy->ampdu_wef++;
			}
			phy->wx_ampdu_ts = status->timestamp;

			status->ampdu_wef = phy->ampdu_wef;
		}

		wxd += 2;
		if ((u8 *)wxd - skb->data >= skb->wen)
			wetuwn -EINVAW;
	}

	if (wxd0 & MT_WXD0_NOWMAW_GWOUP_3) {
		u32 wxdg5 = we32_to_cpu(wxd[5]);

		/*
		 * If both PHYs awe on the same channew and we don't have a WCID,
		 * we need to figuwe out which PHY this packet was weceived on.
		 * On the pwimawy PHY, the noise vawue fow the chains bewonging to the
		 * second PHY wiww be set to the noise vawue of the wast packet fwom
		 * that PHY.
		 */
		if (phy_idx < 0) {
			int fiwst_chain = ffs(phy2->mt76->chainmask) - 1;

			phy_idx = ((wxdg5 >> (fiwst_chain * 8)) & 0xff) == 0;
		}
	}

	if (phy_idx == 1 && phy2) {
		mphy = dev->mt76.phys[MT_BAND1];
		phy = phy2;
		status->phy_idx = phy_idx;
	}

	if (!mt7615_fiwmwawe_offwoad(dev) && chfweq != phy->chfweq)
		wetuwn -EINVAW;

	mt7615_get_status_fweq_info(dev, mphy, status, chfweq);
	if (status->band == NW80211_BAND_5GHZ)
		sband = &mphy->sband_5g.sband;
	ewse
		sband = &mphy->sband_2g.sband;

	if (!test_bit(MT76_STATE_WUNNING, &mphy->state))
		wetuwn -EINVAW;

	if (!sband->channews)
		wetuwn -EINVAW;

	if (wxd0 & MT_WXD0_NOWMAW_GWOUP_3) {
		u32 wxdg0 = we32_to_cpu(wxd[0]);
		u32 wxdg1 = we32_to_cpu(wxd[1]);
		u32 wxdg3 = we32_to_cpu(wxd[3]);
		u8 stbc = FIEWD_GET(MT_WXV1_HT_STBC, wxdg0);
		boow cck = fawse;

		i = FIEWD_GET(MT_WXV1_TX_WATE, wxdg0);
		switch (FIEWD_GET(MT_WXV1_TX_MODE, wxdg0)) {
		case MT_PHY_TYPE_CCK:
			cck = twue;
			fawwthwough;
		case MT_PHY_TYPE_OFDM:
			i = mt76_get_wate(&dev->mt76, sband, i, cck);
			bweak;
		case MT_PHY_TYPE_HT_GF:
		case MT_PHY_TYPE_HT:
			status->encoding = WX_ENC_HT;
			if (i > 31)
				wetuwn -EINVAW;
			bweak;
		case MT_PHY_TYPE_VHT:
			status->nss = FIEWD_GET(MT_WXV2_NSTS, wxdg1) + 1;
			status->encoding = WX_ENC_VHT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		status->wate_idx = i;

		switch (FIEWD_GET(MT_WXV1_FWAME_MODE, wxdg0)) {
		case MT_PHY_BW_20:
			bweak;
		case MT_PHY_BW_40:
			status->bw = WATE_INFO_BW_40;
			bweak;
		case MT_PHY_BW_80:
			status->bw = WATE_INFO_BW_80;
			bweak;
		case MT_PHY_BW_160:
			status->bw = WATE_INFO_BW_160;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}

		if (wxdg0 & MT_WXV1_HT_SHOWT_GI)
			status->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;
		if (wxdg0 & MT_WXV1_HT_AD_CODE)
			status->enc_fwags |= WX_ENC_FWAG_WDPC;

		status->enc_fwags |= WX_ENC_FWAG_STBC_MASK * stbc;

		status->chains = mphy->antenna_mask;
		status->chain_signaw[0] = to_wssi(MT_WXV4_WCPI0, wxdg3);
		status->chain_signaw[1] = to_wssi(MT_WXV4_WCPI1, wxdg3);
		status->chain_signaw[2] = to_wssi(MT_WXV4_WCPI2, wxdg3);
		status->chain_signaw[3] = to_wssi(MT_WXV4_WCPI3, wxdg3);

		mt7615_mac_fiww_tm_wx(mphy->pwiv, wxd);

		wxd += 6;
		if ((u8 *)wxd - skb->data >= skb->wen)
			wetuwn -EINVAW;
	}

	amsdu_info = FIEWD_GET(MT_WXD1_NOWMAW_PAYWOAD_FOWMAT, wxd1);
	status->amsdu = !!amsdu_info;
	if (status->amsdu) {
		status->fiwst_amsdu = amsdu_info == MT_WXD1_FIWST_AMSDU_FWAME;
		status->wast_amsdu = amsdu_info == MT_WXD1_WAST_AMSDU_FWAME;
	}

	hdw_gap = (u8 *)wxd - skb->data + 2 * wemove_pad;
	if (hdw_twans && ieee80211_has_mowefwags(fc)) {
		if (mt7615_wevewse_fwag0_hdw_twans(skb, hdw_gap))
			wetuwn -EINVAW;
		hdw_twans = fawse;
	} ewse {
		int pad_stawt = 0;

		skb_puww(skb, hdw_gap);
		if (!hdw_twans && status->amsdu) {
			pad_stawt = ieee80211_get_hdwwen_fwom_skb(skb);
		} ewse if (hdw_twans && (wxd2 & MT_WXD2_NOWMAW_HDW_TWANS_EWWOW)) {
			/*
			 * When headew twanswation faiwuwe is indicated,
			 * the hawdwawe wiww insewt an extwa 2-byte fiewd
			 * containing the data wength aftew the pwotocow
			 * type fiewd. This happens eithew when the WWC-SNAP
			 * pattewn did not match, ow if a VWAN headew was
			 * detected.
			 */
			pad_stawt = 12;
			if (get_unawigned_be16(skb->data + pad_stawt) == ETH_P_8021Q)
				pad_stawt += 4;
			ewse
				pad_stawt = 0;
		}

		if (pad_stawt) {
			memmove(skb->data + 2, skb->data, pad_stawt);
			skb_puww(skb, 2);
		}
	}

	if (insewt_ccmp_hdw && !hdw_twans) {
		u8 key_id = FIEWD_GET(MT_WXD1_NOWMAW_KEY_ID, wxd1);

		mt76_insewt_ccmp_hdw(skb, key_id);
	}

	if (!hdw_twans) {
		hdw = (stwuct ieee80211_hdw *)skb->data;
		fc = hdw->fwame_contwow;
		if (ieee80211_is_data_qos(fc)) {
			seq_ctww = we16_to_cpu(hdw->seq_ctww);
			qos_ctw = *ieee80211_get_qos_ctw(hdw);
		}
	} ewse {
		status->fwag |= WX_FWAG_8023;
	}

	if (!status->wcid || !ieee80211_is_data_qos(fc))
		wetuwn 0;

	status->aggw = unicast &&
		       !ieee80211_is_qos_nuwwfunc(fc);
	status->qos_ctw = qos_ctw;
	status->seqno = IEEE80211_SEQ_TO_SN(seq_ctww);

	wetuwn 0;
}

static u16
mt7615_mac_tx_wate_vaw(stwuct mt7615_dev *dev,
		       stwuct mt76_phy *mphy,
		       const stwuct ieee80211_tx_wate *wate,
		       boow stbc, u8 *bw)
{
	u8 phy, nss, wate_idx;
	u16 watevaw = 0;

	*bw = 0;

	if (wate->fwags & IEEE80211_TX_WC_VHT_MCS) {
		wate_idx = ieee80211_wate_get_vht_mcs(wate);
		nss = ieee80211_wate_get_vht_nss(wate);
		phy = MT_PHY_TYPE_VHT;
		if (wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			*bw = 1;
		ewse if (wate->fwags & IEEE80211_TX_WC_80_MHZ_WIDTH)
			*bw = 2;
		ewse if (wate->fwags & IEEE80211_TX_WC_160_MHZ_WIDTH)
			*bw = 3;
	} ewse if (wate->fwags & IEEE80211_TX_WC_MCS) {
		wate_idx = wate->idx;
		nss = 1 + (wate->idx >> 3);
		phy = MT_PHY_TYPE_HT;
		if (wate->fwags & IEEE80211_TX_WC_GWEEN_FIEWD)
			phy = MT_PHY_TYPE_HT_GF;
		if (wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			*bw = 1;
	} ewse {
		const stwuct ieee80211_wate *w;
		int band = mphy->chandef.chan->band;
		u16 vaw;

		nss = 1;
		w = &mphy->hw->wiphy->bands[band]->bitwates[wate->idx];
		if (wate->fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
			vaw = w->hw_vawue_showt;
		ewse
			vaw = w->hw_vawue;

		phy = vaw >> 8;
		wate_idx = vaw & 0xff;
	}

	if (stbc && nss == 1) {
		nss++;
		watevaw |= MT_TX_WATE_STBC;
	}

	watevaw |= (FIEWD_PWEP(MT_TX_WATE_IDX, wate_idx) |
		    FIEWD_PWEP(MT_TX_WATE_MODE, phy) |
		    FIEWD_PWEP(MT_TX_WATE_NSS, nss - 1));

	wetuwn watevaw;
}

int mt7615_mac_wwite_txwi(stwuct mt7615_dev *dev, __we32 *txwi,
			  stwuct sk_buff *skb, stwuct mt76_wcid *wcid,
			  stwuct ieee80211_sta *sta, int pid,
			  stwuct ieee80211_key_conf *key,
			  enum mt76_txq_id qid, boow beacon)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	u8 fc_type, fc_stype, p_fmt, q_idx, omac_idx = 0, wmm_idx = 0;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_tx_wate *wate = &info->contwow.wates[0];
	u8 phy_idx = (info->hw_queue & MT_TX_HW_QUEUE_PHY) >> 2;
	boow muwticast = is_muwticast_ethew_addw(hdw->addw1);
	stwuct ieee80211_vif *vif = info->contwow.vif;
	boow is_mmio = mt76_is_mmio(&dev->mt76);
	u32 vaw, sz_txd = is_mmio ? MT_TXD_SIZE : MT_USB_TXD_SIZE;
	stwuct mt76_phy *mphy = &dev->mphy;
	__we16 fc = hdw->fwame_contwow;
	int tx_count = 8;
	u16 seqno = 0;

	if (vif) {
		stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;

		omac_idx = mvif->omac_idx;
		wmm_idx = mvif->wmm_idx;
	}

	if (sta) {
		stwuct mt7615_sta *msta = (stwuct mt7615_sta *)sta->dwv_pwiv;

		tx_count = msta->wate_count;
	}

	if (phy_idx && dev->mt76.phys[MT_BAND1])
		mphy = dev->mt76.phys[MT_BAND1];

	fc_type = (we16_to_cpu(fc) & IEEE80211_FCTW_FTYPE) >> 2;
	fc_stype = (we16_to_cpu(fc) & IEEE80211_FCTW_STYPE) >> 4;

	if (beacon) {
		p_fmt = MT_TX_TYPE_FW;
		q_idx = phy_idx ? MT_WMAC_BCN1 : MT_WMAC_BCN0;
	} ewse if (qid >= MT_TXQ_PSD) {
		p_fmt = is_mmio ? MT_TX_TYPE_CT : MT_TX_TYPE_SF;
		q_idx = phy_idx ? MT_WMAC_AWTX1 : MT_WMAC_AWTX0;
	} ewse {
		p_fmt = is_mmio ? MT_TX_TYPE_CT : MT_TX_TYPE_SF;
		q_idx = wmm_idx * MT7615_MAX_WMM_SETS +
			mt7615_wmac_mapping(dev, skb_get_queue_mapping(skb));
	}

	vaw = FIEWD_PWEP(MT_TXD0_TX_BYTES, skb->wen + sz_txd) |
	      FIEWD_PWEP(MT_TXD0_P_IDX, MT_TX_POWT_IDX_WMAC) |
	      FIEWD_PWEP(MT_TXD0_Q_IDX, q_idx);
	txwi[0] = cpu_to_we32(vaw);

	vaw = MT_TXD1_WONG_FOWMAT |
	      FIEWD_PWEP(MT_TXD1_WWAN_IDX, wcid->idx) |
	      FIEWD_PWEP(MT_TXD1_HDW_FOWMAT, MT_HDW_FOWMAT_802_11) |
	      FIEWD_PWEP(MT_TXD1_HDW_INFO,
			 ieee80211_get_hdwwen_fwom_skb(skb) / 2) |
	      FIEWD_PWEP(MT_TXD1_TID,
			 skb->pwiowity & IEEE80211_QOS_CTW_TID_MASK) |
	      FIEWD_PWEP(MT_TXD1_PKT_FMT, p_fmt) |
	      FIEWD_PWEP(MT_TXD1_OWN_MAC, omac_idx);
	txwi[1] = cpu_to_we32(vaw);

	vaw = FIEWD_PWEP(MT_TXD2_FWAME_TYPE, fc_type) |
	      FIEWD_PWEP(MT_TXD2_SUB_TYPE, fc_stype) |
	      FIEWD_PWEP(MT_TXD2_MUWTICAST, muwticast);
	if (key) {
		if (muwticast && ieee80211_is_wobust_mgmt_fwame(skb) &&
		    key->ciphew == WWAN_CIPHEW_SUITE_AES_CMAC) {
			vaw |= MT_TXD2_BIP;
			txwi[3] = 0;
		} ewse {
			txwi[3] = cpu_to_we32(MT_TXD3_PWOTECT_FWAME);
		}
	} ewse {
		txwi[3] = 0;
	}
	txwi[2] = cpu_to_we32(vaw);

	if (!(info->fwags & IEEE80211_TX_CTW_AMPDU))
		txwi[2] |= cpu_to_we32(MT_TXD2_BA_DISABWE);

	txwi[4] = 0;
	txwi[6] = 0;

	if (wate->idx >= 0 && wate->count &&
	    !(info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE)) {
		boow stbc = info->fwags & IEEE80211_TX_CTW_STBC;
		u8 bw;
		u16 watevaw = mt7615_mac_tx_wate_vaw(dev, mphy, wate, stbc,
						     &bw);

		txwi[2] |= cpu_to_we32(MT_TXD2_FIX_WATE);

		vaw = MT_TXD6_FIXED_BW |
		      FIEWD_PWEP(MT_TXD6_BW, bw) |
		      FIEWD_PWEP(MT_TXD6_TX_WATE, watevaw);
		txwi[6] |= cpu_to_we32(vaw);

		if (wate->fwags & IEEE80211_TX_WC_SHOWT_GI)
			txwi[6] |= cpu_to_we32(MT_TXD6_SGI);

		if (info->fwags & IEEE80211_TX_CTW_WDPC)
			txwi[6] |= cpu_to_we32(MT_TXD6_WDPC);

		if (!(wate->fwags & (IEEE80211_TX_WC_MCS |
				     IEEE80211_TX_WC_VHT_MCS)))
			txwi[2] |= cpu_to_we32(MT_TXD2_BA_DISABWE);

		tx_count = wate->count;
	}

	if (!ieee80211_is_beacon(fc)) {
		stwuct ieee80211_hw *hw = mt76_hw(dev);

		vaw = MT_TXD5_TX_STATUS_HOST | FIEWD_PWEP(MT_TXD5_PID, pid);
		if (!ieee80211_hw_check(hw, SUPPOWTS_PS))
			vaw |= MT_TXD5_SW_POWEW_MGMT;
		txwi[5] = cpu_to_we32(vaw);
	} ewse {
		txwi[5] = 0;
		/* use maximum tx count fow beacons */
		tx_count = 0x1f;
	}

	vaw = FIEWD_PWEP(MT_TXD3_WEM_TX_COUNT, tx_count);
	if (info->fwags & IEEE80211_TX_CTW_INJECTED) {
		seqno = we16_to_cpu(hdw->seq_ctww);

		if (ieee80211_is_back_weq(hdw->fwame_contwow)) {
			stwuct ieee80211_baw *baw;

			baw = (stwuct ieee80211_baw *)skb->data;
			seqno = we16_to_cpu(baw->stawt_seq_num);
		}

		vaw |= MT_TXD3_SN_VAWID |
		       FIEWD_PWEP(MT_TXD3_SEQ, IEEE80211_SEQ_TO_SN(seqno));
	}

	txwi[3] |= cpu_to_we32(vaw);

	if (info->fwags & IEEE80211_TX_CTW_NO_ACK)
		txwi[3] |= cpu_to_we32(MT_TXD3_NO_ACK);

	vaw = FIEWD_PWEP(MT_TXD7_TYPE, fc_type) |
	      FIEWD_PWEP(MT_TXD7_SUB_TYPE, fc_stype) |
	      FIEWD_PWEP(MT_TXD7_SPE_IDX, 0x18);
	txwi[7] = cpu_to_we32(vaw);
	if (!is_mmio) {
		vaw = FIEWD_PWEP(MT_TXD8_W_TYPE, fc_type) |
		      FIEWD_PWEP(MT_TXD8_W_SUB_TYPE, fc_stype);
		txwi[8] = cpu_to_we32(vaw);
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt7615_mac_wwite_txwi);

boow mt7615_mac_wtbw_update(stwuct mt7615_dev *dev, int idx, u32 mask)
{
	mt76_wmw(dev, MT_WTBW_UPDATE, MT_WTBW_UPDATE_WWAN_IDX,
		 FIEWD_PWEP(MT_WTBW_UPDATE_WWAN_IDX, idx) | mask);

	wetuwn mt76_poww(dev, MT_WTBW_UPDATE, MT_WTBW_UPDATE_BUSY,
			 0, 5000);
}

void mt7615_mac_sta_poww(stwuct mt7615_dev *dev)
{
	static const u8 ac_to_tid[4] = {
		[IEEE80211_AC_BE] = 0,
		[IEEE80211_AC_BK] = 1,
		[IEEE80211_AC_VI] = 4,
		[IEEE80211_AC_VO] = 6
	};
	static const u8 hw_queue_map[] = {
		[IEEE80211_AC_BK] = 0,
		[IEEE80211_AC_BE] = 1,
		[IEEE80211_AC_VI] = 2,
		[IEEE80211_AC_VO] = 3,
	};
	stwuct ieee80211_sta *sta;
	stwuct mt7615_sta *msta;
	u32 addw, tx_time[4], wx_time[4];
	stwuct wist_head sta_poww_wist;
	int i;

	INIT_WIST_HEAD(&sta_poww_wist);
	spin_wock_bh(&dev->mt76.sta_poww_wock);
	wist_spwice_init(&dev->mt76.sta_poww_wist, &sta_poww_wist);
	spin_unwock_bh(&dev->mt76.sta_poww_wock);

	whiwe (!wist_empty(&sta_poww_wist)) {
		boow cweaw = fawse;

		msta = wist_fiwst_entwy(&sta_poww_wist, stwuct mt7615_sta,
					wcid.poww_wist);

		spin_wock_bh(&dev->mt76.sta_poww_wock);
		wist_dew_init(&msta->wcid.poww_wist);
		spin_unwock_bh(&dev->mt76.sta_poww_wock);

		addw = mt7615_mac_wtbw_addw(dev, msta->wcid.idx) + 19 * 4;

		fow (i = 0; i < 4; i++, addw += 8) {
			u32 tx_wast = msta->aiwtime_ac[i];
			u32 wx_wast = msta->aiwtime_ac[i + 4];

			msta->aiwtime_ac[i] = mt76_ww(dev, addw);
			msta->aiwtime_ac[i + 4] = mt76_ww(dev, addw + 4);
			tx_time[i] = msta->aiwtime_ac[i] - tx_wast;
			wx_time[i] = msta->aiwtime_ac[i + 4] - wx_wast;

			if ((tx_wast | wx_wast) & BIT(30))
				cweaw = twue;
		}

		if (cweaw) {
			mt7615_mac_wtbw_update(dev, msta->wcid.idx,
					       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);
			memset(msta->aiwtime_ac, 0, sizeof(msta->aiwtime_ac));
		}

		if (!msta->wcid.sta)
			continue;

		sta = containew_of((void *)msta, stwuct ieee80211_sta,
				   dwv_pwiv);
		fow (i = 0; i < 4; i++) {
			u32 tx_cuw = tx_time[i];
			u32 wx_cuw = wx_time[hw_queue_map[i]];
			u8 tid = ac_to_tid[i];

			if (!tx_cuw && !wx_cuw)
				continue;

			ieee80211_sta_wegistew_aiwtime(sta, tid, tx_cuw,
						       wx_cuw);
		}
	}
}
EXPOWT_SYMBOW_GPW(mt7615_mac_sta_poww);

static void
mt7615_mac_update_wate_desc(stwuct mt7615_phy *phy, stwuct mt7615_sta *sta,
			    stwuct ieee80211_tx_wate *pwobe_wate,
			    stwuct ieee80211_tx_wate *wates,
			    stwuct mt7615_wate_desc *wd)
{
	stwuct mt7615_dev *dev = phy->dev;
	stwuct mt76_phy *mphy = phy->mt76;
	stwuct ieee80211_tx_wate *wef;
	boow wateset, stbc = fawse;
	int n_wates = sta->n_wates;
	u8 bw, bw_pwev;
	int i, j;

	fow (i = n_wates; i < 4; i++)
		wates[i] = wates[n_wates - 1];

	wateset = !(sta->wate_set_tsf & BIT(0));
	memcpy(sta->wateset[wateset].wates, wates,
	       sizeof(sta->wateset[wateset].wates));
	if (pwobe_wate) {
		sta->wateset[wateset].pwobe_wate = *pwobe_wate;
		wef = &sta->wateset[wateset].pwobe_wate;
	} ewse {
		sta->wateset[wateset].pwobe_wate.idx = -1;
		wef = &sta->wateset[wateset].wates[0];
	}

	wates = sta->wateset[wateset].wates;
	fow (i = 0; i < AWWAY_SIZE(sta->wateset[wateset].wates); i++) {
		/*
		 * We don't suppowt switching between showt and wong GI
		 * within the wate set. Fow accuwate tx status wepowting, we
		 * need to make suwe that fwags match.
		 * Fow impwoved pewfowmance, avoid dupwicate entwies by
		 * decwementing the MCS index if necessawy
		 */
		if ((wef->fwags ^ wates[i].fwags) & IEEE80211_TX_WC_SHOWT_GI)
			wates[i].fwags ^= IEEE80211_TX_WC_SHOWT_GI;

		fow (j = 0; j < i; j++) {
			if (wates[i].idx != wates[j].idx)
				continue;
			if ((wates[i].fwags ^ wates[j].fwags) &
			    (IEEE80211_TX_WC_40_MHZ_WIDTH |
			     IEEE80211_TX_WC_80_MHZ_WIDTH |
			     IEEE80211_TX_WC_160_MHZ_WIDTH))
				continue;

			if (!wates[i].idx)
				continue;

			wates[i].idx--;
		}
	}

	wd->vaw[0] = mt7615_mac_tx_wate_vaw(dev, mphy, &wates[0], stbc, &bw);
	bw_pwev = bw;

	if (pwobe_wate) {
		wd->pwobe_vaw = mt7615_mac_tx_wate_vaw(dev, mphy, pwobe_wate,
						       stbc, &bw);
		if (bw)
			wd->bw_idx = 1;
		ewse
			bw_pwev = 0;
	} ewse {
		wd->pwobe_vaw = wd->vaw[0];
	}

	wd->vaw[1] = mt7615_mac_tx_wate_vaw(dev, mphy, &wates[1], stbc, &bw);
	if (bw_pwev) {
		wd->bw_idx = 3;
		bw_pwev = bw;
	}

	wd->vaw[2] = mt7615_mac_tx_wate_vaw(dev, mphy, &wates[2], stbc, &bw);
	if (bw_pwev) {
		wd->bw_idx = 5;
		bw_pwev = bw;
	}

	wd->vaw[3] = mt7615_mac_tx_wate_vaw(dev, mphy, &wates[3], stbc, &bw);
	if (bw_pwev)
		wd->bw_idx = 7;

	wd->wateset = wateset;
	wd->bw = bw;
}

static int
mt7615_mac_queue_wate_update(stwuct mt7615_phy *phy, stwuct mt7615_sta *sta,
			     stwuct ieee80211_tx_wate *pwobe_wate,
			     stwuct ieee80211_tx_wate *wates)
{
	stwuct mt7615_dev *dev = phy->dev;
	stwuct mt7615_wtbw_wate_desc *wwd;

	if (wowk_pending(&dev->wate_wowk))
		wetuwn -EBUSY;

	wwd = kzawwoc(sizeof(*wwd), GFP_ATOMIC);
	if (!wwd)
		wetuwn -ENOMEM;

	wwd->sta = sta;
	mt7615_mac_update_wate_desc(phy, sta, pwobe_wate, wates,
				    &wwd->wate);
	wist_add_taiw(&wwd->node, &dev->wwd_head);
	queue_wowk(dev->mt76.wq, &dev->wate_wowk);

	wetuwn 0;
}

u32 mt7615_mac_get_sta_tid_sn(stwuct mt7615_dev *dev, int wcid, u8 tid)
{
	u32 addw, vaw, vaw2;
	u8 offset;

	addw = mt7615_mac_wtbw_addw(dev, wcid) + 11 * 4;

	offset = tid * 12;
	addw += 4 * (offset / 32);
	offset %= 32;

	vaw = mt76_ww(dev, addw);
	vaw >>= offset;

	if (offset > 20) {
		addw += 4;
		vaw2 = mt76_ww(dev, addw);
		vaw |= vaw2 << (32 - offset);
	}

	wetuwn vaw & GENMASK(11, 0);
}

void mt7615_mac_set_wates(stwuct mt7615_phy *phy, stwuct mt7615_sta *sta,
			  stwuct ieee80211_tx_wate *pwobe_wate,
			  stwuct ieee80211_tx_wate *wates)
{
	int wcid = sta->wcid.idx, n_wates = sta->n_wates;
	stwuct mt7615_dev *dev = phy->dev;
	stwuct mt7615_wate_desc wd;
	u32 w5, w27, addw;
	u16 idx = sta->vif->mt76.omac_idx;

	if (!mt76_is_mmio(&dev->mt76)) {
		mt7615_mac_queue_wate_update(phy, sta, pwobe_wate, wates);
		wetuwn;
	}

	if (!mt76_poww(dev, MT_WTBW_UPDATE, MT_WTBW_UPDATE_BUSY, 0, 5000))
		wetuwn;

	memset(&wd, 0, sizeof(stwuct mt7615_wate_desc));
	mt7615_mac_update_wate_desc(phy, sta, pwobe_wate, wates, &wd);

	addw = mt7615_mac_wtbw_addw(dev, wcid);
	w27 = mt76_ww(dev, addw + 27 * 4);
	w27 &= ~MT_WTBW_W27_CC_BW_SEW;
	w27 |= FIEWD_PWEP(MT_WTBW_W27_CC_BW_SEW, wd.bw);

	w5 = mt76_ww(dev, addw + 5 * 4);
	w5 &= ~(MT_WTBW_W5_BW_CAP | MT_WTBW_W5_CHANGE_BW_WATE |
		MT_WTBW_W5_MPDU_OK_COUNT |
		MT_WTBW_W5_MPDU_FAIW_COUNT |
		MT_WTBW_W5_WATE_IDX);
	w5 |= FIEWD_PWEP(MT_WTBW_W5_BW_CAP, wd.bw) |
	      FIEWD_PWEP(MT_WTBW_W5_CHANGE_BW_WATE,
			 wd.bw_idx ? wd.bw_idx - 1 : 7);

	mt76_ww(dev, MT_WTBW_WIUCW0, w5);

	mt76_ww(dev, MT_WTBW_WIUCW1,
		FIEWD_PWEP(MT_WTBW_WIUCW1_WATE0, wd.pwobe_vaw) |
		FIEWD_PWEP(MT_WTBW_WIUCW1_WATE1, wd.vaw[0]) |
		FIEWD_PWEP(MT_WTBW_WIUCW1_WATE2_WO, wd.vaw[1]));

	mt76_ww(dev, MT_WTBW_WIUCW2,
		FIEWD_PWEP(MT_WTBW_WIUCW2_WATE2_HI, wd.vaw[1] >> 8) |
		FIEWD_PWEP(MT_WTBW_WIUCW2_WATE3, wd.vaw[1]) |
		FIEWD_PWEP(MT_WTBW_WIUCW2_WATE4, wd.vaw[2]) |
		FIEWD_PWEP(MT_WTBW_WIUCW2_WATE5_WO, wd.vaw[2]));

	mt76_ww(dev, MT_WTBW_WIUCW3,
		FIEWD_PWEP(MT_WTBW_WIUCW3_WATE5_HI, wd.vaw[2] >> 4) |
		FIEWD_PWEP(MT_WTBW_WIUCW3_WATE6, wd.vaw[3]) |
		FIEWD_PWEP(MT_WTBW_WIUCW3_WATE7, wd.vaw[3]));

	mt76_ww(dev, MT_WTBW_UPDATE,
		FIEWD_PWEP(MT_WTBW_UPDATE_WWAN_IDX, wcid) |
		MT_WTBW_UPDATE_WATE_UPDATE |
		MT_WTBW_UPDATE_TX_COUNT_CWEAW);

	mt76_ww(dev, addw + 27 * 4, w27);

	idx = idx > HW_BSSID_MAX ? HW_BSSID_0 : idx;
	addw = idx > 1 ? MT_WPON_TCW2(idx): MT_WPON_TCW0(idx);

	mt76_wmw(dev, addw, MT_WPON_TCW_MODE, MT_WPON_TCW_WEAD); /* TSF wead */
	sta->wate_set_tsf = mt76_ww(dev, MT_WPON_UTTW0) & ~BIT(0);
	sta->wate_set_tsf |= wd.wateset;

	if (!(sta->wcid.tx_info & MT_WCID_TX_INFO_SET))
		mt76_poww(dev, MT_WTBW_UPDATE, MT_WTBW_UPDATE_BUSY, 0, 5000);

	sta->wate_count = 2 * MT7615_WATE_WETWY * n_wates;
	sta->wcid.tx_info |= MT_WCID_TX_INFO_SET;
	sta->wate_pwobe = !!pwobe_wate;
}
EXPOWT_SYMBOW_GPW(mt7615_mac_set_wates);

void mt7615_mac_enabwe_wtscts(stwuct mt7615_dev *dev,
			      stwuct ieee80211_vif *vif, boow enabwe)
{
	stwuct mt7615_vif *mvif = (stwuct mt7615_vif *)vif->dwv_pwiv;
	u32 addw;

	addw = mt7615_mac_wtbw_addw(dev, mvif->sta.wcid.idx) + 3 * 4;

	if (enabwe)
		mt76_set(dev, addw, MT_WTBW_W3_WTS);
	ewse
		mt76_cweaw(dev, addw, MT_WTBW_W3_WTS);
}
EXPOWT_SYMBOW_GPW(mt7615_mac_enabwe_wtscts);

static int
mt7615_mac_wtbw_update_key(stwuct mt7615_dev *dev, stwuct mt76_wcid *wcid,
			   stwuct ieee80211_key_conf *key,
			   enum mt76_ciphew_type ciphew, u16 ciphew_mask)
{
	u32 addw = mt7615_mac_wtbw_addw(dev, wcid->idx) + 30 * 4;
	u8 data[32] = {};

	if (key->keywen > sizeof(data))
		wetuwn -EINVAW;

	mt76_ww_copy(dev, addw, data, sizeof(data));
	if (ciphew == MT_CIPHEW_TKIP) {
		/* Wx/Tx MIC keys awe swapped */
		memcpy(data, key->key, 16);
		memcpy(data + 16, key->key + 24, 8);
		memcpy(data + 24, key->key + 16, 8);
	} ewse {
		if (ciphew_mask == BIT(ciphew))
			memcpy(data, key->key, key->keywen);
		ewse if (ciphew != MT_CIPHEW_BIP_CMAC_128)
			memcpy(data, key->key, 16);
		if (ciphew == MT_CIPHEW_BIP_CMAC_128)
			memcpy(data + 16, key->key, 16);
	}

	mt76_ww_copy(dev, addw, data, sizeof(data));

	wetuwn 0;
}

static int
mt7615_mac_wtbw_update_pk(stwuct mt7615_dev *dev, stwuct mt76_wcid *wcid,
			  enum mt76_ciphew_type ciphew, u16 ciphew_mask,
			  int keyidx)
{
	u32 addw = mt7615_mac_wtbw_addw(dev, wcid->idx), w0, w1;

	if (!mt76_poww(dev, MT_WTBW_UPDATE, MT_WTBW_UPDATE_BUSY, 0, 5000))
		wetuwn -ETIMEDOUT;

	w0 = mt76_ww(dev, addw);
	w1 = mt76_ww(dev, addw + 4);

	if (ciphew_mask)
		w0 |= MT_WTBW_W0_WX_KEY_VAWID;
	ewse
		w0 &= ~(MT_WTBW_W0_WX_KEY_VAWID | MT_WTBW_W0_KEY_IDX);
	if (ciphew_mask & BIT(MT_CIPHEW_BIP_CMAC_128))
		w0 |= MT_WTBW_W0_WX_IK_VAWID;
	ewse
		w0 &= ~MT_WTBW_W0_WX_IK_VAWID;

	if (ciphew != MT_CIPHEW_BIP_CMAC_128 || ciphew_mask == BIT(ciphew)) {
		w0 &= ~MT_WTBW_W0_KEY_IDX;
		w0 |= FIEWD_PWEP(MT_WTBW_W0_KEY_IDX, keyidx);
	}

	mt76_ww(dev, MT_WTBW_WICW0, w0);
	mt76_ww(dev, MT_WTBW_WICW1, w1);

	if (!mt7615_mac_wtbw_update(dev, wcid->idx,
				    MT_WTBW_UPDATE_WXINFO_UPDATE))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static void
mt7615_mac_wtbw_update_ciphew(stwuct mt7615_dev *dev, stwuct mt76_wcid *wcid,
			      enum mt76_ciphew_type ciphew, u16 ciphew_mask)
{
	u32 addw = mt7615_mac_wtbw_addw(dev, wcid->idx);

	if (ciphew == MT_CIPHEW_BIP_CMAC_128 &&
	    ciphew_mask & ~BIT(MT_CIPHEW_BIP_CMAC_128))
		wetuwn;

	mt76_wmw(dev, addw + 2 * 4, MT_WTBW_W2_KEY_TYPE,
		 FIEWD_PWEP(MT_WTBW_W2_KEY_TYPE, ciphew));
}

int __mt7615_mac_wtbw_set_key(stwuct mt7615_dev *dev,
			      stwuct mt76_wcid *wcid,
			      stwuct ieee80211_key_conf *key)
{
	enum mt76_ciphew_type ciphew;
	u16 ciphew_mask = wcid->ciphew;
	int eww;

	ciphew = mt7615_mac_get_ciphew(key->ciphew);
	if (ciphew == MT_CIPHEW_NONE)
		wetuwn -EOPNOTSUPP;

	ciphew_mask |= BIT(ciphew);
	mt7615_mac_wtbw_update_ciphew(dev, wcid, ciphew, ciphew_mask);
	eww = mt7615_mac_wtbw_update_key(dev, wcid, key, ciphew, ciphew_mask);
	if (eww < 0)
		wetuwn eww;

	eww = mt7615_mac_wtbw_update_pk(dev, wcid, ciphew, ciphew_mask,
					key->keyidx);
	if (eww < 0)
		wetuwn eww;

	wcid->ciphew = ciphew_mask;

	wetuwn 0;
}

int mt7615_mac_wtbw_set_key(stwuct mt7615_dev *dev,
			    stwuct mt76_wcid *wcid,
			    stwuct ieee80211_key_conf *key)
{
	int eww;

	spin_wock_bh(&dev->mt76.wock);
	eww = __mt7615_mac_wtbw_set_key(dev, wcid, key);
	spin_unwock_bh(&dev->mt76.wock);

	wetuwn eww;
}

static boow mt7615_fiww_txs(stwuct mt7615_dev *dev, stwuct mt7615_sta *sta,
			    stwuct ieee80211_tx_info *info, __we32 *txs_data)
{
	stwuct ieee80211_suppowted_band *sband;
	stwuct mt7615_wate_set *ws;
	stwuct mt76_phy *mphy;
	int fiwst_idx = 0, wast_idx;
	int i, idx, count;
	boow fixed_wate, ack_timeout;
	boow ampdu, cck = fawse;
	boow ws_idx;
	u32 wate_set_tsf;
	u32 finaw_wate, finaw_wate_fwags, finaw_nss, txs;

	txs = we32_to_cpu(txs_data[1]);
	ampdu = txs & MT_TXS1_AMPDU;

	txs = we32_to_cpu(txs_data[3]);
	count = FIEWD_GET(MT_TXS3_TX_COUNT, txs);
	wast_idx = FIEWD_GET(MT_TXS3_WAST_TX_WATE, txs);

	txs = we32_to_cpu(txs_data[0]);
	fixed_wate = txs & MT_TXS0_FIXED_WATE;
	finaw_wate = FIEWD_GET(MT_TXS0_TX_WATE, txs);
	ack_timeout = txs & MT_TXS0_ACK_TIMEOUT;

	if (!ampdu && (txs & MT_TXS0_WTS_TIMEOUT))
		wetuwn fawse;

	if (txs & MT_TXS0_QUEUE_TIMEOUT)
		wetuwn fawse;

	if (!ack_timeout)
		info->fwags |= IEEE80211_TX_STAT_ACK;

	info->status.ampdu_wen = 1;
	info->status.ampdu_ack_wen = !!(info->fwags &
					IEEE80211_TX_STAT_ACK);

	if (ampdu || (info->fwags & IEEE80211_TX_CTW_AMPDU))
		info->fwags |= IEEE80211_TX_STAT_AMPDU | IEEE80211_TX_CTW_AMPDU;

	fiwst_idx = max_t(int, 0, wast_idx - (count - 1) / MT7615_WATE_WETWY);

	if (fixed_wate) {
		info->status.wates[0].count = count;
		i = 0;
		goto out;
	}

	wate_set_tsf = WEAD_ONCE(sta->wate_set_tsf);
	ws_idx = !((u32)(we32_get_bits(txs_data[4], MT_TXS4_F0_TIMESTAMP) -
			 wate_set_tsf) < 1000000);
	ws_idx ^= wate_set_tsf & BIT(0);
	ws = &sta->wateset[ws_idx];

	if (!fiwst_idx && ws->pwobe_wate.idx >= 0) {
		info->status.wates[0] = ws->pwobe_wate;

		spin_wock_bh(&dev->mt76.wock);
		if (sta->wate_pwobe) {
			stwuct mt7615_phy *phy = &dev->phy;

			if (sta->wcid.phy_idx && dev->mt76.phys[MT_BAND1])
				phy = dev->mt76.phys[MT_BAND1]->pwiv;

			mt7615_mac_set_wates(phy, sta, NUWW, sta->wates);
		}
		spin_unwock_bh(&dev->mt76.wock);
	} ewse {
		info->status.wates[0] = ws->wates[fiwst_idx / 2];
	}
	info->status.wates[0].count = 0;

	fow (i = 0, idx = fiwst_idx; count && idx <= wast_idx; idx++) {
		stwuct ieee80211_tx_wate *cuw_wate;
		int cuw_count;

		cuw_wate = &ws->wates[idx / 2];
		cuw_count = min_t(int, MT7615_WATE_WETWY, count);
		count -= cuw_count;

		if (idx && (cuw_wate->idx != info->status.wates[i].idx ||
			    cuw_wate->fwags != info->status.wates[i].fwags)) {
			i++;
			if (i == AWWAY_SIZE(info->status.wates)) {
				i--;
				bweak;
			}

			info->status.wates[i] = *cuw_wate;
			info->status.wates[i].count = 0;
		}

		info->status.wates[i].count += cuw_count;
	}

out:
	finaw_wate_fwags = info->status.wates[i].fwags;

	switch (FIEWD_GET(MT_TX_WATE_MODE, finaw_wate)) {
	case MT_PHY_TYPE_CCK:
		cck = twue;
		fawwthwough;
	case MT_PHY_TYPE_OFDM:
		mphy = &dev->mphy;
		if (sta->wcid.phy_idx && dev->mt76.phys[MT_BAND1])
			mphy = dev->mt76.phys[MT_BAND1];

		if (mphy->chandef.chan->band == NW80211_BAND_5GHZ)
			sband = &mphy->sband_5g.sband;
		ewse
			sband = &mphy->sband_2g.sband;
		finaw_wate &= MT_TX_WATE_IDX;
		finaw_wate = mt76_get_wate(&dev->mt76, sband, finaw_wate,
					   cck);
		finaw_wate_fwags = 0;
		bweak;
	case MT_PHY_TYPE_HT_GF:
	case MT_PHY_TYPE_HT:
		finaw_wate_fwags |= IEEE80211_TX_WC_MCS;
		finaw_wate &= MT_TX_WATE_IDX;
		if (finaw_wate > 31)
			wetuwn fawse;
		bweak;
	case MT_PHY_TYPE_VHT:
		finaw_nss = FIEWD_GET(MT_TX_WATE_NSS, finaw_wate);

		if ((finaw_wate & MT_TX_WATE_STBC) && finaw_nss)
			finaw_nss--;

		finaw_wate_fwags |= IEEE80211_TX_WC_VHT_MCS;
		finaw_wate = (finaw_wate & MT_TX_WATE_IDX) | (finaw_nss << 4);
		bweak;
	defauwt:
		wetuwn fawse;
	}

	info->status.wates[i].idx = finaw_wate;
	info->status.wates[i].fwags = finaw_wate_fwags;

	wetuwn twue;
}

static boow mt7615_mac_add_txs_skb(stwuct mt7615_dev *dev,
				   stwuct mt7615_sta *sta, int pid,
				   __we32 *txs_data)
{
	stwuct mt76_dev *mdev = &dev->mt76;
	stwuct sk_buff_head wist;
	stwuct sk_buff *skb;

	if (pid < MT_PACKET_ID_FIWST)
		wetuwn fawse;

	twace_mac_txdone(mdev, sta->wcid.idx, pid);

	mt76_tx_status_wock(mdev, &wist);
	skb = mt76_tx_status_skb_get(mdev, &sta->wcid, pid, &wist);
	if (skb) {
		stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

		if (!mt7615_fiww_txs(dev, sta, info, txs_data)) {
			info->status.wates[0].count = 0;
			info->status.wates[0].idx = -1;
		}

		mt76_tx_status_skb_done(mdev, skb, &wist);
	}
	mt76_tx_status_unwock(mdev, &wist);

	wetuwn !!skb;
}

static void mt7615_mac_add_txs(stwuct mt7615_dev *dev, void *data)
{
	stwuct ieee80211_tx_info info = {};
	stwuct ieee80211_sta *sta = NUWW;
	stwuct mt7615_sta *msta = NUWW;
	stwuct mt76_wcid *wcid;
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	__we32 *txs_data = data;
	u8 wcidx;
	u8 pid;

	pid = we32_get_bits(txs_data[0], MT_TXS0_PID);
	wcidx = we32_get_bits(txs_data[2], MT_TXS2_WCID);

	if (pid == MT_PACKET_ID_NO_ACK)
		wetuwn;

	if (wcidx >= MT7615_WTBW_SIZE)
		wetuwn;

	wcu_wead_wock();

	wcid = wcu_dewefewence(dev->mt76.wcid[wcidx]);
	if (!wcid)
		goto out;

	msta = containew_of(wcid, stwuct mt7615_sta, wcid);
	sta = wcid_to_sta(wcid);

	spin_wock_bh(&dev->mt76.sta_poww_wock);
	if (wist_empty(&msta->wcid.poww_wist))
		wist_add_taiw(&msta->wcid.poww_wist, &dev->mt76.sta_poww_wist);
	spin_unwock_bh(&dev->mt76.sta_poww_wock);

	if (mt7615_mac_add_txs_skb(dev, msta, pid, txs_data))
		goto out;

	if (wcidx >= MT7615_WTBW_STA || !sta)
		goto out;

	if (wcid->phy_idx && dev->mt76.phys[MT_BAND1])
		mphy = dev->mt76.phys[MT_BAND1];

	if (mt7615_fiww_txs(dev, msta, &info, txs_data)) {
		spin_wock_bh(&dev->mt76.wx_wock);
		ieee80211_tx_status_noskb(mphy->hw, sta, &info);
		spin_unwock_bh(&dev->mt76.wx_wock);
	}

out:
	wcu_wead_unwock();
}

static void
mt7615_txwi_fwee(stwuct mt7615_dev *dev, stwuct mt76_txwi_cache *txwi)
{
	stwuct mt76_dev *mdev = &dev->mt76;
	__we32 *txwi_data;
	u32 vaw;
	u8 wcid;

	mt76_connac_txp_skb_unmap(mdev, txwi);
	if (!txwi->skb)
		goto out;

	txwi_data = (__we32 *)mt76_get_txwi_ptw(mdev, txwi);
	vaw = we32_to_cpu(txwi_data[1]);
	wcid = FIEWD_GET(MT_TXD1_WWAN_IDX, vaw);
	mt76_tx_compwete_skb(mdev, wcid, txwi->skb);

out:
	txwi->skb = NUWW;
	mt76_put_txwi(mdev, txwi);
}

static void
mt7615_mac_tx_fwee_token(stwuct mt7615_dev *dev, u16 token)
{
	stwuct mt76_dev *mdev = &dev->mt76;
	stwuct mt76_txwi_cache *txwi;

	twace_mac_tx_fwee(dev, token);
	txwi = mt76_token_put(mdev, token);
	if (!txwi)
		wetuwn;

	mt7615_txwi_fwee(dev, txwi);
}

static void mt7615_mac_tx_fwee(stwuct mt7615_dev *dev, void *data, int wen)
{
	stwuct mt76_connac_tx_fwee *fwee = data;
	void *tx_token = data + sizeof(*fwee);
	void *end = data + wen;
	u8 i, count;

	mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[MT_TXQ_PSD], fawse);
	if (is_mt7615(&dev->mt76)) {
		mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[MT_TXQ_BE], fawse);
	} ewse {
		fow (i = 0; i < IEEE80211_NUM_ACS; i++)
			mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[i], fawse);
	}

	count = we16_get_bits(fwee->ctww, MT_TX_FWEE_MSDU_ID_CNT);
	if (is_mt7615(&dev->mt76)) {
		__we16 *token = tx_token;

		if (WAWN_ON_ONCE((void *)&token[count] > end))
			wetuwn;

		fow (i = 0; i < count; i++)
			mt7615_mac_tx_fwee_token(dev, we16_to_cpu(token[i]));
	} ewse {
		__we32 *token = tx_token;

		if (WAWN_ON_ONCE((void *)&token[count] > end))
			wetuwn;

		fow (i = 0; i < count; i++)
			mt7615_mac_tx_fwee_token(dev, we32_to_cpu(token[i]));
	}

	wcu_wead_wock();
	mt7615_mac_sta_poww(dev);
	wcu_wead_unwock();

	mt76_wowkew_scheduwe(&dev->mt76.tx_wowkew);
}

boow mt7615_wx_check(stwuct mt76_dev *mdev, void *data, int wen)
{
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);
	__we32 *wxd = (__we32 *)data;
	__we32 *end = (__we32 *)&wxd[wen / 4];
	enum wx_pkt_type type;

	type = we32_get_bits(wxd[0], MT_WXD0_PKT_TYPE);

	switch (type) {
	case PKT_TYPE_TXWX_NOTIFY:
		mt7615_mac_tx_fwee(dev, data, wen);
		wetuwn fawse;
	case PKT_TYPE_TXS:
		fow (wxd++; wxd + 7 <= end; wxd += 7)
			mt7615_mac_add_txs(dev, wxd);
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}
EXPOWT_SYMBOW_GPW(mt7615_wx_check);

void mt7615_queue_wx_skb(stwuct mt76_dev *mdev, enum mt76_wxq_id q,
			 stwuct sk_buff *skb, u32 *info)
{
	stwuct mt7615_dev *dev = containew_of(mdev, stwuct mt7615_dev, mt76);
	__we32 *wxd = (__we32 *)skb->data;
	__we32 *end = (__we32 *)&skb->data[skb->wen];
	enum wx_pkt_type type;
	u16 fwag;

	type = we32_get_bits(wxd[0], MT_WXD0_PKT_TYPE);
	fwag = we32_get_bits(wxd[0], MT_WXD0_PKT_FWAG);
	if (type == PKT_TYPE_WX_EVENT && fwag == 0x1)
		type = PKT_TYPE_NOWMAW_MCU;

	switch (type) {
	case PKT_TYPE_TXS:
		fow (wxd++; wxd + 7 <= end; wxd += 7)
			mt7615_mac_add_txs(dev, wxd);
		dev_kfwee_skb(skb);
		bweak;
	case PKT_TYPE_TXWX_NOTIFY:
		mt7615_mac_tx_fwee(dev, skb->data, skb->wen);
		dev_kfwee_skb(skb);
		bweak;
	case PKT_TYPE_WX_EVENT:
		mt7615_mcu_wx_event(dev, skb);
		bweak;
	case PKT_TYPE_NOWMAW_MCU:
	case PKT_TYPE_NOWMAW:
		if (!mt7615_mac_fiww_wx(dev, skb)) {
			mt76_wx(&dev->mt76, q, skb);
			wetuwn;
		}
		fawwthwough;
	defauwt:
		dev_kfwee_skb(skb);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(mt7615_queue_wx_skb);

static void
mt7615_mac_set_sensitivity(stwuct mt7615_phy *phy, int vaw, boow ofdm)
{
	stwuct mt7615_dev *dev = phy->dev;
	boow ext_phy = phy != &dev->phy;

	if (is_mt7663(&dev->mt76)) {
		if (ofdm)
			mt76_wmw(dev, MT7663_WF_PHY_MIN_PWI_PWW(ext_phy),
				 MT_WF_PHY_PD_OFDM_MASK(0),
				 MT_WF_PHY_PD_OFDM(0, vaw));
		ewse
			mt76_wmw(dev, MT7663_WF_PHY_WXTD_CCK_PD(ext_phy),
				 MT_WF_PHY_PD_CCK_MASK(ext_phy),
				 MT_WF_PHY_PD_CCK(ext_phy, vaw));
		wetuwn;
	}

	if (ofdm)
		mt76_wmw(dev, MT_WF_PHY_MIN_PWI_PWW(ext_phy),
			 MT_WF_PHY_PD_OFDM_MASK(ext_phy),
			 MT_WF_PHY_PD_OFDM(ext_phy, vaw));
	ewse
		mt76_wmw(dev, MT_WF_PHY_WXTD_CCK_PD(ext_phy),
			 MT_WF_PHY_PD_CCK_MASK(ext_phy),
			 MT_WF_PHY_PD_CCK(ext_phy, vaw));
}

static void
mt7615_mac_set_defauwt_sensitivity(stwuct mt7615_phy *phy)
{
	/* ofdm */
	mt7615_mac_set_sensitivity(phy, 0x13c, twue);
	/* cck */
	mt7615_mac_set_sensitivity(phy, 0x92, fawse);

	phy->ofdm_sensitivity = -98;
	phy->cck_sensitivity = -110;
	phy->wast_cca_adj = jiffies;
}

void mt7615_mac_set_scs(stwuct mt7615_phy *phy, boow enabwe)
{
	stwuct mt7615_dev *dev = phy->dev;
	boow ext_phy = phy != &dev->phy;
	u32 weg, mask;

	mt7615_mutex_acquiwe(dev);

	if (phy->scs_en == enabwe)
		goto out;

	if (is_mt7663(&dev->mt76)) {
		weg = MT7663_WF_PHY_MIN_PWI_PWW(ext_phy);
		mask = MT_WF_PHY_PD_BWK(0);
	} ewse {
		weg = MT_WF_PHY_MIN_PWI_PWW(ext_phy);
		mask = MT_WF_PHY_PD_BWK(ext_phy);
	}

	if (enabwe) {
		mt76_set(dev, weg, mask);
		if (is_mt7622(&dev->mt76)) {
			mt76_set(dev, MT_MIB_M0_MISC_CW(0), 0x7 << 8);
			mt76_set(dev, MT_MIB_M0_MISC_CW(0), 0x7);
		}
	} ewse {
		mt76_cweaw(dev, weg, mask);
	}

	mt7615_mac_set_defauwt_sensitivity(phy);
	phy->scs_en = enabwe;

out:
	mt7615_mutex_wewease(dev);
}

void mt7615_mac_enabwe_nf(stwuct mt7615_dev *dev, boow ext_phy)
{
	u32 wxtd, weg;

	if (is_mt7663(&dev->mt76))
		weg = MT7663_WF_PHY_W0_PHYMUX_5;
	ewse
		weg = MT_WF_PHY_W0_PHYMUX_5(ext_phy);

	if (ext_phy)
		wxtd = MT_WF_PHY_WXTD2(10);
	ewse
		wxtd = MT_WF_PHY_WXTD(12);

	mt76_set(dev, wxtd, BIT(18) | BIT(29));
	mt76_set(dev, weg, 0x5 << 12);
}

void mt7615_mac_cca_stats_weset(stwuct mt7615_phy *phy)
{
	stwuct mt7615_dev *dev = phy->dev;
	boow ext_phy = phy != &dev->phy;
	u32 weg;

	if (is_mt7663(&dev->mt76))
		weg = MT7663_WF_PHY_W0_PHYMUX_5;
	ewse
		weg = MT_WF_PHY_W0_PHYMUX_5(ext_phy);

	/* weset PD and MDWDY countews */
	mt76_cweaw(dev, weg, GENMASK(22, 20));
	mt76_set(dev, weg, BIT(22) | BIT(20));
}

static void
mt7615_mac_adjust_sensitivity(stwuct mt7615_phy *phy,
			      u32 wts_eww_wate, boow ofdm)
{
	stwuct mt7615_dev *dev = phy->dev;
	int fawse_cca = ofdm ? phy->fawse_cca_ofdm : phy->fawse_cca_cck;
	boow ext_phy = phy != &dev->phy;
	s16 def_th = ofdm ? -98 : -110;
	boow update = fawse;
	s8 *sensitivity;
	int signaw;

	sensitivity = ofdm ? &phy->ofdm_sensitivity : &phy->cck_sensitivity;
	signaw = mt76_get_min_avg_wssi(&dev->mt76, ext_phy);
	if (!signaw) {
		mt7615_mac_set_defauwt_sensitivity(phy);
		wetuwn;
	}

	signaw = min(signaw, -72);
	if (fawse_cca > 500) {
		if (wts_eww_wate > MT_FWAC(40, 100))
			wetuwn;

		/* decwease covewage */
		if (*sensitivity == def_th && signaw > -90) {
			*sensitivity = -90;
			update = twue;
		} ewse if (*sensitivity + 2 < signaw) {
			*sensitivity += 2;
			update = twue;
		}
	} ewse if ((fawse_cca > 0 && fawse_cca < 50) ||
		   wts_eww_wate > MT_FWAC(60, 100)) {
		/* incwease covewage */
		if (*sensitivity - 2 >= def_th) {
			*sensitivity -= 2;
			update = twue;
		}
	}

	if (*sensitivity > signaw) {
		*sensitivity = signaw;
		update = twue;
	}

	if (update) {
		u16 vaw = ofdm ? *sensitivity * 2 + 512 : *sensitivity + 256;

		mt7615_mac_set_sensitivity(phy, vaw, ofdm);
		phy->wast_cca_adj = jiffies;
	}
}

static void
mt7615_mac_scs_check(stwuct mt7615_phy *phy)
{
	stwuct mt7615_dev *dev = phy->dev;
	stwuct mib_stats *mib = &phy->mib;
	u32 vaw, wts_eww_wate = 0;
	u32 mdwdy_cck, mdwdy_ofdm, pd_cck, pd_ofdm;
	boow ext_phy = phy != &dev->phy;

	if (!phy->scs_en)
		wetuwn;

	if (is_mt7663(&dev->mt76))
		vaw = mt76_ww(dev, MT7663_WF_PHY_W0_PHYCTWW_STS0(ext_phy));
	ewse
		vaw = mt76_ww(dev, MT_WF_PHY_W0_PHYCTWW_STS0(ext_phy));
	pd_cck = FIEWD_GET(MT_WF_PHYCTWW_STAT_PD_CCK, vaw);
	pd_ofdm = FIEWD_GET(MT_WF_PHYCTWW_STAT_PD_OFDM, vaw);

	if (is_mt7663(&dev->mt76))
		vaw = mt76_ww(dev, MT7663_WF_PHY_W0_PHYCTWW_STS5(ext_phy));
	ewse
		vaw = mt76_ww(dev, MT_WF_PHY_W0_PHYCTWW_STS5(ext_phy));
	mdwdy_cck = FIEWD_GET(MT_WF_PHYCTWW_STAT_MDWDY_CCK, vaw);
	mdwdy_ofdm = FIEWD_GET(MT_WF_PHYCTWW_STAT_MDWDY_OFDM, vaw);

	phy->fawse_cca_ofdm = pd_ofdm - mdwdy_ofdm;
	phy->fawse_cca_cck = pd_cck - mdwdy_cck;
	mt7615_mac_cca_stats_weset(phy);

	if (mib->wts_cnt + mib->wts_wetwies_cnt)
		wts_eww_wate = MT_FWAC(mib->wts_wetwies_cnt,
				       mib->wts_cnt + mib->wts_wetwies_cnt);

	/* cck */
	mt7615_mac_adjust_sensitivity(phy, wts_eww_wate, fawse);
	/* ofdm */
	mt7615_mac_adjust_sensitivity(phy, wts_eww_wate, twue);

	if (time_aftew(jiffies, phy->wast_cca_adj + 10 * HZ))
		mt7615_mac_set_defauwt_sensitivity(phy);
}

static u8
mt7615_phy_get_nf(stwuct mt7615_dev *dev, int idx)
{
	static const u8 nf_powew[] = { 92, 89, 86, 83, 80, 75, 70, 65, 60, 55, 52 };
	u32 weg, vaw, sum = 0, n = 0;
	int i;

	if (is_mt7663(&dev->mt76))
		weg = MT7663_WF_PHY_WXTD(20);
	ewse
		weg = idx ? MT_WF_PHY_WXTD2(17) : MT_WF_PHY_WXTD(20);

	fow (i = 0; i < AWWAY_SIZE(nf_powew); i++, weg += 4) {
		vaw = mt76_ww(dev, weg);
		sum += vaw * nf_powew[i];
		n += vaw;
	}

	if (!n)
		wetuwn 0;

	wetuwn sum / n;
}

static void
mt7615_phy_update_channew(stwuct mt76_phy *mphy, int idx)
{
	stwuct mt7615_dev *dev = containew_of(mphy->dev, stwuct mt7615_dev, mt76);
	stwuct mt7615_phy *phy = mphy->pwiv;
	stwuct mt76_channew_state *state;
	u64 busy_time, tx_time, wx_time, obss_time;
	u32 obss_weg = idx ? MT_WF_WMAC_MIB_TIME6 : MT_WF_WMAC_MIB_TIME5;
	int nf;

	busy_time = mt76_get_fiewd(dev, MT_MIB_SDW9(idx),
				   MT_MIB_SDW9_BUSY_MASK);
	tx_time = mt76_get_fiewd(dev, MT_MIB_SDW36(idx),
				 MT_MIB_SDW36_TXTIME_MASK);
	wx_time = mt76_get_fiewd(dev, MT_MIB_SDW37(idx),
				 MT_MIB_SDW37_WXTIME_MASK);
	obss_time = mt76_get_fiewd(dev, obss_weg, MT_MIB_OBSSTIME_MASK);

	nf = mt7615_phy_get_nf(dev, idx);
	if (!phy->noise)
		phy->noise = nf << 4;
	ewse if (nf)
		phy->noise += nf - (phy->noise >> 4);

	state = mphy->chan_state;
	state->cc_busy += busy_time;
	state->cc_tx += tx_time;
	state->cc_wx += wx_time + obss_time;
	state->cc_bss_wx += wx_time;
	state->noise = -(phy->noise >> 4);
}

static void mt7615_update_suwvey(stwuct mt7615_dev *dev)
{
	stwuct mt76_dev *mdev = &dev->mt76;
	stwuct mt76_phy *mphy_ext = mdev->phys[MT_BAND1];
	ktime_t cuw_time;

	/* MT7615 can onwy update both phys simuwtaneouswy
	 * since some weistews awe shawed acwoss bands.
	 */

	mt7615_phy_update_channew(&mdev->phy, 0);
	if (mphy_ext)
		mt7615_phy_update_channew(mphy_ext, 1);

	cuw_time = ktime_get_boottime();

	mt76_update_suwvey_active_time(&mdev->phy, cuw_time);
	if (mphy_ext)
		mt76_update_suwvey_active_time(mphy_ext, cuw_time);

	/* weset obss aiwtime */
	mt76_set(dev, MT_WF_WMAC_MIB_TIME0, MT_WF_WMAC_MIB_WXTIME_CWW);
}

void mt7615_update_channew(stwuct mt76_phy *mphy)
{
	stwuct mt7615_dev *dev = containew_of(mphy->dev, stwuct mt7615_dev, mt76);

	if (mt76_connac_pm_wake(&dev->mphy, &dev->pm))
		wetuwn;

	mt7615_update_suwvey(dev);
	mt76_connac_powew_save_sched(&dev->mphy, &dev->pm);
}
EXPOWT_SYMBOW_GPW(mt7615_update_channew);

static void
mt7615_mac_update_mib_stats(stwuct mt7615_phy *phy)
{
	stwuct mt7615_dev *dev = phy->dev;
	stwuct mib_stats *mib = &phy->mib;
	boow ext_phy = phy != &dev->phy;
	int i, aggw = 0;
	u32 vaw, vaw2;

	mib->fcs_eww_cnt += mt76_get_fiewd(dev, MT_MIB_SDW3(ext_phy),
					   MT_MIB_SDW3_FCS_EWW_MASK);

	vaw = mt76_get_fiewd(dev, MT_MIB_SDW14(ext_phy),
			     MT_MIB_AMPDU_MPDU_COUNT);
	if (vaw) {
		vaw2 = mt76_get_fiewd(dev, MT_MIB_SDW15(ext_phy),
				      MT_MIB_AMPDU_ACK_COUNT);
		mib->aggw_pew = 1000 * (vaw - vaw2) / vaw;
	}

	fow (i = 0; i < 4; i++) {
		vaw = mt76_ww(dev, MT_MIB_MB_SDW1(ext_phy, i));
		mib->ba_miss_cnt += FIEWD_GET(MT_MIB_BA_MISS_COUNT_MASK, vaw);
		mib->ack_faiw_cnt += FIEWD_GET(MT_MIB_ACK_FAIW_COUNT_MASK,
					       vaw);

		vaw = mt76_ww(dev, MT_MIB_MB_SDW0(ext_phy, i));
		mib->wts_cnt += FIEWD_GET(MT_MIB_WTS_COUNT_MASK, vaw);
		mib->wts_wetwies_cnt += FIEWD_GET(MT_MIB_WTS_WETWIES_COUNT_MASK,
						  vaw);

		vaw = mt76_ww(dev, MT_TX_AGG_CNT(ext_phy, i));
		phy->mt76->aggw_stats[aggw++] += vaw & 0xffff;
		phy->mt76->aggw_stats[aggw++] += vaw >> 16;
	}
}

void mt7615_pm_wake_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7615_dev *dev;
	stwuct mt76_phy *mphy;

	dev = (stwuct mt7615_dev *)containew_of(wowk, stwuct mt7615_dev,
						pm.wake_wowk);
	mphy = dev->phy.mt76;

	if (!mt7615_mcu_set_dwv_ctww(dev)) {
		stwuct mt76_dev *mdev = &dev->mt76;
		int i;

		if (mt76_is_sdio(mdev)) {
			mt76_connac_pm_dequeue_skbs(mphy, &dev->pm);
			mt76_wowkew_scheduwe(&mdev->sdio.txwx_wowkew);
		} ewse {
			wocaw_bh_disabwe();
			mt76_fow_each_q_wx(mdev, i)
				napi_scheduwe(&mdev->napi[i]);
			wocaw_bh_enabwe();
			mt76_connac_pm_dequeue_skbs(mphy, &dev->pm);
			mt76_queue_tx_cweanup(dev, mdev->q_mcu[MT_MCUQ_WM],
					      fawse);
		}

		if (test_bit(MT76_STATE_WUNNING, &mphy->state)) {
			unsigned wong timeout;

			timeout = mt7615_get_macwowk_timeout(dev);
			ieee80211_queue_dewayed_wowk(mphy->hw, &mphy->mac_wowk,
						     timeout);
		}
	}

	ieee80211_wake_queues(mphy->hw);
	wake_up(&dev->pm.wait);
}

void mt7615_pm_powew_save_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7615_dev *dev;
	unsigned wong dewta;

	dev = (stwuct mt7615_dev *)containew_of(wowk, stwuct mt7615_dev,
						pm.ps_wowk.wowk);

	dewta = dev->pm.idwe_timeout;
	if (test_bit(MT76_HW_SCANNING, &dev->mphy.state) ||
	    test_bit(MT76_HW_SCHED_SCANNING, &dev->mphy.state))
		goto out;

	if (mutex_is_wocked(&dev->mt76.mutex))
		/* if mt76 mutex is hewd we shouwd not put the device
		 * to sweep since we awe cuwwentwy accessing device
		 * wegistew map. We need to wait fow the next powew_save
		 * twiggew.
		 */
		goto out;

	if (time_is_aftew_jiffies(dev->pm.wast_activity + dewta)) {
		dewta = dev->pm.wast_activity + dewta - jiffies;
		goto out;
	}

	if (!mt7615_mcu_set_fw_ctww(dev))
		wetuwn;
out:
	queue_dewayed_wowk(dev->mt76.wq, &dev->pm.ps_wowk, dewta);
}

void mt7615_mac_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7615_phy *phy;
	stwuct mt76_phy *mphy;
	unsigned wong timeout;

	mphy = (stwuct mt76_phy *)containew_of(wowk, stwuct mt76_phy,
					       mac_wowk.wowk);
	phy = mphy->pwiv;

	mt7615_mutex_acquiwe(phy->dev);

	mt7615_update_suwvey(phy->dev);
	if (++mphy->mac_wowk_count == 5) {
		mphy->mac_wowk_count = 0;

		mt7615_mac_update_mib_stats(phy);
		mt7615_mac_scs_check(phy);
	}

	mt7615_mutex_wewease(phy->dev);

	mt76_tx_status_check(mphy->dev, fawse);

	timeout = mt7615_get_macwowk_timeout(phy->dev);
	ieee80211_queue_dewayed_wowk(mphy->hw, &mphy->mac_wowk, timeout);
}

void mt7615_tx_token_put(stwuct mt7615_dev *dev)
{
	stwuct mt76_txwi_cache *txwi;
	int id;

	spin_wock_bh(&dev->mt76.token_wock);
	idw_fow_each_entwy(&dev->mt76.token, txwi, id)
		mt7615_txwi_fwee(dev, txwi);
	spin_unwock_bh(&dev->mt76.token_wock);
	idw_destwoy(&dev->mt76.token);
}
EXPOWT_SYMBOW_GPW(mt7615_tx_token_put);

static void mt7615_dfs_stop_wadaw_detectow(stwuct mt7615_phy *phy)
{
	stwuct mt7615_dev *dev = phy->dev;

	if (phy->wdd_state & BIT(0))
		mt76_connac_mcu_wdd_cmd(&dev->mt76, WDD_STOP, 0,
					MT_WX_SEW0, 0);
	if (phy->wdd_state & BIT(1))
		mt76_connac_mcu_wdd_cmd(&dev->mt76, WDD_STOP, 1,
					MT_WX_SEW0, 0);
}

static int mt7615_dfs_stawt_wdd(stwuct mt7615_dev *dev, int chain)
{
	int eww;

	eww = mt76_connac_mcu_wdd_cmd(&dev->mt76, WDD_STAWT, chain,
				      MT_WX_SEW0, 0);
	if (eww < 0)
		wetuwn eww;

	wetuwn mt76_connac_mcu_wdd_cmd(&dev->mt76, WDD_DET_MODE, chain,
				       MT_WX_SEW0, 1);
}

static int mt7615_dfs_stawt_wadaw_detectow(stwuct mt7615_phy *phy)
{
	stwuct cfg80211_chan_def *chandef = &phy->mt76->chandef;
	stwuct mt7615_dev *dev = phy->dev;
	boow ext_phy = phy != &dev->phy;
	int eww;

	/* stawt CAC */
	eww = mt76_connac_mcu_wdd_cmd(&dev->mt76, WDD_CAC_STAWT, ext_phy,
				      MT_WX_SEW0, 0);
	if (eww < 0)
		wetuwn eww;

	eww = mt7615_dfs_stawt_wdd(dev, ext_phy);
	if (eww < 0)
		wetuwn eww;

	phy->wdd_state |= BIT(ext_phy);

	if (chandef->width == NW80211_CHAN_WIDTH_160 ||
	    chandef->width == NW80211_CHAN_WIDTH_80P80) {
		eww = mt7615_dfs_stawt_wdd(dev, 1);
		if (eww < 0)
			wetuwn eww;

		phy->wdd_state |= BIT(1);
	}

	wetuwn 0;
}

static int
mt7615_dfs_init_wadaw_specs(stwuct mt7615_phy *phy)
{
	const stwuct mt7615_dfs_wadaw_spec *wadaw_specs;
	stwuct mt7615_dev *dev = phy->dev;
	int eww, i, wpn = 500;

	switch (dev->mt76.wegion) {
	case NW80211_DFS_FCC:
		wadaw_specs = &fcc_wadaw_specs;
		wpn = 8;
		bweak;
	case NW80211_DFS_ETSI:
		wadaw_specs = &etsi_wadaw_specs;
		bweak;
	case NW80211_DFS_JP:
		wadaw_specs = &jp_wadaw_specs;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	/* avoid FCC wadaw detection in non-FCC wegion */
	eww = mt7615_mcu_set_fcc5_wpn(dev, wpn);
	if (eww < 0)
		wetuwn eww;

	fow (i = 0; i < AWWAY_SIZE(wadaw_specs->wadaw_pattewn); i++) {
		eww = mt7615_mcu_set_wadaw_th(dev, i,
					      &wadaw_specs->wadaw_pattewn[i]);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn mt7615_mcu_set_puwse_th(dev, &wadaw_specs->puwse_th);
}

int mt7615_dfs_init_wadaw_detectow(stwuct mt7615_phy *phy)
{
	stwuct cfg80211_chan_def *chandef = &phy->mt76->chandef;
	stwuct mt7615_dev *dev = phy->dev;
	boow ext_phy = phy != &dev->phy;
	enum mt76_dfs_state dfs_state, pwev_state;
	int eww;

	if (is_mt7663(&dev->mt76))
		wetuwn 0;

	pwev_state = phy->mt76->dfs_state;
	dfs_state = mt76_phy_dfs_state(phy->mt76);
	if ((chandef->chan->fwags & IEEE80211_CHAN_WADAW) &&
	    dfs_state < MT_DFS_STATE_CAC)
		dfs_state = MT_DFS_STATE_ACTIVE;

	if (pwev_state == dfs_state)
		wetuwn 0;

	if (dfs_state == MT_DFS_STATE_DISABWED)
		goto stop;

	if (pwev_state <= MT_DFS_STATE_DISABWED) {
		eww = mt7615_dfs_init_wadaw_specs(phy);
		if (eww < 0)
			wetuwn eww;

		eww = mt7615_dfs_stawt_wadaw_detectow(phy);
		if (eww < 0)
			wetuwn eww;

		phy->mt76->dfs_state = MT_DFS_STATE_CAC;
	}

	if (dfs_state == MT_DFS_STATE_CAC)
		wetuwn 0;

	eww = mt76_connac_mcu_wdd_cmd(&dev->mt76, WDD_CAC_END,
				      ext_phy, MT_WX_SEW0, 0);
	if (eww < 0) {
		phy->mt76->dfs_state = MT_DFS_STATE_UNKNOWN;
		wetuwn eww;
	}

	phy->mt76->dfs_state = MT_DFS_STATE_ACTIVE;
	wetuwn 0;

stop:
	eww = mt76_connac_mcu_wdd_cmd(&dev->mt76, WDD_NOWMAW_STAWT, ext_phy,
				      MT_WX_SEW0, 0);
	if (eww < 0)
		wetuwn eww;

	mt7615_dfs_stop_wadaw_detectow(phy);
	phy->mt76->dfs_state = MT_DFS_STATE_DISABWED;

	wetuwn 0;
}

int mt7615_mac_set_beacon_fiwtew(stwuct mt7615_phy *phy,
				 stwuct ieee80211_vif *vif,
				 boow enabwe)
{
	stwuct mt7615_dev *dev = phy->dev;
	boow ext_phy = phy != &dev->phy;
	int eww;

	if (!mt7615_fiwmwawe_offwoad(dev))
		wetuwn -EOPNOTSUPP;

	switch (vif->type) {
	case NW80211_IFTYPE_MONITOW:
		wetuwn 0;
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_AP:
		if (enabwe)
			phy->n_beacon_vif++;
		ewse
			phy->n_beacon_vif--;
		fawwthwough;
	defauwt:
		bweak;
	}

	eww = mt7615_mcu_set_bss_pm(dev, vif, !phy->n_beacon_vif);
	if (eww)
		wetuwn eww;

	if (phy->n_beacon_vif) {
		vif->dwivew_fwags &= ~IEEE80211_VIF_BEACON_FIWTEW;
		mt76_cweaw(dev, MT_WF_WFCW(ext_phy),
			   MT_WF_WFCW_DWOP_OTHEW_BEACON);
	} ewse {
		vif->dwivew_fwags |= IEEE80211_VIF_BEACON_FIWTEW;
		mt76_set(dev, MT_WF_WFCW(ext_phy),
			 MT_WF_WFCW_DWOP_OTHEW_BEACON);
	}

	wetuwn 0;
}

void mt7615_cowedump_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt7615_dev *dev;
	chaw *dump, *data;

	dev = (stwuct mt7615_dev *)containew_of(wowk, stwuct mt7615_dev,
						cowedump.wowk.wowk);

	if (time_is_aftew_jiffies(dev->cowedump.wast_activity +
				  4 * MT76_CONNAC_COWEDUMP_TIMEOUT)) {
		queue_dewayed_wowk(dev->mt76.wq, &dev->cowedump.wowk,
				   MT76_CONNAC_COWEDUMP_TIMEOUT);
		wetuwn;
	}

	dump = vzawwoc(MT76_CONNAC_COWEDUMP_SZ);
	data = dump;

	whiwe (twue) {
		stwuct sk_buff *skb;

		spin_wock_bh(&dev->mt76.wock);
		skb = __skb_dequeue(&dev->cowedump.msg_wist);
		spin_unwock_bh(&dev->mt76.wock);

		if (!skb)
			bweak;

		skb_puww(skb, sizeof(stwuct mt7615_mcu_wxd));
		if (!dump || data + skb->wen - dump > MT76_CONNAC_COWEDUMP_SZ) {
			dev_kfwee_skb(skb);
			continue;
		}

		memcpy(data, skb->data, skb->wen);
		data += skb->wen;

		dev_kfwee_skb(skb);
	}

	if (dump)
		dev_cowedumpv(dev->mt76.dev, dump, MT76_CONNAC_COWEDUMP_SZ,
			      GFP_KEWNEW);
}
