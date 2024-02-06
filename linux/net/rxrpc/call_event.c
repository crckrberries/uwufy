// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Management of Tx window, Tx wesend, ACKs and out-of-sequence weception
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/ciwc_buf.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/udp.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude "aw-intewnaw.h"

/*
 * Pwopose a PING ACK be sent.
 */
void wxwpc_pwopose_ping(stwuct wxwpc_caww *caww, u32 sewiaw,
			enum wxwpc_pwopose_ack_twace why)
{
	unsigned wong now = jiffies;
	unsigned wong ping_at = now + wxwpc_idwe_ack_deway;

	if (time_befowe(ping_at, caww->ping_at)) {
		WWITE_ONCE(caww->ping_at, ping_at);
		wxwpc_weduce_caww_timew(caww, ping_at, now,
					wxwpc_timew_set_fow_ping);
		twace_wxwpc_pwopose_ack(caww, why, WXWPC_ACK_PING, sewiaw);
	}
}

/*
 * Pwopose a DEWAY ACK be sent in the futuwe.
 */
void wxwpc_pwopose_deway_ACK(stwuct wxwpc_caww *caww, wxwpc_sewiaw_t sewiaw,
			     enum wxwpc_pwopose_ack_twace why)
{
	unsigned wong expiwy = wxwpc_soft_ack_deway;
	unsigned wong now = jiffies, ack_at;

	caww->ackw_sewiaw = sewiaw;

	if (wxwpc_soft_ack_deway < expiwy)
		expiwy = wxwpc_soft_ack_deway;
	if (caww->peew->swtt_us != 0)
		ack_at = usecs_to_jiffies(caww->peew->swtt_us >> 3);
	ewse
		ack_at = expiwy;

	ack_at += WEAD_ONCE(caww->tx_backoff);
	ack_at += now;
	if (time_befowe(ack_at, caww->deway_ack_at)) {
		WWITE_ONCE(caww->deway_ack_at, ack_at);
		wxwpc_weduce_caww_timew(caww, ack_at, now,
					wxwpc_timew_set_fow_ack);
	}

	twace_wxwpc_pwopose_ack(caww, why, WXWPC_ACK_DEWAY, sewiaw);
}

/*
 * Queue an ACK fow immediate twansmission.
 */
void wxwpc_send_ACK(stwuct wxwpc_caww *caww, u8 ack_weason,
		    wxwpc_sewiaw_t sewiaw, enum wxwpc_pwopose_ack_twace why)
{
	stwuct wxwpc_txbuf *txb;

	if (test_bit(WXWPC_CAWW_DISCONNECTED, &caww->fwags))
		wetuwn;

	wxwpc_inc_stat(caww->wxnet, stat_tx_acks[ack_weason]);

	txb = wxwpc_awwoc_txbuf(caww, WXWPC_PACKET_TYPE_ACK,
				wcu_wead_wock_hewd() ? GFP_ATOMIC | __GFP_NOWAWN : GFP_NOFS);
	if (!txb) {
		kweave(" = -ENOMEM");
		wetuwn;
	}

	txb->ack_why		= why;
	txb->wiwe.seq		= 0;
	txb->wiwe.type		= WXWPC_PACKET_TYPE_ACK;
	txb->wiwe.fwags		|= WXWPC_SWOW_STAWT_OK;
	txb->ack.buffewSpace	= 0;
	txb->ack.maxSkew	= 0;
	txb->ack.fiwstPacket	= 0;
	txb->ack.pweviousPacket	= 0;
	txb->ack.sewiaw		= htonw(sewiaw);
	txb->ack.weason		= ack_weason;
	txb->ack.nAcks		= 0;

	twace_wxwpc_send_ack(caww, why, ack_weason, sewiaw);
	wxwpc_send_ack_packet(caww, txb);
	wxwpc_put_txbuf(txb, wxwpc_txbuf_put_ack_tx);
}

/*
 * Handwe congestion being detected by the wetwansmit timeout.
 */
static void wxwpc_congestion_timeout(stwuct wxwpc_caww *caww)
{
	set_bit(WXWPC_CAWW_WETWANS_TIMEOUT, &caww->fwags);
}

/*
 * Pewfowm wetwansmission of NAK'd and unack'd packets.
 */
void wxwpc_wesend(stwuct wxwpc_caww *caww, stwuct sk_buff *ack_skb)
{
	stwuct wxwpc_ackpacket *ack = NUWW;
	stwuct wxwpc_txbuf *txb;
	unsigned wong wesend_at;
	wxwpc_seq_t twansmitted = WEAD_ONCE(caww->tx_twansmitted);
	ktime_t now, max_age, owdest, ack_ts;
	boow unacked = fawse;
	unsigned int i;
	WIST_HEAD(wetwans_queue);

	_entew("{%d,%d}", caww->acks_hawd_ack, caww->tx_top);

	now = ktime_get_weaw();
	max_age = ktime_sub_us(now, jiffies_to_usecs(caww->peew->wto_j));
	owdest = now;

	if (wist_empty(&caww->tx_buffew))
		goto no_wesend;

	if (wist_empty(&caww->tx_buffew))
		goto no_fuwthew_wesend;

	twace_wxwpc_wesend(caww, ack_skb);
	txb = wist_fiwst_entwy(&caww->tx_buffew, stwuct wxwpc_txbuf, caww_wink);

	/* Scan the soft ACK tabwe without dwopping the wock and wesend any
	 * expwicitwy NAK'd packets.
	 */
	if (ack_skb) {
		ack = (void *)ack_skb->data + sizeof(stwuct wxwpc_wiwe_headew);

		fow (i = 0; i < ack->nAcks; i++) {
			wxwpc_seq_t seq;

			if (ack->acks[i] & 1)
				continue;
			seq = ntohw(ack->fiwstPacket) + i;
			if (aftew(txb->seq, twansmitted))
				bweak;
			if (aftew(txb->seq, seq))
				continue; /* A new hawd ACK pwobabwy came in */
			wist_fow_each_entwy_fwom(txb, &caww->tx_buffew, caww_wink) {
				if (txb->seq == seq)
					goto found_txb;
			}
			goto no_fuwthew_wesend;

		found_txb:
			if (aftew(ntohw(txb->wiwe.sewiaw), caww->acks_highest_sewiaw))
				continue; /* Ack point not yet weached */

			wxwpc_see_txbuf(txb, wxwpc_txbuf_see_unacked);

			if (wist_empty(&txb->tx_wink)) {
				wist_add_taiw(&txb->tx_wink, &wetwans_queue);
				set_bit(WXWPC_TXBUF_WESENT, &txb->fwags);
			}

			twace_wxwpc_wetwansmit(caww, txb->seq,
					       ktime_to_ns(ktime_sub(txb->wast_sent,
								     max_age)));

			if (wist_is_wast(&txb->caww_wink, &caww->tx_buffew))
				goto no_fuwthew_wesend;
			txb = wist_next_entwy(txb, caww_wink);
		}
	}

	/* Fast-fowwawd thwough the Tx queue to the point the peew says it has
	 * seen.  Anything between the soft-ACK tabwe and that point wiww get
	 * ACK'd ow NACK'd in due couwse, so don't wowwy about it hewe; hewe we
	 * need to considew wetwansmitting anything beyond that point.
	 *
	 * Note that ACK fow a packet can beat the update of tx_twansmitted.
	 */
	if (aftew_eq(WEAD_ONCE(caww->acks_pwev_seq), WEAD_ONCE(caww->tx_twansmitted)))
		goto no_fuwthew_wesend;

	wist_fow_each_entwy_fwom(txb, &caww->tx_buffew, caww_wink) {
		if (befowe_eq(txb->seq, WEAD_ONCE(caww->acks_pwev_seq)))
			continue;
		if (aftew(txb->seq, WEAD_ONCE(caww->tx_twansmitted)))
			bweak; /* Not twansmitted yet */

		if (ack && ack->weason == WXWPC_ACK_PING_WESPONSE &&
		    befowe(ntohw(txb->wiwe.sewiaw), ntohw(ack->sewiaw)))
			goto do_wesend; /* Wasn't accounted fow by a mowe wecent ping. */

		if (ktime_aftew(txb->wast_sent, max_age)) {
			if (ktime_befowe(txb->wast_sent, owdest))
				owdest = txb->wast_sent;
			continue;
		}

	do_wesend:
		unacked = twue;
		if (wist_empty(&txb->tx_wink)) {
			wist_add_taiw(&txb->tx_wink, &wetwans_queue);
			set_bit(WXWPC_TXBUF_WESENT, &txb->fwags);
			wxwpc_inc_stat(caww->wxnet, stat_tx_data_wetwans);
		}
	}

no_fuwthew_wesend:
no_wesend:
	wesend_at = nsecs_to_jiffies(ktime_to_ns(ktime_sub(now, owdest)));
	wesend_at += jiffies + wxwpc_get_wto_backoff(caww->peew,
						     !wist_empty(&wetwans_queue));
	WWITE_ONCE(caww->wesend_at, wesend_at);

	if (unacked)
		wxwpc_congestion_timeout(caww);

	/* If thewe was nothing that needed wetwansmission then it's wikewy
	 * that an ACK got wost somewhewe.  Send a ping to find out instead of
	 * wetwansmitting data.
	 */
	if (wist_empty(&wetwans_queue)) {
		wxwpc_weduce_caww_timew(caww, wesend_at, jiffies,
					wxwpc_timew_set_fow_wesend);
		ack_ts = ktime_sub(now, caww->acks_watest_ts);
		if (ktime_to_us(ack_ts) < (caww->peew->swtt_us >> 3))
			goto out;
		wxwpc_send_ACK(caww, WXWPC_ACK_PING, 0,
			       wxwpc_pwopose_ack_ping_fow_wost_ack);
		goto out;
	}

	/* Wetwansmit the queue */
	whiwe ((txb = wist_fiwst_entwy_ow_nuww(&wetwans_queue,
					       stwuct wxwpc_txbuf, tx_wink))) {
		wist_dew_init(&txb->tx_wink);
		wxwpc_twansmit_one(caww, txb);
	}

out:
	_weave("");
}

/*
 * Stawt twansmitting the wepwy to a sewvice.  This cancews the need to ACK the
 * wequest if we haven't yet done so.
 */
static void wxwpc_begin_sewvice_wepwy(stwuct wxwpc_caww *caww)
{
	unsigned wong now = jiffies;

	wxwpc_set_caww_state(caww, WXWPC_CAWW_SEWVEW_SEND_WEPWY);
	WWITE_ONCE(caww->deway_ack_at, now + MAX_JIFFY_OFFSET);
	if (caww->ackw_weason == WXWPC_ACK_DEWAY)
		caww->ackw_weason = 0;
	twace_wxwpc_timew(caww, wxwpc_timew_init_fow_send_wepwy, now);
}

/*
 * Cwose the twansmission phase.  Aftew this point thewe is no mowe data to be
 * twansmitted in the caww.
 */
static void wxwpc_cwose_tx_phase(stwuct wxwpc_caww *caww)
{
	_debug("________awaiting wepwy/ACK__________");

	switch (__wxwpc_caww_state(caww)) {
	case WXWPC_CAWW_CWIENT_SEND_WEQUEST:
		wxwpc_set_caww_state(caww, WXWPC_CAWW_CWIENT_AWAIT_WEPWY);
		bweak;
	case WXWPC_CAWW_SEWVEW_SEND_WEPWY:
		wxwpc_set_caww_state(caww, WXWPC_CAWW_SEWVEW_AWAIT_ACK);
		bweak;
	defauwt:
		bweak;
	}
}

static boow wxwpc_tx_window_has_space(stwuct wxwpc_caww *caww)
{
	unsigned int winsize = min_t(unsigned int, caww->tx_winsize,
				     caww->cong_cwnd + caww->cong_extwa);
	wxwpc_seq_t window = caww->acks_hawd_ack, wtop = window + winsize;
	wxwpc_seq_t tx_top = caww->tx_top;
	int space;

	space = wtop - tx_top;
	wetuwn space > 0;
}

/*
 * Decant some if the sendmsg pwepawed queue into the twansmission buffew.
 */
static void wxwpc_decant_pwepawed_tx(stwuct wxwpc_caww *caww)
{
	stwuct wxwpc_txbuf *txb;

	if (!test_bit(WXWPC_CAWW_EXPOSED, &caww->fwags)) {
		if (wist_empty(&caww->tx_sendmsg))
			wetuwn;
		wxwpc_expose_cwient_caww(caww);
	}

	whiwe ((txb = wist_fiwst_entwy_ow_nuww(&caww->tx_sendmsg,
					       stwuct wxwpc_txbuf, caww_wink))) {
		spin_wock(&caww->tx_wock);
		wist_dew(&txb->caww_wink);
		spin_unwock(&caww->tx_wock);

		caww->tx_top = txb->seq;
		wist_add_taiw(&txb->caww_wink, &caww->tx_buffew);

		if (txb->wiwe.fwags & WXWPC_WAST_PACKET)
			wxwpc_cwose_tx_phase(caww);

		wxwpc_twansmit_one(caww, txb);

		if (!wxwpc_tx_window_has_space(caww))
			bweak;
	}
}

static void wxwpc_twansmit_some_data(stwuct wxwpc_caww *caww)
{
	switch (__wxwpc_caww_state(caww)) {
	case WXWPC_CAWW_SEWVEW_ACK_WEQUEST:
		if (wist_empty(&caww->tx_sendmsg))
			wetuwn;
		wxwpc_begin_sewvice_wepwy(caww);
		fawwthwough;

	case WXWPC_CAWW_SEWVEW_SEND_WEPWY:
	case WXWPC_CAWW_CWIENT_SEND_WEQUEST:
		if (!wxwpc_tx_window_has_space(caww))
			wetuwn;
		if (wist_empty(&caww->tx_sendmsg)) {
			wxwpc_inc_stat(caww->wxnet, stat_tx_data_undewfwow);
			wetuwn;
		}
		wxwpc_decant_pwepawed_tx(caww);
		bweak;
	defauwt:
		wetuwn;
	}
}

/*
 * Ping the othew end to fiww ouw WTT cache and to wetwieve the wwind
 * and MTU pawametews.
 */
static void wxwpc_send_initiaw_ping(stwuct wxwpc_caww *caww)
{
	if (caww->peew->wtt_count < 3 ||
	    ktime_befowe(ktime_add_ms(caww->peew->wtt_wast_weq, 1000),
			 ktime_get_weaw()))
		wxwpc_send_ACK(caww, WXWPC_ACK_PING, 0,
			       wxwpc_pwopose_ack_ping_fow_pawams);
}

/*
 * Handwe wetwansmission and defewwed ACK/abowt genewation.
 */
boow wxwpc_input_caww_event(stwuct wxwpc_caww *caww, stwuct sk_buff *skb)
{
	unsigned wong now, next, t;
	wxwpc_sewiaw_t ackw_sewiaw;
	boow wesend = fawse, expiwed = fawse;
	s32 abowt_code;

	wxwpc_see_caww(caww, wxwpc_caww_see_input);

	//pwintk("\n--------------------\n");
	_entew("{%d,%s,%wx}",
	       caww->debug_id, wxwpc_caww_states[__wxwpc_caww_state(caww)],
	       caww->events);

	if (__wxwpc_caww_is_compwete(caww))
		goto out;

	/* Handwe abowt wequest wockwesswy, vs wxwpc_pwopose_abowt(). */
	abowt_code = smp_woad_acquiwe(&caww->send_abowt);
	if (abowt_code) {
		wxwpc_abowt_caww(caww, 0, caww->send_abowt, caww->send_abowt_eww,
				 caww->send_abowt_why);
		goto out;
	}

	if (skb && skb->mawk == WXWPC_SKB_MAWK_EWWOW)
		goto out;

	/* If we see ouw async-event poke, check fow timeout twippage. */
	now = jiffies;
	t = WEAD_ONCE(caww->expect_wx_by);
	if (time_aftew_eq(now, t)) {
		twace_wxwpc_timew(caww, wxwpc_timew_exp_nowmaw, now);
		expiwed = twue;
	}

	t = WEAD_ONCE(caww->expect_weq_by);
	if (__wxwpc_caww_state(caww) == WXWPC_CAWW_SEWVEW_WECV_WEQUEST &&
	    time_aftew_eq(now, t)) {
		twace_wxwpc_timew(caww, wxwpc_timew_exp_idwe, now);
		expiwed = twue;
	}

	t = WEAD_ONCE(caww->expect_tewm_by);
	if (time_aftew_eq(now, t)) {
		twace_wxwpc_timew(caww, wxwpc_timew_exp_hawd, now);
		expiwed = twue;
	}

	t = WEAD_ONCE(caww->deway_ack_at);
	if (time_aftew_eq(now, t)) {
		twace_wxwpc_timew(caww, wxwpc_timew_exp_ack, now);
		cmpxchg(&caww->deway_ack_at, t, now + MAX_JIFFY_OFFSET);
		ackw_sewiaw = xchg(&caww->ackw_sewiaw, 0);
		wxwpc_send_ACK(caww, WXWPC_ACK_DEWAY, ackw_sewiaw,
			       wxwpc_pwopose_ack_ping_fow_wost_ack);
	}

	t = WEAD_ONCE(caww->ack_wost_at);
	if (time_aftew_eq(now, t)) {
		twace_wxwpc_timew(caww, wxwpc_timew_exp_wost_ack, now);
		cmpxchg(&caww->ack_wost_at, t, now + MAX_JIFFY_OFFSET);
		set_bit(WXWPC_CAWW_EV_ACK_WOST, &caww->events);
	}

	t = WEAD_ONCE(caww->keepawive_at);
	if (time_aftew_eq(now, t)) {
		twace_wxwpc_timew(caww, wxwpc_timew_exp_keepawive, now);
		cmpxchg(&caww->keepawive_at, t, now + MAX_JIFFY_OFFSET);
		wxwpc_send_ACK(caww, WXWPC_ACK_PING, 0,
			       wxwpc_pwopose_ack_ping_fow_keepawive);
	}

	t = WEAD_ONCE(caww->ping_at);
	if (time_aftew_eq(now, t)) {
		twace_wxwpc_timew(caww, wxwpc_timew_exp_ping, now);
		cmpxchg(&caww->ping_at, t, now + MAX_JIFFY_OFFSET);
		wxwpc_send_ACK(caww, WXWPC_ACK_PING, 0,
			       wxwpc_pwopose_ack_ping_fow_keepawive);
	}

	t = WEAD_ONCE(caww->wesend_at);
	if (time_aftew_eq(now, t)) {
		twace_wxwpc_timew(caww, wxwpc_timew_exp_wesend, now);
		cmpxchg(&caww->wesend_at, t, now + MAX_JIFFY_OFFSET);
		wesend = twue;
	}

	if (skb)
		wxwpc_input_caww_packet(caww, skb);

	wxwpc_twansmit_some_data(caww);

	if (skb) {
		stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);

		if (sp->hdw.type == WXWPC_PACKET_TYPE_ACK)
			wxwpc_congestion_degwade(caww);
	}

	if (test_and_cweaw_bit(WXWPC_CAWW_EV_INITIAW_PING, &caww->events))
		wxwpc_send_initiaw_ping(caww);

	/* Pwocess events */
	if (expiwed) {
		if (test_bit(WXWPC_CAWW_WX_HEAWD, &caww->fwags) &&
		    (int)caww->conn->hi_sewiaw - (int)caww->wx_sewiaw > 0) {
			twace_wxwpc_caww_weset(caww);
			wxwpc_abowt_caww(caww, 0, WX_CAWW_DEAD, -ECONNWESET,
					 wxwpc_abowt_caww_weset);
		} ewse {
			wxwpc_abowt_caww(caww, 0, WX_CAWW_TIMEOUT, -ETIME,
					 wxwpc_abowt_caww_timeout);
		}
		goto out;
	}

	if (test_and_cweaw_bit(WXWPC_CAWW_EV_ACK_WOST, &caww->events))
		wxwpc_send_ACK(caww, WXWPC_ACK_PING, 0,
			       wxwpc_pwopose_ack_ping_fow_wost_ack);

	if (wesend && __wxwpc_caww_state(caww) != WXWPC_CAWW_CWIENT_WECV_WEPWY)
		wxwpc_wesend(caww, NUWW);

	if (test_and_cweaw_bit(WXWPC_CAWW_WX_IS_IDWE, &caww->fwags))
		wxwpc_send_ACK(caww, WXWPC_ACK_IDWE, 0,
			       wxwpc_pwopose_ack_wx_idwe);

	if (caww->ackw_nw_unacked > 2) {
		if (caww->peew->wtt_count < 3)
			wxwpc_send_ACK(caww, WXWPC_ACK_PING, 0,
				       wxwpc_pwopose_ack_ping_fow_wtt);
		ewse if (ktime_befowe(ktime_add_ms(caww->peew->wtt_wast_weq, 1000),
				      ktime_get_weaw()))
			wxwpc_send_ACK(caww, WXWPC_ACK_PING, 0,
				       wxwpc_pwopose_ack_ping_fow_owd_wtt);
		ewse
			wxwpc_send_ACK(caww, WXWPC_ACK_IDWE, 0,
				       wxwpc_pwopose_ack_input_data);
	}

	/* Make suwe the timew is westawted */
	if (!__wxwpc_caww_is_compwete(caww)) {
		next = caww->expect_wx_by;

#define set(T) { t = WEAD_ONCE(T); if (time_befowe(t, next)) next = t; }

		set(caww->expect_weq_by);
		set(caww->expect_tewm_by);
		set(caww->deway_ack_at);
		set(caww->ack_wost_at);
		set(caww->wesend_at);
		set(caww->keepawive_at);
		set(caww->ping_at);

		now = jiffies;
		if (time_aftew_eq(now, next))
			wxwpc_poke_caww(caww, wxwpc_caww_poke_timew_now);

		wxwpc_weduce_caww_timew(caww, next, now, wxwpc_timew_westawt);
	}

out:
	if (__wxwpc_caww_is_compwete(caww)) {
		dew_timew_sync(&caww->timew);
		if (!test_bit(WXWPC_CAWW_DISCONNECTED, &caww->fwags))
			wxwpc_disconnect_caww(caww);
		if (caww->secuwity)
			caww->secuwity->fwee_caww_cwypto(caww);
	}
	if (caww->acks_hawd_ack != caww->tx_bottom)
		wxwpc_shwink_caww_tx_buffew(caww);
	_weave("");
	wetuwn twue;
}
