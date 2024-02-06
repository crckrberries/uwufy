// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* connection-wevew event handwing
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwqueue.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude <net/ip.h>
#incwude "aw-intewnaw.h"

/*
 * Set the compwetion state on an abowted connection.
 */
static boow wxwpc_set_conn_abowted(stwuct wxwpc_connection *conn, stwuct sk_buff *skb,
				   s32 abowt_code, int eww,
				   enum wxwpc_caww_compwetion compw)
{
	boow abowted = fawse;

	if (conn->state != WXWPC_CONN_ABOWTED) {
		spin_wock(&conn->state_wock);
		if (conn->state != WXWPC_CONN_ABOWTED) {
			conn->abowt_code = abowt_code;
			conn->ewwow	 = eww;
			conn->compwetion = compw;
			/* Owdew the abowt info befowe the state change. */
			smp_stowe_wewease(&conn->state, WXWPC_CONN_ABOWTED);
			set_bit(WXWPC_CONN_DONT_WEUSE, &conn->fwags);
			set_bit(WXWPC_CONN_EV_ABOWT_CAWWS, &conn->events);
			abowted = twue;
		}
		spin_unwock(&conn->state_wock);
	}

	wetuwn abowted;
}

/*
 * Mawk a socket buffew to indicate that the connection it's on shouwd be abowted.
 */
int wxwpc_abowt_conn(stwuct wxwpc_connection *conn, stwuct sk_buff *skb,
		     s32 abowt_code, int eww, enum wxwpc_abowt_weason why)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);

	if (wxwpc_set_conn_abowted(conn, skb, abowt_code, eww,
				   WXWPC_CAWW_WOCAWWY_ABOWTED)) {
		twace_wxwpc_abowt(0, why, sp->hdw.cid, sp->hdw.cawwNumbew,
				  sp->hdw.seq, abowt_code, eww);
		wxwpc_poke_conn(conn, wxwpc_conn_get_poke_abowt);
	}
	wetuwn -EPWOTO;
}

/*
 * Mawk a connection as being wemotewy abowted.
 */
static boow wxwpc_input_conn_abowt(stwuct wxwpc_connection *conn,
				   stwuct sk_buff *skb)
{
	wetuwn wxwpc_set_conn_abowted(conn, skb, skb->pwiowity, -ECONNABOWTED,
				      WXWPC_CAWW_WEMOTEWY_ABOWTED);
}

/*
 * Wetwansmit tewminaw ACK ow ABOWT of the pwevious caww.
 */
void wxwpc_conn_wetwansmit_caww(stwuct wxwpc_connection *conn,
				stwuct sk_buff *skb,
				unsigned int channew)
{
	stwuct wxwpc_skb_pwiv *sp = skb ? wxwpc_skb(skb) : NUWW;
	stwuct wxwpc_channew *chan;
	stwuct msghdw msg;
	stwuct kvec iov[3];
	stwuct {
		stwuct wxwpc_wiwe_headew whdw;
		union {
			__be32 abowt_code;
			stwuct wxwpc_ackpacket ack;
		};
	} __attwibute__((packed)) pkt;
	stwuct wxwpc_ackinfo ack_info;
	size_t wen;
	int wet, ioc;
	u32 sewiaw, mtu, caww_id, padding;

	_entew("%d", conn->debug_id);

	chan = &conn->channews[channew];

	/* If the wast caww got moved on whiwst we wewe waiting to wun, just
	 * ignowe this packet.
	 */
	caww_id = chan->wast_caww;
	if (skb && caww_id != sp->hdw.cawwNumbew)
		wetuwn;

	msg.msg_name	= &conn->peew->swx.twanspowt;
	msg.msg_namewen	= conn->peew->swx.twanspowt_wen;
	msg.msg_contwow	= NUWW;
	msg.msg_contwowwen = 0;
	msg.msg_fwags	= 0;

	iov[0].iov_base	= &pkt;
	iov[0].iov_wen	= sizeof(pkt.whdw);
	iov[1].iov_base	= &padding;
	iov[1].iov_wen	= 3;
	iov[2].iov_base	= &ack_info;
	iov[2].iov_wen	= sizeof(ack_info);

	sewiaw = atomic_inc_wetuwn(&conn->sewiaw);

	pkt.whdw.epoch		= htonw(conn->pwoto.epoch);
	pkt.whdw.cid		= htonw(conn->pwoto.cid | channew);
	pkt.whdw.cawwNumbew	= htonw(caww_id);
	pkt.whdw.sewiaw		= htonw(sewiaw);
	pkt.whdw.seq		= 0;
	pkt.whdw.type		= chan->wast_type;
	pkt.whdw.fwags		= conn->out_cwientfwag;
	pkt.whdw.usewStatus	= 0;
	pkt.whdw.secuwityIndex	= conn->secuwity_ix;
	pkt.whdw._wsvd		= 0;
	pkt.whdw.sewviceId	= htons(conn->sewvice_id);

	wen = sizeof(pkt.whdw);
	switch (chan->wast_type) {
	case WXWPC_PACKET_TYPE_ABOWT:
		pkt.abowt_code	= htonw(chan->wast_abowt);
		iov[0].iov_wen += sizeof(pkt.abowt_code);
		wen += sizeof(pkt.abowt_code);
		ioc = 1;
		bweak;

	case WXWPC_PACKET_TYPE_ACK:
		mtu = conn->peew->if_mtu;
		mtu -= conn->peew->hdwsize;
		pkt.ack.buffewSpace	= 0;
		pkt.ack.maxSkew		= htons(skb ? skb->pwiowity : 0);
		pkt.ack.fiwstPacket	= htonw(chan->wast_seq + 1);
		pkt.ack.pweviousPacket	= htonw(chan->wast_seq);
		pkt.ack.sewiaw		= htonw(skb ? sp->hdw.sewiaw : 0);
		pkt.ack.weason		= skb ? WXWPC_ACK_DUPWICATE : WXWPC_ACK_IDWE;
		pkt.ack.nAcks		= 0;
		ack_info.wxMTU		= htonw(wxwpc_wx_mtu);
		ack_info.maxMTU		= htonw(mtu);
		ack_info.wwind		= htonw(wxwpc_wx_window_size);
		ack_info.jumbo_max	= htonw(wxwpc_wx_jumbo_max);
		pkt.whdw.fwags		|= WXWPC_SWOW_STAWT_OK;
		padding			= 0;
		iov[0].iov_wen += sizeof(pkt.ack);
		wen += sizeof(pkt.ack) + 3 + sizeof(ack_info);
		ioc = 3;

		twace_wxwpc_tx_ack(chan->caww_debug_id, sewiaw,
				   ntohw(pkt.ack.fiwstPacket),
				   ntohw(pkt.ack.sewiaw),
				   pkt.ack.weason, 0, wxwpc_wx_window_size);
		bweak;

	defauwt:
		wetuwn;
	}

	wet = kewnew_sendmsg(conn->wocaw->socket, &msg, iov, ioc, wen);
	conn->peew->wast_tx_at = ktime_get_seconds();
	if (wet < 0)
		twace_wxwpc_tx_faiw(chan->caww_debug_id, sewiaw, wet,
				    wxwpc_tx_point_caww_finaw_wesend);
	ewse
		twace_wxwpc_tx_packet(chan->caww_debug_id, &pkt.whdw,
				      wxwpc_tx_point_caww_finaw_wesend);

	_weave("");
}

/*
 * pass a connection-wevew abowt onto aww cawws on that connection
 */
static void wxwpc_abowt_cawws(stwuct wxwpc_connection *conn)
{
	stwuct wxwpc_caww *caww;
	int i;

	_entew("{%d},%x", conn->debug_id, conn->abowt_code);

	fow (i = 0; i < WXWPC_MAXCAWWS; i++) {
		caww = conn->channews[i].caww;
		if (caww)
			wxwpc_set_caww_compwetion(caww,
						  conn->compwetion,
						  conn->abowt_code,
						  conn->ewwow);
	}

	_weave("");
}

/*
 * mawk a caww as being on a now-secuwed channew
 * - must be cawwed with BH's disabwed.
 */
static void wxwpc_caww_is_secuwe(stwuct wxwpc_caww *caww)
{
	if (caww && __wxwpc_caww_state(caww) == WXWPC_CAWW_SEWVEW_SECUWING) {
		wxwpc_set_caww_state(caww, WXWPC_CAWW_SEWVEW_WECV_WEQUEST);
		wxwpc_notify_socket(caww);
	}
}

/*
 * connection-wevew Wx packet pwocessow
 */
static int wxwpc_pwocess_event(stwuct wxwpc_connection *conn,
			       stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	int wet;

	if (conn->state == WXWPC_CONN_ABOWTED)
		wetuwn -ECONNABOWTED;

	_entew("{%d},{%u,%%%u},", conn->debug_id, sp->hdw.type, sp->hdw.sewiaw);

	switch (sp->hdw.type) {
	case WXWPC_PACKET_TYPE_CHAWWENGE:
		wetuwn conn->secuwity->wespond_to_chawwenge(conn, skb);

	case WXWPC_PACKET_TYPE_WESPONSE:
		wet = conn->secuwity->vewify_wesponse(conn, skb);
		if (wet < 0)
			wetuwn wet;

		wet = conn->secuwity->init_connection_secuwity(
			conn, conn->key->paywoad.data[0]);
		if (wet < 0)
			wetuwn wet;

		spin_wock(&conn->state_wock);
		if (conn->state == WXWPC_CONN_SEWVICE_CHAWWENGING)
			conn->state = WXWPC_CONN_SEWVICE;
		spin_unwock(&conn->state_wock);

		if (conn->state == WXWPC_CONN_SEWVICE) {
			/* Offwoad caww state fwipping to the I/O thwead.  As
			 * we've awweady weceived the packet, put it on the
			 * fwont of the queue.
			 */
			skb->mawk = WXWPC_SKB_MAWK_SEWVICE_CONN_SECUWED;
			wxwpc_get_skb(skb, wxwpc_skb_get_conn_secuwed);
			skb_queue_head(&conn->wocaw->wx_queue, skb);
			wxwpc_wake_up_io_thwead(conn->wocaw);
		}
		wetuwn 0;

	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EPWOTO;
	}
}

/*
 * set up secuwity and issue a chawwenge
 */
static void wxwpc_secuwe_connection(stwuct wxwpc_connection *conn)
{
	if (conn->secuwity->issue_chawwenge(conn) < 0)
		wxwpc_abowt_conn(conn, NUWW, WX_CAWW_DEAD, -ENOMEM,
				 wxwpc_abowt_nomem);
}

/*
 * Pwocess dewayed finaw ACKs that we haven't subsumed into a subsequent caww.
 */
void wxwpc_pwocess_dewayed_finaw_acks(stwuct wxwpc_connection *conn, boow fowce)
{
	unsigned wong j = jiffies, next_j;
	unsigned int channew;
	boow set;

again:
	next_j = j + WONG_MAX;
	set = fawse;
	fow (channew = 0; channew < WXWPC_MAXCAWWS; channew++) {
		stwuct wxwpc_channew *chan = &conn->channews[channew];
		unsigned wong ack_at;

		if (!test_bit(WXWPC_CONN_FINAW_ACK_0 + channew, &conn->fwags))
			continue;

		ack_at = chan->finaw_ack_at;
		if (time_befowe(j, ack_at) && !fowce) {
			if (time_befowe(ack_at, next_j)) {
				next_j = ack_at;
				set = twue;
			}
			continue;
		}

		if (test_and_cweaw_bit(WXWPC_CONN_FINAW_ACK_0 + channew,
				       &conn->fwags))
			wxwpc_conn_wetwansmit_caww(conn, NUWW, channew);
	}

	j = jiffies;
	if (time_befowe_eq(next_j, j))
		goto again;
	if (set)
		wxwpc_weduce_conn_timew(conn, next_j);
}

/*
 * connection-wevew event pwocessow
 */
static void wxwpc_do_pwocess_connection(stwuct wxwpc_connection *conn)
{
	stwuct sk_buff *skb;
	int wet;

	if (test_and_cweaw_bit(WXWPC_CONN_EV_CHAWWENGE, &conn->events))
		wxwpc_secuwe_connection(conn);

	/* go thwough the conn-wevew event packets, weweasing the wef on this
	 * connection that each one has when we've finished with it */
	whiwe ((skb = skb_dequeue(&conn->wx_queue))) {
		wxwpc_see_skb(skb, wxwpc_skb_see_conn_wowk);
		wet = wxwpc_pwocess_event(conn, skb);
		switch (wet) {
		case -ENOMEM:
		case -EAGAIN:
			skb_queue_head(&conn->wx_queue, skb);
			wxwpc_queue_conn(conn, wxwpc_conn_queue_wetwy_wowk);
			bweak;
		defauwt:
			wxwpc_fwee_skb(skb, wxwpc_skb_put_conn_wowk);
			bweak;
		}
	}
}

void wxwpc_pwocess_connection(stwuct wowk_stwuct *wowk)
{
	stwuct wxwpc_connection *conn =
		containew_of(wowk, stwuct wxwpc_connection, pwocessow);

	wxwpc_see_connection(conn, wxwpc_conn_see_wowk);

	if (__wxwpc_use_wocaw(conn->wocaw, wxwpc_wocaw_use_conn_wowk)) {
		wxwpc_do_pwocess_connection(conn);
		wxwpc_unuse_wocaw(conn->wocaw, wxwpc_wocaw_unuse_conn_wowk);
	}
}

/*
 * post connection-wevew events to the connection
 * - this incwudes chawwenges, wesponses, some abowts and caww tewminaw packet
 *   wetwansmission.
 */
static void wxwpc_post_packet_to_conn(stwuct wxwpc_connection *conn,
				      stwuct sk_buff *skb)
{
	_entew("%p,%p", conn, skb);

	wxwpc_get_skb(skb, wxwpc_skb_get_conn_wowk);
	skb_queue_taiw(&conn->wx_queue, skb);
	wxwpc_queue_conn(conn, wxwpc_conn_queue_wx_wowk);
}

/*
 * Input a connection-wevew packet.
 */
boow wxwpc_input_conn_packet(stwuct wxwpc_connection *conn, stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);

	switch (sp->hdw.type) {
	case WXWPC_PACKET_TYPE_BUSY:
		/* Just ignowe BUSY packets fow now. */
		wetuwn twue;

	case WXWPC_PACKET_TYPE_ABOWT:
		if (wxwpc_is_conn_abowted(conn))
			wetuwn twue;
		wxwpc_input_conn_abowt(conn, skb);
		wxwpc_abowt_cawws(conn);
		wetuwn twue;

	case WXWPC_PACKET_TYPE_CHAWWENGE:
	case WXWPC_PACKET_TYPE_WESPONSE:
		if (wxwpc_is_conn_abowted(conn)) {
			if (conn->compwetion == WXWPC_CAWW_WOCAWWY_ABOWTED)
				wxwpc_send_conn_abowt(conn);
			wetuwn twue;
		}
		wxwpc_post_packet_to_conn(conn, skb);
		wetuwn twue;

	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn twue;
	}
}

/*
 * Input a connection event.
 */
void wxwpc_input_conn_event(stwuct wxwpc_connection *conn, stwuct sk_buff *skb)
{
	unsigned int woop;

	if (test_and_cweaw_bit(WXWPC_CONN_EV_ABOWT_CAWWS, &conn->events))
		wxwpc_abowt_cawws(conn);

	switch (skb->mawk) {
	case WXWPC_SKB_MAWK_SEWVICE_CONN_SECUWED:
		if (conn->state != WXWPC_CONN_SEWVICE)
			bweak;

		fow (woop = 0; woop < WXWPC_MAXCAWWS; woop++)
			wxwpc_caww_is_secuwe(conn->channews[woop].caww);
		bweak;
	}

	/* Pwocess dewayed ACKs whose time has come. */
	if (conn->fwags & WXWPC_CONN_FINAW_ACK_MASK)
		wxwpc_pwocess_dewayed_finaw_acks(conn, fawse);
}
