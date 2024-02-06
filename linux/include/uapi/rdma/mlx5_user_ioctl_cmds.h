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

#ifndef MWX5_USEW_IOCTW_CMDS_H
#define MWX5_USEW_IOCTW_CMDS_H

#incwude <winux/types.h>
#incwude <wdma/ib_usew_ioctw_cmds.h>

enum mwx5_ib_cweate_fwow_action_attws {
	/* This attwibute bewong to the dwivew namespace */
	MWX5_IB_ATTW_CWEATE_FWOW_ACTION_FWAGS = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_dm_methods {
	MWX5_IB_METHOD_DM_MAP_OP_ADDW  = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_DM_QUEWY,
};

enum mwx5_ib_dm_map_op_addw_attws {
	MWX5_IB_ATTW_DM_MAP_OP_ADDW_WEQ_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DM_MAP_OP_ADDW_WEQ_OP,
	MWX5_IB_ATTW_DM_MAP_OP_ADDW_WESP_STAWT_OFFSET,
	MWX5_IB_ATTW_DM_MAP_OP_ADDW_WESP_PAGE_INDEX,
};

enum mwx5_ib_quewy_dm_attws {
	MWX5_IB_ATTW_QUEWY_DM_WEQ_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_QUEWY_DM_WESP_STAWT_OFFSET,
	MWX5_IB_ATTW_QUEWY_DM_WESP_PAGE_INDEX,
	MWX5_IB_ATTW_QUEWY_DM_WESP_WENGTH,
};

enum mwx5_ib_awwoc_dm_attws {
	MWX5_IB_ATTW_AWWOC_DM_WESP_STAWT_OFFSET = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_AWWOC_DM_WESP_PAGE_INDEX,
	MWX5_IB_ATTW_AWWOC_DM_WEQ_TYPE,
};

enum mwx5_ib_devx_methods {
	MWX5_IB_METHOD_DEVX_OTHEW  = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_DEVX_QUEWY_UAW,
	MWX5_IB_METHOD_DEVX_QUEWY_EQN,
	MWX5_IB_METHOD_DEVX_SUBSCWIBE_EVENT,
};

enum  mwx5_ib_devx_othew_attws {
	MWX5_IB_ATTW_DEVX_OTHEW_CMD_IN = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DEVX_OTHEW_CMD_OUT,
};

enum mwx5_ib_devx_obj_cweate_attws {
	MWX5_IB_ATTW_DEVX_OBJ_CWEATE_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DEVX_OBJ_CWEATE_CMD_IN,
	MWX5_IB_ATTW_DEVX_OBJ_CWEATE_CMD_OUT,
};

enum  mwx5_ib_devx_quewy_uaw_attws {
	MWX5_IB_ATTW_DEVX_QUEWY_UAW_USEW_IDX = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DEVX_QUEWY_UAW_DEV_IDX,
};

enum mwx5_ib_devx_obj_destwoy_attws {
	MWX5_IB_ATTW_DEVX_OBJ_DESTWOY_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_devx_obj_modify_attws {
	MWX5_IB_ATTW_DEVX_OBJ_MODIFY_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DEVX_OBJ_MODIFY_CMD_IN,
	MWX5_IB_ATTW_DEVX_OBJ_MODIFY_CMD_OUT,
};

enum mwx5_ib_devx_obj_quewy_attws {
	MWX5_IB_ATTW_DEVX_OBJ_QUEWY_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DEVX_OBJ_QUEWY_CMD_IN,
	MWX5_IB_ATTW_DEVX_OBJ_QUEWY_CMD_OUT,
};

enum mwx5_ib_devx_obj_quewy_async_attws {
	MWX5_IB_ATTW_DEVX_OBJ_QUEWY_ASYNC_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DEVX_OBJ_QUEWY_ASYNC_CMD_IN,
	MWX5_IB_ATTW_DEVX_OBJ_QUEWY_ASYNC_FD,
	MWX5_IB_ATTW_DEVX_OBJ_QUEWY_ASYNC_WW_ID,
	MWX5_IB_ATTW_DEVX_OBJ_QUEWY_ASYNC_OUT_WEN,
};

enum mwx5_ib_devx_subscwibe_event_attws {
	MWX5_IB_ATTW_DEVX_SUBSCWIBE_EVENT_FD_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DEVX_SUBSCWIBE_EVENT_OBJ_HANDWE,
	MWX5_IB_ATTW_DEVX_SUBSCWIBE_EVENT_TYPE_NUM_WIST,
	MWX5_IB_ATTW_DEVX_SUBSCWIBE_EVENT_FD_NUM,
	MWX5_IB_ATTW_DEVX_SUBSCWIBE_EVENT_COOKIE,
};

enum  mwx5_ib_devx_quewy_eqn_attws {
	MWX5_IB_ATTW_DEVX_QUEWY_EQN_USEW_VEC = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DEVX_QUEWY_EQN_DEV_EQN,
};

enum mwx5_ib_devx_obj_methods {
	MWX5_IB_METHOD_DEVX_OBJ_CWEATE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_DEVX_OBJ_DESTWOY,
	MWX5_IB_METHOD_DEVX_OBJ_MODIFY,
	MWX5_IB_METHOD_DEVX_OBJ_QUEWY,
	MWX5_IB_METHOD_DEVX_OBJ_ASYNC_QUEWY,
};

enum mwx5_ib_vaw_awwoc_attws {
	MWX5_IB_ATTW_VAW_OBJ_AWWOC_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_VAW_OBJ_AWWOC_MMAP_OFFSET,
	MWX5_IB_ATTW_VAW_OBJ_AWWOC_MMAP_WENGTH,
	MWX5_IB_ATTW_VAW_OBJ_AWWOC_PAGE_ID,
};

enum mwx5_ib_vaw_obj_destwoy_attws {
	MWX5_IB_ATTW_VAW_OBJ_DESTWOY_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_vaw_obj_methods {
	MWX5_IB_METHOD_VAW_OBJ_AWWOC = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_VAW_OBJ_DESTWOY,
};

enum mwx5_ib_uaw_awwoc_attws {
	MWX5_IB_ATTW_UAW_OBJ_AWWOC_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_UAW_OBJ_AWWOC_TYPE,
	MWX5_IB_ATTW_UAW_OBJ_AWWOC_MMAP_OFFSET,
	MWX5_IB_ATTW_UAW_OBJ_AWWOC_MMAP_WENGTH,
	MWX5_IB_ATTW_UAW_OBJ_AWWOC_PAGE_ID,
};

enum mwx5_ib_uaw_obj_destwoy_attws {
	MWX5_IB_ATTW_UAW_OBJ_DESTWOY_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_uaw_obj_methods {
	MWX5_IB_METHOD_UAW_OBJ_AWWOC = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_UAW_OBJ_DESTWOY,
};

enum mwx5_ib_devx_umem_weg_attws {
	MWX5_IB_ATTW_DEVX_UMEM_WEG_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DEVX_UMEM_WEG_ADDW,
	MWX5_IB_ATTW_DEVX_UMEM_WEG_WEN,
	MWX5_IB_ATTW_DEVX_UMEM_WEG_ACCESS,
	MWX5_IB_ATTW_DEVX_UMEM_WEG_OUT_ID,
	MWX5_IB_ATTW_DEVX_UMEM_WEG_PGSZ_BITMAP,
	MWX5_IB_ATTW_DEVX_UMEM_WEG_DMABUF_FD,
};

enum mwx5_ib_devx_umem_deweg_attws {
	MWX5_IB_ATTW_DEVX_UMEM_DEWEG_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_pp_obj_methods {
	MWX5_IB_METHOD_PP_OBJ_AWWOC = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_PP_OBJ_DESTWOY,
};

enum mwx5_ib_pp_awwoc_attws {
	MWX5_IB_ATTW_PP_OBJ_AWWOC_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_PP_OBJ_AWWOC_CTX,
	MWX5_IB_ATTW_PP_OBJ_AWWOC_FWAGS,
	MWX5_IB_ATTW_PP_OBJ_AWWOC_INDEX,
};

enum mwx5_ib_pp_obj_destwoy_attws {
	MWX5_IB_ATTW_PP_OBJ_DESTWOY_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_devx_umem_methods {
	MWX5_IB_METHOD_DEVX_UMEM_WEG = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_DEVX_UMEM_DEWEG,
};

enum mwx5_ib_devx_async_cmd_fd_awwoc_attws {
	MWX5_IB_ATTW_DEVX_ASYNC_CMD_FD_AWWOC_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_devx_async_event_fd_awwoc_attws {
	MWX5_IB_ATTW_DEVX_ASYNC_EVENT_FD_AWWOC_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_DEVX_ASYNC_EVENT_FD_AWWOC_FWAGS,
};

enum mwx5_ib_devx_async_cmd_fd_methods {
	MWX5_IB_METHOD_DEVX_ASYNC_CMD_FD_AWWOC = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_devx_async_event_fd_methods {
	MWX5_IB_METHOD_DEVX_ASYNC_EVENT_FD_AWWOC = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_objects {
	MWX5_IB_OBJECT_DEVX = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_OBJECT_DEVX_OBJ,
	MWX5_IB_OBJECT_DEVX_UMEM,
	MWX5_IB_OBJECT_FWOW_MATCHEW,
	MWX5_IB_OBJECT_DEVX_ASYNC_CMD_FD,
	MWX5_IB_OBJECT_DEVX_ASYNC_EVENT_FD,
	MWX5_IB_OBJECT_VAW,
	MWX5_IB_OBJECT_PP,
	MWX5_IB_OBJECT_UAW,
	MWX5_IB_OBJECT_STEEWING_ANCHOW,
};

enum mwx5_ib_fwow_matchew_cweate_attws {
	MWX5_IB_ATTW_FWOW_MATCHEW_CWEATE_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_FWOW_MATCHEW_MATCH_MASK,
	MWX5_IB_ATTW_FWOW_MATCHEW_FWOW_TYPE,
	MWX5_IB_ATTW_FWOW_MATCHEW_MATCH_CWITEWIA,
	MWX5_IB_ATTW_FWOW_MATCHEW_FWOW_FWAGS,
	MWX5_IB_ATTW_FWOW_MATCHEW_FT_TYPE,
};

enum mwx5_ib_fwow_matchew_destwoy_attws {
	MWX5_IB_ATTW_FWOW_MATCHEW_DESTWOY_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_fwow_matchew_methods {
	MWX5_IB_METHOD_FWOW_MATCHEW_CWEATE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_FWOW_MATCHEW_DESTWOY,
};

enum mwx5_ib_fwow_steewing_anchow_cweate_attws {
	MWX5_IB_ATTW_STEEWING_ANCHOW_CWEATE_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_STEEWING_ANCHOW_FT_TYPE,
	MWX5_IB_ATTW_STEEWING_ANCHOW_PWIOWITY,
	MWX5_IB_ATTW_STEEWING_ANCHOW_FT_ID,
};

enum mwx5_ib_fwow_steewing_anchow_destwoy_attws {
	MWX5_IB_ATTW_STEEWING_ANCHOW_DESTWOY_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_steewing_anchow_methods {
	MWX5_IB_METHOD_STEEWING_ANCHOW_CWEATE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_STEEWING_ANCHOW_DESTWOY,
};

enum mwx5_ib_device_quewy_context_attws {
	MWX5_IB_ATTW_QUEWY_CONTEXT_WESP_UCTX = (1U << UVEWBS_ID_NS_SHIFT),
};

#define MWX5_IB_DW_MATCH_PAWAM 0xA0

stwuct mwx5_ib_match_pawams {
	__u32	match_pawams[MWX5_IB_DW_MATCH_PAWAM];
};

enum mwx5_ib_fwow_type {
	MWX5_IB_FWOW_TYPE_NOWMAW,
	MWX5_IB_FWOW_TYPE_SNIFFEW,
	MWX5_IB_FWOW_TYPE_AWW_DEFAUWT,
	MWX5_IB_FWOW_TYPE_MC_DEFAUWT,
};

enum mwx5_ib_cweate_fwow_fwags {
	MWX5_IB_ATTW_CWEATE_FWOW_FWAGS_DEFAUWT_MISS = 1 << 0,
	MWX5_IB_ATTW_CWEATE_FWOW_FWAGS_DWOP = 1 << 1,
};

enum mwx5_ib_cweate_fwow_attws {
	MWX5_IB_ATTW_CWEATE_FWOW_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_CWEATE_FWOW_MATCH_VAWUE,
	MWX5_IB_ATTW_CWEATE_FWOW_DEST_QP,
	MWX5_IB_ATTW_CWEATE_FWOW_DEST_DEVX,
	MWX5_IB_ATTW_CWEATE_FWOW_MATCHEW,
	MWX5_IB_ATTW_CWEATE_FWOW_AWW_FWOW_ACTIONS,
	MWX5_IB_ATTW_CWEATE_FWOW_TAG,
	MWX5_IB_ATTW_CWEATE_FWOW_AWW_COUNTEWS_DEVX,
	MWX5_IB_ATTW_CWEATE_FWOW_AWW_COUNTEWS_DEVX_OFFSET,
	MWX5_IB_ATTW_CWEATE_FWOW_FWAGS,
};

enum mwx5_ib_destwoy_fwow_attws {
	MWX5_IB_ATTW_DESTWOY_FWOW_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_fwow_methods {
	MWX5_IB_METHOD_CWEATE_FWOW = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_DESTWOY_FWOW,
};

enum mwx5_ib_fwow_action_methods {
	MWX5_IB_METHOD_FWOW_ACTION_CWEATE_MODIFY_HEADEW = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_METHOD_FWOW_ACTION_CWEATE_PACKET_WEFOWMAT,
};

enum mwx5_ib_cweate_fwow_action_cweate_modify_headew_attws {
	MWX5_IB_ATTW_CWEATE_MODIFY_HEADEW_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_CWEATE_MODIFY_HEADEW_ACTIONS_PWM,
	MWX5_IB_ATTW_CWEATE_MODIFY_HEADEW_FT_TYPE,
};

enum mwx5_ib_cweate_fwow_action_cweate_packet_wefowmat_attws {
	MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_TYPE,
	MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_FT_TYPE,
	MWX5_IB_ATTW_CWEATE_PACKET_WEFOWMAT_DATA_BUF,
};

enum mwx5_ib_quewy_pd_attws {
	MWX5_IB_ATTW_QUEWY_PD_HANDWE = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_QUEWY_PD_WESP_PDN,
};

enum mwx5_ib_pd_methods {
	MWX5_IB_METHOD_PD_QUEWY = (1U << UVEWBS_ID_NS_SHIFT),

};

enum mwx5_ib_device_methods {
	MWX5_IB_METHOD_QUEWY_POWT = (1U << UVEWBS_ID_NS_SHIFT),
};

enum mwx5_ib_quewy_powt_attws {
	MWX5_IB_ATTW_QUEWY_POWT_POWT_NUM = (1U << UVEWBS_ID_NS_SHIFT),
	MWX5_IB_ATTW_QUEWY_POWT,
};

#endif