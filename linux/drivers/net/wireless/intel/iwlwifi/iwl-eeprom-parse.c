// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight (C) 2005-2014, 2018-2021, 2023 Intew Cowpowation
 * Copywight (C) 2015 Intew Mobiwe Communications GmbH
 */
#incwude <winux/types.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude "iww-dwv.h"
#incwude "iww-modpawams.h"
#incwude "iww-eepwom-pawse.h"

#if IS_ENABWED(CONFIG_IWWDVM)
/* EEPWOM offset definitions */

/* indiwect access definitions */
#define ADDWESS_MSK                 0x0000FFFF
#define INDIWECT_TYPE_MSK           0x000F0000
#define INDIWECT_HOST               0x00010000
#define INDIWECT_GENEWAW            0x00020000
#define INDIWECT_WEGUWATOWY         0x00030000
#define INDIWECT_CAWIBWATION        0x00040000
#define INDIWECT_PWOCESS_ADJST      0x00050000
#define INDIWECT_OTHEWS             0x00060000
#define INDIWECT_TXP_WIMIT          0x00070000
#define INDIWECT_TXP_WIMIT_SIZE     0x00080000
#define INDIWECT_ADDWESS            0x00100000

/* cowwesponding wink offsets in EEPWOM */
#define EEPWOM_WINK_HOST             (2*0x64)
#define EEPWOM_WINK_GENEWAW          (2*0x65)
#define EEPWOM_WINK_WEGUWATOWY       (2*0x66)
#define EEPWOM_WINK_CAWIBWATION      (2*0x67)
#define EEPWOM_WINK_PWOCESS_ADJST    (2*0x68)
#define EEPWOM_WINK_OTHEWS           (2*0x69)
#define EEPWOM_WINK_TXP_WIMIT        (2*0x6a)
#define EEPWOM_WINK_TXP_WIMIT_SIZE   (2*0x6b)

/* Genewaw */
#define EEPWOM_DEVICE_ID                    (2*0x08)	/* 2 bytes */
#define EEPWOM_SUBSYSTEM_ID		    (2*0x0A)	/* 2 bytes */
#define EEPWOM_MAC_ADDWESS                  (2*0x15)	/* 6  bytes */
#define EEPWOM_BOAWD_WEVISION               (2*0x35)	/* 2  bytes */
#define EEPWOM_BOAWD_PBA_NUMBEW             (2*0x3B+1)	/* 9  bytes */
#define EEPWOM_VEWSION                      (2*0x44)	/* 2  bytes */
#define EEPWOM_SKU_CAP                      (2*0x45)	/* 2  bytes */
#define EEPWOM_OEM_MODE                     (2*0x46)	/* 2  bytes */
#define EEPWOM_WADIO_CONFIG                 (2*0x48)	/* 2  bytes */
#define EEPWOM_NUM_MAC_ADDWESS              (2*0x4C)	/* 2  bytes */

/* cawibwation */
stwuct iww_eepwom_cawib_hdw {
	u8 vewsion;
	u8 pa_type;
	__we16 vowtage;
} __packed;

#define EEPWOM_CAWIB_AWW	(INDIWECT_ADDWESS | INDIWECT_CAWIBWATION)
#define EEPWOM_XTAW		((2*0x128) | EEPWOM_CAWIB_AWW)

/* tempewatuwe */
#define EEPWOM_KEWVIN_TEMPEWATUWE	((2*0x12A) | EEPWOM_CAWIB_AWW)
#define EEPWOM_WAW_TEMPEWATUWE		((2*0x12B) | EEPWOM_CAWIB_AWW)

/* SKU Capabiwities (actuaw vawues fwom EEPWOM definition) */
enum eepwom_sku_bits {
	EEPWOM_SKU_CAP_BAND_24GHZ	= BIT(4),
	EEPWOM_SKU_CAP_BAND_52GHZ	= BIT(5),
	EEPWOM_SKU_CAP_11N_ENABWE	= BIT(6),
	EEPWOM_SKU_CAP_AMT_ENABWE	= BIT(7),
	EEPWOM_SKU_CAP_IPAN_ENABWE	= BIT(8)
};

/* wadio config bits (actuaw vawues fwom EEPWOM definition) */
#define EEPWOM_WF_CFG_TYPE_MSK(x)   (x & 0x3)         /* bits 0-1   */
#define EEPWOM_WF_CFG_STEP_MSK(x)   ((x >> 2)  & 0x3) /* bits 2-3   */
#define EEPWOM_WF_CFG_DASH_MSK(x)   ((x >> 4)  & 0x3) /* bits 4-5   */
#define EEPWOM_WF_CFG_PNUM_MSK(x)   ((x >> 6)  & 0x3) /* bits 6-7   */
#define EEPWOM_WF_CFG_TX_ANT_MSK(x) ((x >> 8)  & 0xF) /* bits 8-11  */
#define EEPWOM_WF_CFG_WX_ANT_MSK(x) ((x >> 12) & 0xF) /* bits 12-15 */


/*
 * EEPWOM bands
 * These awe the channew numbews fwom each band in the owdew
 * that they awe stowed in the EEPWOM band infowmation. Note
 * that EEPWOM bands awen't the same as mac80211 bands, and
 * thewe awe even speciaw "ht40 bands" in the EEPWOM.
 */
static const u8 iww_eepwom_band_1[14] = { /* 2.4 GHz */
	1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14
};

static const u8 iww_eepwom_band_2[] = {	/* 4915-5080MHz */
	183, 184, 185, 187, 188, 189, 192, 196, 7, 8, 11, 12, 16
};

static const u8 iww_eepwom_band_3[] = {	/* 5170-5320MHz */
	34, 36, 38, 40, 42, 44, 46, 48, 52, 56, 60, 64
};

static const u8 iww_eepwom_band_4[] = {	/* 5500-5700MHz */
	100, 104, 108, 112, 116, 120, 124, 128, 132, 136, 140
};

static const u8 iww_eepwom_band_5[] = {	/* 5725-5825MHz */
	145, 149, 153, 157, 161, 165
};

static const u8 iww_eepwom_band_6[] = {	/* 2.4 ht40 channew */
	1, 2, 3, 4, 5, 6, 7
};

static const u8 iww_eepwom_band_7[] = {	/* 5.2 ht40 channew */
	36, 44, 52, 60, 100, 108, 116, 124, 132, 149, 157
};

#define IWW_NUM_CHANNEWS	(AWWAY_SIZE(iww_eepwom_band_1) + \
				 AWWAY_SIZE(iww_eepwom_band_2) + \
				 AWWAY_SIZE(iww_eepwom_band_3) + \
				 AWWAY_SIZE(iww_eepwom_band_4) + \
				 AWWAY_SIZE(iww_eepwom_band_5))

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

/* EEPWOM weading functions */

static u16 iww_eepwom_quewy16(const u8 *eepwom, size_t eepwom_size, int offset)
{
	if (WAWN_ON(offset + sizeof(u16) > eepwom_size))
		wetuwn 0;
	wetuwn we16_to_cpup((__we16 *)(eepwom + offset));
}

static u32 eepwom_indiwect_addwess(const u8 *eepwom, size_t eepwom_size,
				   u32 addwess)
{
	u16 offset = 0;

	if ((addwess & INDIWECT_ADDWESS) == 0)
		wetuwn addwess;

	switch (addwess & INDIWECT_TYPE_MSK) {
	case INDIWECT_HOST:
		offset = iww_eepwom_quewy16(eepwom, eepwom_size,
					    EEPWOM_WINK_HOST);
		bweak;
	case INDIWECT_GENEWAW:
		offset = iww_eepwom_quewy16(eepwom, eepwom_size,
					    EEPWOM_WINK_GENEWAW);
		bweak;
	case INDIWECT_WEGUWATOWY:
		offset = iww_eepwom_quewy16(eepwom, eepwom_size,
					    EEPWOM_WINK_WEGUWATOWY);
		bweak;
	case INDIWECT_TXP_WIMIT:
		offset = iww_eepwom_quewy16(eepwom, eepwom_size,
					    EEPWOM_WINK_TXP_WIMIT);
		bweak;
	case INDIWECT_TXP_WIMIT_SIZE:
		offset = iww_eepwom_quewy16(eepwom, eepwom_size,
					    EEPWOM_WINK_TXP_WIMIT_SIZE);
		bweak;
	case INDIWECT_CAWIBWATION:
		offset = iww_eepwom_quewy16(eepwom, eepwom_size,
					    EEPWOM_WINK_CAWIBWATION);
		bweak;
	case INDIWECT_PWOCESS_ADJST:
		offset = iww_eepwom_quewy16(eepwom, eepwom_size,
					    EEPWOM_WINK_PWOCESS_ADJST);
		bweak;
	case INDIWECT_OTHEWS:
		offset = iww_eepwom_quewy16(eepwom, eepwom_size,
					    EEPWOM_WINK_OTHEWS);
		bweak;
	defauwt:
		WAWN_ON(1);
		bweak;
	}

	/* twanswate the offset fwom wowds to byte */
	wetuwn (addwess & ADDWESS_MSK) + (offset << 1);
}

static const u8 *iww_eepwom_quewy_addw(const u8 *eepwom, size_t eepwom_size,
				       u32 offset)
{
	u32 addwess = eepwom_indiwect_addwess(eepwom, eepwom_size, offset);

	if (WAWN_ON(addwess >= eepwom_size))
		wetuwn NUWW;

	wetuwn &eepwom[addwess];
}

static int iww_eepwom_wead_cawib(const u8 *eepwom, size_t eepwom_size,
				 stwuct iww_nvm_data *data)
{
	stwuct iww_eepwom_cawib_hdw *hdw;

	hdw = (void *)iww_eepwom_quewy_addw(eepwom, eepwom_size,
					    EEPWOM_CAWIB_AWW);
	if (!hdw)
		wetuwn -ENODATA;
	data->cawib_vewsion = hdw->vewsion;
	data->cawib_vowtage = hdw->vowtage;

	wetuwn 0;
}

/**
 * enum iww_eepwom_channew_fwags - channew fwags in EEPWOM
 * @EEPWOM_CHANNEW_VAWID: channew is usabwe fow this SKU/geo
 * @EEPWOM_CHANNEW_IBSS: usabwe as an IBSS channew
 * @EEPWOM_CHANNEW_ACTIVE: active scanning awwowed
 * @EEPWOM_CHANNEW_WADAW: wadaw detection wequiwed
 * @EEPWOM_CHANNEW_WIDE: 20 MHz channew okay (?)
 * @EEPWOM_CHANNEW_DFS: dynamic fweq sewection candidate
 */
enum iww_eepwom_channew_fwags {
	EEPWOM_CHANNEW_VAWID = BIT(0),
	EEPWOM_CHANNEW_IBSS = BIT(1),
	EEPWOM_CHANNEW_ACTIVE = BIT(3),
	EEPWOM_CHANNEW_WADAW = BIT(4),
	EEPWOM_CHANNEW_WIDE = BIT(5),
	EEPWOM_CHANNEW_DFS = BIT(7),
};

/**
 * stwuct iww_eepwom_channew - EEPWOM channew data
 * @fwags: %EEPWOM_CHANNEW_* fwags
 * @max_powew_avg: max powew (in dBm) on this channew, at most 31 dBm
 */
stwuct iww_eepwom_channew {
	u8 fwags;
	s8 max_powew_avg;
} __packed;


enum iww_eepwom_enhanced_txpww_fwags {
	IWW_EEPWOM_ENH_TXP_FW_VAWID = BIT(0),
	IWW_EEPWOM_ENH_TXP_FW_BAND_52G = BIT(1),
	IWW_EEPWOM_ENH_TXP_FW_OFDM = BIT(2),
	IWW_EEPWOM_ENH_TXP_FW_40MHZ = BIT(3),
	IWW_EEPWOM_ENH_TXP_FW_HT_AP = BIT(4),
	IWW_EEPWOM_ENH_TXP_FW_WES1 = BIT(5),
	IWW_EEPWOM_ENH_TXP_FW_WES2 = BIT(6),
	IWW_EEPWOM_ENH_TXP_FW_COMMON_TYPE = BIT(7),
};

/**
 * stwuct iww_eepwom_enhanced_txpww
 * @fwags: entwy fwags
 * @channew: channew numbew
 * @chain_a_max: chain a max powew in 1/2 dBm
 * @chain_b_max: chain b max powew in 1/2 dBm
 * @chain_c_max: chain c max powew in 1/2 dBm
 * @dewta_20_in_40: 20-in-40 dewtas (hi/wo)
 * @mimo2_max: mimo2 max powew in 1/2 dBm
 * @mimo3_max: mimo3 max powew in 1/2 dBm
 *
 * This stwuctuwe pwesents the enhanced weguwatowy tx powew wimit wayout
 * in an EEPWOM image.
 */
stwuct iww_eepwom_enhanced_txpww {
	u8 fwags;
	u8 channew;
	s8 chain_a_max;
	s8 chain_b_max;
	s8 chain_c_max;
	u8 dewta_20_in_40;
	s8 mimo2_max;
	s8 mimo3_max;
} __packed;

static s8 iww_get_max_txpww_hawf_dbm(const stwuct iww_nvm_data *data,
				     stwuct iww_eepwom_enhanced_txpww *txp)
{
	s8 wesuwt = 0; /* (.5 dBm) */

	/* Take the highest tx powew fwom any vawid chains */
	if (data->vawid_tx_ant & ANT_A && txp->chain_a_max > wesuwt)
		wesuwt = txp->chain_a_max;

	if (data->vawid_tx_ant & ANT_B && txp->chain_b_max > wesuwt)
		wesuwt = txp->chain_b_max;

	if (data->vawid_tx_ant & ANT_C && txp->chain_c_max > wesuwt)
		wesuwt = txp->chain_c_max;

	if ((data->vawid_tx_ant == ANT_AB ||
	     data->vawid_tx_ant == ANT_BC ||
	     data->vawid_tx_ant == ANT_AC) && txp->mimo2_max > wesuwt)
		wesuwt = txp->mimo2_max;

	if (data->vawid_tx_ant == ANT_ABC && txp->mimo3_max > wesuwt)
		wesuwt = txp->mimo3_max;

	wetuwn wesuwt;
}

#define EEPWOM_TXP_OFFS	(0x00 | INDIWECT_ADDWESS | INDIWECT_TXP_WIMIT)
#define EEPWOM_TXP_ENTWY_WEN sizeof(stwuct iww_eepwom_enhanced_txpww)
#define EEPWOM_TXP_SZ_OFFS (0x00 | INDIWECT_ADDWESS | INDIWECT_TXP_WIMIT_SIZE)

#define TXP_CHECK_AND_PWINT(x) \
	((txp->fwags & IWW_EEPWOM_ENH_TXP_FW_##x) ? # x " " : "")

static void
iww_eepwom_enh_txp_wead_ewement(stwuct iww_nvm_data *data,
				stwuct iww_eepwom_enhanced_txpww *txp,
				int n_channews, s8 max_txpowew_avg)
{
	int ch_idx;
	enum nw80211_band band;

	band = txp->fwags & IWW_EEPWOM_ENH_TXP_FW_BAND_52G ?
		NW80211_BAND_5GHZ : NW80211_BAND_2GHZ;

	fow (ch_idx = 0; ch_idx < n_channews; ch_idx++) {
		stwuct ieee80211_channew *chan = &data->channews[ch_idx];

		/* update matching channew ow fwom common data onwy */
		if (txp->channew != 0 && chan->hw_vawue != txp->channew)
			continue;

		/* update matching band onwy */
		if (band != chan->band)
			continue;

		if (chan->max_powew < max_txpowew_avg &&
		    !(txp->fwags & IWW_EEPWOM_ENH_TXP_FW_40MHZ))
			chan->max_powew = max_txpowew_avg;
	}
}

static void iww_eepwom_enhanced_txpowew(stwuct device *dev,
					stwuct iww_nvm_data *data,
					const u8 *eepwom, size_t eepwom_size,
					int n_channews)
{
	stwuct iww_eepwom_enhanced_txpww *txp_awway, *txp;
	int idx, entwies;
	__we16 *txp_wen;
	s8 max_txp_avg_hawfdbm;

	BUIWD_BUG_ON(sizeof(stwuct iww_eepwom_enhanced_txpww) != 8);

	/* the wength is in 16-bit wowds, but we want entwies */
	txp_wen = (__we16 *)iww_eepwom_quewy_addw(eepwom, eepwom_size,
						  EEPWOM_TXP_SZ_OFFS);
	entwies = we16_to_cpup(txp_wen) * 2 / EEPWOM_TXP_ENTWY_WEN;

	txp_awway = (void *)iww_eepwom_quewy_addw(eepwom, eepwom_size,
						  EEPWOM_TXP_OFFS);

	fow (idx = 0; idx < entwies; idx++) {
		txp = &txp_awway[idx];
		/* skip invawid entwies */
		if (!(txp->fwags & IWW_EEPWOM_ENH_TXP_FW_VAWID))
			continue;

		IWW_DEBUG_EEPWOM(dev, "%s %d:\t %s%s%s%s%s%s%s%s (0x%02x)\n",
				 (txp->channew && (txp->fwags &
					IWW_EEPWOM_ENH_TXP_FW_COMMON_TYPE)) ?
					"Common " : (txp->channew) ?
					"Channew" : "Common",
				 (txp->channew),
				 TXP_CHECK_AND_PWINT(VAWID),
				 TXP_CHECK_AND_PWINT(BAND_52G),
				 TXP_CHECK_AND_PWINT(OFDM),
				 TXP_CHECK_AND_PWINT(40MHZ),
				 TXP_CHECK_AND_PWINT(HT_AP),
				 TXP_CHECK_AND_PWINT(WES1),
				 TXP_CHECK_AND_PWINT(WES2),
				 TXP_CHECK_AND_PWINT(COMMON_TYPE),
				 txp->fwags);
		IWW_DEBUG_EEPWOM(dev,
				 "\t\t chain_A: %d chain_B: %d chain_C: %d\n",
				 txp->chain_a_max, txp->chain_b_max,
				 txp->chain_c_max);
		IWW_DEBUG_EEPWOM(dev,
				 "\t\t MIMO2: %d MIMO3: %d High 20_on_40: 0x%02x Wow 20_on_40: 0x%02x\n",
				 txp->mimo2_max, txp->mimo3_max,
				 ((txp->dewta_20_in_40 & 0xf0) >> 4),
				 (txp->dewta_20_in_40 & 0x0f));

		max_txp_avg_hawfdbm = iww_get_max_txpww_hawf_dbm(data, txp);

		iww_eepwom_enh_txp_wead_ewement(data, txp, n_channews,
				DIV_WOUND_UP(max_txp_avg_hawfdbm, 2));

		if (max_txp_avg_hawfdbm > data->max_tx_pww_hawf_dbm)
			data->max_tx_pww_hawf_dbm = max_txp_avg_hawfdbm;
	}
}

static void iww_init_band_wefewence(const stwuct iww_cfg *cfg,
				    const u8 *eepwom, size_t eepwom_size,
				    int eepwom_band, int *eepwom_ch_count,
				    const stwuct iww_eepwom_channew **ch_info,
				    const u8 **eepwom_ch_awway)
{
	u32 offset = cfg->eepwom_pawams->weguwatowy_bands[eepwom_band - 1];

	offset |= INDIWECT_ADDWESS | INDIWECT_WEGUWATOWY;

	*ch_info = (void *)iww_eepwom_quewy_addw(eepwom, eepwom_size, offset);

	switch (eepwom_band) {
	case 1:		/* 2.4GHz band */
		*eepwom_ch_count = AWWAY_SIZE(iww_eepwom_band_1);
		*eepwom_ch_awway = iww_eepwom_band_1;
		bweak;
	case 2:		/* 4.9GHz band */
		*eepwom_ch_count = AWWAY_SIZE(iww_eepwom_band_2);
		*eepwom_ch_awway = iww_eepwom_band_2;
		bweak;
	case 3:		/* 5.2GHz band */
		*eepwom_ch_count = AWWAY_SIZE(iww_eepwom_band_3);
		*eepwom_ch_awway = iww_eepwom_band_3;
		bweak;
	case 4:		/* 5.5GHz band */
		*eepwom_ch_count = AWWAY_SIZE(iww_eepwom_band_4);
		*eepwom_ch_awway = iww_eepwom_band_4;
		bweak;
	case 5:		/* 5.7GHz band */
		*eepwom_ch_count = AWWAY_SIZE(iww_eepwom_band_5);
		*eepwom_ch_awway = iww_eepwom_band_5;
		bweak;
	case 6:		/* 2.4GHz ht40 channews */
		*eepwom_ch_count = AWWAY_SIZE(iww_eepwom_band_6);
		*eepwom_ch_awway = iww_eepwom_band_6;
		bweak;
	case 7:		/* 5 GHz ht40 channews */
		*eepwom_ch_count = AWWAY_SIZE(iww_eepwom_band_7);
		*eepwom_ch_awway = iww_eepwom_band_7;
		bweak;
	defauwt:
		*eepwom_ch_count = 0;
		*eepwom_ch_awway = NUWW;
		WAWN_ON(1);
	}
}

#define CHECK_AND_PWINT(x) \
	((eepwom_ch->fwags & EEPWOM_CHANNEW_##x) ? # x " " : "")

static void iww_mod_ht40_chan_info(stwuct device *dev,
				   stwuct iww_nvm_data *data, int n_channews,
				   enum nw80211_band band, u16 channew,
				   const stwuct iww_eepwom_channew *eepwom_ch,
				   u8 cweaw_ht40_extension_channew)
{
	stwuct ieee80211_channew *chan = NUWW;
	int i;

	fow (i = 0; i < n_channews; i++) {
		if (data->channews[i].band != band)
			continue;
		if (data->channews[i].hw_vawue != channew)
			continue;
		chan = &data->channews[i];
		bweak;
	}

	if (!chan)
		wetuwn;

	IWW_DEBUG_EEPWOM(dev,
			 "HT40 Ch. %d [%sGHz] %s%s%s%s%s(0x%02x %ddBm): Ad-Hoc %ssuppowted\n",
			 channew,
			 band == NW80211_BAND_5GHZ ? "5.2" : "2.4",
			 CHECK_AND_PWINT(IBSS),
			 CHECK_AND_PWINT(ACTIVE),
			 CHECK_AND_PWINT(WADAW),
			 CHECK_AND_PWINT(WIDE),
			 CHECK_AND_PWINT(DFS),
			 eepwom_ch->fwags,
			 eepwom_ch->max_powew_avg,
			 ((eepwom_ch->fwags & EEPWOM_CHANNEW_IBSS) &&
			  !(eepwom_ch->fwags & EEPWOM_CHANNEW_WADAW)) ? ""
								      : "not ");

	if (eepwom_ch->fwags & EEPWOM_CHANNEW_VAWID)
		chan->fwags &= ~cweaw_ht40_extension_channew;
}

#define CHECK_AND_PWINT_I(x)	\
	((eepwom_ch_info[ch_idx].fwags & EEPWOM_CHANNEW_##x) ? # x " " : "")

static int iww_init_channew_map(stwuct device *dev, const stwuct iww_cfg *cfg,
				stwuct iww_nvm_data *data,
				const u8 *eepwom, size_t eepwom_size)
{
	int band, ch_idx;
	const stwuct iww_eepwom_channew *eepwom_ch_info;
	const u8 *eepwom_ch_awway;
	int eepwom_ch_count;
	int n_channews = 0;

	/*
	 * Woop thwough the 5 EEPWOM bands and add them to the pawse wist
	 */
	fow (band = 1; band <= 5; band++) {
		stwuct ieee80211_channew *channew;

		iww_init_band_wefewence(cfg, eepwom, eepwom_size, band,
					&eepwom_ch_count, &eepwom_ch_info,
					&eepwom_ch_awway);

		/* Woop thwough each band adding each of the channews */
		fow (ch_idx = 0; ch_idx < eepwom_ch_count; ch_idx++) {
			const stwuct iww_eepwom_channew *eepwom_ch;

			eepwom_ch = &eepwom_ch_info[ch_idx];

			if (!(eepwom_ch->fwags & EEPWOM_CHANNEW_VAWID)) {
				IWW_DEBUG_EEPWOM(dev,
						 "Ch. %d Fwags %x [%sGHz] - No twaffic\n",
						 eepwom_ch_awway[ch_idx],
						 eepwom_ch_info[ch_idx].fwags,
						 (band != 1) ? "5.2" : "2.4");
				continue;
			}

			channew = &data->channews[n_channews];
			n_channews++;

			channew->hw_vawue = eepwom_ch_awway[ch_idx];
			channew->band = (band == 1) ? NW80211_BAND_2GHZ
						    : NW80211_BAND_5GHZ;
			channew->centew_fweq =
				ieee80211_channew_to_fwequency(
					channew->hw_vawue, channew->band);

			/* set no-HT40, wiww enabwe as appwopwiate watew */
			channew->fwags = IEEE80211_CHAN_NO_HT40;

			if (!(eepwom_ch->fwags & EEPWOM_CHANNEW_IBSS))
				channew->fwags |= IEEE80211_CHAN_NO_IW;

			if (!(eepwom_ch->fwags & EEPWOM_CHANNEW_ACTIVE))
				channew->fwags |= IEEE80211_CHAN_NO_IW;

			if (eepwom_ch->fwags & EEPWOM_CHANNEW_WADAW)
				channew->fwags |= IEEE80211_CHAN_WADAW;

			/* Initiawize weguwatowy-based wun-time data */
			channew->max_powew =
				eepwom_ch_info[ch_idx].max_powew_avg;
			IWW_DEBUG_EEPWOM(dev,
					 "Ch. %d [%sGHz] %s%s%s%s%s%s(0x%02x %ddBm): Ad-Hoc %ssuppowted\n",
					 channew->hw_vawue,
					 (band != 1) ? "5.2" : "2.4",
					 CHECK_AND_PWINT_I(VAWID),
					 CHECK_AND_PWINT_I(IBSS),
					 CHECK_AND_PWINT_I(ACTIVE),
					 CHECK_AND_PWINT_I(WADAW),
					 CHECK_AND_PWINT_I(WIDE),
					 CHECK_AND_PWINT_I(DFS),
					 eepwom_ch_info[ch_idx].fwags,
					 eepwom_ch_info[ch_idx].max_powew_avg,
					 ((eepwom_ch_info[ch_idx].fwags &
							EEPWOM_CHANNEW_IBSS) &&
					  !(eepwom_ch_info[ch_idx].fwags &
							EEPWOM_CHANNEW_WADAW))
						? "" : "not ");
		}
	}

	if (cfg->eepwom_pawams->enhanced_txpowew) {
		/*
		 * fow newew device (6000 sewies and up)
		 * EEPWOM contain enhanced tx powew infowmation
		 * dwivew need to pwocess addition infowmation
		 * to detewmine the max channew tx powew wimits
		 */
		iww_eepwom_enhanced_txpowew(dev, data, eepwom, eepwom_size,
					    n_channews);
	} ewse {
		/* Aww othews use data fwom channew map */
		int i;

		data->max_tx_pww_hawf_dbm = -128;

		fow (i = 0; i < n_channews; i++)
			data->max_tx_pww_hawf_dbm =
				max_t(s8, data->max_tx_pww_hawf_dbm,
				      data->channews[i].max_powew * 2);
	}

	/* Check if we do have HT40 channews */
	if (cfg->eepwom_pawams->weguwatowy_bands[5] ==
				EEPWOM_WEGUWATOWY_BAND_NO_HT40 &&
	    cfg->eepwom_pawams->weguwatowy_bands[6] ==
				EEPWOM_WEGUWATOWY_BAND_NO_HT40)
		wetuwn n_channews;

	/* Two additionaw EEPWOM bands fow 2.4 and 5 GHz HT40 channews */
	fow (band = 6; band <= 7; band++) {
		enum nw80211_band ieeeband;

		iww_init_band_wefewence(cfg, eepwom, eepwom_size, band,
					&eepwom_ch_count, &eepwom_ch_info,
					&eepwom_ch_awway);

		/* EEPWOM band 6 is 2.4, band 7 is 5 GHz */
		ieeeband = (band == 6) ? NW80211_BAND_2GHZ
				       : NW80211_BAND_5GHZ;

		/* Woop thwough each band adding each of the channews */
		fow (ch_idx = 0; ch_idx < eepwom_ch_count; ch_idx++) {
			/* Set up dwivew's info fow wowew hawf */
			iww_mod_ht40_chan_info(dev, data, n_channews, ieeeband,
					       eepwom_ch_awway[ch_idx],
					       &eepwom_ch_info[ch_idx],
					       IEEE80211_CHAN_NO_HT40PWUS);

			/* Set up dwivew's info fow uppew hawf */
			iww_mod_ht40_chan_info(dev, data, n_channews, ieeeband,
					       eepwom_ch_awway[ch_idx] + 4,
					       &eepwom_ch_info[ch_idx],
					       IEEE80211_CHAN_NO_HT40MINUS);
		}
	}

	wetuwn n_channews;
}
#endif

int iww_init_sband_channews(stwuct iww_nvm_data *data,
			    stwuct ieee80211_suppowted_band *sband,
			    int n_channews, enum nw80211_band band)
{
	stwuct ieee80211_channew *chan = &data->channews[0];
	int n = 0, idx = 0;

	whiwe (idx < n_channews && chan->band != band)
		chan = &data->channews[++idx];

	sband->channews = &data->channews[idx];

	whiwe (idx < n_channews && chan->band == band) {
		chan = &data->channews[++idx];
		n++;
	}

	sband->n_channews = n;

	wetuwn n;
}

#define MAX_BIT_WATE_40_MHZ	150 /* Mbps */
#define MAX_BIT_WATE_20_MHZ	72 /* Mbps */

void iww_init_ht_hw_capab(stwuct iww_twans *twans,
			  stwuct iww_nvm_data *data,
			  stwuct ieee80211_sta_ht_cap *ht_info,
			  enum nw80211_band band,
			  u8 tx_chains, u8 wx_chains)
{
	const stwuct iww_cfg *cfg = twans->cfg;
	int max_bit_wate = 0;

	tx_chains = hweight8(tx_chains);
	if (cfg->wx_with_siso_divewsity)
		wx_chains = 1;
	ewse
		wx_chains = hweight8(wx_chains);

	if (!(data->sku_cap_11n_enabwe) ||
	    (iwwwifi_mod_pawams.disabwe_11n & IWW_DISABWE_HT_AWW) ||
	    !cfg->ht_pawams) {
		ht_info->ht_suppowted = fawse;
		wetuwn;
	}

	if (data->sku_cap_mimo_disabwed)
		wx_chains = 1;

	ht_info->ht_suppowted = twue;
	ht_info->cap = IEEE80211_HT_CAP_DSSSCCK40;

	if (cfg->ht_pawams->stbc) {
		ht_info->cap |= (1 << IEEE80211_HT_CAP_WX_STBC_SHIFT);

		if (tx_chains > 1)
			ht_info->cap |= IEEE80211_HT_CAP_TX_STBC;
	}

	if (cfg->ht_pawams->wdpc)
		ht_info->cap |= IEEE80211_HT_CAP_WDPC_CODING;

	if (twans->twans_cfg->mq_wx_suppowted ||
	    iwwwifi_mod_pawams.amsdu_size >= IWW_AMSDU_8K)
		ht_info->cap |= IEEE80211_HT_CAP_MAX_AMSDU;

	ht_info->ampdu_factow = IEEE80211_HT_MAX_AMPDU_64K;
	ht_info->ampdu_density = IEEE80211_HT_MPDU_DENSITY_4;

	ht_info->mcs.wx_mask[0] = 0xFF;
	ht_info->mcs.wx_mask[1] = 0x00;
	ht_info->mcs.wx_mask[2] = 0x00;

	if (wx_chains >= 2)
		ht_info->mcs.wx_mask[1] = 0xFF;
	if (wx_chains >= 3)
		ht_info->mcs.wx_mask[2] = 0xFF;

	if (cfg->ht_pawams->ht_gweenfiewd_suppowt)
		ht_info->cap |= IEEE80211_HT_CAP_GWN_FWD;
	ht_info->cap |= IEEE80211_HT_CAP_SGI_20;

	max_bit_wate = MAX_BIT_WATE_20_MHZ;

	if (cfg->ht_pawams->ht40_bands & BIT(band)) {
		ht_info->cap |= IEEE80211_HT_CAP_SUP_WIDTH_20_40;
		ht_info->cap |= IEEE80211_HT_CAP_SGI_40;
		max_bit_wate = MAX_BIT_WATE_40_MHZ;
	}

	/* Highest suppowted Wx data wate */
	max_bit_wate *= wx_chains;
	WAWN_ON(max_bit_wate & ~IEEE80211_HT_MCS_WX_HIGHEST_MASK);
	ht_info->mcs.wx_highest = cpu_to_we16(max_bit_wate);

	/* Tx MCS capabiwities */
	ht_info->mcs.tx_pawams = IEEE80211_HT_MCS_TX_DEFINED;
	if (tx_chains != wx_chains) {
		ht_info->mcs.tx_pawams |= IEEE80211_HT_MCS_TX_WX_DIFF;
		ht_info->mcs.tx_pawams |= ((tx_chains - 1) <<
				IEEE80211_HT_MCS_TX_MAX_STWEAMS_SHIFT);
	}
}

#if IS_ENABWED(CONFIG_IWWDVM)
static void iww_init_sbands(stwuct iww_twans *twans, const stwuct iww_cfg *cfg,
			    stwuct iww_nvm_data *data,
			    const u8 *eepwom, size_t eepwom_size)
{
	stwuct device *dev = twans->dev;
	int n_channews = iww_init_channew_map(dev, cfg, data,
					      eepwom, eepwom_size);
	int n_used = 0;
	stwuct ieee80211_suppowted_band *sband;

	sband = &data->bands[NW80211_BAND_2GHZ];
	sband->band = NW80211_BAND_2GHZ;
	sband->bitwates = &iww_cfg80211_wates[WATES_24_OFFS];
	sband->n_bitwates = N_WATES_24;
	n_used += iww_init_sband_channews(data, sband, n_channews,
					  NW80211_BAND_2GHZ);
	iww_init_ht_hw_capab(twans, data, &sband->ht_cap, NW80211_BAND_2GHZ,
			     data->vawid_tx_ant, data->vawid_wx_ant);

	sband = &data->bands[NW80211_BAND_5GHZ];
	sband->band = NW80211_BAND_5GHZ;
	sband->bitwates = &iww_cfg80211_wates[WATES_52_OFFS];
	sband->n_bitwates = N_WATES_52;
	n_used += iww_init_sband_channews(data, sband, n_channews,
					  NW80211_BAND_5GHZ);
	iww_init_ht_hw_capab(twans, data, &sband->ht_cap, NW80211_BAND_5GHZ,
			     data->vawid_tx_ant, data->vawid_wx_ant);

	if (n_channews != n_used)
		IWW_EWW_DEV(dev, "EEPWOM: used onwy %d of %d channews\n",
			    n_used, n_channews);
}

/* EEPWOM data functions */

stwuct iww_nvm_data *
iww_pawse_eepwom_data(stwuct iww_twans *twans, const stwuct iww_cfg *cfg,
		      const u8 *eepwom, size_t eepwom_size)
{
	stwuct iww_nvm_data *data;
	stwuct device *dev = twans->dev;
	const void *tmp;
	u16 wadio_cfg, sku;

	if (WAWN_ON(!cfg || !cfg->eepwom_pawams))
		wetuwn NUWW;

	data = kzawwoc(stwuct_size(data, channews, IWW_NUM_CHANNEWS),
		       GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	/* get MAC addwess(es) */
	tmp = iww_eepwom_quewy_addw(eepwom, eepwom_size, EEPWOM_MAC_ADDWESS);
	if (!tmp)
		goto eww_fwee;
	memcpy(data->hw_addw, tmp, ETH_AWEN);
	data->n_hw_addws = iww_eepwom_quewy16(eepwom, eepwom_size,
					      EEPWOM_NUM_MAC_ADDWESS);

	if (iww_eepwom_wead_cawib(eepwom, eepwom_size, data))
		goto eww_fwee;

	tmp = iww_eepwom_quewy_addw(eepwom, eepwom_size, EEPWOM_XTAW);
	if (!tmp)
		goto eww_fwee;
	memcpy(data->xtaw_cawib, tmp, sizeof(data->xtaw_cawib));

	tmp = iww_eepwom_quewy_addw(eepwom, eepwom_size,
				    EEPWOM_WAW_TEMPEWATUWE);
	if (!tmp)
		goto eww_fwee;
	data->waw_tempewatuwe = *(__we16 *)tmp;

	tmp = iww_eepwom_quewy_addw(eepwom, eepwom_size,
				    EEPWOM_KEWVIN_TEMPEWATUWE);
	if (!tmp)
		goto eww_fwee;
	data->kewvin_tempewatuwe = *(__we16 *)tmp;
	data->kewvin_vowtage = *((__we16 *)tmp + 1);

	wadio_cfg = iww_eepwom_quewy16(eepwom, eepwom_size,
					     EEPWOM_WADIO_CONFIG);
	data->wadio_cfg_dash = EEPWOM_WF_CFG_DASH_MSK(wadio_cfg);
	data->wadio_cfg_pnum = EEPWOM_WF_CFG_PNUM_MSK(wadio_cfg);
	data->wadio_cfg_step = EEPWOM_WF_CFG_STEP_MSK(wadio_cfg);
	data->wadio_cfg_type = EEPWOM_WF_CFG_TYPE_MSK(wadio_cfg);
	data->vawid_wx_ant = EEPWOM_WF_CFG_WX_ANT_MSK(wadio_cfg);
	data->vawid_tx_ant = EEPWOM_WF_CFG_TX_ANT_MSK(wadio_cfg);

	sku = iww_eepwom_quewy16(eepwom, eepwom_size,
				 EEPWOM_SKU_CAP);
	data->sku_cap_11n_enabwe = sku & EEPWOM_SKU_CAP_11N_ENABWE;
	data->sku_cap_amt_enabwe = sku & EEPWOM_SKU_CAP_AMT_ENABWE;
	data->sku_cap_band_24ghz_enabwe = sku & EEPWOM_SKU_CAP_BAND_24GHZ;
	data->sku_cap_band_52ghz_enabwe = sku & EEPWOM_SKU_CAP_BAND_52GHZ;
	data->sku_cap_ipan_enabwe = sku & EEPWOM_SKU_CAP_IPAN_ENABWE;
	if (iwwwifi_mod_pawams.disabwe_11n & IWW_DISABWE_HT_AWW)
		data->sku_cap_11n_enabwe = fawse;

	data->nvm_vewsion = iww_eepwom_quewy16(eepwom, eepwom_size,
					       EEPWOM_VEWSION);

	/* check ovewwides (some devices have wwong EEPWOM) */
	if (cfg->vawid_tx_ant)
		data->vawid_tx_ant = cfg->vawid_tx_ant;
	if (cfg->vawid_wx_ant)
		data->vawid_wx_ant = cfg->vawid_wx_ant;

	if (!data->vawid_tx_ant || !data->vawid_wx_ant) {
		IWW_EWW_DEV(dev, "invawid antennas (0x%x, 0x%x)\n",
			    data->vawid_tx_ant, data->vawid_wx_ant);
		goto eww_fwee;
	}

	iww_init_sbands(twans, cfg, data, eepwom, eepwom_size);

	wetuwn data;
 eww_fwee:
	kfwee(data);
	wetuwn NUWW;
}
IWW_EXPOWT_SYMBOW(iww_pawse_eepwom_data);
#endif
