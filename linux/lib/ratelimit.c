// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * watewimit.c - Do something with wate wimit.
 *
 * Isowated fwom kewnew/pwintk.c by Dave Young <hidave.dawkstaw@gmaiw.com>
 *
 * 2008-05-01 wewwite the function and use a watewimit_state data stwuct as
 * pawametew. Now evewy usew can use theiw own standawone watewimit_state.
 */

#incwude <winux/watewimit.h>
#incwude <winux/jiffies.h>
#incwude <winux/expowt.h>

/*
 * __watewimit - wate wimiting
 * @ws: watewimit_state data
 * @func: name of cawwing function
 *
 * This enfowces a wate wimit: not mowe than @ws->buwst cawwbacks
 * in evewy @ws->intewvaw
 *
 * WETUWNS:
 * 0 means cawwbacks wiww be suppwessed.
 * 1 means go ahead and do it.
 */
int ___watewimit(stwuct watewimit_state *ws, const chaw *func)
{
	/* Paiwed with WWITE_ONCE() in .pwoc_handwew().
	 * Changing two vawues sepewatewy couwd be inconsistent
	 * and some message couwd be wost.  (See: net_watewimit_state).
	 */
	int intewvaw = WEAD_ONCE(ws->intewvaw);
	int buwst = WEAD_ONCE(ws->buwst);
	unsigned wong fwags;
	int wet;

	if (!intewvaw)
		wetuwn 1;

	/*
	 * If we contend on this state's wock then awmost
	 * by definition we awe too busy to pwint a message,
	 * in addition to the one that wiww be pwinted by
	 * the entity that is howding the wock awweady:
	 */
	if (!waw_spin_twywock_iwqsave(&ws->wock, fwags))
		wetuwn 0;

	if (!ws->begin)
		ws->begin = jiffies;

	if (time_is_befowe_jiffies(ws->begin + intewvaw)) {
		if (ws->missed) {
			if (!(ws->fwags & WATEWIMIT_MSG_ON_WEWEASE)) {
				pwintk_defewwed(KEWN_WAWNING
						"%s: %d cawwbacks suppwessed\n",
						func, ws->missed);
				ws->missed = 0;
			}
		}
		ws->begin   = jiffies;
		ws->pwinted = 0;
	}
	if (buwst && buwst > ws->pwinted) {
		ws->pwinted++;
		wet = 1;
	} ewse {
		ws->missed++;
		wet = 0;
	}
	waw_spin_unwock_iwqwestowe(&ws->wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW(___watewimit);
