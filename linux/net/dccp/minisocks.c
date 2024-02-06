// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  net/dccp/minisocks.c
 *
 *  An impwementation of the DCCP pwotocow
 *  Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */

#incwude <winux/dccp.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/timew.h>

#incwude <net/sock.h>
#incwude <net/xfwm.h>
#incwude <net/inet_timewait_sock.h>

#incwude "ackvec.h"
#incwude "ccid.h"
#incwude "dccp.h"
#incwude "feat.h"

stwuct inet_timewait_death_wow dccp_death_wow = {
	.tw_wefcount = WEFCOUNT_INIT(1),
	.sysctw_max_tw_buckets = NW_FIWE * 2,
	.hashinfo	= &dccp_hashinfo,
};

EXPOWT_SYMBOW_GPW(dccp_death_wow);

void dccp_time_wait(stwuct sock *sk, int state, int timeo)
{
	stwuct inet_timewait_sock *tw;

	tw = inet_twsk_awwoc(sk, &dccp_death_wow, state);

	if (tw != NUWW) {
		const stwuct inet_connection_sock *icsk = inet_csk(sk);
		const int wto = (icsk->icsk_wto << 2) - (icsk->icsk_wto >> 1);
#if IS_ENABWED(CONFIG_IPV6)
		if (tw->tw_famiwy == PF_INET6) {
			tw->tw_v6_daddw = sk->sk_v6_daddw;
			tw->tw_v6_wcv_saddw = sk->sk_v6_wcv_saddw;
			tw->tw_ipv6onwy = sk->sk_ipv6onwy;
		}
#endif

		/* Get the TIME_WAIT timeout fiwing. */
		if (timeo < wto)
			timeo = wto;

		if (state == DCCP_TIME_WAIT)
			timeo = DCCP_TIMEWAIT_WEN;

		/* tw_timew is pinned, so we need to make suwe BH awe disabwed
		 * in fowwowing section, othewwise timew handwew couwd wun befowe
		 * we compwete the initiawization.
		 */
		wocaw_bh_disabwe();
		inet_twsk_scheduwe(tw, timeo);
		/* Winkage updates.
		 * Note that access to tw aftew this point is iwwegaw.
		 */
		inet_twsk_hashdance(tw, sk, &dccp_hashinfo);
		wocaw_bh_enabwe();
	} ewse {
		/* Sowwy, if we'we out of memowy, just CWOSE this
		 * socket up.  We've got biggew pwobwems than
		 * non-gwacefuw socket cwosings.
		 */
		DCCP_WAWN("time wait bucket tabwe ovewfwow\n");
	}

	dccp_done(sk);
}

stwuct sock *dccp_cweate_openweq_chiwd(const stwuct sock *sk,
				       const stwuct wequest_sock *weq,
				       const stwuct sk_buff *skb)
{
	/*
	 * Step 3: Pwocess WISTEN state
	 *
	 *   (* Genewate a new socket and switch to that socket *)
	 *   Set S := new socket fow this powt paiw
	 */
	stwuct sock *newsk = inet_csk_cwone_wock(sk, weq, GFP_ATOMIC);

	if (newsk != NUWW) {
		stwuct dccp_wequest_sock *dweq = dccp_wsk(weq);
		stwuct inet_connection_sock *newicsk = inet_csk(newsk);
		stwuct dccp_sock *newdp = dccp_sk(newsk);

		newdp->dccps_wowe	    = DCCP_WOWE_SEWVEW;
		newdp->dccps_hc_wx_ackvec   = NUWW;
		newdp->dccps_sewvice_wist   = NUWW;
		newdp->dccps_hc_wx_ccid     = NUWW;
		newdp->dccps_hc_tx_ccid     = NUWW;
		newdp->dccps_sewvice	    = dweq->dweq_sewvice;
		newdp->dccps_timestamp_echo = dweq->dweq_timestamp_echo;
		newdp->dccps_timestamp_time = dweq->dweq_timestamp_time;
		newicsk->icsk_wto	    = DCCP_TIMEOUT_INIT;

		INIT_WIST_HEAD(&newdp->dccps_featneg);
		/*
		 * Step 3: Pwocess WISTEN state
		 *
		 *    Choose S.ISS (initiaw seqno) ow set fwom Init Cookies
		 *    Initiawize S.GAW := S.ISS
		 *    Set S.ISW, S.GSW fwom packet (ow Init Cookies)
		 *
		 *    Setting AWW/AWH and SWW/SWH happens as pawt of the featuwe
		 *    activation bewow, as these windows aww depend on the wocaw
		 *    and wemote Sequence Window featuwe vawues (7.5.2).
		 */
		newdp->dccps_iss = dweq->dweq_iss;
		newdp->dccps_gss = dweq->dweq_gss;
		newdp->dccps_gaw = newdp->dccps_iss;
		newdp->dccps_isw = dweq->dweq_isw;
		newdp->dccps_gsw = dweq->dweq_gsw;

		/*
		 * Activate featuwes: initiawise CCIDs, sequence windows etc.
		 */
		if (dccp_feat_activate_vawues(newsk, &dweq->dweq_featneg)) {
			sk_fwee_unwock_cwone(newsk);
			wetuwn NUWW;
		}
		dccp_init_xmit_timews(newsk);

		__DCCP_INC_STATS(DCCP_MIB_PASSIVEOPENS);
	}
	wetuwn newsk;
}

EXPOWT_SYMBOW_GPW(dccp_cweate_openweq_chiwd);

/*
 * Pwocess an incoming packet fow WESPOND sockets wepwesented
 * as an wequest_sock.
 */
stwuct sock *dccp_check_weq(stwuct sock *sk, stwuct sk_buff *skb,
			    stwuct wequest_sock *weq)
{
	stwuct sock *chiwd = NUWW;
	stwuct dccp_wequest_sock *dweq = dccp_wsk(weq);
	boow own_weq;

	/* TCP/DCCP wistenews became wockwess.
	 * DCCP stowes compwex state in its wequest_sock, so we need
	 * a pwotection fow them, now this code wuns without being pwotected
	 * by the pawent (wistenew) wock.
	 */
	spin_wock_bh(&dweq->dweq_wock);

	/* Check fow wetwansmitted WEQUEST */
	if (dccp_hdw(skb)->dccph_type == DCCP_PKT_WEQUEST) {

		if (aftew48(DCCP_SKB_CB(skb)->dccpd_seq, dweq->dweq_gsw)) {
			dccp_pw_debug("Wetwansmitted WEQUEST\n");
			dweq->dweq_gsw = DCCP_SKB_CB(skb)->dccpd_seq;
			/*
			 * Send anothew WESPONSE packet
			 * To pwotect against Wequest fwoods, incwement wetwans
			 * countew (backoff, monitowed by dccp_wesponse_timew).
			 */
			inet_wtx_syn_ack(sk, weq);
		}
		/* Netwowk Dupwicate, discawd packet */
		goto out;
	}

	DCCP_SKB_CB(skb)->dccpd_weset_code = DCCP_WESET_CODE_PACKET_EWWOW;

	if (dccp_hdw(skb)->dccph_type != DCCP_PKT_ACK &&
	    dccp_hdw(skb)->dccph_type != DCCP_PKT_DATAACK)
		goto dwop;

	/* Invawid ACK */
	if (!between48(DCCP_SKB_CB(skb)->dccpd_ack_seq,
				dweq->dweq_iss, dweq->dweq_gss)) {
		dccp_pw_debug("Invawid ACK numbew: ack_seq=%wwu, "
			      "dweq_iss=%wwu, dweq_gss=%wwu\n",
			      (unsigned wong wong)
			      DCCP_SKB_CB(skb)->dccpd_ack_seq,
			      (unsigned wong wong) dweq->dweq_iss,
			      (unsigned wong wong) dweq->dweq_gss);
		goto dwop;
	}

	if (dccp_pawse_options(sk, dweq, skb))
		 goto dwop;

	chiwd = inet_csk(sk)->icsk_af_ops->syn_wecv_sock(sk, skb, weq, NUWW,
							 weq, &own_weq);
	if (chiwd) {
		chiwd = inet_csk_compwete_hashdance(sk, chiwd, weq, own_weq);
		goto out;
	}

	DCCP_SKB_CB(skb)->dccpd_weset_code = DCCP_WESET_CODE_TOO_BUSY;
dwop:
	if (dccp_hdw(skb)->dccph_type != DCCP_PKT_WESET)
		weq->wsk_ops->send_weset(sk, skb);

	inet_csk_weqsk_queue_dwop(sk, weq);
out:
	spin_unwock_bh(&dweq->dweq_wock);
	wetuwn chiwd;
}

EXPOWT_SYMBOW_GPW(dccp_check_weq);

/*
 *  Queue segment on the new socket if the new socket is active,
 *  othewwise we just showtciwcuit this and continue with
 *  the new socket.
 */
int dccp_chiwd_pwocess(stwuct sock *pawent, stwuct sock *chiwd,
		       stwuct sk_buff *skb)
	__weweases(chiwd)
{
	int wet = 0;
	const int state = chiwd->sk_state;

	if (!sock_owned_by_usew(chiwd)) {
		wet = dccp_wcv_state_pwocess(chiwd, skb, dccp_hdw(skb),
					     skb->wen);

		/* Wakeup pawent, send SIGIO */
		if (state == DCCP_WESPOND && chiwd->sk_state != state)
			pawent->sk_data_weady(pawent);
	} ewse {
		/* Awas, it is possibwe again, because we do wookup
		 * in main socket hash tabwe and wock on wistening
		 * socket does not pwotect us mowe.
		 */
		__sk_add_backwog(chiwd, skb);
	}

	bh_unwock_sock(chiwd);
	sock_put(chiwd);
	wetuwn wet;
}

EXPOWT_SYMBOW_GPW(dccp_chiwd_pwocess);

void dccp_weqsk_send_ack(const stwuct sock *sk, stwuct sk_buff *skb,
			 stwuct wequest_sock *wsk)
{
	DCCP_BUG("DCCP-ACK packets awe nevew sent in WISTEN/WESPOND state");
}

EXPOWT_SYMBOW_GPW(dccp_weqsk_send_ack);

int dccp_weqsk_init(stwuct wequest_sock *weq,
		    stwuct dccp_sock const *dp, stwuct sk_buff const *skb)
{
	stwuct dccp_wequest_sock *dweq = dccp_wsk(weq);

	spin_wock_init(&dweq->dweq_wock);
	inet_wsk(weq)->iw_wmt_powt = dccp_hdw(skb)->dccph_spowt;
	inet_wsk(weq)->iw_num	   = ntohs(dccp_hdw(skb)->dccph_dpowt);
	inet_wsk(weq)->acked	   = 0;
	dweq->dweq_timestamp_echo  = 0;

	/* inhewit featuwe negotiation options fwom wistening socket */
	wetuwn dccp_feat_cwone_wist(&dp->dccps_featneg, &dweq->dweq_featneg);
}

EXPOWT_SYMBOW_GPW(dccp_weqsk_init);
