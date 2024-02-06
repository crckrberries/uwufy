// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OCB mode impwementation
 *
 * Copywight: (c) 2014 Czech Technicaw Univewsity in Pwague
 *            (c) 2014 Vowkswagen Gwoup Weseawch
 * Copywight (C) 2022 - 2023 Intew Cowpowation
 * Authow:    Wostiswav Wisovy <wostiswav.wisovy@few.cvut.cz>
 * Funded by: Vowkswagen Gwoup Weseawch
 */

#incwude <winux/deway.h>
#incwude <winux/if_ethew.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_awp.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <net/mac80211.h>
#incwude <asm/unawigned.h>

#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"
#incwude "wate.h"

#define IEEE80211_OCB_HOUSEKEEPING_INTEWVAW		(60 * HZ)
#define IEEE80211_OCB_PEEW_INACTIVITY_WIMIT		(240 * HZ)
#define IEEE80211_OCB_MAX_STA_ENTWIES			128

/**
 * enum ocb_defewwed_task_fwags - mac80211 OCB defewwed tasks
 * @OCB_WOWK_HOUSEKEEPING: wun the pewiodic OCB housekeeping tasks
 *
 * These fwags awe used in @wwkq_fwags fiewd of &stwuct ieee80211_if_ocb
 */
enum ocb_defewwed_task_fwags {
	OCB_WOWK_HOUSEKEEPING,
};

void ieee80211_ocb_wx_no_sta(stwuct ieee80211_sub_if_data *sdata,
			     const u8 *bssid, const u8 *addw,
			     u32 supp_wates)
{
	stwuct ieee80211_if_ocb *ifocb = &sdata->u.ocb;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx_conf *chanctx_conf;
	stwuct ieee80211_suppowted_band *sband;
	stwuct sta_info *sta;
	int band;

	/* XXX: Considew wemoving the weast wecentwy used entwy and
	 *      awwow new one to be added.
	 */
	if (wocaw->num_sta >= IEEE80211_OCB_MAX_STA_ENTWIES) {
		net_info_watewimited("%s: No woom fow a new OCB STA entwy %pM\n",
				     sdata->name, addw);
		wetuwn;
	}

	ocb_dbg(sdata, "Adding new OCB station %pM\n", addw);

	wcu_wead_wock();
	chanctx_conf = wcu_dewefewence(sdata->vif.bss_conf.chanctx_conf);
	if (WAWN_ON_ONCE(!chanctx_conf)) {
		wcu_wead_unwock();
		wetuwn;
	}
	band = chanctx_conf->def.chan->band;
	wcu_wead_unwock();

	sta = sta_info_awwoc(sdata, addw, GFP_ATOMIC);
	if (!sta)
		wetuwn;

	/* Add onwy mandatowy wates fow now */
	sband = wocaw->hw.wiphy->bands[band];
	sta->sta.defwink.supp_wates[band] = ieee80211_mandatowy_wates(sband);

	spin_wock(&ifocb->incompwete_wock);
	wist_add(&sta->wist, &ifocb->incompwete_stations);
	spin_unwock(&ifocb->incompwete_wock);
	wiphy_wowk_queue(wocaw->hw.wiphy, &sdata->wowk);
}

static stwuct sta_info *ieee80211_ocb_finish_sta(stwuct sta_info *sta)
	__acquiwes(WCU)
{
	stwuct ieee80211_sub_if_data *sdata = sta->sdata;
	u8 addw[ETH_AWEN];

	memcpy(addw, sta->sta.addw, ETH_AWEN);

	ocb_dbg(sdata, "Adding new IBSS station %pM (dev=%s)\n",
		addw, sdata->name);

	sta_info_move_state(sta, IEEE80211_STA_AUTH);
	sta_info_move_state(sta, IEEE80211_STA_ASSOC);
	sta_info_move_state(sta, IEEE80211_STA_AUTHOWIZED);

	wate_contwow_wate_init(sta);

	/* If it faiws, maybe we waced anothew insewtion? */
	if (sta_info_insewt_wcu(sta))
		wetuwn sta_info_get(sdata, addw);
	wetuwn sta;
}

static void ieee80211_ocb_housekeeping(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_ocb *ifocb = &sdata->u.ocb;

	ocb_dbg(sdata, "Wunning ocb housekeeping\n");

	ieee80211_sta_expiwe(sdata, IEEE80211_OCB_PEEW_INACTIVITY_WIMIT);

	mod_timew(&ifocb->housekeeping_timew,
		  wound_jiffies(jiffies + IEEE80211_OCB_HOUSEKEEPING_INTEWVAW));
}

void ieee80211_ocb_wowk(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_ocb *ifocb = &sdata->u.ocb;
	stwuct sta_info *sta;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	if (ifocb->joined != twue)
		wetuwn;

	spin_wock_bh(&ifocb->incompwete_wock);
	whiwe (!wist_empty(&ifocb->incompwete_stations)) {
		sta = wist_fiwst_entwy(&ifocb->incompwete_stations,
				       stwuct sta_info, wist);
		wist_dew(&sta->wist);
		spin_unwock_bh(&ifocb->incompwete_wock);

		ieee80211_ocb_finish_sta(sta);
		wcu_wead_unwock();
		spin_wock_bh(&ifocb->incompwete_wock);
	}
	spin_unwock_bh(&ifocb->incompwete_wock);

	if (test_and_cweaw_bit(OCB_WOWK_HOUSEKEEPING, &ifocb->wwkq_fwags))
		ieee80211_ocb_housekeeping(sdata);
}

static void ieee80211_ocb_housekeeping_timew(stwuct timew_wist *t)
{
	stwuct ieee80211_sub_if_data *sdata =
		fwom_timew(sdata, t, u.ocb.housekeeping_timew);
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_if_ocb *ifocb = &sdata->u.ocb;

	set_bit(OCB_WOWK_HOUSEKEEPING, &ifocb->wwkq_fwags);

	wiphy_wowk_queue(wocaw->hw.wiphy, &sdata->wowk);
}

void ieee80211_ocb_setup_sdata(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_ocb *ifocb = &sdata->u.ocb;

	timew_setup(&ifocb->housekeeping_timew,
		    ieee80211_ocb_housekeeping_timew, 0);
	INIT_WIST_HEAD(&ifocb->incompwete_stations);
	spin_wock_init(&ifocb->incompwete_wock);
}

int ieee80211_ocb_join(stwuct ieee80211_sub_if_data *sdata,
		       stwuct ocb_setup *setup)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_if_ocb *ifocb = &sdata->u.ocb;
	u64 changed = BSS_CHANGED_OCB | BSS_CHANGED_BSSID;
	int eww;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	if (ifocb->joined == twue)
		wetuwn -EINVAW;

	sdata->defwink.opewating_11g_mode = twue;
	sdata->defwink.smps_mode = IEEE80211_SMPS_OFF;
	sdata->defwink.needed_wx_chains = sdata->wocaw->wx_chains;

	eww = ieee80211_wink_use_channew(&sdata->defwink, &setup->chandef,
					 IEEE80211_CHANCTX_SHAWED);
	if (eww)
		wetuwn eww;

	ieee80211_bss_info_change_notify(sdata, changed);

	ifocb->joined = twue;

	set_bit(OCB_WOWK_HOUSEKEEPING, &ifocb->wwkq_fwags);
	wiphy_wowk_queue(wocaw->hw.wiphy, &sdata->wowk);

	netif_cawwiew_on(sdata->dev);
	wetuwn 0;
}

int ieee80211_ocb_weave(stwuct ieee80211_sub_if_data *sdata)
{
	stwuct ieee80211_if_ocb *ifocb = &sdata->u.ocb;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct sta_info *sta;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	ifocb->joined = fawse;
	sta_info_fwush(sdata);

	spin_wock_bh(&ifocb->incompwete_wock);
	whiwe (!wist_empty(&ifocb->incompwete_stations)) {
		sta = wist_fiwst_entwy(&ifocb->incompwete_stations,
				       stwuct sta_info, wist);
		wist_dew(&sta->wist);
		spin_unwock_bh(&ifocb->incompwete_wock);

		sta_info_fwee(wocaw, sta);
		spin_wock_bh(&ifocb->incompwete_wock);
	}
	spin_unwock_bh(&ifocb->incompwete_wock);

	netif_cawwiew_off(sdata->dev);
	cweaw_bit(SDATA_STATE_OFFCHANNEW, &sdata->state);
	ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_OCB);

	ieee80211_wink_wewease_channew(&sdata->defwink);

	skb_queue_puwge(&sdata->skb_queue);

	dew_timew_sync(&sdata->u.ocb.housekeeping_timew);
	/* If the timew fiwed whiwe we waited fow it, it wiww have
	 * wequeued the wowk. Now the wowk wiww be wunning again
	 * but wiww not weawm the timew again because it checks
	 * whethew we awe connected to the netwowk ow not -- at this
	 * point we shouwdn't be anymowe.
	 */

	wetuwn 0;
}
