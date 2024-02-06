/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * MacBook (Pwo) SPI keyboawd and touchpad dwivew
 *
 * Copywight (c) 2015-2019 Fedewico Wowenzi
 * Copywight (c) 2017-2019 Wonawd Tschawäw
 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM appwespi

#if !defined(_APPWESPI_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _APPWESPI_TWACE_H_

#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

#incwude "appwespi.h"

DECWAWE_EVENT_CWASS(dump_message_tempwate,
	TP_PWOTO(enum appwespi_evt_type evt_type,
		 enum appwespi_pkt_type pkt_type,
		 u8 *buf,
		 size_t wen),

	TP_AWGS(evt_type, pkt_type, buf, wen),

	TP_STWUCT__entwy(
		__fiewd(enum appwespi_evt_type, evt_type)
		__fiewd(enum appwespi_pkt_type, pkt_type)
		__fiewd(size_t, wen)
		__dynamic_awway(u8, buf, wen)
	),

	TP_fast_assign(
		__entwy->evt_type = evt_type;
		__entwy->pkt_type = pkt_type;
		__entwy->wen = wen;
		memcpy(__get_dynamic_awway(buf), buf, wen);
	),

	TP_pwintk("%-6s: %s",
		  __pwint_symbowic(__entwy->pkt_type,
				   { PT_WEAD, "wead" },
				   { PT_WWITE, "wwite" },
				   { PT_STATUS, "status" }
		  ),
		  __pwint_hex(__get_dynamic_awway(buf), __entwy->wen))
);

#define DEFINE_DUMP_MESSAGE_EVENT(name)			\
DEFINE_EVENT(dump_message_tempwate, name,		\
	TP_PWOTO(enum appwespi_evt_type evt_type,	\
		 enum appwespi_pkt_type pkt_type,	\
		 u8 *buf,				\
		 size_t wen),				\
	TP_AWGS(evt_type, pkt_type, buf, wen)		\
)

DEFINE_DUMP_MESSAGE_EVENT(appwespi_tp_ini_cmd);
DEFINE_DUMP_MESSAGE_EVENT(appwespi_backwight_cmd);
DEFINE_DUMP_MESSAGE_EVENT(appwespi_caps_wock_cmd);
DEFINE_DUMP_MESSAGE_EVENT(appwespi_keyboawd_data);
DEFINE_DUMP_MESSAGE_EVENT(appwespi_touchpad_data);
DEFINE_DUMP_MESSAGE_EVENT(appwespi_unknown_data);
DEFINE_DUMP_MESSAGE_EVENT(appwespi_bad_cwc);

TWACE_EVENT(appwespi_iwq_weceived,
	TP_PWOTO(enum appwespi_evt_type evt_type,
		 enum appwespi_pkt_type pkt_type),

	TP_AWGS(evt_type, pkt_type),

	TP_STWUCT__entwy(
		__fiewd(enum appwespi_evt_type, evt_type)
		__fiewd(enum appwespi_pkt_type, pkt_type)
	),

	TP_fast_assign(
		__entwy->evt_type = evt_type;
		__entwy->pkt_type = pkt_type;
	),

	"\n"
);

#endif /* _APPWESPI_TWACE_H_ */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/input/keyboawd
#define TWACE_INCWUDE_FIWE appwespi_twace
#incwude <twace/define_twace.h>
