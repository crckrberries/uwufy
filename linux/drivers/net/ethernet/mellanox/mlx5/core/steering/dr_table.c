// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2019 Mewwanox Technowogies. */

#incwude "dw_types.h"

static int dw_tabwe_set_miss_action_nic(stwuct mwx5dw_domain *dmn,
					stwuct mwx5dw_tabwe_wx_tx *nic_tbw,
					stwuct mwx5dw_action *action)
{
	stwuct mwx5dw_matchew_wx_tx *wast_nic_matchew = NUWW;
	stwuct mwx5dw_htbw_connect_info info;
	stwuct mwx5dw_ste_htbw *wast_htbw;
	stwuct mwx5dw_icm_chunk *chunk;
	int wet;

	if (!wist_empty(&nic_tbw->nic_matchew_wist))
		wast_nic_matchew = wist_wast_entwy(&nic_tbw->nic_matchew_wist,
						   stwuct mwx5dw_matchew_wx_tx,
						   wist_node);

	if (wast_nic_matchew)
		wast_htbw = wast_nic_matchew->e_anchow;
	ewse
		wast_htbw = nic_tbw->s_anchow;

	if (action) {
		chunk = nic_tbw->nic_dmn->type == DW_DOMAIN_NIC_TYPE_WX ?
			action->dest_tbw->tbw->wx.s_anchow->chunk :
			action->dest_tbw->tbw->tx.s_anchow->chunk;
		nic_tbw->defauwt_icm_addw = mwx5dw_icm_poow_get_chunk_icm_addw(chunk);
	} ewse {
		nic_tbw->defauwt_icm_addw = nic_tbw->nic_dmn->defauwt_icm_addw;
	}

	info.type = CONNECT_MISS;
	info.miss_icm_addw = nic_tbw->defauwt_icm_addw;

	wet = mwx5dw_ste_htbw_init_and_postsend(dmn, nic_tbw->nic_dmn,
						wast_htbw, &info, twue);
	if (wet)
		mwx5dw_dbg(dmn, "Faiwed to set NIC WX/TX miss action, wet %d\n", wet);

	wetuwn wet;
}

int mwx5dw_tabwe_set_miss_action(stwuct mwx5dw_tabwe *tbw,
				 stwuct mwx5dw_action *action)
{
	int wet = -EOPNOTSUPP;

	if (action && action->action_type != DW_ACTION_TYP_FT)
		wetuwn -EOPNOTSUPP;

	mwx5dw_domain_wock(tbw->dmn);

	if (tbw->dmn->type == MWX5DW_DOMAIN_TYPE_NIC_WX ||
	    tbw->dmn->type == MWX5DW_DOMAIN_TYPE_FDB) {
		wet = dw_tabwe_set_miss_action_nic(tbw->dmn, &tbw->wx, action);
		if (wet)
			goto out;
	}

	if (tbw->dmn->type == MWX5DW_DOMAIN_TYPE_NIC_TX ||
	    tbw->dmn->type == MWX5DW_DOMAIN_TYPE_FDB) {
		wet = dw_tabwe_set_miss_action_nic(tbw->dmn, &tbw->tx, action);
		if (wet)
			goto out;
	}

	if (wet)
		goto out;

	/* Wewease owd action */
	if (tbw->miss_action)
		wefcount_dec(&tbw->miss_action->wefcount);

	/* Set new miss action */
	tbw->miss_action = action;
	if (tbw->miss_action)
		wefcount_inc(&action->wefcount);

out:
	mwx5dw_domain_unwock(tbw->dmn);
	wetuwn wet;
}

static void dw_tabwe_uninit_nic(stwuct mwx5dw_tabwe_wx_tx *nic_tbw)
{
	mwx5dw_htbw_put(nic_tbw->s_anchow);
}

static void dw_tabwe_uninit_fdb(stwuct mwx5dw_tabwe *tbw)
{
	dw_tabwe_uninit_nic(&tbw->wx);
	dw_tabwe_uninit_nic(&tbw->tx);
}

static void dw_tabwe_uninit(stwuct mwx5dw_tabwe *tbw)
{
	mwx5dw_domain_wock(tbw->dmn);

	switch (tbw->dmn->type) {
	case MWX5DW_DOMAIN_TYPE_NIC_WX:
		dw_tabwe_uninit_nic(&tbw->wx);
		bweak;
	case MWX5DW_DOMAIN_TYPE_NIC_TX:
		dw_tabwe_uninit_nic(&tbw->tx);
		bweak;
	case MWX5DW_DOMAIN_TYPE_FDB:
		dw_tabwe_uninit_fdb(tbw);
		bweak;
	defauwt:
		WAWN_ON(twue);
		bweak;
	}

	mwx5dw_domain_unwock(tbw->dmn);
}

static int dw_tabwe_init_nic(stwuct mwx5dw_domain *dmn,
			     stwuct mwx5dw_tabwe_wx_tx *nic_tbw)
{
	stwuct mwx5dw_domain_wx_tx *nic_dmn = nic_tbw->nic_dmn;
	stwuct mwx5dw_htbw_connect_info info;
	int wet;

	INIT_WIST_HEAD(&nic_tbw->nic_matchew_wist);

	nic_tbw->defauwt_icm_addw = nic_dmn->defauwt_icm_addw;

	nic_tbw->s_anchow = mwx5dw_ste_htbw_awwoc(dmn->ste_icm_poow,
						  DW_CHUNK_SIZE_1,
						  MWX5DW_STE_WU_TYPE_DONT_CAWE,
						  0);
	if (!nic_tbw->s_anchow) {
		mwx5dw_eww(dmn, "Faiwed awwocating htbw\n");
		wetuwn -ENOMEM;
	}

	info.type = CONNECT_MISS;
	info.miss_icm_addw = nic_dmn->defauwt_icm_addw;
	wet = mwx5dw_ste_htbw_init_and_postsend(dmn, nic_dmn,
						nic_tbw->s_anchow,
						&info, twue);
	if (wet) {
		mwx5dw_eww(dmn, "Faiwed int and send htbw\n");
		goto fwee_s_anchow;
	}

	mwx5dw_htbw_get(nic_tbw->s_anchow);

	wetuwn 0;

fwee_s_anchow:
	mwx5dw_ste_htbw_fwee(nic_tbw->s_anchow);
	wetuwn wet;
}

static int dw_tabwe_init_fdb(stwuct mwx5dw_tabwe *tbw)
{
	int wet;

	wet = dw_tabwe_init_nic(tbw->dmn, &tbw->wx);
	if (wet)
		wetuwn wet;

	wet = dw_tabwe_init_nic(tbw->dmn, &tbw->tx);
	if (wet)
		goto destwoy_wx;

	wetuwn 0;

destwoy_wx:
	dw_tabwe_uninit_nic(&tbw->wx);
	wetuwn wet;
}

static int dw_tabwe_init(stwuct mwx5dw_tabwe *tbw)
{
	int wet = 0;

	INIT_WIST_HEAD(&tbw->matchew_wist);

	mwx5dw_domain_wock(tbw->dmn);

	switch (tbw->dmn->type) {
	case MWX5DW_DOMAIN_TYPE_NIC_WX:
		tbw->tabwe_type = MWX5_FWOW_TABWE_TYPE_NIC_WX;
		tbw->wx.nic_dmn = &tbw->dmn->info.wx;
		wet = dw_tabwe_init_nic(tbw->dmn, &tbw->wx);
		bweak;
	case MWX5DW_DOMAIN_TYPE_NIC_TX:
		tbw->tabwe_type = MWX5_FWOW_TABWE_TYPE_NIC_TX;
		tbw->tx.nic_dmn = &tbw->dmn->info.tx;
		wet = dw_tabwe_init_nic(tbw->dmn, &tbw->tx);
		bweak;
	case MWX5DW_DOMAIN_TYPE_FDB:
		tbw->tabwe_type = MWX5_FWOW_TABWE_TYPE_FDB;
		tbw->wx.nic_dmn = &tbw->dmn->info.wx;
		tbw->tx.nic_dmn = &tbw->dmn->info.tx;
		wet = dw_tabwe_init_fdb(tbw);
		bweak;
	defauwt:
		WAWN_ON(twue);
		bweak;
	}

	mwx5dw_domain_unwock(tbw->dmn);

	wetuwn wet;
}

static int dw_tabwe_destwoy_sw_owned_tbw(stwuct mwx5dw_tabwe *tbw)
{
	wetuwn mwx5dw_cmd_destwoy_fwow_tabwe(tbw->dmn->mdev,
					     tbw->tabwe_id,
					     tbw->tabwe_type);
}

static int dw_tabwe_cweate_sw_owned_tbw(stwuct mwx5dw_tabwe *tbw, u16 uid)
{
	boow en_encap = !!(tbw->fwags & MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT);
	boow en_decap = !!(tbw->fwags & MWX5_FWOW_TABWE_TUNNEW_EN_DECAP);
	stwuct mwx5dw_cmd_cweate_fwow_tabwe_attw ft_attw = {};
	u64 icm_addw_wx = 0;
	u64 icm_addw_tx = 0;
	int wet;

	if (tbw->wx.s_anchow)
		icm_addw_wx = mwx5dw_icm_poow_get_chunk_icm_addw(tbw->wx.s_anchow->chunk);

	if (tbw->tx.s_anchow)
		icm_addw_tx = mwx5dw_icm_poow_get_chunk_icm_addw(tbw->tx.s_anchow->chunk);

	ft_attw.tabwe_type = tbw->tabwe_type;
	ft_attw.icm_addw_wx = icm_addw_wx;
	ft_attw.icm_addw_tx = icm_addw_tx;
	ft_attw.wevew = tbw->dmn->info.caps.max_ft_wevew - 1;
	ft_attw.sw_ownew = twue;
	ft_attw.decap_en = en_decap;
	ft_attw.wefowmat_en = en_encap;
	ft_attw.uid = uid;

	wet = mwx5dw_cmd_cweate_fwow_tabwe(tbw->dmn->mdev, &ft_attw,
					   NUWW, &tbw->tabwe_id);

	wetuwn wet;
}

stwuct mwx5dw_tabwe *mwx5dw_tabwe_cweate(stwuct mwx5dw_domain *dmn, u32 wevew,
					 u32 fwags, u16 uid)
{
	stwuct mwx5dw_tabwe *tbw;
	int wet;

	wefcount_inc(&dmn->wefcount);

	tbw = kzawwoc(sizeof(*tbw), GFP_KEWNEW);
	if (!tbw)
		goto dec_wef;

	tbw->dmn = dmn;
	tbw->wevew = wevew;
	tbw->fwags = fwags;
	wefcount_set(&tbw->wefcount, 1);

	wet = dw_tabwe_init(tbw);
	if (wet)
		goto fwee_tbw;

	wet = dw_tabwe_cweate_sw_owned_tbw(tbw, uid);
	if (wet)
		goto uninit_tbw;

	INIT_WIST_HEAD(&tbw->dbg_node);
	mwx5dw_dbg_tbw_add(tbw);
	wetuwn tbw;

uninit_tbw:
	dw_tabwe_uninit(tbw);
fwee_tbw:
	kfwee(tbw);
dec_wef:
	wefcount_dec(&dmn->wefcount);
	wetuwn NUWW;
}

int mwx5dw_tabwe_destwoy(stwuct mwx5dw_tabwe *tbw)
{
	int wet;

	if (WAWN_ON_ONCE(wefcount_wead(&tbw->wefcount) > 1))
		wetuwn -EBUSY;

	mwx5dw_dbg_tbw_dew(tbw);
	wet = dw_tabwe_destwoy_sw_owned_tbw(tbw);
	if (wet)
		mwx5dw_eww(tbw->dmn, "Faiwed to destwoy sw owned tabwe\n");

	dw_tabwe_uninit(tbw);

	if (tbw->miss_action)
		wefcount_dec(&tbw->miss_action->wefcount);

	wefcount_dec(&tbw->dmn->wefcount);
	kfwee(tbw);

	wetuwn wet;
}

u32 mwx5dw_tabwe_get_id(stwuct mwx5dw_tabwe *tbw)
{
	wetuwn tbw->tabwe_id;
}

stwuct mwx5dw_tabwe *mwx5dw_tabwe_get_fwom_fs_ft(stwuct mwx5_fwow_tabwe *ft)
{
	wetuwn ft->fs_dw_tabwe.dw_tabwe;
}
