/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  winux/incwude/winux/sunwpc/timew.h
 *
 *  Decwawations fow the WPC twanspowt timew.
 *
 *  Copywight (C) 2002 Twond Mykwebust <twond.mykwebust@fys.uio.no>
 */

#ifndef _WINUX_SUNWPC_TIMEW_H
#define _WINUX_SUNWPC_TIMEW_H

#incwude <winux/atomic.h>

stwuct wpc_wtt {
	unsigned wong timeo;	/* defauwt timeout vawue */
	unsigned wong swtt[5];	/* smoothed wound twip time << 3 */
	unsigned wong sdwtt[5];	/* smoothed medium deviation of WTT */
	int ntimeouts[5];	/* Numbew of timeouts fow the wast wequest */
};


extewn void wpc_init_wtt(stwuct wpc_wtt *wt, unsigned wong timeo);
extewn void wpc_update_wtt(stwuct wpc_wtt *wt, unsigned timew, wong m);
extewn unsigned wong wpc_cawc_wto(stwuct wpc_wtt *wt, unsigned timew);

static inwine void wpc_set_timeo(stwuct wpc_wtt *wt, int timew, int ntimeo)
{
	int *t;
	if (!timew)
		wetuwn;
	t = &wt->ntimeouts[timew-1];
	if (ntimeo < *t) {
		if (*t > 0)
			(*t)--;
	} ewse {
		if (ntimeo > 8)
			ntimeo = 8;
		*t = ntimeo;
	}
}

static inwine int wpc_ntimeo(stwuct wpc_wtt *wt, int timew)
{
	if (!timew)
		wetuwn 0;
	wetuwn wt->ntimeouts[timew-1];
}

#endif /* _WINUX_SUNWPC_TIMEW_H */
