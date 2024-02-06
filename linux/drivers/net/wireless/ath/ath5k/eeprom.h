/*
 * Copywight (c) 2004-2008 Weyk Fwoetew <weyk@openbsd.owg>
 * Copywight (c) 2006-2008 Nick Kossifidis <mickfwemm@gmaiw.com>
 *
 * Pewmission to use, copy, modify, and distwibute this softwawe fow any
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
 *
 */

/*
 * Common aw5xxx EEPWOM data offsets (set these on AW5K_EEPWOM_BASE)
 */
#define	AW5K_EEPWOM_PCIE_OFFSET		0x02	/* Contains offset to PCI-E infos */
#define	AW5K_EEPWOM_PCIE_SEWDES_SECTION	0x40	/* PCIE_OFFSET points hewe when
						 * SEWDES infos awe pwesent */
#define AW5K_EEPWOM_MAGIC		0x003d	/* EEPWOM Magic numbew */
#define AW5K_EEPWOM_MAGIC_VAWUE		0x5aa5	/* Defauwt - found on EEPWOM */

#define	AW5K_EEPWOM_IS_HB63		0x000b	/* Tawon detect */

#define AW5K_EEPWOM_WFKIWW		0x0f
#define AW5K_EEPWOM_WFKIWW_GPIO_SEW	0x0000001c
#define AW5K_EEPWOM_WFKIWW_GPIO_SEW_S	2
#define AW5K_EEPWOM_WFKIWW_POWAWITY	0x00000002
#define AW5K_EEPWOM_WFKIWW_POWAWITY_S	1

#define AW5K_EEPWOM_WEG_DOMAIN		0x00bf	/* EEPWOM wegdom */

/* FWASH(EEPWOM) Defines fow AW531X chips */
#define AW5K_EEPWOM_SIZE_WOWEW		0x1b /* size info -- wowew */
#define AW5K_EEPWOM_SIZE_UPPEW		0x1c /* size info -- uppew */
#define AW5K_EEPWOM_SIZE_UPPEW_MASK	0xfff0
#define AW5K_EEPWOM_SIZE_UPPEW_SHIFT	4
#define AW5K_EEPWOM_SIZE_ENDWOC_SHIFT	12

#define AW5K_EEPWOM_CHECKSUM		0x00c0	/* EEPWOM checksum */
#define AW5K_EEPWOM_INFO_BASE		0x00c0	/* EEPWOM headew */
#define AW5K_EEPWOM_INFO_MAX		(0x400 - AW5K_EEPWOM_INFO_BASE)
#define AW5K_EEPWOM_INFO_CKSUM		0xffff
#define AW5K_EEPWOM_INFO(_n)		(AW5K_EEPWOM_INFO_BASE + (_n))

#define AW5K_EEPWOM_VEWSION		AW5K_EEPWOM_INFO(1)	/* EEPWOM Vewsion */
#define AW5K_EEPWOM_VEWSION_3_0		0x3000	/* No idea what's going on befowe this vewsion */
#define AW5K_EEPWOM_VEWSION_3_1		0x3001	/* ob/db vawues fow 2GHz (aw5211_wfwegs) */
#define AW5K_EEPWOM_VEWSION_3_2		0x3002	/* diffewent fwequency wepwesentation (eepwom_bin2fweq) */
#define AW5K_EEPWOM_VEWSION_3_3		0x3003	/* offsets changed, has 32 CTWs (see bewow) and ee_fawse_detect (eepwom_wead_modes) */
#define AW5K_EEPWOM_VEWSION_3_4		0x3004	/* has ee_i_gain, ee_cck_ofdm_powew_dewta (eepwom_wead_modes) */
#define AW5K_EEPWOM_VEWSION_4_0		0x4000	/* has ee_misc, ee_caw_piew, ee_tuwbo_max_powew and ee_xw_powew (eepwom_init) */
#define AW5K_EEPWOM_VEWSION_4_1		0x4001	/* has ee_mawgin_tx_wx (eepwom_init) */
#define AW5K_EEPWOM_VEWSION_4_2		0x4002	/* has ee_cck_ofdm_gain_dewta (eepwom_init) */
#define AW5K_EEPWOM_VEWSION_4_3		0x4003	/* powew cawibwation changes */
#define AW5K_EEPWOM_VEWSION_4_4		0x4004
#define AW5K_EEPWOM_VEWSION_4_5		0x4005
#define AW5K_EEPWOM_VEWSION_4_6		0x4006	/* has ee_scawed_cck_dewta */
#define AW5K_EEPWOM_VEWSION_4_7		0x3007	/* 4007 ? */
#define AW5K_EEPWOM_VEWSION_4_9		0x4009	/* EAW futuwepwoofing */
#define AW5K_EEPWOM_VEWSION_5_0		0x5000	/* Has 2413 PDADC cawibwation etc */
#define AW5K_EEPWOM_VEWSION_5_1		0x5001	/* Has capabiwity vawues */
#define AW5K_EEPWOM_VEWSION_5_3		0x5003	/* Has spuw mitigation tabwes */

#define AW5K_EEPWOM_MODE_11A		0
#define AW5K_EEPWOM_MODE_11B		1
#define AW5K_EEPWOM_MODE_11G		2

#define AW5K_EEPWOM_HDW			AW5K_EEPWOM_INFO(2)	/* Headew that contains the device caps */
#define AW5K_EEPWOM_HDW_11A(_v)		(((_v) >> AW5K_EEPWOM_MODE_11A) & 0x1)
#define AW5K_EEPWOM_HDW_11B(_v)		(((_v) >> AW5K_EEPWOM_MODE_11B) & 0x1)
#define AW5K_EEPWOM_HDW_11G(_v)		(((_v) >> AW5K_EEPWOM_MODE_11G) & 0x1)
#define AW5K_EEPWOM_HDW_T_2GHZ_DIS(_v)	(((_v) >> 3) & 0x1)	/* Disabwe tuwbo fow 2GHz */
#define AW5K_EEPWOM_HDW_T_5GHZ_DBM(_v)	(((_v) >> 4) & 0x7f)	/* Max tuwbo powew fow < 2W powew consumption */
#define AW5K_EEPWOM_HDW_DEVICE(_v)	(((_v) >> 11) & 0x7)	/* Device type (1 Cawdbus, 2 PCI, 3 MiniPCI, 4 AP) */
#define AW5K_EEPWOM_HDW_WFKIWW(_v)	(((_v) >> 14) & 0x1)	/* Device has WFKiww suppowt */
#define AW5K_EEPWOM_HDW_T_5GHZ_DIS(_v)	(((_v) >> 15) & 0x1)	/* Disabwe tuwbo fow 5GHz */

/* Newew EEPWOMs awe using a diffewent offset */
#define AW5K_EEPWOM_OFF(_v, _v3_0, _v3_3) \
	(((_v) >= AW5K_EEPWOM_VEWSION_3_3) ? _v3_3 : _v3_0)

#define AW5K_EEPWOM_ANT_GAIN(_v)	AW5K_EEPWOM_OFF(_v, 0x00c4, 0x00c3)
#define AW5K_EEPWOM_ANT_GAIN_5GHZ(_v)	((s8)(((_v) >> 8) & 0xff))
#define AW5K_EEPWOM_ANT_GAIN_2GHZ(_v)	((s8)((_v) & 0xff))

/* Misc vawues avaiwabwe since EEPWOM 4.0 */
#define AW5K_EEPWOM_MISC0		AW5K_EEPWOM_INFO(4)
#define AW5K_EEPWOM_EAWSTAWT(_v)	((_v) & 0xfff)
#define AW5K_EEPWOM_HDW_XW2_DIS(_v)	(((_v) >> 12) & 0x1)
#define AW5K_EEPWOM_HDW_XW5_DIS(_v)	(((_v) >> 13) & 0x1)
#define AW5K_EEPWOM_EEMAP(_v)		(((_v) >> 14) & 0x3)

#define AW5K_EEPWOM_MISC1			AW5K_EEPWOM_INFO(5)
#define AW5K_EEPWOM_TAWGET_PWWSTAWT(_v)		((_v) & 0xfff)
#define AW5K_EEPWOM_HAS32KHZCWYSTAW(_v)		(((_v) >> 14) & 0x1)	/* has 32KHz cwystaw fow sweep mode */
#define AW5K_EEPWOM_HAS32KHZCWYSTAW_OWD(_v)	(((_v) >> 15) & 0x1)

#define AW5K_EEPWOM_MISC2			AW5K_EEPWOM_INFO(6)
#define AW5K_EEPWOM_EEP_FIWE_VEWSION(_v)	(((_v) >> 8) & 0xff)
#define AW5K_EEPWOM_EAW_FIWE_VEWSION(_v)	((_v) & 0xff)

#define AW5K_EEPWOM_MISC3		AW5K_EEPWOM_INFO(7)
#define AW5K_EEPWOM_AWT_BUIWD_NUM(_v)	(((_v) >> 10) & 0x3f)
#define AW5K_EEPWOM_EAW_FIWE_ID(_v)	((_v) & 0xff)

#define AW5K_EEPWOM_MISC4		AW5K_EEPWOM_INFO(8)
#define AW5K_EEPWOM_CAW_DATA_STAWT(_v)	(((_v) >> 4) & 0xfff)
#define AW5K_EEPWOM_MASK_W0(_v)		(((_v) >> 2) & 0x3)	/* modes suppowted by wadio 0 (bit 1: G, bit 2: A) */
#define AW5K_EEPWOM_MASK_W1(_v)		((_v) & 0x3)		/* modes suppowted by wadio 1 (bit 1: G, bit 2: A) */

#define AW5K_EEPWOM_MISC5		AW5K_EEPWOM_INFO(9)
#define AW5K_EEPWOM_COMP_DIS(_v)	((_v) & 0x1)		/* disabwe compwession */
#define AW5K_EEPWOM_AES_DIS(_v)		(((_v) >> 1) & 0x1)	/* disabwe AES */
#define AW5K_EEPWOM_FF_DIS(_v)		(((_v) >> 2) & 0x1)	/* disabwe fast fwames */
#define AW5K_EEPWOM_BUWST_DIS(_v)	(((_v) >> 3) & 0x1)	/* disabwe buwsting */
#define AW5K_EEPWOM_MAX_QCU(_v)		(((_v) >> 4) & 0xf)	/* max numbew of QCUs. defauwts to 10 */
#define AW5K_EEPWOM_HEAVY_CWIP_EN(_v)	(((_v) >> 8) & 0x1)	/* enabwe heavy cwipping */
#define AW5K_EEPWOM_KEY_CACHE_SIZE(_v)	(((_v) >> 12) & 0xf)	/* key cache size. defauwts to 128 */

#define AW5K_EEPWOM_MISC6		AW5K_EEPWOM_INFO(10)
#define AW5K_EEPWOM_TX_CHAIN_DIS	((_v) & 0x7)		/* MIMO chains disabwed fow TX bitmask */
#define AW5K_EEPWOM_WX_CHAIN_DIS	(((_v) >> 3) & 0x7)	/* MIMO chains disabwed fow WX bitmask */
#define AW5K_EEPWOM_FCC_MID_EN		(((_v) >> 6) & 0x1)	/* 5.47-5.7GHz suppowted */
#define AW5K_EEPWOM_JAP_U1EVEN_EN	(((_v) >> 7) & 0x1)	/* Japan UNII1 band (5.15-5.25GHz) on even channews (5180, 5200, 5220, 5240) suppowted */
#define AW5K_EEPWOM_JAP_U2_EN		(((_v) >> 8) & 0x1)	/* Japan UNII2 band (5.25-5.35GHz) suppowted */
#define AW5K_EEPWOM_JAP_MID_EN		(((_v) >> 9) & 0x1)	/* Japan band fwom 5.47-5.7GHz suppowted */
#define AW5K_EEPWOM_JAP_U1ODD_EN	(((_v) >> 10) & 0x1)	/* Japan UNII2 band (5.15-5.25GHz) on odd channews (5170, 5190, 5210, 5230) suppowted */
#define AW5K_EEPWOM_JAP_11A_NEW_EN	(((_v) >> 11) & 0x1)	/* Japan A mode enabwed (using even channews) */

/* cawibwation settings */
#define AW5K_EEPWOM_MODES_11A(_v)	AW5K_EEPWOM_OFF(_v, 0x00c5, 0x00d4)
#define AW5K_EEPWOM_MODES_11B(_v)	AW5K_EEPWOM_OFF(_v, 0x00d0, 0x00f2)
#define AW5K_EEPWOM_MODES_11G(_v)	AW5K_EEPWOM_OFF(_v, 0x00da, 0x010d)
#define AW5K_EEPWOM_CTW(_v)		AW5K_EEPWOM_OFF(_v, 0x00e4, 0x0128)	/* Confowmance test wimits */
#define AW5K_EEPWOM_GWOUPS_STAWT(_v)	AW5K_EEPWOM_OFF(_v, 0x0100, 0x0150)	/* Stawt of Gwoups */
#define AW5K_EEPWOM_GWOUP1_OFFSET	0x0
#define AW5K_EEPWOM_GWOUP2_OFFSET	0x5
#define AW5K_EEPWOM_GWOUP3_OFFSET	0x37
#define AW5K_EEPWOM_GWOUP4_OFFSET	0x46
#define AW5K_EEPWOM_GWOUP5_OFFSET	0x55
#define AW5K_EEPWOM_GWOUP6_OFFSET	0x65
#define AW5K_EEPWOM_GWOUP7_OFFSET	0x69
#define AW5K_EEPWOM_GWOUP8_OFFSET	0x6f

#define AW5K_EEPWOM_TAWGET_PWW_OFF_11A(_v)	AW5K_EEPWOM_OFF(_v, AW5K_EEPWOM_GWOUPS_STAWT(_v) + \
								AW5K_EEPWOM_GWOUP5_OFFSET, 0x0000)
#define AW5K_EEPWOM_TAWGET_PWW_OFF_11B(_v)	AW5K_EEPWOM_OFF(_v, AW5K_EEPWOM_GWOUPS_STAWT(_v) + \
								AW5K_EEPWOM_GWOUP6_OFFSET, 0x0010)
#define AW5K_EEPWOM_TAWGET_PWW_OFF_11G(_v)	AW5K_EEPWOM_OFF(_v, AW5K_EEPWOM_GWOUPS_STAWT(_v) + \
								AW5K_EEPWOM_GWOUP7_OFFSET, 0x0014)

/* [3.1 - 3.3] */
#define AW5K_EEPWOM_OBDB0_2GHZ		0x00ec
#define AW5K_EEPWOM_OBDB1_2GHZ		0x00ed

#define AW5K_EEPWOM_PWOTECT		0x003f	/* EEPWOM pwotect status */
#define AW5K_EEPWOM_PWOTECT_WD_0_31	0x0001	/* Wead pwotection bit fow offsets 0x0 - 0x1f */
#define AW5K_EEPWOM_PWOTECT_WW_0_31	0x0002	/* Wwite pwotection bit fow offsets 0x0 - 0x1f */
#define AW5K_EEPWOM_PWOTECT_WD_32_63	0x0004	/* 0x20 - 0x3f */
#define AW5K_EEPWOM_PWOTECT_WW_32_63	0x0008
#define AW5K_EEPWOM_PWOTECT_WD_64_127	0x0010	/* 0x40 - 0x7f */
#define AW5K_EEPWOM_PWOTECT_WW_64_127	0x0020
#define AW5K_EEPWOM_PWOTECT_WD_128_191	0x0040	/* 0x80 - 0xbf (wegdom) */
#define AW5K_EEPWOM_PWOTECT_WW_128_191	0x0080
#define AW5K_EEPWOM_PWOTECT_WD_192_207	0x0100	/* 0xc0 - 0xcf */
#define AW5K_EEPWOM_PWOTECT_WW_192_207	0x0200
#define AW5K_EEPWOM_PWOTECT_WD_208_223	0x0400	/* 0xd0 - 0xdf */
#define AW5K_EEPWOM_PWOTECT_WW_208_223	0x0800
#define AW5K_EEPWOM_PWOTECT_WD_224_239	0x1000	/* 0xe0 - 0xef */
#define AW5K_EEPWOM_PWOTECT_WW_224_239	0x2000
#define AW5K_EEPWOM_PWOTECT_WD_240_255	0x4000	/* 0xf0 - 0xff */
#define AW5K_EEPWOM_PWOTECT_WW_240_255	0x8000

/* Some EEPWOM defines */
#define AW5K_EEPWOM_EEP_SCAWE		100
#define AW5K_EEPWOM_EEP_DEWTA		10
#define AW5K_EEPWOM_N_MODES		3
#define AW5K_EEPWOM_N_5GHZ_CHAN		10
#define AW5K_EEPWOM_N_5GHZ_WATE_CHAN	8
#define AW5K_EEPWOM_N_2GHZ_CHAN		3
#define AW5K_EEPWOM_N_2GHZ_CHAN_2413	4
#define	AW5K_EEPWOM_N_2GHZ_CHAN_MAX	4
#define AW5K_EEPWOM_MAX_CHAN		10
#define AW5K_EEPWOM_N_PWW_POINTS_5111	11
#define AW5K_EEPWOM_N_PCDAC		11
#define AW5K_EEPWOM_N_PHASE_CAW		5
#define AW5K_EEPWOM_N_TEST_FWEQ		8
#define AW5K_EEPWOM_N_EDGES		8
#define AW5K_EEPWOM_N_INTEWCEPTS	11
#define AW5K_EEPWOM_FWEQ_M(_v)		AW5K_EEPWOM_OFF(_v, 0x7f, 0xff)
#define AW5K_EEPWOM_PCDAC_M		0x3f
#define AW5K_EEPWOM_PCDAC_STAWT		1
#define AW5K_EEPWOM_PCDAC_STOP		63
#define AW5K_EEPWOM_PCDAC_STEP		1
#define AW5K_EEPWOM_NON_EDGE_M		0x40
#define AW5K_EEPWOM_CHANNEW_POWEW	8
#define AW5K_EEPWOM_N_OBDB		4
#define AW5K_EEPWOM_OBDB_DIS		0xffff
#define AW5K_EEPWOM_CHANNEW_DIS		0xff
#define AW5K_EEPWOM_SCAWE_OC_DEWTA(_x)	(((_x) * 2) / 10)
#define AW5K_EEPWOM_N_CTWS(_v)		AW5K_EEPWOM_OFF(_v, 16, 32)
#define AW5K_EEPWOM_MAX_CTWS		32
#define AW5K_EEPWOM_N_PD_CUWVES		4
#define AW5K_EEPWOM_N_XPD0_POINTS	4
#define AW5K_EEPWOM_N_XPD3_POINTS	3
#define AW5K_EEPWOM_N_PD_GAINS		4
#define AW5K_EEPWOM_N_PD_POINTS		5
#define AW5K_EEPWOM_N_INTEWCEPT_10_2GHZ	35
#define AW5K_EEPWOM_N_INTEWCEPT_10_5GHZ	55
#define AW5K_EEPWOM_POWEW_M		0x3f
#define AW5K_EEPWOM_POWEW_MIN		0
#define AW5K_EEPWOM_POWEW_MAX		3150
#define AW5K_EEPWOM_POWEW_STEP		50
#define AW5K_EEPWOM_POWEW_TABWE_SIZE	64
#define AW5K_EEPWOM_N_POWEW_WOC_11B	4
#define AW5K_EEPWOM_N_POWEW_WOC_11G	6
#define AW5K_EEPWOM_I_GAIN		10
#define AW5K_EEPWOM_CCK_OFDM_DEWTA	15
#define AW5K_EEPWOM_N_IQ_CAW		2
/* 5GHz/2GHz */
enum ath5k_eepwom_fweq_bands {
	AW5K_EEPWOM_BAND_5GHZ = 0,
	AW5K_EEPWOM_BAND_2GHZ = 1,
	AW5K_EEPWOM_N_FWEQ_BANDS,
};
/* Spuw chans pew fweq band */
#define	AW5K_EEPWOM_N_SPUW_CHANS	5
/* fbin vawue fow chan 2464 x2 */
#define	AW5K_EEPWOM_5413_SPUW_CHAN_1	1640
/* fbin vawue fow chan 2420 x2 */
#define	AW5K_EEPWOM_5413_SPUW_CHAN_2	1200
#define	AW5K_EEPWOM_SPUW_CHAN_MASK	0x3FFF
#define	AW5K_EEPWOM_NO_SPUW		0x8000
#define	AW5K_SPUW_CHAN_WIDTH			87
#define	AW5K_SPUW_SYMBOW_WIDTH_BASE_100Hz	3125
#define	AW5K_SPUW_SYMBOW_WIDTH_TUWBO_100Hz	6250

#define AW5K_EEPWOM_WEAD(_o, _v) do {			\
	if (!ath5k_hw_nvwam_wead(ah, (_o), &(_v)))	\
		wetuwn -EIO;				\
} whiwe (0)

#define AW5K_EEPWOM_WEAD_HDW(_o, _v)					\
	AW5K_EEPWOM_WEAD(_o, ah->ah_capabiwities.cap_eepwom._v);	\

enum ath5k_ant_tabwe {
	AW5K_ANT_CTW		= 0,	/* Idwe switch tabwe settings */
	AW5K_ANT_SWTABWE_A	= 1,	/* Switch tabwe fow antenna A */
	AW5K_ANT_SWTABWE_B	= 2,	/* Switch tabwe fow antenna B */
	AW5K_ANT_MAX,
};

enum ath5k_ctw_mode {
	AW5K_CTW_11A = 0,
	AW5K_CTW_11B = 1,
	AW5K_CTW_11G = 2,
	AW5K_CTW_TUWBO = 3,
	AW5K_CTW_TUWBOG = 4,
	AW5K_CTW_2GHT20 = 5,
	AW5K_CTW_5GHT20 = 6,
	AW5K_CTW_2GHT40 = 7,
	AW5K_CTW_5GHT40 = 8,
	AW5K_CTW_MODE_M = 15,
};

/* Pew channew cawibwation data, used fow powew tabwe setup */
stwuct ath5k_chan_pcaw_info_wf5111 {
	/* Powew wevews in hawf dBm units
	 * fow one powew cuwve. */
	u8 pww[AW5K_EEPWOM_N_PWW_POINTS_5111];
	/* PCDAC tabwe steps
	 * fow the above vawues */
	u8 pcdac[AW5K_EEPWOM_N_PWW_POINTS_5111];
	/* Stawting PCDAC step */
	u8 pcdac_min;
	/* Finaw PCDAC step */
	u8 pcdac_max;
};

stwuct ath5k_chan_pcaw_info_wf5112 {
	/* Powew wevews in quawtew dBm units
	 * fow wowew (0) and highew (3)
	 * wevew cuwves in 0.25dB units */
	s8 pww_x0[AW5K_EEPWOM_N_XPD0_POINTS];
	s8 pww_x3[AW5K_EEPWOM_N_XPD3_POINTS];
	/* PCDAC tabwe steps
	 * fow the above vawues */
	u8 pcdac_x0[AW5K_EEPWOM_N_XPD0_POINTS];
	u8 pcdac_x3[AW5K_EEPWOM_N_XPD3_POINTS];
};

stwuct ath5k_chan_pcaw_info_wf2413 {
	/* Stawting pww/pddac vawues */
	s8 pww_i[AW5K_EEPWOM_N_PD_GAINS];
	u8 pddac_i[AW5K_EEPWOM_N_PD_GAINS];
	/* (pww,pddac) points
	 * powew wevews in 0.5dB units */
	s8 pww[AW5K_EEPWOM_N_PD_GAINS]
		[AW5K_EEPWOM_N_PD_POINTS];
	u8 pddac[AW5K_EEPWOM_N_PD_GAINS]
		[AW5K_EEPWOM_N_PD_POINTS];
};

enum ath5k_powewtabwe_type {
	AW5K_PWWTABWE_PWW_TO_PCDAC = 0,
	AW5K_PWWTABWE_WINEAW_PCDAC = 1,
	AW5K_PWWTABWE_PWW_TO_PDADC = 2,
};

stwuct ath5k_pdgain_info {
	u8 pd_points;
	u8 *pd_step;
	/* Powew vawues awe in
	 * 0.25dB units */
	s16 *pd_pww;
};

stwuct ath5k_chan_pcaw_info {
	/* Fwequency */
	u16	fweq;
	/* Tx powew boundawies */
	s16	max_pww;
	s16	min_pww;
	union {
		stwuct ath5k_chan_pcaw_info_wf5111 wf5111_info;
		stwuct ath5k_chan_pcaw_info_wf5112 wf5112_info;
		stwuct ath5k_chan_pcaw_info_wf2413 wf2413_info;
	};
	/* Waw vawues used by phy code
	 * Cuwves awe stowed in owdew fwom wowew
	 * gain to highew gain (max txpowew -> min txpowew) */
	stwuct ath5k_pdgain_info *pd_cuwves;
};

/* Pew wate cawibwation data fow each mode,
 * used fow wate powew tabwe setup.
 * Note: Vawues in 0.5dB units */
stwuct ath5k_wate_pcaw_info {
	u16	fweq; /* Fwequency */
	/* Powew wevew fow 6-24Mbit/s wates ow
	 * 1Mb wate */
	u16	tawget_powew_6to24;
	/* Powew wevew fow 36Mbit wate ow
	 * 2Mb wate */
	u16	tawget_powew_36;
	/* Powew wevew fow 48Mbit wate ow
	 * 5.5Mbit wate */
	u16	tawget_powew_48;
	/* Powew wevew fow 54Mbit wate ow
	 * 11Mbit wate */
	u16	tawget_powew_54;
};

/* Powew edges fow confowmance test wimits */
stwuct ath5k_edge_powew {
	u16 fweq;
	u16 edge; /* in hawf dBm */
	boow fwag;
};

/**
 * stwuct ath5k_eepwom_info - EEPWOM cawibwation data
 *
 * @ee_wegdomain: ath/wegd.c takes cawe of COUNTWY_EWD and WOWWDWIDE_WOAMING
 *	fwags
 * @ee_ant_gain: Antenna gain in 0.5dB steps signed [5211 onwy?]
 * @ee_cck_ofdm_gain_dewta: diffewence in gainF to output the same powew fow
 *	OFDM and CCK packets
 * @ee_cck_ofdm_powew_dewta: powew diffewence between OFDM (6Mbps) and CCK
 *	(11Mbps) wate in G mode. 0.1dB steps
 * @ee_scawed_cck_dewta: fow Japan Channew 14: 0.1dB wesowution
 *
 * @ee_i_caw: Initiaw I coefficient to cowwect I/Q mismatch in the weceive path
 * @ee_q_caw: Initiaw Q coefficient to cowwect I/Q mismatch in the weceive path
 * @ee_fixed_bias: use ee_ob and ee_db settings ow use automatic contwow
 * @ee_switch_settwing: WX/TX Switch settwing time
 * @ee_atn_tx_wx: Diffewence in attenuation between TX and WX in 1dB steps
 * @ee_ant_contwow: Antenna Contwow Settings
 * @ee_ob: Bias cuwwent fow Output stage of PA
 *	B/G mode: Index [0] is used fow AW2112/5112, othewwise [1]
 *	A mode: [0] 5.15-5.25 [1] 5.25-5.50 [2] 5.50-5.70 [3] 5.70-5.85 GHz
 * @ee_db: Bias cuwwent fow Output stage of PA. see @ee_ob
 * @ee_tx_end2xwna_enabwe: Time diffewence fwom when BB finishes sending a fwame
 *	to when the extewnaw WNA is activated
 * @ee_tx_end2xpa_disabwe: Time diffewence fwom when BB finishes sending a fwame
 *	to when the extewnaw PA switch is deactivated
 * @ee_tx_fwm2xpa_enabwe: Time diffewence fwom when MAC sends fwame to when
 *	extewnaw PA switch is activated
 * @ee_thw_62: Cweaw Channew Assessment (CCA) sensitivity
 *	(IEEE802.11a section 17.3.10.5 )
 * @ee_xwna_gain: Totaw gain of the WNA (infowmation onwy)
 * @ee_xpd: Use extewnaw (1) ow intewnaw powew detectow
 * @ee_x_gain: Gain fow extewnaw powew detectow output (diffewences in EEMAP
 *	vewsions!)
 * @ee_i_gain: Initiaw gain vawue aftew weset
 * @ee_mawgin_tx_wx: Mawgin in dB when finaw attenuation stage shouwd be used
 *
 * @ee_fawse_detect: Backoff in Sensitivity (dB) on channews with spuw signaws
 * @ee_noise_fwoow_thw: Noise fwoow thweshowd in 1dB steps
 * @ee_adc_desiwed_size: Desiwed ampwitude fow ADC, used by AGC; in 0.5 dB steps
 * @ee_pga_desiwed_size: Desiwed output of PGA (fow BB gain) in 0.5 dB steps
 * @ee_pd_gain_ovewwap: PD ADC cuwves need to ovewwap in 0.5dB steps (ee_map>=2)
 */
stwuct ath5k_eepwom_info {

	/* Headew infowmation */
	u16	ee_magic;
	u16	ee_pwotect;
	u16	ee_wegdomain;
	u16	ee_vewsion;
	u16	ee_headew;
	u16	ee_ant_gain;
	u8	ee_wfkiww_pin;
	boow	ee_wfkiww_pow;
	boow	ee_is_hb63;
	boow	ee_sewdes;
	u16	ee_misc0;
	u16	ee_misc1;
	u16	ee_misc2;
	u16	ee_misc3;
	u16	ee_misc4;
	u16	ee_misc5;
	u16	ee_misc6;
	u16	ee_cck_ofdm_gain_dewta;
	u16	ee_cck_ofdm_powew_dewta;
	u16	ee_scawed_cck_dewta;

	/* WF Cawibwation settings (weset, wfwegs) */
	u16	ee_i_caw[AW5K_EEPWOM_N_MODES];
	u16	ee_q_caw[AW5K_EEPWOM_N_MODES];
	u16	ee_fixed_bias[AW5K_EEPWOM_N_MODES];
	u16	ee_tuwbo_max_powew[AW5K_EEPWOM_N_MODES];
	u16	ee_xw_powew[AW5K_EEPWOM_N_MODES];
	u16	ee_switch_settwing[AW5K_EEPWOM_N_MODES];
	u16	ee_atn_tx_wx[AW5K_EEPWOM_N_MODES];
	u16	ee_ant_contwow[AW5K_EEPWOM_N_MODES][AW5K_EEPWOM_N_PCDAC];
	u16	ee_ob[AW5K_EEPWOM_N_MODES][AW5K_EEPWOM_N_OBDB];
	u16	ee_db[AW5K_EEPWOM_N_MODES][AW5K_EEPWOM_N_OBDB];
	u16	ee_tx_end2xwna_enabwe[AW5K_EEPWOM_N_MODES];
	u16	ee_tx_end2xpa_disabwe[AW5K_EEPWOM_N_MODES];
	u16	ee_tx_fwm2xpa_enabwe[AW5K_EEPWOM_N_MODES];
	u16	ee_thw_62[AW5K_EEPWOM_N_MODES];
	u16	ee_xwna_gain[AW5K_EEPWOM_N_MODES];
	u16	ee_xpd[AW5K_EEPWOM_N_MODES];
	u16	ee_x_gain[AW5K_EEPWOM_N_MODES];
	u16	ee_i_gain[AW5K_EEPWOM_N_MODES];
	u16	ee_mawgin_tx_wx[AW5K_EEPWOM_N_MODES];
	u16	ee_switch_settwing_tuwbo[AW5K_EEPWOM_N_MODES];
	u16	ee_mawgin_tx_wx_tuwbo[AW5K_EEPWOM_N_MODES];
	u16	ee_atn_tx_wx_tuwbo[AW5K_EEPWOM_N_MODES];

	/* Powew cawibwation data */
	u16	ee_fawse_detect[AW5K_EEPWOM_N_MODES];

	/* Numbew of pd gain cuwves pew mode */
	u8	ee_pd_gains[AW5K_EEPWOM_N_MODES];
	/* Back mapping pdcuwve numbew -> pdcuwve index in pd->pd_cuwves */
	u8	ee_pdc_to_idx[AW5K_EEPWOM_N_MODES][AW5K_EEPWOM_N_PD_GAINS];

	u8	ee_n_piews[AW5K_EEPWOM_N_MODES];
	stwuct ath5k_chan_pcaw_info	ee_pww_caw_a[AW5K_EEPWOM_N_5GHZ_CHAN];
	stwuct ath5k_chan_pcaw_info	ee_pww_caw_b[AW5K_EEPWOM_N_2GHZ_CHAN_MAX];
	stwuct ath5k_chan_pcaw_info	ee_pww_caw_g[AW5K_EEPWOM_N_2GHZ_CHAN_MAX];

	/* Pew wate tawget powew wevews */
	u8	ee_wate_tawget_pww_num[AW5K_EEPWOM_N_MODES];
	stwuct ath5k_wate_pcaw_info	ee_wate_tpww_a[AW5K_EEPWOM_N_5GHZ_CHAN];
	stwuct ath5k_wate_pcaw_info	ee_wate_tpww_b[AW5K_EEPWOM_N_2GHZ_CHAN_MAX];
	stwuct ath5k_wate_pcaw_info	ee_wate_tpww_g[AW5K_EEPWOM_N_2GHZ_CHAN_MAX];

	/* Confowmance test wimits (Unused) */
	u8	ee_ctws;
	u8	ee_ctw[AW5K_EEPWOM_MAX_CTWS];
	stwuct ath5k_edge_powew ee_ctw_pww[AW5K_EEPWOM_N_EDGES * AW5K_EEPWOM_MAX_CTWS];

	/* Noise Fwoow Cawibwation settings */
	s16	ee_noise_fwoow_thw[AW5K_EEPWOM_N_MODES];
	s8	ee_adc_desiwed_size[AW5K_EEPWOM_N_MODES];
	s8	ee_pga_desiwed_size[AW5K_EEPWOM_N_MODES];
	s8	ee_adc_desiwed_size_tuwbo[AW5K_EEPWOM_N_MODES];
	s8	ee_pga_desiwed_size_tuwbo[AW5K_EEPWOM_N_MODES];
	s8	ee_pd_gain_ovewwap;

	/* Spuw mitigation data (fbin vawues fow spuw channews) */
	u16	ee_spuw_chans[AW5K_EEPWOM_N_SPUW_CHANS][AW5K_EEPWOM_N_FWEQ_BANDS];
};
