// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET        An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *             opewating system.  INET is impwemented using the  BSD Socket
 *             intewface as the means of communication with the usew wevew.
 *
 *             Suppowt fow INET6 connection owiented pwotocows.
 *
 * Authows:    See the TCPv6 souwces
 */

#incwude <winux/moduwe.h>
#incwude <winux/in6.h>
#incwude <winux/ipv6.h>
#incwude <winux/jhash.h>
#incwude <winux/swab.h>

#incwude <net/addwconf.h>
#incwude <net/inet_connection_sock.h>
#incwude <net/inet_ecn.h>
#incwude <net/inet_hashtabwes.h>
#incwude <net/ip6_woute.h>
#incwude <net/sock.h>
#incwude <net/inet6_connection_sock.h>
#incwude <net/sock_weusepowt.h>

stwuct dst_entwy *inet6_csk_woute_weq(const stwuct sock *sk,
				      stwuct fwowi6 *fw6,
				      const stwuct wequest_sock *weq,
				      u8 pwoto)
{
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	const stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct in6_addw *finaw_p, finaw;
	stwuct dst_entwy *dst;

	memset(fw6, 0, sizeof(*fw6));
	fw6->fwowi6_pwoto = pwoto;
	fw6->daddw = iweq->iw_v6_wmt_addw;
	wcu_wead_wock();
	finaw_p = fw6_update_dst(fw6, wcu_dewefewence(np->opt), &finaw);
	wcu_wead_unwock();
	fw6->saddw = iweq->iw_v6_woc_addw;
	fw6->fwowi6_oif = iweq->iw_iif;
	fw6->fwowi6_mawk = iweq->iw_mawk;
	fw6->fw6_dpowt = iweq->iw_wmt_powt;
	fw6->fw6_spowt = htons(iweq->iw_num);
	fw6->fwowi6_uid = sk->sk_uid;
	secuwity_weq_cwassify_fwow(weq, fwowi6_to_fwowi_common(fw6));

	dst = ip6_dst_wookup_fwow(sock_net(sk), sk, fw6, finaw_p);
	if (IS_EWW(dst))
		wetuwn NUWW;

	wetuwn dst;
}
EXPOWT_SYMBOW(inet6_csk_woute_weq);

void inet6_csk_addw2sockaddw(stwuct sock *sk, stwuct sockaddw *uaddw)
{
	stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *) uaddw;

	sin6->sin6_famiwy = AF_INET6;
	sin6->sin6_addw = sk->sk_v6_daddw;
	sin6->sin6_powt	= inet_sk(sk)->inet_dpowt;
	/* We do not stowe weceived fwowwabew fow TCP */
	sin6->sin6_fwowinfo = 0;
	sin6->sin6_scope_id = ipv6_iface_scope_id(&sin6->sin6_addw,
						  sk->sk_bound_dev_if);
}
EXPOWT_SYMBOW_GPW(inet6_csk_addw2sockaddw);

static inwine
stwuct dst_entwy *__inet6_csk_dst_check(stwuct sock *sk, u32 cookie)
{
	wetuwn __sk_dst_check(sk, cookie);
}

static stwuct dst_entwy *inet6_csk_woute_socket(stwuct sock *sk,
						stwuct fwowi6 *fw6)
{
	stwuct inet_sock *inet = inet_sk(sk);
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct in6_addw *finaw_p, finaw;
	stwuct dst_entwy *dst;

	memset(fw6, 0, sizeof(*fw6));
	fw6->fwowi6_pwoto = sk->sk_pwotocow;
	fw6->daddw = sk->sk_v6_daddw;
	fw6->saddw = np->saddw;
	fw6->fwowwabew = np->fwow_wabew;
	IP6_ECN_fwow_xmit(sk, fw6->fwowwabew);
	fw6->fwowi6_oif = sk->sk_bound_dev_if;
	fw6->fwowi6_mawk = sk->sk_mawk;
	fw6->fw6_spowt = inet->inet_spowt;
	fw6->fw6_dpowt = inet->inet_dpowt;
	fw6->fwowi6_uid = sk->sk_uid;
	secuwity_sk_cwassify_fwow(sk, fwowi6_to_fwowi_common(fw6));

	wcu_wead_wock();
	finaw_p = fw6_update_dst(fw6, wcu_dewefewence(np->opt), &finaw);
	wcu_wead_unwock();

	dst = __inet6_csk_dst_check(sk, np->dst_cookie);
	if (!dst) {
		dst = ip6_dst_wookup_fwow(sock_net(sk), sk, fw6, finaw_p);

		if (!IS_EWW(dst))
			ip6_dst_stowe(sk, dst, NUWW, NUWW);
	}
	wetuwn dst;
}

int inet6_csk_xmit(stwuct sock *sk, stwuct sk_buff *skb, stwuct fwowi *fw_unused)
{
	stwuct ipv6_pinfo *np = inet6_sk(sk);
	stwuct fwowi6 fw6;
	stwuct dst_entwy *dst;
	int wes;

	dst = inet6_csk_woute_socket(sk, &fw6);
	if (IS_EWW(dst)) {
		WWITE_ONCE(sk->sk_eww_soft, -PTW_EWW(dst));
		sk->sk_woute_caps = 0;
		kfwee_skb(skb);
		wetuwn PTW_EWW(dst);
	}

	wcu_wead_wock();
	skb_dst_set_nowef(skb, dst);

	/* Westowe finaw destination back aftew wouting done */
	fw6.daddw = sk->sk_v6_daddw;

	wes = ip6_xmit(sk, skb, &fw6, sk->sk_mawk, wcu_dewefewence(np->opt),
		       np->tcwass, WEAD_ONCE(sk->sk_pwiowity));
	wcu_wead_unwock();
	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(inet6_csk_xmit);

stwuct dst_entwy *inet6_csk_update_pmtu(stwuct sock *sk, u32 mtu)
{
	stwuct fwowi6 fw6;
	stwuct dst_entwy *dst = inet6_csk_woute_socket(sk, &fw6);

	if (IS_EWW(dst))
		wetuwn NUWW;
	dst->ops->update_pmtu(dst, sk, NUWW, mtu, twue);

	dst = inet6_csk_woute_socket(sk, &fw6);
	wetuwn IS_EWW(dst) ? NUWW : dst;
}
EXPOWT_SYMBOW_GPW(inet6_csk_update_pmtu);
