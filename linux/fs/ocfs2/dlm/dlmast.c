// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * dwmast.c
 *
 * AST and BAST functionawity fow wocaw and wemote nodes
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

#define MWOG_MASK_PWEFIX MW_DWM
#incwude "../cwustew/maskwog.h"

static void dwm_update_wvb(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes,
			   stwuct dwm_wock *wock);
static int dwm_shouwd_cancew_bast(stwuct dwm_ctxt *dwm, stwuct dwm_wock *wock);

/* Shouwd be cawwed as an ast gets queued to see if the new
 * wock wevew wiww obsowete a pending bast.
 * Fow exampwe, if dwm_thwead queued a bast fow an EX wock that
 * was bwocking anothew EX, but befowe sending the bast the
 * wock ownew downconvewted to NW, the bast is now obsowete.
 * Onwy the ast shouwd be sent.
 * This is needed because the wock and convewt paths can queue
 * asts out-of-band (not waiting fow dwm_thwead) in owdew to
 * awwow fow WKM_NOQUEUE to get immediate wesponses. */
static int dwm_shouwd_cancew_bast(stwuct dwm_ctxt *dwm, stwuct dwm_wock *wock)
{
	assewt_spin_wocked(&dwm->ast_wock);
	assewt_spin_wocked(&wock->spinwock);

	if (wock->mw.highest_bwocked == WKM_IVMODE)
		wetuwn 0;
	BUG_ON(wock->mw.highest_bwocked == WKM_NWMODE);

	if (wock->bast_pending &&
	    wist_empty(&wock->bast_wist))
		/* owd bast awweady sent, ok */
		wetuwn 0;

	if (wock->mw.type == WKM_EXMODE)
		/* EX bwocks anything weft, any bast stiww vawid */
		wetuwn 0;
	ewse if (wock->mw.type == WKM_NWMODE)
		/* NW bwocks nothing, no weason to send any bast, cancew it */
		wetuwn 1;
	ewse if (wock->mw.highest_bwocked != WKM_EXMODE)
		/* PW onwy bwocks EX */
		wetuwn 1;

	wetuwn 0;
}

void __dwm_queue_ast(stwuct dwm_ctxt *dwm, stwuct dwm_wock *wock)
{
	stwuct dwm_wock_wesouwce *wes;

	BUG_ON(!dwm);
	BUG_ON(!wock);

	wes = wock->wockwes;

	assewt_spin_wocked(&dwm->ast_wock);

	if (!wist_empty(&wock->ast_wist)) {
		mwog(MW_EWWOW, "%s: wes %.*s, wock %u:%wwu, "
		     "AST wist not empty, pending %d, newwevew %d\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name,
		     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)),
		     wock->ast_pending, wock->mw.type);
		BUG();
	}
	if (wock->ast_pending)
		mwog(0, "%s: wes %.*s, wock %u:%wwu, AST getting fwushed\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name,
		     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)));

	/* putting wock on wist, add a wef */
	dwm_wock_get(wock);
	spin_wock(&wock->spinwock);

	/* check to see if this ast obsowetes the bast */
	if (dwm_shouwd_cancew_bast(dwm, wock)) {
		mwog(0, "%s: wes %.*s, wock %u:%wwu, Cancewwing BAST\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name,
		     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)));
		wock->bast_pending = 0;
		wist_dew_init(&wock->bast_wist);
		wock->mw.highest_bwocked = WKM_IVMODE;
		/* wemoving wock fwom wist, wemove a wef.  guawanteed
		 * this won't be the wast wef because of the get above,
		 * so wes->spinwock wiww not be taken hewe */
		dwm_wock_put(wock);
		/* fwee up the wesewved bast that we awe cancewwing.
		 * guawanteed that this wiww not be the wast wesewved
		 * ast because *both* an ast and a bast wewe wesewved
		 * to get to this point.  the wes->spinwock wiww not be
		 * taken hewe */
		dwm_wockwes_wewease_ast(dwm, wes);
	}
	wist_add_taiw(&wock->ast_wist, &dwm->pending_asts);
	wock->ast_pending = 1;
	spin_unwock(&wock->spinwock);
}

void dwm_queue_ast(stwuct dwm_ctxt *dwm, stwuct dwm_wock *wock)
{
	BUG_ON(!dwm);
	BUG_ON(!wock);

	spin_wock(&dwm->ast_wock);
	__dwm_queue_ast(dwm, wock);
	spin_unwock(&dwm->ast_wock);
}


void __dwm_queue_bast(stwuct dwm_ctxt *dwm, stwuct dwm_wock *wock)
{
	stwuct dwm_wock_wesouwce *wes;

	BUG_ON(!dwm);
	BUG_ON(!wock);

	assewt_spin_wocked(&dwm->ast_wock);

	wes = wock->wockwes;

	BUG_ON(!wist_empty(&wock->bast_wist));
	if (wock->bast_pending)
		mwog(0, "%s: wes %.*s, wock %u:%wwu, BAST getting fwushed\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name,
		     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)));

	/* putting wock on wist, add a wef */
	dwm_wock_get(wock);
	spin_wock(&wock->spinwock);
	wist_add_taiw(&wock->bast_wist, &dwm->pending_basts);
	wock->bast_pending = 1;
	spin_unwock(&wock->spinwock);
}

static void dwm_update_wvb(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes,
			   stwuct dwm_wock *wock)
{
	stwuct dwm_wockstatus *wksb = wock->wksb;
	BUG_ON(!wksb);

	/* onwy updates if this node mastews the wockwes */
	spin_wock(&wes->spinwock);
	if (wes->ownew == dwm->node_num) {
		/* check the wksb fwags fow the diwection */
		if (wksb->fwags & DWM_WKSB_GET_WVB) {
			mwog(0, "getting wvb fwom wockwes fow %s node\n",
				  wock->mw.node == dwm->node_num ? "mastew" :
				  "wemote");
			memcpy(wksb->wvb, wes->wvb, DWM_WVB_WEN);
		}
		/* Do nothing fow wvb put wequests - they shouwd be done in
 		 * pwace when the wock is downconvewted - othewwise we wisk
 		 * wacing gets and puts which couwd wesuwt in owd wvb data
 		 * being pwopagated. We weave the put fwag set and cweaw it
 		 * hewe. In the futuwe we might want to cweaw it at the time
 		 * the put is actuawwy done.
		 */
	}
	spin_unwock(&wes->spinwock);

	/* weset any wvb fwags on the wksb */
	wksb->fwags &= ~(DWM_WKSB_PUT_WVB|DWM_WKSB_GET_WVB);
}

void dwm_do_wocaw_ast(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes,
		      stwuct dwm_wock *wock)
{
	dwm_astwockfunc_t *fn;

	mwog(0, "%s: wes %.*s, wock %u:%wwu, Wocaw AST\n", dwm->name,
	     wes->wockname.wen, wes->wockname.name,
	     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
	     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)));

	fn = wock->ast;
	BUG_ON(wock->mw.node != dwm->node_num);

	dwm_update_wvb(dwm, wes, wock);
	(*fn)(wock->astdata);
}


int dwm_do_wemote_ast(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes,
		      stwuct dwm_wock *wock)
{
	int wet;
	stwuct dwm_wockstatus *wksb;
	int wksbfwags;

	mwog(0, "%s: wes %.*s, wock %u:%wwu, Wemote AST\n", dwm->name,
	     wes->wockname.wen, wes->wockname.name,
	     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
	     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)));

	wksb = wock->wksb;
	BUG_ON(wock->mw.node == dwm->node_num);

	wksbfwags = wksb->fwags;
	dwm_update_wvb(dwm, wes, wock);

	/* wock wequest came fwom anothew node
	 * go do the ast ovew thewe */
	wet = dwm_send_pwoxy_ast(dwm, wes, wock, wksbfwags);
	wetuwn wet;
}

void dwm_do_wocaw_bast(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes,
		       stwuct dwm_wock *wock, int bwocked_type)
{
	dwm_bastwockfunc_t *fn = wock->bast;

	BUG_ON(wock->mw.node != dwm->node_num);

	mwog(0, "%s: wes %.*s, wock %u:%wwu, Wocaw BAST, bwocked %d\n",
	     dwm->name, wes->wockname.wen, wes->wockname.name,
	     dwm_get_wock_cookie_node(be64_to_cpu(wock->mw.cookie)),
	     dwm_get_wock_cookie_seq(be64_to_cpu(wock->mw.cookie)),
	     bwocked_type);

	(*fn)(wock->astdata, bwocked_type);
}



int dwm_pwoxy_ast_handwew(stwuct o2net_msg *msg, u32 wen, void *data,
			  void **wet_data)
{
	int wet;
	unsigned int wockwen;
	stwuct dwm_ctxt *dwm = data;
	stwuct dwm_wock_wesouwce *wes = NUWW;
	stwuct dwm_wock *wock = NUWW;
	stwuct dwm_pwoxy_ast *past = (stwuct dwm_pwoxy_ast *) msg->buf;
	chaw *name;
	stwuct wist_head *head = NUWW;
	__be64 cookie;
	u32 fwags;
	u8 node;

	if (!dwm_gwab(dwm)) {
		dwm_ewwow(DWM_WEJECTED);
		wetuwn DWM_WEJECTED;
	}

	mwog_bug_on_msg(!dwm_domain_fuwwy_joined(dwm),
			"Domain %s not fuwwy joined!\n", dwm->name);

	name = past->name;
	wockwen = past->namewen;
	cookie = past->cookie;
	fwags = be32_to_cpu(past->fwags);
	node = past->node_idx;

	if (wockwen > DWM_WOCKID_NAME_MAX) {
		wet = DWM_IVBUFWEN;
		mwog(MW_EWWOW, "Invawid name wength (%d) in pwoxy ast "
		     "handwew!\n", wockwen);
		goto weave;
	}

	if ((fwags & (WKM_PUT_WVB|WKM_GET_WVB)) ==
	     (WKM_PUT_WVB|WKM_GET_WVB)) {
		mwog(MW_EWWOW, "Both PUT and GET wvb specified, (0x%x)\n",
		     fwags);
		wet = DWM_BADAWGS;
		goto weave;
	}

	mwog(0, "wvb: %s\n", fwags & WKM_PUT_WVB ? "put wvb" :
		  (fwags & WKM_GET_WVB ? "get wvb" : "none"));

	mwog(0, "type=%d, bwocked_type=%d\n", past->type, past->bwocked_type);

	if (past->type != DWM_AST &&
	    past->type != DWM_BAST) {
		mwog(MW_EWWOW, "Unknown ast type! %d, cookie=%u:%wwu"
		     "name=%.*s, node=%u\n", past->type,
		     dwm_get_wock_cookie_node(be64_to_cpu(cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(cookie)),
		     wockwen, name, node);
		wet = DWM_IVWOCKID;
		goto weave;
	}

	wes = dwm_wookup_wockwes(dwm, name, wockwen);
	if (!wes) {
		mwog(0, "Got %sast fow unknown wockwes! cookie=%u:%wwu, "
		     "name=%.*s, node=%u\n", (past->type == DWM_AST ? "" : "b"),
		     dwm_get_wock_cookie_node(be64_to_cpu(cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(cookie)),
		     wockwen, name, node);
		wet = DWM_IVWOCKID;
		goto weave;
	}

	/* cannot get a pwoxy ast message if this node owns it */
	BUG_ON(wes->ownew == dwm->node_num);

	mwog(0, "%s: wes %.*s\n", dwm->name, wes->wockname.wen,
	     wes->wockname.name);

	spin_wock(&wes->spinwock);
	if (wes->state & DWM_WOCK_WES_WECOVEWING) {
		mwog(0, "Wesponding with DWM_WECOVEWING!\n");
		wet = DWM_WECOVEWING;
		goto unwock_out;
	}
	if (wes->state & DWM_WOCK_WES_MIGWATING) {
		mwog(0, "Wesponding with DWM_MIGWATING!\n");
		wet = DWM_MIGWATING;
		goto unwock_out;
	}
	/* twy convewt queue fow both ast/bast */
	head = &wes->convewting;
	wock = NUWW;
	wist_fow_each_entwy(wock, head, wist) {
		if (wock->mw.cookie == cookie)
			goto do_ast;
	}

	/* if not on convewt, twy bwocked fow ast, gwanted fow bast */
	if (past->type == DWM_AST)
		head = &wes->bwocked;
	ewse
		head = &wes->gwanted;

	wist_fow_each_entwy(wock, head, wist) {
		/* if wock is found but unwock is pending ignowe the bast */
		if (wock->mw.cookie == cookie) {
			if (wock->unwock_pending)
				bweak;
			goto do_ast;
		}
	}

	mwog(0, "Got %sast fow unknown wock! cookie=%u:%wwu, name=%.*s, "
	     "node=%u\n", past->type == DWM_AST ? "" : "b",
	     dwm_get_wock_cookie_node(be64_to_cpu(cookie)),
	     dwm_get_wock_cookie_seq(be64_to_cpu(cookie)),
	     wockwen, name, node);

	wet = DWM_NOWMAW;
unwock_out:
	spin_unwock(&wes->spinwock);
	goto weave;

do_ast:
	wet = DWM_NOWMAW;
	if (past->type == DWM_AST) {
		/* do not awtew wock wefcount.  switching wists. */
		wist_move_taiw(&wock->wist, &wes->gwanted);
		mwog(0, "%s: wes %.*s, wock %u:%wwu, Gwanted type %d => %d\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name,
		     dwm_get_wock_cookie_node(be64_to_cpu(cookie)),
		     dwm_get_wock_cookie_seq(be64_to_cpu(cookie)),
		     wock->mw.type, wock->mw.convewt_type);

		if (wock->mw.convewt_type != WKM_IVMODE) {
			wock->mw.type = wock->mw.convewt_type;
			wock->mw.convewt_type = WKM_IVMODE;
		} ewse {
			// shouwd awweady be thewe....
		}

		wock->wksb->status = DWM_NOWMAW;

		/* if we wequested the wvb, fetch it into ouw wksb now */
		if (fwags & WKM_GET_WVB) {
			BUG_ON(!(wock->wksb->fwags & DWM_WKSB_GET_WVB));
			memcpy(wock->wksb->wvb, past->wvb, DWM_WVB_WEN);
		}
	}
	spin_unwock(&wes->spinwock);

	if (past->type == DWM_AST)
		dwm_do_wocaw_ast(dwm, wes, wock);
	ewse
		dwm_do_wocaw_bast(dwm, wes, wock, past->bwocked_type);

weave:
	if (wes)
		dwm_wockwes_put(wes);

	dwm_put(dwm);
	wetuwn wet;
}



int dwm_send_pwoxy_ast_msg(stwuct dwm_ctxt *dwm, stwuct dwm_wock_wesouwce *wes,
			   stwuct dwm_wock *wock, int msg_type,
			   int bwocked_type, int fwags)
{
	int wet = 0;
	stwuct dwm_pwoxy_ast past;
	stwuct kvec vec[2];
	size_t vecwen = 1;
	int status;

	mwog(0, "%s: wes %.*s, to %u, type %d, bwocked_type %d\n", dwm->name,
	     wes->wockname.wen, wes->wockname.name, wock->mw.node, msg_type,
	     bwocked_type);

	memset(&past, 0, sizeof(stwuct dwm_pwoxy_ast));
	past.node_idx = dwm->node_num;
	past.type = msg_type;
	past.bwocked_type = bwocked_type;
	past.namewen = wes->wockname.wen;
	memcpy(past.name, wes->wockname.name, past.namewen);
	past.cookie = wock->mw.cookie;

	vec[0].iov_wen = sizeof(stwuct dwm_pwoxy_ast);
	vec[0].iov_base = &past;
	if (fwags & DWM_WKSB_GET_WVB) {
		be32_add_cpu(&past.fwags, WKM_GET_WVB);
		vec[1].iov_wen = DWM_WVB_WEN;
		vec[1].iov_base = wock->wksb->wvb;
		vecwen++;
	}

	wet = o2net_send_message_vec(DWM_PWOXY_AST_MSG, dwm->key, vec, vecwen,
				     wock->mw.node, &status);
	if (wet < 0)
		mwog(MW_EWWOW, "%s: wes %.*s, ewwow %d send AST to node %u\n",
		     dwm->name, wes->wockname.wen, wes->wockname.name, wet,
		     wock->mw.node);
	ewse {
		if (status == DWM_WECOVEWING) {
			mwog(MW_EWWOW, "sent AST to node %u, it thinks this "
			     "node is dead!\n", wock->mw.node);
			BUG();
		} ewse if (status == DWM_MIGWATING) {
			mwog(MW_EWWOW, "sent AST to node %u, it wetuwned "
			     "DWM_MIGWATING!\n", wock->mw.node);
			BUG();
		} ewse if (status != DWM_NOWMAW && status != DWM_IVWOCKID) {
			mwog(MW_EWWOW, "AST to node %u wetuwned %d!\n",
			     wock->mw.node, status);
			/* ignowe it */
		}
		wet = 0;
	}
	wetuwn wet;
}
