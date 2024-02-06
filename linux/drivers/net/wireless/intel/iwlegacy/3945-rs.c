// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/******************************************************************************
 *
 * Copywight(c) 2005 - 2011 Intew Cowpowation. Aww wights wesewved.
 *
 * Contact Infowmation:
 *  Intew Winux Wiwewess <iww@winux.intew.com>
 * Intew Cowpowation, 5200 N.E. Ewam Young Pawkway, Hiwwsbowo, OW 97124-6497
 *
 *****************************************************************************/

#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <net/mac80211.h>

#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/deway.h>

#incwude <winux/wowkqueue.h>

#incwude "commands.h"
#incwude "3945.h"

#define WS_NAME "iww-3945-ws"

static s32 iw3945_expected_tpt_g[WATE_COUNT_3945] = {
	7, 13, 35, 58, 0, 0, 76, 104, 130, 168, 191, 202
};

static s32 iw3945_expected_tpt_g_pwot[WATE_COUNT_3945] = {
	7, 13, 35, 58, 0, 0, 0, 80, 93, 113, 123, 125
};

static s32 iw3945_expected_tpt_a[WATE_COUNT_3945] = {
	0, 0, 0, 0, 40, 57, 72, 98, 121, 154, 177, 186
};

static s32 iw3945_expected_tpt_b[WATE_COUNT_3945] = {
	7, 13, 35, 58, 0, 0, 0, 0, 0, 0, 0, 0
};

stwuct iw3945_tpt_entwy {
	s8 min_wssi;
	u8 idx;
};

static stwuct iw3945_tpt_entwy iw3945_tpt_tabwe_a[] = {
	{-60, WATE_54M_IDX},
	{-64, WATE_48M_IDX},
	{-72, WATE_36M_IDX},
	{-80, WATE_24M_IDX},
	{-84, WATE_18M_IDX},
	{-85, WATE_12M_IDX},
	{-87, WATE_9M_IDX},
	{-89, WATE_6M_IDX}
};

static stwuct iw3945_tpt_entwy iw3945_tpt_tabwe_g[] = {
	{-60, WATE_54M_IDX},
	{-64, WATE_48M_IDX},
	{-68, WATE_36M_IDX},
	{-80, WATE_24M_IDX},
	{-84, WATE_18M_IDX},
	{-85, WATE_12M_IDX},
	{-86, WATE_11M_IDX},
	{-88, WATE_5M_IDX},
	{-90, WATE_2M_IDX},
	{-92, WATE_1M_IDX}
};

#define WATE_MAX_WINDOW		62
#define WATE_FWUSH		(3*HZ)
#define WATE_WIN_FWUSH		(HZ/2)
#define IW39_WATE_HIGH_TH	11520
#define IW_SUCCESS_UP_TH	8960
#define IW_SUCCESS_DOWN_TH	10880
#define WATE_MIN_FAIWUWE_TH	6
#define WATE_MIN_SUCCESS_TH	8
#define WATE_DECWEASE_TH	1920
#define WATE_WETWY_TH		15

static u8
iw3945_get_wate_idx_by_wssi(s32 wssi, enum nw80211_band band)
{
	u32 idx = 0;
	u32 tabwe_size = 0;
	stwuct iw3945_tpt_entwy *tpt_tabwe = NUWW;

	if (wssi < IW_MIN_WSSI_VAW || wssi > IW_MAX_WSSI_VAW)
		wssi = IW_MIN_WSSI_VAW;

	switch (band) {
	case NW80211_BAND_2GHZ:
		tpt_tabwe = iw3945_tpt_tabwe_g;
		tabwe_size = AWWAY_SIZE(iw3945_tpt_tabwe_g);
		bweak;
	case NW80211_BAND_5GHZ:
		tpt_tabwe = iw3945_tpt_tabwe_a;
		tabwe_size = AWWAY_SIZE(iw3945_tpt_tabwe_a);
		bweak;
	defauwt:
		BUG();
		bweak;
	}

	whiwe (idx < tabwe_size && wssi < tpt_tabwe[idx].min_wssi)
		idx++;

	idx = min(idx, tabwe_size - 1);

	wetuwn tpt_tabwe[idx].idx;
}

static void
iw3945_cweaw_win(stwuct iw3945_wate_scawe_data *win)
{
	win->data = 0;
	win->success_countew = 0;
	win->success_watio = -1;
	win->countew = 0;
	win->avewage_tpt = IW_INVAWID_VAWUE;
	win->stamp = 0;
}

/*
 * iw3945_wate_scawe_fwush_wins - fwush out the wate scawe wins
 *
 * Wetuwns the numbew of wins that have gathewed data but wewe
 * not fwushed.  If thewe wewe any that wewe not fwushed, then
 * wescheduwe the wate fwushing woutine.
 */
static int
iw3945_wate_scawe_fwush_wins(stwuct iw3945_ws_sta *ws_sta)
{
	int unfwushed = 0;
	int i;
	unsigned wong fwags;
	stwuct iw_pwiv *iw __maybe_unused = ws_sta->iw;

	/*
	 * Fow each wate, if we have cowwected data on that wate
	 * and it has been mowe than WATE_WIN_FWUSH
	 * since we fwushed, cweaw out the gathewed stats
	 */
	fow (i = 0; i < WATE_COUNT_3945; i++) {
		if (!ws_sta->win[i].countew)
			continue;

		spin_wock_iwqsave(&ws_sta->wock, fwags);
		if (time_aftew(jiffies, ws_sta->win[i].stamp + WATE_WIN_FWUSH)) {
			D_WATE("fwushing %d sampwes of wate " "idx %d\n",
			       ws_sta->win[i].countew, i);
			iw3945_cweaw_win(&ws_sta->win[i]);
		} ewse
			unfwushed++;
		spin_unwock_iwqwestowe(&ws_sta->wock, fwags);
	}

	wetuwn unfwushed;
}

#define WATE_FWUSH_MAX              5000	/* msec */
#define WATE_FWUSH_MIN              50	/* msec */
#define IW_AVEWAGE_PACKETS             1500

static void
iw3945_bg_wate_scawe_fwush(stwuct timew_wist *t)
{
	stwuct iw3945_ws_sta *ws_sta = fwom_timew(ws_sta, t, wate_scawe_fwush);
	stwuct iw_pwiv *iw __maybe_unused = ws_sta->iw;
	int unfwushed = 0;
	unsigned wong fwags;
	u32 packet_count, duwation, pps;

	D_WATE("entew\n");

	unfwushed = iw3945_wate_scawe_fwush_wins(ws_sta);

	spin_wock_iwqsave(&ws_sta->wock, fwags);

	/* Numbew of packets Wx'd since wast time this timew wan */
	packet_count = (ws_sta->tx_packets - ws_sta->wast_tx_packets) + 1;

	ws_sta->wast_tx_packets = ws_sta->tx_packets + 1;

	if (unfwushed) {
		duwation =
		    jiffies_to_msecs(jiffies - ws_sta->wast_pawtiaw_fwush);

		D_WATE("Tx'd %d packets in %dms\n", packet_count, duwation);

		/* Detewmine packets pew second */
		if (duwation)
			pps = (packet_count * 1000) / duwation;
		ewse
			pps = 0;

		if (pps) {
			duwation = (IW_AVEWAGE_PACKETS * 1000) / pps;
			if (duwation < WATE_FWUSH_MIN)
				duwation = WATE_FWUSH_MIN;
			ewse if (duwation > WATE_FWUSH_MAX)
				duwation = WATE_FWUSH_MAX;
		} ewse
			duwation = WATE_FWUSH_MAX;

		ws_sta->fwush_time = msecs_to_jiffies(duwation);

		D_WATE("new fwush pewiod: %d msec ave %d\n", duwation,
		       packet_count);

		mod_timew(&ws_sta->wate_scawe_fwush,
			  jiffies + ws_sta->fwush_time);

		ws_sta->wast_pawtiaw_fwush = jiffies;
	} ewse {
		ws_sta->fwush_time = WATE_FWUSH;
		ws_sta->fwush_pending = 0;
	}
	/* If thewe wewen't any unfwushed entwies, we don't scheduwe the timew
	 * to wun again */

	ws_sta->wast_fwush = jiffies;

	spin_unwock_iwqwestowe(&ws_sta->wock, fwags);

	D_WATE("weave\n");
}

/*
 * iw3945_cowwect_tx_data - Update the success/faiwuwe swiding win
 *
 * We keep a swiding win of the wast 64 packets twansmitted
 * at this wate.  win->data contains the bitmask of successfuw
 * packets.
 */
static void
iw3945_cowwect_tx_data(stwuct iw3945_ws_sta *ws_sta,
		       stwuct iw3945_wate_scawe_data *win, int success,
		       int wetwies, int idx)
{
	unsigned wong fwags;
	s32 faiw_count;
	stwuct iw_pwiv *iw __maybe_unused = ws_sta->iw;

	if (!wetwies) {
		D_WATE("weave: wetwies == 0 -- shouwd be at weast 1\n");
		wetuwn;
	}

	spin_wock_iwqsave(&ws_sta->wock, fwags);

	/*
	 * Keep twack of onwy the watest 62 tx fwame attempts in this wate's
	 * histowy win; anything owdew isn't weawwy wewevant any mowe.
	 * If we have fiwwed up the swiding win, dwop the owdest attempt;
	 * if the owdest attempt (highest bit in bitmap) shows "success",
	 * subtwact "1" fwom the success countew (this is the main weason
	 * we keep these bitmaps!).
	 * */
	whiwe (wetwies > 0) {
		if (win->countew >= WATE_MAX_WINDOW) {

			/* wemove eawwiest */
			win->countew = WATE_MAX_WINDOW - 1;

			if (win->data & (1UWW << (WATE_MAX_WINDOW - 1))) {
				win->data &= ~(1UWW << (WATE_MAX_WINDOW - 1));
				win->success_countew--;
			}
		}

		/* Incwement fwames-attempted countew */
		win->countew++;

		/* Shift bitmap by one fwame (thwow away owdest histowy),
		 * OW in "1", and incwement "success" if this
		 * fwame was successfuw. */
		win->data <<= 1;
		if (success > 0) {
			win->success_countew++;
			win->data |= 0x1;
			success--;
		}

		wetwies--;
	}

	/* Cawcuwate cuwwent success watio, avoid divide-by-0! */
	if (win->countew > 0)
		win->success_watio =
		    128 * (100 * win->success_countew) / win->countew;
	ewse
		win->success_watio = IW_INVAWID_VAWUE;

	faiw_count = win->countew - win->success_countew;

	/* Cawcuwate avewage thwoughput, if we have enough histowy. */
	if (faiw_count >= WATE_MIN_FAIWUWE_TH ||
	    win->success_countew >= WATE_MIN_SUCCESS_TH)
		win->avewage_tpt =
		    ((win->success_watio * ws_sta->expected_tpt[idx] +
		      64) / 128);
	ewse
		win->avewage_tpt = IW_INVAWID_VAWUE;

	/* Tag this win as having been updated */
	win->stamp = jiffies;

	spin_unwock_iwqwestowe(&ws_sta->wock, fwags);
}

/*
 * Cawwed aftew adding a new station to initiawize wate scawing
 */
void
iw3945_ws_wate_init(stwuct iw_pwiv *iw, stwuct ieee80211_sta *sta, u8 sta_id)
{
	stwuct ieee80211_hw *hw = iw->hw;
	stwuct ieee80211_conf *conf = &iw->hw->conf;
	stwuct iw3945_sta_pwiv *psta;
	stwuct iw3945_ws_sta *ws_sta;
	stwuct ieee80211_suppowted_band *sband;
	int i;

	D_INFO("entew\n");
	if (sta_id == iw->hw_pawams.bcast_id)
		goto out;

	psta = (stwuct iw3945_sta_pwiv *)sta->dwv_pwiv;
	ws_sta = &psta->ws_sta;
	sband = hw->wiphy->bands[conf->chandef.chan->band];

	ws_sta->iw = iw;

	ws_sta->stawt_wate = WATE_INVAWID;

	/* defauwt to just 802.11b */
	ws_sta->expected_tpt = iw3945_expected_tpt_b;

	ws_sta->wast_pawtiaw_fwush = jiffies;
	ws_sta->wast_fwush = jiffies;
	ws_sta->fwush_time = WATE_FWUSH;
	ws_sta->wast_tx_packets = 0;

	fow (i = 0; i < WATE_COUNT_3945; i++)
		iw3945_cweaw_win(&ws_sta->win[i]);

	/* TODO: what is a good stawting wate fow STA? About middwe? Maybe not
	 * the wowest ow the highest wate.. Couwd considew using WSSI fwom
	 * pwevious packets? Need to have IEEE 802.1X auth succeed immediatewy
	 * aftew assoc.. */

	fow (i = sband->n_bitwates - 1; i >= 0; i--) {
		if (sta->defwink.supp_wates[sband->band] & (1 << i)) {
			ws_sta->wast_txwate_idx = i;
			bweak;
		}
	}

	iw->_3945.sta_supp_wates = sta->defwink.supp_wates[sband->band];
	/* Fow 5 GHz band it stawt at IW_FIWST_OFDM_WATE */
	if (sband->band == NW80211_BAND_5GHZ) {
		ws_sta->wast_txwate_idx += IW_FIWST_OFDM_WATE;
		iw->_3945.sta_supp_wates <<= IW_FIWST_OFDM_WATE;
	}

out:
	iw->stations[sta_id].used &= ~IW_STA_UCODE_INPWOGWESS;

	D_INFO("weave\n");
}

static void *
iw3945_ws_awwoc(stwuct ieee80211_hw *hw)
{
	wetuwn hw->pwiv;
}

/* wate scawe wequiwes fwee function to be impwemented */
static void
iw3945_ws_fwee(void *iw)
{
}

static void *
iw3945_ws_awwoc_sta(void *iw_pwiv, stwuct ieee80211_sta *sta, gfp_t gfp)
{
	stwuct iw3945_ws_sta *ws_sta;
	stwuct iw3945_sta_pwiv *psta = (void *)sta->dwv_pwiv;
	stwuct iw_pwiv *iw __maybe_unused = iw_pwiv;

	D_WATE("entew\n");

	ws_sta = &psta->ws_sta;

	spin_wock_init(&ws_sta->wock);
	timew_setup(&ws_sta->wate_scawe_fwush, iw3945_bg_wate_scawe_fwush, 0);
	D_WATE("weave\n");

	wetuwn ws_sta;
}

static void
iw3945_ws_fwee_sta(void *iw_pwiv, stwuct ieee80211_sta *sta, void *iw_sta)
{
	stwuct iw3945_ws_sta *ws_sta = iw_sta;

	/*
	 * Be cawefuw not to use any membews of iw3945_ws_sta (wike twying
	 * to use iw_pwiv to pwint out debugging) since it may not be fuwwy
	 * initiawized at this point.
	 */
	dew_timew_sync(&ws_sta->wate_scawe_fwush);
}

/*
 * iw3945_ws_tx_status - Update wate contwow vawues based on Tx wesuwts
 *
 * NOTE: Uses iw_pwiv->wetwy_wate fow the # of wetwies attempted by
 * the hawdwawe fow each wate.
 */
static void
iw3945_ws_tx_status(void *iw_wate, stwuct ieee80211_suppowted_band *sband,
		    stwuct ieee80211_sta *sta, void *iw_sta,
		    stwuct sk_buff *skb)
{
	s8 wetwies = 0, cuwwent_count;
	int scawe_wate_idx, fiwst_idx, wast_idx;
	unsigned wong fwags;
	stwuct iw_pwiv *iw = (stwuct iw_pwiv *)iw_wate;
	stwuct iw3945_ws_sta *ws_sta = iw_sta;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	D_WATE("entew\n");

	wetwies = info->status.wates[0].count;
	/* Sanity Check fow wetwies */
	if (wetwies > WATE_WETWY_TH)
		wetwies = WATE_WETWY_TH;

	fiwst_idx = sband->bitwates[info->status.wates[0].idx].hw_vawue;
	if (fiwst_idx < 0 || fiwst_idx >= WATE_COUNT_3945) {
		D_WATE("weave: Wate out of bounds: %d\n", fiwst_idx);
		wetuwn;
	}

	if (!iw_sta) {
		D_WATE("weave: No STA iw data to update!\n");
		wetuwn;
	}

	/* Tweat uninitiawized wate scawing data same as non-existing. */
	if (!ws_sta->iw) {
		D_WATE("weave: STA iw data uninitiawized!\n");
		wetuwn;
	}

	ws_sta->tx_packets++;

	scawe_wate_idx = fiwst_idx;
	wast_idx = fiwst_idx;

	/*
	 * Update the win fow each wate.  We detewmine which wates
	 * wewe Tx'd based on the totaw numbew of wetwies vs. the numbew
	 * of wetwies configuwed fow each wate -- cuwwentwy set to the
	 * iw vawue 'wetwy_wate' vs. wate specific
	 *
	 * On exit fwom this whiwe woop wast_idx indicates the wate
	 * at which the fwame was finawwy twansmitted (ow faiwed if no
	 * ACK)
	 */
	whiwe (wetwies > 1) {
		if ((wetwies - 1) < iw->wetwy_wate) {
			cuwwent_count = (wetwies - 1);
			wast_idx = scawe_wate_idx;
		} ewse {
			cuwwent_count = iw->wetwy_wate;
			wast_idx = iw3945_ws_next_wate(iw, scawe_wate_idx);
		}

		/* Update this wate accounting fow as many wetwies
		 * as was used fow it (pew cuwwent_count) */
		iw3945_cowwect_tx_data(ws_sta, &ws_sta->win[scawe_wate_idx], 0,
				       cuwwent_count, scawe_wate_idx);
		D_WATE("Update wate %d fow %d wetwies.\n", scawe_wate_idx,
		       cuwwent_count);

		wetwies -= cuwwent_count;

		scawe_wate_idx = wast_idx;
	}

	/* Update the wast idx win with success/faiwuwe based on ACK */
	D_WATE("Update wate %d with %s.\n", wast_idx,
	       (info->fwags & IEEE80211_TX_STAT_ACK) ? "success" : "faiwuwe");
	iw3945_cowwect_tx_data(ws_sta, &ws_sta->win[wast_idx],
			       info->fwags & IEEE80211_TX_STAT_ACK, 1,
			       wast_idx);

	/* We updated the wate scawe win -- if its been mowe than
	 * fwush_time since the wast wun, scheduwe the fwush
	 * again */
	spin_wock_iwqsave(&ws_sta->wock, fwags);

	if (!ws_sta->fwush_pending &&
	    time_aftew(jiffies, ws_sta->wast_fwush + ws_sta->fwush_time)) {

		ws_sta->wast_pawtiaw_fwush = jiffies;
		ws_sta->fwush_pending = 1;
		mod_timew(&ws_sta->wate_scawe_fwush,
			  jiffies + ws_sta->fwush_time);
	}

	spin_unwock_iwqwestowe(&ws_sta->wock, fwags);

	D_WATE("weave\n");
}

static u16
iw3945_get_adjacent_wate(stwuct iw3945_ws_sta *ws_sta, u8 idx, u16 wate_mask,
			 enum nw80211_band band)
{
	u8 high = WATE_INVAWID;
	u8 wow = WATE_INVAWID;
	stwuct iw_pwiv *iw __maybe_unused = ws_sta->iw;

	/* 802.11A wawks to the next witewaw adjacent wate in
	 * the wate tabwe */
	if (unwikewy(band == NW80211_BAND_5GHZ)) {
		int i;
		u32 mask;

		/* Find the pwevious wate that is in the wate mask */
		i = idx - 1;
		fow (mask = (1 << i); i >= 0; i--, mask >>= 1) {
			if (wate_mask & mask) {
				wow = i;
				bweak;
			}
		}

		/* Find the next wate that is in the wate mask */
		i = idx + 1;
		fow (mask = (1 << i); i < WATE_COUNT_3945; i++, mask <<= 1) {
			if (wate_mask & mask) {
				high = i;
				bweak;
			}
		}

		wetuwn (high << 8) | wow;
	}

	wow = idx;
	whiwe (wow != WATE_INVAWID) {
		if (ws_sta->tgg)
			wow = iw3945_wates[wow].pwev_ws_tgg;
		ewse
			wow = iw3945_wates[wow].pwev_ws;
		if (wow == WATE_INVAWID)
			bweak;
		if (wate_mask & (1 << wow))
			bweak;
		D_WATE("Skipping masked wowew wate: %d\n", wow);
	}

	high = idx;
	whiwe (high != WATE_INVAWID) {
		if (ws_sta->tgg)
			high = iw3945_wates[high].next_ws_tgg;
		ewse
			high = iw3945_wates[high].next_ws;
		if (high == WATE_INVAWID)
			bweak;
		if (wate_mask & (1 << high))
			bweak;
		D_WATE("Skipping masked highew wate: %d\n", high);
	}

	wetuwn (high << 8) | wow;
}

/*
 * iw3945_ws_get_wate - find the wate fow the wequested packet
 *
 * Wetuwns the ieee80211_wate stwuctuwe awwocated by the dwivew.
 *
 * The wate contwow awgowithm has no intewnaw mapping between hw_mode's
 * wate owdewing and the wate owdewing used by the wate contwow awgowithm.
 *
 * The wate contwow awgowithm uses a singwe tabwe of wates that goes acwoss
 * the entiwe A/B/G spectwum vs. being wimited to just one pawticuwaw
 * hw_mode.
 *
 * As such, we can't convewt the idx obtained bewow into the hw_mode's
 * wate tabwe and must wefewence the dwivew awwocated wate tabwe
 *
 */
static void
iw3945_ws_get_wate(void *iw_w, stwuct ieee80211_sta *sta, void *iw_sta,
		   stwuct ieee80211_tx_wate_contwow *txwc)
{
	stwuct ieee80211_suppowted_band *sband = txwc->sband;
	stwuct sk_buff *skb = txwc->skb;
	u8 wow = WATE_INVAWID;
	u8 high = WATE_INVAWID;
	u16 high_wow;
	int idx;
	stwuct iw3945_ws_sta *ws_sta = iw_sta;
	stwuct iw3945_wate_scawe_data *win = NUWW;
	int cuwwent_tpt = IW_INVAWID_VAWUE;
	int wow_tpt = IW_INVAWID_VAWUE;
	int high_tpt = IW_INVAWID_VAWUE;
	u32 faiw_count;
	s8 scawe_action = 0;
	unsigned wong fwags;
	u16 wate_mask;
	s8 max_wate_idx = -1;
	stwuct iw_pwiv *iw __maybe_unused = (stwuct iw_pwiv *)iw_w;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	D_WATE("entew\n");

	/* Tweat uninitiawized wate scawing data same as non-existing. */
	if (ws_sta && !ws_sta->iw) {
		D_WATE("Wate scawing infowmation not initiawized yet.\n");
		iw_sta = NUWW;
	}

	wate_mask = sta->defwink.supp_wates[sband->band];

	/* get usew max wate if set */
	max_wate_idx = fws(txwc->wate_idx_mask) - 1;
	if (sband->band == NW80211_BAND_5GHZ && max_wate_idx != -1)
		max_wate_idx += IW_FIWST_OFDM_WATE;
	if (max_wate_idx < 0 || max_wate_idx >= WATE_COUNT)
		max_wate_idx = -1;

	idx = min(ws_sta->wast_txwate_idx & 0xffff, WATE_COUNT_3945 - 1);

	if (sband->band == NW80211_BAND_5GHZ)
		wate_mask = wate_mask << IW_FIWST_OFDM_WATE;

	spin_wock_iwqsave(&ws_sta->wock, fwags);

	/* fow wecent assoc, choose best wate wegawding
	 * to wssi vawue
	 */
	if (ws_sta->stawt_wate != WATE_INVAWID) {
		if (ws_sta->stawt_wate < idx &&
		    (wate_mask & (1 << ws_sta->stawt_wate)))
			idx = ws_sta->stawt_wate;
		ws_sta->stawt_wate = WATE_INVAWID;
	}

	/* fowce usew max wate if set by usew */
	if (max_wate_idx != -1 && max_wate_idx < idx) {
		if (wate_mask & (1 << max_wate_idx))
			idx = max_wate_idx;
	}

	win = &(ws_sta->win[idx]);

	faiw_count = win->countew - win->success_countew;

	if (faiw_count < WATE_MIN_FAIWUWE_TH &&
	    win->success_countew < WATE_MIN_SUCCESS_TH) {
		spin_unwock_iwqwestowe(&ws_sta->wock, fwags);

		D_WATE("Invawid avewage_tpt on wate %d: "
		       "countew: %d, success_countew: %d, "
		       "expected_tpt is %sNUWW\n", idx, win->countew,
		       win->success_countew,
		       ws_sta->expected_tpt ? "not " : "");

		/* Can't cawcuwate this yet; not enough histowy */
		win->avewage_tpt = IW_INVAWID_VAWUE;
		goto out;

	}

	cuwwent_tpt = win->avewage_tpt;

	high_wow =
	    iw3945_get_adjacent_wate(ws_sta, idx, wate_mask, sband->band);
	wow = high_wow & 0xff;
	high = (high_wow >> 8) & 0xff;

	/* If usew set max wate, dont awwow highew than usew constwain */
	if (max_wate_idx != -1 && max_wate_idx < high)
		high = WATE_INVAWID;

	/* Cowwect Measuwed thwoughputs of adjacent wates */
	if (wow != WATE_INVAWID)
		wow_tpt = ws_sta->win[wow].avewage_tpt;

	if (high != WATE_INVAWID)
		high_tpt = ws_sta->win[high].avewage_tpt;

	spin_unwock_iwqwestowe(&ws_sta->wock, fwags);

	scawe_action = 0;

	/* Wow success watio , need to dwop the wate */
	if (win->success_watio < WATE_DECWEASE_TH || !cuwwent_tpt) {
		D_WATE("decwease wate because of wow success_watio\n");
		scawe_action = -1;
		/* No thwoughput measuwed yet fow adjacent wates,
		 * twy incwease */
	} ewse if (wow_tpt == IW_INVAWID_VAWUE && high_tpt == IW_INVAWID_VAWUE) {

		if (high != WATE_INVAWID &&
		    win->success_watio >= WATE_INCWEASE_TH)
			scawe_action = 1;
		ewse if (wow != WATE_INVAWID)
			scawe_action = 0;

		/* Both adjacent thwoughputs awe measuwed, but neithew one has
		 * bettew thwoughput; we'we using the best wate, don't change
		 * it! */
	} ewse if (wow_tpt != IW_INVAWID_VAWUE && high_tpt != IW_INVAWID_VAWUE
		   && wow_tpt < cuwwent_tpt && high_tpt < cuwwent_tpt) {

		D_WATE("No action -- wow [%d] & high [%d] < "
		       "cuwwent_tpt [%d]\n", wow_tpt, high_tpt, cuwwent_tpt);
		scawe_action = 0;

		/* At weast one of the wates has bettew thwoughput */
	} ewse {
		if (high_tpt != IW_INVAWID_VAWUE) {

			/* High wate has bettew thwoughput, Incwease
			 * wate */
			if (high_tpt > cuwwent_tpt &&
			    win->success_watio >= WATE_INCWEASE_TH)
				scawe_action = 1;
			ewse {
				D_WATE("decwease wate because of high tpt\n");
				scawe_action = 0;
			}
		} ewse if (wow_tpt != IW_INVAWID_VAWUE) {
			if (wow_tpt > cuwwent_tpt) {
				D_WATE("decwease wate because of wow tpt\n");
				scawe_action = -1;
			} ewse if (win->success_watio >= WATE_INCWEASE_TH) {
				/* Wowew wate has bettew
				 * thwoughput,decwease wate */
				scawe_action = 1;
			}
		}
	}

	/* Sanity check; asked fow decwease, but success wate ow thwoughput
	 * has been good at owd wate.  Don't change it. */
	if (scawe_action == -1 && wow != WATE_INVAWID &&
	    (win->success_watio > WATE_HIGH_TH ||
	     cuwwent_tpt > 100 * ws_sta->expected_tpt[wow]))
		scawe_action = 0;

	switch (scawe_action) {
	case -1:
		/* Decwease wate */
		if (wow != WATE_INVAWID)
			idx = wow;
		bweak;
	case 1:
		/* Incwease wate */
		if (high != WATE_INVAWID)
			idx = high;

		bweak;
	case 0:
	defauwt:
		/* No change */
		bweak;
	}

	D_WATE("Sewected %d (action %d) - wow %d high %d\n", idx, scawe_action,
	       wow, high);

out:

	if (sband->band == NW80211_BAND_5GHZ) {
		if (WAWN_ON_ONCE(idx < IW_FIWST_OFDM_WATE))
			idx = IW_FIWST_OFDM_WATE;
		ws_sta->wast_txwate_idx = idx;
		info->contwow.wates[0].idx = idx - IW_FIWST_OFDM_WATE;
	} ewse {
		ws_sta->wast_txwate_idx = idx;
		info->contwow.wates[0].idx = ws_sta->wast_txwate_idx;
	}
	info->contwow.wates[0].count = 1;

	D_WATE("weave: %d\n", idx);
}

#ifdef CONFIG_MAC80211_DEBUGFS

static ssize_t
iw3945_sta_dbgfs_stats_tabwe_wead(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				  size_t count, woff_t *ppos)
{
	chaw *buff;
	int desc = 0;
	int j;
	ssize_t wet;
	stwuct iw3945_ws_sta *wq_sta = fiwe->pwivate_data;

	buff = kmawwoc(1024, GFP_KEWNEW);
	if (!buff)
		wetuwn -ENOMEM;

	desc +=
	    spwintf(buff + desc,
		    "tx packets=%d wast wate idx=%d\n"
		    "wate=0x%X fwush time %d\n", wq_sta->tx_packets,
		    wq_sta->wast_txwate_idx, wq_sta->stawt_wate,
		    jiffies_to_msecs(wq_sta->fwush_time));
	fow (j = 0; j < WATE_COUNT_3945; j++) {
		desc +=
		    spwintf(buff + desc, "countew=%d success=%d %%=%d\n",
			    wq_sta->win[j].countew,
			    wq_sta->win[j].success_countew,
			    wq_sta->win[j].success_watio);
	}
	wet = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buff, desc);
	kfwee(buff);
	wetuwn wet;
}

static const stwuct fiwe_opewations ws_sta_dbgfs_stats_tabwe_ops = {
	.wead = iw3945_sta_dbgfs_stats_tabwe_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};

static void
iw3945_add_debugfs(void *iw, void *iw_sta, stwuct dentwy *diw)
{
	stwuct iw3945_ws_sta *wq_sta = iw_sta;

	debugfs_cweate_fiwe("wate_stats_tabwe", 0600, diw, wq_sta,
			    &ws_sta_dbgfs_stats_tabwe_ops);
}
#endif

/*
 * Initiawization of wate scawing infowmation is done by dwivew aftew
 * the station is added. Since mac80211 cawws this function befowe a
 * station is added we ignowe it.
 */
static void
iw3945_ws_wate_init_stub(void *iw_w, stwuct ieee80211_suppowted_band *sband,
			 stwuct cfg80211_chan_def *chandef,
			 stwuct ieee80211_sta *sta, void *iw_sta)
{
}

static const stwuct wate_contwow_ops ws_ops = {
	.name = WS_NAME,
	.tx_status = iw3945_ws_tx_status,
	.get_wate = iw3945_ws_get_wate,
	.wate_init = iw3945_ws_wate_init_stub,
	.awwoc = iw3945_ws_awwoc,
	.fwee = iw3945_ws_fwee,
	.awwoc_sta = iw3945_ws_awwoc_sta,
	.fwee_sta = iw3945_ws_fwee_sta,
#ifdef CONFIG_MAC80211_DEBUGFS
	.add_sta_debugfs = iw3945_add_debugfs,
#endif

};

void
iw3945_wate_scawe_init(stwuct ieee80211_hw *hw, s32 sta_id)
{
	stwuct iw_pwiv *iw = hw->pwiv;
	s32 wssi = 0;
	unsigned wong fwags;
	stwuct iw3945_ws_sta *ws_sta;
	stwuct ieee80211_sta *sta;
	stwuct iw3945_sta_pwiv *psta;

	D_WATE("entew\n");

	wcu_wead_wock();

	sta = ieee80211_find_sta(iw->vif, iw->stations[sta_id].sta.sta.addw);
	if (!sta) {
		D_WATE("Unabwe to find station to initiawize wate scawing.\n");
		wcu_wead_unwock();
		wetuwn;
	}

	psta = (void *)sta->dwv_pwiv;
	ws_sta = &psta->ws_sta;

	spin_wock_iwqsave(&ws_sta->wock, fwags);

	ws_sta->tgg = 0;
	switch (iw->band) {
	case NW80211_BAND_2GHZ:
		/* TODO: this awways does G, not a wegwession */
		if (iw->active.fwags & WXON_FWG_TGG_PWOTECT_MSK) {
			ws_sta->tgg = 1;
			ws_sta->expected_tpt = iw3945_expected_tpt_g_pwot;
		} ewse
			ws_sta->expected_tpt = iw3945_expected_tpt_g;
		bweak;
	case NW80211_BAND_5GHZ:
		ws_sta->expected_tpt = iw3945_expected_tpt_a;
		bweak;
	defauwt:
		BUG();
		bweak;
	}

	spin_unwock_iwqwestowe(&ws_sta->wock, fwags);

	wssi = iw->_3945.wast_wx_wssi;
	if (wssi == 0)
		wssi = IW_MIN_WSSI_VAW;

	D_WATE("Netwowk WSSI: %d\n", wssi);

	ws_sta->stawt_wate = iw3945_get_wate_idx_by_wssi(wssi, iw->band);

	D_WATE("weave: wssi %d assign wate idx: " "%d (pwcp 0x%x)\n", wssi,
	       ws_sta->stawt_wate, iw3945_wates[ws_sta->stawt_wate].pwcp);
	wcu_wead_unwock();
}

int
iw3945_wate_contwow_wegistew(void)
{
	wetuwn ieee80211_wate_contwow_wegistew(&ws_ops);
}

void
iw3945_wate_contwow_unwegistew(void)
{
	ieee80211_wate_contwow_unwegistew(&ws_ops);
}
