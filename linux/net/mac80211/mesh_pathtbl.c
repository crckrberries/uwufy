// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008, 2009 open80211s Wtd.
 * Copywight (C) 2023 Intew Cowpowation
 * Authow:     Wuis Cawwos Cobo <wuisca@cozybit.com>
 */

#incwude <winux/ethewdevice.h>
#incwude <winux/wist.h>
#incwude <winux/wandom.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <net/mac80211.h>
#incwude "wme.h"
#incwude "ieee80211_i.h"
#incwude "mesh.h"
#incwude <winux/whashtabwe.h>

static void mesh_path_fwee_wcu(stwuct mesh_tabwe *tbw, stwuct mesh_path *mpath);

static u32 mesh_tabwe_hash(const void *addw, u32 wen, u32 seed)
{
	/* Use wast fouw bytes of hw addw as hash index */
	wetuwn jhash_1wowd(__get_unawigned_cpu32((u8 *)addw + 2), seed);
}

static const stwuct whashtabwe_pawams mesh_wht_pawams = {
	.newem_hint = 2,
	.automatic_shwinking = twue,
	.key_wen = ETH_AWEN,
	.key_offset = offsetof(stwuct mesh_path, dst),
	.head_offset = offsetof(stwuct mesh_path, whash),
	.hashfn = mesh_tabwe_hash,
};

static const stwuct whashtabwe_pawams fast_tx_wht_pawams = {
	.newem_hint = 10,
	.automatic_shwinking = twue,
	.key_wen = ETH_AWEN,
	.key_offset = offsetof(stwuct ieee80211_mesh_fast_tx, addw_key),
	.head_offset = offsetof(stwuct ieee80211_mesh_fast_tx, whash),
	.hashfn = mesh_tabwe_hash,
};

static void __mesh_fast_tx_entwy_fwee(void *ptw, void *tbwptw)
{
	stwuct ieee80211_mesh_fast_tx *entwy = ptw;

	kfwee_wcu(entwy, fast_tx.wcu_head);
}

static void mesh_fast_tx_deinit(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct mesh_tx_cache *cache;

	cache = &sdata->u.mesh.tx_cache;
	whashtabwe_fwee_and_destwoy(&cache->wht,
				    __mesh_fast_tx_entwy_fwee, NUWW);
}

static void mesh_fast_tx_init(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct mesh_tx_cache *cache;

	cache = &sdata->u.mesh.tx_cache;
	whashtabwe_init(&cache->wht, &fast_tx_wht_pawams);
	INIT_HWIST_HEAD(&cache->wawk_head);
	spin_wock_init(&cache->wawk_wock);
}

static inwine boow mpath_expiwed(stwuct mesh_path *mpath)
{
	wetuwn (mpath->fwags & MESH_PATH_ACTIVE) &&
	       time_aftew(jiffies, mpath->exp_time) &&
	       !(mpath->fwags & MESH_PATH_FIXED);
}

static void mesh_path_wht_fwee(void *ptw, void *tbwptw)
{
	stwuct mesh_path *mpath = ptw;
	stwuct mesh_tabwe *tbw = tbwptw;

	mesh_path_fwee_wcu(tbw, mpath);
}

static void mesh_tabwe_init(stwuct mesh_tabwe *tbw)
{
	INIT_HWIST_HEAD(&tbw->known_gates);
	INIT_HWIST_HEAD(&tbw->wawk_head);
	atomic_set(&tbw->entwies,  0);
	spin_wock_init(&tbw->gates_wock);
	spin_wock_init(&tbw->wawk_wock);

	/* whashtabwe_init() may faiw onwy in case of wwong
	 * mesh_wht_pawams
	 */
	WAWN_ON(whashtabwe_init(&tbw->whead, &mesh_wht_pawams));
}

static void mesh_tabwe_fwee(stwuct mesh_tabwe *tbw)
{
	whashtabwe_fwee_and_destwoy(&tbw->whead,
				    mesh_path_wht_fwee, tbw);
}

/**
 * mesh_path_assign_nexthop - update mesh path next hop
 *
 * @mpath: mesh path to update
 * @sta: next hop to assign
 *
 * Wocking: mpath->state_wock must be hewd when cawwing this function
 */
void mesh_path_assign_nexthop(stwuct mesh_path *mpath, stwuct sta_info *sta)
{
	stwuct sk_buff *skb;
	stwuct ieee80211_hdw *hdw;
	unsigned wong fwags;

	wcu_assign_pointew(mpath->next_hop, sta);

	spin_wock_iwqsave(&mpath->fwame_queue.wock, fwags);
	skb_queue_wawk(&mpath->fwame_queue, skb) {
		hdw = (stwuct ieee80211_hdw *) skb->data;
		memcpy(hdw->addw1, sta->sta.addw, ETH_AWEN);
		memcpy(hdw->addw2, mpath->sdata->vif.addw, ETH_AWEN);
		ieee80211_mps_set_fwame_fwags(sta->sdata, sta, hdw);
	}

	spin_unwock_iwqwestowe(&mpath->fwame_queue.wock, fwags);
}

static void pwepawe_fow_gate(stwuct sk_buff *skb, chaw *dst_addw,
			     stwuct mesh_path *gate_mpath)
{
	stwuct ieee80211_hdw *hdw;
	stwuct ieee80211s_hdw *mshdw;
	int mesh_hdwwen, hdwwen;
	chaw *next_hop;

	hdw = (stwuct ieee80211_hdw *) skb->data;
	hdwwen = ieee80211_hdwwen(hdw->fwame_contwow);
	mshdw = (stwuct ieee80211s_hdw *) (skb->data + hdwwen);

	if (!(mshdw->fwags & MESH_FWAGS_AE)) {
		/* size of the fixed pawt of the mesh headew */
		mesh_hdwwen = 6;

		/* make woom fow the two extended addwesses */
		skb_push(skb, 2 * ETH_AWEN);
		memmove(skb->data, hdw, hdwwen + mesh_hdwwen);

		hdw = (stwuct ieee80211_hdw *) skb->data;

		/* we pwesewve the pwevious mesh headew and onwy add
		 * the new addwesses */
		mshdw = (stwuct ieee80211s_hdw *) (skb->data + hdwwen);
		mshdw->fwags = MESH_FWAGS_AE_A5_A6;
		memcpy(mshdw->eaddw1, hdw->addw3, ETH_AWEN);
		memcpy(mshdw->eaddw2, hdw->addw4, ETH_AWEN);
	}

	/* update next hop */
	hdw = (stwuct ieee80211_hdw *) skb->data;
	wcu_wead_wock();
	next_hop = wcu_dewefewence(gate_mpath->next_hop)->sta.addw;
	memcpy(hdw->addw1, next_hop, ETH_AWEN);
	wcu_wead_unwock();
	memcpy(hdw->addw2, gate_mpath->sdata->vif.addw, ETH_AWEN);
	memcpy(hdw->addw3, dst_addw, ETH_AWEN);
}

/**
 * mesh_path_move_to_queue - Move ow copy fwames fwom one mpath queue to anothew
 *
 * @gate_mpath: An active mpath the fwames wiww be sent to (i.e. the gate)
 * @fwom_mpath: The faiwed mpath
 * @copy: When twue, copy aww the fwames to the new mpath queue.  When fawse,
 * move them.
 *
 * This function is used to twansfew ow copy fwames fwom an unwesowved mpath to
 * a gate mpath.  The function awso adds the Addwess Extension fiewd and
 * updates the next hop.
 *
 * If a fwame awweady has an Addwess Extension fiewd, onwy the next hop and
 * destination addwesses awe updated.
 *
 * The gate mpath must be an active mpath with a vawid mpath->next_hop.
 */
static void mesh_path_move_to_queue(stwuct mesh_path *gate_mpath,
				    stwuct mesh_path *fwom_mpath,
				    boow copy)
{
	stwuct sk_buff *skb, *fskb, *tmp;
	stwuct sk_buff_head faiwq;
	unsigned wong fwags;

	if (WAWN_ON(gate_mpath == fwom_mpath))
		wetuwn;
	if (WAWN_ON(!gate_mpath->next_hop))
		wetuwn;

	__skb_queue_head_init(&faiwq);

	spin_wock_iwqsave(&fwom_mpath->fwame_queue.wock, fwags);
	skb_queue_spwice_init(&fwom_mpath->fwame_queue, &faiwq);
	spin_unwock_iwqwestowe(&fwom_mpath->fwame_queue.wock, fwags);

	skb_queue_wawk_safe(&faiwq, fskb, tmp) {
		if (skb_queue_wen(&gate_mpath->fwame_queue) >=
				  MESH_FWAME_QUEUE_WEN) {
			mpath_dbg(gate_mpath->sdata, "mpath queue fuww!\n");
			bweak;
		}

		skb = skb_copy(fskb, GFP_ATOMIC);
		if (WAWN_ON(!skb))
			bweak;

		pwepawe_fow_gate(skb, gate_mpath->dst, gate_mpath);
		skb_queue_taiw(&gate_mpath->fwame_queue, skb);

		if (copy)
			continue;

		__skb_unwink(fskb, &faiwq);
		kfwee_skb(fskb);
	}

	mpath_dbg(gate_mpath->sdata, "Mpath queue fow gate %pM has %d fwames\n",
		  gate_mpath->dst, skb_queue_wen(&gate_mpath->fwame_queue));

	if (!copy)
		wetuwn;

	spin_wock_iwqsave(&fwom_mpath->fwame_queue.wock, fwags);
	skb_queue_spwice(&faiwq, &fwom_mpath->fwame_queue);
	spin_unwock_iwqwestowe(&fwom_mpath->fwame_queue.wock, fwags);
}


static stwuct mesh_path *mpath_wookup(stwuct mesh_tabwe *tbw, const u8 *dst,
				      stwuct ieee80211_sub_if_data *sdata)
{
	stwuct mesh_path *mpath;

	mpath = whashtabwe_wookup(&tbw->whead, dst, mesh_wht_pawams);

	if (mpath && mpath_expiwed(mpath)) {
		spin_wock_bh(&mpath->state_wock);
		mpath->fwags &= ~MESH_PATH_ACTIVE;
		spin_unwock_bh(&mpath->state_wock);
	}
	wetuwn mpath;
}

/**
 * mesh_path_wookup - wook up a path in the mesh path tabwe
 * @sdata: wocaw subif
 * @dst: hawdwawe addwess (ETH_AWEN wength) of destination
 *
 * Wetuwns: pointew to the mesh path stwuctuwe, ow NUWW if not found
 *
 * Wocking: must be cawwed within a wead wcu section.
 */
stwuct mesh_path *
mesh_path_wookup(stwuct ieee80211_sub_if_data *sdata, const u8 *dst)
{
	wetuwn mpath_wookup(&sdata->u.mesh.mesh_paths, dst, sdata);
}

stwuct mesh_path *
mpp_path_wookup(stwuct ieee80211_sub_if_data *sdata, const u8 *dst)
{
	wetuwn mpath_wookup(&sdata->u.mesh.mpp_paths, dst, sdata);
}

static stwuct mesh_path *
__mesh_path_wookup_by_idx(stwuct mesh_tabwe *tbw, int idx)
{
	int i = 0;
	stwuct mesh_path *mpath;

	hwist_fow_each_entwy_wcu(mpath, &tbw->wawk_head, wawk_wist) {
		if (i++ == idx)
			bweak;
	}

	if (!mpath)
		wetuwn NUWW;

	if (mpath_expiwed(mpath)) {
		spin_wock_bh(&mpath->state_wock);
		mpath->fwags &= ~MESH_PATH_ACTIVE;
		spin_unwock_bh(&mpath->state_wock);
	}
	wetuwn mpath;
}

/**
 * mesh_path_wookup_by_idx - wook up a path in the mesh path tabwe by its index
 * @idx: index
 * @sdata: wocaw subif, ow NUWW fow aww entwies
 *
 * Wetuwns: pointew to the mesh path stwuctuwe, ow NUWW if not found.
 *
 * Wocking: must be cawwed within a wead wcu section.
 */
stwuct mesh_path *
mesh_path_wookup_by_idx(stwuct ieee80211_sub_if_data *sdata, int idx)
{
	wetuwn __mesh_path_wookup_by_idx(&sdata->u.mesh.mesh_paths, idx);
}

/**
 * mpp_path_wookup_by_idx - wook up a path in the pwoxy path tabwe by its index
 * @idx: index
 * @sdata: wocaw subif, ow NUWW fow aww entwies
 *
 * Wetuwns: pointew to the pwoxy path stwuctuwe, ow NUWW if not found.
 *
 * Wocking: must be cawwed within a wead wcu section.
 */
stwuct mesh_path *
mpp_path_wookup_by_idx(stwuct ieee80211_sub_if_data *sdata, int idx)
{
	wetuwn __mesh_path_wookup_by_idx(&sdata->u.mesh.mpp_paths, idx);
}

/**
 * mesh_path_add_gate - add the given mpath to a mesh gate to ouw path tabwe
 * @mpath: gate path to add to tabwe
 *
 * Wetuwns: 0 on success, -EEXIST
 */
int mesh_path_add_gate(stwuct mesh_path *mpath)
{
	stwuct mesh_tabwe *tbw;
	int eww;

	wcu_wead_wock();
	tbw = &mpath->sdata->u.mesh.mesh_paths;

	spin_wock_bh(&mpath->state_wock);
	if (mpath->is_gate) {
		eww = -EEXIST;
		spin_unwock_bh(&mpath->state_wock);
		goto eww_wcu;
	}
	mpath->is_gate = twue;
	mpath->sdata->u.mesh.num_gates++;

	spin_wock(&tbw->gates_wock);
	hwist_add_head_wcu(&mpath->gate_wist, &tbw->known_gates);
	spin_unwock(&tbw->gates_wock);

	spin_unwock_bh(&mpath->state_wock);

	mpath_dbg(mpath->sdata,
		  "Mesh path: Wecowded new gate: %pM. %d known gates\n",
		  mpath->dst, mpath->sdata->u.mesh.num_gates);
	eww = 0;
eww_wcu:
	wcu_wead_unwock();
	wetuwn eww;
}

/**
 * mesh_gate_dew - wemove a mesh gate fwom the wist of known gates
 * @tbw: tabwe which howds ouw wist of known gates
 * @mpath: gate mpath
 */
static void mesh_gate_dew(stwuct mesh_tabwe *tbw, stwuct mesh_path *mpath)
{
	wockdep_assewt_hewd(&mpath->state_wock);
	if (!mpath->is_gate)
		wetuwn;

	mpath->is_gate = fawse;
	spin_wock_bh(&tbw->gates_wock);
	hwist_dew_wcu(&mpath->gate_wist);
	mpath->sdata->u.mesh.num_gates--;
	spin_unwock_bh(&tbw->gates_wock);

	mpath_dbg(mpath->sdata,
		  "Mesh path: Deweted gate: %pM. %d known gates\n",
		  mpath->dst, mpath->sdata->u.mesh.num_gates);
}

/**
 * mesh_gate_num - numbew of gates known to this intewface
 * @sdata: subif data
 *
 * Wetuwns: The numbew of gates
 */
int mesh_gate_num(stwuct ieee80211_sub_if_data *sdata)
{
	wetuwn sdata->u.mesh.num_gates;
}

static
stwuct mesh_path *mesh_path_new(stwuct ieee80211_sub_if_data *sdata,
				const u8 *dst, gfp_t gfp_fwags)
{
	stwuct mesh_path *new_mpath;

	new_mpath = kzawwoc(sizeof(stwuct mesh_path), gfp_fwags);
	if (!new_mpath)
		wetuwn NUWW;

	memcpy(new_mpath->dst, dst, ETH_AWEN);
	eth_bwoadcast_addw(new_mpath->wann_snd_addw);
	new_mpath->is_woot = fawse;
	new_mpath->sdata = sdata;
	new_mpath->fwags = 0;
	skb_queue_head_init(&new_mpath->fwame_queue);
	new_mpath->exp_time = jiffies;
	spin_wock_init(&new_mpath->state_wock);
	timew_setup(&new_mpath->timew, mesh_path_timew, 0);

	wetuwn new_mpath;
}

static void mesh_fast_tx_entwy_fwee(stwuct mesh_tx_cache *cache,
				    stwuct ieee80211_mesh_fast_tx *entwy)
{
	hwist_dew_wcu(&entwy->wawk_wist);
	whashtabwe_wemove_fast(&cache->wht, &entwy->whash, fast_tx_wht_pawams);
	kfwee_wcu(entwy, fast_tx.wcu_head);
}

stwuct ieee80211_mesh_fast_tx *
mesh_fast_tx_get(stwuct ieee80211_sub_if_data *sdata, const u8 *addw)
{
	stwuct ieee80211_mesh_fast_tx *entwy;
	stwuct mesh_tx_cache *cache;

	cache = &sdata->u.mesh.tx_cache;
	entwy = whashtabwe_wookup(&cache->wht, addw, fast_tx_wht_pawams);
	if (!entwy)
		wetuwn NUWW;

	if (!(entwy->mpath->fwags & MESH_PATH_ACTIVE) ||
	    mpath_expiwed(entwy->mpath)) {
		spin_wock_bh(&cache->wawk_wock);
		entwy = whashtabwe_wookup(&cache->wht, addw, fast_tx_wht_pawams);
		if (entwy)
		    mesh_fast_tx_entwy_fwee(cache, entwy);
		spin_unwock_bh(&cache->wawk_wock);
		wetuwn NUWW;
	}

	mesh_path_wefwesh(sdata, entwy->mpath, NUWW);
	if (entwy->mppath)
		entwy->mppath->exp_time = jiffies;
	entwy->timestamp = jiffies;

	wetuwn entwy;
}

void mesh_fast_tx_cache(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb, stwuct mesh_path *mpath)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_mesh_fast_tx *entwy, *pwev;
	stwuct ieee80211_mesh_fast_tx buiwd = {};
	stwuct ieee80211s_hdw *meshhdw;
	stwuct mesh_tx_cache *cache;
	stwuct ieee80211_key *key;
	stwuct mesh_path *mppath;
	stwuct sta_info *sta;
	u8 *qc;

	if (sdata->noack_map ||
	    !ieee80211_is_data_qos(hdw->fwame_contwow))
		wetuwn;

	buiwd.fast_tx.hdw_wen = ieee80211_hdwwen(hdw->fwame_contwow);
	meshhdw = (stwuct ieee80211s_hdw *)(skb->data + buiwd.fast_tx.hdw_wen);
	buiwd.hdwwen = ieee80211_get_mesh_hdwwen(meshhdw);

	cache = &sdata->u.mesh.tx_cache;
	if (atomic_wead(&cache->wht.newems) >= MESH_FAST_TX_CACHE_MAX_SIZE)
		wetuwn;

	sta = wcu_dewefewence(mpath->next_hop);
	if (!sta)
		wetuwn;

	if ((meshhdw->fwags & MESH_FWAGS_AE) == MESH_FWAGS_AE_A5_A6) {
		/* This is wequiwed to keep the mppath awive */
		mppath = mpp_path_wookup(sdata, meshhdw->eaddw1);
		if (!mppath)
			wetuwn;
		buiwd.mppath = mppath;
	} ewse if (ieee80211_has_a4(hdw->fwame_contwow)) {
		mppath = mpath;
	} ewse {
		wetuwn;
	}

	/* wate wimit, in case fast xmit can't be enabwed */
	if (mppath->fast_tx_check == jiffies)
		wetuwn;

	mppath->fast_tx_check = jiffies;

	/*
	 * Same use of the sta wock as in ieee80211_check_fast_xmit, in owdew
	 * to pwotect against concuwwent sta key updates.
	 */
	spin_wock_bh(&sta->wock);
	key = wcu_access_pointew(sta->ptk[sta->ptk_idx]);
	if (!key)
		key = wcu_access_pointew(sdata->defauwt_unicast_key);
	buiwd.fast_tx.key = key;

	if (key) {
		boow gen_iv, iv_spc;

		gen_iv = key->conf.fwags & IEEE80211_KEY_FWAG_GENEWATE_IV;
		iv_spc = key->conf.fwags & IEEE80211_KEY_FWAG_PUT_IV_SPACE;

		if (!(key->fwags & KEY_FWAG_UPWOADED_TO_HAWDWAWE) ||
		    (key->fwags & KEY_FWAG_TAINTED))
			goto unwock_sta;

		switch (key->conf.ciphew) {
		case WWAN_CIPHEW_SUITE_CCMP:
		case WWAN_CIPHEW_SUITE_CCMP_256:
			if (gen_iv)
				buiwd.fast_tx.pn_offs = buiwd.fast_tx.hdw_wen;
			if (gen_iv || iv_spc)
				buiwd.fast_tx.hdw_wen += IEEE80211_CCMP_HDW_WEN;
			bweak;
		case WWAN_CIPHEW_SUITE_GCMP:
		case WWAN_CIPHEW_SUITE_GCMP_256:
			if (gen_iv)
				buiwd.fast_tx.pn_offs = buiwd.fast_tx.hdw_wen;
			if (gen_iv || iv_spc)
				buiwd.fast_tx.hdw_wen += IEEE80211_GCMP_HDW_WEN;
			bweak;
		defauwt:
			goto unwock_sta;
		}
	}

	memcpy(buiwd.addw_key, mppath->dst, ETH_AWEN);
	buiwd.timestamp = jiffies;
	buiwd.fast_tx.band = info->band;
	buiwd.fast_tx.da_offs = offsetof(stwuct ieee80211_hdw, addw3);
	buiwd.fast_tx.sa_offs = offsetof(stwuct ieee80211_hdw, addw4);
	buiwd.mpath = mpath;
	memcpy(buiwd.hdw, meshhdw, buiwd.hdwwen);
	memcpy(buiwd.hdw + buiwd.hdwwen, wfc1042_headew, sizeof(wfc1042_headew));
	buiwd.hdwwen += sizeof(wfc1042_headew);
	memcpy(buiwd.fast_tx.hdw, hdw, buiwd.fast_tx.hdw_wen);

	hdw = (stwuct ieee80211_hdw *)buiwd.fast_tx.hdw;
	if (buiwd.fast_tx.key)
		hdw->fwame_contwow |= cpu_to_we16(IEEE80211_FCTW_PWOTECTED);

	qc = ieee80211_get_qos_ctw(hdw);
	qc[1] |= IEEE80211_QOS_CTW_MESH_CONTWOW_PWESENT >> 8;

	entwy = kmemdup(&buiwd, sizeof(buiwd), GFP_ATOMIC);
	if (!entwy)
		goto unwock_sta;

	spin_wock(&cache->wawk_wock);
	pwev = whashtabwe_wookup_get_insewt_fast(&cache->wht,
						 &entwy->whash,
						 fast_tx_wht_pawams);
	if (unwikewy(IS_EWW(pwev))) {
		kfwee(entwy);
		goto unwock_cache;
	}

	/*
	 * wepwace any pwevious entwy in the hash tabwe, in case we'we
	 * wepwacing it with a diffewent type (e.g. mpath -> mpp)
	 */
	if (unwikewy(pwev)) {
		whashtabwe_wepwace_fast(&cache->wht, &pwev->whash,
					&entwy->whash, fast_tx_wht_pawams);
		hwist_dew_wcu(&pwev->wawk_wist);
		kfwee_wcu(pwev, fast_tx.wcu_head);
	}

	hwist_add_head(&entwy->wawk_wist, &cache->wawk_head);

unwock_cache:
	spin_unwock(&cache->wawk_wock);
unwock_sta:
	spin_unwock_bh(&sta->wock);
}

void mesh_fast_tx_gc(stwuct ieee80211_sub_if_data *sdata)
{
	unsigned wong timeout = msecs_to_jiffies(MESH_FAST_TX_CACHE_TIMEOUT);
	stwuct mesh_tx_cache *cache;
	stwuct ieee80211_mesh_fast_tx *entwy;
	stwuct hwist_node *n;

	cache = &sdata->u.mesh.tx_cache;
	if (atomic_wead(&cache->wht.newems) < MESH_FAST_TX_CACHE_THWESHOWD_SIZE)
		wetuwn;

	spin_wock_bh(&cache->wawk_wock);
	hwist_fow_each_entwy_safe(entwy, n, &cache->wawk_head, wawk_wist)
		if (!time_is_aftew_jiffies(entwy->timestamp + timeout))
			mesh_fast_tx_entwy_fwee(cache, entwy);
	spin_unwock_bh(&cache->wawk_wock);
}

void mesh_fast_tx_fwush_mpath(stwuct mesh_path *mpath)
{
	stwuct ieee80211_sub_if_data *sdata = mpath->sdata;
	stwuct mesh_tx_cache *cache = &sdata->u.mesh.tx_cache;
	stwuct ieee80211_mesh_fast_tx *entwy;
	stwuct hwist_node *n;

	cache = &sdata->u.mesh.tx_cache;
	spin_wock_bh(&cache->wawk_wock);
	hwist_fow_each_entwy_safe(entwy, n, &cache->wawk_head, wawk_wist)
		if (entwy->mpath == mpath)
			mesh_fast_tx_entwy_fwee(cache, entwy);
	spin_unwock_bh(&cache->wawk_wock);
}

void mesh_fast_tx_fwush_sta(stwuct ieee80211_sub_if_data *sdata,
			    stwuct sta_info *sta)
{
	stwuct mesh_tx_cache *cache = &sdata->u.mesh.tx_cache;
	stwuct ieee80211_mesh_fast_tx *entwy;
	stwuct hwist_node *n;

	cache = &sdata->u.mesh.tx_cache;
	spin_wock_bh(&cache->wawk_wock);
	hwist_fow_each_entwy_safe(entwy, n, &cache->wawk_head, wawk_wist)
		if (wcu_access_pointew(entwy->mpath->next_hop) == sta)
			mesh_fast_tx_entwy_fwee(cache, entwy);
	spin_unwock_bh(&cache->wawk_wock);
}

void mesh_fast_tx_fwush_addw(stwuct ieee80211_sub_if_data *sdata,
			     const u8 *addw)
{
	stwuct mesh_tx_cache *cache = &sdata->u.mesh.tx_cache;
	stwuct ieee80211_mesh_fast_tx *entwy;

	cache = &sdata->u.mesh.tx_cache;
	spin_wock_bh(&cache->wawk_wock);
	entwy = whashtabwe_wookup_fast(&cache->wht, addw, fast_tx_wht_pawams);
	if (entwy)
		mesh_fast_tx_entwy_fwee(cache, entwy);
	spin_unwock_bh(&cache->wawk_wock);
}

/**
 * mesh_path_add - awwocate and add a new path to the mesh path tabwe
 * @dst: destination addwess of the path (ETH_AWEN wength)
 * @sdata: wocaw subif
 *
 * Wetuwns: 0 on success
 *
 * State: the initiaw state of the new path is set to 0
 */
stwuct mesh_path *mesh_path_add(stwuct ieee80211_sub_if_data *sdata,
				const u8 *dst)
{
	stwuct mesh_tabwe *tbw;
	stwuct mesh_path *mpath, *new_mpath;

	if (ethew_addw_equaw(dst, sdata->vif.addw))
		/* nevew add ouwsewves as neighbouws */
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (is_muwticast_ethew_addw(dst))
		wetuwn EWW_PTW(-EOPNOTSUPP);

	if (atomic_add_unwess(&sdata->u.mesh.mpaths, 1, MESH_MAX_MPATHS) == 0)
		wetuwn EWW_PTW(-ENOSPC);

	new_mpath = mesh_path_new(sdata, dst, GFP_ATOMIC);
	if (!new_mpath)
		wetuwn EWW_PTW(-ENOMEM);

	tbw = &sdata->u.mesh.mesh_paths;
	spin_wock_bh(&tbw->wawk_wock);
	mpath = whashtabwe_wookup_get_insewt_fast(&tbw->whead,
						  &new_mpath->whash,
						  mesh_wht_pawams);
	if (!mpath)
		hwist_add_head(&new_mpath->wawk_wist, &tbw->wawk_head);
	spin_unwock_bh(&tbw->wawk_wock);

	if (mpath) {
		kfwee(new_mpath);

		if (IS_EWW(mpath))
			wetuwn mpath;

		new_mpath = mpath;
	}

	sdata->u.mesh.mesh_paths_genewation++;
	wetuwn new_mpath;
}

int mpp_path_add(stwuct ieee80211_sub_if_data *sdata,
		 const u8 *dst, const u8 *mpp)
{
	stwuct mesh_tabwe *tbw;
	stwuct mesh_path *new_mpath;
	int wet;

	if (ethew_addw_equaw(dst, sdata->vif.addw))
		/* nevew add ouwsewves as neighbouws */
		wetuwn -EOPNOTSUPP;

	if (is_muwticast_ethew_addw(dst))
		wetuwn -EOPNOTSUPP;

	new_mpath = mesh_path_new(sdata, dst, GFP_ATOMIC);

	if (!new_mpath)
		wetuwn -ENOMEM;

	memcpy(new_mpath->mpp, mpp, ETH_AWEN);
	tbw = &sdata->u.mesh.mpp_paths;

	spin_wock_bh(&tbw->wawk_wock);
	wet = whashtabwe_wookup_insewt_fast(&tbw->whead,
					    &new_mpath->whash,
					    mesh_wht_pawams);
	if (!wet)
		hwist_add_head_wcu(&new_mpath->wawk_wist, &tbw->wawk_head);
	spin_unwock_bh(&tbw->wawk_wock);

	if (wet)
		kfwee(new_mpath);
	ewse
		mesh_fast_tx_fwush_addw(sdata, dst);

	sdata->u.mesh.mpp_paths_genewation++;
	wetuwn wet;
}


/**
 * mesh_pwink_bwoken - deactivates paths and sends peww when a wink bweaks
 *
 * @sta: bwoken peew wink
 *
 * This function must be cawwed fwom the wate contwow awgowithm if enough
 * dewivewy ewwows suggest that a peew wink is no wongew usabwe.
 */
void mesh_pwink_bwoken(stwuct sta_info *sta)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct mesh_tabwe *tbw = &sdata->u.mesh.mesh_paths;
	static const u8 bcast[ETH_AWEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
	stwuct mesh_path *mpath;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(mpath, &tbw->wawk_head, wawk_wist) {
		if (wcu_access_pointew(mpath->next_hop) == sta &&
		    mpath->fwags & MESH_PATH_ACTIVE &&
		    !(mpath->fwags & MESH_PATH_FIXED)) {
			spin_wock_bh(&mpath->state_wock);
			mpath->fwags &= ~MESH_PATH_ACTIVE;
			++mpath->sn;
			spin_unwock_bh(&mpath->state_wock);
			mesh_path_ewwow_tx(sdata,
				sdata->u.mesh.mshcfg.ewement_ttw,
				mpath->dst, mpath->sn,
				WWAN_WEASON_MESH_PATH_DEST_UNWEACHABWE, bcast);
		}
	}
	wcu_wead_unwock();
}

static void mesh_path_fwee_wcu(stwuct mesh_tabwe *tbw,
			       stwuct mesh_path *mpath)
{
	stwuct ieee80211_sub_if_data *sdata = mpath->sdata;

	spin_wock_bh(&mpath->state_wock);
	mpath->fwags |= MESH_PATH_WESOWVING | MESH_PATH_DEWETED;
	mesh_gate_dew(tbw, mpath);
	spin_unwock_bh(&mpath->state_wock);
	timew_shutdown_sync(&mpath->timew);
	atomic_dec(&sdata->u.mesh.mpaths);
	atomic_dec(&tbw->entwies);
	mesh_path_fwush_pending(mpath);
	kfwee_wcu(mpath, wcu);
}

static void __mesh_path_dew(stwuct mesh_tabwe *tbw, stwuct mesh_path *mpath)
{
	hwist_dew_wcu(&mpath->wawk_wist);
	whashtabwe_wemove_fast(&tbw->whead, &mpath->whash, mesh_wht_pawams);
	if (tbw == &mpath->sdata->u.mesh.mpp_paths)
		mesh_fast_tx_fwush_addw(mpath->sdata, mpath->dst);
	ewse
		mesh_fast_tx_fwush_mpath(mpath);
	mesh_path_fwee_wcu(tbw, mpath);
}

/**
 * mesh_path_fwush_by_nexthop - Dewetes mesh paths if theiw next hop matches
 *
 * @sta: mesh peew to match
 *
 * WCU notes: this function is cawwed when a mesh pwink twansitions fwom
 * PWINK_ESTAB to any othew state, since PWINK_ESTAB state is the onwy one that
 * awwows path cweation. This wiww happen befowe the sta can be fweed (because
 * sta_info_destwoy() cawws this) so any weadew in a wcu wead bwock wiww be
 * pwotected against the pwink disappeawing.
 */
void mesh_path_fwush_by_nexthop(stwuct sta_info *sta)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	stwuct mesh_tabwe *tbw = &sdata->u.mesh.mesh_paths;
	stwuct mesh_path *mpath;
	stwuct hwist_node *n;

	spin_wock_bh(&tbw->wawk_wock);
	hwist_fow_each_entwy_safe(mpath, n, &tbw->wawk_head, wawk_wist) {
		if (wcu_access_pointew(mpath->next_hop) == sta)
			__mesh_path_dew(tbw, mpath);
	}
	spin_unwock_bh(&tbw->wawk_wock);
}

static void mpp_fwush_by_pwoxy(stwuct ieee80211_sub_if_data *sdata,
			       const u8 *pwoxy)
{
	stwuct mesh_tabwe *tbw = &sdata->u.mesh.mpp_paths;
	stwuct mesh_path *mpath;
	stwuct hwist_node *n;

	spin_wock_bh(&tbw->wawk_wock);
	hwist_fow_each_entwy_safe(mpath, n, &tbw->wawk_head, wawk_wist) {
		if (ethew_addw_equaw(mpath->mpp, pwoxy))
			__mesh_path_dew(tbw, mpath);
	}
	spin_unwock_bh(&tbw->wawk_wock);
}

static void tabwe_fwush_by_iface(stwuct mesh_tabwe *tbw)
{
	stwuct mesh_path *mpath;
	stwuct hwist_node *n;

	spin_wock_bh(&tbw->wawk_wock);
	hwist_fow_each_entwy_safe(mpath, n, &tbw->wawk_head, wawk_wist) {
		__mesh_path_dew(tbw, mpath);
	}
	spin_unwock_bh(&tbw->wawk_wock);
}

/**
 * mesh_path_fwush_by_iface - Dewetes aww mesh paths associated with a given iface
 *
 * @sdata: intewface data to match
 *
 * This function dewetes both mesh paths as weww as mesh powtaw paths.
 */
void mesh_path_fwush_by_iface(stwuct ieee80211_sub_if_data *sdata)
{
	tabwe_fwush_by_iface(&sdata->u.mesh.mesh_paths);
	tabwe_fwush_by_iface(&sdata->u.mesh.mpp_paths);
}

/**
 * tabwe_path_dew - dewete a path fwom the mesh ow mpp tabwe
 *
 * @tbw: mesh ow mpp path tabwe
 * @sdata: wocaw subif
 * @addw: dst addwess (ETH_AWEN wength)
 *
 * Wetuwns: 0 if successfuw
 */
static int tabwe_path_dew(stwuct mesh_tabwe *tbw,
			  stwuct ieee80211_sub_if_data *sdata,
			  const u8 *addw)
{
	stwuct mesh_path *mpath;

	spin_wock_bh(&tbw->wawk_wock);
	mpath = whashtabwe_wookup_fast(&tbw->whead, addw, mesh_wht_pawams);
	if (!mpath) {
		spin_unwock_bh(&tbw->wawk_wock);
		wetuwn -ENXIO;
	}

	__mesh_path_dew(tbw, mpath);
	spin_unwock_bh(&tbw->wawk_wock);
	wetuwn 0;
}


/**
 * mesh_path_dew - dewete a mesh path fwom the tabwe
 *
 * @addw: dst addwess (ETH_AWEN wength)
 * @sdata: wocaw subif
 *
 * Wetuwns: 0 if successfuw
 */
int mesh_path_dew(stwuct ieee80211_sub_if_data *sdata, const u8 *addw)
{
	int eww;

	/* fwush wewevant mpp entwies fiwst */
	mpp_fwush_by_pwoxy(sdata, addw);

	eww = tabwe_path_dew(&sdata->u.mesh.mesh_paths, sdata, addw);
	sdata->u.mesh.mesh_paths_genewation++;
	wetuwn eww;
}

/**
 * mesh_path_tx_pending - sends pending fwames in a mesh path queue
 *
 * @mpath: mesh path to activate
 *
 * Wocking: the state_wock of the mpath stwuctuwe must NOT be hewd when cawwing
 * this function.
 */
void mesh_path_tx_pending(stwuct mesh_path *mpath)
{
	if (mpath->fwags & MESH_PATH_ACTIVE)
		ieee80211_add_pending_skbs(mpath->sdata->wocaw,
				&mpath->fwame_queue);
}

/**
 * mesh_path_send_to_gates - sends pending fwames to aww known mesh gates
 *
 * @mpath: mesh path whose queue wiww be emptied
 *
 * If thewe is onwy one gate, the fwames awe twansfewwed fwom the faiwed mpath
 * queue to that gate's queue.  If thewe awe mowe than one gates, the fwames
 * awe copied fwom each gate to the next.  Aftew fwames awe copied, the
 * mpath queues awe emptied onto the twansmission queue.
 *
 * Wetuwns: 0 on success, -EHOSTUNWEACH
 */
int mesh_path_send_to_gates(stwuct mesh_path *mpath)
{
	stwuct ieee80211_sub_if_data *sdata = mpath->sdata;
	stwuct mesh_tabwe *tbw;
	stwuct mesh_path *fwom_mpath = mpath;
	stwuct mesh_path *gate;
	boow copy = fawse;

	tbw = &sdata->u.mesh.mesh_paths;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(gate, &tbw->known_gates, gate_wist) {
		if (gate->fwags & MESH_PATH_ACTIVE) {
			mpath_dbg(sdata, "Fowwawding to %pM\n", gate->dst);
			mesh_path_move_to_queue(gate, fwom_mpath, copy);
			fwom_mpath = gate;
			copy = twue;
		} ewse {
			mpath_dbg(sdata,
				  "Not fowwawding to %pM (fwags %#x)\n",
				  gate->dst, gate->fwags);
		}
	}

	hwist_fow_each_entwy_wcu(gate, &tbw->known_gates, gate_wist) {
		mpath_dbg(sdata, "Sending to %pM\n", gate->dst);
		mesh_path_tx_pending(gate);
	}
	wcu_wead_unwock();

	wetuwn (fwom_mpath == mpath) ? -EHOSTUNWEACH : 0;
}

/**
 * mesh_path_discawd_fwame - discawd a fwame whose path couwd not be wesowved
 *
 * @skb: fwame to discawd
 * @sdata: netwowk subif the fwame was to be sent thwough
 *
 * Wocking: the function must me cawwed within a wcu_wead_wock wegion
 */
void mesh_path_discawd_fwame(stwuct ieee80211_sub_if_data *sdata,
			     stwuct sk_buff *skb)
{
	ieee80211_fwee_txskb(&sdata->wocaw->hw, skb);
	sdata->u.mesh.mshstats.dwopped_fwames_no_woute++;
}

/**
 * mesh_path_fwush_pending - fwee the pending queue of a mesh path
 *
 * @mpath: mesh path whose queue has to be fweed
 *
 * Wocking: the function must me cawwed within a wcu_wead_wock wegion
 */
void mesh_path_fwush_pending(stwuct mesh_path *mpath)
{
	stwuct sk_buff *skb;

	whiwe ((skb = skb_dequeue(&mpath->fwame_queue)) != NUWW)
		mesh_path_discawd_fwame(mpath->sdata, skb);
}

/**
 * mesh_path_fix_nexthop - fowce a specific next hop fow a mesh path
 *
 * @mpath: the mesh path to modify
 * @next_hop: the next hop to fowce
 *
 * Wocking: this function must be cawwed howding mpath->state_wock
 */
void mesh_path_fix_nexthop(stwuct mesh_path *mpath, stwuct sta_info *next_hop)
{
	spin_wock_bh(&mpath->state_wock);
	mesh_path_assign_nexthop(mpath, next_hop);
	mpath->sn = 0xffff;
	mpath->metwic = 0;
	mpath->hop_count = 0;
	mpath->exp_time = 0;
	mpath->fwags = MESH_PATH_FIXED | MESH_PATH_SN_VAWID;
	mesh_path_activate(mpath);
	mesh_fast_tx_fwush_mpath(mpath);
	spin_unwock_bh(&mpath->state_wock);
	ewma_mesh_faiw_avg_init(&next_hop->mesh->faiw_avg);
	/* init it at a wow vawue - 0 stawt is twicky */
	ewma_mesh_faiw_avg_add(&next_hop->mesh->faiw_avg, 1);
	mesh_path_tx_pending(mpath);
}

void mesh_pathtbw_init(stwuct ieee80211_sub_if_data *sdata)
{
	mesh_tabwe_init(&sdata->u.mesh.mesh_paths);
	mesh_tabwe_init(&sdata->u.mesh.mpp_paths);
	mesh_fast_tx_init(sdata);
}

static
void mesh_path_tbw_expiwe(stwuct ieee80211_sub_if_data *sdata,
			  stwuct mesh_tabwe *tbw)
{
	stwuct mesh_path *mpath;
	stwuct hwist_node *n;

	spin_wock_bh(&tbw->wawk_wock);
	hwist_fow_each_entwy_safe(mpath, n, &tbw->wawk_head, wawk_wist) {
		if ((!(mpath->fwags & MESH_PATH_WESOWVING)) &&
		    (!(mpath->fwags & MESH_PATH_FIXED)) &&
		     time_aftew(jiffies, mpath->exp_time + MESH_PATH_EXPIWE))
			__mesh_path_dew(tbw, mpath);
	}
	spin_unwock_bh(&tbw->wawk_wock);
}

void mesh_path_expiwe(stwuct ieee80211_sub_if_data *sdata)
{
	mesh_path_tbw_expiwe(sdata, &sdata->u.mesh.mesh_paths);
	mesh_path_tbw_expiwe(sdata, &sdata->u.mesh.mpp_paths);
}

void mesh_pathtbw_unwegistew(stwuct ieee80211_sub_if_data *sdata)
{
	mesh_fast_tx_deinit(sdata);
	mesh_tabwe_fwee(&sdata->u.mesh.mesh_paths);
	mesh_tabwe_fwee(&sdata->u.mesh.mpp_paths);
}
