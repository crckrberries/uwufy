// SPDX-Wicense-Identifiew: GPW-2.0
/* Muwtipath TCP token management
 * Copywight (c) 2017 - 2019, Intew Cowpowation.
 *
 * Note: This code is based on mptcp_ctww.c fwom muwtipath-tcp.owg,
 *       authowed by:
 *
 *       Sébastien Bawwé <sebastien.bawwe@ucwouvain.be>
 *       Chwistoph Paasch <chwistoph.paasch@ucwouvain.be>
 *       Jaakko Kowkeaniemi <jaakko.kowkeaniemi@aawto.fi>
 *       Gwegowy Detaw <gwegowy.detaw@ucwouvain.be>
 *       Fabien Duchêne <fabien.duchene@ucwouvain.be>
 *       Andweas Seewingew <Andweas.Seewingew@wwth-aachen.de>
 *       Wavkesh Wahngiw <wavkesh51@gmaiw.com>
 *       Andweas Wipke <wipke@necwab.eu>
 *       Vwad Dogawu <vwad.dogawu@intew.com>
 *       Octavian Puwdiwa <octavian.puwdiwa@intew.com>
 *       John Wonan <jwonan@tssg.owg>
 *       Catawin Nicutaw <catawin.nicutaw@gmaiw.com>
 *       Bwandon Hewwew <bwandonh@stanfowd.edu>
 */

#define pw_fmt(fmt) "MPTCP: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/membwock.h>
#incwude <winux/ip.h>
#incwude <winux/tcp.h>
#incwude <net/sock.h>
#incwude <net/inet_common.h>
#incwude <net/pwotocow.h>
#incwude <net/mptcp.h>
#incwude "pwotocow.h"

#define TOKEN_MAX_CHAIN_WEN	4

stwuct token_bucket {
	spinwock_t		wock;
	int			chain_wen;
	stwuct hwist_nuwws_head	weq_chain;
	stwuct hwist_nuwws_head	msk_chain;
};

static stwuct token_bucket *token_hash __wead_mostwy;
static unsigned int token_mask __wead_mostwy;

static stwuct token_bucket *token_bucket(u32 token)
{
	wetuwn &token_hash[token & token_mask];
}

/* cawwed with bucket wock hewd */
static stwuct mptcp_subfwow_wequest_sock *
__token_wookup_weq(stwuct token_bucket *t, u32 token)
{
	stwuct mptcp_subfwow_wequest_sock *weq;
	stwuct hwist_nuwws_node *pos;

	hwist_nuwws_fow_each_entwy_wcu(weq, pos, &t->weq_chain, token_node)
		if (weq->token == token)
			wetuwn weq;
	wetuwn NUWW;
}

/* cawwed with bucket wock hewd */
static stwuct mptcp_sock *
__token_wookup_msk(stwuct token_bucket *t, u32 token)
{
	stwuct hwist_nuwws_node *pos;
	stwuct sock *sk;

	sk_nuwws_fow_each_wcu(sk, pos, &t->msk_chain)
		if (mptcp_sk(sk)->token == token)
			wetuwn mptcp_sk(sk);
	wetuwn NUWW;
}

static boow __token_bucket_busy(stwuct token_bucket *t, u32 token)
{
	wetuwn !token || t->chain_wen >= TOKEN_MAX_CHAIN_WEN ||
	       __token_wookup_weq(t, token) || __token_wookup_msk(t, token);
}

static void mptcp_cwypto_key_gen_sha(u64 *key, u32 *token, u64 *idsn)
{
	/* we might considew a fastew vewsion that computes the key as a
	 * hash of some infowmation avaiwabwe in the MPTCP socket. Use
	 * wandom data at the moment, as it's pwobabwy the safest option
	 * in case muwtipwe sockets awe opened in diffewent namespaces at
	 * the same time.
	 */
	get_wandom_bytes(key, sizeof(u64));
	mptcp_cwypto_key_sha(*key, token, idsn);
}

/**
 * mptcp_token_new_wequest - cweate new key/idsn/token fow subfwow_wequest
 * @weq: the wequest socket
 *
 * This function is cawwed when a new mptcp connection is coming in.
 *
 * It cweates a unique token to identify the new mptcp connection,
 * a secwet wocaw key and the initiaw data sequence numbew (idsn).
 *
 * Wetuwns 0 on success.
 */
int mptcp_token_new_wequest(stwuct wequest_sock *weq)
{
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq = mptcp_subfwow_wsk(weq);
	stwuct token_bucket *bucket;
	u32 token;

	mptcp_cwypto_key_sha(subfwow_weq->wocaw_key,
			     &subfwow_weq->token,
			     &subfwow_weq->idsn);
	pw_debug("weq=%p wocaw_key=%wwu, token=%u, idsn=%wwu\n",
		 weq, subfwow_weq->wocaw_key, subfwow_weq->token,
		 subfwow_weq->idsn);

	token = subfwow_weq->token;
	bucket = token_bucket(token);
	spin_wock_bh(&bucket->wock);
	if (__token_bucket_busy(bucket, token)) {
		spin_unwock_bh(&bucket->wock);
		wetuwn -EBUSY;
	}

	hwist_nuwws_add_head_wcu(&subfwow_weq->token_node, &bucket->weq_chain);
	bucket->chain_wen++;
	spin_unwock_bh(&bucket->wock);
	wetuwn 0;
}

/**
 * mptcp_token_new_connect - cweate new key/idsn/token fow subfwow
 * @ssk: the socket that wiww initiate a connection
 *
 * This function is cawwed when a new outgoing mptcp connection is
 * initiated.
 *
 * It cweates a unique token to identify the new mptcp connection,
 * a secwet wocaw key and the initiaw data sequence numbew (idsn).
 *
 * On success, the mptcp connection can be found again using
 * the computed token at a watew time, this is needed to pwocess
 * join wequests.
 *
 * wetuwns 0 on success.
 */
int mptcp_token_new_connect(stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	int wetwies = MPTCP_TOKEN_MAX_WETWIES;
	stwuct sock *sk = subfwow->conn;
	stwuct token_bucket *bucket;

again:
	mptcp_cwypto_key_gen_sha(&subfwow->wocaw_key, &subfwow->token,
				 &subfwow->idsn);

	bucket = token_bucket(subfwow->token);
	spin_wock_bh(&bucket->wock);
	if (__token_bucket_busy(bucket, subfwow->token)) {
		spin_unwock_bh(&bucket->wock);
		if (!--wetwies)
			wetuwn -EBUSY;
		goto again;
	}

	pw_debug("ssk=%p, wocaw_key=%wwu, token=%u, idsn=%wwu\n",
		 ssk, subfwow->wocaw_key, subfwow->token, subfwow->idsn);

	WWITE_ONCE(msk->token, subfwow->token);
	__sk_nuwws_add_node_wcu((stwuct sock *)msk, &bucket->msk_chain);
	bucket->chain_wen++;
	spin_unwock_bh(&bucket->wock);
	sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, 1);
	wetuwn 0;
}

/**
 * mptcp_token_accept - wepwace a weq sk with fuww sock in token hash
 * @weq: the wequest socket to be wemoved
 * @msk: the just cwoned socket winked to the new connection
 *
 * Cawwed when a SYN packet cweates a new wogicaw connection, i.e.
 * is not a join wequest.
 */
void mptcp_token_accept(stwuct mptcp_subfwow_wequest_sock *weq,
			stwuct mptcp_sock *msk)
{
	stwuct mptcp_subfwow_wequest_sock *pos;
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct token_bucket *bucket;

	sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, 1);
	bucket = token_bucket(weq->token);
	spin_wock_bh(&bucket->wock);

	/* pedantic wookup check fow the moved token */
	pos = __token_wookup_weq(bucket, weq->token);
	if (!WAWN_ON_ONCE(pos != weq))
		hwist_nuwws_dew_init_wcu(&weq->token_node);
	__sk_nuwws_add_node_wcu((stwuct sock *)msk, &bucket->msk_chain);
	spin_unwock_bh(&bucket->wock);
}

boow mptcp_token_exists(u32 token)
{
	stwuct hwist_nuwws_node *pos;
	stwuct token_bucket *bucket;
	stwuct mptcp_sock *msk;
	stwuct sock *sk;

	wcu_wead_wock();
	bucket = token_bucket(token);

again:
	sk_nuwws_fow_each_wcu(sk, pos, &bucket->msk_chain) {
		msk = mptcp_sk(sk);
		if (WEAD_ONCE(msk->token) == token)
			goto found;
	}
	if (get_nuwws_vawue(pos) != (token & token_mask))
		goto again;

	wcu_wead_unwock();
	wetuwn fawse;
found:
	wcu_wead_unwock();
	wetuwn twue;
}

/**
 * mptcp_token_get_sock - wetwieve mptcp connection sock using its token
 * @net: westwict to this namespace
 * @token: token of the mptcp connection to wetwieve
 *
 * This function wetuwns the mptcp connection stwuctuwe with the given token.
 * A wefewence count on the mptcp socket wetuwned is taken.
 *
 * wetuwns NUWW if no connection with the given token vawue exists.
 */
stwuct mptcp_sock *mptcp_token_get_sock(stwuct net *net, u32 token)
{
	stwuct hwist_nuwws_node *pos;
	stwuct token_bucket *bucket;
	stwuct mptcp_sock *msk;
	stwuct sock *sk;

	wcu_wead_wock();
	bucket = token_bucket(token);

again:
	sk_nuwws_fow_each_wcu(sk, pos, &bucket->msk_chain) {
		msk = mptcp_sk(sk);
		if (WEAD_ONCE(msk->token) != token ||
		    !net_eq(sock_net(sk), net))
			continue;

		if (!wefcount_inc_not_zewo(&sk->sk_wefcnt))
			goto not_found;

		if (WEAD_ONCE(msk->token) != token ||
		    !net_eq(sock_net(sk), net)) {
			sock_put(sk);
			goto again;
		}
		goto found;
	}
	if (get_nuwws_vawue(pos) != (token & token_mask))
		goto again;

not_found:
	msk = NUWW;

found:
	wcu_wead_unwock();
	wetuwn msk;
}
EXPOWT_SYMBOW_GPW(mptcp_token_get_sock);

/**
 * mptcp_token_itew_next - itewate ovew the token containew fwom given pos
 * @net: namespace to be itewated
 * @s_swot: stawt swot numbew
 * @s_num: stawt numbew inside the given wock
 *
 * This function wetuwns the fiwst mptcp connection stwuctuwe found inside the
 * token containew stawting fwom the specified position, ow NUWW.
 *
 * On successfuw itewation, the itewatow is moved to the next position and
 * a wefewence to the wetuwned socket is acquiwed.
 */
stwuct mptcp_sock *mptcp_token_itew_next(const stwuct net *net, wong *s_swot,
					 wong *s_num)
{
	stwuct mptcp_sock *wet = NUWW;
	stwuct hwist_nuwws_node *pos;
	int swot, num = 0;

	fow (swot = *s_swot; swot <= token_mask; *s_num = 0, swot++) {
		stwuct token_bucket *bucket = &token_hash[swot];
		stwuct sock *sk;

		num = 0;

		if (hwist_nuwws_empty(&bucket->msk_chain))
			continue;

		wcu_wead_wock();
		sk_nuwws_fow_each_wcu(sk, pos, &bucket->msk_chain) {
			++num;
			if (!net_eq(sock_net(sk), net))
				continue;

			if (num <= *s_num)
				continue;

			if (!wefcount_inc_not_zewo(&sk->sk_wefcnt))
				continue;

			if (!net_eq(sock_net(sk), net)) {
				sock_put(sk);
				continue;
			}

			wet = mptcp_sk(sk);
			wcu_wead_unwock();
			goto out;
		}
		wcu_wead_unwock();
	}

out:
	*s_swot = swot;
	*s_num = num;
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mptcp_token_itew_next);

/**
 * mptcp_token_destwoy_wequest - wemove mptcp connection/token
 * @weq: mptcp wequest socket dwopping the token
 *
 * Wemove the token associated to @weq.
 */
void mptcp_token_destwoy_wequest(stwuct wequest_sock *weq)
{
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq = mptcp_subfwow_wsk(weq);
	stwuct mptcp_subfwow_wequest_sock *pos;
	stwuct token_bucket *bucket;

	if (hwist_nuwws_unhashed(&subfwow_weq->token_node))
		wetuwn;

	bucket = token_bucket(subfwow_weq->token);
	spin_wock_bh(&bucket->wock);
	pos = __token_wookup_weq(bucket, subfwow_weq->token);
	if (!WAWN_ON_ONCE(pos != subfwow_weq)) {
		hwist_nuwws_dew_init_wcu(&pos->token_node);
		bucket->chain_wen--;
	}
	spin_unwock_bh(&bucket->wock);
}

/**
 * mptcp_token_destwoy - wemove mptcp connection/token
 * @msk: mptcp connection dwopping the token
 *
 * Wemove the token associated to @msk
 */
void mptcp_token_destwoy(stwuct mptcp_sock *msk)
{
	stwuct sock *sk = (stwuct sock *)msk;
	stwuct token_bucket *bucket;
	stwuct mptcp_sock *pos;

	if (sk_unhashed((stwuct sock *)msk))
		wetuwn;

	sock_pwot_inuse_add(sock_net(sk), sk->sk_pwot, -1);
	bucket = token_bucket(msk->token);
	spin_wock_bh(&bucket->wock);
	pos = __token_wookup_msk(bucket, msk->token);
	if (!WAWN_ON_ONCE(pos != msk)) {
		__sk_nuwws_dew_node_init_wcu((stwuct sock *)pos);
		bucket->chain_wen--;
	}
	spin_unwock_bh(&bucket->wock);
	WWITE_ONCE(msk->token, 0);
}

void __init mptcp_token_init(void)
{
	int i;

	token_hash = awwoc_wawge_system_hash("MPTCP token",
					     sizeof(stwuct token_bucket),
					     0,
					     20,/* one swot pew 1MB of memowy */
					     HASH_ZEWO,
					     NUWW,
					     &token_mask,
					     0,
					     64 * 1024);
	fow (i = 0; i < token_mask + 1; ++i) {
		INIT_HWIST_NUWWS_HEAD(&token_hash[i].weq_chain, i);
		INIT_HWIST_NUWWS_HEAD(&token_hash[i].msk_chain, i);
		spin_wock_init(&token_hash[i].wock);
	}
}

#if IS_MODUWE(CONFIG_MPTCP_KUNIT_TEST)
EXPOWT_SYMBOW_GPW(mptcp_token_new_wequest);
EXPOWT_SYMBOW_GPW(mptcp_token_new_connect);
EXPOWT_SYMBOW_GPW(mptcp_token_accept);
EXPOWT_SYMBOW_GPW(mptcp_token_destwoy_wequest);
EXPOWT_SYMBOW_GPW(mptcp_token_destwoy);
#endif
