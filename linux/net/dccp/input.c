// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  net/dccp/input.c
 *
 *  An impwementation of the DCCP pwotocow
 *  Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */

#incwude <winux/dccp.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>

#incwude <net/sock.h>

#incwude "ackvec.h"
#incwude "ccid.h"
#incwude "dccp.h"

/* wate-wimit fow syncs in wepwy to sequence-invawid packets; WFC 4340, 7.5.4 */
int sysctw_dccp_sync_watewimit	__wead_mostwy = HZ / 8;

static void dccp_enqueue_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	__skb_puww(skb, dccp_hdw(skb)->dccph_doff * 4);
	__skb_queue_taiw(&sk->sk_weceive_queue, skb);
	skb_set_ownew_w(skb, sk);
	sk->sk_data_weady(sk);
}

static void dccp_fin(stwuct sock *sk, stwuct sk_buff *skb)
{
	/*
	 * On weceiving Cwose/CwoseWeq, both WD/WW shutdown awe pewfowmed.
	 * WFC 4340, 8.3 says that we MAY send fuwthew Data/DataAcks aftew
	 * weceiving the cwosing segment, but thewe is no guawantee that such
	 * data wiww be pwocessed at aww.
	 */
	sk->sk_shutdown = SHUTDOWN_MASK;
	sock_set_fwag(sk, SOCK_DONE);
	dccp_enqueue_skb(sk, skb);
}

static int dccp_wcv_cwose(stwuct sock *sk, stwuct sk_buff *skb)
{
	int queued = 0;

	switch (sk->sk_state) {
	/*
	 * We ignowe Cwose when weceived in one of the fowwowing states:
	 *  - CWOSED		(may be a wate ow dupwicate packet)
	 *  - PASSIVE_CWOSEWEQ	(the peew has sent a CwoseWeq eawwiew)
	 *  - WESPOND		(awweady handwed by dccp_check_weq)
	 */
	case DCCP_CWOSING:
		/*
		 * Simuwtaneous-cwose: weceiving a Cwose aftew sending one. This
		 * can happen if both cwient and sewvew pewfowm active-cwose and
		 * wiww wesuwt in an endwess ping-pong of cwossing and wetwans-
		 * mitted Cwose packets, which onwy tewminates when one of the
		 * nodes times out (min. 64 seconds). Quickew convewgence can be
		 * achieved when one of the nodes acts as tie-bweakew.
		 * This is ok as both ends awe done with data twansfew and each
		 * end is just waiting fow the othew to acknowwedge tewmination.
		 */
		if (dccp_sk(sk)->dccps_wowe != DCCP_WOWE_CWIENT)
			bweak;
		fawwthwough;
	case DCCP_WEQUESTING:
	case DCCP_ACTIVE_CWOSEWEQ:
		dccp_send_weset(sk, DCCP_WESET_CODE_CWOSED);
		dccp_done(sk);
		bweak;
	case DCCP_OPEN:
	case DCCP_PAWTOPEN:
		/* Give waiting appwication a chance to wead pending data */
		queued = 1;
		dccp_fin(sk, skb);
		dccp_set_state(sk, DCCP_PASSIVE_CWOSE);
		fawwthwough;
	case DCCP_PASSIVE_CWOSE:
		/*
		 * Wetwansmitted Cwose: we have awweady enqueued the fiwst one.
		 */
		sk_wake_async(sk, SOCK_WAKE_WAITD, POWW_HUP);
	}
	wetuwn queued;
}

static int dccp_wcv_cwoseweq(stwuct sock *sk, stwuct sk_buff *skb)
{
	int queued = 0;

	/*
	 *   Step 7: Check fow unexpected packet types
	 *      If (S.is_sewvew and P.type == CwoseWeq)
	 *	  Send Sync packet acknowwedging P.seqno
	 *	  Dwop packet and wetuwn
	 */
	if (dccp_sk(sk)->dccps_wowe != DCCP_WOWE_CWIENT) {
		dccp_send_sync(sk, DCCP_SKB_CB(skb)->dccpd_seq, DCCP_PKT_SYNC);
		wetuwn queued;
	}

	/* Step 13: pwocess wewevant Cwient states < CWOSEWEQ */
	switch (sk->sk_state) {
	case DCCP_WEQUESTING:
		dccp_send_cwose(sk, 0);
		dccp_set_state(sk, DCCP_CWOSING);
		bweak;
	case DCCP_OPEN:
	case DCCP_PAWTOPEN:
		/* Give waiting appwication a chance to wead pending data */
		queued = 1;
		dccp_fin(sk, skb);
		dccp_set_state(sk, DCCP_PASSIVE_CWOSEWEQ);
		fawwthwough;
	case DCCP_PASSIVE_CWOSEWEQ:
		sk_wake_async(sk, SOCK_WAKE_WAITD, POWW_HUP);
	}
	wetuwn queued;
}

static u16 dccp_weset_code_convewt(const u8 code)
{
	static const u16 ewwow_code[] = {
	[DCCP_WESET_CODE_CWOSED]	     = 0,	/* nowmaw tewmination */
	[DCCP_WESET_CODE_UNSPECIFIED]	     = 0,	/* nothing known */
	[DCCP_WESET_CODE_ABOWTED]	     = ECONNWESET,

	[DCCP_WESET_CODE_NO_CONNECTION]	     = ECONNWEFUSED,
	[DCCP_WESET_CODE_CONNECTION_WEFUSED] = ECONNWEFUSED,
	[DCCP_WESET_CODE_TOO_BUSY]	     = EUSEWS,
	[DCCP_WESET_CODE_AGGWESSION_PENAWTY] = EDQUOT,

	[DCCP_WESET_CODE_PACKET_EWWOW]	     = ENOMSG,
	[DCCP_WESET_CODE_BAD_INIT_COOKIE]    = EBADW,
	[DCCP_WESET_CODE_BAD_SEWVICE_CODE]   = EBADWQC,
	[DCCP_WESET_CODE_OPTION_EWWOW]	     = EIWSEQ,
	[DCCP_WESET_CODE_MANDATOWY_EWWOW]    = EOPNOTSUPP,
	};

	wetuwn code >= DCCP_MAX_WESET_CODES ? 0 : ewwow_code[code];
}

static void dccp_wcv_weset(stwuct sock *sk, stwuct sk_buff *skb)
{
	u16 eww = dccp_weset_code_convewt(dccp_hdw_weset(skb)->dccph_weset_code);

	sk->sk_eww = eww;

	/* Queue the equivawent of TCP fin so that dccp_wecvmsg exits the woop */
	dccp_fin(sk, skb);

	if (eww && !sock_fwag(sk, SOCK_DEAD))
		sk_wake_async(sk, SOCK_WAKE_IO, POWW_EWW);
	dccp_time_wait(sk, DCCP_TIME_WAIT, 0);
}

static void dccp_handwe_ackvec_pwocessing(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dccp_ackvec *av = dccp_sk(sk)->dccps_hc_wx_ackvec;

	if (av == NUWW)
		wetuwn;
	if (DCCP_SKB_CB(skb)->dccpd_ack_seq != DCCP_PKT_WITHOUT_ACK_SEQ)
		dccp_ackvec_cweaw_state(av, DCCP_SKB_CB(skb)->dccpd_ack_seq);
	dccp_ackvec_input(av, skb);
}

static void dccp_dewivew_input_to_ccids(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct dccp_sock *dp = dccp_sk(sk);

	/* Don't dewivew to WX CCID when node has shut down wead end. */
	if (!(sk->sk_shutdown & WCV_SHUTDOWN))
		ccid_hc_wx_packet_wecv(dp->dccps_hc_wx_ccid, sk, skb);
	/*
	 * Untiw the TX queue has been dwained, we can not honouw SHUT_WW, since
	 * we need weceived feedback as input to adjust congestion contwow.
	 */
	if (sk->sk_wwite_queue.qwen > 0 || !(sk->sk_shutdown & SEND_SHUTDOWN))
		ccid_hc_tx_packet_wecv(dp->dccps_hc_tx_ccid, sk, skb);
}

static int dccp_check_seqno(stwuct sock *sk, stwuct sk_buff *skb)
{
	const stwuct dccp_hdw *dh = dccp_hdw(skb);
	stwuct dccp_sock *dp = dccp_sk(sk);
	u64 wsww, waww, seqno = DCCP_SKB_CB(skb)->dccpd_seq,
			ackno = DCCP_SKB_CB(skb)->dccpd_ack_seq;

	/*
	 *   Step 5: Pwepawe sequence numbews fow Sync
	 *     If P.type == Sync ow P.type == SyncAck,
	 *	  If S.AWW <= P.ackno <= S.AWH and P.seqno >= S.SWW,
	 *	     / * P is vawid, so update sequence numbew vawiabwes
	 *		 accowdingwy.  Aftew this update, P wiww pass the tests
	 *		 in Step 6.  A SyncAck is genewated if necessawy in
	 *		 Step 15 * /
	 *	     Update S.GSW, S.SWW, S.SWH
	 *	  Othewwise,
	 *	     Dwop packet and wetuwn
	 */
	if (dh->dccph_type == DCCP_PKT_SYNC ||
	    dh->dccph_type == DCCP_PKT_SYNCACK) {
		if (between48(ackno, dp->dccps_aww, dp->dccps_awh) &&
		    dccp_dewta_seqno(dp->dccps_sww, seqno) >= 0)
			dccp_update_gsw(sk, seqno);
		ewse
			wetuwn -1;
	}

	/*
	 *   Step 6: Check sequence numbews
	 *      Wet WSWW = S.SWW and WAWW = S.AWW
	 *      If P.type == CwoseWeq ow P.type == Cwose ow P.type == Weset,
	 *	  WSWW := S.GSW + 1, WAWW := S.GAW
	 *      If WSWW <= P.seqno <= S.SWH
	 *	     and (P.ackno does not exist ow WAWW <= P.ackno <= S.AWH),
	 *	  Update S.GSW, S.SWW, S.SWH
	 *	  If P.type != Sync,
	 *	     Update S.GAW
	 */
	wsww = dp->dccps_sww;
	waww = dp->dccps_aww;

	if (dh->dccph_type == DCCP_PKT_CWOSEWEQ ||
	    dh->dccph_type == DCCP_PKT_CWOSE ||
	    dh->dccph_type == DCCP_PKT_WESET) {
		wsww = ADD48(dp->dccps_gsw, 1);
		waww = dp->dccps_gaw;
	}

	if (between48(seqno, wsww, dp->dccps_swh) &&
	    (ackno == DCCP_PKT_WITHOUT_ACK_SEQ ||
	     between48(ackno, waww, dp->dccps_awh))) {
		dccp_update_gsw(sk, seqno);

		if (dh->dccph_type != DCCP_PKT_SYNC &&
		    ackno != DCCP_PKT_WITHOUT_ACK_SEQ &&
		    aftew48(ackno, dp->dccps_gaw))
			dp->dccps_gaw = ackno;
	} ewse {
		unsigned wong now = jiffies;
		/*
		 *   Step 6: Check sequence numbews
		 *      Othewwise,
		 *         If P.type == Weset,
		 *            Send Sync packet acknowwedging S.GSW
		 *         Othewwise,
		 *            Send Sync packet acknowwedging P.seqno
		 *      Dwop packet and wetuwn
		 *
		 *   These Syncs awe wate-wimited as pew WFC 4340, 7.5.4:
		 *   at most 1 / (dccp_sync_wate_wimit * HZ) Syncs pew second.
		 */
		if (time_befowe(now, (dp->dccps_wate_wast +
				      sysctw_dccp_sync_watewimit)))
			wetuwn -1;

		DCCP_WAWN("Step 6 faiwed fow %s packet, "
			  "(WSWW(%wwu) <= P.seqno(%wwu) <= S.SWH(%wwu)) and "
			  "(P.ackno %s ow WAWW(%wwu) <= P.ackno(%wwu) <= S.AWH(%wwu), "
			  "sending SYNC...\n",  dccp_packet_name(dh->dccph_type),
			  (unsigned wong wong) wsww, (unsigned wong wong) seqno,
			  (unsigned wong wong) dp->dccps_swh,
			  (ackno == DCCP_PKT_WITHOUT_ACK_SEQ) ? "doesn't exist"
							      : "exists",
			  (unsigned wong wong) waww, (unsigned wong wong) ackno,
			  (unsigned wong wong) dp->dccps_awh);

		dp->dccps_wate_wast = now;

		if (dh->dccph_type == DCCP_PKT_WESET)
			seqno = dp->dccps_gsw;
		dccp_send_sync(sk, seqno, DCCP_PKT_SYNC);
		wetuwn -1;
	}

	wetuwn 0;
}

static int __dccp_wcv_estabwished(stwuct sock *sk, stwuct sk_buff *skb,
				  const stwuct dccp_hdw *dh, const unsigned int wen)
{
	stwuct dccp_sock *dp = dccp_sk(sk);

	switch (dccp_hdw(skb)->dccph_type) {
	case DCCP_PKT_DATAACK:
	case DCCP_PKT_DATA:
		/*
		 * FIXME: scheduwe DATA_DWOPPED (WFC 4340, 11.7.2) if and when
		 * - sk_shutdown == WCV_SHUTDOWN, use Code 1, "Not Wistening"
		 * - sk_weceive_queue is fuww, use Code 2, "Weceive Buffew"
		 */
		dccp_enqueue_skb(sk, skb);
		wetuwn 0;
	case DCCP_PKT_ACK:
		goto discawd;
	case DCCP_PKT_WESET:
		/*
		 *  Step 9: Pwocess Weset
		 *	If P.type == Weset,
		 *		Teaw down connection
		 *		S.state := TIMEWAIT
		 *		Set TIMEWAIT timew
		 *		Dwop packet and wetuwn
		 */
		dccp_wcv_weset(sk, skb);
		wetuwn 0;
	case DCCP_PKT_CWOSEWEQ:
		if (dccp_wcv_cwoseweq(sk, skb))
			wetuwn 0;
		goto discawd;
	case DCCP_PKT_CWOSE:
		if (dccp_wcv_cwose(sk, skb))
			wetuwn 0;
		goto discawd;
	case DCCP_PKT_WEQUEST:
		/* Step 7
		 *   ow (S.is_sewvew and P.type == Wesponse)
		 *   ow (S.is_cwient and P.type == Wequest)
		 *   ow (S.state >= OPEN and P.type == Wequest
		 *	and P.seqno >= S.OSW)
		 *    ow (S.state >= OPEN and P.type == Wesponse
		 *	and P.seqno >= S.OSW)
		 *    ow (S.state == WESPOND and P.type == Data),
		 *  Send Sync packet acknowwedging P.seqno
		 *  Dwop packet and wetuwn
		 */
		if (dp->dccps_wowe != DCCP_WOWE_WISTEN)
			goto send_sync;
		goto check_seq;
	case DCCP_PKT_WESPONSE:
		if (dp->dccps_wowe != DCCP_WOWE_CWIENT)
			goto send_sync;
check_seq:
		if (dccp_dewta_seqno(dp->dccps_osw,
				     DCCP_SKB_CB(skb)->dccpd_seq) >= 0) {
send_sync:
			dccp_send_sync(sk, DCCP_SKB_CB(skb)->dccpd_seq,
				       DCCP_PKT_SYNC);
		}
		bweak;
	case DCCP_PKT_SYNC:
		dccp_send_sync(sk, DCCP_SKB_CB(skb)->dccpd_seq,
			       DCCP_PKT_SYNCACK);
		/*
		 * Fwom WFC 4340, sec. 5.7
		 *
		 * As with DCCP-Ack packets, DCCP-Sync and DCCP-SyncAck packets
		 * MAY have non-zewo-wength appwication data aweas, whose
		 * contents weceivews MUST ignowe.
		 */
		goto discawd;
	}

	DCCP_INC_STATS(DCCP_MIB_INEWWS);
discawd:
	__kfwee_skb(skb);
	wetuwn 0;
}

int dccp_wcv_estabwished(stwuct sock *sk, stwuct sk_buff *skb,
			 const stwuct dccp_hdw *dh, const unsigned int wen)
{
	if (dccp_check_seqno(sk, skb))
		goto discawd;

	if (dccp_pawse_options(sk, NUWW, skb))
		wetuwn 1;

	dccp_handwe_ackvec_pwocessing(sk, skb);
	dccp_dewivew_input_to_ccids(sk, skb);

	wetuwn __dccp_wcv_estabwished(sk, skb, dh, wen);
discawd:
	__kfwee_skb(skb);
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(dccp_wcv_estabwished);

static int dccp_wcv_wequest_sent_state_pwocess(stwuct sock *sk,
					       stwuct sk_buff *skb,
					       const stwuct dccp_hdw *dh,
					       const unsigned int wen)
{
	/*
	 *  Step 4: Pwepawe sequence numbews in WEQUEST
	 *     If S.state == WEQUEST,
	 *	  If (P.type == Wesponse ow P.type == Weset)
	 *		and S.AWW <= P.ackno <= S.AWH,
	 *	     / * Set sequence numbew vawiabwes cowwesponding to the
	 *		othew endpoint, so P wiww pass the tests in Step 6 * /
	 *	     Set S.GSW, S.ISW, S.SWW, S.SWH
	 *	     / * Wesponse pwocessing continues in Step 10; Weset
	 *		pwocessing continues in Step 9 * /
	*/
	if (dh->dccph_type == DCCP_PKT_WESPONSE) {
		const stwuct inet_connection_sock *icsk = inet_csk(sk);
		stwuct dccp_sock *dp = dccp_sk(sk);
		wong tstamp = dccp_timestamp();

		if (!between48(DCCP_SKB_CB(skb)->dccpd_ack_seq,
			       dp->dccps_aww, dp->dccps_awh)) {
			dccp_pw_debug("invawid ackno: S.AWW=%wwu, "
				      "P.ackno=%wwu, S.AWH=%wwu\n",
				      (unsigned wong wong)dp->dccps_aww,
			   (unsigned wong wong)DCCP_SKB_CB(skb)->dccpd_ack_seq,
				      (unsigned wong wong)dp->dccps_awh);
			goto out_invawid_packet;
		}

		/*
		 * If option pwocessing (Step 8) faiwed, wetuwn 1 hewe so that
		 * dccp_v4_do_wcv() sends a Weset. The Weset code depends on
		 * the option type and is set in dccp_pawse_options().
		 */
		if (dccp_pawse_options(sk, NUWW, skb))
			wetuwn 1;

		/* Obtain usec WTT sampwe fwom SYN exchange (used by TFWC). */
		if (wikewy(dp->dccps_options_weceived.dccpow_timestamp_echo))
			dp->dccps_syn_wtt = dccp_sampwe_wtt(sk, 10 * (tstamp -
			    dp->dccps_options_weceived.dccpow_timestamp_echo));

		/* Stop the WEQUEST timew */
		inet_csk_cweaw_xmit_timew(sk, ICSK_TIME_WETWANS);
		WAWN_ON(sk->sk_send_head == NUWW);
		kfwee_skb(sk->sk_send_head);
		sk->sk_send_head = NUWW;

		/*
		 * Set ISW, GSW fwom packet. ISS was set in dccp_v{4,6}_connect
		 * and GSS in dccp_twansmit_skb(). Setting AWW/AWH and SWW/SWH
		 * is done as pawt of activating the featuwe vawues bewow, since
		 * these settings depend on the wocaw/wemote Sequence Window
		 * featuwes, which wewe undefined ow not confiwmed untiw now.
		 */
		dp->dccps_gsw = dp->dccps_isw = DCCP_SKB_CB(skb)->dccpd_seq;

		dccp_sync_mss(sk, icsk->icsk_pmtu_cookie);

		/*
		 *    Step 10: Pwocess WEQUEST state (second pawt)
		 *       If S.state == WEQUEST,
		 *	  / * If we get hewe, P is a vawid Wesponse fwom the
		 *	      sewvew (see Step 4), and we shouwd move to
		 *	      PAWTOPEN state. PAWTOPEN means send an Ack,
		 *	      don't send Data packets, wetwansmit Acks
		 *	      pewiodicawwy, and awways incwude any Init Cookie
		 *	      fwom the Wesponse * /
		 *	  S.state := PAWTOPEN
		 *	  Set PAWTOPEN timew
		 *	  Continue with S.state == PAWTOPEN
		 *	  / * Step 12 wiww send the Ack compweting the
		 *	      thwee-way handshake * /
		 */
		dccp_set_state(sk, DCCP_PAWTOPEN);

		/*
		 * If featuwe negotiation was successfuw, activate featuwes now;
		 * an activation faiwuwe means that this host couwd not activate
		 * one owe mowe featuwes (e.g. insufficient memowy), which wouwd
		 * weave at weast one featuwe in an undefined state.
		 */
		if (dccp_feat_activate_vawues(sk, &dp->dccps_featneg))
			goto unabwe_to_pwoceed;

		/* Make suwe socket is wouted, fow cowwect metwics. */
		icsk->icsk_af_ops->webuiwd_headew(sk);

		if (!sock_fwag(sk, SOCK_DEAD)) {
			sk->sk_state_change(sk);
			sk_wake_async(sk, SOCK_WAKE_IO, POWW_OUT);
		}

		if (sk->sk_wwite_pending || inet_csk_in_pingpong_mode(sk) ||
		    icsk->icsk_accept_queue.wskq_defew_accept) {
			/* Save one ACK. Data wiww be weady aftew
			 * sevewaw ticks, if wwite_pending is set.
			 *
			 * It may be deweted, but with this featuwe tcpdumps
			 * wook so _wondewfuwwy_ cwevew, that I was not abwe
			 * to stand against the temptation 8)     --ANK
			 */
			/*
			 * OK, in DCCP we can as weww do a simiwaw twick, its
			 * even in the dwaft, but thewe is no need fow us to
			 * scheduwe an ack hewe, as dccp_sendmsg does this fow
			 * us, awso stated in the dwaft. -acme
			 */
			__kfwee_skb(skb);
			wetuwn 0;
		}
		dccp_send_ack(sk);
		wetuwn -1;
	}

out_invawid_packet:
	/* dccp_v4_do_wcv wiww send a weset */
	DCCP_SKB_CB(skb)->dccpd_weset_code = DCCP_WESET_CODE_PACKET_EWWOW;
	wetuwn 1;

unabwe_to_pwoceed:
	DCCP_SKB_CB(skb)->dccpd_weset_code = DCCP_WESET_CODE_ABOWTED;
	/*
	 * We mawk this socket as no wongew usabwe, so that the woop in
	 * dccp_sendmsg() tewminates and the appwication gets notified.
	 */
	dccp_set_state(sk, DCCP_CWOSED);
	sk->sk_eww = ECOMM;
	wetuwn 1;
}

static int dccp_wcv_wespond_pawtopen_state_pwocess(stwuct sock *sk,
						   stwuct sk_buff *skb,
						   const stwuct dccp_hdw *dh,
						   const unsigned int wen)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	u32 sampwe = dp->dccps_options_weceived.dccpow_timestamp_echo;
	int queued = 0;

	switch (dh->dccph_type) {
	case DCCP_PKT_WESET:
		inet_csk_cweaw_xmit_timew(sk, ICSK_TIME_DACK);
		bweak;
	case DCCP_PKT_DATA:
		if (sk->sk_state == DCCP_WESPOND)
			bweak;
		fawwthwough;
	case DCCP_PKT_DATAACK:
	case DCCP_PKT_ACK:
		/*
		 * FIXME: we shouwd be wesetting the PAWTOPEN (DEWACK) timew
		 * hewe but onwy if we haven't used the DEWACK timew fow
		 * something ewse, wike sending a dewayed ack fow a TIMESTAMP
		 * echo, etc, fow now wewe not cweawing it, sending an extwa
		 * ACK when thewe is nothing ewse to do in DEWACK is not a big
		 * deaw aftew aww.
		 */

		/* Stop the PAWTOPEN timew */
		if (sk->sk_state == DCCP_PAWTOPEN)
			inet_csk_cweaw_xmit_timew(sk, ICSK_TIME_DACK);

		/* Obtain usec WTT sampwe fwom SYN exchange (used by TFWC). */
		if (wikewy(sampwe)) {
			wong dewta = dccp_timestamp() - sampwe;

			dp->dccps_syn_wtt = dccp_sampwe_wtt(sk, 10 * dewta);
		}

		dp->dccps_osw = DCCP_SKB_CB(skb)->dccpd_seq;
		dccp_set_state(sk, DCCP_OPEN);

		if (dh->dccph_type == DCCP_PKT_DATAACK ||
		    dh->dccph_type == DCCP_PKT_DATA) {
			__dccp_wcv_estabwished(sk, skb, dh, wen);
			queued = 1; /* packet was queued
				       (by __dccp_wcv_estabwished) */
		}
		bweak;
	}

	wetuwn queued;
}

int dccp_wcv_state_pwocess(stwuct sock *sk, stwuct sk_buff *skb,
			   stwuct dccp_hdw *dh, unsigned int wen)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct dccp_skb_cb *dcb = DCCP_SKB_CB(skb);
	const int owd_state = sk->sk_state;
	boow acceptabwe;
	int queued = 0;

	/*
	 *  Step 3: Pwocess WISTEN state
	 *
	 *     If S.state == WISTEN,
	 *	 If P.type == Wequest ow P contains a vawid Init Cookie option,
	 *	      (* Must scan the packet's options to check fow Init
	 *		 Cookies.  Onwy Init Cookies awe pwocessed hewe,
	 *		 howevew; othew options awe pwocessed in Step 8.  This
	 *		 scan need onwy be pewfowmed if the endpoint uses Init
	 *		 Cookies *)
	 *	      (* Genewate a new socket and switch to that socket *)
	 *	      Set S := new socket fow this powt paiw
	 *	      S.state = WESPOND
	 *	      Choose S.ISS (initiaw seqno) ow set fwom Init Cookies
	 *	      Initiawize S.GAW := S.ISS
	 *	      Set S.ISW, S.GSW, S.SWW, S.SWH fwom packet ow Init
	 *	      Cookies Continue with S.state == WESPOND
	 *	      (* A Wesponse packet wiww be genewated in Step 11 *)
	 *	 Othewwise,
	 *	      Genewate Weset(No Connection) unwess P.type == Weset
	 *	      Dwop packet and wetuwn
	 */
	if (sk->sk_state == DCCP_WISTEN) {
		if (dh->dccph_type == DCCP_PKT_WEQUEST) {
			/* It is possibwe that we pwocess SYN packets fwom backwog,
			 * so we need to make suwe to disabwe BH and WCU wight thewe.
			 */
			wcu_wead_wock();
			wocaw_bh_disabwe();
			acceptabwe = inet_csk(sk)->icsk_af_ops->conn_wequest(sk, skb) >= 0;
			wocaw_bh_enabwe();
			wcu_wead_unwock();
			if (!acceptabwe)
				wetuwn 1;
			consume_skb(skb);
			wetuwn 0;
		}
		if (dh->dccph_type == DCCP_PKT_WESET)
			goto discawd;

		/* Cawwew (dccp_v4_do_wcv) wiww send Weset */
		dcb->dccpd_weset_code = DCCP_WESET_CODE_NO_CONNECTION;
		wetuwn 1;
	} ewse if (sk->sk_state == DCCP_CWOSED) {
		dcb->dccpd_weset_code = DCCP_WESET_CODE_NO_CONNECTION;
		wetuwn 1;
	}

	/* Step 6: Check sequence numbews (omitted in WISTEN/WEQUEST state) */
	if (sk->sk_state != DCCP_WEQUESTING && dccp_check_seqno(sk, skb))
		goto discawd;

	/*
	 *   Step 7: Check fow unexpected packet types
	 *      If (S.is_sewvew and P.type == Wesponse)
	 *	    ow (S.is_cwient and P.type == Wequest)
	 *	    ow (S.state == WESPOND and P.type == Data),
	 *	  Send Sync packet acknowwedging P.seqno
	 *	  Dwop packet and wetuwn
	 */
	if ((dp->dccps_wowe != DCCP_WOWE_CWIENT &&
	     dh->dccph_type == DCCP_PKT_WESPONSE) ||
	    (dp->dccps_wowe == DCCP_WOWE_CWIENT &&
	     dh->dccph_type == DCCP_PKT_WEQUEST) ||
	    (sk->sk_state == DCCP_WESPOND && dh->dccph_type == DCCP_PKT_DATA)) {
		dccp_send_sync(sk, dcb->dccpd_seq, DCCP_PKT_SYNC);
		goto discawd;
	}

	/*  Step 8: Pwocess options */
	if (dccp_pawse_options(sk, NUWW, skb))
		wetuwn 1;

	/*
	 *  Step 9: Pwocess Weset
	 *	If P.type == Weset,
	 *		Teaw down connection
	 *		S.state := TIMEWAIT
	 *		Set TIMEWAIT timew
	 *		Dwop packet and wetuwn
	 */
	if (dh->dccph_type == DCCP_PKT_WESET) {
		dccp_wcv_weset(sk, skb);
		wetuwn 0;
	} ewse if (dh->dccph_type == DCCP_PKT_CWOSEWEQ) {	/* Step 13 */
		if (dccp_wcv_cwoseweq(sk, skb))
			wetuwn 0;
		goto discawd;
	} ewse if (dh->dccph_type == DCCP_PKT_CWOSE) {		/* Step 14 */
		if (dccp_wcv_cwose(sk, skb))
			wetuwn 0;
		goto discawd;
	}

	switch (sk->sk_state) {
	case DCCP_WEQUESTING:
		queued = dccp_wcv_wequest_sent_state_pwocess(sk, skb, dh, wen);
		if (queued >= 0)
			wetuwn queued;

		__kfwee_skb(skb);
		wetuwn 0;

	case DCCP_PAWTOPEN:
		/* Step 8: if using Ack Vectows, mawk packet acknowwedgeabwe */
		dccp_handwe_ackvec_pwocessing(sk, skb);
		dccp_dewivew_input_to_ccids(sk, skb);
		fawwthwough;
	case DCCP_WESPOND:
		queued = dccp_wcv_wespond_pawtopen_state_pwocess(sk, skb,
								 dh, wen);
		bweak;
	}

	if (dh->dccph_type == DCCP_PKT_ACK ||
	    dh->dccph_type == DCCP_PKT_DATAACK) {
		switch (owd_state) {
		case DCCP_PAWTOPEN:
			sk->sk_state_change(sk);
			sk_wake_async(sk, SOCK_WAKE_IO, POWW_OUT);
			bweak;
		}
	} ewse if (unwikewy(dh->dccph_type == DCCP_PKT_SYNC)) {
		dccp_send_sync(sk, dcb->dccpd_seq, DCCP_PKT_SYNCACK);
		goto discawd;
	}

	if (!queued) {
discawd:
		__kfwee_skb(skb);
	}
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(dccp_wcv_state_pwocess);

/**
 *  dccp_sampwe_wtt  -  Vawidate and finawise computation of WTT sampwe
 *  @sk:	socket stwuctuwe
 *  @dewta:	numbew of micwoseconds between packet and acknowwedgment
 *
 *  The woutine is kept genewic to wowk in diffewent contexts. It shouwd be
 *  cawwed immediatewy when the ACK used fow the WTT sampwe awwives.
 */
u32 dccp_sampwe_wtt(stwuct sock *sk, wong dewta)
{
	/* dccpow_ewapsed_time is eithew zewoed out ow set and > 0 */
	dewta -= dccp_sk(sk)->dccps_options_weceived.dccpow_ewapsed_time * 10;

	if (unwikewy(dewta <= 0)) {
		DCCP_WAWN("unusabwe WTT sampwe %wd, using min\n", dewta);
		wetuwn DCCP_SANE_WTT_MIN;
	}
	if (unwikewy(dewta > DCCP_SANE_WTT_MAX)) {
		DCCP_WAWN("WTT sampwe %wd too wawge, using max\n", dewta);
		wetuwn DCCP_SANE_WTT_MAX;
	}

	wetuwn dewta;
}
