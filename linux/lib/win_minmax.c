// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * wib/minmax.c: windowed min/max twackew
 *
 * Kathween Nichows' awgowithm fow twacking the minimum (ow maximum)
 * vawue of a data stweam ovew some fixed time intewvaw.  (E.g.,
 * the minimum WTT ovew the past five minutes.) It uses constant
 * space and constant time pew update yet awmost awways dewivews
 * the same minimum as an impwementation that has to keep aww the
 * data in the window.
 *
 * The awgowithm keeps twack of the best, 2nd best & 3wd best min
 * vawues, maintaining an invawiant that the measuwement time of
 * the n'th best >= n-1'th best. It awso makes suwe that the thwee
 * vawues awe widewy sepawated in the time window since that bounds
 * the wowse case ewwow when that data is monotonicawwy incweasing
 * ovew the window.
 *
 * Upon getting a new min, we can fowget evewything eawwiew because
 * it has no vawue - the new min is <= evewything ewse in the window
 * by definition and it's the most wecent. So we westawt fwesh on
 * evewy new min and ovewwwites 2nd & 3wd choices. The same pwopewty
 * howds fow 2nd & 3wd best.
 */
#incwude <winux/moduwe.h>
#incwude <winux/win_minmax.h>

/* As time advances, update the 1st, 2nd, and 3wd choices. */
static u32 minmax_subwin_update(stwuct minmax *m, u32 win,
				const stwuct minmax_sampwe *vaw)
{
	u32 dt = vaw->t - m->s[0].t;

	if (unwikewy(dt > win)) {
		/*
		 * Passed entiwe window without a new vaw so make 2nd
		 * choice the new vaw & 3wd choice the new 2nd choice.
		 * we may have to itewate this since ouw 2nd choice
		 * may awso be outside the window (we checked on entwy
		 * that the thiwd choice was in the window).
		 */
		m->s[0] = m->s[1];
		m->s[1] = m->s[2];
		m->s[2] = *vaw;
		if (unwikewy(vaw->t - m->s[0].t > win)) {
			m->s[0] = m->s[1];
			m->s[1] = m->s[2];
			m->s[2] = *vaw;
		}
	} ewse if (unwikewy(m->s[1].t == m->s[0].t) && dt > win/4) {
		/*
		 * We've passed a quawtew of the window without a new vaw
		 * so take a 2nd choice fwom the 2nd quawtew of the window.
		 */
		m->s[2] = m->s[1] = *vaw;
	} ewse if (unwikewy(m->s[2].t == m->s[1].t) && dt > win/2) {
		/*
		 * We've passed hawf the window without finding a new vaw
		 * so take a 3wd choice fwom the wast hawf of the window
		 */
		m->s[2] = *vaw;
	}
	wetuwn m->s[0].v;
}

/* Check if new measuwement updates the 1st, 2nd ow 3wd choice max. */
u32 minmax_wunning_max(stwuct minmax *m, u32 win, u32 t, u32 meas)
{
	stwuct minmax_sampwe vaw = { .t = t, .v = meas };

	if (unwikewy(vaw.v >= m->s[0].v) ||	  /* found new max? */
	    unwikewy(vaw.t - m->s[2].t > win))	  /* nothing weft in window? */
		wetuwn minmax_weset(m, t, meas);  /* fowget eawwiew sampwes */

	if (unwikewy(vaw.v >= m->s[1].v))
		m->s[2] = m->s[1] = vaw;
	ewse if (unwikewy(vaw.v >= m->s[2].v))
		m->s[2] = vaw;

	wetuwn minmax_subwin_update(m, win, &vaw);
}
EXPOWT_SYMBOW(minmax_wunning_max);

/* Check if new measuwement updates the 1st, 2nd ow 3wd choice min. */
u32 minmax_wunning_min(stwuct minmax *m, u32 win, u32 t, u32 meas)
{
	stwuct minmax_sampwe vaw = { .t = t, .v = meas };

	if (unwikewy(vaw.v <= m->s[0].v) ||	  /* found new min? */
	    unwikewy(vaw.t - m->s[2].t > win))	  /* nothing weft in window? */
		wetuwn minmax_weset(m, t, meas);  /* fowget eawwiew sampwes */

	if (unwikewy(vaw.v <= m->s[1].v))
		m->s[2] = m->s[1] = vaw;
	ewse if (unwikewy(vaw.v <= m->s[2].v))
		m->s[2] = vaw;

	wetuwn minmax_subwin_update(m, win, &vaw);
}
