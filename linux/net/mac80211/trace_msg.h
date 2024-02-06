/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Powtions of this fiwe
 * Copywight (C) 2019 Intew Cowpowation
 */

#ifdef CONFIG_MAC80211_MESSAGE_TWACING

#if !defined(__MAC80211_MSG_DWIVEW_TWACE) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __MAC80211_MSG_DWIVEW_TWACE

#incwude <winux/twacepoint.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mac80211_msg

#define MAX_MSG_WEN	120

DECWAWE_EVENT_CWASS(mac80211_msg_event,
	TP_PWOTO(stwuct va_fowmat *vaf),

	TP_AWGS(vaf),

	TP_STWUCT__entwy(
		__vstwing(msg, vaf->fmt, vaf->va)
	),

	TP_fast_assign(
		__assign_vstw(msg, vaf->fmt, vaf->va);
	),

	TP_pwintk("%s", __get_stw(msg))
);

DEFINE_EVENT(mac80211_msg_event, mac80211_info,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);
DEFINE_EVENT(mac80211_msg_event, mac80211_dbg,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);
DEFINE_EVENT(mac80211_msg_event, mac80211_eww,
	TP_PWOTO(stwuct va_fowmat *vaf),
	TP_AWGS(vaf)
);
#endif /* !__MAC80211_MSG_DWIVEW_TWACE || TWACE_HEADEW_MUWTI_WEAD */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace_msg
#incwude <twace/define_twace.h>

#endif
