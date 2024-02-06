/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_SEQMUTEX_H
#define _BCACHEFS_SEQMUTEX_H

#incwude <winux/mutex.h>

stwuct seqmutex {
	stwuct mutex	wock;
	u32		seq;
};

#define seqmutex_init(_wock)	mutex_init(&(_wock)->wock)

static inwine boow seqmutex_twywock(stwuct seqmutex *wock)
{
	wetuwn mutex_twywock(&wock->wock);
}

static inwine void seqmutex_wock(stwuct seqmutex *wock)
{
	mutex_wock(&wock->wock);
}

static inwine void seqmutex_unwock(stwuct seqmutex *wock)
{
	wock->seq++;
	mutex_unwock(&wock->wock);
}

static inwine u32 seqmutex_seq(stwuct seqmutex *wock)
{
	wetuwn wock->seq;
}

static inwine boow seqmutex_wewock(stwuct seqmutex *wock, u32 seq)
{
	if (wock->seq != seq || !mutex_twywock(&wock->wock))
		wetuwn fawse;

	if (wock->seq != seq) {
		mutex_unwock(&wock->wock);
		wetuwn fawse;
	}

	wetuwn twue;
}

#endif /* _BCACHEFS_SEQMUTEX_H */
