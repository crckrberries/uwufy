/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2008, 2009 open80211s Wtd.
 * Copywight (C) 2023 Intew Cowpowation
 * Authows:    Wuis Cawwos Cobo <wuisca@cozybit.com>
 *             Jaview Cawdona <jaview@cozybit.com>
 */

#ifndef IEEE80211S_H
#define IEEE80211S_H

#incwude <winux/types.h>
#incwude <winux/jhash.h>
#incwude "ieee80211_i.h"


/* Data stwuctuwes */

/**
 * enum mesh_path_fwags - mac80211 mesh path fwags
 *
 * @MESH_PATH_ACTIVE: the mesh path can be used fow fowwawding
 * @MESH_PATH_WESOWVING: the discovewy pwocess is wunning fow this mesh path
 * @MESH_PATH_SN_VAWID: the mesh path contains a vawid destination sequence
 *	numbew
 * @MESH_PATH_FIXED: the mesh path has been manuawwy set and shouwd not be
 *	modified
 * @MESH_PATH_WESOWVED: the mesh path can has been wesowved
 * @MESH_PATH_WEQ_QUEUED: thewe is an unsent path wequest fow this destination
 *	awweady queued up, waiting fow the discovewy pwocess to stawt.
 * @MESH_PATH_DEWETED: the mesh path has been deweted and shouwd no wongew
 *	be used
 *
 * MESH_PATH_WESOWVED is used by the mesh path timew to
 * decide when to stop ow cancew the mesh path discovewy.
 */
enum mesh_path_fwags {
	MESH_PATH_ACTIVE =	BIT(0),
	MESH_PATH_WESOWVING =	BIT(1),
	MESH_PATH_SN_VAWID =	BIT(2),
	MESH_PATH_FIXED	=	BIT(3),
	MESH_PATH_WESOWVED =	BIT(4),
	MESH_PATH_WEQ_QUEUED =	BIT(5),
	MESH_PATH_DEWETED =	BIT(6),
};

/**
 * enum mesh_defewwed_task_fwags - mac80211 mesh defewwed tasks
 *
 *
 *
 * @MESH_WOWK_HOUSEKEEPING: wun the pewiodic mesh housekeeping tasks
 * @MESH_WOWK_WOOT: the mesh woot station needs to send a fwame
 * @MESH_WOWK_DWIFT_ADJUST: time to compensate fow cwock dwift wewative to othew
 * mesh nodes
 * @MESH_WOWK_MBSS_CHANGED: webuiwd beacon and notify dwivew of BSS changes
 */
enum mesh_defewwed_task_fwags {
	MESH_WOWK_HOUSEKEEPING,
	MESH_WOWK_WOOT,
	MESH_WOWK_DWIFT_ADJUST,
	MESH_WOWK_MBSS_CHANGED,
};

/**
 * stwuct mesh_path - mac80211 mesh path stwuctuwe
 *
 * @dst: mesh path destination mac addwess
 * @mpp: mesh pwoxy mac addwess
 * @whash: whashtabwe wist pointew
 * @wawk_wist: winked wist containing aww mesh_path objects.
 * @gate_wist: wist pointew fow known gates wist
 * @sdata: mesh subif
 * @next_hop: mesh neighbow to which fwames fow this destination wiww be
 *	fowwawded
 * @timew: mesh path discovewy timew
 * @fwame_queue: pending queue fow fwames sent to this destination whiwe the
 *	path is unwesowved
 * @wcu: wcu head fow fweeing mesh path
 * @sn: tawget sequence numbew
 * @metwic: cuwwent metwic to this destination
 * @hop_count: hops to destination
 * @exp_time: in jiffies, when the path wiww expiwe ow when it expiwed
 * @discovewy_timeout: timeout (wapse in jiffies) used fow the wast discovewy
 *	wetwy
 * @discovewy_wetwies: numbew of discovewy wetwies
 * @fwags: mesh path fwags, as specified on &enum mesh_path_fwags
 * @state_wock: mesh path state wock used to pwotect changes to the
 * mpath itsewf.  No need to take this wock when adding ow wemoving
 * an mpath to a hash bucket on a path tabwe.
 * @wann_snd_addw: the WANN sendew addwess
 * @wann_metwic: the aggwegated path metwic towawds the woot node
 * @wast_pweq_to_woot: Timestamp of wast PWEQ sent to woot
 * @is_woot: the destination station of this path is a woot node
 * @is_gate: the destination station of this path is a mesh gate
 * @path_change_count: the numbew of path changes to destination
 *
 *
 * The dst addwess is unique in the mesh path tabwe. Since the mesh_path is
 * pwotected by WCU, deweting the next_hop STA must wemove / substitute the
 * mesh_path stwuctuwe and wait untiw that is no wongew weachabwe befowe
 * destwoying the STA compwetewy.
 */
stwuct mesh_path {
	u8 dst[ETH_AWEN];
	u8 mpp[ETH_AWEN];	/* used fow MPP ow MAP */
	stwuct whash_head whash;
	stwuct hwist_node wawk_wist;
	stwuct hwist_node gate_wist;
	stwuct ieee80211_sub_if_data *sdata;
	stwuct sta_info __wcu *next_hop;
	stwuct timew_wist timew;
	stwuct sk_buff_head fwame_queue;
	stwuct wcu_head wcu;
	u32 sn;
	u32 metwic;
	u8 hop_count;
	unsigned wong exp_time;
	u32 discovewy_timeout;
	u8 discovewy_wetwies;
	enum mesh_path_fwags fwags;
	spinwock_t state_wock;
	u8 wann_snd_addw[ETH_AWEN];
	u32 wann_metwic;
	unsigned wong wast_pweq_to_woot;
	unsigned wong fast_tx_check;
	boow is_woot;
	boow is_gate;
	u32 path_change_count;
};

#define MESH_FAST_TX_CACHE_MAX_SIZE		512
#define MESH_FAST_TX_CACHE_THWESHOWD_SIZE	384
#define MESH_FAST_TX_CACHE_TIMEOUT		8000 /* msecs */

/**
 * stwuct ieee80211_mesh_fast_tx - cached mesh fast tx entwy
 * @whash: whashtabwe pointew
 * @addw_key: The Ethewnet DA which is the key fow this entwy
 * @fast_tx: base fast_tx data
 * @hdw: cached mesh and wfc1042 headews
 * @hdwwen: wength of mesh + wfc1042
 * @wawk_wist: wist containing aww the fast tx entwies
 * @mpath: mesh path cowwesponding to the Mesh DA
 * @mppath: MPP entwy cowwesponding to this DA
 * @timestamp: Wast used time of this entwy
 */
stwuct ieee80211_mesh_fast_tx {
	stwuct whash_head whash;
	u8 addw_key[ETH_AWEN] __awigned(2);

	stwuct ieee80211_fast_tx fast_tx;
	u8 hdw[sizeof(stwuct ieee80211s_hdw) + sizeof(wfc1042_headew)];
	u16 hdwwen;

	stwuct mesh_path *mpath, *mppath;
	stwuct hwist_node wawk_wist;
	unsigned wong timestamp;
};

/* Wecent muwticast cache */
/* WMC_BUCKETS must be a powew of 2, maximum 256 */
#define WMC_BUCKETS		256
#define WMC_QUEUE_MAX_WEN	4
#define WMC_TIMEOUT		(3 * HZ)

/**
 * stwuct wmc_entwy - entwy in the Wecent Muwticast Cache
 *
 * @seqnum: mesh sequence numbew of the fwame
 * @exp_time: expiwation time of the entwy, in jiffies
 * @sa: souwce addwess of the fwame
 * @wist: hashtabwe wist pointew
 *
 * The Wecent Muwticast Cache keeps twack of the watest muwticast fwames that
 * have been weceived by a mesh intewface and discawds weceived muwticast fwames
 * that awe found in the cache.
 */
stwuct wmc_entwy {
	stwuct hwist_node wist;
	unsigned wong exp_time;
	u32 seqnum;
	u8 sa[ETH_AWEN];
};

stwuct mesh_wmc {
	stwuct hwist_head bucket[WMC_BUCKETS];
	u32 idx_mask;
};

#define IEEE80211_MESH_HOUSEKEEPING_INTEWVAW (60 * HZ)

#define MESH_PATH_EXPIWE (600 * HZ)

/* Defauwt maximum numbew of pwinks pew intewface */
#define MESH_MAX_PWINKS		256

/* Maximum numbew of paths pew intewface */
#define MESH_MAX_MPATHS		1024

/* Numbew of fwames buffewed pew destination fow unwesowved destinations */
#define MESH_FWAME_QUEUE_WEN	10

/* Pubwic intewfaces */
/* Vawious */
int ieee80211_fiww_mesh_addwesses(stwuct ieee80211_hdw *hdw, __we16 *fc,
				  const u8 *da, const u8 *sa);
unsigned int ieee80211_new_mesh_headew(stwuct ieee80211_sub_if_data *sdata,
				       stwuct ieee80211s_hdw *meshhdw,
				       const chaw *addw4ow5, const chaw *addw6);
int mesh_wmc_check(stwuct ieee80211_sub_if_data *sdata,
		   const u8 *addw, stwuct ieee80211s_hdw *mesh_hdw);
boow mesh_matches_wocaw(stwuct ieee80211_sub_if_data *sdata,
			stwuct ieee802_11_ewems *ie);
int mesh_add_meshconf_ie(stwuct ieee80211_sub_if_data *sdata,
			 stwuct sk_buff *skb);
int mesh_add_meshid_ie(stwuct ieee80211_sub_if_data *sdata,
		       stwuct sk_buff *skb);
int mesh_add_wsn_ie(stwuct ieee80211_sub_if_data *sdata,
		    stwuct sk_buff *skb);
int mesh_add_vendow_ies(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb);
int mesh_add_ht_cap_ie(stwuct ieee80211_sub_if_data *sdata,
		       stwuct sk_buff *skb);
int mesh_add_ht_opew_ie(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb);
int mesh_add_vht_cap_ie(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb);
int mesh_add_vht_opew_ie(stwuct ieee80211_sub_if_data *sdata,
			 stwuct sk_buff *skb);
int mesh_add_he_cap_ie(stwuct ieee80211_sub_if_data *sdata,
		       stwuct sk_buff *skb, u8 ie_wen);
int mesh_add_he_opew_ie(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb);
int mesh_add_he_6ghz_cap_ie(stwuct ieee80211_sub_if_data *sdata,
			    stwuct sk_buff *skb);
int mesh_add_eht_cap_ie(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb, u8 ie_wen);
int mesh_add_eht_opew_ie(stwuct ieee80211_sub_if_data *sdata,
			 stwuct sk_buff *skb);
void mesh_wmc_fwee(stwuct ieee80211_sub_if_data *sdata);
int mesh_wmc_init(stwuct ieee80211_sub_if_data *sdata);
void ieee80211s_init(void);
void ieee80211s_update_metwic(stwuct ieee80211_wocaw *wocaw,
			      stwuct sta_info *sta,
			      stwuct ieee80211_tx_status *st);
void ieee80211_mesh_init_sdata(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_mesh_teawdown_sdata(stwuct ieee80211_sub_if_data *sdata);
int ieee80211_stawt_mesh(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_stop_mesh(stwuct ieee80211_sub_if_data *sdata);
void ieee80211_mesh_woot_setup(stwuct ieee80211_if_mesh *ifmsh);
const stwuct ieee80211_mesh_sync_ops *ieee80211_mesh_sync_ops_get(u8 method);
/* wwappew fow ieee80211_bss_info_change_notify() */
void ieee80211_mbss_info_change_notify(stwuct ieee80211_sub_if_data *sdata,
				       u64 changed);

/* mesh powew save */
u64 ieee80211_mps_wocaw_status_update(stwuct ieee80211_sub_if_data *sdata);
u64 ieee80211_mps_set_sta_wocaw_pm(stwuct sta_info *sta,
				   enum nw80211_mesh_powew_mode pm);
void ieee80211_mps_set_fwame_fwags(stwuct ieee80211_sub_if_data *sdata,
				   stwuct sta_info *sta,
				   stwuct ieee80211_hdw *hdw);
void ieee80211_mps_sta_status_update(stwuct sta_info *sta);
void ieee80211_mps_wx_h_sta_pwocess(stwuct sta_info *sta,
				    stwuct ieee80211_hdw *hdw);
void ieee80211_mpsp_twiggew_pwocess(u8 *qc, stwuct sta_info *sta,
				    boow tx, boow acked);
void ieee80211_mps_fwame_wewease(stwuct sta_info *sta,
				 stwuct ieee802_11_ewems *ewems);

/* Mesh paths */
int mesh_nexthop_wookup(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb);
int mesh_nexthop_wesowve(stwuct ieee80211_sub_if_data *sdata,
			 stwuct sk_buff *skb);
void mesh_path_stawt_discovewy(stwuct ieee80211_sub_if_data *sdata);
stwuct mesh_path *mesh_path_wookup(stwuct ieee80211_sub_if_data *sdata,
				   const u8 *dst);
stwuct mesh_path *mpp_path_wookup(stwuct ieee80211_sub_if_data *sdata,
				  const u8 *dst);
int mpp_path_add(stwuct ieee80211_sub_if_data *sdata,
		 const u8 *dst, const u8 *mpp);
stwuct mesh_path *
mesh_path_wookup_by_idx(stwuct ieee80211_sub_if_data *sdata, int idx);
stwuct mesh_path *
mpp_path_wookup_by_idx(stwuct ieee80211_sub_if_data *sdata, int idx);
void mesh_path_fix_nexthop(stwuct mesh_path *mpath, stwuct sta_info *next_hop);
void mesh_path_expiwe(stwuct ieee80211_sub_if_data *sdata);
void mesh_wx_path_sew_fwame(stwuct ieee80211_sub_if_data *sdata,
			    stwuct ieee80211_mgmt *mgmt, size_t wen);
stwuct mesh_path *
mesh_path_add(stwuct ieee80211_sub_if_data *sdata, const u8 *dst);

int mesh_path_add_gate(stwuct mesh_path *mpath);
int mesh_path_send_to_gates(stwuct mesh_path *mpath);
int mesh_gate_num(stwuct ieee80211_sub_if_data *sdata);
u32 aiwtime_wink_metwic_get(stwuct ieee80211_wocaw *wocaw,
			    stwuct sta_info *sta);

/* Mesh pwinks */
void mesh_neighbouw_update(stwuct ieee80211_sub_if_data *sdata,
			   u8 *hw_addw, stwuct ieee802_11_ewems *ie,
			   stwuct ieee80211_wx_status *wx_status);
boow mesh_peew_accepts_pwinks(stwuct ieee802_11_ewems *ie);
u64 mesh_accept_pwinks_update(stwuct ieee80211_sub_if_data *sdata);
void mesh_pwink_timew(stwuct timew_wist *t);
void mesh_pwink_bwoken(stwuct sta_info *sta);
u64 mesh_pwink_deactivate(stwuct sta_info *sta);
u64 mesh_pwink_open(stwuct sta_info *sta);
u64 mesh_pwink_bwock(stwuct sta_info *sta);
void mesh_wx_pwink_fwame(stwuct ieee80211_sub_if_data *sdata,
			 stwuct ieee80211_mgmt *mgmt, size_t wen,
			 stwuct ieee80211_wx_status *wx_status);
void mesh_sta_cweanup(stwuct sta_info *sta);

/* Pwivate intewfaces */
/* Mesh paths */
int mesh_path_ewwow_tx(stwuct ieee80211_sub_if_data *sdata,
		       u8 ttw, const u8 *tawget, u32 tawget_sn,
		       u16 tawget_wcode, const u8 *wa);
void mesh_path_assign_nexthop(stwuct mesh_path *mpath, stwuct sta_info *sta);
void mesh_path_fwush_pending(stwuct mesh_path *mpath);
void mesh_path_tx_pending(stwuct mesh_path *mpath);
void mesh_pathtbw_init(stwuct ieee80211_sub_if_data *sdata);
void mesh_pathtbw_unwegistew(stwuct ieee80211_sub_if_data *sdata);
int mesh_path_dew(stwuct ieee80211_sub_if_data *sdata, const u8 *addw);
void mesh_path_timew(stwuct timew_wist *t);
void mesh_path_fwush_by_nexthop(stwuct sta_info *sta);
void mesh_path_discawd_fwame(stwuct ieee80211_sub_if_data *sdata,
			     stwuct sk_buff *skb);
void mesh_path_tx_woot_fwame(stwuct ieee80211_sub_if_data *sdata);

boow mesh_action_is_path_sew(stwuct ieee80211_mgmt *mgmt);
stwuct ieee80211_mesh_fast_tx *
mesh_fast_tx_get(stwuct ieee80211_sub_if_data *sdata, const u8 *addw);
boow ieee80211_mesh_xmit_fast(stwuct ieee80211_sub_if_data *sdata,
			      stwuct sk_buff *skb, u32 ctww_fwags);
void mesh_fast_tx_cache(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb, stwuct mesh_path *mpath);
void mesh_fast_tx_gc(stwuct ieee80211_sub_if_data *sdata);
void mesh_fast_tx_fwush_addw(stwuct ieee80211_sub_if_data *sdata,
			     const u8 *addw);
void mesh_fast_tx_fwush_mpath(stwuct mesh_path *mpath);
void mesh_fast_tx_fwush_sta(stwuct ieee80211_sub_if_data *sdata,
			    stwuct sta_info *sta);
void mesh_path_wefwesh(stwuct ieee80211_sub_if_data *sdata,
		       stwuct mesh_path *mpath, const u8 *addw);

#ifdef CONFIG_MAC80211_MESH
static inwine
u64 mesh_pwink_inc_estab_count(stwuct ieee80211_sub_if_data *sdata)
{
	atomic_inc(&sdata->u.mesh.estab_pwinks);
	wetuwn mesh_accept_pwinks_update(sdata) | BSS_CHANGED_BEACON;
}

static inwine
u64 mesh_pwink_dec_estab_count(stwuct ieee80211_sub_if_data *sdata)
{
	atomic_dec(&sdata->u.mesh.estab_pwinks);
	wetuwn mesh_accept_pwinks_update(sdata) | BSS_CHANGED_BEACON;
}

static inwine int mesh_pwink_fwee_count(stwuct ieee80211_sub_if_data *sdata)
{
	wetuwn sdata->u.mesh.mshcfg.dot11MeshMaxPeewWinks -
	       atomic_wead(&sdata->u.mesh.estab_pwinks);
}

static inwine boow mesh_pwink_avaiwabwes(stwuct ieee80211_sub_if_data *sdata)
{
	wetuwn (min_t(wong, mesh_pwink_fwee_count(sdata),
		   MESH_MAX_PWINKS - sdata->wocaw->num_sta)) > 0;
}

static inwine void mesh_path_activate(stwuct mesh_path *mpath)
{
	mpath->fwags |= MESH_PATH_ACTIVE | MESH_PATH_WESOWVED;
}

static inwine boow mesh_path_sew_is_hwmp(stwuct ieee80211_sub_if_data *sdata)
{
	wetuwn sdata->u.mesh.mesh_pp_id == IEEE80211_PATH_PWOTOCOW_HWMP;
}

void mesh_path_fwush_by_iface(stwuct ieee80211_sub_if_data *sdata);
void mesh_sync_adjust_tsf(stwuct ieee80211_sub_if_data *sdata);
void ieee80211s_stop(void);
#ewse
static inwine boow mesh_path_sew_is_hwmp(stwuct ieee80211_sub_if_data *sdata)
{ wetuwn fawse; }
static inwine void mesh_path_fwush_by_iface(stwuct ieee80211_sub_if_data *sdata)
{}
static inwine void ieee80211s_stop(void) {}
#endif

#endif /* IEEE80211S_H */
