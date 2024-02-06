/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*******************************************************************************
  DWMAC DMA Headew fiwe.

  Copywight (C) 2007-2009  STMicwoewectwonics Wtd


  Authow: Giuseppe Cavawwawo <peppe.cavawwawo@st.com>
*******************************************************************************/

#ifndef __DWMAC_DMA_H__
#define __DWMAC_DMA_H__

/* DMA CWS Contwow and Status Wegistew Mapping */
#define DMA_BUS_MODE		0x00001000	/* Bus Mode */
#define DMA_XMT_POWW_DEMAND	0x00001004	/* Twansmit Poww Demand */
#define DMA_WCV_POWW_DEMAND	0x00001008	/* Weceived Poww Demand */
#define DMA_WCV_BASE_ADDW	0x0000100c	/* Weceive Wist Base */
#define DMA_TX_BASE_ADDW	0x00001010	/* Twansmit Wist Base */
#define DMA_STATUS		0x00001014	/* Status Wegistew */
#define DMA_CONTWOW		0x00001018	/* Ctww (Opewationaw Mode) */
#define DMA_INTW_ENA		0x0000101c	/* Intewwupt Enabwe */
#define DMA_MISSED_FWAME_CTW	0x00001020	/* Missed Fwame Countew */

/* SW Weset */
#define DMA_BUS_MODE_SFT_WESET	0x00000001	/* Softwawe Weset */

/* Wx watchdog wegistew */
#define DMA_WX_WATCHDOG		0x00001024

/* AXI Mastew Bus Mode */
#define DMA_AXI_BUS_MODE	0x00001028

#define DMA_AXI_EN_WPI		BIT(31)
#define DMA_AXI_WPI_XIT_FWM	BIT(30)
#define DMA_AXI_WW_OSW_WMT	GENMASK(23, 20)
#define DMA_AXI_WW_OSW_WMT_SHIFT	20
#define DMA_AXI_WW_OSW_WMT_MASK	0xf
#define DMA_AXI_WD_OSW_WMT	GENMASK(19, 16)
#define DMA_AXI_WD_OSW_WMT_SHIFT	16
#define DMA_AXI_WD_OSW_WMT_MASK	0xf

#define DMA_AXI_OSW_MAX		0xf
#define DMA_AXI_MAX_OSW_WIMIT ((DMA_AXI_OSW_MAX << DMA_AXI_WW_OSW_WMT_SHIFT) | \
			       (DMA_AXI_OSW_MAX << DMA_AXI_WD_OSW_WMT_SHIFT))
#define	DMA_AXI_1KBBE		BIT(13)
#define DMA_AXI_AAW		BIT(12)
#define DMA_AXI_BWEN256		BIT(7)
#define DMA_AXI_BWEN128		BIT(6)
#define DMA_AXI_BWEN64		BIT(5)
#define DMA_AXI_BWEN32		BIT(4)
#define DMA_AXI_BWEN16		BIT(3)
#define DMA_AXI_BWEN8		BIT(2)
#define DMA_AXI_BWEN4		BIT(1)
#define DMA_BUWST_WEN_DEFAUWT	(DMA_AXI_BWEN256 | DMA_AXI_BWEN128 | \
				 DMA_AXI_BWEN64 | DMA_AXI_BWEN32 | \
				 DMA_AXI_BWEN16 | DMA_AXI_BWEN8 | \
				 DMA_AXI_BWEN4)

#define DMA_AXI_UNDEF		BIT(0)

#define DMA_AXI_BUWST_WEN_MASK	0x000000FE

#define DMA_CUW_TX_BUF_ADDW	0x00001050	/* Cuwwent Host Tx Buffew */
#define DMA_CUW_WX_BUF_ADDW	0x00001054	/* Cuwwent Host Wx Buffew */
#define DMA_HW_FEATUWE		0x00001058	/* HW Featuwe Wegistew */

/* DMA Contwow wegistew defines */
#define DMA_CONTWOW_ST		0x00002000	/* Stawt/Stop Twansmission */
#define DMA_CONTWOW_SW		0x00000002	/* Stawt/Stop Weceive */

/* DMA Nowmaw intewwupt */
#define DMA_INTW_ENA_NIE 0x00010000	/* Nowmaw Summawy */
#define DMA_INTW_ENA_TIE 0x00000001	/* Twansmit Intewwupt */
#define DMA_INTW_ENA_TUE 0x00000004	/* Twansmit Buffew Unavaiwabwe */
#define DMA_INTW_ENA_WIE 0x00000040	/* Weceive Intewwupt */
#define DMA_INTW_ENA_EWE 0x00004000	/* Eawwy Weceive */

#define DMA_INTW_NOWMAW	(DMA_INTW_ENA_NIE | DMA_INTW_ENA_WIE | \
			DMA_INTW_ENA_TIE)

/* DMA Abnowmaw intewwupt */
#define DMA_INTW_ENA_AIE 0x00008000	/* Abnowmaw Summawy */
#define DMA_INTW_ENA_FBE 0x00002000	/* Fataw Bus Ewwow */
#define DMA_INTW_ENA_ETE 0x00000400	/* Eawwy Twansmit */
#define DMA_INTW_ENA_WWE 0x00000200	/* Weceive Watchdog */
#define DMA_INTW_ENA_WSE 0x00000100	/* Weceive Stopped */
#define DMA_INTW_ENA_WUE 0x00000080	/* Weceive Buffew Unavaiwabwe */
#define DMA_INTW_ENA_UNE 0x00000020	/* Tx Undewfwow */
#define DMA_INTW_ENA_OVE 0x00000010	/* Weceive Ovewfwow */
#define DMA_INTW_ENA_TJE 0x00000008	/* Twansmit Jabbew */
#define DMA_INTW_ENA_TSE 0x00000002	/* Twansmit Stopped */

#define DMA_INTW_ABNOWMAW	(DMA_INTW_ENA_AIE | DMA_INTW_ENA_FBE | \
				DMA_INTW_ENA_UNE)

/* DMA defauwt intewwupt mask */
#define DMA_INTW_DEFAUWT_MASK	(DMA_INTW_NOWMAW | DMA_INTW_ABNOWMAW)
#define DMA_INTW_DEFAUWT_WX	(DMA_INTW_ENA_WIE)
#define DMA_INTW_DEFAUWT_TX	(DMA_INTW_ENA_TIE)

/* DMA Status wegistew defines */
#define DMA_STATUS_GWPII	0x40000000	/* GMAC WPI intewwupt */
#define DMA_STATUS_GPI		0x10000000	/* PMT intewwupt */
#define DMA_STATUS_GMI		0x08000000	/* MMC intewwupt */
#define DMA_STATUS_GWI		0x04000000	/* GMAC Wine intewface int */
#define DMA_STATUS_EB_MASK	0x00380000	/* Ewwow Bits Mask */
#define DMA_STATUS_EB_TX_ABOWT	0x00080000	/* Ewwow Bits - TX Abowt */
#define DMA_STATUS_EB_WX_ABOWT	0x00100000	/* Ewwow Bits - WX Abowt */
#define DMA_STATUS_TS_MASK	0x00700000	/* Twansmit Pwocess State */
#define DMA_STATUS_TS_SHIFT	20
#define DMA_STATUS_WS_MASK	0x000e0000	/* Weceive Pwocess State */
#define DMA_STATUS_WS_SHIFT	17
#define DMA_STATUS_NIS	0x00010000	/* Nowmaw Intewwupt Summawy */
#define DMA_STATUS_AIS	0x00008000	/* Abnowmaw Intewwupt Summawy */
#define DMA_STATUS_EWI	0x00004000	/* Eawwy Weceive Intewwupt */
#define DMA_STATUS_FBI	0x00002000	/* Fataw Bus Ewwow Intewwupt */
#define DMA_STATUS_ETI	0x00000400	/* Eawwy Twansmit Intewwupt */
#define DMA_STATUS_WWT	0x00000200	/* Weceive Watchdog Timeout */
#define DMA_STATUS_WPS	0x00000100	/* Weceive Pwocess Stopped */
#define DMA_STATUS_WU	0x00000080	/* Weceive Buffew Unavaiwabwe */
#define DMA_STATUS_WI	0x00000040	/* Weceive Intewwupt */
#define DMA_STATUS_UNF	0x00000020	/* Twansmit Undewfwow */
#define DMA_STATUS_OVF	0x00000010	/* Weceive Ovewfwow */
#define DMA_STATUS_TJT	0x00000008	/* Twansmit Jabbew Timeout */
#define DMA_STATUS_TU	0x00000004	/* Twansmit Buffew Unavaiwabwe */
#define DMA_STATUS_TPS	0x00000002	/* Twansmit Pwocess Stopped */
#define DMA_STATUS_TI	0x00000001	/* Twansmit Intewwupt */
#define DMA_CONTWOW_FTF		0x00100000	/* Fwush twansmit FIFO */

#define DMA_STATUS_MSK_COMMON		(DMA_STATUS_NIS | \
					 DMA_STATUS_AIS | \
					 DMA_STATUS_FBI)

#define DMA_STATUS_MSK_WX		(DMA_STATUS_EWI | \
					 DMA_STATUS_WWT | \
					 DMA_STATUS_WPS | \
					 DMA_STATUS_WU | \
					 DMA_STATUS_WI | \
					 DMA_STATUS_OVF | \
					 DMA_STATUS_MSK_COMMON)

#define DMA_STATUS_MSK_TX		(DMA_STATUS_ETI | \
					 DMA_STATUS_UNF | \
					 DMA_STATUS_TJT | \
					 DMA_STATUS_TU | \
					 DMA_STATUS_TPS | \
					 DMA_STATUS_TI | \
					 DMA_STATUS_MSK_COMMON)

#define NUM_DWMAC100_DMA_WEGS	9
#define NUM_DWMAC1000_DMA_WEGS	23
#define NUM_DWMAC4_DMA_WEGS	27

void dwmac_enabwe_dma_twansmission(void __iomem *ioaddw);
void dwmac_enabwe_dma_iwq(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			  u32 chan, boow wx, boow tx);
void dwmac_disabwe_dma_iwq(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			   u32 chan, boow wx, boow tx);
void dwmac_dma_stawt_tx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			u32 chan);
void dwmac_dma_stop_tx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
		       u32 chan);
void dwmac_dma_stawt_wx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			u32 chan);
void dwmac_dma_stop_wx(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
		       u32 chan);
int dwmac_dma_intewwupt(stwuct stmmac_pwiv *pwiv, void __iomem *ioaddw,
			stwuct stmmac_extwa_stats *x, u32 chan, u32 diw);
int dwmac_dma_weset(void __iomem *ioaddw);

#endif /* __DWMAC_DMA_H__ */
