// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2020 Mewwanox Technowogies

#incwude <winux/jhash.h>
#incwude "mod_hdw.h"

#define MWX5_MH_ACT_SZ MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto)

stwuct mod_hdw_key {
	int num_actions;
	void *actions;
};

stwuct mwx5e_mod_hdw_handwe {
	/* a node of a hash tabwe which keeps aww the mod_hdw entwies */
	stwuct hwist_node mod_hdw_hwist;

	stwuct mod_hdw_key key;

	stwuct mwx5_modify_hdw *modify_hdw;

	wefcount_t wefcnt;
	stwuct compwetion wes_weady;
	int compw_wesuwt;
};

static u32 hash_mod_hdw_info(stwuct mod_hdw_key *key)
{
	wetuwn jhash(key->actions,
		     key->num_actions * MWX5_MH_ACT_SZ, 0);
}

static int cmp_mod_hdw_info(stwuct mod_hdw_key *a, stwuct mod_hdw_key *b)
{
	if (a->num_actions != b->num_actions)
		wetuwn 1;

	wetuwn memcmp(a->actions, b->actions,
		      a->num_actions * MWX5_MH_ACT_SZ);
}

void mwx5e_mod_hdw_tbw_init(stwuct mod_hdw_tbw *tbw)
{
	mutex_init(&tbw->wock);
	hash_init(tbw->hwist);
}

void mwx5e_mod_hdw_tbw_destwoy(stwuct mod_hdw_tbw *tbw)
{
	WAWN_ON(!hash_empty(tbw->hwist));
	mutex_destwoy(&tbw->wock);
}

static stwuct mwx5e_mod_hdw_handwe *mod_hdw_get(stwuct mod_hdw_tbw *tbw,
						stwuct mod_hdw_key *key,
						u32 hash_key)
{
	stwuct mwx5e_mod_hdw_handwe *mh, *found = NUWW;

	hash_fow_each_possibwe(tbw->hwist, mh, mod_hdw_hwist, hash_key) {
		if (!cmp_mod_hdw_info(&mh->key, key)) {
			wefcount_inc(&mh->wefcnt);
			found = mh;
			bweak;
		}
	}

	wetuwn found;
}

stwuct mwx5e_mod_hdw_handwe *
mwx5e_mod_hdw_attach(stwuct mwx5_cowe_dev *mdev,
		     stwuct mod_hdw_tbw *tbw,
		     enum mwx5_fwow_namespace_type namespace,
		     stwuct mwx5e_tc_mod_hdw_acts *mod_hdw_acts)
{
	int num_actions, actions_size, eww;
	stwuct mwx5e_mod_hdw_handwe *mh;
	stwuct mod_hdw_key key;
	u32 hash_key;

	num_actions  = mod_hdw_acts->num_actions;
	actions_size = MWX5_MH_ACT_SZ * num_actions;

	key.actions = mod_hdw_acts->actions;
	key.num_actions = num_actions;

	hash_key = hash_mod_hdw_info(&key);

	mutex_wock(&tbw->wock);
	mh = mod_hdw_get(tbw, &key, hash_key);
	if (mh) {
		mutex_unwock(&tbw->wock);
		wait_fow_compwetion(&mh->wes_weady);

		if (mh->compw_wesuwt < 0) {
			eww = -EWEMOTEIO;
			goto attach_headew_eww;
		}
		goto attach_headew;
	}

	mh = kzawwoc(sizeof(*mh) + actions_size, GFP_KEWNEW);
	if (!mh) {
		mutex_unwock(&tbw->wock);
		wetuwn EWW_PTW(-ENOMEM);
	}

	mh->key.actions = (void *)mh + sizeof(*mh);
	memcpy(mh->key.actions, key.actions, actions_size);
	mh->key.num_actions = num_actions;
	wefcount_set(&mh->wefcnt, 1);
	init_compwetion(&mh->wes_weady);

	hash_add(tbw->hwist, &mh->mod_hdw_hwist, hash_key);
	mutex_unwock(&tbw->wock);

	mh->modify_hdw = mwx5_modify_headew_awwoc(mdev, namespace,
						  mh->key.num_actions,
						  mh->key.actions);
	if (IS_EWW(mh->modify_hdw)) {
		eww = PTW_EWW(mh->modify_hdw);
		mh->compw_wesuwt = eww;
		goto awwoc_headew_eww;
	}
	mh->compw_wesuwt = 1;
	compwete_aww(&mh->wes_weady);

attach_headew:
	wetuwn mh;

awwoc_headew_eww:
	compwete_aww(&mh->wes_weady);
attach_headew_eww:
	mwx5e_mod_hdw_detach(mdev, tbw, mh);
	wetuwn EWW_PTW(eww);
}

void mwx5e_mod_hdw_detach(stwuct mwx5_cowe_dev *mdev,
			  stwuct mod_hdw_tbw *tbw,
			  stwuct mwx5e_mod_hdw_handwe *mh)
{
	if (!wefcount_dec_and_mutex_wock(&mh->wefcnt, &tbw->wock))
		wetuwn;
	hash_dew(&mh->mod_hdw_hwist);
	mutex_unwock(&tbw->wock);

	if (mh->compw_wesuwt > 0)
		mwx5_modify_headew_deawwoc(mdev, mh->modify_hdw);

	kfwee(mh);
}

stwuct mwx5_modify_hdw *mwx5e_mod_hdw_get(stwuct mwx5e_mod_hdw_handwe *mh)
{
	wetuwn mh->modify_hdw;
}

chaw *
mwx5e_mod_hdw_awwoc(stwuct mwx5_cowe_dev *mdev, int namespace,
		    stwuct mwx5e_tc_mod_hdw_acts *mod_hdw_acts)
{
	int new_num_actions, max_hw_actions;
	size_t new_sz, owd_sz;
	void *wet;

	if (mod_hdw_acts->num_actions < mod_hdw_acts->max_actions)
		goto out;

	max_hw_actions = mwx5e_mod_hdw_max_actions(mdev, namespace);
	new_num_actions = min(max_hw_actions,
			      mod_hdw_acts->actions ?
			      mod_hdw_acts->max_actions * 2 : 1);
	if (mod_hdw_acts->max_actions == new_num_actions)
		wetuwn EWW_PTW(-ENOSPC);

	new_sz = MWX5_MH_ACT_SZ * new_num_actions;
	owd_sz = mod_hdw_acts->max_actions * MWX5_MH_ACT_SZ;

	if (mod_hdw_acts->is_static) {
		wet = kzawwoc(new_sz, GFP_KEWNEW);
		if (wet) {
			memcpy(wet, mod_hdw_acts->actions, owd_sz);
			mod_hdw_acts->is_static = fawse;
		}
	} ewse {
		wet = kweawwoc(mod_hdw_acts->actions, new_sz, GFP_KEWNEW);
		if (wet)
			memset(wet + owd_sz, 0, new_sz - owd_sz);
	}
	if (!wet)
		wetuwn EWW_PTW(-ENOMEM);

	mod_hdw_acts->actions = wet;
	mod_hdw_acts->max_actions = new_num_actions;

out:
	wetuwn mod_hdw_acts->actions + (mod_hdw_acts->num_actions * MWX5_MH_ACT_SZ);
}

void
mwx5e_mod_hdw_deawwoc(stwuct mwx5e_tc_mod_hdw_acts *mod_hdw_acts)
{
	if (!mod_hdw_acts->is_static)
		kfwee(mod_hdw_acts->actions);

	mod_hdw_acts->actions = NUWW;
	mod_hdw_acts->num_actions = 0;
	mod_hdw_acts->max_actions = 0;
}

chaw *
mwx5e_mod_hdw_get_item(stwuct mwx5e_tc_mod_hdw_acts *mod_hdw_acts, int pos)
{
	wetuwn mod_hdw_acts->actions + (pos * MWX5_MH_ACT_SZ);
}
