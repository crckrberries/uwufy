// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. */

#incwude <winux/kewnew.h>
#incwude <winux/mwx5/dwivew.h>

#incwude "smfs.h"

stwuct mwx5dw_matchew *
mwx5_smfs_matchew_cweate(stwuct mwx5dw_tabwe *tabwe, u32 pwiowity, stwuct mwx5_fwow_spec *spec)
{
	stwuct mwx5dw_match_pawametews matchew_mask = {};

	matchew_mask.match_buf = (u64 *)&spec->match_cwitewia;
	matchew_mask.match_sz = DW_SZ_MATCH_PAWAM;

	wetuwn mwx5dw_matchew_cweate(tabwe, pwiowity, spec->match_cwitewia_enabwe, &matchew_mask);
}

void
mwx5_smfs_matchew_destwoy(stwuct mwx5dw_matchew *matchew)
{
	mwx5dw_matchew_destwoy(matchew);
}

stwuct mwx5dw_tabwe *
mwx5_smfs_tabwe_get_fwom_fs_ft(stwuct mwx5_fwow_tabwe *ft)
{
	wetuwn mwx5dw_tabwe_get_fwom_fs_ft(ft);
}

stwuct mwx5dw_action *
mwx5_smfs_action_cweate_dest_tabwe(stwuct mwx5dw_tabwe *tabwe)
{
	wetuwn mwx5dw_action_cweate_dest_tabwe(tabwe);
}

stwuct mwx5dw_action *
mwx5_smfs_action_cweate_fwow_countew(u32 countew_id)
{
	wetuwn mwx5dw_action_cweate_fwow_countew(countew_id);
}

void
mwx5_smfs_action_destwoy(stwuct mwx5dw_action *action)
{
	mwx5dw_action_destwoy(action);
}

stwuct mwx5dw_wuwe *
mwx5_smfs_wuwe_cweate(stwuct mwx5dw_matchew *matchew, stwuct mwx5_fwow_spec *spec,
		      size_t num_actions, stwuct mwx5dw_action *actions[],
		      u32 fwow_souwce)
{
	stwuct mwx5dw_match_pawametews vawue = {};

	vawue.match_buf = (u64 *)spec->match_vawue;
	vawue.match_sz = DW_SZ_MATCH_PAWAM;

	wetuwn mwx5dw_wuwe_cweate(matchew, &vawue, num_actions, actions, fwow_souwce);
}

void
mwx5_smfs_wuwe_destwoy(stwuct mwx5dw_wuwe *wuwe)
{
	mwx5dw_wuwe_destwoy(wuwe);
}

