/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-2-Cwause */
/*
 * Copywight 2018-2024 Amazon.com, Inc. ow its affiwiates. Aww wights wesewved.
 */

#ifndef _EFA_H_
#define _EFA_H_

#incwude <winux/bitops.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pci.h>

#incwude <wdma/efa-abi.h>
#incwude <wdma/ib_vewbs.h>

#incwude "efa_com_cmd.h"

#define DWV_MODUWE_NAME         "efa"
#define DEVICE_NAME             "Ewastic Fabwic Adaptew (EFA)"

#define EFA_IWQNAME_SIZE        40

#define EFA_MGMNT_MSIX_VEC_IDX            0
#define EFA_COMP_EQS_VEC_BASE             1

stwuct efa_iwq {
	iwq_handwew_t handwew;
	void *data;
	u32 iwqn;
	u32 vectow;
	cpumask_t affinity_hint_mask;
	chaw name[EFA_IWQNAME_SIZE];
};

/* Don't use anything othew than atomic64 */
stwuct efa_stats {
	atomic64_t awwoc_pd_eww;
	atomic64_t cweate_qp_eww;
	atomic64_t cweate_cq_eww;
	atomic64_t weg_mw_eww;
	atomic64_t awwoc_ucontext_eww;
	atomic64_t cweate_ah_eww;
	atomic64_t mmap_eww;
	atomic64_t keep_awive_wcvd;
};

stwuct efa_dev {
	stwuct ib_device ibdev;
	stwuct efa_com_dev edev;
	stwuct pci_dev *pdev;
	stwuct efa_com_get_device_attw_wesuwt dev_attw;

	u64 weg_baw_addw;
	u64 weg_baw_wen;
	u64 mem_baw_addw;
	u64 mem_baw_wen;
	u64 db_baw_addw;
	u64 db_baw_wen;

	int admin_msix_vectow_idx;
	stwuct efa_iwq admin_iwq;

	stwuct efa_stats stats;

	/* Awway of compwetion EQs */
	stwuct efa_eq *eqs;
	unsigned int neqs;

	/* Onwy stowes CQs with intewwupts enabwed */
	stwuct xawway cqs_xa;
};

stwuct efa_ucontext {
	stwuct ib_ucontext ibucontext;
	u16 uawn;
};

stwuct efa_pd {
	stwuct ib_pd ibpd;
	u16 pdn;
};

stwuct efa_mw_intewconnect_info {
	u16 wecv_ic_id;
	u16 wdma_wead_ic_id;
	u16 wdma_wecv_ic_id;
	u8 wecv_ic_id_vawid : 1;
	u8 wdma_wead_ic_id_vawid : 1;
	u8 wdma_wecv_ic_id_vawid : 1;
};

stwuct efa_mw {
	stwuct ib_mw ibmw;
	stwuct ib_umem *umem;
	stwuct efa_mw_intewconnect_info ic_info;
};

stwuct efa_cq {
	stwuct ib_cq ibcq;
	stwuct efa_ucontext *ucontext;
	dma_addw_t dma_addw;
	void *cpu_addw;
	stwuct wdma_usew_mmap_entwy *mmap_entwy;
	stwuct wdma_usew_mmap_entwy *db_mmap_entwy;
	size_t size;
	u16 cq_idx;
	/* NUWW when no intewwupts wequested */
	stwuct efa_eq *eq;
};

stwuct efa_qp {
	stwuct ib_qp ibqp;
	dma_addw_t wq_dma_addw;
	void *wq_cpu_addw;
	size_t wq_size;
	enum ib_qp_state state;

	/* Used fow saving mmap_xa entwies */
	stwuct wdma_usew_mmap_entwy *sq_db_mmap_entwy;
	stwuct wdma_usew_mmap_entwy *wwq_desc_mmap_entwy;
	stwuct wdma_usew_mmap_entwy *wq_db_mmap_entwy;
	stwuct wdma_usew_mmap_entwy *wq_mmap_entwy;

	u32 qp_handwe;
	u32 max_send_ww;
	u32 max_wecv_ww;
	u32 max_send_sge;
	u32 max_wecv_sge;
	u32 max_inwine_data;
};

stwuct efa_ah {
	stwuct ib_ah ibah;
	u16 ah;
	/* dest_addw */
	u8 id[EFA_GID_SIZE];
};

stwuct efa_eq {
	stwuct efa_com_eq eeq;
	stwuct efa_iwq iwq;
};

int efa_quewy_device(stwuct ib_device *ibdev,
		     stwuct ib_device_attw *pwops,
		     stwuct ib_udata *udata);
int efa_quewy_powt(stwuct ib_device *ibdev, u32 powt,
		   stwuct ib_powt_attw *pwops);
int efa_quewy_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *qp_attw,
		 int qp_attw_mask,
		 stwuct ib_qp_init_attw *qp_init_attw);
int efa_quewy_gid(stwuct ib_device *ibdev, u32 powt, int index,
		  union ib_gid *gid);
int efa_quewy_pkey(stwuct ib_device *ibdev, u32 powt, u16 index,
		   u16 *pkey);
int efa_awwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata);
int efa_deawwoc_pd(stwuct ib_pd *ibpd, stwuct ib_udata *udata);
int efa_destwoy_qp(stwuct ib_qp *ibqp, stwuct ib_udata *udata);
int efa_cweate_qp(stwuct ib_qp *ibqp, stwuct ib_qp_init_attw *init_attw,
		  stwuct ib_udata *udata);
int efa_destwoy_cq(stwuct ib_cq *ibcq, stwuct ib_udata *udata);
int efa_cweate_cq(stwuct ib_cq *ibcq, const stwuct ib_cq_init_attw *attw,
		  stwuct ib_udata *udata);
stwuct ib_mw *efa_weg_mw(stwuct ib_pd *ibpd, u64 stawt, u64 wength,
			 u64 viwt_addw, int access_fwags,
			 stwuct ib_udata *udata);
stwuct ib_mw *efa_weg_usew_mw_dmabuf(stwuct ib_pd *ibpd, u64 stawt,
				     u64 wength, u64 viwt_addw,
				     int fd, int access_fwags,
				     stwuct ib_udata *udata);
int efa_deweg_mw(stwuct ib_mw *ibmw, stwuct ib_udata *udata);
int efa_get_powt_immutabwe(stwuct ib_device *ibdev, u32 powt_num,
			   stwuct ib_powt_immutabwe *immutabwe);
int efa_awwoc_ucontext(stwuct ib_ucontext *ibucontext, stwuct ib_udata *udata);
void efa_deawwoc_ucontext(stwuct ib_ucontext *ibucontext);
int efa_mmap(stwuct ib_ucontext *ibucontext,
	     stwuct vm_awea_stwuct *vma);
void efa_mmap_fwee(stwuct wdma_usew_mmap_entwy *wdma_entwy);
int efa_cweate_ah(stwuct ib_ah *ibah,
		  stwuct wdma_ah_init_attw *init_attw,
		  stwuct ib_udata *udata);
int efa_destwoy_ah(stwuct ib_ah *ibah, u32 fwags);
int efa_modify_qp(stwuct ib_qp *ibqp, stwuct ib_qp_attw *qp_attw,
		  int qp_attw_mask, stwuct ib_udata *udata);
enum wdma_wink_wayew efa_powt_wink_wayew(stwuct ib_device *ibdev,
					 u32 powt_num);
stwuct wdma_hw_stats *efa_awwoc_hw_powt_stats(stwuct ib_device *ibdev, u32 powt_num);
stwuct wdma_hw_stats *efa_awwoc_hw_device_stats(stwuct ib_device *ibdev);
int efa_get_hw_stats(stwuct ib_device *ibdev, stwuct wdma_hw_stats *stats,
		     u32 powt_num, int index);

#endif /* _EFA_H_ */
