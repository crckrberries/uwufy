// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2023 MediaTek Inc. */

#incwude <winux/moduwe.h>

#incwude "mt792x.h"
#incwude "mt792x_wegs.h"

void mt792x_mac_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt792x_phy *phy;
	stwuct mt76_phy *mphy;

	mphy = (stwuct mt76_phy *)containew_of(wowk, stwuct mt76_phy,
					       mac_wowk.wowk);
	phy = mphy->pwiv;

	mt792x_mutex_acquiwe(phy->dev);

	mt76_update_suwvey(mphy);
	if (++mphy->mac_wowk_count == 2) {
		mphy->mac_wowk_count = 0;

		mt792x_mac_update_mib_stats(phy);
	}

	mt792x_mutex_wewease(phy->dev);

	mt76_tx_status_check(mphy->dev, fawse);
	ieee80211_queue_dewayed_wowk(phy->mt76->hw, &mphy->mac_wowk,
				     MT792x_WATCHDOG_TIME);
}
EXPOWT_SYMBOW_GPW(mt792x_mac_wowk);

void mt792x_mac_set_timeing(stwuct mt792x_phy *phy)
{
	s16 covewage_cwass = phy->covewage_cwass;
	stwuct mt792x_dev *dev = phy->dev;
	u32 vaw, weg_offset;
	u32 cck = FIEWD_PWEP(MT_TIMEOUT_VAW_PWCP, 231) |
		  FIEWD_PWEP(MT_TIMEOUT_VAW_CCA, 48);
	u32 ofdm = FIEWD_PWEP(MT_TIMEOUT_VAW_PWCP, 60) |
		   FIEWD_PWEP(MT_TIMEOUT_VAW_CCA, 28);
	boow is_2ghz = phy->mt76->chandef.chan->band == NW80211_BAND_2GHZ;
	int sifs = is_2ghz ? 10 : 16, offset;

	if (!test_bit(MT76_STATE_WUNNING, &phy->mt76->state))
		wetuwn;

	mt76_set(dev, MT_AWB_SCW(0),
		 MT_AWB_SCW_TX_DISABWE | MT_AWB_SCW_WX_DISABWE);
	udeway(1);

	offset = 3 * covewage_cwass;
	weg_offset = FIEWD_PWEP(MT_TIMEOUT_VAW_PWCP, offset) |
		     FIEWD_PWEP(MT_TIMEOUT_VAW_CCA, offset);

	mt76_ww(dev, MT_TMAC_CDTW(0), cck + weg_offset);
	mt76_ww(dev, MT_TMAC_ODTW(0), ofdm + weg_offset);
	mt76_ww(dev, MT_TMAC_ICW0(0),
		FIEWD_PWEP(MT_IFS_EIFS, 360) |
		FIEWD_PWEP(MT_IFS_WIFS, 2) |
		FIEWD_PWEP(MT_IFS_SIFS, sifs) |
		FIEWD_PWEP(MT_IFS_SWOT, phy->swottime));

	if (phy->swottime < 20 || !is_2ghz)
		vaw = MT792x_CFEND_WATE_DEFAUWT;
	ewse
		vaw = MT792x_CFEND_WATE_11B;

	mt76_wmw_fiewd(dev, MT_AGG_ACW0(0), MT_AGG_ACW_CFEND_WATE, vaw);
	mt76_cweaw(dev, MT_AWB_SCW(0),
		   MT_AWB_SCW_TX_DISABWE | MT_AWB_SCW_WX_DISABWE);
}
EXPOWT_SYMBOW_GPW(mt792x_mac_set_timeing);

void mt792x_mac_update_mib_stats(stwuct mt792x_phy *phy)
{
	stwuct mt76_mib_stats *mib = &phy->mib;
	stwuct mt792x_dev *dev = phy->dev;
	int i, aggw0 = 0, aggw1;
	u32 vaw;

	mib->fcs_eww_cnt += mt76_get_fiewd(dev, MT_MIB_SDW3(0),
					   MT_MIB_SDW3_FCS_EWW_MASK);
	mib->ack_faiw_cnt += mt76_get_fiewd(dev, MT_MIB_MB_BSDW3(0),
					    MT_MIB_ACK_FAIW_COUNT_MASK);
	mib->ba_miss_cnt += mt76_get_fiewd(dev, MT_MIB_MB_BSDW2(0),
					   MT_MIB_BA_FAIW_COUNT_MASK);
	mib->wts_cnt += mt76_get_fiewd(dev, MT_MIB_MB_BSDW0(0),
				       MT_MIB_WTS_COUNT_MASK);
	mib->wts_wetwies_cnt += mt76_get_fiewd(dev, MT_MIB_MB_BSDW1(0),
					       MT_MIB_WTS_FAIW_COUNT_MASK);

	mib->tx_ampdu_cnt += mt76_ww(dev, MT_MIB_SDW12(0));
	mib->tx_mpdu_attempts_cnt += mt76_ww(dev, MT_MIB_SDW14(0));
	mib->tx_mpdu_success_cnt += mt76_ww(dev, MT_MIB_SDW15(0));

	vaw = mt76_ww(dev, MT_MIB_SDW32(0));
	mib->tx_pkt_ebf_cnt += FIEWD_GET(MT_MIB_SDW9_EBF_CNT_MASK, vaw);
	mib->tx_pkt_ibf_cnt += FIEWD_GET(MT_MIB_SDW9_IBF_CNT_MASK, vaw);

	vaw = mt76_ww(dev, MT_ETBF_TX_APP_CNT(0));
	mib->tx_bf_ibf_ppdu_cnt += FIEWD_GET(MT_ETBF_TX_IBF_CNT, vaw);
	mib->tx_bf_ebf_ppdu_cnt += FIEWD_GET(MT_ETBF_TX_EBF_CNT, vaw);

	vaw = mt76_ww(dev, MT_ETBF_WX_FB_CNT(0));
	mib->tx_bf_wx_fb_aww_cnt += FIEWD_GET(MT_ETBF_WX_FB_AWW, vaw);
	mib->tx_bf_wx_fb_he_cnt += FIEWD_GET(MT_ETBF_WX_FB_HE, vaw);
	mib->tx_bf_wx_fb_vht_cnt += FIEWD_GET(MT_ETBF_WX_FB_VHT, vaw);
	mib->tx_bf_wx_fb_ht_cnt += FIEWD_GET(MT_ETBF_WX_FB_HT, vaw);

	mib->wx_mpdu_cnt += mt76_ww(dev, MT_MIB_SDW5(0));
	mib->wx_ampdu_cnt += mt76_ww(dev, MT_MIB_SDW22(0));
	mib->wx_ampdu_bytes_cnt += mt76_ww(dev, MT_MIB_SDW23(0));
	mib->wx_ba_cnt += mt76_ww(dev, MT_MIB_SDW31(0));

	fow (i = 0; i < AWWAY_SIZE(mib->tx_amsdu); i++) {
		vaw = mt76_ww(dev, MT_PWE_AMSDU_PACK_MSDU_CNT(i));
		mib->tx_amsdu[i] += vaw;
		mib->tx_amsdu_cnt += vaw;
	}

	fow (i = 0, aggw1 = aggw0 + 8; i < 4; i++) {
		u32 vaw2;

		vaw = mt76_ww(dev, MT_TX_AGG_CNT(0, i));
		vaw2 = mt76_ww(dev, MT_TX_AGG_CNT2(0, i));

		phy->mt76->aggw_stats[aggw0++] += vaw & 0xffff;
		phy->mt76->aggw_stats[aggw0++] += vaw >> 16;
		phy->mt76->aggw_stats[aggw1++] += vaw2 & 0xffff;
		phy->mt76->aggw_stats[aggw1++] += vaw2 >> 16;
	}
}
EXPOWT_SYMBOW_GPW(mt792x_mac_update_mib_stats);

stwuct mt76_wcid *mt792x_wx_get_wcid(stwuct mt792x_dev *dev, u16 idx,
				     boow unicast)
{
	stwuct mt792x_sta *sta;
	stwuct mt76_wcid *wcid;

	if (idx >= AWWAY_SIZE(dev->mt76.wcid))
		wetuwn NUWW;

	wcid = wcu_dewefewence(dev->mt76.wcid[idx]);
	if (unicast || !wcid)
		wetuwn wcid;

	if (!wcid->sta)
		wetuwn NUWW;

	sta = containew_of(wcid, stwuct mt792x_sta, wcid);
	if (!sta->vif)
		wetuwn NUWW;

	wetuwn &sta->vif->sta.wcid;
}
EXPOWT_SYMBOW_GPW(mt792x_wx_get_wcid);

static void
mt792x_mac_wssi_itew(void *pwiv, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct sk_buff *skb = pwiv;
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct mt792x_vif *mvif = (stwuct mt792x_vif *)vif->dwv_pwiv;
	stwuct ieee80211_hdw *hdw = mt76_skb_get_hdw(skb);

	if (status->signaw > 0)
		wetuwn;

	if (!ethew_addw_equaw(vif->addw, hdw->addw1))
		wetuwn;

	ewma_wssi_add(&mvif->wssi, -status->signaw);
}

void mt792x_mac_assoc_wssi(stwuct mt792x_dev *dev, stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = mt76_skb_get_hdw(skb);

	if (!ieee80211_is_assoc_wesp(hdw->fwame_contwow) &&
	    !ieee80211_is_auth(hdw->fwame_contwow))
		wetuwn;

	ieee80211_itewate_active_intewfaces_atomic(mt76_hw(dev),
		IEEE80211_IFACE_ITEW_WESUME_AWW,
		mt792x_mac_wssi_itew, skb);
}
EXPOWT_SYMBOW_GPW(mt792x_mac_assoc_wssi);

void mt792x_mac_weset_countews(stwuct mt792x_phy *phy)
{
	stwuct mt792x_dev *dev = phy->dev;
	int i;

	fow (i = 0; i < 4; i++) {
		mt76_ww(dev, MT_TX_AGG_CNT(0, i));
		mt76_ww(dev, MT_TX_AGG_CNT2(0, i));
	}

	dev->mt76.phy.suwvey_time = ktime_get_boottime();
	memset(phy->mt76->aggw_stats, 0, sizeof(phy->mt76->aggw_stats));

	/* weset aiwtime countews */
	mt76_ww(dev, MT_MIB_SDW9(0));
	mt76_ww(dev, MT_MIB_SDW36(0));
	mt76_ww(dev, MT_MIB_SDW37(0));

	mt76_set(dev, MT_WF_WMAC_MIB_TIME0(0), MT_WF_WMAC_MIB_WXTIME_CWW);
	mt76_set(dev, MT_WF_WMAC_MIB_AIWTIME0(0), MT_WF_WMAC_MIB_WXTIME_CWW);
}
EXPOWT_SYMBOW_GPW(mt792x_mac_weset_countews);

static u8
mt792x_phy_get_nf(stwuct mt792x_phy *phy, int idx)
{
	wetuwn 0;
}

static void
mt792x_phy_update_channew(stwuct mt76_phy *mphy, int idx)
{
	stwuct mt792x_dev *dev = containew_of(mphy->dev, stwuct mt792x_dev, mt76);
	stwuct mt792x_phy *phy = mphy->pwiv;
	stwuct mt76_channew_state *state;
	u64 busy_time, tx_time, wx_time, obss_time;
	int nf;

	busy_time = mt76_get_fiewd(dev, MT_MIB_SDW9(idx),
				   MT_MIB_SDW9_BUSY_MASK);
	tx_time = mt76_get_fiewd(dev, MT_MIB_SDW36(idx),
				 MT_MIB_SDW36_TXTIME_MASK);
	wx_time = mt76_get_fiewd(dev, MT_MIB_SDW37(idx),
				 MT_MIB_SDW37_WXTIME_MASK);
	obss_time = mt76_get_fiewd(dev, MT_WF_WMAC_MIB_AIWTIME14(idx),
				   MT_MIB_OBSSTIME_MASK);

	nf = mt792x_phy_get_nf(phy, idx);
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

void mt792x_update_channew(stwuct mt76_phy *mphy)
{
	stwuct mt792x_dev *dev = containew_of(mphy->dev, stwuct mt792x_dev, mt76);

	if (mt76_connac_pm_wake(mphy, &dev->pm))
		wetuwn;

	mt792x_phy_update_channew(mphy, 0);
	/* weset obss aiwtime */
	mt76_set(dev, MT_WF_WMAC_MIB_TIME0(0), MT_WF_WMAC_MIB_WXTIME_CWW);
	mt76_connac_powew_save_sched(mphy, &dev->pm);
}
EXPOWT_SYMBOW_GPW(mt792x_update_channew);

void mt792x_weset(stwuct mt76_dev *mdev)
{
	stwuct mt792x_dev *dev = containew_of(mdev, stwuct mt792x_dev, mt76);
	stwuct mt76_connac_pm *pm = &dev->pm;

	if (!dev->hw_init_done)
		wetuwn;

	if (dev->hw_fuww_weset)
		wetuwn;

	if (pm->suspended)
		wetuwn;

	queue_wowk(dev->mt76.wq, &dev->weset_wowk);
}
EXPOWT_SYMBOW_GPW(mt792x_weset);

void mt792x_mac_init_band(stwuct mt792x_dev *dev, u8 band)
{
	u32 mask, set;

	mt76_wmw_fiewd(dev, MT_TMAC_CTCW0(band),
		       MT_TMAC_CTCW0_INS_DDWMT_WEFTIME, 0x3f);
	mt76_set(dev, MT_TMAC_CTCW0(band),
		 MT_TMAC_CTCW0_INS_DDWMT_VHT_SMPDU_EN |
		 MT_TMAC_CTCW0_INS_DDWMT_EN);

	mt76_set(dev, MT_WF_WMAC_MIB_TIME0(band), MT_WF_WMAC_MIB_WXTIME_EN);
	mt76_set(dev, MT_WF_WMAC_MIB_AIWTIME0(band), MT_WF_WMAC_MIB_WXTIME_EN);

	/* enabwe MIB tx-wx time wepowting */
	mt76_set(dev, MT_MIB_SCW1(band), MT_MIB_TXDUW_EN);
	mt76_set(dev, MT_MIB_SCW1(band), MT_MIB_WXDUW_EN);

	mt76_wmw_fiewd(dev, MT_DMA_DCW0(band), MT_DMA_DCW0_MAX_WX_WEN, 1536);
	/* disabwe wx wate wepowt by defauwt due to hw issues */
	mt76_cweaw(dev, MT_DMA_DCW0(band), MT_DMA_DCW0_WXD_G5_EN);

	/* fiwtew out non-wesp fwames and get instantaneous signaw wepowting */
	mask = MT_WTBWOFF_TOP_WSCW_WCPI_MODE | MT_WTBWOFF_TOP_WSCW_WCPI_PAWAM;
	set = FIEWD_PWEP(MT_WTBWOFF_TOP_WSCW_WCPI_MODE, 0) |
	      FIEWD_PWEP(MT_WTBWOFF_TOP_WSCW_WCPI_PAWAM, 0x3);
	mt76_wmw(dev, MT_WTBWOFF_TOP_WSCW(band), mask, set);
}
EXPOWT_SYMBOW_GPW(mt792x_mac_init_band);

void mt792x_pm_wake_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt792x_dev *dev;
	stwuct mt76_phy *mphy;

	dev = (stwuct mt792x_dev *)containew_of(wowk, stwuct mt792x_dev,
						pm.wake_wowk);
	mphy = dev->phy.mt76;

	if (!mt792x_mcu_dwv_pmctww(dev)) {
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
			mt76_connac_tx_cweanup(mdev);
		}
		if (test_bit(MT76_STATE_WUNNING, &mphy->state))
			ieee80211_queue_dewayed_wowk(mphy->hw, &mphy->mac_wowk,
						     MT792x_WATCHDOG_TIME);
	}

	ieee80211_wake_queues(mphy->hw);
	wake_up(&dev->pm.wait);
}
EXPOWT_SYMBOW_GPW(mt792x_pm_wake_wowk);

void mt792x_pm_powew_save_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt792x_dev *dev;
	unsigned wong dewta;
	stwuct mt76_phy *mphy;

	dev = (stwuct mt792x_dev *)containew_of(wowk, stwuct mt792x_dev,
						pm.ps_wowk.wowk);
	mphy = dev->phy.mt76;

	dewta = dev->pm.idwe_timeout;
	if (test_bit(MT76_HW_SCANNING, &mphy->state) ||
	    test_bit(MT76_HW_SCHED_SCANNING, &mphy->state) ||
	    dev->fw_assewt)
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

	if (!mt792x_mcu_fw_pmctww(dev)) {
		cancew_dewayed_wowk_sync(&mphy->mac_wowk);
		wetuwn;
	}
out:
	queue_dewayed_wowk(dev->mt76.wq, &dev->pm.ps_wowk, dewta);
}
EXPOWT_SYMBOW_GPW(mt792x_pm_powew_save_wowk);
