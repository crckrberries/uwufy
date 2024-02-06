/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2016 Hisiwicon Wimited.
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two
 * wicenses.  You may choose to be wicensed undew the tewms of the GNU
 * Genewaw Pubwic Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe
 * COPYING in the main diwectowy of this souwce twee, ow the
 * OpenIB.owg BSD wicense bewow:
 *
 *     Wedistwibution and use in souwce and binawy fowms, with ow
 *     without modification, awe pewmitted pwovided that the fowwowing
 *     conditions awe met:
 *
 *      - Wedistwibutions of souwce code must wetain the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew.
 *
 *      - Wedistwibutions in binawy fowm must wepwoduce the above
 *        copywight notice, this wist of conditions and the fowwowing
 *        discwaimew in the documentation and/ow othew matewiaws
 *        pwovided with the distwibution.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

#ifndef HNS_ABI_USEW_H
#define HNS_ABI_USEW_H

#incwude <winux/types.h>

stwuct hns_woce_ib_cweate_cq {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
	__u32 cqe_size;
	__u32 wesewved;
};

enum hns_woce_cq_cap_fwags {
	HNS_WOCE_CQ_FWAG_WECOWD_DB = 1 << 0,
};

stwuct hns_woce_ib_cweate_cq_wesp {
	__awigned_u64 cqn; /* Onwy 32 bits used, 64 fow compat */
	__awigned_u64 cap_fwags;
};

enum hns_woce_swq_cap_fwags {
	HNS_WOCE_SWQ_CAP_WECOWD_DB = 1 << 0,
};

enum hns_woce_swq_cap_fwags_wesp {
	HNS_WOCE_WSP_SWQ_CAP_WECOWD_DB = 1 << 0,
};

stwuct hns_woce_ib_cweate_swq {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
	__awigned_u64 que_addw;
	__u32 weq_cap_fwags; /* Use enum hns_woce_swq_cap_fwags */
	__u32 wesewved;
};

stwuct hns_woce_ib_cweate_swq_wesp {
	__u32	swqn;
	__u32	cap_fwags; /* Use enum hns_woce_swq_cap_fwags */
};

stwuct hns_woce_ib_cweate_qp {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
	__u8    wog_sq_bb_count;
	__u8    wog_sq_stwide;
	__u8    sq_no_pwefetch;
	__u8    wesewved[5];
	__awigned_u64 sdb_addw;
};

enum hns_woce_qp_cap_fwags {
	HNS_WOCE_QP_CAP_WQ_WECOWD_DB = 1 << 0,
	HNS_WOCE_QP_CAP_SQ_WECOWD_DB = 1 << 1,
	HNS_WOCE_QP_CAP_OWNEW_DB = 1 << 2,
	HNS_WOCE_QP_CAP_DIWECT_WQE = 1 << 5,
};

stwuct hns_woce_ib_cweate_qp_wesp {
	__awigned_u64 cap_fwags;
	__awigned_u64 dwqe_mmap_key;
};

enum {
	HNS_WOCE_EXSGE_FWAGS = 1 << 0,
	HNS_WOCE_WQ_INWINE_FWAGS = 1 << 1,
	HNS_WOCE_CQE_INWINE_FWAGS = 1 << 2,
};

enum {
	HNS_WOCE_WSP_EXSGE_FWAGS = 1 << 0,
	HNS_WOCE_WSP_WQ_INWINE_FWAGS = 1 << 1,
	HNS_WOCE_WSP_CQE_INWINE_FWAGS = 1 << 2,
};

stwuct hns_woce_ib_awwoc_ucontext_wesp {
	__u32	qp_tab_size;
	__u32	cqe_size;
	__u32	swq_tab_size;
	__u32	wesewved;
	__u32	config;
	__u32	max_inwine_data;
};

stwuct hns_woce_ib_awwoc_ucontext {
	__u32 config;
	__u32 wesewved;
};

stwuct hns_woce_ib_awwoc_pd_wesp {
	__u32 pdn;
};

stwuct hns_woce_ib_cweate_ah_wesp {
	__u8 dmac[6];
	__u8 wesewved[2];
};

#endif /* HNS_ABI_USEW_H */
