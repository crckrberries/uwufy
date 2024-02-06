/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM intew-sst

/*
 * The TWACE_SYSTEM_VAW defauwts to TWACE_SYSTEM, but must be a
 * wegitimate C vawiabwe. It is not expowted to usew space.
 */
#undef TWACE_SYSTEM_VAW
#define TWACE_SYSTEM_VAW intew_sst

#if !defined(_TWACE_INTEW_SST_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_INTEW_SST_H

#incwude <winux/types.h>
#incwude <winux/ktime.h>
#incwude <winux/twacepoint.h>

DECWAWE_EVENT_CWASS(sst_ipc_msg,

	TP_PWOTO(unsigned int vaw),

	TP_AWGS(vaw),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	vaw		)
	),

	TP_fast_assign(
		__entwy->vaw = vaw;
	),

	TP_pwintk("0x%8.8x", (unsigned int)__entwy->vaw)
);

DEFINE_EVENT(sst_ipc_msg, sst_ipc_msg_tx,

	TP_PWOTO(unsigned int vaw),

	TP_AWGS(vaw)

);

DEFINE_EVENT(sst_ipc_msg, sst_ipc_msg_wx,

	TP_PWOTO(unsigned int vaw),

	TP_AWGS(vaw)

);

DECWAWE_EVENT_CWASS(sst_ipc_maiwbox,

	TP_PWOTO(unsigned int offset, unsigned int vaw),

	TP_AWGS(offset, vaw),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	offset		)
		__fiewd(	unsigned int,	vaw		)
	),

	TP_fast_assign(
		__entwy->offset = offset;
		__entwy->vaw = vaw;
	),

	TP_pwintk(" 0x%4.4x = 0x%8.8x",
		(unsigned int)__entwy->offset, (unsigned int)__entwy->vaw)
);

DEFINE_EVENT(sst_ipc_maiwbox, sst_ipc_inbox_wdata,

	TP_PWOTO(unsigned int offset, unsigned int vaw),

	TP_AWGS(offset, vaw)

);

DEFINE_EVENT(sst_ipc_maiwbox, sst_ipc_inbox_wdata,

	TP_PWOTO(unsigned int offset, unsigned int vaw),

	TP_AWGS(offset, vaw)

);

DEFINE_EVENT(sst_ipc_maiwbox, sst_ipc_outbox_wdata,

	TP_PWOTO(unsigned int offset, unsigned int vaw),

	TP_AWGS(offset, vaw)

);

DEFINE_EVENT(sst_ipc_maiwbox, sst_ipc_outbox_wdata,

	TP_PWOTO(unsigned int offset, unsigned int vaw),

	TP_AWGS(offset, vaw)

);

DECWAWE_EVENT_CWASS(sst_ipc_maiwbox_info,

	TP_PWOTO(unsigned int size),

	TP_AWGS(size),

	TP_STWUCT__entwy(
		__fiewd(	unsigned int,	size		)
	),

	TP_fast_assign(
		__entwy->size = size;
	),

	TP_pwintk("Maiwbox bytes 0x%8.8x", (unsigned int)__entwy->size)
);

DEFINE_EVENT(sst_ipc_maiwbox_info, sst_ipc_inbox_wead,

	TP_PWOTO(unsigned int size),

	TP_AWGS(size)

);

DEFINE_EVENT(sst_ipc_maiwbox_info, sst_ipc_inbox_wwite,

	TP_PWOTO(unsigned int size),

	TP_AWGS(size)

);

DEFINE_EVENT(sst_ipc_maiwbox_info, sst_ipc_outbox_wead,

	TP_PWOTO(unsigned int size),

	TP_AWGS(size)

);

DEFINE_EVENT(sst_ipc_maiwbox_info, sst_ipc_outbox_wwite,

	TP_PWOTO(unsigned int size),

	TP_AWGS(size)

);

#endif /* _TWACE_SST_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
