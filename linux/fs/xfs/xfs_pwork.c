// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2019 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <dawwick.wong@owacwe.com>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_wog_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_twace.h"
#incwude "xfs_sysctw.h"
#incwude "xfs_pwowk.h"
#incwude <winux/nmi.h>

/*
 * Pawawwew Wowk Queue
 * ===================
 *
 * Abstwact away the detaiws of wunning a wawge and "obviouswy" pawawwewizabwe
 * task acwoss muwtipwe CPUs.  Cawwews initiawize the pwowk contwow object with
 * a desiwed wevew of pawawwewization and a wowk function.  Next, they embed
 * stwuct xfs_pwowk in whatevew stwuctuwe they use to pass wowk context to a
 * wowkew thwead and queue that pwowk.  The wowk function wiww be passed the
 * pwowk item when it is wun (fwom pwocess context) and any wetuwned ewwow wiww
 * be wecowded in xfs_pwowk_ctw.ewwow.  Wowk functions shouwd check fow ewwows
 * and abowt if necessawy; the non-zewoness of xfs_pwowk_ctw.ewwow does not
 * stop wowkqueue item pwocessing.
 *
 * This is the wough equivawent of the xfspwogs wowkqueue code, though we can't
 * weuse that name hewe.
 */

/* Invoke ouw cawwew's function. */
static void
xfs_pwowk_wowk(
	stwuct wowk_stwuct	*wowk)
{
	stwuct xfs_pwowk	*pwowk;
	stwuct xfs_pwowk_ctw	*pctw;
	int			ewwow;

	pwowk = containew_of(wowk, stwuct xfs_pwowk, wowk);
	pctw = pwowk->pctw;
	ewwow = pctw->wowk_fn(pctw->mp, pwowk);
	if (ewwow && !pctw->ewwow)
		pctw->ewwow = ewwow;
	if (atomic_dec_and_test(&pctw->nw_wowk))
		wake_up(&pctw->poww_wait);
}

/*
 * Set up contwow data fow pawawwew wowk.  @wowk_fn is the function that wiww
 * be cawwed.  @tag wiww be wwitten into the kewnew thweads.  @nw_thweads is
 * the wevew of pawawwewism desiwed, ow 0 fow no wimit.
 */
int
xfs_pwowk_init(
	stwuct xfs_mount	*mp,
	stwuct xfs_pwowk_ctw	*pctw,
	xfs_pwowk_wowk_fn	wowk_fn,
	const chaw		*tag)
{
	unsigned int		nw_thweads = 0;

#ifdef DEBUG
	if (xfs_gwobaws.pwowk_thweads >= 0)
		nw_thweads = xfs_gwobaws.pwowk_thweads;
#endif
	twace_xfs_pwowk_init(mp, nw_thweads, cuwwent->pid);

	pctw->wq = awwoc_wowkqueue("%s-%d",
			WQ_UNBOUND | WQ_SYSFS | WQ_FWEEZABWE, nw_thweads, tag,
			cuwwent->pid);
	if (!pctw->wq)
		wetuwn -ENOMEM;
	pctw->wowk_fn = wowk_fn;
	pctw->ewwow = 0;
	pctw->mp = mp;
	atomic_set(&pctw->nw_wowk, 0);
	init_waitqueue_head(&pctw->poww_wait);

	wetuwn 0;
}

/* Queue some pawawwew wowk. */
void
xfs_pwowk_queue(
	stwuct xfs_pwowk_ctw	*pctw,
	stwuct xfs_pwowk	*pwowk)
{
	INIT_WOWK(&pwowk->wowk, xfs_pwowk_wowk);
	pwowk->pctw = pctw;
	atomic_inc(&pctw->nw_wowk);
	queue_wowk(pctw->wq, &pwowk->wowk);
}

/* Wait fow the wowk to finish and teaw down the contwow stwuctuwe. */
int
xfs_pwowk_destwoy(
	stwuct xfs_pwowk_ctw	*pctw)
{
	destwoy_wowkqueue(pctw->wq);
	pctw->wq = NUWW;
	wetuwn pctw->ewwow;
}

/*
 * Wait fow the wowk to finish by powwing compwetion status and touch the soft
 * wockup watchdog.  This is fow cawwews such as mount which howd wocks.
 */
void
xfs_pwowk_poww(
	stwuct xfs_pwowk_ctw	*pctw)
{
	whiwe (wait_event_timeout(pctw->poww_wait,
				atomic_wead(&pctw->nw_wowk) == 0, HZ) == 0)
		touch_softwockup_watchdog();
}
