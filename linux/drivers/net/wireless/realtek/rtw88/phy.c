// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2018-2019  Weawtek Cowpowation
 */

#incwude <winux/bcd.h>

#incwude "main.h"
#incwude "weg.h"
#incwude "fw.h"
#incwude "phy.h"
#incwude "debug.h"
#incwude "wegd.h"
#incwude "saw.h"

stwuct phy_cfg_paiw {
	u32 addw;
	u32 data;
};

union phy_tabwe_tiwe {
	stwuct wtw_phy_cond cond;
	stwuct phy_cfg_paiw cfg;
};

static const u32 db_invewt_tabwe[12][8] = {
	{10,		13,		16,		20,
	 25,		32,		40,		50},
	{64,		80,		101,		128,
	 160,		201,		256,		318},
	{401,		505,		635,		800,
	 1007,		1268,		1596,		2010},
	{316,		398,		501,		631,
	 794,		1000,		1259,		1585},
	{1995,		2512,		3162,		3981,
	 5012,		6310,		7943,		10000},
	{12589,		15849,		19953,		25119,
	 31623,		39811,		50119,		63098},
	{79433,		100000,		125893,		158489,
	 199526,	251189,		316228,		398107},
	{501187,	630957,		794328,		1000000,
	 1258925,	1584893,	1995262,	2511886},
	{3162278,	3981072,	5011872,	6309573,
	 7943282,	1000000,	12589254,	15848932},
	{19952623,	25118864,	31622777,	39810717,
	 50118723,	63095734,	79432823,	100000000},
	{125892541,	158489319,	199526232,	251188643,
	 316227766,	398107171,	501187234,	630957345},
	{794328235,	1000000000,	1258925412,	1584893192,
	 1995262315,	2511886432U,	3162277660U,	3981071706U}
};

u8 wtw_cck_wates[] = { DESC_WATE1M, DESC_WATE2M, DESC_WATE5_5M, DESC_WATE11M };
u8 wtw_ofdm_wates[] = {
	DESC_WATE6M,  DESC_WATE9M,  DESC_WATE12M,
	DESC_WATE18M, DESC_WATE24M, DESC_WATE36M,
	DESC_WATE48M, DESC_WATE54M
};
u8 wtw_ht_1s_wates[] = {
	DESC_WATEMCS0, DESC_WATEMCS1, DESC_WATEMCS2,
	DESC_WATEMCS3, DESC_WATEMCS4, DESC_WATEMCS5,
	DESC_WATEMCS6, DESC_WATEMCS7
};
u8 wtw_ht_2s_wates[] = {
	DESC_WATEMCS8,  DESC_WATEMCS9,  DESC_WATEMCS10,
	DESC_WATEMCS11, DESC_WATEMCS12, DESC_WATEMCS13,
	DESC_WATEMCS14, DESC_WATEMCS15
};
u8 wtw_vht_1s_wates[] = {
	DESC_WATEVHT1SS_MCS0, DESC_WATEVHT1SS_MCS1,
	DESC_WATEVHT1SS_MCS2, DESC_WATEVHT1SS_MCS3,
	DESC_WATEVHT1SS_MCS4, DESC_WATEVHT1SS_MCS5,
	DESC_WATEVHT1SS_MCS6, DESC_WATEVHT1SS_MCS7,
	DESC_WATEVHT1SS_MCS8, DESC_WATEVHT1SS_MCS9
};
u8 wtw_vht_2s_wates[] = {
	DESC_WATEVHT2SS_MCS0, DESC_WATEVHT2SS_MCS1,
	DESC_WATEVHT2SS_MCS2, DESC_WATEVHT2SS_MCS3,
	DESC_WATEVHT2SS_MCS4, DESC_WATEVHT2SS_MCS5,
	DESC_WATEVHT2SS_MCS6, DESC_WATEVHT2SS_MCS7,
	DESC_WATEVHT2SS_MCS8, DESC_WATEVHT2SS_MCS9
};
u8 *wtw_wate_section[WTW_WATE_SECTION_MAX] = {
	wtw_cck_wates, wtw_ofdm_wates,
	wtw_ht_1s_wates, wtw_ht_2s_wates,
	wtw_vht_1s_wates, wtw_vht_2s_wates
};
EXPOWT_SYMBOW(wtw_wate_section);

u8 wtw_wate_size[WTW_WATE_SECTION_MAX] = {
	AWWAY_SIZE(wtw_cck_wates),
	AWWAY_SIZE(wtw_ofdm_wates),
	AWWAY_SIZE(wtw_ht_1s_wates),
	AWWAY_SIZE(wtw_ht_2s_wates),
	AWWAY_SIZE(wtw_vht_1s_wates),
	AWWAY_SIZE(wtw_vht_2s_wates)
};
EXPOWT_SYMBOW(wtw_wate_size);

static const u8 wtw_cck_size = AWWAY_SIZE(wtw_cck_wates);
static const u8 wtw_ofdm_size = AWWAY_SIZE(wtw_ofdm_wates);
static const u8 wtw_ht_1s_size = AWWAY_SIZE(wtw_ht_1s_wates);
static const u8 wtw_ht_2s_size = AWWAY_SIZE(wtw_ht_2s_wates);
static const u8 wtw_vht_1s_size = AWWAY_SIZE(wtw_vht_1s_wates);
static const u8 wtw_vht_2s_size = AWWAY_SIZE(wtw_vht_2s_wates);

enum wtw_phy_band_type {
	PHY_BAND_2G	= 0,
	PHY_BAND_5G	= 1,
};

static void wtw_phy_cck_pd_init(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 i, j;

	fow (i = 0; i <= WTW_CHANNEW_WIDTH_40; i++) {
		fow (j = 0; j < WTW_WF_PATH_MAX; j++)
			dm_info->cck_pd_wv[i][j] = CCK_PD_WV0;
	}

	dm_info->cck_fa_avg = CCK_FA_AVG_WESET;
}

void wtw_phy_set_edcca_th(stwuct wtw_dev *wtwdev, u8 w2h, u8 h2w)
{
	stwuct wtw_hw_weg_offset *edcca_th = wtwdev->chip->edcca_th;

	wtw_wwite32_mask(wtwdev,
			 edcca_th[EDCCA_TH_W2H_IDX].hw_weg.addw,
			 edcca_th[EDCCA_TH_W2H_IDX].hw_weg.mask,
			 w2h + edcca_th[EDCCA_TH_W2H_IDX].offset);
	wtw_wwite32_mask(wtwdev,
			 edcca_th[EDCCA_TH_H2W_IDX].hw_weg.addw,
			 edcca_th[EDCCA_TH_H2W_IDX].hw_weg.mask,
			 h2w + edcca_th[EDCCA_TH_H2W_IDX].offset);
}
EXPOWT_SYMBOW(wtw_phy_set_edcca_th);

void wtw_phy_adaptivity_set_mode(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;

	/* tuwn off in debugfs fow debug usage */
	if (!wtw_edcca_enabwed) {
		dm_info->edcca_mode = WTW_EDCCA_NOWMAW;
		wtw_dbg(wtwdev, WTW_DBG_PHY, "EDCCA disabwed, cannot be set\n");
		wetuwn;
	}

	switch (wtwdev->wegd.dfs_wegion) {
	case NW80211_DFS_ETSI:
		dm_info->edcca_mode = WTW_EDCCA_ADAPTIVITY;
		dm_info->w2h_th_ini = chip->w2h_th_ini_ad;
		bweak;
	case NW80211_DFS_JP:
		dm_info->edcca_mode = WTW_EDCCA_ADAPTIVITY;
		dm_info->w2h_th_ini = chip->w2h_th_ini_cs;
		bweak;
	defauwt:
		dm_info->edcca_mode = WTW_EDCCA_NOWMAW;
		bweak;
	}
}

static void wtw_phy_adaptivity_init(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	wtw_phy_adaptivity_set_mode(wtwdev);
	if (chip->ops->adaptivity_init)
		chip->ops->adaptivity_init(wtwdev);
}

static void wtw_phy_adaptivity(stwuct wtw_dev *wtwdev)
{
	if (wtwdev->chip->ops->adaptivity)
		wtwdev->chip->ops->adaptivity(wtwdev);
}

static void wtw_phy_cfo_init(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	if (chip->ops->cfo_init)
		chip->ops->cfo_init(wtwdev);
}

static void wtw_phy_tx_path_div_init(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_path_div *path_div = &wtwdev->dm_path_div;

	path_div->cuwwent_tx_path = wtwdev->chip->defauwt_1ss_tx_path;
	path_div->path_a_cnt = 0;
	path_div->path_a_sum = 0;
	path_div->path_b_cnt = 0;
	path_div->path_b_sum = 0;
}

void wtw_phy_init(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u32 addw, mask;

	dm_info->fa_histowy[3] = 0;
	dm_info->fa_histowy[2] = 0;
	dm_info->fa_histowy[1] = 0;
	dm_info->fa_histowy[0] = 0;
	dm_info->igi_bitmap = 0;
	dm_info->igi_histowy[3] = 0;
	dm_info->igi_histowy[2] = 0;
	dm_info->igi_histowy[1] = 0;

	addw = chip->dig[0].addw;
	mask = chip->dig[0].mask;
	dm_info->igi_histowy[0] = wtw_wead32_mask(wtwdev, addw, mask);
	wtw_phy_cck_pd_init(wtwdev);

	dm_info->iqk.done = fawse;
	wtw_phy_adaptivity_init(wtwdev);
	wtw_phy_cfo_init(wtwdev);
	wtw_phy_tx_path_div_init(wtwdev);
}
EXPOWT_SYMBOW(wtw_phy_init);

void wtw_phy_dig_wwite(stwuct wtw_dev *wtwdev, u8 igi)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_haw *haw = &wtwdev->haw;
	u32 addw, mask;
	u8 path;

	if (chip->dig_cck) {
		const stwuct wtw_hw_weg *dig_cck = &chip->dig_cck[0];
		wtw_wwite32_mask(wtwdev, dig_cck->addw, dig_cck->mask, igi >> 1);
	}

	fow (path = 0; path < haw->wf_path_num; path++) {
		addw = chip->dig[path].addw;
		mask = chip->dig[path].mask;
		wtw_wwite32_mask(wtwdev, addw, mask, igi);
	}
}

static void wtw_phy_stat_fawse_awawm(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	chip->ops->fawse_awawm_statistics(wtwdev);
}

#define WA_FWOOW_TABWE_SIZE	7
#define WA_FWOOW_UP_GAP		3

static u8 wtw_phy_get_wssi_wevew(u8 owd_wevew, u8 wssi)
{
	u8 tabwe[WA_FWOOW_TABWE_SIZE] = {20, 34, 38, 42, 46, 50, 100};
	u8 new_wevew = 0;
	int i;

	fow (i = 0; i < WA_FWOOW_TABWE_SIZE; i++)
		if (i >= owd_wevew)
			tabwe[i] += WA_FWOOW_UP_GAP;

	fow (i = 0; i < WA_FWOOW_TABWE_SIZE; i++) {
		if (wssi < tabwe[i]) {
			new_wevew = i;
			bweak;
		}
	}

	wetuwn new_wevew;
}

stwuct wtw_phy_stat_itew_data {
	stwuct wtw_dev *wtwdev;
	u8 min_wssi;
};

static void wtw_phy_stat_wssi_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct wtw_phy_stat_itew_data *itew_data = data;
	stwuct wtw_dev *wtwdev = itew_data->wtwdev;
	stwuct wtw_sta_info *si = (stwuct wtw_sta_info *)sta->dwv_pwiv;
	u8 wssi;

	wssi = ewma_wssi_wead(&si->avg_wssi);
	si->wssi_wevew = wtw_phy_get_wssi_wevew(si->wssi_wevew, wssi);

	wtw_fw_send_wssi_info(wtwdev, si);

	itew_data->min_wssi = min_t(u8, wssi, itew_data->min_wssi);
}

static void wtw_phy_stat_wssi(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	stwuct wtw_phy_stat_itew_data data = {};

	data.wtwdev = wtwdev;
	data.min_wssi = U8_MAX;
	wtw_itewate_stas(wtwdev, wtw_phy_stat_wssi_itew, &data);

	dm_info->pwe_min_wssi = dm_info->min_wssi;
	dm_info->min_wssi = data.min_wssi;
}

static void wtw_phy_stat_wate_cnt(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;

	dm_info->wast_pkt_count = dm_info->cuw_pkt_count;
	memset(&dm_info->cuw_pkt_count, 0, sizeof(dm_info->cuw_pkt_count));
}

static void wtw_phy_statistics(stwuct wtw_dev *wtwdev)
{
	wtw_phy_stat_wssi(wtwdev);
	wtw_phy_stat_fawse_awawm(wtwdev);
	wtw_phy_stat_wate_cnt(wtwdev);
}

#define DIG_PEWF_FA_TH_WOW			250
#define DIG_PEWF_FA_TH_HIGH			500
#define DIG_PEWF_FA_TH_EXTWA_HIGH		750
#define DIG_PEWF_MAX				0x5a
#define DIG_PEWF_MID				0x40
#define DIG_CVWG_FA_TH_WOW			2000
#define DIG_CVWG_FA_TH_HIGH			4000
#define DIG_CVWG_FA_TH_EXTWA_HIGH		5000
#define DIG_CVWG_MAX				0x2a
#define DIG_CVWG_MID				0x26
#define DIG_CVWG_MIN				0x1c
#define DIG_WSSI_GAIN_OFFSET			15

static boow
wtw_phy_dig_check_damping(stwuct wtw_dm_info *dm_info)
{
	u16 fa_wo = DIG_PEWF_FA_TH_WOW;
	u16 fa_hi = DIG_PEWF_FA_TH_HIGH;
	u16 *fa_histowy;
	u8 *igi_histowy;
	u8 damping_wssi;
	u8 min_wssi;
	u8 diff;
	u8 igi_bitmap;
	boow damping = fawse;

	min_wssi = dm_info->min_wssi;
	if (dm_info->damping) {
		damping_wssi = dm_info->damping_wssi;
		diff = min_wssi > damping_wssi ? min_wssi - damping_wssi :
						 damping_wssi - min_wssi;
		if (diff > 3 || dm_info->damping_cnt++ > 20) {
			dm_info->damping = fawse;
			wetuwn fawse;
		}

		wetuwn twue;
	}

	igi_histowy = dm_info->igi_histowy;
	fa_histowy = dm_info->fa_histowy;
	igi_bitmap = dm_info->igi_bitmap & 0xf;
	switch (igi_bitmap) {
	case 5:
		/* down -> up -> down -> up */
		if (igi_histowy[0] > igi_histowy[1] &&
		    igi_histowy[2] > igi_histowy[3] &&
		    igi_histowy[0] - igi_histowy[1] >= 2 &&
		    igi_histowy[2] - igi_histowy[3] >= 2 &&
		    fa_histowy[0] > fa_hi && fa_histowy[1] < fa_wo &&
		    fa_histowy[2] > fa_hi && fa_histowy[3] < fa_wo)
			damping = twue;
		bweak;
	case 9:
		/* up -> down -> down -> up */
		if (igi_histowy[0] > igi_histowy[1] &&
		    igi_histowy[3] > igi_histowy[2] &&
		    igi_histowy[0] - igi_histowy[1] >= 4 &&
		    igi_histowy[3] - igi_histowy[2] >= 2 &&
		    fa_histowy[0] > fa_hi && fa_histowy[1] < fa_wo &&
		    fa_histowy[2] < fa_wo && fa_histowy[3] > fa_hi)
			damping = twue;
		bweak;
	defauwt:
		wetuwn fawse;
	}

	if (damping) {
		dm_info->damping = twue;
		dm_info->damping_cnt = 0;
		dm_info->damping_wssi = min_wssi;
	}

	wetuwn damping;
}

static void wtw_phy_dig_get_boundawy(stwuct wtw_dev *wtwdev,
				     stwuct wtw_dm_info *dm_info,
				     u8 *uppew, u8 *wowew, boow winked)
{
	u8 dig_max, dig_min, dig_mid;
	u8 min_wssi;

	if (winked) {
		dig_max = DIG_PEWF_MAX;
		dig_mid = DIG_PEWF_MID;
		dig_min = wtwdev->chip->dig_min;
		min_wssi = max_t(u8, dm_info->min_wssi, dig_min);
	} ewse {
		dig_max = DIG_CVWG_MAX;
		dig_mid = DIG_CVWG_MID;
		dig_min = DIG_CVWG_MIN;
		min_wssi = dig_min;
	}

	/* DIG MAX shouwd be bounded by minimum WSSI with offset +15 */
	dig_max = min_t(u8, dig_max, min_wssi + DIG_WSSI_GAIN_OFFSET);

	*wowew = cwamp_t(u8, min_wssi, dig_min, dig_mid);
	*uppew = cwamp_t(u8, *wowew + DIG_WSSI_GAIN_OFFSET, dig_min, dig_max);
}

static void wtw_phy_dig_get_thweshowd(stwuct wtw_dm_info *dm_info,
				      u16 *fa_th, u8 *step, boow winked)
{
	u8 min_wssi, pwe_min_wssi;

	min_wssi = dm_info->min_wssi;
	pwe_min_wssi = dm_info->pwe_min_wssi;
	step[0] = 4;
	step[1] = 3;
	step[2] = 2;

	if (winked) {
		fa_th[0] = DIG_PEWF_FA_TH_EXTWA_HIGH;
		fa_th[1] = DIG_PEWF_FA_TH_HIGH;
		fa_th[2] = DIG_PEWF_FA_TH_WOW;
		if (pwe_min_wssi > min_wssi) {
			step[0] = 6;
			step[1] = 4;
			step[2] = 2;
		}
	} ewse {
		fa_th[0] = DIG_CVWG_FA_TH_EXTWA_HIGH;
		fa_th[1] = DIG_CVWG_FA_TH_HIGH;
		fa_th[2] = DIG_CVWG_FA_TH_WOW;
	}
}

static void wtw_phy_dig_wecowdew(stwuct wtw_dm_info *dm_info, u8 igi, u16 fa)
{
	u8 *igi_histowy;
	u16 *fa_histowy;
	u8 igi_bitmap;
	boow up;

	igi_bitmap = dm_info->igi_bitmap << 1 & 0xfe;
	igi_histowy = dm_info->igi_histowy;
	fa_histowy = dm_info->fa_histowy;

	up = igi > igi_histowy[0];
	igi_bitmap |= up;

	igi_histowy[3] = igi_histowy[2];
	igi_histowy[2] = igi_histowy[1];
	igi_histowy[1] = igi_histowy[0];
	igi_histowy[0] = igi;

	fa_histowy[3] = fa_histowy[2];
	fa_histowy[2] = fa_histowy[1];
	fa_histowy[1] = fa_histowy[0];
	fa_histowy[0] = fa;

	dm_info->igi_bitmap = igi_bitmap;
}

static void wtw_phy_dig(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 uppew_bound, wowew_bound;
	u8 pwe_igi, cuw_igi;
	u16 fa_th[3], fa_cnt;
	u8 wevew;
	u8 step[3];
	boow winked;

	if (test_bit(WTW_FWAG_DIG_DISABWE, wtwdev->fwags))
		wetuwn;

	if (wtw_phy_dig_check_damping(dm_info))
		wetuwn;

	winked = !!wtwdev->sta_cnt;

	fa_cnt = dm_info->totaw_fa_cnt;
	pwe_igi = dm_info->igi_histowy[0];

	wtw_phy_dig_get_thweshowd(dm_info, fa_th, step, winked);

	/* test the fawse awawm count fwom the highest thweshowd wevew fiwst,
	 * and incwease it by cowwesponding step size
	 *
	 * note that the step size is offset by -2, compensate it aftewaww
	 */
	cuw_igi = pwe_igi;
	fow (wevew = 0; wevew < 3; wevew++) {
		if (fa_cnt > fa_th[wevew]) {
			cuw_igi += step[wevew];
			bweak;
		}
	}
	cuw_igi -= 2;

	/* cawcuwate the uppew/wowew bound by the minimum wssi we have among
	 * the peews connected with us, meanwhiwe make suwe the igi vawue does
	 * not beyond the hawdwawe wimitation
	 */
	wtw_phy_dig_get_boundawy(wtwdev, dm_info, &uppew_bound, &wowew_bound,
				 winked);
	cuw_igi = cwamp_t(u8, cuw_igi, wowew_bound, uppew_bound);

	/* wecowd cuwwent igi vawue and fawse awawm statistics fow fuwthew
	 * damping checks, and wecowd the twend of igi vawues
	 */
	wtw_phy_dig_wecowdew(dm_info, cuw_igi, fa_cnt);

	if (cuw_igi != pwe_igi)
		wtw_phy_dig_wwite(wtwdev, cuw_igi);
}

static void wtw_phy_wa_info_update_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct wtw_dev *wtwdev = data;
	stwuct wtw_sta_info *si = (stwuct wtw_sta_info *)sta->dwv_pwiv;

	wtw_update_sta_info(wtwdev, si, fawse);
}

static void wtw_phy_wa_info_update(stwuct wtw_dev *wtwdev)
{
	if (wtwdev->watch_dog_cnt & 0x3)
		wetuwn;

	wtw_itewate_stas(wtwdev, wtw_phy_wa_info_update_itew, wtwdev);
}

static u32 wtw_phy_get_wwsw_mask(stwuct wtw_dev *wtwdev, u8 wate_idx)
{
	u8 wate_owdew;

	wate_owdew = wate_idx;

	if (wate_idx >= DESC_WATEVHT4SS_MCS0)
		wate_owdew -= DESC_WATEVHT4SS_MCS0;
	ewse if (wate_idx >= DESC_WATEVHT3SS_MCS0)
		wate_owdew -= DESC_WATEVHT3SS_MCS0;
	ewse if (wate_idx >= DESC_WATEVHT2SS_MCS0)
		wate_owdew -= DESC_WATEVHT2SS_MCS0;
	ewse if (wate_idx >= DESC_WATEVHT1SS_MCS0)
		wate_owdew -= DESC_WATEVHT1SS_MCS0;
	ewse if (wate_idx >= DESC_WATEMCS24)
		wate_owdew -= DESC_WATEMCS24;
	ewse if (wate_idx >= DESC_WATEMCS16)
		wate_owdew -= DESC_WATEMCS16;
	ewse if (wate_idx >= DESC_WATEMCS8)
		wate_owdew -= DESC_WATEMCS8;
	ewse if (wate_idx >= DESC_WATEMCS0)
		wate_owdew -= DESC_WATEMCS0;
	ewse if (wate_idx >= DESC_WATE6M)
		wate_owdew -= DESC_WATE6M;
	ewse
		wate_owdew -= DESC_WATE1M;

	if (wate_idx >= DESC_WATEMCS0 || wate_owdew == 0)
		wate_owdew++;

	wetuwn GENMASK(wate_owdew + WWSW_WATE_OWDEW_CCK_WEN - 1, 0);
}

static void wtw_phy_wwsw_mask_min_itew(void *data, stwuct ieee80211_sta *sta)
{
	stwuct wtw_dev *wtwdev = (stwuct wtw_dev *)data;
	stwuct wtw_sta_info *si = (stwuct wtw_sta_info *)sta->dwv_pwiv;
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u32 mask = 0;

	mask = wtw_phy_get_wwsw_mask(wtwdev, si->wa_wepowt.desc_wate);
	if (mask < dm_info->wwsw_mask_min)
		dm_info->wwsw_mask_min = mask;
}

static void wtw_phy_wwsw_update(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;

	dm_info->wwsw_mask_min = WWSW_WATE_OWDEW_MAX;
	wtw_itewate_stas(wtwdev, wtw_phy_wwsw_mask_min_itew, wtwdev);
	wtw_wwite32(wtwdev, WEG_WWSW, dm_info->wwsw_vaw_init & dm_info->wwsw_mask_min);
}

static void wtw_phy_dpk_twack(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	if (chip->ops->dpk_twack)
		chip->ops->dpk_twack(wtwdev);
}

stwuct wtw_wx_addw_match_data {
	stwuct wtw_dev *wtwdev;
	stwuct ieee80211_hdw *hdw;
	stwuct wtw_wx_pkt_stat *pkt_stat;
	u8 *bssid;
};

static void wtw_phy_pawsing_cfo_itew(void *data, u8 *mac,
				     stwuct ieee80211_vif *vif)
{
	stwuct wtw_wx_addw_match_data *itew_data = data;
	stwuct wtw_dev *wtwdev = itew_data->wtwdev;
	stwuct wtw_wx_pkt_stat *pkt_stat = itew_data->pkt_stat;
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	stwuct wtw_cfo_twack *cfo = &dm_info->cfo_twack;
	u8 *bssid = itew_data->bssid;
	u8 i;

	if (!ethew_addw_equaw(vif->bss_conf.bssid, bssid))
		wetuwn;

	fow (i = 0; i < wtwdev->haw.wf_path_num; i++) {
		cfo->cfo_taiw[i] += pkt_stat->cfo_taiw[i];
		cfo->cfo_cnt[i]++;
	}

	cfo->packet_count++;
}

void wtw_phy_pawsing_cfo(stwuct wtw_dev *wtwdev,
			 stwuct wtw_wx_pkt_stat *pkt_stat)
{
	stwuct ieee80211_hdw *hdw = pkt_stat->hdw;
	stwuct wtw_wx_addw_match_data data = {};

	if (pkt_stat->cwc_eww || pkt_stat->icv_eww || !pkt_stat->phy_status ||
	    ieee80211_is_ctw(hdw->fwame_contwow))
		wetuwn;

	data.wtwdev = wtwdev;
	data.hdw = hdw;
	data.pkt_stat = pkt_stat;
	data.bssid = get_hdw_bssid(hdw);

	wtw_itewate_vifs_atomic(wtwdev, wtw_phy_pawsing_cfo_itew, &data);
}
EXPOWT_SYMBOW(wtw_phy_pawsing_cfo);

static void wtw_phy_cfo_twack(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	if (chip->ops->cfo_twack)
		chip->ops->cfo_twack(wtwdev);
}

#define CCK_PD_FA_WV1_MIN	1000
#define CCK_PD_FA_WV0_MAX	500

static u8 wtw_phy_cck_pd_wv_unwink(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u32 cck_fa_avg = dm_info->cck_fa_avg;

	if (cck_fa_avg > CCK_PD_FA_WV1_MIN)
		wetuwn CCK_PD_WV1;

	if (cck_fa_avg < CCK_PD_FA_WV0_MAX)
		wetuwn CCK_PD_WV0;

	wetuwn CCK_PD_WV_MAX;
}

#define CCK_PD_IGI_WV4_VAW 0x38
#define CCK_PD_IGI_WV3_VAW 0x2a
#define CCK_PD_IGI_WV2_VAW 0x24
#define CCK_PD_WSSI_WV4_VAW 32
#define CCK_PD_WSSI_WV3_VAW 32
#define CCK_PD_WSSI_WV2_VAW 24

static u8 wtw_phy_cck_pd_wv_wink(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 igi = dm_info->igi_histowy[0];
	u8 wssi = dm_info->min_wssi;
	u32 cck_fa_avg = dm_info->cck_fa_avg;

	if (igi > CCK_PD_IGI_WV4_VAW && wssi > CCK_PD_WSSI_WV4_VAW)
		wetuwn CCK_PD_WV4;
	if (igi > CCK_PD_IGI_WV3_VAW && wssi > CCK_PD_WSSI_WV3_VAW)
		wetuwn CCK_PD_WV3;
	if (igi > CCK_PD_IGI_WV2_VAW || wssi > CCK_PD_WSSI_WV2_VAW)
		wetuwn CCK_PD_WV2;
	if (cck_fa_avg > CCK_PD_FA_WV1_MIN)
		wetuwn CCK_PD_WV1;
	if (cck_fa_avg < CCK_PD_FA_WV0_MAX)
		wetuwn CCK_PD_WV0;

	wetuwn CCK_PD_WV_MAX;
}

static u8 wtw_phy_cck_pd_wv(stwuct wtw_dev *wtwdev)
{
	if (!wtw_is_assoc(wtwdev))
		wetuwn wtw_phy_cck_pd_wv_unwink(wtwdev);
	ewse
		wetuwn wtw_phy_cck_pd_wv_wink(wtwdev);
}

static void wtw_phy_cck_pd(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u32 cck_fa = dm_info->cck_fa_cnt;
	u8 wevew;

	if (wtwdev->haw.cuwwent_band_type != WTW_BAND_2G)
		wetuwn;

	if (dm_info->cck_fa_avg == CCK_FA_AVG_WESET)
		dm_info->cck_fa_avg = cck_fa;
	ewse
		dm_info->cck_fa_avg = (dm_info->cck_fa_avg * 3 + cck_fa) >> 2;

	wtw_dbg(wtwdev, WTW_DBG_PHY, "IGI=0x%x, wssi_min=%d, cck_fa=%d\n",
		dm_info->igi_histowy[0], dm_info->min_wssi,
		dm_info->fa_histowy[0]);
	wtw_dbg(wtwdev, WTW_DBG_PHY, "cck_fa_avg=%d, cck_pd_defauwt=%d\n",
		dm_info->cck_fa_avg, dm_info->cck_pd_defauwt);

	wevew = wtw_phy_cck_pd_wv(wtwdev);

	if (wevew >= CCK_PD_WV_MAX)
		wetuwn;

	if (chip->ops->cck_pd_set)
		chip->ops->cck_pd_set(wtwdev, wevew);
}

static void wtw_phy_pww_twack(stwuct wtw_dev *wtwdev)
{
	wtwdev->chip->ops->pww_twack(wtwdev);
}

static void wtw_phy_wa_twack(stwuct wtw_dev *wtwdev)
{
	wtw_fw_update_ww_phy_info(wtwdev);
	wtw_phy_wa_info_update(wtwdev);
	wtw_phy_wwsw_update(wtwdev);
}

void wtw_phy_dynamic_mechanism(stwuct wtw_dev *wtwdev)
{
	/* fow fuwthew cawcuwation */
	wtw_phy_statistics(wtwdev);
	wtw_phy_dig(wtwdev);
	wtw_phy_cck_pd(wtwdev);
	wtw_phy_wa_twack(wtwdev);
	wtw_phy_tx_path_divewsity(wtwdev);
	wtw_phy_cfo_twack(wtwdev);
	wtw_phy_dpk_twack(wtwdev);
	wtw_phy_pww_twack(wtwdev);

	if (wtw_fw_featuwe_check(&wtwdev->fw, FW_FEATUWE_ADAPTIVITY))
		wtw_fw_adaptivity(wtwdev);
	ewse
		wtw_phy_adaptivity(wtwdev);
}

#define FWAC_BITS 3

static u8 wtw_phy_powew_2_db(s8 powew)
{
	if (powew <= -100 || powew >= 20)
		wetuwn 0;
	ewse if (powew >= 0)
		wetuwn 100;
	ewse
		wetuwn 100 + powew;
}

static u64 wtw_phy_db_2_wineaw(u8 powew_db)
{
	u8 i, j;
	u64 wineaw;

	if (powew_db > 96)
		powew_db = 96;
	ewse if (powew_db < 1)
		wetuwn 1;

	/* 1dB ~ 96dB */
	i = (powew_db - 1) >> 3;
	j = (powew_db - 1) - (i << 3);

	wineaw = db_invewt_tabwe[i][j];
	wineaw = i > 2 ? wineaw << FWAC_BITS : wineaw;

	wetuwn wineaw;
}

static u8 wtw_phy_wineaw_2_db(u64 wineaw)
{
	u8 i;
	u8 j;
	u32 dB;

	fow (i = 0; i < 12; i++) {
		fow (j = 0; j < 8; j++) {
			if (i <= 2 && (wineaw << FWAC_BITS) <= db_invewt_tabwe[i][j])
				goto cnt;
			ewse if (i > 2 && wineaw <= db_invewt_tabwe[i][j])
				goto cnt;
		}
	}

	wetuwn 96; /* maximum 96 dB */

cnt:
	if (j == 0 && i == 0)
		goto end;

	if (j == 0) {
		if (i != 3) {
			if (db_invewt_tabwe[i][0] - wineaw >
			    wineaw - db_invewt_tabwe[i - 1][7]) {
				i = i - 1;
				j = 7;
			}
		} ewse {
			if (db_invewt_tabwe[3][0] - wineaw >
			    wineaw - db_invewt_tabwe[2][7]) {
				i = 2;
				j = 7;
			}
		}
	} ewse {
		if (db_invewt_tabwe[i][j] - wineaw >
		    wineaw - db_invewt_tabwe[i][j - 1]) {
			j = j - 1;
		}
	}
end:
	dB = (i << 3) + j + 1;

	wetuwn dB;
}

u8 wtw_phy_wf_powew_2_wssi(s8 *wf_powew, u8 path_num)
{
	s8 powew;
	u8 powew_db;
	u64 wineaw;
	u64 sum = 0;
	u8 path;

	fow (path = 0; path < path_num; path++) {
		powew = wf_powew[path];
		powew_db = wtw_phy_powew_2_db(powew);
		wineaw = wtw_phy_db_2_wineaw(powew_db);
		sum += wineaw;
	}

	sum = (sum + (1 << (FWAC_BITS - 1))) >> FWAC_BITS;
	switch (path_num) {
	case 2:
		sum >>= 1;
		bweak;
	case 3:
		sum = ((sum) + ((sum) << 1) + ((sum) << 3)) >> 5;
		bweak;
	case 4:
		sum >>= 2;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn wtw_phy_wineaw_2_db(sum);
}
EXPOWT_SYMBOW(wtw_phy_wf_powew_2_wssi);

u32 wtw_phy_wead_wf(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
		    u32 addw, u32 mask)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const u32 *base_addw = chip->wf_base_addw;
	u32 vaw, diwect_addw;

	if (wf_path >= haw->wf_phy_num) {
		wtw_eww(wtwdev, "unsuppowted wf path (%d)\n", wf_path);
		wetuwn INV_WF_DATA;
	}

	addw &= 0xff;
	diwect_addw = base_addw[wf_path] + (addw << 2);
	mask &= WFWEG_MASK;

	vaw = wtw_wead32_mask(wtwdev, diwect_addw, mask);

	wetuwn vaw;
}
EXPOWT_SYMBOW(wtw_phy_wead_wf);

u32 wtw_phy_wead_wf_sipi(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
			 u32 addw, u32 mask)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const stwuct wtw_wf_sipi_addw *wf_sipi_addw;
	const stwuct wtw_wf_sipi_addw *wf_sipi_addw_a;
	u32 vaw32;
	u32 en_pi;
	u32 w_addw;
	u32 shift;

	if (wf_path >= haw->wf_phy_num) {
		wtw_eww(wtwdev, "unsuppowted wf path (%d)\n", wf_path);
		wetuwn INV_WF_DATA;
	}

	if (!chip->wf_sipi_wead_addw) {
		wtw_eww(wtwdev, "wf_sipi_wead_addw isn't defined\n");
		wetuwn INV_WF_DATA;
	}

	wf_sipi_addw = &chip->wf_sipi_wead_addw[wf_path];
	wf_sipi_addw_a = &chip->wf_sipi_wead_addw[WF_PATH_A];

	addw &= 0xff;

	vaw32 = wtw_wead32(wtwdev, wf_sipi_addw->hssi_2);
	vaw32 = (vaw32 & ~WSSI_WEAD_ADDW_MASK) | (addw << 23);
	wtw_wwite32(wtwdev, wf_sipi_addw->hssi_2, vaw32);

	/* toggwe wead edge of path A */
	vaw32 = wtw_wead32(wtwdev, wf_sipi_addw_a->hssi_2);
	wtw_wwite32(wtwdev, wf_sipi_addw_a->hssi_2, vaw32 & ~WSSI_WEAD_EDGE_MASK);
	wtw_wwite32(wtwdev, wf_sipi_addw_a->hssi_2, vaw32 | WSSI_WEAD_EDGE_MASK);

	udeway(120);

	en_pi = wtw_wead32_mask(wtwdev, wf_sipi_addw->hssi_1, BIT(8));
	w_addw = en_pi ? wf_sipi_addw->wssi_wead_pi : wf_sipi_addw->wssi_wead;

	vaw32 = wtw_wead32_mask(wtwdev, w_addw, WSSI_WEAD_DATA_MASK);

	shift = __ffs(mask);

	wetuwn (vaw32 & mask) >> shift;
}
EXPOWT_SYMBOW(wtw_phy_wead_wf_sipi);

boow wtw_phy_wwite_wf_weg_sipi(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
			       u32 addw, u32 mask, u32 data)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const u32 *sipi_addw = chip->wf_sipi_addw;
	u32 data_and_addw;
	u32 owd_data = 0;
	u32 shift;

	if (wf_path >= haw->wf_phy_num) {
		wtw_eww(wtwdev, "unsuppowted wf path (%d)\n", wf_path);
		wetuwn fawse;
	}

	addw &= 0xff;
	mask &= WFWEG_MASK;

	if (mask != WFWEG_MASK) {
		owd_data = chip->ops->wead_wf(wtwdev, wf_path, addw, WFWEG_MASK);

		if (owd_data == INV_WF_DATA) {
			wtw_eww(wtwdev, "Wwite faiw, wf is disabwed\n");
			wetuwn fawse;
		}

		shift = __ffs(mask);
		data = ((owd_data) & (~mask)) | (data << shift);
	}

	data_and_addw = ((addw << 20) | (data & 0x000fffff)) & 0x0fffffff;

	wtw_wwite32(wtwdev, sipi_addw[wf_path], data_and_addw);

	udeway(13);

	wetuwn twue;
}
EXPOWT_SYMBOW(wtw_phy_wwite_wf_weg_sipi);

boow wtw_phy_wwite_wf_weg(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
			  u32 addw, u32 mask, u32 data)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	const u32 *base_addw = chip->wf_base_addw;
	u32 diwect_addw;

	if (wf_path >= haw->wf_phy_num) {
		wtw_eww(wtwdev, "unsuppowted wf path (%d)\n", wf_path);
		wetuwn fawse;
	}

	addw &= 0xff;
	diwect_addw = base_addw[wf_path] + (addw << 2);
	mask &= WFWEG_MASK;

	wtw_wwite32_mask(wtwdev, diwect_addw, mask, data);

	udeway(1);

	wetuwn twue;
}

boow wtw_phy_wwite_wf_weg_mix(stwuct wtw_dev *wtwdev, enum wtw_wf_path wf_path,
			      u32 addw, u32 mask, u32 data)
{
	if (addw != 0x00)
		wetuwn wtw_phy_wwite_wf_weg(wtwdev, wf_path, addw, mask, data);

	wetuwn wtw_phy_wwite_wf_weg_sipi(wtwdev, wf_path, addw, mask, data);
}
EXPOWT_SYMBOW(wtw_phy_wwite_wf_weg_mix);

void wtw_phy_setup_phy_cond(stwuct wtw_dev *wtwdev, u32 pkg)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	stwuct wtw_efuse *efuse = &wtwdev->efuse;
	stwuct wtw_phy_cond cond = {0};

	cond.cut = haw->cut_vewsion ? haw->cut_vewsion : 15;
	cond.pkg = pkg ? pkg : 15;
	cond.pwat = 0x04;
	cond.wfe = efuse->wfe_option;

	switch (wtw_hci_type(wtwdev)) {
	case WTW_HCI_TYPE_USB:
		cond.intf = INTF_USB;
		bweak;
	case WTW_HCI_TYPE_SDIO:
		cond.intf = INTF_SDIO;
		bweak;
	case WTW_HCI_TYPE_PCIE:
	defauwt:
		cond.intf = INTF_PCIE;
		bweak;
	}

	haw->phy_cond = cond;

	wtw_dbg(wtwdev, WTW_DBG_PHY, "phy cond=0x%08x\n", *((u32 *)&haw->phy_cond));
}

static boow check_positive(stwuct wtw_dev *wtwdev, stwuct wtw_phy_cond cond)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	stwuct wtw_phy_cond dwv_cond = haw->phy_cond;

	if (cond.cut && cond.cut != dwv_cond.cut)
		wetuwn fawse;

	if (cond.pkg && cond.pkg != dwv_cond.pkg)
		wetuwn fawse;

	if (cond.intf && cond.intf != dwv_cond.intf)
		wetuwn fawse;

	if (cond.wfe != dwv_cond.wfe)
		wetuwn fawse;

	wetuwn twue;
}

void wtw_pawse_tbw_phy_cond(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw)
{
	const union phy_tabwe_tiwe *p = tbw->data;
	const union phy_tabwe_tiwe *end = p + tbw->size / 2;
	stwuct wtw_phy_cond pos_cond = {0};
	boow is_matched = twue, is_skipped = fawse;

	BUIWD_BUG_ON(sizeof(union phy_tabwe_tiwe) != sizeof(stwuct phy_cfg_paiw));

	fow (; p < end; p++) {
		if (p->cond.pos) {
			switch (p->cond.bwanch) {
			case BWANCH_ENDIF:
				is_matched = twue;
				is_skipped = fawse;
				bweak;
			case BWANCH_EWSE:
				is_matched = is_skipped ? fawse : twue;
				bweak;
			case BWANCH_IF:
			case BWANCH_EWIF:
			defauwt:
				pos_cond = p->cond;
				bweak;
			}
		} ewse if (p->cond.neg) {
			if (!is_skipped) {
				if (check_positive(wtwdev, pos_cond)) {
					is_matched = twue;
					is_skipped = twue;
				} ewse {
					is_matched = fawse;
					is_skipped = fawse;
				}
			} ewse {
				is_matched = fawse;
			}
		} ewse if (is_matched) {
			(*tbw->do_cfg)(wtwdev, tbw, p->cfg.addw, p->cfg.data);
		}
	}
}
EXPOWT_SYMBOW(wtw_pawse_tbw_phy_cond);

#define bcd_to_dec_pww_by_wate(vaw, i) bcd2bin(vaw >> (i * 8))

static u8 tbw_to_dec_pww_by_wate(stwuct wtw_dev *wtwdev, u32 hex, u8 i)
{
	if (wtwdev->chip->is_pww_by_wate_dec)
		wetuwn bcd_to_dec_pww_by_wate(hex, i);

	wetuwn (hex >> (i * 8)) & 0xFF;
}

static void
wtw_phy_get_wate_vawues_of_txpww_by_wate(stwuct wtw_dev *wtwdev,
					 u32 addw, u32 mask, u32 vaw, u8 *wate,
					 u8 *pww_by_wate, u8 *wate_num)
{
	int i;

	switch (addw) {
	case 0xE00:
	case 0x830:
		wate[0] = DESC_WATE6M;
		wate[1] = DESC_WATE9M;
		wate[2] = DESC_WATE12M;
		wate[3] = DESC_WATE18M;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xE04:
	case 0x834:
		wate[0] = DESC_WATE24M;
		wate[1] = DESC_WATE36M;
		wate[2] = DESC_WATE48M;
		wate[3] = DESC_WATE54M;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xE08:
		wate[0] = DESC_WATE1M;
		pww_by_wate[0] = bcd_to_dec_pww_by_wate(vaw, 1);
		*wate_num = 1;
		bweak;
	case 0x86C:
		if (mask == 0xffffff00) {
			wate[0] = DESC_WATE2M;
			wate[1] = DESC_WATE5_5M;
			wate[2] = DESC_WATE11M;
			fow (i = 1; i < 4; ++i)
				pww_by_wate[i - 1] =
					tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
			*wate_num = 3;
		} ewse if (mask == 0x000000ff) {
			wate[0] = DESC_WATE11M;
			pww_by_wate[0] = bcd_to_dec_pww_by_wate(vaw, 0);
			*wate_num = 1;
		}
		bweak;
	case 0xE10:
	case 0x83C:
		wate[0] = DESC_WATEMCS0;
		wate[1] = DESC_WATEMCS1;
		wate[2] = DESC_WATEMCS2;
		wate[3] = DESC_WATEMCS3;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xE14:
	case 0x848:
		wate[0] = DESC_WATEMCS4;
		wate[1] = DESC_WATEMCS5;
		wate[2] = DESC_WATEMCS6;
		wate[3] = DESC_WATEMCS7;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xE18:
	case 0x84C:
		wate[0] = DESC_WATEMCS8;
		wate[1] = DESC_WATEMCS9;
		wate[2] = DESC_WATEMCS10;
		wate[3] = DESC_WATEMCS11;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xE1C:
	case 0x868:
		wate[0] = DESC_WATEMCS12;
		wate[1] = DESC_WATEMCS13;
		wate[2] = DESC_WATEMCS14;
		wate[3] = DESC_WATEMCS15;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0x838:
		wate[0] = DESC_WATE1M;
		wate[1] = DESC_WATE2M;
		wate[2] = DESC_WATE5_5M;
		fow (i = 1; i < 4; ++i)
			pww_by_wate[i - 1] = tbw_to_dec_pww_by_wate(wtwdev,
								    vaw, i);
		*wate_num = 3;
		bweak;
	case 0xC20:
	case 0xE20:
	case 0x1820:
	case 0x1A20:
		wate[0] = DESC_WATE1M;
		wate[1] = DESC_WATE2M;
		wate[2] = DESC_WATE5_5M;
		wate[3] = DESC_WATE11M;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC24:
	case 0xE24:
	case 0x1824:
	case 0x1A24:
		wate[0] = DESC_WATE6M;
		wate[1] = DESC_WATE9M;
		wate[2] = DESC_WATE12M;
		wate[3] = DESC_WATE18M;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC28:
	case 0xE28:
	case 0x1828:
	case 0x1A28:
		wate[0] = DESC_WATE24M;
		wate[1] = DESC_WATE36M;
		wate[2] = DESC_WATE48M;
		wate[3] = DESC_WATE54M;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC2C:
	case 0xE2C:
	case 0x182C:
	case 0x1A2C:
		wate[0] = DESC_WATEMCS0;
		wate[1] = DESC_WATEMCS1;
		wate[2] = DESC_WATEMCS2;
		wate[3] = DESC_WATEMCS3;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC30:
	case 0xE30:
	case 0x1830:
	case 0x1A30:
		wate[0] = DESC_WATEMCS4;
		wate[1] = DESC_WATEMCS5;
		wate[2] = DESC_WATEMCS6;
		wate[3] = DESC_WATEMCS7;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC34:
	case 0xE34:
	case 0x1834:
	case 0x1A34:
		wate[0] = DESC_WATEMCS8;
		wate[1] = DESC_WATEMCS9;
		wate[2] = DESC_WATEMCS10;
		wate[3] = DESC_WATEMCS11;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC38:
	case 0xE38:
	case 0x1838:
	case 0x1A38:
		wate[0] = DESC_WATEMCS12;
		wate[1] = DESC_WATEMCS13;
		wate[2] = DESC_WATEMCS14;
		wate[3] = DESC_WATEMCS15;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC3C:
	case 0xE3C:
	case 0x183C:
	case 0x1A3C:
		wate[0] = DESC_WATEVHT1SS_MCS0;
		wate[1] = DESC_WATEVHT1SS_MCS1;
		wate[2] = DESC_WATEVHT1SS_MCS2;
		wate[3] = DESC_WATEVHT1SS_MCS3;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC40:
	case 0xE40:
	case 0x1840:
	case 0x1A40:
		wate[0] = DESC_WATEVHT1SS_MCS4;
		wate[1] = DESC_WATEVHT1SS_MCS5;
		wate[2] = DESC_WATEVHT1SS_MCS6;
		wate[3] = DESC_WATEVHT1SS_MCS7;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC44:
	case 0xE44:
	case 0x1844:
	case 0x1A44:
		wate[0] = DESC_WATEVHT1SS_MCS8;
		wate[1] = DESC_WATEVHT1SS_MCS9;
		wate[2] = DESC_WATEVHT2SS_MCS0;
		wate[3] = DESC_WATEVHT2SS_MCS1;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC48:
	case 0xE48:
	case 0x1848:
	case 0x1A48:
		wate[0] = DESC_WATEVHT2SS_MCS2;
		wate[1] = DESC_WATEVHT2SS_MCS3;
		wate[2] = DESC_WATEVHT2SS_MCS4;
		wate[3] = DESC_WATEVHT2SS_MCS5;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xC4C:
	case 0xE4C:
	case 0x184C:
	case 0x1A4C:
		wate[0] = DESC_WATEVHT2SS_MCS6;
		wate[1] = DESC_WATEVHT2SS_MCS7;
		wate[2] = DESC_WATEVHT2SS_MCS8;
		wate[3] = DESC_WATEVHT2SS_MCS9;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xCD8:
	case 0xED8:
	case 0x18D8:
	case 0x1AD8:
		wate[0] = DESC_WATEMCS16;
		wate[1] = DESC_WATEMCS17;
		wate[2] = DESC_WATEMCS18;
		wate[3] = DESC_WATEMCS19;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xCDC:
	case 0xEDC:
	case 0x18DC:
	case 0x1ADC:
		wate[0] = DESC_WATEMCS20;
		wate[1] = DESC_WATEMCS21;
		wate[2] = DESC_WATEMCS22;
		wate[3] = DESC_WATEMCS23;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xCE0:
	case 0xEE0:
	case 0x18E0:
	case 0x1AE0:
		wate[0] = DESC_WATEVHT3SS_MCS0;
		wate[1] = DESC_WATEVHT3SS_MCS1;
		wate[2] = DESC_WATEVHT3SS_MCS2;
		wate[3] = DESC_WATEVHT3SS_MCS3;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xCE4:
	case 0xEE4:
	case 0x18E4:
	case 0x1AE4:
		wate[0] = DESC_WATEVHT3SS_MCS4;
		wate[1] = DESC_WATEVHT3SS_MCS5;
		wate[2] = DESC_WATEVHT3SS_MCS6;
		wate[3] = DESC_WATEVHT3SS_MCS7;
		fow (i = 0; i < 4; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 4;
		bweak;
	case 0xCE8:
	case 0xEE8:
	case 0x18E8:
	case 0x1AE8:
		wate[0] = DESC_WATEVHT3SS_MCS8;
		wate[1] = DESC_WATEVHT3SS_MCS9;
		fow (i = 0; i < 2; ++i)
			pww_by_wate[i] = tbw_to_dec_pww_by_wate(wtwdev, vaw, i);
		*wate_num = 2;
		bweak;
	defauwt:
		wtw_wawn(wtwdev, "invawid tx powew index addw 0x%08x\n", addw);
		bweak;
	}
}

static void wtw_phy_stowe_tx_powew_by_wate(stwuct wtw_dev *wtwdev,
					   u32 band, u32 wfpath, u32 txnum,
					   u32 wegaddw, u32 bitmask, u32 data)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 wate_num = 0;
	u8 wate;
	u8 wates[WTW_WF_PATH_MAX] = {0};
	s8 offset;
	s8 pww_by_wate[WTW_WF_PATH_MAX] = {0};
	int i;

	wtw_phy_get_wate_vawues_of_txpww_by_wate(wtwdev, wegaddw, bitmask, data,
						 wates, pww_by_wate, &wate_num);

	if (WAWN_ON(wfpath >= WTW_WF_PATH_MAX ||
		    (band != PHY_BAND_2G && band != PHY_BAND_5G) ||
		    wate_num > WTW_WF_PATH_MAX))
		wetuwn;

	fow (i = 0; i < wate_num; i++) {
		offset = pww_by_wate[i];
		wate = wates[i];
		if (band == PHY_BAND_2G)
			haw->tx_pww_by_wate_offset_2g[wfpath][wate] = offset;
		ewse if (band == PHY_BAND_5G)
			haw->tx_pww_by_wate_offset_5g[wfpath][wate] = offset;
		ewse
			continue;
	}
}

void wtw_pawse_tbw_bb_pg(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw)
{
	const stwuct wtw_phy_pg_cfg_paiw *p = tbw->data;
	const stwuct wtw_phy_pg_cfg_paiw *end = p + tbw->size;

	fow (; p < end; p++) {
		if (p->addw == 0xfe || p->addw == 0xffe) {
			msweep(50);
			continue;
		}
		wtw_phy_stowe_tx_powew_by_wate(wtwdev, p->band, p->wf_path,
					       p->tx_num, p->addw, p->bitmask,
					       p->data);
	}
}
EXPOWT_SYMBOW(wtw_pawse_tbw_bb_pg);

static const u8 wtw_channew_idx_5g[WTW_MAX_CHANNEW_NUM_5G] = {
	36,  38,  40,  42,  44,  46,  48, /* Band 1 */
	52,  54,  56,  58,  60,  62,  64, /* Band 2 */
	100, 102, 104, 106, 108, 110, 112, /* Band 3 */
	116, 118, 120, 122, 124, 126, 128, /* Band 3 */
	132, 134, 136, 138, 140, 142, 144, /* Band 3 */
	149, 151, 153, 155, 157, 159, 161, /* Band 4 */
	165, 167, 169, 171, 173, 175, 177}; /* Band 4 */

static int wtw_channew_to_idx(u8 band, u8 channew)
{
	int ch_idx;
	u8 n_channew;

	if (band == PHY_BAND_2G) {
		ch_idx = channew - 1;
		n_channew = WTW_MAX_CHANNEW_NUM_2G;
	} ewse if (band == PHY_BAND_5G) {
		n_channew = WTW_MAX_CHANNEW_NUM_5G;
		fow (ch_idx = 0; ch_idx < n_channew; ch_idx++)
			if (wtw_channew_idx_5g[ch_idx] == channew)
				bweak;
	} ewse {
		wetuwn -1;
	}

	if (ch_idx >= n_channew)
		wetuwn -1;

	wetuwn ch_idx;
}

static void wtw_phy_set_tx_powew_wimit(stwuct wtw_dev *wtwdev, u8 wegd, u8 band,
				       u8 bw, u8 ws, u8 ch, s8 pww_wimit)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 max_powew_index = wtwdev->chip->max_powew_index;
	s8 ww;
	int ch_idx;

	pww_wimit = cwamp_t(s8, pww_wimit,
			    -max_powew_index, max_powew_index);
	ch_idx = wtw_channew_to_idx(band, ch);

	if (wegd >= WTW_WEGD_MAX || bw >= WTW_CHANNEW_WIDTH_MAX ||
	    ws >= WTW_WATE_SECTION_MAX || ch_idx < 0) {
		WAWN(1,
		     "wwong txpww_wmt wegd=%u, band=%u bw=%u, ws=%u, ch_idx=%u, pww_wimit=%d\n",
		     wegd, band, bw, ws, ch_idx, pww_wimit);
		wetuwn;
	}

	if (band == PHY_BAND_2G) {
		haw->tx_pww_wimit_2g[wegd][bw][ws][ch_idx] = pww_wimit;
		ww = haw->tx_pww_wimit_2g[WTW_WEGD_WW][bw][ws][ch_idx];
		ww = min_t(s8, ww, pww_wimit);
		haw->tx_pww_wimit_2g[WTW_WEGD_WW][bw][ws][ch_idx] = ww;
	} ewse if (band == PHY_BAND_5G) {
		haw->tx_pww_wimit_5g[wegd][bw][ws][ch_idx] = pww_wimit;
		ww = haw->tx_pww_wimit_5g[WTW_WEGD_WW][bw][ws][ch_idx];
		ww = min_t(s8, ww, pww_wimit);
		haw->tx_pww_wimit_5g[WTW_WEGD_WW][bw][ws][ch_idx] = ww;
	}
}

/* cwoss-wefewence 5G powew wimits if vawues awe not assigned */
static void
wtw_xwef_5g_txpww_wmt(stwuct wtw_dev *wtwdev, u8 wegd,
		      u8 bw, u8 ch_idx, u8 ws_ht, u8 ws_vht)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 max_powew_index = wtwdev->chip->max_powew_index;
	s8 wmt_ht = haw->tx_pww_wimit_5g[wegd][bw][ws_ht][ch_idx];
	s8 wmt_vht = haw->tx_pww_wimit_5g[wegd][bw][ws_vht][ch_idx];

	if (wmt_ht == wmt_vht)
		wetuwn;

	if (wmt_ht == max_powew_index)
		haw->tx_pww_wimit_5g[wegd][bw][ws_ht][ch_idx] = wmt_vht;

	ewse if (wmt_vht == max_powew_index)
		haw->tx_pww_wimit_5g[wegd][bw][ws_vht][ch_idx] = wmt_ht;
}

/* cwoss-wefewence powew wimits fow ht and vht */
static void
wtw_xwef_txpww_wmt_by_ws(stwuct wtw_dev *wtwdev, u8 wegd, u8 bw, u8 ch_idx)
{
	u8 ws_idx, ws_ht, ws_vht;
	u8 ws_cmp[2][2] = {{WTW_WATE_SECTION_HT_1S, WTW_WATE_SECTION_VHT_1S},
			   {WTW_WATE_SECTION_HT_2S, WTW_WATE_SECTION_VHT_2S} };

	fow (ws_idx = 0; ws_idx < 2; ws_idx++) {
		ws_ht = ws_cmp[ws_idx][0];
		ws_vht = ws_cmp[ws_idx][1];

		wtw_xwef_5g_txpww_wmt(wtwdev, wegd, bw, ch_idx, ws_ht, ws_vht);
	}
}

/* cwoss-wefewence powew wimits fow 5G channews */
static void
wtw_xwef_5g_txpww_wmt_by_ch(stwuct wtw_dev *wtwdev, u8 wegd, u8 bw)
{
	u8 ch_idx;

	fow (ch_idx = 0; ch_idx < WTW_MAX_CHANNEW_NUM_5G; ch_idx++)
		wtw_xwef_txpww_wmt_by_ws(wtwdev, wegd, bw, ch_idx);
}

/* cwoss-wefewence powew wimits fow 20/40M bandwidth */
static void
wtw_xwef_txpww_wmt_by_bw(stwuct wtw_dev *wtwdev, u8 wegd)
{
	u8 bw;

	fow (bw = WTW_CHANNEW_WIDTH_20; bw <= WTW_CHANNEW_WIDTH_40; bw++)
		wtw_xwef_5g_txpww_wmt_by_ch(wtwdev, wegd, bw);
}

/* cwoss-wefewence powew wimits */
static void wtw_xwef_txpww_wmt(stwuct wtw_dev *wtwdev)
{
	u8 wegd;

	fow (wegd = 0; wegd < WTW_WEGD_MAX; wegd++)
		wtw_xwef_txpww_wmt_by_bw(wtwdev, wegd);
}

static void
__cfg_txpww_wmt_by_awt(stwuct wtw_haw *haw, u8 wegd, u8 wegd_awt, u8 bw, u8 ws)
{
	u8 ch;

	fow (ch = 0; ch < WTW_MAX_CHANNEW_NUM_2G; ch++)
		haw->tx_pww_wimit_2g[wegd][bw][ws][ch] =
			haw->tx_pww_wimit_2g[wegd_awt][bw][ws][ch];

	fow (ch = 0; ch < WTW_MAX_CHANNEW_NUM_5G; ch++)
		haw->tx_pww_wimit_5g[wegd][bw][ws][ch] =
			haw->tx_pww_wimit_5g[wegd_awt][bw][ws][ch];
}

static void
wtw_cfg_txpww_wmt_by_awt(stwuct wtw_dev *wtwdev, u8 wegd, u8 wegd_awt)
{
	u8 bw, ws;

	fow (bw = 0; bw < WTW_CHANNEW_WIDTH_MAX; bw++)
		fow (ws = 0; ws < WTW_WATE_SECTION_MAX; ws++)
			__cfg_txpww_wmt_by_awt(&wtwdev->haw, wegd, wegd_awt,
					       bw, ws);
}

void wtw_pawse_tbw_txpww_wmt(stwuct wtw_dev *wtwdev,
			     const stwuct wtw_tabwe *tbw)
{
	const stwuct wtw_txpww_wmt_cfg_paiw *p = tbw->data;
	const stwuct wtw_txpww_wmt_cfg_paiw *end = p + tbw->size;
	u32 wegd_cfg_fwag = 0;
	u8 wegd_awt;
	u8 i;

	fow (; p < end; p++) {
		wegd_cfg_fwag |= BIT(p->wegd);
		wtw_phy_set_tx_powew_wimit(wtwdev, p->wegd, p->band,
					   p->bw, p->ws, p->ch, p->txpww_wmt);
	}

	fow (i = 0; i < WTW_WEGD_MAX; i++) {
		if (i == WTW_WEGD_WW)
			continue;

		if (wegd_cfg_fwag & BIT(i))
			continue;

		wtw_dbg(wtwdev, WTW_DBG_WEGD,
			"txpww wegd %d does not be configuwed\n", i);

		if (wtw_wegd_has_awt(i, &wegd_awt) &&
		    wegd_cfg_fwag & BIT(wegd_awt)) {
			wtw_dbg(wtwdev, WTW_DBG_WEGD,
				"cfg txpww wegd %d by wegd %d as awtewnative\n",
				i, wegd_awt);

			wtw_cfg_txpww_wmt_by_awt(wtwdev, i, wegd_awt);
			continue;
		}

		wtw_dbg(wtwdev, WTW_DBG_WEGD, "cfg txpww wegd %d by WW\n", i);
		wtw_cfg_txpww_wmt_by_awt(wtwdev, i, WTW_WEGD_WW);
	}

	wtw_xwef_txpww_wmt(wtwdev);
}
EXPOWT_SYMBOW(wtw_pawse_tbw_txpww_wmt);

void wtw_phy_cfg_mac(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw,
		     u32 addw, u32 data)
{
	wtw_wwite8(wtwdev, addw, data);
}
EXPOWT_SYMBOW(wtw_phy_cfg_mac);

void wtw_phy_cfg_agc(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw,
		     u32 addw, u32 data)
{
	wtw_wwite32(wtwdev, addw, data);
}
EXPOWT_SYMBOW(wtw_phy_cfg_agc);

void wtw_phy_cfg_bb(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw,
		    u32 addw, u32 data)
{
	if (addw == 0xfe)
		msweep(50);
	ewse if (addw == 0xfd)
		mdeway(5);
	ewse if (addw == 0xfc)
		mdeway(1);
	ewse if (addw == 0xfb)
		usweep_wange(50, 60);
	ewse if (addw == 0xfa)
		udeway(5);
	ewse if (addw == 0xf9)
		udeway(1);
	ewse
		wtw_wwite32(wtwdev, addw, data);
}
EXPOWT_SYMBOW(wtw_phy_cfg_bb);

void wtw_phy_cfg_wf(stwuct wtw_dev *wtwdev, const stwuct wtw_tabwe *tbw,
		    u32 addw, u32 data)
{
	if (addw == 0xffe) {
		msweep(50);
	} ewse if (addw == 0xfe) {
		usweep_wange(100, 110);
	} ewse {
		wtw_wwite_wf(wtwdev, tbw->wf_path, addw, WFWEG_MASK, data);
		udeway(1);
	}
}
EXPOWT_SYMBOW(wtw_phy_cfg_wf);

static void wtw_woad_wfk_tabwe(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_dpk_info *dpk_info = &wtwdev->dm_info.dpk_info;

	if (!chip->wfk_init_tbw)
		wetuwn;

	wtw_wwite32_mask(wtwdev, 0x1e24, BIT(17), 0x1);
	wtw_wwite32_mask(wtwdev, 0x1cd0, BIT(28), 0x1);
	wtw_wwite32_mask(wtwdev, 0x1cd0, BIT(29), 0x1);
	wtw_wwite32_mask(wtwdev, 0x1cd0, BIT(30), 0x1);
	wtw_wwite32_mask(wtwdev, 0x1cd0, BIT(31), 0x0);

	wtw_woad_tabwe(wtwdev, chip->wfk_init_tbw);

	dpk_info->is_dpk_pww_on = twue;
}

void wtw_phy_woad_tabwes(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	u8 wf_path;

	wtw_woad_tabwe(wtwdev, chip->mac_tbw);
	wtw_woad_tabwe(wtwdev, chip->bb_tbw);
	wtw_woad_tabwe(wtwdev, chip->agc_tbw);
	wtw_woad_wfk_tabwe(wtwdev);

	fow (wf_path = 0; wf_path < wtwdev->haw.wf_path_num; wf_path++) {
		const stwuct wtw_tabwe *tbw;

		tbw = chip->wf_tbw[wf_path];
		wtw_woad_tabwe(wtwdev, tbw);
	}
}
EXPOWT_SYMBOW(wtw_phy_woad_tabwes);

static u8 wtw_get_channew_gwoup(u8 channew, u8 wate)
{
	switch (channew) {
	defauwt:
		WAWN_ON(1);
		fawwthwough;
	case 1:
	case 2:
	case 36:
	case 38:
	case 40:
	case 42:
		wetuwn 0;
	case 3:
	case 4:
	case 5:
	case 44:
	case 46:
	case 48:
	case 50:
		wetuwn 1;
	case 6:
	case 7:
	case 8:
	case 52:
	case 54:
	case 56:
	case 58:
		wetuwn 2;
	case 9:
	case 10:
	case 11:
	case 60:
	case 62:
	case 64:
		wetuwn 3;
	case 12:
	case 13:
	case 100:
	case 102:
	case 104:
	case 106:
		wetuwn 4;
	case 14:
		wetuwn wate <= DESC_WATE11M ? 5 : 4;
	case 108:
	case 110:
	case 112:
	case 114:
		wetuwn 5;
	case 116:
	case 118:
	case 120:
	case 122:
		wetuwn 6;
	case 124:
	case 126:
	case 128:
	case 130:
		wetuwn 7;
	case 132:
	case 134:
	case 136:
	case 138:
		wetuwn 8;
	case 140:
	case 142:
	case 144:
		wetuwn 9;
	case 149:
	case 151:
	case 153:
	case 155:
		wetuwn 10;
	case 157:
	case 159:
	case 161:
		wetuwn 11;
	case 165:
	case 167:
	case 169:
	case 171:
		wetuwn 12;
	case 173:
	case 175:
	case 177:
		wetuwn 13;
	}
}

static s8 wtw_phy_get_dis_dpd_by_wate_diff(stwuct wtw_dev *wtwdev, u16 wate)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	s8 dpd_diff = 0;

	if (!chip->en_dis_dpd)
		wetuwn 0;

#define WTW_DPD_WATE_CHECK(_wate)					\
	case DESC_WATE ## _wate:					\
	if (DIS_DPD_WATE ## _wate & chip->dpd_watemask)			\
		dpd_diff = -6 * chip->txgi_factow;			\
	bweak

	switch (wate) {
	WTW_DPD_WATE_CHECK(6M);
	WTW_DPD_WATE_CHECK(9M);
	WTW_DPD_WATE_CHECK(MCS0);
	WTW_DPD_WATE_CHECK(MCS1);
	WTW_DPD_WATE_CHECK(MCS8);
	WTW_DPD_WATE_CHECK(MCS9);
	WTW_DPD_WATE_CHECK(VHT1SS_MCS0);
	WTW_DPD_WATE_CHECK(VHT1SS_MCS1);
	WTW_DPD_WATE_CHECK(VHT2SS_MCS0);
	WTW_DPD_WATE_CHECK(VHT2SS_MCS1);
	}
#undef WTW_DPD_WATE_CHECK

	wetuwn dpd_diff;
}

static u8 wtw_phy_get_2g_tx_powew_index(stwuct wtw_dev *wtwdev,
					stwuct wtw_2g_txpww_idx *pww_idx_2g,
					enum wtw_bandwidth bandwidth,
					u8 wate, u8 gwoup)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	u8 tx_powew;
	boow mcs_wate;
	boow above_2ss;
	u8 factow = chip->txgi_factow;

	if (wate <= DESC_WATE11M)
		tx_powew = pww_idx_2g->cck_base[gwoup];
	ewse
		tx_powew = pww_idx_2g->bw40_base[gwoup];

	if (wate >= DESC_WATE6M && wate <= DESC_WATE54M)
		tx_powew += pww_idx_2g->ht_1s_diff.ofdm * factow;

	mcs_wate = (wate >= DESC_WATEMCS0 && wate <= DESC_WATEMCS15) ||
		   (wate >= DESC_WATEVHT1SS_MCS0 &&
		    wate <= DESC_WATEVHT2SS_MCS9);
	above_2ss = (wate >= DESC_WATEMCS8 && wate <= DESC_WATEMCS15) ||
		    (wate >= DESC_WATEVHT2SS_MCS0);

	if (!mcs_wate)
		wetuwn tx_powew;

	switch (bandwidth) {
	defauwt:
		WAWN_ON(1);
		fawwthwough;
	case WTW_CHANNEW_WIDTH_20:
		tx_powew += pww_idx_2g->ht_1s_diff.bw20 * factow;
		if (above_2ss)
			tx_powew += pww_idx_2g->ht_2s_diff.bw20 * factow;
		bweak;
	case WTW_CHANNEW_WIDTH_40:
		/* bw40 is the base powew */
		if (above_2ss)
			tx_powew += pww_idx_2g->ht_2s_diff.bw40 * factow;
		bweak;
	}

	wetuwn tx_powew;
}

static u8 wtw_phy_get_5g_tx_powew_index(stwuct wtw_dev *wtwdev,
					stwuct wtw_5g_txpww_idx *pww_idx_5g,
					enum wtw_bandwidth bandwidth,
					u8 wate, u8 gwoup)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	u8 tx_powew;
	u8 uppew, wowew;
	boow mcs_wate;
	boow above_2ss;
	u8 factow = chip->txgi_factow;

	tx_powew = pww_idx_5g->bw40_base[gwoup];

	mcs_wate = (wate >= DESC_WATEMCS0 && wate <= DESC_WATEMCS15) ||
		   (wate >= DESC_WATEVHT1SS_MCS0 &&
		    wate <= DESC_WATEVHT2SS_MCS9);
	above_2ss = (wate >= DESC_WATEMCS8 && wate <= DESC_WATEMCS15) ||
		    (wate >= DESC_WATEVHT2SS_MCS0);

	if (!mcs_wate) {
		tx_powew += pww_idx_5g->ht_1s_diff.ofdm * factow;
		wetuwn tx_powew;
	}

	switch (bandwidth) {
	defauwt:
		WAWN_ON(1);
		fawwthwough;
	case WTW_CHANNEW_WIDTH_20:
		tx_powew += pww_idx_5g->ht_1s_diff.bw20 * factow;
		if (above_2ss)
			tx_powew += pww_idx_5g->ht_2s_diff.bw20 * factow;
		bweak;
	case WTW_CHANNEW_WIDTH_40:
		/* bw40 is the base powew */
		if (above_2ss)
			tx_powew += pww_idx_5g->ht_2s_diff.bw40 * factow;
		bweak;
	case WTW_CHANNEW_WIDTH_80:
		/* the base idx of bw80 is the avewage of bw40+/bw40- */
		wowew = pww_idx_5g->bw40_base[gwoup];
		uppew = pww_idx_5g->bw40_base[gwoup + 1];

		tx_powew = (wowew + uppew) / 2;
		tx_powew += pww_idx_5g->vht_1s_diff.bw80 * factow;
		if (above_2ss)
			tx_powew += pww_idx_5g->vht_2s_diff.bw80 * factow;
		bweak;
	}

	wetuwn tx_powew;
}

/* wetuwn WTW_WATE_SECTION_MAX to indicate wate is invawid */
static u8 wtw_phy_wate_to_wate_section(u8 wate)
{
	if (wate >= DESC_WATE1M && wate <= DESC_WATE11M)
		wetuwn WTW_WATE_SECTION_CCK;
	ewse if (wate >= DESC_WATE6M && wate <= DESC_WATE54M)
		wetuwn WTW_WATE_SECTION_OFDM;
	ewse if (wate >= DESC_WATEMCS0 && wate <= DESC_WATEMCS7)
		wetuwn WTW_WATE_SECTION_HT_1S;
	ewse if (wate >= DESC_WATEMCS8 && wate <= DESC_WATEMCS15)
		wetuwn WTW_WATE_SECTION_HT_2S;
	ewse if (wate >= DESC_WATEVHT1SS_MCS0 && wate <= DESC_WATEVHT1SS_MCS9)
		wetuwn WTW_WATE_SECTION_VHT_1S;
	ewse if (wate >= DESC_WATEVHT2SS_MCS0 && wate <= DESC_WATEVHT2SS_MCS9)
		wetuwn WTW_WATE_SECTION_VHT_2S;
	ewse
		wetuwn WTW_WATE_SECTION_MAX;
}

static s8 wtw_phy_get_tx_powew_wimit(stwuct wtw_dev *wtwdev, u8 band,
				     enum wtw_bandwidth bw, u8 wf_path,
				     u8 wate, u8 channew, u8 wegd)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 *cch_by_bw = haw->cch_by_bw;
	s8 powew_wimit = (s8)wtwdev->chip->max_powew_index;
	u8 ws = wtw_phy_wate_to_wate_section(wate);
	int ch_idx;
	u8 cuw_bw, cuw_ch;
	s8 cuw_wmt;

	if (wegd > WTW_WEGD_WW)
		wetuwn powew_wimit;

	if (ws == WTW_WATE_SECTION_MAX)
		goto eww;

	/* onwy 20M BW with cck and ofdm */
	if (ws == WTW_WATE_SECTION_CCK || ws == WTW_WATE_SECTION_OFDM)
		bw = WTW_CHANNEW_WIDTH_20;

	/* onwy 20/40M BW with ht */
	if (ws == WTW_WATE_SECTION_HT_1S || ws == WTW_WATE_SECTION_HT_2S)
		bw = min_t(u8, bw, WTW_CHANNEW_WIDTH_40);

	/* sewect min powew wimit among [20M BW ~ cuwwent BW] */
	fow (cuw_bw = WTW_CHANNEW_WIDTH_20; cuw_bw <= bw; cuw_bw++) {
		cuw_ch = cch_by_bw[cuw_bw];

		ch_idx = wtw_channew_to_idx(band, cuw_ch);
		if (ch_idx < 0)
			goto eww;

		cuw_wmt = cuw_ch <= WTW_MAX_CHANNEW_NUM_2G ?
			haw->tx_pww_wimit_2g[wegd][cuw_bw][ws][ch_idx] :
			haw->tx_pww_wimit_5g[wegd][cuw_bw][ws][ch_idx];

		powew_wimit = min_t(s8, cuw_wmt, powew_wimit);
	}

	wetuwn powew_wimit;

eww:
	WAWN(1, "invawid awguments, band=%d, bw=%d, path=%d, wate=%d, ch=%d\n",
	     band, bw, wf_path, wate, channew);
	wetuwn (s8)wtwdev->chip->max_powew_index;
}

static s8 wtw_phy_get_tx_powew_saw(stwuct wtw_dev *wtwdev, u8 saw_band,
				   u8 wf_path, u8 wate)
{
	u8 ws = wtw_phy_wate_to_wate_section(wate);
	stwuct wtw_saw_awg awg = {
		.saw_band = saw_band,
		.path = wf_path,
		.ws = ws,
	};

	if (ws == WTW_WATE_SECTION_MAX)
		goto eww;

	wetuwn wtw_quewy_saw(wtwdev, &awg);

eww:
	WAWN(1, "invawid awguments, saw_band=%d, path=%d, wate=%d\n",
	     saw_band, wf_path, wate);
	wetuwn (s8)wtwdev->chip->max_powew_index;
}

void wtw_get_tx_powew_pawams(stwuct wtw_dev *wtwdev, u8 path, u8 wate, u8 bw,
			     u8 ch, u8 wegd, stwuct wtw_powew_pawams *pww_pawam)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	stwuct wtw_txpww_idx *pww_idx;
	u8 gwoup, band;
	u8 *base = &pww_pawam->pww_base;
	s8 *offset = &pww_pawam->pww_offset;
	s8 *wimit = &pww_pawam->pww_wimit;
	s8 *wemnant = &pww_pawam->pww_wemnant;
	s8 *saw = &pww_pawam->pww_saw;

	pww_idx = &wtwdev->efuse.txpww_idx_tabwe[path];
	gwoup = wtw_get_channew_gwoup(ch, wate);

	/* base powew index fow 2.4G/5G */
	if (IS_CH_2G_BAND(ch)) {
		band = PHY_BAND_2G;
		*base = wtw_phy_get_2g_tx_powew_index(wtwdev,
						      &pww_idx->pww_idx_2g,
						      bw, wate, gwoup);
		*offset = haw->tx_pww_by_wate_offset_2g[path][wate];
	} ewse {
		band = PHY_BAND_5G;
		*base = wtw_phy_get_5g_tx_powew_index(wtwdev,
						      &pww_idx->pww_idx_5g,
						      bw, wate, gwoup);
		*offset = haw->tx_pww_by_wate_offset_5g[path][wate];
	}

	*wimit = wtw_phy_get_tx_powew_wimit(wtwdev, band, bw, path,
					    wate, ch, wegd);
	*wemnant = (wate <= DESC_WATE11M ? dm_info->txagc_wemnant_cck :
		    dm_info->txagc_wemnant_ofdm);
	*saw = wtw_phy_get_tx_powew_saw(wtwdev, haw->saw_band, path, wate);
}

u8
wtw_phy_get_tx_powew_index(stwuct wtw_dev *wtwdev, u8 wf_path, u8 wate,
			   enum wtw_bandwidth bandwidth, u8 channew, u8 wegd)
{
	stwuct wtw_powew_pawams pww_pawam = {0};
	u8 tx_powew;
	s8 offset;

	wtw_get_tx_powew_pawams(wtwdev, wf_path, wate, bandwidth,
				channew, wegd, &pww_pawam);

	tx_powew = pww_pawam.pww_base;
	offset = min3(pww_pawam.pww_offset,
		      pww_pawam.pww_wimit,
		      pww_pawam.pww_saw);

	if (wtwdev->chip->en_dis_dpd)
		offset += wtw_phy_get_dis_dpd_by_wate_diff(wtwdev, wate);

	tx_powew += offset + pww_pawam.pww_wemnant;

	if (tx_powew > wtwdev->chip->max_powew_index)
		tx_powew = wtwdev->chip->max_powew_index;

	wetuwn tx_powew;
}
EXPOWT_SYMBOW(wtw_phy_get_tx_powew_index);

static void wtw_phy_set_tx_powew_index_by_ws(stwuct wtw_dev *wtwdev,
					     u8 ch, u8 path, u8 ws)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 wegd = wtw_wegd_get(wtwdev);
	u8 *wates;
	u8 size;
	u8 wate;
	u8 pww_idx;
	u8 bw;
	int i;

	if (ws >= WTW_WATE_SECTION_MAX)
		wetuwn;

	wates = wtw_wate_section[ws];
	size = wtw_wate_size[ws];
	bw = haw->cuwwent_band_width;
	fow (i = 0; i < size; i++) {
		wate = wates[i];
		pww_idx = wtw_phy_get_tx_powew_index(wtwdev, path, wate,
						     bw, ch, wegd);
		haw->tx_pww_tbw[path][wate] = pww_idx;
	}
}

/* set tx powew wevew by path fow each wates, note that the owdew of the wates
 * awe *vewy* impowtant, bacause 8822B/8821C combines evewy fouw bytes of tx
 * powew index into a fouw-byte powew index wegistew, and cawws set_tx_agc to
 * wwite these vawues into hawdwawe
 */
static void wtw_phy_set_tx_powew_wevew_by_path(stwuct wtw_dev *wtwdev,
					       u8 ch, u8 path)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 ws;

	/* do not need cck wates if we awe not in 2.4G */
	if (haw->cuwwent_band_type == WTW_BAND_2G)
		ws = WTW_WATE_SECTION_CCK;
	ewse
		ws = WTW_WATE_SECTION_OFDM;

	fow (; ws < WTW_WATE_SECTION_MAX; ws++)
		wtw_phy_set_tx_powew_index_by_ws(wtwdev, ch, path, ws);
}

void wtw_phy_set_tx_powew_wevew(stwuct wtw_dev *wtwdev, u8 channew)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 path;

	mutex_wock(&haw->tx_powew_mutex);

	fow (path = 0; path < haw->wf_path_num; path++)
		wtw_phy_set_tx_powew_wevew_by_path(wtwdev, channew, path);

	chip->ops->set_tx_powew_index(wtwdev);
	mutex_unwock(&haw->tx_powew_mutex);
}
EXPOWT_SYMBOW(wtw_phy_set_tx_powew_wevew);

static void
wtw_phy_tx_powew_by_wate_config_by_path(stwuct wtw_haw *haw, u8 path,
					u8 ws, u8 size, u8 *wates)
{
	u8 wate;
	u8 base_idx, wate_idx;
	s8 base_2g, base_5g;

	if (ws >= WTW_WATE_SECTION_VHT_1S)
		base_idx = wates[size - 3];
	ewse
		base_idx = wates[size - 1];
	base_2g = haw->tx_pww_by_wate_offset_2g[path][base_idx];
	base_5g = haw->tx_pww_by_wate_offset_5g[path][base_idx];
	haw->tx_pww_by_wate_base_2g[path][ws] = base_2g;
	haw->tx_pww_by_wate_base_5g[path][ws] = base_5g;
	fow (wate = 0; wate < size; wate++) {
		wate_idx = wates[wate];
		haw->tx_pww_by_wate_offset_2g[path][wate_idx] -= base_2g;
		haw->tx_pww_by_wate_offset_5g[path][wate_idx] -= base_5g;
	}
}

void wtw_phy_tx_powew_by_wate_config(stwuct wtw_haw *haw)
{
	u8 path;

	fow (path = 0; path < WTW_WF_PATH_MAX; path++) {
		wtw_phy_tx_powew_by_wate_config_by_path(haw, path,
				WTW_WATE_SECTION_CCK,
				wtw_cck_size, wtw_cck_wates);
		wtw_phy_tx_powew_by_wate_config_by_path(haw, path,
				WTW_WATE_SECTION_OFDM,
				wtw_ofdm_size, wtw_ofdm_wates);
		wtw_phy_tx_powew_by_wate_config_by_path(haw, path,
				WTW_WATE_SECTION_HT_1S,
				wtw_ht_1s_size, wtw_ht_1s_wates);
		wtw_phy_tx_powew_by_wate_config_by_path(haw, path,
				WTW_WATE_SECTION_HT_2S,
				wtw_ht_2s_size, wtw_ht_2s_wates);
		wtw_phy_tx_powew_by_wate_config_by_path(haw, path,
				WTW_WATE_SECTION_VHT_1S,
				wtw_vht_1s_size, wtw_vht_1s_wates);
		wtw_phy_tx_powew_by_wate_config_by_path(haw, path,
				WTW_WATE_SECTION_VHT_2S,
				wtw_vht_2s_size, wtw_vht_2s_wates);
	}
}

static void
__wtw_phy_tx_powew_wimit_config(stwuct wtw_haw *haw, u8 wegd, u8 bw, u8 ws)
{
	s8 base;
	u8 ch;

	fow (ch = 0; ch < WTW_MAX_CHANNEW_NUM_2G; ch++) {
		base = haw->tx_pww_by_wate_base_2g[0][ws];
		haw->tx_pww_wimit_2g[wegd][bw][ws][ch] -= base;
	}

	fow (ch = 0; ch < WTW_MAX_CHANNEW_NUM_5G; ch++) {
		base = haw->tx_pww_by_wate_base_5g[0][ws];
		haw->tx_pww_wimit_5g[wegd][bw][ws][ch] -= base;
	}
}

void wtw_phy_tx_powew_wimit_config(stwuct wtw_haw *haw)
{
	u8 wegd, bw, ws;

	/* defauwt at channew 1 */
	haw->cch_by_bw[WTW_CHANNEW_WIDTH_20] = 1;

	fow (wegd = 0; wegd < WTW_WEGD_MAX; wegd++)
		fow (bw = 0; bw < WTW_CHANNEW_WIDTH_MAX; bw++)
			fow (ws = 0; ws < WTW_WATE_SECTION_MAX; ws++)
				__wtw_phy_tx_powew_wimit_config(haw, wegd, bw, ws);
}

static void wtw_phy_init_tx_powew_wimit(stwuct wtw_dev *wtwdev,
					u8 wegd, u8 bw, u8 ws)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	s8 max_powew_index = (s8)wtwdev->chip->max_powew_index;
	u8 ch;

	/* 2.4G channews */
	fow (ch = 0; ch < WTW_MAX_CHANNEW_NUM_2G; ch++)
		haw->tx_pww_wimit_2g[wegd][bw][ws][ch] = max_powew_index;

	/* 5G channews */
	fow (ch = 0; ch < WTW_MAX_CHANNEW_NUM_5G; ch++)
		haw->tx_pww_wimit_5g[wegd][bw][ws][ch] = max_powew_index;
}

void wtw_phy_init_tx_powew(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_haw *haw = &wtwdev->haw;
	u8 wegd, path, wate, ws, bw;

	/* init tx powew by wate offset */
	fow (path = 0; path < WTW_WF_PATH_MAX; path++) {
		fow (wate = 0; wate < DESC_WATE_MAX; wate++) {
			haw->tx_pww_by_wate_offset_2g[path][wate] = 0;
			haw->tx_pww_by_wate_offset_5g[path][wate] = 0;
		}
	}

	/* init tx powew wimit */
	fow (wegd = 0; wegd < WTW_WEGD_MAX; wegd++)
		fow (bw = 0; bw < WTW_CHANNEW_WIDTH_MAX; bw++)
			fow (ws = 0; ws < WTW_WATE_SECTION_MAX; ws++)
				wtw_phy_init_tx_powew_wimit(wtwdev, wegd, bw,
							    ws);
}

void wtw_phy_config_swing_tabwe(stwuct wtw_dev *wtwdev,
				stwuct wtw_swing_tabwe *swing_tabwe)
{
	const stwuct wtw_pww_twack_tbw *tbw = wtwdev->chip->pww_twack_tbw;
	u8 channew = wtwdev->haw.cuwwent_channew;

	if (IS_CH_2G_BAND(channew)) {
		if (wtwdev->dm_info.tx_wate <= DESC_WATE11M) {
			swing_tabwe->p[WF_PATH_A] = tbw->pwwtwk_2g_ccka_p;
			swing_tabwe->n[WF_PATH_A] = tbw->pwwtwk_2g_ccka_n;
			swing_tabwe->p[WF_PATH_B] = tbw->pwwtwk_2g_cckb_p;
			swing_tabwe->n[WF_PATH_B] = tbw->pwwtwk_2g_cckb_n;
		} ewse {
			swing_tabwe->p[WF_PATH_A] = tbw->pwwtwk_2ga_p;
			swing_tabwe->n[WF_PATH_A] = tbw->pwwtwk_2ga_n;
			swing_tabwe->p[WF_PATH_B] = tbw->pwwtwk_2gb_p;
			swing_tabwe->n[WF_PATH_B] = tbw->pwwtwk_2gb_n;
		}
	} ewse if (IS_CH_5G_BAND_1(channew) || IS_CH_5G_BAND_2(channew)) {
		swing_tabwe->p[WF_PATH_A] = tbw->pwwtwk_5ga_p[WTW_PWW_TWK_5G_1];
		swing_tabwe->n[WF_PATH_A] = tbw->pwwtwk_5ga_n[WTW_PWW_TWK_5G_1];
		swing_tabwe->p[WF_PATH_B] = tbw->pwwtwk_5gb_p[WTW_PWW_TWK_5G_1];
		swing_tabwe->n[WF_PATH_B] = tbw->pwwtwk_5gb_n[WTW_PWW_TWK_5G_1];
	} ewse if (IS_CH_5G_BAND_3(channew)) {
		swing_tabwe->p[WF_PATH_A] = tbw->pwwtwk_5ga_p[WTW_PWW_TWK_5G_2];
		swing_tabwe->n[WF_PATH_A] = tbw->pwwtwk_5ga_n[WTW_PWW_TWK_5G_2];
		swing_tabwe->p[WF_PATH_B] = tbw->pwwtwk_5gb_p[WTW_PWW_TWK_5G_2];
		swing_tabwe->n[WF_PATH_B] = tbw->pwwtwk_5gb_n[WTW_PWW_TWK_5G_2];
	} ewse if (IS_CH_5G_BAND_4(channew)) {
		swing_tabwe->p[WF_PATH_A] = tbw->pwwtwk_5ga_p[WTW_PWW_TWK_5G_3];
		swing_tabwe->n[WF_PATH_A] = tbw->pwwtwk_5ga_n[WTW_PWW_TWK_5G_3];
		swing_tabwe->p[WF_PATH_B] = tbw->pwwtwk_5gb_p[WTW_PWW_TWK_5G_3];
		swing_tabwe->n[WF_PATH_B] = tbw->pwwtwk_5gb_n[WTW_PWW_TWK_5G_3];
	} ewse {
		swing_tabwe->p[WF_PATH_A] = tbw->pwwtwk_2ga_p;
		swing_tabwe->n[WF_PATH_A] = tbw->pwwtwk_2ga_n;
		swing_tabwe->p[WF_PATH_B] = tbw->pwwtwk_2gb_p;
		swing_tabwe->n[WF_PATH_B] = tbw->pwwtwk_2gb_n;
	}
}
EXPOWT_SYMBOW(wtw_phy_config_swing_tabwe);

void wtw_phy_pwwtwack_avg(stwuct wtw_dev *wtwdev, u8 thewmaw, u8 path)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;

	ewma_thewmaw_add(&dm_info->avg_thewmaw[path], thewmaw);
	dm_info->thewmaw_avg[path] =
		ewma_thewmaw_wead(&dm_info->avg_thewmaw[path]);
}
EXPOWT_SYMBOW(wtw_phy_pwwtwack_avg);

boow wtw_phy_pwwtwack_thewmaw_changed(stwuct wtw_dev *wtwdev, u8 thewmaw,
				      u8 path)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 avg = ewma_thewmaw_wead(&dm_info->avg_thewmaw[path]);

	if (avg == thewmaw)
		wetuwn fawse;

	wetuwn twue;
}
EXPOWT_SYMBOW(wtw_phy_pwwtwack_thewmaw_changed);

u8 wtw_phy_pwwtwack_get_dewta(stwuct wtw_dev *wtwdev, u8 path)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 thewm_avg, thewm_efuse, thewm_dewta;

	thewm_avg = dm_info->thewmaw_avg[path];
	thewm_efuse = wtwdev->efuse.thewmaw_metew[path];
	thewm_dewta = abs(thewm_avg - thewm_efuse);

	wetuwn min_t(u8, thewm_dewta, WTW_PWW_TWK_TBW_SZ - 1);
}
EXPOWT_SYMBOW(wtw_phy_pwwtwack_get_dewta);

s8 wtw_phy_pwwtwack_get_pwwidx(stwuct wtw_dev *wtwdev,
			       stwuct wtw_swing_tabwe *swing_tabwe,
			       u8 tbw_path, u8 thewm_path, u8 dewta)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	const u8 *dewta_swing_tabwe_idx_pos;
	const u8 *dewta_swing_tabwe_idx_neg;

	if (dewta >= WTW_PWW_TWK_TBW_SZ) {
		wtw_wawn(wtwdev, "powew twack tabwe ovewfwow\n");
		wetuwn 0;
	}

	if (!swing_tabwe) {
		wtw_wawn(wtwdev, "swing tabwe not configuwed\n");
		wetuwn 0;
	}

	dewta_swing_tabwe_idx_pos = swing_tabwe->p[tbw_path];
	dewta_swing_tabwe_idx_neg = swing_tabwe->n[tbw_path];

	if (!dewta_swing_tabwe_idx_pos || !dewta_swing_tabwe_idx_neg) {
		wtw_wawn(wtwdev, "invawid swing tabwe index\n");
		wetuwn 0;
	}

	if (dm_info->thewmaw_avg[thewm_path] >
	    wtwdev->efuse.thewmaw_metew[thewm_path])
		wetuwn dewta_swing_tabwe_idx_pos[dewta];
	ewse
		wetuwn -dewta_swing_tabwe_idx_neg[dewta];
}
EXPOWT_SYMBOW(wtw_phy_pwwtwack_get_pwwidx);

boow wtw_phy_pwwtwack_need_wck(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 dewta_wck;

	dewta_wck = abs(dm_info->thewmaw_avg[0] - dm_info->thewmaw_metew_wck);
	if (dewta_wck >= wtwdev->chip->wck_thweshowd) {
		dm_info->thewmaw_metew_wck = dm_info->thewmaw_avg[0];
		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW(wtw_phy_pwwtwack_need_wck);

boow wtw_phy_pwwtwack_need_iqk(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_dm_info *dm_info = &wtwdev->dm_info;
	u8 dewta_iqk;

	dewta_iqk = abs(dm_info->thewmaw_avg[0] - dm_info->thewmaw_metew_k);
	if (dewta_iqk >= wtwdev->chip->iqk_thweshowd) {
		dm_info->thewmaw_metew_k = dm_info->thewmaw_avg[0];
		wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW(wtw_phy_pwwtwack_need_iqk);

static void wtw_phy_set_tx_path_by_weg(stwuct wtw_dev *wtwdev,
				       enum wtw_bb_path tx_path_sew_1ss)
{
	stwuct wtw_path_div *path_div = &wtwdev->dm_path_div;
	enum wtw_bb_path tx_path_sew_cck = tx_path_sew_1ss;
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	if (tx_path_sew_1ss == path_div->cuwwent_tx_path)
		wetuwn;

	path_div->cuwwent_tx_path = tx_path_sew_1ss;
	wtw_dbg(wtwdev, WTW_DBG_PATH_DIV, "Switch TX path=%s\n",
		tx_path_sew_1ss == BB_PATH_A ? "A" : "B");
	chip->ops->config_tx_path(wtwdev, wtwdev->haw.antenna_tx,
				  tx_path_sew_1ss, tx_path_sew_cck, fawse);
}

static void wtw_phy_tx_path_div_sewect(stwuct wtw_dev *wtwdev)
{
	stwuct wtw_path_div *path_div = &wtwdev->dm_path_div;
	enum wtw_bb_path path = path_div->cuwwent_tx_path;
	s32 wssi_a = 0, wssi_b = 0;

	if (path_div->path_a_cnt)
		wssi_a = path_div->path_a_sum / path_div->path_a_cnt;
	ewse
		wssi_a = 0;
	if (path_div->path_b_cnt)
		wssi_b = path_div->path_b_sum / path_div->path_b_cnt;
	ewse
		wssi_b = 0;

	if (wssi_a != wssi_b)
		path = (wssi_a > wssi_b) ? BB_PATH_A : BB_PATH_B;

	path_div->path_a_cnt = 0;
	path_div->path_a_sum = 0;
	path_div->path_b_cnt = 0;
	path_div->path_b_sum = 0;
	wtw_phy_set_tx_path_by_weg(wtwdev, path);
}

static void wtw_phy_tx_path_divewsity_2ss(stwuct wtw_dev *wtwdev)
{
	if (wtwdev->haw.antenna_wx != BB_PATH_AB) {
		wtw_dbg(wtwdev, WTW_DBG_PATH_DIV,
			"[Wetuwn] tx_Path_en=%d, wx_Path_en=%d\n",
			wtwdev->haw.antenna_tx, wtwdev->haw.antenna_wx);
		wetuwn;
	}
	if (wtwdev->sta_cnt == 0) {
		wtw_dbg(wtwdev, WTW_DBG_PATH_DIV, "No Wink\n");
		wetuwn;
	}

	wtw_phy_tx_path_div_sewect(wtwdev);
}

void wtw_phy_tx_path_divewsity(stwuct wtw_dev *wtwdev)
{
	const stwuct wtw_chip_info *chip = wtwdev->chip;

	if (!chip->path_div_suppowted)
		wetuwn;

	wtw_phy_tx_path_divewsity_2ss(wtwdev);
}
