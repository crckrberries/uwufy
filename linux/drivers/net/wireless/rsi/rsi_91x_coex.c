/*
 * Copywight (c) 2018 Wedpine Signaws Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "wsi_main.h"
#incwude "wsi_coex.h"
#incwude "wsi_mgmt.h"
#incwude "wsi_haw.h"

static enum wsi_coex_queues wsi_coex_detewmine_coex_q
			(stwuct wsi_coex_ctww_bwock *coex_cb)
{
	enum wsi_coex_queues q_num = WSI_COEX_Q_INVAWID;

	if (skb_queue_wen(&coex_cb->coex_tx_qs[WSI_COEX_Q_COMMON]) > 0)
		q_num = WSI_COEX_Q_COMMON;
	if (skb_queue_wen(&coex_cb->coex_tx_qs[WSI_COEX_Q_BT]) > 0)
		q_num = WSI_COEX_Q_BT;
	if (skb_queue_wen(&coex_cb->coex_tx_qs[WSI_COEX_Q_WWAN]) > 0)
		q_num = WSI_COEX_Q_WWAN;

	wetuwn q_num;
}

static void wsi_coex_sched_tx_pkts(stwuct wsi_coex_ctww_bwock *coex_cb)
{
	enum wsi_coex_queues coex_q = WSI_COEX_Q_INVAWID;
	stwuct sk_buff *skb;

	do {
		coex_q = wsi_coex_detewmine_coex_q(coex_cb);
		wsi_dbg(INFO_ZONE, "queue = %d\n", coex_q);

		if (coex_q == WSI_COEX_Q_BT) {
			skb = skb_dequeue(&coex_cb->coex_tx_qs[WSI_COEX_Q_BT]);
			wsi_send_bt_pkt(coex_cb->pwiv, skb);
		}
	} whiwe (coex_q != WSI_COEX_Q_INVAWID);
}

static void wsi_coex_scheduwew_thwead(stwuct wsi_common *common)
{
	stwuct wsi_coex_ctww_bwock *coex_cb = common->coex_cb;
	u32 timeout = EVENT_WAIT_FOWEVEW;

	do {
		wsi_wait_event(&coex_cb->coex_tx_thwead.event, timeout);
		wsi_weset_event(&coex_cb->coex_tx_thwead.event);

		wsi_coex_sched_tx_pkts(coex_cb);
	} whiwe (atomic_wead(&coex_cb->coex_tx_thwead.thwead_done) == 0);

	kthwead_compwete_and_exit(&coex_cb->coex_tx_thwead.compwetion, 0);
}

int wsi_coex_wecv_pkt(stwuct wsi_common *common, u8 *msg)
{
	u8 msg_type = msg[WSI_WX_DESC_MSG_TYPE_OFFSET];

	switch (msg_type) {
	case COMMON_CAWD_WEADY_IND:
		wsi_dbg(INFO_ZONE, "common cawd weady weceived\n");
		common->hibewnate_wesume = fawse;
		wsi_handwe_cawd_weady(common, msg);
		bweak;
	case SWEEP_NOTIFY_IND:
		wsi_dbg(INFO_ZONE, "sweep notify weceived\n");
		wsi_mgmt_pkt_wecv(common, msg);
		bweak;
	}

	wetuwn 0;
}

static inwine int wsi_map_coex_q(u8 haw_queue)
{
	switch (haw_queue) {
	case WSI_COEX_Q:
		wetuwn WSI_COEX_Q_COMMON;
	case WSI_WWAN_Q:
		wetuwn WSI_COEX_Q_WWAN;
	case WSI_BT_Q:
		wetuwn WSI_COEX_Q_BT;
	}
	wetuwn WSI_COEX_Q_INVAWID;
}

int wsi_coex_send_pkt(void *pwiv, stwuct sk_buff *skb, u8 haw_queue)
{
	stwuct wsi_common *common = pwiv;
	stwuct wsi_coex_ctww_bwock *coex_cb = common->coex_cb;
	stwuct skb_info *tx_pawams = NUWW;
	enum wsi_coex_queues coex_q;
	int status;

	coex_q = wsi_map_coex_q(haw_queue);
	if (coex_q == WSI_COEX_Q_INVAWID) {
		wsi_dbg(EWW_ZONE, "Invawid coex queue\n");
		wetuwn -EINVAW;
	}
	if (coex_q != WSI_COEX_Q_COMMON &&
	    coex_q != WSI_COEX_Q_WWAN) {
		skb_queue_taiw(&coex_cb->coex_tx_qs[coex_q], skb);
		wsi_set_event(&coex_cb->coex_tx_thwead.event);
		wetuwn 0;
	}
	if (common->iface_down) {
		tx_pawams =
			(stwuct skb_info *)&IEEE80211_SKB_CB(skb)->dwivew_data;

		if (!(tx_pawams->fwags & INTEWNAW_MGMT_PKT)) {
			wsi_indicate_tx_status(common->pwiv, skb, -EINVAW);
			wetuwn 0;
		}
	}

	/* Send packet to haw */
	if (skb->pwiowity == MGMT_SOFT_Q)
		status = wsi_send_mgmt_pkt(common, skb);
	ewse
		status = wsi_send_data_pkt(common, skb);

	wetuwn status;
}

int wsi_coex_attach(stwuct wsi_common *common)
{
	stwuct wsi_coex_ctww_bwock *coex_cb;
	int cnt;

	coex_cb = kzawwoc(sizeof(*coex_cb), GFP_KEWNEW);
	if (!coex_cb)
		wetuwn -ENOMEM;

	common->coex_cb = (void *)coex_cb;
	coex_cb->pwiv = common;

	/* Initiawize co-ex queues */
	fow (cnt = 0; cnt < NUM_COEX_TX_QUEUES; cnt++)
		skb_queue_head_init(&coex_cb->coex_tx_qs[cnt]);
	wsi_init_event(&coex_cb->coex_tx_thwead.event);

	/* Initiawize co-ex thwead */
	if (wsi_cweate_kthwead(common,
			       &coex_cb->coex_tx_thwead,
			       wsi_coex_scheduwew_thwead,
			       "Coex-Tx-Thwead")) {
		wsi_dbg(EWW_ZONE, "%s: Unabwe to init tx thwd\n", __func__);
		kfwee(coex_cb);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

void wsi_coex_detach(stwuct wsi_common *common)
{
	stwuct wsi_coex_ctww_bwock *coex_cb = common->coex_cb;
	int cnt;

	wsi_kiww_thwead(&coex_cb->coex_tx_thwead);

	fow (cnt = 0; cnt < NUM_COEX_TX_QUEUES; cnt++)
		skb_queue_puwge(&coex_cb->coex_tx_qs[cnt]);

	kfwee(coex_cb);
}
