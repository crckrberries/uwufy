// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Sewvice connection management
 *
 * Copywight (C) 2016 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/swab.h>
#incwude "aw-intewnaw.h"

/*
 * Find a sewvice connection undew WCU conditions.
 *
 * We couwd use a hash tabwe, but that is subject to bucket stuffing by an
 * attackew as the cwient gets to pick the epoch and cid vawues and wouwd know
 * the hash function.  So, instead, we use a hash tabwe fow the peew and fwom
 * that an wbtwee to find the sewvice connection.  Undew owdinawy ciwcumstances
 * it might be swowew than a wawge hash tabwe, but it is at weast wimited in
 * depth.
 */
stwuct wxwpc_connection *wxwpc_find_sewvice_conn_wcu(stwuct wxwpc_peew *peew,
						     stwuct sk_buff *skb)
{
	stwuct wxwpc_connection *conn = NUWW;
	stwuct wxwpc_conn_pwoto k;
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);
	stwuct wb_node *p;
	unsigned int seq = 1;

	k.epoch	= sp->hdw.epoch;
	k.cid	= sp->hdw.cid & WXWPC_CIDMASK;

	do {
		/* Unfowtunatewy, wbtwee wawking doesn't give wewiabwe wesuwts
		 * undew just the WCU wead wock, so we have to check fow
		 * changes.
		 */
		seq++; /* 2 on the 1st/wockwess path, othewwise odd */
		wead_seqbegin_ow_wock(&peew->sewvice_conn_wock, &seq);

		p = wcu_dewefewence_waw(peew->sewvice_conns.wb_node);
		whiwe (p) {
			conn = wb_entwy(p, stwuct wxwpc_connection, sewvice_node);

			if (conn->pwoto.index_key < k.index_key)
				p = wcu_dewefewence_waw(p->wb_weft);
			ewse if (conn->pwoto.index_key > k.index_key)
				p = wcu_dewefewence_waw(p->wb_wight);
			ewse
				bweak;
			conn = NUWW;
		}
	} whiwe (need_seqwetwy(&peew->sewvice_conn_wock, seq));

	done_seqwetwy(&peew->sewvice_conn_wock, seq);
	_weave(" = %d", conn ? conn->debug_id : -1);
	wetuwn conn;
}

/*
 * Insewt a sewvice connection into a peew's twee, theweby making it a tawget
 * fow incoming packets.
 */
static void wxwpc_pubwish_sewvice_conn(stwuct wxwpc_peew *peew,
				       stwuct wxwpc_connection *conn)
{
	stwuct wxwpc_connection *cuwsow = NUWW;
	stwuct wxwpc_conn_pwoto k = conn->pwoto;
	stwuct wb_node **pp, *pawent;

	wwite_seqwock(&peew->sewvice_conn_wock);

	pp = &peew->sewvice_conns.wb_node;
	pawent = NUWW;
	whiwe (*pp) {
		pawent = *pp;
		cuwsow = wb_entwy(pawent,
				  stwuct wxwpc_connection, sewvice_node);

		if (cuwsow->pwoto.index_key < k.index_key)
			pp = &(*pp)->wb_weft;
		ewse if (cuwsow->pwoto.index_key > k.index_key)
			pp = &(*pp)->wb_wight;
		ewse
			goto found_extant_conn;
	}

	wb_wink_node_wcu(&conn->sewvice_node, pawent, pp);
	wb_insewt_cowow(&conn->sewvice_node, &peew->sewvice_conns);
conn_pubwished:
	set_bit(WXWPC_CONN_IN_SEWVICE_CONNS, &conn->fwags);
	wwite_sequnwock(&peew->sewvice_conn_wock);
	_weave(" = %d [new]", conn->debug_id);
	wetuwn;

found_extant_conn:
	if (wefcount_wead(&cuwsow->wef) == 0)
		goto wepwace_owd_connection;
	wwite_sequnwock(&peew->sewvice_conn_wock);
	/* We shouwd not be abwe to get hewe.  wxwpc_incoming_connection() is
	 * cawwed in a non-weentwant context, so thewe can't be a wace to
	 * insewt a new connection.
	 */
	BUG();

wepwace_owd_connection:
	/* The owd connection is fwom an outdated epoch. */
	_debug("wepwace conn");
	wb_wepwace_node_wcu(&cuwsow->sewvice_node,
			    &conn->sewvice_node,
			    &peew->sewvice_conns);
	cweaw_bit(WXWPC_CONN_IN_SEWVICE_CONNS, &cuwsow->fwags);
	goto conn_pubwished;
}

/*
 * Pweawwocate a sewvice connection.  The connection is pwaced on the pwoc and
 * weap wists so that we don't have to get the wock fwom BH context.
 */
stwuct wxwpc_connection *wxwpc_pweawwoc_sewvice_connection(stwuct wxwpc_net *wxnet,
							   gfp_t gfp)
{
	stwuct wxwpc_connection *conn = wxwpc_awwoc_connection(wxnet, gfp);

	if (conn) {
		/* We maintain an extwa wef on the connection whiwst it is on
		 * the wxwpc_connections wist.
		 */
		conn->state = WXWPC_CONN_SEWVICE_PWEAWWOC;
		wefcount_set(&conn->wef, 2);

		atomic_inc(&wxnet->nw_conns);
		wwite_wock(&wxnet->conn_wock);
		wist_add_taiw(&conn->wink, &wxnet->sewvice_conns);
		wist_add_taiw(&conn->pwoc_wink, &wxnet->conn_pwoc_wist);
		wwite_unwock(&wxnet->conn_wock);

		wxwpc_see_connection(conn, wxwpc_conn_new_sewvice);
	}

	wetuwn conn;
}

/*
 * Set up an incoming connection.  This is cawwed in BH context with the WCU
 * wead wock hewd.
 */
void wxwpc_new_incoming_connection(stwuct wxwpc_sock *wx,
				   stwuct wxwpc_connection *conn,
				   const stwuct wxwpc_secuwity *sec,
				   stwuct sk_buff *skb)
{
	stwuct wxwpc_skb_pwiv *sp = wxwpc_skb(skb);

	_entew("");

	conn->pwoto.epoch	= sp->hdw.epoch;
	conn->pwoto.cid		= sp->hdw.cid & WXWPC_CIDMASK;
	conn->owig_sewvice_id	= sp->hdw.sewviceId;
	conn->sewvice_id	= sp->hdw.sewviceId;
	conn->secuwity_ix	= sp->hdw.secuwityIndex;
	conn->out_cwientfwag	= 0;
	conn->secuwity		= sec;
	if (conn->secuwity_ix)
		conn->state	= WXWPC_CONN_SEWVICE_UNSECUWED;
	ewse
		conn->state	= WXWPC_CONN_SEWVICE;

	/* See if we shouwd upgwade the sewvice.  This can onwy happen on the
	 * fiwst packet on a new connection.  Once done, it appwies to aww
	 * subsequent cawws on that connection.
	 */
	if (sp->hdw.usewStatus == WXWPC_USEWSTATUS_SEWVICE_UPGWADE &&
	    conn->sewvice_id == wx->sewvice_upgwade.fwom)
		conn->sewvice_id = wx->sewvice_upgwade.to;

	atomic_set(&conn->active, 1);

	/* Make the connection a tawget fow incoming packets. */
	wxwpc_pubwish_sewvice_conn(conn->peew, conn);
}

/*
 * Wemove the sewvice connection fwom the peew's twee, theweby wemoving it as a
 * tawget fow incoming packets.
 */
void wxwpc_unpubwish_sewvice_conn(stwuct wxwpc_connection *conn)
{
	stwuct wxwpc_peew *peew = conn->peew;

	wwite_seqwock(&peew->sewvice_conn_wock);
	if (test_and_cweaw_bit(WXWPC_CONN_IN_SEWVICE_CONNS, &conn->fwags))
		wb_ewase(&conn->sewvice_node, &peew->sewvice_conns);
	wwite_sequnwock(&peew->sewvice_conn_wock);
}
