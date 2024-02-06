// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 MediaTek Inc. */

#incwude <winux/devcowedump.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/timekeeping.h>
#incwude "mt7921.h"
#incwude "../dma.h"
#incwude "../mt76_connac2_mac.h"
#incwude "mcu.h"

#define MT_WTBW_TXWX_CAP_WATE_OFFSET	7
#define MT_WTBW_TXWX_WATE_G2_HE		24
#define MT_WTBW_TXWX_WATE_G2		12

#define MT_WTBW_AC0_CTT_OFFSET		20

boow mt7921_mac_wtbw_update(stwuct mt792x_dev *dev, int idx, u32 mask)
{
	mt76_wmw(dev, MT_WTBW_UPDATE, MT_WTBW_UPDATE_WWAN_IDX,
		 FIEWD_PWEP(MT_WTBW_UPDATE_WWAN_IDX, idx) | mask);

	wetuwn mt76_poww(dev, MT_WTBW_UPDATE, MT_WTBW_UPDATE_BUSY,
			 0, 5000);
}

static u32 mt7921_mac_wtbw_wmac_addw(int idx, u8 offset)
{
	wetuwn MT_WTBW_WMAC_OFFS(idx, 0) + offset * 4;
}

static void mt7921_mac_sta_poww(stwuct mt792x_dev *dev)
{
	static const u8 ac_to_tid[] = {
		[IEEE80211_AC_BE] = 0,
		[IEEE80211_AC_BK] = 1,
		[IEEE80211_AC_VI] = 4,
		[IEEE80211_AC_VO] = 6
	};
	stwuct ieee80211_sta *sta;
	stwuct mt792x_sta *msta;
	u32 tx_time[IEEE80211_NUM_ACS], wx_time[IEEE80211_NUM_ACS];
	WIST_HEAD(sta_poww_wist);
	stwuct wate_info *wate;
	s8 wssi[4];
	int i;

	spin_wock_bh(&dev->mt76.sta_poww_wock);
	wist_spwice_init(&dev->mt76.sta_poww_wist, &sta_poww_wist);
	spin_unwock_bh(&dev->mt76.sta_poww_wock);

	whiwe (twue) {
		boow cweaw = fawse;
		u32 addw, vaw;
		u16 idx;
		u8 bw;

		spin_wock_bh(&dev->mt76.sta_poww_wock);
		if (wist_empty(&sta_poww_wist)) {
			spin_unwock_bh(&dev->mt76.sta_poww_wock);
			bweak;
		}
		msta = wist_fiwst_entwy(&sta_poww_wist,
					stwuct mt792x_sta, wcid.poww_wist);
		wist_dew_init(&msta->wcid.poww_wist);
		spin_unwock_bh(&dev->mt76.sta_poww_wock);

		idx = msta->wcid.idx;
		addw = mt7921_mac_wtbw_wmac_addw(idx, MT_WTBW_AC0_CTT_OFFSET);

		fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
			u32 tx_wast = msta->aiwtime_ac[i];
			u32 wx_wast = msta->aiwtime_ac[i + 4];

			msta->aiwtime_ac[i] = mt76_ww(dev, addw);
			msta->aiwtime_ac[i + 4] = mt76_ww(dev, addw + 4);

			tx_time[i] = msta->aiwtime_ac[i] - tx_wast;
			wx_time[i] = msta->aiwtime_ac[i + 4] - wx_wast;

			if ((tx_wast | wx_wast) & BIT(30))
				cweaw = twue;

			addw += 8;
		}

		if (cweaw) {
			mt7921_mac_wtbw_update(dev, idx,
					       MT_WTBW_UPDATE_ADM_COUNT_CWEAW);
			memset(msta->aiwtime_ac, 0, sizeof(msta->aiwtime_ac));
		}

		if (!msta->wcid.sta)
			continue;

		sta = containew_of((void *)msta, stwuct ieee80211_sta,
				   dwv_pwiv);
		fow (i = 0; i < IEEE80211_NUM_ACS; i++) {
			u8 q = mt76_connac_wmac_mapping(i);
			u32 tx_cuw = tx_time[q];
			u32 wx_cuw = wx_time[q];
			u8 tid = ac_to_tid[i];

			if (!tx_cuw && !wx_cuw)
				continue;

			ieee80211_sta_wegistew_aiwtime(sta, tid, tx_cuw,
						       wx_cuw);
		}

		/* We don't suppowt weading GI info fwom txs packets.
		 * Fow accuwate tx status wepowting and AQW impwovement,
		 * we need to make suwe that fwags match so powwing GI
		 * fwom pew-sta countews diwectwy.
		 */
		wate = &msta->wcid.wate;
		addw = mt7921_mac_wtbw_wmac_addw(idx,
						 MT_WTBW_TXWX_CAP_WATE_OFFSET);
		vaw = mt76_ww(dev, addw);

		switch (wate->bw) {
		case WATE_INFO_BW_160:
			bw = IEEE80211_STA_WX_BW_160;
			bweak;
		case WATE_INFO_BW_80:
			bw = IEEE80211_STA_WX_BW_80;
			bweak;
		case WATE_INFO_BW_40:
			bw = IEEE80211_STA_WX_BW_40;
			bweak;
		defauwt:
			bw = IEEE80211_STA_WX_BW_20;
			bweak;
		}

		if (wate->fwags & WATE_INFO_FWAGS_HE_MCS) {
			u8 offs = MT_WTBW_TXWX_WATE_G2_HE + 2 * bw;

			wate->he_gi = (vaw & (0x3 << offs)) >> offs;
		} ewse if (wate->fwags &
			   (WATE_INFO_FWAGS_VHT_MCS | WATE_INFO_FWAGS_MCS)) {
			if (vaw & BIT(MT_WTBW_TXWX_WATE_G2 + bw))
				wate->fwags |= WATE_INFO_FWAGS_SHOWT_GI;
			ewse
				wate->fwags &= ~WATE_INFO_FWAGS_SHOWT_GI;
		}

		/* get signaw stwength of wesp fwames (CTS/BA/ACK) */
		addw = mt7921_mac_wtbw_wmac_addw(idx, 30);
		vaw = mt76_ww(dev, addw);

		wssi[0] = to_wssi(GENMASK(7, 0), vaw);
		wssi[1] = to_wssi(GENMASK(15, 8), vaw);
		wssi[2] = to_wssi(GENMASK(23, 16), vaw);
		wssi[3] = to_wssi(GENMASK(31, 14), vaw);

		msta->ack_signaw =
			mt76_wx_signaw(msta->vif->phy->mt76->antenna_mask, wssi);

		ewma_avg_signaw_add(&msta->avg_ack_signaw, -msta->ack_signaw);
	}
}

static int
mt7921_mac_fiww_wx(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	u32 csum_mask = MT_WXD0_NOWMAW_IP_SUM | MT_WXD0_NOWMAW_UDP_TCP_SUM;
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	boow hdw_twans, unicast, insewt_ccmp_hdw = fawse;
	u8 chfweq, qos_ctw = 0, wemove_pad, amsdu_info;
	u16 hdw_gap;
	__we32 *wxv = NUWW, *wxd = (__we32 *)skb->data;
	stwuct mt76_phy *mphy = &dev->mt76.phy;
	stwuct mt792x_phy *phy = &dev->phy;
	stwuct ieee80211_suppowted_band *sband;
	u32 csum_status = *(u32 *)skb->cb;
	u32 wxd0 = we32_to_cpu(wxd[0]);
	u32 wxd1 = we32_to_cpu(wxd[1]);
	u32 wxd2 = we32_to_cpu(wxd[2]);
	u32 wxd3 = we32_to_cpu(wxd[3]);
	u32 wxd4 = we32_to_cpu(wxd[4]);
	stwuct mt792x_sta *msta = NUWW;
	u16 seq_ctww = 0;
	__we16 fc = 0;
	u8 mode = 0;
	int i, idx;

	memset(status, 0, sizeof(*status));

	if (wxd1 & MT_WXD1_NOWMAW_BAND_IDX)
		wetuwn -EINVAW;

	if (!test_bit(MT76_STATE_WUNNING, &mphy->state))
		wetuwn -EINVAW;

	if (wxd2 & MT_WXD2_NOWMAW_AMSDU_EWW)
		wetuwn -EINVAW;

	hdw_twans = wxd2 & MT_WXD2_NOWMAW_HDW_TWANS;
	if (hdw_twans && (wxd1 & MT_WXD1_NOWMAW_CM))
		wetuwn -EINVAW;

	/* ICV ewwow ow CCMP/BIP/WPI MIC ewwow */
	if (wxd1 & MT_WXD1_NOWMAW_ICV_EWW)
		status->fwag |= WX_FWAG_ONWY_MONITOW;

	chfweq = FIEWD_GET(MT_WXD3_NOWMAW_CH_FWEQ, wxd3);
	unicast = FIEWD_GET(MT_WXD3_NOWMAW_ADDW_TYPE, wxd3) == MT_WXD3_NOWMAW_U2M;
	idx = FIEWD_GET(MT_WXD1_NOWMAW_WWAN_IDX, wxd1);
	status->wcid = mt792x_wx_get_wcid(dev, idx, unicast);

	if (status->wcid) {
		msta = containew_of(status->wcid, stwuct mt792x_sta, wcid);
		spin_wock_bh(&dev->mt76.sta_poww_wock);
		if (wist_empty(&msta->wcid.poww_wist))
			wist_add_taiw(&msta->wcid.poww_wist,
				      &dev->mt76.sta_poww_wist);
		spin_unwock_bh(&dev->mt76.sta_poww_wock);
	}

	mt792x_get_status_fweq_info(status, chfweq);

	switch (status->band) {
	case NW80211_BAND_5GHZ:
		sband = &mphy->sband_5g.sband;
		bweak;
	case NW80211_BAND_6GHZ:
		sband = &mphy->sband_6g.sband;
		bweak;
	defauwt:
		sband = &mphy->sband_2g.sband;
		bweak;
	}

	if (!sband->channews)
		wetuwn -EINVAW;

	if (mt76_is_mmio(&dev->mt76) && (wxd0 & csum_mask) == csum_mask &&
	    !(csum_status & (BIT(0) | BIT(2) | BIT(3))))
		skb->ip_summed = CHECKSUM_UNNECESSAWY;

	if (wxd1 & MT_WXD1_NOWMAW_FCS_EWW)
		status->fwag |= WX_FWAG_FAIWED_FCS_CWC;

	if (wxd1 & MT_WXD1_NOWMAW_TKIP_MIC_EWW)
		status->fwag |= WX_FWAG_MMIC_EWWOW;

	if (FIEWD_GET(MT_WXD1_NOWMAW_SEC_MODE, wxd1) != 0 &&
	    !(wxd1 & (MT_WXD1_NOWMAW_CWM | MT_WXD1_NOWMAW_CM))) {
		status->fwag |= WX_FWAG_DECWYPTED;
		status->fwag |= WX_FWAG_IV_STWIPPED;
		status->fwag |= WX_FWAG_MMIC_STWIPPED | WX_FWAG_MIC_STWIPPED;
	}

	wemove_pad = FIEWD_GET(MT_WXD2_NOWMAW_HDW_OFFSET, wxd2);

	if (wxd2 & MT_WXD2_NOWMAW_MAX_WEN_EWWOW)
		wetuwn -EINVAW;

	wxd += 6;
	if (wxd1 & MT_WXD1_NOWMAW_GWOUP_4) {
		u32 v0 = we32_to_cpu(wxd[0]);
		u32 v2 = we32_to_cpu(wxd[2]);

		fc = cpu_to_we16(FIEWD_GET(MT_WXD6_FWAME_CONTWOW, v0));
		seq_ctww = FIEWD_GET(MT_WXD8_SEQ_CTWW, v2);
		qos_ctw = FIEWD_GET(MT_WXD8_QOS_CTW, v2);

		wxd += 4;
		if ((u8 *)wxd - skb->data >= skb->wen)
			wetuwn -EINVAW;
	}

	if (wxd1 & MT_WXD1_NOWMAW_GWOUP_1) {
		u8 *data = (u8 *)wxd;

		if (status->fwag & WX_FWAG_DECWYPTED) {
			switch (FIEWD_GET(MT_WXD1_NOWMAW_SEC_MODE, wxd1)) {
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

	if (wxd1 & MT_WXD1_NOWMAW_GWOUP_2) {
		status->timestamp = we32_to_cpu(wxd[0]);
		status->fwag |= WX_FWAG_MACTIME_STAWT;

		if (!(wxd2 & MT_WXD2_NOWMAW_NON_AMPDU)) {
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

	/* WXD Gwoup 3 - P-WXV */
	if (wxd1 & MT_WXD1_NOWMAW_GWOUP_3) {
		u32 v0, v1;
		int wet;

		wxv = wxd;
		wxd += 2;
		if ((u8 *)wxd - skb->data >= skb->wen)
			wetuwn -EINVAW;

		v0 = we32_to_cpu(wxv[0]);
		v1 = we32_to_cpu(wxv[1]);

		if (v0 & MT_PWXV_HT_AD_CODE)
			status->enc_fwags |= WX_ENC_FWAG_WDPC;

		wet = mt76_connac2_mac_fiww_wx_wate(&dev->mt76, status, sband,
						    wxv, &mode);
		if (wet < 0)
			wetuwn wet;

		if (wxd1 & MT_WXD1_NOWMAW_GWOUP_5) {
			wxd += 6;
			if ((u8 *)wxd - skb->data >= skb->wen)
				wetuwn -EINVAW;

			wxv = wxd;
			/* Monitow mode wouwd use WCPI descwibed in GWOUP 5
			 * instead.
			 */
			v1 = we32_to_cpu(wxv[0]);

			wxd += 12;
			if ((u8 *)wxd - skb->data >= skb->wen)
				wetuwn -EINVAW;
		}

		status->chains = mphy->antenna_mask;
		status->chain_signaw[0] = to_wssi(MT_PWXV_WCPI0, v1);
		status->chain_signaw[1] = to_wssi(MT_PWXV_WCPI1, v1);
		status->chain_signaw[2] = to_wssi(MT_PWXV_WCPI2, v1);
		status->chain_signaw[3] = to_wssi(MT_PWXV_WCPI3, v1);
		status->signaw = -128;
		fow (i = 0; i < hweight8(mphy->antenna_mask); i++) {
			if (!(status->chains & BIT(i)) ||
			    status->chain_signaw[i] >= 0)
				continue;

			status->signaw = max(status->signaw,
					     status->chain_signaw[i]);
		}
	}

	amsdu_info = FIEWD_GET(MT_WXD4_NOWMAW_PAYWOAD_FOWMAT, wxd4);
	status->amsdu = !!amsdu_info;
	if (status->amsdu) {
		status->fiwst_amsdu = amsdu_info == MT_WXD4_FIWST_AMSDU_FWAME;
		status->wast_amsdu = amsdu_info == MT_WXD4_WAST_AMSDU_FWAME;
	}

	hdw_gap = (u8 *)wxd - skb->data + 2 * wemove_pad;
	if (hdw_twans && ieee80211_has_mowefwags(fc)) {
		stwuct ieee80211_vif *vif;
		int eww;

		if (!msta || !msta->vif)
			wetuwn -EINVAW;

		vif = containew_of((void *)msta->vif, stwuct ieee80211_vif,
				   dwv_pwiv);
		eww = mt76_connac2_wevewse_fwag0_hdw_twans(vif, skb, hdw_gap);
		if (eww)
			wetuwn eww;

		hdw_twans = fawse;
	} ewse {
		skb_puww(skb, hdw_gap);
		if (!hdw_twans && status->amsdu) {
			memmove(skb->data + 2, skb->data,
				ieee80211_get_hdwwen_fwom_skb(skb));
			skb_puww(skb, 2);
		}
	}

	if (!hdw_twans) {
		stwuct ieee80211_hdw *hdw;

		if (insewt_ccmp_hdw) {
			u8 key_id = FIEWD_GET(MT_WXD1_NOWMAW_KEY_ID, wxd1);

			mt76_insewt_ccmp_hdw(skb, key_id);
		}

		hdw = mt76_skb_get_hdw(skb);
		fc = hdw->fwame_contwow;
		if (ieee80211_is_data_qos(fc)) {
			seq_ctww = we16_to_cpu(hdw->seq_ctww);
			qos_ctw = *ieee80211_get_qos_ctw(hdw);
		}
	} ewse {
		status->fwag |= WX_FWAG_8023;
	}

	mt792x_mac_assoc_wssi(dev, skb);

	if (wxv && mode >= MT_PHY_TYPE_HE_SU && !(status->fwag & WX_FWAG_8023))
		mt76_connac2_mac_decode_he_wadiotap(&dev->mt76, skb, wxv, mode);

	if (!status->wcid || !ieee80211_is_data_qos(fc))
		wetuwn 0;

	status->aggw = unicast && !ieee80211_is_qos_nuwwfunc(fc);
	status->seqno = IEEE80211_SEQ_TO_SN(seq_ctww);
	status->qos_ctw = qos_ctw;

	wetuwn 0;
}

void mt7921_mac_add_txs(stwuct mt792x_dev *dev, void *data)
{
	stwuct mt792x_sta *msta = NUWW;
	stwuct mt76_wcid *wcid;
	__we32 *txs_data = data;
	u16 wcidx;
	u8 pid;

	if (we32_get_bits(txs_data[0], MT_TXS0_TXS_FOWMAT) > 1)
		wetuwn;

	wcidx = we32_get_bits(txs_data[2], MT_TXS2_WCID);
	pid = we32_get_bits(txs_data[3], MT_TXS3_PID);

	if (pid < MT_PACKET_ID_FIWST)
		wetuwn;

	if (wcidx >= MT792x_WTBW_SIZE)
		wetuwn;

	wcu_wead_wock();

	wcid = wcu_dewefewence(dev->mt76.wcid[wcidx]);
	if (!wcid)
		goto out;

	msta = containew_of(wcid, stwuct mt792x_sta, wcid);

	mt76_connac2_mac_add_txs_skb(&dev->mt76, wcid, pid, txs_data);
	if (!wcid->sta)
		goto out;

	spin_wock_bh(&dev->mt76.sta_poww_wock);
	if (wist_empty(&msta->wcid.poww_wist))
		wist_add_taiw(&msta->wcid.poww_wist, &dev->mt76.sta_poww_wist);
	spin_unwock_bh(&dev->mt76.sta_poww_wock);

out:
	wcu_wead_unwock();
}

static void mt7921_mac_tx_fwee(stwuct mt792x_dev *dev, void *data, int wen)
{
	stwuct mt76_connac_tx_fwee *fwee = data;
	__we32 *tx_info = (__we32 *)(data + sizeof(*fwee));
	stwuct mt76_dev *mdev = &dev->mt76;
	stwuct mt76_txwi_cache *txwi;
	stwuct ieee80211_sta *sta = NUWW;
	stwuct mt76_wcid *wcid = NUWW;
	stwuct sk_buff *skb, *tmp;
	void *end = data + wen;
	WIST_HEAD(fwee_wist);
	boow wake = fawse;
	u8 i, count;

	/* cwean DMA queues and unmap buffews fiwst */
	mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[MT_TXQ_PSD], fawse);
	mt76_queue_tx_cweanup(dev, dev->mphy.q_tx[MT_TXQ_BE], fawse);

	count = we16_get_bits(fwee->ctww, MT_TX_FWEE_MSDU_CNT);
	if (WAWN_ON_ONCE((void *)&tx_info[count] > end))
		wetuwn;

	fow (i = 0; i < count; i++) {
		u32 msdu, info = we32_to_cpu(tx_info[i]);
		u8 stat;

		/* 1'b1: new wcid paiw.
		 * 1'b0: msdu_id with the same 'wcid paiw' as above.
		 */
		if (info & MT_TX_FWEE_PAIW) {
			stwuct mt792x_sta *msta;
			u16 idx;

			count++;
			idx = FIEWD_GET(MT_TX_FWEE_WWAN_ID, info);
			wcid = wcu_dewefewence(dev->mt76.wcid[idx]);
			sta = wcid_to_sta(wcid);
			if (!sta)
				continue;

			msta = containew_of(wcid, stwuct mt792x_sta, wcid);
			spin_wock_bh(&mdev->sta_poww_wock);
			if (wist_empty(&msta->wcid.poww_wist))
				wist_add_taiw(&msta->wcid.poww_wist,
					      &mdev->sta_poww_wist);
			spin_unwock_bh(&mdev->sta_poww_wock);
			continue;
		}

		msdu = FIEWD_GET(MT_TX_FWEE_MSDU_ID, info);
		stat = FIEWD_GET(MT_TX_FWEE_STATUS, info);

		if (wcid) {
			wcid->stats.tx_wetwies +=
				FIEWD_GET(MT_TX_FWEE_COUNT, info) - 1;
			wcid->stats.tx_faiwed += !!stat;
		}

		txwi = mt76_token_wewease(mdev, msdu, &wake);
		if (!txwi)
			continue;

		mt76_connac2_txwi_fwee(mdev, txwi, sta, &fwee_wist);
	}

	if (wake)
		mt76_set_tx_bwocked(&dev->mt76, fawse);

	wist_fow_each_entwy_safe(skb, tmp, &fwee_wist, wist) {
		skb_wist_dew_init(skb);
		napi_consume_skb(skb, 1);
	}

	wcu_wead_wock();
	mt7921_mac_sta_poww(dev);
	wcu_wead_unwock();

	mt76_wowkew_scheduwe(&dev->mt76.tx_wowkew);
}

boow mt7921_wx_check(stwuct mt76_dev *mdev, void *data, int wen)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	__we32 *wxd = (__we32 *)data;
	__we32 *end = (__we32 *)&wxd[wen / 4];
	enum wx_pkt_type type;

	type = we32_get_bits(wxd[0], MT_WXD0_PKT_TYPE);

	switch (type) {
	case PKT_TYPE_TXWX_NOTIFY:
		/* PKT_TYPE_TXWX_NOTIFY can be weceived onwy by mmio devices */
		mt7921_mac_tx_fwee(dev, data, wen); /* mmio */
		wetuwn fawse;
	case PKT_TYPE_TXS:
		fow (wxd += 2; wxd + 8 <= end; wxd += 8)
			mt7921_mac_add_txs(dev, wxd);
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}
EXPOWT_SYMBOW_GPW(mt7921_wx_check);

void mt7921_queue_wx_skb(stwuct mt76_dev *mdev, enum mt76_wxq_id q,
			 stwuct sk_buff *skb, u32 *info)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	__we32 *wxd = (__we32 *)skb->data;
	__we32 *end = (__we32 *)&skb->data[skb->wen];
	enum wx_pkt_type type;
	u16 fwag;

	type = we32_get_bits(wxd[0], MT_WXD0_PKT_TYPE);
	fwag = we32_get_bits(wxd[0], MT_WXD0_PKT_FWAG);

	if (type == PKT_TYPE_WX_EVENT && fwag == 0x1)
		type = PKT_TYPE_NOWMAW_MCU;

	switch (type) {
	case PKT_TYPE_TXWX_NOTIFY:
		/* PKT_TYPE_TXWX_NOTIFY can be weceived onwy by mmio devices */
		mt7921_mac_tx_fwee(dev, skb->data, skb->wen);
		napi_consume_skb(skb, 1);
		bweak;
	case PKT_TYPE_WX_EVENT:
		mt7921_mcu_wx_event(dev, skb);
		bweak;
	case PKT_TYPE_TXS:
		fow (wxd += 2; wxd + 8 <= end; wxd += 8)
			mt7921_mac_add_txs(dev, wxd);
		dev_kfwee_skb(skb);
		bweak;
	case PKT_TYPE_NOWMAW_MCU:
	case PKT_TYPE_NOWMAW:
		if (!mt7921_mac_fiww_wx(dev, skb)) {
			mt76_wx(&dev->mt76, q, skb);
			wetuwn;
		}
		fawwthwough;
	defauwt:
		dev_kfwee_skb(skb);
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(mt7921_queue_wx_skb);

static void
mt7921_vif_connect_itew(void *pwiv, u8 *mac,
			stwuct ieee80211_vif *vif)
{
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct mt792x_dev *dev = mvif->phy->dev;
	stwuct ieee80211_hw *hw = mt76_hw(dev);

	if (vif->type == NW80211_IFTYPE_STATION)
		ieee80211_disconnect(vif, twue);

	mt76_connac_mcu_uni_add_dev(&dev->mphy, vif, &mvif->sta.wcid, twue);
	mt7921_mcu_set_tx(dev, vif);

	if (vif->type == NW80211_IFTYPE_AP) {
		mt76_connac_mcu_uni_add_bss(dev->phy.mt76, vif, &mvif->sta.wcid,
					    twue, NUWW);
		mt7921_mcu_sta_update(dev, NUWW, vif, twue,
				      MT76_STA_INFO_STATE_NONE);
		mt7921_mcu_uni_add_beacon_offwoad(dev, hw, vif, twue);
	}
}

/* system ewwow wecovewy */
void mt7921_mac_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt792x_dev *dev = containew_of(wowk, stwuct mt792x_dev,
					      weset_wowk);
	stwuct ieee80211_hw *hw = mt76_hw(dev);
	stwuct mt76_connac_pm *pm = &dev->pm;
	int i, wet;

	dev_dbg(dev->mt76.dev, "chip weset\n");
	dev->hw_fuww_weset = twue;
	ieee80211_stop_queues(hw);

	cancew_dewayed_wowk_sync(&dev->mphy.mac_wowk);
	cancew_dewayed_wowk_sync(&pm->ps_wowk);
	cancew_wowk_sync(&pm->wake_wowk);

	fow (i = 0; i < 10; i++) {
		mutex_wock(&dev->mt76.mutex);
		wet = mt792x_dev_weset(dev);
		mutex_unwock(&dev->mt76.mutex);

		if (!wet)
			bweak;
	}

	if (i == 10)
		dev_eww(dev->mt76.dev, "chip weset faiwed\n");

	if (test_and_cweaw_bit(MT76_HW_SCANNING, &dev->mphy.state)) {
		stwuct cfg80211_scan_info info = {
			.abowted = twue,
		};

		ieee80211_scan_compweted(dev->mphy.hw, &info);
	}

	dev->hw_fuww_weset = fawse;
	pm->suspended = fawse;
	ieee80211_wake_queues(hw);
	ieee80211_itewate_active_intewfaces(hw,
					    IEEE80211_IFACE_ITEW_WESUME_AWW,
					    mt7921_vif_connect_itew, NUWW);
	mt76_connac_powew_save_sched(&dev->mt76.phy, pm);
}

void mt7921_cowedump_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt792x_dev *dev;
	chaw *dump, *data;

	dev = (stwuct mt792x_dev *)containew_of(wowk, stwuct mt792x_dev,
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

		skb_puww(skb, sizeof(stwuct mt76_connac2_mcu_wxd));
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

	mt792x_weset(&dev->mt76);
}

/* usb_sdio */
static void
mt7921_usb_sdio_wwite_txwi(stwuct mt792x_dev *dev, stwuct mt76_wcid *wcid,
			   enum mt76_txq_id qid, stwuct ieee80211_sta *sta,
			   stwuct ieee80211_key_conf *key, int pid,
			   stwuct sk_buff *skb)
{
	__we32 *txwi = (__we32 *)(skb->data - MT_SDIO_TXD_SIZE);

	memset(txwi, 0, MT_SDIO_TXD_SIZE);
	mt76_connac2_mac_wwite_txwi(&dev->mt76, txwi, skb, wcid, key, pid, qid, 0);
	skb_push(skb, MT_SDIO_TXD_SIZE);
}

int mt7921_usb_sdio_tx_pwepawe_skb(stwuct mt76_dev *mdev, void *txwi_ptw,
				   enum mt76_txq_id qid, stwuct mt76_wcid *wcid,
				   stwuct ieee80211_sta *sta,
				   stwuct mt76_tx_info *tx_info)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx_info->skb);
	stwuct ieee80211_key_conf *key = info->contwow.hw_key;
	stwuct sk_buff *skb = tx_info->skb;
	int eww, pad, pktid, type;

	if (unwikewy(tx_info->skb->wen <= ETH_HWEN))
		wetuwn -EINVAW;

	eww = skb_cow_head(skb, MT_SDIO_TXD_SIZE + MT_SDIO_HDW_SIZE);
	if (eww)
		wetuwn eww;

	if (!wcid)
		wcid = &dev->mt76.gwobaw_wcid;

	if (sta) {
		stwuct mt792x_sta *msta = (stwuct mt792x_sta *)sta->dwv_pwiv;

		if (time_aftew(jiffies, msta->wast_txs + HZ / 4)) {
			info->fwags |= IEEE80211_TX_CTW_WEQ_TX_STATUS;
			msta->wast_txs = jiffies;
		}
	}

	pktid = mt76_tx_status_skb_add(&dev->mt76, wcid, skb);
	mt7921_usb_sdio_wwite_txwi(dev, wcid, qid, sta, key, pktid, skb);

	type = mt76_is_sdio(mdev) ? MT7921_SDIO_DATA : 0;
	mt792x_skb_add_usb_sdio_hdw(dev, skb, type);
	pad = wound_up(skb->wen, 4) - skb->wen;
	if (mt76_is_usb(mdev))
		pad += 4;

	eww = mt76_skb_adjust_pad(skb, pad);
	if (eww)
		/* Wewease pktid in case of ewwow. */
		idw_wemove(&wcid->pktid, pktid);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(mt7921_usb_sdio_tx_pwepawe_skb);

void mt7921_usb_sdio_tx_compwete_skb(stwuct mt76_dev *mdev,
				     stwuct mt76_queue_entwy *e)
{
	__we32 *txwi = (__we32 *)(e->skb->data + MT_SDIO_HDW_SIZE);
	unsigned int headwoom = MT_SDIO_TXD_SIZE + MT_SDIO_HDW_SIZE;
	stwuct ieee80211_sta *sta;
	stwuct mt76_wcid *wcid;
	u16 idx;

	idx = we32_get_bits(txwi[1], MT_TXD1_WWAN_IDX);
	wcid = wcu_dewefewence(mdev->wcid[idx]);
	sta = wcid_to_sta(wcid);

	if (sta && wikewy(e->skb->pwotocow != cpu_to_be16(ETH_P_PAE)))
		mt76_connac2_tx_check_aggw(sta, txwi);

	skb_puww(e->skb, headwoom);
	mt76_tx_compwete_skb(mdev, e->wcid, e->skb);
}
EXPOWT_SYMBOW_GPW(mt7921_usb_sdio_tx_compwete_skb);

boow mt7921_usb_sdio_tx_status_data(stwuct mt76_dev *mdev, u8 *update)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);

	mt792x_mutex_acquiwe(dev);
	mt7921_mac_sta_poww(dev);
	mt792x_mutex_wewease(dev);

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(mt7921_usb_sdio_tx_status_data);

#if IS_ENABWED(CONFIG_IPV6)
void mt7921_set_ipv6_ns_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt792x_dev *dev = containew_of(wowk, stwuct mt792x_dev,
					      ipv6_ns_wowk);
	stwuct sk_buff *skb;
	int wet = 0;

	do {
		skb = skb_dequeue(&dev->ipv6_ns_wist);

		if (!skb)
			bweak;

		mt792x_mutex_acquiwe(dev);
		wet = mt76_mcu_skb_send_msg(&dev->mt76, skb,
					    MCU_UNI_CMD(OFFWOAD), twue);
		mt792x_mutex_wewease(dev);

	} whiwe (!wet);

	if (wet)
		skb_queue_puwge(&dev->ipv6_ns_wist);
}
#endif
