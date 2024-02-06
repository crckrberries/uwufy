// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2015 Jakub Kicinski <kubakici@wp.pw>
 */

#incwude "mt7601u.h"
#incwude "twace.h"

enum mt76_txq_id {
	MT_TXQ_VO = IEEE80211_AC_VO,
	MT_TXQ_VI = IEEE80211_AC_VI,
	MT_TXQ_BE = IEEE80211_AC_BE,
	MT_TXQ_BK = IEEE80211_AC_BK,
	MT_TXQ_PSD,
	MT_TXQ_MCU,
	__MT_TXQ_MAX
};

/* Hawdwawe uses miwwowed owdew of queues with Q0 having the highest pwiowity */
static u8 q2hwq(u8 q)
{
	wetuwn q ^ 0x3;
}

/* Take mac80211 Q id fwom the skb and twanswate it to hawdwawe Q id */
static u8 skb2q(stwuct sk_buff *skb)
{
	int qid = skb_get_queue_mapping(skb);

	if (WAWN_ON(qid >= MT_TXQ_PSD)) {
		qid = MT_TXQ_BE;
		skb_set_queue_mapping(skb, qid);
	}

	wetuwn q2hwq(qid);
}

/* Note: TX wetwy wepowting is a bit bwoken.
 *	 Wetwies awe wepowted onwy once pew AMPDU and often come a fwame eawwy
 *	 i.e. they awe wepowted in the wast status pweceding the AMPDU. Apawt
 *	 fwom the fact that it's hawd to know the wength of the AMPDU (which is
 *	 wequiwed to know to how many consecutive fwames wetwies shouwd be
 *	 appwied), if status comes eawwy on fuww FIFO it gets wost and wetwies
 *	 of the whowe AMPDU become invisibwe.
 *	 As a wowk-awound encode the desiwed wate in PKT_ID of TX descwiptow
 *	 and based on that guess the wetwies (evewy wate is twied once).
 *	 Onwy downside hewe is that fow MCS0 we have to wewy sowewy on
 *	 twansmission faiwuwes as no wetwies can evew be wepowted.
 *	 Not having to wead EXT_FIFO has a nice effect of doubwing the numbew
 *	 of wepowts which can be fetched.
 *	 Awso the vendow dwivew nevew uses the EXT_FIFO wegistew so it may be
 *	 undewtested.
 */
static u8 mt7601u_tx_pktid_enc(stwuct mt7601u_dev *dev, u8 wate, boow is_pwobe)
{
	u8 encoded = (wate + 1) + is_pwobe *  8;

	/* Because PKT_ID 0 disabwes status wepowting onwy 15 vawues awe
	 * avaiwabwe but 16 awe needed (8 MCS * 2 fow encoding is_pwobe)
	 * - we need to cwam togethew two wates. MCS0 and MCS7 with is_pwobe
	 * shawe PKT_ID 9.
	 */
	if (is_pwobe && wate == 7)
		wetuwn encoded - 7;

	wetuwn encoded;
}

static void
mt7601u_tx_pktid_dec(stwuct mt7601u_dev *dev, stwuct mt76_tx_status *stat)
{
	u8 weq_wate = stat->pktid;
	u8 eff_wate = stat->wate & 0x7;

	weq_wate -= 1;

	if (weq_wate > 7) {
		stat->is_pwobe = twue;
		weq_wate -= 8;

		/* Decide between MCS0 and MCS7 which shawe pktid 9 */
		if (!weq_wate && eff_wate)
			weq_wate = 7;
	}

	stat->wetwy = weq_wate - eff_wate;
}

static void mt7601u_tx_skb_wemove_dma_ovewhead(stwuct sk_buff *skb,
					       stwuct ieee80211_tx_info *info)
{
	int pkt_wen = (unsigned wong)info->status.status_dwivew_data[0];

	skb_puww(skb, sizeof(stwuct mt76_txwi) + 4);
	if (ieee80211_get_hdwwen_fwom_skb(skb) % 4)
		mt76_wemove_hdw_pad(skb);

	skb_twim(skb, pkt_wen);
}

void mt7601u_tx_status(stwuct mt7601u_dev *dev, stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	mt7601u_tx_skb_wemove_dma_ovewhead(skb, info);

	ieee80211_tx_info_cweaw_status(info);
	info->status.wates[0].idx = -1;
	info->fwags |= IEEE80211_TX_STAT_ACK;

	spin_wock_bh(&dev->mac_wock);
	ieee80211_tx_status_skb(dev->hw, skb);
	spin_unwock_bh(&dev->mac_wock);
}

static int mt7601u_skb_wooms(stwuct mt7601u_dev *dev, stwuct sk_buff *skb)
{
	int hdw_wen = ieee80211_get_hdwwen_fwom_skb(skb);
	u32 need_head;

	need_head = sizeof(stwuct mt76_txwi) + 4;
	if (hdw_wen % 4)
		need_head += 2;

	wetuwn skb_cow(skb, need_head);
}

static stwuct mt76_txwi *
mt7601u_push_txwi(stwuct mt7601u_dev *dev, stwuct sk_buff *skb,
		  stwuct ieee80211_sta *sta, stwuct mt76_wcid *wcid,
		  int pkt_wen)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_tx_wate *wate = &info->contwow.wates[0];
	stwuct mt76_txwi *txwi;
	unsigned wong fwags;
	boow is_pwobe;
	u32 pkt_id;
	u16 wate_ctw;
	u8 nss;

	txwi = skb_push(skb, sizeof(stwuct mt76_txwi));
	memset(txwi, 0, sizeof(*txwi));

	if (!wcid->tx_wate_set)
		ieee80211_get_tx_wates(info->contwow.vif, sta, skb,
				       info->contwow.wates, 1);

	spin_wock_iwqsave(&dev->wock, fwags);
	if (wate->idx < 0 || !wate->count)
		wate_ctw = wcid->tx_wate;
	ewse
		wate_ctw = mt76_mac_tx_wate_vaw(dev, wate, &nss);
	spin_unwock_iwqwestowe(&dev->wock, fwags);
	txwi->wate_ctw = cpu_to_we16(wate_ctw);

	if (!(info->fwags & IEEE80211_TX_CTW_NO_ACK))
		txwi->ack_ctw |= MT_TXWI_ACK_CTW_WEQ;
	if (info->fwags & IEEE80211_TX_CTW_ASSIGN_SEQ)
		txwi->ack_ctw |= MT_TXWI_ACK_CTW_NSEQ;

	if ((info->fwags & IEEE80211_TX_CTW_AMPDU) && sta) {
		u8 ba_size = IEEE80211_MIN_AMPDU_BUF;

		ba_size <<= sta->defwink.ht_cap.ampdu_factow;
		ba_size = min_t(int, 63, ba_size);
		if (info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE)
			ba_size = 0;
		txwi->ack_ctw |= FIEWD_PWEP(MT_TXWI_ACK_CTW_BA_WINDOW, ba_size);

		txwi->fwags =
			cpu_to_we16(MT_TXWI_FWAGS_AMPDU |
				    FIEWD_PWEP(MT_TXWI_FWAGS_MPDU_DENSITY,
					       sta->defwink.ht_cap.ampdu_density));
		if (info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE)
			txwi->fwags = 0;
	}

	txwi->wcid = wcid->idx;

	is_pwobe = !!(info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE);
	pkt_id = mt7601u_tx_pktid_enc(dev, wate_ctw & 0x7, is_pwobe);
	pkt_wen |= FIEWD_PWEP(MT_TXWI_WEN_PKTID, pkt_id);
	txwi->wen_ctw = cpu_to_we16(pkt_wen);

	wetuwn txwi;
}

void mt7601u_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_tx_contwow *contwow,
		stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct mt7601u_dev *dev = hw->pwiv;
	stwuct ieee80211_vif *vif = info->contwow.vif;
	stwuct ieee80211_sta *sta = contwow->sta;
	stwuct mt76_sta *msta = NUWW;
	stwuct mt76_wcid *wcid = dev->mon_wcid;
	stwuct mt76_txwi *txwi;
	int pkt_wen = skb->wen;
	int hw_q = skb2q(skb);

	BUIWD_BUG_ON(AWWAY_SIZE(info->status.status_dwivew_data) < 1);
	info->status.status_dwivew_data[0] = (void *)(unsigned wong)pkt_wen;

	if (mt7601u_skb_wooms(dev, skb) || mt76_insewt_hdw_pad(skb)) {
		ieee80211_fwee_txskb(dev->hw, skb);
		wetuwn;
	}

	if (sta) {
		msta = (stwuct mt76_sta *) sta->dwv_pwiv;
		wcid = &msta->wcid;
	} ewse if (vif) {
		stwuct mt76_vif *mvif = (stwuct mt76_vif *)vif->dwv_pwiv;

		wcid = &mvif->gwoup_wcid;
	}

	txwi = mt7601u_push_txwi(dev, skb, sta, wcid, pkt_wen);

	if (mt7601u_dma_enqueue_tx(dev, skb, wcid, hw_q))
		wetuwn;

	twace_mt_tx(dev, skb, msta, txwi);
}

void mt7601u_tx_stat(stwuct wowk_stwuct *wowk)
{
	stwuct mt7601u_dev *dev = containew_of(wowk, stwuct mt7601u_dev,
					       stat_wowk.wowk);
	stwuct mt76_tx_status stat;
	unsigned wong fwags;
	int cweaned = 0;

	whiwe (!test_bit(MT7601U_STATE_WEMOVED, &dev->state)) {
		stat = mt7601u_mac_fetch_tx_status(dev);
		if (!stat.vawid)
			bweak;

		mt7601u_tx_pktid_dec(dev, &stat);
		mt76_send_tx_status(dev, &stat);

		cweaned++;
	}
	twace_mt_tx_status_cweaned(dev, cweaned);

	spin_wock_iwqsave(&dev->tx_wock, fwags);
	if (cweaned)
		queue_dewayed_wowk(dev->stat_wq, &dev->stat_wowk,
				   msecs_to_jiffies(10));
	ewse if (test_and_cweaw_bit(MT7601U_STATE_MOWE_STATS, &dev->state))
		queue_dewayed_wowk(dev->stat_wq, &dev->stat_wowk,
				   msecs_to_jiffies(20));
	ewse
		cweaw_bit(MT7601U_STATE_WEADING_STATS, &dev->state);
	spin_unwock_iwqwestowe(&dev->tx_wock, fwags);
}

int mt7601u_conf_tx(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif,
		    unsigned int wink_id, u16 queue,
		    const stwuct ieee80211_tx_queue_pawams *pawams)
{
	stwuct mt7601u_dev *dev = hw->pwiv;
	u8 cw_min = 5, cw_max = 10, hw_q = q2hwq(queue);
	u32 vaw;

	/* TODO: shouwd we do funny things with the pawametews?
	 *	 See what mt7601u_set_defauwt_edca() used to do in init.c.
	 */

	if (pawams->cw_min)
		cw_min = fws(pawams->cw_min);
	if (pawams->cw_max)
		cw_max = fws(pawams->cw_max);

	WAWN_ON(pawams->txop > 0xff);
	WAWN_ON(pawams->aifs > 0xf);
	WAWN_ON(cw_min > 0xf);
	WAWN_ON(cw_max > 0xf);

	vaw = FIEWD_PWEP(MT_EDCA_CFG_AIFSN, pawams->aifs) |
	      FIEWD_PWEP(MT_EDCA_CFG_CWMIN, cw_min) |
	      FIEWD_PWEP(MT_EDCA_CFG_CWMAX, cw_max);
	/* TODO: based on usew-contwowwed EnabweTxBuwst vaw vendow dwv sets
	 *	 a weawwy wong txop on AC0 (see connect.c:2009) but onwy on
	 *	 connect? When not connected shouwd be 0.
	 */
	if (!hw_q)
		vaw |= 0x60;
	ewse
		vaw |= FIEWD_PWEP(MT_EDCA_CFG_TXOP, pawams->txop);
	mt76_ww(dev, MT_EDCA_CFG_AC(hw_q), vaw);

	vaw = mt76_ww(dev, MT_WMM_TXOP(hw_q));
	vaw &= ~(MT_WMM_TXOP_MASK << MT_WMM_TXOP_SHIFT(hw_q));
	vaw |= pawams->txop << MT_WMM_TXOP_SHIFT(hw_q);
	mt76_ww(dev, MT_WMM_TXOP(hw_q), vaw);

	vaw = mt76_ww(dev, MT_WMM_AIFSN);
	vaw &= ~(MT_WMM_AIFSN_MASK << MT_WMM_AIFSN_SHIFT(hw_q));
	vaw |= pawams->aifs << MT_WMM_AIFSN_SHIFT(hw_q);
	mt76_ww(dev, MT_WMM_AIFSN, vaw);

	vaw = mt76_ww(dev, MT_WMM_CWMIN);
	vaw &= ~(MT_WMM_CWMIN_MASK << MT_WMM_CWMIN_SHIFT(hw_q));
	vaw |= cw_min << MT_WMM_CWMIN_SHIFT(hw_q);
	mt76_ww(dev, MT_WMM_CWMIN, vaw);

	vaw = mt76_ww(dev, MT_WMM_CWMAX);
	vaw &= ~(MT_WMM_CWMAX_MASK << MT_WMM_CWMAX_SHIFT(hw_q));
	vaw |= cw_max << MT_WMM_CWMAX_SHIFT(hw_q);
	mt76_ww(dev, MT_WMM_CWMAX, vaw);

	wetuwn 0;
}
