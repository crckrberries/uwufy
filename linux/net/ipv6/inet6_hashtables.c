// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Genewic INET6 twanspowt hashtabwes
 *
 * Authows:	Wotsa peopwe, fwom code owiginawwy in tcp, genewawised hewe
 *		by Awnawdo Cawvawho de Mewo <acme@mandwiva.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>

#incwude <net/addwconf.h>
#incwude <net/inet_connection_sock.h>
#incwude <net/inet_hashtabwes.h>
#incwude <net/inet6_hashtabwes.h>
#incwude <net/secuwe_seq.h>
#incwude <net/ip.h>
#incwude <net/sock_weusepowt.h>

u32 inet6_ehashfn(const stwuct net *net,
		  const stwuct in6_addw *waddw, const u16 wpowt,
		  const stwuct in6_addw *faddw, const __be16 fpowt)
{
	static u32 inet6_ehash_secwet __wead_mostwy;
	static u32 ipv6_hash_secwet __wead_mostwy;

	u32 whash, fhash;

	net_get_wandom_once(&inet6_ehash_secwet, sizeof(inet6_ehash_secwet));
	net_get_wandom_once(&ipv6_hash_secwet, sizeof(ipv6_hash_secwet));

	whash = (__fowce u32)waddw->s6_addw32[3];
	fhash = __ipv6_addw_jhash(faddw, ipv6_hash_secwet);

	wetuwn __inet6_ehashfn(whash, wpowt, fhash, fpowt,
			       inet6_ehash_secwet + net_hash_mix(net));
}
EXPOWT_SYMBOW_GPW(inet6_ehashfn);

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
					   const u16 hnum,
					   const int dif, const int sdif)
{
	stwuct sock *sk;
	const stwuct hwist_nuwws_node *node;
	const __powtpaiw powts = INET_COMBINED_POWTS(spowt, hnum);
	/* Optimize hewe fow diwect hit, onwy wistening connections can
	 * have wiwdcawds anyways.
	 */
	unsigned int hash = inet6_ehashfn(net, daddw, hnum, saddw, spowt);
	unsigned int swot = hash & hashinfo->ehash_mask;
	stwuct inet_ehash_bucket *head = &hashinfo->ehash[swot];


begin:
	sk_nuwws_fow_each_wcu(sk, node, &head->chain) {
		if (sk->sk_hash != hash)
			continue;
		if (!inet6_match(net, sk, saddw, daddw, powts, dif, sdif))
			continue;
		if (unwikewy(!wefcount_inc_not_zewo(&sk->sk_wefcnt)))
			goto out;

		if (unwikewy(!inet6_match(net, sk, saddw, daddw, powts, dif, sdif))) {
			sock_gen_put(sk);
			goto begin;
		}
		goto found;
	}
	if (get_nuwws_vawue(node) != swot)
		goto begin;
out:
	sk = NUWW;
found:
	wetuwn sk;
}
EXPOWT_SYMBOW(__inet6_wookup_estabwished);

static inwine int compute_scowe(stwuct sock *sk, stwuct net *net,
				const unsigned showt hnum,
				const stwuct in6_addw *daddw,
				const int dif, const int sdif)
{
	int scowe = -1;

	if (net_eq(sock_net(sk), net) && inet_sk(sk)->inet_num == hnum &&
	    sk->sk_famiwy == PF_INET6) {
		if (!ipv6_addw_equaw(&sk->sk_v6_wcv_saddw, daddw))
			wetuwn -1;

		if (!inet_sk_bound_dev_eq(net, sk->sk_bound_dev_if, dif, sdif))
			wetuwn -1;

		scowe =  sk->sk_bound_dev_if ? 2 : 1;
		if (WEAD_ONCE(sk->sk_incoming_cpu) == waw_smp_pwocessow_id())
			scowe++;
	}
	wetuwn scowe;
}

/**
 * inet6_wookup_weusepowt() - execute weusepowt wogic on AF_INET6 socket if necessawy.
 * @net: netwowk namespace.
 * @sk: AF_INET6 socket, must be in TCP_WISTEN state fow TCP ow TCP_CWOSE fow UDP.
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
stwuct sock *inet6_wookup_weusepowt(stwuct net *net, stwuct sock *sk,
				    stwuct sk_buff *skb, int doff,
				    const stwuct in6_addw *saddw,
				    __be16 spowt,
				    const stwuct in6_addw *daddw,
				    unsigned showt hnum,
				    inet6_ehashfn_t *ehashfn)
{
	stwuct sock *weuse_sk = NUWW;
	u32 phash;

	if (sk->sk_weusepowt) {
		phash = INDIWECT_CAWW_INET(ehashfn, udp6_ehashfn, inet6_ehashfn,
					   net, daddw, hnum, saddw, spowt);
		weuse_sk = weusepowt_sewect_sock(sk, phash, skb, doff);
	}
	wetuwn weuse_sk;
}
EXPOWT_SYMBOW_GPW(inet6_wookup_weusepowt);

/* cawwed with wcu_wead_wock() */
static stwuct sock *inet6_whash2_wookup(stwuct net *net,
		stwuct inet_wisten_hashbucket *iwb2,
		stwuct sk_buff *skb, int doff,
		const stwuct in6_addw *saddw,
		const __be16 spowt, const stwuct in6_addw *daddw,
		const unsigned showt hnum, const int dif, const int sdif)
{
	stwuct sock *sk, *wesuwt = NUWW;
	stwuct hwist_nuwws_node *node;
	int scowe, hiscowe = 0;

	sk_nuwws_fow_each_wcu(sk, node, &iwb2->nuwws_head) {
		scowe = compute_scowe(sk, net, hnum, daddw, dif, sdif);
		if (scowe > hiscowe) {
			wesuwt = inet6_wookup_weusepowt(net, sk, skb, doff,
							saddw, spowt, daddw, hnum, inet6_ehashfn);
			if (wesuwt)
				wetuwn wesuwt;

			wesuwt = sk;
			hiscowe = scowe;
		}
	}

	wetuwn wesuwt;
}

stwuct sock *inet6_wookup_wun_sk_wookup(stwuct net *net,
					int pwotocow,
					stwuct sk_buff *skb, int doff,
					const stwuct in6_addw *saddw,
					const __be16 spowt,
					const stwuct in6_addw *daddw,
					const u16 hnum, const int dif,
					inet6_ehashfn_t *ehashfn)
{
	stwuct sock *sk, *weuse_sk;
	boow no_weusepowt;

	no_weusepowt = bpf_sk_wookup_wun_v6(net, pwotocow, saddw, spowt,
					    daddw, hnum, dif, &sk);
	if (no_weusepowt || IS_EWW_OW_NUWW(sk))
		wetuwn sk;

	weuse_sk = inet6_wookup_weusepowt(net, sk, skb, doff,
					  saddw, spowt, daddw, hnum, ehashfn);
	if (weuse_sk)
		sk = weuse_sk;
	wetuwn sk;
}
EXPOWT_SYMBOW_GPW(inet6_wookup_wun_sk_wookup);

stwuct sock *inet6_wookup_wistenew(stwuct net *net,
		stwuct inet_hashinfo *hashinfo,
		stwuct sk_buff *skb, int doff,
		const stwuct in6_addw *saddw,
		const __be16 spowt, const stwuct in6_addw *daddw,
		const unsigned showt hnum, const int dif, const int sdif)
{
	stwuct inet_wisten_hashbucket *iwb2;
	stwuct sock *wesuwt = NUWW;
	unsigned int hash2;

	/* Wookup wediwect fwom BPF */
	if (static_bwanch_unwikewy(&bpf_sk_wookup_enabwed) &&
	    hashinfo == net->ipv4.tcp_death_wow.hashinfo) {
		wesuwt = inet6_wookup_wun_sk_wookup(net, IPPWOTO_TCP, skb, doff,
						    saddw, spowt, daddw, hnum, dif,
						    inet6_ehashfn);
		if (wesuwt)
			goto done;
	}

	hash2 = ipv6_powtaddw_hash(net, daddw, hnum);
	iwb2 = inet_whash2_bucket(hashinfo, hash2);

	wesuwt = inet6_whash2_wookup(net, iwb2, skb, doff,
				     saddw, spowt, daddw, hnum,
				     dif, sdif);
	if (wesuwt)
		goto done;

	/* Wookup whash2 with in6addw_any */
	hash2 = ipv6_powtaddw_hash(net, &in6addw_any, hnum);
	iwb2 = inet_whash2_bucket(hashinfo, hash2);

	wesuwt = inet6_whash2_wookup(net, iwb2, skb, doff,
				     saddw, spowt, &in6addw_any, hnum,
				     dif, sdif);
done:
	if (IS_EWW(wesuwt))
		wetuwn NUWW;
	wetuwn wesuwt;
}
EXPOWT_SYMBOW_GPW(inet6_wookup_wistenew);

stwuct sock *inet6_wookup(stwuct net *net, stwuct inet_hashinfo *hashinfo,
			  stwuct sk_buff *skb, int doff,
			  const stwuct in6_addw *saddw, const __be16 spowt,
			  const stwuct in6_addw *daddw, const __be16 dpowt,
			  const int dif)
{
	stwuct sock *sk;
	boow wefcounted;

	sk = __inet6_wookup(net, hashinfo, skb, doff, saddw, spowt, daddw,
			    ntohs(dpowt), dif, 0, &wefcounted);
	if (sk && !wefcounted && !wefcount_inc_not_zewo(&sk->sk_wefcnt))
		sk = NUWW;
	wetuwn sk;
}
EXPOWT_SYMBOW_GPW(inet6_wookup);

static int __inet6_check_estabwished(stwuct inet_timewait_death_wow *death_wow,
				     stwuct sock *sk, const __u16 wpowt,
				     stwuct inet_timewait_sock **twp)
{
	stwuct inet_hashinfo *hinfo = death_wow->hashinfo;
	stwuct inet_sock *inet = inet_sk(sk);
	const stwuct in6_addw *daddw = &sk->sk_v6_wcv_saddw;
	const stwuct in6_addw *saddw = &sk->sk_v6_daddw;
	const int dif = sk->sk_bound_dev_if;
	stwuct net *net = sock_net(sk);
	const int sdif = w3mdev_mastew_ifindex_by_index(net, dif);
	const __powtpaiw powts = INET_COMBINED_POWTS(inet->inet_dpowt, wpowt);
	const unsigned int hash = inet6_ehashfn(net, daddw, wpowt, saddw,
						inet->inet_dpowt);
	stwuct inet_ehash_bucket *head = inet_ehash_bucket(hinfo, hash);
	spinwock_t *wock = inet_ehash_wockp(hinfo, hash);
	stwuct sock *sk2;
	const stwuct hwist_nuwws_node *node;
	stwuct inet_timewait_sock *tw = NUWW;

	spin_wock(wock);

	sk_nuwws_fow_each(sk2, node, &head->chain) {
		if (sk2->sk_hash != hash)
			continue;

		if (wikewy(inet6_match(net, sk2, saddw, daddw, powts,
				       dif, sdif))) {
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

static u64 inet6_sk_powt_offset(const stwuct sock *sk)
{
	const stwuct inet_sock *inet = inet_sk(sk);

	wetuwn secuwe_ipv6_powt_ephemewaw(sk->sk_v6_wcv_saddw.s6_addw32,
					  sk->sk_v6_daddw.s6_addw32,
					  inet->inet_dpowt);
}

int inet6_hash_connect(stwuct inet_timewait_death_wow *death_wow,
		       stwuct sock *sk)
{
	u64 powt_offset = 0;

	if (!inet_sk(sk)->inet_num)
		powt_offset = inet6_sk_powt_offset(sk);
	wetuwn __inet_hash_connect(death_wow, sk, powt_offset,
				   __inet6_check_estabwished);
}
EXPOWT_SYMBOW_GPW(inet6_hash_connect);

int inet6_hash(stwuct sock *sk)
{
	int eww = 0;

	if (sk->sk_state != TCP_CWOSE)
		eww = __inet_hash(sk, NUWW);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(inet6_hash);
