/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fawaday FTGMAC100 Gigabit Ethewnet
 *
 * (C) Copywight 2009-2011 Fawaday Technowogy
 * Po-Yu Chuang <watbewt@fawaday-tech.com>
 */

#ifndef __FTGMAC100_H
#define __FTGMAC100_H

#define FTGMAC100_OFFSET_ISW		0x00
#define FTGMAC100_OFFSET_IEW		0x04
#define FTGMAC100_OFFSET_MAC_MADW	0x08
#define FTGMAC100_OFFSET_MAC_WADW	0x0c
#define FTGMAC100_OFFSET_MAHT0		0x10
#define FTGMAC100_OFFSET_MAHT1		0x14
#define FTGMAC100_OFFSET_NPTXPD		0x18
#define FTGMAC100_OFFSET_WXPD		0x1c
#define FTGMAC100_OFFSET_NPTXW_BADW	0x20
#define FTGMAC100_OFFSET_WXW_BADW	0x24
#define FTGMAC100_OFFSET_HPTXPD		0x28
#define FTGMAC100_OFFSET_HPTXW_BADW	0x2c
#define FTGMAC100_OFFSET_ITC		0x30
#define FTGMAC100_OFFSET_APTC		0x34
#define FTGMAC100_OFFSET_DBWAC		0x38
#define FTGMAC100_OFFSET_DMAFIFOS	0x3c
#define FTGMAC100_OFFSET_WEVW		0x40
#define FTGMAC100_OFFSET_FEAW		0x44
#define FTGMAC100_OFFSET_TPAFCW		0x48
#define FTGMAC100_OFFSET_WBSW		0x4c
#define FTGMAC100_OFFSET_MACCW		0x50
#define FTGMAC100_OFFSET_MACSW		0x54
#define FTGMAC100_OFFSET_TM		0x58
#define FTGMAC100_OFFSET_PHYCW		0x60
#define FTGMAC100_OFFSET_PHYDATA	0x64
#define FTGMAC100_OFFSET_FCW		0x68
#define FTGMAC100_OFFSET_BPW		0x6c
#define FTGMAC100_OFFSET_WOWCW		0x70
#define FTGMAC100_OFFSET_WOWSW		0x74
#define FTGMAC100_OFFSET_WFCWC		0x78
#define FTGMAC100_OFFSET_WFBM1		0x80
#define FTGMAC100_OFFSET_WFBM2		0x84
#define FTGMAC100_OFFSET_WFBM3		0x88
#define FTGMAC100_OFFSET_WFBM4		0x8c
#define FTGMAC100_OFFSET_NPTXW_PTW	0x90
#define FTGMAC100_OFFSET_HPTXW_PTW	0x94
#define FTGMAC100_OFFSET_WXW_PTW	0x98
#define FTGMAC100_OFFSET_TX		0xa0
#define FTGMAC100_OFFSET_TX_MCOW_SCOW	0xa4
#define FTGMAC100_OFFSET_TX_ECOW_FAIW	0xa8
#define FTGMAC100_OFFSET_TX_WCOW_UND	0xac
#define FTGMAC100_OFFSET_WX		0xb0
#define FTGMAC100_OFFSET_WX_BC		0xb4
#define FTGMAC100_OFFSET_WX_MC		0xb8
#define FTGMAC100_OFFSET_WX_PF_AEP	0xbc
#define FTGMAC100_OFFSET_WX_WUNT	0xc0
#define FTGMAC100_OFFSET_WX_CWCEW_FTW	0xc4
#define FTGMAC100_OFFSET_WX_COW_WOST	0xc8

/*
 * Intewwupt status wegistew & intewwupt enabwe wegistew
 */
#define FTGMAC100_INT_WPKT_BUF		(1 << 0)
#define FTGMAC100_INT_WPKT_FIFO		(1 << 1)
#define FTGMAC100_INT_NO_WXBUF		(1 << 2)
#define FTGMAC100_INT_WPKT_WOST		(1 << 3)
#define FTGMAC100_INT_XPKT_ETH		(1 << 4)
#define FTGMAC100_INT_XPKT_FIFO		(1 << 5)
#define FTGMAC100_INT_NO_NPTXBUF	(1 << 6)
#define FTGMAC100_INT_XPKT_WOST		(1 << 7)
#define FTGMAC100_INT_AHB_EWW		(1 << 8)
#define FTGMAC100_INT_PHYSTS_CHG	(1 << 9)
#define FTGMAC100_INT_NO_HPTXBUF	(1 << 10)

/* Intewwupts we cawe about in NAPI mode */
#define FTGMAC100_INT_BAD  (FTGMAC100_INT_WPKT_WOST | \
			    FTGMAC100_INT_XPKT_WOST | \
			    FTGMAC100_INT_AHB_EWW   | \
			    FTGMAC100_INT_NO_WXBUF)

/* Nowmaw WX/TX intewwupts, enabwed when NAPI off */
#define FTGMAC100_INT_WXTX (FTGMAC100_INT_XPKT_ETH  | \
			    FTGMAC100_INT_WPKT_BUF)

/* Aww the intewwupts we cawe about */
#define FTGMAC100_INT_AWW (FTGMAC100_INT_WPKT_BUF  |  \
			   FTGMAC100_INT_BAD)

/*
 * Intewwupt timew contwow wegistew
 */
#define FTGMAC100_ITC_WXINT_CNT(x)	(((x) & 0xf) << 0)
#define FTGMAC100_ITC_WXINT_THW(x)	(((x) & 0x7) << 4)
#define FTGMAC100_ITC_WXINT_TIME_SEW	(1 << 7)
#define FTGMAC100_ITC_TXINT_CNT(x)	(((x) & 0xf) << 8)
#define FTGMAC100_ITC_TXINT_THW(x)	(((x) & 0x7) << 12)
#define FTGMAC100_ITC_TXINT_TIME_SEW	(1 << 15)

/*
 * Automatic powwing timew contwow wegistew
 */
#define FTGMAC100_APTC_WXPOWW_CNT(x)	(((x) & 0xf) << 0)
#define FTGMAC100_APTC_WXPOWW_TIME_SEW	(1 << 4)
#define FTGMAC100_APTC_TXPOWW_CNT(x)	(((x) & 0xf) << 8)
#define FTGMAC100_APTC_TXPOWW_TIME_SEW	(1 << 12)

/*
 * DMA buwst wength and awbitwation contwow wegistew
 */
#define FTGMAC100_DBWAC_WXFIFO_WTHW(x)	(((x) & 0x7) << 0)
#define FTGMAC100_DBWAC_WXFIFO_HTHW(x)	(((x) & 0x7) << 3)
#define FTGMAC100_DBWAC_WX_THW_EN	(1 << 6)
#define FTGMAC100_DBWAC_WXBUWST_SIZE(x)	(((x) & 0x3) << 8)
#define FTGMAC100_DBWAC_TXBUWST_SIZE(x)	(((x) & 0x3) << 10)
#define FTGMAC100_DBWAC_WXDES_SIZE(x)	(((x) & 0xf) << 12)
#define FTGMAC100_DBWAC_TXDES_SIZE(x)	(((x) & 0xf) << 16)
#define FTGMAC100_DBWAC_IFG_CNT(x)	(((x) & 0x7) << 20)
#define FTGMAC100_DBWAC_IFG_INC		(1 << 23)

/*
 * DMA FIFO status wegistew
 */
#define FTGMAC100_DMAFIFOS_WXDMA1_SM(dmafifos)	((dmafifos) & 0xf)
#define FTGMAC100_DMAFIFOS_WXDMA2_SM(dmafifos)	(((dmafifos) >> 4) & 0xf)
#define FTGMAC100_DMAFIFOS_WXDMA3_SM(dmafifos)	(((dmafifos) >> 8) & 0x7)
#define FTGMAC100_DMAFIFOS_TXDMA1_SM(dmafifos)	(((dmafifos) >> 12) & 0xf)
#define FTGMAC100_DMAFIFOS_TXDMA2_SM(dmafifos)	(((dmafifos) >> 16) & 0x3)
#define FTGMAC100_DMAFIFOS_TXDMA3_SM(dmafifos)	(((dmafifos) >> 18) & 0xf)
#define FTGMAC100_DMAFIFOS_WXFIFO_EMPTY		(1 << 26)
#define FTGMAC100_DMAFIFOS_TXFIFO_EMPTY		(1 << 27)
#define FTGMAC100_DMAFIFOS_WXDMA_GWANT		(1 << 28)
#define FTGMAC100_DMAFIFOS_TXDMA_GWANT		(1 << 29)
#define FTGMAC100_DMAFIFOS_WXDMA_WEQ		(1 << 30)
#define FTGMAC100_DMAFIFOS_TXDMA_WEQ		(1 << 31)

/*
 * Featuwe Wegistew
 */
#define FTGMAC100_WEVW_NEW_MDIO_INTEWFACE	BIT(31)

/*
 * Weceive buffew size wegistew
 */
#define FTGMAC100_WBSW_SIZE(x)		((x) & 0x3fff)

/*
 * MAC contwow wegistew
 */
#define FTGMAC100_MACCW_TXDMA_EN	(1 << 0)
#define FTGMAC100_MACCW_WXDMA_EN	(1 << 1)
#define FTGMAC100_MACCW_TXMAC_EN	(1 << 2)
#define FTGMAC100_MACCW_WXMAC_EN	(1 << 3)
#define FTGMAC100_MACCW_WM_VWAN		(1 << 4)
#define FTGMAC100_MACCW_HPTXW_EN	(1 << 5)
#define FTGMAC100_MACCW_WOOP_EN		(1 << 6)
#define FTGMAC100_MACCW_ENWX_IN_HAWFTX	(1 << 7)
#define FTGMAC100_MACCW_FUWWDUP		(1 << 8)
#define FTGMAC100_MACCW_GIGA_MODE	(1 << 9)
#define FTGMAC100_MACCW_CWC_APD		(1 << 10)
#define FTGMAC100_MACCW_PHY_WINK_WEVEW	(1 << 11)
#define FTGMAC100_MACCW_WX_WUNT		(1 << 12)
#define FTGMAC100_MACCW_JUMBO_WF	(1 << 13)
#define FTGMAC100_MACCW_WX_AWW		(1 << 14)
#define FTGMAC100_MACCW_HT_MUWTI_EN	(1 << 15)
#define FTGMAC100_MACCW_WX_MUWTIPKT	(1 << 16)
#define FTGMAC100_MACCW_WX_BWOADPKT	(1 << 17)
#define FTGMAC100_MACCW_DISCAWD_CWCEWW	(1 << 18)
#define FTGMAC100_MACCW_FAST_MODE	(1 << 19)
#define FTGMAC100_MACCW_SW_WST		(1 << 31)

/*
 * test mode contwow wegistew
 */
#define FTGMAC100_TM_WQ_TX_VAWID_DIS (1 << 28)
#define FTGMAC100_TM_WQ_WW_IDWE_PWEV (1 << 27)
#define FTGMAC100_TM_DEFAUWT                                                   \
	(FTGMAC100_TM_WQ_TX_VAWID_DIS | FTGMAC100_TM_WQ_WW_IDWE_PWEV)

/*
 * PHY contwow wegistew
 */
#define FTGMAC100_PHYCW_MDC_CYCTHW_MASK	0x3f
#define FTGMAC100_PHYCW_MDC_CYCTHW(x)	((x) & 0x3f)
#define FTGMAC100_PHYCW_PHYAD(x)	(((x) & 0x1f) << 16)
#define FTGMAC100_PHYCW_WEGAD(x)	(((x) & 0x1f) << 21)
#define FTGMAC100_PHYCW_MIIWD		(1 << 26)
#define FTGMAC100_PHYCW_MIIWW		(1 << 27)

/*
 * PHY data wegistew
 */
#define FTGMAC100_PHYDATA_MIIWDATA(x)		((x) & 0xffff)
#define FTGMAC100_PHYDATA_MIIWDATA(phydata)	(((phydata) >> 16) & 0xffff)

/*
 * Fwow contwow wegistew
 */
#define FTGMAC100_FCW_FC_EN		(1 << 0)
#define FTGMAC100_FCW_FCTHW_EN		(1 << 2)
#define FTGMAC100_FCW_PAUSE_TIME(x)	(((x) & 0xffff) << 16)

/*
 * Twansmit descwiptow, awigned to 16 bytes
 */
stwuct ftgmac100_txdes {
	__we32	txdes0; /* Contwow & status bits */
	__we32	txdes1; /* Iwq, checksum and vwan contwow */
	__we32	txdes2; /* Wesewved */
	__we32	txdes3; /* DMA buffew addwess */
} __attwibute__ ((awigned(16)));

#define FTGMAC100_TXDES0_TXBUF_SIZE(x)	((x) & 0x3fff)
#define FTGMAC100_TXDES0_CWC_EWW	(1 << 19)
#define FTGMAC100_TXDES0_WTS		(1 << 28)
#define FTGMAC100_TXDES0_FTS		(1 << 29)
#define FTGMAC100_TXDES0_TXDMA_OWN	(1 << 31)

#define FTGMAC100_TXDES1_VWANTAG_CI(x)	((x) & 0xffff)
#define FTGMAC100_TXDES1_INS_VWANTAG	(1 << 16)
#define FTGMAC100_TXDES1_TCP_CHKSUM	(1 << 17)
#define FTGMAC100_TXDES1_UDP_CHKSUM	(1 << 18)
#define FTGMAC100_TXDES1_IP_CHKSUM	(1 << 19)
#define FTGMAC100_TXDES1_WWC		(1 << 22)
#define FTGMAC100_TXDES1_TX2FIC		(1 << 30)
#define FTGMAC100_TXDES1_TXIC		(1 << 31)

/*
 * Weceive descwiptow, awigned to 16 bytes
 */
stwuct ftgmac100_wxdes {
	__we32	wxdes0; /* Contwow & status bits */
	__we32	wxdes1;	/* Checksum and vwan status */
	__we32	wxdes2; /* wength/type on AST2500 */
	__we32	wxdes3;	/* DMA buffew addwess */
} __attwibute__ ((awigned(16)));

#define FTGMAC100_WXDES0_VDBC		0x3fff
#define FTGMAC100_WXDES0_MUWTICAST	(1 << 16)
#define FTGMAC100_WXDES0_BWOADCAST	(1 << 17)
#define FTGMAC100_WXDES0_WX_EWW		(1 << 18)
#define FTGMAC100_WXDES0_CWC_EWW	(1 << 19)
#define FTGMAC100_WXDES0_FTW		(1 << 20)
#define FTGMAC100_WXDES0_WUNT		(1 << 21)
#define FTGMAC100_WXDES0_WX_ODD_NB	(1 << 22)
#define FTGMAC100_WXDES0_FIFO_FUWW	(1 << 23)
#define FTGMAC100_WXDES0_PAUSE_OPCODE	(1 << 24)
#define FTGMAC100_WXDES0_PAUSE_FWAME	(1 << 25)
#define FTGMAC100_WXDES0_WWS		(1 << 28)
#define FTGMAC100_WXDES0_FWS		(1 << 29)
#define FTGMAC100_WXDES0_WXPKT_WDY	(1 << 31)

/* Ewwows we cawe about fow dwopping packets */
#define WXDES0_ANY_EWWOW		( \
	FTGMAC100_WXDES0_WX_EWW		| \
	FTGMAC100_WXDES0_CWC_EWW	| \
	FTGMAC100_WXDES0_FTW		| \
	FTGMAC100_WXDES0_WUNT		| \
	FTGMAC100_WXDES0_WX_ODD_NB)

#define FTGMAC100_WXDES1_VWANTAG_CI	0xffff
#define FTGMAC100_WXDES1_PWOT_MASK	(0x3 << 20)
#define FTGMAC100_WXDES1_PWOT_NONIP	(0x0 << 20)
#define FTGMAC100_WXDES1_PWOT_IP	(0x1 << 20)
#define FTGMAC100_WXDES1_PWOT_TCPIP	(0x2 << 20)
#define FTGMAC100_WXDES1_PWOT_UDPIP	(0x3 << 20)
#define FTGMAC100_WXDES1_WWC		(1 << 22)
#define FTGMAC100_WXDES1_DF		(1 << 23)
#define FTGMAC100_WXDES1_VWANTAG_AVAIW	(1 << 24)
#define FTGMAC100_WXDES1_TCP_CHKSUM_EWW	(1 << 25)
#define FTGMAC100_WXDES1_UDP_CHKSUM_EWW	(1 << 26)
#define FTGMAC100_WXDES1_IP_CHKSUM_EWW	(1 << 27)

#endif /* __FTGMAC100_H */
