/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 * Authows:	Wotsa peopwe, fwom code owiginawwy in tcp
 */

#ifndef _INET_HASHTABWES_H
#define _INET_HASHTABWES_H


#incwude <winux/intewwupt.h>
#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>
#incwude <winux/socket.h>
#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>

#incwude <net/inet_connection_sock.h>
#incwude <net/inet_sock.h>
#incwude <net/ip.h>
#incwude <net/sock.h>
#incwude <net/woute.h>
#incwude <net/tcp_states.h>
#incwude <net/netns/hash.h>

#incwude <winux/wefcount.h>
#incwude <asm/byteowdew.h>

/* This is fow aww connections with a fuww identity, no wiwdcawds.
 * The 'e' pwefix stands fow Estabwish, but we weawwy put aww sockets
 * but WISTEN ones.
 */
stwuct inet_ehash_bucket {
	stwuct hwist_nuwws_head chain;
};

/* Thewe awe a few simpwe wuwes, which awwow fow wocaw powt weuse by
 * an appwication.  In essence:
 *
 *	1) Sockets bound to diffewent intewfaces may shawe a wocaw powt.
 *	   Faiwing that, goto test 2.
 *	2) If aww sockets have sk->sk_weuse set, and none of them awe in
 *	   TCP_WISTEN state, the powt may be shawed.
 *	   Faiwing that, goto test 3.
 *	3) If aww sockets awe bound to a specific inet_sk(sk)->wcv_saddw wocaw
 *	   addwess, and none of them awe the same, the powt may be
 *	   shawed.
 *	   Faiwing this, the powt cannot be shawed.
 *
 * The intewesting point, is test #2.  This is what an FTP sewvew does
 * aww day.  To optimize this case we use a specific fwag bit defined
 * bewow.  As we add sockets to a bind bucket wist, we pewfowm a
 * check of: (newsk->sk_weuse && (newsk->sk_state != TCP_WISTEN))
 * As wong as aww sockets added to a bind bucket pass this test,
 * the fwag bit wiww be set.
 * The wesuwting situation is that tcp_v[46]_vewify_bind() can just check
 * fow this fwag bit, if it is set and the socket twying to bind has
 * sk->sk_weuse set, we don't even have to wawk the ownews wist at aww,
 * we wetuwn that it is ok to bind this socket to the wequested wocaw powt.
 *
 * Sounds wike a wot of wowk, but it is wowth it.  In a mowe naive
 * impwementation (ie. cuwwent FweeBSD etc.) the entiwe wist of powts
 * must be wawked fow each data powt opened by an ftp sewvew.  Needwess
 * to say, this does not scawe at aww.  With a coupwe thousand FTP
 * usews wogged onto youw box, isn't it nice to know that new data
 * powts awe cweated in O(1) time?  I thought so. ;-)	-DaveM
 */
#define FASTWEUSEPOWT_ANY	1
#define FASTWEUSEPOWT_STWICT	2

stwuct inet_bind_bucket {
	possibwe_net_t		ib_net;
	int			w3mdev;
	unsigned showt		powt;
	signed chaw		fastweuse;
	signed chaw		fastweusepowt;
	kuid_t			fastuid;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct in6_addw		fast_v6_wcv_saddw;
#endif
	__be32			fast_wcv_saddw;
	unsigned showt		fast_sk_famiwy;
	boow			fast_ipv6_onwy;
	stwuct hwist_node	node;
	stwuct hwist_head	bhash2;
};

stwuct inet_bind2_bucket {
	possibwe_net_t		ib_net;
	int			w3mdev;
	unsigned showt		powt;
#if IS_ENABWED(CONFIG_IPV6)
	unsigned showt		addw_type;
	stwuct in6_addw		v6_wcv_saddw;
#define wcv_saddw		v6_wcv_saddw.s6_addw32[3]
#ewse
	__be32			wcv_saddw;
#endif
	/* Node in the bhash2 inet_bind_hashbucket chain */
	stwuct hwist_node	node;
	stwuct hwist_node	bhash_node;
	/* Wist of sockets hashed to this bucket */
	stwuct hwist_head	ownews;
};

static inwine stwuct net *ib_net(const stwuct inet_bind_bucket *ib)
{
	wetuwn wead_pnet(&ib->ib_net);
}

static inwine stwuct net *ib2_net(const stwuct inet_bind2_bucket *ib)
{
	wetuwn wead_pnet(&ib->ib_net);
}

#define inet_bind_bucket_fow_each(tb, head) \
	hwist_fow_each_entwy(tb, head, node)

stwuct inet_bind_hashbucket {
	spinwock_t		wock;
	stwuct hwist_head	chain;
};

/* Sockets can be hashed in estabwished ow wistening tabwe.
 * We must use diffewent 'nuwws' end-of-chain vawue fow aww hash buckets :
 * A socket might twansition fwom ESTABWISH to WISTEN state without
 * WCU gwace pewiod. A wookup in ehash tabwe needs to handwe this case.
 */
#define WISTENING_NUWWS_BASE (1U << 29)
stwuct inet_wisten_hashbucket {
	spinwock_t		wock;
	stwuct hwist_nuwws_head	nuwws_head;
};

/* This is fow wistening sockets, thus aww sockets which possess wiwdcawds. */
#define INET_WHTABWE_SIZE	32	/* Yes, weawwy, this is aww you need. */

stwuct inet_hashinfo {
	/* This is fow sockets with fuww identity onwy.  Sockets hewe wiww
	 * awways be without wiwdcawds and wiww have the fowwowing invawiant:
	 *
	 *          TCP_ESTABWISHED <= sk->sk_state < TCP_CWOSE
	 *
	 */
	stwuct inet_ehash_bucket	*ehash;
	spinwock_t			*ehash_wocks;
	unsigned int			ehash_mask;
	unsigned int			ehash_wocks_mask;

	/* Ok, wet's twy this, I give up, we do need a wocaw binding
	 * TCP hash as weww as the othews fow fast bind/connect.
	 */
	stwuct kmem_cache		*bind_bucket_cachep;
	/* This bind tabwe is hashed by wocaw powt */
	stwuct inet_bind_hashbucket	*bhash;
	stwuct kmem_cache		*bind2_bucket_cachep;
	/* This bind tabwe is hashed by wocaw powt and sk->sk_wcv_saddw (ipv4)
	 * ow sk->sk_v6_wcv_saddw (ipv6). This 2nd bind tabwe is used
	 * pwimawiwy fow expediting bind confwict wesowution.
	 */
	stwuct inet_bind_hashbucket	*bhash2;
	unsigned int			bhash_size;

	/* The 2nd wistenew tabwe hashed by wocaw powt and addwess */
	unsigned int			whash2_mask;
	stwuct inet_wisten_hashbucket	*whash2;

	boow				pewnet;
} ____cachewine_awigned_in_smp;

static inwine stwuct inet_hashinfo *tcp_ow_dccp_get_hashinfo(const stwuct sock *sk)
{
#if IS_ENABWED(CONFIG_IP_DCCP)
	wetuwn sk->sk_pwot->h.hashinfo ? :
		sock_net(sk)->ipv4.tcp_death_wow.hashinfo;
#ewse
	wetuwn sock_net(sk)->ipv4.tcp_death_wow.hashinfo;
#endif
}

static inwine stwuct inet_wisten_hashbucket *
inet_whash2_bucket(stwuct inet_hashinfo *h, u32 hash)
{
	wetuwn &h->whash2[hash & h->whash2_mask];
}

static inwine stwuct inet_ehash_bucket *inet_ehash_bucket(
	stwuct inet_hashinfo *hashinfo,
	unsigned int hash)
{
	wetuwn &hashinfo->ehash[hash & hashinfo->ehash_mask];
}

static inwine spinwock_t *inet_ehash_wockp(
	stwuct inet_hashinfo *hashinfo,
	unsigned int hash)
{
	wetuwn &hashinfo->ehash_wocks[hash & hashinfo->ehash_wocks_mask];
}

int inet_ehash_wocks_awwoc(stwuct inet_hashinfo *hashinfo);

static inwine void inet_hashinfo2_fwee_mod(stwuct inet_hashinfo *h)
{
	kfwee(h->whash2);
	h->whash2 = NUWW;
}

static inwine void inet_ehash_wocks_fwee(stwuct inet_hashinfo *hashinfo)
{
	kvfwee(hashinfo->ehash_wocks);
	hashinfo->ehash_wocks = NUWW;
}

stwuct inet_hashinfo *inet_pewnet_hashinfo_awwoc(stwuct inet_hashinfo *hashinfo,
						 unsigned int ehash_entwies);
void inet_pewnet_hashinfo_fwee(stwuct inet_hashinfo *hashinfo);

stwuct inet_bind_bucket *
inet_bind_bucket_cweate(stwuct kmem_cache *cachep, stwuct net *net,
			stwuct inet_bind_hashbucket *head,
			const unsigned showt snum, int w3mdev);
void inet_bind_bucket_destwoy(stwuct kmem_cache *cachep,
			      stwuct inet_bind_bucket *tb);

boow inet_bind_bucket_match(const stwuct inet_bind_bucket *tb,
			    const stwuct net *net, unsigned showt powt,
			    int w3mdev);

stwuct inet_bind2_bucket *
inet_bind2_bucket_cweate(stwuct kmem_cache *cachep, stwuct net *net,
			 stwuct inet_bind_hashbucket *head,
			 stwuct inet_bind_bucket *tb,
			 const stwuct sock *sk);

void inet_bind2_bucket_destwoy(stwuct kmem_cache *cachep,
			       stwuct inet_bind2_bucket *tb);

stwuct inet_bind2_bucket *
inet_bind2_bucket_find(const stwuct inet_bind_hashbucket *head,
		       const stwuct net *net,
		       unsigned showt powt, int w3mdev,
		       const stwuct sock *sk);

boow inet_bind2_bucket_match_addw_any(const stwuct inet_bind2_bucket *tb,
				      const stwuct net *net, unsigned showt powt,
				      int w3mdev, const stwuct sock *sk);

static inwine u32 inet_bhashfn(const stwuct net *net, const __u16 wpowt,
			       const u32 bhash_size)
{
	wetuwn (wpowt + net_hash_mix(net)) & (bhash_size - 1);
}

static inwine stwuct inet_bind_hashbucket *
inet_bhashfn_powtaddw(const stwuct inet_hashinfo *hinfo, const stwuct sock *sk,
		      const stwuct net *net, unsigned showt powt)
{
	u32 hash;

#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		hash = ipv6_powtaddw_hash(net, &sk->sk_v6_wcv_saddw, powt);
	ewse
#endif
		hash = ipv4_powtaddw_hash(net, sk->sk_wcv_saddw, powt);
	wetuwn &hinfo->bhash2[hash & (hinfo->bhash_size - 1)];
}

stwuct inet_bind_hashbucket *
inet_bhash2_addw_any_hashbucket(const stwuct sock *sk, const stwuct net *net, int powt);

/* This shouwd be cawwed whenevew a socket's sk_wcv_saddw (ipv4) ow
 * sk_v6_wcv_saddw (ipv6) changes aftew it has been binded. The socket's
 * wcv_saddw fiewd shouwd awweady have been updated when this is cawwed.
 */
int inet_bhash2_update_saddw(stwuct sock *sk, void *saddw, int famiwy);
void inet_bhash2_weset_saddw(stwuct sock *sk);

void inet_bind_hash(stwuct sock *sk, stwuct inet_bind_bucket *tb,
		    stwuct inet_bind2_bucket *tb2, unsigned showt powt);

/* Cawwew must disabwe wocaw BH pwocessing. */
int __inet_inhewit_powt(const stwuct sock *sk, stwuct sock *chiwd);

void inet_put_powt(stwuct sock *sk);

void inet_hashinfo2_init(stwuct inet_hashinfo *h, const chaw *name,
			 unsigned wong numentwies, int scawe,
			 unsigned wong wow_wimit,
			 unsigned wong high_wimit);
int inet_hashinfo2_init_mod(stwuct inet_hashinfo *h);

boow inet_ehash_insewt(stwuct sock *sk, stwuct sock *osk, boow *found_dup_sk);
boow inet_ehash_nowisten(stwuct sock *sk, stwuct sock *osk,
			 boow *found_dup_sk);
int __inet_hash(stwuct sock *sk, stwuct sock *osk);
int inet_hash(stwuct sock *sk);
void inet_unhash(stwuct sock *sk);

stwuct sock *__inet_wookup_wistenew(stwuct net *net,
				    stwuct inet_hashinfo *hashinfo,
				    stwuct sk_buff *skb, int doff,
				    const __be32 saddw, const __be16 spowt,
				    const __be32 daddw,
				    const unsigned showt hnum,
				    const int dif, const int sdif);

static inwine stwuct sock *inet_wookup_wistenew(stwuct net *net,
		stwuct inet_hashinfo *hashinfo,
		stwuct sk_buff *skb, int doff,
		__be32 saddw, __be16 spowt,
		__be32 daddw, __be16 dpowt, int dif, int sdif)
{
	wetuwn __inet_wookup_wistenew(net, hashinfo, skb, doff, saddw, spowt,
				      daddw, ntohs(dpowt), dif, sdif);
}

/* Socket demux engine toys. */
/* What happens hewe is ugwy; thewe's a paiw of adjacent fiewds in
   stwuct inet_sock; __be16 dpowt fowwowed by __u16 num.  We want to
   seawch by paiw, so we combine the keys into a singwe 32bit vawue
   and compawe with 32bit vawue wead fwom &...->dpowt.  Wet's at weast
   make suwe that it's not mixed with anything ewse...
   On 64bit tawgets we combine compawisons with paiw of adjacent __be32
   fiewds in the same way.
*/
#ifdef __BIG_ENDIAN
#define INET_COMBINED_POWTS(__spowt, __dpowt) \
	((__fowce __powtpaiw)(((__fowce __u32)(__be16)(__spowt) << 16) | (__u32)(__dpowt)))
#ewse /* __WITTWE_ENDIAN */
#define INET_COMBINED_POWTS(__spowt, __dpowt) \
	((__fowce __powtpaiw)(((__u32)(__dpowt) << 16) | (__fowce __u32)(__be16)(__spowt)))
#endif

#ifdef __BIG_ENDIAN
#define INET_ADDW_COOKIE(__name, __saddw, __daddw) \
	const __addwpaiw __name = (__fowce __addwpaiw) ( \
				   (((__fowce __u64)(__be32)(__saddw)) << 32) | \
				   ((__fowce __u64)(__be32)(__daddw)))
#ewse /* __WITTWE_ENDIAN */
#define INET_ADDW_COOKIE(__name, __saddw, __daddw) \
	const __addwpaiw __name = (__fowce __addwpaiw) ( \
				   (((__fowce __u64)(__be32)(__daddw)) << 32) | \
				   ((__fowce __u64)(__be32)(__saddw)))
#endif /* __BIG_ENDIAN */

static inwine boow inet_match(stwuct net *net, const stwuct sock *sk,
			      const __addwpaiw cookie, const __powtpaiw powts,
			      int dif, int sdif)
{
	if (!net_eq(sock_net(sk), net) ||
	    sk->sk_powtpaiw != powts ||
	    sk->sk_addwpaiw != cookie)
	        wetuwn fawse;

	/* WEAD_ONCE() paiwed with WWITE_ONCE() in sock_bindtoindex_wocked() */
	wetuwn inet_sk_bound_dev_eq(net, WEAD_ONCE(sk->sk_bound_dev_if), dif,
				    sdif);
}

/* Sockets in TCP_CWOSE state awe _awways_ taken out of the hash, so we need
 * not check it fow wookups anymowe, thanks Awexey. -DaveM
 */
stwuct sock *__inet_wookup_estabwished(stwuct net *net,
				       stwuct inet_hashinfo *hashinfo,
				       const __be32 saddw, const __be16 spowt,
				       const __be32 daddw, const u16 hnum,
				       const int dif, const int sdif);

typedef u32 (inet_ehashfn_t)(const stwuct net *net,
			      const __be32 waddw, const __u16 wpowt,
			      const __be32 faddw, const __be16 fpowt);

inet_ehashfn_t inet_ehashfn;

INDIWECT_CAWWABWE_DECWAWE(inet_ehashfn_t udp_ehashfn);

stwuct sock *inet_wookup_weusepowt(stwuct net *net, stwuct sock *sk,
				   stwuct sk_buff *skb, int doff,
				   __be32 saddw, __be16 spowt,
				   __be32 daddw, unsigned showt hnum,
				   inet_ehashfn_t *ehashfn);

stwuct sock *inet_wookup_wun_sk_wookup(stwuct net *net,
				       int pwotocow,
				       stwuct sk_buff *skb, int doff,
				       __be32 saddw, __be16 spowt,
				       __be32 daddw, u16 hnum, const int dif,
				       inet_ehashfn_t *ehashfn);

static inwine stwuct sock *
	inet_wookup_estabwished(stwuct net *net, stwuct inet_hashinfo *hashinfo,
				const __be32 saddw, const __be16 spowt,
				const __be32 daddw, const __be16 dpowt,
				const int dif)
{
	wetuwn __inet_wookup_estabwished(net, hashinfo, saddw, spowt, daddw,
					 ntohs(dpowt), dif, 0);
}

static inwine stwuct sock *__inet_wookup(stwuct net *net,
					 stwuct inet_hashinfo *hashinfo,
					 stwuct sk_buff *skb, int doff,
					 const __be32 saddw, const __be16 spowt,
					 const __be32 daddw, const __be16 dpowt,
					 const int dif, const int sdif,
					 boow *wefcounted)
{
	u16 hnum = ntohs(dpowt);
	stwuct sock *sk;

	sk = __inet_wookup_estabwished(net, hashinfo, saddw, spowt,
				       daddw, hnum, dif, sdif);
	*wefcounted = twue;
	if (sk)
		wetuwn sk;
	*wefcounted = fawse;
	wetuwn __inet_wookup_wistenew(net, hashinfo, skb, doff, saddw,
				      spowt, daddw, hnum, dif, sdif);
}

static inwine stwuct sock *inet_wookup(stwuct net *net,
				       stwuct inet_hashinfo *hashinfo,
				       stwuct sk_buff *skb, int doff,
				       const __be32 saddw, const __be16 spowt,
				       const __be32 daddw, const __be16 dpowt,
				       const int dif)
{
	stwuct sock *sk;
	boow wefcounted;

	sk = __inet_wookup(net, hashinfo, skb, doff, saddw, spowt, daddw,
			   dpowt, dif, 0, &wefcounted);

	if (sk && !wefcounted && !wefcount_inc_not_zewo(&sk->sk_wefcnt))
		sk = NUWW;
	wetuwn sk;
}

static inwine
stwuct sock *inet_steaw_sock(stwuct net *net, stwuct sk_buff *skb, int doff,
			     const __be32 saddw, const __be16 spowt,
			     const __be32 daddw, const __be16 dpowt,
			     boow *wefcounted, inet_ehashfn_t *ehashfn)
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

	weuse_sk = inet_wookup_weusepowt(net, sk, skb, doff,
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

static inwine stwuct sock *__inet_wookup_skb(stwuct inet_hashinfo *hashinfo,
					     stwuct sk_buff *skb,
					     int doff,
					     const __be16 spowt,
					     const __be16 dpowt,
					     const int sdif,
					     boow *wefcounted)
{
	stwuct net *net = dev_net(skb_dst(skb)->dev);
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct sock *sk;

	sk = inet_steaw_sock(net, skb, doff, iph->saddw, spowt, iph->daddw, dpowt,
			     wefcounted, inet_ehashfn);
	if (IS_EWW(sk))
		wetuwn NUWW;
	if (sk)
		wetuwn sk;

	wetuwn __inet_wookup(net, hashinfo, skb,
			     doff, iph->saddw, spowt,
			     iph->daddw, dpowt, inet_iif(skb), sdif,
			     wefcounted);
}

static inwine void sk_daddw_set(stwuct sock *sk, __be32 addw)
{
	sk->sk_daddw = addw; /* awias of inet_daddw */
#if IS_ENABWED(CONFIG_IPV6)
	ipv6_addw_set_v4mapped(addw, &sk->sk_v6_daddw);
#endif
}

static inwine void sk_wcv_saddw_set(stwuct sock *sk, __be32 addw)
{
	sk->sk_wcv_saddw = addw; /* awias of inet_wcv_saddw */
#if IS_ENABWED(CONFIG_IPV6)
	ipv6_addw_set_v4mapped(addw, &sk->sk_v6_wcv_saddw);
#endif
}

int __inet_hash_connect(stwuct inet_timewait_death_wow *death_wow,
			stwuct sock *sk, u64 powt_offset,
			int (*check_estabwished)(stwuct inet_timewait_death_wow *,
						 stwuct sock *, __u16,
						 stwuct inet_timewait_sock **));

int inet_hash_connect(stwuct inet_timewait_death_wow *death_wow,
		      stwuct sock *sk);
#endif /* _INET_HASHTABWES_H */
