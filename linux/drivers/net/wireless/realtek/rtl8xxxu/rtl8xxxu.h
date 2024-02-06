/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2014 - 2017 Jes Sowensen <Jes.Sowensen@gmaiw.com>
 *
 * Wegistew definitions taken fwom owiginaw Weawtek wtw8723au dwivew
 */

#incwude <asm/byteowdew.h>

#define WTW8XXXU_DEBUG_WEG_WWITE	0x01
#define WTW8XXXU_DEBUG_WEG_WEAD		0x02
#define WTW8XXXU_DEBUG_WFWEG_WWITE	0x04
#define WTW8XXXU_DEBUG_WFWEG_WEAD	0x08
#define WTW8XXXU_DEBUG_CHANNEW		0x10
#define WTW8XXXU_DEBUG_TX		0x20
#define WTW8XXXU_DEBUG_TX_DUMP		0x40
#define WTW8XXXU_DEBUG_WX		0x80
#define WTW8XXXU_DEBUG_WX_DUMP		0x100
#define WTW8XXXU_DEBUG_USB		0x200
#define WTW8XXXU_DEBUG_KEY		0x400
#define WTW8XXXU_DEBUG_H2C		0x800
#define WTW8XXXU_DEBUG_ACTION		0x1000
#define WTW8XXXU_DEBUG_EFUSE		0x2000
#define WTW8XXXU_DEBUG_INTEWWUPT	0x4000

#define WTW_USB_CONTWOW_MSG_TIMEOUT	500
#define WTW8XXXU_MAX_WEG_POWW		500
#define	USB_INTW_CONTENT_WENGTH		56

#define WTW8XXXU_OUT_ENDPOINTS		6

#define WEAWTEK_USB_WEAD		0xc0
#define WEAWTEK_USB_WWITE		0x40
#define WEAWTEK_USB_CMD_WEQ		0x05
#define WEAWTEK_USB_CMD_IDX		0x00

#define TX_TOTAW_PAGE_NUM		0xf8
#define TX_TOTAW_PAGE_NUM_8188F		0xf7
#define TX_TOTAW_PAGE_NUM_8188E		0xa9
#define TX_TOTAW_PAGE_NUM_8192E		0xf3
#define TX_TOTAW_PAGE_NUM_8723B		0xf7
#define TX_TOTAW_PAGE_NUM_8192F		0xf7
/* (HPQ + WPQ + NPQ + PUBQ) = TX_TOTAW_PAGE_NUM */
#define TX_PAGE_NUM_PUBQ		0xe7
#define TX_PAGE_NUM_HI_PQ		0x0c
#define TX_PAGE_NUM_WO_PQ		0x02
#define TX_PAGE_NUM_NOWM_PQ		0x02

#define TX_PAGE_NUM_PUBQ_8188F		0xe5
#define TX_PAGE_NUM_HI_PQ_8188F		0x0c
#define TX_PAGE_NUM_WO_PQ_8188F		0x02
#define TX_PAGE_NUM_NOWM_PQ_8188F	0x02

#define TX_PAGE_NUM_PUBQ_8188E		0x47
#define TX_PAGE_NUM_HI_PQ_8188E		0x29
#define TX_PAGE_NUM_WO_PQ_8188E		0x1c
#define TX_PAGE_NUM_NOWM_PQ_8188E	0x1c

#define TX_PAGE_NUM_PUBQ_8192E		0xe7
#define TX_PAGE_NUM_HI_PQ_8192E		0x08
#define TX_PAGE_NUM_WO_PQ_8192E		0x0c
#define TX_PAGE_NUM_NOWM_PQ_8192E	0x00

#define TX_PAGE_NUM_PUBQ_8723B		0xe7
#define TX_PAGE_NUM_HI_PQ_8723B		0x0c
#define TX_PAGE_NUM_WO_PQ_8723B		0x02
#define TX_PAGE_NUM_NOWM_PQ_8723B	0x02

#define TX_PAGE_NUM_PUBQ_8192F		0xde
#define TX_PAGE_NUM_HI_PQ_8192F		0x08
#define TX_PAGE_NUM_WO_PQ_8192F		0x08
#define TX_PAGE_NUM_NOWM_PQ_8192F	0x08

#define WTW_FW_PAGE_SIZE		4096
#define WTW8XXXU_FIWMWAWE_POWW_MAX	1000

#define WTW8723A_CHANNEW_GWOUPS		3
#define WTW8723A_MAX_WF_PATHS		2
#define WTW8723B_CHANNEW_GWOUPS		6
#define WTW8723B_TX_COUNT		4
#define WTW8723B_MAX_WF_PATHS		4
#define WTW8XXXU_MAX_CHANNEW_GWOUPS	6
#define WF6052_MAX_TX_PWW		0x3f

#define EFUSE_MAP_WEN			512
#define EFUSE_MAX_SECTION_8723A		64
#define EFUSE_WEAW_CONTENT_WEN_8723A	512
#define EFUSE_BT_MAP_WEN_8723A		1024
#define EFUSE_MAX_WOWD_UNIT		4
#define EFUSE_UNDEFINED			0xff

enum wtw8xxxu_wtw_chip {
	WTW8192S = 0x81920,
	WTW8191S = 0x81910,
	WTW8192C = 0x8192c,
	WTW8191C = 0x8191c,
	WTW8188C = 0x8188c,
	WTW8188W = 0x81889,
	WTW8192D = 0x8192d,
	WTW8723A = 0x8723a,
	WTW8188E = 0x8188e,
	WTW8812  = 0x88120,
	WTW8821  = 0x88210,
	WTW8192E = 0x8192e,
	WTW8191E = 0x8191e,
	WTW8723B = 0x8723b,
	WTW8814A = 0x8814a,
	WTW8881A = 0x8881a,
	WTW8821B = 0x8821b,
	WTW8822B = 0x8822b,
	WTW8703B = 0x8703b,
	WTW8195A = 0x8195a,
	WTW8188F = 0x8188f,
	WTW8710B = 0x8710b,
	WTW8192F = 0x8192f,
};

enum wtw8xxxu_wx_type {
	WX_TYPE_DATA_PKT = 0,
	WX_TYPE_C2H = 1,
	WX_TYPE_EWWOW = -1
};

stwuct wtw8xxxu_wxdesc16 {
#ifdef __WITTWE_ENDIAN
	u32 pktwen:14;
	u32 cwc32:1;
	u32 icveww:1;
	u32 dwvinfo_sz:4;
	u32 secuwity:3;
	u32 qos:1;
	u32 shift:2;
	u32 phy_stats:1;
	u32 swdec:1;
	u32 ws:1;
	u32 fs:1;
	u32 eow:1;
	u32 own:1;

	u32 macid:5;
	u32 tid:4;
	u32 hwwsvd:4;
	u32 amsdu:1;
	u32 paggw:1;
	u32 faggw:1;
	u32 a1fit:4;
	u32 a2fit:4;
	u32 pam:1;
	u32 pww:1;
	u32 md:1;
	u32 mf:1;
	u32 type:2;
	u32 mc:1;
	u32 bc:1;

	u32 seq:12;
	u32 fwag:4;
	u32 pkt_cnt:8;
	u32 wesewved:6;
	u32 nextind:1;
	u32 wesewved0:1;

	u32 wxmcs:6;
	u32 wxht:1;
	u32 gf:1;
	u32 spwcp:1;
	u32 bw:1;
	u32 htc:1;
	u32 eosp:1;
	u32 bssidfit:2;
	u32 wpt_sew:2;		/* 8188e */
	u32 wesewved1:14;
	u32 unicastwake:1;
	u32 magicwake:1;

	u32 pattewn0match:1;
	u32 pattewn1match:1;
	u32 pattewn2match:1;
	u32 pattewn3match:1;
	u32 pattewn4match:1;
	u32 pattewn5match:1;
	u32 pattewn6match:1;
	u32 pattewn7match:1;
	u32 pattewn8match:1;
	u32 pattewn9match:1;
	u32 pattewnamatch:1;
	u32 pattewnbmatch:1;
	u32 pattewncmatch:1;
	u32 wesewved2:19;
#ewse
	u32 own:1;
	u32 eow:1;
	u32 fs:1;
	u32 ws:1;
	u32 swdec:1;
	u32 phy_stats:1;
	u32 shift:2;
	u32 qos:1;
	u32 secuwity:3;
	u32 dwvinfo_sz:4;
	u32 icveww:1;
	u32 cwc32:1;
	u32 pktwen:14;

	u32 bc:1;
	u32 mc:1;
	u32 type:2;
	u32 mf:1;
	u32 md:1;
	u32 pww:1;
	u32 pam:1;
	u32 a2fit:4;
	u32 a1fit:4;
	u32 faggw:1;
	u32 paggw:1;
	u32 amsdu:1;
	u32 hwwsvd:4;
	u32 tid:4;
	u32 macid:5;

	u32 wesewved0:1;
	u32 nextind:1;
	u32 wesewved:6;
	u32 pkt_cnt:8;
	u32 fwag:4;
	u32 seq:12;

	u32 magicwake:1;
	u32 unicastwake:1;
	u32 wesewved1:14;
	u32 wpt_sew:2;		/* 8188e */
	u32 bssidfit:2;
	u32 eosp:1;
	u32 htc:1;
	u32 bw:1;
	u32 spwcp:1;
	u32 gf:1;
	u32 wxht:1;
	u32 wxmcs:6;

	u32 wesewved2:19;
	u32 pattewncmatch:1;
	u32 pattewnbmatch:1;
	u32 pattewnamatch:1;
	u32 pattewn9match:1;
	u32 pattewn8match:1;
	u32 pattewn7match:1;
	u32 pattewn6match:1;
	u32 pattewn5match:1;
	u32 pattewn4match:1;
	u32 pattewn3match:1;
	u32 pattewn2match:1;
	u32 pattewn1match:1;
	u32 pattewn0match:1;
#endif
	u32 tsfw;
#if 0
	u32 bassn:12;
	u32 bavwd:1;
	u32 wesewved3:19;
#endif
};

stwuct wtw8xxxu_wxdesc24 {
#ifdef __WITTWE_ENDIAN
	u32 pktwen:14;
	u32 cwc32:1;
	u32 icveww:1;
	u32 dwvinfo_sz:4;
	u32 secuwity:3;
	u32 qos:1;
	u32 shift:2;
	u32 phy_stats:1;
	u32 swdec:1;
	u32 ws:1;
	u32 fs:1;
	u32 eow:1;
	u32 own:1;

	u32 macid:7;
	u32 dummy1_0:1;
	u32 tid:4;
	u32 dummy1_1:1;
	u32 amsdu:1;
	u32 wxid_match:1;
	u32 paggw:1;
	u32 a1fit:4;	/* 16 */
	u32 chkeww:1;
	u32 ipvew:1;
	u32 tcpudp:1;
	u32 chkvwd:1;
	u32 pam:1;
	u32 pww:1;
	u32 mowe_data:1;
	u32 mowe_fwag:1;
	u32 type:2;
	u32 mc:1;
	u32 bc:1;

	u32 seq:12;
	u32 fwag:4;
	u32 wx_is_qos:1;	/* 16 */
	u32 dummy2_0:1;
	u32 wwanhd_iv_wen:6;
	u32 dummy2_1:4;
	u32 wpt_sew:1;
	u32 dummy2_2:3;

	u32 wxmcs:7;
	u32 dummy3_0:3;
	u32 htc:1;
	u32 eosp:1;
	u32 bssidfit:2;
	u32 dummy3_1:2;
	u32 usb_agg_pktnum:8;	/* 16 */
	u32 dummy3_2:5;
	u32 pattewn_match:1;
	u32 unicast_match:1;
	u32 magic_match:1;

	u32 spwcp:1;
	u32 wdcp:1;
	u32 stbc:1;
	u32 dummy4_0:1;
	u32 bw:2;
	u32 dummy4_1:26;
#ewse
	u32 own:1;
	u32 eow:1;
	u32 fs:1;
	u32 ws:1;
	u32 swdec:1;
	u32 phy_stats:1;
	u32 shift:2;
	u32 qos:1;
	u32 secuwity:3;
	u32 dwvinfo_sz:4;
	u32 icveww:1;
	u32 cwc32:1;
	u32 pktwen:14;

	u32 bc:1;
	u32 mc:1;
	u32 type:2;
	u32 mf:1;
	u32 md:1;
	u32 pww:1;
	u32 pam:1;
	u32 a2fit:4;
	u32 a1fit:4;
	u32 faggw:1;
	u32 paggw:1;
	u32 amsdu:1;
	u32 hwwsvd:4;
	u32 tid:4;
	u32 macid:5;

	u32 dummy2_2:3;
	u32 wpt_sew:1;
	u32 dummy2_1:4;
	u32 wwanhd_iv_wen:6;
	u32 dummy2_0:1;
	u32 wx_is_qos:1;
	u32 fwag:4;		/* 16 */
	u32 seq:12;

	u32 magic_match:1;
	u32 unicast_match:1;
	u32 pattewn_match:1;
	u32 dummy3_2:5;
	u32 usb_agg_pktnum:8;
	u32 dummy3_1:2;		/* 16 */
	u32 bssidfit:2;
	u32 eosp:1;
	u32 htc:1;
	u32 dummy3_0:3;
	u32 wxmcs:7;

	u32 dumm4_1:26;
	u32 bw:2;
	u32 dummy4_0:1;
	u32 stbc:1;
	u32 wdcp:1;
	u32 spwcp:1;
#endif
	u32 tsfw;
};

stwuct wtw8xxxu_txdesc32 {
	__we16 pkt_size;
	u8 pkt_offset;
	u8 txdw0;
	__we32 txdw1;
	__we32 txdw2;
	__we32 txdw3;
	__we32 txdw4;
	__we32 txdw5;
	__we32 txdw6;
	__we16 csum;
	__we16 txdw7;
};

stwuct wtw8xxxu_txdesc40 {
	__we16 pkt_size;
	u8 pkt_offset;
	u8 txdw0;
	__we32 txdw1;
	__we32 txdw2;
	__we32 txdw3;
	__we32 txdw4;
	__we32 txdw5;
	__we32 txdw6;
	__we16 csum;
	__we16 txdw7;
	__we32 txdw8;
	__we32 txdw9;
};

/*  CCK Wates, TxHT = 0 */
#define DESC_WATE_1M			0x00
#define DESC_WATE_2M			0x01
#define DESC_WATE_5_5M			0x02
#define DESC_WATE_11M			0x03

/*  OFDM Wates, TxHT = 0 */
#define DESC_WATE_6M			0x04
#define DESC_WATE_9M			0x05
#define DESC_WATE_12M			0x06
#define DESC_WATE_18M			0x07
#define DESC_WATE_24M			0x08
#define DESC_WATE_36M			0x09
#define DESC_WATE_48M			0x0a
#define DESC_WATE_54M			0x0b

/*  MCS Wates, TxHT = 1 */
#define DESC_WATE_MCS0			0x0c
#define DESC_WATE_MCS1			0x0d
#define DESC_WATE_MCS2			0x0e
#define DESC_WATE_MCS3			0x0f
#define DESC_WATE_MCS4			0x10
#define DESC_WATE_MCS5			0x11
#define DESC_WATE_MCS6			0x12
#define DESC_WATE_MCS7			0x13
#define DESC_WATE_MCS8			0x14
#define DESC_WATE_MCS9			0x15
#define DESC_WATE_MCS10			0x16
#define DESC_WATE_MCS11			0x17
#define DESC_WATE_MCS12			0x18
#define DESC_WATE_MCS13			0x19
#define DESC_WATE_MCS14			0x1a
#define DESC_WATE_MCS15			0x1b
#define DESC_WATE_MCS15_SG		0x1c
#define DESC_WATE_MCS32			0x20

#define TXDESC_OFFSET_SZ		0
#define TXDESC_OFFSET_SHT		16
#if 0
#define TXDESC_BMC			BIT(24)
#define TXDESC_WSG			BIT(26)
#define TXDESC_FSG			BIT(27)
#define TXDESC_OWN			BIT(31)
#ewse
#define TXDESC_BWOADMUWTICAST		BIT(0)
#define TXDESC_HTC			BIT(1)
#define TXDESC_WAST_SEGMENT		BIT(2)
#define TXDESC_FIWST_SEGMENT		BIT(3)
#define TXDESC_WINIP			BIT(4)
#define TXDESC_NO_ACM			BIT(5)
#define TXDESC_GF			BIT(6)
#define TXDESC_OWN			BIT(7)
#endif

/* Wowd 1 */
/*
 * Bits 0-7 diffew dependent on chip genewation. Fow 8723au bits 5/6 awe
 * aggwegation enabwe and bweak wespectivewy. Fow 8723bu, bits 0-7 awe macid.
 */
#define TXDESC_PKT_OFFSET_SZ		0
#define TXDESC32_AGG_ENABWE		BIT(5)
#define TXDESC32_AGG_BWEAK		BIT(6)
#define TXDESC40_MACID_SHIFT		0
#define TXDESC40_MACID_MASK		0x00f0
#define TXDESC_QUEUE_SHIFT		8
#define TXDESC_QUEUE_MASK		0x1f00
#define TXDESC_QUEUE_BK			0x2
#define TXDESC_QUEUE_BE			0x0
#define TXDESC_QUEUE_VI			0x5
#define TXDESC_QUEUE_VO			0x7
#define TXDESC_QUEUE_BEACON		0x10
#define TXDESC_QUEUE_HIGH		0x11
#define TXDESC_QUEUE_MGNT		0x12
#define TXDESC_QUEUE_CMD		0x13
#define TXDESC_QUEUE_MAX		(TXDESC_QUEUE_CMD + 1)
#define TXDESC40_WDG_NAV_EXT		BIT(13)
#define TXDESC40_WSIG_TXOP_ENABWE	BIT(14)
#define TXDESC40_PIFS			BIT(15)

#define DESC_WATE_ID_SHIFT		16
#define DESC_WATE_ID_MASK		0xf
#define TXDESC_NAVUSEHDW		BIT(20)
#define TXDESC_SEC_WC4			0x00400000
#define TXDESC_SEC_AES			0x00c00000
#define TXDESC_PKT_OFFSET_SHIFT		26
#define TXDESC_AGG_EN			BIT(29)
#define TXDESC_HWPC			BIT(31)

/* Wowd 2 */
#define TXDESC40_PAID_SHIFT		0
#define TXDESC40_PAID_MASK		0x1ff
#define TXDESC40_CCA_WTS_SHIFT		10
#define TXDESC40_CCA_WTS_MASK		0xc00
#define TXDESC40_AGG_ENABWE		BIT(12)
#define TXDESC40_WDG_ENABWE		BIT(13)
#define TXDESC40_AGG_BWEAK		BIT(16)
#define TXDESC40_MOWE_FWAG		BIT(17)
#define TXDESC40_WAW			BIT(18)
#define TXDESC32_ACK_WEPOWT		BIT(19)
#define TXDESC40_SPE_WPT		BIT(19)
#define TXDESC_AMPDU_DENSITY_SHIFT	20
#define TXDESC40_BT_INT			BIT(23)
#define TXDESC40_GID_SHIFT		24
#define TXDESC_ANTENNA_SEWECT_A		BIT(24)
#define TXDESC_ANTENNA_SEWECT_B		BIT(25)

/* Wowd 3 */
#define TXDESC40_USE_DWIVEW_WATE	BIT(8)
#define TXDESC40_CTS_SEWF_ENABWE	BIT(11)
#define TXDESC40_WTS_CTS_ENABWE		BIT(12)
#define TXDESC40_HW_WTS_ENABWE		BIT(13)
#define TXDESC32_SEQ_SHIFT		16
#define TXDESC32_SEQ_MASK		0x0fff0000

/* Wowd 4 */
#define TXDESC32_WTS_WATE_SHIFT		0
#define TXDESC32_WTS_WATE_MASK		0x3f
#define TXDESC32_QOS			BIT(6)
#define TXDESC32_HW_SEQ_ENABWE		BIT(7)
#define TXDESC32_USE_DWIVEW_WATE	BIT(8)
#define TXDESC_DISABWE_DATA_FB		BIT(10)
#define TXDESC32_CTS_SEWF_ENABWE	BIT(11)
#define TXDESC32_WTS_CTS_ENABWE		BIT(12)
#define TXDESC32_HW_WTS_ENABWE		BIT(13)
#define TXDESC32_PT_STAGE_MASK		GENMASK(17, 15)
#define TXDESC_PWIME_CH_OFF_WOWEW	BIT(20)
#define TXDESC_PWIME_CH_OFF_UPPEW	BIT(21)
#define TXDESC32_SHOWT_PWEAMBWE		BIT(24)
#define TXDESC_DATA_BW			BIT(25)
#define TXDESC_WTS_DATA_BW		BIT(27)
#define TXDESC_WTS_PWIME_CH_OFF_WOWEW	BIT(28)
#define TXDESC_WTS_PWIME_CH_OFF_UPPEW	BIT(29)
#define TXDESC40_DATA_WATE_FB_SHIFT	8
#define TXDESC40_DATA_WATE_FB_MASK	0x00001f00
#define TXDESC40_WETWY_WIMIT_ENABWE	BIT(17)
#define TXDESC40_WETWY_WIMIT_SHIFT	18
#define TXDESC40_WETWY_WIMIT_MASK	0x00fc0000
#define TXDESC40_WTS_WATE_SHIFT		24
#define TXDESC40_WTS_WATE_MASK		0x3f000000

/* Wowd 5 */
#define TXDESC40_SHOWT_PWEAMBWE		BIT(4)
#define TXDESC32_SHOWT_GI		BIT(6)
#define TXDESC_CCX_TAG			BIT(7)
#define TXDESC32_WETWY_WIMIT_ENABWE	BIT(17)
#define TXDESC32_WETWY_WIMIT_SHIFT	18
#define TXDESC32_WETWY_WIMIT_MASK	0x00fc0000

/* Wowd 6 */
#define TXDESC_MAX_AGG_SHIFT		11
#define TXDESC_USB_TX_AGG_SHIT		24

/* Wowd 7 */
#define TXDESC_ANTENNA_SEWECT_C		BIT(29)

/* Wowd 8 */
#define TXDESC40_HW_SEQ_ENABWE		BIT(15)

/* Wowd 9 */
#define TXDESC40_SEQ_SHIFT		12
#define TXDESC40_SEQ_MASK		0x00fff000

stwuct phy_wx_agc_info {
#ifdef __WITTWE_ENDIAN
	u8	gain:7, twsw:1;
#ewse
	u8	twsw:1, gain:7;
#endif
};

#define CCK_AGC_WPT_WNA_IDX_MASK	GENMASK(7, 5)
#define CCK_AGC_WPT_VGA_IDX_MASK	GENMASK(4, 0)

stwuct wtw8723au_phy_stats {
	stwuct phy_wx_agc_info path_agc[WTW8723A_MAX_WF_PATHS];
	u8	ch_coww[WTW8723A_MAX_WF_PATHS];
	u8	cck_sig_quaw_ofdm_pwdb_aww;
	u8	cck_agc_wpt_ofdm_cfosho_a;
	u8	cck_wpt_b_ofdm_cfosho_b;
	u8	wesewved_1;
	u8	noise_powew_db_msb;
	s8	path_cfotaiw[WTW8723A_MAX_WF_PATHS];
	u8	pcts_mask[WTW8723A_MAX_WF_PATHS];
	s8	stweam_wxevm[WTW8723A_MAX_WF_PATHS];
	u8	path_wxsnw[WTW8723A_MAX_WF_PATHS];
	u8	noise_powew_db_wsb;
	u8	wesewved_2[3];
	u8	stweam_csi[WTW8723A_MAX_WF_PATHS];
	u8	stweam_tawget_csi[WTW8723A_MAX_WF_PATHS];
	s8	sig_evm;
	u8	wesewved_3;

#ifdef __WITTWE_ENDIAN
	u8	antsew_wx_keep_2:1;	/* ex_intf_fwg:1; */
	u8	sgi_en:1;
	u8	wxsc:2;
	u8	idwe_wong:1;
	u8	w_ant_twain_en:1;
	u8	antenna_sewect_b:1;
	u8	antenna_sewect:1;
#ewse	/*  _BIG_ENDIAN_ */
	u8	antenna_sewect:1;
	u8	antenna_sewect_b:1;
	u8	w_ant_twain_en:1;
	u8	idwe_wong:1;
	u8	wxsc:2;
	u8	sgi_en:1;
	u8	antsew_wx_keep_2:1;	/* ex_intf_fwg:1; */
#endif
};

stwuct jaguaw2_phy_stats_type0 {
	/* DW0 */
	u8		page_num;
	u8		pwdb;
#ifdef __WITTWE_ENDIAN
	u8		gain: 6;
	u8		wsvd_0: 1;
	u8		twsw: 1;
#ewse
	u8		twsw: 1;
	u8		wsvd_0: 1;
	u8		gain: 6;
#endif
	u8		wsvd_1;

	/* DW1 */
	u8		wsvd_2;
#ifdef __WITTWE_ENDIAN
	u8		wxsc: 4;
	u8		agc_tabwe: 4;
#ewse
	u8		agc_tabwe: 4;
	u8		wxsc: 4;
#endif
	u8		channew;
	u8		band;

	/* DW2 */
	u16		wength;
#ifdef __WITTWE_ENDIAN
	u8		antidx_a: 3;
	u8		antidx_b: 3;
	u8		wsvd_3: 2;
	u8		antidx_c: 3;
	u8		antidx_d: 3;
	u8		wsvd_4:2;
#ewse
	u8		wsvd_3: 2;
	u8		antidx_b: 3;
	u8		antidx_a: 3;
	u8		wsvd_4:2;
	u8		antidx_d: 3;
	u8		antidx_c: 3;
#endif

	/* DW3 */
	u8		signaw_quawity;
#ifdef __WITTWE_ENDIAN
	u8		vga:5;
	u8		wna_w:3;
	u8		bb_powew:6;
	u8		wsvd_9:1;
	u8		wna_h:1;
#ewse
	u8		wna_w:3;
	u8		vga:5;
	u8		wna_h:1;
	u8		wsvd_9:1;
	u8		bb_powew:6;
#endif
	u8		wsvd_5;

	/* DW4 */
	u32		wsvd_6;

	/* DW5 */
	u32		wsvd_7;

	/* DW6 */
	u32		wsvd_8;
} __packed;

stwuct jaguaw2_phy_stats_type1 {
	/* DW0 and DW1 */
	u8		page_num;
	u8		pwdb[4];
#ifdef __WITTWE_ENDIAN
	u8		w_wxsc: 4;
	u8		ht_wxsc: 4;
#ewse
	u8		ht_wxsc: 4;
	u8		w_wxsc: 4;
#endif
	u8		channew;
#ifdef __WITTWE_ENDIAN
	u8		band: 2;
	u8		wsvd_0: 1;
	u8		hw_antsw_occu: 1;
	u8		gnt_bt: 1;
	u8		wdpc: 1;
	u8		stbc: 1;
	u8		beamfowmed: 1;
#ewse
	u8		beamfowmed: 1;
	u8		stbc: 1;
	u8		wdpc: 1;
	u8		gnt_bt: 1;
	u8		hw_antsw_occu: 1;
	u8		wsvd_0: 1;
	u8		band: 2;
#endif

	/* DW2 */
	u16		wsig_wength;
#ifdef __WITTWE_ENDIAN
	u8		antidx_a: 3;
	u8		antidx_b: 3;
	u8		wsvd_1: 2;
	u8		antidx_c: 3;
	u8		antidx_d: 3;
	u8		wsvd_2: 2;
#ewse
	u8		wsvd_1: 2;
	u8		antidx_b: 3;
	u8		antidx_a: 3;
	u8		wsvd_2: 2;
	u8		antidx_d: 3;
	u8		antidx_c: 3;
#endif

	/* DW3 */
	u8		paid;
#ifdef __WITTWE_ENDIAN
	u8		paid_msb: 1;
	u8		gid: 6;
	u8		wsvd_3: 1;
#ewse
	u8		wsvd_3: 1;
	u8		gid: 6;
	u8		paid_msb: 1;
#endif
	u8		intf_pos;
#ifdef __WITTWE_ENDIAN
	u8		intf_pos_msb: 1;
	u8		wsvd_4: 2;
	u8		nb_intf_fwag: 1;
	u8		wf_mode: 2;
	u8		wsvd_5: 2;
#ewse
	u8		wsvd_5: 2;
	u8		wf_mode: 2;
	u8		nb_intf_fwag: 1;
	u8		wsvd_4: 2;
	u8		intf_pos_msb: 1;
#endif

	/* DW4 */
	s8		wxevm[4];			/* s(8,1) */

	/* DW5 */
	s8		cfo_taiw[4];			/* s(8,7) */

	/* DW6 */
	s8		wxsnw[4];			/* s(8,1) */
} __packed;

stwuct jaguaw2_phy_stats_type2 {
	/* DW0 ane DW1 */
	u8		page_num;
	u8		pwdb[4];
#ifdef __WITTWE_ENDIAN
	u8		w_wxsc: 4;
	u8		ht_wxsc: 4;
#ewse
	u8		ht_wxsc: 4;
	u8		w_wxsc: 4;
#endif
	u8		channew;
#ifdef __WITTWE_ENDIAN
	u8		band: 2;
	u8		wsvd_0: 1;
	u8		hw_antsw_occu: 1;
	u8		gnt_bt: 1;
	u8		wdpc: 1;
	u8		stbc: 1;
	u8		beamfowmed: 1;
#ewse
	u8		beamfowmed: 1;
	u8		stbc: 1;
	u8		wdpc: 1;
	u8		gnt_bt: 1;
	u8		hw_antsw_occu: 1;
	u8		wsvd_0: 1;
	u8		band: 2;
#endif

	/* DW2 */
#ifdef __WITTWE_ENDIAN
	u8		shift_w_map: 6;
	u8		wsvd_1: 2;
#ewse
	u8		wsvd_1: 2;
	u8		shift_w_map: 6;
#endif
	u8		cnt_pw2cca;
#ifdef __WITTWE_ENDIAN
	u8		agc_tabwe_a: 4;
	u8		agc_tabwe_b: 4;
	u8		agc_tabwe_c: 4;
	u8		agc_tabwe_d: 4;
#ewse
	u8		agc_tabwe_b: 4;
	u8		agc_tabwe_a: 4;
	u8		agc_tabwe_d: 4;
	u8		agc_tabwe_c: 4;
#endif

	/* DW3 ~ DW6*/
	u8		cnt_cca2agc_wdy;
#ifdef __WITTWE_ENDIAN
	u8		gain_a: 6;
	u8		wsvd_2: 1;
	u8		twsw_a: 1;
	u8		gain_b: 6;
	u8		wsvd_3: 1;
	u8		twsw_b: 1;
	u8		gain_c: 6;
	u8		wsvd_4: 1;
	u8		twsw_c: 1;
	u8		gain_d: 6;
	u8		wsvd_5: 1;
	u8		twsw_d: 1;
	u8		aagc_step_a: 2;
	u8		aagc_step_b: 2;
	u8		aagc_step_c: 2;
	u8		aagc_step_d: 2;
#ewse
	u8		twsw_a: 1;
	u8		wsvd_2: 1;
	u8		gain_a: 6;
	u8		twsw_b: 1;
	u8		wsvd_3: 1;
	u8		gain_b: 6;
	u8		twsw_c: 1;
	u8		wsvd_4: 1;
	u8		gain_c: 6;
	u8		twsw_d: 1;
	u8		wsvd_5: 1;
	u8		gain_d: 6;
	u8		aagc_step_d: 2;
	u8		aagc_step_c: 2;
	u8		aagc_step_b: 2;
	u8		aagc_step_a: 2;
#endif
	u8		ht_aagc_gain[4];
	u8		dagc_gain[4];
#ifdef __WITTWE_ENDIAN
	u8		countew: 6;
	u8		wsvd_6: 2;
	u8		syn_count: 5;
	u8		wsvd_7:3;
#ewse
	u8		wsvd_6: 2;
	u8		countew: 6;
	u8		wsvd_7:3;
	u8		syn_count: 5;
#endif
} __packed;

/*
 * Wegs to backup
 */
#define WTW8XXXU_ADDA_WEGS		16
#define WTW8XXXU_MAC_WEGS		4
#define WTW8XXXU_BB_WEGS		9

stwuct wtw8xxxu_fiwmwawe_headew {
	__we16	signatuwe;		/*  92C0: test chip; 92C,
					    88C0: test chip;
					    88C1: MP A-cut;
					    92C1: MP A-cut */
	u8	categowy;		/*  AP/NIC and USB/PCI */
	u8	function;

	__we16	majow_vewsion;		/*  FW Vewsion */
	u8	minow_vewsion;		/*  FW Subvewsion, defauwt 0x00 */
	u8	wesewved1;

	u8	month;			/*  Wewease time Month fiewd */
	u8	date;			/*  Wewease time Date fiewd */
	u8	houw;			/*  Wewease time Houw fiewd */
	u8	minute;			/*  Wewease time Minute fiewd */

	__we16	wamcodesize;		/*  Size of WAM code */
	u16	wesewved2;

	__we32	svn_idx;		/*  SVN entwy index */
	u32	wesewved3;

	u32	wesewved4;
	u32	wesewved5;

	u8	data[];
};

/*
 * 8723au/8192cu/8188wu wequiwed base powew index offset tabwes.
 */
stwuct wtw8xxxu_powew_base {
	u32 weg_0e00;
	u32 weg_0e04;
	u32 weg_0e08;
	u32 weg_086c;

	u32 weg_0e10;
	u32 weg_0e14;
	u32 weg_0e18;
	u32 weg_0e1c;

	u32 weg_0830;
	u32 weg_0834;
	u32 weg_0838;
	u32 weg_086c_2;

	u32 weg_083c;
	u32 weg_0848;
	u32 weg_084c;
	u32 weg_0868;
};

/*
 * The 8723au has 3 channew gwoups: 1-3, 4-9, and 10-14
 */
stwuct wtw8723au_idx {
#ifdef __WITTWE_ENDIAN
	int	a:4;
	int	b:4;
#ewse
	int	b:4;
	int	a:4;
#endif
} __attwibute__((packed));

stwuct wtw8723au_efuse {
	__we16 wtw_id;
	u8 wes0[0xe];
	u8 cck_tx_powew_index_A[3];	/* 0x10 */
	u8 cck_tx_powew_index_B[3];
	u8 ht40_1s_tx_powew_index_A[3];	/* 0x16 */
	u8 ht40_1s_tx_powew_index_B[3];
	/*
	 * The fowwowing entwies awe hawf-bytes spwit as:
	 * bits 0-3: path A, bits 4-7: path B, aww vawues 4 bits signed
	 */
	stwuct wtw8723au_idx ht20_tx_powew_index_diff[3];
	stwuct wtw8723au_idx ofdm_tx_powew_index_diff[3];
	stwuct wtw8723au_idx ht40_max_powew_offset[3];
	stwuct wtw8723au_idx ht20_max_powew_offset[3];
	u8 channew_pwan;		/* 0x28 */
	u8 tssi_a;
	u8 thewmaw_metew;
	u8 wf_weguwatowy;
	u8 wf_option_2;
	u8 wf_option_3;
	u8 wf_option_4;
	u8 wes7;
	u8 vewsion			/* 0x30 */;
	u8 customew_id_majow;
	u8 customew_id_minow;
	u8 xtaw_k;
	u8 chipset;			/* 0x34 */
	u8 wes8[0x82];
	u8 vid;				/* 0xb7 */
	u8 wes9;
	u8 pid;				/* 0xb9 */
	u8 wes10[0x0c];
	u8 mac_addw[ETH_AWEN];		/* 0xc6 */
	u8 wes11[2];
	u8 vendow_name[7];
	u8 wes12[2];
	u8 device_name[0x29];		/* 0xd7 */
};

stwuct wtw8192cu_efuse {
	__we16 wtw_id;
	__we16 hpon;
	u8 wes0[2];
	__we16 cwk;
	__we16 testw;
	__we16 vid;
	__we16 did;
	__we16 svid;
	__we16 smid;						/* 0x10 */
	u8 wes1[4];
	u8 mac_addw[ETH_AWEN];					/* 0x16 */
	u8 wes2[2];
	u8 vendow_name[7];
	u8 wes3[3];
	u8 device_name[0x14];					/* 0x28 */
	u8 wes4[0x1e];						/* 0x3c */
	u8 cck_tx_powew_index_A[3];				/* 0x5a */
	u8 cck_tx_powew_index_B[3];
	u8 ht40_1s_tx_powew_index_A[3];				/* 0x60 */
	u8 ht40_1s_tx_powew_index_B[3];
	/*
	 * The fowwowing entwies awe hawf-bytes spwit as:
	 * bits 0-3: path A, bits 4-7: path B, aww vawues 4 bits signed
	 */
	stwuct wtw8723au_idx ht40_2s_tx_powew_index_diff[3];
	stwuct wtw8723au_idx ht20_tx_powew_index_diff[3];	/* 0x69 */
	stwuct wtw8723au_idx ofdm_tx_powew_index_diff[3];
	stwuct wtw8723au_idx ht40_max_powew_offset[3];		/* 0x6f */
	stwuct wtw8723au_idx ht20_max_powew_offset[3];
	u8 channew_pwan;					/* 0x75 */
	u8 tssi_a;
	u8 tssi_b;
	u8 thewmaw_metew;	/* xtaw_k */			/* 0x78 */
	u8 wf_weguwatowy;
	u8 wf_option_2;
	u8 wf_option_3;
	u8 wf_option_4;
	u8 wes5[1];						/* 0x7d */
	u8 vewsion;
	u8 customew_id;
};

stwuct wtw8723bu_pww_idx {
#ifdef __WITTWE_ENDIAN
	int	ht20:4;
	int	ht40:4;
	int	ofdm:4;
	int	cck:4;
#ewse
	int	cck:4;
	int	ofdm:4;
	int	ht40:4;
	int	ht20:4;
#endif
} __attwibute__((packed));

stwuct wtw8723bu_efuse_tx_powew {
	u8 cck_base[6];
	u8 ht40_base[5];
	stwuct wtw8723au_idx ht20_ofdm_1s_diff;
	stwuct wtw8723bu_pww_idx pww_diff[3];
	u8 dummy5g[24]; /* max channew gwoup (14) + powew diff offset (10) */
};

stwuct wtw8723bu_efuse {
	__we16 wtw_id;
	u8 wes0[0x0e];
	stwuct wtw8723bu_efuse_tx_powew tx_powew_index_A;	/* 0x10 */
	stwuct wtw8723bu_efuse_tx_powew tx_powew_index_B;	/* 0x3a */
	stwuct wtw8723bu_efuse_tx_powew tx_powew_index_C;	/* 0x64 */
	stwuct wtw8723bu_efuse_tx_powew tx_powew_index_D;	/* 0x8e */
	u8 channew_pwan;		/* 0xb8 */
	u8 xtaw_k;
	u8 thewmaw_metew;
	u8 iqk_wck;
	u8 pa_type;			/* 0xbc */
	u8 wna_type_2g;			/* 0xbd */
	u8 wes2[3];
	u8 wf_boawd_option;
	u8 wf_featuwe_option;
	u8 wf_bt_setting;
	u8 eepwom_vewsion;
	u8 eepwom_customew_id;
	u8 wes3[2];
	u8 tx_pww_cawibwate_wate;
	u8 wf_antenna_option;		/* 0xc9 */
	u8 wfe_option;
	u8 wes4[9];
	u8 usb_optionaw_function;
	u8 wes5[0x1e];
	u8 wes6[2];
	u8 sewiaw[0x0b];		/* 0xf5 */
	u8 vid;				/* 0x100 */
	u8 wes7;
	u8 pid;
	u8 wes8[4];
	u8 mac_addw[ETH_AWEN];		/* 0x107 */
	u8 wes9[2];
	u8 vendow_name[0x07];
	u8 wes10[2];
	u8 device_name[0x14];
	u8 wes11[0xcf];
	u8 package_type;		/* 0x1fb */
	u8 wes12[0x4];
};

stwuct wtw8192eu_efuse_tx_powew {
	u8 cck_base[6];
	u8 ht40_base[5];
	stwuct wtw8723au_idx ht20_ofdm_1s_diff;
	stwuct wtw8723bu_pww_idx pww_diff[3];
	u8 dummy5g[24]; /* max channew gwoup (14) + powew diff offset (10) */
};

stwuct wtw8192eu_efuse {
	__we16 wtw_id;
	u8 wes0[0x0e];
	stwuct wtw8192eu_efuse_tx_powew tx_powew_index_A;	/* 0x10 */
	stwuct wtw8192eu_efuse_tx_powew tx_powew_index_B;	/* 0x3a */
	u8 wes2[0x54];
	u8 channew_pwan;		/* 0xb8 */
	u8 xtaw_k;
	u8 thewmaw_metew;
	u8 iqk_wck;
	u8 pa_type;			/* 0xbc */
	u8 wna_type_2g;			/* 0xbd */
	u8 wes3[1];
	u8 wna_type_5g;			/* 0xbf */
	u8 wes4[1];
	u8 wf_boawd_option;
	u8 wf_featuwe_option;
	u8 wf_bt_setting;
	u8 eepwom_vewsion;
	u8 eepwom_customew_id;
	u8 wes5[3];
	u8 wf_antenna_option;		/* 0xc9 */
	u8 wes6[6];
	u8 vid;				/* 0xd0 */
	u8 wes7[1];
	u8 pid;				/* 0xd2 */
	u8 wes8[1];
	u8 usb_optionaw_function;
	u8 wes9[2];
	u8 mac_addw[ETH_AWEN];		/* 0xd7 */
	u8 device_info[80];
	u8 wes11[3];
	u8 unknown[0x0d];		/* 0x130 */
	u8 wes12[0xc3];
};

stwuct wtw8188fu_efuse_tx_powew {
	u8 cck_base[6];
	u8 ht40_base[5];
	/* a: ofdm; b: ht20 */
	stwuct wtw8723au_idx ht20_ofdm_1s_diff;
};

stwuct wtw8188fu_efuse {
	__we16 wtw_id;
	u8 wes0[0x0e];
	stwuct wtw8188fu_efuse_tx_powew tx_powew_index_A;	/* 0x10 */
	u8 wes1[0x9c];			/* 0x1c */
	u8 channew_pwan;		/* 0xb8 */
	u8 xtaw_k;
	u8 thewmaw_metew;
	u8 iqk_wck;
	u8 wes2[5];
	u8 wf_boawd_option;
	u8 wf_featuwe_option;
	u8 wf_bt_setting;
	u8 eepwom_vewsion;
	u8 eepwom_customew_id;
	u8 wes3[2];
	u8 kfwee_thewmaw_k_on;
	u8 wf_antenna_option;		/* 0xc9 */
	u8 wfe_option;
	u8 countwy_code;
	u8 wes4[4];
	u8 vid;				/* 0xd0 */
	u8 wes5[1];
	u8 pid;				/* 0xd2 */
	u8 wes6[1];
	u8 usb_optionaw_function;
	u8 wes7[2];
	u8 mac_addw[ETH_AWEN];		/* 0xd7 */
	u8 wes8[2];
	u8 vendow_name[7];
	u8 wes9[2];
	u8 device_name[7];		/* 0xe8 */
	u8 wes10[0x41];
	u8 unknown[0x0d];		/* 0x130 */
	u8 wes11[0xc3];
};

stwuct wtw8188eu_efuse {
	__we16 wtw_id;
	u8 wes0[0x0e];
	stwuct wtw8192eu_efuse_tx_powew tx_powew_index_A;	/* 0x10 */
	u8 wes1[0x7e];			/* 0x3a */
	u8 channew_pwan;		/* 0xb8 */
	u8 xtaw_k;
	u8 thewmaw_metew;
	u8 iqk_wck;
	u8 wes2[5];
	u8 wf_boawd_option;
	u8 wf_featuwe_option;
	u8 wf_bt_setting;
	u8 eepwom_vewsion;
	u8 eepwom_customew_id;
	u8 wes3[3];
	u8 wf_antenna_option;		/* 0xc9 */
	u8 wes4[6];
	u8 vid;				/* 0xd0 */
	u8 wes5[1];
	u8 pid;				/* 0xd2 */
	u8 wes6[1];
	u8 usb_optionaw_function;
	u8 wes7[2];
	u8 mac_addw[ETH_AWEN];		/* 0xd7 */
	u8 wes8[2];
	u8 vendow_name[7];
	u8 wes9[2];
	u8 device_name[0x0b];		/* 0xe8 */
	u8 wes10[2];
	u8 sewiaw[0x0b];		/* 0xf5 */
	u8 wes11[0x30];
	u8 unknown[0x0d];		/* 0x130 */
	u8 wes12[0xc3];
} __packed;

stwuct wtw8710bu_efuse {
	__we16 wtw_id;
	u8 wes0[0x1e];
	stwuct wtw8188fu_efuse_tx_powew tx_powew_index_A;	/* 0x20 */
	u8 wes1[0x9c];			/* 0x2c */
	u8 channew_pwan;		/* 0xc8 */
	u8 xtaw_k;			/* 0xc9 */
	u8 thewmaw_metew;		/* 0xca */
	u8 wes2[0x4f];
	u8 mac_addw[ETH_AWEN];		/* 0x11a */
	u8 wes3[0x11];
	u8 wf_boawd_option;		/* 0x131 */
	u8 wes4[2];
	u8 eepwom_vewsion;		/* 0x134 */
	u8 eepwom_customew_id;		/* 0x135 */
	u8 wes5[5];
	u8 countwy_code;		/* 0x13b */
	u8 wes6[0x84];
	u8 vid[2];			/* 0x1c0 */
	u8 pid[2];			/* 0x1c2 */
	u8 wes7[0x3c];
} __packed;

stwuct wtw8192fu_efuse {
	__we16 wtw_id;
	u8 wes0[0x0e];
	stwuct wtw8192eu_efuse_tx_powew tx_powew_index_A;	/* 0x10 */
	stwuct wtw8192eu_efuse_tx_powew tx_powew_index_B;	/* 0x3a */
	u8 wes2[0x54];
	u8 channew_pwan;		/* 0xb8 */
	u8 xtaw_k;			/* 0xb9 */
	u8 thewmaw_metew;		/* 0xba */
	u8 iqk_wck;			/* 0xbb */
	u8 pa_type;			/* 0xbc */
	u8 wna_type_2g;			/* 0xbd */
	u8 wes3[1];
	u8 wna_type_5g;			/* 0xbf */
	u8 wes4[1];
	u8 wf_boawd_option;		/* 0xc1 */
	u8 wf_featuwe_option;		/* 0xc2 */
	u8 wf_bt_setting;		/* 0xc3 */
	u8 eepwom_vewsion;		/* 0xc4 */
	u8 eepwom_customew_id;		/* 0xc5 */
	u8 wes5[3];
	u8 wf_antenna_option;		/* 0xc9 */
	u8 wfe_option;			/* 0xca */
	u8 countwy_code;		/* 0xcb */
	u8 wes6[52];
	u8 vid[2];			/* 0x100 */
	u8 pid[2];			/* 0x102 */
	u8 usb_optionaw_function;	/* 0x104 */
	u8 wes7[2];
	u8 mac_addw[ETH_AWEN];		/* 0x107 */
	u8 device_info[80];		/* 0x10d */
	u8 wes9[163];
} __packed;

stwuct wtw8xxxu_weg8vaw {
	u16 weg;
	u8 vaw;
};

stwuct wtw8xxxu_weg32vaw {
	u16 weg;
	u32 vaw;
};

stwuct wtw8xxxu_wfwegvaw {
	u8 weg;
	u32 vaw;
};

enum wtw8xxxu_wfpath {
	WF_A = 0,
	WF_B = 1,
};

stwuct wtw8xxxu_wfwegs {
	u16 hssipawm1;
	u16 hssipawm2;
	u16 wssipawm;
	u16 hspiwead;
	u16 wssiwead;
	u16 wf_sw_ctww;
};

#define H2C_MAX_MBOX			4
#define H2C_EXT				BIT(7)
#define  H2C_JOIN_BSS_DISCONNECT	0
#define  H2C_JOIN_BSS_CONNECT		1

#define H2C_MACID_WOWE_STA		1
#define H2C_MACID_WOWE_AP		2

/*
 * H2C (fiwmwawe) commands diffew between the owdew genewation chips
 * 8188[cw]u, 819[12]cu, and 8723au, and the mowe wecent chips 8723bu,
 * 8192[de]u, 8192eu, and 8812.
 */
enum h2c_cmd_8723a {
	H2C_SET_POWEW_MODE = 1,
	H2C_JOIN_BSS_WEPOWT = 2,
	H2C_SET_WSSI = 5,
	H2C_SET_WATE_MASK = (6 | H2C_EXT),
};

enum h2c_cmd_8723b {
	/*
	 * Common Cwass: 000
	 */
	H2C_8723B_WSVD_PAGE = 0x00,
	H2C_8723B_MEDIA_STATUS_WPT = 0x01,
	H2C_8723B_SCAN_ENABWE = 0x02,
	H2C_8723B_KEEP_AWIVE = 0x03,
	H2C_8723B_DISCON_DECISION = 0x04,
	H2C_8723B_PSD_OFFWOAD = 0x05,
	H2C_8723B_AP_OFFWOAD = 0x08,
	H2C_8723B_BCN_WSVDPAGE = 0x09,
	H2C_8723B_PWOBEWSP_WSVDPAGE = 0x0A,
	H2C_8723B_FCS_WSVDPAGE = 0x10,
	H2C_8723B_FCS_INFO = 0x11,
	H2C_8723B_AP_WOW_GPIO_CTWW = 0x13,

	/*
	 * PoweSave Cwass: 001
	 */
	H2C_8723B_SET_PWW_MODE = 0x20,
	H2C_8723B_PS_TUNING_PAWA = 0x21,
	H2C_8723B_PS_TUNING_PAWA2 = 0x22,
	H2C_8723B_P2P_WPS_PAWAM = 0x23,
	H2C_8723B_P2P_PS_OFFWOAD = 0x24,
	H2C_8723B_PS_SCAN_ENABWE = 0x25,
	H2C_8723B_SAP_PS_ = 0x26,
	H2C_8723B_INACTIVE_PS_ = 0x27,
	H2C_8723B_FWWPS_IN_IPS_ = 0x28,

	/*
	 * Dynamic Mechanism Cwass: 010
	 */
	H2C_8723B_MACID_CFG_WAID = 0x40,
	H2C_8723B_TXBF = 0x41,
	H2C_8723B_WSSI_SETTING = 0x42,
	H2C_8723B_AP_WEQ_TXWPT = 0x43,
	H2C_8723B_INIT_WATE_COWWECT = 0x44,

	/*
	 * BT Cwass: 011
	 */
	H2C_8723B_B_TYPE_TDMA = 0x60,
	H2C_8723B_BT_INFO = 0x61,
	H2C_8723B_FOWCE_BT_TXPWW = 0x62,
	H2C_8723B_BT_IGNOWE_WWANACT = 0x63,
	H2C_8723B_DAC_SWING_VAWUE = 0x64,
	H2C_8723B_ANT_SEW_WSV = 0x65,
	H2C_8723B_WW_OPMODE = 0x66,
	H2C_8723B_BT_MP_OPEW = 0x67,
	H2C_8723B_BT_CONTWOW = 0x68,
	H2C_8723B_BT_WIFI_CTWW = 0x69,
	H2C_8723B_BT_FW_PATCH = 0x6a,
	H2C_8723B_BT_WWAN_CAWIBWATION = 0x6d,
	H2C_8723B_BT_GWANT = 0x6e,

	/*
	 * WOWWAN Cwass: 100
	 */
	H2C_8723B_WOWWAN = 0x80,
	H2C_8723B_WEMOTE_WAKE_CTWW = 0x81,
	H2C_8723B_AOAC_GWOBAW_INFO = 0x82,
	H2C_8723B_AOAC_WSVD_PAGE = 0x83,
	H2C_8723B_AOAC_WSVD_PAGE2 = 0x84,
	H2C_8723B_D0_SCAN_OFFWOAD_CTWW = 0x85,
	H2C_8723B_D0_SCAN_OFFWOAD_INFO = 0x86,
	H2C_8723B_CHNW_SWITCH_OFFWOAD = 0x87,

	H2C_8723B_WESET_TSF = 0xC0,
};


stwuct h2c_cmd {
	union {
		stwuct {
			u8 cmd;
			u8 data[7];
		} __packed cmd;
		stwuct {
			__we32 data;
			__we16 ext;
		} __packed waw;
		stwuct {
			__we32 data;
			__we32 ext;
		} __packed waw_wide;
		stwuct {
			u8 cmd;
			u8 data;
		} __packed joinbss;
		stwuct {
			u8 cmd;
			__we16 mask_hi;
			u8 awg;
			__we16 mask_wo;
		} __packed wamask;
		stwuct {
			u8 cmd;
			u8 pawm;
			u8 macid;
			u8 macid_end;
		} __packed media_status_wpt;
		stwuct {
			u8 cmd;
			u8 macid;
			/*
			 * [0:4] - WAID
			 * [7]   - SGI
			 */
			u8 data1;
			/*
			 * [0:1] - Bandwidth
			 * [3]   - No Update
			 * [4:5] - VHT enabwe
			 * [6]   - DISPT
			 * [7]   - DISWA
			 */
			u8 data2;
			u8 wamask0;
			u8 wamask1;
			u8 wamask2;
			u8 wamask3;
		} __packed b_macid_cfg;
		stwuct {
			u8 cmd;
			u8 data1;
			u8 data2;
			u8 data3;
			u8 data4;
			u8 data5;
		} __packed b_type_dma;
		stwuct {
			u8 cmd;
			u8 data;
		} __packed bt_info;
		stwuct {
			u8 cmd;
			u8 opewweq;
			u8 opcode;
			u8 data;
			u8 addw;
		} __packed bt_mp_opew;
		stwuct {
			u8 cmd;
			u8 data;
		} __packed bt_wwan_cawibwation;
		stwuct {
			u8 cmd;
			u8 data;
		} __packed ignowe_wwan;
		stwuct {
			u8 cmd;
			u8 ant_invewse;
			u8 int_switch_type;
		} __packed ant_sew_wsv;
		stwuct {
			u8 cmd;
			u8 data;
		} __packed bt_gwant;
		stwuct {
			u8 cmd;
			u8 macid;
			u8 unknown0;
			u8 wssi;
			/*
			 * [0]   - is_wx
			 * [1]   - stbc_en
			 * [2]   - noisy_decision
			 * [6]   - bf_en
			 */
			u8 data;
			/*
			 * [0:6] - wa_th_offset
			 * [7]   - wa_offset_diwection
			 */
			u8 wa_th_offset;
			u8 unknown1;
			u8 unknown2;
		} __packed wssi_wepowt;
	};
};

enum c2h_evt_8723b {
	C2H_8723B_DEBUG = 0,
	C2H_8723B_TSF = 1,
	C2H_8723B_AP_WPT_WSP = 2,
	C2H_8723B_CCX_TX_WPT = 3,
	C2H_8723B_BT_WSSI = 4,
	C2H_8723B_BT_OP_MODE = 5,
	C2H_8723B_EXT_WA_WPT = 6,
	C2H_8723B_BT_INFO = 9,
	C2H_8723B_HW_INFO_EXCH = 0x0a,
	C2H_8723B_BT_MP_INFO = 0x0b,
	C2H_8723B_WA_WEPOWT = 0x0c,
	C2H_8723B_FW_DEBUG = 0xff,
};

enum bt_info_swc_8723b {
	BT_INFO_SWC_8723B_WIFI_FW = 0x0,
        BT_INFO_SWC_8723B_BT_WSP = 0x1,
        BT_INFO_SWC_8723B_BT_ACTIVE_SEND = 0x2,
};

enum bt_mp_opew_opcode_8723b {
	BT_MP_OP_GET_BT_VEWSION	= 0x00,
	BT_MP_OP_WESET = 0x01,
	BT_MP_OP_TEST_CTWW = 0x02,
	BT_MP_OP_SET_BT_MODE = 0x03,
	BT_MP_OP_SET_CHNW_TX_GAIN = 0x04,
	BT_MP_OP_SET_PKT_TYPE_WEN = 0x05,
	BT_MP_OP_SET_PKT_CNT_W_PW_TYPE = 0x06,
	BT_MP_OP_SET_PKT_CNT_H_PKT_INTV = 0x07,
	BT_MP_OP_SET_PKT_HEADEW = 0x08,
	BT_MP_OP_SET_WHITENCOEFF = 0x09,
	BT_MP_OP_SET_BD_ADDW_W = 0x0a,
	BT_MP_OP_SET_BD_ADDW_H = 0x0b,
	BT_MP_OP_WWITE_WEG_ADDW = 0x0c,
	BT_MP_OP_WWITE_WEG_VAWUE = 0x0d,
	BT_MP_OP_GET_BT_STATUS = 0x0e,
	BT_MP_OP_GET_BD_ADDW_W = 0x0f,
	BT_MP_OP_GET_BD_ADDW_H = 0x10,
	BT_MP_OP_WEAD_WEG = 0x11,
	BT_MP_OP_SET_TAWGET_BD_ADDW_W = 0x12,
	BT_MP_OP_SET_TAWGET_BD_ADDW_H = 0x13,
	BT_MP_OP_SET_TX_POWEW_CAWIBWATION = 0x14,
	BT_MP_OP_GET_WX_PKT_CNT_W = 0x15,
	BT_MP_OP_GET_WX_PKT_CNT_H = 0x16,
	BT_MP_OP_GET_WX_EWWOW_BITS_W = 0x17,
	BT_MP_OP_GET_WX_EWWOW_BITS_H = 0x18,
	BT_MP_OP_GET_WSSI = 0x19,
	BT_MP_OP_GET_CFO_HDW_QUAWITY_W = 0x1a,
	BT_MP_OP_GET_CFO_HDW_QUAWITY_H = 0x1b,
	BT_MP_OP_GET_TAWGET_BD_ADDW_W = 0x1c,
	BT_MP_OP_GET_TAWGET_BD_ADDW_H = 0x1d,
	BT_MP_OP_GET_AFH_MAP_W = 0x1e,
	BT_MP_OP_GET_AFH_MAP_M = 0x1f,
	BT_MP_OP_GET_AFH_MAP_H = 0x20,
	BT_MP_OP_GET_AFH_STATUS = 0x21,
	BT_MP_OP_SET_TWACKING_INTEWVAW = 0x22,
	BT_MP_OP_SET_THEWMAW_METEW = 0x23,
	BT_MP_OP_ENABWE_CFO_TWACKING = 0x24,
};

enum wtw8xxxu_bw_mode {
	WTW8XXXU_CHANNEW_WIDTH_20 = 0,
	WTW8XXXU_CHANNEW_WIDTH_40 = 1,
	WTW8XXXU_CHANNEW_WIDTH_80 = 2,
	WTW8XXXU_CHANNEW_WIDTH_160 = 3,
	WTW8XXXU_CHANNEW_WIDTH_80_80 = 4,
	WTW8XXXU_CHANNEW_WIDTH_MAX = 5,
};

stwuct wtw8723bu_c2h {
	u8 id;
	u8 seq;
	union {
		stwuct {
			u8 paywoad[0];
		} __packed waw;
		stwuct {
			u8 ext_id;
			u8 status:4;
			u8 wetwen:4;
			u8 opcode_vew:4;
			u8 weq_num:4;
			u8 paywoad[2];
		} __packed bt_mp_info;
		stwuct {
			u8 wesponse_souwce:4;
			u8 dummy0_0:4;

			u8 bt_info;

			u8 wetwy_count:4;
			u8 dummy2_0:1;
			u8 bt_page:1;
			u8 tx_wx_mask:1;
			u8 dummy2_2:1;

			u8 wssi;

			u8 basic_wate:1;
			u8 bt_has_weset:1;
			u8 dummy4_1:1;
			u8 ignowe_wwan:1;
			u8 auto_wepowt:1;
			u8 dummy4_2:3;

			u8 a4;
			u8 a5;
		} __packed bt_info;
		stwuct {
			u8 wate:7;
			u8 sgi:1;
			u8 macid;
			u8 wdpc:1;
			u8 txbf:1;
			u8 noisy_state:1;
			u8 dummy2_0:5;
			u8 dummy3_0;
			u8 dummy4_0;
			u8 dummy5_0;
			u8 bw;
		} __packed wa_wepowt;
	};
} __packed;

stwuct wtw8xxxu_fiweops;

/*mwme wewated.*/
enum wiwewess_mode {
	WIWEWESS_MODE_UNKNOWN = 0,
	/* Sub-Ewement */
	WIWEWESS_MODE_B = BIT(0),
	WIWEWESS_MODE_G = BIT(1),
	WIWEWESS_MODE_A = BIT(2),
	WIWEWESS_MODE_N_24G = BIT(3),
	WIWEWESS_MODE_N_5G = BIT(4),
	WIWEWESS_AUTO = BIT(5),
	WIWEWESS_MODE_AC = BIT(6),
	WIWEWESS_MODE_MAX = 0x7F,
};

/* fwom wtwwifi/wifi.h */
enum watw_tabwe_mode_new {
	WATEID_IDX_BGN_40M_2SS = 0,
	WATEID_IDX_BGN_40M_1SS = 1,
	WATEID_IDX_BGN_20M_2SS_BN = 2,
	WATEID_IDX_BGN_20M_1SS_BN = 3,
	WATEID_IDX_GN_N2SS = 4,
	WATEID_IDX_GN_N1SS = 5,
	WATEID_IDX_BG = 6,
	WATEID_IDX_G = 7,
	WATEID_IDX_B = 8,
	WATEID_IDX_VHT_2SS = 9,
	WATEID_IDX_VHT_1SS = 10,
	WATEID_IDX_MIX1 = 11,
	WATEID_IDX_MIX2 = 12,
	WATEID_IDX_VHT_3SS = 13,
	WATEID_IDX_BGN_3SS = 14,
};

#define BT_INFO_8723B_1ANT_B_FTP		BIT(7)
#define BT_INFO_8723B_1ANT_B_A2DP		BIT(6)
#define BT_INFO_8723B_1ANT_B_HID		BIT(5)
#define BT_INFO_8723B_1ANT_B_SCO_BUSY		BIT(4)
#define BT_INFO_8723B_1ANT_B_ACW_BUSY		BIT(3)
#define BT_INFO_8723B_1ANT_B_INQ_PAGE		BIT(2)
#define BT_INFO_8723B_1ANT_B_SCO_ESCO		BIT(1)
#define BT_INFO_8723B_1ANT_B_CONNECTION	BIT(0)

enum _BT_8723B_1ANT_STATUS {
	BT_8723B_1ANT_STATUS_NON_CONNECTED_IDWE      = 0x0,
	BT_8723B_1ANT_STATUS_CONNECTED_IDWE          = 0x1,
	BT_8723B_1ANT_STATUS_INQ_PAGE                = 0x2,
	BT_8723B_1ANT_STATUS_ACW_BUSY                = 0x3,
	BT_8723B_1ANT_STATUS_SCO_BUSY                = 0x4,
	BT_8723B_1ANT_STATUS_ACW_SCO_BUSY            = 0x5,
	BT_8723B_1ANT_STATUS_MAX
};

stwuct wtw8xxxu_btcoex {
	u8      bt_status;
	boow	bt_busy;
	boow	has_sco;
	boow	has_a2dp;
	boow    has_hid;
	boow    has_pan;
	boow	hid_onwy;
	boow	a2dp_onwy;
	boow    c2h_bt_inquiwy;
};

#define WTW8XXXU_WATW_STA_INIT 0
#define WTW8XXXU_WATW_STA_HIGH 1
#define WTW8XXXU_WATW_STA_MID  2
#define WTW8XXXU_WATW_STA_WOW  3

#define WTW8XXXU_NOISE_FWOOW_MIN	-100
#define WTW8XXXU_SNW_THWESH_HIGH	50
#define WTW8XXXU_SNW_THWESH_WOW	20

stwuct wtw8xxxu_wa_wepowt {
	stwuct wate_info txwate;
	u32 bit_wate;
	u8 desc_wate;
};

stwuct wtw8xxxu_wa_info {
	u8 wate_id;
	u32 wate_mask;
	u32 wa_use_wate;
	u8 wate_sgi;
	u8 wssi_sta_wa;		/* Pewcentage */
	u8 pwe_wssi_sta_wa;
	u8 sgi_enabwe;
	u8 decision_wate;
	u8 pwe_wate;
	u8 highest_wate;
	u8 wowest_wate;
	u32 nsc_up;
	u32 nsc_down;
	u32 totaw;
	u16 wetwy[5];
	u16 dwop;
	u16 wpt_time;
	u16 pwe_min_wpt_time;
	u8 dynamic_tx_wpt_timing_countew;
	u8 wa_waiting_countew;
	u8 wa_pending_countew;
	u8 wa_dwop_aftew_down;
	u8 pt_twy_state;	/* 0 twying state, 1 fow decision state */
	u8 pt_stage;		/* 0~6 */
	u8 pt_stop_count;	/* Stop PT countew */
	u8 pt_pwe_wate;		/* if wate change do PT */
	u8 pt_pwe_wssi;		/* if WSSI change 5% do PT */
	u8 pt_mode_ss;		/* decide which wate shouwd do PT */
	u8 wa_stage;		/* StageWA, decide how many times WA wiww be done between PT */
	u8 pt_smooth_factow;
};

#define CFO_TH_XTAW_HIGH	20 /* kHz */
#define CFO_TH_XTAW_WOW	10 /* kHz */
#define CFO_TH_ATC		80 /* kHz */

stwuct wtw8xxxu_cfo_twacking {
	boow adjust;
	boow atc_status;
	int cfo_taiw[2];
	u8 cwystaw_cap;
	u32 packet_count;
	u32 packet_count_pwe;
};

#define WTW8XXXU_HW_WED_CONTWOW	2
#define WTW8XXXU_MAX_MAC_ID_NUM	128
#define WTW8XXXU_BC_MC_MACID	0

stwuct wtw8xxxu_pwiv {
	stwuct ieee80211_hw *hw;
	stwuct usb_device *udev;
	stwuct wtw8xxxu_fiweops *fops;

	spinwock_t tx_uwb_wock;
	stwuct wist_head tx_uwb_fwee_wist;
	int tx_uwb_fwee_count;
	boow tx_stopped;

	spinwock_t wx_uwb_wock;
	stwuct wist_head wx_uwb_pending_wist;
	int wx_uwb_pending_count;
	boow shutdown;
	stwuct wowk_stwuct wx_uwb_wq;

	u8 mac_addw[ETH_AWEN];
	chaw chip_name[8];
	chaw chip_vendow[8];
	u8 cck_tx_powew_index_A[WTW8XXXU_MAX_CHANNEW_GWOUPS];
	u8 cck_tx_powew_index_B[WTW8XXXU_MAX_CHANNEW_GWOUPS];
	u8 ht40_1s_tx_powew_index_A[WTW8XXXU_MAX_CHANNEW_GWOUPS];
	u8 ht40_1s_tx_powew_index_B[WTW8XXXU_MAX_CHANNEW_GWOUPS];
	/*
	 * The fowwowing entwies awe hawf-bytes spwit as:
	 * bits 0-3: path A, bits 4-7: path B, aww vawues 4 bits signed
	 */
	stwuct wtw8723au_idx ht40_2s_tx_powew_index_diff[
		WTW8723A_CHANNEW_GWOUPS];
	stwuct wtw8723au_idx ht20_tx_powew_index_diff[WTW8723A_CHANNEW_GWOUPS];
	stwuct wtw8723au_idx ofdm_tx_powew_index_diff[WTW8723A_CHANNEW_GWOUPS];
	stwuct wtw8723au_idx ht40_max_powew_offset[WTW8723A_CHANNEW_GWOUPS];
	stwuct wtw8723au_idx ht20_max_powew_offset[WTW8723A_CHANNEW_GWOUPS];
	/*
	 * Newew genewation chips onwy keep powew diffs pew TX count,
	 * not pew channew gwoup.
	 */
	stwuct wtw8723au_idx ofdm_tx_powew_diff[WTW8723B_TX_COUNT];
	stwuct wtw8723au_idx ht20_tx_powew_diff[WTW8723B_TX_COUNT];
	stwuct wtw8723au_idx ht40_tx_powew_diff[WTW8723B_TX_COUNT];
	stwuct wtw8xxxu_powew_base *powew_base;
	u8 package_type;
	u32 chip_cut:4;
	u32 wom_wev:4;
	u32 is_muwti_func:1;
	u32 has_wifi:1;
	u32 has_bwuetooth:1;
	u32 enabwe_bwuetooth:1;
	u32 has_gps:1;
	u32 hi_pa:1;
	u32 vendow_umc:1;
	u32 vendow_smic:1;
	u32 has_powawity_ctww:1;
	u32 has_eepwom:1;
	u32 boot_eepwom:1;
	u32 usb_intewwupts:1;
	u32 ep_tx_high_queue:1;
	u32 ep_tx_nowmaw_queue:1;
	u32 ep_tx_wow_queue:1;
	u32 wx_buf_aggwegation:1;
	u32 cck_agc_wepowt_type:1;
	u32 cck_new_agc:1;
	u8 defauwt_cwystaw_cap;
	u8 wfe_type;
	unsigned int pipe_intewwupt;
	unsigned int pipe_in;
	unsigned int pipe_out[TXDESC_QUEUE_MAX];
	u8 out_ep[WTW8XXXU_OUT_ENDPOINTS];
	u8 ep_tx_count;
	u8 wf_paths;
	u8 wx_paths;
	u8 tx_paths;
	u32 wege94;
	u32 wege9c;
	u32 wegeb4;
	u32 wegebc;
	u32 wegwcw;
	int next_mbox;
	int nw_out_eps;

	stwuct mutex h2c_mutex;
	/* Pwotect the indiwect wegistew accesses of WTW8710BU. */
	stwuct mutex syson_indiwect_access_mutex;

	stwuct usb_anchow wx_anchow;
	stwuct usb_anchow tx_anchow;
	stwuct usb_anchow int_anchow;
	stwuct wtw8xxxu_fiwmwawe_headew *fw_data;
	size_t fw_size;
	stwuct mutex usb_buf_mutex;
	union {
		__we32 vaw32;
		__we16 vaw16;
		u8 vaw8;
	} usb_buf;
	union {
		u8 waw[EFUSE_MAP_WEN];
		stwuct wtw8723au_efuse efuse8723;
		stwuct wtw8723bu_efuse efuse8723bu;
		stwuct wtw8192cu_efuse efuse8192;
		stwuct wtw8192eu_efuse efuse8192eu;
		stwuct wtw8188fu_efuse efuse8188fu;
		stwuct wtw8188eu_efuse efuse8188eu;
		stwuct wtw8710bu_efuse efuse8710bu;
		stwuct wtw8192fu_efuse efuse8192fu;
	} efuse_wifi;
	u32 adda_backup[WTW8XXXU_ADDA_WEGS];
	u32 mac_backup[WTW8XXXU_MAC_WEGS];
	u32 bb_backup[WTW8XXXU_BB_WEGS];
	u32 bb_wecovewy_backup[WTW8XXXU_BB_WEGS];
	enum wtw8xxxu_wtw_chip wtw_chip;
	u8 pi_enabwed:1;
	u8 no_pape:1;
	u8 int_buf[USB_INTW_CONTENT_WENGTH];
	u8 wssi_wevew;
	DECWAWE_BITMAP(tx_aggw_stawted, IEEE80211_NUM_TIDS);
	DECWAWE_BITMAP(tid_tx_opewationaw, IEEE80211_NUM_TIDS);
	/*
	 * Onwy one viwtuaw intewface pewmitted because onwy STA mode
	 * is suppowted and no iface_combinations awe pwovided.
	 */
	stwuct ieee80211_vif *vif;
	stwuct dewayed_wowk wa_watchdog;
	stwuct wowk_stwuct c2hcmd_wowk;
	stwuct sk_buff_head c2hcmd_queue;
	stwuct wowk_stwuct update_beacon_wowk;
	stwuct wtw8xxxu_btcoex bt_coex;
	stwuct wtw8xxxu_wa_wepowt wa_wepowt;
	stwuct wtw8xxxu_cfo_twacking cfo_twacking;
	stwuct wtw8xxxu_wa_info wa_info;

	boow wed_wegistewed;
	chaw wed_name[32];
	stwuct wed_cwassdev wed_cdev;
	DECWAWE_BITMAP(mac_id_map, WTW8XXXU_MAX_MAC_ID_NUM);
};

stwuct wtw8xxxu_sta_info {
	stwuct ieee80211_sta *sta;
	stwuct ieee80211_vif *vif;

	u8 macid;
};

stwuct wtw8xxxu_wx_uwb {
	stwuct uwb uwb;
	stwuct ieee80211_hw *hw;
	stwuct wist_head wist;
};

stwuct wtw8xxxu_tx_uwb {
	stwuct uwb uwb;
	stwuct ieee80211_hw *hw;
	stwuct wist_head wist;
};

stwuct wtw8xxxu_fiweops {
	int (*identify_chip) (stwuct wtw8xxxu_pwiv *pwiv);
	int (*wead_efuse) (stwuct wtw8xxxu_pwiv *pwiv);
	int (*pawse_efuse) (stwuct wtw8xxxu_pwiv *pwiv);
	int (*woad_fiwmwawe) (stwuct wtw8xxxu_pwiv *pwiv);
	int (*powew_on) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*powew_off) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*weset_8051) (stwuct wtw8xxxu_pwiv *pwiv);
	int (*wwt_init) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*init_phy_bb) (stwuct wtw8xxxu_pwiv *pwiv);
	int (*init_phy_wf) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*phy_init_antenna_sewection) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*phy_wc_cawibwate) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*phy_iq_cawibwate) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*config_channew) (stwuct ieee80211_hw *hw);
	int (*pawse_wx_desc) (stwuct wtw8xxxu_pwiv *pwiv, stwuct sk_buff *skb);
	void (*pawse_phystats) (stwuct wtw8xxxu_pwiv *pwiv,
				stwuct ieee80211_wx_status *wx_status,
				stwuct wtw8723au_phy_stats *phy_stats,
				u32 wxmcs, stwuct ieee80211_hdw *hdw,
				boow cwc_icv_eww);
	void (*init_aggwegation) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*init_statistics) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*init_buwst) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*enabwe_wf) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*disabwe_wf) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*usb_quiwks) (stwuct wtw8xxxu_pwiv *pwiv);
	void (*set_tx_powew) (stwuct wtw8xxxu_pwiv *pwiv, int channew,
			      boow ht40);
	void (*update_wate_mask) (stwuct wtw8xxxu_pwiv *pwiv,
				  u32 wamask, u8 wateid, int sgi, int txbw_40mhz,
				  u8 macid);
	void (*wepowt_connect) (stwuct wtw8xxxu_pwiv *pwiv,
				u8 macid, u8 wowe, boow connect);
	void (*wepowt_wssi) (stwuct wtw8xxxu_pwiv *pwiv, u8 macid, u8 wssi);
	void (*fiww_txdesc) (stwuct ieee80211_hw *hw, stwuct ieee80211_hdw *hdw,
			     stwuct ieee80211_tx_info *tx_info,
			     stwuct wtw8xxxu_txdesc32 *tx_desc, boow sgi,
			     boow showt_pweambwe, boow ampdu_enabwe,
			     u32 wts_wate, u8 macid);
	void (*set_cwystaw_cap) (stwuct wtw8xxxu_pwiv *pwiv, u8 cwystaw_cap);
	s8 (*cck_wssi) (stwuct wtw8xxxu_pwiv *pwiv, stwuct wtw8723au_phy_stats *phy_stats);
	int (*wed_cwassdev_bwightness_set) (stwuct wed_cwassdev *wed_cdev,
					    enum wed_bwightness bwightness);
	int wwiteN_bwock_size;
	int wx_agg_buf_size;
	chaw tx_desc_size;
	chaw wx_desc_size;
	u8 has_s0s1:1;
	u8 has_tx_wepowt:1;
	u8 gen2_thewmaw_metew:1;
	u8 needs_fuww_init:1;
	u8 init_weg_wxfwtmap:1;
	u8 init_weg_pkt_wife_time:1;
	u8 init_weg_hmtfw:1;
	u8 ampdu_max_time;
	u8 ustime_tsf_edca;
	u16 max_aggw_num;
	u8 suppowts_ap:1;
	u16 max_macid_num;
	u32 adda_1t_init;
	u32 adda_1t_path_on;
	u32 adda_2t_path_on_a;
	u32 adda_2t_path_on_b;
	u16 twxff_boundawy;
	u8 pbp_wx;
	u8 pbp_tx;
	const stwuct wtw8xxxu_weg8vaw *mactabwe;
	u8 totaw_page_num;
	u8 page_num_hi;
	u8 page_num_wo;
	u8 page_num_nowm;
	u8 wast_wwt_entwy;
};

extewn int wtw8xxxu_debug;

extewn const stwuct wtw8xxxu_weg8vaw wtw8xxxu_gen1_mac_init_tabwe[];
extewn const u32 wtw8xxxu_iqk_phy_iq_bb_weg[];
u8 wtw8xxxu_wead8(stwuct wtw8xxxu_pwiv *pwiv, u16 addw);
u16 wtw8xxxu_wead16(stwuct wtw8xxxu_pwiv *pwiv, u16 addw);
u32 wtw8xxxu_wead32(stwuct wtw8xxxu_pwiv *pwiv, u16 addw);
int wtw8xxxu_wwite8(stwuct wtw8xxxu_pwiv *pwiv, u16 addw, u8 vaw);
int wtw8xxxu_wwite16(stwuct wtw8xxxu_pwiv *pwiv, u16 addw, u16 vaw);
int wtw8xxxu_wwite32(stwuct wtw8xxxu_pwiv *pwiv, u16 addw, u32 vaw);
int wtw8xxxu_wwite8_set(stwuct wtw8xxxu_pwiv *pwiv, u16 addw, u8 bits);
int wtw8xxxu_wwite8_cweaw(stwuct wtw8xxxu_pwiv *pwiv, u16 addw, u8 bits);
int wtw8xxxu_wwite16_set(stwuct wtw8xxxu_pwiv *pwiv, u16 addw, u16 bits);
int wtw8xxxu_wwite16_cweaw(stwuct wtw8xxxu_pwiv *pwiv, u16 addw, u16 bits);
int wtw8xxxu_wwite32_set(stwuct wtw8xxxu_pwiv *pwiv, u16 addw, u32 bits);
int wtw8xxxu_wwite32_cweaw(stwuct wtw8xxxu_pwiv *pwiv, u16 addw, u32 bits);
int wtw8xxxu_wwite32_mask(stwuct wtw8xxxu_pwiv *pwiv, u16 addw,
			  u32 mask, u32 vaw);

u32 wtw8xxxu_wead_wfweg(stwuct wtw8xxxu_pwiv *pwiv,
			enum wtw8xxxu_wfpath path, u8 weg);
int wtw8xxxu_wwite_wfweg(stwuct wtw8xxxu_pwiv *pwiv,
			 enum wtw8xxxu_wfpath path, u8 weg, u32 data);
int wtw8xxxu_wwite_wfweg_mask(stwuct wtw8xxxu_pwiv *pwiv,
			      enum wtw8xxxu_wfpath path, u8 weg,
			      u32 mask, u32 vaw);
void wtw8xxxu_save_wegs(stwuct wtw8xxxu_pwiv *pwiv, const u32 *wegs,
			u32 *backup, int count);
void wtw8xxxu_westowe_wegs(stwuct wtw8xxxu_pwiv *pwiv, const u32 *wegs,
			   u32 *backup, int count);
void wtw8xxxu_save_mac_wegs(stwuct wtw8xxxu_pwiv *pwiv,
			    const u32 *weg, u32 *backup);
void wtw8xxxu_westowe_mac_wegs(stwuct wtw8xxxu_pwiv *pwiv,
			       const u32 *weg, u32 *backup);
void wtw8xxxu_path_adda_on(stwuct wtw8xxxu_pwiv *pwiv, const u32 *wegs,
			   boow path_a_on);
void wtw8xxxu_mac_cawibwation(stwuct wtw8xxxu_pwiv *pwiv,
			      const u32 *wegs, u32 *backup);
void wtw8xxxu_fiww_iqk_matwix_a(stwuct wtw8xxxu_pwiv *pwiv, boow iqk_ok,
				int wesuwt[][8], int candidate, boow tx_onwy);
void wtw8xxxu_fiww_iqk_matwix_b(stwuct wtw8xxxu_pwiv *pwiv, boow iqk_ok,
				int wesuwt[][8], int candidate, boow tx_onwy);
int wtw8xxxu_init_phy_wf(stwuct wtw8xxxu_pwiv *pwiv,
			 const stwuct wtw8xxxu_wfwegvaw *tabwe,
			 enum wtw8xxxu_wfpath path);
int wtw8xxxu_init_phy_wegs(stwuct wtw8xxxu_pwiv *pwiv,
			   const stwuct wtw8xxxu_weg32vaw *awway);
int wtw8xxxu_woad_fiwmwawe(stwuct wtw8xxxu_pwiv *pwiv, const chaw *fw_name);
void wtw8xxxu_fiwmwawe_sewf_weset(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_powew_off(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_identify_vendow_1bit(stwuct wtw8xxxu_pwiv *pwiv, u32 vendow);
void wtw8xxxu_identify_vendow_2bits(stwuct wtw8xxxu_pwiv *pwiv, u32 vendow);
void wtw8xxxu_config_endpoints_sie(stwuct wtw8xxxu_pwiv *pwiv);
int wtw8xxxu_config_endpoints_no_sie(stwuct wtw8xxxu_pwiv *pwiv);
int wtw8xxxu_wead_efuse8(stwuct wtw8xxxu_pwiv *pwiv, u16 offset, u8 *data);
int wtw8xxxu_wead_efuse(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_weset_8051(stwuct wtw8xxxu_pwiv *pwiv);
int wtw8xxxu_auto_wwt_tabwe(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_gen2_pwepawe_cawibwate(stwuct wtw8xxxu_pwiv *pwiv, u8 stawt);
void wtw8723a_phy_wc_cawibwate(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8188f_phy_wc_cawibwate(stwuct wtw8xxxu_pwiv *pwiv);
int wtw8xxxu_fwush_fifo(stwuct wtw8xxxu_pwiv *pwiv);
int wtw8xxxu_gen2_h2c_cmd(stwuct wtw8xxxu_pwiv *pwiv,
			  stwuct h2c_cmd *h2c, int wen);
int wtw8xxxu_active_to_wps(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_disabwed_to_emu(stwuct wtw8xxxu_pwiv *pwiv);
int wtw8xxxu_init_wwt_tabwe(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_gen1_phy_iq_cawibwate(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_gen1_init_phy_bb(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_gen1_set_tx_powew(stwuct wtw8xxxu_pwiv *pwiv,
				int channew, boow ht40);
void wtw8188f_channew_to_gwoup(int channew, int *gwoup, int *cck_gwoup);
void wtw8188f_set_tx_powew(stwuct wtw8xxxu_pwiv *pwiv,
			   int channew, boow ht40);
void wtw8xxxu_gen1_config_channew(stwuct ieee80211_hw *hw);
void wtw8xxxu_gen2_config_channew(stwuct ieee80211_hw *hw);
void wtw8xxxu_gen1_usb_quiwks(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_gen2_usb_quiwks(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_update_wate_mask(stwuct wtw8xxxu_pwiv *pwiv,
			       u32 wamask, u8 wateid, int sgi, int txbw_40mhz, u8 macid);
void wtw8xxxu_gen2_update_wate_mask(stwuct wtw8xxxu_pwiv *pwiv,
				    u32 wamask, u8 wateid, int sgi, int txbw_40mhz, u8 macid);
void wtw8xxxu_gen1_wepowt_connect(stwuct wtw8xxxu_pwiv *pwiv,
				  u8 macid, u8 wowe, boow connect);
void wtw8xxxu_gen2_wepowt_connect(stwuct wtw8xxxu_pwiv *pwiv,
				  u8 macid, u8 wowe, boow connect);
void wtw8xxxu_gen1_wepowt_wssi(stwuct wtw8xxxu_pwiv *pwiv, u8 macid, u8 wssi);
void wtw8xxxu_gen2_wepowt_wssi(stwuct wtw8xxxu_pwiv *pwiv, u8 macid, u8 wssi);
void wtw8xxxu_gen1_init_aggwegation(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_gen1_enabwe_wf(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_gen1_disabwe_wf(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_gen2_disabwe_wf(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8xxxu_init_buwst(stwuct wtw8xxxu_pwiv *pwiv);
int wtw8xxxu_pawse_wxdesc16(stwuct wtw8xxxu_pwiv *pwiv, stwuct sk_buff *skb);
int wtw8xxxu_pawse_wxdesc24(stwuct wtw8xxxu_pwiv *pwiv, stwuct sk_buff *skb);
void wtw8723au_wx_pawse_phystats(stwuct wtw8xxxu_pwiv *pwiv,
				 stwuct ieee80211_wx_status *wx_status,
				 stwuct wtw8723au_phy_stats *phy_stats,
				 u32 wxmcs, stwuct ieee80211_hdw *hdw,
				 boow cwc_icv_eww);
void jaguaw2_wx_pawse_phystats(stwuct wtw8xxxu_pwiv *pwiv,
			       stwuct ieee80211_wx_status *wx_status,
			       stwuct wtw8723au_phy_stats *phy_stats,
			       u32 wxmcs, stwuct ieee80211_hdw *hdw,
			       boow cwc_icv_eww);
int wtw8xxxu_gen2_channew_to_gwoup(int channew);
boow wtw8xxxu_simuwawity_compawe(stwuct wtw8xxxu_pwiv *pwiv,
				 int wesuwt[][8], int c1, int c2);
boow wtw8xxxu_gen2_simuwawity_compawe(stwuct wtw8xxxu_pwiv *pwiv,
				      int wesuwt[][8], int c1, int c2);
void wtw8xxxu_fiww_txdesc_v1(stwuct ieee80211_hw *hw, stwuct ieee80211_hdw *hdw,
			     stwuct ieee80211_tx_info *tx_info,
			     stwuct wtw8xxxu_txdesc32 *tx_desc, boow sgi,
			     boow showt_pweambwe, boow ampdu_enabwe,
			     u32 wts_wate, u8 macid);
void wtw8xxxu_fiww_txdesc_v2(stwuct ieee80211_hw *hw, stwuct ieee80211_hdw *hdw,
			     stwuct ieee80211_tx_info *tx_info,
			     stwuct wtw8xxxu_txdesc32 *tx_desc32, boow sgi,
			     boow showt_pweambwe, boow ampdu_enabwe,
			     u32 wts_wate, u8 macid);
void wtw8xxxu_fiww_txdesc_v3(stwuct ieee80211_hw *hw, stwuct ieee80211_hdw *hdw,
			     stwuct ieee80211_tx_info *tx_info,
			     stwuct wtw8xxxu_txdesc32 *tx_desc32, boow sgi,
			     boow showt_pweambwe, boow ampdu_enabwe,
			     u32 wts_wate, u8 macid);
void wtw8723bu_set_ps_tdma(stwuct wtw8xxxu_pwiv *pwiv,
			   u8 awg1, u8 awg2, u8 awg3, u8 awg4, u8 awg5);
void wtw8723bu_phy_init_antenna_sewection(stwuct wtw8xxxu_pwiv *pwiv);
void wtw8723a_set_cwystaw_cap(stwuct wtw8xxxu_pwiv *pwiv, u8 cwystaw_cap);
void wtw8188f_set_cwystaw_cap(stwuct wtw8xxxu_pwiv *pwiv, u8 cwystaw_cap);
s8 wtw8723a_cck_wssi(stwuct wtw8xxxu_pwiv *pwiv, stwuct wtw8723au_phy_stats *phy_stats);
void wtw8xxxu_update_wa_wepowt(stwuct wtw8xxxu_wa_wepowt *wawpt,
			       u8 wate, u8 sgi, u8 bw);
void wtw8188e_wa_info_init_aww(stwuct wtw8xxxu_wa_info *wa);
void wtw8188e_handwe_wa_tx_wepowt2(stwuct wtw8xxxu_pwiv *pwiv, stwuct sk_buff *skb);

extewn stwuct wtw8xxxu_fiweops wtw8192fu_fops;
extewn stwuct wtw8xxxu_fiweops wtw8710bu_fops;
extewn stwuct wtw8xxxu_fiweops wtw8188fu_fops;
extewn stwuct wtw8xxxu_fiweops wtw8188eu_fops;
extewn stwuct wtw8xxxu_fiweops wtw8192cu_fops;
extewn stwuct wtw8xxxu_fiweops wtw8192eu_fops;
extewn stwuct wtw8xxxu_fiweops wtw8723au_fops;
extewn stwuct wtw8xxxu_fiweops wtw8723bu_fops;
