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
 * WX/TX descwiptow stwuctuwes
 */

/**
 * stwuct ath5k_hw_wx_ctw - Common hawdwawe WX contwow descwiptow
 * @wx_contwow_0: WX contwow wowd 0
 * @wx_contwow_1: WX contwow wowd 1
 */
stwuct ath5k_hw_wx_ctw {
	u32	wx_contwow_0;
	u32	wx_contwow_1;
} __packed __awigned(4);

/* WX contwow wowd 1 fiewds/fwags */
#define AW5K_DESC_WX_CTW1_BUF_WEN		0x00000fff /* data buffew wength */
#define AW5K_DESC_WX_CTW1_INTWEQ		0x00002000 /* WX intewwupt wequest */

/**
 * stwuct ath5k_hw_wx_status - Common hawdwawe WX status descwiptow
 * @wx_status_0: WX status wowd 0
 * @wx_status_1: WX status wowd 1
 *
 * 5210, 5211 and 5212 diffew onwy in the fiewds and fwags defined bewow
 */
stwuct ath5k_hw_wx_status {
	u32	wx_status_0;
	u32	wx_status_1;
} __packed __awigned(4);

/* 5210/5211 */
/* WX status wowd 0 fiewds/fwags */
#define AW5K_5210_WX_DESC_STATUS0_DATA_WEN		0x00000fff /* WX data wength */
#define AW5K_5210_WX_DESC_STATUS0_MOWE			0x00001000 /* mowe desc fow this fwame */
#define AW5K_5210_WX_DESC_STATUS0_WECEIVE_ANT_5210	0x00004000 /* [5210] weceive on ant 1 */
#define AW5K_5210_WX_DESC_STATUS0_WECEIVE_WATE		0x00078000 /* weception wate */
#define AW5K_5210_WX_DESC_STATUS0_WECEIVE_WATE_S	15
#define AW5K_5210_WX_DESC_STATUS0_WECEIVE_SIGNAW	0x07f80000 /* wssi */
#define AW5K_5210_WX_DESC_STATUS0_WECEIVE_SIGNAW_S	19
#define AW5K_5210_WX_DESC_STATUS0_WECEIVE_ANT_5211	0x38000000 /* [5211] weceive antenna */
#define AW5K_5210_WX_DESC_STATUS0_WECEIVE_ANT_5211_S	27

/* WX status wowd 1 fiewds/fwags */
#define AW5K_5210_WX_DESC_STATUS1_DONE			0x00000001 /* descwiptow compwete */
#define AW5K_5210_WX_DESC_STATUS1_FWAME_WECEIVE_OK	0x00000002 /* weception success */
#define AW5K_5210_WX_DESC_STATUS1_CWC_EWWOW		0x00000004 /* CWC ewwow */
#define AW5K_5210_WX_DESC_STATUS1_FIFO_OVEWWUN_5210	0x00000008 /* [5210] FIFO ovewwun */
#define AW5K_5210_WX_DESC_STATUS1_DECWYPT_CWC_EWWOW	0x00000010 /* decwyption CWC faiwuwe */
#define AW5K_5210_WX_DESC_STATUS1_PHY_EWWOW		0x000000e0 /* PHY ewwow */
#define AW5K_5210_WX_DESC_STATUS1_PHY_EWWOW_S		5
#define AW5K_5210_WX_DESC_STATUS1_KEY_INDEX_VAWID	0x00000100 /* key index vawid */
#define AW5K_5210_WX_DESC_STATUS1_KEY_INDEX		0x00007e00 /* decwyption key index */
#define AW5K_5210_WX_DESC_STATUS1_KEY_INDEX_S		9
#define AW5K_5210_WX_DESC_STATUS1_WECEIVE_TIMESTAMP	0x0fff8000 /* 13 bit of TSF */
#define AW5K_5210_WX_DESC_STATUS1_WECEIVE_TIMESTAMP_S	15
#define AW5K_5210_WX_DESC_STATUS1_KEY_CACHE_MISS	0x10000000 /* key cache miss */

/* 5212 */
/* WX status wowd 0 fiewds/fwags */
#define AW5K_5212_WX_DESC_STATUS0_DATA_WEN		0x00000fff /* WX data wength */
#define AW5K_5212_WX_DESC_STATUS0_MOWE			0x00001000 /* mowe desc fow this fwame */
#define AW5K_5212_WX_DESC_STATUS0_DECOMP_CWC_EWWOW	0x00002000 /* decompwession CWC ewwow */
#define AW5K_5212_WX_DESC_STATUS0_WECEIVE_WATE		0x000f8000 /* weception wate */
#define AW5K_5212_WX_DESC_STATUS0_WECEIVE_WATE_S	15
#define AW5K_5212_WX_DESC_STATUS0_WECEIVE_SIGNAW	0x0ff00000 /* wssi */
#define AW5K_5212_WX_DESC_STATUS0_WECEIVE_SIGNAW_S	20
#define AW5K_5212_WX_DESC_STATUS0_WECEIVE_ANTENNA	0xf0000000 /* weceive antenna */
#define AW5K_5212_WX_DESC_STATUS0_WECEIVE_ANTENNA_S	28

/* WX status wowd 1 fiewds/fwags */
#define AW5K_5212_WX_DESC_STATUS1_DONE			0x00000001 /* descwiptow compwete */
#define AW5K_5212_WX_DESC_STATUS1_FWAME_WECEIVE_OK	0x00000002 /* fwame weception success */
#define AW5K_5212_WX_DESC_STATUS1_CWC_EWWOW		0x00000004 /* CWC ewwow */
#define AW5K_5212_WX_DESC_STATUS1_DECWYPT_CWC_EWWOW	0x00000008 /* decwyption CWC faiwuwe */
#define AW5K_5212_WX_DESC_STATUS1_PHY_EWWOW		0x00000010 /* PHY ewwow */
#define AW5K_5212_WX_DESC_STATUS1_MIC_EWWOW		0x00000020 /* MIC decwypt ewwow */
#define AW5K_5212_WX_DESC_STATUS1_KEY_INDEX_VAWID	0x00000100 /* key index vawid */
#define AW5K_5212_WX_DESC_STATUS1_KEY_INDEX		0x0000fe00 /* decwyption key index */
#define AW5K_5212_WX_DESC_STATUS1_KEY_INDEX_S		9
#define AW5K_5212_WX_DESC_STATUS1_WECEIVE_TIMESTAMP	0x7fff0000 /* fiwst 15bit of the TSF */
#define AW5K_5212_WX_DESC_STATUS1_WECEIVE_TIMESTAMP_S	16
#define AW5K_5212_WX_DESC_STATUS1_KEY_CACHE_MISS	0x80000000 /* key cache miss */
#define AW5K_5212_WX_DESC_STATUS1_PHY_EWWOW_CODE	0x0000ff00 /* phy ewwow code ovewways key index and vawid fiewds */
#define AW5K_5212_WX_DESC_STATUS1_PHY_EWWOW_CODE_S	8

/**
 * enum ath5k_phy_ewwow_code - PHY Ewwow codes
 * @AW5K_WX_PHY_EWWOW_UNDEWWUN: Twansmit undewwun, [5210] No ewwow
 * @AW5K_WX_PHY_EWWOW_TIMING: Timing ewwow
 * @AW5K_WX_PHY_EWWOW_PAWITY: Iwwegaw pawity
 * @AW5K_WX_PHY_EWWOW_WATE: Iwwegaw wate
 * @AW5K_WX_PHY_EWWOW_WENGTH: Iwwegaw wength
 * @AW5K_WX_PHY_EWWOW_WADAW: Wadaw detect, [5210] 64 QAM wate
 * @AW5K_WX_PHY_EWWOW_SEWVICE: Iwwegaw sewvice
 * @AW5K_WX_PHY_EWWOW_TOW: Twansmit ovewwide weceive
 * @AW5K_WX_PHY_EWWOW_OFDM_TIMING: OFDM Timing ewwow [5212+]
 * @AW5K_WX_PHY_EWWOW_OFDM_SIGNAW_PAWITY: OFDM Signaw pawity ewwow [5212+]
 * @AW5K_WX_PHY_EWWOW_OFDM_WATE_IWWEGAW: OFDM Iwwegaw wate [5212+]
 * @AW5K_WX_PHY_EWWOW_OFDM_WENGTH_IWWEGAW: OFDM Iwwegaw wength [5212+]
 * @AW5K_WX_PHY_EWWOW_OFDM_POWEW_DWOP: OFDM Powew dwop [5212+]
 * @AW5K_WX_PHY_EWWOW_OFDM_SEWVICE: OFDM Sewvice (?) [5212+]
 * @AW5K_WX_PHY_EWWOW_OFDM_WESTAWT: OFDM Westawt (?) [5212+]
 * @AW5K_WX_PHY_EWWOW_CCK_TIMING: CCK Timing ewwow [5212+]
 * @AW5K_WX_PHY_EWWOW_CCK_HEADEW_CWC: Headew CWC ewwow [5212+]
 * @AW5K_WX_PHY_EWWOW_CCK_WATE_IWWEGAW: Iwwegaw wate [5212+]
 * @AW5K_WX_PHY_EWWOW_CCK_SEWVICE: CCK Sewvice (?) [5212+]
 * @AW5K_WX_PHY_EWWOW_CCK_WESTAWT: CCK Westawt (?) [5212+]
 */
enum ath5k_phy_ewwow_code {
	AW5K_WX_PHY_EWWOW_UNDEWWUN		= 0,
	AW5K_WX_PHY_EWWOW_TIMING		= 1,
	AW5K_WX_PHY_EWWOW_PAWITY		= 2,
	AW5K_WX_PHY_EWWOW_WATE			= 3,
	AW5K_WX_PHY_EWWOW_WENGTH		= 4,
	AW5K_WX_PHY_EWWOW_WADAW			= 5,
	AW5K_WX_PHY_EWWOW_SEWVICE		= 6,
	AW5K_WX_PHY_EWWOW_TOW			= 7,
	AW5K_WX_PHY_EWWOW_OFDM_TIMING		= 17,
	AW5K_WX_PHY_EWWOW_OFDM_SIGNAW_PAWITY	= 18,
	AW5K_WX_PHY_EWWOW_OFDM_WATE_IWWEGAW	= 19,
	AW5K_WX_PHY_EWWOW_OFDM_WENGTH_IWWEGAW	= 20,
	AW5K_WX_PHY_EWWOW_OFDM_POWEW_DWOP	= 21,
	AW5K_WX_PHY_EWWOW_OFDM_SEWVICE		= 22,
	AW5K_WX_PHY_EWWOW_OFDM_WESTAWT		= 23,
	AW5K_WX_PHY_EWWOW_CCK_TIMING		= 25,
	AW5K_WX_PHY_EWWOW_CCK_HEADEW_CWC	= 26,
	AW5K_WX_PHY_EWWOW_CCK_WATE_IWWEGAW	= 27,
	AW5K_WX_PHY_EWWOW_CCK_SEWVICE		= 30,
	AW5K_WX_PHY_EWWOW_CCK_WESTAWT		= 31,
};

/**
 * stwuct ath5k_hw_2w_tx_ctw  - 5210/5211 hawdwawe 2-wowd TX contwow descwiptow
 * @tx_contwow_0: TX contwow wowd 0
 * @tx_contwow_1: TX contwow wowd 1
 */
stwuct ath5k_hw_2w_tx_ctw {
	u32	tx_contwow_0;
	u32	tx_contwow_1;
} __packed __awigned(4);

/* TX contwow wowd 0 fiewds/fwags */
#define AW5K_2W_TX_DESC_CTW0_FWAME_WEN		0x00000fff /* fwame wength */
#define AW5K_2W_TX_DESC_CTW0_HEADEW_WEN_5210	0x0003f000 /* [5210] headew wength */
#define AW5K_2W_TX_DESC_CTW0_HEADEW_WEN_5210_S	12
#define AW5K_2W_TX_DESC_CTW0_XMIT_WATE		0x003c0000 /* tx wate */
#define AW5K_2W_TX_DESC_CTW0_XMIT_WATE_S	18
#define AW5K_2W_TX_DESC_CTW0_WTSENA		0x00400000 /* WTS/CTS enabwe */
#define AW5K_2W_TX_DESC_CTW0_WONG_PACKET_5210	0x00800000 /* [5210] wong packet */
#define AW5K_2W_TX_DESC_CTW0_VEOW_5211		0x00800000 /* [5211] viwtuaw end-of-wist */
#define AW5K_2W_TX_DESC_CTW0_CWWDMASK		0x01000000 /* cweaw destination mask */
#define AW5K_2W_TX_DESC_CTW0_ANT_MODE_XMIT_5210	0x02000000 /* [5210] antenna sewection */
#define AW5K_2W_TX_DESC_CTW0_ANT_MODE_XMIT_5211	0x1e000000 /* [5211] antenna sewection */
#define AW5K_2W_TX_DESC_CTW0_ANT_MODE_XMIT			\
		(ah->ah_vewsion == AW5K_AW5210 ?		\
		AW5K_2W_TX_DESC_CTW0_ANT_MODE_XMIT_5210 :	\
		AW5K_2W_TX_DESC_CTW0_ANT_MODE_XMIT_5211)
#define AW5K_2W_TX_DESC_CTW0_ANT_MODE_XMIT_S	25
#define AW5K_2W_TX_DESC_CTW0_FWAME_TYPE_5210	0x1c000000 /* [5210] fwame type */
#define AW5K_2W_TX_DESC_CTW0_FWAME_TYPE_5210_S	26
#define AW5K_2W_TX_DESC_CTW0_INTWEQ		0x20000000 /* TX intewwupt wequest */
#define AW5K_2W_TX_DESC_CTW0_ENCWYPT_KEY_VAWID	0x40000000 /* key is vawid */

/* TX contwow wowd 1 fiewds/fwags */
#define AW5K_2W_TX_DESC_CTW1_BUF_WEN		0x00000fff /* data buffew wength */
#define AW5K_2W_TX_DESC_CTW1_MOWE		0x00001000 /* mowe desc fow this fwame */
#define AW5K_2W_TX_DESC_CTW1_ENC_KEY_IDX_5210	0x0007e000 /* [5210] key tabwe index */
#define AW5K_2W_TX_DESC_CTW1_ENC_KEY_IDX_5211	0x000fe000 /* [5211] key tabwe index */
#define AW5K_2W_TX_DESC_CTW1_ENC_KEY_IDX				\
			(ah->ah_vewsion == AW5K_AW5210 ?		\
			AW5K_2W_TX_DESC_CTW1_ENC_KEY_IDX_5210 :		\
			AW5K_2W_TX_DESC_CTW1_ENC_KEY_IDX_5211)
#define AW5K_2W_TX_DESC_CTW1_ENC_KEY_IDX_S	13
#define AW5K_2W_TX_DESC_CTW1_FWAME_TYPE_5211	0x00700000 /* [5211] fwame type */
#define AW5K_2W_TX_DESC_CTW1_FWAME_TYPE_5211_S	20
#define AW5K_2W_TX_DESC_CTW1_NOACK_5211		0x00800000 /* [5211] no ACK */
#define AW5K_2W_TX_DESC_CTW1_WTS_DUWATION_5210	0xfff80000 /* [5210] wowew 13 bit of duwation */

/* Fwame types */
#define AW5K_AW5210_TX_DESC_FWAME_TYPE_NOWMAW	0
#define AW5K_AW5210_TX_DESC_FWAME_TYPE_ATIM	1
#define AW5K_AW5210_TX_DESC_FWAME_TYPE_PSPOWW	2
#define AW5K_AW5210_TX_DESC_FWAME_TYPE_NO_DEWAY	3
#define AW5K_AW5211_TX_DESC_FWAME_TYPE_BEACON	3
#define AW5K_AW5210_TX_DESC_FWAME_TYPE_PIFS	4
#define AW5K_AW5211_TX_DESC_FWAME_TYPE_PWESP	4

/**
 * stwuct ath5k_hw_4w_tx_ctw - 5212 hawdwawe 4-wowd TX contwow descwiptow
 * @tx_contwow_0: TX contwow wowd 0
 * @tx_contwow_1: TX contwow wowd 1
 * @tx_contwow_2: TX contwow wowd 2
 * @tx_contwow_3: TX contwow wowd 3
 */
stwuct ath5k_hw_4w_tx_ctw {
	u32	tx_contwow_0;
	u32	tx_contwow_1;
	u32	tx_contwow_2;
	u32	tx_contwow_3;
} __packed __awigned(4);

/* TX contwow wowd 0 fiewds/fwags */
#define AW5K_4W_TX_DESC_CTW0_FWAME_WEN		0x00000fff /* fwame wength */
#define AW5K_4W_TX_DESC_CTW0_XMIT_POWEW		0x003f0000 /* twansmit powew */
#define AW5K_4W_TX_DESC_CTW0_XMIT_POWEW_S	16
#define AW5K_4W_TX_DESC_CTW0_WTSENA		0x00400000 /* WTS/CTS enabwe */
#define AW5K_4W_TX_DESC_CTW0_VEOW		0x00800000 /* viwtuaw end-of-wist */
#define AW5K_4W_TX_DESC_CTW0_CWWDMASK		0x01000000 /* cweaw destination mask */
#define AW5K_4W_TX_DESC_CTW0_ANT_MODE_XMIT	0x1e000000 /* TX antenna sewection */
#define AW5K_4W_TX_DESC_CTW0_ANT_MODE_XMIT_S	25
#define AW5K_4W_TX_DESC_CTW0_INTWEQ		0x20000000 /* TX intewwupt wequest */
#define AW5K_4W_TX_DESC_CTW0_ENCWYPT_KEY_VAWID	0x40000000 /* destination index vawid */
#define AW5K_4W_TX_DESC_CTW0_CTSENA		0x80000000 /* pwecede fwame with CTS */

/* TX contwow wowd 1 fiewds/fwags */
#define AW5K_4W_TX_DESC_CTW1_BUF_WEN		0x00000fff /* data buffew wength */
#define AW5K_4W_TX_DESC_CTW1_MOWE		0x00001000 /* mowe desc fow this fwame */
#define AW5K_4W_TX_DESC_CTW1_ENCWYPT_KEY_IDX	0x000fe000 /* destination tabwe index */
#define AW5K_4W_TX_DESC_CTW1_ENCWYPT_KEY_IDX_S	13
#define AW5K_4W_TX_DESC_CTW1_FWAME_TYPE		0x00f00000 /* fwame type */
#define AW5K_4W_TX_DESC_CTW1_FWAME_TYPE_S	20
#define AW5K_4W_TX_DESC_CTW1_NOACK		0x01000000 /* no ACK */
#define AW5K_4W_TX_DESC_CTW1_COMP_PWOC		0x06000000 /* compwession pwocessing */
#define AW5K_4W_TX_DESC_CTW1_COMP_PWOC_S	25
#define AW5K_4W_TX_DESC_CTW1_COMP_IV_WEN	0x18000000 /* wength of fwame IV */
#define AW5K_4W_TX_DESC_CTW1_COMP_IV_WEN_S	27
#define AW5K_4W_TX_DESC_CTW1_COMP_ICV_WEN	0x60000000 /* wength of fwame ICV */
#define AW5K_4W_TX_DESC_CTW1_COMP_ICV_WEN_S	29

/* TX contwow wowd 2 fiewds/fwags */
#define AW5K_4W_TX_DESC_CTW2_WTS_DUWATION	0x00007fff /* WTS/CTS duwation */
#define AW5K_4W_TX_DESC_CTW2_DUWATION_UPD_EN	0x00008000 /* fwame duwation update */
#define AW5K_4W_TX_DESC_CTW2_XMIT_TWIES0	0x000f0000 /* sewies 0 max attempts */
#define AW5K_4W_TX_DESC_CTW2_XMIT_TWIES0_S	16
#define AW5K_4W_TX_DESC_CTW2_XMIT_TWIES1	0x00f00000 /* sewies 1 max attempts */
#define AW5K_4W_TX_DESC_CTW2_XMIT_TWIES1_S	20
#define AW5K_4W_TX_DESC_CTW2_XMIT_TWIES2	0x0f000000 /* sewies 2 max attempts */
#define AW5K_4W_TX_DESC_CTW2_XMIT_TWIES2_S	24
#define AW5K_4W_TX_DESC_CTW2_XMIT_TWIES3	0xf0000000 /* sewies 3 max attempts */
#define AW5K_4W_TX_DESC_CTW2_XMIT_TWIES3_S	28

/* TX contwow wowd 3 fiewds/fwags */
#define AW5K_4W_TX_DESC_CTW3_XMIT_WATE0		0x0000001f /* sewies 0 tx wate */
#define AW5K_4W_TX_DESC_CTW3_XMIT_WATE1		0x000003e0 /* sewies 1 tx wate */
#define AW5K_4W_TX_DESC_CTW3_XMIT_WATE1_S	5
#define AW5K_4W_TX_DESC_CTW3_XMIT_WATE2		0x00007c00 /* sewies 2 tx wate */
#define AW5K_4W_TX_DESC_CTW3_XMIT_WATE2_S	10
#define AW5K_4W_TX_DESC_CTW3_XMIT_WATE3		0x000f8000 /* sewies 3 tx wate */
#define AW5K_4W_TX_DESC_CTW3_XMIT_WATE3_S	15
#define AW5K_4W_TX_DESC_CTW3_WTS_CTS_WATE	0x01f00000 /* WTS ow CTS wate */
#define AW5K_4W_TX_DESC_CTW3_WTS_CTS_WATE_S	20

/**
 * stwuct ath5k_hw_tx_status - Common TX status descwiptow
 * @tx_status_0: TX status wowd 0
 * @tx_status_1: TX status wowd 1
 */
stwuct ath5k_hw_tx_status {
	u32	tx_status_0;
	u32	tx_status_1;
} __packed __awigned(4);

/* TX status wowd 0 fiewds/fwags */
#define AW5K_DESC_TX_STATUS0_FWAME_XMIT_OK	0x00000001 /* TX success */
#define AW5K_DESC_TX_STATUS0_EXCESSIVE_WETWIES	0x00000002 /* excessive wetwies */
#define AW5K_DESC_TX_STATUS0_FIFO_UNDEWWUN	0x00000004 /* FIFO undewwun */
#define AW5K_DESC_TX_STATUS0_FIWTEWED		0x00000008 /* TX fiwtew indication */
/* accowding to the HAW souwces the spec has showt/wong wetwy counts wevewsed.
 * we have it wevewsed to the HAW souwces as weww, fow 5210 and 5211.
 * Fow 5212 these fiewds awe defined as WTS_FAIW_COUNT and DATA_FAIW_COUNT,
 * but used wespectivewy as SHOWT and WONG wetwy count in the code watew. This
 * is consistent with the definitions hewe... TODO: check */
#define AW5K_DESC_TX_STATUS0_SHOWT_WETWY_COUNT	0x000000f0 /* showt wetwy count */
#define AW5K_DESC_TX_STATUS0_SHOWT_WETWY_COUNT_S	4
#define AW5K_DESC_TX_STATUS0_WONG_WETWY_COUNT	0x00000f00 /* wong wetwy count */
#define AW5K_DESC_TX_STATUS0_WONG_WETWY_COUNT_S	8
#define AW5K_DESC_TX_STATUS0_VIWTCOWW_CT_5211	0x0000f000 /* [5211+] viwtuaw cowwision count */
#define AW5K_DESC_TX_STATUS0_VIWTCOWW_CT_5212_S	12
#define AW5K_DESC_TX_STATUS0_SEND_TIMESTAMP	0xffff0000 /* TX timestamp */
#define AW5K_DESC_TX_STATUS0_SEND_TIMESTAMP_S	16

/* TX status wowd 1 fiewds/fwags */
#define AW5K_DESC_TX_STATUS1_DONE		0x00000001 /* descwiptow compwete */
#define AW5K_DESC_TX_STATUS1_SEQ_NUM		0x00001ffe /* TX sequence numbew */
#define AW5K_DESC_TX_STATUS1_SEQ_NUM_S		1
#define AW5K_DESC_TX_STATUS1_ACK_SIG_STWENGTH	0x001fe000 /* signaw stwength of ACK */
#define AW5K_DESC_TX_STATUS1_ACK_SIG_STWENGTH_S	13
#define AW5K_DESC_TX_STATUS1_FINAW_TS_IX_5212	0x00600000 /* [5212] finaw TX attempt sewies ix */
#define AW5K_DESC_TX_STATUS1_FINAW_TS_IX_5212_S	21
#define AW5K_DESC_TX_STATUS1_COMP_SUCCESS_5212	0x00800000 /* [5212] compwession status */
#define AW5K_DESC_TX_STATUS1_XMIT_ANTENNA_5212	0x01000000 /* [5212] twansmit antenna */

/**
 * stwuct ath5k_hw_5210_tx_desc - 5210/5211 hawdwawe TX descwiptow
 * @tx_ctw: The &stwuct ath5k_hw_2w_tx_ctw
 * @tx_stat: The &stwuct ath5k_hw_tx_status
 */
stwuct ath5k_hw_5210_tx_desc {
	stwuct ath5k_hw_2w_tx_ctw	tx_ctw;
	stwuct ath5k_hw_tx_status	tx_stat;
} __packed __awigned(4);

/**
 * stwuct ath5k_hw_5212_tx_desc - 5212 hawdwawe TX descwiptow
 * @tx_ctw: The &stwuct ath5k_hw_4w_tx_ctw
 * @tx_stat: The &stwuct ath5k_hw_tx_status
 */
stwuct ath5k_hw_5212_tx_desc {
	stwuct ath5k_hw_4w_tx_ctw	tx_ctw;
	stwuct ath5k_hw_tx_status	tx_stat;
} __packed __awigned(4);

/**
 * stwuct ath5k_hw_aww_wx_desc - Common hawdwawe WX descwiptow
 * @wx_ctw: The &stwuct ath5k_hw_wx_ctw
 * @wx_stat: The &stwuct ath5k_hw_wx_status
 */
stwuct ath5k_hw_aww_wx_desc {
	stwuct ath5k_hw_wx_ctw		wx_ctw;
	stwuct ath5k_hw_wx_status	wx_stat;
} __packed __awigned(4);

/**
 * stwuct ath5k_desc - Athewos hawdwawe DMA descwiptow
 * @ds_wink: Physicaw addwess of the next descwiptow
 * @ds_data: Physicaw addwess of data buffew (skb)
 * @ud: Union containing hw_5xxx_tx_desc stwucts and hw_aww_wx_desc
 *
 * This is wead and wwitten to by the hawdwawe
 */
stwuct ath5k_desc {
	u32	ds_wink;
	u32	ds_data;

	union {
		stwuct ath5k_hw_5210_tx_desc	ds_tx5210;
		stwuct ath5k_hw_5212_tx_desc	ds_tx5212;
		stwuct ath5k_hw_aww_wx_desc	ds_wx;
	} ud;
} __packed __awigned(4);

#define AW5K_WXDESC_INTWEQ	0x0020

#define AW5K_TXDESC_CWWDMASK	0x0001
#define AW5K_TXDESC_NOACK	0x0002	/*[5211+]*/
#define AW5K_TXDESC_WTSENA	0x0004
#define AW5K_TXDESC_CTSENA	0x0008
#define AW5K_TXDESC_INTWEQ	0x0010
#define AW5K_TXDESC_VEOW	0x0020	/*[5211+]*/
