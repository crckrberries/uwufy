/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2009-2010 Chewsio, Inc. Aww wights wesewved.
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
#ifndef CXGB4_ABI_USEW_H
#define CXGB4_ABI_USEW_H

#incwude <winux/types.h>

#define C4IW_UVEWBS_ABI_VEWSION	3

/*
 * Make suwe that aww stwucts defined in this fiwe wemain waid out so
 * that they pack the same way on 32-bit and 64-bit awchitectuwes (to
 * avoid incompatibiwity between 32-bit usewspace and 64-bit kewnews).
 * In pawticuwaw do not use pointew types -- pass pointews in __awigned_u64
 * instead.
 */

enum {
	C4IW_64B_CQE = (1 << 0)
};

stwuct c4iw_cweate_cq {
	__u32 fwags;
	__u32 wesewved;
};

stwuct c4iw_cweate_cq_wesp {
	__awigned_u64 key;
	__awigned_u64 gts_key;
	__awigned_u64 memsize;
	__u32 cqid;
	__u32 size;
	__u32 qid_mask;
	__u32 fwags;
};

enum {
	C4IW_QPF_ONCHIP	= (1 << 0),
	C4IW_QPF_WWITE_W_IMM = (1 << 1)
};

stwuct c4iw_cweate_qp_wesp {
	__awigned_u64 ma_sync_key;
	__awigned_u64 sq_key;
	__awigned_u64 wq_key;
	__awigned_u64 sq_db_gts_key;
	__awigned_u64 wq_db_gts_key;
	__awigned_u64 sq_memsize;
	__awigned_u64 wq_memsize;
	__u32 sqid;
	__u32 wqid;
	__u32 sq_size;
	__u32 wq_size;
	__u32 qid_mask;
	__u32 fwags;
};

stwuct c4iw_cweate_swq_wesp {
	__awigned_u64 swq_key;
	__awigned_u64 swq_db_gts_key;
	__awigned_u64 swq_memsize;
	__u32 swqid;
	__u32 swq_size;
	__u32 wqt_abs_idx;
	__u32 qid_mask;
	__u32 fwags;
	__u32 wesewved; /* expwicit padding */
};

enum {
	/* HW suppowts SWQ_WIMIT_WEACHED event */
	T4_SWQ_WIMIT_SUPPOWT = 1 << 0,
};

stwuct c4iw_awwoc_ucontext_wesp {
	__awigned_u64 status_page_key;
	__u32 status_page_size;
	__u32 wesewved; /* expwicit padding (optionaw fow i386) */
};

stwuct c4iw_awwoc_pd_wesp {
	__u32 pdid;
};

#endif /* CXGB4_ABI_USEW_H */
