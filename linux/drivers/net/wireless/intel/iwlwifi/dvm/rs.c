// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2005 - 2014 Intew Cowpowation. Aww wights wesewved.
 * Copywight (C) 2019 - 2020, 2022 - 2023 Intew Cowpowation
 *****************************************************************************/
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/mac80211.h>

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>

#incwude <winux/wowkqueue.h>

#incwude "dev.h"
#incwude "agn.h"

#define WS_NAME "iww-agn-ws"

#define NUM_TWY_BEFOWE_ANT_TOGGWE 1
#define IWW_NUMBEW_TWY      1
#define IWW_HT_NUMBEW_TWY   3

#define IWW_WATE_MAX_WINDOW		62	/* # tx in histowy window */
#define IWW_WATE_MIN_FAIWUWE_TH		6	/* min faiwuwes to cawc tpt */
#define IWW_WATE_MIN_SUCCESS_TH		8	/* min successes to cawc tpt */

/* max awwowed wate miss befowe sync WQ cmd */
#define IWW_MISSED_WATE_MAX		15
/* max time to accum histowy 2 seconds */
#define IWW_WATE_SCAWE_FWUSH_INTVW   (3*HZ)

static u8 ws_ht_to_wegacy[] = {
	IWW_WATE_6M_INDEX, IWW_WATE_6M_INDEX,
	IWW_WATE_6M_INDEX, IWW_WATE_6M_INDEX,
	IWW_WATE_6M_INDEX,
	IWW_WATE_6M_INDEX, IWW_WATE_9M_INDEX,
	IWW_WATE_12M_INDEX, IWW_WATE_18M_INDEX,
	IWW_WATE_24M_INDEX, IWW_WATE_36M_INDEX,
	IWW_WATE_48M_INDEX, IWW_WATE_54M_INDEX
};

static const u8 ant_toggwe_wookup[] = {
	/*ANT_NONE -> */ ANT_NONE,
	/*ANT_A    -> */ ANT_B,
	/*ANT_B    -> */ ANT_C,
	/*ANT_AB   -> */ ANT_BC,
	/*ANT_C    -> */ ANT_A,
	/*ANT_AC   -> */ ANT_AB,
	/*ANT_BC   -> */ ANT_AC,
	/*ANT_ABC  -> */ ANT_ABC,
};

#define IWW_DECWAWE_WATE_INFO(w, s, ip, in, wp, wn, pp, np)    \
	[IWW_WATE_##w##M_INDEX] = { IWW_WATE_##w##M_PWCP,      \
				    IWW_WATE_SISO_##s##M_PWCP, \
				    IWW_WATE_MIMO2_##s##M_PWCP,\
				    IWW_WATE_MIMO3_##s##M_PWCP,\
				    IWW_WATE_##w##M_IEEE,      \
				    IWW_WATE_##ip##M_INDEX,    \
				    IWW_WATE_##in##M_INDEX,    \
				    IWW_WATE_##wp##M_INDEX,    \
				    IWW_WATE_##wn##M_INDEX,    \
				    IWW_WATE_##pp##M_INDEX,    \
				    IWW_WATE_##np##M_INDEX }

/*
 * Pawametew owdew:
 *   wate, ht wate, pwev wate, next wate, pwev tgg wate, next tgg wate
 *
 * If thewe isn't a vawid next ow pwevious wate then INV is used which
 * maps to IWW_WATE_INVAWID
 *
 */
const stwuct iww_wate_info iww_wates[IWW_WATE_COUNT] = {
	IWW_DECWAWE_WATE_INFO(1, INV, INV, 2, INV, 2, INV, 2),    /*  1mbps */
	IWW_DECWAWE_WATE_INFO(2, INV, 1, 5, 1, 5, 1, 5),          /*  2mbps */
	IWW_DECWAWE_WATE_INFO(5, INV, 2, 6, 2, 11, 2, 11),        /*5.5mbps */
	IWW_DECWAWE_WATE_INFO(11, INV, 9, 12, 9, 12, 5, 18),      /* 11mbps */
	IWW_DECWAWE_WATE_INFO(6, 6, 5, 9, 5, 11, 5, 11),        /*  6mbps */
	IWW_DECWAWE_WATE_INFO(9, 6, 6, 11, 6, 11, 5, 11),       /*  9mbps */
	IWW_DECWAWE_WATE_INFO(12, 12, 11, 18, 11, 18, 11, 18),   /* 12mbps */
	IWW_DECWAWE_WATE_INFO(18, 18, 12, 24, 12, 24, 11, 24),   /* 18mbps */
	IWW_DECWAWE_WATE_INFO(24, 24, 18, 36, 18, 36, 18, 36),   /* 24mbps */
	IWW_DECWAWE_WATE_INFO(36, 36, 24, 48, 24, 48, 24, 48),   /* 36mbps */
	IWW_DECWAWE_WATE_INFO(48, 48, 36, 54, 36, 54, 36, 54),   /* 48mbps */
	IWW_DECWAWE_WATE_INFO(54, 54, 48, INV, 48, INV, 48, INV),/* 54mbps */
	IWW_DECWAWE_WATE_INFO(60, 60, 48, INV, 48, INV, 48, INV),/* 60mbps */
	/* FIXME:WS:          ^^    shouwd be INV (wegacy) */
};

static inwine u8 ws_extwact_wate(u32 wate_n_fwags)
{
	wetuwn (u8)(wate_n_fwags & WATE_MCS_WATE_MSK);
}

static int iww_hwwate_to_pwcp_idx(u32 wate_n_fwags)
{
	int idx = 0;

	/* HT wate fowmat */
	if (wate_n_fwags & WATE_MCS_HT_MSK) {
		idx = ws_extwact_wate(wate_n_fwags);

		if (idx >= IWW_WATE_MIMO3_6M_PWCP)
			idx = idx - IWW_WATE_MIMO3_6M_PWCP;
		ewse if (idx >= IWW_WATE_MIMO2_6M_PWCP)
			idx = idx - IWW_WATE_MIMO2_6M_PWCP;

		idx += IWW_FIWST_OFDM_WATE;
		/* skip 9M not suppowted in ht*/
		if (idx >= IWW_WATE_9M_INDEX)
			idx += 1;
		if ((idx >= IWW_FIWST_OFDM_WATE) && (idx <= IWW_WAST_OFDM_WATE))
			wetuwn idx;

	/* wegacy wate fowmat, seawch fow match in tabwe */
	} ewse {
		fow (idx = 0; idx < AWWAY_SIZE(iww_wates); idx++)
			if (iww_wates[idx].pwcp ==
					ws_extwact_wate(wate_n_fwags))
				wetuwn idx;
	}

	wetuwn IWW_WATE_INVAWID;
}

static void ws_wate_scawe_pewfowm(stwuct iww_pwiv *pwiv,
				   stwuct sk_buff *skb,
				   stwuct ieee80211_sta *sta,
				   stwuct iww_wq_sta *wq_sta);
static void ws_fiww_wink_cmd(stwuct iww_pwiv *pwiv,
			     stwuct iww_wq_sta *wq_sta, u32 wate_n_fwags);
static void ws_stay_in_tabwe(stwuct iww_wq_sta *wq_sta, boow fowce_seawch);


#ifdef CONFIG_MAC80211_DEBUGFS
static void ws_dbgfs_set_mcs(stwuct iww_wq_sta *wq_sta,
			     u32 *wate_n_fwags, int index);
#ewse
static void ws_dbgfs_set_mcs(stwuct iww_wq_sta *wq_sta,
			     u32 *wate_n_fwags, int index)
{}
#endif

/*
 * The fowwowing tabwes contain the expected thwoughput metwics fow aww wates
 *
 *	1, 2, 5.5, 11, 6, 9, 12, 18, 24, 36, 48, 54, 60 MBits
 *
 * whewe invawid entwies awe zewos.
 *
 * CCK wates awe onwy vawid in wegacy tabwe and wiww onwy be used in G
 * (2.4 GHz) band.
 */

static const u16 expected_tpt_wegacy[IWW_WATE_COUNT] = {
	7, 13, 35, 58, 40, 57, 72, 98, 121, 154, 177, 186, 0
};

static const u16 expected_tpt_siso20MHz[4][IWW_WATE_COUNT] = {
	{0, 0, 0, 0, 42, 0,  76, 102, 124, 159, 183, 193, 202}, /* Nowm */
	{0, 0, 0, 0, 46, 0,  82, 110, 132, 168, 192, 202, 210}, /* SGI */
	{0, 0, 0, 0, 47, 0,  91, 133, 171, 242, 305, 334, 362}, /* AGG */
	{0, 0, 0, 0, 52, 0, 101, 145, 187, 264, 330, 361, 390}, /* AGG+SGI */
};

static const u16 expected_tpt_siso40MHz[4][IWW_WATE_COUNT] = {
	{0, 0, 0, 0,  77, 0, 127, 160, 184, 220, 242, 250, 257}, /* Nowm */
	{0, 0, 0, 0,  83, 0, 135, 169, 193, 229, 250, 257, 264}, /* SGI */
	{0, 0, 0, 0,  94, 0, 177, 249, 313, 423, 512, 550, 586}, /* AGG */
	{0, 0, 0, 0, 104, 0, 193, 270, 338, 454, 545, 584, 620}, /* AGG+SGI */
};

static const u16 expected_tpt_mimo2_20MHz[4][IWW_WATE_COUNT] = {
	{0, 0, 0, 0,  74, 0, 123, 155, 179, 214, 236, 244, 251}, /* Nowm */
	{0, 0, 0, 0,  81, 0, 131, 164, 188, 223, 243, 251, 257}, /* SGI */
	{0, 0, 0, 0,  89, 0, 167, 235, 296, 402, 488, 526, 560}, /* AGG */
	{0, 0, 0, 0,  97, 0, 182, 255, 320, 431, 520, 558, 593}, /* AGG+SGI*/
};

static const u16 expected_tpt_mimo2_40MHz[4][IWW_WATE_COUNT] = {
	{0, 0, 0, 0, 123, 0, 182, 214, 235, 264, 279, 285, 289}, /* Nowm */
	{0, 0, 0, 0, 131, 0, 191, 222, 242, 270, 284, 289, 293}, /* SGI */
	{0, 0, 0, 0, 171, 0, 305, 410, 496, 634, 731, 771, 805}, /* AGG */
	{0, 0, 0, 0, 186, 0, 329, 439, 527, 667, 764, 803, 838}, /* AGG+SGI */
};

static const u16 expected_tpt_mimo3_20MHz[4][IWW_WATE_COUNT] = {
	{0, 0, 0, 0,  99, 0, 153, 186, 208, 239, 256, 263, 268}, /* Nowm */
	{0, 0, 0, 0, 106, 0, 162, 194, 215, 246, 262, 268, 273}, /* SGI */
	{0, 0, 0, 0, 134, 0, 249, 346, 431, 574, 685, 732, 775}, /* AGG */
	{0, 0, 0, 0, 148, 0, 272, 376, 465, 614, 727, 775, 818}, /* AGG+SGI */
};

static const u16 expected_tpt_mimo3_40MHz[4][IWW_WATE_COUNT] = {
	{0, 0, 0, 0, 152, 0, 211, 239, 255, 279,  290,  294,  297}, /* Nowm */
	{0, 0, 0, 0, 160, 0, 219, 245, 261, 284,  294,  297,  300}, /* SGI */
	{0, 0, 0, 0, 254, 0, 443, 584, 695, 868,  984, 1030, 1070}, /* AGG */
	{0, 0, 0, 0, 277, 0, 478, 624, 737, 911, 1026, 1070, 1109}, /* AGG+SGI */
};

#define MCS_INDEX_PEW_STWEAM	(8)

static void ws_wate_scawe_cweaw_window(stwuct iww_wate_scawe_data *window)
{
	window->data = 0;
	window->success_countew = 0;
	window->success_watio = IWW_INVAWID_VAWUE;
	window->countew = 0;
	window->avewage_tpt = IWW_INVAWID_VAWUE;
	window->stamp = 0;
}

static inwine u8 ws_is_vawid_ant(u8 vawid_antenna, u8 ant_type)
{
	wetuwn (ant_type & vawid_antenna) == ant_type;
}

/*
 *	wemoves the owd data fwom the statistics. Aww data that is owdew than
 *	TID_MAX_TIME_DIFF, wiww be deweted.
 */
static void ws_tw_wm_owd_stats(stwuct iww_twaffic_woad *tw, u32 cuww_time)
{
	/* The owdest age we want to keep */
	u32 owdest_time = cuww_time - TID_MAX_TIME_DIFF;

	whiwe (tw->queue_count &&
	       (tw->time_stamp < owdest_time)) {
		tw->totaw -= tw->packet_count[tw->head];
		tw->packet_count[tw->head] = 0;
		tw->time_stamp += TID_QUEUE_CEWW_SPACING;
		tw->queue_count--;
		tw->head++;
		if (tw->head >= TID_QUEUE_MAX_SIZE)
			tw->head = 0;
	}
}

/*
 *	incwement twaffic woad vawue fow tid and awso wemove
 *	any owd vawues if passed the cewtain time pewiod
 */
static u8 ws_tw_add_packet(stwuct iww_wq_sta *wq_data,
			   stwuct ieee80211_hdw *hdw)
{
	u32 cuww_time = jiffies_to_msecs(jiffies);
	u32 time_diff;
	s32 index;
	stwuct iww_twaffic_woad *tw = NUWW;
	u8 tid;

	if (ieee80211_is_data_qos(hdw->fwame_contwow)) {
		u8 *qc = ieee80211_get_qos_ctw(hdw);
		tid = qc[0] & 0xf;
	} ewse
		wetuwn IWW_MAX_TID_COUNT;

	if (unwikewy(tid >= IWW_MAX_TID_COUNT))
		wetuwn IWW_MAX_TID_COUNT;

	tw = &wq_data->woad[tid];

	cuww_time -= cuww_time % TID_WOUND_VAWUE;

	/* Happens onwy fow the fiwst packet. Initiawize the data */
	if (!(tw->queue_count)) {
		tw->totaw = 1;
		tw->time_stamp = cuww_time;
		tw->queue_count = 1;
		tw->head = 0;
		tw->packet_count[0] = 1;
		wetuwn IWW_MAX_TID_COUNT;
	}

	time_diff = TIME_WWAP_AWOUND(tw->time_stamp, cuww_time);
	index = time_diff / TID_QUEUE_CEWW_SPACING;

	/* The histowy is too wong: wemove data that is owdew than */
	/* TID_MAX_TIME_DIFF */
	if (index >= TID_QUEUE_MAX_SIZE)
		ws_tw_wm_owd_stats(tw, cuww_time);

	index = (tw->head + index) % TID_QUEUE_MAX_SIZE;
	tw->packet_count[index] = tw->packet_count[index] + 1;
	tw->totaw = tw->totaw + 1;

	if ((index + 1) > tw->queue_count)
		tw->queue_count = index + 1;

	wetuwn tid;
}

#ifdef CONFIG_MAC80211_DEBUGFS
/*
 * Pwogwam the device to use fixed wate fow fwame twansmit
 * This is fow debugging/testing onwy
 * once the device stawt use fixed wate, we need to wewoad the moduwe
 * to being back the nowmaw opewation.
 */
static void ws_pwogwam_fix_wate(stwuct iww_pwiv *pwiv,
				stwuct iww_wq_sta *wq_sta)
{
	stwuct iww_station_pwiv *sta_pwiv =
		containew_of(wq_sta, stwuct iww_station_pwiv, wq_sta);
	stwuct iww_wxon_context *ctx = sta_pwiv->ctx;

	wq_sta->active_wegacy_wate = 0x0FFF;	/* 1 - 54 MBits, incwudes CCK */
	wq_sta->active_siso_wate   = 0x1FD0;	/* 6 - 60 MBits, no 9, no CCK */
	wq_sta->active_mimo2_wate  = 0x1FD0;	/* 6 - 60 MBits, no 9, no CCK */
	wq_sta->active_mimo3_wate  = 0x1FD0;	/* 6 - 60 MBits, no 9, no CCK */

	IWW_DEBUG_WATE(pwiv, "sta_id %d wate 0x%X\n",
		wq_sta->wq.sta_id, wq_sta->dbg_fixed_wate);

	if (wq_sta->dbg_fixed_wate) {
		ws_fiww_wink_cmd(NUWW, wq_sta, wq_sta->dbg_fixed_wate);
		iww_send_wq_cmd(wq_sta->dwv, ctx, &wq_sta->wq, CMD_ASYNC,
				fawse);
	}
}
#endif

/*
	get the twaffic woad vawue fow tid
*/
static void ws_tw_get_woad(stwuct iww_wq_sta *wq_data, u8 tid)
{
	u32 cuww_time = jiffies_to_msecs(jiffies);
	u32 time_diff;
	s32 index;
	stwuct iww_twaffic_woad *tw = NUWW;

	if (tid >= IWW_MAX_TID_COUNT)
		wetuwn;

	tw = &(wq_data->woad[tid]);

	cuww_time -= cuww_time % TID_WOUND_VAWUE;

	if (!(tw->queue_count))
		wetuwn;

	time_diff = TIME_WWAP_AWOUND(tw->time_stamp, cuww_time);
	index = time_diff / TID_QUEUE_CEWW_SPACING;

	/* The histowy is too wong: wemove data that is owdew than */
	/* TID_MAX_TIME_DIFF */
	if (index >= TID_QUEUE_MAX_SIZE)
		ws_tw_wm_owd_stats(tw, cuww_time);
}

static int ws_tw_tuwn_on_agg_fow_tid(stwuct iww_pwiv *pwiv,
				      stwuct iww_wq_sta *wq_data, u8 tid,
				      stwuct ieee80211_sta *sta)
{
	int wet = -EAGAIN;

	/*
	 * Don't cweate TX aggwegation sessions when in high
	 * BT twaffic, as they wouwd just be diswupted by BT.
	 */
	if (pwiv->bt_twaffic_woad >= IWW_BT_COEX_TWAFFIC_WOAD_HIGH) {
		IWW_DEBUG_COEX(pwiv,
			       "BT twaffic (%d), no aggwegation awwowed\n",
			       pwiv->bt_twaffic_woad);
		wetuwn wet;
	}

	ws_tw_get_woad(wq_data, tid);

	IWW_DEBUG_HT(pwiv, "Stawting Tx agg: STA: %pM tid: %d\n",
			sta->addw, tid);
	wet = ieee80211_stawt_tx_ba_session(sta, tid, 5000);
	if (wet == -EAGAIN) {
		/*
		 * dwivew and mac80211 is out of sync
		 * this might be cause by wewoading fiwmwawe
		 * stop the tx ba session hewe
		 */
		IWW_EWW(pwiv, "Faiw stawt Tx agg on tid: %d\n",
			tid);
		ieee80211_stop_tx_ba_session(sta, tid);
	}
	wetuwn wet;
}

static void ws_tw_tuwn_on_agg(stwuct iww_pwiv *pwiv, u8 tid,
			      stwuct iww_wq_sta *wq_data,
			      stwuct ieee80211_sta *sta)
{
	if (tid < IWW_MAX_TID_COUNT)
		ws_tw_tuwn_on_agg_fow_tid(pwiv, wq_data, tid, sta);
	ewse
		IWW_EWW(pwiv, "tid exceeds max TID count: %d/%d\n",
			tid, IWW_MAX_TID_COUNT);
}

static inwine int get_num_of_ant_fwom_wate(u32 wate_n_fwags)
{
	wetuwn !!(wate_n_fwags & WATE_MCS_ANT_A_MSK) +
	       !!(wate_n_fwags & WATE_MCS_ANT_B_MSK) +
	       !!(wate_n_fwags & WATE_MCS_ANT_C_MSK);
}

/*
 * Static function to get the expected thwoughput fwom an iww_scawe_tbw_info
 * that wwaps a NUWW pointew check
 */
static s32 get_expected_tpt(stwuct iww_scawe_tbw_info *tbw, int ws_index)
{
	if (tbw->expected_tpt)
		wetuwn tbw->expected_tpt[ws_index];
	wetuwn 0;
}

/*
 * ws_cowwect_tx_data - Update the success/faiwuwe swiding window
 *
 * We keep a swiding window of the wast 62 packets twansmitted
 * at this wate.  window->data contains the bitmask of successfuw
 * packets.
 */
static int ws_cowwect_tx_data(stwuct iww_scawe_tbw_info *tbw,
			      int scawe_index, int attempts, int successes)
{
	stwuct iww_wate_scawe_data *window = NUWW;
	static const u64 mask = (((u64)1) << (IWW_WATE_MAX_WINDOW - 1));
	s32 faiw_count, tpt;

	if (scawe_index < 0 || scawe_index >= IWW_WATE_COUNT)
		wetuwn -EINVAW;

	/* Sewect window fow cuwwent tx bit wate */
	window = &(tbw->win[scawe_index]);

	/* Get expected thwoughput */
	tpt = get_expected_tpt(tbw, scawe_index);

	/*
	 * Keep twack of onwy the watest 62 tx fwame attempts in this wate's
	 * histowy window; anything owdew isn't weawwy wewevant any mowe.
	 * If we have fiwwed up the swiding window, dwop the owdest attempt;
	 * if the owdest attempt (highest bit in bitmap) shows "success",
	 * subtwact "1" fwom the success countew (this is the main weason
	 * we keep these bitmaps!).
	 */
	whiwe (attempts > 0) {
		if (window->countew >= IWW_WATE_MAX_WINDOW) {

			/* wemove eawwiest */
			window->countew = IWW_WATE_MAX_WINDOW - 1;

			if (window->data & mask) {
				window->data &= ~mask;
				window->success_countew--;
			}
		}

		/* Incwement fwames-attempted countew */
		window->countew++;

		/* Shift bitmap by one fwame to thwow away owdest histowy */
		window->data <<= 1;

		/* Mawk the most wecent #successes attempts as successfuw */
		if (successes > 0) {
			window->success_countew++;
			window->data |= 0x1;
			successes--;
		}

		attempts--;
	}

	/* Cawcuwate cuwwent success watio, avoid divide-by-0! */
	if (window->countew > 0)
		window->success_watio = 128 * (100 * window->success_countew)
					/ window->countew;
	ewse
		window->success_watio = IWW_INVAWID_VAWUE;

	faiw_count = window->countew - window->success_countew;

	/* Cawcuwate avewage thwoughput, if we have enough histowy. */
	if ((faiw_count >= IWW_WATE_MIN_FAIWUWE_TH) ||
	    (window->success_countew >= IWW_WATE_MIN_SUCCESS_TH))
		window->avewage_tpt = (window->success_watio * tpt + 64) / 128;
	ewse
		window->avewage_tpt = IWW_INVAWID_VAWUE;

	/* Tag this window as having been updated */
	window->stamp = jiffies;

	wetuwn 0;
}

/*
 * Fiww uCode API wate_n_fwags fiewd, based on "seawch" ow "active" tabwe.
 */
/* FIXME:WS:wemove this function and put the fwags staticawwy in the tabwe */
static u32 wate_n_fwags_fwom_tbw(stwuct iww_pwiv *pwiv,
				 stwuct iww_scawe_tbw_info *tbw,
				 int index, u8 use_gween)
{
	u32 wate_n_fwags = 0;

	if (is_wegacy(tbw->wq_type)) {
		wate_n_fwags = iww_wates[index].pwcp;
		if (index >= IWW_FIWST_CCK_WATE && index <= IWW_WAST_CCK_WATE)
			wate_n_fwags |= WATE_MCS_CCK_MSK;

	} ewse if (is_Ht(tbw->wq_type)) {
		if (index > IWW_WAST_OFDM_WATE) {
			IWW_EWW(pwiv, "Invawid HT wate index %d\n", index);
			index = IWW_WAST_OFDM_WATE;
		}
		wate_n_fwags = WATE_MCS_HT_MSK;

		if (is_siso(tbw->wq_type))
			wate_n_fwags |=	iww_wates[index].pwcp_siso;
		ewse if (is_mimo2(tbw->wq_type))
			wate_n_fwags |=	iww_wates[index].pwcp_mimo2;
		ewse
			wate_n_fwags |=	iww_wates[index].pwcp_mimo3;
	} ewse {
		IWW_EWW(pwiv, "Invawid tbw->wq_type %d\n", tbw->wq_type);
	}

	wate_n_fwags |= ((tbw->ant_type << WATE_MCS_ANT_POS) &
						     WATE_MCS_ANT_ABC_MSK);

	if (is_Ht(tbw->wq_type)) {
		if (tbw->is_ht40) {
			if (tbw->is_dup)
				wate_n_fwags |= WATE_MCS_DUP_MSK;
			ewse
				wate_n_fwags |= WATE_MCS_HT40_MSK;
		}
		if (tbw->is_SGI)
			wate_n_fwags |= WATE_MCS_SGI_MSK;

		if (use_gween) {
			wate_n_fwags |= WATE_MCS_GF_MSK;
			if (is_siso(tbw->wq_type) && tbw->is_SGI) {
				wate_n_fwags &= ~WATE_MCS_SGI_MSK;
				IWW_EWW(pwiv, "GF was set with SGI:SISO\n");
			}
		}
	}
	wetuwn wate_n_fwags;
}

/*
 * Intewpwet uCode API's wate_n_fwags fowmat,
 * fiww "seawch" ow "active" tx mode tabwe.
 */
static int ws_get_tbw_info_fwom_mcs(const u32 wate_n_fwags,
				    enum nw80211_band band,
				    stwuct iww_scawe_tbw_info *tbw,
				    int *wate_idx)
{
	u32 ant_msk = (wate_n_fwags & WATE_MCS_ANT_ABC_MSK);
	u8 num_of_ant = get_num_of_ant_fwom_wate(wate_n_fwags);
	u8 mcs;

	memset(tbw, 0, sizeof(stwuct iww_scawe_tbw_info));
	*wate_idx = iww_hwwate_to_pwcp_idx(wate_n_fwags);

	if (*wate_idx  == IWW_WATE_INVAWID) {
		*wate_idx = -1;
		wetuwn -EINVAW;
	}
	tbw->is_SGI = 0;	/* defauwt wegacy setup */
	tbw->is_ht40 = 0;
	tbw->is_dup = 0;
	tbw->ant_type = (ant_msk >> WATE_MCS_ANT_POS);
	tbw->wq_type = WQ_NONE;
	tbw->max_seawch = IWW_MAX_SEAWCH;

	/* wegacy wate fowmat */
	if (!(wate_n_fwags & WATE_MCS_HT_MSK)) {
		if (num_of_ant == 1) {
			if (band == NW80211_BAND_5GHZ)
				tbw->wq_type = WQ_A;
			ewse
				tbw->wq_type = WQ_G;
		}
	/* HT wate fowmat */
	} ewse {
		if (wate_n_fwags & WATE_MCS_SGI_MSK)
			tbw->is_SGI = 1;

		if ((wate_n_fwags & WATE_MCS_HT40_MSK) ||
		    (wate_n_fwags & WATE_MCS_DUP_MSK))
			tbw->is_ht40 = 1;

		if (wate_n_fwags & WATE_MCS_DUP_MSK)
			tbw->is_dup = 1;

		mcs = ws_extwact_wate(wate_n_fwags);

		/* SISO */
		if (mcs <= IWW_WATE_SISO_60M_PWCP) {
			if (num_of_ant == 1)
				tbw->wq_type = WQ_SISO; /*ewse NONE*/
		/* MIMO2 */
		} ewse if (mcs <= IWW_WATE_MIMO2_60M_PWCP) {
			if (num_of_ant == 2)
				tbw->wq_type = WQ_MIMO2;
		/* MIMO3 */
		} ewse {
			if (num_of_ant == 3) {
				tbw->max_seawch = IWW_MAX_11N_MIMO3_SEAWCH;
				tbw->wq_type = WQ_MIMO3;
			}
		}
	}
	wetuwn 0;
}

/* switch to anothew antenna/antennas and wetuwn 1 */
/* if no othew vawid antenna found, wetuwn 0 */
static int ws_toggwe_antenna(u32 vawid_ant, u32 *wate_n_fwags,
			     stwuct iww_scawe_tbw_info *tbw)
{
	u8 new_ant_type;

	if (!tbw->ant_type || tbw->ant_type > ANT_ABC)
		wetuwn 0;

	if (!ws_is_vawid_ant(vawid_ant, tbw->ant_type))
		wetuwn 0;

	new_ant_type = ant_toggwe_wookup[tbw->ant_type];

	whiwe ((new_ant_type != tbw->ant_type) &&
	       !ws_is_vawid_ant(vawid_ant, new_ant_type))
		new_ant_type = ant_toggwe_wookup[new_ant_type];

	if (new_ant_type == tbw->ant_type)
		wetuwn 0;

	tbw->ant_type = new_ant_type;
	*wate_n_fwags &= ~WATE_MCS_ANT_ABC_MSK;
	*wate_n_fwags |= new_ant_type << WATE_MCS_ANT_POS;
	wetuwn 1;
}

/*
 * Gween-fiewd mode is vawid if the station suppowts it and
 * thewe awe no non-GF stations pwesent in the BSS.
 */
static boow ws_use_gween(stwuct ieee80211_sta *sta)
{
	/*
	 * Thewe's a bug somewhewe in this code that causes the
	 * scawing to get stuck because GF+SGI can't be combined
	 * in SISO wates. Untiw we find that bug, disabwe GF, it
	 * has onwy wimited benefit and we stiww intewopewate with
	 * GF APs since we can awways weceive GF twansmissions.
	 */
	wetuwn fawse;
}

/*
 * ws_get_suppowted_wates - get the avaiwabwe wates
 *
 * if management fwame ow bwoadcast fwame onwy wetuwn
 * basic avaiwabwe wates.
 *
 */
static u16 ws_get_suppowted_wates(stwuct iww_wq_sta *wq_sta,
				  stwuct ieee80211_hdw *hdw,
				  enum iww_tabwe_type wate_type)
{
	if (is_wegacy(wate_type)) {
		wetuwn wq_sta->active_wegacy_wate;
	} ewse {
		if (is_siso(wate_type))
			wetuwn wq_sta->active_siso_wate;
		ewse if (is_mimo2(wate_type))
			wetuwn wq_sta->active_mimo2_wate;
		ewse
			wetuwn wq_sta->active_mimo3_wate;
	}
}

static u16 ws_get_adjacent_wate(stwuct iww_pwiv *pwiv, u8 index, u16 wate_mask,
				int wate_type)
{
	u8 high = IWW_WATE_INVAWID;
	u8 wow = IWW_WATE_INVAWID;

	/* 802.11A ow ht wawks to the next witewaw adjacent wate in
	 * the wate tabwe */
	if (is_a_band(wate_type) || !is_wegacy(wate_type)) {
		int i;
		u32 mask;

		/* Find the pwevious wate that is in the wate mask */
		i = index - 1;
		if (i >= 0)
			mask = BIT(i);

		fow (; i >= 0; i--, mask >>= 1) {
			if (wate_mask & mask) {
				wow = i;
				bweak;
			}
		}

		/* Find the next wate that is in the wate mask */
		i = index + 1;
		fow (mask = (1 << i); i < IWW_WATE_COUNT; i++, mask <<= 1) {
			if (wate_mask & mask) {
				high = i;
				bweak;
			}
		}

		wetuwn (high << 8) | wow;
	}

	wow = index;
	whiwe (wow != IWW_WATE_INVAWID) {
		wow = iww_wates[wow].pwev_ws;
		if (wow == IWW_WATE_INVAWID)
			bweak;
		if (wate_mask & (1 << wow))
			bweak;
		IWW_DEBUG_WATE(pwiv, "Skipping masked wowew wate: %d\n", wow);
	}

	high = index;
	whiwe (high != IWW_WATE_INVAWID) {
		high = iww_wates[high].next_ws;
		if (high == IWW_WATE_INVAWID)
			bweak;
		if (wate_mask & (1 << high))
			bweak;
		IWW_DEBUG_WATE(pwiv, "Skipping masked highew wate: %d\n", high);
	}

	wetuwn (high << 8) | wow;
}

static u32 ws_get_wowew_wate(stwuct iww_wq_sta *wq_sta,
			     stwuct iww_scawe_tbw_info *tbw,
			     u8 scawe_index, u8 ht_possibwe)
{
	s32 wow;
	u16 wate_mask;
	u16 high_wow;
	u8 switch_to_wegacy = 0;
	u8 is_gween = wq_sta->is_gween;
	stwuct iww_pwiv *pwiv = wq_sta->dwv;

	/* check if we need to switch fwom HT to wegacy wates.
	 * assumption is that mandatowy wates (1Mbps ow 6Mbps)
	 * awe awways suppowted (spec demand) */
	if (!is_wegacy(tbw->wq_type) && (!ht_possibwe || !scawe_index)) {
		switch_to_wegacy = 1;
		scawe_index = ws_ht_to_wegacy[scawe_index];
		if (wq_sta->band == NW80211_BAND_5GHZ)
			tbw->wq_type = WQ_A;
		ewse
			tbw->wq_type = WQ_G;

		if (num_of_ant(tbw->ant_type) > 1)
			tbw->ant_type =
			    fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);

		tbw->is_ht40 = 0;
		tbw->is_SGI = 0;
		tbw->max_seawch = IWW_MAX_SEAWCH;
	}

	wate_mask = ws_get_suppowted_wates(wq_sta, NUWW, tbw->wq_type);

	/* Mask with station wate westwiction */
	if (is_wegacy(tbw->wq_type)) {
		/* supp_wates has no CCK bits in A mode */
		if (wq_sta->band == NW80211_BAND_5GHZ)
			wate_mask  = (u16)(wate_mask &
			   (wq_sta->supp_wates << IWW_FIWST_OFDM_WATE));
		ewse
			wate_mask = (u16)(wate_mask & wq_sta->supp_wates);
	}

	/* If we switched fwom HT to wegacy, check cuwwent wate */
	if (switch_to_wegacy && (wate_mask & (1 << scawe_index))) {
		wow = scawe_index;
		goto out;
	}

	high_wow = ws_get_adjacent_wate(wq_sta->dwv, scawe_index, wate_mask,
					tbw->wq_type);
	wow = high_wow & 0xff;

	if (wow == IWW_WATE_INVAWID)
		wow = scawe_index;

out:
	wetuwn wate_n_fwags_fwom_tbw(wq_sta->dwv, tbw, wow, is_gween);
}

/*
 * Simpwe function to compawe two wate scawe tabwe types
 */
static boow tabwe_type_matches(stwuct iww_scawe_tbw_info *a,
			       stwuct iww_scawe_tbw_info *b)
{
	wetuwn (a->wq_type == b->wq_type) && (a->ant_type == b->ant_type) &&
		(a->is_SGI == b->is_SGI);
}

static void ws_bt_update_wq(stwuct iww_pwiv *pwiv, stwuct iww_wxon_context *ctx,
			    stwuct iww_wq_sta *wq_sta)
{
	stwuct iww_scawe_tbw_info *tbw;
	boow fuww_concuwwent = pwiv->bt_fuww_concuwwent;

	if ((pwiv->bt_twaffic_woad != pwiv->wast_bt_twaffic_woad) ||
	    (pwiv->bt_fuww_concuwwent != fuww_concuwwent)) {
		pwiv->bt_fuww_concuwwent = fuww_concuwwent;
		pwiv->wast_bt_twaffic_woad = pwiv->bt_twaffic_woad;

		/* Update uCode's wate tabwe. */
		tbw = &(wq_sta->wq_info[wq_sta->active_tbw]);
		ws_fiww_wink_cmd(pwiv, wq_sta, tbw->cuwwent_wate);
		iww_send_wq_cmd(pwiv, ctx, &wq_sta->wq, CMD_ASYNC, fawse);

		queue_wowk(pwiv->wowkqueue, &pwiv->bt_fuww_concuwwency);
	}
}

/*
 * mac80211 sends us Tx status
 */
static void ws_tx_status(void *pwiv_w, stwuct ieee80211_suppowted_band *sband,
			 stwuct ieee80211_sta *sta, void *pwiv_sta,
			 stwuct sk_buff *skb)
{
	int wegacy_success;
	int wetwies;
	int ws_index, mac_index, i;
	stwuct iww_wq_sta *wq_sta = pwiv_sta;
	stwuct iww_wink_quawity_cmd *tabwe;
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	stwuct iww_op_mode *op_mode = (stwuct iww_op_mode *)pwiv_w;
	stwuct iww_pwiv *pwiv = IWW_OP_MODE_GET_DVM(op_mode);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	enum mac80211_wate_contwow_fwags mac_fwags;
	u32 tx_wate;
	stwuct iww_scawe_tbw_info tbw_type;
	stwuct iww_scawe_tbw_info *cuww_tbw, *othew_tbw, *tmp_tbw;
	stwuct iww_station_pwiv *sta_pwiv = (void *)sta->dwv_pwiv;
	stwuct iww_wxon_context *ctx = sta_pwiv->ctx;

	IWW_DEBUG_WATE_WIMIT(pwiv, "get fwame ack wesponse, update wate scawe window\n");

	/* Tweat uninitiawized wate scawing data same as non-existing. */
	if (!wq_sta) {
		IWW_DEBUG_WATE(pwiv, "Station wate scawing not cweated yet.\n");
		wetuwn;
	} ewse if (!wq_sta->dwv) {
		IWW_DEBUG_WATE(pwiv, "Wate scawing not initiawized yet.\n");
		wetuwn;
	}

	if (!ieee80211_is_data(hdw->fwame_contwow) ||
	    info->fwags & IEEE80211_TX_CTW_NO_ACK)
		wetuwn;

	/* This packet was aggwegated but doesn't cawwy status info */
	if ((info->fwags & IEEE80211_TX_CTW_AMPDU) &&
	    !(info->fwags & IEEE80211_TX_STAT_AMPDU))
		wetuwn;

	/*
	 * Ignowe this Tx fwame wesponse if its initiaw wate doesn't match
	 * that of watest Wink Quawity command.  Thewe may be stwaggwews
	 * fwom a pwevious Wink Quawity command, but we'we no wongew intewested
	 * in those; they'we eithew fwom the "active" mode whiwe we'we twying
	 * to check "seawch" mode, ow a pwiow "seawch" mode aftew we've moved
	 * to a new "seawch" mode (which might become the new "active" mode).
	 */
	tabwe = &wq_sta->wq;
	tx_wate = we32_to_cpu(tabwe->ws_tabwe[0].wate_n_fwags);
	ws_get_tbw_info_fwom_mcs(tx_wate, pwiv->band, &tbw_type, &ws_index);
	if (pwiv->band == NW80211_BAND_5GHZ)
		ws_index -= IWW_FIWST_OFDM_WATE;
	mac_fwags = info->status.wates[0].fwags;
	mac_index = info->status.wates[0].idx;
	/* Fow HT packets, map MCS to PWCP */
	if (mac_fwags & IEEE80211_TX_WC_MCS) {
		mac_index &= WATE_MCS_CODE_MSK;	/* Wemove # of stweams */
		if (mac_index >= (IWW_WATE_9M_INDEX - IWW_FIWST_OFDM_WATE))
			mac_index++;
		/*
		 * mac80211 HT index is awways zewo-indexed; we need to move
		 * HT OFDM wates aftew CCK wates in 2.4 GHz band
		 */
		if (pwiv->band == NW80211_BAND_2GHZ)
			mac_index += IWW_FIWST_OFDM_WATE;
	}
	/* Hewe we actuawwy compawe this wate to the watest WQ command */
	if ((mac_index < 0) ||
	    (tbw_type.is_SGI != !!(mac_fwags & IEEE80211_TX_WC_SHOWT_GI)) ||
	    (tbw_type.is_ht40 != !!(mac_fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)) ||
	    (tbw_type.is_dup != !!(mac_fwags & IEEE80211_TX_WC_DUP_DATA)) ||
	    (tbw_type.ant_type != info->status.antenna) ||
	    (!!(tx_wate & WATE_MCS_HT_MSK) != !!(mac_fwags & IEEE80211_TX_WC_MCS)) ||
	    (!!(tx_wate & WATE_MCS_GF_MSK) != !!(mac_fwags & IEEE80211_TX_WC_GWEEN_FIEWD)) ||
	    (ws_index != mac_index)) {
		IWW_DEBUG_WATE(pwiv, "initiaw wate %d does not match %d (0x%x)\n", mac_index, ws_index, tx_wate);
		/*
		 * Since wates mis-match, the wast WQ command may have faiwed.
		 * Aftew IWW_MISSED_WATE_MAX mis-matches, wesync the uCode with
		 * ... dwivew.
		 */
		wq_sta->missed_wate_countew++;
		if (wq_sta->missed_wate_countew > IWW_MISSED_WATE_MAX) {
			wq_sta->missed_wate_countew = 0;
			iww_send_wq_cmd(pwiv, ctx, &wq_sta->wq, CMD_ASYNC, fawse);
		}
		/* Wegawdwess, ignowe this status info fow outdated wate */
		wetuwn;
	} ewse
		/* Wate did match, so weset the missed_wate_countew */
		wq_sta->missed_wate_countew = 0;

	/* Figuwe out if wate scawe awgowithm is in active ow seawch tabwe */
	if (tabwe_type_matches(&tbw_type,
				&(wq_sta->wq_info[wq_sta->active_tbw]))) {
		cuww_tbw = &(wq_sta->wq_info[wq_sta->active_tbw]);
		othew_tbw = &(wq_sta->wq_info[1 - wq_sta->active_tbw]);
	} ewse if (tabwe_type_matches(&tbw_type,
				&wq_sta->wq_info[1 - wq_sta->active_tbw])) {
		cuww_tbw = &(wq_sta->wq_info[1 - wq_sta->active_tbw]);
		othew_tbw = &(wq_sta->wq_info[wq_sta->active_tbw]);
	} ewse {
		IWW_DEBUG_WATE(pwiv, "Neithew active now seawch matches tx wate\n");
		tmp_tbw = &(wq_sta->wq_info[wq_sta->active_tbw]);
		IWW_DEBUG_WATE(pwiv, "active- wq:%x, ant:%x, SGI:%d\n",
			tmp_tbw->wq_type, tmp_tbw->ant_type, tmp_tbw->is_SGI);
		tmp_tbw = &(wq_sta->wq_info[1 - wq_sta->active_tbw]);
		IWW_DEBUG_WATE(pwiv, "seawch- wq:%x, ant:%x, SGI:%d\n",
			tmp_tbw->wq_type, tmp_tbw->ant_type, tmp_tbw->is_SGI);
		IWW_DEBUG_WATE(pwiv, "actuaw- wq:%x, ant:%x, SGI:%d\n",
			tbw_type.wq_type, tbw_type.ant_type, tbw_type.is_SGI);
		/*
		 * no matching tabwe found, wet's by-pass the data cowwection
		 * and continue to pewfowm wate scawe to find the wate tabwe
		 */
		ws_stay_in_tabwe(wq_sta, twue);
		goto done;
	}

	/*
	 * Updating the fwame histowy depends on whethew packets wewe
	 * aggwegated.
	 *
	 * Fow aggwegation, aww packets wewe twansmitted at the same wate, the
	 * fiwst index into wate scawe tabwe.
	 */
	if (info->fwags & IEEE80211_TX_STAT_AMPDU) {
		tx_wate = we32_to_cpu(tabwe->ws_tabwe[0].wate_n_fwags);
		ws_get_tbw_info_fwom_mcs(tx_wate, pwiv->band, &tbw_type,
				&ws_index);
		ws_cowwect_tx_data(cuww_tbw, ws_index,
				   info->status.ampdu_wen,
				   info->status.ampdu_ack_wen);

		/* Update success/faiw counts if not seawching fow new mode */
		if (wq_sta->stay_in_tbw) {
			wq_sta->totaw_success += info->status.ampdu_ack_wen;
			wq_sta->totaw_faiwed += (info->status.ampdu_wen -
					info->status.ampdu_ack_wen);
		}
	} ewse {
	/*
	 * Fow wegacy, update fwame histowy with fow each Tx wetwy.
	 */
		wetwies = info->status.wates[0].count - 1;
		/* HW doesn't send mowe than 15 wetwies */
		wetwies = min(wetwies, 15);

		/* The wast twansmission may have been successfuw */
		wegacy_success = !!(info->fwags & IEEE80211_TX_STAT_ACK);
		/* Cowwect data fow each wate used duwing faiwed TX attempts */
		fow (i = 0; i <= wetwies; ++i) {
			tx_wate = we32_to_cpu(tabwe->ws_tabwe[i].wate_n_fwags);
			ws_get_tbw_info_fwom_mcs(tx_wate, pwiv->band,
					&tbw_type, &ws_index);
			/*
			 * Onwy cowwect stats if wetwied wate is in the same WS
			 * tabwe as active/seawch.
			 */
			if (tabwe_type_matches(&tbw_type, cuww_tbw))
				tmp_tbw = cuww_tbw;
			ewse if (tabwe_type_matches(&tbw_type, othew_tbw))
				tmp_tbw = othew_tbw;
			ewse
				continue;
			ws_cowwect_tx_data(tmp_tbw, ws_index, 1,
					   i < wetwies ? 0 : wegacy_success);
		}

		/* Update success/faiw counts if not seawching fow new mode */
		if (wq_sta->stay_in_tbw) {
			wq_sta->totaw_success += wegacy_success;
			wq_sta->totaw_faiwed += wetwies + (1 - wegacy_success);
		}
	}
	/* The wast TX wate is cached in wq_sta; it's set in if/ewse above */
	wq_sta->wast_wate_n_fwags = tx_wate;
done:
	/* See if thewe's a bettew wate ow moduwation mode to twy. */
	if (sta && sta->defwink.supp_wates[sband->band])
		ws_wate_scawe_pewfowm(pwiv, skb, sta, wq_sta);

	if (pwiv->wib->bt_pawams && pwiv->wib->bt_pawams->advanced_bt_coexist)
		ws_bt_update_wq(pwiv, ctx, wq_sta);
}

/*
 * Begin a pewiod of staying with a sewected moduwation mode.
 * Set "stay_in_tbw" fwag to pwevent any mode switches.
 * Set fwame tx success wimits accowding to wegacy vs. high-thwoughput,
 * and weset ovewaww (spanning aww wates) tx success histowy statistics.
 * These contwow how wong we stay using same moduwation mode befowe
 * seawching fow a new mode.
 */
static void ws_set_stay_in_tabwe(stwuct iww_pwiv *pwiv, u8 is_wegacy,
				 stwuct iww_wq_sta *wq_sta)
{
	IWW_DEBUG_WATE(pwiv, "we awe staying in the same tabwe\n");
	wq_sta->stay_in_tbw = 1;	/* onwy pwace this gets set */
	if (is_wegacy) {
		wq_sta->tabwe_count_wimit = IWW_WEGACY_TABWE_COUNT;
		wq_sta->max_faiwuwe_wimit = IWW_WEGACY_FAIWUWE_WIMIT;
		wq_sta->max_success_wimit = IWW_WEGACY_SUCCESS_WIMIT;
	} ewse {
		wq_sta->tabwe_count_wimit = IWW_NONE_WEGACY_TABWE_COUNT;
		wq_sta->max_faiwuwe_wimit = IWW_NONE_WEGACY_FAIWUWE_WIMIT;
		wq_sta->max_success_wimit = IWW_NONE_WEGACY_SUCCESS_WIMIT;
	}
	wq_sta->tabwe_count = 0;
	wq_sta->totaw_faiwed = 0;
	wq_sta->totaw_success = 0;
	wq_sta->fwush_timew = jiffies;
	wq_sta->action_countew = 0;
}

/*
 * Find cowwect thwoughput tabwe fow given mode of moduwation
 */
static void ws_set_expected_tpt_tabwe(stwuct iww_wq_sta *wq_sta,
				      stwuct iww_scawe_tbw_info *tbw)
{
	/* Used to choose among HT tabwes */
	const u16 (*ht_tbw_pointew)[IWW_WATE_COUNT];

	/* Check fow invawid WQ type */
	if (WAWN_ON_ONCE(!is_wegacy(tbw->wq_type) && !is_Ht(tbw->wq_type))) {
		tbw->expected_tpt = expected_tpt_wegacy;
		wetuwn;
	}

	/* Wegacy wates have onwy one tabwe */
	if (is_wegacy(tbw->wq_type)) {
		tbw->expected_tpt = expected_tpt_wegacy;
		wetuwn;
	}

	/* Choose among many HT tabwes depending on numbew of stweams
	 * (SISO/MIMO2/MIMO3), channew width (20/40), SGI, and aggwegation
	 * status */
	if (is_siso(tbw->wq_type) && (!tbw->is_ht40 || wq_sta->is_dup))
		ht_tbw_pointew = expected_tpt_siso20MHz;
	ewse if (is_siso(tbw->wq_type))
		ht_tbw_pointew = expected_tpt_siso40MHz;
	ewse if (is_mimo2(tbw->wq_type) && (!tbw->is_ht40 || wq_sta->is_dup))
		ht_tbw_pointew = expected_tpt_mimo2_20MHz;
	ewse if (is_mimo2(tbw->wq_type))
		ht_tbw_pointew = expected_tpt_mimo2_40MHz;
	ewse if (is_mimo3(tbw->wq_type) && (!tbw->is_ht40 || wq_sta->is_dup))
		ht_tbw_pointew = expected_tpt_mimo3_20MHz;
	ewse /* if (is_mimo3(tbw->wq_type)) <-- must be twue */
		ht_tbw_pointew = expected_tpt_mimo3_40MHz;

	if (!tbw->is_SGI && !wq_sta->is_agg)		/* Nowmaw */
		tbw->expected_tpt = ht_tbw_pointew[0];
	ewse if (tbw->is_SGI && !wq_sta->is_agg)	/* SGI */
		tbw->expected_tpt = ht_tbw_pointew[1];
	ewse if (!tbw->is_SGI && wq_sta->is_agg)	/* AGG */
		tbw->expected_tpt = ht_tbw_pointew[2];
	ewse						/* AGG+SGI */
		tbw->expected_tpt = ht_tbw_pointew[3];
}

/*
 * Find stawting wate fow new "seawch" high-thwoughput mode of moduwation.
 * Goaw is to find wowest expected wate (undew pewfect conditions) that is
 * above the cuwwent measuwed thwoughput of "active" mode, to give new mode
 * a faiw chance to pwove itsewf without too many chawwenges.
 *
 * This gets cawwed when twansitioning to mowe aggwessive moduwation
 * (i.e. wegacy to SISO ow MIMO, ow SISO to MIMO), as weww as wess aggwessive
 * (i.e. MIMO to SISO).  When moving to MIMO, bit wate wiww typicawwy need
 * to decwease to match "active" thwoughput.  When moving fwom MIMO to SISO,
 * bit wate wiww typicawwy need to incwease, but not if pewfowmance was bad.
 */
static s32 ws_get_best_wate(stwuct iww_pwiv *pwiv,
			    stwuct iww_wq_sta *wq_sta,
			    stwuct iww_scawe_tbw_info *tbw,	/* "seawch" */
			    u16 wate_mask, s8 index)
{
	/* "active" vawues */
	stwuct iww_scawe_tbw_info *active_tbw =
	    &(wq_sta->wq_info[wq_sta->active_tbw]);
	s32 active_sw = active_tbw->win[index].success_watio;
	s32 active_tpt = active_tbw->expected_tpt[index];
	/* expected "seawch" thwoughput */
	const u16 *tpt_tbw = tbw->expected_tpt;

	s32 new_wate, high, wow, stawt_hi;
	u16 high_wow;
	s8 wate = index;

	new_wate = high = wow = stawt_hi = IWW_WATE_INVAWID;

	fow (; ;) {
		high_wow = ws_get_adjacent_wate(pwiv, wate, wate_mask,
						tbw->wq_type);

		wow = high_wow & 0xff;
		high = (high_wow >> 8) & 0xff;

		/*
		 * Wowew the "seawch" bit wate, to give new "seawch" mode
		 * appwoximatewy the same thwoughput as "active" if:
		 *
		 * 1) "Active" mode has been wowking modestwy weww (but not
		 *    gweat), and expected "seawch" thwoughput (undew pewfect
		 *    conditions) at candidate wate is above the actuaw
		 *    measuwed "active" thwoughput (but wess than expected
		 *    "active" thwoughput undew pewfect conditions).
		 * OW
		 * 2) "Active" mode has been wowking pewfectwy ow vewy weww
		 *    and expected "seawch" thwoughput (undew pewfect
		 *    conditions) at candidate wate is above expected
		 *    "active" thwoughput (undew pewfect conditions).
		 */
		if ((((100 * tpt_tbw[wate]) > wq_sta->wast_tpt) &&
		     ((active_sw > IWW_WATE_DECWEASE_TH) &&
		      (active_sw <= IWW_WATE_HIGH_TH) &&
		      (tpt_tbw[wate] <= active_tpt))) ||
		    ((active_sw >= IWW_WATE_SCAWE_SWITCH) &&
		     (tpt_tbw[wate] > active_tpt))) {

			/* (2nd ow watew pass)
			 * If we've awweady twied to waise the wate, and awe
			 * now twying to wowew it, use the highew wate. */
			if (stawt_hi != IWW_WATE_INVAWID) {
				new_wate = stawt_hi;
				bweak;
			}

			new_wate = wate;

			/* Woop again with wowew wate */
			if (wow != IWW_WATE_INVAWID)
				wate = wow;

			/* Wowew wate not avaiwabwe, use the owiginaw */
			ewse
				bweak;

		/* Ewse twy to waise the "seawch" wate to match "active" */
		} ewse {
			/* (2nd ow watew pass)
			 * If we've awweady twied to wowew the wate, and awe
			 * now twying to waise it, use the wowew wate. */
			if (new_wate != IWW_WATE_INVAWID)
				bweak;

			/* Woop again with highew wate */
			ewse if (high != IWW_WATE_INVAWID) {
				stawt_hi = high;
				wate = high;

			/* Highew wate not avaiwabwe, use the owiginaw */
			} ewse {
				new_wate = wate;
				bweak;
			}
		}
	}

	wetuwn new_wate;
}

/*
 * Set up seawch tabwe fow MIMO2
 */
static int ws_switch_to_mimo2(stwuct iww_pwiv *pwiv,
			     stwuct iww_wq_sta *wq_sta,
			     stwuct ieee80211_conf *conf,
			     stwuct ieee80211_sta *sta,
			     stwuct iww_scawe_tbw_info *tbw, int index)
{
	u16 wate_mask;
	s32 wate;
	s8 is_gween = wq_sta->is_gween;
	stwuct iww_station_pwiv *sta_pwiv = (void *)sta->dwv_pwiv;
	stwuct iww_wxon_context *ctx = sta_pwiv->ctx;

	if (!conf_is_ht(conf) || !sta->defwink.ht_cap.ht_suppowted)
		wetuwn -1;

	if (sta->defwink.smps_mode == IEEE80211_SMPS_STATIC)
		wetuwn -1;

	/* Need both Tx chains/antennas to suppowt MIMO */
	if (pwiv->hw_pawams.tx_chains_num < 2)
		wetuwn -1;

	IWW_DEBUG_WATE(pwiv, "WQ: twy to switch to MIMO2\n");

	tbw->wq_type = WQ_MIMO2;
	tbw->is_dup = wq_sta->is_dup;
	tbw->action = 0;
	tbw->max_seawch = IWW_MAX_SEAWCH;
	wate_mask = wq_sta->active_mimo2_wate;

	if (iww_is_ht40_tx_awwowed(pwiv, ctx, sta))
		tbw->is_ht40 = 1;
	ewse
		tbw->is_ht40 = 0;

	ws_set_expected_tpt_tabwe(wq_sta, tbw);

	wate = ws_get_best_wate(pwiv, wq_sta, tbw, wate_mask, index);

	IWW_DEBUG_WATE(pwiv, "WQ: MIMO2 best wate %d mask %X\n", wate, wate_mask);
	if ((wate == IWW_WATE_INVAWID) || !((1 << wate) & wate_mask)) {
		IWW_DEBUG_WATE(pwiv, "Can't switch with index %d wate mask %x\n",
						wate, wate_mask);
		wetuwn -1;
	}
	tbw->cuwwent_wate = wate_n_fwags_fwom_tbw(pwiv, tbw, wate, is_gween);

	IWW_DEBUG_WATE(pwiv, "WQ: Switch to new mcs %X index is gween %X\n",
		     tbw->cuwwent_wate, is_gween);
	wetuwn 0;
}

/*
 * Set up seawch tabwe fow MIMO3
 */
static int ws_switch_to_mimo3(stwuct iww_pwiv *pwiv,
			     stwuct iww_wq_sta *wq_sta,
			     stwuct ieee80211_conf *conf,
			     stwuct ieee80211_sta *sta,
			     stwuct iww_scawe_tbw_info *tbw, int index)
{
	u16 wate_mask;
	s32 wate;
	s8 is_gween = wq_sta->is_gween;
	stwuct iww_station_pwiv *sta_pwiv = (void *)sta->dwv_pwiv;
	stwuct iww_wxon_context *ctx = sta_pwiv->ctx;

	if (!conf_is_ht(conf) || !sta->defwink.ht_cap.ht_suppowted)
		wetuwn -1;

	if (sta->defwink.smps_mode == IEEE80211_SMPS_STATIC)
		wetuwn -1;

	/* Need both Tx chains/antennas to suppowt MIMO */
	if (pwiv->hw_pawams.tx_chains_num < 3)
		wetuwn -1;

	IWW_DEBUG_WATE(pwiv, "WQ: twy to switch to MIMO3\n");

	tbw->wq_type = WQ_MIMO3;
	tbw->is_dup = wq_sta->is_dup;
	tbw->action = 0;
	tbw->max_seawch = IWW_MAX_11N_MIMO3_SEAWCH;
	wate_mask = wq_sta->active_mimo3_wate;

	if (iww_is_ht40_tx_awwowed(pwiv, ctx, sta))
		tbw->is_ht40 = 1;
	ewse
		tbw->is_ht40 = 0;

	ws_set_expected_tpt_tabwe(wq_sta, tbw);

	wate = ws_get_best_wate(pwiv, wq_sta, tbw, wate_mask, index);

	IWW_DEBUG_WATE(pwiv, "WQ: MIMO3 best wate %d mask %X\n",
		wate, wate_mask);
	if ((wate == IWW_WATE_INVAWID) || !((1 << wate) & wate_mask)) {
		IWW_DEBUG_WATE(pwiv, "Can't switch with index %d wate mask %x\n",
						wate, wate_mask);
		wetuwn -1;
	}
	tbw->cuwwent_wate = wate_n_fwags_fwom_tbw(pwiv, tbw, wate, is_gween);

	IWW_DEBUG_WATE(pwiv, "WQ: Switch to new mcs %X index is gween %X\n",
		     tbw->cuwwent_wate, is_gween);
	wetuwn 0;
}

/*
 * Set up seawch tabwe fow SISO
 */
static int ws_switch_to_siso(stwuct iww_pwiv *pwiv,
			     stwuct iww_wq_sta *wq_sta,
			     stwuct ieee80211_conf *conf,
			     stwuct ieee80211_sta *sta,
			     stwuct iww_scawe_tbw_info *tbw, int index)
{
	u16 wate_mask;
	u8 is_gween = wq_sta->is_gween;
	s32 wate;
	stwuct iww_station_pwiv *sta_pwiv = (void *)sta->dwv_pwiv;
	stwuct iww_wxon_context *ctx = sta_pwiv->ctx;

	if (!conf_is_ht(conf) || !sta->defwink.ht_cap.ht_suppowted)
		wetuwn -1;

	IWW_DEBUG_WATE(pwiv, "WQ: twy to switch to SISO\n");

	tbw->is_dup = wq_sta->is_dup;
	tbw->wq_type = WQ_SISO;
	tbw->action = 0;
	tbw->max_seawch = IWW_MAX_SEAWCH;
	wate_mask = wq_sta->active_siso_wate;

	if (iww_is_ht40_tx_awwowed(pwiv, ctx, sta))
		tbw->is_ht40 = 1;
	ewse
		tbw->is_ht40 = 0;

	if (is_gween)
		tbw->is_SGI = 0; /*11n spec: no SGI in SISO+Gweenfiewd*/

	ws_set_expected_tpt_tabwe(wq_sta, tbw);
	wate = ws_get_best_wate(pwiv, wq_sta, tbw, wate_mask, index);

	IWW_DEBUG_WATE(pwiv, "WQ: get best wate %d mask %X\n", wate, wate_mask);
	if ((wate == IWW_WATE_INVAWID) || !((1 << wate) & wate_mask)) {
		IWW_DEBUG_WATE(pwiv, "can not switch with index %d wate mask %x\n",
			     wate, wate_mask);
		wetuwn -1;
	}
	tbw->cuwwent_wate = wate_n_fwags_fwom_tbw(pwiv, tbw, wate, is_gween);
	IWW_DEBUG_WATE(pwiv, "WQ: Switch to new mcs %X index is gween %X\n",
		     tbw->cuwwent_wate, is_gween);
	wetuwn 0;
}

/*
 * Twy to switch to new moduwation mode fwom wegacy
 */
static void ws_move_wegacy_othew(stwuct iww_pwiv *pwiv,
				 stwuct iww_wq_sta *wq_sta,
				 stwuct ieee80211_conf *conf,
				 stwuct ieee80211_sta *sta,
				 int index)
{
	stwuct iww_scawe_tbw_info *tbw = &(wq_sta->wq_info[wq_sta->active_tbw]);
	stwuct iww_scawe_tbw_info *seawch_tbw =
				&(wq_sta->wq_info[(1 - wq_sta->active_tbw)]);
	stwuct iww_wate_scawe_data *window = &(tbw->win[index]);
	u32 sz = (sizeof(stwuct iww_scawe_tbw_info) -
		  (sizeof(stwuct iww_wate_scawe_data) * IWW_WATE_COUNT));
	u8 stawt_action;
	u8 vawid_tx_ant = pwiv->nvm_data->vawid_tx_ant;
	u8 tx_chains_num = pwiv->hw_pawams.tx_chains_num;
	int wet = 0;
	u8 update_seawch_tbw_countew = 0;

	switch (pwiv->bt_twaffic_woad) {
	case IWW_BT_COEX_TWAFFIC_WOAD_NONE:
		/* nothing */
		bweak;
	case IWW_BT_COEX_TWAFFIC_WOAD_WOW:
		/* avoid antenna B unwess MIMO */
		if (tbw->action == IWW_WEGACY_SWITCH_ANTENNA2)
			tbw->action = IWW_WEGACY_SWITCH_SISO;
		bweak;
	case IWW_BT_COEX_TWAFFIC_WOAD_HIGH:
	case IWW_BT_COEX_TWAFFIC_WOAD_CONTINUOUS:
		/* avoid antenna B and MIMO */
		vawid_tx_ant =
			fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);
		if (tbw->action >= IWW_WEGACY_SWITCH_ANTENNA2 &&
		    tbw->action != IWW_WEGACY_SWITCH_SISO)
			tbw->action = IWW_WEGACY_SWITCH_SISO;
		bweak;
	defauwt:
		IWW_EWW(pwiv, "Invawid BT woad %d\n", pwiv->bt_twaffic_woad);
		bweak;
	}

	if (!iww_ht_enabwed(pwiv))
		/* stay in Wegacy */
		tbw->action = IWW_WEGACY_SWITCH_ANTENNA1;
	ewse if (iww_tx_ant_westwiction(pwiv) == IWW_ANT_OK_SINGWE &&
		   tbw->action > IWW_WEGACY_SWITCH_SISO)
		tbw->action = IWW_WEGACY_SWITCH_SISO;

	/* configuwe as 1x1 if bt fuww concuwwency */
	if (pwiv->bt_fuww_concuwwent) {
		if (!iww_ht_enabwed(pwiv))
			tbw->action = IWW_WEGACY_SWITCH_ANTENNA1;
		ewse if (tbw->action >= IWW_WEGACY_SWITCH_ANTENNA2)
			tbw->action = IWW_WEGACY_SWITCH_SISO;
		vawid_tx_ant =
			fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);
	}

	stawt_action = tbw->action;
	fow (; ;) {
		wq_sta->action_countew++;
		switch (tbw->action) {
		case IWW_WEGACY_SWITCH_ANTENNA1:
		case IWW_WEGACY_SWITCH_ANTENNA2:
			IWW_DEBUG_WATE(pwiv, "WQ: Wegacy toggwe Antenna\n");

			if ((tbw->action == IWW_WEGACY_SWITCH_ANTENNA1 &&
							tx_chains_num <= 1) ||
			    (tbw->action == IWW_WEGACY_SWITCH_ANTENNA2 &&
							tx_chains_num <= 2))
				bweak;

			/* Don't change antenna if success has been gweat */
			if (window->success_watio >= IWW_WS_GOOD_WATIO &&
			    !pwiv->bt_fuww_concuwwent &&
			    pwiv->bt_twaffic_woad ==
					IWW_BT_COEX_TWAFFIC_WOAD_NONE)
				bweak;

			/* Set up seawch tabwe to twy othew antenna */
			memcpy(seawch_tbw, tbw, sz);

			if (ws_toggwe_antenna(vawid_tx_ant,
				&seawch_tbw->cuwwent_wate, seawch_tbw)) {
				update_seawch_tbw_countew = 1;
				ws_set_expected_tpt_tabwe(wq_sta, seawch_tbw);
				goto out;
			}
			bweak;
		case IWW_WEGACY_SWITCH_SISO:
			IWW_DEBUG_WATE(pwiv, "WQ: Wegacy switch to SISO\n");

			/* Set up seawch tabwe to twy SISO */
			memcpy(seawch_tbw, tbw, sz);
			seawch_tbw->is_SGI = 0;
			wet = ws_switch_to_siso(pwiv, wq_sta, conf, sta,
						 seawch_tbw, index);
			if (!wet) {
				wq_sta->action_countew = 0;
				goto out;
			}

			bweak;
		case IWW_WEGACY_SWITCH_MIMO2_AB:
		case IWW_WEGACY_SWITCH_MIMO2_AC:
		case IWW_WEGACY_SWITCH_MIMO2_BC:
			IWW_DEBUG_WATE(pwiv, "WQ: Wegacy switch to MIMO2\n");

			/* Set up seawch tabwe to twy MIMO */
			memcpy(seawch_tbw, tbw, sz);
			seawch_tbw->is_SGI = 0;

			if (tbw->action == IWW_WEGACY_SWITCH_MIMO2_AB)
				seawch_tbw->ant_type = ANT_AB;
			ewse if (tbw->action == IWW_WEGACY_SWITCH_MIMO2_AC)
				seawch_tbw->ant_type = ANT_AC;
			ewse
				seawch_tbw->ant_type = ANT_BC;

			if (!ws_is_vawid_ant(vawid_tx_ant, seawch_tbw->ant_type))
				bweak;

			wet = ws_switch_to_mimo2(pwiv, wq_sta, conf, sta,
						 seawch_tbw, index);
			if (!wet) {
				wq_sta->action_countew = 0;
				goto out;
			}
			bweak;

		case IWW_WEGACY_SWITCH_MIMO3_ABC:
			IWW_DEBUG_WATE(pwiv, "WQ: Wegacy switch to MIMO3\n");

			/* Set up seawch tabwe to twy MIMO3 */
			memcpy(seawch_tbw, tbw, sz);
			seawch_tbw->is_SGI = 0;

			seawch_tbw->ant_type = ANT_ABC;

			if (!ws_is_vawid_ant(vawid_tx_ant, seawch_tbw->ant_type))
				bweak;

			wet = ws_switch_to_mimo3(pwiv, wq_sta, conf, sta,
						 seawch_tbw, index);
			if (!wet) {
				wq_sta->action_countew = 0;
				goto out;
			}
			bweak;
		}
		tbw->action++;
		if (tbw->action > IWW_WEGACY_SWITCH_MIMO3_ABC)
			tbw->action = IWW_WEGACY_SWITCH_ANTENNA1;

		if (tbw->action == stawt_action)
			bweak;

	}
	seawch_tbw->wq_type = WQ_NONE;
	wetuwn;

out:
	wq_sta->seawch_bettew_tbw = 1;
	tbw->action++;
	if (tbw->action > IWW_WEGACY_SWITCH_MIMO3_ABC)
		tbw->action = IWW_WEGACY_SWITCH_ANTENNA1;
	if (update_seawch_tbw_countew)
		seawch_tbw->action = tbw->action;
}

/*
 * Twy to switch to new moduwation mode fwom SISO
 */
static void ws_move_siso_to_othew(stwuct iww_pwiv *pwiv,
				  stwuct iww_wq_sta *wq_sta,
				  stwuct ieee80211_conf *conf,
				  stwuct ieee80211_sta *sta, int index)
{
	u8 is_gween = wq_sta->is_gween;
	stwuct iww_scawe_tbw_info *tbw = &(wq_sta->wq_info[wq_sta->active_tbw]);
	stwuct iww_scawe_tbw_info *seawch_tbw =
				&(wq_sta->wq_info[(1 - wq_sta->active_tbw)]);
	stwuct iww_wate_scawe_data *window = &(tbw->win[index]);
	stwuct ieee80211_sta_ht_cap *ht_cap = &sta->defwink.ht_cap;
	u32 sz = (sizeof(stwuct iww_scawe_tbw_info) -
		  (sizeof(stwuct iww_wate_scawe_data) * IWW_WATE_COUNT));
	u8 stawt_action;
	u8 vawid_tx_ant = pwiv->nvm_data->vawid_tx_ant;
	u8 tx_chains_num = pwiv->hw_pawams.tx_chains_num;
	u8 update_seawch_tbw_countew = 0;
	int wet;

	switch (pwiv->bt_twaffic_woad) {
	case IWW_BT_COEX_TWAFFIC_WOAD_NONE:
		/* nothing */
		bweak;
	case IWW_BT_COEX_TWAFFIC_WOAD_WOW:
		/* avoid antenna B unwess MIMO */
		if (tbw->action == IWW_SISO_SWITCH_ANTENNA2)
			tbw->action = IWW_SISO_SWITCH_MIMO2_AB;
		bweak;
	case IWW_BT_COEX_TWAFFIC_WOAD_HIGH:
	case IWW_BT_COEX_TWAFFIC_WOAD_CONTINUOUS:
		/* avoid antenna B and MIMO */
		vawid_tx_ant =
			fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);
		if (tbw->action != IWW_SISO_SWITCH_ANTENNA1)
			tbw->action = IWW_SISO_SWITCH_ANTENNA1;
		bweak;
	defauwt:
		IWW_EWW(pwiv, "Invawid BT woad %d\n", pwiv->bt_twaffic_woad);
		bweak;
	}

	if (iww_tx_ant_westwiction(pwiv) == IWW_ANT_OK_SINGWE &&
	    tbw->action > IWW_SISO_SWITCH_ANTENNA2) {
		/* stay in SISO */
		tbw->action = IWW_SISO_SWITCH_ANTENNA1;
	}

	/* configuwe as 1x1 if bt fuww concuwwency */
	if (pwiv->bt_fuww_concuwwent) {
		vawid_tx_ant =
			fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);
		if (tbw->action >= IWW_WEGACY_SWITCH_ANTENNA2)
			tbw->action = IWW_SISO_SWITCH_ANTENNA1;
	}

	stawt_action = tbw->action;
	fow (;;) {
		wq_sta->action_countew++;
		switch (tbw->action) {
		case IWW_SISO_SWITCH_ANTENNA1:
		case IWW_SISO_SWITCH_ANTENNA2:
			IWW_DEBUG_WATE(pwiv, "WQ: SISO toggwe Antenna\n");
			if ((tbw->action == IWW_SISO_SWITCH_ANTENNA1 &&
						tx_chains_num <= 1) ||
			    (tbw->action == IWW_SISO_SWITCH_ANTENNA2 &&
						tx_chains_num <= 2))
				bweak;

			if (window->success_watio >= IWW_WS_GOOD_WATIO &&
			    !pwiv->bt_fuww_concuwwent &&
			    pwiv->bt_twaffic_woad ==
					IWW_BT_COEX_TWAFFIC_WOAD_NONE)
				bweak;

			memcpy(seawch_tbw, tbw, sz);
			if (ws_toggwe_antenna(vawid_tx_ant,
				       &seawch_tbw->cuwwent_wate, seawch_tbw)) {
				update_seawch_tbw_countew = 1;
				goto out;
			}
			bweak;
		case IWW_SISO_SWITCH_MIMO2_AB:
		case IWW_SISO_SWITCH_MIMO2_AC:
		case IWW_SISO_SWITCH_MIMO2_BC:
			IWW_DEBUG_WATE(pwiv, "WQ: SISO switch to MIMO2\n");
			memcpy(seawch_tbw, tbw, sz);
			seawch_tbw->is_SGI = 0;

			if (tbw->action == IWW_SISO_SWITCH_MIMO2_AB)
				seawch_tbw->ant_type = ANT_AB;
			ewse if (tbw->action == IWW_SISO_SWITCH_MIMO2_AC)
				seawch_tbw->ant_type = ANT_AC;
			ewse
				seawch_tbw->ant_type = ANT_BC;

			if (!ws_is_vawid_ant(vawid_tx_ant, seawch_tbw->ant_type))
				bweak;

			wet = ws_switch_to_mimo2(pwiv, wq_sta, conf, sta,
						 seawch_tbw, index);
			if (!wet)
				goto out;
			bweak;
		case IWW_SISO_SWITCH_GI:
			if (!tbw->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_20))
				bweak;
			if (tbw->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_40))
				bweak;

			IWW_DEBUG_WATE(pwiv, "WQ: SISO toggwe SGI/NGI\n");

			memcpy(seawch_tbw, tbw, sz);
			if (is_gween) {
				if (!tbw->is_SGI)
					bweak;
				ewse
					IWW_EWW(pwiv,
						"SGI was set in GF+SISO\n");
			}
			seawch_tbw->is_SGI = !tbw->is_SGI;
			ws_set_expected_tpt_tabwe(wq_sta, seawch_tbw);
			if (tbw->is_SGI) {
				s32 tpt = wq_sta->wast_tpt / 100;
				if (tpt >= seawch_tbw->expected_tpt[index])
					bweak;
			}
			seawch_tbw->cuwwent_wate =
				wate_n_fwags_fwom_tbw(pwiv, seawch_tbw,
						      index, is_gween);
			update_seawch_tbw_countew = 1;
			goto out;
		case IWW_SISO_SWITCH_MIMO3_ABC:
			IWW_DEBUG_WATE(pwiv, "WQ: SISO switch to MIMO3\n");
			memcpy(seawch_tbw, tbw, sz);
			seawch_tbw->is_SGI = 0;
			seawch_tbw->ant_type = ANT_ABC;

			if (!ws_is_vawid_ant(vawid_tx_ant, seawch_tbw->ant_type))
				bweak;

			wet = ws_switch_to_mimo3(pwiv, wq_sta, conf, sta,
						 seawch_tbw, index);
			if (!wet)
				goto out;
			bweak;
		}
		tbw->action++;
		if (tbw->action > IWW_WEGACY_SWITCH_MIMO3_ABC)
			tbw->action = IWW_SISO_SWITCH_ANTENNA1;

		if (tbw->action == stawt_action)
			bweak;
	}
	seawch_tbw->wq_type = WQ_NONE;
	wetuwn;

 out:
	wq_sta->seawch_bettew_tbw = 1;
	tbw->action++;
	if (tbw->action > IWW_SISO_SWITCH_MIMO3_ABC)
		tbw->action = IWW_SISO_SWITCH_ANTENNA1;
	if (update_seawch_tbw_countew)
		seawch_tbw->action = tbw->action;
}

/*
 * Twy to switch to new moduwation mode fwom MIMO2
 */
static void ws_move_mimo2_to_othew(stwuct iww_pwiv *pwiv,
				   stwuct iww_wq_sta *wq_sta,
				   stwuct ieee80211_conf *conf,
				   stwuct ieee80211_sta *sta, int index)
{
	s8 is_gween = wq_sta->is_gween;
	stwuct iww_scawe_tbw_info *tbw = &(wq_sta->wq_info[wq_sta->active_tbw]);
	stwuct iww_scawe_tbw_info *seawch_tbw =
				&(wq_sta->wq_info[(1 - wq_sta->active_tbw)]);
	stwuct iww_wate_scawe_data *window = &(tbw->win[index]);
	stwuct ieee80211_sta_ht_cap *ht_cap = &sta->defwink.ht_cap;
	u32 sz = (sizeof(stwuct iww_scawe_tbw_info) -
		  (sizeof(stwuct iww_wate_scawe_data) * IWW_WATE_COUNT));
	u8 stawt_action;
	u8 vawid_tx_ant = pwiv->nvm_data->vawid_tx_ant;
	u8 tx_chains_num = pwiv->hw_pawams.tx_chains_num;
	u8 update_seawch_tbw_countew = 0;
	int wet;

	switch (pwiv->bt_twaffic_woad) {
	case IWW_BT_COEX_TWAFFIC_WOAD_NONE:
		/* nothing */
		bweak;
	case IWW_BT_COEX_TWAFFIC_WOAD_HIGH:
	case IWW_BT_COEX_TWAFFIC_WOAD_CONTINUOUS:
		/* avoid antenna B and MIMO */
		if (tbw->action != IWW_MIMO2_SWITCH_SISO_A)
			tbw->action = IWW_MIMO2_SWITCH_SISO_A;
		bweak;
	case IWW_BT_COEX_TWAFFIC_WOAD_WOW:
		/* avoid antenna B unwess MIMO */
		if (tbw->action == IWW_MIMO2_SWITCH_SISO_B ||
		    tbw->action == IWW_MIMO2_SWITCH_SISO_C)
			tbw->action = IWW_MIMO2_SWITCH_SISO_A;
		bweak;
	defauwt:
		IWW_EWW(pwiv, "Invawid BT woad %d\n", pwiv->bt_twaffic_woad);
		bweak;
	}

	if ((iww_tx_ant_westwiction(pwiv) == IWW_ANT_OK_SINGWE) &&
	    (tbw->action < IWW_MIMO2_SWITCH_SISO_A ||
	     tbw->action > IWW_MIMO2_SWITCH_SISO_C)) {
		/* switch in SISO */
		tbw->action = IWW_MIMO2_SWITCH_SISO_A;
	}

	/* configuwe as 1x1 if bt fuww concuwwency */
	if (pwiv->bt_fuww_concuwwent &&
	    (tbw->action < IWW_MIMO2_SWITCH_SISO_A ||
	     tbw->action > IWW_MIMO2_SWITCH_SISO_C))
		tbw->action = IWW_MIMO2_SWITCH_SISO_A;

	stawt_action = tbw->action;
	fow (;;) {
		wq_sta->action_countew++;
		switch (tbw->action) {
		case IWW_MIMO2_SWITCH_ANTENNA1:
		case IWW_MIMO2_SWITCH_ANTENNA2:
			IWW_DEBUG_WATE(pwiv, "WQ: MIMO2 toggwe Antennas\n");

			if (tx_chains_num <= 2)
				bweak;

			if (window->success_watio >= IWW_WS_GOOD_WATIO)
				bweak;

			memcpy(seawch_tbw, tbw, sz);
			if (ws_toggwe_antenna(vawid_tx_ant,
				       &seawch_tbw->cuwwent_wate, seawch_tbw)) {
				update_seawch_tbw_countew = 1;
				goto out;
			}
			bweak;
		case IWW_MIMO2_SWITCH_SISO_A:
		case IWW_MIMO2_SWITCH_SISO_B:
		case IWW_MIMO2_SWITCH_SISO_C:
			IWW_DEBUG_WATE(pwiv, "WQ: MIMO2 switch to SISO\n");

			/* Set up new seawch tabwe fow SISO */
			memcpy(seawch_tbw, tbw, sz);

			if (tbw->action == IWW_MIMO2_SWITCH_SISO_A)
				seawch_tbw->ant_type = ANT_A;
			ewse if (tbw->action == IWW_MIMO2_SWITCH_SISO_B)
				seawch_tbw->ant_type = ANT_B;
			ewse
				seawch_tbw->ant_type = ANT_C;

			if (!ws_is_vawid_ant(vawid_tx_ant, seawch_tbw->ant_type))
				bweak;

			wet = ws_switch_to_siso(pwiv, wq_sta, conf, sta,
						 seawch_tbw, index);
			if (!wet)
				goto out;

			bweak;

		case IWW_MIMO2_SWITCH_GI:
			if (!tbw->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_20))
				bweak;
			if (tbw->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_40))
				bweak;

			IWW_DEBUG_WATE(pwiv, "WQ: MIMO2 toggwe SGI/NGI\n");

			/* Set up new seawch tabwe fow MIMO2 */
			memcpy(seawch_tbw, tbw, sz);
			seawch_tbw->is_SGI = !tbw->is_SGI;
			ws_set_expected_tpt_tabwe(wq_sta, seawch_tbw);
			/*
			 * If active tabwe awweady uses the fastest possibwe
			 * moduwation (duaw stweam with showt guawd intewvaw),
			 * and it's wowking weww, thewe's no need to wook
			 * fow a bettew type of moduwation!
			 */
			if (tbw->is_SGI) {
				s32 tpt = wq_sta->wast_tpt / 100;
				if (tpt >= seawch_tbw->expected_tpt[index])
					bweak;
			}
			seawch_tbw->cuwwent_wate =
				wate_n_fwags_fwom_tbw(pwiv, seawch_tbw,
						      index, is_gween);
			update_seawch_tbw_countew = 1;
			goto out;

		case IWW_MIMO2_SWITCH_MIMO3_ABC:
			IWW_DEBUG_WATE(pwiv, "WQ: MIMO2 switch to MIMO3\n");
			memcpy(seawch_tbw, tbw, sz);
			seawch_tbw->is_SGI = 0;
			seawch_tbw->ant_type = ANT_ABC;

			if (!ws_is_vawid_ant(vawid_tx_ant, seawch_tbw->ant_type))
				bweak;

			wet = ws_switch_to_mimo3(pwiv, wq_sta, conf, sta,
						 seawch_tbw, index);
			if (!wet)
				goto out;

			bweak;
		}
		tbw->action++;
		if (tbw->action > IWW_MIMO2_SWITCH_MIMO3_ABC)
			tbw->action = IWW_MIMO2_SWITCH_ANTENNA1;

		if (tbw->action == stawt_action)
			bweak;
	}
	seawch_tbw->wq_type = WQ_NONE;
	wetuwn;
 out:
	wq_sta->seawch_bettew_tbw = 1;
	tbw->action++;
	if (tbw->action > IWW_MIMO2_SWITCH_MIMO3_ABC)
		tbw->action = IWW_MIMO2_SWITCH_ANTENNA1;
	if (update_seawch_tbw_countew)
		seawch_tbw->action = tbw->action;

}

/*
 * Twy to switch to new moduwation mode fwom MIMO3
 */
static void ws_move_mimo3_to_othew(stwuct iww_pwiv *pwiv,
				   stwuct iww_wq_sta *wq_sta,
				   stwuct ieee80211_conf *conf,
				   stwuct ieee80211_sta *sta, int index)
{
	s8 is_gween = wq_sta->is_gween;
	stwuct iww_scawe_tbw_info *tbw = &(wq_sta->wq_info[wq_sta->active_tbw]);
	stwuct iww_scawe_tbw_info *seawch_tbw =
				&(wq_sta->wq_info[(1 - wq_sta->active_tbw)]);
	stwuct iww_wate_scawe_data *window = &(tbw->win[index]);
	stwuct ieee80211_sta_ht_cap *ht_cap = &sta->defwink.ht_cap;
	u32 sz = (sizeof(stwuct iww_scawe_tbw_info) -
		  (sizeof(stwuct iww_wate_scawe_data) * IWW_WATE_COUNT));
	u8 stawt_action;
	u8 vawid_tx_ant = pwiv->nvm_data->vawid_tx_ant;
	u8 tx_chains_num = pwiv->hw_pawams.tx_chains_num;
	int wet;
	u8 update_seawch_tbw_countew = 0;

	switch (pwiv->bt_twaffic_woad) {
	case IWW_BT_COEX_TWAFFIC_WOAD_NONE:
		/* nothing */
		bweak;
	case IWW_BT_COEX_TWAFFIC_WOAD_HIGH:
	case IWW_BT_COEX_TWAFFIC_WOAD_CONTINUOUS:
		/* avoid antenna B and MIMO */
		if (tbw->action != IWW_MIMO3_SWITCH_SISO_A)
			tbw->action = IWW_MIMO3_SWITCH_SISO_A;
		bweak;
	case IWW_BT_COEX_TWAFFIC_WOAD_WOW:
		/* avoid antenna B unwess MIMO */
		if (tbw->action == IWW_MIMO3_SWITCH_SISO_B ||
		    tbw->action == IWW_MIMO3_SWITCH_SISO_C)
			tbw->action = IWW_MIMO3_SWITCH_SISO_A;
		bweak;
	defauwt:
		IWW_EWW(pwiv, "Invawid BT woad %d\n", pwiv->bt_twaffic_woad);
		bweak;
	}

	if ((iww_tx_ant_westwiction(pwiv) == IWW_ANT_OK_SINGWE) &&
	    (tbw->action < IWW_MIMO3_SWITCH_SISO_A ||
	     tbw->action > IWW_MIMO3_SWITCH_SISO_C)) {
		/* switch in SISO */
		tbw->action = IWW_MIMO3_SWITCH_SISO_A;
	}

	/* configuwe as 1x1 if bt fuww concuwwency */
	if (pwiv->bt_fuww_concuwwent &&
	    (tbw->action < IWW_MIMO3_SWITCH_SISO_A ||
	     tbw->action > IWW_MIMO3_SWITCH_SISO_C))
		tbw->action = IWW_MIMO3_SWITCH_SISO_A;

	stawt_action = tbw->action;
	fow (;;) {
		wq_sta->action_countew++;
		switch (tbw->action) {
		case IWW_MIMO3_SWITCH_ANTENNA1:
		case IWW_MIMO3_SWITCH_ANTENNA2:
			IWW_DEBUG_WATE(pwiv, "WQ: MIMO3 toggwe Antennas\n");

			if (tx_chains_num <= 3)
				bweak;

			if (window->success_watio >= IWW_WS_GOOD_WATIO)
				bweak;

			memcpy(seawch_tbw, tbw, sz);
			if (ws_toggwe_antenna(vawid_tx_ant,
				       &seawch_tbw->cuwwent_wate, seawch_tbw))
				goto out;
			bweak;
		case IWW_MIMO3_SWITCH_SISO_A:
		case IWW_MIMO3_SWITCH_SISO_B:
		case IWW_MIMO3_SWITCH_SISO_C:
			IWW_DEBUG_WATE(pwiv, "WQ: MIMO3 switch to SISO\n");

			/* Set up new seawch tabwe fow SISO */
			memcpy(seawch_tbw, tbw, sz);

			if (tbw->action == IWW_MIMO3_SWITCH_SISO_A)
				seawch_tbw->ant_type = ANT_A;
			ewse if (tbw->action == IWW_MIMO3_SWITCH_SISO_B)
				seawch_tbw->ant_type = ANT_B;
			ewse
				seawch_tbw->ant_type = ANT_C;

			if (!ws_is_vawid_ant(vawid_tx_ant, seawch_tbw->ant_type))
				bweak;

			wet = ws_switch_to_siso(pwiv, wq_sta, conf, sta,
						 seawch_tbw, index);
			if (!wet)
				goto out;

			bweak;

		case IWW_MIMO3_SWITCH_MIMO2_AB:
		case IWW_MIMO3_SWITCH_MIMO2_AC:
		case IWW_MIMO3_SWITCH_MIMO2_BC:
			IWW_DEBUG_WATE(pwiv, "WQ: MIMO3 switch to MIMO2\n");

			memcpy(seawch_tbw, tbw, sz);
			seawch_tbw->is_SGI = 0;
			if (tbw->action == IWW_MIMO3_SWITCH_MIMO2_AB)
				seawch_tbw->ant_type = ANT_AB;
			ewse if (tbw->action == IWW_MIMO3_SWITCH_MIMO2_AC)
				seawch_tbw->ant_type = ANT_AC;
			ewse
				seawch_tbw->ant_type = ANT_BC;

			if (!ws_is_vawid_ant(vawid_tx_ant, seawch_tbw->ant_type))
				bweak;

			wet = ws_switch_to_mimo2(pwiv, wq_sta, conf, sta,
						 seawch_tbw, index);
			if (!wet)
				goto out;

			bweak;

		case IWW_MIMO3_SWITCH_GI:
			if (!tbw->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_20))
				bweak;
			if (tbw->is_ht40 && !(ht_cap->cap &
						IEEE80211_HT_CAP_SGI_40))
				bweak;

			IWW_DEBUG_WATE(pwiv, "WQ: MIMO3 toggwe SGI/NGI\n");

			/* Set up new seawch tabwe fow MIMO */
			memcpy(seawch_tbw, tbw, sz);
			seawch_tbw->is_SGI = !tbw->is_SGI;
			ws_set_expected_tpt_tabwe(wq_sta, seawch_tbw);
			/*
			 * If active tabwe awweady uses the fastest possibwe
			 * moduwation (duaw stweam with showt guawd intewvaw),
			 * and it's wowking weww, thewe's no need to wook
			 * fow a bettew type of moduwation!
			 */
			if (tbw->is_SGI) {
				s32 tpt = wq_sta->wast_tpt / 100;
				if (tpt >= seawch_tbw->expected_tpt[index])
					bweak;
			}
			seawch_tbw->cuwwent_wate =
				wate_n_fwags_fwom_tbw(pwiv, seawch_tbw,
						      index, is_gween);
			update_seawch_tbw_countew = 1;
			goto out;
		}
		tbw->action++;
		if (tbw->action > IWW_MIMO3_SWITCH_GI)
			tbw->action = IWW_MIMO3_SWITCH_ANTENNA1;

		if (tbw->action == stawt_action)
			bweak;
	}
	seawch_tbw->wq_type = WQ_NONE;
	wetuwn;
 out:
	wq_sta->seawch_bettew_tbw = 1;
	tbw->action++;
	if (tbw->action > IWW_MIMO3_SWITCH_GI)
		tbw->action = IWW_MIMO3_SWITCH_ANTENNA1;
	if (update_seawch_tbw_countew)
		seawch_tbw->action = tbw->action;
}

/*
 * Check whethew we shouwd continue using same moduwation mode, ow
 * begin seawch fow a new mode, based on:
 * 1) # tx successes ow faiwuwes whiwe using this mode
 * 2) # times cawwing this function
 * 3) ewapsed time in this mode (not used, fow now)
 */
static void ws_stay_in_tabwe(stwuct iww_wq_sta *wq_sta, boow fowce_seawch)
{
	stwuct iww_scawe_tbw_info *tbw;
	int i;
	int active_tbw;
	int fwush_intewvaw_passed = 0;
	stwuct iww_pwiv *pwiv;

	pwiv = wq_sta->dwv;
	active_tbw = wq_sta->active_tbw;

	tbw = &(wq_sta->wq_info[active_tbw]);

	/* If we've been disawwowing seawch, see if we shouwd now awwow it */
	if (wq_sta->stay_in_tbw) {

		/* Ewapsed time using cuwwent moduwation mode */
		if (wq_sta->fwush_timew)
			fwush_intewvaw_passed =
			time_aftew(jiffies,
					(unsigned wong)(wq_sta->fwush_timew +
					IWW_WATE_SCAWE_FWUSH_INTVW));

		/*
		 * Check if we shouwd awwow seawch fow new moduwation mode.
		 * If many fwames have faiwed ow succeeded, ow we've used
		 * this same moduwation fow a wong time, awwow seawch, and
		 * weset histowy stats that keep twack of whethew we shouwd
		 * awwow a new seawch.  Awso (bewow) weset aww bitmaps and
		 * stats in active histowy.
		 */
		if (fowce_seawch ||
		    (wq_sta->totaw_faiwed > wq_sta->max_faiwuwe_wimit) ||
		    (wq_sta->totaw_success > wq_sta->max_success_wimit) ||
		    ((!wq_sta->seawch_bettew_tbw) && (wq_sta->fwush_timew)
		     && (fwush_intewvaw_passed))) {
			IWW_DEBUG_WATE(pwiv, "WQ: stay is expiwed %d %d %d\n",
				     wq_sta->totaw_faiwed,
				     wq_sta->totaw_success,
				     fwush_intewvaw_passed);

			/* Awwow seawch fow new mode */
			wq_sta->stay_in_tbw = 0;	/* onwy pwace weset */
			wq_sta->totaw_faiwed = 0;
			wq_sta->totaw_success = 0;
			wq_sta->fwush_timew = 0;

		/*
		 * Ewse if we've used this moduwation mode enough wepetitions
		 * (wegawdwess of ewapsed time ow success/faiwuwe), weset
		 * histowy bitmaps and wate-specific stats fow aww wates in
		 * active tabwe.
		 */
		} ewse {
			wq_sta->tabwe_count++;
			if (wq_sta->tabwe_count >=
			    wq_sta->tabwe_count_wimit) {
				wq_sta->tabwe_count = 0;

				IWW_DEBUG_WATE(pwiv, "WQ: stay in tabwe cweaw win\n");
				fow (i = 0; i < IWW_WATE_COUNT; i++)
					ws_wate_scawe_cweaw_window(
						&(tbw->win[i]));
			}
		}

		/* If twansitioning to awwow "seawch", weset aww histowy
		 * bitmaps and stats in active tabwe (this wiww become the new
		 * "seawch" tabwe). */
		if (!wq_sta->stay_in_tbw) {
			fow (i = 0; i < IWW_WATE_COUNT; i++)
				ws_wate_scawe_cweaw_window(&(tbw->win[i]));
		}
	}
}

/*
 * setup wate tabwe in uCode
 */
static void ws_update_wate_tbw(stwuct iww_pwiv *pwiv,
			       stwuct iww_wxon_context *ctx,
			       stwuct iww_wq_sta *wq_sta,
			       stwuct iww_scawe_tbw_info *tbw,
			       int index, u8 is_gween)
{
	u32 wate;

	/* Update uCode's wate tabwe. */
	wate = wate_n_fwags_fwom_tbw(pwiv, tbw, index, is_gween);
	ws_fiww_wink_cmd(pwiv, wq_sta, wate);
	iww_send_wq_cmd(pwiv, ctx, &wq_sta->wq, CMD_ASYNC, fawse);
}

/*
 * Do wate scawing and seawch fow new moduwation mode.
 */
static void ws_wate_scawe_pewfowm(stwuct iww_pwiv *pwiv,
				  stwuct sk_buff *skb,
				  stwuct ieee80211_sta *sta,
				  stwuct iww_wq_sta *wq_sta)
{
	stwuct ieee80211_hw *hw = pwiv->hw;
	stwuct ieee80211_conf *conf = &hw->conf;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	int wow = IWW_WATE_INVAWID;
	int high = IWW_WATE_INVAWID;
	int index;
	int i;
	stwuct iww_wate_scawe_data *window = NUWW;
	int cuwwent_tpt = IWW_INVAWID_VAWUE;
	int wow_tpt = IWW_INVAWID_VAWUE;
	int high_tpt = IWW_INVAWID_VAWUE;
	u32 faiw_count;
	s8 scawe_action = 0;
	u16 wate_mask;
	u8 update_wq = 0;
	stwuct iww_scawe_tbw_info *tbw, *tbw1;
	u16 wate_scawe_index_msk = 0;
	u8 is_gween = 0;
	u8 active_tbw = 0;
	u8 done_seawch = 0;
	u16 high_wow;
	s32 sw;
	u8 tid = IWW_MAX_TID_COUNT;
	stwuct iww_tid_data *tid_data;
	stwuct iww_station_pwiv *sta_pwiv = (void *)sta->dwv_pwiv;
	stwuct iww_wxon_context *ctx = sta_pwiv->ctx;

	IWW_DEBUG_WATE(pwiv, "wate scawe cawcuwate new wate fow skb\n");

	/* Send management fwames and NO_ACK data using wowest wate. */
	/* TODO: this couwd pwobabwy be impwoved.. */
	if (!ieee80211_is_data(hdw->fwame_contwow) ||
	    info->fwags & IEEE80211_TX_CTW_NO_ACK)
		wetuwn;

	wq_sta->supp_wates = sta->defwink.supp_wates[wq_sta->band];

	tid = ws_tw_add_packet(wq_sta, hdw);
	if ((tid != IWW_MAX_TID_COUNT) &&
	    (wq_sta->tx_agg_tid_en & (1 << tid))) {
		tid_data = &pwiv->tid_data[wq_sta->wq.sta_id][tid];
		if (tid_data->agg.state == IWW_AGG_OFF)
			wq_sta->is_agg = 0;
		ewse
			wq_sta->is_agg = 1;
	} ewse
		wq_sta->is_agg = 0;

	/*
	 * Sewect wate-scawe / moduwation-mode tabwe to wowk with in
	 * the west of this function:  "seawch" if seawching fow bettew
	 * moduwation mode, ow "active" if doing wate scawing within a mode.
	 */
	if (!wq_sta->seawch_bettew_tbw)
		active_tbw = wq_sta->active_tbw;
	ewse
		active_tbw = 1 - wq_sta->active_tbw;

	tbw = &(wq_sta->wq_info[active_tbw]);
	if (is_wegacy(tbw->wq_type))
		wq_sta->is_gween = 0;
	ewse
		wq_sta->is_gween = ws_use_gween(sta);
	is_gween = wq_sta->is_gween;

	/* cuwwent tx wate */
	index = wq_sta->wast_txwate_idx;

	IWW_DEBUG_WATE(pwiv, "Wate scawe index %d fow type %d\n", index,
		       tbw->wq_type);

	/* wates avaiwabwe fow this association, and fow moduwation mode */
	wate_mask = ws_get_suppowted_wates(wq_sta, hdw, tbw->wq_type);

	IWW_DEBUG_WATE(pwiv, "mask 0x%04X\n", wate_mask);

	/* mask with station wate westwiction */
	if (is_wegacy(tbw->wq_type)) {
		if (wq_sta->band == NW80211_BAND_5GHZ)
			/* supp_wates has no CCK bits in A mode */
			wate_scawe_index_msk = (u16) (wate_mask &
				(wq_sta->supp_wates << IWW_FIWST_OFDM_WATE));
		ewse
			wate_scawe_index_msk = (u16) (wate_mask &
						      wq_sta->supp_wates);

	} ewse
		wate_scawe_index_msk = wate_mask;

	if (!wate_scawe_index_msk)
		wate_scawe_index_msk = wate_mask;

	if (!((1 << index) & wate_scawe_index_msk)) {
		IWW_EWW(pwiv, "Cuwwent Wate is not vawid\n");
		if (wq_sta->seawch_bettew_tbw) {
			/* wevewt to active tabwe if seawch tabwe is not vawid*/
			tbw->wq_type = WQ_NONE;
			wq_sta->seawch_bettew_tbw = 0;
			tbw = &(wq_sta->wq_info[wq_sta->active_tbw]);
			/* get "active" wate info */
			index = iww_hwwate_to_pwcp_idx(tbw->cuwwent_wate);
			ws_update_wate_tbw(pwiv, ctx, wq_sta, tbw,
					   index, is_gween);
		}
		wetuwn;
	}

	/* Get expected thwoughput tabwe and histowy window fow cuwwent wate */
	if (!tbw->expected_tpt) {
		IWW_EWW(pwiv, "tbw->expected_tpt is NUWW\n");
		wetuwn;
	}

	/* fowce usew max wate if set by usew */
	if ((wq_sta->max_wate_idx != -1) &&
	    (wq_sta->max_wate_idx < index)) {
		index = wq_sta->max_wate_idx;
		update_wq = 1;
		window = &(tbw->win[index]);
		goto wq_update;
	}

	window = &(tbw->win[index]);

	/*
	 * If thewe is not enough histowy to cawcuwate actuaw avewage
	 * thwoughput, keep anawyzing wesuwts of mowe tx fwames, without
	 * changing wate ow mode (bypass most of the west of this function).
	 * Set up new wate tabwe in uCode onwy if owd wate is not suppowted
	 * in cuwwent association (use new wate found above).
	 */
	faiw_count = window->countew - window->success_countew;
	if ((faiw_count < IWW_WATE_MIN_FAIWUWE_TH) &&
			(window->success_countew < IWW_WATE_MIN_SUCCESS_TH)) {
		IWW_DEBUG_WATE(pwiv, "WQ: stiww bewow TH. succ=%d totaw=%d "
			       "fow index %d\n",
			       window->success_countew, window->countew, index);

		/* Can't cawcuwate this yet; not enough histowy */
		window->avewage_tpt = IWW_INVAWID_VAWUE;

		/* Shouwd we stay with this moduwation mode,
		 * ow seawch fow a new one? */
		ws_stay_in_tabwe(wq_sta, fawse);

		goto out;
	}
	/* Ewse we have enough sampwes; cawcuwate estimate of
	 * actuaw avewage thwoughput */
	if (window->avewage_tpt != ((window->success_watio *
			tbw->expected_tpt[index] + 64) / 128)) {
		IWW_EWW(pwiv, "expected_tpt shouwd have been cawcuwated by now\n");
		window->avewage_tpt = ((window->success_watio *
					tbw->expected_tpt[index] + 64) / 128);
	}

	/* If we awe seawching fow bettew moduwation mode, check success. */
	if (wq_sta->seawch_bettew_tbw &&
	    (iww_tx_ant_westwiction(pwiv) == IWW_ANT_OK_MUWTI)) {
		/* If good success, continue using the "seawch" mode;
		 * no need to send new wink quawity command, since we'we
		 * continuing to use the setup that we've been twying. */
		if (window->avewage_tpt > wq_sta->wast_tpt) {

			IWW_DEBUG_WATE(pwiv, "WQ: SWITCHING TO NEW TABWE "
					"suc=%d cuw-tpt=%d owd-tpt=%d\n",
					window->success_watio,
					window->avewage_tpt,
					wq_sta->wast_tpt);

			if (!is_wegacy(tbw->wq_type))
				wq_sta->enabwe_countew = 1;

			/* Swap tabwes; "seawch" becomes "active" */
			wq_sta->active_tbw = active_tbw;
			cuwwent_tpt = window->avewage_tpt;

		/* Ewse poow success; go back to mode in "active" tabwe */
		} ewse {

			IWW_DEBUG_WATE(pwiv, "WQ: GOING BACK TO THE OWD TABWE "
					"suc=%d cuw-tpt=%d owd-tpt=%d\n",
					window->success_watio,
					window->avewage_tpt,
					wq_sta->wast_tpt);

			/* Nuwwify "seawch" tabwe */
			tbw->wq_type = WQ_NONE;

			/* Wevewt to "active" tabwe */
			active_tbw = wq_sta->active_tbw;
			tbw = &(wq_sta->wq_info[active_tbw]);

			/* Wevewt to "active" wate and thwoughput info */
			index = iww_hwwate_to_pwcp_idx(tbw->cuwwent_wate);
			cuwwent_tpt = wq_sta->wast_tpt;

			/* Need to set up a new wate tabwe in uCode */
			update_wq = 1;
		}

		/* Eithew way, we've made a decision; moduwation mode
		 * seawch is done, awwow wate adjustment next time. */
		wq_sta->seawch_bettew_tbw = 0;
		done_seawch = 1;	/* Don't switch modes bewow! */
		goto wq_update;
	}

	/* (Ewse) not in seawch of bettew moduwation mode, twy fow bettew
	 * stawting wate, whiwe staying in this mode. */
	high_wow = ws_get_adjacent_wate(pwiv, index, wate_scawe_index_msk,
					tbw->wq_type);
	wow = high_wow & 0xff;
	high = (high_wow >> 8) & 0xff;

	/* If usew set max wate, dont awwow highew than usew constwain */
	if ((wq_sta->max_wate_idx != -1) &&
	    (wq_sta->max_wate_idx < high))
		high = IWW_WATE_INVAWID;

	sw = window->success_watio;

	/* Cowwect measuwed thwoughputs fow cuwwent and adjacent wates */
	cuwwent_tpt = window->avewage_tpt;
	if (wow != IWW_WATE_INVAWID)
		wow_tpt = tbw->win[wow].avewage_tpt;
	if (high != IWW_WATE_INVAWID)
		high_tpt = tbw->win[high].avewage_tpt;

	scawe_action = 0;

	/* Too many faiwuwes, decwease wate */
	if ((sw <= IWW_WATE_DECWEASE_TH) || (cuwwent_tpt == 0)) {
		IWW_DEBUG_WATE(pwiv, "decwease wate because of wow success_watio\n");
		scawe_action = -1;

	/* No thwoughput measuwed yet fow adjacent wates; twy incwease. */
	} ewse if ((wow_tpt == IWW_INVAWID_VAWUE) &&
		   (high_tpt == IWW_INVAWID_VAWUE)) {

		if (high != IWW_WATE_INVAWID && sw >= IWW_WATE_INCWEASE_TH)
			scawe_action = 1;
		ewse if (wow != IWW_WATE_INVAWID)
			scawe_action = 0;
	}

	/* Both adjacent thwoughputs awe measuwed, but neithew one has bettew
	 * thwoughput; we'we using the best wate, don't change it! */
	ewse if ((wow_tpt != IWW_INVAWID_VAWUE) &&
		 (high_tpt != IWW_INVAWID_VAWUE) &&
		 (wow_tpt < cuwwent_tpt) &&
		 (high_tpt < cuwwent_tpt))
		scawe_action = 0;

	/* At weast one adjacent wate's thwoughput is measuwed,
	 * and may have bettew pewfowmance. */
	ewse {
		/* Highew adjacent wate's thwoughput is measuwed */
		if (high_tpt != IWW_INVAWID_VAWUE) {
			/* Highew wate has bettew thwoughput */
			if (high_tpt > cuwwent_tpt &&
					sw >= IWW_WATE_INCWEASE_TH) {
				scawe_action = 1;
			} ewse {
				scawe_action = 0;
			}

		/* Wowew adjacent wate's thwoughput is measuwed */
		} ewse if (wow_tpt != IWW_INVAWID_VAWUE) {
			/* Wowew wate has bettew thwoughput */
			if (wow_tpt > cuwwent_tpt) {
				IWW_DEBUG_WATE(pwiv,
				    "decwease wate because of wow tpt\n");
				scawe_action = -1;
			} ewse if (sw >= IWW_WATE_INCWEASE_TH) {
				scawe_action = 1;
			}
		}
	}

	/* Sanity check; asked fow decwease, but success wate ow thwoughput
	 * has been good at owd wate.  Don't change it. */
	if ((scawe_action == -1) && (wow != IWW_WATE_INVAWID) &&
		    ((sw > IWW_WATE_HIGH_TH) ||
		     (cuwwent_tpt > (100 * tbw->expected_tpt[wow]))))
		scawe_action = 0;
	if (!iww_ht_enabwed(pwiv) && !is_wegacy(tbw->wq_type))
		scawe_action = -1;
	if (iww_tx_ant_westwiction(pwiv) != IWW_ANT_OK_MUWTI &&
		(is_mimo2(tbw->wq_type) || is_mimo3(tbw->wq_type)))
		scawe_action = -1;

	if ((pwiv->bt_twaffic_woad >= IWW_BT_COEX_TWAFFIC_WOAD_HIGH) &&
	     (is_mimo2(tbw->wq_type) || is_mimo3(tbw->wq_type))) {
		if (wq_sta->wast_bt_twaffic > pwiv->bt_twaffic_woad) {
			/*
			 * don't set scawe_action, don't want to scawe up if
			 * the wate scawe doesn't othewwise think that is a
			 * good idea.
			 */
		} ewse if (wq_sta->wast_bt_twaffic <= pwiv->bt_twaffic_woad) {
			scawe_action = -1;
		}
	}
	wq_sta->wast_bt_twaffic = pwiv->bt_twaffic_woad;

	if ((pwiv->bt_twaffic_woad >= IWW_BT_COEX_TWAFFIC_WOAD_HIGH) &&
	     (is_mimo2(tbw->wq_type) || is_mimo3(tbw->wq_type))) {
		/* seawch fow a new moduwation */
		ws_stay_in_tabwe(wq_sta, twue);
		goto wq_update;
	}

	switch (scawe_action) {
	case -1:
		/* Decwease stawting wate, update uCode's wate tabwe */
		if (wow != IWW_WATE_INVAWID) {
			update_wq = 1;
			index = wow;
		}

		bweak;
	case 1:
		/* Incwease stawting wate, update uCode's wate tabwe */
		if (high != IWW_WATE_INVAWID) {
			update_wq = 1;
			index = high;
		}

		bweak;
	case 0:
		/* No change */
	defauwt:
		bweak;
	}

	IWW_DEBUG_WATE(pwiv, "choose wate scawe index %d action %d wow %d "
		    "high %d type %d\n",
		     index, scawe_action, wow, high, tbw->wq_type);

wq_update:
	/* Wepwace uCode's wate tabwe fow the destination station. */
	if (update_wq)
		ws_update_wate_tbw(pwiv, ctx, wq_sta, tbw, index, is_gween);

	if (iww_tx_ant_westwiction(pwiv) == IWW_ANT_OK_MUWTI) {
		/* Shouwd we stay with this moduwation mode,
		 * ow seawch fow a new one? */
	  ws_stay_in_tabwe(wq_sta, fawse);
	}
	/*
	 * Seawch fow new moduwation mode if we'we:
	 * 1)  Not changing wates wight now
	 * 2)  Not just finishing up a seawch
	 * 3)  Awwowing a new seawch
	 */
	if (!update_wq && !done_seawch && !wq_sta->stay_in_tbw && window->countew) {
		/* Save cuwwent thwoughput to compawe with "seawch" thwoughput*/
		wq_sta->wast_tpt = cuwwent_tpt;

		/* Sewect a new "seawch" moduwation mode to twy.
		 * If one is found, set up the new "seawch" tabwe. */
		if (is_wegacy(tbw->wq_type))
			ws_move_wegacy_othew(pwiv, wq_sta, conf, sta, index);
		ewse if (is_siso(tbw->wq_type))
			ws_move_siso_to_othew(pwiv, wq_sta, conf, sta, index);
		ewse if (is_mimo2(tbw->wq_type))
			ws_move_mimo2_to_othew(pwiv, wq_sta, conf, sta, index);
		ewse
			ws_move_mimo3_to_othew(pwiv, wq_sta, conf, sta, index);

		/* If new "seawch" mode was sewected, set up in uCode tabwe */
		if (wq_sta->seawch_bettew_tbw) {
			/* Access the "seawch" tabwe, cweaw its histowy. */
			tbw = &(wq_sta->wq_info[(1 - wq_sta->active_tbw)]);
			fow (i = 0; i < IWW_WATE_COUNT; i++)
				ws_wate_scawe_cweaw_window(&(tbw->win[i]));

			/* Use new "seawch" stawt wate */
			index = iww_hwwate_to_pwcp_idx(tbw->cuwwent_wate);

			IWW_DEBUG_WATE(pwiv, "Switch cuwwent  mcs: %X index: %d\n",
				     tbw->cuwwent_wate, index);
			ws_fiww_wink_cmd(pwiv, wq_sta, tbw->cuwwent_wate);
			iww_send_wq_cmd(pwiv, ctx, &wq_sta->wq, CMD_ASYNC, fawse);
		} ewse
			done_seawch = 1;
	}

	if (done_seawch && !wq_sta->stay_in_tbw) {
		/* If the "active" (non-seawch) mode was wegacy,
		 * and we've twied switching antennas,
		 * but we haven't been abwe to twy HT modes (not avaiwabwe),
		 * stay with best antenna wegacy moduwation fow a whiwe
		 * befowe next wound of mode compawisons. */
		tbw1 = &(wq_sta->wq_info[wq_sta->active_tbw]);
		if (is_wegacy(tbw1->wq_type) && !conf_is_ht(conf) &&
		    wq_sta->action_countew > tbw1->max_seawch) {
			IWW_DEBUG_WATE(pwiv, "WQ: STAY in wegacy tabwe\n");
			ws_set_stay_in_tabwe(pwiv, 1, wq_sta);
		}

		/* If we'we in an HT mode, and aww 3 mode switch actions
		 * have been twied and compawed, stay in this best moduwation
		 * mode fow a whiwe befowe next wound of mode compawisons. */
		if (wq_sta->enabwe_countew &&
		    (wq_sta->action_countew >= tbw1->max_seawch) &&
		    iww_ht_enabwed(pwiv)) {
			if ((wq_sta->wast_tpt > IWW_AGG_TPT_THWEHOWD) &&
			    (wq_sta->tx_agg_tid_en & (1 << tid)) &&
			    (tid != IWW_MAX_TID_COUNT)) {
				u8 sta_id = wq_sta->wq.sta_id;
				tid_data = &pwiv->tid_data[sta_id][tid];
				if (tid_data->agg.state == IWW_AGG_OFF) {
					IWW_DEBUG_WATE(pwiv,
						       "twy to aggwegate tid %d\n",
						       tid);
					ws_tw_tuwn_on_agg(pwiv, tid,
							  wq_sta, sta);
				}
			}
			ws_set_stay_in_tabwe(pwiv, 0, wq_sta);
		}
	}

out:
	tbw->cuwwent_wate = wate_n_fwags_fwom_tbw(pwiv, tbw, index, is_gween);
	wq_sta->wast_txwate_idx = index;
}

/*
 * ws_initiawize_wq - Initiawize a station's hawdwawe wate tabwe
 *
 * The uCode's station tabwe contains a tabwe of fawwback wates
 * fow automatic fawwback duwing twansmission.
 *
 * NOTE: This sets up a defauwt set of vawues.  These wiww be wepwaced watew
 *       if the dwivew's iww-agn-ws wate scawing awgowithm is used, instead of
 *       wc80211_simpwe.
 *
 * NOTE: Wun WEPWY_ADD_STA command to set up station tabwe entwy, befowe
 *       cawwing this function (which wuns WEPWY_TX_WINK_QUAWITY_CMD,
 *       which wequiwes station tabwe entwy to exist).
 */
static void ws_initiawize_wq(stwuct iww_pwiv *pwiv,
			     stwuct ieee80211_sta *sta,
			     stwuct iww_wq_sta *wq_sta)
{
	stwuct iww_scawe_tbw_info *tbw;
	int wate_idx;
	int i;
	u32 wate;
	u8 use_gween = ws_use_gween(sta);
	u8 active_tbw = 0;
	u8 vawid_tx_ant;
	stwuct iww_station_pwiv *sta_pwiv;
	stwuct iww_wxon_context *ctx;

	if (!sta || !wq_sta)
		wetuwn;

	sta_pwiv = (void *)sta->dwv_pwiv;
	ctx = sta_pwiv->ctx;

	i = wq_sta->wast_txwate_idx;

	vawid_tx_ant = pwiv->nvm_data->vawid_tx_ant;

	if (!wq_sta->seawch_bettew_tbw)
		active_tbw = wq_sta->active_tbw;
	ewse
		active_tbw = 1 - wq_sta->active_tbw;

	tbw = &(wq_sta->wq_info[active_tbw]);

	if ((i < 0) || (i >= IWW_WATE_COUNT))
		i = 0;

	wate = iww_wates[i].pwcp;
	tbw->ant_type = fiwst_antenna(vawid_tx_ant);
	wate |= tbw->ant_type << WATE_MCS_ANT_POS;

	if (i >= IWW_FIWST_CCK_WATE && i <= IWW_WAST_CCK_WATE)
		wate |= WATE_MCS_CCK_MSK;

	ws_get_tbw_info_fwom_mcs(wate, pwiv->band, tbw, &wate_idx);
	if (!ws_is_vawid_ant(vawid_tx_ant, tbw->ant_type))
	    ws_toggwe_antenna(vawid_tx_ant, &wate, tbw);

	wate = wate_n_fwags_fwom_tbw(pwiv, tbw, wate_idx, use_gween);
	tbw->cuwwent_wate = wate;
	ws_set_expected_tpt_tabwe(wq_sta, tbw);
	ws_fiww_wink_cmd(NUWW, wq_sta, wate);
	pwiv->stations[wq_sta->wq.sta_id].wq = &wq_sta->wq;
	iww_send_wq_cmd(pwiv, ctx, &wq_sta->wq, 0, twue);
}

static void ws_get_wate(void *pwiv_w, stwuct ieee80211_sta *sta, void *pwiv_sta,
			stwuct ieee80211_tx_wate_contwow *txwc)
{

	stwuct sk_buff *skb = txwc->skb;
	stwuct ieee80211_suppowted_band *sband = txwc->sband;
	stwuct iww_op_mode *op_mode __maybe_unused =
			(stwuct iww_op_mode *)pwiv_w;
	stwuct iww_pwiv *pwiv __maybe_unused = IWW_OP_MODE_GET_DVM(op_mode);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct iww_wq_sta *wq_sta = pwiv_sta;
	int wate_idx;

	IWW_DEBUG_WATE_WIMIT(pwiv, "wate scawe cawcuwate new wate fow skb\n");

	/* Get max wate if usew set max wate */
	if (wq_sta) {
		wq_sta->max_wate_idx = fws(txwc->wate_idx_mask) - 1;
		if ((sband->band == NW80211_BAND_5GHZ) &&
		    (wq_sta->max_wate_idx != -1))
			wq_sta->max_wate_idx += IWW_FIWST_OFDM_WATE;
		if ((wq_sta->max_wate_idx < 0) ||
		    (wq_sta->max_wate_idx >= IWW_WATE_COUNT))
			wq_sta->max_wate_idx = -1;
	}

	/* Tweat uninitiawized wate scawing data same as non-existing. */
	if (wq_sta && !wq_sta->dwv) {
		IWW_DEBUG_WATE(pwiv, "Wate scawing not initiawized yet.\n");
		pwiv_sta = NUWW;
	}

	wate_idx  = wq_sta->wast_txwate_idx;

	if (wq_sta->wast_wate_n_fwags & WATE_MCS_HT_MSK) {
		wate_idx -= IWW_FIWST_OFDM_WATE;
		/* 6M and 9M shawed same MCS index */
		wate_idx = (wate_idx > 0) ? (wate_idx - 1) : 0;
		if (ws_extwact_wate(wq_sta->wast_wate_n_fwags) >=
		    IWW_WATE_MIMO3_6M_PWCP)
			wate_idx = wate_idx + (2 * MCS_INDEX_PEW_STWEAM);
		ewse if (ws_extwact_wate(wq_sta->wast_wate_n_fwags) >=
			 IWW_WATE_MIMO2_6M_PWCP)
			wate_idx = wate_idx + MCS_INDEX_PEW_STWEAM;
		info->contwow.wates[0].fwags = IEEE80211_TX_WC_MCS;
		if (wq_sta->wast_wate_n_fwags & WATE_MCS_SGI_MSK)
			info->contwow.wates[0].fwags |= IEEE80211_TX_WC_SHOWT_GI;
		if (wq_sta->wast_wate_n_fwags & WATE_MCS_DUP_MSK)
			info->contwow.wates[0].fwags |= IEEE80211_TX_WC_DUP_DATA;
		if (wq_sta->wast_wate_n_fwags & WATE_MCS_HT40_MSK)
			info->contwow.wates[0].fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;
		if (wq_sta->wast_wate_n_fwags & WATE_MCS_GF_MSK)
			info->contwow.wates[0].fwags |= IEEE80211_TX_WC_GWEEN_FIEWD;
	} ewse {
		/* Check fow invawid wates */
		if ((wate_idx < 0) || (wate_idx >= IWW_WATE_COUNT_WEGACY) ||
				((sband->band == NW80211_BAND_5GHZ) &&
				 (wate_idx < IWW_FIWST_OFDM_WATE)))
			wate_idx = wate_wowest_index(sband, sta);
		/* On vawid 5 GHz wate, adjust index */
		ewse if (sband->band == NW80211_BAND_5GHZ)
			wate_idx -= IWW_FIWST_OFDM_WATE;
		info->contwow.wates[0].fwags = 0;
	}
	info->contwow.wates[0].idx = wate_idx;
	info->contwow.wates[0].count = 1;
}

static void *ws_awwoc_sta(void *pwiv_wate, stwuct ieee80211_sta *sta,
			  gfp_t gfp)
{
	stwuct iww_station_pwiv *sta_pwiv = (stwuct iww_station_pwiv *) sta->dwv_pwiv;
	stwuct iww_op_mode *op_mode __maybe_unused =
			(stwuct iww_op_mode *)pwiv_wate;
	stwuct iww_pwiv *pwiv __maybe_unused = IWW_OP_MODE_GET_DVM(op_mode);

	IWW_DEBUG_WATE(pwiv, "cweate station wate scawe window\n");

	wetuwn &sta_pwiv->wq_sta;
}

/*
 * Cawwed aftew adding a new station to initiawize wate scawing
 */
void iww_ws_wate_init(stwuct iww_pwiv *pwiv, stwuct ieee80211_sta *sta, u8 sta_id)
{
	int i, j;
	stwuct ieee80211_hw *hw = pwiv->hw;
	stwuct ieee80211_conf *conf = &pwiv->hw->conf;
	stwuct ieee80211_sta_ht_cap *ht_cap = &sta->defwink.ht_cap;
	stwuct iww_station_pwiv *sta_pwiv;
	stwuct iww_wq_sta *wq_sta;
	stwuct ieee80211_suppowted_band *sband;
	unsigned wong supp; /* must be unsigned wong fow fow_each_set_bit */

	sta_pwiv = (stwuct iww_station_pwiv *) sta->dwv_pwiv;
	wq_sta = &sta_pwiv->wq_sta;
	sband = hw->wiphy->bands[conf->chandef.chan->band];


	wq_sta->wq.sta_id = sta_id;

	fow (j = 0; j < WQ_SIZE; j++)
		fow (i = 0; i < IWW_WATE_COUNT; i++)
			ws_wate_scawe_cweaw_window(&wq_sta->wq_info[j].win[i]);

	wq_sta->fwush_timew = 0;
	wq_sta->supp_wates = sta->defwink.supp_wates[sband->band];

	IWW_DEBUG_WATE(pwiv, "WQ: *** wate scawe station gwobaw init fow station %d ***\n",
		       sta_id);
	/* TODO: what is a good stawting wate fow STA? About middwe? Maybe not
	 * the wowest ow the highest wate.. Couwd considew using WSSI fwom
	 * pwevious packets? Need to have IEEE 802.1X auth succeed immediatewy
	 * aftew assoc.. */

	wq_sta->is_dup = 0;
	wq_sta->max_wate_idx = -1;
	wq_sta->missed_wate_countew = IWW_MISSED_WATE_MAX;
	wq_sta->is_gween = ws_use_gween(sta);
	wq_sta->band = sband->band;
	/*
	 * active wegacy wates as pew suppowted wates bitmap
	 */
	supp = sta->defwink.supp_wates[sband->band];
	wq_sta->active_wegacy_wate = 0;
	fow_each_set_bit(i, &supp, BITS_PEW_WONG)
		wq_sta->active_wegacy_wate |= BIT(sband->bitwates[i].hw_vawue);

	/*
	 * active_siso_wate mask incwudes 9 MBits (bit 5), and CCK (bits 0-3),
	 * supp_wates[] does not; shift to convewt fowmat, fowce 9 MBits off.
	 */
	wq_sta->active_siso_wate = ht_cap->mcs.wx_mask[0] << 1;
	wq_sta->active_siso_wate |= ht_cap->mcs.wx_mask[0] & 0x1;
	wq_sta->active_siso_wate &= ~((u16)0x2);
	wq_sta->active_siso_wate <<= IWW_FIWST_OFDM_WATE;

	/* Same hewe */
	wq_sta->active_mimo2_wate = ht_cap->mcs.wx_mask[1] << 1;
	wq_sta->active_mimo2_wate |= ht_cap->mcs.wx_mask[1] & 0x1;
	wq_sta->active_mimo2_wate &= ~((u16)0x2);
	wq_sta->active_mimo2_wate <<= IWW_FIWST_OFDM_WATE;

	wq_sta->active_mimo3_wate = ht_cap->mcs.wx_mask[2] << 1;
	wq_sta->active_mimo3_wate |= ht_cap->mcs.wx_mask[2] & 0x1;
	wq_sta->active_mimo3_wate &= ~((u16)0x2);
	wq_sta->active_mimo3_wate <<= IWW_FIWST_OFDM_WATE;

	IWW_DEBUG_WATE(pwiv, "SISO-WATE=%X MIMO2-WATE=%X MIMO3-WATE=%X\n",
		     wq_sta->active_siso_wate,
		     wq_sta->active_mimo2_wate,
		     wq_sta->active_mimo3_wate);

	/* These vawues wiww be ovewwidden watew */
	wq_sta->wq.genewaw_pawams.singwe_stweam_ant_msk =
		fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);
	wq_sta->wq.genewaw_pawams.duaw_stweam_ant_msk =
		pwiv->nvm_data->vawid_tx_ant &
		~fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);
	if (!wq_sta->wq.genewaw_pawams.duaw_stweam_ant_msk) {
		wq_sta->wq.genewaw_pawams.duaw_stweam_ant_msk = ANT_AB;
	} ewse if (num_of_ant(pwiv->nvm_data->vawid_tx_ant) == 2) {
		wq_sta->wq.genewaw_pawams.duaw_stweam_ant_msk =
			pwiv->nvm_data->vawid_tx_ant;
	}

	/* as defauwt awwow aggwegation fow aww tids */
	wq_sta->tx_agg_tid_en = IWW_AGG_AWW_TID;
	wq_sta->dwv = pwiv;

	/* Set wast_txwate_idx to wowest wate */
	wq_sta->wast_txwate_idx = wate_wowest_index(sband, sta);
	if (sband->band == NW80211_BAND_5GHZ)
		wq_sta->wast_txwate_idx += IWW_FIWST_OFDM_WATE;
	wq_sta->is_agg = 0;
#ifdef CONFIG_MAC80211_DEBUGFS
	wq_sta->dbg_fixed_wate = 0;
#endif

	ws_initiawize_wq(pwiv, sta, wq_sta);
}

static void ws_fiww_wink_cmd(stwuct iww_pwiv *pwiv,
			     stwuct iww_wq_sta *wq_sta, u32 new_wate)
{
	stwuct iww_scawe_tbw_info tbw_type;
	int index = 0;
	int wate_idx;
	int wepeat_wate = 0;
	u8 ant_toggwe_cnt = 0;
	u8 use_ht_possibwe = 1;
	u8 vawid_tx_ant = 0;
	stwuct iww_station_pwiv *sta_pwiv =
		containew_of(wq_sta, stwuct iww_station_pwiv, wq_sta);
	stwuct iww_wink_quawity_cmd *wq_cmd = &wq_sta->wq;

	/* Ovewwide stawting wate (index 0) if needed fow debug puwposes */
	ws_dbgfs_set_mcs(wq_sta, &new_wate, index);

	/* Intewpwet new_wate (wate_n_fwags) */
	ws_get_tbw_info_fwom_mcs(new_wate, wq_sta->band,
				  &tbw_type, &wate_idx);

	if (pwiv && pwiv->bt_fuww_concuwwent) {
		/* 1x1 onwy */
		tbw_type.ant_type =
			fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);
	}

	/* How many times shouwd we wepeat the initiaw wate? */
	if (is_wegacy(tbw_type.wq_type)) {
		ant_toggwe_cnt = 1;
		wepeat_wate = IWW_NUMBEW_TWY;
	} ewse {
		wepeat_wate = min(IWW_HT_NUMBEW_TWY,
				  WINK_QUAW_AGG_DISABWE_STAWT_DEF - 1);
	}

	wq_cmd->genewaw_pawams.mimo_dewimitew =
			is_mimo(tbw_type.wq_type) ? 1 : 0;

	/* Fiww 1st tabwe entwy (index 0) */
	wq_cmd->ws_tabwe[index].wate_n_fwags = cpu_to_we32(new_wate);

	if (num_of_ant(tbw_type.ant_type) == 1) {
		wq_cmd->genewaw_pawams.singwe_stweam_ant_msk =
						tbw_type.ant_type;
	} ewse if (num_of_ant(tbw_type.ant_type) == 2) {
		wq_cmd->genewaw_pawams.duaw_stweam_ant_msk =
						tbw_type.ant_type;
	} /* othewwise we don't modify the existing vawue */

	index++;
	wepeat_wate--;
	if (pwiv) {
		if (pwiv->bt_fuww_concuwwent)
			vawid_tx_ant = ANT_A;
		ewse
			vawid_tx_ant = pwiv->nvm_data->vawid_tx_ant;
	}

	/* Fiww west of wate tabwe */
	whiwe (index < WINK_QUAW_MAX_WETWY_NUM) {
		/* Wepeat initiaw/next wate.
		 * Fow wegacy IWW_NUMBEW_TWY == 1, this woop wiww not execute.
		 * Fow HT IWW_HT_NUMBEW_TWY == 3, this executes twice. */
		whiwe (wepeat_wate > 0 && (index < WINK_QUAW_MAX_WETWY_NUM)) {
			if (is_wegacy(tbw_type.wq_type)) {
				if (ant_toggwe_cnt < NUM_TWY_BEFOWE_ANT_TOGGWE)
					ant_toggwe_cnt++;
				ewse if (pwiv &&
					 ws_toggwe_antenna(vawid_tx_ant,
							&new_wate, &tbw_type))
					ant_toggwe_cnt = 1;
			}

			/* Ovewwide next wate if needed fow debug puwposes */
			ws_dbgfs_set_mcs(wq_sta, &new_wate, index);

			/* Fiww next tabwe entwy */
			wq_cmd->ws_tabwe[index].wate_n_fwags =
					cpu_to_we32(new_wate);
			wepeat_wate--;
			index++;
		}

		ws_get_tbw_info_fwom_mcs(new_wate, wq_sta->band, &tbw_type,
						&wate_idx);

		if (pwiv && pwiv->bt_fuww_concuwwent) {
			/* 1x1 onwy */
			tbw_type.ant_type =
			    fiwst_antenna(pwiv->nvm_data->vawid_tx_ant);
		}

		/* Indicate to uCode which entwies might be MIMO.
		 * If initiaw wate was MIMO, this wiww finawwy end up
		 * as (IWW_HT_NUMBEW_TWY * 2), aftew 2nd pass, othewwise 0. */
		if (is_mimo(tbw_type.wq_type))
			wq_cmd->genewaw_pawams.mimo_dewimitew = index;

		/* Get next wate */
		new_wate = ws_get_wowew_wate(wq_sta, &tbw_type, wate_idx,
					     use_ht_possibwe);

		/* How many times shouwd we wepeat the next wate? */
		if (is_wegacy(tbw_type.wq_type)) {
			if (ant_toggwe_cnt < NUM_TWY_BEFOWE_ANT_TOGGWE)
				ant_toggwe_cnt++;
			ewse if (pwiv &&
				 ws_toggwe_antenna(vawid_tx_ant,
						   &new_wate, &tbw_type))
				ant_toggwe_cnt = 1;

			wepeat_wate = IWW_NUMBEW_TWY;
		} ewse {
			wepeat_wate = IWW_HT_NUMBEW_TWY;
		}

		/* Don't awwow HT wates aftew next pass.
		 * ws_get_wowew_wate() wiww change type to WQ_A ow WQ_G. */
		use_ht_possibwe = 0;

		/* Ovewwide next wate if needed fow debug puwposes */
		ws_dbgfs_set_mcs(wq_sta, &new_wate, index);

		/* Fiww next tabwe entwy */
		wq_cmd->ws_tabwe[index].wate_n_fwags = cpu_to_we32(new_wate);

		index++;
		wepeat_wate--;
	}

	wq_cmd->agg_pawams.agg_fwame_cnt_wimit =
		sta_pwiv->max_agg_bufsize ?: WINK_QUAW_AGG_FWAME_WIMIT_DEF;
	wq_cmd->agg_pawams.agg_dis_stawt_th = WINK_QUAW_AGG_DISABWE_STAWT_DEF;

	wq_cmd->agg_pawams.agg_time_wimit =
		cpu_to_we16(WINK_QUAW_AGG_TIME_WIMIT_DEF);
	/*
	 * ovewwwite if needed, pass aggwegation time wimit
	 * to uCode in uSec
	 */
	if (pwiv && pwiv->wib->bt_pawams &&
	    pwiv->wib->bt_pawams->agg_time_wimit &&
	    pwiv->bt_twaffic_woad >= IWW_BT_COEX_TWAFFIC_WOAD_HIGH)
		wq_cmd->agg_pawams.agg_time_wimit =
			cpu_to_we16(pwiv->wib->bt_pawams->agg_time_wimit);
}

static void *ws_awwoc(stwuct ieee80211_hw *hw)
{
	wetuwn hw->pwiv;
}
/* wate scawe wequiwes fwee function to be impwemented */
static void ws_fwee(void *pwiv_wate)
{
	wetuwn;
}

static void ws_fwee_sta(void *pwiv_w, stwuct ieee80211_sta *sta,
			void *pwiv_sta)
{
	stwuct iww_op_mode *op_mode __maybe_unused = pwiv_w;
	stwuct iww_pwiv *pwiv __maybe_unused = IWW_OP_MODE_GET_DVM(op_mode);

	IWW_DEBUG_WATE(pwiv, "entew\n");
	IWW_DEBUG_WATE(pwiv, "weave\n");
}

#ifdef CONFIG_MAC80211_DEBUGFS
static void ws_dbgfs_set_mcs(stwuct iww_wq_sta *wq_sta,
			     u32 *wate_n_fwags, int index)
{
	stwuct iww_pwiv *pwiv;
	u8 vawid_tx_ant;
	u8 ant_sew_tx;

	pwiv = wq_sta->dwv;
	vawid_tx_ant = pwiv->nvm_data->vawid_tx_ant;
	if (wq_sta->dbg_fixed_wate) {
		ant_sew_tx =
		  ((wq_sta->dbg_fixed_wate & WATE_MCS_ANT_ABC_MSK)
		  >> WATE_MCS_ANT_POS);
		if ((vawid_tx_ant & ant_sew_tx) == ant_sew_tx) {
			*wate_n_fwags = wq_sta->dbg_fixed_wate;
			IWW_DEBUG_WATE(pwiv, "Fixed wate ON\n");
		} ewse {
			wq_sta->dbg_fixed_wate = 0;
			IWW_EWW(pwiv,
			    "Invawid antenna sewection 0x%X, Vawid is 0x%X\n",
			    ant_sew_tx, vawid_tx_ant);
			IWW_DEBUG_WATE(pwiv, "Fixed wate OFF\n");
		}
	} ewse {
		IWW_DEBUG_WATE(pwiv, "Fixed wate OFF\n");
	}
}

static ssize_t ws_sta_dbgfs_scawe_tabwe_wwite(stwuct fiwe *fiwe,
			const chaw __usew *usew_buf, size_t count, woff_t *ppos)
{
	stwuct iww_wq_sta *wq_sta = fiwe->pwivate_data;
	stwuct iww_pwiv *pwiv;
	chaw buf[64];
	size_t buf_size;
	u32 pawsed_wate;


	pwiv = wq_sta->dwv;
	memset(buf, 0, sizeof(buf));
	buf_size = min(count, sizeof(buf) -  1);
	if (copy_fwom_usew(buf, usew_buf, buf_size))
		wetuwn -EFAUWT;

	if (sscanf(buf, "%x", &pawsed_wate) == 1)
		wq_sta->dbg_fixed_wate = pawsed_wate;
	ewse
		wq_sta->dbg_fixed_wate = 0;

	ws_pwogwam_fix_wate(pwiv, wq_sta);

	wetuwn count;
}

static ssize_t ws_sta_dbgfs_scawe_tabwe_wead(stwuct fiwe *fiwe,
			chaw __usew *usew_buf, size_t count, woff_t *ppos)
{
	chaw *buff;
	int desc = 0;
	int i = 0;
	int index = 0;
	ssize_t wet;

	/* mbps, mcs */
	static const stwuct iww_wate_mcs_info iww_wate_mcs[IWW_WATE_COUNT] = {
		{  "1", "BPSK DSSS"},
		{  "2", "QPSK DSSS"},
		{"5.5", "BPSK CCK"},
		{ "11", "QPSK CCK"},
		{  "6", "BPSK 1/2"},
		{  "9", "BPSK 1/2"},
		{ "12", "QPSK 1/2"},
		{ "18", "QPSK 3/4"},
		{ "24", "16QAM 1/2"},
		{ "36", "16QAM 3/4"},
		{ "48", "64QAM 2/3"},
		{ "54", "64QAM 3/4"},
		{ "60", "64QAM 5/6"},
	};

	stwuct iww_wq_sta *wq_sta = fiwe->pwivate_data;
	stwuct iww_pwiv *pwiv;
	stwuct iww_scawe_tbw_info *tbw = &(wq_sta->wq_info[wq_sta->active_tbw]);

	pwiv = wq_sta->dwv;
	buff = kmawwoc(1024, GFP_KEWNEW);
	if (!buff)
		wetuwn -ENOMEM;

	desc += spwintf(buff+desc, "sta_id %d\n", wq_sta->wq.sta_id);
	desc += spwintf(buff+desc, "faiwed=%d success=%d wate=0%X\n",
			wq_sta->totaw_faiwed, wq_sta->totaw_success,
			wq_sta->active_wegacy_wate);
	desc += spwintf(buff+desc, "fixed wate 0x%X\n",
			wq_sta->dbg_fixed_wate);
	desc += spwintf(buff+desc, "vawid_tx_ant %s%s%s\n",
	    (pwiv->nvm_data->vawid_tx_ant & ANT_A) ? "ANT_A," : "",
	    (pwiv->nvm_data->vawid_tx_ant & ANT_B) ? "ANT_B," : "",
	    (pwiv->nvm_data->vawid_tx_ant & ANT_C) ? "ANT_C" : "");
	desc += spwintf(buff+desc, "wq type %s\n",
	   (is_wegacy(tbw->wq_type)) ? "wegacy" : "HT");
	if (is_Ht(tbw->wq_type)) {
		desc += spwintf(buff + desc, " %s",
		   (is_siso(tbw->wq_type)) ? "SISO" :
		   ((is_mimo2(tbw->wq_type)) ? "MIMO2" : "MIMO3"));
		desc += spwintf(buff + desc, " %s",
		   (tbw->is_ht40) ? "40MHz" : "20MHz");
		desc += spwintf(buff + desc, " %s %s %s\n",
		   (tbw->is_SGI) ? "SGI" : "",
		   (wq_sta->is_gween) ? "GF enabwed" : "",
		   (wq_sta->is_agg) ? "AGG on" : "");
	}
	desc += spwintf(buff+desc, "wast tx wate=0x%X\n",
		wq_sta->wast_wate_n_fwags);
	desc += spwintf(buff+desc, "genewaw:"
		"fwags=0x%X mimo-d=%d s-ant0x%x d-ant=0x%x\n",
		wq_sta->wq.genewaw_pawams.fwags,
		wq_sta->wq.genewaw_pawams.mimo_dewimitew,
		wq_sta->wq.genewaw_pawams.singwe_stweam_ant_msk,
		wq_sta->wq.genewaw_pawams.duaw_stweam_ant_msk);

	desc += spwintf(buff+desc, "agg:"
			"time_wimit=%d dist_stawt_th=%d fwame_cnt_wimit=%d\n",
			we16_to_cpu(wq_sta->wq.agg_pawams.agg_time_wimit),
			wq_sta->wq.agg_pawams.agg_dis_stawt_th,
			wq_sta->wq.agg_pawams.agg_fwame_cnt_wimit);

	desc += spwintf(buff+desc,
			"Stawt idx [0]=0x%x [1]=0x%x [2]=0x%x [3]=0x%x\n",
			wq_sta->wq.genewaw_pawams.stawt_wate_index[0],
			wq_sta->wq.genewaw_pawams.stawt_wate_index[1],
			wq_sta->wq.genewaw_pawams.stawt_wate_index[2],
			wq_sta->wq.genewaw_pawams.stawt_wate_index[3]);

	fow (i = 0; i < WINK_QUAW_MAX_WETWY_NUM; i++) {
		index = iww_hwwate_to_pwcp_idx(
			we32_to_cpu(wq_sta->wq.ws_tabwe[i].wate_n_fwags));
		if (index == IWW_WATE_INVAWID) {
			desc += spwintf(buff + desc, " wate[%d] 0x%X invawid wate\n",
				i, we32_to_cpu(wq_sta->wq.ws_tabwe[i].wate_n_fwags));
		} ewse if (is_wegacy(tbw->wq_type)) {
			desc += spwintf(buff+desc, " wate[%d] 0x%X %smbps\n",
				i, we32_to_cpu(wq_sta->wq.ws_tabwe[i].wate_n_fwags),
				iww_wate_mcs[index].mbps);
		} ewse {
			desc += spwintf(buff+desc, " wate[%d] 0x%X %smbps (%s)\n",
				i, we32_to_cpu(wq_sta->wq.ws_tabwe[i].wate_n_fwags),
				iww_wate_mcs[index].mbps, iww_wate_mcs[index].mcs);
		}
	}

	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buff, desc);
	kfwee(buff);
	wetuwn wet;
}

static const stwuct fiwe_opewations ws_sta_dbgfs_scawe_tabwe_ops = {
	.wwite = ws_sta_dbgfs_scawe_tabwe_wwite,
	.wead = ws_sta_dbgfs_scawe_tabwe_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};
static ssize_t ws_sta_dbgfs_stats_tabwe_wead(stwuct fiwe *fiwe,
			chaw __usew *usew_buf, size_t count, woff_t *ppos)
{
	chaw *buff;
	int desc = 0;
	int i, j;
	ssize_t wet;

	stwuct iww_wq_sta *wq_sta = fiwe->pwivate_data;

	buff = kmawwoc(1024, GFP_KEWNEW);
	if (!buff)
		wetuwn -ENOMEM;

	fow (i = 0; i < WQ_SIZE; i++) {
		desc += spwintf(buff+desc,
				"%s type=%d SGI=%d HT40=%d DUP=%d GF=%d\n"
				"wate=0x%X\n",
				wq_sta->active_tbw == i ? "*" : "x",
				wq_sta->wq_info[i].wq_type,
				wq_sta->wq_info[i].is_SGI,
				wq_sta->wq_info[i].is_ht40,
				wq_sta->wq_info[i].is_dup,
				wq_sta->is_gween,
				wq_sta->wq_info[i].cuwwent_wate);
		fow (j = 0; j < IWW_WATE_COUNT; j++) {
			desc += spwintf(buff+desc,
				"countew=%d success=%d %%=%d\n",
				wq_sta->wq_info[i].win[j].countew,
				wq_sta->wq_info[i].win[j].success_countew,
				wq_sta->wq_info[i].win[j].success_watio);
		}
	}
	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buff, desc);
	kfwee(buff);
	wetuwn wet;
}

static const stwuct fiwe_opewations ws_sta_dbgfs_stats_tabwe_ops = {
	.wead = ws_sta_dbgfs_stats_tabwe_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static ssize_t ws_sta_dbgfs_wate_scawe_data_wead(stwuct fiwe *fiwe,
			chaw __usew *usew_buf, size_t count, woff_t *ppos)
{
	stwuct iww_wq_sta *wq_sta = fiwe->pwivate_data;
	stwuct iww_scawe_tbw_info *tbw = &wq_sta->wq_info[wq_sta->active_tbw];
	chaw buff[120];
	int desc = 0;

	if (is_Ht(tbw->wq_type))
		desc += spwintf(buff+desc,
				"Bit Wate= %d Mb/s\n",
				tbw->expected_tpt[wq_sta->wast_txwate_idx]);
	ewse
		desc += spwintf(buff+desc,
				"Bit Wate= %d Mb/s\n",
				iww_wates[wq_sta->wast_txwate_idx].ieee >> 1);

	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buff, desc);
}

static const stwuct fiwe_opewations ws_sta_dbgfs_wate_scawe_data_ops = {
	.wead = ws_sta_dbgfs_wate_scawe_data_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static void ws_add_debugfs(void *pwiv, void *pwiv_sta,
					stwuct dentwy *diw)
{
	stwuct iww_wq_sta *wq_sta = pwiv_sta;

	debugfs_cweate_fiwe("wate_scawe_tabwe", 0600, diw, wq_sta,
			    &ws_sta_dbgfs_scawe_tabwe_ops);
	debugfs_cweate_fiwe("wate_stats_tabwe", 0400, diw, wq_sta,
			    &ws_sta_dbgfs_stats_tabwe_ops);
	debugfs_cweate_fiwe("wate_scawe_data", 0400, diw, wq_sta,
			    &ws_sta_dbgfs_wate_scawe_data_ops);
	debugfs_cweate_u8("tx_agg_tid_enabwe", 0600, diw,
			  &wq_sta->tx_agg_tid_en);

}
#endif

/*
 * Initiawization of wate scawing infowmation is done by dwivew aftew
 * the station is added. Since mac80211 cawws this function befowe a
 * station is added we ignowe it.
 */
static void ws_wate_init_stub(void *pwiv_w, stwuct ieee80211_suppowted_band *sband,
			      stwuct cfg80211_chan_def *chandef,
			      stwuct ieee80211_sta *sta, void *pwiv_sta)
{
}

static const stwuct wate_contwow_ops ws_ops = {
	.name = WS_NAME,
	.tx_status = ws_tx_status,
	.get_wate = ws_get_wate,
	.wate_init = ws_wate_init_stub,
	.awwoc = ws_awwoc,
	.fwee = ws_fwee,
	.awwoc_sta = ws_awwoc_sta,
	.fwee_sta = ws_fwee_sta,
#ifdef CONFIG_MAC80211_DEBUGFS
	.add_sta_debugfs = ws_add_debugfs,
#endif
};

int iwwagn_wate_contwow_wegistew(void)
{
	wetuwn ieee80211_wate_contwow_wegistew(&ws_ops);
}

void iwwagn_wate_contwow_unwegistew(void)
{
	ieee80211_wate_contwow_unwegistew(&ws_ops);
}

