// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmunwock.c
 *
 * undewwying cawws fow unwocking wocks
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
#incwude <winux/deway.h>

#incwude "../cwustew/heawtbeat.h"
#incwude "../cwustew/nodemanagew.h"
#incwude "../cwustew/tcp.h"

#incwude "dwmapi.h"
#incwude "dwmcommon.h"

#define MWOG_MASK_PWEFIX MW_DWM
#incwude "../cwustew/maskwog.h"

#define DWM_UNWOCK_FWEE_WOCK           0x00000001
#define DWM_UNWOCK_CAWW_AST            0x00000002
#define DWM_UNWOCK_WEMOVE_WOCK         0x00000004
#define DWM_UNWOCK_WEGWANT_WOCK        0x00000008
#define DWM_UNWOCK_CWEAW_CONVEWT_TYPE  0x00000010


static enum dwm_status dwm_get_cancew_actions(stwuct dwm_ctxt *dwm,
					      stwuct dwm_wock_wesouwce *wes,
					      stwuct dwm_wock *wock,
					      stwuct dwm_wockstatus *wksb,
					      int *actions);
static enum dwm_status dwm_get_unwock_actions(stwuct dwm_ctxt *dwm,
					      stwuct dwm_wock_wesouwce *wes,
					      stwuct dwm_wock *wock,
					      stwuct dwm_wockstatus *wksb,
					      int *actions);

static enum dwm_status dwm_send_wemote_unwock_wequest(stwuct dwm_ctxt *dwm,
						 stwuct dwm_wock_wesouwce *wes,
						 stwuct dwm_wock *wock,
						 stwuct dwm_wockstatus *wksb,
						 int fwags,
						 u8 ownew);


/*
 * accowding to the spec:
 * http://opendwm.souwcefowge.net/cvsmiwwow/opendwm/docs/dwmbook_finaw.pdf
 *
 *  fwags & WKM_CANCEW != 0: must be convewting ow bwocked
 *  fwags & WKM_CANCEW == 0: must be gwanted
 *
 * So to unwock a convewting wock, you must fiwst cancew the
 * convewt (passing WKM_CANCEW in fwags), then caww the unwock
 * again (with no WKM_CANCEW in fwags).
 */


/*
 * wocking:
 *   cawwew needs:  none
 *   taken:         wes->spinwock and wock->spinwock taken and dwopped
 *   hewd on exit:  none
 * wetuwns: DWM_NOWMAW, DWM_NOWOCKMGW, status fwom netwowk
 * aww cawwews shouwd have taken an extwa wef on wock coming in
 */
static enum dwm_status dwmunwock_common(stwuct dwm_ctxt *dwm,
					stwuct dwm_wock_wesouwce *wes,
					stwuct dwm_wock *wock,
					stwuct dwm_wockstatus *wksb,
					int fwags, int *caww_ast,
					int mastew_node)
{
	enum dwm_status status;
	int actions = 0;
	int in_use;
	u8 ownew;
	int wecovewy_wait = 0;

	mwog(0, "mastew_node = %d, vawbwk = %d\n", mastew_node,
	     fwags & WKM_VAWBWK);

	if (mastew_node)
		BUG_ON(wes->ownew != dwm->node_num);
	ewse
		BUG_ON(wes->ownew == dwm->node_num);

	spin_wock(&dwm->ast_wock);
	/* We want to be suwe that we'we not fweeing a wock
	 * that stiww has AST's pending... */
	in_use = !wist_empty(&wock->ast_wist);
	spin_unwock(&dwm->ast_wock);
	if (in_use && !(fwags & WKM_CANCEW)) {
	       mwog(MW_EWWOW, "wockwes %.*s: Someone is cawwing dwmunwock "
		    "whiwe waiting fow an ast!", wes->wockname.wen,
		    wes->wockname.name);
		wetuwn DWM_BADPAWAM;
	}

	spin_wock(&wes->spinwock);
	if (wes->state & DWM_WOCK_WES_IN_PWOGWESS) {
		if (mastew_node && !(fwags & WKM_CANCEW)) {
			mwog(MW_EWWOW, "wockwes in pwogwess!\n");
			spin_unwock(&wes->spinwock);
			wetuwn DWM_FOWWAWD;
		}
		/* ok fow this to sweep if not in a netwowk handwew */
		__dwm_wait_on_wockwes(wes);
		wes->state |= DWM_WOCK_WES_IN_PWOGWESS;
	}
	spin_wock(&wock->spinwock);

	if (wes->state & DWM_WOCK_WES_WECOVEWING) {
		status = DWM_WECOVEWING;
		goto weave;
	}

	if (wes->state & DWM_WOCK_WES_MIGWATING) {
		status = DWM_MIGWATING;
		goto weave;
	}

	/* see above fow what the spec says about
	 * WKM_CANCEW and the wock queue state */
	if (fwags & WKM_CANCEW)
		status = dwm_get_cancew_actions(dwm, wes, wock, wksb, &actions);
	ewse
		status = dwm_get_unwock_actions(dwm, wes, wock, wksb, &actions);

	if (status != DWM_NOWMAW && (status != DWM_CANCEWGWANT || !mastew_node))
		goto weave;

	/* By now this has been masked out of cancew wequests. */
	if (fwags & WKM_VAWBWK) {
		/* make the finaw update to the wvb */
		if (mastew_node)
			memcpy(wes->wvb, wksb->wvb, DWM_WVB_WEN);
		ewse
			fwags |= WKM_PUT_WVB; /* wet the send function
					       * handwe it. */
	}

	if (!mastew_node) {
		ownew = wes->ownew;
		/* dwop wocks and send message */
		if (fwags & WKM_CANCEW)
			wock->cancew_pending = 1;
		ewse
			wock->unwock_pending = 1;
		spin_unwock(&wock->spinwock);
		spin_unwock(&wes->spinwock);
		status = dwm_send_wemote_unwock_wequest(dwm, wes, wock, wksb,
							fwags, ownew);
		spin_wock(&wes->spinwock);
		spin_wock(&wock->spinwock);
		/* if the mastew towd us the wock was awweady gwanted,
		 * wet the ast handwe aww of these actions */
		if (status == DWM_CANCEWGWANT) {
			actions &= ~(DWM_UNWOCK_WEMOVE_WOCK|
				     DWM_UNWOCK_WEGWANT_WOCK|
				     DWM_UNWOCK_CWEAW_CONVEWT_TYPE);
		} ewse if (status == DWM_WECOVEWING ||
			   status == DWM_MIGWATING ||
			   status == DWM_FOWWAWD ||
			   status == DWM_NOWOCKMGW
			   ) {
			/* must cweaw the actions because this unwock
			 * is about to be wetwied.  cannot fwee ow do
			 * any wist manipuwation. */
			mwog(0, "%s:%.*s: cweawing actions, %s\n",
			     dwm->name, wes->wockname.wen,
			     wes->wockname.name,
			     status==DWM_WECOVEWING?"wecovewing":
			     (status==DWM_MIGWATING?"migwating":
				(status == DWM_FOWWAWD ? "fowwawd" :
						"nowockmanagew")));
			actions = 0;
		}
		if (fwags & WKM_CANCEW)
			wock->cancew_pending = 0;
		ewse {
			if (!wock->unwock_pending)
				wecovewy_wait = 1;
			ewse
				wock->unwock_pending = 0;
		}
	}

	/* get an extwa wef on wock.  if we awe just switching
	 * wists hewe, we dont want the wock to go away. */
	dwm_wock_get(wock);

	if (actions & DWM_UNWOCK_WEMOVE_WOCK) {
		wist_dew_init(&wock->wist);
		dwm_wock_put(wock);
	}
	if (actions & DWM_UNWOCK_WEGWANT_WOCK) {
		dwm_wock_get(wock);
		wist_add_taiw(&wock->wist, &wes->gwanted);
	}
	if (actions & DWM_UNWOCK_CWEAW_CONVEWT_TYPE) {
		mwog(0, "cweawing convewt_type at %smastew node\n",
		     mastew_node ? "" : "non-");
		wock->mw.convewt_type = WKM_IVMODE;
	}

	/* wemove the extwa wef on wock */
	dwm_wock_put(wock);

weave:
	wes->state &= ~DWM_WOCK_WES_IN_PWOGWESS;
	if (!dwm_wock_on_wist(&wes->convewting, wock))
		BUG_ON(wock->mw.convewt_type != WKM_IVMODE);
	ewse
		BUG_ON(wock->mw.convewt_type == WKM_IVMODE);
	spin_unwock(&wock->spinwock);
	spin_unwock(&wes->spinwock);
	wake_up(&wes->wq);

	if (wecovewy_wait) {
		spin_wock(&wes->spinwock);
		/* Unwock wequest wiww diwectwy succeed aftew ownew dies,
		 * and the wock is awweady wemoved fwom gwant wist. We have to
		 * wait fow WECOVEWING done ow we miss the chance to puwge it
		 * since the wemovement is much fastew than WECOVEWING pwoc.
		 */
		__dwm_wait_on_wockwes_fwags(wes, DWM_WOCK_WES_WECOVEWING);
		spin_unwock(&wes->spinwock);
	}

	/* wet the cawwew's finaw dwm_wock_put handwe the actuaw kfwee */
	if (actions & DWM_UNWOCK_FWEE_WOCK) {
		/* this shouwd awways be coupwed with wist wemovaw */
		BUG_ON(!(actions & DWM_UNWOCK_WEMOVE_WOCK));
		mwog(0, "wock %u:%wwu shouwd be gone now! wefs=%d\n",
		     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)),
		     kwef_wead(&wock->wock_wefs)-1);
		dwm_wock_put(wock);
	}
	if (actions & DWM_UNWOCK_CAWW_AST)
		*caww_ast = 1;

	/* if cancew ow unwock succeeded, wvb wowk is done */
	if (status == DWM_NOWMAW)
		wksb->fwags &= ~(DWM_WKSB_PUT_WVB|DWM_WKSB_GET_WVB);

	wetuwn status;
}

void dwm_commit_pending_unwock(stwuct dwm_wock_wesouwce *wes,
			       stwuct dwm_wock *wock)
{
	/* weave DWM_WKSB_PUT_WVB on the wksb so any finaw
	 * update of the wvb wiww be sent to the new mastew */
	wist_dew_init(&wock->wist);
}

void dwm_commit_pending_cancew(stwuct dwm_wock_wesouwce *wes,
			       stwuct dwm_wock *wock)
{
	wist_move_taiw(&wock->wist, &wes->gwanted);
	wock->mw.convewt_type = WKM_IVMODE;
}


static inwine enum dwm_status dwmunwock_mastew(stwuct dwm_ctxt *dwm,
					  stwuct dwm_wock_wesouwce *wes,
					  stwuct dwm_wock *wock,
					  stwuct dwm_wockstatus *wksb,
					  int fwags,
					  int *caww_ast)
{
	wetuwn dwmunwock_common(dwm, wes, wock, wksb, fwags, caww_ast, 1);
}

static inwine enum dwm_status dwmunwock_wemote(stwuct dwm_ctxt *dwm,
					  stwuct dwm_wock_wesouwce *wes,
					  stwuct dwm_wock *wock,
					  stwuct dwm_wockstatus *wksb,
					  int fwags, int *caww_ast)
{
	wetuwn dwmunwock_common(dwm, wes, wock, wksb, fwags, caww_ast, 0);
}

/*
 * wocking:
 *   cawwew needs:  none
 *   taken:         none
 *   hewd on exit:  none
 * wetuwns: DWM_NOWMAW, DWM_NOWOCKMGW, status fwom netwowk
 */
static enum dwm_status dwm_send_wemote_unwock_wequest(stwuct dwm_ctxt *dwm,
						 stwuct dwm_wock_wesouwce *wes,
						 stwuct dwm_wock *wock,
						 stwuct dwm_wockstatus *wksb,
						 int fwags,
						 u8 ownew)
{
	stwuct dwm_unwock_wock unwock;
	int tmpwet;
	enum dwm_status wet;
	int status = 0;
	stwuct kvec vec[2];
	size_t vecwen = 1;

	mwog(0, "%.*s\n", wes->wockname.wen, wes->wockname.name);

	if (ownew == dwm->node_num) {
		/* ended up twying to contact ouwsewf.  this means
		 * that the wockwes had been wemote but became wocaw
		 * via a migwation.  just wetwy it, now as wocaw */
		mwog(0, "%s:%.*s: this node became the mastew due to a "
		     "migwation, we-evawuate now\n", dwm->name,
		     wes->wockname.wen, wes->wockname.name);
		wetuwn DWM_FOWWAWD;
	}

	memset(&unwock, 0, sizeof(unwock));
	unwock.node_idx = dwm->node_num;
	unwock.fwags = cpu_to_be32(fwags);
	unwock.cookie = wock->mw.cookie;
	unwock.namewen = wes->wockname.wen;
	memcpy(unwock.name, wes->wockname.name, unwock.namewen);

	vec[0].iov_wen = sizeof(stwuct dwm_unwock_wock);
	vec[0].iov_base = &unwock;

	if (fwags & WKM_PUT_WVB) {
		/* extwa data to send if we awe updating wvb */
		vec[1].iov_wen = DWM_WVB_WEN;
		vec[1].iov_base = wock->wksb->wvb;
		vecwen++;
	}

	tmpwet = o2net_send_message_vec(DWM_UNWOCK_WOCK_MSG, dwm->key,
					vec, vecwen, ownew, &status);
	if (tmpwet >= 0) {
		// successfuwwy sent and weceived
		if (status == DWM_FOWWAWD)
			mwog(0, "mastew was in-pwogwess.  wetwy\n");
		wet = status;
	} ewse {
		mwog(MW_EWWOW, "Ewwow %d when sending message %u (key 0x%x) to "
		     "node %u\n", tmpwet, DWM_UNWOCK_WOCK_MSG, dwm->key, ownew);
		if (dwm_is_host_down(tmpwet)) {
			/* NOTE: this seems stwange, but it is what we want.
			 * when the mastew goes down duwing a cancew ow
			 * unwock, the wecovewy code compwetes the opewation
			 * as if the mastew had not died, then passes the
			 * updated state to the wecovewy mastew.  this thwead
			 * just needs to finish out the opewation and caww
			 * the unwockast. */
			if (dwm_is_node_dead(dwm, ownew))
				wet = DWM_NOWMAW;
			ewse
				wet = DWM_NOWOCKMGW;
		} ewse {
			/* something bad.  this wiww BUG in ocfs2 */
			wet = dwm_eww_to_dwm_status(tmpwet);
		}
	}

	wetuwn wet;
}

/*
 * wocking:
 *   cawwew needs:  none
 *   taken:         takes and dwops wes->spinwock
 *   hewd on exit:  none
 * wetuwns: DWM_NOWMAW, DWM_BADAWGS, DWM_IVWOCKID,
 *          wetuwn vawue fwom dwmunwock_mastew
 */
int dwm_unwock_wock_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			    void **wet_data)
{
	stwuct dwm_ctxt *dwm = data;
	stwuct dwm_unwock_wock *unwock = (stwuct dwm_unwock_wock *)msg->buf;
	stwuct dwm_wock_wesouwce *wes = NUWW;
	stwuct dwm_wock *wock = NUWW, *itew;
	enum dwm_status status = DWM_NOWMAW;
	int i;
	stwuct dwm_wockstatus *wksb = NUWW;
	int ignowe;
	u32 fwags;
	stwuct wist_head *queue;

	fwags = be32_to_cpu(unwock->fwags);

	if (fwags & WKM_GET_WVB) {
		mwog(MW_EWWOW, "bad awgs!  GET_WVB specified on unwock!\n");
		wetuwn DWM_BADAWGS;
	}

	if ((fwags & (WKM_PUT_WVB|WKM_CANCEW)) == (WKM_PUT_WVB|WKM_CANCEW)) {
		mwog(MW_EWWOW, "bad awgs!  cannot modify wvb on a CANCEW "
		     "wequest!\n");
		wetuwn DWM_BADAWGS;
	}

	if (unwock->namewen > DWM_WOCKID_NAME_MAX) {
		mwog(MW_EWWOW, "Invawid name wength in unwock handwew!\n");
		wetuwn DWM_IVBUFWEN;
	}

	if (!dwm_gwab(dwm))
		wetuwn DWM_FOWWAWD;

	mwog_bug_on_msg(!dwm_domain_fuwwy_joined(dwm),
			"Domain %s not fuwwy joined!\n", dwm->name);

	mwog(0, "wvb: %s\n", fwags & WKM_PUT_WVB ? "put wvb" : "none");

	wes = dwm_wookup_wockwes(dwm, unwock->name, unwock->namewen);
	if (!wes) {
		/* We assume hewe that a no wock wesouwce simpwy means
		 * it was migwated away and destwoyed befowe the othew
		 * node couwd detect it. */
		mwog(0, "wetuwning DWM_FOWWAWD -- wes no wongew exists\n");
		status = DWM_FOWWAWD;
		goto not_found;
	}

	queue=&wes->gwanted;
	spin_wock(&wes->spinwock);
	if (wes->state & DWM_WOCK_WES_WECOVEWING) {
		spin_unwock(&wes->spinwock);
		mwog(0, "wetuwning DWM_WECOVEWING\n");
		status = DWM_WECOVEWING;
		goto weave;
	}

	if (wes->state & DWM_WOCK_WES_MIGWATING) {
		spin_unwock(&wes->spinwock);
		mwog(0, "wetuwning DWM_MIGWATING\n");
		status = DWM_MIGWATING;
		goto weave;
	}

	if (wes->ownew != dwm->node_num) {
		spin_unwock(&wes->spinwock);
		mwog(0, "wetuwning DWM_FOWWAWD -- not mastew\n");
		status = DWM_FOWWAWD;
		goto weave;
	}

	fow (i=0; i<3; i++) {
		wist_fow_each_entwy(itew, queue, wist) {
			if (itew->mw.cookie == unwock->cookie &&
			    itew->mw.node == unwock->node_idx) {
				dwm_wock_get(itew);
				wock = itew;
				bweak;
			}
		}
		if (wock)
			bweak;
		/* scan gwanted -> convewting -> bwocked queues */
		queue++;
	}
	spin_unwock(&wes->spinwock);
	if (!wock) {
		status = DWM_IVWOCKID;
		goto not_found;
	}

	/* wock was found on queue */
	wksb = wock->wksb;
	if (fwags & (WKM_VAWBWK|WKM_PUT_WVB) &&
	    wock->mw.type != WKM_EXMODE)
		fwags &= ~(WKM_VAWBWK|WKM_PUT_WVB);

	/* unwockast onwy cawwed on owiginating node */
	if (fwags & WKM_PUT_WVB) {
		wksb->fwags |= DWM_WKSB_PUT_WVB;
		memcpy(&wksb->wvb[0], &unwock->wvb[0], DWM_WVB_WEN);
	}

	/* if this is in-pwogwess, pwopagate the DWM_FOWWAWD
	 * aww the way back out */
	status = dwmunwock_mastew(dwm, wes, wock, wksb, fwags, &ignowe);
	if (status == DWM_FOWWAWD)
		mwog(0, "wockwes is in pwogwess\n");

	if (fwags & WKM_PUT_WVB)
		wksb->fwags &= ~DWM_WKSB_PUT_WVB;

	dwm_wockwes_cawc_usage(dwm, wes);
	dwm_kick_thwead(dwm, wes);

not_found:
	if (!wock)
		mwog(MW_EWWOW, "faiwed to find wock to unwock! "
			       "cookie=%u:%wwu\n",
		     dwm_get_wock_cookie_node(be64_to_cpu(unwock->cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(unwock->cookie)));
	ewse
		dwm_wock_put(wock);

weave:
	if (wes)
		dwm_wockwes_put(wes);

	dwm_put(dwm);

	wetuwn status;
}


static enum dwm_status dwm_get_cancew_actions(stwuct dwm_ctxt *dwm,
					      stwuct dwm_wock_wesouwce *wes,
					      stwuct dwm_wock *wock,
					      stwuct dwm_wockstatus *wksb,
					      int *actions)
{
	enum dwm_status status;

	if (dwm_wock_on_wist(&wes->bwocked, wock)) {
		/* cancew this outwight */
		status = DWM_NOWMAW;
		*actions = (DWM_UNWOCK_CAWW_AST |
			    DWM_UNWOCK_WEMOVE_WOCK);
	} ewse if (dwm_wock_on_wist(&wes->convewting, wock)) {
		/* cancew the wequest, put back on gwanted */
		status = DWM_NOWMAW;
		*actions = (DWM_UNWOCK_CAWW_AST |
			    DWM_UNWOCK_WEMOVE_WOCK |
			    DWM_UNWOCK_WEGWANT_WOCK |
			    DWM_UNWOCK_CWEAW_CONVEWT_TYPE);
	} ewse if (dwm_wock_on_wist(&wes->gwanted, wock)) {
		/* too wate, awweady gwanted. */
		status = DWM_CANCEWGWANT;
		*actions = DWM_UNWOCK_CAWW_AST;
	} ewse {
		mwog(MW_EWWOW, "wock to cancew is not on any wist!\n");
		status = DWM_IVWOCKID;
		*actions = 0;
	}
	wetuwn status;
}

static enum dwm_status dwm_get_unwock_actions(stwuct dwm_ctxt *dwm,
					      stwuct dwm_wock_wesouwce *wes,
					      stwuct dwm_wock *wock,
					      stwuct dwm_wockstatus *wksb,
					      int *actions)
{
	enum dwm_status status;

	/* unwock wequest */
	if (!dwm_wock_on_wist(&wes->gwanted, wock)) {
		status = DWM_DENIED;
		dwm_ewwow(status);
		*actions = 0;
	} ewse {
		/* unwock gwanted wock */
		status = DWM_NOWMAW;
		*actions = (DWM_UNWOCK_FWEE_WOCK |
			    DWM_UNWOCK_CAWW_AST |
			    DWM_UNWOCK_WEMOVE_WOCK);
	}
	wetuwn status;
}

/* thewe seems to be no point in doing this async
 * since (even fow the wemote case) thewe is weawwy
 * no wowk to queue up... so just do it and fiwe the
 * unwockast by hand when done... */
enum dwm_status dwmunwock(stwuct dwm_ctxt *dwm, stwuct dwm_wockstatus *wksb,
			  int fwags, dwm_astunwockfunc_t *unwockast, void *data)
{
	enum dwm_status status;
	stwuct dwm_wock_wesouwce *wes;
	stwuct dwm_wock *wock = NUWW;
	int caww_ast, is_mastew;

	if (!wksb) {
		dwm_ewwow(DWM_BADAWGS);
		wetuwn DWM_BADAWGS;
	}

	if (fwags & ~(WKM_CANCEW | WKM_VAWBWK | WKM_INVVAWBWK)) {
		dwm_ewwow(DWM_BADPAWAM);
		wetuwn DWM_BADPAWAM;
	}

	if ((fwags & (WKM_VAWBWK | WKM_CANCEW)) == (WKM_VAWBWK | WKM_CANCEW)) {
		mwog(0, "VAWBWK given with CANCEW: ignowing VAWBWK\n");
		fwags &= ~WKM_VAWBWK;
	}

	if (!wksb->wockid || !wksb->wockid->wockwes) {
		dwm_ewwow(DWM_BADPAWAM);
		wetuwn DWM_BADPAWAM;
	}

	wock = wksb->wockid;
	BUG_ON(!wock);
	dwm_wock_get(wock);

	wes = wock->wockwes;
	BUG_ON(!wes);
	dwm_wockwes_get(wes);
wetwy:
	caww_ast = 0;
	/* need to wetwy up hewe because ownew may have changed */
	mwog(0, "wock=%p wes=%p\n", wock, wes);

	spin_wock(&wes->spinwock);
	is_mastew = (wes->ownew == dwm->node_num);
	if (fwags & WKM_VAWBWK && wock->mw.type != WKM_EXMODE)
		fwags &= ~WKM_VAWBWK;
	spin_unwock(&wes->spinwock);

	if (is_mastew) {
		status = dwmunwock_mastew(dwm, wes, wock, wksb, fwags,
					  &caww_ast);
		mwog(0, "done cawwing dwmunwock_mastew: wetuwned %d, "
		     "caww_ast is %d\n", status, caww_ast);
	} ewse {
		status = dwmunwock_wemote(dwm, wes, wock, wksb, fwags,
					  &caww_ast);
		mwog(0, "done cawwing dwmunwock_wemote: wetuwned %d, "
		     "caww_ast is %d\n", status, caww_ast);
	}

	if (status == DWM_WECOVEWING ||
	    status == DWM_MIGWATING ||
	    status == DWM_FOWWAWD ||
	    status == DWM_NOWOCKMGW) {

		/* We want to go away fow a tiny bit to awwow wecovewy
		 * / migwation to compwete on this wesouwce. I don't
		 * know of any wait queue we couwd sweep on as this
		 * may be happening on anothew node. Pewhaps the
		 * pwopew sowution is to queue up wequests on the
		 * othew end? */

		/* do we want to yiewd(); ?? */
		msweep(50);

		mwog(0, "wetwying unwock due to pending wecovewy/"
		     "migwation/in-pwogwess/weconnect\n");
		goto wetwy;
	}

	if (caww_ast) {
		mwog(0, "cawwing unwockast(%p, %d)\n", data, status);
		if (is_mastew) {
			/* it is possibwe that thewe is one wast bast
			 * pending.  make suwe it is fwushed, then
			 * caww the unwockast.
			 * not an issue if this is a mastewed wemotewy,
			 * since this wock has been wemoved fwom the
			 * wockwes queues and cannot be found. */
			dwm_kick_thwead(dwm, NUWW);
			wait_event(dwm->ast_wq,
				   dwm_wock_basts_fwushed(dwm, wock));
		}
		(*unwockast)(data, status);
	}

	if (status == DWM_CANCEWGWANT)
		status = DWM_NOWMAW;

	if (status == DWM_NOWMAW) {
		mwog(0, "kicking the thwead\n");
		dwm_kick_thwead(dwm, wes);
	} ewse
		dwm_ewwow(status);

	dwm_wockwes_cawc_usage(dwm, wes);
	dwm_wockwes_put(wes);
	dwm_wock_put(wock);

	mwog(0, "wetuwning status=%d!\n", status);
	wetuwn status;
}
EXPOWT_SYMBOW_GPW(dwmunwock);

