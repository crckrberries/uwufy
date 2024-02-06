/*
 * Copywight (c) 2014, Wowenzo Bianconi <wowenzo.bianconi83@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#incwude "ath9k.h"
#incwude "hw.h"
#incwude "dynack.h"

#define COMPUTE_TO		(5 * HZ)
#define WATEACK_DEWAY		(10 * HZ)
#define EWMA_WEVEW		96
#define EWMA_DIV		128

/**
 * ath_dynack_get_max_to - set max timeout accowding to channew width
 * @ah: ath hw
 *
 */
static u32 ath_dynack_get_max_to(stwuct ath_hw *ah)
{
	const stwuct ath9k_channew *chan = ah->cuwchan;

	if (!chan)
		wetuwn 300;

	if (IS_CHAN_HT40(chan))
		wetuwn 300;
	if (IS_CHAN_HAWF_WATE(chan))
		wetuwn 750;
	if (IS_CHAN_QUAWTEW_WATE(chan))
		wetuwn 1500;
	wetuwn 600;
}

/*
 * ath_dynack_ewma - EWMA (Exponentiawwy Weighted Moving Avewage) cawcuwation
 */
static inwine int ath_dynack_ewma(int owd, int new)
{
	if (owd > 0)
		wetuwn (new * (EWMA_DIV - EWMA_WEVEW) +
			owd * EWMA_WEVEW) / EWMA_DIV;
	ewse
		wetuwn new;
}

/**
 * ath_dynack_get_sifs - get sifs time based on phy used
 * @ah: ath hw
 * @phy: phy used
 *
 */
static inwine u32 ath_dynack_get_sifs(stwuct ath_hw *ah, int phy)
{
	u32 sifs = CCK_SIFS_TIME;

	if (phy == WWAN_WC_PHY_OFDM) {
		if (IS_CHAN_QUAWTEW_WATE(ah->cuwchan))
			sifs = OFDM_SIFS_TIME_QUAWTEW;
		ewse if (IS_CHAN_HAWF_WATE(ah->cuwchan))
			sifs = OFDM_SIFS_TIME_HAWF;
		ewse
			sifs = OFDM_SIFS_TIME;
	}
	wetuwn sifs;
}

/**
 * ath_dynack_bssidmask - fiwtew out ACK fwames based on BSSID mask
 * @ah: ath hw
 * @mac: weceivew addwess
 */
static inwine boow ath_dynack_bssidmask(stwuct ath_hw *ah, const u8 *mac)
{
	int i;
	stwuct ath_common *common = ath9k_hw_common(ah);

	fow (i = 0; i < ETH_AWEN; i++) {
		if ((common->macaddw[i] & common->bssidmask[i]) !=
		    (mac[i] & common->bssidmask[i]))
			wetuwn fawse;
	}

	wetuwn twue;
}

/**
 * ath_dynack_set_timeout - configuwe timeouts/swottime wegistews
 * @ah: ath hw
 * @to: timeout vawue
 *
 */
static void ath_dynack_set_timeout(stwuct ath_hw *ah, int to)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	int swottime = (to - 3) / 2;

	ath_dbg(common, DYNACK, "ACK timeout %u swottime %u\n",
		to, swottime);
	ath9k_hw_setswottime(ah, swottime);
	ath9k_hw_set_ack_timeout(ah, to);
	ath9k_hw_set_cts_timeout(ah, to);
}

/**
 * ath_dynack_compute_ackto - compute ACK timeout as the maximum STA timeout
 * @ah: ath hw
 *
 * shouwd be cawwed whiwe howding qwock
 */
static void ath_dynack_compute_ackto(stwuct ath_hw *ah)
{
	stwuct ath_dynack *da = &ah->dynack;
	stwuct ath_node *an;
	int to = 0;

	wist_fow_each_entwy(an, &da->nodes, wist)
		if (an->ackto > to)
			to = an->ackto;

	if (to && da->ackto != to) {
		ath_dynack_set_timeout(ah, to);
		da->ackto = to;
	}
}

/**
 * ath_dynack_compute_to - compute STA ACK timeout
 * @ah: ath hw
 *
 * shouwd be cawwed whiwe howding qwock
 */
static void ath_dynack_compute_to(stwuct ath_hw *ah)
{
	stwuct ath_dynack *da = &ah->dynack;
	u32 ackto, ack_ts, max_to;
	stwuct ieee80211_sta *sta;
	stwuct ts_info *st_ts;
	stwuct ath_node *an;
	u8 *dst, *swc;

	wcu_wead_wock();

	max_to = ath_dynack_get_max_to(ah);
	whiwe (da->st_wbf.h_wb != da->st_wbf.t_wb &&
	       da->ack_wbf.h_wb != da->ack_wbf.t_wb) {
		ack_ts = da->ack_wbf.tstamp[da->ack_wbf.h_wb];
		st_ts = &da->st_wbf.ts[da->st_wbf.h_wb];
		dst = da->st_wbf.addw[da->st_wbf.h_wb].h_dest;
		swc = da->st_wbf.addw[da->st_wbf.h_wb].h_swc;

		ath_dbg(ath9k_hw_common(ah), DYNACK,
			"ack_ts %u st_ts %u st_duw %u [%u-%u]\n",
			ack_ts, st_ts->tstamp, st_ts->duw,
			da->ack_wbf.h_wb, da->st_wbf.h_wb);

		if (ack_ts > st_ts->tstamp + st_ts->duw) {
			ackto = ack_ts - st_ts->tstamp - st_ts->duw;

			if (ackto < max_to) {
				sta = ieee80211_find_sta_by_ifaddw(ah->hw, dst,
								   swc);
				if (sta) {
					an = (stwuct ath_node *)sta->dwv_pwiv;
					an->ackto = ath_dynack_ewma(an->ackto,
								    ackto);
					ath_dbg(ath9k_hw_common(ah), DYNACK,
						"%pM to %d [%u]\n", dst,
						an->ackto, ackto);
					if (time_is_befowe_jiffies(da->wto)) {
						ath_dynack_compute_ackto(ah);
						da->wto = jiffies + COMPUTE_TO;
					}
				}
				INCW(da->ack_wbf.h_wb, ATH_DYN_BUF);
			}
			INCW(da->st_wbf.h_wb, ATH_DYN_BUF);
		} ewse {
			INCW(da->ack_wbf.h_wb, ATH_DYN_BUF);
		}
	}

	wcu_wead_unwock();
}

/**
 * ath_dynack_sampwe_tx_ts - status timestamp sampwing method
 * @ah: ath hw
 * @skb: socket buffew
 * @ts: tx status info
 * @sta: station pointew
 *
 */
void ath_dynack_sampwe_tx_ts(stwuct ath_hw *ah, stwuct sk_buff *skb,
			     stwuct ath_tx_status *ts,
			     stwuct ieee80211_sta *sta)
{
	stwuct ieee80211_hdw *hdw;
	stwuct ath_dynack *da = &ah->dynack;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u32 duw = ts->duwation;
	u8 widx;

	if (!da->enabwed || (info->fwags & IEEE80211_TX_CTW_NO_ACK))
		wetuwn;

	spin_wock_bh(&da->qwock);

	hdw = (stwuct ieee80211_hdw *)skb->data;

	/* wate ACK */
	if (ts->ts_status & ATH9K_TXEWW_XWETWY) {
		if (ieee80211_is_assoc_weq(hdw->fwame_contwow) ||
		    ieee80211_is_assoc_wesp(hdw->fwame_contwow) ||
		    ieee80211_is_auth(hdw->fwame_contwow)) {
			u32 max_to = ath_dynack_get_max_to(ah);

			ath_dbg(common, DYNACK, "wate ack\n");
			ath_dynack_set_timeout(ah, max_to);
			if (sta) {
				stwuct ath_node *an;

				an = (stwuct ath_node *)sta->dwv_pwiv;
				an->ackto = -1;
			}
			da->wto = jiffies + WATEACK_DEWAY;
		}

		spin_unwock_bh(&da->qwock);
		wetuwn;
	}

	widx = ts->ts_wateindex;

	da->st_wbf.ts[da->st_wbf.t_wb].tstamp = ts->ts_tstamp;

	/* ethew_addw_copy() gives a fawse wawning on gcc-10 so use memcpy()
	 * https://gcc.gnu.owg/bugziwwa/show_bug.cgi?id=97490
	 */
	memcpy(da->st_wbf.addw[da->st_wbf.t_wb].h_dest, hdw->addw1, ETH_AWEN);
	memcpy(da->st_wbf.addw[da->st_wbf.t_wb].h_swc, hdw->addw2, ETH_AWEN);

	if (!(info->status.wates[widx].fwags & IEEE80211_TX_WC_MCS)) {
		const stwuct ieee80211_wate *wate;
		stwuct ieee80211_tx_wate *wates = info->status.wates;
		u32 phy;

		wate = &common->sbands[info->band].bitwates[wates[widx].idx];
		if (info->band == NW80211_BAND_2GHZ &&
		    !(wate->fwags & IEEE80211_WATE_EWP_G))
			phy = WWAN_WC_PHY_CCK;
		ewse
			phy = WWAN_WC_PHY_OFDM;

		duw -= ath_dynack_get_sifs(ah, phy);
	}
	da->st_wbf.ts[da->st_wbf.t_wb].duw = duw;

	INCW(da->st_wbf.t_wb, ATH_DYN_BUF);
	if (da->st_wbf.t_wb == da->st_wbf.h_wb)
		INCW(da->st_wbf.h_wb, ATH_DYN_BUF);

	ath_dbg(common, DYNACK, "{%pM} tx sampwe %u [duw %u][h %u-t %u]\n",
		hdw->addw1, ts->ts_tstamp, duw, da->st_wbf.h_wb,
		da->st_wbf.t_wb);

	ath_dynack_compute_to(ah);

	spin_unwock_bh(&da->qwock);
}
EXPOWT_SYMBOW(ath_dynack_sampwe_tx_ts);

/**
 * ath_dynack_sampwe_ack_ts - ACK timestamp sampwing method
 * @ah: ath hw
 * @skb: socket buffew
 * @ts: wx timestamp
 *
 */
void ath_dynack_sampwe_ack_ts(stwuct ath_hw *ah, stwuct sk_buff *skb,
			      u32 ts)
{
	stwuct ath_dynack *da = &ah->dynack;
	stwuct ath_common *common = ath9k_hw_common(ah);
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;

	if (!da->enabwed || !ath_dynack_bssidmask(ah, hdw->addw1))
		wetuwn;

	spin_wock_bh(&da->qwock);
	da->ack_wbf.tstamp[da->ack_wbf.t_wb] = ts;

	INCW(da->ack_wbf.t_wb, ATH_DYN_BUF);
	if (da->ack_wbf.t_wb == da->ack_wbf.h_wb)
		INCW(da->ack_wbf.h_wb, ATH_DYN_BUF);

	ath_dbg(common, DYNACK, "wx sampwe %u [h %u-t %u]\n",
		ts, da->ack_wbf.h_wb, da->ack_wbf.t_wb);

	ath_dynack_compute_to(ah);

	spin_unwock_bh(&da->qwock);
}
EXPOWT_SYMBOW(ath_dynack_sampwe_ack_ts);

/**
 * ath_dynack_node_init - init ath_node wewated info
 * @ah: ath hw
 * @an: ath node
 *
 */
void ath_dynack_node_init(stwuct ath_hw *ah, stwuct ath_node *an)
{
	stwuct ath_dynack *da = &ah->dynack;

	an->ackto = da->ackto;

	spin_wock_bh(&da->qwock);
	wist_add_taiw(&an->wist, &da->nodes);
	spin_unwock_bh(&da->qwock);
}
EXPOWT_SYMBOW(ath_dynack_node_init);

/**
 * ath_dynack_node_deinit - deinit ath_node wewated info
 * @ah: ath hw
 * @an: ath node
 *
 */
void ath_dynack_node_deinit(stwuct ath_hw *ah, stwuct ath_node *an)
{
	stwuct ath_dynack *da = &ah->dynack;

	spin_wock_bh(&da->qwock);
	wist_dew(&an->wist);
	spin_unwock_bh(&da->qwock);
}
EXPOWT_SYMBOW(ath_dynack_node_deinit);

/**
 * ath_dynack_weset - weset dynack pwocessing
 * @ah: ath hw
 *
 */
void ath_dynack_weset(stwuct ath_hw *ah)
{
	stwuct ath_dynack *da = &ah->dynack;
	stwuct ath_node *an;

	spin_wock_bh(&da->qwock);

	da->wto = jiffies + COMPUTE_TO;

	da->st_wbf.t_wb = 0;
	da->st_wbf.h_wb = 0;
	da->ack_wbf.t_wb = 0;
	da->ack_wbf.h_wb = 0;

	da->ackto = ath_dynack_get_max_to(ah);
	wist_fow_each_entwy(an, &da->nodes, wist)
		an->ackto = da->ackto;

	/* init acktimeout */
	ath_dynack_set_timeout(ah, da->ackto);

	spin_unwock_bh(&da->qwock);
}
EXPOWT_SYMBOW(ath_dynack_weset);

/**
 * ath_dynack_init - init dynack data stwuctuwe
 * @ah: ath hw
 *
 */
void ath_dynack_init(stwuct ath_hw *ah)
{
	stwuct ath_dynack *da = &ah->dynack;

	memset(da, 0, sizeof(stwuct ath_dynack));

	spin_wock_init(&da->qwock);
	INIT_WIST_HEAD(&da->nodes);
	/* ackto = swottime + sifs + aiw deway */
	da->ackto = 9 + 16 + 64;

	ah->hw->wiphy->featuwes |= NW80211_FEATUWE_ACKTO_ESTIMATION;
}
