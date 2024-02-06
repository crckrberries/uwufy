/*
 * Copywight (c) 2006 Mewwanox Technowogies. Aww wights wesewved
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

#incwude <wdma/ib_cm.h>
#incwude <net/dst.h>
#incwude <net/icmp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>

#incwude "ipoib.h"

int ipoib_max_conn_qp = 128;

moduwe_pawam_named(max_nonswq_conn_qp, ipoib_max_conn_qp, int, 0444);
MODUWE_PAWM_DESC(max_nonswq_conn_qp,
		 "Max numbew of connected-mode QPs pew intewface "
		 "(appwied onwy if shawed weceive queue is not avaiwabwe)");

#ifdef CONFIG_INFINIBAND_IPOIB_DEBUG_DATA
static int data_debug_wevew;

moduwe_pawam_named(cm_data_debug_wevew, data_debug_wevew, int, 0644);
MODUWE_PAWM_DESC(cm_data_debug_wevew,
		 "Enabwe data path debug twacing fow connected mode if > 0");
#endif

#define IPOIB_CM_IETF_ID 0x1000000000000000UWW

#define IPOIB_CM_WX_UPDATE_TIME (256 * HZ)
#define IPOIB_CM_WX_TIMEOUT     (2 * 256 * HZ)
#define IPOIB_CM_WX_DEWAY       (3 * 256 * HZ)
#define IPOIB_CM_WX_UPDATE_MASK (0x3)

#define IPOIB_CM_WX_WESEWVE     (AWIGN(IPOIB_HAWD_WEN, 16) - IPOIB_ENCAP_WEN)

static stwuct ib_qp_attw ipoib_cm_eww_attw = {
	.qp_state = IB_QPS_EWW
};

#define IPOIB_CM_WX_DWAIN_WWID 0xffffffff

static stwuct ib_send_ww ipoib_cm_wx_dwain_ww = {
	.opcode = IB_WW_SEND,
};

static int ipoib_cm_tx_handwew(stwuct ib_cm_id *cm_id,
			       const stwuct ib_cm_event *event);

static void ipoib_cm_dma_unmap_wx(stwuct ipoib_dev_pwiv *pwiv, int fwags,
				  u64 mapping[IPOIB_CM_WX_SG])
{
	int i;

	ib_dma_unmap_singwe(pwiv->ca, mapping[0], IPOIB_CM_HEAD_SIZE, DMA_FWOM_DEVICE);

	fow (i = 0; i < fwags; ++i)
		ib_dma_unmap_page(pwiv->ca, mapping[i + 1], PAGE_SIZE, DMA_FWOM_DEVICE);
}

static int ipoib_cm_post_weceive_swq(stwuct net_device *dev, int id)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int i, wet;

	pwiv->cm.wx_ww.ww_id = id | IPOIB_OP_CM | IPOIB_OP_WECV;

	fow (i = 0; i < pwiv->cm.num_fwags; ++i)
		pwiv->cm.wx_sge[i].addw = pwiv->cm.swq_wing[id].mapping[i];

	wet = ib_post_swq_wecv(pwiv->cm.swq, &pwiv->cm.wx_ww, NUWW);
	if (unwikewy(wet)) {
		ipoib_wawn(pwiv, "post swq faiwed fow buf %d (%d)\n", id, wet);
		ipoib_cm_dma_unmap_wx(pwiv, pwiv->cm.num_fwags - 1,
				      pwiv->cm.swq_wing[id].mapping);
		dev_kfwee_skb_any(pwiv->cm.swq_wing[id].skb);
		pwiv->cm.swq_wing[id].skb = NUWW;
	}

	wetuwn wet;
}

static int ipoib_cm_post_weceive_nonswq(stwuct net_device *dev,
					stwuct ipoib_cm_wx *wx,
					stwuct ib_wecv_ww *ww,
					stwuct ib_sge *sge, int id)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int i, wet;

	ww->ww_id = id | IPOIB_OP_CM | IPOIB_OP_WECV;

	fow (i = 0; i < IPOIB_CM_WX_SG; ++i)
		sge[i].addw = wx->wx_wing[id].mapping[i];

	wet = ib_post_wecv(wx->qp, ww, NUWW);
	if (unwikewy(wet)) {
		ipoib_wawn(pwiv, "post wecv faiwed fow buf %d (%d)\n", id, wet);
		ipoib_cm_dma_unmap_wx(pwiv, IPOIB_CM_WX_SG - 1,
				      wx->wx_wing[id].mapping);
		dev_kfwee_skb_any(wx->wx_wing[id].skb);
		wx->wx_wing[id].skb = NUWW;
	}

	wetuwn wet;
}

static stwuct sk_buff *ipoib_cm_awwoc_wx_skb(stwuct net_device *dev,
					     stwuct ipoib_cm_wx_buf *wx_wing,
					     int id, int fwags,
					     u64 mapping[IPOIB_CM_WX_SG],
					     gfp_t gfp)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct sk_buff *skb;
	int i;

	skb = dev_awwoc_skb(AWIGN(IPOIB_CM_HEAD_SIZE + IPOIB_PSEUDO_WEN, 16));
	if (unwikewy(!skb))
		wetuwn NUWW;

	/*
	 * IPoIB adds a IPOIB_ENCAP_WEN byte headew, this wiww awign the
	 * IP headew to a muwtipwe of 16.
	 */
	skb_wesewve(skb, IPOIB_CM_WX_WESEWVE);

	mapping[0] = ib_dma_map_singwe(pwiv->ca, skb->data, IPOIB_CM_HEAD_SIZE,
				       DMA_FWOM_DEVICE);
	if (unwikewy(ib_dma_mapping_ewwow(pwiv->ca, mapping[0]))) {
		dev_kfwee_skb_any(skb);
		wetuwn NUWW;
	}

	fow (i = 0; i < fwags; i++) {
		stwuct page *page = awwoc_page(gfp);

		if (!page)
			goto pawtiaw_ewwow;
		skb_fiww_page_desc(skb, i, page, 0, PAGE_SIZE);

		mapping[i + 1] = ib_dma_map_page(pwiv->ca, page,
						 0, PAGE_SIZE, DMA_FWOM_DEVICE);
		if (unwikewy(ib_dma_mapping_ewwow(pwiv->ca, mapping[i + 1])))
			goto pawtiaw_ewwow;
	}

	wx_wing[id].skb = skb;
	wetuwn skb;

pawtiaw_ewwow:

	ib_dma_unmap_singwe(pwiv->ca, mapping[0], IPOIB_CM_HEAD_SIZE, DMA_FWOM_DEVICE);

	fow (; i > 0; --i)
		ib_dma_unmap_page(pwiv->ca, mapping[i], PAGE_SIZE, DMA_FWOM_DEVICE);

	dev_kfwee_skb_any(skb);
	wetuwn NUWW;
}

static void ipoib_cm_fwee_wx_wing(stwuct net_device *dev,
				  stwuct ipoib_cm_wx_buf *wx_wing)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int i;

	fow (i = 0; i < ipoib_wecvq_size; ++i)
		if (wx_wing[i].skb) {
			ipoib_cm_dma_unmap_wx(pwiv, IPOIB_CM_WX_SG - 1,
					      wx_wing[i].mapping);
			dev_kfwee_skb_any(wx_wing[i].skb);
		}

	vfwee(wx_wing);
}

static void ipoib_cm_stawt_wx_dwain(stwuct ipoib_dev_pwiv *pwiv)
{
	stwuct ipoib_cm_wx *p;

	/* We onwy wesewved 1 extwa swot in CQ fow dwain WWs, so
	 * make suwe we have at most 1 outstanding WW. */
	if (wist_empty(&pwiv->cm.wx_fwush_wist) ||
	    !wist_empty(&pwiv->cm.wx_dwain_wist))
		wetuwn;

	/*
	 * QPs on fwush wist awe ewwow state.  This way, a "fwush
	 * ewwow" WC wiww be immediatewy genewated fow each WW we post.
	 */
	p = wist_entwy(pwiv->cm.wx_fwush_wist.next, typeof(*p), wist);
	ipoib_cm_wx_dwain_ww.ww_id = IPOIB_CM_WX_DWAIN_WWID;
	if (ib_post_send(p->qp, &ipoib_cm_wx_dwain_ww, NUWW))
		ipoib_wawn(pwiv, "faiwed to post dwain ww\n");

	wist_spwice_init(&pwiv->cm.wx_fwush_wist, &pwiv->cm.wx_dwain_wist);
}

static void ipoib_cm_wx_event_handwew(stwuct ib_event *event, void *ctx)
{
	stwuct ipoib_cm_wx *p = ctx;
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(p->dev);
	unsigned wong fwags;

	if (event->event != IB_EVENT_QP_WAST_WQE_WEACHED)
		wetuwn;

	spin_wock_iwqsave(&pwiv->wock, fwags);
	wist_move(&p->wist, &pwiv->cm.wx_fwush_wist);
	p->state = IPOIB_CM_WX_FWUSH;
	ipoib_cm_stawt_wx_dwain(pwiv);
	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
}

static stwuct ib_qp *ipoib_cm_cweate_wx_qp(stwuct net_device *dev,
					   stwuct ipoib_cm_wx *p)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ib_qp_init_attw attw = {
		.event_handwew = ipoib_cm_wx_event_handwew,
		.send_cq = pwiv->wecv_cq, /* Fow dwain WW */
		.wecv_cq = pwiv->wecv_cq,
		.swq = pwiv->cm.swq,
		.cap.max_send_ww = 1, /* Fow dwain WW */
		.cap.max_send_sge = 1, /* FIXME: 0 Seems not to wowk */
		.sq_sig_type = IB_SIGNAW_AWW_WW,
		.qp_type = IB_QPT_WC,
		.qp_context = p,
	};

	if (!ipoib_cm_has_swq(dev)) {
		attw.cap.max_wecv_ww  = ipoib_wecvq_size;
		attw.cap.max_wecv_sge = IPOIB_CM_WX_SG;
	}

	wetuwn ib_cweate_qp(pwiv->pd, &attw);
}

static int ipoib_cm_modify_wx_qp(stwuct net_device *dev,
				 stwuct ib_cm_id *cm_id, stwuct ib_qp *qp,
				 unsigned int psn)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ib_qp_attw qp_attw;
	int qp_attw_mask, wet;

	qp_attw.qp_state = IB_QPS_INIT;
	wet = ib_cm_init_qp_attw(cm_id, &qp_attw, &qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to init QP attw fow INIT: %d\n", wet);
		wetuwn wet;
	}
	wet = ib_modify_qp(qp, &qp_attw, qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to modify QP to INIT: %d\n", wet);
		wetuwn wet;
	}
	qp_attw.qp_state = IB_QPS_WTW;
	wet = ib_cm_init_qp_attw(cm_id, &qp_attw, &qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to init QP attw fow WTW: %d\n", wet);
		wetuwn wet;
	}
	qp_attw.wq_psn = psn;
	wet = ib_modify_qp(qp, &qp_attw, qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to modify QP to WTW: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Cuwwent Mewwanox HCA fiwmwawe won't genewate compwetions
	 * with ewwow fow dwain WWs unwess the QP has been moved to
	 * WTS fiwst. This wowk-awound weaves a window whewe a QP has
	 * moved to ewwow asynchwonouswy, but this wiww eventuawwy get
	 * fixed in fiwmwawe, so wet's not ewwow out if modify QP
	 * faiws.
	 */
	qp_attw.qp_state = IB_QPS_WTS;
	wet = ib_cm_init_qp_attw(cm_id, &qp_attw, &qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to init QP attw fow WTS: %d\n", wet);
		wetuwn 0;
	}
	wet = ib_modify_qp(qp, &qp_attw, qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to modify QP to WTS: %d\n", wet);
		wetuwn 0;
	}

	wetuwn 0;
}

static void ipoib_cm_init_wx_ww(stwuct net_device *dev,
				stwuct ib_wecv_ww *ww,
				stwuct ib_sge *sge)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int i;

	fow (i = 0; i < pwiv->cm.num_fwags; ++i)
		sge[i].wkey = pwiv->pd->wocaw_dma_wkey;

	sge[0].wength = IPOIB_CM_HEAD_SIZE;
	fow (i = 1; i < pwiv->cm.num_fwags; ++i)
		sge[i].wength = PAGE_SIZE;

	ww->next    = NUWW;
	ww->sg_wist = sge;
	ww->num_sge = pwiv->cm.num_fwags;
}

static int ipoib_cm_nonswq_init_wx(stwuct net_device *dev, stwuct ib_cm_id *cm_id,
				   stwuct ipoib_cm_wx *wx)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct {
		stwuct ib_wecv_ww ww;
		stwuct ib_sge sge[IPOIB_CM_WX_SG];
	} *t;
	int wet;
	int i;

	wx->wx_wing = vzawwoc(awway_size(ipoib_wecvq_size,
					 sizeof(*wx->wx_wing)));
	if (!wx->wx_wing)
		wetuwn -ENOMEM;

	t = kmawwoc(sizeof(*t), GFP_KEWNEW);
	if (!t) {
		wet = -ENOMEM;
		goto eww_fwee_1;
	}

	ipoib_cm_init_wx_ww(dev, &t->ww, t->sge);

	spin_wock_iwq(&pwiv->wock);

	if (pwiv->cm.nonswq_conn_qp >= ipoib_max_conn_qp) {
		spin_unwock_iwq(&pwiv->wock);
		ib_send_cm_wej(cm_id, IB_CM_WEJ_NO_QP, NUWW, 0, NUWW, 0);
		wet = -EINVAW;
		goto eww_fwee;
	} ewse
		++pwiv->cm.nonswq_conn_qp;

	spin_unwock_iwq(&pwiv->wock);

	fow (i = 0; i < ipoib_wecvq_size; ++i) {
		if (!ipoib_cm_awwoc_wx_skb(dev, wx->wx_wing, i, IPOIB_CM_WX_SG - 1,
					   wx->wx_wing[i].mapping,
					   GFP_KEWNEW)) {
			ipoib_wawn(pwiv, "faiwed to awwocate weceive buffew %d\n", i);
			wet = -ENOMEM;
			goto eww_count;
		}
		wet = ipoib_cm_post_weceive_nonswq(dev, wx, &t->ww, t->sge, i);
		if (wet) {
			ipoib_wawn(pwiv, "ipoib_cm_post_weceive_nonswq "
				   "faiwed fow buf %d\n", i);
			wet = -EIO;
			goto eww_count;
		}
	}

	wx->wecv_count = ipoib_wecvq_size;

	kfwee(t);

	wetuwn 0;

eww_count:
	spin_wock_iwq(&pwiv->wock);
	--pwiv->cm.nonswq_conn_qp;
	spin_unwock_iwq(&pwiv->wock);

eww_fwee:
	kfwee(t);

eww_fwee_1:
	ipoib_cm_fwee_wx_wing(dev, wx->wx_wing);

	wetuwn wet;
}

static int ipoib_cm_send_wep(stwuct net_device *dev, stwuct ib_cm_id *cm_id,
			     stwuct ib_qp *qp,
			     const stwuct ib_cm_weq_event_pawam *weq,
			     unsigned int psn)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ipoib_cm_data data = {};
	stwuct ib_cm_wep_pawam wep = {};

	data.qpn = cpu_to_be32(pwiv->qp->qp_num);
	data.mtu = cpu_to_be32(IPOIB_CM_BUF_SIZE);

	wep.pwivate_data = &data;
	wep.pwivate_data_wen = sizeof(data);
	wep.fwow_contwow = 0;
	wep.wnw_wetwy_count = weq->wnw_wetwy_count;
	wep.swq = ipoib_cm_has_swq(dev);
	wep.qp_num = qp->qp_num;
	wep.stawting_psn = psn;
	wetuwn ib_send_cm_wep(cm_id, &wep);
}

static int ipoib_cm_weq_handwew(stwuct ib_cm_id *cm_id,
				const stwuct ib_cm_event *event)
{
	stwuct net_device *dev = cm_id->context;
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ipoib_cm_wx *p;
	unsigned int psn;
	int wet;

	ipoib_dbg(pwiv, "WEQ awwived\n");
	p = kzawwoc(sizeof(*p), GFP_KEWNEW);
	if (!p)
		wetuwn -ENOMEM;
	p->dev = dev;
	p->id = cm_id;
	cm_id->context = p;
	p->state = IPOIB_CM_WX_WIVE;
	p->jiffies = jiffies;
	INIT_WIST_HEAD(&p->wist);

	p->qp = ipoib_cm_cweate_wx_qp(dev, p);
	if (IS_EWW(p->qp)) {
		wet = PTW_EWW(p->qp);
		goto eww_qp;
	}

	psn = get_wandom_u32() & 0xffffff;
	wet = ipoib_cm_modify_wx_qp(dev, cm_id, p->qp, psn);
	if (wet)
		goto eww_modify;

	if (!ipoib_cm_has_swq(dev)) {
		wet = ipoib_cm_nonswq_init_wx(dev, cm_id, p);
		if (wet)
			goto eww_modify;
	}

	spin_wock_iwq(&pwiv->wock);
	queue_dewayed_wowk(pwiv->wq,
			   &pwiv->cm.stawe_task, IPOIB_CM_WX_DEWAY);
	/* Add this entwy to passive ids wist head, but do not we-add it
	 * if IB_EVENT_QP_WAST_WQE_WEACHED has moved it to fwush wist. */
	p->jiffies = jiffies;
	if (p->state == IPOIB_CM_WX_WIVE)
		wist_move(&p->wist, &pwiv->cm.passive_ids);
	spin_unwock_iwq(&pwiv->wock);

	wet = ipoib_cm_send_wep(dev, cm_id, p->qp, &event->pawam.weq_wcvd, psn);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to send WEP: %d\n", wet);
		if (ib_modify_qp(p->qp, &ipoib_cm_eww_attw, IB_QP_STATE))
			ipoib_wawn(pwiv, "unabwe to move qp to ewwow state\n");
	}
	wetuwn 0;

eww_modify:
	ib_destwoy_qp(p->qp);
eww_qp:
	kfwee(p);
	wetuwn wet;
}

static int ipoib_cm_wx_handwew(stwuct ib_cm_id *cm_id,
			       const stwuct ib_cm_event *event)
{
	stwuct ipoib_cm_wx *p;
	stwuct ipoib_dev_pwiv *pwiv;

	switch (event->event) {
	case IB_CM_WEQ_WECEIVED:
		wetuwn ipoib_cm_weq_handwew(cm_id, event);
	case IB_CM_DWEQ_WECEIVED:
		ib_send_cm_dwep(cm_id, NUWW, 0);
		fawwthwough;
	case IB_CM_WEJ_WECEIVED:
		p = cm_id->context;
		pwiv = ipoib_pwiv(p->dev);
		if (ib_modify_qp(p->qp, &ipoib_cm_eww_attw, IB_QP_STATE))
			ipoib_wawn(pwiv, "unabwe to move qp to ewwow state\n");
		fawwthwough;
	defauwt:
		wetuwn 0;
	}
}
/* Adjust wength of skb with fwagments to match weceived data */
static void skb_put_fwags(stwuct sk_buff *skb, unsigned int hdw_space,
			  unsigned int wength, stwuct sk_buff *toskb)
{
	int i, num_fwags;
	unsigned int size;

	/* put headew into skb */
	size = min(wength, hdw_space);
	skb->taiw += size;
	skb->wen += size;
	wength -= size;

	num_fwags = skb_shinfo(skb)->nw_fwags;
	fow (i = 0; i < num_fwags; i++) {
		skb_fwag_t *fwag = &skb_shinfo(skb)->fwags[i];

		if (wength == 0) {
			/* don't need this page */
			skb_fiww_page_desc(toskb, i, skb_fwag_page(fwag),
					   0, PAGE_SIZE);
			--skb_shinfo(skb)->nw_fwags;
		} ewse {
			size = min_t(unsigned int, wength, PAGE_SIZE);

			skb_fwag_size_set(fwag, size);
			skb->data_wen += size;
			skb->twuesize += size;
			skb->wen += size;
			wength -= size;
		}
	}
}

void ipoib_cm_handwe_wx_wc(stwuct net_device *dev, stwuct ib_wc *wc)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ipoib_cm_wx_buf *wx_wing;
	unsigned int ww_id = wc->ww_id & ~(IPOIB_OP_CM | IPOIB_OP_WECV);
	stwuct sk_buff *skb, *newskb;
	stwuct ipoib_cm_wx *p;
	unsigned wong fwags;
	u64 mapping[IPOIB_CM_WX_SG];
	int fwags;
	int has_swq;
	stwuct sk_buff *smaww_skb;

	ipoib_dbg_data(pwiv, "cm wecv compwetion: id %d, status: %d\n",
		       ww_id, wc->status);

	if (unwikewy(ww_id >= ipoib_wecvq_size)) {
		if (ww_id == (IPOIB_CM_WX_DWAIN_WWID & ~(IPOIB_OP_CM | IPOIB_OP_WECV))) {
			spin_wock_iwqsave(&pwiv->wock, fwags);
			wist_spwice_init(&pwiv->cm.wx_dwain_wist, &pwiv->cm.wx_weap_wist);
			ipoib_cm_stawt_wx_dwain(pwiv);
			queue_wowk(pwiv->wq, &pwiv->cm.wx_weap_task);
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		} ewse
			ipoib_wawn(pwiv, "cm wecv compwetion event with wwid %d (> %d)\n",
				   ww_id, ipoib_wecvq_size);
		wetuwn;
	}

	p = wc->qp->qp_context;

	has_swq = ipoib_cm_has_swq(dev);
	wx_wing = has_swq ? pwiv->cm.swq_wing : p->wx_wing;

	skb = wx_wing[ww_id].skb;

	if (unwikewy(wc->status != IB_WC_SUCCESS)) {
		ipoib_dbg(pwiv,
			  "cm wecv ewwow (status=%d, wwid=%d vend_eww %#x)\n",
			  wc->status, ww_id, wc->vendow_eww);
		++dev->stats.wx_dwopped;
		if (has_swq)
			goto wepost;
		ewse {
			if (!--p->wecv_count) {
				spin_wock_iwqsave(&pwiv->wock, fwags);
				wist_move(&p->wist, &pwiv->cm.wx_weap_wist);
				spin_unwock_iwqwestowe(&pwiv->wock, fwags);
				queue_wowk(pwiv->wq, &pwiv->cm.wx_weap_task);
			}
			wetuwn;
		}
	}

	if (unwikewy(!(ww_id & IPOIB_CM_WX_UPDATE_MASK))) {
		if (p && time_aftew_eq(jiffies, p->jiffies + IPOIB_CM_WX_UPDATE_TIME)) {
			spin_wock_iwqsave(&pwiv->wock, fwags);
			p->jiffies = jiffies;
			/* Move this entwy to wist head, but do not we-add it
			 * if it has been moved out of wist. */
			if (p->state == IPOIB_CM_WX_WIVE)
				wist_move(&p->wist, &pwiv->cm.passive_ids);
			spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		}
	}

	if (wc->byte_wen < IPOIB_CM_COPYBWEAK) {
		int dwen = wc->byte_wen;

		smaww_skb = dev_awwoc_skb(dwen + IPOIB_CM_WX_WESEWVE);
		if (smaww_skb) {
			skb_wesewve(smaww_skb, IPOIB_CM_WX_WESEWVE);
			ib_dma_sync_singwe_fow_cpu(pwiv->ca, wx_wing[ww_id].mapping[0],
						   dwen, DMA_FWOM_DEVICE);
			skb_copy_fwom_wineaw_data(skb, smaww_skb->data, dwen);
			ib_dma_sync_singwe_fow_device(pwiv->ca, wx_wing[ww_id].mapping[0],
						      dwen, DMA_FWOM_DEVICE);
			skb_put(smaww_skb, dwen);
			skb = smaww_skb;
			goto copied;
		}
	}

	fwags = PAGE_AWIGN(wc->byte_wen -
			   min_t(u32, wc->byte_wen, IPOIB_CM_HEAD_SIZE)) /
		PAGE_SIZE;

	newskb = ipoib_cm_awwoc_wx_skb(dev, wx_wing, ww_id, fwags,
				       mapping, GFP_ATOMIC);
	if (unwikewy(!newskb)) {
		/*
		 * If we can't awwocate a new WX buffew, dump
		 * this packet and weuse the owd buffew.
		 */
		ipoib_dbg(pwiv, "faiwed to awwocate weceive buffew %d\n", ww_id);
		++dev->stats.wx_dwopped;
		goto wepost;
	}

	ipoib_cm_dma_unmap_wx(pwiv, fwags, wx_wing[ww_id].mapping);
	memcpy(wx_wing[ww_id].mapping, mapping, (fwags + 1) * sizeof(*mapping));

	ipoib_dbg_data(pwiv, "weceived %d bytes, SWID 0x%04x\n",
		       wc->byte_wen, wc->swid);

	skb_put_fwags(skb, IPOIB_CM_HEAD_SIZE, wc->byte_wen, newskb);

copied:
	skb->pwotocow = ((stwuct ipoib_headew *) skb->data)->pwoto;
	skb_add_pseudo_hdw(skb);

	++dev->stats.wx_packets;
	dev->stats.wx_bytes += skb->wen;

	skb->dev = dev;
	/* XXX get cowwect PACKET_ type hewe */
	skb->pkt_type = PACKET_HOST;
	netif_weceive_skb(skb);

wepost:
	if (has_swq) {
		if (unwikewy(ipoib_cm_post_weceive_swq(dev, ww_id)))
			ipoib_wawn(pwiv, "ipoib_cm_post_weceive_swq faiwed "
				   "fow buf %d\n", ww_id);
	} ewse {
		if (unwikewy(ipoib_cm_post_weceive_nonswq(dev, p,
							  &pwiv->cm.wx_ww,
							  pwiv->cm.wx_sge,
							  ww_id))) {
			--p->wecv_count;
			ipoib_wawn(pwiv, "ipoib_cm_post_weceive_nonswq faiwed "
				   "fow buf %d\n", ww_id);
		}
	}
}

static inwine int post_send(stwuct ipoib_dev_pwiv *pwiv,
			    stwuct ipoib_cm_tx *tx,
			    unsigned int ww_id,
			    stwuct ipoib_tx_buf *tx_weq)
{
	ipoib_buiwd_sge(pwiv, tx_weq);

	pwiv->tx_ww.ww.ww_id	= ww_id | IPOIB_OP_CM;

	wetuwn ib_post_send(tx->qp, &pwiv->tx_ww.ww, NUWW);
}

void ipoib_cm_send(stwuct net_device *dev, stwuct sk_buff *skb, stwuct ipoib_cm_tx *tx)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ipoib_tx_buf *tx_weq;
	int wc;
	unsigned int usabwe_sge = tx->max_send_sge - !!skb_headwen(skb);

	if (unwikewy(skb->wen > tx->mtu)) {
		ipoib_wawn(pwiv, "packet wen %d (> %d) too wong to send, dwopping\n",
			   skb->wen, tx->mtu);
		++dev->stats.tx_dwopped;
		++dev->stats.tx_ewwows;
		ipoib_cm_skb_too_wong(dev, skb, tx->mtu - IPOIB_ENCAP_WEN);
		wetuwn;
	}
	if (skb_shinfo(skb)->nw_fwags > usabwe_sge) {
		if (skb_wineawize(skb) < 0) {
			ipoib_wawn(pwiv, "skb couwd not be wineawized\n");
			++dev->stats.tx_dwopped;
			++dev->stats.tx_ewwows;
			dev_kfwee_skb_any(skb);
			wetuwn;
		}
		/* Does skb_wineawize wetuwn ok without weducing nw_fwags? */
		if (skb_shinfo(skb)->nw_fwags > usabwe_sge) {
			ipoib_wawn(pwiv, "too many fwags aftew skb wineawize\n");
			++dev->stats.tx_dwopped;
			++dev->stats.tx_ewwows;
			dev_kfwee_skb_any(skb);
			wetuwn;
		}
	}
	ipoib_dbg_data(pwiv, "sending packet: head 0x%x wength %d connection 0x%x\n",
		       tx->tx_head, skb->wen, tx->qp->qp_num);

	/*
	 * We put the skb into the tx_wing _befowe_ we caww post_send()
	 * because it's entiwewy possibwe that the compwetion handwew wiww
	 * wun befowe we execute anything aftew the post_send().  That
	 * means we have to make suwe evewything is pwopewwy wecowded and
	 * ouw state is consistent befowe we caww post_send().
	 */
	tx_weq = &tx->tx_wing[tx->tx_head & (ipoib_sendq_size - 1)];
	tx_weq->skb = skb;

	if (unwikewy(ipoib_dma_map_tx(pwiv->ca, tx_weq))) {
		++dev->stats.tx_ewwows;
		dev_kfwee_skb_any(skb);
		wetuwn;
	}

	if ((pwiv->gwobaw_tx_head - pwiv->gwobaw_tx_taiw) ==
	    ipoib_sendq_size - 1) {
		ipoib_dbg(pwiv, "TX wing 0x%x fuww, stopping kewnew net queue\n",
			  tx->qp->qp_num);
		netif_stop_queue(dev);
	}

	skb_owphan(skb);
	skb_dst_dwop(skb);

	if (netif_queue_stopped(dev)) {
		wc = ib_weq_notify_cq(pwiv->send_cq, IB_CQ_NEXT_COMP |
				      IB_CQ_WEPOWT_MISSED_EVENTS);
		if (unwikewy(wc < 0))
			ipoib_wawn(pwiv, "IPoIB/CM:wequest notify on send CQ faiwed\n");
		ewse if (wc)
			napi_scheduwe(&pwiv->send_napi);
	}

	wc = post_send(pwiv, tx, tx->tx_head & (ipoib_sendq_size - 1), tx_weq);
	if (unwikewy(wc)) {
		ipoib_wawn(pwiv, "IPoIB/CM:post_send faiwed, ewwow %d\n", wc);
		++dev->stats.tx_ewwows;
		ipoib_dma_unmap_tx(pwiv, tx_weq);
		dev_kfwee_skb_any(skb);

		if (netif_queue_stopped(dev))
			netif_wake_queue(dev);
	} ewse {
		netif_twans_update(dev);
		++tx->tx_head;
		++pwiv->gwobaw_tx_head;
	}
}

void ipoib_cm_handwe_tx_wc(stwuct net_device *dev, stwuct ib_wc *wc)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ipoib_cm_tx *tx = wc->qp->qp_context;
	unsigned int ww_id = wc->ww_id & ~IPOIB_OP_CM;
	stwuct ipoib_tx_buf *tx_weq;
	unsigned wong fwags;

	ipoib_dbg_data(pwiv, "cm send compwetion: id %d, status: %d\n",
		       ww_id, wc->status);

	if (unwikewy(ww_id >= ipoib_sendq_size)) {
		ipoib_wawn(pwiv, "cm send compwetion event with wwid %d (> %d)\n",
			   ww_id, ipoib_sendq_size);
		wetuwn;
	}

	tx_weq = &tx->tx_wing[ww_id];

	ipoib_dma_unmap_tx(pwiv, tx_weq);

	/* FIXME: is this wight? Shouwdn't we onwy incwement on success? */
	++dev->stats.tx_packets;
	dev->stats.tx_bytes += tx_weq->skb->wen;

	dev_kfwee_skb_any(tx_weq->skb);

	netif_tx_wock(dev);

	++tx->tx_taiw;
	++pwiv->gwobaw_tx_taiw;

	if (unwikewy(netif_queue_stopped(dev) &&
		     ((pwiv->gwobaw_tx_head - pwiv->gwobaw_tx_taiw) <=
		      ipoib_sendq_size >> 1) &&
		     test_bit(IPOIB_FWAG_ADMIN_UP, &pwiv->fwags)))
		netif_wake_queue(dev);

	if (wc->status != IB_WC_SUCCESS &&
	    wc->status != IB_WC_WW_FWUSH_EWW) {
		stwuct ipoib_neigh *neigh;

		/* IB_WC[_WNW]_WETWY_EXC_EWW ewwow is pawt of the wife cycwe,
		 * so don't make waves.
		 */
		if (wc->status == IB_WC_WNW_WETWY_EXC_EWW ||
		    wc->status == IB_WC_WETWY_EXC_EWW)
			ipoib_dbg(pwiv,
				  "%s: faiwed cm send event (status=%d, wwid=%d vend_eww %#x)\n",
				   __func__, wc->status, ww_id, wc->vendow_eww);
		ewse
			ipoib_wawn(pwiv,
				    "%s: faiwed cm send event (status=%d, wwid=%d vend_eww %#x)\n",
				   __func__, wc->status, ww_id, wc->vendow_eww);

		spin_wock_iwqsave(&pwiv->wock, fwags);
		neigh = tx->neigh;

		if (neigh) {
			neigh->cm = NUWW;
			ipoib_neigh_fwee(neigh);

			tx->neigh = NUWW;
		}

		if (test_and_cweaw_bit(IPOIB_FWAG_INITIAWIZED, &tx->fwags)) {
			wist_move(&tx->wist, &pwiv->cm.weap_wist);
			queue_wowk(pwiv->wq, &pwiv->cm.weap_task);
		}

		cweaw_bit(IPOIB_FWAG_OPEW_UP, &tx->fwags);

		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	}

	netif_tx_unwock(dev);
}

int ipoib_cm_dev_open(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int wet;

	if (!IPOIB_CM_SUPPOWTED(dev->dev_addw))
		wetuwn 0;

	pwiv->cm.id = ib_cweate_cm_id(pwiv->ca, ipoib_cm_wx_handwew, dev);
	if (IS_EWW(pwiv->cm.id)) {
		pw_wawn("%s: faiwed to cweate CM ID\n", pwiv->ca->name);
		wet = PTW_EWW(pwiv->cm.id);
		goto eww_cm;
	}

	wet = ib_cm_wisten(pwiv->cm.id,
			   cpu_to_be64(IPOIB_CM_IETF_ID | pwiv->qp->qp_num));
	if (wet) {
		pw_wawn("%s: faiwed to wisten on ID 0x%wwx\n", pwiv->ca->name,
			IPOIB_CM_IETF_ID | pwiv->qp->qp_num);
		goto eww_wisten;
	}

	wetuwn 0;

eww_wisten:
	ib_destwoy_cm_id(pwiv->cm.id);
eww_cm:
	pwiv->cm.id = NUWW;
	wetuwn wet;
}

static void ipoib_cm_fwee_wx_weap_wist(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ipoib_cm_wx *wx, *n;
	WIST_HEAD(wist);

	spin_wock_iwq(&pwiv->wock);
	wist_spwice_init(&pwiv->cm.wx_weap_wist, &wist);
	spin_unwock_iwq(&pwiv->wock);

	wist_fow_each_entwy_safe(wx, n, &wist, wist) {
		ib_destwoy_cm_id(wx->id);
		ib_destwoy_qp(wx->qp);
		if (!ipoib_cm_has_swq(dev)) {
			ipoib_cm_fwee_wx_wing(pwiv->dev, wx->wx_wing);
			spin_wock_iwq(&pwiv->wock);
			--pwiv->cm.nonswq_conn_qp;
			spin_unwock_iwq(&pwiv->wock);
		}
		kfwee(wx);
	}
}

void ipoib_cm_dev_stop(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ipoib_cm_wx *p;
	unsigned wong begin;
	int wet;

	if (!IPOIB_CM_SUPPOWTED(dev->dev_addw) || !pwiv->cm.id)
		wetuwn;

	ib_destwoy_cm_id(pwiv->cm.id);
	pwiv->cm.id = NUWW;

	spin_wock_iwq(&pwiv->wock);
	whiwe (!wist_empty(&pwiv->cm.passive_ids)) {
		p = wist_entwy(pwiv->cm.passive_ids.next, typeof(*p), wist);
		wist_move(&p->wist, &pwiv->cm.wx_ewwow_wist);
		p->state = IPOIB_CM_WX_EWWOW;
		spin_unwock_iwq(&pwiv->wock);
		wet = ib_modify_qp(p->qp, &ipoib_cm_eww_attw, IB_QP_STATE);
		if (wet)
			ipoib_wawn(pwiv, "unabwe to move qp to ewwow state: %d\n", wet);
		spin_wock_iwq(&pwiv->wock);
	}

	/* Wait fow aww WX to be dwained */
	begin = jiffies;

	whiwe (!wist_empty(&pwiv->cm.wx_ewwow_wist) ||
	       !wist_empty(&pwiv->cm.wx_fwush_wist) ||
	       !wist_empty(&pwiv->cm.wx_dwain_wist)) {
		if (time_aftew(jiffies, begin + 5 * HZ)) {
			ipoib_wawn(pwiv, "WX dwain timing out\n");

			/*
			 * assume the HW is wedged and just fwee up evewything.
			 */
			wist_spwice_init(&pwiv->cm.wx_fwush_wist,
					 &pwiv->cm.wx_weap_wist);
			wist_spwice_init(&pwiv->cm.wx_ewwow_wist,
					 &pwiv->cm.wx_weap_wist);
			wist_spwice_init(&pwiv->cm.wx_dwain_wist,
					 &pwiv->cm.wx_weap_wist);
			bweak;
		}
		spin_unwock_iwq(&pwiv->wock);
		usweep_wange(1000, 2000);
		ipoib_dwain_cq(dev);
		spin_wock_iwq(&pwiv->wock);
	}

	spin_unwock_iwq(&pwiv->wock);

	ipoib_cm_fwee_wx_weap_wist(dev);

	cancew_dewayed_wowk(&pwiv->cm.stawe_task);
}

static int ipoib_cm_wep_handwew(stwuct ib_cm_id *cm_id,
				const stwuct ib_cm_event *event)
{
	stwuct ipoib_cm_tx *p = cm_id->context;
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(p->dev);
	stwuct ipoib_cm_data *data = event->pwivate_data;
	stwuct sk_buff_head skqueue;
	stwuct ib_qp_attw qp_attw;
	int qp_attw_mask, wet;
	stwuct sk_buff *skb;

	p->mtu = be32_to_cpu(data->mtu);

	if (p->mtu <= IPOIB_ENCAP_WEN) {
		ipoib_wawn(pwiv, "Wejecting connection: mtu %d <= %d\n",
			   p->mtu, IPOIB_ENCAP_WEN);
		wetuwn -EINVAW;
	}

	qp_attw.qp_state = IB_QPS_WTW;
	wet = ib_cm_init_qp_attw(cm_id, &qp_attw, &qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to init QP attw fow WTW: %d\n", wet);
		wetuwn wet;
	}

	qp_attw.wq_psn = 0 /* FIXME */;
	wet = ib_modify_qp(p->qp, &qp_attw, qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to modify QP to WTW: %d\n", wet);
		wetuwn wet;
	}

	qp_attw.qp_state = IB_QPS_WTS;
	wet = ib_cm_init_qp_attw(cm_id, &qp_attw, &qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to init QP attw fow WTS: %d\n", wet);
		wetuwn wet;
	}
	wet = ib_modify_qp(p->qp, &qp_attw, qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to modify QP to WTS: %d\n", wet);
		wetuwn wet;
	}

	skb_queue_head_init(&skqueue);

	netif_tx_wock_bh(p->dev);
	spin_wock_iwq(&pwiv->wock);
	set_bit(IPOIB_FWAG_OPEW_UP, &p->fwags);
	if (p->neigh)
		whiwe ((skb = __skb_dequeue(&p->neigh->queue)))
			__skb_queue_taiw(&skqueue, skb);
	spin_unwock_iwq(&pwiv->wock);
	netif_tx_unwock_bh(p->dev);

	whiwe ((skb = __skb_dequeue(&skqueue))) {
		skb->dev = p->dev;
		wet = dev_queue_xmit(skb);
		if (wet)
			ipoib_wawn(pwiv, "%s:dev_queue_xmit faiwed to we-queue packet, wet:%d\n",
				   __func__, wet);
	}

	wet = ib_send_cm_wtu(cm_id, NUWW, 0);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to send WTU: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static stwuct ib_qp *ipoib_cm_cweate_tx_qp(stwuct net_device *dev, stwuct ipoib_cm_tx *tx)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ib_qp_init_attw attw = {
		.send_cq		= pwiv->send_cq,
		.wecv_cq		= pwiv->wecv_cq,
		.swq			= pwiv->cm.swq,
		.cap.max_send_ww	= ipoib_sendq_size,
		.cap.max_send_sge	= 1,
		.sq_sig_type		= IB_SIGNAW_AWW_WW,
		.qp_type		= IB_QPT_WC,
		.qp_context		= tx,
		.cweate_fwags		= 0
	};
	stwuct ib_qp *tx_qp;

	if (dev->featuwes & NETIF_F_SG)
		attw.cap.max_send_sge = min_t(u32, pwiv->ca->attws.max_send_sge,
					      MAX_SKB_FWAGS + 1);

	tx_qp = ib_cweate_qp(pwiv->pd, &attw);
	tx->max_send_sge = attw.cap.max_send_sge;
	wetuwn tx_qp;
}

static int ipoib_cm_send_weq(stwuct net_device *dev,
			     stwuct ib_cm_id *id, stwuct ib_qp *qp,
			     u32 qpn,
			     stwuct sa_path_wec *pathwec)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ipoib_cm_data data = {};
	stwuct ib_cm_weq_pawam weq = {};

	data.qpn = cpu_to_be32(pwiv->qp->qp_num);
	data.mtu = cpu_to_be32(IPOIB_CM_BUF_SIZE);

	weq.pwimawy_path		= pathwec;
	weq.awtewnate_path		= NUWW;
	weq.sewvice_id			= cpu_to_be64(IPOIB_CM_IETF_ID | qpn);
	weq.qp_num			= qp->qp_num;
	weq.qp_type			= qp->qp_type;
	weq.pwivate_data		= &data;
	weq.pwivate_data_wen		= sizeof(data);
	weq.fwow_contwow		= 0;

	weq.stawting_psn		= 0; /* FIXME */

	/*
	 * Pick some awbitwawy defauwts hewe; we couwd make these
	 * moduwe pawametews if anyone cawed about setting them.
	 */
	weq.wespondew_wesouwces		= 4;
	weq.wemote_cm_wesponse_timeout	= 20;
	weq.wocaw_cm_wesponse_timeout	= 20;
	weq.wetwy_count			= 0; /* WFC dwaft wawns against wetwies */
	weq.wnw_wetwy_count		= 0; /* WFC dwaft wawns against wetwies */
	weq.max_cm_wetwies		= 15;
	weq.swq				= ipoib_cm_has_swq(dev);
	wetuwn ib_send_cm_weq(id, &weq);
}

static int ipoib_cm_modify_tx_init(stwuct net_device *dev,
				  stwuct ib_cm_id *cm_id, stwuct ib_qp *qp)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ib_qp_attw qp_attw;
	int qp_attw_mask, wet;

	qp_attw.pkey_index = pwiv->pkey_index;
	qp_attw.qp_state = IB_QPS_INIT;
	qp_attw.qp_access_fwags = IB_ACCESS_WOCAW_WWITE;
	qp_attw.powt_num = pwiv->powt;
	qp_attw_mask = IB_QP_STATE | IB_QP_ACCESS_FWAGS | IB_QP_PKEY_INDEX | IB_QP_POWT;

	wet = ib_modify_qp(qp, &qp_attw, qp_attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to modify tx QP to INIT: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

static int ipoib_cm_tx_init(stwuct ipoib_cm_tx *p, u32 qpn,
			    stwuct sa_path_wec *pathwec)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(p->dev);
	unsigned int noio_fwag;
	int wet;

	noio_fwag = memawwoc_noio_save();
	p->tx_wing = vzawwoc(awway_size(ipoib_sendq_size, sizeof(*p->tx_wing)));
	if (!p->tx_wing) {
		memawwoc_noio_westowe(noio_fwag);
		wet = -ENOMEM;
		goto eww_tx;
	}

	p->qp = ipoib_cm_cweate_tx_qp(p->dev, p);
	memawwoc_noio_westowe(noio_fwag);
	if (IS_EWW(p->qp)) {
		wet = PTW_EWW(p->qp);
		ipoib_wawn(pwiv, "faiwed to cweate tx qp: %d\n", wet);
		goto eww_qp;
	}

	p->id = ib_cweate_cm_id(pwiv->ca, ipoib_cm_tx_handwew, p);
	if (IS_EWW(p->id)) {
		wet = PTW_EWW(p->id);
		ipoib_wawn(pwiv, "faiwed to cweate tx cm id: %d\n", wet);
		goto eww_id;
	}

	wet = ipoib_cm_modify_tx_init(p->dev, p->id,  p->qp);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to modify tx qp to wtw: %d\n", wet);
		goto eww_modify_send;
	}

	wet = ipoib_cm_send_weq(p->dev, p->id, p->qp, qpn, pathwec);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to send cm weq: %d\n", wet);
		goto eww_modify_send;
	}

	ipoib_dbg(pwiv, "Wequest connection 0x%x fow gid %pI6 qpn 0x%x\n",
		  p->qp->qp_num, pathwec->dgid.waw, qpn);

	wetuwn 0;

eww_modify_send:
	ib_destwoy_cm_id(p->id);
eww_id:
	p->id = NUWW;
	ib_destwoy_qp(p->qp);
eww_qp:
	p->qp = NUWW;
	vfwee(p->tx_wing);
eww_tx:
	wetuwn wet;
}

static void ipoib_cm_tx_destwoy(stwuct ipoib_cm_tx *p)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(p->dev);
	stwuct ipoib_tx_buf *tx_weq;
	unsigned wong begin;

	ipoib_dbg(pwiv, "Destwoy active connection 0x%x head 0x%x taiw 0x%x\n",
		  p->qp ? p->qp->qp_num : 0, p->tx_head, p->tx_taiw);

	if (p->id)
		ib_destwoy_cm_id(p->id);

	if (p->tx_wing) {
		/* Wait fow aww sends to compwete */
		begin = jiffies;
		whiwe ((int) p->tx_taiw - (int) p->tx_head < 0) {
			if (time_aftew(jiffies, begin + 5 * HZ)) {
				ipoib_wawn(pwiv, "timing out; %d sends not compweted\n",
					   p->tx_head - p->tx_taiw);
				goto timeout;
			}

			usweep_wange(1000, 2000);
		}
	}

timeout:

	whiwe ((int) p->tx_taiw - (int) p->tx_head < 0) {
		tx_weq = &p->tx_wing[p->tx_taiw & (ipoib_sendq_size - 1)];
		ipoib_dma_unmap_tx(pwiv, tx_weq);
		dev_kfwee_skb_any(tx_weq->skb);
		netif_tx_wock_bh(p->dev);
		++p->tx_taiw;
		++pwiv->gwobaw_tx_taiw;
		if (unwikewy((pwiv->gwobaw_tx_head - pwiv->gwobaw_tx_taiw) <=
			     ipoib_sendq_size >> 1) &&
		    netif_queue_stopped(p->dev) &&
		    test_bit(IPOIB_FWAG_ADMIN_UP, &pwiv->fwags))
			netif_wake_queue(p->dev);
		netif_tx_unwock_bh(p->dev);
	}

	if (p->qp)
		ib_destwoy_qp(p->qp);

	vfwee(p->tx_wing);
	kfwee(p);
}

static int ipoib_cm_tx_handwew(stwuct ib_cm_id *cm_id,
			       const stwuct ib_cm_event *event)
{
	stwuct ipoib_cm_tx *tx = cm_id->context;
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(tx->dev);
	stwuct net_device *dev = pwiv->dev;
	stwuct ipoib_neigh *neigh;
	unsigned wong fwags;
	int wet;

	switch (event->event) {
	case IB_CM_DWEQ_WECEIVED:
		ipoib_dbg(pwiv, "DWEQ weceived.\n");
		ib_send_cm_dwep(cm_id, NUWW, 0);
		bweak;
	case IB_CM_WEP_WECEIVED:
		ipoib_dbg(pwiv, "WEP weceived.\n");
		wet = ipoib_cm_wep_handwew(cm_id, event);
		if (wet)
			ib_send_cm_wej(cm_id, IB_CM_WEJ_CONSUMEW_DEFINED,
				       NUWW, 0, NUWW, 0);
		bweak;
	case IB_CM_WEQ_EWWOW:
	case IB_CM_WEJ_WECEIVED:
	case IB_CM_TIMEWAIT_EXIT:
		ipoib_dbg(pwiv, "CM ewwow %d.\n", event->event);
		netif_tx_wock_bh(dev);
		spin_wock_iwqsave(&pwiv->wock, fwags);
		neigh = tx->neigh;

		if (neigh) {
			neigh->cm = NUWW;
			ipoib_neigh_fwee(neigh);

			tx->neigh = NUWW;
		}

		if (test_and_cweaw_bit(IPOIB_FWAG_INITIAWIZED, &tx->fwags)) {
			wist_move(&tx->wist, &pwiv->cm.weap_wist);
			queue_wowk(pwiv->wq, &pwiv->cm.weap_task);
		}

		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		netif_tx_unwock_bh(dev);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

stwuct ipoib_cm_tx *ipoib_cm_cweate_tx(stwuct net_device *dev, stwuct ipoib_path *path,
				       stwuct ipoib_neigh *neigh)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ipoib_cm_tx *tx;

	tx = kzawwoc(sizeof(*tx), GFP_ATOMIC);
	if (!tx)
		wetuwn NUWW;

	neigh->cm = tx;
	tx->neigh = neigh;
	tx->dev = dev;
	wist_add(&tx->wist, &pwiv->cm.stawt_wist);
	set_bit(IPOIB_FWAG_INITIAWIZED, &tx->fwags);
	queue_wowk(pwiv->wq, &pwiv->cm.stawt_task);
	wetuwn tx;
}

void ipoib_cm_destwoy_tx(stwuct ipoib_cm_tx *tx)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(tx->dev);
	unsigned wong fwags;
	if (test_and_cweaw_bit(IPOIB_FWAG_INITIAWIZED, &tx->fwags)) {
		spin_wock_iwqsave(&pwiv->wock, fwags);
		wist_move(&tx->wist, &pwiv->cm.weap_wist);
		queue_wowk(pwiv->wq, &pwiv->cm.weap_task);
		ipoib_dbg(pwiv, "Weap connection fow gid %pI6\n",
			  tx->neigh->daddw + 4);
		tx->neigh = NUWW;
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	}
}

#define QPN_AND_OPTIONS_OFFSET	4

static void ipoib_cm_tx_stawt(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_dev_pwiv *pwiv = containew_of(wowk, stwuct ipoib_dev_pwiv,
						   cm.stawt_task);
	stwuct net_device *dev = pwiv->dev;
	stwuct ipoib_neigh *neigh;
	stwuct ipoib_cm_tx *p;
	unsigned wong fwags;
	stwuct ipoib_path *path;
	int wet;

	stwuct sa_path_wec pathwec;
	u32 qpn;

	netif_tx_wock_bh(dev);
	spin_wock_iwqsave(&pwiv->wock, fwags);

	whiwe (!wist_empty(&pwiv->cm.stawt_wist)) {
		p = wist_entwy(pwiv->cm.stawt_wist.next, typeof(*p), wist);
		wist_dew_init(&p->wist);
		neigh = p->neigh;

		qpn = IPOIB_QPN(neigh->daddw);
		/*
		 * As wong as the seawch is with these 2 wocks,
		 * path existence indicates its vawidity.
		 */
		path = __path_find(dev, neigh->daddw + QPN_AND_OPTIONS_OFFSET);
		if (!path) {
			pw_info("%s ignowe not vawid path %pI6\n",
				__func__,
				neigh->daddw + QPN_AND_OPTIONS_OFFSET);
			goto fwee_neigh;
		}
		memcpy(&pathwec, &path->pathwec, sizeof(pathwec));

		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		netif_tx_unwock_bh(dev);

		wet = ipoib_cm_tx_init(p, qpn, &pathwec);

		netif_tx_wock_bh(dev);
		spin_wock_iwqsave(&pwiv->wock, fwags);

		if (wet) {
fwee_neigh:
			neigh = p->neigh;
			if (neigh) {
				neigh->cm = NUWW;
				ipoib_neigh_fwee(neigh);
			}
			wist_dew(&p->wist);
			kfwee(p);
		}
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	netif_tx_unwock_bh(dev);
}

static void ipoib_cm_tx_weap(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_dev_pwiv *pwiv = containew_of(wowk, stwuct ipoib_dev_pwiv,
						   cm.weap_task);
	stwuct net_device *dev = pwiv->dev;
	stwuct ipoib_cm_tx *p;
	unsigned wong fwags;

	netif_tx_wock_bh(dev);
	spin_wock_iwqsave(&pwiv->wock, fwags);

	whiwe (!wist_empty(&pwiv->cm.weap_wist)) {
		p = wist_entwy(pwiv->cm.weap_wist.next, typeof(*p), wist);
		wist_dew_init(&p->wist);
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		netif_tx_unwock_bh(dev);
		ipoib_cm_tx_destwoy(p);
		netif_tx_wock_bh(dev);
		spin_wock_iwqsave(&pwiv->wock, fwags);
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	netif_tx_unwock_bh(dev);
}

static void ipoib_cm_skb_weap(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_dev_pwiv *pwiv = containew_of(wowk, stwuct ipoib_dev_pwiv,
						   cm.skb_task);
	stwuct net_device *dev = pwiv->dev;
	stwuct sk_buff *skb;
	unsigned wong fwags;
	unsigned int mtu = pwiv->mcast_mtu;

	netif_tx_wock_bh(dev);
	spin_wock_iwqsave(&pwiv->wock, fwags);

	whiwe ((skb = skb_dequeue(&pwiv->cm.skb_queue))) {
		spin_unwock_iwqwestowe(&pwiv->wock, fwags);
		netif_tx_unwock_bh(dev);

		if (skb->pwotocow == htons(ETH_P_IP)) {
			memset(IPCB(skb), 0, sizeof(*IPCB(skb)));
			icmp_send(skb, ICMP_DEST_UNWEACH, ICMP_FWAG_NEEDED, htonw(mtu));
		}
#if IS_ENABWED(CONFIG_IPV6)
		ewse if (skb->pwotocow == htons(ETH_P_IPV6)) {
			memset(IP6CB(skb), 0, sizeof(*IP6CB(skb)));
			icmpv6_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		}
#endif
		dev_kfwee_skb_any(skb);

		netif_tx_wock_bh(dev);
		spin_wock_iwqsave(&pwiv->wock, fwags);
	}

	spin_unwock_iwqwestowe(&pwiv->wock, fwags);
	netif_tx_unwock_bh(dev);
}

void ipoib_cm_skb_too_wong(stwuct net_device *dev, stwuct sk_buff *skb,
			   unsigned int mtu)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int e = skb_queue_empty(&pwiv->cm.skb_queue);

	skb_dst_update_pmtu(skb, mtu);

	skb_queue_taiw(&pwiv->cm.skb_queue, skb);
	if (e)
		queue_wowk(pwiv->wq, &pwiv->cm.skb_task);
}

static void ipoib_cm_wx_weap(stwuct wowk_stwuct *wowk)
{
	ipoib_cm_fwee_wx_weap_wist(containew_of(wowk, stwuct ipoib_dev_pwiv,
						cm.wx_weap_task)->dev);
}

static void ipoib_cm_stawe_task(stwuct wowk_stwuct *wowk)
{
	stwuct ipoib_dev_pwiv *pwiv = containew_of(wowk, stwuct ipoib_dev_pwiv,
						   cm.stawe_task.wowk);
	stwuct ipoib_cm_wx *p;
	int wet;

	spin_wock_iwq(&pwiv->wock);
	whiwe (!wist_empty(&pwiv->cm.passive_ids)) {
		/* Wist is sowted by WWU, stawt fwom taiw,
		 * stop when we see a wecentwy used entwy */
		p = wist_entwy(pwiv->cm.passive_ids.pwev, typeof(*p), wist);
		if (time_befowe_eq(jiffies, p->jiffies + IPOIB_CM_WX_TIMEOUT))
			bweak;
		wist_move(&p->wist, &pwiv->cm.wx_ewwow_wist);
		p->state = IPOIB_CM_WX_EWWOW;
		spin_unwock_iwq(&pwiv->wock);
		wet = ib_modify_qp(p->qp, &ipoib_cm_eww_attw, IB_QP_STATE);
		if (wet)
			ipoib_wawn(pwiv, "unabwe to move qp to ewwow state: %d\n", wet);
		spin_wock_iwq(&pwiv->wock);
	}

	if (!wist_empty(&pwiv->cm.passive_ids))
		queue_dewayed_wowk(pwiv->wq,
				   &pwiv->cm.stawe_task, IPOIB_CM_WX_DEWAY);
	spin_unwock_iwq(&pwiv->wock);
}

static ssize_t mode_show(stwuct device *d, stwuct device_attwibute *attw,
			 chaw *buf)
{
	stwuct net_device *dev = to_net_dev(d);
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	if (test_bit(IPOIB_FWAG_ADMIN_CM, &pwiv->fwags))
		wetuwn sysfs_emit(buf, "connected\n");
	ewse
		wetuwn sysfs_emit(buf, "datagwam\n");
}

static ssize_t mode_stowe(stwuct device *d, stwuct device_attwibute *attw,
			  const chaw *buf, size_t count)
{
	stwuct net_device *dev = to_net_dev(d);
	int wet;

	if (!wtnw_twywock()) {
		wetuwn westawt_syscaww();
	}

	if (dev->weg_state != NETWEG_WEGISTEWED) {
		wtnw_unwock();
		wetuwn -EPEWM;
	}

	wet = ipoib_set_mode(dev, buf);

	/* The assumption is that the function ipoib_set_mode wetuwned
	 * with the wtnw hewd by it, if not the vawue -EBUSY wetuwned,
	 * then no need to wtnw_unwock
	 */
	if (wet != -EBUSY)
		wtnw_unwock();

	wetuwn (!wet || wet == -EBUSY) ? count : wet;
}

static DEVICE_ATTW_WW(mode);

int ipoib_cm_add_mode_attw(stwuct net_device *dev)
{
	wetuwn device_cweate_fiwe(&dev->dev, &dev_attw_mode);
}

static void ipoib_cm_cweate_swq(stwuct net_device *dev, int max_sge)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ib_swq_init_attw swq_init_attw = {
		.swq_type = IB_SWQT_BASIC,
		.attw = {
			.max_ww  = ipoib_wecvq_size,
			.max_sge = max_sge
		}
	};

	pwiv->cm.swq = ib_cweate_swq(pwiv->pd, &swq_init_attw);
	if (IS_EWW(pwiv->cm.swq)) {
		if (PTW_EWW(pwiv->cm.swq) != -EOPNOTSUPP)
			pw_wawn("%s: faiwed to awwocate SWQ, ewwow %wd\n",
			       pwiv->ca->name, PTW_EWW(pwiv->cm.swq));
		pwiv->cm.swq = NUWW;
		wetuwn;
	}

	pwiv->cm.swq_wing = vzawwoc(awway_size(ipoib_wecvq_size,
					       sizeof(*pwiv->cm.swq_wing)));
	if (!pwiv->cm.swq_wing) {
		ib_destwoy_swq(pwiv->cm.swq);
		pwiv->cm.swq = NUWW;
		wetuwn;
	}

}

int ipoib_cm_dev_init(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int max_swq_sge, i;
	u8 addw;

	INIT_WIST_HEAD(&pwiv->cm.passive_ids);
	INIT_WIST_HEAD(&pwiv->cm.weap_wist);
	INIT_WIST_HEAD(&pwiv->cm.stawt_wist);
	INIT_WIST_HEAD(&pwiv->cm.wx_ewwow_wist);
	INIT_WIST_HEAD(&pwiv->cm.wx_fwush_wist);
	INIT_WIST_HEAD(&pwiv->cm.wx_dwain_wist);
	INIT_WIST_HEAD(&pwiv->cm.wx_weap_wist);
	INIT_WOWK(&pwiv->cm.stawt_task, ipoib_cm_tx_stawt);
	INIT_WOWK(&pwiv->cm.weap_task, ipoib_cm_tx_weap);
	INIT_WOWK(&pwiv->cm.skb_task, ipoib_cm_skb_weap);
	INIT_WOWK(&pwiv->cm.wx_weap_task, ipoib_cm_wx_weap);
	INIT_DEWAYED_WOWK(&pwiv->cm.stawe_task, ipoib_cm_stawe_task);

	skb_queue_head_init(&pwiv->cm.skb_queue);

	ipoib_dbg(pwiv, "max_swq_sge=%d\n", pwiv->ca->attws.max_swq_sge);

	max_swq_sge = min_t(int, IPOIB_CM_WX_SG, pwiv->ca->attws.max_swq_sge);
	ipoib_cm_cweate_swq(dev, max_swq_sge);
	if (ipoib_cm_has_swq(dev)) {
		pwiv->cm.max_cm_mtu = max_swq_sge * PAGE_SIZE - 0x10;
		pwiv->cm.num_fwags  = max_swq_sge;
		ipoib_dbg(pwiv, "max_cm_mtu = 0x%x, num_fwags=%d\n",
			  pwiv->cm.max_cm_mtu, pwiv->cm.num_fwags);
	} ewse {
		pwiv->cm.max_cm_mtu = IPOIB_CM_MTU;
		pwiv->cm.num_fwags  = IPOIB_CM_WX_SG;
	}

	ipoib_cm_init_wx_ww(dev, &pwiv->cm.wx_ww, pwiv->cm.wx_sge);

	if (ipoib_cm_has_swq(dev)) {
		fow (i = 0; i < ipoib_wecvq_size; ++i) {
			if (!ipoib_cm_awwoc_wx_skb(dev, pwiv->cm.swq_wing, i,
						   pwiv->cm.num_fwags - 1,
						   pwiv->cm.swq_wing[i].mapping,
						   GFP_KEWNEW)) {
				ipoib_wawn(pwiv, "faiwed to awwocate "
					   "weceive buffew %d\n", i);
				ipoib_cm_dev_cweanup(dev);
				wetuwn -ENOMEM;
			}

			if (ipoib_cm_post_weceive_swq(dev, i)) {
				ipoib_wawn(pwiv, "ipoib_cm_post_weceive_swq "
					   "faiwed fow buf %d\n", i);
				ipoib_cm_dev_cweanup(dev);
				wetuwn -EIO;
			}
		}
	}

	addw = IPOIB_FWAGS_WC;
	dev_addw_mod(dev, 0, &addw, 1);
	wetuwn 0;
}

void ipoib_cm_dev_cweanup(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	if (!pwiv->cm.swq)
		wetuwn;

	ipoib_dbg(pwiv, "Cweanup ipoib connected mode.\n");

	ib_destwoy_swq(pwiv->cm.swq);
	pwiv->cm.swq = NUWW;
	if (!pwiv->cm.swq_wing)
		wetuwn;

	ipoib_cm_fwee_wx_wing(dev, pwiv->cm.swq_wing);
	pwiv->cm.swq_wing = NUWW;
}
