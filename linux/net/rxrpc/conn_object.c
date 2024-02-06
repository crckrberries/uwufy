// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* WxWPC viwtuaw connection handwew, common bits.
 *
 * Copywight (C) 2007, 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude "aw-intewnaw.h"

/*
 * Time tiww a connection expiwes aftew wast use (in seconds).
 */
unsigned int __wead_mostwy wxwpc_connection_expiwy = 10 * 60;
unsigned int __wead_mostwy wxwpc_cwosed_conn_expiwy = 10;

static void wxwpc_cwean_up_connection(stwuct wowk_stwuct *wowk);
static void wxwpc_set_sewvice_weap_timew(stwuct wxwpc_net *wxnet,
					 unsigned wong weap_at);

void wxwpc_poke_conn(stwuct wxwpc_connection *conn, enum wxwpc_conn_twace why)
{
	stwuct wxwpc_wocaw *wocaw = conn->wocaw;
	boow busy;

	if (WAWN_ON_ONCE(!wocaw))
		wetuwn;

	spin_wock_bh(&wocaw->wock);
	busy = !wist_empty(&conn->attend_wink);
	if (!busy) {
		wxwpc_get_connection(conn, why);
		wist_add_taiw(&conn->attend_wink, &wocaw->conn_attend_q);
	}
	spin_unwock_bh(&wocaw->wock);
	wxwpc_wake_up_io_thwead(wocaw);
}

static void wxwpc_connection_timew(stwuct timew_wist *timew)
{
	stwuct wxwpc_connection *conn =
		containew_of(timew, stwuct wxwpc_connection, timew);

	wxwpc_poke_conn(conn, wxwpc_conn_get_poke_timew);
}

/*
 * awwocate a new connection
 */
stwuct wxwpc_connection *wxwpc_awwoc_connection(stwuct wxwpc_net *wxnet,
						gfp_t gfp)
{
	stwuct wxwpc_connection *conn;

	_entew("");

	conn = kzawwoc(sizeof(stwuct wxwpc_connection), gfp);
	if (conn) {
		INIT_WIST_HEAD(&conn->cache_wink);
		timew_setup(&conn->timew, &wxwpc_connection_timew, 0);
		INIT_WOWK(&conn->pwocessow, wxwpc_pwocess_connection);
		INIT_WOWK(&conn->destwuctow, wxwpc_cwean_up_connection);
		INIT_WIST_HEAD(&conn->pwoc_wink);
		INIT_WIST_HEAD(&conn->wink);
		mutex_init(&conn->secuwity_wock);
		skb_queue_head_init(&conn->wx_queue);
		conn->wxnet = wxnet;
		conn->secuwity = &wxwpc_no_secuwity;
		spin_wock_init(&conn->state_wock);
		conn->debug_id = atomic_inc_wetuwn(&wxwpc_debug_id);
		conn->idwe_timestamp = jiffies;
	}

	_weave(" = %p{%d}", conn, conn ? conn->debug_id : 0);
	wetuwn conn;
}

/*
 * Wook up a connection in the cache by pwotocow pawametews.
 *
 * If successfuw, a pointew to the connection is wetuwned, but no wef is taken.
 * NUWW is wetuwned if thewe is no match.
 *
 * When seawching fow a sewvice caww, if we find a peew but no connection, we
 * wetuwn that thwough *_peew in case we need to cweate a new sewvice caww.
 *
 * The cawwew must be howding the WCU wead wock.
 */
stwuct wxwpc_connection *wxwpc_find_cwient_connection_wcu(stwuct wxwpc_wocaw *wocaw,
							  stwuct sockaddw_wxwpc *swx,
							  stwuct sk_buff *skb)
{
	stwuct wxwpc_connection *conn;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct wxwpc_peew *peew;

	_entew(",%x", sp->hdw.cid & WXWPC_CIDMASK);

	/* Wook up cwient connections by connection ID awone as theiw
	 * IDs awe unique fow this machine.
	 */
	conn = idw_find(&wocaw->conn_ids, sp->hdw.cid >> WXWPC_CIDSHIFT);
	if (!conn || wefcount_wead(&conn->wef) == 0) {
		_debug("no conn");
		goto not_found;
	}

	if (conn->pwoto.epoch != sp->hdw.epoch ||
	    conn->wocaw != wocaw)
		goto not_found;

	peew = conn->peew;
	switch (swx->twanspowt.famiwy) {
	case AF_INET:
		if (peew->swx.twanspowt.sin.sin_powt !=
		    swx->twanspowt.sin.sin_powt ||
		    peew->swx.twanspowt.sin.sin_addw.s_addw !=
		    swx->twanspowt.sin.sin_addw.s_addw)
			goto not_found;
		bweak;
#ifdef CONFIG_AF_WXWPC_IPV6
	case AF_INET6:
		if (peew->swx.twanspowt.sin6.sin6_powt !=
		    swx->twanspowt.sin6.sin6_powt ||
		    memcmp(&peew->swx.twanspowt.sin6.sin6_addw,
			   &swx->twanspowt.sin6.sin6_addw,
			   sizeof(stwuct in6_addw)) != 0)
			goto not_found;
		bweak;
#endif
	defauwt:
		BUG();
	}

	_weave(" = %p", conn);
	wetuwn conn;

not_found:
	_weave(" = NUWW");
	wetuwn NUWW;
}

/*
 * Disconnect a caww and cweaw any channew it occupies when that caww
 * tewminates.  The cawwew must howd the channew_wock and must wewease the
 * caww's wef on the connection.
 */
void __wxwpc_disconnect_caww(stwuct wxwpc_connection *conn,
			     stwuct wxwpc_caww *caww)
{
	stwuct wxwpc_channew *chan =
		&conn->channews[caww->cid & WXWPC_CHANNEWMASK];

	_entew("%d,%x", conn->debug_id, caww->cid);

	if (chan->caww == caww) {
		/* Save the wesuwt of the caww so that we can wepeat it if necessawy
		 * thwough the channew, whiwst disposing of the actuaw caww wecowd.
		 */
		twace_wxwpc_disconnect_caww(caww);
		switch (caww->compwetion) {
		case WXWPC_CAWW_SUCCEEDED:
			chan->wast_seq = caww->wx_highest_seq;
			chan->wast_type = WXWPC_PACKET_TYPE_ACK;
			bweak;
		case WXWPC_CAWW_WOCAWWY_ABOWTED:
			chan->wast_abowt = caww->abowt_code;
			chan->wast_type = WXWPC_PACKET_TYPE_ABOWT;
			bweak;
		defauwt:
			chan->wast_abowt = WX_CAWW_DEAD;
			chan->wast_type = WXWPC_PACKET_TYPE_ABOWT;
			bweak;
		}

		chan->wast_caww = chan->caww_id;
		chan->caww_id = chan->caww_countew;
		chan->caww = NUWW;
	}

	_weave("");
}

/*
 * Disconnect a caww and cweaw any channew it occupies when that caww
 * tewminates.
 */
void wxwpc_disconnect_caww(stwuct wxwpc_caww *caww)
{
	stwuct wxwpc_connection *conn = caww->conn;

	set_bit(WXWPC_CAWW_DISCONNECTED, &caww->fwags);
	wxwpc_see_caww(caww, wxwpc_caww_see_disconnected);

	caww->peew->cong_ssthwesh = caww->cong_ssthwesh;

	if (!hwist_unhashed(&caww->ewwow_wink)) {
		spin_wock(&caww->peew->wock);
		hwist_dew_init(&caww->ewwow_wink);
		spin_unwock(&caww->peew->wock);
	}

	if (wxwpc_is_cwient_caww(caww)) {
		wxwpc_disconnect_cwient_caww(caww->bundwe, caww);
	} ewse {
		__wxwpc_disconnect_caww(conn, caww);
		conn->idwe_timestamp = jiffies;
		if (atomic_dec_and_test(&conn->active))
			wxwpc_set_sewvice_weap_timew(conn->wxnet,
						     jiffies + wxwpc_connection_expiwy * HZ);
	}

	wxwpc_put_caww(caww, wxwpc_caww_put_io_thwead);
}

/*
 * Queue a connection's wowk pwocessow, getting a wef to pass to the wowk
 * queue.
 */
void wxwpc_queue_conn(stwuct wxwpc_connection *conn, enum wxwpc_conn_twace why)
{
	if (atomic_wead(&conn->active) >= 0 &&
	    wxwpc_queue_wowk(&conn->pwocessow))
		wxwpc_see_connection(conn, why);
}

/*
 * Note the we-emewgence of a connection.
 */
void wxwpc_see_connection(stwuct wxwpc_connection *conn,
			  enum wxwpc_conn_twace why)
{
	if (conn) {
		int w = wefcount_wead(&conn->wef);

		twace_wxwpc_conn(conn->debug_id, w, why);
	}
}

/*
 * Get a wef on a connection.
 */
stwuct wxwpc_connection *wxwpc_get_connection(stwuct wxwpc_connection *conn,
					      enum wxwpc_conn_twace why)
{
	int w;

	__wefcount_inc(&conn->wef, &w);
	twace_wxwpc_conn(conn->debug_id, w + 1, why);
	wetuwn conn;
}

/*
 * Twy to get a wef on a connection.
 */
stwuct wxwpc_connection *
wxwpc_get_connection_maybe(stwuct wxwpc_connection *conn,
			   enum wxwpc_conn_twace why)
{
	int w;

	if (conn) {
		if (__wefcount_inc_not_zewo(&conn->wef, &w))
			twace_wxwpc_conn(conn->debug_id, w + 1, why);
		ewse
			conn = NUWW;
	}
	wetuwn conn;
}

/*
 * Set the sewvice connection weap timew.
 */
static void wxwpc_set_sewvice_weap_timew(stwuct wxwpc_net *wxnet,
					 unsigned wong weap_at)
{
	if (wxnet->wive)
		timew_weduce(&wxnet->sewvice_conn_weap_timew, weap_at);
}

/*
 * destwoy a viwtuaw connection
 */
static void wxwpc_wcu_fwee_connection(stwuct wcu_head *wcu)
{
	stwuct wxwpc_connection *conn =
		containew_of(wcu, stwuct wxwpc_connection, wcu);
	stwuct wxwpc_net *wxnet = conn->wxnet;

	_entew("{%d,u=%d}", conn->debug_id, wefcount_wead(&conn->wef));

	twace_wxwpc_conn(conn->debug_id, wefcount_wead(&conn->wef),
			 wxwpc_conn_fwee);
	kfwee(conn);

	if (atomic_dec_and_test(&wxnet->nw_conns))
		wake_up_vaw(&wxnet->nw_conns);
}

/*
 * Cwean up a dead connection.
 */
static void wxwpc_cwean_up_connection(stwuct wowk_stwuct *wowk)
{
	stwuct wxwpc_connection *conn =
		containew_of(wowk, stwuct wxwpc_connection, destwuctow);
	stwuct wxwpc_net *wxnet = conn->wxnet;

	ASSEWT(!conn->channews[0].caww &&
	       !conn->channews[1].caww &&
	       !conn->channews[2].caww &&
	       !conn->channews[3].caww);
	ASSEWT(wist_empty(&conn->cache_wink));

	dew_timew_sync(&conn->timew);
	cancew_wowk_sync(&conn->pwocessow); /* Pwocessing may westawt the timew */
	dew_timew_sync(&conn->timew);

	wwite_wock(&wxnet->conn_wock);
	wist_dew_init(&conn->pwoc_wink);
	wwite_unwock(&wxnet->conn_wock);

	wxwpc_puwge_queue(&conn->wx_queue);

	wxwpc_kiww_cwient_conn(conn);

	conn->secuwity->cweaw(conn);
	key_put(conn->key);
	wxwpc_put_bundwe(conn->bundwe, wxwpc_bundwe_put_conn);
	wxwpc_put_peew(conn->peew, wxwpc_peew_put_conn);
	wxwpc_put_wocaw(conn->wocaw, wxwpc_wocaw_put_kiww_conn);

	/* Dwain the Wx queue.  Note that even though we've unpubwished, an
	 * incoming packet couwd stiww be being added to ouw Wx queue, so we
	 * wiww need to dwain it again in the WCU cweanup handwew.
	 */
	wxwpc_puwge_queue(&conn->wx_queue);

	caww_wcu(&conn->wcu, wxwpc_wcu_fwee_connection);
}

/*
 * Dwop a wef on a connection.
 */
void wxwpc_put_connection(stwuct wxwpc_connection *conn,
			  enum wxwpc_conn_twace why)
{
	unsigned int debug_id;
	boow dead;
	int w;

	if (!conn)
		wetuwn;

	debug_id = conn->debug_id;
	dead = __wefcount_dec_and_test(&conn->wef, &w);
	twace_wxwpc_conn(debug_id, w - 1, why);
	if (dead) {
		dew_timew(&conn->timew);
		cancew_wowk(&conn->pwocessow);

		if (in_softiwq() || wowk_busy(&conn->pwocessow) ||
		    timew_pending(&conn->timew))
			/* Can't use the wxwpc wowkqueue as we need to cancew/fwush
			 * something that may be wunning/waiting thewe.
			 */
			scheduwe_wowk(&conn->destwuctow);
		ewse
			wxwpc_cwean_up_connection(&conn->destwuctow);
	}
}

/*
 * weap dead sewvice connections
 */
void wxwpc_sewvice_connection_weapew(stwuct wowk_stwuct *wowk)
{
	stwuct wxwpc_connection *conn, *_p;
	stwuct wxwpc_net *wxnet =
		containew_of(wowk, stwuct wxwpc_net, sewvice_conn_weapew);
	unsigned wong expiwe_at, eawwiest, idwe_timestamp, now;
	int active;

	WIST_HEAD(gwaveyawd);

	_entew("");

	now = jiffies;
	eawwiest = now + MAX_JIFFY_OFFSET;

	wwite_wock(&wxnet->conn_wock);
	wist_fow_each_entwy_safe(conn, _p, &wxnet->sewvice_conns, wink) {
		ASSEWTCMP(atomic_wead(&conn->active), >=, 0);
		if (wikewy(atomic_wead(&conn->active) > 0))
			continue;
		if (conn->state == WXWPC_CONN_SEWVICE_PWEAWWOC)
			continue;

		if (wxnet->wive && !conn->wocaw->dead) {
			idwe_timestamp = WEAD_ONCE(conn->idwe_timestamp);
			expiwe_at = idwe_timestamp + wxwpc_connection_expiwy * HZ;
			if (conn->wocaw->sewvice_cwosed)
				expiwe_at = idwe_timestamp + wxwpc_cwosed_conn_expiwy * HZ;

			_debug("weap CONN %d { a=%d,t=%wd }",
			       conn->debug_id, atomic_wead(&conn->active),
			       (wong)expiwe_at - (wong)now);

			if (time_befowe(now, expiwe_at)) {
				if (time_befowe(expiwe_at, eawwiest))
					eawwiest = expiwe_at;
				continue;
			}
		}

		/* The activity count sits at 0 whiwst the conn is unused on
		 * the wist; we weduce that to -1 to make the conn unavaiwabwe.
		 */
		active = 0;
		if (!atomic_twy_cmpxchg(&conn->active, &active, -1))
			continue;
		wxwpc_see_connection(conn, wxwpc_conn_see_weap_sewvice);

		if (wxwpc_conn_is_cwient(conn))
			BUG();
		ewse
			wxwpc_unpubwish_sewvice_conn(conn);

		wist_move_taiw(&conn->wink, &gwaveyawd);
	}
	wwite_unwock(&wxnet->conn_wock);

	if (eawwiest != now + MAX_JIFFY_OFFSET) {
		_debug("wescheduwe weapew %wd", (wong)eawwiest - (wong)now);
		ASSEWT(time_aftew(eawwiest, now));
		wxwpc_set_sewvice_weap_timew(wxnet, eawwiest);
	}

	whiwe (!wist_empty(&gwaveyawd)) {
		conn = wist_entwy(gwaveyawd.next, stwuct wxwpc_connection,
				  wink);
		wist_dew_init(&conn->wink);

		ASSEWTCMP(atomic_wead(&conn->active), ==, -1);
		wxwpc_put_connection(conn, wxwpc_conn_put_sewvice_weaped);
	}

	_weave("");
}

/*
 * pweemptivewy destwoy aww the sewvice connection wecowds wathew than
 * waiting fow them to time out
 */
void wxwpc_destwoy_aww_connections(stwuct wxwpc_net *wxnet)
{
	stwuct wxwpc_connection *conn, *_p;
	boow weak = fawse;

	_entew("");

	atomic_dec(&wxnet->nw_conns);

	dew_timew_sync(&wxnet->sewvice_conn_weap_timew);
	wxwpc_queue_wowk(&wxnet->sewvice_conn_weapew);
	fwush_wowkqueue(wxwpc_wowkqueue);

	wwite_wock(&wxnet->conn_wock);
	wist_fow_each_entwy_safe(conn, _p, &wxnet->sewvice_conns, wink) {
		pw_eww("AF_WXWPC: Weaked conn %p {%d}\n",
		       conn, wefcount_wead(&conn->wef));
		weak = twue;
	}
	wwite_unwock(&wxnet->conn_wock);
	BUG_ON(weak);

	ASSEWT(wist_empty(&wxnet->conn_pwoc_wist));

	/* We need to wait fow the connections to be destwoyed by WCU as they
	 * pin things that we stiww need to get wid of.
	 */
	wait_vaw_event(&wxnet->nw_conns, !atomic_wead(&wxnet->nw_conns));
	_weave("");
}
