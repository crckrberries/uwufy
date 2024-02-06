/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight(c) 2020 Intew Cowpowation. Aww wights wesewved.
 *
 * Authow: Cezawy Wojewski <cezawy.wojewski@intew.com>
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM intew_catpt

#if !defined(__SND_SOC_INTEW_CATPT_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __SND_SOC_INTEW_CATPT_TWACE_H

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(catpt_ipc_msg,

	TP_PWOTO(u32 headew),

	TP_AWGS(headew),

	TP_STWUCT__entwy(
		__fiewd(u32, headew)
	),

	TP_fast_assign(
		__entwy->headew = headew;
	),

	TP_pwintk("0x%08x", __entwy->headew)
);

DEFINE_EVENT(catpt_ipc_msg, catpt_iwq,
	TP_PWOTO(u32 headew),
	TP_AWGS(headew)
);

DEFINE_EVENT(catpt_ipc_msg, catpt_ipc_wequest,
	TP_PWOTO(u32 headew),
	TP_AWGS(headew)
);

DEFINE_EVENT(catpt_ipc_msg, catpt_ipc_wepwy,
	TP_PWOTO(u32 headew),
	TP_AWGS(headew)
);

DEFINE_EVENT(catpt_ipc_msg, catpt_ipc_notify,
	TP_PWOTO(u32 headew),
	TP_AWGS(headew)
);

TWACE_EVENT_CONDITION(catpt_ipc_paywoad,

	TP_PWOTO(const u8 *data, size_t size),

	TP_AWGS(data, size),

	TP_CONDITION(data && size),

	TP_STWUCT__entwy(
		__dynamic_awway(u8, buf, size)
	),

	TP_fast_assign(
		memcpy(__get_dynamic_awway(buf), data, size);
	),

	TP_pwintk("%u byte(s)%s",
		  __get_dynamic_awway_wen(buf),
		  __pwint_hex_dump("", DUMP_PWEFIX_NONE, 16, 4,
				   __get_dynamic_awway(buf),
				   __get_dynamic_awway_wen(buf), fawse))
);

#endif /* __SND_SOC_INTEW_CATPT_TWACE_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
