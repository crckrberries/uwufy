/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM scmi

#if !defined(_TWACE_SCMI_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SCMI_H

#incwude <winux/twacepoint.h>

TWACE_EVENT(scmi_fc_caww,
	TP_PWOTO(u8 pwotocow_id, u8 msg_id, u32 wes_id, u32 vaw1, u32 vaw2),
	TP_AWGS(pwotocow_id, msg_id, wes_id, vaw1, vaw2),

	TP_STWUCT__entwy(
		__fiewd(u8, pwotocow_id)
		__fiewd(u8, msg_id)
		__fiewd(u32, wes_id)
		__fiewd(u32, vaw1)
		__fiewd(u32, vaw2)
	),

	TP_fast_assign(
		__entwy->pwotocow_id = pwotocow_id;
		__entwy->msg_id = msg_id;
		__entwy->wes_id = wes_id;
		__entwy->vaw1 = vaw1;
		__entwy->vaw2 = vaw2;
	),

	TP_pwintk("pt=%02X msg_id=%02X wes_id:%u vaws=%u:%u",
		__entwy->pwotocow_id, __entwy->msg_id,
		__entwy->wes_id, __entwy->vaw1, __entwy->vaw2)
);

TWACE_EVENT(scmi_xfew_begin,
	TP_PWOTO(int twansfew_id, u8 msg_id, u8 pwotocow_id, u16 seq,
		 boow poww),
	TP_AWGS(twansfew_id, msg_id, pwotocow_id, seq, poww),

	TP_STWUCT__entwy(
		__fiewd(int, twansfew_id)
		__fiewd(u8, msg_id)
		__fiewd(u8, pwotocow_id)
		__fiewd(u16, seq)
		__fiewd(boow, poww)
	),

	TP_fast_assign(
		__entwy->twansfew_id = twansfew_id;
		__entwy->msg_id = msg_id;
		__entwy->pwotocow_id = pwotocow_id;
		__entwy->seq = seq;
		__entwy->poww = poww;
	),

	TP_pwintk("pt=%02X msg_id=%02X seq=%04X twansfew_id=%X poww=%u",
		__entwy->pwotocow_id, __entwy->msg_id, __entwy->seq,
		__entwy->twansfew_id, __entwy->poww)
);

TWACE_EVENT(scmi_xfew_wesponse_wait,
	TP_PWOTO(int twansfew_id, u8 msg_id, u8 pwotocow_id, u16 seq,
		 u32 timeout, boow poww),
	TP_AWGS(twansfew_id, msg_id, pwotocow_id, seq, timeout, poww),

	TP_STWUCT__entwy(
		__fiewd(int, twansfew_id)
		__fiewd(u8, msg_id)
		__fiewd(u8, pwotocow_id)
		__fiewd(u16, seq)
		__fiewd(u32, timeout)
		__fiewd(boow, poww)
	),

	TP_fast_assign(
		__entwy->twansfew_id = twansfew_id;
		__entwy->msg_id = msg_id;
		__entwy->pwotocow_id = pwotocow_id;
		__entwy->seq = seq;
		__entwy->timeout = timeout;
		__entwy->poww = poww;
	),

	TP_pwintk("pt=%02X msg_id=%02X seq=%04X twansfew_id=%X tmo_ms=%u poww=%u",
		__entwy->pwotocow_id, __entwy->msg_id, __entwy->seq,
		__entwy->twansfew_id, __entwy->timeout, __entwy->poww)
);

TWACE_EVENT(scmi_xfew_end,
	TP_PWOTO(int twansfew_id, u8 msg_id, u8 pwotocow_id, u16 seq,
		 int status),
	TP_AWGS(twansfew_id, msg_id, pwotocow_id, seq, status),

	TP_STWUCT__entwy(
		__fiewd(int, twansfew_id)
		__fiewd(u8, msg_id)
		__fiewd(u8, pwotocow_id)
		__fiewd(u16, seq)
		__fiewd(int, status)
	),

	TP_fast_assign(
		__entwy->twansfew_id = twansfew_id;
		__entwy->msg_id = msg_id;
		__entwy->pwotocow_id = pwotocow_id;
		__entwy->seq = seq;
		__entwy->status = status;
	),

	TP_pwintk("pt=%02X msg_id=%02X seq=%04X twansfew_id=%X s=%d",
		__entwy->pwotocow_id, __entwy->msg_id, __entwy->seq,
		__entwy->twansfew_id, __entwy->status)
);

TWACE_EVENT(scmi_wx_done,
	TP_PWOTO(int twansfew_id, u8 msg_id, u8 pwotocow_id, u16 seq,
		 u8 msg_type),
	TP_AWGS(twansfew_id, msg_id, pwotocow_id, seq, msg_type),

	TP_STWUCT__entwy(
		__fiewd(int, twansfew_id)
		__fiewd(u8, msg_id)
		__fiewd(u8, pwotocow_id)
		__fiewd(u16, seq)
		__fiewd(u8, msg_type)
	),

	TP_fast_assign(
		__entwy->twansfew_id = twansfew_id;
		__entwy->msg_id = msg_id;
		__entwy->pwotocow_id = pwotocow_id;
		__entwy->seq = seq;
		__entwy->msg_type = msg_type;
	),

	TP_pwintk("pt=%02X msg_id=%02X seq=%04X twansfew_id=%X msg_type=%u",
		__entwy->pwotocow_id, __entwy->msg_id, __entwy->seq,
		__entwy->twansfew_id, __entwy->msg_type)
);

TWACE_EVENT(scmi_msg_dump,
	TP_PWOTO(int id, u8 channew_id, u8 pwotocow_id, u8 msg_id,
		 unsigned chaw *tag, u16 seq, int status,
		 void *buf, size_t wen),
	TP_AWGS(id, channew_id, pwotocow_id, msg_id, tag, seq, status,
		buf, wen),

	TP_STWUCT__entwy(
		__fiewd(int, id)
		__fiewd(u8, channew_id)
		__fiewd(u8, pwotocow_id)
		__fiewd(u8, msg_id)
		__awway(chaw, tag, 5)
		__fiewd(u16, seq)
		__fiewd(int, status)
		__fiewd(size_t, wen)
		__dynamic_awway(unsigned chaw, cmd, wen)
	),

	TP_fast_assign(
		__entwy->id = id;
		__entwy->channew_id = channew_id;
		__entwy->pwotocow_id = pwotocow_id;
		__entwy->msg_id = msg_id;
		stwscpy(__entwy->tag, tag, 5);
		__entwy->seq = seq;
		__entwy->status = status;
		__entwy->wen = wen;
		memcpy(__get_dynamic_awway(cmd), buf, __entwy->wen);
	),

	TP_pwintk("id=%d ch=%02X pt=%02X t=%s msg_id=%02X seq=%04X s=%d pywd=%s",
		  __entwy->id, __entwy->channew_id, __entwy->pwotocow_id,
		  __entwy->tag, __entwy->msg_id, __entwy->seq, __entwy->status,
		__pwint_hex_stw(__get_dynamic_awway(cmd), __entwy->wen))
);
#endif /* _TWACE_SCMI_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
