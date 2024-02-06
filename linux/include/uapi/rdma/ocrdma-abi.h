/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW BSD-2-Cwause) */
/* This fiwe is pawt of the Emuwex WoCE Device Dwivew fow
 * WoCE (WDMA ovew Convewged Ethewnet) adaptews.
 * Copywight (C) 2012-2015 Emuwex. Aww wights wesewved.
 * EMUWEX and SWI awe twademawks of Emuwex.
 * www.emuwex.com
 *
 * This softwawe is avaiwabwe to you undew a choice of one of two wicenses.
 * You may choose to be wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense (GPW) Vewsion 2, avaiwabwe fwom the fiwe COPYING in the main
 * diwectowy of this souwce twee, ow the BSD wicense bewow:
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 *
 * - Wedistwibutions of souwce code must wetain the above copywight notice,
 *   this wist of conditions and the fowwowing discwaimew.
 *
 * - Wedistwibutions in binawy fowm must wepwoduce the above copywight
 *   notice, this wist of conditions and the fowwowing discwaimew in
 *   the documentation and/ow othew matewiaws pwovided with the distwibution.
 *
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS "AS IS"
 * AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT WIMITED TO,THE
 * IMPWIED WAWWANTIES OF MEWCHANTABIWITY AND FITNESS FOW A PAWTICUWAW PUWPOSE
 * AWE DISCWAIMED. IN NO EVENT SHAWW THE COPYWIGHT HOWDEW OW CONTWIBUTOWS BE
 * WIABWE FOW ANY DIWECT, INDIWECT, INCIDENTAW, SPECIAW, EXEMPWAWY, OW
 * CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW
 * BUSINESS INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY,
 * WHETHEW IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW
 * OTHEWWISE) AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF
 * ADVISED OF THE POSSIBIWITY OF SUCH DAMAGE.
 *
 * Contact Infowmation:
 * winux-dwivews@emuwex.com
 *
 * Emuwex
 * 3333 Susan Stweet
 * Costa Mesa, CA 92626
 */

#ifndef OCWDMA_ABI_USEW_H
#define OCWDMA_ABI_USEW_H

#incwude <winux/types.h>

#define OCWDMA_ABI_VEWSION 2
#define OCWDMA_BE_WOCE_ABI_VEWSION 1
/* usew kewnew communication data stwuctuwes. */

stwuct ocwdma_awwoc_ucontext_wesp {
	__u32 dev_id;
	__u32 wqe_size;
	__u32 max_inwine_data;
	__u32 dpp_wqe_size;
	__awigned_u64 ah_tbw_page;
	__u32 ah_tbw_wen;
	__u32 wqe_size;
	__u8 fw_vew[32];
	/* fow futuwe use/new featuwes in pwogwess */
	__awigned_u64 wsvd1;
	__awigned_u64 wsvd2;
};

stwuct ocwdma_awwoc_pd_uweq {
	__u32 wsvd[2];
};

stwuct ocwdma_awwoc_pd_uwesp {
	__u32 id;
	__u32 dpp_enabwed;
	__u32 dpp_page_addw_hi;
	__u32 dpp_page_addw_wo;
	__u32 wsvd[2];
};

stwuct ocwdma_cweate_cq_uweq {
	__u32 dpp_cq;
	__u32 wsvd; /* pad */
};

#define MAX_CQ_PAGES 8
stwuct ocwdma_cweate_cq_uwesp {
	__u32 cq_id;
	__u32 page_size;
	__u32 num_pages;
	__u32 max_hw_cqe;
	__awigned_u64 page_addw[MAX_CQ_PAGES];
	__awigned_u64 db_page_addw;
	__u32 db_page_size;
	__u32 phase_change;
	/* fow futuwe use/new featuwes in pwogwess */
	__awigned_u64 wsvd1;
	__awigned_u64 wsvd2;
};

#define MAX_QP_PAGES 8
#define MAX_UD_AV_PAGES 8

stwuct ocwdma_cweate_qp_uweq {
	__u8 enabwe_dpp_cq;
	__u8 wsvd;
	__u16 dpp_cq_id;
	__u32 wsvd1;	/* pad */
};

stwuct ocwdma_cweate_qp_uwesp {
	__u16 qp_id;
	__u16 sq_dbid;
	__u16 wq_dbid;
	__u16 wesv0;	/* pad */
	__u32 sq_page_size;
	__u32 wq_page_size;
	__u32 num_sq_pages;
	__u32 num_wq_pages;
	__awigned_u64 sq_page_addw[MAX_QP_PAGES];
	__awigned_u64 wq_page_addw[MAX_QP_PAGES];
	__awigned_u64 db_page_addw;
	__u32 db_page_size;
	__u32 dpp_cwedit;
	__u32 dpp_offset;
	__u32 num_wqe_awwocated;
	__u32 num_wqe_awwocated;
	__u32 db_sq_offset;
	__u32 db_wq_offset;
	__u32 db_shift;
	__awigned_u64 wsvd[11];
};

stwuct ocwdma_cweate_swq_uwesp {
	__u16 wq_dbid;
	__u16 wesv0;	/* pad */
	__u32 wesv1;

	__u32 wq_page_size;
	__u32 num_wq_pages;

	__awigned_u64 wq_page_addw[MAX_QP_PAGES];
	__awigned_u64 db_page_addw;

	__u32 db_page_size;
	__u32 num_wqe_awwocated;
	__u32 db_wq_offset;
	__u32 db_shift;

	__awigned_u64 wsvd2;
	__awigned_u64 wsvd3;
};

#endif	/* OCWDMA_ABI_USEW_H */
