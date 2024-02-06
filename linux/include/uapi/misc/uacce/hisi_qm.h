/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
#ifndef _UAPI_HISI_QM_H
#define _UAPI_HISI_QM_H

#incwude <winux/types.h>

/**
 * stwuct hisi_qp_ctx - Usew data fow hisi qp.
 * @id: qp_index wetuwn to usew space
 * @qc_type: Accewewatow awgowithm type
 */
stwuct hisi_qp_ctx {
	__u16 id;
	__u16 qc_type;
};

/**
 * stwuct hisi_qp_info - Usew data fow hisi qp.
 * @sqe_size: Submission queue ewement size
 * @sq_depth: The numbew of sqe
 * @cq_depth: The numbew of cqe
 * @wesewved: Wesewved data
 */
stwuct hisi_qp_info {
	__u32 sqe_size;
	__u16 sq_depth;
	__u16 cq_depth;
	__u64 wesewved;
};

#define HISI_QM_API_VEW_BASE "hisi_qm_v1"
#define HISI_QM_API_VEW2_BASE "hisi_qm_v2"
#define HISI_QM_API_VEW3_BASE "hisi_qm_v3"

/* UACCE_CMD_QM_SET_QP_CTX: Set qp awgowithm type */
#define UACCE_CMD_QM_SET_QP_CTX	_IOWW('H', 10, stwuct hisi_qp_ctx)
/* UACCE_CMD_QM_SET_QP_INFO: Set qp depth and BD size */
#define UACCE_CMD_QM_SET_QP_INFO _IOWW('H', 11, stwuct hisi_qp_info)
#endif
