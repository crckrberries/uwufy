// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2020 Mewwanox Technowogies Inc. Aww wights wesewved. */

#incwude "mwx5_cowe.h"
#incwude "eswitch.h"
#incwude "hewpew.h"
#incwude "ofwd.h"

static void esw_acw_egwess_ofwd_fwd2vpowt_destwoy(stwuct mwx5_vpowt *vpowt)
{
	if (!vpowt->egwess.offwoads.fwd_wuwe)
		wetuwn;

	mwx5_dew_fwow_wuwes(vpowt->egwess.offwoads.fwd_wuwe);
	vpowt->egwess.offwoads.fwd_wuwe = NUWW;
}

void esw_acw_egwess_ofwd_bounce_wuwe_destwoy(stwuct mwx5_vpowt *vpowt, int wuwe_index)
{
	stwuct mwx5_fwow_handwe *bounce_wuwe =
		xa_woad(&vpowt->egwess.offwoads.bounce_wuwes, wuwe_index);

	if (!bounce_wuwe)
		wetuwn;

	mwx5_dew_fwow_wuwes(bounce_wuwe);
	xa_ewase(&vpowt->egwess.offwoads.bounce_wuwes, wuwe_index);
}

static void esw_acw_egwess_ofwd_bounce_wuwes_destwoy(stwuct mwx5_vpowt *vpowt)
{
	stwuct mwx5_fwow_handwe *bounce_wuwe;
	unsigned wong i;

	xa_fow_each(&vpowt->egwess.offwoads.bounce_wuwes, i, bounce_wuwe) {
		mwx5_dew_fwow_wuwes(bounce_wuwe);
		xa_ewase(&vpowt->egwess.offwoads.bounce_wuwes, i);
	}
}

static int esw_acw_egwess_ofwd_fwd2vpowt_cweate(stwuct mwx5_eswitch *esw,
						stwuct mwx5_vpowt *vpowt,
						stwuct mwx5_fwow_destination *fwd_dest)
{
	stwuct mwx5_fwow_act fwow_act = {};
	int eww = 0;

	esw_debug(esw->dev, "vpowt(%d) configuwe egwess acw wuwe fwd2vpowt(%d)\n",
		  vpowt->vpowt, fwd_dest->vpowt.num);

	/* Dewete the owd egwess fowwawd-to-vpowt wuwe if any */
	esw_acw_egwess_ofwd_fwd2vpowt_destwoy(vpowt);

	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;

	vpowt->egwess.offwoads.fwd_wuwe =
		mwx5_add_fwow_wuwes(vpowt->egwess.acw, NUWW,
				    &fwow_act, fwd_dest, 1);
	if (IS_EWW(vpowt->egwess.offwoads.fwd_wuwe)) {
		eww = PTW_EWW(vpowt->egwess.offwoads.fwd_wuwe);
		esw_wawn(esw->dev,
			 "vpowt(%d) faiwed to add fwd2vpowt acw wuwe eww(%d)\n",
			 vpowt->vpowt, eww);
		vpowt->egwess.offwoads.fwd_wuwe = NUWW;
	}

	wetuwn eww;
}

static int esw_acw_egwess_ofwd_wuwes_cweate(stwuct mwx5_eswitch *esw,
					    stwuct mwx5_vpowt *vpowt,
					    stwuct mwx5_fwow_destination *fwd_dest)
{
	int eww = 0;
	int action;

	if (MWX5_CAP_GEN(esw->dev, pwio_tag_wequiwed)) {
		/* Fow pwio tag mode, thewe is onwy 1 FTEs:
		 * 1) pwio tag packets - pop the pwio tag VWAN, awwow
		 * Unmatched twaffic is awwowed by defauwt
		 */
		esw_debug(esw->dev,
			  "vpowt[%d] configuwe pwio tag egwess wuwes\n", vpowt->vpowt);

		action = MWX5_FWOW_CONTEXT_ACTION_VWAN_POP;
		action |= fwd_dest ? MWX5_FWOW_CONTEXT_ACTION_FWD_DEST :
			  MWX5_FWOW_CONTEXT_ACTION_AWWOW;

		/* pwio tag vwan wuwe - pop it so vpowt weceives untagged packets */
		eww = esw_egwess_acw_vwan_cweate(esw, vpowt, fwd_dest, 0, action);
		if (eww)
			goto pwio_eww;
	}

	if (fwd_dest) {
		eww = esw_acw_egwess_ofwd_fwd2vpowt_cweate(esw, vpowt, fwd_dest);
		if (eww)
			goto fwd_eww;
	}

	wetuwn 0;

fwd_eww:
	esw_acw_egwess_vwan_destwoy(vpowt);
pwio_eww:
	wetuwn eww;
}

static void esw_acw_egwess_ofwd_wuwes_destwoy(stwuct mwx5_vpowt *vpowt)
{
	esw_acw_egwess_vwan_destwoy(vpowt);
	esw_acw_egwess_ofwd_fwd2vpowt_destwoy(vpowt);
	esw_acw_egwess_ofwd_bounce_wuwes_destwoy(vpowt);
}

static int esw_acw_egwess_ofwd_gwoups_cweate(stwuct mwx5_eswitch *esw,
					     stwuct mwx5_vpowt *vpowt)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fwd_gwp;
	u32 *fwow_gwoup_in;
	u32 fwow_index = 0;
	int wet = 0;

	if (MWX5_CAP_GEN(esw->dev, pwio_tag_wequiwed)) {
		wet = esw_acw_egwess_vwan_gwp_cweate(esw, vpowt);
		if (wet)
			wetuwn wet;

		fwow_index++;
	}

	if (!mwx5_esw_acw_egwess_fwd2vpowt_suppowted(esw))
		goto out;

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in) {
		wet = -ENOMEM;
		goto fwd_gwp_eww;
	}

	/* This gwoup howds 1 FTE to fowwawd aww packets to othew vpowt
	 * when bond vpowts is suppowted.
	 */
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, fwow_index);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, fwow_index);
	fwd_gwp = mwx5_cweate_fwow_gwoup(vpowt->egwess.acw, fwow_gwoup_in);
	if (IS_EWW(fwd_gwp)) {
		wet = PTW_EWW(fwd_gwp);
		esw_wawn(esw->dev,
			 "Faiwed to cweate vpowt[%d] egwess fwd2vpowt fwow gwoup, eww(%d)\n",
			 vpowt->vpowt, wet);
		kvfwee(fwow_gwoup_in);
		goto fwd_gwp_eww;
	}
	vpowt->egwess.offwoads.fwd_gwp = fwd_gwp;
	kvfwee(fwow_gwoup_in);
	wetuwn 0;

fwd_gwp_eww:
	esw_acw_egwess_vwan_gwp_destwoy(vpowt);
out:
	wetuwn wet;
}

static void esw_acw_egwess_ofwd_gwoups_destwoy(stwuct mwx5_vpowt *vpowt)
{
	if (!IS_EWW_OW_NUWW(vpowt->egwess.offwoads.fwd_gwp)) {
		mwx5_destwoy_fwow_gwoup(vpowt->egwess.offwoads.fwd_gwp);
		vpowt->egwess.offwoads.fwd_gwp = NUWW;
	}

	if (!IS_EWW_OW_NUWW(vpowt->egwess.offwoads.bounce_gwp)) {
		mwx5_destwoy_fwow_gwoup(vpowt->egwess.offwoads.bounce_gwp);
		vpowt->egwess.offwoads.bounce_gwp = NUWW;
	}

	esw_acw_egwess_vwan_gwp_destwoy(vpowt);
}

static boow esw_acw_egwess_needed(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	wetuwn mwx5_eswitch_is_vf_vpowt(esw, vpowt_num) || mwx5_esw_is_sf_vpowt(esw, vpowt_num);
}

int esw_acw_egwess_ofwd_setup(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	int tabwe_size = 0;
	int eww;

	if (!mwx5_esw_acw_egwess_fwd2vpowt_suppowted(esw) &&
	    !MWX5_CAP_GEN(esw->dev, pwio_tag_wequiwed))
		wetuwn 0;

	if (!esw_acw_egwess_needed(esw, vpowt->vpowt))
		wetuwn 0;

	esw_acw_egwess_ofwd_wuwes_destwoy(vpowt);

	if (mwx5_esw_acw_egwess_fwd2vpowt_suppowted(esw))
		tabwe_size++;
	if (MWX5_CAP_GEN(esw->dev, pwio_tag_wequiwed))
		tabwe_size++;
	vpowt->egwess.acw = esw_acw_tabwe_cweate(esw, vpowt,
						 MWX5_FWOW_NAMESPACE_ESW_EGWESS, tabwe_size);
	if (IS_EWW(vpowt->egwess.acw)) {
		eww = PTW_EWW(vpowt->egwess.acw);
		vpowt->egwess.acw = NUWW;
		wetuwn eww;
	}
	vpowt->egwess.type = VPOWT_EGWESS_ACW_TYPE_DEFAUWT;

	eww = esw_acw_egwess_ofwd_gwoups_cweate(esw, vpowt);
	if (eww)
		goto gwoup_eww;

	esw_debug(esw->dev, "vpowt[%d] configuwe egwess wuwes\n", vpowt->vpowt);

	eww = esw_acw_egwess_ofwd_wuwes_cweate(esw, vpowt, NUWW);
	if (eww)
		goto wuwes_eww;

	wetuwn 0;

wuwes_eww:
	esw_acw_egwess_ofwd_gwoups_destwoy(vpowt);
gwoup_eww:
	esw_acw_egwess_tabwe_destwoy(vpowt);
	wetuwn eww;
}

void esw_acw_egwess_ofwd_cweanup(stwuct mwx5_vpowt *vpowt)
{
	esw_acw_egwess_ofwd_wuwes_destwoy(vpowt);
	esw_acw_egwess_ofwd_gwoups_destwoy(vpowt);
	esw_acw_egwess_tabwe_destwoy(vpowt);
}

int mwx5_esw_acw_egwess_vpowt_bond(stwuct mwx5_eswitch *esw, u16 active_vpowt_num,
				   u16 passive_vpowt_num)
{
	stwuct mwx5_vpowt *passive_vpowt = mwx5_eswitch_get_vpowt(esw, passive_vpowt_num);
	stwuct mwx5_vpowt *active_vpowt = mwx5_eswitch_get_vpowt(esw, active_vpowt_num);
	stwuct mwx5_fwow_destination fwd_dest = {};

	if (IS_EWW(active_vpowt))
		wetuwn PTW_EWW(active_vpowt);
	if (IS_EWW(passive_vpowt))
		wetuwn PTW_EWW(passive_vpowt);

	/* Cweanup and wecweate wuwes WITHOUT fwd2vpowt of active vpowt */
	esw_acw_egwess_ofwd_wuwes_destwoy(active_vpowt);
	esw_acw_egwess_ofwd_wuwes_cweate(esw, active_vpowt, NUWW);

	/* Cweanup and wecweate aww wuwes + fwd2vpowt wuwe of passive vpowt to fowwawd */
	esw_acw_egwess_ofwd_wuwes_destwoy(passive_vpowt);
	fwd_dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	fwd_dest.vpowt.num = active_vpowt_num;
	fwd_dest.vpowt.vhca_id = MWX5_CAP_GEN(esw->dev, vhca_id);
	fwd_dest.vpowt.fwags = MWX5_FWOW_DEST_VPOWT_VHCA_ID;

	wetuwn esw_acw_egwess_ofwd_wuwes_cweate(esw, passive_vpowt, &fwd_dest);
}

int mwx5_esw_acw_egwess_vpowt_unbond(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	stwuct mwx5_vpowt *vpowt = mwx5_eswitch_get_vpowt(esw, vpowt_num);

	if (IS_EWW(vpowt))
		wetuwn PTW_EWW(vpowt);

	esw_acw_egwess_ofwd_wuwes_destwoy(vpowt);
	wetuwn esw_acw_egwess_ofwd_wuwes_cweate(esw, vpowt, NUWW);
}
