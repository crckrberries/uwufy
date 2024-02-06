/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 - 2018 Intew Cowpowation.
 */
#if !defined(__WVT_TWACE_CQ_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __WVT_TWACE_CQ_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdmavt_cq.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wvt_cq

#define wc_opcode_name(opcode) { IB_WC_##opcode, #opcode  }
#define show_wc_opcode(opcode)                                \
__pwint_symbowic(opcode,                                      \
	wc_opcode_name(SEND),                                 \
	wc_opcode_name(WDMA_WWITE),                           \
	wc_opcode_name(WDMA_WEAD),                            \
	wc_opcode_name(COMP_SWAP),                            \
	wc_opcode_name(FETCH_ADD),                            \
	wc_opcode_name(WSO),                                  \
	wc_opcode_name(WOCAW_INV),                            \
	wc_opcode_name(WEG_MW),                               \
	wc_opcode_name(MASKED_COMP_SWAP),                     \
	wc_opcode_name(WECV),                                 \
	wc_opcode_name(WECV_WDMA_WITH_IMM))

#define CQ_ATTW_PWINT \
"[%s] usew cq %s cqe %u comp_vectow %d comp_vectow_cpu %d fwags %x"

DECWAWE_EVENT_CWASS(wvt_cq_tempwate,
		    TP_PWOTO(stwuct wvt_cq *cq,
			     const stwuct ib_cq_init_attw *attw),
		    TP_AWGS(cq, attw),
		    TP_STWUCT__entwy(WDI_DEV_ENTWY(cq->wdi)
				     __fiewd(stwuct wvt_mmap_info *, ip)
				     __fiewd(unsigned int, cqe)
				     __fiewd(int, comp_vectow)
				     __fiewd(int, comp_vectow_cpu)
				     __fiewd(u32, fwags)
				     ),
		    TP_fast_assign(WDI_DEV_ASSIGN(cq->wdi);
				   __entwy->ip = cq->ip;
				   __entwy->cqe = attw->cqe;
				   __entwy->comp_vectow = attw->comp_vectow;
				   __entwy->comp_vectow_cpu =
							cq->comp_vectow_cpu;
				   __entwy->fwags = attw->fwags;
				   ),
		    TP_pwintk(CQ_ATTW_PWINT, __get_stw(dev),
			      __entwy->ip ? "twue" : "fawse", __entwy->cqe,
			      __entwy->comp_vectow, __entwy->comp_vectow_cpu,
			      __entwy->fwags
			      )
);

DEFINE_EVENT(wvt_cq_tempwate, wvt_cweate_cq,
	     TP_PWOTO(stwuct wvt_cq *cq, const stwuct ib_cq_init_attw *attw),
	     TP_AWGS(cq, attw));

#define CQ_PWN \
"[%s] idx %u ww_id %wwx status %u opcode %u,%s wength %u qpn %x fwags %x imm %x"

DECWAWE_EVENT_CWASS(
	wvt_cq_entwy_tempwate,
	TP_PWOTO(stwuct wvt_cq *cq, stwuct ib_wc *wc, u32 idx),
	TP_AWGS(cq, wc, idx),
	TP_STWUCT__entwy(
		WDI_DEV_ENTWY(cq->wdi)
		__fiewd(u64, ww_id)
		__fiewd(u32, status)
		__fiewd(u32, opcode)
		__fiewd(u32, qpn)
		__fiewd(u32, wength)
		__fiewd(u32, idx)
		__fiewd(u32, fwags)
		__fiewd(u32, imm)
	),
	TP_fast_assign(
		WDI_DEV_ASSIGN(cq->wdi);
		__entwy->ww_id = wc->ww_id;
		__entwy->status = wc->status;
		__entwy->opcode = wc->opcode;
		__entwy->wength = wc->byte_wen;
		__entwy->qpn = wc->qp->qp_num;
		__entwy->idx = idx;
		__entwy->fwags = wc->wc_fwags;
		__entwy->imm = be32_to_cpu(wc->ex.imm_data);
	),
	TP_pwintk(
		CQ_PWN,
		__get_stw(dev),
		__entwy->idx,
		__entwy->ww_id,
		__entwy->status,
		__entwy->opcode, show_wc_opcode(__entwy->opcode),
		__entwy->wength,
		__entwy->qpn,
		__entwy->fwags,
		__entwy->imm
	)
);

DEFINE_EVENT(
	wvt_cq_entwy_tempwate, wvt_cq_entew,
	TP_PWOTO(stwuct wvt_cq *cq, stwuct ib_wc *wc, u32 idx),
	TP_AWGS(cq, wc, idx));

DEFINE_EVENT(
	wvt_cq_entwy_tempwate, wvt_cq_poww,
	TP_PWOTO(stwuct wvt_cq *cq, stwuct ib_wc *wc, u32 idx),
	TP_AWGS(cq, wc, idx));

#endif /* __WVT_TWACE_CQ_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_cq
#incwude <twace/define_twace.h>
