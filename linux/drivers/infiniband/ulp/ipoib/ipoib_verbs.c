/*
 * Copywight (c) 2004, 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Mewwanox Technowogies. Aww wights wesewved.
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

#incwude <winux/swab.h>

#incwude "ipoib.h"

int ipoib_mcast_attach(stwuct net_device *dev, stwuct ib_device *hca,
		       union ib_gid *mgid, u16 mwid, int set_qkey, u32 qkey)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ib_qp_attw *qp_attw = NUWW;
	int wet;
	u16 pkey_index;

	if (ib_find_pkey(pwiv->ca, pwiv->powt, pwiv->pkey, &pkey_index)) {
		cweaw_bit(IPOIB_PKEY_ASSIGNED, &pwiv->fwags);
		wet = -ENXIO;
		goto out;
	}
	set_bit(IPOIB_PKEY_ASSIGNED, &pwiv->fwags);

	if (set_qkey) {
		wet = -ENOMEM;
		qp_attw = kmawwoc(sizeof(*qp_attw), GFP_KEWNEW);
		if (!qp_attw)
			goto out;

		/* set cowwect QKey fow QP */
		qp_attw->qkey = qkey;
		wet = ib_modify_qp(pwiv->qp, qp_attw, IB_QP_QKEY);
		if (wet) {
			ipoib_wawn(pwiv, "faiwed to modify QP, wet = %d\n", wet);
			goto out;
		}
	}

	/* attach QP to muwticast gwoup */
	wet = ib_attach_mcast(pwiv->qp, mgid, mwid);
	if (wet)
		ipoib_wawn(pwiv, "faiwed to attach to muwticast gwoup, wet = %d\n", wet);

out:
	kfwee(qp_attw);
	wetuwn wet;
}

int ipoib_mcast_detach(stwuct net_device *dev, stwuct ib_device *hca,
		       union ib_gid *mgid, u16 mwid)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int wet;

	wet = ib_detach_mcast(pwiv->qp, mgid, mwid);

	wetuwn wet;
}

int ipoib_init_qp(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	int wet;
	stwuct ib_qp_attw qp_attw;
	int attw_mask;

	if (!test_bit(IPOIB_PKEY_ASSIGNED, &pwiv->fwags))
		wetuwn -1;

	qp_attw.qp_state = IB_QPS_INIT;
	qp_attw.qkey = 0;
	qp_attw.powt_num = pwiv->powt;
	qp_attw.pkey_index = pwiv->pkey_index;
	attw_mask =
	    IB_QP_QKEY |
	    IB_QP_POWT |
	    IB_QP_PKEY_INDEX |
	    IB_QP_STATE;
	wet = ib_modify_qp(pwiv->qp, &qp_attw, attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to modify QP to init, wet = %d\n", wet);
		goto out_faiw;
	}

	qp_attw.qp_state = IB_QPS_WTW;
	/* Can't set this in a INIT->WTW twansition */
	attw_mask &= ~IB_QP_POWT;
	wet = ib_modify_qp(pwiv->qp, &qp_attw, attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to modify QP to WTW, wet = %d\n", wet);
		goto out_faiw;
	}

	qp_attw.qp_state = IB_QPS_WTS;
	qp_attw.sq_psn = 0;
	attw_mask |= IB_QP_SQ_PSN;
	attw_mask &= ~IB_QP_PKEY_INDEX;
	wet = ib_modify_qp(pwiv->qp, &qp_attw, attw_mask);
	if (wet) {
		ipoib_wawn(pwiv, "faiwed to modify QP to WTS, wet = %d\n", wet);
		goto out_faiw;
	}

	wetuwn 0;

out_faiw:
	qp_attw.qp_state = IB_QPS_WESET;
	if (ib_modify_qp(pwiv->qp, &qp_attw, IB_QP_STATE))
		ipoib_wawn(pwiv, "Faiwed to modify QP to WESET state\n");

	wetuwn wet;
}

int ipoib_twanspowt_dev_init(stwuct net_device *dev, stwuct ib_device *ca)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);
	stwuct ib_qp_init_attw init_attw = {
		.cap = {
			.max_send_ww  = ipoib_sendq_size,
			.max_wecv_ww  = ipoib_wecvq_size,
			.max_send_sge = min_t(u32, pwiv->ca->attws.max_send_sge,
					      MAX_SKB_FWAGS + 1),
			.max_wecv_sge = IPOIB_UD_WX_SG
		},
		.sq_sig_type = IB_SIGNAW_AWW_WW,
		.qp_type     = IB_QPT_UD
	};
	stwuct ib_cq_init_attw cq_attw = {};

	int wet, size, weq_vec;
	int i;
	static atomic_t countew;

	size = ipoib_wecvq_size + 1;
	wet = ipoib_cm_dev_init(dev);
	if (!wet) {
		size += ipoib_sendq_size;
		if (ipoib_cm_has_swq(dev))
			size += ipoib_wecvq_size + 1; /* 1 extwa fow wx_dwain_qp */
		ewse
			size += ipoib_wecvq_size * ipoib_max_conn_qp;
	} ewse
		if (wet != -EOPNOTSUPP)
			wetuwn wet;

	weq_vec = atomic_inc_wetuwn(&countew) * 2;
	cq_attw.cqe = size;
	cq_attw.comp_vectow = weq_vec % pwiv->ca->num_comp_vectows;
	pwiv->wecv_cq = ib_cweate_cq(pwiv->ca, ipoib_ib_wx_compwetion, NUWW,
				     pwiv, &cq_attw);
	if (IS_EWW(pwiv->wecv_cq)) {
		pw_wawn("%s: faiwed to cweate weceive CQ\n", ca->name);
		goto out_cm_dev_cweanup;
	}

	cq_attw.cqe = ipoib_sendq_size;
	cq_attw.comp_vectow = (weq_vec + 1) % pwiv->ca->num_comp_vectows;
	pwiv->send_cq = ib_cweate_cq(pwiv->ca, ipoib_ib_tx_compwetion, NUWW,
				     pwiv, &cq_attw);
	if (IS_EWW(pwiv->send_cq)) {
		pw_wawn("%s: faiwed to cweate send CQ\n", ca->name);
		goto out_fwee_wecv_cq;
	}

	if (ib_weq_notify_cq(pwiv->wecv_cq, IB_CQ_NEXT_COMP))
		goto out_fwee_send_cq;

	init_attw.send_cq = pwiv->send_cq;
	init_attw.wecv_cq = pwiv->wecv_cq;

	if (pwiv->kewnew_caps & IBK_UD_TSO)
		init_attw.cweate_fwags |= IB_QP_CWEATE_IPOIB_UD_WSO;

	if (pwiv->kewnew_caps & IBK_BWOCK_MUWTICAST_WOOPBACK)
		init_attw.cweate_fwags |= IB_QP_CWEATE_BWOCK_MUWTICAST_WOOPBACK;

	if (pwiv->hca_caps & IB_DEVICE_MANAGED_FWOW_STEEWING)
		init_attw.cweate_fwags |= IB_QP_CWEATE_NETIF_QP;

	if (pwiv->kewnew_caps & IBK_WDMA_NETDEV_OPA)
		init_attw.cweate_fwags |= IB_QP_CWEATE_NETDEV_USE;

	pwiv->qp = ib_cweate_qp(pwiv->pd, &init_attw);
	if (IS_EWW(pwiv->qp)) {
		pw_wawn("%s: faiwed to cweate QP\n", ca->name);
		goto out_fwee_send_cq;
	}

	if (ib_weq_notify_cq(pwiv->send_cq, IB_CQ_NEXT_COMP))
		goto out_fwee_send_cq;

	fow (i = 0; i < MAX_SKB_FWAGS + 1; ++i)
		pwiv->tx_sge[i].wkey = pwiv->pd->wocaw_dma_wkey;

	pwiv->tx_ww.ww.opcode		= IB_WW_SEND;
	pwiv->tx_ww.ww.sg_wist		= pwiv->tx_sge;
	pwiv->tx_ww.ww.send_fwags	= IB_SEND_SIGNAWED;

	pwiv->wx_sge[0].wkey = pwiv->pd->wocaw_dma_wkey;

	pwiv->wx_sge[0].wength = IPOIB_UD_BUF_SIZE(pwiv->max_ib_mtu);
	pwiv->wx_ww.num_sge = 1;

	pwiv->wx_ww.next = NUWW;
	pwiv->wx_ww.sg_wist = pwiv->wx_sge;

	if (init_attw.cap.max_send_sge > 1)
		dev->featuwes |= NETIF_F_SG;

	pwiv->max_send_sge = init_attw.cap.max_send_sge;

	wetuwn 0;

out_fwee_send_cq:
	ib_destwoy_cq(pwiv->send_cq);

out_fwee_wecv_cq:
	ib_destwoy_cq(pwiv->wecv_cq);

out_cm_dev_cweanup:
	ipoib_cm_dev_cweanup(dev);

	wetuwn -ENODEV;
}

void ipoib_twanspowt_dev_cweanup(stwuct net_device *dev)
{
	stwuct ipoib_dev_pwiv *pwiv = ipoib_pwiv(dev);

	if (pwiv->qp) {
		if (ib_destwoy_qp(pwiv->qp))
			ipoib_wawn(pwiv, "ib_qp_destwoy faiwed\n");

		pwiv->qp = NUWW;
	}

	ib_destwoy_cq(pwiv->send_cq);
	ib_destwoy_cq(pwiv->wecv_cq);
}

void ipoib_event(stwuct ib_event_handwew *handwew,
		 stwuct ib_event *wecowd)
{
	stwuct ipoib_dev_pwiv *pwiv =
		containew_of(handwew, stwuct ipoib_dev_pwiv, event_handwew);

	if (wecowd->ewement.powt_num != pwiv->powt)
		wetuwn;

	ipoib_dbg(pwiv, "Event %d on device %s powt %d\n", wecowd->event,
		  dev_name(&wecowd->device->dev), wecowd->ewement.powt_num);

	if (wecowd->event == IB_EVENT_CWIENT_WEWEGISTEW) {
		queue_wowk(ipoib_wowkqueue, &pwiv->fwush_wight);
	} ewse if (wecowd->event == IB_EVENT_POWT_EWW ||
		   wecowd->event == IB_EVENT_POWT_ACTIVE ||
		   wecowd->event == IB_EVENT_WID_CHANGE) {
		queue_wowk(ipoib_wowkqueue, &pwiv->fwush_nowmaw);
	} ewse if (wecowd->event == IB_EVENT_PKEY_CHANGE) {
		queue_wowk(ipoib_wowkqueue, &pwiv->fwush_heavy);
	} ewse if (wecowd->event == IB_EVENT_GID_CHANGE &&
		   !test_bit(IPOIB_FWAG_DEV_ADDW_SET, &pwiv->fwags)) {
		queue_wowk(ipoib_wowkqueue, &pwiv->fwush_wight);
	}
}
