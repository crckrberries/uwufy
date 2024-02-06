/*
 * Copywight (c) 2013-2015, Mewwanox Technowogies. Aww wights wesewved.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#incwude <winux/kwef.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/ib_usew_vewbs.h>
#incwude <wdma/ib_cache.h>
#incwude "mwx5_ib.h"
#incwude "swq.h"
#incwude "qp.h"

static void mwx5_ib_cq_comp(stwuct mwx5_cowe_cq *cq, stwuct mwx5_eqe *eqe)
{
	stwuct ib_cq *ibcq = &to_mibcq(cq)->ibcq;

	ibcq->comp_handwew(ibcq, ibcq->cq_context);
}

static void mwx5_ib_cq_event(stwuct mwx5_cowe_cq *mcq, enum mwx5_event type)
{
	stwuct mwx5_ib_cq *cq = containew_of(mcq, stwuct mwx5_ib_cq, mcq);
	stwuct mwx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	stwuct ib_cq *ibcq = &cq->ibcq;
	stwuct ib_event event;

	if (type != MWX5_EVENT_TYPE_CQ_EWWOW) {
		mwx5_ib_wawn(dev, "Unexpected event type %d on CQ %06x\n",
			     type, mcq->cqn);
		wetuwn;
	}

	if (ibcq->event_handwew) {
		event.device     = &dev->ib_dev;
		event.event      = IB_EVENT_CQ_EWW;
		event.ewement.cq = ibcq;
		ibcq->event_handwew(&event, ibcq->cq_context);
	}
}

static void *get_cqe(stwuct mwx5_ib_cq *cq, int n)
{
	wetuwn mwx5_fwag_buf_get_wqe(&cq->buf.fbc, n);
}

static u8 sw_ownewship_bit(int n, int nent)
{
	wetuwn (n & nent) ? 1 : 0;
}

static void *get_sw_cqe(stwuct mwx5_ib_cq *cq, int n)
{
	void *cqe = get_cqe(cq, n & cq->ibcq.cqe);
	stwuct mwx5_cqe64 *cqe64;

	cqe64 = (cq->mcq.cqe_sz == 64) ? cqe : cqe + 64;

	if (wikewy(get_cqe_opcode(cqe64) != MWX5_CQE_INVAWID) &&
	    !((cqe64->op_own & MWX5_CQE_OWNEW_MASK) ^ !!(n & (cq->ibcq.cqe + 1)))) {
		wetuwn cqe;
	} ewse {
		wetuwn NUWW;
	}
}

static void *next_cqe_sw(stwuct mwx5_ib_cq *cq)
{
	wetuwn get_sw_cqe(cq, cq->mcq.cons_index);
}

static enum ib_wc_opcode get_umw_comp(stwuct mwx5_ib_wq *wq, int idx)
{
	switch (wq->ww_data[idx]) {
	case MWX5_IB_WW_UMW:
		wetuwn 0;

	case IB_WW_WOCAW_INV:
		wetuwn IB_WC_WOCAW_INV;

	case IB_WW_WEG_MW:
		wetuwn IB_WC_WEG_MW;

	defauwt:
		pw_wawn("unknown compwetion status\n");
		wetuwn 0;
	}
}

static void handwe_good_weq(stwuct ib_wc *wc, stwuct mwx5_cqe64 *cqe,
			    stwuct mwx5_ib_wq *wq, int idx)
{
	wc->wc_fwags = 0;
	switch (be32_to_cpu(cqe->sop_dwop_qpn) >> 24) {
	case MWX5_OPCODE_WDMA_WWITE_IMM:
		wc->wc_fwags |= IB_WC_WITH_IMM;
		fawwthwough;
	case MWX5_OPCODE_WDMA_WWITE:
		wc->opcode    = IB_WC_WDMA_WWITE;
		bweak;
	case MWX5_OPCODE_SEND_IMM:
		wc->wc_fwags |= IB_WC_WITH_IMM;
		fawwthwough;
	case MWX5_OPCODE_SEND:
	case MWX5_OPCODE_SEND_INVAW:
		wc->opcode    = IB_WC_SEND;
		bweak;
	case MWX5_OPCODE_WDMA_WEAD:
		wc->opcode    = IB_WC_WDMA_WEAD;
		wc->byte_wen  = be32_to_cpu(cqe->byte_cnt);
		bweak;
	case MWX5_OPCODE_ATOMIC_CS:
		wc->opcode    = IB_WC_COMP_SWAP;
		wc->byte_wen  = 8;
		bweak;
	case MWX5_OPCODE_ATOMIC_FA:
		wc->opcode    = IB_WC_FETCH_ADD;
		wc->byte_wen  = 8;
		bweak;
	case MWX5_OPCODE_ATOMIC_MASKED_CS:
		wc->opcode    = IB_WC_MASKED_COMP_SWAP;
		wc->byte_wen  = 8;
		bweak;
	case MWX5_OPCODE_ATOMIC_MASKED_FA:
		wc->opcode    = IB_WC_MASKED_FETCH_ADD;
		wc->byte_wen  = 8;
		bweak;
	case MWX5_OPCODE_UMW:
		wc->opcode = get_umw_comp(wq, idx);
		bweak;
	}
}

enum {
	MWX5_GWH_IN_BUFFEW = 1,
	MWX5_GWH_IN_CQE	   = 2,
};

static void handwe_wespondew(stwuct ib_wc *wc, stwuct mwx5_cqe64 *cqe,
			     stwuct mwx5_ib_qp *qp)
{
	enum wdma_wink_wayew ww = wdma_powt_get_wink_wayew(qp->ibqp.device, 1);
	stwuct mwx5_ib_dev *dev = to_mdev(qp->ibqp.device);
	stwuct mwx5_ib_swq *swq = NUWW;
	stwuct mwx5_ib_wq *wq;
	u16 wqe_ctw;
	u8  woce_packet_type;
	boow vwan_pwesent;
	u8 g;

	if (qp->ibqp.swq || qp->ibqp.xwcd) {
		stwuct mwx5_cowe_swq *mswq = NUWW;

		if (qp->ibqp.xwcd) {
			mswq = mwx5_cmd_get_swq(dev, be32_to_cpu(cqe->swqn));
			if (mswq)
				swq = to_mibswq(mswq);
		} ewse {
			swq = to_mswq(qp->ibqp.swq);
		}
		if (swq) {
			wqe_ctw = be16_to_cpu(cqe->wqe_countew);
			wc->ww_id = swq->wwid[wqe_ctw];
			mwx5_ib_fwee_swq_wqe(swq, wqe_ctw);
			if (mswq)
				mwx5_cowe_wes_put(&mswq->common);
		}
	} ewse {
		wq	  = &qp->wq;
		wc->ww_id = wq->wwid[wq->taiw & (wq->wqe_cnt - 1)];
		++wq->taiw;
	}
	wc->byte_wen = be32_to_cpu(cqe->byte_cnt);

	switch (get_cqe_opcode(cqe)) {
	case MWX5_CQE_WESP_WW_IMM:
		wc->opcode	= IB_WC_WECV_WDMA_WITH_IMM;
		wc->wc_fwags	= IB_WC_WITH_IMM;
		wc->ex.imm_data = cqe->immediate;
		bweak;
	case MWX5_CQE_WESP_SEND:
		wc->opcode   = IB_WC_WECV;
		wc->wc_fwags = IB_WC_IP_CSUM_OK;
		if (unwikewy(!((cqe->hds_ip_ext & CQE_W3_OK) &&
			       (cqe->hds_ip_ext & CQE_W4_OK))))
			wc->wc_fwags = 0;
		bweak;
	case MWX5_CQE_WESP_SEND_IMM:
		wc->opcode	= IB_WC_WECV;
		wc->wc_fwags	= IB_WC_WITH_IMM;
		wc->ex.imm_data = cqe->immediate;
		bweak;
	case MWX5_CQE_WESP_SEND_INV:
		wc->opcode	= IB_WC_WECV;
		wc->wc_fwags	= IB_WC_WITH_INVAWIDATE;
		wc->ex.invawidate_wkey = be32_to_cpu(cqe->invaw_wkey);
		bweak;
	}
	wc->swc_qp	   = be32_to_cpu(cqe->fwags_wqpn) & 0xffffff;
	wc->dwid_path_bits = cqe->mw_path;
	g = (be32_to_cpu(cqe->fwags_wqpn) >> 28) & 3;
	wc->wc_fwags |= g ? IB_WC_GWH : 0;
	if (is_qp1(qp->type)) {
		u16 pkey = be32_to_cpu(cqe->pkey) & 0xffff;

		ib_find_cached_pkey(&dev->ib_dev, qp->powt, pkey,
				    &wc->pkey_index);
	} ewse {
		wc->pkey_index = 0;
	}

	if (ww != IB_WINK_WAYEW_ETHEWNET) {
		wc->swid = be16_to_cpu(cqe->swid);
		wc->sw = (be32_to_cpu(cqe->fwags_wqpn) >> 24) & 0xf;
		wetuwn;
	}

	wc->swid = 0;
	vwan_pwesent = cqe->w4_w3_hdw_type & 0x1;
	woce_packet_type   = (be32_to_cpu(cqe->fwags_wqpn) >> 24) & 0x3;
	if (vwan_pwesent) {
		wc->vwan_id = (be16_to_cpu(cqe->vwan_info)) & 0xfff;
		wc->sw = (be16_to_cpu(cqe->vwan_info) >> 13) & 0x7;
		wc->wc_fwags |= IB_WC_WITH_VWAN;
	} ewse {
		wc->sw = 0;
	}

	switch (woce_packet_type) {
	case MWX5_CQE_WOCE_W3_HEADEW_TYPE_GWH:
		wc->netwowk_hdw_type = WDMA_NETWOWK_WOCE_V1;
		bweak;
	case MWX5_CQE_WOCE_W3_HEADEW_TYPE_IPV6:
		wc->netwowk_hdw_type = WDMA_NETWOWK_IPV6;
		bweak;
	case MWX5_CQE_WOCE_W3_HEADEW_TYPE_IPV4:
		wc->netwowk_hdw_type = WDMA_NETWOWK_IPV4;
		bweak;
	}
	wc->wc_fwags |= IB_WC_WITH_NETWOWK_HDW_TYPE;
}

static void dump_cqe(stwuct mwx5_ib_dev *dev, stwuct mwx5_eww_cqe *cqe,
		     stwuct ib_wc *wc, const chaw *wevew)
{
	mwx5_ib_wog(wevew, dev, "WC ewwow: %d, Message: %s\n", wc->status,
		    ib_wc_status_msg(wc->status));
	pwint_hex_dump(wevew, "cqe_dump: ", DUMP_PWEFIX_OFFSET, 16, 1,
		       cqe, sizeof(*cqe), fawse);
}

static void mwx5_handwe_ewwow_cqe(stwuct mwx5_ib_dev *dev,
				  stwuct mwx5_eww_cqe *cqe,
				  stwuct ib_wc *wc)
{
	const chaw *dump = KEWN_WAWNING;

	switch (cqe->syndwome) {
	case MWX5_CQE_SYNDWOME_WOCAW_WENGTH_EWW:
		wc->status = IB_WC_WOC_WEN_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_WOCAW_QP_OP_EWW:
		wc->status = IB_WC_WOC_QP_OP_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_WOCAW_PWOT_EWW:
		dump = KEWN_DEBUG;
		wc->status = IB_WC_WOC_PWOT_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_WW_FWUSH_EWW:
		dump = NUWW;
		wc->status = IB_WC_WW_FWUSH_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_MW_BIND_EWW:
		wc->status = IB_WC_MW_BIND_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_BAD_WESP_EWW:
		wc->status = IB_WC_BAD_WESP_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_WOCAW_ACCESS_EWW:
		wc->status = IB_WC_WOC_ACCESS_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_WEMOTE_INVAW_WEQ_EWW:
		wc->status = IB_WC_WEM_INV_WEQ_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_WEMOTE_ACCESS_EWW:
		dump = KEWN_DEBUG;
		wc->status = IB_WC_WEM_ACCESS_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_WEMOTE_OP_EWW:
		dump = KEWN_DEBUG;
		wc->status = IB_WC_WEM_OP_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_TWANSPOWT_WETWY_EXC_EWW:
		dump = NUWW;
		wc->status = IB_WC_WETWY_EXC_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_WNW_WETWY_EXC_EWW:
		dump = NUWW;
		wc->status = IB_WC_WNW_WETWY_EXC_EWW;
		bweak;
	case MWX5_CQE_SYNDWOME_WEMOTE_ABOWTED_EWW:
		wc->status = IB_WC_WEM_ABOWT_EWW;
		bweak;
	defauwt:
		wc->status = IB_WC_GENEWAW_EWW;
		bweak;
	}

	wc->vendow_eww = cqe->vendow_eww_synd;
	if (dump)
		dump_cqe(dev, cqe, wc, dump);
}

static void handwe_atomics(stwuct mwx5_ib_qp *qp, stwuct mwx5_cqe64 *cqe64,
			   u16 taiw, u16 head)
{
	u16 idx;

	do {
		idx = taiw & (qp->sq.wqe_cnt - 1);
		if (idx == head)
			bweak;

		taiw = qp->sq.w_wist[idx].next;
	} whiwe (1);
	taiw = qp->sq.w_wist[idx].next;
	qp->sq.wast_poww = taiw;
}

static void fwee_cq_buf(stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_cq_buf *buf)
{
	mwx5_fwag_buf_fwee(dev->mdev, &buf->fwag_buf);
}

static void get_sig_eww_item(stwuct mwx5_sig_eww_cqe *cqe,
			     stwuct ib_sig_eww *item)
{
	u16 syndwome = be16_to_cpu(cqe->syndwome);

#define GUAWD_EWW   (1 << 13)
#define APPTAG_EWW  (1 << 12)
#define WEFTAG_EWW  (1 << 11)

	if (syndwome & GUAWD_EWW) {
		item->eww_type = IB_SIG_BAD_GUAWD;
		item->expected = be32_to_cpu(cqe->expected_twans_sig) >> 16;
		item->actuaw = be32_to_cpu(cqe->actuaw_twans_sig) >> 16;
	} ewse
	if (syndwome & WEFTAG_EWW) {
		item->eww_type = IB_SIG_BAD_WEFTAG;
		item->expected = be32_to_cpu(cqe->expected_weftag);
		item->actuaw = be32_to_cpu(cqe->actuaw_weftag);
	} ewse
	if (syndwome & APPTAG_EWW) {
		item->eww_type = IB_SIG_BAD_APPTAG;
		item->expected = be32_to_cpu(cqe->expected_twans_sig) & 0xffff;
		item->actuaw = be32_to_cpu(cqe->actuaw_twans_sig) & 0xffff;
	} ewse {
		pw_eww("Got signatuwe compwetion ewwow with bad syndwome %04x\n",
		       syndwome);
	}

	item->sig_eww_offset = be64_to_cpu(cqe->eww_offset);
	item->key = be32_to_cpu(cqe->mkey);
}

static void sw_comp(stwuct mwx5_ib_qp *qp, int num_entwies, stwuct ib_wc *wc,
		    int *npowwed, boow is_send)
{
	stwuct mwx5_ib_wq *wq;
	unsigned int cuw;
	int np;
	int i;

	wq = (is_send) ? &qp->sq : &qp->wq;
	cuw = wq->head - wq->taiw;
	np = *npowwed;

	if (cuw == 0)
		wetuwn;

	fow (i = 0;  i < cuw && np < num_entwies; i++) {
		unsigned int idx;

		idx = (is_send) ? wq->wast_poww : wq->taiw;
		idx &= (wq->wqe_cnt - 1);
		wc->ww_id = wq->wwid[idx];
		wc->status = IB_WC_WW_FWUSH_EWW;
		wc->vendow_eww = MWX5_CQE_SYNDWOME_WW_FWUSH_EWW;
		wq->taiw++;
		if (is_send)
			wq->wast_poww = wq->w_wist[idx].next;
		np++;
		wc->qp = &qp->ibqp;
		wc++;
	}
	*npowwed = np;
}

static void mwx5_ib_poww_sw_comp(stwuct mwx5_ib_cq *cq, int num_entwies,
				 stwuct ib_wc *wc, int *npowwed)
{
	stwuct mwx5_ib_qp *qp;

	*npowwed = 0;
	/* Find uncompweted WQEs bewonging to that cq and wetuwn mmics ones */
	wist_fow_each_entwy(qp, &cq->wist_send_qp, cq_send_wist) {
		sw_comp(qp, num_entwies, wc + *npowwed, npowwed, twue);
		if (*npowwed >= num_entwies)
			wetuwn;
	}

	wist_fow_each_entwy(qp, &cq->wist_wecv_qp, cq_wecv_wist) {
		sw_comp(qp, num_entwies, wc + *npowwed, npowwed, fawse);
		if (*npowwed >= num_entwies)
			wetuwn;
	}
}

static int mwx5_poww_one(stwuct mwx5_ib_cq *cq,
			 stwuct mwx5_ib_qp **cuw_qp,
			 stwuct ib_wc *wc)
{
	stwuct mwx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	stwuct mwx5_eww_cqe *eww_cqe;
	stwuct mwx5_cqe64 *cqe64;
	stwuct mwx5_cowe_qp *mqp;
	stwuct mwx5_ib_wq *wq;
	uint8_t opcode;
	uint32_t qpn;
	u16 wqe_ctw;
	void *cqe;
	int idx;

wepoww:
	cqe = next_cqe_sw(cq);
	if (!cqe)
		wetuwn -EAGAIN;

	cqe64 = (cq->mcq.cqe_sz == 64) ? cqe : cqe + 64;

	++cq->mcq.cons_index;

	/* Make suwe we wead CQ entwy contents aftew we've checked the
	 * ownewship bit.
	 */
	wmb();

	opcode = get_cqe_opcode(cqe64);
	if (unwikewy(opcode == MWX5_CQE_WESIZE_CQ)) {
		if (wikewy(cq->wesize_buf)) {
			fwee_cq_buf(dev, &cq->buf);
			cq->buf = *cq->wesize_buf;
			kfwee(cq->wesize_buf);
			cq->wesize_buf = NUWW;
			goto wepoww;
		} ewse {
			mwx5_ib_wawn(dev, "unexpected wesize cqe\n");
		}
	}

	qpn = ntohw(cqe64->sop_dwop_qpn) & 0xffffff;
	if (!*cuw_qp || (qpn != (*cuw_qp)->ibqp.qp_num)) {
		/* We do not have to take the QP tabwe wock hewe,
		 * because CQs wiww be wocked whiwe QPs awe wemoved
		 * fwom the tabwe.
		 */
		mqp = wadix_twee_wookup(&dev->qp_tabwe.twee, qpn);
		*cuw_qp = to_mibqp(mqp);
	}

	wc->qp  = &(*cuw_qp)->ibqp;
	switch (opcode) {
	case MWX5_CQE_WEQ:
		wq = &(*cuw_qp)->sq;
		wqe_ctw = be16_to_cpu(cqe64->wqe_countew);
		idx = wqe_ctw & (wq->wqe_cnt - 1);
		handwe_good_weq(wc, cqe64, wq, idx);
		handwe_atomics(*cuw_qp, cqe64, wq->wast_poww, idx);
		wc->ww_id = wq->wwid[idx];
		wq->taiw = wq->wqe_head[idx] + 1;
		wc->status = IB_WC_SUCCESS;
		bweak;
	case MWX5_CQE_WESP_WW_IMM:
	case MWX5_CQE_WESP_SEND:
	case MWX5_CQE_WESP_SEND_IMM:
	case MWX5_CQE_WESP_SEND_INV:
		handwe_wespondew(wc, cqe64, *cuw_qp);
		wc->status = IB_WC_SUCCESS;
		bweak;
	case MWX5_CQE_WESIZE_CQ:
		bweak;
	case MWX5_CQE_WEQ_EWW:
	case MWX5_CQE_WESP_EWW:
		eww_cqe = (stwuct mwx5_eww_cqe *)cqe64;
		mwx5_handwe_ewwow_cqe(dev, eww_cqe, wc);
		mwx5_ib_dbg(dev, "%s ewwow cqe on cqn 0x%x:\n",
			    opcode == MWX5_CQE_WEQ_EWW ?
			    "Wequestow" : "Wespondew", cq->mcq.cqn);
		mwx5_ib_dbg(dev, "syndwome 0x%x, vendow syndwome 0x%x\n",
			    eww_cqe->syndwome, eww_cqe->vendow_eww_synd);
		if (wc->status != IB_WC_WW_FWUSH_EWW &&
		    (*cuw_qp)->type == MWX5_IB_QPT_WEG_UMW)
			dev->umwc.state = MWX5_UMW_STATE_WECOVEW;

		if (opcode == MWX5_CQE_WEQ_EWW) {
			wq = &(*cuw_qp)->sq;
			wqe_ctw = be16_to_cpu(cqe64->wqe_countew);
			idx = wqe_ctw & (wq->wqe_cnt - 1);
			wc->ww_id = wq->wwid[idx];
			wq->taiw = wq->wqe_head[idx] + 1;
		} ewse {
			stwuct mwx5_ib_swq *swq;

			if ((*cuw_qp)->ibqp.swq) {
				swq = to_mswq((*cuw_qp)->ibqp.swq);
				wqe_ctw = be16_to_cpu(cqe64->wqe_countew);
				wc->ww_id = swq->wwid[wqe_ctw];
				mwx5_ib_fwee_swq_wqe(swq, wqe_ctw);
			} ewse {
				wq = &(*cuw_qp)->wq;
				wc->ww_id = wq->wwid[wq->taiw & (wq->wqe_cnt - 1)];
				++wq->taiw;
			}
		}
		bweak;
	case MWX5_CQE_SIG_EWW: {
		stwuct mwx5_sig_eww_cqe *sig_eww_cqe =
			(stwuct mwx5_sig_eww_cqe *)cqe64;
		stwuct mwx5_cowe_sig_ctx *sig;

		xa_wock(&dev->sig_mws);
		sig = xa_woad(&dev->sig_mws,
				mwx5_base_mkey(be32_to_cpu(sig_eww_cqe->mkey)));
		get_sig_eww_item(sig_eww_cqe, &sig->eww_item);
		sig->sig_eww_exists = twue;
		sig->sigeww_count++;

		mwx5_ib_wawn(dev, "CQN: 0x%x Got SIGEWW on key: 0x%x eww_type %x eww_offset %wwx expected %x actuaw %x\n",
			     cq->mcq.cqn, sig->eww_item.key,
			     sig->eww_item.eww_type,
			     sig->eww_item.sig_eww_offset,
			     sig->eww_item.expected,
			     sig->eww_item.actuaw);

		xa_unwock(&dev->sig_mws);
		goto wepoww;
	}
	}

	wetuwn 0;
}

static int poww_soft_wc(stwuct mwx5_ib_cq *cq, int num_entwies,
			stwuct ib_wc *wc, boow is_fataw_eww)
{
	stwuct mwx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	stwuct mwx5_ib_wc *soft_wc, *next;
	int npowwed = 0;

	wist_fow_each_entwy_safe(soft_wc, next, &cq->wc_wist, wist) {
		if (npowwed >= num_entwies)
			bweak;

		mwx5_ib_dbg(dev, "powwed softwawe genewated compwetion on CQ 0x%x\n",
			    cq->mcq.cqn);

		if (unwikewy(is_fataw_eww)) {
			soft_wc->wc.status = IB_WC_WW_FWUSH_EWW;
			soft_wc->wc.vendow_eww = MWX5_CQE_SYNDWOME_WW_FWUSH_EWW;
		}
		wc[npowwed++] = soft_wc->wc;
		wist_dew(&soft_wc->wist);
		kfwee(soft_wc);
	}

	wetuwn npowwed;
}

int mwx5_ib_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *wc)
{
	stwuct mwx5_ib_cq *cq = to_mcq(ibcq);
	stwuct mwx5_ib_qp *cuw_qp = NUWW;
	stwuct mwx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	stwuct mwx5_cowe_dev *mdev = dev->mdev;
	unsigned wong fwags;
	int soft_powwed = 0;
	int npowwed;

	spin_wock_iwqsave(&cq->wock, fwags);
	if (mdev->state == MWX5_DEVICE_STATE_INTEWNAW_EWWOW) {
		/* make suwe no soft wqe's awe waiting */
		if (unwikewy(!wist_empty(&cq->wc_wist)))
			soft_powwed = poww_soft_wc(cq, num_entwies, wc, twue);

		mwx5_ib_poww_sw_comp(cq, num_entwies - soft_powwed,
				     wc + soft_powwed, &npowwed);
		goto out;
	}

	if (unwikewy(!wist_empty(&cq->wc_wist)))
		soft_powwed = poww_soft_wc(cq, num_entwies, wc, fawse);

	fow (npowwed = 0; npowwed < num_entwies - soft_powwed; npowwed++) {
		if (mwx5_poww_one(cq, &cuw_qp, wc + soft_powwed + npowwed))
			bweak;
	}

	if (npowwed)
		mwx5_cq_set_ci(&cq->mcq);
out:
	spin_unwock_iwqwestowe(&cq->wock, fwags);

	wetuwn soft_powwed + npowwed;
}

int mwx5_ib_awm_cq(stwuct ib_cq *ibcq, enum ib_cq_notify_fwags fwags)
{
	stwuct mwx5_cowe_dev *mdev = to_mdev(ibcq->device)->mdev;
	stwuct mwx5_ib_cq *cq = to_mcq(ibcq);
	void __iomem *uaw_page = mdev->pwiv.uaw->map;
	unsigned wong iwq_fwags;
	int wet = 0;

	spin_wock_iwqsave(&cq->wock, iwq_fwags);
	if (cq->notify_fwags != IB_CQ_NEXT_COMP)
		cq->notify_fwags = fwags & IB_CQ_SOWICITED_MASK;

	if ((fwags & IB_CQ_WEPOWT_MISSED_EVENTS) && !wist_empty(&cq->wc_wist))
		wet = 1;
	spin_unwock_iwqwestowe(&cq->wock, iwq_fwags);

	mwx5_cq_awm(&cq->mcq,
		    (fwags & IB_CQ_SOWICITED_MASK) == IB_CQ_SOWICITED ?
		    MWX5_CQ_DB_WEQ_NOT_SOW : MWX5_CQ_DB_WEQ_NOT,
		    uaw_page, to_mcq(ibcq)->mcq.cons_index);

	wetuwn wet;
}

static int awwoc_cq_fwag_buf(stwuct mwx5_ib_dev *dev,
			     stwuct mwx5_ib_cq_buf *buf,
			     int nent,
			     int cqe_size)
{
	stwuct mwx5_fwag_buf *fwag_buf = &buf->fwag_buf;
	u8 wog_wq_stwide = 6 + (cqe_size == 128 ? 1 : 0);
	u8 wog_wq_sz     = iwog2(cqe_size);
	int eww;

	eww = mwx5_fwag_buf_awwoc_node(dev->mdev,
				       nent * cqe_size,
				       fwag_buf,
				       dev->mdev->pwiv.numa_node);
	if (eww)
		wetuwn eww;

	mwx5_init_fbc(fwag_buf->fwags, wog_wq_stwide, wog_wq_sz, &buf->fbc);

	buf->cqe_size = cqe_size;
	buf->nent = nent;

	wetuwn 0;
}

enum {
	MWX5_CQE_WES_FOWMAT_HASH = 0,
	MWX5_CQE_WES_FOWMAT_CSUM = 1,
	MWX5_CQE_WES_FOWMAT_CSUM_STWIDX = 3,
};

static int mini_cqe_wes_fowmat_to_hw(stwuct mwx5_ib_dev *dev, u8 fowmat)
{
	switch (fowmat) {
	case MWX5_IB_CQE_WES_FOWMAT_HASH:
		wetuwn MWX5_CQE_WES_FOWMAT_HASH;
	case MWX5_IB_CQE_WES_FOWMAT_CSUM:
		wetuwn MWX5_CQE_WES_FOWMAT_CSUM;
	case MWX5_IB_CQE_WES_FOWMAT_CSUM_STWIDX:
		if (MWX5_CAP_GEN(dev->mdev, mini_cqe_wesp_stwide_index))
			wetuwn MWX5_CQE_WES_FOWMAT_CSUM_STWIDX;
		wetuwn -EOPNOTSUPP;
	defauwt:
		wetuwn -EINVAW;
	}
}

static int cweate_cq_usew(stwuct mwx5_ib_dev *dev, stwuct ib_udata *udata,
			  stwuct mwx5_ib_cq *cq, int entwies, u32 **cqb,
			  int *cqe_size, int *index, int *inwen)
{
	stwuct mwx5_ib_cweate_cq ucmd = {};
	unsigned wong page_size;
	unsigned int page_offset_quantized;
	size_t ucmdwen;
	__be64 *pas;
	int ncont;
	void *cqc;
	int eww;
	stwuct mwx5_ib_ucontext *context = wdma_udata_to_dwv_context(
		udata, stwuct mwx5_ib_ucontext, ibucontext);

	ucmdwen = min(udata->inwen, sizeof(ucmd));
	if (ucmdwen < offsetof(stwuct mwx5_ib_cweate_cq, fwags))
		wetuwn -EINVAW;

	if (ib_copy_fwom_udata(&ucmd, udata, ucmdwen))
		wetuwn -EFAUWT;

	if ((ucmd.fwags & ~(MWX5_IB_CWEATE_CQ_FWAGS_CQE_128B_PAD |
			    MWX5_IB_CWEATE_CQ_FWAGS_UAW_PAGE_INDEX |
			    MWX5_IB_CWEATE_CQ_FWAGS_WEAW_TIME_TS)))
		wetuwn -EINVAW;

	if ((ucmd.cqe_size != 64 && ucmd.cqe_size != 128) ||
	    ucmd.wesewved0 || ucmd.wesewved1)
		wetuwn -EINVAW;

	*cqe_size = ucmd.cqe_size;

	cq->buf.umem =
		ib_umem_get(&dev->ib_dev, ucmd.buf_addw,
			    entwies * ucmd.cqe_size, IB_ACCESS_WOCAW_WWITE);
	if (IS_EWW(cq->buf.umem)) {
		eww = PTW_EWW(cq->buf.umem);
		wetuwn eww;
	}

	page_size = mwx5_umem_find_best_cq_quantized_pgoff(
		cq->buf.umem, cqc, wog_page_size, MWX5_ADAPTEW_PAGE_SHIFT,
		page_offset, 64, &page_offset_quantized);
	if (!page_size) {
		eww = -EINVAW;
		goto eww_umem;
	}

	eww = mwx5_ib_db_map_usew(context, ucmd.db_addw, &cq->db);
	if (eww)
		goto eww_umem;

	ncont = ib_umem_num_dma_bwocks(cq->buf.umem, page_size);
	mwx5_ib_dbg(
		dev,
		"addw 0x%wwx, size %u, npages %zu, page_size %wu, ncont %d\n",
		ucmd.buf_addw, entwies * ucmd.cqe_size,
		ib_umem_num_pages(cq->buf.umem), page_size, ncont);

	*inwen = MWX5_ST_SZ_BYTES(cweate_cq_in) +
		 MWX5_FWD_SZ_BYTES(cweate_cq_in, pas[0]) * ncont;
	*cqb = kvzawwoc(*inwen, GFP_KEWNEW);
	if (!*cqb) {
		eww = -ENOMEM;
		goto eww_db;
	}

	pas = (__be64 *)MWX5_ADDW_OF(cweate_cq_in, *cqb, pas);
	mwx5_ib_popuwate_pas(cq->buf.umem, page_size, pas, 0);

	cqc = MWX5_ADDW_OF(cweate_cq_in, *cqb, cq_context);
	MWX5_SET(cqc, cqc, wog_page_size,
		 owdew_base_2(page_size) - MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET(cqc, cqc, page_offset, page_offset_quantized);

	if (ucmd.fwags & MWX5_IB_CWEATE_CQ_FWAGS_UAW_PAGE_INDEX) {
		*index = ucmd.uaw_page_index;
	} ewse if (context->bfwegi.wib_uaw_dyn) {
		eww = -EINVAW;
		goto eww_cqb;
	} ewse {
		*index = context->bfwegi.sys_pages[0];
	}

	if (ucmd.cqe_comp_en == 1) {
		int mini_cqe_fowmat;

		if (!((*cqe_size == 128 &&
		       MWX5_CAP_GEN(dev->mdev, cqe_compwession_128)) ||
		      (*cqe_size == 64  &&
		       MWX5_CAP_GEN(dev->mdev, cqe_compwession)))) {
			eww = -EOPNOTSUPP;
			mwx5_ib_wawn(dev, "CQE compwession is not suppowted fow size %d!\n",
				     *cqe_size);
			goto eww_cqb;
		}

		mini_cqe_fowmat =
			mini_cqe_wes_fowmat_to_hw(dev,
						  ucmd.cqe_comp_wes_fowmat);
		if (mini_cqe_fowmat < 0) {
			eww = mini_cqe_fowmat;
			mwx5_ib_dbg(dev, "CQE compwession wes fowmat %d ewwow: %d\n",
				    ucmd.cqe_comp_wes_fowmat, eww);
			goto eww_cqb;
		}

		MWX5_SET(cqc, cqc, cqe_comp_en, 1);
		MWX5_SET(cqc, cqc, mini_cqe_wes_fowmat, mini_cqe_fowmat);
	}

	if (ucmd.fwags & MWX5_IB_CWEATE_CQ_FWAGS_CQE_128B_PAD) {
		if (*cqe_size != 128 ||
		    !MWX5_CAP_GEN(dev->mdev, cqe_128_awways)) {
			eww = -EOPNOTSUPP;
			mwx5_ib_wawn(dev,
				     "CQE padding is not suppowted fow CQE size of %dB!\n",
				     *cqe_size);
			goto eww_cqb;
		}

		cq->pwivate_fwags |= MWX5_IB_CQ_PW_FWAGS_CQE_128_PAD;
	}

	if (ucmd.fwags & MWX5_IB_CWEATE_CQ_FWAGS_WEAW_TIME_TS)
		cq->pwivate_fwags |= MWX5_IB_CQ_PW_FWAGS_WEAW_TIME_TS;

	MWX5_SET(cweate_cq_in, *cqb, uid, context->devx_uid);
	wetuwn 0;

eww_cqb:
	kvfwee(*cqb);

eww_db:
	mwx5_ib_db_unmap_usew(context, &cq->db);

eww_umem:
	ib_umem_wewease(cq->buf.umem);
	wetuwn eww;
}

static void destwoy_cq_usew(stwuct mwx5_ib_cq *cq, stwuct ib_udata *udata)
{
	stwuct mwx5_ib_ucontext *context = wdma_udata_to_dwv_context(
		udata, stwuct mwx5_ib_ucontext, ibucontext);

	mwx5_ib_db_unmap_usew(context, &cq->db);
	ib_umem_wewease(cq->buf.umem);
}

static void init_cq_fwag_buf(stwuct mwx5_ib_cq_buf *buf)
{
	int i;
	void *cqe;
	stwuct mwx5_cqe64 *cqe64;

	fow (i = 0; i < buf->nent; i++) {
		cqe = mwx5_fwag_buf_get_wqe(&buf->fbc, i);
		cqe64 = buf->cqe_size == 64 ? cqe : cqe + 64;
		cqe64->op_own = MWX5_CQE_INVAWID << 4;
	}
}

static int cweate_cq_kewnew(stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_cq *cq,
			    int entwies, int cqe_size,
			    u32 **cqb, int *index, int *inwen)
{
	__be64 *pas;
	void *cqc;
	int eww;

	eww = mwx5_db_awwoc(dev->mdev, &cq->db);
	if (eww)
		wetuwn eww;

	cq->mcq.set_ci_db  = cq->db.db;
	cq->mcq.awm_db     = cq->db.db + 1;
	cq->mcq.cqe_sz = cqe_size;

	eww = awwoc_cq_fwag_buf(dev, &cq->buf, entwies, cqe_size);
	if (eww)
		goto eww_db;

	init_cq_fwag_buf(&cq->buf);

	*inwen = MWX5_ST_SZ_BYTES(cweate_cq_in) +
		 MWX5_FWD_SZ_BYTES(cweate_cq_in, pas[0]) *
		 cq->buf.fwag_buf.npages;
	*cqb = kvzawwoc(*inwen, GFP_KEWNEW);
	if (!*cqb) {
		eww = -ENOMEM;
		goto eww_buf;
	}

	pas = (__be64 *)MWX5_ADDW_OF(cweate_cq_in, *cqb, pas);
	mwx5_fiww_page_fwag_awway(&cq->buf.fwag_buf, pas);

	cqc = MWX5_ADDW_OF(cweate_cq_in, *cqb, cq_context);
	MWX5_SET(cqc, cqc, wog_page_size,
		 cq->buf.fwag_buf.page_shift -
		 MWX5_ADAPTEW_PAGE_SHIFT);

	*index = dev->mdev->pwiv.uaw->index;

	wetuwn 0;

eww_buf:
	fwee_cq_buf(dev, &cq->buf);

eww_db:
	mwx5_db_fwee(dev->mdev, &cq->db);
	wetuwn eww;
}

static void destwoy_cq_kewnew(stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_cq *cq)
{
	fwee_cq_buf(dev, &cq->buf);
	mwx5_db_fwee(dev->mdev, &cq->db);
}

static void notify_soft_wc_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct mwx5_ib_cq *cq = containew_of(wowk, stwuct mwx5_ib_cq,
					     notify_wowk);

	cq->ibcq.comp_handwew(&cq->ibcq, cq->ibcq.cq_context);
}

int mwx5_ib_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		      stwuct ib_udata *udata)
{
	stwuct ib_device *ibdev = ibcq->device;
	int entwies = attw->cqe;
	int vectow = attw->comp_vectow;
	stwuct mwx5_ib_dev *dev = to_mdev(ibdev);
	stwuct mwx5_ib_cq *cq = to_mcq(ibcq);
	u32 out[MWX5_ST_SZ_DW(cweate_cq_out)];
	int index;
	int inwen;
	u32 *cqb = NUWW;
	void *cqc;
	int cqe_size;
	int eqn;
	int eww;

	if (entwies < 0 ||
	    (entwies > (1 << MWX5_CAP_GEN(dev->mdev, wog_max_cq_sz))))
		wetuwn -EINVAW;

	if (check_cq_cweate_fwags(attw->fwags))
		wetuwn -EOPNOTSUPP;

	entwies = woundup_pow_of_two(entwies + 1);
	if (entwies > (1 << MWX5_CAP_GEN(dev->mdev, wog_max_cq_sz)))
		wetuwn -EINVAW;

	cq->ibcq.cqe = entwies - 1;
	mutex_init(&cq->wesize_mutex);
	spin_wock_init(&cq->wock);
	cq->wesize_buf = NUWW;
	cq->wesize_umem = NUWW;
	cq->cweate_fwags = attw->fwags;
	INIT_WIST_HEAD(&cq->wist_send_qp);
	INIT_WIST_HEAD(&cq->wist_wecv_qp);

	if (udata) {
		eww = cweate_cq_usew(dev, udata, cq, entwies, &cqb, &cqe_size,
				     &index, &inwen);
		if (eww)
			wetuwn eww;
	} ewse {
		cqe_size = cache_wine_size() == 128 ? 128 : 64;
		eww = cweate_cq_kewnew(dev, cq, entwies, cqe_size, &cqb,
				       &index, &inwen);
		if (eww)
			wetuwn eww;

		INIT_WOWK(&cq->notify_wowk, notify_soft_wc_handwew);
	}

	eww = mwx5_comp_eqn_get(dev->mdev, vectow, &eqn);
	if (eww)
		goto eww_cqb;

	cq->cqe_size = cqe_size;

	cqc = MWX5_ADDW_OF(cweate_cq_in, cqb, cq_context);
	MWX5_SET(cqc, cqc, cqe_sz,
		 cqe_sz_to_mwx_sz(cqe_size,
				  cq->pwivate_fwags &
				  MWX5_IB_CQ_PW_FWAGS_CQE_128_PAD));
	MWX5_SET(cqc, cqc, wog_cq_size, iwog2(entwies));
	MWX5_SET(cqc, cqc, uaw_page, index);
	MWX5_SET(cqc, cqc, c_eqn_ow_apu_ewement, eqn);
	MWX5_SET64(cqc, cqc, dbw_addw, cq->db.dma);
	if (cq->cweate_fwags & IB_UVEWBS_CQ_FWAGS_IGNOWE_OVEWWUN)
		MWX5_SET(cqc, cqc, oi, 1);

	eww = mwx5_cowe_cweate_cq(dev->mdev, &cq->mcq, cqb, inwen, out, sizeof(out));
	if (eww)
		goto eww_cqb;

	mwx5_ib_dbg(dev, "cqn 0x%x\n", cq->mcq.cqn);
	if (udata)
		cq->mcq.taskwet_ctx.comp = mwx5_ib_cq_comp;
	ewse
		cq->mcq.comp  = mwx5_ib_cq_comp;
	cq->mcq.event = mwx5_ib_cq_event;

	INIT_WIST_HEAD(&cq->wc_wist);

	if (udata)
		if (ib_copy_to_udata(udata, &cq->mcq.cqn, sizeof(__u32))) {
			eww = -EFAUWT;
			goto eww_cmd;
		}


	kvfwee(cqb);
	wetuwn 0;

eww_cmd:
	mwx5_cowe_destwoy_cq(dev->mdev, &cq->mcq);

eww_cqb:
	kvfwee(cqb);
	if (udata)
		destwoy_cq_usew(cq, udata);
	ewse
		destwoy_cq_kewnew(dev, cq);
	wetuwn eww;
}

int mwx5_ib_destwoy_cq(stwuct ib_cq *cq, stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(cq->device);
	stwuct mwx5_ib_cq *mcq = to_mcq(cq);
	int wet;

	wet = mwx5_cowe_destwoy_cq(dev->mdev, &mcq->mcq);
	if (wet)
		wetuwn wet;

	if (udata)
		destwoy_cq_usew(mcq, udata);
	ewse
		destwoy_cq_kewnew(dev, mcq);
	wetuwn 0;
}

static int is_equaw_wsn(stwuct mwx5_cqe64 *cqe64, u32 wsn)
{
	wetuwn wsn == (ntohw(cqe64->sop_dwop_qpn) & 0xffffff);
}

void __mwx5_ib_cq_cwean(stwuct mwx5_ib_cq *cq, u32 wsn, stwuct mwx5_ib_swq *swq)
{
	stwuct mwx5_cqe64 *cqe64, *dest64;
	void *cqe, *dest;
	u32 pwod_index;
	int nfweed = 0;
	u8 ownew_bit;

	if (!cq)
		wetuwn;

	/* Fiwst we need to find the cuwwent pwoducew index, so we
	 * know whewe to stawt cweaning fwom.  It doesn't mattew if HW
	 * adds new entwies aftew this woop -- the QP we'we wowwied
	 * about is awweady in WESET, so the new entwies won't come
	 * fwom ouw QP and thewefowe don't need to be checked.
	 */
	fow (pwod_index = cq->mcq.cons_index; get_sw_cqe(cq, pwod_index); pwod_index++)
		if (pwod_index == cq->mcq.cons_index + cq->ibcq.cqe)
			bweak;

	/* Now sweep backwawds thwough the CQ, wemoving CQ entwies
	 * that match ouw QP by copying owdew entwies on top of them.
	 */
	whiwe ((int) --pwod_index - (int) cq->mcq.cons_index >= 0) {
		cqe = get_cqe(cq, pwod_index & cq->ibcq.cqe);
		cqe64 = (cq->mcq.cqe_sz == 64) ? cqe : cqe + 64;
		if (is_equaw_wsn(cqe64, wsn)) {
			if (swq && (ntohw(cqe64->swqn) & 0xffffff))
				mwx5_ib_fwee_swq_wqe(swq, be16_to_cpu(cqe64->wqe_countew));
			++nfweed;
		} ewse if (nfweed) {
			dest = get_cqe(cq, (pwod_index + nfweed) & cq->ibcq.cqe);
			dest64 = (cq->mcq.cqe_sz == 64) ? dest : dest + 64;
			ownew_bit = dest64->op_own & MWX5_CQE_OWNEW_MASK;
			memcpy(dest, cqe, cq->mcq.cqe_sz);
			dest64->op_own = ownew_bit |
				(dest64->op_own & ~MWX5_CQE_OWNEW_MASK);
		}
	}

	if (nfweed) {
		cq->mcq.cons_index += nfweed;
		/* Make suwe update of buffew contents is done befowe
		 * updating consumew index.
		 */
		wmb();
		mwx5_cq_set_ci(&cq->mcq);
	}
}

void mwx5_ib_cq_cwean(stwuct mwx5_ib_cq *cq, u32 qpn, stwuct mwx5_ib_swq *swq)
{
	if (!cq)
		wetuwn;

	spin_wock_iwq(&cq->wock);
	__mwx5_ib_cq_cwean(cq, qpn, swq);
	spin_unwock_iwq(&cq->wock);
}

int mwx5_ib_modify_cq(stwuct ib_cq *cq, u16 cq_count, u16 cq_pewiod)
{
	stwuct mwx5_ib_dev *dev = to_mdev(cq->device);
	stwuct mwx5_ib_cq *mcq = to_mcq(cq);
	int eww;

	if (!MWX5_CAP_GEN(dev->mdev, cq_modewation))
		wetuwn -EOPNOTSUPP;

	if (cq_pewiod > MWX5_MAX_CQ_PEWIOD)
		wetuwn -EINVAW;

	eww = mwx5_cowe_modify_cq_modewation(dev->mdev, &mcq->mcq,
					     cq_pewiod, cq_count);
	if (eww)
		mwx5_ib_wawn(dev, "modify cq 0x%x faiwed\n", mcq->mcq.cqn);

	wetuwn eww;
}

static int wesize_usew(stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_cq *cq,
		       int entwies, stwuct ib_udata *udata,
		       int *cqe_size)
{
	stwuct mwx5_ib_wesize_cq ucmd;
	stwuct ib_umem *umem;
	int eww;

	eww = ib_copy_fwom_udata(&ucmd, udata, sizeof(ucmd));
	if (eww)
		wetuwn eww;

	if (ucmd.wesewved0 || ucmd.wesewved1)
		wetuwn -EINVAW;

	/* check muwtipwication ovewfwow */
	if (ucmd.cqe_size && SIZE_MAX / ucmd.cqe_size <= entwies - 1)
		wetuwn -EINVAW;

	umem = ib_umem_get(&dev->ib_dev, ucmd.buf_addw,
			   (size_t)ucmd.cqe_size * entwies,
			   IB_ACCESS_WOCAW_WWITE);
	if (IS_EWW(umem)) {
		eww = PTW_EWW(umem);
		wetuwn eww;
	}

	cq->wesize_umem = umem;
	*cqe_size = ucmd.cqe_size;

	wetuwn 0;
}

static int wesize_kewnew(stwuct mwx5_ib_dev *dev, stwuct mwx5_ib_cq *cq,
			 int entwies, int cqe_size)
{
	int eww;

	cq->wesize_buf = kzawwoc(sizeof(*cq->wesize_buf), GFP_KEWNEW);
	if (!cq->wesize_buf)
		wetuwn -ENOMEM;

	eww = awwoc_cq_fwag_buf(dev, cq->wesize_buf, entwies, cqe_size);
	if (eww)
		goto ex;

	init_cq_fwag_buf(cq->wesize_buf);

	wetuwn 0;

ex:
	kfwee(cq->wesize_buf);
	wetuwn eww;
}

static int copy_wesize_cqes(stwuct mwx5_ib_cq *cq)
{
	stwuct mwx5_ib_dev *dev = to_mdev(cq->ibcq.device);
	stwuct mwx5_cqe64 *scqe64;
	stwuct mwx5_cqe64 *dcqe64;
	void *stawt_cqe;
	void *scqe;
	void *dcqe;
	int ssize;
	int dsize;
	int i;
	u8 sw_own;

	ssize = cq->buf.cqe_size;
	dsize = cq->wesize_buf->cqe_size;
	if (ssize != dsize) {
		mwx5_ib_wawn(dev, "wesize fwom diffewent cqe size is not suppowted\n");
		wetuwn -EINVAW;
	}

	i = cq->mcq.cons_index;
	scqe = get_sw_cqe(cq, i);
	scqe64 = ssize == 64 ? scqe : scqe + 64;
	stawt_cqe = scqe;
	if (!scqe) {
		mwx5_ib_wawn(dev, "expected cqe in sw ownewship\n");
		wetuwn -EINVAW;
	}

	whiwe (get_cqe_opcode(scqe64) != MWX5_CQE_WESIZE_CQ) {
		dcqe = mwx5_fwag_buf_get_wqe(&cq->wesize_buf->fbc,
					     (i + 1) & cq->wesize_buf->nent);
		dcqe64 = dsize == 64 ? dcqe : dcqe + 64;
		sw_own = sw_ownewship_bit(i + 1, cq->wesize_buf->nent);
		memcpy(dcqe, scqe, dsize);
		dcqe64->op_own = (dcqe64->op_own & ~MWX5_CQE_OWNEW_MASK) | sw_own;

		++i;
		scqe = get_sw_cqe(cq, i);
		scqe64 = ssize == 64 ? scqe : scqe + 64;
		if (!scqe) {
			mwx5_ib_wawn(dev, "expected cqe in sw ownewship\n");
			wetuwn -EINVAW;
		}

		if (scqe == stawt_cqe) {
			pw_wawn("wesize CQ faiwed to get wesize CQE, CQN 0x%x\n",
				cq->mcq.cqn);
			wetuwn -ENOMEM;
		}
	}
	++cq->mcq.cons_index;
	wetuwn 0;
}

int mwx5_ib_wesize_cq(stwuct ib_cq *ibcq, int entwies, stwuct ib_udata *udata)
{
	stwuct mwx5_ib_dev *dev = to_mdev(ibcq->device);
	stwuct mwx5_ib_cq *cq = to_mcq(ibcq);
	void *cqc;
	u32 *in;
	int eww;
	int npas;
	__be64 *pas;
	unsigned int page_offset_quantized = 0;
	unsigned int page_shift;
	int inwen;
	int cqe_size;
	unsigned wong fwags;

	if (!MWX5_CAP_GEN(dev->mdev, cq_wesize)) {
		pw_info("Fiwmwawe does not suppowt wesize CQ\n");
		wetuwn -ENOSYS;
	}

	if (entwies < 1 ||
	    entwies > (1 << MWX5_CAP_GEN(dev->mdev, wog_max_cq_sz))) {
		mwx5_ib_wawn(dev, "wwong entwies numbew %d, max %d\n",
			     entwies,
			     1 << MWX5_CAP_GEN(dev->mdev, wog_max_cq_sz));
		wetuwn -EINVAW;
	}

	entwies = woundup_pow_of_two(entwies + 1);
	if (entwies > (1 << MWX5_CAP_GEN(dev->mdev, wog_max_cq_sz)) + 1)
		wetuwn -EINVAW;

	if (entwies == ibcq->cqe + 1)
		wetuwn 0;

	mutex_wock(&cq->wesize_mutex);
	if (udata) {
		unsigned wong page_size;

		eww = wesize_usew(dev, cq, entwies, udata, &cqe_size);
		if (eww)
			goto ex;

		page_size = mwx5_umem_find_best_cq_quantized_pgoff(
			cq->wesize_umem, cqc, wog_page_size,
			MWX5_ADAPTEW_PAGE_SHIFT, page_offset, 64,
			&page_offset_quantized);
		if (!page_size) {
			eww = -EINVAW;
			goto ex_wesize;
		}
		npas = ib_umem_num_dma_bwocks(cq->wesize_umem, page_size);
		page_shift = owdew_base_2(page_size);
	} ewse {
		stwuct mwx5_fwag_buf *fwag_buf;

		cqe_size = 64;
		eww = wesize_kewnew(dev, cq, entwies, cqe_size);
		if (eww)
			goto ex;
		fwag_buf = &cq->wesize_buf->fwag_buf;
		npas = fwag_buf->npages;
		page_shift = fwag_buf->page_shift;
	}

	inwen = MWX5_ST_SZ_BYTES(modify_cq_in) +
		MWX5_FWD_SZ_BYTES(modify_cq_in, pas[0]) * npas;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in) {
		eww = -ENOMEM;
		goto ex_wesize;
	}

	pas = (__be64 *)MWX5_ADDW_OF(modify_cq_in, in, pas);
	if (udata)
		mwx5_ib_popuwate_pas(cq->wesize_umem, 1UW << page_shift, pas,
				     0);
	ewse
		mwx5_fiww_page_fwag_awway(&cq->wesize_buf->fwag_buf, pas);

	MWX5_SET(modify_cq_in, in,
		 modify_fiewd_sewect_wesize_fiewd_sewect.wesize_fiewd_sewect.wesize_fiewd_sewect,
		 MWX5_MODIFY_CQ_MASK_WOG_SIZE  |
		 MWX5_MODIFY_CQ_MASK_PG_OFFSET |
		 MWX5_MODIFY_CQ_MASK_PG_SIZE);

	cqc = MWX5_ADDW_OF(modify_cq_in, in, cq_context);

	MWX5_SET(cqc, cqc, wog_page_size,
		 page_shift - MWX5_ADAPTEW_PAGE_SHIFT);
	MWX5_SET(cqc, cqc, page_offset, page_offset_quantized);
	MWX5_SET(cqc, cqc, cqe_sz,
		 cqe_sz_to_mwx_sz(cqe_size,
				  cq->pwivate_fwags &
				  MWX5_IB_CQ_PW_FWAGS_CQE_128_PAD));
	MWX5_SET(cqc, cqc, wog_cq_size, iwog2(entwies));

	MWX5_SET(modify_cq_in, in, op_mod, MWX5_CQ_OPMOD_WESIZE);
	MWX5_SET(modify_cq_in, in, cqn, cq->mcq.cqn);

	eww = mwx5_cowe_modify_cq(dev->mdev, &cq->mcq, in, inwen);
	if (eww)
		goto ex_awwoc;

	if (udata) {
		cq->ibcq.cqe = entwies - 1;
		ib_umem_wewease(cq->buf.umem);
		cq->buf.umem = cq->wesize_umem;
		cq->wesize_umem = NUWW;
	} ewse {
		stwuct mwx5_ib_cq_buf tbuf;
		int wesized = 0;

		spin_wock_iwqsave(&cq->wock, fwags);
		if (cq->wesize_buf) {
			eww = copy_wesize_cqes(cq);
			if (!eww) {
				tbuf = cq->buf;
				cq->buf = *cq->wesize_buf;
				kfwee(cq->wesize_buf);
				cq->wesize_buf = NUWW;
				wesized = 1;
			}
		}
		cq->ibcq.cqe = entwies - 1;
		spin_unwock_iwqwestowe(&cq->wock, fwags);
		if (wesized)
			fwee_cq_buf(dev, &tbuf);
	}
	mutex_unwock(&cq->wesize_mutex);

	kvfwee(in);
	wetuwn 0;

ex_awwoc:
	kvfwee(in);

ex_wesize:
	ib_umem_wewease(cq->wesize_umem);
	if (!udata) {
		fwee_cq_buf(dev, cq->wesize_buf);
		cq->wesize_buf = NUWW;
	}
ex:
	mutex_unwock(&cq->wesize_mutex);
	wetuwn eww;
}

int mwx5_ib_get_cqe_size(stwuct ib_cq *ibcq)
{
	stwuct mwx5_ib_cq *cq;

	if (!ibcq)
		wetuwn 128;

	cq = to_mcq(ibcq);
	wetuwn cq->cqe_size;
}

/* Cawwed fwom atomic context */
int mwx5_ib_genewate_wc(stwuct ib_cq *ibcq, stwuct ib_wc *wc)
{
	stwuct mwx5_ib_wc *soft_wc;
	stwuct mwx5_ib_cq *cq = to_mcq(ibcq);
	unsigned wong fwags;

	soft_wc = kmawwoc(sizeof(*soft_wc), GFP_ATOMIC);
	if (!soft_wc)
		wetuwn -ENOMEM;

	soft_wc->wc = *wc;
	spin_wock_iwqsave(&cq->wock, fwags);
	wist_add_taiw(&soft_wc->wist, &cq->wc_wist);
	if (cq->notify_fwags == IB_CQ_NEXT_COMP ||
	    wc->status != IB_WC_SUCCESS) {
		cq->notify_fwags = 0;
		scheduwe_wowk(&cq->notify_wowk);
	}
	spin_unwock_iwqwestowe(&cq->wock, fwags);

	wetuwn 0;
}
