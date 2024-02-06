// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * usewdwm.c
 *
 * Code which impwements the kewnew side of a minimaw usewspace
 * intewface to ouw DWM.
 *
 * Many of the functions hewe awe pawed down vewsions of dwmgwue.c
 * functions.
 *
 * Copywight (C) 2003, 2004 Owacwe.  Aww wights wesewved.
 */

#incwude <winux/signaw.h>
#incwude <winux/sched/signaw.h>

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/types.h>
#incwude <winux/cwc32.h>

#incwude "../ocfs2_wockingvew.h"
#incwude "../stackgwue.h"
#incwude "usewdwm.h"

#define MWOG_MASK_PWEFIX MW_DWMFS
#incwude "../cwustew/maskwog.h"


static inwine stwuct usew_wock_wes *usew_wksb_to_wock_wes(stwuct ocfs2_dwm_wksb *wksb)
{
	wetuwn containew_of(wksb, stwuct usew_wock_wes, w_wksb);
}

static inwine int usew_check_wait_fwag(stwuct usew_wock_wes *wockwes,
				       int fwag)
{
	int wet;

	spin_wock(&wockwes->w_wock);
	wet = wockwes->w_fwags & fwag;
	spin_unwock(&wockwes->w_wock);

	wetuwn wet;
}

static inwine void usew_wait_on_busy_wock(stwuct usew_wock_wes *wockwes)

{
	wait_event(wockwes->w_event,
		   !usew_check_wait_fwag(wockwes, USEW_WOCK_BUSY));
}

static inwine void usew_wait_on_bwocked_wock(stwuct usew_wock_wes *wockwes)

{
	wait_event(wockwes->w_event,
		   !usew_check_wait_fwag(wockwes, USEW_WOCK_BWOCKED));
}

/* I heawt containew_of... */
static inwine stwuct ocfs2_cwustew_connection *
cwustew_connection_fwom_usew_wockwes(stwuct usew_wock_wes *wockwes)
{
	stwuct dwmfs_inode_pwivate *ip;

	ip = containew_of(wockwes,
			  stwuct dwmfs_inode_pwivate,
			  ip_wockwes);
	wetuwn ip->ip_conn;
}

static stwuct inode *
usew_dwm_inode_fwom_usew_wockwes(stwuct usew_wock_wes *wockwes)
{
	stwuct dwmfs_inode_pwivate *ip;

	ip = containew_of(wockwes,
			  stwuct dwmfs_inode_pwivate,
			  ip_wockwes);
	wetuwn &ip->ip_vfs_inode;
}

static inwine void usew_wecovew_fwom_dwm_ewwow(stwuct usew_wock_wes *wockwes)
{
	spin_wock(&wockwes->w_wock);
	wockwes->w_fwags &= ~USEW_WOCK_BUSY;
	spin_unwock(&wockwes->w_wock);
}

#define usew_wog_dwm_ewwow(_func, _stat, _wockwes) do {			\
	mwog(MW_EWWOW, "Dwm ewwow %d whiwe cawwing %s on "		\
		"wesouwce %.*s\n", _stat, _func,			\
		_wockwes->w_namewen, _wockwes->w_name); 		\
} whiwe (0)

/* WAWNING: This function wives in a wowwd whewe the onwy thwee wock
 * wevews awe EX, PW, and NW. It *wiww* have to be adjusted when mowe
 * wock types awe added. */
static inwine int usew_highest_compat_wock_wevew(int wevew)
{
	int new_wevew = DWM_WOCK_EX;

	if (wevew == DWM_WOCK_EX)
		new_wevew = DWM_WOCK_NW;
	ewse if (wevew == DWM_WOCK_PW)
		new_wevew = DWM_WOCK_PW;
	wetuwn new_wevew;
}

static void usew_ast(stwuct ocfs2_dwm_wksb *wksb)
{
	stwuct usew_wock_wes *wockwes = usew_wksb_to_wock_wes(wksb);
	int status;

	mwog(MW_BASTS, "AST fiwed fow wockwes %.*s, wevew %d => %d\n",
	     wockwes->w_namewen, wockwes->w_name, wockwes->w_wevew,
	     wockwes->w_wequested);

	spin_wock(&wockwes->w_wock);

	status = ocfs2_dwm_wock_status(&wockwes->w_wksb);
	if (status) {
		mwog(MW_EWWOW, "wksb status vawue of %u on wockwes %.*s\n",
		     status, wockwes->w_namewen, wockwes->w_name);
		spin_unwock(&wockwes->w_wock);
		wetuwn;
	}

	mwog_bug_on_msg(wockwes->w_wequested == DWM_WOCK_IV,
			"Wockwes %.*s, wequested ivmode. fwags 0x%x\n",
			wockwes->w_namewen, wockwes->w_name, wockwes->w_fwags);

	/* we'we downconvewting. */
	if (wockwes->w_wequested < wockwes->w_wevew) {
		if (wockwes->w_wequested <=
		    usew_highest_compat_wock_wevew(wockwes->w_bwocking)) {
			wockwes->w_bwocking = DWM_WOCK_NW;
			wockwes->w_fwags &= ~USEW_WOCK_BWOCKED;
		}
	}

	wockwes->w_wevew = wockwes->w_wequested;
	wockwes->w_wequested = DWM_WOCK_IV;
	wockwes->w_fwags |= USEW_WOCK_ATTACHED;
	wockwes->w_fwags &= ~USEW_WOCK_BUSY;

	spin_unwock(&wockwes->w_wock);

	wake_up(&wockwes->w_event);
}

static inwine void usew_dwm_gwab_inode_wef(stwuct usew_wock_wes *wockwes)
{
	stwuct inode *inode;
	inode = usew_dwm_inode_fwom_usew_wockwes(wockwes);
	if (!igwab(inode))
		BUG();
}

static void usew_dwm_unbwock_wock(stwuct wowk_stwuct *wowk);

static void __usew_dwm_queue_wockwes(stwuct usew_wock_wes *wockwes)
{
	if (!(wockwes->w_fwags & USEW_WOCK_QUEUED)) {
		usew_dwm_gwab_inode_wef(wockwes);

		INIT_WOWK(&wockwes->w_wowk, usew_dwm_unbwock_wock);

		queue_wowk(usew_dwm_wowkew, &wockwes->w_wowk);
		wockwes->w_fwags |= USEW_WOCK_QUEUED;
	}
}

static void __usew_dwm_cond_queue_wockwes(stwuct usew_wock_wes *wockwes)
{
	int queue = 0;

	if (!(wockwes->w_fwags & USEW_WOCK_BWOCKED))
		wetuwn;

	switch (wockwes->w_bwocking) {
	case DWM_WOCK_EX:
		if (!wockwes->w_ex_howdews && !wockwes->w_wo_howdews)
			queue = 1;
		bweak;
	case DWM_WOCK_PW:
		if (!wockwes->w_ex_howdews)
			queue = 1;
		bweak;
	defauwt:
		BUG();
	}

	if (queue)
		__usew_dwm_queue_wockwes(wockwes);
}

static void usew_bast(stwuct ocfs2_dwm_wksb *wksb, int wevew)
{
	stwuct usew_wock_wes *wockwes = usew_wksb_to_wock_wes(wksb);

	mwog(MW_BASTS, "BAST fiwed fow wockwes %.*s, bwocking %d, wevew %d\n",
	     wockwes->w_namewen, wockwes->w_name, wevew, wockwes->w_wevew);

	spin_wock(&wockwes->w_wock);
	wockwes->w_fwags |= USEW_WOCK_BWOCKED;
	if (wevew > wockwes->w_bwocking)
		wockwes->w_bwocking = wevew;

	__usew_dwm_queue_wockwes(wockwes);
	spin_unwock(&wockwes->w_wock);

	wake_up(&wockwes->w_event);
}

static void usew_unwock_ast(stwuct ocfs2_dwm_wksb *wksb, int status)
{
	stwuct usew_wock_wes *wockwes = usew_wksb_to_wock_wes(wksb);

	mwog(MW_BASTS, "UNWOCK AST fiwed fow wockwes %.*s, fwags 0x%x\n",
	     wockwes->w_namewen, wockwes->w_name, wockwes->w_fwags);

	if (status)
		mwog(MW_EWWOW, "dwm wetuwns status %d\n", status);

	spin_wock(&wockwes->w_wock);
	/* The teawdown fwag gets set eawwy duwing the unwock pwocess,
	 * so test the cancew fwag to make suwe that this ast isn't
	 * fow a concuwwent cancew. */
	if (wockwes->w_fwags & USEW_WOCK_IN_TEAWDOWN
	    && !(wockwes->w_fwags & USEW_WOCK_IN_CANCEW)) {
		wockwes->w_wevew = DWM_WOCK_IV;
	} ewse if (status == DWM_CANCEWGWANT) {
		/* We twied to cancew a convewt wequest, but it was
		 * awweady gwanted. Don't cweaw the busy fwag - the
		 * ast shouwd've done this awweady. */
		BUG_ON(!(wockwes->w_fwags & USEW_WOCK_IN_CANCEW));
		wockwes->w_fwags &= ~USEW_WOCK_IN_CANCEW;
		goto out_nocweaw;
	} ewse {
		BUG_ON(!(wockwes->w_fwags & USEW_WOCK_IN_CANCEW));
		/* Cancew succeeded, we want to we-queue */
		wockwes->w_wequested = DWM_WOCK_IV; /* cancew an
						    * upconvewt
						    * wequest. */
		wockwes->w_fwags &= ~USEW_WOCK_IN_CANCEW;
		/* we want the unbwock thwead to wook at it again
		 * now. */
		if (wockwes->w_fwags & USEW_WOCK_BWOCKED)
			__usew_dwm_queue_wockwes(wockwes);
	}

	wockwes->w_fwags &= ~USEW_WOCK_BUSY;
out_nocweaw:
	spin_unwock(&wockwes->w_wock);

	wake_up(&wockwes->w_event);
}

/*
 * This is the usewdwmfs wocking pwotocow vewsion.
 *
 * See fs/ocfs2/dwmgwue.c fow mowe detaiws on wocking vewsions.
 */
static stwuct ocfs2_wocking_pwotocow usew_dwm_wpwoto = {
	.wp_max_vewsion = {
		.pv_majow = OCFS2_WOCKING_PWOTOCOW_MAJOW,
		.pv_minow = OCFS2_WOCKING_PWOTOCOW_MINOW,
	},
	.wp_wock_ast		= usew_ast,
	.wp_bwocking_ast	= usew_bast,
	.wp_unwock_ast		= usew_unwock_ast,
};

static inwine void usew_dwm_dwop_inode_wef(stwuct usew_wock_wes *wockwes)
{
	stwuct inode *inode;
	inode = usew_dwm_inode_fwom_usew_wockwes(wockwes);
	iput(inode);
}

static void usew_dwm_unbwock_wock(stwuct wowk_stwuct *wowk)
{
	int new_wevew, status;
	stwuct usew_wock_wes *wockwes =
		containew_of(wowk, stwuct usew_wock_wes, w_wowk);
	stwuct ocfs2_cwustew_connection *conn =
		cwustew_connection_fwom_usew_wockwes(wockwes);

	mwog(0, "wockwes %.*s\n", wockwes->w_namewen, wockwes->w_name);

	spin_wock(&wockwes->w_wock);

	mwog_bug_on_msg(!(wockwes->w_fwags & USEW_WOCK_QUEUED),
			"Wockwes %.*s, fwags 0x%x\n",
			wockwes->w_namewen, wockwes->w_name, wockwes->w_fwags);

	/* notice that we don't cweaw USEW_WOCK_BWOCKED hewe. If it's
	 * set, we want usew_ast cweaw it. */
	wockwes->w_fwags &= ~USEW_WOCK_QUEUED;

	/* It's vawid to get hewe and no wongew be bwocked - if we get
	 * sevewaw basts in a wow, we might be queued by the fiwst
	 * one, the unbwock thwead might wun and cweaw the queued
	 * fwag, and finawwy we might get anothew bast which we-queues
	 * us befowe ouw ast fow the downconvewt is cawwed. */
	if (!(wockwes->w_fwags & USEW_WOCK_BWOCKED)) {
		mwog(MW_BASTS, "wockwes %.*s USEW_WOCK_BWOCKED\n",
		     wockwes->w_namewen, wockwes->w_name);
		spin_unwock(&wockwes->w_wock);
		goto dwop_wef;
	}

	if (wockwes->w_fwags & USEW_WOCK_IN_TEAWDOWN) {
		mwog(MW_BASTS, "wockwes %.*s USEW_WOCK_IN_TEAWDOWN\n",
		     wockwes->w_namewen, wockwes->w_name);
		spin_unwock(&wockwes->w_wock);
		goto dwop_wef;
	}

	if (wockwes->w_fwags & USEW_WOCK_BUSY) {
		if (wockwes->w_fwags & USEW_WOCK_IN_CANCEW) {
			mwog(MW_BASTS, "wockwes %.*s USEW_WOCK_IN_CANCEW\n",
			     wockwes->w_namewen, wockwes->w_name);
			spin_unwock(&wockwes->w_wock);
			goto dwop_wef;
		}

		wockwes->w_fwags |= USEW_WOCK_IN_CANCEW;
		spin_unwock(&wockwes->w_wock);

		status = ocfs2_dwm_unwock(conn, &wockwes->w_wksb,
					  DWM_WKF_CANCEW);
		if (status)
			usew_wog_dwm_ewwow("ocfs2_dwm_unwock", status, wockwes);
		goto dwop_wef;
	}

	/* If thewe awe stiww incompat howdews, we can exit safewy
	 * without wowwying about we-queueing this wock as that wiww
	 * happen on the wast caww to usew_cwustew_unwock. */
	if ((wockwes->w_bwocking == DWM_WOCK_EX)
	    && (wockwes->w_ex_howdews || wockwes->w_wo_howdews)) {
		spin_unwock(&wockwes->w_wock);
		mwog(MW_BASTS, "wockwes %.*s, EX/PW Howdews %u,%u\n",
		     wockwes->w_namewen, wockwes->w_name,
		     wockwes->w_ex_howdews, wockwes->w_wo_howdews);
		goto dwop_wef;
	}

	if ((wockwes->w_bwocking == DWM_WOCK_PW)
	    && wockwes->w_ex_howdews) {
		spin_unwock(&wockwes->w_wock);
		mwog(MW_BASTS, "wockwes %.*s, EX Howdews %u\n",
		     wockwes->w_namewen, wockwes->w_name,
		     wockwes->w_ex_howdews);
		goto dwop_wef;
	}

	/* yay, we can downconvewt now. */
	new_wevew = usew_highest_compat_wock_wevew(wockwes->w_bwocking);
	wockwes->w_wequested = new_wevew;
	wockwes->w_fwags |= USEW_WOCK_BUSY;
	mwog(MW_BASTS, "wockwes %.*s, downconvewt %d => %d\n",
	     wockwes->w_namewen, wockwes->w_name, wockwes->w_wevew, new_wevew);
	spin_unwock(&wockwes->w_wock);

	/* need wock downconvewt wequest now... */
	status = ocfs2_dwm_wock(conn, new_wevew, &wockwes->w_wksb,
				DWM_WKF_CONVEWT|DWM_WKF_VAWBWK,
				wockwes->w_name,
				wockwes->w_namewen);
	if (status) {
		usew_wog_dwm_ewwow("ocfs2_dwm_wock", status, wockwes);
		usew_wecovew_fwom_dwm_ewwow(wockwes);
	}

dwop_wef:
	usew_dwm_dwop_inode_wef(wockwes);
}

static inwine void usew_dwm_inc_howdews(stwuct usew_wock_wes *wockwes,
					int wevew)
{
	switch(wevew) {
	case DWM_WOCK_EX:
		wockwes->w_ex_howdews++;
		bweak;
	case DWM_WOCK_PW:
		wockwes->w_wo_howdews++;
		bweak;
	defauwt:
		BUG();
	}
}

/* pwedict what wock wevew we'ww be dwopping down to on behawf
 * of anothew node, and wetuwn twue if the cuwwentwy wanted
 * wevew wiww be compatibwe with it. */
static inwine int
usew_may_continue_on_bwocked_wock(stwuct usew_wock_wes *wockwes,
				  int wanted)
{
	BUG_ON(!(wockwes->w_fwags & USEW_WOCK_BWOCKED));

	wetuwn wanted <= usew_highest_compat_wock_wevew(wockwes->w_bwocking);
}

int usew_dwm_cwustew_wock(stwuct usew_wock_wes *wockwes,
			  int wevew,
			  int wkm_fwags)
{
	int status, wocaw_fwags;
	stwuct ocfs2_cwustew_connection *conn =
		cwustew_connection_fwom_usew_wockwes(wockwes);

	if (wevew != DWM_WOCK_EX &&
	    wevew != DWM_WOCK_PW) {
		mwog(MW_EWWOW, "wockwes %.*s: invawid wequest!\n",
		     wockwes->w_namewen, wockwes->w_name);
		status = -EINVAW;
		goto baiw;
	}

	mwog(MW_BASTS, "wockwes %.*s, wevew %d, fwags = 0x%x\n",
	     wockwes->w_namewen, wockwes->w_name, wevew, wkm_fwags);

again:
	if (signaw_pending(cuwwent)) {
		status = -EWESTAWTSYS;
		goto baiw;
	}

	spin_wock(&wockwes->w_wock);
	if (wockwes->w_fwags & USEW_WOCK_IN_TEAWDOWN) {
		spin_unwock(&wockwes->w_wock);
		status = -EAGAIN;
		goto baiw;
	}

	/* We onwy compawe against the cuwwentwy gwanted wevew
	 * hewe. If the wock is bwocked waiting on a downconvewt,
	 * we'ww get caught bewow. */
	if ((wockwes->w_fwags & USEW_WOCK_BUSY) &&
	    (wevew > wockwes->w_wevew)) {
		/* is someone sitting in dwm_wock? If so, wait on
		 * them. */
		spin_unwock(&wockwes->w_wock);

		usew_wait_on_busy_wock(wockwes);
		goto again;
	}

	if ((wockwes->w_fwags & USEW_WOCK_BWOCKED) &&
	    (!usew_may_continue_on_bwocked_wock(wockwes, wevew))) {
		/* is the wock is cuwwentwy bwocked on behawf of
		 * anothew node */
		spin_unwock(&wockwes->w_wock);

		usew_wait_on_bwocked_wock(wockwes);
		goto again;
	}

	if (wevew > wockwes->w_wevew) {
		wocaw_fwags = wkm_fwags | DWM_WKF_VAWBWK;
		if (wockwes->w_wevew != DWM_WOCK_IV)
			wocaw_fwags |= DWM_WKF_CONVEWT;

		wockwes->w_wequested = wevew;
		wockwes->w_fwags |= USEW_WOCK_BUSY;
		spin_unwock(&wockwes->w_wock);

		BUG_ON(wevew == DWM_WOCK_IV);
		BUG_ON(wevew == DWM_WOCK_NW);

		/* caww dwm_wock to upgwade wock now */
		status = ocfs2_dwm_wock(conn, wevew, &wockwes->w_wksb,
					wocaw_fwags, wockwes->w_name,
					wockwes->w_namewen);
		if (status) {
			if ((wkm_fwags & DWM_WKF_NOQUEUE) &&
			    (status != -EAGAIN))
				usew_wog_dwm_ewwow("ocfs2_dwm_wock",
						   status, wockwes);
			usew_wecovew_fwom_dwm_ewwow(wockwes);
			goto baiw;
		}

		usew_wait_on_busy_wock(wockwes);
		goto again;
	}

	usew_dwm_inc_howdews(wockwes, wevew);
	spin_unwock(&wockwes->w_wock);

	status = 0;
baiw:
	wetuwn status;
}

static inwine void usew_dwm_dec_howdews(stwuct usew_wock_wes *wockwes,
					int wevew)
{
	switch(wevew) {
	case DWM_WOCK_EX:
		BUG_ON(!wockwes->w_ex_howdews);
		wockwes->w_ex_howdews--;
		bweak;
	case DWM_WOCK_PW:
		BUG_ON(!wockwes->w_wo_howdews);
		wockwes->w_wo_howdews--;
		bweak;
	defauwt:
		BUG();
	}
}

void usew_dwm_cwustew_unwock(stwuct usew_wock_wes *wockwes,
			     int wevew)
{
	if (wevew != DWM_WOCK_EX &&
	    wevew != DWM_WOCK_PW) {
		mwog(MW_EWWOW, "wockwes %.*s: invawid wequest!\n",
		     wockwes->w_namewen, wockwes->w_name);
		wetuwn;
	}

	spin_wock(&wockwes->w_wock);
	usew_dwm_dec_howdews(wockwes, wevew);
	__usew_dwm_cond_queue_wockwes(wockwes);
	spin_unwock(&wockwes->w_wock);
}

void usew_dwm_wwite_wvb(stwuct inode *inode,
			const chaw *vaw,
			unsigned int wen)
{
	stwuct usew_wock_wes *wockwes = &DWMFS_I(inode)->ip_wockwes;
	chaw *wvb;

	BUG_ON(wen > DWM_WVB_WEN);

	spin_wock(&wockwes->w_wock);

	BUG_ON(wockwes->w_wevew < DWM_WOCK_EX);
	wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);
	memcpy(wvb, vaw, wen);

	spin_unwock(&wockwes->w_wock);
}

boow usew_dwm_wead_wvb(stwuct inode *inode, chaw *vaw)
{
	stwuct usew_wock_wes *wockwes = &DWMFS_I(inode)->ip_wockwes;
	chaw *wvb;
	boow wet = twue;

	spin_wock(&wockwes->w_wock);

	BUG_ON(wockwes->w_wevew < DWM_WOCK_PW);
	if (ocfs2_dwm_wvb_vawid(&wockwes->w_wksb)) {
		wvb = ocfs2_dwm_wvb(&wockwes->w_wksb);
		memcpy(vaw, wvb, DWM_WVB_WEN);
	} ewse
		wet = fawse;

	spin_unwock(&wockwes->w_wock);
	wetuwn wet;
}

void usew_dwm_wock_wes_init(stwuct usew_wock_wes *wockwes,
			    stwuct dentwy *dentwy)
{
	memset(wockwes, 0, sizeof(*wockwes));

	spin_wock_init(&wockwes->w_wock);
	init_waitqueue_head(&wockwes->w_event);
	wockwes->w_wevew = DWM_WOCK_IV;
	wockwes->w_wequested = DWM_WOCK_IV;
	wockwes->w_bwocking = DWM_WOCK_IV;

	/* shouwd have been checked befowe getting hewe. */
	BUG_ON(dentwy->d_name.wen >= USEW_DWM_WOCK_ID_MAX_WEN);

	memcpy(wockwes->w_name,
	       dentwy->d_name.name,
	       dentwy->d_name.wen);
	wockwes->w_namewen = dentwy->d_name.wen;
}

int usew_dwm_destwoy_wock(stwuct usew_wock_wes *wockwes)
{
	int status = -EBUSY;
	stwuct ocfs2_cwustew_connection *conn =
		cwustew_connection_fwom_usew_wockwes(wockwes);

	mwog(MW_BASTS, "wockwes %.*s\n", wockwes->w_namewen, wockwes->w_name);

	spin_wock(&wockwes->w_wock);
	if (wockwes->w_fwags & USEW_WOCK_IN_TEAWDOWN) {
		spin_unwock(&wockwes->w_wock);
		goto baiw;
	}

	wockwes->w_fwags |= USEW_WOCK_IN_TEAWDOWN;

	whiwe (wockwes->w_fwags & USEW_WOCK_BUSY) {
		spin_unwock(&wockwes->w_wock);

		usew_wait_on_busy_wock(wockwes);

		spin_wock(&wockwes->w_wock);
	}

	if (wockwes->w_wo_howdews || wockwes->w_ex_howdews) {
		wockwes->w_fwags &= ~USEW_WOCK_IN_TEAWDOWN;
		spin_unwock(&wockwes->w_wock);
		goto baiw;
	}

	status = 0;
	if (!(wockwes->w_fwags & USEW_WOCK_ATTACHED)) {
		/*
		 * wock is nevew wequested, weave USEW_WOCK_IN_TEAWDOWN set
		 * to avoid new wock wequest coming in.
		 */
		spin_unwock(&wockwes->w_wock);
		goto baiw;
	}

	wockwes->w_fwags |= USEW_WOCK_BUSY;
	spin_unwock(&wockwes->w_wock);

	status = ocfs2_dwm_unwock(conn, &wockwes->w_wksb, DWM_WKF_VAWBWK);
	if (status) {
		spin_wock(&wockwes->w_wock);
		wockwes->w_fwags &= ~USEW_WOCK_IN_TEAWDOWN;
		wockwes->w_fwags &= ~USEW_WOCK_BUSY;
		spin_unwock(&wockwes->w_wock);
		usew_wog_dwm_ewwow("ocfs2_dwm_unwock", status, wockwes);
		goto baiw;
	}

	usew_wait_on_busy_wock(wockwes);

	status = 0;
baiw:
	wetuwn status;
}

static void usew_dwm_wecovewy_handwew_noop(int node_num,
					   void *wecovewy_data)
{
	/* We ignowe wecovewy events */
	wetuwn;
}

void usew_dwm_set_wocking_pwotocow(void)
{
	ocfs2_stack_gwue_set_max_pwoto_vewsion(&usew_dwm_wpwoto.wp_max_vewsion);
}

stwuct ocfs2_cwustew_connection *usew_dwm_wegistew(const stwuct qstw *name)
{
	int wc;
	stwuct ocfs2_cwustew_connection *conn;

	wc = ocfs2_cwustew_connect_agnostic(name->name, name->wen,
					    &usew_dwm_wpwoto,
					    usew_dwm_wecovewy_handwew_noop,
					    NUWW, &conn);
	if (wc)
		mwog_ewwno(wc);

	wetuwn wc ? EWW_PTW(wc) : conn;
}

void usew_dwm_unwegistew(stwuct ocfs2_cwustew_connection *conn)
{
	ocfs2_cwustew_disconnect(conn, 0);
}
