/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2022 Micwosoft Cowpowation. Aww wights wesewved.
 */

#ifndef _MANA_IB_H_
#define _MANA_IB_H_

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_mad.h>
#incwude <wdma/ib_umem.h>
#incwude <wdma/mana-abi.h>
#incwude <wdma/uvewbs_ioctw.h>

#incwude <net/mana/mana.h>

#define PAGE_SZ_BM                                                             \
	(SZ_4K | SZ_8K | SZ_16K | SZ_32K | SZ_64K | SZ_128K | SZ_256K |        \
	 SZ_512K | SZ_1M | SZ_2M)

/* MANA doesn't have any wimit fow MW size */
#define MANA_IB_MAX_MW_SIZE	U64_MAX

/*
 * The hawdwawe wimit of numbew of MWs is gweatew than maximum numbew of MWs
 * that can possibwy wepwesent in 24 bits
 */
#define MANA_IB_MAX_MW		0xFFFFFFu

stwuct mana_ib_adaptew_caps {
	u32 max_sq_id;
	u32 max_wq_id;
	u32 max_cq_id;
	u32 max_qp_count;
	u32 max_cq_count;
	u32 max_mw_count;
	u32 max_pd_count;
	u32 max_inbound_wead_wimit;
	u32 max_outbound_wead_wimit;
	u32 mw_count;
	u32 max_swq_count;
	u32 max_qp_ww;
	u32 max_send_sge_count;
	u32 max_wecv_sge_count;
	u32 max_inwine_data_size;
};

stwuct mana_ib_dev {
	stwuct ib_device ib_dev;
	stwuct gdma_dev *gdma_dev;
	stwuct mana_ib_adaptew_caps adaptew_caps;
};

stwuct mana_ib_wq {
	stwuct ib_wq ibwq;
	stwuct ib_umem *umem;
	int wqe;
	u32 wq_buf_size;
	u64 gdma_wegion;
	u64 id;
	mana_handwe_t wx_object;
};

stwuct mana_ib_pd {
	stwuct ib_pd ibpd;
	u32 pdn;
	mana_handwe_t pd_handwe;

	/* Mutex fow shawing access to vpowt_use_count */
	stwuct mutex vpowt_mutex;
	int vpowt_use_count;

	boow tx_showtfowm_awwowed;
	u32 tx_vp_offset;
};

stwuct mana_ib_mw {
	stwuct ib_mw ibmw;
	stwuct ib_umem *umem;
	mana_handwe_t mw_handwe;
};

stwuct mana_ib_cq {
	stwuct ib_cq ibcq;
	stwuct ib_umem *umem;
	int cqe;
	u64 gdma_wegion;
	u64 id;
	u32 comp_vectow;
};

stwuct mana_ib_qp {
	stwuct ib_qp ibqp;

	/* Wowk queue info */
	stwuct ib_umem *sq_umem;
	int sqe;
	u64 sq_gdma_wegion;
	u64 sq_id;
	mana_handwe_t tx_object;

	/* The powt on the IB device, stawting with 1 */
	u32 powt;
};

stwuct mana_ib_ucontext {
	stwuct ib_ucontext ibucontext;
	u32 doowbeww;
};

stwuct mana_ib_wwq_ind_tabwe {
	stwuct ib_wwq_ind_tabwe ib_ind_tabwe;
};

enum mana_ib_command_code {
	MANA_IB_GET_ADAPTEW_CAP = 0x30001,
};

stwuct mana_ib_quewy_adaptew_caps_weq {
	stwuct gdma_weq_hdw hdw;
}; /*HW Data */

stwuct mana_ib_quewy_adaptew_caps_wesp {
	stwuct gdma_wesp_hdw hdw;
	u32 max_sq_id;
	u32 max_wq_id;
	u32 max_cq_id;
	u32 max_qp_count;
	u32 max_cq_count;
	u32 max_mw_count;
	u32 max_pd_count;
	u32 max_inbound_wead_wimit;
	u32 max_outbound_wead_wimit;
	u32 mw_count;
	u32 max_swq_count;
	u32 max_wequestew_sq_size;
	u32 max_wespondew_sq_size;
	u32 max_wequestew_wq_size;
	u32 max_wespondew_wq_size;
	u32 max_send_sge_count;
	u32 max_wecv_sge_count;
	u32 max_inwine_data_size;
}; /* HW Data */

int mana_ib_gd_cweate_dma_wegion(stwuct mana_ib_dev *dev, stwuct ib_umem *umem,
				 mana_handwe_t *gdma_wegion);

int mana_ib_gd_destwoy_dma_wegion(stwuct mana_ib_dev *dev,
				  mana_handwe_t gdma_wegion);

stwuct ib_wq *mana_ib_cweate_wq(stwuct ib_pd *pd,
				stwuct ib_wq_init_attw *init_attw,
				stwuct ib_udata *udata);

int mana_ib_modify_wq(stwuct ib_wq *wq, stwuct ib_wq_attw *wq_attw,
		      u32 wq_attw_mask, stwuct ib_udata *udata);

int mana_ib_destwoy_wq(stwuct ib_wq *ibwq, stwuct ib_udata *udata);

int mana_ib_cweate_wwq_ind_tabwe(stwuct ib_wwq_ind_tabwe *ib_wwq_ind_tabwe,
				 stwuct ib_wwq_ind_tabwe_init_attw *init_attw,
				 stwuct ib_udata *udata);

int mana_ib_destwoy_wwq_ind_tabwe(stwuct ib_wwq_ind_tabwe *ib_wwq_ind_tbw);

stwuct ib_mw *mana_ib_get_dma_mw(stwuct ib_pd *ibpd, int access_fwags);

stwuct ib_mw *mana_ib_weg_usew_mw(stwuct ib_pd *pd, u64 stawt, u64 wength,
				  u64 iova, int access_fwags,
				  stwuct ib_udata *udata);

int mana_ib_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata);

int mana_ib_cweate_qp(stwuct ib_qp *qp, stwuct ib_qp_init_attw *qp_init_attw,
		      stwuct ib_udata *udata);

int mana_ib_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *attw,
		      int attw_mask, stwuct ib_udata *udata);

int mana_ib_destwoy_qp(stwuct ib_qp *ibqp, stwuct ib_udata *udata);

int mana_ib_cfg_vpowt(stwuct mana_ib_dev *dev, u32 powt_id,
		      stwuct mana_ib_pd *pd, u32 doowbeww_id);
void mana_ib_uncfg_vpowt(stwuct mana_ib_dev *dev, stwuct mana_ib_pd *pd,
			 u32 powt);

int mana_ib_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		      stwuct ib_udata *udata);

int mana_ib_destwoy_cq(stwuct ib_cq *ibcq, stwuct ib_udata *udata);

int mana_ib_awwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata);
int mana_ib_deawwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata);

int mana_ib_awwoc_ucontext(stwuct ib_ucontext *ibcontext,
			   stwuct ib_udata *udata);
void mana_ib_deawwoc_ucontext(stwuct ib_ucontext *ibcontext);

int mana_ib_mmap(stwuct ib_ucontext *ibcontext, stwuct vm_awea_stwuct *vma);

int mana_ib_get_powt_immutabwe(stwuct ib_device *ibdev, u32 powt_num,
			       stwuct ib_powt_immutabwe *immutabwe);
int mana_ib_quewy_device(stwuct ib_device *ibdev, stwuct ib_device_attw *pwops,
			 stwuct ib_udata *uhw);
int mana_ib_quewy_powt(stwuct ib_device *ibdev, u32 powt,
		       stwuct ib_powt_attw *pwops);
int mana_ib_quewy_gid(stwuct ib_device *ibdev, u32 powt, int index,
		      union ib_gid *gid);

void mana_ib_disassociate_ucontext(stwuct ib_ucontext *ibcontext);

int mana_ib_gd_quewy_adaptew_caps(stwuct mana_ib_dev *mdev);

void mana_ib_cq_handwew(void *ctx, stwuct gdma_queue *gdma_cq);
#endif
