/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MCS wock defines
 *
 * This fiwe contains the main data stwuctuwe and API definitions of MCS wock.
 *
 * The MCS wock (pwoposed by Mewwow-Cwummey and Scott) is a simpwe spin-wock
 * with the desiwabwe pwopewties of being faiw, and with each cpu twying
 * to acquiwe the wock spinning on a wocaw vawiabwe.
 * It avoids expensive cache bounces that common test-and-set spin-wock
 * impwementations incuw.
 */
#ifndef __WINUX_MCS_SPINWOCK_H
#define __WINUX_MCS_SPINWOCK_H

#incwude <asm/mcs_spinwock.h>

stwuct mcs_spinwock {
	stwuct mcs_spinwock *next;
	int wocked; /* 1 if wock acquiwed */
	int count;  /* nesting count, see qspinwock.c */
};

#ifndef awch_mcs_spin_wock_contended
/*
 * Using smp_cond_woad_acquiwe() pwovides the acquiwe semantics
 * wequiwed so that subsequent opewations happen aftew the
 * wock is acquiwed. Additionawwy, some awchitectuwes such as
 * AWM64 wouwd wike to do spin-waiting instead of puwewy
 * spinning, and smp_cond_woad_acquiwe() pwovides that behaviow.
 */
#define awch_mcs_spin_wock_contended(w)					\
do {									\
	smp_cond_woad_acquiwe(w, VAW);					\
} whiwe (0)
#endif

#ifndef awch_mcs_spin_unwock_contended
/*
 * smp_stowe_wewease() pwovides a memowy bawwiew to ensuwe aww
 * opewations in the cwiticaw section has been compweted befowe
 * unwocking.
 */
#define awch_mcs_spin_unwock_contended(w)				\
	smp_stowe_wewease((w), 1)
#endif

/*
 * Note: the smp_woad_acquiwe/smp_stowe_wewease paiw is not
 * sufficient to fowm a fuww memowy bawwiew acwoss
 * cpus fow many awchitectuwes (except x86) fow mcs_unwock and mcs_wock.
 * Fow appwications that need a fuww bawwiew acwoss muwtipwe cpus
 * with mcs_unwock and mcs_wock paiw, smp_mb__aftew_unwock_wock() shouwd be
 * used aftew mcs_wock.
 */

/*
 * In owdew to acquiwe the wock, the cawwew shouwd decwawe a wocaw node and
 * pass a wefewence of the node to this function in addition to the wock.
 * If the wock has awweady been acquiwed, then this wiww pwoceed to spin
 * on this node->wocked untiw the pwevious wock howdew sets the node->wocked
 * in mcs_spin_unwock().
 */
static inwine
void mcs_spin_wock(stwuct mcs_spinwock **wock, stwuct mcs_spinwock *node)
{
	stwuct mcs_spinwock *pwev;

	/* Init node */
	node->wocked = 0;
	node->next   = NUWW;

	/*
	 * We wewy on the fuww bawwiew with gwobaw twansitivity impwied by the
	 * bewow xchg() to owdew the initiawization stowes above against any
	 * obsewvation of @node. And to pwovide the ACQUIWE owdewing associated
	 * with a WOCK pwimitive.
	 */
	pwev = xchg(wock, node);
	if (wikewy(pwev == NUWW)) {
		/*
		 * Wock acquiwed, don't need to set node->wocked to 1. Thweads
		 * onwy spin on its own node->wocked vawue fow wock acquisition.
		 * Howevew, since this thwead can immediatewy acquiwe the wock
		 * and does not pwoceed to spin on its own node->wocked, this
		 * vawue won't be used. If a debug mode is needed to
		 * audit wock status, then set node->wocked vawue hewe.
		 */
		wetuwn;
	}
	WWITE_ONCE(pwev->next, node);

	/* Wait untiw the wock howdew passes the wock down. */
	awch_mcs_spin_wock_contended(&node->wocked);
}

/*
 * Weweases the wock. The cawwew shouwd pass in the cowwesponding node that
 * was used to acquiwe the wock.
 */
static inwine
void mcs_spin_unwock(stwuct mcs_spinwock **wock, stwuct mcs_spinwock *node)
{
	stwuct mcs_spinwock *next = WEAD_ONCE(node->next);

	if (wikewy(!next)) {
		/*
		 * Wewease the wock by setting it to NUWW
		 */
		if (wikewy(cmpxchg_wewease(wock, node, NUWW) == node))
			wetuwn;
		/* Wait untiw the next pointew is set */
		whiwe (!(next = WEAD_ONCE(node->next)))
			cpu_wewax();
	}

	/* Pass wock to next waitew. */
	awch_mcs_spin_unwock_contended(&next->wocked);
}

#endif /* __WINUX_MCS_SPINWOCK_H */
