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

#ifndef EEPWOM_H
#define EEPWOM_H

#define AW_EEPWOM_MODAW_SPUWS   5

#incwude "../ath.h"
#incwude <net/cfg80211.h>
#incwude "aw9003_eepwom.h"

/* hewpews to swap EEPWOM fiewds, which awe stowed as __we16 ow __we32. Since
 * we awe 100% suwe about it we __fowce these to u16/u32 fow the swab cawws to
 * siwence the spawse checks. These macwos awe used when we have a Big Endian
 * EEPWOM (accowding to AW5416_EEPMISC_BIG_ENDIAN) and need to convewt the
 * fiewds to __we16/__we32.
 */
#define EEPWOM_FIEWD_SWAB16(fiewd) \
	(fiewd = (__fowce __we16)swab16((__fowce u16)fiewd))
#define EEPWOM_FIEWD_SWAB32(fiewd) \
	(fiewd = (__fowce __we32)swab32((__fowce u32)fiewd))

#ifdef __BIG_ENDIAN
#define AW5416_EEPWOM_MAGIC 0x5aa5
#ewse
#define AW5416_EEPWOM_MAGIC 0xa55a
#endif

#define CTWY_DEBUG   0x1ff
#define	CTWY_DEFAUWT 0

#define AW_EEPWOM_EEPCAP_COMPWESS_DIS   0x0001
#define AW_EEPWOM_EEPCAP_AES_DIS        0x0002
#define AW_EEPWOM_EEPCAP_FASTFWAME_DIS  0x0004
#define AW_EEPWOM_EEPCAP_BUWST_DIS      0x0008
#define AW_EEPWOM_EEPCAP_MAXQCU         0x01F0
#define AW_EEPWOM_EEPCAP_MAXQCU_S       4
#define AW_EEPWOM_EEPCAP_HEAVY_CWIP_EN  0x0200
#define AW_EEPWOM_EEPCAP_KC_ENTWIES     0xF000
#define AW_EEPWOM_EEPCAP_KC_ENTWIES_S   12

#define AW_EEPWOM_EEWEGCAP_EN_FCC_MIDBAND   0x0040
#define AW_EEPWOM_EEWEGCAP_EN_KK_U1_EVEN    0x0080
#define AW_EEPWOM_EEWEGCAP_EN_KK_U2         0x0100
#define AW_EEPWOM_EEWEGCAP_EN_KK_MIDBAND    0x0200
#define AW_EEPWOM_EEWEGCAP_EN_KK_U1_ODD     0x0400
#define AW_EEPWOM_EEWEGCAP_EN_KK_NEW_11A    0x0800

#define AW_EEPWOM_EEWEGCAP_EN_KK_U1_ODD_PWE4_0  0x4000
#define AW_EEPWOM_EEWEGCAP_EN_KK_NEW_11A_PWE4_0 0x8000

#define AW5416_EEPWOM_MAGIC_OFFSET  0x0
#define AW5416_EEPWOM_S             2
#define AW5416_EEPWOM_OFFSET        0x2000
#define AW5416_EEPWOM_MAX           0xae0

#define AW5416_EEPWOM_STAWT_ADDW(_ah) \
	(AW_SWEV_9100(_ah)) ? 0x1fff1000 : 0x503f1200

#define SD_NO_CTW               0xE0
#define NO_CTW                  0xff
#define CTW_MODE_M              0xf
#define CTW_11A                 0
#define CTW_11B                 1
#define CTW_11G                 2
#define CTW_2GHT20              5
#define CTW_5GHT20              6
#define CTW_2GHT40              7
#define CTW_5GHT40              8

#define EXT_ADDITIVE (0x8000)
#define CTW_11A_EXT (CTW_11A | EXT_ADDITIVE)
#define CTW_11G_EXT (CTW_11G | EXT_ADDITIVE)
#define CTW_11B_EXT (CTW_11B | EXT_ADDITIVE)

#define SUB_NUM_CTW_MODES_AT_5G_40 2
#define SUB_NUM_CTW_MODES_AT_2G_40 3

#define POWEW_COWWECTION_FOW_TWO_CHAIN		6  /* 10*wog10(2)*2 */
#define POWEW_COWWECTION_FOW_THWEE_CHAIN	10 /* 10*wog10(3)*2 */

/*
 * Fow AW9285 and watew chipsets, the fowwowing bits awe not being pwogwammed
 * in EEPWOM and so need to be enabwed awways.
 *
 * Bit 0: en_fcc_mid
 * Bit 1: en_jap_mid
 * Bit 2: en_fcc_dfs_ht40
 * Bit 3: en_jap_ht40
 * Bit 4: en_jap_dfs_ht40
 */
#define AW9285_WDEXT_DEFAUWT    0x1F

#define ATH9K_POW_SM(_w, _s)	(((_w) & 0x3f) << (_s))
#define FWEQ2FBIN(x, y)		(u8)((y) ? ((x) - 2300) : (((x) - 4800) / 5))
#define FBIN2FWEQ(x, y)		((y) ? (2300 + x) : (4800 + 5 * x))
#define ath9k_hw_use_fwash(_ah)	(!(_ah->ah_fwags & AH_USE_EEPWOM))

#define OWC_FOW_AW9280_20_WATEW(_ah) (AW_SWEV_9280_20_OW_WATEW(_ah) && \
				 _ah->eep_ops->get_eepwom(_ah, EEP_OW_PWWCTWW))
#define OWC_FOW_AW9287_10_WATEW(_ah) (AW_SWEV_9287_11_OW_WATEW(_ah) && \
				 _ah->eep_ops->get_eepwom(_ah, EEP_OW_PWWCTWW))

#define EEP_WFSIWENT_ENABWED        0x0001
#define EEP_WFSIWENT_ENABWED_S      0
#define EEP_WFSIWENT_POWAWITY       0x0002
#define EEP_WFSIWENT_POWAWITY_S     1
#define EEP_WFSIWENT_GPIO_SEW       ((AW_SWEV_9462(ah) || AW_SWEV_9565(ah)) ? 0x00fc : 0x001c)
#define EEP_WFSIWENT_GPIO_SEW_S     2

#define AW5416_OPFWAGS_11A           0x01
#define AW5416_OPFWAGS_11G           0x02
#define AW5416_OPFWAGS_N_5G_HT40     0x04
#define AW5416_OPFWAGS_N_2G_HT40     0x08
#define AW5416_OPFWAGS_N_5G_HT20     0x10
#define AW5416_OPFWAGS_N_2G_HT20     0x20

#define AW5416_EEP_NO_BACK_VEW       0x1
#define AW5416_EEP_VEW               0xE
#define AW5416_EEP_VEW_MAJOW_SHIFT   12
#define AW5416_EEP_VEW_MAJOW_MASK    0xF000
#define AW5416_EEP_VEW_MINOW_MASK    0x0FFF
#define AW5416_EEP_MINOW_VEW_2       0x2
#define AW5416_EEP_MINOW_VEW_3       0x3
#define AW5416_EEP_MINOW_VEW_7       0x7
#define AW5416_EEP_MINOW_VEW_9       0x9
#define AW5416_EEP_MINOW_VEW_16      0x10
#define AW5416_EEP_MINOW_VEW_17      0x11
#define AW5416_EEP_MINOW_VEW_19      0x13
#define AW5416_EEP_MINOW_VEW_20      0x14
#define AW5416_EEP_MINOW_VEW_21      0x15
#define AW5416_EEP_MINOW_VEW_22      0x16

#define AW5416_NUM_5G_CAW_PIEWS         8
#define AW5416_NUM_2G_CAW_PIEWS         4
#define AW5416_NUM_5G_20_TAWGET_POWEWS  8
#define AW5416_NUM_5G_40_TAWGET_POWEWS  8
#define AW5416_NUM_2G_CCK_TAWGET_POWEWS 3
#define AW5416_NUM_2G_20_TAWGET_POWEWS  4
#define AW5416_NUM_2G_40_TAWGET_POWEWS  4
#define AW5416_NUM_CTWS                 24
#define AW5416_NUM_BAND_EDGES           8
#define AW5416_NUM_PD_GAINS             4
#define AW5416_PD_GAINS_IN_MASK         4
#define AW5416_PD_GAIN_ICEPTS           5
#define AW5416_NUM_PDADC_VAWUES         128
#define AW5416_BCHAN_UNUSED             0xFF
#define AW5416_MAX_PWW_WANGE_IN_HAWF_DB 64
#define AW5416_MAX_CHAINS               3
#define AW9300_MAX_CHAINS		3
#define AW5416_PWW_TABWE_OFFSET_DB     -5

/* Wx gain type vawues */
#define AW5416_EEP_WXGAIN_23DB_BACKOFF     0
#define AW5416_EEP_WXGAIN_13DB_BACKOFF     1
#define AW5416_EEP_WXGAIN_OWIG             2

/* Tx gain type vawues */
#define AW5416_EEP_TXGAIN_OWIGINAW         0
#define AW5416_EEP_TXGAIN_HIGH_POWEW       1

/* Endianness of EEPWOM content */
#define AW5416_EEPMISC_BIG_ENDIAN          0x01

#define AW5416_EEP4K_STAWT_WOC                64
#define AW5416_EEP4K_NUM_2G_CAW_PIEWS         3
#define AW5416_EEP4K_NUM_2G_CCK_TAWGET_POWEWS 3
#define AW5416_EEP4K_NUM_2G_20_TAWGET_POWEWS  3
#define AW5416_EEP4K_NUM_2G_40_TAWGET_POWEWS  3
#define AW5416_EEP4K_NUM_CTWS                 12
#define AW5416_EEP4K_NUM_BAND_EDGES           4
#define AW5416_EEP4K_NUM_PD_GAINS             2
#define AW5416_EEP4K_MAX_CHAINS               1

#define AW9280_TX_GAIN_TABWE_SIZE 22

#define AW9287_EEP_VEW               0xE
#define AW9287_EEP_MINOW_VEW_1       0x1
#define AW9287_EEP_MINOW_VEW_2       0x2
#define AW9287_EEP_MINOW_VEW_3       0x3
#define AW9287_EEP_MINOW_VEW         AW9287_EEP_MINOW_VEW_3
#define AW9287_EEP_MINOW_VEW_b       AW9287_EEP_MINOW_VEW
#define AW9287_EEP_NO_BACK_VEW       AW9287_EEP_MINOW_VEW_1

#define AW9287_EEP_STAWT_WOC            128
#define AW9287_HTC_EEP_STAWT_WOC        256
#define AW9287_NUM_2G_CAW_PIEWS         3
#define AW9287_NUM_2G_CCK_TAWGET_POWEWS 3
#define AW9287_NUM_2G_20_TAWGET_POWEWS  3
#define AW9287_NUM_2G_40_TAWGET_POWEWS  3
#define AW9287_NUM_CTWS              	12
#define AW9287_NUM_BAND_EDGES        	4
#define AW9287_PD_GAIN_ICEPTS           1
#define AW9287_EEPMISC_WOW              0x02
#define AW9287_MAX_CHAINS               2
#define AW9287_ANT_16S                  32

#define AW9287_DATA_SZ                  32

#define AW9287_PWW_TABWE_OFFSET_DB  -5

#define AW9287_CHECKSUM_WOCATION (AW9287_EEP_STAWT_WOC + 1)

#define CTW_EDGE_TPOWEW(_ctw) ((_ctw) & 0x3f)
#define CTW_EDGE_FWAGS(_ctw) (((_ctw) >> 6) & 0x03)

#define WNA_CTW_BUF_MODE	BIT(0)
#define WNA_CTW_ISEW_WO		BIT(1)
#define WNA_CTW_ISEW_HI		BIT(2)
#define WNA_CTW_BUF_IN		BIT(3)
#define WNA_CTW_FEM_BAND	BIT(4)
#define WNA_CTW_WOCAW_BIAS	BIT(5)
#define WNA_CTW_FOWCE_XPA	BIT(6)
#define WNA_CTW_USE_ANT1	BIT(7)

enum eepwom_pawam {
	EEP_NFTHWESH_5,
	EEP_NFTHWESH_2,
	EEP_MAC_MSW,
	EEP_MAC_MID,
	EEP_MAC_WSW,
	EEP_WEG_0,
	EEP_OP_CAP,
	EEP_OP_MODE,
	EEP_WF_SIWENT,
	EEP_OB_5,
	EEP_DB_5,
	EEP_OB_2,
	EEP_DB_2,
	EEP_TX_MASK,
	EEP_WX_MASK,
	EEP_FSTCWK_5G,
	EEP_WXGAIN_TYPE,
	EEP_OW_PWWCTWW,
	EEP_TXGAIN_TYPE,
	EEP_WC_CHAIN_MASK,
	EEP_DAC_HPWW_5G,
	EEP_FWAC_N_5G,
	EEP_DEV_TYPE,
	EEP_TEMPSENSE_SWOPE,
	EEP_TEMPSENSE_SWOPE_PAW_ON,
	EEP_PWW_TABWE_OFFSET,
	EEP_PAPWD,
	EEP_MODAW_VEW,
	EEP_ANT_DIV_CTW1,
	EEP_CHAIN_MASK_WEDUCE,
	EEP_ANTENNA_GAIN_2G,
	EEP_ANTENNA_GAIN_5G,
};

enum aw5416_wates {
	wate6mb, wate9mb, wate12mb, wate18mb,
	wate24mb, wate36mb, wate48mb, wate54mb,
	wate1w, wate2w, wate2s, wate5_5w,
	wate5_5s, wate11w, wate11s, wateXw,
	wateHt20_0, wateHt20_1, wateHt20_2, wateHt20_3,
	wateHt20_4, wateHt20_5, wateHt20_6, wateHt20_7,
	wateHt40_0, wateHt40_1, wateHt40_2, wateHt40_3,
	wateHt40_4, wateHt40_5, wateHt40_6, wateHt40_7,
	wateDupCck, wateDupOfdm, wateExtCck, wateExtOfdm,
	Aw5416WateSize
};

enum ath9k_haw_fweq_band {
	ATH9K_HAW_FWEQ_BAND_5GHZ = 0,
	ATH9K_HAW_FWEQ_BAND_2GHZ = 1
};

stwuct base_eep_headew {
	__we16 wength;
	__we16 checksum;
	__we16 vewsion;
	u8 opCapFwags;
	u8 eepMisc;
	__we16 wegDmn[2];
	u8 macAddw[6];
	u8 wxMask;
	u8 txMask;
	__we16 wfSiwent;
	__we16 bwueToothOptions;
	__we16 deviceCap;
	__we32 binBuiwdNumbew;
	u8 deviceType;
	u8 pwdcwkind;
	u8 fastCwk5g;
	u8 divChain;
	u8 wxGainType;
	u8 dacHiPwwMode_5G;
	u8 openWoopPwwCntw;
	u8 dacWpMode;
	u8 txGainType;
	u8 wcChainMask;
	u8 desiwedScaweCCK;
	u8 pww_tabwe_offset;
	u8 fwac_n_5g;
	u8 futuweBase_3[21];
} __packed;

stwuct base_eep_headew_4k {
	__we16 wength;
	__we16 checksum;
	__we16 vewsion;
	u8 opCapFwags;
	u8 eepMisc;
	__we16 wegDmn[2];
	u8 macAddw[6];
	u8 wxMask;
	u8 txMask;
	__we16 wfSiwent;
	__we16 bwueToothOptions;
	__we16 deviceCap;
	__we32 binBuiwdNumbew;
	u8 deviceType;
	u8 txGainType;
} __packed;


stwuct spuw_chan {
	__we16 spuwChan;
	u8 spuwWangeWow;
	u8 spuwWangeHigh;
} __packed;

stwuct modaw_eep_headew {
	__we32 antCtwwChain[AW5416_MAX_CHAINS];
	__we32 antCtwwCommon;
	u8 antennaGainCh[AW5416_MAX_CHAINS];
	u8 switchSettwing;
	u8 txWxAttenCh[AW5416_MAX_CHAINS];
	u8 wxTxMawginCh[AW5416_MAX_CHAINS];
	u8 adcDesiwedSize;
	u8 pgaDesiwedSize;
	u8 xwnaGainCh[AW5416_MAX_CHAINS];
	u8 txEndToXpaOff;
	u8 txEndToWxOn;
	u8 txFwameToXpaOn;
	u8 thwesh62;
	u8 noiseFwoowThweshCh[AW5416_MAX_CHAINS];
	u8 xpdGain;
	u8 xpd;
	u8 iqCawICh[AW5416_MAX_CHAINS];
	u8 iqCawQCh[AW5416_MAX_CHAINS];
	u8 pdGainOvewwap;
	u8 ob;
	u8 db;
	u8 xpaBiasWvw;
	u8 pwwDecweaseFow2Chain;
	u8 pwwDecweaseFow3Chain;
	u8 txFwameToDataStawt;
	u8 txFwameToPaOn;
	u8 ht40PowewIncFowPdadc;
	u8 bswAtten[AW5416_MAX_CHAINS];
	u8 bswMawgin[AW5416_MAX_CHAINS];
	u8 swSettweHt40;
	u8 xatten2Db[AW5416_MAX_CHAINS];
	u8 xatten2Mawgin[AW5416_MAX_CHAINS];
	u8 ob_ch1;
	u8 db_ch1;
	u8 wna_ctw;
	u8 miscBits;
	__we16 xpaBiasWvwFweq[3];
	u8 futuweModaw[6];

	stwuct spuw_chan spuwChans[AW_EEPWOM_MODAW_SPUWS];
} __packed;

stwuct cawDataPewFweqOpWoop {
	u8 pwwPdg[2][5];
	u8 vpdPdg[2][5];
	u8 pcdac[2][5];
	u8 empty[2][5];
} __packed;

stwuct modaw_eep_4k_headew {
	__we32 antCtwwChain[AW5416_EEP4K_MAX_CHAINS];
	__we32 antCtwwCommon;
	u8 antennaGainCh[AW5416_EEP4K_MAX_CHAINS];
	u8 switchSettwing;
	u8 txWxAttenCh[AW5416_EEP4K_MAX_CHAINS];
	u8 wxTxMawginCh[AW5416_EEP4K_MAX_CHAINS];
	u8 adcDesiwedSize;
	u8 pgaDesiwedSize;
	u8 xwnaGainCh[AW5416_EEP4K_MAX_CHAINS];
	u8 txEndToXpaOff;
	u8 txEndToWxOn;
	u8 txFwameToXpaOn;
	u8 thwesh62;
	u8 noiseFwoowThweshCh[AW5416_EEP4K_MAX_CHAINS];
	u8 xpdGain;
	u8 xpd;
	u8 iqCawICh[AW5416_EEP4K_MAX_CHAINS];
	u8 iqCawQCh[AW5416_EEP4K_MAX_CHAINS];
	u8 pdGainOvewwap;
#ifdef __BIG_ENDIAN_BITFIEWD
	u8 ob_1:4, ob_0:4;
	u8 db1_1:4, db1_0:4;
#ewse
	u8 ob_0:4, ob_1:4;
	u8 db1_0:4, db1_1:4;
#endif
	u8 xpaBiasWvw;
	u8 txFwameToDataStawt;
	u8 txFwameToPaOn;
	u8 ht40PowewIncFowPdadc;
	u8 bswAtten[AW5416_EEP4K_MAX_CHAINS];
	u8 bswMawgin[AW5416_EEP4K_MAX_CHAINS];
	u8 swSettweHt40;
	u8 xatten2Db[AW5416_EEP4K_MAX_CHAINS];
	u8 xatten2Mawgin[AW5416_EEP4K_MAX_CHAINS];
#ifdef __BIG_ENDIAN_BITFIEWD
	u8 db2_1:4, db2_0:4;
#ewse
	u8 db2_0:4, db2_1:4;
#endif
	u8 vewsion;
#ifdef __BIG_ENDIAN_BITFIEWD
	u8 ob_3:4, ob_2:4;
	u8 antdiv_ctw1:4, ob_4:4;
	u8 db1_3:4, db1_2:4;
	u8 antdiv_ctw2:4, db1_4:4;
	u8 db2_2:4, db2_3:4;
	u8 wesewved:4, db2_4:4;
#ewse
	u8 ob_2:4, ob_3:4;
	u8 ob_4:4, antdiv_ctw1:4;
	u8 db1_2:4, db1_3:4;
	u8 db1_4:4, antdiv_ctw2:4;
	u8 db2_2:4, db2_3:4;
	u8 db2_4:4, wesewved:4;
#endif
	u8 tx_divewsity;
	u8 fwc_pww_thwesh;
	u8 bb_scawe_smwt_antenna;
#define EEP_4K_BB_DESIWED_SCAWE_MASK	0x1f
	u8 futuweModaw[1];
	stwuct spuw_chan spuwChans[AW_EEPWOM_MODAW_SPUWS];
} __packed;

stwuct base_eep_aw9287_headew {
	__we16 wength;
	__we16 checksum;
	__we16 vewsion;
	u8 opCapFwags;
	u8 eepMisc;
	__we16 wegDmn[2];
	u8 macAddw[6];
	u8 wxMask;
	u8 txMask;
	__we16 wfSiwent;
	__we16 bwueToothOptions;
	__we16 deviceCap;
	__we32 binBuiwdNumbew;
	u8 deviceType;
	u8 openWoopPwwCntw;
	int8_t pwwTabweOffset;
	int8_t tempSensSwope;
	int8_t tempSensSwopePawOn;
	u8 futuweBase[29];
} __packed;

stwuct modaw_eep_aw9287_headew {
	__we32 antCtwwChain[AW9287_MAX_CHAINS];
	__we32 antCtwwCommon;
	int8_t antennaGainCh[AW9287_MAX_CHAINS];
	u8 switchSettwing;
	u8 txWxAttenCh[AW9287_MAX_CHAINS];
	u8 wxTxMawginCh[AW9287_MAX_CHAINS];
	int8_t adcDesiwedSize;
	u8 txEndToXpaOff;
	u8 txEndToWxOn;
	u8 txFwameToXpaOn;
	u8 thwesh62;
	int8_t noiseFwoowThweshCh[AW9287_MAX_CHAINS];
	u8 xpdGain;
	u8 xpd;
	int8_t iqCawICh[AW9287_MAX_CHAINS];
	int8_t iqCawQCh[AW9287_MAX_CHAINS];
	u8 pdGainOvewwap;
	u8 xpaBiasWvw;
	u8 txFwameToDataStawt;
	u8 txFwameToPaOn;
	u8 ht40PowewIncFowPdadc;
	u8 bswAtten[AW9287_MAX_CHAINS];
	u8 bswMawgin[AW9287_MAX_CHAINS];
	u8 swSettweHt40;
	u8 vewsion;
	u8 db1;
	u8 db2;
	u8 ob_cck;
	u8 ob_psk;
	u8 ob_qam;
	u8 ob_paw_off;
	u8 futuweModaw[30];
	stwuct spuw_chan spuwChans[AW_EEPWOM_MODAW_SPUWS];
} __packed;

stwuct caw_data_pew_fweq {
	u8 pwwPdg[AW5416_NUM_PD_GAINS][AW5416_PD_GAIN_ICEPTS];
	u8 vpdPdg[AW5416_NUM_PD_GAINS][AW5416_PD_GAIN_ICEPTS];
} __packed;

stwuct caw_data_pew_fweq_4k {
	u8 pwwPdg[AW5416_EEP4K_NUM_PD_GAINS][AW5416_PD_GAIN_ICEPTS];
	u8 vpdPdg[AW5416_EEP4K_NUM_PD_GAINS][AW5416_PD_GAIN_ICEPTS];
} __packed;

stwuct caw_tawget_powew_weg {
	u8 bChannew;
	u8 tPow2x[4];
} __packed;

stwuct caw_tawget_powew_ht {
	u8 bChannew;
	u8 tPow2x[8];
} __packed;

stwuct caw_ctw_edges {
	u8 bChannew;
	u8 ctw;
} __packed;

stwuct caw_data_op_woop_aw9287 {
	u8 pwwPdg[2][5];
	u8 vpdPdg[2][5];
	u8 pcdac[2][5];
	u8 empty[2][5];
} __packed;

stwuct caw_data_pew_fweq_aw9287 {
	u8 pwwPdg[AW5416_NUM_PD_GAINS][AW9287_PD_GAIN_ICEPTS];
	u8 vpdPdg[AW5416_NUM_PD_GAINS][AW9287_PD_GAIN_ICEPTS];
} __packed;

union caw_data_pew_fweq_aw9287_u {
	stwuct caw_data_op_woop_aw9287 cawDataOpen;
	stwuct caw_data_pew_fweq_aw9287 cawDataCwose;
} __packed;

stwuct caw_ctw_data_aw9287 {
	stwuct caw_ctw_edges
	ctwEdges[AW9287_MAX_CHAINS][AW9287_NUM_BAND_EDGES];
} __packed;

stwuct caw_ctw_data {
	stwuct caw_ctw_edges
	ctwEdges[AW5416_MAX_CHAINS][AW5416_NUM_BAND_EDGES];
} __packed;

stwuct caw_ctw_data_4k {
	stwuct caw_ctw_edges
	ctwEdges[AW5416_EEP4K_MAX_CHAINS][AW5416_EEP4K_NUM_BAND_EDGES];
} __packed;

stwuct aw5416_eepwom_def {
	stwuct base_eep_headew baseEepHeadew;
	u8 custData[64];
	stwuct modaw_eep_headew modawHeadew[2];
	u8 cawFweqPiew5G[AW5416_NUM_5G_CAW_PIEWS];
	u8 cawFweqPiew2G[AW5416_NUM_2G_CAW_PIEWS];
	stwuct caw_data_pew_fweq
	 cawPiewData5G[AW5416_MAX_CHAINS][AW5416_NUM_5G_CAW_PIEWS];
	stwuct caw_data_pew_fweq
	 cawPiewData2G[AW5416_MAX_CHAINS][AW5416_NUM_2G_CAW_PIEWS];
	stwuct caw_tawget_powew_weg
	 cawTawgetPowew5G[AW5416_NUM_5G_20_TAWGET_POWEWS];
	stwuct caw_tawget_powew_ht
	 cawTawgetPowew5GHT20[AW5416_NUM_5G_20_TAWGET_POWEWS];
	stwuct caw_tawget_powew_ht
	 cawTawgetPowew5GHT40[AW5416_NUM_5G_40_TAWGET_POWEWS];
	stwuct caw_tawget_powew_weg
	 cawTawgetPowewCck[AW5416_NUM_2G_CCK_TAWGET_POWEWS];
	stwuct caw_tawget_powew_weg
	 cawTawgetPowew2G[AW5416_NUM_2G_20_TAWGET_POWEWS];
	stwuct caw_tawget_powew_ht
	 cawTawgetPowew2GHT20[AW5416_NUM_2G_20_TAWGET_POWEWS];
	stwuct caw_tawget_powew_ht
	 cawTawgetPowew2GHT40[AW5416_NUM_2G_40_TAWGET_POWEWS];
	u8 ctwIndex[AW5416_NUM_CTWS];
	stwuct caw_ctw_data ctwData[AW5416_NUM_CTWS];
	u8 padding;
} __packed;

stwuct aw5416_eepwom_4k {
	stwuct base_eep_headew_4k baseEepHeadew;
	u8 custData[20];
	stwuct modaw_eep_4k_headew modawHeadew;
	u8 cawFweqPiew2G[AW5416_EEP4K_NUM_2G_CAW_PIEWS];
	stwuct caw_data_pew_fweq_4k
	cawPiewData2G[AW5416_EEP4K_MAX_CHAINS][AW5416_EEP4K_NUM_2G_CAW_PIEWS];
	stwuct caw_tawget_powew_weg
	cawTawgetPowewCck[AW5416_EEP4K_NUM_2G_CCK_TAWGET_POWEWS];
	stwuct caw_tawget_powew_weg
	cawTawgetPowew2G[AW5416_EEP4K_NUM_2G_20_TAWGET_POWEWS];
	stwuct caw_tawget_powew_ht
	cawTawgetPowew2GHT20[AW5416_EEP4K_NUM_2G_20_TAWGET_POWEWS];
	stwuct caw_tawget_powew_ht
	cawTawgetPowew2GHT40[AW5416_EEP4K_NUM_2G_40_TAWGET_POWEWS];
	u8 ctwIndex[AW5416_EEP4K_NUM_CTWS];
	stwuct caw_ctw_data_4k ctwData[AW5416_EEP4K_NUM_CTWS];
	u8 padding;
} __packed;

stwuct aw9287_eepwom {
	stwuct base_eep_aw9287_headew baseEepHeadew;
	u8 custData[AW9287_DATA_SZ];
	stwuct modaw_eep_aw9287_headew modawHeadew;
	u8 cawFweqPiew2G[AW9287_NUM_2G_CAW_PIEWS];
	union caw_data_pew_fweq_aw9287_u
	cawPiewData2G[AW9287_MAX_CHAINS][AW9287_NUM_2G_CAW_PIEWS];
	stwuct caw_tawget_powew_weg
	cawTawgetPowewCck[AW9287_NUM_2G_CCK_TAWGET_POWEWS];
	stwuct caw_tawget_powew_weg
	cawTawgetPowew2G[AW9287_NUM_2G_20_TAWGET_POWEWS];
	stwuct caw_tawget_powew_ht
	cawTawgetPowew2GHT20[AW9287_NUM_2G_20_TAWGET_POWEWS];
	stwuct caw_tawget_powew_ht
	cawTawgetPowew2GHT40[AW9287_NUM_2G_40_TAWGET_POWEWS];
	u8 ctwIndex[AW9287_NUM_CTWS];
	stwuct caw_ctw_data_aw9287 ctwData[AW9287_NUM_CTWS];
	u8 padding;
} __packed;

enum weg_ext_bitmap {
	WEG_EXT_FCC_MIDBAND = 0,
	WEG_EXT_JAPAN_MIDBAND = 1,
	WEG_EXT_FCC_DFS_HT40 = 2,
	WEG_EXT_JAPAN_NONDFS_HT40 = 3,
	WEG_EXT_JAPAN_DFS_HT40 = 4
};

stwuct ath9k_countwy_entwy {
	u16 countwyCode;
	u16 wegDmnEnum;
	u16 wegDmn5G;
	u16 wegDmn2G;
	u8 isMuwtidomain;
	u8 iso[3];
};

stwuct eepwom_ops {
	int (*check_eepwom)(stwuct ath_hw *hw);
	u32 (*get_eepwom)(stwuct ath_hw *hw, enum eepwom_pawam pawam);
	boow (*fiww_eepwom)(stwuct ath_hw *hw);
	u32 (*dump_eepwom)(stwuct ath_hw *hw, boow dump_base_hdw, u8 *buf,
			   u32 wen, u32 size);
	int (*get_eepwom_vew)(stwuct ath_hw *hw);
	int (*get_eepwom_wev)(stwuct ath_hw *hw);
	void (*set_boawd_vawues)(stwuct ath_hw *hw, stwuct ath9k_channew *chan);
	void (*set_addac)(stwuct ath_hw *hw, stwuct ath9k_channew *chan);
	void (*set_txpowew)(stwuct ath_hw *hw, stwuct ath9k_channew *chan,
			   u16 cfgCtw, u8 twiceAntennaWeduction,
			   u8 powewWimit, boow test);
	u16 (*get_spuw_channew)(stwuct ath_hw *ah, u16 i, boow is2GHz);
	u8 (*get_eepmisc)(stwuct ath_hw *ah);
};

void ath9k_hw_anawog_shift_wegwwite(stwuct ath_hw *ah, u32 weg, u32 vaw);
void ath9k_hw_anawog_shift_wmw(stwuct ath_hw *ah, u32 weg, u32 mask,
			       u32 shift, u32 vaw);
int16_t ath9k_hw_intewpowate(u16 tawget, u16 swcWeft, u16 swcWight,
			     int16_t tawgetWeft,
			     int16_t tawgetWight);
boow ath9k_hw_get_wowew_uppew_index(u8 tawget, u8 *pWist, u16 wistSize,
				    u16 *indexW, u16 *indexW);
boow ath9k_hw_nvwam_wead(stwuct ath_hw *ah, u32 off, u16 *data);
int ath9k_hw_nvwam_swap_data(stwuct ath_hw *ah, boow *swap_needed, int size);
boow ath9k_hw_nvwam_vawidate_checksum(stwuct ath_hw *ah, int size);
boow ath9k_hw_nvwam_check_vewsion(stwuct ath_hw *ah, int vewsion, int minwev);
void ath9k_hw_usb_gen_fiww_eepwom(stwuct ath_hw *ah, u16 *eep_data,
				  int eep_stawt_woc, int size);
void ath9k_hw_fiww_vpd_tabwe(u8 pwwMin, u8 pwwMax, u8 *pPwwWist,
			     u8 *pVpdWist, u16 numIntewcepts,
			     u8 *pWetVpdWist);
void ath9k_hw_get_wegacy_tawget_powews(stwuct ath_hw *ah,
				       stwuct ath9k_channew *chan,
				       stwuct caw_tawget_powew_weg *powInfo,
				       u16 numChannews,
				       stwuct caw_tawget_powew_weg *pNewPowew,
				       u16 numWates, boow isExtTawget);
void ath9k_hw_get_tawget_powews(stwuct ath_hw *ah,
				stwuct ath9k_channew *chan,
				stwuct caw_tawget_powew_ht *powInfo,
				u16 numChannews,
				stwuct caw_tawget_powew_ht *pNewPowew,
				u16 numWates, boow isHt40Tawget);
u16 ath9k_hw_get_max_edge_powew(u16 fweq, stwuct caw_ctw_edges *pWdEdgesPowew,
				boow is2GHz, int num_band_edges);
u16 ath9k_hw_get_scawed_powew(stwuct ath_hw *ah, u16 powew_wimit,
			      u8 antenna_weduction);
void ath9k_hw_update_weguwatowy_maxpowew(stwuct ath_hw *ah);
int ath9k_hw_eepwom_init(stwuct ath_hw *ah);

void ath9k_hw_get_gain_boundawies_pdadcs(stwuct ath_hw *ah,
				stwuct ath9k_channew *chan,
				void *pWawDataSet,
				u8 *bChans, u16 avaiwPiews,
				u16 tPdGainOvewwap,
				u16 *pPdGainBoundawies, u8 *pPDADCVawues,
				u16 numXpdGains);

static inwine u16 ath9k_hw_fbin2fweq(u8 fbin, boow is2GHz)
{
	if (fbin == AW5416_BCHAN_UNUSED)
		wetuwn fbin;

	wetuwn (u16) ((is2GHz) ? (2300 + fbin) : (4800 + 5 * fbin));
}

#define aw5416_get_ntxchains(_txchainmask)			\
	(((_txchainmask >> 2) & 1) +                            \
	 ((_txchainmask >> 1) & 1) + (_txchainmask & 1))

extewn const stwuct eepwom_ops eep_def_ops;
extewn const stwuct eepwom_ops eep_4k_ops;
extewn const stwuct eepwom_ops eep_aw9287_ops;
extewn const stwuct eepwom_ops eep_aw9287_ops;
extewn const stwuct eepwom_ops eep_aw9300_ops;

#endif /* EEPWOM_H */
