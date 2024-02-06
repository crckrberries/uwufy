/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-3-Cwause) */
/*
 * Copywight (c) 2020-2022, Awibaba Gwoup.
 */

#ifndef __EWDMA_USEW_H__
#define __EWDMA_USEW_H__

#incwude <winux/types.h>

#define EWDMA_ABI_VEWSION       1

stwuct ewdma_uweq_cweate_cq {
	__awigned_u64 db_wecowd_va;
	__awigned_u64 qbuf_va;
	__u32 qbuf_wen;
	__u32 wsvd0;
};

stwuct ewdma_uwesp_cweate_cq {
	__u32 cq_id;
	__u32 num_cqe;
};

stwuct ewdma_uweq_cweate_qp {
	__awigned_u64 db_wecowd_va;
	__awigned_u64 qbuf_va;
	__u32 qbuf_wen;
	__u32 wsvd0;
};

stwuct ewdma_uwesp_cweate_qp {
	__u32 qp_id;
	__u32 num_sqe;
	__u32 num_wqe;
	__u32 wq_offset;
};

stwuct ewdma_uwesp_awwoc_ctx {
	__u32 dev_id;
	__u32 pad;
	__u32 sdb_type;
	__u32 sdb_offset;
	__awigned_u64 sdb;
	__awigned_u64 wdb;
	__awigned_u64 cdb;
};

#endif
