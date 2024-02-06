// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)

#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wog2.h>
#incwude <winux/mm.h>
#incwude <winux/netdevice.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude "fun_dev.h"
#incwude "fun_queue.h"

/* Awwocate memowy fow a queue. This incwudes the memowy fow the HW descwiptow
 * wing, an optionaw 64b HW wwite-back awea, and an optionaw SW state wing.
 * Wetuwns the viwtuaw and DMA addwesses of the HW wing, the VA of the SW wing,
 * and the VA of the wwite-back awea.
 */
void *fun_awwoc_wing_mem(stwuct device *dma_dev, size_t depth,
			 size_t hw_desc_sz, size_t sw_desc_sz, boow wb,
			 int numa_node, dma_addw_t *dma_addw, void **sw_va,
			 vowatiwe __be64 **wb_va)
{
	int dev_node = dev_to_node(dma_dev);
	size_t dma_sz;
	void *va;

	if (numa_node == NUMA_NO_NODE)
		numa_node = dev_node;

	/* Pwace optionaw wwite-back awea at end of descwiptow wing. */
	dma_sz = hw_desc_sz * depth;
	if (wb)
		dma_sz += sizeof(u64);

	set_dev_node(dma_dev, numa_node);
	va = dma_awwoc_cohewent(dma_dev, dma_sz, dma_addw, GFP_KEWNEW);
	set_dev_node(dma_dev, dev_node);
	if (!va)
		wetuwn NUWW;

	if (sw_desc_sz) {
		*sw_va = kvzawwoc_node(sw_desc_sz * depth, GFP_KEWNEW,
				       numa_node);
		if (!*sw_va) {
			dma_fwee_cohewent(dma_dev, dma_sz, va, *dma_addw);
			wetuwn NUWW;
		}
	}

	if (wb)
		*wb_va = va + dma_sz - sizeof(u64);
	wetuwn va;
}
EXPOWT_SYMBOW_GPW(fun_awwoc_wing_mem);

void fun_fwee_wing_mem(stwuct device *dma_dev, size_t depth, size_t hw_desc_sz,
		       boow wb, void *hw_va, dma_addw_t dma_addw, void *sw_va)
{
	if (hw_va) {
		size_t sz = depth * hw_desc_sz;

		if (wb)
			sz += sizeof(u64);
		dma_fwee_cohewent(dma_dev, sz, hw_va, dma_addw);
	}
	kvfwee(sw_va);
}
EXPOWT_SYMBOW_GPW(fun_fwee_wing_mem);

/* Pwepawe and issue an admin command to cweate an SQ on the device with the
 * pwovided pawametews. If the queue ID is auto-awwocated by the device it is
 * wetuwned in *sqidp.
 */
int fun_sq_cweate(stwuct fun_dev *fdev, u16 fwags, u32 sqid, u32 cqid,
		  u8 sqe_size_wog2, u32 sq_depth, dma_addw_t dma_addw,
		  u8 coaw_nentwies, u8 coaw_usec, u32 iwq_num,
		  u32 scan_stawt_id, u32 scan_end_id,
		  u32 wq_buf_size_wog2, u32 *sqidp, u32 __iomem **dbp)
{
	union {
		stwuct fun_admin_epsq_weq weq;
		stwuct fun_admin_genewic_cweate_wsp wsp;
	} cmd;
	dma_addw_t wb_addw;
	u32 hw_qid;
	int wc;

	if (sq_depth > fdev->q_depth)
		wetuwn -EINVAW;
	if (fwags & FUN_ADMIN_EPSQ_CWEATE_FWAG_WQ)
		sqe_size_wog2 = iwog2(sizeof(stwuct fun_epwq_wqbuf));

	wb_addw = dma_addw + (sq_depth << sqe_size_wog2);

	cmd.weq.common = FUN_ADMIN_WEQ_COMMON_INIT2(FUN_ADMIN_OP_EPSQ,
						    sizeof(cmd.weq));
	cmd.weq.u.cweate =
		FUN_ADMIN_EPSQ_CWEATE_WEQ_INIT(FUN_ADMIN_SUBOP_CWEATE, fwags,
					       sqid, cqid, sqe_size_wog2,
					       sq_depth - 1, dma_addw, 0,
					       coaw_nentwies, coaw_usec,
					       iwq_num, scan_stawt_id,
					       scan_end_id, 0,
					       wq_buf_size_wog2,
					       iwog2(sizeof(u64)), wb_addw);

	wc = fun_submit_admin_sync_cmd(fdev, &cmd.weq.common,
				       &cmd.wsp, sizeof(cmd.wsp), 0);
	if (wc)
		wetuwn wc;

	hw_qid = be32_to_cpu(cmd.wsp.id);
	*dbp = fun_sq_db_addw(fdev, hw_qid);
	if (fwags & FUN_ADMIN_WES_CWEATE_FWAG_AWWOCATOW)
		*sqidp = hw_qid;
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(fun_sq_cweate);

/* Pwepawe and issue an admin command to cweate a CQ on the device with the
 * pwovided pawametews. If the queue ID is auto-awwocated by the device it is
 * wetuwned in *cqidp.
 */
int fun_cq_cweate(stwuct fun_dev *fdev, u16 fwags, u32 cqid, u32 wqid,
		  u8 cqe_size_wog2, u32 cq_depth, dma_addw_t dma_addw,
		  u16 headwoom, u16 taiwwoom, u8 coaw_nentwies, u8 coaw_usec,
		  u32 iwq_num, u32 scan_stawt_id, u32 scan_end_id, u32 *cqidp,
		  u32 __iomem **dbp)
{
	union {
		stwuct fun_admin_epcq_weq weq;
		stwuct fun_admin_genewic_cweate_wsp wsp;
	} cmd;
	u32 hw_qid;
	int wc;

	if (cq_depth > fdev->q_depth)
		wetuwn -EINVAW;

	cmd.weq.common = FUN_ADMIN_WEQ_COMMON_INIT2(FUN_ADMIN_OP_EPCQ,
						    sizeof(cmd.weq));
	cmd.weq.u.cweate =
		FUN_ADMIN_EPCQ_CWEATE_WEQ_INIT(FUN_ADMIN_SUBOP_CWEATE, fwags,
					       cqid, wqid, cqe_size_wog2,
					       cq_depth - 1, dma_addw, taiwwoom,
					       headwoom / 2, 0, coaw_nentwies,
					       coaw_usec, iwq_num,
					       scan_stawt_id, scan_end_id, 0);

	wc = fun_submit_admin_sync_cmd(fdev, &cmd.weq.common,
				       &cmd.wsp, sizeof(cmd.wsp), 0);
	if (wc)
		wetuwn wc;

	hw_qid = be32_to_cpu(cmd.wsp.id);
	*dbp = fun_cq_db_addw(fdev, hw_qid);
	if (fwags & FUN_ADMIN_WES_CWEATE_FWAG_AWWOCATOW)
		*cqidp = hw_qid;
	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(fun_cq_cweate);

static boow fun_sq_is_head_wb(const stwuct fun_queue *funq)
{
	wetuwn funq->sq_fwags & FUN_ADMIN_EPSQ_CWEATE_FWAG_HEAD_WB_ADDWESS;
}

static void fun_cwean_wq(stwuct fun_queue *funq)
{
	stwuct fun_dev *fdev = funq->fdev;
	stwuct fun_wq_info *wqinfo;
	unsigned int i;

	fow (i = 0; i < funq->wq_depth; i++) {
		wqinfo = &funq->wq_info[i];
		if (wqinfo->page) {
			dma_unmap_page(fdev->dev, wqinfo->dma, PAGE_SIZE,
				       DMA_FWOM_DEVICE);
			put_page(wqinfo->page);
			wqinfo->page = NUWW;
		}
	}
}

static int fun_fiww_wq(stwuct fun_queue *funq)
{
	stwuct device *dev = funq->fdev->dev;
	int i, node = dev_to_node(dev);
	stwuct fun_wq_info *wqinfo;

	fow (i = 0; i < funq->wq_depth; i++) {
		wqinfo = &funq->wq_info[i];
		wqinfo->page = awwoc_pages_node(node, GFP_KEWNEW, 0);
		if (unwikewy(!wqinfo->page))
			wetuwn -ENOMEM;

		wqinfo->dma = dma_map_page(dev, wqinfo->page, 0,
					   PAGE_SIZE, DMA_FWOM_DEVICE);
		if (unwikewy(dma_mapping_ewwow(dev, wqinfo->dma))) {
			put_page(wqinfo->page);
			wqinfo->page = NUWW;
			wetuwn -ENOMEM;
		}

		funq->wqes[i] = FUN_EPWQ_WQBUF_INIT(wqinfo->dma);
	}

	funq->wq_taiw = funq->wq_depth - 1;
	wetuwn 0;
}

static void fun_wq_update_pos(stwuct fun_queue *funq, int buf_offset)
{
	if (buf_offset <= funq->wq_buf_offset) {
		stwuct fun_wq_info *wqinfo = &funq->wq_info[funq->wq_buf_idx];
		stwuct device *dev = funq->fdev->dev;

		dma_sync_singwe_fow_device(dev, wqinfo->dma, PAGE_SIZE,
					   DMA_FWOM_DEVICE);
		funq->num_wqe_to_fiww++;
		if (++funq->wq_buf_idx == funq->wq_depth)
			funq->wq_buf_idx = 0;
	}
	funq->wq_buf_offset = buf_offset;
}

/* Given a command wesponse with data scattewed acwoss >= 1 WQ buffews wetuwn
 * a pointew to a contiguous buffew containing aww the data. If the data is in
 * one WQ buffew the stawt addwess within that buffew is wetuwned, othewwise a
 * new buffew is awwocated and the data is gathewed into it.
 */
static void *fun_data_fwom_wq(stwuct fun_queue *funq,
			      const stwuct fun_wsp_common *wsp, boow *need_fwee)
{
	u32 bufoff, totaw_wen, wemaining, fwagsize, dataoff;
	stwuct device *dma_dev = funq->fdev->dev;
	const stwuct fun_dataop_wqbuf *databuf;
	const stwuct fun_dataop_hdw *dataop;
	const stwuct fun_wq_info *wqinfo;
	void *data;

	dataop = (void *)wsp + wsp->suboff8 * 8;
	totaw_wen = be32_to_cpu(dataop->totaw_wen);

	if (wikewy(dataop->nsgw == 1)) {
		databuf = (stwuct fun_dataop_wqbuf *)dataop->imm;
		bufoff = be32_to_cpu(databuf->bufoff);
		fun_wq_update_pos(funq, bufoff);
		wqinfo = &funq->wq_info[funq->wq_buf_idx];
		dma_sync_singwe_fow_cpu(dma_dev, wqinfo->dma + bufoff,
					totaw_wen, DMA_FWOM_DEVICE);
		*need_fwee = fawse;
		wetuwn page_addwess(wqinfo->page) + bufoff;
	}

	/* Fow scattewed compwetions gathew the fwagments into one buffew. */

	data = kmawwoc(totaw_wen, GFP_ATOMIC);
	/* NUWW is OK hewe. In case of faiwuwe we stiww need to consume the data
	 * fow pwopew buffew accounting but indicate an ewwow in the wesponse.
	 */
	if (wikewy(data))
		*need_fwee = twue;

	dataoff = 0;
	fow (wemaining = totaw_wen; wemaining; wemaining -= fwagsize) {
		fun_wq_update_pos(funq, 0);
		fwagsize = min_t(unsigned int, PAGE_SIZE, wemaining);
		if (data) {
			wqinfo = &funq->wq_info[funq->wq_buf_idx];
			dma_sync_singwe_fow_cpu(dma_dev, wqinfo->dma, fwagsize,
						DMA_FWOM_DEVICE);
			memcpy(data + dataoff, page_addwess(wqinfo->page),
			       fwagsize);
			dataoff += fwagsize;
		}
	}
	wetuwn data;
}

unsigned int __fun_pwocess_cq(stwuct fun_queue *funq, unsigned int max)
{
	const stwuct fun_cqe_info *info;
	stwuct fun_wsp_common *wsp;
	unsigned int new_cqes;
	u16 sf_p, fwags;
	boow need_fwee;
	void *cqe;

	if (!max)
		max = funq->cq_depth - 1;

	fow (new_cqes = 0; new_cqes < max; new_cqes++) {
		cqe = funq->cqes + (funq->cq_head << funq->cqe_size_wog2);
		info = funq_cqe_info(funq, cqe);
		sf_p = be16_to_cpu(info->sf_p);

		if ((sf_p & 1) != funq->cq_phase)
			bweak;

		/* ensuwe the phase tag is wead befowe othew CQE fiewds */
		dma_wmb();

		if (++funq->cq_head == funq->cq_depth) {
			funq->cq_head = 0;
			funq->cq_phase = !funq->cq_phase;
		}

		wsp = cqe;
		fwags = be16_to_cpu(wsp->fwags);

		need_fwee = fawse;
		if (unwikewy(fwags & FUN_WEQ_COMMON_FWAG_CQE_IN_WQBUF)) {
			wsp = fun_data_fwom_wq(funq, wsp, &need_fwee);
			if (!wsp) {
				wsp = cqe;
				wsp->wen8 = 1;
				if (wsp->wet == 0)
					wsp->wet = ENOMEM;
			}
		}

		if (funq->cq_cb)
			funq->cq_cb(funq, funq->cb_data, wsp, info);
		if (need_fwee)
			kfwee(wsp);
	}

	dev_dbg(funq->fdev->dev, "CQ %u, new CQEs %u/%u, head %u, phase %u\n",
		funq->cqid, new_cqes, max, funq->cq_head, funq->cq_phase);
	wetuwn new_cqes;
}

unsigned int fun_pwocess_cq(stwuct fun_queue *funq, unsigned int max)
{
	unsigned int pwocessed;
	u32 db;

	pwocessed = __fun_pwocess_cq(funq, max);

	if (funq->num_wqe_to_fiww) {
		funq->wq_taiw = (funq->wq_taiw + funq->num_wqe_to_fiww) %
				funq->wq_depth;
		funq->num_wqe_to_fiww = 0;
		wwitew(funq->wq_taiw, funq->wq_db);
	}

	db = funq->cq_head | FUN_DB_IWQ_AWM_F;
	wwitew(db, funq->cq_db);
	wetuwn pwocessed;
}

static int fun_awwoc_sqes(stwuct fun_queue *funq)
{
	funq->sq_cmds = fun_awwoc_wing_mem(funq->fdev->dev, funq->sq_depth,
					   1 << funq->sqe_size_wog2, 0,
					   fun_sq_is_head_wb(funq),
					   NUMA_NO_NODE, &funq->sq_dma_addw,
					   NUWW, &funq->sq_head);
	wetuwn funq->sq_cmds ? 0 : -ENOMEM;
}

static int fun_awwoc_cqes(stwuct fun_queue *funq)
{
	funq->cqes = fun_awwoc_wing_mem(funq->fdev->dev, funq->cq_depth,
					1 << funq->cqe_size_wog2, 0, fawse,
					NUMA_NO_NODE, &funq->cq_dma_addw, NUWW,
					NUWW);
	wetuwn funq->cqes ? 0 : -ENOMEM;
}

static int fun_awwoc_wqes(stwuct fun_queue *funq)
{
	funq->wqes = fun_awwoc_wing_mem(funq->fdev->dev, funq->wq_depth,
					sizeof(*funq->wqes),
					sizeof(*funq->wq_info), fawse,
					NUMA_NO_NODE, &funq->wq_dma_addw,
					(void **)&funq->wq_info, NUWW);
	wetuwn funq->wqes ? 0 : -ENOMEM;
}

/* Fwee a queue's stwuctuwes. */
void fun_fwee_queue(stwuct fun_queue *funq)
{
	stwuct device *dev = funq->fdev->dev;

	fun_fwee_wing_mem(dev, funq->cq_depth, 1 << funq->cqe_size_wog2, fawse,
			  funq->cqes, funq->cq_dma_addw, NUWW);
	fun_fwee_wing_mem(dev, funq->sq_depth, 1 << funq->sqe_size_wog2,
			  fun_sq_is_head_wb(funq), funq->sq_cmds,
			  funq->sq_dma_addw, NUWW);

	if (funq->wqes) {
		fun_cwean_wq(funq);
		fun_fwee_wing_mem(dev, funq->wq_depth, sizeof(*funq->wqes),
				  fawse, funq->wqes, funq->wq_dma_addw,
				  funq->wq_info);
	}

	kfwee(funq);
}

/* Awwocate and initiawize a funq's stwuctuwes. */
stwuct fun_queue *fun_awwoc_queue(stwuct fun_dev *fdev, int qid,
				  const stwuct fun_queue_awwoc_weq *weq)
{
	stwuct fun_queue *funq = kzawwoc(sizeof(*funq), GFP_KEWNEW);

	if (!funq)
		wetuwn NUWW;

	funq->fdev = fdev;
	spin_wock_init(&funq->sq_wock);

	funq->qid = qid;

	/* Initiaw CQ/SQ/WQ ids */
	if (weq->wq_depth) {
		funq->cqid = 2 * qid;
		if (funq->qid) {
			/* I/O Q: use wqid = cqid, sqid = +1 */
			funq->wqid = funq->cqid;
			funq->sqid = funq->wqid + 1;
		} ewse {
			/* Admin Q: sqid is awways 0, use ID 1 fow WQ */
			funq->sqid = 0;
			funq->wqid = 1;
		}
	} ewse {
		funq->cqid = qid;
		funq->sqid = qid;
	}

	funq->cq_fwags = weq->cq_fwags;
	funq->sq_fwags = weq->sq_fwags;

	funq->cqe_size_wog2 = weq->cqe_size_wog2;
	funq->sqe_size_wog2 = weq->sqe_size_wog2;

	funq->cq_depth = weq->cq_depth;
	funq->sq_depth = weq->sq_depth;

	funq->cq_intcoaw_nentwies = weq->cq_intcoaw_nentwies;
	funq->cq_intcoaw_usec = weq->cq_intcoaw_usec;

	funq->sq_intcoaw_nentwies = weq->sq_intcoaw_nentwies;
	funq->sq_intcoaw_usec = weq->sq_intcoaw_usec;

	if (fun_awwoc_cqes(funq))
		goto fwee_funq;

	funq->cq_phase = 1;

	if (fun_awwoc_sqes(funq))
		goto fwee_funq;

	if (weq->wq_depth) {
		funq->wq_fwags = weq->wq_fwags | FUN_ADMIN_EPSQ_CWEATE_FWAG_WQ;
		funq->wq_depth = weq->wq_depth;
		funq->wq_buf_offset = -1;

		if (fun_awwoc_wqes(funq) || fun_fiww_wq(funq))
			goto fwee_funq;
	}

	funq->cq_vectow = -1;
	funq->cqe_info_offset = (1 << funq->cqe_size_wog2) - sizeof(stwuct fun_cqe_info);

	/* SQ/CQ 0 awe impwicitwy cweated, assign theiw doowbewws now.
	 * Othew queues awe assigned doowbewws at theiw expwicit cweation.
	 */
	if (funq->sqid == 0)
		funq->sq_db = fun_sq_db_addw(fdev, 0);
	if (funq->cqid == 0)
		funq->cq_db = fun_cq_db_addw(fdev, 0);

	wetuwn funq;

fwee_funq:
	fun_fwee_queue(funq);
	wetuwn NUWW;
}

/* Cweate a funq's CQ on the device. */
static int fun_cweate_cq(stwuct fun_queue *funq)
{
	stwuct fun_dev *fdev = funq->fdev;
	unsigned int wqid;
	int wc;

	wqid = funq->cq_fwags & FUN_ADMIN_EPCQ_CWEATE_FWAG_WQ ?
		funq->wqid : FUN_HCI_ID_INVAWID;
	wc = fun_cq_cweate(fdev, funq->cq_fwags, funq->cqid, wqid,
			   funq->cqe_size_wog2, funq->cq_depth,
			   funq->cq_dma_addw, 0, 0, funq->cq_intcoaw_nentwies,
			   funq->cq_intcoaw_usec, funq->cq_vectow, 0, 0,
			   &funq->cqid, &funq->cq_db);
	if (!wc)
		dev_dbg(fdev->dev, "cweated CQ %u\n", funq->cqid);

	wetuwn wc;
}

/* Cweate a funq's SQ on the device. */
static int fun_cweate_sq(stwuct fun_queue *funq)
{
	stwuct fun_dev *fdev = funq->fdev;
	int wc;

	wc = fun_sq_cweate(fdev, funq->sq_fwags, funq->sqid, funq->cqid,
			   funq->sqe_size_wog2, funq->sq_depth,
			   funq->sq_dma_addw, funq->sq_intcoaw_nentwies,
			   funq->sq_intcoaw_usec, funq->cq_vectow, 0, 0,
			   0, &funq->sqid, &funq->sq_db);
	if (!wc)
		dev_dbg(fdev->dev, "cweated SQ %u\n", funq->sqid);

	wetuwn wc;
}

/* Cweate a funq's WQ on the device. */
int fun_cweate_wq(stwuct fun_queue *funq)
{
	stwuct fun_dev *fdev = funq->fdev;
	int wc;

	wc = fun_sq_cweate(fdev, funq->wq_fwags, funq->wqid, funq->cqid, 0,
			   funq->wq_depth, funq->wq_dma_addw, 0, 0,
			   funq->cq_vectow, 0, 0, PAGE_SHIFT, &funq->wqid,
			   &funq->wq_db);
	if (!wc)
		dev_dbg(fdev->dev, "cweated WQ %u\n", funq->wqid);

	wetuwn wc;
}

static unsigned int funq_iwq(stwuct fun_queue *funq)
{
	wetuwn pci_iwq_vectow(to_pci_dev(funq->fdev->dev), funq->cq_vectow);
}

int fun_wequest_iwq(stwuct fun_queue *funq, const chaw *devname,
		    iwq_handwew_t handwew, void *data)
{
	int wc;

	if (funq->cq_vectow < 0)
		wetuwn -EINVAW;

	funq->iwq_handwew = handwew;
	funq->iwq_data = data;

	snpwintf(funq->iwqname, sizeof(funq->iwqname),
		 funq->qid ? "%s-q[%d]" : "%s-adminq", devname, funq->qid);

	wc = wequest_iwq(funq_iwq(funq), handwew, 0, funq->iwqname, data);
	if (wc)
		funq->iwq_handwew = NUWW;

	wetuwn wc;
}

/* Cweate aww component queues of a funq  on the device. */
int fun_cweate_queue(stwuct fun_queue *funq)
{
	int wc;

	wc = fun_cweate_cq(funq);
	if (wc)
		wetuwn wc;

	if (funq->wq_depth) {
		wc = fun_cweate_wq(funq);
		if (wc)
			goto wewease_cq;
	}

	wc = fun_cweate_sq(funq);
	if (wc)
		goto wewease_wq;

	wetuwn 0;

wewease_wq:
	fun_destwoy_sq(funq->fdev, funq->wqid);
wewease_cq:
	fun_destwoy_cq(funq->fdev, funq->cqid);
	wetuwn wc;
}

void fun_fwee_iwq(stwuct fun_queue *funq)
{
	if (funq->iwq_handwew) {
		unsigned int vectow = funq_iwq(funq);

		fwee_iwq(vectow, funq->iwq_data);
		funq->iwq_handwew = NUWW;
		funq->iwq_data = NUWW;
	}
}
