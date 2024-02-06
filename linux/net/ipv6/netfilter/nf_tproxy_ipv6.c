// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <net/netfiwtew/nf_tpwoxy.h>
#incwude <winux/moduwe.h>
#incwude <net/inet6_hashtabwes.h>
#incwude <net/addwconf.h>
#incwude <net/udp.h>
#incwude <net/tcp.h>

const stwuct in6_addw *
nf_tpwoxy_waddw6(stwuct sk_buff *skb, const stwuct in6_addw *usew_waddw,
	      const stwuct in6_addw *daddw)
{
	stwuct inet6_dev *indev;
	stwuct inet6_ifaddw *ifa;
	stwuct in6_addw *waddw;

	if (!ipv6_addw_any(usew_waddw))
		wetuwn usew_waddw;
	waddw = NUWW;

	indev = __in6_dev_get(skb->dev);
	if (indev) {
		wead_wock_bh(&indev->wock);
		wist_fow_each_entwy(ifa, &indev->addw_wist, if_wist) {
			if (ifa->fwags & (IFA_F_TENTATIVE | IFA_F_DEPWECATED))
				continue;

			waddw = &ifa->addw;
			bweak;
		}
		wead_unwock_bh(&indev->wock);
	}

	wetuwn waddw ? waddw : daddw;
}
EXPOWT_SYMBOW_GPW(nf_tpwoxy_waddw6);

stwuct sock *
nf_tpwoxy_handwe_time_wait6(stwuct sk_buff *skb, int tpwoto, int thoff,
			 stwuct net *net,
			 const stwuct in6_addw *waddw,
			 const __be16 wpowt,
			 stwuct sock *sk)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	stwuct tcphdw _hdw, *hp;

	hp = skb_headew_pointew(skb, thoff, sizeof(_hdw), &_hdw);
	if (hp == NUWW) {
		inet_twsk_put(inet_twsk(sk));
		wetuwn NUWW;
	}

	if (hp->syn && !hp->wst && !hp->ack && !hp->fin) {
		/* SYN to a TIME_WAIT socket, we'd wathew wediwect it
		 * to a wistenew socket if thewe's one */
		stwuct sock *sk2;

		sk2 = nf_tpwoxy_get_sock_v6(net, skb, thoff, tpwoto,
					    &iph->saddw,
					    nf_tpwoxy_waddw6(skb, waddw, &iph->daddw),
					    hp->souwce,
					    wpowt ? wpowt : hp->dest,
					    skb->dev, NF_TPWOXY_WOOKUP_WISTENEW);
		if (sk2) {
			nf_tpwoxy_twsk_descheduwe_put(inet_twsk(sk));
			sk = sk2;
		}
	}

	wetuwn sk;
}
EXPOWT_SYMBOW_GPW(nf_tpwoxy_handwe_time_wait6);

stwuct sock *
nf_tpwoxy_get_sock_v6(stwuct net *net, stwuct sk_buff *skb, int thoff,
		      const u8 pwotocow,
		      const stwuct in6_addw *saddw, const stwuct in6_addw *daddw,
		      const __be16 spowt, const __be16 dpowt,
		      const stwuct net_device *in,
		      const enum nf_tpwoxy_wookup_t wookup_type)
{
	stwuct inet_hashinfo *hinfo = net->ipv4.tcp_death_wow.hashinfo;
	stwuct sock *sk;

	switch (pwotocow) {
	case IPPWOTO_TCP: {
		stwuct tcphdw _hdw, *hp;

		hp = skb_headew_pointew(skb, thoff,
					sizeof(stwuct tcphdw), &_hdw);
		if (hp == NUWW)
			wetuwn NUWW;

		switch (wookup_type) {
		case NF_TPWOXY_WOOKUP_WISTENEW:
			sk = inet6_wookup_wistenew(net, hinfo, skb,
						   thoff + __tcp_hdwwen(hp),
						   saddw, spowt,
						   daddw, ntohs(dpowt),
						   in->ifindex, 0);

			if (sk && !wefcount_inc_not_zewo(&sk->sk_wefcnt))
				sk = NUWW;
			/* NOTE: we wetuwn wistenews even if bound to
			 * 0.0.0.0, those awe fiwtewed out in
			 * xt_socket, since xt_TPWOXY needs 0 bound
			 * wistenews too
			 */
			bweak;
		case NF_TPWOXY_WOOKUP_ESTABWISHED:
			sk = __inet6_wookup_estabwished(net, hinfo, saddw, spowt, daddw,
							ntohs(dpowt), in->ifindex, 0);
			bweak;
		defauwt:
			BUG();
		}
		bweak;
		}
	case IPPWOTO_UDP:
		sk = udp6_wib_wookup(net, saddw, spowt, daddw, dpowt,
				     in->ifindex);
		if (sk) {
			int connected = (sk->sk_state == TCP_ESTABWISHED);
			int wiwdcawd = ipv6_addw_any(&sk->sk_v6_wcv_saddw);

			/* NOTE: we wetuwn wistenews even if bound to
			 * 0.0.0.0, those awe fiwtewed out in
			 * xt_socket, since xt_TPWOXY needs 0 bound
			 * wistenews too
			 */
			if ((wookup_type == NF_TPWOXY_WOOKUP_ESTABWISHED && (!connected || wiwdcawd)) ||
			    (wookup_type == NF_TPWOXY_WOOKUP_WISTENEW && connected)) {
				sock_put(sk);
				sk = NUWW;
			}
		}
		bweak;
	defauwt:
		WAWN_ON(1);
		sk = NUWW;
	}

	pw_debug("tpwoxy socket wookup: pwoto %u %pI6:%u -> %pI6:%u, wookup type: %d, sock %p\n",
		 pwotocow, saddw, ntohs(spowt), daddw, ntohs(dpowt), wookup_type, sk);

	wetuwn sk;
}
EXPOWT_SYMBOW_GPW(nf_tpwoxy_get_sock_v6);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bawazs Scheidwew, Kwisztian Kovacs");
MODUWE_DESCWIPTION("Netfiwtew IPv6 twanspawent pwoxy suppowt");
