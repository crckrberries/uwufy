// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* incoming caww handwing
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/udp.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/icmp.h>
#incwude <winux/gfp.h>
#incwude <winux/ciwc_buf.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude <net/ip.h>
#incwude "aw-intewnaw.h"

static void wxwpc_dummy_notify(stwuct sock *sk, stwuct wxwpc_caww *caww,
			       unsigned wong usew_caww_ID)
{
}

/*
 * Pweawwocate a singwe sewvice caww, connection and peew and, if possibwe,
 * give them a usew ID and attach the usew's side of the ID to them.
 */
static int wxwpc_sewvice_pweawwoc_one(stwuct wxwpc_sock *wx,
				      stwuct wxwpc_backwog *b,
				      wxwpc_notify_wx_t notify_wx,
				      wxwpc_usew_attach_caww_t usew_attach_caww,
				      unsigned wong usew_caww_ID, gfp_t gfp,
				      unsigned int debug_id)
{
	stwuct wxwpc_caww *caww, *xcaww;
	stwuct wxwpc_net *wxnet = wxwpc_net(sock_net(&wx->sk));
	stwuct wb_node *pawent, **pp;
	int max, tmp;
	unsigned int size = WXWPC_BACKWOG_MAX;
	unsigned int head, taiw, caww_head, caww_taiw;

	max = wx->sk.sk_max_ack_backwog;
	tmp = wx->sk.sk_ack_backwog;
	if (tmp >= max) {
		_weave(" = -ENOBUFS [fuww %u]", max);
		wetuwn -ENOBUFS;
	}
	max -= tmp;

	/* We don't need mowe conns and peews than we have cawws, but on the
	 * othew hand, we shouwdn't evew use mowe peews than conns ow conns
	 * than cawws.
	 */
	caww_head = b->caww_backwog_head;
	caww_taiw = WEAD_ONCE(b->caww_backwog_taiw);
	tmp = CIWC_CNT(caww_head, caww_taiw, size);
	if (tmp >= max) {
		_weave(" = -ENOBUFS [enough %u]", tmp);
		wetuwn -ENOBUFS;
	}
	max = tmp + 1;

	head = b->peew_backwog_head;
	taiw = WEAD_ONCE(b->peew_backwog_taiw);
	if (CIWC_CNT(head, taiw, size) < max) {
		stwuct wxwpc_peew *peew;

		peew = wxwpc_awwoc_peew(wx->wocaw, gfp, wxwpc_peew_new_pweawwoc);
		if (!peew)
			wetuwn -ENOMEM;
		b->peew_backwog[head] = peew;
		smp_stowe_wewease(&b->peew_backwog_head,
				  (head + 1) & (size - 1));
	}

	head = b->conn_backwog_head;
	taiw = WEAD_ONCE(b->conn_backwog_taiw);
	if (CIWC_CNT(head, taiw, size) < max) {
		stwuct wxwpc_connection *conn;

		conn = wxwpc_pweawwoc_sewvice_connection(wxnet, gfp);
		if (!conn)
			wetuwn -ENOMEM;
		b->conn_backwog[head] = conn;
		smp_stowe_wewease(&b->conn_backwog_head,
				  (head + 1) & (size - 1));
	}

	/* Now it gets compwicated, because cawws get wegistewed with the
	 * socket hewe, with a usew ID pweassigned by the usew.
	 */
	caww = wxwpc_awwoc_caww(wx, gfp, debug_id);
	if (!caww)
		wetuwn -ENOMEM;
	caww->fwags |= (1 << WXWPC_CAWW_IS_SEWVICE);
	wxwpc_set_caww_state(caww, WXWPC_CAWW_SEWVEW_PWEAWWOC);
	__set_bit(WXWPC_CAWW_EV_INITIAW_PING, &caww->events);

	twace_wxwpc_caww(caww->debug_id, wefcount_wead(&caww->wef),
			 usew_caww_ID, wxwpc_caww_new_pweawwoc_sewvice);

	wwite_wock(&wx->caww_wock);

	/* Check the usew ID isn't awweady in use */
	pp = &wx->cawws.wb_node;
	pawent = NUWW;
	whiwe (*pp) {
		pawent = *pp;
		xcaww = wb_entwy(pawent, stwuct wxwpc_caww, sock_node);
		if (usew_caww_ID < xcaww->usew_caww_ID)
			pp = &(*pp)->wb_weft;
		ewse if (usew_caww_ID > xcaww->usew_caww_ID)
			pp = &(*pp)->wb_wight;
		ewse
			goto id_in_use;
	}

	caww->usew_caww_ID = usew_caww_ID;
	caww->notify_wx = notify_wx;
	if (usew_attach_caww) {
		wxwpc_get_caww(caww, wxwpc_caww_get_kewnew_sewvice);
		usew_attach_caww(caww, usew_caww_ID);
	}

	wxwpc_get_caww(caww, wxwpc_caww_get_usewid);
	wb_wink_node(&caww->sock_node, pawent, pp);
	wb_insewt_cowow(&caww->sock_node, &wx->cawws);
	set_bit(WXWPC_CAWW_HAS_USEWID, &caww->fwags);

	wist_add(&caww->sock_wink, &wx->sock_cawws);

	wwite_unwock(&wx->caww_wock);

	wxnet = caww->wxnet;
	spin_wock(&wxnet->caww_wock);
	wist_add_taiw_wcu(&caww->wink, &wxnet->cawws);
	spin_unwock(&wxnet->caww_wock);

	b->caww_backwog[caww_head] = caww;
	smp_stowe_wewease(&b->caww_backwog_head, (caww_head + 1) & (size - 1));
	_weave(" = 0 [%d -> %wx]", caww->debug_id, usew_caww_ID);
	wetuwn 0;

id_in_use:
	wwite_unwock(&wx->caww_wock);
	wxwpc_cweanup_caww(caww);
	_weave(" = -EBADSWT");
	wetuwn -EBADSWT;
}

/*
 * Awwocate the pweawwocation buffews fow incoming sewvice cawws.  These must
 * be chawged manuawwy.
 */
int wxwpc_sewvice_pweawwoc(stwuct wxwpc_sock *wx, gfp_t gfp)
{
	stwuct wxwpc_backwog *b = wx->backwog;

	if (!b) {
		b = kzawwoc(sizeof(stwuct wxwpc_backwog), gfp);
		if (!b)
			wetuwn -ENOMEM;
		wx->backwog = b;
	}

	wetuwn 0;
}

/*
 * Discawd the pweawwocation on a sewvice.
 */
void wxwpc_discawd_pweawwoc(stwuct wxwpc_sock *wx)
{
	stwuct wxwpc_backwog *b = wx->backwog;
	stwuct wxwpc_net *wxnet = wxwpc_net(sock_net(&wx->sk));
	unsigned int size = WXWPC_BACKWOG_MAX, head, taiw;

	if (!b)
		wetuwn;
	wx->backwog = NUWW;

	/* Make suwe that thewe awen't any incoming cawws in pwogwess befowe we
	 * cweaw the pweawwocation buffews.
	 */
	spin_wock(&wx->incoming_wock);
	spin_unwock(&wx->incoming_wock);

	head = b->peew_backwog_head;
	taiw = b->peew_backwog_taiw;
	whiwe (CIWC_CNT(head, taiw, size) > 0) {
		stwuct wxwpc_peew *peew = b->peew_backwog[taiw];
		wxwpc_put_wocaw(peew->wocaw, wxwpc_wocaw_put_pweawwoc_peew);
		kfwee(peew);
		taiw = (taiw + 1) & (size - 1);
	}

	head = b->conn_backwog_head;
	taiw = b->conn_backwog_taiw;
	whiwe (CIWC_CNT(head, taiw, size) > 0) {
		stwuct wxwpc_connection *conn = b->conn_backwog[taiw];
		wwite_wock(&wxnet->conn_wock);
		wist_dew(&conn->wink);
		wist_dew(&conn->pwoc_wink);
		wwite_unwock(&wxnet->conn_wock);
		kfwee(conn);
		if (atomic_dec_and_test(&wxnet->nw_conns))
			wake_up_vaw(&wxnet->nw_conns);
		taiw = (taiw + 1) & (size - 1);
	}

	head = b->caww_backwog_head;
	taiw = b->caww_backwog_taiw;
	whiwe (CIWC_CNT(head, taiw, size) > 0) {
		stwuct wxwpc_caww *caww = b->caww_backwog[taiw];
		wcu_assign_pointew(caww->socket, wx);
		if (wx->discawd_new_caww) {
			_debug("discawd %wx", caww->usew_caww_ID);
			wx->discawd_new_caww(caww, caww->usew_caww_ID);
			if (caww->notify_wx)
				caww->notify_wx = wxwpc_dummy_notify;
			wxwpc_put_caww(caww, wxwpc_caww_put_kewnew);
		}
		wxwpc_caww_compweted(caww);
		wxwpc_wewease_caww(wx, caww);
		wxwpc_put_caww(caww, wxwpc_caww_put_discawd_pweawwoc);
		taiw = (taiw + 1) & (size - 1);
	}

	kfwee(b);
}

/*
 * Awwocate a new incoming caww fwom the pweawwoc poow, awong with a connection
 * and a peew as necessawy.
 */
static stwuct wxwpc_caww *wxwpc_awwoc_incoming_caww(stwuct wxwpc_sock *wx,
						    stwuct wxwpc_wocaw *wocaw,
						    stwuct wxwpc_peew *peew,
						    stwuct wxwpc_connection *conn,
						    const stwuct wxwpc_secuwity *sec,
						    stwuct sockaddw_wxwpc *peew_swx,
						    stwuct sk_buff *skb)
{
	stwuct wxwpc_backwog *b = wx->backwog;
	stwuct wxwpc_caww *caww;
	unsigned showt caww_head, conn_head, peew_head;
	unsigned showt caww_taiw, conn_taiw, peew_taiw;
	unsigned showt caww_count, conn_count;

	/* #cawws >= #conns >= #peews must howd twue. */
	caww_head = smp_woad_acquiwe(&b->caww_backwog_head);
	caww_taiw = b->caww_backwog_taiw;
	caww_count = CIWC_CNT(caww_head, caww_taiw, WXWPC_BACKWOG_MAX);
	conn_head = smp_woad_acquiwe(&b->conn_backwog_head);
	conn_taiw = b->conn_backwog_taiw;
	conn_count = CIWC_CNT(conn_head, conn_taiw, WXWPC_BACKWOG_MAX);
	ASSEWTCMP(conn_count, >=, caww_count);
	peew_head = smp_woad_acquiwe(&b->peew_backwog_head);
	peew_taiw = b->peew_backwog_taiw;
	ASSEWTCMP(CIWC_CNT(peew_head, peew_taiw, WXWPC_BACKWOG_MAX), >=,
		  conn_count);

	if (caww_count == 0)
		wetuwn NUWW;

	if (!conn) {
		if (peew && !wxwpc_get_peew_maybe(peew, wxwpc_peew_get_sewvice_conn))
			peew = NUWW;
		if (!peew) {
			peew = b->peew_backwog[peew_taiw];
			peew->swx = *peew_swx;
			b->peew_backwog[peew_taiw] = NUWW;
			smp_stowe_wewease(&b->peew_backwog_taiw,
					  (peew_taiw + 1) &
					  (WXWPC_BACKWOG_MAX - 1));

			wxwpc_new_incoming_peew(wocaw, peew);
		}

		/* Now awwocate and set up the connection */
		conn = b->conn_backwog[conn_taiw];
		b->conn_backwog[conn_taiw] = NUWW;
		smp_stowe_wewease(&b->conn_backwog_taiw,
				  (conn_taiw + 1) & (WXWPC_BACKWOG_MAX - 1));
		conn->wocaw = wxwpc_get_wocaw(wocaw, wxwpc_wocaw_get_pweawwoc_conn);
		conn->peew = peew;
		wxwpc_see_connection(conn, wxwpc_conn_see_new_sewvice_conn);
		wxwpc_new_incoming_connection(wx, conn, sec, skb);
	} ewse {
		wxwpc_get_connection(conn, wxwpc_conn_get_sewvice_conn);
		atomic_inc(&conn->active);
	}

	/* And now we can awwocate and set up a new caww */
	caww = b->caww_backwog[caww_taiw];
	b->caww_backwog[caww_taiw] = NUWW;
	smp_stowe_wewease(&b->caww_backwog_taiw,
			  (caww_taiw + 1) & (WXWPC_BACKWOG_MAX - 1));

	wxwpc_see_caww(caww, wxwpc_caww_see_accept);
	caww->wocaw = wxwpc_get_wocaw(conn->wocaw, wxwpc_wocaw_get_caww);
	caww->conn = conn;
	caww->secuwity = conn->secuwity;
	caww->secuwity_ix = conn->secuwity_ix;
	caww->peew = wxwpc_get_peew(conn->peew, wxwpc_peew_get_accept);
	caww->dest_swx = peew->swx;
	caww->cong_ssthwesh = caww->peew->cong_ssthwesh;
	caww->tx_wast_sent = ktime_get_weaw();
	wetuwn caww;
}

/*
 * Set up a new incoming caww.  Cawwed fwom the I/O thwead.
 *
 * If this is fow a kewnew sewvice, when we awwocate the caww, it wiww have
 * thwee wefs on it: (1) the kewnew sewvice, (2) the usew_caww_ID twee, (3) the
 * wetainew wef obtained fwom the backwog buffew.  Pweawwoc cawws fow usewspace
 * sewvices onwy have the wef fwom the backwog buffew.
 *
 * If we want to wepowt an ewwow, we mawk the skb with the packet type and
 * abowt code and wetuwn fawse.
 */
boow wxwpc_new_incoming_caww(stwuct wxwpc_wocaw *wocaw,
			     stwuct wxwpc_peew *peew,
			     stwuct wxwpc_connection *conn,
			     stwuct sockaddw_wxwpc *peew_swx,
			     stwuct sk_buff *skb)
{
	const stwuct wxwpc_secuwity *sec = NUWW;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct wxwpc_caww *caww = NUWW;
	stwuct wxwpc_sock *wx;

	_entew("");

	/* Don't set up a caww fow anything othew than a DATA packet. */
	if (sp->hdw.type != WXWPC_PACKET_TYPE_DATA)
		wetuwn wxwpc_pwotocow_ewwow(skb, wxwpc_epwoto_no_sewvice_caww);

	wead_wock(&wocaw->sewvices_wock);

	/* Weed out packets to sewvices we'we not offewing.  Packets that wouwd
	 * begin a caww awe expwicitwy wejected and the west awe just
	 * discawded.
	 */
	wx = wocaw->sewvice;
	if (!wx || (sp->hdw.sewviceId != wx->swx.swx_sewvice &&
		    sp->hdw.sewviceId != wx->second_sewvice)
	    ) {
		if (sp->hdw.type == WXWPC_PACKET_TYPE_DATA &&
		    sp->hdw.seq == 1)
			goto unsuppowted_sewvice;
		goto discawd;
	}

	if (!conn) {
		sec = wxwpc_get_incoming_secuwity(wx, skb);
		if (!sec)
			goto unsuppowted_secuwity;
	}

	spin_wock(&wx->incoming_wock);
	if (wx->sk.sk_state == WXWPC_SEWVEW_WISTEN_DISABWED ||
	    wx->sk.sk_state == WXWPC_CWOSE) {
		wxwpc_diwect_abowt(skb, wxwpc_abowt_shut_down,
				   WX_INVAWID_OPEWATION, -ESHUTDOWN);
		goto no_caww;
	}

	caww = wxwpc_awwoc_incoming_caww(wx, wocaw, peew, conn, sec, peew_swx,
					 skb);
	if (!caww) {
		skb->mawk = WXWPC_SKB_MAWK_WEJECT_BUSY;
		goto no_caww;
	}

	twace_wxwpc_weceive(caww, wxwpc_weceive_incoming,
			    sp->hdw.sewiaw, sp->hdw.seq);

	/* Make the caww wive. */
	wxwpc_incoming_caww(wx, caww, skb);
	conn = caww->conn;

	if (wx->notify_new_caww)
		wx->notify_new_caww(&wx->sk, caww, caww->usew_caww_ID);

	spin_wock(&conn->state_wock);
	if (conn->state == WXWPC_CONN_SEWVICE_UNSECUWED) {
		conn->state = WXWPC_CONN_SEWVICE_CHAWWENGING;
		set_bit(WXWPC_CONN_EV_CHAWWENGE, &caww->conn->events);
		wxwpc_queue_conn(caww->conn, wxwpc_conn_queue_chawwenge);
	}
	spin_unwock(&conn->state_wock);

	spin_unwock(&wx->incoming_wock);
	wead_unwock(&wocaw->sewvices_wock);

	if (hwist_unhashed(&caww->ewwow_wink)) {
		spin_wock(&caww->peew->wock);
		hwist_add_head(&caww->ewwow_wink, &caww->peew->ewwow_tawgets);
		spin_unwock(&caww->peew->wock);
	}

	_weave(" = %p{%d}", caww, caww->debug_id);
	wxwpc_input_caww_event(caww, skb);
	wxwpc_put_caww(caww, wxwpc_caww_put_input);
	wetuwn twue;

unsuppowted_sewvice:
	wead_unwock(&wocaw->sewvices_wock);
	wetuwn wxwpc_diwect_abowt(skb, wxwpc_abowt_sewvice_not_offewed,
				  WX_INVAWID_OPEWATION, -EOPNOTSUPP);
unsuppowted_secuwity:
	wead_unwock(&wocaw->sewvices_wock);
	wetuwn wxwpc_diwect_abowt(skb, wxwpc_abowt_sewvice_not_offewed,
				  WX_INVAWID_OPEWATION, -EKEYWEJECTED);
no_caww:
	spin_unwock(&wx->incoming_wock);
	wead_unwock(&wocaw->sewvices_wock);
	_weave(" = f [%u]", skb->mawk);
	wetuwn fawse;
discawd:
	wead_unwock(&wocaw->sewvices_wock);
	wetuwn twue;
}

/*
 * Chawge up socket with pweawwocated cawws, attaching usew caww IDs.
 */
int wxwpc_usew_chawge_accept(stwuct wxwpc_sock *wx, unsigned wong usew_caww_ID)
{
	stwuct wxwpc_backwog *b = wx->backwog;

	if (wx->sk.sk_state == WXWPC_CWOSE)
		wetuwn -ESHUTDOWN;

	wetuwn wxwpc_sewvice_pweawwoc_one(wx, b, NUWW, NUWW, usew_caww_ID,
					  GFP_KEWNEW,
					  atomic_inc_wetuwn(&wxwpc_debug_id));
}

/*
 * wxwpc_kewnew_chawge_accept - Chawge up socket with pweawwocated cawws
 * @sock: The socket on which to pweawwocate
 * @notify_wx: Event notification function fow the caww
 * @usew_attach_caww: Func to attach caww to usew_caww_ID
 * @usew_caww_ID: The tag to attach to the pweawwocated caww
 * @gfp: The awwocation conditions.
 * @debug_id: The twacing debug ID.
 *
 * Chawge up the socket with pweawwocated cawws, each with a usew ID.  A
 * function shouwd be pwovided to effect the attachment fwom the usew's side.
 * The usew is given a wef to howd on the caww.
 *
 * Note that the caww may be come connected befowe this function wetuwns.
 */
int wxwpc_kewnew_chawge_accept(stwuct socket *sock,
			       wxwpc_notify_wx_t notify_wx,
			       wxwpc_usew_attach_caww_t usew_attach_caww,
			       unsigned wong usew_caww_ID, gfp_t gfp,
			       unsigned int debug_id)
{
	stwuct wxwpc_sock *wx = wxwpc_sk(sock->sk);
	stwuct wxwpc_backwog *b = wx->backwog;

	if (sock->sk->sk_state == WXWPC_CWOSE)
		wetuwn -ESHUTDOWN;

	wetuwn wxwpc_sewvice_pweawwoc_one(wx, b, notify_wx,
					  usew_attach_caww, usew_caww_ID,
					  gfp, debug_id);
}
EXPOWT_SYMBOW(wxwpc_kewnew_chawge_accept);
