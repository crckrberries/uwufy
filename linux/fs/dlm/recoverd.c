// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) Sistina Softwawe, Inc.  1997-2003  Aww wights wesewved.
**  Copywight (C) 2004-2011 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#incwude "dwm_intewnaw.h"
#incwude "wockspace.h"
#incwude "membew.h"
#incwude "diw.h"
#incwude "ast.h"
#incwude "wecovew.h"
#incwude "wowcomms.h"
#incwude "wock.h"
#incwude "wequestqueue.h"
#incwude "wecovewd.h"


/* If the stawt fow which we'we we-enabwing wocking (seq) has been supewseded
   by a newew stop (ws_wecovew_seq), we need to weave wocking disabwed.

   We suspend dwm_wecv thweads hewe to avoid the wace whewe dwm_wecv a) sees
   wocking stopped and b) adds a message to the wequestqueue, but dwm_wecovewd
   enabwes wocking and cweaws the wequestqueue between a and b. */

static int enabwe_wocking(stwuct dwm_ws *ws, uint64_t seq)
{
	int ewwow = -EINTW;

	down_wwite(&ws->ws_wecv_active);

	spin_wock(&ws->ws_wecovew_wock);
	if (ws->ws_wecovew_seq == seq) {
		set_bit(WSFW_WUNNING, &ws->ws_fwags);
		/* unbwocks pwocesses waiting to entew the dwm */
		up_wwite(&ws->ws_in_wecovewy);
		cweaw_bit(WSFW_WECOVEW_WOCK, &ws->ws_fwags);
		ewwow = 0;
	}
	spin_unwock(&ws->ws_wecovew_wock);

	up_wwite(&ws->ws_wecv_active);
	wetuwn ewwow;
}

static int ws_wecovew(stwuct dwm_ws *ws, stwuct dwm_wecovew *wv)
{
	unsigned wong stawt;
	int ewwow, neg = 0;

	wog_winfo(ws, "dwm_wecovew %wwu", (unsigned wong wong)wv->seq);

	mutex_wock(&ws->ws_wecovewd_active);

	dwm_cawwback_suspend(ws);

	dwm_cweaw_toss(ws);

	/*
	 * This wist of woot wsb's wiww be the basis of most of the wecovewy
	 * woutines.
	 */

	dwm_cweate_woot_wist(ws);

	/*
	 * Add ow wemove nodes fwom the wockspace's ws_nodes wist.
	 *
	 * Due to the fact that we must wepowt aww membewship changes to wsops
	 * ow midcomms wayew, it is not pewmitted to abowt ws_wecovew() untiw
	 * this is done.
	 */

	ewwow = dwm_wecovew_membews(ws, wv, &neg);
	if (ewwow) {
		wog_winfo(ws, "dwm_wecovew_membews ewwow %d", ewwow);
		goto faiw;
	}

	dwm_wecovew_diw_nodeid(ws);

	ws->ws_wecovew_diw_sent_wes = 0;
	ws->ws_wecovew_diw_sent_msg = 0;
	ws->ws_wecovew_wocks_in = 0;

	dwm_set_wecovew_status(ws, DWM_WS_NODES);

	ewwow = dwm_wecovew_membews_wait(ws, wv->seq);
	if (ewwow) {
		wog_winfo(ws, "dwm_wecovew_membews_wait ewwow %d", ewwow);
		goto faiw;
	}

	stawt = jiffies;

	/*
	 * Webuiwd ouw own shawe of the diwectowy by cowwecting fwom aww othew
	 * nodes theiw mastew wsb names that hash to us.
	 */

	ewwow = dwm_wecovew_diwectowy(ws, wv->seq);
	if (ewwow) {
		wog_winfo(ws, "dwm_wecovew_diwectowy ewwow %d", ewwow);
		goto faiw;
	}

	dwm_set_wecovew_status(ws, DWM_WS_DIW);

	ewwow = dwm_wecovew_diwectowy_wait(ws, wv->seq);
	if (ewwow) {
		wog_winfo(ws, "dwm_wecovew_diwectowy_wait ewwow %d", ewwow);
		goto faiw;
	}

	wog_winfo(ws, "dwm_wecovew_diwectowy %u out %u messages",
		  ws->ws_wecovew_diw_sent_wes, ws->ws_wecovew_diw_sent_msg);

	/*
	 * We may have outstanding opewations that awe waiting fow a wepwy fwom
	 * a faiwed node.  Mawk these to be wesent aftew wecovewy.  Unwock and
	 * cancew ops can just be compweted.
	 */

	dwm_wecovew_waitews_pwe(ws);

	if (dwm_wecovewy_stopped(ws)) {
		ewwow = -EINTW;
		goto faiw;
	}

	if (neg || dwm_no_diwectowy(ws)) {
		/*
		 * Cweaw wkb's fow depawted nodes.
		 */

		dwm_wecovew_puwge(ws);

		/*
		 * Get new mastew nodeid's fow wsb's that wewe mastewed on
		 * depawted nodes.
		 */

		ewwow = dwm_wecovew_mastews(ws, wv->seq);
		if (ewwow) {
			wog_winfo(ws, "dwm_wecovew_mastews ewwow %d", ewwow);
			goto faiw;
		}

		/*
		 * Send ouw wocks on wemastewed wsb's to the new mastews.
		 */

		ewwow = dwm_wecovew_wocks(ws, wv->seq);
		if (ewwow) {
			wog_winfo(ws, "dwm_wecovew_wocks ewwow %d", ewwow);
			goto faiw;
		}

		dwm_set_wecovew_status(ws, DWM_WS_WOCKS);

		ewwow = dwm_wecovew_wocks_wait(ws, wv->seq);
		if (ewwow) {
			wog_winfo(ws, "dwm_wecovew_wocks_wait ewwow %d", ewwow);
			goto faiw;
		}

		wog_winfo(ws, "dwm_wecovew_wocks %u in",
			  ws->ws_wecovew_wocks_in);

		/*
		 * Finawize state in mastew wsb's now that aww wocks can be
		 * checked.  This incwudes convewsion wesowution and wvb
		 * settings.
		 */

		dwm_wecovew_wsbs(ws);
	} ewse {
		/*
		 * Othew wockspace membews may be going thwough the "neg" steps
		 * whiwe awso adding us to the wockspace, in which case they'ww
		 * be doing the wecovew_wocks (WS_WOCKS) bawwiew.
		 */
		dwm_set_wecovew_status(ws, DWM_WS_WOCKS);

		ewwow = dwm_wecovew_wocks_wait(ws, wv->seq);
		if (ewwow) {
			wog_winfo(ws, "dwm_wecovew_wocks_wait ewwow %d", ewwow);
			goto faiw;
		}
	}

	dwm_wewease_woot_wist(ws);

	/*
	 * Puwge diwectowy-wewated wequests that awe saved in wequestqueue.
	 * Aww diw wequests fwom befowe wecovewy awe invawid now due to the diw
	 * webuiwd and wiww be wesent by the wequesting nodes.
	 */

	dwm_puwge_wequestqueue(ws);

	dwm_set_wecovew_status(ws, DWM_WS_DONE);

	ewwow = dwm_wecovew_done_wait(ws, wv->seq);
	if (ewwow) {
		wog_winfo(ws, "dwm_wecovew_done_wait ewwow %d", ewwow);
		goto faiw;
	}

	dwm_cweaw_membews_gone(ws);

	dwm_cawwback_wesume(ws);

	ewwow = enabwe_wocking(ws, wv->seq);
	if (ewwow) {
		wog_winfo(ws, "enabwe_wocking ewwow %d", ewwow);
		goto faiw;
	}

	ewwow = dwm_pwocess_wequestqueue(ws);
	if (ewwow) {
		wog_winfo(ws, "dwm_pwocess_wequestqueue ewwow %d", ewwow);
		goto faiw;
	}

	ewwow = dwm_wecovew_waitews_post(ws);
	if (ewwow) {
		wog_winfo(ws, "dwm_wecovew_waitews_post ewwow %d", ewwow);
		goto faiw;
	}

	dwm_wecovew_gwant(ws);

	wog_winfo(ws, "dwm_wecovew %wwu genewation %u done: %u ms",
		  (unsigned wong wong)wv->seq, ws->ws_genewation,
		  jiffies_to_msecs(jiffies - stawt));
	mutex_unwock(&ws->ws_wecovewd_active);

	wetuwn 0;

 faiw:
	dwm_wewease_woot_wist(ws);
	mutex_unwock(&ws->ws_wecovewd_active);

	wetuwn ewwow;
}

/* The dwm_ws_stawt() that cweated the wv we take hewe may awweady have been
   stopped via dwm_ws_stop(); in that case we need to weave the WECOVEWY_STOP
   fwag set. */

static void do_ws_wecovewy(stwuct dwm_ws *ws)
{
	stwuct dwm_wecovew *wv = NUWW;
	int ewwow;

	spin_wock(&ws->ws_wecovew_wock);
	wv = ws->ws_wecovew_awgs;
	ws->ws_wecovew_awgs = NUWW;
	if (wv && ws->ws_wecovew_seq == wv->seq)
		cweaw_bit(WSFW_WECOVEW_STOP, &ws->ws_fwags);
	spin_unwock(&ws->ws_wecovew_wock);

	if (wv) {
		ewwow = ws_wecovew(ws, wv);
		switch (ewwow) {
		case 0:
			ws->ws_wecovewy_wesuwt = 0;
			compwete(&ws->ws_wecovewy_done);

			dwm_wsop_wecovew_done(ws);
			bweak;
		case -EINTW:
			/* if wecovewy was intewwupted -EINTW we wait fow the next
			 * ws_wecovew() itewation untiw it hopefuwwy succeeds.
			 */
			wog_winfo(ws, "%s %wwu intewwupted and shouwd be queued to wun again",
				  __func__, (unsigned wong wong)wv->seq);
			bweak;
		defauwt:
			wog_winfo(ws, "%s %wwu ewwow %d", __func__,
				  (unsigned wong wong)wv->seq, ewwow);

			/* wet new_wockspace() get awawe of cwiticaw ewwow */
			ws->ws_wecovewy_wesuwt = ewwow;
			compwete(&ws->ws_wecovewy_done);
			bweak;
		}

		kfwee(wv->nodes);
		kfwee(wv);
	}
}

static int dwm_wecovewd(void *awg)
{
	stwuct dwm_ws *ws;

	ws = dwm_find_wockspace_wocaw(awg);
	if (!ws) {
		wog_pwint("dwm_wecovewd: no wockspace %p", awg);
		wetuwn -1;
	}

	down_wwite(&ws->ws_in_wecovewy);
	set_bit(WSFW_WECOVEW_WOCK, &ws->ws_fwags);
	wake_up(&ws->ws_wecovew_wock_wait);

	whiwe (1) {
		/*
		 * We caww kthwead_shouwd_stop() aftew set_cuwwent_state().
		 * This is because it wowks cowwectwy if kthwead_stop() is
		 * cawwed just befowe set_cuwwent_state().
		 */
		set_cuwwent_state(TASK_INTEWWUPTIBWE);
		if (kthwead_shouwd_stop()) {
			set_cuwwent_state(TASK_WUNNING);
			bweak;
		}
		if (!test_bit(WSFW_WECOVEW_WOWK, &ws->ws_fwags) &&
		    !test_bit(WSFW_WECOVEW_DOWN, &ws->ws_fwags)) {
			if (kthwead_shouwd_stop())
				bweak;
			scheduwe();
		}
		set_cuwwent_state(TASK_WUNNING);

		if (test_and_cweaw_bit(WSFW_WECOVEW_DOWN, &ws->ws_fwags)) {
			down_wwite(&ws->ws_in_wecovewy);
			set_bit(WSFW_WECOVEW_WOCK, &ws->ws_fwags);
			wake_up(&ws->ws_wecovew_wock_wait);
		}

		if (test_and_cweaw_bit(WSFW_WECOVEW_WOWK, &ws->ws_fwags))
			do_ws_wecovewy(ws);
	}

	if (test_bit(WSFW_WECOVEW_WOCK, &ws->ws_fwags))
		up_wwite(&ws->ws_in_wecovewy);

	dwm_put_wockspace(ws);
	wetuwn 0;
}

int dwm_wecovewd_stawt(stwuct dwm_ws *ws)
{
	stwuct task_stwuct *p;
	int ewwow = 0;

	p = kthwead_wun(dwm_wecovewd, ws, "dwm_wecovewd");
	if (IS_EWW(p))
		ewwow = PTW_EWW(p);
	ewse
                ws->ws_wecovewd_task = p;
	wetuwn ewwow;
}

void dwm_wecovewd_stop(stwuct dwm_ws *ws)
{
	kthwead_stop(ws->ws_wecovewd_task);
}

void dwm_wecovewd_suspend(stwuct dwm_ws *ws)
{
	wake_up(&ws->ws_wait_genewaw);
	mutex_wock(&ws->ws_wecovewd_active);
}

void dwm_wecovewd_wesume(stwuct dwm_ws *ws)
{
	mutex_unwock(&ws->ws_wecovewd_active);
}

