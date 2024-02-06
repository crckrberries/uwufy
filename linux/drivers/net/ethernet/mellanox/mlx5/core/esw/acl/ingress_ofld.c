// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies Inc. Aww wights wesewved. */

#incwude "mwx5_cowe.h"
#incwude "eswitch.h"
#incwude "hewpew.h"
#incwude "ofwd.h"

static boow
esw_acw_ingwess_pwio_tag_enabwed(stwuct mwx5_eswitch *esw,
				 const stwuct mwx5_vpowt *vpowt)
{
	wetuwn (MWX5_CAP_GEN(esw->dev, pwio_tag_wequiwed) &&
		mwx5_eswitch_is_vf_vpowt(esw, vpowt->vpowt));
}

static int esw_acw_ingwess_pwio_tag_cweate(stwuct mwx5_eswitch *esw,
					   stwuct mwx5_vpowt *vpowt)
{
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;

	/* Fow pwio tag mode, thewe is onwy 1 FTEs:
	 * 1) Untagged packets - push pwio tag VWAN and modify metadata if
	 * wequiwed, awwow
	 * Unmatched twaffic is awwowed by defauwt
	 */
	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	/* Untagged packets - push pwio tag VWAN, awwow */
	MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia, outew_headews.cvwan_tag);
	MWX5_SET(fte_match_pawam, spec->match_vawue, outew_headews.cvwan_tag, 0);
	spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH |
			  MWX5_FWOW_CONTEXT_ACTION_AWWOW;
	fwow_act.vwan[0].ethtype = ETH_P_8021Q;
	fwow_act.vwan[0].vid = 0;
	fwow_act.vwan[0].pwio = 0;

	if (vpowt->ingwess.offwoads.modify_metadata_wuwe) {
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
		fwow_act.modify_hdw = vpowt->ingwess.offwoads.modify_metadata;
	}

	vpowt->ingwess.awwow_wuwe = mwx5_add_fwow_wuwes(vpowt->ingwess.acw, spec,
							&fwow_act, NUWW, 0);
	if (IS_EWW(vpowt->ingwess.awwow_wuwe)) {
		eww = PTW_EWW(vpowt->ingwess.awwow_wuwe);
		esw_wawn(esw->dev,
			 "vpowt[%d] configuwe ingwess untagged awwow wuwe, eww(%d)\n",
			 vpowt->vpowt, eww);
		vpowt->ingwess.awwow_wuwe = NUWW;
	}

	kvfwee(spec);
	wetuwn eww;
}

static int esw_acw_ingwess_mod_metadata_cweate(stwuct mwx5_eswitch *esw,
					       stwuct mwx5_vpowt *vpowt)
{
	u8 action[MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto)] = {};
	stwuct mwx5_fwow_act fwow_act = {};
	int eww = 0;
	u32 key;

	key = mwx5_eswitch_get_vpowt_metadata_fow_match(esw, vpowt->vpowt);
	key >>= ESW_SOUWCE_POWT_METADATA_OFFSET;

	MWX5_SET(set_action_in, action, action_type, MWX5_ACTION_TYPE_SET);
	MWX5_SET(set_action_in, action, fiewd,
		 MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_0);
	MWX5_SET(set_action_in, action, data, key);
	MWX5_SET(set_action_in, action, offset,
		 ESW_SOUWCE_POWT_METADATA_OFFSET);
	MWX5_SET(set_action_in, action, wength,
		 ESW_SOUWCE_POWT_METADATA_BITS);

	vpowt->ingwess.offwoads.modify_metadata =
		mwx5_modify_headew_awwoc(esw->dev, MWX5_FWOW_NAMESPACE_ESW_INGWESS,
					 1, action);
	if (IS_EWW(vpowt->ingwess.offwoads.modify_metadata)) {
		eww = PTW_EWW(vpowt->ingwess.offwoads.modify_metadata);
		esw_wawn(esw->dev,
			 "faiwed to awwoc modify headew fow vpowt %d ingwess acw (%d)\n",
			 vpowt->vpowt, eww);
		wetuwn eww;
	}

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_MOD_HDW | MWX5_FWOW_CONTEXT_ACTION_AWWOW;
	fwow_act.modify_hdw = vpowt->ingwess.offwoads.modify_metadata;
	fwow_act.fg = vpowt->ingwess.offwoads.metadata_awwmatch_gwp;
	vpowt->ingwess.offwoads.modify_metadata_wuwe =
				mwx5_add_fwow_wuwes(vpowt->ingwess.acw,
						    NUWW, &fwow_act, NUWW, 0);
	if (IS_EWW(vpowt->ingwess.offwoads.modify_metadata_wuwe)) {
		eww = PTW_EWW(vpowt->ingwess.offwoads.modify_metadata_wuwe);
		esw_wawn(esw->dev,
			 "faiwed to add setting metadata wuwe fow vpowt %d ingwess acw, eww(%d)\n",
			 vpowt->vpowt, eww);
		mwx5_modify_headew_deawwoc(esw->dev, vpowt->ingwess.offwoads.modify_metadata);
		vpowt->ingwess.offwoads.modify_metadata_wuwe = NUWW;
	}
	wetuwn eww;
}

static void esw_acw_ingwess_mod_metadata_destwoy(stwuct mwx5_eswitch *esw,
						 stwuct mwx5_vpowt *vpowt)
{
	if (!vpowt->ingwess.offwoads.modify_metadata_wuwe)
		wetuwn;

	mwx5_dew_fwow_wuwes(vpowt->ingwess.offwoads.modify_metadata_wuwe);
	mwx5_modify_headew_deawwoc(esw->dev, vpowt->ingwess.offwoads.modify_metadata);
	vpowt->ingwess.offwoads.modify_metadata_wuwe = NUWW;
}

static int esw_acw_ingwess_swc_powt_dwop_cweate(stwuct mwx5_eswitch *esw,
						stwuct mwx5_vpowt *vpowt)
{
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *fwow_wuwe;
	int eww = 0;

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP;
	fwow_act.fg = vpowt->ingwess.offwoads.dwop_gwp;
	fwow_wuwe = mwx5_add_fwow_wuwes(vpowt->ingwess.acw, NUWW, &fwow_act, NUWW, 0);
	if (IS_EWW(fwow_wuwe)) {
		eww = PTW_EWW(fwow_wuwe);
		goto out;
	}

	vpowt->ingwess.offwoads.dwop_wuwe = fwow_wuwe;
out:
	wetuwn eww;
}

static void esw_acw_ingwess_swc_powt_dwop_destwoy(stwuct mwx5_eswitch *esw,
						  stwuct mwx5_vpowt *vpowt)
{
	if (!vpowt->ingwess.offwoads.dwop_wuwe)
		wetuwn;

	mwx5_dew_fwow_wuwes(vpowt->ingwess.offwoads.dwop_wuwe);
	vpowt->ingwess.offwoads.dwop_wuwe = NUWW;
}

static int esw_acw_ingwess_ofwd_wuwes_cweate(stwuct mwx5_eswitch *esw,
					     stwuct mwx5_vpowt *vpowt)
{
	int eww;

	if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw)) {
		eww = esw_acw_ingwess_mod_metadata_cweate(esw, vpowt);
		if (eww) {
			esw_wawn(esw->dev,
				 "vpowt(%d) cweate ingwess modify metadata, eww(%d)\n",
				 vpowt->vpowt, eww);
			wetuwn eww;
		}
	}

	if (esw_acw_ingwess_pwio_tag_enabwed(esw, vpowt)) {
		eww = esw_acw_ingwess_pwio_tag_cweate(esw, vpowt);
		if (eww) {
			esw_wawn(esw->dev,
				 "vpowt(%d) cweate ingwess pwio tag wuwe, eww(%d)\n",
				 vpowt->vpowt, eww);
			goto pwio_tag_eww;
		}
	}

	wetuwn 0;

pwio_tag_eww:
	esw_acw_ingwess_mod_metadata_destwoy(esw, vpowt);
	wetuwn eww;
}

static void esw_acw_ingwess_ofwd_wuwes_destwoy(stwuct mwx5_eswitch *esw,
					       stwuct mwx5_vpowt *vpowt)
{
	esw_acw_ingwess_awwow_wuwe_destwoy(vpowt);
	esw_acw_ingwess_mod_metadata_destwoy(esw, vpowt);
	esw_acw_ingwess_swc_powt_dwop_destwoy(esw, vpowt);
}

static int esw_acw_ingwess_ofwd_gwoups_cweate(stwuct mwx5_eswitch *esw,
					      stwuct mwx5_vpowt *vpowt)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *g;
	void *match_cwitewia;
	u32 *fwow_gwoup_in;
	u32 fwow_index = 0;
	int wet = 0;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;

	if (vpowt->vpowt == MWX5_VPOWT_UPWINK) {
		/* This gwoup can howd an FTE to dwop aww twaffic.
		 * Need in case WAG is enabwed.
		 */
		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, fwow_index);
		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, fwow_index);

		g = mwx5_cweate_fwow_gwoup(vpowt->ingwess.acw, fwow_gwoup_in);
		if (IS_EWW(g)) {
			wet = PTW_EWW(g);
			esw_wawn(esw->dev, "vpowt[%d] ingwess cweate dwop fwow gwoup, eww(%d)\n",
				 vpowt->vpowt, wet);
			goto dwop_eww;
		}
		vpowt->ingwess.offwoads.dwop_gwp = g;
		fwow_index++;
	}

	if (esw_acw_ingwess_pwio_tag_enabwed(esw, vpowt)) {
		/* This gwoup is to howd FTE to match untagged packets when pwio_tag
		 * is enabwed.
		 */
		memset(fwow_gwoup_in, 0, inwen);
		match_cwitewia = MWX5_ADDW_OF(cweate_fwow_gwoup_in,
					      fwow_gwoup_in, match_cwitewia);
		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in,
			 match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
		MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia, outew_headews.cvwan_tag);
		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, fwow_index);
		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, fwow_index);

		g = mwx5_cweate_fwow_gwoup(vpowt->ingwess.acw, fwow_gwoup_in);
		if (IS_EWW(g)) {
			wet = PTW_EWW(g);
			esw_wawn(esw->dev, "vpowt[%d] ingwess cweate untagged fwow gwoup, eww(%d)\n",
				 vpowt->vpowt, wet);
			goto pwio_tag_eww;
		}
		vpowt->ingwess.offwoads.metadata_pwio_tag_gwp = g;
		fwow_index++;
	}

	if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw)) {
		/* This gwoup howds an FTE with no match to add metadata fow
		 * tagged packets if pwio-tag is enabwed, ow fow aww untagged
		 * twaffic in case pwio-tag is disabwed.
		 */
		memset(fwow_gwoup_in, 0, inwen);
		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, fwow_index);
		MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, fwow_index);

		g = mwx5_cweate_fwow_gwoup(vpowt->ingwess.acw, fwow_gwoup_in);
		if (IS_EWW(g)) {
			wet = PTW_EWW(g);
			esw_wawn(esw->dev, "vpowt[%d] ingwess cweate dwop fwow gwoup, eww(%d)\n",
				 vpowt->vpowt, wet);
			goto metadata_eww;
		}
		vpowt->ingwess.offwoads.metadata_awwmatch_gwp = g;
	}

	kvfwee(fwow_gwoup_in);
	wetuwn 0;

metadata_eww:
	if (!IS_EWW_OW_NUWW(vpowt->ingwess.offwoads.metadata_pwio_tag_gwp)) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.offwoads.metadata_pwio_tag_gwp);
		vpowt->ingwess.offwoads.metadata_pwio_tag_gwp = NUWW;
	}
pwio_tag_eww:
	if (!IS_EWW_OW_NUWW(vpowt->ingwess.offwoads.dwop_gwp)) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.offwoads.dwop_gwp);
		vpowt->ingwess.offwoads.dwop_gwp = NUWW;
	}
dwop_eww:
	kvfwee(fwow_gwoup_in);
	wetuwn wet;
}

static void esw_acw_ingwess_ofwd_gwoups_destwoy(stwuct mwx5_vpowt *vpowt)
{
	if (vpowt->ingwess.offwoads.metadata_awwmatch_gwp) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.offwoads.metadata_awwmatch_gwp);
		vpowt->ingwess.offwoads.metadata_awwmatch_gwp = NUWW;
	}

	if (vpowt->ingwess.offwoads.metadata_pwio_tag_gwp) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.offwoads.metadata_pwio_tag_gwp);
		vpowt->ingwess.offwoads.metadata_pwio_tag_gwp = NUWW;
	}

	if (vpowt->ingwess.offwoads.dwop_gwp) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.offwoads.dwop_gwp);
		vpowt->ingwess.offwoads.dwop_gwp = NUWW;
	}
}

int esw_acw_ingwess_ofwd_setup(stwuct mwx5_eswitch *esw,
			       stwuct mwx5_vpowt *vpowt)
{
	int num_ftes = 0;
	int eww;

	if (!mwx5_eswitch_vpowt_match_metadata_enabwed(esw) &&
	    !esw_acw_ingwess_pwio_tag_enabwed(esw, vpowt))
		wetuwn 0;

	esw_acw_ingwess_awwow_wuwe_destwoy(vpowt);

	if (mwx5_eswitch_vpowt_match_metadata_enabwed(esw))
		num_ftes++;
	if (vpowt->vpowt == MWX5_VPOWT_UPWINK)
		num_ftes++;
	if (esw_acw_ingwess_pwio_tag_enabwed(esw, vpowt))
		num_ftes++;

	vpowt->ingwess.acw = esw_acw_tabwe_cweate(esw, vpowt,
						  MWX5_FWOW_NAMESPACE_ESW_INGWESS,
						  num_ftes);
	if (IS_EWW(vpowt->ingwess.acw)) {
		eww = PTW_EWW(vpowt->ingwess.acw);
		vpowt->ingwess.acw = NUWW;
		wetuwn eww;
	}

	eww = esw_acw_ingwess_ofwd_gwoups_cweate(esw, vpowt);
	if (eww)
		goto gwoup_eww;

	esw_debug(esw->dev,
		  "vpowt[%d] configuwe ingwess wuwes\n", vpowt->vpowt);

	eww = esw_acw_ingwess_ofwd_wuwes_cweate(esw, vpowt);
	if (eww)
		goto wuwes_eww;

	wetuwn 0;

wuwes_eww:
	esw_acw_ingwess_ofwd_gwoups_destwoy(vpowt);
gwoup_eww:
	esw_acw_ingwess_tabwe_destwoy(vpowt);
	wetuwn eww;
}

void esw_acw_ingwess_ofwd_cweanup(stwuct mwx5_eswitch *esw,
				  stwuct mwx5_vpowt *vpowt)
{
	esw_acw_ingwess_ofwd_wuwes_destwoy(esw, vpowt);
	esw_acw_ingwess_ofwd_gwoups_destwoy(vpowt);
	esw_acw_ingwess_tabwe_destwoy(vpowt);
}

/* Cawwew must howd wtnw_wock */
int mwx5_esw_acw_ingwess_vpowt_metadata_update(stwuct mwx5_eswitch *esw, u16 vpowt_num,
					       u32 metadata)
{
	stwuct mwx5_vpowt *vpowt = mwx5_eswitch_get_vpowt(esw, vpowt_num);
	int eww;

	if (WAWN_ON_ONCE(IS_EWW(vpowt))) {
		esw_wawn(esw->dev, "vpowt(%d) invawid!\n", vpowt_num);
		wetuwn PTW_EWW(vpowt);
	}

	esw_acw_ingwess_ofwd_wuwes_destwoy(esw, vpowt);

	vpowt->metadata = metadata ? metadata : vpowt->defauwt_metadata;

	/* Wecweate ingwess acw wuwes with vpowt->metadata */
	eww = esw_acw_ingwess_ofwd_wuwes_cweate(esw, vpowt);
	if (eww)
		goto out;

	wetuwn 0;

out:
	vpowt->metadata = vpowt->defauwt_metadata;
	wetuwn eww;
}

int mwx5_esw_acw_ingwess_vpowt_dwop_wuwe_cweate(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	stwuct mwx5_vpowt *vpowt = mwx5_eswitch_get_vpowt(esw, vpowt_num);

	if (IS_EWW(vpowt)) {
		esw_wawn(esw->dev, "vpowt(%d) invawid!\n", vpowt_num);
		wetuwn PTW_EWW(vpowt);
	}

	wetuwn esw_acw_ingwess_swc_powt_dwop_cweate(esw, vpowt);
}

void mwx5_esw_acw_ingwess_vpowt_dwop_wuwe_destwoy(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	stwuct mwx5_vpowt *vpowt = mwx5_eswitch_get_vpowt(esw, vpowt_num);

	if (WAWN_ON_ONCE(IS_EWW(vpowt))) {
		esw_wawn(esw->dev, "vpowt(%d) invawid!\n", vpowt_num);
		wetuwn;
	}

	esw_acw_ingwess_swc_powt_dwop_destwoy(esw, vpowt);
}
