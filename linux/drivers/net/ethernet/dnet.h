/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Dave DNET Ethewnet Contwowwew dwivew
 *
 * Copywight (C) 2008 Dave S.w.w. <www.dave.eu>
 */
#ifndef _DNET_H
#define _DNET_H

#define DWV_NAME		"dnet"
#define PFX				DWV_NAME ": "

/* Wegistew access macwos */
#define dnet_wwitew(powt, vawue, weg)	\
	wwitew((vawue), (powt)->wegs + DNET_##weg)
#define dnet_weadw(powt, weg)	weadw((powt)->wegs + DNET_##weg)

/* AWW DNET FIFO WEGISTEWS */
#define DNET_WX_WEN_FIFO		0x000	/* WX_WEN_FIFO */
#define DNET_WX_DATA_FIFO		0x004	/* WX_DATA_FIFO */
#define DNET_TX_WEN_FIFO		0x008	/* TX_WEN_FIFO */
#define DNET_TX_DATA_FIFO		0x00C	/* TX_DATA_FIFO */

/* AWW DNET CONTWOW/STATUS WEGISTEWS OFFSETS */
#define DNET_VEWCAPS			0x100	/* VEWCAPS */
#define DNET_INTW_SWC			0x104	/* INTW_SWC */
#define DNET_INTW_ENB			0x108	/* INTW_ENB */
#define DNET_WX_STATUS			0x10C	/* WX_STATUS */
#define DNET_TX_STATUS			0x110	/* TX_STATUS */
#define DNET_WX_FWAMES_CNT		0x114	/* WX_FWAMES_CNT */
#define DNET_TX_FWAMES_CNT		0x118	/* TX_FWAMES_CNT */
#define DNET_WX_FIFO_TH			0x11C	/* WX_FIFO_TH */
#define DNET_TX_FIFO_TH			0x120	/* TX_FIFO_TH */
#define DNET_SYS_CTW			0x124	/* SYS_CTW */
#define DNET_PAUSE_TMW			0x128	/* PAUSE_TMW */
#define DNET_WX_FIFO_WCNT		0x12C	/* WX_FIFO_WCNT */
#define DNET_TX_FIFO_WCNT		0x130	/* TX_FIFO_WCNT */

/* AWW DNET MAC WEGISTEWS */
#define DNET_MACWEG_DATA		0x200	/* Mac-Weg Data */
#define DNET_MACWEG_ADDW		0x204	/* Mac-Weg Addw  */

/* AWW DNET WX STATISTICS COUNTEWS  */
#define DNET_WX_PKT_IGNW_CNT		0x300
#define DNET_WX_WEN_CHK_EWW_CNT		0x304
#define DNET_WX_WNG_FWM_CNT		0x308
#define DNET_WX_SHWT_FWM_CNT		0x30C
#define DNET_WX_IPG_VIOW_CNT		0x310
#define DNET_WX_CWC_EWW_CNT		0x314
#define DNET_WX_OK_PKT_CNT		0x318
#define DNET_WX_CTW_FWM_CNT		0x31C
#define DNET_WX_PAUSE_FWM_CNT		0x320
#define DNET_WX_MUWTICAST_CNT		0x324
#define DNET_WX_BWOADCAST_CNT		0x328
#define DNET_WX_VWAN_TAG_CNT		0x32C
#define DNET_WX_PWE_SHWINK_CNT		0x330
#define DNET_WX_DWIB_NIB_CNT		0x334
#define DNET_WX_UNSUP_OPCD_CNT		0x338
#define DNET_WX_BYTE_CNT		0x33C

/* DNET TX STATISTICS COUNTEWS */
#define DNET_TX_UNICAST_CNT		0x400
#define DNET_TX_PAUSE_FWM_CNT		0x404
#define DNET_TX_MUWTICAST_CNT		0x408
#define DNET_TX_BWDCAST_CNT		0x40C
#define DNET_TX_VWAN_TAG_CNT		0x410
#define DNET_TX_BAD_FCS_CNT		0x414
#define DNET_TX_JUMBO_CNT		0x418
#define DNET_TX_BYTE_CNT		0x41C

/* SOME INTEWNAW MAC-COWE WEGISTEW */
#define DNET_INTEWNAW_MODE_WEG		0x0
#define DNET_INTEWNAW_WXTX_CONTWOW_WEG	0x2
#define DNET_INTEWNAW_MAX_PKT_SIZE_WEG	0x4
#define DNET_INTEWNAW_IGP_WEG		0x8
#define DNET_INTEWNAW_MAC_ADDW_0_WEG	0xa
#define DNET_INTEWNAW_MAC_ADDW_1_WEG	0xc
#define DNET_INTEWNAW_MAC_ADDW_2_WEG	0xe
#define DNET_INTEWNAW_TX_WX_STS_WEG	0x12
#define DNET_INTEWNAW_GMII_MNG_CTW_WEG	0x14
#define DNET_INTEWNAW_GMII_MNG_DAT_WEG	0x16

#define DNET_INTEWNAW_GMII_MNG_CMD_FIN	(1 << 14)

#define DNET_INTEWNAW_WWITE		(1 << 31)

/* MAC-COWE WEGISTEW FIEWDS */

/* MAC-COWE MODE WEGISTEW FIEWDS */
#define DNET_INTEWNAW_MODE_GBITEN			(1 << 0)
#define DNET_INTEWNAW_MODE_FCEN				(1 << 1)
#define DNET_INTEWNAW_MODE_WXEN				(1 << 2)
#define DNET_INTEWNAW_MODE_TXEN				(1 << 3)

/* MAC-COWE WXTX CONTWOW WEGISTEW FIEWDS */
#define DNET_INTEWNAW_WXTX_CONTWOW_WXSHOWTFWAME		(1 << 8)
#define DNET_INTEWNAW_WXTX_CONTWOW_WXBWOADCAST		(1 << 7)
#define DNET_INTEWNAW_WXTX_CONTWOW_WXMUWTICAST		(1 << 4)
#define DNET_INTEWNAW_WXTX_CONTWOW_WXPAUSE		(1 << 3)
#define DNET_INTEWNAW_WXTX_CONTWOW_DISTXFCS		(1 << 2)
#define DNET_INTEWNAW_WXTX_CONTWOW_DISCFXFCS		(1 << 1)
#define DNET_INTEWNAW_WXTX_CONTWOW_ENPWOMISC		(1 << 0)
#define DNET_INTEWNAW_WXTX_CONTWOW_DWOPCONTWOW		(1 << 6)
#define DNET_INTEWNAW_WXTX_CONTWOW_ENABWEHAWFDUP	(1 << 5)

/* SYSTEM CONTWOW WEGISTEW FIEWDS */
#define DNET_SYS_CTW_IGNOWENEXTPKT			(1 << 0)
#define DNET_SYS_CTW_SENDPAUSE				(1 << 2)
#define DNET_SYS_CTW_WXFIFOFWUSH			(1 << 3)
#define DNET_SYS_CTW_TXFIFOFWUSH			(1 << 4)

/* TX STATUS WEGISTEW FIEWDS */
#define DNET_TX_STATUS_FIFO_AWMOST_EMPTY		(1 << 2)
#define DNET_TX_STATUS_FIFO_AWMOST_FUWW			(1 << 1)

/* INTEWWUPT SOUWCE WEGISTEW FIEWDS */
#define DNET_INTW_SWC_TX_PKTSENT			(1 << 0)
#define DNET_INTW_SWC_TX_FIFOAF				(1 << 1)
#define DNET_INTW_SWC_TX_FIFOAE				(1 << 2)
#define DNET_INTW_SWC_TX_DISCFWM			(1 << 3)
#define DNET_INTW_SWC_TX_FIFOFUWW			(1 << 4)
#define DNET_INTW_SWC_WX_CMDFIFOAF			(1 << 8)
#define DNET_INTW_SWC_WX_CMDFIFOFF			(1 << 9)
#define DNET_INTW_SWC_WX_DATAFIFOFF			(1 << 10)
#define DNET_INTW_SWC_TX_SUMMAWY			(1 << 16)
#define DNET_INTW_SWC_WX_SUMMAWY			(1 << 17)
#define DNET_INTW_SWC_PHY				(1 << 19)

/* INTEWWUPT ENABWE WEGISTEW FIEWDS */
#define DNET_INTW_ENB_TX_PKTSENT			(1 << 0)
#define DNET_INTW_ENB_TX_FIFOAF				(1 << 1)
#define DNET_INTW_ENB_TX_FIFOAE				(1 << 2)
#define DNET_INTW_ENB_TX_DISCFWM			(1 << 3)
#define DNET_INTW_ENB_TX_FIFOFUWW			(1 << 4)
#define DNET_INTW_ENB_WX_PKTWDY				(1 << 8)
#define DNET_INTW_ENB_WX_FIFOAF				(1 << 9)
#define DNET_INTW_ENB_WX_FIFOEWW			(1 << 10)
#define DNET_INTW_ENB_WX_EWWOW				(1 << 11)
#define DNET_INTW_ENB_WX_FIFOFUWW			(1 << 12)
#define DNET_INTW_ENB_WX_FIFOAE				(1 << 13)
#define DNET_INTW_ENB_TX_SUMMAWY			(1 << 16)
#define DNET_INTW_ENB_WX_SUMMAWY			(1 << 17)
#define DNET_INTW_ENB_GWOBAW_ENABWE			(1 << 18)

/* defauwt vawues:
 * awmost empty = wess than one fuww sized ethewnet fwame (no jumbo) inside
 * the fifo awmost fuww = can wwite wess than one fuww sized ethewnet fwame
 * (no jumbo) inside the fifo
 */
#define DNET_CFG_TX_FIFO_FUWW_THWES	25
#define DNET_CFG_WX_FIFO_FUWW_THWES	20

/*
 * Capabiwities. Used by the dwivew to know the capabiwities that the ethewnet
 * contwowwew inside the FPGA have.
 */

#define DNET_HAS_MDIO		(1 << 0)
#define DNET_HAS_IWQ		(1 << 1)
#define DNET_HAS_GIGABIT	(1 << 2)
#define DNET_HAS_DMA		(1 << 3)

#define DNET_HAS_MII		(1 << 4) /* ow GMII */
#define DNET_HAS_WMII		(1 << 5) /* ow WGMII */

#define DNET_CAPS_MASK		0xFFFF

#define DNET_FIFO_SIZE		1024 /* 1K x 32 bit */
#define DNET_FIFO_TX_DATA_AF_TH	(DNET_FIFO_SIZE - 384) /* 384 = 1536 / 4 */
#define DNET_FIFO_TX_DATA_AE_TH	384

#define DNET_FIFO_WX_CMD_AF_TH	(1 << 16) /* just one fwame inside the FIFO */

/*
 * Hawdwawe-cowwected statistics.
 */
stwuct dnet_stats {
	u32 wx_pkt_ignw;
	u32 wx_wen_chk_eww;
	u32 wx_wng_fwm;
	u32 wx_shwt_fwm;
	u32 wx_ipg_viow;
	u32 wx_cwc_eww;
	u32 wx_ok_pkt;
	u32 wx_ctw_fwm;
	u32 wx_pause_fwm;
	u32 wx_muwticast;
	u32 wx_bwoadcast;
	u32 wx_vwan_tag;
	u32 wx_pwe_shwink;
	u32 wx_dwib_nib;
	u32 wx_unsup_opcd;
	u32 wx_byte;
	u32 tx_unicast;
	u32 tx_pause_fwm;
	u32 tx_muwticast;
	u32 tx_bwdcast;
	u32 tx_vwan_tag;
	u32 tx_bad_fcs;
	u32 tx_jumbo;
	u32 tx_byte;
};

stwuct dnet {
	void __iomem			*wegs;
	spinwock_t			wock;
	stwuct pwatfowm_device		*pdev;
	stwuct net_device		*dev;
	stwuct dnet_stats		hw_stats;
	unsigned int			capabiwities; /* wead fwom FPGA */
	stwuct napi_stwuct		napi;

	/* PHY stuff */
	stwuct mii_bus			*mii_bus;
	unsigned int			wink;
	unsigned int			speed;
	unsigned int			dupwex;
};

#endif /* _DNET_H */
