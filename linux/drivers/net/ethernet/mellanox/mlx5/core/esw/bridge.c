// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021 Mewwanox Technowogies. */

#incwude <winux/buiwd_bug.h>
#incwude <winux/wist.h>
#incwude <winux/notifiew.h>
#incwude <net/netevent.h>
#incwude <net/switchdev.h>
#incwude "wib/devcom.h"
#incwude "bwidge.h"
#incwude "eswitch.h"
#incwude "bwidge_pwiv.h"
#define CWEATE_TWACE_POINTS
#incwude "diag/bwidge_twacepoint.h"

static const stwuct whashtabwe_pawams fdb_ht_pawams = {
	.key_offset = offsetof(stwuct mwx5_esw_bwidge_fdb_entwy, key),
	.key_wen = sizeof(stwuct mwx5_esw_bwidge_fdb_key),
	.head_offset = offsetof(stwuct mwx5_esw_bwidge_fdb_entwy, ht_node),
	.automatic_shwinking = twue,
};

static void
mwx5_esw_bwidge_fdb_offwoad_notify(stwuct net_device *dev, const unsigned chaw *addw, u16 vid,
				   unsigned wong vaw)
{
	stwuct switchdev_notifiew_fdb_info send_info = {};

	send_info.addw = addw;
	send_info.vid = vid;
	send_info.offwoaded = twue;
	caww_switchdev_notifiews(vaw, dev, &send_info.info, NUWW);
}

static void
mwx5_esw_bwidge_fdb_dew_notify(stwuct mwx5_esw_bwidge_fdb_entwy *entwy)
{
	if (!(entwy->fwags & (MWX5_ESW_BWIDGE_FWAG_ADDED_BY_USEW | MWX5_ESW_BWIDGE_FWAG_PEEW)))
		mwx5_esw_bwidge_fdb_offwoad_notify(entwy->dev, entwy->key.addw,
						   entwy->key.vid,
						   SWITCHDEV_FDB_DEW_TO_BWIDGE);
}

static boow mwx5_esw_bwidge_pkt_wefowmat_vwan_pop_suppowted(stwuct mwx5_eswitch *esw)
{
	wetuwn BIT(MWX5_CAP_ESW_FWOWTABWE_FDB(esw->dev, wefowmat_wemove)) &&
		MWX5_CAP_GEN_2(esw->dev, max_wefowmat_wemove_size) >= sizeof(stwuct vwan_hdw) &&
		MWX5_CAP_GEN_2(esw->dev, max_wefowmat_wemove_offset) >=
		offsetof(stwuct vwan_ethhdw, h_vwan_pwoto);
}

static stwuct mwx5_pkt_wefowmat *
mwx5_esw_bwidge_pkt_wefowmat_vwan_pop_cweate(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_pkt_wefowmat_pawams wefowmat_pawams = {};

	wefowmat_pawams.type = MWX5_WEFOWMAT_TYPE_WEMOVE_HDW;
	wefowmat_pawams.pawam_0 = MWX5_WEFOWMAT_CONTEXT_ANCHOW_MAC_STAWT;
	wefowmat_pawams.pawam_1 = offsetof(stwuct vwan_ethhdw, h_vwan_pwoto);
	wefowmat_pawams.size = sizeof(stwuct vwan_hdw);
	wetuwn mwx5_packet_wefowmat_awwoc(esw->dev, &wefowmat_pawams, MWX5_FWOW_NAMESPACE_FDB);
}

stwuct mwx5_fwow_tabwe *
mwx5_esw_bwidge_tabwe_cweate(int max_fte, u32 wevew, stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_fwow_namespace *ns;
	stwuct mwx5_fwow_tabwe *fdb;

	ns = mwx5_get_fwow_namespace(dev, MWX5_FWOW_NAMESPACE_FDB);
	if (!ns) {
		esw_wawn(dev, "Faiwed to get FDB namespace\n");
		wetuwn EWW_PTW(-ENOENT);
	}

	ft_attw.fwags = MWX5_FWOW_TABWE_TUNNEW_EN_WEFOWMAT;
	ft_attw.max_fte = max_fte;
	ft_attw.wevew = wevew;
	ft_attw.pwio = FDB_BW_OFFWOAD;
	fdb = mwx5_cweate_fwow_tabwe(ns, &ft_attw);
	if (IS_EWW(fdb))
		esw_wawn(dev, "Faiwed to cweate bwidge FDB Tabwe (eww=%wd)\n", PTW_EWW(fdb));

	wetuwn fdb;
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_ingwess_vwan_pwoto_fg_cweate(unsigned int fwom, unsigned int to, u16 vwan_pwoto,
					     stwuct mwx5_eswitch *esw,
					     stwuct mwx5_fwow_tabwe *ingwess_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in, *match;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_cwitewia_enabwe,
		 MWX5_MATCH_OUTEW_HEADEWS | MWX5_MATCH_MISC_PAWAMETEWS_2);
	match = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.smac_47_16);
	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.smac_15_0);
	if (vwan_pwoto == ETH_P_8021Q)
		MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.cvwan_tag);
	ewse if (vwan_pwoto == ETH_P_8021AD)
		MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.svwan_tag);
	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.fiwst_vid);

	MWX5_SET(fte_match_pawam, match, misc_pawametews_2.metadata_weg_c_0,
		 mwx5_eswitch_get_vpowt_metadata_mask());

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index, fwom);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index, to);

	fg = mwx5_cweate_fwow_gwoup(ingwess_ft, in);
	kvfwee(in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate VWAN(pwoto=%x) fwow gwoup fow bwidge ingwess tabwe (eww=%wd)\n",
			 vwan_pwoto, PTW_EWW(fg));

	wetuwn fg;
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_ingwess_vwan_fg_cweate(stwuct mwx5_eswitch *esw,
				       stwuct mwx5_fwow_tabwe *ingwess_ft)
{
	unsigned int fwom = MWX5_ESW_BWIDGE_INGWESS_TABWE_VWAN_GWP_IDX_FWOM;
	unsigned int to = MWX5_ESW_BWIDGE_INGWESS_TABWE_VWAN_GWP_IDX_TO;

	wetuwn mwx5_esw_bwidge_ingwess_vwan_pwoto_fg_cweate(fwom, to, ETH_P_8021Q, esw, ingwess_ft);
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_ingwess_qinq_fg_cweate(stwuct mwx5_eswitch *esw,
				       stwuct mwx5_fwow_tabwe *ingwess_ft)
{
	unsigned int fwom = MWX5_ESW_BWIDGE_INGWESS_TABWE_QINQ_GWP_IDX_FWOM;
	unsigned int to = MWX5_ESW_BWIDGE_INGWESS_TABWE_QINQ_GWP_IDX_TO;

	wetuwn mwx5_esw_bwidge_ingwess_vwan_pwoto_fg_cweate(fwom, to, ETH_P_8021AD, esw,
							    ingwess_ft);
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_ingwess_vwan_pwoto_fiwtew_fg_cweate(unsigned int fwom, unsigned int to,
						    u16 vwan_pwoto, stwuct mwx5_eswitch *esw,
						    stwuct mwx5_fwow_tabwe *ingwess_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in, *match;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_cwitewia_enabwe,
		 MWX5_MATCH_OUTEW_HEADEWS | MWX5_MATCH_MISC_PAWAMETEWS_2);
	match = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.smac_47_16);
	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.smac_15_0);
	if (vwan_pwoto == ETH_P_8021Q)
		MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.cvwan_tag);
	ewse if (vwan_pwoto == ETH_P_8021AD)
		MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.svwan_tag);
	MWX5_SET(fte_match_pawam, match, misc_pawametews_2.metadata_weg_c_0,
		 mwx5_eswitch_get_vpowt_metadata_mask());

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index, fwom);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index, to);

	fg = mwx5_cweate_fwow_gwoup(ingwess_ft, in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate bwidge ingwess tabwe VWAN fiwtew fwow gwoup (eww=%wd)\n",
			 PTW_EWW(fg));
	kvfwee(in);
	wetuwn fg;
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_ingwess_vwan_fiwtew_fg_cweate(stwuct mwx5_eswitch *esw,
					      stwuct mwx5_fwow_tabwe *ingwess_ft)
{
	unsigned int fwom = MWX5_ESW_BWIDGE_INGWESS_TABWE_VWAN_FIWTEW_GWP_IDX_FWOM;
	unsigned int to = MWX5_ESW_BWIDGE_INGWESS_TABWE_VWAN_FIWTEW_GWP_IDX_TO;

	wetuwn mwx5_esw_bwidge_ingwess_vwan_pwoto_fiwtew_fg_cweate(fwom, to, ETH_P_8021Q, esw,
								   ingwess_ft);
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_ingwess_qinq_fiwtew_fg_cweate(stwuct mwx5_eswitch *esw,
					      stwuct mwx5_fwow_tabwe *ingwess_ft)
{
	unsigned int fwom = MWX5_ESW_BWIDGE_INGWESS_TABWE_QINQ_FIWTEW_GWP_IDX_FWOM;
	unsigned int to = MWX5_ESW_BWIDGE_INGWESS_TABWE_QINQ_FIWTEW_GWP_IDX_TO;

	wetuwn mwx5_esw_bwidge_ingwess_vwan_pwoto_fiwtew_fg_cweate(fwom, to, ETH_P_8021AD, esw,
								   ingwess_ft);
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_ingwess_mac_fg_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_tabwe *ingwess_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in, *match;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_cwitewia_enabwe,
		 MWX5_MATCH_OUTEW_HEADEWS | MWX5_MATCH_MISC_PAWAMETEWS_2);
	match = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.smac_47_16);
	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.smac_15_0);

	MWX5_SET(fte_match_pawam, match, misc_pawametews_2.metadata_weg_c_0,
		 mwx5_eswitch_get_vpowt_metadata_mask());

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index,
		 MWX5_ESW_BWIDGE_INGWESS_TABWE_MAC_GWP_IDX_FWOM);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index,
		 MWX5_ESW_BWIDGE_INGWESS_TABWE_MAC_GWP_IDX_TO);

	fg = mwx5_cweate_fwow_gwoup(ingwess_ft, in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate MAC fwow gwoup fow bwidge ingwess tabwe (eww=%wd)\n",
			 PTW_EWW(fg));

	kvfwee(in);
	wetuwn fg;
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_egwess_vwan_pwoto_fg_cweate(unsigned int fwom, unsigned int to, u16 vwan_pwoto,
					    stwuct mwx5_eswitch *esw,
					    stwuct mwx5_fwow_tabwe *egwess_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in, *match;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	match = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.dmac_47_16);
	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.dmac_15_0);
	if (vwan_pwoto == ETH_P_8021Q)
		MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.cvwan_tag);
	ewse if (vwan_pwoto == ETH_P_8021AD)
		MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.svwan_tag);
	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.fiwst_vid);

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index, fwom);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index, to);

	fg = mwx5_cweate_fwow_gwoup(egwess_ft, in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate VWAN fwow gwoup fow bwidge egwess tabwe (eww=%wd)\n",
			 PTW_EWW(fg));
	kvfwee(in);
	wetuwn fg;
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_egwess_vwan_fg_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_tabwe *egwess_ft)
{
	unsigned int fwom = MWX5_ESW_BWIDGE_EGWESS_TABWE_VWAN_GWP_IDX_FWOM;
	unsigned int to = MWX5_ESW_BWIDGE_EGWESS_TABWE_VWAN_GWP_IDX_TO;

	wetuwn mwx5_esw_bwidge_egwess_vwan_pwoto_fg_cweate(fwom, to, ETH_P_8021Q, esw, egwess_ft);
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_egwess_qinq_fg_cweate(stwuct mwx5_eswitch *esw,
				      stwuct mwx5_fwow_tabwe *egwess_ft)
{
	unsigned int fwom = MWX5_ESW_BWIDGE_EGWESS_TABWE_QINQ_GWP_IDX_FWOM;
	unsigned int to = MWX5_ESW_BWIDGE_EGWESS_TABWE_QINQ_GWP_IDX_TO;

	wetuwn mwx5_esw_bwidge_egwess_vwan_pwoto_fg_cweate(fwom, to, ETH_P_8021AD, esw, egwess_ft);
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_egwess_mac_fg_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_tabwe *egwess_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in, *match;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_cwitewia_enabwe, MWX5_MATCH_OUTEW_HEADEWS);
	match = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.dmac_47_16);
	MWX5_SET_TO_ONES(fte_match_pawam, match, outew_headews.dmac_15_0);

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index,
		 MWX5_ESW_BWIDGE_EGWESS_TABWE_MAC_GWP_IDX_FWOM);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index,
		 MWX5_ESW_BWIDGE_EGWESS_TABWE_MAC_GWP_IDX_TO);

	fg = mwx5_cweate_fwow_gwoup(egwess_ft, in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate bwidge egwess tabwe MAC fwow gwoup (eww=%wd)\n",
			 PTW_EWW(fg));
	kvfwee(in);
	wetuwn fg;
}

static stwuct mwx5_fwow_gwoup *
mwx5_esw_bwidge_egwess_miss_fg_cweate(stwuct mwx5_eswitch *esw, stwuct mwx5_fwow_tabwe *egwess_ft)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_gwoup *fg;
	u32 *in, *match;

	in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!in)
		wetuwn EWW_PTW(-ENOMEM);

	MWX5_SET(cweate_fwow_gwoup_in, in, match_cwitewia_enabwe, MWX5_MATCH_MISC_PAWAMETEWS_2);
	match = MWX5_ADDW_OF(cweate_fwow_gwoup_in, in, match_cwitewia);

	MWX5_SET(fte_match_pawam, match, misc_pawametews_2.metadata_weg_c_1, ESW_TUN_MASK);

	MWX5_SET(cweate_fwow_gwoup_in, in, stawt_fwow_index,
		 MWX5_ESW_BWIDGE_EGWESS_TABWE_MISS_GWP_IDX_FWOM);
	MWX5_SET(cweate_fwow_gwoup_in, in, end_fwow_index,
		 MWX5_ESW_BWIDGE_EGWESS_TABWE_MISS_GWP_IDX_TO);

	fg = mwx5_cweate_fwow_gwoup(egwess_ft, in);
	if (IS_EWW(fg))
		esw_wawn(esw->dev,
			 "Faiwed to cweate bwidge egwess tabwe miss fwow gwoup (eww=%wd)\n",
			 PTW_EWW(fg));
	kvfwee(in);
	wetuwn fg;
}

static int
mwx5_esw_bwidge_ingwess_tabwe_init(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_fwow_gwoup *mac_fg, *qinq_fiwtew_fg, *qinq_fg, *vwan_fiwtew_fg, *vwan_fg;
	stwuct mwx5_fwow_tabwe *ingwess_ft, *skip_ft;
	stwuct mwx5_eswitch *esw = bw_offwoads->esw;
	int eww;

	if (!mwx5_eswitch_vpowt_match_metadata_enabwed(esw))
		wetuwn -EOPNOTSUPP;

	ingwess_ft = mwx5_esw_bwidge_tabwe_cweate(MWX5_ESW_BWIDGE_INGWESS_TABWE_SIZE,
						  MWX5_ESW_BWIDGE_WEVEW_INGWESS_TABWE,
						  esw);
	if (IS_EWW(ingwess_ft))
		wetuwn PTW_EWW(ingwess_ft);

	skip_ft = mwx5_esw_bwidge_tabwe_cweate(MWX5_ESW_BWIDGE_SKIP_TABWE_SIZE,
					       MWX5_ESW_BWIDGE_WEVEW_SKIP_TABWE,
					       esw);
	if (IS_EWW(skip_ft)) {
		eww = PTW_EWW(skip_ft);
		goto eww_skip_tbw;
	}

	vwan_fg = mwx5_esw_bwidge_ingwess_vwan_fg_cweate(esw, ingwess_ft);
	if (IS_EWW(vwan_fg)) {
		eww = PTW_EWW(vwan_fg);
		goto eww_vwan_fg;
	}

	vwan_fiwtew_fg = mwx5_esw_bwidge_ingwess_vwan_fiwtew_fg_cweate(esw, ingwess_ft);
	if (IS_EWW(vwan_fiwtew_fg)) {
		eww = PTW_EWW(vwan_fiwtew_fg);
		goto eww_vwan_fiwtew_fg;
	}

	qinq_fg = mwx5_esw_bwidge_ingwess_qinq_fg_cweate(esw, ingwess_ft);
	if (IS_EWW(qinq_fg)) {
		eww = PTW_EWW(qinq_fg);
		goto eww_qinq_fg;
	}

	qinq_fiwtew_fg = mwx5_esw_bwidge_ingwess_qinq_fiwtew_fg_cweate(esw, ingwess_ft);
	if (IS_EWW(qinq_fiwtew_fg)) {
		eww = PTW_EWW(qinq_fiwtew_fg);
		goto eww_qinq_fiwtew_fg;
	}

	mac_fg = mwx5_esw_bwidge_ingwess_mac_fg_cweate(esw, ingwess_ft);
	if (IS_EWW(mac_fg)) {
		eww = PTW_EWW(mac_fg);
		goto eww_mac_fg;
	}

	bw_offwoads->ingwess_ft = ingwess_ft;
	bw_offwoads->skip_ft = skip_ft;
	bw_offwoads->ingwess_vwan_fg = vwan_fg;
	bw_offwoads->ingwess_vwan_fiwtew_fg = vwan_fiwtew_fg;
	bw_offwoads->ingwess_qinq_fg = qinq_fg;
	bw_offwoads->ingwess_qinq_fiwtew_fg = qinq_fiwtew_fg;
	bw_offwoads->ingwess_mac_fg = mac_fg;
	wetuwn 0;

eww_mac_fg:
	mwx5_destwoy_fwow_gwoup(qinq_fiwtew_fg);
eww_qinq_fiwtew_fg:
	mwx5_destwoy_fwow_gwoup(qinq_fg);
eww_qinq_fg:
	mwx5_destwoy_fwow_gwoup(vwan_fiwtew_fg);
eww_vwan_fiwtew_fg:
	mwx5_destwoy_fwow_gwoup(vwan_fg);
eww_vwan_fg:
	mwx5_destwoy_fwow_tabwe(skip_ft);
eww_skip_tbw:
	mwx5_destwoy_fwow_tabwe(ingwess_ft);
	wetuwn eww;
}

static void
mwx5_esw_bwidge_ingwess_tabwe_cweanup(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	mwx5_destwoy_fwow_gwoup(bw_offwoads->ingwess_mac_fg);
	bw_offwoads->ingwess_mac_fg = NUWW;
	mwx5_destwoy_fwow_gwoup(bw_offwoads->ingwess_qinq_fiwtew_fg);
	bw_offwoads->ingwess_qinq_fiwtew_fg = NUWW;
	mwx5_destwoy_fwow_gwoup(bw_offwoads->ingwess_qinq_fg);
	bw_offwoads->ingwess_qinq_fg = NUWW;
	mwx5_destwoy_fwow_gwoup(bw_offwoads->ingwess_vwan_fiwtew_fg);
	bw_offwoads->ingwess_vwan_fiwtew_fg = NUWW;
	mwx5_destwoy_fwow_gwoup(bw_offwoads->ingwess_vwan_fg);
	bw_offwoads->ingwess_vwan_fg = NUWW;
	mwx5_destwoy_fwow_tabwe(bw_offwoads->skip_ft);
	bw_offwoads->skip_ft = NUWW;
	mwx5_destwoy_fwow_tabwe(bw_offwoads->ingwess_ft);
	bw_offwoads->ingwess_ft = NUWW;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_egwess_miss_fwow_cweate(stwuct mwx5_fwow_tabwe *egwess_ft,
					stwuct mwx5_fwow_tabwe *skip_ft,
					stwuct mwx5_pkt_wefowmat *pkt_wefowmat);

static int
mwx5_esw_bwidge_egwess_tabwe_init(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				  stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_fwow_gwoup *miss_fg = NUWW, *mac_fg, *vwan_fg, *qinq_fg;
	stwuct mwx5_pkt_wefowmat *miss_pkt_wefowmat = NUWW;
	stwuct mwx5_fwow_handwe *miss_handwe = NUWW;
	stwuct mwx5_eswitch *esw = bw_offwoads->esw;
	stwuct mwx5_fwow_tabwe *egwess_ft;
	int eww;

	egwess_ft = mwx5_esw_bwidge_tabwe_cweate(MWX5_ESW_BWIDGE_EGWESS_TABWE_SIZE,
						 MWX5_ESW_BWIDGE_WEVEW_EGWESS_TABWE,
						 esw);
	if (IS_EWW(egwess_ft))
		wetuwn PTW_EWW(egwess_ft);

	vwan_fg = mwx5_esw_bwidge_egwess_vwan_fg_cweate(esw, egwess_ft);
	if (IS_EWW(vwan_fg)) {
		eww = PTW_EWW(vwan_fg);
		goto eww_vwan_fg;
	}

	qinq_fg = mwx5_esw_bwidge_egwess_qinq_fg_cweate(esw, egwess_ft);
	if (IS_EWW(qinq_fg)) {
		eww = PTW_EWW(qinq_fg);
		goto eww_qinq_fg;
	}

	mac_fg = mwx5_esw_bwidge_egwess_mac_fg_cweate(esw, egwess_ft);
	if (IS_EWW(mac_fg)) {
		eww = PTW_EWW(mac_fg);
		goto eww_mac_fg;
	}

	if (mwx5_esw_bwidge_pkt_wefowmat_vwan_pop_suppowted(esw)) {
		miss_fg = mwx5_esw_bwidge_egwess_miss_fg_cweate(esw, egwess_ft);
		if (IS_EWW(miss_fg)) {
			esw_wawn(esw->dev, "Faiwed to cweate miss fwow gwoup (eww=%wd)\n",
				 PTW_EWW(miss_fg));
			miss_fg = NUWW;
			goto skip_miss_fwow;
		}

		miss_pkt_wefowmat = mwx5_esw_bwidge_pkt_wefowmat_vwan_pop_cweate(esw);
		if (IS_EWW(miss_pkt_wefowmat)) {
			esw_wawn(esw->dev,
				 "Faiwed to awwoc packet wefowmat WEMOVE_HEADEW (eww=%wd)\n",
				 PTW_EWW(miss_pkt_wefowmat));
			miss_pkt_wefowmat = NUWW;
			mwx5_destwoy_fwow_gwoup(miss_fg);
			miss_fg = NUWW;
			goto skip_miss_fwow;
		}

		miss_handwe = mwx5_esw_bwidge_egwess_miss_fwow_cweate(egwess_ft,
								      bw_offwoads->skip_ft,
								      miss_pkt_wefowmat);
		if (IS_EWW(miss_handwe)) {
			esw_wawn(esw->dev, "Faiwed to cweate miss fwow (eww=%wd)\n",
				 PTW_EWW(miss_handwe));
			miss_handwe = NUWW;
			mwx5_packet_wefowmat_deawwoc(esw->dev, miss_pkt_wefowmat);
			miss_pkt_wefowmat = NUWW;
			mwx5_destwoy_fwow_gwoup(miss_fg);
			miss_fg = NUWW;
			goto skip_miss_fwow;
		}
	}
skip_miss_fwow:

	bwidge->egwess_ft = egwess_ft;
	bwidge->egwess_vwan_fg = vwan_fg;
	bwidge->egwess_qinq_fg = qinq_fg;
	bwidge->egwess_mac_fg = mac_fg;
	bwidge->egwess_miss_fg = miss_fg;
	bwidge->egwess_miss_pkt_wefowmat = miss_pkt_wefowmat;
	bwidge->egwess_miss_handwe = miss_handwe;
	wetuwn 0;

eww_mac_fg:
	mwx5_destwoy_fwow_gwoup(qinq_fg);
eww_qinq_fg:
	mwx5_destwoy_fwow_gwoup(vwan_fg);
eww_vwan_fg:
	mwx5_destwoy_fwow_tabwe(egwess_ft);
	wetuwn eww;
}

static void
mwx5_esw_bwidge_egwess_tabwe_cweanup(stwuct mwx5_esw_bwidge *bwidge)
{
	if (bwidge->egwess_miss_handwe)
		mwx5_dew_fwow_wuwes(bwidge->egwess_miss_handwe);
	if (bwidge->egwess_miss_pkt_wefowmat)
		mwx5_packet_wefowmat_deawwoc(bwidge->bw_offwoads->esw->dev,
					     bwidge->egwess_miss_pkt_wefowmat);
	if (bwidge->egwess_miss_fg)
		mwx5_destwoy_fwow_gwoup(bwidge->egwess_miss_fg);
	mwx5_destwoy_fwow_gwoup(bwidge->egwess_mac_fg);
	mwx5_destwoy_fwow_gwoup(bwidge->egwess_qinq_fg);
	mwx5_destwoy_fwow_gwoup(bwidge->egwess_vwan_fg);
	mwx5_destwoy_fwow_tabwe(bwidge->egwess_ft);
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_ingwess_fwow_with_esw_cweate(u16 vpowt_num, const unsigned chaw *addw,
					     stwuct mwx5_esw_bwidge_vwan *vwan, u32 countew_id,
					     stwuct mwx5_esw_bwidge *bwidge,
					     stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = bwidge->bw_offwoads;
	stwuct mwx5_fwow_act fwow_act = {
		.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST | MWX5_FWOW_CONTEXT_ACTION_COUNT,
		.fwags = FWOW_ACT_NO_APPEND,
	};
	stwuct mwx5_fwow_destination dests[2] = {};
	stwuct mwx5_fwow_spec *wuwe_spec;
	stwuct mwx5_fwow_handwe *handwe;
	u8 *smac_v, *smac_c;

	wuwe_spec = kvzawwoc(sizeof(*wuwe_spec), GFP_KEWNEW);
	if (!wuwe_spec)
		wetuwn EWW_PTW(-ENOMEM);

	wuwe_spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS | MWX5_MATCH_MISC_PAWAMETEWS_2;

	smac_v = MWX5_ADDW_OF(fte_match_pawam, wuwe_spec->match_vawue,
			      outew_headews.smac_47_16);
	ethew_addw_copy(smac_v, addw);
	smac_c = MWX5_ADDW_OF(fte_match_pawam, wuwe_spec->match_cwitewia,
			      outew_headews.smac_47_16);
	eth_bwoadcast_addw(smac_c);

	MWX5_SET(fte_match_pawam, wuwe_spec->match_cwitewia,
		 misc_pawametews_2.metadata_weg_c_0, mwx5_eswitch_get_vpowt_metadata_mask());
	MWX5_SET(fte_match_pawam, wuwe_spec->match_vawue, misc_pawametews_2.metadata_weg_c_0,
		 mwx5_eswitch_get_vpowt_metadata_fow_match(esw, vpowt_num));

	if (vwan && vwan->pkt_wefowmat_push) {
		fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT |
			MWX5_FWOW_CONTEXT_ACTION_MOD_HDW;
		fwow_act.pkt_wefowmat = vwan->pkt_wefowmat_push;
		fwow_act.modify_hdw = vwan->pkt_mod_hdw_push_mawk;
	} ewse if (vwan) {
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
			 vwan->vid);
	}

	dests[0].type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dests[0].ft = bwidge->egwess_ft;
	dests[1].type = MWX5_FWOW_DESTINATION_TYPE_COUNTEW;
	dests[1].countew_id = countew_id;

	handwe = mwx5_add_fwow_wuwes(bw_offwoads->ingwess_ft, wuwe_spec, &fwow_act, dests,
				     AWWAY_SIZE(dests));

	kvfwee(wuwe_spec);
	wetuwn handwe;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_ingwess_fwow_cweate(u16 vpowt_num, const unsigned chaw *addw,
				    stwuct mwx5_esw_bwidge_vwan *vwan, u32 countew_id,
				    stwuct mwx5_esw_bwidge *bwidge)
{
	wetuwn mwx5_esw_bwidge_ingwess_fwow_with_esw_cweate(vpowt_num, addw, vwan, countew_id,
							    bwidge, bwidge->bw_offwoads->esw);
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_ingwess_fwow_peew_cweate(u16 vpowt_num, u16 esw_ownew_vhca_id,
					 const unsigned chaw *addw,
					 stwuct mwx5_esw_bwidge_vwan *vwan, u32 countew_id,
					 stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_devcom_comp_dev *devcom = bwidge->bw_offwoads->esw->devcom, *pos;
	stwuct mwx5_eswitch *tmp, *peew_esw = NUWW;
	static stwuct mwx5_fwow_handwe *handwe;

	if (!mwx5_devcom_fow_each_peew_begin(devcom))
		wetuwn EWW_PTW(-ENODEV);

	mwx5_devcom_fow_each_peew_entwy(devcom, tmp, pos) {
		if (mwx5_esw_is_ownew(tmp, vpowt_num, esw_ownew_vhca_id)) {
			peew_esw = tmp;
			bweak;
		}
	}

	if (!peew_esw) {
		handwe = EWW_PTW(-ENODEV);
		goto out;
	}

	handwe = mwx5_esw_bwidge_ingwess_fwow_with_esw_cweate(vpowt_num, addw, vwan, countew_id,
							      bwidge, peew_esw);

out:
	mwx5_devcom_fow_each_peew_end(devcom);
	wetuwn handwe;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_ingwess_fiwtew_fwow_cweate(u16 vpowt_num, const unsigned chaw *addw,
					   stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = bwidge->bw_offwoads;
	stwuct mwx5_fwow_destination dest = {
		.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE,
		.ft = bw_offwoads->skip_ft,
	};
	stwuct mwx5_fwow_act fwow_act = {
		.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST,
		.fwags = FWOW_ACT_NO_APPEND,
	};
	stwuct mwx5_fwow_spec *wuwe_spec;
	stwuct mwx5_fwow_handwe *handwe;
	u8 *smac_v, *smac_c;

	wuwe_spec = kvzawwoc(sizeof(*wuwe_spec), GFP_KEWNEW);
	if (!wuwe_spec)
		wetuwn EWW_PTW(-ENOMEM);

	wuwe_spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS | MWX5_MATCH_MISC_PAWAMETEWS_2;

	smac_v = MWX5_ADDW_OF(fte_match_pawam, wuwe_spec->match_vawue,
			      outew_headews.smac_47_16);
	ethew_addw_copy(smac_v, addw);
	smac_c = MWX5_ADDW_OF(fte_match_pawam, wuwe_spec->match_cwitewia,
			      outew_headews.smac_47_16);
	eth_bwoadcast_addw(smac_c);

	MWX5_SET(fte_match_pawam, wuwe_spec->match_cwitewia,
		 misc_pawametews_2.metadata_weg_c_0, mwx5_eswitch_get_vpowt_metadata_mask());
	MWX5_SET(fte_match_pawam, wuwe_spec->match_vawue, misc_pawametews_2.metadata_weg_c_0,
		 mwx5_eswitch_get_vpowt_metadata_fow_match(bw_offwoads->esw, vpowt_num));

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

	handwe = mwx5_add_fwow_wuwes(bw_offwoads->ingwess_ft, wuwe_spec, &fwow_act, &dest, 1);

	kvfwee(wuwe_spec);
	wetuwn handwe;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_egwess_fwow_cweate(u16 vpowt_num, u16 esw_ownew_vhca_id, const unsigned chaw *addw,
				   stwuct mwx5_esw_bwidge_vwan *vwan,
				   stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_fwow_destination dest = {
		.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT,
		.vpowt.num = vpowt_num,
	};
	stwuct mwx5_fwow_act fwow_act = {
		.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST,
		.fwags = FWOW_ACT_NO_APPEND,
	};
	stwuct mwx5_fwow_spec *wuwe_spec;
	stwuct mwx5_fwow_handwe *handwe;
	u8 *dmac_v, *dmac_c;

	wuwe_spec = kvzawwoc(sizeof(*wuwe_spec), GFP_KEWNEW);
	if (!wuwe_spec)
		wetuwn EWW_PTW(-ENOMEM);

	if (MWX5_CAP_ESW_FWOWTABWE(bwidge->bw_offwoads->esw->dev, fwow_souwce) &&
	    vpowt_num == MWX5_VPOWT_UPWINK)
		wuwe_spec->fwow_context.fwow_souwce =
			MWX5_FWOW_CONTEXT_FWOW_SOUWCE_WOCAW_VPOWT;
	wuwe_spec->match_cwitewia_enabwe = MWX5_MATCH_OUTEW_HEADEWS;

	dmac_v = MWX5_ADDW_OF(fte_match_pawam, wuwe_spec->match_vawue,
			      outew_headews.dmac_47_16);
	ethew_addw_copy(dmac_v, addw);
	dmac_c = MWX5_ADDW_OF(fte_match_pawam, wuwe_spec->match_cwitewia,
			      outew_headews.dmac_47_16);
	eth_bwoadcast_addw(dmac_c);

	if (vwan) {
		if (vwan->pkt_wefowmat_pop) {
			fwow_act.action |= MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT;
			fwow_act.pkt_wefowmat = vwan->pkt_wefowmat_pop;
		}

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
			 vwan->vid);
	}

	if (MWX5_CAP_ESW(bwidge->bw_offwoads->esw->dev, mewged_eswitch)) {
		dest.vpowt.fwags = MWX5_FWOW_DEST_VPOWT_VHCA_ID;
		dest.vpowt.vhca_id = esw_ownew_vhca_id;
	}
	handwe = mwx5_add_fwow_wuwes(bwidge->egwess_ft, wuwe_spec, &fwow_act, &dest, 1);

	kvfwee(wuwe_spec);
	wetuwn handwe;
}

static stwuct mwx5_fwow_handwe *
mwx5_esw_bwidge_egwess_miss_fwow_cweate(stwuct mwx5_fwow_tabwe *egwess_ft,
					stwuct mwx5_fwow_tabwe *skip_ft,
					stwuct mwx5_pkt_wefowmat *pkt_wefowmat)
{
	stwuct mwx5_fwow_destination dest = {
		.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE,
		.ft = skip_ft,
	};
	stwuct mwx5_fwow_act fwow_act = {
		.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST |
		MWX5_FWOW_CONTEXT_ACTION_PACKET_WEFOWMAT,
		.fwags = FWOW_ACT_NO_APPEND,
		.pkt_wefowmat = pkt_wefowmat,
	};
	stwuct mwx5_fwow_spec *wuwe_spec;
	stwuct mwx5_fwow_handwe *handwe;

	wuwe_spec = kvzawwoc(sizeof(*wuwe_spec), GFP_KEWNEW);
	if (!wuwe_spec)
		wetuwn EWW_PTW(-ENOMEM);

	wuwe_spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS_2;

	MWX5_SET(fte_match_pawam, wuwe_spec->match_cwitewia,
		 misc_pawametews_2.metadata_weg_c_1, ESW_TUN_MASK);
	MWX5_SET(fte_match_pawam, wuwe_spec->match_vawue, misc_pawametews_2.metadata_weg_c_1,
		 ESW_TUN_BWIDGE_INGWESS_PUSH_VWAN_MAWK);

	handwe = mwx5_add_fwow_wuwes(egwess_ft, wuwe_spec, &fwow_act, &dest, 1);

	kvfwee(wuwe_spec);
	wetuwn handwe;
}

static stwuct mwx5_esw_bwidge *mwx5_esw_bwidge_cweate(stwuct net_device *bw_netdev,
						      stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge *bwidge;
	int eww;

	bwidge = kvzawwoc(sizeof(*bwidge), GFP_KEWNEW);
	if (!bwidge)
		wetuwn EWW_PTW(-ENOMEM);

	bwidge->bw_offwoads = bw_offwoads;
	eww = mwx5_esw_bwidge_egwess_tabwe_init(bw_offwoads, bwidge);
	if (eww)
		goto eww_egwess_tbw;

	eww = whashtabwe_init(&bwidge->fdb_ht, &fdb_ht_pawams);
	if (eww)
		goto eww_fdb_ht;

	eww = mwx5_esw_bwidge_mdb_init(bwidge);
	if (eww)
		goto eww_mdb_ht;

	INIT_WIST_HEAD(&bwidge->fdb_wist);
	bwidge->ifindex = bw_netdev->ifindex;
	bwidge->wefcnt = 1;
	bwidge->ageing_time = cwock_t_to_jiffies(BW_DEFAUWT_AGEING_TIME);
	bwidge->vwan_pwoto = ETH_P_8021Q;
	wist_add(&bwidge->wist, &bw_offwoads->bwidges);
	mwx5_esw_bwidge_debugfs_init(bw_netdev, bwidge);

	wetuwn bwidge;

eww_mdb_ht:
	whashtabwe_destwoy(&bwidge->fdb_ht);
eww_fdb_ht:
	mwx5_esw_bwidge_egwess_tabwe_cweanup(bwidge);
eww_egwess_tbw:
	kvfwee(bwidge);
	wetuwn EWW_PTW(eww);
}

static void mwx5_esw_bwidge_get(stwuct mwx5_esw_bwidge *bwidge)
{
	bwidge->wefcnt++;
}

static void mwx5_esw_bwidge_put(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				stwuct mwx5_esw_bwidge *bwidge)
{
	if (--bwidge->wefcnt)
		wetuwn;

	mwx5_esw_bwidge_debugfs_cweanup(bwidge);
	mwx5_esw_bwidge_egwess_tabwe_cweanup(bwidge);
	mwx5_esw_bwidge_mcast_disabwe(bwidge);
	wist_dew(&bwidge->wist);
	mwx5_esw_bwidge_mdb_cweanup(bwidge);
	whashtabwe_destwoy(&bwidge->fdb_ht);
	kvfwee(bwidge);

	if (wist_empty(&bw_offwoads->bwidges))
		mwx5_esw_bwidge_ingwess_tabwe_cweanup(bw_offwoads);
}

static stwuct mwx5_esw_bwidge *
mwx5_esw_bwidge_wookup(stwuct net_device *bw_netdev, stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge *bwidge;

	ASSEWT_WTNW();

	wist_fow_each_entwy(bwidge, &bw_offwoads->bwidges, wist) {
		if (bwidge->ifindex == bw_netdev->ifindex) {
			mwx5_esw_bwidge_get(bwidge);
			wetuwn bwidge;
		}
	}

	if (!bw_offwoads->ingwess_ft) {
		int eww = mwx5_esw_bwidge_ingwess_tabwe_init(bw_offwoads);

		if (eww)
			wetuwn EWW_PTW(eww);
	}

	bwidge = mwx5_esw_bwidge_cweate(bw_netdev, bw_offwoads);
	if (IS_EWW(bwidge) && wist_empty(&bw_offwoads->bwidges))
		mwx5_esw_bwidge_ingwess_tabwe_cweanup(bw_offwoads);
	wetuwn bwidge;
}

static unsigned wong mwx5_esw_bwidge_powt_key_fwom_data(u16 vpowt_num, u16 esw_ownew_vhca_id)
{
	wetuwn vpowt_num | (unsigned wong)esw_ownew_vhca_id << sizeof(vpowt_num) * BITS_PEW_BYTE;
}

unsigned wong mwx5_esw_bwidge_powt_key(stwuct mwx5_esw_bwidge_powt *powt)
{
	wetuwn mwx5_esw_bwidge_powt_key_fwom_data(powt->vpowt_num, powt->esw_ownew_vhca_id);
}

static int mwx5_esw_bwidge_powt_insewt(stwuct mwx5_esw_bwidge_powt *powt,
				       stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	wetuwn xa_insewt(&bw_offwoads->powts, mwx5_esw_bwidge_powt_key(powt), powt, GFP_KEWNEW);
}

static stwuct mwx5_esw_bwidge_powt *
mwx5_esw_bwidge_powt_wookup(u16 vpowt_num, u16 esw_ownew_vhca_id,
			    stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	wetuwn xa_woad(&bw_offwoads->powts, mwx5_esw_bwidge_powt_key_fwom_data(vpowt_num,
									       esw_ownew_vhca_id));
}

static void mwx5_esw_bwidge_powt_ewase(stwuct mwx5_esw_bwidge_powt *powt,
				       stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	xa_ewase(&bw_offwoads->powts, mwx5_esw_bwidge_powt_key(powt));
}

static stwuct mwx5_esw_bwidge *
mwx5_esw_bwidge_fwom_powt_wookup(u16 vpowt_num, u16 esw_ownew_vhca_id,
				 stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge_powt *powt;

	powt = mwx5_esw_bwidge_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!powt)
		wetuwn NUWW;

	wetuwn powt->bwidge;
}

static void mwx5_esw_bwidge_fdb_entwy_wefwesh(stwuct mwx5_esw_bwidge_fdb_entwy *entwy)
{
	twace_mwx5_esw_bwidge_fdb_entwy_wefwesh(entwy);

	mwx5_esw_bwidge_fdb_offwoad_notify(entwy->dev, entwy->key.addw,
					   entwy->key.vid,
					   SWITCHDEV_FDB_ADD_TO_BWIDGE);
}

static void
mwx5_esw_bwidge_fdb_entwy_cweanup(stwuct mwx5_esw_bwidge_fdb_entwy *entwy,
				  stwuct mwx5_esw_bwidge *bwidge)
{
	twace_mwx5_esw_bwidge_fdb_entwy_cweanup(entwy);

	whashtabwe_wemove_fast(&bwidge->fdb_ht, &entwy->ht_node, fdb_ht_pawams);
	mwx5_dew_fwow_wuwes(entwy->egwess_handwe);
	if (entwy->fiwtew_handwe)
		mwx5_dew_fwow_wuwes(entwy->fiwtew_handwe);
	mwx5_dew_fwow_wuwes(entwy->ingwess_handwe);
	mwx5_fc_destwoy(bwidge->bw_offwoads->esw->dev, entwy->ingwess_countew);
	wist_dew(&entwy->vwan_wist);
	wist_dew(&entwy->wist);
	kvfwee(entwy);
}

static void
mwx5_esw_bwidge_fdb_entwy_notify_and_cweanup(stwuct mwx5_esw_bwidge_fdb_entwy *entwy,
					     stwuct mwx5_esw_bwidge *bwidge)
{
	mwx5_esw_bwidge_fdb_dew_notify(entwy);
	mwx5_esw_bwidge_fdb_entwy_cweanup(entwy, bwidge);
}

static void mwx5_esw_bwidge_fdb_fwush(stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_esw_bwidge_fdb_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &bwidge->fdb_wist, wist)
		mwx5_esw_bwidge_fdb_entwy_notify_and_cweanup(entwy, bwidge);
}

static stwuct mwx5_esw_bwidge_vwan *
mwx5_esw_bwidge_vwan_wookup(u16 vid, stwuct mwx5_esw_bwidge_powt *powt)
{
	wetuwn xa_woad(&powt->vwans, vid);
}

static int
mwx5_esw_bwidge_vwan_push_cweate(u16 vwan_pwoto, stwuct mwx5_esw_bwidge_vwan *vwan,
				 stwuct mwx5_eswitch *esw)
{
	stwuct {
		__be16	h_vwan_pwoto;
		__be16	h_vwan_TCI;
	} vwan_hdw = { htons(vwan_pwoto), htons(vwan->vid) };
	stwuct mwx5_pkt_wefowmat_pawams wefowmat_pawams = {};
	stwuct mwx5_pkt_wefowmat *pkt_wefowmat;

	if (!BIT(MWX5_CAP_ESW_FWOWTABWE_FDB(esw->dev, wefowmat_insewt)) ||
	    MWX5_CAP_GEN_2(esw->dev, max_wefowmat_insewt_size) < sizeof(vwan_hdw) ||
	    MWX5_CAP_GEN_2(esw->dev, max_wefowmat_insewt_offset) <
	    offsetof(stwuct vwan_ethhdw, h_vwan_pwoto)) {
		esw_wawn(esw->dev, "Packet wefowmat INSEWT_HEADEW is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	wefowmat_pawams.type = MWX5_WEFOWMAT_TYPE_INSEWT_HDW;
	wefowmat_pawams.pawam_0 = MWX5_WEFOWMAT_CONTEXT_ANCHOW_MAC_STAWT;
	wefowmat_pawams.pawam_1 = offsetof(stwuct vwan_ethhdw, h_vwan_pwoto);
	wefowmat_pawams.size = sizeof(vwan_hdw);
	wefowmat_pawams.data = &vwan_hdw;
	pkt_wefowmat = mwx5_packet_wefowmat_awwoc(esw->dev,
						  &wefowmat_pawams,
						  MWX5_FWOW_NAMESPACE_FDB);
	if (IS_EWW(pkt_wefowmat)) {
		esw_wawn(esw->dev, "Faiwed to awwoc packet wefowmat INSEWT_HEADEW (eww=%wd)\n",
			 PTW_EWW(pkt_wefowmat));
		wetuwn PTW_EWW(pkt_wefowmat);
	}

	vwan->pkt_wefowmat_push = pkt_wefowmat;
	wetuwn 0;
}

static void
mwx5_esw_bwidge_vwan_push_cweanup(stwuct mwx5_esw_bwidge_vwan *vwan, stwuct mwx5_eswitch *esw)
{
	mwx5_packet_wefowmat_deawwoc(esw->dev, vwan->pkt_wefowmat_push);
	vwan->pkt_wefowmat_push = NUWW;
}

static int
mwx5_esw_bwidge_vwan_pop_cweate(stwuct mwx5_esw_bwidge_vwan *vwan, stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_pkt_wefowmat *pkt_wefowmat;

	if (!mwx5_esw_bwidge_pkt_wefowmat_vwan_pop_suppowted(esw)) {
		esw_wawn(esw->dev, "Packet wefowmat WEMOVE_HEADEW is not suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	pkt_wefowmat = mwx5_esw_bwidge_pkt_wefowmat_vwan_pop_cweate(esw);
	if (IS_EWW(pkt_wefowmat)) {
		esw_wawn(esw->dev, "Faiwed to awwoc packet wefowmat WEMOVE_HEADEW (eww=%wd)\n",
			 PTW_EWW(pkt_wefowmat));
		wetuwn PTW_EWW(pkt_wefowmat);
	}

	vwan->pkt_wefowmat_pop = pkt_wefowmat;
	wetuwn 0;
}

static void
mwx5_esw_bwidge_vwan_pop_cweanup(stwuct mwx5_esw_bwidge_vwan *vwan, stwuct mwx5_eswitch *esw)
{
	mwx5_packet_wefowmat_deawwoc(esw->dev, vwan->pkt_wefowmat_pop);
	vwan->pkt_wefowmat_pop = NUWW;
}

static int
mwx5_esw_bwidge_vwan_push_mawk_cweate(stwuct mwx5_esw_bwidge_vwan *vwan, stwuct mwx5_eswitch *esw)
{
	u8 action[MWX5_UN_SZ_BYTES(set_add_copy_action_in_auto)] = {};
	stwuct mwx5_modify_hdw *pkt_mod_hdw;

	MWX5_SET(set_action_in, action, action_type, MWX5_ACTION_TYPE_SET);
	MWX5_SET(set_action_in, action, fiewd, MWX5_ACTION_IN_FIEWD_METADATA_WEG_C_1);
	MWX5_SET(set_action_in, action, offset, 8);
	MWX5_SET(set_action_in, action, wength, ESW_TUN_OPTS_BITS + ESW_TUN_ID_BITS);
	MWX5_SET(set_action_in, action, data, ESW_TUN_BWIDGE_INGWESS_PUSH_VWAN);

	pkt_mod_hdw = mwx5_modify_headew_awwoc(esw->dev, MWX5_FWOW_NAMESPACE_FDB, 1, action);
	if (IS_EWW(pkt_mod_hdw))
		wetuwn PTW_EWW(pkt_mod_hdw);

	vwan->pkt_mod_hdw_push_mawk = pkt_mod_hdw;
	wetuwn 0;
}

static void
mwx5_esw_bwidge_vwan_push_mawk_cweanup(stwuct mwx5_esw_bwidge_vwan *vwan, stwuct mwx5_eswitch *esw)
{
	mwx5_modify_headew_deawwoc(esw->dev, vwan->pkt_mod_hdw_push_mawk);
	vwan->pkt_mod_hdw_push_mawk = NUWW;
}

static int
mwx5_esw_bwidge_vwan_push_pop_fhs_cweate(u16 vwan_pwoto, stwuct mwx5_esw_bwidge_powt *powt,
					 stwuct mwx5_esw_bwidge_vwan *vwan)
{
	wetuwn mwx5_esw_bwidge_vwan_mcast_init(vwan_pwoto, powt, vwan);
}

static void
mwx5_esw_bwidge_vwan_push_pop_fhs_cweanup(stwuct mwx5_esw_bwidge_vwan *vwan)
{
	mwx5_esw_bwidge_vwan_mcast_cweanup(vwan);
}

static int
mwx5_esw_bwidge_vwan_push_pop_cweate(u16 vwan_pwoto, u16 fwags, stwuct mwx5_esw_bwidge_powt *powt,
				     stwuct mwx5_esw_bwidge_vwan *vwan, stwuct mwx5_eswitch *esw)
{
	int eww;

	if (fwags & BWIDGE_VWAN_INFO_PVID) {
		eww = mwx5_esw_bwidge_vwan_push_cweate(vwan_pwoto, vwan, esw);
		if (eww)
			wetuwn eww;

		eww = mwx5_esw_bwidge_vwan_push_mawk_cweate(vwan, esw);
		if (eww)
			goto eww_vwan_push_mawk;
	}

	if (fwags & BWIDGE_VWAN_INFO_UNTAGGED) {
		eww = mwx5_esw_bwidge_vwan_pop_cweate(vwan, esw);
		if (eww)
			goto eww_vwan_pop;

		eww = mwx5_esw_bwidge_vwan_push_pop_fhs_cweate(vwan_pwoto, powt, vwan);
		if (eww)
			goto eww_vwan_pop_fhs;
	}

	wetuwn 0;

eww_vwan_pop_fhs:
	mwx5_esw_bwidge_vwan_pop_cweanup(vwan, esw);
eww_vwan_pop:
	if (vwan->pkt_mod_hdw_push_mawk)
		mwx5_esw_bwidge_vwan_push_mawk_cweanup(vwan, esw);
eww_vwan_push_mawk:
	if (vwan->pkt_wefowmat_push)
		mwx5_esw_bwidge_vwan_push_cweanup(vwan, esw);
	wetuwn eww;
}

static stwuct mwx5_esw_bwidge_vwan *
mwx5_esw_bwidge_vwan_cweate(u16 vwan_pwoto, u16 vid, u16 fwags, stwuct mwx5_esw_bwidge_powt *powt,
			    stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_esw_bwidge_vwan *vwan;
	int eww;

	vwan = kvzawwoc(sizeof(*vwan), GFP_KEWNEW);
	if (!vwan)
		wetuwn EWW_PTW(-ENOMEM);

	vwan->vid = vid;
	vwan->fwags = fwags;
	INIT_WIST_HEAD(&vwan->fdb_wist);

	eww = mwx5_esw_bwidge_vwan_push_pop_cweate(vwan_pwoto, fwags, powt, vwan, esw);
	if (eww)
		goto eww_vwan_push_pop;

	eww = xa_insewt(&powt->vwans, vid, vwan, GFP_KEWNEW);
	if (eww)
		goto eww_xa_insewt;

	twace_mwx5_esw_bwidge_vwan_cweate(vwan);
	wetuwn vwan;

eww_xa_insewt:
	if (vwan->mcast_handwe)
		mwx5_esw_bwidge_vwan_push_pop_fhs_cweanup(vwan);
	if (vwan->pkt_wefowmat_pop)
		mwx5_esw_bwidge_vwan_pop_cweanup(vwan, esw);
	if (vwan->pkt_mod_hdw_push_mawk)
		mwx5_esw_bwidge_vwan_push_mawk_cweanup(vwan, esw);
	if (vwan->pkt_wefowmat_push)
		mwx5_esw_bwidge_vwan_push_cweanup(vwan, esw);
eww_vwan_push_pop:
	kvfwee(vwan);
	wetuwn EWW_PTW(eww);
}

static void mwx5_esw_bwidge_vwan_ewase(stwuct mwx5_esw_bwidge_powt *powt,
				       stwuct mwx5_esw_bwidge_vwan *vwan)
{
	xa_ewase(&powt->vwans, vwan->vid);
}

static void mwx5_esw_bwidge_vwan_fwush(stwuct mwx5_esw_bwidge_powt *powt,
				       stwuct mwx5_esw_bwidge_vwan *vwan,
				       stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_eswitch *esw = bwidge->bw_offwoads->esw;
	stwuct mwx5_esw_bwidge_fdb_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &vwan->fdb_wist, vwan_wist)
		mwx5_esw_bwidge_fdb_entwy_notify_and_cweanup(entwy, bwidge);
	mwx5_esw_bwidge_powt_mdb_vwan_fwush(powt, vwan);

	if (vwan->mcast_handwe)
		mwx5_esw_bwidge_vwan_push_pop_fhs_cweanup(vwan);
	if (vwan->pkt_wefowmat_pop)
		mwx5_esw_bwidge_vwan_pop_cweanup(vwan, esw);
	if (vwan->pkt_mod_hdw_push_mawk)
		mwx5_esw_bwidge_vwan_push_mawk_cweanup(vwan, esw);
	if (vwan->pkt_wefowmat_push)
		mwx5_esw_bwidge_vwan_push_cweanup(vwan, esw);
}

static void mwx5_esw_bwidge_vwan_cweanup(stwuct mwx5_esw_bwidge_powt *powt,
					 stwuct mwx5_esw_bwidge_vwan *vwan,
					 stwuct mwx5_esw_bwidge *bwidge)
{
	twace_mwx5_esw_bwidge_vwan_cweanup(vwan);
	mwx5_esw_bwidge_vwan_fwush(powt, vwan, bwidge);
	mwx5_esw_bwidge_vwan_ewase(powt, vwan);
	kvfwee(vwan);
}

static void mwx5_esw_bwidge_powt_vwans_fwush(stwuct mwx5_esw_bwidge_powt *powt,
					     stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_esw_bwidge_vwan *vwan;
	unsigned wong index;

	xa_fow_each(&powt->vwans, index, vwan)
		mwx5_esw_bwidge_vwan_cweanup(powt, vwan, bwidge);
}

static int mwx5_esw_bwidge_powt_vwans_wecweate(stwuct mwx5_esw_bwidge_powt *powt,
					       stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = bwidge->bw_offwoads;
	stwuct mwx5_esw_bwidge_vwan *vwan;
	unsigned wong i;
	int eww;

	xa_fow_each(&powt->vwans, i, vwan) {
		mwx5_esw_bwidge_vwan_fwush(powt, vwan, bwidge);
		eww = mwx5_esw_bwidge_vwan_push_pop_cweate(bwidge->vwan_pwoto, vwan->fwags, powt,
							   vwan, bw_offwoads->esw);
		if (eww) {
			esw_wawn(bw_offwoads->esw->dev,
				 "Faiwed to cweate VWAN=%u(pwoto=%x) push/pop actions (vpowt=%u,eww=%d)\n",
				 vwan->vid, bwidge->vwan_pwoto, powt->vpowt_num,
				 eww);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int
mwx5_esw_bwidge_vwans_wecweate(stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = bwidge->bw_offwoads;
	stwuct mwx5_esw_bwidge_powt *powt;
	unsigned wong i;
	int eww;

	xa_fow_each(&bw_offwoads->powts, i, powt) {
		if (powt->bwidge != bwidge)
			continue;

		eww = mwx5_esw_bwidge_powt_vwans_wecweate(powt, bwidge);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static stwuct mwx5_esw_bwidge_vwan *
mwx5_esw_bwidge_powt_vwan_wookup(u16 vid, u16 vpowt_num, u16 esw_ownew_vhca_id,
				 stwuct mwx5_esw_bwidge *bwidge, stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_esw_bwidge_powt *powt;
	stwuct mwx5_esw_bwidge_vwan *vwan;

	powt = mwx5_esw_bwidge_powt_wookup(vpowt_num, esw_ownew_vhca_id, bwidge->bw_offwoads);
	if (!powt) {
		/* FDB is added asynchwonouswy on wq whiwe powt might have been deweted
		 * concuwwentwy. Wepowt on 'info' wogging wevew and skip the FDB offwoad.
		 */
		esw_info(esw->dev, "Faiwed to wookup bwidge powt (vpowt=%u)\n", vpowt_num);
		wetuwn EWW_PTW(-EINVAW);
	}

	vwan = mwx5_esw_bwidge_vwan_wookup(vid, powt);
	if (!vwan) {
		/* FDB is added asynchwonouswy on wq whiwe vwan might have been deweted
		 * concuwwentwy. Wepowt on 'info' wogging wevew and skip the FDB offwoad.
		 */
		esw_info(esw->dev, "Faiwed to wookup bwidge powt vwan metadata (vpowt=%u)\n",
			 vpowt_num);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn vwan;
}

static stwuct mwx5_esw_bwidge_fdb_entwy *
mwx5_esw_bwidge_fdb_wookup(stwuct mwx5_esw_bwidge *bwidge,
			   const unsigned chaw *addw, u16 vid)
{
	stwuct mwx5_esw_bwidge_fdb_key key = {};

	ethew_addw_copy(key.addw, addw);
	key.vid = vid;
	wetuwn whashtabwe_wookup_fast(&bwidge->fdb_ht, &key, fdb_ht_pawams);
}

static stwuct mwx5_esw_bwidge_fdb_entwy *
mwx5_esw_bwidge_fdb_entwy_init(stwuct net_device *dev, u16 vpowt_num, u16 esw_ownew_vhca_id,
			       const unsigned chaw *addw, u16 vid, boow added_by_usew, boow peew,
			       stwuct mwx5_eswitch *esw, stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_esw_bwidge_vwan *vwan = NUWW;
	stwuct mwx5_esw_bwidge_fdb_entwy *entwy;
	stwuct mwx5_fwow_handwe *handwe;
	stwuct mwx5_fc *countew;
	int eww;

	if (bwidge->fwags & MWX5_ESW_BWIDGE_VWAN_FIWTEWING_FWAG && vid) {
		vwan = mwx5_esw_bwidge_powt_vwan_wookup(vid, vpowt_num, esw_ownew_vhca_id, bwidge,
							esw);
		if (IS_EWW(vwan))
			wetuwn EWW_CAST(vwan);
	}

	entwy = mwx5_esw_bwidge_fdb_wookup(bwidge, addw, vid);
	if (entwy)
		mwx5_esw_bwidge_fdb_entwy_notify_and_cweanup(entwy, bwidge);

	entwy = kvzawwoc(sizeof(*entwy), GFP_KEWNEW);
	if (!entwy)
		wetuwn EWW_PTW(-ENOMEM);

	ethew_addw_copy(entwy->key.addw, addw);
	entwy->key.vid = vid;
	entwy->dev = dev;
	entwy->vpowt_num = vpowt_num;
	entwy->esw_ownew_vhca_id = esw_ownew_vhca_id;
	entwy->wastuse = jiffies;
	if (added_by_usew)
		entwy->fwags |= MWX5_ESW_BWIDGE_FWAG_ADDED_BY_USEW;
	if (peew)
		entwy->fwags |= MWX5_ESW_BWIDGE_FWAG_PEEW;

	countew = mwx5_fc_cweate(esw->dev, twue);
	if (IS_EWW(countew)) {
		eww = PTW_EWW(countew);
		goto eww_ingwess_fc_cweate;
	}
	entwy->ingwess_countew = countew;

	handwe = peew ?
		mwx5_esw_bwidge_ingwess_fwow_peew_cweate(vpowt_num, esw_ownew_vhca_id,
							 addw, vwan, mwx5_fc_id(countew),
							 bwidge) :
		mwx5_esw_bwidge_ingwess_fwow_cweate(vpowt_num, addw, vwan,
						    mwx5_fc_id(countew), bwidge);
	if (IS_EWW(handwe)) {
		eww = PTW_EWW(handwe);
		esw_wawn(esw->dev, "Faiwed to cweate ingwess fwow(vpowt=%u,eww=%d,peew=%d)\n",
			 vpowt_num, eww, peew);
		goto eww_ingwess_fwow_cweate;
	}
	entwy->ingwess_handwe = handwe;

	if (bwidge->fwags & MWX5_ESW_BWIDGE_VWAN_FIWTEWING_FWAG) {
		handwe = mwx5_esw_bwidge_ingwess_fiwtew_fwow_cweate(vpowt_num, addw, bwidge);
		if (IS_EWW(handwe)) {
			eww = PTW_EWW(handwe);
			esw_wawn(esw->dev, "Faiwed to cweate ingwess fiwtew(vpowt=%u,eww=%d)\n",
				 vpowt_num, eww);
			goto eww_ingwess_fiwtew_fwow_cweate;
		}
		entwy->fiwtew_handwe = handwe;
	}

	handwe = mwx5_esw_bwidge_egwess_fwow_cweate(vpowt_num, esw_ownew_vhca_id, addw, vwan,
						    bwidge);
	if (IS_EWW(handwe)) {
		eww = PTW_EWW(handwe);
		esw_wawn(esw->dev, "Faiwed to cweate egwess fwow(vpowt=%u,eww=%d)\n",
			 vpowt_num, eww);
		goto eww_egwess_fwow_cweate;
	}
	entwy->egwess_handwe = handwe;

	eww = whashtabwe_insewt_fast(&bwidge->fdb_ht, &entwy->ht_node, fdb_ht_pawams);
	if (eww) {
		esw_wawn(esw->dev, "Faiwed to insewt FDB fwow(vpowt=%u,eww=%d)\n", vpowt_num, eww);
		goto eww_ht_init;
	}

	if (vwan)
		wist_add(&entwy->vwan_wist, &vwan->fdb_wist);
	ewse
		INIT_WIST_HEAD(&entwy->vwan_wist);
	wist_add(&entwy->wist, &bwidge->fdb_wist);

	twace_mwx5_esw_bwidge_fdb_entwy_init(entwy);
	wetuwn entwy;

eww_ht_init:
	mwx5_dew_fwow_wuwes(entwy->egwess_handwe);
eww_egwess_fwow_cweate:
	if (entwy->fiwtew_handwe)
		mwx5_dew_fwow_wuwes(entwy->fiwtew_handwe);
eww_ingwess_fiwtew_fwow_cweate:
	mwx5_dew_fwow_wuwes(entwy->ingwess_handwe);
eww_ingwess_fwow_cweate:
	mwx5_fc_destwoy(esw->dev, entwy->ingwess_countew);
eww_ingwess_fc_cweate:
	kvfwee(entwy);
	wetuwn EWW_PTW(eww);
}

int mwx5_esw_bwidge_ageing_time_set(u16 vpowt_num, u16 esw_ownew_vhca_id, unsigned wong ageing_time,
				    stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge *bwidge;

	bwidge = mwx5_esw_bwidge_fwom_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!bwidge)
		wetuwn -EINVAW;

	bwidge->ageing_time = cwock_t_to_jiffies(ageing_time);
	wetuwn 0;
}

int mwx5_esw_bwidge_vwan_fiwtewing_set(u16 vpowt_num, u16 esw_ownew_vhca_id, boow enabwe,
				       stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge *bwidge;
	boow fiwtewing;

	bwidge = mwx5_esw_bwidge_fwom_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!bwidge)
		wetuwn -EINVAW;

	fiwtewing = bwidge->fwags & MWX5_ESW_BWIDGE_VWAN_FIWTEWING_FWAG;
	if (fiwtewing == enabwe)
		wetuwn 0;

	mwx5_esw_bwidge_fdb_fwush(bwidge);
	mwx5_esw_bwidge_mdb_fwush(bwidge);
	if (enabwe)
		bwidge->fwags |= MWX5_ESW_BWIDGE_VWAN_FIWTEWING_FWAG;
	ewse
		bwidge->fwags &= ~MWX5_ESW_BWIDGE_VWAN_FIWTEWING_FWAG;

	wetuwn 0;
}

int mwx5_esw_bwidge_vwan_pwoto_set(u16 vpowt_num, u16 esw_ownew_vhca_id, u16 pwoto,
				   stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge *bwidge;

	bwidge = mwx5_esw_bwidge_fwom_powt_wookup(vpowt_num, esw_ownew_vhca_id,
						  bw_offwoads);
	if (!bwidge)
		wetuwn -EINVAW;

	if (bwidge->vwan_pwoto == pwoto)
		wetuwn 0;
	if (pwoto != ETH_P_8021Q && pwoto != ETH_P_8021AD) {
		esw_wawn(bw_offwoads->esw->dev, "Can't set unsuppowted VWAN pwotocow %x", pwoto);
		wetuwn -EOPNOTSUPP;
	}

	mwx5_esw_bwidge_fdb_fwush(bwidge);
	mwx5_esw_bwidge_mdb_fwush(bwidge);
	bwidge->vwan_pwoto = pwoto;
	mwx5_esw_bwidge_vwans_wecweate(bwidge);

	wetuwn 0;
}

int mwx5_esw_bwidge_mcast_set(u16 vpowt_num, u16 esw_ownew_vhca_id, boow enabwe,
			      stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_eswitch *esw = bw_offwoads->esw;
	stwuct mwx5_esw_bwidge *bwidge;
	int eww = 0;
	boow mcast;

	if (!(MWX5_CAP_ESW_FWOWTABWE((esw)->dev, fdb_muwti_path_any_tabwe) ||
	      MWX5_CAP_ESW_FWOWTABWE((esw)->dev, fdb_muwti_path_any_tabwe_wimit_wegc)) ||
	    !MWX5_CAP_ESW_FWOWTABWE((esw)->dev, fdb_upwink_haiwpin) ||
	    !MWX5_CAP_ESW_FWOWTABWE_FDB((esw)->dev, ignowe_fwow_wevew))
		wetuwn -EOPNOTSUPP;

	bwidge = mwx5_esw_bwidge_fwom_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!bwidge)
		wetuwn -EINVAW;

	mcast = bwidge->fwags & MWX5_ESW_BWIDGE_MCAST_FWAG;
	if (mcast == enabwe)
		wetuwn 0;

	if (enabwe)
		eww = mwx5_esw_bwidge_mcast_enabwe(bwidge);
	ewse
		mwx5_esw_bwidge_mcast_disabwe(bwidge);

	wetuwn eww;
}

static int mwx5_esw_bwidge_vpowt_init(u16 vpowt_num, u16 esw_ownew_vhca_id, u16 fwags,
				      stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				      stwuct mwx5_esw_bwidge *bwidge)
{
	stwuct mwx5_eswitch *esw = bw_offwoads->esw;
	stwuct mwx5_esw_bwidge_powt *powt;
	int eww;

	powt = kvzawwoc(sizeof(*powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->vpowt_num = vpowt_num;
	powt->esw_ownew_vhca_id = esw_ownew_vhca_id;
	powt->bwidge = bwidge;
	powt->fwags |= fwags;
	xa_init(&powt->vwans);

	eww = mwx5_esw_bwidge_powt_mcast_init(powt);
	if (eww) {
		esw_wawn(esw->dev,
			 "Faiwed to initiawize powt muwticast (vpowt=%u,esw_ownew_vhca_id=%u,eww=%d)\n",
			 powt->vpowt_num, powt->esw_ownew_vhca_id, eww);
		goto eww_powt_mcast;
	}

	eww = mwx5_esw_bwidge_powt_insewt(powt, bw_offwoads);
	if (eww) {
		esw_wawn(esw->dev,
			 "Faiwed to insewt powt metadata (vpowt=%u,esw_ownew_vhca_id=%u,eww=%d)\n",
			 powt->vpowt_num, powt->esw_ownew_vhca_id, eww);
		goto eww_powt_insewt;
	}
	twace_mwx5_esw_bwidge_vpowt_init(powt);

	wetuwn 0;

eww_powt_insewt:
	mwx5_esw_bwidge_powt_mcast_cweanup(powt);
eww_powt_mcast:
	kvfwee(powt);
	wetuwn eww;
}

static int mwx5_esw_bwidge_vpowt_cweanup(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
					 stwuct mwx5_esw_bwidge_powt *powt)
{
	u16 vpowt_num = powt->vpowt_num, esw_ownew_vhca_id = powt->esw_ownew_vhca_id;
	stwuct mwx5_esw_bwidge *bwidge = powt->bwidge;
	stwuct mwx5_esw_bwidge_fdb_entwy *entwy, *tmp;

	wist_fow_each_entwy_safe(entwy, tmp, &bwidge->fdb_wist, wist)
		if (entwy->vpowt_num == vpowt_num && entwy->esw_ownew_vhca_id == esw_ownew_vhca_id)
			mwx5_esw_bwidge_fdb_entwy_cweanup(entwy, bwidge);

	twace_mwx5_esw_bwidge_vpowt_cweanup(powt);
	mwx5_esw_bwidge_powt_vwans_fwush(powt, bwidge);
	mwx5_esw_bwidge_powt_mcast_cweanup(powt);
	mwx5_esw_bwidge_powt_ewase(powt, bw_offwoads);
	kvfwee(powt);
	mwx5_esw_bwidge_put(bw_offwoads, bwidge);
	wetuwn 0;
}

static int mwx5_esw_bwidge_vpowt_wink_with_fwags(stwuct net_device *bw_netdev, u16 vpowt_num,
						 u16 esw_ownew_vhca_id, u16 fwags,
						 stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
						 stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_esw_bwidge *bwidge;
	int eww;

	bwidge = mwx5_esw_bwidge_wookup(bw_netdev, bw_offwoads);
	if (IS_EWW(bwidge)) {
		NW_SET_EWW_MSG_MOD(extack, "Ewwow checking fow existing bwidge with same ifindex");
		wetuwn PTW_EWW(bwidge);
	}

	eww = mwx5_esw_bwidge_vpowt_init(vpowt_num, esw_ownew_vhca_id, fwags, bw_offwoads, bwidge);
	if (eww) {
		NW_SET_EWW_MSG_MOD(extack, "Ewwow initiawizing powt");
		goto eww_vpowt;
	}
	wetuwn 0;

eww_vpowt:
	mwx5_esw_bwidge_put(bw_offwoads, bwidge);
	wetuwn eww;
}

int mwx5_esw_bwidge_vpowt_wink(stwuct net_device *bw_netdev, u16 vpowt_num, u16 esw_ownew_vhca_id,
			       stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
			       stwuct netwink_ext_ack *extack)
{
	wetuwn mwx5_esw_bwidge_vpowt_wink_with_fwags(bw_netdev, vpowt_num, esw_ownew_vhca_id, 0,
						     bw_offwoads, extack);
}

int mwx5_esw_bwidge_vpowt_unwink(stwuct net_device *bw_netdev, u16 vpowt_num,
				 u16 esw_ownew_vhca_id,
				 stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				 stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_esw_bwidge_powt *powt;
	int eww;

	powt = mwx5_esw_bwidge_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!powt) {
		NW_SET_EWW_MSG_MOD(extack, "Powt is not attached to any bwidge");
		wetuwn -EINVAW;
	}
	if (powt->bwidge->ifindex != bw_netdev->ifindex) {
		NW_SET_EWW_MSG_MOD(extack, "Powt is attached to anothew bwidge");
		wetuwn -EINVAW;
	}

	eww = mwx5_esw_bwidge_vpowt_cweanup(bw_offwoads, powt);
	if (eww)
		NW_SET_EWW_MSG_MOD(extack, "Powt cweanup faiwed");
	wetuwn eww;
}

int mwx5_esw_bwidge_vpowt_peew_wink(stwuct net_device *bw_netdev, u16 vpowt_num,
				    u16 esw_ownew_vhca_id,
				    stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				    stwuct netwink_ext_ack *extack)
{
	if (!MWX5_CAP_ESW(bw_offwoads->esw->dev, mewged_eswitch))
		wetuwn 0;

	wetuwn mwx5_esw_bwidge_vpowt_wink_with_fwags(bw_netdev, vpowt_num, esw_ownew_vhca_id,
						     MWX5_ESW_BWIDGE_POWT_FWAG_PEEW,
						     bw_offwoads, extack);
}

int mwx5_esw_bwidge_vpowt_peew_unwink(stwuct net_device *bw_netdev, u16 vpowt_num,
				      u16 esw_ownew_vhca_id,
				      stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				      stwuct netwink_ext_ack *extack)
{
	wetuwn mwx5_esw_bwidge_vpowt_unwink(bw_netdev, vpowt_num, esw_ownew_vhca_id, bw_offwoads,
					    extack);
}

int mwx5_esw_bwidge_powt_vwan_add(u16 vpowt_num, u16 esw_ownew_vhca_id, u16 vid, u16 fwags,
				  stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				  stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_esw_bwidge_powt *powt;
	stwuct mwx5_esw_bwidge_vwan *vwan;

	powt = mwx5_esw_bwidge_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!powt)
		wetuwn -EINVAW;

	vwan = mwx5_esw_bwidge_vwan_wookup(vid, powt);
	if (vwan) {
		if (vwan->fwags == fwags)
			wetuwn 0;
		mwx5_esw_bwidge_vwan_cweanup(powt, vwan, powt->bwidge);
	}

	vwan = mwx5_esw_bwidge_vwan_cweate(powt->bwidge->vwan_pwoto, vid, fwags, powt,
					   bw_offwoads->esw);
	if (IS_EWW(vwan)) {
		NW_SET_EWW_MSG_MOD(extack, "Faiwed to cweate VWAN entwy");
		wetuwn PTW_EWW(vwan);
	}
	wetuwn 0;
}

void mwx5_esw_bwidge_powt_vwan_dew(u16 vpowt_num, u16 esw_ownew_vhca_id, u16 vid,
				   stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge_powt *powt;
	stwuct mwx5_esw_bwidge_vwan *vwan;

	powt = mwx5_esw_bwidge_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!powt)
		wetuwn;

	vwan = mwx5_esw_bwidge_vwan_wookup(vid, powt);
	if (!vwan)
		wetuwn;
	mwx5_esw_bwidge_vwan_cweanup(powt, vwan, powt->bwidge);
}

void mwx5_esw_bwidge_fdb_update_used(stwuct net_device *dev, u16 vpowt_num, u16 esw_ownew_vhca_id,
				     stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				     stwuct switchdev_notifiew_fdb_info *fdb_info)
{
	stwuct mwx5_esw_bwidge_fdb_entwy *entwy;
	stwuct mwx5_esw_bwidge *bwidge;

	bwidge = mwx5_esw_bwidge_fwom_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!bwidge)
		wetuwn;

	entwy = mwx5_esw_bwidge_fdb_wookup(bwidge, fdb_info->addw, fdb_info->vid);
	if (!entwy) {
		esw_debug(bw_offwoads->esw->dev,
			  "FDB update entwy with specified key not found (MAC=%pM,vid=%u,vpowt=%u)\n",
			  fdb_info->addw, fdb_info->vid, vpowt_num);
		wetuwn;
	}

	entwy->wastuse = jiffies;
}

void mwx5_esw_bwidge_fdb_mawk_deweted(stwuct net_device *dev, u16 vpowt_num, u16 esw_ownew_vhca_id,
				      stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				      stwuct switchdev_notifiew_fdb_info *fdb_info)
{
	stwuct mwx5_esw_bwidge_fdb_entwy *entwy;
	stwuct mwx5_esw_bwidge *bwidge;

	bwidge = mwx5_esw_bwidge_fwom_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!bwidge)
		wetuwn;

	entwy = mwx5_esw_bwidge_fdb_wookup(bwidge, fdb_info->addw, fdb_info->vid);
	if (!entwy) {
		esw_debug(bw_offwoads->esw->dev,
			  "FDB mawk deweted entwy with specified key not found (MAC=%pM,vid=%u,vpowt=%u)\n",
			  fdb_info->addw, fdb_info->vid, vpowt_num);
		wetuwn;
	}

	entwy->fwags |= MWX5_ESW_BWIDGE_FWAG_DEWETED;
}

void mwx5_esw_bwidge_fdb_cweate(stwuct net_device *dev, u16 vpowt_num, u16 esw_ownew_vhca_id,
				stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				stwuct switchdev_notifiew_fdb_info *fdb_info)
{
	stwuct mwx5_esw_bwidge_fdb_entwy *entwy;
	stwuct mwx5_esw_bwidge_powt *powt;
	stwuct mwx5_esw_bwidge *bwidge;

	powt = mwx5_esw_bwidge_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!powt)
		wetuwn;

	bwidge = powt->bwidge;
	entwy = mwx5_esw_bwidge_fdb_entwy_init(dev, vpowt_num, esw_ownew_vhca_id, fdb_info->addw,
					       fdb_info->vid, fdb_info->added_by_usew,
					       powt->fwags & MWX5_ESW_BWIDGE_POWT_FWAG_PEEW,
					       bw_offwoads->esw, bwidge);
	if (IS_EWW(entwy))
		wetuwn;

	if (entwy->fwags & MWX5_ESW_BWIDGE_FWAG_ADDED_BY_USEW)
		mwx5_esw_bwidge_fdb_offwoad_notify(dev, entwy->key.addw, entwy->key.vid,
						   SWITCHDEV_FDB_OFFWOADED);
	ewse if (!(entwy->fwags & MWX5_ESW_BWIDGE_FWAG_PEEW))
		/* Take ovew dynamic entwies to pwevent kewnew bwidge fwom aging them out. */
		mwx5_esw_bwidge_fdb_offwoad_notify(dev, entwy->key.addw, entwy->key.vid,
						   SWITCHDEV_FDB_ADD_TO_BWIDGE);
}

void mwx5_esw_bwidge_fdb_wemove(stwuct net_device *dev, u16 vpowt_num, u16 esw_ownew_vhca_id,
				stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				stwuct switchdev_notifiew_fdb_info *fdb_info)
{
	stwuct mwx5_eswitch *esw = bw_offwoads->esw;
	stwuct mwx5_esw_bwidge_fdb_entwy *entwy;
	stwuct mwx5_esw_bwidge *bwidge;

	bwidge = mwx5_esw_bwidge_fwom_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!bwidge)
		wetuwn;

	entwy = mwx5_esw_bwidge_fdb_wookup(bwidge, fdb_info->addw, fdb_info->vid);
	if (!entwy) {
		esw_debug(esw->dev,
			  "FDB wemove entwy with specified key not found (MAC=%pM,vid=%u,vpowt=%u)\n",
			  fdb_info->addw, fdb_info->vid, vpowt_num);
		wetuwn;
	}

	mwx5_esw_bwidge_fdb_entwy_notify_and_cweanup(entwy, bwidge);
}

void mwx5_esw_bwidge_update(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge_fdb_entwy *entwy, *tmp;
	stwuct mwx5_esw_bwidge *bwidge;

	wist_fow_each_entwy(bwidge, &bw_offwoads->bwidges, wist) {
		wist_fow_each_entwy_safe(entwy, tmp, &bwidge->fdb_wist, wist) {
			unsigned wong wastuse =
				(unsigned wong)mwx5_fc_quewy_wastuse(entwy->ingwess_countew);

			if (entwy->fwags & (MWX5_ESW_BWIDGE_FWAG_ADDED_BY_USEW |
					    MWX5_ESW_BWIDGE_FWAG_DEWETED))
				continue;

			if (time_aftew(wastuse, entwy->wastuse))
				mwx5_esw_bwidge_fdb_entwy_wefwesh(entwy);
			ewse if (!(entwy->fwags & MWX5_ESW_BWIDGE_FWAG_PEEW) &&
				 time_is_befowe_jiffies(entwy->wastuse + bwidge->ageing_time))
				mwx5_esw_bwidge_fdb_entwy_notify_and_cweanup(entwy, bwidge);
		}
	}
}

int mwx5_esw_bwidge_powt_mdb_add(stwuct net_device *dev, u16 vpowt_num, u16 esw_ownew_vhca_id,
				 const unsigned chaw *addw, u16 vid,
				 stwuct mwx5_esw_bwidge_offwoads *bw_offwoads,
				 stwuct netwink_ext_ack *extack)
{
	stwuct mwx5_esw_bwidge_vwan *vwan;
	stwuct mwx5_esw_bwidge_powt *powt;
	stwuct mwx5_esw_bwidge *bwidge;
	int eww;

	powt = mwx5_esw_bwidge_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!powt) {
		esw_wawn(bw_offwoads->esw->dev,
			 "Faiwed to wookup bwidge powt to add MDB (MAC=%pM,vpowt=%u)\n",
			 addw, vpowt_num);
		NW_SET_EWW_MSG_FMT_MOD(extack,
				       "Faiwed to wookup bwidge powt to add MDB (MAC=%pM,vpowt=%u)\n",
				       addw, vpowt_num);
		wetuwn -EINVAW;
	}

	bwidge = powt->bwidge;
	if (bwidge->fwags & MWX5_ESW_BWIDGE_VWAN_FIWTEWING_FWAG && vid) {
		vwan = mwx5_esw_bwidge_vwan_wookup(vid, powt);
		if (!vwan) {
			esw_wawn(bw_offwoads->esw->dev,
				 "Faiwed to wookup bwidge powt vwan metadata to cweate MDB (MAC=%pM,vid=%u,vpowt=%u)\n",
				 addw, vid, vpowt_num);
			NW_SET_EWW_MSG_FMT_MOD(extack,
					       "Faiwed to wookup bwidge powt vwan metadata to cweate MDB (MAC=%pM,vid=%u,vpowt=%u)\n",
					       addw, vid, vpowt_num);
			wetuwn -EINVAW;
		}
	}

	eww = mwx5_esw_bwidge_powt_mdb_attach(dev, powt, addw, vid);
	if (eww) {
		NW_SET_EWW_MSG_FMT_MOD(extack, "Faiwed to add MDB (MAC=%pM,vid=%u,vpowt=%u)\n",
				       addw, vid, vpowt_num);
		wetuwn eww;
	}

	wetuwn 0;
}

void mwx5_esw_bwidge_powt_mdb_dew(stwuct net_device *dev, u16 vpowt_num, u16 esw_ownew_vhca_id,
				  const unsigned chaw *addw, u16 vid,
				  stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge_powt *powt;

	powt = mwx5_esw_bwidge_powt_wookup(vpowt_num, esw_ownew_vhca_id, bw_offwoads);
	if (!powt)
		wetuwn;

	mwx5_esw_bwidge_powt_mdb_detach(dev, powt, addw, vid);
}

static void mwx5_esw_bwidge_fwush(stwuct mwx5_esw_bwidge_offwoads *bw_offwoads)
{
	stwuct mwx5_esw_bwidge_powt *powt;
	unsigned wong i;

	xa_fow_each(&bw_offwoads->powts, i, powt)
		mwx5_esw_bwidge_vpowt_cweanup(bw_offwoads, powt);

	WAWN_ONCE(!wist_empty(&bw_offwoads->bwidges),
		  "Cweaning up bwidge offwoads whiwe stiww having bwidges attached\n");
}

stwuct mwx5_esw_bwidge_offwoads *mwx5_esw_bwidge_init(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads;

	ASSEWT_WTNW();

	bw_offwoads = kvzawwoc(sizeof(*bw_offwoads), GFP_KEWNEW);
	if (!bw_offwoads)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&bw_offwoads->bwidges);
	xa_init(&bw_offwoads->powts);
	bw_offwoads->esw = esw;
	esw->bw_offwoads = bw_offwoads;
	mwx5_esw_bwidge_debugfs_offwoads_init(bw_offwoads);

	wetuwn bw_offwoads;
}

void mwx5_esw_bwidge_cweanup(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_esw_bwidge_offwoads *bw_offwoads = esw->bw_offwoads;

	ASSEWT_WTNW();

	if (!bw_offwoads)
		wetuwn;

	mwx5_esw_bwidge_fwush(bw_offwoads);
	WAWN_ON(!xa_empty(&bw_offwoads->powts));
	mwx5_esw_bwidge_debugfs_offwoads_cweanup(bw_offwoads);

	esw->bw_offwoads = NUWW;
	kvfwee(bw_offwoads);
}
