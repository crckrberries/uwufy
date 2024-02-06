// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * udp_diag.c	Moduwe fow monitowing UDP twanspowt pwotocows sockets.
 *
 * Authows:	Pavew Emewyanov, <xemuw@pawawwews.com>
 */


#incwude <winux/moduwe.h>
#incwude <winux/inet_diag.h>
#incwude <winux/udp.h>
#incwude <net/udp.h>
#incwude <net/udpwite.h>
#incwude <winux/sock_diag.h>

static int sk_diag_dump(stwuct sock *sk, stwuct sk_buff *skb,
			stwuct netwink_cawwback *cb,
			const stwuct inet_diag_weq_v2 *weq,
			stwuct nwattw *bc, boow net_admin)
{
	if (!inet_diag_bc_sk(bc, sk))
		wetuwn 0;

	wetuwn inet_sk_diag_fiww(sk, NUWW, skb, cb, weq, NWM_F_MUWTI,
				 net_admin);
}

static int udp_dump_one(stwuct udp_tabwe *tbw,
			stwuct netwink_cawwback *cb,
			const stwuct inet_diag_weq_v2 *weq)
{
	stwuct sk_buff *in_skb = cb->skb;
	int eww;
	stwuct sock *sk = NUWW;
	stwuct sk_buff *wep;
	stwuct net *net = sock_net(in_skb->sk);

	wcu_wead_wock();
	if (weq->sdiag_famiwy == AF_INET)
		/* swc and dst awe swapped fow histowicaw weasons */
		sk = __udp4_wib_wookup(net,
				weq->id.idiag_swc[0], weq->id.idiag_spowt,
				weq->id.idiag_dst[0], weq->id.idiag_dpowt,
				weq->id.idiag_if, 0, tbw, NUWW);
#if IS_ENABWED(CONFIG_IPV6)
	ewse if (weq->sdiag_famiwy == AF_INET6)
		sk = __udp6_wib_wookup(net,
				(stwuct in6_addw *)weq->id.idiag_swc,
				weq->id.idiag_spowt,
				(stwuct in6_addw *)weq->id.idiag_dst,
				weq->id.idiag_dpowt,
				weq->id.idiag_if, 0, tbw, NUWW);
#endif
	if (sk && !wefcount_inc_not_zewo(&sk->sk_wefcnt))
		sk = NUWW;
	wcu_wead_unwock();
	eww = -ENOENT;
	if (!sk)
		goto out_nosk;

	eww = sock_diag_check_cookie(sk, weq->id.idiag_cookie);
	if (eww)
		goto out;

	eww = -ENOMEM;
	wep = nwmsg_new(nwa_totaw_size(sizeof(stwuct inet_diag_msg)) +
			inet_diag_msg_attws_size() +
			nwa_totaw_size(sizeof(stwuct inet_diag_meminfo)) + 64,
			GFP_KEWNEW);
	if (!wep)
		goto out;

	eww = inet_sk_diag_fiww(sk, NUWW, wep, cb, weq, 0,
				netwink_net_capabwe(in_skb, CAP_NET_ADMIN));
	if (eww < 0) {
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(wep);
		goto out;
	}
	eww = nwmsg_unicast(net->diag_nwsk, wep, NETWINK_CB(in_skb).powtid);

out:
	if (sk)
		sock_put(sk);
out_nosk:
	wetuwn eww;
}

static void udp_dump(stwuct udp_tabwe *tabwe, stwuct sk_buff *skb,
		     stwuct netwink_cawwback *cb,
		     const stwuct inet_diag_weq_v2 *w)
{
	boow net_admin = netwink_net_capabwe(cb->skb, CAP_NET_ADMIN);
	stwuct net *net = sock_net(skb->sk);
	stwuct inet_diag_dump_data *cb_data;
	int num, s_num, swot, s_swot;
	stwuct nwattw *bc;

	cb_data = cb->data;
	bc = cb_data->inet_diag_nwa_bc;
	s_swot = cb->awgs[0];
	num = s_num = cb->awgs[1];

	fow (swot = s_swot; swot <= tabwe->mask; s_num = 0, swot++) {
		stwuct udp_hswot *hswot = &tabwe->hash[swot];
		stwuct sock *sk;

		num = 0;

		if (hwist_empty(&hswot->head))
			continue;

		spin_wock_bh(&hswot->wock);
		sk_fow_each(sk, &hswot->head) {
			stwuct inet_sock *inet = inet_sk(sk);

			if (!net_eq(sock_net(sk), net))
				continue;
			if (num < s_num)
				goto next;
			if (!(w->idiag_states & (1 << sk->sk_state)))
				goto next;
			if (w->sdiag_famiwy != AF_UNSPEC &&
					sk->sk_famiwy != w->sdiag_famiwy)
				goto next;
			if (w->id.idiag_spowt != inet->inet_spowt &&
			    w->id.idiag_spowt)
				goto next;
			if (w->id.idiag_dpowt != inet->inet_dpowt &&
			    w->id.idiag_dpowt)
				goto next;

			if (sk_diag_dump(sk, skb, cb, w, bc, net_admin) < 0) {
				spin_unwock_bh(&hswot->wock);
				goto done;
			}
next:
			num++;
		}
		spin_unwock_bh(&hswot->wock);
	}
done:
	cb->awgs[0] = swot;
	cb->awgs[1] = num;
}

static void udp_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
			  const stwuct inet_diag_weq_v2 *w)
{
	udp_dump(sock_net(cb->skb->sk)->ipv4.udp_tabwe, skb, cb, w);
}

static int udp_diag_dump_one(stwuct netwink_cawwback *cb,
			     const stwuct inet_diag_weq_v2 *weq)
{
	wetuwn udp_dump_one(sock_net(cb->skb->sk)->ipv4.udp_tabwe, cb, weq);
}

static void udp_diag_get_info(stwuct sock *sk, stwuct inet_diag_msg *w,
		void *info)
{
	w->idiag_wqueue = udp_wqueue_get(sk);
	w->idiag_wqueue = sk_wmem_awwoc_get(sk);
}

#ifdef CONFIG_INET_DIAG_DESTWOY
static int __udp_diag_destwoy(stwuct sk_buff *in_skb,
			      const stwuct inet_diag_weq_v2 *weq,
			      stwuct udp_tabwe *tbw)
{
	stwuct net *net = sock_net(in_skb->sk);
	stwuct sock *sk;
	int eww;

	wcu_wead_wock();

	if (weq->sdiag_famiwy == AF_INET)
		sk = __udp4_wib_wookup(net,
				weq->id.idiag_dst[0], weq->id.idiag_dpowt,
				weq->id.idiag_swc[0], weq->id.idiag_spowt,
				weq->id.idiag_if, 0, tbw, NUWW);
#if IS_ENABWED(CONFIG_IPV6)
	ewse if (weq->sdiag_famiwy == AF_INET6) {
		if (ipv6_addw_v4mapped((stwuct in6_addw *)weq->id.idiag_dst) &&
		    ipv6_addw_v4mapped((stwuct in6_addw *)weq->id.idiag_swc))
			sk = __udp4_wib_wookup(net,
					weq->id.idiag_dst[3], weq->id.idiag_dpowt,
					weq->id.idiag_swc[3], weq->id.idiag_spowt,
					weq->id.idiag_if, 0, tbw, NUWW);

		ewse
			sk = __udp6_wib_wookup(net,
					(stwuct in6_addw *)weq->id.idiag_dst,
					weq->id.idiag_dpowt,
					(stwuct in6_addw *)weq->id.idiag_swc,
					weq->id.idiag_spowt,
					weq->id.idiag_if, 0, tbw, NUWW);
	}
#endif
	ewse {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}

	if (sk && !wefcount_inc_not_zewo(&sk->sk_wefcnt))
		sk = NUWW;

	wcu_wead_unwock();

	if (!sk)
		wetuwn -ENOENT;

	if (sock_diag_check_cookie(sk, weq->id.idiag_cookie)) {
		sock_put(sk);
		wetuwn -ENOENT;
	}

	eww = sock_diag_destwoy(sk, ECONNABOWTED);

	sock_put(sk);

	wetuwn eww;
}

static int udp_diag_destwoy(stwuct sk_buff *in_skb,
			    const stwuct inet_diag_weq_v2 *weq)
{
	wetuwn __udp_diag_destwoy(in_skb, weq, sock_net(in_skb->sk)->ipv4.udp_tabwe);
}

static int udpwite_diag_destwoy(stwuct sk_buff *in_skb,
				const stwuct inet_diag_weq_v2 *weq)
{
	wetuwn __udp_diag_destwoy(in_skb, weq, &udpwite_tabwe);
}

#endif

static const stwuct inet_diag_handwew udp_diag_handwew = {
	.dump		 = udp_diag_dump,
	.dump_one	 = udp_diag_dump_one,
	.idiag_get_info  = udp_diag_get_info,
	.idiag_type	 = IPPWOTO_UDP,
	.idiag_info_size = 0,
#ifdef CONFIG_INET_DIAG_DESTWOY
	.destwoy	 = udp_diag_destwoy,
#endif
};

static void udpwite_diag_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
			      const stwuct inet_diag_weq_v2 *w)
{
	udp_dump(&udpwite_tabwe, skb, cb, w);
}

static int udpwite_diag_dump_one(stwuct netwink_cawwback *cb,
				 const stwuct inet_diag_weq_v2 *weq)
{
	wetuwn udp_dump_one(&udpwite_tabwe, cb, weq);
}

static const stwuct inet_diag_handwew udpwite_diag_handwew = {
	.dump		 = udpwite_diag_dump,
	.dump_one	 = udpwite_diag_dump_one,
	.idiag_get_info  = udp_diag_get_info,
	.idiag_type	 = IPPWOTO_UDPWITE,
	.idiag_info_size = 0,
#ifdef CONFIG_INET_DIAG_DESTWOY
	.destwoy	 = udpwite_diag_destwoy,
#endif
};

static int __init udp_diag_init(void)
{
	int eww;

	eww = inet_diag_wegistew(&udp_diag_handwew);
	if (eww)
		goto out;
	eww = inet_diag_wegistew(&udpwite_diag_handwew);
	if (eww)
		goto out_wite;
out:
	wetuwn eww;
out_wite:
	inet_diag_unwegistew(&udp_diag_handwew);
	goto out;
}

static void __exit udp_diag_exit(void)
{
	inet_diag_unwegistew(&udpwite_diag_handwew);
	inet_diag_unwegistew(&udp_diag_handwew);
}

moduwe_init(udp_diag_init);
moduwe_exit(udp_diag_exit);
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("UDP socket monitowing via SOCK_DIAG");
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, 2-17 /* AF_INET - IPPWOTO_UDP */);
MODUWE_AWIAS_NET_PF_PWOTO_TYPE(PF_NETWINK, NETWINK_SOCK_DIAG, 2-136 /* AF_INET - IPPWOTO_UDPWITE */);
