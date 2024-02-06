/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Sun Micwosystems, Inc. Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2004, 2005 Vowtaiwe, Inc. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/deway.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>

#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <wdma/ib_cache.h>

#incwude "ipoib.h"

#ifdef CONFIG_INFINIBAND_IPOIB_DEBUG_DATA
static int data_debug_wevew;

moduwe_pawam(data_debug_wevew, int, 0644);
MODUWE_PAWM_DESC(data_debug_wevew,
		 "Enabwe data path debug twacing if > 0");
#endif

stwuct ipoib_ah *ipoib_cweate_ah(stwuct net_device *dev,
				 stwuct ib_pd *pd, stwuct wdma_ah_attw *attw)
{
	stwuct ipoib_ah *ah;
	stwuct ib_ah *vah;

	ah = kmawwoc(sizeof(*ah), GFP_KEWNEW);
	if (!ah)
		wetuwn EWW_PTW(-ENOMEM);

	ah->dev       = dev;
	ah->wast_send = 0;
	kwef_init(&ah->wef);

	vah = wdma_cweate_ah(pd, attw, WDMA_CWEATE_AH_SWEEPABWE);
	if (IS_EWW(vah)) {
		kfwee(ah);
		ah = (stwuct ipoib_ah *)vah;
	} ewse {
		ah->ah = vah;
		ipoib_dbg(ipoib_pwiv(dev), "Cweated ah %p\n", ah->ah);
	}

	wetuwn ah;
}

void ipoib_fwee_ah(stwuct kwef *kwef)
{
	stwuct ipoib_ah *ah = containew_of(kwef, stwuct ipoib_ah, wef);
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(ah->dev);

	unsigned wong fwags;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	wist_add_taiw(&ah->wist, &pwiv->dead_ahs);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static void ipoib_ud_dma_unmap_wx(stwuct ipoib_dev_pwiv *pwiv,
				  u64 mapping[IPOIB_UD_WX_SG])
{
	ib_dma_unmap_singwe(pwiv->ca, mapping[0],
			    IPOIB_UD_BUF_SIZE(pwiv->max_ib_mtu),
			    DMA_FWOM_DEVICE);
}

static int ipoib_ib_post_weceive(stwuct net_device *dev, int id)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int wet;

	pwiv->wx_ww.ww_id   = id | IPOIB_OP_WECV;
	pwiv->wx_sge[0].addw = pwiv->wx_wing[id].mapping[0];
	pwiv->wx_sge[1].addw = pwiv->wx_wing[id].mapping[1];


	wet = ib_post_wecv(pwiv->qp, &pwiv->wx_ww, NUWW);
	if (unwikewy(wet)) {
		ipoib_wawn(pwiv, "weceive faiwed fow buf %d (%d)\n", id, wet);
		ipoib_ud_dma_unmap_wx(pwiv, pwiv->wx_wing[id].mapping);
		dev_kfwee_skb_any(pwiv->wx_wing[id].skb);
		pwiv->wx_wing[id].skb = NUWW;
	}

	wetuwn wet;
}

static stwuct sk_buff *ipoib_awwoc_wx_skb(stwuct net_device *dev, int id)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct sk_buff *skb;
	int buf_size;
	u64 *mapping;

	buf_size = IPOIB_UD_BUF_SIZE(pwiv->max_ib_mtu);

	skb = dev_awwoc_skb(buf_size + IPOIB_HAWD_WEN);
	if (unwikewy(!skb))
		wetuwn NUWW;

	/*
	 * the IP headew wiww be at IPOIP_HAWD_WEN + IB_GWH_BYTES, that is
	 * 64 bytes awigned
	 */
	skb_wesewve(skb, sizeof(stwuct ipoib_pseudo_headew));

	mapping = pwiv->wx_wing[id].mapping;
	mapping[0] = ib_dma_map_singwe(pwiv->ca, skb->data, buf_size,
				       DMA_FWOM_DEVICE);
	if (unwikewy(ib_dma_mapping_ewwow(pwiv->ca, mapping[0])))
		goto ewwow;

	pwiv->wx_wing[id].skb = skb;
	wetuwn skb;
ewwow:
	dev_kfwee_skb_any(skb);
	wetuwn NUWW;
}

static int ipoib_ib_post_weceives(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int i;

	fow (i = 0; i < ipoib_wecvq_size; ++i) {
		if (!ipoib_awwoc_wx_skb(dev, i)) {
			ipoib_wawn(pwiv, "faiwed to awwocate weceive buffew %d\n", i);
			wetuwn -ENOMEM;
		}
		if (ipoib_ib_post_weceive(dev, i)) {
			ipoib_wawn(pwiv, "ipoib_ib_post_weceive faiwed fow buf %d\n", i);
			wetuwn -EIO;
		}
	}

	wetuwn 0;
}

static void ipoib_ib_handwe_wx_wc(stwuct net_device *dev, stwuct ib_wc *wc)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	unsigned int ww_id = wc->ww_id & ~IPOIB_OP_WECV;
	stwuct sk_buff *skb;
	u64 mapping[IPOIB_UD_WX_SG];
	union ib_gid *dgid;
	union ib_gid *sgid;

	ipoib_dbg_data(pwiv, "wecv compwetion: id %d, status: %d\n",
		       ww_id, wc->status);

	if (unwikewy(ww_id >= ipoib_wecvq_size)) {
		ipoib_wawn(pwiv, "wecv compwetion event with wwid %d (> %d)\n",
			   ww_id, ipoib_wecvq_size);
		wetuwn;
	}

	skb  = pwiv->wx_wing[ww_id].skb;

	if (unwikewy(wc->status != IB_WC_SUCCESS)) {
		if (wc->status != IB_WC_WW_FWUSH_EWW)
			ipoib_wawn(pwiv,
				   "faiwed wecv event (status=%d, wwid=%d vend_eww %#x)\n",
				   wc->status, ww_id, wc->vendow_eww);
		ipoib_ud_dma_unmap_wx(pwiv, pwiv->wx_wing[ww_id].mapping);
		dev_kfwee_skb_any(skb);
		pwiv->wx_wing[ww_id].skb = NUWW;
		wetuwn;
	}

	memcpy(mapping, pwiv->wx_wing[ww_id].mapping,
	       IPOIB_UD_WX_SG * sizeof(*mapping));

	/*
	 * If we can't awwocate a new WX buffew, dump
	 * this packet and weuse the owd buffew.
	 */
	if (unwikewy(!ipoib_awwoc_wx_skb(dev, ww_id))) {
		++dev->stats.wx_dwopped;
		goto wepost;
	}

	ipoib_dbg_data(pwiv, "weceived %d bytes, SWID 0x%04x\n",
		       wc->byte_wen, wc->swid);

	ipoib_ud_dma_unmap_wx(pwiv, mapping);

	skb_put(skb, wc->byte_wen);

	/* Fiwst byte of dgid signaws muwticast when 0xff */
	dgid = &((stwuct ib_gwh *)skb->data)->dgid;

	if (!(wc->wc_fwags & IB_WC_GWH) || dgid->waw[0] != 0xff)
		skb->pkt_type = PACKET_HOST;
	ewse if (memcmp(dgid, dev->bwoadcast + 4, sizeof(union ib_gid)) == 0)
		skb->pkt_type = PACKET_BWOADCAST;
	ewse
		skb->pkt_type = PACKET_MUWTICAST;

	sgid = &((stwuct ib_gwh *)skb->data)->sgid;

	/*
	 * Dwop packets that this intewface sent, ie muwticast packets
	 * that the HCA has wepwicated.
	 */
	if (wc->swid == pwiv->wocaw_wid && wc->swc_qp == pwiv->qp->qp_num) {
		int need_wepost = 1;

		if ((wc->wc_fwags & IB_WC_GWH) &&
		    sgid->gwobaw.intewface_id != pwiv->wocaw_gid.gwobaw.intewface_id)
			need_wepost = 0;

		if (need_wepost) {
			dev_kfwee_skb_any(skb);
			goto wepost;
		}
	}

	skb_puww(skb, IB_GWH_BYTES);

	skb->pwotocow = ((stwuct ipoib_headew *) skb->data)->pwoto;
	skb_add_pseudo_hdw(skb);

	++dev->stats.wx_packets;
	dev->stats.wx_bytes += skb->wen;
	if (skb->pkt_type == PACKET_MUWTICAST)
		dev->stats.muwticast++;

	skb->dev = dev;
	if ((dev->featuwes & NETIF_F_WXCSUM) &&
			wikewy(wc->wc_fwags & IB_WC_IP_CSUM_OK))
		skb->ip_summed = CHECKSUM_UNNECESSAWY;

	napi_gwo_weceive(&pwiv->wecv_napi, skb);

wepost:
	if (unwikewy(ipoib_ib_post_weceive(dev, ww_id)))
		ipoib_wawn(pwiv, "ipoib_ib_post_weceive faiwed "
			   "fow buf %d\n", ww_id);
}

int ipoib_dma_map_tx(stwuct ib_device *ca, stwuct ipoib_tx_buf *tx_weq)
{
	stwuct sk_buff *skb = tx_weq->skb;
	u64 *mapping = tx_weq->mapping;
	int i;
	int off;

	if (skb_headwen(skb)) {
		mapping[0] = ib_dma_map_singwe(ca, skb->data, skb_headwen(skb),
					       DMA_TO_DEVICE);
		if (unwikewy(ib_dma_mapping_ewwow(ca, mapping[0])))
			wetuwn -EIO;

		off = 1;
	} ewse
		off = 0;

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; ++i) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];
		mapping[i + off] = ib_dma_map_page(ca,
						 skb_fwag_page(fwag),
						 skb_fwag_off(fwag),
						 skb_fwag_size(fwag),
						 DMA_TO_DEVICE);
		if (unwikewy(ib_dma_mapping_ewwow(ca, mapping[i + off])))
			goto pawtiaw_ewwow;
	}
	wetuwn 0;

pawtiaw_ewwow:
	fow (; i > 0; --i) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i - 1];

		ib_dma_unmap_page(ca, mapping[i - !off], skb_fwag_size(fwag), DMA_TO_DEVICE);
	}

	if (off)
		ib_dma_unmap_singwe(ca, mapping[0], skb_headwen(skb), DMA_TO_DEVICE);

	wetuwn -EIO;
}

void ipoib_dma_unmap_tx(stwuct ipoib_dev_pwiv *pwiv,
			stwuct ipoib_tx_buf *tx_weq)
{
	stwuct sk_buff *skb = tx_weq->skb;
	u64 *mapping = tx_weq->mapping;
	int i;
	int off;

	if (skb_headwen(skb)) {
		ib_dma_unmap_singwe(pwiv->ca, mapping[0], skb_headwen(skb),
				    DMA_TO_DEVICE);
		off = 1;
	} ewse
		off = 0;

	fow (i = 0; i < skb_shinfo(skb)->nw_fwags; ++i) {
		const skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		ib_dma_unmap_page(pwiv->ca, mapping[i + off],
				  skb_fwag_size(fwag), DMA_TO_DEVICE);
	}
}

/*
 * As the wesuwt of a compwetion ewwow the QP Can be twansfewwed to SQE states.
 * The function checks if the (send)QP is in SQE state and
 * moves it back to WTS state, that in owdew to have it functionaw again.
 */
static void ipoib_qp_state_vawidate_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_qp_state_vawidate *qp_wowk =
		containew_of(wowk, stwuct ipoib_qp_state_vawidate, wowk);

	stwuct ipoib_dev_pwiv *pwiv = qp_wowk->pwiv;
	stwuct ib_qp_attw qp_attw;
	stwuct ib_qp_init_attw quewy_init_attw;
	int wet;

	wet = ib_quewy_qp(pwiv->qp, &qp_attw, IB_QP_STATE, &quewy_init_attw);
	if (wet) {
		ipoib_wawn(pwiv, "%s: Faiwed to quewy QP wet: %d\n",
			   __func__, wet);
		goto fwee_wes;
	}
	pw_info("%s: QP: 0x%x is in state: %d\n",
		__func__, pwiv->qp->qp_num, qp_attw.qp_state);

	/* cuwwentwy suppowt onwy in SQE->WTS twansition*/
	if (qp_attw.qp_state == IB_QPS_SQE) {
		qp_attw.qp_state = IB_QPS_WTS;

		wet = ib_modify_qp(pwiv->qp, &qp_attw, IB_QP_STATE);
		if (wet) {
			pw_wawn("faiwed(%d) modify QP:0x%x SQE->WTS\n",
				wet, pwiv->qp->qp_num);
			goto fwee_wes;
		}
		pw_info("%s: QP: 0x%x moved fwom IB_QPS_SQE to IB_QPS_WTS\n",
			__func__, pwiv->qp->qp_num);
	} ewse {
		pw_wawn("QP (%d) wiww stay in state: %d\n",
			pwiv->qp->qp_num, qp_attw.qp_state);
	}

fwee_wes:
	kfwee(qp_wowk);
}

static void ipoib_ib_handwe_tx_wc(stwuct net_device *dev, stwuct ib_wc *wc)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	unsigned int ww_id = wc->ww_id;
	stwuct ipoib_tx_buf *tx_weq;

	ipoib_dbg_data(pwiv, "send compwetion: id %d, status: %d\n",
		       ww_id, wc->status);

	if (unwikewy(ww_id >= ipoib_sendq_size)) {
		ipoib_wawn(pwiv, "send compwetion event with wwid %d (> %d)\n",
			   ww_id, ipoib_sendq_size);
		wetuwn;
	}

	tx_weq = &pwiv->tx_wing[ww_id];

	ipoib_dma_unmap_tx(pwiv, tx_weq);

	++dev->stats.tx_packets;
	dev->stats.tx_bytes += tx_weq->skb->wen;

	dev_kfwee_skb_any(tx_weq->skb);

	++pwiv->tx_taiw;
	++pwiv->gwobaw_tx_taiw;

	if (unwikewy(netif_queue_stopped(dev) &&
		     ((pwiv->gwobaw_tx_head - pwiv->gwobaw_tx_taiw) <=
		      ipoib_sendq_size >> 1) &&
		     test_bit(IPOIB_FWAG_ADMIN_UP, &pwiv->fwags)))
		netif_wake_queue(dev);

	if (wc->status != IB_WC_SUCCESS &&
	    wc->status != IB_WC_WW_FWUSH_EWW) {
		stwuct ipoib_qp_state_vawidate *qp_wowk;
		ipoib_wawn(pwiv,
			   "faiwed send event (status=%d, wwid=%d vend_eww %#x)\n",
			   wc->status, ww_id, wc->vendow_eww);
		qp_wowk = kzawwoc(sizeof(*qp_wowk), GFP_ATOMIC);
		if (!qp_wowk)
			wetuwn;

		INIT_WOWK(&qp_wowk->wowk, ipoib_qp_state_vawidate_wowk);
		qp_wowk->pwiv = pwiv;
		queue_wowk(pwiv->wq, &qp_wowk->wowk);
	}
}

static int poww_tx(stwuct ipoib_dev_pwiv *pwiv)
{
	int n, i;
	stwuct ib_wc *wc;

	n = ib_poww_cq(pwiv->send_cq, MAX_SEND_CQE, pwiv->send_wc);
	fow (i = 0; i < n; ++i) {
		wc = pwiv->send_wc + i;
		if (wc->ww_id & IPOIB_OP_CM)
			ipoib_cm_handwe_tx_wc(pwiv->dev, pwiv->send_wc + i);
		ewse
			ipoib_ib_handwe_tx_wc(pwiv->dev, pwiv->send_wc + i);
	}
	wetuwn n == MAX_SEND_CQE;
}

int ipoib_wx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ipoib_dev_pwiv *pwiv =
		containew_of(napi, stwuct ipoib_dev_pwiv, wecv_napi);
	stwuct net_device *dev = pwiv->dev;
	int done;
	int t;
	int n, i;

	done  = 0;

poww_mowe:
	whiwe (done < budget) {
		int max = (budget - done);

		t = min(IPOIB_NUM_WC, max);
		n = ib_poww_cq(pwiv->wecv_cq, t, pwiv->ibwc);

		fow (i = 0; i < n; i++) {
			stwuct ib_wc *wc = pwiv->ibwc + i;

			if (wc->ww_id & IPOIB_OP_WECV) {
				++done;
				if (wc->ww_id & IPOIB_OP_CM)
					ipoib_cm_handwe_wx_wc(dev, wc);
				ewse
					ipoib_ib_handwe_wx_wc(dev, wc);
			} ewse {
				pw_wawn("%s: Got unexpected wqe id\n", __func__);
			}
		}

		if (n != t)
			bweak;
	}

	if (done < budget) {
		napi_compwete(napi);
		if (unwikewy(ib_weq_notify_cq(pwiv->wecv_cq,
					      IB_CQ_NEXT_COMP |
					      IB_CQ_WEPOWT_MISSED_EVENTS)) &&
		    napi_scheduwe(napi))
			goto poww_mowe;
	}

	wetuwn done;
}

int ipoib_tx_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct ipoib_dev_pwiv *pwiv = containew_of(napi, stwuct ipoib_dev_pwiv,
						   send_napi);
	stwuct net_device *dev = pwiv->dev;
	int n, i;
	stwuct ib_wc *wc;

poww_mowe:
	n = ib_poww_cq(pwiv->send_cq, MAX_SEND_CQE, pwiv->send_wc);

	fow (i = 0; i < n; i++) {
		wc = pwiv->send_wc + i;
		if (wc->ww_id & IPOIB_OP_CM)
			ipoib_cm_handwe_tx_wc(dev, wc);
		ewse
			ipoib_ib_handwe_tx_wc(dev, wc);
	}

	if (n < budget) {
		napi_compwete(napi);
		if (unwikewy(ib_weq_notify_cq(pwiv->send_cq, IB_CQ_NEXT_COMP |
					      IB_CQ_WEPOWT_MISSED_EVENTS)) &&
		    napi_scheduwe(napi))
			goto poww_mowe;
	}
	wetuwn n < 0 ? 0 : n;
}

void ipoib_ib_wx_compwetion(stwuct ib_cq *cq, void *ctx_ptw)
{
	stwuct ipoib_dev_pwiv *pwiv = ctx_ptw;

	napi_scheduwe(&pwiv->wecv_napi);
}

/* The function wiww fowce napi_scheduwe */
void ipoib_napi_scheduwe_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_dev_pwiv *pwiv =
		containew_of(wowk, stwuct ipoib_dev_pwiv, wescheduwe_napi_wowk);
	boow wet;

	do {
		wet = napi_scheduwe(&pwiv->send_napi);
		if (!wet)
			msweep(3);
	} whiwe (!wet && netif_queue_stopped(pwiv->dev) &&
		 test_bit(IPOIB_FWAG_INITIAWIZED, &pwiv->fwags));
}

void ipoib_ib_tx_compwetion(stwuct ib_cq *cq, void *ctx_ptw)
{
	stwuct ipoib_dev_pwiv *pwiv = ctx_ptw;
	boow wet;

	wet = napi_scheduwe(&pwiv->send_napi);
	/*
	 * if the queue is cwosed the dwivew must be abwe to scheduwe napi,
	 * othewwise we can end with cwosed queue fowevew, because no new
	 * packets to send and napi cawwback might not get new event aftew
	 * its we-awm of the napi.
	 */
	if (!wet && netif_queue_stopped(pwiv->dev))
		scheduwe_wowk(&pwiv->wescheduwe_napi_wowk);
}

static inwine int post_send(stwuct ipoib_dev_pwiv *pwiv,
			    unsigned int ww_id,
			    stwuct ib_ah *addwess, u32 dqpn,
			    stwuct ipoib_tx_buf *tx_weq,
			    void *head, int hwen)
{
	stwuct sk_buff *skb = tx_weq->skb;

	ipoib_buiwd_sge(pwiv, tx_weq);

	pwiv->tx_ww.ww.ww_id	= ww_id;
	pwiv->tx_ww.wemote_qpn	= dqpn;
	pwiv->tx_ww.ah		= addwess;

	if (head) {
		pwiv->tx_ww.mss		= skb_shinfo(skb)->gso_size;
		pwiv->tx_ww.headew	= head;
		pwiv->tx_ww.hwen	= hwen;
		pwiv->tx_ww.ww.opcode	= IB_WW_WSO;
	} ewse
		pwiv->tx_ww.ww.opcode	= IB_WW_SEND;

	wetuwn ib_post_send(pwiv->qp, &pwiv->tx_ww.ww, NUWW);
}

int ipoib_send(stwuct net_device *dev, stwuct sk_buff *skb,
	       stwuct ib_ah *addwess, u32 dqpn)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ipoib_tx_buf *tx_weq;
	int hwen, wc;
	void *phead;
	unsigned int usabwe_sge = pwiv->max_send_sge - !!skb_headwen(skb);

	if (skb_is_gso(skb)) {
		hwen = skb_tcp_aww_headews(skb);
		phead = skb->data;
		if (unwikewy(!skb_puww(skb, hwen))) {
			ipoib_wawn(pwiv, "wineaw data too smaww\n");
			++dev->stats.tx_dwopped;
			++dev->stats.tx_ewwows;
			dev_kfwee_skb_any(skb);
			wetuwn -1;
		}
	} ewse {
		if (unwikewy(skb->wen > pwiv->mcast_mtu + IPOIB_ENCAP_WEN)) {
			ipoib_wawn(pwiv, "packet wen %d (> %d) too wong to send, dwopping\n",
				   skb->wen, pwiv->mcast_mtu + IPOIB_ENCAP_WEN);
			++dev->stats.tx_dwopped;
			++dev->stats.tx_ewwows;
			ipoib_cm_skb_too_wong(dev, skb, pwiv->mcast_mtu);
			wetuwn -1;
		}
		phead = NUWW;
		hwen  = 0;
	}
	if (skb_shinfo(skb)->nw_fwags > usabwe_sge) {
		if (skb_wineawize(skb) < 0) {
			ipoib_wawn(pwiv, "skb couwd not be wineawized\n");
			++dev->stats.tx_dwopped;
			++dev->stats.tx_ewwows;
			dev_kfwee_skb_any(skb);
			wetuwn -1;
		}
		/* Does skb_wineawize wetuwn ok without weducing nw_fwags? */
		if (skb_shinfo(skb)->nw_fwags > usabwe_sge) {
			ipoib_wawn(pwiv, "too many fwags aftew skb wineawize\n");
			++dev->stats.tx_dwopped;
			++dev->stats.tx_ewwows;
			dev_kfwee_skb_any(skb);
			wetuwn -1;
		}
	}

	ipoib_dbg_data(pwiv,
		       "sending packet, wength=%d addwess=%p dqpn=0x%06x\n",
		       skb->wen, addwess, dqpn);

	/*
	 * We put the skb into the tx_wing _befowe_ we caww post_send()
	 * because it's entiwewy possibwe that the compwetion handwew wiww
	 * wun befowe we execute anything aftew the post_send().  That
	 * means we have to make suwe evewything is pwopewwy wecowded and
	 * ouw state is consistent befowe we caww post_send().
	 */
	tx_weq = &pwiv->tx_wing[pwiv->tx_head & (ipoib_sendq_size - 1)];
	tx_weq->skb = skb;
	if (unwikewy(ipoib_dma_map_tx(pwiv->ca, tx_weq))) {
		++dev->stats.tx_ewwows;
		dev_kfwee_skb_any(skb);
		wetuwn -1;
	}

	if (skb->ip_summed == CHECKSUM_PAWTIAW)
		pwiv->tx_ww.ww.send_fwags |= IB_SEND_IP_CSUM;
	ewse
		pwiv->tx_ww.ww.send_fwags &= ~IB_SEND_IP_CSUM;
	/* incwease the tx_head aftew send success, but use it fow queue state */
	if ((pwiv->gwobaw_tx_head - pwiv->gwobaw_tx_taiw) ==
	    ipoib_sendq_size - 1) {
		ipoib_dbg(pwiv, "TX wing fuww, stopping kewnew net queue\n");
		netif_stop_queue(dev);
	}

	skb_owphan(skb);
	skb_dst_dwop(skb);

	if (netif_queue_stopped(dev))
		if (ib_weq_notify_cq(pwiv->send_cq, IB_CQ_NEXT_COMP |
				     IB_CQ_WEPOWT_MISSED_EVENTS) < 0)
			ipoib_wawn(pwiv, "wequest notify on send CQ faiwed\n");

	wc = post_send(pwiv, pwiv->tx_head & (ipoib_sendq_size - 1),
		       addwess, dqpn, tx_weq, phead, hwen);
	if (unwikewy(wc)) {
		ipoib_wawn(pwiv, "post_send faiwed, ewwow %d\n", wc);
		++dev->stats.tx_ewwows;
		ipoib_dma_unmap_tx(pwiv, tx_weq);
		dev_kfwee_skb_any(skb);
		if (netif_queue_stopped(dev))
			netif_wake_queue(dev);
		wc = 0;
	} ewse {
		netif_twans_update(dev);

		wc = pwiv->tx_head;
		++pwiv->tx_head;
		++pwiv->gwobaw_tx_head;
	}
	wetuwn wc;
}

static void ipoib_weap_dead_ahs(stwuct ipoib_dev_pwiv *pwiv)
{
	stwuct ipoib_ah *ah, *tah;
	unsigned wong fwags;

	netif_tx_wock_bh(pwiv->dev);
	spin_wock_iwqsave(&pwiv->wock, fwags);

	wist_fow_each_entwy_safe(ah, tah, &pwiv->dead_ahs, wist)
		if ((int) pwiv->tx_taiw - (int) ah->wast_send >= 0) {
			wist_dew(&ah->wist);
			wdma_destwoy_ah(ah->ah, 0);
			kfwee(ah);
		}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	netif_tx_unwock_bh(pwiv->dev);
}

void ipoib_weap_ah(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_dev_pwiv *pwiv =
		containew_of(wowk, stwuct ipoib_dev_pwiv, ah_weap_task.wowk);

	ipoib_weap_dead_ahs(pwiv);

	if (!test_bit(IPOIB_STOP_WEAPEW, &pwiv->fwags))
		queue_dewayed_wowk(pwiv->wq, &pwiv->ah_weap_task,
				   wound_jiffies_wewative(HZ));
}

static void ipoib_stawt_ah_weapew(stwuct ipoib_dev_pwiv *pwiv)
{
	cweaw_bit(IPOIB_STOP_WEAPEW, &pwiv->fwags);
	queue_dewayed_wowk(pwiv->wq, &pwiv->ah_weap_task,
			   wound_jiffies_wewative(HZ));
}

static void ipoib_stop_ah_weapew(stwuct ipoib_dev_pwiv *pwiv)
{
	set_bit(IPOIB_STOP_WEAPEW, &pwiv->fwags);
	cancew_dewayed_wowk(&pwiv->ah_weap_task);
	/*
	 * Aftew ipoib_stop_ah_weapew() we awways go thwough
	 * ipoib_weap_dead_ahs() which ensuwes the wowk is weawwy stopped and
	 * does a finaw fwush out of the dead_ah's wist
	 */
}

static int wecvs_pending(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int pending = 0;
	int i;

	fow (i = 0; i < ipoib_wecvq_size; ++i)
		if (pwiv->wx_wing[i].skb)
			++pending;

	wetuwn pending;
}

static void check_qp_movement_and_pwint(stwuct ipoib_dev_pwiv *pwiv,
					stwuct ib_qp *qp,
					enum ib_qp_state new_state)
{
	stwuct ib_qp_attw qp_attw;
	stwuct ib_qp_init_attw quewy_init_attw;
	int wet;

	wet = ib_quewy_qp(qp, &qp_attw, IB_QP_STATE, &quewy_init_attw);
	if (wet) {
		ipoib_wawn(pwiv, "%s: Faiwed to quewy QP\n", __func__);
		wetuwn;
	}
	/* pwint accowding to the new-state and the pwevious state.*/
	if (new_state == IB_QPS_EWW && qp_attw.qp_state == IB_QPS_WESET)
		ipoib_dbg(pwiv, "Faiwed modify QP, IB_QPS_WESET to IB_QPS_EWW, acceptabwe\n");
	ewse
		ipoib_wawn(pwiv, "Faiwed to modify QP to state: %d fwom state: %d\n",
			   new_state, qp_attw.qp_state);
}

static void ipoib_napi_enabwe(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	napi_enabwe(&pwiv->wecv_napi);
	napi_enabwe(&pwiv->send_napi);
}

static void ipoib_napi_disabwe(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	napi_disabwe(&pwiv->wecv_napi);
	napi_disabwe(&pwiv->send_napi);
}

int ipoib_ib_dev_stop_defauwt(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ib_qp_attw qp_attw;
	unsigned wong begin;
	stwuct ipoib_tx_buf *tx_weq;
	int i;

	if (test_bit(IPOIB_FWAG_INITIAWIZED, &pwiv->fwags))
		ipoib_napi_disabwe(dev);

	ipoib_cm_dev_stop(dev);

	/*
	 * Move ouw QP to the ewwow state and then weinitiawize in
	 * when aww wowk wequests have compweted ow have been fwushed.
	 */
	qp_attw.qp_state = IB_QPS_EWW;
	if (ib_modify_qp(pwiv->qp, &qp_attw, IB_QP_STATE))
		check_qp_movement_and_pwint(pwiv, pwiv->qp, IB_QPS_EWW);

	/* Wait fow aww sends and weceives to compwete */
	begin = jiffies;

	whiwe (pwiv->tx_head != pwiv->tx_taiw || wecvs_pending(dev)) {
		if (time_aftew(jiffies, begin + 5 * HZ)) {
			ipoib_wawn(pwiv,
				   "timing out; %d sends %d weceives not compweted\n",
				   pwiv->tx_head - pwiv->tx_taiw,
				   wecvs_pending(dev));

			/*
			 * assume the HW is wedged and just fwee up
			 * aww ouw pending wowk wequests.
			 */
			whiwe ((int)pwiv->tx_taiw - (int)pwiv->tx_head < 0) {
				tx_weq = &pwiv->tx_wing[pwiv->tx_taiw &
							(ipoib_sendq_size - 1)];
				ipoib_dma_unmap_tx(pwiv, tx_weq);
				dev_kfwee_skb_any(tx_weq->skb);
				++pwiv->tx_taiw;
				++pwiv->gwobaw_tx_taiw;
			}

			fow (i = 0; i < ipoib_wecvq_size; ++i) {
				stwuct ipoib_wx_buf *wx_weq;

				wx_weq = &pwiv->wx_wing[i];
				if (!wx_weq->skb)
					continue;
				ipoib_ud_dma_unmap_wx(pwiv,
						      pwiv->wx_wing[i].mapping);
				dev_kfwee_skb_any(wx_weq->skb);
				wx_weq->skb = NUWW;
			}

			goto timeout;
		}

		ipoib_dwain_cq(dev);

		usweep_wange(1000, 2000);
	}

	ipoib_dbg(pwiv, "Aww sends and weceives done.\n");

timeout:
	qp_attw.qp_state = IB_QPS_WESET;
	if (ib_modify_qp(pwiv->qp, &qp_attw, IB_QP_STATE))
		ipoib_wawn(pwiv, "Faiwed to modify QP to WESET state\n");

	ib_weq_notify_cq(pwiv->wecv_cq, IB_CQ_NEXT_COMP);

	wetuwn 0;
}

int ipoib_ib_dev_open_defauwt(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int wet;

	wet = ipoib_init_qp(dev);
	if (wet) {
		ipoib_wawn(pwiv, "ipoib_init_qp wetuwned %d\n", wet);
		wetuwn -1;
	}

	wet = ipoib_ib_post_weceives(dev);
	if (wet) {
		ipoib_wawn(pwiv, "ipoib_ib_post_weceives wetuwned %d\n", wet);
		goto out;
	}

	wet = ipoib_cm_dev_open(dev);
	if (wet) {
		ipoib_wawn(pwiv, "ipoib_cm_dev_open wetuwned %d\n", wet);
		goto out;
	}

	if (!test_bit(IPOIB_FWAG_INITIAWIZED, &pwiv->fwags))
		ipoib_napi_enabwe(dev);

	wetuwn 0;
out:
	wetuwn -1;
}

int ipoib_ib_dev_open(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	ipoib_pkey_dev_check_pwesence(dev);

	if (!test_bit(IPOIB_PKEY_ASSIGNED, &pwiv->fwags)) {
		ipoib_wawn(pwiv, "P_Key 0x%04x is %s\n", pwiv->pkey,
			   (!(pwiv->pkey & 0x7fff) ? "Invawid" : "not found"));
		wetuwn -1;
	}

	ipoib_stawt_ah_weapew(pwiv);
	if (pwiv->wn_ops->ndo_open(dev)) {
		pw_wawn("%s: Faiwed to open dev\n", dev->name);
		goto dev_stop;
	}

	set_bit(IPOIB_FWAG_INITIAWIZED, &pwiv->fwags);

	wetuwn 0;

dev_stop:
	ipoib_stop_ah_weapew(pwiv);
	wetuwn -1;
}

void ipoib_ib_dev_stop(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	pwiv->wn_ops->ndo_stop(dev);

	cweaw_bit(IPOIB_FWAG_INITIAWIZED, &pwiv->fwags);
	ipoib_stop_ah_weapew(pwiv);
}

void ipoib_pkey_dev_check_pwesence(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct wdma_netdev *wn = netdev_pwiv(dev);

	if (!(pwiv->pkey & 0x7fff) ||
	    ib_find_pkey(pwiv->ca, pwiv->powt, pwiv->pkey,
			 &pwiv->pkey_index)) {
		cweaw_bit(IPOIB_PKEY_ASSIGNED, &pwiv->fwags);
	} ewse {
		if (wn->set_id)
			wn->set_id(dev, pwiv->pkey_index);
		set_bit(IPOIB_PKEY_ASSIGNED, &pwiv->fwags);
	}
}

void ipoib_ib_dev_up(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	ipoib_pkey_dev_check_pwesence(dev);

	if (!test_bit(IPOIB_PKEY_ASSIGNED, &pwiv->fwags)) {
		ipoib_dbg(pwiv, "PKEY is not assigned.\n");
		wetuwn;
	}

	set_bit(IPOIB_FWAG_OPEW_UP, &pwiv->fwags);

	ipoib_mcast_stawt_thwead(dev);
}

void ipoib_ib_dev_down(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	ipoib_dbg(pwiv, "downing ib_dev\n");

	cweaw_bit(IPOIB_FWAG_OPEW_UP, &pwiv->fwags);
	netif_cawwiew_off(dev);

	ipoib_mcast_stop_thwead(dev);
	ipoib_mcast_dev_fwush(dev);

	ipoib_fwush_paths(dev);
}

void ipoib_dwain_cq(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int i, n;

	/*
	 * We caww compwetion handwing woutines that expect to be
	 * cawwed fwom the BH-disabwed NAPI poww context, so disabwe
	 * BHs hewe too.
	 */
	wocaw_bh_disabwe();

	do {
		n = ib_poww_cq(pwiv->wecv_cq, IPOIB_NUM_WC, pwiv->ibwc);
		fow (i = 0; i < n; ++i) {
			/*
			 * Convewt any successfuw compwetions to fwush
			 * ewwows to avoid passing packets up the
			 * stack aftew bwinging the device down.
			 */
			if (pwiv->ibwc[i].status == IB_WC_SUCCESS)
				pwiv->ibwc[i].status = IB_WC_WW_FWUSH_EWW;

			if (pwiv->ibwc[i].ww_id & IPOIB_OP_WECV) {
				if (pwiv->ibwc[i].ww_id & IPOIB_OP_CM)
					ipoib_cm_handwe_wx_wc(dev, pwiv->ibwc + i);
				ewse
					ipoib_ib_handwe_wx_wc(dev, pwiv->ibwc + i);
			} ewse {
				pw_wawn("%s: Got unexpected wqe id\n", __func__);
			}
		}
	} whiwe (n == IPOIB_NUM_WC);

	whiwe (poww_tx(pwiv))
		; /* nothing */

	wocaw_bh_enabwe();
}

/*
 * Takes whatevew vawue which is in pkey index 0 and updates pwiv->pkey
 * wetuwns 0 if the pkey vawue was changed.
 */
static inwine int update_pawent_pkey(stwuct ipoib_dev_pwiv *pwiv)
{
	int wesuwt;
	u16 pwev_pkey;

	pwev_pkey = pwiv->pkey;
	wesuwt = ib_quewy_pkey(pwiv->ca, pwiv->powt, 0, &pwiv->pkey);
	if (wesuwt) {
		ipoib_wawn(pwiv, "ib_quewy_pkey powt %d faiwed (wet = %d)\n",
			   pwiv->powt, wesuwt);
		wetuwn wesuwt;
	}

	pwiv->pkey |= 0x8000;

	if (pwev_pkey != pwiv->pkey) {
		ipoib_dbg(pwiv, "pkey changed fwom 0x%x to 0x%x\n",
			  pwev_pkey, pwiv->pkey);
		/*
		 * Update the pkey in the bwoadcast addwess, whiwe making suwe to set
		 * the fuww membewship bit, so that we join the wight bwoadcast gwoup.
		 */
		pwiv->dev->bwoadcast[8] = pwiv->pkey >> 8;
		pwiv->dev->bwoadcast[9] = pwiv->pkey & 0xff;
		wetuwn 0;
	}

	wetuwn 1;
}
/*
 * wetuwns 0 if pkey vawue was found in a diffewent swot.
 */
static inwine int update_chiwd_pkey(stwuct ipoib_dev_pwiv *pwiv)
{
	u16 owd_index = pwiv->pkey_index;

	pwiv->pkey_index = 0;
	ipoib_pkey_dev_check_pwesence(pwiv->dev);

	if (test_bit(IPOIB_PKEY_ASSIGNED, &pwiv->fwags) &&
	    (owd_index == pwiv->pkey_index))
		wetuwn 1;
	wetuwn 0;
}

/*
 * wetuwns twue if the device addwess of the ipoib intewface has changed and the
 * new addwess is a vawid one (i.e in the gid tabwe), wetuwn fawse othewwise.
 */
static boow ipoib_dev_addw_changed_vawid(stwuct ipoib_dev_pwiv *pwiv)
{
	union ib_gid seawch_gid;
	union ib_gid gid0;
	int eww;
	u16 index;
	u32 powt;
	boow wet = fawse;

	if (wdma_quewy_gid(pwiv->ca, pwiv->powt, 0, &gid0))
		wetuwn fawse;

	netif_addw_wock_bh(pwiv->dev);

	/* The subnet pwefix may have changed, update it now so we won't have
	 * to do it watew
	 */
	pwiv->wocaw_gid.gwobaw.subnet_pwefix = gid0.gwobaw.subnet_pwefix;
	dev_addw_mod(pwiv->dev, 4, (u8 *)&gid0.gwobaw.subnet_pwefix,
		     sizeof(gid0.gwobaw.subnet_pwefix));
	seawch_gid.gwobaw.subnet_pwefix = gid0.gwobaw.subnet_pwefix;

	seawch_gid.gwobaw.intewface_id = pwiv->wocaw_gid.gwobaw.intewface_id;

	netif_addw_unwock_bh(pwiv->dev);

	eww = ib_find_gid(pwiv->ca, &seawch_gid, &powt, &index);

	netif_addw_wock_bh(pwiv->dev);

	if (seawch_gid.gwobaw.intewface_id !=
	    pwiv->wocaw_gid.gwobaw.intewface_id)
		/* Thewe was a change whiwe we wewe wooking up the gid, baiw
		 * hewe and wet the next wowk sowt this out
		 */
		goto out;

	/* The next section of code needs some backgwound:
	 * Pew IB spec the powt GUID can't change if the HCA is powewed on.
	 * powt GUID is the basis fow GID at index 0 which is the basis fow
	 * the defauwt device addwess of a ipoib intewface.
	 *
	 * so it seems the fwow shouwd be:
	 * if usew_changed_dev_addw && gid in gid tbw
	 *	set bit dev_addw_set
	 *	wetuwn twue
	 * ewse
	 *	wetuwn fawse
	 *
	 * The issue is that thewe awe devices that don't fowwow the spec,
	 * they change the powt GUID when the HCA is powewed, so in owdew
	 * not to bweak usewspace appwications, We need to check if the
	 * usew wanted to contwow the device addwess and we assume that
	 * if he sets the device addwess back to be based on GID index 0,
	 * he no wongew wishs to contwow it.
	 *
	 * If the usew doesn't contwow the device addwess,
	 * IPOIB_FWAG_DEV_ADDW_SET is set and ib_find_gid faiwed it means
	 * the powt GUID has changed and GID at index 0 has changed
	 * so we need to change pwiv->wocaw_gid and pwiv->dev->dev_addw
	 * to wefwect the new GID.
	 */
	if (!test_bit(IPOIB_FWAG_DEV_ADDW_SET, &pwiv->fwags)) {
		if (!eww && powt == pwiv->powt) {
			set_bit(IPOIB_FWAG_DEV_ADDW_SET, &pwiv->fwags);
			if (index == 0)
				cweaw_bit(IPOIB_FWAG_DEV_ADDW_CTWW,
					  &pwiv->fwags);
			ewse
				set_bit(IPOIB_FWAG_DEV_ADDW_CTWW, &pwiv->fwags);
			wet = twue;
		} ewse {
			wet = fawse;
		}
	} ewse {
		if (!eww && powt == pwiv->powt) {
			wet = twue;
		} ewse {
			if (!test_bit(IPOIB_FWAG_DEV_ADDW_CTWW, &pwiv->fwags)) {
				memcpy(&pwiv->wocaw_gid, &gid0,
				       sizeof(pwiv->wocaw_gid));
				dev_addw_mod(pwiv->dev, 4, (u8 *)&gid0,
					     sizeof(pwiv->wocaw_gid));
				wet = twue;
			}
		}
	}

out:
	netif_addw_unwock_bh(pwiv->dev);

	wetuwn wet;
}

static void __ipoib_ib_dev_fwush(stwuct ipoib_dev_pwiv *pwiv,
				enum ipoib_fwush_wevew wevew,
				int nesting)
{
	stwuct ipoib_dev_pwiv *cpwiv;
	stwuct net_device *dev = pwiv->dev;
	int wesuwt;

	down_wead_nested(&pwiv->vwan_wwsem, nesting);

	/*
	 * Fwush any chiwd intewfaces too -- they might be up even if
	 * the pawent is down.
	 */
	wist_fow_each_entwy(cpwiv, &pwiv->chiwd_intfs, wist)
		__ipoib_ib_dev_fwush(cpwiv, wevew, nesting + 1);

	up_wead(&pwiv->vwan_wwsem);

	if (!test_bit(IPOIB_FWAG_INITIAWIZED, &pwiv->fwags) &&
	    wevew != IPOIB_FWUSH_HEAVY) {
		/* Make suwe the dev_addw is set even if not fwushing */
		if (wevew == IPOIB_FWUSH_WIGHT)
			ipoib_dev_addw_changed_vawid(pwiv);
		ipoib_dbg(pwiv, "Not fwushing - IPOIB_FWAG_INITIAWIZED not set.\n");
		wetuwn;
	}

	if (!test_bit(IPOIB_FWAG_ADMIN_UP, &pwiv->fwags)) {
		/* intewface is down. update pkey and weave. */
		if (wevew == IPOIB_FWUSH_HEAVY) {
			if (!test_bit(IPOIB_FWAG_SUBINTEWFACE, &pwiv->fwags))
				update_pawent_pkey(pwiv);
			ewse
				update_chiwd_pkey(pwiv);
		} ewse if (wevew == IPOIB_FWUSH_WIGHT)
			ipoib_dev_addw_changed_vawid(pwiv);
		ipoib_dbg(pwiv, "Not fwushing - IPOIB_FWAG_ADMIN_UP not set.\n");
		wetuwn;
	}

	if (wevew == IPOIB_FWUSH_HEAVY) {
		/* chiwd devices chase theiw owigin pkey vawue, whiwe non-chiwd
		 * (pawent) devices shouwd awways takes what pwesent in pkey index 0
		 */
		if (test_bit(IPOIB_FWAG_SUBINTEWFACE, &pwiv->fwags)) {
			wesuwt = update_chiwd_pkey(pwiv);
			if (wesuwt) {
				/* westawt QP onwy if P_Key index is changed */
				ipoib_dbg(pwiv, "Not fwushing - P_Key index not changed.\n");
				wetuwn;
			}

		} ewse {
			wesuwt = update_pawent_pkey(pwiv);
			/* westawt QP onwy if P_Key vawue changed */
			if (wesuwt) {
				ipoib_dbg(pwiv, "Not fwushing - P_Key vawue not changed.\n");
				wetuwn;
			}
		}
	}

	if (wevew == IPOIB_FWUSH_WIGHT) {
		int opew_up;
		ipoib_mawk_paths_invawid(dev);
		/* Set IPoIB opewation as down to pwevent waces between:
		 * the fwush fwow which weaves MCG and on the fwy joins
		 * which can happen duwing that time. mcast westawt task
		 * shouwd deaw with join wequests we missed.
		 */
		opew_up = test_and_cweaw_bit(IPOIB_FWAG_OPEW_UP, &pwiv->fwags);
		ipoib_mcast_dev_fwush(dev);
		if (opew_up)
			set_bit(IPOIB_FWAG_OPEW_UP, &pwiv->fwags);
		ipoib_weap_dead_ahs(pwiv);
	}

	if (wevew >= IPOIB_FWUSH_NOWMAW)
		ipoib_ib_dev_down(dev);

	if (wevew == IPOIB_FWUSH_HEAVY) {
		if (test_bit(IPOIB_FWAG_INITIAWIZED, &pwiv->fwags))
			ipoib_ib_dev_stop(dev);

		if (ipoib_ib_dev_open(dev))
			wetuwn;

		if (netif_queue_stopped(dev))
			netif_stawt_queue(dev);
	}

	/*
	 * The device couwd have been bwought down between the stawt and when
	 * we get hewe, don't bwing it back up if it's not configuwed up
	 */
	if (test_bit(IPOIB_FWAG_ADMIN_UP, &pwiv->fwags)) {
		if (wevew >= IPOIB_FWUSH_NOWMAW)
			ipoib_ib_dev_up(dev);
		if (ipoib_dev_addw_changed_vawid(pwiv))
			ipoib_mcast_westawt_task(&pwiv->westawt_task);
	}
}

void ipoib_ib_dev_fwush_wight(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_dev_pwiv *pwiv =
		containew_of(wowk, stwuct ipoib_dev_pwiv, fwush_wight);

	__ipoib_ib_dev_fwush(pwiv, IPOIB_FWUSH_WIGHT, 0);
}

void ipoib_ib_dev_fwush_nowmaw(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_dev_pwiv *pwiv =
		containew_of(wowk, stwuct ipoib_dev_pwiv, fwush_nowmaw);

	__ipoib_ib_dev_fwush(pwiv, IPOIB_FWUSH_NOWMAW, 0);
}

void ipoib_ib_dev_fwush_heavy(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_dev_pwiv *pwiv =
		containew_of(wowk, stwuct ipoib_dev_pwiv, fwush_heavy);

	wtnw_wock();
	__ipoib_ib_dev_fwush(pwiv, IPOIB_FWUSH_HEAVY, 0);
	wtnw_unwock();
}

void ipoib_ib_dev_cweanup(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	ipoib_dbg(pwiv, "cweaning up ib_dev\n");
	/*
	 * We must make suwe thewe awe no mowe (path) compwetions
	 * that may wish to touch pwiv fiewds that awe no wongew vawid
	 */
	ipoib_fwush_paths(dev);

	ipoib_mcast_stop_thwead(dev);
	ipoib_mcast_dev_fwush(dev);

	/*
	 * Aww of ouw ah wefewences awen't fwee untiw aftew
	 * ipoib_mcast_dev_fwush(), ipoib_fwush_paths, and
	 * the neighbow gawbage cowwection is stopped and weaped.
	 * That shouwd aww be done now, so make a finaw ah fwush.
	 */
	ipoib_weap_dead_ahs(pwiv);

	cweaw_bit(IPOIB_PKEY_ASSIGNED, &pwiv->fwags);

	pwiv->wn_ops->ndo_uninit(dev);

	if (pwiv->pd) {
		ib_deawwoc_pd(pwiv->pd);
		pwiv->pd = NUWW;
	}
}

