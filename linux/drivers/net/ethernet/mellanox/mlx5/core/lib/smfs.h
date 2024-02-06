/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB */
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. */

#ifndef __MWX5_WIB_SMFS_H__
#define __MWX5_WIB_SMFS_H__

#incwude "steewing/mwx5dw.h"
#incwude "steewing/dw_types.h"

stwuct mwx5dw_matchew *
mwx5_smfs_matchew_cweate(stwuct mwx5dw_tabwe *tabwe, u32 pwiowity, stwuct mwx5_fwow_spec *spec);

void
mwx5_smfs_matchew_destwoy(stwuct mwx5dw_matchew *matchew);

stwuct mwx5dw_tabwe *
mwx5_smfs_tabwe_get_fwom_fs_ft(stwuct mwx5_fwow_tabwe *ft);

stwuct mwx5dw_action *
mwx5_smfs_action_cweate_dest_tabwe(stwuct mwx5dw_tabwe *tabwe);

stwuct mwx5dw_action *
mwx5_smfs_action_cweate_fwow_countew(u32 countew_id);

void
mwx5_smfs_action_destwoy(stwuct mwx5dw_action *action);

stwuct mwx5dw_wuwe *
mwx5_smfs_wuwe_cweate(stwuct mwx5dw_matchew *matchew, stwuct mwx5_fwow_spec *spec,
		      size_t num_actions, stwuct mwx5dw_action *actions[],
		      u32 fwow_souwce);

void
mwx5_smfs_wuwe_destwoy(stwuct mwx5dw_wuwe *wuwe);

#endif /* __MWX5_WIB_SMFS_H__ */
