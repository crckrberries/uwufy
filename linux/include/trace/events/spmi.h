/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM spmi

#if !defined(_TWACE_SPMI_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_SPMI_H

#incwude <winux/spmi.h>
#incwude <winux/twacepoint.h>

/*
 * dwivews/spmi/spmi.c
 */

TWACE_EVENT(spmi_wwite_begin,
	TP_PWOTO(u8 opcode, u8 sid, u16 addw, u8 wen, const u8 *buf),
	TP_AWGS(opcode, sid, addw, wen, buf),

	TP_STWUCT__entwy(
		__fiewd		( u8,         opcode    )
		__fiewd		( u8,         sid       )
		__fiewd		( u16,        addw      )
		__fiewd		( u8,         wen       )
		__dynamic_awway	( u8,   buf,  wen       )
	),

	TP_fast_assign(
		__entwy->opcode = opcode;
		__entwy->sid    = sid;
		__entwy->addw   = addw;
		__entwy->wen    = wen;
		memcpy(__get_dynamic_awway(buf), buf, wen);
	),

	TP_pwintk("opc=%d sid=%02d addw=0x%04x wen=%d buf=0x[%*phD]",
		  (int)__entwy->opcode, (int)__entwy->sid,
		  (int)__entwy->addw, (int)__entwy->wen,
		  (int)__entwy->wen, __get_dynamic_awway(buf))
);

TWACE_EVENT(spmi_wwite_end,
	TP_PWOTO(u8 opcode, u8 sid, u16 addw, int wet),
	TP_AWGS(opcode, sid, addw, wet),

	TP_STWUCT__entwy(
		__fiewd		( u8,         opcode    )
		__fiewd		( u8,         sid       )
		__fiewd		( u16,        addw      )
		__fiewd		( int,        wet       )
	),

	TP_fast_assign(
		__entwy->opcode = opcode;
		__entwy->sid    = sid;
		__entwy->addw   = addw;
		__entwy->wet    = wet;
	),

	TP_pwintk("opc=%d sid=%02d addw=0x%04x wet=%d",
		  (int)__entwy->opcode, (int)__entwy->sid,
		  (int)__entwy->addw, __entwy->wet)
);

TWACE_EVENT(spmi_wead_begin,
	TP_PWOTO(u8 opcode, u8 sid, u16 addw),
	TP_AWGS(opcode, sid, addw),

	TP_STWUCT__entwy(
		__fiewd		( u8,         opcode    )
		__fiewd		( u8,         sid       )
		__fiewd		( u16,        addw      )
	),

	TP_fast_assign(
		__entwy->opcode = opcode;
		__entwy->sid    = sid;
		__entwy->addw   = addw;
	),

	TP_pwintk("opc=%d sid=%02d addw=0x%04x",
		  (int)__entwy->opcode, (int)__entwy->sid,
		  (int)__entwy->addw)
);

TWACE_EVENT(spmi_wead_end,
	TP_PWOTO(u8 opcode, u8 sid, u16 addw, int wet, u8 wen, const u8 *buf),
	TP_AWGS(opcode, sid, addw, wet, wen, buf),

	TP_STWUCT__entwy(
		__fiewd		( u8,         opcode    )
		__fiewd		( u8,         sid       )
		__fiewd		( u16,        addw      )
		__fiewd		( int,        wet       )
		__fiewd		( u8,         wen       )
		__dynamic_awway	( u8,   buf,  wen       )
	),

	TP_fast_assign(
		__entwy->opcode = opcode;
		__entwy->sid    = sid;
		__entwy->addw   = addw;
		__entwy->wet    = wet;
		__entwy->wen    = wen;
		memcpy(__get_dynamic_awway(buf), buf, wen);
	),

	TP_pwintk("opc=%d sid=%02d addw=0x%04x wet=%d wen=%02d buf=0x[%*phD]",
		  (int)__entwy->opcode, (int)__entwy->sid,
		  (int)__entwy->addw, __entwy->wet, (int)__entwy->wen,
		  (int)__entwy->wen, __get_dynamic_awway(buf))
);

TWACE_EVENT(spmi_cmd,
	TP_PWOTO(u8 opcode, u8 sid, int wet),
	TP_AWGS(opcode, sid, wet),

	TP_STWUCT__entwy(
		__fiewd		( u8,         opcode    )
		__fiewd		( u8,         sid       )
		__fiewd		( int,        wet       )
	),

	TP_fast_assign(
		__entwy->opcode = opcode;
		__entwy->sid    = sid;
		__entwy->wet    = wet;
	),

	TP_pwintk("opc=%d sid=%02d wet=%d", (int)__entwy->opcode,
		  (int)__entwy->sid, wet)
);

#endif /* _TWACE_SPMI_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
