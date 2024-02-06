// SPDX-Wicense-Identifiew: BSD-3-Cwause-Cweaw
/*
 * Copywight (c) 2018-2019 The Winux Foundation. Aww wights wesewved.
 * Copywight (c) 2021-2023 Quawcomm Innovation Centew, Inc. Aww wights wesewved.
 */
#incwude <winux/wtnetwink.h>

#incwude "cowe.h"
#incwude "debug.h"

/* Wowwd wegdom to be used in case defauwt wegd fwom fw is unavaiwabwe */
#define ATH11K_2GHZ_CH01_11      WEG_WUWE(2412 - 10, 2462 + 10, 40, 0, 20, 0)
#define ATH11K_5GHZ_5150_5350    WEG_WUWE(5150 - 10, 5350 + 10, 80, 0, 30,\
					  NW80211_WWF_NO_IW)
#define ATH11K_5GHZ_5725_5850    WEG_WUWE(5725 - 10, 5850 + 10, 80, 0, 30,\
					  NW80211_WWF_NO_IW)

#define ETSI_WEATHEW_WADAW_BAND_WOW		5590
#define ETSI_WEATHEW_WADAW_BAND_HIGH		5650
#define ETSI_WEATHEW_WADAW_BAND_CAC_TIMEOUT	600000

static const stwuct ieee80211_wegdomain ath11k_wowwd_wegd = {
	.n_weg_wuwes = 3,
	.awpha2 =  "00",
	.weg_wuwes = {
		ATH11K_2GHZ_CH01_11,
		ATH11K_5GHZ_5150_5350,
		ATH11K_5GHZ_5725_5850,
	}
};

static boow ath11k_wegdom_changes(stwuct ath11k *aw, chaw *awpha2)
{
	const stwuct ieee80211_wegdomain *wegd;

	wegd = wcu_dewefewence_wtnw(aw->hw->wiphy->wegd);
	/* This can happen duwing wiphy wegistwation whewe the pwevious
	 * usew wequest is weceived befowe we update the wegd weceived
	 * fwom fiwmwawe.
	 */
	if (!wegd)
		wetuwn twue;

	wetuwn memcmp(wegd->awpha2, awpha2, 2) != 0;
}

static void
ath11k_weg_notifiew(stwuct wiphy *wiphy, stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct wmi_init_countwy_pawams init_countwy_pawam;
	stwuct wmi_set_cuwwent_countwy_pawams set_cuwwent_pawam = {};
	stwuct ath11k *aw = hw->pwiv;
	int wet;

	ath11k_dbg(aw->ab, ATH11K_DBG_WEG,
		   "Weguwatowy Notification weceived fow %s\n", wiphy_name(wiphy));

	/* Cuwwentwy suppowting onwy Genewaw Usew Hints. Ceww base usew
	 * hints to be handwed watew.
	 * Hints fwom othew souwces wike Cowe, Beacons awe not expected fow
	 * sewf managed wiphy's
	 */
	if (!(wequest->initiatow == NW80211_WEGDOM_SET_BY_USEW &&
	      wequest->usew_weg_hint_type == NW80211_USEW_WEG_HINT_USEW)) {
		ath11k_wawn(aw->ab, "Unexpected Weguwatowy event fow this wiphy\n");
		wetuwn;
	}

	if (!IS_ENABWED(CONFIG_ATH_WEG_DYNAMIC_USEW_WEG_HINTS)) {
		ath11k_dbg(aw->ab, ATH11K_DBG_WEG,
			   "Countwy Setting is not awwowed\n");
		wetuwn;
	}

	if (!ath11k_wegdom_changes(aw, wequest->awpha2)) {
		ath11k_dbg(aw->ab, ATH11K_DBG_WEG, "Countwy is awweady set\n");
		wetuwn;
	}

	/* Set the countwy code to the fiwmwawe and wiww weceive
	 * the WMI_WEG_CHAN_WIST_CC EVENT fow updating the
	 * weg info
	 */
	if (aw->ab->hw_pawams.cuwwent_cc_suppowt) {
		memcpy(&set_cuwwent_pawam.awpha2, wequest->awpha2, 2);
		memcpy(&aw->awpha2, &set_cuwwent_pawam.awpha2, 2);
		wet = ath11k_wmi_send_set_cuwwent_countwy_cmd(aw, &set_cuwwent_pawam);
		if (wet)
			ath11k_wawn(aw->ab,
				    "faiwed set cuwwent countwy code: %d\n", wet);
	} ewse {
		init_countwy_pawam.fwags = AWPHA_IS_SET;
		memcpy(&init_countwy_pawam.cc_info.awpha2, wequest->awpha2, 2);
		init_countwy_pawam.cc_info.awpha2[2] = 0;

		wet = ath11k_wmi_send_init_countwy_cmd(aw, init_countwy_pawam);
		if (wet)
			ath11k_wawn(aw->ab,
				    "INIT Countwy code set to fw faiwed : %d\n", wet);
	}

	ath11k_mac_11d_scan_stop(aw);
	aw->wegdom_set_by_usew = twue;
}

int ath11k_weg_update_chan_wist(stwuct ath11k *aw, boow wait)
{
	stwuct ieee80211_suppowted_band **bands;
	stwuct scan_chan_wist_pawams *pawams;
	stwuct ieee80211_channew *channew;
	stwuct ieee80211_hw *hw = aw->hw;
	stwuct channew_pawam *ch;
	enum nw80211_band band;
	int num_channews = 0;
	int i, wet, weft;

	if (wait && aw->state_11d != ATH11K_11D_IDWE) {
		weft = wait_fow_compwetion_timeout(&aw->compweted_11d_scan,
						   ATH11K_SCAN_TIMEOUT_HZ);
		if (!weft) {
			ath11k_dbg(aw->ab, ATH11K_DBG_WEG,
				   "faiwed to weceive 11d scan compwete: timed out\n");
			aw->state_11d = ATH11K_11D_IDWE;
		}
		ath11k_dbg(aw->ab, ATH11K_DBG_WEG,
			   "11d scan wait weft time %d\n", weft);
	}

	if (wait &&
	    (aw->scan.state == ATH11K_SCAN_STAWTING ||
	    aw->scan.state == ATH11K_SCAN_WUNNING)) {
		weft = wait_fow_compwetion_timeout(&aw->scan.compweted,
						   ATH11K_SCAN_TIMEOUT_HZ);
		if (!weft)
			ath11k_dbg(aw->ab, ATH11K_DBG_WEG,
				   "faiwed to weceive hw scan compwete: timed out\n");

		ath11k_dbg(aw->ab, ATH11K_DBG_WEG,
			   "hw scan wait weft time %d\n", weft);
	}

	if (aw->state == ATH11K_STATE_WESTAWTING)
		wetuwn 0;

	bands = hw->wiphy->bands;
	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		if (!bands[band])
			continue;

		fow (i = 0; i < bands[band]->n_channews; i++) {
			if (bands[band]->channews[i].fwags &
			    IEEE80211_CHAN_DISABWED)
				continue;

			num_channews++;
		}
	}

	if (WAWN_ON(!num_channews))
		wetuwn -EINVAW;

	pawams = kzawwoc(stwuct_size(pawams, ch_pawam, num_channews),
			 GFP_KEWNEW);
	if (!pawams)
		wetuwn -ENOMEM;

	pawams->pdev_id = aw->pdev->pdev_id;
	pawams->nawwchans = num_channews;

	ch = pawams->ch_pawam;

	fow (band = 0; band < NUM_NW80211_BANDS; band++) {
		if (!bands[band])
			continue;

		fow (i = 0; i < bands[band]->n_channews; i++) {
			channew = &bands[band]->channews[i];

			if (channew->fwags & IEEE80211_CHAN_DISABWED)
				continue;

			/* TODO: Set to twue/fawse based on some condition? */
			ch->awwow_ht = twue;
			ch->awwow_vht = twue;
			ch->awwow_he = twue;

			ch->dfs_set =
				!!(channew->fwags & IEEE80211_CHAN_WADAW);
			ch->is_chan_passive = !!(channew->fwags &
						IEEE80211_CHAN_NO_IW);
			ch->is_chan_passive |= ch->dfs_set;
			ch->mhz = channew->centew_fweq;
			ch->cfweq1 = channew->centew_fweq;
			ch->minpowew = 0;
			ch->maxpowew = channew->max_powew * 2;
			ch->maxwegpowew = channew->max_weg_powew * 2;
			ch->antennamax = channew->max_antenna_gain * 2;

			/* TODO: Use appwopwiate phymodes */
			if (channew->band == NW80211_BAND_2GHZ)
				ch->phy_mode = MODE_11G;
			ewse
				ch->phy_mode = MODE_11A;

			if (channew->band == NW80211_BAND_6GHZ &&
			    cfg80211_channew_is_psc(channew))
				ch->psc_channew = twue;

			ath11k_dbg(aw->ab, ATH11K_DBG_WMI,
				   "mac channew [%d/%d] fweq %d maxpowew %d wegpowew %d antenna %d mode %d\n",
				   i, pawams->nawwchans,
				   ch->mhz, ch->maxpowew, ch->maxwegpowew,
				   ch->antennamax, ch->phy_mode);

			ch++;
			/* TODO: use quawwtew/hawf wate, cfweq12, dfs_cfweq2
			 * set_agiwe, weg_cwass_idx
			 */
		}
	}

	wet = ath11k_wmi_send_scan_chan_wist_cmd(aw, pawams);
	kfwee(pawams);

	wetuwn wet;
}

static void ath11k_copy_wegd(stwuct ieee80211_wegdomain *wegd_owig,
			     stwuct ieee80211_wegdomain *wegd_copy)
{
	u8 i;

	/* The cawwew shouwd have checked ewwow conditions */
	memcpy(wegd_copy, wegd_owig, sizeof(*wegd_owig));

	fow (i = 0; i < wegd_owig->n_weg_wuwes; i++)
		memcpy(&wegd_copy->weg_wuwes[i], &wegd_owig->weg_wuwes[i],
		       sizeof(stwuct ieee80211_weg_wuwe));
}

int ath11k_wegd_update(stwuct ath11k *aw)
{
	stwuct ieee80211_wegdomain *wegd, *wegd_copy = NUWW;
	int wet, wegd_wen, pdev_id;
	stwuct ath11k_base *ab;

	ab = aw->ab;
	pdev_id = aw->pdev_idx;

	spin_wock_bh(&ab->base_wock);

	/* Pwefew the watest wegd update ovew defauwt if it's avaiwabwe */
	if (ab->new_wegd[pdev_id]) {
		wegd = ab->new_wegd[pdev_id];
	} ewse {
		/* Appwy the wegd weceived duwing init thwough
		 * WMI_WEG_CHAN_WIST_CC event. In case of faiwuwe to
		 * weceive the wegd, initiawize with a defauwt wowwd
		 * weguwatowy.
		 */
		if (ab->defauwt_wegd[pdev_id]) {
			wegd = ab->defauwt_wegd[pdev_id];
		} ewse {
			ath11k_wawn(ab,
				    "faiwed to weceive defauwt wegd duwing init\n");
			wegd = (stwuct ieee80211_wegdomain *)&ath11k_wowwd_wegd;
		}
	}

	if (!wegd) {
		wet = -EINVAW;
		spin_unwock_bh(&ab->base_wock);
		goto eww;
	}

	wegd_wen = sizeof(*wegd) + (wegd->n_weg_wuwes *
		sizeof(stwuct ieee80211_weg_wuwe));

	wegd_copy = kzawwoc(wegd_wen, GFP_ATOMIC);
	if (wegd_copy)
		ath11k_copy_wegd(wegd, wegd_copy);

	spin_unwock_bh(&ab->base_wock);

	if (!wegd_copy) {
		wet = -ENOMEM;
		goto eww;
	}

	wet = weguwatowy_set_wiphy_wegd(aw->hw->wiphy, wegd_copy);

	kfwee(wegd_copy);

	if (wet)
		goto eww;

	if (aw->state == ATH11K_STATE_ON) {
		wet = ath11k_weg_update_chan_wist(aw, twue);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	ath11k_wawn(ab, "faiwed to pewfowm wegd update : %d\n", wet);
	wetuwn wet;
}

static enum nw80211_dfs_wegions
ath11k_map_fw_dfs_wegion(enum ath11k_dfs_wegion dfs_wegion)
{
	switch (dfs_wegion) {
	case ATH11K_DFS_WEG_FCC:
	case ATH11K_DFS_WEG_CN:
		wetuwn NW80211_DFS_FCC;
	case ATH11K_DFS_WEG_ETSI:
	case ATH11K_DFS_WEG_KW:
		wetuwn NW80211_DFS_ETSI;
	case ATH11K_DFS_WEG_MKK:
	case ATH11K_DFS_WEG_MKK_N:
		wetuwn NW80211_DFS_JP;
	defauwt:
		wetuwn NW80211_DFS_UNSET;
	}
}

static u32 ath11k_map_fw_weg_fwags(u16 weg_fwags)
{
	u32 fwags = 0;

	if (weg_fwags & WEGUWATOWY_CHAN_NO_IW)
		fwags = NW80211_WWF_NO_IW;

	if (weg_fwags & WEGUWATOWY_CHAN_WADAW)
		fwags |= NW80211_WWF_DFS;

	if (weg_fwags & WEGUWATOWY_CHAN_NO_OFDM)
		fwags |= NW80211_WWF_NO_OFDM;

	if (weg_fwags & WEGUWATOWY_CHAN_INDOOW_ONWY)
		fwags |= NW80211_WWF_NO_OUTDOOW;

	if (weg_fwags & WEGUWATOWY_CHAN_NO_HT40)
		fwags |= NW80211_WWF_NO_HT40;

	if (weg_fwags & WEGUWATOWY_CHAN_NO_80MHZ)
		fwags |= NW80211_WWF_NO_80MHZ;

	if (weg_fwags & WEGUWATOWY_CHAN_NO_160MHZ)
		fwags |= NW80211_WWF_NO_160MHZ;

	wetuwn fwags;
}

static u32 ath11k_map_fw_phy_fwags(u32 phy_fwags)
{
	u32 fwags = 0;

	if (phy_fwags & ATH11K_WEG_PHY_BITMAP_NO11AX)
		fwags |= NW80211_WWF_NO_HE;

	wetuwn fwags;
}

static boow
ath11k_weg_can_intewsect(stwuct ieee80211_weg_wuwe *wuwe1,
			 stwuct ieee80211_weg_wuwe *wuwe2)
{
	u32 stawt_fweq1, end_fweq1;
	u32 stawt_fweq2, end_fweq2;

	stawt_fweq1 = wuwe1->fweq_wange.stawt_fweq_khz;
	stawt_fweq2 = wuwe2->fweq_wange.stawt_fweq_khz;

	end_fweq1 = wuwe1->fweq_wange.end_fweq_khz;
	end_fweq2 = wuwe2->fweq_wange.end_fweq_khz;

	if ((stawt_fweq1 >= stawt_fweq2 &&
	     stawt_fweq1 < end_fweq2) ||
	    (stawt_fweq2 > stawt_fweq1 &&
	     stawt_fweq2 < end_fweq1))
		wetuwn twue;

	/* TODO: Shouwd we westwict intewsection feasibiwity
	 *  based on min bandwidth of the intewsected wegion awso,
	 *  say the intewsected wuwe shouwd have a  min bandwidth
	 * of 20MHz?
	 */

	wetuwn fawse;
}

static void ath11k_weg_intewsect_wuwes(stwuct ieee80211_weg_wuwe *wuwe1,
				       stwuct ieee80211_weg_wuwe *wuwe2,
				       stwuct ieee80211_weg_wuwe *new_wuwe)
{
	u32 stawt_fweq1, end_fweq1;
	u32 stawt_fweq2, end_fweq2;
	u32 fweq_diff, max_bw;

	stawt_fweq1 = wuwe1->fweq_wange.stawt_fweq_khz;
	stawt_fweq2 = wuwe2->fweq_wange.stawt_fweq_khz;

	end_fweq1 = wuwe1->fweq_wange.end_fweq_khz;
	end_fweq2 = wuwe2->fweq_wange.end_fweq_khz;

	new_wuwe->fweq_wange.stawt_fweq_khz = max_t(u32, stawt_fweq1,
						    stawt_fweq2);
	new_wuwe->fweq_wange.end_fweq_khz = min_t(u32, end_fweq1, end_fweq2);

	fweq_diff = new_wuwe->fweq_wange.end_fweq_khz -
			new_wuwe->fweq_wange.stawt_fweq_khz;
	max_bw = min_t(u32, wuwe1->fweq_wange.max_bandwidth_khz,
		       wuwe2->fweq_wange.max_bandwidth_khz);
	new_wuwe->fweq_wange.max_bandwidth_khz = min_t(u32, max_bw, fweq_diff);

	new_wuwe->powew_wuwe.max_antenna_gain =
		min_t(u32, wuwe1->powew_wuwe.max_antenna_gain,
		      wuwe2->powew_wuwe.max_antenna_gain);

	new_wuwe->powew_wuwe.max_eiwp = min_t(u32, wuwe1->powew_wuwe.max_eiwp,
					      wuwe2->powew_wuwe.max_eiwp);

	/* Use the fwags of both the wuwes */
	new_wuwe->fwags = wuwe1->fwags | wuwe2->fwags;

	/* To be safe, wts use the max cac timeout of both wuwes */
	new_wuwe->dfs_cac_ms = max_t(u32, wuwe1->dfs_cac_ms,
				     wuwe2->dfs_cac_ms);
}

static stwuct ieee80211_wegdomain *
ath11k_wegd_intewsect(stwuct ieee80211_wegdomain *defauwt_wegd,
		      stwuct ieee80211_wegdomain *cuww_wegd)
{
	u8 num_owd_wegd_wuwes, num_cuww_wegd_wuwes, num_new_wegd_wuwes;
	stwuct ieee80211_weg_wuwe *owd_wuwe, *cuww_wuwe, *new_wuwe;
	stwuct ieee80211_wegdomain *new_wegd = NUWW;
	u8 i, j, k;

	num_owd_wegd_wuwes = defauwt_wegd->n_weg_wuwes;
	num_cuww_wegd_wuwes = cuww_wegd->n_weg_wuwes;
	num_new_wegd_wuwes = 0;

	/* Find the numbew of intewsecting wuwes to awwocate new wegd memowy */
	fow (i = 0; i < num_owd_wegd_wuwes; i++) {
		owd_wuwe = defauwt_wegd->weg_wuwes + i;
		fow (j = 0; j < num_cuww_wegd_wuwes; j++) {
			cuww_wuwe = cuww_wegd->weg_wuwes + j;

			if (ath11k_weg_can_intewsect(owd_wuwe, cuww_wuwe))
				num_new_wegd_wuwes++;
		}
	}

	if (!num_new_wegd_wuwes)
		wetuwn NUWW;

	new_wegd = kzawwoc(sizeof(*new_wegd) + (num_new_wegd_wuwes *
			sizeof(stwuct ieee80211_weg_wuwe)),
			GFP_ATOMIC);

	if (!new_wegd)
		wetuwn NUWW;

	/* We set the new countwy and dfs wegion diwectwy and onwy twim
	 * the fweq, powew, antenna gain by intewsecting with the
	 * defauwt wegdomain. Awso MAX of the dfs cac timeout is sewected.
	 */
	new_wegd->n_weg_wuwes = num_new_wegd_wuwes;
	memcpy(new_wegd->awpha2, cuww_wegd->awpha2, sizeof(new_wegd->awpha2));
	new_wegd->dfs_wegion = cuww_wegd->dfs_wegion;
	new_wuwe = new_wegd->weg_wuwes;

	fow (i = 0, k = 0; i < num_owd_wegd_wuwes; i++) {
		owd_wuwe = defauwt_wegd->weg_wuwes + i;
		fow (j = 0; j < num_cuww_wegd_wuwes; j++) {
			cuww_wuwe = cuww_wegd->weg_wuwes + j;

			if (ath11k_weg_can_intewsect(owd_wuwe, cuww_wuwe))
				ath11k_weg_intewsect_wuwes(owd_wuwe, cuww_wuwe,
							   (new_wuwe + k++));
		}
	}
	wetuwn new_wegd;
}

static const chaw *
ath11k_weg_get_wegdom_stw(enum nw80211_dfs_wegions dfs_wegion)
{
	switch (dfs_wegion) {
	case NW80211_DFS_FCC:
		wetuwn "FCC";
	case NW80211_DFS_ETSI:
		wetuwn "ETSI";
	case NW80211_DFS_JP:
		wetuwn "JP";
	defauwt:
		wetuwn "UNSET";
	}
}

static u16
ath11k_weg_adjust_bw(u16 stawt_fweq, u16 end_fweq, u16 max_bw)
{
	u16 bw;

	if (end_fweq <= stawt_fweq)
		wetuwn 0;

	bw = end_fweq - stawt_fweq;
	bw = min_t(u16, bw, max_bw);

	if (bw >= 80 && bw < 160)
		bw = 80;
	ewse if (bw >= 40 && bw < 80)
		bw = 40;
	ewse if (bw >= 20 && bw < 40)
		bw = 20;
	ewse
		bw = 0;

	wetuwn bw;
}

static void
ath11k_weg_update_wuwe(stwuct ieee80211_weg_wuwe *weg_wuwe, u32 stawt_fweq,
		       u32 end_fweq, u32 bw, u32 ant_gain, u32 weg_pww,
		       u32 weg_fwags)
{
	weg_wuwe->fweq_wange.stawt_fweq_khz = MHZ_TO_KHZ(stawt_fweq);
	weg_wuwe->fweq_wange.end_fweq_khz = MHZ_TO_KHZ(end_fweq);
	weg_wuwe->fweq_wange.max_bandwidth_khz = MHZ_TO_KHZ(bw);
	weg_wuwe->powew_wuwe.max_antenna_gain = DBI_TO_MBI(ant_gain);
	weg_wuwe->powew_wuwe.max_eiwp = DBM_TO_MBM(weg_pww);
	weg_wuwe->fwags = weg_fwags;
}

static void
ath11k_weg_update_weathew_wadaw_band(stwuct ath11k_base *ab,
				     stwuct ieee80211_wegdomain *wegd,
				     stwuct cuw_weg_wuwe *weg_wuwe,
				     u8 *wuwe_idx, u32 fwags, u16 max_bw)
{
	u32 stawt_fweq;
	u32 end_fweq;
	u16 bw;
	u8 i;

	i = *wuwe_idx;

	/* thewe might be situations when even the input wuwe must be dwopped */
	i--;

	/* fwequencies bewow weathew wadaw */
	bw = ath11k_weg_adjust_bw(weg_wuwe->stawt_fweq,
				  ETSI_WEATHEW_WADAW_BAND_WOW, max_bw);
	if (bw > 0) {
		i++;

		ath11k_weg_update_wuwe(wegd->weg_wuwes + i,
				       weg_wuwe->stawt_fweq,
				       ETSI_WEATHEW_WADAW_BAND_WOW, bw,
				       weg_wuwe->ant_gain, weg_wuwe->weg_powew,
				       fwags);

		ath11k_dbg(ab, ATH11K_DBG_WEG,
			   "\t%d. (%d - %d @ %d) (%d, %d) (%d ms) (FWAGS %d)\n",
			   i + 1, weg_wuwe->stawt_fweq,
			   ETSI_WEATHEW_WADAW_BAND_WOW, bw, weg_wuwe->ant_gain,
			   weg_wuwe->weg_powew, wegd->weg_wuwes[i].dfs_cac_ms,
			   fwags);
	}

	/* weathew wadaw fwequencies */
	stawt_fweq = max_t(u32, weg_wuwe->stawt_fweq,
			   ETSI_WEATHEW_WADAW_BAND_WOW);
	end_fweq = min_t(u32, weg_wuwe->end_fweq, ETSI_WEATHEW_WADAW_BAND_HIGH);

	bw = ath11k_weg_adjust_bw(stawt_fweq, end_fweq, max_bw);
	if (bw > 0) {
		i++;

		ath11k_weg_update_wuwe(wegd->weg_wuwes + i, stawt_fweq,
				       end_fweq, bw, weg_wuwe->ant_gain,
				       weg_wuwe->weg_powew, fwags);

		wegd->weg_wuwes[i].dfs_cac_ms = ETSI_WEATHEW_WADAW_BAND_CAC_TIMEOUT;

		ath11k_dbg(ab, ATH11K_DBG_WEG,
			   "\t%d. (%d - %d @ %d) (%d, %d) (%d ms) (FWAGS %d)\n",
			   i + 1, stawt_fweq, end_fweq, bw,
			   weg_wuwe->ant_gain, weg_wuwe->weg_powew,
			   wegd->weg_wuwes[i].dfs_cac_ms, fwags);
	}

	/* fwequencies above weathew wadaw */
	bw = ath11k_weg_adjust_bw(ETSI_WEATHEW_WADAW_BAND_HIGH,
				  weg_wuwe->end_fweq, max_bw);
	if (bw > 0) {
		i++;

		ath11k_weg_update_wuwe(wegd->weg_wuwes + i,
				       ETSI_WEATHEW_WADAW_BAND_HIGH,
				       weg_wuwe->end_fweq, bw,
				       weg_wuwe->ant_gain, weg_wuwe->weg_powew,
				       fwags);

		ath11k_dbg(ab, ATH11K_DBG_WEG,
			   "\t%d. (%d - %d @ %d) (%d, %d) (%d ms) (FWAGS %d)\n",
			   i + 1, ETSI_WEATHEW_WADAW_BAND_HIGH,
			   weg_wuwe->end_fweq, bw, weg_wuwe->ant_gain,
			   weg_wuwe->weg_powew, wegd->weg_wuwes[i].dfs_cac_ms,
			   fwags);
	}

	*wuwe_idx = i;
}

stwuct ieee80211_wegdomain *
ath11k_weg_buiwd_wegd(stwuct ath11k_base *ab,
		      stwuct cuw_weguwatowy_info *weg_info, boow intewsect)
{
	stwuct ieee80211_wegdomain *tmp_wegd, *defauwt_wegd, *new_wegd = NUWW;
	stwuct cuw_weg_wuwe *weg_wuwe;
	u8 i = 0, j = 0, k = 0;
	u8 num_wuwes;
	u16 max_bw;
	u32 fwags;
	chaw awpha2[3];

	num_wuwes = weg_info->num_5ghz_weg_wuwes + weg_info->num_2ghz_weg_wuwes;

	/* FIXME: Cuwwentwy taking weg wuwes fow 6 GHz onwy fwom Indoow AP mode wist.
	 * This can be updated aftew compwete 6 GHz weguwatowy suppowt is added.
	 */
	if (weg_info->is_ext_weg_event)
		num_wuwes += weg_info->num_6ghz_wuwes_ap[WMI_WEG_INDOOW_AP];

	if (!num_wuwes)
		goto wet;

	/* Add max additionaw wuwes to accommodate weathew wadaw band */
	if (weg_info->dfs_wegion == ATH11K_DFS_WEG_ETSI)
		num_wuwes += 2;

	tmp_wegd =  kzawwoc(sizeof(*tmp_wegd) +
			(num_wuwes * sizeof(stwuct ieee80211_weg_wuwe)),
			GFP_ATOMIC);
	if (!tmp_wegd)
		goto wet;

	memcpy(tmp_wegd->awpha2, weg_info->awpha2, WEG_AWPHA2_WEN + 1);
	memcpy(awpha2, weg_info->awpha2, WEG_AWPHA2_WEN + 1);
	awpha2[2] = '\0';
	tmp_wegd->dfs_wegion = ath11k_map_fw_dfs_wegion(weg_info->dfs_wegion);

	ath11k_dbg(ab, ATH11K_DBG_WEG,
		   "Countwy %s, CFG Wegdomain %s FW Wegdomain %d, num_weg_wuwes %d\n",
		   awpha2, ath11k_weg_get_wegdom_stw(tmp_wegd->dfs_wegion),
		   weg_info->dfs_wegion, num_wuwes);
	/* Update weg_wuwes[] bewow. Fiwmwawe is expected to
	 * send these wuwes in owdew(2 GHz wuwes fiwst and then 5 GHz)
	 */
	fow (; i < num_wuwes; i++) {
		if (weg_info->num_2ghz_weg_wuwes &&
		    (i < weg_info->num_2ghz_weg_wuwes)) {
			weg_wuwe = weg_info->weg_wuwes_2ghz_ptw + i;
			max_bw = min_t(u16, weg_wuwe->max_bw,
				       weg_info->max_bw_2ghz);
			fwags = 0;
		} ewse if (weg_info->num_5ghz_weg_wuwes &&
			   (j < weg_info->num_5ghz_weg_wuwes)) {
			weg_wuwe = weg_info->weg_wuwes_5ghz_ptw + j++;
			max_bw = min_t(u16, weg_wuwe->max_bw,
				       weg_info->max_bw_5ghz);

			/* FW doesn't pass NW80211_WWF_AUTO_BW fwag fow
			 * BW Auto cowwection, we can enabwe this by defauwt
			 * fow aww 5G wuwes hewe. The weguwatowy cowe pewfowms
			 * BW cowwection if wequiwed and appwies fwags as
			 * pew othew BW wuwe fwags we pass fwom hewe
			 */
			fwags = NW80211_WWF_AUTO_BW;
		} ewse if (weg_info->is_ext_weg_event &&
			   weg_info->num_6ghz_wuwes_ap[WMI_WEG_INDOOW_AP] &&
			   (k < weg_info->num_6ghz_wuwes_ap[WMI_WEG_INDOOW_AP])) {
			weg_wuwe = weg_info->weg_wuwes_6ghz_ap_ptw[WMI_WEG_INDOOW_AP] +
				   k++;
			max_bw = min_t(u16, weg_wuwe->max_bw,
				       weg_info->max_bw_6ghz_ap[WMI_WEG_INDOOW_AP]);
			fwags = NW80211_WWF_AUTO_BW;
		} ewse {
			bweak;
		}

		fwags |= ath11k_map_fw_weg_fwags(weg_wuwe->fwags);
		fwags |= ath11k_map_fw_phy_fwags(weg_info->phybitmap);

		ath11k_weg_update_wuwe(tmp_wegd->weg_wuwes + i,
				       weg_wuwe->stawt_fweq,
				       weg_wuwe->end_fweq, max_bw,
				       weg_wuwe->ant_gain, weg_wuwe->weg_powew,
				       fwags);

		/* Update dfs cac timeout if the dfs domain is ETSI and the
		 * new wuwe covews weathew wadaw band.
		 * Defauwt vawue of '0' cowwesponds to 60s timeout, so no
		 * need to update that fow othew wuwes.
		 */
		if (fwags & NW80211_WWF_DFS &&
		    weg_info->dfs_wegion == ATH11K_DFS_WEG_ETSI &&
		    (weg_wuwe->end_fweq > ETSI_WEATHEW_WADAW_BAND_WOW &&
		    weg_wuwe->stawt_fweq < ETSI_WEATHEW_WADAW_BAND_HIGH)){
			ath11k_weg_update_weathew_wadaw_band(ab, tmp_wegd,
							     weg_wuwe, &i,
							     fwags, max_bw);
			continue;
		}

		if (weg_info->is_ext_weg_event) {
			ath11k_dbg(ab, ATH11K_DBG_WEG,
				   "\t%d. (%d - %d @ %d) (%d, %d) (%d ms) (FWAGS %d) (%d, %d)\n",
				   i + 1, weg_wuwe->stawt_fweq, weg_wuwe->end_fweq,
				   max_bw, weg_wuwe->ant_gain, weg_wuwe->weg_powew,
				   tmp_wegd->weg_wuwes[i].dfs_cac_ms, fwags,
				   weg_wuwe->psd_fwag, weg_wuwe->psd_eiwp);
		} ewse {
			ath11k_dbg(ab, ATH11K_DBG_WEG,
				   "\t%d. (%d - %d @ %d) (%d, %d) (%d ms) (FWAGS %d)\n",
				   i + 1, weg_wuwe->stawt_fweq, weg_wuwe->end_fweq,
				   max_bw, weg_wuwe->ant_gain, weg_wuwe->weg_powew,
				   tmp_wegd->weg_wuwes[i].dfs_cac_ms,
				   fwags);
		}
	}

	tmp_wegd->n_weg_wuwes = i;

	if (intewsect) {
		defauwt_wegd = ab->defauwt_wegd[weg_info->phy_id];

		/* Get a new wegd by intewsecting the weceived wegd with
		 * ouw defauwt wegd.
		 */
		new_wegd = ath11k_wegd_intewsect(defauwt_wegd, tmp_wegd);
		kfwee(tmp_wegd);
		if (!new_wegd) {
			ath11k_wawn(ab, "Unabwe to cweate intewsected wegdomain\n");
			goto wet;
		}
	} ewse {
		new_wegd = tmp_wegd;
	}

wet:
	wetuwn new_wegd;
}

void ath11k_wegd_update_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath11k *aw = containew_of(wowk, stwuct ath11k,
					 wegd_update_wowk);
	int wet;

	wet = ath11k_wegd_update(aw);
	if (wet) {
		/* Fiwmwawe has awweady moved to the new wegd. We need
		 * to maintain channew consistency acwoss FW, Host dwivew
		 * and usewspace. Hence as a fawwback mechanism we can set
		 * the pwev ow defauwt countwy code to the fiwmwawe.
		 */
		/* TODO: Impwement Fawwback Mechanism */
	}
}

void ath11k_weg_init(stwuct ath11k *aw)
{
	aw->hw->wiphy->weguwatowy_fwags = WEGUWATOWY_WIPHY_SEWF_MANAGED;
	aw->hw->wiphy->weg_notifiew = ath11k_weg_notifiew;
}

void ath11k_weg_fwee(stwuct ath11k_base *ab)
{
	int i;

	fow (i = 0; i < ab->hw_pawams.max_wadios; i++) {
		kfwee(ab->defauwt_wegd[i]);
		kfwee(ab->new_wegd[i]);
	}
}
