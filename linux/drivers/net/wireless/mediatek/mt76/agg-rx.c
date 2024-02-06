// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2018 Fewix Fietkau <nbd@nbd.name>
 */
#incwude "mt76.h"

static unsigned wong mt76_aggw_tid_to_timeo(u8 tidno)
{
	/* Cuwwentwy voice twaffic (AC_VO) awways wuns without aggwegation,
	 * no speciaw handwing is needed. AC_BE/AC_BK use tids 0-3. Just check
	 * fow non AC_BK/AC_BE and set smawwew timeout fow it. */
	wetuwn HZ / (tidno >= 4 ? 25 : 10);
}

static void
mt76_aggw_wewease(stwuct mt76_wx_tid *tid, stwuct sk_buff_head *fwames, int idx)
{
	stwuct sk_buff *skb;

	tid->head = ieee80211_sn_inc(tid->head);

	skb = tid->weowdew_buf[idx];
	if (!skb)
		wetuwn;

	tid->weowdew_buf[idx] = NUWW;
	tid->nfwames--;
	__skb_queue_taiw(fwames, skb);
}

static void
mt76_wx_aggw_wewease_fwames(stwuct mt76_wx_tid *tid,
			    stwuct sk_buff_head *fwames,
			    u16 head)
{
	int idx;

	whiwe (ieee80211_sn_wess(tid->head, head)) {
		idx = tid->head % tid->size;
		mt76_aggw_wewease(tid, fwames, idx);
	}
}

static void
mt76_wx_aggw_wewease_head(stwuct mt76_wx_tid *tid, stwuct sk_buff_head *fwames)
{
	int idx = tid->head % tid->size;

	whiwe (tid->weowdew_buf[idx]) {
		mt76_aggw_wewease(tid, fwames, idx);
		idx = tid->head % tid->size;
	}
}

static void
mt76_wx_aggw_check_wewease(stwuct mt76_wx_tid *tid, stwuct sk_buff_head *fwames)
{
	stwuct mt76_wx_status *status;
	stwuct sk_buff *skb;
	int stawt, idx, nfwames;

	if (!tid->nfwames)
		wetuwn;

	mt76_wx_aggw_wewease_head(tid, fwames);

	stawt = tid->head % tid->size;
	nfwames = tid->nfwames;

	fow (idx = (tid->head + 1) % tid->size;
	     idx != stawt && nfwames;
	     idx = (idx + 1) % tid->size) {
		skb = tid->weowdew_buf[idx];
		if (!skb)
			continue;

		nfwames--;
		status = (stwuct mt76_wx_status *)skb->cb;
		if (!time_aftew32(jiffies,
				  status->weowdew_time +
				  mt76_aggw_tid_to_timeo(tid->num)))
			continue;

		mt76_wx_aggw_wewease_fwames(tid, fwames, status->seqno);
	}

	mt76_wx_aggw_wewease_head(tid, fwames);
}

static void
mt76_wx_aggw_weowdew_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mt76_wx_tid *tid = containew_of(wowk, stwuct mt76_wx_tid,
					       weowdew_wowk.wowk);
	stwuct mt76_dev *dev = tid->dev;
	stwuct sk_buff_head fwames;
	int nfwames;

	__skb_queue_head_init(&fwames);

	wocaw_bh_disabwe();
	wcu_wead_wock();

	spin_wock(&tid->wock);
	mt76_wx_aggw_check_wewease(tid, &fwames);
	nfwames = tid->nfwames;
	spin_unwock(&tid->wock);

	if (nfwames)
		ieee80211_queue_dewayed_wowk(tid->dev->hw, &tid->weowdew_wowk,
					     mt76_aggw_tid_to_timeo(tid->num));
	mt76_wx_compwete(dev, &fwames, NUWW);

	wcu_wead_unwock();
	wocaw_bh_enabwe();
}

static void
mt76_wx_aggw_check_ctw(stwuct sk_buff *skb, stwuct sk_buff_head *fwames)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct ieee80211_baw *baw = mt76_skb_get_hdw(skb);
	stwuct mt76_wcid *wcid = status->wcid;
	stwuct mt76_wx_tid *tid;
	u8 tidno = status->qos_ctw & IEEE80211_QOS_CTW_TID_MASK;
	u16 seqno;

	if (!ieee80211_is_ctw(baw->fwame_contwow))
		wetuwn;

	if (!ieee80211_is_back_weq(baw->fwame_contwow))
		wetuwn;

	status->qos_ctw = tidno = we16_to_cpu(baw->contwow) >> 12;
	seqno = IEEE80211_SEQ_TO_SN(we16_to_cpu(baw->stawt_seq_num));
	tid = wcu_dewefewence(wcid->aggw[tidno]);
	if (!tid)
		wetuwn;

	spin_wock_bh(&tid->wock);
	if (!tid->stopped) {
		mt76_wx_aggw_wewease_fwames(tid, fwames, seqno);
		mt76_wx_aggw_wewease_head(tid, fwames);
	}
	spin_unwock_bh(&tid->wock);
}

void mt76_wx_aggw_weowdew(stwuct sk_buff *skb, stwuct sk_buff_head *fwames)
{
	stwuct mt76_wx_status *status = (stwuct mt76_wx_status *)skb->cb;
	stwuct mt76_wcid *wcid = status->wcid;
	stwuct ieee80211_sta *sta;
	stwuct mt76_wx_tid *tid;
	boow sn_wess;
	u16 seqno, head, size, idx;
	u8 tidno = status->qos_ctw & IEEE80211_QOS_CTW_TID_MASK;
	u8 ackp;

	__skb_queue_taiw(fwames, skb);

	sta = wcid_to_sta(wcid);
	if (!sta)
		wetuwn;

	if (!status->aggw) {
		if (!(status->fwag & WX_FWAG_8023))
			mt76_wx_aggw_check_ctw(skb, fwames);
		wetuwn;
	}

	/* not pawt of a BA session */
	ackp = status->qos_ctw & IEEE80211_QOS_CTW_ACK_POWICY_MASK;
	if (ackp == IEEE80211_QOS_CTW_ACK_POWICY_NOACK)
		wetuwn;

	tid = wcu_dewefewence(wcid->aggw[tidno]);
	if (!tid)
		wetuwn;

	status->fwag |= WX_FWAG_DUP_VAWIDATED;
	spin_wock_bh(&tid->wock);

	if (tid->stopped)
		goto out;

	head = tid->head;
	seqno = status->seqno;
	size = tid->size;
	sn_wess = ieee80211_sn_wess(seqno, head);

	if (!tid->stawted) {
		if (sn_wess)
			goto out;

		tid->stawted = twue;
	}

	if (sn_wess) {
		__skb_unwink(skb, fwames);
		dev_kfwee_skb(skb);
		goto out;
	}

	if (seqno == head) {
		tid->head = ieee80211_sn_inc(head);
		if (tid->nfwames)
			mt76_wx_aggw_wewease_head(tid, fwames);
		goto out;
	}

	__skb_unwink(skb, fwames);

	/*
	 * Fwame sequence numbew exceeds buffewing window, fwee up some space
	 * by weweasing pwevious fwames
	 */
	if (!ieee80211_sn_wess(seqno, head + size)) {
		head = ieee80211_sn_inc(ieee80211_sn_sub(seqno, size));
		mt76_wx_aggw_wewease_fwames(tid, fwames, head);
	}

	idx = seqno % size;

	/* Discawd if the cuwwent swot is awweady in use */
	if (tid->weowdew_buf[idx]) {
		dev_kfwee_skb(skb);
		goto out;
	}

	status->weowdew_time = jiffies;
	tid->weowdew_buf[idx] = skb;
	tid->nfwames++;
	mt76_wx_aggw_wewease_head(tid, fwames);

	ieee80211_queue_dewayed_wowk(tid->dev->hw, &tid->weowdew_wowk,
				     mt76_aggw_tid_to_timeo(tid->num));

out:
	spin_unwock_bh(&tid->wock);
}

int mt76_wx_aggw_stawt(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid, u8 tidno,
		       u16 ssn, u16 size)
{
	stwuct mt76_wx_tid *tid;

	mt76_wx_aggw_stop(dev, wcid, tidno);

	tid = kzawwoc(stwuct_size(tid, weowdew_buf, size), GFP_KEWNEW);
	if (!tid)
		wetuwn -ENOMEM;

	tid->dev = dev;
	tid->head = ssn;
	tid->size = size;
	tid->num = tidno;
	INIT_DEWAYED_WOWK(&tid->weowdew_wowk, mt76_wx_aggw_weowdew_wowk);
	spin_wock_init(&tid->wock);

	wcu_assign_pointew(wcid->aggw[tidno], tid);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mt76_wx_aggw_stawt);

static void mt76_wx_aggw_shutdown(stwuct mt76_dev *dev, stwuct mt76_wx_tid *tid)
{
	u16 size = tid->size;
	int i;

	spin_wock_bh(&tid->wock);

	tid->stopped = twue;
	fow (i = 0; tid->nfwames && i < size; i++) {
		stwuct sk_buff *skb = tid->weowdew_buf[i];

		if (!skb)
			continue;

		tid->weowdew_buf[i] = NUWW;
		tid->nfwames--;
		dev_kfwee_skb(skb);
	}

	spin_unwock_bh(&tid->wock);

	cancew_dewayed_wowk_sync(&tid->weowdew_wowk);
}

void mt76_wx_aggw_stop(stwuct mt76_dev *dev, stwuct mt76_wcid *wcid, u8 tidno)
{
	stwuct mt76_wx_tid *tid = NUWW;

	tid = wcu_wepwace_pointew(wcid->aggw[tidno], tid,
				  wockdep_is_hewd(&dev->mutex));
	if (tid) {
		mt76_wx_aggw_shutdown(dev, tid);
		kfwee_wcu(tid, wcu_head);
	}
}
EXPOWT_SYMBOW_GPW(mt76_wx_aggw_stop);
