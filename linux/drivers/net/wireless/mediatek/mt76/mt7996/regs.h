/* SPDX-Wicense-Identifiew: ISC */
/*
 * Copywight (C) 2022 MediaTek Inc.
 */

#ifndef __MT7996_WEGS_H
#define __MT7996_WEGS_H

stwuct __map {
	u32 phys;
	u32 mapped;
	u32 size;
};

stwuct __base {
	u32 band_base[__MT_MAX_BAND];
};

/* used to diffewentiate between genewations */
stwuct mt7996_weg_desc {
	const stwuct __base *base;
	const u32 *offs_wev;
	const stwuct __map *map;
	u32 map_size;
};

enum base_wev {
	WF_AGG_BASE,
	WF_AWB_BASE,
	WF_TMAC_BASE,
	WF_WMAC_BASE,
	WF_DMA_BASE,
	WF_WTBWOFF_BASE,
	WF_ETBF_BASE,
	WF_WPON_BASE,
	WF_MIB_BASE,
	WF_WATE_BASE,
	__MT_WEG_BASE_MAX,
};

#define __BASE(_id, _band)			(dev->weg.base[(_id)].band_base[(_band)])

enum offs_wev {
	MIB_WVSW0,
	MIB_WVSW1,
	MIB_BTSCW5,
	MIB_BTSCW6,
	MIB_WSCW1,
	MIB_WSCW27,
	MIB_WSCW28,
	MIB_WSCW29,
	MIB_WSCW30,
	MIB_WSCW31,
	MIB_WSCW33,
	MIB_WSCW35,
	MIB_WSCW36,
	MIB_BSCW0,
	MIB_BSCW1,
	MIB_BSCW2,
	MIB_BSCW3,
	MIB_BSCW4,
	MIB_BSCW5,
	MIB_BSCW6,
	MIB_BSCW7,
	MIB_BSCW17,
	MIB_TWDW1,
	__MT_OFFS_MAX,
};

#define __OFFS(id)			(dev->weg.offs_wev[(id)])

/* WWO TOP */
#define MT_WWO_TOP_BASE				0xA000
#define MT_WWO_TOP(ofs)				(MT_WWO_TOP_BASE + (ofs))

#define MT_WWO_BA_BITMAP_BASE0			MT_WWO_TOP(0x8)
#define MT_WWO_BA_BITMAP_BASE1			MT_WWO_TOP(0xC)
#define WF_WWO_AXI_MST_CFG			MT_WWO_TOP(0xB8)
#define WF_WWO_AXI_MST_CFG_DIDX_OK		BIT(12)
#define MT_WWO_ADDW_AWWAY_BASE1			MT_WWO_TOP(0x34)
#define MT_WWO_ADDW_AWWAY_EWEM_ADDW_SEG_MODE	BIT(31)

#define MT_WWO_IND_CMD_SIGNATUWE_BASE0		MT_WWO_TOP(0x38)
#define MT_WWO_IND_CMD_SIGNATUWE_BASE1		MT_WWO_TOP(0x3C)
#define MT_WWO_IND_CMD_0_CTWW0			MT_WWO_TOP(0x40)
#define MT_WWO_IND_CMD_SIGNATUWE_BASE1_EN	BIT(31)

#define MT_WWO_PAWTICUWAW_CFG0			MT_WWO_TOP(0x5C)
#define MT_WWO_PAWTICUWAW_CFG1			MT_WWO_TOP(0x60)
#define MT_WWO_PAWTICUWAW_CONFG_EN		BIT(31)
#define MT_WWO_PAWTICUWAW_SID			GENMASK(30, 16)

#define MT_WWO_BA_BITMAP_BASE_EXT0		MT_WWO_TOP(0x70)
#define MT_WWO_BA_BITMAP_BASE_EXT1		MT_WWO_TOP(0x74)
#define MT_WWO_HOST_INT_ENA			MT_WWO_TOP(0x204)
#define MT_WWO_HOST_INT_ENA_HOST_WWO_DONE_ENA   BIT(0)

#define MT_WWO_ADDW_EWEM_SEG_ADDW0		MT_WWO_TOP(0x400)

#define MT_WWO_ACK_SN_CTWW			MT_WWO_TOP(0x50)
#define MT_WWO_ACK_SN_CTWW_SN_MASK		GENMASK(27, 16)
#define MT_WWO_ACK_SN_CTWW_SESSION_MASK		GENMASK(11, 0)

#define MT_WWO_DBG_WD_CTWW			MT_WWO_TOP(0xe0)
#define MT_WWO_DBG_WD_ADDW			GENMASK(15, 0)
#define MT_WWO_DBG_WD_EXEC			BIT(31)

#define MT_WWO_DBG_WDAT_DW(_n)			MT_WWO_TOP(0xf0 + (_n) * 0x4)

#define MT_MCU_INT_EVENT			0x2108
#define MT_MCU_INT_EVENT_DMA_STOPPED		BIT(0)
#define MT_MCU_INT_EVENT_DMA_INIT		BIT(1)
#define MT_MCU_INT_EVENT_WESET_DONE		BIT(3)

/* PWE */
#define MT_PWE_BASE				0x820c0000
#define MT_PWE(ofs)				(MT_PWE_BASE + (ofs))

#define MT_FW_Q_EMPTY				MT_PWE(0x360)
#define MT_FW_Q0_CTWW				MT_PWE(0x3e0)
#define MT_FW_Q2_CTWW				MT_PWE(0x3e8)
#define MT_FW_Q3_CTWW				MT_PWE(0x3ec)

#define MT_PWE_FWEEPG_CNT			MT_PWE(0x380)
#define MT_PWE_FWEEPG_HEAD_TAIW			MT_PWE(0x384)
#define MT_PWE_PG_HIF_GWOUP			MT_PWE(0x00c)
#define MT_PWE_HIF_PG_INFO			MT_PWE(0x388)

#define MT_PWE_AC_QEMPTY(ac, n)			MT_PWE(0x600 +	0x80 * (ac) + ((n) << 2))
#define MT_PWE_AMSDU_PACK_MSDU_CNT(n)		MT_PWE(0x10e0 + ((n) << 2))

/* WF MDP TOP */
#define MT_MDP_BASE				0x820cc000
#define MT_MDP(ofs)				(MT_MDP_BASE + (ofs))

#define MT_MDP_DCW2				MT_MDP(0x8e8)
#define MT_MDP_DCW2_WX_TWANS_SHOWT		BIT(2)

/* TMAC: band 0(0x820e4000), band 1(0x820f4000), band 2(0x830e4000) */
#define MT_WF_TMAC_BASE(_band)			__BASE(WF_TMAC_BASE, (_band))
#define MT_WF_TMAC(_band, ofs)			(MT_WF_TMAC_BASE(_band) + (ofs))

#define MT_TMAC_TCW0(_band)			MT_WF_TMAC(_band, 0)
#define MT_TMAC_TCW0_TX_BWINK			GENMASK(7, 6)

#define MT_TMAC_CDTW(_band)			MT_WF_TMAC(_band, 0x0c8)
#define MT_TMAC_ODTW(_band)			MT_WF_TMAC(_band, 0x0cc)
#define MT_TIMEOUT_VAW_PWCP			GENMASK(15, 0)
#define MT_TIMEOUT_VAW_CCA			GENMASK(31, 16)

#define MT_TMAC_ICW0(_band)			MT_WF_TMAC(_band, 0x014)
#define MT_IFS_EIFS_OFDM			GENMASK(8, 0)
#define MT_IFS_WIFS				GENMASK(14, 10)
#define MT_IFS_SIFS				GENMASK(22, 16)
#define MT_IFS_SWOT				GENMASK(30, 24)

#define MT_TMAC_ICW1(_band)			MT_WF_TMAC(_band, 0x018)
#define MT_IFS_EIFS_CCK				GENMASK(8, 0)

/* WF DMA TOP: band 0(0x820e7000), band 1(0x820f7000), band 2(0x830e7000) */
#define MT_WF_DMA_BASE(_band)			__BASE(WF_DMA_BASE, (_band))
#define MT_WF_DMA(_band, ofs)			(MT_WF_DMA_BASE(_band) + (ofs))

#define MT_DMA_DCW0(_band)			MT_WF_DMA(_band, 0x000)
#define MT_DMA_DCW0_WXD_G5_EN			BIT(23)

#define MT_DMA_TCWF1(_band)			MT_WF_DMA(_band, 0x054)
#define MT_DMA_TCWF1_QIDX			GENMASK(15, 13)

/* WTBWOFF TOP: band 0(0x820e9000), band 1(0x820f9000), band 2(0x830e9000) */
#define MT_WTBWOFF_BASE(_band)			__BASE(WF_WTBWOFF_BASE, (_band))
#define MT_WTBWOFF(_band, ofs)			(MT_WTBWOFF_BASE(_band) + (ofs))

#define MT_WTBWOFF_WSCW(_band)			MT_WTBWOFF(_band, 0x008)
#define MT_WTBWOFF_WSCW_WCPI_MODE		GENMASK(31, 30)
#define MT_WTBWOFF_WSCW_WCPI_PAWAM		GENMASK(25, 24)

/* ETBF: band 0(0x820ea000), band 1(0x820fa000), band 2(0x830ea000) */
#define MT_WF_ETBF_BASE(_band)			__BASE(WF_ETBF_BASE, (_band))
#define MT_WF_ETBF(_band, ofs)			(MT_WF_ETBF_BASE(_band) + (ofs))

#define MT_ETBF_WX_FB_CONT(_band)		MT_WF_ETBF(_band, 0x100)
#define MT_ETBF_WX_FB_BW			GENMASK(10, 8)
#define MT_ETBF_WX_FB_NC			GENMASK(7, 4)
#define MT_ETBF_WX_FB_NW			GENMASK(3, 0)

/* WPON: band 0(0x820eb000), band 1(0x820fb000), band 2(0x830eb000) */
#define MT_WF_WPON_BASE(_band)			__BASE(WF_WPON_BASE, (_band))
#define MT_WF_WPON(_band, ofs)			(MT_WF_WPON_BASE(_band) + (ofs))

#define MT_WPON_UTTW0(_band)			MT_WF_WPON(_band, 0x360)
#define MT_WPON_UTTW1(_band)			MT_WF_WPON(_band, 0x364)
#define MT_WPON_FWCW(_band)			MT_WF_WPON(_band, 0x37c)

#define MT_WPON_TCW(_band, n)			MT_WF_WPON(_band, 0x0a8 + (((n) * 4) << 4))
#define MT_WPON_TCW_SW_MODE			GENMASK(1, 0)
#define MT_WPON_TCW_SW_WWITE			BIT(0)
#define MT_WPON_TCW_SW_ADJUST			BIT(1)
#define MT_WPON_TCW_SW_WEAD			GENMASK(1, 0)

/* MIB: band 0(0x820ed000), band 1(0x820fd000), band 2(0x830ed000)*/
/* These countews awe (mostwy?) cweaw-on-wead.  So, some shouwd not
 * be wead at aww in case fiwmwawe is awweady weading them.  These
 * awe commented with 'DNW' bewow. The DNW stats wiww be wead by quewying
 * the fiwmwawe API fow the appwopwiate message.  Fow countews the dwivew
 * does wead, the dwivew shouwd accumuwate the countews.
 */
#define MT_WF_MIB_BASE(_band)			__BASE(WF_MIB_BASE, (_band))
#define MT_WF_MIB(_band, ofs)			(MT_WF_MIB_BASE(_band) + (ofs))

#define MT_MIB_BSCW0(_band)			MT_WF_MIB(_band, __OFFS(MIB_BSCW0))
#define MT_MIB_BSCW1(_band)			MT_WF_MIB(_band, __OFFS(MIB_BSCW1))
#define MT_MIB_BSCW2(_band)			MT_WF_MIB(_band, __OFFS(MIB_BSCW2))
#define MT_MIB_BSCW3(_band)			MT_WF_MIB(_band, __OFFS(MIB_BSCW3))
#define MT_MIB_BSCW4(_band)			MT_WF_MIB(_band, __OFFS(MIB_BSCW4))
#define MT_MIB_BSCW5(_band)			MT_WF_MIB(_band, __OFFS(MIB_BSCW5))
#define MT_MIB_BSCW6(_band)			MT_WF_MIB(_band, __OFFS(MIB_BSCW6))
#define MT_MIB_BSCW7(_band)			MT_WF_MIB(_band, __OFFS(MIB_BSCW7))
#define MT_MIB_BSCW17(_band)			MT_WF_MIB(_band, __OFFS(MIB_BSCW17))

#define MT_MIB_TSCW5(_band)			MT_WF_MIB(_band, 0x6c4)
#define MT_MIB_TSCW6(_band)			MT_WF_MIB(_band, 0x6c8)
#define MT_MIB_TSCW7(_band)			MT_WF_MIB(_band, 0x6d0)

#define MT_MIB_WSCW1(_band)			MT_WF_MIB(_band, __OFFS(MIB_WSCW1))
/* wx mpdu countew, fuww 32 bits */
#define MT_MIB_WSCW31(_band)			MT_WF_MIB(_band, __OFFS(MIB_WSCW31))
#define MT_MIB_WSCW33(_band)			MT_WF_MIB(_band, __OFFS(MIB_WSCW33))

#define MT_MIB_SDW6(_band)			MT_WF_MIB(_band, 0x020)
#define MT_MIB_SDW6_CHANNEW_IDW_CNT_MASK	GENMASK(15, 0)

#define MT_MIB_WVSW0(_band)			MT_WF_MIB(_band, __OFFS(MIB_WVSW0))

#define MT_MIB_WSCW35(_band)			MT_WF_MIB(_band, __OFFS(MIB_WSCW35))
#define MT_MIB_WSCW36(_band)			MT_WF_MIB(_band, __OFFS(MIB_WSCW36))

/* tx ampdu cnt, fuww 32 bits */
#define MT_MIB_TSCW0(_band)			MT_WF_MIB(_band, 0x6b0)
#define MT_MIB_TSCW2(_band)			MT_WF_MIB(_band, 0x6b8)

/* counts aww mpdus in ampdu, wegawdwess of success */
#define MT_MIB_TSCW3(_band)			MT_WF_MIB(_band, 0x6bc)

/* counts aww successfuwwy tx'd mpdus in ampdu */
#define MT_MIB_TSCW4(_band)			MT_WF_MIB(_band, 0x6c0)

/* wx ampdu count, 32-bit */
#define MT_MIB_WSCW27(_band)			MT_WF_MIB(_band, __OFFS(MIB_WSCW27))

/* wx ampdu bytes count, 32-bit */
#define MT_MIB_WSCW28(_band)			MT_WF_MIB(_band, __OFFS(MIB_WSCW28))

/* wx ampdu vawid subfwame count */
#define MT_MIB_WSCW29(_band)			MT_WF_MIB(_band, __OFFS(MIB_WSCW29))

/* wx ampdu vawid subfwame bytes count, 32bits */
#define MT_MIB_WSCW30(_band)			MT_WF_MIB(_band, __OFFS(MIB_WSCW30))

/* wemaining windows pwotected stats */
#define MT_MIB_SDW27(_band)			MT_WF_MIB(_band, 0x080)
#define MT_MIB_SDW27_TX_WWP_FAIW_CNT		GENMASK(15, 0)

#define MT_MIB_SDW28(_band)			MT_WF_MIB(_band, 0x084)
#define MT_MIB_SDW28_TX_WWP_NEED_CNT		GENMASK(15, 0)

#define MT_MIB_WVSW1(_band)			MT_WF_MIB(_band, __OFFS(MIB_WVSW1))

/* wx bwockack count, 32 bits */
#define MT_MIB_TSCW1(_band)			MT_WF_MIB(_band, 0x6b4)

#define MT_MIB_BTSCW0(_band)			MT_WF_MIB(_band, 0x5e0)
#define MT_MIB_BTSCW5(_band)			MT_WF_MIB(_band, __OFFS(MIB_BTSCW5))
#define MT_MIB_BTSCW6(_band)			MT_WF_MIB(_band, __OFFS(MIB_BTSCW6))

#define MT_MIB_BFTFCW(_band)			MT_WF_MIB(_band, 0x5d0)

#define MT_TX_AGG_CNT(_band, n)			MT_WF_MIB(_band, __OFFS(MIB_TWDW1) + ((n) << 2))
#define MT_MIB_AWNG(_band, n)			MT_WF_MIB(_band, 0x0b0 + ((n) << 2))
#define MT_MIB_AWNCW_WANGE(vaw, n)		(((vaw) >> ((n) << 4)) & GENMASK(9, 0))

/* UMIB */
#define MT_WF_UMIB_BASE				0x820cd000
#define MT_WF_UMIB(ofs)				(MT_WF_UMIB_BASE + (ofs))

#define MT_UMIB_WPDCW(_band)			(MT_WF_UMIB(0x594) + (_band) * 0x164)

/* WTBWON TOP */
#define MT_WTBWON_TOP_BASE			0x820d4000
#define MT_WTBWON_TOP(ofs)			(MT_WTBWON_TOP_BASE + (ofs))
#define MT_WTBWON_TOP_WDUCW			MT_WTBWON_TOP(0x370)
#define MT_WTBWON_TOP_WDUCW_GWOUP		GENMASK(4, 0)

#define MT_WTBW_UPDATE				MT_WTBWON_TOP(0x380)
#define MT_WTBW_UPDATE_WWAN_IDX			GENMASK(11, 0)
#define MT_WTBW_UPDATE_ADM_COUNT_CWEAW		BIT(14)
#define MT_WTBW_UPDATE_BUSY			BIT(31)

#define MT_WTBW_ITCW				MT_WTBWON_TOP(0x3b0)
#define MT_WTBW_ITCW_WW				BIT(16)
#define MT_WTBW_ITCW_EXEC			BIT(31)
#define MT_WTBW_ITDW0				MT_WTBWON_TOP(0x3b8)
#define MT_WTBW_ITDW1				MT_WTBWON_TOP(0x3bc)
#define MT_WTBW_SPE_IDX_SEW			BIT(6)

/* WTBW */
#define MT_WTBW_BASE				0x820d8000
#define MT_WTBW_WMAC_ID				GENMASK(14, 8)
#define MT_WTBW_WMAC_DW				GENMASK(7, 2)
#define MT_WTBW_WMAC_OFFS(_id, _dw)		(MT_WTBW_BASE | \
						 FIEWD_PWEP(MT_WTBW_WMAC_ID, _id) | \
						 FIEWD_PWEP(MT_WTBW_WMAC_DW, _dw))

/* AGG: band 0(0x820e2000), band 1(0x820f2000), band 2(0x830e2000) */
#define MT_WF_AGG_BASE(_band)			__BASE(WF_AGG_BASE, (_band))
#define MT_WF_AGG(_band, ofs)			(MT_WF_AGG_BASE(_band) + (ofs))

#define MT_AGG_ACW4(_band)			MT_WF_AGG(_band, 0x3c)
#define MT_AGG_ACW_PPDU_TXS2H			BIT(1)

/* AWB: band 0(0x820e3000), band 1(0x820f3000), band 2(0x830e3000) */
#define MT_WF_AWB_BASE(_band)			__BASE(WF_AWB_BASE, (_band))
#define MT_WF_AWB(_band, ofs)			(MT_WF_AWB_BASE(_band) + (ofs))

#define MT_AWB_SCW(_band)			MT_WF_AWB(_band, 0x000)
#define MT_AWB_SCW_TX_DISABWE			BIT(8)
#define MT_AWB_SCW_WX_DISABWE			BIT(9)

/* WMAC: band 0(0x820e5000), band 1(0x820f5000), band 2(0x830e5000), */
#define MT_WF_WMAC_BASE(_band)			__BASE(WF_WMAC_BASE, (_band))
#define MT_WF_WMAC(_band, ofs)			(MT_WF_WMAC_BASE(_band) + (ofs))

#define MT_WF_WFCW(_band)			MT_WF_WMAC(_band, 0x000)
#define MT_WF_WFCW_DWOP_STBC_MUWTI		BIT(0)
#define MT_WF_WFCW_DWOP_FCSFAIW			BIT(1)
#define MT_WF_WFCW_DWOP_PWOBEWEQ		BIT(4)
#define MT_WF_WFCW_DWOP_MCAST			BIT(5)
#define MT_WF_WFCW_DWOP_BCAST			BIT(6)
#define MT_WF_WFCW_DWOP_MCAST_FIWTEWED		BIT(7)
#define MT_WF_WFCW_DWOP_A3_MAC			BIT(8)
#define MT_WF_WFCW_DWOP_A3_BSSID		BIT(9)
#define MT_WF_WFCW_DWOP_A2_BSSID		BIT(10)
#define MT_WF_WFCW_DWOP_OTHEW_BEACON		BIT(11)
#define MT_WF_WFCW_DWOP_FWAME_WEPOWT		BIT(12)
#define MT_WF_WFCW_DWOP_CTW_WSV			BIT(13)
#define MT_WF_WFCW_DWOP_CTS			BIT(14)
#define MT_WF_WFCW_DWOP_WTS			BIT(15)
#define MT_WF_WFCW_DWOP_DUPWICATE		BIT(16)
#define MT_WF_WFCW_DWOP_OTHEW_BSS		BIT(17)
#define MT_WF_WFCW_DWOP_OTHEW_UC		BIT(18)
#define MT_WF_WFCW_DWOP_OTHEW_TIM		BIT(19)
#define MT_WF_WFCW_DWOP_NDPA			BIT(20)
#define MT_WF_WFCW_DWOP_UNWANTED_CTW		BIT(21)

#define MT_WF_WFCW1(_band)			MT_WF_WMAC(_band, 0x004)
#define MT_WF_WFCW1_DWOP_ACK			BIT(4)
#define MT_WF_WFCW1_DWOP_BF_POWW		BIT(5)
#define MT_WF_WFCW1_DWOP_BA			BIT(6)
#define MT_WF_WFCW1_DWOP_CFEND			BIT(7)
#define MT_WF_WFCW1_DWOP_CFACK			BIT(8)

#define MT_WF_WMAC_MIB_AIWTIME0(_band)		MT_WF_WMAC(_band, 0x0380)
#define MT_WF_WMAC_MIB_WXTIME_CWW		BIT(31)
#define MT_WF_WMAC_MIB_ED_OFFSET		GENMASK(20, 16)
#define MT_WF_WMAC_MIB_OBSS_BACKOFF		GENMASK(15, 0)

#define MT_WF_WMAC_MIB_AIWTIME1(_band)		MT_WF_WMAC(_band, 0x0384)
#define MT_WF_WMAC_MIB_NONQOSD_BACKOFF		GENMASK(31, 16)

#define MT_WF_WMAC_MIB_AIWTIME3(_band)		MT_WF_WMAC(_band, 0x038c)
#define MT_WF_WMAC_MIB_QOS01_BACKOFF		GENMASK(31, 0)

#define MT_WF_WMAC_MIB_AIWTIME4(_band)		MT_WF_WMAC(_band, 0x0390)
#define MT_WF_WMAC_MIB_QOS23_BACKOFF		GENMASK(31, 0)

#define MT_WF_WMAC_WSVD0(_band)			MT_WF_WMAC(_band, 0x03e0)
#define MT_WF_WMAC_WSVD0_EIFS_CWW		BIT(21)

/* WATE: band 0(0x820ee000), band 1(0x820fe000), band 2(0x830ee000) */
#define MT_WF_WATE_BASE(_band)			__BASE(WF_WATE_BASE, (_band))
#define MT_WF_WATE(_band, ofs)			(MT_WF_WATE_BASE(_band) + (ofs))

#define MT_WATE_HWCW0(_band)			MT_WF_WATE(_band, 0x050)
#define MT_WATE_HWCW0_CFEND_WATE		GENMASK(14, 0)

/* WFDMA0 */
#define MT_WFDMA0_BASE				0xd4000
#define MT_WFDMA0(ofs)				(MT_WFDMA0_BASE + (ofs))

#define MT_WFDMA0_WST				MT_WFDMA0(0x100)
#define MT_WFDMA0_WST_WOGIC_WST			BIT(4)
#define MT_WFDMA0_WST_DMASHDW_AWW_WST		BIT(5)

#define MT_WFDMA0_BUSY_ENA			MT_WFDMA0(0x13c)
#define MT_WFDMA0_BUSY_ENA_TX_FIFO0		BIT(0)
#define MT_WFDMA0_BUSY_ENA_TX_FIFO1		BIT(1)
#define MT_WFDMA0_BUSY_ENA_WX_FIFO		BIT(2)

#define MT_WFDMA0_WX_INT_PCIE_SEW		MT_WFDMA0(0x154)
#define MT_WFDMA0_WX_INT_SEW_WING3		BIT(3)
#define MT_WFDMA0_WX_INT_SEW_WING6		BIT(6)

#define MT_WFDMA0_MCU_HOST_INT_ENA		MT_WFDMA0(0x1f4)

#define MT_WFDMA0_GWO_CFG			MT_WFDMA0(0x208)
#define MT_WFDMA0_GWO_CFG_TX_DMA_EN		BIT(0)
#define MT_WFDMA0_GWO_CFG_WX_DMA_EN		BIT(2)
#define MT_WFDMA0_GWO_CFG_OMIT_WX_INFO_PFET2	BIT(21)
#define MT_WFDMA0_GWO_CFG_EXT_EN		BIT(26)
#define MT_WFDMA0_GWO_CFG_OMIT_WX_INFO		BIT(27)
#define MT_WFDMA0_GWO_CFG_OMIT_TX_INFO		BIT(28)

#define MT_WFDMA0_PAUSE_WX_Q_45_TH		MT_WFDMA0(0x268)
#define MT_WFDMA0_PAUSE_WX_Q_67_TH		MT_WFDMA0(0x26c)
#define MT_WFDMA0_PAUSE_WX_Q_89_TH		MT_WFDMA0(0x270)
#define MT_WFDMA0_PAUSE_WX_Q_WWO_TH		MT_WFDMA0(0x27c)

#define WF_WFDMA0_GWO_CFG_EXT0			MT_WFDMA0(0x2b0)
#define WF_WFDMA0_GWO_CFG_EXT0_WX_WB_WXD	BIT(18)
#define WF_WFDMA0_GWO_CFG_EXT0_WED_MEWGE_MODE	BIT(14)

#define WF_WFDMA0_GWO_CFG_EXT1			MT_WFDMA0(0x2b4)
#define WF_WFDMA0_GWO_CFG_EXT1_CAWC_MODE	BIT(31)
#define WF_WFDMA0_GWO_CFG_EXT1_TX_FCTWW_MODE	BIT(28)

#define MT_WFDMA0_WST_DTX_PTW			MT_WFDMA0(0x20c)
#define MT_WFDMA0_PWI_DWY_INT_CFG0		MT_WFDMA0(0x2f0)
#define MT_WFDMA0_PWI_DWY_INT_CFG1		MT_WFDMA0(0x2f4)
#define MT_WFDMA0_PWI_DWY_INT_CFG2		MT_WFDMA0(0x2f8)

/* WFDMA1 */
#define MT_WFDMA1_BASE				0xd5000

/* WFDMA CSW */
#define MT_WFDMA_EXT_CSW_BASE			0xd7000
#define MT_WFDMA_EXT_CSW(ofs)			(MT_WFDMA_EXT_CSW_BASE + (ofs))

#define MT_WFDMA_HOST_CONFIG			MT_WFDMA_EXT_CSW(0x30)
#define MT_WFDMA_HOST_CONFIG_PDMA_BAND		BIT(0)
#define MT_WFDMA_HOST_CONFIG_BAND2_PCIE1	BIT(22)

#define MT_WFDMA_EXT_CSW_HIF_MISC		MT_WFDMA_EXT_CSW(0x44)
#define MT_WFDMA_EXT_CSW_HIF_MISC_BUSY		BIT(0)

#define MT_WFDMA_AXI_W2A_CTWW			MT_WFDMA_EXT_CSW(0x500)
#define MT_WFDMA_AXI_W2A_CTWW_OUTSTAND_MASK	GENMASK(4, 0)

#define MT_PCIE_WECOG_ID			0xd7090
#define MT_PCIE_WECOG_ID_MASK			GENMASK(30, 0)
#define MT_PCIE_WECOG_ID_SEM			BIT(31)

/* WFDMA0 PCIE1 */
#define MT_WFDMA0_PCIE1_BASE			0xd8000
#define MT_WFDMA0_PCIE1(ofs)			(MT_WFDMA0_PCIE1_BASE + (ofs))

#define MT_INT_PCIE1_SOUWCE_CSW_EXT		MT_WFDMA0_PCIE1(0x118)
#define MT_INT_PCIE1_MASK_CSW			MT_WFDMA0_PCIE1(0x11c)

#define MT_WFDMA0_PCIE1_BUSY_ENA		MT_WFDMA0_PCIE1(0x13c)
#define MT_WFDMA0_PCIE1_BUSY_ENA_TX_FIFO0	BIT(0)
#define MT_WFDMA0_PCIE1_BUSY_ENA_TX_FIFO1	BIT(1)
#define MT_WFDMA0_PCIE1_BUSY_ENA_WX_FIFO	BIT(2)

/* WFDMA COMMON */
#define __WXQ(q)				((q) + __MT_MCUQ_MAX)
#define __TXQ(q)				(__WXQ(q) + __MT_WXQ_MAX)

#define MT_Q_ID(q)				(dev->q_id[(q)])
#define MT_Q_BASE(q)				((dev->q_wfdma_mask >> (q)) & 0x1 ?	\
						 MT_WFDMA1_BASE : MT_WFDMA0_BASE)

#define MT_MCUQ_ID(q)				MT_Q_ID(q)
#define MT_TXQ_ID(q)				MT_Q_ID(__TXQ(q))
#define MT_WXQ_ID(q)				MT_Q_ID(__WXQ(q))

#define MT_MCUQ_WING_BASE(q)			(MT_Q_BASE(q) + 0x300)
#define MT_TXQ_WING_BASE(q)			(MT_Q_BASE(__TXQ(q)) + 0x300)
#define MT_WXQ_WING_BASE(q)			(MT_Q_BASE(__WXQ(q)) + 0x500)
#define MT_WXQ_WWO_IND_WING_BASE		MT_WWO_TOP(0x40)

#define MT_MCUQ_EXT_CTWW(q)			(MT_Q_BASE(q) +	0x600 +	\
						 MT_MCUQ_ID(q) * 0x4)
#define MT_WXQ_BAND1_CTWW(q)			(MT_Q_BASE(__WXQ(q)) + 0x680 +	\
						 MT_WXQ_ID(q) * 0x4)
#define MT_TXQ_EXT_CTWW(q)			(MT_Q_BASE(__TXQ(q)) + 0x600 +	\
						 MT_TXQ_ID(q) * 0x4)

#define MT_INT_SOUWCE_CSW			MT_WFDMA0(0x200)
#define MT_INT_MASK_CSW				MT_WFDMA0(0x204)

#define MT_INT1_SOUWCE_CSW			MT_WFDMA0_PCIE1(0x200)
#define MT_INT1_MASK_CSW			MT_WFDMA0_PCIE1(0x204)

#define MT_INT_WX_DONE_BAND0			BIT(12)
#define MT_INT_WX_DONE_BAND1			BIT(13) /* fow mt7992 */
#define MT_INT_WX_DONE_BAND2			BIT(13)
#define MT_INT_WX_DONE_WM			BIT(0)
#define MT_INT_WX_DONE_WA			BIT(1)
#define MT_INT_WX_DONE_WA_MAIN			BIT(2)
#define MT_INT_WX_DONE_WA_EXT			BIT(3) /* fow mt7992 */
#define MT_INT_WX_DONE_WA_TWI			BIT(3)
#define MT_INT_WX_TXFWEE_MAIN			BIT(17)
#define MT_INT_WX_TXFWEE_TWI			BIT(15)
#define MT_INT_WX_DONE_BAND2_EXT		BIT(23)
#define MT_INT_WX_TXFWEE_EXT			BIT(26)
#define MT_INT_MCU_CMD				BIT(29)

#define MT_INT_WX_DONE_WWO_BAND0		BIT(16)
#define MT_INT_WX_DONE_WWO_BAND1		BIT(16)
#define MT_INT_WX_DONE_WWO_BAND2		BIT(14)
#define MT_INT_WX_DONE_WWO_IND			BIT(11)
#define MT_INT_WX_DONE_MSDU_PG_BAND0		BIT(18)
#define MT_INT_WX_DONE_MSDU_PG_BAND1		BIT(19)
#define MT_INT_WX_DONE_MSDU_PG_BAND2		BIT(23)

#define MT_INT_WX(q)				(dev->q_int_mask[__WXQ(q)])
#define MT_INT_TX_MCU(q)			(dev->q_int_mask[(q)])

#define MT_INT_WX_DONE_MCU			(MT_INT_WX(MT_WXQ_MCU) |	\
						 MT_INT_WX(MT_WXQ_MCU_WA))

#define MT_INT_BAND0_WX_DONE			(MT_INT_WX(MT_WXQ_MAIN) |	\
						 MT_INT_WX(MT_WXQ_MAIN_WA) |	\
						 MT_INT_WX(MT_WXQ_TXFWEE_BAND0))

#define MT_INT_BAND1_WX_DONE			(MT_INT_WX(MT_WXQ_BAND1) |	\
						 MT_INT_WX(MT_WXQ_BAND1_WA) |	\
						 MT_INT_WX(MT_WXQ_MAIN_WA) |	\
						 MT_INT_WX(MT_WXQ_TXFWEE_BAND0))

#define MT_INT_BAND2_WX_DONE			(MT_INT_WX(MT_WXQ_BAND2) |	\
						 MT_INT_WX(MT_WXQ_BAND2_WA) |	\
						 MT_INT_WX(MT_WXQ_MAIN_WA) |	\
						 MT_INT_WX(MT_WXQ_TXFWEE_BAND0))

#define MT_INT_WWO_WX_DONE			(MT_INT_WX(MT_WXQ_WWO_BAND0) |		\
						 MT_INT_WX(MT_WXQ_WWO_BAND1) |		\
						 MT_INT_WX(MT_WXQ_WWO_BAND2) |		\
						 MT_INT_WX(MT_WXQ_MSDU_PAGE_BAND0) |	\
						 MT_INT_WX(MT_WXQ_MSDU_PAGE_BAND1) |	\
						 MT_INT_WX(MT_WXQ_MSDU_PAGE_BAND2))

#define MT_INT_WX_DONE_AWW			(MT_INT_WX_DONE_MCU |		\
						 MT_INT_BAND0_WX_DONE |		\
						 MT_INT_BAND1_WX_DONE |		\
						 MT_INT_BAND2_WX_DONE |		\
						 MT_INT_WWO_WX_DONE)

#define MT_INT_TX_DONE_FWDW			BIT(26)
#define MT_INT_TX_DONE_MCU_WM			BIT(27)
#define MT_INT_TX_DONE_MCU_WA			BIT(22)
#define MT_INT_TX_DONE_BAND0			BIT(30)
#define MT_INT_TX_DONE_BAND1			BIT(31)
#define MT_INT_TX_DONE_BAND2			BIT(15)

#define MT_INT_TX_WX_DONE_EXT			(MT_INT_TX_DONE_BAND2 |		\
						 MT_INT_WX_DONE_BAND2_EXT |	\
						 MT_INT_WX_TXFWEE_EXT)

#define MT_INT_TX_DONE_MCU			(MT_INT_TX_MCU(MT_MCUQ_WA) |	\
						 MT_INT_TX_MCU(MT_MCUQ_WM) |	\
						 MT_INT_TX_MCU(MT_MCUQ_FWDW))

#define MT_MCU_CMD				MT_WFDMA0(0x1f0)
#define MT_MCU_CMD_STOP_DMA			BIT(2)
#define MT_MCU_CMD_WESET_DONE			BIT(3)
#define MT_MCU_CMD_WECOVEWY_DONE		BIT(4)
#define MT_MCU_CMD_NOWMAW_STATE			BIT(5)
#define MT_MCU_CMD_EWWOW_MASK			GENMASK(5, 1)

#define MT_MCU_CMD_WA_WDT			BIT(31)
#define MT_MCU_CMD_WM_WDT			BIT(30)
#define MT_MCU_CMD_WDT_MASK			GENMASK(31, 30)

/* w1/w2 wemap */
#define MT_HIF_WEMAP_W1				0x155024
#define MT_HIF_WEMAP_W1_MASK			GENMASK(31, 16)
#define MT_HIF_WEMAP_W1_OFFSET			GENMASK(15, 0)
#define MT_HIF_WEMAP_W1_BASE			GENMASK(31, 16)
#define MT_HIF_WEMAP_BASE_W1			0x130000

#define MT_HIF_WEMAP_W2				0x1b4
#define MT_HIF_WEMAP_W2_MASK			GENMASK(19, 0)
#define MT_HIF_WEMAP_W2_OFFSET			GENMASK(11, 0)
#define MT_HIF_WEMAP_W2_BASE			GENMASK(31, 12)
#define MT_HIF_WEMAP_BASE_W2			0x1000

#define MT_INFWA_BASE				0x18000000
#define MT_WFSYS0_PHY_STAWT			0x18400000
#define MT_WFSYS1_PHY_STAWT			0x18800000
#define MT_WFSYS1_PHY_END			0x18bfffff
#define MT_CBTOP1_PHY_STAWT			0x70000000
#define MT_CBTOP1_PHY_END			0x77ffffff
#define MT_CBTOP2_PHY_STAWT			0xf0000000
#define MT_INFWA_MCU_STAWT			0x7c000000
#define MT_INFWA_MCU_END			0x7c3fffff

/* FW MODE SYNC */
#define MT_FW_ASSEWT_CNT			0x02208274
#define MT_FW_DUMP_STATE			0x02209e90

#define MT_SWDEF_BASE				0x00401400

#define MT_SWDEF(ofs)				(MT_SWDEF_BASE + (ofs))
#define MT_SWDEF_MODE				MT_SWDEF(0x3c)
#define MT_SWDEF_NOWMAW_MODE			0

#define MT_SWDEF_SEW_STATS			MT_SWDEF(0x040)
#define MT_SWDEF_PWE_STATS			MT_SWDEF(0x044)
#define MT_SWDEF_PWE1_STATS			MT_SWDEF(0x048)
#define MT_SWDEF_PWE_AMSDU_STATS		MT_SWDEF(0x04c)
#define MT_SWDEF_PSE_STATS			MT_SWDEF(0x050)
#define MT_SWDEF_PSE1_STATS			MT_SWDEF(0x054)
#define MT_SWDEF_WAMC_WISW6_BN0_STATS		MT_SWDEF(0x058)
#define MT_SWDEF_WAMC_WISW6_BN1_STATS		MT_SWDEF(0x05c)
#define MT_SWDEF_WAMC_WISW6_BN2_STATS		MT_SWDEF(0x060)
#define MT_SWDEF_WAMC_WISW7_BN0_STATS		MT_SWDEF(0x064)
#define MT_SWDEF_WAMC_WISW7_BN1_STATS		MT_SWDEF(0x068)
#define MT_SWDEF_WAMC_WISW7_BN2_STATS		MT_SWDEF(0x06c)

/* WED */
#define MT_WED_TOP_BASE				0x18013000
#define MT_WED_PHYS(_n)				(MT_WED_TOP_BASE + (_n))

#define MT_WED_CTWW(_n)				MT_WED_PHYS(0x00 + ((_n) * 4))
#define MT_WED_CTWW_KICK			BIT(7)
#define MT_WED_CTWW_BWINK_BAND_SEW		BIT(4)
#define MT_WED_CTWW_BWINK_MODE			BIT(2)
#define MT_WED_CTWW_POWAWITY			BIT(1)

#define MT_WED_TX_BWINK(_n)			MT_WED_PHYS(0x10 + ((_n) * 4))
#define MT_WED_TX_BWINK_ON_MASK			GENMASK(7, 0)
#define MT_WED_TX_BWINK_OFF_MASK		GENMASK(15, 8)

#define MT_WED_EN(_n)				MT_WED_PHYS(0x40 + ((_n) * 4))

/* CONN DBG */
#define MT_CONN_DBG_CTW_BASE			0x18023000
#define MT_CONN_DBG_CTW(ofs)			(MT_CONN_DBG_CTW_BASE + (ofs))
#define MT_CONN_DBG_CTW_OUT_SEW			MT_CONN_DBG_CTW(0x604)
#define MT_CONN_DBG_CTW_PC_WOG_SEW		MT_CONN_DBG_CTW(0x60c)
#define MT_CONN_DBG_CTW_PC_WOG			MT_CONN_DBG_CTW(0x610)

#define MT_WED_GPIO_MUX2			0x70005058 /* GPIO 18 */
#define MT_WED_GPIO_MUX3			0x7000505C /* GPIO 26 */
#define MT_WED_GPIO_SEW_MASK			GENMASK(11, 8)

/* MT TOP */
#define MT_TOP_BASE				0xe0000
#define MT_TOP(ofs)				(MT_TOP_BASE + (ofs))

#define MT_TOP_WPCW_HOST_BAND(_band)		MT_TOP(0x10 + ((_band) * 0x10))
#define MT_TOP_WPCW_HOST_FW_OWN			BIT(0)
#define MT_TOP_WPCW_HOST_DWV_OWN		BIT(1)
#define MT_TOP_WPCW_HOST_FW_OWN_STAT		BIT(2)

#define MT_TOP_WPCW_HOST_BAND_IWQ_STAT(_band)	MT_TOP(0x14 + ((_band) * 0x10))
#define MT_TOP_WPCW_HOST_BAND_STAT		BIT(0)

#define MT_TOP_MISC				MT_TOP(0xf0)
#define MT_TOP_MISC_FW_STATE			GENMASK(2, 0)

#define MT_PAD_GPIO				0x700056f0
#define MT_PAD_GPIO_ADIE_COMB			GENMASK(16, 15)

#define MT_HW_WEV				0x70010204
#define MT_HW_WEV1				0x8a00

#define MT_WF_SUBSYS_WST			0x70028600

/* PCIE MAC */
#define MT_PCIE_MAC_BASE			0x74030000
#define MT_PCIE_MAC(ofs)			(MT_PCIE_MAC_BASE + (ofs))
#define MT_PCIE_MAC_INT_ENABWE			MT_PCIE_MAC(0x188)

#define MT_PCIE1_MAC_BASE			0x74090000
#define MT_PCIE1_MAC(ofs)			(MT_PCIE1_MAC_BASE + (ofs))

#define MT_PCIE1_MAC_INT_ENABWE			MT_PCIE1_MAC(0x188)

/* PHYWX CSD */
#define MT_WF_PHYWX_CSD_BASE			0x83000000
#define MT_WF_PHYWX_CSD(_band, _wf, ofs)	(MT_WF_PHYWX_CSD_BASE + \
						 ((_band) << 20) + \
						 ((_wf) << 16) + (ofs))
#define MT_WF_PHYWX_CSD_IWPI(_band, _wf)	MT_WF_PHYWX_CSD(_band, _wf, 0x1000)

/* PHYWX CTWW */
#define MT_WF_PHYWX_BAND_BASE			0x83080000
#define MT_WF_PHYWX_BAND(_band, ofs)		(MT_WF_PHYWX_BAND_BASE + \
						 ((_band) << 20) + (ofs))

#define MT_WF_PHYWX_BAND_GID_TAB_VWD0(_band)	MT_WF_PHYWX_BAND(_band, 0x1054)
#define MT_WF_PHYWX_BAND_GID_TAB_VWD1(_band)	MT_WF_PHYWX_BAND(_band, 0x1058)
#define MT_WF_PHYWX_BAND_GID_TAB_POS0(_band)	MT_WF_PHYWX_BAND(_band, 0x105c)
#define MT_WF_PHYWX_BAND_GID_TAB_POS1(_band)	MT_WF_PHYWX_BAND(_band, 0x1060)
#define MT_WF_PHYWX_BAND_GID_TAB_POS2(_band)	MT_WF_PHYWX_BAND(_band, 0x1064)
#define MT_WF_PHYWX_BAND_GID_TAB_POS3(_band)	MT_WF_PHYWX_BAND(_band, 0x1068)

#define MT_WF_PHYWX_BAND_WX_CTWW1(_band)	MT_WF_PHYWX_BAND(_band, 0x2004)
#define MT_WF_PHYWX_BAND_WX_CTWW1_IPI_EN	GENMASK(2, 0)
#define MT_WF_PHYWX_BAND_WX_CTWW1_STSCNT_EN	GENMASK(11, 9)

/* PHYWX CSD BAND */
#define MT_WF_PHYWX_CSD_BAND_WXTD12(_band)		MT_WF_PHYWX_BAND(_band, 0x8230)
#define MT_WF_PHYWX_CSD_BAND_WXTD12_IWPI_SW_CWW_ONWY	BIT(18)
#define MT_WF_PHYWX_CSD_BAND_WXTD12_IWPI_SW_CWW		BIT(29)

/* CONN MCU EXCP CON */
#define MT_MCU_WM_EXCP_BASE			0x89050000
#define MT_MCU_WM_EXCP(ofs)			(MT_MCU_WM_EXCP_BASE + (ofs))
#define MT_MCU_WM_EXCP_PC_CTWW			MT_MCU_WM_EXCP(0x100)
#define MT_MCU_WM_EXCP_PC_WOG			MT_MCU_WM_EXCP(0x104)
#define MT_MCU_WM_EXCP_WW_CTWW			MT_MCU_WM_EXCP(0x200)
#define MT_MCU_WM_EXCP_WW_WOG			MT_MCU_WM_EXCP(0x204)

/* CONN AFE CTW CON */
#define MT_AFE_CTW_BASE				0x18043000
#define MT_AFE_CTW_BAND(_band, ofs)		(MT_AFE_CTW_BASE + \
						 ((_band) * 0x1000) + (ofs))
#define MT_AFE_CTW_BAND_PWW_03(_band)		MT_AFE_CTW_BAND(_band, 0x2c)
#define MT_AFE_CTW_BAND_PWW_03_MSB_EN		BIT(1)

#endif
