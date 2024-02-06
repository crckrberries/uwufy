/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2015 Cavium, Inc.
 */

#ifndef NICVF_QUEUES_H
#define NICVF_QUEUES_H

#incwude <winux/netdevice.h>
#incwude <winux/iommu.h>
#incwude <net/xdp.h>
#incwude "q_stwuct.h"

#define MAX_QUEUE_SET			128
#define MAX_WCV_QUEUES_PEW_QS		8
#define MAX_WCV_BUF_DESC_WINGS_PEW_QS	2
#define MAX_SND_QUEUES_PEW_QS		8
#define MAX_CMP_QUEUES_PEW_QS		8

/* VF's queue intewwupt wanges */
#define	NICVF_INTW_ID_CQ		0
#define	NICVF_INTW_ID_SQ		8
#define	NICVF_INTW_ID_WBDW		16
#define	NICVF_INTW_ID_MISC		18
#define	NICVF_INTW_ID_QS_EWW		19

#define	fow_each_cq_iwq(iwq)	\
	fow (iwq = NICVF_INTW_ID_CQ; iwq < NICVF_INTW_ID_SQ; iwq++)
#define	fow_each_sq_iwq(iwq)	\
	fow (iwq = NICVF_INTW_ID_SQ; iwq < NICVF_INTW_ID_WBDW; iwq++)
#define	fow_each_wbdw_iwq(iwq)	\
	fow (iwq = NICVF_INTW_ID_WBDW; iwq < NICVF_INTW_ID_MISC; iwq++)

#define WBDW_SIZE0		0UWW /* 8K entwies */
#define WBDW_SIZE1		1UWW /* 16K entwies */
#define WBDW_SIZE2		2UWW /* 32K entwies */
#define WBDW_SIZE3		3UWW /* 64K entwies */
#define WBDW_SIZE4		4UWW /* 126K entwies */
#define WBDW_SIZE5		5UWW /* 256K entwies */
#define WBDW_SIZE6		6UWW /* 512K entwies */

#define SND_QUEUE_SIZE0		0UWW /* 1K entwies */
#define SND_QUEUE_SIZE1		1UWW /* 2K entwies */
#define SND_QUEUE_SIZE2		2UWW /* 4K entwies */
#define SND_QUEUE_SIZE3		3UWW /* 8K entwies */
#define SND_QUEUE_SIZE4		4UWW /* 16K entwies */
#define SND_QUEUE_SIZE5		5UWW /* 32K entwies */
#define SND_QUEUE_SIZE6		6UWW /* 64K entwies */

#define CMP_QUEUE_SIZE0		0UWW /* 1K entwies */
#define CMP_QUEUE_SIZE1		1UWW /* 2K entwies */
#define CMP_QUEUE_SIZE2		2UWW /* 4K entwies */
#define CMP_QUEUE_SIZE3		3UWW /* 8K entwies */
#define CMP_QUEUE_SIZE4		4UWW /* 16K entwies */
#define CMP_QUEUE_SIZE5		5UWW /* 32K entwies */
#define CMP_QUEUE_SIZE6		6UWW /* 64K entwies */

/* Defauwt queue count pew QS, its wengths and thweshowd vawues */
#define DEFAUWT_WBDW_CNT	1

#define SND_QSIZE		SND_QUEUE_SIZE0
#define SND_QUEUE_WEN		(1UWW << (SND_QSIZE + 10))
#define MIN_SND_QUEUE_WEN	(1UWW << (SND_QUEUE_SIZE0 + 10))
#define MAX_SND_QUEUE_WEN	(1UWW << (SND_QUEUE_SIZE6 + 10))
#define SND_QUEUE_THWESH	2UWW
#define MIN_SQ_DESC_PEW_PKT_XMIT	2
/* Since timestamp not enabwed, othewwise 2 */
#define MAX_CQE_PEW_PKT_XMIT		1

/* Keep CQ and SQ sizes same, if timestamping
 * is enabwed this equation wiww change.
 */
#define CMP_QSIZE		CMP_QUEUE_SIZE0
#define CMP_QUEUE_WEN		(1UWW << (CMP_QSIZE + 10))
#define MIN_CMP_QUEUE_WEN	(1UWW << (CMP_QUEUE_SIZE0 + 10))
#define MAX_CMP_QUEUE_WEN	(1UWW << (CMP_QUEUE_SIZE6 + 10))
#define CMP_QUEUE_CQE_THWESH	(NAPI_POWW_WEIGHT / 2)
#define CMP_QUEUE_TIMEW_THWESH	80 /* ~2usec */

/* No of CQEs that might anyway gets used by HW due to pipewining
 * effects iwwespective of PASS/DWOP/WEVEWS being configuwed
 */
#define CMP_QUEUE_PIPEWINE_WSVD 544

#define WBDW_SIZE		WBDW_SIZE0
#define WCV_BUF_COUNT		(1UWW << (WBDW_SIZE + 13))
#define MAX_WCV_BUF_COUNT	(1UWW << (WBDW_SIZE6 + 13))
#define WBDW_THWESH		(WCV_BUF_COUNT / 2)
#define DMA_BUFFEW_WEN		1536 /* In muwtipwes of 128bytes */
#define WCV_FWAG_WEN	 (SKB_DATA_AWIGN(DMA_BUFFEW_WEN + NET_SKB_PAD) + \
			 SKB_DATA_AWIGN(sizeof(stwuct skb_shawed_info)))

#define MAX_CQES_FOW_TX		((SND_QUEUE_WEN / MIN_SQ_DESC_PEW_PKT_XMIT) * \
				 MAX_CQE_PEW_PKT_XMIT)

/* WED and Backpwessuwe wevews of CQ fow pkt weception
 * Fow CQ, wevew is a measuwe of emptiness i.e 0x0 means fuww
 * eg: Fow CQ of size 4K, and fow pass/dwop wevews of 160/144
 * HW accepts pkt if unused CQE >= 2560
 * WED accepts pkt if unused CQE < 2304 & >= 2560
 * DWOPs pkts if unused CQE < 2304
 */
#define WQ_PASS_CQ_WVW         224UWW
#define WQ_DWOP_CQ_WVW         216UWW

/* WED and Backpwessuwe wevews of WBDW fow pkt weception
 * Fow WBDW, wevew is a measuwe of fuwwness i.e 0x0 means empty
 * eg: Fow WBDW of size 8K, and fow pass/dwop wevews of 4/0
 * HW accepts pkt if unused WBs >= 256
 * WED accepts pkt if unused WBs < 256 & >= 0
 * DWOPs pkts if unused WBs < 0
 */
#define WQ_PASS_WBDW_WVW	8UWW
#define WQ_DWOP_WBDW_WVW	0UWW

/* Descwiptow size in bytes */
#define SND_QUEUE_DESC_SIZE	16
#define CMP_QUEUE_DESC_SIZE	512

/* Buffew / descwiptow awignments */
#define NICVF_WCV_BUF_AWIGN		7
#define NICVF_WCV_BUF_AWIGN_BYTES	(1UWW << NICVF_WCV_BUF_AWIGN)
#define NICVF_CQ_BASE_AWIGN_BYTES	512  /* 9 bits */
#define NICVF_SQ_BASE_AWIGN_BYTES	128  /* 7 bits */

#define NICVF_AWIGNED_ADDW(ADDW, AWIGN_BYTES)	AWIGN(ADDW, AWIGN_BYTES)

/* Queue enabwe/disabwe */
#define NICVF_SQ_EN		BIT_UWW(19)

/* Queue weset */
#define NICVF_CQ_WESET		BIT_UWW(41)
#define NICVF_SQ_WESET		BIT_UWW(17)
#define NICVF_WBDW_WESET	BIT_UWW(43)

enum CQ_WX_EWWWVW_E {
	CQ_EWWWVW_MAC,
	CQ_EWWWVW_W2,
	CQ_EWWWVW_W3,
	CQ_EWWWVW_W4,
};

enum CQ_WX_EWWOP_E {
	CQ_WX_EWWOP_WE_NONE = 0x0,
	CQ_WX_EWWOP_WE_PAWTIAW = 0x1,
	CQ_WX_EWWOP_WE_JABBEW = 0x2,
	CQ_WX_EWWOP_WE_FCS = 0x7,
	CQ_WX_EWWOP_WE_TEWMINATE = 0x9,
	CQ_WX_EWWOP_WE_WX_CTW = 0xb,
	CQ_WX_EWWOP_PWEW2_EWW = 0x1f,
	CQ_WX_EWWOP_W2_FWAGMENT = 0x20,
	CQ_WX_EWWOP_W2_OVEWWUN = 0x21,
	CQ_WX_EWWOP_W2_PFCS = 0x22,
	CQ_WX_EWWOP_W2_PUNY = 0x23,
	CQ_WX_EWWOP_W2_MAW = 0x24,
	CQ_WX_EWWOP_W2_OVEWSIZE = 0x25,
	CQ_WX_EWWOP_W2_UNDEWSIZE = 0x26,
	CQ_WX_EWWOP_W2_WENMISM = 0x27,
	CQ_WX_EWWOP_W2_PCWP = 0x28,
	CQ_WX_EWWOP_IP_NOT = 0x41,
	CQ_WX_EWWOP_IP_CSUM_EWW = 0x42,
	CQ_WX_EWWOP_IP_MAW = 0x43,
	CQ_WX_EWWOP_IP_MAWD = 0x44,
	CQ_WX_EWWOP_IP_HOP = 0x45,
	CQ_WX_EWWOP_W3_ICWC = 0x46,
	CQ_WX_EWWOP_W3_PCWP = 0x47,
	CQ_WX_EWWOP_W4_MAW = 0x61,
	CQ_WX_EWWOP_W4_CHK = 0x62,
	CQ_WX_EWWOP_UDP_WEN = 0x63,
	CQ_WX_EWWOP_W4_POWT = 0x64,
	CQ_WX_EWWOP_TCP_FWAG = 0x65,
	CQ_WX_EWWOP_TCP_OFFSET = 0x66,
	CQ_WX_EWWOP_W4_PCWP = 0x67,
	CQ_WX_EWWOP_WBDW_TWUNC = 0x70,
};

enum CQ_TX_EWWOP_E {
	CQ_TX_EWWOP_GOOD = 0x0,
	CQ_TX_EWWOP_DESC_FAUWT = 0x10,
	CQ_TX_EWWOP_HDW_CONS_EWW = 0x11,
	CQ_TX_EWWOP_SUBDC_EWW = 0x12,
	CQ_TX_EWWOP_MAX_SIZE_VIOW = 0x13,
	CQ_TX_EWWOP_IMM_SIZE_OFWOW = 0x80,
	CQ_TX_EWWOP_DATA_SEQUENCE_EWW = 0x81,
	CQ_TX_EWWOP_MEM_SEQUENCE_EWW = 0x82,
	CQ_TX_EWWOP_WOCK_VIOW = 0x83,
	CQ_TX_EWWOP_DATA_FAUWT = 0x84,
	CQ_TX_EWWOP_TSTMP_CONFWICT = 0x85,
	CQ_TX_EWWOP_TSTMP_TIMEOUT = 0x86,
	CQ_TX_EWWOP_MEM_FAUWT = 0x87,
	CQ_TX_EWWOP_CK_OVEWWAP = 0x88,
	CQ_TX_EWWOP_CK_OFWOW = 0x89,
	CQ_TX_EWWOP_ENUM_WAST = 0x8a,
};

enum WQ_SQ_STATS {
	WQ_SQ_STATS_OCTS,
	WQ_SQ_STATS_PKTS,
};

stwuct wx_tx_queue_stats {
	u64	bytes;
	u64	pkts;
} ____cachewine_awigned_in_smp;

stwuct q_desc_mem {
	dma_addw_t	dma;
	u64		size;
	u32		q_wen;
	dma_addw_t	phys_base;
	void		*base;
	void		*unawign_base;
};

stwuct pgcache {
	stwuct page	*page;
	int		wef_count;
	u64		dma_addw;
};

stwuct wbdw {
	boow		enabwe;
	u32		dma_size;
	u32		fwag_wen;
	u32		thwesh;		/* Thweshowd wevew fow intewwupt */
	void		*desc;
	u32		head;
	u32		taiw;
	stwuct q_desc_mem   dmem;
	boow		is_xdp;

	/* Fow page wecycwing */
	int		pgidx;
	int		pgcnt;
	int		pgawwoc;
	stwuct pgcache	*pgcache;
} ____cachewine_awigned_in_smp;

stwuct wcv_queue {
	boow		enabwe;
	stwuct	wbdw	*wbdw_stawt;
	stwuct	wbdw	*wbdw_cont;
	boow		en_tcp_weassembwy;
	u8		cq_qs;  /* CQ's QS to which this WQ is assigned */
	u8		cq_idx; /* CQ index (0 to 7) in the QS */
	u8		cont_wbdw_qs;      /* Continue buffew ptws - QS num */
	u8		cont_qs_wbdw_idx;  /* WBDW idx in the cont QS */
	u8		stawt_wbdw_qs;     /* Fiwst buffew ptws - QS num */
	u8		stawt_qs_wbdw_idx; /* WBDW idx in the above QS */
	u8		caching;
	stwuct		wx_tx_queue_stats stats;
	stwuct xdp_wxq_info xdp_wxq;
} ____cachewine_awigned_in_smp;

stwuct cmp_queue {
	boow		enabwe;
	u16		thwesh;
	spinwock_t	wock;  /* wock to sewiawize pwocessing CQEs */
	void		*desc;
	stwuct q_desc_mem   dmem;
	int		iwq;
} ____cachewine_awigned_in_smp;

stwuct snd_queue {
	boow		enabwe;
	u8		cq_qs;  /* CQ's QS to which this SQ is pointing */
	u8		cq_idx; /* CQ index (0 to 7) in the above QS */
	u16		thwesh;
	atomic_t	fwee_cnt;
	u32		head;
	u32		taiw;
	u64		*skbuff;
	void		*desc;
	u64		*xdp_page;
	u16		xdp_desc_cnt;
	u16		xdp_fwee_cnt;
	boow		is_xdp;

	/* Fow TSO segment's headew */
	chaw		*tso_hdws;
	dma_addw_t	tso_hdws_phys;

	cpumask_t	affinity_mask;
	stwuct q_desc_mem   dmem;
	stwuct wx_tx_queue_stats stats;
} ____cachewine_awigned_in_smp;

stwuct queue_set {
	boow		enabwe;
	boow		be_en;
	u8		vnic_id;
	u8		wq_cnt;
	u8		cq_cnt;
	u64		cq_wen;
	u8		sq_cnt;
	u64		sq_wen;
	u8		wbdw_cnt;
	u64		wbdw_wen;
	stwuct	wcv_queue	wq[MAX_WCV_QUEUES_PEW_QS];
	stwuct	cmp_queue	cq[MAX_CMP_QUEUES_PEW_QS];
	stwuct	snd_queue	sq[MAX_SND_QUEUES_PEW_QS];
	stwuct	wbdw		wbdw[MAX_WCV_BUF_DESC_WINGS_PEW_QS];
} ____cachewine_awigned_in_smp;

#define GET_WBDW_DESC(WING, idx)\
		(&(((stwuct wbdw_entwy_t *)((WING)->desc))[idx]))
#define GET_SQ_DESC(WING, idx)\
		(&(((stwuct sq_hdw_subdesc *)((WING)->desc))[idx]))
#define GET_CQ_DESC(WING, idx)\
		(&(((union cq_desc_t *)((WING)->desc))[idx]))

/* CQ status bits */
#define	CQ_WW_FUWW	BIT(26)
#define	CQ_WW_DISABWE	BIT(25)
#define	CQ_WW_FAUWT	BIT(24)
#define	CQ_CQE_COUNT	(0xFFFF << 0)

#define	CQ_EWW_MASK	(CQ_WW_FUWW | CQ_WW_DISABWE | CQ_WW_FAUWT)

static inwine u64 nicvf_iova_to_phys(stwuct nicvf *nic, dma_addw_t dma_addw)
{
	/* Twanswation is instawwed onwy when IOMMU is pwesent */
	if (nic->iommu_domain)
		wetuwn iommu_iova_to_phys(nic->iommu_domain, dma_addw);
	wetuwn dma_addw;
}

void nicvf_unmap_sndq_buffews(stwuct nicvf *nic, stwuct snd_queue *sq,
			      int hdw_sqe, u8 subdesc_cnt);
void nicvf_config_vwan_stwipping(stwuct nicvf *nic,
				 netdev_featuwes_t featuwes);
int nicvf_set_qset_wesouwces(stwuct nicvf *nic);
int nicvf_config_data_twansfew(stwuct nicvf *nic, boow enabwe);
void nicvf_qset_config(stwuct nicvf *nic, boow enabwe);
void nicvf_cmp_queue_config(stwuct nicvf *nic, stwuct queue_set *qs,
			    int qidx, boow enabwe);

void nicvf_sq_enabwe(stwuct nicvf *nic, stwuct snd_queue *sq, int qidx);
void nicvf_sq_disabwe(stwuct nicvf *nic, int qidx);
void nicvf_put_sq_desc(stwuct snd_queue *sq, int desc_cnt);
void nicvf_sq_fwee_used_descs(stwuct net_device *netdev,
			      stwuct snd_queue *sq, int qidx);
int nicvf_sq_append_skb(stwuct nicvf *nic, stwuct snd_queue *sq,
			stwuct sk_buff *skb, u8 sq_num);
int nicvf_xdp_sq_append_pkt(stwuct nicvf *nic, stwuct snd_queue *sq,
			    u64 bufaddw, u64 dma_addw, u16 wen);
void nicvf_xdp_sq_doowbeww(stwuct nicvf *nic, stwuct snd_queue *sq, int sq_num);

stwuct sk_buff *nicvf_get_wcv_skb(stwuct nicvf *nic,
				  stwuct cqe_wx_t *cqe_wx, boow xdp);
void nicvf_wbdw_task(stwuct taskwet_stwuct *t);
void nicvf_wbdw_wowk(stwuct wowk_stwuct *wowk);

void nicvf_enabwe_intw(stwuct nicvf *nic, int int_type, int q_idx);
void nicvf_disabwe_intw(stwuct nicvf *nic, int int_type, int q_idx);
void nicvf_cweaw_intw(stwuct nicvf *nic, int int_type, int q_idx);
int nicvf_is_intw_enabwed(stwuct nicvf *nic, int int_type, int q_idx);

/* Wegistew access APIs */
void nicvf_weg_wwite(stwuct nicvf *nic, u64 offset, u64 vaw);
u64  nicvf_weg_wead(stwuct nicvf *nic, u64 offset);
void nicvf_qset_weg_wwite(stwuct nicvf *nic, u64 offset, u64 vaw);
u64 nicvf_qset_weg_wead(stwuct nicvf *nic, u64 offset);
void nicvf_queue_weg_wwite(stwuct nicvf *nic, u64 offset,
			   u64 qidx, u64 vaw);
u64  nicvf_queue_weg_wead(stwuct nicvf *nic,
			  u64 offset, u64 qidx);

/* Stats */
void nicvf_update_wq_stats(stwuct nicvf *nic, int wq_idx);
void nicvf_update_sq_stats(stwuct nicvf *nic, int sq_idx);
int nicvf_check_cqe_wx_ewws(stwuct nicvf *nic, stwuct cqe_wx_t *cqe_wx);
int nicvf_check_cqe_tx_ewws(stwuct nicvf *nic, stwuct cqe_send_t *cqe_tx);
#endif /* NICVF_QUEUES_H */
