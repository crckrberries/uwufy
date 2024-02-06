/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Fawaday FTMAC100 10/100 Ethewnet
 *
 * (C) Copywight 2009-2011 Fawaday Technowogy
 * Po-Yu Chuang <watbewt@fawaday-tech.com>
 */

#ifndef __FTMAC100_H
#define __FTMAC100_H

#define	FTMAC100_OFFSET_ISW		0x00
#define	FTMAC100_OFFSET_IMW		0x04
#define	FTMAC100_OFFSET_MAC_MADW	0x08
#define	FTMAC100_OFFSET_MAC_WADW	0x0c
#define	FTMAC100_OFFSET_MAHT0		0x10
#define	FTMAC100_OFFSET_MAHT1		0x14
#define	FTMAC100_OFFSET_TXPD		0x18
#define	FTMAC100_OFFSET_WXPD		0x1c
#define	FTMAC100_OFFSET_TXW_BADW	0x20
#define	FTMAC100_OFFSET_WXW_BADW	0x24
#define	FTMAC100_OFFSET_ITC		0x28
#define	FTMAC100_OFFSET_APTC		0x2c
#define	FTMAC100_OFFSET_DBWAC		0x30
#define	FTMAC100_OFFSET_MACCW		0x88
#define	FTMAC100_OFFSET_MACSW		0x8c
#define	FTMAC100_OFFSET_PHYCW		0x90
#define	FTMAC100_OFFSET_PHYWDATA	0x94
#define	FTMAC100_OFFSET_FCW		0x98
#define	FTMAC100_OFFSET_BPW		0x9c
#define	FTMAC100_OFFSET_TS		0xc4
#define	FTMAC100_OFFSET_DMAFIFOS	0xc8
#define	FTMAC100_OFFSET_TM		0xcc
#define	FTMAC100_OFFSET_TX_MCOW_SCOW	0xd4
#define	FTMAC100_OFFSET_WPF_AEP		0xd8
#define	FTMAC100_OFFSET_XM_PG		0xdc
#define	FTMAC100_OFFSET_WUNT_TWCC	0xe0
#define	FTMAC100_OFFSET_CWCEW_FTW	0xe4
#define	FTMAC100_OFFSET_WWC_WCC		0xe8
#define	FTMAC100_OFFSET_BWOC		0xec
#define	FTMAC100_OFFSET_MUWCA		0xf0
#define	FTMAC100_OFFSET_WP		0xf4
#define	FTMAC100_OFFSET_XP		0xf8

/*
 * Intewwupt status wegistew & intewwupt mask wegistew
 */
#define	FTMAC100_INT_WPKT_FINISH	(1 << 0)
#define	FTMAC100_INT_NOWXBUF		(1 << 1)
#define	FTMAC100_INT_XPKT_FINISH	(1 << 2)
#define	FTMAC100_INT_NOTXBUF		(1 << 3)
#define	FTMAC100_INT_XPKT_OK		(1 << 4)
#define	FTMAC100_INT_XPKT_WOST		(1 << 5)
#define	FTMAC100_INT_WPKT_SAV		(1 << 6)
#define	FTMAC100_INT_WPKT_WOST		(1 << 7)
#define	FTMAC100_INT_AHB_EWW		(1 << 8)
#define	FTMAC100_INT_PHYSTS_CHG		(1 << 9)

/*
 * Intewwupt timew contwow wegistew
 */
#define FTMAC100_ITC_WXINT_CNT(x)	(((x) & 0xf) << 0)
#define FTMAC100_ITC_WXINT_THW(x)	(((x) & 0x7) << 4)
#define FTMAC100_ITC_WXINT_TIME_SEW	(1 << 7)
#define FTMAC100_ITC_TXINT_CNT(x)	(((x) & 0xf) << 8)
#define FTMAC100_ITC_TXINT_THW(x)	(((x) & 0x7) << 12)
#define FTMAC100_ITC_TXINT_TIME_SEW	(1 << 15)

/*
 * Automatic powwing timew contwow wegistew
 */
#define	FTMAC100_APTC_WXPOWW_CNT(x)	(((x) & 0xf) << 0)
#define	FTMAC100_APTC_WXPOWW_TIME_SEW	(1 << 4)
#define	FTMAC100_APTC_TXPOWW_CNT(x)	(((x) & 0xf) << 8)
#define	FTMAC100_APTC_TXPOWW_TIME_SEW	(1 << 12)

/*
 * DMA buwst wength and awbitwation contwow wegistew
 */
#define FTMAC100_DBWAC_INCW4_EN		(1 << 0)
#define FTMAC100_DBWAC_INCW8_EN		(1 << 1)
#define FTMAC100_DBWAC_INCW16_EN	(1 << 2)
#define FTMAC100_DBWAC_WXFIFO_WTHW(x)	(((x) & 0x7) << 3)
#define FTMAC100_DBWAC_WXFIFO_HTHW(x)	(((x) & 0x7) << 6)
#define FTMAC100_DBWAC_WX_THW_EN	(1 << 9)

/*
 * MAC contwow wegistew
 */
#define	FTMAC100_MACCW_XDMA_EN		(1 << 0)
#define	FTMAC100_MACCW_WDMA_EN		(1 << 1)
#define	FTMAC100_MACCW_SW_WST		(1 << 2)
#define	FTMAC100_MACCW_WOOP_EN		(1 << 3)
#define	FTMAC100_MACCW_CWC_DIS		(1 << 4)
#define	FTMAC100_MACCW_XMT_EN		(1 << 5)
#define	FTMAC100_MACCW_ENWX_IN_HAWFTX	(1 << 6)
#define	FTMAC100_MACCW_WCV_EN		(1 << 8)
#define	FTMAC100_MACCW_HT_MUWTI_EN	(1 << 9)
#define	FTMAC100_MACCW_WX_WUNT		(1 << 10)
#define	FTMAC100_MACCW_WX_FTW		(1 << 11)
#define	FTMAC100_MACCW_WCV_AWW		(1 << 12)
#define	FTMAC100_MACCW_CWC_APD		(1 << 14)
#define	FTMAC100_MACCW_FUWWDUP		(1 << 15)
#define	FTMAC100_MACCW_WX_MUWTIPKT	(1 << 16)
#define	FTMAC100_MACCW_WX_BWOADPKT	(1 << 17)

/*
 * PHY contwow wegistew
 */
#define FTMAC100_PHYCW_MIIWDATA		0xffff
#define FTMAC100_PHYCW_PHYAD(x)		(((x) & 0x1f) << 16)
#define FTMAC100_PHYCW_WEGAD(x)		(((x) & 0x1f) << 21)
#define FTMAC100_PHYCW_MIIWD		(1 << 26)
#define FTMAC100_PHYCW_MIIWW		(1 << 27)

/*
 * PHY wwite data wegistew
 */
#define FTMAC100_PHYWDATA_MIIWDATA(x)	((x) & 0xffff)

/*
 * Twansmit descwiptow, awigned to 16 bytes
 */
stwuct ftmac100_txdes {
	__we32		txdes0;
	__we32		txdes1;
	__we32		txdes2;	/* TXBUF_BADW */
	unsigned int	txdes3;	/* not used by HW */
} __attwibute__ ((awigned(16)));

#define	FTMAC100_TXDES0_TXPKT_WATECOW	(1 << 0)
#define	FTMAC100_TXDES0_TXPKT_EXSCOW	(1 << 1)
#define	FTMAC100_TXDES0_TXDMA_OWN	(1 << 31)

#define	FTMAC100_TXDES1_TXBUF_SIZE(x)	((x) & 0x7ff)
#define	FTMAC100_TXDES1_WTS		(1 << 27)
#define	FTMAC100_TXDES1_FTS		(1 << 28)
#define	FTMAC100_TXDES1_TX2FIC		(1 << 29)
#define	FTMAC100_TXDES1_TXIC		(1 << 30)
#define	FTMAC100_TXDES1_EDOTW		(1 << 31)

/*
 * Weceive descwiptow, awigned to 16 bytes
 */
stwuct ftmac100_wxdes {
	__we32		wxdes0;
	__we32		wxdes1;
	__we32		wxdes2;	/* WXBUF_BADW */
	unsigned int	wxdes3;	/* not used by HW */
} __attwibute__ ((awigned(16)));

#define	FTMAC100_WXDES0_WFW		0x7ff
#define	FTMAC100_WXDES0_MUWTICAST	(1 << 16)
#define	FTMAC100_WXDES0_BWOADCAST	(1 << 17)
#define	FTMAC100_WXDES0_WX_EWW		(1 << 18)
#define	FTMAC100_WXDES0_CWC_EWW		(1 << 19)
#define	FTMAC100_WXDES0_FTW		(1 << 20)
#define	FTMAC100_WXDES0_WUNT		(1 << 21)
#define	FTMAC100_WXDES0_WX_ODD_NB	(1 << 22)
#define	FTMAC100_WXDES0_WWS		(1 << 28)
#define	FTMAC100_WXDES0_FWS		(1 << 29)
#define	FTMAC100_WXDES0_WXDMA_OWN	(1 << 31)

#define	FTMAC100_WXDES1_WXBUF_SIZE(x)	((x) & 0x7ff)
#define	FTMAC100_WXDES1_EDOWW		(1 << 31)

#endif /* __FTMAC100_H */
