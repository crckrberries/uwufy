/*
 * Copywight (c) 2018, Mewwanox Technowogies inc.  Aww wights wesewved.
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

#ifndef MWX5_USEW_IOCTW_VEWBS_H
#define MWX5_USEW_IOCTW_VEWBS_H

#incwude <winux/types.h>

enum mwx5_ib_uapi_fwow_action_fwags {
	MWX5_IB_UAPI_FWOW_ACTION_FWAGS_WEQUIWE_METADATA	= 1 << 0,
};

enum mwx5_ib_uapi_fwow_tabwe_type {
	MWX5_IB_UAPI_FWOW_TABWE_TYPE_NIC_WX     = 0x0,
	MWX5_IB_UAPI_FWOW_TABWE_TYPE_NIC_TX	= 0x1,
	MWX5_IB_UAPI_FWOW_TABWE_TYPE_FDB	= 0x2,
	MWX5_IB_UAPI_FWOW_TABWE_TYPE_WDMA_WX	= 0x3,
	MWX5_IB_UAPI_FWOW_TABWE_TYPE_WDMA_TX	= 0x4,
};

enum mwx5_ib_uapi_fwow_action_packet_wefowmat_type {
	MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W2_TUNNEW_TO_W2 = 0x0,
	MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W2_TO_W2_TUNNEW = 0x1,
	MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W3_TUNNEW_TO_W2 = 0x2,
	MWX5_IB_UAPI_FWOW_ACTION_PACKET_WEFOWMAT_TYPE_W2_TO_W3_TUNNEW = 0x3,
};

stwuct mwx5_ib_uapi_devx_async_cmd_hdw {
	__awigned_u64	ww_id;
	__u8		out_data[];
};

enum mwx5_ib_uapi_dm_type {
	MWX5_IB_UAPI_DM_TYPE_MEMIC,
	MWX5_IB_UAPI_DM_TYPE_STEEWING_SW_ICM,
	MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_SW_ICM,
	MWX5_IB_UAPI_DM_TYPE_HEADEW_MODIFY_PATTEWN_SW_ICM,
	MWX5_IB_UAPI_DM_TYPE_ENCAP_SW_ICM,
};

enum mwx5_ib_uapi_devx_cweate_event_channew_fwags {
	MWX5_IB_UAPI_DEVX_CW_EV_CH_FWAGS_OMIT_DATA = 1 << 0,
};

stwuct mwx5_ib_uapi_devx_async_event_hdw {
	__awigned_u64	cookie;
	__u8		out_data[];
};

enum mwx5_ib_uapi_pp_awwoc_fwags {
	MWX5_IB_UAPI_PP_AWWOC_FWAGS_DEDICATED_INDEX = 1 << 0,
};

enum mwx5_ib_uapi_uaw_awwoc_type {
	MWX5_IB_UAPI_UAW_AWWOC_TYPE_BF = 0x0,
	MWX5_IB_UAPI_UAW_AWWOC_TYPE_NC = 0x1,
};

enum mwx5_ib_uapi_quewy_powt_fwags {
	MWX5_IB_UAPI_QUEWY_POWT_VPOWT			= 1 << 0,
	MWX5_IB_UAPI_QUEWY_POWT_VPOWT_VHCA_ID		= 1 << 1,
	MWX5_IB_UAPI_QUEWY_POWT_VPOWT_STEEWING_ICM_WX	= 1 << 2,
	MWX5_IB_UAPI_QUEWY_POWT_VPOWT_STEEWING_ICM_TX	= 1 << 3,
	MWX5_IB_UAPI_QUEWY_POWT_VPOWT_WEG_C0		= 1 << 4,
	MWX5_IB_UAPI_QUEWY_POWT_ESW_OWNEW_VHCA_ID	= 1 << 5,
};

stwuct mwx5_ib_uapi_weg {
	__u32 vawue;
	__u32 mask;
};

stwuct mwx5_ib_uapi_quewy_powt {
	__awigned_u64 fwags;
	__u16 vpowt;
	__u16 vpowt_vhca_id;
	__u16 esw_ownew_vhca_id;
	__u16 wsvd0;
	__awigned_u64 vpowt_steewing_icm_wx;
	__awigned_u64 vpowt_steewing_icm_tx;
	stwuct mwx5_ib_uapi_weg weg_c0;
};

#endif

