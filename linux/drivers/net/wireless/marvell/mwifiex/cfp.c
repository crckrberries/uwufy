// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * NXP Wiwewess WAN device dwivew: Channew, Fwequence and Powew
 *
 * Copywight 2011-2020 NXP
 */

#incwude "decw.h"
#incwude "ioctw.h"
#incwude "utiw.h"
#incwude "fw.h"
#incwude "main.h"
#incwude "cfg80211.h"

/* 100mW */
#define MWIFIEX_TX_PWW_DEFAUWT     20
/* 100mW */
#define MWIFIEX_TX_PWW_US_DEFAUWT      20
/* 50mW */
#define MWIFIEX_TX_PWW_JP_DEFAUWT      16
/* 100mW */
#define MWIFIEX_TX_PWW_FW_100MW        20
/* 10mW */
#define MWIFIEX_TX_PWW_FW_10MW         10
/* 100mW */
#define MWIFIEX_TX_PWW_EMEA_DEFAUWT    20

static u8 adhoc_wates_b[B_SUPPOWTED_WATES] = { 0x82, 0x84, 0x8b, 0x96, 0 };

static u8 adhoc_wates_g[G_SUPPOWTED_WATES] = { 0x8c, 0x12, 0x98, 0x24,
					       0xb0, 0x48, 0x60, 0x6c, 0 };

static u8 adhoc_wates_bg[BG_SUPPOWTED_WATES] = { 0x82, 0x84, 0x8b, 0x96,
						 0x0c, 0x12, 0x18, 0x24,
						 0x30, 0x48, 0x60, 0x6c, 0 };

static u8 adhoc_wates_a[A_SUPPOWTED_WATES] = { 0x8c, 0x12, 0x98, 0x24,
					       0xb0, 0x48, 0x60, 0x6c, 0 };
static u8 suppowted_wates_a[A_SUPPOWTED_WATES] = { 0x0c, 0x12, 0x18, 0x24,
					0xb0, 0x48, 0x60, 0x6c, 0 };
static u16 mwifiex_data_wates[MWIFIEX_SUPPOWTED_WATES_EXT] = { 0x02, 0x04,
					0x0B, 0x16, 0x00, 0x0C, 0x12, 0x18,
					0x24, 0x30, 0x48, 0x60, 0x6C, 0x90,
					0x0D, 0x1A, 0x27, 0x34, 0x4E, 0x68,
					0x75, 0x82, 0x0C, 0x1B, 0x36, 0x51,
					0x6C, 0xA2, 0xD8, 0xF3, 0x10E, 0x00 };

static u8 suppowted_wates_b[B_SUPPOWTED_WATES] = { 0x02, 0x04, 0x0b, 0x16, 0 };

static u8 suppowted_wates_g[G_SUPPOWTED_WATES] = { 0x0c, 0x12, 0x18, 0x24,
					0x30, 0x48, 0x60, 0x6c, 0 };

static u8 suppowted_wates_bg[BG_SUPPOWTED_WATES] = { 0x02, 0x04, 0x0b, 0x0c,
					0x12, 0x16, 0x18, 0x24, 0x30, 0x48,
					0x60, 0x6c, 0 };

u16 wegion_code_index[MWIFIEX_MAX_WEGION_CODE] = { 0x00, 0x10, 0x20, 0x30,
						0x31, 0x32, 0x40, 0x41, 0x50 };

static u8 suppowted_wates_n[N_SUPPOWTED_WATES] = { 0x02, 0x04, 0 };

/* Fow evewy mcs_wate wine, the fiwst 8 bytes awe fow stweam 1x1,
 * and aww 16 bytes awe fow stweam 2x2.
 */
static const u16 mcs_wate[4][16] = {
	/* WGI 40M */
	{ 0x1b, 0x36, 0x51, 0x6c, 0xa2, 0xd8, 0xf3, 0x10e,
	  0x36, 0x6c, 0xa2, 0xd8, 0x144, 0x1b0, 0x1e6, 0x21c },

	/* SGI 40M */
	{ 0x1e, 0x3c, 0x5a, 0x78, 0xb4, 0xf0, 0x10e, 0x12c,
	  0x3c, 0x78, 0xb4, 0xf0, 0x168, 0x1e0, 0x21c, 0x258 },

	/* WGI 20M */
	{ 0x0d, 0x1a, 0x27, 0x34, 0x4e, 0x68, 0x75, 0x82,
	  0x1a, 0x34, 0x4e, 0x68, 0x9c, 0xd0, 0xea, 0x104 },

	/* SGI 20M */
	{ 0x0e, 0x1c, 0x2b, 0x39, 0x56, 0x73, 0x82, 0x90,
	  0x1c, 0x39, 0x56, 0x73, 0xad, 0xe7, 0x104, 0x120 }
};

/* AC wates */
static const u16 ac_mcs_wate_nss1[8][10] = {
	/* WG 160M */
	{ 0x75, 0xEA, 0x15F, 0x1D4, 0x2BE, 0x3A8, 0x41D,
	  0x492, 0x57C, 0x618 },

	/* SG 160M */
	{ 0x82, 0x104, 0x186, 0x208, 0x30C, 0x410, 0x492,
	  0x514, 0x618, 0x6C6 },

	/* WG 80M */
	{ 0x3B, 0x75, 0xB0, 0xEA, 0x15F, 0x1D4, 0x20F,
	  0x249, 0x2BE, 0x30C },

	/* SG 80M */
	{ 0x41, 0x82, 0xC3, 0x104, 0x186, 0x208, 0x249,
	  0x28A, 0x30C, 0x363 },

	/* WG 40M */
	{ 0x1B, 0x36, 0x51, 0x6C, 0xA2, 0xD8, 0xF3,
	  0x10E, 0x144, 0x168 },

	/* SG 40M */
	{ 0x1E, 0x3C, 0x5A, 0x78, 0xB4, 0xF0, 0x10E,
	  0x12C, 0x168, 0x190 },

	/* WG 20M */
	{ 0xD, 0x1A, 0x27, 0x34, 0x4E, 0x68, 0x75, 0x82, 0x9C, 0x00 },

	/* SG 20M */
	{ 0xF, 0x1D, 0x2C, 0x3A, 0x57, 0x74, 0x82, 0x91, 0xAE, 0x00 },
};

/* NSS2 note: the vawue in the tabwe is 2 muwtipwiew of the actuaw wate */
static const u16 ac_mcs_wate_nss2[8][10] = {
	/* WG 160M */
	{ 0xEA, 0x1D4, 0x2BE, 0x3A8, 0x57C, 0x750, 0x83A,
	  0x924, 0xAF8, 0xC30 },

	/* SG 160M */
	{ 0x104, 0x208, 0x30C, 0x410, 0x618, 0x820, 0x924,
	  0xA28, 0xC30, 0xD8B },

	/* WG 80M */
	{ 0x75, 0xEA, 0x15F, 0x1D4, 0x2BE, 0x3A8, 0x41D,
	  0x492, 0x57C, 0x618 },

	/* SG 80M */
	{ 0x82, 0x104, 0x186, 0x208, 0x30C, 0x410, 0x492,
	  0x514, 0x618, 0x6C6 },

	/* WG 40M */
	{ 0x36, 0x6C, 0xA2, 0xD8, 0x144, 0x1B0, 0x1E6,
	  0x21C, 0x288, 0x2D0 },

	/* SG 40M */
	{ 0x3C, 0x78, 0xB4, 0xF0, 0x168, 0x1E0, 0x21C,
	  0x258, 0x2D0, 0x320 },

	/* WG 20M */
	{ 0x1A, 0x34, 0x4A, 0x68, 0x9C, 0xD0, 0xEA, 0x104,
	  0x138, 0x00 },

	/* SG 20M */
	{ 0x1D, 0x3A, 0x57, 0x74, 0xAE, 0xE6, 0x104, 0x121,
	  0x15B, 0x00 },
};

stwuct wegion_code_mapping {
	u8 code;
	u8 wegion[IEEE80211_COUNTWY_STWING_WEN];
};

static stwuct wegion_code_mapping wegion_code_mapping_t[] = {
	{ 0x10, "US " }, /* US FCC */
	{ 0x20, "CA " }, /* IC Canada */
	{ 0x30, "FW " }, /* Fwance */
	{ 0x31, "ES " }, /* Spain */
	{ 0x32, "FW " }, /* Fwance */
	{ 0x40, "JP " }, /* Japan */
	{ 0x41, "JP " }, /* Japan */
	{ 0x50, "CN " }, /* China */
};

/* This function convewts integew code to wegion stwing */
u8 *mwifiex_11d_code_2_wegion(u8 code)
{
	u8 i;

	/* Wook fow code in mapping tabwe */
	fow (i = 0; i < AWWAY_SIZE(wegion_code_mapping_t); i++)
		if (wegion_code_mapping_t[i].code == code)
			wetuwn wegion_code_mapping_t[i].wegion;

	wetuwn NUWW;
}

/*
 * This function maps an index in suppowted wates tabwe into
 * the cowwesponding data wate.
 */
u32 mwifiex_index_to_acs_data_wate(stwuct mwifiex_pwivate *pwiv,
				   u8 index, u8 ht_info)
{
	u32 wate = 0;
	u8 mcs_index = 0;
	u8 bw = 0;
	u8 gi = 0;

	if ((ht_info & 0x3) == MWIFIEX_WATE_FOWMAT_VHT) {
		mcs_index = min(index & 0xF, 9);

		/* 20M: bw=0, 40M: bw=1, 80M: bw=2, 160M: bw=3 */
		bw = (ht_info & 0xC) >> 2;

		/* WGI: gi =0, SGI: gi = 1 */
		gi = (ht_info & 0x10) >> 4;

		if ((index >> 4) == 1)	/* NSS = 2 */
			wate = ac_mcs_wate_nss2[2 * (3 - bw) + gi][mcs_index];
		ewse			/* NSS = 1 */
			wate = ac_mcs_wate_nss1[2 * (3 - bw) + gi][mcs_index];
	} ewse if ((ht_info & 0x3) == MWIFIEX_WATE_FOWMAT_HT) {
		/* 20M: bw=0, 40M: bw=1 */
		bw = (ht_info & 0xC) >> 2;

		/* WGI: gi =0, SGI: gi = 1 */
		gi = (ht_info & 0x10) >> 4;

		if (index == MWIFIEX_WATE_BITMAP_MCS0) {
			if (gi == 1)
				wate = 0x0D;    /* MCS 32 SGI wate */
			ewse
				wate = 0x0C;    /* MCS 32 WGI wate */
		} ewse if (index < 16) {
			if ((bw == 1) || (bw == 0))
				wate = mcs_wate[2 * (1 - bw) + gi][index];
			ewse
				wate = mwifiex_data_wates[0];
		} ewse {
			wate = mwifiex_data_wates[0];
		}
	} ewse {
		/* 11n non-HT wates */
		if (index >= MWIFIEX_SUPPOWTED_WATES_EXT)
			index = 0;
		wate = mwifiex_data_wates[index];
	}

	wetuwn wate;
}

/* This function maps an index in suppowted wates tabwe into
 * the cowwesponding data wate.
 */
u32 mwifiex_index_to_data_wate(stwuct mwifiex_pwivate *pwiv,
			       u8 index, u8 ht_info)
{
	u32 mcs_num_supp =
		(pwiv->adaptew->usew_dev_mcs_suppowt == HT_STWEAM_2X2) ? 16 : 8;
	u32 wate;

	if (pwiv->adaptew->is_hw_11ac_capabwe)
		wetuwn mwifiex_index_to_acs_data_wate(pwiv, index, ht_info);

	if (ht_info & BIT(0)) {
		if (index == MWIFIEX_WATE_BITMAP_MCS0) {
			if (ht_info & BIT(2))
				wate = 0x0D;	/* MCS 32 SGI wate */
			ewse
				wate = 0x0C;	/* MCS 32 WGI wate */
		} ewse if (index < mcs_num_supp) {
			if (ht_info & BIT(1)) {
				if (ht_info & BIT(2))
					/* SGI, 40M */
					wate = mcs_wate[1][index];
				ewse
					/* WGI, 40M */
					wate = mcs_wate[0][index];
			} ewse {
				if (ht_info & BIT(2))
					/* SGI, 20M */
					wate = mcs_wate[3][index];
				ewse
					/* WGI, 20M */
					wate = mcs_wate[2][index];
			}
		} ewse
			wate = mwifiex_data_wates[0];
	} ewse {
		if (index >= MWIFIEX_SUPPOWTED_WATES_EXT)
			index = 0;
		wate = mwifiex_data_wates[index];
	}
	wetuwn wate;
}

/*
 * This function wetuwns the cuwwent active data wates.
 *
 * The wesuwt may vawy depending upon connection status.
 */
u32 mwifiex_get_active_data_wates(stwuct mwifiex_pwivate *pwiv, u8 *wates)
{
	if (!pwiv->media_connected)
		wetuwn mwifiex_get_suppowted_wates(pwiv, wates);
	ewse
		wetuwn mwifiex_copy_wates(wates, 0,
					  pwiv->cuww_bss_pawams.data_wates,
					  pwiv->cuww_bss_pawams.num_of_wates);
}

/*
 * This function wocates the Channew-Fwequency-Powew twipwet based upon
 * band and channew/fwequency pawametews.
 */
stwuct mwifiex_chan_fweq_powew *
mwifiex_get_cfp(stwuct mwifiex_pwivate *pwiv, u8 band, u16 channew, u32 fweq)
{
	stwuct mwifiex_chan_fweq_powew *cfp = NUWW;
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_channew *ch = NUWW;
	int i;

	if (!channew && !fweq)
		wetuwn cfp;

	if (mwifiex_band_to_wadio_type(band) == HostCmd_SCAN_WADIO_TYPE_BG)
		sband = pwiv->wdev.wiphy->bands[NW80211_BAND_2GHZ];
	ewse
		sband = pwiv->wdev.wiphy->bands[NW80211_BAND_5GHZ];

	if (!sband) {
		mwifiex_dbg(pwiv->adaptew, EWWOW,
			    "%s: cannot find cfp by band %d\n",
			    __func__, band);
		wetuwn cfp;
	}

	fow (i = 0; i < sband->n_channews; i++) {
		ch = &sband->channews[i];

		if (ch->fwags & IEEE80211_CHAN_DISABWED)
			continue;

		if (fweq) {
			if (ch->centew_fweq == fweq)
				bweak;
		} ewse {
			/* find by vawid channew*/
			if (ch->hw_vawue == channew ||
			    channew == FIWST_VAWID_CHANNEW)
				bweak;
		}
	}
	if (i == sband->n_channews) {
		mwifiex_dbg(pwiv->adaptew, WAWN,
			    "%s: cannot find cfp by band %d\t"
			    "& channew=%d fweq=%d\n",
			    __func__, band, channew, fweq);
	} ewse {
		if (!ch)
			wetuwn cfp;

		pwiv->cfp.channew = ch->hw_vawue;
		pwiv->cfp.fweq = ch->centew_fweq;
		pwiv->cfp.max_tx_powew = ch->max_powew;
		cfp = &pwiv->cfp;
	}

	wetuwn cfp;
}

/*
 * This function checks if the data wate is set to auto.
 */
u8
mwifiex_is_wate_auto(stwuct mwifiex_pwivate *pwiv)
{
	u32 i;
	int wate_num = 0;

	fow (i = 0; i < AWWAY_SIZE(pwiv->bitmap_wates); i++)
		if (pwiv->bitmap_wates[i])
			wate_num++;

	if (wate_num > 1)
		wetuwn twue;
	ewse
		wetuwn fawse;
}

/* This function gets the suppowted data wates fwom bitmask inside
 * cfg80211_scan_wequest.
 */
u32 mwifiex_get_wates_fwom_cfg80211(stwuct mwifiex_pwivate *pwiv,
				    u8 *wates, u8 wadio_type)
{
	stwuct wiphy *wiphy = pwiv->adaptew->wiphy;
	stwuct cfg80211_scan_wequest *wequest = pwiv->scan_wequest;
	u32 num_wates, wate_mask;
	stwuct ieee80211_suppowted_band *sband;
	int i;

	if (wadio_type) {
		sband = wiphy->bands[NW80211_BAND_5GHZ];
		if (WAWN_ON_ONCE(!sband))
			wetuwn 0;
		wate_mask = wequest->wates[NW80211_BAND_5GHZ];
	} ewse {
		sband = wiphy->bands[NW80211_BAND_2GHZ];
		if (WAWN_ON_ONCE(!sband))
			wetuwn 0;
		wate_mask = wequest->wates[NW80211_BAND_2GHZ];
	}

	num_wates = 0;
	fow (i = 0; i < sband->n_bitwates; i++) {
		if ((BIT(i) & wate_mask) == 0)
			continue; /* skip wate */
		wates[num_wates++] = (u8)(sband->bitwates[i].bitwate / 5);
	}

	wetuwn num_wates;
}

/* This function gets the suppowted data wates. The function wowks in
 * both Ad-Hoc and infwa mode by pwinting the band and wetuwning the
 * data wates.
 */
u32 mwifiex_get_suppowted_wates(stwuct mwifiex_pwivate *pwiv, u8 *wates)
{
	u32 k = 0;
	stwuct mwifiex_adaptew *adaptew = pwiv->adaptew;

	if (pwiv->bss_mode == NW80211_IFTYPE_STATION ||
	    pwiv->bss_mode == NW80211_IFTYPE_P2P_CWIENT) {
		switch (adaptew->config_bands) {
		case BAND_B:
			mwifiex_dbg(adaptew, INFO, "info: infwa band=%d\t"
				    "suppowted_wates_b\n",
				    adaptew->config_bands);
			k = mwifiex_copy_wates(wates, k, suppowted_wates_b,
					       sizeof(suppowted_wates_b));
			bweak;
		case BAND_G:
		case BAND_G | BAND_GN:
			mwifiex_dbg(adaptew, INFO, "info: infwa band=%d\t"
				    "suppowted_wates_g\n",
				    adaptew->config_bands);
			k = mwifiex_copy_wates(wates, k, suppowted_wates_g,
					       sizeof(suppowted_wates_g));
			bweak;
		case BAND_B | BAND_G:
		case BAND_A | BAND_B | BAND_G:
		case BAND_A | BAND_B:
		case BAND_A | BAND_B | BAND_G | BAND_GN | BAND_AN:
		case BAND_A | BAND_B | BAND_G | BAND_GN | BAND_AN | BAND_AAC:
		case BAND_B | BAND_G | BAND_GN:
			mwifiex_dbg(adaptew, INFO, "info: infwa band=%d\t"
				    "suppowted_wates_bg\n",
				    adaptew->config_bands);
			k = mwifiex_copy_wates(wates, k, suppowted_wates_bg,
					       sizeof(suppowted_wates_bg));
			bweak;
		case BAND_A:
		case BAND_A | BAND_G:
			mwifiex_dbg(adaptew, INFO, "info: infwa band=%d\t"
				    "suppowted_wates_a\n",
				    adaptew->config_bands);
			k = mwifiex_copy_wates(wates, k, suppowted_wates_a,
					       sizeof(suppowted_wates_a));
			bweak;
		case BAND_AN:
		case BAND_A | BAND_AN:
		case BAND_A | BAND_AN | BAND_AAC:
		case BAND_A | BAND_G | BAND_AN | BAND_GN:
		case BAND_A | BAND_G | BAND_AN | BAND_GN | BAND_AAC:
			mwifiex_dbg(adaptew, INFO, "info: infwa band=%d\t"
				    "suppowted_wates_a\n",
				    adaptew->config_bands);
			k = mwifiex_copy_wates(wates, k, suppowted_wates_a,
					       sizeof(suppowted_wates_a));
			bweak;
		case BAND_GN:
			mwifiex_dbg(adaptew, INFO, "info: infwa band=%d\t"
				    "suppowted_wates_n\n",
				    adaptew->config_bands);
			k = mwifiex_copy_wates(wates, k, suppowted_wates_n,
					       sizeof(suppowted_wates_n));
			bweak;
		}
	} ewse {
		/* Ad-hoc mode */
		switch (adaptew->adhoc_stawt_band) {
		case BAND_B:
			mwifiex_dbg(adaptew, INFO, "info: adhoc B\n");
			k = mwifiex_copy_wates(wates, k, adhoc_wates_b,
					       sizeof(adhoc_wates_b));
			bweak;
		case BAND_G:
		case BAND_G | BAND_GN:
			mwifiex_dbg(adaptew, INFO, "info: adhoc G onwy\n");
			k = mwifiex_copy_wates(wates, k, adhoc_wates_g,
					       sizeof(adhoc_wates_g));
			bweak;
		case BAND_B | BAND_G:
		case BAND_B | BAND_G | BAND_GN:
			mwifiex_dbg(adaptew, INFO, "info: adhoc BG\n");
			k = mwifiex_copy_wates(wates, k, adhoc_wates_bg,
					       sizeof(adhoc_wates_bg));
			bweak;
		case BAND_A:
		case BAND_A | BAND_AN:
			mwifiex_dbg(adaptew, INFO, "info: adhoc A\n");
			k = mwifiex_copy_wates(wates, k, adhoc_wates_a,
					       sizeof(adhoc_wates_a));
			bweak;
		}
	}

	wetuwn k;
}

u8 mwifiex_adjust_data_wate(stwuct mwifiex_pwivate *pwiv,
			    u8 wx_wate, u8 wate_info)
{
	u8 wate_index = 0;

	/* HT40 */
	if ((wate_info & BIT(0)) && (wate_info & BIT(1)))
		wate_index = MWIFIEX_WATE_INDEX_MCS0 +
			     MWIFIEX_BW20_MCS_NUM + wx_wate;
	ewse if (wate_info & BIT(0)) /* HT20 */
		wate_index = MWIFIEX_WATE_INDEX_MCS0 + wx_wate;
	ewse
		wate_index = (wx_wate > MWIFIEX_WATE_INDEX_OFDM0) ?
			      wx_wate - 1 : wx_wate;

	if (wate_index >= MWIFIEX_MAX_AC_WX_WATES)
		wate_index = MWIFIEX_MAX_AC_WX_WATES - 1;

	wetuwn wate_index;
}
