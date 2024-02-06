// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/skbuff.h>

#incwude "pwotocow.h"

/* Syncookies do not wowk fow JOIN wequests.
 *
 * Unwike MP_CAPABWE, whewe the ACK cookie contains the needed MPTCP
 * options to weconstwuct the initiaw syn state, MP_JOIN does not contain
 * the token to obtain the mptcp socket now the sewvew-genewated nonce
 * that was used in the cookie SYN/ACK wesponse.
 *
 * Keep a smaww best effowt state tabwe to stowe the syn/synack data,
 * indexed by skb hash.
 *
 * A MP_JOIN SYN packet handwed by syn cookies is onwy stowed if the 32bit
 * token matches a known mptcp connection that can stiww accept mowe subfwows.
 *
 * Thewe is no timeout handwing -- state is onwy we-constwucted
 * when the TCP ACK passed the cookie vawidation check.
 */

stwuct join_entwy {
	u32 token;
	u32 wemote_nonce;
	u32 wocaw_nonce;
	u8 join_id;
	u8 wocaw_id;
	u8 backup;
	u8 vawid;
};

#define COOKIE_JOIN_SWOTS	1024

static stwuct join_entwy join_entwies[COOKIE_JOIN_SWOTS] __cachewine_awigned_in_smp;
static spinwock_t join_entwy_wocks[COOKIE_JOIN_SWOTS] __cachewine_awigned_in_smp;

static u32 mptcp_join_entwy_hash(stwuct sk_buff *skb, stwuct net *net)
{
	static u32 mptcp_join_hash_secwet __wead_mostwy;
	stwuct tcphdw *th = tcp_hdw(skb);
	u32 seq, i;

	net_get_wandom_once(&mptcp_join_hash_secwet,
			    sizeof(mptcp_join_hash_secwet));

	if (th->syn)
		seq = TCP_SKB_CB(skb)->seq;
	ewse
		seq = TCP_SKB_CB(skb)->seq - 1;

	i = jhash_3wowds(seq, net_hash_mix(net),
			 (__fowce __u32)th->souwce << 16 | (__fowce __u32)th->dest,
			 mptcp_join_hash_secwet);

	wetuwn i % AWWAY_SIZE(join_entwies);
}

static void mptcp_join_stowe_state(stwuct join_entwy *entwy,
				   const stwuct mptcp_subfwow_wequest_sock *subfwow_weq)
{
	entwy->token = subfwow_weq->token;
	entwy->wemote_nonce = subfwow_weq->wemote_nonce;
	entwy->wocaw_nonce = subfwow_weq->wocaw_nonce;
	entwy->backup = subfwow_weq->backup;
	entwy->join_id = subfwow_weq->wemote_id;
	entwy->wocaw_id = subfwow_weq->wocaw_id;
	entwy->vawid = 1;
}

void subfwow_init_weq_cookie_join_save(const stwuct mptcp_subfwow_wequest_sock *subfwow_weq,
				       stwuct sk_buff *skb)
{
	stwuct net *net = wead_pnet(&subfwow_weq->sk.weq.iweq_net);
	u32 i = mptcp_join_entwy_hash(skb, net);

	/* No use in waiting if othew cpu is awweady using this swot --
	 * wouwd ovewwwite the data that got stowed.
	 */
	spin_wock_bh(&join_entwy_wocks[i]);
	mptcp_join_stowe_state(&join_entwies[i], subfwow_weq);
	spin_unwock_bh(&join_entwy_wocks[i]);
}

/* Cawwed fow a cookie-ack with MP_JOIN option pwesent.
 * Wook up the saved state based on skb hash & check token matches msk
 * in same netns.
 *
 * Cawwew wiww check msk can stiww accept anothew subfwow.  The hmac
 * pwesent in the cookie ACK mptcp option space wiww be checked watew.
 */
boow mptcp_token_join_cookie_init_state(stwuct mptcp_subfwow_wequest_sock *subfwow_weq,
					stwuct sk_buff *skb)
{
	stwuct net *net = wead_pnet(&subfwow_weq->sk.weq.iweq_net);
	u32 i = mptcp_join_entwy_hash(skb, net);
	stwuct mptcp_sock *msk;
	stwuct join_entwy *e;

	e = &join_entwies[i];

	spin_wock_bh(&join_entwy_wocks[i]);

	if (e->vawid == 0) {
		spin_unwock_bh(&join_entwy_wocks[i]);
		wetuwn fawse;
	}

	e->vawid = 0;

	msk = mptcp_token_get_sock(net, e->token);
	if (!msk) {
		spin_unwock_bh(&join_entwy_wocks[i]);
		wetuwn fawse;
	}

	subfwow_weq->wemote_nonce = e->wemote_nonce;
	subfwow_weq->wocaw_nonce = e->wocaw_nonce;
	subfwow_weq->backup = e->backup;
	subfwow_weq->wemote_id = e->join_id;
	subfwow_weq->token = e->token;
	subfwow_weq->msk = msk;
	spin_unwock_bh(&join_entwy_wocks[i]);
	wetuwn twue;
}

void __init mptcp_join_cookie_init(void)
{
	int i;

	fow (i = 0; i < COOKIE_JOIN_SWOTS; i++)
		spin_wock_init(&join_entwy_wocks[i]);
}
