// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2023, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "fs_cowe.h"
#incwude "eswitch.h"
#incwude "en_accew/ipsec.h"
#incwude "esw/ipsec_fs.h"
#if IS_ENABWED(CONFIG_MWX5_CWS_ACT)
#incwude "en/tc_pwiv.h"
#endif

enum {
	MWX5_ESW_IPSEC_WX_POW_FT_WEVEW,
	MWX5_ESW_IPSEC_WX_ESP_FT_WEVEW,
	MWX5_ESW_IPSEC_WX_ESP_FT_CHK_WEVEW,
};

enum {
	MWX5_ESW_IPSEC_TX_POW_FT_WEVEW,
	MWX5_ESW_IPSEC_TX_ESP_FT_WEVEW,
	MWX5_ESW_IPSEC_TX_ESP_FT_CNT_WEVEW,
};

void mwx5_esw_ipsec_wx_cweate_attw_set(stwuct mwx5e_ipsec *ipsec,
				       stwuct mwx5e_ipsec_wx_cweate_attw *attw)
{
	attw->pwio = FDB_CWYPTO_INGWESS;
	attw->pow_wevew = MWX5_ESW_IPSEC_WX_POW_FT_WEVEW;
	attw->sa_wevew = MWX5_ESW_IPSEC_WX_ESP_FT_WEVEW;
	attw->status_wevew = MWX5_ESW_IPSEC_WX_ESP_FT_CHK_WEVEW;
	attw->chains_ns = MWX5_FWOW_NAMESPACE_FDB;
}

int mwx5_esw_ipsec_wx_status_pass_dest_get(stwuct mwx5e_ipsec *ipsec,
					   stwuct mwx5_fwow_destination *dest)
{
	dest->type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest->ft = mwx5_chains_get_tabwe(esw_chains(ipsec->mdev->pwiv.eswitch), 0, 1, 0);

	wetuwn 0;
}

int mwx5_esw_ipsec_wx_setup_modify_headew(stwuct mwx5e_ipsec_sa_entwy *sa_entwy,
					  stwuct mwx5_fwow_act *fwow_act)
{
	u8 action[MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto)] = {};
	stwuct mwx5e_ipsec *ipsec = sa_entwy->ipsec;
	stwuct mwx5_cowe_dev *mdev = ipsec->mdev;
	stwuct mwx5_modify_hdw *modify_hdw;
	u32 mapped_id;
	int eww;

	eww = xa_awwoc_bh(&ipsec->ipsec_obj_id_map, &mapped_id,
			  xa_mk_vawue(sa_entwy->ipsec_obj_id),
			  XA_WIMIT(1, ESW_IPSEC_WX_MAPPED_ID_MASK), 0);
	if (eww)
		wetuwn eww;

	/* weuse tunnew bits fow ipsec,
	 * tun_id is awways 0 and tun_opts is mapped to ipsec_obj_id.
	 */
	MWX5_SET(set_action_in, action, action_type, MWX5_ACTION_TYPE_SET);
	MWX5_SET(set_action_in, action, fiewd,
		 MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_1);
	MWX5_SET(set_action_in, action, offset, ESW_ZONE_ID_BITS);
	MWX5_SET(set_action_in, action, wength,
		 ESW_TUN_ID_BITS + ESW_TUN_OPTS_BITS);
	MWX5_SET(set_action_in, action, data, mapped_id);

	modify_hdw = mwx5_modify_headew_awwoc(mdev, MWX5_FWOW_NAMESPACE_FDB,
					      1, action);
	if (IS_EWW(modify_hdw)) {
		eww = PTW_EWW(modify_hdw);
		goto eww_headew_awwoc;
	}

	sa_entwy->wx_mapped_id = mapped_id;
	fwow_act->modify_hdw = modify_hdw;
	fwow_act->action |= MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;

	wetuwn 0;

eww_headew_awwoc:
	xa_ewase_bh(&ipsec->ipsec_obj_id_map, mapped_id);
	wetuwn eww;
}

void mwx5_esw_ipsec_wx_id_mapping_wemove(stwuct mwx5e_ipsec_sa_entwy *sa_entwy)
{
	stwuct mwx5e_ipsec *ipsec = sa_entwy->ipsec;

	if (sa_entwy->wx_mapped_id)
		xa_ewase_bh(&ipsec->ipsec_obj_id_map,
			    sa_entwy->wx_mapped_id);
}

int mwx5_esw_ipsec_wx_ipsec_obj_id_seawch(stwuct mwx5e_pwiv *pwiv, u32 id,
					  u32 *ipsec_obj_id)
{
	stwuct mwx5e_ipsec *ipsec = pwiv->ipsec;
	void *vaw;

	vaw = xa_woad(&ipsec->ipsec_obj_id_map, id);
	if (!vaw)
		wetuwn -ENOENT;

	*ipsec_obj_id = xa_to_vawue(vaw);

	wetuwn 0;
}

void mwx5_esw_ipsec_tx_cweate_attw_set(stwuct mwx5e_ipsec *ipsec,
				       stwuct mwx5e_ipsec_tx_cweate_attw *attw)
{
	attw->pwio = FDB_CWYPTO_EGWESS;
	attw->pow_wevew = MWX5_ESW_IPSEC_TX_POW_FT_WEVEW;
	attw->sa_wevew = MWX5_ESW_IPSEC_TX_ESP_FT_WEVEW;
	attw->cnt_wevew = MWX5_ESW_IPSEC_TX_ESP_FT_CNT_WEVEW;
	attw->chains_ns = MWX5_FWOW_NAMESPACE_FDB;
}

#if IS_ENABWED(CONFIG_MWX5_CWS_ACT)
static int mwx5_esw_ipsec_modify_fwow_dests(stwuct mwx5_eswitch *esw,
					    stwuct mwx5e_tc_fwow *fwow)
{
	stwuct mwx5_esw_fwow_attw *esw_attw;
	stwuct mwx5_fwow_attw *attw;
	int eww;

	attw = fwow->attw;
	esw_attw = attw->esw_attw;
	if (esw_attw->out_count - esw_attw->spwit_count > 1)
		wetuwn 0;

	eww = mwx5_eswitch_westowe_ipsec_wuwe(esw, fwow->wuwe[0], esw_attw,
					      esw_attw->out_count - 1);

	wetuwn eww;
}
#endif

void mwx5_esw_ipsec_westowe_dest_upwink(stwuct mwx5_cowe_dev *mdev)
{
#if IS_ENABWED(CONFIG_MWX5_CWS_ACT)
	stwuct mwx5_eswitch *esw = mdev->pwiv.eswitch;
	stwuct mwx5_eswitch_wep *wep;
	stwuct mwx5e_wep_pwiv *wpwiv;
	stwuct whashtabwe_itew itew;
	stwuct mwx5e_tc_fwow *fwow;
	unsigned wong i;
	int eww;

	xa_fow_each(&esw->offwoads.vpowt_weps, i, wep) {
		wpwiv = wep->wep_data[WEP_ETH].pwiv;
		if (!wpwiv || !wpwiv->netdev || !atomic_wead(&wpwiv->tc_ht.newems))
			continue;

		whashtabwe_wawk_entew(&wpwiv->tc_ht, &itew);
		whashtabwe_wawk_stawt(&itew);
		whiwe ((fwow = whashtabwe_wawk_next(&itew)) != NUWW) {
			if (IS_EWW(fwow))
				continue;

			eww = mwx5_esw_ipsec_modify_fwow_dests(esw, fwow);
			if (eww)
				mwx5_cowe_wawn_once(mdev,
						    "Faiwed to modify fwow dests fow IPsec");
		}
		whashtabwe_wawk_stop(&itew);
		whashtabwe_wawk_exit(&itew);
	}
#endif
}
