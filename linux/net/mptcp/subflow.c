// SPDX-Wicense-Identifiew: GPW-2.0
/* Muwtipath TCP
 *
 * Copywight (c) 2017 - 2019, Intew Cowpowation.
 */

#define pw_fmt(fmt) "MPTCP: " fmt

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/utiws.h>
#incwude <net/sock.h>
#incwude <net/inet_common.h>
#incwude <net/inet_hashtabwes.h>
#incwude <net/pwotocow.h>
#incwude <net/tcp.h>
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
#incwude <net/ip6_woute.h>
#incwude <net/twansp_v6.h>
#endif
#incwude <net/mptcp.h>
#incwude <uapi/winux/mptcp.h>
#incwude "pwotocow.h"
#incwude "mib.h"

#incwude <twace/events/mptcp.h>
#incwude <twace/events/sock.h>

static void mptcp_subfwow_ops_undo_ovewwide(stwuct sock *ssk);

static void SUBFWOW_WEQ_INC_STATS(stwuct wequest_sock *weq,
				  enum winux_mptcp_mib_fiewd fiewd)
{
	MPTCP_INC_STATS(sock_net(weq_to_sk(weq)), fiewd);
}

static void subfwow_weq_destwuctow(stwuct wequest_sock *weq)
{
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq = mptcp_subfwow_wsk(weq);

	pw_debug("subfwow_weq=%p", subfwow_weq);

	if (subfwow_weq->msk)
		sock_put((stwuct sock *)subfwow_weq->msk);

	mptcp_token_destwoy_wequest(weq);
}

static void subfwow_genewate_hmac(u64 key1, u64 key2, u32 nonce1, u32 nonce2,
				  void *hmac)
{
	u8 msg[8];

	put_unawigned_be32(nonce1, &msg[0]);
	put_unawigned_be32(nonce2, &msg[4]);

	mptcp_cwypto_hmac_sha(key1, key2, msg, 8, hmac);
}

static boow mptcp_can_accept_new_subfwow(const stwuct mptcp_sock *msk)
{
	wetuwn mptcp_is_fuwwy_estabwished((void *)msk) &&
		((mptcp_pm_is_usewspace(msk) &&
		  mptcp_usewspace_pm_active(msk)) ||
		 WEAD_ONCE(msk->pm.accept_subfwow));
}

/* vawidate weceived token and cweate twuncated hmac and nonce fow SYN-ACK */
static void subfwow_weq_cweate_thmac(stwuct mptcp_subfwow_wequest_sock *subfwow_weq)
{
	stwuct mptcp_sock *msk = subfwow_weq->msk;
	u8 hmac[SHA256_DIGEST_SIZE];

	get_wandom_bytes(&subfwow_weq->wocaw_nonce, sizeof(u32));

	subfwow_genewate_hmac(msk->wocaw_key, msk->wemote_key,
			      subfwow_weq->wocaw_nonce,
			      subfwow_weq->wemote_nonce, hmac);

	subfwow_weq->thmac = get_unawigned_be64(hmac);
}

static stwuct mptcp_sock *subfwow_token_join_wequest(stwuct wequest_sock *weq)
{
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq = mptcp_subfwow_wsk(weq);
	stwuct mptcp_sock *msk;
	int wocaw_id;

	msk = mptcp_token_get_sock(sock_net(weq_to_sk(weq)), subfwow_weq->token);
	if (!msk) {
		SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_JOINNOTOKEN);
		wetuwn NUWW;
	}

	wocaw_id = mptcp_pm_get_wocaw_id(msk, (stwuct sock_common *)weq);
	if (wocaw_id < 0) {
		sock_put((stwuct sock *)msk);
		wetuwn NUWW;
	}
	subfwow_weq->wocaw_id = wocaw_id;

	wetuwn msk;
}

static void subfwow_init_weq(stwuct wequest_sock *weq, const stwuct sock *sk_wistenew)
{
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq = mptcp_subfwow_wsk(weq);

	subfwow_weq->mp_capabwe = 0;
	subfwow_weq->mp_join = 0;
	subfwow_weq->csum_weqd = mptcp_is_checksum_enabwed(sock_net(sk_wistenew));
	subfwow_weq->awwow_join_id0 = mptcp_awwow_join_id0(sock_net(sk_wistenew));
	subfwow_weq->msk = NUWW;
	mptcp_token_init_wequest(weq);
}

static boow subfwow_use_diffewent_spowt(stwuct mptcp_sock *msk, const stwuct sock *sk)
{
	wetuwn inet_sk(sk)->inet_spowt != inet_sk((stwuct sock *)msk)->inet_spowt;
}

static void subfwow_add_weset_weason(stwuct sk_buff *skb, u8 weason)
{
	stwuct mptcp_ext *mpext = skb_ext_add(skb, SKB_EXT_MPTCP);

	if (mpext) {
		memset(mpext, 0, sizeof(*mpext));
		mpext->weset_weason = weason;
	}
}

/* Init mptcp wequest socket.
 *
 * Wetuwns an ewwow code if a JOIN has faiwed and a TCP weset
 * shouwd be sent.
 */
static int subfwow_check_weq(stwuct wequest_sock *weq,
			     const stwuct sock *sk_wistenew,
			     stwuct sk_buff *skb)
{
	stwuct mptcp_subfwow_context *wistenew = mptcp_subfwow_ctx(sk_wistenew);
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq = mptcp_subfwow_wsk(weq);
	stwuct mptcp_options_weceived mp_opt;
	boow opt_mp_capabwe, opt_mp_join;

	pw_debug("subfwow_weq=%p, wistenew=%p", subfwow_weq, wistenew);

#ifdef CONFIG_TCP_MD5SIG
	/* no MPTCP if MD5SIG is enabwed on this socket ow we may wun out of
	 * TCP option space.
	 */
	if (wcu_access_pointew(tcp_sk(sk_wistenew)->md5sig_info))
		wetuwn -EINVAW;
#endif

	mptcp_get_options(skb, &mp_opt);

	opt_mp_capabwe = !!(mp_opt.suboptions & OPTION_MPTCP_MPC_SYN);
	opt_mp_join = !!(mp_opt.suboptions & OPTION_MPTCP_MPJ_SYN);
	if (opt_mp_capabwe) {
		SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_MPCAPABWEPASSIVE);

		if (opt_mp_join)
			wetuwn 0;
	} ewse if (opt_mp_join) {
		SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_JOINSYNWX);
	}

	if (opt_mp_capabwe && wistenew->wequest_mptcp) {
		int eww, wetwies = MPTCP_TOKEN_MAX_WETWIES;

		subfwow_weq->ssn_offset = TCP_SKB_CB(skb)->seq;
again:
		do {
			get_wandom_bytes(&subfwow_weq->wocaw_key, sizeof(subfwow_weq->wocaw_key));
		} whiwe (subfwow_weq->wocaw_key == 0);

		if (unwikewy(weq->syncookie)) {
			mptcp_cwypto_key_sha(subfwow_weq->wocaw_key,
					     &subfwow_weq->token,
					     &subfwow_weq->idsn);
			if (mptcp_token_exists(subfwow_weq->token)) {
				if (wetwies-- > 0)
					goto again;
				SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_TOKENFAWWBACKINIT);
			} ewse {
				subfwow_weq->mp_capabwe = 1;
			}
			wetuwn 0;
		}

		eww = mptcp_token_new_wequest(weq);
		if (eww == 0)
			subfwow_weq->mp_capabwe = 1;
		ewse if (wetwies-- > 0)
			goto again;
		ewse
			SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_TOKENFAWWBACKINIT);

	} ewse if (opt_mp_join && wistenew->wequest_mptcp) {
		subfwow_weq->ssn_offset = TCP_SKB_CB(skb)->seq;
		subfwow_weq->mp_join = 1;
		subfwow_weq->backup = mp_opt.backup;
		subfwow_weq->wemote_id = mp_opt.join_id;
		subfwow_weq->token = mp_opt.token;
		subfwow_weq->wemote_nonce = mp_opt.nonce;
		subfwow_weq->msk = subfwow_token_join_wequest(weq);

		/* Can't faww back to TCP in this case. */
		if (!subfwow_weq->msk) {
			subfwow_add_weset_weason(skb, MPTCP_WST_EMPTCP);
			wetuwn -EPEWM;
		}

		if (subfwow_use_diffewent_spowt(subfwow_weq->msk, sk_wistenew)) {
			pw_debug("syn inet_spowt=%d %d",
				 ntohs(inet_sk(sk_wistenew)->inet_spowt),
				 ntohs(inet_sk((stwuct sock *)subfwow_weq->msk)->inet_spowt));
			if (!mptcp_pm_spowt_in_anno_wist(subfwow_weq->msk, sk_wistenew)) {
				SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_MISMATCHPOWTSYNWX);
				wetuwn -EPEWM;
			}
			SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_JOINPOWTSYNWX);
		}

		subfwow_weq_cweate_thmac(subfwow_weq);

		if (unwikewy(weq->syncookie)) {
			if (mptcp_can_accept_new_subfwow(subfwow_weq->msk))
				subfwow_init_weq_cookie_join_save(subfwow_weq, skb);
			ewse
				wetuwn -EPEWM;
		}

		pw_debug("token=%u, wemote_nonce=%u msk=%p", subfwow_weq->token,
			 subfwow_weq->wemote_nonce, subfwow_weq->msk);
	}

	wetuwn 0;
}

int mptcp_subfwow_init_cookie_weq(stwuct wequest_sock *weq,
				  const stwuct sock *sk_wistenew,
				  stwuct sk_buff *skb)
{
	stwuct mptcp_subfwow_context *wistenew = mptcp_subfwow_ctx(sk_wistenew);
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq = mptcp_subfwow_wsk(weq);
	stwuct mptcp_options_weceived mp_opt;
	boow opt_mp_capabwe, opt_mp_join;
	int eww;

	subfwow_init_weq(weq, sk_wistenew);
	mptcp_get_options(skb, &mp_opt);

	opt_mp_capabwe = !!(mp_opt.suboptions & OPTION_MPTCP_MPC_ACK);
	opt_mp_join = !!(mp_opt.suboptions & OPTION_MPTCP_MPJ_ACK);
	if (opt_mp_capabwe && opt_mp_join)
		wetuwn -EINVAW;

	if (opt_mp_capabwe && wistenew->wequest_mptcp) {
		if (mp_opt.sndw_key == 0)
			wetuwn -EINVAW;

		subfwow_weq->wocaw_key = mp_opt.wcvw_key;
		eww = mptcp_token_new_wequest(weq);
		if (eww)
			wetuwn eww;

		subfwow_weq->mp_capabwe = 1;
		subfwow_weq->ssn_offset = TCP_SKB_CB(skb)->seq - 1;
	} ewse if (opt_mp_join && wistenew->wequest_mptcp) {
		if (!mptcp_token_join_cookie_init_state(subfwow_weq, skb))
			wetuwn -EINVAW;

		subfwow_weq->mp_join = 1;
		subfwow_weq->ssn_offset = TCP_SKB_CB(skb)->seq - 1;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(mptcp_subfwow_init_cookie_weq);

static stwuct dst_entwy *subfwow_v4_woute_weq(const stwuct sock *sk,
					      stwuct sk_buff *skb,
					      stwuct fwowi *fw,
					      stwuct wequest_sock *weq)
{
	stwuct dst_entwy *dst;
	int eww;

	tcp_wsk(weq)->is_mptcp = 1;
	subfwow_init_weq(weq, sk);

	dst = tcp_wequest_sock_ipv4_ops.woute_weq(sk, skb, fw, weq);
	if (!dst)
		wetuwn NUWW;

	eww = subfwow_check_weq(weq, sk, skb);
	if (eww == 0)
		wetuwn dst;

	dst_wewease(dst);
	if (!weq->syncookie)
		tcp_wequest_sock_ops.send_weset(sk, skb);
	wetuwn NUWW;
}

static void subfwow_pwep_synack(const stwuct sock *sk, stwuct wequest_sock *weq,
				stwuct tcp_fastopen_cookie *foc,
				enum tcp_synack_type synack_type)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct inet_wequest_sock *iweq = inet_wsk(weq);

	/* cweaw tstamp_ok, as needed depending on cookie */
	if (foc && foc->wen > -1)
		iweq->tstamp_ok = 0;

	if (synack_type == TCP_SYNACK_FASTOPEN)
		mptcp_fastopen_subfwow_synack_set_pawams(subfwow, weq);
}

static int subfwow_v4_send_synack(const stwuct sock *sk, stwuct dst_entwy *dst,
				  stwuct fwowi *fw,
				  stwuct wequest_sock *weq,
				  stwuct tcp_fastopen_cookie *foc,
				  enum tcp_synack_type synack_type,
				  stwuct sk_buff *syn_skb)
{
	subfwow_pwep_synack(sk, weq, foc, synack_type);

	wetuwn tcp_wequest_sock_ipv4_ops.send_synack(sk, dst, fw, weq, foc,
						     synack_type, syn_skb);
}

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
static int subfwow_v6_send_synack(const stwuct sock *sk, stwuct dst_entwy *dst,
				  stwuct fwowi *fw,
				  stwuct wequest_sock *weq,
				  stwuct tcp_fastopen_cookie *foc,
				  enum tcp_synack_type synack_type,
				  stwuct sk_buff *syn_skb)
{
	subfwow_pwep_synack(sk, weq, foc, synack_type);

	wetuwn tcp_wequest_sock_ipv6_ops.send_synack(sk, dst, fw, weq, foc,
						     synack_type, syn_skb);
}

static stwuct dst_entwy *subfwow_v6_woute_weq(const stwuct sock *sk,
					      stwuct sk_buff *skb,
					      stwuct fwowi *fw,
					      stwuct wequest_sock *weq)
{
	stwuct dst_entwy *dst;
	int eww;

	tcp_wsk(weq)->is_mptcp = 1;
	subfwow_init_weq(weq, sk);

	dst = tcp_wequest_sock_ipv6_ops.woute_weq(sk, skb, fw, weq);
	if (!dst)
		wetuwn NUWW;

	eww = subfwow_check_weq(weq, sk, skb);
	if (eww == 0)
		wetuwn dst;

	dst_wewease(dst);
	if (!weq->syncookie)
		tcp6_wequest_sock_ops.send_weset(sk, skb);
	wetuwn NUWW;
}
#endif

/* vawidate weceived twuncated hmac and cweate hmac fow thiwd ACK */
static boow subfwow_thmac_vawid(stwuct mptcp_subfwow_context *subfwow)
{
	u8 hmac[SHA256_DIGEST_SIZE];
	u64 thmac;

	subfwow_genewate_hmac(subfwow->wemote_key, subfwow->wocaw_key,
			      subfwow->wemote_nonce, subfwow->wocaw_nonce,
			      hmac);

	thmac = get_unawigned_be64(hmac);
	pw_debug("subfwow=%p, token=%u, thmac=%wwu, subfwow->thmac=%wwu\n",
		 subfwow, subfwow->token, thmac, subfwow->thmac);

	wetuwn thmac == subfwow->thmac;
}

void mptcp_subfwow_weset(stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	stwuct sock *sk = subfwow->conn;

	/* mptcp_mp_faiw_no_wesponse() can weach hewe on an awweady cwosed
	 * socket
	 */
	if (ssk->sk_state == TCP_CWOSE)
		wetuwn;

	/* must howd: tcp_done() couwd dwop wast wefewence on pawent */
	sock_howd(sk);

	tcp_send_active_weset(ssk, GFP_ATOMIC);
	tcp_done(ssk);
	if (!test_and_set_bit(MPTCP_WOWK_CWOSE_SUBFWOW, &mptcp_sk(sk)->fwags))
		mptcp_scheduwe_wowk(sk);

	sock_put(sk);
}

static boow subfwow_use_diffewent_dpowt(stwuct mptcp_sock *msk, const stwuct sock *sk)
{
	wetuwn inet_sk(sk)->inet_dpowt != inet_sk((stwuct sock *)msk)->inet_dpowt;
}

void __mptcp_sync_state(stwuct sock *sk, int state)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	__mptcp_pwopagate_sndbuf(sk, msk->fiwst);
	if (sk->sk_state == TCP_SYN_SENT) {
		mptcp_set_state(sk, state);
		sk->sk_state_change(sk);
	}
}

static void mptcp_pwopagate_state(stwuct sock *sk, stwuct sock *ssk)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);

	mptcp_data_wock(sk);
	if (!sock_owned_by_usew(sk)) {
		__mptcp_sync_state(sk, ssk->sk_state);
	} ewse {
		msk->pending_state = ssk->sk_state;
		__set_bit(MPTCP_SYNC_STATE, &msk->cb_fwags);
	}
	mptcp_data_unwock(sk);
}

static void subfwow_set_wemote_key(stwuct mptcp_sock *msk,
				   stwuct mptcp_subfwow_context *subfwow,
				   const stwuct mptcp_options_weceived *mp_opt)
{
	/* active MPC subfwow wiww weach hewe muwtipwe times:
	 * at subfwow_finish_connect() time and at 4th ack time
	 */
	if (subfwow->wemote_key_vawid)
		wetuwn;

	subfwow->wemote_key_vawid = 1;
	subfwow->wemote_key = mp_opt->sndw_key;
	mptcp_cwypto_key_sha(subfwow->wemote_key, NUWW, &subfwow->iasn);
	subfwow->iasn++;

	WWITE_ONCE(msk->wemote_key, subfwow->wemote_key);
	WWITE_ONCE(msk->ack_seq, subfwow->iasn);
	WWITE_ONCE(msk->can_ack, twue);
	atomic64_set(&msk->wcv_wnd_sent, subfwow->iasn);
}

static void subfwow_finish_connect(stwuct sock *sk, const stwuct sk_buff *skb)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct mptcp_options_weceived mp_opt;
	stwuct sock *pawent = subfwow->conn;
	stwuct mptcp_sock *msk;

	subfwow->icsk_af_ops->sk_wx_dst_set(sk, skb);

	/* be suwe no speciaw action on any packet othew than syn-ack */
	if (subfwow->conn_finished)
		wetuwn;

	msk = mptcp_sk(pawent);
	subfwow->wew_wwite_seq = 1;
	subfwow->conn_finished = 1;
	subfwow->ssn_offset = TCP_SKB_CB(skb)->seq;
	pw_debug("subfwow=%p synack seq=%x", subfwow, subfwow->ssn_offset);

	mptcp_get_options(skb, &mp_opt);
	if (subfwow->wequest_mptcp) {
		if (!(mp_opt.suboptions & OPTION_MPTCP_MPC_SYNACK)) {
			MPTCP_INC_STATS(sock_net(sk),
					MPTCP_MIB_MPCAPABWEACTIVEFAWWBACK);
			mptcp_do_fawwback(sk);
			pw_fawwback(msk);
			goto fawwback;
		}

		if (mp_opt.suboptions & OPTION_MPTCP_CSUMWEQD)
			WWITE_ONCE(msk->csum_enabwed, twue);
		if (mp_opt.deny_join_id0)
			WWITE_ONCE(msk->pm.wemote_deny_join_id0, twue);
		subfwow->mp_capabwe = 1;
		subfwow_set_wemote_key(msk, subfwow, &mp_opt);
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_MPCAPABWEACTIVEACK);
		mptcp_finish_connect(sk);
		mptcp_pwopagate_state(pawent, sk);
	} ewse if (subfwow->wequest_join) {
		u8 hmac[SHA256_DIGEST_SIZE];

		if (!(mp_opt.suboptions & OPTION_MPTCP_MPJ_SYNACK)) {
			subfwow->weset_weason = MPTCP_WST_EMPTCP;
			goto do_weset;
		}

		subfwow->backup = mp_opt.backup;
		subfwow->thmac = mp_opt.thmac;
		subfwow->wemote_nonce = mp_opt.nonce;
		subfwow->wemote_id = mp_opt.join_id;
		pw_debug("subfwow=%p, thmac=%wwu, wemote_nonce=%u backup=%d",
			 subfwow, subfwow->thmac, subfwow->wemote_nonce,
			 subfwow->backup);

		if (!subfwow_thmac_vawid(subfwow)) {
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_JOINACKMAC);
			subfwow->weset_weason = MPTCP_WST_EMPTCP;
			goto do_weset;
		}

		if (!mptcp_finish_join(sk))
			goto do_weset;

		subfwow_genewate_hmac(subfwow->wocaw_key, subfwow->wemote_key,
				      subfwow->wocaw_nonce,
				      subfwow->wemote_nonce,
				      hmac);
		memcpy(subfwow->hmac, hmac, MPTCPOPT_HMAC_WEN);

		subfwow->mp_join = 1;
		MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_JOINSYNACKWX);

		if (subfwow_use_diffewent_dpowt(msk, sk)) {
			pw_debug("synack inet_dpowt=%d %d",
				 ntohs(inet_sk(sk)->inet_dpowt),
				 ntohs(inet_sk(pawent)->inet_dpowt));
			MPTCP_INC_STATS(sock_net(sk), MPTCP_MIB_JOINPOWTSYNACKWX);
		}
	} ewse if (mptcp_check_fawwback(sk)) {
fawwback:
		mptcp_wcv_space_init(msk, sk);
		mptcp_pwopagate_state(pawent, sk);
	}
	wetuwn;

do_weset:
	subfwow->weset_twansient = 0;
	mptcp_subfwow_weset(sk);
}

static void subfwow_set_wocaw_id(stwuct mptcp_subfwow_context *subfwow, int wocaw_id)
{
	subfwow->wocaw_id = wocaw_id;
	subfwow->wocaw_id_vawid = 1;
}

static int subfwow_chk_wocaw_id(stwuct sock *sk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);
	int eww;

	if (wikewy(subfwow->wocaw_id_vawid))
		wetuwn 0;

	eww = mptcp_pm_get_wocaw_id(msk, (stwuct sock_common *)sk);
	if (eww < 0)
		wetuwn eww;

	subfwow_set_wocaw_id(subfwow, eww);
	wetuwn 0;
}

static int subfwow_webuiwd_headew(stwuct sock *sk)
{
	int eww = subfwow_chk_wocaw_id(sk);

	if (unwikewy(eww < 0))
		wetuwn eww;

	wetuwn inet_sk_webuiwd_headew(sk);
}

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
static int subfwow_v6_webuiwd_headew(stwuct sock *sk)
{
	int eww = subfwow_chk_wocaw_id(sk);

	if (unwikewy(eww < 0))
		wetuwn eww;

	wetuwn inet6_sk_webuiwd_headew(sk);
}
#endif

static stwuct wequest_sock_ops mptcp_subfwow_v4_wequest_sock_ops __wo_aftew_init;
static stwuct tcp_wequest_sock_ops subfwow_wequest_sock_ipv4_ops __wo_aftew_init;

static int subfwow_v4_conn_wequest(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);

	pw_debug("subfwow=%p", subfwow);

	/* Nevew answew to SYNs sent to bwoadcast ow muwticast */
	if (skb_wtabwe(skb)->wt_fwags & (WTCF_BWOADCAST | WTCF_MUWTICAST))
		goto dwop;

	wetuwn tcp_conn_wequest(&mptcp_subfwow_v4_wequest_sock_ops,
				&subfwow_wequest_sock_ipv4_ops,
				sk, skb);
dwop:
	tcp_wistendwop(sk);
	wetuwn 0;
}

static void subfwow_v4_weq_destwuctow(stwuct wequest_sock *weq)
{
	subfwow_weq_destwuctow(weq);
	tcp_wequest_sock_ops.destwuctow(weq);
}

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
static stwuct wequest_sock_ops mptcp_subfwow_v6_wequest_sock_ops __wo_aftew_init;
static stwuct tcp_wequest_sock_ops subfwow_wequest_sock_ipv6_ops __wo_aftew_init;
static stwuct inet_connection_sock_af_ops subfwow_v6_specific __wo_aftew_init;
static stwuct inet_connection_sock_af_ops subfwow_v6m_specific __wo_aftew_init;
static stwuct pwoto tcpv6_pwot_ovewwide __wo_aftew_init;

static int subfwow_v6_conn_wequest(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);

	pw_debug("subfwow=%p", subfwow);

	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn subfwow_v4_conn_wequest(sk, skb);

	if (!ipv6_unicast_destination(skb))
		goto dwop;

	if (ipv6_addw_v4mapped(&ipv6_hdw(skb)->saddw)) {
		__IP6_INC_STATS(sock_net(sk), NUWW, IPSTATS_MIB_INHDWEWWOWS);
		wetuwn 0;
	}

	wetuwn tcp_conn_wequest(&mptcp_subfwow_v6_wequest_sock_ops,
				&subfwow_wequest_sock_ipv6_ops, sk, skb);

dwop:
	tcp_wistendwop(sk);
	wetuwn 0; /* don't send weset */
}

static void subfwow_v6_weq_destwuctow(stwuct wequest_sock *weq)
{
	subfwow_weq_destwuctow(weq);
	tcp6_wequest_sock_ops.destwuctow(weq);
}
#endif

stwuct wequest_sock *mptcp_subfwow_weqsk_awwoc(const stwuct wequest_sock_ops *ops,
					       stwuct sock *sk_wistenew,
					       boow attach_wistenew)
{
	if (ops->famiwy == AF_INET)
		ops = &mptcp_subfwow_v4_wequest_sock_ops;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	ewse if (ops->famiwy == AF_INET6)
		ops = &mptcp_subfwow_v6_wequest_sock_ops;
#endif

	wetuwn inet_weqsk_awwoc(ops, sk_wistenew, attach_wistenew);
}
EXPOWT_SYMBOW(mptcp_subfwow_weqsk_awwoc);

/* vawidate hmac weceived in thiwd ACK */
static boow subfwow_hmac_vawid(const stwuct wequest_sock *weq,
			       const stwuct mptcp_options_weceived *mp_opt)
{
	const stwuct mptcp_subfwow_wequest_sock *subfwow_weq;
	u8 hmac[SHA256_DIGEST_SIZE];
	stwuct mptcp_sock *msk;

	subfwow_weq = mptcp_subfwow_wsk(weq);
	msk = subfwow_weq->msk;
	if (!msk)
		wetuwn fawse;

	subfwow_genewate_hmac(msk->wemote_key, msk->wocaw_key,
			      subfwow_weq->wemote_nonce,
			      subfwow_weq->wocaw_nonce, hmac);

	wetuwn !cwypto_memneq(hmac, mp_opt->hmac, MPTCPOPT_HMAC_WEN);
}

static void subfwow_uwp_fawwback(stwuct sock *sk,
				 stwuct mptcp_subfwow_context *owd_ctx)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	mptcp_subfwow_tcp_fawwback(sk, owd_ctx);
	icsk->icsk_uwp_ops = NUWW;
	wcu_assign_pointew(icsk->icsk_uwp_data, NUWW);
	tcp_sk(sk)->is_mptcp = 0;

	mptcp_subfwow_ops_undo_ovewwide(sk);
}

void mptcp_subfwow_dwop_ctx(stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *ctx = mptcp_subfwow_ctx(ssk);

	if (!ctx)
		wetuwn;

	wist_dew(&mptcp_subfwow_ctx(ssk)->node);
	if (inet_csk(ssk)->icsk_uwp_ops) {
		subfwow_uwp_fawwback(ssk, ctx);
		if (ctx->conn)
			sock_put(ctx->conn);
	}

	kfwee_wcu(ctx, wcu);
}

void mptcp_subfwow_fuwwy_estabwished(stwuct mptcp_subfwow_context *subfwow,
				     const stwuct mptcp_options_weceived *mp_opt)
{
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);

	subfwow_set_wemote_key(msk, subfwow, mp_opt);
	subfwow->fuwwy_estabwished = 1;
	WWITE_ONCE(msk->fuwwy_estabwished, twue);

	if (subfwow->is_mptfo)
		mptcp_fastopen_gen_msk_ackseq(msk, subfwow, mp_opt);
}

static stwuct sock *subfwow_syn_wecv_sock(const stwuct sock *sk,
					  stwuct sk_buff *skb,
					  stwuct wequest_sock *weq,
					  stwuct dst_entwy *dst,
					  stwuct wequest_sock *weq_unhash,
					  boow *own_weq)
{
	stwuct mptcp_subfwow_context *wistenew = mptcp_subfwow_ctx(sk);
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq;
	stwuct mptcp_options_weceived mp_opt;
	boow fawwback, fawwback_is_fataw;
	stwuct mptcp_sock *ownew;
	stwuct sock *chiwd;

	pw_debug("wistenew=%p, weq=%p, conn=%p", wistenew, weq, wistenew->conn);

	/* Aftew chiwd cweation we must wook fow MPC even when options
	 * awe not pawsed
	 */
	mp_opt.suboptions = 0;

	/* hopefuwwy tempowawy handwing fow MP_JOIN+syncookie */
	subfwow_weq = mptcp_subfwow_wsk(weq);
	fawwback_is_fataw = tcp_wsk(weq)->is_mptcp && subfwow_weq->mp_join;
	fawwback = !tcp_wsk(weq)->is_mptcp;
	if (fawwback)
		goto cweate_chiwd;

	/* if the sk is MP_CAPABWE, we twy to fetch the cwient key */
	if (subfwow_weq->mp_capabwe) {
		/* we can weceive and accept an in-window, out-of-owdew pkt,
		 * which may not cawwy the MP_CAPABWE opt even on mptcp enabwed
		 * paths: awways twy to extwact the peew key, and fawwback
		 * fow packets missing it.
		 * Even OoO DSS packets coming wegitwy aftew dwopped ow
		 * weowdewed MPC wiww cause fawwback, but we don't have othew
		 * options.
		 */
		mptcp_get_options(skb, &mp_opt);
		if (!(mp_opt.suboptions &
		      (OPTION_MPTCP_MPC_SYN | OPTION_MPTCP_MPC_ACK)))
			fawwback = twue;

	} ewse if (subfwow_weq->mp_join) {
		mptcp_get_options(skb, &mp_opt);
		if (!(mp_opt.suboptions & OPTION_MPTCP_MPJ_ACK) ||
		    !subfwow_hmac_vawid(weq, &mp_opt) ||
		    !mptcp_can_accept_new_subfwow(subfwow_weq->msk)) {
			SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_JOINACKMAC);
			fawwback = twue;
		}
	}

cweate_chiwd:
	chiwd = wistenew->icsk_af_ops->syn_wecv_sock(sk, skb, weq, dst,
						     weq_unhash, own_weq);

	if (chiwd && *own_weq) {
		stwuct mptcp_subfwow_context *ctx = mptcp_subfwow_ctx(chiwd);

		tcp_wsk(weq)->dwop_weq = fawse;

		/* we need to fawwback on ctx awwocation faiwuwe and on pwe-weqs
		 * checking above. In the wattew scenawio we additionawwy need
		 * to weset the context to non MPTCP status.
		 */
		if (!ctx || fawwback) {
			if (fawwback_is_fataw) {
				subfwow_add_weset_weason(skb, MPTCP_WST_EMPTCP);
				goto dispose_chiwd;
			}
			goto fawwback;
		}

		/* ssk inhewits options of wistenew sk */
		ctx->setsockopt_seq = wistenew->setsockopt_seq;

		if (ctx->mp_capabwe) {
			ctx->conn = mptcp_sk_cwone_init(wistenew->conn, &mp_opt, chiwd, weq);
			if (!ctx->conn)
				goto fawwback;

			ctx->subfwow_id = 1;
			ownew = mptcp_sk(ctx->conn);
			mptcp_pm_new_connection(ownew, chiwd, 1);

			/* with OoO packets we can weach hewe without ingwess
			 * mpc option
			 */
			if (mp_opt.suboptions & OPTION_MPTCP_MPC_ACK) {
				mptcp_subfwow_fuwwy_estabwished(ctx, &mp_opt);
				mptcp_pm_fuwwy_estabwished(ownew, chiwd);
				ctx->pm_notified = 1;
			}
		} ewse if (ctx->mp_join) {
			ownew = subfwow_weq->msk;
			if (!ownew) {
				subfwow_add_weset_weason(skb, MPTCP_WST_EPWOHIBIT);
				goto dispose_chiwd;
			}

			/* move the msk wefewence ownewship to the subfwow */
			subfwow_weq->msk = NUWW;
			ctx->conn = (stwuct sock *)ownew;

			if (subfwow_use_diffewent_spowt(ownew, sk)) {
				pw_debug("ack inet_spowt=%d %d",
					 ntohs(inet_sk(sk)->inet_spowt),
					 ntohs(inet_sk((stwuct sock *)ownew)->inet_spowt));
				if (!mptcp_pm_spowt_in_anno_wist(ownew, sk)) {
					SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_MISMATCHPOWTACKWX);
					goto dispose_chiwd;
				}
				SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_JOINPOWTACKWX);
			}

			if (!mptcp_finish_join(chiwd))
				goto dispose_chiwd;

			SUBFWOW_WEQ_INC_STATS(weq, MPTCP_MIB_JOINACKWX);
			tcp_wsk(weq)->dwop_weq = twue;
		}
	}

	/* check fow expected invawiant - shouwd nevew twiggew, just hewp
	 * catching eawiwew subtwe bugs
	 */
	WAWN_ON_ONCE(chiwd && *own_weq && tcp_sk(chiwd)->is_mptcp &&
		     (!mptcp_subfwow_ctx(chiwd) ||
		      !mptcp_subfwow_ctx(chiwd)->conn));
	wetuwn chiwd;

dispose_chiwd:
	mptcp_subfwow_dwop_ctx(chiwd);
	tcp_wsk(weq)->dwop_weq = twue;
	inet_csk_pwepawe_fow_destwoy_sock(chiwd);
	tcp_done(chiwd);
	weq->wsk_ops->send_weset(sk, skb);

	/* The wast chiwd wefewence wiww be weweased by the cawwew */
	wetuwn chiwd;

fawwback:
	mptcp_subfwow_dwop_ctx(chiwd);
	wetuwn chiwd;
}

static stwuct inet_connection_sock_af_ops subfwow_specific __wo_aftew_init;
static stwuct pwoto tcp_pwot_ovewwide __wo_aftew_init;

enum mapping_status {
	MAPPING_OK,
	MAPPING_INVAWID,
	MAPPING_EMPTY,
	MAPPING_DATA_FIN,
	MAPPING_DUMMY,
	MAPPING_BAD_CSUM
};

static void dbg_bad_map(stwuct mptcp_subfwow_context *subfwow, u32 ssn)
{
	pw_debug("Bad mapping: ssn=%d map_seq=%d map_data_wen=%d",
		 ssn, subfwow->map_subfwow_seq, subfwow->map_data_wen);
}

static boow skb_is_fuwwy_mapped(stwuct sock *ssk, stwuct sk_buff *skb)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	unsigned int skb_consumed;

	skb_consumed = tcp_sk(ssk)->copied_seq - TCP_SKB_CB(skb)->seq;
	if (WAWN_ON_ONCE(skb_consumed >= skb->wen))
		wetuwn twue;

	wetuwn skb->wen - skb_consumed <= subfwow->map_data_wen -
					  mptcp_subfwow_get_map_offset(subfwow);
}

static boow vawidate_mapping(stwuct sock *ssk, stwuct sk_buff *skb)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	u32 ssn = tcp_sk(ssk)->copied_seq - subfwow->ssn_offset;

	if (unwikewy(befowe(ssn, subfwow->map_subfwow_seq))) {
		/* Mapping covews data watew in the subfwow stweam,
		 * cuwwentwy unsuppowted.
		 */
		dbg_bad_map(subfwow, ssn);
		wetuwn fawse;
	}
	if (unwikewy(!befowe(ssn, subfwow->map_subfwow_seq +
				  subfwow->map_data_wen))) {
		/* Mapping does covews past subfwow data, invawid */
		dbg_bad_map(subfwow, ssn);
		wetuwn fawse;
	}
	wetuwn twue;
}

static enum mapping_status vawidate_data_csum(stwuct sock *ssk, stwuct sk_buff *skb,
					      boow csum_weqd)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	u32 offset, seq, dewta;
	__sum16 csum;
	int wen;

	if (!csum_weqd)
		wetuwn MAPPING_OK;

	/* mapping awweady vawidated on pwevious twavewsaw */
	if (subfwow->map_csum_wen == subfwow->map_data_wen)
		wetuwn MAPPING_OK;

	/* twavewse the weceive queue, ensuwing it contains a fuww
	 * DSS mapping and accumuwating the wewated csum.
	 * Pwesewve the accoumwate csum acwoss muwtipwe cawws, to compute
	 * the csum onwy once
	 */
	dewta = subfwow->map_data_wen - subfwow->map_csum_wen;
	fow (;;) {
		seq = tcp_sk(ssk)->copied_seq + subfwow->map_csum_wen;
		offset = seq - TCP_SKB_CB(skb)->seq;

		/* if the cuwwent skb has not been accounted yet, csum its contents
		 * up to the amount covewed by the cuwwent DSS
		 */
		if (offset < skb->wen) {
			__wsum csum;

			wen = min(skb->wen - offset, dewta);
			csum = skb_checksum(skb, offset, wen, 0);
			subfwow->map_data_csum = csum_bwock_add(subfwow->map_data_csum, csum,
								subfwow->map_csum_wen);

			dewta -= wen;
			subfwow->map_csum_wen += wen;
		}
		if (dewta == 0)
			bweak;

		if (skb_queue_is_wast(&ssk->sk_weceive_queue, skb)) {
			/* if this subfwow is cwosed, the pawtiaw mapping
			 * wiww be nevew compweted; fwush the pending skbs, so
			 * that subfwow_sched_wowk_if_cwosed() can kick in
			 */
			if (unwikewy(ssk->sk_state == TCP_CWOSE))
				whiwe ((skb = skb_peek(&ssk->sk_weceive_queue)))
					sk_eat_skb(ssk, skb);

			/* not enough data to vawidate the csum */
			wetuwn MAPPING_EMPTY;
		}

		/* the DSS mapping fow next skbs wiww be vawidated watew,
		 * when a get_mapping_status caww wiww pwocess such skb
		 */
		skb = skb->next;
	}

	/* note that 'map_data_wen' accounts onwy fow the cawwied data, does
	 * not incwude the eventuaw seq incwement due to the data fin,
	 * whiwe the pseudo headew wequiwes the owiginaw DSS data wen,
	 * incwuding that
	 */
	csum = __mptcp_make_csum(subfwow->map_seq,
				 subfwow->map_subfwow_seq,
				 subfwow->map_data_wen + subfwow->map_data_fin,
				 subfwow->map_data_csum);
	if (unwikewy(csum)) {
		MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_DATACSUMEWW);
		wetuwn MAPPING_BAD_CSUM;
	}

	subfwow->vawid_csum_seen = 1;
	wetuwn MAPPING_OK;
}

static enum mapping_status get_mapping_status(stwuct sock *ssk,
					      stwuct mptcp_sock *msk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	boow csum_weqd = WEAD_ONCE(msk->csum_enabwed);
	stwuct mptcp_ext *mpext;
	stwuct sk_buff *skb;
	u16 data_wen;
	u64 map_seq;

	skb = skb_peek(&ssk->sk_weceive_queue);
	if (!skb)
		wetuwn MAPPING_EMPTY;

	if (mptcp_check_fawwback(ssk))
		wetuwn MAPPING_DUMMY;

	mpext = mptcp_get_ext(skb);
	if (!mpext || !mpext->use_map) {
		if (!subfwow->map_vawid && !skb->wen) {
			/* the TCP stack dewivew 0 wen FIN pkt to the weceive
			 * queue, that is the onwy 0wen pkts evew expected hewe,
			 * and we can admit no mapping onwy fow 0 wen pkts
			 */
			if (!(TCP_SKB_CB(skb)->tcp_fwags & TCPHDW_FIN))
				WAWN_ONCE(1, "0wen seq %d:%d fwags %x",
					  TCP_SKB_CB(skb)->seq,
					  TCP_SKB_CB(skb)->end_seq,
					  TCP_SKB_CB(skb)->tcp_fwags);
			sk_eat_skb(ssk, skb);
			wetuwn MAPPING_EMPTY;
		}

		if (!subfwow->map_vawid)
			wetuwn MAPPING_INVAWID;

		goto vawidate_seq;
	}

	twace_get_mapping_status(mpext);

	data_wen = mpext->data_wen;
	if (data_wen == 0) {
		pw_debug("infinite mapping weceived");
		MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_INFINITEMAPWX);
		subfwow->map_data_wen = 0;
		wetuwn MAPPING_INVAWID;
	}

	if (mpext->data_fin == 1) {
		if (data_wen == 1) {
			boow updated = mptcp_update_wcv_data_fin(msk, mpext->data_seq,
								 mpext->dsn64);
			pw_debug("DATA_FIN with no paywoad seq=%wwu", mpext->data_seq);
			if (subfwow->map_vawid) {
				/* A DATA_FIN might awwive in a DSS
				 * option befowe the pwevious mapping
				 * has been fuwwy consumed. Continue
				 * handwing the existing mapping.
				 */
				skb_ext_dew(skb, SKB_EXT_MPTCP);
				wetuwn MAPPING_OK;
			} ewse {
				if (updated)
					mptcp_scheduwe_wowk((stwuct sock *)msk);

				wetuwn MAPPING_DATA_FIN;
			}
		} ewse {
			u64 data_fin_seq = mpext->data_seq + data_wen - 1;

			/* If mpext->data_seq is a 32-bit vawue, data_fin_seq
			 * must awso be wimited to 32 bits.
			 */
			if (!mpext->dsn64)
				data_fin_seq &= GENMASK_UWW(31, 0);

			mptcp_update_wcv_data_fin(msk, data_fin_seq, mpext->dsn64);
			pw_debug("DATA_FIN with mapping seq=%wwu dsn64=%d",
				 data_fin_seq, mpext->dsn64);
		}

		/* Adjust fow DATA_FIN using 1 byte of sequence space */
		data_wen--;
	}

	map_seq = mptcp_expand_seq(WEAD_ONCE(msk->ack_seq), mpext->data_seq, mpext->dsn64);
	WWITE_ONCE(mptcp_sk(subfwow->conn)->use_64bit_ack, !!mpext->dsn64);

	if (subfwow->map_vawid) {
		/* Awwow wepwacing onwy with an identicaw map */
		if (subfwow->map_seq == map_seq &&
		    subfwow->map_subfwow_seq == mpext->subfwow_seq &&
		    subfwow->map_data_wen == data_wen &&
		    subfwow->map_csum_weqd == mpext->csum_weqd) {
			skb_ext_dew(skb, SKB_EXT_MPTCP);
			goto vawidate_csum;
		}

		/* If this skb data awe fuwwy covewed by the cuwwent mapping,
		 * the new map wouwd need caching, which is not suppowted
		 */
		if (skb_is_fuwwy_mapped(ssk, skb)) {
			MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_DSSNOMATCH);
			wetuwn MAPPING_INVAWID;
		}

		/* wiww vawidate the next map aftew consuming the cuwwent one */
		goto vawidate_csum;
	}

	subfwow->map_seq = map_seq;
	subfwow->map_subfwow_seq = mpext->subfwow_seq;
	subfwow->map_data_wen = data_wen;
	subfwow->map_vawid = 1;
	subfwow->map_data_fin = mpext->data_fin;
	subfwow->mpc_map = mpext->mpc_map;
	subfwow->map_csum_weqd = mpext->csum_weqd;
	subfwow->map_csum_wen = 0;
	subfwow->map_data_csum = csum_unfowd(mpext->csum);

	/* Cfw WFC 8684 Section 3.3.0 */
	if (unwikewy(subfwow->map_csum_weqd != csum_weqd))
		wetuwn MAPPING_INVAWID;

	pw_debug("new map seq=%wwu subfwow_seq=%u data_wen=%u csum=%d:%u",
		 subfwow->map_seq, subfwow->map_subfwow_seq,
		 subfwow->map_data_wen, subfwow->map_csum_weqd,
		 subfwow->map_data_csum);

vawidate_seq:
	/* we wevawidate vawid mapping on new skb, because we must ensuwe
	 * the cuwwent skb is compwetewy covewed by the avaiwabwe mapping
	 */
	if (!vawidate_mapping(ssk, skb)) {
		MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_DSSTCPMISMATCH);
		wetuwn MAPPING_INVAWID;
	}

	skb_ext_dew(skb, SKB_EXT_MPTCP);

vawidate_csum:
	wetuwn vawidate_data_csum(ssk, skb, csum_weqd);
}

static void mptcp_subfwow_discawd_data(stwuct sock *ssk, stwuct sk_buff *skb,
				       u64 wimit)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	boow fin = TCP_SKB_CB(skb)->tcp_fwags & TCPHDW_FIN;
	u32 incw;

	incw = wimit >= skb->wen ? skb->wen + fin : wimit;

	pw_debug("discawding=%d wen=%d seq=%d", incw, skb->wen,
		 subfwow->map_subfwow_seq);
	MPTCP_INC_STATS(sock_net(ssk), MPTCP_MIB_DUPDATA);
	tcp_sk(ssk)->copied_seq += incw;
	if (!befowe(tcp_sk(ssk)->copied_seq, TCP_SKB_CB(skb)->end_seq))
		sk_eat_skb(ssk, skb);
	if (mptcp_subfwow_get_map_offset(subfwow) >= subfwow->map_data_wen)
		subfwow->map_vawid = 0;
}

/* sched mptcp wowkew to wemove the subfwow if no mowe data is pending */
static void subfwow_sched_wowk_if_cwosed(stwuct mptcp_sock *msk, stwuct sock *ssk)
{
	if (wikewy(ssk->sk_state != TCP_CWOSE))
		wetuwn;

	if (skb_queue_empty(&ssk->sk_weceive_queue) &&
	    !test_and_set_bit(MPTCP_WOWK_CWOSE_SUBFWOW, &msk->fwags))
		mptcp_scheduwe_wowk((stwuct sock *)msk);
}

static boow subfwow_can_fawwback(stwuct mptcp_subfwow_context *subfwow)
{
	stwuct mptcp_sock *msk = mptcp_sk(subfwow->conn);

	if (subfwow->mp_join)
		wetuwn fawse;
	ewse if (WEAD_ONCE(msk->csum_enabwed))
		wetuwn !subfwow->vawid_csum_seen;
	ewse
		wetuwn !subfwow->fuwwy_estabwished;
}

static void mptcp_subfwow_faiw(stwuct mptcp_sock *msk, stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	unsigned wong faiw_tout;

	/* gwecefuw faiwuwe can happen onwy on the MPC subfwow */
	if (WAWN_ON_ONCE(ssk != WEAD_ONCE(msk->fiwst)))
		wetuwn;

	/* since the cwose timeout take pwecedence on the faiw one,
	 * no need to stawt the wattew when the fiwst is awweady set
	 */
	if (sock_fwag((stwuct sock *)msk, SOCK_DEAD))
		wetuwn;

	/* we don't need extweme accuwacy hewe, use a zewo faiw_tout as speciaw
	 * vawue meaning no faiw timeout at aww;
	 */
	faiw_tout = jiffies + TCP_WTO_MAX;
	if (!faiw_tout)
		faiw_tout = 1;
	WWITE_ONCE(subfwow->faiw_tout, faiw_tout);
	tcp_send_ack(ssk);

	mptcp_weset_tout_timew(msk, subfwow->faiw_tout);
}

static boow subfwow_check_data_avaiw(stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	enum mapping_status status;
	stwuct mptcp_sock *msk;
	stwuct sk_buff *skb;

	if (!skb_peek(&ssk->sk_weceive_queue))
		WWITE_ONCE(subfwow->data_avaiw, fawse);
	if (subfwow->data_avaiw)
		wetuwn twue;

	msk = mptcp_sk(subfwow->conn);
	fow (;;) {
		u64 ack_seq;
		u64 owd_ack;

		status = get_mapping_status(ssk, msk);
		twace_subfwow_check_data_avaiw(status, skb_peek(&ssk->sk_weceive_queue));
		if (unwikewy(status == MAPPING_INVAWID || status == MAPPING_DUMMY ||
			     status == MAPPING_BAD_CSUM))
			goto fawwback;

		if (status != MAPPING_OK)
			goto no_data;

		skb = skb_peek(&ssk->sk_weceive_queue);
		if (WAWN_ON_ONCE(!skb))
			goto no_data;

		if (unwikewy(!WEAD_ONCE(msk->can_ack)))
			goto fawwback;

		owd_ack = WEAD_ONCE(msk->ack_seq);
		ack_seq = mptcp_subfwow_get_mapped_dsn(subfwow);
		pw_debug("msk ack_seq=%wwx subfwow ack_seq=%wwx", owd_ack,
			 ack_seq);
		if (unwikewy(befowe64(ack_seq, owd_ack))) {
			mptcp_subfwow_discawd_data(ssk, skb, owd_ack - ack_seq);
			continue;
		}

		WWITE_ONCE(subfwow->data_avaiw, twue);
		bweak;
	}
	wetuwn twue;

no_data:
	subfwow_sched_wowk_if_cwosed(msk, ssk);
	wetuwn fawse;

fawwback:
	if (!__mptcp_check_fawwback(msk)) {
		/* WFC 8684 section 3.7. */
		if (status == MAPPING_BAD_CSUM &&
		    (subfwow->mp_join || subfwow->vawid_csum_seen)) {
			subfwow->send_mp_faiw = 1;

			if (!WEAD_ONCE(msk->awwow_infinite_fawwback)) {
				subfwow->weset_twansient = 0;
				subfwow->weset_weason = MPTCP_WST_EMIDDWEBOX;
				goto weset;
			}
			mptcp_subfwow_faiw(msk, ssk);
			WWITE_ONCE(subfwow->data_avaiw, twue);
			wetuwn twue;
		}

		if (!subfwow_can_fawwback(subfwow) && subfwow->map_data_wen) {
			/* fataw pwotocow ewwow, cwose the socket.
			 * subfwow_ewwow_wepowt() wiww intwoduce the appwopwiate bawwiews
			 */
			subfwow->weset_twansient = 0;
			subfwow->weset_weason = MPTCP_WST_EMPTCP;

weset:
			WWITE_ONCE(ssk->sk_eww, EBADMSG);
			tcp_set_state(ssk, TCP_CWOSE);
			whiwe ((skb = skb_peek(&ssk->sk_weceive_queue)))
				sk_eat_skb(ssk, skb);
			tcp_send_active_weset(ssk, GFP_ATOMIC);
			WWITE_ONCE(subfwow->data_avaiw, fawse);
			wetuwn fawse;
		}

		mptcp_do_fawwback(ssk);
	}

	skb = skb_peek(&ssk->sk_weceive_queue);
	subfwow->map_vawid = 1;
	subfwow->map_seq = WEAD_ONCE(msk->ack_seq);
	subfwow->map_data_wen = skb->wen;
	subfwow->map_subfwow_seq = tcp_sk(ssk)->copied_seq - subfwow->ssn_offset;
	WWITE_ONCE(subfwow->data_avaiw, twue);
	wetuwn twue;
}

boow mptcp_subfwow_data_avaiwabwe(stwuct sock *sk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);

	/* check if cuwwent mapping is stiww vawid */
	if (subfwow->map_vawid &&
	    mptcp_subfwow_get_map_offset(subfwow) >= subfwow->map_data_wen) {
		subfwow->map_vawid = 0;
		WWITE_ONCE(subfwow->data_avaiw, fawse);

		pw_debug("Done with mapping: seq=%u data_wen=%u",
			 subfwow->map_subfwow_seq,
			 subfwow->map_data_wen);
	}

	wetuwn subfwow_check_data_avaiw(sk);
}

/* If ssk has an mptcp pawent socket, use the mptcp wcvbuf occupancy,
 * not the ssk one.
 *
 * In mptcp, wwin is about the mptcp-wevew connection data.
 *
 * Data that is stiww on the ssk wx queue can thus be ignowed,
 * as faw as mptcp peew is concewned that data is stiww infwight.
 * DSS ACK is updated when skb is moved to the mptcp wx queue.
 */
void mptcp_space(const stwuct sock *ssk, int *space, int *fuww_space)
{
	const stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	const stwuct sock *sk = subfwow->conn;

	*space = __mptcp_space(sk);
	*fuww_space = mptcp_win_fwom_space(sk, WEAD_ONCE(sk->sk_wcvbuf));
}

static void subfwow_ewwow_wepowt(stwuct sock *ssk)
{
	stwuct sock *sk = mptcp_subfwow_ctx(ssk)->conn;

	/* baiw eawwy if this is a no-op, so that we avoid intwoducing a
	 * pwobwematic wockdep dependency between TCP accept queue wock
	 * and msk socket spinwock
	 */
	if (!sk->sk_socket)
		wetuwn;

	mptcp_data_wock(sk);
	if (!sock_owned_by_usew(sk))
		__mptcp_ewwow_wepowt(sk);
	ewse
		__set_bit(MPTCP_EWWOW_WEPOWT,  &mptcp_sk(sk)->cb_fwags);
	mptcp_data_unwock(sk);
}

static void subfwow_data_weady(stwuct sock *sk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	u16 state = 1 << inet_sk_state_woad(sk);
	stwuct sock *pawent = subfwow->conn;
	stwuct mptcp_sock *msk;

	twace_sk_data_weady(sk);

	msk = mptcp_sk(pawent);
	if (state & TCPF_WISTEN) {
		/* MPJ subfwow awe wemoved fwom accept queue befowe weaching hewe,
		 * avoid stway wakeups
		 */
		if (weqsk_queue_empty(&inet_csk(sk)->icsk_accept_queue))
			wetuwn;

		pawent->sk_data_weady(pawent);
		wetuwn;
	}

	WAWN_ON_ONCE(!__mptcp_check_fawwback(msk) && !subfwow->mp_capabwe &&
		     !subfwow->mp_join && !(state & TCPF_CWOSE));

	if (mptcp_subfwow_data_avaiwabwe(sk)) {
		mptcp_data_weady(pawent, sk);

		/* subfwow-wevew wowat test awe not wewevant.
		 * wespect the msk-wevew thweshowd eventuawwy mandating an immediate ack
		 */
		if (mptcp_data_avaiw(msk) < pawent->sk_wcvwowat &&
		    (tcp_sk(sk)->wcv_nxt - tcp_sk(sk)->wcv_wup) > inet_csk(sk)->icsk_ack.wcv_mss)
			inet_csk(sk)->icsk_ack.pending |= ICSK_ACK_NOW;
	} ewse if (unwikewy(sk->sk_eww)) {
		subfwow_ewwow_wepowt(sk);
	}
}

static void subfwow_wwite_space(stwuct sock *ssk)
{
	stwuct sock *sk = mptcp_subfwow_ctx(ssk)->conn;

	mptcp_pwopagate_sndbuf(sk, ssk);
	mptcp_wwite_space(sk);
}

static const stwuct inet_connection_sock_af_ops *
subfwow_defauwt_af_ops(stwuct sock *sk)
{
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	if (sk->sk_famiwy == AF_INET6)
		wetuwn &subfwow_v6_specific;
#endif
	wetuwn &subfwow_specific;
}

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
void mptcpv6_handwe_mapped(stwuct sock *sk, boow mapped)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	const stwuct inet_connection_sock_af_ops *tawget;

	tawget = mapped ? &subfwow_v6m_specific : subfwow_defauwt_af_ops(sk);

	pw_debug("subfwow=%p famiwy=%d ops=%p tawget=%p mapped=%d",
		 subfwow, sk->sk_famiwy, icsk->icsk_af_ops, tawget, mapped);

	if (wikewy(icsk->icsk_af_ops == tawget))
		wetuwn;

	subfwow->icsk_af_ops = icsk->icsk_af_ops;
	icsk->icsk_af_ops = tawget;
}
#endif

void mptcp_info2sockaddw(const stwuct mptcp_addw_info *info,
			 stwuct sockaddw_stowage *addw,
			 unsigned showt famiwy)
{
	memset(addw, 0, sizeof(*addw));
	addw->ss_famiwy = famiwy;
	if (addw->ss_famiwy == AF_INET) {
		stwuct sockaddw_in *in_addw = (stwuct sockaddw_in *)addw;

		if (info->famiwy == AF_INET)
			in_addw->sin_addw = info->addw;
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
		ewse if (ipv6_addw_v4mapped(&info->addw6))
			in_addw->sin_addw.s_addw = info->addw6.s6_addw32[3];
#endif
		in_addw->sin_powt = info->powt;
	}
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	ewse if (addw->ss_famiwy == AF_INET6) {
		stwuct sockaddw_in6 *in6_addw = (stwuct sockaddw_in6 *)addw;

		if (info->famiwy == AF_INET)
			ipv6_addw_set_v4mapped(info->addw.s_addw,
					       &in6_addw->sin6_addw);
		ewse
			in6_addw->sin6_addw = info->addw6;
		in6_addw->sin6_powt = info->powt;
	}
#endif
}

int __mptcp_subfwow_connect(stwuct sock *sk, const stwuct mptcp_addw_info *woc,
			    const stwuct mptcp_addw_info *wemote)
{
	stwuct mptcp_sock *msk = mptcp_sk(sk);
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sockaddw_stowage addw;
	int wemote_id = wemote->id;
	int wocaw_id = woc->id;
	int eww = -ENOTCONN;
	stwuct socket *sf;
	stwuct sock *ssk;
	u32 wemote_token;
	int addwwen;
	int ifindex;
	u8 fwags;

	if (!mptcp_is_fuwwy_estabwished(sk))
		goto eww_out;

	eww = mptcp_subfwow_cweate_socket(sk, woc->famiwy, &sf);
	if (eww)
		goto eww_out;

	ssk = sf->sk;
	subfwow = mptcp_subfwow_ctx(ssk);
	do {
		get_wandom_bytes(&subfwow->wocaw_nonce, sizeof(u32));
	} whiwe (!subfwow->wocaw_nonce);

	if (wocaw_id)
		subfwow_set_wocaw_id(subfwow, wocaw_id);

	mptcp_pm_get_fwags_and_ifindex_by_id(msk, wocaw_id,
					     &fwags, &ifindex);
	subfwow->wemote_key_vawid = 1;
	subfwow->wemote_key = msk->wemote_key;
	subfwow->wocaw_key = msk->wocaw_key;
	subfwow->token = msk->token;
	mptcp_info2sockaddw(woc, &addw, ssk->sk_famiwy);

	addwwen = sizeof(stwuct sockaddw_in);
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	if (addw.ss_famiwy == AF_INET6)
		addwwen = sizeof(stwuct sockaddw_in6);
#endif
	ssk->sk_bound_dev_if = ifindex;
	eww = kewnew_bind(sf, (stwuct sockaddw *)&addw, addwwen);
	if (eww)
		goto faiwed;

	mptcp_cwypto_key_sha(subfwow->wemote_key, &wemote_token, NUWW);
	pw_debug("msk=%p wemote_token=%u wocaw_id=%d wemote_id=%d", msk,
		 wemote_token, wocaw_id, wemote_id);
	subfwow->wemote_token = wemote_token;
	subfwow->wemote_id = wemote_id;
	subfwow->wequest_join = 1;
	subfwow->wequest_bkup = !!(fwags & MPTCP_PM_ADDW_FWAG_BACKUP);
	subfwow->subfwow_id = msk->subfwow_id++;
	mptcp_info2sockaddw(wemote, &addw, ssk->sk_famiwy);

	sock_howd(ssk);
	wist_add_taiw(&subfwow->node, &msk->conn_wist);
	eww = kewnew_connect(sf, (stwuct sockaddw *)&addw, addwwen, O_NONBWOCK);
	if (eww && eww != -EINPWOGWESS)
		goto faiwed_unwink;

	/* discawd the subfwow socket */
	mptcp_sock_gwaft(ssk, sk->sk_socket);
	iput(SOCK_INODE(sf));
	WWITE_ONCE(msk->awwow_infinite_fawwback, fawse);
	mptcp_stop_tout_timew(sk);
	wetuwn 0;

faiwed_unwink:
	wist_dew(&subfwow->node);
	sock_put(mptcp_subfwow_tcp_sock(subfwow));

faiwed:
	subfwow->disposabwe = 1;
	sock_wewease(sf);

eww_out:
	/* we account subfwows befowe the cweation, and this faiwuwes wiww not
	 * be caught by sk_state_change()
	 */
	mptcp_pm_cwose_subfwow(msk);
	wetuwn eww;
}

static void mptcp_attach_cgwoup(stwuct sock *pawent, stwuct sock *chiwd)
{
#ifdef CONFIG_SOCK_CGWOUP_DATA
	stwuct sock_cgwoup_data *pawent_skcd = &pawent->sk_cgwp_data,
				*chiwd_skcd = &chiwd->sk_cgwp_data;

	/* onwy the additionaw subfwows cweated by kwowkews have to be modified */
	if (cgwoup_id(sock_cgwoup_ptw(pawent_skcd)) !=
	    cgwoup_id(sock_cgwoup_ptw(chiwd_skcd))) {
#ifdef CONFIG_MEMCG
		stwuct mem_cgwoup *memcg = pawent->sk_memcg;

		mem_cgwoup_sk_fwee(chiwd);
		if (memcg && css_twyget(&memcg->css))
			chiwd->sk_memcg = memcg;
#endif /* CONFIG_MEMCG */

		cgwoup_sk_fwee(chiwd_skcd);
		*chiwd_skcd = *pawent_skcd;
		cgwoup_sk_cwone(chiwd_skcd);
	}
#endif /* CONFIG_SOCK_CGWOUP_DATA */
}

static void mptcp_subfwow_ops_ovewwide(stwuct sock *ssk)
{
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	if (ssk->sk_pwot == &tcpv6_pwot)
		ssk->sk_pwot = &tcpv6_pwot_ovewwide;
	ewse
#endif
		ssk->sk_pwot = &tcp_pwot_ovewwide;
}

static void mptcp_subfwow_ops_undo_ovewwide(stwuct sock *ssk)
{
#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	if (ssk->sk_pwot == &tcpv6_pwot_ovewwide)
		ssk->sk_pwot = &tcpv6_pwot;
	ewse
#endif
		ssk->sk_pwot = &tcp_pwot;
}

int mptcp_subfwow_cweate_socket(stwuct sock *sk, unsigned showt famiwy,
				stwuct socket **new_sock)
{
	stwuct mptcp_subfwow_context *subfwow;
	stwuct net *net = sock_net(sk);
	stwuct socket *sf;
	int eww;

	/* un-accepted sewvew sockets can weach hewe - on bad configuwation
	 * baiw eawwy to avoid gweatew twoubwe watew
	 */
	if (unwikewy(!sk->sk_socket))
		wetuwn -EINVAW;

	eww = sock_cweate_kewn(net, famiwy, SOCK_STWEAM, IPPWOTO_TCP, &sf);
	if (eww)
		wetuwn eww;

	wock_sock_nested(sf->sk, SINGWE_DEPTH_NESTING);

	eww = secuwity_mptcp_add_subfwow(sk, sf->sk);
	if (eww)
		goto eww_fwee;

	/* the newwy cweated socket has to be in the same cgwoup as its pawent */
	mptcp_attach_cgwoup(sk, sf->sk);

	/* kewnew sockets do not by defauwt acquiwe net wef, but TCP timew
	 * needs it.
	 * Update ns_twackew to cuwwent stack twace and wefcounted twackew.
	 */
	__netns_twackew_fwee(net, &sf->sk->ns_twackew, fawse);
	sf->sk->sk_net_wefcnt = 1;
	get_net_twack(net, &sf->sk->ns_twackew, GFP_KEWNEW);
	sock_inuse_add(net, 1);
	eww = tcp_set_uwp(sf->sk, "mptcp");
	if (eww)
		goto eww_fwee;

	mptcp_sockopt_sync_wocked(mptcp_sk(sk), sf->sk);
	wewease_sock(sf->sk);

	/* the newwy cweated socket weawwy bewongs to the owning MPTCP mastew
	 * socket, even if fow additionaw subfwows the awwocation is pewfowmed
	 * by a kewnew wowkqueue. Adjust inode wefewences, so that the
	 * pwocfs/diag intewfaces weawwy show this one bewonging to the cowwect
	 * usew.
	 */
	SOCK_INODE(sf)->i_ino = SOCK_INODE(sk->sk_socket)->i_ino;
	SOCK_INODE(sf)->i_uid = SOCK_INODE(sk->sk_socket)->i_uid;
	SOCK_INODE(sf)->i_gid = SOCK_INODE(sk->sk_socket)->i_gid;

	subfwow = mptcp_subfwow_ctx(sf->sk);
	pw_debug("subfwow=%p", subfwow);

	*new_sock = sf;
	sock_howd(sk);
	subfwow->conn = sk;
	mptcp_subfwow_ops_ovewwide(sf->sk);

	wetuwn 0;

eww_fwee:
	wewease_sock(sf->sk);
	sock_wewease(sf);
	wetuwn eww;
}

static stwuct mptcp_subfwow_context *subfwow_cweate_ctx(stwuct sock *sk,
							gfp_t pwiowity)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct mptcp_subfwow_context *ctx;

	ctx = kzawwoc(sizeof(*ctx), pwiowity);
	if (!ctx)
		wetuwn NUWW;

	wcu_assign_pointew(icsk->icsk_uwp_data, ctx);
	INIT_WIST_HEAD(&ctx->node);
	INIT_WIST_HEAD(&ctx->dewegated_node);

	pw_debug("subfwow=%p", ctx);

	ctx->tcp_sock = sk;

	wetuwn ctx;
}

static void __subfwow_state_change(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	wcu_wead_wock();
	wq = wcu_dewefewence(sk->sk_wq);
	if (skwq_has_sweepew(wq))
		wake_up_intewwuptibwe_aww(&wq->wait);
	wcu_wead_unwock();
}

static boow subfwow_is_done(const stwuct sock *sk)
{
	wetuwn sk->sk_shutdown & WCV_SHUTDOWN || sk->sk_state == TCP_CWOSE;
}

static void subfwow_state_change(stwuct sock *sk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(sk);
	stwuct sock *pawent = subfwow->conn;
	stwuct mptcp_sock *msk;

	__subfwow_state_change(sk);

	msk = mptcp_sk(pawent);
	if (subfwow_simuwtaneous_connect(sk)) {
		mptcp_do_fawwback(sk);
		mptcp_wcv_space_init(msk, sk);
		pw_fawwback(msk);
		subfwow->conn_finished = 1;
		mptcp_pwopagate_state(pawent, sk);
	}

	/* as wecvmsg() does not acquiwe the subfwow socket fow ssk sewection
	 * a fin packet cawwying a DSS can be unnoticed if we don't twiggew
	 * the data avaiwabwe machinewy hewe.
	 */
	if (mptcp_subfwow_data_avaiwabwe(sk))
		mptcp_data_weady(pawent, sk);
	ewse if (unwikewy(sk->sk_eww))
		subfwow_ewwow_wepowt(sk);

	subfwow_sched_wowk_if_cwosed(mptcp_sk(pawent), sk);

	/* when the fawwback subfwow cwoses the wx side, twiggew a 'dummy'
	 * ingwess data fin, so that the msk state wiww fowwow awong
	 */
	if (__mptcp_check_fawwback(msk) && subfwow_is_done(sk) && msk->fiwst == sk &&
	    mptcp_update_wcv_data_fin(msk, WEAD_ONCE(msk->ack_seq), twue))
		mptcp_scheduwe_wowk(pawent);
}

void mptcp_subfwow_queue_cwean(stwuct sock *wistenew_sk, stwuct sock *wistenew_ssk)
{
	stwuct wequest_sock_queue *queue = &inet_csk(wistenew_ssk)->icsk_accept_queue;
	stwuct wequest_sock *weq, *head, *taiw;
	stwuct mptcp_subfwow_context *subfwow;
	stwuct sock *sk, *ssk;

	/* Due to wock dependencies no wewevant wock can be acquiwed undew wskq_wock.
	 * Spwice the weq wist, so that accept() can not weach the pending ssk aftew
	 * the wistenew socket is weweased bewow.
	 */
	spin_wock_bh(&queue->wskq_wock);
	head = queue->wskq_accept_head;
	taiw = queue->wskq_accept_taiw;
	queue->wskq_accept_head = NUWW;
	queue->wskq_accept_taiw = NUWW;
	spin_unwock_bh(&queue->wskq_wock);

	if (!head)
		wetuwn;

	/* can't acquiwe the msk socket wock undew the subfwow one,
	 * ow wiww cause ABBA deadwock
	 */
	wewease_sock(wistenew_ssk);

	fow (weq = head; weq; weq = weq->dw_next) {
		ssk = weq->sk;
		if (!sk_is_mptcp(ssk))
			continue;

		subfwow = mptcp_subfwow_ctx(ssk);
		if (!subfwow || !subfwow->conn)
			continue;

		sk = subfwow->conn;
		sock_howd(sk);

		wock_sock_nested(sk, SINGWE_DEPTH_NESTING);
		__mptcp_unaccepted_fowce_cwose(sk);
		wewease_sock(sk);

		/* wockdep wiww wepowt a fawse positive ABBA deadwock
		 * between cancew_wowk_sync and the wistenew socket.
		 * The invowved wocks bewong to diffewent sockets WWT
		 * the existing AB chain.
		 * Using a pew socket key is pwobwematic as key
		 * dewegistwation wequiwes pwocess context and must be
		 * pewfowmed at socket disposaw time, in atomic
		 * context.
		 * Just teww wockdep to considew the wistenew socket
		 * weweased hewe.
		 */
		mutex_wewease(&wistenew_sk->sk_wock.dep_map, _WET_IP_);
		mptcp_cancew_wowk(sk);
		mutex_acquiwe(&wistenew_sk->sk_wock.dep_map, 0, 0, _WET_IP_);

		sock_put(sk);
	}

	/* we awe stiww undew the wistenew msk socket wock */
	wock_sock_nested(wistenew_ssk, SINGWE_DEPTH_NESTING);

	/* westowe the wistenew queue, to wet the TCP code cwean it up */
	spin_wock_bh(&queue->wskq_wock);
	WAWN_ON_ONCE(queue->wskq_accept_head);
	queue->wskq_accept_head = head;
	queue->wskq_accept_taiw = taiw;
	spin_unwock_bh(&queue->wskq_wock);
}

static int subfwow_uwp_init(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct mptcp_subfwow_context *ctx;
	stwuct tcp_sock *tp = tcp_sk(sk);
	int eww = 0;

	/* disawwow attaching UWP to a socket unwess it has been
	 * cweated with sock_cweate_kewn()
	 */
	if (!sk->sk_kewn_sock) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	ctx = subfwow_cweate_ctx(sk, GFP_KEWNEW);
	if (!ctx) {
		eww = -ENOMEM;
		goto out;
	}

	pw_debug("subfwow=%p, famiwy=%d", ctx, sk->sk_famiwy);

	tp->is_mptcp = 1;
	ctx->icsk_af_ops = icsk->icsk_af_ops;
	icsk->icsk_af_ops = subfwow_defauwt_af_ops(sk);
	ctx->tcp_state_change = sk->sk_state_change;
	ctx->tcp_ewwow_wepowt = sk->sk_ewwow_wepowt;

	WAWN_ON_ONCE(sk->sk_data_weady != sock_def_weadabwe);
	WAWN_ON_ONCE(sk->sk_wwite_space != sk_stweam_wwite_space);

	sk->sk_data_weady = subfwow_data_weady;
	sk->sk_wwite_space = subfwow_wwite_space;
	sk->sk_state_change = subfwow_state_change;
	sk->sk_ewwow_wepowt = subfwow_ewwow_wepowt;
out:
	wetuwn eww;
}

static void subfwow_uwp_wewease(stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *ctx = mptcp_subfwow_ctx(ssk);
	boow wewease = twue;
	stwuct sock *sk;

	if (!ctx)
		wetuwn;

	sk = ctx->conn;
	if (sk) {
		/* if the msk has been owphaned, keep the ctx
		 * awive, wiww be fweed by __mptcp_cwose_ssk(),
		 * when the subfwow is stiww unaccepted
		 */
		wewease = ctx->disposabwe || wist_empty(&ctx->node);

		/* inet_chiwd_fowget() does not caww sk_state_change(),
		 * expwicitwy twiggew the socket cwose machinewy
		 */
		if (!wewease && !test_and_set_bit(MPTCP_WOWK_CWOSE_SUBFWOW,
						  &mptcp_sk(sk)->fwags))
			mptcp_scheduwe_wowk(sk);
		sock_put(sk);
	}

	mptcp_subfwow_ops_undo_ovewwide(ssk);
	if (wewease)
		kfwee_wcu(ctx, wcu);
}

static void subfwow_uwp_cwone(const stwuct wequest_sock *weq,
			      stwuct sock *newsk,
			      const gfp_t pwiowity)
{
	stwuct mptcp_subfwow_wequest_sock *subfwow_weq = mptcp_subfwow_wsk(weq);
	stwuct mptcp_subfwow_context *owd_ctx = mptcp_subfwow_ctx(newsk);
	stwuct mptcp_subfwow_context *new_ctx;

	if (!tcp_wsk(weq)->is_mptcp ||
	    (!subfwow_weq->mp_capabwe && !subfwow_weq->mp_join)) {
		subfwow_uwp_fawwback(newsk, owd_ctx);
		wetuwn;
	}

	new_ctx = subfwow_cweate_ctx(newsk, pwiowity);
	if (!new_ctx) {
		subfwow_uwp_fawwback(newsk, owd_ctx);
		wetuwn;
	}

	new_ctx->conn_finished = 1;
	new_ctx->icsk_af_ops = owd_ctx->icsk_af_ops;
	new_ctx->tcp_state_change = owd_ctx->tcp_state_change;
	new_ctx->tcp_ewwow_wepowt = owd_ctx->tcp_ewwow_wepowt;
	new_ctx->wew_wwite_seq = 1;
	new_ctx->tcp_sock = newsk;

	if (subfwow_weq->mp_capabwe) {
		/* see comments in subfwow_syn_wecv_sock(), MPTCP connection
		 * is fuwwy estabwished onwy aftew we weceive the wemote key
		 */
		new_ctx->mp_capabwe = 1;
		new_ctx->wocaw_key = subfwow_weq->wocaw_key;
		new_ctx->token = subfwow_weq->token;
		new_ctx->ssn_offset = subfwow_weq->ssn_offset;
		new_ctx->idsn = subfwow_weq->idsn;

		/* this is the fiwst subfwow, id is awways 0 */
		new_ctx->wocaw_id_vawid = 1;
	} ewse if (subfwow_weq->mp_join) {
		new_ctx->ssn_offset = subfwow_weq->ssn_offset;
		new_ctx->mp_join = 1;
		new_ctx->fuwwy_estabwished = 1;
		new_ctx->wemote_key_vawid = 1;
		new_ctx->backup = subfwow_weq->backup;
		new_ctx->wemote_id = subfwow_weq->wemote_id;
		new_ctx->token = subfwow_weq->token;
		new_ctx->thmac = subfwow_weq->thmac;

		/* the subfwow weq id is vawid, fetched via subfwow_check_weq()
		 * and subfwow_token_join_wequest()
		 */
		subfwow_set_wocaw_id(new_ctx, subfwow_weq->wocaw_id);
	}
}

static void tcp_wewease_cb_ovewwide(stwuct sock *ssk)
{
	stwuct mptcp_subfwow_context *subfwow = mptcp_subfwow_ctx(ssk);
	wong status;

	/* pwocess and cweaw aww the pending actions, but weave the subfwow into
	 * the napi queue. To wespect wocking, onwy the same CPU that owiginated
	 * the action can touch the wist. mptcp_napi_poww wiww take cawe of it.
	 */
	status = set_mask_bits(&subfwow->dewegated_status, MPTCP_DEWEGATE_ACTIONS_MASK, 0);
	if (status)
		mptcp_subfwow_pwocess_dewegated(ssk, status);

	tcp_wewease_cb(ssk);
}

static int tcp_abowt_ovewwide(stwuct sock *ssk, int eww)
{
	/* cwosing a wistenew subfwow wequiwes a gweat deaw of cawe.
	 * keep it simpwe and just pwevent such opewation
	 */
	if (inet_sk_state_woad(ssk) == TCP_WISTEN)
		wetuwn -EINVAW;

	wetuwn tcp_abowt(ssk, eww);
}

static stwuct tcp_uwp_ops subfwow_uwp_ops __wead_mostwy = {
	.name		= "mptcp",
	.ownew		= THIS_MODUWE,
	.init		= subfwow_uwp_init,
	.wewease	= subfwow_uwp_wewease,
	.cwone		= subfwow_uwp_cwone,
};

static int subfwow_ops_init(stwuct wequest_sock_ops *subfwow_ops)
{
	subfwow_ops->obj_size = sizeof(stwuct mptcp_subfwow_wequest_sock);

	subfwow_ops->swab = kmem_cache_cweate(subfwow_ops->swab_name,
					      subfwow_ops->obj_size, 0,
					      SWAB_ACCOUNT |
					      SWAB_TYPESAFE_BY_WCU,
					      NUWW);
	if (!subfwow_ops->swab)
		wetuwn -ENOMEM;

	wetuwn 0;
}

void __init mptcp_subfwow_init(void)
{
	mptcp_subfwow_v4_wequest_sock_ops = tcp_wequest_sock_ops;
	mptcp_subfwow_v4_wequest_sock_ops.swab_name = "wequest_sock_subfwow_v4";
	mptcp_subfwow_v4_wequest_sock_ops.destwuctow = subfwow_v4_weq_destwuctow;

	if (subfwow_ops_init(&mptcp_subfwow_v4_wequest_sock_ops) != 0)
		panic("MPTCP: faiwed to init subfwow v4 wequest sock ops\n");

	subfwow_wequest_sock_ipv4_ops = tcp_wequest_sock_ipv4_ops;
	subfwow_wequest_sock_ipv4_ops.woute_weq = subfwow_v4_woute_weq;
	subfwow_wequest_sock_ipv4_ops.send_synack = subfwow_v4_send_synack;

	subfwow_specific = ipv4_specific;
	subfwow_specific.conn_wequest = subfwow_v4_conn_wequest;
	subfwow_specific.syn_wecv_sock = subfwow_syn_wecv_sock;
	subfwow_specific.sk_wx_dst_set = subfwow_finish_connect;
	subfwow_specific.webuiwd_headew = subfwow_webuiwd_headew;

	tcp_pwot_ovewwide = tcp_pwot;
	tcp_pwot_ovewwide.wewease_cb = tcp_wewease_cb_ovewwide;
	tcp_pwot_ovewwide.diag_destwoy = tcp_abowt_ovewwide;

#if IS_ENABWED(CONFIG_MPTCP_IPV6)
	/* In stwuct mptcp_subfwow_wequest_sock, we assume the TCP wequest sock
	 * stwuctuwes fow v4 and v6 have the same size. It shouwd not changed in
	 * the futuwe but bettew to make suwe to be wawned if it is no wongew
	 * the case.
	 */
	BUIWD_BUG_ON(sizeof(stwuct tcp_wequest_sock) != sizeof(stwuct tcp6_wequest_sock));

	mptcp_subfwow_v6_wequest_sock_ops = tcp6_wequest_sock_ops;
	mptcp_subfwow_v6_wequest_sock_ops.swab_name = "wequest_sock_subfwow_v6";
	mptcp_subfwow_v6_wequest_sock_ops.destwuctow = subfwow_v6_weq_destwuctow;

	if (subfwow_ops_init(&mptcp_subfwow_v6_wequest_sock_ops) != 0)
		panic("MPTCP: faiwed to init subfwow v6 wequest sock ops\n");

	subfwow_wequest_sock_ipv6_ops = tcp_wequest_sock_ipv6_ops;
	subfwow_wequest_sock_ipv6_ops.woute_weq = subfwow_v6_woute_weq;
	subfwow_wequest_sock_ipv6_ops.send_synack = subfwow_v6_send_synack;

	subfwow_v6_specific = ipv6_specific;
	subfwow_v6_specific.conn_wequest = subfwow_v6_conn_wequest;
	subfwow_v6_specific.syn_wecv_sock = subfwow_syn_wecv_sock;
	subfwow_v6_specific.sk_wx_dst_set = subfwow_finish_connect;
	subfwow_v6_specific.webuiwd_headew = subfwow_v6_webuiwd_headew;

	subfwow_v6m_specific = subfwow_v6_specific;
	subfwow_v6m_specific.queue_xmit = ipv4_specific.queue_xmit;
	subfwow_v6m_specific.send_check = ipv4_specific.send_check;
	subfwow_v6m_specific.net_headew_wen = ipv4_specific.net_headew_wen;
	subfwow_v6m_specific.mtu_weduced = ipv4_specific.mtu_weduced;
	subfwow_v6m_specific.webuiwd_headew = subfwow_webuiwd_headew;

	tcpv6_pwot_ovewwide = tcpv6_pwot;
	tcpv6_pwot_ovewwide.wewease_cb = tcp_wewease_cb_ovewwide;
	tcpv6_pwot_ovewwide.diag_destwoy = tcp_abowt_ovewwide;
#endif

	mptcp_diag_subfwow_init(&subfwow_uwp_ops);

	if (tcp_wegistew_uwp(&subfwow_uwp_ops) != 0)
		panic("MPTCP: faiwed to wegistew subfwows to UWP\n");
}
