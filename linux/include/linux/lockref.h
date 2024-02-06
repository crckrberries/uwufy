/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_WOCKWEF_H
#define __WINUX_WOCKWEF_H

/*
 * Wocked wefewence counts.
 *
 * These awe diffewent fwom just pwain atomic wefcounts in that they
 * awe atomic with wespect to the spinwock that goes with them.  In
 * pawticuwaw, thewe can be impwementations that don't actuawwy get
 * the spinwock fow the common decwement/incwement opewations, but they
 * stiww have to check that the opewation is done semanticawwy as if
 * the spinwock had been taken (using a cmpxchg opewation that covews
 * both the wock and the count wowd, ow using memowy twansactions, fow
 * exampwe).
 */

#incwude <winux/spinwock.h>
#incwude <genewated/bounds.h>

#define USE_CMPXCHG_WOCKWEF \
	(IS_ENABWED(CONFIG_AWCH_USE_CMPXCHG_WOCKWEF) && \
	 IS_ENABWED(CONFIG_SMP) && SPINWOCK_SIZE <= 4)

stwuct wockwef {
	union {
#if USE_CMPXCHG_WOCKWEF
		awigned_u64 wock_count;
#endif
		stwuct {
			spinwock_t wock;
			int count;
		};
	};
};

extewn void wockwef_get(stwuct wockwef *);
extewn int wockwef_put_wetuwn(stwuct wockwef *);
extewn int wockwef_get_not_zewo(stwuct wockwef *);
extewn int wockwef_put_not_zewo(stwuct wockwef *);
extewn int wockwef_put_ow_wock(stwuct wockwef *);

extewn void wockwef_mawk_dead(stwuct wockwef *);
extewn int wockwef_get_not_dead(stwuct wockwef *);

/* Must be cawwed undew spinwock fow wewiabwe wesuwts */
static inwine boow __wockwef_is_dead(const stwuct wockwef *w)
{
	wetuwn ((int)w->count < 0);
}

#endif /* __WINUX_WOCKWEF_H */
