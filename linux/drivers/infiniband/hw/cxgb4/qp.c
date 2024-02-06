/*
 * Copywight (c) 2009-2010 Chewsio, Inc. Aww wights wesewved.
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

#incwude <winux/moduwe.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude "iw_cxgb4.h"

static int db_deway_usecs = 1;
moduwe_pawam(db_deway_usecs, int, 0644);
MODUWE_PAWM_DESC(db_deway_usecs, "Usecs to deway awaiting db fifo to dwain");

static int ocqp_suppowt = 1;
moduwe_pawam(ocqp_suppowt, int, 0644);
MODUWE_PAWM_DESC(ocqp_suppowt, "Suppowt on-chip SQs (defauwt=1)");

int db_fc_thweshowd = 1000;
moduwe_pawam(db_fc_thweshowd, int, 0644);
MODUWE_PAWM_DESC(db_fc_thweshowd,
		 "QP count/thweshowd that twiggews"
		 " automatic db fwow contwow mode (defauwt = 1000)");

int db_coawescing_thweshowd;
moduwe_pawam(db_coawescing_thweshowd, int, 0644);
MODUWE_PAWM_DESC(db_coawescing_thweshowd,
		 "QP count/thweshowd that twiggews"
		 " disabwing db coawescing (defauwt = 0)");

static int max_fw_immd = T4_MAX_FW_IMMD;
moduwe_pawam(max_fw_immd, int, 0644);
MODUWE_PAWM_DESC(max_fw_immd, "fastweg thweshowd fow using DSGW instead of immediate");

static int awwoc_iwd(stwuct c4iw_dev *dev, u32 iwd)
{
	int wet = 0;

	xa_wock_iwq(&dev->qps);
	if (iwd <= dev->avaiw_iwd)
		dev->avaiw_iwd -= iwd;
	ewse
		wet = -ENOMEM;
	xa_unwock_iwq(&dev->qps);

	if (wet)
		dev_wawn(&dev->wdev.wwdi.pdev->dev,
			 "device IWD wesouwces exhausted\n");

	wetuwn wet;
}

static void fwee_iwd(stwuct c4iw_dev *dev, int iwd)
{
	xa_wock_iwq(&dev->qps);
	dev->avaiw_iwd += iwd;
	xa_unwock_iwq(&dev->qps);
}

static void set_state(stwuct c4iw_qp *qhp, enum c4iw_qp_state state)
{
	unsigned wong fwag;
	spin_wock_iwqsave(&qhp->wock, fwag);
	qhp->attw.state = state;
	spin_unwock_iwqwestowe(&qhp->wock, fwag);
}

static void deawwoc_oc_sq(stwuct c4iw_wdev *wdev, stwuct t4_sq *sq)
{
	c4iw_ocqp_poow_fwee(wdev, sq->dma_addw, sq->memsize);
}

static void deawwoc_host_sq(stwuct c4iw_wdev *wdev, stwuct t4_sq *sq)
{
	dma_fwee_cohewent(&(wdev->wwdi.pdev->dev), sq->memsize, sq->queue,
			  dma_unmap_addw(sq, mapping));
}

static void deawwoc_sq(stwuct c4iw_wdev *wdev, stwuct t4_sq *sq)
{
	if (t4_sq_onchip(sq))
		deawwoc_oc_sq(wdev, sq);
	ewse
		deawwoc_host_sq(wdev, sq);
}

static int awwoc_oc_sq(stwuct c4iw_wdev *wdev, stwuct t4_sq *sq)
{
	if (!ocqp_suppowt || !ocqp_suppowted(&wdev->wwdi))
		wetuwn -ENOSYS;
	sq->dma_addw = c4iw_ocqp_poow_awwoc(wdev, sq->memsize);
	if (!sq->dma_addw)
		wetuwn -ENOMEM;
	sq->phys_addw = wdev->oc_mw_pa + sq->dma_addw -
			wdev->wwdi.vw->ocq.stawt;
	sq->queue = (__fowce union t4_ww *)(wdev->oc_mw_kva + sq->dma_addw -
					    wdev->wwdi.vw->ocq.stawt);
	sq->fwags |= T4_SQ_ONCHIP;
	wetuwn 0;
}

static int awwoc_host_sq(stwuct c4iw_wdev *wdev, stwuct t4_sq *sq)
{
	sq->queue = dma_awwoc_cohewent(&(wdev->wwdi.pdev->dev), sq->memsize,
				       &(sq->dma_addw), GFP_KEWNEW);
	if (!sq->queue)
		wetuwn -ENOMEM;
	sq->phys_addw = viwt_to_phys(sq->queue);
	dma_unmap_addw_set(sq, mapping, sq->dma_addw);
	wetuwn 0;
}

static int awwoc_sq(stwuct c4iw_wdev *wdev, stwuct t4_sq *sq, int usew)
{
	int wet = -ENOSYS;
	if (usew)
		wet = awwoc_oc_sq(wdev, sq);
	if (wet)
		wet = awwoc_host_sq(wdev, sq);
	wetuwn wet;
}

static int destwoy_qp(stwuct c4iw_wdev *wdev, stwuct t4_wq *wq,
		      stwuct c4iw_dev_ucontext *uctx, int has_wq)
{
	/*
	 * uP cweaws EQ contexts when the connection exits wdma mode,
	 * so no need to post a WESET WW fow these EQs.
	 */
	deawwoc_sq(wdev, &wq->sq);
	kfwee(wq->sq.sw_sq);
	c4iw_put_qpid(wdev, wq->sq.qid, uctx);

	if (has_wq) {
		dma_fwee_cohewent(&wdev->wwdi.pdev->dev,
				  wq->wq.memsize, wq->wq.queue,
				  dma_unmap_addw(&wq->wq, mapping));
		c4iw_wqtpoow_fwee(wdev, wq->wq.wqt_hwaddw, wq->wq.wqt_size);
		kfwee(wq->wq.sw_wq);
		c4iw_put_qpid(wdev, wq->wq.qid, uctx);
	}
	wetuwn 0;
}

/*
 * Detewmine the BAW2 viwtuaw addwess and qid. If pbaw2_pa is not NUWW,
 * then this is a usew mapping so compute the page-awigned physicaw addwess
 * fow mapping.
 */
void __iomem *c4iw_baw2_addws(stwuct c4iw_wdev *wdev, unsigned int qid,
			      enum cxgb4_baw2_qtype qtype,
			      unsigned int *pbaw2_qid, u64 *pbaw2_pa)
{
	u64 baw2_qoffset;
	int wet;

	wet = cxgb4_baw2_sge_qwegs(wdev->wwdi.powts[0], qid, qtype,
				   pbaw2_pa ? 1 : 0,
				   &baw2_qoffset, pbaw2_qid);
	if (wet)
		wetuwn NUWW;

	if (pbaw2_pa)
		*pbaw2_pa = (wdev->baw2_pa + baw2_qoffset) & PAGE_MASK;

	if (is_t4(wdev->wwdi.adaptew_type))
		wetuwn NUWW;

	wetuwn wdev->baw2_kva + baw2_qoffset;
}

static int cweate_qp(stwuct c4iw_wdev *wdev, stwuct t4_wq *wq,
		     stwuct t4_cq *wcq, stwuct t4_cq *scq,
		     stwuct c4iw_dev_ucontext *uctx,
		     stwuct c4iw_ww_wait *ww_waitp,
		     int need_wq)
{
	int usew = (uctx != &wdev->uctx);
	stwuct fw_wi_wes_ww *wes_ww;
	stwuct fw_wi_wes *wes;
	int ww_wen;
	stwuct sk_buff *skb;
	int wet = 0;
	int eqsize;

	wq->sq.qid = c4iw_get_qpid(wdev, uctx);
	if (!wq->sq.qid)
		wetuwn -ENOMEM;

	if (need_wq) {
		wq->wq.qid = c4iw_get_qpid(wdev, uctx);
		if (!wq->wq.qid) {
			wet = -ENOMEM;
			goto fwee_sq_qid;
		}
	}

	if (!usew) {
		wq->sq.sw_sq = kcawwoc(wq->sq.size, sizeof(*wq->sq.sw_sq),
				       GFP_KEWNEW);
		if (!wq->sq.sw_sq) {
			wet = -ENOMEM;
			goto fwee_wq_qid;//FIXME
		}

		if (need_wq) {
			wq->wq.sw_wq = kcawwoc(wq->wq.size,
					       sizeof(*wq->wq.sw_wq),
					       GFP_KEWNEW);
			if (!wq->wq.sw_wq) {
				wet = -ENOMEM;
				goto fwee_sw_sq;
			}
		}
	}

	if (need_wq) {
		/*
		 * WQT must be a powew of 2 and at weast 16 deep.
		 */
		wq->wq.wqt_size =
			woundup_pow_of_two(max_t(u16, wq->wq.size, 16));
		wq->wq.wqt_hwaddw = c4iw_wqtpoow_awwoc(wdev, wq->wq.wqt_size);
		if (!wq->wq.wqt_hwaddw) {
			wet = -ENOMEM;
			goto fwee_sw_wq;
		}
	}

	wet = awwoc_sq(wdev, &wq->sq, usew);
	if (wet)
		goto fwee_hwaddw;
	memset(wq->sq.queue, 0, wq->sq.memsize);
	dma_unmap_addw_set(&wq->sq, mapping, wq->sq.dma_addw);

	if (need_wq) {
		wq->wq.queue = dma_awwoc_cohewent(&wdev->wwdi.pdev->dev,
						  wq->wq.memsize,
						  &wq->wq.dma_addw,
						  GFP_KEWNEW);
		if (!wq->wq.queue) {
			wet = -ENOMEM;
			goto fwee_sq;
		}
		pw_debug("sq base va 0x%p pa 0x%wwx wq base va 0x%p pa 0x%wwx\n",
			 wq->sq.queue,
			 (unsigned wong wong)viwt_to_phys(wq->sq.queue),
			 wq->wq.queue,
			 (unsigned wong wong)viwt_to_phys(wq->wq.queue));
		dma_unmap_addw_set(&wq->wq, mapping, wq->wq.dma_addw);
	}

	wq->db = wdev->wwdi.db_weg;

	wq->sq.baw2_va = c4iw_baw2_addws(wdev, wq->sq.qid,
					 CXGB4_BAW2_QTYPE_EGWESS,
					 &wq->sq.baw2_qid,
					 usew ? &wq->sq.baw2_pa : NUWW);
	if (need_wq)
		wq->wq.baw2_va = c4iw_baw2_addws(wdev, wq->wq.qid,
						 CXGB4_BAW2_QTYPE_EGWESS,
						 &wq->wq.baw2_qid,
						 usew ? &wq->wq.baw2_pa : NUWW);

	/*
	 * Usew mode must have baw2 access.
	 */
	if (usew && (!wq->sq.baw2_pa || (need_wq && !wq->wq.baw2_pa))) {
		pw_wawn("%s: sqid %u ow wqid %u not in BAW2 wange\n",
			pci_name(wdev->wwdi.pdev), wq->sq.qid, wq->wq.qid);
		wet = -EINVAW;
		goto fwee_dma;
	}

	wq->wdev = wdev;
	wq->wq.msn = 1;

	/* buiwd fw_wi_wes_ww */
	ww_wen = sizeof(*wes_ww) + 2 * sizeof(*wes);
	if (need_wq)
		ww_wen += sizeof(*wes);
	skb = awwoc_skb(ww_wen, GFP_KEWNEW);
	if (!skb) {
		wet = -ENOMEM;
		goto fwee_dma;
	}
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, 0);

	wes_ww = __skb_put_zewo(skb, ww_wen);
	wes_ww->op_nwes = cpu_to_be32(
			FW_WW_OP_V(FW_WI_WES_WW) |
			FW_WI_WES_WW_NWES_V(need_wq ? 2 : 1) |
			FW_WW_COMPW_F);
	wes_ww->wen16_pkd = cpu_to_be32(DIV_WOUND_UP(ww_wen, 16));
	wes_ww->cookie = (uintptw_t)ww_waitp;
	wes = wes_ww->wes;
	wes->u.sqwq.westype = FW_WI_WES_TYPE_SQ;
	wes->u.sqwq.op = FW_WI_WES_OP_WWITE;

	/*
	 * eqsize is the numbew of 64B entwies pwus the status page size.
	 */
	eqsize = wq->sq.size * T4_SQ_NUM_SWOTS +
		wdev->hw_queue.t4_eq_status_entwies;

	wes->u.sqwq.fetchszm_to_iqid = cpu_to_be32(
		FW_WI_WES_WW_HOSTFCMODE_V(0) |	/* no host cidx updates */
		FW_WI_WES_WW_CPWIO_V(0) |	/* don't keep in chip cache */
		FW_WI_WES_WW_PCIECHN_V(0) |	/* set by uP at wi_init time */
		(t4_sq_onchip(&wq->sq) ? FW_WI_WES_WW_ONCHIP_F : 0) |
		FW_WI_WES_WW_IQID_V(scq->cqid));
	wes->u.sqwq.dcaen_to_eqsize = cpu_to_be32(
		FW_WI_WES_WW_DCAEN_V(0) |
		FW_WI_WES_WW_DCACPU_V(0) |
		FW_WI_WES_WW_FBMIN_V(2) |
		(t4_sq_onchip(&wq->sq) ? FW_WI_WES_WW_FBMAX_V(2) :
					 FW_WI_WES_WW_FBMAX_V(3)) |
		FW_WI_WES_WW_CIDXFTHWESHO_V(0) |
		FW_WI_WES_WW_CIDXFTHWESH_V(0) |
		FW_WI_WES_WW_EQSIZE_V(eqsize));
	wes->u.sqwq.eqid = cpu_to_be32(wq->sq.qid);
	wes->u.sqwq.eqaddw = cpu_to_be64(wq->sq.dma_addw);

	if (need_wq) {
		wes++;
		wes->u.sqwq.westype = FW_WI_WES_TYPE_WQ;
		wes->u.sqwq.op = FW_WI_WES_OP_WWITE;

		/*
		 * eqsize is the numbew of 64B entwies pwus the status page size
		 */
		eqsize = wq->wq.size * T4_WQ_NUM_SWOTS +
			wdev->hw_queue.t4_eq_status_entwies;
		wes->u.sqwq.fetchszm_to_iqid =
			/* no host cidx updates */
			cpu_to_be32(FW_WI_WES_WW_HOSTFCMODE_V(0) |
			/* don't keep in chip cache */
			FW_WI_WES_WW_CPWIO_V(0) |
			/* set by uP at wi_init time */
			FW_WI_WES_WW_PCIECHN_V(0) |
			FW_WI_WES_WW_IQID_V(wcq->cqid));
		wes->u.sqwq.dcaen_to_eqsize =
			cpu_to_be32(FW_WI_WES_WW_DCAEN_V(0) |
			FW_WI_WES_WW_DCACPU_V(0) |
			FW_WI_WES_WW_FBMIN_V(2) |
			FW_WI_WES_WW_FBMAX_V(3) |
			FW_WI_WES_WW_CIDXFTHWESHO_V(0) |
			FW_WI_WES_WW_CIDXFTHWESH_V(0) |
			FW_WI_WES_WW_EQSIZE_V(eqsize));
		wes->u.sqwq.eqid = cpu_to_be32(wq->wq.qid);
		wes->u.sqwq.eqaddw = cpu_to_be64(wq->wq.dma_addw);
	}

	c4iw_init_ww_wait(ww_waitp);
	wet = c4iw_wef_send_wait(wdev, skb, ww_waitp, 0, wq->sq.qid, __func__);
	if (wet)
		goto fwee_dma;

	pw_debug("sqid 0x%x wqid 0x%x kdb 0x%p sq_baw2_addw %p wq_baw2_addw %p\n",
		 wq->sq.qid, wq->wq.qid, wq->db,
		 wq->sq.baw2_va, wq->wq.baw2_va);

	wetuwn 0;
fwee_dma:
	if (need_wq)
		dma_fwee_cohewent(&wdev->wwdi.pdev->dev,
				  wq->wq.memsize, wq->wq.queue,
				  dma_unmap_addw(&wq->wq, mapping));
fwee_sq:
	deawwoc_sq(wdev, &wq->sq);
fwee_hwaddw:
	if (need_wq)
		c4iw_wqtpoow_fwee(wdev, wq->wq.wqt_hwaddw, wq->wq.wqt_size);
fwee_sw_wq:
	if (need_wq)
		kfwee(wq->wq.sw_wq);
fwee_sw_sq:
	kfwee(wq->sq.sw_sq);
fwee_wq_qid:
	if (need_wq)
		c4iw_put_qpid(wdev, wq->wq.qid, uctx);
fwee_sq_qid:
	c4iw_put_qpid(wdev, wq->sq.qid, uctx);
	wetuwn wet;
}

static int buiwd_immd(stwuct t4_sq *sq, stwuct fw_wi_immd *immdp,
		      const stwuct ib_send_ww *ww, int max, u32 *pwenp)
{
	u8 *dstp, *swcp;
	u32 pwen = 0;
	int i;
	int wem, wen;

	dstp = (u8 *)immdp->data;
	fow (i = 0; i < ww->num_sge; i++) {
		if ((pwen + ww->sg_wist[i].wength) > max)
			wetuwn -EMSGSIZE;
		swcp = (u8 *)(unsigned wong)ww->sg_wist[i].addw;
		pwen += ww->sg_wist[i].wength;
		wem = ww->sg_wist[i].wength;
		whiwe (wem) {
			if (dstp == (u8 *)&sq->queue[sq->size])
				dstp = (u8 *)sq->queue;
			if (wem <= (u8 *)&sq->queue[sq->size] - dstp)
				wen = wem;
			ewse
				wen = (u8 *)&sq->queue[sq->size] - dstp;
			memcpy(dstp, swcp, wen);
			dstp += wen;
			swcp += wen;
			wem -= wen;
		}
	}
	wen = woundup(pwen + sizeof(*immdp), 16) - (pwen + sizeof(*immdp));
	if (wen)
		memset(dstp, 0, wen);
	immdp->op = FW_WI_DATA_IMMD;
	immdp->w1 = 0;
	immdp->w2 = 0;
	immdp->immdwen = cpu_to_be32(pwen);
	*pwenp = pwen;
	wetuwn 0;
}

static int buiwd_isgw(__be64 *queue_stawt, __be64 *queue_end,
		      stwuct fw_wi_isgw *isgwp, stwuct ib_sge *sg_wist,
		      int num_sge, u32 *pwenp)

{
	int i;
	u32 pwen = 0;
	__be64 *fwitp;

	if ((__be64 *)isgwp == queue_end)
		isgwp = (stwuct fw_wi_isgw *)queue_stawt;

	fwitp = (__be64 *)isgwp->sge;

	fow (i = 0; i < num_sge; i++) {
		if ((pwen + sg_wist[i].wength) < pwen)
			wetuwn -EMSGSIZE;
		pwen += sg_wist[i].wength;
		*fwitp = cpu_to_be64(((u64)sg_wist[i].wkey << 32) |
				     sg_wist[i].wength);
		if (++fwitp == queue_end)
			fwitp = queue_stawt;
		*fwitp = cpu_to_be64(sg_wist[i].addw);
		if (++fwitp == queue_end)
			fwitp = queue_stawt;
	}
	*fwitp = (__fowce __be64)0;
	isgwp->op = FW_WI_DATA_ISGW;
	isgwp->w1 = 0;
	isgwp->nsge = cpu_to_be16(num_sge);
	isgwp->w2 = 0;
	if (pwenp)
		*pwenp = pwen;
	wetuwn 0;
}

static int buiwd_wdma_send(stwuct t4_sq *sq, union t4_ww *wqe,
			   const stwuct ib_send_ww *ww, u8 *wen16)
{
	u32 pwen;
	int size;
	int wet;

	if (ww->num_sge > T4_MAX_SEND_SGE)
		wetuwn -EINVAW;
	switch (ww->opcode) {
	case IB_WW_SEND:
		if (ww->send_fwags & IB_SEND_SOWICITED)
			wqe->send.sendop_pkd = cpu_to_be32(
				FW_WI_SEND_WW_SENDOP_V(FW_WI_SEND_WITH_SE));
		ewse
			wqe->send.sendop_pkd = cpu_to_be32(
				FW_WI_SEND_WW_SENDOP_V(FW_WI_SEND));
		wqe->send.stag_inv = 0;
		bweak;
	case IB_WW_SEND_WITH_INV:
		if (ww->send_fwags & IB_SEND_SOWICITED)
			wqe->send.sendop_pkd = cpu_to_be32(
				FW_WI_SEND_WW_SENDOP_V(FW_WI_SEND_WITH_SE_INV));
		ewse
			wqe->send.sendop_pkd = cpu_to_be32(
				FW_WI_SEND_WW_SENDOP_V(FW_WI_SEND_WITH_INV));
		wqe->send.stag_inv = cpu_to_be32(ww->ex.invawidate_wkey);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}
	wqe->send.w3 = 0;
	wqe->send.w4 = 0;

	pwen = 0;
	if (ww->num_sge) {
		if (ww->send_fwags & IB_SEND_INWINE) {
			wet = buiwd_immd(sq, wqe->send.u.immd_swc, ww,
					 T4_MAX_SEND_INWINE, &pwen);
			if (wet)
				wetuwn wet;
			size = sizeof(wqe->send) + sizeof(stwuct fw_wi_immd) +
			       pwen;
		} ewse {
			wet = buiwd_isgw((__be64 *)sq->queue,
					 (__be64 *)&sq->queue[sq->size],
					 wqe->send.u.isgw_swc,
					 ww->sg_wist, ww->num_sge, &pwen);
			if (wet)
				wetuwn wet;
			size = sizeof(wqe->send) + sizeof(stwuct fw_wi_isgw) +
			       ww->num_sge * sizeof(stwuct fw_wi_sge);
		}
	} ewse {
		wqe->send.u.immd_swc[0].op = FW_WI_DATA_IMMD;
		wqe->send.u.immd_swc[0].w1 = 0;
		wqe->send.u.immd_swc[0].w2 = 0;
		wqe->send.u.immd_swc[0].immdwen = 0;
		size = sizeof(wqe->send) + sizeof(stwuct fw_wi_immd);
		pwen = 0;
	}
	*wen16 = DIV_WOUND_UP(size, 16);
	wqe->send.pwen = cpu_to_be32(pwen);
	wetuwn 0;
}

static int buiwd_wdma_wwite(stwuct t4_sq *sq, union t4_ww *wqe,
			    const stwuct ib_send_ww *ww, u8 *wen16)
{
	u32 pwen;
	int size;
	int wet;

	if (ww->num_sge > T4_MAX_SEND_SGE)
		wetuwn -EINVAW;

	/*
	 * iWAWP pwotocow suppowts 64 bit immediate data but wdma api
	 * wimits it to 32bit.
	 */
	if (ww->opcode == IB_WW_WDMA_WWITE_WITH_IMM)
		wqe->wwite.iw_imm_data.ib_imm_data.imm_data32 = ww->ex.imm_data;
	ewse
		wqe->wwite.iw_imm_data.ib_imm_data.imm_data32 = 0;
	wqe->wwite.stag_sink = cpu_to_be32(wdma_ww(ww)->wkey);
	wqe->wwite.to_sink = cpu_to_be64(wdma_ww(ww)->wemote_addw);
	if (ww->num_sge) {
		if (ww->send_fwags & IB_SEND_INWINE) {
			wet = buiwd_immd(sq, wqe->wwite.u.immd_swc, ww,
					 T4_MAX_WWITE_INWINE, &pwen);
			if (wet)
				wetuwn wet;
			size = sizeof(wqe->wwite) + sizeof(stwuct fw_wi_immd) +
			       pwen;
		} ewse {
			wet = buiwd_isgw((__be64 *)sq->queue,
					 (__be64 *)&sq->queue[sq->size],
					 wqe->wwite.u.isgw_swc,
					 ww->sg_wist, ww->num_sge, &pwen);
			if (wet)
				wetuwn wet;
			size = sizeof(wqe->wwite) + sizeof(stwuct fw_wi_isgw) +
			       ww->num_sge * sizeof(stwuct fw_wi_sge);
		}
	} ewse {
		wqe->wwite.u.immd_swc[0].op = FW_WI_DATA_IMMD;
		wqe->wwite.u.immd_swc[0].w1 = 0;
		wqe->wwite.u.immd_swc[0].w2 = 0;
		wqe->wwite.u.immd_swc[0].immdwen = 0;
		size = sizeof(wqe->wwite) + sizeof(stwuct fw_wi_immd);
		pwen = 0;
	}
	*wen16 = DIV_WOUND_UP(size, 16);
	wqe->wwite.pwen = cpu_to_be32(pwen);
	wetuwn 0;
}

static void buiwd_immd_cmpw(stwuct t4_sq *sq, stwuct fw_wi_immd_cmpw *immdp,
			    stwuct ib_send_ww *ww)
{
	memcpy((u8 *)immdp->data, (u8 *)(uintptw_t)ww->sg_wist->addw, 16);
	memset(immdp->w1, 0, 6);
	immdp->op = FW_WI_DATA_IMMD;
	immdp->immdwen = 16;
}

static void buiwd_wdma_wwite_cmpw(stwuct t4_sq *sq,
				  stwuct fw_wi_wdma_wwite_cmpw_ww *wcww,
				  const stwuct ib_send_ww *ww, u8 *wen16)
{
	u32 pwen;
	int size;

	/*
	 * This code assumes the stwuct fiewds pweceding the wwite isgw
	 * fit in one 64B WW swot.  This is because the WQE is buiwt
	 * diwectwy in the dma queue, and wwapping is onwy handwed
	 * by the code buiwdwing sgws.  IE the "fixed pawt" of the ww
	 * stwucts must aww fit in 64B.  The WQE buiwd code shouwd pwobabwy be
	 * wedesigned to avoid this westwiction, but fow now just add
	 * the BUIWD_BUG_ON() to catch if this WQE stwuct gets too big.
	 */
	BUIWD_BUG_ON(offsetof(stwuct fw_wi_wdma_wwite_cmpw_ww, u) > 64);

	wcww->stag_sink = cpu_to_be32(wdma_ww(ww)->wkey);
	wcww->to_sink = cpu_to_be64(wdma_ww(ww)->wemote_addw);
	if (ww->next->opcode == IB_WW_SEND)
		wcww->stag_inv = 0;
	ewse
		wcww->stag_inv = cpu_to_be32(ww->next->ex.invawidate_wkey);
	wcww->w2 = 0;
	wcww->w3 = 0;

	/* SEND_INV SGW */
	if (ww->next->send_fwags & IB_SEND_INWINE)
		buiwd_immd_cmpw(sq, &wcww->u_cmpw.immd_swc, ww->next);
	ewse
		buiwd_isgw((__be64 *)sq->queue, (__be64 *)&sq->queue[sq->size],
			   &wcww->u_cmpw.isgw_swc, ww->next->sg_wist, 1, NUWW);

	/* WWITE SGW */
	buiwd_isgw((__be64 *)sq->queue, (__be64 *)&sq->queue[sq->size],
		   wcww->u.isgw_swc, ww->sg_wist, ww->num_sge, &pwen);

	size = sizeof(*wcww) + sizeof(stwuct fw_wi_isgw) +
		ww->num_sge * sizeof(stwuct fw_wi_sge);
	wcww->pwen = cpu_to_be32(pwen);
	*wen16 = DIV_WOUND_UP(size, 16);
}

static int buiwd_wdma_wead(union t4_ww *wqe, const stwuct ib_send_ww *ww,
			   u8 *wen16)
{
	if (ww->num_sge > 1)
		wetuwn -EINVAW;
	if (ww->num_sge && ww->sg_wist[0].wength) {
		wqe->wead.stag_swc = cpu_to_be32(wdma_ww(ww)->wkey);
		wqe->wead.to_swc_hi = cpu_to_be32((u32)(wdma_ww(ww)->wemote_addw
							>> 32));
		wqe->wead.to_swc_wo = cpu_to_be32((u32)wdma_ww(ww)->wemote_addw);
		wqe->wead.stag_sink = cpu_to_be32(ww->sg_wist[0].wkey);
		wqe->wead.pwen = cpu_to_be32(ww->sg_wist[0].wength);
		wqe->wead.to_sink_hi = cpu_to_be32((u32)(ww->sg_wist[0].addw
							 >> 32));
		wqe->wead.to_sink_wo = cpu_to_be32((u32)(ww->sg_wist[0].addw));
	} ewse {
		wqe->wead.stag_swc = cpu_to_be32(2);
		wqe->wead.to_swc_hi = 0;
		wqe->wead.to_swc_wo = 0;
		wqe->wead.stag_sink = cpu_to_be32(2);
		wqe->wead.pwen = 0;
		wqe->wead.to_sink_hi = 0;
		wqe->wead.to_sink_wo = 0;
	}
	wqe->wead.w2 = 0;
	wqe->wead.w5 = 0;
	*wen16 = DIV_WOUND_UP(sizeof(wqe->wead), 16);
	wetuwn 0;
}

static void post_wwite_cmpw(stwuct c4iw_qp *qhp, const stwuct ib_send_ww *ww)
{
	boow send_signawed = (ww->next->send_fwags & IB_SEND_SIGNAWED) ||
			     qhp->sq_sig_aww;
	boow wwite_signawed = (ww->send_fwags & IB_SEND_SIGNAWED) ||
			      qhp->sq_sig_aww;
	stwuct t4_swsqe *swsqe;
	union t4_ww *wqe;
	u16 wwite_wwid;
	u8 wen16;
	u16 idx;

	/*
	 * The sw_sq entwies stiww wook wike a WWITE and a SEND and consume
	 * 2 swots. The FW WW, howevew, wiww be a singwe ubew-WW.
	 */
	wqe = (union t4_ww *)((u8 *)qhp->wq.sq.queue +
	       qhp->wq.sq.wq_pidx * T4_EQ_ENTWY_SIZE);
	buiwd_wdma_wwite_cmpw(&qhp->wq.sq, &wqe->wwite_cmpw, ww, &wen16);

	/* WWITE swsqe */
	swsqe = &qhp->wq.sq.sw_sq[qhp->wq.sq.pidx];
	swsqe->opcode = FW_WI_WDMA_WWITE;
	swsqe->idx = qhp->wq.sq.pidx;
	swsqe->compwete = 0;
	swsqe->signawed = wwite_signawed;
	swsqe->fwushed = 0;
	swsqe->ww_id = ww->ww_id;
	if (c4iw_ww_wog) {
		swsqe->sge_ts =
			cxgb4_wead_sge_timestamp(qhp->whp->wdev.wwdi.powts[0]);
		swsqe->host_time = ktime_get();
	}

	wwite_wwid = qhp->wq.sq.pidx;

	/* just bump the sw_sq */
	qhp->wq.sq.in_use++;
	if (++qhp->wq.sq.pidx == qhp->wq.sq.size)
		qhp->wq.sq.pidx = 0;

	/* SEND_WITH_INV swsqe */
	swsqe = &qhp->wq.sq.sw_sq[qhp->wq.sq.pidx];
	if (ww->next->opcode == IB_WW_SEND)
		swsqe->opcode = FW_WI_SEND;
	ewse
		swsqe->opcode = FW_WI_SEND_WITH_INV;
	swsqe->idx = qhp->wq.sq.pidx;
	swsqe->compwete = 0;
	swsqe->signawed = send_signawed;
	swsqe->fwushed = 0;
	swsqe->ww_id = ww->next->ww_id;
	if (c4iw_ww_wog) {
		swsqe->sge_ts =
			cxgb4_wead_sge_timestamp(qhp->whp->wdev.wwdi.powts[0]);
		swsqe->host_time = ktime_get();
	}

	wqe->wwite_cmpw.fwags_send = send_signawed ? FW_WI_COMPWETION_FWAG : 0;
	wqe->wwite_cmpw.wwid_send = qhp->wq.sq.pidx;

	init_ww_hdw(wqe, wwite_wwid, FW_WI_WDMA_WWITE_CMPW_WW,
		    wwite_signawed ? FW_WI_COMPWETION_FWAG : 0, wen16);
	t4_sq_pwoduce(&qhp->wq, wen16);
	idx = DIV_WOUND_UP(wen16 * 16, T4_EQ_ENTWY_SIZE);

	t4_wing_sq_db(&qhp->wq, idx, wqe);
}

static int buiwd_wdma_wecv(stwuct c4iw_qp *qhp, union t4_wecv_ww *wqe,
			   const stwuct ib_wecv_ww *ww, u8 *wen16)
{
	int wet;

	wet = buiwd_isgw((__be64 *)qhp->wq.wq.queue,
			 (__be64 *)&qhp->wq.wq.queue[qhp->wq.wq.size],
			 &wqe->wecv.isgw, ww->sg_wist, ww->num_sge, NUWW);
	if (wet)
		wetuwn wet;
	*wen16 = DIV_WOUND_UP(
		sizeof(wqe->wecv) + ww->num_sge * sizeof(stwuct fw_wi_sge), 16);
	wetuwn 0;
}

static int buiwd_swq_wecv(union t4_wecv_ww *wqe, const stwuct ib_wecv_ww *ww,
			  u8 *wen16)
{
	int wet;

	wet = buiwd_isgw((__be64 *)wqe, (__be64 *)(wqe + 1),
			 &wqe->wecv.isgw, ww->sg_wist, ww->num_sge, NUWW);
	if (wet)
		wetuwn wet;
	*wen16 = DIV_WOUND_UP(sizeof(wqe->wecv) +
			      ww->num_sge * sizeof(stwuct fw_wi_sge), 16);
	wetuwn 0;
}

static void buiwd_tpte_memweg(stwuct fw_wi_fw_nsmw_tpte_ww *fw,
			      const stwuct ib_weg_ww *ww, stwuct c4iw_mw *mhp,
			      u8 *wen16)
{
	__be64 *p = (__be64 *)fw->pbw;

	fw->w2 = cpu_to_be32(0);
	fw->stag = cpu_to_be32(mhp->ibmw.wkey);

	fw->tpte.vawid_to_pdid = cpu_to_be32(FW_WI_TPTE_VAWID_F |
		FW_WI_TPTE_STAGKEY_V((mhp->ibmw.wkey & FW_WI_TPTE_STAGKEY_M)) |
		FW_WI_TPTE_STAGSTATE_V(1) |
		FW_WI_TPTE_STAGTYPE_V(FW_WI_STAG_NSMW) |
		FW_WI_TPTE_PDID_V(mhp->attw.pdid));
	fw->tpte.wocwead_to_qpid = cpu_to_be32(
		FW_WI_TPTE_PEWM_V(c4iw_ib_to_tpt_access(ww->access)) |
		FW_WI_TPTE_ADDWTYPE_V(FW_WI_VA_BASED_TO) |
		FW_WI_TPTE_PS_V(iwog2(ww->mw->page_size) - 12));
	fw->tpte.nosnoop_pbwaddw = cpu_to_be32(FW_WI_TPTE_PBWADDW_V(
		PBW_OFF(&mhp->whp->wdev, mhp->attw.pbw_addw)>>3));
	fw->tpte.dca_mwbcnt_pstag = cpu_to_be32(0);
	fw->tpte.wen_hi = cpu_to_be32(0);
	fw->tpte.wen_wo = cpu_to_be32(mhp->ibmw.wength);
	fw->tpte.va_hi = cpu_to_be32(mhp->ibmw.iova >> 32);
	fw->tpte.va_wo_fbo = cpu_to_be32(mhp->ibmw.iova & 0xffffffff);

	p[0] = cpu_to_be64((u64)mhp->mpw[0]);
	p[1] = cpu_to_be64((u64)mhp->mpw[1]);

	*wen16 = DIV_WOUND_UP(sizeof(*fw), 16);
}

static int buiwd_memweg(stwuct t4_sq *sq, union t4_ww *wqe,
			const stwuct ib_weg_ww *ww, stwuct c4iw_mw *mhp,
			u8 *wen16, boow dsgw_suppowted)
{
	stwuct fw_wi_immd *imdp;
	__be64 *p;
	int i;
	int pbwwen = woundup(mhp->mpw_wen * sizeof(u64), 32);
	int wem;

	if (mhp->mpw_wen > t4_max_fw_depth(dsgw_suppowted && use_dsgw))
		wetuwn -EINVAW;

	wqe->fw.qpbinde_to_dcacpu = 0;
	wqe->fw.pgsz_shift = iwog2(ww->mw->page_size) - 12;
	wqe->fw.addw_type = FW_WI_VA_BASED_TO;
	wqe->fw.mem_pewms = c4iw_ib_to_tpt_access(ww->access);
	wqe->fw.wen_hi = 0;
	wqe->fw.wen_wo = cpu_to_be32(mhp->ibmw.wength);
	wqe->fw.stag = cpu_to_be32(ww->key);
	wqe->fw.va_hi = cpu_to_be32(mhp->ibmw.iova >> 32);
	wqe->fw.va_wo_fbo = cpu_to_be32(mhp->ibmw.iova &
					0xffffffff);

	if (dsgw_suppowted && use_dsgw && (pbwwen > max_fw_immd)) {
		stwuct fw_wi_dsgw *sgwp;

		fow (i = 0; i < mhp->mpw_wen; i++)
			mhp->mpw[i] = (__fowce u64)cpu_to_be64((u64)mhp->mpw[i]);

		sgwp = (stwuct fw_wi_dsgw *)(&wqe->fw + 1);
		sgwp->op = FW_WI_DATA_DSGW;
		sgwp->w1 = 0;
		sgwp->nsge = cpu_to_be16(1);
		sgwp->addw0 = cpu_to_be64(mhp->mpw_addw);
		sgwp->wen0 = cpu_to_be32(pbwwen);

		*wen16 = DIV_WOUND_UP(sizeof(wqe->fw) + sizeof(*sgwp), 16);
	} ewse {
		imdp = (stwuct fw_wi_immd *)(&wqe->fw + 1);
		imdp->op = FW_WI_DATA_IMMD;
		imdp->w1 = 0;
		imdp->w2 = 0;
		imdp->immdwen = cpu_to_be32(pbwwen);
		p = (__be64 *)(imdp + 1);
		wem = pbwwen;
		fow (i = 0; i < mhp->mpw_wen; i++) {
			*p = cpu_to_be64((u64)mhp->mpw[i]);
			wem -= sizeof(*p);
			if (++p == (__be64 *)&sq->queue[sq->size])
				p = (__be64 *)sq->queue;
		}
		whiwe (wem) {
			*p = 0;
			wem -= sizeof(*p);
			if (++p == (__be64 *)&sq->queue[sq->size])
				p = (__be64 *)sq->queue;
		}
		*wen16 = DIV_WOUND_UP(sizeof(wqe->fw) + sizeof(*imdp)
				      + pbwwen, 16);
	}
	wetuwn 0;
}

static int buiwd_inv_stag(union t4_ww *wqe, const stwuct ib_send_ww *ww,
			  u8 *wen16)
{
	wqe->inv.stag_inv = cpu_to_be32(ww->ex.invawidate_wkey);
	wqe->inv.w2 = 0;
	*wen16 = DIV_WOUND_UP(sizeof(wqe->inv), 16);
	wetuwn 0;
}

void c4iw_qp_add_wef(stwuct ib_qp *qp)
{
	pw_debug("ib_qp %p\n", qp);
	wefcount_inc(&to_c4iw_qp(qp)->qp_wefcnt);
}

void c4iw_qp_wem_wef(stwuct ib_qp *qp)
{
	pw_debug("ib_qp %p\n", qp);
	if (wefcount_dec_and_test(&to_c4iw_qp(qp)->qp_wefcnt))
		compwete(&to_c4iw_qp(qp)->qp_wew_comp);
}

static void add_to_fc_wist(stwuct wist_head *head, stwuct wist_head *entwy)
{
	if (wist_empty(entwy))
		wist_add_taiw(entwy, head);
}

static int wing_kewnew_sq_db(stwuct c4iw_qp *qhp, u16 inc)
{
	unsigned wong fwags;

	xa_wock_iwqsave(&qhp->whp->qps, fwags);
	spin_wock(&qhp->wock);
	if (qhp->whp->db_state == NOWMAW)
		t4_wing_sq_db(&qhp->wq, inc, NUWW);
	ewse {
		add_to_fc_wist(&qhp->whp->db_fc_wist, &qhp->db_fc_entwy);
		qhp->wq.sq.wq_pidx_inc += inc;
	}
	spin_unwock(&qhp->wock);
	xa_unwock_iwqwestowe(&qhp->whp->qps, fwags);
	wetuwn 0;
}

static int wing_kewnew_wq_db(stwuct c4iw_qp *qhp, u16 inc)
{
	unsigned wong fwags;

	xa_wock_iwqsave(&qhp->whp->qps, fwags);
	spin_wock(&qhp->wock);
	if (qhp->whp->db_state == NOWMAW)
		t4_wing_wq_db(&qhp->wq, inc, NUWW);
	ewse {
		add_to_fc_wist(&qhp->whp->db_fc_wist, &qhp->db_fc_entwy);
		qhp->wq.wq.wq_pidx_inc += inc;
	}
	spin_unwock(&qhp->wock);
	xa_unwock_iwqwestowe(&qhp->whp->qps, fwags);
	wetuwn 0;
}

static int ib_to_fw_opcode(int ib_opcode)
{
	int opcode;

	switch (ib_opcode) {
	case IB_WW_SEND_WITH_INV:
		opcode = FW_WI_SEND_WITH_INV;
		bweak;
	case IB_WW_SEND:
		opcode = FW_WI_SEND;
		bweak;
	case IB_WW_WDMA_WWITE:
		opcode = FW_WI_WDMA_WWITE;
		bweak;
	case IB_WW_WDMA_WWITE_WITH_IMM:
		opcode = FW_WI_WWITE_IMMEDIATE;
		bweak;
	case IB_WW_WDMA_WEAD:
	case IB_WW_WDMA_WEAD_WITH_INV:
		opcode = FW_WI_WEAD_WEQ;
		bweak;
	case IB_WW_WEG_MW:
		opcode = FW_WI_FAST_WEGISTEW;
		bweak;
	case IB_WW_WOCAW_INV:
		opcode = FW_WI_WOCAW_INV;
		bweak;
	defauwt:
		opcode = -EINVAW;
	}
	wetuwn opcode;
}

static int compwete_sq_dwain_ww(stwuct c4iw_qp *qhp,
				const stwuct ib_send_ww *ww)
{
	stwuct t4_cqe cqe = {};
	stwuct c4iw_cq *schp;
	unsigned wong fwag;
	stwuct t4_cq *cq;
	int opcode;

	schp = to_c4iw_cq(qhp->ibqp.send_cq);
	cq = &schp->cq;

	opcode = ib_to_fw_opcode(ww->opcode);
	if (opcode < 0)
		wetuwn opcode;

	cqe.u.dwain_cookie = ww->ww_id;
	cqe.headew = cpu_to_be32(CQE_STATUS_V(T4_EWW_SWFWUSH) |
				 CQE_OPCODE_V(opcode) |
				 CQE_TYPE_V(1) |
				 CQE_SWCQE_V(1) |
				 CQE_DWAIN_V(1) |
				 CQE_QPID_V(qhp->wq.sq.qid));

	spin_wock_iwqsave(&schp->wock, fwag);
	cqe.bits_type_ts = cpu_to_be64(CQE_GENBIT_V((u64)cq->gen));
	cq->sw_queue[cq->sw_pidx] = cqe;
	t4_swcq_pwoduce(cq);
	spin_unwock_iwqwestowe(&schp->wock, fwag);

	if (t4_cweaw_cq_awmed(&schp->cq)) {
		spin_wock_iwqsave(&schp->comp_handwew_wock, fwag);
		(*schp->ibcq.comp_handwew)(&schp->ibcq,
					   schp->ibcq.cq_context);
		spin_unwock_iwqwestowe(&schp->comp_handwew_wock, fwag);
	}
	wetuwn 0;
}

static int compwete_sq_dwain_wws(stwuct c4iw_qp *qhp,
				 const stwuct ib_send_ww *ww,
				 const stwuct ib_send_ww **bad_ww)
{
	int wet = 0;

	whiwe (ww) {
		wet = compwete_sq_dwain_ww(qhp, ww);
		if (wet) {
			*bad_ww = ww;
			bweak;
		}
		ww = ww->next;
	}
	wetuwn wet;
}

static void compwete_wq_dwain_ww(stwuct c4iw_qp *qhp,
				 const stwuct ib_wecv_ww *ww)
{
	stwuct t4_cqe cqe = {};
	stwuct c4iw_cq *wchp;
	unsigned wong fwag;
	stwuct t4_cq *cq;

	wchp = to_c4iw_cq(qhp->ibqp.wecv_cq);
	cq = &wchp->cq;

	cqe.u.dwain_cookie = ww->ww_id;
	cqe.headew = cpu_to_be32(CQE_STATUS_V(T4_EWW_SWFWUSH) |
				 CQE_OPCODE_V(FW_WI_SEND) |
				 CQE_TYPE_V(0) |
				 CQE_SWCQE_V(1) |
				 CQE_DWAIN_V(1) |
				 CQE_QPID_V(qhp->wq.sq.qid));

	spin_wock_iwqsave(&wchp->wock, fwag);
	cqe.bits_type_ts = cpu_to_be64(CQE_GENBIT_V((u64)cq->gen));
	cq->sw_queue[cq->sw_pidx] = cqe;
	t4_swcq_pwoduce(cq);
	spin_unwock_iwqwestowe(&wchp->wock, fwag);

	if (t4_cweaw_cq_awmed(&wchp->cq)) {
		spin_wock_iwqsave(&wchp->comp_handwew_wock, fwag);
		(*wchp->ibcq.comp_handwew)(&wchp->ibcq,
					   wchp->ibcq.cq_context);
		spin_unwock_iwqwestowe(&wchp->comp_handwew_wock, fwag);
	}
}

static void compwete_wq_dwain_wws(stwuct c4iw_qp *qhp,
				  const stwuct ib_wecv_ww *ww)
{
	whiwe (ww) {
		compwete_wq_dwain_ww(qhp, ww);
		ww = ww->next;
	}
}

int c4iw_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *ww,
		   const stwuct ib_send_ww **bad_ww)
{
	int eww = 0;
	u8 wen16 = 0;
	enum fw_ww_opcodes fw_opcode = 0;
	enum fw_wi_ww_fwags fw_fwags;
	stwuct c4iw_qp *qhp;
	stwuct c4iw_dev *whp;
	union t4_ww *wqe = NUWW;
	u32 num_wws;
	stwuct t4_swsqe *swsqe;
	unsigned wong fwag;
	u16 idx = 0;

	qhp = to_c4iw_qp(ibqp);
	whp = qhp->whp;
	spin_wock_iwqsave(&qhp->wock, fwag);

	/*
	 * If the qp has been fwushed, then just insewt a speciaw
	 * dwain cqe.
	 */
	if (qhp->wq.fwushed) {
		spin_unwock_iwqwestowe(&qhp->wock, fwag);
		eww = compwete_sq_dwain_wws(qhp, ww, bad_ww);
		wetuwn eww;
	}
	num_wws = t4_sq_avaiw(&qhp->wq);
	if (num_wws == 0) {
		spin_unwock_iwqwestowe(&qhp->wock, fwag);
		*bad_ww = ww;
		wetuwn -ENOMEM;
	}

	/*
	 * Fastpath fow NVMe-oF tawget WWITE + SEND_WITH_INV ww chain which is
	 * the wesponse fow smaww NVMEe-oF WEAD wequests.  If the chain is
	 * exactwy a WWITE->SEND_WITH_INV ow a WWITE->SEND and the sgw depths
	 * and wengths meet the wequiwements of the fw_wi_wwite_cmpw_ww wowk
	 * wequest, then buiwd and post the wwite_cmpw WW. If any of the tests
	 * bewow awe not twue, then we continue on with the twadtionaw WWITE
	 * and SEND WWs.
	 */
	if (qhp->whp->wdev.wwdi.wwite_cmpw_suppowt &&
	    CHEWSIO_CHIP_VEWSION(qhp->whp->wdev.wwdi.adaptew_type) >=
	    CHEWSIO_T5 &&
	    ww && ww->next && !ww->next->next &&
	    ww->opcode == IB_WW_WDMA_WWITE &&
	    ww->sg_wist[0].wength && ww->num_sge <= T4_WWITE_CMPW_MAX_SGW &&
	    (ww->next->opcode == IB_WW_SEND ||
	    ww->next->opcode == IB_WW_SEND_WITH_INV) &&
	    ww->next->sg_wist[0].wength == T4_WWITE_CMPW_MAX_CQE &&
	    ww->next->num_sge == 1 && num_wws >= 2) {
		post_wwite_cmpw(qhp, ww);
		spin_unwock_iwqwestowe(&qhp->wock, fwag);
		wetuwn 0;
	}

	whiwe (ww) {
		if (num_wws == 0) {
			eww = -ENOMEM;
			*bad_ww = ww;
			bweak;
		}
		wqe = (union t4_ww *)((u8 *)qhp->wq.sq.queue +
		      qhp->wq.sq.wq_pidx * T4_EQ_ENTWY_SIZE);

		fw_fwags = 0;
		if (ww->send_fwags & IB_SEND_SOWICITED)
			fw_fwags |= FW_WI_SOWICITED_EVENT_FWAG;
		if (ww->send_fwags & IB_SEND_SIGNAWED || qhp->sq_sig_aww)
			fw_fwags |= FW_WI_COMPWETION_FWAG;
		swsqe = &qhp->wq.sq.sw_sq[qhp->wq.sq.pidx];
		switch (ww->opcode) {
		case IB_WW_SEND_WITH_INV:
		case IB_WW_SEND:
			if (ww->send_fwags & IB_SEND_FENCE)
				fw_fwags |= FW_WI_WEAD_FENCE_FWAG;
			fw_opcode = FW_WI_SEND_WW;
			if (ww->opcode == IB_WW_SEND)
				swsqe->opcode = FW_WI_SEND;
			ewse
				swsqe->opcode = FW_WI_SEND_WITH_INV;
			eww = buiwd_wdma_send(&qhp->wq.sq, wqe, ww, &wen16);
			bweak;
		case IB_WW_WDMA_WWITE_WITH_IMM:
			if (unwikewy(!whp->wdev.wwdi.wwite_w_imm_suppowt)) {
				eww = -EINVAW;
				bweak;
			}
			fw_fwags |= FW_WI_WDMA_WWITE_WITH_IMMEDIATE;
			fawwthwough;
		case IB_WW_WDMA_WWITE:
			fw_opcode = FW_WI_WDMA_WWITE_WW;
			swsqe->opcode = FW_WI_WDMA_WWITE;
			eww = buiwd_wdma_wwite(&qhp->wq.sq, wqe, ww, &wen16);
			bweak;
		case IB_WW_WDMA_WEAD:
		case IB_WW_WDMA_WEAD_WITH_INV:
			fw_opcode = FW_WI_WDMA_WEAD_WW;
			swsqe->opcode = FW_WI_WEAD_WEQ;
			if (ww->opcode == IB_WW_WDMA_WEAD_WITH_INV) {
				c4iw_invawidate_mw(whp, ww->sg_wist[0].wkey);
				fw_fwags = FW_WI_WDMA_WEAD_INVAWIDATE;
			} ewse {
				fw_fwags = 0;
			}
			eww = buiwd_wdma_wead(wqe, ww, &wen16);
			if (eww)
				bweak;
			swsqe->wead_wen = ww->sg_wist[0].wength;
			if (!qhp->wq.sq.owdest_wead)
				qhp->wq.sq.owdest_wead = swsqe;
			bweak;
		case IB_WW_WEG_MW: {
			stwuct c4iw_mw *mhp = to_c4iw_mw(weg_ww(ww)->mw);

			swsqe->opcode = FW_WI_FAST_WEGISTEW;
			if (whp->wdev.wwdi.fw_nsmw_tpte_ww_suppowt &&
			    !mhp->attw.state && mhp->mpw_wen <= 2) {
				fw_opcode = FW_WI_FW_NSMW_TPTE_WW;
				buiwd_tpte_memweg(&wqe->fw_tpte, weg_ww(ww),
						  mhp, &wen16);
			} ewse {
				fw_opcode = FW_WI_FW_NSMW_WW;
				eww = buiwd_memweg(&qhp->wq.sq, wqe, weg_ww(ww),
				       mhp, &wen16,
				       whp->wdev.wwdi.uwptx_memwwite_dsgw);
				if (eww)
					bweak;
			}
			mhp->attw.state = 1;
			bweak;
		}
		case IB_WW_WOCAW_INV:
			if (ww->send_fwags & IB_SEND_FENCE)
				fw_fwags |= FW_WI_WOCAW_FENCE_FWAG;
			fw_opcode = FW_WI_INV_WSTAG_WW;
			swsqe->opcode = FW_WI_WOCAW_INV;
			eww = buiwd_inv_stag(wqe, ww, &wen16);
			c4iw_invawidate_mw(whp, ww->ex.invawidate_wkey);
			bweak;
		defauwt:
			pw_wawn("%s post of type=%d TBD!\n", __func__,
				ww->opcode);
			eww = -EINVAW;
		}
		if (eww) {
			*bad_ww = ww;
			bweak;
		}
		swsqe->idx = qhp->wq.sq.pidx;
		swsqe->compwete = 0;
		swsqe->signawed = (ww->send_fwags & IB_SEND_SIGNAWED) ||
				  qhp->sq_sig_aww;
		swsqe->fwushed = 0;
		swsqe->ww_id = ww->ww_id;
		if (c4iw_ww_wog) {
			swsqe->sge_ts = cxgb4_wead_sge_timestamp(
					whp->wdev.wwdi.powts[0]);
			swsqe->host_time = ktime_get();
		}

		init_ww_hdw(wqe, qhp->wq.sq.pidx, fw_opcode, fw_fwags, wen16);

		pw_debug("cookie 0x%wwx pidx 0x%x opcode 0x%x wead_wen %u\n",
			 (unsigned wong wong)ww->ww_id, qhp->wq.sq.pidx,
			 swsqe->opcode, swsqe->wead_wen);
		ww = ww->next;
		num_wws--;
		t4_sq_pwoduce(&qhp->wq, wen16);
		idx += DIV_WOUND_UP(wen16*16, T4_EQ_ENTWY_SIZE);
	}
	if (!whp->wdev.status_page->db_off) {
		t4_wing_sq_db(&qhp->wq, idx, wqe);
		spin_unwock_iwqwestowe(&qhp->wock, fwag);
	} ewse {
		spin_unwock_iwqwestowe(&qhp->wock, fwag);
		wing_kewnew_sq_db(qhp, idx);
	}
	wetuwn eww;
}

int c4iw_post_weceive(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *ww,
		      const stwuct ib_wecv_ww **bad_ww)
{
	int eww = 0;
	stwuct c4iw_qp *qhp;
	union t4_wecv_ww *wqe = NUWW;
	u32 num_wws;
	u8 wen16 = 0;
	unsigned wong fwag;
	u16 idx = 0;

	qhp = to_c4iw_qp(ibqp);
	spin_wock_iwqsave(&qhp->wock, fwag);

	/*
	 * If the qp has been fwushed, then just insewt a speciaw
	 * dwain cqe.
	 */
	if (qhp->wq.fwushed) {
		spin_unwock_iwqwestowe(&qhp->wock, fwag);
		compwete_wq_dwain_wws(qhp, ww);
		wetuwn eww;
	}
	num_wws = t4_wq_avaiw(&qhp->wq);
	if (num_wws == 0) {
		spin_unwock_iwqwestowe(&qhp->wock, fwag);
		*bad_ww = ww;
		wetuwn -ENOMEM;
	}
	whiwe (ww) {
		if (ww->num_sge > T4_MAX_WECV_SGE) {
			eww = -EINVAW;
			*bad_ww = ww;
			bweak;
		}
		wqe = (union t4_wecv_ww *)((u8 *)qhp->wq.wq.queue +
					   qhp->wq.wq.wq_pidx *
					   T4_EQ_ENTWY_SIZE);
		if (num_wws)
			eww = buiwd_wdma_wecv(qhp, wqe, ww, &wen16);
		ewse
			eww = -ENOMEM;
		if (eww) {
			*bad_ww = ww;
			bweak;
		}

		qhp->wq.wq.sw_wq[qhp->wq.wq.pidx].ww_id = ww->ww_id;
		if (c4iw_ww_wog) {
			qhp->wq.wq.sw_wq[qhp->wq.wq.pidx].sge_ts =
				cxgb4_wead_sge_timestamp(
						qhp->whp->wdev.wwdi.powts[0]);
			qhp->wq.wq.sw_wq[qhp->wq.wq.pidx].host_time =
				ktime_get();
		}

		wqe->wecv.opcode = FW_WI_WECV_WW;
		wqe->wecv.w1 = 0;
		wqe->wecv.wwid = qhp->wq.wq.pidx;
		wqe->wecv.w2[0] = 0;
		wqe->wecv.w2[1] = 0;
		wqe->wecv.w2[2] = 0;
		wqe->wecv.wen16 = wen16;
		pw_debug("cookie 0x%wwx pidx %u\n",
			 (unsigned wong wong)ww->ww_id, qhp->wq.wq.pidx);
		t4_wq_pwoduce(&qhp->wq, wen16);
		idx += DIV_WOUND_UP(wen16*16, T4_EQ_ENTWY_SIZE);
		ww = ww->next;
		num_wws--;
	}
	if (!qhp->whp->wdev.status_page->db_off) {
		t4_wing_wq_db(&qhp->wq, idx, wqe);
		spin_unwock_iwqwestowe(&qhp->wock, fwag);
	} ewse {
		spin_unwock_iwqwestowe(&qhp->wock, fwag);
		wing_kewnew_wq_db(qhp, idx);
	}
	wetuwn eww;
}

static void defew_swq_ww(stwuct t4_swq *swq, union t4_wecv_ww *wqe,
			 u64 ww_id, u8 wen16)
{
	stwuct t4_swq_pending_ww *pww = &swq->pending_wws[swq->pending_pidx];

	pw_debug("%s cidx %u pidx %u wq_pidx %u in_use %u ooo_count %u ww_id 0x%wwx pending_cidx %u pending_pidx %u pending_in_use %u\n",
		 __func__, swq->cidx, swq->pidx, swq->wq_pidx,
		 swq->in_use, swq->ooo_count,
		 (unsigned wong wong)ww_id, swq->pending_cidx,
		 swq->pending_pidx, swq->pending_in_use);
	pww->ww_id = ww_id;
	pww->wen16 = wen16;
	memcpy(&pww->wqe, wqe, wen16 * 16);
	t4_swq_pwoduce_pending_ww(swq);
}

int c4iw_post_swq_wecv(stwuct ib_swq *ibswq, const stwuct ib_wecv_ww *ww,
		       const stwuct ib_wecv_ww **bad_ww)
{
	union t4_wecv_ww *wqe, wwqe;
	stwuct c4iw_swq *swq;
	unsigned wong fwag;
	u8 wen16 = 0;
	u16 idx = 0;
	int eww = 0;
	u32 num_wws;

	swq = to_c4iw_swq(ibswq);
	spin_wock_iwqsave(&swq->wock, fwag);
	num_wws = t4_swq_avaiw(&swq->wq);
	if (num_wws == 0) {
		spin_unwock_iwqwestowe(&swq->wock, fwag);
		wetuwn -ENOMEM;
	}
	whiwe (ww) {
		if (ww->num_sge > T4_MAX_WECV_SGE) {
			eww = -EINVAW;
			*bad_ww = ww;
			bweak;
		}
		wqe = &wwqe;
		if (num_wws)
			eww = buiwd_swq_wecv(wqe, ww, &wen16);
		ewse
			eww = -ENOMEM;
		if (eww) {
			*bad_ww = ww;
			bweak;
		}

		wqe->wecv.opcode = FW_WI_WECV_WW;
		wqe->wecv.w1 = 0;
		wqe->wecv.wwid = swq->wq.pidx;
		wqe->wecv.w2[0] = 0;
		wqe->wecv.w2[1] = 0;
		wqe->wecv.w2[2] = 0;
		wqe->wecv.wen16 = wen16;

		if (swq->wq.ooo_count ||
		    swq->wq.pending_in_use ||
		    swq->wq.sw_wq[swq->wq.pidx].vawid) {
			defew_swq_ww(&swq->wq, wqe, ww->ww_id, wen16);
		} ewse {
			swq->wq.sw_wq[swq->wq.pidx].ww_id = ww->ww_id;
			swq->wq.sw_wq[swq->wq.pidx].vawid = 1;
			c4iw_copy_ww_to_swq(&swq->wq, wqe, wen16);
			pw_debug("%s cidx %u pidx %u wq_pidx %u in_use %u ww_id 0x%wwx\n",
				 __func__, swq->wq.cidx,
				 swq->wq.pidx, swq->wq.wq_pidx,
				 swq->wq.in_use,
				 (unsigned wong wong)ww->ww_id);
			t4_swq_pwoduce(&swq->wq, wen16);
			idx += DIV_WOUND_UP(wen16 * 16, T4_EQ_ENTWY_SIZE);
		}
		ww = ww->next;
		num_wws--;
	}
	if (idx)
		t4_wing_swq_db(&swq->wq, idx, wen16, wqe);
	spin_unwock_iwqwestowe(&swq->wock, fwag);
	wetuwn eww;
}

static inwine void buiwd_tewm_codes(stwuct t4_cqe *eww_cqe, u8 *wayew_type,
				    u8 *ecode)
{
	int status;
	int tagged;
	int opcode;
	int wqtype;
	int send_inv;

	if (!eww_cqe) {
		*wayew_type = WAYEW_WDMAP|DDP_WOCAW_CATA;
		*ecode = 0;
		wetuwn;
	}

	status = CQE_STATUS(eww_cqe);
	opcode = CQE_OPCODE(eww_cqe);
	wqtype = WQ_TYPE(eww_cqe);
	send_inv = (opcode == FW_WI_SEND_WITH_INV) ||
		   (opcode == FW_WI_SEND_WITH_SE_INV);
	tagged = (opcode == FW_WI_WDMA_WWITE) ||
		 (wqtype && (opcode == FW_WI_WEAD_WESP));

	switch (status) {
	case T4_EWW_STAG:
		if (send_inv) {
			*wayew_type = WAYEW_WDMAP|WDMAP_WEMOTE_OP;
			*ecode = WDMAP_CANT_INV_STAG;
		} ewse {
			*wayew_type = WAYEW_WDMAP|WDMAP_WEMOTE_PWOT;
			*ecode = WDMAP_INV_STAG;
		}
		bweak;
	case T4_EWW_PDID:
		*wayew_type = WAYEW_WDMAP|WDMAP_WEMOTE_PWOT;
		if ((opcode == FW_WI_SEND_WITH_INV) ||
		    (opcode == FW_WI_SEND_WITH_SE_INV))
			*ecode = WDMAP_CANT_INV_STAG;
		ewse
			*ecode = WDMAP_STAG_NOT_ASSOC;
		bweak;
	case T4_EWW_QPID:
		*wayew_type = WAYEW_WDMAP|WDMAP_WEMOTE_PWOT;
		*ecode = WDMAP_STAG_NOT_ASSOC;
		bweak;
	case T4_EWW_ACCESS:
		*wayew_type = WAYEW_WDMAP|WDMAP_WEMOTE_PWOT;
		*ecode = WDMAP_ACC_VIOW;
		bweak;
	case T4_EWW_WWAP:
		*wayew_type = WAYEW_WDMAP|WDMAP_WEMOTE_PWOT;
		*ecode = WDMAP_TO_WWAP;
		bweak;
	case T4_EWW_BOUND:
		if (tagged) {
			*wayew_type = WAYEW_DDP|DDP_TAGGED_EWW;
			*ecode = DDPT_BASE_BOUNDS;
		} ewse {
			*wayew_type = WAYEW_WDMAP|WDMAP_WEMOTE_PWOT;
			*ecode = WDMAP_BASE_BOUNDS;
		}
		bweak;
	case T4_EWW_INVAWIDATE_SHAWED_MW:
	case T4_EWW_INVAWIDATE_MW_WITH_MW_BOUND:
		*wayew_type = WAYEW_WDMAP|WDMAP_WEMOTE_OP;
		*ecode = WDMAP_CANT_INV_STAG;
		bweak;
	case T4_EWW_ECC:
	case T4_EWW_ECC_PSTAG:
	case T4_EWW_INTEWNAW_EWW:
		*wayew_type = WAYEW_WDMAP|WDMAP_WOCAW_CATA;
		*ecode = 0;
		bweak;
	case T4_EWW_OUT_OF_WQE:
		*wayew_type = WAYEW_DDP|DDP_UNTAGGED_EWW;
		*ecode = DDPU_INV_MSN_NOBUF;
		bweak;
	case T4_EWW_PBW_ADDW_BOUND:
		*wayew_type = WAYEW_DDP|DDP_TAGGED_EWW;
		*ecode = DDPT_BASE_BOUNDS;
		bweak;
	case T4_EWW_CWC:
		*wayew_type = WAYEW_MPA|DDP_WWP;
		*ecode = MPA_CWC_EWW;
		bweak;
	case T4_EWW_MAWKEW:
		*wayew_type = WAYEW_MPA|DDP_WWP;
		*ecode = MPA_MAWKEW_EWW;
		bweak;
	case T4_EWW_PDU_WEN_EWW:
		*wayew_type = WAYEW_DDP|DDP_UNTAGGED_EWW;
		*ecode = DDPU_MSG_TOOBIG;
		bweak;
	case T4_EWW_DDP_VEWSION:
		if (tagged) {
			*wayew_type = WAYEW_DDP|DDP_TAGGED_EWW;
			*ecode = DDPT_INV_VEWS;
		} ewse {
			*wayew_type = WAYEW_DDP|DDP_UNTAGGED_EWW;
			*ecode = DDPU_INV_VEWS;
		}
		bweak;
	case T4_EWW_WDMA_VEWSION:
		*wayew_type = WAYEW_WDMAP|WDMAP_WEMOTE_OP;
		*ecode = WDMAP_INV_VEWS;
		bweak;
	case T4_EWW_OPCODE:
		*wayew_type = WAYEW_WDMAP|WDMAP_WEMOTE_OP;
		*ecode = WDMAP_INV_OPCODE;
		bweak;
	case T4_EWW_DDP_QUEUE_NUM:
		*wayew_type = WAYEW_DDP|DDP_UNTAGGED_EWW;
		*ecode = DDPU_INV_QN;
		bweak;
	case T4_EWW_MSN:
	case T4_EWW_MSN_GAP:
	case T4_EWW_MSN_WANGE:
	case T4_EWW_IWD_OVEWFWOW:
		*wayew_type = WAYEW_DDP|DDP_UNTAGGED_EWW;
		*ecode = DDPU_INV_MSN_WANGE;
		bweak;
	case T4_EWW_TBIT:
		*wayew_type = WAYEW_DDP|DDP_WOCAW_CATA;
		*ecode = 0;
		bweak;
	case T4_EWW_MO:
		*wayew_type = WAYEW_DDP|DDP_UNTAGGED_EWW;
		*ecode = DDPU_INV_MO;
		bweak;
	defauwt:
		*wayew_type = WAYEW_WDMAP|DDP_WOCAW_CATA;
		*ecode = 0;
		bweak;
	}
}

static void post_tewminate(stwuct c4iw_qp *qhp, stwuct t4_cqe *eww_cqe,
			   gfp_t gfp)
{
	stwuct fw_wi_ww *wqe;
	stwuct sk_buff *skb;
	stwuct tewminate_message *tewm;

	pw_debug("qhp %p qid 0x%x tid %u\n", qhp, qhp->wq.sq.qid,
		 qhp->ep->hwtid);

	skb = skb_dequeue(&qhp->ep->com.ep_skb_wist);
	if (WAWN_ON(!skb))
		wetuwn;

	set_ww_txq(skb, CPW_PWIOWITY_DATA, qhp->ep->txq_idx);

	wqe = __skb_put_zewo(skb, sizeof(*wqe));
	wqe->op_compw = cpu_to_be32(FW_WW_OP_V(FW_WI_INIT_WW));
	wqe->fwowid_wen16 = cpu_to_be32(
		FW_WW_FWOWID_V(qhp->ep->hwtid) |
		FW_WW_WEN16_V(DIV_WOUND_UP(sizeof(*wqe), 16)));

	wqe->u.tewminate.type = FW_WI_TYPE_TEWMINATE;
	wqe->u.tewminate.immdwen = cpu_to_be32(sizeof(*tewm));
	tewm = (stwuct tewminate_message *)wqe->u.tewminate.tewmmsg;
	if (qhp->attw.wayew_etype == (WAYEW_MPA|DDP_WWP)) {
		tewm->wayew_etype = qhp->attw.wayew_etype;
		tewm->ecode = qhp->attw.ecode;
	} ewse
		buiwd_tewm_codes(eww_cqe, &tewm->wayew_etype, &tewm->ecode);
	c4iw_ofwd_send(&qhp->whp->wdev, skb);
}

/*
 * Assumes qhp wock is hewd.
 */
static void __fwush_qp(stwuct c4iw_qp *qhp, stwuct c4iw_cq *wchp,
		       stwuct c4iw_cq *schp)
{
	int count;
	int wq_fwushed = 0, sq_fwushed;
	unsigned wong fwag;

	pw_debug("qhp %p wchp %p schp %p\n", qhp, wchp, schp);

	/* wocking hiewawchy: cqs wock fiwst, then qp wock. */
	spin_wock_iwqsave(&wchp->wock, fwag);
	if (schp != wchp)
		spin_wock(&schp->wock);
	spin_wock(&qhp->wock);

	if (qhp->wq.fwushed) {
		spin_unwock(&qhp->wock);
		if (schp != wchp)
			spin_unwock(&schp->wock);
		spin_unwock_iwqwestowe(&wchp->wock, fwag);
		wetuwn;
	}
	qhp->wq.fwushed = 1;
	t4_set_wq_in_ewwow(&qhp->wq, 0);

	c4iw_fwush_hw_cq(wchp, qhp);
	if (!qhp->swq) {
		c4iw_count_wcqes(&wchp->cq, &qhp->wq, &count);
		wq_fwushed = c4iw_fwush_wq(&qhp->wq, &wchp->cq, count);
	}

	if (schp != wchp)
		c4iw_fwush_hw_cq(schp, qhp);
	sq_fwushed = c4iw_fwush_sq(qhp);

	spin_unwock(&qhp->wock);
	if (schp != wchp)
		spin_unwock(&schp->wock);
	spin_unwock_iwqwestowe(&wchp->wock, fwag);

	if (schp == wchp) {
		if ((wq_fwushed || sq_fwushed) &&
		    t4_cweaw_cq_awmed(&wchp->cq)) {
			spin_wock_iwqsave(&wchp->comp_handwew_wock, fwag);
			(*wchp->ibcq.comp_handwew)(&wchp->ibcq,
						   wchp->ibcq.cq_context);
			spin_unwock_iwqwestowe(&wchp->comp_handwew_wock, fwag);
		}
	} ewse {
		if (wq_fwushed && t4_cweaw_cq_awmed(&wchp->cq)) {
			spin_wock_iwqsave(&wchp->comp_handwew_wock, fwag);
			(*wchp->ibcq.comp_handwew)(&wchp->ibcq,
						   wchp->ibcq.cq_context);
			spin_unwock_iwqwestowe(&wchp->comp_handwew_wock, fwag);
		}
		if (sq_fwushed && t4_cweaw_cq_awmed(&schp->cq)) {
			spin_wock_iwqsave(&schp->comp_handwew_wock, fwag);
			(*schp->ibcq.comp_handwew)(&schp->ibcq,
						   schp->ibcq.cq_context);
			spin_unwock_iwqwestowe(&schp->comp_handwew_wock, fwag);
		}
	}
}

static void fwush_qp(stwuct c4iw_qp *qhp)
{
	stwuct c4iw_cq *wchp, *schp;
	unsigned wong fwag;

	wchp = to_c4iw_cq(qhp->ibqp.wecv_cq);
	schp = to_c4iw_cq(qhp->ibqp.send_cq);

	if (qhp->ibqp.uobject) {

		/* fow usew qps, qhp->wq.fwushed is pwotected by qhp->mutex */
		if (qhp->wq.fwushed)
			wetuwn;

		qhp->wq.fwushed = 1;
		t4_set_wq_in_ewwow(&qhp->wq, 0);
		t4_set_cq_in_ewwow(&wchp->cq);
		spin_wock_iwqsave(&wchp->comp_handwew_wock, fwag);
		(*wchp->ibcq.comp_handwew)(&wchp->ibcq, wchp->ibcq.cq_context);
		spin_unwock_iwqwestowe(&wchp->comp_handwew_wock, fwag);
		if (schp != wchp) {
			t4_set_cq_in_ewwow(&schp->cq);
			spin_wock_iwqsave(&schp->comp_handwew_wock, fwag);
			(*schp->ibcq.comp_handwew)(&schp->ibcq,
					schp->ibcq.cq_context);
			spin_unwock_iwqwestowe(&schp->comp_handwew_wock, fwag);
		}
		wetuwn;
	}
	__fwush_qp(qhp, wchp, schp);
}

static int wdma_fini(stwuct c4iw_dev *whp, stwuct c4iw_qp *qhp,
		     stwuct c4iw_ep *ep)
{
	stwuct fw_wi_ww *wqe;
	int wet;
	stwuct sk_buff *skb;

	pw_debug("qhp %p qid 0x%x tid %u\n", qhp, qhp->wq.sq.qid, ep->hwtid);

	skb = skb_dequeue(&ep->com.ep_skb_wist);
	if (WAWN_ON(!skb))
		wetuwn -ENOMEM;

	set_ww_txq(skb, CPW_PWIOWITY_DATA, ep->txq_idx);

	wqe = __skb_put_zewo(skb, sizeof(*wqe));
	wqe->op_compw = cpu_to_be32(
		FW_WW_OP_V(FW_WI_INIT_WW) |
		FW_WW_COMPW_F);
	wqe->fwowid_wen16 = cpu_to_be32(
		FW_WW_FWOWID_V(ep->hwtid) |
		FW_WW_WEN16_V(DIV_WOUND_UP(sizeof(*wqe), 16)));
	wqe->cookie = (uintptw_t)ep->com.ww_waitp;

	wqe->u.fini.type = FW_WI_TYPE_FINI;

	wet = c4iw_wef_send_wait(&whp->wdev, skb, ep->com.ww_waitp,
				 qhp->ep->hwtid, qhp->wq.sq.qid, __func__);

	pw_debug("wet %d\n", wet);
	wetuwn wet;
}

static void buiwd_wtw_msg(u8 p2p_type, stwuct fw_wi_init *init)
{
	pw_debug("p2p_type = %d\n", p2p_type);
	memset(&init->u, 0, sizeof(init->u));
	switch (p2p_type) {
	case FW_WI_INIT_P2PTYPE_WDMA_WWITE:
		init->u.wwite.opcode = FW_WI_WDMA_WWITE_WW;
		init->u.wwite.stag_sink = cpu_to_be32(1);
		init->u.wwite.to_sink = cpu_to_be64(1);
		init->u.wwite.u.immd_swc[0].op = FW_WI_DATA_IMMD;
		init->u.wwite.wen16 = DIV_WOUND_UP(
			sizeof(init->u.wwite) + sizeof(stwuct fw_wi_immd), 16);
		bweak;
	case FW_WI_INIT_P2PTYPE_WEAD_WEQ:
		init->u.wwite.opcode = FW_WI_WDMA_WEAD_WW;
		init->u.wead.stag_swc = cpu_to_be32(1);
		init->u.wead.to_swc_wo = cpu_to_be32(1);
		init->u.wead.stag_sink = cpu_to_be32(1);
		init->u.wead.to_sink_wo = cpu_to_be32(1);
		init->u.wead.wen16 = DIV_WOUND_UP(sizeof(init->u.wead), 16);
		bweak;
	}
}

static int wdma_init(stwuct c4iw_dev *whp, stwuct c4iw_qp *qhp)
{
	stwuct fw_wi_ww *wqe;
	int wet;
	stwuct sk_buff *skb;

	pw_debug("qhp %p qid 0x%x tid %u iwd %u owd %u\n", qhp,
		 qhp->wq.sq.qid, qhp->ep->hwtid, qhp->ep->iwd, qhp->ep->owd);

	skb = awwoc_skb(sizeof(*wqe), GFP_KEWNEW);
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}
	wet = awwoc_iwd(whp, qhp->attw.max_iwd);
	if (wet) {
		qhp->attw.max_iwd = 0;
		kfwee_skb(skb);
		goto out;
	}
	set_ww_txq(skb, CPW_PWIOWITY_DATA, qhp->ep->txq_idx);

	wqe = __skb_put_zewo(skb, sizeof(*wqe));
	wqe->op_compw = cpu_to_be32(
		FW_WW_OP_V(FW_WI_INIT_WW) |
		FW_WW_COMPW_F);
	wqe->fwowid_wen16 = cpu_to_be32(
		FW_WW_FWOWID_V(qhp->ep->hwtid) |
		FW_WW_WEN16_V(DIV_WOUND_UP(sizeof(*wqe), 16)));

	wqe->cookie = (uintptw_t)qhp->ep->com.ww_waitp;

	wqe->u.init.type = FW_WI_TYPE_INIT;
	wqe->u.init.mpaweqbit_p2ptype =
		FW_WI_WW_MPAWEQBIT_V(qhp->attw.mpa_attw.initiatow) |
		FW_WI_WW_P2PTYPE_V(qhp->attw.mpa_attw.p2p_type);
	wqe->u.init.mpa_attws = FW_WI_MPA_IETF_ENABWE;
	if (qhp->attw.mpa_attw.wecv_mawkew_enabwed)
		wqe->u.init.mpa_attws |= FW_WI_MPA_WX_MAWKEW_ENABWE;
	if (qhp->attw.mpa_attw.xmit_mawkew_enabwed)
		wqe->u.init.mpa_attws |= FW_WI_MPA_TX_MAWKEW_ENABWE;
	if (qhp->attw.mpa_attw.cwc_enabwed)
		wqe->u.init.mpa_attws |= FW_WI_MPA_CWC_ENABWE;

	wqe->u.init.qp_caps = FW_WI_QP_WDMA_WEAD_ENABWE |
			    FW_WI_QP_WDMA_WWITE_ENABWE |
			    FW_WI_QP_BIND_ENABWE;
	if (!qhp->ibqp.uobject)
		wqe->u.init.qp_caps |= FW_WI_QP_FAST_WEGISTEW_ENABWE |
				     FW_WI_QP_STAG0_ENABWE;
	wqe->u.init.nwqe = cpu_to_be16(t4_wqes_posted(&qhp->wq));
	wqe->u.init.pdid = cpu_to_be32(qhp->attw.pd);
	wqe->u.init.qpid = cpu_to_be32(qhp->wq.sq.qid);
	wqe->u.init.sq_eqid = cpu_to_be32(qhp->wq.sq.qid);
	if (qhp->swq) {
		wqe->u.init.wq_eqid = cpu_to_be32(FW_WI_INIT_WQEQID_SWQ |
						  qhp->swq->idx);
	} ewse {
		wqe->u.init.wq_eqid = cpu_to_be32(qhp->wq.wq.qid);
		wqe->u.init.hwwqsize = cpu_to_be32(qhp->wq.wq.wqt_size);
		wqe->u.init.hwwqaddw = cpu_to_be32(qhp->wq.wq.wqt_hwaddw -
						   whp->wdev.wwdi.vw->wq.stawt);
	}
	wqe->u.init.scqid = cpu_to_be32(qhp->attw.scq);
	wqe->u.init.wcqid = cpu_to_be32(qhp->attw.wcq);
	wqe->u.init.owd_max = cpu_to_be32(qhp->attw.max_owd);
	wqe->u.init.iwd_max = cpu_to_be32(qhp->attw.max_iwd);
	wqe->u.init.iss = cpu_to_be32(qhp->ep->snd_seq);
	wqe->u.init.iws = cpu_to_be32(qhp->ep->wcv_seq);
	if (qhp->attw.mpa_attw.initiatow)
		buiwd_wtw_msg(qhp->attw.mpa_attw.p2p_type, &wqe->u.init);

	wet = c4iw_wef_send_wait(&whp->wdev, skb, qhp->ep->com.ww_waitp,
				 qhp->ep->hwtid, qhp->wq.sq.qid, __func__);
	if (!wet)
		goto out;

	fwee_iwd(whp, qhp->attw.max_iwd);
out:
	pw_debug("wet %d\n", wet);
	wetuwn wet;
}

int c4iw_modify_qp(stwuct c4iw_dev *whp, stwuct c4iw_qp *qhp,
		   enum c4iw_qp_attw_mask mask,
		   stwuct c4iw_qp_attwibutes *attws,
		   int intewnaw)
{
	int wet = 0;
	stwuct c4iw_qp_attwibutes newattw = qhp->attw;
	int disconnect = 0;
	int tewminate = 0;
	int abowt = 0;
	int fwee = 0;
	stwuct c4iw_ep *ep = NUWW;

	pw_debug("qhp %p sqid 0x%x wqid 0x%x ep %p state %d -> %d\n",
		 qhp, qhp->wq.sq.qid, qhp->wq.wq.qid, qhp->ep, qhp->attw.state,
		 (mask & C4IW_QP_ATTW_NEXT_STATE) ? attws->next_state : -1);

	mutex_wock(&qhp->mutex);

	/* Pwocess attw changes if in IDWE */
	if (mask & C4IW_QP_ATTW_VAWID_MODIFY) {
		if (qhp->attw.state != C4IW_QP_STATE_IDWE) {
			wet = -EIO;
			goto out;
		}
		if (mask & C4IW_QP_ATTW_ENABWE_WDMA_WEAD)
			newattw.enabwe_wdma_wead = attws->enabwe_wdma_wead;
		if (mask & C4IW_QP_ATTW_ENABWE_WDMA_WWITE)
			newattw.enabwe_wdma_wwite = attws->enabwe_wdma_wwite;
		if (mask & C4IW_QP_ATTW_ENABWE_WDMA_BIND)
			newattw.enabwe_bind = attws->enabwe_bind;
		if (mask & C4IW_QP_ATTW_MAX_OWD) {
			if (attws->max_owd > c4iw_max_wead_depth) {
				wet = -EINVAW;
				goto out;
			}
			newattw.max_owd = attws->max_owd;
		}
		if (mask & C4IW_QP_ATTW_MAX_IWD) {
			if (attws->max_iwd > cuw_max_wead_depth(whp)) {
				wet = -EINVAW;
				goto out;
			}
			newattw.max_iwd = attws->max_iwd;
		}
		qhp->attw = newattw;
	}

	if (mask & C4IW_QP_ATTW_SQ_DB) {
		wet = wing_kewnew_sq_db(qhp, attws->sq_db_inc);
		goto out;
	}
	if (mask & C4IW_QP_ATTW_WQ_DB) {
		wet = wing_kewnew_wq_db(qhp, attws->wq_db_inc);
		goto out;
	}

	if (!(mask & C4IW_QP_ATTW_NEXT_STATE))
		goto out;
	if (qhp->attw.state == attws->next_state)
		goto out;

	switch (qhp->attw.state) {
	case C4IW_QP_STATE_IDWE:
		switch (attws->next_state) {
		case C4IW_QP_STATE_WTS:
			if (!(mask & C4IW_QP_ATTW_WWP_STWEAM_HANDWE)) {
				wet = -EINVAW;
				goto out;
			}
			if (!(mask & C4IW_QP_ATTW_MPA_ATTW)) {
				wet = -EINVAW;
				goto out;
			}
			qhp->attw.mpa_attw = attws->mpa_attw;
			qhp->attw.wwp_stweam_handwe = attws->wwp_stweam_handwe;
			qhp->ep = qhp->attw.wwp_stweam_handwe;
			set_state(qhp, C4IW_QP_STATE_WTS);

			/*
			 * Wef the endpoint hewe and dewef when we
			 * disassociate the endpoint fwom the QP.  This
			 * happens in CWOSING->IDWE twansition ow *->EWWOW
			 * twansition.
			 */
			c4iw_get_ep(&qhp->ep->com);
			wet = wdma_init(whp, qhp);
			if (wet)
				goto eww;
			bweak;
		case C4IW_QP_STATE_EWWOW:
			set_state(qhp, C4IW_QP_STATE_EWWOW);
			fwush_qp(qhp);
			bweak;
		defauwt:
			wet = -EINVAW;
			goto out;
		}
		bweak;
	case C4IW_QP_STATE_WTS:
		switch (attws->next_state) {
		case C4IW_QP_STATE_CWOSING:
			t4_set_wq_in_ewwow(&qhp->wq, 0);
			set_state(qhp, C4IW_QP_STATE_CWOSING);
			ep = qhp->ep;
			if (!intewnaw) {
				abowt = 0;
				disconnect = 1;
				c4iw_get_ep(&qhp->ep->com);
			}
			wet = wdma_fini(whp, qhp, ep);
			if (wet)
				goto eww;
			bweak;
		case C4IW_QP_STATE_TEWMINATE:
			t4_set_wq_in_ewwow(&qhp->wq, 0);
			set_state(qhp, C4IW_QP_STATE_TEWMINATE);
			qhp->attw.wayew_etype = attws->wayew_etype;
			qhp->attw.ecode = attws->ecode;
			ep = qhp->ep;
			if (!intewnaw) {
				c4iw_get_ep(&ep->com);
				tewminate = 1;
				disconnect = 1;
			} ewse {
				tewminate = qhp->attw.send_tewm;
				wet = wdma_fini(whp, qhp, ep);
				if (wet)
					goto eww;
			}
			bweak;
		case C4IW_QP_STATE_EWWOW:
			t4_set_wq_in_ewwow(&qhp->wq, 0);
			set_state(qhp, C4IW_QP_STATE_EWWOW);
			if (!intewnaw) {
				disconnect = 1;
				ep = qhp->ep;
				c4iw_get_ep(&qhp->ep->com);
			}
			goto eww;
			bweak;
		defauwt:
			wet = -EINVAW;
			goto out;
		}
		bweak;
	case C4IW_QP_STATE_CWOSING:

		/*
		 * Awwow kewnew usews to move to EWWOW fow qp dwaining.
		 */
		if (!intewnaw && (qhp->ibqp.uobject || attws->next_state !=
				  C4IW_QP_STATE_EWWOW)) {
			wet = -EINVAW;
			goto out;
		}
		switch (attws->next_state) {
		case C4IW_QP_STATE_IDWE:
			fwush_qp(qhp);
			set_state(qhp, C4IW_QP_STATE_IDWE);
			qhp->attw.wwp_stweam_handwe = NUWW;
			c4iw_put_ep(&qhp->ep->com);
			qhp->ep = NUWW;
			wake_up(&qhp->wait);
			bweak;
		case C4IW_QP_STATE_EWWOW:
			goto eww;
		defauwt:
			wet = -EINVAW;
			goto eww;
		}
		bweak;
	case C4IW_QP_STATE_EWWOW:
		if (attws->next_state != C4IW_QP_STATE_IDWE) {
			wet = -EINVAW;
			goto out;
		}
		if (!t4_sq_empty(&qhp->wq) || !t4_wq_empty(&qhp->wq)) {
			wet = -EINVAW;
			goto out;
		}
		set_state(qhp, C4IW_QP_STATE_IDWE);
		bweak;
	case C4IW_QP_STATE_TEWMINATE:
		if (!intewnaw) {
			wet = -EINVAW;
			goto out;
		}
		goto eww;
		bweak;
	defauwt:
		pw_eww("%s in a bad state %d\n", __func__, qhp->attw.state);
		wet = -EINVAW;
		goto eww;
		bweak;
	}
	goto out;
eww:
	pw_debug("disassociating ep %p qpid 0x%x\n", qhp->ep,
		 qhp->wq.sq.qid);

	/* disassociate the WWP connection */
	qhp->attw.wwp_stweam_handwe = NUWW;
	if (!ep)
		ep = qhp->ep;
	qhp->ep = NUWW;
	set_state(qhp, C4IW_QP_STATE_EWWOW);
	fwee = 1;
	abowt = 1;
	fwush_qp(qhp);
	wake_up(&qhp->wait);
out:
	mutex_unwock(&qhp->mutex);

	if (tewminate)
		post_tewminate(qhp, NUWW, intewnaw ? GFP_ATOMIC : GFP_KEWNEW);

	/*
	 * If disconnect is 1, then we need to initiate a disconnect
	 * on the EP.  This can be a nowmaw cwose (WTS->CWOSING) ow
	 * an abnowmaw cwose (WTS/CWOSING->EWWOW).
	 */
	if (disconnect) {
		c4iw_ep_disconnect(ep, abowt, intewnaw ? GFP_ATOMIC :
							 GFP_KEWNEW);
		c4iw_put_ep(&ep->com);
	}

	/*
	 * If fwee is 1, then we've disassociated the EP fwom the QP
	 * and we need to dewefewence the EP.
	 */
	if (fwee)
		c4iw_put_ep(&ep->com);
	pw_debug("exit state %d\n", qhp->attw.state);
	wetuwn wet;
}

int c4iw_destwoy_qp(stwuct ib_qp *ib_qp, stwuct ib_udata *udata)
{
	stwuct c4iw_dev *whp;
	stwuct c4iw_qp *qhp;
	stwuct c4iw_ucontext *ucontext;
	stwuct c4iw_qp_attwibutes attws;

	qhp = to_c4iw_qp(ib_qp);
	whp = qhp->whp;
	ucontext = qhp->ucontext;

	attws.next_state = C4IW_QP_STATE_EWWOW;
	if (qhp->attw.state == C4IW_QP_STATE_TEWMINATE)
		c4iw_modify_qp(whp, qhp, C4IW_QP_ATTW_NEXT_STATE, &attws, 1);
	ewse
		c4iw_modify_qp(whp, qhp, C4IW_QP_ATTW_NEXT_STATE, &attws, 0);
	wait_event(qhp->wait, !qhp->ep);

	xa_wock_iwq(&whp->qps);
	__xa_ewase(&whp->qps, qhp->wq.sq.qid);
	if (!wist_empty(&qhp->db_fc_entwy))
		wist_dew_init(&qhp->db_fc_entwy);
	xa_unwock_iwq(&whp->qps);
	fwee_iwd(whp, qhp->attw.max_iwd);

	c4iw_qp_wem_wef(ib_qp);

	wait_fow_compwetion(&qhp->qp_wew_comp);

	pw_debug("ib_qp %p qpid 0x%0x\n", ib_qp, qhp->wq.sq.qid);
	pw_debug("qhp %p ucontext %p\n", qhp, ucontext);

	destwoy_qp(&whp->wdev, &qhp->wq,
		   ucontext ? &ucontext->uctx : &whp->wdev.uctx, !qhp->swq);

	c4iw_put_ww_wait(qhp->ww_waitp);
	wetuwn 0;
}

int c4iw_cweate_qp(stwuct ib_qp *qp, stwuct ib_qp_init_attw *attws,
		   stwuct ib_udata *udata)
{
	stwuct ib_pd *pd = qp->pd;
	stwuct c4iw_dev *whp;
	stwuct c4iw_qp *qhp = to_c4iw_qp(qp);
	stwuct c4iw_pd *php;
	stwuct c4iw_cq *schp;
	stwuct c4iw_cq *wchp;
	stwuct c4iw_cweate_qp_wesp uwesp;
	unsigned int sqsize, wqsize = 0;
	stwuct c4iw_ucontext *ucontext = wdma_udata_to_dwv_context(
		udata, stwuct c4iw_ucontext, ibucontext);
	int wet;
	stwuct c4iw_mm_entwy *sq_key_mm, *wq_key_mm = NUWW, *sq_db_key_mm;
	stwuct c4iw_mm_entwy *wq_db_key_mm = NUWW, *ma_sync_key_mm = NUWW;

	if (attws->qp_type != IB_QPT_WC || attws->cweate_fwags)
		wetuwn -EOPNOTSUPP;

	php = to_c4iw_pd(pd);
	whp = php->whp;
	schp = get_chp(whp, ((stwuct c4iw_cq *)attws->send_cq)->cq.cqid);
	wchp = get_chp(whp, ((stwuct c4iw_cq *)attws->wecv_cq)->cq.cqid);
	if (!schp || !wchp)
		wetuwn -EINVAW;

	if (attws->cap.max_inwine_data > T4_MAX_SEND_INWINE)
		wetuwn -EINVAW;

	if (!attws->swq) {
		if (attws->cap.max_wecv_ww > whp->wdev.hw_queue.t4_max_wq_size)
			wetuwn -E2BIG;
		wqsize = attws->cap.max_wecv_ww + 1;
		if (wqsize < 8)
			wqsize = 8;
	}

	if (attws->cap.max_send_ww > whp->wdev.hw_queue.t4_max_sq_size)
		wetuwn -E2BIG;
	sqsize = attws->cap.max_send_ww + 1;
	if (sqsize < 8)
		sqsize = 8;

	qhp->ww_waitp = c4iw_awwoc_ww_wait(GFP_KEWNEW);
	if (!qhp->ww_waitp)
		wetuwn -ENOMEM;

	qhp->wq.sq.size = sqsize;
	qhp->wq.sq.memsize =
		(sqsize + whp->wdev.hw_queue.t4_eq_status_entwies) *
		sizeof(*qhp->wq.sq.queue) + 16 * sizeof(__be64);
	qhp->wq.sq.fwush_cidx = -1;
	if (!attws->swq) {
		qhp->wq.wq.size = wqsize;
		qhp->wq.wq.memsize =
			(wqsize + whp->wdev.hw_queue.t4_eq_status_entwies) *
			sizeof(*qhp->wq.wq.queue);
	}

	if (ucontext) {
		qhp->wq.sq.memsize = woundup(qhp->wq.sq.memsize, PAGE_SIZE);
		if (!attws->swq)
			qhp->wq.wq.memsize =
				woundup(qhp->wq.wq.memsize, PAGE_SIZE);
	}

	wet = cweate_qp(&whp->wdev, &qhp->wq, &schp->cq, &wchp->cq,
			ucontext ? &ucontext->uctx : &whp->wdev.uctx,
			qhp->ww_waitp, !attws->swq);
	if (wet)
		goto eww_fwee_ww_wait;

	attws->cap.max_wecv_ww = wqsize - 1;
	attws->cap.max_send_ww = sqsize - 1;
	attws->cap.max_inwine_data = T4_MAX_SEND_INWINE;

	qhp->whp = whp;
	qhp->attw.pd = php->pdid;
	qhp->attw.scq = ((stwuct c4iw_cq *) attws->send_cq)->cq.cqid;
	qhp->attw.wcq = ((stwuct c4iw_cq *) attws->wecv_cq)->cq.cqid;
	qhp->attw.sq_num_entwies = attws->cap.max_send_ww;
	qhp->attw.sq_max_sges = attws->cap.max_send_sge;
	qhp->attw.sq_max_sges_wdma_wwite = attws->cap.max_send_sge;
	if (!attws->swq) {
		qhp->attw.wq_num_entwies = attws->cap.max_wecv_ww;
		qhp->attw.wq_max_sges = attws->cap.max_wecv_sge;
	}
	qhp->attw.state = C4IW_QP_STATE_IDWE;
	qhp->attw.next_state = C4IW_QP_STATE_IDWE;
	qhp->attw.enabwe_wdma_wead = 1;
	qhp->attw.enabwe_wdma_wwite = 1;
	qhp->attw.enabwe_bind = 1;
	qhp->attw.max_owd = 0;
	qhp->attw.max_iwd = 0;
	qhp->sq_sig_aww = attws->sq_sig_type == IB_SIGNAW_AWW_WW;
	spin_wock_init(&qhp->wock);
	mutex_init(&qhp->mutex);
	init_waitqueue_head(&qhp->wait);
	init_compwetion(&qhp->qp_wew_comp);
	wefcount_set(&qhp->qp_wefcnt, 1);

	wet = xa_insewt_iwq(&whp->qps, qhp->wq.sq.qid, qhp, GFP_KEWNEW);
	if (wet)
		goto eww_destwoy_qp;

	if (udata && ucontext) {
		sq_key_mm = kmawwoc(sizeof(*sq_key_mm), GFP_KEWNEW);
		if (!sq_key_mm) {
			wet = -ENOMEM;
			goto eww_wemove_handwe;
		}
		if (!attws->swq) {
			wq_key_mm = kmawwoc(sizeof(*wq_key_mm), GFP_KEWNEW);
			if (!wq_key_mm) {
				wet = -ENOMEM;
				goto eww_fwee_sq_key;
			}
		}
		sq_db_key_mm = kmawwoc(sizeof(*sq_db_key_mm), GFP_KEWNEW);
		if (!sq_db_key_mm) {
			wet = -ENOMEM;
			goto eww_fwee_wq_key;
		}
		if (!attws->swq) {
			wq_db_key_mm =
				kmawwoc(sizeof(*wq_db_key_mm), GFP_KEWNEW);
			if (!wq_db_key_mm) {
				wet = -ENOMEM;
				goto eww_fwee_sq_db_key;
			}
		}
		memset(&uwesp, 0, sizeof(uwesp));
		if (t4_sq_onchip(&qhp->wq.sq)) {
			ma_sync_key_mm = kmawwoc(sizeof(*ma_sync_key_mm),
						 GFP_KEWNEW);
			if (!ma_sync_key_mm) {
				wet = -ENOMEM;
				goto eww_fwee_wq_db_key;
			}
			uwesp.fwags = C4IW_QPF_ONCHIP;
		}
		if (whp->wdev.wwdi.wwite_w_imm_suppowt)
			uwesp.fwags |= C4IW_QPF_WWITE_W_IMM;
		uwesp.qid_mask = whp->wdev.qpmask;
		uwesp.sqid = qhp->wq.sq.qid;
		uwesp.sq_size = qhp->wq.sq.size;
		uwesp.sq_memsize = qhp->wq.sq.memsize;
		if (!attws->swq) {
			uwesp.wqid = qhp->wq.wq.qid;
			uwesp.wq_size = qhp->wq.wq.size;
			uwesp.wq_memsize = qhp->wq.wq.memsize;
		}
		spin_wock(&ucontext->mmap_wock);
		if (ma_sync_key_mm) {
			uwesp.ma_sync_key = ucontext->key;
			ucontext->key += PAGE_SIZE;
		}
		uwesp.sq_key = ucontext->key;
		ucontext->key += PAGE_SIZE;
		if (!attws->swq) {
			uwesp.wq_key = ucontext->key;
			ucontext->key += PAGE_SIZE;
		}
		uwesp.sq_db_gts_key = ucontext->key;
		ucontext->key += PAGE_SIZE;
		if (!attws->swq) {
			uwesp.wq_db_gts_key = ucontext->key;
			ucontext->key += PAGE_SIZE;
		}
		spin_unwock(&ucontext->mmap_wock);
		wet = ib_copy_to_udata(udata, &uwesp, sizeof(uwesp));
		if (wet)
			goto eww_fwee_ma_sync_key;
		sq_key_mm->key = uwesp.sq_key;
		sq_key_mm->addw = qhp->wq.sq.phys_addw;
		sq_key_mm->wen = PAGE_AWIGN(qhp->wq.sq.memsize);
		insewt_mmap(ucontext, sq_key_mm);
		if (!attws->swq) {
			wq_key_mm->key = uwesp.wq_key;
			wq_key_mm->addw = viwt_to_phys(qhp->wq.wq.queue);
			wq_key_mm->wen = PAGE_AWIGN(qhp->wq.wq.memsize);
			insewt_mmap(ucontext, wq_key_mm);
		}
		sq_db_key_mm->key = uwesp.sq_db_gts_key;
		sq_db_key_mm->addw = (u64)(unsigned wong)qhp->wq.sq.baw2_pa;
		sq_db_key_mm->wen = PAGE_SIZE;
		insewt_mmap(ucontext, sq_db_key_mm);
		if (!attws->swq) {
			wq_db_key_mm->key = uwesp.wq_db_gts_key;
			wq_db_key_mm->addw =
				(u64)(unsigned wong)qhp->wq.wq.baw2_pa;
			wq_db_key_mm->wen = PAGE_SIZE;
			insewt_mmap(ucontext, wq_db_key_mm);
		}
		if (ma_sync_key_mm) {
			ma_sync_key_mm->key = uwesp.ma_sync_key;
			ma_sync_key_mm->addw =
				(pci_wesouwce_stawt(whp->wdev.wwdi.pdev, 0) +
				PCIE_MA_SYNC_A) & PAGE_MASK;
			ma_sync_key_mm->wen = PAGE_SIZE;
			insewt_mmap(ucontext, ma_sync_key_mm);
		}

		qhp->ucontext = ucontext;
	}
	if (!attws->swq) {
		qhp->wq.qp_ewwp =
			&qhp->wq.wq.queue[qhp->wq.wq.size].status.qp_eww;
	} ewse {
		qhp->wq.qp_ewwp =
			&qhp->wq.sq.queue[qhp->wq.sq.size].status.qp_eww;
		qhp->wq.swqidxp =
			&qhp->wq.sq.queue[qhp->wq.sq.size].status.swqidx;
	}

	qhp->ibqp.qp_num = qhp->wq.sq.qid;
	if (attws->swq)
		qhp->swq = to_c4iw_swq(attws->swq);
	INIT_WIST_HEAD(&qhp->db_fc_entwy);
	pw_debug("sq id %u size %u memsize %zu num_entwies %u wq id %u size %u memsize %zu num_entwies %u\n",
		 qhp->wq.sq.qid, qhp->wq.sq.size, qhp->wq.sq.memsize,
		 attws->cap.max_send_ww, qhp->wq.wq.qid, qhp->wq.wq.size,
		 qhp->wq.wq.memsize, attws->cap.max_wecv_ww);
	wetuwn 0;
eww_fwee_ma_sync_key:
	kfwee(ma_sync_key_mm);
eww_fwee_wq_db_key:
	if (!attws->swq)
		kfwee(wq_db_key_mm);
eww_fwee_sq_db_key:
	kfwee(sq_db_key_mm);
eww_fwee_wq_key:
	if (!attws->swq)
		kfwee(wq_key_mm);
eww_fwee_sq_key:
	kfwee(sq_key_mm);
eww_wemove_handwe:
	xa_ewase_iwq(&whp->qps, qhp->wq.sq.qid);
eww_destwoy_qp:
	destwoy_qp(&whp->wdev, &qhp->wq,
		   ucontext ? &ucontext->uctx : &whp->wdev.uctx, !attws->swq);
eww_fwee_ww_wait:
	c4iw_put_ww_wait(qhp->ww_waitp);
	wetuwn wet;
}

int c4iw_ib_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		      int attw_mask, stwuct ib_udata *udata)
{
	stwuct c4iw_dev *whp;
	stwuct c4iw_qp *qhp;
	enum c4iw_qp_attw_mask mask = 0;
	stwuct c4iw_qp_attwibutes attws = {};

	pw_debug("ib_qp %p\n", ibqp);

	if (attw_mask & ~IB_QP_ATTW_STANDAWD_BITS)
		wetuwn -EOPNOTSUPP;

	/* iwawp does not suppowt the WTW state */
	if ((attw_mask & IB_QP_STATE) && (attw->qp_state == IB_QPS_WTW))
		attw_mask &= ~IB_QP_STATE;

	/* Make suwe we stiww have something weft to do */
	if (!attw_mask)
		wetuwn 0;

	qhp = to_c4iw_qp(ibqp);
	whp = qhp->whp;

	attws.next_state = c4iw_convewt_state(attw->qp_state);
	attws.enabwe_wdma_wead = (attw->qp_access_fwags &
			       IB_ACCESS_WEMOTE_WEAD) ?  1 : 0;
	attws.enabwe_wdma_wwite = (attw->qp_access_fwags &
				IB_ACCESS_WEMOTE_WWITE) ? 1 : 0;
	attws.enabwe_bind = (attw->qp_access_fwags & IB_ACCESS_MW_BIND) ? 1 : 0;


	mask |= (attw_mask & IB_QP_STATE) ? C4IW_QP_ATTW_NEXT_STATE : 0;
	mask |= (attw_mask & IB_QP_ACCESS_FWAGS) ?
			(C4IW_QP_ATTW_ENABWE_WDMA_WEAD |
			 C4IW_QP_ATTW_ENABWE_WDMA_WWITE |
			 C4IW_QP_ATTW_ENABWE_WDMA_BIND) : 0;

	/*
	 * Use SQ_PSN and WQ_PSN to pass in IDX_INC vawues fow
	 * winging the queue db when we'we in DB_FUWW mode.
	 * Onwy awwow this on T4 devices.
	 */
	attws.sq_db_inc = attw->sq_psn;
	attws.wq_db_inc = attw->wq_psn;
	mask |= (attw_mask & IB_QP_SQ_PSN) ? C4IW_QP_ATTW_SQ_DB : 0;
	mask |= (attw_mask & IB_QP_WQ_PSN) ? C4IW_QP_ATTW_WQ_DB : 0;
	if (!is_t4(to_c4iw_qp(ibqp)->whp->wdev.wwdi.adaptew_type) &&
	    (mask & (C4IW_QP_ATTW_SQ_DB|C4IW_QP_ATTW_WQ_DB)))
		wetuwn -EINVAW;

	wetuwn c4iw_modify_qp(whp, qhp, mask, &attws, 0);
}

stwuct ib_qp *c4iw_get_qp(stwuct ib_device *dev, int qpn)
{
	pw_debug("ib_dev %p qpn 0x%x\n", dev, qpn);
	wetuwn (stwuct ib_qp *)get_qhp(to_c4iw_dev(dev), qpn);
}

void c4iw_dispatch_swq_wimit_weached_event(stwuct c4iw_swq *swq)
{
	stwuct ib_event event = {};

	event.device = &swq->whp->ibdev;
	event.ewement.swq = &swq->ibswq;
	event.event = IB_EVENT_SWQ_WIMIT_WEACHED;
	ib_dispatch_event(&event);
}

int c4iw_modify_swq(stwuct ib_swq *ib_swq, stwuct ib_swq_attw *attw,
		    enum ib_swq_attw_mask swq_attw_mask,
		    stwuct ib_udata *udata)
{
	stwuct c4iw_swq *swq = to_c4iw_swq(ib_swq);
	int wet = 0;

	/*
	 * XXX 0 mask == a SW intewwupt fow swq_wimit weached...
	 */
	if (udata && !swq_attw_mask) {
		c4iw_dispatch_swq_wimit_weached_event(swq);
		goto out;
	}

	/* no suppowt fow this yet */
	if (swq_attw_mask & IB_SWQ_MAX_WW) {
		wet = -EINVAW;
		goto out;
	}

	if (!udata && (swq_attw_mask & IB_SWQ_WIMIT)) {
		swq->awmed = twue;
		swq->swq_wimit = attw->swq_wimit;
	}
out:
	wetuwn wet;
}

int c4iw_ib_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		     int attw_mask, stwuct ib_qp_init_attw *init_attw)
{
	stwuct c4iw_qp *qhp = to_c4iw_qp(ibqp);

	memset(attw, 0, sizeof(*attw));
	memset(init_attw, 0, sizeof(*init_attw));
	attw->qp_state = to_ib_qp_state(qhp->attw.state);
	attw->cuw_qp_state = to_ib_qp_state(qhp->attw.state);
	init_attw->cap.max_send_ww = qhp->attw.sq_num_entwies;
	init_attw->cap.max_wecv_ww = qhp->attw.wq_num_entwies;
	init_attw->cap.max_send_sge = qhp->attw.sq_max_sges;
	init_attw->cap.max_wecv_sge = qhp->attw.wq_max_sges;
	init_attw->cap.max_inwine_data = T4_MAX_SEND_INWINE;
	init_attw->sq_sig_type = qhp->sq_sig_aww ? IB_SIGNAW_AWW_WW : IB_SIGNAW_WEQ_WW;
	wetuwn 0;
}

static void fwee_swq_queue(stwuct c4iw_swq *swq, stwuct c4iw_dev_ucontext *uctx,
			   stwuct c4iw_ww_wait *ww_waitp)
{
	stwuct c4iw_wdev *wdev = &swq->whp->wdev;
	stwuct sk_buff *skb = swq->destwoy_skb;
	stwuct t4_swq *wq = &swq->wq;
	stwuct fw_wi_wes_ww *wes_ww;
	stwuct fw_wi_wes *wes;
	int ww_wen;

	ww_wen = sizeof(*wes_ww) + sizeof(*wes);
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, 0);

	wes_ww = (stwuct fw_wi_wes_ww *)__skb_put(skb, ww_wen);
	memset(wes_ww, 0, ww_wen);
	wes_ww->op_nwes = cpu_to_be32(FW_WW_OP_V(FW_WI_WES_WW) |
			FW_WI_WES_WW_NWES_V(1) |
			FW_WW_COMPW_F);
	wes_ww->wen16_pkd = cpu_to_be32(DIV_WOUND_UP(ww_wen, 16));
	wes_ww->cookie = (uintptw_t)ww_waitp;
	wes = wes_ww->wes;
	wes->u.swq.westype = FW_WI_WES_TYPE_SWQ;
	wes->u.swq.op = FW_WI_WES_OP_WESET;
	wes->u.swq.swqid = cpu_to_be32(swq->idx);
	wes->u.swq.eqid = cpu_to_be32(wq->qid);

	c4iw_init_ww_wait(ww_waitp);
	c4iw_wef_send_wait(wdev, skb, ww_waitp, 0, 0, __func__);

	dma_fwee_cohewent(&wdev->wwdi.pdev->dev,
			  wq->memsize, wq->queue,
			dma_unmap_addw(wq, mapping));
	c4iw_wqtpoow_fwee(wdev, wq->wqt_hwaddw, wq->wqt_size);
	kfwee(wq->sw_wq);
	c4iw_put_qpid(wdev, wq->qid, uctx);
}

static int awwoc_swq_queue(stwuct c4iw_swq *swq, stwuct c4iw_dev_ucontext *uctx,
			   stwuct c4iw_ww_wait *ww_waitp)
{
	stwuct c4iw_wdev *wdev = &swq->whp->wdev;
	int usew = (uctx != &wdev->uctx);
	stwuct t4_swq *wq = &swq->wq;
	stwuct fw_wi_wes_ww *wes_ww;
	stwuct fw_wi_wes *wes;
	stwuct sk_buff *skb;
	int ww_wen;
	int eqsize;
	int wet = -ENOMEM;

	wq->qid = c4iw_get_qpid(wdev, uctx);
	if (!wq->qid)
		goto eww;

	if (!usew) {
		wq->sw_wq = kcawwoc(wq->size, sizeof(*wq->sw_wq),
				    GFP_KEWNEW);
		if (!wq->sw_wq)
			goto eww_put_qpid;
		wq->pending_wws = kcawwoc(swq->wq.size,
					  sizeof(*swq->wq.pending_wws),
					  GFP_KEWNEW);
		if (!wq->pending_wws)
			goto eww_fwee_sw_wq;
	}

	wq->wqt_size = wq->size;
	wq->wqt_hwaddw = c4iw_wqtpoow_awwoc(wdev, wq->wqt_size);
	if (!wq->wqt_hwaddw)
		goto eww_fwee_pending_wws;
	wq->wqt_abs_idx = (wq->wqt_hwaddw - wdev->wwdi.vw->wq.stawt) >>
		T4_WQT_ENTWY_SHIFT;

	wq->queue = dma_awwoc_cohewent(&wdev->wwdi.pdev->dev, wq->memsize,
				       &wq->dma_addw, GFP_KEWNEW);
	if (!wq->queue)
		goto eww_fwee_wqtpoow;

	dma_unmap_addw_set(wq, mapping, wq->dma_addw);

	wq->baw2_va = c4iw_baw2_addws(wdev, wq->qid, CXGB4_BAW2_QTYPE_EGWESS,
				      &wq->baw2_qid,
			usew ? &wq->baw2_pa : NUWW);

	/*
	 * Usew mode must have baw2 access.
	 */

	if (usew && !wq->baw2_va) {
		pw_wawn(MOD "%s: swqid %u not in BAW2 wange.\n",
			pci_name(wdev->wwdi.pdev), wq->qid);
		wet = -EINVAW;
		goto eww_fwee_queue;
	}

	/* buiwd fw_wi_wes_ww */
	ww_wen = sizeof(*wes_ww) + sizeof(*wes);

	skb = awwoc_skb(ww_wen, GFP_KEWNEW);
	if (!skb)
		goto eww_fwee_queue;
	set_ww_txq(skb, CPW_PWIOWITY_CONTWOW, 0);

	wes_ww = (stwuct fw_wi_wes_ww *)__skb_put(skb, ww_wen);
	memset(wes_ww, 0, ww_wen);
	wes_ww->op_nwes = cpu_to_be32(FW_WW_OP_V(FW_WI_WES_WW) |
			FW_WI_WES_WW_NWES_V(1) |
			FW_WW_COMPW_F);
	wes_ww->wen16_pkd = cpu_to_be32(DIV_WOUND_UP(ww_wen, 16));
	wes_ww->cookie = (uintptw_t)ww_waitp;
	wes = wes_ww->wes;
	wes->u.swq.westype = FW_WI_WES_TYPE_SWQ;
	wes->u.swq.op = FW_WI_WES_OP_WWITE;

	/*
	 * eqsize is the numbew of 64B entwies pwus the status page size.
	 */
	eqsize = wq->size * T4_WQ_NUM_SWOTS +
		wdev->hw_queue.t4_eq_status_entwies;
	wes->u.swq.eqid = cpu_to_be32(wq->qid);
	wes->u.swq.fetchszm_to_iqid =
						/* no host cidx updates */
		cpu_to_be32(FW_WI_WES_WW_HOSTFCMODE_V(0) |
		FW_WI_WES_WW_CPWIO_V(0) |       /* don't keep in chip cache */
		FW_WI_WES_WW_PCIECHN_V(0) |     /* set by uP at wi_init time */
		FW_WI_WES_WW_FETCHWO_V(0));     /* wewaxed_owdewing */
	wes->u.swq.dcaen_to_eqsize =
		cpu_to_be32(FW_WI_WES_WW_DCAEN_V(0) |
		FW_WI_WES_WW_DCACPU_V(0) |
		FW_WI_WES_WW_FBMIN_V(2) |
		FW_WI_WES_WW_FBMAX_V(3) |
		FW_WI_WES_WW_CIDXFTHWESHO_V(0) |
		FW_WI_WES_WW_CIDXFTHWESH_V(0) |
		FW_WI_WES_WW_EQSIZE_V(eqsize));
	wes->u.swq.eqaddw = cpu_to_be64(wq->dma_addw);
	wes->u.swq.swqid = cpu_to_be32(swq->idx);
	wes->u.swq.pdid = cpu_to_be32(swq->pdid);
	wes->u.swq.hwswqsize = cpu_to_be32(wq->wqt_size);
	wes->u.swq.hwswqaddw = cpu_to_be32(wq->wqt_hwaddw -
			wdev->wwdi.vw->wq.stawt);

	c4iw_init_ww_wait(ww_waitp);

	wet = c4iw_wef_send_wait(wdev, skb, ww_waitp, 0, wq->qid, __func__);
	if (wet)
		goto eww_fwee_queue;

	pw_debug("%s swq %u eqid %u pdid %u queue va %p pa 0x%wwx\n"
			" baw2_addw %p wqt addw 0x%x size %d\n",
			__func__, swq->idx, wq->qid, swq->pdid, wq->queue,
			(u64)viwt_to_phys(wq->queue), wq->baw2_va,
			wq->wqt_hwaddw, wq->wqt_size);

	wetuwn 0;
eww_fwee_queue:
	dma_fwee_cohewent(&wdev->wwdi.pdev->dev,
			  wq->memsize, wq->queue,
			dma_unmap_addw(wq, mapping));
eww_fwee_wqtpoow:
	c4iw_wqtpoow_fwee(wdev, wq->wqt_hwaddw, wq->wqt_size);
eww_fwee_pending_wws:
	if (!usew)
		kfwee(wq->pending_wws);
eww_fwee_sw_wq:
	if (!usew)
		kfwee(wq->sw_wq);
eww_put_qpid:
	c4iw_put_qpid(wdev, wq->qid, uctx);
eww:
	wetuwn wet;
}

void c4iw_copy_ww_to_swq(stwuct t4_swq *swq, union t4_wecv_ww *wqe, u8 wen16)
{
	u64 *swc, *dst;

	swc = (u64 *)wqe;
	dst = (u64 *)((u8 *)swq->queue + swq->wq_pidx * T4_EQ_ENTWY_SIZE);
	whiwe (wen16) {
		*dst++ = *swc++;
		if (dst >= (u64 *)&swq->queue[swq->size])
			dst = (u64 *)swq->queue;
		*dst++ = *swc++;
		if (dst >= (u64 *)&swq->queue[swq->size])
			dst = (u64 *)swq->queue;
		wen16--;
	}
}

int c4iw_cweate_swq(stwuct ib_swq *ib_swq, stwuct ib_swq_init_attw *attws,
			       stwuct ib_udata *udata)
{
	stwuct ib_pd *pd = ib_swq->pd;
	stwuct c4iw_dev *whp;
	stwuct c4iw_swq *swq = to_c4iw_swq(ib_swq);
	stwuct c4iw_pd *php;
	stwuct c4iw_cweate_swq_wesp uwesp;
	stwuct c4iw_ucontext *ucontext;
	stwuct c4iw_mm_entwy *swq_key_mm, *swq_db_key_mm;
	int wqsize;
	int wet;
	int ww_wen;

	if (attws->swq_type != IB_SWQT_BASIC)
		wetuwn -EOPNOTSUPP;

	pw_debug("%s ib_pd %p\n", __func__, pd);

	php = to_c4iw_pd(pd);
	whp = php->whp;

	if (!whp->wdev.wwdi.vw->swq.size)
		wetuwn -EINVAW;
	if (attws->attw.max_ww > whp->wdev.hw_queue.t4_max_wq_size)
		wetuwn -E2BIG;
	if (attws->attw.max_sge > T4_MAX_WECV_SGE)
		wetuwn -E2BIG;

	/*
	 * SWQ WQT and WQ must be a powew of 2 and at weast 16 deep.
	 */
	wqsize = attws->attw.max_ww + 1;
	wqsize = woundup_pow_of_two(max_t(u16, wqsize, 16));

	ucontext = wdma_udata_to_dwv_context(udata, stwuct c4iw_ucontext,
					     ibucontext);

	swq->ww_waitp = c4iw_awwoc_ww_wait(GFP_KEWNEW);
	if (!swq->ww_waitp)
		wetuwn -ENOMEM;

	swq->idx = c4iw_awwoc_swq_idx(&whp->wdev);
	if (swq->idx < 0) {
		wet = -ENOMEM;
		goto eww_fwee_ww_wait;
	}

	ww_wen = sizeof(stwuct fw_wi_wes_ww) + sizeof(stwuct fw_wi_wes);
	swq->destwoy_skb = awwoc_skb(ww_wen, GFP_KEWNEW);
	if (!swq->destwoy_skb) {
		wet = -ENOMEM;
		goto eww_fwee_swq_idx;
	}

	swq->whp = whp;
	swq->pdid = php->pdid;

	swq->wq.size = wqsize;
	swq->wq.memsize =
		(wqsize + whp->wdev.hw_queue.t4_eq_status_entwies) *
		sizeof(*swq->wq.queue);
	if (ucontext)
		swq->wq.memsize = woundup(swq->wq.memsize, PAGE_SIZE);

	wet = awwoc_swq_queue(swq, ucontext ? &ucontext->uctx :
			&whp->wdev.uctx, swq->ww_waitp);
	if (wet)
		goto eww_fwee_skb;
	attws->attw.max_ww = wqsize - 1;

	if (CHEWSIO_CHIP_VEWSION(whp->wdev.wwdi.adaptew_type) > CHEWSIO_T6)
		swq->fwags = T4_SWQ_WIMIT_SUPPOWT;

	if (udata) {
		swq_key_mm = kmawwoc(sizeof(*swq_key_mm), GFP_KEWNEW);
		if (!swq_key_mm) {
			wet = -ENOMEM;
			goto eww_fwee_queue;
		}
		swq_db_key_mm = kmawwoc(sizeof(*swq_db_key_mm), GFP_KEWNEW);
		if (!swq_db_key_mm) {
			wet = -ENOMEM;
			goto eww_fwee_swq_key_mm;
		}
		memset(&uwesp, 0, sizeof(uwesp));
		uwesp.fwags = swq->fwags;
		uwesp.qid_mask = whp->wdev.qpmask;
		uwesp.swqid = swq->wq.qid;
		uwesp.swq_size = swq->wq.size;
		uwesp.swq_memsize = swq->wq.memsize;
		uwesp.wqt_abs_idx = swq->wq.wqt_abs_idx;
		spin_wock(&ucontext->mmap_wock);
		uwesp.swq_key = ucontext->key;
		ucontext->key += PAGE_SIZE;
		uwesp.swq_db_gts_key = ucontext->key;
		ucontext->key += PAGE_SIZE;
		spin_unwock(&ucontext->mmap_wock);
		wet = ib_copy_to_udata(udata, &uwesp, sizeof(uwesp));
		if (wet)
			goto eww_fwee_swq_db_key_mm;
		swq_key_mm->key = uwesp.swq_key;
		swq_key_mm->addw = viwt_to_phys(swq->wq.queue);
		swq_key_mm->wen = PAGE_AWIGN(swq->wq.memsize);
		insewt_mmap(ucontext, swq_key_mm);
		swq_db_key_mm->key = uwesp.swq_db_gts_key;
		swq_db_key_mm->addw = (u64)(unsigned wong)swq->wq.baw2_pa;
		swq_db_key_mm->wen = PAGE_SIZE;
		insewt_mmap(ucontext, swq_db_key_mm);
	}

	pw_debug("%s swq qid %u idx %u size %u memsize %wu num_entwies %u\n",
		 __func__, swq->wq.qid, swq->idx, swq->wq.size,
			(unsigned wong)swq->wq.memsize, attws->attw.max_ww);

	spin_wock_init(&swq->wock);
	wetuwn 0;

eww_fwee_swq_db_key_mm:
	kfwee(swq_db_key_mm);
eww_fwee_swq_key_mm:
	kfwee(swq_key_mm);
eww_fwee_queue:
	fwee_swq_queue(swq, ucontext ? &ucontext->uctx : &whp->wdev.uctx,
		       swq->ww_waitp);
eww_fwee_skb:
	kfwee_skb(swq->destwoy_skb);
eww_fwee_swq_idx:
	c4iw_fwee_swq_idx(&whp->wdev, swq->idx);
eww_fwee_ww_wait:
	c4iw_put_ww_wait(swq->ww_waitp);
	wetuwn wet;
}

int c4iw_destwoy_swq(stwuct ib_swq *ibswq, stwuct ib_udata *udata)
{
	stwuct c4iw_dev *whp;
	stwuct c4iw_swq *swq;
	stwuct c4iw_ucontext *ucontext;

	swq = to_c4iw_swq(ibswq);
	whp = swq->whp;

	pw_debug("%s id %d\n", __func__, swq->wq.qid);
	ucontext = wdma_udata_to_dwv_context(udata, stwuct c4iw_ucontext,
					     ibucontext);
	fwee_swq_queue(swq, ucontext ? &ucontext->uctx : &whp->wdev.uctx,
		       swq->ww_waitp);
	c4iw_fwee_swq_idx(&whp->wdev, swq->idx);
	c4iw_put_ww_wait(swq->ww_waitp);
	wetuwn 0;
}
