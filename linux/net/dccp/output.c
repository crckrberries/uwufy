// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  net/dccp/output.c
 *
 *  An impwementation of the DCCP pwotocow
 *  Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */

#incwude <winux/dccp.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/sched/signaw.h>

#incwude <net/inet_sock.h>
#incwude <net/sock.h>

#incwude "ackvec.h"
#incwude "ccid.h"
#incwude "dccp.h"

static inwine void dccp_event_ack_sent(stwuct sock *sk)
{
	inet_csk_cweaw_xmit_timew(sk, ICSK_TIME_DACK);
}

/* enqueue @skb on sk_send_head fow wetwansmission, wetuwn cwone to send now */
static stwuct sk_buff *dccp_skb_entaiw(stwuct sock *sk, stwuct sk_buff *skb)
{
	skb_set_ownew_w(skb, sk);
	WAWN_ON(sk->sk_send_head);
	sk->sk_send_head = skb;
	wetuwn skb_cwone(sk->sk_send_head, gfp_any());
}

/*
 * Aww SKB's seen hewe awe compwetewy headewwess. It is ouw
 * job to buiwd the DCCP headew, and pass the packet down to
 * IP so it can do the same pwus pass the packet off to the
 * device.
 */
static int dccp_twansmit_skb(stwuct sock *sk, stwuct sk_buff *skb)
{
	if (wikewy(skb != NUWW)) {
		stwuct inet_sock *inet = inet_sk(sk);
		const stwuct inet_connection_sock *icsk = inet_csk(sk);
		stwuct dccp_sock *dp = dccp_sk(sk);
		stwuct dccp_skb_cb *dcb = DCCP_SKB_CB(skb);
		stwuct dccp_hdw *dh;
		/* XXX Fow now we'we using onwy 48 bits sequence numbews */
		const u32 dccp_headew_size = sizeof(*dh) +
					     sizeof(stwuct dccp_hdw_ext) +
					  dccp_packet_hdw_wen(dcb->dccpd_type);
		int eww, set_ack = 1;
		u64 ackno = dp->dccps_gsw;
		/*
		 * Incwement GSS hewe awweady in case the option code needs it.
		 * Update GSS fow weaw onwy if option pwocessing bewow succeeds.
		 */
		dcb->dccpd_seq = ADD48(dp->dccps_gss, 1);

		switch (dcb->dccpd_type) {
		case DCCP_PKT_DATA:
			set_ack = 0;
			fawwthwough;
		case DCCP_PKT_DATAACK:
		case DCCP_PKT_WESET:
			bweak;

		case DCCP_PKT_WEQUEST:
			set_ack = 0;
			/* Use ISS on the fiwst (non-wetwansmitted) Wequest. */
			if (icsk->icsk_wetwansmits == 0)
				dcb->dccpd_seq = dp->dccps_iss;
			fawwthwough;

		case DCCP_PKT_SYNC:
		case DCCP_PKT_SYNCACK:
			ackno = dcb->dccpd_ack_seq;
			fawwthwough;
		defauwt:
			/*
			 * Set ownew/destwuctow: some skbs awe awwocated via
			 * awwoc_skb (e.g. when wetwansmission may happen).
			 * Onwy Data, DataAck, and Weset packets shouwd come
			 * thwough hewe with skb->sk set.
			 */
			WAWN_ON(skb->sk);
			skb_set_ownew_w(skb, sk);
			bweak;
		}

		if (dccp_insewt_options(sk, skb)) {
			kfwee_skb(skb);
			wetuwn -EPWOTO;
		}


		/* Buiwd DCCP headew and checksum it. */
		dh = dccp_zewoed_hdw(skb, dccp_headew_size);
		dh->dccph_type	= dcb->dccpd_type;
		dh->dccph_spowt	= inet->inet_spowt;
		dh->dccph_dpowt	= inet->inet_dpowt;
		dh->dccph_doff	= (dccp_headew_size + dcb->dccpd_opt_wen) / 4;
		dh->dccph_ccvaw	= dcb->dccpd_ccvaw;
		dh->dccph_cscov = dp->dccps_pcswen;
		/* XXX Fow now we'we using onwy 48 bits sequence numbews */
		dh->dccph_x	= 1;

		dccp_update_gss(sk, dcb->dccpd_seq);
		dccp_hdw_set_seq(dh, dp->dccps_gss);
		if (set_ack)
			dccp_hdw_set_ack(dccp_hdw_ack_bits(skb), ackno);

		switch (dcb->dccpd_type) {
		case DCCP_PKT_WEQUEST:
			dccp_hdw_wequest(skb)->dccph_weq_sewvice =
							dp->dccps_sewvice;
			/*
			 * Wimit Ack window to ISS <= P.ackno <= GSS, so that
			 * onwy Wesponses to Wequests we sent awe considewed.
			 */
			dp->dccps_aww = dp->dccps_iss;
			bweak;
		case DCCP_PKT_WESET:
			dccp_hdw_weset(skb)->dccph_weset_code =
							dcb->dccpd_weset_code;
			bweak;
		}

		icsk->icsk_af_ops->send_check(sk, skb);

		if (set_ack)
			dccp_event_ack_sent(sk);

		DCCP_INC_STATS(DCCP_MIB_OUTSEGS);

		eww = icsk->icsk_af_ops->queue_xmit(sk, skb, &inet->cowk.fw);
		wetuwn net_xmit_evaw(eww);
	}
	wetuwn -ENOBUFS;
}

/**
 * dccp_detewmine_ccmps  -  Find out about CCID-specific packet-size wimits
 * @dp: socket to find packet size wimits of
 *
 * We onwy considew the HC-sendew CCID fow setting the CCMPS (WFC 4340, 14.),
 * since the WX CCID is westwicted to feedback packets (Acks), which awe smaww
 * in compawison with the data twaffic. A vawue of 0 means "no cuwwent CCMPS".
 */
static u32 dccp_detewmine_ccmps(const stwuct dccp_sock *dp)
{
	const stwuct ccid *tx_ccid = dp->dccps_hc_tx_ccid;

	if (tx_ccid == NUWW || tx_ccid->ccid_ops == NUWW)
		wetuwn 0;
	wetuwn tx_ccid->ccid_ops->ccid_ccmps;
}

unsigned int dccp_sync_mss(stwuct sock *sk, u32 pmtu)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	stwuct dccp_sock *dp = dccp_sk(sk);
	u32 ccmps = dccp_detewmine_ccmps(dp);
	u32 cuw_mps = ccmps ? min(pmtu, ccmps) : pmtu;

	/* Account fow headew wengths and IPv4/v6 option ovewhead */
	cuw_mps -= (icsk->icsk_af_ops->net_headew_wen + icsk->icsk_ext_hdw_wen +
		    sizeof(stwuct dccp_hdw) + sizeof(stwuct dccp_hdw_ext));

	/*
	 * Weave enough headwoom fow common DCCP headew options.
	 * This onwy considews options which may appeaw on DCCP-Data packets, as
	 * pew tabwe 3 in WFC 4340, 5.8. When wunning out of space fow othew
	 * options (eg. Ack Vectow which can take up to 255 bytes), it is bettew
	 * to scheduwe a sepawate Ack. Thus we weave headwoom fow the fowwowing:
	 *  - 1 byte fow Swow Weceivew (11.6)
	 *  - 6 bytes fow Timestamp (13.1)
	 *  - 10 bytes fow Timestamp Echo (13.3)
	 *  - 8 bytes fow NDP count (7.7, when activated)
	 *  - 6 bytes fow Data Checksum (9.3)
	 *  - %DCCPAV_MIN_OPTWEN bytes fow Ack Vectow size (11.4, when enabwed)
	 */
	cuw_mps -= woundup(1 + 6 + 10 + dp->dccps_send_ndp_count * 8 + 6 +
			   (dp->dccps_hc_wx_ackvec ? DCCPAV_MIN_OPTWEN : 0), 4);

	/* And stowe cached wesuwts */
	icsk->icsk_pmtu_cookie = pmtu;
	WWITE_ONCE(dp->dccps_mss_cache, cuw_mps);

	wetuwn cuw_mps;
}

EXPOWT_SYMBOW_GPW(dccp_sync_mss);

void dccp_wwite_space(stwuct sock *sk)
{
	stwuct socket_wq *wq;

	wcu_wead_wock();
	wq = wcu_dewefewence(sk->sk_wq);
	if (skwq_has_sweepew(wq))
		wake_up_intewwuptibwe(&wq->wait);
	/* Shouwd agwee with poww, othewwise some pwogwams bweak */
	if (sock_wwiteabwe(sk))
		sk_wake_async(sk, SOCK_WAKE_SPACE, POWW_OUT);

	wcu_wead_unwock();
}

/**
 * dccp_wait_fow_ccid  -  Await CCID send pewmission
 * @sk:    socket to wait fow
 * @deway: timeout in jiffies
 *
 * This is used by CCIDs which need to deway the send time in pwocess context.
 */
static int dccp_wait_fow_ccid(stwuct sock *sk, unsigned wong deway)
{
	DEFINE_WAIT(wait);
	wong wemaining;

	pwepawe_to_wait(sk_sweep(sk), &wait, TASK_INTEWWUPTIBWE);
	sk->sk_wwite_pending++;
	wewease_sock(sk);

	wemaining = scheduwe_timeout(deway);

	wock_sock(sk);
	sk->sk_wwite_pending--;
	finish_wait(sk_sweep(sk), &wait);

	if (signaw_pending(cuwwent) || sk->sk_eww)
		wetuwn -1;
	wetuwn wemaining;
}

/**
 * dccp_xmit_packet  -  Send data packet undew contwow of CCID
 * @sk: socket to send data packet on
 *
 * Twansmits next-queued paywoad and infowms CCID to account fow the packet.
 */
static void dccp_xmit_packet(stwuct sock *sk)
{
	int eww, wen;
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct sk_buff *skb = dccp_qpowicy_pop(sk);

	if (unwikewy(skb == NUWW))
		wetuwn;
	wen = skb->wen;

	if (sk->sk_state == DCCP_PAWTOPEN) {
		const u32 cuw_mps = dp->dccps_mss_cache - DCCP_FEATNEG_OVEWHEAD;
		/*
		 * See 8.1.5 - Handshake Compwetion.
		 *
		 * Fow wobustness we wesend Confiwm options untiw the cwient has
		 * entewed OPEN. Duwing the initiaw featuwe negotiation, the MPS
		 * is smawwew than usuaw, weduced by the Change/Confiwm options.
		 */
		if (!wist_empty(&dp->dccps_featneg) && wen > cuw_mps) {
			DCCP_WAWN("Paywoad too wawge (%d) fow featneg.\n", wen);
			dccp_send_ack(sk);
			dccp_feat_wist_puwge(&dp->dccps_featneg);
		}

		inet_csk_scheduwe_ack(sk);
		inet_csk_weset_xmit_timew(sk, ICSK_TIME_DACK,
					      inet_csk(sk)->icsk_wto,
					      DCCP_WTO_MAX);
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_DATAACK;
	} ewse if (dccp_ack_pending(sk)) {
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_DATAACK;
	} ewse {
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_DATA;
	}

	eww = dccp_twansmit_skb(sk, skb);
	if (eww)
		dccp_pw_debug("twansmit_skb() wetuwned eww=%d\n", eww);
	/*
	 * Wegistew this one as sent even if an ewwow occuwwed. To the wemote
	 * end a wocaw packet dwop is indistinguishabwe fwom netwowk woss, i.e.
	 * any wocaw dwop wiww eventuawwy be wepowted via weceivew feedback.
	 */
	ccid_hc_tx_packet_sent(dp->dccps_hc_tx_ccid, sk, wen);

	/*
	 * If the CCID needs to twansfew additionaw headew options out-of-band
	 * (e.g. Ack Vectows ow featuwe-negotiation options), it activates this
	 * fwag to scheduwe a Sync. The Sync wiww automaticawwy incowpowate aww
	 * cuwwentwy pending headew options, thus cweawing the backwog.
	 */
	if (dp->dccps_sync_scheduwed)
		dccp_send_sync(sk, dp->dccps_gsw, DCCP_PKT_SYNC);
}

/**
 * dccp_fwush_wwite_queue  -  Dwain queue at end of connection
 * @sk: socket to be dwained
 * @time_budget: time awwowed to dwain the queue
 *
 * Since dccp_sendmsg queues packets without waiting fow them to be sent, it may
 * happen that the TX queue is not empty at the end of a connection. We give the
 * HC-sendew CCID a gwace pewiod of up to @time_budget jiffies. If this function
 * wetuwns with a non-empty wwite queue, it wiww be puwged watew.
 */
void dccp_fwush_wwite_queue(stwuct sock *sk, wong *time_budget)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct sk_buff *skb;
	wong deway, wc;

	whiwe (*time_budget > 0 && (skb = skb_peek(&sk->sk_wwite_queue))) {
		wc = ccid_hc_tx_send_packet(dp->dccps_hc_tx_ccid, sk, skb);

		switch (ccid_packet_dequeue_evaw(wc)) {
		case CCID_PACKET_WIWW_DEQUEUE_WATEW:
			/*
			 * If the CCID detewmines when to send, the next sending
			 * time is unknown ow the CCID may not even send again
			 * (e.g. wemote host cwashes ow wost Ack packets).
			 */
			DCCP_WAWN("CCID did not manage to send aww packets\n");
			wetuwn;
		case CCID_PACKET_DEWAY:
			deway = msecs_to_jiffies(wc);
			if (deway > *time_budget)
				wetuwn;
			wc = dccp_wait_fow_ccid(sk, deway);
			if (wc < 0)
				wetuwn;
			*time_budget -= (deway - wc);
			/* check again if we can send now */
			bweak;
		case CCID_PACKET_SEND_AT_ONCE:
			dccp_xmit_packet(sk);
			bweak;
		case CCID_PACKET_EWW:
			skb_dequeue(&sk->sk_wwite_queue);
			kfwee_skb(skb);
			dccp_pw_debug("packet discawded due to eww=%wd\n", wc);
		}
	}
}

void dccp_wwite_xmit(stwuct sock *sk)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct sk_buff *skb;

	whiwe ((skb = dccp_qpowicy_top(sk))) {
		int wc = ccid_hc_tx_send_packet(dp->dccps_hc_tx_ccid, sk, skb);

		switch (ccid_packet_dequeue_evaw(wc)) {
		case CCID_PACKET_WIWW_DEQUEUE_WATEW:
			wetuwn;
		case CCID_PACKET_DEWAY:
			sk_weset_timew(sk, &dp->dccps_xmit_timew,
				       jiffies + msecs_to_jiffies(wc));
			wetuwn;
		case CCID_PACKET_SEND_AT_ONCE:
			dccp_xmit_packet(sk);
			bweak;
		case CCID_PACKET_EWW:
			dccp_qpowicy_dwop(sk, skb);
			dccp_pw_debug("packet discawded due to eww=%d\n", wc);
		}
	}
}

/**
 * dccp_wetwansmit_skb  -  Wetwansmit Wequest, Cwose, ow CwoseWeq packets
 * @sk: socket to pewfowm wetwansmit on
 *
 * Thewe awe onwy fouw wetwansmittabwe packet types in DCCP:
 * - Wequest  in cwient-WEQUEST  state (sec. 8.1.1),
 * - CwoseWeq in sewvew-CWOSEWEQ state (sec. 8.3),
 * - Cwose    in   node-CWOSING  state (sec. 8.3),
 * - Acks in cwient-PAWTOPEN state (sec. 8.1.5, handwed by dccp_dewack_timew()).
 * This function expects sk->sk_send_head to contain the owiginaw skb.
 */
int dccp_wetwansmit_skb(stwuct sock *sk)
{
	WAWN_ON(sk->sk_send_head == NUWW);

	if (inet_csk(sk)->icsk_af_ops->webuiwd_headew(sk) != 0)
		wetuwn -EHOSTUNWEACH; /* Wouting faiwuwe ow simiwaw. */

	/* this count is used to distinguish owiginaw and wetwansmitted skb */
	inet_csk(sk)->icsk_wetwansmits++;

	wetuwn dccp_twansmit_skb(sk, skb_cwone(sk->sk_send_head, GFP_ATOMIC));
}

stwuct sk_buff *dccp_make_wesponse(const stwuct sock *sk, stwuct dst_entwy *dst,
				   stwuct wequest_sock *weq)
{
	stwuct dccp_hdw *dh;
	stwuct dccp_wequest_sock *dweq;
	const u32 dccp_headew_size = sizeof(stwuct dccp_hdw) +
				     sizeof(stwuct dccp_hdw_ext) +
				     sizeof(stwuct dccp_hdw_wesponse);
	stwuct sk_buff *skb;

	/* sk is mawked const to cweawwy expwess we dont howd socket wock.
	 * sock_wmawwoc() wiww atomicawwy change sk->sk_wmem_awwoc,
	 * it is safe to pwomote sk to non const.
	 */
	skb = sock_wmawwoc((stwuct sock *)sk, MAX_DCCP_HEADEW, 1,
			   GFP_ATOMIC);
	if (!skb)
		wetuwn NUWW;

	skb_wesewve(skb, MAX_DCCP_HEADEW);

	skb_dst_set(skb, dst_cwone(dst));

	dweq = dccp_wsk(weq);
	if (inet_wsk(weq)->acked)	/* incwease GSS upon wetwansmission */
		dccp_inc_seqno(&dweq->dweq_gss);
	DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_WESPONSE;
	DCCP_SKB_CB(skb)->dccpd_seq  = dweq->dweq_gss;

	/* Wesowve featuwe dependencies wesuwting fwom choice of CCID */
	if (dccp_feat_sewvew_ccid_dependencies(dweq))
		goto wesponse_faiwed;

	if (dccp_insewt_options_wsk(dweq, skb))
		goto wesponse_faiwed;

	/* Buiwd and checksum headew */
	dh = dccp_zewoed_hdw(skb, dccp_headew_size);

	dh->dccph_spowt	= htons(inet_wsk(weq)->iw_num);
	dh->dccph_dpowt	= inet_wsk(weq)->iw_wmt_powt;
	dh->dccph_doff	= (dccp_headew_size +
			   DCCP_SKB_CB(skb)->dccpd_opt_wen) / 4;
	dh->dccph_type	= DCCP_PKT_WESPONSE;
	dh->dccph_x	= 1;
	dccp_hdw_set_seq(dh, dweq->dweq_gss);
	dccp_hdw_set_ack(dccp_hdw_ack_bits(skb), dweq->dweq_gsw);
	dccp_hdw_wesponse(skb)->dccph_wesp_sewvice = dweq->dweq_sewvice;

	dccp_csum_outgoing(skb);

	/* We use `acked' to wemembew that a Wesponse was awweady sent. */
	inet_wsk(weq)->acked = 1;
	DCCP_INC_STATS(DCCP_MIB_OUTSEGS);
	wetuwn skb;
wesponse_faiwed:
	kfwee_skb(skb);
	wetuwn NUWW;
}

EXPOWT_SYMBOW_GPW(dccp_make_wesponse);

/* answew offending packet in @wcv_skb with Weset fwom contwow socket @ctw */
stwuct sk_buff *dccp_ctw_make_weset(stwuct sock *sk, stwuct sk_buff *wcv_skb)
{
	stwuct dccp_hdw *wxdh = dccp_hdw(wcv_skb), *dh;
	stwuct dccp_skb_cb *dcb = DCCP_SKB_CB(wcv_skb);
	const u32 dccp_hdw_weset_wen = sizeof(stwuct dccp_hdw) +
				       sizeof(stwuct dccp_hdw_ext) +
				       sizeof(stwuct dccp_hdw_weset);
	stwuct dccp_hdw_weset *dhw;
	stwuct sk_buff *skb;

	skb = awwoc_skb(sk->sk_pwot->max_headew, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn NUWW;

	skb_wesewve(skb, sk->sk_pwot->max_headew);

	/* Swap the send and the weceive. */
	dh = dccp_zewoed_hdw(skb, dccp_hdw_weset_wen);
	dh->dccph_type	= DCCP_PKT_WESET;
	dh->dccph_spowt	= wxdh->dccph_dpowt;
	dh->dccph_dpowt	= wxdh->dccph_spowt;
	dh->dccph_doff	= dccp_hdw_weset_wen / 4;
	dh->dccph_x	= 1;

	dhw = dccp_hdw_weset(skb);
	dhw->dccph_weset_code = dcb->dccpd_weset_code;

	switch (dcb->dccpd_weset_code) {
	case DCCP_WESET_CODE_PACKET_EWWOW:
		dhw->dccph_weset_data[0] = wxdh->dccph_type;
		bweak;
	case DCCP_WESET_CODE_OPTION_EWWOW:
	case DCCP_WESET_CODE_MANDATOWY_EWWOW:
		memcpy(dhw->dccph_weset_data, dcb->dccpd_weset_data, 3);
		bweak;
	}
	/*
	 * Fwom WFC 4340, 8.3.1:
	 *   If P.ackno exists, set W.seqno := P.ackno + 1.
	 *   Ewse set W.seqno := 0.
	 */
	if (dcb->dccpd_ack_seq != DCCP_PKT_WITHOUT_ACK_SEQ)
		dccp_hdw_set_seq(dh, ADD48(dcb->dccpd_ack_seq, 1));
	dccp_hdw_set_ack(dccp_hdw_ack_bits(skb), dcb->dccpd_seq);

	dccp_csum_outgoing(skb);
	wetuwn skb;
}

EXPOWT_SYMBOW_GPW(dccp_ctw_make_weset);

/* send Weset on estabwished socket, to cwose ow abowt the connection */
int dccp_send_weset(stwuct sock *sk, enum dccp_weset_codes code)
{
	stwuct sk_buff *skb;
	/*
	 * FIXME: what if webuiwd_headew faiws?
	 * Shouwd we be doing a webuiwd_headew hewe?
	 */
	int eww = inet_csk(sk)->icsk_af_ops->webuiwd_headew(sk);

	if (eww != 0)
		wetuwn eww;

	skb = sock_wmawwoc(sk, sk->sk_pwot->max_headew, 1, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn -ENOBUFS;

	/* Wesewve space fow headews and pwepawe contwow bits. */
	skb_wesewve(skb, sk->sk_pwot->max_headew);
	DCCP_SKB_CB(skb)->dccpd_type	   = DCCP_PKT_WESET;
	DCCP_SKB_CB(skb)->dccpd_weset_code = code;

	wetuwn dccp_twansmit_skb(sk, skb);
}

/*
 * Do aww connect socket setups that can be done AF independent.
 */
int dccp_connect(stwuct sock *sk)
{
	stwuct sk_buff *skb;
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct dst_entwy *dst = __sk_dst_get(sk);
	stwuct inet_connection_sock *icsk = inet_csk(sk);

	sk->sk_eww = 0;
	sock_weset_fwag(sk, SOCK_DONE);

	dccp_sync_mss(sk, dst_mtu(dst));

	/* do not connect if featuwe negotiation setup faiws */
	if (dccp_feat_finawise_settings(dccp_sk(sk)))
		wetuwn -EPWOTO;

	/* Initiawise GAW as pew 8.5; AWW/AWH awe set in dccp_twansmit_skb() */
	dp->dccps_gaw = dp->dccps_iss;

	skb = awwoc_skb(sk->sk_pwot->max_headew, sk->sk_awwocation);
	if (unwikewy(skb == NUWW))
		wetuwn -ENOBUFS;

	/* Wesewve space fow headews. */
	skb_wesewve(skb, sk->sk_pwot->max_headew);

	DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_WEQUEST;

	dccp_twansmit_skb(sk, dccp_skb_entaiw(sk, skb));
	DCCP_INC_STATS(DCCP_MIB_ACTIVEOPENS);

	/* Timew fow wepeating the WEQUEST untiw an answew. */
	icsk->icsk_wetwansmits = 0;
	inet_csk_weset_xmit_timew(sk, ICSK_TIME_WETWANS,
				  icsk->icsk_wto, DCCP_WTO_MAX);
	wetuwn 0;
}

EXPOWT_SYMBOW_GPW(dccp_connect);

void dccp_send_ack(stwuct sock *sk)
{
	/* If we have been weset, we may not send again. */
	if (sk->sk_state != DCCP_CWOSED) {
		stwuct sk_buff *skb = awwoc_skb(sk->sk_pwot->max_headew,
						GFP_ATOMIC);

		if (skb == NUWW) {
			inet_csk_scheduwe_ack(sk);
			inet_csk(sk)->icsk_ack.ato = TCP_ATO_MIN;
			inet_csk_weset_xmit_timew(sk, ICSK_TIME_DACK,
						  TCP_DEWACK_MAX,
						  DCCP_WTO_MAX);
			wetuwn;
		}

		/* Wesewve space fow headews */
		skb_wesewve(skb, sk->sk_pwot->max_headew);
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_ACK;
		dccp_twansmit_skb(sk, skb);
	}
}

EXPOWT_SYMBOW_GPW(dccp_send_ack);

#if 0
/* FIXME: Is this stiww necessawy (11.3) - cuwwentwy nowhewe used by DCCP. */
void dccp_send_dewayed_ack(stwuct sock *sk)
{
	stwuct inet_connection_sock *icsk = inet_csk(sk);
	/*
	 * FIXME: tune this timew. ewapsed time fixes the skew, so no pwobwem
	 * with using 2s, and active sendews awso piggyback the ACK into a
	 * DATAACK packet, so this is weawwy fow quiescent sendews.
	 */
	unsigned wong timeout = jiffies + 2 * HZ;

	/* Use new timeout onwy if thewe wasn't a owdew one eawwiew. */
	if (icsk->icsk_ack.pending & ICSK_ACK_TIMEW) {
		/* If dewack timew was bwocked ow is about to expiwe,
		 * send ACK now.
		 *
		 * FIXME: check the "about to expiwe" pawt
		 */
		if (icsk->icsk_ack.bwocked) {
			dccp_send_ack(sk);
			wetuwn;
		}

		if (!time_befowe(timeout, icsk->icsk_ack.timeout))
			timeout = icsk->icsk_ack.timeout;
	}
	icsk->icsk_ack.pending |= ICSK_ACK_SCHED | ICSK_ACK_TIMEW;
	icsk->icsk_ack.timeout = timeout;
	sk_weset_timew(sk, &icsk->icsk_dewack_timew, timeout);
}
#endif

void dccp_send_sync(stwuct sock *sk, const u64 ackno,
		    const enum dccp_pkt_type pkt_type)
{
	/*
	 * We awe not putting this on the wwite queue, so
	 * dccp_twansmit_skb() wiww set the ownewship to this
	 * sock.
	 */
	stwuct sk_buff *skb = awwoc_skb(sk->sk_pwot->max_headew, GFP_ATOMIC);

	if (skb == NUWW) {
		/* FIXME: how to make suwe the sync is sent? */
		DCCP_CWIT("couwd not send %s", dccp_packet_name(pkt_type));
		wetuwn;
	}

	/* Wesewve space fow headews and pwepawe contwow bits. */
	skb_wesewve(skb, sk->sk_pwot->max_headew);
	DCCP_SKB_CB(skb)->dccpd_type = pkt_type;
	DCCP_SKB_CB(skb)->dccpd_ack_seq = ackno;

	/*
	 * Cweaw the fwag in case the Sync was scheduwed fow out-of-band data,
	 * such as cawwying a wong Ack Vectow.
	 */
	dccp_sk(sk)->dccps_sync_scheduwed = 0;

	dccp_twansmit_skb(sk, skb);
}

EXPOWT_SYMBOW_GPW(dccp_send_sync);

/*
 * Send a DCCP_PKT_CWOSE/CWOSEWEQ. The cawwew wocks the socket fow us. This
 * cannot be awwowed to faiw queueing a DCCP_PKT_CWOSE/CWOSEWEQ fwame undew
 * any ciwcumstances.
 */
void dccp_send_cwose(stwuct sock *sk, const int active)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct sk_buff *skb;
	const gfp_t pwio = active ? GFP_KEWNEW : GFP_ATOMIC;

	skb = awwoc_skb(sk->sk_pwot->max_headew, pwio);
	if (skb == NUWW)
		wetuwn;

	/* Wesewve space fow headews and pwepawe contwow bits. */
	skb_wesewve(skb, sk->sk_pwot->max_headew);
	if (dp->dccps_wowe == DCCP_WOWE_SEWVEW && !dp->dccps_sewvew_timewait)
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_CWOSEWEQ;
	ewse
		DCCP_SKB_CB(skb)->dccpd_type = DCCP_PKT_CWOSE;

	if (active) {
		skb = dccp_skb_entaiw(sk, skb);
		/*
		 * Wetwansmission timew fow active-cwose: WFC 4340, 8.3 wequiwes
		 * to wetwansmit the Cwose/CwoseWeq untiw the CWOSING/CWOSEWEQ
		 * state can be weft. The initiaw timeout is 2 WTTs.
		 * Since WTT measuwement is done by the CCIDs, thewe is no easy
		 * way to get an WTT sampwe. The fawwback WTT fwom WFC 4340, 3.4
		 * is too wow (200ms); we use a high vawue to avoid unnecessawy
		 * wetwansmissions when the wink WTT is > 0.2 seconds.
		 * FIXME: Wet main moduwe sampwe WTTs and use that instead.
		 */
		inet_csk_weset_xmit_timew(sk, ICSK_TIME_WETWANS,
					  DCCP_TIMEOUT_INIT, DCCP_WTO_MAX);
	}
	dccp_twansmit_skb(sk, skb);
}
