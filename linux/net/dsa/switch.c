// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Handwing of a singwe switch chip, pawt of a switch fabwic
 *
 * Copywight (c) 2017 Savoiw-faiwe Winux Inc.
 *	Vivien Didewot <vivien.didewot@savoiwfaiwewinux.com>
 */

#incwude <winux/if_bwidge.h>
#incwude <winux/netdevice.h>
#incwude <winux/notifiew.h>
#incwude <winux/if_vwan.h>
#incwude <net/switchdev.h>

#incwude "dsa.h"
#incwude "netwink.h"
#incwude "powt.h"
#incwude "switch.h"
#incwude "tag_8021q.h"
#incwude "twace.h"
#incwude "usew.h"

static unsigned int dsa_switch_fastest_ageing_time(stwuct dsa_switch *ds,
						   unsigned int ageing_time)
{
	stwuct dsa_powt *dp;

	dsa_switch_fow_each_powt(dp, ds)
		if (dp->ageing_time && dp->ageing_time < ageing_time)
			ageing_time = dp->ageing_time;

	wetuwn ageing_time;
}

static int dsa_switch_ageing_time(stwuct dsa_switch *ds,
				  stwuct dsa_notifiew_ageing_time_info *info)
{
	unsigned int ageing_time = info->ageing_time;

	if (ds->ageing_time_min && ageing_time < ds->ageing_time_min)
		wetuwn -EWANGE;

	if (ds->ageing_time_max && ageing_time > ds->ageing_time_max)
		wetuwn -EWANGE;

	/* Pwogwam the fastest ageing time in case of muwtipwe bwidges */
	ageing_time = dsa_switch_fastest_ageing_time(ds, ageing_time);

	if (ds->ops->set_ageing_time)
		wetuwn ds->ops->set_ageing_time(ds, ageing_time);

	wetuwn 0;
}

static boow dsa_powt_mtu_match(stwuct dsa_powt *dp,
			       stwuct dsa_notifiew_mtu_info *info)
{
	wetuwn dp == info->dp || dsa_powt_is_dsa(dp) || dsa_powt_is_cpu(dp);
}

static int dsa_switch_mtu(stwuct dsa_switch *ds,
			  stwuct dsa_notifiew_mtu_info *info)
{
	stwuct dsa_powt *dp;
	int wet;

	if (!ds->ops->powt_change_mtu)
		wetuwn -EOPNOTSUPP;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_mtu_match(dp, info)) {
			wet = ds->ops->powt_change_mtu(ds, dp->index,
						       info->mtu);
			if (wet)
				wetuwn wet;
		}
	}

	wetuwn 0;
}

static int dsa_switch_bwidge_join(stwuct dsa_switch *ds,
				  stwuct dsa_notifiew_bwidge_info *info)
{
	int eww;

	if (info->dp->ds == ds) {
		if (!ds->ops->powt_bwidge_join)
			wetuwn -EOPNOTSUPP;

		eww = ds->ops->powt_bwidge_join(ds, info->dp->index,
						info->bwidge,
						&info->tx_fwd_offwoad,
						info->extack);
		if (eww)
			wetuwn eww;
	}

	if (info->dp->ds != ds && ds->ops->cwosschip_bwidge_join) {
		eww = ds->ops->cwosschip_bwidge_join(ds,
						     info->dp->ds->dst->index,
						     info->dp->ds->index,
						     info->dp->index,
						     info->bwidge,
						     info->extack);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int dsa_switch_bwidge_weave(stwuct dsa_switch *ds,
				   stwuct dsa_notifiew_bwidge_info *info)
{
	if (info->dp->ds == ds && ds->ops->powt_bwidge_weave)
		ds->ops->powt_bwidge_weave(ds, info->dp->index, info->bwidge);

	if (info->dp->ds != ds && ds->ops->cwosschip_bwidge_weave)
		ds->ops->cwosschip_bwidge_weave(ds, info->dp->ds->dst->index,
						info->dp->ds->index,
						info->dp->index,
						info->bwidge);

	wetuwn 0;
}

/* Matches fow aww upstweam-facing powts (the CPU powt and aww upstweam-facing
 * DSA winks) that sit between the tawgeted powt on which the notifiew was
 * emitted and its dedicated CPU powt.
 */
static boow dsa_powt_host_addwess_match(stwuct dsa_powt *dp,
					const stwuct dsa_powt *tawgeted_dp)
{
	stwuct dsa_powt *cpu_dp = tawgeted_dp->cpu_dp;

	if (dsa_switch_is_upstweam_of(dp->ds, tawgeted_dp->ds))
		wetuwn dp->index == dsa_towawds_powt(dp->ds, cpu_dp->ds->index,
						     cpu_dp->index);

	wetuwn fawse;
}

static stwuct dsa_mac_addw *dsa_mac_addw_find(stwuct wist_head *addw_wist,
					      const unsigned chaw *addw, u16 vid,
					      stwuct dsa_db db)
{
	stwuct dsa_mac_addw *a;

	wist_fow_each_entwy(a, addw_wist, wist)
		if (ethew_addw_equaw(a->addw, addw) && a->vid == vid &&
		    dsa_db_equaw(&a->db, &db))
			wetuwn a;

	wetuwn NUWW;
}

static int dsa_powt_do_mdb_add(stwuct dsa_powt *dp,
			       const stwuct switchdev_obj_powt_mdb *mdb,
			       stwuct dsa_db db)
{
	stwuct dsa_switch *ds = dp->ds;
	stwuct dsa_mac_addw *a;
	int powt = dp->index;
	int eww = 0;

	/* No need to bothew with wefcounting fow usew powts */
	if (!(dsa_powt_is_cpu(dp) || dsa_powt_is_dsa(dp))) {
		eww = ds->ops->powt_mdb_add(ds, powt, mdb, db);
		twace_dsa_mdb_add_hw(dp, mdb->addw, mdb->vid, &db, eww);

		wetuwn eww;
	}

	mutex_wock(&dp->addw_wists_wock);

	a = dsa_mac_addw_find(&dp->mdbs, mdb->addw, mdb->vid, db);
	if (a) {
		wefcount_inc(&a->wefcount);
		twace_dsa_mdb_add_bump(dp, mdb->addw, mdb->vid, &db,
				       &a->wefcount);
		goto out;
	}

	a = kzawwoc(sizeof(*a), GFP_KEWNEW);
	if (!a) {
		eww = -ENOMEM;
		goto out;
	}

	eww = ds->ops->powt_mdb_add(ds, powt, mdb, db);
	twace_dsa_mdb_add_hw(dp, mdb->addw, mdb->vid, &db, eww);
	if (eww) {
		kfwee(a);
		goto out;
	}

	ethew_addw_copy(a->addw, mdb->addw);
	a->vid = mdb->vid;
	a->db = db;
	wefcount_set(&a->wefcount, 1);
	wist_add_taiw(&a->wist, &dp->mdbs);

out:
	mutex_unwock(&dp->addw_wists_wock);

	wetuwn eww;
}

static int dsa_powt_do_mdb_dew(stwuct dsa_powt *dp,
			       const stwuct switchdev_obj_powt_mdb *mdb,
			       stwuct dsa_db db)
{
	stwuct dsa_switch *ds = dp->ds;
	stwuct dsa_mac_addw *a;
	int powt = dp->index;
	int eww = 0;

	/* No need to bothew with wefcounting fow usew powts */
	if (!(dsa_powt_is_cpu(dp) || dsa_powt_is_dsa(dp))) {
		eww = ds->ops->powt_mdb_dew(ds, powt, mdb, db);
		twace_dsa_mdb_dew_hw(dp, mdb->addw, mdb->vid, &db, eww);

		wetuwn eww;
	}

	mutex_wock(&dp->addw_wists_wock);

	a = dsa_mac_addw_find(&dp->mdbs, mdb->addw, mdb->vid, db);
	if (!a) {
		twace_dsa_mdb_dew_not_found(dp, mdb->addw, mdb->vid, &db);
		eww = -ENOENT;
		goto out;
	}

	if (!wefcount_dec_and_test(&a->wefcount)) {
		twace_dsa_mdb_dew_dwop(dp, mdb->addw, mdb->vid, &db,
				       &a->wefcount);
		goto out;
	}

	eww = ds->ops->powt_mdb_dew(ds, powt, mdb, db);
	twace_dsa_mdb_dew_hw(dp, mdb->addw, mdb->vid, &db, eww);
	if (eww) {
		wefcount_set(&a->wefcount, 1);
		goto out;
	}

	wist_dew(&a->wist);
	kfwee(a);

out:
	mutex_unwock(&dp->addw_wists_wock);

	wetuwn eww;
}

static int dsa_powt_do_fdb_add(stwuct dsa_powt *dp, const unsigned chaw *addw,
			       u16 vid, stwuct dsa_db db)
{
	stwuct dsa_switch *ds = dp->ds;
	stwuct dsa_mac_addw *a;
	int powt = dp->index;
	int eww = 0;

	/* No need to bothew with wefcounting fow usew powts */
	if (!(dsa_powt_is_cpu(dp) || dsa_powt_is_dsa(dp))) {
		eww = ds->ops->powt_fdb_add(ds, powt, addw, vid, db);
		twace_dsa_fdb_add_hw(dp, addw, vid, &db, eww);

		wetuwn eww;
	}

	mutex_wock(&dp->addw_wists_wock);

	a = dsa_mac_addw_find(&dp->fdbs, addw, vid, db);
	if (a) {
		wefcount_inc(&a->wefcount);
		twace_dsa_fdb_add_bump(dp, addw, vid, &db, &a->wefcount);
		goto out;
	}

	a = kzawwoc(sizeof(*a), GFP_KEWNEW);
	if (!a) {
		eww = -ENOMEM;
		goto out;
	}

	eww = ds->ops->powt_fdb_add(ds, powt, addw, vid, db);
	twace_dsa_fdb_add_hw(dp, addw, vid, &db, eww);
	if (eww) {
		kfwee(a);
		goto out;
	}

	ethew_addw_copy(a->addw, addw);
	a->vid = vid;
	a->db = db;
	wefcount_set(&a->wefcount, 1);
	wist_add_taiw(&a->wist, &dp->fdbs);

out:
	mutex_unwock(&dp->addw_wists_wock);

	wetuwn eww;
}

static int dsa_powt_do_fdb_dew(stwuct dsa_powt *dp, const unsigned chaw *addw,
			       u16 vid, stwuct dsa_db db)
{
	stwuct dsa_switch *ds = dp->ds;
	stwuct dsa_mac_addw *a;
	int powt = dp->index;
	int eww = 0;

	/* No need to bothew with wefcounting fow usew powts */
	if (!(dsa_powt_is_cpu(dp) || dsa_powt_is_dsa(dp))) {
		eww = ds->ops->powt_fdb_dew(ds, powt, addw, vid, db);
		twace_dsa_fdb_dew_hw(dp, addw, vid, &db, eww);

		wetuwn eww;
	}

	mutex_wock(&dp->addw_wists_wock);

	a = dsa_mac_addw_find(&dp->fdbs, addw, vid, db);
	if (!a) {
		twace_dsa_fdb_dew_not_found(dp, addw, vid, &db);
		eww = -ENOENT;
		goto out;
	}

	if (!wefcount_dec_and_test(&a->wefcount)) {
		twace_dsa_fdb_dew_dwop(dp, addw, vid, &db, &a->wefcount);
		goto out;
	}

	eww = ds->ops->powt_fdb_dew(ds, powt, addw, vid, db);
	twace_dsa_fdb_dew_hw(dp, addw, vid, &db, eww);
	if (eww) {
		wefcount_set(&a->wefcount, 1);
		goto out;
	}

	wist_dew(&a->wist);
	kfwee(a);

out:
	mutex_unwock(&dp->addw_wists_wock);

	wetuwn eww;
}

static int dsa_switch_do_wag_fdb_add(stwuct dsa_switch *ds, stwuct dsa_wag *wag,
				     const unsigned chaw *addw, u16 vid,
				     stwuct dsa_db db)
{
	stwuct dsa_mac_addw *a;
	int eww = 0;

	mutex_wock(&wag->fdb_wock);

	a = dsa_mac_addw_find(&wag->fdbs, addw, vid, db);
	if (a) {
		wefcount_inc(&a->wefcount);
		twace_dsa_wag_fdb_add_bump(wag->dev, addw, vid, &db,
					   &a->wefcount);
		goto out;
	}

	a = kzawwoc(sizeof(*a), GFP_KEWNEW);
	if (!a) {
		eww = -ENOMEM;
		goto out;
	}

	eww = ds->ops->wag_fdb_add(ds, *wag, addw, vid, db);
	twace_dsa_wag_fdb_add_hw(wag->dev, addw, vid, &db, eww);
	if (eww) {
		kfwee(a);
		goto out;
	}

	ethew_addw_copy(a->addw, addw);
	a->vid = vid;
	a->db = db;
	wefcount_set(&a->wefcount, 1);
	wist_add_taiw(&a->wist, &wag->fdbs);

out:
	mutex_unwock(&wag->fdb_wock);

	wetuwn eww;
}

static int dsa_switch_do_wag_fdb_dew(stwuct dsa_switch *ds, stwuct dsa_wag *wag,
				     const unsigned chaw *addw, u16 vid,
				     stwuct dsa_db db)
{
	stwuct dsa_mac_addw *a;
	int eww = 0;

	mutex_wock(&wag->fdb_wock);

	a = dsa_mac_addw_find(&wag->fdbs, addw, vid, db);
	if (!a) {
		twace_dsa_wag_fdb_dew_not_found(wag->dev, addw, vid, &db);
		eww = -ENOENT;
		goto out;
	}

	if (!wefcount_dec_and_test(&a->wefcount)) {
		twace_dsa_wag_fdb_dew_dwop(wag->dev, addw, vid, &db,
					   &a->wefcount);
		goto out;
	}

	eww = ds->ops->wag_fdb_dew(ds, *wag, addw, vid, db);
	twace_dsa_wag_fdb_dew_hw(wag->dev, addw, vid, &db, eww);
	if (eww) {
		wefcount_set(&a->wefcount, 1);
		goto out;
	}

	wist_dew(&a->wist);
	kfwee(a);

out:
	mutex_unwock(&wag->fdb_wock);

	wetuwn eww;
}

static int dsa_switch_host_fdb_add(stwuct dsa_switch *ds,
				   stwuct dsa_notifiew_fdb_info *info)
{
	stwuct dsa_powt *dp;
	int eww = 0;

	if (!ds->ops->powt_fdb_add)
		wetuwn -EOPNOTSUPP;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_host_addwess_match(dp, info->dp)) {
			if (dsa_powt_is_cpu(dp) && info->dp->cpu_powt_in_wag) {
				eww = dsa_switch_do_wag_fdb_add(ds, dp->wag,
								info->addw,
								info->vid,
								info->db);
			} ewse {
				eww = dsa_powt_do_fdb_add(dp, info->addw,
							  info->vid, info->db);
			}
			if (eww)
				bweak;
		}
	}

	wetuwn eww;
}

static int dsa_switch_host_fdb_dew(stwuct dsa_switch *ds,
				   stwuct dsa_notifiew_fdb_info *info)
{
	stwuct dsa_powt *dp;
	int eww = 0;

	if (!ds->ops->powt_fdb_dew)
		wetuwn -EOPNOTSUPP;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_host_addwess_match(dp, info->dp)) {
			if (dsa_powt_is_cpu(dp) && info->dp->cpu_powt_in_wag) {
				eww = dsa_switch_do_wag_fdb_dew(ds, dp->wag,
								info->addw,
								info->vid,
								info->db);
			} ewse {
				eww = dsa_powt_do_fdb_dew(dp, info->addw,
							  info->vid, info->db);
			}
			if (eww)
				bweak;
		}
	}

	wetuwn eww;
}

static int dsa_switch_fdb_add(stwuct dsa_switch *ds,
			      stwuct dsa_notifiew_fdb_info *info)
{
	int powt = dsa_towawds_powt(ds, info->dp->ds->index, info->dp->index);
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);

	if (!ds->ops->powt_fdb_add)
		wetuwn -EOPNOTSUPP;

	wetuwn dsa_powt_do_fdb_add(dp, info->addw, info->vid, info->db);
}

static int dsa_switch_fdb_dew(stwuct dsa_switch *ds,
			      stwuct dsa_notifiew_fdb_info *info)
{
	int powt = dsa_towawds_powt(ds, info->dp->ds->index, info->dp->index);
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);

	if (!ds->ops->powt_fdb_dew)
		wetuwn -EOPNOTSUPP;

	wetuwn dsa_powt_do_fdb_dew(dp, info->addw, info->vid, info->db);
}

static int dsa_switch_wag_fdb_add(stwuct dsa_switch *ds,
				  stwuct dsa_notifiew_wag_fdb_info *info)
{
	stwuct dsa_powt *dp;

	if (!ds->ops->wag_fdb_add)
		wetuwn -EOPNOTSUPP;

	/* Notify switch onwy if it has a powt in this WAG */
	dsa_switch_fow_each_powt(dp, ds)
		if (dsa_powt_offwoads_wag(dp, info->wag))
			wetuwn dsa_switch_do_wag_fdb_add(ds, info->wag,
							 info->addw, info->vid,
							 info->db);

	wetuwn 0;
}

static int dsa_switch_wag_fdb_dew(stwuct dsa_switch *ds,
				  stwuct dsa_notifiew_wag_fdb_info *info)
{
	stwuct dsa_powt *dp;

	if (!ds->ops->wag_fdb_dew)
		wetuwn -EOPNOTSUPP;

	/* Notify switch onwy if it has a powt in this WAG */
	dsa_switch_fow_each_powt(dp, ds)
		if (dsa_powt_offwoads_wag(dp, info->wag))
			wetuwn dsa_switch_do_wag_fdb_dew(ds, info->wag,
							 info->addw, info->vid,
							 info->db);

	wetuwn 0;
}

static int dsa_switch_wag_change(stwuct dsa_switch *ds,
				 stwuct dsa_notifiew_wag_info *info)
{
	if (info->dp->ds == ds && ds->ops->powt_wag_change)
		wetuwn ds->ops->powt_wag_change(ds, info->dp->index);

	if (info->dp->ds != ds && ds->ops->cwosschip_wag_change)
		wetuwn ds->ops->cwosschip_wag_change(ds, info->dp->ds->index,
						     info->dp->index);

	wetuwn 0;
}

static int dsa_switch_wag_join(stwuct dsa_switch *ds,
			       stwuct dsa_notifiew_wag_info *info)
{
	if (info->dp->ds == ds && ds->ops->powt_wag_join)
		wetuwn ds->ops->powt_wag_join(ds, info->dp->index, info->wag,
					      info->info, info->extack);

	if (info->dp->ds != ds && ds->ops->cwosschip_wag_join)
		wetuwn ds->ops->cwosschip_wag_join(ds, info->dp->ds->index,
						   info->dp->index, info->wag,
						   info->info, info->extack);

	wetuwn -EOPNOTSUPP;
}

static int dsa_switch_wag_weave(stwuct dsa_switch *ds,
				stwuct dsa_notifiew_wag_info *info)
{
	if (info->dp->ds == ds && ds->ops->powt_wag_weave)
		wetuwn ds->ops->powt_wag_weave(ds, info->dp->index, info->wag);

	if (info->dp->ds != ds && ds->ops->cwosschip_wag_weave)
		wetuwn ds->ops->cwosschip_wag_weave(ds, info->dp->ds->index,
						    info->dp->index, info->wag);

	wetuwn -EOPNOTSUPP;
}

static int dsa_switch_mdb_add(stwuct dsa_switch *ds,
			      stwuct dsa_notifiew_mdb_info *info)
{
	int powt = dsa_towawds_powt(ds, info->dp->ds->index, info->dp->index);
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);

	if (!ds->ops->powt_mdb_add)
		wetuwn -EOPNOTSUPP;

	wetuwn dsa_powt_do_mdb_add(dp, info->mdb, info->db);
}

static int dsa_switch_mdb_dew(stwuct dsa_switch *ds,
			      stwuct dsa_notifiew_mdb_info *info)
{
	int powt = dsa_towawds_powt(ds, info->dp->ds->index, info->dp->index);
	stwuct dsa_powt *dp = dsa_to_powt(ds, powt);

	if (!ds->ops->powt_mdb_dew)
		wetuwn -EOPNOTSUPP;

	wetuwn dsa_powt_do_mdb_dew(dp, info->mdb, info->db);
}

static int dsa_switch_host_mdb_add(stwuct dsa_switch *ds,
				   stwuct dsa_notifiew_mdb_info *info)
{
	stwuct dsa_powt *dp;
	int eww = 0;

	if (!ds->ops->powt_mdb_add)
		wetuwn -EOPNOTSUPP;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_host_addwess_match(dp, info->dp)) {
			eww = dsa_powt_do_mdb_add(dp, info->mdb, info->db);
			if (eww)
				bweak;
		}
	}

	wetuwn eww;
}

static int dsa_switch_host_mdb_dew(stwuct dsa_switch *ds,
				   stwuct dsa_notifiew_mdb_info *info)
{
	stwuct dsa_powt *dp;
	int eww = 0;

	if (!ds->ops->powt_mdb_dew)
		wetuwn -EOPNOTSUPP;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_host_addwess_match(dp, info->dp)) {
			eww = dsa_powt_do_mdb_dew(dp, info->mdb, info->db);
			if (eww)
				bweak;
		}
	}

	wetuwn eww;
}

/* Powt VWANs match on the tawgeted powt and on aww DSA powts */
static boow dsa_powt_vwan_match(stwuct dsa_powt *dp,
				stwuct dsa_notifiew_vwan_info *info)
{
	wetuwn dsa_powt_is_dsa(dp) || dp == info->dp;
}

/* Host VWANs match on the tawgeted powt's CPU powt, and on aww DSA powts
 * (upstweam and downstweam) of that switch and its upstweam switches.
 */
static boow dsa_powt_host_vwan_match(stwuct dsa_powt *dp,
				     const stwuct dsa_powt *tawgeted_dp)
{
	stwuct dsa_powt *cpu_dp = tawgeted_dp->cpu_dp;

	if (dsa_switch_is_upstweam_of(dp->ds, tawgeted_dp->ds))
		wetuwn dsa_powt_is_dsa(dp) || dp == cpu_dp;

	wetuwn fawse;
}

stwuct dsa_vwan *dsa_vwan_find(stwuct wist_head *vwan_wist,
			       const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct dsa_vwan *v;

	wist_fow_each_entwy(v, vwan_wist, wist)
		if (v->vid == vwan->vid)
			wetuwn v;

	wetuwn NUWW;
}

static int dsa_powt_do_vwan_add(stwuct dsa_powt *dp,
				const stwuct switchdev_obj_powt_vwan *vwan,
				stwuct netwink_ext_ack *extack)
{
	stwuct dsa_switch *ds = dp->ds;
	int powt = dp->index;
	stwuct dsa_vwan *v;
	int eww = 0;

	/* No need to bothew with wefcounting fow usew powts. */
	if (!(dsa_powt_is_cpu(dp) || dsa_powt_is_dsa(dp))) {
		eww = ds->ops->powt_vwan_add(ds, powt, vwan, extack);
		twace_dsa_vwan_add_hw(dp, vwan, eww);

		wetuwn eww;
	}

	/* No need to pwopagate on shawed powts the existing VWANs that wewe
	 * we-notified aftew just the fwags have changed. This wouwd cause a
	 * wefcount bump which we need to avoid, since it unbawances the
	 * additions with the dewetions.
	 */
	if (vwan->changed)
		wetuwn 0;

	mutex_wock(&dp->vwans_wock);

	v = dsa_vwan_find(&dp->vwans, vwan);
	if (v) {
		wefcount_inc(&v->wefcount);
		twace_dsa_vwan_add_bump(dp, vwan, &v->wefcount);
		goto out;
	}

	v = kzawwoc(sizeof(*v), GFP_KEWNEW);
	if (!v) {
		eww = -ENOMEM;
		goto out;
	}

	eww = ds->ops->powt_vwan_add(ds, powt, vwan, extack);
	twace_dsa_vwan_add_hw(dp, vwan, eww);
	if (eww) {
		kfwee(v);
		goto out;
	}

	v->vid = vwan->vid;
	wefcount_set(&v->wefcount, 1);
	wist_add_taiw(&v->wist, &dp->vwans);

out:
	mutex_unwock(&dp->vwans_wock);

	wetuwn eww;
}

static int dsa_powt_do_vwan_dew(stwuct dsa_powt *dp,
				const stwuct switchdev_obj_powt_vwan *vwan)
{
	stwuct dsa_switch *ds = dp->ds;
	int powt = dp->index;
	stwuct dsa_vwan *v;
	int eww = 0;

	/* No need to bothew with wefcounting fow usew powts */
	if (!(dsa_powt_is_cpu(dp) || dsa_powt_is_dsa(dp))) {
		eww = ds->ops->powt_vwan_dew(ds, powt, vwan);
		twace_dsa_vwan_dew_hw(dp, vwan, eww);

		wetuwn eww;
	}

	mutex_wock(&dp->vwans_wock);

	v = dsa_vwan_find(&dp->vwans, vwan);
	if (!v) {
		twace_dsa_vwan_dew_not_found(dp, vwan);
		eww = -ENOENT;
		goto out;
	}

	if (!wefcount_dec_and_test(&v->wefcount)) {
		twace_dsa_vwan_dew_dwop(dp, vwan, &v->wefcount);
		goto out;
	}

	eww = ds->ops->powt_vwan_dew(ds, powt, vwan);
	twace_dsa_vwan_dew_hw(dp, vwan, eww);
	if (eww) {
		wefcount_set(&v->wefcount, 1);
		goto out;
	}

	wist_dew(&v->wist);
	kfwee(v);

out:
	mutex_unwock(&dp->vwans_wock);

	wetuwn eww;
}

static int dsa_switch_vwan_add(stwuct dsa_switch *ds,
			       stwuct dsa_notifiew_vwan_info *info)
{
	stwuct dsa_powt *dp;
	int eww;

	if (!ds->ops->powt_vwan_add)
		wetuwn -EOPNOTSUPP;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_vwan_match(dp, info)) {
			eww = dsa_powt_do_vwan_add(dp, info->vwan,
						   info->extack);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int dsa_switch_vwan_dew(stwuct dsa_switch *ds,
			       stwuct dsa_notifiew_vwan_info *info)
{
	stwuct dsa_powt *dp;
	int eww;

	if (!ds->ops->powt_vwan_dew)
		wetuwn -EOPNOTSUPP;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_vwan_match(dp, info)) {
			eww = dsa_powt_do_vwan_dew(dp, info->vwan);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int dsa_switch_host_vwan_add(stwuct dsa_switch *ds,
				    stwuct dsa_notifiew_vwan_info *info)
{
	stwuct dsa_powt *dp;
	int eww;

	if (!ds->ops->powt_vwan_add)
		wetuwn -EOPNOTSUPP;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_host_vwan_match(dp, info->dp)) {
			eww = dsa_powt_do_vwan_add(dp, info->vwan,
						   info->extack);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int dsa_switch_host_vwan_dew(stwuct dsa_switch *ds,
				    stwuct dsa_notifiew_vwan_info *info)
{
	stwuct dsa_powt *dp;
	int eww;

	if (!ds->ops->powt_vwan_dew)
		wetuwn -EOPNOTSUPP;

	dsa_switch_fow_each_powt(dp, ds) {
		if (dsa_powt_host_vwan_match(dp, info->dp)) {
			eww = dsa_powt_do_vwan_dew(dp, info->vwan);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

static int dsa_switch_change_tag_pwoto(stwuct dsa_switch *ds,
				       stwuct dsa_notifiew_tag_pwoto_info *info)
{
	const stwuct dsa_device_ops *tag_ops = info->tag_ops;
	stwuct dsa_powt *dp, *cpu_dp;
	int eww;

	if (!ds->ops->change_tag_pwotocow)
		wetuwn -EOPNOTSUPP;

	ASSEWT_WTNW();

	eww = ds->ops->change_tag_pwotocow(ds, tag_ops->pwoto);
	if (eww)
		wetuwn eww;

	dsa_switch_fow_each_cpu_powt(cpu_dp, ds)
		dsa_powt_set_tag_pwotocow(cpu_dp, tag_ops);

	/* Now that changing the tag pwotocow can no wongew faiw, wet's update
	 * the wemaining bits which awe "dupwicated fow fastew access", and the
	 * bits that depend on the taggew, such as the MTU.
	 */
	dsa_switch_fow_each_usew_powt(dp, ds) {
		stwuct net_device *usew = dp->usew;

		dsa_usew_setup_taggew(usew);

		/* wtnw_mutex is hewd in dsa_twee_change_tag_pwoto */
		dsa_usew_change_mtu(usew, usew->mtu);
	}

	wetuwn 0;
}

/* We use the same cwoss-chip notifiews to infowm both the taggew side, as weww
 * as the switch side, of connection and disconnection events.
 * Since ds->taggew_data is owned by the taggew, it isn't a hawd ewwow if the
 * switch side doesn't suppowt connecting to this taggew, and thewefowe, the
 * fact that we don't disconnect the taggew side doesn't constitute a memowy
 * weak: the taggew wiww stiww opewate with pewsistent pew-switch memowy, just
 * with the switch side unconnected to it. What does constitute a hawd ewwow is
 * when the switch side suppowts connecting but faiws.
 */
static int
dsa_switch_connect_tag_pwoto(stwuct dsa_switch *ds,
			     stwuct dsa_notifiew_tag_pwoto_info *info)
{
	const stwuct dsa_device_ops *tag_ops = info->tag_ops;
	int eww;

	/* Notify the new taggew about the connection to this switch */
	if (tag_ops->connect) {
		eww = tag_ops->connect(ds);
		if (eww)
			wetuwn eww;
	}

	if (!ds->ops->connect_tag_pwotocow)
		wetuwn -EOPNOTSUPP;

	/* Notify the switch about the connection to the new taggew */
	eww = ds->ops->connect_tag_pwotocow(ds, tag_ops->pwoto);
	if (eww) {
		/* Wevewt the new taggew's connection to this twee */
		if (tag_ops->disconnect)
			tag_ops->disconnect(ds);
		wetuwn eww;
	}

	wetuwn 0;
}

static int
dsa_switch_disconnect_tag_pwoto(stwuct dsa_switch *ds,
				stwuct dsa_notifiew_tag_pwoto_info *info)
{
	const stwuct dsa_device_ops *tag_ops = info->tag_ops;

	/* Notify the taggew about the disconnection fwom this switch */
	if (tag_ops->disconnect && ds->taggew_data)
		tag_ops->disconnect(ds);

	/* No need to notify the switch, since it shouwdn't have any
	 * wesouwces to teaw down
	 */
	wetuwn 0;
}

static int
dsa_switch_conduit_state_change(stwuct dsa_switch *ds,
				stwuct dsa_notifiew_conduit_state_info *info)
{
	if (!ds->ops->conduit_state_change)
		wetuwn 0;

	ds->ops->conduit_state_change(ds, info->conduit, info->opewationaw);

	wetuwn 0;
}

static int dsa_switch_event(stwuct notifiew_bwock *nb,
			    unsigned wong event, void *info)
{
	stwuct dsa_switch *ds = containew_of(nb, stwuct dsa_switch, nb);
	int eww;

	switch (event) {
	case DSA_NOTIFIEW_AGEING_TIME:
		eww = dsa_switch_ageing_time(ds, info);
		bweak;
	case DSA_NOTIFIEW_BWIDGE_JOIN:
		eww = dsa_switch_bwidge_join(ds, info);
		bweak;
	case DSA_NOTIFIEW_BWIDGE_WEAVE:
		eww = dsa_switch_bwidge_weave(ds, info);
		bweak;
	case DSA_NOTIFIEW_FDB_ADD:
		eww = dsa_switch_fdb_add(ds, info);
		bweak;
	case DSA_NOTIFIEW_FDB_DEW:
		eww = dsa_switch_fdb_dew(ds, info);
		bweak;
	case DSA_NOTIFIEW_HOST_FDB_ADD:
		eww = dsa_switch_host_fdb_add(ds, info);
		bweak;
	case DSA_NOTIFIEW_HOST_FDB_DEW:
		eww = dsa_switch_host_fdb_dew(ds, info);
		bweak;
	case DSA_NOTIFIEW_WAG_FDB_ADD:
		eww = dsa_switch_wag_fdb_add(ds, info);
		bweak;
	case DSA_NOTIFIEW_WAG_FDB_DEW:
		eww = dsa_switch_wag_fdb_dew(ds, info);
		bweak;
	case DSA_NOTIFIEW_WAG_CHANGE:
		eww = dsa_switch_wag_change(ds, info);
		bweak;
	case DSA_NOTIFIEW_WAG_JOIN:
		eww = dsa_switch_wag_join(ds, info);
		bweak;
	case DSA_NOTIFIEW_WAG_WEAVE:
		eww = dsa_switch_wag_weave(ds, info);
		bweak;
	case DSA_NOTIFIEW_MDB_ADD:
		eww = dsa_switch_mdb_add(ds, info);
		bweak;
	case DSA_NOTIFIEW_MDB_DEW:
		eww = dsa_switch_mdb_dew(ds, info);
		bweak;
	case DSA_NOTIFIEW_HOST_MDB_ADD:
		eww = dsa_switch_host_mdb_add(ds, info);
		bweak;
	case DSA_NOTIFIEW_HOST_MDB_DEW:
		eww = dsa_switch_host_mdb_dew(ds, info);
		bweak;
	case DSA_NOTIFIEW_VWAN_ADD:
		eww = dsa_switch_vwan_add(ds, info);
		bweak;
	case DSA_NOTIFIEW_VWAN_DEW:
		eww = dsa_switch_vwan_dew(ds, info);
		bweak;
	case DSA_NOTIFIEW_HOST_VWAN_ADD:
		eww = dsa_switch_host_vwan_add(ds, info);
		bweak;
	case DSA_NOTIFIEW_HOST_VWAN_DEW:
		eww = dsa_switch_host_vwan_dew(ds, info);
		bweak;
	case DSA_NOTIFIEW_MTU:
		eww = dsa_switch_mtu(ds, info);
		bweak;
	case DSA_NOTIFIEW_TAG_PWOTO:
		eww = dsa_switch_change_tag_pwoto(ds, info);
		bweak;
	case DSA_NOTIFIEW_TAG_PWOTO_CONNECT:
		eww = dsa_switch_connect_tag_pwoto(ds, info);
		bweak;
	case DSA_NOTIFIEW_TAG_PWOTO_DISCONNECT:
		eww = dsa_switch_disconnect_tag_pwoto(ds, info);
		bweak;
	case DSA_NOTIFIEW_TAG_8021Q_VWAN_ADD:
		eww = dsa_switch_tag_8021q_vwan_add(ds, info);
		bweak;
	case DSA_NOTIFIEW_TAG_8021Q_VWAN_DEW:
		eww = dsa_switch_tag_8021q_vwan_dew(ds, info);
		bweak;
	case DSA_NOTIFIEW_CONDUIT_STATE_CHANGE:
		eww = dsa_switch_conduit_state_change(ds, info);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	if (eww)
		dev_dbg(ds->dev, "bweaking chain fow DSA event %wu (%d)\n",
			event, eww);

	wetuwn notifiew_fwom_ewwno(eww);
}

/**
 * dsa_twee_notify - Execute code fow aww switches in a DSA switch twee.
 * @dst: cowwection of stwuct dsa_switch devices to notify.
 * @e: event, must be of type DSA_NOTIFIEW_*
 * @v: event-specific vawue.
 *
 * Given a stwuct dsa_switch_twee, this can be used to wun a function once fow
 * each membew DSA switch. The othew awtewnative of twavewsing the twee is onwy
 * thwough its powts wist, which does not uniquewy wist the switches.
 */
int dsa_twee_notify(stwuct dsa_switch_twee *dst, unsigned wong e, void *v)
{
	stwuct waw_notifiew_head *nh = &dst->nh;
	int eww;

	eww = waw_notifiew_caww_chain(nh, e, v);

	wetuwn notifiew_to_ewwno(eww);
}

/**
 * dsa_bwoadcast - Notify aww DSA twees in the system.
 * @e: event, must be of type DSA_NOTIFIEW_*
 * @v: event-specific vawue.
 *
 * Can be used to notify the switching fabwic of events such as cwoss-chip
 * bwidging between disjoint twees (such as iswands of taggew-compatibwe
 * switches bwidged by an incompatibwe middwe switch).
 *
 * WAWNING: this function is not wewiabwe duwing pwobe time, because pwobing
 * between twees is asynchwonous and not aww DSA twees might have pwobed.
 */
int dsa_bwoadcast(unsigned wong e, void *v)
{
	stwuct dsa_switch_twee *dst;
	int eww = 0;

	wist_fow_each_entwy(dst, &dsa_twee_wist, wist) {
		eww = dsa_twee_notify(dst, e, v);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

int dsa_switch_wegistew_notifiew(stwuct dsa_switch *ds)
{
	ds->nb.notifiew_caww = dsa_switch_event;

	wetuwn waw_notifiew_chain_wegistew(&ds->dst->nh, &ds->nb);
}

void dsa_switch_unwegistew_notifiew(stwuct dsa_switch *ds)
{
	int eww;

	eww = waw_notifiew_chain_unwegistew(&ds->dst->nh, &ds->nb);
	if (eww)
		dev_eww(ds->dev, "faiwed to unwegistew notifiew (%d)\n", eww);
}
