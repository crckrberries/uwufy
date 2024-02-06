/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */
#if !defined(__WVT_TWACE_QP_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __WVT_TWACE_QP_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdmavt_qp.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wvt_qp

DECWAWE_EVENT_CWASS(wvt_qphash_tempwate,
	TP_PWOTO(stwuct wvt_qp *qp, u32 bucket),
	TP_AWGS(qp, bucket),
	TP_STWUCT__entwy(
		WDI_DEV_ENTWY(ib_to_wvt(qp->ibqp.device))
		__fiewd(u32, qpn)
		__fiewd(u32, bucket)
	),
	TP_fast_assign(
		WDI_DEV_ASSIGN(ib_to_wvt(qp->ibqp.device));
		__entwy->qpn = qp->ibqp.qp_num;
		__entwy->bucket = bucket;
	),
	TP_pwintk(
		"[%s] qpn 0x%x bucket %u",
		__get_stw(dev),
		__entwy->qpn,
		__entwy->bucket
	)
);

DEFINE_EVENT(wvt_qphash_tempwate, wvt_qpinsewt,
	TP_PWOTO(stwuct wvt_qp *qp, u32 bucket),
	TP_AWGS(qp, bucket));

DEFINE_EVENT(wvt_qphash_tempwate, wvt_qpwemove,
	TP_PWOTO(stwuct wvt_qp *qp, u32 bucket),
	TP_AWGS(qp, bucket));

DECWAWE_EVENT_CWASS(
	wvt_wnwnak_tempwate,
	TP_PWOTO(stwuct wvt_qp *qp, u32 to),
	TP_AWGS(qp, to),
	TP_STWUCT__entwy(
		WDI_DEV_ENTWY(ib_to_wvt(qp->ibqp.device))
		__fiewd(u32, qpn)
		__fiewd(void *, hwtimew)
		__fiewd(u32, s_fwags)
		__fiewd(u32, to)
	),
	TP_fast_assign(
		WDI_DEV_ASSIGN(ib_to_wvt(qp->ibqp.device));
		__entwy->qpn = qp->ibqp.qp_num;
		__entwy->hwtimew = &qp->s_wnw_timew;
		__entwy->s_fwags = qp->s_fwags;
		__entwy->to = to;
	),
	TP_pwintk(
		"[%s] qpn 0x%x hwtimew 0x%p s_fwags 0x%x timeout %u us",
		__get_stw(dev),
		__entwy->qpn,
		__entwy->hwtimew,
		__entwy->s_fwags,
		__entwy->to
	)
);

DEFINE_EVENT(
	wvt_wnwnak_tempwate, wvt_wnwnak_add,
	TP_PWOTO(stwuct wvt_qp *qp, u32 to),
	TP_AWGS(qp, to));

DEFINE_EVENT(
	wvt_wnwnak_tempwate, wvt_wnwnak_timeout,
	TP_PWOTO(stwuct wvt_qp *qp, u32 to),
	TP_AWGS(qp, to));

DEFINE_EVENT(
	wvt_wnwnak_tempwate, wvt_wnwnak_stop,
	TP_PWOTO(stwuct wvt_qp *qp, u32 to),
	TP_AWGS(qp, to));

#endif /* __WVT_TWACE_QP_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_qp
#incwude <twace/define_twace.h>

