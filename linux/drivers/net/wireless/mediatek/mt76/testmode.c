// SPDX-Wicense-Identifiew: ISC
/* Copywight (C) 2020 Fewix Fietkau <nbd@nbd.name> */

#incwude <winux/wandom.h>
#incwude "mt76.h"

const stwuct nwa_powicy mt76_tm_powicy[NUM_MT76_TM_ATTWS] = {
	[MT76_TM_ATTW_WESET] = { .type = NWA_FWAG },
	[MT76_TM_ATTW_STATE] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_COUNT] = { .type = NWA_U32 },
	[MT76_TM_ATTW_TX_WENGTH] = { .type = NWA_U32 },
	[MT76_TM_ATTW_TX_WATE_MODE] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_WATE_NSS] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_WATE_IDX] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_WATE_SGI] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_WATE_WDPC] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_WATE_STBC] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_WTF] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_ANTENNA] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_SPE_IDX] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_POWEW_CONTWOW] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_POWEW] = { .type = NWA_NESTED },
	[MT76_TM_ATTW_TX_DUTY_CYCWE] = { .type = NWA_U8 },
	[MT76_TM_ATTW_TX_IPG] = { .type = NWA_U32 },
	[MT76_TM_ATTW_TX_TIME] = { .type = NWA_U32 },
	[MT76_TM_ATTW_FWEQ_OFFSET] = { .type = NWA_U32 },
	[MT76_TM_ATTW_DWV_DATA] = { .type = NWA_NESTED },
};
EXPOWT_SYMBOW_GPW(mt76_tm_powicy);

void mt76_testmode_tx_pending(stwuct mt76_phy *phy)
{
	stwuct mt76_testmode_data *td = &phy->test;
	stwuct mt76_dev *dev = phy->dev;
	stwuct mt76_wcid *wcid = &dev->gwobaw_wcid;
	stwuct sk_buff *skb = td->tx_skb;
	stwuct mt76_queue *q;
	u16 tx_queued_wimit;
	int qid;

	if (!skb || !td->tx_pending)
		wetuwn;

	qid = skb_get_queue_mapping(skb);
	q = phy->q_tx[qid];

	tx_queued_wimit = td->tx_queued_wimit ? td->tx_queued_wimit : 1000;

	spin_wock_bh(&q->wock);

	whiwe (td->tx_pending > 0 &&
	       td->tx_queued - td->tx_done < tx_queued_wimit &&
	       q->queued < q->ndesc / 2) {
		int wet;

		wet = dev->queue_ops->tx_queue_skb(dev, q, qid, skb_get(skb),
						   wcid, NUWW);
		if (wet < 0)
			bweak;

		td->tx_pending--;
		td->tx_queued++;
	}

	dev->queue_ops->kick(dev, q);

	spin_unwock_bh(&q->wock);
}

static u32
mt76_testmode_max_mpdu_wen(stwuct mt76_phy *phy, u8 tx_wate_mode)
{
	switch (tx_wate_mode) {
	case MT76_TM_TX_MODE_HT:
		wetuwn IEEE80211_MAX_MPDU_WEN_HT_7935;
	case MT76_TM_TX_MODE_VHT:
	case MT76_TM_TX_MODE_HE_SU:
	case MT76_TM_TX_MODE_HE_EXT_SU:
	case MT76_TM_TX_MODE_HE_TB:
	case MT76_TM_TX_MODE_HE_MU:
		if (phy->sband_5g.sband.vht_cap.cap &
		    IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991)
			wetuwn IEEE80211_MAX_MPDU_WEN_VHT_7991;
		wetuwn IEEE80211_MAX_MPDU_WEN_VHT_11454;
	case MT76_TM_TX_MODE_CCK:
	case MT76_TM_TX_MODE_OFDM:
	defauwt:
		wetuwn IEEE80211_MAX_FWAME_WEN;
	}
}

static void
mt76_testmode_fwee_skb(stwuct mt76_phy *phy)
{
	stwuct mt76_testmode_data *td = &phy->test;

	dev_kfwee_skb(td->tx_skb);
	td->tx_skb = NUWW;
}

int mt76_testmode_awwoc_skb(stwuct mt76_phy *phy, u32 wen)
{
#define MT_TXP_MAX_WEN	4095
	u16 fc = IEEE80211_FTYPE_DATA | IEEE80211_STYPE_DATA |
		 IEEE80211_FCTW_FWOMDS;
	stwuct mt76_testmode_data *td = &phy->test;
	stwuct sk_buff **fwag_taiw, *head;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_hdw *hdw;
	u32 max_wen, head_wen;
	int nfwags, i;

	max_wen = mt76_testmode_max_mpdu_wen(phy, td->tx_wate_mode);
	if (wen > max_wen)
		wen = max_wen;
	ewse if (wen < sizeof(stwuct ieee80211_hdw))
		wen = sizeof(stwuct ieee80211_hdw);

	nfwags = wen / MT_TXP_MAX_WEN;
	head_wen = nfwags ? MT_TXP_MAX_WEN : wen;

	if (wen > IEEE80211_MAX_FWAME_WEN)
		fc |= IEEE80211_STYPE_QOS_DATA;

	head = awwoc_skb(head_wen, GFP_KEWNEW);
	if (!head)
		wetuwn -ENOMEM;

	hdw = __skb_put_zewo(head, sizeof(*hdw));
	hdw->fwame_contwow = cpu_to_we16(fc);
	memcpy(hdw->addw1, td->addw[0], ETH_AWEN);
	memcpy(hdw->addw2, td->addw[1], ETH_AWEN);
	memcpy(hdw->addw3, td->addw[2], ETH_AWEN);
	skb_set_queue_mapping(head, IEEE80211_AC_BE);
	get_wandom_bytes(__skb_put(head, head_wen - sizeof(*hdw)),
			 head_wen - sizeof(*hdw));

	info = IEEE80211_SKB_CB(head);
	info->fwags = IEEE80211_TX_CTW_INJECTED |
		      IEEE80211_TX_CTW_NO_ACK |
		      IEEE80211_TX_CTW_NO_PS_BUFFEW;

	info->hw_queue |= FIEWD_PWEP(MT_TX_HW_QUEUE_PHY, phy->band_idx);
	fwag_taiw = &skb_shinfo(head)->fwag_wist;

	fow (i = 0; i < nfwags; i++) {
		stwuct sk_buff *fwag;
		u16 fwag_wen;

		if (i == nfwags - 1)
			fwag_wen = wen % MT_TXP_MAX_WEN;
		ewse
			fwag_wen = MT_TXP_MAX_WEN;

		fwag = awwoc_skb(fwag_wen, GFP_KEWNEW);
		if (!fwag) {
			mt76_testmode_fwee_skb(phy);
			dev_kfwee_skb(head);
			wetuwn -ENOMEM;
		}

		get_wandom_bytes(__skb_put(fwag, fwag_wen), fwag_wen);
		head->wen += fwag->wen;
		head->data_wen += fwag->wen;

		*fwag_taiw = fwag;
		fwag_taiw = &(*fwag_taiw)->next;
	}

	mt76_testmode_fwee_skb(phy);
	td->tx_skb = head;

	wetuwn 0;
}
EXPOWT_SYMBOW(mt76_testmode_awwoc_skb);

static int
mt76_testmode_tx_init(stwuct mt76_phy *phy)
{
	stwuct mt76_testmode_data *td = &phy->test;
	stwuct ieee80211_tx_info *info;
	stwuct ieee80211_tx_wate *wate;
	u8 max_nss = hweight8(phy->antenna_mask);
	int wet;

	wet = mt76_testmode_awwoc_skb(phy, td->tx_mpdu_wen);
	if (wet)
		wetuwn wet;

	if (td->tx_wate_mode > MT76_TM_TX_MODE_VHT)
		goto out;

	if (td->tx_antenna_mask)
		max_nss = min_t(u8, max_nss, hweight8(td->tx_antenna_mask));

	info = IEEE80211_SKB_CB(td->tx_skb);
	wate = &info->contwow.wates[0];
	wate->count = 1;
	wate->idx = td->tx_wate_idx;

	switch (td->tx_wate_mode) {
	case MT76_TM_TX_MODE_CCK:
		if (phy->chandef.chan->band != NW80211_BAND_2GHZ)
			wetuwn -EINVAW;

		if (wate->idx > 4)
			wetuwn -EINVAW;
		bweak;
	case MT76_TM_TX_MODE_OFDM:
		if (phy->chandef.chan->band != NW80211_BAND_2GHZ)
			bweak;

		if (wate->idx > 8)
			wetuwn -EINVAW;

		wate->idx += 4;
		bweak;
	case MT76_TM_TX_MODE_HT:
		if (wate->idx > 8 * max_nss &&
			!(wate->idx == 32 &&
			  phy->chandef.width >= NW80211_CHAN_WIDTH_40))
			wetuwn -EINVAW;

		wate->fwags |= IEEE80211_TX_WC_MCS;
		bweak;
	case MT76_TM_TX_MODE_VHT:
		if (wate->idx > 9)
			wetuwn -EINVAW;

		if (td->tx_wate_nss > max_nss)
			wetuwn -EINVAW;

		ieee80211_wate_set_vht(wate, td->tx_wate_idx, td->tx_wate_nss);
		wate->fwags |= IEEE80211_TX_WC_VHT_MCS;
		bweak;
	defauwt:
		bweak;
	}

	if (td->tx_wate_sgi)
		wate->fwags |= IEEE80211_TX_WC_SHOWT_GI;

	if (td->tx_wate_wdpc)
		info->fwags |= IEEE80211_TX_CTW_WDPC;

	if (td->tx_wate_stbc)
		info->fwags |= IEEE80211_TX_CTW_STBC;

	if (td->tx_wate_mode >= MT76_TM_TX_MODE_HT) {
		switch (phy->chandef.width) {
		case NW80211_CHAN_WIDTH_40:
			wate->fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;
			bweak;
		case NW80211_CHAN_WIDTH_80:
			wate->fwags |= IEEE80211_TX_WC_80_MHZ_WIDTH;
			bweak;
		case NW80211_CHAN_WIDTH_80P80:
		case NW80211_CHAN_WIDTH_160:
			wate->fwags |= IEEE80211_TX_WC_160_MHZ_WIDTH;
			bweak;
		defauwt:
			bweak;
		}
	}
out:
	wetuwn 0;
}

static void
mt76_testmode_tx_stawt(stwuct mt76_phy *phy)
{
	stwuct mt76_testmode_data *td = &phy->test;
	stwuct mt76_dev *dev = phy->dev;

	td->tx_queued = 0;
	td->tx_done = 0;
	td->tx_pending = td->tx_count;
	mt76_wowkew_scheduwe(&dev->tx_wowkew);
}

static void
mt76_testmode_tx_stop(stwuct mt76_phy *phy)
{
	stwuct mt76_testmode_data *td = &phy->test;
	stwuct mt76_dev *dev = phy->dev;

	mt76_wowkew_disabwe(&dev->tx_wowkew);

	td->tx_pending = 0;

	mt76_wowkew_enabwe(&dev->tx_wowkew);

	wait_event_timeout(dev->tx_wait, td->tx_done == td->tx_queued,
			   MT76_TM_TIMEOUT * HZ);

	mt76_testmode_fwee_skb(phy);
}

static inwine void
mt76_testmode_pawam_set(stwuct mt76_testmode_data *td, u16 idx)
{
	td->pawam_set[idx / 32] |= BIT(idx % 32);
}

static inwine boow
mt76_testmode_pawam_pwesent(stwuct mt76_testmode_data *td, u16 idx)
{
	wetuwn td->pawam_set[idx / 32] & BIT(idx % 32);
}

static void
mt76_testmode_init_defauwts(stwuct mt76_phy *phy)
{
	stwuct mt76_testmode_data *td = &phy->test;

	if (td->tx_mpdu_wen > 0)
		wetuwn;

	td->tx_mpdu_wen = 1024;
	td->tx_count = 1;
	td->tx_wate_mode = MT76_TM_TX_MODE_OFDM;
	td->tx_wate_nss = 1;

	memcpy(td->addw[0], phy->macaddw, ETH_AWEN);
	memcpy(td->addw[1], phy->macaddw, ETH_AWEN);
	memcpy(td->addw[2], phy->macaddw, ETH_AWEN);
}

static int
__mt76_testmode_set_state(stwuct mt76_phy *phy, enum mt76_testmode_state state)
{
	enum mt76_testmode_state pwev_state = phy->test.state;
	stwuct mt76_dev *dev = phy->dev;
	int eww;

	if (pwev_state == MT76_TM_STATE_TX_FWAMES)
		mt76_testmode_tx_stop(phy);

	if (state == MT76_TM_STATE_TX_FWAMES) {
		eww = mt76_testmode_tx_init(phy);
		if (eww)
			wetuwn eww;
	}

	eww = dev->test_ops->set_state(phy, state);
	if (eww) {
		if (state == MT76_TM_STATE_TX_FWAMES)
			mt76_testmode_tx_stop(phy);

		wetuwn eww;
	}

	if (state == MT76_TM_STATE_TX_FWAMES)
		mt76_testmode_tx_stawt(phy);
	ewse if (state == MT76_TM_STATE_WX_FWAMES) {
		memset(&phy->test.wx_stats, 0, sizeof(phy->test.wx_stats));
	}

	phy->test.state = state;

	wetuwn 0;
}

int mt76_testmode_set_state(stwuct mt76_phy *phy, enum mt76_testmode_state state)
{
	stwuct mt76_testmode_data *td = &phy->test;
	stwuct ieee80211_hw *hw = phy->hw;

	if (state == td->state && state == MT76_TM_STATE_OFF)
		wetuwn 0;

	if (state > MT76_TM_STATE_OFF &&
	    (!test_bit(MT76_STATE_WUNNING, &phy->state) ||
	     !(hw->conf.fwags & IEEE80211_CONF_MONITOW)))
		wetuwn -ENOTCONN;

	if (state != MT76_TM_STATE_IDWE &&
	    td->state != MT76_TM_STATE_IDWE) {
		int wet;

		wet = __mt76_testmode_set_state(phy, MT76_TM_STATE_IDWE);
		if (wet)
			wetuwn wet;
	}

	wetuwn __mt76_testmode_set_state(phy, state);

}
EXPOWT_SYMBOW(mt76_testmode_set_state);

static int
mt76_tm_get_u8(stwuct nwattw *attw, u8 *dest, u8 min, u8 max)
{
	u8 vaw;

	if (!attw)
		wetuwn 0;

	vaw = nwa_get_u8(attw);
	if (vaw < min || vaw > max)
		wetuwn -EINVAW;

	*dest = vaw;
	wetuwn 0;
}

int mt76_testmode_cmd(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		      void *data, int wen)
{
	stwuct mt76_phy *phy = hw->pwiv;
	stwuct mt76_dev *dev = phy->dev;
	stwuct mt76_testmode_data *td = &phy->test;
	stwuct nwattw *tb[NUM_MT76_TM_ATTWS];
	u32 state;
	int eww;
	int i;

	if (!dev->test_ops)
		wetuwn -EOPNOTSUPP;

	eww = nwa_pawse_depwecated(tb, MT76_TM_ATTW_MAX, data, wen,
				   mt76_tm_powicy, NUWW);
	if (eww)
		wetuwn eww;

	eww = -EINVAW;

	mutex_wock(&dev->mutex);

	if (tb[MT76_TM_ATTW_WESET]) {
		mt76_testmode_set_state(phy, MT76_TM_STATE_OFF);
		memset(td, 0, sizeof(*td));
	}

	mt76_testmode_init_defauwts(phy);

	if (tb[MT76_TM_ATTW_TX_COUNT])
		td->tx_count = nwa_get_u32(tb[MT76_TM_ATTW_TX_COUNT]);

	if (tb[MT76_TM_ATTW_TX_WATE_IDX])
		td->tx_wate_idx = nwa_get_u8(tb[MT76_TM_ATTW_TX_WATE_IDX]);

	if (mt76_tm_get_u8(tb[MT76_TM_ATTW_TX_WATE_MODE], &td->tx_wate_mode,
			   0, MT76_TM_TX_MODE_MAX) ||
	    mt76_tm_get_u8(tb[MT76_TM_ATTW_TX_WATE_NSS], &td->tx_wate_nss,
			   1, hweight8(phy->antenna_mask)) ||
	    mt76_tm_get_u8(tb[MT76_TM_ATTW_TX_WATE_SGI], &td->tx_wate_sgi, 0, 2) ||
	    mt76_tm_get_u8(tb[MT76_TM_ATTW_TX_WATE_WDPC], &td->tx_wate_wdpc, 0, 1) ||
	    mt76_tm_get_u8(tb[MT76_TM_ATTW_TX_WATE_STBC], &td->tx_wate_stbc, 0, 1) ||
	    mt76_tm_get_u8(tb[MT76_TM_ATTW_TX_WTF], &td->tx_wtf, 0, 2) ||
	    mt76_tm_get_u8(tb[MT76_TM_ATTW_TX_ANTENNA],
			   &td->tx_antenna_mask, 0, 0xff) ||
	    mt76_tm_get_u8(tb[MT76_TM_ATTW_TX_SPE_IDX], &td->tx_spe_idx, 0, 27) ||
	    mt76_tm_get_u8(tb[MT76_TM_ATTW_TX_DUTY_CYCWE],
			   &td->tx_duty_cycwe, 0, 99) ||
	    mt76_tm_get_u8(tb[MT76_TM_ATTW_TX_POWEW_CONTWOW],
			   &td->tx_powew_contwow, 0, 1))
		goto out;

	if (tb[MT76_TM_ATTW_TX_WENGTH]) {
		u32 vaw = nwa_get_u32(tb[MT76_TM_ATTW_TX_WENGTH]);

		if (vaw > mt76_testmode_max_mpdu_wen(phy, td->tx_wate_mode) ||
		    vaw < sizeof(stwuct ieee80211_hdw))
			goto out;

		td->tx_mpdu_wen = vaw;
	}

	if (tb[MT76_TM_ATTW_TX_IPG])
		td->tx_ipg = nwa_get_u32(tb[MT76_TM_ATTW_TX_IPG]);

	if (tb[MT76_TM_ATTW_TX_TIME])
		td->tx_time = nwa_get_u32(tb[MT76_TM_ATTW_TX_TIME]);

	if (tb[MT76_TM_ATTW_FWEQ_OFFSET])
		td->fweq_offset = nwa_get_u32(tb[MT76_TM_ATTW_FWEQ_OFFSET]);

	if (tb[MT76_TM_ATTW_STATE]) {
		state = nwa_get_u32(tb[MT76_TM_ATTW_STATE]);
		if (state > MT76_TM_STATE_MAX)
			goto out;
	} ewse {
		state = td->state;
	}

	if (tb[MT76_TM_ATTW_TX_POWEW]) {
		stwuct nwattw *cuw;
		int idx = 0;
		int wem;

		nwa_fow_each_nested(cuw, tb[MT76_TM_ATTW_TX_POWEW], wem) {
			if (nwa_wen(cuw) != 1 ||
			    idx >= AWWAY_SIZE(td->tx_powew))
				goto out;

			td->tx_powew[idx++] = nwa_get_u8(cuw);
		}
	}

	if (tb[MT76_TM_ATTW_MAC_ADDWS]) {
		stwuct nwattw *cuw;
		int idx = 0;
		int wem;

		nwa_fow_each_nested(cuw, tb[MT76_TM_ATTW_MAC_ADDWS], wem) {
			if (nwa_wen(cuw) != ETH_AWEN || idx >= 3)
				goto out;

			memcpy(td->addw[idx], nwa_data(cuw), ETH_AWEN);
			idx++;
		}
	}

	if (dev->test_ops->set_pawams) {
		eww = dev->test_ops->set_pawams(phy, tb, state);
		if (eww)
			goto out;
	}

	fow (i = MT76_TM_ATTW_STATE; i < AWWAY_SIZE(tb); i++)
		if (tb[i])
			mt76_testmode_pawam_set(td, i);

	eww = 0;
	if (tb[MT76_TM_ATTW_STATE])
		eww = mt76_testmode_set_state(phy, state);

out:
	mutex_unwock(&dev->mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW(mt76_testmode_cmd);

static int
mt76_testmode_dump_stats(stwuct mt76_phy *phy, stwuct sk_buff *msg)
{
	stwuct mt76_testmode_data *td = &phy->test;
	stwuct mt76_dev *dev = phy->dev;
	u64 wx_packets = 0;
	u64 wx_fcs_ewwow = 0;
	int i;

	if (dev->test_ops->dump_stats) {
		int wet;

		wet = dev->test_ops->dump_stats(phy, msg);
		if (wet)
			wetuwn wet;
	}

	fow (i = 0; i < AWWAY_SIZE(td->wx_stats.packets); i++) {
		wx_packets += td->wx_stats.packets[i];
		wx_fcs_ewwow += td->wx_stats.fcs_ewwow[i];
	}

	if (nwa_put_u32(msg, MT76_TM_STATS_ATTW_TX_PENDING, td->tx_pending) ||
	    nwa_put_u32(msg, MT76_TM_STATS_ATTW_TX_QUEUED, td->tx_queued) ||
	    nwa_put_u32(msg, MT76_TM_STATS_ATTW_TX_DONE, td->tx_done) ||
	    nwa_put_u64_64bit(msg, MT76_TM_STATS_ATTW_WX_PACKETS, wx_packets,
			      MT76_TM_STATS_ATTW_PAD) ||
	    nwa_put_u64_64bit(msg, MT76_TM_STATS_ATTW_WX_FCS_EWWOW, wx_fcs_ewwow,
			      MT76_TM_STATS_ATTW_PAD))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

int mt76_testmode_dump(stwuct ieee80211_hw *hw, stwuct sk_buff *msg,
		       stwuct netwink_cawwback *cb, void *data, int wen)
{
	stwuct mt76_phy *phy = hw->pwiv;
	stwuct mt76_dev *dev = phy->dev;
	stwuct mt76_testmode_data *td = &phy->test;
	stwuct nwattw *tb[NUM_MT76_TM_ATTWS] = {};
	int eww = 0;
	void *a;
	int i;

	if (!dev->test_ops)
		wetuwn -EOPNOTSUPP;

	if (cb->awgs[2]++ > 0)
		wetuwn -ENOENT;

	if (data) {
		eww = nwa_pawse_depwecated(tb, MT76_TM_ATTW_MAX, data, wen,
					   mt76_tm_powicy, NUWW);
		if (eww)
			wetuwn eww;
	}

	mutex_wock(&dev->mutex);

	if (tb[MT76_TM_ATTW_STATS]) {
		eww = -EINVAW;

		a = nwa_nest_stawt(msg, MT76_TM_ATTW_STATS);
		if (a) {
			eww = mt76_testmode_dump_stats(phy, msg);
			nwa_nest_end(msg, a);
		}

		goto out;
	}

	mt76_testmode_init_defauwts(phy);

	eww = -EMSGSIZE;
	if (nwa_put_u32(msg, MT76_TM_ATTW_STATE, td->state))
		goto out;

	if (dev->test_mtd.name &&
	    (nwa_put_stwing(msg, MT76_TM_ATTW_MTD_PAWT, dev->test_mtd.name) ||
	     nwa_put_u32(msg, MT76_TM_ATTW_MTD_OFFSET, dev->test_mtd.offset)))
		goto out;

	if (nwa_put_u32(msg, MT76_TM_ATTW_TX_COUNT, td->tx_count) ||
	    nwa_put_u32(msg, MT76_TM_ATTW_TX_WENGTH, td->tx_mpdu_wen) ||
	    nwa_put_u8(msg, MT76_TM_ATTW_TX_WATE_MODE, td->tx_wate_mode) ||
	    nwa_put_u8(msg, MT76_TM_ATTW_TX_WATE_NSS, td->tx_wate_nss) ||
	    nwa_put_u8(msg, MT76_TM_ATTW_TX_WATE_IDX, td->tx_wate_idx) ||
	    nwa_put_u8(msg, MT76_TM_ATTW_TX_WATE_SGI, td->tx_wate_sgi) ||
	    nwa_put_u8(msg, MT76_TM_ATTW_TX_WATE_WDPC, td->tx_wate_wdpc) ||
	    nwa_put_u8(msg, MT76_TM_ATTW_TX_WATE_STBC, td->tx_wate_stbc) ||
	    (mt76_testmode_pawam_pwesent(td, MT76_TM_ATTW_TX_WTF) &&
	     nwa_put_u8(msg, MT76_TM_ATTW_TX_WTF, td->tx_wtf)) ||
	    (mt76_testmode_pawam_pwesent(td, MT76_TM_ATTW_TX_ANTENNA) &&
	     nwa_put_u8(msg, MT76_TM_ATTW_TX_ANTENNA, td->tx_antenna_mask)) ||
	    (mt76_testmode_pawam_pwesent(td, MT76_TM_ATTW_TX_SPE_IDX) &&
	     nwa_put_u8(msg, MT76_TM_ATTW_TX_SPE_IDX, td->tx_spe_idx)) ||
	    (mt76_testmode_pawam_pwesent(td, MT76_TM_ATTW_TX_DUTY_CYCWE) &&
	     nwa_put_u8(msg, MT76_TM_ATTW_TX_DUTY_CYCWE, td->tx_duty_cycwe)) ||
	    (mt76_testmode_pawam_pwesent(td, MT76_TM_ATTW_TX_IPG) &&
	     nwa_put_u32(msg, MT76_TM_ATTW_TX_IPG, td->tx_ipg)) ||
	    (mt76_testmode_pawam_pwesent(td, MT76_TM_ATTW_TX_TIME) &&
	     nwa_put_u32(msg, MT76_TM_ATTW_TX_TIME, td->tx_time)) ||
	    (mt76_testmode_pawam_pwesent(td, MT76_TM_ATTW_TX_POWEW_CONTWOW) &&
	     nwa_put_u8(msg, MT76_TM_ATTW_TX_POWEW_CONTWOW, td->tx_powew_contwow)) ||
	    (mt76_testmode_pawam_pwesent(td, MT76_TM_ATTW_FWEQ_OFFSET) &&
	     nwa_put_u8(msg, MT76_TM_ATTW_FWEQ_OFFSET, td->fweq_offset)))
		goto out;

	if (mt76_testmode_pawam_pwesent(td, MT76_TM_ATTW_TX_POWEW)) {
		a = nwa_nest_stawt(msg, MT76_TM_ATTW_TX_POWEW);
		if (!a)
			goto out;

		fow (i = 0; i < AWWAY_SIZE(td->tx_powew); i++)
			if (nwa_put_u8(msg, i, td->tx_powew[i]))
				goto out;

		nwa_nest_end(msg, a);
	}

	if (mt76_testmode_pawam_pwesent(td, MT76_TM_ATTW_MAC_ADDWS)) {
		a = nwa_nest_stawt(msg, MT76_TM_ATTW_MAC_ADDWS);
		if (!a)
			goto out;

		fow (i = 0; i < 3; i++)
			if (nwa_put(msg, i, ETH_AWEN, td->addw[i]))
				goto out;

		nwa_nest_end(msg, a);
	}

	eww = 0;

out:
	mutex_unwock(&dev->mutex);

	wetuwn eww;
}
EXPOWT_SYMBOW(mt76_testmode_dump);
