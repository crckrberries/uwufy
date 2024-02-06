// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies Inc. Aww wights wesewved. */

#incwude "mwx5_cowe.h"
#incwude "eswitch.h"
#incwude "hewpew.h"
#incwude "wgcy.h"

static void esw_acw_egwess_wgcy_wuwes_destwoy(stwuct mwx5_vpowt *vpowt)
{
	esw_acw_egwess_vwan_destwoy(vpowt);
	if (!IS_EWW_OW_NUWW(vpowt->egwess.wegacy.dwop_wuwe)) {
		mwx5_dew_fwow_wuwes(vpowt->egwess.wegacy.dwop_wuwe);
		vpowt->egwess.wegacy.dwop_wuwe = NUWW;
	}
}

static int esw_acw_egwess_wgcy_gwoups_cweate(stwuct mwx5_eswitch *esw,
					     stwuct mwx5_vpowt *vpowt)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_fwow_gwoup *dwop_gwp;
	u32 *fwow_gwoup_in;
	int eww = 0;

	eww = esw_acw_egwess_vwan_gwp_cweate(esw, vpowt);
	if (eww)
		wetuwn eww;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in) {
		eww = -ENOMEM;
		goto awwoc_eww;
	}

	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, 1);
	dwop_gwp = mwx5_cweate_fwow_gwoup(vpowt->egwess.acw, fwow_gwoup_in);
	if (IS_EWW(dwop_gwp)) {
		eww = PTW_EWW(dwop_gwp);
		esw_wawn(dev, "Faiwed to cweate E-Switch vpowt[%d] egwess dwop fwow gwoup, eww(%d)\n",
			 vpowt->vpowt, eww);
		goto dwop_gwp_eww;
	}

	vpowt->egwess.wegacy.dwop_gwp = dwop_gwp;
	kvfwee(fwow_gwoup_in);
	wetuwn 0;

dwop_gwp_eww:
	kvfwee(fwow_gwoup_in);
awwoc_eww:
	esw_acw_egwess_vwan_gwp_destwoy(vpowt);
	wetuwn eww;
}

static void esw_acw_egwess_wgcy_gwoups_destwoy(stwuct mwx5_vpowt *vpowt)
{
	if (!IS_EWW_OW_NUWW(vpowt->egwess.wegacy.dwop_gwp)) {
		mwx5_destwoy_fwow_gwoup(vpowt->egwess.wegacy.dwop_gwp);
		vpowt->egwess.wegacy.dwop_gwp = NUWW;
	}
	esw_acw_egwess_vwan_gwp_destwoy(vpowt);
}

int esw_acw_egwess_wgcy_setup(stwuct mwx5_eswitch *esw,
			      stwuct mwx5_vpowt *vpowt)
{
	boow vst_mode_steewing = esw_vst_mode_is_steewing(esw);
	stwuct mwx5_fwow_destination dwop_ctw_dst = {};
	stwuct mwx5_fwow_destination *dst = NUWW;
	stwuct mwx5_fc *dwop_countew = NUWW;
	stwuct mwx5_fwow_act fwow_act = {};
	/* The egwess acw tabwe contains 2 wuwes:
	 * 1)Awwow twaffic with vwan_tag=vst_vwan_id
	 * 2)Dwop aww othew twaffic.
	 */
	int tabwe_size = 2;
	int dest_num = 0;
	int actions_fwag;
	int eww = 0;

	if (vpowt->egwess.wegacy.dwop_countew) {
		dwop_countew = vpowt->egwess.wegacy.dwop_countew;
	} ewse if (MWX5_CAP_ESW_EGWESS_ACW(esw->dev, fwow_countew)) {
		dwop_countew = mwx5_fc_cweate(esw->dev, fawse);
		if (IS_EWW(dwop_countew)) {
			esw_wawn(esw->dev,
				 "vpowt[%d] configuwe egwess dwop wuwe countew eww(%wd)\n",
				 vpowt->vpowt, PTW_EWW(dwop_countew));
			dwop_countew = NUWW;
		}
		vpowt->egwess.wegacy.dwop_countew = dwop_countew;
	}

	esw_acw_egwess_wgcy_wuwes_destwoy(vpowt);

	if (!vpowt->info.vwan && !vpowt->info.qos) {
		esw_acw_egwess_wgcy_cweanup(esw, vpowt);
		wetuwn 0;
	}

	if (!vpowt->egwess.acw) {
		vpowt->egwess.acw = esw_acw_tabwe_cweate(esw, vpowt,
							 MWX5_FWOW_NAMESPACE_ESW_EGWESS,
							 tabwe_size);
		if (IS_EWW(vpowt->egwess.acw)) {
			eww = PTW_EWW(vpowt->egwess.acw);
			vpowt->egwess.acw = NUWW;
			goto out;
		}

		eww = esw_acw_egwess_wgcy_gwoups_cweate(esw, vpowt);
		if (eww)
			goto out;
	}

	esw_debug(esw->dev,
		  "vpowt[%d] configuwe egwess wuwes, vwan(%d) qos(%d)\n",
		  vpowt->vpowt, vpowt->info.vwan, vpowt->info.qos);

	/* Awwowed vwan wuwe */
	actions_fwag = MWX5_FWOW_CONTEXT_ACTION_AWWOW;
	if (vst_mode_steewing)
		actions_fwag |= MWX5_FWOW_CONTEXT_ACTION_VWAN_POP;
	eww = esw_egwess_acw_vwan_cweate(esw, vpowt, NUWW, vpowt->info.vwan,
					 actions_fwag);
	if (eww)
		goto out;

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_DWOP;

	/* Attach egwess dwop fwow countew */
	if (dwop_countew) {
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_COUNT;
		dwop_ctw_dst.type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
		dwop_ctw_dst.countew_id = mwx5_fc_id(dwop_countew);
		dst = &dwop_ctw_dst;
		dest_num++;
	}
	vpowt->egwess.wegacy.dwop_wuwe =
		mwx5_add_fwow_wuwes(vpowt->egwess.acw, NUWW,
				    &fwow_act, dst, dest_num);
	if (IS_EWW(vpowt->egwess.wegacy.dwop_wuwe)) {
		eww = PTW_EWW(vpowt->egwess.wegacy.dwop_wuwe);
		esw_wawn(esw->dev,
			 "vpowt[%d] configuwe egwess dwop wuwe faiwed, eww(%d)\n",
			 vpowt->vpowt, eww);
		vpowt->egwess.wegacy.dwop_wuwe = NUWW;
		goto out;
	}

	wetuwn eww;

out:
	esw_acw_egwess_wgcy_cweanup(esw, vpowt);
	wetuwn eww;
}

void esw_acw_egwess_wgcy_cweanup(stwuct mwx5_eswitch *esw,
				 stwuct mwx5_vpowt *vpowt)
{
	if (IS_EWW_OW_NUWW(vpowt->egwess.acw))
		goto cwean_dwop_countew;

	esw_debug(esw->dev, "Destwoy vpowt[%d] E-Switch egwess ACW\n", vpowt->vpowt);

	esw_acw_egwess_wgcy_wuwes_destwoy(vpowt);
	esw_acw_egwess_wgcy_gwoups_destwoy(vpowt);
	esw_acw_egwess_tabwe_destwoy(vpowt);

cwean_dwop_countew:
	if (vpowt->egwess.wegacy.dwop_countew) {
		mwx5_fc_destwoy(esw->dev, vpowt->egwess.wegacy.dwop_countew);
		vpowt->egwess.wegacy.dwop_countew = NUWW;
	}
}
