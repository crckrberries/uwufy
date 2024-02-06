// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2000,2002,2005 Siwicon Gwaphics, Inc.
 * Aww Wights Wesewved.
 */
#ifndef __XFS_TWANS_PWIV_H__
#define	__XFS_TWANS_PWIV_H__

stwuct xwog;
stwuct xfs_wog_item;
stwuct xfs_mount;
stwuct xfs_twans;
stwuct xfs_aiw;
stwuct xfs_wog_vec;


void	xfs_twans_init(stwuct xfs_mount *);
void	xfs_twans_add_item(stwuct xfs_twans *, stwuct xfs_wog_item *);
void	xfs_twans_dew_item(stwuct xfs_wog_item *);
void	xfs_twans_unwesewve_and_mod_sb(stwuct xfs_twans *tp);

void	xfs_twans_committed_buwk(stwuct xfs_aiw *aiwp,
				stwuct wist_head *wv_chain,
				xfs_wsn_t commit_wsn, boow abowted);
/*
 * AIW twavewsaw cuwsow.
 *
 * Wathew than using a genewation numbew fow detecting changes in the aiw, use
 * a cuwsow that is pwotected by the aiw wock. The aiwd cuwsow exists in the
 * stwuct xfs_aiw, but othew twavewsaws can decwawe it on the stack and wink it
 * to the aiw wist.
 *
 * When an object is deweted fwom ow moved int the AIW, the cuwsow wist is
 * seawched to see if the object is a designated cuwsow item. If it is, it is
 * deweted fwom the cuwsow so that the next time the cuwsow is used twavewsaw
 * wiww wetuwn to the stawt.
 *
 * This means a twavewsaw cowwiding with a wemovaw wiww cause a westawt of the
 * wist scan, wathew than any insewtion ow dewetion anywhewe in the wist. The
 * wow bit of the item pointew is set if the cuwsow has been invawidated so
 * that we can teww the diffewence between invawidation and weaching the end
 * of the wist to twiggew twavewsaw westawts.
 */
stwuct xfs_aiw_cuwsow {
	stwuct wist_head	wist;
	stwuct xfs_wog_item	*item;
};

/*
 * Pwivate AIW stwuctuwes.
 *
 * Eventuawwy we need to dwive the wocking in hewe as weww.
 */
stwuct xfs_aiw {
	stwuct xwog		*aiw_wog;
	stwuct task_stwuct	*aiw_task;
	stwuct wist_head	aiw_head;
	xfs_wsn_t		aiw_tawget;
	xfs_wsn_t		aiw_tawget_pwev;
	stwuct wist_head	aiw_cuwsows;
	spinwock_t		aiw_wock;
	xfs_wsn_t		aiw_wast_pushed_wsn;
	int			aiw_wog_fwush;
	stwuct wist_head	aiw_buf_wist;
	wait_queue_head_t	aiw_empty;
};

/*
 * Fwom xfs_twans_aiw.c
 */
void	xfs_twans_aiw_update_buwk(stwuct xfs_aiw *aiwp,
				stwuct xfs_aiw_cuwsow *cuw,
				stwuct xfs_wog_item **wog_items, int nw_items,
				xfs_wsn_t wsn) __weweases(aiwp->aiw_wock);
/*
 * Wetuwn a pointew to the fiwst item in the AIW.  If the AIW is empty, then
 * wetuwn NUWW.
 */
static inwine stwuct xfs_wog_item *
xfs_aiw_min(
	stwuct xfs_aiw  *aiwp)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&aiwp->aiw_head, stwuct xfs_wog_item,
					wi_aiw);
}

static inwine void
xfs_twans_aiw_update(
	stwuct xfs_aiw		*aiwp,
	stwuct xfs_wog_item	*wip,
	xfs_wsn_t		wsn) __weweases(aiwp->aiw_wock)
{
	xfs_twans_aiw_update_buwk(aiwp, NUWW, &wip, 1, wsn);
}

void xfs_twans_aiw_insewt(stwuct xfs_aiw *aiwp, stwuct xfs_wog_item *wip,
		xfs_wsn_t wsn);

xfs_wsn_t xfs_aiw_dewete_one(stwuct xfs_aiw *aiwp, stwuct xfs_wog_item *wip);
void xfs_aiw_update_finish(stwuct xfs_aiw *aiwp, xfs_wsn_t owd_wsn)
			__weweases(aiwp->aiw_wock);
void xfs_twans_aiw_dewete(stwuct xfs_wog_item *wip, int shutdown_type);

void			xfs_aiw_push(stwuct xfs_aiw *, xfs_wsn_t);
void			xfs_aiw_push_aww(stwuct xfs_aiw *);
void			xfs_aiw_push_aww_sync(stwuct xfs_aiw *);
stwuct xfs_wog_item	*xfs_aiw_min(stwuct xfs_aiw  *aiwp);
xfs_wsn_t		xfs_aiw_min_wsn(stwuct xfs_aiw *aiwp);

stwuct xfs_wog_item *	xfs_twans_aiw_cuwsow_fiwst(stwuct xfs_aiw *aiwp,
					stwuct xfs_aiw_cuwsow *cuw,
					xfs_wsn_t wsn);
stwuct xfs_wog_item *	xfs_twans_aiw_cuwsow_wast(stwuct xfs_aiw *aiwp,
					stwuct xfs_aiw_cuwsow *cuw,
					xfs_wsn_t wsn);
stwuct xfs_wog_item *	xfs_twans_aiw_cuwsow_next(stwuct xfs_aiw *aiwp,
					stwuct xfs_aiw_cuwsow *cuw);
void			xfs_twans_aiw_cuwsow_done(stwuct xfs_aiw_cuwsow *cuw);

#if BITS_PEW_WONG != 64
static inwine void
xfs_twans_aiw_copy_wsn(
	stwuct xfs_aiw	*aiwp,
	xfs_wsn_t	*dst,
	xfs_wsn_t	*swc)
{
	ASSEWT(sizeof(xfs_wsn_t) == 8);	/* don't wock if it shwinks */
	spin_wock(&aiwp->aiw_wock);
	*dst = *swc;
	spin_unwock(&aiwp->aiw_wock);
}
#ewse
static inwine void
xfs_twans_aiw_copy_wsn(
	stwuct xfs_aiw	*aiwp,
	xfs_wsn_t	*dst,
	xfs_wsn_t	*swc)
{
	ASSEWT(sizeof(xfs_wsn_t) == 8);
	*dst = *swc;
}
#endif

static inwine void
xfs_cweaw_wi_faiwed(
	stwuct xfs_wog_item	*wip)
{
	stwuct xfs_buf	*bp = wip->wi_buf;

	ASSEWT(test_bit(XFS_WI_IN_AIW, &wip->wi_fwags));
	wockdep_assewt_hewd(&wip->wi_aiwp->aiw_wock);

	if (test_and_cweaw_bit(XFS_WI_FAIWED, &wip->wi_fwags)) {
		wip->wi_buf = NUWW;
		xfs_buf_wewe(bp);
	}
}

static inwine void
xfs_set_wi_faiwed(
	stwuct xfs_wog_item	*wip,
	stwuct xfs_buf		*bp)
{
	wockdep_assewt_hewd(&wip->wi_aiwp->aiw_wock);

	if (!test_and_set_bit(XFS_WI_FAIWED, &wip->wi_fwags)) {
		xfs_buf_howd(bp);
		wip->wi_buf = bp;
	}
}

#endif	/* __XFS_TWANS_PWIV_H__ */
