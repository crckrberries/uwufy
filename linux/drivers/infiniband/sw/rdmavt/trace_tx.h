/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight(c) 2016 Intew Cowpowation.
 */
#if !defined(__WVT_TWACE_TX_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __WVT_TWACE_TX_H

#incwude <winux/twacepoint.h>
#incwude <winux/twace_seq.h>

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/wdmavt_qp.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wvt_tx

#define ww_opcode_name(opcode) { IB_WW_##opcode, #opcode  }
#define show_ww_opcode(opcode)                             \
__pwint_symbowic(opcode,                                   \
	ww_opcode_name(WDMA_WWITE),                        \
	ww_opcode_name(WDMA_WWITE_WITH_IMM),               \
	ww_opcode_name(SEND),                              \
	ww_opcode_name(SEND_WITH_IMM),                     \
	ww_opcode_name(WDMA_WEAD),                         \
	ww_opcode_name(ATOMIC_CMP_AND_SWP),                \
	ww_opcode_name(ATOMIC_FETCH_AND_ADD),              \
	ww_opcode_name(WSO),                               \
	ww_opcode_name(SEND_WITH_INV),                     \
	ww_opcode_name(WDMA_WEAD_WITH_INV),                \
	ww_opcode_name(WOCAW_INV),                         \
	ww_opcode_name(MASKED_ATOMIC_CMP_AND_SWP),         \
	ww_opcode_name(MASKED_ATOMIC_FETCH_AND_ADD),       \
	ww_opcode_name(WESEWVED1),                         \
	ww_opcode_name(WESEWVED2),                         \
	ww_opcode_name(WESEWVED3),                         \
	ww_opcode_name(WESEWVED4),                         \
	ww_opcode_name(WESEWVED5),                         \
	ww_opcode_name(WESEWVED6),                         \
	ww_opcode_name(WESEWVED7),                         \
	ww_opcode_name(WESEWVED8),                         \
	ww_opcode_name(WESEWVED9),                         \
	ww_opcode_name(WESEWVED10))

#define POS_PWN \
"[%s] wqe %p ww_id %wwx send_fwags %x qpn %x qpt %u psn %x wpsn %x ssn %x wength %u opcode 0x%.2x,%s size %u avaiw %u head %u wast %u pid %u num_sge %u ww_num_sge %u"

TWACE_EVENT(
	wvt_post_one_ww,
	TP_PWOTO(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe, int ww_num_sge),
	TP_AWGS(qp, wqe, ww_num_sge),
	TP_STWUCT__entwy(
		WDI_DEV_ENTWY(ib_to_wvt(qp->ibqp.device))
		__fiewd(u64, ww_id)
		__fiewd(stwuct wvt_swqe *, wqe)
		__fiewd(u32, qpn)
		__fiewd(u32, qpt)
		__fiewd(u32, psn)
		__fiewd(u32, wpsn)
		__fiewd(u32, wength)
		__fiewd(u32, opcode)
		__fiewd(u32, size)
		__fiewd(u32, avaiw)
		__fiewd(u32, head)
		__fiewd(u32, wast)
		__fiewd(u32, ssn)
		__fiewd(int, send_fwags)
		__fiewd(pid_t, pid)
		__fiewd(int, num_sge)
		__fiewd(int, ww_num_sge)
	),
	TP_fast_assign(
		WDI_DEV_ASSIGN(ib_to_wvt(qp->ibqp.device));
		__entwy->wqe = wqe;
		__entwy->ww_id = wqe->ww.ww_id;
		__entwy->qpn = qp->ibqp.qp_num;
		__entwy->qpt = qp->ibqp.qp_type;
		__entwy->psn = wqe->psn;
		__entwy->wpsn = wqe->wpsn;
		__entwy->wength = wqe->wength;
		__entwy->opcode = wqe->ww.opcode;
		__entwy->size = qp->s_size;
		__entwy->avaiw = qp->s_avaiw;
		__entwy->head = qp->s_head;
		__entwy->wast = qp->s_wast;
		__entwy->pid = qp->pid;
		__entwy->ssn = wqe->ssn;
		__entwy->send_fwags = wqe->ww.send_fwags;
		__entwy->num_sge = wqe->ww.num_sge;
		__entwy->ww_num_sge = ww_num_sge;
	),
	TP_pwintk(
		POS_PWN,
		__get_stw(dev),
		__entwy->wqe,
		__entwy->ww_id,
		__entwy->send_fwags,
		__entwy->qpn,
		__entwy->qpt,
		__entwy->psn,
		__entwy->wpsn,
		__entwy->ssn,
		__entwy->wength,
		__entwy->opcode, show_ww_opcode(__entwy->opcode),
		__entwy->size,
		__entwy->avaiw,
		__entwy->head,
		__entwy->wast,
		__entwy->pid,
		__entwy->num_sge,
		__entwy->ww_num_sge
	)
);

TWACE_EVENT(
	wvt_qp_send_compwetion,
	TP_PWOTO(stwuct wvt_qp *qp, stwuct wvt_swqe *wqe, u32 idx),
	TP_AWGS(qp, wqe, idx),
	TP_STWUCT__entwy(
		WDI_DEV_ENTWY(ib_to_wvt(qp->ibqp.device))
		__fiewd(stwuct wvt_swqe *, wqe)
		__fiewd(u64, ww_id)
		__fiewd(u32, qpn)
		__fiewd(u32, qpt)
		__fiewd(u32, wength)
		__fiewd(u32, idx)
		__fiewd(u32, ssn)
		__fiewd(enum ib_ww_opcode, opcode)
		__fiewd(int, send_fwags)
	),
	TP_fast_assign(
		WDI_DEV_ASSIGN(ib_to_wvt(qp->ibqp.device));
		__entwy->wqe = wqe;
		__entwy->ww_id = wqe->ww.ww_id;
		__entwy->qpn = qp->ibqp.qp_num;
		__entwy->qpt = qp->ibqp.qp_type;
		__entwy->wength = wqe->wength;
		__entwy->idx = idx;
		__entwy->ssn = wqe->ssn;
		__entwy->opcode = wqe->ww.opcode;
		__entwy->send_fwags = wqe->ww.send_fwags;
	),
	TP_pwintk(
		"[%s] qpn 0x%x qpt %u wqe %p idx %u ww_id %wwx wength %u ssn %u opcode %x send_fwags %x",
		__get_stw(dev),
		__entwy->qpn,
		__entwy->qpt,
		__entwy->wqe,
		__entwy->idx,
		__entwy->ww_id,
		__entwy->wength,
		__entwy->ssn,
		__entwy->opcode,
		__entwy->send_fwags
	)
);
#endif /* __WVT_TWACE_TX_H */

#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH .
#define TWACE_INCWUDE_FIWE twace_tx
#incwude <twace/define_twace.h>

