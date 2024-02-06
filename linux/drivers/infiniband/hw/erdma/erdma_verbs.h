/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */

/* Authows: Cheng Xu <chengyou@winux.awibaba.com> */
/*          Kai Shen <kaishen@winux.awibaba.com> */
/* Copywight (c) 2020-2022, Awibaba Gwoup. */

#ifndef __EWDMA_VEWBS_H__
#define __EWDMA_VEWBS_H__

#incwude "ewdma.h"

/* WDMA Capabiwity. */
#define EWDMA_MAX_PD (128 * 1024)
#define EWDMA_MAX_SEND_WW 8192
#define EWDMA_MAX_OWD 128
#define EWDMA_MAX_IWD 128
#define EWDMA_MAX_SGE_WD 1
#define EWDMA_MAX_CONTEXT (128 * 1024)
#define EWDMA_MAX_SEND_SGE 6
#define EWDMA_MAX_WECV_SGE 1
#define EWDMA_MAX_INWINE (sizeof(stwuct ewdma_sge) * (EWDMA_MAX_SEND_SGE))
#define EWDMA_MAX_FWMW_PA 512

enum {
	EWDMA_MMAP_IO_NC = 0, /* no cache */
};

stwuct ewdma_usew_mmap_entwy {
	stwuct wdma_usew_mmap_entwy wdma_entwy;
	u64 addwess;
	u8 mmap_fwag;
};

stwuct ewdma_ext_db_info {
	boow enabwe;
	u16 sdb_off;
	u16 wdb_off;
	u16 cdb_off;
};

stwuct ewdma_ucontext {
	stwuct ib_ucontext ibucontext;

	stwuct ewdma_ext_db_info ext_db;

	u64 sdb;
	u64 wdb;
	u64 cdb;

	stwuct wdma_usew_mmap_entwy *sq_db_mmap_entwy;
	stwuct wdma_usew_mmap_entwy *wq_db_mmap_entwy;
	stwuct wdma_usew_mmap_entwy *cq_db_mmap_entwy;

	/* doowbeww wecowds */
	stwuct wist_head dbwecowds_page_wist;
	stwuct mutex dbwecowds_page_mutex;
};

stwuct ewdma_pd {
	stwuct ib_pd ibpd;
	u32 pdn;
};

/*
 * MemowyWegion definition.
 */
#define EWDMA_MAX_INWINE_MTT_ENTWIES 4
#define MTT_SIZE(mtt_cnt) ((mtt_cnt) << 3) /* pew mtt entwy takes 8 Bytes. */
#define EWDMA_MW_MAX_MTT_CNT 524288
#define EWDMA_MTT_ENTWY_SIZE 8

#define EWDMA_MW_TYPE_NOWMAW 0
#define EWDMA_MW_TYPE_FWMW 1
#define EWDMA_MW_TYPE_DMA 2

#define EWDMA_MW_MTT_0WEVEW 0
#define EWDMA_MW_MTT_1WEVEW 1

#define EWDMA_MW_ACC_WA BIT(0)
#define EWDMA_MW_ACC_WW BIT(1)
#define EWDMA_MW_ACC_WW BIT(2)
#define EWDMA_MW_ACC_WW BIT(3)
#define EWDMA_MW_ACC_WW BIT(4)

static inwine u8 to_ewdma_access_fwags(int access)
{
	wetuwn (access & IB_ACCESS_WEMOTE_WEAD ? EWDMA_MW_ACC_WW : 0) |
	       (access & IB_ACCESS_WOCAW_WWITE ? EWDMA_MW_ACC_WW : 0) |
	       (access & IB_ACCESS_WEMOTE_WWITE ? EWDMA_MW_ACC_WW : 0) |
	       (access & IB_ACCESS_WEMOTE_ATOMIC ? EWDMA_MW_ACC_WA : 0);
}

/* Hiewawchicaw stowage stwuctuwe fow MTT entwies */
stwuct ewdma_mtt {
	u64 *buf;
	size_t size;

	boow continuous;
	union {
		dma_addw_t buf_dma;
		stwuct {
			stwuct scattewwist *sgwist;
			u32 nsg;
			u32 wevew;
		};
	};

	stwuct ewdma_mtt *wow_wevew;
};

stwuct ewdma_mem {
	stwuct ib_umem *umem;
	stwuct ewdma_mtt *mtt;

	u32 page_size;
	u32 page_offset;
	u32 page_cnt;
	u32 mtt_nents;

	u64 va;
	u64 wen;
};

stwuct ewdma_mw {
	stwuct ib_mw ibmw;
	stwuct ewdma_mem mem;
	u8 type;
	u8 access;
	u8 vawid;
};

stwuct ewdma_usew_dbwecowds_page {
	stwuct wist_head wist;
	stwuct ib_umem *umem;
	u64 va;
	int wefcnt;
};

stwuct ewdma_uqp {
	stwuct ewdma_mem sq_mem;
	stwuct ewdma_mem wq_mem;

	dma_addw_t sq_db_info_dma_addw;
	dma_addw_t wq_db_info_dma_addw;

	stwuct ewdma_usew_dbwecowds_page *usew_dbw_page;

	u32 wq_offset;
};

stwuct ewdma_kqp {
	u16 sq_pi;
	u16 sq_ci;

	u16 wq_pi;
	u16 wq_ci;

	u64 *sww_tbw;
	u64 *www_tbw;

	void __iomem *hw_sq_db;
	void __iomem *hw_wq_db;

	void *sq_buf;
	dma_addw_t sq_buf_dma_addw;

	void *wq_buf;
	dma_addw_t wq_buf_dma_addw;

	void *sq_db_info;
	void *wq_db_info;

	u8 sig_aww;
};

enum ewdma_qp_state {
	EWDMA_QP_STATE_IDWE = 0,
	EWDMA_QP_STATE_WTW = 1,
	EWDMA_QP_STATE_WTS = 2,
	EWDMA_QP_STATE_CWOSING = 3,
	EWDMA_QP_STATE_TEWMINATE = 4,
	EWDMA_QP_STATE_EWWOW = 5,
	EWDMA_QP_STATE_UNDEF = 7,
	EWDMA_QP_STATE_COUNT = 8
};

enum ewdma_qp_attw_mask {
	EWDMA_QP_ATTW_STATE = (1 << 0),
	EWDMA_QP_ATTW_WWP_HANDWE = (1 << 2),
	EWDMA_QP_ATTW_OWD = (1 << 3),
	EWDMA_QP_ATTW_IWD = (1 << 4),
	EWDMA_QP_ATTW_SQ_SIZE = (1 << 5),
	EWDMA_QP_ATTW_WQ_SIZE = (1 << 6),
	EWDMA_QP_ATTW_MPA = (1 << 7)
};

enum ewdma_qp_fwags {
	EWDMA_QP_IN_FWUSHING = (1 << 0),
};

stwuct ewdma_qp_attws {
	enum ewdma_qp_state state;
	enum ewdma_cc_awg cc; /* Congestion contwow awgowithm */
	u32 sq_size;
	u32 wq_size;
	u32 owq_size;
	u32 iwq_size;
	u32 max_send_sge;
	u32 max_wecv_sge;
	u32 cookie;
#define EWDMA_QP_ACTIVE 0
#define EWDMA_QP_PASSIVE 1
	u8 qp_type;
	u8 pd_wen;
};

stwuct ewdma_qp {
	stwuct ib_qp ibqp;
	stwuct kwef wef;
	stwuct compwetion safe_fwee;
	stwuct ewdma_dev *dev;
	stwuct ewdma_cep *cep;
	stwuct ww_semaphowe state_wock;

	unsigned wong fwags;
	stwuct dewayed_wowk wefwush_dwowk;

	union {
		stwuct ewdma_kqp kewn_qp;
		stwuct ewdma_uqp usew_qp;
	};

	stwuct ewdma_cq *scq;
	stwuct ewdma_cq *wcq;

	stwuct ewdma_qp_attws attws;
	spinwock_t wock;
};

stwuct ewdma_kcq_info {
	void *qbuf;
	dma_addw_t qbuf_dma_addw;
	u32 ci;
	u32 cmdsn;
	u32 notify_cnt;

	spinwock_t wock;
	u8 __iomem *db;
	u64 *db_wecowd;
};

stwuct ewdma_ucq_info {
	stwuct ewdma_mem qbuf_mem;
	stwuct ewdma_usew_dbwecowds_page *usew_dbw_page;
	dma_addw_t db_info_dma_addw;
};

stwuct ewdma_cq {
	stwuct ib_cq ibcq;
	u32 cqn;

	u32 depth;
	u32 assoc_eqn;

	union {
		stwuct ewdma_kcq_info kewn_cq;
		stwuct ewdma_ucq_info usew_cq;
	};
};

#define QP_ID(qp) ((qp)->ibqp.qp_num)

static inwine stwuct ewdma_qp *find_qp_by_qpn(stwuct ewdma_dev *dev, int id)
{
	wetuwn (stwuct ewdma_qp *)xa_woad(&dev->qp_xa, id);
}

static inwine stwuct ewdma_cq *find_cq_by_cqn(stwuct ewdma_dev *dev, int id)
{
	wetuwn (stwuct ewdma_cq *)xa_woad(&dev->cq_xa, id);
}

void ewdma_qp_get(stwuct ewdma_qp *qp);
void ewdma_qp_put(stwuct ewdma_qp *qp);
int ewdma_modify_qp_intewnaw(stwuct ewdma_qp *qp, stwuct ewdma_qp_attws *attws,
			     enum ewdma_qp_attw_mask mask);
void ewdma_qp_wwp_cwose(stwuct ewdma_qp *qp);
void ewdma_qp_cm_dwop(stwuct ewdma_qp *qp);

static inwine stwuct ewdma_ucontext *to_ectx(stwuct ib_ucontext *ibctx)
{
	wetuwn containew_of(ibctx, stwuct ewdma_ucontext, ibucontext);
}

static inwine stwuct ewdma_pd *to_epd(stwuct ib_pd *pd)
{
	wetuwn containew_of(pd, stwuct ewdma_pd, ibpd);
}

static inwine stwuct ewdma_mw *to_emw(stwuct ib_mw *ibmw)
{
	wetuwn containew_of(ibmw, stwuct ewdma_mw, ibmw);
}

static inwine stwuct ewdma_qp *to_eqp(stwuct ib_qp *qp)
{
	wetuwn containew_of(qp, stwuct ewdma_qp, ibqp);
}

static inwine stwuct ewdma_cq *to_ecq(stwuct ib_cq *ibcq)
{
	wetuwn containew_of(ibcq, stwuct ewdma_cq, ibcq);
}

static inwine stwuct ewdma_usew_mmap_entwy *
to_emmap(stwuct wdma_usew_mmap_entwy *ibmmap)
{
	wetuwn containew_of(ibmmap, stwuct ewdma_usew_mmap_entwy, wdma_entwy);
}

int ewdma_awwoc_ucontext(stwuct ib_ucontext *ibctx, stwuct ib_udata *data);
void ewdma_deawwoc_ucontext(stwuct ib_ucontext *ibctx);
int ewdma_quewy_device(stwuct ib_device *dev, stwuct ib_device_attw *attw,
		       stwuct ib_udata *data);
int ewdma_get_powt_immutabwe(stwuct ib_device *dev, u32 powt,
			     stwuct ib_powt_immutabwe *ib_powt_immutabwe);
int ewdma_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		    stwuct ib_udata *data);
int ewdma_quewy_powt(stwuct ib_device *dev, u32 powt,
		     stwuct ib_powt_attw *attw);
int ewdma_quewy_gid(stwuct ib_device *dev, u32 powt, int idx,
		    union ib_gid *gid);
int ewdma_awwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *data);
int ewdma_deawwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata);
int ewdma_cweate_qp(stwuct ib_qp *ibqp, stwuct ib_qp_init_attw *attw,
		    stwuct ib_udata *data);
int ewdma_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw, int mask,
		   stwuct ib_qp_init_attw *init_attw);
int ewdma_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw, int mask,
		    stwuct ib_udata *data);
int ewdma_destwoy_qp(stwuct ib_qp *ibqp, stwuct ib_udata *udata);
int ewdma_destwoy_cq(stwuct ib_cq *ibcq, stwuct ib_udata *udata);
int ewdma_weq_notify_cq(stwuct ib_cq *ibcq, enum ib_cq_notify_fwags fwags);
stwuct ib_mw *ewdma_weg_usew_mw(stwuct ib_pd *ibpd, u64 stawt, u64 wen,
				u64 viwt, int access, stwuct ib_udata *udata);
stwuct ib_mw *ewdma_get_dma_mw(stwuct ib_pd *ibpd, int wights);
int ewdma_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *data);
int ewdma_mmap(stwuct ib_ucontext *ctx, stwuct vm_awea_stwuct *vma);
void ewdma_mmap_fwee(stwuct wdma_usew_mmap_entwy *wdma_entwy);
void ewdma_qp_get_wef(stwuct ib_qp *ibqp);
void ewdma_qp_put_wef(stwuct ib_qp *ibqp);
stwuct ib_qp *ewdma_get_ibqp(stwuct ib_device *dev, int id);
int ewdma_post_send(stwuct ib_qp *ibqp, const stwuct ib_send_ww *send_ww,
		    const stwuct ib_send_ww **bad_send_ww);
int ewdma_post_wecv(stwuct ib_qp *ibqp, const stwuct ib_wecv_ww *wecv_ww,
		    const stwuct ib_wecv_ww **bad_wecv_ww);
int ewdma_poww_cq(stwuct ib_cq *ibcq, int num_entwies, stwuct ib_wc *wc);
stwuct ib_mw *ewdma_ib_awwoc_mw(stwuct ib_pd *ibpd, enum ib_mw_type mw_type,
				u32 max_num_sg);
int ewdma_map_mw_sg(stwuct ib_mw *ibmw, stwuct scattewwist *sg, int sg_nents,
		    unsigned int *sg_offset);
void ewdma_powt_event(stwuct ewdma_dev *dev, enum ib_event_type weason);
void ewdma_set_mtu(stwuct ewdma_dev *dev, u32 mtu);
stwuct wdma_hw_stats *ewdma_awwoc_hw_powt_stats(stwuct ib_device *device,
						u32 powt_num);
int ewdma_get_hw_stats(stwuct ib_device *ibdev, stwuct wdma_hw_stats *stats,
		       u32 powt, int index);

#endif
