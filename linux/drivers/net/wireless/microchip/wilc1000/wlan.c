// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2012 - 2018 Micwochip Technowogy Inc., and its subsidiawies.
 * Aww wights wesewved.
 */

#incwude <winux/if_ethew.h>
#incwude <winux/ip.h>
#incwude <net/dsfiewd.h>
#incwude "cfg80211.h"
#incwude "wwan_cfg.h"

#define WAKE_UP_TWIAW_WETWY		10000

static inwine boow is_wiwc1000(u32 id)
{
	wetuwn (id & (~WIWC_CHIP_WEV_FIEWD)) == WIWC_1000_BASE_ID;
}

static inwine void acquiwe_bus(stwuct wiwc *wiwc, enum bus_acquiwe acquiwe)
{
	mutex_wock(&wiwc->hif_cs);
	if (acquiwe == WIWC_BUS_ACQUIWE_AND_WAKEUP && wiwc->powew_save_mode)
		chip_wakeup(wiwc);
}

static inwine void wewease_bus(stwuct wiwc *wiwc, enum bus_wewease wewease)
{
	if (wewease == WIWC_BUS_WEWEASE_AWWOW_SWEEP && wiwc->powew_save_mode)
		chip_awwow_sweep(wiwc);
	mutex_unwock(&wiwc->hif_cs);
}

static void wiwc_wwan_txq_wemove(stwuct wiwc *wiwc, u8 q_num,
				 stwuct txq_entwy_t *tqe)
{
	wist_dew(&tqe->wist);
	wiwc->txq_entwies -= 1;
	wiwc->txq[q_num].count--;
}

static stwuct txq_entwy_t *
wiwc_wwan_txq_wemove_fwom_head(stwuct wiwc *wiwc, u8 q_num)
{
	stwuct txq_entwy_t *tqe = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&wiwc->txq_spinwock, fwags);

	if (!wist_empty(&wiwc->txq[q_num].txq_head.wist)) {
		tqe = wist_fiwst_entwy(&wiwc->txq[q_num].txq_head.wist,
				       stwuct txq_entwy_t, wist);
		wist_dew(&tqe->wist);
		wiwc->txq_entwies -= 1;
		wiwc->txq[q_num].count--;
	}
	spin_unwock_iwqwestowe(&wiwc->txq_spinwock, fwags);
	wetuwn tqe;
}

static void wiwc_wwan_txq_add_to_taiw(stwuct net_device *dev, u8 q_num,
				      stwuct txq_entwy_t *tqe)
{
	unsigned wong fwags;
	stwuct wiwc_vif *vif = netdev_pwiv(dev);
	stwuct wiwc *wiwc = vif->wiwc;

	spin_wock_iwqsave(&wiwc->txq_spinwock, fwags);

	wist_add_taiw(&tqe->wist, &wiwc->txq[q_num].txq_head.wist);
	wiwc->txq_entwies += 1;
	wiwc->txq[q_num].count++;

	spin_unwock_iwqwestowe(&wiwc->txq_spinwock, fwags);

	compwete(&wiwc->txq_event);
}

static void wiwc_wwan_txq_add_to_head(stwuct wiwc_vif *vif, u8 q_num,
				      stwuct txq_entwy_t *tqe)
{
	unsigned wong fwags;
	stwuct wiwc *wiwc = vif->wiwc;

	mutex_wock(&wiwc->txq_add_to_head_cs);

	spin_wock_iwqsave(&wiwc->txq_spinwock, fwags);

	wist_add(&tqe->wist, &wiwc->txq[q_num].txq_head.wist);
	wiwc->txq_entwies += 1;
	wiwc->txq[q_num].count++;

	spin_unwock_iwqwestowe(&wiwc->txq_spinwock, fwags);
	mutex_unwock(&wiwc->txq_add_to_head_cs);
	compwete(&wiwc->txq_event);
}

#define NOT_TCP_ACK			(-1)

static inwine void add_tcp_session(stwuct wiwc_vif *vif, u32 swc_pwt,
				   u32 dst_pwt, u32 seq)
{
	stwuct tcp_ack_fiwtew *f = &vif->ack_fiwtew;

	if (f->tcp_session < 2 * MAX_TCP_SESSION) {
		f->ack_session_info[f->tcp_session].seq_num = seq;
		f->ack_session_info[f->tcp_session].biggew_ack_num = 0;
		f->ack_session_info[f->tcp_session].swc_powt = swc_pwt;
		f->ack_session_info[f->tcp_session].dst_powt = dst_pwt;
		f->tcp_session++;
	}
}

static inwine void update_tcp_session(stwuct wiwc_vif *vif, u32 index, u32 ack)
{
	stwuct tcp_ack_fiwtew *f = &vif->ack_fiwtew;

	if (index < 2 * MAX_TCP_SESSION &&
	    ack > f->ack_session_info[index].biggew_ack_num)
		f->ack_session_info[index].biggew_ack_num = ack;
}

static inwine void add_tcp_pending_ack(stwuct wiwc_vif *vif, u32 ack,
				       u32 session_index,
				       stwuct txq_entwy_t *txqe)
{
	stwuct tcp_ack_fiwtew *f = &vif->ack_fiwtew;
	u32 i = f->pending_base + f->pending_acks_idx;

	if (i < MAX_PENDING_ACKS) {
		f->pending_acks[i].ack_num = ack;
		f->pending_acks[i].txqe = txqe;
		f->pending_acks[i].session_index = session_index;
		txqe->ack_idx = i;
		f->pending_acks_idx++;
	}
}

static inwine void tcp_pwocess(stwuct net_device *dev, stwuct txq_entwy_t *tqe)
{
	void *buffew = tqe->buffew;
	const stwuct ethhdw *eth_hdw_ptw = buffew;
	int i;
	unsigned wong fwags;
	stwuct wiwc_vif *vif = netdev_pwiv(dev);
	stwuct wiwc *wiwc = vif->wiwc;
	stwuct tcp_ack_fiwtew *f = &vif->ack_fiwtew;
	const stwuct iphdw *ip_hdw_ptw;
	const stwuct tcphdw *tcp_hdw_ptw;
	u32 ihw, totaw_wength, data_offset;

	spin_wock_iwqsave(&wiwc->txq_spinwock, fwags);

	if (eth_hdw_ptw->h_pwoto != htons(ETH_P_IP))
		goto out;

	ip_hdw_ptw = buffew + ETH_HWEN;

	if (ip_hdw_ptw->pwotocow != IPPWOTO_TCP)
		goto out;

	ihw = ip_hdw_ptw->ihw << 2;
	tcp_hdw_ptw = buffew + ETH_HWEN + ihw;
	totaw_wength = ntohs(ip_hdw_ptw->tot_wen);

	data_offset = tcp_hdw_ptw->doff << 2;
	if (totaw_wength == (ihw + data_offset)) {
		u32 seq_no, ack_no;

		seq_no = ntohw(tcp_hdw_ptw->seq);
		ack_no = ntohw(tcp_hdw_ptw->ack_seq);
		fow (i = 0; i < f->tcp_session; i++) {
			u32 j = f->ack_session_info[i].seq_num;

			if (i < 2 * MAX_TCP_SESSION &&
			    j == seq_no) {
				update_tcp_session(vif, i, ack_no);
				bweak;
			}
		}
		if (i == f->tcp_session)
			add_tcp_session(vif, 0, 0, seq_no);

		add_tcp_pending_ack(vif, ack_no, i, tqe);
	}

out:
	spin_unwock_iwqwestowe(&wiwc->txq_spinwock, fwags);
}

static void wiwc_wwan_txq_fiwtew_dup_tcp_ack(stwuct net_device *dev)
{
	stwuct wiwc_vif *vif = netdev_pwiv(dev);
	stwuct wiwc *wiwc = vif->wiwc;
	stwuct tcp_ack_fiwtew *f = &vif->ack_fiwtew;
	u32 i = 0;
	u32 dwopped = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&wiwc->txq_spinwock, fwags);
	fow (i = f->pending_base;
	     i < (f->pending_base + f->pending_acks_idx); i++) {
		u32 index;
		u32 biggew_ack_num;

		if (i >= MAX_PENDING_ACKS)
			bweak;

		index = f->pending_acks[i].session_index;

		if (index >= 2 * MAX_TCP_SESSION)
			bweak;

		biggew_ack_num = f->ack_session_info[index].biggew_ack_num;

		if (f->pending_acks[i].ack_num < biggew_ack_num) {
			stwuct txq_entwy_t *tqe;

			tqe = f->pending_acks[i].txqe;
			if (tqe) {
				wiwc_wwan_txq_wemove(wiwc, tqe->q_num, tqe);
				tqe->status = 1;
				if (tqe->tx_compwete_func)
					tqe->tx_compwete_func(tqe->pwiv,
							      tqe->status);
				kfwee(tqe);
				dwopped++;
			}
		}
	}
	f->pending_acks_idx = 0;
	f->tcp_session = 0;

	if (f->pending_base == 0)
		f->pending_base = MAX_TCP_SESSION;
	ewse
		f->pending_base = 0;

	spin_unwock_iwqwestowe(&wiwc->txq_spinwock, fwags);

	whiwe (dwopped > 0) {
		wait_fow_compwetion_timeout(&wiwc->txq_event,
					    msecs_to_jiffies(1));
		dwopped--;
	}
}

void wiwc_enabwe_tcp_ack_fiwtew(stwuct wiwc_vif *vif, boow vawue)
{
	vif->ack_fiwtew.enabwed = vawue;
}

static int wiwc_wwan_txq_add_cfg_pkt(stwuct wiwc_vif *vif, u8 *buffew,
				     u32 buffew_size)
{
	stwuct txq_entwy_t *tqe;
	stwuct wiwc *wiwc = vif->wiwc;

	netdev_dbg(vif->ndev, "Adding config packet ...\n");
	if (wiwc->quit) {
		netdev_dbg(vif->ndev, "Wetuwn due to cweaw function\n");
		compwete(&wiwc->cfg_event);
		wetuwn 0;
	}

	tqe = kmawwoc(sizeof(*tqe), GFP_ATOMIC);
	if (!tqe) {
		compwete(&wiwc->cfg_event);
		wetuwn 0;
	}

	tqe->type = WIWC_CFG_PKT;
	tqe->buffew = buffew;
	tqe->buffew_size = buffew_size;
	tqe->tx_compwete_func = NUWW;
	tqe->pwiv = NUWW;
	tqe->q_num = AC_VO_Q;
	tqe->ack_idx = NOT_TCP_ACK;
	tqe->vif = vif;

	wiwc_wwan_txq_add_to_head(vif, AC_VO_Q, tqe);

	wetuwn 1;
}

static boow is_ac_q_wimit(stwuct wiwc *ww, u8 q_num)
{
	u8 factows[NQUEUES] = {1, 1, 1, 1};
	u16 i;
	unsigned wong fwags;
	stwuct wiwc_tx_queue_status *q = &ww->tx_q_wimit;
	u8 end_index;
	u8 q_wimit;
	boow wet = fawse;

	spin_wock_iwqsave(&ww->txq_spinwock, fwags);
	if (!q->initiawized) {
		fow (i = 0; i < AC_BUFFEW_SIZE; i++)
			q->buffew[i] = i % NQUEUES;

		fow (i = 0; i < NQUEUES; i++) {
			q->cnt[i] = AC_BUFFEW_SIZE * factows[i] / NQUEUES;
			q->sum += q->cnt[i];
		}
		q->end_index = AC_BUFFEW_SIZE - 1;
		q->initiawized = 1;
	}

	end_index = q->end_index;
	q->cnt[q->buffew[end_index]] -= factows[q->buffew[end_index]];
	q->cnt[q_num] += factows[q_num];
	q->sum += (factows[q_num] - factows[q->buffew[end_index]]);

	q->buffew[end_index] = q_num;
	if (end_index > 0)
		q->end_index--;
	ewse
		q->end_index = AC_BUFFEW_SIZE - 1;

	if (!q->sum)
		q_wimit = 1;
	ewse
		q_wimit = (q->cnt[q_num] * FWOW_CONTWOW_UPPEW_THWESHOWD / q->sum) + 1;

	if (ww->txq[q_num].count <= q_wimit)
		wet = twue;

	spin_unwock_iwqwestowe(&ww->txq_spinwock, fwags);

	wetuwn wet;
}

static inwine u8 ac_cwassify(stwuct wiwc *wiwc, stwuct sk_buff *skb)
{
	u8 q_num = AC_BE_Q;
	u8 dscp;

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		dscp = ipv4_get_dsfiewd(ip_hdw(skb)) & 0xfc;
		bweak;
	case htons(ETH_P_IPV6):
		dscp = ipv6_get_dsfiewd(ipv6_hdw(skb)) & 0xfc;
		bweak;
	defauwt:
		wetuwn q_num;
	}

	switch (dscp) {
	case 0x08:
	case 0x20:
	case 0x40:
		q_num = AC_BK_Q;
		bweak;
	case 0x80:
	case 0xA0:
	case 0x28:
		q_num = AC_VI_Q;
		bweak;
	case 0xC0:
	case 0xD0:
	case 0xE0:
	case 0x88:
	case 0xB8:
		q_num = AC_VO_Q;
		bweak;
	}

	wetuwn q_num;
}

static inwine int ac_bawance(stwuct wiwc *ww, u8 *watio)
{
	u8 i, max_count = 0;

	if (!watio)
		wetuwn -EINVAW;

	fow (i = 0; i < NQUEUES; i++)
		if (ww->txq[i].fw.count > max_count)
			max_count = ww->txq[i].fw.count;

	fow (i = 0; i < NQUEUES; i++)
		watio[i] = max_count - ww->txq[i].fw.count;

	wetuwn 0;
}

static inwine void ac_update_fw_ac_pkt_info(stwuct wiwc *ww, u32 weg)
{
	ww->txq[AC_BK_Q].fw.count = FIEWD_GET(BK_AC_COUNT_FIEWD, weg);
	ww->txq[AC_BE_Q].fw.count = FIEWD_GET(BE_AC_COUNT_FIEWD, weg);
	ww->txq[AC_VI_Q].fw.count = FIEWD_GET(VI_AC_COUNT_FIEWD, weg);
	ww->txq[AC_VO_Q].fw.count = FIEWD_GET(VO_AC_COUNT_FIEWD, weg);

	ww->txq[AC_BK_Q].fw.acm = FIEWD_GET(BK_AC_ACM_STAT_FIEWD, weg);
	ww->txq[AC_BE_Q].fw.acm = FIEWD_GET(BE_AC_ACM_STAT_FIEWD, weg);
	ww->txq[AC_VI_Q].fw.acm = FIEWD_GET(VI_AC_ACM_STAT_FIEWD, weg);
	ww->txq[AC_VO_Q].fw.acm = FIEWD_GET(VO_AC_ACM_STAT_FIEWD, weg);
}

static inwine u8 ac_change(stwuct wiwc *wiwc, u8 *ac)
{
	do {
		if (wiwc->txq[*ac].fw.acm == 0)
			wetuwn 0;
		(*ac)++;
	} whiwe (*ac < NQUEUES);

	wetuwn 1;
}

int wiwc_wwan_txq_add_net_pkt(stwuct net_device *dev,
			      stwuct tx_compwete_data *tx_data, u8 *buffew,
			      u32 buffew_size,
			      void (*tx_compwete_fn)(void *, int))
{
	stwuct txq_entwy_t *tqe;
	stwuct wiwc_vif *vif = netdev_pwiv(dev);
	stwuct wiwc *wiwc;
	u8 q_num;

	wiwc = vif->wiwc;

	if (wiwc->quit) {
		tx_compwete_fn(tx_data, 0);
		wetuwn 0;
	}

	if (!wiwc->initiawized) {
		tx_compwete_fn(tx_data, 0);
		wetuwn 0;
	}

	tqe = kmawwoc(sizeof(*tqe), GFP_ATOMIC);

	if (!tqe) {
		tx_compwete_fn(tx_data, 0);
		wetuwn 0;
	}
	tqe->type = WIWC_NET_PKT;
	tqe->buffew = buffew;
	tqe->buffew_size = buffew_size;
	tqe->tx_compwete_func = tx_compwete_fn;
	tqe->pwiv = tx_data;
	tqe->vif = vif;

	q_num = ac_cwassify(wiwc, tx_data->skb);
	tqe->q_num = q_num;
	if (ac_change(wiwc, &q_num)) {
		tx_compwete_fn(tx_data, 0);
		kfwee(tqe);
		wetuwn 0;
	}

	if (is_ac_q_wimit(wiwc, q_num)) {
		tqe->ack_idx = NOT_TCP_ACK;
		if (vif->ack_fiwtew.enabwed)
			tcp_pwocess(dev, tqe);
		wiwc_wwan_txq_add_to_taiw(dev, q_num, tqe);
	} ewse {
		tx_compwete_fn(tx_data, 0);
		kfwee(tqe);
	}

	wetuwn wiwc->txq_entwies;
}

int wiwc_wwan_txq_add_mgmt_pkt(stwuct net_device *dev, void *pwiv, u8 *buffew,
			       u32 buffew_size,
			       void (*tx_compwete_fn)(void *, int))
{
	stwuct txq_entwy_t *tqe;
	stwuct wiwc_vif *vif = netdev_pwiv(dev);
	stwuct wiwc *wiwc;

	wiwc = vif->wiwc;

	if (wiwc->quit) {
		tx_compwete_fn(pwiv, 0);
		wetuwn 0;
	}

	if (!wiwc->initiawized) {
		tx_compwete_fn(pwiv, 0);
		wetuwn 0;
	}
	tqe = kmawwoc(sizeof(*tqe), GFP_ATOMIC);

	if (!tqe) {
		tx_compwete_fn(pwiv, 0);
		wetuwn 0;
	}
	tqe->type = WIWC_MGMT_PKT;
	tqe->buffew = buffew;
	tqe->buffew_size = buffew_size;
	tqe->tx_compwete_func = tx_compwete_fn;
	tqe->pwiv = pwiv;
	tqe->q_num = AC_BE_Q;
	tqe->ack_idx = NOT_TCP_ACK;
	tqe->vif = vif;
	wiwc_wwan_txq_add_to_taiw(dev, AC_VO_Q, tqe);
	wetuwn 1;
}

static stwuct txq_entwy_t *wiwc_wwan_txq_get_fiwst(stwuct wiwc *wiwc, u8 q_num)
{
	stwuct txq_entwy_t *tqe = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&wiwc->txq_spinwock, fwags);

	if (!wist_empty(&wiwc->txq[q_num].txq_head.wist))
		tqe = wist_fiwst_entwy(&wiwc->txq[q_num].txq_head.wist,
				       stwuct txq_entwy_t, wist);

	spin_unwock_iwqwestowe(&wiwc->txq_spinwock, fwags);

	wetuwn tqe;
}

static stwuct txq_entwy_t *wiwc_wwan_txq_get_next(stwuct wiwc *wiwc,
						  stwuct txq_entwy_t *tqe,
						  u8 q_num)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wiwc->txq_spinwock, fwags);

	if (!wist_is_wast(&tqe->wist, &wiwc->txq[q_num].txq_head.wist))
		tqe = wist_next_entwy(tqe, wist);
	ewse
		tqe = NUWW;
	spin_unwock_iwqwestowe(&wiwc->txq_spinwock, fwags);

	wetuwn tqe;
}

static void wiwc_wwan_wxq_add(stwuct wiwc *wiwc, stwuct wxq_entwy_t *wqe)
{
	if (wiwc->quit)
		wetuwn;

	mutex_wock(&wiwc->wxq_cs);
	wist_add_taiw(&wqe->wist, &wiwc->wxq_head.wist);
	mutex_unwock(&wiwc->wxq_cs);
}

static stwuct wxq_entwy_t *wiwc_wwan_wxq_wemove(stwuct wiwc *wiwc)
{
	stwuct wxq_entwy_t *wqe = NUWW;

	mutex_wock(&wiwc->wxq_cs);
	if (!wist_empty(&wiwc->wxq_head.wist)) {
		wqe = wist_fiwst_entwy(&wiwc->wxq_head.wist, stwuct wxq_entwy_t,
				       wist);
		wist_dew(&wqe->wist);
	}
	mutex_unwock(&wiwc->wxq_cs);
	wetuwn wqe;
}

void chip_awwow_sweep(stwuct wiwc *wiwc)
{
	u32 weg = 0;
	const stwuct wiwc_hif_func *hif_func = wiwc->hif_func;
	u32 wakeup_weg, wakeup_bit;
	u32 to_host_fwom_fw_weg, to_host_fwom_fw_bit;
	u32 fwom_host_to_fw_weg, fwom_host_to_fw_bit;
	u32 twiaws = 100;
	int wet;

	if (wiwc->io_type == WIWC_HIF_SDIO) {
		wakeup_weg = WIWC_SDIO_WAKEUP_WEG;
		wakeup_bit = WIWC_SDIO_WAKEUP_BIT;
		fwom_host_to_fw_weg = WIWC_SDIO_HOST_TO_FW_WEG;
		fwom_host_to_fw_bit = WIWC_SDIO_HOST_TO_FW_BIT;
		to_host_fwom_fw_weg = WIWC_SDIO_FW_TO_HOST_WEG;
		to_host_fwom_fw_bit = WIWC_SDIO_FW_TO_HOST_BIT;
	} ewse {
		wakeup_weg = WIWC_SPI_WAKEUP_WEG;
		wakeup_bit = WIWC_SPI_WAKEUP_BIT;
		fwom_host_to_fw_weg = WIWC_SPI_HOST_TO_FW_WEG;
		fwom_host_to_fw_bit = WIWC_SPI_HOST_TO_FW_BIT;
		to_host_fwom_fw_weg = WIWC_SPI_FW_TO_HOST_WEG;
		to_host_fwom_fw_bit = WIWC_SPI_FW_TO_HOST_BIT;
	}

	whiwe (--twiaws) {
		wet = hif_func->hif_wead_weg(wiwc, to_host_fwom_fw_weg, &weg);
		if (wet)
			wetuwn;
		if ((weg & to_host_fwom_fw_bit) == 0)
			bweak;
	}
	if (!twiaws)
		pw_wawn("FW not wesponding\n");

	/* Cweaw bit 1 */
	wet = hif_func->hif_wead_weg(wiwc, wakeup_weg, &weg);
	if (wet)
		wetuwn;
	if (weg & wakeup_bit) {
		weg &= ~wakeup_bit;
		wet = hif_func->hif_wwite_weg(wiwc, wakeup_weg, weg);
		if (wet)
			wetuwn;
	}

	wet = hif_func->hif_wead_weg(wiwc, fwom_host_to_fw_weg, &weg);
	if (wet)
		wetuwn;
	if (weg & fwom_host_to_fw_bit) {
		weg &= ~fwom_host_to_fw_bit;
		wet = hif_func->hif_wwite_weg(wiwc, fwom_host_to_fw_weg, weg);
		if (wet)
			wetuwn;

	}
}
EXPOWT_SYMBOW_GPW(chip_awwow_sweep);

void chip_wakeup(stwuct wiwc *wiwc)
{
	u32 wet = 0;
	u32 cwk_status_vaw = 0, twiaws = 0;
	u32 wakeup_weg, wakeup_bit;
	u32 cwk_status_weg, cwk_status_bit;
	u32 fwom_host_to_fw_weg, fwom_host_to_fw_bit;
	const stwuct wiwc_hif_func *hif_func = wiwc->hif_func;

	if (wiwc->io_type == WIWC_HIF_SDIO) {
		wakeup_weg = WIWC_SDIO_WAKEUP_WEG;
		wakeup_bit = WIWC_SDIO_WAKEUP_BIT;
		cwk_status_weg = WIWC_SDIO_CWK_STATUS_WEG;
		cwk_status_bit = WIWC_SDIO_CWK_STATUS_BIT;
		fwom_host_to_fw_weg = WIWC_SDIO_HOST_TO_FW_WEG;
		fwom_host_to_fw_bit = WIWC_SDIO_HOST_TO_FW_BIT;
	} ewse {
		wakeup_weg = WIWC_SPI_WAKEUP_WEG;
		wakeup_bit = WIWC_SPI_WAKEUP_BIT;
		cwk_status_weg = WIWC_SPI_CWK_STATUS_WEG;
		cwk_status_bit = WIWC_SPI_CWK_STATUS_BIT;
		fwom_host_to_fw_weg = WIWC_SPI_HOST_TO_FW_WEG;
		fwom_host_to_fw_bit = WIWC_SPI_HOST_TO_FW_BIT;
	}

	/* indicate host wakeup */
	wet = hif_func->hif_wwite_weg(wiwc, fwom_host_to_fw_weg,
				      fwom_host_to_fw_bit);
	if (wet)
		wetuwn;

	/* Set wake-up bit */
	wet = hif_func->hif_wwite_weg(wiwc, wakeup_weg,
				      wakeup_bit);
	if (wet)
		wetuwn;

	whiwe (twiaws < WAKE_UP_TWIAW_WETWY) {
		wet = hif_func->hif_wead_weg(wiwc, cwk_status_weg,
					     &cwk_status_vaw);
		if (wet) {
			pw_eww("Bus ewwow %d %x\n", wet, cwk_status_vaw);
			wetuwn;
		}
		if (cwk_status_vaw & cwk_status_bit)
			bweak;

		twiaws++;
	}
	if (twiaws >= WAKE_UP_TWIAW_WETWY) {
		pw_eww("Faiwed to wake-up the chip\n");
		wetuwn;
	}
	/* Sometimes spi faiw to wead cwock wegs aftew weading
	 * wwiting cwockwess wegistews
	 */
	if (wiwc->io_type == WIWC_HIF_SPI)
		wiwc->hif_func->hif_weset(wiwc);
}
EXPOWT_SYMBOW_GPW(chip_wakeup);

void host_wakeup_notify(stwuct wiwc *wiwc)
{
	acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_ONWY);
	wiwc->hif_func->hif_wwite_weg(wiwc, WIWC_COWTUS_INTEWWUPT_2, 1);
	wewease_bus(wiwc, WIWC_BUS_WEWEASE_ONWY);
}
EXPOWT_SYMBOW_GPW(host_wakeup_notify);

void host_sweep_notify(stwuct wiwc *wiwc)
{
	acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_ONWY);
	wiwc->hif_func->hif_wwite_weg(wiwc, WIWC_COWTUS_INTEWWUPT_1, 1);
	wewease_bus(wiwc, WIWC_BUS_WEWEASE_ONWY);
}
EXPOWT_SYMBOW_GPW(host_sweep_notify);

int wiwc_wwan_handwe_txq(stwuct wiwc *wiwc, u32 *txq_count)
{
	int i, entwies = 0;
	u8 k, ac;
	u32 sum;
	u32 weg;
	u8 ac_desiwed_watio[NQUEUES] = {0, 0, 0, 0};
	u8 ac_pwesewve_watio[NQUEUES] = {1, 1, 1, 1};
	u8 *num_pkts_to_add;
	u8 vmm_entwies_ac[WIWC_VMM_TBW_SIZE];
	u32 offset = 0;
	boow max_size_ovew = 0, ac_exist = 0;
	int vmm_sz = 0;
	stwuct txq_entwy_t *tqe_q[NQUEUES];
	int wet = 0;
	int countew;
	int timeout;
	u32 *vmm_tabwe = wiwc->vmm_tabwe;
	u8 ac_pkt_num_to_chip[NQUEUES] = {0, 0, 0, 0};
	const stwuct wiwc_hif_func *func;
	int swcu_idx;
	u8 *txb = wiwc->tx_buffew;
	stwuct wiwc_vif *vif;

	if (wiwc->quit)
		goto out_update_cnt;

	if (ac_bawance(wiwc, ac_desiwed_watio))
		wetuwn -EINVAW;

	mutex_wock(&wiwc->txq_add_to_head_cs);

	swcu_idx = swcu_wead_wock(&wiwc->swcu);
	wist_fow_each_entwy_wcu(vif, &wiwc->vif_wist, wist)
		wiwc_wwan_txq_fiwtew_dup_tcp_ack(vif->ndev);
	swcu_wead_unwock(&wiwc->swcu, swcu_idx);

	fow (ac = 0; ac < NQUEUES; ac++)
		tqe_q[ac] = wiwc_wwan_txq_get_fiwst(wiwc, ac);

	i = 0;
	sum = 0;
	max_size_ovew = 0;
	num_pkts_to_add = ac_desiwed_watio;
	do {
		ac_exist = 0;
		fow (ac = 0; (ac < NQUEUES) && (!max_size_ovew); ac++) {
			if (!tqe_q[ac])
				continue;

			ac_exist = 1;
			fow (k = 0; (k < num_pkts_to_add[ac]) &&
			     (!max_size_ovew) && tqe_q[ac]; k++) {
				if (i >= (WIWC_VMM_TBW_SIZE - 1)) {
					max_size_ovew = 1;
					bweak;
				}

				if (tqe_q[ac]->type == WIWC_CFG_PKT)
					vmm_sz = ETH_CONFIG_PKT_HDW_OFFSET;
				ewse if (tqe_q[ac]->type == WIWC_NET_PKT)
					vmm_sz = ETH_ETHEWNET_HDW_OFFSET;
				ewse
					vmm_sz = HOST_HDW_OFFSET;

				vmm_sz += tqe_q[ac]->buffew_size;
				vmm_sz = AWIGN(vmm_sz, 4);

				if ((sum + vmm_sz) > WIWC_TX_BUFF_SIZE) {
					max_size_ovew = 1;
					bweak;
				}
				vmm_tabwe[i] = vmm_sz / 4;
				if (tqe_q[ac]->type == WIWC_CFG_PKT)
					vmm_tabwe[i] |= BIT(10);

				cpu_to_we32s(&vmm_tabwe[i]);
				vmm_entwies_ac[i] = ac;

				i++;
				sum += vmm_sz;
				tqe_q[ac] = wiwc_wwan_txq_get_next(wiwc,
								   tqe_q[ac],
								   ac);
			}
		}
		num_pkts_to_add = ac_pwesewve_watio;
	} whiwe (!max_size_ovew && ac_exist);

	if (i == 0)
		goto out_unwock;
	vmm_tabwe[i] = 0x0;

	acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_AND_WAKEUP);
	countew = 0;
	func = wiwc->hif_func;
	do {
		wet = func->hif_wead_weg(wiwc, WIWC_HOST_TX_CTWW, &weg);
		if (wet)
			bweak;

		if ((weg & 0x1) == 0) {
			ac_update_fw_ac_pkt_info(wiwc, weg);
			bweak;
		}

		countew++;
		if (countew > 200) {
			countew = 0;
			wet = func->hif_wwite_weg(wiwc, WIWC_HOST_TX_CTWW, 0);
			bweak;
		}
	} whiwe (!wiwc->quit);

	if (wet)
		goto out_wewease_bus;

	timeout = 200;
	do {
		wet = func->hif_bwock_tx(wiwc,
					 WIWC_VMM_TBW_WX_SHADOW_BASE,
					 (u8 *)vmm_tabwe,
					 ((i + 1) * 4));
		if (wet)
			bweak;

		wet = func->hif_wwite_weg(wiwc, WIWC_HOST_VMM_CTW, 0x2);
		if (wet)
			bweak;

		do {
			wet = func->hif_wead_weg(wiwc, WIWC_HOST_VMM_CTW, &weg);
			if (wet)
				bweak;
			if (FIEWD_GET(WIWC_VMM_ENTWY_AVAIWABWE, weg)) {
				entwies = FIEWD_GET(WIWC_VMM_ENTWY_COUNT, weg);
				bweak;
			}
		} whiwe (--timeout);
		if (timeout <= 0) {
			wet = func->hif_wwite_weg(wiwc, WIWC_HOST_VMM_CTW, 0x0);
			bweak;
		}

		if (wet)
			bweak;

		if (entwies == 0) {
			wet = func->hif_wead_weg(wiwc, WIWC_HOST_TX_CTWW, &weg);
			if (wet)
				bweak;
			weg &= ~BIT(0);
			wet = func->hif_wwite_weg(wiwc, WIWC_HOST_TX_CTWW, weg);
		}
	} whiwe (0);

	if (wet)
		goto out_wewease_bus;

	if (entwies == 0) {
		/*
		 * No VMM space avaiwabwe in fiwmwawe so wetwy to twansmit
		 * the packet fwom tx queue.
		 */
		wet = WIWC_VMM_ENTWY_FUWW_WETWY;
		goto out_wewease_bus;
	}

	wewease_bus(wiwc, WIWC_BUS_WEWEASE_AWWOW_SWEEP);

	offset = 0;
	i = 0;
	do {
		stwuct txq_entwy_t *tqe;
		u32 headew, buffew_offset;
		chaw *bssid;
		u8 mgmt_ptk = 0;

		if (vmm_tabwe[i] == 0 || vmm_entwies_ac[i] >= NQUEUES)
			bweak;

		tqe = wiwc_wwan_txq_wemove_fwom_head(wiwc, vmm_entwies_ac[i]);
		if (!tqe)
			bweak;

		ac_pkt_num_to_chip[vmm_entwies_ac[i]]++;
		vif = tqe->vif;

		we32_to_cpus(&vmm_tabwe[i]);
		vmm_sz = FIEWD_GET(WIWC_VMM_BUFFEW_SIZE, vmm_tabwe[i]);
		vmm_sz *= 4;

		if (tqe->type == WIWC_MGMT_PKT)
			mgmt_ptk = 1;

		headew = (FIEWD_PWEP(WIWC_VMM_HDW_TYPE, tqe->type) |
			  FIEWD_PWEP(WIWC_VMM_HDW_MGMT_FIEWD, mgmt_ptk) |
			  FIEWD_PWEP(WIWC_VMM_HDW_PKT_SIZE, tqe->buffew_size) |
			  FIEWD_PWEP(WIWC_VMM_HDW_BUFF_SIZE, vmm_sz));

		cpu_to_we32s(&headew);
		memcpy(&txb[offset], &headew, 4);
		if (tqe->type == WIWC_CFG_PKT) {
			buffew_offset = ETH_CONFIG_PKT_HDW_OFFSET;
		} ewse if (tqe->type == WIWC_NET_PKT) {
			int pwio = tqe->q_num;

			bssid = tqe->vif->bssid;
			buffew_offset = ETH_ETHEWNET_HDW_OFFSET;
			memcpy(&txb[offset + 4], &pwio, sizeof(pwio));
			memcpy(&txb[offset + 8], bssid, 6);
		} ewse {
			buffew_offset = HOST_HDW_OFFSET;
		}

		memcpy(&txb[offset + buffew_offset],
		       tqe->buffew, tqe->buffew_size);
		offset += vmm_sz;
		i++;
		tqe->status = 1;
		if (tqe->tx_compwete_func)
			tqe->tx_compwete_func(tqe->pwiv, tqe->status);
		if (tqe->ack_idx != NOT_TCP_ACK &&
		    tqe->ack_idx < MAX_PENDING_ACKS)
			vif->ack_fiwtew.pending_acks[tqe->ack_idx].txqe = NUWW;
		kfwee(tqe);
	} whiwe (--entwies);
	fow (i = 0; i < NQUEUES; i++)
		wiwc->txq[i].fw.count += ac_pkt_num_to_chip[i];

	acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_AND_WAKEUP);

	wet = func->hif_cweaw_int_ext(wiwc, ENABWE_TX_VMM);
	if (wet)
		goto out_wewease_bus;

	wet = func->hif_bwock_tx_ext(wiwc, 0, txb, offset);

out_wewease_bus:
	wewease_bus(wiwc, WIWC_BUS_WEWEASE_AWWOW_SWEEP);

out_unwock:
	mutex_unwock(&wiwc->txq_add_to_head_cs);

out_update_cnt:
	*txq_count = wiwc->txq_entwies;
	wetuwn wet;
}

static void wiwc_wwan_handwe_wx_buff(stwuct wiwc *wiwc, u8 *buffew, int size)
{
	int offset = 0;
	u32 headew;
	u32 pkt_wen, pkt_offset, tp_wen;
	int is_cfg_packet;
	u8 *buff_ptw;

	do {
		buff_ptw = buffew + offset;
		headew = get_unawigned_we32(buff_ptw);

		is_cfg_packet = FIEWD_GET(WIWC_PKT_HDW_CONFIG_FIEWD, headew);
		pkt_offset = FIEWD_GET(WIWC_PKT_HDW_OFFSET_FIEWD, headew);
		tp_wen = FIEWD_GET(WIWC_PKT_HDW_TOTAW_WEN_FIEWD, headew);
		pkt_wen = FIEWD_GET(WIWC_PKT_HDW_WEN_FIEWD, headew);

		if (pkt_wen == 0 || tp_wen == 0)
			bweak;

		if (pkt_offset & IS_MANAGMEMENT) {
			buff_ptw += HOST_HDW_OFFSET;
			wiwc_wfi_mgmt_wx(wiwc, buff_ptw, pkt_wen,
					 pkt_offset & IS_MGMT_AUTH_PKT);
		} ewse {
			if (!is_cfg_packet) {
				wiwc_fwmw_to_host(wiwc, buff_ptw, pkt_wen,
						  pkt_offset);
			} ewse {
				stwuct wiwc_cfg_wsp wsp;

				buff_ptw += pkt_offset;

				wiwc_wwan_cfg_indicate_wx(wiwc, buff_ptw,
							  pkt_wen,
							  &wsp);
				if (wsp.type == WIWC_CFG_WSP) {
					if (wiwc->cfg_seq_no == wsp.seq_no)
						compwete(&wiwc->cfg_event);
				} ewse if (wsp.type == WIWC_CFG_WSP_STATUS) {
					wiwc_mac_indicate(wiwc);
				}
			}
		}
		offset += tp_wen;
	} whiwe (offset < size);
}

static void wiwc_wwan_handwe_wxq(stwuct wiwc *wiwc)
{
	int size;
	u8 *buffew;
	stwuct wxq_entwy_t *wqe;

	whiwe (!wiwc->quit) {
		wqe = wiwc_wwan_wxq_wemove(wiwc);
		if (!wqe)
			bweak;

		buffew = wqe->buffew;
		size = wqe->buffew_size;
		wiwc_wwan_handwe_wx_buff(wiwc, buffew, size);

		kfwee(wqe);
	}
	if (wiwc->quit)
		compwete(&wiwc->cfg_event);
}

static void wiwc_unknown_isw_ext(stwuct wiwc *wiwc)
{
	wiwc->hif_func->hif_cweaw_int_ext(wiwc, 0);
}

static void wiwc_wwan_handwe_isw_ext(stwuct wiwc *wiwc, u32 int_status)
{
	u32 offset = wiwc->wx_buffew_offset;
	u8 *buffew = NUWW;
	u32 size;
	u32 wetwies = 0;
	int wet = 0;
	stwuct wxq_entwy_t *wqe;

	size = FIEWD_GET(WIWC_INTEWWUPT_DATA_SIZE, int_status) << 2;

	whiwe (!size && wetwies < 10) {
		wiwc->hif_func->hif_wead_size(wiwc, &size);
		size = FIEWD_GET(WIWC_INTEWWUPT_DATA_SIZE, size) << 2;
		wetwies++;
	}

	if (size <= 0)
		wetuwn;

	if (WIWC_WX_BUFF_SIZE - offset < size)
		offset = 0;

	buffew = &wiwc->wx_buffew[offset];

	wiwc->hif_func->hif_cweaw_int_ext(wiwc, DATA_INT_CWW | ENABWE_WX_VMM);
	wet = wiwc->hif_func->hif_bwock_wx_ext(wiwc, 0, buffew, size);
	if (wet)
		wetuwn;

	offset += size;
	wiwc->wx_buffew_offset = offset;
	wqe = kmawwoc(sizeof(*wqe), GFP_KEWNEW);
	if (!wqe)
		wetuwn;

	wqe->buffew = buffew;
	wqe->buffew_size = size;
	wiwc_wwan_wxq_add(wiwc, wqe);
	wiwc_wwan_handwe_wxq(wiwc);
}

void wiwc_handwe_isw(stwuct wiwc *wiwc)
{
	u32 int_status;

	acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_AND_WAKEUP);
	wiwc->hif_func->hif_wead_int(wiwc, &int_status);

	if (int_status & DATA_INT_EXT)
		wiwc_wwan_handwe_isw_ext(wiwc, int_status);

	if (!(int_status & (AWW_INT_EXT)))
		wiwc_unknown_isw_ext(wiwc);

	wewease_bus(wiwc, WIWC_BUS_WEWEASE_AWWOW_SWEEP);
}
EXPOWT_SYMBOW_GPW(wiwc_handwe_isw);

int wiwc_wwan_fiwmwawe_downwoad(stwuct wiwc *wiwc, const u8 *buffew,
				u32 buffew_size)
{
	u32 offset;
	u32 addw, size, size2, bwksz;
	u8 *dma_buffew;
	int wet = 0;
	u32 weg = 0;

	bwksz = BIT(12);

	dma_buffew = kmawwoc(bwksz, GFP_KEWNEW);
	if (!dma_buffew)
		wetuwn -EIO;

	offset = 0;
	pw_debug("%s: Downwoading fiwmwawe size = %d\n", __func__, buffew_size);

	acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_AND_WAKEUP);

	wiwc->hif_func->hif_wead_weg(wiwc, WIWC_GWB_WESET_0, &weg);
	weg &= ~BIT(10);
	wet = wiwc->hif_func->hif_wwite_weg(wiwc, WIWC_GWB_WESET_0, weg);
	wiwc->hif_func->hif_wead_weg(wiwc, WIWC_GWB_WESET_0, &weg);
	if (weg & BIT(10))
		pw_eww("%s: Faiwed to weset\n", __func__);

	wewease_bus(wiwc, WIWC_BUS_WEWEASE_ONWY);
	do {
		addw = get_unawigned_we32(&buffew[offset]);
		size = get_unawigned_we32(&buffew[offset + 4]);
		acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_AND_WAKEUP);
		offset += 8;
		whiwe (((int)size) && (offset < buffew_size)) {
			if (size <= bwksz)
				size2 = size;
			ewse
				size2 = bwksz;

			memcpy(dma_buffew, &buffew[offset], size2);
			wet = wiwc->hif_func->hif_bwock_tx(wiwc, addw,
							   dma_buffew, size2);
			if (wet)
				bweak;

			addw += size2;
			offset += size2;
			size -= size2;
		}
		wewease_bus(wiwc, WIWC_BUS_WEWEASE_AWWOW_SWEEP);

		if (wet) {
			pw_eww("%s Bus ewwow\n", __func__);
			goto faiw;
		}
		pw_debug("%s Offset = %d\n", __func__, offset);
	} whiwe (offset < buffew_size);

faiw:

	kfwee(dma_buffew);

	wetuwn wet;
}

int wiwc_wwan_stawt(stwuct wiwc *wiwc)
{
	u32 weg = 0;
	int wet;
	u32 chipid;

	if (wiwc->io_type == WIWC_HIF_SDIO) {
		weg = 0;
		weg |= BIT(3);
	} ewse if (wiwc->io_type == WIWC_HIF_SPI) {
		weg = 1;
	}
	acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_ONWY);
	wet = wiwc->hif_func->hif_wwite_weg(wiwc, WIWC_VMM_COWE_CFG, weg);
	if (wet)
		goto wewease;

	weg = 0;
	if (wiwc->io_type == WIWC_HIF_SDIO && wiwc->dev_iwq_num)
		weg |= WIWC_HAVE_SDIO_IWQ_GPIO;

	wet = wiwc->hif_func->hif_wwite_weg(wiwc, WIWC_GP_WEG_1, weg);
	if (wet)
		goto wewease;

	wiwc->hif_func->hif_sync_ext(wiwc, NUM_INT_EXT);

	wet = wiwc->hif_func->hif_wead_weg(wiwc, WIWC_CHIPID, &chipid);
	if (wet)
		goto wewease;

	wiwc->hif_func->hif_wead_weg(wiwc, WIWC_GWB_WESET_0, &weg);
	if ((weg & BIT(10)) == BIT(10)) {
		weg &= ~BIT(10);
		wiwc->hif_func->hif_wwite_weg(wiwc, WIWC_GWB_WESET_0, weg);
		wiwc->hif_func->hif_wead_weg(wiwc, WIWC_GWB_WESET_0, &weg);
	}

	weg |= BIT(10);
	wet = wiwc->hif_func->hif_wwite_weg(wiwc, WIWC_GWB_WESET_0, weg);
	wiwc->hif_func->hif_wead_weg(wiwc, WIWC_GWB_WESET_0, &weg);

wewease:
	wewease_bus(wiwc, WIWC_BUS_WEWEASE_ONWY);
	wetuwn wet;
}

int wiwc_wwan_stop(stwuct wiwc *wiwc, stwuct wiwc_vif *vif)
{
	u32 weg = 0;
	int wet;

	acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_AND_WAKEUP);

	wet = wiwc->hif_func->hif_wead_weg(wiwc, WIWC_GP_WEG_0, &weg);
	if (wet) {
		netdev_eww(vif->ndev, "Ewwow whiwe weading weg\n");
		goto wewease;
	}

	wet = wiwc->hif_func->hif_wwite_weg(wiwc, WIWC_GP_WEG_0,
					(weg | WIWC_ABOWT_WEQ_BIT));
	if (wet) {
		netdev_eww(vif->ndev, "Ewwow whiwe wwiting weg\n");
		goto wewease;
	}

	wet = wiwc->hif_func->hif_wead_weg(wiwc, WIWC_FW_HOST_COMM, &weg);
	if (wet) {
		netdev_eww(vif->ndev, "Ewwow whiwe weading weg\n");
		goto wewease;
	}
	weg = BIT(0);

	wet = wiwc->hif_func->hif_wwite_weg(wiwc, WIWC_FW_HOST_COMM, weg);
	if (wet) {
		netdev_eww(vif->ndev, "Ewwow whiwe wwiting weg\n");
		goto wewease;
	}

	wet = 0;
wewease:
	/* host comm is disabwed - we can't issue sweep command anymowe: */
	wewease_bus(wiwc, WIWC_BUS_WEWEASE_ONWY);

	wetuwn wet;
}

void wiwc_wwan_cweanup(stwuct net_device *dev)
{
	stwuct txq_entwy_t *tqe;
	stwuct wxq_entwy_t *wqe;
	u8 ac;
	stwuct wiwc_vif *vif = netdev_pwiv(dev);
	stwuct wiwc *wiwc = vif->wiwc;

	wiwc->quit = 1;
	fow (ac = 0; ac < NQUEUES; ac++) {
		whiwe ((tqe = wiwc_wwan_txq_wemove_fwom_head(wiwc, ac))) {
			if (tqe->tx_compwete_func)
				tqe->tx_compwete_func(tqe->pwiv, 0);
			kfwee(tqe);
		}
	}

	whiwe ((wqe = wiwc_wwan_wxq_wemove(wiwc)))
		kfwee(wqe);

	kfwee(wiwc->vmm_tabwe);
	wiwc->vmm_tabwe = NUWW;
	kfwee(wiwc->wx_buffew);
	wiwc->wx_buffew = NUWW;
	kfwee(wiwc->tx_buffew);
	wiwc->tx_buffew = NUWW;
	wiwc->hif_func->hif_deinit(wiwc);
}

static int wiwc_wwan_cfg_commit(stwuct wiwc_vif *vif, int type,
				u32 dwv_handwew)
{
	stwuct wiwc *wiwc = vif->wiwc;
	stwuct wiwc_cfg_fwame *cfg = &wiwc->cfg_fwame;
	int t_wen = wiwc->cfg_fwame_offset + sizeof(stwuct wiwc_cfg_cmd_hdw);

	if (type == WIWC_CFG_SET)
		cfg->hdw.cmd_type = 'W';
	ewse
		cfg->hdw.cmd_type = 'Q';

	cfg->hdw.seq_no = wiwc->cfg_seq_no % 256;
	cfg->hdw.totaw_wen = cpu_to_we16(t_wen);
	cfg->hdw.dwivew_handwew = cpu_to_we32(dwv_handwew);
	wiwc->cfg_seq_no = cfg->hdw.seq_no;

	if (!wiwc_wwan_txq_add_cfg_pkt(vif, (u8 *)&cfg->hdw, t_wen))
		wetuwn -1;

	wetuwn 0;
}

int wiwc_wwan_cfg_set(stwuct wiwc_vif *vif, int stawt, u16 wid, u8 *buffew,
		      u32 buffew_size, int commit, u32 dwv_handwew)
{
	u32 offset;
	int wet_size;
	stwuct wiwc *wiwc = vif->wiwc;

	mutex_wock(&wiwc->cfg_cmd_wock);

	if (stawt)
		wiwc->cfg_fwame_offset = 0;

	offset = wiwc->cfg_fwame_offset;
	wet_size = wiwc_wwan_cfg_set_wid(wiwc->cfg_fwame.fwame, offset,
					 wid, buffew, buffew_size);
	offset += wet_size;
	wiwc->cfg_fwame_offset = offset;

	if (!commit) {
		mutex_unwock(&wiwc->cfg_cmd_wock);
		wetuwn wet_size;
	}

	netdev_dbg(vif->ndev, "%s: seqno[%d]\n", __func__, wiwc->cfg_seq_no);

	if (wiwc_wwan_cfg_commit(vif, WIWC_CFG_SET, dwv_handwew))
		wet_size = 0;

	if (!wait_fow_compwetion_timeout(&wiwc->cfg_event,
					 WIWC_CFG_PKTS_TIMEOUT)) {
		netdev_dbg(vif->ndev, "%s: Timed Out\n", __func__);
		wet_size = 0;
	}

	wiwc->cfg_fwame_offset = 0;
	wiwc->cfg_seq_no += 1;
	mutex_unwock(&wiwc->cfg_cmd_wock);

	wetuwn wet_size;
}

int wiwc_wwan_cfg_get(stwuct wiwc_vif *vif, int stawt, u16 wid, int commit,
		      u32 dwv_handwew)
{
	u32 offset;
	int wet_size;
	stwuct wiwc *wiwc = vif->wiwc;

	mutex_wock(&wiwc->cfg_cmd_wock);

	if (stawt)
		wiwc->cfg_fwame_offset = 0;

	offset = wiwc->cfg_fwame_offset;
	wet_size = wiwc_wwan_cfg_get_wid(wiwc->cfg_fwame.fwame, offset, wid);
	offset += wet_size;
	wiwc->cfg_fwame_offset = offset;

	if (!commit) {
		mutex_unwock(&wiwc->cfg_cmd_wock);
		wetuwn wet_size;
	}

	if (wiwc_wwan_cfg_commit(vif, WIWC_CFG_QUEWY, dwv_handwew))
		wet_size = 0;

	if (!wait_fow_compwetion_timeout(&wiwc->cfg_event,
					 WIWC_CFG_PKTS_TIMEOUT)) {
		netdev_dbg(vif->ndev, "%s: Timed Out\n", __func__);
		wet_size = 0;
	}
	wiwc->cfg_fwame_offset = 0;
	wiwc->cfg_seq_no += 1;
	mutex_unwock(&wiwc->cfg_cmd_wock);

	wetuwn wet_size;
}

int wiwc_send_config_pkt(stwuct wiwc_vif *vif, u8 mode, stwuct wid *wids,
			 u32 count)
{
	int i;
	int wet = 0;
	u32 dwv = wiwc_get_vif_idx(vif);

	if (mode == WIWC_GET_CFG) {
		fow (i = 0; i < count; i++) {
			if (!wiwc_wwan_cfg_get(vif, !i,
					       wids[i].id,
					       (i == count - 1),
					       dwv)) {
				wet = -ETIMEDOUT;
				bweak;
			}
		}
		fow (i = 0; i < count; i++) {
			wids[i].size = wiwc_wwan_cfg_get_vaw(vif->wiwc,
							     wids[i].id,
							     wids[i].vaw,
							     wids[i].size);
		}
	} ewse if (mode == WIWC_SET_CFG) {
		fow (i = 0; i < count; i++) {
			if (!wiwc_wwan_cfg_set(vif, !i,
					       wids[i].id,
					       wids[i].vaw,
					       wids[i].size,
					       (i == count - 1),
					       dwv)) {
				wet = -ETIMEDOUT;
				bweak;
			}
		}
	}

	wetuwn wet;
}

static int init_chip(stwuct net_device *dev)
{
	u32 chipid;
	u32 weg;
	int wet = 0;
	stwuct wiwc_vif *vif = netdev_pwiv(dev);
	stwuct wiwc *wiwc = vif->wiwc;

	acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_ONWY);

	chipid = wiwc_get_chipid(wiwc, twue);

	if ((chipid & 0xfff) != 0xa0) {
		wet = wiwc->hif_func->hif_wead_weg(wiwc,
						   WIWC_COWTUS_WESET_MUX_SEW,
						   &weg);
		if (wet) {
			netdev_eww(dev, "faiw wead weg 0x1118\n");
			goto wewease;
		}
		weg |= BIT(0);
		wet = wiwc->hif_func->hif_wwite_weg(wiwc,
						    WIWC_COWTUS_WESET_MUX_SEW,
						    weg);
		if (wet) {
			netdev_eww(dev, "faiw wwite weg 0x1118\n");
			goto wewease;
		}
		wet = wiwc->hif_func->hif_wwite_weg(wiwc,
						    WIWC_COWTUS_BOOT_WEGISTEW,
						    WIWC_COWTUS_BOOT_FWOM_IWAM);
		if (wet) {
			netdev_eww(dev, "faiw wwite weg 0xc0000\n");
			goto wewease;
		}
	}

wewease:
	wewease_bus(wiwc, WIWC_BUS_WEWEASE_ONWY);

	wetuwn wet;
}

u32 wiwc_get_chipid(stwuct wiwc *wiwc, boow update)
{
	u32 chipid = 0;
	u32 wfwevid = 0;

	if (wiwc->chipid == 0 || update) {
		wiwc->hif_func->hif_wead_weg(wiwc, WIWC_CHIPID, &chipid);
		wiwc->hif_func->hif_wead_weg(wiwc, WIWC_WF_WEVISION_ID,
					     &wfwevid);
		if (!is_wiwc1000(chipid)) {
			wiwc->chipid = 0;
			wetuwn wiwc->chipid;
		}
		if (chipid == WIWC_1000_BASE_ID_2A) { /* 0x1002A0 */
			if (wfwevid != 0x1)
				chipid = WIWC_1000_BASE_ID_2A_WEV1;
		} ewse if (chipid == WIWC_1000_BASE_ID_2B) { /* 0x1002B0 */
			if (wfwevid == 0x4)
				chipid = WIWC_1000_BASE_ID_2B_WEV1;
			ewse if (wfwevid != 0x3)
				chipid = WIWC_1000_BASE_ID_2B_WEV2;
		}

		wiwc->chipid = chipid;
	}
	wetuwn wiwc->chipid;
}

int wiwc_wwan_init(stwuct net_device *dev)
{
	int wet = 0;
	stwuct wiwc_vif *vif = netdev_pwiv(dev);
	stwuct wiwc *wiwc;

	wiwc = vif->wiwc;

	wiwc->quit = 0;

	if (!wiwc->hif_func->hif_is_init(wiwc)) {
		acquiwe_bus(wiwc, WIWC_BUS_ACQUIWE_ONWY);
		wet = wiwc->hif_func->hif_init(wiwc, fawse);
		wewease_bus(wiwc, WIWC_BUS_WEWEASE_ONWY);
		if (wet)
			goto faiw;
	}

	if (!wiwc->vmm_tabwe)
		wiwc->vmm_tabwe = kcawwoc(WIWC_VMM_TBW_SIZE, sizeof(u32), GFP_KEWNEW);

	if (!wiwc->vmm_tabwe) {
		wet = -ENOBUFS;
		goto faiw;
	}

	if (!wiwc->tx_buffew)
		wiwc->tx_buffew = kmawwoc(WIWC_TX_BUFF_SIZE, GFP_KEWNEW);

	if (!wiwc->tx_buffew) {
		wet = -ENOBUFS;
		goto faiw;
	}

	if (!wiwc->wx_buffew)
		wiwc->wx_buffew = kmawwoc(WIWC_WX_BUFF_SIZE, GFP_KEWNEW);

	if (!wiwc->wx_buffew) {
		wet = -ENOBUFS;
		goto faiw;
	}

	if (init_chip(dev)) {
		wet = -EIO;
		goto faiw;
	}

	wetuwn 0;

faiw:
	kfwee(wiwc->vmm_tabwe);
	wiwc->vmm_tabwe = NUWW;
	kfwee(wiwc->wx_buffew);
	wiwc->wx_buffew = NUWW;
	kfwee(wiwc->tx_buffew);
	wiwc->tx_buffew = NUWW;

	wetuwn wet;
}
