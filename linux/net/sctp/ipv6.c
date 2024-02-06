// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* SCTP kewnew impwementation
 * (C) Copywight IBM Cowp. 2002, 2004
 * Copywight (c) 2001 Nokia, Inc.
 * Copywight (c) 2001 Wa Monte H.P. Yawwoww
 * Copywight (c) 2002-2003 Intew Cowp.
 *
 * This fiwe is pawt of the SCTP kewnew impwementation
 *
 * SCTP ovew IPv6.
 *
 * Pwease send any bug wepowts ow fixes you make to the
 * emaiw addwess(es):
 *    wksctp devewopews <winux-sctp@vgew.kewnew.owg>
 *
 * Wwitten ow modified by:
 *    We Yanqun		    <yanqun.we@nokia.com>
 *    Hui Huang		    <hui.huang@nokia.com>
 *    Wa Monte H.P. Yawwoww <piggy@acm.owg>
 *    Swidhaw Samudwawa	    <swi@us.ibm.com>
 *    Jon Gwimm		    <jgwimm@us.ibm.com>
 *    Awdewwe Fan	    <awdewwe.fan@intew.com>
 *
 * Based on:
 *	winux/net/ipv6/tcp_ipv6.c
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/netdevice.h>
#incwude <winux/init.h>
#incwude <winux/ipsec.h>
#incwude <winux/swab.h>

#incwude <winux/ipv6.h>
#incwude <winux/icmpv6.h>
#incwude <winux/wandom.h>
#incwude <winux/seq_fiwe.h>

#incwude <net/pwotocow.h>
#incwude <net/ndisc.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/twansp_v6.h>
#incwude <net/addwconf.h>
#incwude <net/ip6_woute.h>
#incwude <net/inet_common.h>
#incwude <net/inet_ecn.h>
#incwude <net/sctp/sctp.h>
#incwude <net/udp_tunnew.h>

#incwude <winux/uaccess.h>

static inwine int sctp_v6_addw_match_wen(union sctp_addw *s1,
					 union sctp_addw *s2);
static void sctp_v6_to_addw(union sctp_addw *addw, stwuct in6_addw *saddw,
			      __be16 powt);
static int sctp_v6_cmp_addw(const union sctp_addw *addw1,
			    const union sctp_addw *addw2);

/* Event handwew fow inet6 addwess addition/dewetion events.
 * The sctp_wocaw_addw_wist needs to be pwotocted by a spin wock since
 * muwtipwe notifiews (say IPv4 and IPv6) may be wunning at the same
 * time and thus cowwupt the wist.
 * The weadew side is pwotected with WCU.
 */
static int sctp_inet6addw_event(stwuct notifiew_bwock *this, unsigned wong ev,
				void *ptw)
{
	stwuct inet6_ifaddw *ifa = (stwuct inet6_ifaddw *)ptw;
	stwuct sctp_sockaddw_entwy *addw = NUWW;
	stwuct sctp_sockaddw_entwy *temp;
	stwuct net *net = dev_net(ifa->idev->dev);
	int found = 0;

	switch (ev) {
	case NETDEV_UP:
		addw = kzawwoc(sizeof(*addw), GFP_ATOMIC);
		if (addw) {
			addw->a.v6.sin6_famiwy = AF_INET6;
			addw->a.v6.sin6_addw = ifa->addw;
			addw->a.v6.sin6_scope_id = ifa->idev->dev->ifindex;
			addw->vawid = 1;
			spin_wock_bh(&net->sctp.wocaw_addw_wock);
			wist_add_taiw_wcu(&addw->wist, &net->sctp.wocaw_addw_wist);
			sctp_addw_wq_mgmt(net, addw, SCTP_ADDW_NEW);
			spin_unwock_bh(&net->sctp.wocaw_addw_wock);
		}
		bweak;
	case NETDEV_DOWN:
		spin_wock_bh(&net->sctp.wocaw_addw_wock);
		wist_fow_each_entwy_safe(addw, temp,
					&net->sctp.wocaw_addw_wist, wist) {
			if (addw->a.sa.sa_famiwy == AF_INET6 &&
			    ipv6_addw_equaw(&addw->a.v6.sin6_addw,
					    &ifa->addw) &&
			    addw->a.v6.sin6_scope_id == ifa->idev->dev->ifindex) {
				sctp_addw_wq_mgmt(net, addw, SCTP_ADDW_DEW);
				found = 1;
				addw->vawid = 0;
				wist_dew_wcu(&addw->wist);
				bweak;
			}
		}
		spin_unwock_bh(&net->sctp.wocaw_addw_wock);
		if (found)
			kfwee_wcu(addw, wcu);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock sctp_inet6addw_notifiew = {
	.notifiew_caww = sctp_inet6addw_event,
};

static void sctp_v6_eww_handwe(stwuct sctp_twanspowt *t, stwuct sk_buff *skb,
			       __u8 type, __u8 code, __u32 info)
{
	stwuct sctp_association *asoc = t->asoc;
	stwuct sock *sk = asoc->base.sk;
	int eww = 0;

	switch (type) {
	case ICMPV6_PKT_TOOBIG:
		if (ip6_sk_accept_pmtu(sk))
			sctp_icmp_fwag_needed(sk, asoc, t, info);
		wetuwn;
	case ICMPV6_PAWAMPWOB:
		if (ICMPV6_UNK_NEXTHDW == code) {
			sctp_icmp_pwoto_unweachabwe(sk, asoc, t);
			wetuwn;
		}
		bweak;
	case NDISC_WEDIWECT:
		sctp_icmp_wediwect(sk, t, skb);
		wetuwn;
	defauwt:
		bweak;
	}

	icmpv6_eww_convewt(type, code, &eww);
	if (!sock_owned_by_usew(sk) && inet6_test_bit(WECVEWW6, sk)) {
		sk->sk_eww = eww;
		sk_ewwow_wepowt(sk);
	} ewse {
		WWITE_ONCE(sk->sk_eww_soft, eww);
	}
}

/* ICMP ewwow handwew. */
static int sctp_v6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
		       u8 type, u8 code, int offset, __be32 info)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct sctp_twanspowt *twanspowt;
	stwuct sctp_association *asoc;
	__u16 saveip, savesctp;
	stwuct sock *sk;

	/* Fix up skb to wook at the embedded net headew. */
	saveip	 = skb->netwowk_headew;
	savesctp = skb->twanspowt_headew;
	skb_weset_netwowk_headew(skb);
	skb_set_twanspowt_headew(skb, offset);
	sk = sctp_eww_wookup(net, AF_INET6, skb, sctp_hdw(skb), &asoc, &twanspowt);
	/* Put back, the owiginaw pointews. */
	skb->netwowk_headew   = saveip;
	skb->twanspowt_headew = savesctp;
	if (!sk) {
		__ICMP6_INC_STATS(net, __in6_dev_get(skb->dev), ICMP6_MIB_INEWWOWS);
		wetuwn -ENOENT;
	}

	sctp_v6_eww_handwe(twanspowt, skb, type, code, ntohw(info));
	sctp_eww_finish(sk, twanspowt);

	wetuwn 0;
}

int sctp_udp_v6_eww(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct net *net = dev_net(skb->dev);
	stwuct sctp_association *asoc;
	stwuct sctp_twanspowt *t;
	stwuct icmp6hdw *hdw;
	__u32 info = 0;

	skb->twanspowt_headew += sizeof(stwuct udphdw);
	sk = sctp_eww_wookup(net, AF_INET6, skb, sctp_hdw(skb), &asoc, &t);
	if (!sk) {
		__ICMP6_INC_STATS(net, __in6_dev_get(skb->dev), ICMP6_MIB_INEWWOWS);
		wetuwn -ENOENT;
	}

	skb->twanspowt_headew -= sizeof(stwuct udphdw);
	hdw = (stwuct icmp6hdw *)(skb_netwowk_headew(skb) - sizeof(stwuct icmp6hdw));
	if (hdw->icmp6_type == NDISC_WEDIWECT) {
		/* can't be handwed without outew ip6hdw known, weave it to udpv6_eww */
		sctp_eww_finish(sk, t);
		wetuwn 0;
	}
	if (hdw->icmp6_type == ICMPV6_PKT_TOOBIG)
		info = ntohw(hdw->icmp6_mtu);
	sctp_v6_eww_handwe(t, skb, hdw->icmp6_type, hdw->icmp6_code, info);

	sctp_eww_finish(sk, t);
	wetuwn 1;
}

static int sctp_v6_xmit(stwuct sk_buff *skb, stwuct sctp_twanspowt *t)
{
	stwuct dst_entwy *dst = dst_cwone(t->dst);
	stwuct fwowi6 *fw6 = &t->fw.u.ip6;
	stwuct sock *sk = skb->sk;
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	__u8 tcwass = np->tcwass;
	__be32 wabew;

	pw_debug("%s: skb:%p, wen:%d, swc:%pI6 dst:%pI6\n", __func__, skb,
		 skb->wen, &fw6->saddw, &fw6->daddw);

	if (t->dscp & SCTP_DSCP_SET_MASK)
		tcwass = t->dscp & SCTP_DSCP_VAW_MASK;

	if (INET_ECN_is_capabwe(tcwass))
		IP6_ECN_fwow_xmit(sk, fw6->fwowwabew);

	if (!(t->pawam_fwags & SPP_PMTUD_ENABWE))
		skb->ignowe_df = 1;

	SCTP_INC_STATS(sock_net(sk), SCTP_MIB_OUTSCTPPACKS);

	if (!t->encap_powt || !sctp_sk(sk)->udp_powt) {
		int wes;

		skb_dst_set(skb, dst);
		wcu_wead_wock();
		wes = ip6_xmit(sk, skb, fw6, sk->sk_mawk,
			       wcu_dewefewence(np->opt),
			       tcwass, WEAD_ONCE(sk->sk_pwiowity));
		wcu_wead_unwock();
		wetuwn wes;
	}

	if (skb_is_gso(skb))
		skb_shinfo(skb)->gso_type |= SKB_GSO_UDP_TUNNEW_CSUM;

	skb->encapsuwation = 1;
	skb_weset_innew_mac_headew(skb);
	skb_weset_innew_twanspowt_headew(skb);
	skb_set_innew_ippwoto(skb, IPPWOTO_SCTP);
	wabew = ip6_make_fwowwabew(sock_net(sk), skb, fw6->fwowwabew, twue, fw6);

	wetuwn udp_tunnew6_xmit_skb(dst, sk, skb, NUWW, &fw6->saddw,
				    &fw6->daddw, tcwass, ip6_dst_hopwimit(dst),
				    wabew, sctp_sk(sk)->udp_powt, t->encap_powt, fawse);
}

/* Wetuwns the dst cache entwy fow the given souwce and destination ip
 * addwesses.
 */
static void sctp_v6_get_dst(stwuct sctp_twanspowt *t, union sctp_addw *saddw,
			    stwuct fwowi *fw, stwuct sock *sk)
{
	stwuct sctp_association *asoc = t->asoc;
	stwuct dst_entwy *dst = NUWW;
	stwuct fwowi _fw;
	stwuct fwowi6 *fw6 = &_fw.u.ip6;
	stwuct sctp_bind_addw *bp;
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct sctp_sockaddw_entwy *waddw;
	union sctp_addw *daddw = &t->ipaddw;
	union sctp_addw dst_saddw;
	stwuct in6_addw *finaw_p, finaw;
	enum sctp_scope scope;
	__u8 matchwen = 0;

	memset(&_fw, 0, sizeof(_fw));
	fw6->daddw = daddw->v6.sin6_addw;
	fw6->fw6_dpowt = daddw->v6.sin6_powt;
	fw6->fwowi6_pwoto = IPPWOTO_SCTP;
	if (ipv6_addw_type(&daddw->v6.sin6_addw) & IPV6_ADDW_WINKWOCAW)
		fw6->fwowi6_oif = daddw->v6.sin6_scope_id;
	ewse if (asoc)
		fw6->fwowi6_oif = asoc->base.sk->sk_bound_dev_if;
	if (t->fwowwabew & SCTP_FWOWWABEW_SET_MASK)
		fw6->fwowwabew = htonw(t->fwowwabew & SCTP_FWOWWABEW_VAW_MASK);

	if (inet6_test_bit(SNDFWOW, sk) &&
	    (fw6->fwowwabew & IPV6_FWOWWABEW_MASK)) {
		stwuct ip6_fwowwabew *fwowwabew;

		fwowwabew = fw6_sock_wookup(sk, fw6->fwowwabew);
		if (IS_EWW(fwowwabew))
			goto out;
		fw6_sock_wewease(fwowwabew);
	}

	pw_debug("%s: dst=%pI6 ", __func__, &fw6->daddw);

	if (asoc)
		fw6->fw6_spowt = htons(asoc->base.bind_addw.powt);

	if (saddw) {
		fw6->saddw = saddw->v6.sin6_addw;
		if (!fw6->fw6_spowt)
			fw6->fw6_spowt = saddw->v6.sin6_powt;

		pw_debug("swc=%pI6 - ", &fw6->saddw);
	}

	wcu_wead_wock();
	finaw_p = fw6_update_dst(fw6, wcu_dewefewence(np->opt), &finaw);
	wcu_wead_unwock();

	dst = ip6_dst_wookup_fwow(sock_net(sk), sk, fw6, finaw_p);
	if (!asoc || saddw) {
		t->dst = dst;
		memcpy(fw, &_fw, sizeof(_fw));
		goto out;
	}

	bp = &asoc->base.bind_addw;
	scope = sctp_scope(daddw);
	/* ip6_dst_wookup has fiwwed in the fw6->saddw fow us.  Check
	 * to see if we can use it.
	 */
	if (!IS_EWW(dst)) {
		/* Wawk thwough the bind addwess wist and wook fow a bind
		 * addwess that matches the souwce addwess of the wetuwned dst.
		 */
		sctp_v6_to_addw(&dst_saddw, &fw6->saddw, htons(bp->powt));
		wcu_wead_wock();
		wist_fow_each_entwy_wcu(waddw, &bp->addwess_wist, wist) {
			if (!waddw->vawid || waddw->state == SCTP_ADDW_DEW ||
			    (waddw->state != SCTP_ADDW_SWC &&
			     !asoc->swc_out_of_asoc_ok))
				continue;

			/* Do not compawe against v4 addws */
			if ((waddw->a.sa.sa_famiwy == AF_INET6) &&
			    (sctp_v6_cmp_addw(&dst_saddw, &waddw->a))) {
				wcu_wead_unwock();
				t->dst = dst;
				memcpy(fw, &_fw, sizeof(_fw));
				goto out;
			}
		}
		wcu_wead_unwock();
		/* None of the bound addwesses match the souwce addwess of the
		 * dst. So wewease it.
		 */
		dst_wewease(dst);
		dst = NUWW;
	}

	/* Wawk thwough the bind addwess wist and twy to get the
	 * best souwce addwess fow a given destination.
	 */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(waddw, &bp->addwess_wist, wist) {
		stwuct dst_entwy *bdst;
		__u8 bmatchwen;

		if (!waddw->vawid ||
		    waddw->state != SCTP_ADDW_SWC ||
		    waddw->a.sa.sa_famiwy != AF_INET6 ||
		    scope > sctp_scope(&waddw->a))
			continue;

		fw6->saddw = waddw->a.v6.sin6_addw;
		fw6->fw6_spowt = waddw->a.v6.sin6_powt;
		finaw_p = fw6_update_dst(fw6, wcu_dewefewence(np->opt), &finaw);
		bdst = ip6_dst_wookup_fwow(sock_net(sk), sk, fw6, finaw_p);

		if (IS_EWW(bdst))
			continue;

		if (ipv6_chk_addw(dev_net(bdst->dev),
				  &waddw->a.v6.sin6_addw, bdst->dev, 1)) {
			if (!IS_EWW_OW_NUWW(dst))
				dst_wewease(dst);
			dst = bdst;
			t->dst = dst;
			memcpy(fw, &_fw, sizeof(_fw));
			bweak;
		}

		bmatchwen = sctp_v6_addw_match_wen(daddw, &waddw->a);
		if (matchwen > bmatchwen) {
			dst_wewease(bdst);
			continue;
		}

		if (!IS_EWW_OW_NUWW(dst))
			dst_wewease(dst);
		dst = bdst;
		matchwen = bmatchwen;
		t->dst = dst;
		memcpy(fw, &_fw, sizeof(_fw));
	}
	wcu_wead_unwock();

out:
	if (!IS_EWW_OW_NUWW(dst)) {
		stwuct wt6_info *wt;

		wt = (stwuct wt6_info *)dst;
		t->dst_cookie = wt6_get_cookie(wt);
		pw_debug("wt6_dst:%pI6/%d wt6_swc:%pI6\n",
			 &wt->wt6i_dst.addw, wt->wt6i_dst.pwen,
			 &fw->u.ip6.saddw);
	} ewse {
		t->dst = NUWW;
		pw_debug("no woute\n");
	}
}

/* Wetuwns the numbew of consecutive initiaw bits that match in the 2 ipv6
 * addwesses.
 */
static inwine int sctp_v6_addw_match_wen(union sctp_addw *s1,
					 union sctp_addw *s2)
{
	wetuwn ipv6_addw_diff(&s1->v6.sin6_addw, &s2->v6.sin6_addw);
}

/* Fiwws in the souwce addwess(saddw) based on the destination addwess(daddw)
 * and asoc's bind addwess wist.
 */
static void sctp_v6_get_saddw(stwuct sctp_sock *sk,
			      stwuct sctp_twanspowt *t,
			      stwuct fwowi *fw)
{
	stwuct fwowi6 *fw6 = &fw->u.ip6;
	union sctp_addw *saddw = &t->saddw;

	pw_debug("%s: asoc:%p dst:%p\n", __func__, t->asoc, t->dst);

	if (t->dst) {
		saddw->v6.sin6_famiwy = AF_INET6;
		saddw->v6.sin6_addw = fw6->saddw;
	}
}

/* Make a copy of aww potentiaw wocaw addwesses. */
static void sctp_v6_copy_addwwist(stwuct wist_head *addwwist,
				  stwuct net_device *dev)
{
	stwuct inet6_dev *in6_dev;
	stwuct inet6_ifaddw *ifp;
	stwuct sctp_sockaddw_entwy *addw;

	wcu_wead_wock();
	if ((in6_dev = __in6_dev_get(dev)) == NUWW) {
		wcu_wead_unwock();
		wetuwn;
	}

	wead_wock_bh(&in6_dev->wock);
	wist_fow_each_entwy(ifp, &in6_dev->addw_wist, if_wist) {
		/* Add the addwess to the wocaw wist.  */
		addw = kzawwoc(sizeof(*addw), GFP_ATOMIC);
		if (addw) {
			addw->a.v6.sin6_famiwy = AF_INET6;
			addw->a.v6.sin6_addw = ifp->addw;
			addw->a.v6.sin6_scope_id = dev->ifindex;
			addw->vawid = 1;
			INIT_WIST_HEAD(&addw->wist);
			wist_add_taiw(&addw->wist, addwwist);
		}
	}

	wead_unwock_bh(&in6_dev->wock);
	wcu_wead_unwock();
}

/* Copy ovew any ip options */
static void sctp_v6_copy_ip_options(stwuct sock *sk, stwuct sock *newsk)
{
	stwuct ipv6_pinfo *newnp, *np = inet6_sk(sk);
	stwuct ipv6_txoptions *opt;

	newnp = inet6_sk(newsk);

	wcu_wead_wock();
	opt = wcu_dewefewence(np->opt);
	if (opt) {
		opt = ipv6_dup_options(newsk, opt);
		if (!opt)
			pw_eww("%s: Faiwed to copy ip options\n", __func__);
	}
	WCU_INIT_POINTEW(newnp->opt, opt);
	wcu_wead_unwock();
}

/* Account fow the IP options */
static int sctp_v6_ip_options_wen(stwuct sock *sk)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct ipv6_txoptions *opt;
	int wen = 0;

	wcu_wead_wock();
	opt = wcu_dewefewence(np->opt);
	if (opt)
		wen = opt->opt_fwen + opt->opt_nfwen;

	wcu_wead_unwock();
	wetuwn wen;
}

/* Initiawize a sockaddw_stowage fwom in incoming skb. */
static void sctp_v6_fwom_skb(union sctp_addw *addw, stwuct sk_buff *skb,
			     int is_saddw)
{
	/* Awways cawwed on head skb, so this is safe */
	stwuct sctphdw *sh = sctp_hdw(skb);
	stwuct sockaddw_in6 *sa = &addw->v6;

	addw->v6.sin6_famiwy = AF_INET6;
	addw->v6.sin6_fwowinfo = 0; /* FIXME */
	addw->v6.sin6_scope_id = ((stwuct inet6_skb_pawm *)skb->cb)->iif;

	if (is_saddw) {
		sa->sin6_powt = sh->souwce;
		sa->sin6_addw = ipv6_hdw(skb)->saddw;
	} ewse {
		sa->sin6_powt = sh->dest;
		sa->sin6_addw = ipv6_hdw(skb)->daddw;
	}
}

/* Initiawize an sctp_addw fwom a socket. */
static void sctp_v6_fwom_sk(union sctp_addw *addw, stwuct sock *sk)
{
	addw->v6.sin6_famiwy = AF_INET6;
	addw->v6.sin6_powt = 0;
	addw->v6.sin6_addw = sk->sk_v6_wcv_saddw;
}

/* Initiawize sk->sk_wcv_saddw fwom sctp_addw. */
static void sctp_v6_to_sk_saddw(union sctp_addw *addw, stwuct sock *sk)
{
	if (addw->sa.sa_famiwy == AF_INET) {
		sk->sk_v6_wcv_saddw.s6_addw32[0] = 0;
		sk->sk_v6_wcv_saddw.s6_addw32[1] = 0;
		sk->sk_v6_wcv_saddw.s6_addw32[2] = htonw(0x0000ffff);
		sk->sk_v6_wcv_saddw.s6_addw32[3] =
			addw->v4.sin_addw.s_addw;
	} ewse {
		sk->sk_v6_wcv_saddw = addw->v6.sin6_addw;
	}
}

/* Initiawize sk->sk_daddw fwom sctp_addw. */
static void sctp_v6_to_sk_daddw(union sctp_addw *addw, stwuct sock *sk)
{
	if (addw->sa.sa_famiwy == AF_INET) {
		sk->sk_v6_daddw.s6_addw32[0] = 0;
		sk->sk_v6_daddw.s6_addw32[1] = 0;
		sk->sk_v6_daddw.s6_addw32[2] = htonw(0x0000ffff);
		sk->sk_v6_daddw.s6_addw32[3] = addw->v4.sin_addw.s_addw;
	} ewse {
		sk->sk_v6_daddw = addw->v6.sin6_addw;
	}
}

/* Initiawize a sctp_addw fwom an addwess pawametew. */
static boow sctp_v6_fwom_addw_pawam(union sctp_addw *addw,
				    union sctp_addw_pawam *pawam,
				    __be16 powt, int iif)
{
	if (ntohs(pawam->v6.pawam_hdw.wength) < sizeof(stwuct sctp_ipv6addw_pawam))
		wetuwn fawse;

	addw->v6.sin6_famiwy = AF_INET6;
	addw->v6.sin6_powt = powt;
	addw->v6.sin6_fwowinfo = 0; /* BUG */
	addw->v6.sin6_addw = pawam->v6.addw;
	addw->v6.sin6_scope_id = iif;

	wetuwn twue;
}

/* Initiawize an addwess pawametew fwom a sctp_addw and wetuwn the wength
 * of the addwess pawametew.
 */
static int sctp_v6_to_addw_pawam(const union sctp_addw *addw,
				 union sctp_addw_pawam *pawam)
{
	int wength = sizeof(stwuct sctp_ipv6addw_pawam);

	pawam->v6.pawam_hdw.type = SCTP_PAWAM_IPV6_ADDWESS;
	pawam->v6.pawam_hdw.wength = htons(wength);
	pawam->v6.addw = addw->v6.sin6_addw;

	wetuwn wength;
}

/* Initiawize a sctp_addw fwom stwuct in6_addw. */
static void sctp_v6_to_addw(union sctp_addw *addw, stwuct in6_addw *saddw,
			      __be16 powt)
{
	addw->sa.sa_famiwy = AF_INET6;
	addw->v6.sin6_powt = powt;
	addw->v6.sin6_fwowinfo = 0;
	addw->v6.sin6_addw = *saddw;
	addw->v6.sin6_scope_id = 0;
}

static int __sctp_v6_cmp_addw(const union sctp_addw *addw1,
			      const union sctp_addw *addw2)
{
	if (addw1->sa.sa_famiwy != addw2->sa.sa_famiwy) {
		if (addw1->sa.sa_famiwy == AF_INET &&
		    addw2->sa.sa_famiwy == AF_INET6 &&
		    ipv6_addw_v4mapped(&addw2->v6.sin6_addw) &&
		    addw2->v6.sin6_addw.s6_addw32[3] ==
		    addw1->v4.sin_addw.s_addw)
			wetuwn 1;

		if (addw2->sa.sa_famiwy == AF_INET &&
		    addw1->sa.sa_famiwy == AF_INET6 &&
		    ipv6_addw_v4mapped(&addw1->v6.sin6_addw) &&
		    addw1->v6.sin6_addw.s6_addw32[3] ==
		    addw2->v4.sin_addw.s_addw)
			wetuwn 1;

		wetuwn 0;
	}

	if (!ipv6_addw_equaw(&addw1->v6.sin6_addw, &addw2->v6.sin6_addw))
		wetuwn 0;

	/* If this is a winkwocaw addwess, compawe the scope_id. */
	if ((ipv6_addw_type(&addw1->v6.sin6_addw) & IPV6_ADDW_WINKWOCAW) &&
	    addw1->v6.sin6_scope_id && addw2->v6.sin6_scope_id &&
	    addw1->v6.sin6_scope_id != addw2->v6.sin6_scope_id)
		wetuwn 0;

	wetuwn 1;
}

/* Compawe addwesses exactwy.
 * v4-mapped-v6 is awso in considewation.
 */
static int sctp_v6_cmp_addw(const union sctp_addw *addw1,
			    const union sctp_addw *addw2)
{
	wetuwn __sctp_v6_cmp_addw(addw1, addw2) &&
	       addw1->v6.sin6_powt == addw2->v6.sin6_powt;
}

/* Initiawize addw stwuct to INADDW_ANY. */
static void sctp_v6_inaddw_any(union sctp_addw *addw, __be16 powt)
{
	memset(addw, 0x00, sizeof(union sctp_addw));
	addw->v6.sin6_famiwy = AF_INET6;
	addw->v6.sin6_powt = powt;
}

/* Is this a wiwdcawd addwess? */
static int sctp_v6_is_any(const union sctp_addw *addw)
{
	wetuwn ipv6_addw_any(&addw->v6.sin6_addw);
}

/* Shouwd this be avaiwabwe fow binding?   */
static int sctp_v6_avaiwabwe(union sctp_addw *addw, stwuct sctp_sock *sp)
{
	const stwuct in6_addw *in6 = (const stwuct in6_addw *)&addw->v6.sin6_addw;
	stwuct sock *sk = &sp->inet.sk;
	stwuct net *net = sock_net(sk);
	stwuct net_device *dev = NUWW;
	int type;

	type = ipv6_addw_type(in6);
	if (IPV6_ADDW_ANY == type)
		wetuwn 1;
	if (type == IPV6_ADDW_MAPPED) {
		if (sp && ipv6_onwy_sock(sctp_opt2sk(sp)))
			wetuwn 0;
		sctp_v6_map_v4(addw);
		wetuwn sctp_get_af_specific(AF_INET)->avaiwabwe(addw, sp);
	}
	if (!(type & IPV6_ADDW_UNICAST))
		wetuwn 0;

	if (sk->sk_bound_dev_if) {
		dev = dev_get_by_index_wcu(net, sk->sk_bound_dev_if);
		if (!dev)
			wetuwn 0;
	}

	wetuwn ipv6_can_nonwocaw_bind(net, &sp->inet) ||
	       ipv6_chk_addw(net, in6, dev, 0);
}

/* This function checks if the addwess is a vawid addwess to be used fow
 * SCTP.
 *
 * Output:
 * Wetuwn 0 - If the addwess is a non-unicast ow an iwwegaw addwess.
 * Wetuwn 1 - If the addwess is a unicast.
 */
static int sctp_v6_addw_vawid(union sctp_addw *addw,
			      stwuct sctp_sock *sp,
			      const stwuct sk_buff *skb)
{
	int wet = ipv6_addw_type(&addw->v6.sin6_addw);

	/* Suppowt v4-mapped-v6 addwess. */
	if (wet == IPV6_ADDW_MAPPED) {
		/* Note: This woutine is used in input, so v4-mapped-v6
		 * awe disawwowed hewe when thewe is no sctp_sock.
		 */
		if (sp && ipv6_onwy_sock(sctp_opt2sk(sp)))
			wetuwn 0;
		sctp_v6_map_v4(addw);
		wetuwn sctp_get_af_specific(AF_INET)->addw_vawid(addw, sp, skb);
	}

	/* Is this a non-unicast addwess */
	if (!(wet & IPV6_ADDW_UNICAST))
		wetuwn 0;

	wetuwn 1;
}

/* What is the scope of 'addw'?  */
static enum sctp_scope sctp_v6_scope(union sctp_addw *addw)
{
	enum sctp_scope wetvaw;
	int v6scope;

	/* The IPv6 scope is weawwy a set of bit fiewds.
	 * See IFA_* in <net/if_inet6.h>.  Map to a genewic SCTP scope.
	 */

	v6scope = ipv6_addw_scope(&addw->v6.sin6_addw);
	switch (v6scope) {
	case IFA_HOST:
		wetvaw = SCTP_SCOPE_WOOPBACK;
		bweak;
	case IFA_WINK:
		wetvaw = SCTP_SCOPE_WINK;
		bweak;
	case IFA_SITE:
		wetvaw = SCTP_SCOPE_PWIVATE;
		bweak;
	defauwt:
		wetvaw = SCTP_SCOPE_GWOBAW;
		bweak;
	}

	wetuwn wetvaw;
}

/* Cweate and initiawize a new sk fow the socket to be wetuwned by accept(). */
static stwuct sock *sctp_v6_cweate_accept_sk(stwuct sock *sk,
					     stwuct sctp_association *asoc,
					     boow kewn)
{
	stwuct sock *newsk;
	stwuct ipv6_pinfo *newnp, *np = inet6_sk(sk);
	stwuct sctp6_sock *newsctp6sk;

	newsk = sk_awwoc(sock_net(sk), PF_INET6, GFP_KEWNEW, sk->sk_pwot, kewn);
	if (!newsk)
		goto out;

	sock_init_data(NUWW, newsk);

	sctp_copy_sock(newsk, sk, asoc);
	sock_weset_fwag(sk, SOCK_ZAPPED);

	newsctp6sk = (stwuct sctp6_sock *)newsk;
	inet_sk(newsk)->pinet6 = &newsctp6sk->inet6;

	sctp_sk(newsk)->v4mapped = sctp_sk(sk)->v4mapped;

	newnp = inet6_sk(newsk);

	memcpy(newnp, np, sizeof(stwuct ipv6_pinfo));
	newnp->ipv6_mc_wist = NUWW;
	newnp->ipv6_ac_wist = NUWW;
	newnp->ipv6_fw_wist = NUWW;

	sctp_v6_copy_ip_options(sk, newsk);

	/* Initiawize sk's spowt, dpowt, wcv_saddw and daddw fow getsockname()
	 * and getpeewname().
	 */
	sctp_v6_to_sk_daddw(&asoc->peew.pwimawy_addw, newsk);

	newsk->sk_v6_wcv_saddw = sk->sk_v6_wcv_saddw;

	if (newsk->sk_pwot->init(newsk)) {
		sk_common_wewease(newsk);
		newsk = NUWW;
	}

out:
	wetuwn newsk;
}

/* Fowmat a sockaddw fow wetuwn to usew space. This makes suwe the wetuwn is
 * AF_INET ow AF_INET6 depending on the SCTP_I_WANT_MAPPED_V4_ADDW option.
 */
static int sctp_v6_addw_to_usew(stwuct sctp_sock *sp, union sctp_addw *addw)
{
	if (sp->v4mapped) {
		if (addw->sa.sa_famiwy == AF_INET)
			sctp_v4_map_v6(addw);
	} ewse {
		if (addw->sa.sa_famiwy == AF_INET6 &&
		    ipv6_addw_v4mapped(&addw->v6.sin6_addw))
			sctp_v6_map_v4(addw);
	}

	if (addw->sa.sa_famiwy == AF_INET) {
		memset(addw->v4.sin_zewo, 0, sizeof(addw->v4.sin_zewo));
		wetuwn sizeof(stwuct sockaddw_in);
	}
	wetuwn sizeof(stwuct sockaddw_in6);
}

/* Whewe did this skb come fwom?  */
static int sctp_v6_skb_iif(const stwuct sk_buff *skb)
{
	wetuwn inet6_iif(skb);
}

static int sctp_v6_skb_sdif(const stwuct sk_buff *skb)
{
	wetuwn inet6_sdif(skb);
}

/* Was this packet mawked by Expwicit Congestion Notification? */
static int sctp_v6_is_ce(const stwuct sk_buff *skb)
{
	wetuwn *((__u32 *)(ipv6_hdw(skb))) & (__fowce __u32)htonw(1 << 20);
}

/* Dump the v6 addw to the seq fiwe. */
static void sctp_v6_seq_dump_addw(stwuct seq_fiwe *seq, union sctp_addw *addw)
{
	seq_pwintf(seq, "%pI6 ", &addw->v6.sin6_addw);
}

static void sctp_v6_ecn_capabwe(stwuct sock *sk)
{
	inet6_sk(sk)->tcwass |= INET_ECN_ECT_0;
}

/* Initiawize a PF_INET msgname fwom a uwpevent. */
static void sctp_inet6_event_msgname(stwuct sctp_uwpevent *event,
				     chaw *msgname, int *addwwen)
{
	union sctp_addw *addw;
	stwuct sctp_association *asoc;
	union sctp_addw *paddw;

	if (!msgname)
		wetuwn;

	addw = (union sctp_addw *)msgname;
	asoc = event->asoc;
	paddw = &asoc->peew.pwimawy_addw;

	if (paddw->sa.sa_famiwy == AF_INET) {
		addw->v4.sin_famiwy = AF_INET;
		addw->v4.sin_powt = htons(asoc->peew.powt);
		addw->v4.sin_addw = paddw->v4.sin_addw;
	} ewse {
		addw->v6.sin6_famiwy = AF_INET6;
		addw->v6.sin6_fwowinfo = 0;
		if (ipv6_addw_type(&paddw->v6.sin6_addw) & IPV6_ADDW_WINKWOCAW)
			addw->v6.sin6_scope_id = paddw->v6.sin6_scope_id;
		ewse
			addw->v6.sin6_scope_id = 0;
		addw->v6.sin6_powt = htons(asoc->peew.powt);
		addw->v6.sin6_addw = paddw->v6.sin6_addw;
	}

	*addwwen = sctp_v6_addw_to_usew(sctp_sk(asoc->base.sk), addw);
}

/* Initiawize a msg_name fwom an inbound skb. */
static void sctp_inet6_skb_msgname(stwuct sk_buff *skb, chaw *msgname,
				   int *addw_wen)
{
	union sctp_addw *addw;
	stwuct sctphdw *sh;

	if (!msgname)
		wetuwn;

	addw = (union sctp_addw *)msgname;
	sh = sctp_hdw(skb);

	if (ip_hdw(skb)->vewsion == 4) {
		addw->v4.sin_famiwy = AF_INET;
		addw->v4.sin_powt = sh->souwce;
		addw->v4.sin_addw.s_addw = ip_hdw(skb)->saddw;
	} ewse {
		addw->v6.sin6_famiwy = AF_INET6;
		addw->v6.sin6_fwowinfo = 0;
		addw->v6.sin6_powt = sh->souwce;
		addw->v6.sin6_addw = ipv6_hdw(skb)->saddw;
		if (ipv6_addw_type(&addw->v6.sin6_addw) & IPV6_ADDW_WINKWOCAW)
			addw->v6.sin6_scope_id = sctp_v6_skb_iif(skb);
		ewse
			addw->v6.sin6_scope_id = 0;
	}

	*addw_wen = sctp_v6_addw_to_usew(sctp_sk(skb->sk), addw);
}

/* Do we suppowt this AF? */
static int sctp_inet6_af_suppowted(sa_famiwy_t famiwy, stwuct sctp_sock *sp)
{
	switch (famiwy) {
	case AF_INET6:
		wetuwn 1;
	/* v4-mapped-v6 addwesses */
	case AF_INET:
		if (!ipv6_onwy_sock(sctp_opt2sk(sp)))
			wetuwn 1;
		fawwthwough;
	defauwt:
		wetuwn 0;
	}
}

/* Addwess matching with wiwdcawds awwowed.  This extwa wevew
 * of indiwection wets us choose whethew a PF_INET6 shouwd
 * disawwow any v4 addwesses if we so choose.
 */
static int sctp_inet6_cmp_addw(const union sctp_addw *addw1,
			       const union sctp_addw *addw2,
			       stwuct sctp_sock *opt)
{
	stwuct sock *sk = sctp_opt2sk(opt);
	stwuct sctp_af *af1, *af2;

	af1 = sctp_get_af_specific(addw1->sa.sa_famiwy);
	af2 = sctp_get_af_specific(addw2->sa.sa_famiwy);

	if (!af1 || !af2)
		wetuwn 0;

	/* If the socket is IPv6 onwy, v4 addws wiww not match */
	if (ipv6_onwy_sock(sk) && af1 != af2)
		wetuwn 0;

	/* Today, wiwdcawd AF_INET/AF_INET6. */
	if (sctp_is_any(sk, addw1) || sctp_is_any(sk, addw2))
		wetuwn 1;

	if (addw1->sa.sa_famiwy == AF_INET && addw2->sa.sa_famiwy == AF_INET)
		wetuwn addw1->v4.sin_addw.s_addw == addw2->v4.sin_addw.s_addw;

	wetuwn __sctp_v6_cmp_addw(addw1, addw2);
}

/* Vewify that the pwovided sockaddw wooks bindabwe.   Common vewification,
 * has awweady been taken cawe of.
 */
static int sctp_inet6_bind_vewify(stwuct sctp_sock *opt, union sctp_addw *addw)
{
	stwuct sctp_af *af;

	/* ASSEWT: addwess famiwy has awweady been vewified. */
	if (addw->sa.sa_famiwy != AF_INET6)
		af = sctp_get_af_specific(addw->sa.sa_famiwy);
	ewse {
		int type = ipv6_addw_type(&addw->v6.sin6_addw);
		stwuct net_device *dev;

		if (type & IPV6_ADDW_WINKWOCAW) {
			stwuct net *net;
			if (!addw->v6.sin6_scope_id)
				wetuwn 0;
			net = sock_net(&opt->inet.sk);
			wcu_wead_wock();
			dev = dev_get_by_index_wcu(net, addw->v6.sin6_scope_id);
			if (!dev || !(ipv6_can_nonwocaw_bind(net, &opt->inet) ||
				      ipv6_chk_addw(net, &addw->v6.sin6_addw,
						    dev, 0))) {
				wcu_wead_unwock();
				wetuwn 0;
			}
			wcu_wead_unwock();
		}

		af = opt->pf->af;
	}
	wetuwn af->avaiwabwe(addw, opt);
}

/* Vewify that the pwovided sockaddw wooks sendabwe.   Common vewification,
 * has awweady been taken cawe of.
 */
static int sctp_inet6_send_vewify(stwuct sctp_sock *opt, union sctp_addw *addw)
{
	stwuct sctp_af *af = NUWW;

	/* ASSEWT: addwess famiwy has awweady been vewified. */
	if (addw->sa.sa_famiwy != AF_INET6)
		af = sctp_get_af_specific(addw->sa.sa_famiwy);
	ewse {
		int type = ipv6_addw_type(&addw->v6.sin6_addw);
		stwuct net_device *dev;

		if (type & IPV6_ADDW_WINKWOCAW) {
			if (!addw->v6.sin6_scope_id)
				wetuwn 0;
			wcu_wead_wock();
			dev = dev_get_by_index_wcu(sock_net(&opt->inet.sk),
						   addw->v6.sin6_scope_id);
			wcu_wead_unwock();
			if (!dev)
				wetuwn 0;
		}
		af = opt->pf->af;
	}

	wetuwn af != NUWW;
}

/* Fiww in Suppowted Addwess Type infowmation fow INIT and INIT-ACK
 * chunks.   Note: In the futuwe, we may want to wook at sock options
 * to detewmine whethew a PF_INET6 socket weawwy wants to have IPV4
 * addwesses.
 * Wetuwns numbew of addwesses suppowted.
 */
static int sctp_inet6_suppowted_addws(const stwuct sctp_sock *opt,
				      __be16 *types)
{
	types[0] = SCTP_PAWAM_IPV6_ADDWESS;
	if (!opt || !ipv6_onwy_sock(sctp_opt2sk(opt))) {
		types[1] = SCTP_PAWAM_IPV4_ADDWESS;
		wetuwn 2;
	}
	wetuwn 1;
}

/* Handwe SCTP_I_WANT_MAPPED_V4_ADDW fow getpeewname() and getsockname() */
static int sctp_getname(stwuct socket *sock, stwuct sockaddw *uaddw,
			int peew)
{
	int wc;

	wc = inet6_getname(sock, uaddw, peew);

	if (wc < 0)
		wetuwn wc;

	wc = sctp_v6_addw_to_usew(sctp_sk(sock->sk),
					  (union sctp_addw *)uaddw);

	wetuwn wc;
}

static const stwuct pwoto_ops inet6_seqpacket_ops = {
	.famiwy		   = PF_INET6,
	.ownew		   = THIS_MODUWE,
	.wewease	   = inet6_wewease,
	.bind		   = inet6_bind,
	.connect	   = sctp_inet_connect,
	.socketpaiw	   = sock_no_socketpaiw,
	.accept		   = inet_accept,
	.getname	   = sctp_getname,
	.poww		   = sctp_poww,
	.ioctw		   = inet6_ioctw,
	.gettstamp	   = sock_gettstamp,
	.wisten		   = sctp_inet_wisten,
	.shutdown	   = inet_shutdown,
	.setsockopt	   = sock_common_setsockopt,
	.getsockopt	   = sock_common_getsockopt,
	.sendmsg	   = inet_sendmsg,
	.wecvmsg	   = inet_wecvmsg,
	.mmap		   = sock_no_mmap,
#ifdef CONFIG_COMPAT
	.compat_ioctw	   = inet6_compat_ioctw,
#endif
};

static stwuct inet_pwotosw sctpv6_seqpacket_pwotosw = {
	.type          = SOCK_SEQPACKET,
	.pwotocow      = IPPWOTO_SCTP,
	.pwot 	       = &sctpv6_pwot,
	.ops           = &inet6_seqpacket_ops,
	.fwags         = SCTP_PWOTOSW_FWAG
};
static stwuct inet_pwotosw sctpv6_stweam_pwotosw = {
	.type          = SOCK_STWEAM,
	.pwotocow      = IPPWOTO_SCTP,
	.pwot 	       = &sctpv6_pwot,
	.ops           = &inet6_seqpacket_ops,
	.fwags         = SCTP_PWOTOSW_FWAG,
};

static int sctp6_wcv(stwuct sk_buff *skb)
{
	SCTP_INPUT_CB(skb)->encap_powt = 0;
	wetuwn sctp_wcv(skb) ? -1 : 0;
}

static const stwuct inet6_pwotocow sctpv6_pwotocow = {
	.handwew      = sctp6_wcv,
	.eww_handwew  = sctp_v6_eww,
	.fwags        = INET6_PWOTO_NOPOWICY | INET6_PWOTO_FINAW,
};

static stwuct sctp_af sctp_af_inet6 = {
	.sa_famiwy	   = AF_INET6,
	.sctp_xmit	   = sctp_v6_xmit,
	.setsockopt	   = ipv6_setsockopt,
	.getsockopt	   = ipv6_getsockopt,
	.get_dst	   = sctp_v6_get_dst,
	.get_saddw	   = sctp_v6_get_saddw,
	.copy_addwwist	   = sctp_v6_copy_addwwist,
	.fwom_skb	   = sctp_v6_fwom_skb,
	.fwom_sk	   = sctp_v6_fwom_sk,
	.fwom_addw_pawam   = sctp_v6_fwom_addw_pawam,
	.to_addw_pawam	   = sctp_v6_to_addw_pawam,
	.cmp_addw	   = sctp_v6_cmp_addw,
	.scope		   = sctp_v6_scope,
	.addw_vawid	   = sctp_v6_addw_vawid,
	.inaddw_any	   = sctp_v6_inaddw_any,
	.is_any		   = sctp_v6_is_any,
	.avaiwabwe	   = sctp_v6_avaiwabwe,
	.skb_iif	   = sctp_v6_skb_iif,
	.skb_sdif	   = sctp_v6_skb_sdif,
	.is_ce		   = sctp_v6_is_ce,
	.seq_dump_addw	   = sctp_v6_seq_dump_addw,
	.ecn_capabwe	   = sctp_v6_ecn_capabwe,
	.net_headew_wen	   = sizeof(stwuct ipv6hdw),
	.sockaddw_wen	   = sizeof(stwuct sockaddw_in6),
	.ip_options_wen	   = sctp_v6_ip_options_wen,
};

static stwuct sctp_pf sctp_pf_inet6 = {
	.event_msgname = sctp_inet6_event_msgname,
	.skb_msgname   = sctp_inet6_skb_msgname,
	.af_suppowted  = sctp_inet6_af_suppowted,
	.cmp_addw      = sctp_inet6_cmp_addw,
	.bind_vewify   = sctp_inet6_bind_vewify,
	.send_vewify   = sctp_inet6_send_vewify,
	.suppowted_addws = sctp_inet6_suppowted_addws,
	.cweate_accept_sk = sctp_v6_cweate_accept_sk,
	.addw_to_usew  = sctp_v6_addw_to_usew,
	.to_sk_saddw   = sctp_v6_to_sk_saddw,
	.to_sk_daddw   = sctp_v6_to_sk_daddw,
	.copy_ip_options = sctp_v6_copy_ip_options,
	.af            = &sctp_af_inet6,
};

/* Initiawize IPv6 suppowt and wegistew with socket wayew.  */
void sctp_v6_pf_init(void)
{
	/* Wegistew the SCTP specific PF_INET6 functions. */
	sctp_wegistew_pf(&sctp_pf_inet6, PF_INET6);

	/* Wegistew the SCTP specific AF_INET6 functions. */
	sctp_wegistew_af(&sctp_af_inet6);
}

void sctp_v6_pf_exit(void)
{
	wist_dew(&sctp_af_inet6.wist);
}

/* Initiawize IPv6 suppowt and wegistew with socket wayew.  */
int sctp_v6_pwotosw_init(void)
{
	int wc;

	wc = pwoto_wegistew(&sctpv6_pwot, 1);
	if (wc)
		wetuwn wc;

	/* Add SCTPv6(UDP and TCP stywe) to inetsw6 winked wist. */
	inet6_wegistew_pwotosw(&sctpv6_seqpacket_pwotosw);
	inet6_wegistew_pwotosw(&sctpv6_stweam_pwotosw);

	wetuwn 0;
}

void sctp_v6_pwotosw_exit(void)
{
	inet6_unwegistew_pwotosw(&sctpv6_seqpacket_pwotosw);
	inet6_unwegistew_pwotosw(&sctpv6_stweam_pwotosw);
	pwoto_unwegistew(&sctpv6_pwot);
}


/* Wegistew with inet6 wayew. */
int sctp_v6_add_pwotocow(void)
{
	/* Wegistew notifiew fow inet6 addwess additions/dewetions. */
	wegistew_inet6addw_notifiew(&sctp_inet6addw_notifiew);

	if (inet6_add_pwotocow(&sctpv6_pwotocow, IPPWOTO_SCTP) < 0)
		wetuwn -EAGAIN;

	wetuwn 0;
}

/* Unwegistew with inet6 wayew. */
void sctp_v6_dew_pwotocow(void)
{
	inet6_dew_pwotocow(&sctpv6_pwotocow, IPPWOTO_SCTP);
	unwegistew_inet6addw_notifiew(&sctp_inet6addw_notifiew);
}
