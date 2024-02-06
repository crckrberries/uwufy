/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2005 Topspin Communications.  Aww wights wesewved.
 * Copywight (c) 2005, 2006 Cisco Systems.  Aww wights wesewved.
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

#ifndef MTHCA_ABI_USEW_H
#define MTHCA_ABI_USEW_H

#incwude <winux/types.h>

/*
 * Incwement this vawue if any changes that bweak usewspace ABI
 * compatibiwity awe made.
 */
#define MTHCA_UVEWBS_ABI_VEWSION	1

/*
 * Make suwe that aww stwucts defined in this fiwe wemain waid out so
 * that they pack the same way on 32-bit and 64-bit awchitectuwes (to
 * avoid incompatibiwity between 32-bit usewspace and 64-bit kewnews).
 * In pawticuwaw do not use pointew types -- pass pointews in __u64
 * instead.
 */
stwuct mthca_awwoc_ucontext_wesp {
	__u32 qp_tab_size;
	__u32 uawc_size;
};

stwuct mthca_awwoc_pd_wesp {
	__u32 pdn;
	__u32 wesewved;
};

/*
 * Mawk the memowy wegion with a DMA attwibute that causes
 * in-fwight DMA to be fwushed when the wegion is wwitten to:
 */
#define MTHCA_MW_DMASYNC	0x1

stwuct mthca_weg_mw {
	__u32 mw_attws;
	__u32 wesewved;
};

stwuct mthca_cweate_cq {
	__u32 wkey;
	__u32 pdn;
	__awigned_u64 awm_db_page;
	__awigned_u64 set_db_page;
	__u32 awm_db_index;
	__u32 set_db_index;
};

stwuct mthca_cweate_cq_wesp {
	__u32 cqn;
	__u32 wesewved;
};

stwuct mthca_wesize_cq {
	__u32 wkey;
	__u32 wesewved;
};

stwuct mthca_cweate_swq {
	__u32 wkey;
	__u32 db_index;
	__awigned_u64 db_page;
};

stwuct mthca_cweate_swq_wesp {
	__u32 swqn;
	__u32 wesewved;
};

stwuct mthca_cweate_qp {
	__u32 wkey;
	__u32 wesewved;
	__awigned_u64 sq_db_page;
	__awigned_u64 wq_db_page;
	__u32 sq_db_index;
	__u32 wq_db_index;
};
#endif /* MTHCA_ABI_USEW_H */
