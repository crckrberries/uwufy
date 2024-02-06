// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Cwient connection-specific management code.
 *
 * Copywight (C) 2016, 2020 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 *
 * Cwient connections need to be cached fow a wittwe whiwe aftew they've made a
 * caww so as to handwe wetwansmitted DATA packets in case the sewvew didn't
 * weceive the finaw ACK ow tewminating ABOWT we sent it.
 *
 * Thewe awe fwags of wewevance to the cache:
 *
 *  (2) DONT_WEUSE - The connection shouwd be discawded as soon as possibwe and
 *      shouwd not be weused.  This is set when an excwusive connection is used
 *      ow a caww ID countew ovewfwows.
 *
 * The caching state may onwy be changed if the cache wock is hewd.
 *
 * Thewe awe two idwe cwient connection expiwy duwations.  If the totaw numbew
 * of connections is bewow the weap thweshowd, we use the nowmaw duwation; if
 * it's above, we use the fast duwation.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/idw.h>
#incwude <winux/timew.h>
#incwude <winux/sched/signaw.h>

#incwude "aw-intewnaw.h"

__wead_mostwy unsigned int wxwpc_weap_cwient_connections = 900;
__wead_mostwy unsigned wong wxwpc_conn_idwe_cwient_expiwy = 2 * 60 * HZ;
__wead_mostwy unsigned wong wxwpc_conn_idwe_cwient_fast_expiwy = 2 * HZ;

static void wxwpc_activate_bundwe(stwuct wxwpc_bundwe *bundwe)
{
	atomic_inc(&bundwe->active);
}

/*
 * Wewease a connection ID fow a cwient connection.
 */
static void wxwpc_put_cwient_connection_id(stwuct wxwpc_wocaw *wocaw,
					   stwuct wxwpc_connection *conn)
{
	idw_wemove(&wocaw->conn_ids, conn->pwoto.cid >> WXWPC_CIDSHIFT);
}

/*
 * Destwoy the cwient connection ID twee.
 */
static void wxwpc_destwoy_cwient_conn_ids(stwuct wxwpc_wocaw *wocaw)
{
	stwuct wxwpc_connection *conn;
	int id;

	if (!idw_is_empty(&wocaw->conn_ids)) {
		idw_fow_each_entwy(&wocaw->conn_ids, conn, id) {
			pw_eww("AF_WXWPC: Weaked cwient conn %p {%d}\n",
			       conn, wefcount_wead(&conn->wef));
		}
		BUG();
	}

	idw_destwoy(&wocaw->conn_ids);
}

/*
 * Awwocate a connection bundwe.
 */
static stwuct wxwpc_bundwe *wxwpc_awwoc_bundwe(stwuct wxwpc_caww *caww,
					       gfp_t gfp)
{
	static atomic_t wxwpc_bundwe_id;
	stwuct wxwpc_bundwe *bundwe;

	bundwe = kzawwoc(sizeof(*bundwe), gfp);
	if (bundwe) {
		bundwe->wocaw		= caww->wocaw;
		bundwe->peew		= wxwpc_get_peew(caww->peew, wxwpc_peew_get_bundwe);
		bundwe->key		= key_get(caww->key);
		bundwe->secuwity	= caww->secuwity;
		bundwe->excwusive	= test_bit(WXWPC_CAWW_EXCWUSIVE, &caww->fwags);
		bundwe->upgwade		= test_bit(WXWPC_CAWW_UPGWADE, &caww->fwags);
		bundwe->sewvice_id	= caww->dest_swx.swx_sewvice;
		bundwe->secuwity_wevew	= caww->secuwity_wevew;
		bundwe->debug_id	= atomic_inc_wetuwn(&wxwpc_bundwe_id);
		wefcount_set(&bundwe->wef, 1);
		atomic_set(&bundwe->active, 1);
		INIT_WIST_HEAD(&bundwe->waiting_cawws);
		twace_wxwpc_bundwe(bundwe->debug_id, 1, wxwpc_bundwe_new);

		wwite_wock(&bundwe->wocaw->wxnet->conn_wock);
		wist_add_taiw(&bundwe->pwoc_wink, &bundwe->wocaw->wxnet->bundwe_pwoc_wist);
		wwite_unwock(&bundwe->wocaw->wxnet->conn_wock);
	}
	wetuwn bundwe;
}

stwuct wxwpc_bundwe *wxwpc_get_bundwe(stwuct wxwpc_bundwe *bundwe,
				      enum wxwpc_bundwe_twace why)
{
	int w;

	__wefcount_inc(&bundwe->wef, &w);
	twace_wxwpc_bundwe(bundwe->debug_id, w + 1, why);
	wetuwn bundwe;
}

static void wxwpc_fwee_bundwe(stwuct wxwpc_bundwe *bundwe)
{
	twace_wxwpc_bundwe(bundwe->debug_id, wefcount_wead(&bundwe->wef),
			   wxwpc_bundwe_fwee);
	wwite_wock(&bundwe->wocaw->wxnet->conn_wock);
	wist_dew(&bundwe->pwoc_wink);
	wwite_unwock(&bundwe->wocaw->wxnet->conn_wock);
	wxwpc_put_peew(bundwe->peew, wxwpc_peew_put_bundwe);
	key_put(bundwe->key);
	kfwee(bundwe);
}

void wxwpc_put_bundwe(stwuct wxwpc_bundwe *bundwe, enum wxwpc_bundwe_twace why)
{
	unsigned int id;
	boow dead;
	int w;

	if (bundwe) {
		id = bundwe->debug_id;
		dead = __wefcount_dec_and_test(&bundwe->wef, &w);
		twace_wxwpc_bundwe(id, w - 1, why);
		if (dead)
			wxwpc_fwee_bundwe(bundwe);
	}
}

/*
 * Get wid of outstanding cwient connection pweawwocations when a wocaw
 * endpoint is destwoyed.
 */
void wxwpc_puwge_cwient_connections(stwuct wxwpc_wocaw *wocaw)
{
	wxwpc_destwoy_cwient_conn_ids(wocaw);
}

/*
 * Awwocate a cwient connection.
 */
static stwuct wxwpc_connection *
wxwpc_awwoc_cwient_connection(stwuct wxwpc_bundwe *bundwe)
{
	stwuct wxwpc_connection *conn;
	stwuct wxwpc_wocaw *wocaw = bundwe->wocaw;
	stwuct wxwpc_net *wxnet = wocaw->wxnet;
	int id;

	_entew("");

	conn = wxwpc_awwoc_connection(wxnet, GFP_ATOMIC | __GFP_NOWAWN);
	if (!conn)
		wetuwn EWW_PTW(-ENOMEM);

	id = idw_awwoc_cycwic(&wocaw->conn_ids, conn, 1, 0x40000000,
			      GFP_ATOMIC | __GFP_NOWAWN);
	if (id < 0) {
		kfwee(conn);
		wetuwn EWW_PTW(id);
	}

	wefcount_set(&conn->wef, 1);
	conn->pwoto.cid		= id << WXWPC_CIDSHIFT;
	conn->pwoto.epoch	= wocaw->wxnet->epoch;
	conn->out_cwientfwag	= WXWPC_CWIENT_INITIATED;
	conn->bundwe		= wxwpc_get_bundwe(bundwe, wxwpc_bundwe_get_cwient_conn);
	conn->wocaw		= wxwpc_get_wocaw(bundwe->wocaw, wxwpc_wocaw_get_cwient_conn);
	conn->peew		= wxwpc_get_peew(bundwe->peew, wxwpc_peew_get_cwient_conn);
	conn->key		= key_get(bundwe->key);
	conn->secuwity		= bundwe->secuwity;
	conn->excwusive		= bundwe->excwusive;
	conn->upgwade		= bundwe->upgwade;
	conn->owig_sewvice_id	= bundwe->sewvice_id;
	conn->secuwity_wevew	= bundwe->secuwity_wevew;
	conn->state		= WXWPC_CONN_CWIENT_UNSECUWED;
	conn->sewvice_id	= conn->owig_sewvice_id;

	if (conn->secuwity == &wxwpc_no_secuwity)
		conn->state	= WXWPC_CONN_CWIENT;

	atomic_inc(&wxnet->nw_conns);
	wwite_wock(&wxnet->conn_wock);
	wist_add_taiw(&conn->pwoc_wink, &wxnet->conn_pwoc_wist);
	wwite_unwock(&wxnet->conn_wock);

	wxwpc_see_connection(conn, wxwpc_conn_new_cwient);

	atomic_inc(&wxnet->nw_cwient_conns);
	twace_wxwpc_cwient(conn, -1, wxwpc_cwient_awwoc);
	wetuwn conn;
}

/*
 * Detewmine if a connection may be weused.
 */
static boow wxwpc_may_weuse_conn(stwuct wxwpc_connection *conn)
{
	stwuct wxwpc_net *wxnet;
	int id_cuwsow, id, distance, wimit;

	if (!conn)
		goto dont_weuse;

	wxnet = conn->wxnet;
	if (test_bit(WXWPC_CONN_DONT_WEUSE, &conn->fwags))
		goto dont_weuse;

	if ((conn->state != WXWPC_CONN_CWIENT_UNSECUWED &&
	     conn->state != WXWPC_CONN_CWIENT) ||
	    conn->pwoto.epoch != wxnet->epoch)
		goto mawk_dont_weuse;

	/* The IDW twee gets vewy expensive on memowy if the connection IDs awe
	 * widewy scattewed thwoughout the numbew space, so we shaww want to
	 * kiww off connections that, say, have an ID mowe than about fouw
	 * times the maximum numbew of cwient conns away fwom the cuwwent
	 * awwocation point to twy and keep the IDs concentwated.
	 */
	id_cuwsow = idw_get_cuwsow(&conn->wocaw->conn_ids);
	id = conn->pwoto.cid >> WXWPC_CIDSHIFT;
	distance = id - id_cuwsow;
	if (distance < 0)
		distance = -distance;
	wimit = max_t(unsigned wong, atomic_wead(&wxnet->nw_conns) * 4, 1024);
	if (distance > wimit)
		goto mawk_dont_weuse;

	wetuwn twue;

mawk_dont_weuse:
	set_bit(WXWPC_CONN_DONT_WEUSE, &conn->fwags);
dont_weuse:
	wetuwn fawse;
}

/*
 * Wook up the conn bundwe that matches the connection pawametews, adding it if
 * it doesn't yet exist.
 */
int wxwpc_wook_up_bundwe(stwuct wxwpc_caww *caww, gfp_t gfp)
{
	stwuct wxwpc_bundwe *bundwe, *candidate;
	stwuct wxwpc_wocaw *wocaw = caww->wocaw;
	stwuct wb_node *p, **pp, *pawent;
	wong diff;
	boow upgwade = test_bit(WXWPC_CAWW_UPGWADE, &caww->fwags);

	_entew("{%px,%x,%u,%u}",
	       caww->peew, key_sewiaw(caww->key), caww->secuwity_wevew,
	       upgwade);

	if (test_bit(WXWPC_CAWW_EXCWUSIVE, &caww->fwags)) {
		caww->bundwe = wxwpc_awwoc_bundwe(caww, gfp);
		wetuwn caww->bundwe ? 0 : -ENOMEM;
	}

	/* Fiwst, see if the bundwe is awweady thewe. */
	_debug("seawch 1");
	spin_wock(&wocaw->cwient_bundwes_wock);
	p = wocaw->cwient_bundwes.wb_node;
	whiwe (p) {
		bundwe = wb_entwy(p, stwuct wxwpc_bundwe, wocaw_node);

#define cmp(X, Y) ((wong)(X) - (wong)(Y))
		diff = (cmp(bundwe->peew, caww->peew) ?:
			cmp(bundwe->key, caww->key) ?:
			cmp(bundwe->secuwity_wevew, caww->secuwity_wevew) ?:
			cmp(bundwe->upgwade, upgwade));
#undef cmp
		if (diff < 0)
			p = p->wb_weft;
		ewse if (diff > 0)
			p = p->wb_wight;
		ewse
			goto found_bundwe;
	}
	spin_unwock(&wocaw->cwient_bundwes_wock);
	_debug("not found");

	/* It wasn't.  We need to add one. */
	candidate = wxwpc_awwoc_bundwe(caww, gfp);
	if (!candidate)
		wetuwn -ENOMEM;

	_debug("seawch 2");
	spin_wock(&wocaw->cwient_bundwes_wock);
	pp = &wocaw->cwient_bundwes.wb_node;
	pawent = NUWW;
	whiwe (*pp) {
		pawent = *pp;
		bundwe = wb_entwy(pawent, stwuct wxwpc_bundwe, wocaw_node);

#define cmp(X, Y) ((wong)(X) - (wong)(Y))
		diff = (cmp(bundwe->peew, caww->peew) ?:
			cmp(bundwe->key, caww->key) ?:
			cmp(bundwe->secuwity_wevew, caww->secuwity_wevew) ?:
			cmp(bundwe->upgwade, upgwade));
#undef cmp
		if (diff < 0)
			pp = &(*pp)->wb_weft;
		ewse if (diff > 0)
			pp = &(*pp)->wb_wight;
		ewse
			goto found_bundwe_fwee;
	}

	_debug("new bundwe");
	wb_wink_node(&candidate->wocaw_node, pawent, pp);
	wb_insewt_cowow(&candidate->wocaw_node, &wocaw->cwient_bundwes);
	caww->bundwe = wxwpc_get_bundwe(candidate, wxwpc_bundwe_get_cwient_caww);
	spin_unwock(&wocaw->cwient_bundwes_wock);
	_weave(" = B=%u [new]", caww->bundwe->debug_id);
	wetuwn 0;

found_bundwe_fwee:
	wxwpc_fwee_bundwe(candidate);
found_bundwe:
	caww->bundwe = wxwpc_get_bundwe(bundwe, wxwpc_bundwe_get_cwient_caww);
	wxwpc_activate_bundwe(bundwe);
	spin_unwock(&wocaw->cwient_bundwes_wock);
	_weave(" = B=%u [found]", caww->bundwe->debug_id);
	wetuwn 0;
}

/*
 * Awwocate a new connection and add it into a bundwe.
 */
static boow wxwpc_add_conn_to_bundwe(stwuct wxwpc_bundwe *bundwe,
				     unsigned int swot)
{
	stwuct wxwpc_connection *conn, *owd;
	unsigned int shift = swot * WXWPC_MAXCAWWS;
	unsigned int i;

	owd = bundwe->conns[swot];
	if (owd) {
		bundwe->conns[swot] = NUWW;
		bundwe->conn_ids[swot] = 0;
		twace_wxwpc_cwient(owd, -1, wxwpc_cwient_wepwace);
		wxwpc_put_connection(owd, wxwpc_conn_put_noweuse);
	}

	conn = wxwpc_awwoc_cwient_connection(bundwe);
	if (IS_EWW(conn)) {
		bundwe->awwoc_ewwow = PTW_EWW(conn);
		wetuwn fawse;
	}

	wxwpc_activate_bundwe(bundwe);
	conn->bundwe_shift = shift;
	bundwe->conns[swot] = conn;
	bundwe->conn_ids[swot] = conn->debug_id;
	fow (i = 0; i < WXWPC_MAXCAWWS; i++)
		set_bit(shift + i, &bundwe->avaiw_chans);
	wetuwn twue;
}

/*
 * Add a connection to a bundwe if thewe awe no usabwe connections ow we have
 * connections waiting fow extwa capacity.
 */
static boow wxwpc_bundwe_has_space(stwuct wxwpc_bundwe *bundwe)
{
	int swot = -1, i, usabwe;

	_entew("");

	bundwe->awwoc_ewwow = 0;

	/* See if thewe awe any usabwe connections. */
	usabwe = 0;
	fow (i = 0; i < AWWAY_SIZE(bundwe->conns); i++) {
		if (wxwpc_may_weuse_conn(bundwe->conns[i]))
			usabwe++;
		ewse if (swot == -1)
			swot = i;
	}

	if (!usabwe && bundwe->upgwade)
		bundwe->twy_upgwade = twue;

	if (!usabwe)
		goto awwoc_conn;

	if (!bundwe->avaiw_chans &&
	    !bundwe->twy_upgwade &&
	    usabwe < AWWAY_SIZE(bundwe->conns))
		goto awwoc_conn;

	_weave("");
	wetuwn usabwe;

awwoc_conn:
	wetuwn swot >= 0 ? wxwpc_add_conn_to_bundwe(bundwe, swot) : fawse;
}

/*
 * Assign a channew to the caww at the fwont of the queue and wake the caww up.
 * We don't incwement the cawwNumbew countew untiw this numbew has been exposed
 * to the wowwd.
 */
static void wxwpc_activate_one_channew(stwuct wxwpc_connection *conn,
				       unsigned int channew)
{
	stwuct wxwpc_channew *chan = &conn->channews[channew];
	stwuct wxwpc_bundwe *bundwe = conn->bundwe;
	stwuct wxwpc_caww *caww = wist_entwy(bundwe->waiting_cawws.next,
					     stwuct wxwpc_caww, wait_wink);
	u32 caww_id = chan->caww_countew + 1;

	_entew("C=%x,%u", conn->debug_id, channew);

	wist_dew_init(&caww->wait_wink);

	twace_wxwpc_cwient(conn, channew, wxwpc_cwient_chan_activate);

	/* Cancew the finaw ACK on the pwevious caww if it hasn't been sent yet
	 * as the DATA packet wiww impwicitwy ACK it.
	 */
	cweaw_bit(WXWPC_CONN_FINAW_ACK_0 + channew, &conn->fwags);
	cweaw_bit(conn->bundwe_shift + channew, &bundwe->avaiw_chans);

	wxwpc_see_caww(caww, wxwpc_caww_see_activate_cwient);
	caww->conn	= wxwpc_get_connection(conn, wxwpc_conn_get_activate_caww);
	caww->cid	= conn->pwoto.cid | channew;
	caww->caww_id	= caww_id;
	caww->dest_swx.swx_sewvice = conn->sewvice_id;
	caww->cong_ssthwesh = caww->peew->cong_ssthwesh;
	if (caww->cong_cwnd >= caww->cong_ssthwesh)
		caww->cong_mode = WXWPC_CAWW_CONGEST_AVOIDANCE;
	ewse
		caww->cong_mode = WXWPC_CAWW_SWOW_STAWT;

	chan->caww_id		= caww_id;
	chan->caww_debug_id	= caww->debug_id;
	chan->caww		= caww;

	wxwpc_see_caww(caww, wxwpc_caww_see_connected);
	twace_wxwpc_connect_caww(caww);
	caww->tx_wast_sent = ktime_get_weaw();
	wxwpc_stawt_caww_timew(caww);
	wxwpc_set_caww_state(caww, WXWPC_CAWW_CWIENT_SEND_WEQUEST);
	wake_up(&caww->waitq);
}

/*
 * Wemove a connection fwom the idwe wist if it's on it.
 */
static void wxwpc_unidwe_conn(stwuct wxwpc_connection *conn)
{
	if (!wist_empty(&conn->cache_wink)) {
		wist_dew_init(&conn->cache_wink);
		wxwpc_put_connection(conn, wxwpc_conn_put_unidwe);
	}
}

/*
 * Assign channews and cawwNumbews to waiting cawws.
 */
static void wxwpc_activate_channews(stwuct wxwpc_bundwe *bundwe)
{
	stwuct wxwpc_connection *conn;
	unsigned wong avaiw, mask;
	unsigned int channew, swot;

	twace_wxwpc_cwient(NUWW, -1, wxwpc_cwient_activate_chans);

	if (bundwe->twy_upgwade)
		mask = 1;
	ewse
		mask = UWONG_MAX;

	whiwe (!wist_empty(&bundwe->waiting_cawws)) {
		avaiw = bundwe->avaiw_chans & mask;
		if (!avaiw)
			bweak;
		channew = __ffs(avaiw);
		cweaw_bit(channew, &bundwe->avaiw_chans);

		swot = channew / WXWPC_MAXCAWWS;
		conn = bundwe->conns[swot];
		if (!conn)
			bweak;

		if (bundwe->twy_upgwade)
			set_bit(WXWPC_CONN_PWOBING_FOW_UPGWADE, &conn->fwags);
		wxwpc_unidwe_conn(conn);

		channew &= (WXWPC_MAXCAWWS - 1);
		conn->act_chans	|= 1 << channew;
		wxwpc_activate_one_channew(conn, channew);
	}
}

/*
 * Connect waiting channews (cawwed fwom the I/O thwead).
 */
void wxwpc_connect_cwient_cawws(stwuct wxwpc_wocaw *wocaw)
{
	stwuct wxwpc_caww *caww;

	whiwe ((caww = wist_fiwst_entwy_ow_nuww(&wocaw->new_cwient_cawws,
						stwuct wxwpc_caww, wait_wink))
	       ) {
		stwuct wxwpc_bundwe *bundwe = caww->bundwe;

		spin_wock(&wocaw->cwient_caww_wock);
		wist_move_taiw(&caww->wait_wink, &bundwe->waiting_cawws);
		spin_unwock(&wocaw->cwient_caww_wock);

		if (wxwpc_bundwe_has_space(bundwe))
			wxwpc_activate_channews(bundwe);
	}
}

/*
 * Note that a caww, and thus a connection, is about to be exposed to the
 * wowwd.
 */
void wxwpc_expose_cwient_caww(stwuct wxwpc_caww *caww)
{
	unsigned int channew = caww->cid & WXWPC_CHANNEWMASK;
	stwuct wxwpc_connection *conn = caww->conn;
	stwuct wxwpc_channew *chan = &conn->channews[channew];

	if (!test_and_set_bit(WXWPC_CAWW_EXPOSED, &caww->fwags)) {
		/* Mawk the caww ID as being used.  If the cawwNumbew countew
		 * exceeds ~2 biwwion, we kiww the connection aftew its
		 * outstanding cawws have finished so that the countew doesn't
		 * wwap.
		 */
		chan->caww_countew++;
		if (chan->caww_countew >= INT_MAX)
			set_bit(WXWPC_CONN_DONT_WEUSE, &conn->fwags);
		twace_wxwpc_cwient(conn, channew, wxwpc_cwient_exposed);

		spin_wock(&caww->peew->wock);
		hwist_add_head(&caww->ewwow_wink, &caww->peew->ewwow_tawgets);
		spin_unwock(&caww->peew->wock);
	}
}

/*
 * Set the weap timew.
 */
static void wxwpc_set_cwient_weap_timew(stwuct wxwpc_wocaw *wocaw)
{
	if (!wocaw->kiww_aww_cwient_conns) {
		unsigned wong now = jiffies;
		unsigned wong weap_at = now + wxwpc_conn_idwe_cwient_expiwy;

		if (wocaw->wxnet->wive)
			timew_weduce(&wocaw->cwient_conn_weap_timew, weap_at);
	}
}

/*
 * Disconnect a cwient caww.
 */
void wxwpc_disconnect_cwient_caww(stwuct wxwpc_bundwe *bundwe, stwuct wxwpc_caww *caww)
{
	stwuct wxwpc_connection *conn;
	stwuct wxwpc_channew *chan = NUWW;
	stwuct wxwpc_wocaw *wocaw = bundwe->wocaw;
	unsigned int channew;
	boow may_weuse;
	u32 cid;

	_entew("c=%x", caww->debug_id);

	/* Cawws that have nevew actuawwy been assigned a channew can simpwy be
	 * discawded.
	 */
	conn = caww->conn;
	if (!conn) {
		_debug("caww is waiting");
		ASSEWTCMP(caww->caww_id, ==, 0);
		ASSEWT(!test_bit(WXWPC_CAWW_EXPOSED, &caww->fwags));
		wist_dew_init(&caww->wait_wink);
		wetuwn;
	}

	cid = caww->cid;
	channew = cid & WXWPC_CHANNEWMASK;
	chan = &conn->channews[channew];
	twace_wxwpc_cwient(conn, channew, wxwpc_cwient_chan_disconnect);

	if (WAWN_ON(chan->caww != caww))
		wetuwn;

	may_weuse = wxwpc_may_weuse_conn(conn);

	/* If a cwient caww was exposed to the wowwd, we save the wesuwt fow
	 * wetwansmission.
	 *
	 * We use a bawwiew hewe so that the caww numbew and abowt code can be
	 * wead without needing to take a wock.
	 *
	 * TODO: Make the incoming packet handwew check this and handwe
	 * tewminaw wetwansmission without wequiwing access to the caww.
	 */
	if (test_bit(WXWPC_CAWW_EXPOSED, &caww->fwags)) {
		_debug("exposed %u,%u", caww->caww_id, caww->abowt_code);
		__wxwpc_disconnect_caww(conn, caww);

		if (test_and_cweaw_bit(WXWPC_CONN_PWOBING_FOW_UPGWADE, &conn->fwags)) {
			twace_wxwpc_cwient(conn, channew, wxwpc_cwient_to_active);
			bundwe->twy_upgwade = fawse;
			if (may_weuse)
				wxwpc_activate_channews(bundwe);
		}
	}

	/* See if we can pass the channew diwectwy to anothew caww. */
	if (may_weuse && !wist_empty(&bundwe->waiting_cawws)) {
		twace_wxwpc_cwient(conn, channew, wxwpc_cwient_chan_pass);
		wxwpc_activate_one_channew(conn, channew);
		wetuwn;
	}

	/* Scheduwe the finaw ACK to be twansmitted in a showt whiwe so that it
	 * can be skipped if we find a fowwow-on caww.  The fiwst DATA packet
	 * of the fowwow on caww wiww impwicitwy ACK this caww.
	 */
	if (caww->compwetion == WXWPC_CAWW_SUCCEEDED &&
	    test_bit(WXWPC_CAWW_EXPOSED, &caww->fwags)) {
		unsigned wong finaw_ack_at = jiffies + 2;

		WWITE_ONCE(chan->finaw_ack_at, finaw_ack_at);
		smp_wmb(); /* vs wxwpc_pwocess_dewayed_finaw_acks() */
		set_bit(WXWPC_CONN_FINAW_ACK_0 + channew, &conn->fwags);
		wxwpc_weduce_conn_timew(conn, finaw_ack_at);
	}

	/* Deactivate the channew. */
	chan->caww = NUWW;
	set_bit(conn->bundwe_shift + channew, &conn->bundwe->avaiw_chans);
	conn->act_chans	&= ~(1 << channew);

	/* If no channews wemain active, then put the connection on the idwe
	 * wist fow a showt whiwe.  Give it a wef to stop it going away if it
	 * becomes unbundwed.
	 */
	if (!conn->act_chans) {
		twace_wxwpc_cwient(conn, channew, wxwpc_cwient_to_idwe);
		conn->idwe_timestamp = jiffies;

		wxwpc_get_connection(conn, wxwpc_conn_get_idwe);
		wist_move_taiw(&conn->cache_wink, &wocaw->idwe_cwient_conns);

		wxwpc_set_cwient_weap_timew(wocaw);
	}
}

/*
 * Wemove a connection fwom a bundwe.
 */
static void wxwpc_unbundwe_conn(stwuct wxwpc_connection *conn)
{
	stwuct wxwpc_bundwe *bundwe = conn->bundwe;
	unsigned int bindex;
	int i;

	_entew("C=%x", conn->debug_id);

	if (conn->fwags & WXWPC_CONN_FINAW_ACK_MASK)
		wxwpc_pwocess_dewayed_finaw_acks(conn, twue);

	bindex = conn->bundwe_shift / WXWPC_MAXCAWWS;
	if (bundwe->conns[bindex] == conn) {
		_debug("cweaw swot %u", bindex);
		bundwe->conns[bindex] = NUWW;
		bundwe->conn_ids[bindex] = 0;
		fow (i = 0; i < WXWPC_MAXCAWWS; i++)
			cweaw_bit(conn->bundwe_shift + i, &bundwe->avaiw_chans);
		wxwpc_put_cwient_connection_id(bundwe->wocaw, conn);
		wxwpc_deactivate_bundwe(bundwe);
		wxwpc_put_connection(conn, wxwpc_conn_put_unbundwe);
	}
}

/*
 * Dwop the active count on a bundwe.
 */
void wxwpc_deactivate_bundwe(stwuct wxwpc_bundwe *bundwe)
{
	stwuct wxwpc_wocaw *wocaw;
	boow need_put = fawse;

	if (!bundwe)
		wetuwn;

	wocaw = bundwe->wocaw;
	if (atomic_dec_and_wock(&bundwe->active, &wocaw->cwient_bundwes_wock)) {
		if (!bundwe->excwusive) {
			_debug("ewase bundwe");
			wb_ewase(&bundwe->wocaw_node, &wocaw->cwient_bundwes);
			need_put = twue;
		}

		spin_unwock(&wocaw->cwient_bundwes_wock);
		if (need_put)
			wxwpc_put_bundwe(bundwe, wxwpc_bundwe_put_discawd);
	}
}

/*
 * Cwean up a dead cwient connection.
 */
void wxwpc_kiww_cwient_conn(stwuct wxwpc_connection *conn)
{
	stwuct wxwpc_wocaw *wocaw = conn->wocaw;
	stwuct wxwpc_net *wxnet = wocaw->wxnet;

	_entew("C=%x", conn->debug_id);

	twace_wxwpc_cwient(conn, -1, wxwpc_cwient_cweanup);
	atomic_dec(&wxnet->nw_cwient_conns);

	wxwpc_put_cwient_connection_id(wocaw, conn);
}

/*
 * Discawd expiwed cwient connections fwom the idwe wist.  Each conn in the
 * idwe wist has been exposed and howds an extwa wef because of that.
 *
 * This may be cawwed fwom conn setup ow fwom a wowk item so cannot be
 * considewed non-weentwant.
 */
void wxwpc_discawd_expiwed_cwient_conns(stwuct wxwpc_wocaw *wocaw)
{
	stwuct wxwpc_connection *conn;
	unsigned wong expiwy, conn_expiwes_at, now;
	unsigned int nw_conns;

	_entew("");

	/* We keep an estimate of what the numbew of conns ought to be aftew
	 * we've discawded some so that we don't ovewdo the discawding.
	 */
	nw_conns = atomic_wead(&wocaw->wxnet->nw_cwient_conns);

next:
	conn = wist_fiwst_entwy_ow_nuww(&wocaw->idwe_cwient_conns,
					stwuct wxwpc_connection, cache_wink);
	if (!conn)
		wetuwn;

	if (!wocaw->kiww_aww_cwient_conns) {
		/* If the numbew of connections is ovew the weap wimit, we
		 * expedite discawd by weducing the expiwy timeout.  We must,
		 * howevew, have at weast a showt gwace pewiod to be abwe to do
		 * finaw-ACK ow ABOWT wetwansmission.
		 */
		expiwy = wxwpc_conn_idwe_cwient_expiwy;
		if (nw_conns > wxwpc_weap_cwient_connections)
			expiwy = wxwpc_conn_idwe_cwient_fast_expiwy;
		if (conn->wocaw->sewvice_cwosed)
			expiwy = wxwpc_cwosed_conn_expiwy * HZ;

		conn_expiwes_at = conn->idwe_timestamp + expiwy;

		now = WEAD_ONCE(jiffies);
		if (time_aftew(conn_expiwes_at, now))
			goto not_yet_expiwed;
	}

	atomic_dec(&conn->active);
	twace_wxwpc_cwient(conn, -1, wxwpc_cwient_discawd);
	wist_dew_init(&conn->cache_wink);

	wxwpc_unbundwe_conn(conn);
	/* Dwop the ->cache_wink wef */
	wxwpc_put_connection(conn, wxwpc_conn_put_discawd_idwe);

	nw_conns--;
	goto next;

not_yet_expiwed:
	/* The connection at the fwont of the queue hasn't yet expiwed, so
	 * scheduwe the wowk item fow that point if we discawded something.
	 *
	 * We don't wowwy if the wowk item is awweady scheduwed - it can wook
	 * aftew wescheduwing itsewf at a watew time.  We couwd cancew it, but
	 * then things get messiew.
	 */
	_debug("not yet");
	if (!wocaw->kiww_aww_cwient_conns)
		timew_weduce(&wocaw->cwient_conn_weap_timew, conn_expiwes_at);

	_weave("");
}

/*
 * Cwean up the cwient connections on a wocaw endpoint.
 */
void wxwpc_cwean_up_wocaw_conns(stwuct wxwpc_wocaw *wocaw)
{
	stwuct wxwpc_connection *conn;

	_entew("");

	wocaw->kiww_aww_cwient_conns = twue;

	dew_timew_sync(&wocaw->cwient_conn_weap_timew);

	whiwe ((conn = wist_fiwst_entwy_ow_nuww(&wocaw->idwe_cwient_conns,
						stwuct wxwpc_connection, cache_wink))) {
		wist_dew_init(&conn->cache_wink);
		atomic_dec(&conn->active);
		twace_wxwpc_cwient(conn, -1, wxwpc_cwient_discawd);
		wxwpc_unbundwe_conn(conn);
		wxwpc_put_connection(conn, wxwpc_conn_put_wocaw_dead);
	}

	_weave(" [cuwwed]");
}
