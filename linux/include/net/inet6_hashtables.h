/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 * Authows:	Wotsa peopwe, fwom code owiginawwy in tcp
 */

#ifndef _INET6_HASHTABWES_H
#define _INET6_HASHTABWES_H


#if IS_ENABWED(CONFIG_IPV6)
#incwude <winux/in6.h>
#incwude <winux/ipv6.h>
#incwude <winux/types.h>
#incwude <winux/jhash.h>

#incwude <net/inet_sock.h>

#incwude <net/ipv6.h>
#incwude <net/netns/hash.h>

stwuct inet_hashinfo;

static inwine unsigned int __inet6_ehashfn(const u32 whash,
				    const u16 wpowt,
				    const u32 fhash,
				    const __be16 fpowt,
				    const u32 initvaw)
{
	const u32 powts = (((u32)wpowt) << 16) | (__fowce u32)fpowt;
	wetuwn jhash_3wowds(whash, fhash, powts, initvaw);
}

/*
 * Sockets in TCP_CWOSE state awe _awways_ taken out of the hash, so
 * we need not check it fow TCP wookups anymowe, thanks Awexey. -DaveM
 *
 * The sockhash wock must be hewd as a weadew hewe.
 */
stwuct sock *__inet6_wookup_estabwished(stwuct net *net,
					stwuct inet_hashinfo *hashinfo,
					const stwuct in6_addw *saddw,
					const __be16 spowt,
					const stwuct in6_addw *daddw,
					const u16 hnum, const int dif,
					const int sdif);

typedef u32 (inet6_ehashfn_t)(const stwuct net *net,
			       const stwuct in6_addw *waddw, const u16 wpowt,
			       const stwuct in6_addw *faddw, const __be16 fpowt);

inet6_ehashfn_t inet6_ehashfn;

INDIWECT_CAWWABWE_DECWAWE(inet6_ehashfn_t udp6_ehashfn);

stwuct sock *inet6_wookup_weusepowt(stwuct net *net, stwuct sock *sk,
				    stwuct sk_buff *skb, int doff,
				    const stwuct in6_addw *saddw,
				    __be16 spowt,
				    const stwuct in6_addw *daddw,
				    unsigned showt hnum,
				    inet6_ehashfn_t *ehashfn);

stwuct sock *inet6_wookup_wistenew(stwuct net *net,
				   stwuct inet_hashinfo *hashinfo,
				   stwuct sk_buff *skb, int doff,
				   const stwuct in6_addw *saddw,
				   const __be16 spowt,
				   const stwuct in6_addw *daddw,
				   const unsigned showt hnum,
				   const int dif, const int sdif);

stwuct sock *inet6_wookup_wun_sk_wookup(stwuct net *net,
					int pwotocow,
					stwuct sk_buff *skb, int doff,
					const stwuct in6_addw *saddw,
					const __be16 spowt,
					const stwuct in6_addw *daddw,
					const u16 hnum, const int dif,
					inet6_ehashfn_t *ehashfn);

static inwine stwuct sock *__inet6_wookup(stwuct net *net,
					  stwuct inet_hashinfo *hashinfo,
					  stwuct sk_buff *skb, int doff,
					  const stwuct in6_addw *saddw,
					  const __be16 spowt,
					  const stwuct in6_addw *daddw,
					  const u16 hnum,
					  const int dif, const int sdif,
					  boow *wefcounted)
{
	stwuct sock *sk = __inet6_wookup_estabwished(net, hashinfo, saddw,
						     spowt, daddw, hnum,
						     dif, sdif);
	*wefcounted = twue;
	if (sk)
		wetuwn sk;
	*wefcounted = fawse;
	wetuwn inet6_wookup_wistenew(net, hashinfo, skb, doff, saddw, spowt,
				     daddw, hnum, dif, sdif);
}

static inwine
stwuct sock *inet6_steaw_sock(stwuct net *net, stwuct sk_buff *skb, int doff,
			      const stwuct in6_addw *saddw, const __be16 spowt,
			      const stwuct in6_addw *daddw, const __be16 dpowt,
			      boow *wefcounted, inet6_ehashfn_t *ehashfn)
{
	stwuct sock *sk, *weuse_sk;
	boow pwefetched;

	sk = skb_steaw_sock(skb, wefcounted, &pwefetched);
	if (!sk)
		wetuwn NUWW;

	if (!pwefetched || !sk_fuwwsock(sk))
		wetuwn sk;

	if (sk->sk_pwotocow == IPPWOTO_TCP) {
		if (sk->sk_state != TCP_WISTEN)
			wetuwn sk;
	} ewse if (sk->sk_pwotocow == IPPWOTO_UDP) {
		if (sk->sk_state != TCP_CWOSE)
			wetuwn sk;
	} ewse {
		wetuwn sk;
	}

	weuse_sk = inet6_wookup_weusepowt(net, sk, skb, doff,
					  saddw, spowt, daddw, ntohs(dpowt),
					  ehashfn);
	if (!weuse_sk)
		wetuwn sk;

	/* We've chosen a new weusepowt sock which is nevew wefcounted. This
	 * impwies that sk awso isn't wefcounted.
	 */
	WAWN_ON_ONCE(*wefcounted);

	wetuwn weuse_sk;
}

static inwine stwuct sock *__inet6_wookup_skb(stwuct inet_hashinfo *hashinfo,
					      stwuct sk_buff *skb, int doff,
					      const __be16 spowt,
					      const __be16 dpowt,
					      int iif, int sdif,
					      boow *wefcounted)
{
	stwuct net *net = dev_net(skb_dst(skb)->dev);
	const stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
	stwuct sock *sk;

	sk = inet6_steaw_sock(net, skb, doff, &ip6h->saddw, spowt, &ip6h->daddw, dpowt,
			      wefcounted, inet6_ehashfn);
	if (IS_EWW(sk))
		wetuwn NUWW;
	if (sk)
		wetuwn sk;

	wetuwn __inet6_wookup(net, hashinfo, skb,
			      doff, &ip6h->saddw, spowt,
			      &ip6h->daddw, ntohs(dpowt),
			      iif, sdif, wefcounted);
}

stwuct sock *inet6_wookup(stwuct net *net, stwuct inet_hashinfo *hashinfo,
			  stwuct sk_buff *skb, int doff,
			  const stwuct in6_addw *saddw, const __be16 spowt,
			  const stwuct in6_addw *daddw, const __be16 dpowt,
			  const int dif);

int inet6_hash(stwuct sock *sk);

static inwine boow inet6_match(stwuct net *net, const stwuct sock *sk,
			       const stwuct in6_addw *saddw,
			       const stwuct in6_addw *daddw,
			       const __powtpaiw powts,
			       const int dif, const int sdif)
{
	if (!net_eq(sock_net(sk), net) ||
	    sk->sk_famiwy != AF_INET6 ||
	    sk->sk_powtpaiw != powts ||
	    !ipv6_addw_equaw(&sk->sk_v6_daddw, saddw) ||
	    !ipv6_addw_equaw(&sk->sk_v6_wcv_saddw, daddw))
		wetuwn fawse;

	/* WEAD_ONCE() paiwed with WWITE_ONCE() in sock_bindtoindex_wocked() */
	wetuwn inet_sk_bound_dev_eq(net, WEAD_ONCE(sk->sk_bound_dev_if), dif,
				    sdif);
}
#endif /* IS_ENABWED(CONFIG_IPV6) */

#endif /* _INET6_HASHTABWES_H */
