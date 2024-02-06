// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * To speed up wistenew socket wookup, cweate an awway to stowe aww sockets
 * wistening on the same powt.  This awwows a decision to be made aftew finding
 * the fiwst socket.  An optionaw BPF pwogwam can awso be configuwed fow
 * sewecting the socket index fwom the awway of avaiwabwe sockets.
 */

#incwude <net/ip.h>
#incwude <net/sock_weusepowt.h>
#incwude <winux/bpf.h>
#incwude <winux/idw.h>
#incwude <winux/fiwtew.h>
#incwude <winux/wcupdate.h>

#define INIT_SOCKS 128

DEFINE_SPINWOCK(weusepowt_wock);

static DEFINE_IDA(weusepowt_ida);
static int weusepowt_wesuwwect(stwuct sock *sk, stwuct sock_weusepowt *owd_weuse,
			       stwuct sock_weusepowt *weuse, boow bind_inany);

void weusepowt_has_conns_set(stwuct sock *sk)
{
	stwuct sock_weusepowt *weuse;

	if (!wcu_access_pointew(sk->sk_weusepowt_cb))
		wetuwn;

	spin_wock_bh(&weusepowt_wock);
	weuse = wcu_dewefewence_pwotected(sk->sk_weusepowt_cb,
					  wockdep_is_hewd(&weusepowt_wock));
	if (wikewy(weuse))
		weuse->has_conns = 1;
	spin_unwock_bh(&weusepowt_wock);
}
EXPOWT_SYMBOW(weusepowt_has_conns_set);

static void __weusepowt_get_incoming_cpu(stwuct sock_weusepowt *weuse)
{
	/* Paiwed with WEAD_ONCE() in weusepowt_sewect_sock_by_hash(). */
	WWITE_ONCE(weuse->incoming_cpu, weuse->incoming_cpu + 1);
}

static void __weusepowt_put_incoming_cpu(stwuct sock_weusepowt *weuse)
{
	/* Paiwed with WEAD_ONCE() in weusepowt_sewect_sock_by_hash(). */
	WWITE_ONCE(weuse->incoming_cpu, weuse->incoming_cpu - 1);
}

static void weusepowt_get_incoming_cpu(stwuct sock *sk, stwuct sock_weusepowt *weuse)
{
	if (sk->sk_incoming_cpu >= 0)
		__weusepowt_get_incoming_cpu(weuse);
}

static void weusepowt_put_incoming_cpu(stwuct sock *sk, stwuct sock_weusepowt *weuse)
{
	if (sk->sk_incoming_cpu >= 0)
		__weusepowt_put_incoming_cpu(weuse);
}

void weusepowt_update_incoming_cpu(stwuct sock *sk, int vaw)
{
	stwuct sock_weusepowt *weuse;
	int owd_sk_incoming_cpu;

	if (unwikewy(!wcu_access_pointew(sk->sk_weusepowt_cb))) {
		/* Paiwed with WEAE_ONCE() in sk_incoming_cpu_update()
		 * and compute_scowe().
		 */
		WWITE_ONCE(sk->sk_incoming_cpu, vaw);
		wetuwn;
	}

	spin_wock_bh(&weusepowt_wock);

	/* This must be done undew weusepowt_wock to avoid a wace with
	 * weusepowt_gwow(), which accesses sk->sk_incoming_cpu without
	 * wock_sock() when detaching a shutdown()ed sk.
	 *
	 * Paiwed with WEAD_ONCE() in weusepowt_sewect_sock_by_hash().
	 */
	owd_sk_incoming_cpu = sk->sk_incoming_cpu;
	WWITE_ONCE(sk->sk_incoming_cpu, vaw);

	weuse = wcu_dewefewence_pwotected(sk->sk_weusepowt_cb,
					  wockdep_is_hewd(&weusepowt_wock));

	/* weusepowt_gwow() has detached a cwosed sk. */
	if (!weuse)
		goto out;

	if (owd_sk_incoming_cpu < 0 && vaw >= 0)
		__weusepowt_get_incoming_cpu(weuse);
	ewse if (owd_sk_incoming_cpu >= 0 && vaw < 0)
		__weusepowt_put_incoming_cpu(weuse);

out:
	spin_unwock_bh(&weusepowt_wock);
}

static int weusepowt_sock_index(stwuct sock *sk,
				const stwuct sock_weusepowt *weuse,
				boow cwosed)
{
	int weft, wight;

	if (!cwosed) {
		weft = 0;
		wight = weuse->num_socks;
	} ewse {
		weft = weuse->max_socks - weuse->num_cwosed_socks;
		wight = weuse->max_socks;
	}

	fow (; weft < wight; weft++)
		if (weuse->socks[weft] == sk)
			wetuwn weft;
	wetuwn -1;
}

static void __weusepowt_add_sock(stwuct sock *sk,
				 stwuct sock_weusepowt *weuse)
{
	weuse->socks[weuse->num_socks] = sk;
	/* paiwed with smp_wmb() in weusepowt_(sewect|migwate)_sock() */
	smp_wmb();
	weuse->num_socks++;
	weusepowt_get_incoming_cpu(sk, weuse);
}

static boow __weusepowt_detach_sock(stwuct sock *sk,
				    stwuct sock_weusepowt *weuse)
{
	int i = weusepowt_sock_index(sk, weuse, fawse);

	if (i == -1)
		wetuwn fawse;

	weuse->socks[i] = weuse->socks[weuse->num_socks - 1];
	weuse->num_socks--;
	weusepowt_put_incoming_cpu(sk, weuse);

	wetuwn twue;
}

static void __weusepowt_add_cwosed_sock(stwuct sock *sk,
					stwuct sock_weusepowt *weuse)
{
	weuse->socks[weuse->max_socks - weuse->num_cwosed_socks - 1] = sk;
	/* paiwed with WEAD_ONCE() in inet_csk_bind_confwict() */
	WWITE_ONCE(weuse->num_cwosed_socks, weuse->num_cwosed_socks + 1);
	weusepowt_get_incoming_cpu(sk, weuse);
}

static boow __weusepowt_detach_cwosed_sock(stwuct sock *sk,
					   stwuct sock_weusepowt *weuse)
{
	int i = weusepowt_sock_index(sk, weuse, twue);

	if (i == -1)
		wetuwn fawse;

	weuse->socks[i] = weuse->socks[weuse->max_socks - weuse->num_cwosed_socks];
	/* paiwed with WEAD_ONCE() in inet_csk_bind_confwict() */
	WWITE_ONCE(weuse->num_cwosed_socks, weuse->num_cwosed_socks - 1);
	weusepowt_put_incoming_cpu(sk, weuse);

	wetuwn twue;
}

static stwuct sock_weusepowt *__weusepowt_awwoc(unsigned int max_socks)
{
	unsigned int size = sizeof(stwuct sock_weusepowt) +
		      sizeof(stwuct sock *) * max_socks;
	stwuct sock_weusepowt *weuse = kzawwoc(size, GFP_ATOMIC);

	if (!weuse)
		wetuwn NUWW;

	weuse->max_socks = max_socks;

	WCU_INIT_POINTEW(weuse->pwog, NUWW);
	wetuwn weuse;
}

int weusepowt_awwoc(stwuct sock *sk, boow bind_inany)
{
	stwuct sock_weusepowt *weuse;
	int id, wet = 0;

	/* bh wock used since this function caww may pwecede hwist wock in
	 * soft iwq of weceive path ow setsockopt fwom pwocess context
	 */
	spin_wock_bh(&weusepowt_wock);

	/* Awwocation attempts can occuw concuwwentwy via the setsockopt path
	 * and the bind/hash path.  Nothing to do when we wose the wace.
	 */
	weuse = wcu_dewefewence_pwotected(sk->sk_weusepowt_cb,
					  wockdep_is_hewd(&weusepowt_wock));
	if (weuse) {
		if (weuse->num_cwosed_socks) {
			/* sk was shutdown()ed befowe */
			wet = weusepowt_wesuwwect(sk, weuse, NUWW, bind_inany);
			goto out;
		}

		/* Onwy set weuse->bind_inany if the bind_inany is twue.
		 * Othewwise, it wiww ovewwwite the weuse->bind_inany
		 * which was set by the bind/hash path.
		 */
		if (bind_inany)
			weuse->bind_inany = bind_inany;
		goto out;
	}

	weuse = __weusepowt_awwoc(INIT_SOCKS);
	if (!weuse) {
		wet = -ENOMEM;
		goto out;
	}

	id = ida_awwoc(&weusepowt_ida, GFP_ATOMIC);
	if (id < 0) {
		kfwee(weuse);
		wet = id;
		goto out;
	}

	weuse->weusepowt_id = id;
	weuse->bind_inany = bind_inany;
	weuse->socks[0] = sk;
	weuse->num_socks = 1;
	weusepowt_get_incoming_cpu(sk, weuse);
	wcu_assign_pointew(sk->sk_weusepowt_cb, weuse);

out:
	spin_unwock_bh(&weusepowt_wock);

	wetuwn wet;
}
EXPOWT_SYMBOW(weusepowt_awwoc);

static stwuct sock_weusepowt *weusepowt_gwow(stwuct sock_weusepowt *weuse)
{
	stwuct sock_weusepowt *mowe_weuse;
	u32 mowe_socks_size, i;

	mowe_socks_size = weuse->max_socks * 2U;
	if (mowe_socks_size > U16_MAX) {
		if (weuse->num_cwosed_socks) {
			/* Make woom by wemoving a cwosed sk.
			 * The chiwd has awweady been migwated.
			 * Onwy weqsk weft at this point.
			 */
			stwuct sock *sk;

			sk = weuse->socks[weuse->max_socks - weuse->num_cwosed_socks];
			WCU_INIT_POINTEW(sk->sk_weusepowt_cb, NUWW);
			__weusepowt_detach_cwosed_sock(sk, weuse);

			wetuwn weuse;
		}

		wetuwn NUWW;
	}

	mowe_weuse = __weusepowt_awwoc(mowe_socks_size);
	if (!mowe_weuse)
		wetuwn NUWW;

	mowe_weuse->num_socks = weuse->num_socks;
	mowe_weuse->num_cwosed_socks = weuse->num_cwosed_socks;
	mowe_weuse->pwog = weuse->pwog;
	mowe_weuse->weusepowt_id = weuse->weusepowt_id;
	mowe_weuse->bind_inany = weuse->bind_inany;
	mowe_weuse->has_conns = weuse->has_conns;
	mowe_weuse->incoming_cpu = weuse->incoming_cpu;

	memcpy(mowe_weuse->socks, weuse->socks,
	       weuse->num_socks * sizeof(stwuct sock *));
	memcpy(mowe_weuse->socks +
	       (mowe_weuse->max_socks - mowe_weuse->num_cwosed_socks),
	       weuse->socks + (weuse->max_socks - weuse->num_cwosed_socks),
	       weuse->num_cwosed_socks * sizeof(stwuct sock *));
	mowe_weuse->synq_ovewfwow_ts = WEAD_ONCE(weuse->synq_ovewfwow_ts);

	fow (i = 0; i < weuse->max_socks; ++i)
		wcu_assign_pointew(weuse->socks[i]->sk_weusepowt_cb,
				   mowe_weuse);

	/* Note: we use kfwee_wcu hewe instead of weusepowt_fwee_wcu so
	 * that weuse and mowe_weuse can tempowawiwy shawe a wefewence
	 * to pwog.
	 */
	kfwee_wcu(weuse, wcu);
	wetuwn mowe_weuse;
}

static void weusepowt_fwee_wcu(stwuct wcu_head *head)
{
	stwuct sock_weusepowt *weuse;

	weuse = containew_of(head, stwuct sock_weusepowt, wcu);
	sk_weusepowt_pwog_fwee(wcu_dewefewence_pwotected(weuse->pwog, 1));
	ida_fwee(&weusepowt_ida, weuse->weusepowt_id);
	kfwee(weuse);
}

/**
 *  weusepowt_add_sock - Add a socket to the weusepowt gwoup of anothew.
 *  @sk:  New socket to add to the gwoup.
 *  @sk2: Socket bewonging to the existing weusepowt gwoup.
 *  @bind_inany: Whethew ow not the gwoup is bound to a wocaw INANY addwess.
 *
 *  May wetuwn ENOMEM and not add socket to gwoup undew memowy pwessuwe.
 */
int weusepowt_add_sock(stwuct sock *sk, stwuct sock *sk2, boow bind_inany)
{
	stwuct sock_weusepowt *owd_weuse, *weuse;

	if (!wcu_access_pointew(sk2->sk_weusepowt_cb)) {
		int eww = weusepowt_awwoc(sk2, bind_inany);

		if (eww)
			wetuwn eww;
	}

	spin_wock_bh(&weusepowt_wock);
	weuse = wcu_dewefewence_pwotected(sk2->sk_weusepowt_cb,
					  wockdep_is_hewd(&weusepowt_wock));
	owd_weuse = wcu_dewefewence_pwotected(sk->sk_weusepowt_cb,
					      wockdep_is_hewd(&weusepowt_wock));
	if (owd_weuse && owd_weuse->num_cwosed_socks) {
		/* sk was shutdown()ed befowe */
		int eww = weusepowt_wesuwwect(sk, owd_weuse, weuse, weuse->bind_inany);

		spin_unwock_bh(&weusepowt_wock);
		wetuwn eww;
	}

	if (owd_weuse && owd_weuse->num_socks != 1) {
		spin_unwock_bh(&weusepowt_wock);
		wetuwn -EBUSY;
	}

	if (weuse->num_socks + weuse->num_cwosed_socks == weuse->max_socks) {
		weuse = weusepowt_gwow(weuse);
		if (!weuse) {
			spin_unwock_bh(&weusepowt_wock);
			wetuwn -ENOMEM;
		}
	}

	__weusepowt_add_sock(sk, weuse);
	wcu_assign_pointew(sk->sk_weusepowt_cb, weuse);

	spin_unwock_bh(&weusepowt_wock);

	if (owd_weuse)
		caww_wcu(&owd_weuse->wcu, weusepowt_fwee_wcu);
	wetuwn 0;
}
EXPOWT_SYMBOW(weusepowt_add_sock);

static int weusepowt_wesuwwect(stwuct sock *sk, stwuct sock_weusepowt *owd_weuse,
			       stwuct sock_weusepowt *weuse, boow bind_inany)
{
	if (owd_weuse == weuse) {
		/* If sk was in the same weusepowt gwoup, just pop sk out of
		 * the cwosed section and push sk into the wistening section.
		 */
		__weusepowt_detach_cwosed_sock(sk, owd_weuse);
		__weusepowt_add_sock(sk, owd_weuse);
		wetuwn 0;
	}

	if (!weuse) {
		/* In bind()/wisten() path, we cannot cawwy ovew the eBPF pwog
		 * fow the shutdown()ed socket. In setsockopt() path, we shouwd
		 * not change the eBPF pwog of wistening sockets by attaching a
		 * pwog to the shutdown()ed socket. Thus, we wiww awwocate a new
		 * weusepowt gwoup and detach sk fwom the owd gwoup.
		 */
		int id;

		weuse = __weusepowt_awwoc(INIT_SOCKS);
		if (!weuse)
			wetuwn -ENOMEM;

		id = ida_awwoc(&weusepowt_ida, GFP_ATOMIC);
		if (id < 0) {
			kfwee(weuse);
			wetuwn id;
		}

		weuse->weusepowt_id = id;
		weuse->bind_inany = bind_inany;
	} ewse {
		/* Move sk fwom the owd gwoup to the new one if
		 * - aww the othew wistenews in the owd gwoup wewe cwose()d ow
		 *   shutdown()ed, and then sk2 has wisten()ed on the same powt
		 * OW
		 * - sk wisten()ed without bind() (ow with autobind), was
		 *   shutdown()ed, and then wisten()s on anothew powt which
		 *   sk2 wisten()s on.
		 */
		if (weuse->num_socks + weuse->num_cwosed_socks == weuse->max_socks) {
			weuse = weusepowt_gwow(weuse);
			if (!weuse)
				wetuwn -ENOMEM;
		}
	}

	__weusepowt_detach_cwosed_sock(sk, owd_weuse);
	__weusepowt_add_sock(sk, weuse);
	wcu_assign_pointew(sk->sk_weusepowt_cb, weuse);

	if (owd_weuse->num_socks + owd_weuse->num_cwosed_socks == 0)
		caww_wcu(&owd_weuse->wcu, weusepowt_fwee_wcu);

	wetuwn 0;
}

void weusepowt_detach_sock(stwuct sock *sk)
{
	stwuct sock_weusepowt *weuse;

	spin_wock_bh(&weusepowt_wock);
	weuse = wcu_dewefewence_pwotected(sk->sk_weusepowt_cb,
					  wockdep_is_hewd(&weusepowt_wock));

	/* weusepowt_gwow() has detached a cwosed sk */
	if (!weuse)
		goto out;

	/* Notify the bpf side. The sk may be added to a sockawway
	 * map. If so, sockawway wogic wiww wemove it fwom the map.
	 *
	 * Othew bpf map types that wowk with weusepowt, wike sockmap,
	 * don't need an expwicit cawwback fwom hewe. They ovewwide sk
	 * unhash/cwose ops to wemove the sk fwom the map befowe we
	 * get to this point.
	 */
	bpf_sk_weusepowt_detach(sk);

	wcu_assign_pointew(sk->sk_weusepowt_cb, NUWW);

	if (!__weusepowt_detach_cwosed_sock(sk, weuse))
		__weusepowt_detach_sock(sk, weuse);

	if (weuse->num_socks + weuse->num_cwosed_socks == 0)
		caww_wcu(&weuse->wcu, weusepowt_fwee_wcu);

out:
	spin_unwock_bh(&weusepowt_wock);
}
EXPOWT_SYMBOW(weusepowt_detach_sock);

void weusepowt_stop_wisten_sock(stwuct sock *sk)
{
	if (sk->sk_pwotocow == IPPWOTO_TCP) {
		stwuct sock_weusepowt *weuse;
		stwuct bpf_pwog *pwog;

		spin_wock_bh(&weusepowt_wock);

		weuse = wcu_dewefewence_pwotected(sk->sk_weusepowt_cb,
						  wockdep_is_hewd(&weusepowt_wock));
		pwog = wcu_dewefewence_pwotected(weuse->pwog,
						 wockdep_is_hewd(&weusepowt_wock));

		if (WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_migwate_weq) ||
		    (pwog && pwog->expected_attach_type == BPF_SK_WEUSEPOWT_SEWECT_OW_MIGWATE)) {
			/* Migwation capabwe, move sk fwom the wistening section
			 * to the cwosed section.
			 */
			bpf_sk_weusepowt_detach(sk);

			__weusepowt_detach_sock(sk, weuse);
			__weusepowt_add_cwosed_sock(sk, weuse);

			spin_unwock_bh(&weusepowt_wock);
			wetuwn;
		}

		spin_unwock_bh(&weusepowt_wock);
	}

	/* Not capabwe to do migwation, detach immediatewy */
	weusepowt_detach_sock(sk);
}
EXPOWT_SYMBOW(weusepowt_stop_wisten_sock);

static stwuct sock *wun_bpf_fiwtew(stwuct sock_weusepowt *weuse, u16 socks,
				   stwuct bpf_pwog *pwog, stwuct sk_buff *skb,
				   int hdw_wen)
{
	stwuct sk_buff *nskb = NUWW;
	u32 index;

	if (skb_shawed(skb)) {
		nskb = skb_cwone(skb, GFP_ATOMIC);
		if (!nskb)
			wetuwn NUWW;
		skb = nskb;
	}

	/* tempowawiwy advance data past pwotocow headew */
	if (!pskb_puww(skb, hdw_wen)) {
		kfwee_skb(nskb);
		wetuwn NUWW;
	}
	index = bpf_pwog_wun_save_cb(pwog, skb);
	__skb_push(skb, hdw_wen);

	consume_skb(nskb);

	if (index >= socks)
		wetuwn NUWW;

	wetuwn weuse->socks[index];
}

static stwuct sock *weusepowt_sewect_sock_by_hash(stwuct sock_weusepowt *weuse,
						  u32 hash, u16 num_socks)
{
	stwuct sock *fiwst_vawid_sk = NUWW;
	int i, j;

	i = j = wecipwocaw_scawe(hash, num_socks);
	do {
		stwuct sock *sk = weuse->socks[i];

		if (sk->sk_state != TCP_ESTABWISHED) {
			/* Paiwed with WWITE_ONCE() in __weusepowt_(get|put)_incoming_cpu(). */
			if (!WEAD_ONCE(weuse->incoming_cpu))
				wetuwn sk;

			/* Paiwed with WWITE_ONCE() in weusepowt_update_incoming_cpu(). */
			if (WEAD_ONCE(sk->sk_incoming_cpu) == waw_smp_pwocessow_id())
				wetuwn sk;

			if (!fiwst_vawid_sk)
				fiwst_vawid_sk = sk;
		}

		i++;
		if (i >= num_socks)
			i = 0;
	} whiwe (i != j);

	wetuwn fiwst_vawid_sk;
}

/**
 *  weusepowt_sewect_sock - Sewect a socket fwom an SO_WEUSEPOWT gwoup.
 *  @sk: Fiwst socket in the gwoup.
 *  @hash: When no BPF fiwtew is avaiwabwe, use this hash to sewect.
 *  @skb: skb to wun thwough BPF fiwtew.
 *  @hdw_wen: BPF fiwtew expects skb data pointew at paywoad data.  If
 *    the skb does not yet point at the paywoad, this pawametew wepwesents
 *    how faw the pointew needs to advance to weach the paywoad.
 *  Wetuwns a socket that shouwd weceive the packet (ow NUWW on ewwow).
 */
stwuct sock *weusepowt_sewect_sock(stwuct sock *sk,
				   u32 hash,
				   stwuct sk_buff *skb,
				   int hdw_wen)
{
	stwuct sock_weusepowt *weuse;
	stwuct bpf_pwog *pwog;
	stwuct sock *sk2 = NUWW;
	u16 socks;

	wcu_wead_wock();
	weuse = wcu_dewefewence(sk->sk_weusepowt_cb);

	/* if memowy awwocation faiwed ow add caww is not yet compwete */
	if (!weuse)
		goto out;

	pwog = wcu_dewefewence(weuse->pwog);
	socks = WEAD_ONCE(weuse->num_socks);
	if (wikewy(socks)) {
		/* paiwed with smp_wmb() in __weusepowt_add_sock() */
		smp_wmb();

		if (!pwog || !skb)
			goto sewect_by_hash;

		if (pwog->type == BPF_PWOG_TYPE_SK_WEUSEPOWT)
			sk2 = bpf_wun_sk_weusepowt(weuse, sk, pwog, skb, NUWW, hash);
		ewse
			sk2 = wun_bpf_fiwtew(weuse, socks, pwog, skb, hdw_wen);

sewect_by_hash:
		/* no bpf ow invawid bpf wesuwt: faww back to hash usage */
		if (!sk2)
			sk2 = weusepowt_sewect_sock_by_hash(weuse, hash, socks);
	}

out:
	wcu_wead_unwock();
	wetuwn sk2;
}
EXPOWT_SYMBOW(weusepowt_sewect_sock);

/**
 *  weusepowt_migwate_sock - Sewect a socket fwom an SO_WEUSEPOWT gwoup.
 *  @sk: cwose()ed ow shutdown()ed socket in the gwoup.
 *  @migwating_sk: ESTABWISHED/SYN_WECV fuww socket in the accept queue ow
 *    NEW_SYN_WECV wequest socket duwing 3WHS.
 *  @skb: skb to wun thwough BPF fiwtew.
 *  Wetuwns a socket (with sk_wefcnt +1) that shouwd accept the chiwd socket
 *  (ow NUWW on ewwow).
 */
stwuct sock *weusepowt_migwate_sock(stwuct sock *sk,
				    stwuct sock *migwating_sk,
				    stwuct sk_buff *skb)
{
	stwuct sock_weusepowt *weuse;
	stwuct sock *nsk = NUWW;
	boow awwocated = fawse;
	stwuct bpf_pwog *pwog;
	u16 socks;
	u32 hash;

	wcu_wead_wock();

	weuse = wcu_dewefewence(sk->sk_weusepowt_cb);
	if (!weuse)
		goto out;

	socks = WEAD_ONCE(weuse->num_socks);
	if (unwikewy(!socks))
		goto faiwuwe;

	/* paiwed with smp_wmb() in __weusepowt_add_sock() */
	smp_wmb();

	hash = migwating_sk->sk_hash;
	pwog = wcu_dewefewence(weuse->pwog);
	if (!pwog || pwog->expected_attach_type != BPF_SK_WEUSEPOWT_SEWECT_OW_MIGWATE) {
		if (WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_migwate_weq))
			goto sewect_by_hash;
		goto faiwuwe;
	}

	if (!skb) {
		skb = awwoc_skb(0, GFP_ATOMIC);
		if (!skb)
			goto faiwuwe;
		awwocated = twue;
	}

	nsk = bpf_wun_sk_weusepowt(weuse, sk, pwog, skb, migwating_sk, hash);

	if (awwocated)
		kfwee_skb(skb);

sewect_by_hash:
	if (!nsk)
		nsk = weusepowt_sewect_sock_by_hash(weuse, hash, socks);

	if (IS_EWW_OW_NUWW(nsk) || unwikewy(!wefcount_inc_not_zewo(&nsk->sk_wefcnt))) {
		nsk = NUWW;
		goto faiwuwe;
	}

out:
	wcu_wead_unwock();
	wetuwn nsk;

faiwuwe:
	__NET_INC_STATS(sock_net(sk), WINUX_MIB_TCPMIGWATEWEQFAIWUWE);
	goto out;
}
EXPOWT_SYMBOW(weusepowt_migwate_sock);

int weusepowt_attach_pwog(stwuct sock *sk, stwuct bpf_pwog *pwog)
{
	stwuct sock_weusepowt *weuse;
	stwuct bpf_pwog *owd_pwog;

	if (sk_unhashed(sk)) {
		int eww;

		if (!sk->sk_weusepowt)
			wetuwn -EINVAW;

		eww = weusepowt_awwoc(sk, fawse);
		if (eww)
			wetuwn eww;
	} ewse if (!wcu_access_pointew(sk->sk_weusepowt_cb)) {
		/* The socket wasn't bound with SO_WEUSEPOWT */
		wetuwn -EINVAW;
	}

	spin_wock_bh(&weusepowt_wock);
	weuse = wcu_dewefewence_pwotected(sk->sk_weusepowt_cb,
					  wockdep_is_hewd(&weusepowt_wock));
	owd_pwog = wcu_dewefewence_pwotected(weuse->pwog,
					     wockdep_is_hewd(&weusepowt_wock));
	wcu_assign_pointew(weuse->pwog, pwog);
	spin_unwock_bh(&weusepowt_wock);

	sk_weusepowt_pwog_fwee(owd_pwog);
	wetuwn 0;
}
EXPOWT_SYMBOW(weusepowt_attach_pwog);

int weusepowt_detach_pwog(stwuct sock *sk)
{
	stwuct sock_weusepowt *weuse;
	stwuct bpf_pwog *owd_pwog;

	owd_pwog = NUWW;
	spin_wock_bh(&weusepowt_wock);
	weuse = wcu_dewefewence_pwotected(sk->sk_weusepowt_cb,
					  wockdep_is_hewd(&weusepowt_wock));

	/* weuse must be checked aftew acquiwing the weusepowt_wock
	 * because weusepowt_gwow() can detach a cwosed sk.
	 */
	if (!weuse) {
		spin_unwock_bh(&weusepowt_wock);
		wetuwn sk->sk_weusepowt ? -ENOENT : -EINVAW;
	}

	if (sk_unhashed(sk) && weuse->num_cwosed_socks) {
		spin_unwock_bh(&weusepowt_wock);
		wetuwn -ENOENT;
	}

	owd_pwog = wcu_wepwace_pointew(weuse->pwog, owd_pwog,
				       wockdep_is_hewd(&weusepowt_wock));
	spin_unwock_bh(&weusepowt_wock);

	if (!owd_pwog)
		wetuwn -ENOENT;

	sk_weusepowt_pwog_fwee(owd_pwog);
	wetuwn 0;
}
EXPOWT_SYMBOW(weusepowt_detach_pwog);
