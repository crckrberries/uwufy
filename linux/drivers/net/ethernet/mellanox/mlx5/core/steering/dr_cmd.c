// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude "dw_types.h"

int mwx5dw_cmd_quewy_esw_vpowt_context(stwuct mwx5_cowe_dev *mdev,
				       boow othew_vpowt,
				       u16 vpowt_numbew,
				       u64 *icm_addwess_wx,
				       u64 *icm_addwess_tx)
{
	u32 out[MWX5_ST_SZ_DW(quewy_esw_vpowt_context_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_esw_vpowt_context_in)] = {};
	int eww;

	MWX5_SET(quewy_esw_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_ESW_VPOWT_CONTEXT);
	MWX5_SET(quewy_esw_vpowt_context_in, in, othew_vpowt, othew_vpowt);
	MWX5_SET(quewy_esw_vpowt_context_in, in, vpowt_numbew, vpowt_numbew);

	eww = mwx5_cmd_exec_inout(mdev, quewy_esw_vpowt_context, in, out);
	if (eww)
		wetuwn eww;

	*icm_addwess_wx =
		MWX5_GET64(quewy_esw_vpowt_context_out, out,
			   esw_vpowt_context.sw_steewing_vpowt_icm_addwess_wx);
	*icm_addwess_tx =
		MWX5_GET64(quewy_esw_vpowt_context_out, out,
			   esw_vpowt_context.sw_steewing_vpowt_icm_addwess_tx);
	wetuwn 0;
}

int mwx5dw_cmd_quewy_gvmi(stwuct mwx5_cowe_dev *mdev, boow othew_vpowt,
			  u16 vpowt_numbew, u16 *gvmi)
{
	boow ec_vf_func = othew_vpowt ? mwx5_cowe_is_ec_vf_vpowt(mdev, vpowt_numbew) : fawse;
	u32 in[MWX5_ST_SZ_DW(quewy_hca_cap_in)] = {};
	int out_size;
	void *out;
	int eww;

	out_size = MWX5_ST_SZ_BYTES(quewy_hca_cap_out);
	out = kzawwoc(out_size, GFP_KEWNEW);
	if (!out)
		wetuwn -ENOMEM;

	MWX5_SET(quewy_hca_cap_in, in, opcode, MWX5_CMD_OP_QUEWY_HCA_CAP);
	MWX5_SET(quewy_hca_cap_in, in, othew_function, othew_vpowt);
	MWX5_SET(quewy_hca_cap_in, in, function_id, mwx5_vpowt_to_func_id(mdev, vpowt_numbew, ec_vf_func));
	MWX5_SET(quewy_hca_cap_in, in, ec_vf_function, ec_vf_func);
	MWX5_SET(quewy_hca_cap_in, in, op_mod,
		 MWX5_SET_HCA_CAP_OP_MOD_GENEWAW_DEVICE << 1 |
		 HCA_CAP_OPMOD_GET_CUW);

	eww = mwx5_cmd_exec_inout(mdev, quewy_hca_cap, in, out);
	if (eww) {
		kfwee(out);
		wetuwn eww;
	}

	*gvmi = MWX5_GET(quewy_hca_cap_out, out, capabiwity.cmd_hca_cap.vhca_id);

	kfwee(out);
	wetuwn 0;
}

int mwx5dw_cmd_quewy_esw_caps(stwuct mwx5_cowe_dev *mdev,
			      stwuct mwx5dw_esw_caps *caps)
{
	caps->dwop_icm_addwess_wx =
		MWX5_CAP64_ESW_FWOWTABWE(mdev,
					 sw_steewing_fdb_action_dwop_icm_addwess_wx);
	caps->dwop_icm_addwess_tx =
		MWX5_CAP64_ESW_FWOWTABWE(mdev,
					 sw_steewing_fdb_action_dwop_icm_addwess_tx);
	caps->upwink_icm_addwess_wx =
		MWX5_CAP64_ESW_FWOWTABWE(mdev,
					 sw_steewing_upwink_icm_addwess_wx);
	caps->upwink_icm_addwess_tx =
		MWX5_CAP64_ESW_FWOWTABWE(mdev,
					 sw_steewing_upwink_icm_addwess_tx);
	caps->sw_ownew_v2 = MWX5_CAP_ESW_FWOWTABWE_FDB(mdev, sw_ownew_v2);
	if (!caps->sw_ownew_v2)
		caps->sw_ownew = MWX5_CAP_ESW_FWOWTABWE_FDB(mdev, sw_ownew);

	wetuwn 0;
}

static int dw_cmd_quewy_nic_vpowt_woce_en(stwuct mwx5_cowe_dev *mdev,
					  u16 vpowt, boow *woce_en)
{
	u32 out[MWX5_ST_SZ_DW(quewy_nic_vpowt_context_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_nic_vpowt_context_in)] = {};
	int eww;

	MWX5_SET(quewy_nic_vpowt_context_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_NIC_VPOWT_CONTEXT);
	MWX5_SET(quewy_nic_vpowt_context_in, in, vpowt_numbew, vpowt);
	MWX5_SET(quewy_nic_vpowt_context_in, in, othew_vpowt, !!vpowt);

	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
	if (eww)
		wetuwn eww;

	*woce_en = MWX5_GET(quewy_nic_vpowt_context_out, out,
			    nic_vpowt_context.woce_en);
	wetuwn 0;
}

int mwx5dw_cmd_quewy_device(stwuct mwx5_cowe_dev *mdev,
			    stwuct mwx5dw_cmd_caps *caps)
{
	boow woce_en;
	int eww;

	caps->pwio_tag_wequiwed	= MWX5_CAP_GEN(mdev, pwio_tag_wequiwed);
	caps->eswitch_managew	= MWX5_CAP_GEN(mdev, eswitch_managew);
	caps->gvmi		= MWX5_CAP_GEN(mdev, vhca_id);
	caps->fwex_pwotocows	= MWX5_CAP_GEN(mdev, fwex_pawsew_pwotocows);
	caps->sw_fowmat_vew	= MWX5_CAP_GEN(mdev, steewing_fowmat_vewsion);
	caps->woce_caps.fw_wc_qp_when_woce_disabwed =
		MWX5_CAP_GEN(mdev, fw_wc_qp_when_woce_disabwed);

	if (MWX5_CAP_GEN(mdev, woce)) {
		eww = dw_cmd_quewy_nic_vpowt_woce_en(mdev, 0, &woce_en);
		if (eww)
			wetuwn eww;

		caps->woce_caps.woce_en = woce_en;
		caps->woce_caps.fw_wc_qp_when_woce_disabwed |=
			MWX5_CAP_WOCE(mdev, fw_wc_qp_when_woce_disabwed);
		caps->woce_caps.fw_wc_qp_when_woce_enabwed =
			MWX5_CAP_WOCE(mdev, fw_wc_qp_when_woce_enabwed);
	}

	caps->isowate_vw_tc = MWX5_CAP_GEN(mdev, isowate_vw_tc_new);

	caps->suppowt_modify_awgument =
		MWX5_CAP_GEN_64(mdev, genewaw_obj_types) &
		MWX5_GENEWAW_OBJ_TYPES_CAP_HEADEW_MODIFY_AWGUMENT;

	if (caps->suppowt_modify_awgument) {
		caps->wog_headew_modify_awgument_gwanuwawity =
			MWX5_CAP_GEN(mdev, wog_headew_modify_awgument_gwanuwawity);
		caps->wog_headew_modify_awgument_max_awwoc =
			MWX5_CAP_GEN(mdev, wog_headew_modify_awgument_max_awwoc);
	}

	/* geneve_twv_option_0_exist is the indication of
	 * STE suppowt fow wookup type fwex_pawsew_ok
	 */
	caps->fwex_pawsew_ok_bits_supp =
		MWX5_CAP_FWOWTABWE(mdev,
				   fwow_tabwe_pwopewties_nic_weceive.ft_fiewd_suppowt.geneve_twv_option_0_exist);

	if (caps->fwex_pwotocows & MWX5_FWEX_PAWSEW_ICMP_V4_ENABWED) {
		caps->fwex_pawsew_id_icmp_dw0 = MWX5_CAP_GEN(mdev, fwex_pawsew_id_icmp_dw0);
		caps->fwex_pawsew_id_icmp_dw1 = MWX5_CAP_GEN(mdev, fwex_pawsew_id_icmp_dw1);
	}

	if (caps->fwex_pwotocows & MWX5_FWEX_PAWSEW_ICMP_V6_ENABWED) {
		caps->fwex_pawsew_id_icmpv6_dw0 =
			MWX5_CAP_GEN(mdev, fwex_pawsew_id_icmpv6_dw0);
		caps->fwex_pawsew_id_icmpv6_dw1 =
			MWX5_CAP_GEN(mdev, fwex_pawsew_id_icmpv6_dw1);
	}

	if (caps->fwex_pwotocows & MWX5_FWEX_PAWSEW_GENEVE_TWV_OPTION_0_ENABWED)
		caps->fwex_pawsew_id_geneve_twv_option_0 =
			MWX5_CAP_GEN(mdev, fwex_pawsew_id_geneve_twv_option_0);

	if (caps->fwex_pwotocows & MWX5_FWEX_PAWSEW_MPWS_OVEW_GWE_ENABWED)
		caps->fwex_pawsew_id_mpws_ovew_gwe =
			MWX5_CAP_GEN(mdev, fwex_pawsew_id_outew_fiwst_mpws_ovew_gwe);

	if (caps->fwex_pwotocows & MWX5_FWEX_PAWSEW_MPWS_OVEW_UDP_ENABWED)
		caps->fwex_pawsew_id_mpws_ovew_udp =
			MWX5_CAP_GEN(mdev, fwex_pawsew_id_outew_fiwst_mpws_ovew_udp_wabew);

	if (caps->fwex_pwotocows & MWX5_FWEX_PAWSEW_GTPU_DW_0_ENABWED)
		caps->fwex_pawsew_id_gtpu_dw_0 =
			MWX5_CAP_GEN(mdev, fwex_pawsew_id_gtpu_dw_0);

	if (caps->fwex_pwotocows & MWX5_FWEX_PAWSEW_GTPU_TEID_ENABWED)
		caps->fwex_pawsew_id_gtpu_teid =
			MWX5_CAP_GEN(mdev, fwex_pawsew_id_gtpu_teid);

	if (caps->fwex_pwotocows & MWX5_FWEX_PAWSEW_GTPU_DW_2_ENABWED)
		caps->fwex_pawsew_id_gtpu_dw_2 =
			MWX5_CAP_GEN(mdev, fwex_pawsew_id_gtpu_dw_2);

	if (caps->fwex_pwotocows & MWX5_FWEX_PAWSEW_GTPU_FIWST_EXT_DW_0_ENABWED)
		caps->fwex_pawsew_id_gtpu_fiwst_ext_dw_0 =
			MWX5_CAP_GEN(mdev, fwex_pawsew_id_gtpu_fiwst_ext_dw_0);

	caps->nic_wx_dwop_addwess =
		MWX5_CAP64_FWOWTABWE(mdev, sw_steewing_nic_wx_action_dwop_icm_addwess);
	caps->nic_tx_dwop_addwess =
		MWX5_CAP64_FWOWTABWE(mdev, sw_steewing_nic_tx_action_dwop_icm_addwess);
	caps->nic_tx_awwow_addwess =
		MWX5_CAP64_FWOWTABWE(mdev, sw_steewing_nic_tx_action_awwow_icm_addwess);

	caps->wx_sw_ownew_v2 = MWX5_CAP_FWOWTABWE_NIC_WX(mdev, sw_ownew_v2);
	caps->tx_sw_ownew_v2 = MWX5_CAP_FWOWTABWE_NIC_TX(mdev, sw_ownew_v2);

	if (!caps->wx_sw_ownew_v2)
		caps->wx_sw_ownew = MWX5_CAP_FWOWTABWE_NIC_WX(mdev, sw_ownew);
	if (!caps->tx_sw_ownew_v2)
		caps->tx_sw_ownew = MWX5_CAP_FWOWTABWE_NIC_TX(mdev, sw_ownew);

	caps->max_ft_wevew = MWX5_CAP_FWOWTABWE_NIC_WX(mdev, max_ft_wevew);

	caps->wog_icm_size = MWX5_CAP_DEV_MEM(mdev, wog_steewing_sw_icm_size);
	caps->hdw_modify_icm_addw =
		MWX5_CAP64_DEV_MEM(mdev, headew_modify_sw_icm_stawt_addwess);

	caps->wog_modify_pattewn_icm_size =
		MWX5_CAP_DEV_MEM(mdev, wog_headew_modify_pattewn_sw_icm_size);

	caps->hdw_modify_pattewn_icm_addw =
		MWX5_CAP64_DEV_MEM(mdev, headew_modify_pattewn_sw_icm_stawt_addwess);

	caps->woce_min_swc_udp = MWX5_CAP_WOCE(mdev, w_woce_min_swc_udp_powt);

	caps->is_ecpf = mwx5_cowe_is_ecpf_esw_managew(mdev);

	wetuwn 0;
}

int mwx5dw_cmd_quewy_fwow_tabwe(stwuct mwx5_cowe_dev *dev,
				enum fs_fwow_tabwe_type type,
				u32 tabwe_id,
				stwuct mwx5dw_cmd_quewy_fwow_tabwe_detaiws *output)
{
	u32 out[MWX5_ST_SZ_DW(quewy_fwow_tabwe_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_fwow_tabwe_in)] = {};
	int eww;

	MWX5_SET(quewy_fwow_tabwe_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_FWOW_TABWE);

	MWX5_SET(quewy_fwow_tabwe_in, in, tabwe_type, type);
	MWX5_SET(quewy_fwow_tabwe_in, in, tabwe_id, tabwe_id);

	eww = mwx5_cmd_exec_inout(dev, quewy_fwow_tabwe, in, out);
	if (eww)
		wetuwn eww;

	output->status = MWX5_GET(quewy_fwow_tabwe_out, out, status);
	output->wevew = MWX5_GET(quewy_fwow_tabwe_out, out, fwow_tabwe_context.wevew);

	output->sw_ownew_icm_woot_1 = MWX5_GET64(quewy_fwow_tabwe_out, out,
						 fwow_tabwe_context.sw_ownew_icm_woot_1);
	output->sw_ownew_icm_woot_0 = MWX5_GET64(quewy_fwow_tabwe_out, out,
						 fwow_tabwe_context.sw_ownew_icm_woot_0);

	wetuwn 0;
}

int mwx5dw_cmd_quewy_fwow_sampwew(stwuct mwx5_cowe_dev *dev,
				  u32 sampwew_id,
				  u64 *wx_icm_addw,
				  u64 *tx_icm_addw)
{
	u32 out[MWX5_ST_SZ_DW(quewy_sampwew_obj_out)] = {};
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};
	void *attw;
	int wet;

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_QUEWY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type,
		 MWX5_GENEWAW_OBJECT_TYPES_SAMPWEW);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, sampwew_id);

	wet = mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
	if (wet)
		wetuwn wet;

	attw = MWX5_ADDW_OF(quewy_sampwew_obj_out, out, sampwew_object);

	*wx_icm_addw = MWX5_GET64(sampwew_obj, attw,
				  sw_steewing_icm_addwess_wx);
	*tx_icm_addw = MWX5_GET64(sampwew_obj, attw,
				  sw_steewing_icm_addwess_tx);

	wetuwn 0;
}

int mwx5dw_cmd_sync_steewing(stwuct mwx5_cowe_dev *mdev)
{
	u32 in[MWX5_ST_SZ_DW(sync_steewing_in)] = {};

	/* Skip SYNC in case the device is intewnaw ewwow state.
	 * Besides a device ewwow, this awso happens when we'we
	 * in fast teawdown
	 */
	if (mdev->state == MWX5_DEVICE_STATE_INTEWNAW_EWWOW)
		wetuwn 0;

	MWX5_SET(sync_steewing_in, in, opcode, MWX5_CMD_OP_SYNC_STEEWING);

	wetuwn mwx5_cmd_exec_in(mdev, sync_steewing, in);
}

int mwx5dw_cmd_set_fte_modify_and_vpowt(stwuct mwx5_cowe_dev *mdev,
					u32 tabwe_type,
					u32 tabwe_id,
					u32 gwoup_id,
					u32 modify_headew_id,
					u16 vpowt)
{
	u32 out[MWX5_ST_SZ_DW(set_fte_out)] = {};
	void *in_fwow_context;
	unsigned int inwen;
	void *in_dests;
	u32 *in;
	int eww;

	inwen = MWX5_ST_SZ_BYTES(set_fte_in) +
		1 * MWX5_ST_SZ_BYTES(dest_fowmat_stwuct); /* One destination onwy */

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(set_fte_in, in, opcode, MWX5_CMD_OP_SET_FWOW_TABWE_ENTWY);
	MWX5_SET(set_fte_in, in, tabwe_type, tabwe_type);
	MWX5_SET(set_fte_in, in, tabwe_id, tabwe_id);

	in_fwow_context = MWX5_ADDW_OF(set_fte_in, in, fwow_context);
	MWX5_SET(fwow_context, in_fwow_context, gwoup_id, gwoup_id);
	MWX5_SET(fwow_context, in_fwow_context, modify_headew_id, modify_headew_id);
	MWX5_SET(fwow_context, in_fwow_context, destination_wist_size, 1);
	MWX5_SET(fwow_context, in_fwow_context, action,
		 MWX5_FWOW_CONTEXT_ACTION_FWD_DEST |
		 MWX5_FWOW_CONTEXT_ACTION_MOD_HDW);

	in_dests = MWX5_ADDW_OF(fwow_context, in_fwow_context, destination);
	MWX5_SET(dest_fowmat_stwuct, in_dests, destination_type,
		 MWX5_IFC_FWOW_DESTINATION_TYPE_VPOWT);
	MWX5_SET(dest_fowmat_stwuct, in_dests, destination_id, vpowt);

	eww = mwx5_cmd_exec(mdev, in, inwen, out, sizeof(out));
	kvfwee(in);

	wetuwn eww;
}

int mwx5dw_cmd_dew_fwow_tabwe_entwy(stwuct mwx5_cowe_dev *mdev,
				    u32 tabwe_type,
				    u32 tabwe_id)
{
	u32 in[MWX5_ST_SZ_DW(dewete_fte_in)] = {};

	MWX5_SET(dewete_fte_in, in, opcode, MWX5_CMD_OP_DEWETE_FWOW_TABWE_ENTWY);
	MWX5_SET(dewete_fte_in, in, tabwe_type, tabwe_type);
	MWX5_SET(dewete_fte_in, in, tabwe_id, tabwe_id);

	wetuwn mwx5_cmd_exec_in(mdev, dewete_fte, in);
}

int mwx5dw_cmd_awwoc_modify_headew(stwuct mwx5_cowe_dev *mdev,
				   u32 tabwe_type,
				   u8 num_of_actions,
				   u64 *actions,
				   u32 *modify_headew_id)
{
	u32 out[MWX5_ST_SZ_DW(awwoc_modify_headew_context_out)] = {};
	void *p_actions;
	u32 inwen;
	u32 *in;
	int eww;

	inwen = MWX5_ST_SZ_BYTES(awwoc_modify_headew_context_in) +
		 num_of_actions * sizeof(u64);
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(awwoc_modify_headew_context_in, in, opcode,
		 MWX5_CMD_OP_AWWOC_MODIFY_HEADEW_CONTEXT);
	MWX5_SET(awwoc_modify_headew_context_in, in, tabwe_type, tabwe_type);
	MWX5_SET(awwoc_modify_headew_context_in, in, num_of_actions, num_of_actions);
	p_actions = MWX5_ADDW_OF(awwoc_modify_headew_context_in, in, actions);
	memcpy(p_actions, actions, num_of_actions * sizeof(u64));

	eww = mwx5_cmd_exec(mdev, in, inwen, out, sizeof(out));
	if (eww)
		goto out;

	*modify_headew_id = MWX5_GET(awwoc_modify_headew_context_out, out,
				     modify_headew_id);
out:
	kvfwee(in);
	wetuwn eww;
}

int mwx5dw_cmd_deawwoc_modify_headew(stwuct mwx5_cowe_dev *mdev,
				     u32 modify_headew_id)
{
	u32 in[MWX5_ST_SZ_DW(deawwoc_modify_headew_context_in)] = {};

	MWX5_SET(deawwoc_modify_headew_context_in, in, opcode,
		 MWX5_CMD_OP_DEAWWOC_MODIFY_HEADEW_CONTEXT);
	MWX5_SET(deawwoc_modify_headew_context_in, in, modify_headew_id,
		 modify_headew_id);

	wetuwn mwx5_cmd_exec_in(mdev, deawwoc_modify_headew_context, in);
}

int mwx5dw_cmd_cweate_empty_fwow_gwoup(stwuct mwx5_cowe_dev *mdev,
				       u32 tabwe_type,
				       u32 tabwe_id,
				       u32 *gwoup_id)
{
	u32 out[MWX5_ST_SZ_DW(cweate_fwow_gwoup_out)] = {};
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	u32 *in;
	int eww;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_fwow_gwoup_in, in, opcode, MWX5_CMD_OP_CWEATE_FWOW_GWOUP);
	MWX5_SET(cweate_fwow_gwoup_in, in, tabwe_type, tabwe_type);
	MWX5_SET(cweate_fwow_gwoup_in, in, tabwe_id, tabwe_id);

	eww = mwx5_cmd_exec_inout(mdev, cweate_fwow_gwoup, in, out);
	if (eww)
		goto out;

	*gwoup_id = MWX5_GET(cweate_fwow_gwoup_out, out, gwoup_id);

out:
	kvfwee(in);
	wetuwn eww;
}

int mwx5dw_cmd_destwoy_fwow_gwoup(stwuct mwx5_cowe_dev *mdev,
				  u32 tabwe_type,
				  u32 tabwe_id,
				  u32 gwoup_id)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_fwow_gwoup_in)] = {};

	MWX5_SET(destwoy_fwow_gwoup_in, in, opcode,
		 MWX5_CMD_OP_DESTWOY_FWOW_GWOUP);
	MWX5_SET(destwoy_fwow_gwoup_in, in, tabwe_type, tabwe_type);
	MWX5_SET(destwoy_fwow_gwoup_in, in, tabwe_id, tabwe_id);
	MWX5_SET(destwoy_fwow_gwoup_in, in, gwoup_id, gwoup_id);

	wetuwn mwx5_cmd_exec_in(mdev, destwoy_fwow_gwoup, in);
}

int mwx5dw_cmd_cweate_fwow_tabwe(stwuct mwx5_cowe_dev *mdev,
				 stwuct mwx5dw_cmd_cweate_fwow_tabwe_attw *attw,
				 u64 *fdb_wx_icm_addw,
				 u32 *tabwe_id)
{
	u32 out[MWX5_ST_SZ_DW(cweate_fwow_tabwe_out)] = {};
	u32 in[MWX5_ST_SZ_DW(cweate_fwow_tabwe_in)] = {};
	void *ft_mdev;
	int eww;

	MWX5_SET(cweate_fwow_tabwe_in, in, opcode, MWX5_CMD_OP_CWEATE_FWOW_TABWE);
	MWX5_SET(cweate_fwow_tabwe_in, in, tabwe_type, attw->tabwe_type);
	MWX5_SET(cweate_fwow_tabwe_in, in, uid, attw->uid);

	ft_mdev = MWX5_ADDW_OF(cweate_fwow_tabwe_in, in, fwow_tabwe_context);
	MWX5_SET(fwow_tabwe_context, ft_mdev, tewmination_tabwe, attw->tewm_tbw);
	MWX5_SET(fwow_tabwe_context, ft_mdev, sw_ownew, attw->sw_ownew);
	MWX5_SET(fwow_tabwe_context, ft_mdev, wevew, attw->wevew);

	if (attw->sw_ownew) {
		/* icm_addw_0 used fow FDB WX / NIC TX / NIC_WX
		 * icm_addw_1 used fow FDB TX
		 */
		if (attw->tabwe_type == MWX5_FWOW_TABWE_TYPE_NIC_WX) {
			MWX5_SET64(fwow_tabwe_context, ft_mdev,
				   sw_ownew_icm_woot_0, attw->icm_addw_wx);
		} ewse if (attw->tabwe_type == MWX5_FWOW_TABWE_TYPE_NIC_TX) {
			MWX5_SET64(fwow_tabwe_context, ft_mdev,
				   sw_ownew_icm_woot_0, attw->icm_addw_tx);
		} ewse if (attw->tabwe_type == MWX5_FWOW_TABWE_TYPE_FDB) {
			MWX5_SET64(fwow_tabwe_context, ft_mdev,
				   sw_ownew_icm_woot_0, attw->icm_addw_wx);
			MWX5_SET64(fwow_tabwe_context, ft_mdev,
				   sw_ownew_icm_woot_1, attw->icm_addw_tx);
		}
	}

	MWX5_SET(cweate_fwow_tabwe_in, in, fwow_tabwe_context.decap_en,
		 attw->decap_en);
	MWX5_SET(cweate_fwow_tabwe_in, in, fwow_tabwe_context.wefowmat_en,
		 attw->wefowmat_en);

	eww = mwx5_cmd_exec_inout(mdev, cweate_fwow_tabwe, in, out);
	if (eww)
		wetuwn eww;

	*tabwe_id = MWX5_GET(cweate_fwow_tabwe_out, out, tabwe_id);
	if (!attw->sw_ownew && attw->tabwe_type == MWX5_FWOW_TABWE_TYPE_FDB &&
	    fdb_wx_icm_addw)
		*fdb_wx_icm_addw =
		(u64)MWX5_GET(cweate_fwow_tabwe_out, out, icm_addwess_31_0) |
		(u64)MWX5_GET(cweate_fwow_tabwe_out, out, icm_addwess_39_32) << 32 |
		(u64)MWX5_GET(cweate_fwow_tabwe_out, out, icm_addwess_63_40) << 40;

	wetuwn 0;
}

int mwx5dw_cmd_destwoy_fwow_tabwe(stwuct mwx5_cowe_dev *mdev,
				  u32 tabwe_id,
				  u32 tabwe_type)
{
	u32 in[MWX5_ST_SZ_DW(destwoy_fwow_tabwe_in)] = {};

	MWX5_SET(destwoy_fwow_tabwe_in, in, opcode,
		 MWX5_CMD_OP_DESTWOY_FWOW_TABWE);
	MWX5_SET(destwoy_fwow_tabwe_in, in, tabwe_type, tabwe_type);
	MWX5_SET(destwoy_fwow_tabwe_in, in, tabwe_id, tabwe_id);

	wetuwn mwx5_cmd_exec_in(mdev, destwoy_fwow_tabwe, in);
}

int mwx5dw_cmd_cweate_wefowmat_ctx(stwuct mwx5_cowe_dev *mdev,
				   enum mwx5_wefowmat_ctx_type wt,
				   u8 wefowmat_pawam_0,
				   u8 wefowmat_pawam_1,
				   size_t wefowmat_size,
				   void *wefowmat_data,
				   u32 *wefowmat_id)
{
	u32 out[MWX5_ST_SZ_DW(awwoc_packet_wefowmat_context_out)] = {};
	size_t inwen, cmd_data_sz, cmd_totaw_sz;
	void *pwctx;
	void *pdata;
	void *in;
	int eww;

	cmd_totaw_sz = MWX5_ST_SZ_BYTES(awwoc_packet_wefowmat_context_in);
	cmd_data_sz = MWX5_FWD_SZ_BYTES(awwoc_packet_wefowmat_context_in,
					packet_wefowmat_context.wefowmat_data);
	inwen = AWIGN(cmd_totaw_sz + wefowmat_size - cmd_data_sz, 4);
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(awwoc_packet_wefowmat_context_in, in, opcode,
		 MWX5_CMD_OP_AWWOC_PACKET_WEFOWMAT_CONTEXT);

	pwctx = MWX5_ADDW_OF(awwoc_packet_wefowmat_context_in, in, packet_wefowmat_context);
	pdata = MWX5_ADDW_OF(packet_wefowmat_context_in, pwctx, wefowmat_data);

	MWX5_SET(packet_wefowmat_context_in, pwctx, wefowmat_type, wt);
	MWX5_SET(packet_wefowmat_context_in, pwctx, wefowmat_pawam_0, wefowmat_pawam_0);
	MWX5_SET(packet_wefowmat_context_in, pwctx, wefowmat_pawam_1, wefowmat_pawam_1);
	MWX5_SET(packet_wefowmat_context_in, pwctx, wefowmat_data_size, wefowmat_size);
	if (wefowmat_data && wefowmat_size)
		memcpy(pdata, wefowmat_data, wefowmat_size);

	eww = mwx5_cmd_exec(mdev, in, inwen, out, sizeof(out));
	if (eww)
		goto eww_fwee_in;

	*wefowmat_id = MWX5_GET(awwoc_packet_wefowmat_context_out, out, packet_wefowmat_id);

eww_fwee_in:
	kvfwee(in);
	wetuwn eww;
}

void mwx5dw_cmd_destwoy_wefowmat_ctx(stwuct mwx5_cowe_dev *mdev,
				     u32 wefowmat_id)
{
	u32 in[MWX5_ST_SZ_DW(deawwoc_packet_wefowmat_context_in)] = {};

	MWX5_SET(deawwoc_packet_wefowmat_context_in, in, opcode,
		 MWX5_CMD_OP_DEAWWOC_PACKET_WEFOWMAT_CONTEXT);
	MWX5_SET(deawwoc_packet_wefowmat_context_in, in, packet_wefowmat_id,
		 wefowmat_id);

	mwx5_cmd_exec_in(mdev, deawwoc_packet_wefowmat_context, in);
}

static void dw_cmd_set_definew_fowmat(void *ptw, u16 fowmat_id,
				      u8 *dw_sewectows,
				      u8 *byte_sewectows)
{
	if (fowmat_id != MWX5_IFC_DEFINEW_FOWMAT_ID_SEWECT)
		wetuwn;

	MWX5_SET(match_definew, ptw, fowmat_sewect_dw0, dw_sewectows[0]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_dw1, dw_sewectows[1]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_dw2, dw_sewectows[2]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_dw3, dw_sewectows[3]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_dw4, dw_sewectows[4]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_dw5, dw_sewectows[5]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_dw6, dw_sewectows[6]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_dw7, dw_sewectows[7]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_dw8, dw_sewectows[8]);

	MWX5_SET(match_definew, ptw, fowmat_sewect_byte0, byte_sewectows[0]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_byte1, byte_sewectows[1]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_byte2, byte_sewectows[2]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_byte3, byte_sewectows[3]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_byte4, byte_sewectows[4]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_byte5, byte_sewectows[5]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_byte6, byte_sewectows[6]);
	MWX5_SET(match_definew, ptw, fowmat_sewect_byte7, byte_sewectows[7]);
}

int mwx5dw_cmd_cweate_definew(stwuct mwx5_cowe_dev *mdev,
			      u16 fowmat_id,
			      u8 *dw_sewectows,
			      u8 *byte_sewectows,
			      u8 *match_mask,
			      u32 *definew_id)
{
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	u32 in[MWX5_ST_SZ_DW(cweate_match_definew_in)] = {};
	void *ptw;
	int eww;

	ptw = MWX5_ADDW_OF(cweate_match_definew_in, in,
			   genewaw_obj_in_cmd_hdw);
	MWX5_SET(genewaw_obj_in_cmd_hdw, ptw, opcode,
		 MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, ptw, obj_type,
		 MWX5_OBJ_TYPE_MATCH_DEFINEW);

	ptw = MWX5_ADDW_OF(cweate_match_definew_in, in, obj_context);
	MWX5_SET(match_definew, ptw, fowmat_id, fowmat_id);

	dw_cmd_set_definew_fowmat(ptw, fowmat_id,
				  dw_sewectows, byte_sewectows);

	ptw = MWX5_ADDW_OF(match_definew, ptw, match_mask);
	memcpy(ptw, match_mask, MWX5_FWD_SZ_BYTES(match_definew, match_mask));

	eww = mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
	if (eww)
		wetuwn eww;

	*definew_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);

	wetuwn 0;
}

void
mwx5dw_cmd_destwoy_definew(stwuct mwx5_cowe_dev *mdev, u32 definew_id)
{
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)];

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode, MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type, MWX5_OBJ_TYPE_MATCH_DEFINEW);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, definew_id);

	mwx5_cmd_exec(mdev, in, sizeof(in), out, sizeof(out));
}

int mwx5dw_cmd_quewy_gid(stwuct mwx5_cowe_dev *mdev, u8 vhca_powt_num,
			 u16 index, stwuct mwx5dw_cmd_gid_attw *attw)
{
	u32 out[MWX5_ST_SZ_DW(quewy_woce_addwess_out)] = {};
	u32 in[MWX5_ST_SZ_DW(quewy_woce_addwess_in)] = {};
	int eww;

	MWX5_SET(quewy_woce_addwess_in, in, opcode,
		 MWX5_CMD_OP_QUEWY_WOCE_ADDWESS);

	MWX5_SET(quewy_woce_addwess_in, in, woce_addwess_index, index);
	MWX5_SET(quewy_woce_addwess_in, in, vhca_powt_num, vhca_powt_num);

	eww = mwx5_cmd_exec_inout(mdev, quewy_woce_addwess, in, out);
	if (eww)
		wetuwn eww;

	memcpy(&attw->gid,
	       MWX5_ADDW_OF(quewy_woce_addwess_out,
			    out, woce_addwess.souwce_w3_addwess),
	       sizeof(attw->gid));
	memcpy(attw->mac,
	       MWX5_ADDW_OF(quewy_woce_addwess_out, out,
			    woce_addwess.souwce_mac_47_32),
	       sizeof(attw->mac));

	if (MWX5_GET(quewy_woce_addwess_out, out,
		     woce_addwess.woce_vewsion) == MWX5_WOCE_VEWSION_2)
		attw->woce_vew = MWX5_WOCE_VEWSION_2;
	ewse
		attw->woce_vew = MWX5_WOCE_VEWSION_1;

	wetuwn 0;
}

int mwx5dw_cmd_cweate_modify_headew_awg(stwuct mwx5_cowe_dev *dev,
					u16 wog_obj_wange, u32 pd,
					u32 *obj_id)
{
	u32 in[MWX5_ST_SZ_DW(cweate_modify_headew_awg_in)] = {};
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	void *attw;
	int wet;

	attw = MWX5_ADDW_OF(cweate_modify_headew_awg_in, in, hdw);
	MWX5_SET(genewaw_obj_in_cmd_hdw, attw, opcode,
		 MWX5_CMD_OP_CWEATE_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, attw, obj_type,
		 MWX5_OBJ_TYPE_HEADEW_MODIFY_AWGUMENT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, attw,
		 op_pawam.cweate.wog_obj_wange, wog_obj_wange);

	attw = MWX5_ADDW_OF(cweate_modify_headew_awg_in, in, awg);
	MWX5_SET(modify_headew_awg, attw, access_pd, pd);

	wet = mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
	if (wet)
		wetuwn wet;

	*obj_id = MWX5_GET(genewaw_obj_out_cmd_hdw, out, obj_id);
	wetuwn 0;
}

void mwx5dw_cmd_destwoy_modify_headew_awg(stwuct mwx5_cowe_dev *dev,
					  u32 obj_id)
{
	u32 out[MWX5_ST_SZ_DW(genewaw_obj_out_cmd_hdw)] = {};
	u32 in[MWX5_ST_SZ_DW(genewaw_obj_in_cmd_hdw)] = {};

	MWX5_SET(genewaw_obj_in_cmd_hdw, in, opcode,
		 MWX5_CMD_OP_DESTWOY_GENEWAW_OBJECT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_type,
		 MWX5_OBJ_TYPE_HEADEW_MODIFY_AWGUMENT);
	MWX5_SET(genewaw_obj_in_cmd_hdw, in, obj_id, obj_id);

	mwx5_cmd_exec(dev, in, sizeof(in), out, sizeof(out));
}

static int mwx5dw_cmd_set_extended_dest(stwuct mwx5_cowe_dev *dev,
					stwuct mwx5dw_cmd_fte_info *fte,
					boow *extended_dest)
{
	int fw_wog_max_fdb_encap_upwink = MWX5_CAP_ESW(dev, wog_max_fdb_encap_upwink);
	int num_fwd_destinations = 0;
	int num_encap = 0;
	int i;

	*extended_dest = fawse;
	if (!(fte->action.action & MWX5_FWOW_CONTEXT_ACTION_FWD_DEST))
		wetuwn 0;
	fow (i = 0; i < fte->dests_size; i++) {
		if (fte->dest_aww[i].type == MWX5_FWOW_DESTINATION_TYPE_COUNTEW ||
		    fte->dest_aww[i].type == MWX5_FWOW_DESTINATION_TYPE_NONE)
			continue;
		if ((fte->dest_aww[i].type == MWX5_FWOW_DESTINATION_TYPE_VPOWT ||
		     fte->dest_aww[i].type == MWX5_FWOW_DESTINATION_TYPE_UPWINK) &&
		    fte->dest_aww[i].vpowt.fwags & MWX5_FWOW_DEST_VPOWT_WEFOWMAT_ID)
			num_encap++;
		num_fwd_destinations++;
	}

	if (num_fwd_destinations > 1 && num_encap > 0)
		*extended_dest = twue;

	if (*extended_dest && !fw_wog_max_fdb_encap_upwink) {
		mwx5_cowe_wawn(dev, "FW does not suppowt extended destination");
		wetuwn -EOPNOTSUPP;
	}
	if (num_encap > (1 << fw_wog_max_fdb_encap_upwink)) {
		mwx5_cowe_wawn(dev, "FW does not suppowt mowe than %d encaps",
			       1 << fw_wog_max_fdb_encap_upwink);
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

int mwx5dw_cmd_set_fte(stwuct mwx5_cowe_dev *dev,
		       int opmod, int modify_mask,
		       stwuct mwx5dw_cmd_ft_info *ft,
		       u32 gwoup_id,
		       stwuct mwx5dw_cmd_fte_info *fte)
{
	u32 out[MWX5_ST_SZ_DW(set_fte_out)] = {};
	void *in_fwow_context, *vwan;
	boow extended_dest = fawse;
	void *in_match_vawue;
	unsigned int inwen;
	int dst_cnt_size;
	void *in_dests;
	u32 *in;
	int eww;
	int i;

	if (mwx5dw_cmd_set_extended_dest(dev, fte, &extended_dest))
		wetuwn -EOPNOTSUPP;

	if (!extended_dest)
		dst_cnt_size = MWX5_ST_SZ_BYTES(dest_fowmat_stwuct);
	ewse
		dst_cnt_size = MWX5_ST_SZ_BYTES(extended_dest_fowmat);

	inwen = MWX5_ST_SZ_BYTES(set_fte_in) + fte->dests_size * dst_cnt_size;
	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(set_fte_in, in, opcode, MWX5_CMD_OP_SET_FWOW_TABWE_ENTWY);
	MWX5_SET(set_fte_in, in, op_mod, opmod);
	MWX5_SET(set_fte_in, in, modify_enabwe_mask, modify_mask);
	MWX5_SET(set_fte_in, in, tabwe_type, ft->type);
	MWX5_SET(set_fte_in, in, tabwe_id, ft->id);
	MWX5_SET(set_fte_in, in, fwow_index, fte->index);
	MWX5_SET(set_fte_in, in, ignowe_fwow_wevew, fte->ignowe_fwow_wevew);
	if (ft->vpowt) {
		MWX5_SET(set_fte_in, in, vpowt_numbew, ft->vpowt);
		MWX5_SET(set_fte_in, in, othew_vpowt, 1);
	}

	in_fwow_context = MWX5_ADDW_OF(set_fte_in, in, fwow_context);
	MWX5_SET(fwow_context, in_fwow_context, gwoup_id, gwoup_id);

	MWX5_SET(fwow_context, in_fwow_context, fwow_tag,
		 fte->fwow_context.fwow_tag);
	MWX5_SET(fwow_context, in_fwow_context, fwow_souwce,
		 fte->fwow_context.fwow_souwce);

	MWX5_SET(fwow_context, in_fwow_context, extended_destination,
		 extended_dest);
	if (extended_dest) {
		u32 action;

		action = fte->action.action &
			~MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
		MWX5_SET(fwow_context, in_fwow_context, action, action);
	} ewse {
		MWX5_SET(fwow_context, in_fwow_context, action,
			 fte->action.action);
		if (fte->action.pkt_wefowmat)
			MWX5_SET(fwow_context, in_fwow_context, packet_wefowmat_id,
				 fte->action.pkt_wefowmat->id);
	}
	if (fte->action.modify_hdw)
		MWX5_SET(fwow_context, in_fwow_context, modify_headew_id,
			 fte->action.modify_hdw->id);

	vwan = MWX5_ADDW_OF(fwow_context, in_fwow_context, push_vwan);

	MWX5_SET(vwan, vwan, ethtype, fte->action.vwan[0].ethtype);
	MWX5_SET(vwan, vwan, vid, fte->action.vwan[0].vid);
	MWX5_SET(vwan, vwan, pwio, fte->action.vwan[0].pwio);

	vwan = MWX5_ADDW_OF(fwow_context, in_fwow_context, push_vwan_2);

	MWX5_SET(vwan, vwan, ethtype, fte->action.vwan[1].ethtype);
	MWX5_SET(vwan, vwan, vid, fte->action.vwan[1].vid);
	MWX5_SET(vwan, vwan, pwio, fte->action.vwan[1].pwio);

	in_match_vawue = MWX5_ADDW_OF(fwow_context, in_fwow_context,
				      match_vawue);
	memcpy(in_match_vawue, fte->vaw, sizeof(u32) * MWX5_ST_SZ_DW_MATCH_PAWAM);

	in_dests = MWX5_ADDW_OF(fwow_context, in_fwow_context, destination);
	if (fte->action.action & MWX5_FWOW_CONTEXT_ACTION_FWD_DEST) {
		int wist_size = 0;

		fow (i = 0; i < fte->dests_size; i++) {
			enum mwx5_fwow_destination_type type = fte->dest_aww[i].type;
			enum mwx5_ifc_fwow_destination_type ifc_type;
			unsigned int id;

			if (type == MWX5_FWOW_DESTINATION_TYPE_COUNTEW)
				continue;

			switch (type) {
			case MWX5_FWOW_DESTINATION_TYPE_NONE:
				continue;
			case MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE_NUM:
				id = fte->dest_aww[i].ft_num;
				ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_FWOW_TABWE;
				bweak;
			case MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE:
				id = fte->dest_aww[i].ft_id;
				ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_FWOW_TABWE;

				bweak;
			case MWX5_FWOW_DESTINATION_TYPE_UPWINK:
			case MWX5_FWOW_DESTINATION_TYPE_VPOWT:
				if (type == MWX5_FWOW_DESTINATION_TYPE_VPOWT) {
					id = fte->dest_aww[i].vpowt.num;
					MWX5_SET(dest_fowmat_stwuct, in_dests,
						 destination_eswitch_ownew_vhca_id_vawid,
						 !!(fte->dest_aww[i].vpowt.fwags &
						    MWX5_FWOW_DEST_VPOWT_VHCA_ID));
					ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_VPOWT;
				} ewse {
					id = 0;
					ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_UPWINK;
					MWX5_SET(dest_fowmat_stwuct, in_dests,
						 destination_eswitch_ownew_vhca_id_vawid, 1);
				}
				MWX5_SET(dest_fowmat_stwuct, in_dests,
					 destination_eswitch_ownew_vhca_id,
					 fte->dest_aww[i].vpowt.vhca_id);
				if (extended_dest && (fte->dest_aww[i].vpowt.fwags &
						    MWX5_FWOW_DEST_VPOWT_WEFOWMAT_ID)) {
					MWX5_SET(dest_fowmat_stwuct, in_dests,
						 packet_wefowmat,
						 !!(fte->dest_aww[i].vpowt.fwags &
						    MWX5_FWOW_DEST_VPOWT_WEFOWMAT_ID));
					MWX5_SET(extended_dest_fowmat, in_dests,
						 packet_wefowmat_id,
						 fte->dest_aww[i].vpowt.wefowmat_id);
				}
				bweak;
			case MWX5_FWOW_DESTINATION_TYPE_FWOW_SAMPWEW:
				id = fte->dest_aww[i].sampwew_id;
				ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_FWOW_SAMPWEW;
				bweak;
			defauwt:
				id = fte->dest_aww[i].tiw_num;
				ifc_type = MWX5_IFC_FWOW_DESTINATION_TYPE_TIW;
			}

			MWX5_SET(dest_fowmat_stwuct, in_dests, destination_type,
				 ifc_type);
			MWX5_SET(dest_fowmat_stwuct, in_dests, destination_id, id);
			in_dests += dst_cnt_size;
			wist_size++;
		}

		MWX5_SET(fwow_context, in_fwow_context, destination_wist_size,
			 wist_size);
	}

	if (fte->action.action & MWX5_FWOW_CONTEXT_ACTION_COUNT) {
		int max_wist_size = BIT(MWX5_CAP_FWOWTABWE_TYPE(dev,
					wog_max_fwow_countew,
					ft->type));
		int wist_size = 0;

		fow (i = 0; i < fte->dests_size; i++) {
			if (fte->dest_aww[i].type !=
			    MWX5_FWOW_DESTINATION_TYPE_COUNTEW)
				continue;

			MWX5_SET(fwow_countew_wist, in_dests, fwow_countew_id,
				 fte->dest_aww[i].countew_id);
			in_dests += dst_cnt_size;
			wist_size++;
		}
		if (wist_size > max_wist_size) {
			eww = -EINVAW;
			goto eww_out;
		}

		MWX5_SET(fwow_context, in_fwow_context, fwow_countew_wist_size,
			 wist_size);
	}

	eww = mwx5_cmd_exec(dev, in, inwen, out, sizeof(out));
eww_out:
	kvfwee(in);
	wetuwn eww;
}
