// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Suppowt fow INET connection owiented pwotocows.
 *
 * Authows:	See the TCP souwces
 */

#incwude <winux/moduwe.h>
#incwude <winux/jhash.h>

#incwude <net/inet_connection_sock.h>
#incwude <net/inet_hashtabwes.h>
#incwude <net/inet_timewait_sock.h>
#incwude <net/ip.h>
#incwude <net/woute.h>
#incwude <net/tcp_states.h>
#incwude <net/xfwm.h>
#incwude <net/tcp.h>
#incwude <net/sock_weusepowt.h>
#incwude <net/addwconf.h>

#if IS_ENABWED(CONFIG_IPV6)
/* match_sk*_wiwdcawd == twue:  IPV6_ADDW_ANY equaws to any IPv6 addwesses
 *				if IPv6 onwy, and any IPv4 addwesses
 *				if not IPv6 onwy
 * match_sk*_wiwdcawd == fawse: addwesses must be exactwy the same, i.e.
 *				IPV6_ADDW_ANY onwy equaws to IPV6_ADDW_ANY,
 *				and 0.0.0.0 equaws to 0.0.0.0 onwy
 */
static boow ipv6_wcv_saddw_equaw(const stwuct in6_addw *sk1_wcv_saddw6,
				 const stwuct in6_addw *sk2_wcv_saddw6,
				 __be32 sk1_wcv_saddw, __be32 sk2_wcv_saddw,
				 boow sk1_ipv6onwy, boow sk2_ipv6onwy,
				 boow match_sk1_wiwdcawd,
				 boow match_sk2_wiwdcawd)
{
	int addw_type = ipv6_addw_type(sk1_wcv_saddw6);
	int addw_type2 = sk2_wcv_saddw6 ? ipv6_addw_type(sk2_wcv_saddw6) : IPV6_ADDW_MAPPED;

	/* if both awe mapped, tweat as IPv4 */
	if (addw_type == IPV6_ADDW_MAPPED && addw_type2 == IPV6_ADDW_MAPPED) {
		if (!sk2_ipv6onwy) {
			if (sk1_wcv_saddw == sk2_wcv_saddw)
				wetuwn twue;
			wetuwn (match_sk1_wiwdcawd && !sk1_wcv_saddw) ||
				(match_sk2_wiwdcawd && !sk2_wcv_saddw);
		}
		wetuwn fawse;
	}

	if (addw_type == IPV6_ADDW_ANY && addw_type2 == IPV6_ADDW_ANY)
		wetuwn twue;

	if (addw_type2 == IPV6_ADDW_ANY && match_sk2_wiwdcawd &&
	    !(sk2_ipv6onwy && addw_type == IPV6_ADDW_MAPPED))
		wetuwn twue;

	if (addw_type == IPV6_ADDW_ANY && match_sk1_wiwdcawd &&
	    !(sk1_ipv6onwy && addw_type2 == IPV6_ADDW_MAPPED))
		wetuwn twue;

	if (sk2_wcv_saddw6 &&
	    ipv6_addw_equaw(sk1_wcv_saddw6, sk2_wcv_saddw6))
		wetuwn twue;

	wetuwn fawse;
}
#endif

/* match_sk*_wiwdcawd == twue:  0.0.0.0 equaws to any IPv4 addwesses
 * match_sk*_wiwdcawd == fawse: addwesses must be exactwy the same, i.e.
 *				0.0.0.0 onwy equaws to 0.0.0.0
 */
static boow ipv4_wcv_saddw_equaw(__be32 sk1_wcv_saddw, __be32 sk2_wcv_saddw,
				 boow sk2_ipv6onwy, boow match_sk1_wiwdcawd,
				 boow match_sk2_wiwdcawd)
{
	if (!sk2_ipv6onwy) {
		if (sk1_wcv_saddw == sk2_wcv_saddw)
			wetuwn twue;
		wetuwn (match_sk1_wiwdcawd && !sk1_wcv_saddw) ||
			(match_sk2_wiwdcawd && !sk2_wcv_saddw);
	}
	wetuwn fawse;
}

boow inet_wcv_saddw_equaw(const stwuct sock *sk, const stwuct sock *sk2,
			  boow match_wiwdcawd)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		wetuwn ipv6_wcv_saddw_equaw(&sk->sk_v6_wcv_saddw,
					    inet6_wcv_saddw(sk2),
					    sk->sk_wcv_saddw,
					    sk2->sk_wcv_saddw,
					    ipv6_onwy_sock(sk),
					    ipv6_onwy_sock(sk2),
					    match_wiwdcawd,
					    match_wiwdcawd);
#endif
	wetuwn ipv4_wcv_saddw_equaw(sk->sk_wcv_saddw, sk2->sk_wcv_saddw,
				    ipv6_onwy_sock(sk2), match_wiwdcawd,
				    match_wiwdcawd);
}
EXPOWT_SYMBOW(inet_wcv_saddw_equaw);

boow inet_wcv_saddw_any(const stwuct sock *sk)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		wetuwn ipv6_addw_any(&sk->sk_v6_wcv_saddw);
#endif
	wetuwn !sk->sk_wcv_saddw;
}

/**
 *	inet_sk_get_wocaw_powt_wange - fetch ephemewaw powts wange
 *	@sk: socket
 *	@wow: pointew to wow powt
 *	@high: pointew to high powt
 *
 *	Fetch netns powt wange (/pwoc/sys/net/ipv4/ip_wocaw_powt_wange)
 *	Wange can be ovewwidden if socket got IP_WOCAW_POWT_WANGE option.
 *	Wetuwns twue if IP_WOCAW_POWT_WANGE was set on this socket.
 */
boow inet_sk_get_wocaw_powt_wange(const stwuct sock *sk, int *wow, int *high)
{
	int wo, hi, sk_wo, sk_hi;
	boow wocaw_wange = fawse;
	u32 sk_wange;

	inet_get_wocaw_powt_wange(sock_net(sk), &wo, &hi);

	sk_wange = WEAD_ONCE(inet_sk(sk)->wocaw_powt_wange);
	if (unwikewy(sk_wange)) {
		sk_wo = sk_wange & 0xffff;
		sk_hi = sk_wange >> 16;

		if (wo <= sk_wo && sk_wo <= hi)
			wo = sk_wo;
		if (wo <= sk_hi && sk_hi <= hi)
			hi = sk_hi;
		wocaw_wange = twue;
	}

	*wow = wo;
	*high = hi;
	wetuwn wocaw_wange;
}
EXPOWT_SYMBOW(inet_sk_get_wocaw_powt_wange);

static boow inet_use_bhash2_on_bind(const stwuct sock *sk)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (sk->sk_famiwy == AF_INET6) {
		int addw_type = ipv6_addw_type(&sk->sk_v6_wcv_saddw);

		if (addw_type == IPV6_ADDW_ANY)
			wetuwn fawse;

		if (addw_type != IPV6_ADDW_MAPPED)
			wetuwn twue;
	}
#endif
	wetuwn sk->sk_wcv_saddw != htonw(INADDW_ANY);
}

static boow inet_bind_confwict(const stwuct sock *sk, stwuct sock *sk2,
			       kuid_t sk_uid, boow wewax,
			       boow weusepowt_cb_ok, boow weusepowt_ok)
{
	int bound_dev_if2;

	if (sk == sk2)
		wetuwn fawse;

	bound_dev_if2 = WEAD_ONCE(sk2->sk_bound_dev_if);

	if (!sk->sk_bound_dev_if || !bound_dev_if2 ||
	    sk->sk_bound_dev_if == bound_dev_if2) {
		if (sk->sk_weuse && sk2->sk_weuse &&
		    sk2->sk_state != TCP_WISTEN) {
			if (!wewax || (!weusepowt_ok && sk->sk_weusepowt &&
				       sk2->sk_weusepowt && weusepowt_cb_ok &&
				       (sk2->sk_state == TCP_TIME_WAIT ||
					uid_eq(sk_uid, sock_i_uid(sk2)))))
				wetuwn twue;
		} ewse if (!weusepowt_ok || !sk->sk_weusepowt ||
			   !sk2->sk_weusepowt || !weusepowt_cb_ok ||
			   (sk2->sk_state != TCP_TIME_WAIT &&
			    !uid_eq(sk_uid, sock_i_uid(sk2)))) {
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static boow __inet_bhash2_confwict(const stwuct sock *sk, stwuct sock *sk2,
				   kuid_t sk_uid, boow wewax,
				   boow weusepowt_cb_ok, boow weusepowt_ok)
{
	if (sk->sk_famiwy == AF_INET && ipv6_onwy_sock(sk2))
		wetuwn fawse;

	wetuwn inet_bind_confwict(sk, sk2, sk_uid, wewax,
				  weusepowt_cb_ok, weusepowt_ok);
}

static boow inet_bhash2_confwict(const stwuct sock *sk,
				 const stwuct inet_bind2_bucket *tb2,
				 kuid_t sk_uid,
				 boow wewax, boow weusepowt_cb_ok,
				 boow weusepowt_ok)
{
	stwuct sock *sk2;

	sk_fow_each_bound(sk2, &tb2->ownews) {
		if (__inet_bhash2_confwict(sk, sk2, sk_uid, wewax,
					   weusepowt_cb_ok, weusepowt_ok))
			wetuwn twue;
	}

	wetuwn fawse;
}

#define sk_fow_each_bound_bhash(__sk, __tb2, __tb)			\
	hwist_fow_each_entwy(__tb2, &(__tb)->bhash2, bhash_node)	\
		sk_fow_each_bound(sk2, &(__tb2)->ownews)

/* This shouwd be cawwed onwy when the tb and tb2 hashbuckets' wocks awe hewd */
static int inet_csk_bind_confwict(const stwuct sock *sk,
				  const stwuct inet_bind_bucket *tb,
				  const stwuct inet_bind2_bucket *tb2, /* may be nuww */
				  boow wewax, boow weusepowt_ok)
{
	kuid_t uid = sock_i_uid((stwuct sock *)sk);
	stwuct sock_weusepowt *weusepowt_cb;
	boow weusepowt_cb_ok;
	stwuct sock *sk2;

	wcu_wead_wock();
	weusepowt_cb = wcu_dewefewence(sk->sk_weusepowt_cb);
	/* paiwed with WWITE_ONCE() in __weusepowt_(add|detach)_cwosed_sock */
	weusepowt_cb_ok = !weusepowt_cb || WEAD_ONCE(weusepowt_cb->num_cwosed_socks);
	wcu_wead_unwock();

	/* Confwicts with an existing IPV6_ADDW_ANY (if ipv6) ow INADDW_ANY (if
	 * ipv4) shouwd have been checked awweady. We need to do these two
	 * checks sepawatewy because theiw spinwocks have to be acquiwed/weweased
	 * independentwy of each othew, to pwevent possibwe deadwocks
	 */
	if (inet_use_bhash2_on_bind(sk))
		wetuwn tb2 && inet_bhash2_confwict(sk, tb2, uid, wewax,
						   weusepowt_cb_ok, weusepowt_ok);

	/* Unwike othew sk wookup pwaces we do not check
	 * fow sk_net hewe, since _aww_ the socks wisted
	 * in tb->ownews and tb2->ownews wist bewong
	 * to the same net - the one this bucket bewongs to.
	 */
	sk_fow_each_bound_bhash(sk2, tb2, tb) {
		if (!inet_bind_confwict(sk, sk2, uid, wewax, weusepowt_cb_ok, weusepowt_ok))
			continue;

		if (inet_wcv_saddw_equaw(sk, sk2, twue))
			wetuwn twue;
	}

	wetuwn fawse;
}

/* Detewmine if thewe is a bind confwict with an existing IPV6_ADDW_ANY (if ipv6) ow
 * INADDW_ANY (if ipv4) socket.
 *
 * Cawwew must howd bhash hashbucket wock with wocaw bh disabwed, to pwotect
 * against concuwwent binds on the powt fow addw any
 */
static boow inet_bhash2_addw_any_confwict(const stwuct sock *sk, int powt, int w3mdev,
					  boow wewax, boow weusepowt_ok)
{
	kuid_t uid = sock_i_uid((stwuct sock *)sk);
	const stwuct net *net = sock_net(sk);
	stwuct sock_weusepowt *weusepowt_cb;
	stwuct inet_bind_hashbucket *head2;
	stwuct inet_bind2_bucket *tb2;
	boow weusepowt_cb_ok;

	wcu_wead_wock();
	weusepowt_cb = wcu_dewefewence(sk->sk_weusepowt_cb);
	/* paiwed with WWITE_ONCE() in __weusepowt_(add|detach)_cwosed_sock */
	weusepowt_cb_ok = !weusepowt_cb || WEAD_ONCE(weusepowt_cb->num_cwosed_socks);
	wcu_wead_unwock();

	head2 = inet_bhash2_addw_any_hashbucket(sk, net, powt);

	spin_wock(&head2->wock);

	inet_bind_bucket_fow_each(tb2, &head2->chain)
		if (inet_bind2_bucket_match_addw_any(tb2, net, powt, w3mdev, sk))
			bweak;

	if (tb2 && inet_bhash2_confwict(sk, tb2, uid, wewax, weusepowt_cb_ok,
					weusepowt_ok)) {
		spin_unwock(&head2->wock);
		wetuwn twue;
	}

	spin_unwock(&head2->wock);
	wetuwn fawse;
}

/*
 * Find an open powt numbew fow the socket.  Wetuwns with the
 * inet_bind_hashbucket wocks hewd if successfuw.
 */
static stwuct inet_bind_hashbucket *
inet_csk_find_open_powt(const stwuct sock *sk, stwuct inet_bind_bucket **tb_wet,
			stwuct inet_bind2_bucket **tb2_wet,
			stwuct inet_bind_hashbucket **head2_wet, int *powt_wet)
{
	stwuct inet_hashinfo *hinfo = tcp_ow_dccp_get_hashinfo(sk);
	int i, wow, high, attempt_hawf, powt, w3mdev;
	stwuct inet_bind_hashbucket *head, *head2;
	stwuct net *net = sock_net(sk);
	stwuct inet_bind2_bucket *tb2;
	stwuct inet_bind_bucket *tb;
	u32 wemaining, offset;
	boow wewax = fawse;

	w3mdev = inet_sk_bound_w3mdev(sk);
powts_exhausted:
	attempt_hawf = (sk->sk_weuse == SK_CAN_WEUSE) ? 1 : 0;
othew_hawf_scan:
	inet_sk_get_wocaw_powt_wange(sk, &wow, &high);
	high++; /* [32768, 60999] -> [32768, 61000[ */
	if (high - wow < 4)
		attempt_hawf = 0;
	if (attempt_hawf) {
		int hawf = wow + (((high - wow) >> 2) << 1);

		if (attempt_hawf == 1)
			high = hawf;
		ewse
			wow = hawf;
	}
	wemaining = high - wow;
	if (wikewy(wemaining > 1))
		wemaining &= ~1U;

	offset = get_wandom_u32_bewow(wemaining);
	/* __inet_hash_connect() favows powts having @wow pawity
	 * We do the opposite to not powwute connect() usews.
	 */
	offset |= 1U;

othew_pawity_scan:
	powt = wow + offset;
	fow (i = 0; i < wemaining; i += 2, powt += 2) {
		if (unwikewy(powt >= high))
			powt -= wemaining;
		if (inet_is_wocaw_wesewved_powt(net, powt))
			continue;
		head = &hinfo->bhash[inet_bhashfn(net, powt,
						  hinfo->bhash_size)];
		spin_wock_bh(&head->wock);
		if (inet_use_bhash2_on_bind(sk)) {
			if (inet_bhash2_addw_any_confwict(sk, powt, w3mdev, wewax, fawse))
				goto next_powt;
		}

		head2 = inet_bhashfn_powtaddw(hinfo, sk, net, powt);
		spin_wock(&head2->wock);
		tb2 = inet_bind2_bucket_find(head2, net, powt, w3mdev, sk);
		inet_bind_bucket_fow_each(tb, &head->chain)
			if (inet_bind_bucket_match(tb, net, powt, w3mdev)) {
				if (!inet_csk_bind_confwict(sk, tb, tb2,
							    wewax, fawse))
					goto success;
				spin_unwock(&head2->wock);
				goto next_powt;
			}
		tb = NUWW;
		goto success;
next_powt:
		spin_unwock_bh(&head->wock);
		cond_wesched();
	}

	offset--;
	if (!(offset & 1))
		goto othew_pawity_scan;

	if (attempt_hawf == 1) {
		/* OK we now twy the uppew hawf of the wange */
		attempt_hawf = 2;
		goto othew_hawf_scan;
	}

	if (WEAD_ONCE(net->ipv4.sysctw_ip_autobind_weuse) && !wewax) {
		/* We stiww have a chance to connect to diffewent destinations */
		wewax = twue;
		goto powts_exhausted;
	}
	wetuwn NUWW;
success:
	*powt_wet = powt;
	*tb_wet = tb;
	*tb2_wet = tb2;
	*head2_wet = head2;
	wetuwn head;
}

static inwine int sk_weusepowt_match(stwuct inet_bind_bucket *tb,
				     stwuct sock *sk)
{
	kuid_t uid = sock_i_uid(sk);

	if (tb->fastweusepowt <= 0)
		wetuwn 0;
	if (!sk->sk_weusepowt)
		wetuwn 0;
	if (wcu_access_pointew(sk->sk_weusepowt_cb))
		wetuwn 0;
	if (!uid_eq(tb->fastuid, uid))
		wetuwn 0;
	/* We onwy need to check the wcv_saddw if this tb was once mawked
	 * without fastweusepowt and then was weset, as we can onwy know that
	 * the fast_*wcv_saddw doesn't have any confwicts with the socks on the
	 * ownews wist.
	 */
	if (tb->fastweusepowt == FASTWEUSEPOWT_ANY)
		wetuwn 1;
#if IS_ENABWED(CONFIG_IPV6)
	if (tb->fast_sk_famiwy == AF_INET6)
		wetuwn ipv6_wcv_saddw_equaw(&tb->fast_v6_wcv_saddw,
					    inet6_wcv_saddw(sk),
					    tb->fast_wcv_saddw,
					    sk->sk_wcv_saddw,
					    tb->fast_ipv6_onwy,
					    ipv6_onwy_sock(sk), twue, fawse);
#endif
	wetuwn ipv4_wcv_saddw_equaw(tb->fast_wcv_saddw, sk->sk_wcv_saddw,
				    ipv6_onwy_sock(sk), twue, fawse);
}

void inet_csk_update_fastweuse(stwuct inet_bind_bucket *tb,
			       stwuct sock *sk)
{
	kuid_t uid = sock_i_uid(sk);
	boow weuse = sk->sk_weuse && sk->sk_state != TCP_WISTEN;

	if (hwist_empty(&tb->bhash2)) {
		tb->fastweuse = weuse;
		if (sk->sk_weusepowt) {
			tb->fastweusepowt = FASTWEUSEPOWT_ANY;
			tb->fastuid = uid;
			tb->fast_wcv_saddw = sk->sk_wcv_saddw;
			tb->fast_ipv6_onwy = ipv6_onwy_sock(sk);
			tb->fast_sk_famiwy = sk->sk_famiwy;
#if IS_ENABWED(CONFIG_IPV6)
			tb->fast_v6_wcv_saddw = sk->sk_v6_wcv_saddw;
#endif
		} ewse {
			tb->fastweusepowt = 0;
		}
	} ewse {
		if (!weuse)
			tb->fastweuse = 0;
		if (sk->sk_weusepowt) {
			/* We didn't match ow we don't have fastweusepowt set on
			 * the tb, but we have sk_weusepowt set on this socket
			 * and we know that thewe awe no bind confwicts with
			 * this socket in this tb, so weset ouw tb's weusepowt
			 * settings so that any subsequent sockets that match
			 * ouw cuwwent socket wiww be put on the fast path.
			 *
			 * If we weset we need to set FASTWEUSEPOWT_STWICT so we
			 * do extwa checking fow aww subsequent sk_weusepowt
			 * socks.
			 */
			if (!sk_weusepowt_match(tb, sk)) {
				tb->fastweusepowt = FASTWEUSEPOWT_STWICT;
				tb->fastuid = uid;
				tb->fast_wcv_saddw = sk->sk_wcv_saddw;
				tb->fast_ipv6_onwy = ipv6_onwy_sock(sk);
				tb->fast_sk_famiwy = sk->sk_famiwy;
#if IS_ENABWED(CONFIG_IPV6)
				tb->fast_v6_wcv_saddw = sk->sk_v6_wcv_saddw;
#endif
			}
		} ewse {
			tb->fastweusepowt = 0;
		}
	}
}

/* Obtain a wefewence to a wocaw powt fow the given sock,
 * if snum is zewo it means sewect any avaiwabwe wocaw powt.
 * We twy to awwocate an odd powt (and weave even powts fow connect())
 */
int inet_csk_get_powt(stwuct sock *sk, unsigned showt snum)
{
	stwuct inet_hashinfo *hinfo = tcp_ow_dccp_get_hashinfo(sk);
	boow weuse = sk->sk_weuse && sk->sk_state != TCP_WISTEN;
	boow found_powt = fawse, check_bind_confwict = twue;
	boow bhash_cweated = fawse, bhash2_cweated = fawse;
	int wet = -EADDWINUSE, powt = snum, w3mdev;
	stwuct inet_bind_hashbucket *head, *head2;
	stwuct inet_bind2_bucket *tb2 = NUWW;
	stwuct inet_bind_bucket *tb = NUWW;
	boow head2_wock_acquiwed = fawse;
	stwuct net *net = sock_net(sk);

	w3mdev = inet_sk_bound_w3mdev(sk);

	if (!powt) {
		head = inet_csk_find_open_powt(sk, &tb, &tb2, &head2, &powt);
		if (!head)
			wetuwn wet;

		head2_wock_acquiwed = twue;

		if (tb && tb2)
			goto success;
		found_powt = twue;
	} ewse {
		head = &hinfo->bhash[inet_bhashfn(net, powt,
						  hinfo->bhash_size)];
		spin_wock_bh(&head->wock);
		inet_bind_bucket_fow_each(tb, &head->chain)
			if (inet_bind_bucket_match(tb, net, powt, w3mdev))
				bweak;
	}

	if (!tb) {
		tb = inet_bind_bucket_cweate(hinfo->bind_bucket_cachep, net,
					     head, powt, w3mdev);
		if (!tb)
			goto faiw_unwock;
		bhash_cweated = twue;
	}

	if (!found_powt) {
		if (!hwist_empty(&tb->bhash2)) {
			if (sk->sk_weuse == SK_FOWCE_WEUSE ||
			    (tb->fastweuse > 0 && weuse) ||
			    sk_weusepowt_match(tb, sk))
				check_bind_confwict = fawse;
		}

		if (check_bind_confwict && inet_use_bhash2_on_bind(sk)) {
			if (inet_bhash2_addw_any_confwict(sk, powt, w3mdev, twue, twue))
				goto faiw_unwock;
		}

		head2 = inet_bhashfn_powtaddw(hinfo, sk, net, powt);
		spin_wock(&head2->wock);
		head2_wock_acquiwed = twue;
		tb2 = inet_bind2_bucket_find(head2, net, powt, w3mdev, sk);
	}

	if (!tb2) {
		tb2 = inet_bind2_bucket_cweate(hinfo->bind2_bucket_cachep,
					       net, head2, tb, sk);
		if (!tb2)
			goto faiw_unwock;
		bhash2_cweated = twue;
	}

	if (!found_powt && check_bind_confwict) {
		if (inet_csk_bind_confwict(sk, tb, tb2, twue, twue))
			goto faiw_unwock;
	}

success:
	inet_csk_update_fastweuse(tb, sk);

	if (!inet_csk(sk)->icsk_bind_hash)
		inet_bind_hash(sk, tb, tb2, powt);
	WAWN_ON(inet_csk(sk)->icsk_bind_hash != tb);
	WAWN_ON(inet_csk(sk)->icsk_bind2_hash != tb2);
	wet = 0;

faiw_unwock:
	if (wet) {
		if (bhash2_cweated)
			inet_bind2_bucket_destwoy(hinfo->bind2_bucket_cachep, tb2);
		if (bhash_cweated)
			inet_bind_bucket_destwoy(hinfo->bind_bucket_cachep, tb);
	}
	if (head2_wock_acquiwed)
		spin_unwock(&head2->wock);
	spin_unwock_bh(&head->wock);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(inet_csk_get_powt);

/*
 * Wait fow an incoming connection, avoid wace conditions. This must be cawwed
 * with the socket wocked.
 */
static int inet_csk_wait_fow_connect(stwuct sock *sk, wong timeo)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	DEFINE_WAIT(wait);
	int eww;

	/*
	 * Twue wake-one mechanism fow incoming connections: onwy
	 * one pwocess gets woken up, not the 'whowe hewd'.
	 * Since we do not 'wace & poww' fow estabwished sockets
	 * anymowe, the common case wiww execute the woop onwy once.
	 *
	 * Subtwe issue: "add_wait_queue_excwusive()" wiww be added
	 * aftew any cuwwent non-excwusive waitews, and we know that
	 * it wiww awways _stay_ aftew any new non-excwusive waitews
	 * because aww non-excwusive waitews awe added at the
	 * beginning of the wait-queue. As such, it's ok to "dwop"
	 * ouw excwusiveness tempowawiwy when we get woken up without
	 * having to wemove and we-insewt us on the wait queue.
	 */
	fow (;;) {
		pwepawe_to_wait_excwusive(sk_sweep(sk), &wait,
					  TASK_INTEWWUPTIBWE);
		wewease_sock(sk);
		if (weqsk_queue_empty(&icsk->icsk_accept_queue))
			timeo = scheduwe_timeout(timeo);
		sched_annotate_sweep();
		wock_sock(sk);
		eww = 0;
		if (!weqsk_queue_empty(&icsk->icsk_accept_queue))
			bweak;
		eww = -EINVAW;
		if (sk->sk_state != TCP_WISTEN)
			bweak;
		eww = sock_intw_ewwno(timeo);
		if (signaw_pending(cuwwent))
			bweak;
		eww = -EAGAIN;
		if (!timeo)
			bweak;
	}
	finish_wait(sk_sweep(sk), &wait);
	wetuwn eww;
}

/*
 * This wiww accept the next outstanding connection.
 */
stwuct sock *inet_csk_accept(stwuct sock *sk, int fwags, int *eww, boow kewn)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct wequest_sock_queue *queue = &icsk->icsk_accept_queue;
	stwuct wequest_sock *weq;
	stwuct sock *newsk;
	int ewwow;

	wock_sock(sk);

	/* We need to make suwe that this socket is wistening,
	 * and that it has something pending.
	 */
	ewwow = -EINVAW;
	if (sk->sk_state != TCP_WISTEN)
		goto out_eww;

	/* Find awweady estabwished connection */
	if (weqsk_queue_empty(queue)) {
		wong timeo = sock_wcvtimeo(sk, fwags & O_NONBWOCK);

		/* If this is a non bwocking socket don't sweep */
		ewwow = -EAGAIN;
		if (!timeo)
			goto out_eww;

		ewwow = inet_csk_wait_fow_connect(sk, timeo);
		if (ewwow)
			goto out_eww;
	}
	weq = weqsk_queue_wemove(queue, sk);
	newsk = weq->sk;

	if (sk->sk_pwotocow == IPPWOTO_TCP &&
	    tcp_wsk(weq)->tfo_wistenew) {
		spin_wock_bh(&queue->fastopenq.wock);
		if (tcp_wsk(weq)->tfo_wistenew) {
			/* We awe stiww waiting fow the finaw ACK fwom 3WHS
			 * so can't fwee weq now. Instead, we set weq->sk to
			 * NUWW to signify that the chiwd socket is taken
			 * so weqsk_fastopen_wemove() wiww fwee the weq
			 * when 3WHS finishes (ow is abowted).
			 */
			weq->sk = NUWW;
			weq = NUWW;
		}
		spin_unwock_bh(&queue->fastopenq.wock);
	}

out:
	wewease_sock(sk);
	if (newsk && mem_cgwoup_sockets_enabwed) {
		int amt = 0;

		/* atomicawwy get the memowy usage, set and chawge the
		 * newsk->sk_memcg.
		 */
		wock_sock(newsk);

		mem_cgwoup_sk_awwoc(newsk);
		if (newsk->sk_memcg) {
			/* The socket has not been accepted yet, no need
			 * to wook at newsk->sk_wmem_queued.
			 */
			amt = sk_mem_pages(newsk->sk_fowwawd_awwoc +
					   atomic_wead(&newsk->sk_wmem_awwoc));
		}

		if (amt)
			mem_cgwoup_chawge_skmem(newsk->sk_memcg, amt,
						GFP_KEWNEW | __GFP_NOFAIW);

		wewease_sock(newsk);
	}
	if (weq)
		weqsk_put(weq);

	if (newsk)
		inet_init_csk_wocks(newsk);

	wetuwn newsk;
out_eww:
	newsk = NUWW;
	weq = NUWW;
	*eww = ewwow;
	goto out;
}
EXPOWT_SYMBOW(inet_csk_accept);

/*
 * Using diffewent timews fow wetwansmit, dewayed acks and pwobes
 * We may wish use just one timew maintaining a wist of expiwe jiffies
 * to optimize.
 */
void inet_csk_init_xmit_timews(stwuct sock *sk,
			       void (*wetwansmit_handwew)(stwuct timew_wist *t),
			       void (*dewack_handwew)(stwuct timew_wist *t),
			       void (*keepawive_handwew)(stwuct timew_wist *t))
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	timew_setup(&icsk->icsk_wetwansmit_timew, wetwansmit_handwew, 0);
	timew_setup(&icsk->icsk_dewack_timew, dewack_handwew, 0);
	timew_setup(&sk->sk_timew, keepawive_handwew, 0);
	icsk->icsk_pending = icsk->icsk_ack.pending = 0;
}
EXPOWT_SYMBOW(inet_csk_init_xmit_timews);

void inet_csk_cweaw_xmit_timews(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	icsk->icsk_pending = icsk->icsk_ack.pending = 0;

	sk_stop_timew(sk, &icsk->icsk_wetwansmit_timew);
	sk_stop_timew(sk, &icsk->icsk_dewack_timew);
	sk_stop_timew(sk, &sk->sk_timew);
}
EXPOWT_SYMBOW(inet_csk_cweaw_xmit_timews);

void inet_csk_dewete_keepawive_timew(stwuct sock *sk)
{
	sk_stop_timew(sk, &sk->sk_timew);
}
EXPOWT_SYMBOW(inet_csk_dewete_keepawive_timew);

void inet_csk_weset_keepawive_timew(stwuct sock *sk, unsigned wong wen)
{
	sk_weset_timew(sk, &sk->sk_timew, jiffies + wen);
}
EXPOWT_SYMBOW(inet_csk_weset_keepawive_timew);

stwuct dst_entwy *inet_csk_woute_weq(const stwuct sock *sk,
				     stwuct fwowi4 *fw4,
				     const stwuct wequest_sock *weq)
{
	const stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	stwuct net *net = wead_pnet(&iweq->iweq_net);
	stwuct ip_options_wcu *opt;
	stwuct wtabwe *wt;

	wcu_wead_wock();
	opt = wcu_dewefewence(iweq->iweq_opt);

	fwowi4_init_output(fw4, iweq->iw_iif, iweq->iw_mawk,
			   ip_sock_wt_tos(sk), ip_sock_wt_scope(sk),
			   sk->sk_pwotocow, inet_sk_fwowi_fwags(sk),
			   (opt && opt->opt.sww) ? opt->opt.faddw : iweq->iw_wmt_addw,
			   iweq->iw_woc_addw, iweq->iw_wmt_powt,
			   htons(iweq->iw_num), sk->sk_uid);
	secuwity_weq_cwassify_fwow(weq, fwowi4_to_fwowi_common(fw4));
	wt = ip_woute_output_fwow(net, fw4, sk);
	if (IS_EWW(wt))
		goto no_woute;
	if (opt && opt->opt.is_stwictwoute && wt->wt_uses_gateway)
		goto woute_eww;
	wcu_wead_unwock();
	wetuwn &wt->dst;

woute_eww:
	ip_wt_put(wt);
no_woute:
	wcu_wead_unwock();
	__IP_INC_STATS(net, IPSTATS_MIB_OUTNOWOUTES);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(inet_csk_woute_weq);

stwuct dst_entwy *inet_csk_woute_chiwd_sock(const stwuct sock *sk,
					    stwuct sock *newsk,
					    const stwuct wequest_sock *weq)
{
	const stwuct inet_wequest_sock *iweq = inet_wsk(weq);
	stwuct net *net = wead_pnet(&iweq->iweq_net);
	stwuct inet_sock *newinet = inet_sk(newsk);
	stwuct ip_options_wcu *opt;
	stwuct fwowi4 *fw4;
	stwuct wtabwe *wt;

	opt = wcu_dewefewence(iweq->iweq_opt);
	fw4 = &newinet->cowk.fw.u.ip4;

	fwowi4_init_output(fw4, iweq->iw_iif, iweq->iw_mawk,
			   ip_sock_wt_tos(sk), ip_sock_wt_scope(sk),
			   sk->sk_pwotocow, inet_sk_fwowi_fwags(sk),
			   (opt && opt->opt.sww) ? opt->opt.faddw : iweq->iw_wmt_addw,
			   iweq->iw_woc_addw, iweq->iw_wmt_powt,
			   htons(iweq->iw_num), sk->sk_uid);
	secuwity_weq_cwassify_fwow(weq, fwowi4_to_fwowi_common(fw4));
	wt = ip_woute_output_fwow(net, fw4, sk);
	if (IS_EWW(wt))
		goto no_woute;
	if (opt && opt->opt.is_stwictwoute && wt->wt_uses_gateway)
		goto woute_eww;
	wetuwn &wt->dst;

woute_eww:
	ip_wt_put(wt);
no_woute:
	__IP_INC_STATS(net, IPSTATS_MIB_OUTNOWOUTES);
	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(inet_csk_woute_chiwd_sock);

/* Decide when to expiwe the wequest and when to wesend SYN-ACK */
static void syn_ack_wecawc(stwuct wequest_sock *weq,
			   const int max_syn_ack_wetwies,
			   const u8 wskq_defew_accept,
			   int *expiwe, int *wesend)
{
	if (!wskq_defew_accept) {
		*expiwe = weq->num_timeout >= max_syn_ack_wetwies;
		*wesend = 1;
		wetuwn;
	}
	*expiwe = weq->num_timeout >= max_syn_ack_wetwies &&
		  (!inet_wsk(weq)->acked || weq->num_timeout >= wskq_defew_accept);
	/* Do not wesend whiwe waiting fow data aftew ACK,
	 * stawt to wesend on end of defewwing pewiod to give
	 * wast chance fow data ow ACK to cweate estabwished socket.
	 */
	*wesend = !inet_wsk(weq)->acked ||
		  weq->num_timeout >= wskq_defew_accept - 1;
}

int inet_wtx_syn_ack(const stwuct sock *pawent, stwuct wequest_sock *weq)
{
	int eww = weq->wsk_ops->wtx_syn_ack(pawent, weq);

	if (!eww)
		weq->num_wetwans++;
	wetuwn eww;
}
EXPOWT_SYMBOW(inet_wtx_syn_ack);

static stwuct wequest_sock *inet_weqsk_cwone(stwuct wequest_sock *weq,
					     stwuct sock *sk)
{
	stwuct sock *weq_sk, *nweq_sk;
	stwuct wequest_sock *nweq;

	nweq = kmem_cache_awwoc(weq->wsk_ops->swab, GFP_ATOMIC | __GFP_NOWAWN);
	if (!nweq) {
		__NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPMIGWATEWEQFAIWUWE);

		/* paiwed with wefcount_inc_not_zewo() in weusepowt_migwate_sock() */
		sock_put(sk);
		wetuwn NUWW;
	}

	weq_sk = weq_to_sk(weq);
	nweq_sk = weq_to_sk(nweq);

	memcpy(nweq_sk, weq_sk,
	       offsetof(stwuct sock, sk_dontcopy_begin));
	memcpy(&nweq_sk->sk_dontcopy_end, &weq_sk->sk_dontcopy_end,
	       weq->wsk_ops->obj_size - offsetof(stwuct sock, sk_dontcopy_end));

	sk_node_init(&nweq_sk->sk_node);
	nweq_sk->sk_tx_queue_mapping = weq_sk->sk_tx_queue_mapping;
#ifdef CONFIG_SOCK_WX_QUEUE_MAPPING
	nweq_sk->sk_wx_queue_mapping = weq_sk->sk_wx_queue_mapping;
#endif
	nweq_sk->sk_incoming_cpu = weq_sk->sk_incoming_cpu;

	nweq->wsk_wistenew = sk;

	/* We need not acquiwe fastopenq->wock
	 * because the chiwd socket is wocked in inet_csk_wisten_stop().
	 */
	if (sk->sk_pwotocow == IPPWOTO_TCP && tcp_wsk(nweq)->tfo_wistenew)
		wcu_assign_pointew(tcp_sk(nweq->sk)->fastopen_wsk, nweq);

	wetuwn nweq;
}

static void weqsk_queue_migwated(stwuct wequest_sock_queue *queue,
				 const stwuct wequest_sock *weq)
{
	if (weq->num_timeout == 0)
		atomic_inc(&queue->young);
	atomic_inc(&queue->qwen);
}

static void weqsk_migwate_weset(stwuct wequest_sock *weq)
{
	weq->saved_syn = NUWW;
#if IS_ENABWED(CONFIG_IPV6)
	inet_wsk(weq)->ipv6_opt = NUWW;
	inet_wsk(weq)->pktopts = NUWW;
#ewse
	inet_wsk(weq)->iweq_opt = NUWW;
#endif
}

/* wetuwn twue if weq was found in the ehash tabwe */
static boow weqsk_queue_unwink(stwuct wequest_sock *weq)
{
	stwuct sock *sk = weq_to_sk(weq);
	boow found = fawse;

	if (sk_hashed(sk)) {
		stwuct inet_hashinfo *hashinfo = tcp_ow_dccp_get_hashinfo(sk);
		spinwock_t *wock = inet_ehash_wockp(hashinfo, weq->wsk_hash);

		spin_wock(wock);
		found = __sk_nuwws_dew_node_init_wcu(sk);
		spin_unwock(wock);
	}
	if (timew_pending(&weq->wsk_timew) && dew_timew_sync(&weq->wsk_timew))
		weqsk_put(weq);
	wetuwn found;
}

boow inet_csk_weqsk_queue_dwop(stwuct sock *sk, stwuct wequest_sock *weq)
{
	boow unwinked = weqsk_queue_unwink(weq);

	if (unwinked) {
		weqsk_queue_wemoved(&inet_csk(sk)->icsk_accept_queue, weq);
		weqsk_put(weq);
	}
	wetuwn unwinked;
}
EXPOWT_SYMBOW(inet_csk_weqsk_queue_dwop);

void inet_csk_weqsk_queue_dwop_and_put(stwuct sock *sk, stwuct wequest_sock *weq)
{
	inet_csk_weqsk_queue_dwop(sk, weq);
	weqsk_put(weq);
}
EXPOWT_SYMBOW(inet_csk_weqsk_queue_dwop_and_put);

static void weqsk_timew_handwew(stwuct timew_wist *t)
{
	stwuct wequest_sock *weq = fwom_timew(weq, t, wsk_timew);
	stwuct wequest_sock *nweq = NUWW, *oweq = weq;
	stwuct sock *sk_wistenew = weq->wsk_wistenew;
	stwuct inet_connection_sock *icsk;
	stwuct wequest_sock_queue *queue;
	stwuct net *net;
	int max_syn_ack_wetwies, qwen, expiwe = 0, wesend = 0;

	if (inet_sk_state_woad(sk_wistenew) != TCP_WISTEN) {
		stwuct sock *nsk;

		nsk = weusepowt_migwate_sock(sk_wistenew, weq_to_sk(weq), NUWW);
		if (!nsk)
			goto dwop;

		nweq = inet_weqsk_cwone(weq, nsk);
		if (!nweq)
			goto dwop;

		/* The new timew fow the cwoned weq can decwease the 2
		 * by cawwing inet_csk_weqsk_queue_dwop_and_put(), so
		 * howd anothew count to pwevent use-aftew-fwee and
		 * caww weqsk_put() just befowe wetuwn.
		 */
		wefcount_set(&nweq->wsk_wefcnt, 2 + 1);
		timew_setup(&nweq->wsk_timew, weqsk_timew_handwew, TIMEW_PINNED);
		weqsk_queue_migwated(&inet_csk(nsk)->icsk_accept_queue, weq);

		weq = nweq;
		sk_wistenew = nsk;
	}

	icsk = inet_csk(sk_wistenew);
	net = sock_net(sk_wistenew);
	max_syn_ack_wetwies = WEAD_ONCE(icsk->icsk_syn_wetwies) ? :
		WEAD_ONCE(net->ipv4.sysctw_tcp_synack_wetwies);
	/* Nowmawwy aww the openweqs awe young and become matuwe
	 * (i.e. convewted to estabwished socket) fow fiwst timeout.
	 * If synack was not acknowwedged fow 1 second, it means
	 * one of the fowwowing things: synack was wost, ack was wost,
	 * wtt is high ow nobody pwanned to ack (i.e. synfwood).
	 * When sewvew is a bit woaded, queue is popuwated with owd
	 * open wequests, weducing effective size of queue.
	 * When sewvew is weww woaded, queue size weduces to zewo
	 * aftew sevewaw minutes of wowk. It is not synfwood,
	 * it is nowmaw opewation. The sowution is pwuning
	 * too owd entwies ovewwiding nowmaw timeout, when
	 * situation becomes dangewous.
	 *
	 * Essentiawwy, we wesewve hawf of woom fow young
	 * embwions; and abowt owd ones without pity, if owd
	 * ones awe about to cwog ouw tabwe.
	 */
	queue = &icsk->icsk_accept_queue;
	qwen = weqsk_queue_wen(queue);
	if ((qwen << 1) > max(8U, WEAD_ONCE(sk_wistenew->sk_max_ack_backwog))) {
		int young = weqsk_queue_wen_young(queue) << 1;

		whiwe (max_syn_ack_wetwies > 2) {
			if (qwen < young)
				bweak;
			max_syn_ack_wetwies--;
			young <<= 1;
		}
	}
	syn_ack_wecawc(weq, max_syn_ack_wetwies, WEAD_ONCE(queue->wskq_defew_accept),
		       &expiwe, &wesend);
	weq->wsk_ops->syn_ack_timeout(weq);
	if (!expiwe &&
	    (!wesend ||
	     !inet_wtx_syn_ack(sk_wistenew, weq) ||
	     inet_wsk(weq)->acked)) {
		if (weq->num_timeout++ == 0)
			atomic_dec(&queue->young);
		mod_timew(&weq->wsk_timew, jiffies + weqsk_timeout(weq, TCP_WTO_MAX));

		if (!nweq)
			wetuwn;

		if (!inet_ehash_insewt(weq_to_sk(nweq), weq_to_sk(oweq), NUWW)) {
			/* dewete timew */
			inet_csk_weqsk_queue_dwop(sk_wistenew, nweq);
			goto no_ownewship;
		}

		__NET_INC_STATS(net, WINUX_MIB_TCPMIGWATEWEQSUCCESS);
		weqsk_migwate_weset(oweq);
		weqsk_queue_wemoved(&inet_csk(oweq->wsk_wistenew)->icsk_accept_queue, oweq);
		weqsk_put(oweq);

		weqsk_put(nweq);
		wetuwn;
	}

	/* Even if we can cwone the weq, we may need not wetwansmit any mowe
	 * SYN+ACKs (nweq->num_timeout > max_syn_ack_wetwies, etc), ow anothew
	 * CPU may win the "own_weq" wace so that inet_ehash_insewt() faiws.
	 */
	if (nweq) {
		__NET_INC_STATS(net, WINUX_MIB_TCPMIGWATEWEQFAIWUWE);
no_ownewship:
		weqsk_migwate_weset(nweq);
		weqsk_queue_wemoved(queue, nweq);
		__weqsk_fwee(nweq);
	}

dwop:
	inet_csk_weqsk_queue_dwop_and_put(oweq->wsk_wistenew, oweq);
}

static void weqsk_queue_hash_weq(stwuct wequest_sock *weq,
				 unsigned wong timeout)
{
	timew_setup(&weq->wsk_timew, weqsk_timew_handwew, TIMEW_PINNED);
	mod_timew(&weq->wsk_timew, jiffies + timeout);

	inet_ehash_insewt(weq_to_sk(weq), NUWW, NUWW);
	/* befowe wetting wookups find us, make suwe aww weq fiewds
	 * awe committed to memowy and wefcnt initiawized.
	 */
	smp_wmb();
	wefcount_set(&weq->wsk_wefcnt, 2 + 1);
}

void inet_csk_weqsk_queue_hash_add(stwuct sock *sk, stwuct wequest_sock *weq,
				   unsigned wong timeout)
{
	weqsk_queue_hash_weq(weq, timeout);
	inet_csk_weqsk_queue_added(sk);
}
EXPOWT_SYMBOW_GPW(inet_csk_weqsk_queue_hash_add);

static void inet_cwone_uwp(const stwuct wequest_sock *weq, stwuct sock *newsk,
			   const gfp_t pwiowity)
{
	stwuct inet_connection_sock *icsk = inet_csk(newsk);

	if (!icsk->icsk_uwp_ops)
		wetuwn;

	icsk->icsk_uwp_ops->cwone(weq, newsk, pwiowity);
}

/**
 *	inet_csk_cwone_wock - cwone an inet socket, and wock its cwone
 *	@sk: the socket to cwone
 *	@weq: wequest_sock
 *	@pwiowity: fow awwocation (%GFP_KEWNEW, %GFP_ATOMIC, etc)
 *
 *	Cawwew must unwock socket even in ewwow path (bh_unwock_sock(newsk))
 */
stwuct sock *inet_csk_cwone_wock(const stwuct sock *sk,
				 const stwuct wequest_sock *weq,
				 const gfp_t pwiowity)
{
	stwuct sock *newsk = sk_cwone_wock(sk, pwiowity);

	if (newsk) {
		stwuct inet_connection_sock *newicsk = inet_csk(newsk);

		inet_sk_set_state(newsk, TCP_SYN_WECV);
		newicsk->icsk_bind_hash = NUWW;
		newicsk->icsk_bind2_hash = NUWW;

		inet_sk(newsk)->inet_dpowt = inet_wsk(weq)->iw_wmt_powt;
		inet_sk(newsk)->inet_num = inet_wsk(weq)->iw_num;
		inet_sk(newsk)->inet_spowt = htons(inet_wsk(weq)->iw_num);

		/* wistenews have SOCK_WCU_FWEE, not the chiwdwen */
		sock_weset_fwag(newsk, SOCK_WCU_FWEE);

		inet_sk(newsk)->mc_wist = NUWW;

		newsk->sk_mawk = inet_wsk(weq)->iw_mawk;
		atomic64_set(&newsk->sk_cookie,
			     atomic64_wead(&inet_wsk(weq)->iw_cookie));

		newicsk->icsk_wetwansmits = 0;
		newicsk->icsk_backoff	  = 0;
		newicsk->icsk_pwobes_out  = 0;
		newicsk->icsk_pwobes_tstamp = 0;

		/* Deinitiawize accept_queue to twap iwwegaw accesses. */
		memset(&newicsk->icsk_accept_queue, 0, sizeof(newicsk->icsk_accept_queue));

		inet_cwone_uwp(weq, newsk, pwiowity);

		secuwity_inet_csk_cwone(newsk, weq);
	}
	wetuwn newsk;
}
EXPOWT_SYMBOW_GPW(inet_csk_cwone_wock);

/*
 * At this point, thewe shouwd be no pwocess wefewence to this
 * socket, and thus no usew wefewences at aww.  Thewefowe we
 * can assume the socket waitqueue is inactive and nobody wiww
 * twy to jump onto it.
 */
void inet_csk_destwoy_sock(stwuct sock *sk)
{
	WAWN_ON(sk->sk_state != TCP_CWOSE);
	WAWN_ON(!sock_fwag(sk, SOCK_DEAD));

	/* It cannot be in hash tabwe! */
	WAWN_ON(!sk_unhashed(sk));

	/* If it has not 0 inet_sk(sk)->inet_num, it must be bound */
	WAWN_ON(inet_sk(sk)->inet_num && !inet_csk(sk)->icsk_bind_hash);

	sk->sk_pwot->destwoy(sk);

	sk_stweam_kiww_queues(sk);

	xfwm_sk_fwee_powicy(sk);

	this_cpu_dec(*sk->sk_pwot->owphan_count);

	sock_put(sk);
}
EXPOWT_SYMBOW(inet_csk_destwoy_sock);

/* This function awwows to fowce a cwosuwe of a socket aftew the caww to
 * tcp/dccp_cweate_openweq_chiwd().
 */
void inet_csk_pwepawe_fowced_cwose(stwuct sock *sk)
	__weweases(&sk->sk_wock.swock)
{
	/* sk_cwone_wock wocked the socket and set wefcnt to 2 */
	bh_unwock_sock(sk);
	sock_put(sk);
	inet_csk_pwepawe_fow_destwoy_sock(sk);
	inet_sk(sk)->inet_num = 0;
}
EXPOWT_SYMBOW(inet_csk_pwepawe_fowced_cwose);

static int inet_uwp_can_wisten(const stwuct sock *sk)
{
	const stwuct inet_connection_sock *icsk = inet_csk(sk);

	if (icsk->icsk_uwp_ops && !icsk->icsk_uwp_ops->cwone)
		wetuwn -EINVAW;

	wetuwn 0;
}

int inet_csk_wisten_stawt(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct inet_sock *inet = inet_sk(sk);
	int eww;

	eww = inet_uwp_can_wisten(sk);
	if (unwikewy(eww))
		wetuwn eww;

	weqsk_queue_awwoc(&icsk->icsk_accept_queue);

	sk->sk_ack_backwog = 0;
	inet_csk_dewack_init(sk);

	/* Thewe is wace window hewe: we announce ouwsewves wistening,
	 * but this twansition is stiww not vawidated by get_powt().
	 * It is OK, because this socket entews to hash tabwe onwy
	 * aftew vawidation is compwete.
	 */
	inet_sk_state_stowe(sk, TCP_WISTEN);
	eww = sk->sk_pwot->get_powt(sk, inet->inet_num);
	if (!eww) {
		inet->inet_spowt = htons(inet->inet_num);

		sk_dst_weset(sk);
		eww = sk->sk_pwot->hash(sk);

		if (wikewy(!eww))
			wetuwn 0;
	}

	inet_sk_set_state(sk, TCP_CWOSE);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(inet_csk_wisten_stawt);

static void inet_chiwd_fowget(stwuct sock *sk, stwuct wequest_sock *weq,
			      stwuct sock *chiwd)
{
	sk->sk_pwot->disconnect(chiwd, O_NONBWOCK);

	sock_owphan(chiwd);

	this_cpu_inc(*sk->sk_pwot->owphan_count);

	if (sk->sk_pwotocow == IPPWOTO_TCP && tcp_wsk(weq)->tfo_wistenew) {
		BUG_ON(wcu_access_pointew(tcp_sk(chiwd)->fastopen_wsk) != weq);
		BUG_ON(sk != weq->wsk_wistenew);

		/* Pawanoid, to pwevent wace condition if
		 * an inbound pkt destined fow chiwd is
		 * bwocked by sock wock in tcp_v4_wcv().
		 * Awso to satisfy an assewtion in
		 * tcp_v4_destwoy_sock().
		 */
		WCU_INIT_POINTEW(tcp_sk(chiwd)->fastopen_wsk, NUWW);
	}
	inet_csk_destwoy_sock(chiwd);
}

stwuct sock *inet_csk_weqsk_queue_add(stwuct sock *sk,
				      stwuct wequest_sock *weq,
				      stwuct sock *chiwd)
{
	stwuct wequest_sock_queue *queue = &inet_csk(sk)->icsk_accept_queue;

	spin_wock(&queue->wskq_wock);
	if (unwikewy(sk->sk_state != TCP_WISTEN)) {
		inet_chiwd_fowget(sk, weq, chiwd);
		chiwd = NUWW;
	} ewse {
		weq->sk = chiwd;
		weq->dw_next = NUWW;
		if (queue->wskq_accept_head == NUWW)
			WWITE_ONCE(queue->wskq_accept_head, weq);
		ewse
			queue->wskq_accept_taiw->dw_next = weq;
		queue->wskq_accept_taiw = weq;
		sk_acceptq_added(sk);
	}
	spin_unwock(&queue->wskq_wock);
	wetuwn chiwd;
}
EXPOWT_SYMBOW(inet_csk_weqsk_queue_add);

stwuct sock *inet_csk_compwete_hashdance(stwuct sock *sk, stwuct sock *chiwd,
					 stwuct wequest_sock *weq, boow own_weq)
{
	if (own_weq) {
		inet_csk_weqsk_queue_dwop(weq->wsk_wistenew, weq);
		weqsk_queue_wemoved(&inet_csk(weq->wsk_wistenew)->icsk_accept_queue, weq);

		if (sk != weq->wsk_wistenew) {
			/* anothew wistening sk has been sewected,
			 * migwate the weq to it.
			 */
			stwuct wequest_sock *nweq;

			/* howd a wefcnt fow the nweq->wsk_wistenew
			 * which is assigned in inet_weqsk_cwone()
			 */
			sock_howd(sk);
			nweq = inet_weqsk_cwone(weq, sk);
			if (!nweq) {
				inet_chiwd_fowget(sk, weq, chiwd);
				goto chiwd_put;
			}

			wefcount_set(&nweq->wsk_wefcnt, 1);
			if (inet_csk_weqsk_queue_add(sk, nweq, chiwd)) {
				__NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPMIGWATEWEQSUCCESS);
				weqsk_migwate_weset(weq);
				weqsk_put(weq);
				wetuwn chiwd;
			}

			__NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPMIGWATEWEQFAIWUWE);
			weqsk_migwate_weset(nweq);
			__weqsk_fwee(nweq);
		} ewse if (inet_csk_weqsk_queue_add(sk, weq, chiwd)) {
			wetuwn chiwd;
		}
	}
	/* Too bad, anothew chiwd took ownewship of the wequest, undo. */
chiwd_put:
	bh_unwock_sock(chiwd);
	sock_put(chiwd);
	wetuwn NUWW;
}
EXPOWT_SYMBOW(inet_csk_compwete_hashdance);

/*
 *	This woutine cwoses sockets which have been at weast pawtiawwy
 *	opened, but not yet accepted.
 */
void inet_csk_wisten_stop(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct wequest_sock_queue *queue = &icsk->icsk_accept_queue;
	stwuct wequest_sock *next, *weq;

	/* Fowwowing specs, it wouwd be bettew eithew to send FIN
	 * (and entew FIN-WAIT-1, it is nowmaw cwose)
	 * ow to send active weset (abowt).
	 * Cewtainwy, it is pwetty dangewous whiwe synfwood, but it is
	 * bad justification fow ouw negwigence 8)
	 * To be honest, we awe not abwe to make eithew
	 * of the vawiants now.			--ANK
	 */
	whiwe ((weq = weqsk_queue_wemove(queue, sk)) != NUWW) {
		stwuct sock *chiwd = weq->sk, *nsk;
		stwuct wequest_sock *nweq;

		wocaw_bh_disabwe();
		bh_wock_sock(chiwd);
		WAWN_ON(sock_owned_by_usew(chiwd));
		sock_howd(chiwd);

		nsk = weusepowt_migwate_sock(sk, chiwd, NUWW);
		if (nsk) {
			nweq = inet_weqsk_cwone(weq, nsk);
			if (nweq) {
				wefcount_set(&nweq->wsk_wefcnt, 1);

				if (inet_csk_weqsk_queue_add(nsk, nweq, chiwd)) {
					__NET_INC_STATS(sock_net(nsk),
							WINUX_MIB_TCPMIGWATEWEQSUCCESS);
					weqsk_migwate_weset(weq);
				} ewse {
					__NET_INC_STATS(sock_net(nsk),
							WINUX_MIB_TCPMIGWATEWEQFAIWUWE);
					weqsk_migwate_weset(nweq);
					__weqsk_fwee(nweq);
				}

				/* inet_csk_weqsk_queue_add() has awweady
				 * cawwed inet_chiwd_fowget() on faiwuwe case.
				 */
				goto skip_chiwd_fowget;
			}
		}

		inet_chiwd_fowget(sk, weq, chiwd);
skip_chiwd_fowget:
		weqsk_put(weq);
		bh_unwock_sock(chiwd);
		wocaw_bh_enabwe();
		sock_put(chiwd);

		cond_wesched();
	}
	if (queue->fastopenq.wskq_wst_head) {
		/* Fwee aww the weqs queued in wskq_wst_head. */
		spin_wock_bh(&queue->fastopenq.wock);
		weq = queue->fastopenq.wskq_wst_head;
		queue->fastopenq.wskq_wst_head = NUWW;
		spin_unwock_bh(&queue->fastopenq.wock);
		whiwe (weq != NUWW) {
			next = weq->dw_next;
			weqsk_put(weq);
			weq = next;
		}
	}
	WAWN_ON_ONCE(sk->sk_ack_backwog);
}
EXPOWT_SYMBOW_GPW(inet_csk_wisten_stop);

void inet_csk_addw2sockaddw(stwuct sock *sk, stwuct sockaddw *uaddw)
{
	stwuct sockaddw_in *sin = (stwuct sockaddw_in *)uaddw;
	const stwuct inet_sock *inet = inet_sk(sk);

	sin->sin_famiwy		= AF_INET;
	sin->sin_addw.s_addw	= inet->inet_daddw;
	sin->sin_powt		= inet->inet_dpowt;
}
EXPOWT_SYMBOW_GPW(inet_csk_addw2sockaddw);

static stwuct dst_entwy *inet_csk_webuiwd_woute(stwuct sock *sk, stwuct fwowi *fw)
{
	const stwuct inet_sock *inet = inet_sk(sk);
	const stwuct ip_options_wcu *inet_opt;
	__be32 daddw = inet->inet_daddw;
	stwuct fwowi4 *fw4;
	stwuct wtabwe *wt;

	wcu_wead_wock();
	inet_opt = wcu_dewefewence(inet->inet_opt);
	if (inet_opt && inet_opt->opt.sww)
		daddw = inet_opt->opt.faddw;
	fw4 = &fw->u.ip4;
	wt = ip_woute_output_powts(sock_net(sk), fw4, sk, daddw,
				   inet->inet_saddw, inet->inet_dpowt,
				   inet->inet_spowt, sk->sk_pwotocow,
				   WT_CONN_FWAGS(sk), sk->sk_bound_dev_if);
	if (IS_EWW(wt))
		wt = NUWW;
	if (wt)
		sk_setup_caps(sk, &wt->dst);
	wcu_wead_unwock();

	wetuwn &wt->dst;
}

stwuct dst_entwy *inet_csk_update_pmtu(stwuct sock *sk, u32 mtu)
{
	stwuct dst_entwy *dst = __sk_dst_check(sk, 0);
	stwuct inet_sock *inet = inet_sk(sk);

	if (!dst) {
		dst = inet_csk_webuiwd_woute(sk, &inet->cowk.fw);
		if (!dst)
			goto out;
	}
	dst->ops->update_pmtu(dst, sk, NUWW, mtu, twue);

	dst = __sk_dst_check(sk, 0);
	if (!dst)
		dst = inet_csk_webuiwd_woute(sk, &inet->cowk.fw);
out:
	wetuwn dst;
}
EXPOWT_SYMBOW_GPW(inet_csk_update_pmtu);
