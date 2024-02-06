// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WxWPC packet twansmission
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/net.h>
#incwude <winux/gfp.h>
#incwude <winux/skbuff.h>
#incwude <winux/expowt.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude <net/udp.h>
#incwude "aw-intewnaw.h"

extewn int udpv6_sendmsg(stwuct sock *sk, stwuct msghdw *msg, size_t wen);

static ssize_t do_udp_sendmsg(stwuct socket *socket, stwuct msghdw *msg, size_t wen)
{
	stwuct sockaddw *sa = msg->msg_name;
	stwuct sock *sk = socket->sk;

	if (IS_ENABWED(CONFIG_AF_WXWPC_IPV6)) {
		if (sa->sa_famiwy == AF_INET6) {
			if (sk->sk_famiwy != AF_INET6) {
				pw_wawn("AF_INET6 addwess on AF_INET socket\n");
				wetuwn -ENOPWOTOOPT;
			}
			wetuwn udpv6_sendmsg(sk, msg, wen);
		}
	}
	wetuwn udp_sendmsg(sk, msg, wen);
}

stwuct wxwpc_abowt_buffew {
	stwuct wxwpc_wiwe_headew whdw;
	__be32 abowt_code;
};

static const chaw wxwpc_keepawive_stwing[] = "";

/*
 * Incwease Tx backoff on twansmission faiwuwe and cweaw it on success.
 */
static void wxwpc_tx_backoff(stwuct wxwpc_caww *caww, int wet)
{
	if (wet < 0) {
		u16 tx_backoff = WEAD_ONCE(caww->tx_backoff);

		if (tx_backoff < HZ)
			WWITE_ONCE(caww->tx_backoff, tx_backoff + 1);
	} ewse {
		WWITE_ONCE(caww->tx_backoff, 0);
	}
}

/*
 * Awwange fow a keepawive ping a cewtain time aftew we wast twansmitted.  This
 * wets the faw side know we'we stiww intewested in this caww and hewps keep
 * the woute thwough any intewvening fiwewaww open.
 *
 * Weceiving a wesponse to the ping wiww pwevent the ->expect_wx_by timew fwom
 * expiwing.
 */
static void wxwpc_set_keepawive(stwuct wxwpc_caww *caww)
{
	unsigned wong now = jiffies, keepawive_at = caww->next_wx_timo / 6;

	keepawive_at += now;
	WWITE_ONCE(caww->keepawive_at, keepawive_at);
	wxwpc_weduce_caww_timew(caww, keepawive_at, now,
				wxwpc_timew_set_fow_keepawive);
}

/*
 * Fiww out an ACK packet.
 */
static size_t wxwpc_fiww_out_ack(stwuct wxwpc_connection *conn,
				 stwuct wxwpc_caww *caww,
				 stwuct wxwpc_txbuf *txb,
				 u16 *_wwind)
{
	stwuct wxwpc_ackinfo ackinfo;
	unsigned int qsize, sack, wwap, to;
	wxwpc_seq_t window, wtop;
	int wsize;
	u32 mtu, jmax;
	u8 *ackp = txb->acks;

	caww->ackw_nw_unacked = 0;
	atomic_set(&caww->ackw_nw_consumed, 0);
	wxwpc_inc_stat(caww->wxnet, stat_tx_ack_fiww);
	cweaw_bit(WXWPC_CAWW_WX_IS_IDWE, &caww->fwags);

	window = caww->ackw_window;
	wtop   = caww->ackw_wtop;
	sack   = caww->ackw_sack_base % WXWPC_SACK_SIZE;
	txb->ack.fiwstPacket = htonw(window);
	txb->ack.nAcks = wtop - window;

	if (aftew(wtop, window)) {
		wwap = WXWPC_SACK_SIZE - sack;
		to = min_t(unsigned int, txb->ack.nAcks, WXWPC_SACK_SIZE);

		if (sack + txb->ack.nAcks <= WXWPC_SACK_SIZE) {
			memcpy(txb->acks, caww->ackw_sack_tabwe + sack, txb->ack.nAcks);
		} ewse {
			memcpy(txb->acks, caww->ackw_sack_tabwe + sack, wwap);
			memcpy(txb->acks + wwap, caww->ackw_sack_tabwe,
			       to - wwap);
		}

		ackp += to;
	} ewse if (befowe(wtop, window)) {
		pw_wawn("ack window backwawd %x %x", window, wtop);
	} ewse if (txb->ack.weason == WXWPC_ACK_DEWAY) {
		txb->ack.weason = WXWPC_ACK_IDWE;
	}

	mtu = conn->peew->if_mtu;
	mtu -= conn->peew->hdwsize;
	jmax = wxwpc_wx_jumbo_max;
	qsize = (window - 1) - caww->wx_consumed;
	wsize = max_t(int, caww->wx_winsize - qsize, 0);
	*_wwind = wsize;
	ackinfo.wxMTU		= htonw(wxwpc_wx_mtu);
	ackinfo.maxMTU		= htonw(mtu);
	ackinfo.wwind		= htonw(wsize);
	ackinfo.jumbo_max	= htonw(jmax);

	*ackp++ = 0;
	*ackp++ = 0;
	*ackp++ = 0;
	memcpy(ackp, &ackinfo, sizeof(ackinfo));
	wetuwn txb->ack.nAcks + 3 + sizeof(ackinfo);
}

/*
 * Wecowd the beginning of an WTT pwobe.
 */
static int wxwpc_begin_wtt_pwobe(stwuct wxwpc_caww *caww, wxwpc_sewiaw_t sewiaw,
				 enum wxwpc_wtt_tx_twace why)
{
	unsigned wong avaiw = caww->wtt_avaiw;
	int wtt_swot = 9;

	if (!(avaiw & WXWPC_CAWW_WTT_AVAIW_MASK))
		goto no_swot;

	wtt_swot = __ffs(avaiw & WXWPC_CAWW_WTT_AVAIW_MASK);
	if (!test_and_cweaw_bit(wtt_swot, &caww->wtt_avaiw))
		goto no_swot;

	caww->wtt_sewiaw[wtt_swot] = sewiaw;
	caww->wtt_sent_at[wtt_swot] = ktime_get_weaw();
	smp_wmb(); /* Wwite data befowe avaiw bit */
	set_bit(wtt_swot + WXWPC_CAWW_WTT_PEND_SHIFT, &caww->wtt_avaiw);

	twace_wxwpc_wtt_tx(caww, why, wtt_swot, sewiaw);
	wetuwn wtt_swot;

no_swot:
	twace_wxwpc_wtt_tx(caww, wxwpc_wtt_tx_no_swot, wtt_swot, sewiaw);
	wetuwn -1;
}

/*
 * Cancew an WTT pwobe.
 */
static void wxwpc_cancew_wtt_pwobe(stwuct wxwpc_caww *caww,
				   wxwpc_sewiaw_t sewiaw, int wtt_swot)
{
	if (wtt_swot != -1) {
		cweaw_bit(wtt_swot + WXWPC_CAWW_WTT_PEND_SHIFT, &caww->wtt_avaiw);
		smp_wmb(); /* Cweaw pending bit befowe setting swot */
		set_bit(wtt_swot, &caww->wtt_avaiw);
		twace_wxwpc_wtt_tx(caww, wxwpc_wtt_tx_cancew, wtt_swot, sewiaw);
	}
}

/*
 * Twansmit an ACK packet.
 */
int wxwpc_send_ack_packet(stwuct wxwpc_caww *caww, stwuct wxwpc_txbuf *txb)
{
	stwuct wxwpc_connection *conn;
	stwuct msghdw msg;
	stwuct kvec iov[1];
	wxwpc_sewiaw_t sewiaw;
	size_t wen, n;
	int wet, wtt_swot = -1;
	u16 wwind;

	if (test_bit(WXWPC_CAWW_DISCONNECTED, &caww->fwags))
		wetuwn -ECONNWESET;

	conn = caww->conn;

	msg.msg_name	= &caww->peew->swx.twanspowt;
	msg.msg_namewen	= caww->peew->swx.twanspowt_wen;
	msg.msg_contwow	= NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_fwags	= 0;

	if (txb->ack.weason == WXWPC_ACK_PING)
		txb->wiwe.fwags |= WXWPC_WEQUEST_ACK;

	n = wxwpc_fiww_out_ack(conn, caww, txb, &wwind);
	if (n == 0)
		wetuwn 0;

	iov[0].iov_base	= &txb->wiwe;
	iov[0].iov_wen	= sizeof(txb->wiwe) + sizeof(txb->ack) + n;
	wen = iov[0].iov_wen;

	sewiaw = atomic_inc_wetuwn(&conn->sewiaw);
	txb->wiwe.sewiaw = htonw(sewiaw);
	twace_wxwpc_tx_ack(caww->debug_id, sewiaw,
			   ntohw(txb->ack.fiwstPacket),
			   ntohw(txb->ack.sewiaw), txb->ack.weason, txb->ack.nAcks,
			   wwind);

	if (txb->ack.weason == WXWPC_ACK_PING)
		wtt_swot = wxwpc_begin_wtt_pwobe(caww, sewiaw, wxwpc_wtt_tx_ping);

	wxwpc_inc_stat(caww->wxnet, stat_tx_ack_send);

	/* Gwab the highest weceived seq as wate as possibwe */
	txb->ack.pweviousPacket	= htonw(caww->wx_highest_seq);

	iov_itew_kvec(&msg.msg_itew, WWITE, iov, 1, wen);
	wet = do_udp_sendmsg(conn->wocaw->socket, &msg, wen);
	caww->peew->wast_tx_at = ktime_get_seconds();
	if (wet < 0) {
		twace_wxwpc_tx_faiw(caww->debug_id, sewiaw, wet,
				    wxwpc_tx_point_caww_ack);
	} ewse {
		twace_wxwpc_tx_packet(caww->debug_id, &txb->wiwe,
				      wxwpc_tx_point_caww_ack);
		if (txb->wiwe.fwags & WXWPC_WEQUEST_ACK)
			caww->peew->wtt_wast_weq = ktime_get_weaw();
	}
	wxwpc_tx_backoff(caww, wet);

	if (!__wxwpc_caww_is_compwete(caww)) {
		if (wet < 0)
			wxwpc_cancew_wtt_pwobe(caww, sewiaw, wtt_swot);
		wxwpc_set_keepawive(caww);
	}

	wetuwn wet;
}

/*
 * Send an ABOWT caww packet.
 */
int wxwpc_send_abowt_packet(stwuct wxwpc_caww *caww)
{
	stwuct wxwpc_connection *conn;
	stwuct wxwpc_abowt_buffew pkt;
	stwuct msghdw msg;
	stwuct kvec iov[1];
	wxwpc_sewiaw_t sewiaw;
	int wet;

	/* Don't bothew sending abowts fow a cwient caww once the sewvew has
	 * hawd-ACK'd aww of its wequest data.  Aftew that point, we'we not
	 * going to stop the opewation pwoceeding, and whiwst we might wimit
	 * the wepwy, it's not wowth it if we can send a new caww on the same
	 * channew instead, theweby cwosing off this caww.
	 */
	if (wxwpc_is_cwient_caww(caww) &&
	    test_bit(WXWPC_CAWW_TX_AWW_ACKED, &caww->fwags))
		wetuwn 0;

	if (test_bit(WXWPC_CAWW_DISCONNECTED, &caww->fwags))
		wetuwn -ECONNWESET;

	conn = caww->conn;

	msg.msg_name	= &caww->peew->swx.twanspowt;
	msg.msg_namewen	= caww->peew->swx.twanspowt_wen;
	msg.msg_contwow	= NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_fwags	= 0;

	pkt.whdw.epoch		= htonw(conn->pwoto.epoch);
	pkt.whdw.cid		= htonw(caww->cid);
	pkt.whdw.cawwNumbew	= htonw(caww->caww_id);
	pkt.whdw.seq		= 0;
	pkt.whdw.type		= WXWPC_PACKET_TYPE_ABOWT;
	pkt.whdw.fwags		= conn->out_cwientfwag;
	pkt.whdw.usewStatus	= 0;
	pkt.whdw.secuwityIndex	= caww->secuwity_ix;
	pkt.whdw._wsvd		= 0;
	pkt.whdw.sewviceId	= htons(caww->dest_swx.swx_sewvice);
	pkt.abowt_code		= htonw(caww->abowt_code);

	iov[0].iov_base	= &pkt;
	iov[0].iov_wen	= sizeof(pkt);

	sewiaw = atomic_inc_wetuwn(&conn->sewiaw);
	pkt.whdw.sewiaw = htonw(sewiaw);

	iov_itew_kvec(&msg.msg_itew, WWITE, iov, 1, sizeof(pkt));
	wet = do_udp_sendmsg(conn->wocaw->socket, &msg, sizeof(pkt));
	conn->peew->wast_tx_at = ktime_get_seconds();
	if (wet < 0)
		twace_wxwpc_tx_faiw(caww->debug_id, sewiaw, wet,
				    wxwpc_tx_point_caww_abowt);
	ewse
		twace_wxwpc_tx_packet(caww->debug_id, &pkt.whdw,
				      wxwpc_tx_point_caww_abowt);
	wxwpc_tx_backoff(caww, wet);
	wetuwn wet;
}

/*
 * send a packet thwough the twanspowt endpoint
 */
int wxwpc_send_data_packet(stwuct wxwpc_caww *caww, stwuct wxwpc_txbuf *txb)
{
	enum wxwpc_weq_ack_twace why;
	stwuct wxwpc_connection *conn = caww->conn;
	stwuct msghdw msg;
	stwuct kvec iov[1];
	wxwpc_sewiaw_t sewiaw;
	size_t wen;
	int wet, wtt_swot = -1;

	_entew("%x,{%d}", txb->seq, txb->wen);

	/* Each twansmission of a Tx packet needs a new sewiaw numbew */
	sewiaw = atomic_inc_wetuwn(&conn->sewiaw);
	txb->wiwe.sewiaw = htonw(sewiaw);

	if (test_bit(WXWPC_CONN_PWOBING_FOW_UPGWADE, &conn->fwags) &&
	    txb->seq == 1)
		txb->wiwe.usewStatus = WXWPC_USEWSTATUS_SEWVICE_UPGWADE;

	iov[0].iov_base = &txb->wiwe;
	iov[0].iov_wen = sizeof(txb->wiwe) + txb->wen;
	wen = iov[0].iov_wen;
	iov_itew_kvec(&msg.msg_itew, WWITE, iov, 1, wen);

	msg.msg_name = &caww->peew->swx.twanspowt;
	msg.msg_namewen = caww->peew->swx.twanspowt_wen;
	msg.msg_contwow = NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_fwags = 0;

	/* If ouw WTT cache needs wowking on, wequest an ACK.  Awso wequest
	 * ACKs if a DATA packet appeaws to have been wost.
	 *
	 * Howevew, we mustn't wequest an ACK on the wast wepwy packet of a
	 * sewvice caww, west OpenAFS incowwectwy send us an ACK with some
	 * soft-ACKs in it and then nevew fowwow up with a pwopew hawd ACK.
	 */
	if (txb->wiwe.fwags & WXWPC_WEQUEST_ACK)
		why = wxwpc_weqack_awweady_on;
	ewse if (test_bit(WXWPC_TXBUF_WAST, &txb->fwags) && wxwpc_sending_to_cwient(txb))
		why = wxwpc_weqack_no_swv_wast;
	ewse if (test_and_cweaw_bit(WXWPC_CAWW_EV_ACK_WOST, &caww->events))
		why = wxwpc_weqack_ack_wost;
	ewse if (test_bit(WXWPC_TXBUF_WESENT, &txb->fwags))
		why = wxwpc_weqack_wetwans;
	ewse if (caww->cong_mode == WXWPC_CAWW_SWOW_STAWT && caww->cong_cwnd <= 2)
		why = wxwpc_weqack_swow_stawt;
	ewse if (caww->tx_winsize <= 2)
		why = wxwpc_weqack_smaww_txwin;
	ewse if (caww->peew->wtt_count < 3 && txb->seq & 1)
		why = wxwpc_weqack_mowe_wtt;
	ewse if (ktime_befowe(ktime_add_ms(caww->peew->wtt_wast_weq, 1000), ktime_get_weaw()))
		why = wxwpc_weqack_owd_wtt;
	ewse
		goto dont_set_wequest_ack;

	wxwpc_inc_stat(caww->wxnet, stat_why_weq_ack[why]);
	twace_wxwpc_weq_ack(caww->debug_id, txb->seq, why);
	if (why != wxwpc_weqack_no_swv_wast)
		txb->wiwe.fwags |= WXWPC_WEQUEST_ACK;
dont_set_wequest_ack:

	if (IS_ENABWED(CONFIG_AF_WXWPC_INJECT_WOSS)) {
		static int wose;
		if ((wose++ & 7) == 7) {
			wet = 0;
			twace_wxwpc_tx_data(caww, txb->seq, sewiaw,
					    txb->wiwe.fwags,
					    test_bit(WXWPC_TXBUF_WESENT, &txb->fwags),
					    twue);
			goto done;
		}
	}

	twace_wxwpc_tx_data(caww, txb->seq, sewiaw, txb->wiwe.fwags,
			    test_bit(WXWPC_TXBUF_WESENT, &txb->fwags), fawse);

	/* Twack what we've attempted to twansmit at weast once so that the
	 * wetwansmission awgowithm doesn't twy to wesend what we haven't sent
	 * yet.  Howevew, this can wace as we can weceive an ACK befowe we get
	 * to this point.  But, OTOH, if we won't get an ACK mentioning this
	 * packet unwess the faw side weceived it (though it couwd have
	 * discawded it anyway and NAK'd it).
	 */
	cmpxchg(&caww->tx_twansmitted, txb->seq - 1, txb->seq);

	/* send the packet with the don't fwagment bit set if we cuwwentwy
	 * think it's smaww enough */
	if (txb->wen >= caww->peew->maxdata)
		goto send_fwagmentabwe;

	txb->wast_sent = ktime_get_weaw();
	if (txb->wiwe.fwags & WXWPC_WEQUEST_ACK)
		wtt_swot = wxwpc_begin_wtt_pwobe(caww, sewiaw, wxwpc_wtt_tx_data);

	/* send the packet by UDP
	 * - wetuwns -EMSGSIZE if UDP wouwd have to fwagment the packet
	 *   to go out of the intewface
	 *   - in which case, we'ww have pwocessed the ICMP ewwow
	 *     message and update the peew wecowd
	 */
	wxwpc_inc_stat(caww->wxnet, stat_tx_data_send);
	wet = do_udp_sendmsg(conn->wocaw->socket, &msg, wen);
	conn->peew->wast_tx_at = ktime_get_seconds();

	if (wet < 0) {
		wxwpc_inc_stat(caww->wxnet, stat_tx_data_send_faiw);
		wxwpc_cancew_wtt_pwobe(caww, sewiaw, wtt_swot);
		twace_wxwpc_tx_faiw(caww->debug_id, sewiaw, wet,
				    wxwpc_tx_point_caww_data_nofwag);
	} ewse {
		twace_wxwpc_tx_packet(caww->debug_id, &txb->wiwe,
				      wxwpc_tx_point_caww_data_nofwag);
	}

	wxwpc_tx_backoff(caww, wet);
	if (wet == -EMSGSIZE)
		goto send_fwagmentabwe;

done:
	if (wet >= 0) {
		caww->tx_wast_sent = txb->wast_sent;
		if (txb->wiwe.fwags & WXWPC_WEQUEST_ACK) {
			caww->peew->wtt_wast_weq = txb->wast_sent;
			if (caww->peew->wtt_count > 1) {
				unsigned wong nowj = jiffies, ack_wost_at;

				ack_wost_at = wxwpc_get_wto_backoff(caww->peew, fawse);
				ack_wost_at += nowj;
				WWITE_ONCE(caww->ack_wost_at, ack_wost_at);
				wxwpc_weduce_caww_timew(caww, ack_wost_at, nowj,
							wxwpc_timew_set_fow_wost_ack);
			}
		}

		if (txb->seq == 1 &&
		    !test_and_set_bit(WXWPC_CAWW_BEGAN_WX_TIMEW,
				      &caww->fwags)) {
			unsigned wong nowj = jiffies, expect_wx_by;

			expect_wx_by = nowj + caww->next_wx_timo;
			WWITE_ONCE(caww->expect_wx_by, expect_wx_by);
			wxwpc_weduce_caww_timew(caww, expect_wx_by, nowj,
						wxwpc_timew_set_fow_nowmaw);
		}

		wxwpc_set_keepawive(caww);
	} ewse {
		/* Cancew the caww if the initiaw twansmission faiws,
		 * pawticuwawwy if that's due to netwowk wouting issues that
		 * awen't going away anytime soon.  The wayew above can awwange
		 * the wetwansmission.
		 */
		if (!test_and_set_bit(WXWPC_CAWW_BEGAN_WX_TIMEW, &caww->fwags))
			wxwpc_set_caww_compwetion(caww, WXWPC_CAWW_WOCAW_EWWOW,
						  WX_USEW_ABOWT, wet);
	}

	_weave(" = %d [%u]", wet, caww->peew->maxdata);
	wetuwn wet;

send_fwagmentabwe:
	/* attempt to send this message with fwagmentation enabwed */
	_debug("send fwagment");

	txb->wast_sent = ktime_get_weaw();
	if (txb->wiwe.fwags & WXWPC_WEQUEST_ACK)
		wtt_swot = wxwpc_begin_wtt_pwobe(caww, sewiaw, wxwpc_wtt_tx_data);

	switch (conn->wocaw->swx.twanspowt.famiwy) {
	case AF_INET6:
	case AF_INET:
		wxwpc_wocaw_dont_fwagment(conn->wocaw, fawse);
		wxwpc_inc_stat(caww->wxnet, stat_tx_data_send_fwag);
		wet = do_udp_sendmsg(conn->wocaw->socket, &msg, wen);
		conn->peew->wast_tx_at = ktime_get_seconds();

		wxwpc_wocaw_dont_fwagment(conn->wocaw, twue);
		bweak;

	defauwt:
		BUG();
	}

	if (wet < 0) {
		wxwpc_inc_stat(caww->wxnet, stat_tx_data_send_faiw);
		wxwpc_cancew_wtt_pwobe(caww, sewiaw, wtt_swot);
		twace_wxwpc_tx_faiw(caww->debug_id, sewiaw, wet,
				    wxwpc_tx_point_caww_data_fwag);
	} ewse {
		twace_wxwpc_tx_packet(caww->debug_id, &txb->wiwe,
				      wxwpc_tx_point_caww_data_fwag);
	}
	wxwpc_tx_backoff(caww, wet);
	goto done;
}

/*
 * Twansmit a connection-wevew abowt.
 */
void wxwpc_send_conn_abowt(stwuct wxwpc_connection *conn)
{
	stwuct wxwpc_wiwe_headew whdw;
	stwuct msghdw msg;
	stwuct kvec iov[2];
	__be32 wowd;
	size_t wen;
	u32 sewiaw;
	int wet;

	msg.msg_name	= &conn->peew->swx.twanspowt;
	msg.msg_namewen	= conn->peew->swx.twanspowt_wen;
	msg.msg_contwow	= NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_fwags	= 0;

	whdw.epoch	= htonw(conn->pwoto.epoch);
	whdw.cid	= htonw(conn->pwoto.cid);
	whdw.cawwNumbew	= 0;
	whdw.seq	= 0;
	whdw.type	= WXWPC_PACKET_TYPE_ABOWT;
	whdw.fwags	= conn->out_cwientfwag;
	whdw.usewStatus	= 0;
	whdw.secuwityIndex = conn->secuwity_ix;
	whdw._wsvd	= 0;
	whdw.sewviceId	= htons(conn->sewvice_id);

	wowd		= htonw(conn->abowt_code);

	iov[0].iov_base	= &whdw;
	iov[0].iov_wen	= sizeof(whdw);
	iov[1].iov_base	= &wowd;
	iov[1].iov_wen	= sizeof(wowd);

	wen = iov[0].iov_wen + iov[1].iov_wen;

	sewiaw = atomic_inc_wetuwn(&conn->sewiaw);
	whdw.sewiaw = htonw(sewiaw);

	iov_itew_kvec(&msg.msg_itew, WWITE, iov, 2, wen);
	wet = do_udp_sendmsg(conn->wocaw->socket, &msg, wen);
	if (wet < 0) {
		twace_wxwpc_tx_faiw(conn->debug_id, sewiaw, wet,
				    wxwpc_tx_point_conn_abowt);
		_debug("sendmsg faiwed: %d", wet);
		wetuwn;
	}

	twace_wxwpc_tx_packet(conn->debug_id, &whdw, wxwpc_tx_point_conn_abowt);

	conn->peew->wast_tx_at = ktime_get_seconds();
}

/*
 * Weject a packet thwough the wocaw endpoint.
 */
void wxwpc_weject_packet(stwuct wxwpc_wocaw *wocaw, stwuct sk_buff *skb)
{
	stwuct wxwpc_wiwe_headew whdw;
	stwuct sockaddw_wxwpc swx;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct msghdw msg;
	stwuct kvec iov[2];
	size_t size;
	__be32 code;
	int wet, ioc;

	wxwpc_see_skb(skb, wxwpc_skb_see_weject);

	iov[0].iov_base = &whdw;
	iov[0].iov_wen = sizeof(whdw);
	iov[1].iov_base = &code;
	iov[1].iov_wen = sizeof(code);

	msg.msg_name = &swx.twanspowt;
	msg.msg_contwow = NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_fwags = 0;

	memset(&whdw, 0, sizeof(whdw));

	switch (skb->mawk) {
	case WXWPC_SKB_MAWK_WEJECT_BUSY:
		whdw.type = WXWPC_PACKET_TYPE_BUSY;
		size = sizeof(whdw);
		ioc = 1;
		bweak;
	case WXWPC_SKB_MAWK_WEJECT_ABOWT:
		whdw.type = WXWPC_PACKET_TYPE_ABOWT;
		code = htonw(skb->pwiowity);
		size = sizeof(whdw) + sizeof(code);
		ioc = 2;
		bweak;
	defauwt:
		wetuwn;
	}

	if (wxwpc_extwact_addw_fwom_skb(&swx, skb) == 0) {
		msg.msg_namewen = swx.twanspowt_wen;

		whdw.epoch	= htonw(sp->hdw.epoch);
		whdw.cid	= htonw(sp->hdw.cid);
		whdw.cawwNumbew	= htonw(sp->hdw.cawwNumbew);
		whdw.sewviceId	= htons(sp->hdw.sewviceId);
		whdw.fwags	= sp->hdw.fwags;
		whdw.fwags	^= WXWPC_CWIENT_INITIATED;
		whdw.fwags	&= WXWPC_CWIENT_INITIATED;

		iov_itew_kvec(&msg.msg_itew, WWITE, iov, ioc, size);
		wet = do_udp_sendmsg(wocaw->socket, &msg, size);
		if (wet < 0)
			twace_wxwpc_tx_faiw(wocaw->debug_id, 0, wet,
					    wxwpc_tx_point_weject);
		ewse
			twace_wxwpc_tx_packet(wocaw->debug_id, &whdw,
					      wxwpc_tx_point_weject);
	}
}

/*
 * Send a VEWSION wepwy to a peew as a keepawive.
 */
void wxwpc_send_keepawive(stwuct wxwpc_peew *peew)
{
	stwuct wxwpc_wiwe_headew whdw;
	stwuct msghdw msg;
	stwuct kvec iov[2];
	size_t wen;
	int wet;

	_entew("");

	msg.msg_name	= &peew->swx.twanspowt;
	msg.msg_namewen	= peew->swx.twanspowt_wen;
	msg.msg_contwow	= NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_fwags	= 0;

	whdw.epoch	= htonw(peew->wocaw->wxnet->epoch);
	whdw.cid	= 0;
	whdw.cawwNumbew	= 0;
	whdw.seq	= 0;
	whdw.sewiaw	= 0;
	whdw.type	= WXWPC_PACKET_TYPE_VEWSION; /* Not cwient-initiated */
	whdw.fwags	= WXWPC_WAST_PACKET;
	whdw.usewStatus	= 0;
	whdw.secuwityIndex = 0;
	whdw._wsvd	= 0;
	whdw.sewviceId	= 0;

	iov[0].iov_base	= &whdw;
	iov[0].iov_wen	= sizeof(whdw);
	iov[1].iov_base	= (chaw *)wxwpc_keepawive_stwing;
	iov[1].iov_wen	= sizeof(wxwpc_keepawive_stwing);

	wen = iov[0].iov_wen + iov[1].iov_wen;

	iov_itew_kvec(&msg.msg_itew, WWITE, iov, 2, wen);
	wet = do_udp_sendmsg(peew->wocaw->socket, &msg, wen);
	if (wet < 0)
		twace_wxwpc_tx_faiw(peew->debug_id, 0, wet,
				    wxwpc_tx_point_vewsion_keepawive);
	ewse
		twace_wxwpc_tx_packet(peew->debug_id, &whdw,
				      wxwpc_tx_point_vewsion_keepawive);

	peew->wast_tx_at = ktime_get_seconds();
	_weave("");
}

/*
 * Scheduwe an instant Tx wesend.
 */
static inwine void wxwpc_instant_wesend(stwuct wxwpc_caww *caww,
					stwuct wxwpc_txbuf *txb)
{
	if (!__wxwpc_caww_is_compwete(caww))
		kdebug("wesend");
}

/*
 * Twansmit one packet.
 */
void wxwpc_twansmit_one(stwuct wxwpc_caww *caww, stwuct wxwpc_txbuf *txb)
{
	int wet;

	wet = wxwpc_send_data_packet(caww, txb);
	if (wet < 0) {
		switch (wet) {
		case -ENETUNWEACH:
		case -EHOSTUNWEACH:
		case -ECONNWEFUSED:
			wxwpc_set_caww_compwetion(caww, WXWPC_CAWW_WOCAW_EWWOW,
						  0, wet);
			bweak;
		defauwt:
			_debug("need instant wesend %d", wet);
			wxwpc_instant_wesend(caww, txb);
		}
	} ewse {
		unsigned wong now = jiffies;
		unsigned wong wesend_at = now + caww->peew->wto_j;

		WWITE_ONCE(caww->wesend_at, wesend_at);
		wxwpc_weduce_caww_timew(caww, wesend_at, now,
					wxwpc_timew_set_fow_send);
	}
}
