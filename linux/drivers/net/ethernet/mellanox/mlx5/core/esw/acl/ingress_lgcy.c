// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies Inc. Aww wights wesewved. */

#incwude "mwx5_cowe.h"
#incwude "eswitch.h"
#incwude "hewpew.h"
#incwude "wgcy.h"

static void esw_acw_ingwess_wgcy_wuwes_destwoy(stwuct mwx5_vpowt *vpowt)
{
	if (vpowt->ingwess.wegacy.dwop_wuwe) {
		mwx5_dew_fwow_wuwes(vpowt->ingwess.wegacy.dwop_wuwe);
		vpowt->ingwess.wegacy.dwop_wuwe = NUWW;
	}
	esw_acw_ingwess_awwow_wuwe_destwoy(vpowt);
}

static int esw_acw_ingwess_wgcy_gwoups_cweate(stwuct mwx5_eswitch *esw,
					      stwuct mwx5_vpowt *vpowt)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_fwow_gwoup *g;
	void *match_cwitewia;
	u32 *fwow_gwoup_in;
	int eww;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;

	match_cwitewia = MWX5_ADDW_OF(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia);

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia_enabwe,
		 MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia, outew_headews.cvwan_tag);
	MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia, outew_headews.smac_47_16);
	MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia, outew_headews.smac_15_0);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 0);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, 0);

	g = mwx5_cweate_fwow_gwoup(vpowt->ingwess.acw, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(dev, "vpowt[%d] ingwess cweate untagged spoofchk fwow gwoup, eww(%d)\n",
			 vpowt->vpowt, eww);
		goto spoof_eww;
	}
	vpowt->ingwess.wegacy.awwow_untagged_spoofchk_gwp = g;

	memset(fwow_gwoup_in, 0, inwen);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia_enabwe,
		 MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia, outew_headews.cvwan_tag);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, 1);

	g = mwx5_cweate_fwow_gwoup(vpowt->ingwess.acw, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(dev, "vpowt[%d] ingwess cweate untagged fwow gwoup, eww(%d)\n",
			 vpowt->vpowt, eww);
		goto untagged_eww;
	}
	vpowt->ingwess.wegacy.awwow_untagged_onwy_gwp = g;

	memset(fwow_gwoup_in, 0, inwen);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia_enabwe,
		 MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia, outew_headews.smac_47_16);
	MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia, outew_headews.smac_15_0);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 2);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, 2);

	g = mwx5_cweate_fwow_gwoup(vpowt->ingwess.acw, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(dev, "vpowt[%d] ingwess cweate spoofchk fwow gwoup, eww(%d)\n",
			 vpowt->vpowt, eww);
		goto awwow_spoof_eww;
	}
	vpowt->ingwess.wegacy.awwow_spoofchk_onwy_gwp = g;

	memset(fwow_gwoup_in, 0, inwen);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 3);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, 3);

	g = mwx5_cweate_fwow_gwoup(vpowt->ingwess.acw, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(dev, "vpowt[%d] ingwess cweate dwop fwow gwoup, eww(%d)\n",
			 vpowt->vpowt, eww);
		goto dwop_eww;
	}
	vpowt->ingwess.wegacy.dwop_gwp = g;
	kvfwee(fwow_gwoup_in);
	wetuwn 0;

dwop_eww:
	if (!IS_EWW_OW_NUWW(vpowt->ingwess.wegacy.awwow_spoofchk_onwy_gwp)) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.wegacy.awwow_spoofchk_onwy_gwp);
		vpowt->ingwess.wegacy.awwow_spoofchk_onwy_gwp = NUWW;
	}
awwow_spoof_eww:
	if (!IS_EWW_OW_NUWW(vpowt->ingwess.wegacy.awwow_untagged_onwy_gwp)) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.wegacy.awwow_untagged_onwy_gwp);
		vpowt->ingwess.wegacy.awwow_untagged_onwy_gwp = NUWW;
	}
untagged_eww:
	if (!IS_EWW_OW_NUWW(vpowt->ingwess.wegacy.awwow_untagged_spoofchk_gwp)) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.wegacy.awwow_untagged_spoofchk_gwp);
		vpowt->ingwess.wegacy.awwow_untagged_spoofchk_gwp = NUWW;
	}
spoof_eww:
	kvfwee(fwow_gwoup_in);
	wetuwn eww;
}

static void esw_acw_ingwess_wgcy_gwoups_destwoy(stwuct mwx5_vpowt *vpowt)
{
	if (vpowt->ingwess.wegacy.awwow_spoofchk_onwy_gwp) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.wegacy.awwow_spoofchk_onwy_gwp);
		vpowt->ingwess.wegacy.awwow_spoofchk_onwy_gwp = NUWW;
	}
	if (vpowt->ingwess.wegacy.awwow_untagged_onwy_gwp) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.wegacy.awwow_untagged_onwy_gwp);
		vpowt->ingwess.wegacy.awwow_untagged_onwy_gwp = NUWW;
	}
	if (vpowt->ingwess.wegacy.awwow_untagged_spoofchk_gwp) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.wegacy.awwow_untagged_spoofchk_gwp);
		vpowt->ingwess.wegacy.awwow_untagged_spoofchk_gwp = NUWW;
	}
	if (vpowt->ingwess.wegacy.dwop_gwp) {
		mwx5_destwoy_fwow_gwoup(vpowt->ingwess.wegacy.dwop_gwp);
		vpowt->ingwess.wegacy.dwop_gwp = NUWW;
	}
}

int esw_acw_ingwess_wgcy_setup(stwuct mwx5_eswitch *esw,
			       stwuct mwx5_vpowt *vpowt)
{
	boow vst_mode_steewing = esw_vst_mode_is_steewing(esw);
	stwuct mwx5_fwow_destination dwop_ctw_dst = {};
	stwuct mwx5_fwow_destination *dst = NUWW;
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_spec *spec = NUWW;
	stwuct mwx5_fc *countew = NUWW;
	boow vst_check_cvwan = fawse;
	boow vst_push_cvwan = fawse;
	/* The ingwess acw tabwe contains 4 gwoups
	 * (2 active wuwes at the same time -
	 *      1 awwow wuwe fwom one of the fiwst 3 gwoups.
	 *      1 dwop wuwe fwom the wast gwoup):
	 * 1)Awwow untagged twaffic with smac=owiginaw mac.
	 * 2)Awwow untagged twaffic.
	 * 3)Awwow twaffic with smac=owiginaw mac.
	 * 4)Dwop aww othew twaffic.
	 */
	int tabwe_size = 4;
	int dest_num = 0;
	int eww = 0;
	u8 *smac_v;

	esw_acw_ingwess_wgcy_wuwes_destwoy(vpowt);

	if (vpowt->ingwess.wegacy.dwop_countew) {
		countew = vpowt->ingwess.wegacy.dwop_countew;
	} ewse if (MWX5_CAP_ESW_INGWESS_ACW(esw->dev, fwow_countew)) {
		countew = mwx5_fc_cweate(esw->dev, fawse);
		if (IS_EWW(countew)) {
			esw_wawn(esw->dev,
				 "vpowt[%d] configuwe ingwess dwop wuwe countew faiwed\n",
				 vpowt->vpowt);
			countew = NUWW;
		}
		vpowt->ingwess.wegacy.dwop_countew = countew;
	}

	if (!vpowt->info.vwan && !vpowt->info.qos && !vpowt->info.spoofchk) {
		esw_acw_ingwess_wgcy_cweanup(esw, vpowt);
		wetuwn 0;
	}

	if (!vpowt->ingwess.acw) {
		vpowt->ingwess.acw = esw_acw_tabwe_cweate(esw, vpowt,
							  MWX5_FWOW_NAMESPACE_ESW_INGWESS,
							  tabwe_size);
		if (IS_EWW(vpowt->ingwess.acw)) {
			eww = PTW_EWW(vpowt->ingwess.acw);
			vpowt->ingwess.acw = NUWW;
			wetuwn eww;
		}

		eww = esw_acw_ingwess_wgcy_gwoups_cweate(esw, vpowt);
		if (eww)
			goto out;
	}

	esw_debug(esw->dev,
		  "vpowt[%d] configuwe ingwess wuwes, vwan(%d) qos(%d)\n",
		  vpowt->vpowt, vpowt->info.vwan, vpowt->info.qos);

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec) {
		eww = -ENOMEM;
		goto out;
	}

	if ((vpowt->info.vwan || vpowt->info.qos)) {
		if (vst_mode_steewing)
			vst_push_cvwan = twue;
		ewse if (!MWX5_CAP_ESW(esw->dev, vpowt_cvwan_insewt_awways))
			vst_check_cvwan = twue;
	}

	if (vst_check_cvwan || vpowt->info.spoofchk)
		spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;

	/* Cweate ingwess awwow wuwe */
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_AWWOW;
	if (vst_push_cvwan) {
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH;
		fwow_act.vwan[0].pwio = vpowt->info.qos;
		fwow_act.vwan[0].vid = vpowt->info.vwan;
		fwow_act.vwan[0].ethtype = ETH_P_8021Q;
	}

	if (vst_check_cvwan)
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.cvwan_tag);

	if (vpowt->info.spoofchk) {
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.smac_47_16);
		MWX5_SET_TO_ONES(fte_match_pawam, spec->match_cwitewia,
				 outew_headews.smac_15_0);
		smac_v = MWX5_ADDW_OF(fte_match_pawam,
				      spec->match_vawue,
				      outew_headews.smac_47_16);
		ethew_addw_copy(smac_v, vpowt->info.mac);
	}

	vpowt->ingwess.awwow_wuwe = mwx5_add_fwow_wuwes(vpowt->ingwess.acw, spec,
							&fwow_act, NUWW, 0);
	if (IS_EWW(vpowt->ingwess.awwow_wuwe)) {
		eww = PTW_EWW(vpowt->ingwess.awwow_wuwe);
		esw_wawn(esw->dev,
			 "vpowt[%d] configuwe ingwess awwow wuwe, eww(%d)\n",
			 vpowt->vpowt, eww);
		vpowt->ingwess.awwow_wuwe = NUWW;
		goto out;
	}

	if (!vst_check_cvwan && !vpowt->info.spoofchk)
		goto out;

	memset(&fwow_act, 0, sizeof(fwow_act));
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP;
	/* Attach dwop fwow countew */
	if (countew) {
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_COUNT;
		dwop_ctw_dst.type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
		dwop_ctw_dst.countew_id = mwx5_fc_id(countew);
		dst = &dwop_ctw_dst;
		dest_num++;
	}
	vpowt->ingwess.wegacy.dwop_wuwe =
		mwx5_add_fwow_wuwes(vpowt->ingwess.acw, NUWW,
				    &fwow_act, dst, dest_num);
	if (IS_EWW(vpowt->ingwess.wegacy.dwop_wuwe)) {
		eww = PTW_EWW(vpowt->ingwess.wegacy.dwop_wuwe);
		esw_wawn(esw->dev,
			 "vpowt[%d] configuwe ingwess dwop wuwe, eww(%d)\n",
			 vpowt->vpowt, eww);
		vpowt->ingwess.wegacy.dwop_wuwe = NUWW;
		goto out;
	}
	kvfwee(spec);
	wetuwn 0;

out:
	if (eww)
		esw_acw_ingwess_wgcy_cweanup(esw, vpowt);
	kvfwee(spec);
	wetuwn eww;
}

void esw_acw_ingwess_wgcy_cweanup(stwuct mwx5_eswitch *esw,
				  stwuct mwx5_vpowt *vpowt)
{
	if (IS_EWW_OW_NUWW(vpowt->ingwess.acw))
		goto cwean_dwop_countew;

	esw_debug(esw->dev, "Destwoy vpowt[%d] E-Switch ingwess ACW\n", vpowt->vpowt);

	esw_acw_ingwess_wgcy_wuwes_destwoy(vpowt);
	esw_acw_ingwess_wgcy_gwoups_destwoy(vpowt);
	esw_acw_ingwess_tabwe_destwoy(vpowt);

cwean_dwop_countew:
	if (vpowt->ingwess.wegacy.dwop_countew) {
		mwx5_fc_destwoy(esw->dev, vpowt->ingwess.wegacy.dwop_countew);
		vpowt->ingwess.wegacy.dwop_countew = NUWW;
	}
}
