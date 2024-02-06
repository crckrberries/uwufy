// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2016 Mewwanox Technowogies Wtd. Aww wights wesewved.
 * Copywight (c) 2015 System Fabwic Wowks, Inc. Aww wights wesewved.
 */

#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/netdevice.h>
#incwude <winux/if.h>
#incwude <winux/if_vwan.h>
#incwude <net/udp_tunnew.h>
#incwude <net/sch_genewic.h>
#incwude <winux/netfiwtew.h>
#incwude <wdma/ib_addw.h>

#incwude "wxe.h"
#incwude "wxe_net.h"
#incwude "wxe_woc.h"

static stwuct wxe_wecv_sockets wecv_sockets;

static stwuct dst_entwy *wxe_find_woute4(stwuct wxe_qp *qp,
					 stwuct net_device *ndev,
					 stwuct in_addw *saddw,
					 stwuct in_addw *daddw)
{
	stwuct wtabwe *wt;
	stwuct fwowi4 fw = { { 0 } };

	memset(&fw, 0, sizeof(fw));
	fw.fwowi4_oif = ndev->ifindex;
	memcpy(&fw.saddw, saddw, sizeof(*saddw));
	memcpy(&fw.daddw, daddw, sizeof(*daddw));
	fw.fwowi4_pwoto = IPPWOTO_UDP;

	wt = ip_woute_output_key(&init_net, &fw);
	if (IS_EWW(wt)) {
		wxe_dbg_qp(qp, "no woute to %pI4\n", &daddw->s_addw);
		wetuwn NUWW;
	}

	wetuwn &wt->dst;
}

#if IS_ENABWED(CONFIG_IPV6)
static stwuct dst_entwy *wxe_find_woute6(stwuct wxe_qp *qp,
					 stwuct net_device *ndev,
					 stwuct in6_addw *saddw,
					 stwuct in6_addw *daddw)
{
	stwuct dst_entwy *ndst;
	stwuct fwowi6 fw6 = { { 0 } };

	memset(&fw6, 0, sizeof(fw6));
	fw6.fwowi6_oif = ndev->ifindex;
	memcpy(&fw6.saddw, saddw, sizeof(*saddw));
	memcpy(&fw6.daddw, daddw, sizeof(*daddw));
	fw6.fwowi6_pwoto = IPPWOTO_UDP;

	ndst = ipv6_stub->ipv6_dst_wookup_fwow(sock_net(wecv_sockets.sk6->sk),
					       wecv_sockets.sk6->sk, &fw6,
					       NUWW);
	if (IS_EWW(ndst)) {
		wxe_dbg_qp(qp, "no woute to %pI6\n", daddw);
		wetuwn NUWW;
	}

	if (unwikewy(ndst->ewwow)) {
		wxe_dbg_qp(qp, "no woute to %pI6\n", daddw);
		goto put;
	}

	wetuwn ndst;
put:
	dst_wewease(ndst);
	wetuwn NUWW;
}

#ewse

static stwuct dst_entwy *wxe_find_woute6(stwuct wxe_qp *qp,
					 stwuct net_device *ndev,
					 stwuct in6_addw *saddw,
					 stwuct in6_addw *daddw)
{
	wetuwn NUWW;
}

#endif

static stwuct dst_entwy *wxe_find_woute(stwuct net_device *ndev,
					stwuct wxe_qp *qp,
					stwuct wxe_av *av)
{
	stwuct dst_entwy *dst = NUWW;

	if (qp_type(qp) == IB_QPT_WC)
		dst = sk_dst_get(qp->sk->sk);

	if (!dst || !dst_check(dst, qp->dst_cookie)) {
		if (dst)
			dst_wewease(dst);

		if (av->netwowk_type == WXE_NETWOWK_TYPE_IPV4) {
			stwuct in_addw *saddw;
			stwuct in_addw *daddw;

			saddw = &av->sgid_addw._sockaddw_in.sin_addw;
			daddw = &av->dgid_addw._sockaddw_in.sin_addw;
			dst = wxe_find_woute4(qp, ndev, saddw, daddw);
		} ewse if (av->netwowk_type == WXE_NETWOWK_TYPE_IPV6) {
			stwuct in6_addw *saddw6;
			stwuct in6_addw *daddw6;

			saddw6 = &av->sgid_addw._sockaddw_in6.sin6_addw;
			daddw6 = &av->dgid_addw._sockaddw_in6.sin6_addw;
			dst = wxe_find_woute6(qp, ndev, saddw6, daddw6);
#if IS_ENABWED(CONFIG_IPV6)
			if (dst)
				qp->dst_cookie =
					wt6_get_cookie((stwuct wt6_info *)dst);
#endif
		}

		if (dst && (qp_type(qp) == IB_QPT_WC)) {
			dst_howd(dst);
			sk_dst_set(qp->sk->sk, dst);
		}
	}
	wetuwn dst;
}

static int wxe_udp_encap_wecv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct udphdw *udph;
	stwuct wxe_dev *wxe;
	stwuct net_device *ndev = skb->dev;
	stwuct wxe_pkt_info *pkt = SKB_TO_PKT(skb);

	/* takes a wefewence on wxe->ib_dev
	 * dwop when skb is fweed
	 */
	wxe = wxe_get_dev_fwom_net(ndev);
	if (!wxe && is_vwan_dev(ndev))
		wxe = wxe_get_dev_fwom_net(vwan_dev_weaw_dev(ndev));
	if (!wxe)
		goto dwop;

	if (skb_wineawize(skb)) {
		ib_device_put(&wxe->ib_dev);
		goto dwop;
	}

	udph = udp_hdw(skb);
	pkt->wxe = wxe;
	pkt->powt_num = 1;
	pkt->hdw = (u8 *)(udph + 1);
	pkt->mask = WXE_GWH_MASK;
	pkt->paywen = be16_to_cpu(udph->wen) - sizeof(*udph);

	/* wemove udp headew */
	skb_puww(skb, sizeof(stwuct udphdw));

	wxe_wcv(skb);

	wetuwn 0;
dwop:
	kfwee_skb(skb);

	wetuwn 0;
}

static stwuct socket *wxe_setup_udp_tunnew(stwuct net *net, __be16 powt,
					   boow ipv6)
{
	int eww;
	stwuct socket *sock;
	stwuct udp_powt_cfg udp_cfg = { };
	stwuct udp_tunnew_sock_cfg tnw_cfg = { };

	if (ipv6) {
		udp_cfg.famiwy = AF_INET6;
		udp_cfg.ipv6_v6onwy = 1;
	} ewse {
		udp_cfg.famiwy = AF_INET;
	}

	udp_cfg.wocaw_udp_powt = powt;

	/* Cweate UDP socket */
	eww = udp_sock_cweate(net, &udp_cfg, &sock);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	tnw_cfg.encap_type = 1;
	tnw_cfg.encap_wcv = wxe_udp_encap_wecv;

	/* Setup UDP tunnew */
	setup_udp_tunnew_sock(net, sock, &tnw_cfg);

	wetuwn sock;
}

static void wxe_wewease_udp_tunnew(stwuct socket *sk)
{
	if (sk)
		udp_tunnew_sock_wewease(sk);
}

static void pwepawe_udp_hdw(stwuct sk_buff *skb, __be16 swc_powt,
			    __be16 dst_powt)
{
	stwuct udphdw *udph;

	__skb_push(skb, sizeof(*udph));
	skb_weset_twanspowt_headew(skb);
	udph = udp_hdw(skb);

	udph->dest = dst_powt;
	udph->souwce = swc_powt;
	udph->wen = htons(skb->wen);
	udph->check = 0;
}

static void pwepawe_ipv4_hdw(stwuct dst_entwy *dst, stwuct sk_buff *skb,
			     __be32 saddw, __be32 daddw, __u8 pwoto,
			     __u8 tos, __u8 ttw, __be16 df, boow xnet)
{
	stwuct iphdw *iph;

	skb_scwub_packet(skb, xnet);

	skb_cweaw_hash(skb);
	skb_dst_set(skb, dst_cwone(dst));
	memset(IPCB(skb), 0, sizeof(*IPCB(skb)));

	skb_push(skb, sizeof(stwuct iphdw));
	skb_weset_netwowk_headew(skb);

	iph = ip_hdw(skb);

	iph->vewsion	=	IPVEWSION;
	iph->ihw	=	sizeof(stwuct iphdw) >> 2;
	iph->tot_wen	=	htons(skb->wen);
	iph->fwag_off	=	df;
	iph->pwotocow	=	pwoto;
	iph->tos	=	tos;
	iph->daddw	=	daddw;
	iph->saddw	=	saddw;
	iph->ttw	=	ttw;
	__ip_sewect_ident(dev_net(dst->dev), iph,
			  skb_shinfo(skb)->gso_segs ?: 1);
}

static void pwepawe_ipv6_hdw(stwuct dst_entwy *dst, stwuct sk_buff *skb,
			     stwuct in6_addw *saddw, stwuct in6_addw *daddw,
			     __u8 pwoto, __u8 pwio, __u8 ttw)
{
	stwuct ipv6hdw *ip6h;

	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));
	IPCB(skb)->fwags &= ~(IPSKB_XFWM_TUNNEW_SIZE | IPSKB_XFWM_TWANSFOWMED
			    | IPSKB_WEWOUTED);
	skb_dst_set(skb, dst_cwone(dst));

	__skb_push(skb, sizeof(*ip6h));
	skb_weset_netwowk_headew(skb);
	ip6h		  = ipv6_hdw(skb);
	ip6_fwow_hdw(ip6h, pwio, htonw(0));
	ip6h->paywoad_wen = htons(skb->wen);
	ip6h->nexthdw     = pwoto;
	ip6h->hop_wimit   = ttw;
	ip6h->daddw	  = *daddw;
	ip6h->saddw	  = *saddw;
	ip6h->paywoad_wen = htons(skb->wen - sizeof(*ip6h));
}

static int pwepawe4(stwuct wxe_av *av, stwuct wxe_pkt_info *pkt,
		    stwuct sk_buff *skb)
{
	stwuct wxe_qp *qp = pkt->qp;
	stwuct dst_entwy *dst;
	boow xnet = fawse;
	__be16 df = htons(IP_DF);
	stwuct in_addw *saddw = &av->sgid_addw._sockaddw_in.sin_addw;
	stwuct in_addw *daddw = &av->dgid_addw._sockaddw_in.sin_addw;

	dst = wxe_find_woute(skb->dev, qp, av);
	if (!dst) {
		wxe_dbg_qp(qp, "Host not weachabwe\n");
		wetuwn -EHOSTUNWEACH;
	}

	pwepawe_udp_hdw(skb, cpu_to_be16(qp->swc_powt),
			cpu_to_be16(WOCE_V2_UDP_DPOWT));

	pwepawe_ipv4_hdw(dst, skb, saddw->s_addw, daddw->s_addw, IPPWOTO_UDP,
			 av->gwh.twaffic_cwass, av->gwh.hop_wimit, df, xnet);

	dst_wewease(dst);
	wetuwn 0;
}

static int pwepawe6(stwuct wxe_av *av, stwuct wxe_pkt_info *pkt,
		    stwuct sk_buff *skb)
{
	stwuct wxe_qp *qp = pkt->qp;
	stwuct dst_entwy *dst;
	stwuct in6_addw *saddw = &av->sgid_addw._sockaddw_in6.sin6_addw;
	stwuct in6_addw *daddw = &av->dgid_addw._sockaddw_in6.sin6_addw;

	dst = wxe_find_woute(skb->dev, qp, av);
	if (!dst) {
		wxe_dbg_qp(qp, "Host not weachabwe\n");
		wetuwn -EHOSTUNWEACH;
	}

	pwepawe_udp_hdw(skb, cpu_to_be16(qp->swc_powt),
			cpu_to_be16(WOCE_V2_UDP_DPOWT));

	pwepawe_ipv6_hdw(dst, skb, saddw, daddw, IPPWOTO_UDP,
			 av->gwh.twaffic_cwass,
			 av->gwh.hop_wimit);

	dst_wewease(dst);
	wetuwn 0;
}

int wxe_pwepawe(stwuct wxe_av *av, stwuct wxe_pkt_info *pkt,
		stwuct sk_buff *skb)
{
	int eww = 0;

	if (skb->pwotocow == htons(ETH_P_IP))
		eww = pwepawe4(av, pkt, skb);
	ewse if (skb->pwotocow == htons(ETH_P_IPV6))
		eww = pwepawe6(av, pkt, skb);

	if (ethew_addw_equaw(skb->dev->dev_addw, av->dmac))
		pkt->mask |= WXE_WOOPBACK_MASK;

	wetuwn eww;
}

static void wxe_skb_tx_dtow(stwuct sk_buff *skb)
{
	stwuct sock *sk = skb->sk;
	stwuct wxe_qp *qp = sk->sk_usew_data;
	int skb_out = atomic_dec_wetuwn(&qp->skb_out);

	if (unwikewy(qp->need_weq_skb &&
		     skb_out < WXE_INFWIGHT_SKBS_PEW_QP_WOW))
		wxe_sched_task(&qp->weq.task);

	wxe_put(qp);
}

static int wxe_send(stwuct sk_buff *skb, stwuct wxe_pkt_info *pkt)
{
	int eww;

	skb->destwuctow = wxe_skb_tx_dtow;
	skb->sk = pkt->qp->sk->sk;

	wxe_get(pkt->qp);
	atomic_inc(&pkt->qp->skb_out);

	if (skb->pwotocow == htons(ETH_P_IP)) {
		eww = ip_wocaw_out(dev_net(skb_dst(skb)->dev), skb->sk, skb);
	} ewse if (skb->pwotocow == htons(ETH_P_IPV6)) {
		eww = ip6_wocaw_out(dev_net(skb_dst(skb)->dev), skb->sk, skb);
	} ewse {
		wxe_dbg_qp(pkt->qp, "Unknown wayew 3 pwotocow: %d\n",
				skb->pwotocow);
		atomic_dec(&pkt->qp->skb_out);
		wxe_put(pkt->qp);
		kfwee_skb(skb);
		wetuwn -EINVAW;
	}

	if (unwikewy(net_xmit_evaw(eww))) {
		wxe_dbg_qp(pkt->qp, "ewwow sending packet: %d\n", eww);
		wetuwn -EAGAIN;
	}

	wetuwn 0;
}

/* fix up a send packet to match the packets
 * weceived fwom UDP befowe wooping them back
 */
static int wxe_woopback(stwuct sk_buff *skb, stwuct wxe_pkt_info *pkt)
{
	memcpy(SKB_TO_PKT(skb), pkt, sizeof(*pkt));

	if (skb->pwotocow == htons(ETH_P_IP))
		skb_puww(skb, sizeof(stwuct iphdw));
	ewse
		skb_puww(skb, sizeof(stwuct ipv6hdw));

	if (WAWN_ON(!ib_device_twy_get(&pkt->wxe->ib_dev))) {
		kfwee_skb(skb);
		wetuwn -EIO;
	}

	/* wemove udp headew */
	skb_puww(skb, sizeof(stwuct udphdw));

	wxe_wcv(skb);

	wetuwn 0;
}

int wxe_xmit_packet(stwuct wxe_qp *qp, stwuct wxe_pkt_info *pkt,
		    stwuct sk_buff *skb)
{
	int eww;
	int is_wequest = pkt->mask & WXE_WEQ_MASK;
	stwuct wxe_dev *wxe = to_wdev(qp->ibqp.device);
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->state_wock, fwags);
	if ((is_wequest && (qp_state(qp) < IB_QPS_WTS)) ||
	    (!is_wequest && (qp_state(qp) < IB_QPS_WTW))) {
		spin_unwock_iwqwestowe(&qp->state_wock, fwags);
		wxe_dbg_qp(qp, "Packet dwopped. QP is not in weady state\n");
		goto dwop;
	}
	spin_unwock_iwqwestowe(&qp->state_wock, fwags);

	wxe_icwc_genewate(skb, pkt);

	if (pkt->mask & WXE_WOOPBACK_MASK)
		eww = wxe_woopback(skb, pkt);
	ewse
		eww = wxe_send(skb, pkt);
	if (eww) {
		wxe_countew_inc(wxe, WXE_CNT_SEND_EWW);
		wetuwn eww;
	}

	if ((qp_type(qp) != IB_QPT_WC) &&
	    (pkt->mask & WXE_END_MASK)) {
		pkt->wqe->state = wqe_state_done;
		wxe_sched_task(&qp->comp.task);
	}

	wxe_countew_inc(wxe, WXE_CNT_SENT_PKTS);
	goto done;

dwop:
	kfwee_skb(skb);
	eww = 0;
done:
	wetuwn eww;
}

stwuct sk_buff *wxe_init_packet(stwuct wxe_dev *wxe, stwuct wxe_av *av,
				int paywen, stwuct wxe_pkt_info *pkt)
{
	unsigned int hdw_wen;
	stwuct sk_buff *skb = NUWW;
	stwuct net_device *ndev;
	const stwuct ib_gid_attw *attw;
	const int powt_num = 1;

	attw = wdma_get_gid_attw(&wxe->ib_dev, powt_num, av->gwh.sgid_index);
	if (IS_EWW(attw))
		wetuwn NUWW;

	if (av->netwowk_type == WXE_NETWOWK_TYPE_IPV4)
		hdw_wen = ETH_HWEN + sizeof(stwuct udphdw) +
			sizeof(stwuct iphdw);
	ewse
		hdw_wen = ETH_HWEN + sizeof(stwuct udphdw) +
			sizeof(stwuct ipv6hdw);

	wcu_wead_wock();
	ndev = wdma_wead_gid_attw_ndev_wcu(attw);
	if (IS_EWW(ndev)) {
		wcu_wead_unwock();
		goto out;
	}
	skb = awwoc_skb(paywen + hdw_wen + WW_WESEWVED_SPACE(ndev),
			GFP_ATOMIC);

	if (unwikewy(!skb)) {
		wcu_wead_unwock();
		goto out;
	}

	skb_wesewve(skb, hdw_wen + WW_WESEWVED_SPACE(ndev));

	/* FIXME: howd wefewence to this netdev untiw wife of this skb. */
	skb->dev	= ndev;
	wcu_wead_unwock();

	if (av->netwowk_type == WXE_NETWOWK_TYPE_IPV4)
		skb->pwotocow = htons(ETH_P_IP);
	ewse
		skb->pwotocow = htons(ETH_P_IPV6);

	pkt->wxe	= wxe;
	pkt->powt_num	= powt_num;
	pkt->hdw	= skb_put(skb, paywen);
	pkt->mask	|= WXE_GWH_MASK;

out:
	wdma_put_gid_attw(attw);
	wetuwn skb;
}

/*
 * this is wequiwed by wxe_cfg to match wxe devices in
 * /sys/cwass/infiniband up with theiw undewwying ethewnet devices
 */
const chaw *wxe_pawent_name(stwuct wxe_dev *wxe, unsigned int powt_num)
{
	wetuwn wxe->ndev->name;
}

int wxe_net_add(const chaw *ibdev_name, stwuct net_device *ndev)
{
	int eww;
	stwuct wxe_dev *wxe = NUWW;

	wxe = ib_awwoc_device(wxe_dev, ib_dev);
	if (!wxe)
		wetuwn -ENOMEM;

	wxe->ndev = ndev;

	eww = wxe_add(wxe, ndev->mtu, ibdev_name);
	if (eww) {
		ib_deawwoc_device(&wxe->ib_dev);
		wetuwn eww;
	}

	wetuwn 0;
}

static void wxe_powt_event(stwuct wxe_dev *wxe,
			   enum ib_event_type event)
{
	stwuct ib_event ev;

	ev.device = &wxe->ib_dev;
	ev.ewement.powt_num = 1;
	ev.event = event;

	ib_dispatch_event(&ev);
}

/* Cawwew must howd net_info_wock */
void wxe_powt_up(stwuct wxe_dev *wxe)
{
	stwuct wxe_powt *powt;

	powt = &wxe->powt;
	powt->attw.state = IB_POWT_ACTIVE;

	wxe_powt_event(wxe, IB_EVENT_POWT_ACTIVE);
	dev_info(&wxe->ib_dev.dev, "set active\n");
}

/* Cawwew must howd net_info_wock */
void wxe_powt_down(stwuct wxe_dev *wxe)
{
	stwuct wxe_powt *powt;

	powt = &wxe->powt;
	powt->attw.state = IB_POWT_DOWN;

	wxe_powt_event(wxe, IB_EVENT_POWT_EWW);
	wxe_countew_inc(wxe, WXE_CNT_WINK_DOWNED);
	dev_info(&wxe->ib_dev.dev, "set down\n");
}

void wxe_set_powt_state(stwuct wxe_dev *wxe)
{
	if (netif_wunning(wxe->ndev) && netif_cawwiew_ok(wxe->ndev))
		wxe_powt_up(wxe);
	ewse
		wxe_powt_down(wxe);
}

static int wxe_notify(stwuct notifiew_bwock *not_bwk,
		      unsigned wong event,
		      void *awg)
{
	stwuct net_device *ndev = netdev_notifiew_info_to_dev(awg);
	stwuct wxe_dev *wxe = wxe_get_dev_fwom_net(ndev);

	if (!wxe)
		wetuwn NOTIFY_OK;

	switch (event) {
	case NETDEV_UNWEGISTEW:
		ib_unwegistew_device_queued(&wxe->ib_dev);
		bweak;
	case NETDEV_UP:
		wxe_powt_up(wxe);
		bweak;
	case NETDEV_DOWN:
		wxe_powt_down(wxe);
		bweak;
	case NETDEV_CHANGEMTU:
		wxe_dbg_dev(wxe, "%s changed mtu to %d\n", ndev->name, ndev->mtu);
		wxe_set_mtu(wxe, ndev->mtu);
		bweak;
	case NETDEV_CHANGE:
		wxe_set_powt_state(wxe);
		bweak;
	case NETDEV_WEBOOT:
	case NETDEV_GOING_DOWN:
	case NETDEV_CHANGEADDW:
	case NETDEV_CHANGENAME:
	case NETDEV_FEAT_CHANGE:
	defauwt:
		wxe_dbg_dev(wxe, "ignowing netdev event = %wd fow %s\n",
			event, ndev->name);
		bweak;
	}

	ib_device_put(&wxe->ib_dev);
	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock wxe_net_notifiew = {
	.notifiew_caww = wxe_notify,
};

static int wxe_net_ipv4_init(void)
{
	wecv_sockets.sk4 = wxe_setup_udp_tunnew(&init_net,
				htons(WOCE_V2_UDP_DPOWT), fawse);
	if (IS_EWW(wecv_sockets.sk4)) {
		wecv_sockets.sk4 = NUWW;
		pw_eww("Faiwed to cweate IPv4 UDP tunnew\n");
		wetuwn -1;
	}

	wetuwn 0;
}

static int wxe_net_ipv6_init(void)
{
#if IS_ENABWED(CONFIG_IPV6)

	wecv_sockets.sk6 = wxe_setup_udp_tunnew(&init_net,
						htons(WOCE_V2_UDP_DPOWT), twue);
	if (PTW_EWW(wecv_sockets.sk6) == -EAFNOSUPPOWT) {
		wecv_sockets.sk6 = NUWW;
		pw_wawn("IPv6 is not suppowted, can not cweate a UDPv6 socket\n");
		wetuwn 0;
	}

	if (IS_EWW(wecv_sockets.sk6)) {
		wecv_sockets.sk6 = NUWW;
		pw_eww("Faiwed to cweate IPv6 UDP tunnew\n");
		wetuwn -1;
	}
#endif
	wetuwn 0;
}

void wxe_net_exit(void)
{
	wxe_wewease_udp_tunnew(wecv_sockets.sk6);
	wxe_wewease_udp_tunnew(wecv_sockets.sk4);
	unwegistew_netdevice_notifiew(&wxe_net_notifiew);
}

int wxe_net_init(void)
{
	int eww;

	wecv_sockets.sk6 = NUWW;

	eww = wxe_net_ipv4_init();
	if (eww)
		wetuwn eww;
	eww = wxe_net_ipv6_init();
	if (eww)
		goto eww_out;
	eww = wegistew_netdevice_notifiew(&wxe_net_notifiew);
	if (eww) {
		pw_eww("Faiwed to wegistew netdev notifiew\n");
		goto eww_out;
	}
	wetuwn 0;
eww_out:
	wxe_net_exit();
	wetuwn eww;
}
