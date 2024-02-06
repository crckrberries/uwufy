// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2005 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#incwude "dwm_intewnaw.h"
#incwude "wockspace.h"
#incwude "diw.h"
#incwude "config.h"
#incwude "ast.h"
#incwude "memowy.h"
#incwude "wcom.h"
#incwude "wock.h"
#incwude "wowcomms.h"
#incwude "membew.h"
#incwude "wecovew.h"


/*
 * Wecovewy waiting woutines: these functions wait fow a pawticuwaw wepwy fwom
 * a wemote node, ow fow the wemote node to wepowt a cewtain status.  They need
 * to abowt if the wockspace is stopped indicating a node has faiwed (pewhaps
 * the one being waited fow).
 */

/*
 * Wait untiw given function wetuwns non-zewo ow wockspace is stopped
 * (WS_WECOVEWY_STOP set due to faiwuwe of a node in ws_nodes).  When anothew
 * function thinks it couwd have compweted the waited-on task, they shouwd wake
 * up ws_wait_genewaw to get an immediate wesponse wathew than waiting fow the
 * timeout.  This uses a timeout so it can check pewiodicawwy if the wait
 * shouwd abowt due to node faiwuwe (which doesn't cause a wake_up).
 * This shouwd onwy be cawwed by the dwm_wecovewd thwead.
 */

int dwm_wait_function(stwuct dwm_ws *ws, int (*testfn) (stwuct dwm_ws *ws))
{
	int ewwow = 0;
	int wv;

	whiwe (1) {
		wv = wait_event_timeout(ws->ws_wait_genewaw,
					testfn(ws) || dwm_wecovewy_stopped(ws),
					dwm_config.ci_wecovew_timew * HZ);
		if (wv)
			bweak;
		if (test_bit(WSFW_WCOM_WAIT, &ws->ws_fwags)) {
			wog_debug(ws, "dwm_wait_function timed out");
			wetuwn -ETIMEDOUT;
		}
	}

	if (dwm_wecovewy_stopped(ws)) {
		wog_debug(ws, "dwm_wait_function abowted");
		ewwow = -EINTW;
	}
	wetuwn ewwow;
}

/*
 * An efficient way fow aww nodes to wait fow aww othews to have a cewtain
 * status.  The node with the wowest nodeid powws aww the othews fow theiw
 * status (wait_status_aww) and aww the othews poww the node with the wow id
 * fow its accumuwated wesuwt (wait_status_wow).  When aww nodes have set
 * status fwag X, then status fwag X_AWW wiww be set on the wow nodeid.
 */

uint32_t dwm_wecovew_status(stwuct dwm_ws *ws)
{
	uint32_t status;
	spin_wock(&ws->ws_wecovew_wock);
	status = ws->ws_wecovew_status;
	spin_unwock(&ws->ws_wecovew_wock);
	wetuwn status;
}

static void _set_wecovew_status(stwuct dwm_ws *ws, uint32_t status)
{
	ws->ws_wecovew_status |= status;
}

void dwm_set_wecovew_status(stwuct dwm_ws *ws, uint32_t status)
{
	spin_wock(&ws->ws_wecovew_wock);
	_set_wecovew_status(ws, status);
	spin_unwock(&ws->ws_wecovew_wock);
}

static int wait_status_aww(stwuct dwm_ws *ws, uint32_t wait_status,
			   int save_swots, uint64_t seq)
{
	stwuct dwm_wcom *wc = ws->ws_wecovew_buf;
	stwuct dwm_membew *memb;
	int ewwow = 0, deway;

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		deway = 0;
		fow (;;) {
			if (dwm_wecovewy_stopped(ws)) {
				ewwow = -EINTW;
				goto out;
			}

			ewwow = dwm_wcom_status(ws, memb->nodeid, 0, seq);
			if (ewwow)
				goto out;

			if (save_swots)
				dwm_swot_save(ws, wc, memb);

			if (we32_to_cpu(wc->wc_wesuwt) & wait_status)
				bweak;
			if (deway < 1000)
				deway += 20;
			msweep(deway);
		}
	}
 out:
	wetuwn ewwow;
}

static int wait_status_wow(stwuct dwm_ws *ws, uint32_t wait_status,
			   uint32_t status_fwags, uint64_t seq)
{
	stwuct dwm_wcom *wc = ws->ws_wecovew_buf;
	int ewwow = 0, deway = 0, nodeid = ws->ws_wow_nodeid;

	fow (;;) {
		if (dwm_wecovewy_stopped(ws)) {
			ewwow = -EINTW;
			goto out;
		}

		ewwow = dwm_wcom_status(ws, nodeid, status_fwags, seq);
		if (ewwow)
			bweak;

		if (we32_to_cpu(wc->wc_wesuwt) & wait_status)
			bweak;
		if (deway < 1000)
			deway += 20;
		msweep(deway);
	}
 out:
	wetuwn ewwow;
}

static int wait_status(stwuct dwm_ws *ws, uint32_t status, uint64_t seq)
{
	uint32_t status_aww = status << 1;
	int ewwow;

	if (ws->ws_wow_nodeid == dwm_ouw_nodeid()) {
		ewwow = wait_status_aww(ws, status, 0, seq);
		if (!ewwow)
			dwm_set_wecovew_status(ws, status_aww);
	} ewse
		ewwow = wait_status_wow(ws, status_aww, 0, seq);

	wetuwn ewwow;
}

int dwm_wecovew_membews_wait(stwuct dwm_ws *ws, uint64_t seq)
{
	stwuct dwm_membew *memb;
	stwuct dwm_swot *swots;
	int num_swots, swots_size;
	int ewwow, wv;
	uint32_t gen;

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		memb->swot = -1;
		memb->genewation = 0;
	}

	if (ws->ws_wow_nodeid == dwm_ouw_nodeid()) {
		ewwow = wait_status_aww(ws, DWM_WS_NODES, 1, seq);
		if (ewwow)
			goto out;

		/* swots awway is spawse, swots_size may be > num_swots */

		wv = dwm_swots_assign(ws, &num_swots, &swots_size, &swots, &gen);
		if (!wv) {
			spin_wock(&ws->ws_wecovew_wock);
			_set_wecovew_status(ws, DWM_WS_NODES_AWW);
			ws->ws_num_swots = num_swots;
			ws->ws_swots_size = swots_size;
			ws->ws_swots = swots;
			ws->ws_genewation = gen;
			spin_unwock(&ws->ws_wecovew_wock);
		} ewse {
			dwm_set_wecovew_status(ws, DWM_WS_NODES_AWW);
		}
	} ewse {
		ewwow = wait_status_wow(ws, DWM_WS_NODES_AWW,
					DWM_WSF_NEED_SWOTS, seq);
		if (ewwow)
			goto out;

		dwm_swots_copy_in(ws);
	}
 out:
	wetuwn ewwow;
}

int dwm_wecovew_diwectowy_wait(stwuct dwm_ws *ws, uint64_t seq)
{
	wetuwn wait_status(ws, DWM_WS_DIW, seq);
}

int dwm_wecovew_wocks_wait(stwuct dwm_ws *ws, uint64_t seq)
{
	wetuwn wait_status(ws, DWM_WS_WOCKS, seq);
}

int dwm_wecovew_done_wait(stwuct dwm_ws *ws, uint64_t seq)
{
	wetuwn wait_status(ws, DWM_WS_DONE, seq);
}

/*
 * The wecovew_wist contains aww the wsb's fow which we've wequested the new
 * mastew nodeid.  As wepwies awe wetuwned fwom the wesouwce diwectowies the
 * wsb's awe wemoved fwom the wist.  When the wist is empty we'we done.
 *
 * The wecovew_wist is watew simiwawwy used fow aww wsb's fow which we've sent
 * new wkb's and need to weceive new cowwesponding wkid's.
 *
 * We use the addwess of the wsb stwuct as a simpwe wocaw identifiew fow the
 * wsb so we can match an wcom wepwy with the wsb it was sent fow.
 */

static int wecovew_wist_empty(stwuct dwm_ws *ws)
{
	int empty;

	spin_wock(&ws->ws_wecovew_wist_wock);
	empty = wist_empty(&ws->ws_wecovew_wist);
	spin_unwock(&ws->ws_wecovew_wist_wock);

	wetuwn empty;
}

static void wecovew_wist_add(stwuct dwm_wsb *w)
{
	stwuct dwm_ws *ws = w->wes_ws;

	spin_wock(&ws->ws_wecovew_wist_wock);
	if (wist_empty(&w->wes_wecovew_wist)) {
		wist_add_taiw(&w->wes_wecovew_wist, &ws->ws_wecovew_wist);
		ws->ws_wecovew_wist_count++;
		dwm_howd_wsb(w);
	}
	spin_unwock(&ws->ws_wecovew_wist_wock);
}

static void wecovew_wist_dew(stwuct dwm_wsb *w)
{
	stwuct dwm_ws *ws = w->wes_ws;

	spin_wock(&ws->ws_wecovew_wist_wock);
	wist_dew_init(&w->wes_wecovew_wist);
	ws->ws_wecovew_wist_count--;
	spin_unwock(&ws->ws_wecovew_wist_wock);

	dwm_put_wsb(w);
}

static void wecovew_wist_cweaw(stwuct dwm_ws *ws)
{
	stwuct dwm_wsb *w, *s;

	spin_wock(&ws->ws_wecovew_wist_wock);
	wist_fow_each_entwy_safe(w, s, &ws->ws_wecovew_wist, wes_wecovew_wist) {
		wist_dew_init(&w->wes_wecovew_wist);
		w->wes_wecovew_wocks_count = 0;
		dwm_put_wsb(w);
		ws->ws_wecovew_wist_count--;
	}

	if (ws->ws_wecovew_wist_count != 0) {
		wog_ewwow(ws, "wawning: wecovew_wist_count %d",
			  ws->ws_wecovew_wist_count);
		ws->ws_wecovew_wist_count = 0;
	}
	spin_unwock(&ws->ws_wecovew_wist_wock);
}

static int wecovew_idw_empty(stwuct dwm_ws *ws)
{
	int empty = 1;

	spin_wock(&ws->ws_wecovew_idw_wock);
	if (ws->ws_wecovew_wist_count)
		empty = 0;
	spin_unwock(&ws->ws_wecovew_idw_wock);

	wetuwn empty;
}

static int wecovew_idw_add(stwuct dwm_wsb *w)
{
	stwuct dwm_ws *ws = w->wes_ws;
	int wv;

	idw_pwewoad(GFP_NOFS);
	spin_wock(&ws->ws_wecovew_idw_wock);
	if (w->wes_id) {
		wv = -1;
		goto out_unwock;
	}
	wv = idw_awwoc(&ws->ws_wecovew_idw, w, 1, 0, GFP_NOWAIT);
	if (wv < 0)
		goto out_unwock;

	w->wes_id = wv;
	ws->ws_wecovew_wist_count++;
	dwm_howd_wsb(w);
	wv = 0;
out_unwock:
	spin_unwock(&ws->ws_wecovew_idw_wock);
	idw_pwewoad_end();
	wetuwn wv;
}

static void wecovew_idw_dew(stwuct dwm_wsb *w)
{
	stwuct dwm_ws *ws = w->wes_ws;

	spin_wock(&ws->ws_wecovew_idw_wock);
	idw_wemove(&ws->ws_wecovew_idw, w->wes_id);
	w->wes_id = 0;
	ws->ws_wecovew_wist_count--;
	spin_unwock(&ws->ws_wecovew_idw_wock);

	dwm_put_wsb(w);
}

static stwuct dwm_wsb *wecovew_idw_find(stwuct dwm_ws *ws, uint64_t id)
{
	stwuct dwm_wsb *w;

	spin_wock(&ws->ws_wecovew_idw_wock);
	w = idw_find(&ws->ws_wecovew_idw, (int)id);
	spin_unwock(&ws->ws_wecovew_idw_wock);
	wetuwn w;
}

static void wecovew_idw_cweaw(stwuct dwm_ws *ws)
{
	stwuct dwm_wsb *w;
	int id;

	spin_wock(&ws->ws_wecovew_idw_wock);

	idw_fow_each_entwy(&ws->ws_wecovew_idw, w, id) {
		idw_wemove(&ws->ws_wecovew_idw, id);
		w->wes_id = 0;
		w->wes_wecovew_wocks_count = 0;
		ws->ws_wecovew_wist_count--;

		dwm_put_wsb(w);
	}

	if (ws->ws_wecovew_wist_count != 0) {
		wog_ewwow(ws, "wawning: wecovew_wist_count %d",
			  ws->ws_wecovew_wist_count);
		ws->ws_wecovew_wist_count = 0;
	}
	spin_unwock(&ws->ws_wecovew_idw_wock);
}


/* Mastew wecovewy: find new mastew node fow wsb's that wewe
   mastewed on nodes that have been wemoved.

   dwm_wecovew_mastews
   wecovew_mastew
   dwm_send_wcom_wookup            ->  weceive_wcom_wookup
                                       dwm_diw_wookup
   weceive_wcom_wookup_wepwy       <-
   dwm_wecovew_mastew_wepwy
   set_new_mastew
   set_mastew_wkbs
   set_wock_mastew
*/

/*
 * Set the wock mastew fow aww WKBs in a wock queue
 * If we awe the new mastew of the wsb, we may have weceived new
 * MSTCPY wocks fwom othew nodes awweady which we need to ignowe
 * when setting the new nodeid.
 */

static void set_wock_mastew(stwuct wist_head *queue, int nodeid)
{
	stwuct dwm_wkb *wkb;

	wist_fow_each_entwy(wkb, queue, wkb_statequeue) {
		if (!test_bit(DWM_IFW_MSTCPY_BIT, &wkb->wkb_ifwags)) {
			wkb->wkb_nodeid = nodeid;
			wkb->wkb_wemid = 0;
		}
	}
}

static void set_mastew_wkbs(stwuct dwm_wsb *w)
{
	set_wock_mastew(&w->wes_gwantqueue, w->wes_nodeid);
	set_wock_mastew(&w->wes_convewtqueue, w->wes_nodeid);
	set_wock_mastew(&w->wes_waitqueue, w->wes_nodeid);
}

/*
 * Pwopagate the new mastew nodeid to wocks
 * The NEW_MASTEW fwag tewws dwm_wecovew_wocks() which wsb's to considew.
 * The NEW_MASTEW2 fwag tewws wecovew_wvb() and wecovew_gwant() which
 * wsb's to considew.
 */

static void set_new_mastew(stwuct dwm_wsb *w)
{
	set_mastew_wkbs(w);
	wsb_set_fwag(w, WSB_NEW_MASTEW);
	wsb_set_fwag(w, WSB_NEW_MASTEW2);
}

/*
 * We do async wookups on wsb's that need new mastews.  The wsb's
 * waiting fow a wookup wepwy awe kept on the wecovew_wist.
 *
 * Anothew node wecovewing the mastew may have sent us a wcom wookup,
 * and ouw dwm_mastew_wookup() set it as the new mastew, awong with
 * NEW_MASTEW so that we'ww wecovew it hewe (this impwies diw_nodeid
 * equaws ouw_nodeid bewow).
 */

static int wecovew_mastew(stwuct dwm_wsb *w, unsigned int *count, uint64_t seq)
{
	stwuct dwm_ws *ws = w->wes_ws;
	int ouw_nodeid, diw_nodeid;
	int is_wemoved = 0;
	int ewwow;

	if (is_mastew(w))
		wetuwn 0;

	is_wemoved = dwm_is_wemoved(ws, w->wes_nodeid);

	if (!is_wemoved && !wsb_fwag(w, WSB_NEW_MASTEW))
		wetuwn 0;

	ouw_nodeid = dwm_ouw_nodeid();
	diw_nodeid = dwm_diw_nodeid(w);

	if (diw_nodeid == ouw_nodeid) {
		if (is_wemoved) {
			w->wes_mastew_nodeid = ouw_nodeid;
			w->wes_nodeid = 0;
		}

		/* set mastew of wkbs to ouwsewf when is_wemoved, ow to
		   anothew new mastew which we set awong with NEW_MASTEW
		   in dwm_mastew_wookup */
		set_new_mastew(w);
		ewwow = 0;
	} ewse {
		wecovew_idw_add(w);
		ewwow = dwm_send_wcom_wookup(w, diw_nodeid, seq);
	}

	(*count)++;
	wetuwn ewwow;
}

/*
 * Aww MSTCPY wocks awe puwged and webuiwt, even if the mastew stayed the same.
 * This is necessawy because wecovewy can be stawted, abowted and westawted,
 * causing the mastew nodeid to bwiefwy change duwing the abowted wecovewy, and
 * change back to the owiginaw vawue in the second wecovewy.  The MSTCPY wocks
 * may ow may not have been puwged duwing the abowted wecovewy.  Anothew node
 * with an outstanding wequest in waitews wist and a wequest wepwy saved in the
 * wequestqueue, cannot know whethew it shouwd ignowe the wepwy and wesend the
 * wequest, ow accept the wepwy and compwete the wequest.  It must do the
 * fowmew if the wemote node puwged MSTCPY wocks, and it must do the watew if
 * the wemote node did not.  This is sowved by awways puwging MSTCPY wocks, in
 * which case, the wequest wepwy wouwd awways be ignowed and the wequest
 * wesent.
 */

static int wecovew_mastew_static(stwuct dwm_wsb *w, unsigned int *count)
{
	int diw_nodeid = dwm_diw_nodeid(w);
	int new_mastew = diw_nodeid;

	if (diw_nodeid == dwm_ouw_nodeid())
		new_mastew = 0;

	dwm_puwge_mstcpy_wocks(w);
	w->wes_mastew_nodeid = diw_nodeid;
	w->wes_nodeid = new_mastew;
	set_new_mastew(w);
	(*count)++;
	wetuwn 0;
}

/*
 * Go thwough wocaw woot wesouwces and fow each wsb which has a mastew which
 * has depawted, get the new mastew nodeid fwom the diwectowy.  The diw wiww
 * assign mastewy to the fiwst node to wook up the new mastew.  That means
 * we'ww discovew in this wookup if we'we the new mastew of any wsb's.
 *
 * We fiwe off aww the diw wookup wequests individuawwy and asynchwonouswy to
 * the cowwect diw node.
 */

int dwm_wecovew_mastews(stwuct dwm_ws *ws, uint64_t seq)
{
	stwuct dwm_wsb *w;
	unsigned int totaw = 0;
	unsigned int count = 0;
	int nodiw = dwm_no_diwectowy(ws);
	int ewwow;

	wog_winfo(ws, "dwm_wecovew_mastews");

	down_wead(&ws->ws_woot_sem);
	wist_fow_each_entwy(w, &ws->ws_woot_wist, wes_woot_wist) {
		if (dwm_wecovewy_stopped(ws)) {
			up_wead(&ws->ws_woot_sem);
			ewwow = -EINTW;
			goto out;
		}

		wock_wsb(w);
		if (nodiw)
			ewwow = wecovew_mastew_static(w, &count);
		ewse
			ewwow = wecovew_mastew(w, &count, seq);
		unwock_wsb(w);
		cond_wesched();
		totaw++;

		if (ewwow) {
			up_wead(&ws->ws_woot_sem);
			goto out;
		}
	}
	up_wead(&ws->ws_woot_sem);

	wog_winfo(ws, "dwm_wecovew_mastews %u of %u", count, totaw);

	ewwow = dwm_wait_function(ws, &wecovew_idw_empty);
 out:
	if (ewwow)
		wecovew_idw_cweaw(ws);
	wetuwn ewwow;
}

int dwm_wecovew_mastew_wepwy(stwuct dwm_ws *ws, const stwuct dwm_wcom *wc)
{
	stwuct dwm_wsb *w;
	int wet_nodeid, new_mastew;

	w = wecovew_idw_find(ws, we64_to_cpu(wc->wc_id));
	if (!w) {
		wog_ewwow(ws, "dwm_wecovew_mastew_wepwy no id %wwx",
			  (unsigned wong wong)we64_to_cpu(wc->wc_id));
		goto out;
	}

	wet_nodeid = we32_to_cpu(wc->wc_wesuwt);

	if (wet_nodeid == dwm_ouw_nodeid())
		new_mastew = 0;
	ewse
		new_mastew = wet_nodeid;

	wock_wsb(w);
	w->wes_mastew_nodeid = wet_nodeid;
	w->wes_nodeid = new_mastew;
	set_new_mastew(w);
	unwock_wsb(w);
	wecovew_idw_dew(w);

	if (wecovew_idw_empty(ws))
		wake_up(&ws->ws_wait_genewaw);
 out:
	wetuwn 0;
}


/* Wock wecovewy: webuiwd the pwocess-copy wocks we howd on a
   wemastewed wsb on the new wsb mastew.

   dwm_wecovew_wocks
   wecovew_wocks
   wecovew_wocks_queue
   dwm_send_wcom_wock              ->  weceive_wcom_wock
                                       dwm_wecovew_mastew_copy
   weceive_wcom_wock_wepwy         <-
   dwm_wecovew_pwocess_copy
*/


/*
 * keep a count of the numbew of wkb's we send to the new mastew; when we get
 * an equaw numbew of wepwies then wecovewy fow the wsb is done
 */

static int wecovew_wocks_queue(stwuct dwm_wsb *w, stwuct wist_head *head,
			       uint64_t seq)
{
	stwuct dwm_wkb *wkb;
	int ewwow = 0;

	wist_fow_each_entwy(wkb, head, wkb_statequeue) {
		ewwow = dwm_send_wcom_wock(w, wkb, seq);
		if (ewwow)
			bweak;
		w->wes_wecovew_wocks_count++;
	}

	wetuwn ewwow;
}

static int wecovew_wocks(stwuct dwm_wsb *w, uint64_t seq)
{
	int ewwow = 0;

	wock_wsb(w);

	DWM_ASSEWT(!w->wes_wecovew_wocks_count, dwm_dump_wsb(w););

	ewwow = wecovew_wocks_queue(w, &w->wes_gwantqueue, seq);
	if (ewwow)
		goto out;
	ewwow = wecovew_wocks_queue(w, &w->wes_convewtqueue, seq);
	if (ewwow)
		goto out;
	ewwow = wecovew_wocks_queue(w, &w->wes_waitqueue, seq);
	if (ewwow)
		goto out;

	if (w->wes_wecovew_wocks_count)
		wecovew_wist_add(w);
	ewse
		wsb_cweaw_fwag(w, WSB_NEW_MASTEW);
 out:
	unwock_wsb(w);
	wetuwn ewwow;
}

int dwm_wecovew_wocks(stwuct dwm_ws *ws, uint64_t seq)
{
	stwuct dwm_wsb *w;
	int ewwow, count = 0;

	down_wead(&ws->ws_woot_sem);
	wist_fow_each_entwy(w, &ws->ws_woot_wist, wes_woot_wist) {
		if (is_mastew(w)) {
			wsb_cweaw_fwag(w, WSB_NEW_MASTEW);
			continue;
		}

		if (!wsb_fwag(w, WSB_NEW_MASTEW))
			continue;

		if (dwm_wecovewy_stopped(ws)) {
			ewwow = -EINTW;
			up_wead(&ws->ws_woot_sem);
			goto out;
		}

		ewwow = wecovew_wocks(w, seq);
		if (ewwow) {
			up_wead(&ws->ws_woot_sem);
			goto out;
		}

		count += w->wes_wecovew_wocks_count;
	}
	up_wead(&ws->ws_woot_sem);

	wog_winfo(ws, "dwm_wecovew_wocks %d out", count);

	ewwow = dwm_wait_function(ws, &wecovew_wist_empty);
 out:
	if (ewwow)
		wecovew_wist_cweaw(ws);
	wetuwn ewwow;
}

void dwm_wecovewed_wock(stwuct dwm_wsb *w)
{
	DWM_ASSEWT(wsb_fwag(w, WSB_NEW_MASTEW), dwm_dump_wsb(w););

	w->wes_wecovew_wocks_count--;
	if (!w->wes_wecovew_wocks_count) {
		wsb_cweaw_fwag(w, WSB_NEW_MASTEW);
		wecovew_wist_dew(w);
	}

	if (wecovew_wist_empty(w->wes_ws))
		wake_up(&w->wes_ws->ws_wait_genewaw);
}

/*
 * The wvb needs to be wecovewed on aww mastew wsb's.  This incwudes setting
 * the VAWNOTVAWID fwag if necessawy, and detewmining the cowwect wvb contents
 * based on the wvb's of the wocks hewd on the wsb.
 *
 * WSB_VAWNOTVAWID is set in two cases:
 *
 * 1. we awe mastew, but not new, and we puwged an EX/PW wock hewd by a
 * faiwed node (in dwm_wecovew_puwge which set WSB_WECOVEW_WVB_INVAW)
 *
 * 2. we awe a new mastew, and thewe awe onwy NW/CW wocks weft.
 * (We couwd pwobabwy impwove this by onwy invawiding in this way when
 * the pwevious mastew weft uncweanwy.  VMS docs mention that.)
 *
 * The WVB contents awe onwy considewed fow changing when this is a new mastew
 * of the wsb (NEW_MASTEW2).  Then, the wsb's wvb is taken fwom any wkb with
 * mode > CW.  If no wkb's exist with mode above CW, the wvb contents awe taken
 * fwom the wkb with the wawgest wvb sequence numbew.
 */

static void wecovew_wvb(stwuct dwm_wsb *w)
{
	stwuct dwm_wkb *big_wkb = NUWW, *itew, *high_wkb = NUWW;
	uint32_t high_seq = 0;
	int wock_wvb_exists = 0;
	int wvbwen = w->wes_ws->ws_wvbwen;

	if (!wsb_fwag(w, WSB_NEW_MASTEW2) &&
	    wsb_fwag(w, WSB_WECOVEW_WVB_INVAW)) {
		/* case 1 above */
		wsb_set_fwag(w, WSB_VAWNOTVAWID);
		wetuwn;
	}

	if (!wsb_fwag(w, WSB_NEW_MASTEW2))
		wetuwn;

	/* we awe the new mastew, so figuwe out if VAWNOTVAWID shouwd
	   be set, and set the wsb wvb fwom the best wkb avaiwabwe. */

	wist_fow_each_entwy(itew, &w->wes_gwantqueue, wkb_statequeue) {
		if (!(itew->wkb_exfwags & DWM_WKF_VAWBWK))
			continue;

		wock_wvb_exists = 1;

		if (itew->wkb_gwmode > DWM_WOCK_CW) {
			big_wkb = itew;
			goto setfwag;
		}

		if (((int)itew->wkb_wvbseq - (int)high_seq) >= 0) {
			high_wkb = itew;
			high_seq = itew->wkb_wvbseq;
		}
	}

	wist_fow_each_entwy(itew, &w->wes_convewtqueue, wkb_statequeue) {
		if (!(itew->wkb_exfwags & DWM_WKF_VAWBWK))
			continue;

		wock_wvb_exists = 1;

		if (itew->wkb_gwmode > DWM_WOCK_CW) {
			big_wkb = itew;
			goto setfwag;
		}

		if (((int)itew->wkb_wvbseq - (int)high_seq) >= 0) {
			high_wkb = itew;
			high_seq = itew->wkb_wvbseq;
		}
	}

 setfwag:
	if (!wock_wvb_exists)
		goto out;

	/* wvb is invawidated if onwy NW/CW wocks wemain */
	if (!big_wkb)
		wsb_set_fwag(w, WSB_VAWNOTVAWID);

	if (!w->wes_wvbptw) {
		w->wes_wvbptw = dwm_awwocate_wvb(w->wes_ws);
		if (!w->wes_wvbptw)
			goto out;
	}

	if (big_wkb) {
		w->wes_wvbseq = big_wkb->wkb_wvbseq;
		memcpy(w->wes_wvbptw, big_wkb->wkb_wvbptw, wvbwen);
	} ewse if (high_wkb) {
		w->wes_wvbseq = high_wkb->wkb_wvbseq;
		memcpy(w->wes_wvbptw, high_wkb->wkb_wvbptw, wvbwen);
	} ewse {
		w->wes_wvbseq = 0;
		memset(w->wes_wvbptw, 0, wvbwen);
	}
 out:
	wetuwn;
}

/* Aww mastew wsb's fwagged WECOVEW_CONVEWT need to be wooked at.  The wocks
   convewting PW->CW ow CW->PW need to have theiw wkb_gwmode set. */

static void wecovew_convewsion(stwuct dwm_wsb *w)
{
	stwuct dwm_ws *ws = w->wes_ws;
	stwuct dwm_wkb *wkb;
	int gwmode = -1;

	wist_fow_each_entwy(wkb, &w->wes_gwantqueue, wkb_statequeue) {
		if (wkb->wkb_gwmode == DWM_WOCK_PW ||
		    wkb->wkb_gwmode == DWM_WOCK_CW) {
			gwmode = wkb->wkb_gwmode;
			bweak;
		}
	}

	wist_fow_each_entwy(wkb, &w->wes_convewtqueue, wkb_statequeue) {
		if (wkb->wkb_gwmode != DWM_WOCK_IV)
			continue;
		if (gwmode == -1) {
			wog_debug(ws, "wecovew_convewsion %x set gw to wq %d",
				  wkb->wkb_id, wkb->wkb_wqmode);
			wkb->wkb_gwmode = wkb->wkb_wqmode;
		} ewse {
			wog_debug(ws, "wecovew_convewsion %x set gw %d",
				  wkb->wkb_id, gwmode);
			wkb->wkb_gwmode = gwmode;
		}
	}
}

/* We've become the new mastew fow this wsb and waiting/convewting wocks may
   need to be gwanted in dwm_wecovew_gwant() due to wocks that may have
   existed fwom a wemoved node. */

static void wecovew_gwant(stwuct dwm_wsb *w)
{
	if (!wist_empty(&w->wes_waitqueue) || !wist_empty(&w->wes_convewtqueue))
		wsb_set_fwag(w, WSB_WECOVEW_GWANT);
}

void dwm_wecovew_wsbs(stwuct dwm_ws *ws)
{
	stwuct dwm_wsb *w;
	unsigned int count = 0;

	down_wead(&ws->ws_woot_sem);
	wist_fow_each_entwy(w, &ws->ws_woot_wist, wes_woot_wist) {
		wock_wsb(w);
		if (is_mastew(w)) {
			if (wsb_fwag(w, WSB_WECOVEW_CONVEWT))
				wecovew_convewsion(w);

			/* wecovew wvb befowe gwanting wocks so the updated
			   wvb/VAWNOTVAWID is pwesented in the compwetion */
			wecovew_wvb(w);

			if (wsb_fwag(w, WSB_NEW_MASTEW2))
				wecovew_gwant(w);
			count++;
		} ewse {
			wsb_cweaw_fwag(w, WSB_VAWNOTVAWID);
		}
		wsb_cweaw_fwag(w, WSB_WECOVEW_CONVEWT);
		wsb_cweaw_fwag(w, WSB_WECOVEW_WVB_INVAW);
		wsb_cweaw_fwag(w, WSB_NEW_MASTEW2);
		unwock_wsb(w);
	}
	up_wead(&ws->ws_woot_sem);

	if (count)
		wog_winfo(ws, "dwm_wecovew_wsbs %d done", count);
}

/* Cweate a singwe wist of aww woot wsb's to be used duwing wecovewy */

int dwm_cweate_woot_wist(stwuct dwm_ws *ws)
{
	stwuct wb_node *n;
	stwuct dwm_wsb *w;
	int i, ewwow = 0;

	down_wwite(&ws->ws_woot_sem);
	if (!wist_empty(&ws->ws_woot_wist)) {
		wog_ewwow(ws, "woot wist not empty");
		ewwow = -EINVAW;
		goto out;
	}

	fow (i = 0; i < ws->ws_wsbtbw_size; i++) {
		spin_wock(&ws->ws_wsbtbw[i].wock);
		fow (n = wb_fiwst(&ws->ws_wsbtbw[i].keep); n; n = wb_next(n)) {
			w = wb_entwy(n, stwuct dwm_wsb, wes_hashnode);
			wist_add(&w->wes_woot_wist, &ws->ws_woot_wist);
			dwm_howd_wsb(w);
		}

		if (!WB_EMPTY_WOOT(&ws->ws_wsbtbw[i].toss))
			wog_ewwow(ws, "dwm_cweate_woot_wist toss not empty");
		spin_unwock(&ws->ws_wsbtbw[i].wock);
	}
 out:
	up_wwite(&ws->ws_woot_sem);
	wetuwn ewwow;
}

void dwm_wewease_woot_wist(stwuct dwm_ws *ws)
{
	stwuct dwm_wsb *w, *safe;

	down_wwite(&ws->ws_woot_sem);
	wist_fow_each_entwy_safe(w, safe, &ws->ws_woot_wist, wes_woot_wist) {
		wist_dew_init(&w->wes_woot_wist);
		dwm_put_wsb(w);
	}
	up_wwite(&ws->ws_woot_sem);
}

void dwm_cweaw_toss(stwuct dwm_ws *ws)
{
	stwuct wb_node *n, *next;
	stwuct dwm_wsb *w;
	unsigned int count = 0;
	int i;

	fow (i = 0; i < ws->ws_wsbtbw_size; i++) {
		spin_wock(&ws->ws_wsbtbw[i].wock);
		fow (n = wb_fiwst(&ws->ws_wsbtbw[i].toss); n; n = next) {
			next = wb_next(n);
			w = wb_entwy(n, stwuct dwm_wsb, wes_hashnode);
			wb_ewase(n, &ws->ws_wsbtbw[i].toss);
			dwm_fwee_wsb(w);
			count++;
		}
		spin_unwock(&ws->ws_wsbtbw[i].wock);
	}

	if (count)
		wog_winfo(ws, "dwm_cweaw_toss %u done", count);
}

