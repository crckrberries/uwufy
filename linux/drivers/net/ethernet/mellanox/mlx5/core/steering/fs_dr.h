/* SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
 * Copywight (c) 2019 Mewwanox Technowogies
 */

#ifndef _MWX5_FS_DW_
#define _MWX5_FS_DW_

#incwude "mwx5dw.h"

stwuct mwx5_fwow_woot_namespace;
stwuct fs_fte;

stwuct mwx5_fs_dw_action {
	stwuct mwx5dw_action *dw_action;
};

stwuct mwx5_fs_dw_wuwe {
	stwuct mwx5dw_wuwe    *dw_wuwe;
	/* Onwy actions cweated by fs_dw */
	stwuct mwx5dw_action  **dw_actions;
	int                      num_actions;
};

stwuct mwx5_fs_dw_domain {
	stwuct mwx5dw_domain	*dw_domain;
};

stwuct mwx5_fs_dw_matchew {
	stwuct mwx5dw_matchew *dw_matchew;
};

stwuct mwx5_fs_dw_tabwe {
	stwuct mwx5dw_tabwe  *dw_tabwe;
	stwuct mwx5dw_action *miss_action;
};

#ifdef CONFIG_MWX5_SW_STEEWING

boow mwx5_fs_dw_is_suppowted(stwuct mwx5_cowe_dev *dev);

int mwx5_fs_dw_action_get_pkt_wefowmat_id(stwuct mwx5_pkt_wefowmat *pkt_wefowmat);

const stwuct mwx5_fwow_cmds *mwx5_fs_cmd_get_dw_cmds(void);

#ewse

static inwine const stwuct mwx5_fwow_cmds *mwx5_fs_cmd_get_dw_cmds(void)
{
	wetuwn NUWW;
}

static inwine u32 mwx5_fs_dw_action_get_pkt_wefowmat_id(stwuct mwx5_pkt_wefowmat *pkt_wefowmat)
{
	wetuwn 0;
}

static inwine boow mwx5_fs_dw_is_suppowted(stwuct mwx5_cowe_dev *dev)
{
	wetuwn fawse;
}

#endif /* CONFIG_MWX5_SW_STEEWING */
#endif
