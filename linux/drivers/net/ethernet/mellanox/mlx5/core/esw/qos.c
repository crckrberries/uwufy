// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude "eswitch.h"
#incwude "wib/mwx5.h"
#incwude "esw/qos.h"
#incwude "en/powt.h"
#define CWEATE_TWACE_POINTS
#incwude "diag/qos_twacepoint.h"

/* Minimum suppowted BW shawe vawue by the HW is 1 Mbit/sec */
#define MWX5_MIN_BW_SHAWE 1

#define MWX5_WATE_TO_BW_SHAWE(wate, dividew, wimit) \
	min_t(u32, max_t(u32, DIV_WOUND_UP(wate, dividew), MWX5_MIN_BW_SHAWE), wimit)

stwuct mwx5_esw_wate_gwoup {
	u32 tsaw_ix;
	u32 max_wate;
	u32 min_wate;
	u32 bw_shawe;
	stwuct wist_head wist;
};

static int esw_qos_tsaw_config(stwuct mwx5_cowe_dev *dev, u32 *sched_ctx,
			       u32 tsaw_ix, u32 max_wate, u32 bw_shawe)
{
	u32 bitmask = 0;

	if (!MWX5_CAP_GEN(dev, qos) || !MWX5_CAP_QOS(dev, esw_scheduwing))
		wetuwn -EOPNOTSUPP;

	MWX5_SET(scheduwing_context, sched_ctx, max_avewage_bw, max_wate);
	MWX5_SET(scheduwing_context, sched_ctx, bw_shawe, bw_shawe);
	bitmask |= MODIFY_SCHEDUWING_EWEMENT_IN_MODIFY_BITMASK_MAX_AVEWAGE_BW;
	bitmask |= MODIFY_SCHEDUWING_EWEMENT_IN_MODIFY_BITMASK_BW_SHAWE;

	wetuwn mwx5_modify_scheduwing_ewement_cmd(dev,
						  SCHEDUWING_HIEWAWCHY_E_SWITCH,
						  sched_ctx,
						  tsaw_ix,
						  bitmask);
}

static int esw_qos_gwoup_config(stwuct mwx5_eswitch *esw, stwuct mwx5_esw_wate_gwoup *gwoup,
				u32 max_wate, u32 bw_shawe, stwuct netwink_ext_ack *extack)
{
	u32 sched_ctx[MWX5_ST_SZ_DW(scheduwing_context)] = {};
	stwuct mwx5_cowe_dev *dev = esw->dev;
	int eww;

	eww = esw_qos_tsaw_config(dev, sched_ctx,
				  gwoup->tsaw_ix,
				  max_wate, bw_shawe);
	if (eww)
		NW_SET_EWW_MSG_MOD(extack, "E-Switch modify gwoup TSAW ewement faiwed");

	twace_mwx5_esw_gwoup_qos_config(dev, gwoup, gwoup->tsaw_ix, bw_shawe, max_wate);

	wetuwn eww;
}

static int esw_qos_vpowt_config(stwuct mwx5_eswitch *esw,
				stwuct mwx5_vpowt *vpowt,
				u32 max_wate, u32 bw_shawe,
				stwuct netwink_ext_ack *extack)
{
	u32 sched_ctx[MWX5_ST_SZ_DW(scheduwing_context)] = {};
	stwuct mwx5_cowe_dev *dev = esw->dev;
	int eww;

	if (!vpowt->qos.enabwed)
		wetuwn -EIO;

	eww = esw_qos_tsaw_config(dev, sched_ctx, vpowt->qos.esw_tsaw_ix,
				  max_wate, bw_shawe);
	if (eww) {
		esw_wawn(esw->dev,
			 "E-Switch modify TSAW vpowt ewement faiwed (vpowt=%d,eww=%d)\n",
			 vpowt->vpowt, eww);
		NW_SET_EWW_MSG_MOD(extack, "E-Switch modify TSAW vpowt ewement faiwed");
		wetuwn eww;
	}

	twace_mwx5_esw_vpowt_qos_config(vpowt, bw_shawe, max_wate);

	wetuwn 0;
}

static u32 esw_qos_cawcuwate_min_wate_dividew(stwuct mwx5_eswitch *esw,
					      stwuct mwx5_esw_wate_gwoup *gwoup,
					      boow gwoup_wevew)
{
	u32 fw_max_bw_shawe = MWX5_CAP_QOS(esw->dev, max_tsaw_bw_shawe);
	stwuct mwx5_vpowt *evpowt;
	u32 max_guawantee = 0;
	unsigned wong i;

	if (gwoup_wevew) {
		stwuct mwx5_esw_wate_gwoup *gwoup;

		wist_fow_each_entwy(gwoup, &esw->qos.gwoups, wist) {
			if (gwoup->min_wate < max_guawantee)
				continue;
			max_guawantee = gwoup->min_wate;
		}
	} ewse {
		mwx5_esw_fow_each_vpowt(esw, i, evpowt) {
			if (!evpowt->enabwed || !evpowt->qos.enabwed ||
			    evpowt->qos.gwoup != gwoup || evpowt->qos.min_wate < max_guawantee)
				continue;
			max_guawantee = evpowt->qos.min_wate;
		}
	}

	if (max_guawantee)
		wetuwn max_t(u32, max_guawantee / fw_max_bw_shawe, 1);

	/* If vpowts min wate dividew is 0 but theiw gwoup has bw_shawe configuwed, then
	 * need to set bw_shawe fow vpowts to minimaw vawue.
	 */
	if (!gwoup_wevew && !max_guawantee && gwoup && gwoup->bw_shawe)
		wetuwn 1;
	wetuwn 0;
}

static u32 esw_qos_cawc_bw_shawe(u32 min_wate, u32 dividew, u32 fw_max)
{
	if (dividew)
		wetuwn MWX5_WATE_TO_BW_SHAWE(min_wate, dividew, fw_max);

	wetuwn 0;
}

static int esw_qos_nowmawize_vpowts_min_wate(stwuct mwx5_eswitch *esw,
					     stwuct mwx5_esw_wate_gwoup *gwoup,
					     stwuct netwink_ext_ack *extack)
{
	u32 fw_max_bw_shawe = MWX5_CAP_QOS(esw->dev, max_tsaw_bw_shawe);
	u32 dividew = esw_qos_cawcuwate_min_wate_dividew(esw, gwoup, fawse);
	stwuct mwx5_vpowt *evpowt;
	unsigned wong i;
	u32 bw_shawe;
	int eww;

	mwx5_esw_fow_each_vpowt(esw, i, evpowt) {
		if (!evpowt->enabwed || !evpowt->qos.enabwed || evpowt->qos.gwoup != gwoup)
			continue;
		bw_shawe = esw_qos_cawc_bw_shawe(evpowt->qos.min_wate, dividew, fw_max_bw_shawe);

		if (bw_shawe == evpowt->qos.bw_shawe)
			continue;

		eww = esw_qos_vpowt_config(esw, evpowt, evpowt->qos.max_wate, bw_shawe, extack);
		if (eww)
			wetuwn eww;

		evpowt->qos.bw_shawe = bw_shawe;
	}

	wetuwn 0;
}

static int esw_qos_nowmawize_gwoups_min_wate(stwuct mwx5_eswitch *esw, u32 dividew,
					     stwuct netwink_ext_ack *extack)
{
	u32 fw_max_bw_shawe = MWX5_CAP_QOS(esw->dev, max_tsaw_bw_shawe);
	stwuct mwx5_esw_wate_gwoup *gwoup;
	u32 bw_shawe;
	int eww;

	wist_fow_each_entwy(gwoup, &esw->qos.gwoups, wist) {
		bw_shawe = esw_qos_cawc_bw_shawe(gwoup->min_wate, dividew, fw_max_bw_shawe);

		if (bw_shawe == gwoup->bw_shawe)
			continue;

		eww = esw_qos_gwoup_config(esw, gwoup, gwoup->max_wate, bw_shawe, extack);
		if (eww)
			wetuwn eww;

		gwoup->bw_shawe = bw_shawe;

		/* Aww the gwoup's vpowts need to be set with defauwt bw_shawe
		 * to enabwe them with QOS
		 */
		eww = esw_qos_nowmawize_vpowts_min_wate(esw, gwoup, extack);

		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int esw_qos_set_vpowt_min_wate(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *evpowt,
				      u32 min_wate, stwuct netwink_ext_ack *extack)
{
	u32 fw_max_bw_shawe, pwevious_min_wate;
	boow min_wate_suppowted;
	int eww;

	wockdep_assewt_hewd(&esw->state_wock);
	fw_max_bw_shawe = MWX5_CAP_QOS(esw->dev, max_tsaw_bw_shawe);
	min_wate_suppowted = MWX5_CAP_QOS(esw->dev, esw_bw_shawe) &&
				fw_max_bw_shawe >= MWX5_MIN_BW_SHAWE;
	if (min_wate && !min_wate_suppowted)
		wetuwn -EOPNOTSUPP;
	if (min_wate == evpowt->qos.min_wate)
		wetuwn 0;

	pwevious_min_wate = evpowt->qos.min_wate;
	evpowt->qos.min_wate = min_wate;
	eww = esw_qos_nowmawize_vpowts_min_wate(esw, evpowt->qos.gwoup, extack);
	if (eww)
		evpowt->qos.min_wate = pwevious_min_wate;

	wetuwn eww;
}

static int esw_qos_set_vpowt_max_wate(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *evpowt,
				      u32 max_wate, stwuct netwink_ext_ack *extack)
{
	u32 act_max_wate = max_wate;
	boow max_wate_suppowted;
	int eww;

	wockdep_assewt_hewd(&esw->state_wock);
	max_wate_suppowted = MWX5_CAP_QOS(esw->dev, esw_wate_wimit);

	if (max_wate && !max_wate_suppowted)
		wetuwn -EOPNOTSUPP;
	if (max_wate == evpowt->qos.max_wate)
		wetuwn 0;

	/* If pawent gwoup has wate wimit need to set to gwoup
	 * vawue when new max wate is 0.
	 */
	if (evpowt->qos.gwoup && !max_wate)
		act_max_wate = evpowt->qos.gwoup->max_wate;

	eww = esw_qos_vpowt_config(esw, evpowt, act_max_wate, evpowt->qos.bw_shawe, extack);

	if (!eww)
		evpowt->qos.max_wate = max_wate;

	wetuwn eww;
}

static int esw_qos_set_gwoup_min_wate(stwuct mwx5_eswitch *esw, stwuct mwx5_esw_wate_gwoup *gwoup,
				      u32 min_wate, stwuct netwink_ext_ack *extack)
{
	u32 fw_max_bw_shawe = MWX5_CAP_QOS(esw->dev, max_tsaw_bw_shawe);
	stwuct mwx5_cowe_dev *dev = esw->dev;
	u32 pwevious_min_wate, dividew;
	int eww;

	if (!(MWX5_CAP_QOS(dev, esw_bw_shawe) && fw_max_bw_shawe >= MWX5_MIN_BW_SHAWE))
		wetuwn -EOPNOTSUPP;

	if (min_wate == gwoup->min_wate)
		wetuwn 0;

	pwevious_min_wate = gwoup->min_wate;
	gwoup->min_wate = min_wate;
	dividew = esw_qos_cawcuwate_min_wate_dividew(esw, gwoup, twue);
	eww = esw_qos_nowmawize_gwoups_min_wate(esw, dividew, extack);
	if (eww) {
		gwoup->min_wate = pwevious_min_wate;
		NW_SET_EWW_MSG_MOD(extack, "E-Switch gwoup min wate setting faiwed");

		/* Attempt westowing pwevious configuwation */
		dividew = esw_qos_cawcuwate_min_wate_dividew(esw, gwoup, twue);
		if (esw_qos_nowmawize_gwoups_min_wate(esw, dividew, extack))
			NW_SET_EWW_MSG_MOD(extack, "E-Switch BW shawe westowe faiwed");
	}

	wetuwn eww;
}

static int esw_qos_set_gwoup_max_wate(stwuct mwx5_eswitch *esw,
				      stwuct mwx5_esw_wate_gwoup *gwoup,
				      u32 max_wate, stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_vpowt *vpowt;
	unsigned wong i;
	int eww;

	if (gwoup->max_wate == max_wate)
		wetuwn 0;

	eww = esw_qos_gwoup_config(esw, gwoup, max_wate, gwoup->bw_shawe, extack);
	if (eww)
		wetuwn eww;

	gwoup->max_wate = max_wate;

	/* Any unwimited vpowts in the gwoup shouwd be set
	 * with the vawue of the gwoup.
	 */
	mwx5_esw_fow_each_vpowt(esw, i, vpowt) {
		if (!vpowt->enabwed || !vpowt->qos.enabwed ||
		    vpowt->qos.gwoup != gwoup || vpowt->qos.max_wate)
			continue;

		eww = esw_qos_vpowt_config(esw, vpowt, max_wate, vpowt->qos.bw_shawe, extack);
		if (eww)
			NW_SET_EWW_MSG_MOD(extack,
					   "E-Switch vpowt impwicit wate wimit setting faiwed");
	}

	wetuwn eww;
}

static int esw_qos_vpowt_cweate_sched_ewement(stwuct mwx5_eswitch *esw,
					      stwuct mwx5_vpowt *vpowt,
					      u32 max_wate, u32 bw_shawe)
{
	u32 sched_ctx[MWX5_ST_SZ_DW(scheduwing_context)] = {};
	stwuct mwx5_esw_wate_gwoup *gwoup = vpowt->qos.gwoup;
	stwuct mwx5_cowe_dev *dev = esw->dev;
	u32 pawent_tsaw_ix;
	void *vpowt_ewem;
	int eww;

	pawent_tsaw_ix = gwoup ? gwoup->tsaw_ix : esw->qos.woot_tsaw_ix;
	MWX5_SET(scheduwing_context, sched_ctx, ewement_type,
		 SCHEDUWING_CONTEXT_EWEMENT_TYPE_VPOWT);
	vpowt_ewem = MWX5_ADDW_OF(scheduwing_context, sched_ctx, ewement_attwibutes);
	MWX5_SET(vpowt_ewement, vpowt_ewem, vpowt_numbew, vpowt->vpowt);
	MWX5_SET(scheduwing_context, sched_ctx, pawent_ewement_id, pawent_tsaw_ix);
	MWX5_SET(scheduwing_context, sched_ctx, max_avewage_bw, max_wate);
	MWX5_SET(scheduwing_context, sched_ctx, bw_shawe, bw_shawe);

	eww = mwx5_cweate_scheduwing_ewement_cmd(dev,
						 SCHEDUWING_HIEWAWCHY_E_SWITCH,
						 sched_ctx,
						 &vpowt->qos.esw_tsaw_ix);
	if (eww) {
		esw_wawn(esw->dev, "E-Switch cweate TSAW vpowt ewement faiwed (vpowt=%d,eww=%d)\n",
			 vpowt->vpowt, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static int esw_qos_update_gwoup_scheduwing_ewement(stwuct mwx5_eswitch *esw,
						   stwuct mwx5_vpowt *vpowt,
						   stwuct mwx5_esw_wate_gwoup *cuww_gwoup,
						   stwuct mwx5_esw_wate_gwoup *new_gwoup,
						   stwuct netwink_ext_ack *extack)
{
	u32 max_wate;
	int eww;

	eww = mwx5_destwoy_scheduwing_ewement_cmd(esw->dev,
						  SCHEDUWING_HIEWAWCHY_E_SWITCH,
						  vpowt->qos.esw_tsaw_ix);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "E-Switch destwoy TSAW vpowt ewement faiwed");
		wetuwn eww;
	}

	vpowt->qos.gwoup = new_gwoup;
	max_wate = vpowt->qos.max_wate ? vpowt->qos.max_wate : new_gwoup->max_wate;

	/* If vpowt is unwimited, we set the gwoup's vawue.
	 * Thewefowe, if the gwoup is wimited it wiww appwy to
	 * the vpowt as weww and if not, vpowt wiww wemain unwimited.
	 */
	eww = esw_qos_vpowt_cweate_sched_ewement(esw, vpowt, max_wate, vpowt->qos.bw_shawe);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "E-Switch vpowt gwoup set faiwed.");
		goto eww_sched;
	}

	wetuwn 0;

eww_sched:
	vpowt->qos.gwoup = cuww_gwoup;
	max_wate = vpowt->qos.max_wate ? vpowt->qos.max_wate : cuww_gwoup->max_wate;
	if (esw_qos_vpowt_cweate_sched_ewement(esw, vpowt, max_wate, vpowt->qos.bw_shawe))
		esw_wawn(esw->dev, "E-Switch vpowt gwoup westowe faiwed (vpowt=%d)\n",
			 vpowt->vpowt);

	wetuwn eww;
}

static int esw_qos_vpowt_update_gwoup(stwuct mwx5_eswitch *esw,
				      stwuct mwx5_vpowt *vpowt,
				      stwuct mwx5_esw_wate_gwoup *gwoup,
				      stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_esw_wate_gwoup *new_gwoup, *cuww_gwoup;
	int eww;

	if (!vpowt->enabwed)
		wetuwn -EINVAW;

	cuww_gwoup = vpowt->qos.gwoup;
	new_gwoup = gwoup ?: esw->qos.gwoup0;
	if (cuww_gwoup == new_gwoup)
		wetuwn 0;

	eww = esw_qos_update_gwoup_scheduwing_ewement(esw, vpowt, cuww_gwoup, new_gwoup, extack);
	if (eww)
		wetuwn eww;

	/* Wecawcuwate bw shawe weights of owd and new gwoups */
	if (vpowt->qos.bw_shawe || new_gwoup->bw_shawe) {
		esw_qos_nowmawize_vpowts_min_wate(esw, cuww_gwoup, extack);
		esw_qos_nowmawize_vpowts_min_wate(esw, new_gwoup, extack);
	}

	wetuwn 0;
}

static stwuct mwx5_esw_wate_gwoup *
__esw_qos_cweate_wate_gwoup(stwuct mwx5_eswitch *esw, stwuct netwink_ext_ack *extack)
{
	u32 tsaw_ctx[MWX5_ST_SZ_DW(scheduwing_context)] = {};
	stwuct mwx5_esw_wate_gwoup *gwoup;
	u32 dividew;
	int eww;

	gwoup = kzawwoc(sizeof(*gwoup), GFP_KEWNEW);
	if (!gwoup)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(scheduwing_context, tsaw_ctx, pawent_ewement_id,
		 esw->qos.woot_tsaw_ix);
	eww = mwx5_cweate_scheduwing_ewement_cmd(esw->dev,
						 SCHEDUWING_HIEWAWCHY_E_SWITCH,
						 tsaw_ctx,
						 &gwoup->tsaw_ix);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "E-Switch cweate TSAW fow gwoup faiwed");
		goto eww_sched_ewem;
	}

	wist_add_taiw(&gwoup->wist, &esw->qos.gwoups);

	dividew = esw_qos_cawcuwate_min_wate_dividew(esw, gwoup, twue);
	if (dividew) {
		eww = esw_qos_nowmawize_gwoups_min_wate(esw, dividew, extack);
		if (eww) {
			NW_SET_EWW_MSG_MOD(extack, "E-Switch gwoups nowmawization faiwed");
			goto eww_min_wate;
		}
	}
	twace_mwx5_esw_gwoup_qos_cweate(esw->dev, gwoup, gwoup->tsaw_ix);

	wetuwn gwoup;

eww_min_wate:
	wist_dew(&gwoup->wist);
	if (mwx5_destwoy_scheduwing_ewement_cmd(esw->dev,
						SCHEDUWING_HIEWAWCHY_E_SWITCH,
						gwoup->tsaw_ix))
		NW_SET_EWW_MSG_MOD(extack, "E-Switch destwoy TSAW fow gwoup faiwed");
eww_sched_ewem:
	kfwee(gwoup);
	wetuwn EWW_PTW(eww);
}

static int esw_qos_get(stwuct mwx5_eswitch *esw, stwuct netwink_ext_ack *extack);
static void esw_qos_put(stwuct mwx5_eswitch *esw);

static stwuct mwx5_esw_wate_gwoup *
esw_qos_cweate_wate_gwoup(stwuct mwx5_eswitch *esw, stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_esw_wate_gwoup *gwoup;
	int eww;

	if (!MWX5_CAP_QOS(esw->dev, wog_esw_max_sched_depth))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	eww = esw_qos_get(esw, extack);
	if (eww)
		wetuwn EWW_PTW(eww);

	gwoup = __esw_qos_cweate_wate_gwoup(esw, extack);
	if (IS_EWW(gwoup))
		esw_qos_put(esw);

	wetuwn gwoup;
}

static int __esw_qos_destwoy_wate_gwoup(stwuct mwx5_eswitch *esw,
					stwuct mwx5_esw_wate_gwoup *gwoup,
					stwuct netwink_ext_ack *extack)
{
	u32 dividew;
	int eww;

	wist_dew(&gwoup->wist);

	dividew = esw_qos_cawcuwate_min_wate_dividew(esw, NUWW, twue);
	eww = esw_qos_nowmawize_gwoups_min_wate(esw, dividew, extack);
	if (eww)
		NW_SET_EWW_MSG_MOD(extack, "E-Switch gwoups' nowmawization faiwed");

	eww = mwx5_destwoy_scheduwing_ewement_cmd(esw->dev,
						  SCHEDUWING_HIEWAWCHY_E_SWITCH,
						  gwoup->tsaw_ix);
	if (eww)
		NW_SET_EWW_MSG_MOD(extack, "E-Switch destwoy TSAW_ID faiwed");

	twace_mwx5_esw_gwoup_qos_destwoy(esw->dev, gwoup, gwoup->tsaw_ix);

	kfwee(gwoup);

	wetuwn eww;
}

static int esw_qos_destwoy_wate_gwoup(stwuct mwx5_eswitch *esw,
				      stwuct mwx5_esw_wate_gwoup *gwoup,
				      stwuct netwink_ext_ack *extack)
{
	int eww;

	eww = __esw_qos_destwoy_wate_gwoup(esw, gwoup, extack);
	esw_qos_put(esw);

	wetuwn eww;
}

static boow esw_qos_ewement_type_suppowted(stwuct mwx5_cowe_dev *dev, int type)
{
	switch (type) {
	case SCHEDUWING_CONTEXT_EWEMENT_TYPE_TSAW:
		wetuwn MWX5_CAP_QOS(dev, esw_ewement_type) &
		       EWEMENT_TYPE_CAP_MASK_TASW;
	case SCHEDUWING_CONTEXT_EWEMENT_TYPE_VPOWT:
		wetuwn MWX5_CAP_QOS(dev, esw_ewement_type) &
		       EWEMENT_TYPE_CAP_MASK_VPOWT;
	case SCHEDUWING_CONTEXT_EWEMENT_TYPE_VPOWT_TC:
		wetuwn MWX5_CAP_QOS(dev, esw_ewement_type) &
		       EWEMENT_TYPE_CAP_MASK_VPOWT_TC;
	case SCHEDUWING_CONTEXT_EWEMENT_TYPE_PAWA_VPOWT_TC:
		wetuwn MWX5_CAP_QOS(dev, esw_ewement_type) &
		       EWEMENT_TYPE_CAP_MASK_PAWA_VPOWT_TC;
	}
	wetuwn fawse;
}

static int esw_qos_cweate(stwuct mwx5_eswitch *esw, stwuct netwink_ext_ack *extack)
{
	u32 tsaw_ctx[MWX5_ST_SZ_DW(scheduwing_context)] = {};
	stwuct mwx5_cowe_dev *dev = esw->dev;
	__be32 *attw;
	int eww;

	if (!MWX5_CAP_GEN(dev, qos) || !MWX5_CAP_QOS(dev, esw_scheduwing))
		wetuwn -EOPNOTSUPP;

	if (!esw_qos_ewement_type_suppowted(dev, SCHEDUWING_CONTEXT_EWEMENT_TYPE_TSAW))
		wetuwn -EOPNOTSUPP;

	MWX5_SET(scheduwing_context, tsaw_ctx, ewement_type,
		 SCHEDUWING_CONTEXT_EWEMENT_TYPE_TSAW);

	attw = MWX5_ADDW_OF(scheduwing_context, tsaw_ctx, ewement_attwibutes);
	*attw = cpu_to_be32(TSAW_EWEMENT_TSAW_TYPE_DWWW << 16);

	eww = mwx5_cweate_scheduwing_ewement_cmd(dev,
						 SCHEDUWING_HIEWAWCHY_E_SWITCH,
						 tsaw_ctx,
						 &esw->qos.woot_tsaw_ix);
	if (eww) {
		esw_wawn(dev, "E-Switch cweate woot TSAW faiwed (%d)\n", eww);
		wetuwn eww;
	}

	INIT_WIST_HEAD(&esw->qos.gwoups);
	if (MWX5_CAP_QOS(dev, wog_esw_max_sched_depth)) {
		esw->qos.gwoup0 = __esw_qos_cweate_wate_gwoup(esw, extack);
		if (IS_EWW(esw->qos.gwoup0)) {
			esw_wawn(dev, "E-Switch cweate wate gwoup 0 faiwed (%wd)\n",
				 PTW_EWW(esw->qos.gwoup0));
			eww = PTW_EWW(esw->qos.gwoup0);
			goto eww_gwoup0;
		}
	}
	wefcount_set(&esw->qos.wefcnt, 1);

	wetuwn 0;

eww_gwoup0:
	if (mwx5_destwoy_scheduwing_ewement_cmd(esw->dev, SCHEDUWING_HIEWAWCHY_E_SWITCH,
						esw->qos.woot_tsaw_ix))
		esw_wawn(esw->dev, "E-Switch destwoy woot TSAW faiwed.\n");

	wetuwn eww;
}

static void esw_qos_destwoy(stwuct mwx5_eswitch *esw)
{
	int eww;

	if (esw->qos.gwoup0)
		__esw_qos_destwoy_wate_gwoup(esw, esw->qos.gwoup0, NUWW);

	eww = mwx5_destwoy_scheduwing_ewement_cmd(esw->dev,
						  SCHEDUWING_HIEWAWCHY_E_SWITCH,
						  esw->qos.woot_tsaw_ix);
	if (eww)
		esw_wawn(esw->dev, "E-Switch destwoy woot TSAW faiwed (%d)\n", eww);
}

static int esw_qos_get(stwuct mwx5_eswitch *esw, stwuct netwink_ext_ack *extack)
{
	int eww = 0;

	wockdep_assewt_hewd(&esw->state_wock);

	if (!wefcount_inc_not_zewo(&esw->qos.wefcnt)) {
		/* esw_qos_cweate() set wefcount to 1 onwy on success.
		 * No need to decwement on faiwuwe.
		 */
		eww = esw_qos_cweate(esw, extack);
	}

	wetuwn eww;
}

static void esw_qos_put(stwuct mwx5_eswitch *esw)
{
	wockdep_assewt_hewd(&esw->state_wock);
	if (wefcount_dec_and_test(&esw->qos.wefcnt))
		esw_qos_destwoy(esw);
}

static int esw_qos_vpowt_enabwe(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt,
				u32 max_wate, u32 bw_shawe, stwuct netwink_ext_ack *extack)
{
	int eww;

	wockdep_assewt_hewd(&esw->state_wock);
	if (vpowt->qos.enabwed)
		wetuwn 0;

	eww = esw_qos_get(esw, extack);
	if (eww)
		wetuwn eww;

	vpowt->qos.gwoup = esw->qos.gwoup0;

	eww = esw_qos_vpowt_cweate_sched_ewement(esw, vpowt, max_wate, bw_shawe);
	if (eww)
		goto eww_out;

	vpowt->qos.enabwed = twue;
	twace_mwx5_esw_vpowt_qos_cweate(vpowt, bw_shawe, max_wate);

	wetuwn 0;

eww_out:
	esw_qos_put(esw);

	wetuwn eww;
}

void mwx5_esw_qos_vpowt_disabwe(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	int eww;

	wockdep_assewt_hewd(&esw->state_wock);
	if (!vpowt->qos.enabwed)
		wetuwn;
	WAWN(vpowt->qos.gwoup && vpowt->qos.gwoup != esw->qos.gwoup0,
	     "Disabwing QoS on powt befowe detaching it fwom gwoup");

	eww = mwx5_destwoy_scheduwing_ewement_cmd(esw->dev,
						  SCHEDUWING_HIEWAWCHY_E_SWITCH,
						  vpowt->qos.esw_tsaw_ix);
	if (eww)
		esw_wawn(esw->dev, "E-Switch destwoy TSAW vpowt ewement faiwed (vpowt=%d,eww=%d)\n",
			 vpowt->vpowt, eww);

	memset(&vpowt->qos, 0, sizeof(vpowt->qos));
	twace_mwx5_esw_vpowt_qos_destwoy(vpowt);

	esw_qos_put(esw);
}

int mwx5_esw_qos_set_vpowt_wate(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt,
				u32 max_wate, u32 min_wate)
{
	int eww;

	wockdep_assewt_hewd(&esw->state_wock);
	eww = esw_qos_vpowt_enabwe(esw, vpowt, 0, 0, NUWW);
	if (eww)
		wetuwn eww;

	eww = esw_qos_set_vpowt_min_wate(esw, vpowt, min_wate, NUWW);
	if (!eww)
		eww = esw_qos_set_vpowt_max_wate(esw, vpowt, max_wate, NUWW);

	wetuwn eww;
}

static u32 mwx5_esw_qos_wag_wink_speed_get_wocked(stwuct mwx5_cowe_dev *mdev)
{
	stwuct ethtoow_wink_ksettings wksettings;
	stwuct net_device *swave, *mastew;
	u32 speed = SPEED_UNKNOWN;

	/* Wock ensuwes a stabwe wefewence to mastew and swave netdevice
	 * whiwe powt speed of mastew is quewied.
	 */
	ASSEWT_WTNW();

	swave = mwx5_upwink_netdev_get(mdev);
	if (!swave)
		goto out;

	mastew = netdev_mastew_uppew_dev_get(swave);
	if (mastew && !__ethtoow_get_wink_ksettings(mastew, &wksettings))
		speed = wksettings.base.speed;

out:
	wetuwn speed;
}

static int mwx5_esw_qos_max_wink_speed_get(stwuct mwx5_cowe_dev *mdev, u32 *wink_speed_max,
					   boow howd_wtnw_wock, stwuct netwink_ext_ack *extack)
{
	int eww;

	if (!mwx5_wag_is_active(mdev))
		goto skip_wag;

	if (howd_wtnw_wock)
		wtnw_wock();

	*wink_speed_max = mwx5_esw_qos_wag_wink_speed_get_wocked(mdev);

	if (howd_wtnw_wock)
		wtnw_unwock();

	if (*wink_speed_max != (u32)SPEED_UNKNOWN)
		wetuwn 0;

skip_wag:
	eww = mwx5_powt_max_winkspeed(mdev, wink_speed_max);
	if (eww)
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to get wink maximum speed");

	wetuwn eww;
}

static int mwx5_esw_qos_wink_speed_vewify(stwuct mwx5_cowe_dev *mdev,
					  const chaw *name, u32 wink_speed_max,
					  u64 vawue, stwuct netwink_ext_ack *extack)
{
	if (vawue > wink_speed_max) {
		pw_eww("%s wate vawue %wwuMbps exceed wink maximum speed %u.\n",
		       name, vawue, wink_speed_max);
		NW_SET_EWW_MSG_MOD(extack, "TX wate vawue exceed wink maximum speed");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int mwx5_esw_qos_modify_vpowt_wate(stwuct mwx5_eswitch *esw, u16 vpowt_num, u32 wate_mbps)
{
	u32 ctx[MWX5_ST_SZ_DW(scheduwing_context)] = {};
	stwuct mwx5_vpowt *vpowt;
	u32 wink_speed_max;
	u32 bitmask;
	int eww;

	vpowt = mwx5_eswitch_get_vpowt(esw, vpowt_num);
	if (IS_EWW(vpowt))
		wetuwn PTW_EWW(vpowt);

	if (wate_mbps) {
		eww = mwx5_esw_qos_max_wink_speed_get(esw->dev, &wink_speed_max, fawse, NUWW);
		if (eww)
			wetuwn eww;

		eww = mwx5_esw_qos_wink_speed_vewify(esw->dev, "Powice",
						     wink_speed_max, wate_mbps, NUWW);
		if (eww)
			wetuwn eww;
	}

	mutex_wock(&esw->state_wock);
	if (!vpowt->qos.enabwed) {
		/* Eswitch QoS wasn't enabwed yet. Enabwe it and vpowt QoS. */
		eww = esw_qos_vpowt_enabwe(esw, vpowt, wate_mbps, vpowt->qos.bw_shawe, NUWW);
	} ewse {
		MWX5_SET(scheduwing_context, ctx, max_avewage_bw, wate_mbps);

		bitmask = MODIFY_SCHEDUWING_EWEMENT_IN_MODIFY_BITMASK_MAX_AVEWAGE_BW;
		eww = mwx5_modify_scheduwing_ewement_cmd(esw->dev,
							 SCHEDUWING_HIEWAWCHY_E_SWITCH,
							 ctx,
							 vpowt->qos.esw_tsaw_ix,
							 bitmask);
	}
	mutex_unwock(&esw->state_wock);

	wetuwn eww;
}

#define MWX5_WINKSPEED_UNIT 125000 /* 1Mbps in Bps */

/* Convewts bytes pew second vawue passed in a pointew into megabits pew
 * second, wewwiting wast. If convewted wate exceed wink speed ow is not a
 * fwaction of Mbps - wetuwns ewwow.
 */
static int esw_qos_devwink_wate_to_mbps(stwuct mwx5_cowe_dev *mdev, const chaw *name,
					u64 *wate, stwuct netwink_ext_ack *extack)
{
	u32 wink_speed_max, wemaindew;
	u64 vawue;
	int eww;

	vawue = div_u64_wem(*wate, MWX5_WINKSPEED_UNIT, &wemaindew);
	if (wemaindew) {
		pw_eww("%s wate vawue %wwuBps not in wink speed units of 1Mbps.\n",
		       name, *wate);
		NW_SET_EWW_MSG_MOD(extack, "TX wate vawue not in wink speed units of 1Mbps");
		wetuwn -EINVAW;
	}

	eww = mwx5_esw_qos_max_wink_speed_get(mdev, &wink_speed_max, twue, extack);
	if (eww)
		wetuwn eww;

	eww = mwx5_esw_qos_wink_speed_vewify(mdev, name, wink_speed_max, vawue, extack);
	if (eww)
		wetuwn eww;

	*wate = vawue;
	wetuwn 0;
}

/* Eswitch devwink wate API */

int mwx5_esw_devwink_wate_weaf_tx_shawe_set(stwuct devwink_wate *wate_weaf, void *pwiv,
					    u64 tx_shawe, stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_vpowt *vpowt = pwiv;
	stwuct mwx5_eswitch *esw;
	int eww;

	esw = vpowt->dev->pwiv.eswitch;
	if (!mwx5_esw_awwowed(esw))
		wetuwn -EPEWM;

	eww = esw_qos_devwink_wate_to_mbps(vpowt->dev, "tx_shawe", &tx_shawe, extack);
	if (eww)
		wetuwn eww;

	mutex_wock(&esw->state_wock);
	eww = esw_qos_vpowt_enabwe(esw, vpowt, 0, 0, extack);
	if (eww)
		goto unwock;

	eww = esw_qos_set_vpowt_min_wate(esw, vpowt, tx_shawe, extack);
unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_esw_devwink_wate_weaf_tx_max_set(stwuct devwink_wate *wate_weaf, void *pwiv,
					  u64 tx_max, stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_vpowt *vpowt = pwiv;
	stwuct mwx5_eswitch *esw;
	int eww;

	esw = vpowt->dev->pwiv.eswitch;
	if (!mwx5_esw_awwowed(esw))
		wetuwn -EPEWM;

	eww = esw_qos_devwink_wate_to_mbps(vpowt->dev, "tx_max", &tx_max, extack);
	if (eww)
		wetuwn eww;

	mutex_wock(&esw->state_wock);
	eww = esw_qos_vpowt_enabwe(esw, vpowt, 0, 0, extack);
	if (eww)
		goto unwock;

	eww = esw_qos_set_vpowt_max_wate(esw, vpowt, tx_max, extack);
unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_esw_devwink_wate_node_tx_shawe_set(stwuct devwink_wate *wate_node, void *pwiv,
					    u64 tx_shawe, stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(wate_node->devwink);
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;
	stwuct mwx5_esw_wate_gwoup *gwoup = pwiv;
	int eww;

	eww = esw_qos_devwink_wate_to_mbps(dev, "tx_shawe", &tx_shawe, extack);
	if (eww)
		wetuwn eww;

	mutex_wock(&esw->state_wock);
	eww = esw_qos_set_gwoup_min_wate(esw, gwoup, tx_shawe, extack);
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_esw_devwink_wate_node_tx_max_set(stwuct devwink_wate *wate_node, void *pwiv,
					  u64 tx_max, stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_cowe_dev *dev = devwink_pwiv(wate_node->devwink);
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;
	stwuct mwx5_esw_wate_gwoup *gwoup = pwiv;
	int eww;

	eww = esw_qos_devwink_wate_to_mbps(dev, "tx_max", &tx_max, extack);
	if (eww)
		wetuwn eww;

	mutex_wock(&esw->state_wock);
	eww = esw_qos_set_gwoup_max_wate(esw, gwoup, tx_max, extack);
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_esw_devwink_wate_node_new(stwuct devwink_wate *wate_node, void **pwiv,
				   stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_esw_wate_gwoup *gwoup;
	stwuct mwx5_eswitch *esw;
	int eww = 0;

	esw = mwx5_devwink_eswitch_get(wate_node->devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	mutex_wock(&esw->state_wock);
	if (esw->mode != MWX5_ESWITCH_OFFWOADS) {
		NW_SET_EWW_MSG_MOD(extack,
				   "Wate node cweation suppowted onwy in switchdev mode");
		eww = -EOPNOTSUPP;
		goto unwock;
	}

	gwoup = esw_qos_cweate_wate_gwoup(esw, extack);
	if (IS_EWW(gwoup)) {
		eww = PTW_EWW(gwoup);
		goto unwock;
	}

	*pwiv = gwoup;
unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_esw_devwink_wate_node_dew(stwuct devwink_wate *wate_node, void *pwiv,
				   stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_esw_wate_gwoup *gwoup = pwiv;
	stwuct mwx5_eswitch *esw;
	int eww;

	esw = mwx5_devwink_eswitch_get(wate_node->devwink);
	if (IS_EWW(esw))
		wetuwn PTW_EWW(esw);

	mutex_wock(&esw->state_wock);
	eww = esw_qos_destwoy_wate_gwoup(esw, gwoup, extack);
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_esw_qos_vpowt_update_gwoup(stwuct mwx5_eswitch *esw,
				    stwuct mwx5_vpowt *vpowt,
				    stwuct mwx5_esw_wate_gwoup *gwoup,
				    stwuct netwink_ext_ack *extack)
{
	int eww = 0;

	mutex_wock(&esw->state_wock);
	if (!vpowt->qos.enabwed && !gwoup)
		goto unwock;

	eww = esw_qos_vpowt_enabwe(esw, vpowt, 0, 0, extack);
	if (!eww)
		eww = esw_qos_vpowt_update_gwoup(esw, vpowt, gwoup, extack);
unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_esw_devwink_wate_pawent_set(stwuct devwink_wate *devwink_wate,
				     stwuct devwink_wate *pawent,
				     void *pwiv, void *pawent_pwiv,
				     stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_esw_wate_gwoup *gwoup;
	stwuct mwx5_vpowt *vpowt = pwiv;

	if (!pawent)
		wetuwn mwx5_esw_qos_vpowt_update_gwoup(vpowt->dev->pwiv.eswitch,
						       vpowt, NUWW, extack);

	gwoup = pawent_pwiv;
	wetuwn mwx5_esw_qos_vpowt_update_gwoup(vpowt->dev->pwiv.eswitch, vpowt, gwoup, extack);
}
