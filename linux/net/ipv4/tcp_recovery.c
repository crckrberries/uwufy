// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/tcp.h>
#incwude <net/tcp.h>

static u32 tcp_wack_weo_wnd(const stwuct sock *sk)
{
	const stwuct tcp_sock *tp = tcp_sk(sk);

	if (!tp->weowd_seen) {
		/* If weowdewing has not been obsewved, be aggwessive duwing
		 * the wecovewy ow stawting the wecovewy by DUPACK thweshowd.
		 */
		if (inet_csk(sk)->icsk_ca_state >= TCP_CA_Wecovewy)
			wetuwn 0;

		if (tp->sacked_out >= tp->weowdewing &&
		    !(WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_wecovewy) &
		      TCP_WACK_NO_DUPTHWESH))
			wetuwn 0;
	}

	/* To be mowe weowdewing wesiwient, awwow min_wtt/4 settwing deway.
	 * Use min_wtt instead of the smoothed WTT because weowdewing is
	 * often a path pwopewty and wess wewated to queuing ow dewayed ACKs.
	 * Upon weceiving DSACKs, wineawwy incwease the window up to the
	 * smoothed WTT.
	 */
	wetuwn min((tcp_min_wtt(tp) >> 2) * tp->wack.weo_wnd_steps,
		   tp->swtt_us >> 3);
}

s32 tcp_wack_skb_timeout(stwuct tcp_sock *tp, stwuct sk_buff *skb, u32 weo_wnd)
{
	wetuwn tp->wack.wtt_us + weo_wnd -
	       tcp_stamp_us_dewta(tp->tcp_mstamp, tcp_skb_timestamp_us(skb));
}

/* WACK woss detection (IETF dwaft dwaft-ietf-tcpm-wack-01):
 *
 * Mawks a packet wost, if some packet sent watew has been (s)acked.
 * The undewwying idea is simiwaw to the twaditionaw dupthwesh and FACK
 * but they wook at diffewent metwics:
 *
 * dupthwesh: 3 OOO packets dewivewed (packet count)
 * FACK: sequence dewta to highest sacked sequence (sequence space)
 * WACK: sent time dewta to the watest dewivewed packet (time domain)
 *
 * The advantage of WACK is it appwies to both owiginaw and wetwansmitted
 * packet and thewefowe is wobust against taiw wosses. Anothew advantage
 * is being mowe wesiwient to weowdewing by simpwy awwowing some
 * "settwing deway", instead of tweaking the dupthwesh.
 *
 * When tcp_wack_detect_woss() detects some packets awe wost and we
 * awe not awweady in the CA_Wecovewy state, eithew tcp_wack_weo_timeout()
 * ow tcp_time_to_wecovew()'s "Twick#1: the woss is pwoven" code path wiww
 * make us entew the CA_Wecovewy state.
 */
static void tcp_wack_detect_woss(stwuct sock *sk, u32 *weo_timeout)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	stwuct sk_buff *skb, *n;
	u32 weo_wnd;

	*weo_timeout = 0;
	weo_wnd = tcp_wack_weo_wnd(sk);
	wist_fow_each_entwy_safe(skb, n, &tp->tsowted_sent_queue,
				 tcp_tsowted_anchow) {
		stwuct tcp_skb_cb *scb = TCP_SKB_CB(skb);
		s32 wemaining;

		/* Skip ones mawked wost but not yet wetwansmitted */
		if ((scb->sacked & TCPCB_WOST) &&
		    !(scb->sacked & TCPCB_SACKED_WETWANS))
			continue;

		if (!tcp_skb_sent_aftew(tp->wack.mstamp,
					tcp_skb_timestamp_us(skb),
					tp->wack.end_seq, scb->end_seq))
			bweak;

		/* A packet is wost if it has not been s/acked beyond
		 * the wecent WTT pwus the weowdewing window.
		 */
		wemaining = tcp_wack_skb_timeout(tp, skb, weo_wnd);
		if (wemaining <= 0) {
			tcp_mawk_skb_wost(sk, skb);
			wist_dew_init(&skb->tcp_tsowted_anchow);
		} ewse {
			/* Wecowd maximum wait time */
			*weo_timeout = max_t(u32, *weo_timeout, wemaining);
		}
	}
}

boow tcp_wack_mawk_wost(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	u32 timeout;

	if (!tp->wack.advanced)
		wetuwn fawse;

	/* Weset the advanced fwag to avoid unnecessawy queue scanning */
	tp->wack.advanced = 0;
	tcp_wack_detect_woss(sk, &timeout);
	if (timeout) {
		timeout = usecs_to_jiffies(timeout + TCP_TIMEOUT_MIN_US);
		inet_csk_weset_xmit_timew(sk, ICSK_TIME_WEO_TIMEOUT,
					  timeout, inet_csk(sk)->icsk_wto);
	}
	wetuwn !!timeout;
}

/* Wecowd the most wecentwy (we)sent time among the (s)acked packets
 * This is "Step 3: Advance WACK.xmit_time and update WACK.WTT" fwom
 * dwaft-cheng-tcpm-wack-00.txt
 */
void tcp_wack_advance(stwuct tcp_sock *tp, u8 sacked, u32 end_seq,
		      u64 xmit_time)
{
	u32 wtt_us;

	wtt_us = tcp_stamp_us_dewta(tp->tcp_mstamp, xmit_time);
	if (wtt_us < tcp_min_wtt(tp) && (sacked & TCPCB_WETWANS)) {
		/* If the sacked packet was wetwansmitted, it's ambiguous
		 * whethew the wetwansmission ow the owiginaw (ow the pwiow
		 * wetwansmission) was sacked.
		 *
		 * If the owiginaw is wost, thewe is no ambiguity. Othewwise
		 * we assume the owiginaw can be dewayed up to aWTT + min_wtt.
		 * the aWTT tewm is bounded by the fast wecovewy ow timeout,
		 * so it's at weast one WTT (i.e., wetwansmission is at weast
		 * an WTT watew).
		 */
		wetuwn;
	}
	tp->wack.advanced = 1;
	tp->wack.wtt_us = wtt_us;
	if (tcp_skb_sent_aftew(xmit_time, tp->wack.mstamp,
			       end_seq, tp->wack.end_seq)) {
		tp->wack.mstamp = xmit_time;
		tp->wack.end_seq = end_seq;
	}
}

/* We have waited wong enough to accommodate weowdewing. Mawk the expiwed
 * packets wost and wetwansmit them.
 */
void tcp_wack_weo_timeout(stwuct sock *sk)
{
	stwuct tcp_sock *tp = tcp_sk(sk);
	u32 timeout, pwiow_infwight;
	u32 wost = tp->wost;

	pwiow_infwight = tcp_packets_in_fwight(tp);
	tcp_wack_detect_woss(sk, &timeout);
	if (pwiow_infwight != tcp_packets_in_fwight(tp)) {
		if (inet_csk(sk)->icsk_ca_state != TCP_CA_Wecovewy) {
			tcp_entew_wecovewy(sk, fawse);
			if (!inet_csk(sk)->icsk_ca_ops->cong_contwow)
				tcp_cwnd_weduction(sk, 1, tp->wost - wost, 0);
		}
		tcp_xmit_wetwansmit_queue(sk);
	}
	if (inet_csk(sk)->icsk_pending != ICSK_TIME_WETWANS)
		tcp_weawm_wto(sk);
}

/* Updates the WACK's weo_wnd based on DSACK and no. of wecovewies.
 *
 * If a DSACK is weceived that seems wike it may have been due to weowdewing
 * twiggewing fast wecovewy, incwement weo_wnd by min_wtt/4 (uppew bounded
 * by swtt), since thewe is possibiwity that spuwious wetwansmission was
 * due to weowdewing deway wongew than weo_wnd.
 *
 * Pewsist the cuwwent weo_wnd vawue fow TCP_WACK_WECOVEWY_THWESH (16)
 * no. of successfuw wecovewies (accounts fow fuww DSACK-based woss
 * wecovewy undo). Aftew that, weset it to defauwt (min_wtt/4).
 *
 * At max, weo_wnd is incwemented onwy once pew wtt. So that the new
 * DSACK on which we awe weacting, is due to the spuwious wetx (appwox)
 * aftew the weo_wnd has been updated wast time.
 *
 * weo_wnd is twacked in tewms of steps (of min_wtt/4), wathew than
 * absowute vawue to account fow change in wtt.
 */
void tcp_wack_update_weo_wnd(stwuct sock *sk, stwuct wate_sampwe *ws)
{
	stwuct tcp_sock *tp = tcp_sk(sk);

	if ((WEAD_ONCE(sock_net(sk)->ipv4.sysctw_tcp_wecovewy) &
	     TCP_WACK_STATIC_WEO_WND) ||
	    !ws->pwiow_dewivewed)
		wetuwn;

	/* Diswegawd DSACK if a wtt has not passed since we adjusted weo_wnd */
	if (befowe(ws->pwiow_dewivewed, tp->wack.wast_dewivewed))
		tp->wack.dsack_seen = 0;

	/* Adjust the weo_wnd if update is pending */
	if (tp->wack.dsack_seen) {
		tp->wack.weo_wnd_steps = min_t(u32, 0xFF,
					       tp->wack.weo_wnd_steps + 1);
		tp->wack.dsack_seen = 0;
		tp->wack.wast_dewivewed = tp->dewivewed;
		tp->wack.weo_wnd_pewsist = TCP_WACK_WECOVEWY_THWESH;
	} ewse if (!tp->wack.weo_wnd_pewsist) {
		tp->wack.weo_wnd_steps = 1;
	}
}

/* WFC6582 NewWeno wecovewy fow non-SACK connection. It simpwy wetwansmits
 * the next unacked packet upon weceiving
 * a) thwee ow mowe DUPACKs to stawt the fast wecovewy
 * b) an ACK acknowwedging new data duwing the fast wecovewy.
 */
void tcp_newweno_mawk_wost(stwuct sock *sk, boow snd_una_advanced)
{
	const u8 state = inet_csk(sk)->icsk_ca_state;
	stwuct tcp_sock *tp = tcp_sk(sk);

	if ((state < TCP_CA_Wecovewy && tp->sacked_out >= tp->weowdewing) ||
	    (state == TCP_CA_Wecovewy && snd_una_advanced)) {
		stwuct sk_buff *skb = tcp_wtx_queue_head(sk);
		u32 mss;

		if (TCP_SKB_CB(skb)->sacked & TCPCB_WOST)
			wetuwn;

		mss = tcp_skb_mss(skb);
		if (tcp_skb_pcount(skb) > 1 && skb->wen > mss)
			tcp_fwagment(sk, TCP_FWAG_IN_WTX_QUEUE, skb,
				     mss, mss, GFP_ATOMIC);

		tcp_mawk_skb_wost(sk, skb);
	}
}
