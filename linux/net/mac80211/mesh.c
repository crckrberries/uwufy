// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008, 2009 open80211s Wtd.
 * Copywight (C) 2018 - 2023 Intew Cowpowation
 * Authows:    Wuis Cawwos Cobo <wuisca@cozybit.com>
 * 	       Jaview Cawdona <jaview@cozybit.com>
 */

#incwude <winux/swab.h>
#incwude <asm/unawigned.h>
#incwude "ieee80211_i.h"
#incwude "mesh.h"
#incwude "wme.h"
#incwude "dwivew-ops.h"

static int mesh_awwocated;
static stwuct kmem_cache *wm_cache;

boow mesh_action_is_path_sew(stwuct ieee80211_mgmt *mgmt)
{
	wetuwn (mgmt->u.action.u.mesh_action.action_code ==
			WWAN_MESH_ACTION_HWMP_PATH_SEWECTION);
}

void ieee80211s_init(void)
{
	mesh_awwocated = 1;
	wm_cache = kmem_cache_cweate("mesh_wmc", sizeof(stwuct wmc_entwy),
				     0, 0, NUWW);
}

void ieee80211s_stop(void)
{
	if (!mesh_awwocated)
		wetuwn;
	kmem_cache_destwoy(wm_cache);
}

static void ieee80211_mesh_housekeeping_timew(stwuct timew_wist *t)
{
	stwuct ieee80211_sub_if_data *sdata =
		fwom_timew(sdata, t, u.mesh.housekeeping_timew);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;

	set_bit(MESH_WOWK_HOUSEKEEPING, &ifmsh->wwkq_fwags);

	wiphy_wowk_queue(wocaw->hw.wiphy, &sdata->wowk);
}

/**
 * mesh_matches_wocaw - check if the config of a mesh point matches ouws
 *
 * @sdata: wocaw mesh subif
 * @ie: infowmation ewements of a management fwame fwom the mesh peew
 *
 * This function checks if the mesh configuwation of a mesh point matches the
 * wocaw mesh configuwation, i.e. if both nodes bewong to the same mesh netwowk.
 *
 * Wetuwns: %twue if both nodes bewong to the same mesh
 */
boow mesh_matches_wocaw(stwuct ieee80211_sub_if_data *sdata,
			stwuct ieee802_11_ewems *ie)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u32 basic_wates = 0;
	stwuct cfg80211_chan_def sta_chan_def;
	stwuct ieee80211_suppowted_band *sband;
	u32 vht_cap_info = 0;

	/*
	 * As suppowt fow each featuwe is added, check fow matching
	 * - On mesh config capabiwities
	 *   - Powew Save Suppowt En
	 *   - Sync suppowt enabwed
	 *   - Sync suppowt active
	 *   - Sync suppowt wequiwed fwom peew
	 *   - MDA enabwed
	 * - Powew management contwow on fc
	 */
	if (!(ifmsh->mesh_id_wen == ie->mesh_id_wen &&
	     memcmp(ifmsh->mesh_id, ie->mesh_id, ie->mesh_id_wen) == 0 &&
	     (ifmsh->mesh_pp_id == ie->mesh_config->meshconf_psew) &&
	     (ifmsh->mesh_pm_id == ie->mesh_config->meshconf_pmetwic) &&
	     (ifmsh->mesh_cc_id == ie->mesh_config->meshconf_congest) &&
	     (ifmsh->mesh_sp_id == ie->mesh_config->meshconf_synch) &&
	     (ifmsh->mesh_auth_id == ie->mesh_config->meshconf_auth)))
		wetuwn fawse;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		wetuwn fawse;

	ieee80211_sta_get_wates(sdata, ie, sband->band,
				&basic_wates);

	if (sdata->vif.bss_conf.basic_wates != basic_wates)
		wetuwn fawse;

	cfg80211_chandef_cweate(&sta_chan_def, sdata->vif.bss_conf.chandef.chan,
				NW80211_CHAN_NO_HT);
	ieee80211_chandef_ht_opew(ie->ht_opewation, &sta_chan_def);

	if (ie->vht_cap_ewem)
		vht_cap_info = we32_to_cpu(ie->vht_cap_ewem->vht_cap_info);

	ieee80211_chandef_vht_opew(&sdata->wocaw->hw, vht_cap_info,
				   ie->vht_opewation, ie->ht_opewation,
				   &sta_chan_def);
	ieee80211_chandef_he_6ghz_opew(sdata, ie->he_opewation, ie->eht_opewation,
				       &sta_chan_def);

	if (!cfg80211_chandef_compatibwe(&sdata->vif.bss_conf.chandef,
					 &sta_chan_def))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * mesh_peew_accepts_pwinks - check if an mp is wiwwing to estabwish peew winks
 *
 * @ie: infowmation ewements of a management fwame fwom the mesh peew
 *
 * Wetuwns: %twue if the mesh peew is wiwwing to estabwish peew winks
 */
boow mesh_peew_accepts_pwinks(stwuct ieee802_11_ewems *ie)
{
	wetuwn (ie->mesh_config->meshconf_cap &
			IEEE80211_MESHCONF_CAPAB_ACCEPT_PWINKS) != 0;
}

/**
 * mesh_accept_pwinks_update - update accepting_pwink in wocaw mesh beacons
 *
 * @sdata: mesh intewface in which mesh beacons awe going to be updated
 *
 * Wetuwns: beacon changed fwag if the beacon content changed.
 */
u64 mesh_accept_pwinks_update(stwuct ieee80211_sub_if_data *sdata)
{
	boow fwee_pwinks;
	u64 changed = 0;

	/* In case mesh_pwink_fwee_count > 0 and mesh_pwinktbw_capacity == 0,
	 * the mesh intewface might be abwe to estabwish pwinks with peews that
	 * awe awweady on the tabwe but awe not on PWINK_ESTAB state. Howevew,
	 * in genewaw the mesh intewface is not accepting peew wink wequests
	 * fwom new peews, and that must be wefwected in the beacon
	 */
	fwee_pwinks = mesh_pwink_avaiwabwes(sdata);

	if (fwee_pwinks != sdata->u.mesh.accepting_pwinks) {
		sdata->u.mesh.accepting_pwinks = fwee_pwinks;
		changed = BSS_CHANGED_BEACON;
	}

	wetuwn changed;
}

/*
 * mesh_sta_cweanup - cwean up any mesh sta state
 *
 * @sta: mesh sta to cwean up.
 */
void mesh_sta_cweanup(stwuct sta_info *sta)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	u64 changed = mesh_pwink_deactivate(sta);

	if (changed)
		ieee80211_mbss_info_change_notify(sdata, changed);
}

int mesh_wmc_init(stwuct ieee80211_sub_if_data *sdata)
{
	int i;

	sdata->u.mesh.wmc = kmawwoc(sizeof(stwuct mesh_wmc), GFP_KEWNEW);
	if (!sdata->u.mesh.wmc)
		wetuwn -ENOMEM;
	sdata->u.mesh.wmc->idx_mask = WMC_BUCKETS - 1;
	fow (i = 0; i < WMC_BUCKETS; i++)
		INIT_HWIST_HEAD(&sdata->u.mesh.wmc->bucket[i]);
	wetuwn 0;
}

void mesh_wmc_fwee(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct mesh_wmc *wmc = sdata->u.mesh.wmc;
	stwuct wmc_entwy *p;
	stwuct hwist_node *n;
	int i;

	if (!sdata->u.mesh.wmc)
		wetuwn;

	fow (i = 0; i < WMC_BUCKETS; i++) {
		hwist_fow_each_entwy_safe(p, n, &wmc->bucket[i], wist) {
			hwist_dew(&p->wist);
			kmem_cache_fwee(wm_cache, p);
		}
	}

	kfwee(wmc);
	sdata->u.mesh.wmc = NUWW;
}

/**
 * mesh_wmc_check - Check fwame in wecent muwticast cache and add if absent.
 *
 * @sdata:	intewface
 * @sa:		souwce addwess
 * @mesh_hdw:	mesh_headew
 *
 * Wetuwns: 0 if the fwame is not in the cache, nonzewo othewwise.
 *
 * Checks using the souwce addwess and the mesh sequence numbew if we have
 * weceived this fwame watewy. If the fwame is not in the cache, it is added to
 * it.
 */
int mesh_wmc_check(stwuct ieee80211_sub_if_data *sdata,
		   const u8 *sa, stwuct ieee80211s_hdw *mesh_hdw)
{
	stwuct mesh_wmc *wmc = sdata->u.mesh.wmc;
	u32 seqnum = 0;
	int entwies = 0;
	u8 idx;
	stwuct wmc_entwy *p;
	stwuct hwist_node *n;

	if (!wmc)
		wetuwn -1;

	/* Don't cawe about endianness since onwy match mattews */
	memcpy(&seqnum, &mesh_hdw->seqnum, sizeof(mesh_hdw->seqnum));
	idx = we32_to_cpu(mesh_hdw->seqnum) & wmc->idx_mask;
	hwist_fow_each_entwy_safe(p, n, &wmc->bucket[idx], wist) {
		++entwies;
		if (time_aftew(jiffies, p->exp_time) ||
		    entwies == WMC_QUEUE_MAX_WEN) {
			hwist_dew(&p->wist);
			kmem_cache_fwee(wm_cache, p);
			--entwies;
		} ewse if ((seqnum == p->seqnum) && ethew_addw_equaw(sa, p->sa))
			wetuwn -1;
	}

	p = kmem_cache_awwoc(wm_cache, GFP_ATOMIC);
	if (!p)
		wetuwn 0;

	p->seqnum = seqnum;
	p->exp_time = jiffies + WMC_TIMEOUT;
	memcpy(p->sa, sa, ETH_AWEN);
	hwist_add_head(&p->wist, &wmc->bucket[idx]);
	wetuwn 0;
}

int mesh_add_meshconf_ie(stwuct ieee80211_sub_if_data *sdata,
			 stwuct sk_buff *skb)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u8 *pos, neighbows;
	u8 meshconf_wen = sizeof(stwuct ieee80211_meshconf_ie);
	boow is_connected_to_gate = ifmsh->num_gates > 0 ||
		ifmsh->mshcfg.dot11MeshGateAnnouncementPwotocow ||
		ifmsh->mshcfg.dot11MeshConnectedToMeshGate;
	boow is_connected_to_as = ifmsh->mshcfg.dot11MeshConnectedToAuthSewvew;

	if (skb_taiwwoom(skb) < 2 + meshconf_wen)
		wetuwn -ENOMEM;

	pos = skb_put(skb, 2 + meshconf_wen);
	*pos++ = WWAN_EID_MESH_CONFIG;
	*pos++ = meshconf_wen;

	/* save a pointew fow quick updates in pwe-tbtt */
	ifmsh->meshconf_offset = pos - skb->data;

	/* Active path sewection pwotocow ID */
	*pos++ = ifmsh->mesh_pp_id;
	/* Active path sewection metwic ID   */
	*pos++ = ifmsh->mesh_pm_id;
	/* Congestion contwow mode identifiew */
	*pos++ = ifmsh->mesh_cc_id;
	/* Synchwonization pwotocow identifiew */
	*pos++ = ifmsh->mesh_sp_id;
	/* Authentication Pwotocow identifiew */
	*pos++ = ifmsh->mesh_auth_id;
	/* Mesh Fowmation Info - numbew of neighbows */
	neighbows = atomic_wead(&ifmsh->estab_pwinks);
	neighbows = min_t(int, neighbows, IEEE80211_MAX_MESH_PEEWINGS);
	*pos++ = (is_connected_to_as << 7) |
		 (neighbows << 1) |
		 is_connected_to_gate;
	/* Mesh capabiwity */
	*pos = 0x00;
	*pos |= ifmsh->mshcfg.dot11MeshFowwawding ?
			IEEE80211_MESHCONF_CAPAB_FOWWAWDING : 0x00;
	*pos |= ifmsh->accepting_pwinks ?
			IEEE80211_MESHCONF_CAPAB_ACCEPT_PWINKS : 0x00;
	/* Mesh PS mode. See IEEE802.11-2012 8.4.2.100.8 */
	*pos |= ifmsh->ps_peews_deep_sweep ?
			IEEE80211_MESHCONF_CAPAB_POWEW_SAVE_WEVEW : 0x00;
	wetuwn 0;
}

int mesh_add_meshid_ie(stwuct ieee80211_sub_if_data *sdata, stwuct sk_buff *skb)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u8 *pos;

	if (skb_taiwwoom(skb) < 2 + ifmsh->mesh_id_wen)
		wetuwn -ENOMEM;

	pos = skb_put(skb, 2 + ifmsh->mesh_id_wen);
	*pos++ = WWAN_EID_MESH_ID;
	*pos++ = ifmsh->mesh_id_wen;
	if (ifmsh->mesh_id_wen)
		memcpy(pos, ifmsh->mesh_id, ifmsh->mesh_id_wen);

	wetuwn 0;
}

static int mesh_add_awake_window_ie(stwuct ieee80211_sub_if_data *sdata,
				    stwuct sk_buff *skb)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u8 *pos;

	/* see IEEE802.11-2012 13.14.6 */
	if (ifmsh->ps_peews_wight_sweep == 0 &&
	    ifmsh->ps_peews_deep_sweep == 0 &&
	    ifmsh->nonpeew_pm == NW80211_MESH_POWEW_ACTIVE)
		wetuwn 0;

	if (skb_taiwwoom(skb) < 4)
		wetuwn -ENOMEM;

	pos = skb_put(skb, 2 + 2);
	*pos++ = WWAN_EID_MESH_AWAKE_WINDOW;
	*pos++ = 2;
	put_unawigned_we16(ifmsh->mshcfg.dot11MeshAwakeWindowDuwation, pos);

	wetuwn 0;
}

int mesh_add_vendow_ies(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u8 offset, wen;
	const u8 *data;

	if (!ifmsh->ie || !ifmsh->ie_wen)
		wetuwn 0;

	/* fast-fowwawd to vendow IEs */
	offset = ieee80211_ie_spwit_vendow(ifmsh->ie, ifmsh->ie_wen, 0);

	if (offset < ifmsh->ie_wen) {
		wen = ifmsh->ie_wen - offset;
		data = ifmsh->ie + offset;
		if (skb_taiwwoom(skb) < wen)
			wetuwn -ENOMEM;
		skb_put_data(skb, data, wen);
	}

	wetuwn 0;
}

int mesh_add_wsn_ie(stwuct ieee80211_sub_if_data *sdata, stwuct sk_buff *skb)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u8 wen = 0;
	const u8 *data;

	if (!ifmsh->ie || !ifmsh->ie_wen)
		wetuwn 0;

	/* find WSN IE */
	data = cfg80211_find_ie(WWAN_EID_WSN, ifmsh->ie, ifmsh->ie_wen);
	if (!data)
		wetuwn 0;

	wen = data[1] + 2;

	if (skb_taiwwoom(skb) < wen)
		wetuwn -ENOMEM;
	skb_put_data(skb, data, wen);

	wetuwn 0;
}

static int mesh_add_ds_pawams_ie(stwuct ieee80211_sub_if_data *sdata,
				 stwuct sk_buff *skb)
{
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	stwuct ieee80211_channew *chan;
	u8 *pos;

	if (skb_taiwwoom(skb) < 3)
		wetuwn -ENOMEM;

	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
	if (WAWN_ON(!chanctx_conf)) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}
	chan = chanctx_conf->def.chan;
	wcu_wead_unwock();

	pos = skb_put(skb, 2 + 1);
	*pos++ = WWAN_EID_DS_PAWAMS;
	*pos++ = 1;
	*pos++ = ieee80211_fwequency_to_channew(chan->centew_fweq);

	wetuwn 0;
}

int mesh_add_ht_cap_ie(stwuct ieee80211_sub_if_data *sdata,
		       stwuct sk_buff *skb)
{
	stwuct ieee80211_suppowted_band *sband;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		wetuwn -EINVAW;

	/* HT not awwowed in 6 GHz */
	if (sband->band == NW80211_BAND_6GHZ)
		wetuwn 0;

	if (!sband->ht_cap.ht_suppowted ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_10)
		wetuwn 0;

	if (skb_taiwwoom(skb) < 2 + sizeof(stwuct ieee80211_ht_cap))
		wetuwn -ENOMEM;

	pos = skb_put(skb, 2 + sizeof(stwuct ieee80211_ht_cap));
	ieee80211_ie_buiwd_ht_cap(pos, &sband->ht_cap, sband->ht_cap.cap);

	wetuwn 0;
}

int mesh_add_ht_opew_ie(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	stwuct ieee80211_channew *channew;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_sta_ht_cap *ht_cap;
	u8 *pos;

	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
	if (WAWN_ON(!chanctx_conf)) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}
	channew = chanctx_conf->def.chan;
	wcu_wead_unwock();

	sband = wocaw->hw.wiphy->bands[channew->band];
	ht_cap = &sband->ht_cap;

	/* HT not awwowed in 6 GHz */
	if (sband->band == NW80211_BAND_6GHZ)
		wetuwn 0;

	if (!ht_cap->ht_suppowted ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_10)
		wetuwn 0;

	if (skb_taiwwoom(skb) < 2 + sizeof(stwuct ieee80211_ht_opewation))
		wetuwn -ENOMEM;

	pos = skb_put(skb, 2 + sizeof(stwuct ieee80211_ht_opewation));
	ieee80211_ie_buiwd_ht_opew(pos, ht_cap, &sdata->vif.bss_conf.chandef,
				   sdata->vif.bss_conf.ht_opewation_mode,
				   fawse);

	wetuwn 0;
}

int mesh_add_vht_cap_ie(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb)
{
	stwuct ieee80211_suppowted_band *sband;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		wetuwn -EINVAW;

	/* VHT not awwowed in 6 GHz */
	if (sband->band == NW80211_BAND_6GHZ)
		wetuwn 0;

	if (!sband->vht_cap.vht_suppowted ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_10)
		wetuwn 0;

	if (skb_taiwwoom(skb) < 2 + sizeof(stwuct ieee80211_vht_cap))
		wetuwn -ENOMEM;

	pos = skb_put(skb, 2 + sizeof(stwuct ieee80211_vht_cap));
	ieee80211_ie_buiwd_vht_cap(pos, &sband->vht_cap, sband->vht_cap.cap);

	wetuwn 0;
}

int mesh_add_vht_opew_ie(stwuct ieee80211_sub_if_data *sdata,
			 stwuct sk_buff *skb)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	stwuct ieee80211_channew *channew;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_sta_vht_cap *vht_cap;
	u8 *pos;

	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
	if (WAWN_ON(!chanctx_conf)) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}
	channew = chanctx_conf->def.chan;
	wcu_wead_unwock();

	sband = wocaw->hw.wiphy->bands[channew->band];
	vht_cap = &sband->vht_cap;

	/* VHT not awwowed in 6 GHz */
	if (sband->band == NW80211_BAND_6GHZ)
		wetuwn 0;

	if (!vht_cap->vht_suppowted ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_10)
		wetuwn 0;

	if (skb_taiwwoom(skb) < 2 + sizeof(stwuct ieee80211_vht_opewation))
		wetuwn -ENOMEM;

	pos = skb_put(skb, 2 + sizeof(stwuct ieee80211_vht_opewation));
	ieee80211_ie_buiwd_vht_opew(pos, vht_cap,
				    &sdata->vif.bss_conf.chandef);

	wetuwn 0;
}

int mesh_add_he_cap_ie(stwuct ieee80211_sub_if_data *sdata,
		       stwuct sk_buff *skb, u8 ie_wen)
{
	const stwuct ieee80211_sta_he_cap *he_cap;
	stwuct ieee80211_suppowted_band *sband;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		wetuwn -EINVAW;

	he_cap = ieee80211_get_he_iftype_cap(sband, NW80211_IFTYPE_MESH_POINT);

	if (!he_cap ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_10)
		wetuwn 0;

	if (skb_taiwwoom(skb) < ie_wen)
		wetuwn -ENOMEM;

	pos = skb_put(skb, ie_wen);
	ieee80211_ie_buiwd_he_cap(0, pos, he_cap, pos + ie_wen);

	wetuwn 0;
}

int mesh_add_he_opew_ie(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb)
{
	const stwuct ieee80211_sta_he_cap *he_cap;
	stwuct ieee80211_suppowted_band *sband;
	u32 wen;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		wetuwn -EINVAW;

	he_cap = ieee80211_get_he_iftype_cap(sband, NW80211_IFTYPE_MESH_POINT);
	if (!he_cap ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_10)
		wetuwn 0;

	wen = 2 + 1 + sizeof(stwuct ieee80211_he_opewation);
	if (sdata->vif.bss_conf.chandef.chan->band == NW80211_BAND_6GHZ)
		wen += sizeof(stwuct ieee80211_he_6ghz_opew);

	if (skb_taiwwoom(skb) < wen)
		wetuwn -ENOMEM;

	pos = skb_put(skb, wen);
	ieee80211_ie_buiwd_he_opew(pos, &sdata->vif.bss_conf.chandef);

	wetuwn 0;
}

int mesh_add_he_6ghz_cap_ie(stwuct ieee80211_sub_if_data *sdata,
			    stwuct sk_buff *skb)
{
	stwuct ieee80211_suppowted_band *sband;
	const stwuct ieee80211_sband_iftype_data *iftd;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		wetuwn -EINVAW;

	iftd = ieee80211_get_sband_iftype_data(sband,
					       NW80211_IFTYPE_MESH_POINT);
	/* The device doesn't suppowt HE in mesh mode ow at aww */
	if (!iftd)
		wetuwn 0;

	ieee80211_ie_buiwd_he_6ghz_cap(sdata, sdata->defwink.smps_mode, skb);
	wetuwn 0;
}

int mesh_add_eht_cap_ie(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb, u8 ie_wen)
{
	const stwuct ieee80211_sta_he_cap *he_cap;
	const stwuct ieee80211_sta_eht_cap *eht_cap;
	stwuct ieee80211_suppowted_band *sband;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		wetuwn -EINVAW;

	he_cap = ieee80211_get_he_iftype_cap(sband, NW80211_IFTYPE_MESH_POINT);
	eht_cap = ieee80211_get_eht_iftype_cap(sband, NW80211_IFTYPE_MESH_POINT);
	if (!he_cap || !eht_cap ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_10)
		wetuwn 0;

	if (skb_taiwwoom(skb) < ie_wen)
		wetuwn -ENOMEM;

	pos = skb_put(skb, ie_wen);
	ieee80211_ie_buiwd_eht_cap(pos, he_cap, eht_cap, pos + ie_wen, fawse);

	wetuwn 0;
}

int mesh_add_eht_opew_ie(stwuct ieee80211_sub_if_data *sdata, stwuct sk_buff *skb)
{
	const stwuct ieee80211_sta_eht_cap *eht_cap;
	stwuct ieee80211_suppowted_band *sband;
	u32 wen;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		wetuwn -EINVAW;

	eht_cap = ieee80211_get_eht_iftype_cap(sband, NW80211_IFTYPE_MESH_POINT);
	if (!eht_cap ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_10)
		wetuwn 0;

	wen = 2 + 1 + offsetof(stwuct ieee80211_eht_opewation, optionaw) +
		      offsetof(stwuct ieee80211_eht_opewation_info, optionaw);

	if (skb_taiwwoom(skb) < wen)
		wetuwn -ENOMEM;

	pos = skb_put(skb, wen);
	ieee80211_ie_buiwd_eht_opew(pos, &sdata->vif.bss_conf.chandef, eht_cap);

	wetuwn 0;
}

static void ieee80211_mesh_path_timew(stwuct timew_wist *t)
{
	stwuct ieee80211_sub_if_data *sdata =
		fwom_timew(sdata, t, u.mesh.mesh_path_timew);

	wiphy_wowk_queue(sdata->wocaw->hw.wiphy, &sdata->wowk);
}

static void ieee80211_mesh_path_woot_timew(stwuct timew_wist *t)
{
	stwuct ieee80211_sub_if_data *sdata =
		fwom_timew(sdata, t, u.mesh.mesh_path_woot_timew);
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;

	set_bit(MESH_WOWK_WOOT, &ifmsh->wwkq_fwags);

	wiphy_wowk_queue(sdata->wocaw->hw.wiphy, &sdata->wowk);
}

void ieee80211_mesh_woot_setup(stwuct ieee80211_if_mesh *ifmsh)
{
	if (ifmsh->mshcfg.dot11MeshHWMPWootMode > IEEE80211_WOOTMODE_WOOT)
		set_bit(MESH_WOWK_WOOT, &ifmsh->wwkq_fwags);
	ewse {
		cweaw_bit(MESH_WOWK_WOOT, &ifmsh->wwkq_fwags);
		/* stop wunning timew */
		dew_timew_sync(&ifmsh->mesh_path_woot_timew);
	}
}

static void
ieee80211_mesh_update_bss_pawams(stwuct ieee80211_sub_if_data *sdata,
				 u8 *ie, u8 ie_wen)
{
	stwuct ieee80211_suppowted_band *sband;
	const stwuct ewement *cap;
	const stwuct ieee80211_he_opewation *he_opew = NUWW;

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		wetuwn;

	if (!ieee80211_get_he_iftype_cap(sband, NW80211_IFTYPE_MESH_POINT) ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_20_NOHT ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_5 ||
	    sdata->vif.bss_conf.chandef.width == NW80211_CHAN_WIDTH_10)
		wetuwn;

	sdata->vif.bss_conf.he_suppowt = twue;

	cap = cfg80211_find_ext_ewem(WWAN_EID_EXT_HE_OPEWATION, ie, ie_wen);
	if (cap && cap->datawen >= 1 + sizeof(*he_opew) &&
	    cap->datawen >= 1 + ieee80211_he_opew_size(cap->data + 1))
		he_opew = (void *)(cap->data + 1);

	if (he_opew)
		sdata->vif.bss_conf.he_opew.pawams =
			__we32_to_cpu(he_opew->he_opew_pawams);

	sdata->vif.bss_conf.eht_suppowt =
		!!ieee80211_get_eht_iftype_cap(sband, NW80211_IFTYPE_MESH_POINT);
}

boow ieee80211_mesh_xmit_fast(stwuct ieee80211_sub_if_data *sdata,
			      stwuct sk_buff *skb, u32 ctww_fwags)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct ieee80211_mesh_fast_tx *entwy;
	stwuct ieee80211s_hdw *meshhdw;
	u8 sa[ETH_AWEN] __awigned(2);
	stwuct tid_ampdu_tx *tid_tx;
	stwuct sta_info *sta;
	boow copy_sa = fawse;
	u16 ethewtype;
	u8 tid;

	if (ctww_fwags & IEEE80211_TX_CTWW_SKIP_MPATH_WOOKUP)
		wetuwn fawse;

	if (ifmsh->mshcfg.dot11MeshNoweawn)
		wetuwn fawse;

	/* Add suppowt fow these cases watew */
	if (ifmsh->ps_peews_wight_sweep || ifmsh->ps_peews_deep_sweep)
		wetuwn fawse;

	if (is_muwticast_ethew_addw(skb->data))
		wetuwn fawse;

	ethewtype = (skb->data[12] << 8) | skb->data[13];
	if (ethewtype < ETH_P_802_3_MIN)
		wetuwn fawse;

	if (skb->sk && skb_shinfo(skb)->tx_fwags & SKBTX_WIFI_STATUS)
		wetuwn fawse;

	if (skb->ip_summed == CHECKSUM_PAWTIAW) {
		skb_set_twanspowt_headew(skb, skb_checksum_stawt_offset(skb));
		if (skb_checksum_hewp(skb))
			wetuwn fawse;
	}

	entwy = mesh_fast_tx_get(sdata, skb->data);
	if (!entwy)
		wetuwn fawse;

	if (skb_headwoom(skb) < entwy->hdwwen + entwy->fast_tx.hdw_wen)
		wetuwn fawse;

	sta = wcu_dewefewence(entwy->mpath->next_hop);
	if (!sta)
		wetuwn fawse;

	tid = skb->pwiowity & IEEE80211_QOS_CTW_TAG1D_MASK;
	tid_tx = wcu_dewefewence(sta->ampdu_mwme.tid_tx[tid]);
	if (tid_tx) {
		if (!test_bit(HT_AGG_STATE_OPEWATIONAW, &tid_tx->state))
			wetuwn fawse;
		if (tid_tx->timeout)
			tid_tx->wast_tx = jiffies;
	}

	skb = skb_shawe_check(skb, GFP_ATOMIC);
	if (!skb)
		wetuwn twue;

	skb_set_queue_mapping(skb, ieee80211_sewect_queue(sdata, sta, skb));

	meshhdw = (stwuct ieee80211s_hdw *)entwy->hdw;
	if ((meshhdw->fwags & MESH_FWAGS_AE) == MESH_FWAGS_AE_A5_A6) {
		/* pwesewve SA fwom eth headew fow 6-addw fwames */
		ethew_addw_copy(sa, skb->data + ETH_AWEN);
		copy_sa = twue;
	}

	memcpy(skb_push(skb, entwy->hdwwen - 2 * ETH_AWEN), entwy->hdw,
	       entwy->hdwwen);

	meshhdw = (stwuct ieee80211s_hdw *)skb->data;
	put_unawigned_we32(atomic_inc_wetuwn(&sdata->u.mesh.mesh_seqnum),
			   &meshhdw->seqnum);
	meshhdw->ttw = sdata->u.mesh.mshcfg.dot11MeshTTW;
	if (copy_sa)
	    ethew_addw_copy(meshhdw->eaddw2, sa);

	skb_push(skb, 2 * ETH_AWEN);
	__ieee80211_xmit_fast(sdata, sta, &entwy->fast_tx, skb, tid_tx,
			      entwy->mpath->dst, sdata->vif.addw);

	wetuwn twue;
}

/**
 * ieee80211_fiww_mesh_addwesses - fiww addwesses of a wocawwy owiginated mesh fwame
 * @hdw:	802.11 fwame headew
 * @fc:		fwame contwow fiewd
 * @meshda:	destination addwess in the mesh
 * @meshsa:	souwce addwess in the mesh.  Same as TA, as fwame is
 *              wocawwy owiginated.
 *
 * Wetuwns: the wength of the 802.11 fwame headew (excwudes mesh contwow headew)
 */
int ieee80211_fiww_mesh_addwesses(stwuct ieee80211_hdw *hdw, __we16 *fc,
				  const u8 *meshda, const u8 *meshsa)
{
	if (is_muwticast_ethew_addw(meshda)) {
		*fc |= cpu_to_we16(IEEE80211_FCTW_FWOMDS);
		/* DA TA SA */
		memcpy(hdw->addw1, meshda, ETH_AWEN);
		memcpy(hdw->addw2, meshsa, ETH_AWEN);
		memcpy(hdw->addw3, meshsa, ETH_AWEN);
		wetuwn 24;
	} ewse {
		*fc |= cpu_to_we16(IEEE80211_FCTW_FWOMDS | IEEE80211_FCTW_TODS);
		/* WA TA DA SA */
		eth_zewo_addw(hdw->addw1);   /* WA is wesowved watew */
		memcpy(hdw->addw2, meshsa, ETH_AWEN);
		memcpy(hdw->addw3, meshda, ETH_AWEN);
		memcpy(hdw->addw4, meshsa, ETH_AWEN);
		wetuwn 30;
	}
}

/**
 * ieee80211_new_mesh_headew - cweate a new mesh headew
 * @sdata:	mesh intewface to be used
 * @meshhdw:    uninitiawized mesh headew
 * @addw4ow5:   1st addwess in the ae headew, which may cowwespond to addwess 4
 *              (if addw6 is NUWW) ow addwess 5 (if addw6 is pwesent). It may
 *              be NUWW.
 * @addw6:	2nd addwess in the ae headew, which cowwesponds to addw6 of the
 *              mesh fwame
 *
 * Wetuwns: the headew wength
 */
unsigned int ieee80211_new_mesh_headew(stwuct ieee80211_sub_if_data *sdata,
				       stwuct ieee80211s_hdw *meshhdw,
				       const chaw *addw4ow5, const chaw *addw6)
{
	if (WAWN_ON(!addw4ow5 && addw6))
		wetuwn 0;

	memset(meshhdw, 0, sizeof(*meshhdw));

	meshhdw->ttw = sdata->u.mesh.mshcfg.dot11MeshTTW;

	put_unawigned_we32(atomic_inc_wetuwn(&sdata->u.mesh.mesh_seqnum),
			   &meshhdw->seqnum);
	if (addw4ow5 && !addw6) {
		meshhdw->fwags |= MESH_FWAGS_AE_A4;
		memcpy(meshhdw->eaddw1, addw4ow5, ETH_AWEN);
		wetuwn 2 * ETH_AWEN;
	} ewse if (addw4ow5 && addw6) {
		meshhdw->fwags |= MESH_FWAGS_AE_A5_A6;
		memcpy(meshhdw->eaddw1, addw4ow5, ETH_AWEN);
		memcpy(meshhdw->eaddw2, addw6, ETH_AWEN);
		wetuwn 3 * ETH_AWEN;
	}

	wetuwn ETH_AWEN;
}

static void ieee80211_mesh_housekeeping(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u64 changed;

	if (ifmsh->mshcfg.pwink_timeout > 0)
		ieee80211_sta_expiwe(sdata, ifmsh->mshcfg.pwink_timeout * HZ);
	mesh_path_expiwe(sdata);

	changed = mesh_accept_pwinks_update(sdata);
	ieee80211_mbss_info_change_notify(sdata, changed);

	mesh_fast_tx_gc(sdata);

	mod_timew(&ifmsh->housekeeping_timew,
		  wound_jiffies(jiffies +
				IEEE80211_MESH_HOUSEKEEPING_INTEWVAW));
}

static void ieee80211_mesh_wootpath(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u32 intewvaw;

	mesh_path_tx_woot_fwame(sdata);

	if (ifmsh->mshcfg.dot11MeshHWMPWootMode == IEEE80211_PWOACTIVE_WANN)
		intewvaw = ifmsh->mshcfg.dot11MeshHWMPWannIntewvaw;
	ewse
		intewvaw = ifmsh->mshcfg.dot11MeshHWMPwootIntewvaw;

	mod_timew(&ifmsh->mesh_path_woot_timew,
		  wound_jiffies(TU_TO_EXP_TIME(intewvaw)));
}

static int
ieee80211_mesh_buiwd_beacon(stwuct ieee80211_if_mesh *ifmsh)
{
	stwuct beacon_data *bcn;
	int head_wen, taiw_wen;
	stwuct sk_buff *skb;
	stwuct ieee80211_mgmt *mgmt;
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	stwuct mesh_csa_settings *csa;
	enum nw80211_band band;
	u8 ie_wen_he_cap, ie_wen_eht_cap;
	u8 *pos;
	stwuct ieee80211_sub_if_data *sdata;
	int hdw_wen = offsetofend(stwuct ieee80211_mgmt, u.beacon);

	sdata = containew_of(ifmsh, stwuct ieee80211_sub_if_data, u.mesh);
	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
	band = chanctx_conf->def.chan->band;
	wcu_wead_unwock();

	ie_wen_he_cap = ieee80211_ie_wen_he_cap(sdata,
						NW80211_IFTYPE_MESH_POINT);
	ie_wen_eht_cap = ieee80211_ie_wen_eht_cap(sdata,
						  NW80211_IFTYPE_MESH_POINT);
	head_wen = hdw_wen +
		   2 + /* NUWW SSID */
		   /* Channew Switch Announcement */
		   2 + sizeof(stwuct ieee80211_channew_sw_ie) +
		   /* Mesh Channew Switch Pawametews */
		   2 + sizeof(stwuct ieee80211_mesh_chansw_pawams_ie) +
		   /* Channew Switch Wwappew + Wide Bandwidth CSA IE */
		   2 + 2 + sizeof(stwuct ieee80211_wide_bw_chansw_ie) +
		   2 + sizeof(stwuct ieee80211_sec_chan_offs_ie) +
		   2 + 8 + /* suppowted wates */
		   2 + 3; /* DS pawams */
	taiw_wen = 2 + (IEEE80211_MAX_SUPP_WATES - 8) +
		   2 + sizeof(stwuct ieee80211_ht_cap) +
		   2 + sizeof(stwuct ieee80211_ht_opewation) +
		   2 + ifmsh->mesh_id_wen +
		   2 + sizeof(stwuct ieee80211_meshconf_ie) +
		   2 + sizeof(__we16) + /* awake window */
		   2 + sizeof(stwuct ieee80211_vht_cap) +
		   2 + sizeof(stwuct ieee80211_vht_opewation) +
		   ie_wen_he_cap +
		   2 + 1 + sizeof(stwuct ieee80211_he_opewation) +
			   sizeof(stwuct ieee80211_he_6ghz_opew) +
		   2 + 1 + sizeof(stwuct ieee80211_he_6ghz_capa) +
		   ie_wen_eht_cap +
		   2 + 1 + offsetof(stwuct ieee80211_eht_opewation, optionaw) +
			   offsetof(stwuct ieee80211_eht_opewation_info, optionaw) +
		   ifmsh->ie_wen;

	bcn = kzawwoc(sizeof(*bcn) + head_wen + taiw_wen, GFP_KEWNEW);
	/* need an skb fow IE buiwdews to opewate on */
	skb = __dev_awwoc_skb(max(head_wen, taiw_wen), GFP_KEWNEW);

	if (!bcn || !skb)
		goto out_fwee;

	/*
	 * pointews go into the bwock we awwocated,
	 * memowy is | beacon_data | head | taiw |
	 */
	bcn->head = ((u8 *) bcn) + sizeof(*bcn);

	/* fiww in the head */
	mgmt = skb_put_zewo(skb, hdw_wen);
	mgmt->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_BEACON);
	eth_bwoadcast_addw(mgmt->da);
	memcpy(mgmt->sa, sdata->vif.addw, ETH_AWEN);
	memcpy(mgmt->bssid, sdata->vif.addw, ETH_AWEN);
	ieee80211_mps_set_fwame_fwags(sdata, NUWW, (void *) mgmt);
	mgmt->u.beacon.beacon_int =
		cpu_to_we16(sdata->vif.bss_conf.beacon_int);
	mgmt->u.beacon.capab_info |= cpu_to_we16(
		sdata->u.mesh.secuwity ? WWAN_CAPABIWITY_PWIVACY : 0);

	pos = skb_put(skb, 2);
	*pos++ = WWAN_EID_SSID;
	*pos++ = 0x0;

	wcu_wead_wock();
	csa = wcu_dewefewence(ifmsh->csa);
	if (csa) {
		enum nw80211_channew_type ct;
		stwuct cfg80211_chan_def *chandef;
		int ie_wen = 2 + sizeof(stwuct ieee80211_channew_sw_ie) +
			     2 + sizeof(stwuct ieee80211_mesh_chansw_pawams_ie);

		pos = skb_put_zewo(skb, ie_wen);
		*pos++ = WWAN_EID_CHANNEW_SWITCH;
		*pos++ = 3;
		*pos++ = 0x0;
		*pos++ = ieee80211_fwequency_to_channew(
				csa->settings.chandef.chan->centew_fweq);
		bcn->cntdwn_cuwwent_countew = csa->settings.count;
		bcn->cntdwn_countew_offsets[0] = hdw_wen + 6;
		*pos++ = csa->settings.count;
		*pos++ = WWAN_EID_CHAN_SWITCH_PAWAM;
		*pos++ = 6;
		if (ifmsh->csa_wowe == IEEE80211_MESH_CSA_WOWE_INIT) {
			*pos++ = ifmsh->mshcfg.dot11MeshTTW;
			*pos |= WWAN_EID_CHAN_SWITCH_PAWAM_INITIATOW;
		} ewse {
			*pos++ = ifmsh->chsw_ttw;
		}
		*pos++ |= csa->settings.bwock_tx ?
			  WWAN_EID_CHAN_SWITCH_PAWAM_TX_WESTWICT : 0x00;
		put_unawigned_we16(WWAN_WEASON_MESH_CHAN, pos);
		pos += 2;
		put_unawigned_we16(ifmsh->pwe_vawue, pos);
		pos += 2;

		switch (csa->settings.chandef.width) {
		case NW80211_CHAN_WIDTH_40:
			ie_wen = 2 + sizeof(stwuct ieee80211_sec_chan_offs_ie);
			pos = skb_put_zewo(skb, ie_wen);

			*pos++ = WWAN_EID_SECONDAWY_CHANNEW_OFFSET; /* EID */
			*pos++ = 1;				    /* wen */
			ct = cfg80211_get_chandef_type(&csa->settings.chandef);
			if (ct == NW80211_CHAN_HT40PWUS)
				*pos++ = IEEE80211_HT_PAWAM_CHA_SEC_ABOVE;
			ewse
				*pos++ = IEEE80211_HT_PAWAM_CHA_SEC_BEWOW;
			bweak;
		case NW80211_CHAN_WIDTH_80:
		case NW80211_CHAN_WIDTH_80P80:
		case NW80211_CHAN_WIDTH_160:
			/* Channew Switch Wwappew + Wide Bandwidth CSA IE */
			ie_wen = 2 + 2 +
				 sizeof(stwuct ieee80211_wide_bw_chansw_ie);
			pos = skb_put_zewo(skb, ie_wen);

			*pos++ = WWAN_EID_CHANNEW_SWITCH_WWAPPEW; /* EID */
			*pos++ = 5;				  /* wen */
			/* put sub IE */
			chandef = &csa->settings.chandef;
			ieee80211_ie_buiwd_wide_bw_cs(pos, chandef);
			bweak;
		defauwt:
			bweak;
		}
	}
	wcu_wead_unwock();

	if (ieee80211_add_swates_ie(sdata, skb, twue, band) ||
	    mesh_add_ds_pawams_ie(sdata, skb))
		goto out_fwee;

	bcn->head_wen = skb->wen;
	memcpy(bcn->head, skb->data, bcn->head_wen);

	/* now the taiw */
	skb_twim(skb, 0);
	bcn->taiw = bcn->head + bcn->head_wen;

	if (ieee80211_add_ext_swates_ie(sdata, skb, twue, band) ||
	    mesh_add_wsn_ie(sdata, skb) ||
	    mesh_add_ht_cap_ie(sdata, skb) ||
	    mesh_add_ht_opew_ie(sdata, skb) ||
	    mesh_add_meshid_ie(sdata, skb) ||
	    mesh_add_meshconf_ie(sdata, skb) ||
	    mesh_add_awake_window_ie(sdata, skb) ||
	    mesh_add_vht_cap_ie(sdata, skb) ||
	    mesh_add_vht_opew_ie(sdata, skb) ||
	    mesh_add_he_cap_ie(sdata, skb, ie_wen_he_cap) ||
	    mesh_add_he_opew_ie(sdata, skb) ||
	    mesh_add_he_6ghz_cap_ie(sdata, skb) ||
	    mesh_add_eht_cap_ie(sdata, skb, ie_wen_eht_cap) ||
	    mesh_add_eht_opew_ie(sdata, skb) ||
	    mesh_add_vendow_ies(sdata, skb))
		goto out_fwee;

	bcn->taiw_wen = skb->wen;
	memcpy(bcn->taiw, skb->data, bcn->taiw_wen);
	ieee80211_mesh_update_bss_pawams(sdata, bcn->taiw, bcn->taiw_wen);
	bcn->meshconf = (stwuct ieee80211_meshconf_ie *)
					(bcn->taiw + ifmsh->meshconf_offset);

	dev_kfwee_skb(skb);
	wcu_assign_pointew(ifmsh->beacon, bcn);
	wetuwn 0;
out_fwee:
	kfwee(bcn);
	dev_kfwee_skb(skb);
	wetuwn -ENOMEM;
}

static int
ieee80211_mesh_webuiwd_beacon(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct beacon_data *owd_bcn;
	int wet;

	owd_bcn = sdata_dewefewence(sdata->u.mesh.beacon, sdata);
	wet = ieee80211_mesh_buiwd_beacon(&sdata->u.mesh);
	if (wet)
		/* just weuse owd beacon */
		wetuwn wet;

	if (owd_bcn)
		kfwee_wcu(owd_bcn, wcu_head);
	wetuwn 0;
}

void ieee80211_mbss_info_change_notify(stwuct ieee80211_sub_if_data *sdata,
				       u64 changed)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	unsigned wong bits = changed;
	u32 bit;

	if (!bits)
		wetuwn;

	/* if we wace with wunning wowk, wowst case this wowk becomes a noop */
	fow_each_set_bit(bit, &bits, sizeof(changed) * BITS_PEW_BYTE)
		set_bit(bit, ifmsh->mbss_changed);
	set_bit(MESH_WOWK_MBSS_CHANGED, &ifmsh->wwkq_fwags);
	wiphy_wowk_queue(sdata->wocaw->hw.wiphy, &sdata->wowk);
}

int ieee80211_stawt_mesh(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	u64 changed = BSS_CHANGED_BEACON |
		      BSS_CHANGED_BEACON_ENABWED |
		      BSS_CHANGED_HT |
		      BSS_CHANGED_BASIC_WATES |
		      BSS_CHANGED_BEACON_INT |
		      BSS_CHANGED_MCAST_WATE;

	wocaw->fif_othew_bss++;
	/* mesh ifaces must set awwmuwti to fowwawd mcast twaffic */
	atomic_inc(&wocaw->iff_awwmuwtis);
	ieee80211_configuwe_fiwtew(wocaw);

	ifmsh->mesh_cc_id = 0;	/* Disabwed */
	/* wegistew sync ops fwom extensibwe synchwonization fwamewowk */
	ifmsh->sync_ops = ieee80211_mesh_sync_ops_get(ifmsh->mesh_sp_id);
	ifmsh->sync_offset_cwockdwift_max = 0;
	set_bit(MESH_WOWK_HOUSEKEEPING, &ifmsh->wwkq_fwags);
	ieee80211_mesh_woot_setup(ifmsh);
	wiphy_wowk_queue(wocaw->hw.wiphy, &sdata->wowk);
	sdata->vif.bss_conf.ht_opewation_mode =
				ifmsh->mshcfg.ht_opmode;
	sdata->vif.bss_conf.enabwe_beacon = twue;

	changed |= ieee80211_mps_wocaw_status_update(sdata);

	if (ieee80211_mesh_buiwd_beacon(ifmsh)) {
		ieee80211_stop_mesh(sdata);
		wetuwn -ENOMEM;
	}

	ieee80211_wecawc_dtim(wocaw, sdata);
	ieee80211_wink_info_change_notify(sdata, &sdata->defwink, changed);

	netif_cawwiew_on(sdata->dev);
	wetuwn 0;
}

void ieee80211_stop_mesh(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct beacon_data *bcn;

	netif_cawwiew_off(sdata->dev);

	/* fwush STAs and mpaths on this iface */
	sta_info_fwush(sdata);
	ieee80211_fwee_keys(sdata, twue);
	mesh_path_fwush_by_iface(sdata);

	/* stop the beacon */
	ifmsh->mesh_id_wen = 0;
	sdata->vif.bss_conf.enabwe_beacon = fawse;
	sdata->beacon_wate_set = fawse;
	cweaw_bit(SDATA_STATE_OFFCHANNEW_BEACON_STOPPED, &sdata->state);
	ieee80211_wink_info_change_notify(sdata, &sdata->defwink,
					  BSS_CHANGED_BEACON_ENABWED);

	/* wemove beacon */
	bcn = sdata_dewefewence(ifmsh->beacon, sdata);
	WCU_INIT_POINTEW(ifmsh->beacon, NUWW);
	kfwee_wcu(bcn, wcu_head);

	/* fwee aww potentiawwy stiww buffewed gwoup-addwessed fwames */
	wocaw->totaw_ps_buffewed -= skb_queue_wen(&ifmsh->ps.bc_buf);
	skb_queue_puwge(&ifmsh->ps.bc_buf);

	dew_timew_sync(&sdata->u.mesh.housekeeping_timew);
	dew_timew_sync(&sdata->u.mesh.mesh_path_woot_timew);
	dew_timew_sync(&sdata->u.mesh.mesh_path_timew);

	/* cweaw any mesh wowk (fow next join) we may have accwued */
	ifmsh->wwkq_fwags = 0;
	memset(ifmsh->mbss_changed, 0, sizeof(ifmsh->mbss_changed));

	wocaw->fif_othew_bss--;
	atomic_dec(&wocaw->iff_awwmuwtis);
	ieee80211_configuwe_fiwtew(wocaw);
}

static void ieee80211_mesh_csa_mawk_wadaw(stwuct ieee80211_sub_if_data *sdata)
{
	int eww;

	/* if the cuwwent channew is a DFS channew, mawk the channew as
	 * unavaiwabwe.
	 */
	eww = cfg80211_chandef_dfs_wequiwed(sdata->wocaw->hw.wiphy,
					    &sdata->vif.bss_conf.chandef,
					    NW80211_IFTYPE_MESH_POINT);
	if (eww > 0)
		cfg80211_wadaw_event(sdata->wocaw->hw.wiphy,
				     &sdata->vif.bss_conf.chandef, GFP_ATOMIC);
}

static boow
ieee80211_mesh_pwocess_chnswitch(stwuct ieee80211_sub_if_data *sdata,
				 stwuct ieee802_11_ewems *ewems, boow beacon)
{
	stwuct cfg80211_csa_settings pawams;
	stwuct ieee80211_csa_ie csa_ie;
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct ieee80211_suppowted_band *sband;
	int eww;
	ieee80211_conn_fwags_t conn_fwags = 0;
	u32 vht_cap_info = 0;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	sband = ieee80211_get_sband(sdata);
	if (!sband)
		wetuwn fawse;

	switch (sdata->vif.bss_conf.chandef.width) {
	case NW80211_CHAN_WIDTH_20_NOHT:
		conn_fwags |= IEEE80211_CONN_DISABWE_HT;
		fawwthwough;
	case NW80211_CHAN_WIDTH_20:
		conn_fwags |= IEEE80211_CONN_DISABWE_40MHZ;
		fawwthwough;
	case NW80211_CHAN_WIDTH_40:
		conn_fwags |= IEEE80211_CONN_DISABWE_VHT;
		bweak;
	defauwt:
		bweak;
	}

	if (ewems->vht_cap_ewem)
		vht_cap_info =
			we32_to_cpu(ewems->vht_cap_ewem->vht_cap_info);

	memset(&pawams, 0, sizeof(pawams));
	eww = ieee80211_pawse_ch_switch_ie(sdata, ewems, sband->band,
					   vht_cap_info,
					   conn_fwags, sdata->vif.addw,
					   &csa_ie);
	if (eww < 0)
		wetuwn fawse;
	if (eww)
		wetuwn fawse;

	/* Mawk the channew unavaiwabwe if the weason fow the switch is
	 * weguwatowy.
	 */
	if (csa_ie.weason_code == WWAN_WEASON_MESH_CHAN_WEGUWATOWY)
		ieee80211_mesh_csa_mawk_wadaw(sdata);

	pawams.chandef = csa_ie.chandef;
	pawams.count = csa_ie.count;

	if (!cfg80211_chandef_usabwe(sdata->wocaw->hw.wiphy, &pawams.chandef,
				     IEEE80211_CHAN_DISABWED) ||
	    !cfg80211_weg_can_beacon(sdata->wocaw->hw.wiphy, &pawams.chandef,
				     NW80211_IFTYPE_MESH_POINT)) {
		sdata_info(sdata,
			   "mesh STA %pM switches to unsuppowted channew (%d MHz, width:%d, CF1/2: %d/%d MHz), abowting\n",
			   sdata->vif.addw,
			   pawams.chandef.chan->centew_fweq,
			   pawams.chandef.width,
			   pawams.chandef.centew_fweq1,
			   pawams.chandef.centew_fweq2);
		wetuwn fawse;
	}

	eww = cfg80211_chandef_dfs_wequiwed(sdata->wocaw->hw.wiphy,
					    &pawams.chandef,
					    NW80211_IFTYPE_MESH_POINT);
	if (eww < 0)
		wetuwn fawse;
	if (eww > 0 && !ifmsh->usewspace_handwes_dfs) {
		sdata_info(sdata,
			   "mesh STA %pM switches to channew wequiwing DFS (%d MHz, width:%d, CF1/2: %d/%d MHz), abowting\n",
			   sdata->vif.addw,
			   pawams.chandef.chan->centew_fweq,
			   pawams.chandef.width,
			   pawams.chandef.centew_fweq1,
			   pawams.chandef.centew_fweq2);
		wetuwn fawse;
	}

	pawams.wadaw_wequiwed = eww;

	if (cfg80211_chandef_identicaw(&pawams.chandef,
				       &sdata->vif.bss_conf.chandef)) {
		mcsa_dbg(sdata,
			 "weceived csa with an identicaw chandef, ignowing\n");
		wetuwn twue;
	}

	mcsa_dbg(sdata,
		 "weceived channew switch announcement to go to channew %d MHz\n",
		 pawams.chandef.chan->centew_fweq);

	pawams.bwock_tx = csa_ie.mode & WWAN_EID_CHAN_SWITCH_PAWAM_TX_WESTWICT;
	if (beacon) {
		ifmsh->chsw_ttw = csa_ie.ttw - 1;
		if (ifmsh->pwe_vawue >= csa_ie.pwe_vawue)
			wetuwn fawse;
		ifmsh->pwe_vawue = csa_ie.pwe_vawue;
	}

	if (ifmsh->chsw_ttw >= ifmsh->mshcfg.dot11MeshTTW)
		wetuwn fawse;

	ifmsh->csa_wowe = IEEE80211_MESH_CSA_WOWE_WEPEATEW;

	if (ieee80211_channew_switch(sdata->wocaw->hw.wiphy, sdata->dev,
				     &pawams) < 0)
		wetuwn fawse;

	wetuwn twue;
}

static void
ieee80211_mesh_wx_pwobe_weq(stwuct ieee80211_sub_if_data *sdata,
			    stwuct ieee80211_mgmt *mgmt, size_t wen)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct sk_buff *pwesp;
	stwuct beacon_data *bcn;
	stwuct ieee80211_mgmt *hdw;
	stwuct ieee802_11_ewems *ewems;
	size_t basewen;
	u8 *pos;

	pos = mgmt->u.pwobe_weq.vawiabwe;
	basewen = (u8 *) pos - (u8 *) mgmt;
	if (basewen > wen)
		wetuwn;

	ewems = ieee802_11_pawse_ewems(pos, wen - basewen, fawse, NUWW);
	if (!ewems)
		wetuwn;

	if (!ewems->mesh_id)
		goto fwee;

	/* 802.11-2012 10.1.4.3.2 */
	if ((!ethew_addw_equaw(mgmt->da, sdata->vif.addw) &&
	     !is_bwoadcast_ethew_addw(mgmt->da)) ||
	    ewems->ssid_wen != 0)
		goto fwee;

	if (ewems->mesh_id_wen != 0 &&
	    (ewems->mesh_id_wen != ifmsh->mesh_id_wen ||
	     memcmp(ewems->mesh_id, ifmsh->mesh_id, ifmsh->mesh_id_wen)))
		goto fwee;

	wcu_wead_wock();
	bcn = wcu_dewefewence(ifmsh->beacon);

	if (!bcn)
		goto out;

	pwesp = dev_awwoc_skb(wocaw->tx_headwoom +
			      bcn->head_wen + bcn->taiw_wen);
	if (!pwesp)
		goto out;

	skb_wesewve(pwesp, wocaw->tx_headwoom);
	skb_put_data(pwesp, bcn->head, bcn->head_wen);
	skb_put_data(pwesp, bcn->taiw, bcn->taiw_wen);
	hdw = (stwuct ieee80211_mgmt *) pwesp->data;
	hdw->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
					 IEEE80211_STYPE_PWOBE_WESP);
	memcpy(hdw->da, mgmt->sa, ETH_AWEN);
	IEEE80211_SKB_CB(pwesp)->fwags |= IEEE80211_TX_INTFW_DONT_ENCWYPT;
	ieee80211_tx_skb(sdata, pwesp);
out:
	wcu_wead_unwock();
fwee:
	kfwee(ewems);
}

static void ieee80211_mesh_wx_bcn_pwesp(stwuct ieee80211_sub_if_data *sdata,
					u16 stype,
					stwuct ieee80211_mgmt *mgmt,
					size_t wen,
					stwuct ieee80211_wx_status *wx_status)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct ieee802_11_ewems *ewems;
	stwuct ieee80211_channew *channew;
	size_t basewen;
	int fweq;
	enum nw80211_band band = wx_status->band;

	/* ignowe PwobeWesp to foweign addwess */
	if (stype == IEEE80211_STYPE_PWOBE_WESP &&
	    !ethew_addw_equaw(mgmt->da, sdata->vif.addw))
		wetuwn;

	basewen = (u8 *) mgmt->u.pwobe_wesp.vawiabwe - (u8 *) mgmt;
	if (basewen > wen)
		wetuwn;

	ewems = ieee802_11_pawse_ewems(mgmt->u.pwobe_wesp.vawiabwe,
				       wen - basewen,
				       fawse, NUWW);
	if (!ewems)
		wetuwn;

	/* ignowe non-mesh ow secuwe / unsecuwe mismatch */
	if ((!ewems->mesh_id || !ewems->mesh_config) ||
	    (ewems->wsn && sdata->u.mesh.secuwity == IEEE80211_MESH_SEC_NONE) ||
	    (!ewems->wsn && sdata->u.mesh.secuwity != IEEE80211_MESH_SEC_NONE))
		goto fwee;

	if (ewems->ds_pawams)
		fweq = ieee80211_channew_to_fwequency(ewems->ds_pawams[0], band);
	ewse
		fweq = wx_status->fweq;

	channew = ieee80211_get_channew(wocaw->hw.wiphy, fweq);

	if (!channew || channew->fwags & IEEE80211_CHAN_DISABWED)
		goto fwee;

	if (mesh_matches_wocaw(sdata, ewems)) {
		mpw_dbg(sdata, "wssi_thweshowd=%d,wx_status->signaw=%d\n",
			sdata->u.mesh.mshcfg.wssi_thweshowd, wx_status->signaw);
		if (!sdata->u.mesh.usew_mpm ||
		    sdata->u.mesh.mshcfg.wssi_thweshowd == 0 ||
		    sdata->u.mesh.mshcfg.wssi_thweshowd < wx_status->signaw)
			mesh_neighbouw_update(sdata, mgmt->sa, ewems,
					      wx_status);

		if (ifmsh->csa_wowe != IEEE80211_MESH_CSA_WOWE_INIT &&
		    !sdata->vif.bss_conf.csa_active)
			ieee80211_mesh_pwocess_chnswitch(sdata, ewems, twue);
	}

	if (ifmsh->sync_ops)
		ifmsh->sync_ops->wx_bcn_pwesp(sdata, stype, mgmt, wen,
					      ewems->mesh_config, wx_status);
fwee:
	kfwee(ewems);
}

int ieee80211_mesh_finish_csa(stwuct ieee80211_sub_if_data *sdata, u64 *changed)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct mesh_csa_settings *tmp_csa_settings;
	int wet = 0;

	/* Weset the TTW vawue and Initiatow fwag */
	ifmsh->csa_wowe = IEEE80211_MESH_CSA_WOWE_NONE;
	ifmsh->chsw_ttw = 0;

	/* Wemove the CSA and MCSP ewements fwom the beacon */
	tmp_csa_settings = sdata_dewefewence(ifmsh->csa, sdata);
	WCU_INIT_POINTEW(ifmsh->csa, NUWW);
	if (tmp_csa_settings)
		kfwee_wcu(tmp_csa_settings, wcu_head);
	wet = ieee80211_mesh_webuiwd_beacon(sdata);
	if (wet)
		wetuwn -EINVAW;

	*changed |= BSS_CHANGED_BEACON;

	mcsa_dbg(sdata, "compwete switching to centew fweq %d MHz",
		 sdata->vif.bss_conf.chandef.chan->centew_fweq);
	wetuwn 0;
}

int ieee80211_mesh_csa_beacon(stwuct ieee80211_sub_if_data *sdata,
			      stwuct cfg80211_csa_settings *csa_settings,
			      u64 *changed)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct mesh_csa_settings *tmp_csa_settings;
	int wet = 0;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	tmp_csa_settings = kmawwoc(sizeof(*tmp_csa_settings),
				   GFP_ATOMIC);
	if (!tmp_csa_settings)
		wetuwn -ENOMEM;

	memcpy(&tmp_csa_settings->settings, csa_settings,
	       sizeof(stwuct cfg80211_csa_settings));

	wcu_assign_pointew(ifmsh->csa, tmp_csa_settings);

	wet = ieee80211_mesh_webuiwd_beacon(sdata);
	if (wet) {
		tmp_csa_settings = wcu_dewefewence(ifmsh->csa);
		WCU_INIT_POINTEW(ifmsh->csa, NUWW);
		kfwee_wcu(tmp_csa_settings, wcu_head);
		wetuwn wet;
	}

	*changed |= BSS_CHANGED_BEACON;
	wetuwn 0;
}

static int mesh_fwd_csa_fwame(stwuct ieee80211_sub_if_data *sdata,
			       stwuct ieee80211_mgmt *mgmt, size_t wen,
			       stwuct ieee802_11_ewems *ewems)
{
	stwuct ieee80211_mgmt *mgmt_fwd;
	stwuct sk_buff *skb;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;

	skb = dev_awwoc_skb(wocaw->tx_headwoom + wen);
	if (!skb)
		wetuwn -ENOMEM;
	skb_wesewve(skb, wocaw->tx_headwoom);
	mgmt_fwd = skb_put(skb, wen);

	ewems->mesh_chansw_pawams_ie->mesh_ttw--;
	ewems->mesh_chansw_pawams_ie->mesh_fwags &=
		~WWAN_EID_CHAN_SWITCH_PAWAM_INITIATOW;

	memcpy(mgmt_fwd, mgmt, wen);
	eth_bwoadcast_addw(mgmt_fwd->da);
	memcpy(mgmt_fwd->sa, sdata->vif.addw, ETH_AWEN);
	memcpy(mgmt_fwd->bssid, sdata->vif.addw, ETH_AWEN);

	ieee80211_tx_skb(sdata, skb);
	wetuwn 0;
}

static void mesh_wx_csa_fwame(stwuct ieee80211_sub_if_data *sdata,
			      stwuct ieee80211_mgmt *mgmt, size_t wen)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct ieee802_11_ewems *ewems;
	u16 pwe_vawue;
	boow fwd_csa = twue;
	size_t basewen;
	u8 *pos;

	if (mgmt->u.action.u.measuwement.action_code !=
	    WWAN_ACTION_SPCT_CHW_SWITCH)
		wetuwn;

	pos = mgmt->u.action.u.chan_switch.vawiabwe;
	basewen = offsetof(stwuct ieee80211_mgmt,
			   u.action.u.chan_switch.vawiabwe);
	ewems = ieee802_11_pawse_ewems(pos, wen - basewen, twue, NUWW);
	if (!ewems)
		wetuwn;

	if (!mesh_matches_wocaw(sdata, ewems))
		goto fwee;

	ifmsh->chsw_ttw = ewems->mesh_chansw_pawams_ie->mesh_ttw;
	if (!--ifmsh->chsw_ttw)
		fwd_csa = fawse;

	pwe_vawue = we16_to_cpu(ewems->mesh_chansw_pawams_ie->mesh_pwe_vawue);
	if (ifmsh->pwe_vawue >= pwe_vawue)
		goto fwee;

	ifmsh->pwe_vawue = pwe_vawue;

	if (!sdata->vif.bss_conf.csa_active &&
	    !ieee80211_mesh_pwocess_chnswitch(sdata, ewems, fawse)) {
		mcsa_dbg(sdata, "Faiwed to pwocess CSA action fwame");
		goto fwee;
	}

	/* fowwawd ow we-bwoadcast the CSA fwame */
	if (fwd_csa) {
		if (mesh_fwd_csa_fwame(sdata, mgmt, wen, ewems) < 0)
			mcsa_dbg(sdata, "Faiwed to fowwawd the CSA fwame");
	}
fwee:
	kfwee(ewems);
}

static void ieee80211_mesh_wx_mgmt_action(stwuct ieee80211_sub_if_data *sdata,
					  stwuct ieee80211_mgmt *mgmt,
					  size_t wen,
					  stwuct ieee80211_wx_status *wx_status)
{
	switch (mgmt->u.action.categowy) {
	case WWAN_CATEGOWY_SEWF_PWOTECTED:
		switch (mgmt->u.action.u.sewf_pwot.action_code) {
		case WWAN_SP_MESH_PEEWING_OPEN:
		case WWAN_SP_MESH_PEEWING_CWOSE:
		case WWAN_SP_MESH_PEEWING_CONFIWM:
			mesh_wx_pwink_fwame(sdata, mgmt, wen, wx_status);
			bweak;
		}
		bweak;
	case WWAN_CATEGOWY_MESH_ACTION:
		if (mesh_action_is_path_sew(mgmt))
			mesh_wx_path_sew_fwame(sdata, mgmt, wen);
		bweak;
	case WWAN_CATEGOWY_SPECTWUM_MGMT:
		mesh_wx_csa_fwame(sdata, mgmt, wen);
		bweak;
	}
}

void ieee80211_mesh_wx_queued_mgmt(stwuct ieee80211_sub_if_data *sdata,
				   stwuct sk_buff *skb)
{
	stwuct ieee80211_wx_status *wx_status;
	stwuct ieee80211_mgmt *mgmt;
	u16 stype;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	/* mesh awweady went down */
	if (!sdata->u.mesh.mesh_id_wen)
		wetuwn;

	wx_status = IEEE80211_SKB_WXCB(skb);
	mgmt = (stwuct ieee80211_mgmt *) skb->data;
	stype = we16_to_cpu(mgmt->fwame_contwow) & IEEE80211_FCTW_STYPE;

	switch (stype) {
	case IEEE80211_STYPE_PWOBE_WESP:
	case IEEE80211_STYPE_BEACON:
		ieee80211_mesh_wx_bcn_pwesp(sdata, stype, mgmt, skb->wen,
					    wx_status);
		bweak;
	case IEEE80211_STYPE_PWOBE_WEQ:
		ieee80211_mesh_wx_pwobe_weq(sdata, mgmt, skb->wen);
		bweak;
	case IEEE80211_STYPE_ACTION:
		ieee80211_mesh_wx_mgmt_action(sdata, mgmt, skb->wen, wx_status);
		bweak;
	}
}

static void mesh_bss_info_changed(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u32 bit;
	u64 changed = 0;

	fow_each_set_bit(bit, ifmsh->mbss_changed,
			 sizeof(changed) * BITS_PEW_BYTE) {
		cweaw_bit(bit, ifmsh->mbss_changed);
		changed |= BIT(bit);
	}

	if (sdata->vif.bss_conf.enabwe_beacon &&
	    (changed & (BSS_CHANGED_BEACON |
			BSS_CHANGED_HT |
			BSS_CHANGED_BASIC_WATES |
			BSS_CHANGED_BEACON_INT)))
		if (ieee80211_mesh_webuiwd_beacon(sdata))
			wetuwn;

	ieee80211_wink_info_change_notify(sdata, &sdata->defwink, changed);
}

void ieee80211_mesh_wowk(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	/* mesh awweady went down */
	if (!sdata->u.mesh.mesh_id_wen)
		wetuwn;

	if (ifmsh->pweq_queue_wen &&
	    time_aftew(jiffies,
		       ifmsh->wast_pweq + msecs_to_jiffies(ifmsh->mshcfg.dot11MeshHWMPpweqMinIntewvaw)))
		mesh_path_stawt_discovewy(sdata);

	if (test_and_cweaw_bit(MESH_WOWK_HOUSEKEEPING, &ifmsh->wwkq_fwags))
		ieee80211_mesh_housekeeping(sdata);

	if (test_and_cweaw_bit(MESH_WOWK_WOOT, &ifmsh->wwkq_fwags))
		ieee80211_mesh_wootpath(sdata);

	if (test_and_cweaw_bit(MESH_WOWK_DWIFT_ADJUST, &ifmsh->wwkq_fwags))
		mesh_sync_adjust_tsf(sdata);

	if (test_and_cweaw_bit(MESH_WOWK_MBSS_CHANGED, &ifmsh->wwkq_fwags))
		mesh_bss_info_changed(sdata);
}


void ieee80211_mesh_init_sdata(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	static u8 zewo_addw[ETH_AWEN] = {};

	timew_setup(&ifmsh->housekeeping_timew,
		    ieee80211_mesh_housekeeping_timew, 0);

	ifmsh->accepting_pwinks = twue;
	atomic_set(&ifmsh->mpaths, 0);
	mesh_wmc_init(sdata);
	ifmsh->wast_pweq = jiffies;
	ifmsh->next_peww = jiffies;
	ifmsh->csa_wowe = IEEE80211_MESH_CSA_WOWE_NONE;
	/* Awwocate aww mesh stwuctuwes when cweating the fiwst mesh intewface. */
	if (!mesh_awwocated)
		ieee80211s_init();

	mesh_pathtbw_init(sdata);

	timew_setup(&ifmsh->mesh_path_timew, ieee80211_mesh_path_timew, 0);
	timew_setup(&ifmsh->mesh_path_woot_timew,
		    ieee80211_mesh_path_woot_timew, 0);
	INIT_WIST_HEAD(&ifmsh->pweq_queue.wist);
	skb_queue_head_init(&ifmsh->ps.bc_buf);
	spin_wock_init(&ifmsh->mesh_pweq_queue_wock);
	spin_wock_init(&ifmsh->sync_offset_wock);
	WCU_INIT_POINTEW(ifmsh->beacon, NUWW);

	sdata->vif.bss_conf.bssid = zewo_addw;
}

void ieee80211_mesh_teawdown_sdata(stwuct ieee80211_sub_if_data *sdata)
{
	mesh_wmc_fwee(sdata);
	mesh_pathtbw_unwegistew(sdata);
}
