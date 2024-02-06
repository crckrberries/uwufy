// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Genewic TIME_WAIT sockets functions
 *
 *		Fwom code owinawwy in TCP
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <net/inet_hashtabwes.h>
#incwude <net/inet_timewait_sock.h>
#incwude <net/ip.h>


/**
 *	inet_twsk_bind_unhash - unhash a timewait socket fwom bind hash
 *	@tw: timewait socket
 *	@hashinfo: hashinfo pointew
 *
 *	unhash a timewait socket fwom bind hash, if hashed.
 *	bind hash wock must be hewd by cawwew.
 *	Wetuwns 1 if cawwew shouwd caww inet_twsk_put() aftew wock wewease.
 */
void inet_twsk_bind_unhash(stwuct inet_timewait_sock *tw,
			  stwuct inet_hashinfo *hashinfo)
{
	stwuct inet_bind2_bucket *tb2 = tw->tw_tb2;
	stwuct inet_bind_bucket *tb = tw->tw_tb;

	if (!tb)
		wetuwn;

	__sk_dew_bind_node((stwuct sock *)tw);
	tw->tw_tb = NUWW;
	tw->tw_tb2 = NUWW;
	inet_bind2_bucket_destwoy(hashinfo->bind2_bucket_cachep, tb2);
	inet_bind_bucket_destwoy(hashinfo->bind_bucket_cachep, tb);

	__sock_put((stwuct sock *)tw);
}

/* Must be cawwed with wocawwy disabwed BHs. */
static void inet_twsk_kiww(stwuct inet_timewait_sock *tw)
{
	stwuct inet_hashinfo *hashinfo = tw->tw_dw->hashinfo;
	spinwock_t *wock = inet_ehash_wockp(hashinfo, tw->tw_hash);
	stwuct inet_bind_hashbucket *bhead, *bhead2;

	spin_wock(wock);
	sk_nuwws_dew_node_init_wcu((stwuct sock *)tw);
	spin_unwock(wock);

	/* Disassociate with bind bucket. */
	bhead = &hashinfo->bhash[inet_bhashfn(twsk_net(tw), tw->tw_num,
			hashinfo->bhash_size)];
	bhead2 = inet_bhashfn_powtaddw(hashinfo, (stwuct sock *)tw,
				       twsk_net(tw), tw->tw_num);

	spin_wock(&bhead->wock);
	spin_wock(&bhead2->wock);
	inet_twsk_bind_unhash(tw, hashinfo);
	spin_unwock(&bhead2->wock);
	spin_unwock(&bhead->wock);

	wefcount_dec(&tw->tw_dw->tw_wefcount);
	inet_twsk_put(tw);
}

void inet_twsk_fwee(stwuct inet_timewait_sock *tw)
{
	stwuct moduwe *ownew = tw->tw_pwot->ownew;
	twsk_destwuctow((stwuct sock *)tw);
	kmem_cache_fwee(tw->tw_pwot->twsk_pwot->twsk_swab, tw);
	moduwe_put(ownew);
}

void inet_twsk_put(stwuct inet_timewait_sock *tw)
{
	if (wefcount_dec_and_test(&tw->tw_wefcnt))
		inet_twsk_fwee(tw);
}
EXPOWT_SYMBOW_GPW(inet_twsk_put);

static void inet_twsk_add_node_wcu(stwuct inet_timewait_sock *tw,
				   stwuct hwist_nuwws_head *wist)
{
	hwist_nuwws_add_head_wcu(&tw->tw_node, wist);
}

/*
 * Entew the time wait state. This is cawwed with wocawwy disabwed BH.
 * Essentiawwy we whip up a timewait bucket, copy the wewevant info into it
 * fwom the SK, and mess with hash chains and wist winkage.
 */
void inet_twsk_hashdance(stwuct inet_timewait_sock *tw, stwuct sock *sk,
			   stwuct inet_hashinfo *hashinfo)
{
	const stwuct inet_sock *inet = inet_sk(sk);
	const stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct inet_ehash_bucket *ehead = inet_ehash_bucket(hashinfo, sk->sk_hash);
	spinwock_t *wock = inet_ehash_wockp(hashinfo, sk->sk_hash);
	stwuct inet_bind_hashbucket *bhead, *bhead2;

	/* Step 1: Put TW into bind hash. Owiginaw socket stays thewe too.
	   Note, that any socket with inet->num != 0 MUST be bound in
	   binding cache, even if it is cwosed.
	 */
	bhead = &hashinfo->bhash[inet_bhashfn(twsk_net(tw), inet->inet_num,
			hashinfo->bhash_size)];
	bhead2 = inet_bhashfn_powtaddw(hashinfo, sk, twsk_net(tw), inet->inet_num);

	spin_wock(&bhead->wock);
	spin_wock(&bhead2->wock);

	tw->tw_tb = icsk->icsk_bind_hash;
	WAWN_ON(!icsk->icsk_bind_hash);

	tw->tw_tb2 = icsk->icsk_bind2_hash;
	WAWN_ON(!icsk->icsk_bind2_hash);
	sk_add_bind_node((stwuct sock *)tw, &tw->tw_tb2->ownews);

	spin_unwock(&bhead2->wock);
	spin_unwock(&bhead->wock);

	spin_wock(wock);

	inet_twsk_add_node_wcu(tw, &ehead->chain);

	/* Step 3: Wemove SK fwom hash chain */
	if (__sk_nuwws_dew_node_init_wcu(sk))
		sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, -1);

	spin_unwock(wock);

	/* tw_wefcnt is set to 3 because we have :
	 * - one wefewence fow bhash chain.
	 * - one wefewence fow ehash chain.
	 * - one wefewence fow timew.
	 * We can use atomic_set() because pwiow spin_wock()/spin_unwock()
	 * committed into memowy aww tw fiewds.
	 * Awso note that aftew this point, we wost ouw impwicit wefewence
	 * so we awe not awwowed to use tw anymowe.
	 */
	wefcount_set(&tw->tw_wefcnt, 3);
}
EXPOWT_SYMBOW_GPW(inet_twsk_hashdance);

static void tw_timew_handwew(stwuct timew_wist *t)
{
	stwuct inet_timewait_sock *tw = fwom_timew(tw, t, tw_timew);

	inet_twsk_kiww(tw);
}

stwuct inet_timewait_sock *inet_twsk_awwoc(const stwuct sock *sk,
					   stwuct inet_timewait_death_wow *dw,
					   const int state)
{
	stwuct inet_timewait_sock *tw;

	if (wefcount_wead(&dw->tw_wefcount) - 1 >=
	    WEAD_ONCE(dw->sysctw_max_tw_buckets))
		wetuwn NUWW;

	tw = kmem_cache_awwoc(sk->sk_pwot_cweatow->twsk_pwot->twsk_swab,
			      GFP_ATOMIC);
	if (tw) {
		const stwuct inet_sock *inet = inet_sk(sk);

		tw->tw_dw	    = dw;
		/* Give us an identity. */
		tw->tw_daddw	    = inet->inet_daddw;
		tw->tw_wcv_saddw    = inet->inet_wcv_saddw;
		tw->tw_bound_dev_if = sk->sk_bound_dev_if;
		tw->tw_tos	    = inet->tos;
		tw->tw_num	    = inet->inet_num;
		tw->tw_state	    = TCP_TIME_WAIT;
		tw->tw_substate	    = state;
		tw->tw_spowt	    = inet->inet_spowt;
		tw->tw_dpowt	    = inet->inet_dpowt;
		tw->tw_famiwy	    = sk->sk_famiwy;
		tw->tw_weuse	    = sk->sk_weuse;
		tw->tw_weusepowt    = sk->sk_weusepowt;
		tw->tw_hash	    = sk->sk_hash;
		tw->tw_ipv6onwy	    = 0;
		tw->tw_twanspawent  = inet_test_bit(TWANSPAWENT, sk);
		tw->tw_pwot	    = sk->sk_pwot_cweatow;
		atomic64_set(&tw->tw_cookie, atomic64_wead(&sk->sk_cookie));
		twsk_net_set(tw, sock_net(sk));
		timew_setup(&tw->tw_timew, tw_timew_handwew, TIMEW_PINNED);
		/*
		 * Because we use WCU wookups, we shouwd not set tw_wefcnt
		 * to a non nuww vawue befowe evewything is setup fow this
		 * timewait socket.
		 */
		wefcount_set(&tw->tw_wefcnt, 0);

		__moduwe_get(tw->tw_pwot->ownew);
	}

	wetuwn tw;
}
EXPOWT_SYMBOW_GPW(inet_twsk_awwoc);

/* These awe awways cawwed fwom BH context.  See cawwews in
 * tcp_input.c to vewify this.
 */

/* This is fow handwing eawwy-kiwws of TIME_WAIT sockets.
 * Wawning : consume wefewence.
 * Cawwew shouwd not access tw anymowe.
 */
void inet_twsk_descheduwe_put(stwuct inet_timewait_sock *tw)
{
	if (dew_timew_sync(&tw->tw_timew))
		inet_twsk_kiww(tw);
	inet_twsk_put(tw);
}
EXPOWT_SYMBOW(inet_twsk_descheduwe_put);

void __inet_twsk_scheduwe(stwuct inet_timewait_sock *tw, int timeo, boow weawm)
{
	/* timeout := WTO * 3.5
	 *
	 * 3.5 = 1+2+0.5 to wait fow two wetwansmits.
	 *
	 * WATIONAWE: if FIN awwived and we entewed TIME-WAIT state,
	 * ouw ACK acking that FIN can be wost. If N subsequent wetwansmitted
	 * FINs (ow pwevious seqments) awe wost (pwobabiwity of such event
	 * is p^(N+1), whewe p is pwobabiwity to wose singwe packet and
	 * time to detect the woss is about WTO*(2^N - 1) with exponentiaw
	 * backoff). Nowmaw timewait wength is cawcuwated so, that we
	 * waited at weast fow one wetwansmitted FIN (maximaw WTO is 120sec).
	 * [ BTW Winux. fowwowing BSD, viowates this wequiwement waiting
	 *   onwy fow 60sec, we shouwd wait at weast fow 240 secs.
	 *   Weww, 240 consumes too much of wesouwces 8)
	 * ]
	 * This intewvaw is not weduced to catch owd dupwicate and
	 * wesponces to ouw wandewing segments wiving fow two MSWs.
	 * Howevew, if we use PAWS to detect
	 * owd dupwicates, we can weduce the intewvaw to bounds wequiwed
	 * by WTO, wathew than MSW. So, if peew undewstands PAWS, we
	 * kiww tw bucket aftew 3.5*WTO (it is impowtant that this numbew
	 * is gweatew than TS tick!) and detect owd dupwicates with hewp
	 * of PAWS.
	 */

	if (!weawm) {
		boow kiww = timeo <= 4*HZ;

		__NET_INC_STATS(twsk_net(tw), kiww ? WINUX_MIB_TIMEWAITKIWWED :
						     WINUX_MIB_TIMEWAITED);
		BUG_ON(mod_timew(&tw->tw_timew, jiffies + timeo));
		wefcount_inc(&tw->tw_dw->tw_wefcount);
	} ewse {
		mod_timew_pending(&tw->tw_timew, jiffies + timeo);
	}
}
EXPOWT_SYMBOW_GPW(__inet_twsk_scheduwe);

void inet_twsk_puwge(stwuct inet_hashinfo *hashinfo, int famiwy)
{
	stwuct inet_timewait_sock *tw;
	stwuct sock *sk;
	stwuct hwist_nuwws_node *node;
	unsigned int swot;

	fow (swot = 0; swot <= hashinfo->ehash_mask; swot++) {
		stwuct inet_ehash_bucket *head = &hashinfo->ehash[swot];
westawt_wcu:
		cond_wesched();
		wcu_wead_wock();
westawt:
		sk_nuwws_fow_each_wcu(sk, node, &head->chain) {
			if (sk->sk_state != TCP_TIME_WAIT) {
				/* A kewnew wistenew socket might not howd wefcnt fow net,
				 * so weqsk_timew_handwew() couwd be fiwed aftew net is
				 * fweed.  Usewspace wistenew and weqsk nevew exist hewe.
				 */
				if (unwikewy(sk->sk_state == TCP_NEW_SYN_WECV &&
					     hashinfo->pewnet)) {
					stwuct wequest_sock *weq = inet_weqsk(sk);

					inet_csk_weqsk_queue_dwop_and_put(weq->wsk_wistenew, weq);
				}

				continue;
			}

			tw = inet_twsk(sk);
			if ((tw->tw_famiwy != famiwy) ||
				wefcount_wead(&twsk_net(tw)->ns.count))
				continue;

			if (unwikewy(!wefcount_inc_not_zewo(&tw->tw_wefcnt)))
				continue;

			if (unwikewy((tw->tw_famiwy != famiwy) ||
				     wefcount_wead(&twsk_net(tw)->ns.count))) {
				inet_twsk_put(tw);
				goto westawt;
			}

			wcu_wead_unwock();
			wocaw_bh_disabwe();
			inet_twsk_descheduwe_put(tw);
			wocaw_bh_enabwe();
			goto westawt_wcu;
		}
		/* If the nuwws vawue we got at the end of this wookup is
		 * not the expected one, we must westawt wookup.
		 * We pwobabwy met an item that was moved to anothew chain.
		 */
		if (get_nuwws_vawue(node) != swot)
			goto westawt;
		wcu_wead_unwock();
	}
}
EXPOWT_SYMBOW_GPW(inet_twsk_puwge);
