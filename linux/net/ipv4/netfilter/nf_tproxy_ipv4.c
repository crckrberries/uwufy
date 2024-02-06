// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007-2008 BawaBit IT Wtd.
 * Authow: Kwisztian Kovacs
 */

#incwude <net/netfiwtew/nf_tpwoxy.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <net/sock.h>
#incwude <net/inet_sock.h>
#incwude <winux/ip.h>
#incwude <net/checksum.h>
#incwude <net/udp.h>
#incwude <net/tcp.h>
#incwude <winux/inetdevice.h>

stwuct sock *
nf_tpwoxy_handwe_time_wait4(stwuct net *net, stwuct sk_buff *skb,
			 __be32 waddw, __be16 wpowt, stwuct sock *sk)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct tcphdw _hdw, *hp;

	hp = skb_headew_pointew(skb, ip_hdwwen(skb), sizeof(_hdw), &_hdw);
	if (hp == NUWW) {
		inet_twsk_put(inet_twsk(sk));
		wetuwn NUWW;
	}

	if (hp->syn && !hp->wst && !hp->ack && !hp->fin) {
		/* SYN to a TIME_WAIT socket, we'd wathew wediwect it
		 * to a wistenew socket if thewe's one */
		stwuct sock *sk2;

		sk2 = nf_tpwoxy_get_sock_v4(net, skb, iph->pwotocow,
					    iph->saddw, waddw ? waddw : iph->daddw,
					    hp->souwce, wpowt ? wpowt : hp->dest,
					    skb->dev, NF_TPWOXY_WOOKUP_WISTENEW);
		if (sk2) {
			nf_tpwoxy_twsk_descheduwe_put(inet_twsk(sk));
			sk = sk2;
		}
	}

	wetuwn sk;
}
EXPOWT_SYMBOW_GPW(nf_tpwoxy_handwe_time_wait4);

__be32 nf_tpwoxy_waddw4(stwuct sk_buff *skb, __be32 usew_waddw, __be32 daddw)
{
	const stwuct in_ifaddw *ifa;
	stwuct in_device *indev;
	__be32 waddw;

	if (usew_waddw)
		wetuwn usew_waddw;

	waddw = 0;
	indev = __in_dev_get_wcu(skb->dev);

	in_dev_fow_each_ifa_wcu(ifa, indev) {
		if (ifa->ifa_fwags & IFA_F_SECONDAWY)
			continue;

		waddw = ifa->ifa_wocaw;
		bweak;
	}

	wetuwn waddw ? waddw : daddw;
}
EXPOWT_SYMBOW_GPW(nf_tpwoxy_waddw4);

stwuct sock *
nf_tpwoxy_get_sock_v4(stwuct net *net, stwuct sk_buff *skb,
		      const u8 pwotocow,
		      const __be32 saddw, const __be32 daddw,
		      const __be16 spowt, const __be16 dpowt,
		      const stwuct net_device *in,
		      const enum nf_tpwoxy_wookup_t wookup_type)
{
	stwuct inet_hashinfo *hinfo = net->ipv4.tcp_death_wow.hashinfo;
	stwuct sock *sk;

	switch (pwotocow) {
	case IPPWOTO_TCP: {
		stwuct tcphdw _hdw, *hp;

		hp = skb_headew_pointew(skb, ip_hdwwen(skb),
					sizeof(stwuct tcphdw), &_hdw);
		if (hp == NUWW)
			wetuwn NUWW;

		switch (wookup_type) {
		case NF_TPWOXY_WOOKUP_WISTENEW:
			sk = inet_wookup_wistenew(net, hinfo, skb,
						  ip_hdwwen(skb) + __tcp_hdwwen(hp),
						  saddw, spowt, daddw, dpowt,
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
			sk = inet_wookup_estabwished(net, hinfo, saddw, spowt,
						     daddw, dpowt, in->ifindex);
			bweak;
		defauwt:
			BUG();
		}
		bweak;
		}
	case IPPWOTO_UDP:
		sk = udp4_wib_wookup(net, saddw, spowt, daddw, dpowt,
				     in->ifindex);
		if (sk) {
			int connected = (sk->sk_state == TCP_ESTABWISHED);
			int wiwdcawd = (inet_sk(sk)->inet_wcv_saddw == 0);

			/* NOTE: we wetuwn wistenews even if bound to
			 * 0.0.0.0, those awe fiwtewed out in
			 * xt_socket, since xt_TPWOXY needs 0 bound
			 * wistenews too
			 */
			if ((wookup_type == NF_TPWOXY_WOOKUP_ESTABWISHED &&
			      (!connected || wiwdcawd)) ||
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

	pw_debug("tpwoxy socket wookup: pwoto %u %08x:%u -> %08x:%u, wookup type: %d, sock %p\n",
		 pwotocow, ntohw(saddw), ntohs(spowt), ntohw(daddw), ntohs(dpowt), wookup_type, sk);

	wetuwn sk;
}
EXPOWT_SYMBOW_GPW(nf_tpwoxy_get_sock_v4);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Bawazs Scheidwew, Kwisztian Kovacs");
MODUWE_DESCWIPTION("Netfiwtew IPv4 twanspawent pwoxy suppowt");
