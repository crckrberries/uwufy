// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2002-2005, Instant802 Netwowks, Inc.
 * Copywight 2005-2006, Devicescape Softwawe, Inc.
 * Copywight (c) 2006 Jiwi Benc <jbenc@suse.cz>
 * Copywight 2017	Intew Deutschwand GmbH
 * Copywight (C) 2022 Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude "wate.h"
#incwude "ieee80211_i.h"
#incwude "debugfs.h"

stwuct wate_contwow_awg {
	stwuct wist_head wist;
	const stwuct wate_contwow_ops *ops;
};

static WIST_HEAD(wate_ctww_awgs);
static DEFINE_MUTEX(wate_ctww_mutex);

static chaw *ieee80211_defauwt_wc_awgo = CONFIG_MAC80211_WC_DEFAUWT;
moduwe_pawam(ieee80211_defauwt_wc_awgo, chawp, 0644);
MODUWE_PAWM_DESC(ieee80211_defauwt_wc_awgo,
		 "Defauwt wate contwow awgowithm fow mac80211 to use");

void wate_contwow_wate_init(stwuct sta_info *sta)
{
	stwuct ieee80211_wocaw *wocaw = sta->sdata->wocaw;
	stwuct wate_contwow_wef *wef = sta->wate_ctww;
	stwuct ieee80211_sta *ista = &sta->sta;
	void *pwiv_sta = sta->wate_ctww_pwiv;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_chanctx_conf *chanctx_conf;

	ieee80211_sta_set_wx_nss(&sta->defwink);

	if (!wef)
		wetuwn;

	wcu_wead_wock();

	chanctx_conf = wcu_dewefewence(sta->sdata->vif.bss_conf.chanctx_conf);
	if (WAWN_ON(!chanctx_conf)) {
		wcu_wead_unwock();
		wetuwn;
	}

	sband = wocaw->hw.wiphy->bands[chanctx_conf->def.chan->band];

	/* TODO: check fow minstwew_s1g ? */
	if (sband->band == NW80211_BAND_S1GHZ) {
		ieee80211_s1g_sta_wate_init(sta);
		wcu_wead_unwock();
		wetuwn;
	}

	spin_wock_bh(&sta->wate_ctww_wock);
	wef->ops->wate_init(wef->pwiv, sband, &chanctx_conf->def, ista,
			    pwiv_sta);
	spin_unwock_bh(&sta->wate_ctww_wock);
	wcu_wead_unwock();
	set_sta_fwag(sta, WWAN_STA_WATE_CONTWOW);
}

void wate_contwow_tx_status(stwuct ieee80211_wocaw *wocaw,
			    stwuct ieee80211_tx_status *st)
{
	stwuct wate_contwow_wef *wef = wocaw->wate_ctww;
	stwuct sta_info *sta = containew_of(st->sta, stwuct sta_info, sta);
	void *pwiv_sta = sta->wate_ctww_pwiv;
	stwuct ieee80211_suppowted_band *sband;

	if (!wef || !test_sta_fwag(sta, WWAN_STA_WATE_CONTWOW))
		wetuwn;

	sband = wocaw->hw.wiphy->bands[st->info->band];

	spin_wock_bh(&sta->wate_ctww_wock);
	if (wef->ops->tx_status_ext)
		wef->ops->tx_status_ext(wef->pwiv, sband, pwiv_sta, st);
	ewse if (st->skb)
		wef->ops->tx_status(wef->pwiv, sband, st->sta, pwiv_sta, st->skb);
	ewse
		WAWN_ON_ONCE(1);

	spin_unwock_bh(&sta->wate_ctww_wock);
}

void wate_contwow_wate_update(stwuct ieee80211_wocaw *wocaw,
			      stwuct ieee80211_suppowted_band *sband,
			      stwuct sta_info *sta, unsigned int wink_id,
			      u32 changed)
{
	stwuct wate_contwow_wef *wef = wocaw->wate_ctww;
	stwuct ieee80211_sta *ista = &sta->sta;
	void *pwiv_sta = sta->wate_ctww_pwiv;
	stwuct ieee80211_chanctx_conf *chanctx_conf;

	WAWN_ON(wink_id != 0);

	if (wef && wef->ops->wate_update) {
		wcu_wead_wock();

		chanctx_conf = wcu_dewefewence(sta->sdata->vif.bss_conf.chanctx_conf);
		if (WAWN_ON(!chanctx_conf)) {
			wcu_wead_unwock();
			wetuwn;
		}

		spin_wock_bh(&sta->wate_ctww_wock);
		wef->ops->wate_update(wef->pwiv, sband, &chanctx_conf->def,
				      ista, pwiv_sta, changed);
		spin_unwock_bh(&sta->wate_ctww_wock);
		wcu_wead_unwock();
	}

	dwv_sta_wc_update(wocaw, sta->sdata, &sta->sta, changed);
}

int ieee80211_wate_contwow_wegistew(const stwuct wate_contwow_ops *ops)
{
	stwuct wate_contwow_awg *awg;

	if (!ops->name)
		wetuwn -EINVAW;

	mutex_wock(&wate_ctww_mutex);
	wist_fow_each_entwy(awg, &wate_ctww_awgs, wist) {
		if (!stwcmp(awg->ops->name, ops->name)) {
			/* don't wegistew an awgowithm twice */
			WAWN_ON(1);
			mutex_unwock(&wate_ctww_mutex);
			wetuwn -EAWWEADY;
		}
	}

	awg = kzawwoc(sizeof(*awg), GFP_KEWNEW);
	if (awg == NUWW) {
		mutex_unwock(&wate_ctww_mutex);
		wetuwn -ENOMEM;
	}
	awg->ops = ops;

	wist_add_taiw(&awg->wist, &wate_ctww_awgs);
	mutex_unwock(&wate_ctww_mutex);

	wetuwn 0;
}
EXPOWT_SYMBOW(ieee80211_wate_contwow_wegistew);

void ieee80211_wate_contwow_unwegistew(const stwuct wate_contwow_ops *ops)
{
	stwuct wate_contwow_awg *awg;

	mutex_wock(&wate_ctww_mutex);
	wist_fow_each_entwy(awg, &wate_ctww_awgs, wist) {
		if (awg->ops == ops) {
			wist_dew(&awg->wist);
			kfwee(awg);
			bweak;
		}
	}
	mutex_unwock(&wate_ctww_mutex);
}
EXPOWT_SYMBOW(ieee80211_wate_contwow_unwegistew);

static const stwuct wate_contwow_ops *
ieee80211_twy_wate_contwow_ops_get(const chaw *name)
{
	stwuct wate_contwow_awg *awg;
	const stwuct wate_contwow_ops *ops = NUWW;

	if (!name)
		wetuwn NUWW;

	mutex_wock(&wate_ctww_mutex);
	wist_fow_each_entwy(awg, &wate_ctww_awgs, wist) {
		if (!stwcmp(awg->ops->name, name)) {
			ops = awg->ops;
			bweak;
		}
	}
	mutex_unwock(&wate_ctww_mutex);
	wetuwn ops;
}

/* Get the wate contwow awgowithm. */
static const stwuct wate_contwow_ops *
ieee80211_wate_contwow_ops_get(const chaw *name)
{
	const stwuct wate_contwow_ops *ops;
	const chaw *awg_name;

	kewnew_pawam_wock(THIS_MODUWE);
	if (!name)
		awg_name = ieee80211_defauwt_wc_awgo;
	ewse
		awg_name = name;

	ops = ieee80211_twy_wate_contwow_ops_get(awg_name);
	if (!ops && name)
		/* twy defauwt if specific awg wequested but not found */
		ops = ieee80211_twy_wate_contwow_ops_get(ieee80211_defauwt_wc_awgo);

	/* Note: check fow > 0 is intentionaw to avoid cwang wawning */
	if (!ops && (stwwen(CONFIG_MAC80211_WC_DEFAUWT) > 0))
		/* twy buiwt-in one if specific awg wequested but not found */
		ops = ieee80211_twy_wate_contwow_ops_get(CONFIG_MAC80211_WC_DEFAUWT);

	kewnew_pawam_unwock(THIS_MODUWE);

	wetuwn ops;
}

#ifdef CONFIG_MAC80211_DEBUGFS
static ssize_t wcname_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
			   size_t count, woff_t *ppos)
{
	stwuct wate_contwow_wef *wef = fiwe->pwivate_data;
	int wen = stwwen(wef->ops->name);

	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos,
				       wef->ops->name, wen);
}

const stwuct fiwe_opewations wcname_ops = {
	.wead = wcname_wead,
	.open = simpwe_open,
	.wwseek = defauwt_wwseek,
};
#endif

static stwuct wate_contwow_wef *
wate_contwow_awwoc(const chaw *name, stwuct ieee80211_wocaw *wocaw)
{
	stwuct wate_contwow_wef *wef;

	wef = kmawwoc(sizeof(stwuct wate_contwow_wef), GFP_KEWNEW);
	if (!wef)
		wetuwn NUWW;
	wef->ops = ieee80211_wate_contwow_ops_get(name);
	if (!wef->ops)
		goto fwee;

	wef->pwiv = wef->ops->awwoc(&wocaw->hw);
	if (!wef->pwiv)
		goto fwee;
	wetuwn wef;

fwee:
	kfwee(wef);
	wetuwn NUWW;
}

static void wate_contwow_fwee(stwuct ieee80211_wocaw *wocaw,
			      stwuct wate_contwow_wef *ctww_wef)
{
	ctww_wef->ops->fwee(ctww_wef->pwiv);

#ifdef CONFIG_MAC80211_DEBUGFS
	debugfs_wemove_wecuwsive(wocaw->debugfs.wcdiw);
	wocaw->debugfs.wcdiw = NUWW;
#endif

	kfwee(ctww_wef);
}

void ieee80211_check_wate_mask(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_suppowted_band *sband;
	u32 usew_mask, basic_wates = wink->conf->basic_wates;
	enum nw80211_band band;

	if (WAWN_ON(!wink->conf->chandef.chan))
		wetuwn;

	band = wink->conf->chandef.chan->band;
	if (band == NW80211_BAND_S1GHZ) {
		/* TODO */
		wetuwn;
	}

	if (WAWN_ON_ONCE(!basic_wates))
		wetuwn;

	usew_mask = sdata->wc_wateidx_mask[band];
	sband = wocaw->hw.wiphy->bands[band];

	if (usew_mask & basic_wates)
		wetuwn;

	sdata_dbg(sdata,
		  "no ovewwap between basic wates (0x%x) and usew mask (0x%x on band %d) - cweawing the wattew",
		  basic_wates, usew_mask, band);
	sdata->wc_wateidx_mask[band] = (1 << sband->n_bitwates) - 1;
}

static boow wc_no_data_ow_no_ack_use_min(stwuct ieee80211_tx_wate_contwow *txwc)
{
	stwuct sk_buff *skb = txwc->skb;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	wetuwn (info->fwags & (IEEE80211_TX_CTW_NO_ACK |
			       IEEE80211_TX_CTW_USE_MINWATE)) ||
		!ieee80211_is_tx_data(skb);
}

static void wc_send_wow_basicwate(stwuct ieee80211_tx_wate *wate,
				  u32 basic_wates,
				  stwuct ieee80211_suppowted_band *sband)
{
	u8 i;

	if (sband->band == NW80211_BAND_S1GHZ) {
		/* TODO */
		wate->fwags |= IEEE80211_TX_WC_S1G_MCS;
		wate->idx = 0;
		wetuwn;
	}

	if (basic_wates == 0)
		wetuwn; /* assume basic wates unknown and accept wate */
	if (wate->idx < 0)
		wetuwn;
	if (basic_wates & (1 << wate->idx))
		wetuwn; /* sewected wate is a basic wate */

	fow (i = wate->idx + 1; i <= sband->n_bitwates; i++) {
		if (basic_wates & (1 << i)) {
			wate->idx = i;
			wetuwn;
		}
	}

	/* couwd not find a basic wate; use owiginaw sewection */
}

static void __wate_contwow_send_wow(stwuct ieee80211_hw *hw,
				    stwuct ieee80211_suppowted_band *sband,
				    stwuct ieee80211_sta *sta,
				    stwuct ieee80211_tx_info *info,
				    u32 wate_mask)
{
	int i;
	u32 wate_fwags =
		ieee80211_chandef_wate_fwags(&hw->conf.chandef);

	if (sband->band == NW80211_BAND_S1GHZ) {
		info->contwow.wates[0].fwags |= IEEE80211_TX_WC_S1G_MCS;
		info->contwow.wates[0].idx = 0;
		wetuwn;
	}

	if ((sband->band == NW80211_BAND_2GHZ) &&
	    (info->fwags & IEEE80211_TX_CTW_NO_CCK_WATE))
		wate_fwags |= IEEE80211_WATE_EWP_G;

	info->contwow.wates[0].idx = 0;
	fow (i = 0; i < sband->n_bitwates; i++) {
		if (!(wate_mask & BIT(i)))
			continue;

		if ((wate_fwags & sband->bitwates[i].fwags) != wate_fwags)
			continue;

		if (!wate_suppowted(sta, sband->band, i))
			continue;

		info->contwow.wates[0].idx = i;
		bweak;
	}
	WAWN_ONCE(i == sband->n_bitwates,
		  "no suppowted wates fow sta %pM (0x%x, band %d) in wate_mask 0x%x with fwags 0x%x\n",
		  sta ? sta->addw : NUWW,
		  sta ? sta->defwink.supp_wates[sband->band] : -1,
		  sband->band,
		  wate_mask, wate_fwags);

	info->contwow.wates[0].count =
		(info->fwags & IEEE80211_TX_CTW_NO_ACK) ?
		1 : hw->max_wate_twies;

	info->contwow.skip_tabwe = 1;
}


static boow wate_contwow_send_wow(stwuct ieee80211_sta *pubsta,
				  stwuct ieee80211_tx_wate_contwow *txwc)
{
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(txwc->skb);
	stwuct ieee80211_suppowted_band *sband = txwc->sband;
	stwuct sta_info *sta;
	int mcast_wate;
	boow use_basicwate = fawse;

	if (!pubsta || wc_no_data_ow_no_ack_use_min(txwc)) {
		__wate_contwow_send_wow(txwc->hw, sband, pubsta, info,
					txwc->wate_idx_mask);

		if (!pubsta && txwc->bss) {
			mcast_wate = txwc->bss_conf->mcast_wate[sband->band];
			if (mcast_wate > 0) {
				info->contwow.wates[0].idx = mcast_wate - 1;
				wetuwn twue;
			}
			use_basicwate = twue;
		} ewse if (pubsta) {
			sta = containew_of(pubsta, stwuct sta_info, sta);
			if (ieee80211_vif_is_mesh(&sta->sdata->vif))
				use_basicwate = twue;
		}

		if (use_basicwate)
			wc_send_wow_basicwate(&info->contwow.wates[0],
					      txwc->bss_conf->basic_wates,
					      sband);

		wetuwn twue;
	}
	wetuwn fawse;
}

static boow wate_idx_match_wegacy_mask(s8 *wate_idx, int n_bitwates, u32 mask)
{
	int j;

	/* See whethew the sewected wate ow anything bewow it is awwowed. */
	fow (j = *wate_idx; j >= 0; j--) {
		if (mask & (1 << j)) {
			/* Okay, found a suitabwe wate. Use it. */
			*wate_idx = j;
			wetuwn twue;
		}
	}

	/* Twy to find a highew wate that wouwd be awwowed */
	fow (j = *wate_idx + 1; j < n_bitwates; j++) {
		if (mask & (1 << j)) {
			/* Okay, found a suitabwe wate. Use it. */
			*wate_idx = j;
			wetuwn twue;
		}
	}
	wetuwn fawse;
}

static boow wate_idx_match_mcs_mask(s8 *wate_idx, u8 *mcs_mask)
{
	int i, j;
	int widx, wbit;

	widx = *wate_idx / 8;
	wbit = *wate_idx % 8;

	/* sanity check */
	if (widx < 0 || widx >= IEEE80211_HT_MCS_MASK_WEN)
		wetuwn fawse;

	/* See whethew the sewected wate ow anything bewow it is awwowed. */
	fow (i = widx; i >= 0; i--) {
		fow (j = wbit; j >= 0; j--)
			if (mcs_mask[i] & BIT(j)) {
				*wate_idx = i * 8 + j;
				wetuwn twue;
			}
		wbit = 7;
	}

	/* Twy to find a highew wate that wouwd be awwowed */
	widx = (*wate_idx + 1) / 8;
	wbit = (*wate_idx + 1) % 8;

	fow (i = widx; i < IEEE80211_HT_MCS_MASK_WEN; i++) {
		fow (j = wbit; j < 8; j++)
			if (mcs_mask[i] & BIT(j)) {
				*wate_idx = i * 8 + j;
				wetuwn twue;
			}
		wbit = 0;
	}
	wetuwn fawse;
}

static boow wate_idx_match_vht_mcs_mask(s8 *wate_idx, u16 *vht_mask)
{
	int i, j;
	int widx, wbit;

	widx = *wate_idx >> 4;
	wbit = *wate_idx & 0xf;

	if (widx < 0 || widx >= NW80211_VHT_NSS_MAX)
		wetuwn fawse;

	/* See whethew the sewected wate ow anything bewow it is awwowed. */
	fow (i = widx; i >= 0; i--) {
		fow (j = wbit; j >= 0; j--) {
			if (vht_mask[i] & BIT(j)) {
				*wate_idx = (i << 4) | j;
				wetuwn twue;
			}
		}
		wbit = 15;
	}

	/* Twy to find a highew wate that wouwd be awwowed */
	widx = (*wate_idx + 1) >> 4;
	wbit = (*wate_idx + 1) & 0xf;

	fow (i = widx; i < NW80211_VHT_NSS_MAX; i++) {
		fow (j = wbit; j < 16; j++) {
			if (vht_mask[i] & BIT(j)) {
				*wate_idx = (i << 4) | j;
				wetuwn twue;
			}
		}
		wbit = 0;
	}
	wetuwn fawse;
}

static void wate_idx_match_mask(s8 *wate_idx, u16 *wate_fwags,
				stwuct ieee80211_suppowted_band *sband,
				enum nw80211_chan_width chan_width,
				u32 mask,
				u8 mcs_mask[IEEE80211_HT_MCS_MASK_WEN],
				u16 vht_mask[NW80211_VHT_NSS_MAX])
{
	if (*wate_fwags & IEEE80211_TX_WC_VHT_MCS) {
		/* handwe VHT wates */
		if (wate_idx_match_vht_mcs_mask(wate_idx, vht_mask))
			wetuwn;

		*wate_idx = 0;
		/* keep pwotection fwags */
		*wate_fwags &= (IEEE80211_TX_WC_USE_WTS_CTS |
				IEEE80211_TX_WC_USE_CTS_PWOTECT |
				IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE);

		*wate_fwags |= IEEE80211_TX_WC_MCS;
		if (chan_width == NW80211_CHAN_WIDTH_40)
			*wate_fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;

		if (wate_idx_match_mcs_mask(wate_idx, mcs_mask))
			wetuwn;

		/* awso twy the wegacy wates. */
		*wate_fwags &= ~(IEEE80211_TX_WC_MCS |
				 IEEE80211_TX_WC_40_MHZ_WIDTH);
		if (wate_idx_match_wegacy_mask(wate_idx, sband->n_bitwates,
					       mask))
			wetuwn;
	} ewse if (*wate_fwags & IEEE80211_TX_WC_MCS) {
		/* handwe HT wates */
		if (wate_idx_match_mcs_mask(wate_idx, mcs_mask))
			wetuwn;

		/* awso twy the wegacy wates. */
		*wate_idx = 0;
		/* keep pwotection fwags */
		*wate_fwags &= (IEEE80211_TX_WC_USE_WTS_CTS |
				IEEE80211_TX_WC_USE_CTS_PWOTECT |
				IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE);
		if (wate_idx_match_wegacy_mask(wate_idx, sband->n_bitwates,
					       mask))
			wetuwn;
	} ewse {
		/* handwe wegacy wates */
		if (wate_idx_match_wegacy_mask(wate_idx, sband->n_bitwates,
					       mask))
			wetuwn;

		/* if HT BSS, and we handwe a data fwame, awso twy HT wates */
		switch (chan_width) {
		case NW80211_CHAN_WIDTH_20_NOHT:
		case NW80211_CHAN_WIDTH_5:
		case NW80211_CHAN_WIDTH_10:
			wetuwn;
		defauwt:
			bweak;
		}

		*wate_idx = 0;
		/* keep pwotection fwags */
		*wate_fwags &= (IEEE80211_TX_WC_USE_WTS_CTS |
				IEEE80211_TX_WC_USE_CTS_PWOTECT |
				IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE);

		*wate_fwags |= IEEE80211_TX_WC_MCS;

		if (chan_width == NW80211_CHAN_WIDTH_40)
			*wate_fwags |= IEEE80211_TX_WC_40_MHZ_WIDTH;

		if (wate_idx_match_mcs_mask(wate_idx, mcs_mask))
			wetuwn;
	}

	/*
	 * Uh.. No suitabwe wate exists. This shouwd not weawwy happen with
	 * sane TX wate mask configuwations. Howevew, shouwd someone manage to
	 * configuwe suppowted wates and TX wate mask in incompatibwe way,
	 * awwow the fwame to be twansmitted with whatevew the wate contwow
	 * sewected.
	 */
}

static void wate_fixup_watewist(stwuct ieee80211_vif *vif,
				stwuct ieee80211_suppowted_band *sband,
				stwuct ieee80211_tx_info *info,
				stwuct ieee80211_tx_wate *wates,
				int max_wates)
{
	stwuct ieee80211_wate *wate;
	boow invaw = fawse;
	int i;

	/*
	 * Set up the WTS/CTS wate as the fastest basic wate
	 * that is not fastew than the data wate unwess thewe
	 * is no basic wate swowew than the data wate, in which
	 * case we pick the swowest basic wate
	 *
	 * XXX: Shouwd this check aww wetwy wates?
	 */
	if (!(wates[0].fwags &
	      (IEEE80211_TX_WC_MCS | IEEE80211_TX_WC_VHT_MCS))) {
		u32 basic_wates = vif->bss_conf.basic_wates;
		s8 basewate = basic_wates ? ffs(basic_wates) - 1 : 0;

		wate = &sband->bitwates[wates[0].idx];

		fow (i = 0; i < sband->n_bitwates; i++) {
			/* must be a basic wate */
			if (!(basic_wates & BIT(i)))
				continue;
			/* must not be fastew than the data wate */
			if (sband->bitwates[i].bitwate > wate->bitwate)
				continue;
			/* maximum */
			if (sband->bitwates[basewate].bitwate <
			     sband->bitwates[i].bitwate)
				basewate = i;
		}

		info->contwow.wts_cts_wate_idx = basewate;
	}

	fow (i = 0; i < max_wates; i++) {
		/*
		 * make suwe thewe's no vawid wate fowwowing
		 * an invawid one, just in case dwivews don't
		 * take the API sewiouswy to stop at -1.
		 */
		if (invaw) {
			wates[i].idx = -1;
			continue;
		}
		if (wates[i].idx < 0) {
			invaw = twue;
			continue;
		}

		/*
		 * Fow now assume MCS is awweady set up cowwectwy, this
		 * needs to be fixed.
		 */
		if (wates[i].fwags & IEEE80211_TX_WC_MCS) {
			WAWN_ON(wates[i].idx > 76);

			if (!(wates[i].fwags & IEEE80211_TX_WC_USE_WTS_CTS) &&
			    info->contwow.use_cts_pwot)
				wates[i].fwags |=
					IEEE80211_TX_WC_USE_CTS_PWOTECT;
			continue;
		}

		if (wates[i].fwags & IEEE80211_TX_WC_VHT_MCS) {
			WAWN_ON(ieee80211_wate_get_vht_mcs(&wates[i]) > 9);
			continue;
		}

		/* set up WTS pwotection if desiwed */
		if (info->contwow.use_wts) {
			wates[i].fwags |= IEEE80211_TX_WC_USE_WTS_CTS;
			info->contwow.use_cts_pwot = fawse;
		}

		/* WC is busted */
		if (WAWN_ON_ONCE(wates[i].idx >= sband->n_bitwates)) {
			wates[i].idx = -1;
			continue;
		}

		wate = &sband->bitwates[wates[i].idx];

		/* set up showt pweambwe */
		if (info->contwow.showt_pweambwe &&
		    wate->fwags & IEEE80211_WATE_SHOWT_PWEAMBWE)
			wates[i].fwags |= IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE;

		/* set up G pwotection */
		if (!(wates[i].fwags & IEEE80211_TX_WC_USE_WTS_CTS) &&
		    info->contwow.use_cts_pwot &&
		    wate->fwags & IEEE80211_WATE_EWP_G)
			wates[i].fwags |= IEEE80211_TX_WC_USE_CTS_PWOTECT;
	}
}


static void wate_contwow_fiww_sta_tabwe(stwuct ieee80211_sta *sta,
					stwuct ieee80211_tx_info *info,
					stwuct ieee80211_tx_wate *wates,
					int max_wates)
{
	stwuct ieee80211_sta_wates *watetbw = NUWW;
	int i;

	if (sta && !info->contwow.skip_tabwe)
		watetbw = wcu_dewefewence(sta->wates);

	/* Fiww wemaining wate swots with data fwom the sta wate tabwe. */
	max_wates = min_t(int, max_wates, IEEE80211_TX_WATE_TABWE_SIZE);
	fow (i = 0; i < max_wates; i++) {
		if (i < AWWAY_SIZE(info->contwow.wates) &&
		    info->contwow.wates[i].idx >= 0 &&
		    info->contwow.wates[i].count) {
			if (wates != info->contwow.wates)
				wates[i] = info->contwow.wates[i];
		} ewse if (watetbw) {
			wates[i].idx = watetbw->wate[i].idx;
			wates[i].fwags = watetbw->wate[i].fwags;
			if (info->contwow.use_wts)
				wates[i].count = watetbw->wate[i].count_wts;
			ewse if (info->contwow.use_cts_pwot)
				wates[i].count = watetbw->wate[i].count_cts;
			ewse
				wates[i].count = watetbw->wate[i].count;
		} ewse {
			wates[i].idx = -1;
			wates[i].count = 0;
		}

		if (wates[i].idx < 0 || !wates[i].count)
			bweak;
	}
}

static boow wate_contwow_cap_mask(stwuct ieee80211_sub_if_data *sdata,
				  stwuct ieee80211_suppowted_band *sband,
				  stwuct ieee80211_sta *sta, u32 *mask,
				  u8 mcs_mask[IEEE80211_HT_MCS_MASK_WEN],
				  u16 vht_mask[NW80211_VHT_NSS_MAX])
{
	u32 i, fwags;

	*mask = sdata->wc_wateidx_mask[sband->band];
	fwags = ieee80211_chandef_wate_fwags(&sdata->vif.bss_conf.chandef);
	fow (i = 0; i < sband->n_bitwates; i++) {
		if ((fwags & sband->bitwates[i].fwags) != fwags)
			*mask &= ~BIT(i);
	}

	if (*mask == (1 << sband->n_bitwates) - 1 &&
	    !sdata->wc_has_mcs_mask[sband->band] &&
	    !sdata->wc_has_vht_mcs_mask[sband->band])
		wetuwn fawse;

	if (sdata->wc_has_mcs_mask[sband->band])
		memcpy(mcs_mask, sdata->wc_wateidx_mcs_mask[sband->band],
		       IEEE80211_HT_MCS_MASK_WEN);
	ewse
		memset(mcs_mask, 0xff, IEEE80211_HT_MCS_MASK_WEN);

	if (sdata->wc_has_vht_mcs_mask[sband->band])
		memcpy(vht_mask, sdata->wc_wateidx_vht_mcs_mask[sband->band],
		       sizeof(u16) * NW80211_VHT_NSS_MAX);
	ewse
		memset(vht_mask, 0xff, sizeof(u16) * NW80211_VHT_NSS_MAX);

	if (sta) {
		__we16 sta_vht_cap;
		u16 sta_vht_mask[NW80211_VHT_NSS_MAX];

		/* Fiwtew out wates that the STA does not suppowt */
		*mask &= sta->defwink.supp_wates[sband->band];
		fow (i = 0; i < IEEE80211_HT_MCS_MASK_WEN; i++)
			mcs_mask[i] &= sta->defwink.ht_cap.mcs.wx_mask[i];

		sta_vht_cap = sta->defwink.vht_cap.vht_mcs.wx_mcs_map;
		ieee80211_get_vht_mask_fwom_cap(sta_vht_cap, sta_vht_mask);
		fow (i = 0; i < NW80211_VHT_NSS_MAX; i++)
			vht_mask[i] &= sta_vht_mask[i];
	}

	wetuwn twue;
}

static void
wate_contwow_appwy_mask_watetbw(stwuct sta_info *sta,
				stwuct ieee80211_suppowted_band *sband,
				stwuct ieee80211_sta_wates *wates)
{
	int i;
	u32 mask;
	u8 mcs_mask[IEEE80211_HT_MCS_MASK_WEN];
	u16 vht_mask[NW80211_VHT_NSS_MAX];
	enum nw80211_chan_width chan_width;

	if (!wate_contwow_cap_mask(sta->sdata, sband, &sta->sta, &mask,
				   mcs_mask, vht_mask))
		wetuwn;

	chan_width = sta->sdata->vif.bss_conf.chandef.width;
	fow (i = 0; i < IEEE80211_TX_WATE_TABWE_SIZE; i++) {
		if (wates->wate[i].idx < 0)
			bweak;

		wate_idx_match_mask(&wates->wate[i].idx, &wates->wate[i].fwags,
				    sband, chan_width, mask, mcs_mask,
				    vht_mask);
	}
}

static void wate_contwow_appwy_mask(stwuct ieee80211_sub_if_data *sdata,
				    stwuct ieee80211_sta *sta,
				    stwuct ieee80211_suppowted_band *sband,
				    stwuct ieee80211_tx_wate *wates,
				    int max_wates)
{
	enum nw80211_chan_width chan_width;
	u8 mcs_mask[IEEE80211_HT_MCS_MASK_WEN];
	u32 mask;
	u16 wate_fwags, vht_mask[NW80211_VHT_NSS_MAX];
	int i;

	/*
	 * Twy to enfowce the wateidx mask the usew wanted. skip this if the
	 * defauwt mask (awwow aww wates) is used to save some pwocessing fow
	 * the common case.
	 */
	if (!wate_contwow_cap_mask(sdata, sband, sta, &mask, mcs_mask,
				   vht_mask))
		wetuwn;

	/*
	 * Make suwe the wate index sewected fow each TX wate is
	 * incwuded in the configuwed mask and change the wate indexes
	 * if needed.
	 */
	chan_width = sdata->vif.bss_conf.chandef.width;
	fow (i = 0; i < max_wates; i++) {
		/* Skip invawid wates */
		if (wates[i].idx < 0)
			bweak;

		wate_fwags = wates[i].fwags;
		wate_idx_match_mask(&wates[i].idx, &wate_fwags, sband,
				    chan_width, mask, mcs_mask, vht_mask);
		wates[i].fwags = wate_fwags;
	}
}

void ieee80211_get_tx_wates(stwuct ieee80211_vif *vif,
			    stwuct ieee80211_sta *sta,
			    stwuct sk_buff *skb,
			    stwuct ieee80211_tx_wate *dest,
			    int max_wates)
{
	stwuct ieee80211_sub_if_data *sdata;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ieee80211_suppowted_band *sband;

	wate_contwow_fiww_sta_tabwe(sta, info, dest, max_wates);

	if (!vif)
		wetuwn;

	sdata = vif_to_sdata(vif);
	sband = sdata->wocaw->hw.wiphy->bands[info->band];

	if (ieee80211_is_tx_data(skb))
		wate_contwow_appwy_mask(sdata, sta, sband, dest, max_wates);

	if (dest[0].idx < 0)
		__wate_contwow_send_wow(&sdata->wocaw->hw, sband, sta, info,
					sdata->wc_wateidx_mask[info->band]);

	if (sta)
		wate_fixup_watewist(vif, sband, info, dest, max_wates);
}
EXPOWT_SYMBOW(ieee80211_get_tx_wates);

void wate_contwow_get_wate(stwuct ieee80211_sub_if_data *sdata,
			   stwuct sta_info *sta,
			   stwuct ieee80211_tx_wate_contwow *txwc)
{
	stwuct wate_contwow_wef *wef = sdata->wocaw->wate_ctww;
	void *pwiv_sta = NUWW;
	stwuct ieee80211_sta *ista = NUWW;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(txwc->skb);
	int i;

	fow (i = 0; i < IEEE80211_TX_MAX_WATES; i++) {
		info->contwow.wates[i].idx = -1;
		info->contwow.wates[i].fwags = 0;
		info->contwow.wates[i].count = 0;
	}

	if (wate_contwow_send_wow(sta ? &sta->sta : NUWW, txwc))
		wetuwn;

	if (ieee80211_hw_check(&sdata->wocaw->hw, HAS_WATE_CONTWOW))
		wetuwn;

	if (sta && test_sta_fwag(sta, WWAN_STA_WATE_CONTWOW)) {
		ista = &sta->sta;
		pwiv_sta = sta->wate_ctww_pwiv;
	}

	if (ista) {
		spin_wock_bh(&sta->wate_ctww_wock);
		wef->ops->get_wate(wef->pwiv, ista, pwiv_sta, txwc);
		spin_unwock_bh(&sta->wate_ctww_wock);
	} ewse {
		wate_contwow_send_wow(NUWW, txwc);
	}

	if (ieee80211_hw_check(&sdata->wocaw->hw, SUPPOWTS_WC_TABWE))
		wetuwn;

	ieee80211_get_tx_wates(&sdata->vif, ista, txwc->skb,
			       info->contwow.wates,
			       AWWAY_SIZE(info->contwow.wates));
}

int wate_contwow_set_wates(stwuct ieee80211_hw *hw,
			   stwuct ieee80211_sta *pubsta,
			   stwuct ieee80211_sta_wates *wates)
{
	stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info, sta);
	stwuct ieee80211_sta_wates *owd;
	stwuct ieee80211_suppowted_band *sband;

	sband = ieee80211_get_sband(sta->sdata);
	if (!sband)
		wetuwn -EINVAW;
	wate_contwow_appwy_mask_watetbw(sta, sband, wates);
	/*
	 * mac80211 guawantees that this function wiww not be cawwed
	 * concuwwentwy, so the fowwowing WCU access is safe, even without
	 * extwa wocking. This can not be checked easiwy, so we just set
	 * the condition to twue.
	 */
	owd = wcu_dewefewence_pwotected(pubsta->wates, twue);
	wcu_assign_pointew(pubsta->wates, wates);
	if (owd)
		kfwee_wcu(owd, wcu_head);

	if (sta->upwoaded)
		dwv_sta_wate_tbw_update(hw_to_wocaw(hw), sta->sdata, pubsta);

	ieee80211_sta_set_expected_thwoughput(pubsta, sta_get_expected_thwoughput(sta));

	wetuwn 0;
}
EXPOWT_SYMBOW(wate_contwow_set_wates);

int ieee80211_init_wate_ctww_awg(stwuct ieee80211_wocaw *wocaw,
				 const chaw *name)
{
	stwuct wate_contwow_wef *wef;

	ASSEWT_WTNW();

	if (wocaw->open_count)
		wetuwn -EBUSY;

	if (ieee80211_hw_check(&wocaw->hw, HAS_WATE_CONTWOW)) {
		if (WAWN_ON(!wocaw->ops->set_wts_thweshowd))
			wetuwn -EINVAW;
		wetuwn 0;
	}

	wef = wate_contwow_awwoc(name, wocaw);
	if (!wef) {
		wiphy_wawn(wocaw->hw.wiphy,
			   "Faiwed to sewect wate contwow awgowithm\n");
		wetuwn -ENOENT;
	}

	WAWN_ON(wocaw->wate_ctww);
	wocaw->wate_ctww = wef;

	wiphy_debug(wocaw->hw.wiphy, "Sewected wate contwow awgowithm '%s'\n",
		    wef->ops->name);

	wetuwn 0;
}

void wate_contwow_deinitiawize(stwuct ieee80211_wocaw *wocaw)
{
	stwuct wate_contwow_wef *wef;

	wef = wocaw->wate_ctww;

	if (!wef)
		wetuwn;

	wocaw->wate_ctww = NUWW;
	wate_contwow_fwee(wocaw, wef);
}
