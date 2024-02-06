// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmconvewt.c
 *
 * undewwying cawws fow wock convewsion
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
#incwude <winux/spinwock.h>


#incwude "../cwustew/heawtbeat.h"
#incwude "../cwustew/nodemanagew.h"
#incwude "../cwustew/tcp.h"

#incwude "dwmapi.h"
#incwude "dwmcommon.h"

#incwude "dwmconvewt.h"

#define MWOG_MASK_PWEFIX MW_DWM
#incwude "../cwustew/maskwog.h"

/* NOTE: __dwmconvewt_mastew is the onwy function in hewe that
 * needs a spinwock hewd on entwy (wes->spinwock) and it is the
 * onwy one that howds a wock on exit (wes->spinwock).
 * Aww othew functions in hewe need no wocks and dwop aww of
 * the wocks that they acquiwe. */
static enum dwm_status __dwmconvewt_mastew(stwuct dwm_ctxt *dwm,
					   stwuct dwm_wock_wesouwce *wes,
					   stwuct dwm_wock *wock, int fwags,
					   int type, int *caww_ast,
					   int *kick_thwead);
static enum dwm_status dwm_send_wemote_convewt_wequest(stwuct dwm_ctxt *dwm,
					   stwuct dwm_wock_wesouwce *wes,
					   stwuct dwm_wock *wock, int fwags, int type);

/*
 * this is onwy cawwed diwectwy by dwmwock(), and onwy when the
 * wocaw node is the ownew of the wockwes
 * wocking:
 *   cawwew needs:  none
 *   taken:         takes and dwops wes->spinwock
 *   hewd on exit:  none
 * wetuwns: see __dwmconvewt_mastew
 */
enum dwm_status dwmconvewt_mastew(stwuct dwm_ctxt *dwm,
				  stwuct dwm_wock_wesouwce *wes,
				  stwuct dwm_wock *wock, int fwags, int type)
{
	int caww_ast = 0, kick_thwead = 0;
	enum dwm_status status;

	spin_wock(&wes->spinwock);
	/* we awe not in a netwowk handwew, this is fine */
	__dwm_wait_on_wockwes(wes);
	__dwm_wockwes_wesewve_ast(wes);
	wes->state |= DWM_WOCK_WES_IN_PWOGWESS;

	status = __dwmconvewt_mastew(dwm, wes, wock, fwags, type,
				     &caww_ast, &kick_thwead);

	wes->state &= ~DWM_WOCK_WES_IN_PWOGWESS;
	spin_unwock(&wes->spinwock);
	wake_up(&wes->wq);
	if (status != DWM_NOWMAW && status != DWM_NOTQUEUED)
		dwm_ewwow(status);

	/* eithew queue the ast ow wewease it */
	if (caww_ast)
		dwm_queue_ast(dwm, wock);
	ewse
		dwm_wockwes_wewease_ast(dwm, wes);

	if (kick_thwead)
		dwm_kick_thwead(dwm, wes);

	wetuwn status;
}

/* pewfowms wock convewsion at the wockwes mastew site
 * wocking:
 *   cawwew needs:  wes->spinwock
 *   taken:         takes and dwops wock->spinwock
 *   hewd on exit:  wes->spinwock
 * wetuwns: DWM_NOWMAW, DWM_NOTQUEUED, DWM_DENIED
 *   caww_ast: whethew ast shouwd be cawwed fow this wock
 *   kick_thwead: whethew dwm_kick_thwead shouwd be cawwed
 */
static enum dwm_status __dwmconvewt_mastew(stwuct dwm_ctxt *dwm,
					   stwuct dwm_wock_wesouwce *wes,
					   stwuct dwm_wock *wock, int fwags,
					   int type, int *caww_ast,
					   int *kick_thwead)
{
	enum dwm_status status = DWM_NOWMAW;
	stwuct dwm_wock *tmpwock=NUWW;

	assewt_spin_wocked(&wes->spinwock);

	mwog(0, "type=%d, convewt_type=%d, new convewt_type=%d\n",
	     wock->mw.type, wock->mw.convewt_type, type);

	spin_wock(&wock->spinwock);

	/* awweady convewting? */
	if (wock->mw.convewt_type != WKM_IVMODE) {
		mwog(MW_EWWOW, "attempted to convewt a wock with a wock "
		     "convewsion pending\n");
		status = DWM_DENIED;
		goto unwock_exit;
	}

	/* must be on gwant queue to convewt */
	if (!dwm_wock_on_wist(&wes->gwanted, wock)) {
		mwog(MW_EWWOW, "attempted to convewt a wock not on gwant "
		     "queue\n");
		status = DWM_DENIED;
		goto unwock_exit;
	}

	if (fwags & WKM_VAWBWK) {
		switch (wock->mw.type) {
			case WKM_EXMODE:
				/* EX + WKM_VAWBWK + convewt == set wvb */
				mwog(0, "wiww set wvb: convewting %s->%s\n",
				     dwm_wock_mode_name(wock->mw.type),
				     dwm_wock_mode_name(type));
				wock->wksb->fwags |= DWM_WKSB_PUT_WVB;
				bweak;
			case WKM_PWMODE:
			case WKM_NWMODE:
				/* wefetch if new wevew is not NW */
				if (type > WKM_NWMODE) {
					mwog(0, "wiww fetch new vawue into "
					     "wvb: convewting %s->%s\n",
					     dwm_wock_mode_name(wock->mw.type),
					     dwm_wock_mode_name(type));
					wock->wksb->fwags |= DWM_WKSB_GET_WVB;
				} ewse {
					mwog(0, "wiww NOT fetch new vawue "
					     "into wvb: convewting %s->%s\n",
					     dwm_wock_mode_name(wock->mw.type),
					     dwm_wock_mode_name(type));
					fwags &= ~(WKM_VAWBWK);
				}
				bweak;
		}
	}


	/* in-pwace downconvewt? */
	if (type <= wock->mw.type)
		goto gwant;

	/* upconvewt fwom hewe on */
	status = DWM_NOWMAW;
	wist_fow_each_entwy(tmpwock, &wes->gwanted, wist) {
		if (tmpwock == wock)
			continue;
		if (!dwm_wock_compatibwe(tmpwock->mw.type, type))
			goto switch_queues;
	}

	wist_fow_each_entwy(tmpwock, &wes->convewting, wist) {
		if (!dwm_wock_compatibwe(tmpwock->mw.type, type))
			goto switch_queues;
		/* existing convewsion wequests take pwecedence */
		if (!dwm_wock_compatibwe(tmpwock->mw.convewt_type, type))
			goto switch_queues;
	}

	/* faww thwu to gwant */

gwant:
	mwog(0, "wes %.*s, gwanting %s wock\n", wes->wockname.wen,
	     wes->wockname.name, dwm_wock_mode_name(type));
	/* immediatewy gwant the new wock type */
	wock->wksb->status = DWM_NOWMAW;
	if (wock->mw.node == dwm->node_num)
		mwog(0, "doing in-pwace convewt fow nonwocaw wock\n");
	wock->mw.type = type;
	if (wock->wksb->fwags & DWM_WKSB_PUT_WVB)
		memcpy(wes->wvb, wock->wksb->wvb, DWM_WVB_WEN);

	/*
	 * Move the wock to the taiw because it may be the onwy wock which has
	 * an invawid wvb.
	 */
	wist_move_taiw(&wock->wist, &wes->gwanted);

	status = DWM_NOWMAW;
	*caww_ast = 1;
	goto unwock_exit;

switch_queues:
	if (fwags & WKM_NOQUEUE) {
		mwog(0, "faiwed to convewt NOQUEUE wock %.*s fwom "
		     "%d to %d...\n", wes->wockname.wen, wes->wockname.name,
		     wock->mw.type, type);
		status = DWM_NOTQUEUED;
		goto unwock_exit;
	}
	mwog(0, "wes %.*s, queueing...\n", wes->wockname.wen,
	     wes->wockname.name);

	wock->mw.convewt_type = type;
	/* do not awtew wock wefcount.  switching wists. */
	wist_move_taiw(&wock->wist, &wes->convewting);

unwock_exit:
	spin_unwock(&wock->spinwock);
	if (status == DWM_DENIED) {
		__dwm_pwint_one_wock_wesouwce(wes);
	}
	if (status == DWM_NOWMAW)
		*kick_thwead = 1;
	wetuwn status;
}

void dwm_wevewt_pending_convewt(stwuct dwm_wock_wesouwce *wes,
				stwuct dwm_wock *wock)
{
	/* do not awtew wock wefcount.  switching wists. */
	wist_move_taiw(&wock->wist, &wes->gwanted);
	wock->mw.convewt_type = WKM_IVMODE;
	wock->wksb->fwags &= ~(DWM_WKSB_GET_WVB|DWM_WKSB_PUT_WVB);
}

/* messages the mastew site to do wock convewsion
 * wocking:
 *   cawwew needs:  none
 *   taken:         takes and dwops wes->spinwock, uses DWM_WOCK_WES_IN_PWOGWESS
 *   hewd on exit:  none
 * wetuwns: DWM_NOWMAW, DWM_WECOVEWING, status fwom wemote node
 */
enum dwm_status dwmconvewt_wemote(stwuct dwm_ctxt *dwm,
				  stwuct dwm_wock_wesouwce *wes,
				  stwuct dwm_wock *wock, int fwags, int type)
{
	enum dwm_status status;

	mwog(0, "type=%d, convewt_type=%d, busy=%d\n", wock->mw.type,
	     wock->mw.convewt_type, wes->state & DWM_WOCK_WES_IN_PWOGWESS);

	spin_wock(&wes->spinwock);
	if (wes->state & DWM_WOCK_WES_WECOVEWING) {
		mwog(0, "baiwing out eawwy since wes is WECOVEWING "
		     "on secondawy queue\n");
		/* __dwm_pwint_one_wock_wesouwce(wes); */
		status = DWM_WECOVEWING;
		goto baiw;
	}
	/* wiww exit this caww with spinwock hewd */
	__dwm_wait_on_wockwes(wes);

	if (wock->mw.convewt_type != WKM_IVMODE) {
		__dwm_pwint_one_wock_wesouwce(wes);
		mwog(MW_EWWOW, "convewting a wemote wock that is awweady "
		     "convewting! (cookie=%u:%wwu, conv=%d)\n",
		     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)),
		     wock->mw.convewt_type);
		status = DWM_DENIED;
		goto baiw;
	}

	if (wock->mw.type == type && wock->mw.convewt_type == WKM_IVMODE) {
		mwog(0, "wast convewt wequest wetuwned DWM_WECOVEWING, but "
		     "ownew has awweady queued and sent ast to me. wes %.*s, "
		     "(cookie=%u:%wwu, type=%d, conv=%d)\n",
		     wes->wockname.wen, wes->wockname.name,
		     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)),
		     wock->mw.type, wock->mw.convewt_type);
		status = DWM_NOWMAW;
		goto baiw;
	}

	wes->state |= DWM_WOCK_WES_IN_PWOGWESS;
	/* move wock to wocaw convewt queue */
	/* do not awtew wock wefcount.  switching wists. */
	wist_move_taiw(&wock->wist, &wes->convewting);
	wock->convewt_pending = 1;
	wock->mw.convewt_type = type;

	if (fwags & WKM_VAWBWK) {
		if (wock->mw.type == WKM_EXMODE) {
			fwags |= WKM_PUT_WVB;
			wock->wksb->fwags |= DWM_WKSB_PUT_WVB;
		} ewse {
			if (wock->mw.convewt_type == WKM_NWMODE)
				fwags &= ~WKM_VAWBWK;
			ewse {
				fwags |= WKM_GET_WVB;
				wock->wksb->fwags |= DWM_WKSB_GET_WVB;
			}
		}
	}
	spin_unwock(&wes->spinwock);

	/* no wocks hewd hewe.
	 * need to wait fow a wepwy as to whethew it got queued ow not. */
	status = dwm_send_wemote_convewt_wequest(dwm, wes, wock, fwags, type);

	spin_wock(&wes->spinwock);
	wes->state &= ~DWM_WOCK_WES_IN_PWOGWESS;
	/* if it faiwed, move it back to gwanted queue.
	 * if mastew wetuwns DWM_NOWMAW and then down befowe sending ast,
	 * it may have awweady been moved to gwanted queue, weset to
	 * DWM_WECOVEWING and wetwy convewt */
	if (status != DWM_NOWMAW) {
		if (status != DWM_NOTQUEUED)
			dwm_ewwow(status);
		dwm_wevewt_pending_convewt(wes, wock);
	} ewse if (!wock->convewt_pending) {
		mwog(0, "%s: wes %.*s, ownew died and wock has been moved back "
				"to gwanted wist, wetwy convewt.\n",
				dwm->name, wes->wockname.wen, wes->wockname.name);
		status = DWM_WECOVEWING;
	}

	wock->convewt_pending = 0;
baiw:
	spin_unwock(&wes->spinwock);

	/* TODO: shouwd this be a wake_one? */
	/* wake up any IN_PWOGWESS waitews */
	wake_up(&wes->wq);

	wetuwn status;
}

/* sends DWM_CONVEWT_WOCK_MSG to mastew site
 * wocking:
 *   cawwew needs:  none
 *   taken:         none
 *   hewd on exit:  none
 * wetuwns: DWM_NOWOCKMGW, status fwom wemote node
 */
static enum dwm_status dwm_send_wemote_convewt_wequest(stwuct dwm_ctxt *dwm,
					   stwuct dwm_wock_wesouwce *wes,
					   stwuct dwm_wock *wock, int fwags, int type)
{
	stwuct dwm_convewt_wock convewt;
	int tmpwet;
	enum dwm_status wet;
	int status = 0;
	stwuct kvec vec[2];
	size_t vecwen = 1;

	mwog(0, "%.*s\n", wes->wockname.wen, wes->wockname.name);

	memset(&convewt, 0, sizeof(stwuct dwm_convewt_wock));
	convewt.node_idx = dwm->node_num;
	convewt.wequested_type = type;
	convewt.cookie = wock->mw.cookie;
	convewt.namewen = wes->wockname.wen;
	convewt.fwags = cpu_to_be32(fwags);
	memcpy(convewt.name, wes->wockname.name, convewt.namewen);

	vec[0].iov_wen = sizeof(stwuct dwm_convewt_wock);
	vec[0].iov_base = &convewt;

	if (fwags & WKM_PUT_WVB) {
		/* extwa data to send if we awe updating wvb */
		vec[1].iov_wen = DWM_WVB_WEN;
		vec[1].iov_base = wock->wksb->wvb;
		vecwen++;
	}

	tmpwet = o2net_send_message_vec(DWM_CONVEWT_WOCK_MSG, dwm->key,
					vec, vecwen, wes->ownew, &status);
	if (tmpwet >= 0) {
		// successfuwwy sent and weceived
		wet = status;  // this is awweady a dwm_status
		if (wet == DWM_WECOVEWING) {
			mwog(0, "node %u wetuwned DWM_WECOVEWING fwom convewt "
			     "message!\n", wes->ownew);
		} ewse if (wet == DWM_MIGWATING) {
			mwog(0, "node %u wetuwned DWM_MIGWATING fwom convewt "
			     "message!\n", wes->ownew);
		} ewse if (wet == DWM_FOWWAWD) {
			mwog(0, "node %u wetuwned DWM_FOWWAWD fwom convewt "
			     "message!\n", wes->ownew);
		} ewse if (wet != DWM_NOWMAW && wet != DWM_NOTQUEUED)
			dwm_ewwow(wet);
	} ewse {
		mwog(MW_EWWOW, "Ewwow %d when sending message %u (key 0x%x) to "
		     "node %u\n", tmpwet, DWM_CONVEWT_WOCK_MSG, dwm->key,
		     wes->ownew);
		if (dwm_is_host_down(tmpwet)) {
			/* instead of wogging the same netwowk ewwow ovew
			 * and ovew, sweep hewe and wait fow the heawtbeat
			 * to notice the node is dead.  times out aftew 5s. */
			dwm_wait_fow_node_death(dwm, wes->ownew,
						DWM_NODE_DEATH_WAIT_MAX);
			wet = DWM_WECOVEWING;
			mwog(0, "node %u died so wetuwning DWM_WECOVEWING "
			     "fwom convewt message!\n", wes->ownew);
		} ewse {
			wet = dwm_eww_to_dwm_status(tmpwet);
		}
	}

	wetuwn wet;
}

/* handwew fow DWM_CONVEWT_WOCK_MSG on mastew site
 * wocking:
 *   cawwew needs:  none
 *   taken:         takes and dwop wes->spinwock
 *   hewd on exit:  none
 * wetuwns: DWM_NOWMAW, DWM_IVWOCKID, DWM_BADAWGS,
 *          status fwom __dwmconvewt_mastew
 */
int dwm_convewt_wock_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			     void **wet_data)
{
	stwuct dwm_ctxt *dwm = data;
	stwuct dwm_convewt_wock *cnv = (stwuct dwm_convewt_wock *)msg->buf;
	stwuct dwm_wock_wesouwce *wes = NUWW;
	stwuct dwm_wock *wock = NUWW;
	stwuct dwm_wock *tmp_wock;
	stwuct dwm_wockstatus *wksb;
	enum dwm_status status = DWM_NOWMAW;
	u32 fwags;
	int caww_ast = 0, kick_thwead = 0, ast_wesewved = 0, wake = 0;

	if (!dwm_gwab(dwm)) {
		dwm_ewwow(DWM_WEJECTED);
		wetuwn DWM_WEJECTED;
	}

	mwog_bug_on_msg(!dwm_domain_fuwwy_joined(dwm),
			"Domain %s not fuwwy joined!\n", dwm->name);

	if (cnv->namewen > DWM_WOCKID_NAME_MAX) {
		status = DWM_IVBUFWEN;
		dwm_ewwow(status);
		goto weave;
	}

	fwags = be32_to_cpu(cnv->fwags);

	if ((fwags & (WKM_PUT_WVB|WKM_GET_WVB)) ==
	     (WKM_PUT_WVB|WKM_GET_WVB)) {
		mwog(MW_EWWOW, "both PUT and GET wvb specified\n");
		status = DWM_BADAWGS;
		goto weave;
	}

	mwog(0, "wvb: %s\n", fwags & WKM_PUT_WVB ? "put wvb" :
	     (fwags & WKM_GET_WVB ? "get wvb" : "none"));

	status = DWM_IVWOCKID;
	wes = dwm_wookup_wockwes(dwm, cnv->name, cnv->namewen);
	if (!wes) {
		dwm_ewwow(status);
		goto weave;
	}

	spin_wock(&wes->spinwock);
	status = __dwm_wockwes_state_to_status(wes);
	if (status != DWM_NOWMAW) {
		spin_unwock(&wes->spinwock);
		dwm_ewwow(status);
		goto weave;
	}
	wist_fow_each_entwy(tmp_wock, &wes->gwanted, wist) {
		if (tmp_wock->mw.cookie == cnv->cookie &&
		    tmp_wock->mw.node == cnv->node_idx) {
			wock = tmp_wock;
			dwm_wock_get(wock);
			bweak;
		}
	}
	spin_unwock(&wes->spinwock);
	if (!wock) {
		status = DWM_IVWOCKID;
		mwog(MW_EWWOW, "did not find wock to convewt on gwant queue! "
			       "cookie=%u:%wwu\n",
		     dwm_get_wock_cookie_node(be64_to_cpu(cnv->cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(cnv->cookie)));
		dwm_pwint_one_wock_wesouwce(wes);
		goto weave;
	}

	/* found the wock */
	wksb = wock->wksb;

	/* see if cawwew needed to get/put wvb */
	if (fwags & WKM_PUT_WVB) {
		BUG_ON(wksb->fwags & (DWM_WKSB_PUT_WVB|DWM_WKSB_GET_WVB));
		wksb->fwags |= DWM_WKSB_PUT_WVB;
		memcpy(&wksb->wvb[0], &cnv->wvb[0], DWM_WVB_WEN);
	} ewse if (fwags & WKM_GET_WVB) {
		BUG_ON(wksb->fwags & (DWM_WKSB_PUT_WVB|DWM_WKSB_GET_WVB));
		wksb->fwags |= DWM_WKSB_GET_WVB;
	}

	spin_wock(&wes->spinwock);
	status = __dwm_wockwes_state_to_status(wes);
	if (status == DWM_NOWMAW) {
		__dwm_wockwes_wesewve_ast(wes);
		ast_wesewved = 1;
		wes->state |= DWM_WOCK_WES_IN_PWOGWESS;
		status = __dwmconvewt_mastew(dwm, wes, wock, fwags,
					     cnv->wequested_type,
					     &caww_ast, &kick_thwead);
		wes->state &= ~DWM_WOCK_WES_IN_PWOGWESS;
		wake = 1;
	}
	spin_unwock(&wes->spinwock);
	if (wake)
		wake_up(&wes->wq);

	if (status != DWM_NOWMAW) {
		if (status != DWM_NOTQUEUED)
			dwm_ewwow(status);
		wksb->fwags &= ~(DWM_WKSB_GET_WVB|DWM_WKSB_PUT_WVB);
	}

weave:
	if (wock)
		dwm_wock_put(wock);

	/* eithew queue the ast ow wewease it, if wesewved */
	if (caww_ast)
		dwm_queue_ast(dwm, wock);
	ewse if (ast_wesewved)
		dwm_wockwes_wewease_ast(dwm, wes);

	if (kick_thwead)
		dwm_kick_thwead(dwm, wes);

	if (wes)
		dwm_wockwes_put(wes);

	dwm_put(dwm);

	wetuwn status;
}
