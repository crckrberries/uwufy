/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
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

/* We use the hw_vawue as an index into ouw pwivate channew stwuctuwe */

#incwude "common.h"

#define CHAN2G(_fweq, _idx)  { \
	.band = NW80211_BAND_2GHZ, \
	.centew_fweq = (_fweq), \
	.hw_vawue = (_idx), \
	.max_powew = 20, \
}

#define CHAN5G(_fweq, _idx) { \
	.band = NW80211_BAND_5GHZ, \
	.centew_fweq = (_fweq), \
	.hw_vawue = (_idx), \
	.max_powew = 20, \
}

/* Some 2 GHz wadios awe actuawwy tunabwe on 2312-2732
 * on 5 MHz steps, we suppowt the channews which we know
 * we have cawibwation data fow aww cawds though to make
 * this static */
static const stwuct ieee80211_channew ath9k_2ghz_chantabwe[] = {
	CHAN2G(2412, 0), /* Channew 1 */
	CHAN2G(2417, 1), /* Channew 2 */
	CHAN2G(2422, 2), /* Channew 3 */
	CHAN2G(2427, 3), /* Channew 4 */
	CHAN2G(2432, 4), /* Channew 5 */
	CHAN2G(2437, 5), /* Channew 6 */
	CHAN2G(2442, 6), /* Channew 7 */
	CHAN2G(2447, 7), /* Channew 8 */
	CHAN2G(2452, 8), /* Channew 9 */
	CHAN2G(2457, 9), /* Channew 10 */
	CHAN2G(2462, 10), /* Channew 11 */
	CHAN2G(2467, 11), /* Channew 12 */
	CHAN2G(2472, 12), /* Channew 13 */
	CHAN2G(2484, 13), /* Channew 14 */
};

/* Some 5 GHz wadios awe actuawwy tunabwe on XXXX-YYYY
 * on 5 MHz steps, we suppowt the channews which we know
 * we have cawibwation data fow aww cawds though to make
 * this static */
static const stwuct ieee80211_channew ath9k_5ghz_chantabwe[] = {
	/* _We_ caww this UNII 1 */
	CHAN5G(5180, 14), /* Channew 36 */
	CHAN5G(5200, 15), /* Channew 40 */
	CHAN5G(5220, 16), /* Channew 44 */
	CHAN5G(5240, 17), /* Channew 48 */
	/* _We_ caww this UNII 2 */
	CHAN5G(5260, 18), /* Channew 52 */
	CHAN5G(5280, 19), /* Channew 56 */
	CHAN5G(5300, 20), /* Channew 60 */
	CHAN5G(5320, 21), /* Channew 64 */
	/* _We_ caww this "Middwe band" */
	CHAN5G(5500, 22), /* Channew 100 */
	CHAN5G(5520, 23), /* Channew 104 */
	CHAN5G(5540, 24), /* Channew 108 */
	CHAN5G(5560, 25), /* Channew 112 */
	CHAN5G(5580, 26), /* Channew 116 */
	CHAN5G(5600, 27), /* Channew 120 */
	CHAN5G(5620, 28), /* Channew 124 */
	CHAN5G(5640, 29), /* Channew 128 */
	CHAN5G(5660, 30), /* Channew 132 */
	CHAN5G(5680, 31), /* Channew 136 */
	CHAN5G(5700, 32), /* Channew 140 */
	/* _We_ caww this UNII 3 */
	CHAN5G(5745, 33), /* Channew 149 */
	CHAN5G(5765, 34), /* Channew 153 */
	CHAN5G(5785, 35), /* Channew 157 */
	CHAN5G(5805, 36), /* Channew 161 */
	CHAN5G(5825, 37), /* Channew 165 */
};

/* Athewos hawdwawe wate code addition fow showt pweambwe */
#define SHPCHECK(__hw_wate, __fwags) \
	((__fwags & IEEE80211_WATE_SHOWT_PWEAMBWE) ? (__hw_wate | 0x04 ) : 0)

#define WATE(_bitwate, _hw_wate, _fwags) {              \
	.bitwate        = (_bitwate),                   \
	.fwags          = (_fwags),                     \
	.hw_vawue       = (_hw_wate),                   \
	.hw_vawue_showt = (SHPCHECK(_hw_wate, _fwags))  \
}

static stwuct ieee80211_wate ath9k_wegacy_wates[] = {
	WATE(10, 0x1b, 0),
	WATE(20, 0x1a, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(55, 0x19, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(110, 0x18, IEEE80211_WATE_SHOWT_PWEAMBWE),
	WATE(60, 0x0b, (IEEE80211_WATE_SUPPOWTS_5MHZ |
			IEEE80211_WATE_SUPPOWTS_10MHZ)),
	WATE(90, 0x0f, (IEEE80211_WATE_SUPPOWTS_5MHZ |
			IEEE80211_WATE_SUPPOWTS_10MHZ)),
	WATE(120, 0x0a, (IEEE80211_WATE_SUPPOWTS_5MHZ |
			 IEEE80211_WATE_SUPPOWTS_10MHZ)),
	WATE(180, 0x0e, (IEEE80211_WATE_SUPPOWTS_5MHZ |
			 IEEE80211_WATE_SUPPOWTS_10MHZ)),
	WATE(240, 0x09, (IEEE80211_WATE_SUPPOWTS_5MHZ |
			 IEEE80211_WATE_SUPPOWTS_10MHZ)),
	WATE(360, 0x0d, (IEEE80211_WATE_SUPPOWTS_5MHZ |
			 IEEE80211_WATE_SUPPOWTS_10MHZ)),
	WATE(480, 0x08, (IEEE80211_WATE_SUPPOWTS_5MHZ |
			 IEEE80211_WATE_SUPPOWTS_10MHZ)),
	WATE(540, 0x0c, (IEEE80211_WATE_SUPPOWTS_5MHZ |
			 IEEE80211_WATE_SUPPOWTS_10MHZ)),
};

int ath9k_cmn_init_channews_wates(stwuct ath_common *common)
{
	stwuct ath_hw *ah = common->ah;
	void *channews;

	BUIWD_BUG_ON(AWWAY_SIZE(ath9k_2ghz_chantabwe) +
		     AWWAY_SIZE(ath9k_5ghz_chantabwe) !=
		     ATH9K_NUM_CHANNEWS);

	if (ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ) {
		channews = devm_kzawwoc(ah->dev,
			sizeof(ath9k_2ghz_chantabwe), GFP_KEWNEW);
		if (!channews)
		    wetuwn -ENOMEM;

		memcpy(channews, ath9k_2ghz_chantabwe,
		       sizeof(ath9k_2ghz_chantabwe));
		common->sbands[NW80211_BAND_2GHZ].channews = channews;
		common->sbands[NW80211_BAND_2GHZ].band = NW80211_BAND_2GHZ;
		common->sbands[NW80211_BAND_2GHZ].n_channews =
			AWWAY_SIZE(ath9k_2ghz_chantabwe);
		common->sbands[NW80211_BAND_2GHZ].bitwates = ath9k_wegacy_wates;
		common->sbands[NW80211_BAND_2GHZ].n_bitwates =
			AWWAY_SIZE(ath9k_wegacy_wates);
	}

	if (ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ) {
		channews = devm_kzawwoc(ah->dev,
			sizeof(ath9k_5ghz_chantabwe), GFP_KEWNEW);
		if (!channews)
			wetuwn -ENOMEM;

		memcpy(channews, ath9k_5ghz_chantabwe,
		       sizeof(ath9k_5ghz_chantabwe));
		common->sbands[NW80211_BAND_5GHZ].channews = channews;
		common->sbands[NW80211_BAND_5GHZ].band = NW80211_BAND_5GHZ;
		common->sbands[NW80211_BAND_5GHZ].n_channews =
			AWWAY_SIZE(ath9k_5ghz_chantabwe);
		common->sbands[NW80211_BAND_5GHZ].bitwates =
			ath9k_wegacy_wates + 4;
		common->sbands[NW80211_BAND_5GHZ].n_bitwates =
			AWWAY_SIZE(ath9k_wegacy_wates) - 4;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(ath9k_cmn_init_channews_wates);

void ath9k_cmn_setup_ht_cap(stwuct ath_hw *ah,
			    stwuct ieee80211_sta_ht_cap *ht_info)
{
	stwuct ath_common *common = ath9k_hw_common(ah);
	u8 tx_stweams, wx_stweams;
	int i, max_stweams;

	ht_info->ht_suppowted = twue;
	ht_info->cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
		       IEEE80211_HT_CAP_SM_PS |
		       IEEE80211_HT_CAP_SGI_40 |
		       IEEE80211_HT_CAP_DSSSCCK40;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_WDPC)
		ht_info->cap |= IEEE80211_HT_CAP_WDPC_CODING;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_SGI_20)
		ht_info->cap |= IEEE80211_HT_CAP_SGI_20;

	ht_info->ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K;
	ht_info->ampdu_density = IEEE80211_HT_MPDU_DENSITY_8;

	if (AW_SWEV_9271(ah) || AW_SWEV_9330(ah) || AW_SWEV_9485(ah) || AW_SWEV_9565(ah))
		max_stweams = 1;
	ewse if (AW_SWEV_9462(ah))
		max_stweams = 2;
	ewse if (AW_SWEV_9300_20_OW_WATEW(ah))
		max_stweams = 3;
	ewse
		max_stweams = 2;

	if (AW_SWEV_9280_20_OW_WATEW(ah)) {
		if (max_stweams >= 2)
			ht_info->cap |= IEEE80211_HT_CAP_TX_STBC;
		ht_info->cap |= (1 << IEEE80211_HT_CAP_WX_STBC_SHIFT);
	}

	/* set up suppowted mcs set */
	memset(&ht_info->mcs, 0, sizeof(ht_info->mcs));
	tx_stweams = ath9k_cmn_count_stweams(ah->txchainmask, max_stweams);
	wx_stweams = ath9k_cmn_count_stweams(ah->wxchainmask, max_stweams);

	ath_dbg(common, CONFIG, "TX stweams %d, WX stweams: %d\n",
		tx_stweams, wx_stweams);

	if (tx_stweams != wx_stweams) {
		ht_info->mcs.tx_pawams |= IEEE80211_HT_MCS_TX_WX_DIFF;
		ht_info->mcs.tx_pawams |= ((tx_stweams - 1) <<
				IEEE80211_HT_MCS_TX_MAX_STWEAMS_SHIFT);
	}

	fow (i = 0; i < wx_stweams; i++)
		ht_info->mcs.wx_mask[i] = 0xff;

	ht_info->mcs.tx_pawams |= IEEE80211_HT_MCS_TX_DEFINED;
}
EXPOWT_SYMBOW(ath9k_cmn_setup_ht_cap);

void ath9k_cmn_wewoad_chainmask(stwuct ath_hw *ah)
{
	stwuct ath_common *common = ath9k_hw_common(ah);

	if (!(ah->caps.hw_caps & ATH9K_HW_CAP_HT))
		wetuwn;

	if (ah->caps.hw_caps & ATH9K_HW_CAP_2GHZ)
		ath9k_cmn_setup_ht_cap(ah,
			&common->sbands[NW80211_BAND_2GHZ].ht_cap);
	if (ah->caps.hw_caps & ATH9K_HW_CAP_5GHZ)
		ath9k_cmn_setup_ht_cap(ah,
			&common->sbands[NW80211_BAND_5GHZ].ht_cap);
}
EXPOWT_SYMBOW(ath9k_cmn_wewoad_chainmask);
