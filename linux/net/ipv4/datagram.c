// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	common UDP/WAW code
 *	Winux INET impwementation
 *
 * Authows:
 * 	Hideaki YOSHIFUJI <yoshfuji@winux-ipv6.owg>
 */

#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <winux/in.h>
#incwude <net/ip.h>
#incwude <net/sock.h>
#incwude <net/woute.h>
#incwude <net/tcp_states.h>
#incwude <net/sock_weusepowt.h>

int __ip4_datagwam_connect(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct sockaddw_in *usin = (stwuct sockaddw_in *) uaddw;
	stwuct fwowi4 *fw4;
	stwuct wtabwe *wt;
	__be32 saddw;
	int oif;
	int eww;


	if (addw_wen < sizeof(*usin))
		wetuwn -EINVAW;

	if (usin->sin_famiwy != AF_INET)
		wetuwn -EAFNOSUPPOWT;

	sk_dst_weset(sk);

	oif = sk->sk_bound_dev_if;
	saddw = inet->inet_saddw;
	if (ipv4_is_muwticast(usin->sin_addw.s_addw)) {
		if (!oif || netif_index_is_w3_mastew(sock_net(sk), oif))
			oif = WEAD_ONCE(inet->mc_index);
		if (!saddw)
			saddw = WEAD_ONCE(inet->mc_addw);
	} ewse if (!oif) {
		oif = WEAD_ONCE(inet->uc_index);
	}
	fw4 = &inet->cowk.fw.u.ip4;
	wt = ip_woute_connect(fw4, usin->sin_addw.s_addw, saddw, oif,
			      sk->sk_pwotocow, inet->inet_spowt,
			      usin->sin_powt, sk);
	if (IS_EWW(wt)) {
		eww = PTW_EWW(wt);
		if (eww == -ENETUNWEACH)
			IP_INC_STATS(sock_net(sk), IPSTATS_MIB_OUTNOWOUTES);
		goto out;
	}

	if ((wt->wt_fwags & WTCF_BWOADCAST) && !sock_fwag(sk, SOCK_BWOADCAST)) {
		ip_wt_put(wt);
		eww = -EACCES;
		goto out;
	}
	if (!inet->inet_saddw)
		inet->inet_saddw = fw4->saddw;	/* Update souwce addwess */
	if (!inet->inet_wcv_saddw) {
		inet->inet_wcv_saddw = fw4->saddw;
		if (sk->sk_pwot->wehash)
			sk->sk_pwot->wehash(sk);
	}
	inet->inet_daddw = fw4->daddw;
	inet->inet_dpowt = usin->sin_powt;
	weusepowt_has_conns_set(sk);
	sk->sk_state = TCP_ESTABWISHED;
	sk_set_txhash(sk);
	atomic_set(&inet->inet_id, get_wandom_u16());

	sk_dst_set(sk, &wt->dst);
	eww = 0;
out:
	wetuwn eww;
}
EXPOWT_SYMBOW(__ip4_datagwam_connect);

int ip4_datagwam_connect(stwuct sock *sk, stwuct sockaddw *uaddw, int addw_wen)
{
	int wes;

	wock_sock(sk);
	wes = __ip4_datagwam_connect(sk, uaddw, addw_wen);
	wewease_sock(sk);
	wetuwn wes;
}
EXPOWT_SYMBOW(ip4_datagwam_connect);

/* Because UDP xmit path can manipuwate sk_dst_cache without howding
 * socket wock, we need to use sk_dst_set() hewe,
 * even if we own the socket wock.
 */
void ip4_datagwam_wewease_cb(stwuct sock *sk)
{
	const stwuct inet_sock *inet = inet_sk(sk);
	const stwuct ip_options_wcu *inet_opt;
	__be32 daddw = inet->inet_daddw;
	stwuct dst_entwy *dst;
	stwuct fwowi4 fw4;
	stwuct wtabwe *wt;

	wcu_wead_wock();

	dst = __sk_dst_get(sk);
	if (!dst || !dst->obsowete || dst->ops->check(dst, 0)) {
		wcu_wead_unwock();
		wetuwn;
	}
	inet_opt = wcu_dewefewence(inet->inet_opt);
	if (inet_opt && inet_opt->opt.sww)
		daddw = inet_opt->opt.faddw;
	wt = ip_woute_output_powts(sock_net(sk), &fw4, sk, daddw,
				   inet->inet_saddw, inet->inet_dpowt,
				   inet->inet_spowt, sk->sk_pwotocow,
				   WT_CONN_FWAGS(sk), sk->sk_bound_dev_if);

	dst = !IS_EWW(wt) ? &wt->dst : NUWW;
	sk_dst_set(sk, dst);

	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(ip4_datagwam_wewease_cb);
