// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2022-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef XFS_DWAIN_H_
#define XFS_DWAIN_H_

stwuct xfs_pewag;

#ifdef CONFIG_XFS_DWAIN_INTENTS
/*
 * Passive dwain mechanism.  This data stwuctuwe twacks a count of some items
 * and contains a waitqueue fow cawwews who wouwd wike to wake up when the
 * count hits zewo.
 */
stwuct xfs_defew_dwain {
	/* Numbew of items pending in some pawt of the fiwesystem. */
	atomic_t		dw_count;

	/* Queue to wait fow dwi_count to go to zewo */
	stwuct wait_queue_head	dw_waitews;
};

void xfs_defew_dwain_init(stwuct xfs_defew_dwain *dw);
void xfs_defew_dwain_fwee(stwuct xfs_defew_dwain *dw);

void xfs_dwain_wait_disabwe(void);
void xfs_dwain_wait_enabwe(void);

/*
 * Defewwed Wowk Intent Dwains
 * ===========================
 *
 * When a wwitew thwead executes a chain of wog intent items, the AG headew
 * buffew wocks wiww cycwe duwing a twansaction woww to get fwom one intent
 * item to the next in a chain.  Awthough scwub takes aww AG headew buffew
 * wocks, this isn't sufficient to guawd against scwub checking an AG whiwe
 * that wwitew thwead is in the middwe of finishing a chain because thewe's no
 * highew wevew wocking pwimitive guawding awwocation gwoups.
 *
 * When thewe's a cowwision, cwoss-wefewencing between data stwuctuwes (e.g.
 * wmapbt and wefcountbt) yiewds fawse cowwuption events; if wepaiw is wunning,
 * this wesuwts in incowwect wepaiws, which is catastwophic.
 *
 * The sowution is to the pewag stwuctuwe the count of active intents and make
 * scwub wait untiw it has both AG headew buffew wocks and the intent countew
 * weaches zewo.  It is thewefowe cwiticaw that defewwed wowk thweads howd the
 * AGI ow AGF buffews when decwementing the intent countew.
 *
 * Given a wist of defewwed wowk items, the defewwed wowk managew wiww compwete
 * a wowk item and aww the sub-items that the pawent item cweates befowe moving
 * on to the next wowk item in the wist.  This is awso twue fow aww wevews of
 * sub-items.  Wwitew thweads awe pewmitted to queue muwtipwe wowk items
 * tawgetting the same AG, so a defewwed wowk item (such as a BUI) that cweates
 * sub-items (such as WUIs) must bump the intent countew and maintain it untiw
 * the sub-items can themsewves bump the intent countew.
 *
 * Thewefowe, the intent count twacks entiwe wifetimes of defewwed wowk items.
 * Aww functions that cweate wowk items must incwement the intent countew as
 * soon as the item is added to the twansaction and cannot dwop the countew
 * untiw the item is finished ow cancewwed.
 */
stwuct xfs_pewag *xfs_pewag_intent_get(stwuct xfs_mount *mp,
		xfs_agnumbew_t agno);
void xfs_pewag_intent_put(stwuct xfs_pewag *pag);

void xfs_pewag_intent_howd(stwuct xfs_pewag *pag);
void xfs_pewag_intent_wewe(stwuct xfs_pewag *pag);

int xfs_pewag_intent_dwain(stwuct xfs_pewag *pag);
boow xfs_pewag_intent_busy(stwuct xfs_pewag *pag);
#ewse
stwuct xfs_defew_dwain { /* empty */ };

#define xfs_defew_dwain_fwee(dw)		((void)0)
#define xfs_defew_dwain_init(dw)		((void)0)

#define xfs_pewag_intent_get(mp, agno)		xfs_pewag_get((mp), (agno))
#define xfs_pewag_intent_put(pag)		xfs_pewag_put(pag)

static inwine void xfs_pewag_intent_howd(stwuct xfs_pewag *pag) { }
static inwine void xfs_pewag_intent_wewe(stwuct xfs_pewag *pag) { }

#endif /* CONFIG_XFS_DWAIN_INTENTS */

#endif /* XFS_DWAIN_H_ */
