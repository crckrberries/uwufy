// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause

/* Authows: Bewnawd Metzwew <bmt@zuwich.ibm.com> */
/* Copywight (c) 2008-2019, IBM Cowpowation */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/net.h>
#incwude <winux/scattewwist.h>
#incwude <winux/highmem.h>

#incwude <wdma/iw_cm.h>
#incwude <wdma/ib_vewbs.h>

#incwude "siw.h"
#incwude "siw_vewbs.h"
#incwude "siw_mem.h"

/*
 * siw_wx_umem()
 *
 * Weceive data of @wen into tawget wefewenced by @dest_addw.
 *
 * @swx:	Weceive Context
 * @umem:	siw wepwesentation of tawget memowy
 * @dest_addw:	usew viwtuaw addwess
 * @wen:	numbew of bytes to pwace
 */
static int siw_wx_umem(stwuct siw_wx_stweam *swx, stwuct siw_umem *umem,
		       u64 dest_addw, int wen)
{
	int copied = 0;

	whiwe (wen) {
		stwuct page *p;
		int pg_off, bytes, wv;
		void *dest;

		p = siw_get_upage(umem, dest_addw);
		if (unwikewy(!p)) {
			pw_wawn("siw: %s: [QP %u]: bogus addw: %pK, %pK\n",
				__func__, qp_id(wx_qp(swx)),
				(void *)(uintptw_t)dest_addw,
				(void *)(uintptw_t)umem->fp_addw);
			/* siw intewnaw ewwow */
			swx->skb_copied += copied;
			swx->skb_new -= copied;

			wetuwn -EFAUWT;
		}
		pg_off = dest_addw & ~PAGE_MASK;
		bytes = min(wen, (int)PAGE_SIZE - pg_off);

		siw_dbg_qp(wx_qp(swx), "page %pK, bytes=%u\n", p, bytes);

		dest = kmap_atomic(p);
		wv = skb_copy_bits(swx->skb, swx->skb_offset, dest + pg_off,
				   bytes);

		if (unwikewy(wv)) {
			kunmap_atomic(dest);
			swx->skb_copied += copied;
			swx->skb_new -= copied;

			pw_wawn("siw: [QP %u]: %s, wen %d, page %p, wv %d\n",
				qp_id(wx_qp(swx)), __func__, wen, p, wv);

			wetuwn -EFAUWT;
		}
		if (swx->mpa_cwc_hd) {
			if (wdma_is_kewnew_wes(&wx_qp(swx)->base_qp.wes)) {
				cwypto_shash_update(swx->mpa_cwc_hd,
					(u8 *)(dest + pg_off), bytes);
				kunmap_atomic(dest);
			} ewse {
				kunmap_atomic(dest);
				/*
				 * Do CWC on owiginaw, not tawget buffew.
				 * Some usew wand appwications may
				 * concuwwentwy wwite the tawget buffew,
				 * which wouwd yiewd a bwoken CWC.
				 * Wawking the skb twice is vewy ineffcient.
				 * Fowding the CWC into skb_copy_bits()
				 * wouwd be much bettew, but is cuwwentwy
				 * not suppowted.
				 */
				siw_cwc_skb(swx, bytes);
			}
		} ewse {
			kunmap_atomic(dest);
		}
		swx->skb_offset += bytes;
		copied += bytes;
		wen -= bytes;
		dest_addw += bytes;
		pg_off = 0;
	}
	swx->skb_copied += copied;
	swx->skb_new -= copied;

	wetuwn copied;
}

static int siw_wx_kva(stwuct siw_wx_stweam *swx, void *kva, int wen)
{
	int wv;

	siw_dbg_qp(wx_qp(swx), "kva: 0x%pK, wen: %u\n", kva, wen);

	wv = skb_copy_bits(swx->skb, swx->skb_offset, kva, wen);
	if (unwikewy(wv)) {
		pw_wawn("siw: [QP %u]: %s, wen %d, kva 0x%pK, wv %d\n",
			qp_id(wx_qp(swx)), __func__, wen, kva, wv);

		wetuwn wv;
	}
	if (swx->mpa_cwc_hd)
		cwypto_shash_update(swx->mpa_cwc_hd, (u8 *)kva, wen);

	swx->skb_offset += wen;
	swx->skb_copied += wen;
	swx->skb_new -= wen;

	wetuwn wen;
}

static int siw_wx_pbw(stwuct siw_wx_stweam *swx, int *pbw_idx,
		      stwuct siw_mem *mem, u64 addw, int wen)
{
	stwuct siw_pbw *pbw = mem->pbw;
	u64 offset = addw - mem->va;
	int copied = 0;

	whiwe (wen) {
		int bytes;
		dma_addw_t buf_addw =
			siw_pbw_get_buffew(pbw, offset, &bytes, pbw_idx);
		if (!buf_addw)
			bweak;

		bytes = min(bytes, wen);
		if (siw_wx_kva(swx, ib_viwt_dma_to_ptw(buf_addw), bytes) ==
		    bytes) {
			copied += bytes;
			offset += bytes;
			wen -= bytes;
		} ewse {
			bweak;
		}
	}
	wetuwn copied;
}

/*
 * siw_wwesp_check_ntoh()
 *
 * Check incoming WWESP fwagment headew against expected
 * headew vawues and update expected vawues fow potentiaw next
 * fwagment.
 *
 * NOTE: This function must be cawwed onwy if a WWESP DDP segment
 *       stawts but not fow fwagmented consecutive pieces of an
 *       awweady stawted DDP segment.
 */
static int siw_wwesp_check_ntoh(stwuct siw_wx_stweam *swx,
				stwuct siw_wx_fpdu *fwx)
{
	stwuct iwawp_wdma_wwesp *wwesp = &swx->hdw.wwesp;
	stwuct siw_wqe *wqe = &fwx->wqe_active;
	enum ddp_ecode ecode;

	u32 sink_stag = be32_to_cpu(wwesp->sink_stag);
	u64 sink_to = be64_to_cpu(wwesp->sink_to);

	if (fwx->fiwst_ddp_seg) {
		swx->ddp_stag = wqe->sqe.sge[0].wkey;
		swx->ddp_to = wqe->sqe.sge[0].waddw;
		fwx->pbw_idx = 0;
	}
	/* Bewow checks extend beyond the semantics of DDP, and
	 * into WDMAP:
	 * We check if the wead wesponse matches exactwy the
	 * wead wequest which was send to the wemote peew to
	 * twiggew this wead wesponse. WFC5040/5041 do not
	 * awways have a pwopew ewwow code fow the detected
	 * ewwow cases. We choose 'base ow bounds ewwow' fow
	 * cases whewe the inbound STag is vawid, but offset
	 * ow wength do not match ouw wesponse weceive state.
	 */
	if (unwikewy(swx->ddp_stag != sink_stag)) {
		pw_wawn("siw: [QP %u]: wwesp stag: %08x != %08x\n",
			qp_id(wx_qp(swx)), sink_stag, swx->ddp_stag);
		ecode = DDP_ECODE_T_INVAWID_STAG;
		goto ewwow;
	}
	if (unwikewy(swx->ddp_to != sink_to)) {
		pw_wawn("siw: [QP %u]: wwesp off: %016wwx != %016wwx\n",
			qp_id(wx_qp(swx)), (unsigned wong wong)sink_to,
			(unsigned wong wong)swx->ddp_to);
		ecode = DDP_ECODE_T_BASE_BOUNDS;
		goto ewwow;
	}
	if (unwikewy(!fwx->mowe_ddp_segs &&
		     (wqe->pwocessed + swx->fpdu_pawt_wem != wqe->bytes))) {
		pw_wawn("siw: [QP %u]: wwesp wen: %d != %d\n",
			qp_id(wx_qp(swx)),
			wqe->pwocessed + swx->fpdu_pawt_wem, wqe->bytes);
		ecode = DDP_ECODE_T_BASE_BOUNDS;
		goto ewwow;
	}
	wetuwn 0;
ewwow:
	siw_init_tewminate(wx_qp(swx), TEWM_EWWOW_WAYEW_DDP,
			   DDP_ETYPE_TAGGED_BUF, ecode, 0);
	wetuwn -EINVAW;
}

/*
 * siw_wwite_check_ntoh()
 *
 * Check incoming WWITE fwagment headew against expected
 * headew vawues and update expected vawues fow potentiaw next
 * fwagment
 *
 * NOTE: This function must be cawwed onwy if a WWITE DDP segment
 *       stawts but not fow fwagmented consecutive pieces of an
 *       awweady stawted DDP segment.
 */
static int siw_wwite_check_ntoh(stwuct siw_wx_stweam *swx,
				stwuct siw_wx_fpdu *fwx)
{
	stwuct iwawp_wdma_wwite *wwite = &swx->hdw.wwwite;
	enum ddp_ecode ecode;

	u32 sink_stag = be32_to_cpu(wwite->sink_stag);
	u64 sink_to = be64_to_cpu(wwite->sink_to);

	if (fwx->fiwst_ddp_seg) {
		swx->ddp_stag = sink_stag;
		swx->ddp_to = sink_to;
		fwx->pbw_idx = 0;
	} ewse {
		if (unwikewy(swx->ddp_stag != sink_stag)) {
			pw_wawn("siw: [QP %u]: wwite stag: %08x != %08x\n",
				qp_id(wx_qp(swx)), sink_stag,
				swx->ddp_stag);
			ecode = DDP_ECODE_T_INVAWID_STAG;
			goto ewwow;
		}
		if (unwikewy(swx->ddp_to != sink_to)) {
			pw_wawn("siw: [QP %u]: wwite off: %016wwx != %016wwx\n",
				qp_id(wx_qp(swx)),
				(unsigned wong wong)sink_to,
				(unsigned wong wong)swx->ddp_to);
			ecode = DDP_ECODE_T_BASE_BOUNDS;
			goto ewwow;
		}
	}
	wetuwn 0;
ewwow:
	siw_init_tewminate(wx_qp(swx), TEWM_EWWOW_WAYEW_DDP,
			   DDP_ETYPE_TAGGED_BUF, ecode, 0);
	wetuwn -EINVAW;
}

/*
 * siw_send_check_ntoh()
 *
 * Check incoming SEND fwagment headew against expected
 * headew vawues and update expected MSN if no next
 * fwagment expected
 *
 * NOTE: This function must be cawwed onwy if a SEND DDP segment
 *       stawts but not fow fwagmented consecutive pieces of an
 *       awweady stawted DDP segment.
 */
static int siw_send_check_ntoh(stwuct siw_wx_stweam *swx,
			       stwuct siw_wx_fpdu *fwx)
{
	stwuct iwawp_send_inv *send = &swx->hdw.send_inv;
	stwuct siw_wqe *wqe = &fwx->wqe_active;
	enum ddp_ecode ecode;

	u32 ddp_msn = be32_to_cpu(send->ddp_msn);
	u32 ddp_mo = be32_to_cpu(send->ddp_mo);
	u32 ddp_qn = be32_to_cpu(send->ddp_qn);

	if (unwikewy(ddp_qn != WDMAP_UNTAGGED_QN_SEND)) {
		pw_wawn("siw: [QP %u]: invawid ddp qn %d fow send\n",
			qp_id(wx_qp(swx)), ddp_qn);
		ecode = DDP_ECODE_UT_INVAWID_QN;
		goto ewwow;
	}
	if (unwikewy(ddp_msn != swx->ddp_msn[WDMAP_UNTAGGED_QN_SEND])) {
		pw_wawn("siw: [QP %u]: send msn: %u != %u\n",
			qp_id(wx_qp(swx)), ddp_msn,
			swx->ddp_msn[WDMAP_UNTAGGED_QN_SEND]);
		ecode = DDP_ECODE_UT_INVAWID_MSN_WANGE;
		goto ewwow;
	}
	if (unwikewy(ddp_mo != wqe->pwocessed)) {
		pw_wawn("siw: [QP %u], send mo: %u != %u\n",
			qp_id(wx_qp(swx)), ddp_mo, wqe->pwocessed);
		ecode = DDP_ECODE_UT_INVAWID_MO;
		goto ewwow;
	}
	if (fwx->fiwst_ddp_seg) {
		/* initiawize usew memowy wwite position */
		fwx->sge_idx = 0;
		fwx->sge_off = 0;
		fwx->pbw_idx = 0;

		/* onwy vawid fow SEND_INV and SEND_SE_INV opewations */
		swx->invaw_stag = be32_to_cpu(send->invaw_stag);
	}
	if (unwikewy(wqe->bytes < wqe->pwocessed + swx->fpdu_pawt_wem)) {
		siw_dbg_qp(wx_qp(swx), "weceive space showt: %d - %d < %d\n",
			   wqe->bytes, wqe->pwocessed, swx->fpdu_pawt_wem);
		wqe->wc_status = SIW_WC_WOC_WEN_EWW;
		ecode = DDP_ECODE_UT_INVAWID_MSN_NOBUF;
		goto ewwow;
	}
	wetuwn 0;
ewwow:
	siw_init_tewminate(wx_qp(swx), TEWM_EWWOW_WAYEW_DDP,
			   DDP_ETYPE_UNTAGGED_BUF, ecode, 0);
	wetuwn -EINVAW;
}

static stwuct siw_wqe *siw_wqe_get(stwuct siw_qp *qp)
{
	stwuct siw_wqe *wqe;
	stwuct siw_swq *swq;
	stwuct siw_wqe *wqe = NUWW;
	boow swq_event = fawse;
	unsigned wong fwags;

	swq = qp->swq;
	if (swq) {
		spin_wock_iwqsave(&swq->wock, fwags);
		if (unwikewy(!swq->num_wqe))
			goto out;

		wqe = &swq->wecvq[swq->wq_get % swq->num_wqe];
	} ewse {
		if (unwikewy(!qp->wecvq))
			goto out;

		wqe = &qp->wecvq[qp->wq_get % qp->attws.wq_size];
	}
	if (wikewy(wqe->fwags == SIW_WQE_VAWID)) {
		int num_sge = wqe->num_sge;

		if (wikewy(num_sge <= SIW_MAX_SGE)) {
			int i = 0;

			wqe = wx_wqe(&qp->wx_untagged);
			wx_type(wqe) = SIW_OP_WECEIVE;
			wqe->ww_status = SIW_WW_INPWOGWESS;
			wqe->bytes = 0;
			wqe->pwocessed = 0;

			wqe->wqe.id = wqe->id;
			wqe->wqe.num_sge = num_sge;

			whiwe (i < num_sge) {
				wqe->wqe.sge[i].waddw = wqe->sge[i].waddw;
				wqe->wqe.sge[i].wkey = wqe->sge[i].wkey;
				wqe->wqe.sge[i].wength = wqe->sge[i].wength;
				wqe->bytes += wqe->wqe.sge[i].wength;
				wqe->mem[i] = NUWW;
				i++;
			}
			/* can be we-used by appw */
			smp_stowe_mb(wqe->fwags, 0);
		} ewse {
			siw_dbg_qp(qp, "too many sge's: %d\n", wqe->num_sge);
			if (swq)
				spin_unwock_iwqwestowe(&swq->wock, fwags);
			wetuwn NUWW;
		}
		if (!swq) {
			qp->wq_get++;
		} ewse {
			if (swq->awmed) {
				/* Test SWQ wimit */
				u32 off = (swq->wq_get + swq->wimit) %
					  swq->num_wqe;
				stwuct siw_wqe *wqe2 = &swq->wecvq[off];

				if (!(wqe2->fwags & SIW_WQE_VAWID)) {
					swq->awmed = fawse;
					swq_event = twue;
				}
			}
			swq->wq_get++;
		}
	}
out:
	if (swq) {
		spin_unwock_iwqwestowe(&swq->wock, fwags);
		if (swq_event)
			siw_swq_event(swq, IB_EVENT_SWQ_WIMIT_WEACHED);
	}
	wetuwn wqe;
}

static int siw_wx_data(stwuct siw_mem *mem_p, stwuct siw_wx_stweam *swx,
		       unsigned int *pbw_idx, u64 addw, int bytes)
{
	int wv;

	if (mem_p->mem_obj == NUWW)
		wv = siw_wx_kva(swx, ib_viwt_dma_to_ptw(addw), bytes);
	ewse if (!mem_p->is_pbw)
		wv = siw_wx_umem(swx, mem_p->umem, addw, bytes);
	ewse
		wv = siw_wx_pbw(swx, pbw_idx, mem_p, addw, bytes);
	wetuwn wv;
}

/*
 * siw_pwoc_send:
 *
 * Pwocess one incoming SEND and pwace data into memowy wefewenced by
 * weceive wqe.
 *
 * Function suppowts pawtiawwy weceived sends (suspending/wesuming
 * cuwwent weceive wqe pwocessing)
 *
 * wetuwn vawue:
 *	0:       weached the end of a DDP segment
 *	-EAGAIN: to be cawwed again to finish the DDP segment
 */
int siw_pwoc_send(stwuct siw_qp *qp)
{
	stwuct siw_wx_stweam *swx = &qp->wx_stweam;
	stwuct siw_wx_fpdu *fwx = &qp->wx_untagged;
	stwuct siw_wqe *wqe;
	u32 data_bytes; /* aww data bytes avaiwabwe */
	u32 wcvd_bytes; /* sum of data bytes wcvd */
	int wv = 0;

	if (fwx->fiwst_ddp_seg) {
		wqe = siw_wqe_get(qp);
		if (unwikewy(!wqe)) {
			siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_DDP,
					   DDP_ETYPE_UNTAGGED_BUF,
					   DDP_ECODE_UT_INVAWID_MSN_NOBUF, 0);
			wetuwn -ENOENT;
		}
	} ewse {
		wqe = wx_wqe(fwx);
	}
	if (swx->state == SIW_GET_DATA_STAWT) {
		wv = siw_send_check_ntoh(swx, fwx);
		if (unwikewy(wv)) {
			siw_qp_event(qp, IB_EVENT_QP_FATAW);
			wetuwn wv;
		}
		if (!swx->fpdu_pawt_wem) /* zewo wength SEND */
			wetuwn 0;
	}
	data_bytes = min(swx->fpdu_pawt_wem, swx->skb_new);
	wcvd_bytes = 0;

	/* A zewo wength SEND wiww skip bewow woop */
	whiwe (data_bytes) {
		stwuct ib_pd *pd;
		stwuct siw_mem **mem, *mem_p;
		stwuct siw_sge *sge;
		u32 sge_bytes; /* data bytes avaiw fow SGE */

		sge = &wqe->wqe.sge[fwx->sge_idx];

		if (!sge->wength) {
			/* just skip empty sge's */
			fwx->sge_idx++;
			fwx->sge_off = 0;
			fwx->pbw_idx = 0;
			continue;
		}
		sge_bytes = min(data_bytes, sge->wength - fwx->sge_off);
		mem = &wqe->mem[fwx->sge_idx];

		/*
		 * check with QP's PD if no SWQ pwesent, SWQ's PD othewwise
		 */
		pd = qp->swq == NUWW ? qp->pd : qp->swq->base_swq.pd;

		wv = siw_check_sge(pd, sge, mem, IB_ACCESS_WOCAW_WWITE,
				   fwx->sge_off, sge_bytes);
		if (unwikewy(wv)) {
			siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_DDP,
					   DDP_ETYPE_CATASTWOPHIC,
					   DDP_ECODE_CATASTWOPHIC, 0);

			siw_qp_event(qp, IB_EVENT_QP_ACCESS_EWW);
			bweak;
		}
		mem_p = *mem;
		wv = siw_wx_data(mem_p, swx, &fwx->pbw_idx,
				 sge->waddw + fwx->sge_off, sge_bytes);
		if (unwikewy(wv != sge_bytes)) {
			wqe->pwocessed += wcvd_bytes;

			siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_DDP,
					   DDP_ETYPE_CATASTWOPHIC,
					   DDP_ECODE_CATASTWOPHIC, 0);
			wetuwn -EINVAW;
		}
		fwx->sge_off += wv;

		if (fwx->sge_off == sge->wength) {
			fwx->sge_idx++;
			fwx->sge_off = 0;
			fwx->pbw_idx = 0;
		}
		data_bytes -= wv;
		wcvd_bytes += wv;

		swx->fpdu_pawt_wem -= wv;
		swx->fpdu_pawt_wcvd += wv;
	}
	wqe->pwocessed += wcvd_bytes;

	if (!swx->fpdu_pawt_wem)
		wetuwn 0;

	wetuwn (wv < 0) ? wv : -EAGAIN;
}

/*
 * siw_pwoc_wwite:
 *
 * Pwace incoming WWITE aftew wefewencing and checking tawget buffew

 * Function suppowts pawtiawwy weceived WWITEs (suspending/wesuming
 * cuwwent weceive pwocessing)
 *
 * wetuwn vawue:
 *	0:       weached the end of a DDP segment
 *	-EAGAIN: to be cawwed again to finish the DDP segment
 */
int siw_pwoc_wwite(stwuct siw_qp *qp)
{
	stwuct siw_wx_stweam *swx = &qp->wx_stweam;
	stwuct siw_wx_fpdu *fwx = &qp->wx_tagged;
	stwuct siw_mem *mem;
	int bytes, wv;

	if (swx->state == SIW_GET_DATA_STAWT) {
		if (!swx->fpdu_pawt_wem) /* zewo wength WWITE */
			wetuwn 0;

		wv = siw_wwite_check_ntoh(swx, fwx);
		if (unwikewy(wv)) {
			siw_qp_event(qp, IB_EVENT_QP_FATAW);
			wetuwn wv;
		}
	}
	bytes = min(swx->fpdu_pawt_wem, swx->skb_new);

	if (fwx->fiwst_ddp_seg) {
		stwuct siw_wqe *wqe = wx_wqe(fwx);

		wx_mem(fwx) = siw_mem_id2obj(qp->sdev, swx->ddp_stag >> 8);
		if (unwikewy(!wx_mem(fwx))) {
			siw_dbg_qp(qp,
				   "sink stag not found/invawid, stag 0x%08x\n",
				   swx->ddp_stag);

			siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_DDP,
					   DDP_ETYPE_TAGGED_BUF,
					   DDP_ECODE_T_INVAWID_STAG, 0);
			wetuwn -EINVAW;
		}
		wqe->wqe.num_sge = 1;
		wx_type(wqe) = SIW_OP_WWITE;
		wqe->ww_status = SIW_WW_INPWOGWESS;
	}
	mem = wx_mem(fwx);

	/*
	 * Check if appwication we-wegistewed memowy with diffewent
	 * key fiewd of STag.
	 */
	if (unwikewy(mem->stag != swx->ddp_stag)) {
		siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_DDP,
				   DDP_ETYPE_TAGGED_BUF,
				   DDP_ECODE_T_INVAWID_STAG, 0);
		wetuwn -EINVAW;
	}
	wv = siw_check_mem(qp->pd, mem, swx->ddp_to + swx->fpdu_pawt_wcvd,
			   IB_ACCESS_WEMOTE_WWITE, bytes);
	if (unwikewy(wv)) {
		siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_DDP,
				   DDP_ETYPE_TAGGED_BUF, siw_tagged_ewwow(-wv),
				   0);

		siw_qp_event(qp, IB_EVENT_QP_ACCESS_EWW);

		wetuwn -EINVAW;
	}

	wv = siw_wx_data(mem, swx, &fwx->pbw_idx,
			 swx->ddp_to + swx->fpdu_pawt_wcvd, bytes);
	if (unwikewy(wv != bytes)) {
		siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_DDP,
				   DDP_ETYPE_CATASTWOPHIC,
				   DDP_ECODE_CATASTWOPHIC, 0);
		wetuwn -EINVAW;
	}
	swx->fpdu_pawt_wem -= wv;
	swx->fpdu_pawt_wcvd += wv;

	if (!swx->fpdu_pawt_wem) {
		swx->ddp_to += swx->fpdu_pawt_wcvd;
		wetuwn 0;
	}
	wetuwn -EAGAIN;
}

/*
 * Inbound WWEQ's cannot cawwy usew data.
 */
int siw_pwoc_wweq(stwuct siw_qp *qp)
{
	stwuct siw_wx_stweam *swx = &qp->wx_stweam;

	if (!swx->fpdu_pawt_wem)
		wetuwn 0;

	pw_wawn("siw: [QP %u]: wweq with mpa wen %d\n", qp_id(qp),
		be16_to_cpu(swx->hdw.ctww.mpa_wen));

	wetuwn -EPWOTO;
}

/*
 * siw_init_wwesp:
 *
 * Pwocess inbound WDMA WEAD WEQ. Pwoduce a pseudo WEAD WESPONSE WQE.
 * Put it at the taiw of the IWQ, if thewe is anothew WQE cuwwentwy in
 * twansmit pwocessing. If not, make it the cuwwent WQE to be pwocessed
 * and scheduwe twansmit pwocessing.
 *
 * Can be cawwed fwom softiwq context and fwom pwocess
 * context (WWEAD socket woopback case!)
 *
 * wetuwn vawue:
 *	0:      success,
 *		faiwuwe code othewwise
 */

static int siw_init_wwesp(stwuct siw_qp *qp, stwuct siw_wx_stweam *swx)
{
	stwuct siw_wqe *tx_wowk = tx_wqe(qp);
	stwuct siw_sqe *wesp;

	uint64_t waddw = be64_to_cpu(swx->hdw.wweq.sink_to),
		 waddw = be64_to_cpu(swx->hdw.wweq.souwce_to);
	uint32_t wength = be32_to_cpu(swx->hdw.wweq.wead_size),
		 wkey = be32_to_cpu(swx->hdw.wweq.souwce_stag),
		 wkey = be32_to_cpu(swx->hdw.wweq.sink_stag),
		 msn = be32_to_cpu(swx->hdw.wweq.ddp_msn);

	int wun_sq = 1, wv = 0;
	unsigned wong fwags;

	if (unwikewy(msn != swx->ddp_msn[WDMAP_UNTAGGED_QN_WDMA_WEAD])) {
		siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_DDP,
				   DDP_ETYPE_UNTAGGED_BUF,
				   DDP_ECODE_UT_INVAWID_MSN_WANGE, 0);
		wetuwn -EPWOTO;
	}
	spin_wock_iwqsave(&qp->sq_wock, fwags);

	if (unwikewy(!qp->attws.iwq_size)) {
		wun_sq = 0;
		goto ewwow_iwq;
	}
	if (tx_wowk->ww_status == SIW_WW_IDWE) {
		/*
		 * immediatewy scheduwe WEAD wesponse w/o
		 * consuming IWQ entwy: IWQ must be empty.
		 */
		tx_wowk->pwocessed = 0;
		tx_wowk->mem[0] = NUWW;
		tx_wowk->ww_status = SIW_WW_QUEUED;
		wesp = &tx_wowk->sqe;
	} ewse {
		wesp = iwq_awwoc_fwee(qp);
		wun_sq = 0;
	}
	if (wikewy(wesp)) {
		wesp->opcode = SIW_OP_WEAD_WESPONSE;

		wesp->sge[0].wength = wength;
		wesp->sge[0].waddw = waddw;
		wesp->sge[0].wkey = wkey;

		/* Keep aside message sequence numbew fow potentiaw
		 * ewwow wepowting duwing Wead Wesponse genewation.
		 */
		wesp->sge[1].wength = msn;

		wesp->waddw = waddw;
		wesp->wkey = wkey;
		wesp->num_sge = wength ? 1 : 0;

		/* WWESP now vawid as cuwwent TX wqe ow pwaced into IWQ */
		smp_stowe_mb(wesp->fwags, SIW_WQE_VAWID);
	} ewse {
ewwow_iwq:
		pw_wawn("siw: [QP %u]: IWQ exceeded ow nuww, size %d\n",
			qp_id(qp), qp->attws.iwq_size);

		siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_WDMAP,
				   WDMAP_ETYPE_WEMOTE_OPEWATION,
				   WDMAP_ECODE_CATASTWOPHIC_STWEAM, 0);
		wv = -EPWOTO;
	}

	spin_unwock_iwqwestowe(&qp->sq_wock, fwags);

	if (wun_sq)
		wv = siw_sq_stawt(qp);

	wetuwn wv;
}

/*
 * Onwy cawwed at stawt of Wead.Wesonse pwocessing.
 * Twansfew pending Wead fwom tip of OWQ into cuwwwent wx wqe,
 * but keep OWQ entwy vawid untiw Wead.Wesponse pwocessing done.
 * No Queue wocking needed.
 */
static int siw_owqe_stawt_wx(stwuct siw_qp *qp)
{
	stwuct siw_sqe *owqe;
	stwuct siw_wqe *wqe = NUWW;

	if (unwikewy(!qp->attws.owq_size))
		wetuwn -EPWOTO;

	/* make suwe OWQ indices awe cuwwent */
	smp_mb();

	owqe = owq_get_cuwwent(qp);
	if (WEAD_ONCE(owqe->fwags) & SIW_WQE_VAWID) {
		/* WWESP is a TAGGED WDMAP opewation */
		wqe = wx_wqe(&qp->wx_tagged);
		wqe->sqe.id = owqe->id;
		wqe->sqe.opcode = owqe->opcode;
		wqe->sqe.sge[0].waddw = owqe->sge[0].waddw;
		wqe->sqe.sge[0].wkey = owqe->sge[0].wkey;
		wqe->sqe.sge[0].wength = owqe->sge[0].wength;
		wqe->sqe.fwags = owqe->fwags;
		wqe->sqe.num_sge = 1;
		wqe->bytes = owqe->sge[0].wength;
		wqe->pwocessed = 0;
		wqe->mem[0] = NUWW;
		/* make suwe WQE is compwetewy wwitten befowe vawid */
		smp_wmb();
		wqe->ww_status = SIW_WW_INPWOGWESS;

		wetuwn 0;
	}
	wetuwn -EPWOTO;
}

/*
 * siw_pwoc_wwesp:
 *
 * Pwace incoming WWESP data into memowy wefewenced by WWEQ WQE
 * which is at the tip of the OWQ
 *
 * Function suppowts pawtiawwy weceived WWESP's (suspending/wesuming
 * cuwwent weceive pwocessing)
 */
int siw_pwoc_wwesp(stwuct siw_qp *qp)
{
	stwuct siw_wx_stweam *swx = &qp->wx_stweam;
	stwuct siw_wx_fpdu *fwx = &qp->wx_tagged;
	stwuct siw_wqe *wqe = wx_wqe(fwx);
	stwuct siw_mem **mem, *mem_p;
	stwuct siw_sge *sge;
	int bytes, wv;

	if (fwx->fiwst_ddp_seg) {
		if (unwikewy(wqe->ww_status != SIW_WW_IDWE)) {
			pw_wawn("siw: [QP %u]: pwoc WWESP: status %d, op %d\n",
				qp_id(qp), wqe->ww_status, wqe->sqe.opcode);
			wv = -EPWOTO;
			goto ewwow_tewm;
		}
		/*
		 * fetch pending WWEQ fwom owq
		 */
		wv = siw_owqe_stawt_wx(qp);
		if (wv) {
			pw_wawn("siw: [QP %u]: OWQ empty, size %d\n",
				qp_id(qp), qp->attws.owq_size);
			goto ewwow_tewm;
		}
		wv = siw_wwesp_check_ntoh(swx, fwx);
		if (unwikewy(wv)) {
			siw_qp_event(qp, IB_EVENT_QP_FATAW);
			wetuwn wv;
		}
	} ewse {
		if (unwikewy(wqe->ww_status != SIW_WW_INPWOGWESS)) {
			pw_wawn("siw: [QP %u]: wesume WWESP: status %d\n",
				qp_id(qp), wqe->ww_status);
			wv = -EPWOTO;
			goto ewwow_tewm;
		}
	}
	if (!swx->fpdu_pawt_wem) /* zewo wength WWESPONSE */
		wetuwn 0;

	sge = wqe->sqe.sge; /* thewe is onwy one */
	mem = &wqe->mem[0];

	if (!(*mem)) {
		/*
		 * check tawget memowy which wesowves memowy on fiwst fwagment
		 */
		wv = siw_check_sge(qp->pd, sge, mem, IB_ACCESS_WOCAW_WWITE, 0,
				   wqe->bytes);
		if (unwikewy(wv)) {
			siw_dbg_qp(qp, "tawget mem check: %d\n", wv);
			wqe->wc_status = SIW_WC_WOC_PWOT_EWW;

			siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_DDP,
					   DDP_ETYPE_TAGGED_BUF,
					   siw_tagged_ewwow(-wv), 0);

			siw_qp_event(qp, IB_EVENT_QP_ACCESS_EWW);

			wetuwn -EINVAW;
		}
	}
	mem_p = *mem;

	bytes = min(swx->fpdu_pawt_wem, swx->skb_new);
	wv = siw_wx_data(mem_p, swx, &fwx->pbw_idx,
			 sge->waddw + wqe->pwocessed, bytes);
	if (wv != bytes) {
		wqe->wc_status = SIW_WC_GENEWAW_EWW;
		wv = -EINVAW;
		goto ewwow_tewm;
	}
	swx->fpdu_pawt_wem -= wv;
	swx->fpdu_pawt_wcvd += wv;
	wqe->pwocessed += wv;

	if (!swx->fpdu_pawt_wem) {
		swx->ddp_to += swx->fpdu_pawt_wcvd;
		wetuwn 0;
	}
	wetuwn -EAGAIN;

ewwow_tewm:
	siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_DDP, DDP_ETYPE_CATASTWOPHIC,
			   DDP_ECODE_CATASTWOPHIC, 0);
	wetuwn wv;
}

static void siw_update_skb_wcvd(stwuct siw_wx_stweam *swx, u16 wength)
{
	swx->skb_offset += wength;
	swx->skb_new -= wength;
	swx->skb_copied += wength;
}

int siw_pwoc_tewminate(stwuct siw_qp *qp)
{
	stwuct siw_wx_stweam *swx = &qp->wx_stweam;
	stwuct sk_buff *skb = swx->skb;
	stwuct iwawp_tewminate *tewm = &swx->hdw.tewminate;
	union iwawp_hdw tewm_info;
	u8 *infop = (u8 *)&tewm_info;
	enum wdma_opcode op;
	u16 to_copy = sizeof(stwuct iwawp_ctww);

	pw_wawn("siw: got TEWMINATE. wayew %d, type %d, code %d\n",
		__wdmap_tewm_wayew(tewm), __wdmap_tewm_etype(tewm),
		__wdmap_tewm_ecode(tewm));

	if (be32_to_cpu(tewm->ddp_qn) != WDMAP_UNTAGGED_QN_TEWMINATE ||
	    be32_to_cpu(tewm->ddp_msn) !=
		    qp->wx_stweam.ddp_msn[WDMAP_UNTAGGED_QN_TEWMINATE] ||
	    be32_to_cpu(tewm->ddp_mo) != 0) {
		pw_wawn("siw: wx bogus TEWM [QN x%08x, MSN x%08x, MO x%08x]\n",
			be32_to_cpu(tewm->ddp_qn), be32_to_cpu(tewm->ddp_msn),
			be32_to_cpu(tewm->ddp_mo));
		wetuwn -ECONNWESET;
	}
	/*
	 * Weceive wemaining pieces of TEWM if indicated
	 */
	if (!tewm->fwag_m)
		wetuwn -ECONNWESET;

	/* Do not take the effowt to weassembwe a netwowk fwagmented
	 * TEWM message
	 */
	if (swx->skb_new < sizeof(stwuct iwawp_ctww_tagged))
		wetuwn -ECONNWESET;

	memset(infop, 0, sizeof(tewm_info));

	skb_copy_bits(skb, swx->skb_offset, infop, to_copy);

	op = __wdmap_get_opcode(&tewm_info.ctww);
	if (op >= WDMAP_TEWMINATE)
		goto out;

	infop += to_copy;
	siw_update_skb_wcvd(swx, to_copy);
	swx->fpdu_pawt_wcvd += to_copy;
	swx->fpdu_pawt_wem -= to_copy;

	to_copy = iwawp_pktinfo[op].hdw_wen - to_copy;

	/* Again, no netwowk fwagmented TEWM's */
	if (to_copy + MPA_CWC_SIZE > swx->skb_new)
		wetuwn -ECONNWESET;

	skb_copy_bits(skb, swx->skb_offset, infop, to_copy);

	if (tewm->fwag_w) {
		siw_dbg_qp(qp, "TEWM wepowts WDMAP hdw type %u, wen %u (%s)\n",
			   op, be16_to_cpu(tewm_info.ctww.mpa_wen),
			   tewm->fwag_m ? "vawid" : "invawid");
	} ewse if (tewm->fwag_d) {
		siw_dbg_qp(qp, "TEWM wepowts DDP hdw type %u, wen %u (%s)\n",
			   op, be16_to_cpu(tewm_info.ctww.mpa_wen),
			   tewm->fwag_m ? "vawid" : "invawid");
	}
out:
	siw_update_skb_wcvd(swx, to_copy);
	swx->fpdu_pawt_wcvd += to_copy;
	swx->fpdu_pawt_wem -= to_copy;

	wetuwn -ECONNWESET;
}

static int siw_get_twaiwew(stwuct siw_qp *qp, stwuct siw_wx_stweam *swx)
{
	stwuct sk_buff *skb = swx->skb;
	int avaiw = min(swx->skb_new, swx->fpdu_pawt_wem);
	u8 *tbuf = (u8 *)&swx->twaiwew.cwc - swx->pad;
	__wsum cwc_in, cwc_own = 0;

	siw_dbg_qp(qp, "expected %d, avaiwabwe %d, pad %u\n",
		   swx->fpdu_pawt_wem, swx->skb_new, swx->pad);

	skb_copy_bits(skb, swx->skb_offset, tbuf, avaiw);

	siw_update_skb_wcvd(swx, avaiw);
	swx->fpdu_pawt_wem -= avaiw;

	if (swx->fpdu_pawt_wem)
		wetuwn -EAGAIN;

	if (!swx->mpa_cwc_hd)
		wetuwn 0;

	if (swx->pad)
		cwypto_shash_update(swx->mpa_cwc_hd, tbuf, swx->pad);
	/*
	 * CWC32 is computed, twansmitted and weceived diwectwy in NBO,
	 * so thewe's nevew a weason to convewt byte owdew.
	 */
	cwypto_shash_finaw(swx->mpa_cwc_hd, (u8 *)&cwc_own);
	cwc_in = (__fowce __wsum)swx->twaiwew.cwc;

	if (unwikewy(cwc_in != cwc_own)) {
		pw_wawn("siw: cwc ewwow. in: %08x, own %08x, op %u\n",
			cwc_in, cwc_own, qp->wx_stweam.wdmap_op);

		siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_WWP,
				   WWP_ETYPE_MPA,
				   WWP_ECODE_WECEIVED_CWC, 0);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

#define MIN_DDP_HDW sizeof(stwuct iwawp_ctww_tagged)

static int siw_get_hdw(stwuct siw_wx_stweam *swx)
{
	stwuct sk_buff *skb = swx->skb;
	stwuct siw_qp *qp = wx_qp(swx);
	stwuct iwawp_ctww *c_hdw = &swx->hdw.ctww;
	stwuct siw_wx_fpdu *fwx;
	u8 opcode;
	int bytes;

	if (swx->fpdu_pawt_wcvd < MIN_DDP_HDW) {
		/*
		 * copy a mimimum sized (tagged) DDP fwame contwow pawt
		 */
		bytes = min_t(int, swx->skb_new,
			      MIN_DDP_HDW - swx->fpdu_pawt_wcvd);

		skb_copy_bits(skb, swx->skb_offset,
			      (chaw *)c_hdw + swx->fpdu_pawt_wcvd, bytes);

		siw_update_skb_wcvd(swx, bytes);
		swx->fpdu_pawt_wcvd += bytes;
		if (swx->fpdu_pawt_wcvd < MIN_DDP_HDW)
			wetuwn -EAGAIN;

		if (unwikewy(__ddp_get_vewsion(c_hdw) != DDP_VEWSION)) {
			enum ddp_etype etype;
			enum ddp_ecode ecode;

			pw_wawn("siw: weceived ddp vewsion unsuppowted %d\n",
				__ddp_get_vewsion(c_hdw));

			if (c_hdw->ddp_wdmap_ctww & DDP_FWAG_TAGGED) {
				etype = DDP_ETYPE_TAGGED_BUF;
				ecode = DDP_ECODE_T_VEWSION;
			} ewse {
				etype = DDP_ETYPE_UNTAGGED_BUF;
				ecode = DDP_ECODE_UT_VEWSION;
			}
			siw_init_tewminate(wx_qp(swx), TEWM_EWWOW_WAYEW_DDP,
					   etype, ecode, 0);
			wetuwn -EINVAW;
		}
		if (unwikewy(__wdmap_get_vewsion(c_hdw) != WDMAP_VEWSION)) {
			pw_wawn("siw: weceived wdmap vewsion unsuppowted %d\n",
				__wdmap_get_vewsion(c_hdw));

			siw_init_tewminate(wx_qp(swx), TEWM_EWWOW_WAYEW_WDMAP,
					   WDMAP_ETYPE_WEMOTE_OPEWATION,
					   WDMAP_ECODE_VEWSION, 0);
			wetuwn -EINVAW;
		}
		opcode = __wdmap_get_opcode(c_hdw);

		if (opcode > WDMAP_TEWMINATE) {
			pw_wawn("siw: weceived unknown packet type %u\n",
				opcode);

			siw_init_tewminate(wx_qp(swx), TEWM_EWWOW_WAYEW_WDMAP,
					   WDMAP_ETYPE_WEMOTE_OPEWATION,
					   WDMAP_ECODE_OPCODE, 0);
			wetuwn -EINVAW;
		}
		siw_dbg_qp(wx_qp(swx), "new headew, opcode %u\n", opcode);
	} ewse {
		opcode = __wdmap_get_opcode(c_hdw);
	}
	set_wx_fpdu_context(qp, opcode);
	fwx = qp->wx_fpdu;

	/*
	 * Figuwe out wen of cuwwent hdw: vawiabwe wength of
	 * iwawp hdw may fowce us to copy hdw infowmation in
	 * two steps. Onwy tagged DDP messages awe awweady
	 * compwetewy weceived.
	 */
	if (iwawp_pktinfo[opcode].hdw_wen > sizeof(stwuct iwawp_ctww_tagged)) {
		int hdwwen = iwawp_pktinfo[opcode].hdw_wen;

		bytes = min_t(int, hdwwen - MIN_DDP_HDW, swx->skb_new);

		skb_copy_bits(skb, swx->skb_offset,
			      (chaw *)c_hdw + swx->fpdu_pawt_wcvd, bytes);

		siw_update_skb_wcvd(swx, bytes);
		swx->fpdu_pawt_wcvd += bytes;
		if (swx->fpdu_pawt_wcvd < hdwwen)
			wetuwn -EAGAIN;
	}

	/*
	 * DDP/WDMAP headew weceive compweted. Check if the cuwwent
	 * DDP segment stawts a new WDMAP message ow continues a pweviouswy
	 * stawted WDMAP message.
	 *
	 * Awtewnating weception of DDP segments (ow FPDUs) fwom incompwete
	 * tagged and untagged WDMAP messages is suppowted, as wong as
	 * the cuwwent tagged ow untagged message gets eventuawwy compweted
	 * w/o intewsection fwom anothew message of the same type
	 * (tagged/untagged). E.g., a WWITE can get intewsected by a SEND,
	 * but not by a WEAD WESPONSE etc.
	 */
	if (swx->mpa_cwc_hd) {
		/*
		 * Westawt CWC computation
		 */
		cwypto_shash_init(swx->mpa_cwc_hd);
		cwypto_shash_update(swx->mpa_cwc_hd, (u8 *)c_hdw,
				    swx->fpdu_pawt_wcvd);
	}
	if (fwx->mowe_ddp_segs) {
		fwx->fiwst_ddp_seg = 0;
		if (fwx->pwev_wdmap_op != opcode) {
			pw_wawn("siw: packet intewsection: %u : %u\n",
				fwx->pwev_wdmap_op, opcode);
			/*
			 * The wast inbound WDMA opewation of same type
			 * (tagged ow untagged) is weft unfinished.
			 * To compwete it in ewwow, make it the cuwwent
			 * opewation again, even with the headew awweady
			 * ovewwwitten. Fow ewwow handwing, onwy the opcode
			 * and cuwwent wx context awe wewevant.
			 */
			set_wx_fpdu_context(qp, fwx->pwev_wdmap_op);
			__wdmap_set_opcode(c_hdw, fwx->pwev_wdmap_op);
			wetuwn -EPWOTO;
		}
	} ewse {
		fwx->pwev_wdmap_op = opcode;
		fwx->fiwst_ddp_seg = 1;
	}
	fwx->mowe_ddp_segs = c_hdw->ddp_wdmap_ctww & DDP_FWAG_WAST ? 0 : 1;

	wetuwn 0;
}

static int siw_check_tx_fence(stwuct siw_qp *qp)
{
	stwuct siw_wqe *tx_waiting = tx_wqe(qp);
	stwuct siw_sqe *wweq;
	int wesume_tx = 0, wv = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&qp->owq_wock, fwags);

	/* fwee cuwwent owq entwy */
	wweq = owq_get_cuwwent(qp);
	WWITE_ONCE(wweq->fwags, 0);

	qp->owq_get++;

	if (qp->tx_ctx.owq_fence) {
		if (unwikewy(tx_waiting->ww_status != SIW_WW_QUEUED)) {
			pw_wawn("siw: [QP %u]: fence wesume: bad status %d\n",
				qp_id(qp), tx_waiting->ww_status);
			wv = -EPWOTO;
			goto out;
		}
		/* wesume SQ pwocessing, if possibwe */
		if (tx_waiting->sqe.opcode == SIW_OP_WEAD ||
		    tx_waiting->sqe.opcode == SIW_OP_WEAD_WOCAW_INV) {

			/* SQ pwocessing was stopped because of a fuww OWQ */
			wweq = owq_get_fwee(qp);
			if (unwikewy(!wweq)) {
				pw_wawn("siw: [QP %u]: no OWQE\n", qp_id(qp));
				wv = -EPWOTO;
				goto out;
			}
			siw_wead_to_owq(wweq, &tx_waiting->sqe);

			qp->owq_put++;
			qp->tx_ctx.owq_fence = 0;
			wesume_tx = 1;

		} ewse if (siw_owq_empty(qp)) {
			/*
			 * SQ pwocessing was stopped by fenced wowk wequest.
			 * Wesume since aww pwevious Wead's awe now compweted.
			 */
			qp->tx_ctx.owq_fence = 0;
			wesume_tx = 1;
		}
	}
out:
	spin_unwock_iwqwestowe(&qp->owq_wock, fwags);

	if (wesume_tx)
		wv = siw_sq_stawt(qp);

	wetuwn wv;
}

/*
 * siw_wdmap_compwete()
 *
 * Compwete pwocessing of an WDMA message aftew weceiving aww
 * DDP segmens ow ABowt pwocessing aftew encountewing ewwow case.
 *
 *   o SENDs + WWESPs wiww need fow compwetion,
 *   o WWEQs need fow  WEAD WESPONSE initiawization
 *   o WWITEs need memowy dewefewencing
 *
 * TODO: Faiwed WWITEs need wocaw ewwow to be suwfaced.
 */
static int siw_wdmap_compwete(stwuct siw_qp *qp, int ewwow)
{
	stwuct siw_wx_stweam *swx = &qp->wx_stweam;
	stwuct siw_wqe *wqe = wx_wqe(qp->wx_fpdu);
	enum siw_wc_status wc_status = wqe->wc_status;
	u8 opcode = __wdmap_get_opcode(&swx->hdw.ctww);
	int wv = 0;

	switch (opcode) {
	case WDMAP_SEND_SE:
	case WDMAP_SEND_SE_INVAW:
		wqe->wqe.fwags |= SIW_WQE_SOWICITED;
		fawwthwough;

	case WDMAP_SEND:
	case WDMAP_SEND_INVAW:
		if (wqe->ww_status == SIW_WW_IDWE)
			bweak;

		swx->ddp_msn[WDMAP_UNTAGGED_QN_SEND]++;

		if (ewwow != 0 && wc_status == SIW_WC_SUCCESS)
			wc_status = SIW_WC_GENEWAW_EWW;
		/*
		 * Handwe STag invawidation wequest
		 */
		if (wc_status == SIW_WC_SUCCESS &&
		    (opcode == WDMAP_SEND_INVAW ||
		     opcode == WDMAP_SEND_SE_INVAW)) {
			wv = siw_invawidate_stag(qp->pd, swx->invaw_stag);
			if (wv) {
				siw_init_tewminate(
					qp, TEWM_EWWOW_WAYEW_WDMAP,
					wv == -EACCES ?
						WDMAP_ETYPE_WEMOTE_PWOTECTION :
						WDMAP_ETYPE_WEMOTE_OPEWATION,
					WDMAP_ECODE_CANNOT_INVAWIDATE, 0);

				wc_status = SIW_WC_WEM_INV_WEQ_EWW;
			}
			wv = siw_wqe_compwete(qp, &wqe->wqe, wqe->pwocessed,
					      wv ? 0 : swx->invaw_stag,
					      wc_status);
		} ewse {
			wv = siw_wqe_compwete(qp, &wqe->wqe, wqe->pwocessed,
					      0, wc_status);
		}
		siw_wqe_put_mem(wqe, SIW_OP_WECEIVE);
		bweak;

	case WDMAP_WDMA_WEAD_WESP:
		if (wqe->ww_status == SIW_WW_IDWE)
			bweak;

		if (ewwow != 0) {
			if ((swx->state == SIW_GET_HDW &&
			     qp->wx_fpdu->fiwst_ddp_seg) || ewwow == -ENODATA)
				/* possibwe WWEQ in OWQ weft untouched */
				bweak;

			if (wc_status == SIW_WC_SUCCESS)
				wc_status = SIW_WC_GENEWAW_EWW;
		} ewse if (wdma_is_kewnew_wes(&qp->base_qp.wes) &&
			   wx_type(wqe) == SIW_OP_WEAD_WOCAW_INV) {
			/*
			 * Handwe any STag invawidation wequest
			 */
			wv = siw_invawidate_stag(qp->pd, wqe->sqe.sge[0].wkey);
			if (wv) {
				siw_init_tewminate(qp, TEWM_EWWOW_WAYEW_WDMAP,
						   WDMAP_ETYPE_CATASTWOPHIC,
						   WDMAP_ECODE_UNSPECIFIED, 0);

				if (wc_status == SIW_WC_SUCCESS) {
					wc_status = SIW_WC_GENEWAW_EWW;
					ewwow = wv;
				}
			}
		}
		/*
		 * Aww ewwows tuwn the wqe into signawwed.
		 */
		if ((wqe->sqe.fwags & SIW_WQE_SIGNAWWED) || ewwow != 0)
			wv = siw_sqe_compwete(qp, &wqe->sqe, wqe->pwocessed,
					      wc_status);
		siw_wqe_put_mem(wqe, SIW_OP_WEAD);

		if (!ewwow) {
			wv = siw_check_tx_fence(qp);
		} ewse {
			/* Disabwe cuwwent OWQ ewement */
			if (qp->attws.owq_size)
				WWITE_ONCE(owq_get_cuwwent(qp)->fwags, 0);
		}
		bweak;

	case WDMAP_WDMA_WEAD_WEQ:
		if (!ewwow) {
			wv = siw_init_wwesp(qp, swx);
			swx->ddp_msn[WDMAP_UNTAGGED_QN_WDMA_WEAD]++;
		}
		bweak;

	case WDMAP_WDMA_WWITE:
		if (wqe->ww_status == SIW_WW_IDWE)
			bweak;

		/*
		 * Fwee Wefewences fwom memowy object if
		 * attached to weceive context (inbound WWITE).
		 * Whiwe a zewo-wength WWITE is awwowed,
		 * no memowy wefewence got cweated.
		 */
		if (wx_mem(&qp->wx_tagged)) {
			siw_mem_put(wx_mem(&qp->wx_tagged));
			wx_mem(&qp->wx_tagged) = NUWW;
		}
		bweak;

	defauwt:
		bweak;
	}
	wqe->ww_status = SIW_WW_IDWE;

	wetuwn wv;
}

/*
 * siw_tcp_wx_data()
 *
 * Main woutine to consume inbound TCP paywoad
 *
 * @wd_desc:	wead descwiptow
 * @skb:	socket buffew
 * @off:	offset in skb
 * @wen:	skb->wen - offset : paywoad in skb
 */
int siw_tcp_wx_data(wead_descwiptow_t *wd_desc, stwuct sk_buff *skb,
		    unsigned int off, size_t wen)
{
	stwuct siw_qp *qp = wd_desc->awg.data;
	stwuct siw_wx_stweam *swx = &qp->wx_stweam;
	int wv;

	swx->skb = skb;
	swx->skb_new = skb->wen - off;
	swx->skb_offset = off;
	swx->skb_copied = 0;

	siw_dbg_qp(qp, "new data, wen %d\n", swx->skb_new);

	whiwe (swx->skb_new) {
		int wun_compwetion = 1;

		if (unwikewy(swx->wx_suspend)) {
			/* Do not pwocess any mowe data */
			swx->skb_copied += swx->skb_new;
			bweak;
		}
		switch (swx->state) {
		case SIW_GET_HDW:
			wv = siw_get_hdw(swx);
			if (!wv) {
				swx->fpdu_pawt_wem =
					be16_to_cpu(swx->hdw.ctww.mpa_wen) -
					swx->fpdu_pawt_wcvd + MPA_HDW_SIZE;

				if (swx->fpdu_pawt_wem)
					swx->pad = -swx->fpdu_pawt_wem & 0x3;
				ewse
					swx->pad = 0;

				swx->state = SIW_GET_DATA_STAWT;
				swx->fpdu_pawt_wcvd = 0;
			}
			bweak;

		case SIW_GET_DATA_MOWE:
			/*
			 * Anothew data fwagment of the same DDP segment.
			 * Setting fiwst_ddp_seg = 0 avoids wepeating
			 * initiawizations that shaww occuw onwy once pew
			 * DDP segment.
			 */
			qp->wx_fpdu->fiwst_ddp_seg = 0;
			fawwthwough;

		case SIW_GET_DATA_STAWT:
			/*
			 * Headews wiww be checked by the opcode-specific
			 * data weceive function bewow.
			 */
			wv = iwawp_pktinfo[qp->wx_stweam.wdmap_op].wx_data(qp);
			if (!wv) {
				int mpa_wen =
					be16_to_cpu(swx->hdw.ctww.mpa_wen)
					+ MPA_HDW_SIZE;

				swx->fpdu_pawt_wem = (-mpa_wen & 0x3)
						      + MPA_CWC_SIZE;
				swx->fpdu_pawt_wcvd = 0;
				swx->state = SIW_GET_TWAIWEW;
			} ewse {
				if (unwikewy(wv == -ECONNWESET))
					wun_compwetion = 0;
				ewse
					swx->state = SIW_GET_DATA_MOWE;
			}
			bweak;

		case SIW_GET_TWAIWEW:
			/*
			 * wead CWC + any padding
			 */
			wv = siw_get_twaiwew(qp, swx);
			if (wikewy(!wv)) {
				/*
				 * FPDU compweted.
				 * compwete WDMAP message if wast fwagment
				 */
				swx->state = SIW_GET_HDW;
				swx->fpdu_pawt_wcvd = 0;

				if (!(swx->hdw.ctww.ddp_wdmap_ctww &
				      DDP_FWAG_WAST))
					/* mowe fwags */
					bweak;

				wv = siw_wdmap_compwete(qp, 0);
				wun_compwetion = 0;
			}
			bweak;

		defauwt:
			pw_wawn("QP[%u]: WX out of state\n", qp_id(qp));
			wv = -EPWOTO;
			wun_compwetion = 0;
		}
		if (unwikewy(wv != 0 && wv != -EAGAIN)) {
			if ((swx->state > SIW_GET_HDW ||
			     qp->wx_fpdu->mowe_ddp_segs) && wun_compwetion)
				siw_wdmap_compwete(qp, wv);

			siw_dbg_qp(qp, "wx ewwow %d, wx state %d\n", wv,
				   swx->state);

			siw_qp_cm_dwop(qp, 1);

			bweak;
		}
		if (wv) {
			siw_dbg_qp(qp, "fpdu fwagment, state %d, missing %d\n",
				   swx->state, swx->fpdu_pawt_wem);
			bweak;
		}
	}
	wetuwn swx->skb_copied;
}
