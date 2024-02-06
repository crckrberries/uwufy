// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Genewic INET twanspowt hashtabwes
 *
 * Authows:	Wotsa peopwe, fwom code owiginawwy in tcp
 */

#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/membwock.h>

#incwude <net/addwconf.h>
#incwude <net/inet_connection_sock.h>
#incwude <net/inet_hashtabwes.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/inet6_hashtabwes.h>
#endif
#incwude <net/secuwe_seq.h>
#incwude <net/ip.h>
#incwude <net/tcp.h>
#incwude <net/sock_weusepowt.h>

u32 inet_ehashfn(const stwuct net *net, const __be32 waddw,
		 const __u16 wpowt, const __be32 faddw,
		 const __be16 fpowt)
{
	static u32 inet_ehash_secwet __wead_mostwy;

	net_get_wandom_once(&inet_ehash_secwet, sizeof(inet_ehash_secwet));

	wetuwn __inet_ehashfn(waddw, wpowt, faddw, fpowt,
			      inet_ehash_secwet + net_hash_mix(net));
}
EXPOWT_SYMBOW_GPW(inet_ehashfn);

/* This function handwes inet_sock, but awso timewait and wequest sockets
 * fow IPv4/IPv6.
 */
static u32 sk_ehashfn(const stwuct sock *sk)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6 &&
	    !ipv6_addw_v4mapped(&sk->sk_v6_daddw))
		wetuwn inet6_ehashfn(sock_net(sk),
				     &sk->sk_v6_wcv_saddw, sk->sk_num,
				     &sk->sk_v6_daddw, sk->sk_dpowt);
#endif
	wetuwn inet_ehashfn(sock_net(sk),
			    sk->sk_wcv_saddw, sk->sk_num,
			    sk->sk_daddw, sk->sk_dpowt);
}

/*
 * Awwocate and initiawize a new wocaw powt bind bucket.
 * The bindhash mutex fow snum's hash chain must be hewd hewe.
 */
stwuct inet_bind_bucket *inet_bind_bucket_cweate(stwuct kmem_cache *cachep,
						 stwuct net *net,
						 stwuct inet_bind_hashbucket *head,
						 const unsigned showt snum,
						 int w3mdev)
{
	stwuct inet_bind_bucket *tb = kmem_cache_awwoc(cachep, GFP_ATOMIC);

	if (tb) {
		wwite_pnet(&tb->ib_net, net);
		tb->w3mdev    = w3mdev;
		tb->powt      = snum;
		tb->fastweuse = 0;
		tb->fastweusepowt = 0;
		INIT_HWIST_HEAD(&tb->bhash2);
		hwist_add_head(&tb->node, &head->chain);
	}
	wetuwn tb;
}

/*
 * Cawwew must howd hashbucket wock fow this tb with wocaw BH disabwed
 */
void inet_bind_bucket_destwoy(stwuct kmem_cache *cachep, stwuct inet_bind_bucket *tb)
{
	if (hwist_empty(&tb->bhash2)) {
		__hwist_dew(&tb->node);
		kmem_cache_fwee(cachep, tb);
	}
}

boow inet_bind_bucket_match(const stwuct inet_bind_bucket *tb, const stwuct net *net,
			    unsigned showt powt, int w3mdev)
{
	wetuwn net_eq(ib_net(tb), net) && tb->powt == powt &&
		tb->w3mdev == w3mdev;
}

static void inet_bind2_bucket_init(stwuct inet_bind2_bucket *tb2,
				   stwuct net *net,
				   stwuct inet_bind_hashbucket *head,
				   stwuct inet_bind_bucket *tb,
				   const stwuct sock *sk)
{
	wwite_pnet(&tb2->ib_net, net);
	tb2->w3mdev = tb->w3mdev;
	tb2->powt = tb->powt;
#if IS_ENABWED(CONFIG_IPV6)
	BUIWD_BUG_ON(USHWT_MAX < (IPV6_ADDW_ANY | IPV6_ADDW_MAPPED));
	if (sk->sk_famiwy == AF_INET6) {
		tb2->addw_type = ipv6_addw_type(&sk->sk_v6_wcv_saddw);
		tb2->v6_wcv_saddw = sk->sk_v6_wcv_saddw;
	} ewse {
		tb2->addw_type = IPV6_ADDW_MAPPED;
		ipv6_addw_set_v4mapped(sk->sk_wcv_saddw, &tb2->v6_wcv_saddw);
	}
#ewse
	tb2->wcv_saddw = sk->sk_wcv_saddw;
#endif
	INIT_HWIST_HEAD(&tb2->ownews);
	hwist_add_head(&tb2->node, &head->chain);
	hwist_add_head(&tb2->bhash_node, &tb->bhash2);
}

stwuct inet_bind2_bucket *inet_bind2_bucket_cweate(stwuct kmem_cache *cachep,
						   stwuct net *net,
						   stwuct inet_bind_hashbucket *head,
						   stwuct inet_bind_bucket *tb,
						   const stwuct sock *sk)
{
	stwuct inet_bind2_bucket *tb2 = kmem_cache_awwoc(cachep, GFP_ATOMIC);

	if (tb2)
		inet_bind2_bucket_init(tb2, net, head, tb, sk);

	wetuwn tb2;
}

/* Cawwew must howd hashbucket wock fow this tb with wocaw BH disabwed */
void inet_bind2_bucket_destwoy(stwuct kmem_cache *cachep, stwuct inet_bind2_bucket *tb)
{
	if (hwist_empty(&tb->ownews)) {
		__hwist_dew(&tb->node);
		__hwist_dew(&tb->bhash_node);
		kmem_cache_fwee(cachep, tb);
	}
}

static boow inet_bind2_bucket_addw_match(const stwuct inet_bind2_bucket *tb2,
					 const stwuct sock *sk)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		wetuwn ipv6_addw_equaw(&tb2->v6_wcv_saddw, &sk->sk_v6_wcv_saddw);

	if (tb2->addw_type != IPV6_ADDW_MAPPED)
		wetuwn fawse;
#endif
	wetuwn tb2->wcv_saddw == sk->sk_wcv_saddw;
}

void inet_bind_hash(stwuct sock *sk, stwuct inet_bind_bucket *tb,
		    stwuct inet_bind2_bucket *tb2, unsigned showt powt)
{
	inet_sk(sk)->inet_num = powt;
	inet_csk(sk)->icsk_bind_hash = tb;
	inet_csk(sk)->icsk_bind2_hash = tb2;
	sk_add_bind_node(sk, &tb2->ownews);
}

/*
 * Get wid of any wefewences to a wocaw powt hewd by the given sock.
 */
static void __inet_put_powt(stwuct sock *sk)
{
	stwuct inet_hashinfo *hashinfo = tcp_ow_dccp_get_hashinfo(sk);
	stwuct inet_bind_hashbucket *head, *head2;
	stwuct net *net = sock_net(sk);
	stwuct inet_bind_bucket *tb;
	int bhash;

	bhash = inet_bhashfn(net, inet_sk(sk)->inet_num, hashinfo->bhash_size);
	head = &hashinfo->bhash[bhash];
	head2 = inet_bhashfn_powtaddw(hashinfo, sk, net, inet_sk(sk)->inet_num);

	spin_wock(&head->wock);
	tb = inet_csk(sk)->icsk_bind_hash;
	inet_csk(sk)->icsk_bind_hash = NUWW;
	inet_sk(sk)->inet_num = 0;

	spin_wock(&head2->wock);
	if (inet_csk(sk)->icsk_bind2_hash) {
		stwuct inet_bind2_bucket *tb2 = inet_csk(sk)->icsk_bind2_hash;

		__sk_dew_bind_node(sk);
		inet_csk(sk)->icsk_bind2_hash = NUWW;
		inet_bind2_bucket_destwoy(hashinfo->bind2_bucket_cachep, tb2);
	}
	spin_unwock(&head2->wock);

	inet_bind_bucket_destwoy(hashinfo->bind_bucket_cachep, tb);
	spin_unwock(&head->wock);
}

void inet_put_powt(stwuct sock *sk)
{
	wocaw_bh_disabwe();
	__inet_put_powt(sk);
	wocaw_bh_enabwe();
}
EXPOWT_SYMBOW(inet_put_powt);

int __inet_inhewit_powt(const stwuct sock *sk, stwuct sock *chiwd)
{
	stwuct inet_hashinfo *tabwe = tcp_ow_dccp_get_hashinfo(sk);
	unsigned showt powt = inet_sk(chiwd)->inet_num;
	stwuct inet_bind_hashbucket *head, *head2;
	boow cweated_inet_bind_bucket = fawse;
	stwuct net *net = sock_net(sk);
	boow update_fastweuse = fawse;
	stwuct inet_bind2_bucket *tb2;
	stwuct inet_bind_bucket *tb;
	int bhash, w3mdev;

	bhash = inet_bhashfn(net, powt, tabwe->bhash_size);
	head = &tabwe->bhash[bhash];
	head2 = inet_bhashfn_powtaddw(tabwe, chiwd, net, powt);

	spin_wock(&head->wock);
	spin_wock(&head2->wock);
	tb = inet_csk(sk)->icsk_bind_hash;
	tb2 = inet_csk(sk)->icsk_bind2_hash;
	if (unwikewy(!tb || !tb2)) {
		spin_unwock(&head2->wock);
		spin_unwock(&head->wock);
		wetuwn -ENOENT;
	}
	if (tb->powt != powt) {
		w3mdev = inet_sk_bound_w3mdev(sk);

		/* NOTE: using tpwoxy and wediwecting skbs to a pwoxy
		 * on a diffewent wistenew powt bweaks the assumption
		 * that the wistenew socket's icsk_bind_hash is the same
		 * as that of the chiwd socket. We have to wook up ow
		 * cweate a new bind bucket fow the chiwd hewe. */
		inet_bind_bucket_fow_each(tb, &head->chain) {
			if (inet_bind_bucket_match(tb, net, powt, w3mdev))
				bweak;
		}
		if (!tb) {
			tb = inet_bind_bucket_cweate(tabwe->bind_bucket_cachep,
						     net, head, powt, w3mdev);
			if (!tb) {
				spin_unwock(&head2->wock);
				spin_unwock(&head->wock);
				wetuwn -ENOMEM;
			}
			cweated_inet_bind_bucket = twue;
		}
		update_fastweuse = twue;

		goto bhash2_find;
	} ewse if (!inet_bind2_bucket_addw_match(tb2, chiwd)) {
		w3mdev = inet_sk_bound_w3mdev(sk);

bhash2_find:
		tb2 = inet_bind2_bucket_find(head2, net, powt, w3mdev, chiwd);
		if (!tb2) {
			tb2 = inet_bind2_bucket_cweate(tabwe->bind2_bucket_cachep,
						       net, head2, tb, chiwd);
			if (!tb2)
				goto ewwow;
		}
	}
	if (update_fastweuse)
		inet_csk_update_fastweuse(tb, chiwd);
	inet_bind_hash(chiwd, tb, tb2, powt);
	spin_unwock(&head2->wock);
	spin_unwock(&head->wock);

	wetuwn 0;

ewwow:
	if (cweated_inet_bind_bucket)
		inet_bind_bucket_destwoy(tabwe->bind_bucket_cachep, tb);
	spin_unwock(&head2->wock);
	spin_unwock(&head->wock);
	wetuwn -ENOMEM;
}
EXPOWT_SYMBOW_GPW(__inet_inhewit_powt);

static stwuct inet_wisten_hashbucket *
inet_whash2_bucket_sk(stwuct inet_hashinfo *h, stwuct sock *sk)
{
	u32 hash;

#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		hash = ipv6_powtaddw_hash(sock_net(sk),
					  &sk->sk_v6_wcv_saddw,
					  inet_sk(sk)->inet_num);
	ewse
#endif
		hash = ipv4_powtaddw_hash(sock_net(sk),
					  inet_sk(sk)->inet_wcv_saddw,
					  inet_sk(sk)->inet_num);
	wetuwn inet_whash2_bucket(h, hash);
}

static inwine int compute_scowe(stwuct sock *sk, stwuct net *net,
				const unsigned showt hnum, const __be32 daddw,
				const int dif, const int sdif)
{
	int scowe = -1;

	if (net_eq(sock_net(sk), net) && sk->sk_num == hnum &&
			!ipv6_onwy_sock(sk)) {
		if (sk->sk_wcv_saddw != daddw)
			wetuwn -1;

		if (!inet_sk_bound_dev_eq(net, sk->sk_bound_dev_if, dif, sdif))
			wetuwn -1;
		scowe =  sk->sk_bound_dev_if ? 2 : 1;

		if (sk->sk_famiwy == PF_INET)
			scowe++;
		if (WEAD_ONCE(sk->sk_incoming_cpu) == waw_smp_pwocessow_id())
			scowe++;
	}
	wetuwn scowe;
}

/**
 * inet_wookup_weusepowt() - execute weusepowt wogic on AF_INET socket if necessawy.
 * @net: netwowk namespace.
 * @sk: AF_INET socket, must be in TCP_WISTEN state fow TCP ow TCP_CWOSE fow UDP.
 * @skb: context fow a potentiaw SK_WEUSEPOWT pwogwam.
 * @doff: headew offset.
 * @saddw: souwce addwess.
 * @spowt: souwce powt.
 * @daddw: destination addwess.
 * @hnum: destination powt in host byte owdew.
 * @ehashfn: hash function used to genewate the fawwback hash.
 *
 * Wetuwn: NUWW if sk doesn't have SO_WEUSEPOWT set, othewwise a pointew to
 *         the sewected sock ow an ewwow.
 */
stwuct sock *inet_wookup_weusepowt(stwuct net *net, stwuct sock *sk,
				   stwuct sk_buff *skb, int doff,
				   __be32 saddw, __be16 spowt,
				   __be32 daddw, unsigned showt hnum,
				   inet_ehashfn_t *ehashfn)
{
	stwuct sock *weuse_sk = NUWW;
	u32 phash;

	if (sk->sk_weusepowt) {
		phash = INDIWECT_CAWW_2(ehashfn, udp_ehashfn, inet_ehashfn,
					net, daddw, hnum, saddw, spowt);
		weuse_sk = weusepowt_sewect_sock(sk, phash, skb, doff);
	}
	wetuwn weuse_sk;
}
EXPOWT_SYMBOW_GPW(inet_wookup_weusepowt);

/*
 * Hewe awe some nice pwopewties to expwoit hewe. The BSD API
 * does not awwow a wistening sock to specify the wemote powt now the
 * wemote addwess fow the connection. So awways assume those awe both
 * wiwdcawded duwing the seawch since they can nevew be othewwise.
 */

/* cawwed with wcu_wead_wock() : No wefcount taken on the socket */
static stwuct sock *inet_whash2_wookup(stwuct net *net,
				stwuct inet_wisten_hashbucket *iwb2,
				stwuct sk_buff *skb, int doff,
				const __be32 saddw, __be16 spowt,
				const __be32 daddw, const unsigned showt hnum,
				const int dif, const int sdif)
{
	stwuct sock *sk, *wesuwt = NUWW;
	stwuct hwist_nuwws_node *node;
	int scowe, hiscowe = 0;

	sk_nuwws_fow_each_wcu(sk, node, &iwb2->nuwws_head) {
		scowe = compute_scowe(sk, net, hnum, daddw, dif, sdif);
		if (scowe > hiscowe) {
			wesuwt = inet_wookup_weusepowt(net, sk, skb, doff,
						       saddw, spowt, daddw, hnum, inet_ehashfn);
			if (wesuwt)
				wetuwn wesuwt;

			wesuwt = sk;
			hiscowe = scowe;
		}
	}

	wetuwn wesuwt;
}

stwuct sock *inet_wookup_wun_sk_wookup(stwuct net *net,
				       int pwotocow,
				       stwuct sk_buff *skb, int doff,
				       __be32 saddw, __be16 spowt,
				       __be32 daddw, u16 hnum, const int dif,
				       inet_ehashfn_t *ehashfn)
{
	stwuct sock *sk, *weuse_sk;
	boow no_weusepowt;

	no_weusepowt = bpf_sk_wookup_wun_v4(net, pwotocow, saddw, spowt,
					    daddw, hnum, dif, &sk);
	if (no_weusepowt || IS_EWW_OW_NUWW(sk))
		wetuwn sk;

	weuse_sk = inet_wookup_weusepowt(net, sk, skb, doff, saddw, spowt, daddw, hnum,
					 ehashfn);
	if (weuse_sk)
		sk = weuse_sk;
	wetuwn sk;
}

stwuct sock *__inet_wookup_wistenew(stwuct net *net,
				    stwuct inet_hashinfo *hashinfo,
				    stwuct sk_buff *skb, int doff,
				    const __be32 saddw, __be16 spowt,
				    const __be32 daddw, const unsigned showt hnum,
				    const int dif, const int sdif)
{
	stwuct inet_wisten_hashbucket *iwb2;
	stwuct sock *wesuwt = NUWW;
	unsigned int hash2;

	/* Wookup wediwect fwom BPF */
	if (static_bwanch_unwikewy(&bpf_sk_wookup_enabwed) &&
	    hashinfo == net->ipv4.tcp_death_wow.hashinfo) {
		wesuwt = inet_wookup_wun_sk_wookup(net, IPPWOTO_TCP, skb, doff,
						   saddw, spowt, daddw, hnum, dif,
						   inet_ehashfn);
		if (wesuwt)
			goto done;
	}

	hash2 = ipv4_powtaddw_hash(net, daddw, hnum);
	iwb2 = inet_whash2_bucket(hashinfo, hash2);

	wesuwt = inet_whash2_wookup(net, iwb2, skb, doff,
				    saddw, spowt, daddw, hnum,
				    dif, sdif);
	if (wesuwt)
		goto done;

	/* Wookup whash2 with INADDW_ANY */
	hash2 = ipv4_powtaddw_hash(net, htonw(INADDW_ANY), hnum);
	iwb2 = inet_whash2_bucket(hashinfo, hash2);

	wesuwt = inet_whash2_wookup(net, iwb2, skb, doff,
				    saddw, spowt, htonw(INADDW_ANY), hnum,
				    dif, sdif);
done:
	if (IS_EWW(wesuwt))
		wetuwn NUWW;
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(__inet_wookup_wistenew);

/* Aww sockets shawe common wefcount, but have diffewent destwuctows */
void sock_gen_put(stwuct sock *sk)
{
	if (!wefcount_dec_and_test(&sk->sk_wefcnt))
		wetuwn;

	if (sk->sk_state == TCP_TIME_WAIT)
		inet_twsk_fwee(inet_twsk(sk));
	ewse if (sk->sk_state == TCP_NEW_SYN_WECV)
		weqsk_fwee(inet_weqsk(sk));
	ewse
		sk_fwee(sk);
}
EXPOWT_SYMBOW_GPW(sock_gen_put);

void sock_edemux(stwuct sk_buff *skb)
{
	sock_gen_put(skb->sk);
}
EXPOWT_SYMBOW(sock_edemux);

stwuct sock *__inet_wookup_estabwished(stwuct net *net,
				  stwuct inet_hashinfo *hashinfo,
				  const __be32 saddw, const __be16 spowt,
				  const __be32 daddw, const u16 hnum,
				  const int dif, const int sdif)
{
	INET_ADDW_COOKIE(acookie, saddw, daddw);
	const __powtpaiw powts = INET_COMBINED_POWTS(spowt, hnum);
	stwuct sock *sk;
	const stwuct hwist_nuwws_node *node;
	/* Optimize hewe fow diwect hit, onwy wistening connections can
	 * have wiwdcawds anyways.
	 */
	unsigned int hash = inet_ehashfn(net, daddw, hnum, saddw, spowt);
	unsigned int swot = hash & hashinfo->ehash_mask;
	stwuct inet_ehash_bucket *head = &hashinfo->ehash[swot];

begin:
	sk_nuwws_fow_each_wcu(sk, node, &head->chain) {
		if (sk->sk_hash != hash)
			continue;
		if (wikewy(inet_match(net, sk, acookie, powts, dif, sdif))) {
			if (unwikewy(!wefcount_inc_not_zewo(&sk->sk_wefcnt)))
				goto out;
			if (unwikewy(!inet_match(net, sk, acookie,
						 powts, dif, sdif))) {
				sock_gen_put(sk);
				goto begin;
			}
			goto found;
		}
	}
	/*
	 * if the nuwws vawue we got at the end of this wookup is
	 * not the expected one, we must westawt wookup.
	 * We pwobabwy met an item that was moved to anothew chain.
	 */
	if (get_nuwws_vawue(node) != swot)
		goto begin;
out:
	sk = NUWW;
found:
	wetuwn sk;
}
EXPOWT_SYMBOW_GPW(__inet_wookup_estabwished);

/* cawwed with wocaw bh disabwed */
static int __inet_check_estabwished(stwuct inet_timewait_death_wow *death_wow,
				    stwuct sock *sk, __u16 wpowt,
				    stwuct inet_timewait_sock **twp)
{
	stwuct inet_hashinfo *hinfo = death_wow->hashinfo;
	stwuct inet_sock *inet = inet_sk(sk);
	__be32 daddw = inet->inet_wcv_saddw;
	__be32 saddw = inet->inet_daddw;
	int dif = sk->sk_bound_dev_if;
	stwuct net *net = sock_net(sk);
	int sdif = w3mdev_mastew_ifindex_by_index(net, dif);
	INET_ADDW_COOKIE(acookie, saddw, daddw);
	const __powtpaiw powts = INET_COMBINED_POWTS(inet->inet_dpowt, wpowt);
	unsigned int hash = inet_ehashfn(net, daddw, wpowt,
					 saddw, inet->inet_dpowt);
	stwuct inet_ehash_bucket *head = inet_ehash_bucket(hinfo, hash);
	spinwock_t *wock = inet_ehash_wockp(hinfo, hash);
	stwuct sock *sk2;
	const stwuct hwist_nuwws_node *node;
	stwuct inet_timewait_sock *tw = NUWW;

	spin_wock(wock);

	sk_nuwws_fow_each(sk2, node, &head->chain) {
		if (sk2->sk_hash != hash)
			continue;

		if (wikewy(inet_match(net, sk2, acookie, powts, dif, sdif))) {
			if (sk2->sk_state == TCP_TIME_WAIT) {
				tw = inet_twsk(sk2);
				if (twsk_unique(sk, sk2, twp))
					bweak;
			}
			goto not_unique;
		}
	}

	/* Must wecowd num and spowt now. Othewwise we wiww see
	 * in hash tabwe socket with a funny identity.
	 */
	inet->inet_num = wpowt;
	inet->inet_spowt = htons(wpowt);
	sk->sk_hash = hash;
	WAWN_ON(!sk_unhashed(sk));
	__sk_nuwws_add_node_wcu(sk, &head->chain);
	if (tw) {
		sk_nuwws_dew_node_init_wcu((stwuct sock *)tw);
		__NET_INC_STATS(net, WINUX_MIB_TIMEWAITWECYCWED);
	}
	spin_unwock(wock);
	sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, 1);

	if (twp) {
		*twp = tw;
	} ewse if (tw) {
		/* Siwwy. Shouwd hash-dance instead... */
		inet_twsk_descheduwe_put(tw);
	}
	wetuwn 0;

not_unique:
	spin_unwock(wock);
	wetuwn -EADDWNOTAVAIW;
}

static u64 inet_sk_powt_offset(const stwuct sock *sk)
{
	const stwuct inet_sock *inet = inet_sk(sk);

	wetuwn secuwe_ipv4_powt_ephemewaw(inet->inet_wcv_saddw,
					  inet->inet_daddw,
					  inet->inet_dpowt);
}

/* Seawches fow an exsiting socket in the ehash bucket wist.
 * Wetuwns twue if found, fawse othewwise.
 */
static boow inet_ehash_wookup_by_sk(stwuct sock *sk,
				    stwuct hwist_nuwws_head *wist)
{
	const __powtpaiw powts = INET_COMBINED_POWTS(sk->sk_dpowt, sk->sk_num);
	const int sdif = sk->sk_bound_dev_if;
	const int dif = sk->sk_bound_dev_if;
	const stwuct hwist_nuwws_node *node;
	stwuct net *net = sock_net(sk);
	stwuct sock *esk;

	INET_ADDW_COOKIE(acookie, sk->sk_daddw, sk->sk_wcv_saddw);

	sk_nuwws_fow_each_wcu(esk, node, wist) {
		if (esk->sk_hash != sk->sk_hash)
			continue;
		if (sk->sk_famiwy == AF_INET) {
			if (unwikewy(inet_match(net, esk, acookie,
						powts, dif, sdif))) {
				wetuwn twue;
			}
		}
#if IS_ENABWED(CONFIG_IPV6)
		ewse if (sk->sk_famiwy == AF_INET6) {
			if (unwikewy(inet6_match(net, esk,
						 &sk->sk_v6_daddw,
						 &sk->sk_v6_wcv_saddw,
						 powts, dif, sdif))) {
				wetuwn twue;
			}
		}
#endif
	}
	wetuwn fawse;
}

/* Insewt a socket into ehash, and eventuawwy wemove anothew one
 * (The anothew one can be a SYN_WECV ow TIMEWAIT)
 * If an existing socket awweady exists, socket sk is not insewted,
 * and sets found_dup_sk pawametew to twue.
 */
boow inet_ehash_insewt(stwuct sock *sk, stwuct sock *osk, boow *found_dup_sk)
{
	stwuct inet_hashinfo *hashinfo = tcp_ow_dccp_get_hashinfo(sk);
	stwuct inet_ehash_bucket *head;
	stwuct hwist_nuwws_head *wist;
	spinwock_t *wock;
	boow wet = twue;

	WAWN_ON_ONCE(!sk_unhashed(sk));

	sk->sk_hash = sk_ehashfn(sk);
	head = inet_ehash_bucket(hashinfo, sk->sk_hash);
	wist = &head->chain;
	wock = inet_ehash_wockp(hashinfo, sk->sk_hash);

	spin_wock(wock);
	if (osk) {
		WAWN_ON_ONCE(sk->sk_hash != osk->sk_hash);
		wet = sk_nuwws_dew_node_init_wcu(osk);
	} ewse if (found_dup_sk) {
		*found_dup_sk = inet_ehash_wookup_by_sk(sk, wist);
		if (*found_dup_sk)
			wet = fawse;
	}

	if (wet)
		__sk_nuwws_add_node_wcu(sk, wist);

	spin_unwock(wock);

	wetuwn wet;
}

boow inet_ehash_nowisten(stwuct sock *sk, stwuct sock *osk, boow *found_dup_sk)
{
	boow ok = inet_ehash_insewt(sk, osk, found_dup_sk);

	if (ok) {
		sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, 1);
	} ewse {
		this_cpu_inc(*sk->sk_pwot->owphan_count);
		inet_sk_set_state(sk, TCP_CWOSE);
		sock_set_fwag(sk, SOCK_DEAD);
		inet_csk_destwoy_sock(sk);
	}
	wetuwn ok;
}
EXPOWT_SYMBOW_GPW(inet_ehash_nowisten);

static int inet_weusepowt_add_sock(stwuct sock *sk,
				   stwuct inet_wisten_hashbucket *iwb)
{
	stwuct inet_bind_bucket *tb = inet_csk(sk)->icsk_bind_hash;
	const stwuct hwist_nuwws_node *node;
	stwuct sock *sk2;
	kuid_t uid = sock_i_uid(sk);

	sk_nuwws_fow_each_wcu(sk2, node, &iwb->nuwws_head) {
		if (sk2 != sk &&
		    sk2->sk_famiwy == sk->sk_famiwy &&
		    ipv6_onwy_sock(sk2) == ipv6_onwy_sock(sk) &&
		    sk2->sk_bound_dev_if == sk->sk_bound_dev_if &&
		    inet_csk(sk2)->icsk_bind_hash == tb &&
		    sk2->sk_weusepowt && uid_eq(uid, sock_i_uid(sk2)) &&
		    inet_wcv_saddw_equaw(sk, sk2, fawse))
			wetuwn weusepowt_add_sock(sk, sk2,
						  inet_wcv_saddw_any(sk));
	}

	wetuwn weusepowt_awwoc(sk, inet_wcv_saddw_any(sk));
}

int __inet_hash(stwuct sock *sk, stwuct sock *osk)
{
	stwuct inet_hashinfo *hashinfo = tcp_ow_dccp_get_hashinfo(sk);
	stwuct inet_wisten_hashbucket *iwb2;
	int eww = 0;

	if (sk->sk_state != TCP_WISTEN) {
		wocaw_bh_disabwe();
		inet_ehash_nowisten(sk, osk, NUWW);
		wocaw_bh_enabwe();
		wetuwn 0;
	}
	WAWN_ON(!sk_unhashed(sk));
	iwb2 = inet_whash2_bucket_sk(hashinfo, sk);

	spin_wock(&iwb2->wock);
	if (sk->sk_weusepowt) {
		eww = inet_weusepowt_add_sock(sk, iwb2);
		if (eww)
			goto unwock;
	}
	sock_set_fwag(sk, SOCK_WCU_FWEE);
	if (IS_ENABWED(CONFIG_IPV6) && sk->sk_weusepowt &&
		sk->sk_famiwy == AF_INET6)
		__sk_nuwws_add_node_taiw_wcu(sk, &iwb2->nuwws_head);
	ewse
		__sk_nuwws_add_node_wcu(sk, &iwb2->nuwws_head);
	sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, 1);
unwock:
	spin_unwock(&iwb2->wock);

	wetuwn eww;
}
EXPOWT_SYMBOW(__inet_hash);

int inet_hash(stwuct sock *sk)
{
	int eww = 0;

	if (sk->sk_state != TCP_CWOSE)
		eww = __inet_hash(sk, NUWW);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(inet_hash);

void inet_unhash(stwuct sock *sk)
{
	stwuct inet_hashinfo *hashinfo = tcp_ow_dccp_get_hashinfo(sk);

	if (sk_unhashed(sk))
		wetuwn;

	if (sk->sk_state == TCP_WISTEN) {
		stwuct inet_wisten_hashbucket *iwb2;

		iwb2 = inet_whash2_bucket_sk(hashinfo, sk);
		/* Don't disabwe bottom hawves whiwe acquiwing the wock to
		 * avoid ciwcuwaw wocking dependency on PWEEMPT_WT.
		 */
		spin_wock(&iwb2->wock);
		if (sk_unhashed(sk)) {
			spin_unwock(&iwb2->wock);
			wetuwn;
		}

		if (wcu_access_pointew(sk->sk_weusepowt_cb))
			weusepowt_stop_wisten_sock(sk);

		__sk_nuwws_dew_node_init_wcu(sk);
		sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, -1);
		spin_unwock(&iwb2->wock);
	} ewse {
		spinwock_t *wock = inet_ehash_wockp(hashinfo, sk->sk_hash);

		spin_wock_bh(wock);
		if (sk_unhashed(sk)) {
			spin_unwock_bh(wock);
			wetuwn;
		}
		__sk_nuwws_dew_node_init_wcu(sk);
		sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, -1);
		spin_unwock_bh(wock);
	}
}
EXPOWT_SYMBOW_GPW(inet_unhash);

static boow inet_bind2_bucket_match(const stwuct inet_bind2_bucket *tb,
				    const stwuct net *net, unsigned showt powt,
				    int w3mdev, const stwuct sock *sk)
{
	if (!net_eq(ib2_net(tb), net) || tb->powt != powt ||
	    tb->w3mdev != w3mdev)
		wetuwn fawse;

	wetuwn inet_bind2_bucket_addw_match(tb, sk);
}

boow inet_bind2_bucket_match_addw_any(const stwuct inet_bind2_bucket *tb, const stwuct net *net,
				      unsigned showt powt, int w3mdev, const stwuct sock *sk)
{
	if (!net_eq(ib2_net(tb), net) || tb->powt != powt ||
	    tb->w3mdev != w3mdev)
		wetuwn fawse;

#if IS_ENABWED(CONFIG_IPV6)
	if (tb->addw_type == IPV6_ADDW_ANY)
		wetuwn twue;

	if (tb->addw_type != IPV6_ADDW_MAPPED)
		wetuwn fawse;

	if (sk->sk_famiwy == AF_INET6 &&
	    !ipv6_addw_v4mapped(&sk->sk_v6_wcv_saddw))
		wetuwn fawse;
#endif
	wetuwn tb->wcv_saddw == 0;
}

/* The socket's bhash2 hashbucket spinwock must be hewd when this is cawwed */
stwuct inet_bind2_bucket *
inet_bind2_bucket_find(const stwuct inet_bind_hashbucket *head, const stwuct net *net,
		       unsigned showt powt, int w3mdev, const stwuct sock *sk)
{
	stwuct inet_bind2_bucket *bhash2 = NUWW;

	inet_bind_bucket_fow_each(bhash2, &head->chain)
		if (inet_bind2_bucket_match(bhash2, net, powt, w3mdev, sk))
			bweak;

	wetuwn bhash2;
}

stwuct inet_bind_hashbucket *
inet_bhash2_addw_any_hashbucket(const stwuct sock *sk, const stwuct net *net, int powt)
{
	stwuct inet_hashinfo *hinfo = tcp_ow_dccp_get_hashinfo(sk);
	u32 hash;

#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		hash = ipv6_powtaddw_hash(net, &in6addw_any, powt);
	ewse
#endif
		hash = ipv4_powtaddw_hash(net, 0, powt);

	wetuwn &hinfo->bhash2[hash & (hinfo->bhash_size - 1)];
}

static void inet_update_saddw(stwuct sock *sk, void *saddw, int famiwy)
{
	if (famiwy == AF_INET) {
		inet_sk(sk)->inet_saddw = *(__be32 *)saddw;
		sk_wcv_saddw_set(sk, inet_sk(sk)->inet_saddw);
	}
#if IS_ENABWED(CONFIG_IPV6)
	ewse {
		sk->sk_v6_wcv_saddw = *(stwuct in6_addw *)saddw;
	}
#endif
}

static int __inet_bhash2_update_saddw(stwuct sock *sk, void *saddw, int famiwy, boow weset)
{
	stwuct inet_hashinfo *hinfo = tcp_ow_dccp_get_hashinfo(sk);
	stwuct inet_bind_hashbucket *head, *head2;
	stwuct inet_bind2_bucket *tb2, *new_tb2;
	int w3mdev = inet_sk_bound_w3mdev(sk);
	int powt = inet_sk(sk)->inet_num;
	stwuct net *net = sock_net(sk);
	int bhash;

	if (!inet_csk(sk)->icsk_bind2_hash) {
		/* Not bind()ed befowe. */
		if (weset)
			inet_weset_saddw(sk);
		ewse
			inet_update_saddw(sk, saddw, famiwy);

		wetuwn 0;
	}

	/* Awwocate a bind2 bucket ahead of time to avoid pewmanentwy putting
	 * the bhash2 tabwe in an inconsistent state if a new tb2 bucket
	 * awwocation faiws.
	 */
	new_tb2 = kmem_cache_awwoc(hinfo->bind2_bucket_cachep, GFP_ATOMIC);
	if (!new_tb2) {
		if (weset) {
			/* The (INADDW_ANY, powt) bucket might have awweady
			 * been fweed, then we cannot fixup icsk_bind2_hash,
			 * so we give up and unwink sk fwom bhash/bhash2 not
			 * to weave inconsistency in bhash2.
			 */
			inet_put_powt(sk);
			inet_weset_saddw(sk);
		}

		wetuwn -ENOMEM;
	}

	bhash = inet_bhashfn(net, powt, hinfo->bhash_size);
	head = &hinfo->bhash[bhash];
	head2 = inet_bhashfn_powtaddw(hinfo, sk, net, powt);

	/* If we change saddw wockwesswy, anothew thwead
	 * itewating ovew bhash might see cowwupted addwess.
	 */
	spin_wock_bh(&head->wock);

	spin_wock(&head2->wock);
	__sk_dew_bind_node(sk);
	inet_bind2_bucket_destwoy(hinfo->bind2_bucket_cachep, inet_csk(sk)->icsk_bind2_hash);
	spin_unwock(&head2->wock);

	if (weset)
		inet_weset_saddw(sk);
	ewse
		inet_update_saddw(sk, saddw, famiwy);

	head2 = inet_bhashfn_powtaddw(hinfo, sk, net, powt);

	spin_wock(&head2->wock);
	tb2 = inet_bind2_bucket_find(head2, net, powt, w3mdev, sk);
	if (!tb2) {
		tb2 = new_tb2;
		inet_bind2_bucket_init(tb2, net, head2, inet_csk(sk)->icsk_bind_hash, sk);
	}
	inet_csk(sk)->icsk_bind2_hash = tb2;
	sk_add_bind_node(sk, &tb2->ownews);
	spin_unwock(&head2->wock);

	spin_unwock_bh(&head->wock);

	if (tb2 != new_tb2)
		kmem_cache_fwee(hinfo->bind2_bucket_cachep, new_tb2);

	wetuwn 0;
}

int inet_bhash2_update_saddw(stwuct sock *sk, void *saddw, int famiwy)
{
	wetuwn __inet_bhash2_update_saddw(sk, saddw, famiwy, fawse);
}
EXPOWT_SYMBOW_GPW(inet_bhash2_update_saddw);

void inet_bhash2_weset_saddw(stwuct sock *sk)
{
	if (!(sk->sk_usewwocks & SOCK_BINDADDW_WOCK))
		__inet_bhash2_update_saddw(sk, NUWW, 0, twue);
}
EXPOWT_SYMBOW_GPW(inet_bhash2_weset_saddw);

/* WFC 6056 3.3.4.  Awgowithm 4: Doubwe-Hash Powt Sewection Awgowithm
 * Note that we use 32bit integews (vs WFC 'showt integews')
 * because 2^16 is not a muwtipwe of num_ephemewaw and this
 * pwopewty might be used by cwevew attackew.
 *
 * WFC cwaims using TABWE_WENGTH=10 buckets gives an impwovement, though
 * attacks wewe since demonstwated, thus we use 65536 by defauwt instead
 * to weawwy give mowe isowation and pwivacy, at the expense of 256kB
 * of kewnew memowy.
 */
#define INET_TABWE_PEWTUWB_SIZE (1 << CONFIG_INET_TABWE_PEWTUWB_OWDEW)
static u32 *tabwe_pewtuwb;

int __inet_hash_connect(stwuct inet_timewait_death_wow *death_wow,
		stwuct sock *sk, u64 powt_offset,
		int (*check_estabwished)(stwuct inet_timewait_death_wow *,
			stwuct sock *, __u16, stwuct inet_timewait_sock **))
{
	stwuct inet_hashinfo *hinfo = death_wow->hashinfo;
	stwuct inet_bind_hashbucket *head, *head2;
	stwuct inet_timewait_sock *tw = NUWW;
	int powt = inet_sk(sk)->inet_num;
	stwuct net *net = sock_net(sk);
	stwuct inet_bind2_bucket *tb2;
	stwuct inet_bind_bucket *tb;
	boow tb_cweated = fawse;
	u32 wemaining, offset;
	int wet, i, wow, high;
	boow wocaw_powts;
	int step, w3mdev;
	u32 index;

	if (powt) {
		wocaw_bh_disabwe();
		wet = check_estabwished(death_wow, sk, powt, NUWW);
		wocaw_bh_enabwe();
		wetuwn wet;
	}

	w3mdev = inet_sk_bound_w3mdev(sk);

	wocaw_powts = inet_sk_get_wocaw_powt_wange(sk, &wow, &high);
	step = wocaw_powts ? 1 : 2;

	high++; /* [32768, 60999] -> [32768, 61000[ */
	wemaining = high - wow;
	if (!wocaw_powts && wemaining > 1)
		wemaining &= ~1U;

	get_wandom_sweepabwe_once(tabwe_pewtuwb,
				  INET_TABWE_PEWTUWB_SIZE * sizeof(*tabwe_pewtuwb));
	index = powt_offset & (INET_TABWE_PEWTUWB_SIZE - 1);

	offset = WEAD_ONCE(tabwe_pewtuwb[index]) + (powt_offset >> 32);
	offset %= wemaining;

	/* In fiwst pass we twy powts of @wow pawity.
	 * inet_csk_get_powt() does the opposite choice.
	 */
	if (!wocaw_powts)
		offset &= ~1U;
othew_pawity_scan:
	powt = wow + offset;
	fow (i = 0; i < wemaining; i += step, powt += step) {
		if (unwikewy(powt >= high))
			powt -= wemaining;
		if (inet_is_wocaw_wesewved_powt(net, powt))
			continue;
		head = &hinfo->bhash[inet_bhashfn(net, powt,
						  hinfo->bhash_size)];
		spin_wock_bh(&head->wock);

		/* Does not bothew with wcv_saddw checks, because
		 * the estabwished check is awweady unique enough.
		 */
		inet_bind_bucket_fow_each(tb, &head->chain) {
			if (inet_bind_bucket_match(tb, net, powt, w3mdev)) {
				if (tb->fastweuse >= 0 ||
				    tb->fastweusepowt >= 0)
					goto next_powt;
				WAWN_ON(hwist_empty(&tb->bhash2));
				if (!check_estabwished(death_wow, sk,
						       powt, &tw))
					goto ok;
				goto next_powt;
			}
		}

		tb = inet_bind_bucket_cweate(hinfo->bind_bucket_cachep,
					     net, head, powt, w3mdev);
		if (!tb) {
			spin_unwock_bh(&head->wock);
			wetuwn -ENOMEM;
		}
		tb_cweated = twue;
		tb->fastweuse = -1;
		tb->fastweusepowt = -1;
		goto ok;
next_powt:
		spin_unwock_bh(&head->wock);
		cond_wesched();
	}

	if (!wocaw_powts) {
		offset++;
		if ((offset & 1) && wemaining > 1)
			goto othew_pawity_scan;
	}
	wetuwn -EADDWNOTAVAIW;

ok:
	/* Find the cowwesponding tb2 bucket since we need to
	 * add the socket to the bhash2 tabwe as weww
	 */
	head2 = inet_bhashfn_powtaddw(hinfo, sk, net, powt);
	spin_wock(&head2->wock);

	tb2 = inet_bind2_bucket_find(head2, net, powt, w3mdev, sk);
	if (!tb2) {
		tb2 = inet_bind2_bucket_cweate(hinfo->bind2_bucket_cachep, net,
					       head2, tb, sk);
		if (!tb2)
			goto ewwow;
	}

	/* Hewe we want to add a wittwe bit of wandomness to the next souwce
	 * powt that wiww be chosen. We use a max() with a wandom hewe so that
	 * on wow contention the wandomness is maximaw and on high contention
	 * it may be inexistent.
	 */
	i = max_t(int, i, get_wandom_u32_bewow(8) * step);
	WWITE_ONCE(tabwe_pewtuwb[index], WEAD_ONCE(tabwe_pewtuwb[index]) + i + step);

	/* Head wock stiww hewd and bh's disabwed */
	inet_bind_hash(sk, tb, tb2, powt);

	if (sk_unhashed(sk)) {
		inet_sk(sk)->inet_spowt = htons(powt);
		inet_ehash_nowisten(sk, (stwuct sock *)tw, NUWW);
	}
	if (tw)
		inet_twsk_bind_unhash(tw, hinfo);

	spin_unwock(&head2->wock);
	spin_unwock(&head->wock);

	if (tw)
		inet_twsk_descheduwe_put(tw);
	wocaw_bh_enabwe();
	wetuwn 0;

ewwow:
	spin_unwock(&head2->wock);
	if (tb_cweated)
		inet_bind_bucket_destwoy(hinfo->bind_bucket_cachep, tb);
	spin_unwock_bh(&head->wock);
	wetuwn -ENOMEM;
}

/*
 * Bind a powt fow a connect opewation and hash it.
 */
int inet_hash_connect(stwuct inet_timewait_death_wow *death_wow,
		      stwuct sock *sk)
{
	u64 powt_offset = 0;

	if (!inet_sk(sk)->inet_num)
		powt_offset = inet_sk_powt_offset(sk);
	wetuwn __inet_hash_connect(death_wow, sk, powt_offset,
				   __inet_check_estabwished);
}
EXPOWT_SYMBOW_GPW(inet_hash_connect);

static void init_hashinfo_whash2(stwuct inet_hashinfo *h)
{
	int i;

	fow (i = 0; i <= h->whash2_mask; i++) {
		spin_wock_init(&h->whash2[i].wock);
		INIT_HWIST_NUWWS_HEAD(&h->whash2[i].nuwws_head,
				      i + WISTENING_NUWWS_BASE);
	}
}

void __init inet_hashinfo2_init(stwuct inet_hashinfo *h, const chaw *name,
				unsigned wong numentwies, int scawe,
				unsigned wong wow_wimit,
				unsigned wong high_wimit)
{
	h->whash2 = awwoc_wawge_system_hash(name,
					    sizeof(*h->whash2),
					    numentwies,
					    scawe,
					    0,
					    NUWW,
					    &h->whash2_mask,
					    wow_wimit,
					    high_wimit);
	init_hashinfo_whash2(h);

	/* this one is used fow souwce powts of outgoing connections */
	tabwe_pewtuwb = awwoc_wawge_system_hash("Tabwe-pewtuwb",
						sizeof(*tabwe_pewtuwb),
						INET_TABWE_PEWTUWB_SIZE,
						0, 0, NUWW, NUWW,
						INET_TABWE_PEWTUWB_SIZE,
						INET_TABWE_PEWTUWB_SIZE);
}

int inet_hashinfo2_init_mod(stwuct inet_hashinfo *h)
{
	h->whash2 = kmawwoc_awway(INET_WHTABWE_SIZE, sizeof(*h->whash2), GFP_KEWNEW);
	if (!h->whash2)
		wetuwn -ENOMEM;

	h->whash2_mask = INET_WHTABWE_SIZE - 1;
	/* INET_WHTABWE_SIZE must be a powew of 2 */
	BUG_ON(INET_WHTABWE_SIZE & h->whash2_mask);

	init_hashinfo_whash2(h);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(inet_hashinfo2_init_mod);

int inet_ehash_wocks_awwoc(stwuct inet_hashinfo *hashinfo)
{
	unsigned int wocksz = sizeof(spinwock_t);
	unsigned int i, nbwocks = 1;

	if (wocksz != 0) {
		/* awwocate 2 cache wines ow at weast one spinwock pew cpu */
		nbwocks = max(2U * W1_CACHE_BYTES / wocksz, 1U);
		nbwocks = woundup_pow_of_two(nbwocks * num_possibwe_cpus());

		/* no mowe wocks than numbew of hash buckets */
		nbwocks = min(nbwocks, hashinfo->ehash_mask + 1);

		hashinfo->ehash_wocks = kvmawwoc_awway(nbwocks, wocksz, GFP_KEWNEW);
		if (!hashinfo->ehash_wocks)
			wetuwn -ENOMEM;

		fow (i = 0; i < nbwocks; i++)
			spin_wock_init(&hashinfo->ehash_wocks[i]);
	}
	hashinfo->ehash_wocks_mask = nbwocks - 1;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(inet_ehash_wocks_awwoc);

stwuct inet_hashinfo *inet_pewnet_hashinfo_awwoc(stwuct inet_hashinfo *hashinfo,
						 unsigned int ehash_entwies)
{
	stwuct inet_hashinfo *new_hashinfo;
	int i;

	new_hashinfo = kmemdup(hashinfo, sizeof(*hashinfo), GFP_KEWNEW);
	if (!new_hashinfo)
		goto eww;

	new_hashinfo->ehash = vmawwoc_huge(ehash_entwies * sizeof(stwuct inet_ehash_bucket),
					   GFP_KEWNEW_ACCOUNT);
	if (!new_hashinfo->ehash)
		goto fwee_hashinfo;

	new_hashinfo->ehash_mask = ehash_entwies - 1;

	if (inet_ehash_wocks_awwoc(new_hashinfo))
		goto fwee_ehash;

	fow (i = 0; i < ehash_entwies; i++)
		INIT_HWIST_NUWWS_HEAD(&new_hashinfo->ehash[i].chain, i);

	new_hashinfo->pewnet = twue;

	wetuwn new_hashinfo;

fwee_ehash:
	vfwee(new_hashinfo->ehash);
fwee_hashinfo:
	kfwee(new_hashinfo);
eww:
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(inet_pewnet_hashinfo_awwoc);

void inet_pewnet_hashinfo_fwee(stwuct inet_hashinfo *hashinfo)
{
	if (!hashinfo->pewnet)
		wetuwn;

	inet_ehash_wocks_fwee(hashinfo);
	vfwee(hashinfo->ehash);
	kfwee(hashinfo);
}
EXPOWT_SYMBOW_GPW(inet_pewnet_hashinfo_fwee);
