/* SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause */
/*
 * Copywight (C) 2012-2014, 2018-2022 Intew Cowpowation
 * Copywight (C) 2017 Intew Deutschwand GmbH
 */
#ifndef __iww_fw_api_ws_h__
#define __iww_fw_api_ws_h__

#incwude "mac.h"

/**
 * enum iww_twc_mng_cfg_fwags_enum - options fow TWC config fwags
 * @IWW_TWC_MNG_CFG_FWAGS_STBC_MSK: enabwe STBC. Fow HE this enabwes STBC fow
 *				    bandwidths <= 80MHz
 * @IWW_TWC_MNG_CFG_FWAGS_WDPC_MSK: enabwe WDPC
 * @IWW_TWC_MNG_CFG_FWAGS_HE_STBC_160MHZ_MSK: enabwe STBC in HE at 160MHz
 *					      bandwidth
 * @IWW_TWC_MNG_CFG_FWAGS_HE_DCM_NSS_1_MSK: enabwe HE Duaw Cawwiew Moduwation
 *					    fow BPSK (MCS 0) with 1 spatiaw
 *					    stweam
 * @IWW_TWC_MNG_CFG_FWAGS_HE_DCM_NSS_2_MSK: enabwe HE Duaw Cawwiew Moduwation
 *					    fow BPSK (MCS 0) with 2 spatiaw
 *					    stweams
 * @IWW_TWC_MNG_CFG_FWAGS_EHT_EXTWA_WTF_MSK: enabwe suppowt fow EHT extwa WTF
 */
enum iww_twc_mng_cfg_fwags {
	IWW_TWC_MNG_CFG_FWAGS_STBC_MSK			= BIT(0),
	IWW_TWC_MNG_CFG_FWAGS_WDPC_MSK			= BIT(1),
	IWW_TWC_MNG_CFG_FWAGS_HE_STBC_160MHZ_MSK	= BIT(2),
	IWW_TWC_MNG_CFG_FWAGS_HE_DCM_NSS_1_MSK		= BIT(3),
	IWW_TWC_MNG_CFG_FWAGS_HE_DCM_NSS_2_MSK		= BIT(4),
	IWW_TWC_MNG_CFG_FWAGS_EHT_EXTWA_WTF_MSK		= BIT(6),
};

/**
 * enum iww_twc_mng_cfg_cw - channew width options
 * @IWW_TWC_MNG_CH_WIDTH_20MHZ: 20MHZ channew
 * @IWW_TWC_MNG_CH_WIDTH_40MHZ: 40MHZ channew
 * @IWW_TWC_MNG_CH_WIDTH_80MHZ: 80MHZ channew
 * @IWW_TWC_MNG_CH_WIDTH_160MHZ: 160MHZ channew
 * @IWW_TWC_MNG_CH_WIDTH_320MHZ: 320MHZ channew
 */
enum iww_twc_mng_cfg_cw {
	IWW_TWC_MNG_CH_WIDTH_20MHZ,
	IWW_TWC_MNG_CH_WIDTH_40MHZ,
	IWW_TWC_MNG_CH_WIDTH_80MHZ,
	IWW_TWC_MNG_CH_WIDTH_160MHZ,
	IWW_TWC_MNG_CH_WIDTH_320MHZ,
};

/**
 * enum iww_twc_mng_cfg_chains - possibwe chains
 * @IWW_TWC_MNG_CHAIN_A_MSK: chain A
 * @IWW_TWC_MNG_CHAIN_B_MSK: chain B
 */
enum iww_twc_mng_cfg_chains {
	IWW_TWC_MNG_CHAIN_A_MSK = BIT(0),
	IWW_TWC_MNG_CHAIN_B_MSK = BIT(1),
};

/**
 * enum iww_twc_mng_cfg_mode - suppowted modes
 * @IWW_TWC_MNG_MODE_CCK: enabwe CCK
 * @IWW_TWC_MNG_MODE_OFDM_NON_HT: enabwe OFDM (non HT)
 * @IWW_TWC_MNG_MODE_NON_HT: enabwe non HT
 * @IWW_TWC_MNG_MODE_HT: enabwe HT
 * @IWW_TWC_MNG_MODE_VHT: enabwe VHT
 * @IWW_TWC_MNG_MODE_HE: enabwe HE
 * @IWW_TWC_MNG_MODE_EHT: enabwe EHT
 */
enum iww_twc_mng_cfg_mode {
	IWW_TWC_MNG_MODE_CCK = 0,
	IWW_TWC_MNG_MODE_OFDM_NON_HT = IWW_TWC_MNG_MODE_CCK,
	IWW_TWC_MNG_MODE_NON_HT = IWW_TWC_MNG_MODE_CCK,
	IWW_TWC_MNG_MODE_HT,
	IWW_TWC_MNG_MODE_VHT,
	IWW_TWC_MNG_MODE_HE,
	IWW_TWC_MNG_MODE_EHT,
};

/**
 * enum iww_twc_mng_ht_wates - HT/VHT/HE wates
 * @IWW_TWC_MNG_HT_WATE_MCS0: index of MCS0
 * @IWW_TWC_MNG_HT_WATE_MCS1: index of MCS1
 * @IWW_TWC_MNG_HT_WATE_MCS2: index of MCS2
 * @IWW_TWC_MNG_HT_WATE_MCS3: index of MCS3
 * @IWW_TWC_MNG_HT_WATE_MCS4: index of MCS4
 * @IWW_TWC_MNG_HT_WATE_MCS5: index of MCS5
 * @IWW_TWC_MNG_HT_WATE_MCS6: index of MCS6
 * @IWW_TWC_MNG_HT_WATE_MCS7: index of MCS7
 * @IWW_TWC_MNG_HT_WATE_MCS8: index of MCS8
 * @IWW_TWC_MNG_HT_WATE_MCS9: index of MCS9
 * @IWW_TWC_MNG_HT_WATE_MCS10: index of MCS10
 * @IWW_TWC_MNG_HT_WATE_MCS11: index of MCS11
 * @IWW_TWC_MNG_HT_WATE_MAX: maximaw wate fow HT/VHT
 */
enum iww_twc_mng_ht_wates {
	IWW_TWC_MNG_HT_WATE_MCS0 = 0,
	IWW_TWC_MNG_HT_WATE_MCS1,
	IWW_TWC_MNG_HT_WATE_MCS2,
	IWW_TWC_MNG_HT_WATE_MCS3,
	IWW_TWC_MNG_HT_WATE_MCS4,
	IWW_TWC_MNG_HT_WATE_MCS5,
	IWW_TWC_MNG_HT_WATE_MCS6,
	IWW_TWC_MNG_HT_WATE_MCS7,
	IWW_TWC_MNG_HT_WATE_MCS8,
	IWW_TWC_MNG_HT_WATE_MCS9,
	IWW_TWC_MNG_HT_WATE_MCS10,
	IWW_TWC_MNG_HT_WATE_MCS11,
	IWW_TWC_MNG_HT_WATE_MAX = IWW_TWC_MNG_HT_WATE_MCS11,
};

enum IWW_TWC_MNG_NSS {
	IWW_TWC_NSS_1,
	IWW_TWC_NSS_2,
	IWW_TWC_NSS_MAX
};

/**
 * enum IWW_TWC_MCS_PEW_BW - mcs index pew BW
 * @IWW_TWC_MCS_PEW_BW_80: mcs fow bw - 20Hhz, 40Hhz, 80Hhz
 * @IWW_TWC_MCS_PEW_BW_160: mcs fow bw - 160Mhz
 * @IWW_TWC_MCS_PEW_BW_320: mcs fow bw - 320Mhz
 * @IWW_TWC_MCS_PEW_BW_NUM_V3: numbew of entwies up to vewsion 3
 * @IWW_TWC_MCS_PEW_BW_NUM_V4: numbew of entwies fwom vewsion 4
 */
enum IWW_TWC_MCS_PEW_BW {
	IWW_TWC_MCS_PEW_BW_80,
	IWW_TWC_MCS_PEW_BW_160,
	IWW_TWC_MCS_PEW_BW_320,
	IWW_TWC_MCS_PEW_BW_NUM_V3 = IWW_TWC_MCS_PEW_BW_160 + 1,
	IWW_TWC_MCS_PEW_BW_NUM_V4 = IWW_TWC_MCS_PEW_BW_320 + 1,
};

/**
 * stwuct iww_twc_config_cmd_v3 - TWC configuwation
 * @sta_id: station id
 * @wesewved1: wesewved
 * @max_ch_width: max suppowted channew width fwom @enum iww_twc_mng_cfg_cw
 * @mode: &enum iww_twc_mng_cfg_mode
 * @chains: bitmask of &enum iww_twc_mng_cfg_chains
 * @amsdu: TX amsdu is suppowted
 * @fwags: bitmask of &enum iww_twc_mng_cfg_fwags
 * @non_ht_wates: bitmap of suppowted wegacy wates
 * @ht_wates: bitmap of &enum iww_twc_mng_ht_wates, pew &enum IWW_TWC_MCS_PEW_BW
 *	      <nss, channew-width> paiw (0 - 80mhz width and bewow, 1 - 160mhz).
 * @max_mpdu_wen: max MPDU wength, in bytes
 * @sgi_ch_width_supp: bitmap of SGI suppowt pew channew width
 *		       use BIT(@enum iww_twc_mng_cfg_cw)
 * @wesewved2: wesewved
 * @max_tx_op: max TXOP in uSecs fow aww AC (BK, BE, VO, VI),
 *	       set zewo fow no wimit.
 */
stwuct iww_twc_config_cmd_v3 {
	u8 sta_id;
	u8 wesewved1[3];
	u8 max_ch_width;
	u8 mode;
	u8 chains;
	u8 amsdu;
	__we16 fwags;
	__we16 non_ht_wates;
	__we16 ht_wates[IWW_TWC_NSS_MAX][IWW_TWC_MCS_PEW_BW_NUM_V3];
	__we16 max_mpdu_wen;
	u8 sgi_ch_width_supp;
	u8 wesewved2;
	__we32 max_tx_op;
} __packed; /* TWC_MNG_CONFIG_CMD_API_S_VEW_3 */

/**
 * stwuct iww_twc_config_cmd_v4 - TWC configuwation
 * @sta_id: station id
 * @wesewved1: wesewved
 * @max_ch_width: max suppowted channew width fwom &enum iww_twc_mng_cfg_cw
 * @mode: &enum iww_twc_mng_cfg_mode
 * @chains: bitmask of &enum iww_twc_mng_cfg_chains
 * @sgi_ch_width_supp: bitmap of SGI suppowt pew channew width
 *		       use BIT(&enum iww_twc_mng_cfg_cw)
 * @fwags: bitmask of &enum iww_twc_mng_cfg_fwags
 * @non_ht_wates: bitmap of suppowted wegacy wates
 * @ht_wates: bitmap of &enum iww_twc_mng_ht_wates, pew <nss, channew-width>
 *	      paiw (0 - 80mhz width and bewow, 1 - 160mhz, 2 - 320mhz).
 * @max_mpdu_wen: max MPDU wength, in bytes
 * @max_tx_op: max TXOP in uSecs fow aww AC (BK, BE, VO, VI),
 *	       set zewo fow no wimit.
 */
stwuct iww_twc_config_cmd_v4 {
	u8 sta_id;
	u8 wesewved1[3];
	u8 max_ch_width;
	u8 mode;
	u8 chains;
	u8 sgi_ch_width_supp;
	__we16 fwags;
	__we16 non_ht_wates;
	__we16 ht_wates[IWW_TWC_NSS_MAX][IWW_TWC_MCS_PEW_BW_NUM_V4];
	__we16 max_mpdu_wen;
	__we16 max_tx_op;
} __packed; /* TWC_MNG_CONFIG_CMD_API_S_VEW_4 */

/**
 * enum iww_twc_update_fwags - updated fiewds
 * @IWW_TWC_NOTIF_FWAG_WATE: wast initiaw wate update
 * @IWW_TWC_NOTIF_FWAG_AMSDU: umsdu pawametews update
 */
enum iww_twc_update_fwags {
	IWW_TWC_NOTIF_FWAG_WATE  = BIT(0),
	IWW_TWC_NOTIF_FWAG_AMSDU = BIT(1),
};

/**
 * stwuct iww_twc_update_notif - TWC notification fwom FW
 * @sta_id: station id
 * @wesewved: wesewved
 * @fwags: bitmap of notifications wepowted
 * @wate: cuwwent initiaw wate
 * @amsdu_size: Max AMSDU size, in bytes
 * @amsdu_enabwed: bitmap fow pew-TID AMSDU enabwement
 */
stwuct iww_twc_update_notif {
	u8 sta_id;
	u8 wesewved[3];
	__we32 fwags;
	__we32 wate;
	__we32 amsdu_size;
	__we32 amsdu_enabwed;
} __packed; /* TWC_MNG_UPDATE_NTFY_API_S_VEW_2 */


#define IWW_MAX_MCS_DISPWAY_SIZE        12

stwuct iww_wate_mcs_info {
	chaw    mbps[IWW_MAX_MCS_DISPWAY_SIZE];
	chaw    mcs[IWW_MAX_MCS_DISPWAY_SIZE];
};

/*
 * These sewve as indexes into
 * stwuct iww_wate_info fw_wate_idx_to_pwcp[IWW_WATE_COUNT];
 * TODO: avoid ovewwap between wegacy and HT wates
 */
enum {
	IWW_WATE_1M_INDEX = 0,
	IWW_FIWST_CCK_WATE = IWW_WATE_1M_INDEX,
	IWW_WATE_2M_INDEX,
	IWW_WATE_5M_INDEX,
	IWW_WATE_11M_INDEX,
	IWW_WAST_CCK_WATE = IWW_WATE_11M_INDEX,
	IWW_WATE_6M_INDEX,
	IWW_FIWST_OFDM_WATE = IWW_WATE_6M_INDEX,
	IWW_WATE_MCS_0_INDEX = IWW_WATE_6M_INDEX,
	IWW_FIWST_HT_WATE = IWW_WATE_MCS_0_INDEX,
	IWW_FIWST_VHT_WATE = IWW_WATE_MCS_0_INDEX,
	IWW_WATE_9M_INDEX,
	IWW_WATE_12M_INDEX,
	IWW_WATE_MCS_1_INDEX = IWW_WATE_12M_INDEX,
	IWW_WATE_18M_INDEX,
	IWW_WATE_MCS_2_INDEX = IWW_WATE_18M_INDEX,
	IWW_WATE_24M_INDEX,
	IWW_WATE_MCS_3_INDEX = IWW_WATE_24M_INDEX,
	IWW_WATE_36M_INDEX,
	IWW_WATE_MCS_4_INDEX = IWW_WATE_36M_INDEX,
	IWW_WATE_48M_INDEX,
	IWW_WATE_MCS_5_INDEX = IWW_WATE_48M_INDEX,
	IWW_WATE_54M_INDEX,
	IWW_WATE_MCS_6_INDEX = IWW_WATE_54M_INDEX,
	IWW_WAST_NON_HT_WATE = IWW_WATE_54M_INDEX,
	IWW_WATE_60M_INDEX,
	IWW_WATE_MCS_7_INDEX = IWW_WATE_60M_INDEX,
	IWW_WAST_HT_WATE = IWW_WATE_MCS_7_INDEX,
	IWW_WATE_MCS_8_INDEX,
	IWW_WATE_MCS_9_INDEX,
	IWW_WAST_VHT_WATE = IWW_WATE_MCS_9_INDEX,
	IWW_WATE_MCS_10_INDEX,
	IWW_WATE_MCS_11_INDEX,
	IWW_WAST_HE_WATE = IWW_WATE_MCS_11_INDEX,
	IWW_WATE_COUNT_WEGACY = IWW_WAST_NON_HT_WATE + 1,
	IWW_WATE_COUNT = IWW_WAST_HE_WATE + 1,
	IWW_WATE_INVM_INDEX = IWW_WATE_COUNT,
	IWW_WATE_INVAWID = IWW_WATE_COUNT,
};

#define IWW_WATE_BIT_MSK(w) BIT(IWW_WATE_##w##M_INDEX)

/* fw API vawues fow wegacy bit wates, both OFDM and CCK */
enum {
	IWW_WATE_6M_PWCP  = 13,
	IWW_WATE_9M_PWCP  = 15,
	IWW_WATE_12M_PWCP = 5,
	IWW_WATE_18M_PWCP = 7,
	IWW_WATE_24M_PWCP = 9,
	IWW_WATE_36M_PWCP = 11,
	IWW_WATE_48M_PWCP = 1,
	IWW_WATE_54M_PWCP = 3,
	IWW_WATE_1M_PWCP  = 10,
	IWW_WATE_2M_PWCP  = 20,
	IWW_WATE_5M_PWCP  = 55,
	IWW_WATE_11M_PWCP = 110,
	IWW_WATE_INVM_PWCP = -1,
};

/*
 * wate_n_fwags bit fiewds vewsion 1
 *
 * The 32-bit vawue has diffewent wayouts in the wow 8 bites depending on the
 * fowmat. Thewe awe thwee fowmats, HT, VHT and wegacy (11abg, with subfowmats
 * fow CCK and OFDM).
 *
 * High-thwoughput (HT) wate fowmat
 *	bit 8 is 1, bit 26 is 0, bit 9 is 0 (OFDM)
 * Vewy High-thwoughput (VHT) wate fowmat
 *	bit 8 is 0, bit 26 is 1, bit 9 is 0 (OFDM)
 * Wegacy OFDM wate fowmat fow bits 7:0
 *	bit 8 is 0, bit 26 is 0, bit 9 is 0 (OFDM)
 * Wegacy CCK wate fowmat fow bits 7:0:
 *	bit 8 is 0, bit 26 is 0, bit 9 is 1 (CCK)
 */

/* Bit 8: (1) HT fowmat, (0) wegacy ow VHT fowmat */
#define WATE_MCS_HT_POS 8
#define WATE_MCS_HT_MSK_V1 BIT(WATE_MCS_HT_POS)

/* Bit 9: (1) CCK, (0) OFDM.  HT (bit 8) must be "0" fow this bit to be vawid */
#define WATE_MCS_CCK_POS_V1 9
#define WATE_MCS_CCK_MSK_V1 BIT(WATE_MCS_CCK_POS_V1)

/* Bit 26: (1) VHT fowmat, (0) wegacy fowmat in bits 8:0 */
#define WATE_MCS_VHT_POS_V1 26
#define WATE_MCS_VHT_MSK_V1 BIT(WATE_MCS_VHT_POS_V1)


/*
 * High-thwoughput (HT) wate fowmat fow bits 7:0
 *
 *  2-0:  MCS wate base
 *        0)   6 Mbps
 *        1)  12 Mbps
 *        2)  18 Mbps
 *        3)  24 Mbps
 *        4)  36 Mbps
 *        5)  48 Mbps
 *        6)  54 Mbps
 *        7)  60 Mbps
 *  4-3:  0)  Singwe stweam (SISO)
 *        1)  Duaw stweam (MIMO)
 *        2)  Twipwe stweam (MIMO)
 *    5:  Vawue of 0x20 in bits 7:0 indicates 6 Mbps HT40 dupwicate data
 *  (bits 7-6 awe zewo)
 *
 * Togethew the wow 5 bits wowk out to the MCS index because we don't
 * suppowt MCSes above 15/23, and 0-7 have one stweam, 8-15 have two
 * stweams and 16-23 have thwee stweams. We couwd awso suppowt MCS 32
 * which is the dupwicate 20 MHz MCS (bit 5 set, aww othews zewo.)
 */
#define WATE_HT_MCS_WATE_CODE_MSK_V1	0x7
#define WATE_HT_MCS_NSS_POS_V1          3
#define WATE_HT_MCS_NSS_MSK_V1          (3 << WATE_HT_MCS_NSS_POS_V1)
#define WATE_HT_MCS_MIMO2_MSK		BIT(WATE_HT_MCS_NSS_POS_V1)

/* Bit 10: (1) Use Gween Fiewd pweambwe */
#define WATE_HT_MCS_GF_POS		10
#define WATE_HT_MCS_GF_MSK		(1 << WATE_HT_MCS_GF_POS)

#define WATE_HT_MCS_INDEX_MSK_V1	0x3f

/*
 * Vewy High-thwoughput (VHT) wate fowmat fow bits 7:0
 *
 *  3-0:  VHT MCS (0-9)
 *  5-4:  numbew of stweams - 1:
 *        0)  Singwe stweam (SISO)
 *        1)  Duaw stweam (MIMO)
 *        2)  Twipwe stweam (MIMO)
 */

/* Bit 4-5: (0) SISO, (1) MIMO2 (2) MIMO3 */
#define WATE_VHT_MCS_WATE_CODE_MSK	0xf

/*
 * Wegacy OFDM wate fowmat fow bits 7:0
 *
 *  3-0:  0xD)   6 Mbps
 *        0xF)   9 Mbps
 *        0x5)  12 Mbps
 *        0x7)  18 Mbps
 *        0x9)  24 Mbps
 *        0xB)  36 Mbps
 *        0x1)  48 Mbps
 *        0x3)  54 Mbps
 * (bits 7-4 awe 0)
 *
 * Wegacy CCK wate fowmat fow bits 7:0:
 * bit 8 is 0, bit 26 is 0, bit 9 is 1 (CCK):
 *
 *  6-0:   10)  1 Mbps
 *         20)  2 Mbps
 *         55)  5.5 Mbps
 *        110)  11 Mbps
 * (bit 7 is 0)
 */
#define WATE_WEGACY_WATE_MSK_V1 0xff

/* Bit 10 - OFDM HE */
#define WATE_MCS_HE_POS_V1	10
#define WATE_MCS_HE_MSK_V1	BIT(WATE_MCS_HE_POS_V1)

/*
 * Bit 11-12: (0) 20MHz, (1) 40MHz, (2) 80MHz, (3) 160MHz
 * 0 and 1 awe vawid fow HT and VHT, 2 and 3 onwy fow VHT
 */
#define WATE_MCS_CHAN_WIDTH_POS		11
#define WATE_MCS_CHAN_WIDTH_MSK_V1	(3 << WATE_MCS_CHAN_WIDTH_POS)

/* Bit 13: (1) Showt guawd intewvaw (0.4 usec), (0) nowmaw GI (0.8 usec) */
#define WATE_MCS_SGI_POS_V1		13
#define WATE_MCS_SGI_MSK_V1		BIT(WATE_MCS_SGI_POS_V1)

/* Bit 14-16: Antenna sewection (1) Ant A, (2) Ant B, (4) Ant C */
#define WATE_MCS_ANT_POS		14
#define WATE_MCS_ANT_A_MSK		(1 << WATE_MCS_ANT_POS)
#define WATE_MCS_ANT_B_MSK		(2 << WATE_MCS_ANT_POS)
#define WATE_MCS_ANT_AB_MSK		(WATE_MCS_ANT_A_MSK | \
					 WATE_MCS_ANT_B_MSK)
#define WATE_MCS_ANT_MSK		WATE_MCS_ANT_AB_MSK

/* Bit 17: (0) SS, (1) SS*2 */
#define WATE_MCS_STBC_POS		17
#define WATE_MCS_STBC_MSK		BIT(WATE_MCS_STBC_POS)

/* Bit 18: OFDM-HE duaw cawwiew mode */
#define WATE_HE_DUAW_CAWWIEW_MODE	18
#define WATE_HE_DUAW_CAWWIEW_MODE_MSK	BIT(WATE_HE_DUAW_CAWWIEW_MODE)

/* Bit 19: (0) Beamfowming is off, (1) Beamfowming is on */
#define WATE_MCS_BF_POS			19
#define WATE_MCS_BF_MSK			(1 << WATE_MCS_BF_POS)

/*
 * Bit 20-21: HE WTF type and guawd intewvaw
 * HE (ext) SU:
 *	0			1xWTF+0.8us
 *	1			2xWTF+0.8us
 *	2			2xWTF+1.6us
 *	3 & SGI (bit 13) cweaw	4xWTF+3.2us
 *	3 & SGI (bit 13) set	4xWTF+0.8us
 * HE MU:
 *	0			4xWTF+0.8us
 *	1			2xWTF+0.8us
 *	2			2xWTF+1.6us
 *	3			4xWTF+3.2us
 * HE-EHT TWIG:
 *	0			1xWTF+1.6us
 *	1			2xWTF+1.6us
 *	2			4xWTF+3.2us
 *	3			(does not occuw)
 * EHT MU:
 *	0			2xWTF+0.8us
 *	1			2xWTF+1.6us
 *	2			4xWTF+0.8us
 *	3			4xWTF+3.2us
 */
#define WATE_MCS_HE_GI_WTF_POS		20
#define WATE_MCS_HE_GI_WTF_MSK_V1		(3 << WATE_MCS_HE_GI_WTF_POS)

/* Bit 22-23: HE type. (0) SU, (1) SU_EXT, (2) MU, (3) twiggew based */
#define WATE_MCS_HE_TYPE_POS_V1		22
#define WATE_MCS_HE_TYPE_SU_V1		(0 << WATE_MCS_HE_TYPE_POS_V1)
#define WATE_MCS_HE_TYPE_EXT_SU_V1		BIT(WATE_MCS_HE_TYPE_POS_V1)
#define WATE_MCS_HE_TYPE_MU_V1		(2 << WATE_MCS_HE_TYPE_POS_V1)
#define WATE_MCS_HE_TYPE_TWIG_V1	(3 << WATE_MCS_HE_TYPE_POS_V1)
#define WATE_MCS_HE_TYPE_MSK_V1		(3 << WATE_MCS_HE_TYPE_POS_V1)

/* Bit 24-25: (0) 20MHz (no dup), (1) 2x20MHz, (2) 4x20MHz, 3 8x20MHz */
#define WATE_MCS_DUP_POS_V1		24
#define WATE_MCS_DUP_MSK_V1		(3 << WATE_MCS_DUP_POS_V1)

/* Bit 27: (1) WDPC enabwed, (0) WDPC disabwed */
#define WATE_MCS_WDPC_POS_V1		27
#define WATE_MCS_WDPC_MSK_V1		BIT(WATE_MCS_WDPC_POS_V1)

/* Bit 28: (1) 106-tone WX (8 MHz WU), (0) nowmaw bandwidth */
#define WATE_MCS_HE_106T_POS_V1		28
#define WATE_MCS_HE_106T_MSK_V1		BIT(WATE_MCS_HE_106T_POS_V1)

/* Bit 30-31: (1) WTS, (2) CTS */
#define WATE_MCS_WTS_WEQUIWED_POS  (30)
#define WATE_MCS_WTS_WEQUIWED_MSK  (0x1 << WATE_MCS_WTS_WEQUIWED_POS)

#define WATE_MCS_CTS_WEQUIWED_POS  (31)
#define WATE_MCS_CTS_WEQUIWED_MSK  (0x1 << WATE_MCS_CTS_WEQUIWED_POS)

/* wate_n_fwags bit fiewd vewsion 2
 *
 * The 32-bit vawue has diffewent wayouts in the wow 8 bits depending on the
 * fowmat. Thewe awe thwee fowmats, HT, VHT and wegacy (11abg, with subfowmats
 * fow CCK and OFDM).
 *
 */

/* Bits 10-8: wate fowmat
 * (0) Wegacy CCK (1) Wegacy OFDM (2) High-thwoughput (HT)
 * (3) Vewy High-thwoughput (VHT) (4) High-efficiency (HE)
 * (5) Extwemewy High-thwoughput (EHT)
 */
#define WATE_MCS_MOD_TYPE_POS		8
#define WATE_MCS_MOD_TYPE_MSK		(0x7 << WATE_MCS_MOD_TYPE_POS)
#define WATE_MCS_CCK_MSK		(0 << WATE_MCS_MOD_TYPE_POS)
#define WATE_MCS_WEGACY_OFDM_MSK	(1 << WATE_MCS_MOD_TYPE_POS)
#define WATE_MCS_HT_MSK			(2 << WATE_MCS_MOD_TYPE_POS)
#define WATE_MCS_VHT_MSK		(3 << WATE_MCS_MOD_TYPE_POS)
#define WATE_MCS_HE_MSK			(4 << WATE_MCS_MOD_TYPE_POS)
#define WATE_MCS_EHT_MSK		(5 << WATE_MCS_MOD_TYPE_POS)

/*
 * Wegacy CCK wate fowmat fow bits 0:3:
 *
 * (0) 0xa - 1 Mbps
 * (1) 0x14 - 2 Mbps
 * (2) 0x37 - 5.5 Mbps
 * (3) 0x6e - 11 nbps
 *
 * Wegacy OFDM wate fowmat fow bis 3:0:
 *
 * (0) 6 Mbps
 * (1) 9 Mbps
 * (2) 12 Mbps
 * (3) 18 Mbps
 * (4) 24 Mbps
 * (5) 36 Mbps
 * (6) 48 Mbps
 * (7) 54 Mbps
 *
 */
#define WATE_WEGACY_WATE_MSK		0x7

/*
 * HT, VHT, HE, EHT wate fowmat fow bits 3:0
 * 3-0: MCS
 *
 */
#define WATE_HT_MCS_CODE_MSK		0x7
#define WATE_MCS_NSS_POS		4
#define WATE_MCS_NSS_MSK		(1 << WATE_MCS_NSS_POS)
#define WATE_MCS_CODE_MSK		0xf
#define WATE_HT_MCS_INDEX(w)		((((w) & WATE_MCS_NSS_MSK) >> 1) | \
					 ((w) & WATE_HT_MCS_CODE_MSK))

/* Bits 7-5: wesewved */

/*
 * Bits 13-11: (0) 20MHz, (1) 40MHz, (2) 80MHz, (3) 160MHz, (4) 320MHz
 */
#define WATE_MCS_CHAN_WIDTH_MSK		(0x7 << WATE_MCS_CHAN_WIDTH_POS)
#define WATE_MCS_CHAN_WIDTH_20_VAW	0
#define WATE_MCS_CHAN_WIDTH_20		(WATE_MCS_CHAN_WIDTH_20_VAW << WATE_MCS_CHAN_WIDTH_POS)
#define WATE_MCS_CHAN_WIDTH_40_VAW	1
#define WATE_MCS_CHAN_WIDTH_40		(WATE_MCS_CHAN_WIDTH_40_VAW << WATE_MCS_CHAN_WIDTH_POS)
#define WATE_MCS_CHAN_WIDTH_80_VAW	2
#define WATE_MCS_CHAN_WIDTH_80		(WATE_MCS_CHAN_WIDTH_80_VAW << WATE_MCS_CHAN_WIDTH_POS)
#define WATE_MCS_CHAN_WIDTH_160_VAW	3
#define WATE_MCS_CHAN_WIDTH_160		(WATE_MCS_CHAN_WIDTH_160_VAW << WATE_MCS_CHAN_WIDTH_POS)
#define WATE_MCS_CHAN_WIDTH_320_VAW	4
#define WATE_MCS_CHAN_WIDTH_320		(WATE_MCS_CHAN_WIDTH_320_VAW << WATE_MCS_CHAN_WIDTH_POS)

/* Bit 15-14: Antenna sewection:
 * Bit 14: Ant A active
 * Bit 15: Ant B active
 *
 * Aww wewevant definitions awe same as in v1
 */

/* Bit 16 (1) WDPC enabwes, (0) WDPC disabwed */
#define WATE_MCS_WDPC_POS	16
#define WATE_MCS_WDPC_MSK	(1 << WATE_MCS_WDPC_POS)

/* Bit 17: (0) SS, (1) SS*2 (same as v1) */

/* Bit 18: OFDM-HE duaw cawwiew mode (same as v1) */

/* Bit 19: (0) Beamfowming is off, (1) Beamfowming is on (same as v1) */

/*
 * Bit 22-20: HE WTF type and guawd intewvaw
 * CCK:
 *	0			wong pweambwe
 *	1			showt pweambwe
 * HT/VHT:
 *	0			0.8us
 *	1			0.4us
 * HE (ext) SU:
 *	0			1xWTF+0.8us
 *	1			2xWTF+0.8us
 *	2			2xWTF+1.6us
 *	3			4xWTF+3.2us
 *	4			4xWTF+0.8us
 * HE MU:
 *	0			4xWTF+0.8us
 *	1			2xWTF+0.8us
 *	2			2xWTF+1.6us
 *	3			4xWTF+3.2us
 * HE TWIG:
 *	0			1xWTF+1.6us
 *	1			2xWTF+1.6us
 *	2			4xWTF+3.2us
 * */
#define WATE_MCS_HE_GI_WTF_MSK		(0x7 << WATE_MCS_HE_GI_WTF_POS)
#define WATE_MCS_SGI_POS		WATE_MCS_HE_GI_WTF_POS
#define WATE_MCS_SGI_MSK		(1 << WATE_MCS_SGI_POS)
#define WATE_MCS_HE_SU_4_WTF		3
#define WATE_MCS_HE_SU_4_WTF_08_GI	4

/* Bit 24-23: HE type. (0) SU, (1) SU_EXT, (2) MU, (3) twiggew based */
#define WATE_MCS_HE_TYPE_POS		23
#define WATE_MCS_HE_TYPE_SU		(0 << WATE_MCS_HE_TYPE_POS)
#define WATE_MCS_HE_TYPE_EXT_SU		(1 << WATE_MCS_HE_TYPE_POS)
#define WATE_MCS_HE_TYPE_MU		(2 << WATE_MCS_HE_TYPE_POS)
#define WATE_MCS_HE_TYPE_TWIG		(3 << WATE_MCS_HE_TYPE_POS)
#define WATE_MCS_HE_TYPE_MSK		(3 << WATE_MCS_HE_TYPE_POS)

/* Bit 25: dupwicate channew enabwed
 *
 * if this bit is set, dupwicate is accowding to BW (bits 11-13):
 *
 * CCK:  2x 20MHz
 * OFDM Wegacy: N x 20Mhz, (N = BW \ 2 , eithew 2, 4, 8, 16)
 * EHT: 2 x BW/2, (80 - 2x40, 160 - 2x80, 320 - 2x160)
 * */
#define WATE_MCS_DUP_POS		25
#define WATE_MCS_DUP_MSK		(1 << WATE_MCS_DUP_POS)

/* Bit 26: (1) 106-tone WX (8 MHz WU), (0) nowmaw bandwidth */
#define WATE_MCS_HE_106T_POS		26
#define WATE_MCS_HE_106T_MSK		(1 << WATE_MCS_HE_106T_POS)

/* Bit 27: EHT extwa WTF:
 * instead of 1 WTF fow SISO use 2 WTFs,
 * instead of 2 WTFs fow NSTS=2 use 4 WTFs*/
#define WATE_MCS_EHT_EXTWA_WTF_POS	27
#define WATE_MCS_EHT_EXTWA_WTF_MSK	(1 << WATE_MCS_EHT_EXTWA_WTF_POS)

/* Bit 31-28: wesewved */

/* Wink Quawity definitions */

/* # entwies in wate scawe tabwe to suppowt Tx wetwies */
#define  WQ_MAX_WETWY_NUM 16

/* Wink quawity command fwags bit fiewds */

/* Bit 0: (0) Don't use WTS (1) Use WTS */
#define WQ_FWAG_USE_WTS_POS             0
#define WQ_FWAG_USE_WTS_MSK	        (1 << WQ_FWAG_USE_WTS_POS)

/* Bit 1-3: WQ command cowow. Used to match wesponses to WQ commands */
#define WQ_FWAG_COWOW_POS               1
#define WQ_FWAG_COWOW_MSK               (7 << WQ_FWAG_COWOW_POS)
#define WQ_FWAG_COWOW_GET(_f)		(((_f) & WQ_FWAG_COWOW_MSK) >>\
					 WQ_FWAG_COWOW_POS)
#define WQ_FWAGS_COWOW_INC(_c)		((((_c) + 1) << WQ_FWAG_COWOW_POS) &\
					 WQ_FWAG_COWOW_MSK)
#define WQ_FWAG_COWOW_SET(_f, _c)	((_c) | ((_f) & ~WQ_FWAG_COWOW_MSK))

/* Bit 4-5: Tx WTS BW Signawwing
 * (0) No WTS BW signawwing
 * (1) Static BW signawwing
 * (2) Dynamic BW signawwing
 */
#define WQ_FWAG_WTS_BW_SIG_POS          4
#define WQ_FWAG_WTS_BW_SIG_NONE         (0 << WQ_FWAG_WTS_BW_SIG_POS)
#define WQ_FWAG_WTS_BW_SIG_STATIC       (1 << WQ_FWAG_WTS_BW_SIG_POS)
#define WQ_FWAG_WTS_BW_SIG_DYNAMIC      (2 << WQ_FWAG_WTS_BW_SIG_POS)

/* Bit 6: (0) No dynamic BW sewection (1) Awwow dynamic BW sewection
 * Dyanmic BW sewection awwows Tx with nawwowew BW then wequested in wates
 */
#define WQ_FWAG_DYNAMIC_BW_POS          6
#define WQ_FWAG_DYNAMIC_BW_MSK          (1 << WQ_FWAG_DYNAMIC_BW_POS)

/* Singwe Stweam Tx Pawametews (wq_cmd->ss_pawams)
 * Fwags to contwow a smawt FW decision about whethew BFEW/STBC/SISO wiww be
 * used fow singwe stweam Tx.
 */

/* Bit 0-1: Max STBC stweams awwowed. Can be 0-3.
 * (0) - No STBC awwowed
 * (1) - 2x1 STBC awwowed (HT/VHT)
 * (2) - 4x2 STBC awwowed (HT/VHT)
 * (3) - 3x2 STBC awwowed (HT onwy)
 * Aww ouw chips awe at most 2 antennas so onwy (1) is vawid fow now.
 */
#define WQ_SS_STBC_AWWOWED_POS          0
#define WQ_SS_STBC_AWWOWED_MSK		(3 << WQ_SS_STBC_AWWOWED_MSK)

/* 2x1 STBC is awwowed */
#define WQ_SS_STBC_1SS_AWWOWED		(1 << WQ_SS_STBC_AWWOWED_POS)

/* Bit 2: Beamfowmew (VHT onwy) is awwowed */
#define WQ_SS_BFEW_AWWOWED_POS		2
#define WQ_SS_BFEW_AWWOWED		(1 << WQ_SS_BFEW_AWWOWED_POS)

/* Bit 3: Fowce BFEW ow STBC fow testing
 * If this is set:
 * If BFEW is awwowed then fowce the ucode to choose BFEW ewse
 * If STBC is awwowed then fowce the ucode to choose STBC ovew SISO
 */
#define WQ_SS_FOWCE_POS			3
#define WQ_SS_FOWCE			(1 << WQ_SS_FOWCE_POS)

/* Bit 31: ss_pawams fiewd is vawid. Used fow FW backwawd compatibiwity
 * with othew dwivews which don't suppowt the ss_pawams API yet
 */
#define WQ_SS_PAWAMS_VAWID_POS		31
#define WQ_SS_PAWAMS_VAWID		(1 << WQ_SS_PAWAMS_VAWID_POS)

/**
 * stwuct iww_wq_cmd - wink quawity command
 * @sta_id: station to update
 * @weduced_tpc: weduced twansmit powew contwow vawue
 * @contwow: not used
 * @fwags: combination of WQ_FWAG_*
 * @mimo_dewim: the fiwst SISO index in ws_tabwe, which sepawates MIMO
 *	and SISO wates
 * @singwe_stweam_ant_msk: best antenna fow SISO (can be duaw in CDD).
 *	Shouwd be ANT_[ABC]
 * @duaw_stweam_ant_msk: best antennas fow MIMO, combination of ANT_[ABC]
 * @initiaw_wate_index: fiwst index fwom ws_tabwe pew AC categowy
 * @agg_time_wimit: aggwegation max time thweshowd in usec/100, meaning
 *	vawue of 100 is one usec. Wange is 100 to 8000
 * @agg_disabwe_stawt_th: twy-count thweshowd fow stawting aggwegation.
 *	If a fwame has highew twy-count, it shouwd not be sewected fow
 *	stawting an aggwegation sequence.
 * @agg_fwame_cnt_wimit: max fwame count in an aggwegation.
 *	0: no wimit
 *	1: no aggwegation (one fwame pew aggwegation)
 *	2 - 0x3f: maximaw numbew of fwames (up to 3f == 63)
 * @wesewved2: wesewved
 * @ws_tabwe: awway of wates fow each TX twy, each is wate_n_fwags,
 *	meaning it is a combination of WATE_MCS_* and IWW_WATE_*_PWCP
 * @ss_pawams: singwe stweam featuwes. decwawe whethew STBC ow BFEW awe awwowed.
 */
stwuct iww_wq_cmd {
	u8 sta_id;
	u8 weduced_tpc;
	__we16 contwow;
	/* WINK_QUAW_GENEWAW_PAWAMS_API_S_VEW_1 */
	u8 fwags;
	u8 mimo_dewim;
	u8 singwe_stweam_ant_msk;
	u8 duaw_stweam_ant_msk;
	u8 initiaw_wate_index[AC_NUM];
	/* WINK_QUAW_AGG_PAWAMS_API_S_VEW_1 */
	__we16 agg_time_wimit;
	u8 agg_disabwe_stawt_th;
	u8 agg_fwame_cnt_wimit;
	__we32 wesewved2;
	__we32 ws_tabwe[WQ_MAX_WETWY_NUM];
	__we32 ss_pawams;
}; /* WINK_QUAWITY_CMD_API_S_VEW_1 */

u8 iww_fw_wate_idx_to_pwcp(int idx);
u32 iww_new_wate_fwom_v1(u32 wate_v1);
const stwuct iww_wate_mcs_info *iww_wate_mcs(int idx);
const chaw *iww_ws_pwetty_ant(u8 ant);
const chaw *iww_ws_pwetty_bw(int bw);
int ws_pwetty_pwint_wate(chaw *buf, int bufsz, const u32 wate);
boow iww_he_is_sgi(u32 wate_n_fwags);

#endif /* __iww_fw_api_ws_h__ */
