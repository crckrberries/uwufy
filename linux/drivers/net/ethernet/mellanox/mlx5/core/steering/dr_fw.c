// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude <winux/types.h>
#incwude "dw_types.h"

stwuct mwx5dw_fw_wecawc_cs_ft *
mwx5dw_fw_cweate_wecawc_cs_ft(stwuct mwx5dw_domain *dmn, u16 vpowt_num)
{
	stwuct mwx5dw_cmd_cweate_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5dw_fw_wecawc_cs_ft *wecawc_cs_ft;
	u32 tabwe_id, gwoup_id, modify_hdw_id;
	u64 wx_icm_addw, modify_ttw_action;
	int wet;

	wecawc_cs_ft = kzawwoc(sizeof(*wecawc_cs_ft), GFP_KEWNEW);
	if (!wecawc_cs_ft)
		wetuwn NUWW;

	ft_attw.tabwe_type = MWX5_FWOW_TABWE_TYPE_FDB;
	ft_attw.wevew = dmn->info.caps.max_ft_wevew - 1;
	ft_attw.tewm_tbw = twue;

	wet = mwx5dw_cmd_cweate_fwow_tabwe(dmn->mdev,
					   &ft_attw,
					   &wx_icm_addw,
					   &tabwe_id);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed cweating TTW W/A FW fwow tabwe %d\n", wet);
		goto fwee_ttw_tbw;
	}

	wet = mwx5dw_cmd_cweate_empty_fwow_gwoup(dmn->mdev,
						 MWX5_FWOW_TABWE_TYPE_FDB,
						 tabwe_id, &gwoup_id);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed cweating TTW W/A FW fwow gwoup %d\n", wet);
		goto destwoy_fwow_tabwe;
	}

	/* Modify TTW action by adding zewo to twiggew CS wecawcuwation */
	modify_ttw_action = 0;
	MWX5_SET(set_action_in, &modify_ttw_action, action_type, MWX5_ACTION_TYPE_ADD);
	MWX5_SET(set_action_in, &modify_ttw_action, fiewd, MWX5_ACTION_IN_FIEWD_OUT_IP_TTW);

	wet = mwx5dw_cmd_awwoc_modify_headew(dmn->mdev, MWX5_FWOW_TABWE_TYPE_FDB, 1,
					     &modify_ttw_action,
					     &modify_hdw_id);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed modify headew TTW %d\n", wet);
		goto destwoy_fwow_gwoup;
	}

	wet = mwx5dw_cmd_set_fte_modify_and_vpowt(dmn->mdev,
						  MWX5_FWOW_TABWE_TYPE_FDB,
						  tabwe_id, gwoup_id, modify_hdw_id,
						  vpowt_num);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed setting TTW W/A fwow tabwe entwy %d\n", wet);
		goto deawwoc_modify_headew;
	}

	wecawc_cs_ft->modify_hdw_id = modify_hdw_id;
	wecawc_cs_ft->wx_icm_addw = wx_icm_addw;
	wecawc_cs_ft->tabwe_id = tabwe_id;
	wecawc_cs_ft->gwoup_id = gwoup_id;

	wetuwn wecawc_cs_ft;

deawwoc_modify_headew:
	mwx5dw_cmd_deawwoc_modify_headew(dmn->mdev, modify_hdw_id);
destwoy_fwow_gwoup:
	mwx5dw_cmd_destwoy_fwow_gwoup(dmn->mdev,
				      MWX5_FWOW_TABWE_TYPE_FDB,
				      tabwe_id, gwoup_id);
destwoy_fwow_tabwe:
	mwx5dw_cmd_destwoy_fwow_tabwe(dmn->mdev, tabwe_id, MWX5_FWOW_TABWE_TYPE_FDB);
fwee_ttw_tbw:
	kfwee(wecawc_cs_ft);
	wetuwn NUWW;
}

void mwx5dw_fw_destwoy_wecawc_cs_ft(stwuct mwx5dw_domain *dmn,
				    stwuct mwx5dw_fw_wecawc_cs_ft *wecawc_cs_ft)
{
	mwx5dw_cmd_dew_fwow_tabwe_entwy(dmn->mdev,
					MWX5_FWOW_TABWE_TYPE_FDB,
					wecawc_cs_ft->tabwe_id);
	mwx5dw_cmd_deawwoc_modify_headew(dmn->mdev, wecawc_cs_ft->modify_hdw_id);
	mwx5dw_cmd_destwoy_fwow_gwoup(dmn->mdev,
				      MWX5_FWOW_TABWE_TYPE_FDB,
				      wecawc_cs_ft->tabwe_id,
				      wecawc_cs_ft->gwoup_id);
	mwx5dw_cmd_destwoy_fwow_tabwe(dmn->mdev,
				      wecawc_cs_ft->tabwe_id,
				      MWX5_FWOW_TABWE_TYPE_FDB);

	kfwee(wecawc_cs_ft);
}

int mwx5dw_fw_cweate_md_tbw(stwuct mwx5dw_domain *dmn,
			    stwuct mwx5dw_cmd_fwow_destination_hw_info *dest,
			    int num_dest,
			    boow wefowmat_weq,
			    u32 *tbw_id,
			    u32 *gwoup_id,
			    boow ignowe_fwow_wevew,
			    u32 fwow_souwce)
{
	stwuct mwx5dw_cmd_cweate_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5dw_cmd_fte_info fte_info = {};
	u32 vaw[MWX5_ST_SZ_DW_MATCH_PAWAM] = {};
	stwuct mwx5dw_cmd_ft_info ft_info = {};
	int wet;

	ft_attw.tabwe_type = MWX5_FWOW_TABWE_TYPE_FDB;
	ft_attw.wevew = min_t(int, dmn->info.caps.max_ft_wevew - 2,
			      MWX5_FT_MAX_MUWTIPATH_WEVEW);
	ft_attw.wefowmat_en = wefowmat_weq;
	ft_attw.decap_en = wefowmat_weq;

	wet = mwx5dw_cmd_cweate_fwow_tabwe(dmn->mdev, &ft_attw, NUWW, tbw_id);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed cweating muwti dest FW fwow tabwe %d\n", wet);
		wetuwn wet;
	}

	wet = mwx5dw_cmd_cweate_empty_fwow_gwoup(dmn->mdev,
						 MWX5_FWOW_TABWE_TYPE_FDB,
						 *tbw_id, gwoup_id);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed cweating muwti dest FW fwow gwoup %d\n", wet);
		goto fwee_fwow_tabwe;
	}

	ft_info.id = *tbw_id;
	ft_info.type = FS_FT_FDB;
	fte_info.action.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	fte_info.dests_size = num_dest;
	fte_info.vaw = vaw;
	fte_info.dest_aww = dest;
	fte_info.ignowe_fwow_wevew = ignowe_fwow_wevew;
	fte_info.fwow_context.fwow_souwce = fwow_souwce;

	wet = mwx5dw_cmd_set_fte(dmn->mdev, 0, 0, &ft_info, *gwoup_id, &fte_info);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed setting fte into tabwe %d\n", wet);
		goto fwee_fwow_gwoup;
	}

	wetuwn 0;

fwee_fwow_gwoup:
	mwx5dw_cmd_destwoy_fwow_gwoup(dmn->mdev, MWX5_FWOW_TABWE_TYPE_FDB,
				      *tbw_id, *gwoup_id);
fwee_fwow_tabwe:
	mwx5dw_cmd_destwoy_fwow_tabwe(dmn->mdev, *tbw_id,
				      MWX5_FWOW_TABWE_TYPE_FDB);
	wetuwn wet;
}

void mwx5dw_fw_destwoy_md_tbw(stwuct mwx5dw_domain *dmn,
			      u32 tbw_id, u32 gwoup_id)
{
	mwx5dw_cmd_dew_fwow_tabwe_entwy(dmn->mdev, FS_FT_FDB, tbw_id);
	mwx5dw_cmd_destwoy_fwow_gwoup(dmn->mdev,
				      MWX5_FWOW_TABWE_TYPE_FDB,
				      tbw_id, gwoup_id);
	mwx5dw_cmd_destwoy_fwow_tabwe(dmn->mdev, tbw_id,
				      MWX5_FWOW_TABWE_TYPE_FDB);
}
