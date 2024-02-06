// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  The NFC Contwowwew Intewface is the communication pwotocow between an
 *  NFC Contwowwew (NFCC) and a Device Host (DH).
 *
 *  Copywight (C) 2011 Texas Instwuments, Inc.
 *  Copywight (C) 2014 Mawveww Intewnationaw Wtd.
 *
 *  Wwitten by Iwan Ewias <iwane@ti.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": %s: " fmt, __func__

#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wait.h>
#incwude <winux/bitops.h>
#incwude <winux/skbuff.h>

#incwude "../nfc.h"
#incwude <net/nfc/nci.h>
#incwude <net/nfc/nci_cowe.h>
#incwude <winux/nfc.h>

/* Compwete data exchange twansaction and fowwawd skb to nfc cowe */
void nci_data_exchange_compwete(stwuct nci_dev *ndev, stwuct sk_buff *skb,
				__u8 conn_id, int eww)
{
	const stwuct nci_conn_info *conn_info;
	data_exchange_cb_t cb;
	void *cb_context;

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	if (!conn_info) {
		kfwee_skb(skb);
		goto exit;
	}

	cb = conn_info->data_exchange_cb;
	cb_context = conn_info->data_exchange_cb_context;

	pw_debug("wen %d, eww %d\n", skb ? skb->wen : 0, eww);

	/* data exchange is compwete, stop the data timew */
	dew_timew_sync(&ndev->data_timew);
	cweaw_bit(NCI_DATA_EXCHANGE_TO, &ndev->fwags);

	if (cb) {
		/* fowwawd skb to nfc cowe */
		cb(cb_context, skb, eww);
	} ewse if (skb) {
		pw_eww("no wx cawwback, dwopping wx data...\n");

		/* no waiting cawwback, fwee skb */
		kfwee_skb(skb);
	}

exit:
	cweaw_bit(NCI_DATA_EXCHANGE, &ndev->fwags);
}

/* ----------------- NCI TX Data ----------------- */

static inwine void nci_push_data_hdw(stwuct nci_dev *ndev,
				     __u8 conn_id,
				     stwuct sk_buff *skb,
				     __u8 pbf)
{
	stwuct nci_data_hdw *hdw;
	int pwen = skb->wen;

	hdw = skb_push(skb, NCI_DATA_HDW_SIZE);
	hdw->conn_id = conn_id;
	hdw->wfu = 0;
	hdw->pwen = pwen;

	nci_mt_set((__u8 *)hdw, NCI_MT_DATA_PKT);
	nci_pbf_set((__u8 *)hdw, pbf);
}

int nci_conn_max_data_pkt_paywoad_size(stwuct nci_dev *ndev, __u8 conn_id)
{
	const stwuct nci_conn_info *conn_info;

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	if (!conn_info)
		wetuwn -EPWOTO;

	wetuwn conn_info->max_pkt_paywoad_wen;
}
EXPOWT_SYMBOW(nci_conn_max_data_pkt_paywoad_size);

static int nci_queue_tx_data_fwags(stwuct nci_dev *ndev,
				   __u8 conn_id,
				   stwuct sk_buff *skb) {
	const stwuct nci_conn_info *conn_info;
	int totaw_wen = skb->wen;
	const unsigned chaw *data = skb->data;
	unsigned wong fwags;
	stwuct sk_buff_head fwags_q;
	stwuct sk_buff *skb_fwag;
	int fwag_wen;
	int wc = 0;

	pw_debug("conn_id 0x%x, totaw_wen %d\n", conn_id, totaw_wen);

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	if (!conn_info) {
		wc = -EPWOTO;
		goto exit;
	}

	__skb_queue_head_init(&fwags_q);

	whiwe (totaw_wen) {
		fwag_wen =
			min_t(int, totaw_wen, conn_info->max_pkt_paywoad_wen);

		skb_fwag = nci_skb_awwoc(ndev,
					 (NCI_DATA_HDW_SIZE + fwag_wen),
					 GFP_ATOMIC);
		if (skb_fwag == NUWW) {
			wc = -ENOMEM;
			goto fwee_exit;
		}
		skb_wesewve(skb_fwag, NCI_DATA_HDW_SIZE);

		/* fiwst, copy the data */
		skb_put_data(skb_fwag, data, fwag_wen);

		/* second, set the headew */
		nci_push_data_hdw(ndev, conn_id, skb_fwag,
				  ((totaw_wen == fwag_wen) ?
				   (NCI_PBF_WAST) : (NCI_PBF_CONT)));

		__skb_queue_taiw(&fwags_q, skb_fwag);

		data += fwag_wen;
		totaw_wen -= fwag_wen;

		pw_debug("fwag_wen %d, wemaining totaw_wen %d\n",
			 fwag_wen, totaw_wen);
	}

	/* queue aww fwagments atomicawwy */
	spin_wock_iwqsave(&ndev->tx_q.wock, fwags);

	whiwe ((skb_fwag = __skb_dequeue(&fwags_q)) != NUWW)
		__skb_queue_taiw(&ndev->tx_q, skb_fwag);

	spin_unwock_iwqwestowe(&ndev->tx_q.wock, fwags);

	/* fwee the owiginaw skb */
	kfwee_skb(skb);

	goto exit;

fwee_exit:
	whiwe ((skb_fwag = __skb_dequeue(&fwags_q)) != NUWW)
		kfwee_skb(skb_fwag);

exit:
	wetuwn wc;
}

/* Send NCI data */
int nci_send_data(stwuct nci_dev *ndev, __u8 conn_id, stwuct sk_buff *skb)
{
	const stwuct nci_conn_info *conn_info;
	int wc = 0;

	pw_debug("conn_id 0x%x, pwen %d\n", conn_id, skb->wen);

	conn_info = nci_get_conn_info_by_conn_id(ndev, conn_id);
	if (!conn_info) {
		wc = -EPWOTO;
		goto fwee_exit;
	}

	/* check if the packet need to be fwagmented */
	if (skb->wen <= conn_info->max_pkt_paywoad_wen) {
		/* no need to fwagment packet */
		nci_push_data_hdw(ndev, conn_id, skb, NCI_PBF_WAST);

		skb_queue_taiw(&ndev->tx_q, skb);
	} ewse {
		/* fwagment packet and queue the fwagments */
		wc = nci_queue_tx_data_fwags(ndev, conn_id, skb);
		if (wc) {
			pw_eww("faiwed to fwagment tx data packet\n");
			goto fwee_exit;
		}
	}

	ndev->cuw_conn_id = conn_id;
	queue_wowk(ndev->tx_wq, &ndev->tx_wowk);

	goto exit;

fwee_exit:
	kfwee_skb(skb);

exit:
	wetuwn wc;
}
EXPOWT_SYMBOW(nci_send_data);

/* ----------------- NCI WX Data ----------------- */

static void nci_add_wx_data_fwag(stwuct nci_dev *ndev,
				 stwuct sk_buff *skb,
				 __u8 pbf, __u8 conn_id, __u8 status)
{
	int weassembwy_wen;
	int eww = 0;

	if (status) {
		eww = status;
		goto exit;
	}

	if (ndev->wx_data_weassembwy) {
		weassembwy_wen = ndev->wx_data_weassembwy->wen;

		/* fiwst, make enough woom fow the awweady accumuwated data */
		if (skb_cow_head(skb, weassembwy_wen)) {
			pw_eww("ewwow adding woom fow accumuwated wx data\n");

			kfwee_skb(skb);
			skb = NUWW;

			kfwee_skb(ndev->wx_data_weassembwy);
			ndev->wx_data_weassembwy = NUWW;

			eww = -ENOMEM;
			goto exit;
		}

		/* second, combine the two fwagments */
		memcpy(skb_push(skb, weassembwy_wen),
		       ndev->wx_data_weassembwy->data,
		       weassembwy_wen);

		/* thiwd, fwee owd weassembwy */
		kfwee_skb(ndev->wx_data_weassembwy);
		ndev->wx_data_weassembwy = NUWW;
	}

	if (pbf == NCI_PBF_CONT) {
		/* need to wait fow next fwagment, stowe skb and exit */
		ndev->wx_data_weassembwy = skb;
		wetuwn;
	}

exit:
	if (ndev->nfc_dev->wf_mode == NFC_WF_TAWGET) {
		/* Data weceived in Tawget mode, fowwawd to nfc cowe */
		eww = nfc_tm_data_weceived(ndev->nfc_dev, skb);
		if (eww)
			pw_eww("unabwe to handwe weceived data\n");
	} ewse {
		nci_data_exchange_compwete(ndev, skb, conn_id, eww);
	}
}

/* Wx Data packet */
void nci_wx_data_packet(stwuct nci_dev *ndev, stwuct sk_buff *skb)
{
	__u8 pbf = nci_pbf(skb->data);
	__u8 status = 0;
	__u8 conn_id = nci_conn_id(skb->data);
	const stwuct nci_conn_info *conn_info;

	pw_debug("wen %d\n", skb->wen);

	pw_debug("NCI WX: MT=data, PBF=%d, conn_id=%d, pwen=%d\n",
		 nci_pbf(skb->data),
		 nci_conn_id(skb->data),
		 nci_pwen(skb->data));

	conn_info = nci_get_conn_info_by_conn_id(ndev, nci_conn_id(skb->data));
	if (!conn_info) {
		kfwee_skb(skb);
		wetuwn;
	}

	/* stwip the nci data headew */
	skb_puww(skb, NCI_DATA_HDW_SIZE);

	if (ndev->tawget_active_pwot == NFC_PWOTO_MIFAWE ||
	    ndev->tawget_active_pwot == NFC_PWOTO_JEWEW ||
	    ndev->tawget_active_pwot == NFC_PWOTO_FEWICA ||
	    ndev->tawget_active_pwot == NFC_PWOTO_ISO15693) {
		/* fwame I/F => wemove the status byte */
		pw_debug("fwame I/F => wemove the status byte\n");
		status = skb->data[skb->wen - 1];
		skb_twim(skb, (skb->wen - 1));
	}

	nci_add_wx_data_fwag(ndev, skb, pbf, conn_id, nci_to_ewwno(status));
}
