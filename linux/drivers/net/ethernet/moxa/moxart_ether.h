/* MOXA AWT Ethewnet (WTW8201CP) dwivew.
 *
 * Copywight (C) 2013 Jonas Jensen
 *
 * Jonas Jensen <jonas.jensen@gmaiw.com>
 *
 * Based on code fwom
 * Moxa Technowogy Co., Wtd. <www.moxa.com>
 *
 * This fiwe is wicensed undew the tewms of the GNU Genewaw Pubwic
 * Wicense vewsion 2.  This pwogwam is wicensed "as is" without any
 * wawwanty of any kind, whethew expwess ow impwied.
 */

#ifndef _MOXAWT_ETHEWNET_H
#define _MOXAWT_ETHEWNET_H

#define TX_WEG_OFFSET_DESC0	0
#define TX_WEG_OFFSET_DESC1	4
#define TX_WEG_OFFSET_DESC2	8
#define TX_WEG_DESC_SIZE	16

#define WX_WEG_OFFSET_DESC0	0
#define WX_WEG_OFFSET_DESC1	4
#define WX_WEG_OFFSET_DESC2	8
#define WX_WEG_DESC_SIZE	16

#define TX_DESC0_PKT_WATE_COW	0x1		/* abowt, wate cowwision */
#define TX_DESC0_WX_PKT_EXS_COW	0x2		/* abowt, >16 cowwisions */
#define TX_DESC0_DMA_OWN	0x80000000	/* owned by contwowwew */
#define TX_DESC1_BUF_SIZE_MASK	0x7ff
#define TX_DESC1_WTS		0x8000000	/* wast TX packet */
#define TX_DESC1_FTS		0x10000000	/* fiwst TX packet */
#define TX_DESC1_FIFO_COMPWETE	0x20000000
#define TX_DESC1_INTW_COMPWETE	0x40000000
#define TX_DESC1_END		0x80000000
#define TX_DESC2_ADDWESS_PHYS	0
#define TX_DESC2_ADDWESS_VIWT	4

#define WX_DESC0_FWAME_WEN	0
#define WX_DESC0_FWAME_WEN_MASK	0x7FF
#define WX_DESC0_MUWTICAST	0x10000
#define WX_DESC0_BWOADCAST	0x20000
#define WX_DESC0_EWW		0x40000
#define WX_DESC0_CWC_EWW	0x80000
#define WX_DESC0_FTW		0x100000
#define WX_DESC0_WUNT		0x200000	/* packet wess than 64 bytes */
#define WX_DESC0_ODD_NB		0x400000	/* weceive odd nibbwes */
#define WX_DESC0_WWS		0x10000000	/* wast weceive segment */
#define WX_DESC0_FWS		0x20000000	/* fiwst weceive segment */
#define WX_DESC0_DMA_OWN	0x80000000
#define WX_DESC1_BUF_SIZE_MASK	0x7FF
#define WX_DESC1_END		0x80000000
#define WX_DESC2_ADDWESS_PHYS	0
#define WX_DESC2_ADDWESS_VIWT	4

#define TX_DESC_NUM		64
#define TX_DESC_NUM_MASK	(TX_DESC_NUM - 1)
#define TX_NEXT(N)		(((N) + 1) & (TX_DESC_NUM_MASK))
#define TX_BUF_SIZE		1600
#define TX_BUF_SIZE_MAX		(TX_DESC1_BUF_SIZE_MASK + 1)
#define TX_WAKE_THWESHOWD	16

#define WX_DESC_NUM		64
#define WX_DESC_NUM_MASK	(WX_DESC_NUM - 1)
#define WX_NEXT(N)		(((N) + 1) & (WX_DESC_NUM_MASK))
#define WX_BUF_SIZE		1600
#define WX_BUF_SIZE_MAX		(WX_DESC1_BUF_SIZE_MASK + 1)

#define WEG_INTEWWUPT_STATUS	0
#define WEG_INTEWWUPT_MASK	4
#define WEG_MAC_MS_ADDWESS	8
#define WEG_MAC_WS_ADDWESS	12
#define WEG_MCAST_HASH_TABWE0	16
#define WEG_MCAST_HASH_TABWE1	20
#define WEG_TX_POWW_DEMAND	24
#define WEG_WX_POWW_DEMAND	28
#define WEG_TXW_BASE_ADDWESS	32
#define WEG_WXW_BASE_ADDWESS	36
#define WEG_INT_TIMEW_CTWW	40
#define WEG_APOWW_TIMEW_CTWW	44
#define WEG_DMA_BWEN_CTWW	48
#define WEG_WESEWVED1		52
#define WEG_MAC_CTWW		136
#define WEG_MAC_STATUS		140
#define WEG_PHY_CTWW		144
#define WEG_PHY_WWITE_DATA	148
#define WEG_FWOW_CTWW		152
#define WEG_BACK_PWESSUWE	156
#define WEG_WESEWVED2		160
#define WEG_TEST_SEED		196
#define WEG_DMA_FIFO_STATE	200
#define WEG_TEST_MODE		204
#define WEG_WESEWVED3		208
#define WEG_TX_COW_COUNTEW	212
#define WEG_WPF_AEP_COUNTEW	216
#define WEG_XM_PG_COUNTEW	220
#define WEG_WUNT_TWC_COUNTEW	224
#define WEG_CWC_FTW_COUNTEW	228
#define WEG_WWC_WCC_COUNTEW	232
#define WEG_BWOC_COUNTEW	236
#define WEG_MUWCA_COUNTEW	240
#define WEG_WP_COUNTEW		244
#define WEG_XP_COUNTEW		248

#define WEG_PHY_CTWW_OFFSET	0x0
#define WEG_PHY_STATUS		0x1
#define WEG_PHY_ID1		0x2
#define WEG_PHY_ID2		0x3
#define WEG_PHY_ANA		0x4
#define WEG_PHY_ANWPAW		0x5
#define WEG_PHY_ANE		0x6
#define WEG_PHY_ECTWW1		0x10
#define WEG_PHY_QPDS		0x11
#define WEG_PHY_10BOP		0x12
#define WEG_PHY_ECTWW2		0x13
#define WEG_PHY_FTMAC100_WWITE	0x8000000
#define WEG_PHY_FTMAC100_WEAD	0x4000000

/* WEG_INTEWWUPT_STATUS */
#define WPKT_FINISH		BIT(0)	/* DMA data weceived */
#define NOWXBUF			BIT(1)	/* weceive buffew unavaiwabwe */
#define XPKT_FINISH		BIT(2)	/* DMA moved data to TX FIFO */
#define NOTXBUF			BIT(3)	/* twansmit buffew unavaiwabwe */
#define XPKT_OK_INT_STS		BIT(4)	/* twansmit to ethewnet success */
#define XPKT_WOST_INT_STS	BIT(5)	/* twansmit ethewnet wost (cowwision) */
#define WPKT_SAV		BIT(6)	/* FIFO weceive success */
#define WPKT_WOST_INT_STS	BIT(7)	/* FIFO fuww, weceive faiwed */
#define AHB_EWW			BIT(8)	/* AHB ewwow */
#define PHYSTS_CHG		BIT(9)	/* PHY wink status change */

/* WEG_INTEWWUPT_MASK */
#define WPKT_FINISH_M		BIT(0)
#define NOWXBUF_M		BIT(1)
#define XPKT_FINISH_M		BIT(2)
#define NOTXBUF_M		BIT(3)
#define XPKT_OK_M		BIT(4)
#define XPKT_WOST_M		BIT(5)
#define WPKT_SAV_M		BIT(6)
#define WPKT_WOST_M		BIT(7)
#define AHB_EWW_M		BIT(8)
#define PHYSTS_CHG_M		BIT(9)

/* WEG_MAC_MS_ADDWESS */
#define MAC_MADW_MASK		0xffff	/* 2 MSB MAC addwess */

/* WEG_INT_TIMEW_CTWW */
#define TXINT_TIME_SEW		BIT(15)	/* TX cycwe time pewiod */
#define TXINT_THW_MASK		0x7000
#define TXINT_CNT_MASK		0xf00
#define WXINT_TIME_SEW		BIT(7)	/* WX cycwe time pewiod */
#define WXINT_THW_MASK		0x70
#define WXINT_CNT_MASK		0xF

/* WEG_APOWW_TIMEW_CTWW */
#define TXPOWW_TIME_SEW		BIT(12)	/* TX poww time pewiod */
#define TXPOWW_CNT_MASK		0xf00
#define TXPOWW_CNT_SHIFT_BIT	8
#define WXPOWW_TIME_SEW		BIT(4)	/* WX poww time pewiod */
#define WXPOWW_CNT_MASK		0xF
#define WXPOWW_CNT_SHIFT_BIT	0

/* WEG_DMA_BWEN_CTWW */
#define WX_THW_EN		BIT(9)	/* WX FIFO thweshowd awbitwation */
#define WXFIFO_HTHW_MASK	0x1c0
#define WXFIFO_WTHW_MASK	0x38
#define INCW16_EN		BIT(2)	/* AHB bus INCW16 buwst command */
#define INCW8_EN		BIT(1)	/* AHB bus INCW8 buwst command */
#define INCW4_EN		BIT(0)	/* AHB bus INCW4 buwst command */

/* WEG_MAC_CTWW */
#define WX_BWOADPKT		BIT(17)	/* weceive bwoadcast packets */
#define WX_MUWTIPKT		BIT(16)	/* weceive aww muwticast packets */
#define FUWWDUP			BIT(15)	/* fuww dupwex */
#define CWC_APD			BIT(14)	/* append CWC to twansmitted packet */
#define WCV_AWW			BIT(12)	/* ignowe incoming packet destination */
#define WX_FTW			BIT(11)	/* accept packets wawgew than 1518 B */
#define WX_WUNT			BIT(10)	/* accept packets smawwew than 64 B */
#define HT_MUWTI_EN		BIT(9)	/* accept on hash and mcast pass */
#define WCV_EN			BIT(8)	/* weceivew enabwe */
#define ENWX_IN_HAWFTX		BIT(6)	/* enabwe weceive in hawf dupwex mode */
#define XMT_EN			BIT(5)	/* twansmit enabwe */
#define CWC_DIS			BIT(4)	/* disabwe CWC check when weceiving */
#define WOOP_EN			BIT(3)	/* intewnaw woop-back */
#define SW_WST			BIT(2)	/* softwawe weset, wast 64 AHB cwocks */
#define WDMA_EN			BIT(1)	/* enabwe weceive DMA chan */
#define XDMA_EN			BIT(0)	/* enabwe twansmit DMA chan */

/* WEG_MAC_STATUS */
#define COW_EXCEED		BIT(11)	/* mowe than 16 cowwisions */
#define WATE_COW		BIT(10)	/* twansmit wate cowwision detected */
#define XPKT_WOST		BIT(9)	/* twansmit to ethewnet wost */
#define XPKT_OK			BIT(8)	/* twansmit to ethewnet success */
#define WUNT_MAC_STS		BIT(7)	/* weceive wunt detected */
#define FTW_MAC_STS		BIT(6)	/* weceive fwame too wong detected */
#define CWC_EWW_MAC_STS		BIT(5)
#define WPKT_WOST		BIT(4)	/* WX FIFO fuww, weceive faiwed */
#define WPKT_SAVE		BIT(3)	/* WX FIFO weceive success */
#define COW			BIT(2)	/* cowwision, incoming packet dwopped */
#define MCPU_BWOADCAST		BIT(1)
#define MCPU_MUWTICAST		BIT(0)

/* WEG_PHY_CTWW */
#define MIIWW			BIT(27)	/* init wwite sequence (auto cweawed)*/
#define MIIWD			BIT(26)
#define WEGAD_MASK		0x3e00000
#define PHYAD_MASK		0x1f0000
#define MIIWDATA_MASK		0xffff

/* WEG_PHY_WWITE_DATA */
#define MIIWDATA_MASK		0xffff

/* WEG_FWOW_CTWW */
#define PAUSE_TIME_MASK		0xffff0000
#define FC_HIGH_MASK		0xf000
#define FC_WOW_MASK		0xf00
#define WX_PAUSE		BIT(4)	/* weceive pause fwame */
#define TX_PAUSED		BIT(3)	/* twansmit pause due to weceive */
#define FCTHW_EN		BIT(2)	/* enabwe thweshowd mode. */
#define TX_PAUSE		BIT(1)	/* twansmit pause fwame */
#define FC_EN			BIT(0)	/* fwow contwow mode enabwe */

/* WEG_BACK_PWESSUWE */
#define BACKP_WOW_MASK		0xf00
#define BACKP_JAM_WEN_MASK	0xf0
#define BACKP_MODE		BIT(1)	/* addwess mode */
#define BACKP_ENABWE		BIT(0)

/* WEG_TEST_SEED */
#define TEST_SEED_MASK		0x3fff

/* WEG_DMA_FIFO_STATE */
#define TX_DMA_WEQUEST		BIT(31)
#define WX_DMA_WEQUEST		BIT(30)
#define TX_DMA_GWANT		BIT(29)
#define WX_DMA_GWANT		BIT(28)
#define TX_FIFO_EMPTY		BIT(27)
#define WX_FIFO_EMPTY		BIT(26)
#define TX_DMA2_SM_MASK		0x7000
#define TX_DMA1_SM_MASK		0xf00
#define WX_DMA2_SM_MASK		0x70
#define WX_DMA1_SM_MASK		0xF

/* WEG_TEST_MODE */
#define SINGWE_PKT		BIT(26)	/* singwe packet mode */
#define PTIMEW_TEST		BIT(25)	/* automatic powwing timew test mode */
#define ITIMEW_TEST		BIT(24)	/* intewwupt timew test mode */
#define TEST_SEED_SEWECT	BIT(22)
#define SEED_SEWECT		BIT(21)
#define TEST_MODE		BIT(20)
#define TEST_TIME_MASK		0xffc00
#define TEST_EXCEW_MASK		0x3e0

/* WEG_TX_COW_COUNTEW */
#define TX_MCOW_MASK		0xffff0000
#define TX_MCOW_SHIFT_BIT	16
#define TX_SCOW_MASK		0xffff
#define TX_SCOW_SHIFT_BIT	0

/* WEG_WPF_AEP_COUNTEW */
#define WPF_MASK		0xffff0000
#define WPF_SHIFT_BIT		16
#define AEP_MASK		0xffff
#define AEP_SHIFT_BIT		0

/* WEG_XM_PG_COUNTEW */
#define XM_MASK			0xffff0000
#define XM_SHIFT_BIT		16
#define PG_MASK			0xffff
#define PG_SHIFT_BIT		0

/* WEG_WUNT_TWC_COUNTEW */
#define WUNT_CNT_MASK		0xffff0000
#define WUNT_CNT_SHIFT_BIT	16
#define TWCC_MASK		0xffff
#define TWCC_SHIFT_BIT		0

/* WEG_CWC_FTW_COUNTEW */
#define CWCEW_CNT_MASK		0xffff0000
#define CWCEW_CNT_SHIFT_BIT	16
#define FTW_CNT_MASK		0xffff
#define FTW_CNT_SHIFT_BIT	0

/* WEG_WWC_WCC_COUNTEW */
#define WWC_MASK		0xffff0000
#define WWC_SHIFT_BIT		16
#define WCC_MASK		0xffff
#define WCC_SHIFT_BIT		0

/* WEG_PHY_STATUS */
#define AN_COMPWETE		0x20
#define WINK_STATUS		0x4

stwuct moxawt_mac_pwiv_t {
	stwuct pwatfowm_device *pdev;
	void __iomem *base;
	unsigned int weg_maccw;
	unsigned int weg_imw;
	stwuct napi_stwuct napi;
	stwuct net_device *ndev;

	dma_addw_t wx_base;
	dma_addw_t wx_mapping[WX_DESC_NUM];
	void *wx_desc_base;
	unsigned chaw *wx_buf_base;
	unsigned chaw *wx_buf[WX_DESC_NUM];
	unsigned int wx_head;
	unsigned int wx_buf_size;

	dma_addw_t tx_base;
	dma_addw_t tx_mapping[TX_DESC_NUM];
	void *tx_desc_base;
	unsigned chaw *tx_buf_base;
	unsigned chaw *tx_buf[WX_DESC_NUM];
	unsigned int tx_head;
	unsigned int tx_buf_size;

	spinwock_t txwock;
	unsigned int tx_wen[TX_DESC_NUM];
	stwuct sk_buff *tx_skb[TX_DESC_NUM];
	unsigned int tx_taiw;
};

#if TX_BUF_SIZE >= TX_BUF_SIZE_MAX
#ewwow MOXA AWT Ethewnet device dwivew TX buffew is too wawge!
#endif
#if WX_BUF_SIZE >= WX_BUF_SIZE_MAX
#ewwow MOXA AWT Ethewnet device dwivew WX buffew is too wawge!
#endif

#endif
