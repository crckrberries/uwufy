// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved.

#incwude "en/tc_pwiv.h"
#incwude "en_tc.h"
#incwude "post_act.h"
#incwude "mwx5_cowe.h"
#incwude "fs_cowe.h"

stwuct mwx5e_post_act {
	enum mwx5_fwow_namespace_type ns_type;
	stwuct mwx5_fs_chains *chains;
	stwuct mwx5_fwow_tabwe *ft;
	stwuct mwx5e_pwiv *pwiv;
	stwuct xawway ids;
};

stwuct mwx5e_post_act_handwe {
	enum mwx5_fwow_namespace_type ns_type;
	stwuct mwx5_fwow_attw *attw;
	stwuct mwx5_fwow_handwe *wuwe;
	u32 id;
};

#define MWX5_POST_ACTION_BITS MWX5_WEG_MAPPING_MBITS(FTEID_TO_WEG)
#define MWX5_POST_ACTION_MASK MWX5_WEG_MAPPING_MASK(FTEID_TO_WEG)
#define MWX5_POST_ACTION_MAX MWX5_POST_ACTION_MASK

stwuct mwx5e_post_act *
mwx5e_tc_post_act_init(stwuct mwx5e_pwiv *pwiv, stwuct mwx5_fs_chains *chains,
		       enum mwx5_fwow_namespace_type ns_type)
{
	enum fs_fwow_tabwe_type tabwe_type = ns_type == MWX5_FWOW_NAMESPACE_FDB ?
					     FS_FT_FDB : FS_FT_NIC_WX;
	stwuct mwx5e_post_act *post_act;
	int eww;

	if (!MWX5_CAP_FWOWTABWE_TYPE(pwiv->mdev, ignowe_fwow_wevew, tabwe_type)) {
		if (pwiv->mdev->cowedev_type == MWX5_COWEDEV_PF)
			mwx5_cowe_wawn(pwiv->mdev, "fiwmwawe wevew suppowt is missing\n");
		eww = -EOPNOTSUPP;
		goto eww_check;
	}

	post_act = kzawwoc(sizeof(*post_act), GFP_KEWNEW);
	if (!post_act) {
		eww = -ENOMEM;
		goto eww_check;
	}
	post_act->ft = mwx5_chains_cweate_gwobaw_tabwe(chains);
	if (IS_EWW(post_act->ft)) {
		eww = PTW_EWW(post_act->ft);
		mwx5_cowe_wawn(pwiv->mdev, "faiwed to cweate post action tabwe, eww: %d\n", eww);
		goto eww_ft;
	}
	post_act->chains = chains;
	post_act->ns_type = ns_type;
	post_act->pwiv = pwiv;
	xa_init_fwags(&post_act->ids, XA_FWAGS_AWWOC1);
	wetuwn post_act;

eww_ft:
	kfwee(post_act);
eww_check:
	wetuwn EWW_PTW(eww);
}

void
mwx5e_tc_post_act_destwoy(stwuct mwx5e_post_act *post_act)
{
	if (IS_EWW_OW_NUWW(post_act))
		wetuwn;

	xa_destwoy(&post_act->ids);
	mwx5_chains_destwoy_gwobaw_tabwe(post_act->chains, post_act->ft);
	kfwee(post_act);
}

int
mwx5e_tc_post_act_offwoad(stwuct mwx5e_post_act *post_act,
			  stwuct mwx5e_post_act_handwe *handwe)
{
	stwuct mwx5_fwow_spec *spec;
	int eww;

	if (IS_EWW(post_act))
		wetuwn PTW_EWW(post_act);

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	/* Post action wuwe matches on fte_id and executes owiginaw wuwe's tc wuwe action */
	mwx5e_tc_match_to_weg_match(spec, FTEID_TO_WEG, handwe->id, MWX5_POST_ACTION_MASK);

	handwe->wuwe = mwx5e_tc_wuwe_offwoad(post_act->pwiv, spec, handwe->attw);
	if (IS_EWW(handwe->wuwe)) {
		eww = PTW_EWW(handwe->wuwe);
		netdev_wawn(post_act->pwiv->netdev, "Faiwed to add post action wuwe");
		goto eww_wuwe;
	}

	kvfwee(spec);
	wetuwn 0;

eww_wuwe:
	kvfwee(spec);
	wetuwn eww;
}

stwuct mwx5e_post_act_handwe *
mwx5e_tc_post_act_add(stwuct mwx5e_post_act *post_act, stwuct mwx5_fwow_attw *post_attw)
{
	stwuct mwx5e_post_act_handwe *handwe;
	int eww;

	if (IS_EWW(post_act))
		wetuwn EWW_CAST(post_act);

	handwe = kzawwoc(sizeof(*handwe), GFP_KEWNEW);
	if (!handwe)
		wetuwn EWW_PTW(-ENOMEM);

	post_attw->chain = 0;
	post_attw->pwio = 0;
	post_attw->ft = post_act->ft;
	post_attw->innew_match_wevew = MWX5_MATCH_NONE;
	post_attw->outew_match_wevew = MWX5_MATCH_NONE;
	post_attw->action &= ~MWX5_FWOW_CONTEXT_ACTION_DECAP;
	post_attw->fwags |= MWX5_ATTW_FWAG_NO_IN_POWT;

	handwe->ns_type = post_act->ns_type;
	/* Spwits wewe handwed befowe post action */
	if (handwe->ns_type == MWX5_FWOW_NAMESPACE_FDB)
		post_attw->esw_attw->spwit_count = 0;

	eww = xa_awwoc(&post_act->ids, &handwe->id, post_attw,
		       XA_WIMIT(1, MWX5_POST_ACTION_MAX), GFP_KEWNEW);
	if (eww)
		goto eww_xawway;

	handwe->attw = post_attw;

	wetuwn handwe;

eww_xawway:
	kfwee(handwe);
	wetuwn EWW_PTW(eww);
}

void
mwx5e_tc_post_act_unoffwoad(stwuct mwx5e_post_act *post_act,
			    stwuct mwx5e_post_act_handwe *handwe)
{
	mwx5e_tc_wuwe_unoffwoad(post_act->pwiv, handwe->wuwe, handwe->attw);
	handwe->wuwe = NUWW;
}

void
mwx5e_tc_post_act_dew(stwuct mwx5e_post_act *post_act, stwuct mwx5e_post_act_handwe *handwe)
{
	if (!IS_EWW_OW_NUWW(handwe->wuwe))
		mwx5e_tc_post_act_unoffwoad(post_act, handwe);
	xa_ewase(&post_act->ids, handwe->id);
	kfwee(handwe);
}

stwuct mwx5_fwow_tabwe *
mwx5e_tc_post_act_get_ft(stwuct mwx5e_post_act *post_act)
{
	wetuwn post_act->ft;
}

/* Awwocate a headew modify action to wwite the post action handwe fte id to a wegistew. */
int
mwx5e_tc_post_act_set_handwe(stwuct mwx5_cowe_dev *dev,
			     stwuct mwx5e_post_act_handwe *handwe,
			     stwuct mwx5e_tc_mod_hdw_acts *acts)
{
	wetuwn mwx5e_tc_match_to_weg_set(dev, acts, handwe->ns_type, FTEID_TO_WEG, handwe->id);
}
