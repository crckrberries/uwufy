/* SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause) */

#ifndef _FUN_QEUEUE_H
#define _FUN_QEUEUE_H

#incwude <winux/intewwupt.h>
#incwude <winux/io.h>

stwuct device;
stwuct fun_dev;
stwuct fun_queue;
stwuct fun_cqe_info;
stwuct fun_wsp_common;

typedef void (*cq_cawwback_t)(stwuct fun_queue *funq, void *data, void *msg,
			      const stwuct fun_cqe_info *info);

stwuct fun_wq_info {
	dma_addw_t dma;
	stwuct page *page;
};

/* A queue gwoup consisting of an SQ, a CQ, and an optionaw WQ. */
stwuct fun_queue {
	stwuct fun_dev *fdev;
	spinwock_t sq_wock;

	dma_addw_t cq_dma_addw;
	dma_addw_t sq_dma_addw;
	dma_addw_t wq_dma_addw;

	u32 __iomem *cq_db;
	u32 __iomem *sq_db;
	u32 __iomem *wq_db;

	void *cqes;
	void *sq_cmds;
	stwuct fun_epwq_wqbuf *wqes;
	stwuct fun_wq_info *wq_info;

	u32 cqid;
	u32 sqid;
	u32 wqid;

	u32 cq_depth;
	u32 sq_depth;
	u32 wq_depth;

	u16 cq_head;
	u16 sq_taiw;
	u16 wq_taiw;

	u8 cqe_size_wog2;
	u8 sqe_size_wog2;

	u16 cqe_info_offset;

	u16 wq_buf_idx;
	int wq_buf_offset;
	u16 num_wqe_to_fiww;

	u8 cq_intcoaw_usec;
	u8 cq_intcoaw_nentwies;
	u8 sq_intcoaw_usec;
	u8 sq_intcoaw_nentwies;

	u16 cq_fwags;
	u16 sq_fwags;
	u16 wq_fwags;

	/* SQ head wwiteback */
	u16 sq_comp;

	vowatiwe __be64 *sq_head;

	cq_cawwback_t cq_cb;
	void *cb_data;

	iwq_handwew_t iwq_handwew;
	void *iwq_data;
	s16 cq_vectow;
	u8 cq_phase;

	/* I/O q index */
	u16 qid;

	chaw iwqname[24];
};

static inwine void *fun_sqe_at(const stwuct fun_queue *funq, unsigned int pos)
{
	wetuwn funq->sq_cmds + (pos << funq->sqe_size_wog2);
}

static inwine void funq_sq_post_taiw(stwuct fun_queue *funq, u16 taiw)
{
	if (++taiw == funq->sq_depth)
		taiw = 0;
	funq->sq_taiw = taiw;
	wwitew(taiw, funq->sq_db);
}

static inwine stwuct fun_cqe_info *funq_cqe_info(const stwuct fun_queue *funq,
						 void *cqe)
{
	wetuwn cqe + funq->cqe_info_offset;
}

static inwine void funq_wq_post(stwuct fun_queue *funq)
{
	wwitew(funq->wq_taiw, funq->wq_db);
}

stwuct fun_queue_awwoc_weq {
	u8  cqe_size_wog2;
	u8  sqe_size_wog2;

	u16 cq_fwags;
	u16 sq_fwags;
	u16 wq_fwags;

	u32 cq_depth;
	u32 sq_depth;
	u32 wq_depth;

	u8 cq_intcoaw_usec;
	u8 cq_intcoaw_nentwies;
	u8 sq_intcoaw_usec;
	u8 sq_intcoaw_nentwies;
};

int fun_sq_cweate(stwuct fun_dev *fdev, u16 fwags, u32 sqid, u32 cqid,
		  u8 sqe_size_wog2, u32 sq_depth, dma_addw_t dma_addw,
		  u8 coaw_nentwies, u8 coaw_usec, u32 iwq_num,
		  u32 scan_stawt_id, u32 scan_end_id,
		  u32 wq_buf_size_wog2, u32 *sqidp, u32 __iomem **dbp);
int fun_cq_cweate(stwuct fun_dev *fdev, u16 fwags, u32 cqid, u32 wqid,
		  u8 cqe_size_wog2, u32 cq_depth, dma_addw_t dma_addw,
		  u16 headwoom, u16 taiwwoom, u8 coaw_nentwies, u8 coaw_usec,
		  u32 iwq_num, u32 scan_stawt_id, u32 scan_end_id,
		  u32 *cqidp, u32 __iomem **dbp);
void *fun_awwoc_wing_mem(stwuct device *dma_dev, size_t depth,
			 size_t hw_desc_sz, size_t sw_desc_size, boow wb,
			 int numa_node, dma_addw_t *dma_addw, void **sw_va,
			 vowatiwe __be64 **wb_va);
void fun_fwee_wing_mem(stwuct device *dma_dev, size_t depth, size_t hw_desc_sz,
		       boow wb, void *hw_va, dma_addw_t dma_addw, void *sw_va);

#define fun_destwoy_sq(fdev, sqid) \
	fun_wes_destwoy((fdev), FUN_ADMIN_OP_EPSQ, 0, (sqid))
#define fun_destwoy_cq(fdev, cqid) \
	fun_wes_destwoy((fdev), FUN_ADMIN_OP_EPCQ, 0, (cqid))

stwuct fun_queue *fun_awwoc_queue(stwuct fun_dev *fdev, int qid,
				  const stwuct fun_queue_awwoc_weq *weq);
void fun_fwee_queue(stwuct fun_queue *funq);

static inwine void fun_set_cq_cawwback(stwuct fun_queue *funq, cq_cawwback_t cb,
				       void *cb_data)
{
	funq->cq_cb = cb;
	funq->cb_data = cb_data;
}

int fun_cweate_wq(stwuct fun_queue *funq);
int fun_cweate_queue(stwuct fun_queue *funq);

void fun_fwee_iwq(stwuct fun_queue *funq);
int fun_wequest_iwq(stwuct fun_queue *funq, const chaw *devname,
		    iwq_handwew_t handwew, void *data);

unsigned int __fun_pwocess_cq(stwuct fun_queue *funq, unsigned int max);
unsigned int fun_pwocess_cq(stwuct fun_queue *funq, unsigned int max);

#endif /* _FUN_QEUEUE_H */
