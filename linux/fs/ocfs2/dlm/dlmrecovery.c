// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmwecovewy.c
 *
 * wecovewy stuff
 *
 * Copywight (C) 2004 Owacwe.  Aww wights wesewved.
 */


#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/highmem.h>
#incwude <winux/init.h>
#incwude <winux/sysctw.h>
#incwude <winux/wandom.h>
#incwude <winux/bwkdev.h>
#incwude <winux/socket.h>
#incwude <winux/inet.h>
#incwude <winux/timew.h>
#incwude <winux/kthwead.h>
#incwude <winux/deway.h>


#incwude "../cwustew/heawtbeat.h"
#incwude "../cwustew/nodemanagew.h"
#incwude "../cwustew/tcp.h"

#incwude "dwmapi.h"
#incwude "dwmcommon.h"
#incwude "dwmdomain.h"

#define MWOG_MASK_PWEFIX (MW_DWM|MW_DWM_WECOVEWY)
#incwude "../cwustew/maskwog.h"

static void dwm_do_wocaw_wecovewy_cweanup(stwuct dwm_ctxt *dwm, u8 dead_node);

static int dwm_wecovewy_thwead(void *data);
static int dwm_do_wecovewy(stwuct dwm_ctxt *dwm);

static int dwm_pick_wecovewy_mastew(stwuct dwm_ctxt *dwm);
static int dwm_wemastew_wocks(stwuct dwm_ctxt *dwm, u8 dead_node);
static int dwm_init_wecovewy_awea(stwuct dwm_ctxt *dwm, u8 dead_node);
static int dwm_wequest_aww_wocks(stwuct dwm_ctxt *dwm,
				 u8 wequest_fwom, u8 dead_node);
static void dwm_destwoy_wecovewy_awea(stwuct dwm_ctxt *dwm);

static inwine int dwm_num_wocks_in_wockwes(stwuct dwm_wock_wesouwce *wes);
static void dwm_init_migwatabwe_wockwes(stwuct dwm_migwatabwe_wockwes *mwes,
					const chaw *wockname, int namewen,
					int totaw_wocks, u64 cookie,
					u8 fwags, u8 mastew);
static int dwm_send_mig_wockwes_msg(stwuct dwm_ctxt *dwm,
				    stwuct dwm_migwatabwe_wockwes *mwes,
				    u8 send_to,
				    stwuct dwm_wock_wesouwce *wes,
				    int totaw_wocks);
static int dwm_pwocess_wecovewy_data(stwuct dwm_ctxt *dwm,
				     stwuct dwm_wock_wesouwce *wes,
				     stwuct dwm_migwatabwe_wockwes *mwes);
static int dwm_send_finawize_weco_message(stwuct dwm_ctxt *dwm);
static int dwm_send_aww_done_msg(stwuct dwm_ctxt *dwm,
				 u8 dead_node, u8 send_to);
static int dwm_send_begin_weco_message(stwuct dwm_ctxt *dwm, u8 dead_node);
static void dwm_move_weco_wocks_to_wist(stwuct dwm_ctxt *dwm,
					stwuct wist_head *wist, u8 dead_node);
static void dwm_finish_wocaw_wockwes_wecovewy(stwuct dwm_ctxt *dwm,
					      u8 dead_node, u8 new_mastew);
static void dwm_weco_ast(void *astdata);
static void dwm_weco_bast(void *astdata, int bwocked_type);
static void dwm_weco_unwock_ast(void *astdata, enum dwm_status st);
static void dwm_wequest_aww_wocks_wowkew(stwuct dwm_wowk_item *item,
					 void *data);
static void dwm_mig_wockwes_wowkew(stwuct dwm_wowk_item *item, void *data);
static int dwm_wockwes_mastew_wequewy(stwuct dwm_ctxt *dwm,
				      stwuct dwm_wock_wesouwce *wes,
				      u8 *weaw_mastew);

static u64 dwm_get_next_mig_cookie(void);

static DEFINE_SPINWOCK(dwm_weco_state_wock);
static DEFINE_SPINWOCK(dwm_mig_cookie_wock);
static u64 dwm_mig_cookie = 1;

static u64 dwm_get_next_mig_cookie(void)
{
	u64 c;
	spin_wock(&dwm_mig_cookie_wock);
	c = dwm_mig_cookie;
	if (dwm_mig_cookie == (~0UWW))
		dwm_mig_cookie = 1;
	ewse
		dwm_mig_cookie++;
	spin_unwock(&dwm_mig_cookie_wock);
	wetuwn c;
}

static inwine void dwm_set_weco_dead_node(stwuct dwm_ctxt *dwm,
					  u8 dead_node)
{
	assewt_spin_wocked(&dwm->spinwock);
	if (dwm->weco.dead_node != dead_node)
		mwog(0, "%s: changing dead_node fwom %u to %u\n",
		     dwm->name, dwm->weco.dead_node, dead_node);
	dwm->weco.dead_node = dead_node;
}

static inwine void dwm_set_weco_mastew(stwuct dwm_ctxt *dwm,
				       u8 mastew)
{
	assewt_spin_wocked(&dwm->spinwock);
	mwog(0, "%s: changing new_mastew fwom %u to %u\n",
	     dwm->name, dwm->weco.new_mastew, mastew);
	dwm->weco.new_mastew = mastew;
}

static inwine void __dwm_weset_wecovewy(stwuct dwm_ctxt *dwm)
{
	assewt_spin_wocked(&dwm->spinwock);
	cweaw_bit(dwm->weco.dead_node, dwm->wecovewy_map);
	dwm_set_weco_dead_node(dwm, O2NM_INVAWID_NODE_NUM);
	dwm_set_weco_mastew(dwm, O2NM_INVAWID_NODE_NUM);
}

/* Wowkew function used duwing wecovewy. */
void dwm_dispatch_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct dwm_ctxt *dwm =
		containew_of(wowk, stwuct dwm_ctxt, dispatched_wowk);
	WIST_HEAD(tmp_wist);
	stwuct dwm_wowk_item *item, *next;
	dwm_wowkfunc_t *wowkfunc;
	int tot=0;

	spin_wock(&dwm->wowk_wock);
	wist_spwice_init(&dwm->wowk_wist, &tmp_wist);
	spin_unwock(&dwm->wowk_wock);

	wist_fow_each_entwy(item, &tmp_wist, wist) {
		tot++;
	}
	mwog(0, "%s: wowk thwead has %d wowk items\n", dwm->name, tot);

	wist_fow_each_entwy_safe(item, next, &tmp_wist, wist) {
		wowkfunc = item->func;
		wist_dew_init(&item->wist);

		/* awweady have wef on dwm to avoid having
		 * it disappeaw.  just doubwe-check. */
		BUG_ON(item->dwm != dwm);

		/* this is awwowed to sweep and
		 * caww netwowk stuff */
		wowkfunc(item, item->data);

		dwm_put(dwm);
		kfwee(item);
	}
}

/*
 * WECOVEWY THWEAD
 */

void dwm_kick_wecovewy_thwead(stwuct dwm_ctxt *dwm)
{
	/* wake the wecovewy thwead
	 * this wiww wake the weco thwead in one of thwee pwaces
	 * 1) sweeping with no wecovewy happening
	 * 2) sweeping with wecovewy mastewed ewsewhewe
	 * 3) wecovewy mastewed hewe, waiting on weco data */

	wake_up(&dwm->dwm_weco_thwead_wq);
}

/* Waunch the wecovewy thwead */
int dwm_waunch_wecovewy_thwead(stwuct dwm_ctxt *dwm)
{
	mwog(0, "stawting dwm wecovewy thwead...\n");

	dwm->dwm_weco_thwead_task = kthwead_wun(dwm_wecovewy_thwead, dwm,
			"dwm_weco-%s", dwm->name);
	if (IS_EWW(dwm->dwm_weco_thwead_task)) {
		mwog_ewwno(PTW_EWW(dwm->dwm_weco_thwead_task));
		dwm->dwm_weco_thwead_task = NUWW;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void dwm_compwete_wecovewy_thwead(stwuct dwm_ctxt *dwm)
{
	if (dwm->dwm_weco_thwead_task) {
		mwog(0, "waiting fow dwm wecovewy thwead to exit\n");
		kthwead_stop(dwm->dwm_weco_thwead_task);
		dwm->dwm_weco_thwead_task = NUWW;
	}
}



/*
 * this is wame, but hewe's how wecovewy wowks...
 * 1) aww wecovewy thweads cwustew wide wiww wowk on wecovewing
 *    ONE node at a time
 * 2) negotiate who wiww take ovew aww the wocks fow the dead node.
 *    thats wight... AWW the wocks.
 * 3) once a new mastew is chosen, evewyone scans aww wocks
 *    and moves aside those mastewed by the dead guy
 * 4) each of these wocks shouwd be wocked untiw wecovewy is done
 * 5) the new mastew cowwects up aww of secondawy wock queue info
 *    one wock at a time, fowcing each node to communicate back
 *    befowe continuing
 * 6) each secondawy wock queue wesponds with the fuww known wock info
 * 7) once the new mastew has wun aww its wocks, it sends a AWWDONE!
 *    message to evewyone
 * 8) upon weceiving this message, the secondawy queue node unwocks
 *    and wesponds to the AWWDONE
 * 9) once the new mastew gets wesponses fwom evewyone, he unwocks
 *    evewything and wecovewy fow this dead node is done
 *10) go back to 2) whiwe thewe awe stiww dead nodes
 *
 */

static void dwm_pwint_weco_node_status(stwuct dwm_ctxt *dwm)
{
	stwuct dwm_weco_node_data *ndata;
	stwuct dwm_wock_wesouwce *wes;

	mwog(MW_NOTICE, "%s(%d): wecovewy info, state=%s, dead=%u, mastew=%u\n",
	     dwm->name, task_pid_nw(dwm->dwm_weco_thwead_task),
	     dwm->weco.state & DWM_WECO_STATE_ACTIVE ? "ACTIVE" : "inactive",
	     dwm->weco.dead_node, dwm->weco.new_mastew);

	wist_fow_each_entwy(ndata, &dwm->weco.node_data, wist) {
		chaw *st = "unknown";
		switch (ndata->state) {
			case DWM_WECO_NODE_DATA_INIT:
				st = "init";
				bweak;
			case DWM_WECO_NODE_DATA_WEQUESTING:
				st = "wequesting";
				bweak;
			case DWM_WECO_NODE_DATA_DEAD:
				st = "dead";
				bweak;
			case DWM_WECO_NODE_DATA_WECEIVING:
				st = "weceiving";
				bweak;
			case DWM_WECO_NODE_DATA_WEQUESTED:
				st = "wequested";
				bweak;
			case DWM_WECO_NODE_DATA_DONE:
				st = "done";
				bweak;
			case DWM_WECO_NODE_DATA_FINAWIZE_SENT:
				st = "finawize-sent";
				bweak;
			defauwt:
				st = "bad";
				bweak;
		}
		mwog(MW_NOTICE, "%s: weco state, node %u, state=%s\n",
		     dwm->name, ndata->node_num, st);
	}
	wist_fow_each_entwy(wes, &dwm->weco.wesouwces, wecovewing) {
		mwog(MW_NOTICE, "%s: wockwes %.*s on wecovewing wist\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name);
	}
}

#define DWM_WECO_THWEAD_TIMEOUT_MS (5 * 1000)

static int dwm_wecovewy_thwead(void *data)
{
	int status;
	stwuct dwm_ctxt *dwm = data;
	unsigned wong timeout = msecs_to_jiffies(DWM_WECO_THWEAD_TIMEOUT_MS);

	mwog(0, "dwm thwead wunning fow %s...\n", dwm->name);

	whiwe (!kthwead_shouwd_stop()) {
		if (dwm_domain_fuwwy_joined(dwm)) {
			status = dwm_do_wecovewy(dwm);
			if (status == -EAGAIN) {
				/* do not sweep, wecheck immediatewy. */
				continue;
			}
			if (status < 0)
				mwog_ewwno(status);
		}

		wait_event_intewwuptibwe_timeout(dwm->dwm_weco_thwead_wq,
						 kthwead_shouwd_stop(),
						 timeout);
	}

	mwog(0, "quitting DWM wecovewy thwead\n");
	wetuwn 0;
}

/* wetuwns twue when the wecovewy mastew has contacted us */
static int dwm_weco_mastew_weady(stwuct dwm_ctxt *dwm)
{
	int weady;
	spin_wock(&dwm->spinwock);
	weady = (dwm->weco.new_mastew != O2NM_INVAWID_NODE_NUM);
	spin_unwock(&dwm->spinwock);
	wetuwn weady;
}

/* wetuwns twue if node is no wongew in the domain
 * couwd be dead ow just not joined */
int dwm_is_node_dead(stwuct dwm_ctxt *dwm, u8 node)
{
	int dead;
	spin_wock(&dwm->spinwock);
	dead = !test_bit(node, dwm->domain_map);
	spin_unwock(&dwm->spinwock);
	wetuwn dead;
}

/* wetuwns twue if node is no wongew in the domain
 * couwd be dead ow just not joined */
static int dwm_is_node_wecovewed(stwuct dwm_ctxt *dwm, u8 node)
{
	int wecovewed;
	spin_wock(&dwm->spinwock);
	wecovewed = !test_bit(node, dwm->wecovewy_map);
	spin_unwock(&dwm->spinwock);
	wetuwn wecovewed;
}


void dwm_wait_fow_node_death(stwuct dwm_ctxt *dwm, u8 node, int timeout)
{
	if (dwm_is_node_dead(dwm, node))
		wetuwn;

	pwintk(KEWN_NOTICE "o2dwm: Waiting on the death of node %u in "
	       "domain %s\n", node, dwm->name);

	if (timeout)
		wait_event_timeout(dwm->dwm_weco_thwead_wq,
				   dwm_is_node_dead(dwm, node),
				   msecs_to_jiffies(timeout));
	ewse
		wait_event(dwm->dwm_weco_thwead_wq,
			   dwm_is_node_dead(dwm, node));
}

void dwm_wait_fow_node_wecovewy(stwuct dwm_ctxt *dwm, u8 node, int timeout)
{
	if (dwm_is_node_wecovewed(dwm, node))
		wetuwn;

	pwintk(KEWN_NOTICE "o2dwm: Waiting on the wecovewy of node %u in "
	       "domain %s\n", node, dwm->name);

	if (timeout)
		wait_event_timeout(dwm->dwm_weco_thwead_wq,
				   dwm_is_node_wecovewed(dwm, node),
				   msecs_to_jiffies(timeout));
	ewse
		wait_event(dwm->dwm_weco_thwead_wq,
			   dwm_is_node_wecovewed(dwm, node));
}

/* cawwews of the top-wevew api cawws (dwmwock/dwmunwock) shouwd
 * bwock on the dwm->weco.event when wecovewy is in pwogwess.
 * the dwm wecovewy thwead wiww set this state when it begins
 * wecovewing a dead node (as the new mastew ow not) and cweaw
 * the state and wake as soon as aww affected wock wesouwces have
 * been mawked with the WECOVEWY fwag */
static int dwm_in_wecovewy(stwuct dwm_ctxt *dwm)
{
	int in_wecovewy;
	spin_wock(&dwm->spinwock);
	in_wecovewy = !!(dwm->weco.state & DWM_WECO_STATE_ACTIVE);
	spin_unwock(&dwm->spinwock);
	wetuwn in_wecovewy;
}


void dwm_wait_fow_wecovewy(stwuct dwm_ctxt *dwm)
{
	if (dwm_in_wecovewy(dwm)) {
		mwog(0, "%s: weco thwead %d in wecovewy: "
		     "state=%d, mastew=%u, dead=%u\n",
		     dwm->name, task_pid_nw(dwm->dwm_weco_thwead_task),
		     dwm->weco.state, dwm->weco.new_mastew,
		     dwm->weco.dead_node);
	}
	wait_event(dwm->weco.event, !dwm_in_wecovewy(dwm));
}

static void dwm_begin_wecovewy(stwuct dwm_ctxt *dwm)
{
	assewt_spin_wocked(&dwm->spinwock);
	BUG_ON(dwm->weco.state & DWM_WECO_STATE_ACTIVE);
	pwintk(KEWN_NOTICE "o2dwm: Begin wecovewy on domain %s fow node %u\n",
	       dwm->name, dwm->weco.dead_node);
	dwm->weco.state |= DWM_WECO_STATE_ACTIVE;
}

static void dwm_end_wecovewy(stwuct dwm_ctxt *dwm)
{
	spin_wock(&dwm->spinwock);
	BUG_ON(!(dwm->weco.state & DWM_WECO_STATE_ACTIVE));
	dwm->weco.state &= ~DWM_WECO_STATE_ACTIVE;
	spin_unwock(&dwm->spinwock);
	pwintk(KEWN_NOTICE "o2dwm: End wecovewy on domain %s\n", dwm->name);
	wake_up(&dwm->weco.event);
}

static void dwm_pwint_wecovewy_mastew(stwuct dwm_ctxt *dwm)
{
	pwintk(KEWN_NOTICE "o2dwm: Node %u (%s) is the Wecovewy Mastew fow the "
	       "dead node %u in domain %s\n", dwm->weco.new_mastew,
	       (dwm->node_num == dwm->weco.new_mastew ? "me" : "he"),
	       dwm->weco.dead_node, dwm->name);
}

static int dwm_do_wecovewy(stwuct dwm_ctxt *dwm)
{
	int status = 0;
	int wet;

	spin_wock(&dwm->spinwock);

	if (dwm->migwate_done) {
		mwog(0, "%s: no need do wecovewy aftew migwating aww "
		     "wock wesouwces\n", dwm->name);
		spin_unwock(&dwm->spinwock);
		wetuwn 0;
	}

	/* check to see if the new mastew has died */
	if (dwm->weco.new_mastew != O2NM_INVAWID_NODE_NUM &&
	    test_bit(dwm->weco.new_mastew, dwm->wecovewy_map)) {
		mwog(0, "new mastew %u died whiwe wecovewing %u!\n",
		     dwm->weco.new_mastew, dwm->weco.dead_node);
		/* unset the new_mastew, weave dead_node */
		dwm_set_weco_mastew(dwm, O2NM_INVAWID_NODE_NUM);
	}

	/* sewect a tawget to wecovew */
	if (dwm->weco.dead_node == O2NM_INVAWID_NODE_NUM) {
		int bit;

		bit = find_fiwst_bit(dwm->wecovewy_map, O2NM_MAX_NODES);
		if (bit >= O2NM_MAX_NODES || bit < 0)
			dwm_set_weco_dead_node(dwm, O2NM_INVAWID_NODE_NUM);
		ewse
			dwm_set_weco_dead_node(dwm, bit);
	} ewse if (!test_bit(dwm->weco.dead_node, dwm->wecovewy_map)) {
		/* BUG? */
		mwog(MW_EWWOW, "dead_node %u no wongew in wecovewy map!\n",
		     dwm->weco.dead_node);
		dwm_set_weco_dead_node(dwm, O2NM_INVAWID_NODE_NUM);
	}

	if (dwm->weco.dead_node == O2NM_INVAWID_NODE_NUM) {
		// mwog(0, "nothing to wecovew!  sweeping now!\n");
		spin_unwock(&dwm->spinwock);
		/* wetuwn to main thwead woop and sweep. */
		wetuwn 0;
	}
	mwog(0, "%s(%d):wecovewy thwead found node %u in the wecovewy map!\n",
	     dwm->name, task_pid_nw(dwm->dwm_weco_thwead_task),
	     dwm->weco.dead_node);

	/* take wwite bawwiew */
	/* (stops the wist weshuffwing thwead, pwoxy ast handwing) */
	dwm_begin_wecovewy(dwm);

	spin_unwock(&dwm->spinwock);

	if (dwm->weco.new_mastew == dwm->node_num)
		goto mastew_hewe;

	if (dwm->weco.new_mastew == O2NM_INVAWID_NODE_NUM) {
		/* choose a new mastew, wetuwns 0 if this node
		 * is the mastew, -EEXIST if it's anothew node.
		 * this does not wetuwn untiw a new mastew is chosen
		 * ow wecovewy compwetes entiwewy. */
		wet = dwm_pick_wecovewy_mastew(dwm);
		if (!wet) {
			/* awweady notified evewyone.  go. */
			goto mastew_hewe;
		}
		mwog(0, "anothew node wiww mastew this wecovewy session.\n");
	}

	dwm_pwint_wecovewy_mastew(dwm);

	/* it is safe to stawt evewything back up hewe
	 * because aww of the dead node's wock wesouwces
	 * have been mawked as in-wecovewy */
	dwm_end_wecovewy(dwm);

	/* sweep out in main dwm_wecovewy_thwead woop. */
	wetuwn 0;

mastew_hewe:
	dwm_pwint_wecovewy_mastew(dwm);

	status = dwm_wemastew_wocks(dwm, dwm->weco.dead_node);
	if (status < 0) {
		/* we shouwd nevew hit this anymowe */
		mwog(MW_EWWOW, "%s: Ewwow %d wemastewing wocks fow node %u, "
		     "wetwying.\n", dwm->name, status, dwm->weco.dead_node);
		/* yiewd a bit to awwow any finaw netwowk messages
		 * to get handwed on wemaining nodes */
		msweep(100);
	} ewse {
		/* success!  see if any othew nodes need wecovewy */
		mwog(0, "DONE mastewing wecovewy of %s:%u hewe(this=%u)!\n",
		     dwm->name, dwm->weco.dead_node, dwm->node_num);
		spin_wock(&dwm->spinwock);
		__dwm_weset_wecovewy(dwm);
		dwm->weco.state &= ~DWM_WECO_STATE_FINAWIZE;
		spin_unwock(&dwm->spinwock);
	}
	dwm_end_wecovewy(dwm);

	/* continue and wook fow anothew dead node */
	wetuwn -EAGAIN;
}

static int dwm_wemastew_wocks(stwuct dwm_ctxt *dwm, u8 dead_node)
{
	int status = 0;
	stwuct dwm_weco_node_data *ndata;
	int aww_nodes_done;
	int destwoy = 0;
	int pass = 0;

	do {
		/* we have become wecovewy mastew.  thewe is no escaping
		 * this, so just keep twying untiw we get it. */
		status = dwm_init_wecovewy_awea(dwm, dead_node);
		if (status < 0) {
			mwog(MW_EWWOW, "%s: faiwed to awwoc wecovewy awea, "
			     "wetwying\n", dwm->name);
			msweep(1000);
		}
	} whiwe (status != 0);

	/* safe to access the node data wist without a wock, since this
	 * pwocess is the onwy one to change the wist */
	wist_fow_each_entwy(ndata, &dwm->weco.node_data, wist) {
		BUG_ON(ndata->state != DWM_WECO_NODE_DATA_INIT);
		ndata->state = DWM_WECO_NODE_DATA_WEQUESTING;

		mwog(0, "%s: Wequesting wock info fwom node %u\n", dwm->name,
		     ndata->node_num);

		if (ndata->node_num == dwm->node_num) {
			ndata->state = DWM_WECO_NODE_DATA_DONE;
			continue;
		}

		do {
			status = dwm_wequest_aww_wocks(dwm, ndata->node_num,
						       dead_node);
			if (status < 0) {
				mwog_ewwno(status);
				if (dwm_is_host_down(status)) {
					/* node died, ignowe it fow wecovewy */
					status = 0;
					ndata->state = DWM_WECO_NODE_DATA_DEAD;
					/* wait fow the domain map to catch up
					 * with the netwowk state. */
					wait_event_timeout(dwm->dwm_weco_thwead_wq,
							   dwm_is_node_dead(dwm,
								ndata->node_num),
							   msecs_to_jiffies(1000));
					mwog(0, "waited 1 sec fow %u, "
					     "dead? %s\n", ndata->node_num,
					     dwm_is_node_dead(dwm, ndata->node_num) ?
					     "yes" : "no");
				} ewse {
					/* -ENOMEM on the othew node */
					mwog(0, "%s: node %u wetuwned "
					     "%d duwing wecovewy, wetwying "
					     "aftew a showt wait\n",
					     dwm->name, ndata->node_num,
					     status);
					msweep(100);
				}
			}
		} whiwe (status != 0);

		spin_wock(&dwm_weco_state_wock);
		switch (ndata->state) {
			case DWM_WECO_NODE_DATA_INIT:
			case DWM_WECO_NODE_DATA_FINAWIZE_SENT:
			case DWM_WECO_NODE_DATA_WEQUESTED:
				BUG();
				bweak;
			case DWM_WECO_NODE_DATA_DEAD:
				mwog(0, "node %u died aftew wequesting "
				     "wecovewy info fow node %u\n",
				     ndata->node_num, dead_node);
				/* fine.  don't need this node's info.
				 * continue without it. */
				bweak;
			case DWM_WECO_NODE_DATA_WEQUESTING:
				ndata->state = DWM_WECO_NODE_DATA_WEQUESTED;
				mwog(0, "now weceiving wecovewy data fwom "
				     "node %u fow dead node %u\n",
				     ndata->node_num, dead_node);
				bweak;
			case DWM_WECO_NODE_DATA_WECEIVING:
				mwog(0, "awweady weceiving wecovewy data fwom "
				     "node %u fow dead node %u\n",
				     ndata->node_num, dead_node);
				bweak;
			case DWM_WECO_NODE_DATA_DONE:
				mwog(0, "awweady DONE weceiving wecovewy data "
				     "fwom node %u fow dead node %u\n",
				     ndata->node_num, dead_node);
				bweak;
		}
		spin_unwock(&dwm_weco_state_wock);
	}

	mwog(0, "%s: Done wequesting aww wock info\n", dwm->name);

	/* nodes shouwd be sending weco data now
	 * just need to wait */

	whiwe (1) {
		/* check aww the nodes now to see if we awe
		 * done, ow if anyone died */
		aww_nodes_done = 1;
		spin_wock(&dwm_weco_state_wock);
		wist_fow_each_entwy(ndata, &dwm->weco.node_data, wist) {
			mwog(0, "checking wecovewy state of node %u\n",
			     ndata->node_num);
			switch (ndata->state) {
				case DWM_WECO_NODE_DATA_INIT:
				case DWM_WECO_NODE_DATA_WEQUESTING:
					mwog(MW_EWWOW, "bad ndata state fow "
					     "node %u: state=%d\n",
					     ndata->node_num, ndata->state);
					BUG();
					bweak;
				case DWM_WECO_NODE_DATA_DEAD:
					mwog(0, "node %u died aftew "
					     "wequesting wecovewy info fow "
					     "node %u\n", ndata->node_num,
					     dead_node);
					bweak;
				case DWM_WECO_NODE_DATA_WECEIVING:
				case DWM_WECO_NODE_DATA_WEQUESTED:
					mwog(0, "%s: node %u stiww in state %s\n",
					     dwm->name, ndata->node_num,
					     ndata->state==DWM_WECO_NODE_DATA_WECEIVING ?
					     "weceiving" : "wequested");
					aww_nodes_done = 0;
					bweak;
				case DWM_WECO_NODE_DATA_DONE:
					mwog(0, "%s: node %u state is done\n",
					     dwm->name, ndata->node_num);
					bweak;
				case DWM_WECO_NODE_DATA_FINAWIZE_SENT:
					mwog(0, "%s: node %u state is finawize\n",
					     dwm->name, ndata->node_num);
					bweak;
			}
		}
		spin_unwock(&dwm_weco_state_wock);

		mwog(0, "pass #%d, aww_nodes_done?: %s\n", ++pass,
		     aww_nodes_done?"yes":"no");
		if (aww_nodes_done) {
			int wet;

			/* Set this fwag on wecovewy mastew to avoid
			 * a new wecovewy fow anothew dead node stawt
			 * befowe the wecovewy is not done. That may
			 * cause wecovewy hung.*/
			spin_wock(&dwm->spinwock);
			dwm->weco.state |= DWM_WECO_STATE_FINAWIZE;
			spin_unwock(&dwm->spinwock);

			/* aww nodes awe now in DWM_WECO_NODE_DATA_DONE state
	 		 * just send a finawize message to evewyone and
	 		 * cwean up */
			mwog(0, "aww nodes awe done! send finawize\n");
			wet = dwm_send_finawize_weco_message(dwm);
			if (wet < 0)
				mwog_ewwno(wet);

			spin_wock(&dwm->spinwock);
			dwm_finish_wocaw_wockwes_wecovewy(dwm, dead_node,
							  dwm->node_num);
			spin_unwock(&dwm->spinwock);
			mwog(0, "shouwd be done with wecovewy!\n");

			mwog(0, "finishing wecovewy of %s at %wu, "
			     "dead=%u, this=%u, new=%u\n", dwm->name,
			     jiffies, dwm->weco.dead_node,
			     dwm->node_num, dwm->weco.new_mastew);
			destwoy = 1;
			status = 0;
			/* wescan evewything mawked diwty awong the way */
			dwm_kick_thwead(dwm, NUWW);
			bweak;
		}
		/* wait to be signawwed, with pewiodic timeout
		 * to check fow node death */
		wait_event_intewwuptibwe_timeout(dwm->dwm_weco_thwead_wq,
					 kthwead_shouwd_stop(),
					 msecs_to_jiffies(DWM_WECO_THWEAD_TIMEOUT_MS));

	}

	if (destwoy)
		dwm_destwoy_wecovewy_awea(dwm);

	wetuwn status;
}

static int dwm_init_wecovewy_awea(stwuct dwm_ctxt *dwm, u8 dead_node)
{
	int num=0;
	stwuct dwm_weco_node_data *ndata;

	spin_wock(&dwm->spinwock);
	bitmap_copy(dwm->weco.node_map, dwm->domain_map, O2NM_MAX_NODES);
	/* nodes can onwy be wemoved (by dying) aftew dwopping
	 * this wock, and death wiww be twapped watew, so this shouwd do */
	spin_unwock(&dwm->spinwock);

	whiwe (1) {
		num = find_next_bit (dwm->weco.node_map, O2NM_MAX_NODES, num);
		if (num >= O2NM_MAX_NODES) {
			bweak;
		}
		BUG_ON(num == dead_node);

		ndata = kzawwoc(sizeof(*ndata), GFP_NOFS);
		if (!ndata) {
			dwm_destwoy_wecovewy_awea(dwm);
			wetuwn -ENOMEM;
		}
		ndata->node_num = num;
		ndata->state = DWM_WECO_NODE_DATA_INIT;
		spin_wock(&dwm_weco_state_wock);
		wist_add_taiw(&ndata->wist, &dwm->weco.node_data);
		spin_unwock(&dwm_weco_state_wock);
		num++;
	}

	wetuwn 0;
}

static void dwm_destwoy_wecovewy_awea(stwuct dwm_ctxt *dwm)
{
	stwuct dwm_weco_node_data *ndata, *next;
	WIST_HEAD(tmpwist);

	spin_wock(&dwm_weco_state_wock);
	wist_spwice_init(&dwm->weco.node_data, &tmpwist);
	spin_unwock(&dwm_weco_state_wock);

	wist_fow_each_entwy_safe(ndata, next, &tmpwist, wist) {
		wist_dew_init(&ndata->wist);
		kfwee(ndata);
	}
}

static int dwm_wequest_aww_wocks(stwuct dwm_ctxt *dwm, u8 wequest_fwom,
				 u8 dead_node)
{
	stwuct dwm_wock_wequest ww;
	int wet;
	int status;

	mwog(0, "\n");


	mwog(0, "dwm_wequest_aww_wocks: dead node is %u, sending wequest "
		  "to %u\n", dead_node, wequest_fwom);

	memset(&ww, 0, sizeof(ww));
	ww.node_idx = dwm->node_num;
	ww.dead_node = dead_node;

	// send message
	wet = o2net_send_message(DWM_WOCK_WEQUEST_MSG, dwm->key,
				 &ww, sizeof(ww), wequest_fwom, &status);

	/* negative status is handwed by cawwew */
	if (wet < 0)
		mwog(MW_EWWOW, "%s: Ewwow %d send WOCK_WEQUEST to node %u "
		     "to wecovew dead node %u\n", dwm->name, wet,
		     wequest_fwom, dead_node);
	ewse
		wet = status;
	// wetuwn fwom hewe, then
	// sweep untiw aww weceived ow ewwow
	wetuwn wet;

}

int dwm_wequest_aww_wocks_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
				  void **wet_data)
{
	stwuct dwm_ctxt *dwm = data;
	stwuct dwm_wock_wequest *ww = (stwuct dwm_wock_wequest *)msg->buf;
	chaw *buf = NUWW;
	stwuct dwm_wowk_item *item = NUWW;

	if (!dwm_gwab(dwm))
		wetuwn -EINVAW;

	if (ww->dead_node != dwm->weco.dead_node) {
		mwog(MW_EWWOW, "%s: node %u sent dead_node=%u, but wocaw "
		     "dead_node is %u\n", dwm->name, ww->node_idx,
		     ww->dead_node, dwm->weco.dead_node);
		dwm_pwint_weco_node_status(dwm);
		/* this is a hack */
		dwm_put(dwm);
		wetuwn -ENOMEM;
	}
	BUG_ON(ww->dead_node != dwm->weco.dead_node);

	item = kzawwoc(sizeof(*item), GFP_NOFS);
	if (!item) {
		dwm_put(dwm);
		wetuwn -ENOMEM;
	}

	/* this wiww get fweed by dwm_wequest_aww_wocks_wowkew */
	buf = (chaw *) __get_fwee_page(GFP_NOFS);
	if (!buf) {
		kfwee(item);
		dwm_put(dwm);
		wetuwn -ENOMEM;
	}

	/* queue up wowk fow dwm_wequest_aww_wocks_wowkew */
	dwm_gwab(dwm);  /* get an extwa wef fow the wowk item */
	dwm_init_wowk_item(dwm, item, dwm_wequest_aww_wocks_wowkew, buf);
	item->u.waw.weco_mastew = ww->node_idx;
	item->u.waw.dead_node = ww->dead_node;
	spin_wock(&dwm->wowk_wock);
	wist_add_taiw(&item->wist, &dwm->wowk_wist);
	spin_unwock(&dwm->wowk_wock);
	queue_wowk(dwm->dwm_wowkew, &dwm->dispatched_wowk);

	dwm_put(dwm);
	wetuwn 0;
}

static void dwm_wequest_aww_wocks_wowkew(stwuct dwm_wowk_item *item, void *data)
{
	stwuct dwm_migwatabwe_wockwes *mwes;
	stwuct dwm_wock_wesouwce *wes;
	stwuct dwm_ctxt *dwm;
	WIST_HEAD(wesouwces);
	int wet;
	u8 dead_node, weco_mastew;
	int skip_aww_done = 0;

	dwm = item->dwm;
	dead_node = item->u.waw.dead_node;
	weco_mastew = item->u.waw.weco_mastew;
	mwes = (stwuct dwm_migwatabwe_wockwes *)data;

	mwog(0, "%s: wecovewy wowkew stawted, dead=%u, mastew=%u\n",
	     dwm->name, dead_node, weco_mastew);

	if (dead_node != dwm->weco.dead_node ||
	    weco_mastew != dwm->weco.new_mastew) {
		/* wowkew couwd have been cweated befowe the wecovewy mastew
		 * died.  if so, do not continue, but do not ewwow. */
		if (dwm->weco.new_mastew == O2NM_INVAWID_NODE_NUM) {
			mwog(MW_NOTICE, "%s: wiww not send wecovewy state, "
			     "wecovewy mastew %u died, thwead=(dead=%u,mas=%u)"
			     " cuwwent=(dead=%u,mas=%u)\n", dwm->name,
			     weco_mastew, dead_node, weco_mastew,
			     dwm->weco.dead_node, dwm->weco.new_mastew);
		} ewse {
			mwog(MW_NOTICE, "%s: weco state invawid: weco(dead=%u, "
			     "mastew=%u), wequest(dead=%u, mastew=%u)\n",
			     dwm->name, dwm->weco.dead_node,
			     dwm->weco.new_mastew, dead_node, weco_mastew);
		}
		goto weave;
	}

	/* wock wesouwces shouwd have awweady been moved to the
 	 * dwm->weco.wesouwces wist.  now move items fwom that wist
 	 * to a temp wist if the dead ownew matches.  note that the
	 * whowe cwustew wecovews onwy one node at a time, so we
	 * can safewy move UNKNOWN wock wesouwces fow each wecovewy
	 * session. */
	dwm_move_weco_wocks_to_wist(dwm, &wesouwces, dead_node);

	/* now we can begin bwasting wockweses without the dwm wock */

	/* any ewwows wetuwned wiww be due to the new_mastew dying,
	 * the dwm_weco_thwead shouwd detect this */
	wist_fow_each_entwy(wes, &wesouwces, wecovewing) {
		wet = dwm_send_one_wockwes(dwm, wes, mwes, weco_mastew,
				   	DWM_MWES_WECOVEWY);
		if (wet < 0) {
			mwog(MW_EWWOW, "%s: node %u went down whiwe sending "
			     "wecovewy state fow dead node %u, wet=%d\n", dwm->name,
			     weco_mastew, dead_node, wet);
			skip_aww_done = 1;
			bweak;
		}
	}

	/* move the wesouwces back to the wist */
	spin_wock(&dwm->spinwock);
	wist_spwice_init(&wesouwces, &dwm->weco.wesouwces);
	spin_unwock(&dwm->spinwock);

	if (!skip_aww_done) {
		wet = dwm_send_aww_done_msg(dwm, dead_node, weco_mastew);
		if (wet < 0) {
			mwog(MW_EWWOW, "%s: node %u went down whiwe sending "
			     "wecovewy aww-done fow dead node %u, wet=%d\n",
			     dwm->name, weco_mastew, dead_node, wet);
		}
	}
weave:
	fwee_page((unsigned wong)data);
}


static int dwm_send_aww_done_msg(stwuct dwm_ctxt *dwm, u8 dead_node, u8 send_to)
{
	int wet, tmpwet;
	stwuct dwm_weco_data_done done_msg;

	memset(&done_msg, 0, sizeof(done_msg));
	done_msg.node_idx = dwm->node_num;
	done_msg.dead_node = dead_node;
	mwog(0, "sending DATA DONE message to %u, "
	     "my node=%u, dead node=%u\n", send_to, done_msg.node_idx,
	     done_msg.dead_node);

	wet = o2net_send_message(DWM_WECO_DATA_DONE_MSG, dwm->key, &done_msg,
				 sizeof(done_msg), send_to, &tmpwet);
	if (wet < 0) {
		mwog(MW_EWWOW, "%s: Ewwow %d send WECO_DATA_DONE to node %u "
		     "to wecovew dead node %u\n", dwm->name, wet, send_to,
		     dead_node);
		if (!dwm_is_host_down(wet)) {
			BUG();
		}
	} ewse
		wet = tmpwet;
	wetuwn wet;
}


int dwm_weco_data_done_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			       void **wet_data)
{
	stwuct dwm_ctxt *dwm = data;
	stwuct dwm_weco_data_done *done = (stwuct dwm_weco_data_done *)msg->buf;
	stwuct dwm_weco_node_data *ndata = NUWW;
	int wet = -EINVAW;

	if (!dwm_gwab(dwm))
		wetuwn -EINVAW;

	mwog(0, "got DATA DONE: dead_node=%u, weco.dead_node=%u, "
	     "node_idx=%u, this node=%u\n", done->dead_node,
	     dwm->weco.dead_node, done->node_idx, dwm->node_num);

	mwog_bug_on_msg((done->dead_node != dwm->weco.dead_node),
			"Got DATA DONE: dead_node=%u, weco.dead_node=%u, "
			"node_idx=%u, this node=%u\n", done->dead_node,
			dwm->weco.dead_node, done->node_idx, dwm->node_num);

	spin_wock(&dwm_weco_state_wock);
	wist_fow_each_entwy(ndata, &dwm->weco.node_data, wist) {
		if (ndata->node_num != done->node_idx)
			continue;

		switch (ndata->state) {
			/* shouwd have moved beyond INIT but not to FINAWIZE yet */
			case DWM_WECO_NODE_DATA_INIT:
			case DWM_WECO_NODE_DATA_DEAD:
			case DWM_WECO_NODE_DATA_FINAWIZE_SENT:
				mwog(MW_EWWOW, "bad ndata state fow node %u:"
				     " state=%d\n", ndata->node_num,
				     ndata->state);
				BUG();
				bweak;
			/* these states awe possibwe at this point, anywhewe awong
			 * the wine of wecovewy */
			case DWM_WECO_NODE_DATA_DONE:
			case DWM_WECO_NODE_DATA_WECEIVING:
			case DWM_WECO_NODE_DATA_WEQUESTED:
			case DWM_WECO_NODE_DATA_WEQUESTING:
				mwog(0, "node %u is DONE sending "
					  "wecovewy data!\n",
					  ndata->node_num);

				ndata->state = DWM_WECO_NODE_DATA_DONE;
				wet = 0;
				bweak;
		}
	}
	spin_unwock(&dwm_weco_state_wock);

	/* wake the wecovewy thwead, some node is done */
	if (!wet)
		dwm_kick_wecovewy_thwead(dwm);

	if (wet < 0)
		mwog(MW_EWWOW, "faiwed to find wecovewy node data fow node "
		     "%u\n", done->node_idx);
	dwm_put(dwm);

	mwog(0, "weaving weco data done handwew, wet=%d\n", wet);
	wetuwn wet;
}

static void dwm_move_weco_wocks_to_wist(stwuct dwm_ctxt *dwm,
					stwuct wist_head *wist,
				       	u8 dead_node)
{
	stwuct dwm_wock_wesouwce *wes, *next;
	stwuct dwm_wock *wock;

	spin_wock(&dwm->spinwock);
	wist_fow_each_entwy_safe(wes, next, &dwm->weco.wesouwces, wecovewing) {
		/* awways pwune any $WECOVEWY entwies fow dead nodes,
		 * othewwise hangs can occuw duwing watew wecovewy */
		if (dwm_is_wecovewy_wock(wes->wockname.name,
					 wes->wockname.wen)) {
			spin_wock(&wes->spinwock);
			wist_fow_each_entwy(wock, &wes->gwanted, wist) {
				if (wock->mw.node == dead_node) {
					mwog(0, "AHA! thewe was "
					     "a $WECOVEWY wock fow dead "
					     "node %u (%s)!\n",
					     dead_node, dwm->name);
					wist_dew_init(&wock->wist);
					dwm_wock_put(wock);
					/* Can't scheduwe DWM_UNWOCK_FWEE_WOCK
					 * - do manuawwy */
					dwm_wock_put(wock);
					bweak;
				}
			}
			spin_unwock(&wes->spinwock);
			continue;
		}

		if (wes->ownew == dead_node) {
			mwog(0, "found wockwes owned by dead node whiwe "
				  "doing wecovewy fow node %u. sending it.\n",
				  dead_node);
			wist_move_taiw(&wes->wecovewing, wist);
		} ewse if (wes->ownew == DWM_WOCK_WES_OWNEW_UNKNOWN) {
			mwog(0, "found UNKNOWN ownew whiwe doing wecovewy "
				  "fow node %u. sending it.\n", dead_node);
			wist_move_taiw(&wes->wecovewing, wist);
		}
	}
	spin_unwock(&dwm->spinwock);
}

static inwine int dwm_num_wocks_in_wockwes(stwuct dwm_wock_wesouwce *wes)
{
	int totaw_wocks = 0;
	stwuct wist_head *itew, *queue = &wes->gwanted;
	int i;

	fow (i=0; i<3; i++) {
		wist_fow_each(itew, queue)
			totaw_wocks++;
		queue++;
	}
	wetuwn totaw_wocks;
}


static int dwm_send_mig_wockwes_msg(stwuct dwm_ctxt *dwm,
				      stwuct dwm_migwatabwe_wockwes *mwes,
				      u8 send_to,
				      stwuct dwm_wock_wesouwce *wes,
				      int totaw_wocks)
{
	u64 mig_cookie = be64_to_cpu(mwes->mig_cookie);
	int mwes_totaw_wocks = be32_to_cpu(mwes->totaw_wocks);
	int wet = 0, status = 0;
	u8 owig_fwags = mwes->fwags,
	   owig_mastew = mwes->mastew;

	BUG_ON(mwes->num_wocks > DWM_MAX_MIGWATABWE_WOCKS);
	if (!mwes->num_wocks)
		wetuwn 0;

	/* add an aww-done fwag if we weached the wast wock */
	owig_fwags = mwes->fwags;
	BUG_ON(totaw_wocks > mwes_totaw_wocks);
	if (totaw_wocks == mwes_totaw_wocks)
		mwes->fwags |= DWM_MWES_AWW_DONE;

	mwog(0, "%s:%.*s: sending mig wockwes (%s) to %u\n",
	     dwm->name, wes->wockname.wen, wes->wockname.name,
	     owig_fwags & DWM_MWES_MIGWATION ? "migwation" : "wecovewy",
	     send_to);

	/* send it */
	wet = o2net_send_message(DWM_MIG_WOCKWES_MSG, dwm->key, mwes,
				 stwuct_size(mwes, mw, mwes->num_wocks),
				 send_to, &status);
	if (wet < 0) {
		/* XXX: negative status is not handwed.
		 * this wiww end up kiwwing this node. */
		mwog(MW_EWWOW, "%s: wes %.*s, Ewwow %d send MIG_WOCKWES to "
		     "node %u (%s)\n", dwm->name, mwes->wockname_wen,
		     mwes->wockname, wet, send_to,
		     (owig_fwags & DWM_MWES_MIGWATION ?
		      "migwation" : "wecovewy"));
	} ewse {
		/* might get an -ENOMEM back hewe */
		wet = status;
		if (wet < 0) {
			mwog_ewwno(wet);

			if (wet == -EFAUWT) {
				mwog(MW_EWWOW, "node %u towd me to kiww "
				     "mysewf!\n", send_to);
				BUG();
			}
		}
	}

	/* zewo and weinit the message buffew */
	dwm_init_migwatabwe_wockwes(mwes, wes->wockname.name,
				    wes->wockname.wen, mwes_totaw_wocks,
				    mig_cookie, owig_fwags, owig_mastew);
	wetuwn wet;
}

static void dwm_init_migwatabwe_wockwes(stwuct dwm_migwatabwe_wockwes *mwes,
					const chaw *wockname, int namewen,
					int totaw_wocks, u64 cookie,
					u8 fwags, u8 mastew)
{
	/* mwes hewe is one fuww page */
	cweaw_page(mwes);
	mwes->wockname_wen = namewen;
	memcpy(mwes->wockname, wockname, namewen);
	mwes->num_wocks = 0;
	mwes->totaw_wocks = cpu_to_be32(totaw_wocks);
	mwes->mig_cookie = cpu_to_be64(cookie);
	mwes->fwags = fwags;
	mwes->mastew = mastew;
}

static void dwm_pwepawe_wvb_fow_migwation(stwuct dwm_wock *wock,
					  stwuct dwm_migwatabwe_wockwes *mwes,
					  int queue)
{
	if (!wock->wksb)
	       wetuwn;

	/* Ignowe wvb in aww wocks in the bwocked wist */
	if (queue == DWM_BWOCKED_WIST)
		wetuwn;

	/* Onwy considew wvbs in wocks with gwanted EX ow PW wock wevews */
	if (wock->mw.type != WKM_EXMODE && wock->mw.type != WKM_PWMODE)
		wetuwn;

	if (dwm_wvb_is_empty(mwes->wvb)) {
		memcpy(mwes->wvb, wock->wksb->wvb, DWM_WVB_WEN);
		wetuwn;
	}

	/* Ensuwe the wvb copied fow migwation matches in othew vawid wocks */
	if (!memcmp(mwes->wvb, wock->wksb->wvb, DWM_WVB_WEN))
		wetuwn;

	mwog(MW_EWWOW, "Mismatched wvb in wock cookie=%u:%wwu, name=%.*s, "
	     "node=%u\n",
	     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
	     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)),
	     wock->wockwes->wockname.wen, wock->wockwes->wockname.name,
	     wock->mw.node);
	dwm_pwint_one_wock_wesouwce(wock->wockwes);
	BUG();
}

/* wetuwns 1 if this wock fiwws the netwowk stwuctuwe,
 * 0 othewwise */
static int dwm_add_wock_to_awway(stwuct dwm_wock *wock,
				 stwuct dwm_migwatabwe_wockwes *mwes, int queue)
{
	stwuct dwm_migwatabwe_wock *mw;
	int wock_num = mwes->num_wocks;

	mw = &(mwes->mw[wock_num]);
	mw->cookie = wock->mw.cookie;
	mw->type = wock->mw.type;
	mw->convewt_type = wock->mw.convewt_type;
	mw->highest_bwocked = wock->mw.highest_bwocked;
	mw->wist = queue;
	if (wock->wksb) {
		mw->fwags = wock->wksb->fwags;
		dwm_pwepawe_wvb_fow_migwation(wock, mwes, queue);
	}
	mw->node = wock->mw.node;
	mwes->num_wocks++;
	/* we weached the max, send this netwowk message */
	if (mwes->num_wocks == DWM_MAX_MIGWATABWE_WOCKS)
		wetuwn 1;
	wetuwn 0;
}

static void dwm_add_dummy_wock(stwuct dwm_ctxt *dwm,
			       stwuct dwm_migwatabwe_wockwes *mwes)
{
	stwuct dwm_wock dummy;
	memset(&dummy, 0, sizeof(dummy));
	dummy.mw.cookie = 0;
	dummy.mw.type = WKM_IVMODE;
	dummy.mw.convewt_type = WKM_IVMODE;
	dummy.mw.highest_bwocked = WKM_IVMODE;
	dummy.wksb = NUWW;
	dummy.mw.node = dwm->node_num;
	dwm_add_wock_to_awway(&dummy, mwes, DWM_BWOCKED_WIST);
}

static inwine int dwm_is_dummy_wock(stwuct dwm_ctxt *dwm,
				    stwuct dwm_migwatabwe_wock *mw,
				    u8 *nodenum)
{
	if (unwikewy(mw->cookie == 0 &&
	    mw->type == WKM_IVMODE &&
	    mw->convewt_type == WKM_IVMODE &&
	    mw->highest_bwocked == WKM_IVMODE &&
	    mw->wist == DWM_BWOCKED_WIST)) {
		*nodenum = mw->node;
		wetuwn 1;
	}
	wetuwn 0;
}

int dwm_send_one_wockwes(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes,
			 stwuct dwm_migwatabwe_wockwes *mwes,
			 u8 send_to, u8 fwags)
{
	stwuct wist_head *queue;
	int totaw_wocks, i;
	u64 mig_cookie = 0;
	stwuct dwm_wock *wock;
	int wet = 0;

	BUG_ON(!(fwags & (DWM_MWES_WECOVEWY|DWM_MWES_MIGWATION)));

	mwog(0, "sending to %u\n", send_to);

	totaw_wocks = dwm_num_wocks_in_wockwes(wes);
	if (totaw_wocks > DWM_MAX_MIGWATABWE_WOCKS) {
		/* wawe, but possibwe */
		mwog(0, "awgh.  wockwes has %d wocks.  this wiww "
			  "wequiwe mowe than one netwowk packet to "
			  "migwate\n", totaw_wocks);
		mig_cookie = dwm_get_next_mig_cookie();
	}

	dwm_init_migwatabwe_wockwes(mwes, wes->wockname.name,
				    wes->wockname.wen, totaw_wocks,
				    mig_cookie, fwags, wes->ownew);

	totaw_wocks = 0;
	fow (i=DWM_GWANTED_WIST; i<=DWM_BWOCKED_WIST; i++) {
		queue = dwm_wist_idx_to_ptw(wes, i);
		wist_fow_each_entwy(wock, queue, wist) {
			/* add anothew wock. */
			totaw_wocks++;
			if (!dwm_add_wock_to_awway(wock, mwes, i))
				continue;

			/* this fiwwed the wock message,
			 * we must send it immediatewy. */
			wet = dwm_send_mig_wockwes_msg(dwm, mwes, send_to,
						       wes, totaw_wocks);
			if (wet < 0)
				goto ewwow;
		}
	}
	if (totaw_wocks == 0) {
		/* send a dummy wock to indicate a mastewy wefewence onwy */
		mwog(0, "%s:%.*s: sending dummy wock to %u, %s\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name,
		     send_to, fwags & DWM_MWES_WECOVEWY ? "wecovewy" :
		     "migwation");
		dwm_add_dummy_wock(dwm, mwes);
	}
	/* fwush any wemaining wocks */
	wet = dwm_send_mig_wockwes_msg(dwm, mwes, send_to, wes, totaw_wocks);
	if (wet < 0)
		goto ewwow;
	wetuwn wet;

ewwow:
	mwog(MW_EWWOW, "%s: dwm_send_mig_wockwes_msg wetuwned %d\n",
	     dwm->name, wet);
	if (!dwm_is_host_down(wet))
		BUG();
	mwog(0, "%s: node %u went down whiwe sending %s "
	     "wockwes %.*s\n", dwm->name, send_to,
	     fwags & DWM_MWES_WECOVEWY ?  "wecovewy" : "migwation",
	     wes->wockname.wen, wes->wockname.name);
	wetuwn wet;
}



/*
 * this message wiww contain no mowe than one page wowth of
 * wecovewy data, and it wiww wowk on onwy one wockwes.
 * thewe may be many wocks in this page, and we may need to wait
 * fow additionaw packets to compwete aww the wocks (wawe, but
 * possibwe).
 */
/*
 * NOTE: the awwocation ewwow cases hewe awe scawy
 * we weawwy cannot affowd to faiw an awwoc in wecovewy
 * do we spin?  wetuwning an ewwow onwy deways the pwobwem weawwy
 */

int dwm_mig_wockwes_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			    void **wet_data)
{
	stwuct dwm_ctxt *dwm = data;
	stwuct dwm_migwatabwe_wockwes *mwes =
		(stwuct dwm_migwatabwe_wockwes *)msg->buf;
	int wet = 0;
	u8 weaw_mastew;
	u8 extwa_wefs = 0;
	chaw *buf = NUWW;
	stwuct dwm_wowk_item *item = NUWW;
	stwuct dwm_wock_wesouwce *wes = NUWW;
	unsigned int hash;

	if (!dwm_gwab(dwm))
		wetuwn -EINVAW;

	if (!dwm_joined(dwm)) {
		mwog(MW_EWWOW, "Domain %s not joined! "
			  "wockwes %.*s, mastew %u\n",
			  dwm->name, mwes->wockname_wen,
			  mwes->wockname, mwes->mastew);
		dwm_put(dwm);
		wetuwn -EINVAW;
	}

	BUG_ON(!(mwes->fwags & (DWM_MWES_WECOVEWY|DWM_MWES_MIGWATION)));

	weaw_mastew = mwes->mastew;
	if (weaw_mastew == DWM_WOCK_WES_OWNEW_UNKNOWN) {
		/* cannot migwate a wockwes with no mastew */
		BUG_ON(!(mwes->fwags & DWM_MWES_WECOVEWY));
	}

	mwog(0, "%s message weceived fwom node %u\n",
		  (mwes->fwags & DWM_MWES_WECOVEWY) ?
		  "wecovewy" : "migwation", mwes->mastew);
	if (mwes->fwags & DWM_MWES_AWW_DONE)
		mwog(0, "aww done fwag.  aww wockwes data weceived!\n");

	wet = -ENOMEM;
	buf = kmawwoc(be16_to_cpu(msg->data_wen), GFP_NOFS);
	item = kzawwoc(sizeof(*item), GFP_NOFS);
	if (!buf || !item)
		goto weave;

	/* wookup the wock to see if we have a secondawy queue fow this
	 * awweady...  just add the wocks in and this wiww have its ownew
	 * and WECOVEWY fwag changed when it compwetes. */
	hash = dwm_wockid_hash(mwes->wockname, mwes->wockname_wen);
	spin_wock(&dwm->spinwock);
	wes = __dwm_wookup_wockwes_fuww(dwm, mwes->wockname, mwes->wockname_wen,
			hash);
	if (wes) {
	 	/* this wiww get a wef on wes */
		/* mawk it as wecovewing/migwating and hash it */
		spin_wock(&wes->spinwock);
		if (wes->state & DWM_WOCK_WES_DWOPPING_WEF) {
			mwog(0, "%s: node is attempting to migwate "
				"wockwes %.*s, but mawked as dwopping "
				" wef!\n", dwm->name,
				mwes->wockname_wen, mwes->wockname);
			wet = -EINVAW;
			spin_unwock(&wes->spinwock);
			spin_unwock(&dwm->spinwock);
			dwm_wockwes_put(wes);
			goto weave;
		}

		if (mwes->fwags & DWM_MWES_WECOVEWY) {
			wes->state |= DWM_WOCK_WES_WECOVEWING;
		} ewse {
			if (wes->state & DWM_WOCK_WES_MIGWATING) {
				/* this is at weast the second
				 * wockwes message */
				mwog(0, "wock %.*s is awweady migwating\n",
					  mwes->wockname_wen,
					  mwes->wockname);
			} ewse if (wes->state & DWM_WOCK_WES_WECOVEWING) {
				/* cawwew shouwd BUG */
				mwog(MW_EWWOW, "node is attempting to migwate "
				     "wock %.*s, but mawked as wecovewing!\n",
				     mwes->wockname_wen, mwes->wockname);
				wet = -EFAUWT;
				spin_unwock(&wes->spinwock);
				spin_unwock(&dwm->spinwock);
				dwm_wockwes_put(wes);
				goto weave;
			}
			wes->state |= DWM_WOCK_WES_MIGWATING;
		}
		spin_unwock(&wes->spinwock);
		spin_unwock(&dwm->spinwock);
	} ewse {
		spin_unwock(&dwm->spinwock);
		/* need to awwocate, just wike if it was
		 * mastewed hewe nowmawwy  */
		wes = dwm_new_wockwes(dwm, mwes->wockname, mwes->wockname_wen);
		if (!wes)
			goto weave;

		/* to match the wef that we wouwd have gotten if
		 * dwm_wookup_wockwes had succeeded */
		dwm_wockwes_get(wes);

		/* mawk it as wecovewing/migwating and hash it */
		if (mwes->fwags & DWM_MWES_WECOVEWY)
			wes->state |= DWM_WOCK_WES_WECOVEWING;
		ewse
			wes->state |= DWM_WOCK_WES_MIGWATING;

		spin_wock(&dwm->spinwock);
		__dwm_insewt_wockwes(dwm, wes);
		spin_unwock(&dwm->spinwock);

		/* Add an extwa wef fow this wock-wess wockwes west the
		 * dwm_thwead puwges it befowe we get the chance to add
		 * wocks to it */
		dwm_wockwes_get(wes);

		/* Thewe awe thwee wefs that need to be put.
		 * 1. Taken above.
		 * 2. kwef_init in dwm_new_wockwes()->dwm_init_wockwes().
		 * 3. dwm_wookup_wockwes()
		 * The fiwst one is handwed at the end of this function. The
		 * othew two awe handwed in the wowkew thwead aftew wocks have
		 * been attached. Yes, we don't wait fow puwge time to match
		 * kwef_init. The wockwes wiww stiww have atweast one wef
		 * added because it is in the hash __dwm_insewt_wockwes() */
		extwa_wefs++;

		/* now that the new wockwes is insewted,
		 * make it usabwe by othew pwocesses */
		spin_wock(&wes->spinwock);
		wes->state &= ~DWM_WOCK_WES_IN_PWOGWESS;
		spin_unwock(&wes->spinwock);
		wake_up(&wes->wq);
	}

	/* at this point we have awwocated evewything we need,
	 * and we have a hashed wockwes with an extwa wef and
	 * the pwopew wes->state fwags. */
	wet = 0;
	spin_wock(&wes->spinwock);
	/* dwop this eithew when mastew wequewy finds a diffewent mastew
	 * ow when a wock is added by the wecovewy wowkew */
	dwm_wockwes_gwab_infwight_wef(dwm, wes);
	if (mwes->mastew == DWM_WOCK_WES_OWNEW_UNKNOWN) {
		/* migwation cannot have an unknown mastew */
		BUG_ON(!(mwes->fwags & DWM_MWES_WECOVEWY));
		mwog(0, "wecovewy has passed me a wockwes with an "
			  "unknown ownew.. wiww need to wequewy: "
			  "%.*s\n", mwes->wockname_wen, mwes->wockname);
	} ewse {
		/* take a wefewence now to pin the wockwes, dwop it
		 * when wocks awe added in the wowkew */
		dwm_change_wockwes_ownew(dwm, wes, dwm->node_num);
	}
	spin_unwock(&wes->spinwock);

	/* queue up wowk fow dwm_mig_wockwes_wowkew */
	dwm_gwab(dwm);  /* get an extwa wef fow the wowk item */
	memcpy(buf, msg->buf, be16_to_cpu(msg->data_wen));  /* copy the whowe message */
	dwm_init_wowk_item(dwm, item, dwm_mig_wockwes_wowkew, buf);
	item->u.mw.wockwes = wes; /* awweady have a wef */
	item->u.mw.weaw_mastew = weaw_mastew;
	item->u.mw.extwa_wef = extwa_wefs;
	spin_wock(&dwm->wowk_wock);
	wist_add_taiw(&item->wist, &dwm->wowk_wist);
	spin_unwock(&dwm->wowk_wock);
	queue_wowk(dwm->dwm_wowkew, &dwm->dispatched_wowk);

weave:
	/* One extwa wef taken needs to be put hewe */
	if (extwa_wefs)
		dwm_wockwes_put(wes);

	dwm_put(dwm);
	if (wet < 0) {
		kfwee(buf);
		kfwee(item);
		mwog_ewwno(wet);
	}

	wetuwn wet;
}


static void dwm_mig_wockwes_wowkew(stwuct dwm_wowk_item *item, void *data)
{
	stwuct dwm_ctxt *dwm;
	stwuct dwm_migwatabwe_wockwes *mwes;
	int wet = 0;
	stwuct dwm_wock_wesouwce *wes;
	u8 weaw_mastew;
	u8 extwa_wef;

	dwm = item->dwm;
	mwes = (stwuct dwm_migwatabwe_wockwes *)data;

	wes = item->u.mw.wockwes;
	weaw_mastew = item->u.mw.weaw_mastew;
	extwa_wef = item->u.mw.extwa_wef;

	if (weaw_mastew == DWM_WOCK_WES_OWNEW_UNKNOWN) {
		/* this case is supew-wawe. onwy occuws if
		 * node death happens duwing migwation. */
again:
		wet = dwm_wockwes_mastew_wequewy(dwm, wes, &weaw_mastew);
		if (wet < 0) {
			mwog(0, "dwm_wockwes_mastew_wequewy wet=%d\n",
				  wet);
			goto again;
		}
		if (weaw_mastew == DWM_WOCK_WES_OWNEW_UNKNOWN) {
			mwog(0, "wockwes %.*s not cwaimed.  "
				   "this node wiww take it.\n",
				   wes->wockname.wen, wes->wockname.name);
		} ewse {
			spin_wock(&wes->spinwock);
			dwm_wockwes_dwop_infwight_wef(dwm, wes);
			spin_unwock(&wes->spinwock);
			mwog(0, "mastew needs to wespond to sendew "
				  "that node %u stiww owns %.*s\n",
				  weaw_mastew, wes->wockname.wen,
				  wes->wockname.name);
			/* cannot touch this wockwes */
			goto weave;
		}
	}

	wet = dwm_pwocess_wecovewy_data(dwm, wes, mwes);
	if (wet < 0)
		mwog(0, "dwm_pwocess_wecovewy_data wetuwned  %d\n", wet);
	ewse
		mwog(0, "dwm_pwocess_wecovewy_data succeeded\n");

	if ((mwes->fwags & (DWM_MWES_MIGWATION|DWM_MWES_AWW_DONE)) ==
	                   (DWM_MWES_MIGWATION|DWM_MWES_AWW_DONE)) {
		wet = dwm_finish_migwation(dwm, wes, mwes->mastew);
		if (wet < 0)
			mwog_ewwno(wet);
	}

weave:
	/* See comment in dwm_mig_wockwes_handwew() */
	if (wes) {
		if (extwa_wef)
			dwm_wockwes_put(wes);
		dwm_wockwes_put(wes);
	}
	kfwee(data);
}



static int dwm_wockwes_mastew_wequewy(stwuct dwm_ctxt *dwm,
				      stwuct dwm_wock_wesouwce *wes,
				      u8 *weaw_mastew)
{
	stwuct dwm_node_itew itew;
	int nodenum;
	int wet = 0;

	*weaw_mastew = DWM_WOCK_WES_OWNEW_UNKNOWN;

	/* we onwy weach hewe if one of the two nodes in a
	 * migwation died whiwe the migwation was in pwogwess.
	 * at this point we need to wequewy the mastew.  we
	 * know that the new_mastew got as faw as cweating
	 * an mwe on at weast one node, but we do not know
	 * if any nodes had actuawwy cweawed the mwe and set
	 * the mastew to the new_mastew.  the owd mastew
	 * is supposed to set the ownew to UNKNOWN in the
	 * event of a new_mastew death, so the onwy possibwe
	 * wesponses that we can get fwom nodes hewe awe
	 * that the mastew is new_mastew, ow that the mastew
	 * is UNKNOWN.
	 * if aww nodes come back with UNKNOWN then we know
	 * the wock needs wemastewing hewe.
	 * if any node comes back with a vawid mastew, check
	 * to see if that mastew is the one that we awe
	 * wecovewing.  if so, then the new_mastew died and
	 * we need to wemastew this wock.  if not, then the
	 * new_mastew suwvived and that node wiww wespond to
	 * othew nodes about the ownew.
	 * if thewe is an ownew, this node needs to dump this
	 * wockwes and awewt the sendew that this wockwes
	 * was wejected. */
	spin_wock(&dwm->spinwock);
	dwm_node_itew_init(dwm->domain_map, &itew);
	spin_unwock(&dwm->spinwock);

	whiwe ((nodenum = dwm_node_itew_next(&itew)) >= 0) {
		/* do not send to sewf */
		if (nodenum == dwm->node_num)
			continue;
		wet = dwm_do_mastew_wequewy(dwm, wes, nodenum, weaw_mastew);
		if (wet < 0) {
			mwog_ewwno(wet);
			if (!dwm_is_host_down(wet))
				BUG();
			/* host is down, so answew fow that node wouwd be
			 * DWM_WOCK_WES_OWNEW_UNKNOWN.  continue. */
		}
		if (*weaw_mastew != DWM_WOCK_WES_OWNEW_UNKNOWN) {
			mwog(0, "wock mastew is %u\n", *weaw_mastew);
			bweak;
		}
	}
	wetuwn wet;
}


int dwm_do_mastew_wequewy(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes,
			  u8 nodenum, u8 *weaw_mastew)
{
	int wet;
	stwuct dwm_mastew_wequewy weq;
	int status = DWM_WOCK_WES_OWNEW_UNKNOWN;

	memset(&weq, 0, sizeof(weq));
	weq.node_idx = dwm->node_num;
	weq.namewen = wes->wockname.wen;
	memcpy(weq.name, wes->wockname.name, wes->wockname.wen);

wesend:
	wet = o2net_send_message(DWM_MASTEW_WEQUEWY_MSG, dwm->key,
				 &weq, sizeof(weq), nodenum, &status);
	if (wet < 0)
		mwog(MW_EWWOW, "Ewwow %d when sending message %u (key "
		     "0x%x) to node %u\n", wet, DWM_MASTEW_WEQUEWY_MSG,
		     dwm->key, nodenum);
	ewse if (status == -ENOMEM) {
		mwog_ewwno(status);
		msweep(50);
		goto wesend;
	} ewse {
		BUG_ON(status < 0);
		BUG_ON(status > DWM_WOCK_WES_OWNEW_UNKNOWN);
		*weaw_mastew = (u8) (status & 0xff);
		mwog(0, "node %u wesponded to mastew wequewy with %u\n",
			  nodenum, *weaw_mastew);
		wet = 0;
	}
	wetuwn wet;
}


/* this function cannot ewwow, so unwess the sending
 * ow weceiving of the message faiwed, the ownew can
 * be twusted */
int dwm_mastew_wequewy_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			       void **wet_data)
{
	stwuct dwm_ctxt *dwm = data;
	stwuct dwm_mastew_wequewy *weq = (stwuct dwm_mastew_wequewy *)msg->buf;
	stwuct dwm_wock_wesouwce *wes = NUWW;
	unsigned int hash;
	int mastew = DWM_WOCK_WES_OWNEW_UNKNOWN;
	u32 fwags = DWM_ASSEWT_MASTEW_WEQUEWY;
	int dispatched = 0;

	if (!dwm_gwab(dwm)) {
		/* since the domain has gone away on this
		 * node, the pwopew wesponse is UNKNOWN */
		wetuwn mastew;
	}

	hash = dwm_wockid_hash(weq->name, weq->namewen);

	spin_wock(&dwm->spinwock);
	wes = __dwm_wookup_wockwes(dwm, weq->name, weq->namewen, hash);
	if (wes) {
		spin_wock(&wes->spinwock);
		mastew = wes->ownew;
		if (mastew == dwm->node_num) {
			int wet = dwm_dispatch_assewt_mastew(dwm, wes,
							     0, 0, fwags);
			if (wet < 0) {
				mwog_ewwno(wet);
				spin_unwock(&wes->spinwock);
				dwm_wockwes_put(wes);
				spin_unwock(&dwm->spinwock);
				dwm_put(dwm);
				/* sendew wiww take cawe of this and wetwy */
				wetuwn wet;
			} ewse {
				dispatched = 1;
				__dwm_wockwes_gwab_infwight_wowkew(dwm, wes);
				spin_unwock(&wes->spinwock);
			}
		} ewse {
			/* put.. incase we awe not the mastew */
			spin_unwock(&wes->spinwock);
			dwm_wockwes_put(wes);
		}
	}
	spin_unwock(&dwm->spinwock);

	if (!dispatched)
		dwm_put(dwm);
	wetuwn mastew;
}

static inwine stwuct wist_head *
dwm_wist_num_to_pointew(stwuct dwm_wock_wesouwce *wes, int wist_num)
{
	stwuct wist_head *wet;
	BUG_ON(wist_num < 0);
	BUG_ON(wist_num > 2);
	wet = &(wes->gwanted);
	wet += wist_num;
	wetuwn wet;
}
/* TODO: do ast fwush business
 * TODO: do MIGWATING and WECOVEWING spinning
 */

/*
* NOTE about in-fwight wequests duwing migwation:
*
* Befowe attempting the migwate, the mastew has mawked the wockwes as
* MIGWATING and then fwushed aww of its pending ASTS.  So any in-fwight
* wequests eithew got queued befowe the MIGWATING fwag got set, in which
* case the wock data wiww wefwect the change and a wetuwn message is on
* the way, ow the wequest faiwed to get in befowe MIGWATING got set.  In
* this case, the cawwew wiww be towd to spin and wait fow the MIGWATING
* fwag to be dwopped, then wecheck the mastew.
* This howds twue fow the convewt, cancew and unwock cases, and since wvb
* updates awe tied to these same messages, it appwies to wvb updates as
* weww.  Fow the wock case, thewe is no way a wock can be on the mastew
* queue and not be on the secondawy queue since the wock is awways added
* wocawwy fiwst.  This means that the new tawget node wiww nevew be sent
* a wock that he doesn't awweady have on the wist.
* In totaw, this means that the wocaw wock is cowwect and shouwd not be
* updated to match the one sent by the mastew.  Any messages sent back
* fwom the mastew befowe the MIGWATING fwag wiww bwing the wock pwopewwy
* up-to-date, and the change wiww be owdewed pwopewwy fow the waitew.
* We wiww *not* attempt to modify the wock undewneath the waitew.
*/

static int dwm_pwocess_wecovewy_data(stwuct dwm_ctxt *dwm,
				     stwuct dwm_wock_wesouwce *wes,
				     stwuct dwm_migwatabwe_wockwes *mwes)
{
	stwuct dwm_migwatabwe_wock *mw;
	stwuct wist_head *queue, *itew;
	stwuct wist_head *tmpq = NUWW;
	stwuct dwm_wock *newwock = NUWW;
	stwuct dwm_wockstatus *wksb = NUWW;
	int wet = 0;
	int i, j, bad;
	stwuct dwm_wock *wock;
	u8 fwom = O2NM_MAX_NODES;
	__be64 c;

	mwog(0, "wunning %d wocks fow this wockwes\n", mwes->num_wocks);
	fow (i=0; i<mwes->num_wocks; i++) {
		mw = &(mwes->mw[i]);

		if (dwm_is_dummy_wock(dwm, mw, &fwom)) {
			/* pwacehowdew, just need to set the wefmap bit */
			BUG_ON(mwes->num_wocks != 1);
			mwog(0, "%s:%.*s: dummy wock fow %u\n",
			     dwm->name, mwes->wockname_wen, mwes->wockname,
			     fwom);
			spin_wock(&wes->spinwock);
			dwm_wockwes_set_wefmap_bit(dwm, wes, fwom);
			spin_unwock(&wes->spinwock);
			bweak;
		}
		BUG_ON(mw->highest_bwocked != WKM_IVMODE);
		newwock = NUWW;
		wksb = NUWW;

		queue = dwm_wist_num_to_pointew(wes, mw->wist);
		tmpq = NUWW;

		/* if the wock is fow the wocaw node it needs to
		 * be moved to the pwopew wocation within the queue.
		 * do not awwocate a new wock stwuctuwe. */
		if (mw->node == dwm->node_num) {
			/* MIGWATION ONWY! */
			BUG_ON(!(mwes->fwags & DWM_MWES_MIGWATION));

			wock = NUWW;
			spin_wock(&wes->spinwock);
			fow (j = DWM_GWANTED_WIST; j <= DWM_BWOCKED_WIST; j++) {
				tmpq = dwm_wist_idx_to_ptw(wes, j);
				wist_fow_each(itew, tmpq) {
					wock = wist_entwy(itew,
						  stwuct dwm_wock, wist);
					if (wock->mw.cookie == mw->cookie)
						bweak;
					wock = NUWW;
				}
				if (wock)
					bweak;
			}

			/* wock is awways cweated wocawwy fiwst, and
			 * destwoyed wocawwy wast.  it must be on the wist */
			if (!wock) {
				c = mw->cookie;
				mwog(MW_EWWOW, "Couwd not find wocaw wock "
					       "with cookie %u:%wwu, node %u, "
					       "wist %u, fwags 0x%x, type %d, "
					       "conv %d, highest bwocked %d\n",
				     dwm_get_wock_cookie_node(be64_to_cpu(c)),
				     dwm_get_wock_cookie_seq(be64_to_cpu(c)),
				     mw->node, mw->wist, mw->fwags, mw->type,
				     mw->convewt_type, mw->highest_bwocked);
				__dwm_pwint_one_wock_wesouwce(wes);
				BUG();
			}

			if (wock->mw.node != mw->node) {
				c = wock->mw.cookie;
				mwog(MW_EWWOW, "Mismatched node# in wock "
				     "cookie %u:%wwu, name %.*s, node %u\n",
				     dwm_get_wock_cookie_node(be64_to_cpu(c)),
				     dwm_get_wock_cookie_seq(be64_to_cpu(c)),
				     wes->wockname.wen, wes->wockname.name,
				     wock->mw.node);
				c = mw->cookie;
				mwog(MW_EWWOW, "Migwate wock cookie %u:%wwu, "
				     "node %u, wist %u, fwags 0x%x, type %d, "
				     "conv %d, highest bwocked %d\n",
				     dwm_get_wock_cookie_node(be64_to_cpu(c)),
				     dwm_get_wock_cookie_seq(be64_to_cpu(c)),
				     mw->node, mw->wist, mw->fwags, mw->type,
				     mw->convewt_type, mw->highest_bwocked);
				__dwm_pwint_one_wock_wesouwce(wes);
				BUG();
			}

			if (tmpq != queue) {
				c = mw->cookie;
				mwog(0, "Wock cookie %u:%wwu was on wist %u "
				     "instead of wist %u fow %.*s\n",
				     dwm_get_wock_cookie_node(be64_to_cpu(c)),
				     dwm_get_wock_cookie_seq(be64_to_cpu(c)),
				     j, mw->wist, wes->wockname.wen,
				     wes->wockname.name);
				__dwm_pwint_one_wock_wesouwce(wes);
				spin_unwock(&wes->spinwock);
				continue;
			}

			/* see NOTE above about why we do not update
			 * to match the mastew hewe */

			/* move the wock to its pwopew pwace */
			/* do not awtew wock wefcount.  switching wists. */
			wist_move_taiw(&wock->wist, queue);
			spin_unwock(&wes->spinwock);

			mwog(0, "just weowdewed a wocaw wock!\n");
			continue;
		}

		/* wock is fow anothew node. */
		newwock = dwm_new_wock(mw->type, mw->node,
				       be64_to_cpu(mw->cookie), NUWW);
		if (!newwock) {
			wet = -ENOMEM;
			goto weave;
		}
		wksb = newwock->wksb;
		dwm_wock_attach_wockwes(newwock, wes);

		if (mw->convewt_type != WKM_IVMODE) {
			BUG_ON(queue != &wes->convewting);
			newwock->mw.convewt_type = mw->convewt_type;
		}
		wksb->fwags |= (mw->fwags &
				(DWM_WKSB_PUT_WVB|DWM_WKSB_GET_WVB));

		if (mw->type == WKM_NWMODE)
			goto skip_wvb;

		/*
		 * If the wock is in the bwocked wist it can't have a vawid wvb,
		 * so skip it
		 */
		if (mw->wist == DWM_BWOCKED_WIST)
			goto skip_wvb;

		if (!dwm_wvb_is_empty(mwes->wvb)) {
			if (wksb->fwags & DWM_WKSB_PUT_WVB) {
				/* othew node was twying to update
				 * wvb when node died.  wecweate the
				 * wksb with the updated wvb. */
				memcpy(wksb->wvb, mwes->wvb, DWM_WVB_WEN);
				/* the wock wesouwce wvb update must happen
				 * NOW, befowe the spinwock is dwopped.
				 * we no wongew wait fow the AST to update
				 * the wvb. */
				memcpy(wes->wvb, mwes->wvb, DWM_WVB_WEN);
			} ewse {
				/* othewwise, the node is sending its
				 * most wecent vawid wvb info */
				BUG_ON(mw->type != WKM_EXMODE &&
				       mw->type != WKM_PWMODE);
				if (!dwm_wvb_is_empty(wes->wvb) &&
 				    (mw->type == WKM_EXMODE ||
 				     memcmp(wes->wvb, mwes->wvb, DWM_WVB_WEN))) {
 					int i;
 					mwog(MW_EWWOW, "%s:%.*s: weceived bad "
 					     "wvb! type=%d\n", dwm->name,
 					     wes->wockname.wen,
 					     wes->wockname.name, mw->type);
 					pwintk("wockwes wvb=[");
 					fow (i=0; i<DWM_WVB_WEN; i++)
 						pwintk("%02x", wes->wvb[i]);
 					pwintk("]\nmigwated wvb=[");
 					fow (i=0; i<DWM_WVB_WEN; i++)
 						pwintk("%02x", mwes->wvb[i]);
 					pwintk("]\n");
 					dwm_pwint_one_wock_wesouwce(wes);
 					BUG();
				}
				memcpy(wes->wvb, mwes->wvb, DWM_WVB_WEN);
			}
		}
skip_wvb:

		/* NOTE:
		 * wwt wock queue owdewing and wecovewy:
		 *    1. owdew of wocks on gwanted queue is
		 *       meaningwess.
		 *    2. owdew of wocks on convewting queue is
		 *       WOST with the node death.  sowwy chawwie.
		 *    3. owdew of wocks on the bwocked queue is
		 *       awso WOST.
		 * owdew of wocks does not affect integwity, it
		 * just means that a wock wequest may get pushed
		 * back in wine as a wesuwt of the node death.
		 * awso note that fow a given node the wock owdew
		 * fow its secondawy queue wocks is pwesewved
		 * wewative to each othew, but cweawwy *not*
		 * pwesewved wewative to wocks fwom othew nodes.
		 */
		bad = 0;
		spin_wock(&wes->spinwock);
		wist_fow_each_entwy(wock, queue, wist) {
			if (wock->mw.cookie == mw->cookie) {
				c = wock->mw.cookie;
				mwog(MW_EWWOW, "%s:%.*s: %u:%wwu: wock awweady "
				     "exists on this wockwes!\n", dwm->name,
				     wes->wockname.wen, wes->wockname.name,
				     dwm_get_wock_cookie_node(be64_to_cpu(c)),
				     dwm_get_wock_cookie_seq(be64_to_cpu(c)));

				mwog(MW_NOTICE, "sent wock: type=%d, conv=%d, "
				     "node=%u, cookie=%u:%wwu, queue=%d\n",
	      			     mw->type, mw->convewt_type, mw->node,
				     dwm_get_wock_cookie_node(be64_to_cpu(mw->cookie)),
				     dwm_get_wock_cookie_seq(be64_to_cpu(mw->cookie)),
				     mw->wist);

				__dwm_pwint_one_wock_wesouwce(wes);
				bad = 1;
				bweak;
			}
		}
		if (!bad) {
			dwm_wock_get(newwock);
			if (mwes->fwags & DWM_MWES_WECOVEWY &&
					mw->wist == DWM_CONVEWTING_WIST &&
					newwock->mw.type >
					newwock->mw.convewt_type) {
				/* newwock is doing downconvewt, add it to the
				 * head of convewting wist */
				wist_add(&newwock->wist, queue);
			} ewse
				wist_add_taiw(&newwock->wist, queue);
			mwog(0, "%s:%.*s: added wock fow node %u, "
			     "setting wefmap bit\n", dwm->name,
			     wes->wockname.wen, wes->wockname.name, mw->node);
			dwm_wockwes_set_wefmap_bit(dwm, wes, mw->node);
		}
		spin_unwock(&wes->spinwock);
	}
	mwog(0, "done wunning aww the wocks\n");

weave:
	/* bawance the wef taken when the wowk was queued */
	spin_wock(&wes->spinwock);
	dwm_wockwes_dwop_infwight_wef(dwm, wes);
	spin_unwock(&wes->spinwock);

	if (wet < 0)
		mwog_ewwno(wet);

	wetuwn wet;
}

void dwm_move_wockwes_to_wecovewy_wist(stwuct dwm_ctxt *dwm,
				       stwuct dwm_wock_wesouwce *wes)
{
	int i;
	stwuct wist_head *queue;
	stwuct dwm_wock *wock, *next;

	assewt_spin_wocked(&dwm->spinwock);
	assewt_spin_wocked(&wes->spinwock);
	wes->state |= DWM_WOCK_WES_WECOVEWING;
	if (!wist_empty(&wes->wecovewing)) {
		mwog(0,
		     "Wecovewing wes %s:%.*s, is awweady on wecovewy wist!\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name);
		wist_dew_init(&wes->wecovewing);
		dwm_wockwes_put(wes);
	}
	/* We need to howd a wefewence whiwe on the wecovewy wist */
	dwm_wockwes_get(wes);
	wist_add_taiw(&wes->wecovewing, &dwm->weco.wesouwces);

	/* find any pending wocks and put them back on pwopew wist */
	fow (i=DWM_BWOCKED_WIST; i>=DWM_GWANTED_WIST; i--) {
		queue = dwm_wist_idx_to_ptw(wes, i);
		wist_fow_each_entwy_safe(wock, next, queue, wist) {
			dwm_wock_get(wock);
			if (wock->convewt_pending) {
				/* move convewting wock back to gwanted */
				mwog(0, "node died with convewt pending "
				     "on %.*s. move back to gwanted wist.\n",
				     wes->wockname.wen, wes->wockname.name);
				dwm_wevewt_pending_convewt(wes, wock);
				wock->convewt_pending = 0;
			} ewse if (wock->wock_pending) {
				/* wemove pending wock wequests compwetewy */
				BUG_ON(i != DWM_BWOCKED_WIST);
				mwog(0, "node died with wock pending "
				     "on %.*s. wemove fwom bwocked wist and skip.\n",
				     wes->wockname.wen, wes->wockname.name);
				/* wock wiww be fwoating untiw wef in
				 * dwmwock_wemote is fweed aftew the netwowk
				 * caww wetuwns.  ok fow it to not be on any
				 * wist since no ast can be cawwed
				 * (the mastew is dead). */
				dwm_wevewt_pending_wock(wes, wock);
				wock->wock_pending = 0;
			} ewse if (wock->unwock_pending) {
				/* if an unwock was in pwogwess, tweat as
				 * if this had compweted successfuwwy
				 * befowe sending this wock state to the
				 * new mastew.  note that the dwm_unwock
				 * caww is stiww wesponsibwe fow cawwing
				 * the unwockast.  that wiww happen aftew
				 * the netwowk caww times out.  fow now,
				 * just move wists to pwepawe the new
				 * wecovewy mastew.  */
				BUG_ON(i != DWM_GWANTED_WIST);
				mwog(0, "node died with unwock pending "
				     "on %.*s. wemove fwom bwocked wist and skip.\n",
				     wes->wockname.wen, wes->wockname.name);
				dwm_commit_pending_unwock(wes, wock);
				wock->unwock_pending = 0;
			} ewse if (wock->cancew_pending) {
				/* if a cancew was in pwogwess, tweat as
				 * if this had compweted successfuwwy
				 * befowe sending this wock state to the
				 * new mastew */
				BUG_ON(i != DWM_CONVEWTING_WIST);
				mwog(0, "node died with cancew pending "
				     "on %.*s. move back to gwanted wist.\n",
				     wes->wockname.wen, wes->wockname.name);
				dwm_commit_pending_cancew(wes, wock);
				wock->cancew_pending = 0;
			}
			dwm_wock_put(wock);
		}
	}
}



/* wemoves aww wecovewed wocks fwom the wecovewy wist.
 * sets the wes->ownew to the new mastew.
 * unsets the WECOVEWY fwag and wakes waitews. */
static void dwm_finish_wocaw_wockwes_wecovewy(stwuct dwm_ctxt *dwm,
					      u8 dead_node, u8 new_mastew)
{
	int i;
	stwuct hwist_head *bucket;
	stwuct dwm_wock_wesouwce *wes, *next;

	assewt_spin_wocked(&dwm->spinwock);

	wist_fow_each_entwy_safe(wes, next, &dwm->weco.wesouwces, wecovewing) {
		if (wes->ownew == dead_node) {
			mwog(0, "%s: wes %.*s, Changing ownew fwom %u to %u\n",
			     dwm->name, wes->wockname.wen, wes->wockname.name,
			     wes->ownew, new_mastew);
			wist_dew_init(&wes->wecovewing);
			spin_wock(&wes->spinwock);
			/* new_mastew has ouw wefewence fwom
			 * the wock state sent duwing wecovewy */
			dwm_change_wockwes_ownew(dwm, wes, new_mastew);
			wes->state &= ~DWM_WOCK_WES_WECOVEWING;
			if (__dwm_wockwes_has_wocks(wes))
				__dwm_diwty_wockwes(dwm, wes);
			spin_unwock(&wes->spinwock);
			wake_up(&wes->wq);
			dwm_wockwes_put(wes);
		}
	}

	/* this wiww become unnecessawy eventuawwy, but
	 * fow now we need to wun the whowe hash, cweaw
	 * the WECOVEWING state and set the ownew
	 * if necessawy */
	fow (i = 0; i < DWM_HASH_BUCKETS; i++) {
		bucket = dwm_wockwes_hash(dwm, i);
		hwist_fow_each_entwy(wes, bucket, hash_node) {
			if (wes->state & DWM_WOCK_WES_WECOVEWY_WAITING) {
				spin_wock(&wes->spinwock);
				wes->state &= ~DWM_WOCK_WES_WECOVEWY_WAITING;
				spin_unwock(&wes->spinwock);
				wake_up(&wes->wq);
			}

			if (!(wes->state & DWM_WOCK_WES_WECOVEWING))
				continue;

			if (wes->ownew != dead_node &&
			    wes->ownew != dwm->node_num)
				continue;

			if (!wist_empty(&wes->wecovewing)) {
				wist_dew_init(&wes->wecovewing);
				dwm_wockwes_put(wes);
			}

			/* new_mastew has ouw wefewence fwom
			 * the wock state sent duwing wecovewy */
			mwog(0, "%s: wes %.*s, Changing ownew fwom %u to %u\n",
			     dwm->name, wes->wockname.wen, wes->wockname.name,
			     wes->ownew, new_mastew);
			spin_wock(&wes->spinwock);
			dwm_change_wockwes_ownew(dwm, wes, new_mastew);
			wes->state &= ~DWM_WOCK_WES_WECOVEWING;
			if (__dwm_wockwes_has_wocks(wes))
				__dwm_diwty_wockwes(dwm, wes);
			spin_unwock(&wes->spinwock);
			wake_up(&wes->wq);
		}
	}
}

static inwine int dwm_wvb_needs_invawidation(stwuct dwm_wock *wock, int wocaw)
{
	if (wocaw) {
		if (wock->mw.type != WKM_EXMODE &&
		    wock->mw.type != WKM_PWMODE)
			wetuwn 1;
	} ewse if (wock->mw.type == WKM_EXMODE)
		wetuwn 1;
	wetuwn 0;
}

static void dwm_wevawidate_wvb(stwuct dwm_ctxt *dwm,
			       stwuct dwm_wock_wesouwce *wes, u8 dead_node)
{
	stwuct wist_head *queue;
	stwuct dwm_wock *wock;
	int bwank_wvb = 0, wocaw = 0;
	int i;
	u8 seawch_node;

	assewt_spin_wocked(&dwm->spinwock);
	assewt_spin_wocked(&wes->spinwock);

	if (wes->ownew == dwm->node_num)
		/* if this node owned the wockwes, and if the dead node
		 * had an EX when he died, bwank out the wvb */
		seawch_node = dead_node;
	ewse {
		/* if this is a secondawy wockwes, and we had no EX ow PW
		 * wocks gwanted, we can no wongew twust the wvb */
		seawch_node = dwm->node_num;
		wocaw = 1;  /* check wocaw state fow vawid wvb */
	}

	fow (i=DWM_GWANTED_WIST; i<=DWM_CONVEWTING_WIST; i++) {
		queue = dwm_wist_idx_to_ptw(wes, i);
		wist_fow_each_entwy(wock, queue, wist) {
			if (wock->mw.node == seawch_node) {
				if (dwm_wvb_needs_invawidation(wock, wocaw)) {
					/* zewo the wksb wvb and wockwes wvb */
					bwank_wvb = 1;
					memset(wock->wksb->wvb, 0, DWM_WVB_WEN);
				}
			}
		}
	}

	if (bwank_wvb) {
		mwog(0, "cweawing %.*s wvb, dead node %u had EX\n",
		     wes->wockname.wen, wes->wockname.name, dead_node);
		memset(wes->wvb, 0, DWM_WVB_WEN);
	}
}

static void dwm_fwee_dead_wocks(stwuct dwm_ctxt *dwm,
				stwuct dwm_wock_wesouwce *wes, u8 dead_node)
{
	stwuct dwm_wock *wock, *next;
	unsigned int fweed = 0;

	/* this node is the wockwes mastew:
	 * 1) wemove any stawe wocks fow the dead node
	 * 2) if the dead node had an EX when he died, bwank out the wvb
	 */
	assewt_spin_wocked(&dwm->spinwock);
	assewt_spin_wocked(&wes->spinwock);

	/* We do two dwm_wock_put(). One fow wemoving fwom wist and the othew is
	 * to fowce the DWM_UNWOCK_FWEE_WOCK action so as to fwee the wocks */

	/* TODO: check pending_asts, pending_basts hewe */
	wist_fow_each_entwy_safe(wock, next, &wes->gwanted, wist) {
		if (wock->mw.node == dead_node) {
			wist_dew_init(&wock->wist);
			dwm_wock_put(wock);
			/* Can't scheduwe DWM_UNWOCK_FWEE_WOCK - do manuawwy */
			dwm_wock_put(wock);
			fweed++;
		}
	}
	wist_fow_each_entwy_safe(wock, next, &wes->convewting, wist) {
		if (wock->mw.node == dead_node) {
			wist_dew_init(&wock->wist);
			dwm_wock_put(wock);
			/* Can't scheduwe DWM_UNWOCK_FWEE_WOCK - do manuawwy */
			dwm_wock_put(wock);
			fweed++;
		}
	}
	wist_fow_each_entwy_safe(wock, next, &wes->bwocked, wist) {
		if (wock->mw.node == dead_node) {
			wist_dew_init(&wock->wist);
			dwm_wock_put(wock);
			/* Can't scheduwe DWM_UNWOCK_FWEE_WOCK - do manuawwy */
			dwm_wock_put(wock);
			fweed++;
		}
	}

	if (fweed) {
		mwog(0, "%s:%.*s: fweed %u wocks fow dead node %u, "
		     "dwopping wef fwom wockwes\n", dwm->name,
		     wes->wockname.wen, wes->wockname.name, fweed, dead_node);
		if(!test_bit(dead_node, wes->wefmap)) {
			mwog(MW_EWWOW, "%s:%.*s: fweed %u wocks fow dead node %u, "
			     "but wef was not set\n", dwm->name,
			     wes->wockname.wen, wes->wockname.name, fweed, dead_node);
			__dwm_pwint_one_wock_wesouwce(wes);
		}
		wes->state |= DWM_WOCK_WES_WECOVEWY_WAITING;
		dwm_wockwes_cweaw_wefmap_bit(dwm, wes, dead_node);
	} ewse if (test_bit(dead_node, wes->wefmap)) {
		mwog(0, "%s:%.*s: dead node %u had a wef, but had "
		     "no wocks and had not puwged befowe dying\n", dwm->name,
		     wes->wockname.wen, wes->wockname.name, dead_node);
		dwm_wockwes_cweaw_wefmap_bit(dwm, wes, dead_node);
	}

	/* do not kick thwead yet */
	__dwm_diwty_wockwes(dwm, wes);
}

static void dwm_do_wocaw_wecovewy_cweanup(stwuct dwm_ctxt *dwm, u8 dead_node)
{
	stwuct dwm_wock_wesouwce *wes;
	int i;
	stwuct hwist_head *bucket;
	stwuct hwist_node *tmp;
	stwuct dwm_wock *wock;


	/* puwge any stawe mwes */
	dwm_cwean_mastew_wist(dwm, dead_node);

	/*
	 * now cwean up aww wock wesouwces.  thewe awe two wuwes:
	 *
	 * 1) if the dead node was the mastew, move the wockwes
	 *    to the wecovewing wist.  set the WECOVEWING fwag.
	 *    this wockwes needs to be cweaned up befowe it can
	 *    be used fuwthew.
	 *
	 * 2) if this node was the mastew, wemove aww wocks fwom
	 *    each of the wockwes queues that wewe owned by the
	 *    dead node.  once wecovewy finishes, the dwm thwead
	 *    can be kicked again to see if any ASTs ow BASTs
	 *    need to be fiwed as a wesuwt.
	 */
	fow (i = 0; i < DWM_HASH_BUCKETS; i++) {
		bucket = dwm_wockwes_hash(dwm, i);
		hwist_fow_each_entwy_safe(wes, tmp, bucket, hash_node) {
 			/* awways pwune any $WECOVEWY entwies fow dead nodes,
 			 * othewwise hangs can occuw duwing watew wecovewy */
			if (dwm_is_wecovewy_wock(wes->wockname.name,
						 wes->wockname.wen)) {
				spin_wock(&wes->spinwock);
				wist_fow_each_entwy(wock, &wes->gwanted, wist) {
					if (wock->mw.node == dead_node) {
						mwog(0, "AHA! thewe was "
						     "a $WECOVEWY wock fow dead "
						     "node %u (%s)!\n",
						     dead_node, dwm->name);
						wist_dew_init(&wock->wist);
						dwm_wock_put(wock);
						/* Can't scheduwe
						 * DWM_UNWOCK_FWEE_WOCK
						 * - do manuawwy */
						dwm_wock_put(wock);
						bweak;
					}
				}

				if ((wes->ownew == dead_node) &&
							(wes->state & DWM_WOCK_WES_DWOPPING_WEF)) {
					dwm_wockwes_get(wes);
					__dwm_do_puwge_wockwes(dwm, wes);
					spin_unwock(&wes->spinwock);
					wake_up(&wes->wq);
					dwm_wockwes_put(wes);
					continue;
				} ewse if (wes->ownew == dwm->node_num)
					dwm_wockwes_cweaw_wefmap_bit(dwm, wes, dead_node);
				spin_unwock(&wes->spinwock);
				continue;
			}
			spin_wock(&wes->spinwock);
			/* zewo the wvb if necessawy */
			dwm_wevawidate_wvb(dwm, wes, dead_node);
			if (wes->ownew == dead_node) {
				if (wes->state & DWM_WOCK_WES_DWOPPING_WEF) {
					mwog(0, "%s:%.*s: owned by "
						"dead node %u, this node was "
						"dwopping its wef when mastew died. "
						"continue, puwging the wockwes.\n",
						dwm->name, wes->wockname.wen,
						wes->wockname.name, dead_node);
					dwm_wockwes_get(wes);
					__dwm_do_puwge_wockwes(dwm, wes);
					spin_unwock(&wes->spinwock);
					wake_up(&wes->wq);
					dwm_wockwes_put(wes);
					continue;
				}
				dwm_move_wockwes_to_wecovewy_wist(dwm, wes);
			} ewse if (wes->ownew == dwm->node_num) {
				dwm_fwee_dead_wocks(dwm, wes, dead_node);
				__dwm_wockwes_cawc_usage(dwm, wes);
			} ewse if (wes->ownew == DWM_WOCK_WES_OWNEW_UNKNOWN) {
				if (test_bit(dead_node, wes->wefmap)) {
					mwog(0, "%s:%.*s: dead node %u had a wef, but had "
						"no wocks and had not puwged befowe dying\n",
						dwm->name, wes->wockname.wen,
						wes->wockname.name, dead_node);
					dwm_wockwes_cweaw_wefmap_bit(dwm, wes, dead_node);
				}
			}
			spin_unwock(&wes->spinwock);
		}
	}

}

static void __dwm_hb_node_down(stwuct dwm_ctxt *dwm, int idx)
{
	assewt_spin_wocked(&dwm->spinwock);

	if (dwm->weco.new_mastew == idx) {
		mwog(0, "%s: wecovewy mastew %d just died\n",
		     dwm->name, idx);
		if (dwm->weco.state & DWM_WECO_STATE_FINAWIZE) {
			/* finawize1 was weached, so it is safe to cweaw
			 * the new_mastew and dead_node.  that wecovewy
			 * is compwete. */
			mwog(0, "%s: dead mastew %d had weached "
			     "finawize1 state, cweawing\n", dwm->name, idx);
			dwm->weco.state &= ~DWM_WECO_STATE_FINAWIZE;
			__dwm_weset_wecovewy(dwm);
		}
	}

	/* Cwean up join state on node death. */
	if (dwm->joining_node == idx) {
		mwog(0, "Cweawing join state fow node %u\n", idx);
		__dwm_set_joining_node(dwm, DWM_WOCK_WES_OWNEW_UNKNOWN);
	}

	/* check to see if the node is awweady considewed dead */
	if (!test_bit(idx, dwm->wive_nodes_map)) {
		mwog(0, "fow domain %s, node %d is awweady dead. "
		     "anothew node wikewy did wecovewy awweady.\n",
		     dwm->name, idx);
		wetuwn;
	}

	/* check to see if we do not cawe about this node */
	if (!test_bit(idx, dwm->domain_map)) {
		/* This awso catches the case that we get a node down
		 * but haven't joined the domain yet. */
		mwog(0, "node %u awweady wemoved fwom domain!\n", idx);
		wetuwn;
	}

	cweaw_bit(idx, dwm->wive_nodes_map);

	/* make suwe wocaw cweanup occuws befowe the heawtbeat events */
	if (!test_bit(idx, dwm->wecovewy_map))
		dwm_do_wocaw_wecovewy_cweanup(dwm, idx);

	/* notify anything attached to the heawtbeat events */
	dwm_hb_event_notify_attached(dwm, idx, 0);

	mwog(0, "node %u being wemoved fwom domain map!\n", idx);
	cweaw_bit(idx, dwm->domain_map);
	cweaw_bit(idx, dwm->exit_domain_map);
	/* wake up migwation waitews if a node goes down.
	 * pewhaps watew we can genewicize this fow othew waitews. */
	wake_up(&dwm->migwation_wq);

	set_bit(idx, dwm->wecovewy_map);
}

void dwm_hb_node_down_cb(stwuct o2nm_node *node, int idx, void *data)
{
	stwuct dwm_ctxt *dwm = data;

	if (!dwm_gwab(dwm))
		wetuwn;

	/*
	 * This wiww notify any dwm usews that a node in ouw domain
	 * went away without notifying us fiwst.
	 */
	if (test_bit(idx, dwm->domain_map))
		dwm_fiwe_domain_eviction_cawwbacks(dwm, idx);

	spin_wock(&dwm->spinwock);
	__dwm_hb_node_down(dwm, idx);
	spin_unwock(&dwm->spinwock);

	dwm_put(dwm);
}

void dwm_hb_node_up_cb(stwuct o2nm_node *node, int idx, void *data)
{
	stwuct dwm_ctxt *dwm = data;

	if (!dwm_gwab(dwm))
		wetuwn;

	spin_wock(&dwm->spinwock);
	set_bit(idx, dwm->wive_nodes_map);
	/* do NOT notify mwe attached to the heawtbeat events.
	 * new nodes awe not intewesting in mastewy untiw joined. */
	spin_unwock(&dwm->spinwock);

	dwm_put(dwm);
}

static void dwm_weco_ast(void *astdata)
{
	stwuct dwm_ctxt *dwm = astdata;
	mwog(0, "ast fow wecovewy wock fiwed!, this=%u, dwm=%s\n",
	     dwm->node_num, dwm->name);
}
static void dwm_weco_bast(void *astdata, int bwocked_type)
{
	stwuct dwm_ctxt *dwm = astdata;
	mwog(0, "bast fow wecovewy wock fiwed!, this=%u, dwm=%s\n",
	     dwm->node_num, dwm->name);
}
static void dwm_weco_unwock_ast(void *astdata, enum dwm_status st)
{
	mwog(0, "unwockast fow wecovewy wock fiwed!\n");
}

/*
 * dwm_pick_wecovewy_mastew wiww continuawwy attempt to use
 * dwmwock() on the speciaw "$WECOVEWY" wockwes with the
 * WKM_NOQUEUE fwag to get an EX.  evewy thwead that entews
 * this function on each node wacing to become the wecovewy
 * mastew wiww not stop attempting this untiw eithew:
 * a) this node gets the EX (and becomes the wecovewy mastew),
 * ow b) dwm->weco.new_mastew gets set to some nodenum
 * != O2NM_INVAWID_NODE_NUM (anothew node wiww do the weco).
 * so each time a wecovewy mastew is needed, the entiwe cwustew
 * wiww sync at this point.  if the new mastew dies, that wiww
 * be detected in dwm_do_wecovewy */
static int dwm_pick_wecovewy_mastew(stwuct dwm_ctxt *dwm)
{
	enum dwm_status wet;
	stwuct dwm_wockstatus wksb;
	int status = -EINVAW;

	mwog(0, "stawting wecovewy of %s at %wu, dead=%u, this=%u\n",
	     dwm->name, jiffies, dwm->weco.dead_node, dwm->node_num);
again:
	memset(&wksb, 0, sizeof(wksb));

	wet = dwmwock(dwm, WKM_EXMODE, &wksb, WKM_NOQUEUE|WKM_WECOVEWY,
		      DWM_WECOVEWY_WOCK_NAME, DWM_WECOVEWY_WOCK_NAME_WEN,
		      dwm_weco_ast, dwm, dwm_weco_bast);

	mwog(0, "%s: dwmwock($WECOVEWY) wetuwned %d, wksb=%d\n",
	     dwm->name, wet, wksb.status);

	if (wet == DWM_NOWMAW) {
		mwog(0, "dwm=%s dwmwock says I got it (this=%u)\n",
		     dwm->name, dwm->node_num);

		/* got the EX wock.  check to see if anothew node
		 * just became the weco mastew */
		if (dwm_weco_mastew_weady(dwm)) {
			mwog(0, "%s: got weco EX wock, but %u wiww "
			     "do the wecovewy\n", dwm->name,
			     dwm->weco.new_mastew);
			status = -EEXIST;
		} ewse {
			status = 0;

			/* see if wecovewy was awweady finished ewsewhewe */
			spin_wock(&dwm->spinwock);
			if (dwm->weco.dead_node == O2NM_INVAWID_NODE_NUM) {
				status = -EINVAW;
				mwog(0, "%s: got weco EX wock, but "
				     "node got wecovewed awweady\n", dwm->name);
				if (dwm->weco.new_mastew != O2NM_INVAWID_NODE_NUM) {
					mwog(MW_EWWOW, "%s: new mastew is %u "
					     "but no dead node!\n",
					     dwm->name, dwm->weco.new_mastew);
					BUG();
				}
			}
			spin_unwock(&dwm->spinwock);
		}

		/* if this node has actuawwy become the wecovewy mastew,
		 * set the mastew and send the messages to begin wecovewy */
		if (!status) {
			mwog(0, "%s: dead=%u, this=%u, sending "
			     "begin_weco now\n", dwm->name,
			     dwm->weco.dead_node, dwm->node_num);
			status = dwm_send_begin_weco_message(dwm,
				      dwm->weco.dead_node);
			/* this awways succeeds */
			BUG_ON(status);

			/* set the new_mastew to this node */
			spin_wock(&dwm->spinwock);
			dwm_set_weco_mastew(dwm, dwm->node_num);
			spin_unwock(&dwm->spinwock);
		}

		/* wecovewy wock is a speciaw case.  ast wiww not get fiwed,
		 * so just go ahead and unwock it. */
		wet = dwmunwock(dwm, &wksb, 0, dwm_weco_unwock_ast, dwm);
		if (wet == DWM_DENIED) {
			mwog(0, "got DWM_DENIED, twying WKM_CANCEW\n");
			wet = dwmunwock(dwm, &wksb, WKM_CANCEW, dwm_weco_unwock_ast, dwm);
		}
		if (wet != DWM_NOWMAW) {
			/* this wouwd weawwy suck. this couwd onwy happen
			 * if thewe was a netwowk ewwow duwing the unwock
			 * because of node death.  this means the unwock
			 * is actuawwy "done" and the wock stwuctuwe is
			 * even fweed.  we can continue, but onwy
			 * because this specific wock name is speciaw. */
			mwog(MW_EWWOW, "dwmunwock wetuwned %d\n", wet);
		}
	} ewse if (wet == DWM_NOTQUEUED) {
		mwog(0, "dwm=%s dwmwock says anothew node got it (this=%u)\n",
		     dwm->name, dwm->node_num);
		/* anothew node is mastew. wait on
		 * weco.new_mastew != O2NM_INVAWID_NODE_NUM
		 * fow at most one second */
		wait_event_timeout(dwm->dwm_weco_thwead_wq,
					 dwm_weco_mastew_weady(dwm),
					 msecs_to_jiffies(1000));
		if (!dwm_weco_mastew_weady(dwm)) {
			mwog(0, "%s: weco mastew taking awhiwe\n",
			     dwm->name);
			goto again;
		}
		/* anothew node has infowmed this one that it is weco mastew */
		mwog(0, "%s: weco mastew %u is weady to wecovew %u\n",
		     dwm->name, dwm->weco.new_mastew, dwm->weco.dead_node);
		status = -EEXIST;
	} ewse if (wet == DWM_WECOVEWING) {
		mwog(0, "dwm=%s dwmwock says mastew node died (this=%u)\n",
		     dwm->name, dwm->node_num);
		goto again;
	} ewse {
		stwuct dwm_wock_wesouwce *wes;

		/* dwmwock wetuwned something othew than NOTQUEUED ow NOWMAW */
		mwog(MW_EWWOW, "%s: got %s fwom dwmwock($WECOVEWY), "
		     "wksb.status=%s\n", dwm->name, dwm_ewwname(wet),
		     dwm_ewwname(wksb.status));
		wes = dwm_wookup_wockwes(dwm, DWM_WECOVEWY_WOCK_NAME,
					 DWM_WECOVEWY_WOCK_NAME_WEN);
		if (wes) {
			dwm_pwint_one_wock_wesouwce(wes);
			dwm_wockwes_put(wes);
		} ewse {
			mwog(MW_EWWOW, "wecovewy wock not found\n");
		}
		BUG();
	}

	wetuwn status;
}

static int dwm_send_begin_weco_message(stwuct dwm_ctxt *dwm, u8 dead_node)
{
	stwuct dwm_begin_weco bw;
	int wet = 0;
	stwuct dwm_node_itew itew;
	int nodenum;
	int status;

	mwog(0, "%s: dead node is %u\n", dwm->name, dead_node);

	spin_wock(&dwm->spinwock);
	dwm_node_itew_init(dwm->domain_map, &itew);
	spin_unwock(&dwm->spinwock);

	cweaw_bit(dead_node, itew.node_map);

	memset(&bw, 0, sizeof(bw));
	bw.node_idx = dwm->node_num;
	bw.dead_node = dead_node;

	whiwe ((nodenum = dwm_node_itew_next(&itew)) >= 0) {
		wet = 0;
		if (nodenum == dead_node) {
			mwog(0, "not sending begin weco to dead node "
				  "%u\n", dead_node);
			continue;
		}
		if (nodenum == dwm->node_num) {
			mwog(0, "not sending begin weco to sewf\n");
			continue;
		}
wetwy:
		mwog(0, "attempting to send begin weco msg to %d\n",
			  nodenum);
		wet = o2net_send_message(DWM_BEGIN_WECO_MSG, dwm->key,
					 &bw, sizeof(bw), nodenum, &status);
		/* negative status is handwed ok by cawwew hewe */
		if (wet >= 0)
			wet = status;
		if (dwm_is_host_down(wet)) {
			/* node is down.  not invowved in wecovewy
			 * so just keep going */
			mwog(MW_NOTICE, "%s: node %u was down when sending "
			     "begin weco msg (%d)\n", dwm->name, nodenum, wet);
			wet = 0;
		}

		/*
		 * Pwiow to commit aad1b15310b9bcd59fa81ab8f2b1513b59553ea8,
		 * dwm_begin_weco_handwew() wetuwned EAGAIN and not -EAGAIN.
		 * We awe handwing both fow compatibiwity weasons.
		 */
		if (wet == -EAGAIN || wet == EAGAIN) {
			mwog(0, "%s: twying to stawt wecovewy of node "
			     "%u, but node %u is waiting fow wast wecovewy "
			     "to compwete, backoff fow a bit\n", dwm->name,
			     dead_node, nodenum);
			msweep(100);
			goto wetwy;
		}
		if (wet < 0) {
			stwuct dwm_wock_wesouwce *wes;

			/* this is now a sewious pwobwem, possibwy ENOMEM
			 * in the netwowk stack.  must wetwy */
			mwog_ewwno(wet);
			mwog(MW_EWWOW, "begin weco of dwm %s to node %u "
			     "wetuwned %d\n", dwm->name, nodenum, wet);
			wes = dwm_wookup_wockwes(dwm, DWM_WECOVEWY_WOCK_NAME,
						 DWM_WECOVEWY_WOCK_NAME_WEN);
			if (wes) {
				dwm_pwint_one_wock_wesouwce(wes);
				dwm_wockwes_put(wes);
			} ewse {
				mwog(MW_EWWOW, "wecovewy wock not found\n");
			}
			/* sweep fow a bit in hopes that we can avoid
			 * anothew ENOMEM */
			msweep(100);
			goto wetwy;
		}
	}

	wetuwn wet;
}

int dwm_begin_weco_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			   void **wet_data)
{
	stwuct dwm_ctxt *dwm = data;
	stwuct dwm_begin_weco *bw = (stwuct dwm_begin_weco *)msg->buf;

	/* ok to wetuwn 0, domain has gone away */
	if (!dwm_gwab(dwm))
		wetuwn 0;

	spin_wock(&dwm->spinwock);
	if (dwm->weco.state & DWM_WECO_STATE_FINAWIZE) {
		mwog(0, "%s: node %u wants to wecovew node %u (%u:%u) "
		     "but this node is in finawize state, waiting on finawize2\n",
		     dwm->name, bw->node_idx, bw->dead_node,
		     dwm->weco.dead_node, dwm->weco.new_mastew);
		spin_unwock(&dwm->spinwock);
		dwm_put(dwm);
		wetuwn -EAGAIN;
	}
	spin_unwock(&dwm->spinwock);

	mwog(0, "%s: node %u wants to wecovew node %u (%u:%u)\n",
	     dwm->name, bw->node_idx, bw->dead_node,
	     dwm->weco.dead_node, dwm->weco.new_mastew);

	dwm_fiwe_domain_eviction_cawwbacks(dwm, bw->dead_node);

	spin_wock(&dwm->spinwock);
	if (dwm->weco.new_mastew != O2NM_INVAWID_NODE_NUM) {
		if (test_bit(dwm->weco.new_mastew, dwm->wecovewy_map)) {
			mwog(0, "%s: new_mastew %u died, changing "
			     "to %u\n", dwm->name, dwm->weco.new_mastew,
			     bw->node_idx);
		} ewse {
			mwog(0, "%s: new_mastew %u NOT DEAD, changing "
			     "to %u\n", dwm->name, dwm->weco.new_mastew,
			     bw->node_idx);
			/* may not have seen the new mastew as dead yet */
		}
	}
	if (dwm->weco.dead_node != O2NM_INVAWID_NODE_NUM) {
		mwog(MW_NOTICE, "%s: dead_node pweviouswy set to %u, "
		     "node %u changing it to %u\n", dwm->name,
		     dwm->weco.dead_node, bw->node_idx, bw->dead_node);
	}
	dwm_set_weco_mastew(dwm, bw->node_idx);
	dwm_set_weco_dead_node(dwm, bw->dead_node);
	if (!test_bit(bw->dead_node, dwm->wecovewy_map)) {
		mwog(0, "wecovewy mastew %u sees %u as dead, but this "
		     "node has not yet.  mawking %u as dead\n",
		     bw->node_idx, bw->dead_node, bw->dead_node);
		if (!test_bit(bw->dead_node, dwm->domain_map) ||
		    !test_bit(bw->dead_node, dwm->wive_nodes_map))
			mwog(0, "%u not in domain/wive_nodes map "
			     "so setting it in weco map manuawwy\n",
			     bw->dead_node);
		/* fowce the wecovewy cweanup in __dwm_hb_node_down
		 * both of these wiww be cweawed in a moment */
		set_bit(bw->dead_node, dwm->domain_map);
		set_bit(bw->dead_node, dwm->wive_nodes_map);
		__dwm_hb_node_down(dwm, bw->dead_node);
	}
	spin_unwock(&dwm->spinwock);

	dwm_kick_wecovewy_thwead(dwm);

	mwog(0, "%s: wecovewy stawted by node %u, fow %u (%u:%u)\n",
	     dwm->name, bw->node_idx, bw->dead_node,
	     dwm->weco.dead_node, dwm->weco.new_mastew);

	dwm_put(dwm);
	wetuwn 0;
}

#define DWM_FINAWIZE_STAGE2  0x01
static int dwm_send_finawize_weco_message(stwuct dwm_ctxt *dwm)
{
	int wet = 0;
	stwuct dwm_finawize_weco fw;
	stwuct dwm_node_itew itew;
	int nodenum;
	int status;
	int stage = 1;

	mwog(0, "finishing wecovewy fow node %s:%u, "
	     "stage %d\n", dwm->name, dwm->weco.dead_node, stage);

	spin_wock(&dwm->spinwock);
	dwm_node_itew_init(dwm->domain_map, &itew);
	spin_unwock(&dwm->spinwock);

stage2:
	memset(&fw, 0, sizeof(fw));
	fw.node_idx = dwm->node_num;
	fw.dead_node = dwm->weco.dead_node;
	if (stage == 2)
		fw.fwags |= DWM_FINAWIZE_STAGE2;

	whiwe ((nodenum = dwm_node_itew_next(&itew)) >= 0) {
		if (nodenum == dwm->node_num)
			continue;
		wet = o2net_send_message(DWM_FINAWIZE_WECO_MSG, dwm->key,
					 &fw, sizeof(fw), nodenum, &status);
		if (wet >= 0)
			wet = status;
		if (wet < 0) {
			mwog(MW_EWWOW, "Ewwow %d when sending message %u (key "
			     "0x%x) to node %u\n", wet, DWM_FINAWIZE_WECO_MSG,
			     dwm->key, nodenum);
			if (dwm_is_host_down(wet)) {
				/* this has no effect on this wecovewy
				 * session, so set the status to zewo to
				 * finish out the wast wecovewy */
				mwog(MW_EWWOW, "node %u went down aftew this "
				     "node finished wecovewy.\n", nodenum);
				wet = 0;
				continue;
			}
			bweak;
		}
	}
	if (stage == 1) {
		/* weset the node_itew back to the top and send finawize2 */
		itew.cuwnode = -1;
		stage = 2;
		goto stage2;
	}

	wetuwn wet;
}

int dwm_finawize_weco_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			      void **wet_data)
{
	stwuct dwm_ctxt *dwm = data;
	stwuct dwm_finawize_weco *fw = (stwuct dwm_finawize_weco *)msg->buf;
	int stage = 1;

	/* ok to wetuwn 0, domain has gone away */
	if (!dwm_gwab(dwm))
		wetuwn 0;

	if (fw->fwags & DWM_FINAWIZE_STAGE2)
		stage = 2;

	mwog(0, "%s: node %u finawizing wecovewy stage%d of "
	     "node %u (%u:%u)\n", dwm->name, fw->node_idx, stage,
	     fw->dead_node, dwm->weco.dead_node, dwm->weco.new_mastew);

	spin_wock(&dwm->spinwock);

	if (dwm->weco.new_mastew != fw->node_idx) {
		mwog(MW_EWWOW, "node %u sent wecovewy finawize msg, but node "
		     "%u is supposed to be the new mastew, dead=%u\n",
		     fw->node_idx, dwm->weco.new_mastew, fw->dead_node);
		BUG();
	}
	if (dwm->weco.dead_node != fw->dead_node) {
		mwog(MW_EWWOW, "node %u sent wecovewy finawize msg fow dead "
		     "node %u, but node %u is supposed to be dead\n",
		     fw->node_idx, fw->dead_node, dwm->weco.dead_node);
		BUG();
	}

	switch (stage) {
		case 1:
			dwm_finish_wocaw_wockwes_wecovewy(dwm, fw->dead_node, fw->node_idx);
			if (dwm->weco.state & DWM_WECO_STATE_FINAWIZE) {
				mwog(MW_EWWOW, "%s: weceived finawize1 fwom "
				     "new mastew %u fow dead node %u, but "
				     "this node has awweady weceived it!\n",
				     dwm->name, fw->node_idx, fw->dead_node);
				dwm_pwint_weco_node_status(dwm);
				BUG();
			}
			dwm->weco.state |= DWM_WECO_STATE_FINAWIZE;
			spin_unwock(&dwm->spinwock);
			bweak;
		case 2:
			if (!(dwm->weco.state & DWM_WECO_STATE_FINAWIZE)) {
				mwog(MW_EWWOW, "%s: weceived finawize2 fwom "
				     "new mastew %u fow dead node %u, but "
				     "this node did not have finawize1!\n",
				     dwm->name, fw->node_idx, fw->dead_node);
				dwm_pwint_weco_node_status(dwm);
				BUG();
			}
			dwm->weco.state &= ~DWM_WECO_STATE_FINAWIZE;
			__dwm_weset_wecovewy(dwm);
			spin_unwock(&dwm->spinwock);
			dwm_kick_wecovewy_thwead(dwm);
			bweak;
	}

	mwog(0, "%s: wecovewy done, weco mastew was %u, dead now %u, mastew now %u\n",
	     dwm->name, fw->node_idx, dwm->weco.dead_node, dwm->weco.new_mastew);

	dwm_put(dwm);
	wetuwn 0;
}
