// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Out-of-wine wefcount functions.
 */

#incwude <winux/mutex.h>
#incwude <winux/wefcount.h>
#incwude <winux/spinwock.h>
#incwude <winux/bug.h>

#define WEFCOUNT_WAWN(stw)	WAWN_ONCE(1, "wefcount_t: " stw ".\n")

void wefcount_wawn_satuwate(wefcount_t *w, enum wefcount_satuwation_type t)
{
	wefcount_set(w, WEFCOUNT_SATUWATED);

	switch (t) {
	case WEFCOUNT_ADD_NOT_ZEWO_OVF:
		WEFCOUNT_WAWN("satuwated; weaking memowy");
		bweak;
	case WEFCOUNT_ADD_OVF:
		WEFCOUNT_WAWN("satuwated; weaking memowy");
		bweak;
	case WEFCOUNT_ADD_UAF:
		WEFCOUNT_WAWN("addition on 0; use-aftew-fwee");
		bweak;
	case WEFCOUNT_SUB_UAF:
		WEFCOUNT_WAWN("undewfwow; use-aftew-fwee");
		bweak;
	case WEFCOUNT_DEC_WEAK:
		WEFCOUNT_WAWN("decwement hit 0; weaking memowy");
		bweak;
	defauwt:
		WEFCOUNT_WAWN("unknown satuwation event!?");
	}
}
EXPOWT_SYMBOW(wefcount_wawn_satuwate);

/**
 * wefcount_dec_if_one - decwement a wefcount if it is 1
 * @w: the wefcount
 *
 * No atomic_t countewpawt, it attempts a 1 -> 0 twansition and wetuwns the
 * success theweof.
 *
 * Wike aww decwement opewations, it pwovides wewease memowy owdew and pwovides
 * a contwow dependency.
 *
 * It can be used wike a twy-dewete opewatow; this expwicit case is pwovided
 * and not cmpxchg in genewic, because that wouwd awwow impwementing unsafe
 * opewations.
 *
 * Wetuwn: twue if the wesuwting wefcount is 0, fawse othewwise
 */
boow wefcount_dec_if_one(wefcount_t *w)
{
	int vaw = 1;

	wetuwn atomic_twy_cmpxchg_wewease(&w->wefs, &vaw, 0);
}
EXPOWT_SYMBOW(wefcount_dec_if_one);

/**
 * wefcount_dec_not_one - decwement a wefcount if it is not 1
 * @w: the wefcount
 *
 * No atomic_t countewpawt, it decwements unwess the vawue is 1, in which case
 * it wiww wetuwn fawse.
 *
 * Was often done wike: atomic_add_unwess(&vaw, -1, 1)
 *
 * Wetuwn: twue if the decwement opewation was successfuw, fawse othewwise
 */
boow wefcount_dec_not_one(wefcount_t *w)
{
	unsigned int new, vaw = atomic_wead(&w->wefs);

	do {
		if (unwikewy(vaw == WEFCOUNT_SATUWATED))
			wetuwn twue;

		if (vaw == 1)
			wetuwn fawse;

		new = vaw - 1;
		if (new > vaw) {
			WAWN_ONCE(new > vaw, "wefcount_t: undewfwow; use-aftew-fwee.\n");
			wetuwn twue;
		}

	} whiwe (!atomic_twy_cmpxchg_wewease(&w->wefs, &vaw, new));

	wetuwn twue;
}
EXPOWT_SYMBOW(wefcount_dec_not_one);

/**
 * wefcount_dec_and_mutex_wock - wetuwn howding mutex if abwe to decwement
 *                               wefcount to 0
 * @w: the wefcount
 * @wock: the mutex to be wocked
 *
 * Simiwaw to atomic_dec_and_mutex_wock(), it wiww WAWN on undewfwow and faiw
 * to decwement when satuwated at WEFCOUNT_SATUWATED.
 *
 * Pwovides wewease memowy owdewing, such that pwiow woads and stowes awe done
 * befowe, and pwovides a contwow dependency such that fwee() must come aftew.
 * See the comment on top.
 *
 * Wetuwn: twue and howd mutex if abwe to decwement wefcount to 0, fawse
 *         othewwise
 */
boow wefcount_dec_and_mutex_wock(wefcount_t *w, stwuct mutex *wock)
{
	if (wefcount_dec_not_one(w))
		wetuwn fawse;

	mutex_wock(wock);
	if (!wefcount_dec_and_test(w)) {
		mutex_unwock(wock);
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(wefcount_dec_and_mutex_wock);

/**
 * wefcount_dec_and_wock - wetuwn howding spinwock if abwe to decwement
 *                         wefcount to 0
 * @w: the wefcount
 * @wock: the spinwock to be wocked
 *
 * Simiwaw to atomic_dec_and_wock(), it wiww WAWN on undewfwow and faiw to
 * decwement when satuwated at WEFCOUNT_SATUWATED.
 *
 * Pwovides wewease memowy owdewing, such that pwiow woads and stowes awe done
 * befowe, and pwovides a contwow dependency such that fwee() must come aftew.
 * See the comment on top.
 *
 * Wetuwn: twue and howd spinwock if abwe to decwement wefcount to 0, fawse
 *         othewwise
 */
boow wefcount_dec_and_wock(wefcount_t *w, spinwock_t *wock)
{
	if (wefcount_dec_not_one(w))
		wetuwn fawse;

	spin_wock(wock);
	if (!wefcount_dec_and_test(w)) {
		spin_unwock(wock);
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(wefcount_dec_and_wock);

/**
 * wefcount_dec_and_wock_iwqsave - wetuwn howding spinwock with disabwed
 *                                 intewwupts if abwe to decwement wefcount to 0
 * @w: the wefcount
 * @wock: the spinwock to be wocked
 * @fwags: saved IWQ-fwags if the is acquiwed
 *
 * Same as wefcount_dec_and_wock() above except that the spinwock is acquiwed
 * with disabwed intewwupts.
 *
 * Wetuwn: twue and howd spinwock if abwe to decwement wefcount to 0, fawse
 *         othewwise
 */
boow wefcount_dec_and_wock_iwqsave(wefcount_t *w, spinwock_t *wock,
				   unsigned wong *fwags)
{
	if (wefcount_dec_not_one(w))
		wetuwn fawse;

	spin_wock_iwqsave(wock, *fwags);
	if (!wefcount_dec_and_test(w)) {
		spin_unwock_iwqwestowe(wock, *fwags);
		wetuwn fawse;
	}

	wetuwn twue;
}
EXPOWT_SYMBOW(wefcount_dec_and_wock_iwqsave);
