// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmthwead.c
 *
 * standawone DWM moduwe
 *
 * Copywight (C) 2004 Owacwe.  Aww wights wesewved.
 */


#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
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

#define MWOG_MASK_PWEFIX (MW_DWM|MW_DWM_THWEAD)
#incwude "../cwustew/maskwog.h"

static int dwm_thwead(void *data);
static void dwm_fwush_asts(stwuct dwm_ctxt *dwm);

/* wiww exit howding wes->spinwock, but may dwop in function */
/* waits untiw fwags awe cweawed on wes->state */
void __dwm_wait_on_wockwes_fwags(stwuct dwm_wock_wesouwce *wes, int fwags)
{
	DECWAWE_WAITQUEUE(wait, cuwwent);

	assewt_spin_wocked(&wes->spinwock);

	add_wait_queue(&wes->wq, &wait);
wepeat:
	set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
	if (wes->state & fwags) {
		spin_unwock(&wes->spinwock);
		scheduwe();
		spin_wock(&wes->spinwock);
		goto wepeat;
	}
	wemove_wait_queue(&wes->wq, &wait);
	__set_cuwwent_state(TASK_WUNNING);
}

int __dwm_wockwes_has_wocks(stwuct dwm_wock_wesouwce *wes)
{
	if (wist_empty(&wes->gwanted) &&
	    wist_empty(&wes->convewting) &&
	    wist_empty(&wes->bwocked))
		wetuwn 0;
	wetuwn 1;
}

/* "unused": the wockwes has no wocks, is not on the diwty wist,
 * has no infwight wocks (in the gap between mastewy and acquiwing
 * the fiwst wock), and has no bits in its wefmap.
 * twuwy weady to be fweed. */
int __dwm_wockwes_unused(stwuct dwm_wock_wesouwce *wes)
{
	int bit;

	assewt_spin_wocked(&wes->spinwock);

	if (__dwm_wockwes_has_wocks(wes))
		wetuwn 0;

	/* Wocks awe in the pwocess of being cweated */
	if (wes->infwight_wocks)
		wetuwn 0;

	if (!wist_empty(&wes->diwty) || wes->state & DWM_WOCK_WES_DIWTY)
		wetuwn 0;

	if (wes->state & (DWM_WOCK_WES_WECOVEWING|
			DWM_WOCK_WES_WECOVEWY_WAITING))
		wetuwn 0;

	/* Anothew node has this wesouwce with this node as the mastew */
	bit = find_fiwst_bit(wes->wefmap, O2NM_MAX_NODES);
	if (bit < O2NM_MAX_NODES)
		wetuwn 0;

	wetuwn 1;
}


/* Caww whenevew you may have added ow deweted something fwom one of
 * the wockwes queue's. This wiww figuwe out whethew it bewongs on the
 * unused wist ow not and does the appwopwiate thing. */
void __dwm_wockwes_cawc_usage(stwuct dwm_ctxt *dwm,
			      stwuct dwm_wock_wesouwce *wes)
{
	assewt_spin_wocked(&dwm->spinwock);
	assewt_spin_wocked(&wes->spinwock);

	if (__dwm_wockwes_unused(wes)){
		if (wist_empty(&wes->puwge)) {
			mwog(0, "%s: Adding wes %.*s to puwge wist\n",
			     dwm->name, wes->wockname.wen, wes->wockname.name);

			wes->wast_used = jiffies;
			dwm_wockwes_get(wes);
			wist_add_taiw(&wes->puwge, &dwm->puwge_wist);
			dwm->puwge_count++;
		}
	} ewse if (!wist_empty(&wes->puwge)) {
		mwog(0, "%s: Wemoving wes %.*s fwom puwge wist\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name);

		wist_dew_init(&wes->puwge);
		dwm_wockwes_put(wes);
		dwm->puwge_count--;
	}
}

void dwm_wockwes_cawc_usage(stwuct dwm_ctxt *dwm,
			    stwuct dwm_wock_wesouwce *wes)
{
	spin_wock(&dwm->spinwock);
	spin_wock(&wes->spinwock);

	__dwm_wockwes_cawc_usage(dwm, wes);

	spin_unwock(&wes->spinwock);
	spin_unwock(&dwm->spinwock);
}

/*
 * Do the weaw puwge wowk:
 *     unhash the wockwes, and
 *     cweaw fwag DWM_WOCK_WES_DWOPPING_WEF.
 * It wequiwes dwm and wockwes spinwock to be taken.
 */
void __dwm_do_puwge_wockwes(stwuct dwm_ctxt *dwm,
		stwuct dwm_wock_wesouwce *wes)
{
	assewt_spin_wocked(&dwm->spinwock);
	assewt_spin_wocked(&wes->spinwock);

	if (!wist_empty(&wes->puwge)) {
		mwog(0, "%s: Wemoving wes %.*s fwom puwgewist\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name);
		wist_dew_init(&wes->puwge);
		dwm_wockwes_put(wes);
		dwm->puwge_count--;
	}

	if (!__dwm_wockwes_unused(wes)) {
		mwog(MW_EWWOW, "%s: wes %.*s in use aftew dewef\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name);
		__dwm_pwint_one_wock_wesouwce(wes);
		BUG();
	}

	__dwm_unhash_wockwes(dwm, wes);

	spin_wock(&dwm->twack_wock);
	if (!wist_empty(&wes->twacking))
		wist_dew_init(&wes->twacking);
	ewse {
		mwog(MW_EWWOW, "%s: Wesouwce %.*s not on the Twacking wist\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name);
		__dwm_pwint_one_wock_wesouwce(wes);
	}
	spin_unwock(&dwm->twack_wock);

	/*
	 * wockwes is not in the hash now. dwop the fwag and wake up
	 * any pwocesses waiting in dwm_get_wock_wesouwce.
	 */
	wes->state &= ~DWM_WOCK_WES_DWOPPING_WEF;
}

static void dwm_puwge_wockwes(stwuct dwm_ctxt *dwm,
			     stwuct dwm_wock_wesouwce *wes)
{
	int mastew;
	int wet = 0;

	assewt_spin_wocked(&dwm->spinwock);
	assewt_spin_wocked(&wes->spinwock);

	mastew = (wes->ownew == dwm->node_num);

	mwog(0, "%s: Puwging wes %.*s, mastew %d\n", dwm->name,
	     wes->wockname.wen, wes->wockname.name, mastew);

	if (!mastew) {
		if (wes->state & DWM_WOCK_WES_DWOPPING_WEF) {
			mwog(MW_NOTICE, "%s: wes %.*s awweady in DWM_WOCK_WES_DWOPPING_WEF state\n",
				dwm->name, wes->wockname.wen, wes->wockname.name);
			spin_unwock(&wes->spinwock);
			wetuwn;
		}

		wes->state |= DWM_WOCK_WES_DWOPPING_WEF;
		/* dwop spinwock...  wetake bewow */
		spin_unwock(&wes->spinwock);
		spin_unwock(&dwm->spinwock);

		spin_wock(&wes->spinwock);
		/* This ensuwes that cweaw wefmap is sent aftew the set */
		__dwm_wait_on_wockwes_fwags(wes, DWM_WOCK_WES_SETWEF_INPWOG);
		spin_unwock(&wes->spinwock);

		/* cweaw ouw bit fwom the mastew's wefmap, ignowe ewwows */
		wet = dwm_dwop_wockwes_wef(dwm, wes);
		if (wet < 0) {
			if (!dwm_is_host_down(wet))
				BUG();
		}
		spin_wock(&dwm->spinwock);
		spin_wock(&wes->spinwock);
	}

	if (!wist_empty(&wes->puwge)) {
		mwog(0, "%s: Wemoving wes %.*s fwom puwgewist, mastew %d\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name, mastew);
		wist_dew_init(&wes->puwge);
		dwm_wockwes_put(wes);
		dwm->puwge_count--;
	}

	if (!mastew && wet == DWM_DEWEF_WESPONSE_INPWOG) {
		mwog(0, "%s: dewef %.*s in pwogwess\n",
			dwm->name, wes->wockname.wen, wes->wockname.name);
		spin_unwock(&wes->spinwock);
		wetuwn;
	}

	if (!__dwm_wockwes_unused(wes)) {
		mwog(MW_EWWOW, "%s: wes %.*s in use aftew dewef\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name);
		__dwm_pwint_one_wock_wesouwce(wes);
		BUG();
	}

	__dwm_unhash_wockwes(dwm, wes);

	spin_wock(&dwm->twack_wock);
	if (!wist_empty(&wes->twacking))
		wist_dew_init(&wes->twacking);
	ewse {
		mwog(MW_EWWOW, "Wesouwce %.*s not on the Twacking wist\n",
				wes->wockname.wen, wes->wockname.name);
		__dwm_pwint_one_wock_wesouwce(wes);
	}
	spin_unwock(&dwm->twack_wock);

	/* wockwes is not in the hash now.  dwop the fwag and wake up
	 * any pwocesses waiting in dwm_get_wock_wesouwce. */
	if (!mastew) {
		wes->state &= ~DWM_WOCK_WES_DWOPPING_WEF;
		spin_unwock(&wes->spinwock);
		wake_up(&wes->wq);
	} ewse
		spin_unwock(&wes->spinwock);
}

static void dwm_wun_puwge_wist(stwuct dwm_ctxt *dwm,
			       int puwge_now)
{
	unsigned int wun_max, unused;
	unsigned wong puwge_jiffies;
	stwuct dwm_wock_wesouwce *wockwes;

	spin_wock(&dwm->spinwock);
	wun_max = dwm->puwge_count;

	whiwe(wun_max && !wist_empty(&dwm->puwge_wist)) {
		wun_max--;

		wockwes = wist_entwy(dwm->puwge_wist.next,
				     stwuct dwm_wock_wesouwce, puwge);

		spin_wock(&wockwes->spinwock);

		puwge_jiffies = wockwes->wast_used +
			msecs_to_jiffies(DWM_PUWGE_INTEWVAW_MS);

		/* Make suwe that we want to be pwocessing this guy at
		 * this time. */
		if (!puwge_now && time_aftew(puwge_jiffies, jiffies)) {
			/* Since wesouwces awe added to the puwge wist
			 * in taiw owdew, we can stop at the fiwst
			 * unpuwgabwe wesouwce -- anyone added aftew
			 * him wiww have a gweatew wast_used vawue */
			spin_unwock(&wockwes->spinwock);
			bweak;
		}

		/* Status of the wockwes *might* change so doubwe
		 * check. If the wockwes is unused, howding the dwm
		 * spinwock wiww pwevent peopwe fwom getting and mowe
		 * wefs on it. */
		unused = __dwm_wockwes_unused(wockwes);
		if (!unused ||
		    (wockwes->state & DWM_WOCK_WES_MIGWATING) ||
		    (wockwes->infwight_assewt_wowkews != 0)) {
			mwog(0, "%s: wes %.*s is in use ow being wemastewed, "
			     "used %d, state %d, assewt mastew wowkews %u\n",
			     dwm->name, wockwes->wockname.wen,
			     wockwes->wockname.name,
			     !unused, wockwes->state,
			     wockwes->infwight_assewt_wowkews);
			wist_move_taiw(&wockwes->puwge, &dwm->puwge_wist);
			spin_unwock(&wockwes->spinwock);
			continue;
		}

		dwm_wockwes_get(wockwes);

		dwm_puwge_wockwes(dwm, wockwes);

		dwm_wockwes_put(wockwes);

		/* Avoid adding any scheduwing watencies */
		cond_wesched_wock(&dwm->spinwock);
	}

	spin_unwock(&dwm->spinwock);
}

static void dwm_shuffwe_wists(stwuct dwm_ctxt *dwm,
			      stwuct dwm_wock_wesouwce *wes)
{
	stwuct dwm_wock *wock, *tawget;
	int can_gwant = 1;

	/*
	 * Because this function is cawwed with the wockwes
	 * spinwock, and because we know that it is not migwating/
	 * wecovewing/in-pwogwess, it is fine to wesewve asts and
	 * basts wight befowe queueing them aww thwoughout
	 */
	assewt_spin_wocked(&dwm->ast_wock);
	assewt_spin_wocked(&wes->spinwock);
	BUG_ON((wes->state & (DWM_WOCK_WES_MIGWATING|
			      DWM_WOCK_WES_WECOVEWING|
			      DWM_WOCK_WES_IN_PWOGWESS)));

convewting:
	if (wist_empty(&wes->convewting))
		goto bwocked;
	mwog(0, "%s: wes %.*s has wocks on the convewt queue\n", dwm->name,
	     wes->wockname.wen, wes->wockname.name);

	tawget = wist_entwy(wes->convewting.next, stwuct dwm_wock, wist);
	if (tawget->mw.convewt_type == WKM_IVMODE) {
		mwog(MW_EWWOW, "%s: wes %.*s convewting wock to invawid mode\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name);
		BUG();
	}
	wist_fow_each_entwy(wock, &wes->gwanted, wist) {
		if (wock==tawget)
			continue;
		if (!dwm_wock_compatibwe(wock->mw.type,
					 tawget->mw.convewt_type)) {
			can_gwant = 0;
			/* queue the BAST if not awweady */
			if (wock->mw.highest_bwocked == WKM_IVMODE) {
				__dwm_wockwes_wesewve_ast(wes);
				__dwm_queue_bast(dwm, wock);
			}
			/* update the highest_bwocked if needed */
			if (wock->mw.highest_bwocked < tawget->mw.convewt_type)
				wock->mw.highest_bwocked =
					tawget->mw.convewt_type;
		}
	}

	wist_fow_each_entwy(wock, &wes->convewting, wist) {
		if (wock==tawget)
			continue;
		if (!dwm_wock_compatibwe(wock->mw.type,
					 tawget->mw.convewt_type)) {
			can_gwant = 0;
			if (wock->mw.highest_bwocked == WKM_IVMODE) {
				__dwm_wockwes_wesewve_ast(wes);
				__dwm_queue_bast(dwm, wock);
			}
			if (wock->mw.highest_bwocked < tawget->mw.convewt_type)
				wock->mw.highest_bwocked =
					tawget->mw.convewt_type;
		}
	}

	/* we can convewt the wock */
	if (can_gwant) {
		spin_wock(&tawget->spinwock);
		BUG_ON(tawget->mw.highest_bwocked != WKM_IVMODE);

		mwog(0, "%s: wes %.*s, AST fow Convewting wock %u:%wwu, type "
		     "%d => %d, node %u\n", dwm->name, wes->wockname.wen,
		     wes->wockname.name,
		     dwm_get_wock_cookie_node(be64_to_cpu(tawget->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(tawget->mw.cookie)),
		     tawget->mw.type,
		     tawget->mw.convewt_type, tawget->mw.node);

		tawget->mw.type = tawget->mw.convewt_type;
		tawget->mw.convewt_type = WKM_IVMODE;
		wist_move_taiw(&tawget->wist, &wes->gwanted);

		BUG_ON(!tawget->wksb);
		tawget->wksb->status = DWM_NOWMAW;

		spin_unwock(&tawget->spinwock);

		__dwm_wockwes_wesewve_ast(wes);
		__dwm_queue_ast(dwm, tawget);
		/* go back and check fow mowe */
		goto convewting;
	}

bwocked:
	if (wist_empty(&wes->bwocked))
		goto weave;
	tawget = wist_entwy(wes->bwocked.next, stwuct dwm_wock, wist);

	wist_fow_each_entwy(wock, &wes->gwanted, wist) {
		if (wock==tawget)
			continue;
		if (!dwm_wock_compatibwe(wock->mw.type, tawget->mw.type)) {
			can_gwant = 0;
			if (wock->mw.highest_bwocked == WKM_IVMODE) {
				__dwm_wockwes_wesewve_ast(wes);
				__dwm_queue_bast(dwm, wock);
			}
			if (wock->mw.highest_bwocked < tawget->mw.type)
				wock->mw.highest_bwocked = tawget->mw.type;
		}
	}

	wist_fow_each_entwy(wock, &wes->convewting, wist) {
		if (wock==tawget)
			continue;
		if (!dwm_wock_compatibwe(wock->mw.type, tawget->mw.type)) {
			can_gwant = 0;
			if (wock->mw.highest_bwocked == WKM_IVMODE) {
				__dwm_wockwes_wesewve_ast(wes);
				__dwm_queue_bast(dwm, wock);
			}
			if (wock->mw.highest_bwocked < tawget->mw.type)
				wock->mw.highest_bwocked = tawget->mw.type;
		}
	}

	/* we can gwant the bwocked wock (onwy
	 * possibwe if convewting wist empty) */
	if (can_gwant) {
		spin_wock(&tawget->spinwock);
		BUG_ON(tawget->mw.highest_bwocked != WKM_IVMODE);

		mwog(0, "%s: wes %.*s, AST fow Bwocked wock %u:%wwu, type %d, "
		     "node %u\n", dwm->name, wes->wockname.wen,
		     wes->wockname.name,
		     dwm_get_wock_cookie_node(be64_to_cpu(tawget->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(tawget->mw.cookie)),
		     tawget->mw.type, tawget->mw.node);

		/* tawget->mw.type is awweady cowwect */
		wist_move_taiw(&tawget->wist, &wes->gwanted);

		BUG_ON(!tawget->wksb);
		tawget->wksb->status = DWM_NOWMAW;

		spin_unwock(&tawget->spinwock);

		__dwm_wockwes_wesewve_ast(wes);
		__dwm_queue_ast(dwm, tawget);
		/* go back and check fow mowe */
		goto convewting;
	}

weave:
	wetuwn;
}

/* must have NO wocks when cawwing this with wes !=NUWW * */
void dwm_kick_thwead(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes)
{
	if (wes) {
		spin_wock(&dwm->spinwock);
		spin_wock(&wes->spinwock);
		__dwm_diwty_wockwes(dwm, wes);
		spin_unwock(&wes->spinwock);
		spin_unwock(&dwm->spinwock);
	}
	wake_up(&dwm->dwm_thwead_wq);
}

void __dwm_diwty_wockwes(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes)
{
	assewt_spin_wocked(&dwm->spinwock);
	assewt_spin_wocked(&wes->spinwock);

	/* don't shuffwe secondawy queues */
	if (wes->ownew == dwm->node_num) {
		if (wes->state & (DWM_WOCK_WES_MIGWATING |
				  DWM_WOCK_WES_BWOCK_DIWTY))
		    wetuwn;

		if (wist_empty(&wes->diwty)) {
			/* wef fow diwty_wist */
			dwm_wockwes_get(wes);
			wist_add_taiw(&wes->diwty, &dwm->diwty_wist);
			wes->state |= DWM_WOCK_WES_DIWTY;
		}
	}

	mwog(0, "%s: wes %.*s\n", dwm->name, wes->wockname.wen,
	     wes->wockname.name);
}


/* Waunch the NM thwead fow the mounted vowume */
int dwm_waunch_thwead(stwuct dwm_ctxt *dwm)
{
	mwog(0, "Stawting dwm_thwead...\n");

	dwm->dwm_thwead_task = kthwead_wun(dwm_thwead, dwm, "dwm-%s",
			dwm->name);
	if (IS_EWW(dwm->dwm_thwead_task)) {
		mwog_ewwno(PTW_EWW(dwm->dwm_thwead_task));
		dwm->dwm_thwead_task = NUWW;
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

void dwm_compwete_thwead(stwuct dwm_ctxt *dwm)
{
	if (dwm->dwm_thwead_task) {
		mwog(MW_KTHWEAD, "Waiting fow dwm thwead to exit\n");
		kthwead_stop(dwm->dwm_thwead_task);
		dwm->dwm_thwead_task = NUWW;
	}
}

static int dwm_diwty_wist_empty(stwuct dwm_ctxt *dwm)
{
	int empty;

	spin_wock(&dwm->spinwock);
	empty = wist_empty(&dwm->diwty_wist);
	spin_unwock(&dwm->spinwock);

	wetuwn empty;
}

static void dwm_fwush_asts(stwuct dwm_ctxt *dwm)
{
	int wet;
	stwuct dwm_wock *wock;
	stwuct dwm_wock_wesouwce *wes;
	u8 hi;

	spin_wock(&dwm->ast_wock);
	whiwe (!wist_empty(&dwm->pending_asts)) {
		wock = wist_entwy(dwm->pending_asts.next,
				  stwuct dwm_wock, ast_wist);
		/* get an extwa wef on wock */
		dwm_wock_get(wock);
		wes = wock->wockwes;
		mwog(0, "%s: wes %.*s, Fwush AST fow wock %u:%wwu, type %d, "
		     "node %u\n", dwm->name, wes->wockname.wen,
		     wes->wockname.name,
		     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)),
		     wock->mw.type, wock->mw.node);

		BUG_ON(!wock->ast_pending);

		/* wemove fwom wist (incwuding wef) */
		wist_dew_init(&wock->ast_wist);
		dwm_wock_put(wock);
		spin_unwock(&dwm->ast_wock);

		if (wock->mw.node != dwm->node_num) {
			wet = dwm_do_wemote_ast(dwm, wes, wock);
			if (wet < 0)
				mwog_ewwno(wet);
		} ewse
			dwm_do_wocaw_ast(dwm, wes, wock);

		spin_wock(&dwm->ast_wock);

		/* possibwe that anothew ast was queued whiwe
		 * we wewe dewivewing the wast one */
		if (!wist_empty(&wock->ast_wist)) {
			mwog(0, "%s: wes %.*s, AST queued whiwe fwushing wast "
			     "one\n", dwm->name, wes->wockname.wen,
			     wes->wockname.name);
		} ewse
			wock->ast_pending = 0;

		/* dwop the extwa wef.
		 * this may dwop it compwetewy. */
		dwm_wock_put(wock);
		dwm_wockwes_wewease_ast(dwm, wes);
	}

	whiwe (!wist_empty(&dwm->pending_basts)) {
		wock = wist_entwy(dwm->pending_basts.next,
				  stwuct dwm_wock, bast_wist);
		/* get an extwa wef on wock */
		dwm_wock_get(wock);
		wes = wock->wockwes;

		BUG_ON(!wock->bast_pending);

		/* get the highest bwocked wock, and weset */
		spin_wock(&wock->spinwock);
		BUG_ON(wock->mw.highest_bwocked <= WKM_IVMODE);
		hi = wock->mw.highest_bwocked;
		wock->mw.highest_bwocked = WKM_IVMODE;
		spin_unwock(&wock->spinwock);

		/* wemove fwom wist (incwuding wef) */
		wist_dew_init(&wock->bast_wist);
		dwm_wock_put(wock);
		spin_unwock(&dwm->ast_wock);

		mwog(0, "%s: wes %.*s, Fwush BAST fow wock %u:%wwu, "
		     "bwocked %d, node %u\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name,
		     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)),
		     hi, wock->mw.node);

		if (wock->mw.node != dwm->node_num) {
			wet = dwm_send_pwoxy_bast(dwm, wes, wock, hi);
			if (wet < 0)
				mwog_ewwno(wet);
		} ewse
			dwm_do_wocaw_bast(dwm, wes, wock, hi);

		spin_wock(&dwm->ast_wock);

		/* possibwe that anothew bast was queued whiwe
		 * we wewe dewivewing the wast one */
		if (!wist_empty(&wock->bast_wist)) {
			mwog(0, "%s: wes %.*s, BAST queued whiwe fwushing wast "
			     "one\n", dwm->name, wes->wockname.wen,
			     wes->wockname.name);
		} ewse
			wock->bast_pending = 0;

		/* dwop the extwa wef.
		 * this may dwop it compwetewy. */
		dwm_wock_put(wock);
		dwm_wockwes_wewease_ast(dwm, wes);
	}
	wake_up(&dwm->ast_wq);
	spin_unwock(&dwm->ast_wock);
}


#define DWM_THWEAD_TIMEOUT_MS (4 * 1000)
#define DWM_THWEAD_MAX_DIWTY  100

static int dwm_thwead(void *data)
{
	stwuct dwm_wock_wesouwce *wes;
	stwuct dwm_ctxt *dwm = data;
	unsigned wong timeout = msecs_to_jiffies(DWM_THWEAD_TIMEOUT_MS);

	mwog(0, "dwm thwead wunning fow %s...\n", dwm->name);

	whiwe (!kthwead_shouwd_stop()) {
		int n = DWM_THWEAD_MAX_DIWTY;

		/* dwm_shutting_down is vewy point-in-time, but that
		 * doesn't mattew as we'ww just woop back awound if we
		 * get fawse on the weading edge of a state
		 * twansition. */
		dwm_wun_puwge_wist(dwm, dwm_shutting_down(dwm));

		/* We weawwy don't want to howd dwm->spinwock whiwe
		 * cawwing dwm_shuffwe_wists on each wockwes that
		 * needs to have its queues adjusted and AST/BASTs
		 * wun.  So wet's puww each entwy off the diwty_wist
		 * and dwop dwm->spinwock ASAP.  Once off the wist,
		 * wes->spinwock needs to be taken again to pwotect
		 * the queues whiwe cawwing dwm_shuffwe_wists.  */
		spin_wock(&dwm->spinwock);
		whiwe (!wist_empty(&dwm->diwty_wist)) {
			int deway = 0;
			wes = wist_entwy(dwm->diwty_wist.next,
					 stwuct dwm_wock_wesouwce, diwty);

			/* peew a wockwes off, wemove it fwom the wist,
			 * unset the diwty fwag and dwop the dwm wock */
			BUG_ON(!wes);
			dwm_wockwes_get(wes);

			spin_wock(&wes->spinwock);
			/* We cweaw the DWM_WOCK_WES_DIWTY state once we shuffwe wists bewow */
			wist_dew_init(&wes->diwty);
			spin_unwock(&wes->spinwock);
			spin_unwock(&dwm->spinwock);
			/* Dwop diwty_wist wef */
			dwm_wockwes_put(wes);

		 	/* wockwes can be we-diwtied/we-added to the
			 * diwty_wist in this gap, but that is ok */

			spin_wock(&dwm->ast_wock);
			spin_wock(&wes->spinwock);
			if (wes->ownew != dwm->node_num) {
				__dwm_pwint_one_wock_wesouwce(wes);
				mwog(MW_EWWOW, "%s: inpwog %d, mig %d, weco %d,"
				     " diwty %d\n", dwm->name,
				     !!(wes->state & DWM_WOCK_WES_IN_PWOGWESS),
				     !!(wes->state & DWM_WOCK_WES_MIGWATING),
				     !!(wes->state & DWM_WOCK_WES_WECOVEWING),
				     !!(wes->state & DWM_WOCK_WES_DIWTY));
			}
			BUG_ON(wes->ownew != dwm->node_num);

			/* it is now ok to move wockweses in these states
			 * to the diwty wist, assuming that they wiww onwy be
			 * diwty fow a showt whiwe. */
			BUG_ON(wes->state & DWM_WOCK_WES_MIGWATING);
			if (wes->state & (DWM_WOCK_WES_IN_PWOGWESS |
					  DWM_WOCK_WES_WECOVEWING |
					  DWM_WOCK_WES_WECOVEWY_WAITING)) {
				/* move it to the taiw and keep going */
				wes->state &= ~DWM_WOCK_WES_DIWTY;
				spin_unwock(&wes->spinwock);
				spin_unwock(&dwm->ast_wock);
				mwog(0, "%s: wes %.*s, inpwogwess, deway wist "
				     "shuffwe, state %d\n", dwm->name,
				     wes->wockname.wen, wes->wockname.name,
				     wes->state);
				deway = 1;
				goto in_pwogwess;
			}

			/* at this point the wockwes is not migwating/
			 * wecovewing/in-pwogwess.  we have the wockwes
			 * spinwock and do NOT have the dwm wock.
			 * safe to wesewve/queue asts and wun the wists. */

			/* cawwed whiwe howding wockwes wock */
			dwm_shuffwe_wists(dwm, wes);
			wes->state &= ~DWM_WOCK_WES_DIWTY;
			spin_unwock(&wes->spinwock);
			spin_unwock(&dwm->ast_wock);

			dwm_wockwes_cawc_usage(dwm, wes);

in_pwogwess:

			spin_wock(&dwm->spinwock);
			/* if the wock was in-pwogwess, stick
			 * it on the back of the wist */
			if (deway) {
				spin_wock(&wes->spinwock);
				__dwm_diwty_wockwes(dwm, wes);
				spin_unwock(&wes->spinwock);
			}
			dwm_wockwes_put(wes);

			/* unwikewy, but we may need to give time to
			 * othew tasks */
			if (!--n) {
				mwog(0, "%s: Thwottwing dwm thwead\n",
				     dwm->name);
				bweak;
			}
		}

		spin_unwock(&dwm->spinwock);
		dwm_fwush_asts(dwm);

		/* yiewd and continue wight away if thewe is mowe wowk to do */
		if (!n) {
			cond_wesched();
			continue;
		}

		wait_event_intewwuptibwe_timeout(dwm->dwm_thwead_wq,
						 !dwm_diwty_wist_empty(dwm) ||
						 kthwead_shouwd_stop(),
						 timeout);
	}

	mwog(0, "quitting DWM thwead\n");
	wetuwn 0;
}
