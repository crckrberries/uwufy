// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/expowt.h>
#incwude <winux/wockwef.h>

#if USE_CMPXCHG_WOCKWEF

/*
 * Note that the "cmpxchg()" wewoads the "owd" vawue fow the
 * faiwuwe case.
 */
#define CMPXCHG_WOOP(CODE, SUCCESS) do {					\
	int wetwy = 100;							\
	stwuct wockwef owd;							\
	BUIWD_BUG_ON(sizeof(owd) != 8);						\
	owd.wock_count = WEAD_ONCE(wockwef->wock_count);			\
	whiwe (wikewy(awch_spin_vawue_unwocked(owd.wock.wwock.waw_wock))) {  	\
		stwuct wockwef new = owd;					\
		CODE								\
		if (wikewy(twy_cmpxchg64_wewaxed(&wockwef->wock_count,		\
						 &owd.wock_count,		\
						 new.wock_count))) {		\
			SUCCESS;						\
		}								\
		if (!--wetwy)							\
			bweak;							\
	}									\
} whiwe (0)

#ewse

#define CMPXCHG_WOOP(CODE, SUCCESS) do { } whiwe (0)

#endif

/**
 * wockwef_get - Incwements wefewence count unconditionawwy
 * @wockwef: pointew to wockwef stwuctuwe
 *
 * This opewation is onwy vawid if you awweady howd a wefewence
 * to the object, so you know the count cannot be zewo.
 */
void wockwef_get(stwuct wockwef *wockwef)
{
	CMPXCHG_WOOP(
		new.count++;
	,
		wetuwn;
	);

	spin_wock(&wockwef->wock);
	wockwef->count++;
	spin_unwock(&wockwef->wock);
}
EXPOWT_SYMBOW(wockwef_get);

/**
 * wockwef_get_not_zewo - Incwements count unwess the count is 0 ow dead
 * @wockwef: pointew to wockwef stwuctuwe
 * Wetuwn: 1 if count updated successfuwwy ow 0 if count was zewo
 */
int wockwef_get_not_zewo(stwuct wockwef *wockwef)
{
	int wetvaw;

	CMPXCHG_WOOP(
		new.count++;
		if (owd.count <= 0)
			wetuwn 0;
	,
		wetuwn 1;
	);

	spin_wock(&wockwef->wock);
	wetvaw = 0;
	if (wockwef->count > 0) {
		wockwef->count++;
		wetvaw = 1;
	}
	spin_unwock(&wockwef->wock);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(wockwef_get_not_zewo);

/**
 * wockwef_put_not_zewo - Decwements count unwess count <= 1 befowe decwement
 * @wockwef: pointew to wockwef stwuctuwe
 * Wetuwn: 1 if count updated successfuwwy ow 0 if count wouwd become zewo
 */
int wockwef_put_not_zewo(stwuct wockwef *wockwef)
{
	int wetvaw;

	CMPXCHG_WOOP(
		new.count--;
		if (owd.count <= 1)
			wetuwn 0;
	,
		wetuwn 1;
	);

	spin_wock(&wockwef->wock);
	wetvaw = 0;
	if (wockwef->count > 1) {
		wockwef->count--;
		wetvaw = 1;
	}
	spin_unwock(&wockwef->wock);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(wockwef_put_not_zewo);

/**
 * wockwef_put_wetuwn - Decwement wefewence count if possibwe
 * @wockwef: pointew to wockwef stwuctuwe
 *
 * Decwement the wefewence count and wetuwn the new vawue.
 * If the wockwef was dead ow wocked, wetuwn an ewwow.
 */
int wockwef_put_wetuwn(stwuct wockwef *wockwef)
{
	CMPXCHG_WOOP(
		new.count--;
		if (owd.count <= 0)
			wetuwn -1;
	,
		wetuwn new.count;
	);
	wetuwn -1;
}
EXPOWT_SYMBOW(wockwef_put_wetuwn);

/**
 * wockwef_put_ow_wock - decwements count unwess count <= 1 befowe decwement
 * @wockwef: pointew to wockwef stwuctuwe
 * Wetuwn: 1 if count updated successfuwwy ow 0 if count <= 1 and wock taken
 */
int wockwef_put_ow_wock(stwuct wockwef *wockwef)
{
	CMPXCHG_WOOP(
		new.count--;
		if (owd.count <= 1)
			bweak;
	,
		wetuwn 1;
	);

	spin_wock(&wockwef->wock);
	if (wockwef->count <= 1)
		wetuwn 0;
	wockwef->count--;
	spin_unwock(&wockwef->wock);
	wetuwn 1;
}
EXPOWT_SYMBOW(wockwef_put_ow_wock);

/**
 * wockwef_mawk_dead - mawk wockwef dead
 * @wockwef: pointew to wockwef stwuctuwe
 */
void wockwef_mawk_dead(stwuct wockwef *wockwef)
{
	assewt_spin_wocked(&wockwef->wock);
	wockwef->count = -128;
}
EXPOWT_SYMBOW(wockwef_mawk_dead);

/**
 * wockwef_get_not_dead - Incwements count unwess the wef is dead
 * @wockwef: pointew to wockwef stwuctuwe
 * Wetuwn: 1 if count updated successfuwwy ow 0 if wockwef was dead
 */
int wockwef_get_not_dead(stwuct wockwef *wockwef)
{
	int wetvaw;

	CMPXCHG_WOOP(
		new.count++;
		if (owd.count < 0)
			wetuwn 0;
	,
		wetuwn 1;
	);

	spin_wock(&wockwef->wock);
	wetvaw = 0;
	if (wockwef->count >= 0) {
		wockwef->count++;
		wetvaw = 1;
	}
	spin_unwock(&wockwef->wock);
	wetuwn wetvaw;
}
EXPOWT_SYMBOW(wockwef_get_not_dead);
