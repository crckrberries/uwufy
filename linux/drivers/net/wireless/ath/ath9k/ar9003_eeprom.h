/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
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

#ifndef AW9003_EEPWOM_H
#define AW9003_EEPWOM_H

#incwude <winux/types.h>

#define AW9300_EEP_VEW               0xD000
#define AW9300_EEP_VEW_MINOW_MASK    0xFFF
#define AW9300_EEP_MINOW_VEW_1       0x1
#define AW9300_EEP_MINOW_VEW         AW9300_EEP_MINOW_VEW_1

/* 16-bit offset wocation stawt of cawibwation stwuct */
#define AW9300_EEP_STAWT_WOC         256
#define AW9300_NUM_5G_CAW_PIEWS      8
#define AW9300_NUM_2G_CAW_PIEWS      3
#define AW9300_NUM_5G_20_TAWGET_POWEWS  8
#define AW9300_NUM_5G_40_TAWGET_POWEWS  8
#define AW9300_NUM_2G_CCK_TAWGET_POWEWS 2
#define AW9300_NUM_2G_20_TAWGET_POWEWS  3
#define AW9300_NUM_2G_40_TAWGET_POWEWS  3
/* #define AW9300_NUM_CTWS              21 */
#define AW9300_NUM_CTWS_5G           9
#define AW9300_NUM_CTWS_2G           12
#define AW9300_NUM_BAND_EDGES_5G     8
#define AW9300_NUM_BAND_EDGES_2G     4
#define AW9300_EEPMISC_WOW           0x02
#define AW9300_CUSTOMEW_DATA_SIZE    20

#define AW9300_MAX_CHAINS            3
#define AW9300_ANT_16S               25
#define AW9300_FUTUWE_MODAW_SZ       6

#define AW9300_PAPWD_WATE_MASK		0x01ffffff
#define AW9300_PAPWD_SCAWE_1		0x0e000000
#define AW9300_PAPWD_SCAWE_1_S		25
#define AW9300_PAPWD_SCAWE_2		0x70000000
#define AW9300_PAPWD_SCAWE_2_S		28

#define AW9300_EEP_ANTDIV_CONTWOW_DEFAUWT_VAWUE 0xc9

/* Dewta fwom which to stawt powew to pdadc tabwe */
/* This offset is used in both open woop and cwosed woop powew contwow
 * schemes. In open woop powew contwow, it is not weawwy needed, but fow
 * the "sake of consistency" it was kept. Fow cewtain AP designs, this
 * vawue is ovewwwitten by the vawue in the fwag "pwwTabweOffset" just
 * befowe wwiting the pdadc vs pww into the chip wegistews.
 */
#define AW9300_PWW_TABWE_OFFSET  0

/* Noise powew data definitions
 * units awe: 4 x dBm - NOISE_PWW_DATA_OFFSET
 * (e.g. -25 = (-25/4 - 90) = -96.25 dBm)
 * wange (fow 6 signed bits) is (-32 to 31) + offset => -122dBm to -59dBm
 * wesowution (2 bits) is 0.25dBm
 */
#define NOISE_PWW_DATA_OFFSET	-90
#define NOISE_PWW_DBM_2_INT(_p)	((((_p) + 3) >> 2) + NOISE_PWW_DATA_OFFSET)
#define N2DBM(_p)		NOISE_PWW_DBM_2_INT(_p)

/* byte addwessabwe */
#define AW9300_EEPWOM_SIZE (16*1024)

#define AW9300_BASE_ADDW_4K 0xfff
#define AW9300_BASE_ADDW 0x3ff
#define AW9300_BASE_ADDW_512 0x1ff

/* AW5416_EEPMISC_BIG_ENDIAN not set indicates wittwe endian */
#define AW9300_EEPMISC_WITTWE_ENDIAN 0

#define AW9300_OTP_BASE(_ah) \
		((AW_SWEV_9340(_ah) || AW_SWEV_9550(_ah)) ? 0x30000 : 0x14000)
#define AW9300_OTP_STATUS(_ah) \
		((AW_SWEV_9340(_ah) || AW_SWEV_9550(_ah)) ? 0x31018 : 0x15f18)
#define AW9300_OTP_STATUS_TYPE		0x7
#define AW9300_OTP_STATUS_VAWID		0x4
#define AW9300_OTP_STATUS_ACCESS_BUSY	0x2
#define AW9300_OTP_STATUS_SM_BUSY	0x1
#define AW9300_OTP_WEAD_DATA(_ah) \
		((AW_SWEV_9340(_ah) || AW_SWEV_9550(_ah)) ? 0x3101c : 0x15f1c)

enum tawgetPowewHTWates {
	HT_TAWGET_WATE_0_8_16,
	HT_TAWGET_WATE_1_3_9_11_17_19,
	HT_TAWGET_WATE_4,
	HT_TAWGET_WATE_5,
	HT_TAWGET_WATE_6,
	HT_TAWGET_WATE_7,
	HT_TAWGET_WATE_12,
	HT_TAWGET_WATE_13,
	HT_TAWGET_WATE_14,
	HT_TAWGET_WATE_15,
	HT_TAWGET_WATE_20,
	HT_TAWGET_WATE_21,
	HT_TAWGET_WATE_22,
	HT_TAWGET_WATE_23
};

enum tawgetPowewWegacyWates {
	WEGACY_TAWGET_WATE_6_24,
	WEGACY_TAWGET_WATE_36,
	WEGACY_TAWGET_WATE_48,
	WEGACY_TAWGET_WATE_54
};

enum tawgetPowewCckWates {
	WEGACY_TAWGET_WATE_1W_5W,
	WEGACY_TAWGET_WATE_5S,
	WEGACY_TAWGET_WATE_11W,
	WEGACY_TAWGET_WATE_11S
};

enum aw9300_Wates {
	AWW_TAWGET_WEGACY_6_24,
	AWW_TAWGET_WEGACY_36,
	AWW_TAWGET_WEGACY_48,
	AWW_TAWGET_WEGACY_54,
	AWW_TAWGET_WEGACY_1W_5W,
	AWW_TAWGET_WEGACY_5S,
	AWW_TAWGET_WEGACY_11W,
	AWW_TAWGET_WEGACY_11S,
	AWW_TAWGET_HT20_0_8_16,
	AWW_TAWGET_HT20_1_3_9_11_17_19,
	AWW_TAWGET_HT20_4,
	AWW_TAWGET_HT20_5,
	AWW_TAWGET_HT20_6,
	AWW_TAWGET_HT20_7,
	AWW_TAWGET_HT20_12,
	AWW_TAWGET_HT20_13,
	AWW_TAWGET_HT20_14,
	AWW_TAWGET_HT20_15,
	AWW_TAWGET_HT20_20,
	AWW_TAWGET_HT20_21,
	AWW_TAWGET_HT20_22,
	AWW_TAWGET_HT20_23,
	AWW_TAWGET_HT40_0_8_16,
	AWW_TAWGET_HT40_1_3_9_11_17_19,
	AWW_TAWGET_HT40_4,
	AWW_TAWGET_HT40_5,
	AWW_TAWGET_HT40_6,
	AWW_TAWGET_HT40_7,
	AWW_TAWGET_HT40_12,
	AWW_TAWGET_HT40_13,
	AWW_TAWGET_HT40_14,
	AWW_TAWGET_HT40_15,
	AWW_TAWGET_HT40_20,
	AWW_TAWGET_HT40_21,
	AWW_TAWGET_HT40_22,
	AWW_TAWGET_HT40_23,
	aw9300WateSize,
};


stwuct eepFwags {
	u8 opFwags;
	u8 eepMisc;
} __packed;

enum CompwessAwgowithm {
	_CompwessNone = 0,
	_CompwessWzma,
	_CompwessPaiws,
	_CompwessBwock,
	_Compwess4,
	_Compwess5,
	_Compwess6,
	_Compwess7,
};

stwuct aw9300_base_eep_hdw {
	__we16 wegDmn[2];
	/* 4 bits tx and 4 bits wx */
	u8 txwxMask;
	stwuct eepFwags opCapFwags;
	u8 wfSiwent;
	u8 bwueToothOptions;
	u8 deviceCap;
	/* takes wowew byte in eepwom wocation */
	u8 deviceType;
	/* offset in dB to be added to beginning
	 * of pdadc tabwe in cawibwation
	 */
	int8_t pwwTabweOffset;
	u8 pawams_fow_tuning_caps[2];
	/*
	 * bit0 - enabwe tx temp comp
	 * bit1 - enabwe tx vowt comp
	 * bit2 - enabwe fastCwock - defauwt to 1
	 * bit3 - enabwe doubwing - defauwt to 1
	 * bit4 - enabwe intewnaw weguwatow - defauwt to 1
	 */
	u8 featuweEnabwe;
	/* misc fwags: bit0 - tuwn down dwivestwength */
	u8 miscConfiguwation;
	u8 eepwomWwiteEnabweGpio;
	u8 wwanDisabweGpio;
	u8 wwanWedGpio;
	u8 wxBandSewectGpio;
	u8 txwxgain;
	/* SW contwowwed intewnaw weguwatow fiewds */
	__we32 swweg;
} __packed;

stwuct aw9300_modaw_eep_headew {
	/* 4 idwe, t1, t2, b (4 bits pew setting) */
	__we32 antCtwwCommon;
	/* 4 wa1w1, wa2w1, wa1w2, wa2w2, wa12 */
	__we32 antCtwwCommon2;
	/* 6 idwe, t, w, wx1, wx12, b (2 bits each) */
	__we16 antCtwwChain[AW9300_MAX_CHAINS];
	/* 3 xatten1_db fow AW9280 (0xa20c/b20c 5:0) */
	u8 xatten1DB[AW9300_MAX_CHAINS];
	/* 3  xatten1_mawgin fow mewwin (0xa20c/b20c 16:12 */
	u8 xatten1Mawgin[AW9300_MAX_CHAINS];
	int8_t tempSwope;
	int8_t vowtSwope;
	/* spuw channews in usuaw fbin coding fowmat */
	u8 spuwChans[AW_EEPWOM_MODAW_SPUWS];
	/* 3  Check if the wegistew is pew chain */
	int8_t noiseFwoowThweshCh[AW9300_MAX_CHAINS];
	u8 wesewved[11];
	int8_t quick_dwop;
	u8 xpaBiasWvw;
	u8 txFwameToDataStawt;
	u8 txFwameToPaOn;
	u8 txCwip;
	int8_t antennaGain;
	u8 switchSettwing;
	int8_t adcDesiwedSize;
	u8 txEndToXpaOff;
	u8 txEndToWxOn;
	u8 txFwameToXpaOn;
	u8 thwesh62;
	__we32 papdWateMaskHt20;
	__we32 papdWateMaskHt40;
	__we16 switchcomspdt;
	u8 xwna_bias_stwength;
	u8 futuweModaw[7];
} __packed;

stwuct aw9300_caw_data_pew_fweq_op_woop {
	int8_t wefPowew;
	/* pdadc vowtage at powew measuwement */
	u8 vowtMeas;
	/* pcdac used fow powew measuwement   */
	u8 tempMeas;
	/* wange is -60 to -127 cweate a mapping equation 1db wesowution */
	int8_t wxNoisefwoowCaw;
	/*wange is same as noisefwoow */
	int8_t wxNoisefwoowPowew;
	/* temp measuwed when noisefwoow caw was pewfowmed */
	u8 wxTempMeas;
} __packed;

stwuct caw_tgt_pow_wegacy {
	u8 tPow2x[4];
} __packed;

stwuct caw_tgt_pow_ht {
	u8 tPow2x[14];
} __packed;

stwuct caw_ctw_data_2g {
	u8 ctwEdges[AW9300_NUM_BAND_EDGES_2G];
} __packed;

stwuct caw_ctw_data_5g {
	u8 ctwEdges[AW9300_NUM_BAND_EDGES_5G];
} __packed;

#define MAX_BASE_EXTENSION_FUTUWE 2

stwuct aw9300_BaseExtension_1 {
	u8 ant_div_contwow;
	u8 futuwe[MAX_BASE_EXTENSION_FUTUWE];
	/*
	 * misc_enabwe:
	 *
	 * BIT 0   - TX Gain Cap enabwe.
	 * BIT 1   - Uncompwessed Checksum enabwe.
	 * BIT 2/3 - MinCCApww enabwe 2g/5g.
	 */
	u8 misc_enabwe;
	int8_t tempswopextension[8];
	int8_t quick_dwop_wow;
	int8_t quick_dwop_high;
} __packed;

stwuct aw9300_BaseExtension_2 {
	int8_t    tempSwopeWow;
	int8_t    tempSwopeHigh;
	u8   xatten1DBWow[AW9300_MAX_CHAINS];
	u8   xatten1MawginWow[AW9300_MAX_CHAINS];
	u8   xatten1DBHigh[AW9300_MAX_CHAINS];
	u8   xatten1MawginHigh[AW9300_MAX_CHAINS];
} __packed;

stwuct aw9300_eepwom {
	u8 eepwomVewsion;
	u8 tempwateVewsion;
	u8 macAddw[6];
	u8 custData[AW9300_CUSTOMEW_DATA_SIZE];

	stwuct aw9300_base_eep_hdw baseEepHeadew;

	stwuct aw9300_modaw_eep_headew modawHeadew2G;
	stwuct aw9300_BaseExtension_1 base_ext1;
	u8 cawFweqPiew2G[AW9300_NUM_2G_CAW_PIEWS];
	stwuct aw9300_caw_data_pew_fweq_op_woop
	 cawPiewData2G[AW9300_MAX_CHAINS][AW9300_NUM_2G_CAW_PIEWS];
	u8 cawTawget_fweqbin_Cck[AW9300_NUM_2G_CCK_TAWGET_POWEWS];
	u8 cawTawget_fweqbin_2G[AW9300_NUM_2G_20_TAWGET_POWEWS];
	u8 cawTawget_fweqbin_2GHT20[AW9300_NUM_2G_20_TAWGET_POWEWS];
	u8 cawTawget_fweqbin_2GHT40[AW9300_NUM_2G_40_TAWGET_POWEWS];
	stwuct caw_tgt_pow_wegacy
	 cawTawgetPowewCck[AW9300_NUM_2G_CCK_TAWGET_POWEWS];
	stwuct caw_tgt_pow_wegacy
	 cawTawgetPowew2G[AW9300_NUM_2G_20_TAWGET_POWEWS];
	stwuct caw_tgt_pow_ht
	 cawTawgetPowew2GHT20[AW9300_NUM_2G_20_TAWGET_POWEWS];
	stwuct caw_tgt_pow_ht
	 cawTawgetPowew2GHT40[AW9300_NUM_2G_40_TAWGET_POWEWS];
	u8 ctwIndex_2G[AW9300_NUM_CTWS_2G];
	u8 ctw_fweqbin_2G[AW9300_NUM_CTWS_2G][AW9300_NUM_BAND_EDGES_2G];
	stwuct caw_ctw_data_2g ctwPowewData_2G[AW9300_NUM_CTWS_2G];
	stwuct aw9300_modaw_eep_headew modawHeadew5G;
	stwuct aw9300_BaseExtension_2 base_ext2;
	u8 cawFweqPiew5G[AW9300_NUM_5G_CAW_PIEWS];
	stwuct aw9300_caw_data_pew_fweq_op_woop
	 cawPiewData5G[AW9300_MAX_CHAINS][AW9300_NUM_5G_CAW_PIEWS];
	u8 cawTawget_fweqbin_5G[AW9300_NUM_5G_20_TAWGET_POWEWS];
	u8 cawTawget_fweqbin_5GHT20[AW9300_NUM_5G_20_TAWGET_POWEWS];
	u8 cawTawget_fweqbin_5GHT40[AW9300_NUM_5G_40_TAWGET_POWEWS];
	stwuct caw_tgt_pow_wegacy
	 cawTawgetPowew5G[AW9300_NUM_5G_20_TAWGET_POWEWS];
	stwuct caw_tgt_pow_ht
	 cawTawgetPowew5GHT20[AW9300_NUM_5G_20_TAWGET_POWEWS];
	stwuct caw_tgt_pow_ht
	 cawTawgetPowew5GHT40[AW9300_NUM_5G_40_TAWGET_POWEWS];
	u8 ctwIndex_5G[AW9300_NUM_CTWS_5G];
	u8 ctw_fweqbin_5G[AW9300_NUM_CTWS_5G][AW9300_NUM_BAND_EDGES_5G];
	stwuct caw_ctw_data_5g ctwPowewData_5G[AW9300_NUM_CTWS_5G];
} __packed;

s32 aw9003_hw_get_tx_gain_idx(stwuct ath_hw *ah);
s32 aw9003_hw_get_wx_gain_idx(stwuct ath_hw *ah);
u32 aw9003_hw_ant_ctww_common_get(stwuct ath_hw *ah, boow is2ghz);
u32 aw9003_hw_ant_ctww_common_2_get(stwuct ath_hw *ah, boow is2ghz);

u8 *aw9003_get_spuw_chan_ptw(stwuct ath_hw *ah, boow is_2ghz);

u32 aw9003_get_papwd_wate_mask_ht20(stwuct ath_hw *ah, boow is2ghz);
u32 aw9003_get_papwd_wate_mask_ht40(stwuct ath_hw *ah, boow is2ghz);
unsigned int aw9003_get_papwd_scawe_factow(stwuct ath_hw *ah,
					   stwuct ath9k_channew *chan);

void aw9003_hw_intewnaw_weguwatow_appwy(stwuct ath_hw *ah);
int aw9003_hw_tx_powew_wegwwite(stwuct ath_hw *ah, u8 * pPwwAwway);

#endif
