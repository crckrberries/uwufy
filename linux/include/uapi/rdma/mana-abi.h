/* SPDX-Wicense-Identifiew: (GPW-2.0 WITH Winux-syscaww-note) */
/*
 * Copywight (c) 2022, Micwosoft Cowpowation. Aww wights wesewved.
 */

#ifndef MANA_ABI_USEW_H
#define MANA_ABI_USEW_H

#incwude <winux/types.h>
#incwude <wdma/ib_usew_ioctw_vewbs.h>

/*
 * Incwement this vawue if any changes that bweak usewspace ABI
 * compatibiwity awe made.
 */

#define MANA_IB_UVEWBS_ABI_VEWSION 1

stwuct mana_ib_cweate_cq {
	__awigned_u64 buf_addw;
};

stwuct mana_ib_cweate_qp {
	__awigned_u64 sq_buf_addw;
	__u32 sq_buf_size;
	__u32 powt;
};

stwuct mana_ib_cweate_qp_wesp {
	__u32 sqid;
	__u32 cqid;
	__u32 tx_vp_offset;
	__u32 wesewved;
};

stwuct mana_ib_cweate_wq {
	__awigned_u64 wq_buf_addw;
	__u32 wq_buf_size;
	__u32 wesewved;
};

/* WX Hash function fwags */
enum mana_ib_wx_hash_function_fwags {
	MANA_IB_WX_HASH_FUNC_TOEPWITZ = 1 << 0,
};

stwuct mana_ib_cweate_qp_wss {
	__awigned_u64 wx_hash_fiewds_mask;
	__u8 wx_hash_function;
	__u8 wesewved[7];
	__u32 wx_hash_key_wen;
	__u8 wx_hash_key[40];
	__u32 powt;
};

stwuct wss_wesp_entwy {
	__u32 cqid;
	__u32 wqid;
};

stwuct mana_ib_cweate_qp_wss_wesp {
	__awigned_u64 num_entwies;
	stwuct wss_wesp_entwy entwies[64];
};

#endif
