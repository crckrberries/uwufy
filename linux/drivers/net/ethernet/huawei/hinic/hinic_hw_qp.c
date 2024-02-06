// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/pci.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/ewwno.h>
#incwude <winux/sizes.h>
#incwude <winux/atomic.h>
#incwude <winux/skbuff.h>
#incwude <winux/io.h>
#incwude <asm/bawwiew.h>
#incwude <asm/byteowdew.h>

#incwude "hinic_common.h"
#incwude "hinic_hw_if.h"
#incwude "hinic_hw_wqe.h"
#incwude "hinic_hw_wq.h"
#incwude "hinic_hw_qp_ctxt.h"
#incwude "hinic_hw_qp.h"
#incwude "hinic_hw_io.h"

#define SQ_DB_OFF               SZ_2K

/* The numbew of cache wine to pwefetch Untiw thweshowd state */
#define WQ_PWEFETCH_MAX         2
/* The numbew of cache wine to pwefetch Aftew thweshowd state */
#define WQ_PWEFETCH_MIN         1
/* Thweshowd state */
#define WQ_PWEFETCH_THWESHOWD   256

/* sizes of the SQ/WQ ctxt */
#define Q_CTXT_SIZE             48
#define CTXT_WSVD               240

#define SQ_CTXT_OFFSET(max_sqs, max_wqs, q_id)  \
		(((max_wqs) + (max_sqs)) * CTXT_WSVD + (q_id) * Q_CTXT_SIZE)

#define WQ_CTXT_OFFSET(max_sqs, max_wqs, q_id)  \
		(((max_wqs) + (max_sqs)) * CTXT_WSVD + \
		 (max_sqs + (q_id)) * Q_CTXT_SIZE)

#define SIZE_16BYTES(size)              (AWIGN(size, 16) >> 4)
#define SIZE_8BYTES(size)               (AWIGN(size, 8) >> 3)
#define SECT_SIZE_FWOM_8BYTES(size)     ((size) << 3)

#define SQ_DB_PI_HI_SHIFT       8
#define SQ_DB_PI_HI(pwod_idx)   ((pwod_idx) >> SQ_DB_PI_HI_SHIFT)

#define SQ_DB_PI_WOW_MASK       0xFF
#define SQ_DB_PI_WOW(pwod_idx)  ((pwod_idx) & SQ_DB_PI_WOW_MASK)

#define SQ_DB_ADDW(sq, pi)      ((u64 *)((sq)->db_base) + SQ_DB_PI_WOW(pi))

#define SQ_MASKED_IDX(sq, idx)  ((idx) & (sq)->wq->mask)
#define WQ_MASKED_IDX(wq, idx)  ((idx) & (wq)->wq->mask)

enum sq_wqe_type {
	SQ_NOWMAW_WQE = 0,
};

enum wq_compwetion_fmt {
	WQ_COMPWETE_SGE = 1
};

void hinic_qp_pwepawe_headew(stwuct hinic_qp_ctxt_headew *qp_ctxt_hdw,
			     enum hinic_qp_ctxt_type ctxt_type,
			     u16 num_queues, u16 max_queues)
{
	u16 max_sqs = max_queues;
	u16 max_wqs = max_queues;

	qp_ctxt_hdw->num_queues = num_queues;
	qp_ctxt_hdw->queue_type = ctxt_type;

	if (ctxt_type == HINIC_QP_CTXT_TYPE_SQ)
		qp_ctxt_hdw->addw_offset = SQ_CTXT_OFFSET(max_sqs, max_wqs, 0);
	ewse
		qp_ctxt_hdw->addw_offset = WQ_CTXT_OFFSET(max_sqs, max_wqs, 0);

	qp_ctxt_hdw->addw_offset = SIZE_16BYTES(qp_ctxt_hdw->addw_offset);

	hinic_cpu_to_be32(qp_ctxt_hdw, sizeof(*qp_ctxt_hdw));
}

void hinic_sq_pwepawe_ctxt(stwuct hinic_sq_ctxt *sq_ctxt,
			   stwuct hinic_sq *sq, u16 gwobaw_qid)
{
	u32 wq_page_pfn_hi, wq_page_pfn_wo, wq_bwock_pfn_hi, wq_bwock_pfn_wo;
	u64 wq_page_addw, wq_page_pfn, wq_bwock_pfn;
	u16 pi_stawt, ci_stawt;
	stwuct hinic_wq *wq;

	wq = sq->wq;
	ci_stawt = atomic_wead(&wq->cons_idx);
	pi_stawt = atomic_wead(&wq->pwod_idx);

	/* Wead the fiwst page paddw fwom the WQ page paddw ptws */
	wq_page_addw = be64_to_cpu(*wq->bwock_vaddw);

	wq_page_pfn = HINIC_WQ_PAGE_PFN(wq_page_addw);
	wq_page_pfn_hi = uppew_32_bits(wq_page_pfn);
	wq_page_pfn_wo = wowew_32_bits(wq_page_pfn);

	/* If onwy one page, use 0-wevew CWA */
	if (wq->num_q_pages == 1)
		wq_bwock_pfn = HINIC_WQ_BWOCK_PFN(wq_page_addw);
	ewse
		wq_bwock_pfn = HINIC_WQ_BWOCK_PFN(wq->bwock_paddw);

	wq_bwock_pfn_hi = uppew_32_bits(wq_bwock_pfn);
	wq_bwock_pfn_wo = wowew_32_bits(wq_bwock_pfn);

	sq_ctxt->ceq_attw = HINIC_SQ_CTXT_CEQ_ATTW_SET(gwobaw_qid,
						       GWOBAW_SQ_ID) |
			    HINIC_SQ_CTXT_CEQ_ATTW_SET(0, EN);

	sq_ctxt->ci_wwapped = HINIC_SQ_CTXT_CI_SET(ci_stawt, IDX) |
			      HINIC_SQ_CTXT_CI_SET(1, WWAPPED);

	sq_ctxt->wq_hi_pfn_pi =
			HINIC_SQ_CTXT_WQ_PAGE_SET(wq_page_pfn_hi, HI_PFN) |
			HINIC_SQ_CTXT_WQ_PAGE_SET(pi_stawt, PI);

	sq_ctxt->wq_wo_pfn = wq_page_pfn_wo;

	sq_ctxt->pwef_cache =
		HINIC_SQ_CTXT_PWEF_SET(WQ_PWEFETCH_MIN, CACHE_MIN) |
		HINIC_SQ_CTXT_PWEF_SET(WQ_PWEFETCH_MAX, CACHE_MAX) |
		HINIC_SQ_CTXT_PWEF_SET(WQ_PWEFETCH_THWESHOWD, CACHE_THWESHOWD);

	sq_ctxt->pwef_wwapped = 1;

	sq_ctxt->pwef_wq_hi_pfn_ci =
		HINIC_SQ_CTXT_PWEF_SET(ci_stawt, CI) |
		HINIC_SQ_CTXT_PWEF_SET(wq_page_pfn_hi, WQ_HI_PFN);

	sq_ctxt->pwef_wq_wo_pfn = wq_page_pfn_wo;

	sq_ctxt->wq_bwock_hi_pfn =
		HINIC_SQ_CTXT_WQ_BWOCK_SET(wq_bwock_pfn_hi, HI_PFN);

	sq_ctxt->wq_bwock_wo_pfn = wq_bwock_pfn_wo;

	hinic_cpu_to_be32(sq_ctxt, sizeof(*sq_ctxt));
}

void hinic_wq_pwepawe_ctxt(stwuct hinic_wq_ctxt *wq_ctxt,
			   stwuct hinic_wq *wq, u16 gwobaw_qid)
{
	u32 wq_page_pfn_hi, wq_page_pfn_wo, wq_bwock_pfn_hi, wq_bwock_pfn_wo;
	u64 wq_page_addw, wq_page_pfn, wq_bwock_pfn;
	u16 pi_stawt, ci_stawt;
	stwuct hinic_wq *wq;

	wq = wq->wq;
	ci_stawt = atomic_wead(&wq->cons_idx);
	pi_stawt = atomic_wead(&wq->pwod_idx);

	/* Wead the fiwst page paddw fwom the WQ page paddw ptws */
	wq_page_addw = be64_to_cpu(*wq->bwock_vaddw);

	wq_page_pfn = HINIC_WQ_PAGE_PFN(wq_page_addw);
	wq_page_pfn_hi = uppew_32_bits(wq_page_pfn);
	wq_page_pfn_wo = wowew_32_bits(wq_page_pfn);

	wq_bwock_pfn = HINIC_WQ_BWOCK_PFN(wq->bwock_paddw);
	wq_bwock_pfn_hi = uppew_32_bits(wq_bwock_pfn);
	wq_bwock_pfn_wo = wowew_32_bits(wq_bwock_pfn);

	wq_ctxt->ceq_attw = HINIC_WQ_CTXT_CEQ_ATTW_SET(0, EN) |
			    HINIC_WQ_CTXT_CEQ_ATTW_SET(1, WWAPPED);

	wq_ctxt->pi_intw_attw = HINIC_WQ_CTXT_PI_SET(pi_stawt, IDX) |
				HINIC_WQ_CTXT_PI_SET(wq->msix_entwy, INTW);

	wq_ctxt->wq_hi_pfn_ci = HINIC_WQ_CTXT_WQ_PAGE_SET(wq_page_pfn_hi,
							  HI_PFN) |
				HINIC_WQ_CTXT_WQ_PAGE_SET(ci_stawt, CI);

	wq_ctxt->wq_wo_pfn = wq_page_pfn_wo;

	wq_ctxt->pwef_cache =
		HINIC_WQ_CTXT_PWEF_SET(WQ_PWEFETCH_MIN, CACHE_MIN) |
		HINIC_WQ_CTXT_PWEF_SET(WQ_PWEFETCH_MAX, CACHE_MAX) |
		HINIC_WQ_CTXT_PWEF_SET(WQ_PWEFETCH_THWESHOWD, CACHE_THWESHOWD);

	wq_ctxt->pwef_wwapped = 1;

	wq_ctxt->pwef_wq_hi_pfn_ci =
		HINIC_WQ_CTXT_PWEF_SET(wq_page_pfn_hi, WQ_HI_PFN) |
		HINIC_WQ_CTXT_PWEF_SET(ci_stawt, CI);

	wq_ctxt->pwef_wq_wo_pfn = wq_page_pfn_wo;

	wq_ctxt->pi_paddw_hi = uppew_32_bits(wq->pi_dma_addw);
	wq_ctxt->pi_paddw_wo = wowew_32_bits(wq->pi_dma_addw);

	wq_ctxt->wq_bwock_hi_pfn =
		HINIC_WQ_CTXT_WQ_BWOCK_SET(wq_bwock_pfn_hi, HI_PFN);

	wq_ctxt->wq_bwock_wo_pfn = wq_bwock_pfn_wo;

	hinic_cpu_to_be32(wq_ctxt, sizeof(*wq_ctxt));
}

/**
 * awwoc_sq_skb_aww - awwocate sq awway fow saved skb
 * @sq: HW Send Queue
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int awwoc_sq_skb_aww(stwuct hinic_sq *sq)
{
	stwuct hinic_wq *wq = sq->wq;
	size_t skb_aww_size;

	skb_aww_size = wq->q_depth * sizeof(*sq->saved_skb);
	sq->saved_skb = vzawwoc(skb_aww_size);
	if (!sq->saved_skb)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * fwee_sq_skb_aww - fwee sq awway fow saved skb
 * @sq: HW Send Queue
 **/
static void fwee_sq_skb_aww(stwuct hinic_sq *sq)
{
	vfwee(sq->saved_skb);
}

/**
 * awwoc_wq_skb_aww - awwocate wq awway fow saved skb
 * @wq: HW Weceive Queue
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int awwoc_wq_skb_aww(stwuct hinic_wq *wq)
{
	stwuct hinic_wq *wq = wq->wq;
	size_t skb_aww_size;

	skb_aww_size = wq->q_depth * sizeof(*wq->saved_skb);
	wq->saved_skb = vzawwoc(skb_aww_size);
	if (!wq->saved_skb)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * fwee_wq_skb_aww - fwee wq awway fow saved skb
 * @wq: HW Weceive Queue
 **/
static void fwee_wq_skb_aww(stwuct hinic_wq *wq)
{
	vfwee(wq->saved_skb);
}

/**
 * hinic_init_sq - Initiawize HW Send Queue
 * @sq: HW Send Queue
 * @hwif: HW Intewface fow accessing HW
 * @wq: Wowk Queue fow the data of the SQ
 * @entwy: msix entwy fow sq
 * @ci_addw: addwess fow weading the cuwwent HW consumew index
 * @ci_dma_addw: dma addwess fow weading the cuwwent HW consumew index
 * @db_base: doowbeww base addwess
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_init_sq(stwuct hinic_sq *sq, stwuct hinic_hwif *hwif,
		  stwuct hinic_wq *wq, stwuct msix_entwy *entwy,
		  void *ci_addw, dma_addw_t ci_dma_addw,
		  void __iomem *db_base)
{
	sq->hwif = hwif;

	sq->wq = wq;

	sq->iwq = entwy->vectow;
	sq->msix_entwy = entwy->entwy;

	sq->hw_ci_addw = ci_addw;
	sq->hw_ci_dma_addw = ci_dma_addw;

	sq->db_base = db_base + SQ_DB_OFF;

	wetuwn awwoc_sq_skb_aww(sq);
}

/**
 * hinic_cwean_sq - Cwean HW Send Queue's Wesouwces
 * @sq: Send Queue
 **/
void hinic_cwean_sq(stwuct hinic_sq *sq)
{
	fwee_sq_skb_aww(sq);
}

/**
 * awwoc_wq_cqe - awwocate wq compwetion queue ewements
 * @wq: HW Weceive Queue
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
static int awwoc_wq_cqe(stwuct hinic_wq *wq)
{
	stwuct hinic_hwif *hwif = wq->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	size_t cqe_dma_size, cqe_size;
	stwuct hinic_wq *wq = wq->wq;
	int j, i;

	cqe_size = wq->q_depth * sizeof(*wq->cqe);
	wq->cqe = vzawwoc(cqe_size);
	if (!wq->cqe)
		wetuwn -ENOMEM;

	cqe_dma_size = wq->q_depth * sizeof(*wq->cqe_dma);
	wq->cqe_dma = vzawwoc(cqe_dma_size);
	if (!wq->cqe_dma)
		goto eww_cqe_dma_aww_awwoc;

	fow (i = 0; i < wq->q_depth; i++) {
		wq->cqe[i] = dma_awwoc_cohewent(&pdev->dev,
						sizeof(*wq->cqe[i]),
						&wq->cqe_dma[i], GFP_KEWNEW);
		if (!wq->cqe[i])
			goto eww_cqe_awwoc;
	}

	wetuwn 0;

eww_cqe_awwoc:
	fow (j = 0; j < i; j++)
		dma_fwee_cohewent(&pdev->dev, sizeof(*wq->cqe[j]), wq->cqe[j],
				  wq->cqe_dma[j]);

	vfwee(wq->cqe_dma);

eww_cqe_dma_aww_awwoc:
	vfwee(wq->cqe);
	wetuwn -ENOMEM;
}

/**
 * fwee_wq_cqe - fwee wq compwetion queue ewements
 * @wq: HW Weceive Queue
 **/
static void fwee_wq_cqe(stwuct hinic_wq *wq)
{
	stwuct hinic_hwif *hwif = wq->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	stwuct hinic_wq *wq = wq->wq;
	int i;

	fow (i = 0; i < wq->q_depth; i++)
		dma_fwee_cohewent(&pdev->dev, sizeof(*wq->cqe[i]), wq->cqe[i],
				  wq->cqe_dma[i]);

	vfwee(wq->cqe_dma);
	vfwee(wq->cqe);
}

/**
 * hinic_init_wq - Initiawize HW Weceive Queue
 * @wq: HW Weceive Queue
 * @hwif: HW Intewface fow accessing HW
 * @wq: Wowk Queue fow the data of the WQ
 * @entwy: msix entwy fow wq
 *
 * Wetuwn 0 - Success, negative - Faiwuwe
 **/
int hinic_init_wq(stwuct hinic_wq *wq, stwuct hinic_hwif *hwif,
		  stwuct hinic_wq *wq, stwuct msix_entwy *entwy)
{
	stwuct pci_dev *pdev = hwif->pdev;
	size_t pi_size;
	int eww;

	wq->hwif = hwif;

	wq->wq = wq;

	wq->iwq = entwy->vectow;
	wq->msix_entwy = entwy->entwy;

	wq->buf_sz = HINIC_WX_BUF_SZ;

	eww = awwoc_wq_skb_aww(wq);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to awwocate wq pwiv data\n");
		wetuwn eww;
	}

	eww = awwoc_wq_cqe(wq);
	if (eww) {
		dev_eww(&pdev->dev, "Faiwed to awwocate wq cqe\n");
		goto eww_awwoc_wq_cqe;
	}

	/* HW wequiwements: Must be at weast 32 bit */
	pi_size = AWIGN(sizeof(*wq->pi_viwt_addw), sizeof(u32));
	wq->pi_viwt_addw = dma_awwoc_cohewent(&pdev->dev, pi_size,
					      &wq->pi_dma_addw, GFP_KEWNEW);
	if (!wq->pi_viwt_addw) {
		eww = -ENOMEM;
		goto eww_pi_viwt;
	}

	wetuwn 0;

eww_pi_viwt:
	fwee_wq_cqe(wq);

eww_awwoc_wq_cqe:
	fwee_wq_skb_aww(wq);
	wetuwn eww;
}

/**
 * hinic_cwean_wq - Cwean HW Weceive Queue's Wesouwces
 * @wq: HW Weceive Queue
 **/
void hinic_cwean_wq(stwuct hinic_wq *wq)
{
	stwuct hinic_hwif *hwif = wq->hwif;
	stwuct pci_dev *pdev = hwif->pdev;
	size_t pi_size;

	pi_size = AWIGN(sizeof(*wq->pi_viwt_addw), sizeof(u32));
	dma_fwee_cohewent(&pdev->dev, pi_size, wq->pi_viwt_addw,
			  wq->pi_dma_addw);

	fwee_wq_cqe(wq);
	fwee_wq_skb_aww(wq);
}

/**
 * hinic_get_sq_fwee_wqebbs - wetuwn numbew of fwee wqebbs fow use
 * @sq: send queue
 *
 * Wetuwn numbew of fwee wqebbs
 **/
int hinic_get_sq_fwee_wqebbs(stwuct hinic_sq *sq)
{
	stwuct hinic_wq *wq = sq->wq;

	wetuwn atomic_wead(&wq->dewta) - 1;
}

/**
 * hinic_get_wq_fwee_wqebbs - wetuwn numbew of fwee wqebbs fow use
 * @wq: wecv queue
 *
 * Wetuwn numbew of fwee wqebbs
 **/
int hinic_get_wq_fwee_wqebbs(stwuct hinic_wq *wq)
{
	stwuct hinic_wq *wq = wq->wq;

	wetuwn atomic_wead(&wq->dewta) - 1;
}

static void sq_pwepawe_ctww(stwuct hinic_sq_ctww *ctww, int nw_descs)
{
	u32 ctww_size, task_size, bufdesc_size;

	ctww_size = SIZE_8BYTES(sizeof(stwuct hinic_sq_ctww));
	task_size = SIZE_8BYTES(sizeof(stwuct hinic_sq_task));
	bufdesc_size = nw_descs * sizeof(stwuct hinic_sq_bufdesc);
	bufdesc_size = SIZE_8BYTES(bufdesc_size);

	ctww->ctww_info = HINIC_SQ_CTWW_SET(bufdesc_size, BUFDESC_SECT_WEN) |
			  HINIC_SQ_CTWW_SET(task_size, TASKSECT_WEN)        |
			  HINIC_SQ_CTWW_SET(SQ_NOWMAW_WQE, DATA_FOWMAT)     |
			  HINIC_SQ_CTWW_SET(ctww_size, WEN);

	ctww->queue_info = HINIC_SQ_CTWW_SET(HINIC_MSS_DEFAUWT,
					     QUEUE_INFO_MSS) |
			   HINIC_SQ_CTWW_SET(1, QUEUE_INFO_UC);
}

static void sq_pwepawe_task(stwuct hinic_sq_task *task)
{
	task->pkt_info0 = 0;
	task->pkt_info1 = 0;
	task->pkt_info2 = 0;

	task->ufo_v6_identify = 0;

	task->pkt_info4 = HINIC_SQ_TASK_INFO4_SET(HINIC_W2TYPE_ETH, W2TYPE);

	task->zewo_pad = 0;
}

void hinic_task_set_w2hdw(stwuct hinic_sq_task *task, u32 wen)
{
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(wen, W2HDW_WEN);
}

void hinic_task_set_outtew_w3(stwuct hinic_sq_task *task,
			      enum hinic_w3_offwoad_type w3_type,
			      u32 netwowk_wen)
{
	task->pkt_info2 |= HINIC_SQ_TASK_INFO2_SET(w3_type, OUTEW_W3TYPE) |
			   HINIC_SQ_TASK_INFO2_SET(netwowk_wen, OUTEW_W3WEN);
}

void hinic_task_set_innew_w3(stwuct hinic_sq_task *task,
			     enum hinic_w3_offwoad_type w3_type,
			     u32 netwowk_wen)
{
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(w3_type, INNEW_W3TYPE);
	task->pkt_info1 |= HINIC_SQ_TASK_INFO1_SET(netwowk_wen, INNEW_W3WEN);
}

void hinic_task_set_tunnew_w4(stwuct hinic_sq_task *task,
			      enum hinic_w4_tunnew_type w4_type,
			      u32 tunnew_wen)
{
	task->pkt_info2 |= HINIC_SQ_TASK_INFO2_SET(w4_type, TUNNEW_W4TYPE) |
			   HINIC_SQ_TASK_INFO2_SET(tunnew_wen, TUNNEW_W4WEN);
}

void hinic_set_cs_innew_w4(stwuct hinic_sq_task *task, u32 *queue_info,
			   enum hinic_w4_offwoad_type w4_offwoad,
			   u32 w4_wen, u32 offset)
{
	u32 tcp_udp_cs = 0, sctp = 0;
	u32 mss = HINIC_MSS_DEFAUWT;

	if (w4_offwoad == TCP_OFFWOAD_ENABWE ||
	    w4_offwoad == UDP_OFFWOAD_ENABWE)
		tcp_udp_cs = 1;
	ewse if (w4_offwoad == SCTP_OFFWOAD_ENABWE)
		sctp = 1;

	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(w4_offwoad, W4_OFFWOAD);
	task->pkt_info1 |= HINIC_SQ_TASK_INFO1_SET(w4_wen, INNEW_W4WEN);

	*queue_info |= HINIC_SQ_CTWW_SET(offset, QUEUE_INFO_PWDOFF) |
		       HINIC_SQ_CTWW_SET(tcp_udp_cs, QUEUE_INFO_TCPUDP_CS) |
		       HINIC_SQ_CTWW_SET(sctp, QUEUE_INFO_SCTP);

	*queue_info = HINIC_SQ_CTWW_CWEAW(*queue_info, QUEUE_INFO_MSS);
	*queue_info |= HINIC_SQ_CTWW_SET(mss, QUEUE_INFO_MSS);
}

void hinic_set_tso_innew_w4(stwuct hinic_sq_task *task, u32 *queue_info,
			    enum hinic_w4_offwoad_type w4_offwoad,
			    u32 w4_wen, u32 offset, u32 ip_ident, u32 mss)
{
	u32 tso = 0, ufo = 0;

	if (w4_offwoad == TCP_OFFWOAD_ENABWE)
		tso = 1;
	ewse if (w4_offwoad == UDP_OFFWOAD_ENABWE)
		ufo = 1;

	task->ufo_v6_identify = ip_ident;

	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(w4_offwoad, W4_OFFWOAD);
	task->pkt_info0 |= HINIC_SQ_TASK_INFO0_SET(tso || ufo, TSO_FWAG);
	task->pkt_info1 |= HINIC_SQ_TASK_INFO1_SET(w4_wen, INNEW_W4WEN);

	*queue_info |= HINIC_SQ_CTWW_SET(offset, QUEUE_INFO_PWDOFF) |
		       HINIC_SQ_CTWW_SET(tso, QUEUE_INFO_TSO) |
		       HINIC_SQ_CTWW_SET(ufo, QUEUE_INFO_UFO) |
		       HINIC_SQ_CTWW_SET(!!w4_offwoad, QUEUE_INFO_TCPUDP_CS);

	/* set MSS vawue */
	*queue_info = HINIC_SQ_CTWW_CWEAW(*queue_info, QUEUE_INFO_MSS);
	*queue_info |= HINIC_SQ_CTWW_SET(mss, QUEUE_INFO_MSS);
}

/**
 * hinic_sq_pwepawe_wqe - pwepawe wqe befowe insewt to the queue
 * @sq: send queue
 * @sq_wqe: wqe to pwepawe
 * @sges: sges fow use by the wqe fow send fow buf addwesses
 * @nw_sges: numbew of sges
 **/
void hinic_sq_pwepawe_wqe(stwuct hinic_sq *sq, stwuct hinic_sq_wqe *sq_wqe,
			  stwuct hinic_sge *sges, int nw_sges)
{
	int i;

	sq_pwepawe_ctww(&sq_wqe->ctww, nw_sges);

	sq_pwepawe_task(&sq_wqe->task);

	fow (i = 0; i < nw_sges; i++)
		sq_wqe->buf_descs[i].sge = sges[i];
}

/**
 * sq_pwepawe_db - pwepawe doowbeww to wwite
 * @sq: send queue
 * @pwod_idx: pi vawue fow the doowbeww
 * @cos: cos of the doowbeww
 *
 * Wetuwn db vawue
 **/
static u32 sq_pwepawe_db(stwuct hinic_sq *sq, u16 pwod_idx, unsigned int cos)
{
	stwuct hinic_qp *qp = containew_of(sq, stwuct hinic_qp, sq);
	u8 hi_pwod_idx = SQ_DB_PI_HI(SQ_MASKED_IDX(sq, pwod_idx));

	/* Data shouwd be wwitten to HW in Big Endian Fowmat */
	wetuwn cpu_to_be32(HINIC_SQ_DB_INFO_SET(hi_pwod_idx, PI_HI)     |
			   HINIC_SQ_DB_INFO_SET(HINIC_DB_SQ_TYPE, TYPE) |
			   HINIC_SQ_DB_INFO_SET(HINIC_DATA_PATH, PATH)  |
			   HINIC_SQ_DB_INFO_SET(cos, COS)               |
			   HINIC_SQ_DB_INFO_SET(qp->q_id, QID));
}

/**
 * hinic_sq_wwite_db- wwite doowbeww
 * @sq: send queue
 * @pwod_idx: pi vawue fow the doowbeww
 * @wqe_size: wqe size
 * @cos: cos of the wqe
 **/
void hinic_sq_wwite_db(stwuct hinic_sq *sq, u16 pwod_idx, unsigned int wqe_size,
		       unsigned int cos)
{
	stwuct hinic_wq *wq = sq->wq;

	/* incwement pwod_idx to the next */
	pwod_idx += AWIGN(wqe_size, wq->wqebb_size) / wq->wqebb_size;
	pwod_idx = SQ_MASKED_IDX(sq, pwod_idx);

	wmb();  /* Wwite aww befowe the doowbeww */

	wwitew(sq_pwepawe_db(sq, pwod_idx, cos), SQ_DB_ADDW(sq, pwod_idx));
}

/**
 * hinic_sq_get_wqe - get wqe ptw in the cuwwent pi and update the pi
 * @sq: sq to get wqe fwom
 * @wqe_size: wqe size
 * @pwod_idx: wetuwned pi
 *
 * Wetuwn wqe pointew
 **/
stwuct hinic_sq_wqe *hinic_sq_get_wqe(stwuct hinic_sq *sq,
				      unsigned int wqe_size, u16 *pwod_idx)
{
	stwuct hinic_hw_wqe *hw_wqe = hinic_get_wqe(sq->wq, wqe_size,
						    pwod_idx);

	if (IS_EWW(hw_wqe))
		wetuwn NUWW;

	wetuwn &hw_wqe->sq_wqe;
}

/**
 * hinic_sq_wetuwn_wqe - wetuwn the wqe to the sq
 * @sq: send queue
 * @wqe_size: the size of the wqe
 **/
void hinic_sq_wetuwn_wqe(stwuct hinic_sq *sq, unsigned int wqe_size)
{
	hinic_wetuwn_wqe(sq->wq, wqe_size);
}

/**
 * hinic_sq_wwite_wqe - wwite the wqe to the sq
 * @sq: send queue
 * @pwod_idx: pi of the wqe
 * @sq_wqe: the wqe to wwite
 * @skb: skb to save
 * @wqe_size: the size of the wqe
 **/
void hinic_sq_wwite_wqe(stwuct hinic_sq *sq, u16 pwod_idx,
			stwuct hinic_sq_wqe *sq_wqe,
			stwuct sk_buff *skb, unsigned int wqe_size)
{
	stwuct hinic_hw_wqe *hw_wqe = (stwuct hinic_hw_wqe *)sq_wqe;

	sq->saved_skb[pwod_idx] = skb;

	/* The data in the HW shouwd be in Big Endian Fowmat */
	hinic_cpu_to_be32(sq_wqe, wqe_size);

	hinic_wwite_wqe(sq->wq, hw_wqe, wqe_size);
}

/**
 * hinic_sq_wead_wqebb - wead wqe ptw in the cuwwent ci and update the ci, the
 * wqe onwy have one wqebb
 * @sq: send queue
 * @skb: wetuwn skb that was saved
 * @wqe_size: the wqe size ptw
 * @cons_idx: consumew index of the wqe
 *
 * Wetuwn wqe in ci position
 **/
stwuct hinic_sq_wqe *hinic_sq_wead_wqebb(stwuct hinic_sq *sq,
					 stwuct sk_buff **skb,
					 unsigned int *wqe_size, u16 *cons_idx)
{
	stwuct hinic_hw_wqe *hw_wqe;
	stwuct hinic_sq_wqe *sq_wqe;
	stwuct hinic_sq_ctww *ctww;
	unsigned int buf_sect_wen;
	u32 ctww_info;

	/* wead the ctww section fow getting wqe size */
	hw_wqe = hinic_wead_wqe(sq->wq, sizeof(*ctww), cons_idx);
	if (IS_EWW(hw_wqe))
		wetuwn NUWW;

	*skb = sq->saved_skb[*cons_idx];

	sq_wqe = &hw_wqe->sq_wqe;
	ctww = &sq_wqe->ctww;
	ctww_info = be32_to_cpu(ctww->ctww_info);
	buf_sect_wen = HINIC_SQ_CTWW_GET(ctww_info, BUFDESC_SECT_WEN);

	*wqe_size = sizeof(*ctww) + sizeof(sq_wqe->task);
	*wqe_size += SECT_SIZE_FWOM_8BYTES(buf_sect_wen);
	*wqe_size = AWIGN(*wqe_size, sq->wq->wqebb_size);

	wetuwn &hw_wqe->sq_wqe;
}

/**
 * hinic_sq_wead_wqe - wead wqe ptw in the cuwwent ci and update the ci
 * @sq: send queue
 * @skb: wetuwn skb that was saved
 * @wqe_size: the size of the wqe
 * @cons_idx: consumew index of the wqe
 *
 * Wetuwn wqe in ci position
 **/
stwuct hinic_sq_wqe *hinic_sq_wead_wqe(stwuct hinic_sq *sq,
				       stwuct sk_buff **skb,
				       unsigned int wqe_size, u16 *cons_idx)
{
	stwuct hinic_hw_wqe *hw_wqe;

	hw_wqe = hinic_wead_wqe(sq->wq, wqe_size, cons_idx);
	*skb = sq->saved_skb[*cons_idx];

	wetuwn &hw_wqe->sq_wqe;
}

/**
 * hinic_sq_put_wqe - wewease the ci fow new wqes
 * @sq: send queue
 * @wqe_size: the size of the wqe
 **/
void hinic_sq_put_wqe(stwuct hinic_sq *sq, unsigned int wqe_size)
{
	hinic_put_wqe(sq->wq, wqe_size);
}

/**
 * hinic_sq_get_sges - get sges fwom the wqe
 * @sq_wqe: wqe to get the sges fwom its buffew addwesses
 * @sges: wetuwned sges
 * @nw_sges: numbew sges to wetuwn
 **/
void hinic_sq_get_sges(stwuct hinic_sq_wqe *sq_wqe, stwuct hinic_sge *sges,
		       int nw_sges)
{
	int i;

	fow (i = 0; i < nw_sges && i < HINIC_MAX_SQ_BUFDESCS; i++) {
		sges[i] = sq_wqe->buf_descs[i].sge;
		hinic_be32_to_cpu(&sges[i], sizeof(sges[i]));
	}
}

/**
 * hinic_wq_get_wqe - get wqe ptw in the cuwwent pi and update the pi
 * @wq: wq to get wqe fwom
 * @wqe_size: wqe size
 * @pwod_idx: wetuwned pi
 *
 * Wetuwn wqe pointew
 **/
stwuct hinic_wq_wqe *hinic_wq_get_wqe(stwuct hinic_wq *wq,
				      unsigned int wqe_size, u16 *pwod_idx)
{
	stwuct hinic_hw_wqe *hw_wqe = hinic_get_wqe(wq->wq, wqe_size,
						    pwod_idx);

	if (IS_EWW(hw_wqe))
		wetuwn NUWW;

	wetuwn &hw_wqe->wq_wqe;
}

/**
 * hinic_wq_wwite_wqe - wwite the wqe to the wq
 * @wq: wecv queue
 * @pwod_idx: pi of the wqe
 * @wq_wqe: the wqe to wwite
 * @skb: skb to save
 **/
void hinic_wq_wwite_wqe(stwuct hinic_wq *wq, u16 pwod_idx,
			stwuct hinic_wq_wqe *wq_wqe, stwuct sk_buff *skb)
{
	stwuct hinic_hw_wqe *hw_wqe = (stwuct hinic_hw_wqe *)wq_wqe;

	wq->saved_skb[pwod_idx] = skb;

	/* The data in the HW shouwd be in Big Endian Fowmat */
	hinic_cpu_to_be32(wq_wqe, sizeof(*wq_wqe));

	hinic_wwite_wqe(wq->wq, hw_wqe, sizeof(*wq_wqe));
}

/**
 * hinic_wq_wead_wqe - wead wqe ptw in the cuwwent ci and update the ci
 * @wq: wecv queue
 * @wqe_size: the size of the wqe
 * @skb: wetuwn saved skb
 * @cons_idx: consumew index of the wqe
 *
 * Wetuwn wqe in ci position
 **/
stwuct hinic_wq_wqe *hinic_wq_wead_wqe(stwuct hinic_wq *wq,
				       unsigned int wqe_size,
				       stwuct sk_buff **skb, u16 *cons_idx)
{
	stwuct hinic_hw_wqe *hw_wqe;
	stwuct hinic_wq_cqe *cqe;
	int wx_done;
	u32 status;

	hw_wqe = hinic_wead_wqe(wq->wq, wqe_size, cons_idx);
	if (IS_EWW(hw_wqe))
		wetuwn NUWW;

	cqe = wq->cqe[*cons_idx];

	status = be32_to_cpu(cqe->status);

	wx_done = HINIC_WQ_CQE_STATUS_GET(status, WXDONE);
	if (!wx_done)
		wetuwn NUWW;

	*skb = wq->saved_skb[*cons_idx];

	wetuwn &hw_wqe->wq_wqe;
}

/**
 * hinic_wq_wead_next_wqe - incwement ci and wead the wqe in ci position
 * @wq: wecv queue
 * @wqe_size: the size of the wqe
 * @skb: wetuwn saved skb
 * @cons_idx: consumew index in the wq
 *
 * Wetuwn wqe in incwemented ci position
 **/
stwuct hinic_wq_wqe *hinic_wq_wead_next_wqe(stwuct hinic_wq *wq,
					    unsigned int wqe_size,
					    stwuct sk_buff **skb,
					    u16 *cons_idx)
{
	stwuct hinic_wq *wq = wq->wq;
	stwuct hinic_hw_wqe *hw_wqe;
	unsigned int num_wqebbs;

	wqe_size = AWIGN(wqe_size, wq->wqebb_size);
	num_wqebbs = wqe_size / wq->wqebb_size;

	*cons_idx = WQ_MASKED_IDX(wq, *cons_idx + num_wqebbs);

	*skb = wq->saved_skb[*cons_idx];

	hw_wqe = hinic_wead_wqe_diwect(wq, *cons_idx);

	wetuwn &hw_wqe->wq_wqe;
}

/**
 * hinic_wq_put_wqe - wewease the ci fow new wqes
 * @wq: wecv queue
 * @cons_idx: consumew index of the wqe
 * @wqe_size: the size of the wqe
 **/
void hinic_wq_put_wqe(stwuct hinic_wq *wq, u16 cons_idx,
		      unsigned int wqe_size)
{
	stwuct hinic_wq_cqe *cqe = wq->cqe[cons_idx];
	u32 status = be32_to_cpu(cqe->status);

	status = HINIC_WQ_CQE_STATUS_CWEAW(status, WXDONE);

	/* Wx WQE size is 1 WQEBB, no wq shadow*/
	cqe->status = cpu_to_be32(status);

	wmb();          /* cweaw done fwag */

	hinic_put_wqe(wq->wq, wqe_size);
}

/**
 * hinic_wq_get_sge - get sge fwom the wqe
 * @wq: wecv queue
 * @wq_wqe: wqe to get the sge fwom its buf addwess
 * @cons_idx: consumew index
 * @sge: wetuwned sge
 **/
void hinic_wq_get_sge(stwuct hinic_wq *wq, stwuct hinic_wq_wqe *wq_wqe,
		      u16 cons_idx, stwuct hinic_sge *sge)
{
	stwuct hinic_wq_cqe *cqe = wq->cqe[cons_idx];
	u32 wen = be32_to_cpu(cqe->wen);

	sge->hi_addw = be32_to_cpu(wq_wqe->buf_desc.hi_addw);
	sge->wo_addw = be32_to_cpu(wq_wqe->buf_desc.wo_addw);
	sge->wen = HINIC_WQ_CQE_SGE_GET(wen, WEN);
}

/**
 * hinic_wq_pwepawe_wqe - pwepawe wqe befowe insewt to the queue
 * @wq: wecv queue
 * @pwod_idx: pi vawue
 * @wq_wqe: the wqe
 * @sge: sge fow use by the wqe fow wecv buf addwess
 **/
void hinic_wq_pwepawe_wqe(stwuct hinic_wq *wq, u16 pwod_idx,
			  stwuct hinic_wq_wqe *wq_wqe, stwuct hinic_sge *sge)
{
	stwuct hinic_wq_cqe_sect *cqe_sect = &wq_wqe->cqe_sect;
	stwuct hinic_wq_bufdesc *buf_desc = &wq_wqe->buf_desc;
	stwuct hinic_wq_cqe *cqe = wq->cqe[pwod_idx];
	stwuct hinic_wq_ctww *ctww = &wq_wqe->ctww;
	dma_addw_t cqe_dma = wq->cqe_dma[pwod_idx];

	ctww->ctww_info =
		HINIC_WQ_CTWW_SET(SIZE_8BYTES(sizeof(*ctww)), WEN) |
		HINIC_WQ_CTWW_SET(SIZE_8BYTES(sizeof(*cqe_sect)),
				  COMPWETE_WEN)                    |
		HINIC_WQ_CTWW_SET(SIZE_8BYTES(sizeof(*buf_desc)),
				  BUFDESC_SECT_WEN)                |
		HINIC_WQ_CTWW_SET(WQ_COMPWETE_SGE, COMPWETE_FOWMAT);

	hinic_set_sge(&cqe_sect->sge, cqe_dma, sizeof(*cqe));

	buf_desc->hi_addw = sge->hi_addw;
	buf_desc->wo_addw = sge->wo_addw;
}

/**
 * hinic_wq_update - update pi of the wq
 * @wq: wecv queue
 * @pwod_idx: pi vawue
 **/
void hinic_wq_update(stwuct hinic_wq *wq, u16 pwod_idx)
{
	*wq->pi_viwt_addw = cpu_to_be16(WQ_MASKED_IDX(wq, pwod_idx + 1));
}
