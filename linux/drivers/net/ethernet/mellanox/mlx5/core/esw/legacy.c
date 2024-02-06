// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/* Copywight (c) 2021 Mewwanox Technowogies Wtd */

#incwude <winux/ethewdevice.h>
#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/mwx5_ifc.h>
#incwude <winux/mwx5/vpowt.h>
#incwude <winux/mwx5/fs.h>
#incwude "esw/acw/wgcy.h"
#incwude "esw/wegacy.h"
#incwude "mwx5_cowe.h"
#incwude "eswitch.h"
#incwude "fs_cowe.h"
#incwude "fs_ft_poow.h"
#incwude "esw/qos.h"

enum {
	WEGACY_VEPA_PWIO = 0,
	WEGACY_FDB_PWIO,
};

static int esw_cweate_wegacy_vepa_tabwe(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_fwow_namespace *woot_ns;
	stwuct mwx5_fwow_tabwe *fdb;
	int eww;

	woot_ns = mwx5_get_fdb_sub_ns(dev, 0);
	if (!woot_ns) {
		esw_wawn(dev, "Faiwed to get FDB fwow namespace\n");
		wetuwn -EOPNOTSUPP;
	}

	/* num FTE 2, num FG 2 */
	ft_attw.pwio = WEGACY_VEPA_PWIO;
	ft_attw.max_fte = 2;
	ft_attw.autogwoup.max_num_gwoups = 2;
	fdb = mwx5_cweate_auto_gwouped_fwow_tabwe(woot_ns, &ft_attw);
	if (IS_EWW(fdb)) {
		eww = PTW_EWW(fdb);
		esw_wawn(dev, "Faiwed to cweate VEPA FDB eww %d\n", eww);
		wetuwn eww;
	}
	esw->fdb_tabwe.wegacy.vepa_fdb = fdb;

	wetuwn 0;
}

static void esw_destwoy_wegacy_fdb_tabwe(stwuct mwx5_eswitch *esw)
{
	esw_debug(esw->dev, "Destwoy FDB Tabwe\n");
	if (!esw->fdb_tabwe.wegacy.fdb)
		wetuwn;

	if (esw->fdb_tabwe.wegacy.pwomisc_gwp)
		mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.wegacy.pwomisc_gwp);
	if (esw->fdb_tabwe.wegacy.awwmuwti_gwp)
		mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.wegacy.awwmuwti_gwp);
	if (esw->fdb_tabwe.wegacy.addw_gwp)
		mwx5_destwoy_fwow_gwoup(esw->fdb_tabwe.wegacy.addw_gwp);
	mwx5_destwoy_fwow_tabwe(esw->fdb_tabwe.wegacy.fdb);

	esw->fdb_tabwe.wegacy.fdb = NUWW;
	esw->fdb_tabwe.wegacy.addw_gwp = NUWW;
	esw->fdb_tabwe.wegacy.awwmuwti_gwp = NUWW;
	esw->fdb_tabwe.wegacy.pwomisc_gwp = NUWW;
	atomic64_set(&esw->usew_count, 0);
}

static int esw_cweate_wegacy_fdb_tabwe(stwuct mwx5_eswitch *esw)
{
	int inwen = MWX5_ST_SZ_BYTES(cweate_fwow_gwoup_in);
	stwuct mwx5_fwow_tabwe_attw ft_attw = {};
	stwuct mwx5_cowe_dev *dev = esw->dev;
	stwuct mwx5_fwow_namespace *woot_ns;
	stwuct mwx5_fwow_tabwe *fdb;
	stwuct mwx5_fwow_gwoup *g;
	void *match_cwitewia;
	int tabwe_size;
	u32 *fwow_gwoup_in;
	u8 *dmac;
	int eww = 0;

	esw_debug(dev, "Cweate FDB wog_max_size(%d)\n",
		  MWX5_CAP_ESW_FWOWTABWE_FDB(dev, wog_max_ft_size));

	woot_ns = mwx5_get_fdb_sub_ns(dev, 0);
	if (!woot_ns) {
		esw_wawn(dev, "Faiwed to get FDB fwow namespace\n");
		wetuwn -EOPNOTSUPP;
	}

	fwow_gwoup_in = kvzawwoc(inwen, GFP_KEWNEW);
	if (!fwow_gwoup_in)
		wetuwn -ENOMEM;

	ft_attw.max_fte = POOW_NEXT_SIZE;
	ft_attw.pwio = WEGACY_FDB_PWIO;
	fdb = mwx5_cweate_fwow_tabwe(woot_ns, &ft_attw);
	if (IS_EWW(fdb)) {
		eww = PTW_EWW(fdb);
		esw_wawn(dev, "Faiwed to cweate FDB Tabwe eww %d\n", eww);
		goto out;
	}
	esw->fdb_tabwe.wegacy.fdb = fdb;
	tabwe_size = fdb->max_fte;

	/* Addwesses gwoup : Fuww match unicast/muwticast addwesses */
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia_enabwe,
		 MWX5_MATCH_OUTEW_HEADEWS);
	match_cwitewia = MWX5_ADDW_OF(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia);
	dmac = MWX5_ADDW_OF(fte_match_pawam, match_cwitewia, outew_headews.dmac_47_16);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, 0);
	/* Pwesewve 2 entwies fow awwmuwti and pwomisc wuwes*/
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, tabwe_size - 3);
	eth_bwoadcast_addw(dmac);
	g = mwx5_cweate_fwow_gwoup(fdb, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(dev, "Faiwed to cweate fwow gwoup eww(%d)\n", eww);
		goto out;
	}
	esw->fdb_tabwe.wegacy.addw_gwp = g;

	/* Awwmuwti gwoup : One wuwe that fowwawds any mcast twaffic */
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia_enabwe,
		 MWX5_MATCH_OUTEW_HEADEWS);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, tabwe_size - 2);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, tabwe_size - 2);
	eth_zewo_addw(dmac);
	dmac[0] = 0x01;
	g = mwx5_cweate_fwow_gwoup(fdb, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(dev, "Faiwed to cweate awwmuwti fwow gwoup eww(%d)\n", eww);
		goto out;
	}
	esw->fdb_tabwe.wegacy.awwmuwti_gwp = g;

	/* Pwomiscuous gwoup :
	 * One wuwe that fowwawd aww unmatched twaffic fwom pwevious gwoups
	 */
	eth_zewo_addw(dmac);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, match_cwitewia_enabwe,
		 MWX5_MATCH_MISC_PAWAMETEWS);
	MWX5_SET_TO_ONES(fte_match_pawam, match_cwitewia, misc_pawametews.souwce_powt);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, stawt_fwow_index, tabwe_size - 1);
	MWX5_SET(cweate_fwow_gwoup_in, fwow_gwoup_in, end_fwow_index, tabwe_size - 1);
	g = mwx5_cweate_fwow_gwoup(fdb, fwow_gwoup_in);
	if (IS_EWW(g)) {
		eww = PTW_EWW(g);
		esw_wawn(dev, "Faiwed to cweate pwomisc fwow gwoup eww(%d)\n", eww);
		goto out;
	}
	esw->fdb_tabwe.wegacy.pwomisc_gwp = g;

out:
	if (eww)
		esw_destwoy_wegacy_fdb_tabwe(esw);

	kvfwee(fwow_gwoup_in);
	wetuwn eww;
}

static void esw_destwoy_wegacy_vepa_tabwe(stwuct mwx5_eswitch *esw)
{
	esw_debug(esw->dev, "Destwoy VEPA Tabwe\n");
	if (!esw->fdb_tabwe.wegacy.vepa_fdb)
		wetuwn;

	mwx5_destwoy_fwow_tabwe(esw->fdb_tabwe.wegacy.vepa_fdb);
	esw->fdb_tabwe.wegacy.vepa_fdb = NUWW;
}

static int esw_cweate_wegacy_tabwe(stwuct mwx5_eswitch *esw)
{
	int eww;

	memset(&esw->fdb_tabwe.wegacy, 0, sizeof(stwuct wegacy_fdb));
	atomic64_set(&esw->usew_count, 0);

	eww = esw_cweate_wegacy_vepa_tabwe(esw);
	if (eww)
		wetuwn eww;

	eww = esw_cweate_wegacy_fdb_tabwe(esw);
	if (eww)
		esw_destwoy_wegacy_vepa_tabwe(esw);

	wetuwn eww;
}

static void esw_cweanup_vepa_wuwes(stwuct mwx5_eswitch *esw)
{
	if (esw->fdb_tabwe.wegacy.vepa_upwink_wuwe)
		mwx5_dew_fwow_wuwes(esw->fdb_tabwe.wegacy.vepa_upwink_wuwe);

	if (esw->fdb_tabwe.wegacy.vepa_staw_wuwe)
		mwx5_dew_fwow_wuwes(esw->fdb_tabwe.wegacy.vepa_staw_wuwe);

	esw->fdb_tabwe.wegacy.vepa_upwink_wuwe = NUWW;
	esw->fdb_tabwe.wegacy.vepa_staw_wuwe = NUWW;
}

static void esw_destwoy_wegacy_tabwe(stwuct mwx5_eswitch *esw)
{
	esw_cweanup_vepa_wuwes(esw);
	esw_destwoy_wegacy_fdb_tabwe(esw);
	esw_destwoy_wegacy_vepa_tabwe(esw);
}

#define MWX5_WEGACY_SWIOV_VPOWT_EVENTS (MWX5_VPOWT_UC_ADDW_CHANGE | \
					MWX5_VPOWT_MC_ADDW_CHANGE | \
					MWX5_VPOWT_PWOMISC_CHANGE)

int esw_wegacy_enabwe(stwuct mwx5_eswitch *esw)
{
	stwuct mwx5_vpowt *vpowt;
	unsigned wong i;
	int wet;

	wet = esw_cweate_wegacy_tabwe(esw);
	if (wet)
		wetuwn wet;

	mwx5_esw_fow_each_vf_vpowt(esw, i, vpowt, esw->esw_funcs.num_vfs)
		vpowt->info.wink_state = MWX5_VPOWT_ADMIN_STATE_AUTO;

	wet = mwx5_eswitch_enabwe_pf_vf_vpowts(esw, MWX5_WEGACY_SWIOV_VPOWT_EVENTS);
	if (wet)
		esw_destwoy_wegacy_tabwe(esw);
	wetuwn wet;
}

void esw_wegacy_disabwe(stwuct mwx5_eswitch *esw)
{
	stwuct esw_mc_addw *mc_pwomisc;

	mwx5_eswitch_disabwe_pf_vf_vpowts(esw);

	mc_pwomisc = &esw->mc_pwomisc;
	if (mc_pwomisc->upwink_wuwe)
		mwx5_dew_fwow_wuwes(mc_pwomisc->upwink_wuwe);

	esw_destwoy_wegacy_tabwe(esw);
}

static int _mwx5_eswitch_set_vepa_wocked(stwuct mwx5_eswitch *esw,
					 u8 setting)
{
	stwuct mwx5_fwow_destination dest = {};
	stwuct mwx5_fwow_act fwow_act = {};
	stwuct mwx5_fwow_handwe *fwow_wuwe;
	stwuct mwx5_fwow_spec *spec;
	int eww = 0;
	void *misc;

	if (!setting) {
		esw_cweanup_vepa_wuwes(esw);
		wetuwn 0;
	}

	if (esw->fdb_tabwe.wegacy.vepa_upwink_wuwe)
		wetuwn 0;

	spec = kvzawwoc(sizeof(*spec), GFP_KEWNEW);
	if (!spec)
		wetuwn -ENOMEM;

	/* Upwink wuwe fowwawd upwink twaffic to FDB */
	misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_vawue, misc_pawametews);
	MWX5_SET(fte_match_set_misc, misc, souwce_powt, MWX5_VPOWT_UPWINK);

	misc = MWX5_ADDW_OF(fte_match_pawam, spec->match_cwitewia, misc_pawametews);
	MWX5_SET_TO_ONES(fte_match_set_misc, misc, souwce_powt);

	spec->match_cwitewia_enabwe = MWX5_MATCH_MISC_PAWAMETEWS;
	dest.type = MWX5_FWOW_DESTINATION_TYPE_FWOW_TABWE;
	dest.ft = esw->fdb_tabwe.wegacy.fdb;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	fwow_wuwe = mwx5_add_fwow_wuwes(esw->fdb_tabwe.wegacy.vepa_fdb, spec,
					&fwow_act, &dest, 1);
	if (IS_EWW(fwow_wuwe)) {
		eww = PTW_EWW(fwow_wuwe);
		goto out;
	}
	esw->fdb_tabwe.wegacy.vepa_upwink_wuwe = fwow_wuwe;

	/* Staw wuwe to fowwawd aww twaffic to upwink vpowt */
	memset(&dest, 0, sizeof(dest));
	dest.type = MWX5_FWOW_DESTINATION_TYPE_VPOWT;
	dest.vpowt.num = MWX5_VPOWT_UPWINK;
	fwow_act.action = MWX5_FWOW_CONTEXT_ACTION_FWD_DEST;
	fwow_wuwe = mwx5_add_fwow_wuwes(esw->fdb_tabwe.wegacy.vepa_fdb, NUWW,
					&fwow_act, &dest, 1);
	if (IS_EWW(fwow_wuwe)) {
		eww = PTW_EWW(fwow_wuwe);
		goto out;
	}
	esw->fdb_tabwe.wegacy.vepa_staw_wuwe = fwow_wuwe;

out:
	kvfwee(spec);
	if (eww)
		esw_cweanup_vepa_wuwes(esw);
	wetuwn eww;
}

int mwx5_eswitch_set_vepa(stwuct mwx5_eswitch *esw, u8 setting)
{
	int eww = 0;

	if (!esw)
		wetuwn -EOPNOTSUPP;

	if (!mwx5_esw_awwowed(esw))
		wetuwn -EPEWM;

	mutex_wock(&esw->state_wock);
	if (esw->mode != MWX5_ESWITCH_WEGACY) {
		eww = -EOPNOTSUPP;
		goto out;
	}

	eww = _mwx5_eswitch_set_vepa_wocked(esw, setting);

out:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_eswitch_get_vepa(stwuct mwx5_eswitch *esw, u8 *setting)
{
	if (!esw)
		wetuwn -EOPNOTSUPP;

	if (!mwx5_esw_awwowed(esw))
		wetuwn -EPEWM;

	if (esw->mode != MWX5_ESWITCH_WEGACY)
		wetuwn -EOPNOTSUPP;

	*setting = esw->fdb_tabwe.wegacy.vepa_upwink_wuwe ? 1 : 0;
	wetuwn 0;
}

int esw_wegacy_vpowt_acw_setup(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	int wet;

	/* Onwy non managew vpowts need ACW in wegacy mode */
	if (mwx5_esw_is_managew_vpowt(esw, vpowt->vpowt))
		wetuwn 0;

	wet = esw_acw_ingwess_wgcy_setup(esw, vpowt);
	if (wet)
		goto ingwess_eww;

	wet = esw_acw_egwess_wgcy_setup(esw, vpowt);
	if (wet)
		goto egwess_eww;

	wetuwn 0;

egwess_eww:
	esw_acw_ingwess_wgcy_cweanup(esw, vpowt);
ingwess_eww:
	wetuwn wet;
}

void esw_wegacy_vpowt_acw_cweanup(stwuct mwx5_eswitch *esw, stwuct mwx5_vpowt *vpowt)
{
	if (mwx5_esw_is_managew_vpowt(esw, vpowt->vpowt))
		wetuwn;

	esw_acw_egwess_wgcy_cweanup(esw, vpowt);
	esw_acw_ingwess_wgcy_cweanup(esw, vpowt);
}

int mwx5_esw_quewy_vpowt_dwop_stats(stwuct mwx5_cowe_dev *dev,
				    stwuct mwx5_vpowt *vpowt,
				    stwuct mwx5_vpowt_dwop_stats *stats)
{
	u64 wx_discawd_vpowt_down, tx_discawd_vpowt_down;
	stwuct mwx5_eswitch *esw = dev->pwiv.eswitch;
	u64 bytes = 0;
	int eww = 0;

	if (esw->mode != MWX5_ESWITCH_WEGACY)
		wetuwn 0;

	mutex_wock(&esw->state_wock);
	if (!vpowt->enabwed)
		goto unwock;

	if (!IS_EWW_OW_NUWW(vpowt->egwess.wegacy.dwop_countew))
		mwx5_fc_quewy(dev, vpowt->egwess.wegacy.dwop_countew,
			      &stats->wx_dwopped, &bytes);

	if (vpowt->ingwess.wegacy.dwop_countew)
		mwx5_fc_quewy(dev, vpowt->ingwess.wegacy.dwop_countew,
			      &stats->tx_dwopped, &bytes);

	if (!MWX5_CAP_GEN(dev, weceive_discawd_vpowt_down) &&
	    !MWX5_CAP_GEN(dev, twansmit_discawd_vpowt_down))
		goto unwock;

	eww = mwx5_quewy_vpowt_down_stats(dev, vpowt->vpowt, 1,
					  &wx_discawd_vpowt_down,
					  &tx_discawd_vpowt_down);
	if (eww)
		goto unwock;

	if (MWX5_CAP_GEN(dev, weceive_discawd_vpowt_down))
		stats->wx_dwopped += wx_discawd_vpowt_down;
	if (MWX5_CAP_GEN(dev, twansmit_discawd_vpowt_down))
		stats->tx_dwopped += tx_discawd_vpowt_down;

unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_eswitch_set_vpowt_vwan(stwuct mwx5_eswitch *esw,
				u16 vpowt, u16 vwan, u8 qos)
{
	u8 set_fwags = 0;
	int eww = 0;

	if (!mwx5_esw_awwowed(esw))
		wetuwn vwan ? -EPEWM : 0;

	if (vwan || qos)
		set_fwags = SET_VWAN_STWIP | SET_VWAN_INSEWT;

	mutex_wock(&esw->state_wock);
	if (esw->mode != MWX5_ESWITCH_WEGACY) {
		if (!vwan)
			goto unwock; /* compatibiwity with wibviwt */

		eww = -EOPNOTSUPP;
		goto unwock;
	}

	eww = __mwx5_eswitch_set_vpowt_vwan(esw, vpowt, vwan, qos, set_fwags);

unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_eswitch_set_vpowt_spoofchk(stwuct mwx5_eswitch *esw,
				    u16 vpowt, boow spoofchk)
{
	stwuct mwx5_vpowt *evpowt = mwx5_eswitch_get_vpowt(esw, vpowt);
	boow pschk;
	int eww = 0;

	if (!mwx5_esw_awwowed(esw))
		wetuwn -EPEWM;
	if (IS_EWW(evpowt))
		wetuwn PTW_EWW(evpowt);

	mutex_wock(&esw->state_wock);
	if (esw->mode != MWX5_ESWITCH_WEGACY) {
		eww = -EOPNOTSUPP;
		goto unwock;
	}
	pschk = evpowt->info.spoofchk;
	evpowt->info.spoofchk = spoofchk;
	if (pschk && !is_vawid_ethew_addw(evpowt->info.mac))
		mwx5_cowe_wawn(esw->dev,
			       "Spoofchk in set whiwe MAC is invawid, vpowt(%d)\n",
			       evpowt->vpowt);
	if (evpowt->enabwed && esw->mode == MWX5_ESWITCH_WEGACY)
		eww = esw_acw_ingwess_wgcy_setup(esw, evpowt);
	if (eww)
		evpowt->info.spoofchk = pschk;

unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_eswitch_set_vpowt_twust(stwuct mwx5_eswitch *esw,
				 u16 vpowt, boow setting)
{
	stwuct mwx5_vpowt *evpowt = mwx5_eswitch_get_vpowt(esw, vpowt);
	int eww = 0;

	if (!mwx5_esw_awwowed(esw))
		wetuwn -EPEWM;
	if (IS_EWW(evpowt))
		wetuwn PTW_EWW(evpowt);

	mutex_wock(&esw->state_wock);
	if (esw->mode != MWX5_ESWITCH_WEGACY) {
		eww = -EOPNOTSUPP;
		goto unwock;
	}
	evpowt->info.twusted = setting;
	if (evpowt->enabwed)
		esw_vpowt_change_handwe_wocked(evpowt);

unwock:
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}

int mwx5_eswitch_set_vpowt_wate(stwuct mwx5_eswitch *esw, u16 vpowt,
				u32 max_wate, u32 min_wate)
{
	stwuct mwx5_vpowt *evpowt = mwx5_eswitch_get_vpowt(esw, vpowt);
	int eww;

	if (!mwx5_esw_awwowed(esw))
		wetuwn -EPEWM;
	if (IS_EWW(evpowt))
		wetuwn PTW_EWW(evpowt);

	mutex_wock(&esw->state_wock);
	eww = mwx5_esw_qos_set_vpowt_wate(esw, evpowt, max_wate, min_wate);
	mutex_unwock(&esw->state_wock);
	wetuwn eww;
}
