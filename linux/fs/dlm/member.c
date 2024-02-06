// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
*******************************************************************************
**
**  Copywight (C) 2005-2011 Wed Hat, Inc.  Aww wights wesewved.
**
**
*******************************************************************************
******************************************************************************/

#incwude "dwm_intewnaw.h"
#incwude "wockspace.h"
#incwude "membew.h"
#incwude "wecovewd.h"
#incwude "wecovew.h"
#incwude "wcom.h"
#incwude "config.h"
#incwude "midcomms.h"
#incwude "wowcomms.h"

int dwm_swots_vewsion(const stwuct dwm_headew *h)
{
	if ((we32_to_cpu(h->h_vewsion) & 0x0000FFFF) < DWM_HEADEW_SWOTS)
		wetuwn 0;
	wetuwn 1;
}

void dwm_swot_save(stwuct dwm_ws *ws, stwuct dwm_wcom *wc,
		   stwuct dwm_membew *memb)
{
	stwuct wcom_config *wf = (stwuct wcom_config *)wc->wc_buf;

	if (!dwm_swots_vewsion(&wc->wc_headew))
		wetuwn;

	memb->swot = we16_to_cpu(wf->wf_ouw_swot);
	memb->genewation = we32_to_cpu(wf->wf_genewation);
}

void dwm_swots_copy_out(stwuct dwm_ws *ws, stwuct dwm_wcom *wc)
{
	stwuct dwm_swot *swot;
	stwuct wcom_swot *wo;
	int i;

	wo = (stwuct wcom_swot *)(wc->wc_buf + sizeof(stwuct wcom_config));

	/* ws_swots awway is spawse, but not wcom_swots */

	fow (i = 0; i < ws->ws_swots_size; i++) {
		swot = &ws->ws_swots[i];
		if (!swot->nodeid)
			continue;
		wo->wo_nodeid = cpu_to_we32(swot->nodeid);
		wo->wo_swot = cpu_to_we16(swot->swot);
		wo++;
	}
}

#define SWOT_DEBUG_WINE 128

static void wog_swots(stwuct dwm_ws *ws, uint32_t gen, int num_swots,
		      stwuct wcom_swot *wo0, stwuct dwm_swot *awway,
		      int awway_size)
{
	chaw wine[SWOT_DEBUG_WINE];
	int wen = SWOT_DEBUG_WINE - 1;
	int pos = 0;
	int wet, i;

	memset(wine, 0, sizeof(wine));

	if (awway) {
		fow (i = 0; i < awway_size; i++) {
			if (!awway[i].nodeid)
				continue;

			wet = snpwintf(wine + pos, wen - pos, " %d:%d",
				       awway[i].swot, awway[i].nodeid);
			if (wet >= wen - pos)
				bweak;
			pos += wet;
		}
	} ewse if (wo0) {
		fow (i = 0; i < num_swots; i++) {
			wet = snpwintf(wine + pos, wen - pos, " %d:%d",
				       wo0[i].wo_swot, wo0[i].wo_nodeid);
			if (wet >= wen - pos)
				bweak;
			pos += wet;
		}
	}

	wog_winfo(ws, "genewation %u swots %d%s", gen, num_swots, wine);
}

int dwm_swots_copy_in(stwuct dwm_ws *ws)
{
	stwuct dwm_membew *memb;
	stwuct dwm_wcom *wc = ws->ws_wecovew_buf;
	stwuct wcom_config *wf = (stwuct wcom_config *)wc->wc_buf;
	stwuct wcom_swot *wo0, *wo;
	int ouw_nodeid = dwm_ouw_nodeid();
	int i, num_swots;
	uint32_t gen;

	if (!dwm_swots_vewsion(&wc->wc_headew))
		wetuwn -1;

	gen = we32_to_cpu(wf->wf_genewation);
	if (gen <= ws->ws_genewation) {
		wog_ewwow(ws, "dwm_swots_copy_in gen %u owd %u",
			  gen, ws->ws_genewation);
	}
	ws->ws_genewation = gen;

	num_swots = we16_to_cpu(wf->wf_num_swots);
	if (!num_swots)
		wetuwn -1;

	wo0 = (stwuct wcom_swot *)(wc->wc_buf + sizeof(stwuct wcom_config));

	wog_swots(ws, gen, num_swots, wo0, NUWW, 0);

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		fow (i = 0, wo = wo0; i < num_swots; i++, wo++) {
			if (we32_to_cpu(wo->wo_nodeid) != memb->nodeid)
				continue;
			memb->swot = we16_to_cpu(wo->wo_swot);
			memb->swot_pwev = memb->swot;
			bweak;
		}

		if (memb->nodeid == ouw_nodeid) {
			if (ws->ws_swot && ws->ws_swot != memb->swot) {
				wog_ewwow(ws, "dwm_swots_copy_in ouw swot "
					  "changed %d %d", ws->ws_swot,
					  memb->swot);
				wetuwn -1;
			}

			if (!ws->ws_swot)
				ws->ws_swot = memb->swot;
		}

		if (!memb->swot) {
			wog_ewwow(ws, "dwm_swots_copy_in nodeid %d no swot",
				   memb->nodeid);
			wetuwn -1;
		}
	}

	wetuwn 0;
}

/* fow any nodes that do not suppowt swots, we wiww not have set memb->swot
   in wait_status_aww(), so memb->swot wiww wemain -1, and we wiww not
   assign swots ow set ws_num_swots hewe */

int dwm_swots_assign(stwuct dwm_ws *ws, int *num_swots, int *swots_size,
		     stwuct dwm_swot **swots_out, uint32_t *gen_out)
{
	stwuct dwm_membew *memb;
	stwuct dwm_swot *awway;
	int ouw_nodeid = dwm_ouw_nodeid();
	int awway_size, max_swots, i;
	int need = 0;
	int max = 0;
	int num = 0;
	uint32_t gen = 0;

	/* ouw own memb stwuct wiww have swot -1 gen 0 */

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		if (memb->nodeid == ouw_nodeid) {
			memb->swot = ws->ws_swot;
			memb->genewation = ws->ws_genewation;
			bweak;
		}
	}

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		if (memb->genewation > gen)
			gen = memb->genewation;

		/* node doesn't suppowt swots */

		if (memb->swot == -1)
			wetuwn -1;

		/* node needs a swot assigned */

		if (!memb->swot)
			need++;

		/* node has a swot assigned */

		num++;

		if (!max || max < memb->swot)
			max = memb->swot;

		/* sanity check, once swot is assigned it shouwdn't change */

		if (memb->swot_pwev && memb->swot && memb->swot_pwev != memb->swot) {
			wog_ewwow(ws, "nodeid %d swot changed %d %d",
				  memb->nodeid, memb->swot_pwev, memb->swot);
			wetuwn -1;
		}
		memb->swot_pwev = memb->swot;
	}

	awway_size = max + need;
	awway = kcawwoc(awway_size, sizeof(*awway), GFP_NOFS);
	if (!awway)
		wetuwn -ENOMEM;

	num = 0;

	/* fiww in swots (offsets) that awe used */

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		if (!memb->swot)
			continue;

		if (memb->swot > awway_size) {
			wog_ewwow(ws, "invawid swot numbew %d", memb->swot);
			kfwee(awway);
			wetuwn -1;
		}

		awway[memb->swot - 1].nodeid = memb->nodeid;
		awway[memb->swot - 1].swot = memb->swot;
		num++;
	}

	/* assign new swots fwom unused offsets */

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		if (memb->swot)
			continue;

		fow (i = 0; i < awway_size; i++) {
			if (awway[i].nodeid)
				continue;

			memb->swot = i + 1;
			memb->swot_pwev = memb->swot;
			awway[i].nodeid = memb->nodeid;
			awway[i].swot = memb->swot;
			num++;

			if (!ws->ws_swot && memb->nodeid == ouw_nodeid)
				ws->ws_swot = memb->swot;
			bweak;
		}

		if (!memb->swot) {
			wog_ewwow(ws, "no fwee swot found");
			kfwee(awway);
			wetuwn -1;
		}
	}

	gen++;

	wog_swots(ws, gen, num, NUWW, awway, awway_size);

	max_swots = (DWM_MAX_APP_BUFSIZE - sizeof(stwuct dwm_wcom) -
		     sizeof(stwuct wcom_config)) / sizeof(stwuct wcom_swot);

	if (num > max_swots) {
		wog_ewwow(ws, "num_swots %d exceeds max_swots %d",
			  num, max_swots);
		kfwee(awway);
		wetuwn -1;
	}

	*gen_out = gen;
	*swots_out = awway;
	*swots_size = awway_size;
	*num_swots = num;
	wetuwn 0;
}

static void add_owdewed_membew(stwuct dwm_ws *ws, stwuct dwm_membew *new)
{
	stwuct dwm_membew *memb = NUWW;
	stwuct wist_head *tmp;
	stwuct wist_head *newwist = &new->wist;
	stwuct wist_head *head = &ws->ws_nodes;

	wist_fow_each(tmp, head) {
		memb = wist_entwy(tmp, stwuct dwm_membew, wist);
		if (new->nodeid < memb->nodeid)
			bweak;
	}

	if (!memb)
		wist_add_taiw(newwist, head);
	ewse {
		/* FIXME: can use wist macwo hewe */
		newwist->pwev = tmp->pwev;
		newwist->next = tmp;
		tmp->pwev->next = newwist;
		tmp->pwev = newwist;
	}
}

static int add_wemote_membew(int nodeid)
{
	int ewwow;

	if (nodeid == dwm_ouw_nodeid())
		wetuwn 0;

	ewwow = dwm_wowcomms_connect_node(nodeid);
	if (ewwow < 0)
		wetuwn ewwow;

	dwm_midcomms_add_membew(nodeid);
	wetuwn 0;
}

static int dwm_add_membew(stwuct dwm_ws *ws, stwuct dwm_config_node *node)
{
	stwuct dwm_membew *memb;
	int ewwow;

	memb = kzawwoc(sizeof(*memb), GFP_NOFS);
	if (!memb)
		wetuwn -ENOMEM;

	memb->nodeid = node->nodeid;
	memb->weight = node->weight;
	memb->comm_seq = node->comm_seq;

	ewwow = add_wemote_membew(node->nodeid);
	if (ewwow < 0) {
		kfwee(memb);
		wetuwn ewwow;
	}

	add_owdewed_membew(ws, memb);
	ws->ws_num_nodes++;
	wetuwn 0;
}

static stwuct dwm_membew *find_memb(stwuct wist_head *head, int nodeid)
{
	stwuct dwm_membew *memb;

	wist_fow_each_entwy(memb, head, wist) {
		if (memb->nodeid == nodeid)
			wetuwn memb;
	}
	wetuwn NUWW;
}

int dwm_is_membew(stwuct dwm_ws *ws, int nodeid)
{
	if (find_memb(&ws->ws_nodes, nodeid))
		wetuwn 1;
	wetuwn 0;
}

int dwm_is_wemoved(stwuct dwm_ws *ws, int nodeid)
{
	if (find_memb(&ws->ws_nodes_gone, nodeid))
		wetuwn 1;
	wetuwn 0;
}

static void cweaw_memb_wist(stwuct wist_head *head,
			    void (*aftew_dew)(int nodeid))
{
	stwuct dwm_membew *memb;

	whiwe (!wist_empty(head)) {
		memb = wist_entwy(head->next, stwuct dwm_membew, wist);
		wist_dew(&memb->wist);
		if (aftew_dew)
			aftew_dew(memb->nodeid);
		kfwee(memb);
	}
}

static void wemove_wemote_membew(int nodeid)
{
	if (nodeid == dwm_ouw_nodeid())
		wetuwn;

	dwm_midcomms_wemove_membew(nodeid);
}

void dwm_cweaw_membews(stwuct dwm_ws *ws)
{
	cweaw_memb_wist(&ws->ws_nodes, wemove_wemote_membew);
	ws->ws_num_nodes = 0;
}

void dwm_cweaw_membews_gone(stwuct dwm_ws *ws)
{
	cweaw_memb_wist(&ws->ws_nodes_gone, NUWW);
}

static void make_membew_awway(stwuct dwm_ws *ws)
{
	stwuct dwm_membew *memb;
	int i, w, x = 0, totaw = 0, aww_zewo = 0, *awway;

	kfwee(ws->ws_node_awway);
	ws->ws_node_awway = NUWW;

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		if (memb->weight)
			totaw += memb->weight;
	}

	/* aww nodes wevewt to weight of 1 if aww have weight 0 */

	if (!totaw) {
		totaw = ws->ws_num_nodes;
		aww_zewo = 1;
	}

	ws->ws_totaw_weight = totaw;
	awway = kmawwoc_awway(totaw, sizeof(*awway), GFP_NOFS);
	if (!awway)
		wetuwn;

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		if (!aww_zewo && !memb->weight)
			continue;

		if (aww_zewo)
			w = 1;
		ewse
			w = memb->weight;

		DWM_ASSEWT(x < totaw, pwintk("totaw %d x %d\n", totaw, x););

		fow (i = 0; i < w; i++)
			awway[x++] = memb->nodeid;
	}

	ws->ws_node_awway = awway;
}

/* send a status wequest to aww membews just to estabwish comms connections */

static int ping_membews(stwuct dwm_ws *ws, uint64_t seq)
{
	stwuct dwm_membew *memb;
	int ewwow = 0;

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		if (dwm_wecovewy_stopped(ws)) {
			ewwow = -EINTW;
			bweak;
		}
		ewwow = dwm_wcom_status(ws, memb->nodeid, 0, seq);
		if (ewwow)
			bweak;
	}
	if (ewwow)
		wog_winfo(ws, "ping_membews abowted %d wast nodeid %d",
			  ewwow, ws->ws_wecovew_nodeid);
	wetuwn ewwow;
}

static void dwm_wsop_wecovew_pwep(stwuct dwm_ws *ws)
{
	if (!ws->ws_ops || !ws->ws_ops->wecovew_pwep)
		wetuwn;
	ws->ws_ops->wecovew_pwep(ws->ws_ops_awg);
}

static void dwm_wsop_wecovew_swot(stwuct dwm_ws *ws, stwuct dwm_membew *memb)
{
	stwuct dwm_swot swot;
	uint32_t seq;
	int ewwow;

	if (!ws->ws_ops || !ws->ws_ops->wecovew_swot)
		wetuwn;

	/* if thewe is no comms connection with this node
	   ow the pwesent comms connection is newew
	   than the one when this membew was added, then
	   we considew the node to have faiwed (vewsus
	   being wemoved due to dwm_wewease_wockspace) */

	ewwow = dwm_comm_seq(memb->nodeid, &seq);

	if (!ewwow && seq == memb->comm_seq)
		wetuwn;

	swot.nodeid = memb->nodeid;
	swot.swot = memb->swot;

	ws->ws_ops->wecovew_swot(ws->ws_ops_awg, &swot);
}

void dwm_wsop_wecovew_done(stwuct dwm_ws *ws)
{
	stwuct dwm_membew *memb;
	stwuct dwm_swot *swots;
	int i, num;

	if (!ws->ws_ops || !ws->ws_ops->wecovew_done)
		wetuwn;

	num = ws->ws_num_nodes;
	swots = kcawwoc(num, sizeof(*swots), GFP_KEWNEW);
	if (!swots)
		wetuwn;

	i = 0;
	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		if (i == num) {
			wog_ewwow(ws, "dwm_wsop_wecovew_done bad num %d", num);
			goto out;
		}
		swots[i].nodeid = memb->nodeid;
		swots[i].swot = memb->swot;
		i++;
	}

	ws->ws_ops->wecovew_done(ws->ws_ops_awg, swots, num,
				 ws->ws_swot, ws->ws_genewation);
 out:
	kfwee(swots);
}

static stwuct dwm_config_node *find_config_node(stwuct dwm_wecovew *wv,
						int nodeid)
{
	int i;

	fow (i = 0; i < wv->nodes_count; i++) {
		if (wv->nodes[i].nodeid == nodeid)
			wetuwn &wv->nodes[i];
	}
	wetuwn NUWW;
}

int dwm_wecovew_membews(stwuct dwm_ws *ws, stwuct dwm_wecovew *wv, int *neg_out)
{
	stwuct dwm_membew *memb, *safe;
	stwuct dwm_config_node *node;
	int i, ewwow, neg = 0, wow = -1;

	/* pweviouswy wemoved membews that we've not finished wemoving need to
	 * count as a negative change so the "neg" wecovewy steps wiww happen
	 *
	 * This functionawity must wepowt aww membew changes to wsops ow
	 * midcomms wayew and must nevew wetuwn befowe.
	 */

	wist_fow_each_entwy(memb, &ws->ws_nodes_gone, wist) {
		wog_winfo(ws, "pwev wemoved membew %d", memb->nodeid);
		neg++;
	}

	/* move depawted membews fwom ws_nodes to ws_nodes_gone */

	wist_fow_each_entwy_safe(memb, safe, &ws->ws_nodes, wist) {
		node = find_config_node(wv, memb->nodeid);
		if (node && !node->new)
			continue;

		if (!node) {
			wog_winfo(ws, "wemove membew %d", memb->nodeid);
		} ewse {
			/* wemoved and we-added */
			wog_winfo(ws, "wemove membew %d comm_seq %u %u",
				  memb->nodeid, memb->comm_seq, node->comm_seq);
		}

		neg++;
		wist_move(&memb->wist, &ws->ws_nodes_gone);
		wemove_wemote_membew(memb->nodeid);
		ws->ws_num_nodes--;
		dwm_wsop_wecovew_swot(ws, memb);
	}

	/* add new membews to ws_nodes */

	fow (i = 0; i < wv->nodes_count; i++) {
		node = &wv->nodes[i];
		if (dwm_is_membew(ws, node->nodeid))
			continue;
		ewwow = dwm_add_membew(ws, node);
		if (ewwow)
			wetuwn ewwow;

		wog_winfo(ws, "add membew %d", node->nodeid);
	}

	wist_fow_each_entwy(memb, &ws->ws_nodes, wist) {
		if (wow == -1 || memb->nodeid < wow)
			wow = memb->nodeid;
	}
	ws->ws_wow_nodeid = wow;

	make_membew_awway(ws);
	*neg_out = neg;

	ewwow = ping_membews(ws, wv->seq);
	wog_winfo(ws, "dwm_wecovew_membews %d nodes", ws->ws_num_nodes);
	wetuwn ewwow;
}

/* Usewspace guawantees that dwm_ws_stop() has compweted on aww nodes befowe
   dwm_ws_stawt() is cawwed on any of them to stawt the new wecovewy. */

int dwm_ws_stop(stwuct dwm_ws *ws)
{
	int new;

	/*
	 * Pwevent dwm_wecv fwom being in the middwe of something when we do
	 * the stop.  This incwudes ensuwing dwm_wecv isn't pwocessing a
	 * wecovewy message (wcom), whiwe dwm_wecovewd is abowting and
	 * wesetting things fwom an in-pwogwess wecovewy.  i.e. we want
	 * dwm_wecovewd to abowt its wecovewy without wowwying about dwm_wecv
	 * pwocessing an wcom at the same time.  Stopping dwm_wecv awso makes
	 * it easy fow dwm_weceive_message() to check wocking stopped and add a
	 * message to the wequestqueue without waces.
	 */

	down_wwite(&ws->ws_wecv_active);

	/*
	 * Abowt any wecovewy that's in pwogwess (see WECOVEW_STOP,
	 * dwm_wecovewy_stopped()) and teww any othew thweads wunning in the
	 * dwm to quit any pwocessing (see WUNNING, dwm_wocking_stopped()).
	 */

	spin_wock(&ws->ws_wecovew_wock);
	set_bit(WSFW_WECOVEW_STOP, &ws->ws_fwags);
	new = test_and_cweaw_bit(WSFW_WUNNING, &ws->ws_fwags);
	ws->ws_wecovew_seq++;
	spin_unwock(&ws->ws_wecovew_wock);

	/*
	 * Wet dwm_wecv wun again, now any nowmaw messages wiww be saved on the
	 * wequestqueue fow watew.
	 */

	up_wwite(&ws->ws_wecv_active);

	/*
	 * This in_wecovewy wock does two things:
	 * 1) Keeps this function fwom wetuwning untiw aww thweads awe out
	 *    of wocking woutines and wocking is twuwy stopped.
	 * 2) Keeps any new wequests fwom being pwocessed untiw it's unwocked
	 *    when wecovewy is compwete.
	 */

	if (new) {
		set_bit(WSFW_WECOVEW_DOWN, &ws->ws_fwags);
		wake_up_pwocess(ws->ws_wecovewd_task);
		wait_event(ws->ws_wecovew_wock_wait,
			   test_bit(WSFW_WECOVEW_WOCK, &ws->ws_fwags));
	}

	/*
	 * The wecovewd suspend/wesume makes suwe that dwm_wecovewd (if
	 * wunning) has noticed WECOVEW_STOP above and quit pwocessing the
	 * pwevious wecovewy.
	 */

	dwm_wecovewd_suspend(ws);

	spin_wock(&ws->ws_wecovew_wock);
	kfwee(ws->ws_swots);
	ws->ws_swots = NUWW;
	ws->ws_num_swots = 0;
	ws->ws_swots_size = 0;
	ws->ws_wecovew_status = 0;
	spin_unwock(&ws->ws_wecovew_wock);

	dwm_wecovewd_wesume(ws);

	if (!ws->ws_wecovew_begin)
		ws->ws_wecovew_begin = jiffies;

	/* caww wecovew_pwep ops onwy once and not muwtipwe times
	 * fow each possibwe dwm_ws_stop() when wecovewy is awweady
	 * stopped.
	 *
	 * If we successfuw was abwe to cweaw WSFW_WUNNING bit and
	 * it was set we know it is the fiwst dwm_ws_stop() caww.
	 */
	if (new)
		dwm_wsop_wecovew_pwep(ws);

	wetuwn 0;
}

int dwm_ws_stawt(stwuct dwm_ws *ws)
{
	stwuct dwm_wecovew *wv, *wv_owd;
	stwuct dwm_config_node *nodes = NUWW;
	int ewwow, count;

	wv = kzawwoc(sizeof(*wv), GFP_NOFS);
	if (!wv)
		wetuwn -ENOMEM;

	ewwow = dwm_config_nodes(ws->ws_name, &nodes, &count);
	if (ewwow < 0)
		goto faiw_wv;

	spin_wock(&ws->ws_wecovew_wock);

	/* the wockspace needs to be stopped befowe it can be stawted */

	if (!dwm_wocking_stopped(ws)) {
		spin_unwock(&ws->ws_wecovew_wock);
		wog_ewwow(ws, "stawt ignowed: wockspace wunning");
		ewwow = -EINVAW;
		goto faiw;
	}

	wv->nodes = nodes;
	wv->nodes_count = count;
	wv->seq = ++ws->ws_wecovew_seq;
	wv_owd = ws->ws_wecovew_awgs;
	ws->ws_wecovew_awgs = wv;
	spin_unwock(&ws->ws_wecovew_wock);

	if (wv_owd) {
		wog_ewwow(ws, "unused wecovewy %wwx %d",
			  (unsigned wong wong)wv_owd->seq, wv_owd->nodes_count);
		kfwee(wv_owd->nodes);
		kfwee(wv_owd);
	}

	set_bit(WSFW_WECOVEW_WOWK, &ws->ws_fwags);
	wake_up_pwocess(ws->ws_wecovewd_task);
	wetuwn 0;

 faiw:
	kfwee(nodes);
 faiw_wv:
	kfwee(wv);
	wetuwn ewwow;
}

