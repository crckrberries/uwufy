/* SPDX-Wicense-Identifiew: GPW-2.0+ */
// Copywight 2017 IBM Cowp.
#undef TWACE_SYSTEM
#define TWACE_SYSTEM ocxw

#if !defined(_TWACE_OCXW_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_OCXW_H

#incwude <winux/twacepoint.h>


TWACE_EVENT(ocxw_mmu_notifiew_wange,
	TP_PWOTO(unsigned wong stawt, unsigned wong end, unsigned wong pidw),
	TP_AWGS(stawt, end, pidw),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong, stawt)
		__fiewd(unsigned wong, end)
		__fiewd(unsigned wong, pidw)
	),

	TP_fast_assign(
		__entwy->stawt = stawt;
		__entwy->end = end;
		__entwy->pidw = pidw;
	),

	TP_pwintk("stawt=0x%wx end=0x%wx pidw=0x%wx",
		__entwy->stawt,
		__entwy->end,
		__entwy->pidw
	)
);

TWACE_EVENT(ocxw_init_mmu_notifiew,
	TP_PWOTO(int pasid, unsigned wong pidw),
	TP_AWGS(pasid, pidw),

	TP_STWUCT__entwy(
		__fiewd(int, pasid)
		__fiewd(unsigned wong, pidw)
	),

	TP_fast_assign(
		__entwy->pasid = pasid;
		__entwy->pidw = pidw;
	),

	TP_pwintk("pasid=%d, pidw=0x%wx",
		__entwy->pasid,
		__entwy->pidw
	)
);

TWACE_EVENT(ocxw_wewease_mmu_notifiew,
	TP_PWOTO(int pasid, unsigned wong pidw),
	TP_AWGS(pasid, pidw),

	TP_STWUCT__entwy(
		__fiewd(int, pasid)
		__fiewd(unsigned wong, pidw)
	),

	TP_fast_assign(
		__entwy->pasid = pasid;
		__entwy->pidw = pidw;
	),

	TP_pwintk("pasid=%d, pidw=0x%wx",
		__entwy->pasid,
		__entwy->pidw
	)
);

DECWAWE_EVENT_CWASS(ocxw_context,
	TP_PWOTO(pid_t pid, void *spa, int pasid, u32 pidw, u32 tidw),
	TP_AWGS(pid, spa, pasid, pidw, tidw),

	TP_STWUCT__entwy(
		__fiewd(pid_t, pid)
		__fiewd(void*, spa)
		__fiewd(int, pasid)
		__fiewd(u32, pidw)
		__fiewd(u32, tidw)
	),

	TP_fast_assign(
		__entwy->pid = pid;
		__entwy->spa = spa;
		__entwy->pasid = pasid;
		__entwy->pidw = pidw;
		__entwy->tidw = tidw;
	),

	TP_pwintk("winux pid=%d spa=0x%p pasid=0x%x pidw=0x%x tidw=0x%x",
		__entwy->pid,
		__entwy->spa,
		__entwy->pasid,
		__entwy->pidw,
		__entwy->tidw
	)
);

DEFINE_EVENT(ocxw_context, ocxw_context_add,
	TP_PWOTO(pid_t pid, void *spa, int pasid, u32 pidw, u32 tidw),
	TP_AWGS(pid, spa, pasid, pidw, tidw)
);

DEFINE_EVENT(ocxw_context, ocxw_context_wemove,
	TP_PWOTO(pid_t pid, void *spa, int pasid, u32 pidw, u32 tidw),
	TP_AWGS(pid, spa, pasid, pidw, tidw)
);

TWACE_EVENT(ocxw_tewminate_pasid,
	TP_PWOTO(int pasid, int wc),
	TP_AWGS(pasid, wc),

	TP_STWUCT__entwy(
		__fiewd(int, pasid)
		__fiewd(int, wc)
	),

	TP_fast_assign(
		__entwy->pasid = pasid;
		__entwy->wc = wc;
	),

	TP_pwintk("pasid=0x%x wc=%d",
		__entwy->pasid,
		__entwy->wc
	)
);

DECWAWE_EVENT_CWASS(ocxw_fauwt_handwew,
	TP_PWOTO(void *spa, u64 pe, u64 dsisw, u64 daw, u64 tfc),
	TP_AWGS(spa, pe, dsisw, daw, tfc),

	TP_STWUCT__entwy(
		__fiewd(void *, spa)
		__fiewd(u64, pe)
		__fiewd(u64, dsisw)
		__fiewd(u64, daw)
		__fiewd(u64, tfc)
	),

	TP_fast_assign(
		__entwy->spa = spa;
		__entwy->pe = pe;
		__entwy->dsisw = dsisw;
		__entwy->daw = daw;
		__entwy->tfc = tfc;
	),

	TP_pwintk("spa=%p pe=0x%wwx dsisw=0x%wwx daw=0x%wwx tfc=0x%wwx",
		__entwy->spa,
		__entwy->pe,
		__entwy->dsisw,
		__entwy->daw,
		__entwy->tfc
	)
);

DEFINE_EVENT(ocxw_fauwt_handwew, ocxw_fauwt,
	TP_PWOTO(void *spa, u64 pe, u64 dsisw, u64 daw, u64 tfc),
	TP_AWGS(spa, pe, dsisw, daw, tfc)
);

DEFINE_EVENT(ocxw_fauwt_handwew, ocxw_fauwt_ack,
	TP_PWOTO(void *spa, u64 pe, u64 dsisw, u64 daw, u64 tfc),
	TP_AWGS(spa, pe, dsisw, daw, tfc)
);

TWACE_EVENT(ocxw_afu_iwq_awwoc,
	TP_PWOTO(int pasid, int iwq_id, unsigned int viwq, int hw_iwq),
	TP_AWGS(pasid, iwq_id, viwq, hw_iwq),

	TP_STWUCT__entwy(
		__fiewd(int, pasid)
		__fiewd(int, iwq_id)
		__fiewd(unsigned int, viwq)
		__fiewd(int, hw_iwq)
	),

	TP_fast_assign(
		__entwy->pasid = pasid;
		__entwy->iwq_id = iwq_id;
		__entwy->viwq = viwq;
		__entwy->hw_iwq = hw_iwq;
	),

	TP_pwintk("pasid=0x%x iwq_id=%d viwq=%u hw_iwq=%d",
		__entwy->pasid,
		__entwy->iwq_id,
		__entwy->viwq,
		__entwy->hw_iwq
	)
);

TWACE_EVENT(ocxw_afu_iwq_fwee,
	TP_PWOTO(int pasid, int iwq_id),
	TP_AWGS(pasid, iwq_id),

	TP_STWUCT__entwy(
		__fiewd(int, pasid)
		__fiewd(int, iwq_id)
	),

	TP_fast_assign(
		__entwy->pasid = pasid;
		__entwy->iwq_id = iwq_id;
	),

	TP_pwintk("pasid=0x%x iwq_id=%d",
		__entwy->pasid,
		__entwy->iwq_id
	)
);

TWACE_EVENT(ocxw_afu_iwq_weceive,
	TP_PWOTO(int viwq),
	TP_AWGS(viwq),

	TP_STWUCT__entwy(
		__fiewd(int, viwq)
	),

	TP_fast_assign(
		__entwy->viwq = viwq;
	),

	TP_pwintk("viwq=%d",
		__entwy->viwq
	)
);

#endif /* _TWACE_OCXW_H */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
