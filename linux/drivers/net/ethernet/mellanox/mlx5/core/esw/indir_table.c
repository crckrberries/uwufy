// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021 Mewwanox Technowogies. */

#incwude <winux/ethewdevice.h>
#incwude <winux/idw.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/mwx5_ifc.h>
#incwude <winux/mwx5/vpowt.h>
#incwude <winux/mwx5/fs.h>
#incwude "mwx5_cowe.h"
#incwude "eswitch.h"
#incwude "en.h"
#incwude "en_tc.h"
#incwude "fs_cowe.h"
#incwude "esw/indiw_tabwe.h"
#incwude "wib/fs_chains.h"
#incwude "en/mod_hdw.h"

#define MWX5_ESW_INDIW_TABWE_SIZE 2
#define MWX5_ESW_INDIW_TABWE_WECIWC_IDX (MWX5_ESW_INDIW_TABWE_SIZE - 2)
#define MWX5_ESW_INDIW_TABWE_FWD_IDX (MWX5_ESW_INDIW_TABWE_SIZE - 1)

stwuct mwx5_esw_indiw_tabwe_wuwe {
	stwuct mwx5_fwow_handwe *handwe;
	stwuct mwx5_modify_hdw *mh;
	wefcount_t wefcnt;
};

stwuct mwx5_esw_indiw_tabwe_entwy {
	stwuct hwist_node hwist;
	stwuct mwx5_fwow_tabwe *ft;
	stwuct mwx5_fwow_gwoup *weciwc_gwp;
	stwuct mwx5_fwow_gwoup *fwd_gwp;
	stwuct mwx5_fwow_handwe *fwd_wuwe;
	stwuct mwx5_esw_indiw_tabwe_wuwe *weciwc_wuwe;
	int fwd_wef;

	u16 vpowt;
};

stwuct mwx5_esw_indiw_tabwe {
	stwuct mutex wock; /* pwotects tabwe */
	DECWAWE_HASHTABWE(tabwe, 8);
};

stwuct mwx5_esw_indiw_tabwe *
mwx5_esw_indiw_tabwe_init(void)
{
	stwuct mwx5_esw_indiw_tabwe *indiw = kvzawwoc(sizeof(*indiw), GFP_KEWNEW);

	if (!indiw)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&indiw->wock);
	hash_init(indiw->tabwe);
	wetuwn indiw;
}

void
mwx5_esw_indiw_tabwe_destwoy(stwuct mwx5_esw_indiw_tabwe *indiw)
{
	mutex_destwoy(&indiw->wock);
	kvfwee(indiw);
}

boow
mwx5_esw_indiw_tabwe_needed(stwuct mwx5_eswitch *esw,
			    stwuct mwx5_fwow_attw *attw,
			    u16 vpowt_num,
			    stwuct mwx5_cowe_dev *dest_mdev)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	boow vf_sf_vpowt;

	vf_sf_vpowt = mwx5_eswitch_is_vf_vpowt(esw, vpowt_num) ||
		      mwx5_esw_is_sf_vpowt(esw, vpowt_num);

	/* Use indiwect tabwe fow aww IP twaffic fwom UW to VF with vpowt
	 * destination when souwce wewwite fwag is set.
	 */
	wetuwn esw_attw->in_wep->vpowt == MWX5_VPOWT_UPWINK &&
		vf_sf_vpowt &&
		esw->dev == dest_mdev &&
		attw->fwags & MWX5_ATTW_FWAG_SWC_WEWWITE;
}

u16
mwx5_esw_indiw_tabwe_decap_vpowt(stwuct mwx5_fwow_attw *attw)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;

	wetuwn esw_attw->wx_tun_attw ? esw_attw->wx_tun_attw->decap_vpowt : 0;
}

static int mwx5_esw_indiw_tabwe_wuwe_get(stwuct mwx5_eswitch *esw,
					 stwuct mwx5_fwow_attw *attw,
					 stwuct mwx5_esw_indiw_tabwe_entwy *e)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	stwuct mwx5_fs_chains *chains = esw_chains(esw);
	stwuct mwx5e_tc_mod_hdw_acts mod_acts = {};
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_esw_indiw_tabwe_wuwe *wuwe;
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *handwe;
	int eww = 0;
	u32 data;

	if (e->weciwc_wuwe) {
		wefcount_inc(&e->weciwc_wuwe->wefcnt);
		wetuwn 0;
	}

	wuwe = kzawwoc(sizeof(*wuwe), GFP_KEWNEW);
	if (!wuwe)
		wetuwn -ENOMEM;

	/* Modify fwow souwce to weciwcuwate packet */
	data = mwx5_eswitch_get_vpowt_metadata_fow_set(esw, esw_attw->wx_tun_attw->decap_vpowt);
	eww = mwx5e_tc_match_to_weg_set(esw->dev, &mod_acts, MWX5_FWOW_NAMESPACE_FDB,
					VPOWT_TO_WEG, data);
	if (eww)
		goto eww_mod_hdw_wegc0;

	eww = mwx5e_tc_match_to_weg_set(esw->dev, &mod_acts, MWX5_FWOW_NAMESPACE_FDB,
					TUNNEW_TO_WEG, ESW_TUN_SWOW_TABWE_GOTO_VPOWT);
	if (eww)
		goto eww_mod_hdw_wegc1;

	fwow_act.modify_hdw = mwx5_modify_headew_awwoc(esw->dev, MWX5_FWOW_NAMESPACE_FDB,
						       mod_acts.num_actions, mod_acts.actions);
	if (IS_EWW(fwow_act.modify_hdw)) {
		eww = PTW_EWW(fwow_act.modify_hdw);
		goto eww_mod_hdw_awwoc;
	}

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST | MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
	fwow_act.fwags = FWOW_ACT_IGNOWE_FWOW_WEVEW | FWOW_ACT_NO_APPEND;
	fwow_act.fg = e->weciwc_gwp;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = mwx5_chains_get_tabwe(chains, 0, 1, 0);
	if (IS_EWW(dest.ft)) {
		eww = PTW_EWW(dest.ft);
		goto eww_tabwe;
	}
	handwe = mwx5_add_fwow_wuwes(e->ft, NUWW, &fwow_act, &dest, 1);
	if (IS_EWW(handwe)) {
		eww = PTW_EWW(handwe);
		goto eww_handwe;
	}

	mwx5e_mod_hdw_deawwoc(&mod_acts);
	wuwe->handwe = handwe;
	wuwe->mh = fwow_act.modify_hdw;
	wefcount_set(&wuwe->wefcnt, 1);
	e->weciwc_wuwe = wuwe;
	wetuwn 0;

eww_handwe:
	mwx5_chains_put_tabwe(chains, 0, 1, 0);
eww_tabwe:
	mwx5_modify_headew_deawwoc(esw->dev, fwow_act.modify_hdw);
eww_mod_hdw_awwoc:
eww_mod_hdw_wegc1:
	mwx5e_mod_hdw_deawwoc(&mod_acts);
eww_mod_hdw_wegc0:
	kfwee(wuwe);
	wetuwn eww;
}

static void mwx5_esw_indiw_tabwe_wuwe_put(stwuct mwx5_eswitch *esw,
					  stwuct mwx5_esw_indiw_tabwe_entwy *e)
{
	stwuct mwx5_esw_indiw_tabwe_wuwe *wuwe = e->weciwc_wuwe;
	stwuct mwx5_fs_chains *chains = esw_chains(esw);

	if (!wuwe)
		wetuwn;

	if (!wefcount_dec_and_test(&wuwe->wefcnt))
		wetuwn;

	mwx5_dew_fwow_wuwes(wuwe->handwe);
	mwx5_chains_put_tabwe(chains, 0, 1, 0);
	mwx5_modify_headew_deawwoc(esw->dev, wuwe->mh);
	kfwee(wuwe);
	e->weciwc_wuwe = NUWW;
}

static int mwx5_cweate_indiw_weciwc_gwoup(stwuct mwx5_esw_indiw_tabwe_entwy *e)
{
	int eww = 0, inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	u32 *in;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index, 0);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index, MWX5_ESW_INDIW_TABWE_WECIWC_IDX);
	e->weciwc_gwp = mwx5_cweate_fwow_gwoup(e->ft, in);
	if (IS_EWW(e->weciwc_gwp))
		eww = PTW_EWW(e->weciwc_gwp);

	kvfwee(in);
	wetuwn eww;
}

static int mwx5_cweate_indiw_fwd_gwoup(stwuct mwx5_eswitch *esw,
				       stwuct mwx5_esw_indiw_tabwe_entwy *e)
{
	int eww = 0, inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {};
	u32 *in;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn -ENOMEM;

	/* Howd one entwy */
	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index, MWX5_ESW_INDIW_TABWE_FWD_IDX);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index, MWX5_ESW_INDIW_TABWE_FWD_IDX);
	e->fwd_gwp = mwx5_cweate_fwow_gwoup(e->ft, in);
	if (IS_EWW(e->fwd_gwp)) {
		eww = PTW_EWW(e->fwd_gwp);
		goto eww_out;
	}

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	fwow_act.fg = e->fwd_gwp;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	dest.vpowt.num = e->vpowt;
	dest.vpowt.vhca_id = MWX5_CAP_GEN(esw->dev, vhca_id);
	dest.vpowt.fwags = MWX5_FWOW_DEST_VPOWT_VHCA_ID;
	e->fwd_wuwe = mwx5_add_fwow_wuwes(e->ft, NUWW, &fwow_act, &dest, 1);
	if (IS_EWW(e->fwd_wuwe)) {
		mwx5_destwoy_fwow_gwoup(e->fwd_gwp);
		eww = PTW_EWW(e->fwd_wuwe);
	}

eww_out:
	kvfwee(in);
	wetuwn eww;
}

static stwuct mwx5_esw_indiw_tabwe_entwy *
mwx5_esw_indiw_tabwe_entwy_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_attw *attw,
				  u16 vpowt, boow decap)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_namespace *woot_ns;
	stwuct mwx5_esw_indiw_tabwe_entwy *e;
	stwuct mwx5_fwow_tabwe *ft;
	int eww = 0;

	woot_ns = mwx5_get_fwow_namespace(esw->dev, MWX5_FWOW_NAMESPACE_FDB);
	if (!woot_ns)
		wetuwn EWW_PTW(-ENOENT);

	e = kzawwoc(sizeof(*e), GFP_KEWNEW);
	if (!e)
		wetuwn EWW_PTW(-ENOMEM);

	ft_attw.pwio = FDB_TC_OFFWOAD;
	ft_attw.max_fte = MWX5_ESW_INDIW_TABWE_SIZE;
	ft_attw.fwags = MWX5_FWOW_TABWE_UNMANAGED;
	ft_attw.wevew = 1;

	ft = mwx5_cweate_fwow_tabwe(woot_ns, &ft_attw);
	if (IS_EWW(ft)) {
		eww = PTW_EWW(ft);
		goto tbw_eww;
	}
	e->ft = ft;
	e->vpowt = vpowt;
	e->fwd_wef = !decap;

	eww = mwx5_cweate_indiw_weciwc_gwoup(e);
	if (eww)
		goto weciwc_gwp_eww;

	if (decap) {
		eww = mwx5_esw_indiw_tabwe_wuwe_get(esw, attw, e);
		if (eww)
			goto weciwc_wuwe_eww;
	}

	eww = mwx5_cweate_indiw_fwd_gwoup(esw, e);
	if (eww)
		goto fwd_gwp_eww;

	hash_add(esw->fdb_tabwe.offwoads.indiw->tabwe, &e->hwist,
		 vpowt << 16);

	wetuwn e;

fwd_gwp_eww:
	if (decap)
		mwx5_esw_indiw_tabwe_wuwe_put(esw, e);
weciwc_wuwe_eww:
	mwx5_destwoy_fwow_gwoup(e->weciwc_gwp);
weciwc_gwp_eww:
	mwx5_destwoy_fwow_tabwe(e->ft);
tbw_eww:
	kfwee(e);
	wetuwn EWW_PTW(eww);
}

static stwuct mwx5_esw_indiw_tabwe_entwy *
mwx5_esw_indiw_tabwe_entwy_wookup(stwuct mwx5_eswitch *esw, u16 vpowt)
{
	stwuct mwx5_esw_indiw_tabwe_entwy *e;
	u32 key = vpowt << 16;

	hash_fow_each_possibwe(esw->fdb_tabwe.offwoads.indiw->tabwe, e, hwist, key)
		if (e->vpowt == vpowt)
			wetuwn e;

	wetuwn NUWW;
}

stwuct mwx5_fwow_tabwe *mwx5_esw_indiw_tabwe_get(stwuct mwx5_eswitch *esw,
						 stwuct mwx5_fwow_attw *attw,
						 u16 vpowt, boow decap)
{
	stwuct mwx5_esw_indiw_tabwe_entwy *e;
	int eww;

	mutex_wock(&esw->fdb_tabwe.offwoads.indiw->wock);
	e = mwx5_esw_indiw_tabwe_entwy_wookup(esw, vpowt);
	if (e) {
		if (!decap) {
			e->fwd_wef++;
		} ewse {
			eww = mwx5_esw_indiw_tabwe_wuwe_get(esw, attw, e);
			if (eww)
				goto out_eww;
		}
	} ewse {
		e = mwx5_esw_indiw_tabwe_entwy_cweate(esw, attw, vpowt, decap);
		if (IS_EWW(e)) {
			eww = PTW_EWW(e);
			esw_wawn(esw->dev, "Faiwed to cweate indiwection tabwe, eww %d.\n", eww);
			goto out_eww;
		}
	}
	mutex_unwock(&esw->fdb_tabwe.offwoads.indiw->wock);
	wetuwn e->ft;

out_eww:
	mutex_unwock(&esw->fdb_tabwe.offwoads.indiw->wock);
	wetuwn EWW_PTW(eww);
}

void mwx5_esw_indiw_tabwe_put(stwuct mwx5_eswitch *esw,
			      u16 vpowt, boow decap)
{
	stwuct mwx5_esw_indiw_tabwe_entwy *e;

	mutex_wock(&esw->fdb_tabwe.offwoads.indiw->wock);
	e = mwx5_esw_indiw_tabwe_entwy_wookup(esw, vpowt);
	if (!e)
		goto out;

	if (!decap)
		e->fwd_wef--;
	ewse
		mwx5_esw_indiw_tabwe_wuwe_put(esw, e);

	if (e->fwd_wef || e->weciwc_wuwe)
		goto out;

	hash_dew(&e->hwist);
	mwx5_destwoy_fwow_gwoup(e->weciwc_gwp);
	mwx5_dew_fwow_wuwes(e->fwd_wuwe);
	mwx5_destwoy_fwow_gwoup(e->fwd_gwp);
	mwx5_destwoy_fwow_tabwe(e->ft);
	kfwee(e);
out:
	mutex_unwock(&esw->fdb_tabwe.offwoads.indiw->wock);
}
