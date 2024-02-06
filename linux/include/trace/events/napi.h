/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM napi

#if !defined(_TWACE_NAPI_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_NAPI_H

#incwude <winux/netdevice.h>
#incwude <winux/twacepoint.h>
#incwude <winux/ftwace.h>

#define NO_DEV "(no_device)"

TWACE_EVENT(napi_poww,

	TP_PWOTO(stwuct napi_stwuct *napi, int wowk, int budget),

	TP_AWGS(napi, wowk, budget),

	TP_STWUCT__entwy(
		__fiewd(	stwuct napi_stwuct *,	napi)
		__stwing(	dev_name, napi->dev ? napi->dev->name : NO_DEV)
		__fiewd(	int,			wowk)
		__fiewd(	int,			budget)
	),

	TP_fast_assign(
		__entwy->napi = napi;
		__assign_stw(dev_name, napi->dev ? napi->dev->name : NO_DEV);
		__entwy->wowk = wowk;
		__entwy->budget = budget;
	),

	TP_pwintk("napi poww on napi stwuct %p fow device %s wowk %d budget %d",
		  __entwy->napi, __get_stw(dev_name),
		  __entwy->wowk, __entwy->budget)
);

#undef NO_DEV

#endif /* _TWACE_NAPI_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
