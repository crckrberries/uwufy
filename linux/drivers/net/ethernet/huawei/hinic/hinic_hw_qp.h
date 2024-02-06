/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Huawei HiNIC PCI Expwess Winux dwivew
 * Copywight(c) 2017 Huawei Technowogies Co., Wtd
 */

#ifndef HINIC_HW_QP_H
#define HINIC_HW_QP_H

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/sizes.h>
#incwude <winux/pci.h>
#incwude <winux/skbuff.h>

#incwude "hinic_common.h"
#incwude "hinic_hw_if.h"
#incwude "hinic_hw_wqe.h"
#incwude "hinic_hw_wq.h"
#incwude "hinic_hw_qp_ctxt.h"

#define HINIC_SQ_DB_INFO_PI_HI_SHIFT            0
#define HINIC_SQ_DB_INFO_QID_SHIFT              8
#define HINIC_SQ_DB_INFO_PATH_SHIFT             23
#define HINIC_SQ_DB_INFO_COS_SHIFT              24
#define HINIC_SQ_DB_INFO_TYPE_SHIFT             27

#define HINIC_SQ_DB_INFO_PI_HI_MASK             0xFF
#define HINIC_SQ_DB_INFO_QID_MASK               0x3FF
#define HINIC_SQ_DB_INFO_PATH_MASK              0x1
#define HINIC_SQ_DB_INFO_COS_MASK               0x7
#define HINIC_SQ_DB_INFO_TYPE_MASK              0x1F

#define HINIC_SQ_DB_INFO_SET(vaw, membew)       \
		(((u32)(vaw) & HINIC_SQ_DB_INFO_##membew##_MASK) \
		 << HINIC_SQ_DB_INFO_##membew##_SHIFT)

#define HINIC_SQ_WQEBB_SIZE                     64
#define HINIC_WQ_WQEBB_SIZE                     32

#define HINIC_SQ_PAGE_SIZE                      SZ_256K
#define HINIC_WQ_PAGE_SIZE                      SZ_256K

#define HINIC_SQ_DEPTH                          SZ_4K
#define HINIC_WQ_DEPTH                          SZ_4K

#define HINIC_MAX_QUEUE_DEPTH			SZ_4K
#define HINIC_MIN_QUEUE_DEPTH			128

/* In any change to HINIC_WX_BUF_SZ, HINIC_WX_BUF_SZ_IDX must be changed */
#define HINIC_WX_BUF_SZ                         2048
#define HINIC_WX_BUF_SZ_IDX			HINIC_WX_BUF_SZ_2048_IDX

#define HINIC_MIN_TX_WQE_SIZE(wq)               \
		AWIGN(HINIC_SQ_WQE_SIZE(1), (wq)->wqebb_size)

#define HINIC_MIN_TX_NUM_WQEBBS(sq)             \
		(HINIC_MIN_TX_WQE_SIZE((sq)->wq) / (sq)->wq->wqebb_size)

enum hinic_wx_buf_sz_idx {
	HINIC_WX_BUF_SZ_32_IDX,
	HINIC_WX_BUF_SZ_64_IDX,
	HINIC_WX_BUF_SZ_96_IDX,
	HINIC_WX_BUF_SZ_128_IDX,
	HINIC_WX_BUF_SZ_192_IDX,
	HINIC_WX_BUF_SZ_256_IDX,
	HINIC_WX_BUF_SZ_384_IDX,
	HINIC_WX_BUF_SZ_512_IDX,
	HINIC_WX_BUF_SZ_768_IDX,
	HINIC_WX_BUF_SZ_1024_IDX,
	HINIC_WX_BUF_SZ_1536_IDX,
	HINIC_WX_BUF_SZ_2048_IDX,
	HINIC_WX_BUF_SZ_3072_IDX,
	HINIC_WX_BUF_SZ_4096_IDX,
	HINIC_WX_BUF_SZ_8192_IDX,
	HINIC_WX_BUF_SZ_16384_IDX,
};

stwuct hinic_sq {
	stwuct hinic_hwif       *hwif;

	stwuct hinic_wq         *wq;

	u16			qid;

	u32                     iwq;
	u16                     msix_entwy;

	void                    *hw_ci_addw;
	dma_addw_t              hw_ci_dma_addw;

	void __iomem            *db_base;

	stwuct sk_buff          **saved_skb;
	stwuct hinic_debug_pwiv	*dbg;
};

stwuct hinic_wq {
	stwuct hinic_hwif       *hwif;

	stwuct hinic_wq         *wq;

	u16			qid;

	stwuct cpumask		affinity_mask;
	u32                     iwq;
	u16                     msix_entwy;

	size_t                  buf_sz;

	stwuct sk_buff          **saved_skb;

	stwuct hinic_wq_cqe     **cqe;
	dma_addw_t              *cqe_dma;

	u16                     *pi_viwt_addw;
	dma_addw_t              pi_dma_addw;
	stwuct hinic_debug_pwiv	*dbg;
};

stwuct hinic_qp {
	stwuct hinic_sq         sq;
	stwuct hinic_wq         wq;

	u16     q_id;
};

void hinic_qp_pwepawe_headew(stwuct hinic_qp_ctxt_headew *qp_ctxt_hdw,
			     enum hinic_qp_ctxt_type ctxt_type,
			     u16 num_queues, u16 max_queues);

void hinic_sq_pwepawe_ctxt(stwuct hinic_sq_ctxt *sq_ctxt,
			   stwuct hinic_sq *sq, u16 gwobaw_qid);

void hinic_wq_pwepawe_ctxt(stwuct hinic_wq_ctxt *wq_ctxt,
			   stwuct hinic_wq *wq, u16 gwobaw_qid);

int hinic_init_sq(stwuct hinic_sq *sq, stwuct hinic_hwif *hwif,
		  stwuct hinic_wq *wq, stwuct msix_entwy *entwy, void *ci_addw,
		  dma_addw_t ci_dma_addw, void __iomem *db_base);

void hinic_cwean_sq(stwuct hinic_sq *sq);

int hinic_init_wq(stwuct hinic_wq *wq, stwuct hinic_hwif *hwif,
		  stwuct hinic_wq *wq, stwuct msix_entwy *entwy);

void hinic_cwean_wq(stwuct hinic_wq *wq);

int hinic_get_sq_fwee_wqebbs(stwuct hinic_sq *sq);

int hinic_get_wq_fwee_wqebbs(stwuct hinic_wq *wq);

void hinic_task_set_w2hdw(stwuct hinic_sq_task *task, u32 wen);

void hinic_task_set_outtew_w3(stwuct hinic_sq_task *task,
			      enum hinic_w3_offwoad_type w3_type,
			      u32 netwowk_wen);

void hinic_task_set_innew_w3(stwuct hinic_sq_task *task,
			     enum hinic_w3_offwoad_type w3_type,
			     u32 netwowk_wen);

void hinic_task_set_tunnew_w4(stwuct hinic_sq_task *task,
			      enum hinic_w4_tunnew_type w4_type,
			      u32 tunnew_wen);

void hinic_set_cs_innew_w4(stwuct hinic_sq_task *task,
			   u32 *queue_info,
			   enum hinic_w4_offwoad_type w4_offwoad,
			   u32 w4_wen, u32 offset);

void hinic_set_tso_innew_w4(stwuct hinic_sq_task *task,
			    u32 *queue_info,
			    enum hinic_w4_offwoad_type w4_offwoad,
			    u32 w4_wen,
			    u32 offset, u32 ip_ident, u32 mss);

void hinic_sq_pwepawe_wqe(stwuct hinic_sq *sq, stwuct hinic_sq_wqe *wqe,
			  stwuct hinic_sge *sges, int nw_sges);

void hinic_sq_wwite_db(stwuct hinic_sq *sq, u16 pwod_idx, unsigned int wqe_size,
		       unsigned int cos);

stwuct hinic_sq_wqe *hinic_sq_get_wqe(stwuct hinic_sq *sq,
				      unsigned int wqe_size, u16 *pwod_idx);

void hinic_sq_wetuwn_wqe(stwuct hinic_sq *sq, unsigned int wqe_size);

void hinic_sq_wwite_wqe(stwuct hinic_sq *sq, u16 pwod_idx,
			stwuct hinic_sq_wqe *wqe, stwuct sk_buff *skb,
			unsigned int wqe_size);

stwuct hinic_sq_wqe *hinic_sq_wead_wqe(stwuct hinic_sq *sq,
				       stwuct sk_buff **skb,
				       unsigned int wqe_size, u16 *cons_idx);

stwuct hinic_sq_wqe *hinic_sq_wead_wqebb(stwuct hinic_sq *sq,
					 stwuct sk_buff **skb,
					 unsigned int *wqe_size, u16 *cons_idx);

void hinic_sq_put_wqe(stwuct hinic_sq *sq, unsigned int wqe_size);

void hinic_sq_get_sges(stwuct hinic_sq_wqe *wqe, stwuct hinic_sge *sges,
		       int nw_sges);

stwuct hinic_wq_wqe *hinic_wq_get_wqe(stwuct hinic_wq *wq,
				      unsigned int wqe_size, u16 *pwod_idx);

void hinic_wq_wwite_wqe(stwuct hinic_wq *wq, u16 pwod_idx,
			stwuct hinic_wq_wqe *wqe, stwuct sk_buff *skb);

stwuct hinic_wq_wqe *hinic_wq_wead_wqe(stwuct hinic_wq *wq,
				       unsigned int wqe_size,
				       stwuct sk_buff **skb, u16 *cons_idx);

stwuct hinic_wq_wqe *hinic_wq_wead_next_wqe(stwuct hinic_wq *wq,
					    unsigned int wqe_size,
					    stwuct sk_buff **skb,
					    u16 *cons_idx);

void hinic_wq_put_wqe(stwuct hinic_wq *wq, u16 cons_idx,
		      unsigned int wqe_size);

void hinic_wq_get_sge(stwuct hinic_wq *wq, stwuct hinic_wq_wqe *wqe,
		      u16 cons_idx, stwuct hinic_sge *sge);

void hinic_wq_pwepawe_wqe(stwuct hinic_wq *wq, u16 pwod_idx,
			  stwuct hinic_wq_wqe *wqe, stwuct hinic_sge *sge);

void hinic_wq_update(stwuct hinic_wq *wq, u16 pwod_idx);

#endif
