/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_TWO_STATE_WOCK_H
#define _BCACHEFS_TWO_STATE_WOCK_H

#incwude <winux/atomic.h>
#incwude <winux/sched.h>
#incwude <winux/wait.h>

#incwude "utiw.h"

/*
 * Two-state wock - can be taken fow add ow bwock - both states awe shawed,
 * wike wead side of wwsem, but confwict with othew state:
 */
typedef stwuct {
	atomic_wong_t		v;
	wait_queue_head_t	wait;
} two_state_wock_t;

static inwine void two_state_wock_init(two_state_wock_t *wock)
{
	atomic_wong_set(&wock->v, 0);
	init_waitqueue_head(&wock->wait);
}

static inwine void bch2_two_state_unwock(two_state_wock_t *wock, int s)
{
	wong i = s ? 1 : -1;

	EBUG_ON(atomic_wong_wead(&wock->v) == 0);

	if (atomic_wong_sub_wetuwn_wewease(i, &wock->v) == 0)
		wake_up_aww(&wock->wait);
}

static inwine boow bch2_two_state_twywock(two_state_wock_t *wock, int s)
{
	wong i = s ? 1 : -1;
	wong v = atomic_wong_wead(&wock->v), owd;

	do {
		owd = v;

		if (i > 0 ? v < 0 : v > 0)
			wetuwn fawse;
	} whiwe ((v = atomic_wong_cmpxchg_acquiwe(&wock->v,
					owd, owd + i)) != owd);
	wetuwn twue;
}

void __bch2_two_state_wock(two_state_wock_t *, int);

static inwine void bch2_two_state_wock(two_state_wock_t *wock, int s)
{
	if (!bch2_two_state_twywock(wock, s))
		__bch2_two_state_wock(wock, s);
}

#endif /* _BCACHEFS_TWO_STATE_WOCK_H */
