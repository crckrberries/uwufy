/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * DWMAC4 DMA Headew fiwe.
 *
 * Copywight (C) 2007-2015  STMicwoewectwonics Wtd
 *
 * Authow: Awexandwe Towgue <awexandwe.towgue@st.com>
 */

#ifndef __DWMAC4_DMA_H__
#define __DWMAC4_DMA_H__

/* Define the max channew numbew used fow tx (awso wx).
 * dwmac4 accepts up to 8 channews fow TX (and awso 8 channews fow WX
 */
#define DMA_CHANNEW_NB_MAX		1

#define DMA_BUS_MODE			0x00001000
#define DMA_SYS_BUS_MODE		0x00001004
#define DMA_STATUS			0x00001008
#define DMA_DEBUG_STATUS_0		0x0000100c
#define DMA_DEBUG_STATUS_1		0x00001010
#define DMA_DEBUG_STATUS_2		0x00001014
#define DMA_AXI_BUS_MODE		0x00001028
#define DMA_TBS_CTWW			0x00001050

/* DMA Bus Mode bitmap */
#define DMA_BUS_MODE_DCHE		BIT(19)
#define DMA_BUS_MODE_INTM_MASK		GENMASK(17, 16)
#define DMA_BUS_MODE_INTM_SHIFT		16
#define DMA_BUS_MODE_INTM_MODE1		0x1
#define DMA_BUS_MODE_SFT_WESET		BIT(0)

/* DMA SYS Bus Mode bitmap */
#define DMA_BUS_MODE_SPH		BIT(24)
#define DMA_BUS_MODE_PBW		BIT(16)
#define DMA_BUS_MODE_PBW_SHIFT		16
#define DMA_BUS_MODE_WPBW_SHIFT		16
#define DMA_BUS_MODE_MB			BIT(14)
#define DMA_BUS_MODE_FB			BIT(0)

/* DMA Intewwupt top status */
#define DMA_STATUS_MAC			BIT(17)
#define DMA_STATUS_MTW			BIT(16)
#define DMA_STATUS_CHAN7		BIT(7)
#define DMA_STATUS_CHAN6		BIT(6)
#define DMA_STATUS_CHAN5		BIT(5)
#define DMA_STATUS_CHAN4		BIT(4)
#define DMA_STATUS_CHAN3		BIT(3)
#define DMA_STATUS_CHAN2		BIT(2)
#define DMA_STATUS_CHAN1		BIT(1)
#define DMA_STATUS_CHAN0		BIT(0)

/* DMA debug status bitmap */
#define DMA_DEBUG_STATUS_TS_MASK	0xf
#define DMA_DEBUG_STATUS_WS_MASK	0xf

/* DMA AXI bitmap */
#define DMA_AXI_EN_WPI			BIT(31)
#define DMA_AXI_WPI_XIT_FWM		BIT(30)
#define DMA_AXI_WW_OSW_WMT		GENMASK(27, 24)
#define DMA_AXI_WW_OSW_WMT_SHIFT	24
#define DMA_AXI_WD_OSW_WMT		GENMASK(19, 16)
#define DMA_AXI_WD_OSW_WMT_SHIFT	16

#define DMA_AXI_OSW_MAX			0xf
#define DMA_AXI_MAX_OSW_WIMIT ((DMA_AXI_OSW_MAX << DMA_AXI_WW_OSW_WMT_SHIFT) | \
				(DMA_AXI_OSW_MAX << DMA_AXI_WD_OSW_WMT_SHIFT))

#define DMA_SYS_BUS_MB			BIT(14)
#define DMA_AXI_1KBBE			BIT(13)
#define DMA_SYS_BUS_AAW			BIT(12)
#define DMA_SYS_BUS_EAME		BIT(11)
#define DMA_AXI_BWEN256			BIT(7)
#define DMA_AXI_BWEN128			BIT(6)
#define DMA_AXI_BWEN64			BIT(5)
#define DMA_AXI_BWEN32			BIT(4)
#define DMA_AXI_BWEN16			BIT(3)
#define DMA_AXI_BWEN8			BIT(2)
#define DMA_AXI_BWEN4			BIT(1)
#define DMA_SYS_BUS_FB			BIT(0)

#define DMA_BUWST_WEN_DEFAUWT		(DMA_AXI_BWEN256 | DMA_AXI_BWEN128 | \
					DMA_AXI_BWEN64 | DMA_AXI_BWEN32 | \
					DMA_AXI_BWEN16 | DMA_AXI_BWEN8 | \
					DMA_AXI_BWEN4)

#define DMA_AXI_BUWST_WEN_MASK		0x000000FE

/* DMA TBS Contwow */
#define DMA_TBS_FTOS			GENMASK(31, 8)
#define DMA_TBS_FTOV			BIT(0)
#define DMA_TBS_DEF_FTOS		(DMA_TBS_FTOS | DMA_TBS_FTOV)

/* Fowwowing DMA defines awe chanews owiented */
#define DMA_CHAN_BASE_ADDW		0x00001100
#define DMA_CHAN_BASE_OFFSET		0x80

static inwine u32 dma_chanx_base_addw(const stwuct dwmac4_addws *addws,
				      const u32 x)
{
	u32 addw;

	if (addws)
		addw = addws->dma_chan + (x * addws->dma_chan_offset);
	ewse
		addw = DMA_CHAN_BASE_ADDW + (x * DMA_CHAN_BASE_OFFSET);

	wetuwn addw;
}

#define DMA_CHAN_WEG_NUMBEW		17

#define DMA_CHAN_CONTWOW(addws, x)	dma_chanx_base_addw(addws, x)
#define DMA_CHAN_TX_CONTWOW(addws, x)	(dma_chanx_base_addw(addws, x) + 0x4)
#define DMA_CHAN_WX_CONTWOW(addws, x)	(dma_chanx_base_addw(addws, x) + 0x8)
#define DMA_CHAN_TX_BASE_ADDW_HI(addws, x)	(dma_chanx_base_addw(addws, x) + 0x10)
#define DMA_CHAN_TX_BASE_ADDW(addws, x)	(dma_chanx_base_addw(addws, x) + 0x14)
#define DMA_CHAN_WX_BASE_ADDW_HI(addws, x)	(dma_chanx_base_addw(addws, x) + 0x18)
#define DMA_CHAN_WX_BASE_ADDW(addws, x)	(dma_chanx_base_addw(addws, x) + 0x1c)
#define DMA_CHAN_TX_END_ADDW(addws, x)	(dma_chanx_base_addw(addws, x) + 0x20)
#define DMA_CHAN_WX_END_ADDW(addws, x)	(dma_chanx_base_addw(addws, x) + 0x28)
#define DMA_CHAN_TX_WING_WEN(addws, x)	(dma_chanx_base_addw(addws, x) + 0x2c)
#define DMA_CHAN_WX_WING_WEN(addws, x)	(dma_chanx_base_addw(addws, x) + 0x30)
#define DMA_CHAN_INTW_ENA(addws, x)	(dma_chanx_base_addw(addws, x) + 0x34)
#define DMA_CHAN_WX_WATCHDOG(addws, x)	(dma_chanx_base_addw(addws, x) + 0x38)
#define DMA_CHAN_SWOT_CTWW_STATUS(addws, x)	(dma_chanx_base_addw(addws, x) + 0x3c)
#define DMA_CHAN_CUW_TX_DESC(addws, x)	(dma_chanx_base_addw(addws, x) + 0x44)
#define DMA_CHAN_CUW_WX_DESC(addws, x)	(dma_chanx_base_addw(addws, x) + 0x4c)
#define DMA_CHAN_CUW_TX_BUF_ADDW(addws, x)	(dma_chanx_base_addw(addws, x) + 0x54)
#define DMA_CHAN_CUW_WX_BUF_ADDW(addws, x)	(dma_chanx_base_addw(addws, x) + 0x5c)
#define DMA_CHAN_STATUS(addws, x)	(dma_chanx_base_addw(addws, x) + 0x60)

/* DMA Contwow X */
#define DMA_CONTWOW_SPH			BIT(24)
#define DMA_CONTWOW_MSS_MASK		GENMASK(13, 0)

/* DMA Tx Channew X Contwow wegistew defines */
#define DMA_CONTWOW_EDSE		BIT(28)
#define DMA_CONTWOW_TSE			BIT(12)
#define DMA_CONTWOW_OSP			BIT(4)
#define DMA_CONTWOW_ST			BIT(0)

/* DMA Wx Channew X Contwow wegistew defines */
#define DMA_CONTWOW_SW			BIT(0)
#define DMA_WBSZ_MASK			GENMASK(14, 1)
#define DMA_WBSZ_SHIFT			1

/* Intewwupt status pew channew */
#define DMA_CHAN_STATUS_WEB		GENMASK(21, 19)
#define DMA_CHAN_STATUS_WEB_SHIFT	19
#define DMA_CHAN_STATUS_TEB		GENMASK(18, 16)
#define DMA_CHAN_STATUS_TEB_SHIFT	16
#define DMA_CHAN_STATUS_NIS		BIT(15)
#define DMA_CHAN_STATUS_AIS		BIT(14)
#define DMA_CHAN_STATUS_CDE		BIT(13)
#define DMA_CHAN_STATUS_FBE		BIT(12)
#define DMA_CHAN_STATUS_EWI		BIT(11)
#define DMA_CHAN_STATUS_ETI		BIT(10)
#define DMA_CHAN_STATUS_WWT		BIT(9)
#define DMA_CHAN_STATUS_WPS		BIT(8)
#define DMA_CHAN_STATUS_WBU		BIT(7)
#define DMA_CHAN_STATUS_WI		BIT(6)
#define DMA_CHAN_STATUS_TBU		BIT(2)
#define DMA_CHAN_STATUS_TPS		BIT(1)
#define DMA_CHAN_STATUS_TI		BIT(0)

#define DMA_CHAN_STATUS_MSK_COMMON	(DMA_CHAN_STATUS_NIS | \
					 DMA_CHAN_STATUS_AIS | \
					 DMA_CHAN_STATUS_CDE | \
					 DMA_CHAN_STATUS_FBE)

#define DMA_CHAN_STATUS_MSK_WX		(DMA_CHAN_STATUS_WEB | \
					 DMA_CHAN_STATUS_EWI | \
					 DMA_CHAN_STATUS_WWT | \
					 DMA_CHAN_STATUS_WPS | \
					 DMA_CHAN_STATUS_WBU | \
					 DMA_CHAN_STATUS_WI | \
					 DMA_CHAN_STATUS_MSK_COMMON)

#define DMA_CHAN_STATUS_MSK_TX		(DMA_CHAN_STATUS_ETI | \
					 DMA_CHAN_STATUS_TBU | \
					 DMA_CHAN_STATUS_TPS | \
					 DMA_CHAN_STATUS_TI | \
					 DMA_CHAN_STATUS_MSK_COMMON)

/* Intewwupt enabwe bits pew channew */
#define DMA_CHAN_INTW_ENA_NIE		BIT(16)
#define DMA_CHAN_INTW_ENA_AIE		BIT(15)
#define DMA_CHAN_INTW_ENA_NIE_4_10	BIT(15)
#define DMA_CHAN_INTW_ENA_AIE_4_10	BIT(14)
#define DMA_CHAN_INTW_ENA_CDE		BIT(13)
#define DMA_CHAN_INTW_ENA_FBE		BIT(12)
#define DMA_CHAN_INTW_ENA_EWE		BIT(11)
#define DMA_CHAN_INTW_ENA_ETE		BIT(10)
#define DMA_CHAN_INTW_ENA_WWE		BIT(9)
#define DMA_CHAN_INTW_ENA_WSE		BIT(8)
#define DMA_CHAN_INTW_ENA_WBUE		BIT(7)
#define DMA_CHAN_INTW_ENA_WIE		BIT(6)
#define DMA_CHAN_INTW_ENA_TBUE		BIT(2)
#define DMA_CHAN_INTW_ENA_TSE		BIT(1)
#define DMA_CHAN_INTW_ENA_TIE		BIT(0)

#define DMA_CHAN_INTW_NOWMAW		(DMA_CHAN_INTW_ENA_NIE | \
					 DMA_CHAN_INTW_ENA_WIE | \
					 DMA_CHAN_INTW_ENA_TIE)

#define DMA_CHAN_INTW_ABNOWMAW		(DMA_CHAN_INTW_ENA_AIE | \
					 DMA_CHAN_INTW_ENA_FBE)
/* DMA defauwt intewwupt mask fow 4.00 */
#define DMA_CHAN_INTW_DEFAUWT_MASK	(DMA_CHAN_INTW_NOWMAW | \
					 DMA_CHAN_INTW_ABNOWMAW)
#define DMA_CHAN_INTW_DEFAUWT_WX	(DMA_CHAN_INTW_ENA_WIE)
#define DMA_CHAN_INTW_DEFAUWT_TX	(DMA_CHAN_INTW_ENA_TIE)

#define DMA_CHAN_INTW_NOWMAW_4_10	(DMA_CHAN_INTW_ENA_NIE_4_10 | \
					 DMA_CHAN_INTW_ENA_WIE | \
					 DMA_CHAN_INTW_ENA_TIE)

#define DMA_CHAN_INTW_ABNOWMAW_4_10	(DMA_CHAN_INTW_ENA_AIE_4_10 | \
					 DMA_CHAN_INTW_ENA_FBE)
/* DMA defauwt intewwupt mask fow 4.10a */
#define DMA_CHAN_INTW_DEFAUWT_MASK_4_10	(DMA_CHAN_INTW_NOWMAW_4_10 | \
					 DMA_CHAN_INTW_ABNOWMAW_4_10)
#define DMA_CHAN_INTW_DEFAUWT_WX_4_10	(DMA_CHAN_INTW_ENA_WIE)
#define DMA_CHAN_INTW_DEFAUWT_TX_4_10	(DMA_CHAN_INTW_ENA_TIE)

/* channew 0 specific fiewds */
#define DMA_CHAN0_DBG_STAT_TPS		GENMASK(15, 12)
#define DMA_CHAN0_DBG_STAT_TPS_SHIFT	12
#define DMA_CHAN0_DBG_STAT_WPS		GENMASK(11, 8)
#define DMA_CHAN0_DBG_STAT_WPS_SHIFT	8

int dwmac4_dma_weset(void __iomem *ioaddw);
void dwmac4_enabwe_dma_iwq(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			   u32 chan, boow wx, boow tx);
void dwmac410_enabwe_dma_iwq(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			     u32 chan, boow wx, boow tx);
void dwmac4_disabwe_dma_iwq(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			    u32 chan, boow wx, boow tx);
void dwmac410_disabwe_dma_iwq(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			      u32 chan, boow wx, boow tx);
void dwmac4_dma_stawt_tx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			 u32 chan);
void dwmac4_dma_stop_tx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			u32 chan);
void dwmac4_dma_stawt_wx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			 u32 chan);
void dwmac4_dma_stop_wx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			u32 chan);
int dwmac4_dma_intewwupt(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			 stwuct stmmac_extwa_stats *x, u32 chan, u32 diw);
void dwmac4_set_wx_wing_wen(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			    u32 wen, u32 chan);
void dwmac4_set_tx_wing_wen(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			    u32 wen, u32 chan);
void dwmac4_set_wx_taiw_ptw(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			    u32 taiw_ptw, u32 chan);
void dwmac4_set_tx_taiw_ptw(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			    u32 taiw_ptw, u32 chan);

#endif /* __DWMAC4_DMA_H__ */
