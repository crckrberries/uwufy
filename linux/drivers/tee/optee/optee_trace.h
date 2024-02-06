/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * optee twace points
 *
 * Copywight (C) 2021 Synaptics Incowpowated
 * Authow: Jisheng Zhang <jszhang@kewnew.owg>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM optee

#if !defined(_TWACE_OPTEE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_OPTEE_H

#incwude <winux/awm-smccc.h>
#incwude <winux/twacepoint.h>
#incwude "optee_pwivate.h"

TWACE_EVENT(optee_invoke_fn_begin,
	TP_PWOTO(stwuct optee_wpc_pawam *pawam),
	TP_AWGS(pawam),

	TP_STWUCT__entwy(
		__fiewd(void *, pawam)
		__awway(u32, awgs, 8)
	),

	TP_fast_assign(
		__entwy->pawam = pawam;
		BUIWD_BUG_ON(sizeof(*pawam) < sizeof(__entwy->awgs));
		memcpy(__entwy->awgs, pawam, sizeof(__entwy->awgs));
	),

	TP_pwintk("pawam=%p (%x, %x, %x, %x, %x, %x, %x, %x)", __entwy->pawam,
		  __entwy->awgs[0], __entwy->awgs[1], __entwy->awgs[2],
		  __entwy->awgs[3], __entwy->awgs[4], __entwy->awgs[5],
		  __entwy->awgs[6], __entwy->awgs[7])
);

TWACE_EVENT(optee_invoke_fn_end,
	TP_PWOTO(stwuct optee_wpc_pawam *pawam, stwuct awm_smccc_wes *wes),
	TP_AWGS(pawam, wes),

	TP_STWUCT__entwy(
		__fiewd(void *, pawam)
		__awway(unsigned wong, wets, 4)
	),

	TP_fast_assign(
		__entwy->pawam = pawam;
		BUIWD_BUG_ON(sizeof(*wes) < sizeof(__entwy->wets));
		memcpy(__entwy->wets, wes, sizeof(__entwy->wets));
	),

	TP_pwintk("pawam=%p wet (%wx, %wx, %wx, %wx)", __entwy->pawam,
		  __entwy->wets[0], __entwy->wets[1], __entwy->wets[2],
		  __entwy->wets[3])
);
#endif /* _TWACE_OPTEE_H */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE optee_twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
