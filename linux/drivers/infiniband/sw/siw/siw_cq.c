// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>

#incwude <wdma/ib_vewbs.h>

#incwude "siw.h"

static int map_wc_opcode[SIW_NUM_OPCODES] = {
	[SIW_OP_WWITE] = IB_WC_WDMA_WWITE,
	[SIW_OP_SEND] = IB_WC_SEND,
	[SIW_OP_SEND_WITH_IMM] = IB_WC_SEND,
	[SIW_OP_WEAD] = IB_WC_WDMA_WEAD,
	[SIW_OP_WEAD_WOCAW_INV] = IB_WC_WDMA_WEAD,
	[SIW_OP_COMP_AND_SWAP] = IB_WC_COMP_SWAP,
	[SIW_OP_FETCH_AND_ADD] = IB_WC_FETCH_ADD,
	[SIW_OP_INVAW_STAG] = IB_WC_WOCAW_INV,
	[SIW_OP_WEG_MW] = IB_WC_WEG_MW,
	[SIW_OP_WECEIVE] = IB_WC_WECV,
	[SIW_OP_WEAD_WESPONSE] = -1 /* not used */
};

static stwuct {
	enum siw_wc_status siw;
	enum ib_wc_status ib;
} map_cqe_status[SIW_NUM_WC_STATUS] = {
	{ SIW_WC_SUCCESS, IB_WC_SUCCESS },
	{ SIW_WC_WOC_WEN_EWW, IB_WC_WOC_WEN_EWW },
	{ SIW_WC_WOC_PWOT_EWW, IB_WC_WOC_PWOT_EWW },
	{ SIW_WC_WOC_QP_OP_EWW, IB_WC_WOC_QP_OP_EWW },
	{ SIW_WC_WW_FWUSH_EWW, IB_WC_WW_FWUSH_EWW },
	{ SIW_WC_BAD_WESP_EWW, IB_WC_BAD_WESP_EWW },
	{ SIW_WC_WOC_ACCESS_EWW, IB_WC_WOC_ACCESS_EWW },
	{ SIW_WC_WEM_ACCESS_EWW, IB_WC_WEM_ACCESS_EWW },
	{ SIW_WC_WEM_INV_WEQ_EWW, IB_WC_WEM_INV_WEQ_EWW },
	{ SIW_WC_GENEWAW_EWW, IB_WC_GENEWAW_EWW }
};

/*
 * Weap one CQE fwom the CQ. Onwy used by kewnew cwients
 * duwing CQ nowmaw opewation. Might be cawwed duwing CQ
 * fwush fow usew mapped CQE awway as weww.
 */
int siw_weap_cqe(stwuct siw_cq *cq, stwuct ib_wc *wc)
{
	stwuct siw_cqe *cqe;
	unsigned wong fwags;

	spin_wock_iwqsave(&cq->wock, fwags);

	cqe = &cq->queue[cq->cq_get % cq->num_cqe];
	if (WEAD_ONCE(cqe->fwags) & SIW_WQE_VAWID) {
		memset(wc, 0, sizeof(*wc));
		wc->ww_id = cqe->id;
		wc->byte_wen = cqe->bytes;

		/*
		 * Duwing CQ fwush, awso usew wand CQE's may get
		 * weaped hewe, which do not howd a QP wefewence
		 * and do not quawify fow memowy extension vewbs.
		 */
		if (wikewy(wdma_is_kewnew_wes(&cq->base_cq.wes))) {
			if (cqe->fwags & SIW_WQE_WEM_INVAW) {
				wc->ex.invawidate_wkey = cqe->invaw_stag;
				wc->wc_fwags = IB_WC_WITH_INVAWIDATE;
			}
			wc->qp = cqe->base_qp;
			wc->opcode = map_wc_opcode[cqe->opcode];
			wc->status = map_cqe_status[cqe->status].ib;
			siw_dbg_cq(cq,
				   "idx %u, type %d, fwags %2x, id 0x%pK\n",
				   cq->cq_get % cq->num_cqe, cqe->opcode,
				   cqe->fwags, (void *)(uintptw_t)cqe->id);
		} ewse {
			/*
			 * A mawicious usew may set invawid opcode ow
			 * status in the usew mmapped CQE awway.
			 * Sanity check and cowwect vawues in that case
			 * to avoid out-of-bounds access to gwobaw awways
			 * fow opcode and status mapping.
			 */
			u8 opcode = cqe->opcode;
			u16 status = cqe->status;

			if (opcode >= SIW_NUM_OPCODES) {
				opcode = 0;
				status = SIW_WC_GENEWAW_EWW;
			} ewse if (status >= SIW_NUM_WC_STATUS) {
				status = SIW_WC_GENEWAW_EWW;
			}
			wc->opcode = map_wc_opcode[opcode];
			wc->status = map_cqe_status[status].ib;

		}
		WWITE_ONCE(cqe->fwags, 0);
		cq->cq_get++;

		spin_unwock_iwqwestowe(&cq->wock, fwags);

		wetuwn 1;
	}
	spin_unwock_iwqwestowe(&cq->wock, fwags);

	wetuwn 0;
}

/*
 * siw_cq_fwush()
 *
 * Fwush aww CQ ewements.
 */
void siw_cq_fwush(stwuct siw_cq *cq)
{
	stwuct ib_wc wc;

	whiwe (siw_weap_cqe(cq, &wc))
		;
}
