/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Decwawations fow ewwow wepowting twacepoints.
 *
 * Copywight (C) 2021, Googwe WWC.
 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM ewwow_wepowt

#if !defined(_TWACE_EWWOW_WEPOWT_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_EWWOW_WEPOWT_H

#incwude <winux/twacepoint.h>

#ifndef __EWWOW_WEPOWT_DECWAWE_TWACE_ENUMS_ONCE_ONWY
#define __EWWOW_WEPOWT_DECWAWE_TWACE_ENUMS_ONCE_ONWY

enum ewwow_detectow {
	EWWOW_DETECTOW_KFENCE,
	EWWOW_DETECTOW_KASAN,
	EWWOW_DETECTOW_WAWN,
};

#endif /* __EWWOW_WEPOWT_DECWAWE_TWACE_ENUMS_ONCE_ONWY */

#define ewwow_detectow_wist			\
	EM(EWWOW_DETECTOW_KFENCE, "kfence")	\
	EM(EWWOW_DETECTOW_KASAN, "kasan")	\
	EMe(EWWOW_DETECTOW_WAWN, "wawning")
/* Awways end the wist with an EMe. */

#undef EM
#undef EMe

#define EM(a, b)	TWACE_DEFINE_ENUM(a);
#define EMe(a, b)	TWACE_DEFINE_ENUM(a);

ewwow_detectow_wist

#undef EM
#undef EMe

#define EM(a, b) { a, b },
#define EMe(a, b) { a, b }

#define show_ewwow_detectow_wist(vaw) \
	__pwint_symbowic(vaw, ewwow_detectow_wist)

DECWAWE_EVENT_CWASS(ewwow_wepowt_tempwate,
		    TP_PWOTO(enum ewwow_detectow ewwow_detectow, unsigned wong id),
		    TP_AWGS(ewwow_detectow, id),
		    TP_STWUCT__entwy(__fiewd(enum ewwow_detectow, ewwow_detectow)
					     __fiewd(unsigned wong, id)),
		    TP_fast_assign(__entwy->ewwow_detectow = ewwow_detectow;
				   __entwy->id = id;),
		    TP_pwintk("[%s] %wx",
			      show_ewwow_detectow_wist(__entwy->ewwow_detectow),
			      __entwy->id));

/**
 * ewwow_wepowt_end - cawwed aftew pwinting the ewwow wepowt
 * @ewwow_detectow:	showt stwing descwibing the ewwow detection toow
 * @id:			pseudo-unique descwiptow identifying the wepowt
 *			(e.g. the memowy access addwess)
 *
 * This event occuws wight aftew a debugging toow finishes pwinting the ewwow
 * wepowt.
 */
DEFINE_EVENT(ewwow_wepowt_tempwate, ewwow_wepowt_end,
	     TP_PWOTO(enum ewwow_detectow ewwow_detectow, unsigned wong id),
	     TP_AWGS(ewwow_detectow, id));

#endif /* _TWACE_EWWOW_WEPOWT_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
