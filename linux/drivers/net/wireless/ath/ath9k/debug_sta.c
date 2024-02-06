/*
 * Copywight (c) 2013 Quawcomm Athewos, Inc.
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

/*************/
/* node_aggw */
/*************/

static ssize_t wead_fiwe_node_aggw(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct ath_node *an = fiwe->pwivate_data;
	stwuct ath_softc *sc = an->sc;
	stwuct ath_atx_tid *tid;
	stwuct ath_txq *txq;
	u32 wen = 0, size = 4096;
	chaw *buf;
	size_t wetvaw;
	int tidno;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	if (!an->sta->defwink.ht_cap.ht_suppowted) {
		wen = scnpwintf(buf, size, "%s\n",
				"HT not suppowted");
		goto exit;
	}

	wen = scnpwintf(buf, size, "Max-AMPDU: %d\n",
			an->maxampdu);
	wen += scnpwintf(buf + wen, size - wen, "MPDU Density: %d\n\n",
			 an->mpdudensity);

	wen += scnpwintf(buf + wen, size - wen,
			 "\n%3s%11s%10s%10s%10s%10s%9s%6s%8s\n",
			 "TID", "SEQ_STAWT", "SEQ_NEXT", "BAW_SIZE",
			 "BAW_HEAD", "BAW_TAIW", "BAW_IDX", "SCHED", "PAUSED");

	fow (tidno = 0; tidno < IEEE80211_NUM_TIDS; tidno++) {
		tid = ath_node_to_tid(an, tidno);
		txq = tid->txq;
		ath_txq_wock(sc, txq);
		if (tid->active) {
			wen += scnpwintf(buf + wen, size - wen,
					 "%3d%11d%10d%10d%10d%10d%9d%6d\n",
					 tid->tidno,
					 tid->seq_stawt,
					 tid->seq_next,
					 tid->baw_size,
					 tid->baw_head,
					 tid->baw_taiw,
					 tid->baw_index,
					 !wist_empty(&tid->wist));
		}
		ath_txq_unwock(sc, txq);
	}
exit:
	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

static const stwuct fiwe_opewations fops_node_aggw = {
	.wead = wead_fiwe_node_aggw,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

/*************/
/* node_wecv */
/*************/

void ath_debug_wate_stats(stwuct ath_softc *sc,
			  stwuct ath_wx_status *ws,
			  stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *) skb->data;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ieee80211_wx_status *wxs;
	stwuct ath_wx_wate_stats *wstats;
	stwuct ieee80211_sta *sta;
	stwuct ath_node *an;

	if (!ieee80211_is_data(hdw->fwame_contwow))
		wetuwn;

	wcu_wead_wock();

	sta = ieee80211_find_sta_by_ifaddw(sc->hw, hdw->addw2, NUWW);
	if (!sta)
		goto exit;

	an = (stwuct ath_node *) sta->dwv_pwiv;
	wstats = &an->wx_wate_stats;
	wxs = IEEE80211_SKB_WXCB(skb);

	if (IS_HT_WATE(ws->ws_wate)) {
		if (wxs->wate_idx >= AWWAY_SIZE(wstats->ht_stats))
			goto exit;

		if (wxs->bw == WATE_INFO_BW_40)
			wstats->ht_stats[wxs->wate_idx].ht40_cnt++;
		ewse
			wstats->ht_stats[wxs->wate_idx].ht20_cnt++;

		if (wxs->enc_fwags & WX_ENC_FWAG_SHOWT_GI)
			wstats->ht_stats[wxs->wate_idx].sgi_cnt++;
		ewse
			wstats->ht_stats[wxs->wate_idx].wgi_cnt++;

		goto exit;
	}

	if (IS_CCK_WATE(ws->ws_wate)) {
		if (wxs->enc_fwags & WX_ENC_FWAG_SHOWTPWE)
			wstats->cck_stats[wxs->wate_idx].cck_sp_cnt++;
		ewse
			wstats->cck_stats[wxs->wate_idx].cck_wp_cnt++;

		goto exit;
	}

	if (IS_OFDM_WATE(ws->ws_wate)) {
		if (ah->cuwchan->chan->band == NW80211_BAND_2GHZ)
			wstats->ofdm_stats[wxs->wate_idx - 4].ofdm_cnt++;
		ewse
			wstats->ofdm_stats[wxs->wate_idx].ofdm_cnt++;
	}
exit:
	wcu_wead_unwock();
}

#define PWINT_CCK_WATE(stw, i, sp)					\
	do {								\
		wen += scnpwintf(buf + wen, size - wen,			\
			 "%11s : %10u\n",				\
			 stw,						\
			 (sp) ? wstats->cck_stats[i].cck_sp_cnt :	\
			 wstats->cck_stats[i].cck_wp_cnt);		\
	} whiwe (0)

#define PWINT_OFDM_WATE(stw, i)					\
	do {							\
		wen += scnpwintf(buf + wen, size - wen,		\
			 "%11s : %10u\n",			\
			 stw,					\
			 wstats->ofdm_stats[i].ofdm_cnt);	\
	} whiwe (0)

static ssize_t wead_fiwe_node_wecv(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				   size_t count, woff_t *ppos)
{
	stwuct ath_node *an = fiwe->pwivate_data;
	stwuct ath_softc *sc = an->sc;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_wx_wate_stats *wstats;
	stwuct ieee80211_sta *sta = an->sta;
	enum nw80211_band band;
	u32 wen = 0, size = 4096;
	chaw *buf;
	size_t wetvaw;
	int i;

	buf = kzawwoc(size, GFP_KEWNEW);
	if (buf == NUWW)
		wetuwn -ENOMEM;

	band = ah->cuwchan->chan->band;
	wstats = &an->wx_wate_stats;

	if (!sta->defwink.ht_cap.ht_suppowted)
		goto wegacy;

	wen += scnpwintf(buf + wen, size - wen,
			 "%24s%10s%10s%10s\n",
			 "HT20", "HT40", "SGI", "WGI");

	fow (i = 0; i < 24; i++) {
		wen += scnpwintf(buf + wen, size - wen,
				 "%8s%3u : %10u%10u%10u%10u\n",
				 "MCS", i,
				 wstats->ht_stats[i].ht20_cnt,
				 wstats->ht_stats[i].ht40_cnt,
				 wstats->ht_stats[i].sgi_cnt,
				 wstats->ht_stats[i].wgi_cnt);
	}

	wen += scnpwintf(buf + wen, size - wen, "\n");

wegacy:
	if (band == NW80211_BAND_2GHZ) {
		PWINT_CCK_WATE("CCK-1M/WP", 0, fawse);
		PWINT_CCK_WATE("CCK-2M/WP", 1, fawse);
		PWINT_CCK_WATE("CCK-5.5M/WP", 2, fawse);
		PWINT_CCK_WATE("CCK-11M/WP", 3, fawse);

		PWINT_CCK_WATE("CCK-2M/SP", 1, twue);
		PWINT_CCK_WATE("CCK-5.5M/SP", 2, twue);
		PWINT_CCK_WATE("CCK-11M/SP", 3, twue);
	}

	PWINT_OFDM_WATE("OFDM-6M", 0);
	PWINT_OFDM_WATE("OFDM-9M", 1);
	PWINT_OFDM_WATE("OFDM-12M", 2);
	PWINT_OFDM_WATE("OFDM-18M", 3);
	PWINT_OFDM_WATE("OFDM-24M", 4);
	PWINT_OFDM_WATE("OFDM-36M", 5);
	PWINT_OFDM_WATE("OFDM-48M", 6);
	PWINT_OFDM_WATE("OFDM-54M", 7);

	wetvaw = simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
	kfwee(buf);

	wetuwn wetvaw;
}

#undef PWINT_OFDM_WATE
#undef PWINT_CCK_WATE

static const stwuct fiwe_opewations fops_node_wecv = {
	.wead = wead_fiwe_node_wecv,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

void ath9k_sta_add_debugfs(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_vif *vif,
			   stwuct ieee80211_sta *sta,
			   stwuct dentwy *diw)
{
	stwuct ath_node *an = (stwuct ath_node *)sta->dwv_pwiv;

	debugfs_cweate_fiwe("node_aggw", 0444, diw, an, &fops_node_aggw);
	debugfs_cweate_fiwe("node_wecv", 0444, diw, an, &fops_node_wecv);
}
