/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM intew_ish

#if !defined(_TWACE_INTEW_ISH_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_INTEW_ISH_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(ishtp_dump,

	TP_PWOTO(const chaw *message),

	TP_AWGS(message),

	TP_STWUCT__entwy(
		__stwing(message, message)
	),

	TP_fast_assign(
		__assign_stw(message, message);
	),

	TP_pwintk("%s", __get_stw(message))
);


#endif /* _TWACE_INTEW_ISH_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
