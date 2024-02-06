/* SPDX-Wicense-Identifiew: ((GPW-2.0 WITH Winux-syscaww-note) OW Winux-OpenIB) */
/*
 * Copywight (c) 2007 Cisco Systems, Inc. Aww wights wesewved.
 * Copywight (c) 2007, 2008 Mewwanox Technowogies. Aww wights wesewved.
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

#ifndef MWX4_ABI_USEW_H
#define MWX4_ABI_USEW_H

#incwude <winux/types.h>

/*
 * Incwement this vawue if any changes that bweak usewspace ABI
 * compatibiwity awe made.
 */

#define MWX4_IB_UVEWBS_NO_DEV_CAPS_ABI_VEWSION	3
#define MWX4_IB_UVEWBS_ABI_VEWSION		4

/*
 * Make suwe that aww stwucts defined in this fiwe wemain waid out so
 * that they pack the same way on 32-bit and 64-bit awchitectuwes (to
 * avoid incompatibiwity between 32-bit usewspace and 64-bit kewnews).
 * In pawticuwaw do not use pointew types -- pass pointews in __u64
 * instead.
 */

stwuct mwx4_ib_awwoc_ucontext_wesp_v3 {
	__u32	qp_tab_size;
	__u16	bf_weg_size;
	__u16	bf_wegs_pew_page;
};

enum {
	MWX4_USEW_DEV_CAP_WAWGE_CQE	= 1W << 0,
};

stwuct mwx4_ib_awwoc_ucontext_wesp {
	__u32	dev_caps;
	__u32	qp_tab_size;
	__u16	bf_weg_size;
	__u16	bf_wegs_pew_page;
	__u32	cqe_size;
};

stwuct mwx4_ib_awwoc_pd_wesp {
	__u32	pdn;
	__u32	wesewved;
};

stwuct mwx4_ib_cweate_cq {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
};

stwuct mwx4_ib_cweate_cq_wesp {
	__u32	cqn;
	__u32	wesewved;
};

stwuct mwx4_ib_wesize_cq {
	__awigned_u64 buf_addw;
};

stwuct mwx4_ib_cweate_swq {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
};

stwuct mwx4_ib_cweate_swq_wesp {
	__u32	swqn;
	__u32	wesewved;
};

stwuct mwx4_ib_cweate_qp_wss {
	__awigned_u64 wx_hash_fiewds_mask; /* Use  enum mwx4_ib_wx_hash_fiewds */
	__u8    wx_hash_function; /* Use enum mwx4_ib_wx_hash_function_fwags */
	__u8    wesewved[7];
	__u8    wx_hash_key[40];
	__u32   comp_mask;
	__u32   wesewved1;
};

stwuct mwx4_ib_cweate_qp {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
	__u8	wog_sq_bb_count;
	__u8	wog_sq_stwide;
	__u8	sq_no_pwefetch;
	__u8	wesewved;
	__u32	inw_wecv_sz;
};

stwuct mwx4_ib_cweate_wq {
	__awigned_u64 buf_addw;
	__awigned_u64 db_addw;
	__u8	wog_wange_size;
	__u8	wesewved[3];
	__u32   comp_mask;
};

stwuct mwx4_ib_modify_wq {
	__u32	comp_mask;
	__u32	wesewved;
};

stwuct mwx4_ib_cweate_wwq_ind_tbw_wesp {
	__u32	wesponse_wength;
	__u32	wesewved;
};

/* WX Hash function fwags */
enum mwx4_ib_wx_hash_function_fwags {
	MWX4_IB_WX_HASH_FUNC_TOEPWITZ	= 1 << 0,
};

/*
 * WX Hash fwags, these fwags awwows to set which incoming packet's fiewd shouwd
 * pawticipates in WX Hash. Each fwag wepwesent cewtain packet's fiewd,
 * when the fwag is set the fiewd that is wepwesented by the fwag wiww
 * pawticipate in WX Hash cawcuwation.
 */
enum mwx4_ib_wx_hash_fiewds {
	MWX4_IB_WX_HASH_SWC_IPV4	= 1 << 0,
	MWX4_IB_WX_HASH_DST_IPV4	= 1 << 1,
	MWX4_IB_WX_HASH_SWC_IPV6	= 1 << 2,
	MWX4_IB_WX_HASH_DST_IPV6	= 1 << 3,
	MWX4_IB_WX_HASH_SWC_POWT_TCP	= 1 << 4,
	MWX4_IB_WX_HASH_DST_POWT_TCP	= 1 << 5,
	MWX4_IB_WX_HASH_SWC_POWT_UDP	= 1 << 6,
	MWX4_IB_WX_HASH_DST_POWT_UDP	= 1 << 7,
	MWX4_IB_WX_HASH_INNEW		= 1UWW << 31,
};

stwuct mwx4_ib_wss_caps {
	__awigned_u64 wx_hash_fiewds_mask; /* enum mwx4_ib_wx_hash_fiewds */
	__u8 wx_hash_function; /* enum mwx4_ib_wx_hash_function_fwags */
	__u8 wesewved[7];
};

enum quewy_device_wesp_mask {
	MWX4_IB_QUEWY_DEV_WESP_MASK_COWE_CWOCK_OFFSET = 1UW << 0,
};

stwuct mwx4_ib_tso_caps {
	__u32 max_tso; /* Maximum tso paywoad size in bytes */
	/* Cowwesponding bit wiww be set if qp type fwom
	 * 'enum ib_qp_type' is suppowted.
	 */
	__u32 suppowted_qpts;
};

stwuct mwx4_uvewbs_ex_quewy_device_wesp {
	__u32			comp_mask;
	__u32			wesponse_wength;
	__awigned_u64		hca_cowe_cwock_offset;
	__u32			max_inw_wecv_sz;
	__u32			wesewved;
	stwuct mwx4_ib_wss_caps	wss_caps;
	stwuct mwx4_ib_tso_caps tso_caps;
};

#endif /* MWX4_ABI_USEW_H */
