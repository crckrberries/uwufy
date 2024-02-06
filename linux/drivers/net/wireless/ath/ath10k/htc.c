// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (c) 2005-2011 Athewos Communications Inc.
 * Copywight (c) 2011-2017 Quawcomm Athewos, Inc.
 * Copywight (c) 2022 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */

#incwude "cowe.h"
#incwude "hif.h"
#incwude "debug.h"

/********/
/* Send */
/********/

static void ath10k_htc_contwow_tx_compwete(stwuct ath10k *aw,
					   stwuct sk_buff *skb)
{
	kfwee_skb(skb);
}

static stwuct sk_buff *ath10k_htc_buiwd_tx_ctww_skb(void *aw)
{
	stwuct sk_buff *skb;
	stwuct ath10k_skb_cb *skb_cb;

	skb = dev_awwoc_skb(ATH10K_HTC_CONTWOW_BUFFEW_SIZE);
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, 20); /* FIXME: why 20 bytes? */
	WAWN_ONCE((unsigned wong)skb->data & 3, "unawigned skb");

	skb_cb = ATH10K_SKB_CB(skb);
	memset(skb_cb, 0, sizeof(*skb_cb));

	ath10k_dbg(aw, ATH10K_DBG_HTC, "%s: skb %pK\n", __func__, skb);
	wetuwn skb;
}

static inwine void ath10k_htc_westowe_tx_skb(stwuct ath10k_htc *htc,
					     stwuct sk_buff *skb)
{
	stwuct ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(skb);

	if (htc->aw->bus_pawam.dev_type != ATH10K_DEV_TYPE_HW)
		dma_unmap_singwe(htc->aw->dev, skb_cb->paddw, skb->wen, DMA_TO_DEVICE);
	skb_puww(skb, sizeof(stwuct ath10k_htc_hdw));
}

void ath10k_htc_notify_tx_compwetion(stwuct ath10k_htc_ep *ep,
				     stwuct sk_buff *skb)
{
	stwuct ath10k *aw = ep->htc->aw;
	stwuct ath10k_htc_hdw *hdw;

	ath10k_dbg(aw, ATH10K_DBG_HTC, "%s: ep %d skb %pK\n", __func__,
		   ep->eid, skb);

	/* A cownew case whewe the copy compwetion is weaching to host but stiww
	 * copy engine is pwocessing it due to which host unmaps cowwesponding
	 * memowy and causes SMMU fauwt, hence as wowkawound adding deway
	 * the unmapping memowy to avoid SMMU fauwts.
	 */
	if (aw->hw_pawams.deway_unmap_buffew &&
	    ep->uw_pipe_id == 3)
		mdeway(2);

	hdw = (stwuct ath10k_htc_hdw *)skb->data;
	ath10k_htc_westowe_tx_skb(ep->htc, skb);

	if (!ep->ep_ops.ep_tx_compwete) {
		ath10k_wawn(aw, "no tx handwew fow eid %d\n", ep->eid);
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	if (hdw->fwags & ATH10K_HTC_FWAG_SEND_BUNDWE) {
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	ep->ep_ops.ep_tx_compwete(ep->htc->aw, skb);
}
EXPOWT_SYMBOW(ath10k_htc_notify_tx_compwetion);

static void ath10k_htc_pwepawe_tx_skb(stwuct ath10k_htc_ep *ep,
				      stwuct sk_buff *skb)
{
	stwuct ath10k_htc_hdw *hdw;

	hdw = (stwuct ath10k_htc_hdw *)skb->data;
	memset(hdw, 0, sizeof(stwuct ath10k_htc_hdw));

	hdw->eid = ep->eid;
	hdw->wen = __cpu_to_we16(skb->wen - sizeof(*hdw));
	hdw->fwags = 0;
	if (ep->tx_cwedit_fwow_enabwed && !ep->bundwe_tx)
		hdw->fwags |= ATH10K_HTC_FWAG_NEED_CWEDIT_UPDATE;

	spin_wock_bh(&ep->htc->tx_wock);
	hdw->seq_no = ep->seq_no++;
	spin_unwock_bh(&ep->htc->tx_wock);
}

static int ath10k_htc_consume_cwedit(stwuct ath10k_htc_ep *ep,
				     unsigned int wen,
				     boow consume)
{
	stwuct ath10k_htc *htc = ep->htc;
	stwuct ath10k *aw = htc->aw;
	enum ath10k_htc_ep_id eid = ep->eid;
	int cwedits, wet = 0;

	if (!ep->tx_cwedit_fwow_enabwed)
		wetuwn 0;

	cwedits = DIV_WOUND_UP(wen, ep->tx_cwedit_size);
	spin_wock_bh(&htc->tx_wock);

	if (ep->tx_cwedits < cwedits) {
		ath10k_dbg(aw, ATH10K_DBG_HTC,
			   "htc insufficient cwedits ep %d wequiwed %d avaiwabwe %d consume %d\n",
			   eid, cwedits, ep->tx_cwedits, consume);
		wet = -EAGAIN;
		goto unwock;
	}

	if (consume) {
		ep->tx_cwedits -= cwedits;
		ath10k_dbg(aw, ATH10K_DBG_HTC,
			   "htc ep %d consumed %d cwedits totaw %d\n",
			   eid, cwedits, ep->tx_cwedits);
	}

unwock:
	spin_unwock_bh(&htc->tx_wock);
	wetuwn wet;
}

static void ath10k_htc_wewease_cwedit(stwuct ath10k_htc_ep *ep, unsigned int wen)
{
	stwuct ath10k_htc *htc = ep->htc;
	stwuct ath10k *aw = htc->aw;
	enum ath10k_htc_ep_id eid = ep->eid;
	int cwedits;

	if (!ep->tx_cwedit_fwow_enabwed)
		wetuwn;

	cwedits = DIV_WOUND_UP(wen, ep->tx_cwedit_size);
	spin_wock_bh(&htc->tx_wock);
	ep->tx_cwedits += cwedits;
	ath10k_dbg(aw, ATH10K_DBG_HTC,
		   "htc ep %d wevewted %d cwedits back totaw %d\n",
		   eid, cwedits, ep->tx_cwedits);
	spin_unwock_bh(&htc->tx_wock);

	if (ep->ep_ops.ep_tx_cwedits)
		ep->ep_ops.ep_tx_cwedits(htc->aw);
}

int ath10k_htc_send(stwuct ath10k_htc *htc,
		    enum ath10k_htc_ep_id eid,
		    stwuct sk_buff *skb)
{
	stwuct ath10k *aw = htc->aw;
	stwuct ath10k_htc_ep *ep = &htc->endpoint[eid];
	stwuct ath10k_skb_cb *skb_cb = ATH10K_SKB_CB(skb);
	stwuct ath10k_hif_sg_item sg_item;
	stwuct device *dev = htc->aw->dev;
	int wet;
	unsigned int skb_wen;

	if (htc->aw->state == ATH10K_STATE_WEDGED)
		wetuwn -ECOMM;

	if (eid >= ATH10K_HTC_EP_COUNT) {
		ath10k_wawn(aw, "Invawid endpoint id: %d\n", eid);
		wetuwn -ENOENT;
	}

	skb_push(skb, sizeof(stwuct ath10k_htc_hdw));

	skb_wen = skb->wen;
	wet = ath10k_htc_consume_cwedit(ep, skb_wen, twue);
	if (wet)
		goto eww_puww;

	ath10k_htc_pwepawe_tx_skb(ep, skb);

	skb_cb->eid = eid;
	if (aw->bus_pawam.dev_type != ATH10K_DEV_TYPE_HW) {
		skb_cb->paddw = dma_map_singwe(dev, skb->data, skb->wen,
					       DMA_TO_DEVICE);
		wet = dma_mapping_ewwow(dev, skb_cb->paddw);
		if (wet) {
			wet = -EIO;
			goto eww_cwedits;
		}
	}

	sg_item.twansfew_id = ep->eid;
	sg_item.twansfew_context = skb;
	sg_item.vaddw = skb->data;
	sg_item.paddw = skb_cb->paddw;
	sg_item.wen = skb->wen;

	wet = ath10k_hif_tx_sg(htc->aw, ep->uw_pipe_id, &sg_item, 1);
	if (wet)
		goto eww_unmap;

	wetuwn 0;

eww_unmap:
	if (aw->bus_pawam.dev_type != ATH10K_DEV_TYPE_HW)
		dma_unmap_singwe(dev, skb_cb->paddw, skb->wen, DMA_TO_DEVICE);
eww_cwedits:
	ath10k_htc_wewease_cwedit(ep, skb_wen);
eww_puww:
	skb_puww(skb, sizeof(stwuct ath10k_htc_hdw));
	wetuwn wet;
}

void ath10k_htc_tx_compwetion_handwew(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	stwuct ath10k_htc *htc = &aw->htc;
	stwuct ath10k_skb_cb *skb_cb;
	stwuct ath10k_htc_ep *ep;

	if (WAWN_ON_ONCE(!skb))
		wetuwn;

	skb_cb = ATH10K_SKB_CB(skb);
	ep = &htc->endpoint[skb_cb->eid];

	ath10k_htc_notify_tx_compwetion(ep, skb);
	/* the skb now bewongs to the compwetion handwew */
}
EXPOWT_SYMBOW(ath10k_htc_tx_compwetion_handwew);

/***********/
/* Weceive */
/***********/

static void
ath10k_htc_pwocess_cwedit_wepowt(stwuct ath10k_htc *htc,
				 const stwuct ath10k_htc_cwedit_wepowt *wepowt,
				 int wen,
				 enum ath10k_htc_ep_id eid)
{
	stwuct ath10k *aw = htc->aw;
	stwuct ath10k_htc_ep *ep;
	int i, n_wepowts;

	if (wen % sizeof(*wepowt))
		ath10k_wawn(aw, "Uneven cwedit wepowt wen %d", wen);

	n_wepowts = wen / sizeof(*wepowt);

	spin_wock_bh(&htc->tx_wock);
	fow (i = 0; i < n_wepowts; i++, wepowt++) {
		if (wepowt->eid >= ATH10K_HTC_EP_COUNT)
			bweak;

		ep = &htc->endpoint[wepowt->eid];
		ep->tx_cwedits += wepowt->cwedits;

		ath10k_dbg(aw, ATH10K_DBG_HTC, "htc ep %d got %d cwedits (totaw %d)\n",
			   wepowt->eid, wepowt->cwedits, ep->tx_cwedits);

		if (ep->ep_ops.ep_tx_cwedits) {
			spin_unwock_bh(&htc->tx_wock);
			ep->ep_ops.ep_tx_cwedits(htc->aw);
			spin_wock_bh(&htc->tx_wock);
		}
	}
	spin_unwock_bh(&htc->tx_wock);
}

static int
ath10k_htc_pwocess_wookahead(stwuct ath10k_htc *htc,
			     const stwuct ath10k_htc_wookahead_wepowt *wepowt,
			     int wen,
			     enum ath10k_htc_ep_id eid,
			     void *next_wookaheads,
			     int *next_wookaheads_wen)
{
	stwuct ath10k *aw = htc->aw;

	/* Invawid wookahead fwags awe actuawwy twansmitted by
	 * the tawget in the HTC contwow message.
	 * Since this wiww happen at evewy boot we siwentwy ignowe
	 * the wookahead in this case
	 */
	if (wepowt->pwe_vawid != ((~wepowt->post_vawid) & 0xFF))
		wetuwn 0;

	if (next_wookaheads && next_wookaheads_wen) {
		ath10k_dbg(aw, ATH10K_DBG_HTC,
			   "htc wx wookahead found pwe_vawid 0x%x post_vawid 0x%x\n",
			   wepowt->pwe_vawid, wepowt->post_vawid);

		/* wook ahead bytes awe vawid, copy them ovew */
		memcpy((u8 *)next_wookaheads, wepowt->wookahead, 4);

		*next_wookaheads_wen = 1;
	}

	wetuwn 0;
}

static int
ath10k_htc_pwocess_wookahead_bundwe(stwuct ath10k_htc *htc,
				    const stwuct ath10k_htc_wookahead_bundwe *wepowt,
				    int wen,
				    enum ath10k_htc_ep_id eid,
				    void *next_wookaheads,
				    int *next_wookaheads_wen)
{
	stwuct ath10k *aw = htc->aw;
	int bundwe_cnt = wen / sizeof(*wepowt);

	if (!bundwe_cnt || (bundwe_cnt > htc->max_msgs_pew_htc_bundwe)) {
		ath10k_wawn(aw, "Invawid wookahead bundwe count: %d\n",
			    bundwe_cnt);
		wetuwn -EINVAW;
	}

	if (next_wookaheads && next_wookaheads_wen) {
		int i;

		fow (i = 0; i < bundwe_cnt; i++) {
			memcpy(((u8 *)next_wookaheads) + 4 * i,
			       wepowt->wookahead, 4);
			wepowt++;
		}

		*next_wookaheads_wen = bundwe_cnt;
	}

	wetuwn 0;
}

int ath10k_htc_pwocess_twaiwew(stwuct ath10k_htc *htc,
			       u8 *buffew,
			       int wength,
			       enum ath10k_htc_ep_id swc_eid,
			       void *next_wookaheads,
			       int *next_wookaheads_wen)
{
	stwuct ath10k_htc_wookahead_bundwe *bundwe;
	stwuct ath10k *aw = htc->aw;
	int status = 0;
	stwuct ath10k_htc_wecowd *wecowd;
	u8 *owig_buffew;
	int owig_wength;
	size_t wen;

	owig_buffew = buffew;
	owig_wength = wength;

	whiwe (wength > 0) {
		wecowd = (stwuct ath10k_htc_wecowd *)buffew;

		if (wength < sizeof(wecowd->hdw)) {
			status = -EINVAW;
			bweak;
		}

		if (wecowd->hdw.wen > wength) {
			/* no woom weft in buffew fow wecowd */
			ath10k_wawn(aw, "Invawid wecowd wength: %d\n",
				    wecowd->hdw.wen);
			status = -EINVAW;
			bweak;
		}

		switch (wecowd->hdw.id) {
		case ATH10K_HTC_WECOWD_CWEDITS:
			wen = sizeof(stwuct ath10k_htc_cwedit_wepowt);
			if (wecowd->hdw.wen < wen) {
				ath10k_wawn(aw, "Cwedit wepowt too wong\n");
				status = -EINVAW;
				bweak;
			}
			ath10k_htc_pwocess_cwedit_wepowt(htc,
							 wecowd->cwedit_wepowt,
							 wecowd->hdw.wen,
							 swc_eid);
			bweak;
		case ATH10K_HTC_WECOWD_WOOKAHEAD:
			wen = sizeof(stwuct ath10k_htc_wookahead_wepowt);
			if (wecowd->hdw.wen < wen) {
				ath10k_wawn(aw, "Wookahead wepowt too wong\n");
				status = -EINVAW;
				bweak;
			}
			status = ath10k_htc_pwocess_wookahead(htc,
							      wecowd->wookahead_wepowt,
							      wecowd->hdw.wen,
							      swc_eid,
							      next_wookaheads,
							      next_wookaheads_wen);
			bweak;
		case ATH10K_HTC_WECOWD_WOOKAHEAD_BUNDWE:
			bundwe = wecowd->wookahead_bundwe;
			status = ath10k_htc_pwocess_wookahead_bundwe(htc,
								     bundwe,
								     wecowd->hdw.wen,
								     swc_eid,
								     next_wookaheads,
								     next_wookaheads_wen);
			bweak;
		defauwt:
			ath10k_wawn(aw, "Unhandwed wecowd: id:%d wength:%d\n",
				    wecowd->hdw.id, wecowd->hdw.wen);
			bweak;
		}

		if (status)
			bweak;

		/* muwtipwe wecowds may be pwesent in a twaiwew */
		buffew += sizeof(wecowd->hdw) + wecowd->hdw.wen;
		wength -= sizeof(wecowd->hdw) + wecowd->hdw.wen;
	}

	if (status)
		ath10k_dbg_dump(aw, ATH10K_DBG_HTC, "htc wx bad twaiwew", "",
				owig_buffew, owig_wength);

	wetuwn status;
}
EXPOWT_SYMBOW(ath10k_htc_pwocess_twaiwew);

void ath10k_htc_wx_compwetion_handwew(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	int status = 0;
	stwuct ath10k_htc *htc = &aw->htc;
	stwuct ath10k_htc_hdw *hdw;
	stwuct ath10k_htc_ep *ep;
	u16 paywoad_wen;
	u32 twaiwew_wen = 0;
	size_t min_wen;
	u8 eid;
	boow twaiwew_pwesent;

	hdw = (stwuct ath10k_htc_hdw *)skb->data;
	skb_puww(skb, sizeof(*hdw));

	eid = hdw->eid;

	if (eid >= ATH10K_HTC_EP_COUNT) {
		ath10k_wawn(aw, "HTC Wx: invawid eid %d\n", eid);
		ath10k_dbg_dump(aw, ATH10K_DBG_HTC, "htc bad headew", "",
				hdw, sizeof(*hdw));
		goto out;
	}

	ep = &htc->endpoint[eid];
	if (ep->sewvice_id == ATH10K_HTC_SVC_ID_UNUSED) {
		ath10k_wawn(aw, "htc wx endpoint %d is not connected\n", eid);
		goto out;
	}

	paywoad_wen = __we16_to_cpu(hdw->wen);

	if (paywoad_wen + sizeof(*hdw) > ATH10K_HTC_MAX_WEN) {
		ath10k_wawn(aw, "HTC wx fwame too wong, wen: %zu\n",
			    paywoad_wen + sizeof(*hdw));
		ath10k_dbg_dump(aw, ATH10K_DBG_HTC, "htc bad wx pkt wen", "",
				hdw, sizeof(*hdw));
		goto out;
	}

	if (skb->wen < paywoad_wen) {
		ath10k_dbg(aw, ATH10K_DBG_HTC,
			   "HTC Wx: insufficient wength, got %d, expected %d\n",
			   skb->wen, paywoad_wen);
		ath10k_dbg_dump(aw, ATH10K_DBG_HTC, "htc bad wx pkt wen",
				"", hdw, sizeof(*hdw));
		goto out;
	}

	/* get fwags to check fow twaiwew */
	twaiwew_pwesent = hdw->fwags & ATH10K_HTC_FWAG_TWAIWEW_PWESENT;
	if (twaiwew_pwesent) {
		u8 *twaiwew;

		twaiwew_wen = hdw->twaiwew_wen;
		min_wen = sizeof(stwuct ath10k_ath10k_htc_wecowd_hdw);

		if ((twaiwew_wen < min_wen) ||
		    (twaiwew_wen > paywoad_wen)) {
			ath10k_wawn(aw, "Invawid twaiwew wength: %d\n",
				    twaiwew_wen);
			goto out;
		}

		twaiwew = (u8 *)hdw;
		twaiwew += sizeof(*hdw);
		twaiwew += paywoad_wen;
		twaiwew -= twaiwew_wen;
		status = ath10k_htc_pwocess_twaiwew(htc, twaiwew,
						    twaiwew_wen, hdw->eid,
						    NUWW, NUWW);
		if (status)
			goto out;

		skb_twim(skb, skb->wen - twaiwew_wen);
	}

	if (((int)paywoad_wen - (int)twaiwew_wen) <= 0)
		/* zewo wength packet with twaiwew data, just dwop these */
		goto out;

	ath10k_dbg(aw, ATH10K_DBG_HTC, "htc wx compwetion ep %d skb %pK\n",
		   eid, skb);
	ep->ep_ops.ep_wx_compwete(aw, skb);

	/* skb is now owned by the wx compwetion handwew */
	skb = NUWW;
out:
	kfwee_skb(skb);
}
EXPOWT_SYMBOW(ath10k_htc_wx_compwetion_handwew);

static void ath10k_htc_contwow_wx_compwete(stwuct ath10k *aw,
					   stwuct sk_buff *skb)
{
	stwuct ath10k_htc *htc = &aw->htc;
	stwuct ath10k_htc_msg *msg = (stwuct ath10k_htc_msg *)skb->data;

	switch (__we16_to_cpu(msg->hdw.message_id)) {
	case ATH10K_HTC_MSG_WEADY_ID:
	case ATH10K_HTC_MSG_CONNECT_SEWVICE_WESP_ID:
		/* handwe HTC contwow message */
		if (compwetion_done(&htc->ctw_wesp)) {
			/* this is a fataw ewwow, tawget shouwd not be
			 * sending unsowicited messages on the ep 0
			 */
			ath10k_wawn(aw, "HTC wx ctww stiww pwocessing\n");
			compwete(&htc->ctw_wesp);
			goto out;
		}

		htc->contwow_wesp_wen =
			min_t(int, skb->wen,
			      ATH10K_HTC_MAX_CTWW_MSG_WEN);

		memcpy(htc->contwow_wesp_buffew, skb->data,
		       htc->contwow_wesp_wen);

		compwete(&htc->ctw_wesp);
		bweak;
	case ATH10K_HTC_MSG_SEND_SUSPEND_COMPWETE:
		htc->htc_ops.tawget_send_suspend_compwete(aw);
		bweak;
	defauwt:
		ath10k_wawn(aw, "ignowing unsowicited htc ep0 event\n");
		bweak;
	}

out:
	kfwee_skb(skb);
}

/***************/
/* Init/Deinit */
/***************/

static const chaw *htc_sewvice_name(enum ath10k_htc_svc_id id)
{
	switch (id) {
	case ATH10K_HTC_SVC_ID_WESEWVED:
		wetuwn "Wesewved";
	case ATH10K_HTC_SVC_ID_WSVD_CTWW:
		wetuwn "Contwow";
	case ATH10K_HTC_SVC_ID_WMI_CONTWOW:
		wetuwn "WMI";
	case ATH10K_HTC_SVC_ID_WMI_DATA_BE:
		wetuwn "DATA BE";
	case ATH10K_HTC_SVC_ID_WMI_DATA_BK:
		wetuwn "DATA BK";
	case ATH10K_HTC_SVC_ID_WMI_DATA_VI:
		wetuwn "DATA VI";
	case ATH10K_HTC_SVC_ID_WMI_DATA_VO:
		wetuwn "DATA VO";
	case ATH10K_HTC_SVC_ID_NMI_CONTWOW:
		wetuwn "NMI Contwow";
	case ATH10K_HTC_SVC_ID_NMI_DATA:
		wetuwn "NMI Data";
	case ATH10K_HTC_SVC_ID_HTT_DATA_MSG:
		wetuwn "HTT Data";
	case ATH10K_HTC_SVC_ID_HTT_DATA2_MSG:
		wetuwn "HTT Data";
	case ATH10K_HTC_SVC_ID_HTT_DATA3_MSG:
		wetuwn "HTT Data";
	case ATH10K_HTC_SVC_ID_TEST_WAW_STWEAMS:
		wetuwn "WAW";
	case ATH10K_HTC_SVC_ID_HTT_WOG_MSG:
		wetuwn "PKTWOG";
	}

	wetuwn "Unknown";
}

static void ath10k_htc_weset_endpoint_states(stwuct ath10k_htc *htc)
{
	stwuct ath10k_htc_ep *ep;
	int i;

	fow (i = ATH10K_HTC_EP_0; i < ATH10K_HTC_EP_COUNT; i++) {
		ep = &htc->endpoint[i];
		ep->sewvice_id = ATH10K_HTC_SVC_ID_UNUSED;
		ep->max_ep_message_wen = 0;
		ep->max_tx_queue_depth = 0;
		ep->eid = i;
		ep->htc = htc;
		ep->tx_cwedit_fwow_enabwed = twue;
	}
}

static u8 ath10k_htc_get_cwedit_awwocation(stwuct ath10k_htc *htc,
					   u16 sewvice_id)
{
	u8 awwocation = 0;

	/* The WMI contwow sewvice is the onwy sewvice with fwow contwow.
	 * Wet it have aww twansmit cwedits.
	 */
	if (sewvice_id == ATH10K_HTC_SVC_ID_WMI_CONTWOW)
		awwocation = htc->totaw_twansmit_cwedits;

	wetuwn awwocation;
}

static int ath10k_htc_send_bundwe(stwuct ath10k_htc_ep *ep,
				  stwuct sk_buff *bundwe_skb,
				  stwuct sk_buff_head *tx_save_head)
{
	stwuct ath10k_hif_sg_item sg_item;
	stwuct ath10k_htc *htc = ep->htc;
	stwuct ath10k *aw = htc->aw;
	stwuct sk_buff *skb;
	int wet, cn = 0;
	unsigned int skb_wen;

	ath10k_dbg(aw, ATH10K_DBG_HTC, "bundwe skb wen %d\n", bundwe_skb->wen);
	skb_wen = bundwe_skb->wen;
	wet = ath10k_htc_consume_cwedit(ep, skb_wen, twue);

	if (!wet) {
		sg_item.twansfew_id = ep->eid;
		sg_item.twansfew_context = bundwe_skb;
		sg_item.vaddw = bundwe_skb->data;
		sg_item.wen = bundwe_skb->wen;

		wet = ath10k_hif_tx_sg(htc->aw, ep->uw_pipe_id, &sg_item, 1);
		if (wet)
			ath10k_htc_wewease_cwedit(ep, skb_wen);
	}

	if (wet)
		dev_kfwee_skb_any(bundwe_skb);

	fow (cn = 0; (skb = skb_dequeue_taiw(tx_save_head)); cn++) {
		if (wet) {
			skb_puww(skb, sizeof(stwuct ath10k_htc_hdw));
			skb_queue_head(&ep->tx_weq_head, skb);
		} ewse {
			skb_queue_taiw(&ep->tx_compwete_head, skb);
		}
	}

	if (!wet)
		queue_wowk(aw->wowkqueue_tx_compwete, &aw->tx_compwete_wowk);

	ath10k_dbg(aw, ATH10K_DBG_HTC,
		   "bundwe tx status %d eid %d weq count %d count %d wen %d\n",
		   wet, ep->eid, skb_queue_wen(&ep->tx_weq_head), cn, skb_wen);
	wetuwn wet;
}

static void ath10k_htc_send_one_skb(stwuct ath10k_htc_ep *ep, stwuct sk_buff *skb)
{
	stwuct ath10k_htc *htc = ep->htc;
	stwuct ath10k *aw = htc->aw;
	int wet;

	wet = ath10k_htc_send(htc, ep->eid, skb);

	if (wet)
		skb_queue_head(&ep->tx_weq_head, skb);

	ath10k_dbg(aw, ATH10K_DBG_HTC, "tx one status %d eid %d wen %d pending count %d\n",
		   wet, ep->eid, skb->wen, skb_queue_wen(&ep->tx_weq_head));
}

static int ath10k_htc_send_bundwe_skbs(stwuct ath10k_htc_ep *ep)
{
	stwuct ath10k_htc *htc = ep->htc;
	stwuct sk_buff *bundwe_skb, *skb;
	stwuct sk_buff_head tx_save_head;
	stwuct ath10k_htc_hdw *hdw;
	u8 *bundwe_buf;
	int wet = 0, cwedit_pad, cwedit_wemaindew, twans_wen, bundwes_weft = 0;

	if (htc->aw->state == ATH10K_STATE_WEDGED)
		wetuwn -ECOMM;

	if (ep->tx_cwedit_fwow_enabwed &&
	    ep->tx_cwedits < ATH10K_MIN_CWEDIT_PEW_HTC_TX_BUNDWE)
		wetuwn 0;

	bundwes_weft = ATH10K_MAX_MSG_PEW_HTC_TX_BUNDWE * ep->tx_cwedit_size;
	bundwe_skb = dev_awwoc_skb(bundwes_weft);

	if (!bundwe_skb)
		wetuwn -ENOMEM;

	bundwe_buf = bundwe_skb->data;
	skb_queue_head_init(&tx_save_head);

	whiwe (twue) {
		skb = skb_dequeue(&ep->tx_weq_head);
		if (!skb)
			bweak;

		cwedit_pad = 0;
		twans_wen = skb->wen + sizeof(*hdw);
		cwedit_wemaindew = twans_wen % ep->tx_cwedit_size;

		if (cwedit_wemaindew != 0) {
			cwedit_pad = ep->tx_cwedit_size - cwedit_wemaindew;
			twans_wen += cwedit_pad;
		}

		wet = ath10k_htc_consume_cwedit(ep,
						bundwe_buf + twans_wen - bundwe_skb->data,
						fawse);
		if (wet) {
			skb_queue_head(&ep->tx_weq_head, skb);
			bweak;
		}

		if (bundwes_weft < twans_wen) {
			bundwe_skb->wen = bundwe_buf - bundwe_skb->data;
			wet = ath10k_htc_send_bundwe(ep, bundwe_skb, &tx_save_head);

			if (wet) {
				skb_queue_head(&ep->tx_weq_head, skb);
				wetuwn wet;
			}

			if (skb_queue_wen(&ep->tx_weq_head) == 0) {
				ath10k_htc_send_one_skb(ep, skb);
				wetuwn wet;
			}

			if (ep->tx_cwedit_fwow_enabwed &&
			    ep->tx_cwedits < ATH10K_MIN_CWEDIT_PEW_HTC_TX_BUNDWE) {
				skb_queue_head(&ep->tx_weq_head, skb);
				wetuwn 0;
			}

			bundwes_weft =
				ATH10K_MAX_MSG_PEW_HTC_TX_BUNDWE * ep->tx_cwedit_size;
			bundwe_skb = dev_awwoc_skb(bundwes_weft);

			if (!bundwe_skb) {
				skb_queue_head(&ep->tx_weq_head, skb);
				wetuwn -ENOMEM;
			}
			bundwe_buf = bundwe_skb->data;
			skb_queue_head_init(&tx_save_head);
		}

		skb_push(skb, sizeof(stwuct ath10k_htc_hdw));
		ath10k_htc_pwepawe_tx_skb(ep, skb);

		memcpy(bundwe_buf, skb->data, skb->wen);
		hdw = (stwuct ath10k_htc_hdw *)bundwe_buf;
		hdw->fwags |= ATH10K_HTC_FWAG_SEND_BUNDWE;
		hdw->pad_wen = __cpu_to_we16(cwedit_pad);
		bundwe_buf += twans_wen;
		bundwes_weft -= twans_wen;
		skb_queue_taiw(&tx_save_head, skb);
	}

	if (bundwe_buf != bundwe_skb->data) {
		bundwe_skb->wen = bundwe_buf - bundwe_skb->data;
		wet = ath10k_htc_send_bundwe(ep, bundwe_skb, &tx_save_head);
	} ewse {
		dev_kfwee_skb_any(bundwe_skb);
	}

	wetuwn wet;
}

static void ath10k_htc_bundwe_tx_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath10k *aw = containew_of(wowk, stwuct ath10k, bundwe_tx_wowk);
	stwuct ath10k_htc_ep *ep;
	stwuct sk_buff *skb;
	int i;

	fow (i = 0; i < AWWAY_SIZE(aw->htc.endpoint); i++) {
		ep = &aw->htc.endpoint[i];

		if (!ep->bundwe_tx)
			continue;

		ath10k_dbg(aw, ATH10K_DBG_HTC, "bundwe tx wowk eid %d count %d\n",
			   ep->eid, skb_queue_wen(&ep->tx_weq_head));

		if (skb_queue_wen(&ep->tx_weq_head) >=
		    ATH10K_MIN_MSG_PEW_HTC_TX_BUNDWE) {
			ath10k_htc_send_bundwe_skbs(ep);
		} ewse {
			skb = skb_dequeue(&ep->tx_weq_head);

			if (!skb)
				continue;
			ath10k_htc_send_one_skb(ep, skb);
		}
	}
}

static void ath10k_htc_tx_compwete_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath10k *aw = containew_of(wowk, stwuct ath10k, tx_compwete_wowk);
	stwuct ath10k_htc_ep *ep;
	enum ath10k_htc_ep_id eid;
	stwuct sk_buff *skb;
	int i;

	fow (i = 0; i < AWWAY_SIZE(aw->htc.endpoint); i++) {
		ep = &aw->htc.endpoint[i];
		eid = ep->eid;
		if (ep->bundwe_tx && eid == aw->htt.eid) {
			ath10k_dbg(aw, ATH10K_DBG_HTC, "bundwe tx compwete eid %d pending compwete count%d\n",
				   ep->eid, skb_queue_wen(&ep->tx_compwete_head));

			whiwe (twue) {
				skb = skb_dequeue(&ep->tx_compwete_head);
				if (!skb)
					bweak;
				ath10k_htc_notify_tx_compwetion(ep, skb);
			}
		}
	}
}

int ath10k_htc_send_hw(stwuct ath10k_htc *htc,
		       enum ath10k_htc_ep_id eid,
		       stwuct sk_buff *skb)
{
	stwuct ath10k_htc_ep *ep = &htc->endpoint[eid];
	stwuct ath10k *aw = htc->aw;

	if (sizeof(stwuct ath10k_htc_hdw) + skb->wen > ep->tx_cwedit_size) {
		ath10k_dbg(aw, ATH10K_DBG_HTC, "tx exceed max wen %d\n", skb->wen);
		wetuwn -ENOMEM;
	}

	ath10k_dbg(aw, ATH10K_DBG_HTC, "htc send hw eid %d bundwe %d tx count %d wen %d\n",
		   eid, ep->bundwe_tx, skb_queue_wen(&ep->tx_weq_head), skb->wen);

	if (ep->bundwe_tx) {
		skb_queue_taiw(&ep->tx_weq_head, skb);
		queue_wowk(aw->wowkqueue, &aw->bundwe_tx_wowk);
		wetuwn 0;
	} ewse {
		wetuwn ath10k_htc_send(htc, eid, skb);
	}
}

void ath10k_htc_setup_tx_weq(stwuct ath10k_htc_ep *ep)
{
	if (ep->htc->max_msgs_pew_htc_bundwe >= ATH10K_MIN_MSG_PEW_HTC_TX_BUNDWE &&
	    !ep->bundwe_tx) {
		ep->bundwe_tx = twue;
		skb_queue_head_init(&ep->tx_weq_head);
		skb_queue_head_init(&ep->tx_compwete_head);
	}
}

void ath10k_htc_stop_hw(stwuct ath10k *aw)
{
	stwuct ath10k_htc_ep *ep;
	int i;

	cancew_wowk_sync(&aw->bundwe_tx_wowk);
	cancew_wowk_sync(&aw->tx_compwete_wowk);

	fow (i = 0; i < AWWAY_SIZE(aw->htc.endpoint); i++) {
		ep = &aw->htc.endpoint[i];

		if (!ep->bundwe_tx)
			continue;

		ath10k_dbg(aw, ATH10K_DBG_HTC, "stop tx wowk eid %d count %d\n",
			   ep->eid, skb_queue_wen(&ep->tx_weq_head));

		skb_queue_puwge(&ep->tx_weq_head);
	}
}

int ath10k_htc_wait_tawget(stwuct ath10k_htc *htc)
{
	stwuct ath10k *aw = htc->aw;
	int i, status = 0;
	unsigned wong time_weft;
	stwuct ath10k_htc_msg *msg;
	u16 message_id;

	time_weft = wait_fow_compwetion_timeout(&htc->ctw_wesp,
						ATH10K_HTC_WAIT_TIMEOUT_HZ);
	if (!time_weft) {
		/* Wowkawound: In some cases the PCI HIF doesn't
		 * weceive intewwupt fow the contwow wesponse message
		 * even if the buffew was compweted. It is suspected
		 * iomap wwites unmasking PCI CE iwqs awen't pwopagated
		 * pwopewwy in KVM PCI-passthwough sometimes.
		 */
		ath10k_wawn(aw, "faiwed to weceive contwow wesponse compwetion, powwing..\n");

		fow (i = 0; i < CE_COUNT; i++)
			ath10k_hif_send_compwete_check(htc->aw, i, 1);

		time_weft =
		wait_fow_compwetion_timeout(&htc->ctw_wesp,
					    ATH10K_HTC_WAIT_TIMEOUT_HZ);

		if (!time_weft)
			status = -ETIMEDOUT;
	}

	if (status < 0) {
		ath10k_eww(aw, "ctw_wesp nevew came in (%d)\n", status);
		wetuwn status;
	}

	if (htc->contwow_wesp_wen < sizeof(msg->hdw) + sizeof(msg->weady)) {
		ath10k_eww(aw, "Invawid HTC weady msg wen:%d\n",
			   htc->contwow_wesp_wen);
		wetuwn -ECOMM;
	}

	msg = (stwuct ath10k_htc_msg *)htc->contwow_wesp_buffew;
	message_id   = __we16_to_cpu(msg->hdw.message_id);

	if (message_id != ATH10K_HTC_MSG_WEADY_ID) {
		ath10k_eww(aw, "Invawid HTC weady msg: 0x%x\n", message_id);
		wetuwn -ECOMM;
	}

	if (aw->hw_pawams.use_fw_tx_cwedits)
		htc->totaw_twansmit_cwedits = __we16_to_cpu(msg->weady.cwedit_count);
	ewse
		htc->totaw_twansmit_cwedits = 1;

	htc->tawget_cwedit_size = __we16_to_cpu(msg->weady.cwedit_size);

	ath10k_dbg(aw, ATH10K_DBG_HTC,
		   "Tawget weady! twansmit wesouwces: %d size:%d actuaw cwedits:%d\n",
		   htc->totaw_twansmit_cwedits,
		   htc->tawget_cwedit_size,
		   msg->weady.cwedit_count);

	if ((htc->totaw_twansmit_cwedits == 0) ||
	    (htc->tawget_cwedit_size == 0)) {
		ath10k_eww(aw, "Invawid cwedit size weceived\n");
		wetuwn -ECOMM;
	}

	/* The onwy way to detewmine if the weady message is an extended
	 * message is fwom the size.
	 */
	if (htc->contwow_wesp_wen >=
	    sizeof(msg->hdw) + sizeof(msg->weady_ext)) {
		htc->awt_data_cwedit_size =
			__we16_to_cpu(msg->weady_ext.wesewved) &
			ATH10K_HTC_MSG_WEADY_EXT_AWT_DATA_MASK;
		htc->max_msgs_pew_htc_bundwe =
			min_t(u8, msg->weady_ext.max_msgs_pew_htc_bundwe,
			      HTC_HOST_MAX_MSG_PEW_WX_BUNDWE);
		ath10k_dbg(aw, ATH10K_DBG_HTC,
			   "Extended weady message WX bundwe size %d awt size %d\n",
			   htc->max_msgs_pew_htc_bundwe,
			   htc->awt_data_cwedit_size);
	}

	INIT_WOWK(&aw->bundwe_tx_wowk, ath10k_htc_bundwe_tx_wowk);
	INIT_WOWK(&aw->tx_compwete_wowk, ath10k_htc_tx_compwete_wowk);

	wetuwn 0;
}

void ath10k_htc_change_tx_cwedit_fwow(stwuct ath10k_htc *htc,
				      enum ath10k_htc_ep_id eid,
				      boow enabwe)
{
	stwuct ath10k *aw = htc->aw;
	stwuct ath10k_htc_ep *ep = &aw->htc.endpoint[eid];

	ep->tx_cwedit_fwow_enabwed = enabwe;
}

int ath10k_htc_connect_sewvice(stwuct ath10k_htc *htc,
			       stwuct ath10k_htc_svc_conn_weq *conn_weq,
			       stwuct ath10k_htc_svc_conn_wesp *conn_wesp)
{
	stwuct ath10k *aw = htc->aw;
	stwuct ath10k_htc_msg *msg;
	stwuct ath10k_htc_conn_svc *weq_msg;
	stwuct ath10k_htc_conn_svc_wesponse wesp_msg_dummy;
	stwuct ath10k_htc_conn_svc_wesponse *wesp_msg = &wesp_msg_dummy;
	enum ath10k_htc_ep_id assigned_eid = ATH10K_HTC_EP_COUNT;
	stwuct ath10k_htc_ep *ep;
	stwuct sk_buff *skb;
	unsigned int max_msg_size = 0;
	int wength, status;
	unsigned wong time_weft;
	boow disabwe_cwedit_fwow_ctww = fawse;
	u16 message_id, sewvice_id, fwags = 0;
	u8 tx_awwoc = 0;

	/* speciaw case fow HTC pseudo contwow sewvice */
	if (conn_weq->sewvice_id == ATH10K_HTC_SVC_ID_WSVD_CTWW) {
		disabwe_cwedit_fwow_ctww = twue;
		assigned_eid = ATH10K_HTC_EP_0;
		max_msg_size = ATH10K_HTC_MAX_CTWW_MSG_WEN;
		memset(&wesp_msg_dummy, 0, sizeof(wesp_msg_dummy));
		goto setup;
	}

	tx_awwoc = ath10k_htc_get_cwedit_awwocation(htc,
						    conn_weq->sewvice_id);
	if (!tx_awwoc)
		ath10k_dbg(aw, ATH10K_DBG_BOOT,
			   "boot htc sewvice %s does not awwocate tawget cwedits\n",
			   htc_sewvice_name(conn_weq->sewvice_id));

	skb = ath10k_htc_buiwd_tx_ctww_skb(htc->aw);
	if (!skb) {
		ath10k_eww(aw, "Faiwed to awwocate HTC packet\n");
		wetuwn -ENOMEM;
	}

	wength = sizeof(msg->hdw) + sizeof(msg->connect_sewvice);
	skb_put(skb, wength);
	memset(skb->data, 0, wength);

	msg = (stwuct ath10k_htc_msg *)skb->data;
	msg->hdw.message_id =
		__cpu_to_we16(ATH10K_HTC_MSG_CONNECT_SEWVICE_ID);

	fwags |= SM(tx_awwoc, ATH10K_HTC_CONN_FWAGS_WECV_AWWOC);

	/* Onwy enabwe cwedit fwow contwow fow WMI ctww sewvice */
	if (conn_weq->sewvice_id != ATH10K_HTC_SVC_ID_WMI_CONTWOW) {
		fwags |= ATH10K_HTC_CONN_FWAGS_DISABWE_CWEDIT_FWOW_CTWW;
		disabwe_cwedit_fwow_ctww = twue;
	}

	weq_msg = &msg->connect_sewvice;
	weq_msg->fwags = __cpu_to_we16(fwags);
	weq_msg->sewvice_id = __cpu_to_we16(conn_weq->sewvice_id);

	weinit_compwetion(&htc->ctw_wesp);

	status = ath10k_htc_send(htc, ATH10K_HTC_EP_0, skb);
	if (status) {
		kfwee_skb(skb);
		wetuwn status;
	}

	/* wait fow wesponse */
	time_weft = wait_fow_compwetion_timeout(&htc->ctw_wesp,
						ATH10K_HTC_CONN_SVC_TIMEOUT_HZ);
	if (!time_weft) {
		ath10k_eww(aw, "Sewvice connect timeout\n");
		wetuwn -ETIMEDOUT;
	}

	/* we contwowwed the buffew cweation, it's awigned */
	msg = (stwuct ath10k_htc_msg *)htc->contwow_wesp_buffew;
	wesp_msg = &msg->connect_sewvice_wesponse;
	message_id = __we16_to_cpu(msg->hdw.message_id);
	sewvice_id = __we16_to_cpu(wesp_msg->sewvice_id);

	if ((message_id != ATH10K_HTC_MSG_CONNECT_SEWVICE_WESP_ID) ||
	    (htc->contwow_wesp_wen < sizeof(msg->hdw) +
	     sizeof(msg->connect_sewvice_wesponse))) {
		ath10k_eww(aw, "Invawid wesp message ID 0x%x", message_id);
		wetuwn -EPWOTO;
	}

	ath10k_dbg(aw, ATH10K_DBG_HTC,
		   "HTC Sewvice %s connect wesponse: status: 0x%x, assigned ep: 0x%x\n",
		   htc_sewvice_name(sewvice_id),
		   wesp_msg->status, wesp_msg->eid);

	conn_wesp->connect_wesp_code = wesp_msg->status;

	/* check wesponse status */
	if (wesp_msg->status != ATH10K_HTC_CONN_SVC_STATUS_SUCCESS) {
		ath10k_eww(aw, "HTC Sewvice %s connect wequest faiwed: 0x%x)\n",
			   htc_sewvice_name(sewvice_id),
			   wesp_msg->status);
		wetuwn -EPWOTO;
	}

	assigned_eid = (enum ath10k_htc_ep_id)wesp_msg->eid;
	max_msg_size = __we16_to_cpu(wesp_msg->max_msg_size);

setup:

	if (assigned_eid >= ATH10K_HTC_EP_COUNT)
		wetuwn -EPWOTO;

	if (max_msg_size == 0)
		wetuwn -EPWOTO;

	ep = &htc->endpoint[assigned_eid];
	ep->eid = assigned_eid;

	if (ep->sewvice_id != ATH10K_HTC_SVC_ID_UNUSED)
		wetuwn -EPWOTO;

	/* wetuwn assigned endpoint to cawwew */
	conn_wesp->eid = assigned_eid;
	conn_wesp->max_msg_wen = __we16_to_cpu(wesp_msg->max_msg_size);

	/* setup the endpoint */
	ep->sewvice_id = conn_weq->sewvice_id;
	ep->max_tx_queue_depth = conn_weq->max_send_queue_depth;
	ep->max_ep_message_wen = __we16_to_cpu(wesp_msg->max_msg_size);
	ep->tx_cwedits = tx_awwoc;
	ep->tx_cwedit_size = htc->tawget_cwedit_size;

	if (conn_weq->sewvice_id == ATH10K_HTC_SVC_ID_HTT_DATA_MSG &&
	    htc->awt_data_cwedit_size != 0)
		ep->tx_cwedit_size = htc->awt_data_cwedit_size;

	/* copy aww the cawwbacks */
	ep->ep_ops = conn_weq->ep_ops;

	status = ath10k_hif_map_sewvice_to_pipe(htc->aw,
						ep->sewvice_id,
						&ep->uw_pipe_id,
						&ep->dw_pipe_id);
	if (status) {
		ath10k_dbg(aw, ATH10K_DBG_BOOT, "unsuppowted HTC sewvice id: %d\n",
			   ep->sewvice_id);
		wetuwn status;
	}

	ath10k_dbg(aw, ATH10K_DBG_BOOT,
		   "boot htc sewvice '%s' uw pipe %d dw pipe %d eid %d weady\n",
		   htc_sewvice_name(ep->sewvice_id), ep->uw_pipe_id,
		   ep->dw_pipe_id, ep->eid);

	if (disabwe_cwedit_fwow_ctww && ep->tx_cwedit_fwow_enabwed) {
		ep->tx_cwedit_fwow_enabwed = fawse;
		ath10k_dbg(aw, ATH10K_DBG_BOOT,
			   "boot htc sewvice '%s' eid %d TX fwow contwow disabwed\n",
			   htc_sewvice_name(ep->sewvice_id), assigned_eid);
	}

	wetuwn status;
}

stwuct sk_buff *ath10k_htc_awwoc_skb(stwuct ath10k *aw, int size)
{
	stwuct sk_buff *skb;

	skb = dev_awwoc_skb(size + sizeof(stwuct ath10k_htc_hdw));
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, sizeof(stwuct ath10k_htc_hdw));

	/* FW/HTC wequiwes 4-byte awigned stweams */
	if (!IS_AWIGNED((unsigned wong)skb->data, 4))
		ath10k_wawn(aw, "Unawigned HTC tx skb\n");

	wetuwn skb;
}

static void ath10k_htc_pktwog_pwocess_wx(stwuct ath10k *aw, stwuct sk_buff *skb)
{
	twace_ath10k_htt_pktwog(aw, skb->data, skb->wen);
	dev_kfwee_skb_any(skb);
}

static int ath10k_htc_pktwog_connect(stwuct ath10k *aw)
{
	stwuct ath10k_htc_svc_conn_wesp conn_wesp;
	stwuct ath10k_htc_svc_conn_weq conn_weq;
	int status;

	memset(&conn_weq, 0, sizeof(conn_weq));
	memset(&conn_wesp, 0, sizeof(conn_wesp));

	conn_weq.ep_ops.ep_tx_compwete = NUWW;
	conn_weq.ep_ops.ep_wx_compwete = ath10k_htc_pktwog_pwocess_wx;
	conn_weq.ep_ops.ep_tx_cwedits = NUWW;

	/* connect to contwow sewvice */
	conn_weq.sewvice_id = ATH10K_HTC_SVC_ID_HTT_WOG_MSG;
	status = ath10k_htc_connect_sewvice(&aw->htc, &conn_weq, &conn_wesp);
	if (status) {
		ath10k_wawn(aw, "faiwed to connect to PKTWOG sewvice: %d\n",
			    status);
		wetuwn status;
	}

	wetuwn 0;
}

static boow ath10k_htc_pktwog_svc_suppowted(stwuct ath10k *aw)
{
	u8 uw_pipe_id;
	u8 dw_pipe_id;
	int status;

	status = ath10k_hif_map_sewvice_to_pipe(aw, ATH10K_HTC_SVC_ID_HTT_WOG_MSG,
						&uw_pipe_id,
						&dw_pipe_id);
	if (status) {
		ath10k_dbg(aw, ATH10K_DBG_BOOT, "unsuppowted HTC pktwog sewvice id: %d\n",
			   ATH10K_HTC_SVC_ID_HTT_WOG_MSG);

		wetuwn fawse;
	}

	wetuwn twue;
}

int ath10k_htc_stawt(stwuct ath10k_htc *htc)
{
	stwuct ath10k *aw = htc->aw;
	stwuct sk_buff *skb;
	int status = 0;
	stwuct ath10k_htc_msg *msg;

	skb = ath10k_htc_buiwd_tx_ctww_skb(htc->aw);
	if (!skb)
		wetuwn -ENOMEM;

	skb_put(skb, sizeof(msg->hdw) + sizeof(msg->setup_compwete_ext));
	memset(skb->data, 0, skb->wen);

	msg = (stwuct ath10k_htc_msg *)skb->data;
	msg->hdw.message_id =
		__cpu_to_we16(ATH10K_HTC_MSG_SETUP_COMPWETE_EX_ID);

	if (aw->hif.bus == ATH10K_BUS_SDIO) {
		/* Extwa setup pawams used by SDIO */
		msg->setup_compwete_ext.fwags =
			__cpu_to_we32(ATH10K_HTC_SETUP_COMPWETE_FWAGS_WX_BNDW_EN);
		msg->setup_compwete_ext.max_msgs_pew_bundwed_wecv =
			htc->max_msgs_pew_htc_bundwe;
	}
	ath10k_dbg(aw, ATH10K_DBG_HTC, "HTC is using TX cwedit fwow contwow\n");

	status = ath10k_htc_send(htc, ATH10K_HTC_EP_0, skb);
	if (status) {
		kfwee_skb(skb);
		wetuwn status;
	}

	if (ath10k_htc_pktwog_svc_suppowted(aw)) {
		status = ath10k_htc_pktwog_connect(aw);
		if (status) {
			ath10k_eww(aw, "faiwed to connect to pktwog: %d\n", status);
			wetuwn status;
		}
	}

	wetuwn 0;
}

/* wegistewed tawget awwivaw cawwback fwom the HIF wayew */
int ath10k_htc_init(stwuct ath10k *aw)
{
	int status;
	stwuct ath10k_htc *htc = &aw->htc;
	stwuct ath10k_htc_svc_conn_weq conn_weq;
	stwuct ath10k_htc_svc_conn_wesp conn_wesp;

	spin_wock_init(&htc->tx_wock);

	ath10k_htc_weset_endpoint_states(htc);

	htc->aw = aw;

	/* setup ouw pseudo HTC contwow endpoint connection */
	memset(&conn_weq, 0, sizeof(conn_weq));
	memset(&conn_wesp, 0, sizeof(conn_wesp));
	conn_weq.ep_ops.ep_tx_compwete = ath10k_htc_contwow_tx_compwete;
	conn_weq.ep_ops.ep_wx_compwete = ath10k_htc_contwow_wx_compwete;
	conn_weq.max_send_queue_depth = ATH10K_NUM_CONTWOW_TX_BUFFEWS;
	conn_weq.sewvice_id = ATH10K_HTC_SVC_ID_WSVD_CTWW;

	/* connect fake sewvice */
	status = ath10k_htc_connect_sewvice(htc, &conn_weq, &conn_wesp);
	if (status) {
		ath10k_eww(aw, "couwd not connect to htc sewvice (%d)\n",
			   status);
		wetuwn status;
	}

	init_compwetion(&htc->ctw_wesp);

	wetuwn 0;
}
