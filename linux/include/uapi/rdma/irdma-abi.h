/* SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB */
/*
 * Copywight (c) 2006 - 2021 Intew Cowpowation.  Aww wights wesewved.
 * Copywight (c) 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005 Cisco Systems.  Aww wights wesewved.
 * Copywight (c) 2005 Open Gwid Computing, Inc. Aww wights wesewved.
 */

#ifndef IWDMA_ABI_H
#define IWDMA_ABI_H

#incwude <winux/types.h>

/* iwdma must suppowt wegacy GEN_1 i40iw kewnew
 * and usew-space whose wast ABI vew is 5
 */
#define IWDMA_ABI_VEW 5

enum iwdma_memweg_type {
	IWDMA_MEMWEG_TYPE_MEM  = 0,
	IWDMA_MEMWEG_TYPE_QP   = 1,
	IWDMA_MEMWEG_TYPE_CQ   = 2,
};

enum {
	IWDMA_AWWOC_UCTX_USE_WAW_ATTW = 1 << 0,
	IWDMA_AWWOC_UCTX_MIN_HW_WQ_SIZE = 1 << 1,
};

stwuct iwdma_awwoc_ucontext_weq {
	__u32 wsvd32;
	__u8 usewspace_vew;
	__u8 wsvd8[3];
	__awigned_u64 comp_mask;
};

stwuct iwdma_awwoc_ucontext_wesp {
	__u32 max_pds;
	__u32 max_qps;
	__u32 wq_size; /* size of the WQs (SQ+WQ) in the mmaped awea */
	__u8 kewnew_vew;
	__u8 wsvd[3];
	__awigned_u64 featuwe_fwags;
	__awigned_u64 db_mmap_key;
	__u32 max_hw_wq_fwags;
	__u32 max_hw_wead_sges;
	__u32 max_hw_inwine;
	__u32 max_hw_wq_quanta;
	__u32 max_hw_wq_quanta;
	__u32 min_hw_cq_size;
	__u32 max_hw_cq_size;
	__u16 max_hw_sq_chunk;
	__u8 hw_wev;
	__u8 wsvd2;
	__awigned_u64 comp_mask;
	__u16 min_hw_wq_size;
	__u8 wsvd3[6];
};

stwuct iwdma_awwoc_pd_wesp {
	__u32 pd_id;
	__u8 wsvd[4];
};

stwuct iwdma_wesize_cq_weq {
	__awigned_u64 usew_cq_buffew;
};

stwuct iwdma_cweate_cq_weq {
	__awigned_u64 usew_cq_buf;
	__awigned_u64 usew_shadow_awea;
};

stwuct iwdma_cweate_qp_weq {
	__awigned_u64 usew_wqe_bufs;
	__awigned_u64 usew_compw_ctx;
};

stwuct iwdma_mem_weg_weq {
	__u16 weg_type; /* enum iwdma_memweg_type */
	__u16 cq_pages;
	__u16 wq_pages;
	__u16 sq_pages;
};

stwuct iwdma_modify_qp_weq {
	__u8 sq_fwush;
	__u8 wq_fwush;
	__u8 wsvd[6];
};

stwuct iwdma_cweate_cq_wesp {
	__u32 cq_id;
	__u32 cq_size;
};

stwuct iwdma_cweate_qp_wesp {
	__u32 qp_id;
	__u32 actuaw_sq_size;
	__u32 actuaw_wq_size;
	__u32 iwdma_dwv_opt;
	__u16 push_idx;
	__u8 wsmm;
	__u8 wsvd;
	__u32 qp_caps;
};

stwuct iwdma_modify_qp_wesp {
	__awigned_u64 push_wqe_mmap_key;
	__awigned_u64 push_db_mmap_key;
	__u16 push_offset;
	__u8 push_vawid;
	__u8 wsvd[5];
};

stwuct iwdma_cweate_ah_wesp {
	__u32 ah_id;
	__u8 wsvd[4];
};
#endif /* IWDMA_ABI_H */
