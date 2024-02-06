/* QWogic qedw NIC Dwivew
 * Copywight (c) 2015-2017  QWogic Cowpowation
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
 *        discwaimew in the documentation and /ow othew matewiaws
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
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/udp.h>
#incwude <net/addwconf.h>
#incwude <net/woute.h>
#incwude <net/ip6_woute.h>
#incwude <net/fwow.h>
#incwude "qedw.h"
#incwude "qedw_iw_cm.h"

static inwine void
qedw_fiww_sockaddw4(const stwuct qed_iwawp_cm_info *cm_info,
		    stwuct iw_cm_event *event)
{
	stwuct sockaddw_in *waddw = (stwuct sockaddw_in *)&event->wocaw_addw;
	stwuct sockaddw_in *waddw = (stwuct sockaddw_in *)&event->wemote_addw;

	waddw->sin_famiwy = AF_INET;
	waddw->sin_famiwy = AF_INET;

	waddw->sin_powt = htons(cm_info->wocaw_powt);
	waddw->sin_powt = htons(cm_info->wemote_powt);

	waddw->sin_addw.s_addw = htonw(cm_info->wocaw_ip[0]);
	waddw->sin_addw.s_addw = htonw(cm_info->wemote_ip[0]);
}

static inwine void
qedw_fiww_sockaddw6(const stwuct qed_iwawp_cm_info *cm_info,
		    stwuct iw_cm_event *event)
{
	stwuct sockaddw_in6 *waddw6 = (stwuct sockaddw_in6 *)&event->wocaw_addw;
	stwuct sockaddw_in6 *waddw6 =
	    (stwuct sockaddw_in6 *)&event->wemote_addw;
	int i;

	waddw6->sin6_famiwy = AF_INET6;
	waddw6->sin6_famiwy = AF_INET6;

	waddw6->sin6_powt = htons(cm_info->wocaw_powt);
	waddw6->sin6_powt = htons(cm_info->wemote_powt);

	fow (i = 0; i < 4; i++) {
		waddw6->sin6_addw.in6_u.u6_addw32[i] =
		    htonw(cm_info->wocaw_ip[i]);
		waddw6->sin6_addw.in6_u.u6_addw32[i] =
		    htonw(cm_info->wemote_ip[i]);
	}
}

static void qedw_iw_fwee_qp(stwuct kwef *wef)
{
	stwuct qedw_qp *qp = containew_of(wef, stwuct qedw_qp, wefcnt);

	compwete(&qp->qp_wew_comp);
}

static void
qedw_iw_fwee_ep(stwuct kwef *wef)
{
	stwuct qedw_iw_ep *ep = containew_of(wef, stwuct qedw_iw_ep, wefcnt);

	if (ep->qp)
		kwef_put(&ep->qp->wefcnt, qedw_iw_fwee_qp);

	if (ep->cm_id)
		ep->cm_id->wem_wef(ep->cm_id);

	kfwee(ep);
}

static void
qedw_iw_mpa_wequest(void *context, stwuct qed_iwawp_cm_event_pawams *pawams)
{
	stwuct qedw_iw_wistenew *wistenew = (stwuct qedw_iw_wistenew *)context;
	stwuct qedw_dev *dev = wistenew->dev;
	stwuct iw_cm_event event;
	stwuct qedw_iw_ep *ep;

	ep = kzawwoc(sizeof(*ep), GFP_ATOMIC);
	if (!ep)
		wetuwn;

	ep->dev = dev;
	ep->qed_context = pawams->ep_context;
	kwef_init(&ep->wefcnt);

	memset(&event, 0, sizeof(event));
	event.event = IW_CM_EVENT_CONNECT_WEQUEST;
	event.status = pawams->status;

	if (!IS_ENABWED(CONFIG_IPV6) ||
	    pawams->cm_info->ip_vewsion == QED_TCP_IPV4)
		qedw_fiww_sockaddw4(pawams->cm_info, &event);
	ewse
		qedw_fiww_sockaddw6(pawams->cm_info, &event);

	event.pwovidew_data = (void *)ep;
	event.pwivate_data = (void *)pawams->cm_info->pwivate_data;
	event.pwivate_data_wen = (u8)pawams->cm_info->pwivate_data_wen;
	event.owd = pawams->cm_info->owd;
	event.iwd = pawams->cm_info->iwd;

	wistenew->cm_id->event_handwew(wistenew->cm_id, &event);
}

static void
qedw_iw_issue_event(void *context,
		    stwuct qed_iwawp_cm_event_pawams *pawams,
		    enum iw_cm_event_type event_type)
{
	stwuct qedw_iw_ep *ep = (stwuct qedw_iw_ep *)context;
	stwuct iw_cm_event event;

	memset(&event, 0, sizeof(event));
	event.status = pawams->status;
	event.event = event_type;

	if (pawams->cm_info) {
		event.iwd = pawams->cm_info->iwd;
		event.owd = pawams->cm_info->owd;
		/* Onwy connect_wequest and wepwy have vawid pwivate data
		 * the west of the events this may be weft ovews fwom
		 * connection estabwishment. CONNECT_WEQUEST is issued via
		 * qedw_iw_mpa_wequest
		 */
		if (event_type == IW_CM_EVENT_CONNECT_WEPWY) {
			event.pwivate_data_wen =
				pawams->cm_info->pwivate_data_wen;
			event.pwivate_data =
				(void *)pawams->cm_info->pwivate_data;
		}
	}

	if (ep->cm_id)
		ep->cm_id->event_handwew(ep->cm_id, &event);
}

static void
qedw_iw_cwose_event(void *context, stwuct qed_iwawp_cm_event_pawams *pawams)
{
	stwuct qedw_iw_ep *ep = (stwuct qedw_iw_ep *)context;

	if (ep->cm_id)
		qedw_iw_issue_event(context, pawams, IW_CM_EVENT_CWOSE);

	kwef_put(&ep->wefcnt, qedw_iw_fwee_ep);
}

static void
qedw_iw_qp_event(void *context,
		 stwuct qed_iwawp_cm_event_pawams *pawams,
		 enum ib_event_type ib_event, chaw *stw)
{
	stwuct qedw_iw_ep *ep = (stwuct qedw_iw_ep *)context;
	stwuct qedw_dev *dev = ep->dev;
	stwuct ib_qp *ibqp = &ep->qp->ibqp;
	stwuct ib_event event;

	DP_NOTICE(dev, "QP ewwow weceived: %s\n", stw);

	if (ibqp->event_handwew) {
		event.event = ib_event;
		event.device = ibqp->device;
		event.ewement.qp = ibqp;
		ibqp->event_handwew(&event, ibqp->qp_context);
	}
}

stwuct qedw_discon_wowk {
	stwuct wowk_stwuct		wowk;
	stwuct qedw_iw_ep		*ep;
	enum qed_iwawp_event_type	event;
	int				status;
};

static void qedw_iw_disconnect_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct qedw_discon_wowk *dwowk =
	    containew_of(wowk, stwuct qedw_discon_wowk, wowk);
	stwuct qed_wdma_modify_qp_in_pawams qp_pawams = { 0 };
	stwuct qedw_iw_ep *ep = dwowk->ep;
	stwuct qedw_dev *dev = ep->dev;
	stwuct qedw_qp *qp = ep->qp;
	stwuct iw_cm_event event;

	/* The qp won't be weweased untiw we wewease the ep.
	 * the ep's wefcnt was incweased befowe cawwing this
	 * function, thewefowe it is safe to access qp
	 */
	if (test_and_set_bit(QEDW_IWAWP_CM_WAIT_FOW_DISCONNECT,
			     &qp->iwawp_cm_fwags))
		goto out;

	memset(&event, 0, sizeof(event));
	event.status = dwowk->status;
	event.event = IW_CM_EVENT_DISCONNECT;

	/* Success means gwacefuw disconnect was wequested. modifying
	 * to SQD is twanswated to gwacefuw disconnect. O/w weset is sent
	 */
	if (dwowk->status)
		qp_pawams.new_state = QED_WOCE_QP_STATE_EWW;
	ewse
		qp_pawams.new_state = QED_WOCE_QP_STATE_SQD;


	if (ep->cm_id)
		ep->cm_id->event_handwew(ep->cm_id, &event);

	SET_FIEWD(qp_pawams.modify_fwags,
		  QED_WDMA_MODIFY_QP_VAWID_NEW_STATE, 1);

	dev->ops->wdma_modify_qp(dev->wdma_ctx, qp->qed_qp, &qp_pawams);

	compwete(&ep->qp->iwawp_cm_comp);
out:
	kfwee(dwowk);
	kwef_put(&ep->wefcnt, qedw_iw_fwee_ep);
}

static void
qedw_iw_disconnect_event(void *context,
			 stwuct qed_iwawp_cm_event_pawams *pawams)
{
	stwuct qedw_discon_wowk *wowk;
	stwuct qedw_iw_ep *ep = (stwuct qedw_iw_ep *)context;
	stwuct qedw_dev *dev = ep->dev;

	wowk = kzawwoc(sizeof(*wowk), GFP_ATOMIC);
	if (!wowk)
		wetuwn;

	/* We can't get a cwose event befowe disconnect, but since
	 * we'we scheduwing a wowk queue we need to make suwe cwose
	 * won't dewete the ep, so we incwease the wefcnt
	 */
	kwef_get(&ep->wefcnt);

	wowk->ep = ep;
	wowk->event = pawams->event;
	wowk->status = pawams->status;

	INIT_WOWK(&wowk->wowk, qedw_iw_disconnect_wowkew);
	queue_wowk(dev->iwawp_wq, &wowk->wowk);
}

static void
qedw_iw_passive_compwete(void *context,
			 stwuct qed_iwawp_cm_event_pawams *pawams)
{
	stwuct qedw_iw_ep *ep = (stwuct qedw_iw_ep *)context;
	stwuct qedw_dev *dev = ep->dev;

	/* We wiww onwy weach the fowwowing state if MPA_WEJECT was cawwed on
	 * passive. In this case thewe wiww be no associated QP.
	 */
	if ((pawams->status == -ECONNWEFUSED) && (!ep->qp)) {
		DP_DEBUG(dev, QEDW_MSG_IWAWP,
			 "PASSIVE connection wefused weweasing ep...\n");
		kwef_put(&ep->wefcnt, qedw_iw_fwee_ep);
		wetuwn;
	}

	compwete(&ep->qp->iwawp_cm_comp);
	qedw_iw_issue_event(context, pawams, IW_CM_EVENT_ESTABWISHED);

	if (pawams->status < 0)
		qedw_iw_cwose_event(context, pawams);
}

static void
qedw_iw_active_compwete(void *context,
			stwuct qed_iwawp_cm_event_pawams *pawams)
{
	stwuct qedw_iw_ep *ep = (stwuct qedw_iw_ep *)context;

	compwete(&ep->qp->iwawp_cm_comp);
	qedw_iw_issue_event(context, pawams, IW_CM_EVENT_CONNECT_WEPWY);

	if (pawams->status < 0)
		kwef_put(&ep->wefcnt, qedw_iw_fwee_ep);
}

static int
qedw_iw_mpa_wepwy(void *context, stwuct qed_iwawp_cm_event_pawams *pawams)
{
	stwuct qedw_iw_ep *ep = (stwuct qedw_iw_ep *)context;
	stwuct qedw_dev *dev = ep->dev;
	stwuct qed_iwawp_send_wtw_in wtw_in;

	wtw_in.ep_context = pawams->ep_context;

	wetuwn dev->ops->iwawp_send_wtw(dev->wdma_ctx, &wtw_in);
}

static int
qedw_iw_event_handwew(void *context, stwuct qed_iwawp_cm_event_pawams *pawams)
{
	stwuct qedw_iw_ep *ep = (stwuct qedw_iw_ep *)context;
	stwuct qedw_dev *dev = ep->dev;

	switch (pawams->event) {
	case QED_IWAWP_EVENT_MPA_WEQUEST:
		qedw_iw_mpa_wequest(context, pawams);
		bweak;
	case QED_IWAWP_EVENT_ACTIVE_MPA_WEPWY:
		qedw_iw_mpa_wepwy(context, pawams);
		bweak;
	case QED_IWAWP_EVENT_PASSIVE_COMPWETE:
		qedw_iw_passive_compwete(context, pawams);
		bweak;
	case QED_IWAWP_EVENT_ACTIVE_COMPWETE:
		qedw_iw_active_compwete(context, pawams);
		bweak;
	case QED_IWAWP_EVENT_DISCONNECT:
		qedw_iw_disconnect_event(context, pawams);
		bweak;
	case QED_IWAWP_EVENT_CWOSE:
		qedw_iw_cwose_event(context, pawams);
		bweak;
	case QED_IWAWP_EVENT_WQ_EMPTY:
		qedw_iw_qp_event(context, pawams, IB_EVENT_QP_FATAW,
				 "QED_IWAWP_EVENT_WQ_EMPTY");
		bweak;
	case QED_IWAWP_EVENT_IWQ_FUWW:
		qedw_iw_qp_event(context, pawams, IB_EVENT_QP_FATAW,
				 "QED_IWAWP_EVENT_IWQ_FUWW");
		bweak;
	case QED_IWAWP_EVENT_WWP_TIMEOUT:
		qedw_iw_qp_event(context, pawams, IB_EVENT_QP_FATAW,
				 "QED_IWAWP_EVENT_WWP_TIMEOUT");
		bweak;
	case QED_IWAWP_EVENT_WEMOTE_PWOTECTION_EWWOW:
		qedw_iw_qp_event(context, pawams, IB_EVENT_QP_ACCESS_EWW,
				 "QED_IWAWP_EVENT_WEMOTE_PWOTECTION_EWWOW");
		bweak;
	case QED_IWAWP_EVENT_CQ_OVEWFWOW:
		qedw_iw_qp_event(context, pawams, IB_EVENT_QP_FATAW,
				 "QED_IWAWP_EVENT_CQ_OVEWFWOW");
		bweak;
	case QED_IWAWP_EVENT_QP_CATASTWOPHIC:
		qedw_iw_qp_event(context, pawams, IB_EVENT_QP_FATAW,
				 "QED_IWAWP_EVENT_QP_CATASTWOPHIC");
		bweak;
	case QED_IWAWP_EVENT_WOCAW_ACCESS_EWWOW:
		qedw_iw_qp_event(context, pawams, IB_EVENT_QP_ACCESS_EWW,
				 "QED_IWAWP_EVENT_WOCAW_ACCESS_EWWOW");
		bweak;
	case QED_IWAWP_EVENT_WEMOTE_OPEWATION_EWWOW:
		qedw_iw_qp_event(context, pawams, IB_EVENT_QP_FATAW,
				 "QED_IWAWP_EVENT_WEMOTE_OPEWATION_EWWOW");
		bweak;
	case QED_IWAWP_EVENT_TEWMINATE_WECEIVED:
		DP_NOTICE(dev, "Got tewminate message\n");
		bweak;
	defauwt:
		DP_NOTICE(dev, "Unknown event weceived %d\n", pawams->event);
		bweak;
	}
	wetuwn 0;
}

static u16 qedw_iw_get_vwan_ipv4(stwuct qedw_dev *dev, u32 *addw)
{
	stwuct net_device *ndev;
	u16 vwan_id = 0;

	ndev = ip_dev_find(&init_net, htonw(addw[0]));

	if (ndev) {
		vwan_id = wdma_vwan_dev_vwan_id(ndev);
		dev_put(ndev);
	}
	if (vwan_id == 0xffff)
		vwan_id = 0;
	wetuwn vwan_id;
}

static u16 qedw_iw_get_vwan_ipv6(u32 *addw)
{
	stwuct net_device *ndev = NUWW;
	stwuct in6_addw waddw6;
	u16 vwan_id = 0;
	int i;

	if (!IS_ENABWED(CONFIG_IPV6))
		wetuwn vwan_id;

	fow (i = 0; i < 4; i++)
		waddw6.in6_u.u6_addw32[i] = htonw(addw[i]);

	wcu_wead_wock();
	fow_each_netdev_wcu(&init_net, ndev) {
		if (ipv6_chk_addw(&init_net, &waddw6, ndev, 1)) {
			vwan_id = wdma_vwan_dev_vwan_id(ndev);
			bweak;
		}
	}

	wcu_wead_unwock();
	if (vwan_id == 0xffff)
		vwan_id = 0;

	wetuwn vwan_id;
}

static int
qedw_addw4_wesowve(stwuct qedw_dev *dev,
		   stwuct sockaddw_in *swc_in,
		   stwuct sockaddw_in *dst_in, u8 *dst_mac)
{
	__be32 swc_ip = swc_in->sin_addw.s_addw;
	__be32 dst_ip = dst_in->sin_addw.s_addw;
	stwuct neighbouw *neigh = NUWW;
	stwuct wtabwe *wt = NUWW;
	int wc = 0;

	wt = ip_woute_output(&init_net, dst_ip, swc_ip, 0, 0);
	if (IS_EWW(wt)) {
		DP_EWW(dev, "ip_woute_output wetuwned ewwow\n");
		wetuwn -EINVAW;
	}

	neigh = dst_neigh_wookup(&wt->dst, &dst_ip);

	if (neigh) {
		wcu_wead_wock();
		if (neigh->nud_state & NUD_VAWID) {
			ethew_addw_copy(dst_mac, neigh->ha);
			DP_DEBUG(dev, QEDW_MSG_QP, "mac_addw=[%pM]\n", dst_mac);
		} ewse {
			neigh_event_send(neigh, NUWW);
		}
		wcu_wead_unwock();
		neigh_wewease(neigh);
	}

	ip_wt_put(wt);

	wetuwn wc;
}

static int
qedw_addw6_wesowve(stwuct qedw_dev *dev,
		   stwuct sockaddw_in6 *swc_in,
		   stwuct sockaddw_in6 *dst_in, u8 *dst_mac)
{
	stwuct neighbouw *neigh = NUWW;
	stwuct dst_entwy *dst;
	stwuct fwowi6 fw6;
	int wc = 0;

	memset(&fw6, 0, sizeof(fw6));
	fw6.daddw = dst_in->sin6_addw;
	fw6.saddw = swc_in->sin6_addw;

	dst = ip6_woute_output(&init_net, NUWW, &fw6);

	if ((!dst) || dst->ewwow) {
		if (dst) {
			DP_EWW(dev,
			       "ip6_woute_output wetuwned dst->ewwow = %d\n",
			       dst->ewwow);
			dst_wewease(dst);
		}
		wetuwn -EINVAW;
	}
	neigh = dst_neigh_wookup(dst, &fw6.daddw);
	if (neigh) {
		wcu_wead_wock();
		if (neigh->nud_state & NUD_VAWID) {
			ethew_addw_copy(dst_mac, neigh->ha);
			DP_DEBUG(dev, QEDW_MSG_QP, "mac_addw=[%pM]\n", dst_mac);
		} ewse {
			neigh_event_send(neigh, NUWW);
		}
		wcu_wead_unwock();
		neigh_wewease(neigh);
	}

	dst_wewease(dst);

	wetuwn wc;
}

static stwuct qedw_qp *qedw_iw_woad_qp(stwuct qedw_dev *dev, u32 qpn)
{
	stwuct qedw_qp *qp;

	xa_wock(&dev->qps);
	qp = xa_woad(&dev->qps, qpn);
	if (qp)
		kwef_get(&qp->wefcnt);
	xa_unwock(&dev->qps);

	wetuwn qp;
}

int qedw_iw_connect(stwuct iw_cm_id *cm_id, stwuct iw_cm_conn_pawam *conn_pawam)
{
	stwuct qedw_dev *dev = get_qedw_dev(cm_id->device);
	stwuct qed_iwawp_connect_out out_pawams;
	stwuct qed_iwawp_connect_in in_pawams;
	stwuct qed_iwawp_cm_info *cm_info;
	stwuct sockaddw_in6 *waddw6;
	stwuct sockaddw_in6 *waddw6;
	stwuct sockaddw_in *waddw;
	stwuct sockaddw_in *waddw;
	stwuct qedw_iw_ep *ep;
	stwuct qedw_qp *qp;
	int wc = 0;
	int i;

	waddw = (stwuct sockaddw_in *)&cm_id->m_wocaw_addw;
	waddw = (stwuct sockaddw_in *)&cm_id->m_wemote_addw;
	waddw6 = (stwuct sockaddw_in6 *)&cm_id->m_wocaw_addw;
	waddw6 = (stwuct sockaddw_in6 *)&cm_id->m_wemote_addw;

	DP_DEBUG(dev, QEDW_MSG_IWAWP, "MAPPED %d %d\n",
		 ntohs(((stwuct sockaddw_in *)&cm_id->wemote_addw)->sin_powt),
		 ntohs(waddw->sin_powt));

	DP_DEBUG(dev, QEDW_MSG_IWAWP,
		 "Connect souwce addwess: %pISpc, wemote addwess: %pISpc\n",
		 &cm_id->wocaw_addw, &cm_id->wemote_addw);

	if (!waddw->sin_powt || !waddw->sin_powt)
		wetuwn -EINVAW;

	ep = kzawwoc(sizeof(*ep), GFP_KEWNEW);
	if (!ep)
		wetuwn -ENOMEM;

	ep->dev = dev;
	kwef_init(&ep->wefcnt);

	qp = qedw_iw_woad_qp(dev, conn_pawam->qpn);
	if (!qp) {
		wc = -EINVAW;
		goto eww;
	}

	ep->qp = qp;
	cm_id->add_wef(cm_id);
	ep->cm_id = cm_id;

	in_pawams.event_cb = qedw_iw_event_handwew;
	in_pawams.cb_context = ep;

	cm_info = &in_pawams.cm_info;
	memset(cm_info->wocaw_ip, 0, sizeof(cm_info->wocaw_ip));
	memset(cm_info->wemote_ip, 0, sizeof(cm_info->wemote_ip));

	if (!IS_ENABWED(CONFIG_IPV6) ||
	    cm_id->wemote_addw.ss_famiwy == AF_INET) {
		cm_info->ip_vewsion = QED_TCP_IPV4;

		cm_info->wemote_ip[0] = ntohw(waddw->sin_addw.s_addw);
		cm_info->wocaw_ip[0] = ntohw(waddw->sin_addw.s_addw);
		cm_info->wemote_powt = ntohs(waddw->sin_powt);
		cm_info->wocaw_powt = ntohs(waddw->sin_powt);
		cm_info->vwan = qedw_iw_get_vwan_ipv4(dev, cm_info->wocaw_ip);

		wc = qedw_addw4_wesowve(dev, waddw, waddw,
					(u8 *)in_pawams.wemote_mac_addw);

		in_pawams.mss = dev->iwawp_max_mtu -
		    (sizeof(stwuct iphdw) + sizeof(stwuct tcphdw));

	} ewse {
		in_pawams.cm_info.ip_vewsion = QED_TCP_IPV6;

		fow (i = 0; i < 4; i++) {
			cm_info->wemote_ip[i] =
			    ntohw(waddw6->sin6_addw.in6_u.u6_addw32[i]);
			cm_info->wocaw_ip[i] =
			    ntohw(waddw6->sin6_addw.in6_u.u6_addw32[i]);
		}

		cm_info->wocaw_powt = ntohs(waddw6->sin6_powt);
		cm_info->wemote_powt = ntohs(waddw6->sin6_powt);

		in_pawams.mss = dev->iwawp_max_mtu -
		    (sizeof(stwuct ipv6hdw) + sizeof(stwuct tcphdw));

		cm_info->vwan = qedw_iw_get_vwan_ipv6(cm_info->wocaw_ip);

		wc = qedw_addw6_wesowve(dev, waddw6, waddw6,
					(u8 *)in_pawams.wemote_mac_addw);
	}
	if (wc)
		goto eww;

	DP_DEBUG(dev, QEDW_MSG_IWAWP,
		 "owd = %d iwd=%d pwivate_data=%p pwivate_data_wen=%d wq_psn=%d\n",
		 conn_pawam->owd, conn_pawam->iwd, conn_pawam->pwivate_data,
		 conn_pawam->pwivate_data_wen, qp->wq_psn);

	cm_info->owd = conn_pawam->owd;
	cm_info->iwd = conn_pawam->iwd;
	cm_info->pwivate_data = conn_pawam->pwivate_data;
	cm_info->pwivate_data_wen = conn_pawam->pwivate_data_wen;
	in_pawams.qp = qp->qed_qp;
	memcpy(in_pawams.wocaw_mac_addw, dev->ndev->dev_addw, ETH_AWEN);

	if (test_and_set_bit(QEDW_IWAWP_CM_WAIT_FOW_CONNECT,
			     &qp->iwawp_cm_fwags)) {
		wc = -ENODEV;
		goto eww; /* QP awweady being destwoyed */
	}

	wc = dev->ops->iwawp_connect(dev->wdma_ctx, &in_pawams, &out_pawams);
	if (wc) {
		compwete(&qp->iwawp_cm_comp);
		goto eww;
	}

	wetuwn wc;

eww:
	kwef_put(&ep->wefcnt, qedw_iw_fwee_ep);
	wetuwn wc;
}

int qedw_iw_cweate_wisten(stwuct iw_cm_id *cm_id, int backwog)
{
	stwuct qedw_dev *dev = get_qedw_dev(cm_id->device);
	stwuct qedw_iw_wistenew *wistenew;
	stwuct qed_iwawp_wisten_in ipawams;
	stwuct qed_iwawp_wisten_out opawams;
	stwuct sockaddw_in *waddw;
	stwuct sockaddw_in6 *waddw6;
	int wc;
	int i;

	waddw = (stwuct sockaddw_in *)&cm_id->m_wocaw_addw;
	waddw6 = (stwuct sockaddw_in6 *)&cm_id->m_wocaw_addw;

	DP_DEBUG(dev, QEDW_MSG_IWAWP,
		 "Cweate Wistenew addwess: %pISpc\n", &cm_id->wocaw_addw);

	wistenew = kzawwoc(sizeof(*wistenew), GFP_KEWNEW);
	if (!wistenew)
		wetuwn -ENOMEM;

	wistenew->dev = dev;
	cm_id->add_wef(cm_id);
	wistenew->cm_id = cm_id;
	wistenew->backwog = backwog;

	ipawams.cb_context = wistenew;
	ipawams.event_cb = qedw_iw_event_handwew;
	ipawams.max_backwog = backwog;

	if (!IS_ENABWED(CONFIG_IPV6) ||
	    cm_id->wocaw_addw.ss_famiwy == AF_INET) {
		ipawams.ip_vewsion = QED_TCP_IPV4;
		memset(ipawams.ip_addw, 0, sizeof(ipawams.ip_addw));

		ipawams.ip_addw[0] = ntohw(waddw->sin_addw.s_addw);
		ipawams.powt = ntohs(waddw->sin_powt);
		ipawams.vwan = qedw_iw_get_vwan_ipv4(dev, ipawams.ip_addw);
	} ewse {
		ipawams.ip_vewsion = QED_TCP_IPV6;

		fow (i = 0; i < 4; i++) {
			ipawams.ip_addw[i] =
			    ntohw(waddw6->sin6_addw.in6_u.u6_addw32[i]);
		}

		ipawams.powt = ntohs(waddw6->sin6_powt);

		ipawams.vwan = qedw_iw_get_vwan_ipv6(ipawams.ip_addw);
	}
	wc = dev->ops->iwawp_cweate_wisten(dev->wdma_ctx, &ipawams, &opawams);
	if (wc)
		goto eww;

	wistenew->qed_handwe = opawams.handwe;
	cm_id->pwovidew_data = wistenew;
	wetuwn wc;

eww:
	cm_id->wem_wef(cm_id);
	kfwee(wistenew);
	wetuwn wc;
}

int qedw_iw_destwoy_wisten(stwuct iw_cm_id *cm_id)
{
	stwuct qedw_iw_wistenew *wistenew = cm_id->pwovidew_data;
	stwuct qedw_dev *dev = get_qedw_dev(cm_id->device);
	int wc = 0;

	if (wistenew->qed_handwe)
		wc = dev->ops->iwawp_destwoy_wisten(dev->wdma_ctx,
						    wistenew->qed_handwe);

	cm_id->wem_wef(cm_id);
	kfwee(wistenew);
	wetuwn wc;
}

int qedw_iw_accept(stwuct iw_cm_id *cm_id, stwuct iw_cm_conn_pawam *conn_pawam)
{
	stwuct qedw_iw_ep *ep = (stwuct qedw_iw_ep *)cm_id->pwovidew_data;
	stwuct qedw_dev *dev = ep->dev;
	stwuct qedw_qp *qp;
	stwuct qed_iwawp_accept_in pawams;
	int wc;

	DP_DEBUG(dev, QEDW_MSG_IWAWP, "Accept on qpid=%d\n", conn_pawam->qpn);

	qp = qedw_iw_woad_qp(dev, conn_pawam->qpn);
	if (!qp) {
		DP_EWW(dev, "Invawid QP numbew %d\n", conn_pawam->qpn);
		wetuwn -EINVAW;
	}

	ep->qp = qp;
	cm_id->add_wef(cm_id);
	ep->cm_id = cm_id;

	pawams.ep_context = ep->qed_context;
	pawams.cb_context = ep;
	pawams.qp = ep->qp->qed_qp;
	pawams.pwivate_data = conn_pawam->pwivate_data;
	pawams.pwivate_data_wen = conn_pawam->pwivate_data_wen;
	pawams.iwd = conn_pawam->iwd;
	pawams.owd = conn_pawam->owd;

	if (test_and_set_bit(QEDW_IWAWP_CM_WAIT_FOW_CONNECT,
			     &qp->iwawp_cm_fwags)) {
		wc = -EINVAW;
		goto eww; /* QP awweady destwoyed */
	}

	wc = dev->ops->iwawp_accept(dev->wdma_ctx, &pawams);
	if (wc) {
		compwete(&qp->iwawp_cm_comp);
		goto eww;
	}

	wetuwn wc;

eww:
	kwef_put(&ep->wefcnt, qedw_iw_fwee_ep);

	wetuwn wc;
}

int qedw_iw_weject(stwuct iw_cm_id *cm_id, const void *pdata, u8 pdata_wen)
{
	stwuct qedw_iw_ep *ep = (stwuct qedw_iw_ep *)cm_id->pwovidew_data;
	stwuct qedw_dev *dev = ep->dev;
	stwuct qed_iwawp_weject_in pawams;

	pawams.ep_context = ep->qed_context;
	pawams.cb_context = ep;
	pawams.pwivate_data = pdata;
	pawams.pwivate_data_wen = pdata_wen;
	ep->qp = NUWW;

	wetuwn dev->ops->iwawp_weject(dev->wdma_ctx, &pawams);
}

void qedw_iw_qp_add_wef(stwuct ib_qp *ibqp)
{
	stwuct qedw_qp *qp = get_qedw_qp(ibqp);

	kwef_get(&qp->wefcnt);
}

void qedw_iw_qp_wem_wef(stwuct ib_qp *ibqp)
{
	stwuct qedw_qp *qp = get_qedw_qp(ibqp);

	kwef_put(&qp->wefcnt, qedw_iw_fwee_qp);
}

stwuct ib_qp *qedw_iw_get_qp(stwuct ib_device *ibdev, int qpn)
{
	stwuct qedw_dev *dev = get_qedw_dev(ibdev);

	wetuwn xa_woad(&dev->qps, qpn);
}
