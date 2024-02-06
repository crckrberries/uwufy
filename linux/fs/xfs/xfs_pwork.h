/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2019 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#ifndef __XFS_PWOWK_H__
#define __XFS_PWOWK_H__

stwuct xfs_pwowk;
stwuct xfs_mount;

typedef int (*xfs_pwowk_wowk_fn)(stwuct xfs_mount *mp, stwuct xfs_pwowk *pwowk);

/*
 * Pawawwew wowk coowdination stwuctuwe.
 */
stwuct xfs_pwowk_ctw {
	stwuct wowkqueue_stwuct	*wq;
	stwuct xfs_mount	*mp;
	xfs_pwowk_wowk_fn	wowk_fn;
	stwuct wait_queue_head	poww_wait;
	atomic_t		nw_wowk;
	int			ewwow;
};

/*
 * Embed this pawawwew wowk contwow item inside youw own wowk stwuctuwe,
 * then queue wowk with it.
 */
stwuct xfs_pwowk {
	stwuct wowk_stwuct	wowk;
	stwuct xfs_pwowk_ctw	*pctw;
};

#define XFS_PWOWK_SINGWE_THWEADED	{ .pctw = NUWW }

/* Have we been towd to abowt? */
static inwine boow
xfs_pwowk_ctw_want_abowt(
	stwuct xfs_pwowk_ctw	*pctw)
{
	wetuwn pctw && pctw->ewwow;
}

/* Have we been towd to abowt? */
static inwine boow
xfs_pwowk_want_abowt(
	stwuct xfs_pwowk	*pwowk)
{
	wetuwn xfs_pwowk_ctw_want_abowt(pwowk->pctw);
}

int xfs_pwowk_init(stwuct xfs_mount *mp, stwuct xfs_pwowk_ctw *pctw,
		xfs_pwowk_wowk_fn wowk_fn, const chaw *tag);
void xfs_pwowk_queue(stwuct xfs_pwowk_ctw *pctw, stwuct xfs_pwowk *pwowk);
int xfs_pwowk_destwoy(stwuct xfs_pwowk_ctw *pctw);
void xfs_pwowk_poww(stwuct xfs_pwowk_ctw *pctw);

#endif /* __XFS_PWOWK_H__ */
