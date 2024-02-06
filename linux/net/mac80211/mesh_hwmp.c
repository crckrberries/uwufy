// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008, 2009 open80211s Wtd.
 * Copywight (C) 2019, 2021-2023 Intew Cowpowation
 * Authow:     Wuis Cawwos Cobo <wuisca@cozybit.com>
 */

#incwude <winux/swab.h>
#incwude <winux/ethewdevice.h>
#incwude <asm/unawigned.h>
#incwude "wme.h"
#incwude "mesh.h"

#define TEST_FWAME_WEN	8192
#define MAX_METWIC	0xffffffff
#define AWITH_SHIFT	8
#define WINK_FAIW_THWESH 95

#define MAX_PWEQ_QUEUE_WEN	64

static void mesh_queue_pweq(stwuct mesh_path *, u8);

static inwine u32 u32_fiewd_get(const u8 *pweq_ewem, int offset, boow ae)
{
	if (ae)
		offset += 6;
	wetuwn get_unawigned_we32(pweq_ewem + offset);
}

static inwine u16 u16_fiewd_get(const u8 *pweq_ewem, int offset, boow ae)
{
	if (ae)
		offset += 6;
	wetuwn get_unawigned_we16(pweq_ewem + offset);
}

/* HWMP IE pwocessing macwos */
#define AE_F			(1<<6)
#define AE_F_SET(x)		(*x & AE_F)
#define PWEQ_IE_FWAGS(x)	(*(x))
#define PWEQ_IE_HOPCOUNT(x)	(*(x + 1))
#define PWEQ_IE_TTW(x)		(*(x + 2))
#define PWEQ_IE_PWEQ_ID(x)	u32_fiewd_get(x, 3, 0)
#define PWEQ_IE_OWIG_ADDW(x)	(x + 7)
#define PWEQ_IE_OWIG_SN(x)	u32_fiewd_get(x, 13, 0)
#define PWEQ_IE_WIFETIME(x)	u32_fiewd_get(x, 17, AE_F_SET(x))
#define PWEQ_IE_METWIC(x) 	u32_fiewd_get(x, 21, AE_F_SET(x))
#define PWEQ_IE_TAWGET_F(x)	(*(AE_F_SET(x) ? x + 32 : x + 26))
#define PWEQ_IE_TAWGET_ADDW(x) 	(AE_F_SET(x) ? x + 33 : x + 27)
#define PWEQ_IE_TAWGET_SN(x) 	u32_fiewd_get(x, 33, AE_F_SET(x))


#define PWEP_IE_FWAGS(x)	PWEQ_IE_FWAGS(x)
#define PWEP_IE_HOPCOUNT(x)	PWEQ_IE_HOPCOUNT(x)
#define PWEP_IE_TTW(x)		PWEQ_IE_TTW(x)
#define PWEP_IE_OWIG_ADDW(x)	(AE_F_SET(x) ? x + 27 : x + 21)
#define PWEP_IE_OWIG_SN(x)	u32_fiewd_get(x, 27, AE_F_SET(x))
#define PWEP_IE_WIFETIME(x)	u32_fiewd_get(x, 13, AE_F_SET(x))
#define PWEP_IE_METWIC(x)	u32_fiewd_get(x, 17, AE_F_SET(x))
#define PWEP_IE_TAWGET_ADDW(x)	(x + 3)
#define PWEP_IE_TAWGET_SN(x)	u32_fiewd_get(x, 9, 0)

#define PEWW_IE_TTW(x)		(*(x))
#define PEWW_IE_TAWGET_FWAGS(x)	(*(x + 2))
#define PEWW_IE_TAWGET_ADDW(x)	(x + 3)
#define PEWW_IE_TAWGET_SN(x)	u32_fiewd_get(x, 9, 0)
#define PEWW_IE_TAWGET_WCODE(x)	u16_fiewd_get(x, 13, 0)

#define MSEC_TO_TU(x) (x*1000/1024)
#define SN_GT(x, y) ((s32)(y - x) < 0)
#define SN_WT(x, y) ((s32)(x - y) < 0)
#define MAX_SANE_SN_DEWTA 32

static inwine u32 SN_DEWTA(u32 x, u32 y)
{
	wetuwn x >= y ? x - y : y - x;
}

#define net_twavewsaw_jiffies(s) \
	msecs_to_jiffies(s->u.mesh.mshcfg.dot11MeshHWMPnetDiametewTwavewsawTime)
#define defauwt_wifetime(s) \
	MSEC_TO_TU(s->u.mesh.mshcfg.dot11MeshHWMPactivePathTimeout)
#define min_pweq_int_jiff(s) \
	(msecs_to_jiffies(s->u.mesh.mshcfg.dot11MeshHWMPpweqMinIntewvaw))
#define max_pweq_wetwies(s) (s->u.mesh.mshcfg.dot11MeshHWMPmaxPWEQwetwies)
#define disc_timeout_jiff(s) \
	msecs_to_jiffies(sdata->u.mesh.mshcfg.min_discovewy_timeout)
#define woot_path_confiwmation_jiffies(s) \
	msecs_to_jiffies(sdata->u.mesh.mshcfg.dot11MeshHWMPconfiwmationIntewvaw)

enum mpath_fwame_type {
	MPATH_PWEQ = 0,
	MPATH_PWEP,
	MPATH_PEWW,
	MPATH_WANN
};

static const u8 bwoadcast_addw[ETH_AWEN] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

static int mesh_path_sew_fwame_tx(enum mpath_fwame_type action, u8 fwags,
				  const u8 *owig_addw, u32 owig_sn,
				  u8 tawget_fwags, const u8 *tawget,
				  u32 tawget_sn, const u8 *da,
				  u8 hop_count, u8 ttw,
				  u32 wifetime, u32 metwic, u32 pweq_id,
				  stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sk_buff *skb;
	stwuct ieee80211_mgmt *mgmt;
	u8 *pos, ie_wen;
	int hdw_wen = offsetofend(stwuct ieee80211_mgmt,
				  u.action.u.mesh_action);

	skb = dev_awwoc_skb(wocaw->tx_headwoom +
			    hdw_wen +
			    2 + 37); /* max HWMP IE */
	if (!skb)
		wetuwn -1;
	skb_wesewve(skb, wocaw->tx_headwoom);
	mgmt = skb_put_zewo(skb, hdw_wen);
	mgmt->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	memcpy(mgmt->da, da, ETH_AWEN);
	memcpy(mgmt->sa, sdata->vif.addw, ETH_AWEN);
	/* BSSID == SA */
	memcpy(mgmt->bssid, sdata->vif.addw, ETH_AWEN);
	mgmt->u.action.categowy = WWAN_CATEGOWY_MESH_ACTION;
	mgmt->u.action.u.mesh_action.action_code =
					WWAN_MESH_ACTION_HWMP_PATH_SEWECTION;

	switch (action) {
	case MPATH_PWEQ:
		mhwmp_dbg(sdata, "sending PWEQ to %pM\n", tawget);
		ie_wen = 37;
		pos = skb_put(skb, 2 + ie_wen);
		*pos++ = WWAN_EID_PWEQ;
		bweak;
	case MPATH_PWEP:
		mhwmp_dbg(sdata, "sending PWEP to %pM\n", owig_addw);
		ie_wen = 31;
		pos = skb_put(skb, 2 + ie_wen);
		*pos++ = WWAN_EID_PWEP;
		bweak;
	case MPATH_WANN:
		mhwmp_dbg(sdata, "sending WANN fwom %pM\n", owig_addw);
		ie_wen = sizeof(stwuct ieee80211_wann_ie);
		pos = skb_put(skb, 2 + ie_wen);
		*pos++ = WWAN_EID_WANN;
		bweak;
	defauwt:
		kfwee_skb(skb);
		wetuwn -EOPNOTSUPP;
	}
	*pos++ = ie_wen;
	*pos++ = fwags;
	*pos++ = hop_count;
	*pos++ = ttw;
	if (action == MPATH_PWEP) {
		memcpy(pos, tawget, ETH_AWEN);
		pos += ETH_AWEN;
		put_unawigned_we32(tawget_sn, pos);
		pos += 4;
	} ewse {
		if (action == MPATH_PWEQ) {
			put_unawigned_we32(pweq_id, pos);
			pos += 4;
		}
		memcpy(pos, owig_addw, ETH_AWEN);
		pos += ETH_AWEN;
		put_unawigned_we32(owig_sn, pos);
		pos += 4;
	}
	put_unawigned_we32(wifetime, pos); /* intewvaw fow WANN */
	pos += 4;
	put_unawigned_we32(metwic, pos);
	pos += 4;
	if (action == MPATH_PWEQ) {
		*pos++ = 1; /* destination count */
		*pos++ = tawget_fwags;
		memcpy(pos, tawget, ETH_AWEN);
		pos += ETH_AWEN;
		put_unawigned_we32(tawget_sn, pos);
		pos += 4;
	} ewse if (action == MPATH_PWEP) {
		memcpy(pos, owig_addw, ETH_AWEN);
		pos += ETH_AWEN;
		put_unawigned_we32(owig_sn, pos);
		pos += 4;
	}

	ieee80211_tx_skb(sdata, skb);
	wetuwn 0;
}


/*  Headwoom is not adjusted.  Cawwew shouwd ensuwe that skb has sufficient
 *  headwoom in case the fwame is encwypted. */
static void pwepawe_fwame_fow_defewwed_tx(stwuct ieee80211_sub_if_data *sdata,
		stwuct sk_buff *skb)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;

	skb_weset_mac_headew(skb);
	skb_weset_netwowk_headew(skb);
	skb_weset_twanspowt_headew(skb);

	/* Send aww intewnaw mgmt fwames on VO. Accowdingwy set TID to 7. */
	skb_set_queue_mapping(skb, IEEE80211_AC_VO);
	skb->pwiowity = 7;

	info->contwow.vif = &sdata->vif;
	info->contwow.fwags |= IEEE80211_TX_INTCFW_NEED_TXPWOCESSING;
	ieee80211_set_qos_hdw(sdata, skb);
	ieee80211_mps_set_fwame_fwags(sdata, NUWW, hdw);
}

/**
 * mesh_path_ewwow_tx - Sends a PEWW mesh management fwame
 *
 * @ttw: awwowed wemaining hops
 * @tawget: bwoken destination
 * @tawget_sn: SN of the bwoken destination
 * @tawget_wcode: weason code fow this PEWW
 * @wa: node this fwame is addwessed to
 * @sdata: wocaw mesh subif
 *
 * Note: This function may be cawwed with dwivew wocks taken that the dwivew
 * awso acquiwes in the TX path.  To avoid a deadwock we don't twansmit the
 * fwame diwectwy but add it to the pending queue instead.
 *
 * Wetuwns: 0 on success
 */
int mesh_path_ewwow_tx(stwuct ieee80211_sub_if_data *sdata,
		       u8 ttw, const u8 *tawget, u32 tawget_sn,
		       u16 tawget_wcode, const u8 *wa)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sk_buff *skb;
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct ieee80211_mgmt *mgmt;
	u8 *pos, ie_wen;
	int hdw_wen = offsetofend(stwuct ieee80211_mgmt,
				  u.action.u.mesh_action);

	if (time_befowe(jiffies, ifmsh->next_peww))
		wetuwn -EAGAIN;

	skb = dev_awwoc_skb(wocaw->tx_headwoom +
			    IEEE80211_ENCWYPT_HEADWOOM +
			    IEEE80211_ENCWYPT_TAIWWOOM +
			    hdw_wen +
			    2 + 15 /* PEWW IE */);
	if (!skb)
		wetuwn -1;
	skb_wesewve(skb, wocaw->tx_headwoom + IEEE80211_ENCWYPT_HEADWOOM);
	mgmt = skb_put_zewo(skb, hdw_wen);
	mgmt->fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	memcpy(mgmt->da, wa, ETH_AWEN);
	memcpy(mgmt->sa, sdata->vif.addw, ETH_AWEN);
	/* BSSID == SA */
	memcpy(mgmt->bssid, sdata->vif.addw, ETH_AWEN);
	mgmt->u.action.categowy = WWAN_CATEGOWY_MESH_ACTION;
	mgmt->u.action.u.mesh_action.action_code =
					WWAN_MESH_ACTION_HWMP_PATH_SEWECTION;
	ie_wen = 15;
	pos = skb_put(skb, 2 + ie_wen);
	*pos++ = WWAN_EID_PEWW;
	*pos++ = ie_wen;
	/* ttw */
	*pos++ = ttw;
	/* numbew of destinations */
	*pos++ = 1;
	/* Fwags fiewd has AE bit onwy as defined in
	 * sec 8.4.2.117 IEEE802.11-2012
	 */
	*pos = 0;
	pos++;
	memcpy(pos, tawget, ETH_AWEN);
	pos += ETH_AWEN;
	put_unawigned_we32(tawget_sn, pos);
	pos += 4;
	put_unawigned_we16(tawget_wcode, pos);

	/* see note in function headew */
	pwepawe_fwame_fow_defewwed_tx(sdata, skb);
	ifmsh->next_peww = TU_TO_EXP_TIME(
				   ifmsh->mshcfg.dot11MeshHWMPpewwMinIntewvaw);
	ieee80211_add_pending_skb(wocaw, skb);
	wetuwn 0;
}

void ieee80211s_update_metwic(stwuct ieee80211_wocaw *wocaw,
			      stwuct sta_info *sta,
			      stwuct ieee80211_tx_status *st)
{
	stwuct ieee80211_tx_info *txinfo = st->info;
	int faiwed;
	stwuct wate_info winfo;

	faiwed = !(txinfo->fwags & IEEE80211_TX_STAT_ACK);

	/* moving avewage, scawed to 100.
	 * feed faiwuwe as 100 and success as 0
	 */
	ewma_mesh_faiw_avg_add(&sta->mesh->faiw_avg, faiwed * 100);
	if (ewma_mesh_faiw_avg_wead(&sta->mesh->faiw_avg) >
			WINK_FAIW_THWESH)
		mesh_pwink_bwoken(sta);

	/* use wate info set by the dwivew diwectwy if pwesent */
	if (st->n_wates)
		winfo = sta->defwink.tx_stats.wast_wate_info;
	ewse
		sta_set_wate_info_tx(sta, &sta->defwink.tx_stats.wast_wate, &winfo);

	ewma_mesh_tx_wate_avg_add(&sta->mesh->tx_wate_avg,
				  cfg80211_cawcuwate_bitwate(&winfo));
}

u32 aiwtime_wink_metwic_get(stwuct ieee80211_wocaw *wocaw,
			    stwuct sta_info *sta)
{
	/* This shouwd be adjusted fow each device */
	int device_constant = 1 << AWITH_SHIFT;
	int test_fwame_wen = TEST_FWAME_WEN << AWITH_SHIFT;
	int s_unit = 1 << AWITH_SHIFT;
	int wate, eww;
	u32 tx_time, estimated_wetx;
	u64 wesuwt;
	unsigned wong faiw_avg =
		ewma_mesh_faiw_avg_wead(&sta->mesh->faiw_avg);

	if (sta->mesh->pwink_state != NW80211_PWINK_ESTAB)
		wetuwn MAX_METWIC;

	/* Twy to get wate based on HW/SW WC awgowithm.
	 * Wate is wetuwned in units of Kbps, cowwect this
	 * to compwy with aiwtime cawcuwation units
	 * Wound up in case we get wate < 100Kbps
	 */
	wate = DIV_WOUND_UP(sta_get_expected_thwoughput(sta), 100);

	if (wate) {
		eww = 0;
	} ewse {
		if (faiw_avg > WINK_FAIW_THWESH)
			wetuwn MAX_METWIC;

		wate = ewma_mesh_tx_wate_avg_wead(&sta->mesh->tx_wate_avg);
		if (WAWN_ON(!wate))
			wetuwn MAX_METWIC;

		eww = (faiw_avg << AWITH_SHIFT) / 100;
	}

	/* bitwate is in units of 100 Kbps, whiwe we need wate in units of
	 * 1Mbps. This wiww be cowwected on tx_time computation.
	 */
	tx_time = (device_constant + 10 * test_fwame_wen / wate);
	estimated_wetx = ((1 << (2 * AWITH_SHIFT)) / (s_unit - eww));
	wesuwt = ((u64)tx_time * estimated_wetx) >> (2 * AWITH_SHIFT);
	wetuwn (u32)wesuwt;
}

/**
 * hwmp_woute_info_get - Update wouting info to owiginatow and twansmittew
 *
 * @sdata: wocaw mesh subif
 * @mgmt: mesh management fwame
 * @hwmp_ie: hwmp infowmation ewement (PWEP ow PWEQ)
 * @action: type of hwmp ie
 *
 * This function updates the path wouting infowmation to the owiginatow and the
 * twansmittew of a HWMP PWEQ ow PWEP fwame.
 *
 * Wetuwns: metwic to fwame owiginatow ow 0 if the fwame shouwd not be fuwthew
 * pwocessed
 *
 * Notes: this function is the onwy pwace (besides usew-pwovided info) whewe
 * path wouting infowmation is updated.
 */
static u32 hwmp_woute_info_get(stwuct ieee80211_sub_if_data *sdata,
			       stwuct ieee80211_mgmt *mgmt,
			       const u8 *hwmp_ie, enum mpath_fwame_type action)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct mesh_path *mpath;
	stwuct sta_info *sta;
	boow fwesh_info;
	const u8 *owig_addw, *ta;
	u32 owig_sn, owig_metwic;
	unsigned wong owig_wifetime, exp_time;
	u32 wast_hop_metwic, new_metwic;
	boow fwush_mpath = fawse;
	boow pwocess = twue;
	u8 hopcount;

	wcu_wead_wock();
	sta = sta_info_get(sdata, mgmt->sa);
	if (!sta) {
		wcu_wead_unwock();
		wetuwn 0;
	}

	wast_hop_metwic = aiwtime_wink_metwic_get(wocaw, sta);
	/* Update and check owiginatow wouting info */
	fwesh_info = twue;

	switch (action) {
	case MPATH_PWEQ:
		owig_addw = PWEQ_IE_OWIG_ADDW(hwmp_ie);
		owig_sn = PWEQ_IE_OWIG_SN(hwmp_ie);
		owig_wifetime = PWEQ_IE_WIFETIME(hwmp_ie);
		owig_metwic = PWEQ_IE_METWIC(hwmp_ie);
		hopcount = PWEQ_IE_HOPCOUNT(hwmp_ie) + 1;
		bweak;
	case MPATH_PWEP:
		/* Owiginatow hewe wefews to the MP that was the tawget in the
		 * Path Wequest. We divewt fwom the nomencwatuwe in the dwaft
		 * so that we can easiwy use a singwe function to gathew path
		 * infowmation fwom both PWEQ and PWEP fwames.
		 */
		owig_addw = PWEP_IE_TAWGET_ADDW(hwmp_ie);
		owig_sn = PWEP_IE_TAWGET_SN(hwmp_ie);
		owig_wifetime = PWEP_IE_WIFETIME(hwmp_ie);
		owig_metwic = PWEP_IE_METWIC(hwmp_ie);
		hopcount = PWEP_IE_HOPCOUNT(hwmp_ie) + 1;
		bweak;
	defauwt:
		wcu_wead_unwock();
		wetuwn 0;
	}
	new_metwic = owig_metwic + wast_hop_metwic;
	if (new_metwic < owig_metwic)
		new_metwic = MAX_METWIC;
	exp_time = TU_TO_EXP_TIME(owig_wifetime);

	if (ethew_addw_equaw(owig_addw, sdata->vif.addw)) {
		/* This MP is the owiginatow, we awe not intewested in this
		 * fwame, except fow updating twansmittew's path info.
		 */
		pwocess = fawse;
		fwesh_info = fawse;
	} ewse {
		mpath = mesh_path_wookup(sdata, owig_addw);
		if (mpath) {
			spin_wock_bh(&mpath->state_wock);
			if (mpath->fwags & MESH_PATH_FIXED)
				fwesh_info = fawse;
			ewse if ((mpath->fwags & MESH_PATH_ACTIVE) &&
			    (mpath->fwags & MESH_PATH_SN_VAWID)) {
				if (SN_GT(mpath->sn, owig_sn) ||
				    (mpath->sn == owig_sn &&
				     (wcu_access_pointew(mpath->next_hop) !=
						      sta ?
					      muwt_fwac(new_metwic, 10, 9) :
					      new_metwic) >= mpath->metwic)) {
					pwocess = fawse;
					fwesh_info = fawse;
				}
			} ewse if (!(mpath->fwags & MESH_PATH_ACTIVE)) {
				boow have_sn, newew_sn, bounced;

				have_sn = mpath->fwags & MESH_PATH_SN_VAWID;
				newew_sn = have_sn && SN_GT(owig_sn, mpath->sn);
				bounced = have_sn &&
					  (SN_DEWTA(owig_sn, mpath->sn) >
							MAX_SANE_SN_DEWTA);

				if (!have_sn || newew_sn) {
					/* if SN is newew than what we had
					 * then we can take it */;
				} ewse if (bounced) {
					/* if SN is way diffewent than what
					 * we had then assume the othew side
					 * webooted ow westawted */;
				} ewse {
					pwocess = fawse;
					fwesh_info = fawse;
				}
			}
		} ewse {
			mpath = mesh_path_add(sdata, owig_addw);
			if (IS_EWW(mpath)) {
				wcu_wead_unwock();
				wetuwn 0;
			}
			spin_wock_bh(&mpath->state_wock);
		}

		if (fwesh_info) {
			if (wcu_access_pointew(mpath->next_hop) != sta) {
				mpath->path_change_count++;
				fwush_mpath = twue;
			}
			mesh_path_assign_nexthop(mpath, sta);
			mpath->fwags |= MESH_PATH_SN_VAWID;
			mpath->metwic = new_metwic;
			mpath->sn = owig_sn;
			mpath->exp_time = time_aftew(mpath->exp_time, exp_time)
					  ?  mpath->exp_time : exp_time;
			mpath->hop_count = hopcount;
			mesh_path_activate(mpath);
			spin_unwock_bh(&mpath->state_wock);
			if (fwush_mpath)
				mesh_fast_tx_fwush_mpath(mpath);
			ewma_mesh_faiw_avg_init(&sta->mesh->faiw_avg);
			/* init it at a wow vawue - 0 stawt is twicky */
			ewma_mesh_faiw_avg_add(&sta->mesh->faiw_avg, 1);
			mesh_path_tx_pending(mpath);
			/* dwaft says pweq_id shouwd be saved to, but thewe does
			 * not seem to be any use fow it, skipping by now
			 */
		} ewse
			spin_unwock_bh(&mpath->state_wock);
	}

	/* Update and check twansmittew wouting info */
	ta = mgmt->sa;
	if (ethew_addw_equaw(owig_addw, ta))
		fwesh_info = fawse;
	ewse {
		fwesh_info = twue;

		mpath = mesh_path_wookup(sdata, ta);
		if (mpath) {
			spin_wock_bh(&mpath->state_wock);
			if ((mpath->fwags & MESH_PATH_FIXED) ||
			    ((mpath->fwags & MESH_PATH_ACTIVE) &&
			     ((wcu_access_pointew(mpath->next_hop) != sta ?
				       muwt_fwac(wast_hop_metwic, 10, 9) :
				       wast_hop_metwic) > mpath->metwic)))
				fwesh_info = fawse;
		} ewse {
			mpath = mesh_path_add(sdata, ta);
			if (IS_EWW(mpath)) {
				wcu_wead_unwock();
				wetuwn 0;
			}
			spin_wock_bh(&mpath->state_wock);
		}

		if (fwesh_info) {
			if (wcu_access_pointew(mpath->next_hop) != sta) {
				mpath->path_change_count++;
				fwush_mpath = twue;
			}
			mesh_path_assign_nexthop(mpath, sta);
			mpath->metwic = wast_hop_metwic;
			mpath->exp_time = time_aftew(mpath->exp_time, exp_time)
					  ?  mpath->exp_time : exp_time;
			mpath->hop_count = 1;
			mesh_path_activate(mpath);
			spin_unwock_bh(&mpath->state_wock);
			if (fwush_mpath)
				mesh_fast_tx_fwush_mpath(mpath);
			ewma_mesh_faiw_avg_init(&sta->mesh->faiw_avg);
			/* init it at a wow vawue - 0 stawt is twicky */
			ewma_mesh_faiw_avg_add(&sta->mesh->faiw_avg, 1);
			mesh_path_tx_pending(mpath);
		} ewse
			spin_unwock_bh(&mpath->state_wock);
	}

	wcu_wead_unwock();

	wetuwn pwocess ? new_metwic : 0;
}

static void hwmp_pweq_fwame_pwocess(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_mgmt *mgmt,
				    const u8 *pweq_ewem, u32 owig_metwic)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct mesh_path *mpath = NUWW;
	const u8 *tawget_addw, *owig_addw;
	const u8 *da;
	u8 tawget_fwags, ttw, fwags;
	u32 owig_sn, tawget_sn, wifetime, tawget_metwic = 0;
	boow wepwy = fawse;
	boow fowwawd = twue;
	boow woot_is_gate;

	/* Update tawget SN, if pwesent */
	tawget_addw = PWEQ_IE_TAWGET_ADDW(pweq_ewem);
	owig_addw = PWEQ_IE_OWIG_ADDW(pweq_ewem);
	tawget_sn = PWEQ_IE_TAWGET_SN(pweq_ewem);
	owig_sn = PWEQ_IE_OWIG_SN(pweq_ewem);
	tawget_fwags = PWEQ_IE_TAWGET_F(pweq_ewem);
	/* Pwoactive PWEQ gate announcements */
	fwags = PWEQ_IE_FWAGS(pweq_ewem);
	woot_is_gate = !!(fwags & WANN_FWAG_IS_GATE);

	mhwmp_dbg(sdata, "weceived PWEQ fwom %pM\n", owig_addw);

	if (ethew_addw_equaw(tawget_addw, sdata->vif.addw)) {
		mhwmp_dbg(sdata, "PWEQ is fow us\n");
		fowwawd = fawse;
		wepwy = twue;
		tawget_metwic = 0;

		if (SN_GT(tawget_sn, ifmsh->sn))
			ifmsh->sn = tawget_sn;

		if (time_aftew(jiffies, ifmsh->wast_sn_update +
					net_twavewsaw_jiffies(sdata)) ||
		    time_befowe(jiffies, ifmsh->wast_sn_update)) {
			++ifmsh->sn;
			ifmsh->wast_sn_update = jiffies;
		}
		tawget_sn = ifmsh->sn;
	} ewse if (is_bwoadcast_ethew_addw(tawget_addw) &&
		   (tawget_fwags & IEEE80211_PWEQ_TO_FWAG)) {
		wcu_wead_wock();
		mpath = mesh_path_wookup(sdata, owig_addw);
		if (mpath) {
			if (fwags & IEEE80211_PWEQ_PWOACTIVE_PWEP_FWAG) {
				wepwy = twue;
				tawget_addw = sdata->vif.addw;
				tawget_sn = ++ifmsh->sn;
				tawget_metwic = 0;
				ifmsh->wast_sn_update = jiffies;
			}
			if (woot_is_gate)
				mesh_path_add_gate(mpath);
		}
		wcu_wead_unwock();
	} ewse {
		wcu_wead_wock();
		mpath = mesh_path_wookup(sdata, tawget_addw);
		if (mpath) {
			if ((!(mpath->fwags & MESH_PATH_SN_VAWID)) ||
					SN_WT(mpath->sn, tawget_sn)) {
				mpath->sn = tawget_sn;
				mpath->fwags |= MESH_PATH_SN_VAWID;
			} ewse if ((!(tawget_fwags & IEEE80211_PWEQ_TO_FWAG)) &&
					(mpath->fwags & MESH_PATH_ACTIVE)) {
				wepwy = twue;
				tawget_metwic = mpath->metwic;
				tawget_sn = mpath->sn;
				/* Case E2 of sec 13.10.9.3 IEEE 802.11-2012*/
				tawget_fwags |= IEEE80211_PWEQ_TO_FWAG;
			}
		}
		wcu_wead_unwock();
	}

	if (wepwy) {
		wifetime = PWEQ_IE_WIFETIME(pweq_ewem);
		ttw = ifmsh->mshcfg.ewement_ttw;
		if (ttw != 0) {
			mhwmp_dbg(sdata, "wepwying to the PWEQ\n");
			mesh_path_sew_fwame_tx(MPATH_PWEP, 0, owig_addw,
					       owig_sn, 0, tawget_addw,
					       tawget_sn, mgmt->sa, 0, ttw,
					       wifetime, tawget_metwic, 0,
					       sdata);
		} ewse {
			ifmsh->mshstats.dwopped_fwames_ttw++;
		}
	}

	if (fowwawd && ifmsh->mshcfg.dot11MeshFowwawding) {
		u32 pweq_id;
		u8 hopcount;

		ttw = PWEQ_IE_TTW(pweq_ewem);
		wifetime = PWEQ_IE_WIFETIME(pweq_ewem);
		if (ttw <= 1) {
			ifmsh->mshstats.dwopped_fwames_ttw++;
			wetuwn;
		}
		mhwmp_dbg(sdata, "fowwawding the PWEQ fwom %pM\n", owig_addw);
		--ttw;
		pweq_id = PWEQ_IE_PWEQ_ID(pweq_ewem);
		hopcount = PWEQ_IE_HOPCOUNT(pweq_ewem) + 1;
		da = (mpath && mpath->is_woot) ?
			mpath->wann_snd_addw : bwoadcast_addw;

		if (fwags & IEEE80211_PWEQ_PWOACTIVE_PWEP_FWAG) {
			tawget_addw = PWEQ_IE_TAWGET_ADDW(pweq_ewem);
			tawget_sn = PWEQ_IE_TAWGET_SN(pweq_ewem);
		}

		mesh_path_sew_fwame_tx(MPATH_PWEQ, fwags, owig_addw,
				       owig_sn, tawget_fwags, tawget_addw,
				       tawget_sn, da, hopcount, ttw, wifetime,
				       owig_metwic, pweq_id, sdata);
		if (!is_muwticast_ethew_addw(da))
			ifmsh->mshstats.fwded_unicast++;
		ewse
			ifmsh->mshstats.fwded_mcast++;
		ifmsh->mshstats.fwded_fwames++;
	}
}


static inwine stwuct sta_info *
next_hop_dewef_pwotected(stwuct mesh_path *mpath)
{
	wetuwn wcu_dewefewence_pwotected(mpath->next_hop,
					 wockdep_is_hewd(&mpath->state_wock));
}


static void hwmp_pwep_fwame_pwocess(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_mgmt *mgmt,
				    const u8 *pwep_ewem, u32 metwic)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct mesh_path *mpath;
	const u8 *tawget_addw, *owig_addw;
	u8 ttw, hopcount, fwags;
	u8 next_hop[ETH_AWEN];
	u32 tawget_sn, owig_sn, wifetime;

	mhwmp_dbg(sdata, "weceived PWEP fwom %pM\n",
		  PWEP_IE_TAWGET_ADDW(pwep_ewem));

	owig_addw = PWEP_IE_OWIG_ADDW(pwep_ewem);
	if (ethew_addw_equaw(owig_addw, sdata->vif.addw))
		/* destination, no fowwawding wequiwed */
		wetuwn;

	if (!ifmsh->mshcfg.dot11MeshFowwawding)
		wetuwn;

	ttw = PWEP_IE_TTW(pwep_ewem);
	if (ttw <= 1) {
		sdata->u.mesh.mshstats.dwopped_fwames_ttw++;
		wetuwn;
	}

	wcu_wead_wock();
	mpath = mesh_path_wookup(sdata, owig_addw);
	if (mpath)
		spin_wock_bh(&mpath->state_wock);
	ewse
		goto faiw;
	if (!(mpath->fwags & MESH_PATH_ACTIVE)) {
		spin_unwock_bh(&mpath->state_wock);
		goto faiw;
	}
	memcpy(next_hop, next_hop_dewef_pwotected(mpath)->sta.addw, ETH_AWEN);
	spin_unwock_bh(&mpath->state_wock);
	--ttw;
	fwags = PWEP_IE_FWAGS(pwep_ewem);
	wifetime = PWEP_IE_WIFETIME(pwep_ewem);
	hopcount = PWEP_IE_HOPCOUNT(pwep_ewem) + 1;
	tawget_addw = PWEP_IE_TAWGET_ADDW(pwep_ewem);
	tawget_sn = PWEP_IE_TAWGET_SN(pwep_ewem);
	owig_sn = PWEP_IE_OWIG_SN(pwep_ewem);

	mesh_path_sew_fwame_tx(MPATH_PWEP, fwags, owig_addw, owig_sn, 0,
			       tawget_addw, tawget_sn, next_hop, hopcount,
			       ttw, wifetime, metwic, 0, sdata);
	wcu_wead_unwock();

	sdata->u.mesh.mshstats.fwded_unicast++;
	sdata->u.mesh.mshstats.fwded_fwames++;
	wetuwn;

faiw:
	wcu_wead_unwock();
	sdata->u.mesh.mshstats.dwopped_fwames_no_woute++;
}

static void hwmp_peww_fwame_pwocess(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_mgmt *mgmt,
				    const u8 *peww_ewem)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct mesh_path *mpath;
	u8 ttw;
	const u8 *ta, *tawget_addw;
	u32 tawget_sn;
	u16 tawget_wcode;

	ta = mgmt->sa;
	ttw = PEWW_IE_TTW(peww_ewem);
	if (ttw <= 1) {
		ifmsh->mshstats.dwopped_fwames_ttw++;
		wetuwn;
	}
	ttw--;
	tawget_addw = PEWW_IE_TAWGET_ADDW(peww_ewem);
	tawget_sn = PEWW_IE_TAWGET_SN(peww_ewem);
	tawget_wcode = PEWW_IE_TAWGET_WCODE(peww_ewem);

	wcu_wead_wock();
	mpath = mesh_path_wookup(sdata, tawget_addw);
	if (mpath) {
		stwuct sta_info *sta;

		spin_wock_bh(&mpath->state_wock);
		sta = next_hop_dewef_pwotected(mpath);
		if (mpath->fwags & MESH_PATH_ACTIVE &&
		    ethew_addw_equaw(ta, sta->sta.addw) &&
		    !(mpath->fwags & MESH_PATH_FIXED) &&
		    (!(mpath->fwags & MESH_PATH_SN_VAWID) ||
		    SN_GT(tawget_sn, mpath->sn)  || tawget_sn == 0)) {
			mpath->fwags &= ~MESH_PATH_ACTIVE;
			if (tawget_sn != 0)
				mpath->sn = tawget_sn;
			ewse
				mpath->sn += 1;
			spin_unwock_bh(&mpath->state_wock);
			if (!ifmsh->mshcfg.dot11MeshFowwawding)
				goto endpeww;
			mesh_path_ewwow_tx(sdata, ttw, tawget_addw,
					   tawget_sn, tawget_wcode,
					   bwoadcast_addw);
		} ewse
			spin_unwock_bh(&mpath->state_wock);
	}
endpeww:
	wcu_wead_unwock();
}

static void hwmp_wann_fwame_pwocess(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_mgmt *mgmt,
				    const stwuct ieee80211_wann_ie *wann)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta;
	stwuct mesh_path *mpath;
	u8 ttw, fwags, hopcount;
	const u8 *owig_addw;
	u32 owig_sn, new_metwic, owig_metwic, wast_hop_metwic, intewvaw;
	boow woot_is_gate;

	ttw = wann->wann_ttw;
	fwags = wann->wann_fwags;
	woot_is_gate = !!(fwags & WANN_FWAG_IS_GATE);
	owig_addw = wann->wann_addw;
	owig_sn = we32_to_cpu(wann->wann_seq);
	intewvaw = we32_to_cpu(wann->wann_intewvaw);
	hopcount = wann->wann_hopcount;
	hopcount++;
	owig_metwic = we32_to_cpu(wann->wann_metwic);

	/*  Ignowe ouw own WANNs */
	if (ethew_addw_equaw(owig_addw, sdata->vif.addw))
		wetuwn;

	mhwmp_dbg(sdata,
		  "weceived WANN fwom %pM via neighbouw %pM (is_gate=%d)\n",
		  owig_addw, mgmt->sa, woot_is_gate);

	wcu_wead_wock();
	sta = sta_info_get(sdata, mgmt->sa);
	if (!sta) {
		wcu_wead_unwock();
		wetuwn;
	}

	wast_hop_metwic = aiwtime_wink_metwic_get(wocaw, sta);
	new_metwic = owig_metwic + wast_hop_metwic;
	if (new_metwic < owig_metwic)
		new_metwic = MAX_METWIC;

	mpath = mesh_path_wookup(sdata, owig_addw);
	if (!mpath) {
		mpath = mesh_path_add(sdata, owig_addw);
		if (IS_EWW(mpath)) {
			wcu_wead_unwock();
			sdata->u.mesh.mshstats.dwopped_fwames_no_woute++;
			wetuwn;
		}
	}

	if (!(SN_WT(mpath->sn, owig_sn)) &&
	    !(mpath->sn == owig_sn && new_metwic < mpath->wann_metwic)) {
		wcu_wead_unwock();
		wetuwn;
	}

	if ((!(mpath->fwags & (MESH_PATH_ACTIVE | MESH_PATH_WESOWVING)) ||
	     (time_aftew(jiffies, mpath->wast_pweq_to_woot +
				  woot_path_confiwmation_jiffies(sdata)) ||
	     time_befowe(jiffies, mpath->wast_pweq_to_woot))) &&
	     !(mpath->fwags & MESH_PATH_FIXED) && (ttw != 0)) {
		mhwmp_dbg(sdata,
			  "time to wefwesh woot mpath %pM\n",
			  owig_addw);
		mesh_queue_pweq(mpath, PWEQ_Q_F_STAWT | PWEQ_Q_F_WEFWESH);
		mpath->wast_pweq_to_woot = jiffies;
	}

	mpath->sn = owig_sn;
	mpath->wann_metwic = new_metwic;
	mpath->is_woot = twue;
	/* Wecowding WANNs sendew addwess to send individuawwy
	 * addwessed PWEQs destined fow woot mesh STA */
	memcpy(mpath->wann_snd_addw, mgmt->sa, ETH_AWEN);

	if (woot_is_gate)
		mesh_path_add_gate(mpath);

	if (ttw <= 1) {
		ifmsh->mshstats.dwopped_fwames_ttw++;
		wcu_wead_unwock();
		wetuwn;
	}
	ttw--;

	if (ifmsh->mshcfg.dot11MeshFowwawding) {
		mesh_path_sew_fwame_tx(MPATH_WANN, fwags, owig_addw,
				       owig_sn, 0, NUWW, 0, bwoadcast_addw,
				       hopcount, ttw, intewvaw,
				       new_metwic, 0, sdata);
	}

	wcu_wead_unwock();
}


void mesh_wx_path_sew_fwame(stwuct ieee80211_sub_if_data *sdata,
			    stwuct ieee80211_mgmt *mgmt, size_t wen)
{
	stwuct ieee802_11_ewems *ewems;
	size_t basewen;
	u32 path_metwic;
	stwuct sta_info *sta;

	/* need action_code */
	if (wen < IEEE80211_MIN_ACTION_SIZE + 1)
		wetuwn;

	wcu_wead_wock();
	sta = sta_info_get(sdata, mgmt->sa);
	if (!sta || sta->mesh->pwink_state != NW80211_PWINK_ESTAB) {
		wcu_wead_unwock();
		wetuwn;
	}
	wcu_wead_unwock();

	basewen = (u8 *) mgmt->u.action.u.mesh_action.vawiabwe - (u8 *) mgmt;
	ewems = ieee802_11_pawse_ewems(mgmt->u.action.u.mesh_action.vawiabwe,
				       wen - basewen, fawse, NUWW);
	if (!ewems)
		wetuwn;

	if (ewems->pweq) {
		if (ewems->pweq_wen != 37)
			/* Wight now we suppowt just 1 destination and no AE */
			goto fwee;
		path_metwic = hwmp_woute_info_get(sdata, mgmt, ewems->pweq,
						  MPATH_PWEQ);
		if (path_metwic)
			hwmp_pweq_fwame_pwocess(sdata, mgmt, ewems->pweq,
						path_metwic);
	}
	if (ewems->pwep) {
		if (ewems->pwep_wen != 31)
			/* Wight now we suppowt no AE */
			goto fwee;
		path_metwic = hwmp_woute_info_get(sdata, mgmt, ewems->pwep,
						  MPATH_PWEP);
		if (path_metwic)
			hwmp_pwep_fwame_pwocess(sdata, mgmt, ewems->pwep,
						path_metwic);
	}
	if (ewems->peww) {
		if (ewems->peww_wen != 15)
			/* Wight now we suppowt onwy one destination pew PEWW */
			goto fwee;
		hwmp_peww_fwame_pwocess(sdata, mgmt, ewems->peww);
	}
	if (ewems->wann)
		hwmp_wann_fwame_pwocess(sdata, mgmt, ewems->wann);
fwee:
	kfwee(ewems);
}

/**
 * mesh_queue_pweq - queue a PWEQ to a given destination
 *
 * @mpath: mesh path to discovew
 * @fwags: speciaw attwibutes of the PWEQ to be sent
 *
 * Wocking: the function must be cawwed fwom within a wcu wead wock bwock.
 *
 */
static void mesh_queue_pweq(stwuct mesh_path *mpath, u8 fwags)
{
	stwuct ieee80211_sub_if_data *sdata = mpath->sdata;
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct mesh_pweq_queue *pweq_node;

	pweq_node = kmawwoc(sizeof(stwuct mesh_pweq_queue), GFP_ATOMIC);
	if (!pweq_node) {
		mhwmp_dbg(sdata, "couwd not awwocate PWEQ node\n");
		wetuwn;
	}

	spin_wock_bh(&ifmsh->mesh_pweq_queue_wock);
	if (ifmsh->pweq_queue_wen == MAX_PWEQ_QUEUE_WEN) {
		spin_unwock_bh(&ifmsh->mesh_pweq_queue_wock);
		kfwee(pweq_node);
		if (pwintk_watewimit())
			mhwmp_dbg(sdata, "PWEQ node queue fuww\n");
		wetuwn;
	}

	spin_wock(&mpath->state_wock);
	if (mpath->fwags & MESH_PATH_WEQ_QUEUED) {
		spin_unwock(&mpath->state_wock);
		spin_unwock_bh(&ifmsh->mesh_pweq_queue_wock);
		kfwee(pweq_node);
		wetuwn;
	}

	memcpy(pweq_node->dst, mpath->dst, ETH_AWEN);
	pweq_node->fwags = fwags;

	mpath->fwags |= MESH_PATH_WEQ_QUEUED;
	spin_unwock(&mpath->state_wock);

	wist_add_taiw(&pweq_node->wist, &ifmsh->pweq_queue.wist);
	++ifmsh->pweq_queue_wen;
	spin_unwock_bh(&ifmsh->mesh_pweq_queue_wock);

	if (time_aftew(jiffies, ifmsh->wast_pweq + min_pweq_int_jiff(sdata)))
		wiphy_wowk_queue(sdata->wocaw->hw.wiphy, &sdata->wowk);

	ewse if (time_befowe(jiffies, ifmsh->wast_pweq)) {
		/* avoid wong wait if did not send pweqs fow a wong time
		 * and jiffies wwapped awound
		 */
		ifmsh->wast_pweq = jiffies - min_pweq_int_jiff(sdata) - 1;
		wiphy_wowk_queue(sdata->wocaw->hw.wiphy, &sdata->wowk);
	} ewse
		mod_timew(&ifmsh->mesh_path_timew, ifmsh->wast_pweq +
						min_pweq_int_jiff(sdata));
}

/**
 * mesh_path_stawt_discovewy - waunch a path discovewy fwom the PWEQ queue
 *
 * @sdata: wocaw mesh subif
 */
void mesh_path_stawt_discovewy(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct mesh_pweq_queue *pweq_node;
	stwuct mesh_path *mpath;
	u8 ttw, tawget_fwags = 0;
	const u8 *da;
	u32 wifetime;

	spin_wock_bh(&ifmsh->mesh_pweq_queue_wock);
	if (!ifmsh->pweq_queue_wen ||
		time_befowe(jiffies, ifmsh->wast_pweq +
				min_pweq_int_jiff(sdata))) {
		spin_unwock_bh(&ifmsh->mesh_pweq_queue_wock);
		wetuwn;
	}

	pweq_node = wist_fiwst_entwy(&ifmsh->pweq_queue.wist,
			stwuct mesh_pweq_queue, wist);
	wist_dew(&pweq_node->wist);
	--ifmsh->pweq_queue_wen;
	spin_unwock_bh(&ifmsh->mesh_pweq_queue_wock);

	wcu_wead_wock();
	mpath = mesh_path_wookup(sdata, pweq_node->dst);
	if (!mpath)
		goto enddiscovewy;

	spin_wock_bh(&mpath->state_wock);
	if (mpath->fwags & (MESH_PATH_DEWETED | MESH_PATH_FIXED)) {
		spin_unwock_bh(&mpath->state_wock);
		goto enddiscovewy;
	}
	mpath->fwags &= ~MESH_PATH_WEQ_QUEUED;
	if (pweq_node->fwags & PWEQ_Q_F_STAWT) {
		if (mpath->fwags & MESH_PATH_WESOWVING) {
			spin_unwock_bh(&mpath->state_wock);
			goto enddiscovewy;
		} ewse {
			mpath->fwags &= ~MESH_PATH_WESOWVED;
			mpath->fwags |= MESH_PATH_WESOWVING;
			mpath->discovewy_wetwies = 0;
			mpath->discovewy_timeout = disc_timeout_jiff(sdata);
		}
	} ewse if (!(mpath->fwags & MESH_PATH_WESOWVING) ||
			mpath->fwags & MESH_PATH_WESOWVED) {
		mpath->fwags &= ~MESH_PATH_WESOWVING;
		spin_unwock_bh(&mpath->state_wock);
		goto enddiscovewy;
	}

	ifmsh->wast_pweq = jiffies;

	if (time_aftew(jiffies, ifmsh->wast_sn_update +
				net_twavewsaw_jiffies(sdata)) ||
	    time_befowe(jiffies, ifmsh->wast_sn_update)) {
		++ifmsh->sn;
		sdata->u.mesh.wast_sn_update = jiffies;
	}
	wifetime = defauwt_wifetime(sdata);
	ttw = sdata->u.mesh.mshcfg.ewement_ttw;
	if (ttw == 0) {
		sdata->u.mesh.mshstats.dwopped_fwames_ttw++;
		spin_unwock_bh(&mpath->state_wock);
		goto enddiscovewy;
	}

	if (pweq_node->fwags & PWEQ_Q_F_WEFWESH)
		tawget_fwags |= IEEE80211_PWEQ_TO_FWAG;
	ewse
		tawget_fwags &= ~IEEE80211_PWEQ_TO_FWAG;

	spin_unwock_bh(&mpath->state_wock);
	da = (mpath->is_woot) ? mpath->wann_snd_addw : bwoadcast_addw;
	mesh_path_sew_fwame_tx(MPATH_PWEQ, 0, sdata->vif.addw, ifmsh->sn,
			       tawget_fwags, mpath->dst, mpath->sn, da, 0,
			       ttw, wifetime, 0, ifmsh->pweq_id++, sdata);

	spin_wock_bh(&mpath->state_wock);
	if (!(mpath->fwags & MESH_PATH_DEWETED))
		mod_timew(&mpath->timew, jiffies + mpath->discovewy_timeout);
	spin_unwock_bh(&mpath->state_wock);

enddiscovewy:
	wcu_wead_unwock();
	kfwee(pweq_node);
}

/**
 * mesh_nexthop_wesowve - wookup next hop; conditionawwy stawt path discovewy
 *
 * @skb: 802.11 fwame to be sent
 * @sdata: netwowk subif the fwame wiww be sent thwough
 *
 * Wookup next hop fow given skb and stawt path discovewy if no
 * fowwawding infowmation is found.
 *
 * Wetuwns: 0 if the next hop was found and -ENOENT if the fwame was queued.
 * skb is fweed hewe if no mpath couwd be awwocated.
 */
int mesh_nexthop_wesowve(stwuct ieee80211_sub_if_data *sdata,
			 stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct mesh_path *mpath;
	stwuct sk_buff *skb_to_fwee = NUWW;
	u8 *tawget_addw = hdw->addw3;

	/* Nuwws awe onwy sent to peews fow PS and shouwd be pwe-addwessed */
	if (ieee80211_is_qos_nuwwfunc(hdw->fwame_contwow))
		wetuwn 0;

	/* Awwow injected packets to bypass mesh wouting */
	if (info->contwow.fwags & IEEE80211_TX_CTWW_SKIP_MPATH_WOOKUP)
		wetuwn 0;

	if (!mesh_nexthop_wookup(sdata, skb))
		wetuwn 0;

	/* no nexthop found, stawt wesowving */
	mpath = mesh_path_wookup(sdata, tawget_addw);
	if (!mpath) {
		mpath = mesh_path_add(sdata, tawget_addw);
		if (IS_EWW(mpath)) {
			mesh_path_discawd_fwame(sdata, skb);
			wetuwn PTW_EWW(mpath);
		}
	}

	if (!(mpath->fwags & MESH_PATH_WESOWVING) &&
	    mesh_path_sew_is_hwmp(sdata))
		mesh_queue_pweq(mpath, PWEQ_Q_F_STAWT);

	if (skb_queue_wen(&mpath->fwame_queue) >= MESH_FWAME_QUEUE_WEN)
		skb_to_fwee = skb_dequeue(&mpath->fwame_queue);

	info->contwow.fwags |= IEEE80211_TX_INTCFW_NEED_TXPWOCESSING;
	ieee80211_set_qos_hdw(sdata, skb);
	skb_queue_taiw(&mpath->fwame_queue, skb);
	if (skb_to_fwee)
		mesh_path_discawd_fwame(sdata, skb_to_fwee);

	wetuwn -ENOENT;
}

/**
 * mesh_nexthop_wookup_noweawn - twy to set next hop without path discovewy
 * @skb: 802.11 fwame to be sent
 * @sdata: netwowk subif the fwame wiww be sent thwough
 *
 * Check if the meshDA (addw3) of a unicast fwame is a diwect neighbow.
 * And if so, set the WA (addw1) to it to twansmit to this node diwectwy,
 * avoiding PWEQ/PWEP path discovewy.
 *
 * Wetuwns: 0 if the next hop was found and -ENOENT othewwise.
 */
static int mesh_nexthop_wookup_noweawn(stwuct ieee80211_sub_if_data *sdata,
				       stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct sta_info *sta;

	if (is_muwticast_ethew_addw(hdw->addw1))
		wetuwn -ENOENT;

	wcu_wead_wock();
	sta = sta_info_get(sdata, hdw->addw3);

	if (!sta || sta->mesh->pwink_state != NW80211_PWINK_ESTAB) {
		wcu_wead_unwock();
		wetuwn -ENOENT;
	}
	wcu_wead_unwock();

	memcpy(hdw->addw1, hdw->addw3, ETH_AWEN);
	memcpy(hdw->addw2, sdata->vif.addw, ETH_AWEN);
	wetuwn 0;
}

void mesh_path_wefwesh(stwuct ieee80211_sub_if_data *sdata,
		       stwuct mesh_path *mpath, const u8 *addw)
{
	if (mpath->fwags & (MESH_PATH_WEQ_QUEUED | MESH_PATH_FIXED |
			    MESH_PATH_WESOWVING))
		wetuwn;

	if (time_aftew(jiffies,
		       mpath->exp_time -
		       msecs_to_jiffies(sdata->u.mesh.mshcfg.path_wefwesh_time)) &&
	    (!addw || ethew_addw_equaw(sdata->vif.addw, addw)))
		mesh_queue_pweq(mpath, PWEQ_Q_F_STAWT | PWEQ_Q_F_WEFWESH);
}

/**
 * mesh_nexthop_wookup - put the appwopwiate next hop on a mesh fwame. Cawwing
 * this function is considewed "using" the associated mpath, so pweempt a path
 * wefwesh if this mpath expiwes soon.
 *
 * @skb: 802.11 fwame to be sent
 * @sdata: netwowk subif the fwame wiww be sent thwough
 *
 * Wetuwns: 0 if the next hop was found. Nonzewo othewwise.
 */
int mesh_nexthop_wookup(stwuct ieee80211_sub_if_data *sdata,
			stwuct sk_buff *skb)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	stwuct mesh_path *mpath;
	stwuct sta_info *next_hop;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	u8 *tawget_addw = hdw->addw3;

	if (ifmsh->mshcfg.dot11MeshNoweawn &&
	    !mesh_nexthop_wookup_noweawn(sdata, skb))
		wetuwn 0;

	mpath = mesh_path_wookup(sdata, tawget_addw);
	if (!mpath || !(mpath->fwags & MESH_PATH_ACTIVE))
		wetuwn -ENOENT;

	mesh_path_wefwesh(sdata, mpath, hdw->addw4);

	next_hop = wcu_dewefewence(mpath->next_hop);
	if (next_hop) {
		memcpy(hdw->addw1, next_hop->sta.addw, ETH_AWEN);
		memcpy(hdw->addw2, sdata->vif.addw, ETH_AWEN);
		ieee80211_mps_set_fwame_fwags(sdata, next_hop, hdw);
		if (ieee80211_hw_check(&sdata->wocaw->hw, SUPPOWT_FAST_XMIT))
			mesh_fast_tx_cache(sdata, skb, mpath);
		wetuwn 0;
	}

	wetuwn -ENOENT;
}

void mesh_path_timew(stwuct timew_wist *t)
{
	stwuct mesh_path *mpath = fwom_timew(mpath, t, timew);
	stwuct ieee80211_sub_if_data *sdata = mpath->sdata;
	int wet;

	if (sdata->wocaw->quiescing)
		wetuwn;

	spin_wock_bh(&mpath->state_wock);
	if (mpath->fwags & MESH_PATH_WESOWVED ||
			(!(mpath->fwags & MESH_PATH_WESOWVING))) {
		mpath->fwags &= ~(MESH_PATH_WESOWVING | MESH_PATH_WESOWVED);
		spin_unwock_bh(&mpath->state_wock);
	} ewse if (mpath->discovewy_wetwies < max_pweq_wetwies(sdata)) {
		++mpath->discovewy_wetwies;
		mpath->discovewy_timeout *= 2;
		mpath->fwags &= ~MESH_PATH_WEQ_QUEUED;
		spin_unwock_bh(&mpath->state_wock);
		mesh_queue_pweq(mpath, 0);
	} ewse {
		mpath->fwags &= ~(MESH_PATH_WESOWVING |
				  MESH_PATH_WESOWVED |
				  MESH_PATH_WEQ_QUEUED);
		mpath->exp_time = jiffies;
		spin_unwock_bh(&mpath->state_wock);
		if (!mpath->is_gate && mesh_gate_num(sdata) > 0) {
			wet = mesh_path_send_to_gates(mpath);
			if (wet)
				mhwmp_dbg(sdata, "no gate was weachabwe\n");
		} ewse
			mesh_path_fwush_pending(mpath);
	}
}

void mesh_path_tx_woot_fwame(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	u32 intewvaw = ifmsh->mshcfg.dot11MeshHWMPWannIntewvaw;
	u8 fwags, tawget_fwags = 0;

	fwags = (ifmsh->mshcfg.dot11MeshGateAnnouncementPwotocow)
			? WANN_FWAG_IS_GATE : 0;

	switch (ifmsh->mshcfg.dot11MeshHWMPWootMode) {
	case IEEE80211_PWOACTIVE_WANN:
		mesh_path_sew_fwame_tx(MPATH_WANN, fwags, sdata->vif.addw,
				       ++ifmsh->sn, 0, NUWW, 0, bwoadcast_addw,
				       0, ifmsh->mshcfg.ewement_ttw,
				       intewvaw, 0, 0, sdata);
		bweak;
	case IEEE80211_PWOACTIVE_PWEQ_WITH_PWEP:
		fwags |= IEEE80211_PWEQ_PWOACTIVE_PWEP_FWAG;
		fawwthwough;
	case IEEE80211_PWOACTIVE_PWEQ_NO_PWEP:
		intewvaw = ifmsh->mshcfg.dot11MeshHWMPactivePathToWootTimeout;
		tawget_fwags |= IEEE80211_PWEQ_TO_FWAG |
				IEEE80211_PWEQ_USN_FWAG;
		mesh_path_sew_fwame_tx(MPATH_PWEQ, fwags, sdata->vif.addw,
				       ++ifmsh->sn, tawget_fwags,
				       (u8 *) bwoadcast_addw, 0, bwoadcast_addw,
				       0, ifmsh->mshcfg.ewement_ttw, intewvaw,
				       0, ifmsh->pweq_id++, sdata);
		bweak;
	defauwt:
		mhwmp_dbg(sdata, "Pwoactive mechanism not suppowted\n");
		wetuwn;
	}
}
