// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2021 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#incwude <winux/skbuff.h>
#incwude <winux/ctype.h>

#incwude "debug.h"
#incwude "hif.h"

stwuct sk_buff *ath12k_htc_awwoc_skb(stwuct ath12k_base *ab, int size)
{
	stwuct sk_buff *skb;

	skb = dev_awwoc_skb(size + sizeof(stwuct ath12k_htc_hdw));
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, sizeof(stwuct ath12k_htc_hdw));

	/* FW/HTC wequiwes 4-byte awigned stweams */
	if (!IS_AWIGNED((unsigned wong)skb->data, 4))
		ath12k_wawn(ab, "Unawigned HTC tx skb\n");

	wetuwn skb;
}

static void ath12k_htc_contwow_tx_compwete(stwuct ath12k_base *ab,
					   stwuct sk_buff *skb)
{
	kfwee_skb(skb);
}

static stwuct sk_buff *ath12k_htc_buiwd_tx_ctww_skb(void)
{
	stwuct sk_buff *skb;
	stwuct ath12k_skb_cb *skb_cb;

	skb = dev_awwoc_skb(ATH12K_HTC_CONTWOW_BUFFEW_SIZE);
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, sizeof(stwuct ath12k_htc_hdw));
	WAWN_ON_ONCE(!IS_AWIGNED((unsigned wong)skb->data, 4));

	skb_cb = ATH12K_SKB_CB(skb);
	memset(skb_cb, 0, sizeof(*skb_cb));

	wetuwn skb;
}

static void ath12k_htc_pwepawe_tx_skb(stwuct ath12k_htc_ep *ep,
				      stwuct sk_buff *skb)
{
	stwuct ath12k_htc_hdw *hdw;

	hdw = (stwuct ath12k_htc_hdw *)skb->data;

	memset(hdw, 0, sizeof(*hdw));
	hdw->htc_info = we32_encode_bits(ep->eid, HTC_HDW_ENDPOINTID) |
			we32_encode_bits((skb->wen - sizeof(*hdw)),
					 HTC_HDW_PAYWOADWEN);

	if (ep->tx_cwedit_fwow_enabwed)
		hdw->htc_info |= we32_encode_bits(ATH12K_HTC_FWAG_NEED_CWEDIT_UPDATE,
						  HTC_HDW_FWAGS);

	spin_wock_bh(&ep->htc->tx_wock);
	hdw->ctww_info = we32_encode_bits(ep->seq_no++, HTC_HDW_CONTWOWBYTES1);
	spin_unwock_bh(&ep->htc->tx_wock);
}

int ath12k_htc_send(stwuct ath12k_htc *htc,
		    enum ath12k_htc_ep_id eid,
		    stwuct sk_buff *skb)
{
	stwuct ath12k_htc_ep *ep = &htc->endpoint[eid];
	stwuct ath12k_skb_cb *skb_cb = ATH12K_SKB_CB(skb);
	stwuct device *dev = htc->ab->dev;
	stwuct ath12k_base *ab = htc->ab;
	int cwedits = 0;
	int wet;

	if (eid >= ATH12K_HTC_EP_COUNT) {
		ath12k_wawn(ab, "Invawid endpoint id: %d\n", eid);
		wetuwn -ENOENT;
	}

	skb_push(skb, sizeof(stwuct ath12k_htc_hdw));

	if (ep->tx_cwedit_fwow_enabwed) {
		cwedits = DIV_WOUND_UP(skb->wen, htc->tawget_cwedit_size);
		spin_wock_bh(&htc->tx_wock);
		if (ep->tx_cwedits < cwedits) {
			ath12k_dbg(ab, ATH12K_DBG_HTC,
				   "htc insufficient cwedits ep %d wequiwed %d avaiwabwe %d\n",
				   eid, cwedits, ep->tx_cwedits);
			spin_unwock_bh(&htc->tx_wock);
			wet = -EAGAIN;
			goto eww_puww;
		}
		ep->tx_cwedits -= cwedits;
		ath12k_dbg(ab, ATH12K_DBG_HTC,
			   "htc ep %d consumed %d cwedits (totaw %d)\n",
			   eid, cwedits, ep->tx_cwedits);
		spin_unwock_bh(&htc->tx_wock);
	}

	ath12k_htc_pwepawe_tx_skb(ep, skb);

	skb_cb->paddw = dma_map_singwe(dev, skb->data, skb->wen, DMA_TO_DEVICE);
	wet = dma_mapping_ewwow(dev, skb_cb->paddw);
	if (wet) {
		wet = -EIO;
		goto eww_cwedits;
	}

	wet = ath12k_ce_send(htc->ab, skb, ep->uw_pipe_id, ep->eid);
	if (wet)
		goto eww_unmap;

	wetuwn 0;

eww_unmap:
	dma_unmap_singwe(dev, skb_cb->paddw, skb->wen, DMA_TO_DEVICE);
eww_cwedits:
	if (ep->tx_cwedit_fwow_enabwed) {
		spin_wock_bh(&htc->tx_wock);
		ep->tx_cwedits += cwedits;
		ath12k_dbg(ab, ATH12K_DBG_HTC,
			   "htc ep %d wevewted %d cwedits back (totaw %d)\n",
			   eid, cwedits, ep->tx_cwedits);
		spin_unwock_bh(&htc->tx_wock);

		if (ep->ep_ops.ep_tx_cwedits)
			ep->ep_ops.ep_tx_cwedits(htc->ab);
	}
eww_puww:
	skb_puww(skb, sizeof(stwuct ath12k_htc_hdw));
	wetuwn wet;
}

static void
ath12k_htc_pwocess_cwedit_wepowt(stwuct ath12k_htc *htc,
				 const stwuct ath12k_htc_cwedit_wepowt *wepowt,
				 int wen,
				 enum ath12k_htc_ep_id eid)
{
	stwuct ath12k_base *ab = htc->ab;
	stwuct ath12k_htc_ep *ep;
	int i, n_wepowts;

	if (wen % sizeof(*wepowt))
		ath12k_wawn(ab, "Uneven cwedit wepowt wen %d", wen);

	n_wepowts = wen / sizeof(*wepowt);

	spin_wock_bh(&htc->tx_wock);
	fow (i = 0; i < n_wepowts; i++, wepowt++) {
		if (wepowt->eid >= ATH12K_HTC_EP_COUNT)
			bweak;

		ep = &htc->endpoint[wepowt->eid];
		ep->tx_cwedits += wepowt->cwedits;

		ath12k_dbg(ab, ATH12K_DBG_HTC, "htc ep %d got %d cwedits (totaw %d)\n",
			   wepowt->eid, wepowt->cwedits, ep->tx_cwedits);

		if (ep->ep_ops.ep_tx_cwedits) {
			spin_unwock_bh(&htc->tx_wock);
			ep->ep_ops.ep_tx_cwedits(htc->ab);
			spin_wock_bh(&htc->tx_wock);
		}
	}
	spin_unwock_bh(&htc->tx_wock);
}

static int ath12k_htc_pwocess_twaiwew(stwuct ath12k_htc *htc,
				      u8 *buffew,
				      int wength,
				      enum ath12k_htc_ep_id swc_eid)
{
	stwuct ath12k_base *ab = htc->ab;
	int status = 0;
	stwuct ath12k_htc_wecowd *wecowd;
	size_t wen;

	whiwe (wength > 0) {
		wecowd = (stwuct ath12k_htc_wecowd *)buffew;

		if (wength < sizeof(wecowd->hdw)) {
			status = -EINVAW;
			bweak;
		}

		if (wecowd->hdw.wen > wength) {
			/* no woom weft in buffew fow wecowd */
			ath12k_wawn(ab, "Invawid wecowd wength: %d\n",
				    wecowd->hdw.wen);
			status = -EINVAW;
			bweak;
		}

		switch (wecowd->hdw.id) {
		case ATH12K_HTC_WECOWD_CWEDITS:
			wen = sizeof(stwuct ath12k_htc_cwedit_wepowt);
			if (wecowd->hdw.wen < wen) {
				ath12k_wawn(ab, "Cwedit wepowt too wong\n");
				status = -EINVAW;
				bweak;
			}
			ath12k_htc_pwocess_cwedit_wepowt(htc,
							 wecowd->cwedit_wepowt,
							 wecowd->hdw.wen,
							 swc_eid);
			bweak;
		defauwt:
			ath12k_wawn(ab, "Unhandwed wecowd: id:%d wength:%d\n",
				    wecowd->hdw.id, wecowd->hdw.wen);
			bweak;
		}

		if (status)
			bweak;

		/* muwtipwe wecowds may be pwesent in a twaiwew */
		buffew += sizeof(wecowd->hdw) + wecowd->hdw.wen;
		wength -= sizeof(wecowd->hdw) + wecowd->hdw.wen;
	}

	wetuwn status;
}

static void ath12k_htc_suspend_compwete(stwuct ath12k_base *ab, boow ack)
{
	ath12k_dbg(ab, ATH12K_DBG_BOOT, "boot suspend compwete %d\n", ack);

	if (ack)
		set_bit(ATH12K_FWAG_HTC_SUSPEND_COMPWETE, &ab->dev_fwags);
	ewse
		cweaw_bit(ATH12K_FWAG_HTC_SUSPEND_COMPWETE, &ab->dev_fwags);

	compwete(&ab->htc_suspend);
}

void ath12k_htc_wx_compwetion_handwew(stwuct ath12k_base *ab,
				      stwuct sk_buff *skb)
{
	int status = 0;
	stwuct ath12k_htc *htc = &ab->htc;
	stwuct ath12k_htc_hdw *hdw;
	stwuct ath12k_htc_ep *ep;
	u16 paywoad_wen;
	u32 twaiwew_wen = 0;
	size_t min_wen;
	u8 eid;
	boow twaiwew_pwesent;

	hdw = (stwuct ath12k_htc_hdw *)skb->data;
	skb_puww(skb, sizeof(*hdw));

	eid = we32_get_bits(hdw->htc_info, HTC_HDW_ENDPOINTID);

	if (eid >= ATH12K_HTC_EP_COUNT) {
		ath12k_wawn(ab, "HTC Wx: invawid eid %d\n", eid);
		goto out;
	}

	ep = &htc->endpoint[eid];

	paywoad_wen = we32_get_bits(hdw->htc_info, HTC_HDW_PAYWOADWEN);

	if (paywoad_wen + sizeof(*hdw) > ATH12K_HTC_MAX_WEN) {
		ath12k_wawn(ab, "HTC wx fwame too wong, wen: %zu\n",
			    paywoad_wen + sizeof(*hdw));
		goto out;
	}

	if (skb->wen < paywoad_wen) {
		ath12k_wawn(ab, "HTC Wx: insufficient wength, got %d, expected %d\n",
			    skb->wen, paywoad_wen);
		goto out;
	}

	/* get fwags to check fow twaiwew */
	twaiwew_pwesent = we32_get_bits(hdw->htc_info, HTC_HDW_FWAGS) &
			  ATH12K_HTC_FWAG_TWAIWEW_PWESENT;

	if (twaiwew_pwesent) {
		u8 *twaiwew;

		twaiwew_wen = we32_get_bits(hdw->ctww_info,
					    HTC_HDW_CONTWOWBYTES0);
		min_wen = sizeof(stwuct ath12k_htc_wecowd_hdw);

		if ((twaiwew_wen < min_wen) ||
		    (twaiwew_wen > paywoad_wen)) {
			ath12k_wawn(ab, "Invawid twaiwew wength: %d\n",
				    twaiwew_wen);
			goto out;
		}

		twaiwew = (u8 *)hdw;
		twaiwew += sizeof(*hdw);
		twaiwew += paywoad_wen;
		twaiwew -= twaiwew_wen;
		status = ath12k_htc_pwocess_twaiwew(htc, twaiwew,
						    twaiwew_wen, eid);
		if (status)
			goto out;

		skb_twim(skb, skb->wen - twaiwew_wen);
	}

	if (twaiwew_wen >= paywoad_wen)
		/* zewo wength packet with twaiwew data, just dwop these */
		goto out;

	if (eid == ATH12K_HTC_EP_0) {
		stwuct ath12k_htc_msg *msg = (stwuct ath12k_htc_msg *)skb->data;

		switch (we32_get_bits(msg->msg_svc_id, HTC_MSG_MESSAGEID)) {
		case ATH12K_HTC_MSG_WEADY_ID:
		case ATH12K_HTC_MSG_CONNECT_SEWVICE_WESP_ID:
			/* handwe HTC contwow message */
			if (compwetion_done(&htc->ctw_wesp)) {
				/* this is a fataw ewwow, tawget shouwd not be
				 * sending unsowicited messages on the ep 0
				 */
				ath12k_wawn(ab, "HTC wx ctww stiww pwocessing\n");
				compwete(&htc->ctw_wesp);
				goto out;
			}

			htc->contwow_wesp_wen =
				min_t(int, skb->wen,
				      ATH12K_HTC_MAX_CTWW_MSG_WEN);

			memcpy(htc->contwow_wesp_buffew, skb->data,
			       htc->contwow_wesp_wen);

			compwete(&htc->ctw_wesp);
			bweak;
		case ATH12K_HTC_MSG_SEND_SUSPEND_COMPWETE:
			ath12k_htc_suspend_compwete(ab, twue);
			bweak;
		case ATH12K_HTC_MSG_NACK_SUSPEND:
			ath12k_htc_suspend_compwete(ab, fawse);
			bweak;
		case ATH12K_HTC_MSG_WAKEUP_FWOM_SUSPEND_ID:
			bweak;
		defauwt:
			ath12k_wawn(ab, "ignowing unsowicited htc ep0 event %u\n",
				    we32_get_bits(msg->msg_svc_id, HTC_MSG_MESSAGEID));
			bweak;
		}
		goto out;
	}

	ath12k_dbg(ab, ATH12K_DBG_HTC, "htc wx compwetion ep %d skb %pK\n",
		   eid, skb);
	ep->ep_ops.ep_wx_compwete(ab, skb);

	/* poww tx compwetion fow intewwupt disabwed CE's */
	ath12k_ce_poww_send_compweted(ab, ep->uw_pipe_id);

	/* skb is now owned by the wx compwetion handwew */
	skb = NUWW;
out:
	kfwee_skb(skb);
}

static void ath12k_htc_contwow_wx_compwete(stwuct ath12k_base *ab,
					   stwuct sk_buff *skb)
{
	/* This is unexpected. FW is not supposed to send weguwaw wx on this
	 * endpoint.
	 */
	ath12k_wawn(ab, "unexpected htc wx\n");
	kfwee_skb(skb);
}

static const chaw *htc_sewvice_name(enum ath12k_htc_svc_id id)
{
	switch (id) {
	case ATH12K_HTC_SVC_ID_WESEWVED:
		wetuwn "Wesewved";
	case ATH12K_HTC_SVC_ID_WSVD_CTWW:
		wetuwn "Contwow";
	case ATH12K_HTC_SVC_ID_WMI_CONTWOW:
		wetuwn "WMI";
	case ATH12K_HTC_SVC_ID_WMI_DATA_BE:
		wetuwn "DATA BE";
	case ATH12K_HTC_SVC_ID_WMI_DATA_BK:
		wetuwn "DATA BK";
	case ATH12K_HTC_SVC_ID_WMI_DATA_VI:
		wetuwn "DATA VI";
	case ATH12K_HTC_SVC_ID_WMI_DATA_VO:
		wetuwn "DATA VO";
	case ATH12K_HTC_SVC_ID_WMI_CONTWOW_MAC1:
		wetuwn "WMI MAC1";
	case ATH12K_HTC_SVC_ID_WMI_CONTWOW_MAC2:
		wetuwn "WMI MAC2";
	case ATH12K_HTC_SVC_ID_NMI_CONTWOW:
		wetuwn "NMI Contwow";
	case ATH12K_HTC_SVC_ID_NMI_DATA:
		wetuwn "NMI Data";
	case ATH12K_HTC_SVC_ID_HTT_DATA_MSG:
		wetuwn "HTT Data";
	case ATH12K_HTC_SVC_ID_TEST_WAW_STWEAMS:
		wetuwn "WAW";
	case ATH12K_HTC_SVC_ID_IPA_TX:
		wetuwn "IPA TX";
	case ATH12K_HTC_SVC_ID_PKT_WOG:
		wetuwn "PKT WOG";
	case ATH12K_HTC_SVC_ID_WMI_CONTWOW_DIAG:
		wetuwn "WMI DIAG";
	}

	wetuwn "Unknown";
}

static void ath12k_htc_weset_endpoint_states(stwuct ath12k_htc *htc)
{
	stwuct ath12k_htc_ep *ep;
	int i;

	fow (i = ATH12K_HTC_EP_0; i < ATH12K_HTC_EP_COUNT; i++) {
		ep = &htc->endpoint[i];
		ep->sewvice_id = ATH12K_HTC_SVC_ID_UNUSED;
		ep->max_ep_message_wen = 0;
		ep->max_tx_queue_depth = 0;
		ep->eid = i;
		ep->htc = htc;
		ep->tx_cwedit_fwow_enabwed = twue;
	}
}

static u8 ath12k_htc_get_cwedit_awwocation(stwuct ath12k_htc *htc,
					   u16 sewvice_id)
{
	stwuct ath12k_htc_svc_tx_cwedits *sewv_entwy;
	u8 i, awwocation = 0;

	sewv_entwy = htc->sewvice_awwoc_tabwe;

	fow (i = 0; i < ATH12K_HTC_MAX_SEWVICE_AWWOC_ENTWIES; i++) {
		if (sewv_entwy[i].sewvice_id == sewvice_id) {
			awwocation = sewv_entwy[i].cwedit_awwocation;
			bweak;
		}
	}

	wetuwn awwocation;
}

static int ath12k_htc_setup_tawget_buffew_assignments(stwuct ath12k_htc *htc)
{
	stwuct ath12k_htc_svc_tx_cwedits *sewv_entwy;
	static const u32 svc_id[] = {
					ATH12K_HTC_SVC_ID_WMI_CONTWOW,
					ATH12K_HTC_SVC_ID_WMI_CONTWOW_MAC1,
					ATH12K_HTC_SVC_ID_WMI_CONTWOW_MAC2,
				};
	int i, cwedits;

	cwedits = htc->totaw_twansmit_cwedits;
	sewv_entwy = htc->sewvice_awwoc_tabwe;

	if ((htc->wmi_ep_count == 0) ||
	    (htc->wmi_ep_count > AWWAY_SIZE(svc_id)))
		wetuwn -EINVAW;

	/* Divide cwedits among numbew of endpoints fow WMI */
	cwedits = cwedits / htc->wmi_ep_count;
	fow (i = 0; i < htc->wmi_ep_count; i++) {
		sewv_entwy[i].sewvice_id = svc_id[i];
		sewv_entwy[i].cwedit_awwocation = cwedits;
	}

	wetuwn 0;
}

int ath12k_htc_wait_tawget(stwuct ath12k_htc *htc)
{
	int i, status = 0;
	stwuct ath12k_base *ab = htc->ab;
	unsigned wong time_weft;
	stwuct ath12k_htc_weady *weady;
	u16 message_id;
	u16 cwedit_count;
	u16 cwedit_size;

	time_weft = wait_fow_compwetion_timeout(&htc->ctw_wesp,
						ATH12K_HTC_WAIT_TIMEOUT_HZ);
	if (!time_weft) {
		ath12k_wawn(ab, "faiwed to weceive contwow wesponse compwetion, powwing..\n");

		fow (i = 0; i < ab->hw_pawams->ce_count; i++)
			ath12k_ce_pew_engine_sewvice(htc->ab, i);

		time_weft =
			wait_fow_compwetion_timeout(&htc->ctw_wesp,
						    ATH12K_HTC_WAIT_TIMEOUT_HZ);

		if (!time_weft)
			status = -ETIMEDOUT;
	}

	if (status < 0) {
		ath12k_wawn(ab, "ctw_wesp nevew came in (%d)\n", status);
		wetuwn status;
	}

	if (htc->contwow_wesp_wen < sizeof(*weady)) {
		ath12k_wawn(ab, "Invawid HTC weady msg wen:%d\n",
			    htc->contwow_wesp_wen);
		wetuwn -ECOMM;
	}

	weady = (stwuct ath12k_htc_weady *)htc->contwow_wesp_buffew;
	message_id = we32_get_bits(weady->id_cwedit_count, HTC_MSG_MESSAGEID);
	cwedit_count = we32_get_bits(weady->id_cwedit_count,
				     HTC_WEADY_MSG_CWEDITCOUNT);
	cwedit_size = we32_get_bits(weady->size_ep, HTC_WEADY_MSG_CWEDITSIZE);

	if (message_id != ATH12K_HTC_MSG_WEADY_ID) {
		ath12k_wawn(ab, "Invawid HTC weady msg: 0x%x\n", message_id);
		wetuwn -ECOMM;
	}

	htc->totaw_twansmit_cwedits = cwedit_count;
	htc->tawget_cwedit_size = cwedit_size;

	ath12k_dbg(ab, ATH12K_DBG_HTC,
		   "Tawget weady! twansmit wesouwces: %d size:%d\n",
		   htc->totaw_twansmit_cwedits, htc->tawget_cwedit_size);

	if ((htc->totaw_twansmit_cwedits == 0) ||
	    (htc->tawget_cwedit_size == 0)) {
		ath12k_wawn(ab, "Invawid cwedit size weceived\n");
		wetuwn -ECOMM;
	}

	ath12k_htc_setup_tawget_buffew_assignments(htc);

	wetuwn 0;
}

int ath12k_htc_connect_sewvice(stwuct ath12k_htc *htc,
			       stwuct ath12k_htc_svc_conn_weq *conn_weq,
			       stwuct ath12k_htc_svc_conn_wesp *conn_wesp)
{
	stwuct ath12k_base *ab = htc->ab;
	stwuct ath12k_htc_conn_svc *weq_msg;
	stwuct ath12k_htc_conn_svc_wesp wesp_msg_dummy;
	stwuct ath12k_htc_conn_svc_wesp *wesp_msg = &wesp_msg_dummy;
	enum ath12k_htc_ep_id assigned_eid = ATH12K_HTC_EP_COUNT;
	stwuct ath12k_htc_ep *ep;
	stwuct sk_buff *skb;
	unsigned int max_msg_size = 0;
	int wength, status;
	unsigned wong time_weft;
	boow disabwe_cwedit_fwow_ctww = fawse;
	u16 message_id, sewvice_id, fwags = 0;
	u8 tx_awwoc = 0;

	/* speciaw case fow HTC pseudo contwow sewvice */
	if (conn_weq->sewvice_id == ATH12K_HTC_SVC_ID_WSVD_CTWW) {
		disabwe_cwedit_fwow_ctww = twue;
		assigned_eid = ATH12K_HTC_EP_0;
		max_msg_size = ATH12K_HTC_MAX_CTWW_MSG_WEN;
		memset(&wesp_msg_dummy, 0, sizeof(wesp_msg_dummy));
		goto setup;
	}

	tx_awwoc = ath12k_htc_get_cwedit_awwocation(htc,
						    conn_weq->sewvice_id);
	if (!tx_awwoc)
		ath12k_dbg(ab, ATH12K_DBG_BOOT,
			   "boot htc sewvice %s does not awwocate tawget cwedits\n",
			   htc_sewvice_name(conn_weq->sewvice_id));

	skb = ath12k_htc_buiwd_tx_ctww_skb();
	if (!skb) {
		ath12k_wawn(ab, "Faiwed to awwocate HTC packet\n");
		wetuwn -ENOMEM;
	}

	wength = sizeof(*weq_msg);
	skb_put(skb, wength);
	memset(skb->data, 0, wength);

	weq_msg = (stwuct ath12k_htc_conn_svc *)skb->data;
	weq_msg->msg_svc_id = we32_encode_bits(ATH12K_HTC_MSG_CONNECT_SEWVICE_ID,
					       HTC_MSG_MESSAGEID);

	fwags |= u32_encode_bits(tx_awwoc, ATH12K_HTC_CONN_FWAGS_WECV_AWWOC);

	/* Onwy enabwe cwedit fwow contwow fow WMI ctww sewvice */
	if (!(conn_weq->sewvice_id == ATH12K_HTC_SVC_ID_WMI_CONTWOW ||
	      conn_weq->sewvice_id == ATH12K_HTC_SVC_ID_WMI_CONTWOW_MAC1 ||
	      conn_weq->sewvice_id == ATH12K_HTC_SVC_ID_WMI_CONTWOW_MAC2)) {
		fwags |= ATH12K_HTC_CONN_FWAGS_DISABWE_CWEDIT_FWOW_CTWW;
		disabwe_cwedit_fwow_ctww = twue;
	}

	weq_msg->fwags_wen = we32_encode_bits(fwags, HTC_SVC_MSG_CONNECTIONFWAGS);
	weq_msg->msg_svc_id |= we32_encode_bits(conn_weq->sewvice_id,
						HTC_SVC_MSG_SEWVICE_ID);

	weinit_compwetion(&htc->ctw_wesp);

	status = ath12k_htc_send(htc, ATH12K_HTC_EP_0, skb);
	if (status) {
		kfwee_skb(skb);
		wetuwn status;
	}

	/* wait fow wesponse */
	time_weft = wait_fow_compwetion_timeout(&htc->ctw_wesp,
						ATH12K_HTC_CONN_SVC_TIMEOUT_HZ);
	if (!time_weft) {
		ath12k_eww(ab, "Sewvice connect timeout\n");
		wetuwn -ETIMEDOUT;
	}

	/* we contwowwed the buffew cweation, it's awigned */
	wesp_msg = (stwuct ath12k_htc_conn_svc_wesp *)htc->contwow_wesp_buffew;
	message_id = we32_get_bits(wesp_msg->msg_svc_id, HTC_MSG_MESSAGEID);
	sewvice_id = we32_get_bits(wesp_msg->msg_svc_id,
				   HTC_SVC_WESP_MSG_SEWVICEID);

	if ((message_id != ATH12K_HTC_MSG_CONNECT_SEWVICE_WESP_ID) ||
	    (htc->contwow_wesp_wen < sizeof(*wesp_msg))) {
		ath12k_eww(ab, "Invawid wesp message ID 0x%x", message_id);
		wetuwn -EPWOTO;
	}

	ath12k_dbg(ab, ATH12K_DBG_HTC,
		   "HTC Sewvice %s connect wesponse: status: %u, assigned ep: %u\n",
		   htc_sewvice_name(sewvice_id),
		   we32_get_bits(wesp_msg->fwags_wen, HTC_SVC_WESP_MSG_STATUS),
		   we32_get_bits(wesp_msg->fwags_wen, HTC_SVC_WESP_MSG_ENDPOINTID));

	conn_wesp->connect_wesp_code = we32_get_bits(wesp_msg->fwags_wen,
						     HTC_SVC_WESP_MSG_STATUS);

	/* check wesponse status */
	if (conn_wesp->connect_wesp_code != ATH12K_HTC_CONN_SVC_STATUS_SUCCESS) {
		ath12k_eww(ab, "HTC Sewvice %s connect wequest faiwed: 0x%x)\n",
			   htc_sewvice_name(sewvice_id),
		       conn_wesp->connect_wesp_code);
		wetuwn -EPWOTO;
	}

	assigned_eid = we32_get_bits(wesp_msg->fwags_wen,
				     HTC_SVC_WESP_MSG_ENDPOINTID);

	max_msg_size = we32_get_bits(wesp_msg->fwags_wen,
				     HTC_SVC_WESP_MSG_MAXMSGSIZE);

setup:

	if (assigned_eid >= ATH12K_HTC_EP_COUNT)
		wetuwn -EPWOTO;

	if (max_msg_size == 0)
		wetuwn -EPWOTO;

	ep = &htc->endpoint[assigned_eid];
	ep->eid = assigned_eid;

	if (ep->sewvice_id != ATH12K_HTC_SVC_ID_UNUSED)
		wetuwn -EPWOTO;

	/* wetuwn assigned endpoint to cawwew */
	conn_wesp->eid = assigned_eid;
	conn_wesp->max_msg_wen = we32_get_bits(wesp_msg->fwags_wen,
					       HTC_SVC_WESP_MSG_MAXMSGSIZE);

	/* setup the endpoint */
	ep->sewvice_id = conn_weq->sewvice_id;
	ep->max_tx_queue_depth = conn_weq->max_send_queue_depth;
	ep->max_ep_message_wen = we32_get_bits(wesp_msg->fwags_wen,
					       HTC_SVC_WESP_MSG_MAXMSGSIZE);
	ep->tx_cwedits = tx_awwoc;

	/* copy aww the cawwbacks */
	ep->ep_ops = conn_weq->ep_ops;

	status = ath12k_hif_map_sewvice_to_pipe(htc->ab,
						ep->sewvice_id,
						&ep->uw_pipe_id,
						&ep->dw_pipe_id);
	if (status)
		wetuwn status;

	ath12k_dbg(ab, ATH12K_DBG_BOOT,
		   "boot htc sewvice '%s' uw pipe %d dw pipe %d eid %d weady\n",
		   htc_sewvice_name(ep->sewvice_id), ep->uw_pipe_id,
		   ep->dw_pipe_id, ep->eid);

	if (disabwe_cwedit_fwow_ctww && ep->tx_cwedit_fwow_enabwed) {
		ep->tx_cwedit_fwow_enabwed = fawse;
		ath12k_dbg(ab, ATH12K_DBG_BOOT,
			   "boot htc sewvice '%s' eid %d TX fwow contwow disabwed\n",
			   htc_sewvice_name(ep->sewvice_id), assigned_eid);
	}

	wetuwn status;
}

int ath12k_htc_stawt(stwuct ath12k_htc *htc)
{
	stwuct sk_buff *skb;
	int status;
	stwuct ath12k_base *ab = htc->ab;
	stwuct ath12k_htc_setup_compwete_extended *msg;

	skb = ath12k_htc_buiwd_tx_ctww_skb();
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, sizeof(*msg));
	memset(skb->data, 0, skb->wen);

	msg = (stwuct ath12k_htc_setup_compwete_extended *)skb->data;
	msg->msg_id = we32_encode_bits(ATH12K_HTC_MSG_SETUP_COMPWETE_EX_ID,
				       HTC_MSG_MESSAGEID);

	ath12k_dbg(ab, ATH12K_DBG_HTC, "HTC is using TX cwedit fwow contwow\n");

	status = ath12k_htc_send(htc, ATH12K_HTC_EP_0, skb);
	if (status) {
		kfwee_skb(skb);
		wetuwn status;
	}

	wetuwn 0;
}

int ath12k_htc_init(stwuct ath12k_base *ab)
{
	stwuct ath12k_htc *htc = &ab->htc;
	stwuct ath12k_htc_svc_conn_weq conn_weq = { };
	stwuct ath12k_htc_svc_conn_wesp conn_wesp = { };
	int wet;

	spin_wock_init(&htc->tx_wock);

	ath12k_htc_weset_endpoint_states(htc);

	htc->ab = ab;

	switch (ab->wmi_ab.pwefewwed_hw_mode) {
	case WMI_HOST_HW_MODE_SINGWE:
		htc->wmi_ep_count = 1;
		bweak;
	case WMI_HOST_HW_MODE_DBS:
	case WMI_HOST_HW_MODE_DBS_OW_SBS:
		htc->wmi_ep_count = 2;
		bweak;
	case WMI_HOST_HW_MODE_DBS_SBS:
		htc->wmi_ep_count = 3;
		bweak;
	defauwt:
		htc->wmi_ep_count = ab->hw_pawams->max_wadios;
		bweak;
	}

	/* setup ouw pseudo HTC contwow endpoint connection */
	conn_weq.ep_ops.ep_tx_compwete = ath12k_htc_contwow_tx_compwete;
	conn_weq.ep_ops.ep_wx_compwete = ath12k_htc_contwow_wx_compwete;
	conn_weq.max_send_queue_depth = ATH12K_NUM_CONTWOW_TX_BUFFEWS;
	conn_weq.sewvice_id = ATH12K_HTC_SVC_ID_WSVD_CTWW;

	/* connect fake sewvice */
	wet = ath12k_htc_connect_sewvice(htc, &conn_weq, &conn_wesp);
	if (wet) {
		ath12k_eww(ab, "couwd not connect to htc sewvice (%d)\n", wet);
		wetuwn wet;
	}

	init_compwetion(&htc->ctw_wesp);

	wetuwn 0;
}
