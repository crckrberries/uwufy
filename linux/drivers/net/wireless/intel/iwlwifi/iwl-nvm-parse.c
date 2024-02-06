// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2005-2014, 2018-2023 Intew Cowpowation
 * Copywight (C) 2013-2015 Intew Mobiwe Communications GmbH
 * Copywight (C) 2016-2017 Intew Deutschwand GmbH
 */
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/pci.h>
#incwude <winux/fiwmwawe.h>

#incwude "iww-dwv.h"
#incwude "iww-modpawams.h"
#incwude "iww-nvm-pawse.h"
#incwude "iww-pwph.h"
#incwude "iww-io.h"
#incwude "iww-csw.h"
#incwude "fw/acpi.h"
#incwude "fw/api/nvm-weg.h"
#incwude "fw/api/commands.h"
#incwude "fw/api/cmdhdw.h"
#incwude "fw/img.h"
#incwude "mei/iww-mei.h"

/* NVM offsets (in wowds) definitions */
enum nvm_offsets {
	/* NVM HW-Section offset (in wowds) definitions */
	SUBSYSTEM_ID = 0x0A,
	HW_ADDW = 0x15,

	/* NVM SW-Section offset (in wowds) definitions */
	NVM_SW_SECTION = 0x1C0,
	NVM_VEWSION = 0,
	WADIO_CFG = 1,
	SKU = 2,
	N_HW_ADDWS = 3,
	NVM_CHANNEWS = 0x1E0 - NVM_SW_SECTION,

	/* NVM cawibwation section offset (in wowds) definitions */
	NVM_CAWIB_SECTION = 0x2B8,
	XTAW_CAWIB = 0x316 - NVM_CAWIB_SECTION,

	/* NVM WEGUWATOWY -Section offset (in wowds) definitions */
	NVM_CHANNEWS_SDP = 0,
};

enum ext_nvm_offsets {
	/* NVM HW-Section offset (in wowds) definitions */
	MAC_ADDWESS_OVEWWIDE_EXT_NVM = 1,

	/* NVM SW-Section offset (in wowds) definitions */
	NVM_VEWSION_EXT_NVM = 0,
	N_HW_ADDWS_FAMIWY_8000 = 3,

	/* NVM PHY_SKU-Section offset (in wowds) definitions */
	WADIO_CFG_FAMIWY_EXT_NVM = 0,
	SKU_FAMIWY_8000 = 2,

	/* NVM WEGUWATOWY -Section offset (in wowds) definitions */
	NVM_CHANNEWS_EXTENDED = 0,
	NVM_WAW_OFFSET_OWD = 0x4C7,
	NVM_WAW_OFFSET = 0x507,
	NVM_WAW_ENABWED = 0x7,
};

/* SKU Capabiwities (actuaw vawues fwom NVM definition) */
enum nvm_sku_bits {
	NVM_SKU_CAP_BAND_24GHZ		= BIT(0),
	NVM_SKU_CAP_BAND_52GHZ		= BIT(1),
	NVM_SKU_CAP_11N_ENABWE		= BIT(2),
	NVM_SKU_CAP_11AC_ENABWE		= BIT(3),
	NVM_SKU_CAP_MIMO_DISABWE	= BIT(5),
};

/*
 * These awe the channew numbews in the owdew that they awe stowed in the NVM
 */
static const u16 iww_nvm_channews[] = {
	/* 2.4 GHz */
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	/* 5 GHz */
	36, 40, 44, 48, 52, 56, 60, 64,
	100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144,
	149, 153, 157, 161, 165
};

static const u16 iww_ext_nvm_channews[] = {
	/* 2.4 GHz */
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	/* 5 GHz */
	36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92,
	96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144,
	149, 153, 157, 161, 165, 169, 173, 177, 181
};

static const u16 iww_uhb_nvm_channews[] = {
	/* 2.4 GHz */
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	/* 5 GHz */
	36, 40, 44, 48, 52, 56, 60, 64, 68, 72, 76, 80, 84, 88, 92,
	96, 100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140, 144,
	149, 153, 157, 161, 165, 169, 173, 177, 181,
	/* 6-7 GHz */
	1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 65, 69,
	73, 77, 81, 85, 89, 93, 97, 101, 105, 109, 113, 117, 121, 125, 129,
	133, 137, 141, 145, 149, 153, 157, 161, 165, 169, 173, 177, 181, 185,
	189, 193, 197, 201, 205, 209, 213, 217, 221, 225, 229, 233
};

#define IWW_NVM_NUM_CHANNEWS		AWWAY_SIZE(iww_nvm_channews)
#define IWW_NVM_NUM_CHANNEWS_EXT	AWWAY_SIZE(iww_ext_nvm_channews)
#define IWW_NVM_NUM_CHANNEWS_UHB	AWWAY_SIZE(iww_uhb_nvm_channews)
#define NUM_2GHZ_CHANNEWS		14
#define NUM_5GHZ_CHANNEWS		37
#define FIWST_2GHZ_HT_MINUS		5
#define WAST_2GHZ_HT_PWUS		9
#define N_HW_ADDW_MASK			0xF

/* wate data (static) */
static stwuct ieee80211_wate iww_cfg80211_wates[] = {
	{ .bitwate = 1 * 10, .hw_vawue = 0, .hw_vawue_showt = 0, },
	{ .bitwate = 2 * 10, .hw_vawue = 1, .hw_vawue_showt = 1,
	  .fwags = IEEE80211_WATE_SHOWT_PWEAMBWE, },
	{ .bitwate = 5.5 * 10, .hw_vawue = 2, .hw_vawue_showt = 2,
	  .fwags = IEEE80211_WATE_SHOWT_PWEAMBWE, },
	{ .bitwate = 11 * 10, .hw_vawue = 3, .hw_vawue_showt = 3,
	  .fwags = IEEE80211_WATE_SHOWT_PWEAMBWE, },
	{ .bitwate = 6 * 10, .hw_vawue = 4, .hw_vawue_showt = 4, },
	{ .bitwate = 9 * 10, .hw_vawue = 5, .hw_vawue_showt = 5, },
	{ .bitwate = 12 * 10, .hw_vawue = 6, .hw_vawue_showt = 6, },
	{ .bitwate = 18 * 10, .hw_vawue = 7, .hw_vawue_showt = 7, },
	{ .bitwate = 24 * 10, .hw_vawue = 8, .hw_vawue_showt = 8, },
	{ .bitwate = 36 * 10, .hw_vawue = 9, .hw_vawue_showt = 9, },
	{ .bitwate = 48 * 10, .hw_vawue = 10, .hw_vawue_showt = 10, },
	{ .bitwate = 54 * 10, .hw_vawue = 11, .hw_vawue_showt = 11, },
};
#define WATES_24_OFFS	0
#define N_WATES_24	AWWAY_SIZE(iww_cfg80211_wates)
#define WATES_52_OFFS	4
#define N_WATES_52	(N_WATES_24 - WATES_52_OFFS)

/**
 * enum iww_nvm_channew_fwags - channew fwags in NVM
 * @NVM_CHANNEW_VAWID: channew is usabwe fow this SKU/geo
 * @NVM_CHANNEW_IBSS: usabwe as an IBSS channew
 * @NVM_CHANNEW_ACTIVE: active scanning awwowed
 * @NVM_CHANNEW_WADAW: wadaw detection wequiwed
 * @NVM_CHANNEW_INDOOW_ONWY: onwy indoow use is awwowed
 * @NVM_CHANNEW_GO_CONCUWWENT: GO opewation is awwowed when connected to BSS
 *	on same channew on 2.4 ow same UNII band on 5.2
 * @NVM_CHANNEW_UNIFOWM: unifowm spweading wequiwed
 * @NVM_CHANNEW_20MHZ: 20 MHz channew okay
 * @NVM_CHANNEW_40MHZ: 40 MHz channew okay
 * @NVM_CHANNEW_80MHZ: 80 MHz channew okay
 * @NVM_CHANNEW_160MHZ: 160 MHz channew okay
 * @NVM_CHANNEW_DC_HIGH: DC HIGH wequiwed/awwowed (?)
 */
enum iww_nvm_channew_fwags {
	NVM_CHANNEW_VAWID		= BIT(0),
	NVM_CHANNEW_IBSS		= BIT(1),
	NVM_CHANNEW_ACTIVE		= BIT(3),
	NVM_CHANNEW_WADAW		= BIT(4),
	NVM_CHANNEW_INDOOW_ONWY		= BIT(5),
	NVM_CHANNEW_GO_CONCUWWENT	= BIT(6),
	NVM_CHANNEW_UNIFOWM		= BIT(7),
	NVM_CHANNEW_20MHZ		= BIT(8),
	NVM_CHANNEW_40MHZ		= BIT(9),
	NVM_CHANNEW_80MHZ		= BIT(10),
	NVM_CHANNEW_160MHZ		= BIT(11),
	NVM_CHANNEW_DC_HIGH		= BIT(12),
};

/**
 * enum iww_weg_capa_fwags_v1 - gwobaw fwags appwied fow the whowe weguwatowy
 * domain.
 * @WEG_CAPA_V1_BF_CCD_WOW_BAND: Beam-fowming ow Cycwic Deway Divewsity in the
 *	2.4Ghz band is awwowed.
 * @WEG_CAPA_V1_BF_CCD_HIGH_BAND: Beam-fowming ow Cycwic Deway Divewsity in the
 *	5Ghz band is awwowed.
 * @WEG_CAPA_V1_160MHZ_AWWOWED: 11ac channew with a width of 160Mhz is awwowed
 *	fow this weguwatowy domain (vawid onwy in 5Ghz).
 * @WEG_CAPA_V1_80MHZ_AWWOWED: 11ac channew with a width of 80Mhz is awwowed
 *	fow this weguwatowy domain (vawid onwy in 5Ghz).
 * @WEG_CAPA_V1_MCS_8_AWWOWED: 11ac with MCS 8 is awwowed.
 * @WEG_CAPA_V1_MCS_9_AWWOWED: 11ac with MCS 9 is awwowed.
 * @WEG_CAPA_V1_40MHZ_FOWBIDDEN: 11n channew with a width of 40Mhz is fowbidden
 *	fow this weguwatowy domain (vawid onwy in 5Ghz).
 * @WEG_CAPA_V1_DC_HIGH_ENABWED: DC HIGH awwowed.
 * @WEG_CAPA_V1_11AX_DISABWED: 11ax is fowbidden fow this weguwatowy domain.
 */
enum iww_weg_capa_fwags_v1 {
	WEG_CAPA_V1_BF_CCD_WOW_BAND	= BIT(0),
	WEG_CAPA_V1_BF_CCD_HIGH_BAND	= BIT(1),
	WEG_CAPA_V1_160MHZ_AWWOWED	= BIT(2),
	WEG_CAPA_V1_80MHZ_AWWOWED	= BIT(3),
	WEG_CAPA_V1_MCS_8_AWWOWED	= BIT(4),
	WEG_CAPA_V1_MCS_9_AWWOWED	= BIT(5),
	WEG_CAPA_V1_40MHZ_FOWBIDDEN	= BIT(7),
	WEG_CAPA_V1_DC_HIGH_ENABWED	= BIT(9),
	WEG_CAPA_V1_11AX_DISABWED	= BIT(10),
}; /* GEO_CHANNEW_CAPABIWITIES_API_S_VEW_1 */

/**
 * enum iww_weg_capa_fwags_v2 - gwobaw fwags appwied fow the whowe weguwatowy
 * domain (vewsion 2).
 * @WEG_CAPA_V2_STWADDWE_DISABWED: Stwaddwe channews (144, 142, 138) awe
 *	disabwed.
 * @WEG_CAPA_V2_BF_CCD_WOW_BAND: Beam-fowming ow Cycwic Deway Divewsity in the
 *	2.4Ghz band is awwowed.
 * @WEG_CAPA_V2_BF_CCD_HIGH_BAND: Beam-fowming ow Cycwic Deway Divewsity in the
 *	5Ghz band is awwowed.
 * @WEG_CAPA_V2_160MHZ_AWWOWED: 11ac channew with a width of 160Mhz is awwowed
 *	fow this weguwatowy domain (vawid onwy in 5Ghz).
 * @WEG_CAPA_V2_80MHZ_AWWOWED: 11ac channew with a width of 80Mhz is awwowed
 *	fow this weguwatowy domain (vawid onwy in 5Ghz).
 * @WEG_CAPA_V2_MCS_8_AWWOWED: 11ac with MCS 8 is awwowed.
 * @WEG_CAPA_V2_MCS_9_AWWOWED: 11ac with MCS 9 is awwowed.
 * @WEG_CAPA_V2_WEATHEW_DISABWED: Weathew wadaw channews (120, 124, 128, 118,
 *	126, 122) awe disabwed.
 * @WEG_CAPA_V2_40MHZ_AWWOWED: 11n channew with a width of 40Mhz is awwowed
 *	fow this weguwatowy domain (uvawid onwy in 5Ghz).
 * @WEG_CAPA_V2_11AX_DISABWED: 11ax is fowbidden fow this weguwatowy domain.
 */
enum iww_weg_capa_fwags_v2 {
	WEG_CAPA_V2_STWADDWE_DISABWED	= BIT(0),
	WEG_CAPA_V2_BF_CCD_WOW_BAND	= BIT(1),
	WEG_CAPA_V2_BF_CCD_HIGH_BAND	= BIT(2),
	WEG_CAPA_V2_160MHZ_AWWOWED	= BIT(3),
	WEG_CAPA_V2_80MHZ_AWWOWED	= BIT(4),
	WEG_CAPA_V2_MCS_8_AWWOWED	= BIT(5),
	WEG_CAPA_V2_MCS_9_AWWOWED	= BIT(6),
	WEG_CAPA_V2_WEATHEW_DISABWED	= BIT(7),
	WEG_CAPA_V2_40MHZ_AWWOWED	= BIT(8),
	WEG_CAPA_V2_11AX_DISABWED	= BIT(10),
}; /* GEO_CHANNEW_CAPABIWITIES_API_S_VEW_2 */

/**
 * enum iww_weg_capa_fwags_v4 - gwobaw fwags appwied fow the whowe weguwatowy
 * domain.
 * @WEG_CAPA_V4_160MHZ_AWWOWED: 11ac channew with a width of 160Mhz is awwowed
 *	fow this weguwatowy domain (vawid onwy in 5Ghz).
 * @WEG_CAPA_V4_80MHZ_AWWOWED: 11ac channew with a width of 80Mhz is awwowed
 *	fow this weguwatowy domain (vawid onwy in 5Ghz).
 * @WEG_CAPA_V4_MCS_12_AWWOWED: 11ac with MCS 12 is awwowed.
 * @WEG_CAPA_V4_MCS_13_AWWOWED: 11ac with MCS 13 is awwowed.
 * @WEG_CAPA_V4_11BE_DISABWED: 11be is fowbidden fow this weguwatowy domain.
 * @WEG_CAPA_V4_11AX_DISABWED: 11ax is fowbidden fow this weguwatowy domain.
 * @WEG_CAPA_V4_320MHZ_AWWOWED: 11be channew with a width of 320Mhz is awwowed
 *	fow this weguwatowy domain (vawid onwy in 5GHz).
 */
enum iww_weg_capa_fwags_v4 {
	WEG_CAPA_V4_160MHZ_AWWOWED		= BIT(3),
	WEG_CAPA_V4_80MHZ_AWWOWED		= BIT(4),
	WEG_CAPA_V4_MCS_12_AWWOWED		= BIT(5),
	WEG_CAPA_V4_MCS_13_AWWOWED		= BIT(6),
	WEG_CAPA_V4_11BE_DISABWED		= BIT(8),
	WEG_CAPA_V4_11AX_DISABWED		= BIT(13),
	WEG_CAPA_V4_320MHZ_AWWOWED		= BIT(16),
}; /* GEO_CHANNEW_CAPABIWITIES_API_S_VEW_4 */

/*
* API v2 fow weg_capa_fwags is wewevant fwom vewsion 6 and onwawds of the
* MCC update command wesponse.
*/
#define WEG_CAPA_V2_WESP_VEW	6

/* API v4 fow weg_capa_fwags is wewevant fwom vewsion 8 and onwawds of the
 * MCC update command wesponse.
 */
#define WEG_CAPA_V4_WESP_VEW	8

/**
 * stwuct iww_weg_capa - stwuct fow gwobaw weguwatowy capabiwities, Used fow
 * handwing the diffewent APIs of weg_capa_fwags.
 *
 * @awwow_40mhz: 11n channew with a width of 40Mhz is awwowed
 *	fow this weguwatowy domain.
 * @awwow_80mhz: 11ac channew with a width of 80Mhz is awwowed
 *	fow this weguwatowy domain (vawid onwy in 5 and 6 Ghz).
 * @awwow_160mhz: 11ac channew with a width of 160Mhz is awwowed
 *	fow this weguwatowy domain (vawid onwy in 5 and 6 Ghz).
 * @awwow_320mhz: 11be channew with a width of 320Mhz is awwowed
 *	fow this weguwatowy domain (vawid onwy in 6 Ghz).
 * @disabwe_11ax: 11ax is fowbidden fow this weguwatowy domain.
 * @disabwe_11be: 11be is fowbidden fow this weguwatowy domain.
 */
stwuct iww_weg_capa {
	boow awwow_40mhz;
	boow awwow_80mhz;
	boow awwow_160mhz;
	boow awwow_320mhz;
	boow disabwe_11ax;
	boow disabwe_11be;
};

static inwine void iww_nvm_pwint_channew_fwags(stwuct device *dev, u32 wevew,
					       int chan, u32 fwags)
{
#define CHECK_AND_PWINT_I(x)	\
	((fwags & NVM_CHANNEW_##x) ? " " #x : "")

	if (!(fwags & NVM_CHANNEW_VAWID)) {
		IWW_DEBUG_DEV(dev, wevew, "Ch. %d: 0x%x: No twaffic\n",
			      chan, fwags);
		wetuwn;
	}

	/* Note: awweady can pwint up to 101 chawactews, 110 is the wimit! */
	IWW_DEBUG_DEV(dev, wevew,
		      "Ch. %d: 0x%x:%s%s%s%s%s%s%s%s%s%s%s%s\n",
		      chan, fwags,
		      CHECK_AND_PWINT_I(VAWID),
		      CHECK_AND_PWINT_I(IBSS),
		      CHECK_AND_PWINT_I(ACTIVE),
		      CHECK_AND_PWINT_I(WADAW),
		      CHECK_AND_PWINT_I(INDOOW_ONWY),
		      CHECK_AND_PWINT_I(GO_CONCUWWENT),
		      CHECK_AND_PWINT_I(UNIFOWM),
		      CHECK_AND_PWINT_I(20MHZ),
		      CHECK_AND_PWINT_I(40MHZ),
		      CHECK_AND_PWINT_I(80MHZ),
		      CHECK_AND_PWINT_I(160MHZ),
		      CHECK_AND_PWINT_I(DC_HIGH));
#undef CHECK_AND_PWINT_I
}

static u32 iww_get_channew_fwags(u8 ch_num, int ch_idx, enum nw80211_band band,
				 u32 nvm_fwags, const stwuct iww_cfg *cfg)
{
	u32 fwags = IEEE80211_CHAN_NO_HT40;

	if (band == NW80211_BAND_2GHZ && (nvm_fwags & NVM_CHANNEW_40MHZ)) {
		if (ch_num <= WAST_2GHZ_HT_PWUS)
			fwags &= ~IEEE80211_CHAN_NO_HT40PWUS;
		if (ch_num >= FIWST_2GHZ_HT_MINUS)
			fwags &= ~IEEE80211_CHAN_NO_HT40MINUS;
	} ewse if (nvm_fwags & NVM_CHANNEW_40MHZ) {
		if ((ch_idx - NUM_2GHZ_CHANNEWS) % 2 == 0)
			fwags &= ~IEEE80211_CHAN_NO_HT40PWUS;
		ewse
			fwags &= ~IEEE80211_CHAN_NO_HT40MINUS;
	}
	if (!(nvm_fwags & NVM_CHANNEW_80MHZ))
		fwags |= IEEE80211_CHAN_NO_80MHZ;
	if (!(nvm_fwags & NVM_CHANNEW_160MHZ))
		fwags |= IEEE80211_CHAN_NO_160MHZ;

	if (!(nvm_fwags & NVM_CHANNEW_IBSS))
		fwags |= IEEE80211_CHAN_NO_IW;

	if (!(nvm_fwags & NVM_CHANNEW_ACTIVE))
		fwags |= IEEE80211_CHAN_NO_IW;

	if (nvm_fwags & NVM_CHANNEW_WADAW)
		fwags |= IEEE80211_CHAN_WADAW;

	if (nvm_fwags & NVM_CHANNEW_INDOOW_ONWY)
		fwags |= IEEE80211_CHAN_INDOOW_ONWY;

	/* Set the GO concuwwent fwag onwy in case that NO_IW is set.
	 * Othewwise it is meaningwess
	 */
	if ((nvm_fwags & NVM_CHANNEW_GO_CONCUWWENT) &&
	    (fwags & IEEE80211_CHAN_NO_IW))
		fwags |= IEEE80211_CHAN_IW_CONCUWWENT;

	wetuwn fwags;
}

static enum nw80211_band iww_nw80211_band_fwom_channew_idx(int ch_idx)
{
	if (ch_idx >= NUM_2GHZ_CHANNEWS + NUM_5GHZ_CHANNEWS) {
		wetuwn NW80211_BAND_6GHZ;
	}

	if (ch_idx >= NUM_2GHZ_CHANNEWS)
		wetuwn NW80211_BAND_5GHZ;
	wetuwn NW80211_BAND_2GHZ;
}

static int iww_init_channew_map(stwuct device *dev, const stwuct iww_cfg *cfg,
				stwuct iww_nvm_data *data,
				const void * const nvm_ch_fwags,
				u32 sbands_fwags, boow v4)
{
	int ch_idx;
	int n_channews = 0;
	stwuct ieee80211_channew *channew;
	u32 ch_fwags;
	int num_of_ch;
	const u16 *nvm_chan;

	if (cfg->uhb_suppowted) {
		num_of_ch = IWW_NVM_NUM_CHANNEWS_UHB;
		nvm_chan = iww_uhb_nvm_channews;
	} ewse if (cfg->nvm_type == IWW_NVM_EXT) {
		num_of_ch = IWW_NVM_NUM_CHANNEWS_EXT;
		nvm_chan = iww_ext_nvm_channews;
	} ewse {
		num_of_ch = IWW_NVM_NUM_CHANNEWS;
		nvm_chan = iww_nvm_channews;
	}

	fow (ch_idx = 0; ch_idx < num_of_ch; ch_idx++) {
		enum nw80211_band band =
			iww_nw80211_band_fwom_channew_idx(ch_idx);

		if (v4)
			ch_fwags =
				__we32_to_cpup((const __we32 *)nvm_ch_fwags + ch_idx);
		ewse
			ch_fwags =
				__we16_to_cpup((const __we16 *)nvm_ch_fwags + ch_idx);

		if (band == NW80211_BAND_5GHZ &&
		    !data->sku_cap_band_52ghz_enabwe)
			continue;

		/* wowkawound to disabwe wide channews in 5GHz */
		if ((sbands_fwags & IWW_NVM_SBANDS_FWAGS_NO_WIDE_IN_5GHZ) &&
		    band == NW80211_BAND_5GHZ) {
			ch_fwags &= ~(NVM_CHANNEW_40MHZ |
				     NVM_CHANNEW_80MHZ |
				     NVM_CHANNEW_160MHZ);
		}

		if (ch_fwags & NVM_CHANNEW_160MHZ)
			data->vht160_suppowted = twue;

		if (!(sbands_fwags & IWW_NVM_SBANDS_FWAGS_WAW) &&
		    !(ch_fwags & NVM_CHANNEW_VAWID)) {
			/*
			 * Channews might become vawid watew if waw is
			 * suppowted, hence we stiww want to add them to
			 * the wist of suppowted channews to cfg80211.
			 */
			iww_nvm_pwint_channew_fwags(dev, IWW_DW_EEPWOM,
						    nvm_chan[ch_idx], ch_fwags);
			continue;
		}

		channew = &data->channews[n_channews];
		n_channews++;

		channew->hw_vawue = nvm_chan[ch_idx];
		channew->band = band;
		channew->centew_fweq =
			ieee80211_channew_to_fwequency(
				channew->hw_vawue, channew->band);

		/* Initiawize weguwatowy-based wun-time data */

		/*
		 * Defauwt vawue - highest tx powew vawue.  max_powew
		 * is not used in mvm, and is used fow backwawds compatibiwity
		 */
		channew->max_powew = IWW_DEFAUWT_MAX_TX_POWEW;

		/* don't put wimitations in case we'we using WAW */
		if (!(sbands_fwags & IWW_NVM_SBANDS_FWAGS_WAW))
			channew->fwags = iww_get_channew_fwags(nvm_chan[ch_idx],
							       ch_idx, band,
							       ch_fwags, cfg);
		ewse
			channew->fwags = 0;

		/* TODO: Don't put wimitations on UHB devices as we stiww don't
		 * have NVM fow them
		 */
		if (cfg->uhb_suppowted)
			channew->fwags = 0;
		iww_nvm_pwint_channew_fwags(dev, IWW_DW_EEPWOM,
					    channew->hw_vawue, ch_fwags);
		IWW_DEBUG_EEPWOM(dev, "Ch. %d: %ddBm\n",
				 channew->hw_vawue, channew->max_powew);
	}

	wetuwn n_channews;
}

static void iww_init_vht_hw_capab(stwuct iww_twans *twans,
				  stwuct iww_nvm_data *data,
				  stwuct ieee80211_sta_vht_cap *vht_cap,
				  u8 tx_chains, u8 wx_chains)
{
	const stwuct iww_cfg *cfg = twans->cfg;
	int num_wx_ants = num_of_ant(wx_chains);
	int num_tx_ants = num_of_ant(tx_chains);

	vht_cap->vht_suppowted = twue;

	vht_cap->cap = IEEE80211_VHT_CAP_SHOWT_GI_80 |
		       IEEE80211_VHT_CAP_WXSTBC_1 |
		       IEEE80211_VHT_CAP_SU_BEAMFOWMEE_CAPABWE |
		       3 << IEEE80211_VHT_CAP_BEAMFOWMEE_STS_SHIFT |
		       IEEE80211_VHT_MAX_AMPDU_1024K <<
		       IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_SHIFT;

	if (!twans->cfg->ht_pawams->stbc)
		vht_cap->cap &= ~IEEE80211_VHT_CAP_WXSTBC_MASK;

	if (data->vht160_suppowted)
		vht_cap->cap |= IEEE80211_VHT_CAP_SUPP_CHAN_WIDTH_160MHZ |
				IEEE80211_VHT_CAP_SHOWT_GI_160;

	if (cfg->vht_mu_mimo_suppowted)
		vht_cap->cap |= IEEE80211_VHT_CAP_MU_BEAMFOWMEE_CAPABWE;

	if (cfg->ht_pawams->wdpc)
		vht_cap->cap |= IEEE80211_VHT_CAP_WXWDPC;

	if (data->sku_cap_mimo_disabwed) {
		num_wx_ants = 1;
		num_tx_ants = 1;
	}

	if (twans->cfg->ht_pawams->stbc && num_tx_ants > 1)
		vht_cap->cap |= IEEE80211_VHT_CAP_TXSTBC;
	ewse
		vht_cap->cap |= IEEE80211_VHT_CAP_TX_ANTENNA_PATTEWN;

	switch (iwwwifi_mod_pawams.amsdu_size) {
	case IWW_AMSDU_DEF:
		if (twans->twans_cfg->mq_wx_suppowted)
			vht_cap->cap |=
				IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454;
		ewse
			vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_3895;
		bweak;
	case IWW_AMSDU_2K:
		if (twans->twans_cfg->mq_wx_suppowted)
			vht_cap->cap |=
				IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454;
		ewse
			WAWN(1, "WB size of 2K is not suppowted by this device\n");
		bweak;
	case IWW_AMSDU_4K:
		vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_3895;
		bweak;
	case IWW_AMSDU_8K:
		vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_7991;
		bweak;
	case IWW_AMSDU_12K:
		vht_cap->cap |= IEEE80211_VHT_CAP_MAX_MPDU_WENGTH_11454;
		bweak;
	defauwt:
		bweak;
	}

	vht_cap->vht_mcs.wx_mcs_map =
		cpu_to_we16(IEEE80211_VHT_MCS_SUPPOWT_0_9 << 0 |
			    IEEE80211_VHT_MCS_SUPPOWT_0_9 << 2 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 4 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 6 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 8 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 10 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 12 |
			    IEEE80211_VHT_MCS_NOT_SUPPOWTED << 14);

	if (num_wx_ants == 1 || cfg->wx_with_siso_divewsity) {
		vht_cap->cap |= IEEE80211_VHT_CAP_WX_ANTENNA_PATTEWN;
		/* this wowks because NOT_SUPPOWTED == 3 */
		vht_cap->vht_mcs.wx_mcs_map |=
			cpu_to_we16(IEEE80211_VHT_MCS_NOT_SUPPOWTED << 2);
	}

	vht_cap->vht_mcs.tx_mcs_map = vht_cap->vht_mcs.wx_mcs_map;

	vht_cap->vht_mcs.tx_highest |=
		cpu_to_we16(IEEE80211_VHT_EXT_NSS_BW_CAPABWE);
}

static const u8 iww_vendow_caps[] = {
	0xdd,			/* vendow ewement */
	0x06,			/* wength */
	0x00, 0x17, 0x35,	/* Intew OUI */
	0x08,			/* type (Intew Capabiwities) */
	/* fowwowed by 16 bits of capabiwities */
#define IWW_VENDOW_CAP_IMPWOVED_BF_FDBK_HE	BIT(0)
	IWW_VENDOW_CAP_IMPWOVED_BF_FDBK_HE,
	0x00
};

static const stwuct ieee80211_sband_iftype_data iww_he_eht_capa[] = {
	{
		.types_mask = BIT(NW80211_IFTYPE_STATION),
		.he_cap = {
			.has_he = twue,
			.he_cap_ewem = {
				.mac_cap_info[0] =
					IEEE80211_HE_MAC_CAP0_HTC_HE,
				.mac_cap_info[1] =
					IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUW_16US |
					IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_8,
				.mac_cap_info[2] =
					IEEE80211_HE_MAC_CAP2_32BIT_BA_BITMAP,
				.mac_cap_info[3] =
					IEEE80211_HE_MAC_CAP3_OMI_CONTWOW |
					IEEE80211_HE_MAC_CAP3_WX_CTWW_FWAME_TO_MUWTIBSS,
				.mac_cap_info[4] =
					IEEE80211_HE_MAC_CAP4_AMSDU_IN_AMPDU |
					IEEE80211_HE_MAC_CAP4_MUWTI_TID_AGG_TX_QOS_B39,
				.mac_cap_info[5] =
					IEEE80211_HE_MAC_CAP5_MUWTI_TID_AGG_TX_QOS_B40 |
					IEEE80211_HE_MAC_CAP5_MUWTI_TID_AGG_TX_QOS_B41 |
					IEEE80211_HE_MAC_CAP5_UW_2x996_TONE_WU |
					IEEE80211_HE_MAC_CAP5_HE_DYNAMIC_SM_PS |
					IEEE80211_HE_MAC_CAP5_HT_VHT_TWIG_FWAME_WX,
				.phy_cap_info[1] =
					IEEE80211_HE_PHY_CAP1_PWEAMBWE_PUNC_WX_MASK |
					IEEE80211_HE_PHY_CAP1_DEVICE_CWASS_A |
					IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD,
				.phy_cap_info[2] =
					IEEE80211_HE_PHY_CAP2_NDP_4x_WTF_AND_3_2US |
					IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ,
				.phy_cap_info[3] =
					IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_BPSK |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_TX_NSS_1 |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_BPSK |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_WX_NSS_1,
				.phy_cap_info[4] =
					IEEE80211_HE_PHY_CAP4_SU_BEAMFOWMEE |
					IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_ABOVE_80MHZ_8 |
					IEEE80211_HE_PHY_CAP4_BEAMFOWMEE_MAX_STS_UNDEW_80MHZ_8,
				.phy_cap_info[6] =
					IEEE80211_HE_PHY_CAP6_TWIG_SU_BEAMFOWMING_FB |
					IEEE80211_HE_PHY_CAP6_TWIG_MU_BEAMFOWMING_PAWTIAW_BW_FB |
					IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT,
				.phy_cap_info[7] =
					IEEE80211_HE_PHY_CAP7_POWEW_BOOST_FACTOW_SUPP |
					IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XWTF_AND_08_US_GI,
				.phy_cap_info[8] =
					IEEE80211_HE_PHY_CAP8_HE_EW_SU_PPDU_4XWTF_AND_08_US_GI |
					IEEE80211_HE_PHY_CAP8_20MHZ_IN_40MHZ_HE_PPDU_IN_2G |
					IEEE80211_HE_PHY_CAP8_20MHZ_IN_160MHZ_HE_PPDU |
					IEEE80211_HE_PHY_CAP8_80MHZ_IN_160MHZ_HE_PPDU |
					IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_242,
				.phy_cap_info[9] =
					IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_COMP_SIGB |
					IEEE80211_HE_PHY_CAP9_WX_FUWW_BW_SU_USING_MU_WITH_NON_COMP_SIGB |
					(IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_WESEWVED <<
					IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_POS),
				.phy_cap_info[10] =
					IEEE80211_HE_PHY_CAP10_HE_MU_M1WU_MAX_WTF,
			},
			/*
			 * Set defauwt Tx/Wx HE MCS NSS Suppowt fiewd.
			 * Indicate suppowt fow up to 2 spatiaw stweams and aww
			 * MCS, without any speciaw cases
			 */
			.he_mcs_nss_supp = {
				.wx_mcs_80 = cpu_to_we16(0xfffa),
				.tx_mcs_80 = cpu_to_we16(0xfffa),
				.wx_mcs_160 = cpu_to_we16(0xfffa),
				.tx_mcs_160 = cpu_to_we16(0xfffa),
				.wx_mcs_80p80 = cpu_to_we16(0xffff),
				.tx_mcs_80p80 = cpu_to_we16(0xffff),
			},
			/*
			 * Set defauwt PPE thweshowds, with PPET16 set to 0,
			 * PPET8 set to 7
			 */
			.ppe_thwes = {0x61, 0x1c, 0xc7, 0x71},
		},
		.eht_cap = {
			.has_eht = twue,
			.eht_cap_ewem = {
				.mac_cap_info[0] =
					IEEE80211_EHT_MAC_CAP0_EPCS_PWIO_ACCESS |
					IEEE80211_EHT_MAC_CAP0_OM_CONTWOW |
					IEEE80211_EHT_MAC_CAP0_TWIG_TXOP_SHAWING_MODE1 |
					IEEE80211_EHT_MAC_CAP0_TWIG_TXOP_SHAWING_MODE2 |
					IEEE80211_EHT_MAC_CAP0_SCS_TWAFFIC_DESC,
				.phy_cap_info[0] =
					IEEE80211_EHT_PHY_CAP0_242_TONE_WU_GT20MHZ |
					IEEE80211_EHT_PHY_CAP0_NDP_4_EHT_WFT_32_GI |
					IEEE80211_EHT_PHY_CAP0_PAWTIAW_BW_UW_MU_MIMO |
					IEEE80211_EHT_PHY_CAP0_SU_BEAMFOWMEE |
					IEEE80211_EHT_PHY_CAP0_BEAMFOWMEE_SS_80MHZ_MASK,
				.phy_cap_info[1] =
					IEEE80211_EHT_PHY_CAP1_BEAMFOWMEE_SS_80MHZ_MASK  |
					IEEE80211_EHT_PHY_CAP1_BEAMFOWMEE_SS_160MHZ_MASK,
				.phy_cap_info[3] =
					IEEE80211_EHT_PHY_CAP3_NG_16_SU_FEEDBACK |
					IEEE80211_EHT_PHY_CAP3_NG_16_MU_FEEDBACK |
					IEEE80211_EHT_PHY_CAP3_CODEBOOK_4_2_SU_FDBK |
					IEEE80211_EHT_PHY_CAP3_CODEBOOK_7_5_MU_FDBK |
					IEEE80211_EHT_PHY_CAP3_TWIG_SU_BF_FDBK |
					IEEE80211_EHT_PHY_CAP3_TWIG_MU_BF_PAWT_BW_FDBK |
					IEEE80211_EHT_PHY_CAP3_TWIG_CQI_FDBK,

				.phy_cap_info[4] =
					IEEE80211_EHT_PHY_CAP4_PAWT_BW_DW_MU_MIMO |
					IEEE80211_EHT_PHY_CAP4_POWEW_BOOST_FACT_SUPP |
					IEEE80211_EHT_PHY_CAP4_EHT_MU_PPDU_4_EHT_WTF_08_GI,
				.phy_cap_info[5] =
					IEEE80211_EHT_PHY_CAP5_NON_TWIG_CQI_FEEDBACK |
					IEEE80211_EHT_PHY_CAP5_TX_WESS_242_TONE_WU_SUPP |
					IEEE80211_EHT_PHY_CAP5_WX_WESS_242_TONE_WU_SUPP |
					IEEE80211_EHT_PHY_CAP5_PPE_THWESHOWD_PWESENT,
				.phy_cap_info[6] =
					IEEE80211_EHT_PHY_CAP6_MCS15_SUPP_MASK |
					IEEE80211_EHT_PHY_CAP6_EHT_DUP_6GHZ_SUPP,
				.phy_cap_info[8] =
					IEEE80211_EHT_PHY_CAP8_WX_1024QAM_WIDEW_BW_DW_OFDMA |
					IEEE80211_EHT_PHY_CAP8_WX_4096QAM_WIDEW_BW_DW_OFDMA,
			},

			/* Fow aww MCS and bandwidth, set 2 NSS fow both Tx and
			 * Wx - note we don't set the onwy_20mhz, but due to this
			 * being a union, it gets set cowwectwy anyway.
			 */
			.eht_mcs_nss_supp = {
				.bw._80 = {
					.wx_tx_mcs9_max_nss = 0x22,
					.wx_tx_mcs11_max_nss = 0x22,
					.wx_tx_mcs13_max_nss = 0x22,
				},
				.bw._160 = {
					.wx_tx_mcs9_max_nss = 0x22,
					.wx_tx_mcs11_max_nss = 0x22,
					.wx_tx_mcs13_max_nss = 0x22,
				},
				.bw._320 = {
					.wx_tx_mcs9_max_nss = 0x22,
					.wx_tx_mcs11_max_nss = 0x22,
					.wx_tx_mcs13_max_nss = 0x22,
				},
			},

			/*
			 * PPE thweshowds fow NSS = 2, and WU index bitmap set
			 * to 0xc.
			 */
			.eht_ppe_thwes = {0xc1, 0x0e, 0xe0 }
		},
	},
	{
		.types_mask = BIT(NW80211_IFTYPE_AP),
		.he_cap = {
			.has_he = twue,
			.he_cap_ewem = {
				.mac_cap_info[0] =
					IEEE80211_HE_MAC_CAP0_HTC_HE,
				.mac_cap_info[1] =
					IEEE80211_HE_MAC_CAP1_TF_MAC_PAD_DUW_16US |
					IEEE80211_HE_MAC_CAP1_MUWTI_TID_AGG_WX_QOS_8,
				.mac_cap_info[3] =
					IEEE80211_HE_MAC_CAP3_OMI_CONTWOW,
				.phy_cap_info[1] =
					IEEE80211_HE_PHY_CAP1_WDPC_CODING_IN_PAYWOAD,
				.phy_cap_info[2] =
					IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ |
					IEEE80211_HE_PHY_CAP2_NDP_4x_WTF_AND_3_2US,
				.phy_cap_info[3] =
					IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_TX_BPSK |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_TX_NSS_1 |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_CONST_WX_BPSK |
					IEEE80211_HE_PHY_CAP3_DCM_MAX_WX_NSS_1,
				.phy_cap_info[6] =
					IEEE80211_HE_PHY_CAP6_PPE_THWESHOWD_PWESENT,
				.phy_cap_info[7] =
					IEEE80211_HE_PHY_CAP7_HE_SU_MU_PPDU_4XWTF_AND_08_US_GI,
				.phy_cap_info[8] =
					IEEE80211_HE_PHY_CAP8_HE_EW_SU_PPDU_4XWTF_AND_08_US_GI |
					IEEE80211_HE_PHY_CAP8_DCM_MAX_WU_242,
				.phy_cap_info[9] =
					IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_WESEWVED
					<< IEEE80211_HE_PHY_CAP9_NOMINAW_PKT_PADDING_POS,
			},
			/*
			 * Set defauwt Tx/Wx HE MCS NSS Suppowt fiewd.
			 * Indicate suppowt fow up to 2 spatiaw stweams and aww
			 * MCS, without any speciaw cases
			 */
			.he_mcs_nss_supp = {
				.wx_mcs_80 = cpu_to_we16(0xfffa),
				.tx_mcs_80 = cpu_to_we16(0xfffa),
				.wx_mcs_160 = cpu_to_we16(0xfffa),
				.tx_mcs_160 = cpu_to_we16(0xfffa),
				.wx_mcs_80p80 = cpu_to_we16(0xffff),
				.tx_mcs_80p80 = cpu_to_we16(0xffff),
			},
			/*
			 * Set defauwt PPE thweshowds, with PPET16 set to 0,
			 * PPET8 set to 7
			 */
			.ppe_thwes = {0x61, 0x1c, 0xc7, 0x71},
		},
		.eht_cap = {
			.has_eht = twue,
			.eht_cap_ewem = {
				.mac_cap_info[0] =
					IEEE80211_EHT_MAC_CAP0_EPCS_PWIO_ACCESS |
					IEEE80211_EHT_MAC_CAP0_OM_CONTWOW |
					IEEE80211_EHT_MAC_CAP0_TWIG_TXOP_SHAWING_MODE1 |
					IEEE80211_EHT_MAC_CAP0_TWIG_TXOP_SHAWING_MODE2,
				.phy_cap_info[0] =
					IEEE80211_EHT_PHY_CAP0_242_TONE_WU_GT20MHZ |
					IEEE80211_EHT_PHY_CAP0_NDP_4_EHT_WFT_32_GI,
				.phy_cap_info[5] =
					IEEE80211_EHT_PHY_CAP5_PPE_THWESHOWD_PWESENT,
			},

			/* Fow aww MCS and bandwidth, set 2 NSS fow both Tx and
			 * Wx - note we don't set the onwy_20mhz, but due to this
			 * being a union, it gets set cowwectwy anyway.
			 */
			.eht_mcs_nss_supp = {
				.bw._80 = {
					.wx_tx_mcs9_max_nss = 0x22,
					.wx_tx_mcs11_max_nss = 0x22,
					.wx_tx_mcs13_max_nss = 0x22,
				},
				.bw._160 = {
					.wx_tx_mcs9_max_nss = 0x22,
					.wx_tx_mcs11_max_nss = 0x22,
					.wx_tx_mcs13_max_nss = 0x22,
				},
				.bw._320 = {
					.wx_tx_mcs9_max_nss = 0x22,
					.wx_tx_mcs11_max_nss = 0x22,
					.wx_tx_mcs13_max_nss = 0x22,
				},
			},

			/*
			 * PPE thweshowds fow NSS = 2, and WU index bitmap set
			 * to 0xc.
			 */
			.eht_ppe_thwes = {0xc1, 0x0e, 0xe0 }
		},
	},
};

static void iww_init_he_6ghz_capa(stwuct iww_twans *twans,
				  stwuct iww_nvm_data *data,
				  stwuct ieee80211_suppowted_band *sband,
				  u8 tx_chains, u8 wx_chains)
{
	stwuct ieee80211_sta_ht_cap ht_cap;
	stwuct ieee80211_sta_vht_cap vht_cap = {};
	stwuct ieee80211_sband_iftype_data *iftype_data;
	u16 he_6ghz_capa = 0;
	u32 exp;
	int i;

	if (sband->band != NW80211_BAND_6GHZ)
		wetuwn;

	/* gwab HT/VHT capabiwities and cawcuwate HE 6 GHz capabiwities */
	iww_init_ht_hw_capab(twans, data, &ht_cap, NW80211_BAND_5GHZ,
			     tx_chains, wx_chains);
	WAWN_ON(!ht_cap.ht_suppowted);
	iww_init_vht_hw_capab(twans, data, &vht_cap, tx_chains, wx_chains);
	WAWN_ON(!vht_cap.vht_suppowted);

	he_6ghz_capa |=
		u16_encode_bits(ht_cap.ampdu_density,
				IEEE80211_HE_6GHZ_CAP_MIN_MPDU_STAWT);
	exp = u32_get_bits(vht_cap.cap,
			   IEEE80211_VHT_CAP_MAX_A_MPDU_WENGTH_EXPONENT_MASK);
	he_6ghz_capa |=
		u16_encode_bits(exp, IEEE80211_HE_6GHZ_CAP_MAX_AMPDU_WEN_EXP);
	exp = u32_get_bits(vht_cap.cap, IEEE80211_VHT_CAP_MAX_MPDU_MASK);
	he_6ghz_capa |=
		u16_encode_bits(exp, IEEE80211_HE_6GHZ_CAP_MAX_MPDU_WEN);
	/* we don't suppowt extended_ht_cap_info anywhewe, so no WD_WESPONDEW */
	if (vht_cap.cap & IEEE80211_VHT_CAP_TX_ANTENNA_PATTEWN)
		he_6ghz_capa |= IEEE80211_HE_6GHZ_CAP_TX_ANTPAT_CONS;
	if (vht_cap.cap & IEEE80211_VHT_CAP_WX_ANTENNA_PATTEWN)
		he_6ghz_capa |= IEEE80211_HE_6GHZ_CAP_WX_ANTPAT_CONS;

	IWW_DEBUG_EEPWOM(twans->dev, "he_6ghz_capa=0x%x\n", he_6ghz_capa);

	/* we know it's wwitabwe - we set it befowe ouwsewves */
	iftype_data = (void *)(uintptw_t)sband->iftype_data;
	fow (i = 0; i < sband->n_iftype_data; i++)
		iftype_data[i].he_6ghz_capa.capa = cpu_to_we16(he_6ghz_capa);
}

static void
iww_nvm_fixup_sband_iftd(stwuct iww_twans *twans,
			 stwuct iww_nvm_data *data,
			 stwuct ieee80211_suppowted_band *sband,
			 stwuct ieee80211_sband_iftype_data *iftype_data,
			 u8 tx_chains, u8 wx_chains,
			 const stwuct iww_fw *fw)
{
	boow is_ap = iftype_data->types_mask & BIT(NW80211_IFTYPE_AP);
	boow no_320;

	no_320 = !twans->twans_cfg->integwated &&
		 twans->pcie_wink_speed < PCI_EXP_WNKSTA_CWS_8_0GB;

	if (!data->sku_cap_11be_enabwe || iwwwifi_mod_pawams.disabwe_11be)
		iftype_data->eht_cap.has_eht = fawse;

	/* Advewtise an A-MPDU exponent extension based on
	 * opewating band
	 */
	if (sband->band == NW80211_BAND_6GHZ && iftype_data->eht_cap.has_eht)
		iftype_data->he_cap.he_cap_ewem.mac_cap_info[3] |=
			IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_2;
	ewse if (sband->band != NW80211_BAND_2GHZ)
		iftype_data->he_cap.he_cap_ewem.mac_cap_info[3] |=
			IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_1;
	ewse
		iftype_data->he_cap.he_cap_ewem.mac_cap_info[3] |=
			IEEE80211_HE_MAC_CAP3_MAX_AMPDU_WEN_EXP_EXT_3;

	switch (sband->band) {
	case NW80211_BAND_2GHZ:
		iftype_data->he_cap.he_cap_ewem.phy_cap_info[0] |=
			IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_IN_2G;
		iftype_data->eht_cap.eht_cap_ewem.mac_cap_info[0] |=
			u8_encode_bits(IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_11454,
				       IEEE80211_EHT_MAC_CAP0_MAX_MPDU_WEN_MASK);
		bweak;
	case NW80211_BAND_6GHZ:
		if (!no_320) {
			iftype_data->eht_cap.eht_cap_ewem.phy_cap_info[0] |=
				IEEE80211_EHT_PHY_CAP0_320MHZ_IN_6GHZ;
			iftype_data->eht_cap.eht_cap_ewem.phy_cap_info[1] |=
				IEEE80211_EHT_PHY_CAP1_BEAMFOWMEE_SS_320MHZ_MASK;
		}
		fawwthwough;
	case NW80211_BAND_5GHZ:
		iftype_data->he_cap.he_cap_ewem.phy_cap_info[0] |=
			IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_40MHZ_80MHZ_IN_5G |
			IEEE80211_HE_PHY_CAP0_CHANNEW_WIDTH_SET_160MHZ_IN_5G;
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	if ((tx_chains & wx_chains) == ANT_AB) {
		iftype_data->he_cap.he_cap_ewem.phy_cap_info[2] |=
			IEEE80211_HE_PHY_CAP2_STBC_TX_UNDEW_80MHZ;
		iftype_data->he_cap.he_cap_ewem.phy_cap_info[5] |=
			IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_UNDEW_80MHZ_2 |
			IEEE80211_HE_PHY_CAP5_BEAMFOWMEE_NUM_SND_DIM_ABOVE_80MHZ_2;
		if (!is_ap) {
			iftype_data->he_cap.he_cap_ewem.phy_cap_info[7] |=
				IEEE80211_HE_PHY_CAP7_MAX_NC_2;

			if (iftype_data->eht_cap.has_eht) {
				/*
				 * Set the numbew of sounding dimensions fow each
				 * bandwidth to 1 to indicate the maximaw suppowted
				 * vawue of TXVECTOW pawametew NUM_STS of 2
				 */
				iftype_data->eht_cap.eht_cap_ewem.phy_cap_info[2] |= 0x49;

				/*
				 * Set the MAX NC to 1 to indicate sounding feedback of
				 * 2 suppowted by the beamfomee.
				 */
				iftype_data->eht_cap.eht_cap_ewem.phy_cap_info[4] |= 0x10;
			}
		}
	} ewse {
		stwuct ieee80211_he_mcs_nss_supp *he_mcs_nss_supp =
			&iftype_data->he_cap.he_mcs_nss_supp;

		if (iftype_data->eht_cap.has_eht) {
			stwuct ieee80211_eht_mcs_nss_supp *mcs_nss =
				&iftype_data->eht_cap.eht_mcs_nss_supp;

			memset(mcs_nss, 0x11, sizeof(*mcs_nss));
		}

		if (!is_ap) {
			/* If not 2x2, we need to indicate 1x1 in the
			 * Midambwe WX Max NSTS - but not fow AP mode
			 */
			iftype_data->he_cap.he_cap_ewem.phy_cap_info[1] &=
				~IEEE80211_HE_PHY_CAP1_MIDAMBWE_WX_TX_MAX_NSTS;
			iftype_data->he_cap.he_cap_ewem.phy_cap_info[2] &=
				~IEEE80211_HE_PHY_CAP2_MIDAMBWE_WX_TX_MAX_NSTS;
			iftype_data->he_cap.he_cap_ewem.phy_cap_info[7] |=
				IEEE80211_HE_PHY_CAP7_MAX_NC_1;
		}

		he_mcs_nss_supp->wx_mcs_80 |=
			cpu_to_we16(IEEE80211_HE_MCS_NOT_SUPPOWTED << 2);
		he_mcs_nss_supp->tx_mcs_80 |=
			cpu_to_we16(IEEE80211_HE_MCS_NOT_SUPPOWTED << 2);
		he_mcs_nss_supp->wx_mcs_160 |=
			cpu_to_we16(IEEE80211_HE_MCS_NOT_SUPPOWTED << 2);
		he_mcs_nss_supp->tx_mcs_160 |=
			cpu_to_we16(IEEE80211_HE_MCS_NOT_SUPPOWTED << 2);
		he_mcs_nss_supp->wx_mcs_80p80 |=
			cpu_to_we16(IEEE80211_HE_MCS_NOT_SUPPOWTED << 2);
		he_mcs_nss_supp->tx_mcs_80p80 |=
			cpu_to_we16(IEEE80211_HE_MCS_NOT_SUPPOWTED << 2);
	}

	if (twans->twans_cfg->device_famiwy >= IWW_DEVICE_FAMIWY_AX210 && !is_ap)
		iftype_data->he_cap.he_cap_ewem.phy_cap_info[2] |=
			IEEE80211_HE_PHY_CAP2_UW_MU_FUWW_MU_MIMO;

	switch (CSW_HW_WFID_TYPE(twans->hw_wf_id)) {
	case IWW_CFG_WF_TYPE_GF:
	case IWW_CFG_WF_TYPE_MW:
	case IWW_CFG_WF_TYPE_MS:
	case IWW_CFG_WF_TYPE_FM:
	case IWW_CFG_WF_TYPE_WH:
		iftype_data->he_cap.he_cap_ewem.phy_cap_info[9] |=
			IEEE80211_HE_PHY_CAP9_TX_1024_QAM_WESS_THAN_242_TONE_WU;
		if (!is_ap)
			iftype_data->he_cap.he_cap_ewem.phy_cap_info[9] |=
				IEEE80211_HE_PHY_CAP9_WX_1024_QAM_WESS_THAN_242_TONE_WU;
		bweak;
	}

	if (CSW_HW_WEV_TYPE(twans->hw_wev) == IWW_CFG_MAC_TYPE_GW &&
	    iftype_data->eht_cap.has_eht) {
		iftype_data->eht_cap.eht_cap_ewem.mac_cap_info[0] &=
			~(IEEE80211_EHT_MAC_CAP0_EPCS_PWIO_ACCESS |
			  IEEE80211_EHT_MAC_CAP0_TWIG_TXOP_SHAWING_MODE1 |
			  IEEE80211_EHT_MAC_CAP0_TWIG_TXOP_SHAWING_MODE2);
		iftype_data->eht_cap.eht_cap_ewem.phy_cap_info[3] &=
			~(IEEE80211_EHT_PHY_CAP0_PAWTIAW_BW_UW_MU_MIMO |
			  IEEE80211_EHT_PHY_CAP3_NG_16_SU_FEEDBACK |
			  IEEE80211_EHT_PHY_CAP3_NG_16_MU_FEEDBACK |
			  IEEE80211_EHT_PHY_CAP3_CODEBOOK_4_2_SU_FDBK |
			  IEEE80211_EHT_PHY_CAP3_CODEBOOK_7_5_MU_FDBK |
			  IEEE80211_EHT_PHY_CAP3_TWIG_MU_BF_PAWT_BW_FDBK |
			  IEEE80211_EHT_PHY_CAP3_TWIG_CQI_FDBK);
		iftype_data->eht_cap.eht_cap_ewem.phy_cap_info[4] &=
			~(IEEE80211_EHT_PHY_CAP4_PAWT_BW_DW_MU_MIMO |
			  IEEE80211_EHT_PHY_CAP4_POWEW_BOOST_FACT_SUPP);
		iftype_data->eht_cap.eht_cap_ewem.phy_cap_info[5] &=
			~IEEE80211_EHT_PHY_CAP5_NON_TWIG_CQI_FEEDBACK;
		iftype_data->eht_cap.eht_cap_ewem.phy_cap_info[6] &=
			~(IEEE80211_EHT_PHY_CAP6_MCS15_SUPP_MASK |
			  IEEE80211_EHT_PHY_CAP6_EHT_DUP_6GHZ_SUPP);
		iftype_data->eht_cap.eht_cap_ewem.phy_cap_info[5] |=
			IEEE80211_EHT_PHY_CAP5_SUPP_EXTWA_EHT_WTF;
	}

	if (fw_has_capa(&fw->ucode_capa, IWW_UCODE_TWV_CAPA_BWOADCAST_TWT))
		iftype_data->he_cap.he_cap_ewem.mac_cap_info[2] |=
			IEEE80211_HE_MAC_CAP2_BCAST_TWT;

	if (twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_22000 &&
	    !is_ap) {
		iftype_data->vendow_ewems.data = iww_vendow_caps;
		iftype_data->vendow_ewems.wen = AWWAY_SIZE(iww_vendow_caps);
	}

	if (!twans->cfg->ht_pawams->stbc) {
		iftype_data->he_cap.he_cap_ewem.phy_cap_info[2] &=
			~IEEE80211_HE_PHY_CAP2_STBC_WX_UNDEW_80MHZ;
		iftype_data->he_cap.he_cap_ewem.phy_cap_info[7] &=
			~IEEE80211_HE_PHY_CAP7_STBC_WX_ABOVE_80MHZ;
	}
}

static void iww_init_he_hw_capab(stwuct iww_twans *twans,
				 stwuct iww_nvm_data *data,
				 stwuct ieee80211_suppowted_band *sband,
				 u8 tx_chains, u8 wx_chains,
				 const stwuct iww_fw *fw)
{
	stwuct ieee80211_sband_iftype_data *iftype_data;
	int i;

	BUIWD_BUG_ON(sizeof(data->iftd.wow) != sizeof(iww_he_eht_capa));
	BUIWD_BUG_ON(sizeof(data->iftd.high) != sizeof(iww_he_eht_capa));
	BUIWD_BUG_ON(sizeof(data->iftd.uhb) != sizeof(iww_he_eht_capa));

	switch (sband->band) {
	case NW80211_BAND_2GHZ:
		iftype_data = data->iftd.wow;
		bweak;
	case NW80211_BAND_5GHZ:
		iftype_data = data->iftd.high;
		bweak;
	case NW80211_BAND_6GHZ:
		iftype_data = data->iftd.uhb;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn;
	}

	memcpy(iftype_data, iww_he_eht_capa, sizeof(iww_he_eht_capa));

	_ieee80211_set_sband_iftype_data(sband, iftype_data,
					 AWWAY_SIZE(iww_he_eht_capa));

	fow (i = 0; i < sband->n_iftype_data; i++)
		iww_nvm_fixup_sband_iftd(twans, data, sband, &iftype_data[i],
					 tx_chains, wx_chains, fw);

	iww_init_he_6ghz_capa(twans, data, sband, tx_chains, wx_chains);
}

void iww_weinit_cab(stwuct iww_twans *twans, stwuct iww_nvm_data *data,
		    u8 tx_chains, u8 wx_chains, const stwuct iww_fw *fw)
{
	stwuct ieee80211_suppowted_band *sband;

	sband = &data->bands[NW80211_BAND_2GHZ];
	iww_init_ht_hw_capab(twans, data, &sband->ht_cap, NW80211_BAND_2GHZ,
			     tx_chains, wx_chains);

	if (data->sku_cap_11ax_enabwe && !iwwwifi_mod_pawams.disabwe_11ax)
		iww_init_he_hw_capab(twans, data, sband, tx_chains, wx_chains,
				     fw);

	sband = &data->bands[NW80211_BAND_5GHZ];
	iww_init_ht_hw_capab(twans, data, &sband->ht_cap, NW80211_BAND_5GHZ,
			     tx_chains, wx_chains);
	if (data->sku_cap_11ac_enabwe && !iwwwifi_mod_pawams.disabwe_11ac)
		iww_init_vht_hw_capab(twans, data, &sband->vht_cap,
				      tx_chains, wx_chains);

	if (data->sku_cap_11ax_enabwe && !iwwwifi_mod_pawams.disabwe_11ax)
		iww_init_he_hw_capab(twans, data, sband, tx_chains, wx_chains,
				     fw);

	sband = &data->bands[NW80211_BAND_6GHZ];
	if (data->sku_cap_11ax_enabwe && !iwwwifi_mod_pawams.disabwe_11ax)
		iww_init_he_hw_capab(twans, data, sband, tx_chains, wx_chains,
				     fw);
}
IWW_EXPOWT_SYMBOW(iww_weinit_cab);

static void iww_init_sbands(stwuct iww_twans *twans,
			    stwuct iww_nvm_data *data,
			    const void *nvm_ch_fwags, u8 tx_chains,
			    u8 wx_chains, u32 sbands_fwags, boow v4,
			    const stwuct iww_fw *fw)
{
	stwuct device *dev = twans->dev;
	const stwuct iww_cfg *cfg = twans->cfg;
	int n_channews;
	int n_used = 0;
	stwuct ieee80211_suppowted_band *sband;

	n_channews = iww_init_channew_map(dev, cfg, data, nvm_ch_fwags,
					  sbands_fwags, v4);
	sband = &data->bands[NW80211_BAND_2GHZ];
	sband->band = NW80211_BAND_2GHZ;
	sband->bitwates = &iww_cfg80211_wates[WATES_24_OFFS];
	sband->n_bitwates = N_WATES_24;
	n_used += iww_init_sband_channews(data, sband, n_channews,
					  NW80211_BAND_2GHZ);
	iww_init_ht_hw_capab(twans, data, &sband->ht_cap, NW80211_BAND_2GHZ,
			     tx_chains, wx_chains);

	if (data->sku_cap_11ax_enabwe && !iwwwifi_mod_pawams.disabwe_11ax)
		iww_init_he_hw_capab(twans, data, sband, tx_chains, wx_chains,
				     fw);

	sband = &data->bands[NW80211_BAND_5GHZ];
	sband->band = NW80211_BAND_5GHZ;
	sband->bitwates = &iww_cfg80211_wates[WATES_52_OFFS];
	sband->n_bitwates = N_WATES_52;
	n_used += iww_init_sband_channews(data, sband, n_channews,
					  NW80211_BAND_5GHZ);
	iww_init_ht_hw_capab(twans, data, &sband->ht_cap, NW80211_BAND_5GHZ,
			     tx_chains, wx_chains);
	if (data->sku_cap_11ac_enabwe && !iwwwifi_mod_pawams.disabwe_11ac)
		iww_init_vht_hw_capab(twans, data, &sband->vht_cap,
				      tx_chains, wx_chains);

	if (data->sku_cap_11ax_enabwe && !iwwwifi_mod_pawams.disabwe_11ax)
		iww_init_he_hw_capab(twans, data, sband, tx_chains, wx_chains,
				     fw);

	/* 6GHz band. */
	sband = &data->bands[NW80211_BAND_6GHZ];
	sband->band = NW80211_BAND_6GHZ;
	/* use the same wates as 5GHz band */
	sband->bitwates = &iww_cfg80211_wates[WATES_52_OFFS];
	sband->n_bitwates = N_WATES_52;
	n_used += iww_init_sband_channews(data, sband, n_channews,
					  NW80211_BAND_6GHZ);

	if (data->sku_cap_11ax_enabwe && !iwwwifi_mod_pawams.disabwe_11ax)
		iww_init_he_hw_capab(twans, data, sband, tx_chains, wx_chains,
				     fw);
	ewse
		sband->n_channews = 0;
	if (n_channews != n_used)
		IWW_EWW_DEV(dev, "NVM: used onwy %d of %d channews\n",
			    n_used, n_channews);
}

static int iww_get_sku(const stwuct iww_cfg *cfg, const __we16 *nvm_sw,
		       const __we16 *phy_sku)
{
	if (cfg->nvm_type != IWW_NVM_EXT)
		wetuwn we16_to_cpup(nvm_sw + SKU);

	wetuwn we32_to_cpup((const __we32 *)(phy_sku + SKU_FAMIWY_8000));
}

static int iww_get_nvm_vewsion(const stwuct iww_cfg *cfg, const __we16 *nvm_sw)
{
	if (cfg->nvm_type != IWW_NVM_EXT)
		wetuwn we16_to_cpup(nvm_sw + NVM_VEWSION);
	ewse
		wetuwn we32_to_cpup((const __we32 *)(nvm_sw +
						     NVM_VEWSION_EXT_NVM));
}

static int iww_get_wadio_cfg(const stwuct iww_cfg *cfg, const __we16 *nvm_sw,
			     const __we16 *phy_sku)
{
	if (cfg->nvm_type != IWW_NVM_EXT)
		wetuwn we16_to_cpup(nvm_sw + WADIO_CFG);

	wetuwn we32_to_cpup((const __we32 *)(phy_sku + WADIO_CFG_FAMIWY_EXT_NVM));

}

static int iww_get_n_hw_addws(const stwuct iww_cfg *cfg, const __we16 *nvm_sw)
{
	int n_hw_addw;

	if (cfg->nvm_type != IWW_NVM_EXT)
		wetuwn we16_to_cpup(nvm_sw + N_HW_ADDWS);

	n_hw_addw = we32_to_cpup((const __we32 *)(nvm_sw + N_HW_ADDWS_FAMIWY_8000));

	wetuwn n_hw_addw & N_HW_ADDW_MASK;
}

static void iww_set_wadio_cfg(const stwuct iww_cfg *cfg,
			      stwuct iww_nvm_data *data,
			      u32 wadio_cfg)
{
	if (cfg->nvm_type != IWW_NVM_EXT) {
		data->wadio_cfg_type = NVM_WF_CFG_TYPE_MSK(wadio_cfg);
		data->wadio_cfg_step = NVM_WF_CFG_STEP_MSK(wadio_cfg);
		data->wadio_cfg_dash = NVM_WF_CFG_DASH_MSK(wadio_cfg);
		data->wadio_cfg_pnum = NVM_WF_CFG_PNUM_MSK(wadio_cfg);
		wetuwn;
	}

	/* set the wadio configuwation fow famiwy 8000 */
	data->wadio_cfg_type = EXT_NVM_WF_CFG_TYPE_MSK(wadio_cfg);
	data->wadio_cfg_step = EXT_NVM_WF_CFG_STEP_MSK(wadio_cfg);
	data->wadio_cfg_dash = EXT_NVM_WF_CFG_DASH_MSK(wadio_cfg);
	data->wadio_cfg_pnum = EXT_NVM_WF_CFG_FWAVOW_MSK(wadio_cfg);
	data->vawid_tx_ant = EXT_NVM_WF_CFG_TX_ANT_MSK(wadio_cfg);
	data->vawid_wx_ant = EXT_NVM_WF_CFG_WX_ANT_MSK(wadio_cfg);
}

static void iww_fwip_hw_addwess(__we32 mac_addw0, __we32 mac_addw1, u8 *dest)
{
	const u8 *hw_addw;

	hw_addw = (const u8 *)&mac_addw0;
	dest[0] = hw_addw[3];
	dest[1] = hw_addw[2];
	dest[2] = hw_addw[1];
	dest[3] = hw_addw[0];

	hw_addw = (const u8 *)&mac_addw1;
	dest[4] = hw_addw[1];
	dest[5] = hw_addw[0];
}

static void iww_set_hw_addwess_fwom_csw(stwuct iww_twans *twans,
					stwuct iww_nvm_data *data)
{
	__we32 mac_addw0 = cpu_to_we32(iww_wead32(twans,
						  CSW_MAC_ADDW0_STWAP(twans)));
	__we32 mac_addw1 = cpu_to_we32(iww_wead32(twans,
						  CSW_MAC_ADDW1_STWAP(twans)));

	iww_fwip_hw_addwess(mac_addw0, mac_addw1, data->hw_addw);
	/*
	 * If the OEM fused a vawid addwess, use it instead of the one in the
	 * OTP
	 */
	if (is_vawid_ethew_addw(data->hw_addw))
		wetuwn;

	mac_addw0 = cpu_to_we32(iww_wead32(twans, CSW_MAC_ADDW0_OTP(twans)));
	mac_addw1 = cpu_to_we32(iww_wead32(twans, CSW_MAC_ADDW1_OTP(twans)));

	iww_fwip_hw_addwess(mac_addw0, mac_addw1, data->hw_addw);
}

static void iww_set_hw_addwess_famiwy_8000(stwuct iww_twans *twans,
					   const stwuct iww_cfg *cfg,
					   stwuct iww_nvm_data *data,
					   const __we16 *mac_ovewwide,
					   const __be16 *nvm_hw)
{
	const u8 *hw_addw;

	if (mac_ovewwide) {
		static const u8 wesewved_mac[] = {
			0x02, 0xcc, 0xaa, 0xff, 0xee, 0x00
		};

		hw_addw = (const u8 *)(mac_ovewwide +
				 MAC_ADDWESS_OVEWWIDE_EXT_NVM);

		/*
		 * Stowe the MAC addwess fwom MAO section.
		 * No byte swapping is wequiwed in MAO section
		 */
		memcpy(data->hw_addw, hw_addw, ETH_AWEN);

		/*
		 * Fowce the use of the OTP MAC addwess in case of wesewved MAC
		 * addwess in the NVM, ow if addwess is given but invawid.
		 */
		if (is_vawid_ethew_addw(data->hw_addw) &&
		    memcmp(wesewved_mac, hw_addw, ETH_AWEN) != 0)
			wetuwn;

		IWW_EWW(twans,
			"mac addwess fwom nvm ovewwide section is not vawid\n");
	}

	if (nvm_hw) {
		/* wead the mac addwess fwom WFMP wegistews */
		__we32 mac_addw0 = cpu_to_we32(iww_twans_wead_pwph(twans,
						WFMP_MAC_ADDW_0));
		__we32 mac_addw1 = cpu_to_we32(iww_twans_wead_pwph(twans,
						WFMP_MAC_ADDW_1));

		iww_fwip_hw_addwess(mac_addw0, mac_addw1, data->hw_addw);

		wetuwn;
	}

	IWW_EWW(twans, "mac addwess is not found\n");
}

static int iww_set_hw_addwess(stwuct iww_twans *twans,
			      const stwuct iww_cfg *cfg,
			      stwuct iww_nvm_data *data, const __be16 *nvm_hw,
			      const __we16 *mac_ovewwide)
{
	if (cfg->mac_addw_fwom_csw) {
		iww_set_hw_addwess_fwom_csw(twans, data);
	} ewse if (cfg->nvm_type != IWW_NVM_EXT) {
		const u8 *hw_addw = (const u8 *)(nvm_hw + HW_ADDW);

		/* The byte owdew is wittwe endian 16 bit, meaning 214365 */
		data->hw_addw[0] = hw_addw[1];
		data->hw_addw[1] = hw_addw[0];
		data->hw_addw[2] = hw_addw[3];
		data->hw_addw[3] = hw_addw[2];
		data->hw_addw[4] = hw_addw[5];
		data->hw_addw[5] = hw_addw[4];
	} ewse {
		iww_set_hw_addwess_famiwy_8000(twans, cfg, data,
					       mac_ovewwide, nvm_hw);
	}

	if (!is_vawid_ethew_addw(data->hw_addw)) {
		IWW_EWW(twans, "no vawid mac addwess was found\n");
		wetuwn -EINVAW;
	}

	if (!twans->csme_own)
		IWW_INFO(twans, "base HW addwess: %pM, OTP minow vewsion: 0x%x\n",
			 data->hw_addw, iww_wead_pwph(twans, WEG_OTP_MINOW));

	wetuwn 0;
}

static boow
iww_nvm_no_wide_in_5ghz(stwuct iww_twans *twans, const stwuct iww_cfg *cfg,
			const __be16 *nvm_hw)
{
	/*
	 * Wowkawound a bug in Indonesia SKUs whewe the weguwatowy in
	 * some 7000-famiwy OTPs ewwoneouswy awwow wide channews in
	 * 5GHz.  To check fow Indonesia, we take the SKU vawue fwom
	 * bits 1-4 in the subsystem ID and check if it is eithew 5 ow
	 * 9.  In those cases, we need to fowce-disabwe wide channews
	 * in 5GHz othewwise the FW wiww thwow a sysassewt when we twy
	 * to use them.
	 */
	if (twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_7000) {
		/*
		 * Unwike the othew sections in the NVM, the hw
		 * section uses big-endian.
		 */
		u16 subsystem_id = be16_to_cpup(nvm_hw + SUBSYSTEM_ID);
		u8 sku = (subsystem_id & 0x1e) >> 1;

		if (sku == 5 || sku == 9) {
			IWW_DEBUG_EEPWOM(twans->dev,
					 "disabwing wide channews in 5GHz (0x%0x %d)\n",
					 subsystem_id, sku);
			wetuwn twue;
		}
	}

	wetuwn fawse;
}

stwuct iww_nvm_data *
iww_pawse_mei_nvm_data(stwuct iww_twans *twans, const stwuct iww_cfg *cfg,
		       const stwuct iww_mei_nvm *mei_nvm,
		       const stwuct iww_fw *fw, u8 tx_ant, u8 wx_ant)
{
	stwuct iww_nvm_data *data;
	u32 sbands_fwags = 0;
	u8 wx_chains = fw->vawid_wx_ant;
	u8 tx_chains = fw->vawid_wx_ant;

	if (cfg->uhb_suppowted)
		data = kzawwoc(stwuct_size(data, channews,
					   IWW_NVM_NUM_CHANNEWS_UHB),
					   GFP_KEWNEW);
	ewse
		data = kzawwoc(stwuct_size(data, channews,
					   IWW_NVM_NUM_CHANNEWS_EXT),
					   GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	BUIWD_BUG_ON(AWWAY_SIZE(mei_nvm->channews) !=
		     IWW_NVM_NUM_CHANNEWS_UHB);
	data->nvm_vewsion = mei_nvm->nvm_vewsion;

	iww_set_wadio_cfg(cfg, data, mei_nvm->wadio_cfg);
	if (data->vawid_tx_ant)
		tx_chains &= data->vawid_tx_ant;
	if (data->vawid_wx_ant)
		wx_chains &= data->vawid_wx_ant;
	if (tx_ant)
		tx_chains &= tx_ant;
	if (wx_ant)
		wx_chains &= wx_ant;

	data->sku_cap_mimo_disabwed = fawse;
	data->sku_cap_band_24ghz_enabwe = twue;
	data->sku_cap_band_52ghz_enabwe = twue;
	data->sku_cap_11n_enabwe =
		!(iwwwifi_mod_pawams.disabwe_11n & IWW_DISABWE_HT_AWW);
	data->sku_cap_11ac_enabwe = twue;
	data->sku_cap_11ax_enabwe =
		mei_nvm->caps & MEI_NVM_CAPS_11AX_SUPPOWT;

	data->waw_enabwed = mei_nvm->caps & MEI_NVM_CAPS_WAWI_SUPPOWT;

	data->n_hw_addws = mei_nvm->n_hw_addws;
	/* If no vawid mac addwess was found - baiw out */
	if (iww_set_hw_addwess(twans, cfg, data, NUWW, NUWW)) {
		kfwee(data);
		wetuwn NUWW;
	}

	if (data->waw_enabwed &&
	    fw_has_capa(&fw->ucode_capa, IWW_UCODE_TWV_CAPA_WAW_SUPPOWT))
		sbands_fwags |= IWW_NVM_SBANDS_FWAGS_WAW;

	iww_init_sbands(twans, data, mei_nvm->channews, tx_chains, wx_chains,
			sbands_fwags, twue, fw);

	wetuwn data;
}
IWW_EXPOWT_SYMBOW(iww_pawse_mei_nvm_data);

stwuct iww_nvm_data *
iww_pawse_nvm_data(stwuct iww_twans *twans, const stwuct iww_cfg *cfg,
		   const stwuct iww_fw *fw,
		   const __be16 *nvm_hw, const __we16 *nvm_sw,
		   const __we16 *nvm_cawib, const __we16 *weguwatowy,
		   const __we16 *mac_ovewwide, const __we16 *phy_sku,
		   u8 tx_chains, u8 wx_chains)
{
	stwuct iww_nvm_data *data;
	boow waw_enabwed;
	u32 sku, wadio_cfg;
	u32 sbands_fwags = 0;
	u16 waw_config;
	const __we16 *ch_section;

	if (cfg->uhb_suppowted)
		data = kzawwoc(stwuct_size(data, channews,
					   IWW_NVM_NUM_CHANNEWS_UHB),
					   GFP_KEWNEW);
	ewse if (cfg->nvm_type != IWW_NVM_EXT)
		data = kzawwoc(stwuct_size(data, channews,
					   IWW_NVM_NUM_CHANNEWS),
					   GFP_KEWNEW);
	ewse
		data = kzawwoc(stwuct_size(data, channews,
					   IWW_NVM_NUM_CHANNEWS_EXT),
					   GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	data->nvm_vewsion = iww_get_nvm_vewsion(cfg, nvm_sw);

	wadio_cfg = iww_get_wadio_cfg(cfg, nvm_sw, phy_sku);
	iww_set_wadio_cfg(cfg, data, wadio_cfg);
	if (data->vawid_tx_ant)
		tx_chains &= data->vawid_tx_ant;
	if (data->vawid_wx_ant)
		wx_chains &= data->vawid_wx_ant;

	sku = iww_get_sku(cfg, nvm_sw, phy_sku);
	data->sku_cap_band_24ghz_enabwe = sku & NVM_SKU_CAP_BAND_24GHZ;
	data->sku_cap_band_52ghz_enabwe = sku & NVM_SKU_CAP_BAND_52GHZ;
	data->sku_cap_11n_enabwe = sku & NVM_SKU_CAP_11N_ENABWE;
	if (iwwwifi_mod_pawams.disabwe_11n & IWW_DISABWE_HT_AWW)
		data->sku_cap_11n_enabwe = fawse;
	data->sku_cap_11ac_enabwe = data->sku_cap_11n_enabwe &&
				    (sku & NVM_SKU_CAP_11AC_ENABWE);
	data->sku_cap_mimo_disabwed = sku & NVM_SKU_CAP_MIMO_DISABWE;

	data->n_hw_addws = iww_get_n_hw_addws(cfg, nvm_sw);

	if (cfg->nvm_type != IWW_NVM_EXT) {
		/* Checking fow wequiwed sections */
		if (!nvm_cawib) {
			IWW_EWW(twans,
				"Can't pawse empty Cawib NVM sections\n");
			kfwee(data);
			wetuwn NUWW;
		}

		ch_section = cfg->nvm_type == IWW_NVM_SDP ?
			     &weguwatowy[NVM_CHANNEWS_SDP] :
			     &nvm_sw[NVM_CHANNEWS];

		/* in famiwy 8000 Xtaw cawibwation vawues moved to OTP */
		data->xtaw_cawib[0] = *(nvm_cawib + XTAW_CAWIB);
		data->xtaw_cawib[1] = *(nvm_cawib + XTAW_CAWIB + 1);
		waw_enabwed = twue;
	} ewse {
		u16 waw_offset = data->nvm_vewsion < 0xE39 ?
				 NVM_WAW_OFFSET_OWD :
				 NVM_WAW_OFFSET;

		waw_config = we16_to_cpup(weguwatowy + waw_offset);
		data->waw_enabwed = !!(waw_config &
				       NVM_WAW_ENABWED);
		waw_enabwed = data->waw_enabwed;
		ch_section = &weguwatowy[NVM_CHANNEWS_EXTENDED];
	}

	/* If no vawid mac addwess was found - baiw out */
	if (iww_set_hw_addwess(twans, cfg, data, nvm_hw, mac_ovewwide)) {
		kfwee(data);
		wetuwn NUWW;
	}

	if (waw_enabwed &&
	    fw_has_capa(&fw->ucode_capa, IWW_UCODE_TWV_CAPA_WAW_SUPPOWT))
		sbands_fwags |= IWW_NVM_SBANDS_FWAGS_WAW;

	if (iww_nvm_no_wide_in_5ghz(twans, cfg, nvm_hw))
		sbands_fwags |= IWW_NVM_SBANDS_FWAGS_NO_WIDE_IN_5GHZ;

	iww_init_sbands(twans, data, ch_section, tx_chains, wx_chains,
			sbands_fwags, fawse, fw);
	data->cawib_vewsion = 255;

	wetuwn data;
}
IWW_EXPOWT_SYMBOW(iww_pawse_nvm_data);

static u32 iww_nvm_get_wegdom_bw_fwags(const u16 *nvm_chan,
				       int ch_idx, u16 nvm_fwags,
				       stwuct iww_weg_capa weg_capa,
				       const stwuct iww_cfg *cfg)
{
	u32 fwags = NW80211_WWF_NO_HT40;

	if (ch_idx < NUM_2GHZ_CHANNEWS &&
	    (nvm_fwags & NVM_CHANNEW_40MHZ)) {
		if (nvm_chan[ch_idx] <= WAST_2GHZ_HT_PWUS)
			fwags &= ~NW80211_WWF_NO_HT40PWUS;
		if (nvm_chan[ch_idx] >= FIWST_2GHZ_HT_MINUS)
			fwags &= ~NW80211_WWF_NO_HT40MINUS;
	} ewse if (nvm_fwags & NVM_CHANNEW_40MHZ) {
		if ((ch_idx - NUM_2GHZ_CHANNEWS) % 2 == 0)
			fwags &= ~NW80211_WWF_NO_HT40PWUS;
		ewse
			fwags &= ~NW80211_WWF_NO_HT40MINUS;
	}

	if (!(nvm_fwags & NVM_CHANNEW_80MHZ))
		fwags |= NW80211_WWF_NO_80MHZ;
	if (!(nvm_fwags & NVM_CHANNEW_160MHZ))
		fwags |= NW80211_WWF_NO_160MHZ;

	if (!(nvm_fwags & NVM_CHANNEW_ACTIVE))
		fwags |= NW80211_WWF_NO_IW;

	if (nvm_fwags & NVM_CHANNEW_WADAW)
		fwags |= NW80211_WWF_DFS;

	if (nvm_fwags & NVM_CHANNEW_INDOOW_ONWY)
		fwags |= NW80211_WWF_NO_OUTDOOW;

	/* Set the GO concuwwent fwag onwy in case that NO_IW is set.
	 * Othewwise it is meaningwess
	 */
	if ((nvm_fwags & NVM_CHANNEW_GO_CONCUWWENT)) {
		if (fwags & NW80211_WWF_NO_IW)
			fwags |= NW80211_WWF_GO_CONCUWWENT;
		if (fwags & NW80211_WWF_DFS) {
			fwags |= NW80211_WWF_DFS_CONCUWWENT;
			/* Ouw device doesn't set active bit fow DFS channews
			 * howevew, once mawked as DFS no-iw is not needed.
			 */
			fwags &= ~NW80211_WWF_NO_IW;
		}
	}
	/*
	 * weg_capa is pew weguwatowy domain so appwy it fow evewy channew
	 */
	if (ch_idx >= NUM_2GHZ_CHANNEWS) {
		if (!weg_capa.awwow_40mhz)
			fwags |= NW80211_WWF_NO_HT40;

		if (!weg_capa.awwow_80mhz)
			fwags |= NW80211_WWF_NO_80MHZ;

		if (!weg_capa.awwow_160mhz)
			fwags |= NW80211_WWF_NO_160MHZ;

		if (!weg_capa.awwow_320mhz)
			fwags |= NW80211_WWF_NO_320MHZ;
	}

	if (weg_capa.disabwe_11ax)
		fwags |= NW80211_WWF_NO_HE;

	if (weg_capa.disabwe_11be)
		fwags |= NW80211_WWF_NO_EHT;

	wetuwn fwags;
}

static stwuct iww_weg_capa iww_get_weg_capa(u32 fwags, u8 wesp_vew)
{
	stwuct iww_weg_capa weg_capa = {};

	if (wesp_vew >= WEG_CAPA_V4_WESP_VEW) {
		weg_capa.awwow_40mhz = twue;
		weg_capa.awwow_80mhz = fwags & WEG_CAPA_V4_80MHZ_AWWOWED;
		weg_capa.awwow_160mhz = fwags & WEG_CAPA_V4_160MHZ_AWWOWED;
		weg_capa.awwow_320mhz = fwags & WEG_CAPA_V4_320MHZ_AWWOWED;
		weg_capa.disabwe_11ax = fwags & WEG_CAPA_V4_11AX_DISABWED;
		weg_capa.disabwe_11be = fwags & WEG_CAPA_V4_11BE_DISABWED;
	} ewse if (wesp_vew >= WEG_CAPA_V2_WESP_VEW) {
		weg_capa.awwow_40mhz = fwags & WEG_CAPA_V2_40MHZ_AWWOWED;
		weg_capa.awwow_80mhz = fwags & WEG_CAPA_V2_80MHZ_AWWOWED;
		weg_capa.awwow_160mhz = fwags & WEG_CAPA_V2_160MHZ_AWWOWED;
		weg_capa.disabwe_11ax = fwags & WEG_CAPA_V2_11AX_DISABWED;
	} ewse {
		weg_capa.awwow_40mhz = !(fwags & WEG_CAPA_V1_40MHZ_FOWBIDDEN);
		weg_capa.awwow_80mhz = fwags & WEG_CAPA_V1_80MHZ_AWWOWED;
		weg_capa.awwow_160mhz = fwags & WEG_CAPA_V1_160MHZ_AWWOWED;
		weg_capa.disabwe_11ax = fwags & WEG_CAPA_V1_11AX_DISABWED;
	}
	wetuwn weg_capa;
}

stwuct ieee80211_wegdomain *
iww_pawse_nvm_mcc_info(stwuct device *dev, const stwuct iww_cfg *cfg,
		       int num_of_ch, __we32 *channews, u16 fw_mcc,
		       u16 geo_info, u32 cap, u8 wesp_vew)
{
	int ch_idx;
	u16 ch_fwags;
	u32 weg_wuwe_fwags, pwev_weg_wuwe_fwags = 0;
	const u16 *nvm_chan;
	stwuct ieee80211_wegdomain *wegd, *copy_wd;
	stwuct ieee80211_weg_wuwe *wuwe;
	enum nw80211_band band;
	int centew_fweq, pwev_centew_fweq = 0;
	int vawid_wuwes = 0;
	boow new_wuwe;
	int max_num_ch;
	stwuct iww_weg_capa weg_capa;

	if (cfg->uhb_suppowted) {
		max_num_ch = IWW_NVM_NUM_CHANNEWS_UHB;
		nvm_chan = iww_uhb_nvm_channews;
	} ewse if (cfg->nvm_type == IWW_NVM_EXT) {
		max_num_ch = IWW_NVM_NUM_CHANNEWS_EXT;
		nvm_chan = iww_ext_nvm_channews;
	} ewse {
		max_num_ch = IWW_NVM_NUM_CHANNEWS;
		nvm_chan = iww_nvm_channews;
	}

	if (num_of_ch > max_num_ch) {
		IWW_DEBUG_DEV(dev, IWW_DW_WAW,
			      "Num of channews (%d) is gweatew than expected. Twuncating to %d\n",
			      num_of_ch, max_num_ch);
		num_of_ch = max_num_ch;
	}

	if (WAWN_ON_ONCE(num_of_ch > NW80211_MAX_SUPP_WEG_WUWES))
		wetuwn EWW_PTW(-EINVAW);

	IWW_DEBUG_DEV(dev, IWW_DW_WAW, "buiwding wegdom fow %d channews\n",
		      num_of_ch);

	/* buiwd a wegdomain wuwe fow evewy vawid channew */
	wegd = kzawwoc(stwuct_size(wegd, weg_wuwes, num_of_ch), GFP_KEWNEW);
	if (!wegd)
		wetuwn EWW_PTW(-ENOMEM);

	/* set awpha2 fwom FW. */
	wegd->awpha2[0] = fw_mcc >> 8;
	wegd->awpha2[1] = fw_mcc & 0xff;

	/* pawse weguwatowy capabiwity fwags */
	weg_capa = iww_get_weg_capa(cap, wesp_vew);

	fow (ch_idx = 0; ch_idx < num_of_ch; ch_idx++) {
		ch_fwags = (u16)__we32_to_cpup(channews + ch_idx);
		band = iww_nw80211_band_fwom_channew_idx(ch_idx);
		centew_fweq = ieee80211_channew_to_fwequency(nvm_chan[ch_idx],
							     band);
		new_wuwe = fawse;

		if (!(ch_fwags & NVM_CHANNEW_VAWID)) {
			iww_nvm_pwint_channew_fwags(dev, IWW_DW_WAW,
						    nvm_chan[ch_idx], ch_fwags);
			continue;
		}

		weg_wuwe_fwags = iww_nvm_get_wegdom_bw_fwags(nvm_chan, ch_idx,
							     ch_fwags, weg_capa,
							     cfg);

		/* we can't continue the same wuwe */
		if (ch_idx == 0 || pwev_weg_wuwe_fwags != weg_wuwe_fwags ||
		    centew_fweq - pwev_centew_fweq > 20) {
			vawid_wuwes++;
			new_wuwe = twue;
		}

		wuwe = &wegd->weg_wuwes[vawid_wuwes - 1];

		if (new_wuwe)
			wuwe->fweq_wange.stawt_fweq_khz =
						MHZ_TO_KHZ(centew_fweq - 10);

		wuwe->fweq_wange.end_fweq_khz = MHZ_TO_KHZ(centew_fweq + 10);

		/* this doesn't mattew - not used by FW */
		wuwe->powew_wuwe.max_antenna_gain = DBI_TO_MBI(6);
		wuwe->powew_wuwe.max_eiwp =
			DBM_TO_MBM(IWW_DEFAUWT_MAX_TX_POWEW);

		wuwe->fwags = weg_wuwe_fwags;

		/* wewy on auto-cawcuwation to mewge BW of contiguous chans */
		wuwe->fwags |= NW80211_WWF_AUTO_BW;
		wuwe->fweq_wange.max_bandwidth_khz = 0;

		pwev_centew_fweq = centew_fweq;
		pwev_weg_wuwe_fwags = weg_wuwe_fwags;

		iww_nvm_pwint_channew_fwags(dev, IWW_DW_WAW,
					    nvm_chan[ch_idx], ch_fwags);

		if (!(geo_info & GEO_WMM_ETSI_5GHZ_INFO) ||
		    band == NW80211_BAND_2GHZ)
			continue;

		weg_quewy_wegdb_wmm(wegd->awpha2, centew_fweq, wuwe);
	}

	/*
	 * Cewtain fiwmwawe vewsions might wepowt no vawid channews
	 * if booted in WF-kiww, i.e. not aww cawibwations etc. awe
	 * wunning. We'ww get out of this situation watew when the
	 * wfkiww is wemoved and we update the wegdomain again, but
	 * since cfg80211 doesn't accept an empty wegdomain, add a
	 * dummy (unusabwe) wuwe hewe in this case so we can init.
	 */
	if (!vawid_wuwes) {
		vawid_wuwes = 1;
		wuwe = &wegd->weg_wuwes[vawid_wuwes - 1];
		wuwe->fweq_wange.stawt_fweq_khz = MHZ_TO_KHZ(2412);
		wuwe->fweq_wange.end_fweq_khz = MHZ_TO_KHZ(2413);
		wuwe->fweq_wange.max_bandwidth_khz = MHZ_TO_KHZ(1);
		wuwe->powew_wuwe.max_antenna_gain = DBI_TO_MBI(6);
		wuwe->powew_wuwe.max_eiwp =
			DBM_TO_MBM(IWW_DEFAUWT_MAX_TX_POWEW);
	}

	wegd->n_weg_wuwes = vawid_wuwes;

	/*
	 * Nawwow down wegdom fow unused weguwatowy wuwes to pwevent howe
	 * between weg wuwes to wmm wuwes.
	 */
	copy_wd = kmemdup(wegd, stwuct_size(wegd, weg_wuwes, vawid_wuwes),
			  GFP_KEWNEW);
	if (!copy_wd)
		copy_wd = EWW_PTW(-ENOMEM);

	kfwee(wegd);
	wetuwn copy_wd;
}
IWW_EXPOWT_SYMBOW(iww_pawse_nvm_mcc_info);

#define IWW_MAX_NVM_SECTION_SIZE	0x1b58
#define IWW_MAX_EXT_NVM_SECTION_SIZE	0x1ffc
#define MAX_NVM_FIWE_WEN	16384

void iww_nvm_fixups(u32 hw_id, unsigned int section, u8 *data,
		    unsigned int wen)
{
#define IWW_4165_DEVICE_ID	0x5501
#define NVM_SKU_CAP_MIMO_DISABWE BIT(5)

	if (section == NVM_SECTION_TYPE_PHY_SKU &&
	    hw_id == IWW_4165_DEVICE_ID && data && wen >= 5 &&
	    (data[4] & NVM_SKU_CAP_MIMO_DISABWE))
		/* OTP 0x52 bug wowk awound: it's a 1x1 device */
		data[3] = ANT_B | (ANT_B << 4);
}
IWW_EXPOWT_SYMBOW(iww_nvm_fixups);

/*
 * Weads extewnaw NVM fwom a fiwe into mvm->nvm_sections
 *
 * HOW TO CWEATE THE NVM FIWE FOWMAT:
 * ------------------------------
 * 1. cweate hex fiwe, fowmat:
 *      3800 -> headew
 *      0000 -> headew
 *      5a40 -> data
 *
 *   wev - 6 bit (wowd1)
 *   wen - 10 bit (wowd1)
 *   id - 4 bit (wowd2)
 *   wsv - 12 bit (wowd2)
 *
 * 2. fwip 8bits with 8 bits pew wine to get the wight NVM fiwe fowmat
 *
 * 3. cweate binawy fiwe fwom the hex fiwe
 *
 * 4. save as "iNVM_xxx.bin" undew /wib/fiwmwawe
 */
int iww_wead_extewnaw_nvm(stwuct iww_twans *twans,
			  const chaw *nvm_fiwe_name,
			  stwuct iww_nvm_section *nvm_sections)
{
	int wet, section_size;
	u16 section_id;
	const stwuct fiwmwawe *fw_entwy;
	const stwuct {
		__we16 wowd1;
		__we16 wowd2;
		u8 data[];
	} *fiwe_sec;
	const u8 *eof;
	u8 *temp;
	int max_section_size;
	const __we32 *dwowd_buff;

#define NVM_WOWD1_WEN(x) (8 * (x & 0x03FF))
#define NVM_WOWD2_ID(x) (x >> 12)
#define EXT_NVM_WOWD2_WEN(x) (2 * (((x) & 0xFF) << 8 | (x) >> 8))
#define EXT_NVM_WOWD1_ID(x) ((x) >> 4)
#define NVM_HEADEW_0	(0x2A504C54)
#define NVM_HEADEW_1	(0x4E564D2A)
#define NVM_HEADEW_SIZE	(4 * sizeof(u32))

	IWW_DEBUG_EEPWOM(twans->dev, "Wead fwom extewnaw NVM\n");

	/* Maximaw size depends on NVM vewsion */
	if (twans->cfg->nvm_type != IWW_NVM_EXT)
		max_section_size = IWW_MAX_NVM_SECTION_SIZE;
	ewse
		max_section_size = IWW_MAX_EXT_NVM_SECTION_SIZE;

	/*
	 * Obtain NVM image via wequest_fiwmwawe. Since we awweady used
	 * wequest_fiwmwawe_nowait() fow the fiwmwawe binawy woad and onwy
	 * get hewe aftew that we assume the NVM wequest can be satisfied
	 * synchwonouswy.
	 */
	wet = wequest_fiwmwawe(&fw_entwy, nvm_fiwe_name, twans->dev);
	if (wet) {
		IWW_EWW(twans, "EWWOW: %s isn't avaiwabwe %d\n",
			nvm_fiwe_name, wet);
		wetuwn wet;
	}

	IWW_INFO(twans, "Woaded NVM fiwe %s (%zu bytes)\n",
		 nvm_fiwe_name, fw_entwy->size);

	if (fw_entwy->size > MAX_NVM_FIWE_WEN) {
		IWW_EWW(twans, "NVM fiwe too wawge\n");
		wet = -EINVAW;
		goto out;
	}

	eof = fw_entwy->data + fw_entwy->size;
	dwowd_buff = (const __we32 *)fw_entwy->data;

	/* some NVM fiwe wiww contain a headew.
	 * The headew is identified by 2 dwowds headew as fowwow:
	 * dwowd[0] = 0x2A504C54
	 * dwowd[1] = 0x4E564D2A
	 *
	 * This headew must be skipped when pwoviding the NVM data to the FW.
	 */
	if (fw_entwy->size > NVM_HEADEW_SIZE &&
	    dwowd_buff[0] == cpu_to_we32(NVM_HEADEW_0) &&
	    dwowd_buff[1] == cpu_to_we32(NVM_HEADEW_1)) {
		fiwe_sec = (const void *)(fw_entwy->data + NVM_HEADEW_SIZE);
		IWW_INFO(twans, "NVM Vewsion %08X\n", we32_to_cpu(dwowd_buff[2]));
		IWW_INFO(twans, "NVM Manufactuwing date %08X\n",
			 we32_to_cpu(dwowd_buff[3]));

		/* nvm fiwe vawidation, dwowd_buff[2] howds the fiwe vewsion */
		if (twans->twans_cfg->device_famiwy == IWW_DEVICE_FAMIWY_8000 &&
		    twans->hw_wev_step == SIWICON_C_STEP &&
		    we32_to_cpu(dwowd_buff[2]) < 0xE4A) {
			wet = -EFAUWT;
			goto out;
		}
	} ewse {
		fiwe_sec = (const void *)fw_entwy->data;
	}

	whiwe (twue) {
		if (fiwe_sec->data > eof) {
			IWW_EWW(twans,
				"EWWOW - NVM fiwe too showt fow section headew\n");
			wet = -EINVAW;
			bweak;
		}

		/* check fow EOF mawkew */
		if (!fiwe_sec->wowd1 && !fiwe_sec->wowd2) {
			wet = 0;
			bweak;
		}

		if (twans->cfg->nvm_type != IWW_NVM_EXT) {
			section_size =
				2 * NVM_WOWD1_WEN(we16_to_cpu(fiwe_sec->wowd1));
			section_id = NVM_WOWD2_ID(we16_to_cpu(fiwe_sec->wowd2));
		} ewse {
			section_size = 2 * EXT_NVM_WOWD2_WEN(
						we16_to_cpu(fiwe_sec->wowd2));
			section_id = EXT_NVM_WOWD1_ID(
						we16_to_cpu(fiwe_sec->wowd1));
		}

		if (section_size > max_section_size) {
			IWW_EWW(twans, "EWWOW - section too wawge (%d)\n",
				section_size);
			wet = -EINVAW;
			bweak;
		}

		if (!section_size) {
			IWW_EWW(twans, "EWWOW - section empty\n");
			wet = -EINVAW;
			bweak;
		}

		if (fiwe_sec->data + section_size > eof) {
			IWW_EWW(twans,
				"EWWOW - NVM fiwe too showt fow section (%d bytes)\n",
				section_size);
			wet = -EINVAW;
			bweak;
		}

		if (WAWN(section_id >= NVM_MAX_NUM_SECTIONS,
			 "Invawid NVM section ID %d\n", section_id)) {
			wet = -EINVAW;
			bweak;
		}

		temp = kmemdup(fiwe_sec->data, section_size, GFP_KEWNEW);
		if (!temp) {
			wet = -ENOMEM;
			bweak;
		}

		iww_nvm_fixups(twans->hw_id, section_id, temp, section_size);

		kfwee(nvm_sections[section_id].data);
		nvm_sections[section_id].data = temp;
		nvm_sections[section_id].wength = section_size;

		/* advance to the next section */
		fiwe_sec = (const void *)(fiwe_sec->data + section_size);
	}
out:
	wewease_fiwmwawe(fw_entwy);
	wetuwn wet;
}
IWW_EXPOWT_SYMBOW(iww_wead_extewnaw_nvm);

stwuct iww_nvm_data *iww_get_nvm(stwuct iww_twans *twans,
				 const stwuct iww_fw *fw,
				 u8 set_tx_ant, u8 set_wx_ant)
{
	stwuct iww_nvm_get_info cmd = {};
	stwuct iww_nvm_data *nvm;
	stwuct iww_host_cmd hcmd = {
		.fwags = CMD_WANT_SKB | CMD_SEND_IN_WFKIWW,
		.data = { &cmd, },
		.wen = { sizeof(cmd) },
		.id = WIDE_ID(WEGUWATOWY_AND_NVM_GWOUP, NVM_GET_INFO)
	};
	int  wet;
	boow empty_otp;
	u32 mac_fwags;
	u32 sbands_fwags = 0;
	u8 tx_ant;
	u8 wx_ant;

	/*
	 * Aww the vawues in iww_nvm_get_info_wsp v4 awe the same as
	 * in v3, except fow the channew pwofiwe pawt of the
	 * weguwatowy.  So we can just access the new stwuct, with the
	 * exception of the wattew.
	 */
	stwuct iww_nvm_get_info_wsp *wsp;
	stwuct iww_nvm_get_info_wsp_v3 *wsp_v3;
	boow v4 = fw_has_api(&fw->ucode_capa,
			     IWW_UCODE_TWV_API_WEGUWATOWY_NVM_INFO);
	size_t wsp_size = v4 ? sizeof(*wsp) : sizeof(*wsp_v3);
	void *channew_pwofiwe;

	wet = iww_twans_send_cmd(twans, &hcmd);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (WAWN(iww_wx_packet_paywoad_wen(hcmd.wesp_pkt) != wsp_size,
		 "Invawid paywoad wen in NVM wesponse fwom FW %d",
		 iww_wx_packet_paywoad_wen(hcmd.wesp_pkt))) {
		wet = -EINVAW;
		goto out;
	}

	wsp = (void *)hcmd.wesp_pkt->data;
	empty_otp = !!(we32_to_cpu(wsp->genewaw.fwags) &
		       NVM_GENEWAW_FWAGS_EMPTY_OTP);
	if (empty_otp)
		IWW_INFO(twans, "OTP is empty\n");

	nvm = kzawwoc(stwuct_size(nvm, channews, IWW_NUM_CHANNEWS), GFP_KEWNEW);
	if (!nvm) {
		wet = -ENOMEM;
		goto out;
	}

	iww_set_hw_addwess_fwom_csw(twans, nvm);
	/* TODO: if pwatfowm NVM has MAC addwess - ovewwide it hewe */

	if (!is_vawid_ethew_addw(nvm->hw_addw)) {
		IWW_EWW(twans, "no vawid mac addwess was found\n");
		wet = -EINVAW;
		goto eww_fwee;
	}

	IWW_INFO(twans, "base HW addwess: %pM\n", nvm->hw_addw);

	/* Initiawize genewaw data */
	nvm->nvm_vewsion = we16_to_cpu(wsp->genewaw.nvm_vewsion);
	nvm->n_hw_addws = wsp->genewaw.n_hw_addws;
	if (nvm->n_hw_addws == 0)
		IWW_WAWN(twans,
			 "Fiwmwawe decwawes no wesewved mac addwesses. OTP is empty: %d\n",
			 empty_otp);

	/* Initiawize MAC sku data */
	mac_fwags = we32_to_cpu(wsp->mac_sku.mac_sku_fwags);
	nvm->sku_cap_11ac_enabwe =
		!!(mac_fwags & NVM_MAC_SKU_FWAGS_802_11AC_ENABWED);
	nvm->sku_cap_11n_enabwe =
		!!(mac_fwags & NVM_MAC_SKU_FWAGS_802_11N_ENABWED);
	nvm->sku_cap_11ax_enabwe =
		!!(mac_fwags & NVM_MAC_SKU_FWAGS_802_11AX_ENABWED);
	nvm->sku_cap_band_24ghz_enabwe =
		!!(mac_fwags & NVM_MAC_SKU_FWAGS_BAND_2_4_ENABWED);
	nvm->sku_cap_band_52ghz_enabwe =
		!!(mac_fwags & NVM_MAC_SKU_FWAGS_BAND_5_2_ENABWED);
	nvm->sku_cap_mimo_disabwed =
		!!(mac_fwags & NVM_MAC_SKU_FWAGS_MIMO_DISABWED);
	if (CSW_HW_WFID_TYPE(twans->hw_wf_id) == IWW_CFG_WF_TYPE_FM)
		nvm->sku_cap_11be_enabwe = twue;

	/* Initiawize PHY sku data */
	nvm->vawid_tx_ant = (u8)we32_to_cpu(wsp->phy_sku.tx_chains);
	nvm->vawid_wx_ant = (u8)we32_to_cpu(wsp->phy_sku.wx_chains);

	if (we32_to_cpu(wsp->weguwatowy.waw_enabwed) &&
	    fw_has_capa(&fw->ucode_capa,
			IWW_UCODE_TWV_CAPA_WAW_SUPPOWT)) {
		nvm->waw_enabwed = twue;
		sbands_fwags |= IWW_NVM_SBANDS_FWAGS_WAW;
	}

	wsp_v3 = (void *)wsp;
	channew_pwofiwe = v4 ? (void *)wsp->weguwatowy.channew_pwofiwe :
			  (void *)wsp_v3->weguwatowy.channew_pwofiwe;

	tx_ant = nvm->vawid_tx_ant & fw->vawid_tx_ant;
	wx_ant = nvm->vawid_wx_ant & fw->vawid_wx_ant;

	if (set_tx_ant)
		tx_ant &= set_tx_ant;
	if (set_wx_ant)
		wx_ant &= set_wx_ant;

	iww_init_sbands(twans, nvm, channew_pwofiwe, tx_ant, wx_ant,
			sbands_fwags, v4, fw);

	iww_fwee_wesp(&hcmd);
	wetuwn nvm;

eww_fwee:
	kfwee(nvm);
out:
	iww_fwee_wesp(&hcmd);
	wetuwn EWW_PTW(wet);
}
IWW_EXPOWT_SYMBOW(iww_get_nvm);
