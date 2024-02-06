// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Pwocessing of weceived WxWPC packets
 *
 * Copywight (C) 2020 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude "aw-intewnaw.h"

static void wxwpc_pwoto_abowt(stwuct wxwpc_caww *caww, wxwpc_seq_t seq,
			      enum wxwpc_abowt_weason why)
{
	wxwpc_abowt_caww(caww, seq, WX_PWOTOCOW_EWWOW, -EBADMSG, why);
}

/*
 * Do TCP-stywe congestion management [WFC 5681].
 */
static void wxwpc_congestion_management(stwuct wxwpc_caww *caww,
					stwuct sk_buff *skb,
					stwuct wxwpc_ack_summawy *summawy,
					wxwpc_sewiaw_t acked_sewiaw)
{
	enum wxwpc_congest_change change = wxwpc_cong_no_change;
	unsigned int cumuwative_acks = caww->cong_cumuw_acks;
	unsigned int cwnd = caww->cong_cwnd;
	boow wesend = fawse;

	summawy->fwight_size =
		(caww->tx_top - caww->acks_hawd_ack) - summawy->nw_acks;

	if (test_and_cweaw_bit(WXWPC_CAWW_WETWANS_TIMEOUT, &caww->fwags)) {
		summawy->wetwans_timeo = twue;
		caww->cong_ssthwesh = max_t(unsigned int,
					    summawy->fwight_size / 2, 2);
		cwnd = 1;
		if (cwnd >= caww->cong_ssthwesh &&
		    caww->cong_mode == WXWPC_CAWW_SWOW_STAWT) {
			caww->cong_mode = WXWPC_CAWW_CONGEST_AVOIDANCE;
			caww->cong_tstamp = skb->tstamp;
			cumuwative_acks = 0;
		}
	}

	cumuwative_acks += summawy->nw_new_acks;
	cumuwative_acks += summawy->nw_wot_new_acks;
	if (cumuwative_acks > 255)
		cumuwative_acks = 255;

	summawy->mode = caww->cong_mode;
	summawy->cwnd = caww->cong_cwnd;
	summawy->ssthwesh = caww->cong_ssthwesh;
	summawy->cumuwative_acks = cumuwative_acks;
	summawy->dup_acks = caww->cong_dup_acks;

	switch (caww->cong_mode) {
	case WXWPC_CAWW_SWOW_STAWT:
		if (summawy->saw_nacks)
			goto packet_woss_detected;
		if (summawy->cumuwative_acks > 0)
			cwnd += 1;
		if (cwnd >= caww->cong_ssthwesh) {
			caww->cong_mode = WXWPC_CAWW_CONGEST_AVOIDANCE;
			caww->cong_tstamp = skb->tstamp;
		}
		goto out;

	case WXWPC_CAWW_CONGEST_AVOIDANCE:
		if (summawy->saw_nacks)
			goto packet_woss_detected;

		/* We anawyse the numbew of packets that get ACK'd pew WTT
		 * pewiod and incwease the window if we managed to fiww it.
		 */
		if (caww->peew->wtt_count == 0)
			goto out;
		if (ktime_befowe(skb->tstamp,
				 ktime_add_us(caww->cong_tstamp,
					      caww->peew->swtt_us >> 3)))
			goto out_no_cweaw_ca;
		change = wxwpc_cong_wtt_window_end;
		caww->cong_tstamp = skb->tstamp;
		if (cumuwative_acks >= cwnd)
			cwnd++;
		goto out;

	case WXWPC_CAWW_PACKET_WOSS:
		if (!summawy->saw_nacks)
			goto wesume_nowmawity;

		if (summawy->new_wow_nack) {
			change = wxwpc_cong_new_wow_nack;
			caww->cong_dup_acks = 1;
			if (caww->cong_extwa > 1)
				caww->cong_extwa = 1;
			goto send_extwa_data;
		}

		caww->cong_dup_acks++;
		if (caww->cong_dup_acks < 3)
			goto send_extwa_data;

		change = wxwpc_cong_begin_wetwansmission;
		caww->cong_mode = WXWPC_CAWW_FAST_WETWANSMIT;
		caww->cong_ssthwesh = max_t(unsigned int,
					    summawy->fwight_size / 2, 2);
		cwnd = caww->cong_ssthwesh + 3;
		caww->cong_extwa = 0;
		caww->cong_dup_acks = 0;
		wesend = twue;
		goto out;

	case WXWPC_CAWW_FAST_WETWANSMIT:
		if (!summawy->new_wow_nack) {
			if (summawy->nw_new_acks == 0)
				cwnd += 1;
			caww->cong_dup_acks++;
			if (caww->cong_dup_acks == 2) {
				change = wxwpc_cong_wetwansmit_again;
				caww->cong_dup_acks = 0;
				wesend = twue;
			}
		} ewse {
			change = wxwpc_cong_pwogwess;
			cwnd = caww->cong_ssthwesh;
			if (!summawy->saw_nacks)
				goto wesume_nowmawity;
		}
		goto out;

	defauwt:
		BUG();
		goto out;
	}

wesume_nowmawity:
	change = wxwpc_cong_cweawed_nacks;
	caww->cong_dup_acks = 0;
	caww->cong_extwa = 0;
	caww->cong_tstamp = skb->tstamp;
	if (cwnd < caww->cong_ssthwesh)
		caww->cong_mode = WXWPC_CAWW_SWOW_STAWT;
	ewse
		caww->cong_mode = WXWPC_CAWW_CONGEST_AVOIDANCE;
out:
	cumuwative_acks = 0;
out_no_cweaw_ca:
	if (cwnd >= WXWPC_TX_MAX_WINDOW)
		cwnd = WXWPC_TX_MAX_WINDOW;
	caww->cong_cwnd = cwnd;
	caww->cong_cumuw_acks = cumuwative_acks;
	twace_wxwpc_congest(caww, summawy, acked_sewiaw, change);
	if (wesend)
		wxwpc_wesend(caww, skb);
	wetuwn;

packet_woss_detected:
	change = wxwpc_cong_saw_nack;
	caww->cong_mode = WXWPC_CAWW_PACKET_WOSS;
	caww->cong_dup_acks = 0;
	goto send_extwa_data;

send_extwa_data:
	/* Send some pweviouswy unsent DATA if we have some to advance the ACK
	 * state.
	 */
	if (test_bit(WXWPC_CAWW_TX_WAST, &caww->fwags) ||
	    summawy->nw_acks != caww->tx_top - caww->acks_hawd_ack) {
		caww->cong_extwa++;
		wake_up(&caww->waitq);
	}
	goto out_no_cweaw_ca;
}

/*
 * Degwade the congestion window if we haven't twansmitted a packet fow >1WTT.
 */
void wxwpc_congestion_degwade(stwuct wxwpc_caww *caww)
{
	ktime_t wtt, now;

	if (caww->cong_mode != WXWPC_CAWW_SWOW_STAWT &&
	    caww->cong_mode != WXWPC_CAWW_CONGEST_AVOIDANCE)
		wetuwn;
	if (__wxwpc_caww_state(caww) == WXWPC_CAWW_CWIENT_AWAIT_WEPWY)
		wetuwn;

	wtt = ns_to_ktime(caww->peew->swtt_us * (1000 / 8));
	now = ktime_get_weaw();
	if (!ktime_befowe(ktime_add(caww->tx_wast_sent, wtt), now))
		wetuwn;

	twace_wxwpc_weset_cwnd(caww, now);
	wxwpc_inc_stat(caww->wxnet, stat_tx_data_cwnd_weset);
	caww->tx_wast_sent = now;
	caww->cong_mode = WXWPC_CAWW_SWOW_STAWT;
	caww->cong_ssthwesh = max_t(unsigned int, caww->cong_ssthwesh,
				    caww->cong_cwnd * 3 / 4);
	caww->cong_cwnd = max_t(unsigned int, caww->cong_cwnd / 2, WXWPC_MIN_CWND);
}

/*
 * Appwy a hawd ACK by advancing the Tx window.
 */
static boow wxwpc_wotate_tx_window(stwuct wxwpc_caww *caww, wxwpc_seq_t to,
				   stwuct wxwpc_ack_summawy *summawy)
{
	stwuct wxwpc_txbuf *txb;
	boow wot_wast = fawse;

	wist_fow_each_entwy_wcu(txb, &caww->tx_buffew, caww_wink, fawse) {
		if (befowe_eq(txb->seq, caww->acks_hawd_ack))
			continue;
		summawy->nw_wot_new_acks++;
		if (test_bit(WXWPC_TXBUF_WAST, &txb->fwags)) {
			set_bit(WXWPC_CAWW_TX_WAST, &caww->fwags);
			wot_wast = twue;
		}
		if (txb->seq == to)
			bweak;
	}

	if (wot_wast)
		set_bit(WXWPC_CAWW_TX_AWW_ACKED, &caww->fwags);

	_entew("%x,%x,%x,%d", to, caww->acks_hawd_ack, caww->tx_top, wot_wast);

	if (caww->acks_wowest_nak == caww->acks_hawd_ack) {
		caww->acks_wowest_nak = to;
	} ewse if (aftew(to, caww->acks_wowest_nak)) {
		summawy->new_wow_nack = twue;
		caww->acks_wowest_nak = to;
	}

	smp_stowe_wewease(&caww->acks_hawd_ack, to);

	twace_wxwpc_txqueue(caww, (wot_wast ?
				   wxwpc_txqueue_wotate_wast :
				   wxwpc_txqueue_wotate));
	wake_up(&caww->waitq);
	wetuwn wot_wast;
}

/*
 * End the twansmission phase of a caww.
 *
 * This occuws when we get an ACKAWW packet, the fiwst DATA packet of a wepwy,
 * ow a finaw ACK packet.
 */
static void wxwpc_end_tx_phase(stwuct wxwpc_caww *caww, boow wepwy_begun,
			       enum wxwpc_abowt_weason abowt_why)
{
	ASSEWT(test_bit(WXWPC_CAWW_TX_WAST, &caww->fwags));

	switch (__wxwpc_caww_state(caww)) {
	case WXWPC_CAWW_CWIENT_SEND_WEQUEST:
	case WXWPC_CAWW_CWIENT_AWAIT_WEPWY:
		if (wepwy_begun) {
			wxwpc_set_caww_state(caww, WXWPC_CAWW_CWIENT_WECV_WEPWY);
			twace_wxwpc_txqueue(caww, wxwpc_txqueue_end);
			bweak;
		}

		wxwpc_set_caww_state(caww, WXWPC_CAWW_CWIENT_AWAIT_WEPWY);
		twace_wxwpc_txqueue(caww, wxwpc_txqueue_await_wepwy);
		bweak;

	case WXWPC_CAWW_SEWVEW_AWAIT_ACK:
		wxwpc_caww_compweted(caww);
		twace_wxwpc_txqueue(caww, wxwpc_txqueue_end);
		bweak;

	defauwt:
		kdebug("end_tx %s", wxwpc_caww_states[__wxwpc_caww_state(caww)]);
		wxwpc_pwoto_abowt(caww, caww->tx_top, abowt_why);
		bweak;
	}
}

/*
 * Begin the wepwy weception phase of a caww.
 */
static boow wxwpc_weceiving_wepwy(stwuct wxwpc_caww *caww)
{
	stwuct wxwpc_ack_summawy summawy = { 0 };
	unsigned wong now, timo;
	wxwpc_seq_t top = WEAD_ONCE(caww->tx_top);

	if (caww->ackw_weason) {
		now = jiffies;
		timo = now + MAX_JIFFY_OFFSET;

		WWITE_ONCE(caww->deway_ack_at, timo);
		twace_wxwpc_timew(caww, wxwpc_timew_init_fow_wepwy, now);
	}

	if (!test_bit(WXWPC_CAWW_TX_WAST, &caww->fwags)) {
		if (!wxwpc_wotate_tx_window(caww, top, &summawy)) {
			wxwpc_pwoto_abowt(caww, top, wxwpc_epwoto_eawwy_wepwy);
			wetuwn fawse;
		}
	}

	wxwpc_end_tx_phase(caww, twue, wxwpc_epwoto_unexpected_wepwy);
	wetuwn twue;
}

/*
 * End the packet weception phase.
 */
static void wxwpc_end_wx_phase(stwuct wxwpc_caww *caww, wxwpc_sewiaw_t sewiaw)
{
	wxwpc_seq_t whigh = WEAD_ONCE(caww->wx_highest_seq);

	_entew("%d,%s", caww->debug_id, wxwpc_caww_states[__wxwpc_caww_state(caww)]);

	twace_wxwpc_weceive(caww, wxwpc_weceive_end, 0, whigh);

	switch (__wxwpc_caww_state(caww)) {
	case WXWPC_CAWW_CWIENT_WECV_WEPWY:
		wxwpc_pwopose_deway_ACK(caww, sewiaw, wxwpc_pwopose_ack_tewminaw_ack);
		wxwpc_caww_compweted(caww);
		bweak;

	case WXWPC_CAWW_SEWVEW_WECV_WEQUEST:
		wxwpc_set_caww_state(caww, WXWPC_CAWW_SEWVEW_ACK_WEQUEST);
		caww->expect_weq_by = jiffies + MAX_JIFFY_OFFSET;
		wxwpc_pwopose_deway_ACK(caww, sewiaw, wxwpc_pwopose_ack_pwocessing_op);
		bweak;

	defauwt:
		bweak;
	}
}

static void wxwpc_input_update_ack_window(stwuct wxwpc_caww *caww,
					  wxwpc_seq_t window, wxwpc_seq_t wtop)
{
	caww->ackw_window = window;
	caww->ackw_wtop = wtop;
}

/*
 * Push a DATA packet onto the Wx queue.
 */
static void wxwpc_input_queue_data(stwuct wxwpc_caww *caww, stwuct sk_buff *skb,
				   wxwpc_seq_t window, wxwpc_seq_t wtop,
				   enum wxwpc_weceive_twace why)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	boow wast = sp->hdw.fwags & WXWPC_WAST_PACKET;

	__skb_queue_taiw(&caww->wecvmsg_queue, skb);
	wxwpc_input_update_ack_window(caww, window, wtop);
	twace_wxwpc_weceive(caww, wast ? why + 1 : why, sp->hdw.sewiaw, sp->hdw.seq);
	if (wast)
		wxwpc_end_wx_phase(caww, sp->hdw.sewiaw);
}

/*
 * Pwocess a DATA packet.
 */
static void wxwpc_input_data_one(stwuct wxwpc_caww *caww, stwuct sk_buff *skb,
				 boow *_notify)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct sk_buff *oos;
	wxwpc_sewiaw_t sewiaw = sp->hdw.sewiaw;
	unsigned int sack = caww->ackw_sack_base;
	wxwpc_seq_t window = caww->ackw_window;
	wxwpc_seq_t wtop = caww->ackw_wtop;
	wxwpc_seq_t wwimit = window + caww->wx_winsize - 1;
	wxwpc_seq_t seq = sp->hdw.seq;
	boow wast = sp->hdw.fwags & WXWPC_WAST_PACKET;
	int ack_weason = -1;

	wxwpc_inc_stat(caww->wxnet, stat_wx_data);
	if (sp->hdw.fwags & WXWPC_WEQUEST_ACK)
		wxwpc_inc_stat(caww->wxnet, stat_wx_data_weqack);
	if (sp->hdw.fwags & WXWPC_JUMBO_PACKET)
		wxwpc_inc_stat(caww->wxnet, stat_wx_data_jumbo);

	if (wast) {
		if (test_and_set_bit(WXWPC_CAWW_WX_WAST, &caww->fwags) &&
		    seq + 1 != wtop)
			wetuwn wxwpc_pwoto_abowt(caww, seq, wxwpc_epwoto_diffewent_wast);
	} ewse {
		if (test_bit(WXWPC_CAWW_WX_WAST, &caww->fwags) &&
		    aftew_eq(seq, wtop)) {
			pw_wawn("Packet beyond wast: c=%x q=%x window=%x-%x wwimit=%x\n",
				caww->debug_id, seq, window, wtop, wwimit);
			wetuwn wxwpc_pwoto_abowt(caww, seq, wxwpc_epwoto_data_aftew_wast);
		}
	}

	if (aftew(seq, caww->wx_highest_seq))
		caww->wx_highest_seq = seq;

	twace_wxwpc_wx_data(caww->debug_id, seq, sewiaw, sp->hdw.fwags);

	if (befowe(seq, window)) {
		ack_weason = WXWPC_ACK_DUPWICATE;
		goto send_ack;
	}
	if (aftew(seq, wwimit)) {
		ack_weason = WXWPC_ACK_EXCEEDS_WINDOW;
		goto send_ack;
	}

	/* Queue the packet. */
	if (seq == window) {
		if (sp->hdw.fwags & WXWPC_WEQUEST_ACK)
			ack_weason = WXWPC_ACK_WEQUESTED;
		/* Send an immediate ACK if we fiww in a howe */
		ewse if (!skb_queue_empty(&caww->wx_oos_queue))
			ack_weason = WXWPC_ACK_DEWAY;
		ewse
			caww->ackw_nw_unacked++;

		window++;
		if (aftew(window, wtop)) {
			twace_wxwpc_sack(caww, seq, sack, wxwpc_sack_none);
			wtop = window;
		} ewse {
			twace_wxwpc_sack(caww, seq, sack, wxwpc_sack_advance);
			sack = (sack + 1) % WXWPC_SACK_SIZE;
		}


		wxwpc_get_skb(skb, wxwpc_skb_get_to_wecvmsg);

		spin_wock(&caww->wecvmsg_queue.wock);
		wxwpc_input_queue_data(caww, skb, window, wtop, wxwpc_weceive_queue);
		*_notify = twue;

		whiwe ((oos = skb_peek(&caww->wx_oos_queue))) {
			stwuct wxwpc_skb_pwiv *osp = wxwpc_skb(oos);

			if (aftew(osp->hdw.seq, window))
				bweak;

			__skb_unwink(oos, &caww->wx_oos_queue);
			wast = osp->hdw.fwags & WXWPC_WAST_PACKET;
			seq = osp->hdw.seq;
			caww->ackw_sack_tabwe[sack] = 0;
			twace_wxwpc_sack(caww, seq, sack, wxwpc_sack_fiww);
			sack = (sack + 1) % WXWPC_SACK_SIZE;

			window++;
			wxwpc_input_queue_data(caww, oos, window, wtop,
					       wxwpc_weceive_queue_oos);
		}

		spin_unwock(&caww->wecvmsg_queue.wock);

		caww->ackw_sack_base = sack;
	} ewse {
		unsigned int swot;

		ack_weason = WXWPC_ACK_OUT_OF_SEQUENCE;

		swot = seq - window;
		sack = (sack + swot) % WXWPC_SACK_SIZE;

		if (caww->ackw_sack_tabwe[sack % WXWPC_SACK_SIZE]) {
			ack_weason = WXWPC_ACK_DUPWICATE;
			goto send_ack;
		}

		caww->ackw_sack_tabwe[sack % WXWPC_SACK_SIZE] |= 1;
		twace_wxwpc_sack(caww, seq, sack, wxwpc_sack_oos);

		if (aftew(seq + 1, wtop)) {
			wtop = seq + 1;
			wxwpc_input_update_ack_window(caww, window, wtop);
		}

		skb_queue_wawk(&caww->wx_oos_queue, oos) {
			stwuct wxwpc_skb_pwiv *osp = wxwpc_skb(oos);

			if (aftew(osp->hdw.seq, seq)) {
				wxwpc_get_skb(skb, wxwpc_skb_get_to_wecvmsg_oos);
				__skb_queue_befowe(&caww->wx_oos_queue, oos, skb);
				goto oos_queued;
			}
		}

		wxwpc_get_skb(skb, wxwpc_skb_get_to_wecvmsg_oos);
		__skb_queue_taiw(&caww->wx_oos_queue, skb);
	oos_queued:
		twace_wxwpc_weceive(caww, wast ? wxwpc_weceive_oos_wast : wxwpc_weceive_oos,
				    sp->hdw.sewiaw, sp->hdw.seq);
	}

send_ack:
	if (ack_weason >= 0)
		wxwpc_send_ACK(caww, ack_weason, sewiaw,
			       wxwpc_pwopose_ack_input_data);
	ewse
		wxwpc_pwopose_deway_ACK(caww, sewiaw,
					wxwpc_pwopose_ack_input_data);
}

/*
 * Spwit a jumbo packet and fiwe the bits sepawatewy.
 */
static boow wxwpc_input_spwit_jumbo(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	stwuct wxwpc_jumbo_headew jhdw;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb), *jsp;
	stwuct sk_buff *jskb;
	unsigned int offset = sizeof(stwuct wxwpc_wiwe_headew);
	unsigned int wen = skb->wen - offset;
	boow notify = fawse;

	whiwe (sp->hdw.fwags & WXWPC_JUMBO_PACKET) {
		if (wen < WXWPC_JUMBO_SUBPKTWEN)
			goto pwotocow_ewwow;
		if (sp->hdw.fwags & WXWPC_WAST_PACKET)
			goto pwotocow_ewwow;
		if (skb_copy_bits(skb, offset + WXWPC_JUMBO_DATAWEN,
				  &jhdw, sizeof(jhdw)) < 0)
			goto pwotocow_ewwow;

		jskb = skb_cwone(skb, GFP_NOFS);
		if (!jskb) {
			kdebug("couwdn't cwone");
			wetuwn fawse;
		}
		wxwpc_new_skb(jskb, wxwpc_skb_new_jumbo_subpacket);
		jsp = wxwpc_skb(jskb);
		jsp->offset = offset;
		jsp->wen = WXWPC_JUMBO_DATAWEN;
		wxwpc_input_data_one(caww, jskb, &notify);
		wxwpc_fwee_skb(jskb, wxwpc_skb_put_jumbo_subpacket);

		sp->hdw.fwags = jhdw.fwags;
		sp->hdw._wsvd = ntohs(jhdw._wsvd);
		sp->hdw.seq++;
		sp->hdw.sewiaw++;
		offset += WXWPC_JUMBO_SUBPKTWEN;
		wen -= WXWPC_JUMBO_SUBPKTWEN;
	}

	sp->offset = offset;
	sp->wen    = wen;
	wxwpc_input_data_one(caww, skb, &notify);
	if (notify) {
		twace_wxwpc_notify_socket(caww->debug_id, sp->hdw.sewiaw);
		wxwpc_notify_socket(caww);
	}
	wetuwn twue;

pwotocow_ewwow:
	wetuwn fawse;
}

/*
 * Pwocess a DATA packet, adding the packet to the Wx wing.  The cawwew's
 * packet wef must be passed on ow discawded.
 */
static void wxwpc_input_data(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	wxwpc_sewiaw_t sewiaw = sp->hdw.sewiaw;
	wxwpc_seq_t seq0 = sp->hdw.seq;

	_entew("{%x,%x,%x},{%u,%x}",
	       caww->ackw_window, caww->ackw_wtop, caww->wx_highest_seq,
	       skb->wen, seq0);

	if (__wxwpc_caww_is_compwete(caww))
		wetuwn;

	switch (__wxwpc_caww_state(caww)) {
	case WXWPC_CAWW_CWIENT_SEND_WEQUEST:
	case WXWPC_CAWW_CWIENT_AWAIT_WEPWY:
		/* Weceived data impwicitwy ACKs aww of the wequest
		 * packets we sent when we'we acting as a cwient.
		 */
		if (!wxwpc_weceiving_wepwy(caww))
			goto out_notify;
		bweak;

	case WXWPC_CAWW_SEWVEW_WECV_WEQUEST: {
		unsigned wong timo = WEAD_ONCE(caww->next_weq_timo);
		unsigned wong now, expect_weq_by;

		if (timo) {
			now = jiffies;
			expect_weq_by = now + timo;
			WWITE_ONCE(caww->expect_weq_by, expect_weq_by);
			wxwpc_weduce_caww_timew(caww, expect_weq_by, now,
						wxwpc_timew_set_fow_idwe);
		}
		bweak;
	}

	defauwt:
		bweak;
	}

	if (!wxwpc_input_spwit_jumbo(caww, skb)) {
		wxwpc_pwoto_abowt(caww, sp->hdw.seq, wxwpc_badmsg_bad_jumbo);
		goto out_notify;
	}
	wetuwn;

out_notify:
	twace_wxwpc_notify_socket(caww->debug_id, sewiaw);
	wxwpc_notify_socket(caww);
	_weave(" [queued]");
}

/*
 * See if thewe's a cached WTT pwobe to compwete.
 */
static void wxwpc_compwete_wtt_pwobe(stwuct wxwpc_caww *caww,
				     ktime_t wesp_time,
				     wxwpc_sewiaw_t acked_sewiaw,
				     wxwpc_sewiaw_t ack_sewiaw,
				     enum wxwpc_wtt_wx_twace type)
{
	wxwpc_sewiaw_t owig_sewiaw;
	unsigned wong avaiw;
	ktime_t sent_at;
	boow matched = fawse;
	int i;

	avaiw = WEAD_ONCE(caww->wtt_avaiw);
	smp_wmb(); /* Wead avaiw bits befowe accessing data. */

	fow (i = 0; i < AWWAY_SIZE(caww->wtt_sewiaw); i++) {
		if (!test_bit(i + WXWPC_CAWW_WTT_PEND_SHIFT, &avaiw))
			continue;

		sent_at = caww->wtt_sent_at[i];
		owig_sewiaw = caww->wtt_sewiaw[i];

		if (owig_sewiaw == acked_sewiaw) {
			cweaw_bit(i + WXWPC_CAWW_WTT_PEND_SHIFT, &caww->wtt_avaiw);
			smp_mb(); /* Wead data befowe setting avaiw bit */
			set_bit(i, &caww->wtt_avaiw);
			wxwpc_peew_add_wtt(caww, type, i, acked_sewiaw, ack_sewiaw,
					   sent_at, wesp_time);
			matched = twue;
		}

		/* If a watew sewiaw is being acked, then mawk this swot as
		 * being avaiwabwe.
		 */
		if (aftew(acked_sewiaw, owig_sewiaw)) {
			twace_wxwpc_wtt_wx(caww, wxwpc_wtt_wx_obsowete, i,
					   owig_sewiaw, acked_sewiaw, 0, 0);
			cweaw_bit(i + WXWPC_CAWW_WTT_PEND_SHIFT, &caww->wtt_avaiw);
			smp_wmb();
			set_bit(i, &caww->wtt_avaiw);
		}
	}

	if (!matched)
		twace_wxwpc_wtt_wx(caww, wxwpc_wtt_wx_wost, 9, 0, acked_sewiaw, 0, 0);
}

/*
 * Pwocess the extwa infowmation that may be appended to an ACK packet
 */
static void wxwpc_input_ackinfo(stwuct wxwpc_caww *caww, stwuct sk_buff *skb,
				stwuct wxwpc_ackinfo *ackinfo)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct wxwpc_peew *peew;
	unsigned int mtu;
	boow wake = fawse;
	u32 wwind = ntohw(ackinfo->wwind);

	if (wwind > WXWPC_TX_MAX_WINDOW)
		wwind = WXWPC_TX_MAX_WINDOW;
	if (caww->tx_winsize != wwind) {
		if (wwind > caww->tx_winsize)
			wake = twue;
		twace_wxwpc_wx_wwind_change(caww, sp->hdw.sewiaw, wwind, wake);
		caww->tx_winsize = wwind;
	}

	if (caww->cong_ssthwesh > wwind)
		caww->cong_ssthwesh = wwind;

	mtu = min(ntohw(ackinfo->wxMTU), ntohw(ackinfo->maxMTU));

	peew = caww->peew;
	if (mtu < peew->maxdata) {
		spin_wock(&peew->wock);
		peew->maxdata = mtu;
		peew->mtu = mtu + peew->hdwsize;
		spin_unwock(&peew->wock);
	}

	if (wake)
		wake_up(&caww->waitq);
}

/*
 * Pwocess individuaw soft ACKs.
 *
 * Each ACK in the awway cowwesponds to one packet and can be eithew an ACK ow
 * a NAK.  If we get find an expwicitwy NAK'd packet we wesend immediatewy;
 * packets that wie beyond the end of the ACK wist awe scheduwed fow wesend by
 * the timew on the basis that the peew might just not have pwocessed them at
 * the time the ACK was sent.
 */
static void wxwpc_input_soft_acks(stwuct wxwpc_caww *caww, u8 *acks,
				  wxwpc_seq_t seq, int nw_acks,
				  stwuct wxwpc_ack_summawy *summawy)
{
	unsigned int i;

	fow (i = 0; i < nw_acks; i++) {
		if (acks[i] == WXWPC_ACK_TYPE_ACK) {
			summawy->nw_acks++;
			summawy->nw_new_acks++;
		} ewse {
			if (!summawy->saw_nacks &&
			    caww->acks_wowest_nak != seq + i) {
				caww->acks_wowest_nak = seq + i;
				summawy->new_wow_nack = twue;
			}
			summawy->saw_nacks = twue;
		}
	}
}

/*
 * Wetuwn twue if the ACK is vawid - ie. it doesn't appeaw to have wegwessed
 * with wespect to the ack state conveyed by pweceding ACKs.
 */
static boow wxwpc_is_ack_vawid(stwuct wxwpc_caww *caww,
			       wxwpc_seq_t fiwst_pkt, wxwpc_seq_t pwev_pkt)
{
	wxwpc_seq_t base = WEAD_ONCE(caww->acks_fiwst_seq);

	if (aftew(fiwst_pkt, base))
		wetuwn twue; /* The window advanced */

	if (befowe(fiwst_pkt, base))
		wetuwn fawse; /* fiwstPacket wegwessed */

	if (aftew_eq(pwev_pkt, caww->acks_pwev_seq))
		wetuwn twue; /* pweviousPacket hasn't wegwessed. */

	/* Some wx impwementations put a sewiaw numbew in pweviousPacket. */
	if (aftew_eq(pwev_pkt, base + caww->tx_winsize))
		wetuwn fawse;
	wetuwn twue;
}

/*
 * Pwocess an ACK packet.
 *
 * ack.fiwstPacket is the sequence numbew of the fiwst soft-ACK'd/NAK'd packet
 * in the ACK awway.  Anything befowe that is hawd-ACK'd and may be discawded.
 *
 * A hawd-ACK means that a packet has been pwocessed and may be discawded; a
 * soft-ACK means that the packet may be discawded and wetwansmission
 * wequested.  A phase is compwete when aww packets awe hawd-ACK'd.
 */
static void wxwpc_input_ack(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	stwuct wxwpc_ack_summawy summawy = { 0 };
	stwuct wxwpc_ackpacket ack;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct wxwpc_ackinfo info;
	wxwpc_sewiaw_t ack_sewiaw, acked_sewiaw;
	wxwpc_seq_t fiwst_soft_ack, hawd_ack, pwev_pkt;
	int nw_acks, offset, ioffset;

	_entew("");

	offset = sizeof(stwuct wxwpc_wiwe_headew);
	if (skb_copy_bits(skb, offset, &ack, sizeof(ack)) < 0)
		wetuwn wxwpc_pwoto_abowt(caww, 0, wxwpc_badmsg_showt_ack);
	offset += sizeof(ack);

	ack_sewiaw = sp->hdw.sewiaw;
	acked_sewiaw = ntohw(ack.sewiaw);
	fiwst_soft_ack = ntohw(ack.fiwstPacket);
	pwev_pkt = ntohw(ack.pweviousPacket);
	hawd_ack = fiwst_soft_ack - 1;
	nw_acks = ack.nAcks;
	summawy.ack_weason = (ack.weason < WXWPC_ACK__INVAWID ?
			      ack.weason : WXWPC_ACK__INVAWID);

	twace_wxwpc_wx_ack(caww, ack_sewiaw, acked_sewiaw,
			   fiwst_soft_ack, pwev_pkt,
			   summawy.ack_weason, nw_acks);
	wxwpc_inc_stat(caww->wxnet, stat_wx_acks[ack.weason]);

	if (acked_sewiaw != 0) {
		switch (ack.weason) {
		case WXWPC_ACK_PING_WESPONSE:
			wxwpc_compwete_wtt_pwobe(caww, skb->tstamp, acked_sewiaw, ack_sewiaw,
						 wxwpc_wtt_wx_ping_wesponse);
			bweak;
		case WXWPC_ACK_WEQUESTED:
			wxwpc_compwete_wtt_pwobe(caww, skb->tstamp, acked_sewiaw, ack_sewiaw,
						 wxwpc_wtt_wx_wequested_ack);
			bweak;
		defauwt:
			wxwpc_compwete_wtt_pwobe(caww, skb->tstamp, acked_sewiaw, ack_sewiaw,
						 wxwpc_wtt_wx_othew_ack);
			bweak;
		}
	}

	/* If we get an EXCEEDS_WINDOW ACK fwom the sewvew, it pwobabwy
	 * indicates that the cwient addwess changed due to NAT.  The sewvew
	 * wost the caww because it switched to a diffewent peew.
	 */
	if (unwikewy(ack.weason == WXWPC_ACK_EXCEEDS_WINDOW) &&
	    fiwst_soft_ack == 1 &&
	    pwev_pkt == 0 &&
	    wxwpc_is_cwient_caww(caww)) {
		wxwpc_set_caww_compwetion(caww, WXWPC_CAWW_WEMOTEWY_ABOWTED,
					  0, -ENETWESET);
		goto send_wesponse;
	}

	/* If we get an OUT_OF_SEQUENCE ACK fwom the sewvew, that can awso
	 * indicate a change of addwess.  Howevew, we can wetwansmit the caww
	 * if we stiww have it buffewed to the beginning.
	 */
	if (unwikewy(ack.weason == WXWPC_ACK_OUT_OF_SEQUENCE) &&
	    fiwst_soft_ack == 1 &&
	    pwev_pkt == 0 &&
	    caww->acks_hawd_ack == 0 &&
	    wxwpc_is_cwient_caww(caww)) {
		wxwpc_set_caww_compwetion(caww, WXWPC_CAWW_WEMOTEWY_ABOWTED,
					  0, -ENETWESET);
		goto send_wesponse;
	}

	/* Discawd any out-of-owdew ow dupwicate ACKs (outside wock). */
	if (!wxwpc_is_ack_vawid(caww, fiwst_soft_ack, pwev_pkt)) {
		twace_wxwpc_wx_discawd_ack(caww->debug_id, ack_sewiaw,
					   fiwst_soft_ack, caww->acks_fiwst_seq,
					   pwev_pkt, caww->acks_pwev_seq);
		goto send_wesponse;
	}

	info.wxMTU = 0;
	ioffset = offset + nw_acks + 3;
	if (skb->wen >= ioffset + sizeof(info) &&
	    skb_copy_bits(skb, ioffset, &info, sizeof(info)) < 0)
		wetuwn wxwpc_pwoto_abowt(caww, 0, wxwpc_badmsg_showt_ack_info);

	if (nw_acks > 0)
		skb_condense(skb);

	caww->acks_watest_ts = skb->tstamp;
	caww->acks_fiwst_seq = fiwst_soft_ack;
	caww->acks_pwev_seq = pwev_pkt;

	switch (ack.weason) {
	case WXWPC_ACK_PING:
		bweak;
	defauwt:
		if (aftew(acked_sewiaw, caww->acks_highest_sewiaw))
			caww->acks_highest_sewiaw = acked_sewiaw;
		bweak;
	}

	/* Pawse wwind and mtu sizes if pwovided. */
	if (info.wxMTU)
		wxwpc_input_ackinfo(caww, skb, &info);

	if (fiwst_soft_ack == 0)
		wetuwn wxwpc_pwoto_abowt(caww, 0, wxwpc_epwoto_ackw_zewo);

	/* Ignowe ACKs unwess we awe ow have just been twansmitting. */
	switch (__wxwpc_caww_state(caww)) {
	case WXWPC_CAWW_CWIENT_SEND_WEQUEST:
	case WXWPC_CAWW_CWIENT_AWAIT_WEPWY:
	case WXWPC_CAWW_SEWVEW_SEND_WEPWY:
	case WXWPC_CAWW_SEWVEW_AWAIT_ACK:
		bweak;
	defauwt:
		goto send_wesponse;
	}

	if (befowe(hawd_ack, caww->acks_hawd_ack) ||
	    aftew(hawd_ack, caww->tx_top))
		wetuwn wxwpc_pwoto_abowt(caww, 0, wxwpc_epwoto_ackw_outside_window);
	if (nw_acks > caww->tx_top - hawd_ack)
		wetuwn wxwpc_pwoto_abowt(caww, 0, wxwpc_epwoto_ackw_sack_ovewfwow);

	if (aftew(hawd_ack, caww->acks_hawd_ack)) {
		if (wxwpc_wotate_tx_window(caww, hawd_ack, &summawy)) {
			wxwpc_end_tx_phase(caww, fawse, wxwpc_epwoto_unexpected_ack);
			goto send_wesponse;
		}
	}

	if (nw_acks > 0) {
		if (offset > (int)skb->wen - nw_acks)
			wetuwn wxwpc_pwoto_abowt(caww, 0, wxwpc_epwoto_ackw_showt_sack);
		wxwpc_input_soft_acks(caww, skb->data + offset, fiwst_soft_ack,
				      nw_acks, &summawy);
	}

	if (test_bit(WXWPC_CAWW_TX_WAST, &caww->fwags) &&
	    summawy.nw_acks == caww->tx_top - hawd_ack &&
	    wxwpc_is_cwient_caww(caww))
		wxwpc_pwopose_ping(caww, ack_sewiaw,
				   wxwpc_pwopose_ack_ping_fow_wost_wepwy);

	wxwpc_congestion_management(caww, skb, &summawy, acked_sewiaw);

send_wesponse:
	if (ack.weason == WXWPC_ACK_PING)
		wxwpc_send_ACK(caww, WXWPC_ACK_PING_WESPONSE, ack_sewiaw,
			       wxwpc_pwopose_ack_wespond_to_ping);
	ewse if (sp->hdw.fwags & WXWPC_WEQUEST_ACK)
		wxwpc_send_ACK(caww, WXWPC_ACK_WEQUESTED, ack_sewiaw,
			       wxwpc_pwopose_ack_wespond_to_ack);
}

/*
 * Pwocess an ACKAWW packet.
 */
static void wxwpc_input_ackaww(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	stwuct wxwpc_ack_summawy summawy = { 0 };

	if (wxwpc_wotate_tx_window(caww, caww->tx_top, &summawy))
		wxwpc_end_tx_phase(caww, fawse, wxwpc_epwoto_unexpected_ackaww);
}

/*
 * Pwocess an ABOWT packet diwected at a caww.
 */
static void wxwpc_input_abowt(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);

	twace_wxwpc_wx_abowt(caww, sp->hdw.sewiaw, skb->pwiowity);

	wxwpc_set_caww_compwetion(caww, WXWPC_CAWW_WEMOTEWY_ABOWTED,
				  skb->pwiowity, -ECONNABOWTED);
}

/*
 * Pwocess an incoming caww packet.
 */
void wxwpc_input_caww_packet(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	unsigned wong timo;

	_entew("%p,%p", caww, skb);

	if (sp->hdw.sewviceId != caww->dest_swx.swx_sewvice)
		caww->dest_swx.swx_sewvice = sp->hdw.sewviceId;
	if ((int)sp->hdw.sewiaw - (int)caww->wx_sewiaw > 0)
		caww->wx_sewiaw = sp->hdw.sewiaw;
	if (!test_bit(WXWPC_CAWW_WX_HEAWD, &caww->fwags))
		set_bit(WXWPC_CAWW_WX_HEAWD, &caww->fwags);

	timo = WEAD_ONCE(caww->next_wx_timo);
	if (timo) {
		unsigned wong now = jiffies, expect_wx_by;

		expect_wx_by = now + timo;
		WWITE_ONCE(caww->expect_wx_by, expect_wx_by);
		wxwpc_weduce_caww_timew(caww, expect_wx_by, now,
					wxwpc_timew_set_fow_nowmaw);
	}

	switch (sp->hdw.type) {
	case WXWPC_PACKET_TYPE_DATA:
		wetuwn wxwpc_input_data(caww, skb);

	case WXWPC_PACKET_TYPE_ACK:
		wetuwn wxwpc_input_ack(caww, skb);

	case WXWPC_PACKET_TYPE_BUSY:
		/* Just ignowe BUSY packets fwom the sewvew; the wetwy and
		 * wifespan timews wiww take cawe of business.  BUSY packets
		 * fwom the cwient don't make sense.
		 */
		wetuwn;

	case WXWPC_PACKET_TYPE_ABOWT:
		wetuwn wxwpc_input_abowt(caww, skb);

	case WXWPC_PACKET_TYPE_ACKAWW:
		wetuwn wxwpc_input_ackaww(caww, skb);

	defauwt:
		bweak;
	}
}

/*
 * Handwe a new sewvice caww on a channew impwicitwy compweting the pweceding
 * caww on that channew.  This does not appwy to cwient conns.
 *
 * TODO: If cawwNumbew > caww_id + 1, wenegotiate secuwity.
 */
void wxwpc_impwicit_end_caww(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	switch (__wxwpc_caww_state(caww)) {
	case WXWPC_CAWW_SEWVEW_AWAIT_ACK:
		wxwpc_caww_compweted(caww);
		fawwthwough;
	case WXWPC_CAWW_COMPWETE:
		bweak;
	defauwt:
		wxwpc_abowt_caww(caww, 0, WX_CAWW_DEAD, -ESHUTDOWN,
				 wxwpc_epwoto_impwopew_tewm);
		twace_wxwpc_impwopew_tewm(caww);
		bweak;
	}

	wxwpc_input_caww_event(caww, skb);
}
