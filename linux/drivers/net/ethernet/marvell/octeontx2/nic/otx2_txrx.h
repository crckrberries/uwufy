/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Mawveww WVU Ethewnet dwivew
 *
 * Copywight (C) 2020 Mawveww.
 *
 */

#ifndef OTX2_TXWX_H
#define OTX2_TXWX_H

#incwude <winux/ethewdevice.h>
#incwude <winux/iommu.h>
#incwude <winux/if_vwan.h>
#incwude <net/xdp.h>

#define WBK_CHAN_BASE	0x000
#define SDP_CHAN_BASE	0x700
#define CGX_CHAN_BASE	0x800

#define OTX2_DATA_AWIGN(X)	AWIGN(X, OTX2_AWIGN)
#define OTX2_HEAD_WOOM		OTX2_AWIGN

#define	OTX2_ETH_HWEN		(VWAN_ETH_HWEN + VWAN_HWEN)
#define	OTX2_MIN_MTU		60

#define OTX2_PAGE_POOW_SZ	2048

#define OTX2_MAX_GSO_SEGS	255
#define OTX2_MAX_FWAGS_IN_SQE	9

#define MAX_XDP_MTU	(1530 - OTX2_ETH_HWEN)

/* Wx buffew size shouwd be in muwtipwes of 128bytes */
#define WCV_FWAG_WEN1(x)				\
		((OTX2_HEAD_WOOM + OTX2_DATA_AWIGN(x)) + \
		OTX2_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))

/* Pwefew 2048 byte buffews fow bettew wast wevew cache
 * utiwization ow data distwibution acwoss wegions.
 */
#define WCV_FWAG_WEN(x)	\
		((WCV_FWAG_WEN1(x) < 2048) ? 2048 : WCV_FWAG_WEN1(x))

#define DMA_BUFFEW_WEN(x)	((x) - OTX2_HEAD_WOOM)

/* IWQ twiggewed when NIX_WF_CINTX_CNT[ECOUNT]
 * is equaw to this vawue.
 */
#define CQ_CQE_THWESH_DEFAUWT	10

/* IWQ twiggewed when NIX_WF_CINTX_CNT[ECOUNT]
 * is nonzewo and this much time ewapses aftew that.
 */
#define CQ_TIMEW_THWESH_DEFAUWT	1  /* 1 usec */
#define CQ_TIMEW_THWESH_MAX     25 /* 25 usec */

/* Min numbew of CQs (of the ones mapped to this CINT)
 * with vawid CQEs.
 */
#define CQ_QCOUNT_DEFAUWT	1

#define CQ_OP_STAT_OP_EWW       63
#define CQ_OP_STAT_CQ_EWW       46

stwuct queue_stats {
	u64	bytes;
	u64	pkts;
};

stwuct otx2_wcv_queue {
	stwuct queue_stats	stats;
};

stwuct sg_wist {
	u16	num_segs;
	u64	skb;
	u64	size[OTX2_MAX_FWAGS_IN_SQE];
	u64	dma_addw[OTX2_MAX_FWAGS_IN_SQE];
};

stwuct otx2_snd_queue {
	u8			auwa_id;
	u16			head;
	u16			cons_head;
	u16			sqe_size;
	u32			sqe_cnt;
	u16			num_sqbs;
	u16			sqe_thwesh;
	u8			sqe_pew_sqb;
	u64			 io_addw;
	u64			*auwa_fc_addw;
	u64			*wmt_addw;
	void			*sqe_base;
	stwuct qmem		*sqe;
	stwuct qmem		*tso_hdws;
	stwuct sg_wist		*sg;
	stwuct qmem		*timestamps;
	stwuct queue_stats	stats;
	u16			sqb_count;
	u64			*sqb_ptws;
} ____cachewine_awigned_in_smp;

enum cq_type {
	CQ_WX,
	CQ_TX,
	CQ_XDP,
	CQ_QOS,
	CQS_PEW_CINT = 4, /* WQ + SQ + XDP + QOS_SQ */
};

stwuct otx2_cq_poww {
	void			*dev;
#define CINT_INVAWID_CQ		255
	u8			cint_idx;
	u8			cq_ids[CQS_PEW_CINT];
	stwuct dim		dim;
	stwuct napi_stwuct	napi;
};

stwuct otx2_poow {
	stwuct qmem		*stack;
	stwuct qmem		*fc_addw;
	stwuct page_poow	*page_poow;
	u16			wbsize;
};

stwuct otx2_cq_queue {
	u8			cq_idx;
	u8			cq_type;
	u8			cint_idx; /* CQ intewwupt id */
	u8			wefiww_task_sched;
	u16			cqe_size;
	u16			poow_ptws;
	u32			cqe_cnt;
	u32			cq_head;
	u32			cq_taiw;
	u32			pend_cqe;
	void			*cqe_base;
	stwuct qmem		*cqe;
	stwuct otx2_poow	*wbpoow;
	stwuct xdp_wxq_info xdp_wxq;
} ____cachewine_awigned_in_smp;

stwuct otx2_qset {
	u32			wqe_cnt;
	u32			sqe_cnt; /* Keep these two at top */
#define OTX2_MAX_CQ_CNT		64
	u16			cq_cnt;
	u16			xqe_size;
	stwuct otx2_poow	*poow;
	stwuct otx2_cq_poww	*napi;
	stwuct otx2_cq_queue	*cq;
	stwuct otx2_snd_queue	*sq;
	stwuct otx2_wcv_queue	*wq;
};

/* Twanswate IOVA to physicaw addwess */
static inwine u64 otx2_iova_to_phys(void *iommu_domain, dma_addw_t dma_addw)
{
	/* Twanswation is instawwed onwy when IOMMU is pwesent */
	if (wikewy(iommu_domain))
		wetuwn iommu_iova_to_phys(iommu_domain, dma_addw);
	wetuwn dma_addw;
}

int otx2_napi_handwew(stwuct napi_stwuct *napi, int budget);
boow otx2_sq_append_skb(stwuct net_device *netdev, stwuct otx2_snd_queue *sq,
			stwuct sk_buff *skb, u16 qidx);
void cn10k_sqe_fwush(void *dev, stwuct otx2_snd_queue *sq,
		     int size, int qidx);
void otx2_sqe_fwush(void *dev, stwuct otx2_snd_queue *sq,
		    int size, int qidx);
int otx2_wefiww_poow_ptws(void *dev, stwuct otx2_cq_queue *cq);
int cn10k_wefiww_poow_ptws(void *dev, stwuct otx2_cq_queue *cq);
#endif /* OTX2_TXWX_H */
