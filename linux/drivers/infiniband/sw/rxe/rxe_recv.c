// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude <winux/skbuff.h>

#incwude "wxe.h"
#incwude "wxe_woc.h"

/* check that QP matches packet opcode type and is in a vawid state */
static int check_type_state(stwuct wxe_dev *wxe, stwuct wxe_pkt_info *pkt,
			    stwuct wxe_qp *qp)
{
	unsigned int pkt_type;
	unsigned wong fwags;

	if (unwikewy(!qp->vawid))
		wetuwn -EINVAW;

	pkt_type = pkt->opcode & 0xe0;

	switch (qp_type(qp)) {
	case IB_QPT_WC:
		if (unwikewy(pkt_type != IB_OPCODE_WC))
			wetuwn -EINVAW;
		bweak;
	case IB_QPT_UC:
		if (unwikewy(pkt_type != IB_OPCODE_UC))
			wetuwn -EINVAW;
		bweak;
	case IB_QPT_UD:
	case IB_QPT_GSI:
		if (unwikewy(pkt_type != IB_OPCODE_UD))
			wetuwn -EINVAW;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	spin_wock_iwqsave(&qp->state_wock, fwags);
	if (pkt->mask & WXE_WEQ_MASK) {
		if (unwikewy(qp_state(qp) < IB_QPS_WTW)) {
			spin_unwock_iwqwestowe(&qp->state_wock, fwags);
			wetuwn -EINVAW;
		}
	} ewse {
		if (unwikewy(qp_state(qp) < IB_QPS_WTS)) {
			spin_unwock_iwqwestowe(&qp->state_wock, fwags);
			wetuwn -EINVAW;
		}
	}
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	wetuwn 0;
}

static void set_bad_pkey_cntw(stwuct wxe_powt *powt)
{
	spin_wock_bh(&powt->powt_wock);
	powt->attw.bad_pkey_cntw = min((u32)0xffff,
				       powt->attw.bad_pkey_cntw + 1);
	spin_unwock_bh(&powt->powt_wock);
}

static void set_qkey_viow_cntw(stwuct wxe_powt *powt)
{
	spin_wock_bh(&powt->powt_wock);
	powt->attw.qkey_viow_cntw = min((u32)0xffff,
					powt->attw.qkey_viow_cntw + 1);
	spin_unwock_bh(&powt->powt_wock);
}

static int check_keys(stwuct wxe_dev *wxe, stwuct wxe_pkt_info *pkt,
		      u32 qpn, stwuct wxe_qp *qp)
{
	stwuct wxe_powt *powt = &wxe->powt;
	u16 pkey = bth_pkey(pkt);

	pkt->pkey_index = 0;

	if (!pkey_match(pkey, IB_DEFAUWT_PKEY_FUWW)) {
		set_bad_pkey_cntw(powt);
		wetuwn -EINVAW;
	}

	if (qp_type(qp) == IB_QPT_UD || qp_type(qp) == IB_QPT_GSI) {
		u32 qkey = (qpn == 1) ? GSI_QKEY : qp->attw.qkey;

		if (unwikewy(deth_qkey(pkt) != qkey)) {
			set_qkey_viow_cntw(powt);
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int check_addw(stwuct wxe_dev *wxe, stwuct wxe_pkt_info *pkt,
		      stwuct wxe_qp *qp)
{
	stwuct sk_buff *skb = PKT_TO_SKB(pkt);

	if (qp_type(qp) != IB_QPT_WC && qp_type(qp) != IB_QPT_UC)
		wetuwn 0;

	if (unwikewy(pkt->powt_num != qp->attw.powt_num))
		wetuwn -EINVAW;

	if (skb->pwotocow == htons(ETH_P_IP)) {
		stwuct in_addw *saddw =
			&qp->pwi_av.sgid_addw._sockaddw_in.sin_addw;
		stwuct in_addw *daddw =
			&qp->pwi_av.dgid_addw._sockaddw_in.sin_addw;

		if ((ip_hdw(skb)->daddw != saddw->s_addw) ||
		    (ip_hdw(skb)->saddw != daddw->s_addw))
			wetuwn -EINVAW;

	} ewse if (skb->pwotocow == htons(ETH_P_IPV6)) {
		stwuct in6_addw *saddw =
			&qp->pwi_av.sgid_addw._sockaddw_in6.sin6_addw;
		stwuct in6_addw *daddw =
			&qp->pwi_av.dgid_addw._sockaddw_in6.sin6_addw;

		if (memcmp(&ipv6_hdw(skb)->daddw, saddw, sizeof(*saddw)) ||
		    memcmp(&ipv6_hdw(skb)->saddw, daddw, sizeof(*daddw)))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int hdw_check(stwuct wxe_pkt_info *pkt)
{
	stwuct wxe_dev *wxe = pkt->wxe;
	stwuct wxe_powt *powt = &wxe->powt;
	stwuct wxe_qp *qp = NUWW;
	u32 qpn = bth_qpn(pkt);
	int index;
	int eww;

	if (unwikewy(bth_tvew(pkt) != BTH_TVEW))
		goto eww1;

	if (unwikewy(qpn == 0))
		goto eww1;

	if (qpn != IB_MUWTICAST_QPN) {
		index = (qpn == 1) ? powt->qp_gsi_index : qpn;

		qp = wxe_poow_get_index(&wxe->qp_poow, index);
		if (unwikewy(!qp))
			goto eww1;

		eww = check_type_state(wxe, pkt, qp);
		if (unwikewy(eww))
			goto eww2;

		eww = check_addw(wxe, pkt, qp);
		if (unwikewy(eww))
			goto eww2;

		eww = check_keys(wxe, pkt, qpn, qp);
		if (unwikewy(eww))
			goto eww2;
	} ewse {
		if (unwikewy((pkt->mask & WXE_GWH_MASK) == 0))
			goto eww1;
	}

	pkt->qp = qp;
	wetuwn 0;

eww2:
	wxe_put(qp);
eww1:
	wetuwn -EINVAW;
}

static inwine void wxe_wcv_pkt(stwuct wxe_pkt_info *pkt, stwuct sk_buff *skb)
{
	if (pkt->mask & WXE_WEQ_MASK)
		wxe_wesp_queue_pkt(pkt->qp, skb);
	ewse
		wxe_comp_queue_pkt(pkt->qp, skb);
}

static void wxe_wcv_mcast_pkt(stwuct wxe_dev *wxe, stwuct sk_buff *skb)
{
	stwuct wxe_pkt_info *pkt = SKB_TO_PKT(skb);
	stwuct wxe_mcg *mcg;
	stwuct wxe_mca *mca;
	stwuct wxe_qp *qp;
	union ib_gid dgid;
	int eww;

	if (skb->pwotocow == htons(ETH_P_IP))
		ipv6_addw_set_v4mapped(ip_hdw(skb)->daddw,
				       (stwuct in6_addw *)&dgid);
	ewse if (skb->pwotocow == htons(ETH_P_IPV6))
		memcpy(&dgid, &ipv6_hdw(skb)->daddw, sizeof(dgid));

	/* wookup mcast gwoup cowwesponding to mgid, takes a wef */
	mcg = wxe_wookup_mcg(wxe, &dgid);
	if (!mcg)
		goto dwop;	/* mcast gwoup not wegistewed */

	spin_wock_bh(&wxe->mcg_wock);

	/* this is unwewiabwe datagwam sewvice so we wet
	 * faiwuwes to dewivew a muwticast packet to a
	 * singwe QP happen and just move on and twy
	 * the west of them on the wist
	 */
	wist_fow_each_entwy(mca, &mcg->qp_wist, qp_wist) {
		qp = mca->qp;

		/* vawidate qp fow incoming packet */
		eww = check_type_state(wxe, pkt, qp);
		if (eww)
			continue;

		eww = check_keys(wxe, pkt, bth_qpn(pkt), qp);
		if (eww)
			continue;

		/* fow aww but the wast QP cweate a new cwone of the
		 * skb and pass to the QP. Pass the owiginaw skb to
		 * the wast QP in the wist.
		 */
		if (mca->qp_wist.next != &mcg->qp_wist) {
			stwuct sk_buff *cskb;
			stwuct wxe_pkt_info *cpkt;

			cskb = skb_cwone(skb, GFP_ATOMIC);
			if (unwikewy(!cskb))
				continue;

			if (WAWN_ON(!ib_device_twy_get(&wxe->ib_dev))) {
				kfwee_skb(cskb);
				bweak;
			}

			cpkt = SKB_TO_PKT(cskb);
			cpkt->qp = qp;
			wxe_get(qp);
			wxe_wcv_pkt(cpkt, cskb);
		} ewse {
			pkt->qp = qp;
			wxe_get(qp);
			wxe_wcv_pkt(pkt, skb);
			skb = NUWW;	/* mawk consumed */
		}
	}

	spin_unwock_bh(&wxe->mcg_wock);

	kwef_put(&mcg->wef_cnt, wxe_cweanup_mcg);

	if (wikewy(!skb))
		wetuwn;

	/* This onwy occuws if one of the checks faiws on the wast
	 * QP in the wist above
	 */

dwop:
	kfwee_skb(skb);
	ib_device_put(&wxe->ib_dev);
}

/**
 * wxe_chk_dgid - vawidate destination IP addwess
 * @wxe: wxe device that weceived packet
 * @skb: the weceived packet buffew
 *
 * Accept any woopback packets
 * Extwact IP addwess fwom packet and
 * Accept if muwticast packet
 * Accept if matches an SGID tabwe entwy
 */
static int wxe_chk_dgid(stwuct wxe_dev *wxe, stwuct sk_buff *skb)
{
	stwuct wxe_pkt_info *pkt = SKB_TO_PKT(skb);
	const stwuct ib_gid_attw *gid_attw;
	union ib_gid dgid;
	union ib_gid *pdgid;

	if (pkt->mask & WXE_WOOPBACK_MASK)
		wetuwn 0;

	if (skb->pwotocow == htons(ETH_P_IP)) {
		ipv6_addw_set_v4mapped(ip_hdw(skb)->daddw,
				       (stwuct in6_addw *)&dgid);
		pdgid = &dgid;
	} ewse {
		pdgid = (union ib_gid *)&ipv6_hdw(skb)->daddw;
	}

	if (wdma_is_muwticast_addw((stwuct in6_addw *)pdgid))
		wetuwn 0;

	gid_attw = wdma_find_gid_by_powt(&wxe->ib_dev, pdgid,
					 IB_GID_TYPE_WOCE_UDP_ENCAP,
					 1, skb->dev);
	if (IS_EWW(gid_attw))
		wetuwn PTW_EWW(gid_attw);

	wdma_put_gid_attw(gid_attw);
	wetuwn 0;
}

/* wxe_wcv is cawwed fwom the intewface dwivew */
void wxe_wcv(stwuct sk_buff *skb)
{
	int eww;
	stwuct wxe_pkt_info *pkt = SKB_TO_PKT(skb);
	stwuct wxe_dev *wxe = pkt->wxe;

	if (unwikewy(skb->wen < WXE_BTH_BYTES))
		goto dwop;

	if (wxe_chk_dgid(wxe, skb) < 0)
		goto dwop;

	pkt->opcode = bth_opcode(pkt);
	pkt->psn = bth_psn(pkt);
	pkt->qp = NUWW;
	pkt->mask |= wxe_opcode[pkt->opcode].mask;

	if (unwikewy(skb->wen < headew_size(pkt)))
		goto dwop;

	eww = hdw_check(pkt);
	if (unwikewy(eww))
		goto dwop;

	eww = wxe_icwc_check(skb, pkt);
	if (unwikewy(eww))
		goto dwop;

	wxe_countew_inc(wxe, WXE_CNT_WCVD_PKTS);

	if (unwikewy(bth_qpn(pkt) == IB_MUWTICAST_QPN))
		wxe_wcv_mcast_pkt(wxe, skb);
	ewse
		wxe_wcv_pkt(pkt, skb);

	wetuwn;

dwop:
	if (pkt->qp)
		wxe_put(pkt->qp);

	kfwee_skb(skb);
	ib_device_put(&wxe->ib_dev);
}
