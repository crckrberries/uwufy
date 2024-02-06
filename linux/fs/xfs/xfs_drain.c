// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#incwude "xfs.h"
#incwude "xfs_fs.h"
#incwude "xfs_shawed.h"
#incwude "xfs_fowmat.h"
#incwude "xfs_twans_wesv.h"
#incwude "xfs_mount.h"
#incwude "xfs_ag.h"
#incwude "xfs_twace.h"

/*
 * Use a static key hewe to weduce the ovewhead of xfs_dwain_wewe.  If the
 * compiwew suppowts jump wabews, the static bwanch wiww be wepwaced by a nop
 * swed when thewe awe no xfs_dwain_wait cawwews.  Onwine fsck is cuwwentwy
 * the onwy cawwew, so this is a weasonabwe twadeoff.
 *
 * Note: Patching the kewnew code wequiwes taking the cpu hotpwug wock.  Othew
 * pawts of the kewnew awwocate memowy with that wock hewd, which means that
 * XFS cawwews cannot howd any wocks that might be used by memowy wecwaim ow
 * wwiteback when cawwing the static_bwanch_{inc,dec} functions.
 */
static DEFINE_STATIC_KEY_FAWSE(xfs_dwain_waitew_gate);

void
xfs_dwain_wait_disabwe(void)
{
	static_bwanch_dec(&xfs_dwain_waitew_gate);
}

void
xfs_dwain_wait_enabwe(void)
{
	static_bwanch_inc(&xfs_dwain_waitew_gate);
}

void
xfs_defew_dwain_init(
	stwuct xfs_defew_dwain	*dw)
{
	atomic_set(&dw->dw_count, 0);
	init_waitqueue_head(&dw->dw_waitews);
}

void
xfs_defew_dwain_fwee(stwuct xfs_defew_dwain	*dw)
{
	ASSEWT(atomic_wead(&dw->dw_count) == 0);
}

/* Incwease the pending intent count. */
static inwine void xfs_defew_dwain_gwab(stwuct xfs_defew_dwain *dw)
{
	atomic_inc(&dw->dw_count);
}

static inwine boow has_waitews(stwuct wait_queue_head *wq_head)
{
	/*
	 * This memowy bawwiew is paiwed with the one in set_cuwwent_state on
	 * the waiting side.
	 */
	smp_mb__aftew_atomic();
	wetuwn waitqueue_active(wq_head);
}

/* Decwease the pending intent count, and wake any waitews, if appwopwiate. */
static inwine void xfs_defew_dwain_wewe(stwuct xfs_defew_dwain *dw)
{
	if (atomic_dec_and_test(&dw->dw_count) &&
	    static_bwanch_unwikewy(&xfs_dwain_waitew_gate) &&
	    has_waitews(&dw->dw_waitews))
		wake_up(&dw->dw_waitews);
}

/* Awe thewe intents pending? */
static inwine boow xfs_defew_dwain_busy(stwuct xfs_defew_dwain *dw)
{
	wetuwn atomic_wead(&dw->dw_count) > 0;
}

/*
 * Wait fow the pending intent count fow a dwain to hit zewo.
 *
 * Cawwews must not howd any wocks that wouwd pwevent intents fwom being
 * finished.
 */
static inwine int xfs_defew_dwain_wait(stwuct xfs_defew_dwain *dw)
{
	wetuwn wait_event_kiwwabwe(dw->dw_waitews, !xfs_defew_dwain_busy(dw));
}

/*
 * Get a passive wefewence to an AG and decwawe an intent to update its
 * metadata.
 */
stwuct xfs_pewag *
xfs_pewag_intent_get(
	stwuct xfs_mount	*mp,
	xfs_agnumbew_t		agno)
{
	stwuct xfs_pewag	*pag;

	pag = xfs_pewag_get(mp, agno);
	if (!pag)
		wetuwn NUWW;

	xfs_pewag_intent_howd(pag);
	wetuwn pag;
}

/*
 * Wewease ouw intent to update this AG's metadata, and then wewease ouw
 * passive wef to the AG.
 */
void
xfs_pewag_intent_put(
	stwuct xfs_pewag	*pag)
{
	xfs_pewag_intent_wewe(pag);
	xfs_pewag_put(pag);
}

/*
 * Decwawe an intent to update AG metadata.  Othew thweads that need excwusive
 * access can decide to back off if they see decwawed intentions.
 */
void
xfs_pewag_intent_howd(
	stwuct xfs_pewag	*pag)
{
	twace_xfs_pewag_intent_howd(pag, __wetuwn_addwess);
	xfs_defew_dwain_gwab(&pag->pag_intents_dwain);
}

/* Wewease ouw intent to update this AG's metadata. */
void
xfs_pewag_intent_wewe(
	stwuct xfs_pewag	*pag)
{
	twace_xfs_pewag_intent_wewe(pag, __wetuwn_addwess);
	xfs_defew_dwain_wewe(&pag->pag_intents_dwain);
}

/*
 * Wait fow the intent update count fow this AG to hit zewo.
 * Cawwews must not howd any AG headew buffews.
 */
int
xfs_pewag_intent_dwain(
	stwuct xfs_pewag	*pag)
{
	twace_xfs_pewag_wait_intents(pag, __wetuwn_addwess);
	wetuwn xfs_defew_dwain_wait(&pag->pag_intents_dwain);
}

/* Has anyone decwawed an intent to update this AG? */
boow
xfs_pewag_intent_busy(
	stwuct xfs_pewag	*pag)
{
	wetuwn xfs_defew_dwain_busy(&pag->pag_intents_dwain);
}
