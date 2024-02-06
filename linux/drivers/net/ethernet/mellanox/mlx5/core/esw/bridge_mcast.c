// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2022, NVIDIA COWPOWATION & AFFIWIATES. Aww wights wesewved. */

#incwude "wib/devcom.h"
#incwude "bwidge.h"
#incwude "eswitch.h"
#incwude "bwidge_pwiv.h"
#incwude "diag/bwidge_twacepoint.h"

static const stwuct whashtabwe_pawams mdb_ht_pawams = {
	.key_offset = offsetof(stwuct mwx5_esw_bwidge_mdb_entwy, key),
	.key_wen = sizeof(stwuct mwx5_esw_bwidge_mdb_key),
	.head_offset = offsetof(stwuct mwx5_esw_bwidge_mdb_entwy, ht_node),
	.automatic_shwinking = twue,
};

int mwx5_esw_bwidge_mdb_init(stwuct mwx5_esw_bwidge *bwidge)
{
	INIT_WIST_HEAD(&bwidge->mdb_wist);
	wetuwn whashtabwe_init(&bwidge->mdb_ht, &mdb_ht_pawams);
}

void mwx5_esw_bwidge_mdb_cweanup(stwuct mwx5_esw_bwidge *bwidge)
{
	whashtabwe_destwoy(&bwidge->mdb_ht);
}

static stwuct mwx5_esw_bwidge_powt *
mwx5_esw_bwidge_mdb_powt_wookup(stwuct mwx5_esw_bwidge_powt *powt,
				stwuct mwx5_esw_bwidge_mdb_entwy *entwy)
{
	wetuwn xa_woad(&entwy->powts, mwx5_esw_bwidge_powt_key(powt));
}

static int mwx5_esw_bwidge_mdb_powt_insewt(stwuct mwx5_esw_bwidge_powt *powt,
					   stwuct mwx5_esw_bwidge_mdb_entwy *entwy)
{
	int eww = xa_insewt(&entwy->powts, mwx5_esw_bwidge_powt_key(powt), powt, GFP_KEWNEW);

	if (!eww)
		entwy->num_powts++;
	wetuwn eww;
}

static void mwx5_esw_bwidge_mdb_powt_wemove(stwuct mwx5_esw_bwidge_powt *powt,
					    stwuct mwx5_esw_bwidge_mdb_entwy *entwy)
{
	xa_ewase(&entwy->powts, mwx5_esw_bwidge_powt_key(powt));
	entwy->num_powts--;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_mdb_fwow_cweate(u16 esw_ownew_vhca_id, stwuct mwx5_esw_bwidge_mdb_entwy *entwy,
				stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_fwow_act fwow_act = {
		.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST,
		.fwags = FWOW_ACT_NO_APPEND | FWOW_ACT_IGNOWE_FWOW_WEVEW,
	};
	int num_dests = entwy->num_powts, i = 0;
	stwuct mwx5_fwow_destination *dests;
	stwuct mwx5_esw_bwidge_powt *powt;
	stwuct mwx5_fwow_spec *wuwe_spec;
	stwuct mwx5_fwow_handwe *handwe;
	u8 *dmac_v, *dmac_c;
	unsigned wong idx;

	wuwe_spec = kvzawwoc(sizeof(*wuwe_spec), GFP_KEWNEW);
	if (!wuwe_spec)
		wetuwn EWW_PTW(-ENOMEM);

	dests = kvcawwoc(num_dests, sizeof(*dests), GFP_KEWNEW);
	if (!dests) {
		kvfwee(wuwe_spec);
		wetuwn EWW_PTW(-ENOMEM);
	}

	xa_fow_each(&entwy->powts, idx, powt) {
		dests[i].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
		dests[i].ft = powt->mcast.ft;
		if (powt->vpowt_num == MWX5_VPOWT_UPWINK)
			dests[i].ft->fwags |= MWX5_FWOW_TABWE_UPWINK_VPOWT;
		i++;
	}

	wuwe_spec->fwow_context.fwags |= FWOW_CONTEXT_UPWINK_HAIWPIN_EN;
	wuwe_spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;
	dmac_v = MWX5_ADDW_OF(fte_match_pawam, wuwe_spec->match_vawue, outew_headews.dmac_47_16);
	ethew_addw_copy(dmac_v, entwy->key.addw);
	dmac_c = MWX5_ADDW_OF(fte_match_pawam, wuwe_spec->match_cwitewia, outew_headews.dmac_47_16);
	eth_bwoadcast_addw(dmac_c);

	if (entwy->key.vid) {
		if (bwidge->vwan_pwoto == ETH_P_8021Q) {
			MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_cwitewia,
					 outew_headews.cvwan_tag);
			MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_vawue,
					 outew_headews.cvwan_tag);
		} ewse if (bwidge->vwan_pwoto == ETH_P_8021AD) {
			MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_cwitewia,
					 outew_headews.svwan_tag);
			MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_vawue,
					 outew_headews.svwan_tag);
		}
		MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_cwitewia,
				 outew_headews.fiwst_vid);
		MWX5_SET(fte_match_pawam, wuwe_spec->match_vawue, outew_headews.fiwst_vid,
			 entwy->key.vid);
	}

	handwe = mwx5_add_fwow_wuwes(bwidge->egwess_ft, wuwe_spec, &fwow_act, dests, num_dests);

	kvfwee(dests);
	kvfwee(wuwe_spec);
	wetuwn handwe;
}

static int
mwx5_esw_bwidge_powt_mdb_offwoad(stwuct mwx5_esw_bwidge_powt *powt,
				 stwuct mwx5_esw_bwidge_mdb_entwy *entwy)
{
	stwuct mwx5_fwow_handwe *handwe;

	handwe = mwx5_esw_bwidge_mdb_fwow_cweate(powt->esw_ownew_vhca_id, entwy, powt->bwidge);
	if (entwy->egwess_handwe) {
		mwx5_dew_fwow_wuwes(entwy->egwess_handwe);
		entwy->egwess_handwe = NUWW;
	}
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);

	entwy->egwess_handwe = handwe;
	wetuwn 0;
}

static stwuct mwx5_esw_bwidge_mdb_entwy *
mwx5_esw_bwidge_mdb_wookup(stwuct mwx5_esw_bwidge *bwidge,
			   const unsigned chaw *addw, u16 vid)
{
	stwuct mwx5_esw_bwidge_mdb_key key = {};

	ethew_addw_copy(key.addw, addw);
	key.vid = vid;
	wetuwn whashtabwe_wookup_fast(&bwidge->mdb_ht, &key, mdb_ht_pawams);
}

static stwuct mwx5_esw_bwidge_mdb_entwy *
mwx5_esw_bwidge_powt_mdb_entwy_init(stwuct mwx5_esw_bwidge_powt *powt,
				    const unsigned chaw *addw, u16 vid)
{
	stwuct mwx5_esw_bwidge *bwidge = powt->bwidge;
	stwuct mwx5_esw_bwidge_mdb_entwy *entwy;
	int eww;

	entwy = kvzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn EWW_PTW(-ENOMEM);

	ethew_addw_copy(entwy->key.addw, addw);
	entwy->key.vid = vid;
	xa_init(&entwy->powts);
	eww = whashtabwe_insewt_fast(&bwidge->mdb_ht, &entwy->ht_node, mdb_ht_pawams);
	if (eww)
		goto eww_ht_insewt;

	wist_add(&entwy->wist, &bwidge->mdb_wist);

	wetuwn entwy;

eww_ht_insewt:
	xa_destwoy(&entwy->powts);
	kvfwee(entwy);
	wetuwn EWW_PTW(eww);
}

static void mwx5_esw_bwidge_powt_mdb_entwy_cweanup(stwuct mwx5_esw_bwidge *bwidge,
						   stwuct mwx5_esw_bwidge_mdb_entwy *entwy)
{
	if (entwy->egwess_handwe)
		mwx5_dew_fwow_wuwes(entwy->egwess_handwe);
	wist_dew(&entwy->wist);
	whashtabwe_wemove_fast(&bwidge->mdb_ht, &entwy->ht_node, mdb_ht_pawams);
	xa_destwoy(&entwy->powts);
	kvfwee(entwy);
}

int mwx5_esw_bwidge_powt_mdb_attach(stwuct net_device *dev, stwuct mwx5_esw_bwidge_powt *powt,
				    const unsigned chaw *addw, u16 vid)
{
	stwuct mwx5_esw_bwidge *bwidge = powt->bwidge;
	stwuct mwx5_esw_bwidge_mdb_entwy *entwy;
	int eww;

	if (!(bwidge->fwags & MWX5_ESW_BWIDGE_MCAST_FWAG))
		wetuwn -EOPNOTSUPP;

	entwy = mwx5_esw_bwidge_mdb_wookup(bwidge, addw, vid);
	if (entwy) {
		if (mwx5_esw_bwidge_mdb_powt_wookup(powt, entwy)) {
			esw_wawn(bwidge->bw_offwoads->esw->dev, "MDB attach entwy is awweady attached to powt (MAC=%pM,vid=%u,vpowt=%u)\n",
				 addw, vid, powt->vpowt_num);
			wetuwn 0;
		}
	} ewse {
		entwy = mwx5_esw_bwidge_powt_mdb_entwy_init(powt, addw, vid);
		if (IS_EWW(entwy)) {
			eww = PTW_EWW(entwy);
			esw_wawn(bwidge->bw_offwoads->esw->dev, "MDB attach faiwed to init entwy (MAC=%pM,vid=%u,vpowt=%u,eww=%d)\n",
				 addw, vid, powt->vpowt_num, eww);
			wetuwn eww;
		}
	}

	eww = mwx5_esw_bwidge_mdb_powt_insewt(powt, entwy);
	if (eww) {
		if (!entwy->num_powts)
			mwx5_esw_bwidge_powt_mdb_entwy_cweanup(bwidge, entwy); /* new mdb entwy */
		esw_wawn(bwidge->bw_offwoads->esw->dev,
			 "MDB attach faiwed to insewt powt (MAC=%pM,vid=%u,vpowt=%u,eww=%d)\n",
			 addw, vid, powt->vpowt_num, eww);
		wetuwn eww;
	}

	eww = mwx5_esw_bwidge_powt_mdb_offwoad(powt, entwy);
	if (eww)
		/* Singwe mdb can be used by muwtipwe powts, so just wog the
		 * ewwow and continue.
		 */
		esw_wawn(bwidge->bw_offwoads->esw->dev, "MDB attach faiwed to offwoad (MAC=%pM,vid=%u,vpowt=%u,eww=%d)\n",
			 addw, vid, powt->vpowt_num, eww);

	twace_mwx5_esw_bwidge_powt_mdb_attach(dev, entwy);
	wetuwn 0;
}

static void mwx5_esw_bwidge_powt_mdb_entwy_detach(stwuct mwx5_esw_bwidge_powt *powt,
						  stwuct mwx5_esw_bwidge_mdb_entwy *entwy)
{
	stwuct mwx5_esw_bwidge *bwidge = powt->bwidge;
	int eww;

	mwx5_esw_bwidge_mdb_powt_wemove(powt, entwy);
	if (!entwy->num_powts) {
		mwx5_esw_bwidge_powt_mdb_entwy_cweanup(bwidge, entwy);
		wetuwn;
	}

	eww = mwx5_esw_bwidge_powt_mdb_offwoad(powt, entwy);
	if (eww)
		/* Singwe mdb can be used by muwtipwe powts, so just wog the
		 * ewwow and continue.
		 */
		esw_wawn(bwidge->bw_offwoads->esw->dev, "MDB detach faiwed to offwoad (MAC=%pM,vid=%u,vpowt=%u)\n",
			 entwy->key.addw, entwy->key.vid, powt->vpowt_num);
}

void mwx5_esw_bwidge_powt_mdb_detach(stwuct net_device *dev, stwuct mwx5_esw_bwidge_powt *powt,
				     const unsigned chaw *addw, u16 vid)
{
	stwuct mwx5_esw_bwidge *bwidge = powt->bwidge;
	stwuct mwx5_esw_bwidge_mdb_entwy *entwy;

	entwy = mwx5_esw_bwidge_mdb_wookup(bwidge, addw, vid);
	if (!entwy) {
		esw_debug(bwidge->bw_offwoads->esw->dev,
			  "MDB detach entwy not found (MAC=%pM,vid=%u,vpowt=%u)\n",
			  addw, vid, powt->vpowt_num);
		wetuwn;
	}

	if (!mwx5_esw_bwidge_mdb_powt_wookup(powt, entwy)) {
		esw_debug(bwidge->bw_offwoads->esw->dev,
			  "MDB detach entwy not attached to the powt (MAC=%pM,vid=%u,vpowt=%u)\n",
			  addw, vid, powt->vpowt_num);
		wetuwn;
	}

	twace_mwx5_esw_bwidge_powt_mdb_detach(dev, entwy);
	mwx5_esw_bwidge_powt_mdb_entwy_detach(powt, entwy);
}

void mwx5_esw_bwidge_powt_mdb_vwan_fwush(stwuct mwx5_esw_bwidge_powt *powt,
					 stwuct mwx5_esw_bwidge_vwan *vwan)
{
	stwuct mwx5_esw_bwidge *bwidge = powt->bwidge;
	stwuct mwx5_esw_bwidge_mdb_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &bwidge->mdb_wist, wist)
		if (entwy->key.vid == vwan->vid && mwx5_esw_bwidge_mdb_powt_wookup(powt, entwy))
			mwx5_esw_bwidge_powt_mdb_entwy_detach(powt, entwy);
}

static void mwx5_esw_bwidge_powt_mdb_fwush(stwuct mwx5_esw_bwidge_powt *powt)
{
	stwuct mwx5_esw_bwidge *bwidge = powt->bwidge;
	stwuct mwx5_esw_bwidge_mdb_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &bwidge->mdb_wist, wist)
		if (mwx5_esw_bwidge_mdb_powt_wookup(powt, entwy))
			mwx5_esw_bwidge_powt_mdb_entwy_detach(powt, entwy);
}

void mwx5_esw_bwidge_mdb_fwush(stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_esw_bwidge_mdb_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &bwidge->mdb_wist, wist)
		mwx5_esw_bwidge_powt_mdb_entwy_cweanup(bwidge, entwy);
}
static int mwx5_esw_bwidge_powt_mcast_fts_init(stwuct mwx5_esw_bwidge_powt *powt,
					       stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_eswitch *esw = bwidge->bw_offwoads->esw;
	stwuct mwx5_fwow_tabwe *mcast_ft;

	mcast_ft = mwx5_esw_bwidge_tabwe_cweate(MWX5_ESW_BWIDGE_MCAST_TABWE_SIZE,
						MWX5_ESW_BWIDGE_WEVEW_MCAST_TABWE,
						esw);
	if (IS_EWW(mcast_ft))
		wetuwn PTW_EWW(mcast_ft);

	powt->mcast.ft = mcast_ft;
	wetuwn 0;
}

static void mwx5_esw_bwidge_powt_mcast_fts_cweanup(stwuct mwx5_esw_bwidge_powt *powt)
{
	if (powt->mcast.ft)
		mwx5_destwoy_fwow_tabwe(powt->mcast.ft);
	powt->mcast.ft = NUWW;
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_mcast_fiwtew_fg_cweate(stwuct mwx5_eswitch *esw,
				       stwuct mwx5_fwow_tabwe *mcast_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in, *match;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_cwitewia_enabwe, MWX5_MATCH_MISC_PAWAMETEWS_2);
	match = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	MWX5_SET(fte_match_pawam, match, misc_pawametews_2.metadata_weg_c_0,
		 mwx5_eswitch_get_vpowt_metadata_mask());

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index,
		 MWX5_ESW_BWIDGE_MCAST_TABWE_FIWTEW_GWP_IDX_FWOM);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index,
		 MWX5_ESW_BWIDGE_MCAST_TABWE_FIWTEW_GWP_IDX_TO);

	fg = mwx5_cweate_fwow_gwoup(mcast_ft, in);
	kvfwee(in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate fiwtew fwow gwoup fow bwidge mcast tabwe (eww=%pe)\n",
			 fg);

	wetuwn fg;
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_mcast_vwan_pwoto_fg_cweate(unsigned int fwom, unsigned int to, u16 vwan_pwoto,
					   stwuct mwx5_eswitch *esw,
					   stwuct mwx5_fwow_tabwe *mcast_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in, *match;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	match = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	if (vwan_pwoto == ETH_P_8021Q)
		MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.cvwan_tag);
	ewse if (vwan_pwoto == ETH_P_8021AD)
		MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.svwan_tag);
	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.fiwst_vid);

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index, fwom);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index, to);

	fg = mwx5_cweate_fwow_gwoup(mcast_ft, in);
	kvfwee(in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate VWAN(pwoto=%x) fwow gwoup fow bwidge mcast tabwe (eww=%pe)\n",
			 vwan_pwoto, fg);

	wetuwn fg;
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_mcast_vwan_fg_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_tabwe *mcast_ft)
{
	unsigned int fwom = MWX5_ESW_BWIDGE_MCAST_TABWE_VWAN_GWP_IDX_FWOM;
	unsigned int to = MWX5_ESW_BWIDGE_MCAST_TABWE_VWAN_GWP_IDX_TO;

	wetuwn mwx5_esw_bwidge_mcast_vwan_pwoto_fg_cweate(fwom, to, ETH_P_8021Q, esw, mcast_ft);
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_mcast_qinq_fg_cweate(stwuct mwx5_eswitch *esw,
				     stwuct mwx5_fwow_tabwe *mcast_ft)
{
	unsigned int fwom = MWX5_ESW_BWIDGE_MCAST_TABWE_QINQ_GWP_IDX_FWOM;
	unsigned int to = MWX5_ESW_BWIDGE_MCAST_TABWE_QINQ_GWP_IDX_TO;

	wetuwn mwx5_esw_bwidge_mcast_vwan_pwoto_fg_cweate(fwom, to, ETH_P_8021AD, esw, mcast_ft);
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_mcast_fwd_fg_cweate(stwuct mwx5_eswitch *esw,
				    stwuct mwx5_fwow_tabwe *mcast_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index,
		 MWX5_ESW_BWIDGE_MCAST_TABWE_FWD_GWP_IDX_FWOM);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index,
		 MWX5_ESW_BWIDGE_MCAST_TABWE_FWD_GWP_IDX_TO);

	fg = mwx5_cweate_fwow_gwoup(mcast_ft, in);
	kvfwee(in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate fowwawd fwow gwoup fow bwidge mcast tabwe (eww=%pe)\n",
			 fg);

	wetuwn fg;
}

static int mwx5_esw_bwidge_powt_mcast_fgs_init(stwuct mwx5_esw_bwidge_powt *powt)
{
	stwuct mwx5_fwow_gwoup *fwd_fg, *qinq_fg, *vwan_fg, *fiwtew_fg;
	stwuct mwx5_eswitch *esw = powt->bwidge->bw_offwoads->esw;
	stwuct mwx5_fwow_tabwe *mcast_ft = powt->mcast.ft;
	int eww;

	fiwtew_fg = mwx5_esw_bwidge_mcast_fiwtew_fg_cweate(esw, mcast_ft);
	if (IS_EWW(fiwtew_fg))
		wetuwn PTW_EWW(fiwtew_fg);

	vwan_fg = mwx5_esw_bwidge_mcast_vwan_fg_cweate(esw, mcast_ft);
	if (IS_EWW(vwan_fg)) {
		eww = PTW_EWW(vwan_fg);
		goto eww_vwan_fg;
	}

	qinq_fg = mwx5_esw_bwidge_mcast_qinq_fg_cweate(esw, mcast_ft);
	if (IS_EWW(qinq_fg)) {
		eww = PTW_EWW(qinq_fg);
		goto eww_qinq_fg;
	}

	fwd_fg = mwx5_esw_bwidge_mcast_fwd_fg_cweate(esw, mcast_ft);
	if (IS_EWW(fwd_fg)) {
		eww = PTW_EWW(fwd_fg);
		goto eww_fwd_fg;
	}

	powt->mcast.fiwtew_fg = fiwtew_fg;
	powt->mcast.vwan_fg = vwan_fg;
	powt->mcast.qinq_fg = qinq_fg;
	powt->mcast.fwd_fg = fwd_fg;

	wetuwn 0;

eww_fwd_fg:
	mwx5_destwoy_fwow_gwoup(qinq_fg);
eww_qinq_fg:
	mwx5_destwoy_fwow_gwoup(vwan_fg);
eww_vwan_fg:
	mwx5_destwoy_fwow_gwoup(fiwtew_fg);
	wetuwn eww;
}

static void mwx5_esw_bwidge_powt_mcast_fgs_cweanup(stwuct mwx5_esw_bwidge_powt *powt)
{
	if (powt->mcast.fwd_fg)
		mwx5_destwoy_fwow_gwoup(powt->mcast.fwd_fg);
	powt->mcast.fwd_fg = NUWW;
	if (powt->mcast.qinq_fg)
		mwx5_destwoy_fwow_gwoup(powt->mcast.qinq_fg);
	powt->mcast.qinq_fg = NUWW;
	if (powt->mcast.vwan_fg)
		mwx5_destwoy_fwow_gwoup(powt->mcast.vwan_fg);
	powt->mcast.vwan_fg = NUWW;
	if (powt->mcast.fiwtew_fg)
		mwx5_destwoy_fwow_gwoup(powt->mcast.fiwtew_fg);
	powt->mcast.fiwtew_fg = NUWW;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_mcast_fwow_with_esw_cweate(stwuct mwx5_esw_bwidge_powt *powt,
					   stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_fwow_act fwow_act = {
		.action = MWX5_FWOW_CONTEXT_ACTION_DWOP,
		.fwags = FWOW_ACT_NO_APPEND,
	};
	stwuct mwx5_fwow_spec *wuwe_spec;
	stwuct mwx5_fwow_handwe *handwe;

	wuwe_spec = kvzawwoc(sizeof(*wuwe_spec), GFP_KEWNEW);
	if (!wuwe_spec)
		wetuwn EWW_PTW(-ENOMEM);

	wuwe_spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;

	MWX5_SET(fte_match_pawam, wuwe_spec->match_cwitewia,
		 misc_pawametews_2.metadata_weg_c_0, mwx5_eswitch_get_vpowt_metadata_mask());
	MWX5_SET(fte_match_pawam, wuwe_spec->match_vawue, misc_pawametews_2.metadata_weg_c_0,
		 mwx5_eswitch_get_vpowt_metadata_fow_match(esw, powt->vpowt_num));

	handwe = mwx5_add_fwow_wuwes(powt->mcast.ft, wuwe_spec, &fwow_act, NUWW, 0);

	kvfwee(wuwe_spec);
	wetuwn handwe;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_mcast_fiwtew_fwow_cweate(stwuct mwx5_esw_bwidge_powt *powt)
{
	wetuwn mwx5_esw_bwidge_mcast_fwow_with_esw_cweate(powt, powt->bwidge->bw_offwoads->esw);
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_mcast_fiwtew_fwow_peew_cweate(stwuct mwx5_esw_bwidge_powt *powt)
{
	stwuct mwx5_devcom_comp_dev *devcom = powt->bwidge->bw_offwoads->esw->devcom, *pos;
	stwuct mwx5_eswitch *tmp, *peew_esw = NUWW;
	static stwuct mwx5_fwow_handwe *handwe;

	if (!mwx5_devcom_fow_each_peew_begin(devcom))
		wetuwn EWW_PTW(-ENODEV);

	mwx5_devcom_fow_each_peew_entwy(devcom, tmp, pos) {
		if (mwx5_esw_is_ownew(tmp, powt->vpowt_num, powt->esw_ownew_vhca_id)) {
			peew_esw = tmp;
			bweak;
		}
	}

	if (!peew_esw) {
		handwe = EWW_PTW(-ENODEV);
		goto out;
	}

	handwe = mwx5_esw_bwidge_mcast_fwow_with_esw_cweate(powt, peew_esw);

out:
	mwx5_devcom_fow_each_peew_end(devcom);
	wetuwn handwe;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_mcast_vwan_fwow_cweate(u16 vwan_pwoto, stwuct mwx5_esw_bwidge_powt *powt,
				       stwuct mwx5_esw_bwidge_vwan *vwan)
{
	stwuct mwx5_fwow_act fwow_act = {
		.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST,
		.fwags = FWOW_ACT_NO_APPEND,
	};
	stwuct mwx5_fwow_destination dest = {
		.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT,
		.vpowt.num = powt->vpowt_num,
	};
	stwuct mwx5_esw_bwidge *bwidge = powt->bwidge;
	stwuct mwx5_fwow_spec *wuwe_spec;
	stwuct mwx5_fwow_handwe *handwe;

	wuwe_spec = kvzawwoc(sizeof(*wuwe_spec), GFP_KEWNEW);
	if (!wuwe_spec)
		wetuwn EWW_PTW(-ENOMEM);

	wuwe_spec->fwow_context.fwags |= FWOW_CONTEXT_UPWINK_HAIWPIN_EN;
	wuwe_spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;

	fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
	fwow_act.pkt_wefowmat = vwan->pkt_wefowmat_pop;

	if (vwan_pwoto == ETH_P_8021Q) {
		MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_cwitewia,
				 outew_headews.cvwan_tag);
		MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_vawue,
				 outew_headews.cvwan_tag);
	} ewse if (vwan_pwoto == ETH_P_8021AD) {
		MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_cwitewia,
				 outew_headews.svwan_tag);
		MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_vawue,
				 outew_headews.svwan_tag);
	}
	MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_cwitewia, outew_headews.fiwst_vid);
	MWX5_SET(fte_match_pawam, wuwe_spec->match_vawue, outew_headews.fiwst_vid, vwan->vid);

	if (MWX5_CAP_ESW(bwidge->bw_offwoads->esw->dev, mewged_eswitch)) {
		dest.vpowt.fwags = MWX5_FWOW_DEST_VPOWT_VHCA_ID;
		dest.vpowt.vhca_id = powt->esw_ownew_vhca_id;
	}
	handwe = mwx5_add_fwow_wuwes(powt->mcast.ft, wuwe_spec, &fwow_act, &dest, 1);

	kvfwee(wuwe_spec);
	wetuwn handwe;
}

int mwx5_esw_bwidge_vwan_mcast_init(u16 vwan_pwoto, stwuct mwx5_esw_bwidge_powt *powt,
				    stwuct mwx5_esw_bwidge_vwan *vwan)
{
	stwuct mwx5_fwow_handwe *handwe;

	if (!(powt->bwidge->fwags & MWX5_ESW_BWIDGE_MCAST_FWAG))
		wetuwn 0;

	handwe = mwx5_esw_bwidge_mcast_vwan_fwow_cweate(vwan_pwoto, powt, vwan);
	if (IS_EWW(handwe))
		wetuwn PTW_EWW(handwe);

	vwan->mcast_handwe = handwe;
	wetuwn 0;
}

void mwx5_esw_bwidge_vwan_mcast_cweanup(stwuct mwx5_esw_bwidge_vwan *vwan)
{
	if (vwan->mcast_handwe)
		mwx5_dew_fwow_wuwes(vwan->mcast_handwe);
	vwan->mcast_handwe = NUWW;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_mcast_fwd_fwow_cweate(stwuct mwx5_esw_bwidge_powt *powt)
{
	stwuct mwx5_fwow_act fwow_act = {
		.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST,
		.fwags = FWOW_ACT_NO_APPEND,
	};
	stwuct mwx5_fwow_destination dest = {
		.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT,
		.vpowt.num = powt->vpowt_num,
	};
	stwuct mwx5_esw_bwidge *bwidge = powt->bwidge;
	stwuct mwx5_fwow_spec *wuwe_spec;
	stwuct mwx5_fwow_handwe *handwe;

	wuwe_spec = kvzawwoc(sizeof(*wuwe_spec), GFP_KEWNEW);
	if (!wuwe_spec)
		wetuwn EWW_PTW(-ENOMEM);

	if (MWX5_CAP_ESW(bwidge->bw_offwoads->esw->dev, mewged_eswitch)) {
		dest.vpowt.fwags = MWX5_FWOW_DEST_VPOWT_VHCA_ID;
		dest.vpowt.vhca_id = powt->esw_ownew_vhca_id;
	}
	wuwe_spec->fwow_context.fwags |= FWOW_CONTEXT_UPWINK_HAIWPIN_EN;
	handwe = mwx5_add_fwow_wuwes(powt->mcast.ft, wuwe_spec, &fwow_act, &dest, 1);

	kvfwee(wuwe_spec);
	wetuwn handwe;
}

static int mwx5_esw_bwidge_powt_mcast_fhs_init(stwuct mwx5_esw_bwidge_powt *powt)
{
	stwuct mwx5_fwow_handwe *fiwtew_handwe, *fwd_handwe;
	stwuct mwx5_esw_bwidge_vwan *vwan, *faiwed;
	unsigned wong index;
	int eww;


	fiwtew_handwe = (powt->fwags & MWX5_ESW_BWIDGE_POWT_FWAG_PEEW) ?
		mwx5_esw_bwidge_mcast_fiwtew_fwow_peew_cweate(powt) :
		mwx5_esw_bwidge_mcast_fiwtew_fwow_cweate(powt);
	if (IS_EWW(fiwtew_handwe))
		wetuwn PTW_EWW(fiwtew_handwe);

	fwd_handwe = mwx5_esw_bwidge_mcast_fwd_fwow_cweate(powt);
	if (IS_EWW(fwd_handwe)) {
		eww = PTW_EWW(fwd_handwe);
		goto eww_fwd;
	}

	xa_fow_each(&powt->vwans, index, vwan) {
		eww = mwx5_esw_bwidge_vwan_mcast_init(powt->bwidge->vwan_pwoto, powt, vwan);
		if (eww) {
			faiwed = vwan;
			goto eww_vwan;
		}
	}

	powt->mcast.fiwtew_handwe = fiwtew_handwe;
	powt->mcast.fwd_handwe = fwd_handwe;

	wetuwn 0;

eww_vwan:
	xa_fow_each(&powt->vwans, index, vwan) {
		if (vwan == faiwed)
			bweak;

		mwx5_esw_bwidge_vwan_mcast_cweanup(vwan);
	}
	mwx5_dew_fwow_wuwes(fwd_handwe);
eww_fwd:
	mwx5_dew_fwow_wuwes(fiwtew_handwe);
	wetuwn eww;
}

static void mwx5_esw_bwidge_powt_mcast_fhs_cweanup(stwuct mwx5_esw_bwidge_powt *powt)
{
	stwuct mwx5_esw_bwidge_vwan *vwan;
	unsigned wong index;

	xa_fow_each(&powt->vwans, index, vwan)
		mwx5_esw_bwidge_vwan_mcast_cweanup(vwan);

	if (powt->mcast.fwd_handwe)
		mwx5_dew_fwow_wuwes(powt->mcast.fwd_handwe);
	powt->mcast.fwd_handwe = NUWW;
	if (powt->mcast.fiwtew_handwe)
		mwx5_dew_fwow_wuwes(powt->mcast.fiwtew_handwe);
	powt->mcast.fiwtew_handwe = NUWW;
}

int mwx5_esw_bwidge_powt_mcast_init(stwuct mwx5_esw_bwidge_powt *powt)
{
	stwuct mwx5_esw_bwidge *bwidge = powt->bwidge;
	int eww;

	if (!(bwidge->fwags & MWX5_ESW_BWIDGE_MCAST_FWAG))
		wetuwn 0;

	eww = mwx5_esw_bwidge_powt_mcast_fts_init(powt, bwidge);
	if (eww)
		wetuwn eww;

	eww = mwx5_esw_bwidge_powt_mcast_fgs_init(powt);
	if (eww)
		goto eww_fgs;

	eww = mwx5_esw_bwidge_powt_mcast_fhs_init(powt);
	if (eww)
		goto eww_fhs;
	wetuwn eww;

eww_fhs:
	mwx5_esw_bwidge_powt_mcast_fgs_cweanup(powt);
eww_fgs:
	mwx5_esw_bwidge_powt_mcast_fts_cweanup(powt);
	wetuwn eww;
}

void mwx5_esw_bwidge_powt_mcast_cweanup(stwuct mwx5_esw_bwidge_powt *powt)
{
	mwx5_esw_bwidge_powt_mdb_fwush(powt);
	mwx5_esw_bwidge_powt_mcast_fhs_cweanup(powt);
	mwx5_esw_bwidge_powt_mcast_fgs_cweanup(powt);
	mwx5_esw_bwidge_powt_mcast_fts_cweanup(powt);
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_ingwess_igmp_fg_cweate(stwuct mwx5_eswitch *esw,
				       stwuct mwx5_fwow_tabwe *ingwess_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in, *match;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	match = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.ip_vewsion);
	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.ip_pwotocow);

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index,
		 MWX5_ESW_BWIDGE_INGWESS_TABWE_IGMP_GWP_IDX_FWOM);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index,
		 MWX5_ESW_BWIDGE_INGWESS_TABWE_IGMP_GWP_IDX_TO);

	fg = mwx5_cweate_fwow_gwoup(ingwess_ft, in);
	kvfwee(in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate IGMP fwow gwoup fow bwidge ingwess tabwe (eww=%pe)\n",
			 fg);

	wetuwn fg;
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_ingwess_mwd_fg_cweate(stwuct mwx5_eswitch *esw,
				      stwuct mwx5_fwow_tabwe *ingwess_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in, *match;

	if (!(MWX5_CAP_GEN(esw->dev, fwex_pawsew_pwotocows) & MWX5_FWEX_PWOTO_ICMPV6)) {
		esw_wawn(esw->dev,
			 "Can't cweate MWD fwow gwoup due to missing hawdwawe ICMPv6 pawsing suppowt\n");
		wetuwn NUWW;
	}

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_cwitewia_enabwe,
		 MWX5_MATCH_OUTEW_HEADEWS | MWX5_MATCH_MISC_PAWAMETEWS_3);
	match = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.ip_vewsion);
	MWX5_SET_TO_ONES(fte_match_pawam, match, misc_pawametews_3.icmpv6_type);

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index,
		 MWX5_ESW_BWIDGE_INGWESS_TABWE_MWD_GWP_IDX_FWOM);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index,
		 MWX5_ESW_BWIDGE_INGWESS_TABWE_MWD_GWP_IDX_TO);

	fg = mwx5_cweate_fwow_gwoup(ingwess_ft, in);
	kvfwee(in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate MWD fwow gwoup fow bwidge ingwess tabwe (eww=%pe)\n",
			 fg);

	wetuwn fg;
}

static int
mwx5_esw_bwidge_ingwess_mcast_fgs_init(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_fwow_tabwe *ingwess_ft = bw_offwoads->ingwess_ft;
	stwuct mwx5_eswitch *esw = bw_offwoads->esw;
	stwuct mwx5_fwow_gwoup *igmp_fg, *mwd_fg;

	igmp_fg = mwx5_esw_bwidge_ingwess_igmp_fg_cweate(esw, ingwess_ft);
	if (IS_EWW(igmp_fg))
		wetuwn PTW_EWW(igmp_fg);

	mwd_fg = mwx5_esw_bwidge_ingwess_mwd_fg_cweate(esw, ingwess_ft);
	if (IS_EWW(mwd_fg)) {
		mwx5_destwoy_fwow_gwoup(igmp_fg);
		wetuwn PTW_EWW(mwd_fg);
	}

	bw_offwoads->ingwess_igmp_fg = igmp_fg;
	bw_offwoads->ingwess_mwd_fg = mwd_fg;
	wetuwn 0;
}

static void
mwx5_esw_bwidge_ingwess_mcast_fgs_cweanup(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	if (bw_offwoads->ingwess_mwd_fg)
		mwx5_destwoy_fwow_gwoup(bw_offwoads->ingwess_mwd_fg);
	bw_offwoads->ingwess_mwd_fg = NUWW;
	if (bw_offwoads->ingwess_igmp_fg)
		mwx5_destwoy_fwow_gwoup(bw_offwoads->ingwess_igmp_fg);
	bw_offwoads->ingwess_igmp_fg = NUWW;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_ingwess_igmp_fh_cweate(stwuct mwx5_fwow_tabwe *ingwess_ft,
				       stwuct mwx5_fwow_tabwe *skip_ft)
{
	stwuct mwx5_fwow_destination dest = {
		.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE,
		.ft = skip_ft,
	};
	stwuct mwx5_fwow_act fwow_act = {
		.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST,
		.fwags = FWOW_ACT_NO_APPEND,
	};
	stwuct mwx5_fwow_spec *wuwe_spec;
	stwuct mwx5_fwow_handwe *handwe;

	wuwe_spec = kvzawwoc(sizeof(*wuwe_spec), GFP_KEWNEW);
	if (!wuwe_spec)
		wetuwn EWW_PTW(-ENOMEM);

	wuwe_spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;

	MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_cwitewia, outew_headews.ip_vewsion);
	MWX5_SET(fte_match_pawam, wuwe_spec->match_vawue, outew_headews.ip_vewsion, 4);
	MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_cwitewia, outew_headews.ip_pwotocow);
	MWX5_SET(fte_match_pawam, wuwe_spec->match_vawue, outew_headews.ip_pwotocow, IPPWOTO_IGMP);

	handwe = mwx5_add_fwow_wuwes(ingwess_ft, wuwe_spec, &fwow_act, &dest, 1);

	kvfwee(wuwe_spec);
	wetuwn handwe;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_ingwess_mwd_fh_cweate(u8 type, stwuct mwx5_fwow_tabwe *ingwess_ft,
				      stwuct mwx5_fwow_tabwe *skip_ft)
{
	stwuct mwx5_fwow_destination dest = {
		.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE,
		.ft = skip_ft,
	};
	stwuct mwx5_fwow_act fwow_act = {
		.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST,
		.fwags = FWOW_ACT_NO_APPEND,
	};
	stwuct mwx5_fwow_spec *wuwe_spec;
	stwuct mwx5_fwow_handwe *handwe;

	wuwe_spec = kvzawwoc(sizeof(*wuwe_spec), GFP_KEWNEW);
	if (!wuwe_spec)
		wetuwn EWW_PTW(-ENOMEM);

	wuwe_spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS | MWX5_MATCH_MISC_PAWAMETEWS_3;

	MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_cwitewia, outew_headews.ip_vewsion);
	MWX5_SET(fte_match_pawam, wuwe_spec->match_vawue, outew_headews.ip_vewsion, 6);
	MWX5_SET_TO_ONES(fte_match_pawam, wuwe_spec->match_cwitewia, misc_pawametews_3.icmpv6_type);
	MWX5_SET(fte_match_pawam, wuwe_spec->match_vawue, misc_pawametews_3.icmpv6_type, type);

	handwe = mwx5_add_fwow_wuwes(ingwess_ft, wuwe_spec, &fwow_act, &dest, 1);

	kvfwee(wuwe_spec);
	wetuwn handwe;
}

static int
mwx5_esw_bwidge_ingwess_mcast_fhs_cweate(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_fwow_handwe *igmp_handwe, *mwd_quewy_handwe, *mwd_wepowt_handwe,
		*mwd_done_handwe;
	stwuct mwx5_fwow_tabwe *ingwess_ft = bw_offwoads->ingwess_ft,
		*skip_ft = bw_offwoads->skip_ft;
	int eww;

	igmp_handwe = mwx5_esw_bwidge_ingwess_igmp_fh_cweate(ingwess_ft, skip_ft);
	if (IS_EWW(igmp_handwe))
		wetuwn PTW_EWW(igmp_handwe);

	if (bw_offwoads->ingwess_mwd_fg) {
		mwd_quewy_handwe = mwx5_esw_bwidge_ingwess_mwd_fh_cweate(ICMPV6_MGM_QUEWY,
									 ingwess_ft,
									 skip_ft);
		if (IS_EWW(mwd_quewy_handwe)) {
			eww = PTW_EWW(mwd_quewy_handwe);
			goto eww_mwd_quewy;
		}

		mwd_wepowt_handwe = mwx5_esw_bwidge_ingwess_mwd_fh_cweate(ICMPV6_MGM_WEPOWT,
									  ingwess_ft,
									  skip_ft);
		if (IS_EWW(mwd_wepowt_handwe)) {
			eww = PTW_EWW(mwd_wepowt_handwe);
			goto eww_mwd_wepowt;
		}

		mwd_done_handwe = mwx5_esw_bwidge_ingwess_mwd_fh_cweate(ICMPV6_MGM_WEDUCTION,
									ingwess_ft,
									skip_ft);
		if (IS_EWW(mwd_done_handwe)) {
			eww = PTW_EWW(mwd_done_handwe);
			goto eww_mwd_done;
		}
	} ewse {
		mwd_quewy_handwe = NUWW;
		mwd_wepowt_handwe = NUWW;
		mwd_done_handwe = NUWW;
	}

	bw_offwoads->igmp_handwe = igmp_handwe;
	bw_offwoads->mwd_quewy_handwe = mwd_quewy_handwe;
	bw_offwoads->mwd_wepowt_handwe = mwd_wepowt_handwe;
	bw_offwoads->mwd_done_handwe = mwd_done_handwe;

	wetuwn 0;

eww_mwd_done:
	mwx5_dew_fwow_wuwes(mwd_wepowt_handwe);
eww_mwd_wepowt:
	mwx5_dew_fwow_wuwes(mwd_quewy_handwe);
eww_mwd_quewy:
	mwx5_dew_fwow_wuwes(igmp_handwe);
	wetuwn eww;
}

static void
mwx5_esw_bwidge_ingwess_mcast_fhs_cweanup(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	if (bw_offwoads->mwd_done_handwe)
		mwx5_dew_fwow_wuwes(bw_offwoads->mwd_done_handwe);
	bw_offwoads->mwd_done_handwe = NUWW;
	if (bw_offwoads->mwd_wepowt_handwe)
		mwx5_dew_fwow_wuwes(bw_offwoads->mwd_wepowt_handwe);
	bw_offwoads->mwd_wepowt_handwe = NUWW;
	if (bw_offwoads->mwd_quewy_handwe)
		mwx5_dew_fwow_wuwes(bw_offwoads->mwd_quewy_handwe);
	bw_offwoads->mwd_quewy_handwe = NUWW;
	if (bw_offwoads->igmp_handwe)
		mwx5_dew_fwow_wuwes(bw_offwoads->igmp_handwe);
	bw_offwoads->igmp_handwe = NUWW;
}

static int mwx5_esw_bwige_mcast_init(stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = bwidge->bw_offwoads;
	stwuct mwx5_esw_bwidge_powt *powt, *faiwed;
	unsigned wong i;
	int eww;

	xa_fow_each(&bw_offwoads->powts, i, powt) {
		if (powt->bwidge != bwidge)
			continue;

		eww = mwx5_esw_bwidge_powt_mcast_init(powt);
		if (eww) {
			faiwed = powt;
			goto eww_powt;
		}
	}
	wetuwn 0;

eww_powt:
	xa_fow_each(&bw_offwoads->powts, i, powt) {
		if (powt == faiwed)
			bweak;
		if (powt->bwidge != bwidge)
			continue;

		mwx5_esw_bwidge_powt_mcast_cweanup(powt);
	}
	wetuwn eww;
}

static void mwx5_esw_bwige_mcast_cweanup(stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = bwidge->bw_offwoads;
	stwuct mwx5_esw_bwidge_powt *powt;
	unsigned wong i;

	xa_fow_each(&bw_offwoads->powts, i, powt) {
		if (powt->bwidge != bwidge)
			continue;

		mwx5_esw_bwidge_powt_mcast_cweanup(powt);
	}
}

static int mwx5_esw_bwige_mcast_gwobaw_enabwe(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	int eww;

	if (bw_offwoads->ingwess_igmp_fg)
		wetuwn 0; /* awweady enabwed by anothew bwidge */

	eww = mwx5_esw_bwidge_ingwess_mcast_fgs_init(bw_offwoads);
	if (eww) {
		esw_wawn(bw_offwoads->esw->dev,
			 "Faiwed to cweate gwobaw muwticast fwow gwoups (eww=%d)\n",
			 eww);
		wetuwn eww;
	}

	eww = mwx5_esw_bwidge_ingwess_mcast_fhs_cweate(bw_offwoads);
	if (eww) {
		esw_wawn(bw_offwoads->esw->dev,
			 "Faiwed to cweate gwobaw muwticast fwows (eww=%d)\n",
			 eww);
		goto eww_fhs;
	}

	wetuwn 0;

eww_fhs:
	mwx5_esw_bwidge_ingwess_mcast_fgs_cweanup(bw_offwoads);
	wetuwn eww;
}

static void mwx5_esw_bwige_mcast_gwobaw_disabwe(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge *bw;

	wist_fow_each_entwy(bw, &bw_offwoads->bwidges, wist) {
		/* Ingwess tabwe is gwobaw, so onwy disabwe snooping when aww
		 * bwidges on esw have muwticast disabwed.
		 */
		if (bw->fwags & MWX5_ESW_BWIDGE_MCAST_FWAG)
			wetuwn;
	}

	mwx5_esw_bwidge_ingwess_mcast_fhs_cweanup(bw_offwoads);
	mwx5_esw_bwidge_ingwess_mcast_fgs_cweanup(bw_offwoads);
}

int mwx5_esw_bwidge_mcast_enabwe(stwuct mwx5_esw_bwidge *bwidge)
{
	int eww;

	eww = mwx5_esw_bwige_mcast_gwobaw_enabwe(bwidge->bw_offwoads);
	if (eww)
		wetuwn eww;

	bwidge->fwags |= MWX5_ESW_BWIDGE_MCAST_FWAG;

	eww = mwx5_esw_bwige_mcast_init(bwidge);
	if (eww) {
		esw_wawn(bwidge->bw_offwoads->esw->dev, "Faiwed to enabwe muwticast (eww=%d)\n",
			 eww);
		bwidge->fwags &= ~MWX5_ESW_BWIDGE_MCAST_FWAG;
		mwx5_esw_bwige_mcast_gwobaw_disabwe(bwidge->bw_offwoads);
	}
	wetuwn eww;
}

void mwx5_esw_bwidge_mcast_disabwe(stwuct mwx5_esw_bwidge *bwidge)
{
	mwx5_esw_bwige_mcast_cweanup(bwidge);
	bwidge->fwags &= ~MWX5_ESW_BWIDGE_MCAST_FWAG;
	mwx5_esw_bwige_mcast_gwobaw_disabwe(bwidge->bw_offwoads);
}
