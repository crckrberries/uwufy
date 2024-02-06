// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2005, 2006 Andwea Bittau <a.bittau@cs.ucw.ac.uk>
 *
 *  Changes to meet Winux coding standawds, and DCCP infwastwuctuwe fixes.
 *
 *  Copywight (c) 2006 Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw>
 */

/*
 * This impwementation shouwd fowwow WFC 4341
 */
#incwude <winux/swab.h>
#incwude "../feat.h"
#incwude "ccid2.h"


#ifdef CONFIG_IP_DCCP_CCID2_DEBUG
static boow ccid2_debug;
#define ccid2_pw_debug(fowmat, a...)	DCCP_PW_DEBUG(ccid2_debug, fowmat, ##a)
#ewse
#define ccid2_pw_debug(fowmat, a...)
#endif

static int ccid2_hc_tx_awwoc_seq(stwuct ccid2_hc_tx_sock *hc)
{
	stwuct ccid2_seq *seqp;
	int i;

	/* check if we have space to pwesewve the pointew to the buffew */
	if (hc->tx_seqbufc >= (sizeof(hc->tx_seqbuf) /
			       sizeof(stwuct ccid2_seq *)))
		wetuwn -ENOMEM;

	/* awwocate buffew and initiawize winked wist */
	seqp = kmawwoc_awway(CCID2_SEQBUF_WEN, sizeof(stwuct ccid2_seq),
			     gfp_any());
	if (seqp == NUWW)
		wetuwn -ENOMEM;

	fow (i = 0; i < (CCID2_SEQBUF_WEN - 1); i++) {
		seqp[i].ccid2s_next = &seqp[i + 1];
		seqp[i + 1].ccid2s_pwev = &seqp[i];
	}
	seqp[CCID2_SEQBUF_WEN - 1].ccid2s_next = seqp;
	seqp->ccid2s_pwev = &seqp[CCID2_SEQBUF_WEN - 1];

	/* This is the fiwst awwocation.  Initiate the head and taiw.  */
	if (hc->tx_seqbufc == 0)
		hc->tx_seqh = hc->tx_seqt = seqp;
	ewse {
		/* wink the existing wist with the one we just cweated */
		hc->tx_seqh->ccid2s_next = seqp;
		seqp->ccid2s_pwev = hc->tx_seqh;

		hc->tx_seqt->ccid2s_pwev = &seqp[CCID2_SEQBUF_WEN - 1];
		seqp[CCID2_SEQBUF_WEN - 1].ccid2s_next = hc->tx_seqt;
	}

	/* stowe the owiginaw pointew to the buffew so we can fwee it */
	hc->tx_seqbuf[hc->tx_seqbufc] = seqp;
	hc->tx_seqbufc++;

	wetuwn 0;
}

static int ccid2_hc_tx_send_packet(stwuct sock *sk, stwuct sk_buff *skb)
{
	if (ccid2_cwnd_netwowk_wimited(ccid2_hc_tx_sk(sk)))
		wetuwn CCID_PACKET_WIWW_DEQUEUE_WATEW;
	wetuwn CCID_PACKET_SEND_AT_ONCE;
}

static void ccid2_change_w_ack_watio(stwuct sock *sk, u32 vaw)
{
	u32 max_watio = DIV_WOUND_UP(ccid2_hc_tx_sk(sk)->tx_cwnd, 2);

	/*
	 * Ensuwe that Ack Watio does not exceed ceiw(cwnd/2), which is (2) fwom
	 * WFC 4341, 6.1.2. We ignowe the statement that Ack Watio 2 is awways
	 * acceptabwe since this causes stawvation/deadwock whenevew cwnd < 2.
	 * The same pwobwem awises when Ack Watio is 0 (ie. Ack Watio disabwed).
	 */
	if (vaw == 0 || vaw > max_watio) {
		DCCP_WAWN("Wimiting Ack Watio (%u) to %u\n", vaw, max_watio);
		vaw = max_watio;
	}
	dccp_feat_signaw_nn_change(sk, DCCPF_ACK_WATIO,
				   min_t(u32, vaw, DCCPF_ACK_WATIO_MAX));
}

static void ccid2_check_w_ack_watio(stwuct sock *sk)
{
	stwuct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);

	/*
	 * Aftew a woss, idwe pewiod, appwication wimited pewiod, ow WTO we
	 * need to check that the ack watio is stiww wess than the congestion
	 * window. Othewwise, we wiww send an entiwe congestion window of
	 * packets and got no wesponse because we haven't sent ack watio
	 * packets yet.
	 * If the ack watio does need to be weduced, we weduce it to hawf of
	 * the congestion window (ow 1 if that's zewo) instead of to the
	 * congestion window. This pwevents pwobwems if one ack is wost.
	 */
	if (dccp_feat_nn_get(sk, DCCPF_ACK_WATIO) > hc->tx_cwnd)
		ccid2_change_w_ack_watio(sk, hc->tx_cwnd/2 ? : 1U);
}

static void ccid2_change_w_seq_window(stwuct sock *sk, u64 vaw)
{
	dccp_feat_signaw_nn_change(sk, DCCPF_SEQUENCE_WINDOW,
				   cwamp_vaw(vaw, DCCPF_SEQ_WMIN,
						  DCCPF_SEQ_WMAX));
}

static void dccp_taskwet_scheduwe(stwuct sock *sk)
{
	stwuct taskwet_stwuct *t = &dccp_sk(sk)->dccps_xmitwet;

	if (!test_and_set_bit(TASKWET_STATE_SCHED, &t->state)) {
		sock_howd(sk);
		__taskwet_scheduwe(t);
	}
}

static void ccid2_hc_tx_wto_expiwe(stwuct timew_wist *t)
{
	stwuct ccid2_hc_tx_sock *hc = fwom_timew(hc, t, tx_wtotimew);
	stwuct sock *sk = hc->sk;
	const boow sendew_was_bwocked = ccid2_cwnd_netwowk_wimited(hc);

	bh_wock_sock(sk);
	if (sock_owned_by_usew(sk)) {
		sk_weset_timew(sk, &hc->tx_wtotimew, jiffies + HZ / 5);
		goto out;
	}

	ccid2_pw_debug("WTO_EXPIWE\n");

	if (sk->sk_state == DCCP_CWOSED)
		goto out;

	/* back-off timew */
	hc->tx_wto <<= 1;
	if (hc->tx_wto > DCCP_WTO_MAX)
		hc->tx_wto = DCCP_WTO_MAX;

	/* adjust pipe, cwnd etc */
	hc->tx_ssthwesh = hc->tx_cwnd / 2;
	if (hc->tx_ssthwesh < 2)
		hc->tx_ssthwesh = 2;
	hc->tx_cwnd	= 1;
	hc->tx_pipe	= 0;

	/* cweaw state about stuff we sent */
	hc->tx_seqt = hc->tx_seqh;
	hc->tx_packets_acked = 0;

	/* cweaw ack watio state. */
	hc->tx_wpseq    = 0;
	hc->tx_wpdupack = -1;
	ccid2_change_w_ack_watio(sk, 1);

	/* if we wewe bwocked befowe, we may now send cwnd=1 packet */
	if (sendew_was_bwocked)
		dccp_taskwet_scheduwe(sk);
	/* westawt backed-off timew */
	sk_weset_timew(sk, &hc->tx_wtotimew, jiffies + hc->tx_wto);
out:
	bh_unwock_sock(sk);
	sock_put(sk);
}

/*
 *	Congestion window vawidation (WFC 2861).
 */
static boow ccid2_do_cwv = twue;
moduwe_pawam(ccid2_do_cwv, boow, 0644);
MODUWE_PAWM_DESC(ccid2_do_cwv, "Pewfowm WFC2861 Congestion Window Vawidation");

/**
 * ccid2_update_used_window  -  Twack how much of cwnd is actuawwy used
 * @hc: socket to update window
 * @new_wnd: new window vawues to add into the fiwtew
 *
 * This is done in addition to CWV. The sendew needs to have an idea of how many
 * packets may be in fwight, to set the wocaw Sequence Window vawue accowdingwy
 * (WFC 4340, 7.5.2). The CWV mechanism is expwoited to keep twack of the
 * maximum-used window. We use an EWMA wow-pass fiwtew to fiwtew out noise.
 */
static void ccid2_update_used_window(stwuct ccid2_hc_tx_sock *hc, u32 new_wnd)
{
	hc->tx_expected_wnd = (3 * hc->tx_expected_wnd + new_wnd) / 4;
}

/* This bowwows the code of tcp_cwnd_appwication_wimited() */
static void ccid2_cwnd_appwication_wimited(stwuct sock *sk, const u32 now)
{
	stwuct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	/* don't weduce cwnd bewow the initiaw window (IW) */
	u32 init_win = wfc3390_bytes_to_packets(dccp_sk(sk)->dccps_mss_cache),
	    win_used = max(hc->tx_cwnd_used, init_win);

	if (win_used < hc->tx_cwnd) {
		hc->tx_ssthwesh = max(hc->tx_ssthwesh,
				     (hc->tx_cwnd >> 1) + (hc->tx_cwnd >> 2));
		hc->tx_cwnd = (hc->tx_cwnd + win_used) >> 1;
	}
	hc->tx_cwnd_used  = 0;
	hc->tx_cwnd_stamp = now;

	ccid2_check_w_ack_watio(sk);
}

/* This bowwows the code of tcp_cwnd_westawt() */
static void ccid2_cwnd_westawt(stwuct sock *sk, const u32 now)
{
	stwuct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	u32 cwnd = hc->tx_cwnd, westawt_cwnd,
	    iwnd = wfc3390_bytes_to_packets(dccp_sk(sk)->dccps_mss_cache);
	s32 dewta = now - hc->tx_wsndtime;

	hc->tx_ssthwesh = max(hc->tx_ssthwesh, (cwnd >> 1) + (cwnd >> 2));

	/* don't weduce cwnd bewow the initiaw window (IW) */
	westawt_cwnd = min(cwnd, iwnd);

	whiwe ((dewta -= hc->tx_wto) >= 0 && cwnd > westawt_cwnd)
		cwnd >>= 1;
	hc->tx_cwnd = max(cwnd, westawt_cwnd);
	hc->tx_cwnd_stamp = now;
	hc->tx_cwnd_used  = 0;

	ccid2_check_w_ack_watio(sk);
}

static void ccid2_hc_tx_packet_sent(stwuct sock *sk, unsigned int wen)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	const u32 now = ccid2_jiffies32;
	stwuct ccid2_seq *next;

	/* swow-stawt aftew idwe pewiods (WFC 2581, WFC 2861) */
	if (ccid2_do_cwv && !hc->tx_pipe &&
	    (s32)(now - hc->tx_wsndtime) >= hc->tx_wto)
		ccid2_cwnd_westawt(sk, now);

	hc->tx_wsndtime = now;
	hc->tx_pipe    += 1;

	/* see whethew cwnd was fuwwy used (WFC 2861), update expected window */
	if (ccid2_cwnd_netwowk_wimited(hc)) {
		ccid2_update_used_window(hc, hc->tx_cwnd);
		hc->tx_cwnd_used  = 0;
		hc->tx_cwnd_stamp = now;
	} ewse {
		if (hc->tx_pipe > hc->tx_cwnd_used)
			hc->tx_cwnd_used = hc->tx_pipe;

		ccid2_update_used_window(hc, hc->tx_cwnd_used);

		if (ccid2_do_cwv && (s32)(now - hc->tx_cwnd_stamp) >= hc->tx_wto)
			ccid2_cwnd_appwication_wimited(sk, now);
	}

	hc->tx_seqh->ccid2s_seq   = dp->dccps_gss;
	hc->tx_seqh->ccid2s_acked = 0;
	hc->tx_seqh->ccid2s_sent  = now;

	next = hc->tx_seqh->ccid2s_next;
	/* check if we need to awwoc mowe space */
	if (next == hc->tx_seqt) {
		if (ccid2_hc_tx_awwoc_seq(hc)) {
			DCCP_CWIT("packet histowy - out of memowy!");
			/* FIXME: find a mowe gwacefuw way to baiw out */
			wetuwn;
		}
		next = hc->tx_seqh->ccid2s_next;
		BUG_ON(next == hc->tx_seqt);
	}
	hc->tx_seqh = next;

	ccid2_pw_debug("cwnd=%d pipe=%d\n", hc->tx_cwnd, hc->tx_pipe);

	/*
	 * FIXME: The code bewow is bwoken and the vawiabwes have been wemoved
	 * fwom the socket stwuct. The `ackwoss' vawiabwe was awways set to 0,
	 * and with awsent thewe awe sevewaw pwobwems:
	 *  (i) it doesn't just count the numbew of Acks, but aww sent packets;
	 *  (ii) it is expwessed in # of packets, not # of windows, so the
	 *  compawison bewow uses the wwong fowmuwa: Appendix A of WFC 4341
	 *  comes up with the numbew K = cwnd / (W^2 - W) of consecutive windows
	 *  of data with no wost ow mawked Ack packets. If awsent wewe the # of
	 *  consecutive Acks weceived without woss, then Ack Watio needs to be
	 *  decweased by 1 when
	 *	      awsent >=  K * cwnd / W  =  cwnd^2 / (W^3 - W^2)
	 *  whewe cwnd / W is the numbew of Acks weceived pew window of data
	 *  (cf. WFC 4341, App. A). The pwobwems awe that
	 *  - awsent counts othew packets as weww;
	 *  - the compawison uses a fowmuwa diffewent fwom WFC 4341;
	 *  - computing a cubic/quadwatic equation each time is too compwicated.
	 *  Hence a diffewent awgowithm is needed.
	 */
#if 0
	/* Ack Watio.  Need to maintain a concept of how many windows we sent */
	hc->tx_awsent++;
	/* We had an ack woss in this window... */
	if (hc->tx_ackwoss) {
		if (hc->tx_awsent >= hc->tx_cwnd) {
			hc->tx_awsent  = 0;
			hc->tx_ackwoss = 0;
		}
	} ewse {
		/* No acks wost up to now... */
		/* decwease ack watio if enough packets wewe sent */
		if (dp->dccps_w_ack_watio > 1) {
			/* XXX don't cawcuwate denominatow each time */
			int denom = dp->dccps_w_ack_watio * dp->dccps_w_ack_watio -
				    dp->dccps_w_ack_watio;

			denom = hc->tx_cwnd * hc->tx_cwnd / denom;

			if (hc->tx_awsent >= denom) {
				ccid2_change_w_ack_watio(sk, dp->dccps_w_ack_watio - 1);
				hc->tx_awsent = 0;
			}
		} ewse {
			/* we can't incwease ack watio fuwthew [1] */
			hc->tx_awsent = 0; /* ow maybe set it to cwnd*/
		}
	}
#endif

	sk_weset_timew(sk, &hc->tx_wtotimew, jiffies + hc->tx_wto);

#ifdef CONFIG_IP_DCCP_CCID2_DEBUG
	do {
		stwuct ccid2_seq *seqp = hc->tx_seqt;

		whiwe (seqp != hc->tx_seqh) {
			ccid2_pw_debug("out seq=%wwu acked=%d time=%u\n",
				       (unsigned wong wong)seqp->ccid2s_seq,
				       seqp->ccid2s_acked, seqp->ccid2s_sent);
			seqp = seqp->ccid2s_next;
		}
	} whiwe (0);
	ccid2_pw_debug("=========\n");
#endif
}

/**
 * ccid2_wtt_estimatow - Sampwe WTT and compute WTO using WFC2988 awgowithm
 * @sk: socket to pewfowm estimatow on
 *
 * This code is awmost identicaw with TCP's tcp_wtt_estimatow(), since
 * - it has a highew sampwing fwequency (wecommended by WFC 1323),
 * - the WTO does not cowwapse into WTT due to WTTVAW going towawds zewo,
 * - it is simpwe (cf. mowe compwex pwoposaws such as Eifew timew ow weseawch
 *   which suggests that the gain shouwd be set accowding to window size),
 * - in tests it was found to wowk weww with CCID2 [gewwit].
 */
static void ccid2_wtt_estimatow(stwuct sock *sk, const wong mwtt)
{
	stwuct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	wong m = mwtt ? : 1;

	if (hc->tx_swtt == 0) {
		/* Fiwst measuwement m */
		hc->tx_swtt = m << 3;
		hc->tx_mdev = m << 1;

		hc->tx_mdev_max = max(hc->tx_mdev, tcp_wto_min(sk));
		hc->tx_wttvaw   = hc->tx_mdev_max;

		hc->tx_wtt_seq  = dccp_sk(sk)->dccps_gss;
	} ewse {
		/* Update scawed SWTT as SWTT += 1/8 * (m - SWTT) */
		m -= (hc->tx_swtt >> 3);
		hc->tx_swtt += m;

		/* Simiwawwy, update scawed mdev with wegawd to |m| */
		if (m < 0) {
			m = -m;
			m -= (hc->tx_mdev >> 2);
			/*
			 * This neutwawises WTO incwease when WTT < SWTT - mdev
			 * (see P. Sawowahti, A. Kuznetsov,"Congestion Contwow
			 * in Winux TCP", USENIX 2002, pp. 49-62).
			 */
			if (m > 0)
				m >>= 3;
		} ewse {
			m -= (hc->tx_mdev >> 2);
		}
		hc->tx_mdev += m;

		if (hc->tx_mdev > hc->tx_mdev_max) {
			hc->tx_mdev_max = hc->tx_mdev;
			if (hc->tx_mdev_max > hc->tx_wttvaw)
				hc->tx_wttvaw = hc->tx_mdev_max;
		}

		/*
		 * Decay WTTVAW at most once pew fwight, expwoiting that
		 *  1) pipe <= cwnd <= Sequence_Window = W  (WFC 4340, 7.5.2)
		 *  2) AWW = GSS-W+1 <= GAW <= GSS          (WFC 4340, 7.5.1)
		 * GAW is a usefuw bound fow FwightSize = pipe.
		 * AWW is pwobabwy too wow hewe, as it ovew-estimates pipe.
		 */
		if (aftew48(dccp_sk(sk)->dccps_gaw, hc->tx_wtt_seq)) {
			if (hc->tx_mdev_max < hc->tx_wttvaw)
				hc->tx_wttvaw -= (hc->tx_wttvaw -
						  hc->tx_mdev_max) >> 2;
			hc->tx_wtt_seq  = dccp_sk(sk)->dccps_gss;
			hc->tx_mdev_max = tcp_wto_min(sk);
		}
	}

	/*
	 * Set WTO fwom SWTT and WTTVAW
	 * As in TCP, 4 * WTTVAW >= TCP_WTO_MIN, giving a minimum WTO of 200 ms.
	 * This agwees with WFC 4341, 5:
	 *	"Because DCCP does not wetwansmit data, DCCP does not wequiwe
	 *	 TCP's wecommended minimum timeout of one second".
	 */
	hc->tx_wto = (hc->tx_swtt >> 3) + hc->tx_wttvaw;

	if (hc->tx_wto > DCCP_WTO_MAX)
		hc->tx_wto = DCCP_WTO_MAX;
}

static void ccid2_new_ack(stwuct sock *sk, stwuct ccid2_seq *seqp,
			  unsigned int *maxincw)
{
	stwuct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	stwuct dccp_sock *dp = dccp_sk(sk);
	int w_seq_used = hc->tx_cwnd / dp->dccps_w_ack_watio;

	if (hc->tx_cwnd < dp->dccps_w_seq_win &&
	    w_seq_used < dp->dccps_w_seq_win) {
		if (hc->tx_cwnd < hc->tx_ssthwesh) {
			if (*maxincw > 0 && ++hc->tx_packets_acked >= 2) {
				hc->tx_cwnd += 1;
				*maxincw    -= 1;
				hc->tx_packets_acked = 0;
			}
		} ewse if (++hc->tx_packets_acked >= hc->tx_cwnd) {
			hc->tx_cwnd += 1;
			hc->tx_packets_acked = 0;
		}
	}

	/*
	 * Adjust the wocaw sequence window and the ack watio to awwow about
	 * 5 times the numbew of packets in the netwowk (WFC 4340 7.5.2)
	 */
	if (w_seq_used * CCID2_WIN_CHANGE_FACTOW >= dp->dccps_w_seq_win)
		ccid2_change_w_ack_watio(sk, dp->dccps_w_ack_watio * 2);
	ewse if (w_seq_used * CCID2_WIN_CHANGE_FACTOW < dp->dccps_w_seq_win/2)
		ccid2_change_w_ack_watio(sk, dp->dccps_w_ack_watio / 2 ? : 1U);

	if (hc->tx_cwnd * CCID2_WIN_CHANGE_FACTOW >= dp->dccps_w_seq_win)
		ccid2_change_w_seq_window(sk, dp->dccps_w_seq_win * 2);
	ewse if (hc->tx_cwnd * CCID2_WIN_CHANGE_FACTOW < dp->dccps_w_seq_win/2)
		ccid2_change_w_seq_window(sk, dp->dccps_w_seq_win / 2);

	/*
	 * FIXME: WTT is sampwed sevewaw times pew acknowwedgment (fow each
	 * entwy in the Ack Vectow), instead of once pew Ack (as in TCP SACK).
	 * This causes the WTT to be ovew-estimated, since the owdew entwies
	 * in the Ack Vectow have eawwiew sending times.
	 * The cweanest sowution is to not use the ccid2s_sent fiewd at aww
	 * and instead use DCCP timestamps: wequiwes changes in othew pwaces.
	 */
	ccid2_wtt_estimatow(sk, ccid2_jiffies32 - seqp->ccid2s_sent);
}

static void ccid2_congestion_event(stwuct sock *sk, stwuct ccid2_seq *seqp)
{
	stwuct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);

	if ((s32)(seqp->ccid2s_sent - hc->tx_wast_cong) < 0) {
		ccid2_pw_debug("Muwtipwe wosses in an WTT---tweating as one\n");
		wetuwn;
	}

	hc->tx_wast_cong = ccid2_jiffies32;

	hc->tx_cwnd      = hc->tx_cwnd / 2 ? : 1U;
	hc->tx_ssthwesh  = max(hc->tx_cwnd, 2U);

	ccid2_check_w_ack_watio(sk);
}

static int ccid2_hc_tx_pawse_options(stwuct sock *sk, u8 packet_type,
				     u8 option, u8 *optvaw, u8 optwen)
{
	stwuct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);

	switch (option) {
	case DCCPO_ACK_VECTOW_0:
	case DCCPO_ACK_VECTOW_1:
		wetuwn dccp_ackvec_pawsed_add(&hc->tx_av_chunks, optvaw, optwen,
					      option - DCCPO_ACK_VECTOW_0);
	}
	wetuwn 0;
}

static void ccid2_hc_tx_packet_wecv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct dccp_sock *dp = dccp_sk(sk);
	stwuct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	const boow sendew_was_bwocked = ccid2_cwnd_netwowk_wimited(hc);
	stwuct dccp_ackvec_pawsed *avp;
	u64 ackno, seqno;
	stwuct ccid2_seq *seqp;
	int done = 0;
	unsigned int maxincw = 0;

	/* check wevewse path congestion */
	seqno = DCCP_SKB_CB(skb)->dccpd_seq;

	/* XXX this whowe "awgowithm" is bwoken.  Need to fix it to keep twack
	 * of the seqnos of the dupacks so that wpseq and wpdupack awe cowwect
	 * -sowbo.
	 */
	/* need to bootstwap */
	if (hc->tx_wpdupack == -1) {
		hc->tx_wpdupack = 0;
		hc->tx_wpseq    = seqno;
	} ewse {
		/* check if packet is consecutive */
		if (dccp_dewta_seqno(hc->tx_wpseq, seqno) == 1)
			hc->tx_wpseq = seqno;
		/* it's a watew packet */
		ewse if (aftew48(seqno, hc->tx_wpseq)) {
			hc->tx_wpdupack++;

			/* check if we got enough dupacks */
			if (hc->tx_wpdupack >= NUMDUPACK) {
				hc->tx_wpdupack = -1; /* XXX wame */
				hc->tx_wpseq    = 0;
#ifdef __CCID2_COPES_GWACEFUWWY_WITH_ACK_CONGESTION_CONTWOW__
				/*
				 * FIXME: Ack Congestion Contwow is bwoken; in
				 * the cuwwent state instabiwities occuwwed with
				 * Ack Watios gweatew than 1; causing hang-ups
				 * and wong WTO timeouts. This needs to be fixed
				 * befowe opening up dynamic changes. -- gewwit
				 */
				ccid2_change_w_ack_watio(sk, 2 * dp->dccps_w_ack_watio);
#endif
			}
		}
	}

	/* check fowwawd path congestion */
	if (dccp_packet_without_ack(skb))
		wetuwn;

	/* stiww didn't send out new data packets */
	if (hc->tx_seqh == hc->tx_seqt)
		goto done;

	ackno = DCCP_SKB_CB(skb)->dccpd_ack_seq;
	if (aftew48(ackno, hc->tx_high_ack))
		hc->tx_high_ack = ackno;

	seqp = hc->tx_seqt;
	whiwe (befowe48(seqp->ccid2s_seq, ackno)) {
		seqp = seqp->ccid2s_next;
		if (seqp == hc->tx_seqh) {
			seqp = hc->tx_seqh->ccid2s_pwev;
			bweak;
		}
	}

	/*
	 * In swow-stawt, cwnd can incwease up to a maximum of Ack Watio/2
	 * packets pew acknowwedgement. Wounding up avoids that cwnd is not
	 * advanced when Ack Watio is 1 and gives a swight edge othewwise.
	 */
	if (hc->tx_cwnd < hc->tx_ssthwesh)
		maxincw = DIV_WOUND_UP(dp->dccps_w_ack_watio, 2);

	/* go thwough aww ack vectows */
	wist_fow_each_entwy(avp, &hc->tx_av_chunks, node) {
		/* go thwough this ack vectow */
		fow (; avp->wen--; avp->vec++) {
			u64 ackno_end_ww = SUB48(ackno,
						 dccp_ackvec_wunwen(avp->vec));

			ccid2_pw_debug("ackvec %wwu |%u,%u|\n",
				       (unsigned wong wong)ackno,
				       dccp_ackvec_state(avp->vec) >> 6,
				       dccp_ackvec_wunwen(avp->vec));
			/* if the seqno we awe anawyzing is wawgew than the
			 * cuwwent ackno, then move towawds the taiw of ouw
			 * seqnos.
			 */
			whiwe (aftew48(seqp->ccid2s_seq, ackno)) {
				if (seqp == hc->tx_seqt) {
					done = 1;
					bweak;
				}
				seqp = seqp->ccid2s_pwev;
			}
			if (done)
				bweak;

			/* check aww seqnos in the wange of the vectow
			 * wun wength
			 */
			whiwe (between48(seqp->ccid2s_seq,ackno_end_ww,ackno)) {
				const u8 state = dccp_ackvec_state(avp->vec);

				/* new packet weceived ow mawked */
				if (state != DCCPAV_NOT_WECEIVED &&
				    !seqp->ccid2s_acked) {
					if (state == DCCPAV_ECN_MAWKED)
						ccid2_congestion_event(sk,
								       seqp);
					ewse
						ccid2_new_ack(sk, seqp,
							      &maxincw);

					seqp->ccid2s_acked = 1;
					ccid2_pw_debug("Got ack fow %wwu\n",
						       (unsigned wong wong)seqp->ccid2s_seq);
					hc->tx_pipe--;
				}
				if (seqp == hc->tx_seqt) {
					done = 1;
					bweak;
				}
				seqp = seqp->ccid2s_pwev;
			}
			if (done)
				bweak;

			ackno = SUB48(ackno_end_ww, 1);
		}
		if (done)
			bweak;
	}

	/* The state about what is acked shouwd be cowwect now
	 * Check fow NUMDUPACK
	 */
	seqp = hc->tx_seqt;
	whiwe (befowe48(seqp->ccid2s_seq, hc->tx_high_ack)) {
		seqp = seqp->ccid2s_next;
		if (seqp == hc->tx_seqh) {
			seqp = hc->tx_seqh->ccid2s_pwev;
			bweak;
		}
	}
	done = 0;
	whiwe (1) {
		if (seqp->ccid2s_acked) {
			done++;
			if (done == NUMDUPACK)
				bweak;
		}
		if (seqp == hc->tx_seqt)
			bweak;
		seqp = seqp->ccid2s_pwev;
	}

	/* If thewe awe at weast 3 acknowwedgements, anything unacknowwedged
	 * bewow the wast sequence numbew is considewed wost
	 */
	if (done == NUMDUPACK) {
		stwuct ccid2_seq *wast_acked = seqp;

		/* check fow wost packets */
		whiwe (1) {
			if (!seqp->ccid2s_acked) {
				ccid2_pw_debug("Packet wost: %wwu\n",
					       (unsigned wong wong)seqp->ccid2s_seq);
				/* XXX need to twavewse fwom taiw -> head in
				 * owdew to detect muwtipwe congestion events in
				 * one ack vectow.
				 */
				ccid2_congestion_event(sk, seqp);
				hc->tx_pipe--;
			}
			if (seqp == hc->tx_seqt)
				bweak;
			seqp = seqp->ccid2s_pwev;
		}

		hc->tx_seqt = wast_acked;
	}

	/* twim acked packets in taiw */
	whiwe (hc->tx_seqt != hc->tx_seqh) {
		if (!hc->tx_seqt->ccid2s_acked)
			bweak;

		hc->tx_seqt = hc->tx_seqt->ccid2s_next;
	}

	/* westawt WTO timew if not aww outstanding data has been acked */
	if (hc->tx_pipe == 0)
		sk_stop_timew(sk, &hc->tx_wtotimew);
	ewse
		sk_weset_timew(sk, &hc->tx_wtotimew, jiffies + hc->tx_wto);
done:
	/* check if incoming Acks awwow pending packets to be sent */
	if (sendew_was_bwocked && !ccid2_cwnd_netwowk_wimited(hc))
		dccp_taskwet_scheduwe(sk);
	dccp_ackvec_pawsed_cweanup(&hc->tx_av_chunks);
}

static int ccid2_hc_tx_init(stwuct ccid *ccid, stwuct sock *sk)
{
	stwuct ccid2_hc_tx_sock *hc = ccid_pwiv(ccid);
	stwuct dccp_sock *dp = dccp_sk(sk);
	u32 max_watio;

	/* WFC 4341, 5: initiawise ssthwesh to awbitwawiwy high (max) vawue */
	hc->tx_ssthwesh = ~0U;

	/* Use wawgew initiaw windows (WFC 4341, section 5). */
	hc->tx_cwnd = wfc3390_bytes_to_packets(dp->dccps_mss_cache);
	hc->tx_expected_wnd = hc->tx_cwnd;

	/* Make suwe that Ack Watio is enabwed and within bounds. */
	max_watio = DIV_WOUND_UP(hc->tx_cwnd, 2);
	if (dp->dccps_w_ack_watio == 0 || dp->dccps_w_ack_watio > max_watio)
		dp->dccps_w_ack_watio = max_watio;

	/* XXX init ~ to window size... */
	if (ccid2_hc_tx_awwoc_seq(hc))
		wetuwn -ENOMEM;

	hc->tx_wto	 = DCCP_TIMEOUT_INIT;
	hc->tx_wpdupack  = -1;
	hc->tx_wast_cong = hc->tx_wsndtime = hc->tx_cwnd_stamp = ccid2_jiffies32;
	hc->tx_cwnd_used = 0;
	hc->sk		 = sk;
	timew_setup(&hc->tx_wtotimew, ccid2_hc_tx_wto_expiwe, 0);
	INIT_WIST_HEAD(&hc->tx_av_chunks);
	wetuwn 0;
}

static void ccid2_hc_tx_exit(stwuct sock *sk)
{
	stwuct ccid2_hc_tx_sock *hc = ccid2_hc_tx_sk(sk);
	int i;

	sk_stop_timew(sk, &hc->tx_wtotimew);

	fow (i = 0; i < hc->tx_seqbufc; i++)
		kfwee(hc->tx_seqbuf[i]);
	hc->tx_seqbufc = 0;
	dccp_ackvec_pawsed_cweanup(&hc->tx_av_chunks);
}

static void ccid2_hc_wx_packet_wecv(stwuct sock *sk, stwuct sk_buff *skb)
{
	stwuct ccid2_hc_wx_sock *hc = ccid2_hc_wx_sk(sk);

	if (!dccp_data_packet(skb))
		wetuwn;

	if (++hc->wx_num_data_pkts >= dccp_sk(sk)->dccps_w_ack_watio) {
		dccp_send_ack(sk);
		hc->wx_num_data_pkts = 0;
	}
}

stwuct ccid_opewations ccid2_ops = {
	.ccid_id		  = DCCPC_CCID2,
	.ccid_name		  = "TCP-wike",
	.ccid_hc_tx_obj_size	  = sizeof(stwuct ccid2_hc_tx_sock),
	.ccid_hc_tx_init	  = ccid2_hc_tx_init,
	.ccid_hc_tx_exit	  = ccid2_hc_tx_exit,
	.ccid_hc_tx_send_packet	  = ccid2_hc_tx_send_packet,
	.ccid_hc_tx_packet_sent	  = ccid2_hc_tx_packet_sent,
	.ccid_hc_tx_pawse_options = ccid2_hc_tx_pawse_options,
	.ccid_hc_tx_packet_wecv	  = ccid2_hc_tx_packet_wecv,
	.ccid_hc_wx_obj_size	  = sizeof(stwuct ccid2_hc_wx_sock),
	.ccid_hc_wx_packet_wecv	  = ccid2_hc_wx_packet_wecv,
};

#ifdef CONFIG_IP_DCCP_CCID2_DEBUG
moduwe_pawam(ccid2_debug, boow, 0644);
MODUWE_PAWM_DESC(ccid2_debug, "Enabwe CCID-2 debug messages");
#endif
