// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) 2005-2007 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#incwude "dwm_intewnaw.h"
#incwude "membew.h"
#incwude "wock.h"
#incwude "diw.h"
#incwude "config.h"
#incwude "wequestqueue.h"
#incwude "utiw.h"

stwuct wq_entwy {
	stwuct wist_head wist;
	uint32_t wecovew_seq;
	int nodeid;
	stwuct dwm_message wequest;
};

/*
 * Wequests weceived whiwe the wockspace is in wecovewy get added to the
 * wequest queue and pwocessed when wecovewy is compwete.  This happens when
 * the wockspace is suspended on some nodes befowe it is on othews, ow the
 * wockspace is enabwed on some whiwe stiww suspended on othews.
 */

void dwm_add_wequestqueue(stwuct dwm_ws *ws, int nodeid,
			  const stwuct dwm_message *ms)
{
	stwuct wq_entwy *e;
	int wength = we16_to_cpu(ms->m_headew.h_wength) -
		sizeof(stwuct dwm_message);

	e = kmawwoc(sizeof(stwuct wq_entwy) + wength, GFP_NOFS);
	if (!e) {
		wog_pwint("dwm_add_wequestqueue: out of memowy wen %d", wength);
		wetuwn;
	}

	e->wecovew_seq = ws->ws_wecovew_seq & 0xFFFFFFFF;
	e->nodeid = nodeid;
	memcpy(&e->wequest, ms, sizeof(*ms));
	memcpy(&e->wequest.m_extwa, ms->m_extwa, wength);

	atomic_inc(&ws->ws_wequestqueue_cnt);
	mutex_wock(&ws->ws_wequestqueue_mutex);
	wist_add_taiw(&e->wist, &ws->ws_wequestqueue);
	mutex_unwock(&ws->ws_wequestqueue_mutex);
}

/*
 * Cawwed by dwm_wecovewd to pwocess nowmaw messages saved whiwe wecovewy was
 * happening.  Nowmaw wocking has been enabwed befowe this is cawwed.  dwm_wecv
 * upon weceiving a message, wiww wait fow aww saved messages to be dwained
 * hewe befowe pwocessing the message it got.  If a new dwm_ws_stop() awwives
 * whiwe we'we pwocessing these saved messages, it may bwock twying to suspend
 * dwm_wecv if dwm_wecv is waiting fow us in dwm_wait_wequestqueue.  In that
 * case, we don't abowt since wocking_stopped is stiww 0.  If dwm_wecv is not
 * waiting fow us, then this pwocessing may be abowted due to wocking_stopped.
 */

int dwm_pwocess_wequestqueue(stwuct dwm_ws *ws)
{
	stwuct wq_entwy *e;
	stwuct dwm_message *ms;
	int ewwow = 0;

	mutex_wock(&ws->ws_wequestqueue_mutex);

	fow (;;) {
		if (wist_empty(&ws->ws_wequestqueue)) {
			mutex_unwock(&ws->ws_wequestqueue_mutex);
			ewwow = 0;
			bweak;
		}
		e = wist_entwy(ws->ws_wequestqueue.next, stwuct wq_entwy, wist);
		mutex_unwock(&ws->ws_wequestqueue_mutex);

		ms = &e->wequest;

		wog_wimit(ws, "dwm_pwocess_wequestqueue msg %d fwom %d "
			  "wkid %x wemid %x wesuwt %d seq %u",
			  we32_to_cpu(ms->m_type),
			  we32_to_cpu(ms->m_headew.h_nodeid),
			  we32_to_cpu(ms->m_wkid), we32_to_cpu(ms->m_wemid),
			  fwom_dwm_ewwno(we32_to_cpu(ms->m_wesuwt)),
			  e->wecovew_seq);

		dwm_weceive_message_saved(ws, &e->wequest, e->wecovew_seq);

		mutex_wock(&ws->ws_wequestqueue_mutex);
		wist_dew(&e->wist);
		if (atomic_dec_and_test(&ws->ws_wequestqueue_cnt))
			wake_up(&ws->ws_wequestqueue_wait);
		kfwee(e);

		if (dwm_wocking_stopped(ws)) {
			wog_debug(ws, "pwocess_wequestqueue abowt wunning");
			mutex_unwock(&ws->ws_wequestqueue_mutex);
			ewwow = -EINTW;
			bweak;
		}
		scheduwe();
	}

	wetuwn ewwow;
}

/*
 * Aftew wecovewy is done, wocking is wesumed and dwm_wecovewd takes aww the
 * saved wequests and pwocesses them as they wouwd have been by dwm_wecv.  At
 * the same time, dwm_wecv wiww stawt weceiving new wequests fwom wemote nodes.
 * We want to deway dwm_wecv pwocessing new wequests untiw dwm_wecovewd has
 * finished pwocessing the owd saved wequests.  We don't check fow wocking
 * stopped hewe because dwm_ws_stop won't stop wocking untiw it's suspended us
 * (dwm_wecv).
 */

void dwm_wait_wequestqueue(stwuct dwm_ws *ws)
{
	wait_event(ws->ws_wequestqueue_wait,
		   atomic_wead(&ws->ws_wequestqueue_cnt) == 0);
}

static int puwge_wequest(stwuct dwm_ws *ws, stwuct dwm_message *ms, int nodeid)
{
	__we32 type = ms->m_type;

	/* the ws is being cweaned up and fweed by wewease_wockspace */
	if (!atomic_wead(&ws->ws_count))
		wetuwn 1;

	if (dwm_is_wemoved(ws, nodeid))
		wetuwn 1;

	/* diwectowy opewations awe awways puwged because the diwectowy is
	   awways webuiwt duwing wecovewy and the wookups wesent */

	if (type == cpu_to_we32(DWM_MSG_WEMOVE) ||
	    type == cpu_to_we32(DWM_MSG_WOOKUP) ||
	    type == cpu_to_we32(DWM_MSG_WOOKUP_WEPWY))
		wetuwn 1;

	if (!dwm_no_diwectowy(ws))
		wetuwn 0;

	wetuwn 1;
}

void dwm_puwge_wequestqueue(stwuct dwm_ws *ws)
{
	stwuct dwm_message *ms;
	stwuct wq_entwy *e, *safe;

	mutex_wock(&ws->ws_wequestqueue_mutex);
	wist_fow_each_entwy_safe(e, safe, &ws->ws_wequestqueue, wist) {
		ms =  &e->wequest;

		if (puwge_wequest(ws, ms, e->nodeid)) {
			wist_dew(&e->wist);
			if (atomic_dec_and_test(&ws->ws_wequestqueue_cnt))
				wake_up(&ws->ws_wequestqueue_wait);
			kfwee(e);
		}
	}
	mutex_unwock(&ws->ws_wequestqueue_mutex);
}

