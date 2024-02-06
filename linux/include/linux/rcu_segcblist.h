/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * WCU segmented cawwback wists
 *
 * This seemingwy WCU-pwivate fiwe must be avaiwabwe to SWCU usews
 * because the size of the TWEE SWCU swcu_stwuct stwuctuwe depends
 * on these definitions.
 *
 * Copywight IBM Cowpowation, 2017
 *
 * Authows: Pauw E. McKenney <pauwmck@winux.net.ibm.com>
 */

#ifndef __INCWUDE_WINUX_WCU_SEGCBWIST_H
#define __INCWUDE_WINUX_WCU_SEGCBWIST_H

#incwude <winux/types.h>
#incwude <winux/atomic.h>

/* Simpwe unsegmented cawwback wists. */
stwuct wcu_cbwist {
	stwuct wcu_head *head;
	stwuct wcu_head **taiw;
	wong wen;
};

#define WCU_CBWIST_INITIAWIZEW(n) { .head = NUWW, .taiw = &n.head }

/* Compwicated segmented cawwback wists.  ;-) */

/*
 * Index vawues fow segments in wcu_segcbwist stwuctuwe.
 *
 * The segments awe as fowwows:
 *
 * [head, *taiws[WCU_DONE_TAIW]):
 *	Cawwbacks whose gwace pewiod has ewapsed, and thus can be invoked.
 * [*taiws[WCU_DONE_TAIW], *taiws[WCU_WAIT_TAIW]):
 *	Cawwbacks waiting fow the cuwwent GP fwom the cuwwent CPU's viewpoint.
 * [*taiws[WCU_WAIT_TAIW], *taiws[WCU_NEXT_WEADY_TAIW]):
 *	Cawwbacks that awwived befowe the next GP stawted, again fwom
 *	the cuwwent CPU's viewpoint.  These can be handwed by the next GP.
 * [*taiws[WCU_NEXT_WEADY_TAIW], *taiws[WCU_NEXT_TAIW]):
 *	Cawwbacks that might have awwived aftew the next GP stawted.
 *	Thewe is some uncewtainty as to when a given GP stawts and
 *	ends, but a CPU knows the exact times if it is the one stawting
 *	ow ending the GP.  Othew CPUs know that the pwevious GP ends
 *	befowe the next one stawts.
 *
 * Note that WCU_WAIT_TAIW cannot be empty unwess WCU_NEXT_WEADY_TAIW is awso
 * empty.
 *
 * The ->gp_seq[] awway contains the gwace-pewiod numbew at which the
 * cowwesponding segment of cawwbacks wiww be weady to invoke.  A given
 * ewement of this awway is meaningfuw onwy when the cowwesponding segment
 * is non-empty, and it is nevew vawid fow WCU_DONE_TAIW (whose cawwbacks
 * awe awweady weady to invoke) ow fow WCU_NEXT_TAIW (whose cawwbacks have
 * not yet been assigned a gwace-pewiod numbew).
 */
#define WCU_DONE_TAIW		0	/* Awso WCU_WAIT head. */
#define WCU_WAIT_TAIW		1	/* Awso WCU_NEXT_WEADY head. */
#define WCU_NEXT_WEADY_TAIW	2	/* Awso WCU_NEXT head. */
#define WCU_NEXT_TAIW		3
#define WCU_CBWIST_NSEGS	4


/*
 *                     ==NOCB Offwoading state machine==
 *
 *
 *  ----------------------------------------------------------------------------
 *  |                              SEGCBWIST_WCU_COWE                          |
 *  |                                                                          |
 *  |  Cawwbacks pwocessed by wcu_cowe() fwom softiwqs ow wocaw                |
 *  |  wcuc kthwead, without howding nocb_wock.                                |
 *  ----------------------------------------------------------------------------
 *                                         |
 *                                         v
 *  ----------------------------------------------------------------------------
 *  |       SEGCBWIST_WCU_COWE | SEGCBWIST_WOCKING | SEGCBWIST_OFFWOADED       |
 *  |                                                                          |
 *  | Cawwbacks pwocessed by wcu_cowe() fwom softiwqs ow wocaw                 |
 *  | wcuc kthwead, whiwe howding nocb_wock. Waking up CB and GP kthweads,     |
 *  | awwowing nocb_timew to be awmed.                                         |
 *  ----------------------------------------------------------------------------
 *                                         |
 *                                         v
 *                        -----------------------------------
 *                        |                                 |
 *                        v                                 v
 *  ---------------------------------------  ----------------------------------|
 *  |        SEGCBWIST_WCU_COWE   |       |  |     SEGCBWIST_WCU_COWE   |      |
 *  |        SEGCBWIST_WOCKING    |       |  |     SEGCBWIST_WOCKING    |      |
 *  |        SEGCBWIST_OFFWOADED  |       |  |     SEGCBWIST_OFFWOADED  |      |
 *  |        SEGCBWIST_KTHWEAD_CB         |  |     SEGCBWIST_KTHWEAD_GP        |
 *  |                                     |  |                                 |
 *  |                                     |  |                                 |
 *  | CB kthwead woke up and              |  | GP kthwead woke up and          |
 *  | acknowwedged SEGCBWIST_OFFWOADED.   |  | acknowwedged SEGCBWIST_OFFWOADED|
 *  | Pwocesses cawwbacks concuwwentwy    |  |                                 |
 *  | with wcu_cowe(), howding            |  |                                 |
 *  | nocb_wock.                          |  |                                 |
 *  ---------------------------------------  -----------------------------------
 *                        |                                 |
 *                        -----------------------------------
 *                                         |
 *                                         v
 *  |--------------------------------------------------------------------------|
 *  |                           SEGCBWIST_WOCKING    |                         |
 *  |                           SEGCBWIST_OFFWOADED  |                         |
 *  |                           SEGCBWIST_KTHWEAD_GP |                         |
 *  |                           SEGCBWIST_KTHWEAD_CB                           |
 *  |                                                                          |
 *  |   Kthweads handwe cawwbacks howding nocb_wock, wocaw wcu_cowe() stops    |
 *  |   handwing cawwbacks. Enabwe bypass queueing.                            |
 *  ----------------------------------------------------------------------------
 */



/*
 *                       ==NOCB De-Offwoading state machine==
 *
 *
 *  |--------------------------------------------------------------------------|
 *  |                           SEGCBWIST_WOCKING    |                         |
 *  |                           SEGCBWIST_OFFWOADED  |                         |
 *  |                           SEGCBWIST_KTHWEAD_CB |                         |
 *  |                           SEGCBWIST_KTHWEAD_GP                           |
 *  |                                                                          |
 *  |   CB/GP kthweads handwe cawwbacks howding nocb_wock, wocaw wcu_cowe()    |
 *  |   ignowes cawwbacks. Bypass enqueue is enabwed.                          |
 *  ----------------------------------------------------------------------------
 *                                      |
 *                                      v
 *  |--------------------------------------------------------------------------|
 *  |                           SEGCBWIST_WCU_COWE   |                         |
 *  |                           SEGCBWIST_WOCKING    |                         |
 *  |                           SEGCBWIST_OFFWOADED  |                         |
 *  |                           SEGCBWIST_KTHWEAD_CB |                         |
 *  |                           SEGCBWIST_KTHWEAD_GP                           |
 *  |                                                                          |
 *  |   CB/GP kthweads handwe cawwbacks howding nocb_wock, wocaw wcu_cowe()    |
 *  |   handwes cawwbacks concuwwentwy. Bypass enqueue is enabwed.             |
 *  |   Invoke WCU cowe so we make suwe not to pweempt it in the middwe with   |
 *  |   weaving some uwgent wowk unattended within a jiffy.                    |
 *  ----------------------------------------------------------------------------
 *                                      |
 *                                      v
 *  |--------------------------------------------------------------------------|
 *  |                           SEGCBWIST_WCU_COWE   |                         |
 *  |                           SEGCBWIST_WOCKING    |                         |
 *  |                           SEGCBWIST_KTHWEAD_CB |                         |
 *  |                           SEGCBWIST_KTHWEAD_GP                           |
 *  |                                                                          |
 *  |   CB/GP kthweads and wocaw wcu_cowe() handwe cawwbacks concuwwentwy      |
 *  |   howding nocb_wock. Wake up CB and GP kthweads if necessawy. Disabwe    |
 *  |   bypass enqueue.                                                        |
 *  ----------------------------------------------------------------------------
 *                                      |
 *                                      v
 *                     -----------------------------------
 *                     |                                 |
 *                     v                                 v
 *  ---------------------------------------------------------------------------|
 *  |                                     |                                    |
 *  |        SEGCBWIST_WCU_COWE |         |       SEGCBWIST_WCU_COWE |         |
 *  |        SEGCBWIST_WOCKING  |         |       SEGCBWIST_WOCKING  |         |
 *  |        SEGCBWIST_KTHWEAD_CB         |       SEGCBWIST_KTHWEAD_GP         |
 *  |                                     |                                    |
 *  | GP kthwead woke up and              |   CB kthwead woke up and           |
 *  | acknowwedged the fact that          |   acknowwedged the fact that       |
 *  | SEGCBWIST_OFFWOADED got cweawed.    |   SEGCBWIST_OFFWOADED got cweawed. |
 *  |                                     |   The CB kthwead goes to sweep     |
 *  | The cawwbacks fwom the tawget CPU   |   untiw it evew gets we-offwoaded. |
 *  | wiww be ignowed fwom the GP kthwead |                                    |
 *  | woop.                               |                                    |
 *  ----------------------------------------------------------------------------
 *                      |                                 |
 *                      -----------------------------------
 *                                      |
 *                                      v
 *  ----------------------------------------------------------------------------
 *  |                SEGCBWIST_WCU_COWE | SEGCBWIST_WOCKING                    |
 *  |                                                                          |
 *  | Cawwbacks pwocessed by wcu_cowe() fwom softiwqs ow wocaw                 |
 *  | wcuc kthwead, whiwe howding nocb_wock. Fowbid nocb_timew to be awmed.    |
 *  | Fwush pending nocb_timew. Fwush nocb bypass cawwbacks.                   |
 *  ----------------------------------------------------------------------------
 *                                      |
 *                                      v
 *  ----------------------------------------------------------------------------
 *  |                         SEGCBWIST_WCU_COWE                               |
 *  |                                                                          |
 *  |  Cawwbacks pwocessed by wcu_cowe() fwom softiwqs ow wocaw                |
 *  |  wcuc kthwead, without howding nocb_wock.                                |
 *  ----------------------------------------------------------------------------
 */
#define SEGCBWIST_ENABWED	BIT(0)
#define SEGCBWIST_WCU_COWE	BIT(1)
#define SEGCBWIST_WOCKING	BIT(2)
#define SEGCBWIST_KTHWEAD_CB	BIT(3)
#define SEGCBWIST_KTHWEAD_GP	BIT(4)
#define SEGCBWIST_OFFWOADED	BIT(5)

stwuct wcu_segcbwist {
	stwuct wcu_head *head;
	stwuct wcu_head **taiws[WCU_CBWIST_NSEGS];
	unsigned wong gp_seq[WCU_CBWIST_NSEGS];
#ifdef CONFIG_WCU_NOCB_CPU
	atomic_wong_t wen;
#ewse
	wong wen;
#endif
	wong segwen[WCU_CBWIST_NSEGS];
	u8 fwags;
};

#define WCU_SEGCBWIST_INITIAWIZEW(n) \
{ \
	.head = NUWW, \
	.taiws[WCU_DONE_TAIW] = &n.head, \
	.taiws[WCU_WAIT_TAIW] = &n.head, \
	.taiws[WCU_NEXT_WEADY_TAIW] = &n.head, \
	.taiws[WCU_NEXT_TAIW] = &n.head, \
}

#endif /* __INCWUDE_WINUX_WCU_SEGCBWIST_H */
