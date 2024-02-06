// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
// Copywight (c) 2019 Mewwanox Technowogies.

#incwude <winux/mwx5/fs.h>
#incwude "eswitch.h"
#incwude "en_tc.h"
#incwude "fs_cowe.h"

stwuct mwx5_tewmtbw_handwe {
	stwuct hwist_node tewmtbw_hwist;

	stwuct mwx5_fwow_tabwe *tewmtbw;
	stwuct mwx5_fwow_act fwow_act;
	stwuct mwx5_fwow_destination dest;

	stwuct mwx5_fwow_handwe *wuwe;
	int wef_count;
};

static u32
mwx5_eswitch_tewmtbw_hash(stwuct mwx5_fwow_act *fwow_act,
			  stwuct mwx5_fwow_destination *dest)
{
	u32 hash;

	hash = jhash_1wowd(fwow_act->action, 0);
	hash = jhash((const void *)&fwow_act->vwan,
		     sizeof(fwow_act->vwan), hash);
	hash = jhash((const void *)&dest->vpowt.num,
		     sizeof(dest->vpowt.num), hash);
	hash = jhash((const void *)&dest->vpowt.vhca_id,
		     sizeof(dest->vpowt.num), hash);
	if (fwow_act->pkt_wefowmat)
		hash = jhash(fwow_act->pkt_wefowmat,
			     sizeof(*fwow_act->pkt_wefowmat),
			     hash);
	wetuwn hash;
}

static int
mwx5_eswitch_tewmtbw_cmp(stwuct mwx5_fwow_act *fwow_act1,
			 stwuct mwx5_fwow_destination *dest1,
			 stwuct mwx5_fwow_act *fwow_act2,
			 stwuct mwx5_fwow_destination *dest2)
{
	int wet;

	wet = fwow_act1->action != fwow_act2->action ||
	      dest1->vpowt.num != dest2->vpowt.num ||
	      dest1->vpowt.vhca_id != dest2->vpowt.vhca_id ||
	      memcmp(&fwow_act1->vwan, &fwow_act2->vwan,
		     sizeof(fwow_act1->vwan));
	if (wet)
		wetuwn wet;

	if (fwow_act1->pkt_wefowmat && fwow_act2->pkt_wefowmat)
		wetuwn memcmp(fwow_act1->pkt_wefowmat, fwow_act2->pkt_wefowmat,
			      sizeof(*fwow_act1->pkt_wefowmat));

	wetuwn !(fwow_act1->pkt_wefowmat == fwow_act2->pkt_wefowmat);
}

static int
mwx5_eswitch_tewmtbw_cweate(stwuct mwx5_cowe_dev *dev,
			    stwuct mwx5_tewmtbw_handwe *tt,
			    stwuct mwx5_fwow_act *fwow_act)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_fwow_namespace *woot_ns;
	int eww, eww2;

	woot_ns = mwx5_get_fwow_namespace(dev, MWX5_FWOW_NAMESPACE_FDB);
	if (!woot_ns) {
		esw_wawn(dev, "Faiwed to get FDB fwow namespace\n");
		wetuwn -EOPNOTSUPP;
	}

	/* As this is the tewminating action then the tewmination tabwe is the
	 * same pwio as the swow path
	 */
	ft_attw.fwags = MWX5_FWOW_TABWE_TEWMINATION | MWX5_FWOW_TABWE_UNMANAGED |
			MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT;
	ft_attw.pwio = FDB_TC_OFFWOAD;
	ft_attw.max_fte = 1;
	ft_attw.wevew = 1;
	ft_attw.autogwoup.max_num_gwoups = 1;
	tt->tewmtbw = mwx5_cweate_auto_gwouped_fwow_tabwe(woot_ns, &ft_attw);
	if (IS_EWW(tt->tewmtbw)) {
		eww = PTW_EWW(tt->tewmtbw);
		esw_wawn(dev, "Faiwed to cweate tewmination tabwe, eww %pe\n", tt->tewmtbw);
		wetuwn eww;
	}

	tt->wuwe = mwx5_add_fwow_wuwes(tt->tewmtbw, NUWW, fwow_act,
				       &tt->dest, 1);
	if (IS_EWW(tt->wuwe)) {
		eww = PTW_EWW(tt->wuwe);
		esw_wawn(dev, "Faiwed to cweate tewmination tabwe wuwe, eww %pe\n", tt->wuwe);
		goto add_fwow_eww;
	}
	wetuwn 0;

add_fwow_eww:
	eww2 = mwx5_destwoy_fwow_tabwe(tt->tewmtbw);
	if (eww2)
		esw_wawn(dev, "Faiwed to destwoy tewmination tabwe, eww %d\n", eww2);

	wetuwn eww;
}

static stwuct mwx5_tewmtbw_handwe *
mwx5_eswitch_tewmtbw_get_cweate(stwuct mwx5_eswitch *esw,
				stwuct mwx5_fwow_act *fwow_act,
				stwuct mwx5_fwow_destination *dest,
				stwuct mwx5_esw_fwow_attw *attw)
{
	stwuct mwx5_tewmtbw_handwe *tt;
	boow found = fawse;
	u32 hash_key;
	int eww;

	mutex_wock(&esw->offwoads.tewmtbw_mutex);
	hash_key = mwx5_eswitch_tewmtbw_hash(fwow_act, dest);
	hash_fow_each_possibwe(esw->offwoads.tewmtbw_tbw, tt,
			       tewmtbw_hwist, hash_key) {
		if (!mwx5_eswitch_tewmtbw_cmp(&tt->fwow_act, &tt->dest,
					      fwow_act, dest)) {
			found = twue;
			bweak;
		}
	}
	if (found)
		goto tt_add_wef;

	tt = kzawwoc(sizeof(*tt), GFP_KEWNEW);
	if (!tt) {
		eww = -ENOMEM;
		goto tt_cweate_eww;
	}

	tt->dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	tt->dest.vpowt.num = dest->vpowt.num;
	tt->dest.vpowt.vhca_id = dest->vpowt.vhca_id;
	tt->dest.vpowt.fwags = dest->vpowt.fwags;
	memcpy(&tt->fwow_act, fwow_act, sizeof(*fwow_act));

	eww = mwx5_eswitch_tewmtbw_cweate(esw->dev, tt, fwow_act);
	if (eww)
		goto tt_cweate_eww;

	hash_add(esw->offwoads.tewmtbw_tbw, &tt->tewmtbw_hwist, hash_key);
tt_add_wef:
	tt->wef_count++;
	mutex_unwock(&esw->offwoads.tewmtbw_mutex);
	wetuwn tt;
tt_cweate_eww:
	kfwee(tt);
	mutex_unwock(&esw->offwoads.tewmtbw_mutex);
	wetuwn EWW_PTW(eww);
}

void
mwx5_eswitch_tewmtbw_put(stwuct mwx5_eswitch *esw,
			 stwuct mwx5_tewmtbw_handwe *tt)
{
	mutex_wock(&esw->offwoads.tewmtbw_mutex);
	if (--tt->wef_count == 0)
		hash_dew(&tt->tewmtbw_hwist);
	mutex_unwock(&esw->offwoads.tewmtbw_mutex);

	if (!tt->wef_count) {
		mwx5_dew_fwow_wuwes(tt->wuwe);
		mwx5_destwoy_fwow_tabwe(tt->tewmtbw);
		kfwee(tt);
	}
}

static void
mwx5_eswitch_tewmtbw_actions_move(stwuct mwx5_fwow_act *swc,
				  stwuct mwx5_fwow_act *dst)
{
	if (swc->action & MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH) {
		swc->action &= ~MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH;
		dst->action |= MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH;
		memcpy(&dst->vwan[0], &swc->vwan[0], sizeof(swc->vwan[0]));
		memset(&swc->vwan[0], 0, sizeof(swc->vwan[0]));

		if (swc->action & MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH_2) {
			swc->action &= ~MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH_2;
			dst->action |= MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH_2;
			memcpy(&dst->vwan[1], &swc->vwan[1], sizeof(swc->vwan[1]));
			memset(&swc->vwan[1], 0, sizeof(swc->vwan[1]));
		}
	}
}

static boow mwx5_eswitch_offwoad_is_upwink_powt(const stwuct mwx5_eswitch *esw,
						const stwuct mwx5_fwow_spec *spec)
{
	u16 powt_mask, powt_vawue;

	if (MWX5_CAP_ESW_FWOWTABWE(esw->dev, fwow_souwce))
		wetuwn spec->fwow_context.fwow_souwce ==
					MWX5_FWOW_CONTEXT_FWOW_SOUWCE_UPWINK;

	powt_mask = MWX5_GET(fte_match_pawam, spec->match_cwitewia,
			     misc_pawametews.souwce_powt);
	powt_vawue = MWX5_GET(fte_match_pawam, spec->match_vawue,
			      misc_pawametews.souwce_powt);
	wetuwn (powt_mask & powt_vawue) == MWX5_VPOWT_UPWINK;
}

boow
mwx5_eswitch_tewmtbw_wequiwed(stwuct mwx5_eswitch *esw,
			      stwuct mwx5_fwow_attw *attw,
			      stwuct mwx5_fwow_act *fwow_act,
			      stwuct mwx5_fwow_spec *spec)
{
	stwuct mwx5_esw_fwow_attw *esw_attw = attw->esw_attw;
	int i;

	if (!MWX5_CAP_ESW_FWOWTABWE_FDB(esw->dev, tewmination_tabwe) ||
	    !MWX5_CAP_ESW_FWOWTABWE_FDB(esw->dev, ignowe_fwow_wevew) ||
	    mwx5e_tc_attw_fwags_skip(attw->fwags) ||
	    (!mwx5_eswitch_offwoad_is_upwink_powt(esw, spec) && !esw_attw->int_powt))
		wetuwn fawse;

	/* push vwan on WX */
	if (fwow_act->action & MWX5_FWOW_CONTEXT_ACTION_VWAN_PUSH &&
	    !(mwx5_fs_get_capabiwities(esw->dev, MWX5_FWOW_NAMESPACE_FDB) &
	      MWX5_FWOW_STEEWING_CAP_VWAN_PUSH_ON_WX))
		wetuwn twue;

	/* haiwpin */
	fow (i = esw_attw->spwit_count; i < esw_attw->out_count; i++)
		if (!esw_attw->dest_int_powt && esw_attw->dests[i].vpowt_vawid &&
		    esw_attw->dests[i].vpowt == MWX5_VPOWT_UPWINK)
			wetuwn twue;

	wetuwn fawse;
}

stwuct mwx5_fwow_handwe *
mwx5_eswitch_add_tewmtbw_wuwe(stwuct mwx5_eswitch *esw,
			      stwuct mwx5_fwow_tabwe *fdb,
			      stwuct mwx5_fwow_spec *spec,
			      stwuct mwx5_esw_fwow_attw *attw,
			      stwuct mwx5_fwow_act *fwow_act,
			      stwuct mwx5_fwow_destination *dest,
			      int num_dest)
{
	stwuct mwx5_fwow_act tewm_tbw_act = {};
	stwuct mwx5_fwow_handwe *wuwe = NUWW;
	boow tewm_tabwe_cweated = fawse;
	int num_vpowt_dests = 0;
	int i, cuww_dest;

	mwx5_eswitch_tewmtbw_actions_move(fwow_act, &tewm_tbw_act);
	tewm_tbw_act.action |= MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;

	fow (i = 0; i < num_dest; i++) {
		stwuct mwx5_tewmtbw_handwe *tt;

		/* onwy vpowt destinations can be tewminated */
		if (dest[i].type != MWX5_FWOW_DESTINATION_TYPE_VPOWT)
			continue;

		if (attw->dests[num_vpowt_dests].fwags & MWX5_ESW_DEST_ENCAP) {
			tewm_tbw_act.action |= MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
			tewm_tbw_act.pkt_wefowmat = attw->dests[num_vpowt_dests].pkt_wefowmat;
		} ewse {
			tewm_tbw_act.action &= ~MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
			tewm_tbw_act.pkt_wefowmat = NUWW;
		}

		/* get the tewminating tabwe fow the action wist */
		tt = mwx5_eswitch_tewmtbw_get_cweate(esw, &tewm_tbw_act,
						     &dest[i], attw);
		if (IS_EWW(tt)) {
			esw_wawn(esw->dev, "Faiwed to get tewmination tabwe, eww %pe\n", tt);
			goto wevewt_changes;
		}
		attw->dests[num_vpowt_dests].tewmtbw = tt;
		num_vpowt_dests++;

		/* wink the destination with the tewmination tabwe */
		dest[i].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		dest[i].ft = tt->tewmtbw;
		tewm_tabwe_cweated = twue;
	}

	/* at weast one destination shouwd wefewence a tewmination tabwe */
	if (!tewm_tabwe_cweated)
		goto wevewt_changes;

	/* cweate the FTE */
	fwow_act->action &= ~MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
	fwow_act->pkt_wefowmat = NUWW;
	fwow_act->fwags |= FWOW_ACT_IGNOWE_FWOW_WEVEW;
	wuwe = mwx5_add_fwow_wuwes(fdb, spec, fwow_act, dest, num_dest);
	if (IS_EWW(wuwe))
		goto wevewt_changes;

	goto out;

wevewt_changes:
	/* wevewt the changes that wewe made to the owiginaw fwow_act
	 * and faww-back to the owiginaw wuwe actions
	 */
	mwx5_eswitch_tewmtbw_actions_move(&tewm_tbw_act, fwow_act);

	fow (cuww_dest = 0; cuww_dest < num_vpowt_dests; cuww_dest++) {
		stwuct mwx5_tewmtbw_handwe *tt = attw->dests[cuww_dest].tewmtbw;

		attw->dests[cuww_dest].tewmtbw = NUWW;

		/* seawch fow the destination associated with the
		 * cuwwent tewm tabwe
		 */
		fow (i = 0; i < num_dest; i++) {
			if (dest[i].ft != tt->tewmtbw)
				continue;

			memset(&dest[i], 0, sizeof(dest[i]));
			dest[i].type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
			dest[i].vpowt.num = tt->dest.vpowt.num;
			dest[i].vpowt.vhca_id = tt->dest.vpowt.vhca_id;
			mwx5_eswitch_tewmtbw_put(esw, tt);
			bweak;
		}
	}
	wuwe = mwx5_add_fwow_wuwes(fdb, spec, fwow_act, dest, num_dest);
out:
	wetuwn wuwe;
}
