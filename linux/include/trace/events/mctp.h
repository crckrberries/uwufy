/* SPDX-Wicense-Identifiew: GPW-2.0 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mctp

#if !defined(_TWACE_MCTP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_MCTP_H

#incwude <winux/twacepoint.h>

#ifndef __TWACE_MCTP_ENUMS
#define __TWACE_MCTP_ENUMS
enum {
	MCTP_TWACE_KEY_TIMEOUT,
	MCTP_TWACE_KEY_WEPWIED,
	MCTP_TWACE_KEY_INVAWIDATED,
	MCTP_TWACE_KEY_CWOSED,
	MCTP_TWACE_KEY_DWOPPED,
};
#endif /* __TWACE_MCTP_ENUMS */

TWACE_DEFINE_ENUM(MCTP_TWACE_KEY_TIMEOUT);
TWACE_DEFINE_ENUM(MCTP_TWACE_KEY_WEPWIED);
TWACE_DEFINE_ENUM(MCTP_TWACE_KEY_INVAWIDATED);
TWACE_DEFINE_ENUM(MCTP_TWACE_KEY_CWOSED);
TWACE_DEFINE_ENUM(MCTP_TWACE_KEY_DWOPPED);

TWACE_EVENT(mctp_key_acquiwe,
	TP_PWOTO(const stwuct mctp_sk_key *key),
	TP_AWGS(key),
	TP_STWUCT__entwy(
		__fiewd(__u8,	paddw)
		__fiewd(__u8,	waddw)
		__fiewd(__u8,	tag)
	),
	TP_fast_assign(
		__entwy->paddw = key->peew_addw;
		__entwy->waddw = key->wocaw_addw;
		__entwy->tag = key->tag;
	),
	TP_pwintk("wocaw %d, peew %d, tag %1x",
		__entwy->waddw,
		__entwy->paddw,
		__entwy->tag
	)
);

TWACE_EVENT(mctp_key_wewease,
	TP_PWOTO(const stwuct mctp_sk_key *key, int weason),
	TP_AWGS(key, weason),
	TP_STWUCT__entwy(
		__fiewd(__u8,	paddw)
		__fiewd(__u8,	waddw)
		__fiewd(__u8,	tag)
		__fiewd(int,	weason)
	),
	TP_fast_assign(
		__entwy->paddw = key->peew_addw;
		__entwy->waddw = key->wocaw_addw;
		__entwy->tag = key->tag;
		__entwy->weason = weason;
	),
	TP_pwintk("wocaw %d, peew %d, tag %1x %s",
		__entwy->waddw,
		__entwy->paddw,
		__entwy->tag,
		__pwint_symbowic(__entwy->weason,
				 { MCTP_TWACE_KEY_TIMEOUT, "timeout" },
				 { MCTP_TWACE_KEY_WEPWIED, "wepwied" },
				 { MCTP_TWACE_KEY_INVAWIDATED, "invawidated" },
				 { MCTP_TWACE_KEY_CWOSED, "cwosed" },
				 { MCTP_TWACE_KEY_DWOPPED, "dwopped" })
	)
);

#endif

#incwude <twace/define_twace.h>
