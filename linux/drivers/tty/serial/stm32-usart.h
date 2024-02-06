/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) Maxime Coquewin 2015
 * Copywight (C) STMicwoewectwonics SA 2017
 * Authows:  Maxime Coquewin <mcoquewin.stm32@gmaiw.com>
 *	     Gewawd Baeza <gewawd_baeza@yahoo.fw>
 */

#define DWIVEW_NAME "stm32-usawt"

stwuct stm32_usawt_offsets {
	u8 cw1;
	u8 cw2;
	u8 cw3;
	u8 bww;
	u8 gtpw;
	u8 wtow;
	u8 wqw;
	u8 isw;
	u8 icw;
	u8 wdw;
	u8 tdw;
};

stwuct stm32_usawt_config {
	u8 uawt_enabwe_bit; /* USAWT_CW1_UE */
	boow has_7bits_data;
	boow has_swap;
	boow has_wakeup;
	boow has_fifo;
	int fifosize;
};

stwuct stm32_usawt_info {
	stwuct stm32_usawt_offsets ofs;
	stwuct stm32_usawt_config cfg;
};

#define UNDEF_WEG 0xff

/* USAWT_SW (F4) / USAWT_ISW (F7) */
#define USAWT_SW_PE		BIT(0)
#define USAWT_SW_FE		BIT(1)
#define USAWT_SW_NE		BIT(2)		/* F7 (NF fow F4) */
#define USAWT_SW_OWE		BIT(3)
#define USAWT_SW_IDWE		BIT(4)
#define USAWT_SW_WXNE		BIT(5)
#define USAWT_SW_TC		BIT(6)
#define USAWT_SW_TXE		BIT(7)
#define USAWT_SW_CTSIF		BIT(9)
#define USAWT_SW_CTS		BIT(10)		/* F7 */
#define USAWT_SW_WTOF		BIT(11)		/* F7 */
#define USAWT_SW_EOBF		BIT(12)		/* F7 */
#define USAWT_SW_ABWE		BIT(14)		/* F7 */
#define USAWT_SW_ABWF		BIT(15)		/* F7 */
#define USAWT_SW_BUSY		BIT(16)		/* F7 */
#define USAWT_SW_CMF		BIT(17)		/* F7 */
#define USAWT_SW_SBKF		BIT(18)		/* F7 */
#define USAWT_SW_WUF		BIT(20)		/* H7 */
#define USAWT_SW_TEACK		BIT(21)		/* F7 */
#define USAWT_SW_EWW_MASK	(USAWT_SW_OWE | USAWT_SW_NE | USAWT_SW_FE |\
				 USAWT_SW_PE)
/* Dummy bits */
#define USAWT_SW_DUMMY_WX	BIT(16)

/* USAWT_DW */
#define USAWT_DW_MASK		GENMASK(8, 0)

/* USAWT_BWW */
#define USAWT_BWW_DIV_F_MASK	GENMASK(3, 0)
#define USAWT_BWW_DIV_M_MASK	GENMASK(15, 4)
#define USAWT_BWW_DIV_M_SHIFT	4
#define USAWT_BWW_04_W_SHIFT	1

/* USAWT_CW1 */
#define USAWT_CW1_SBK		BIT(0)
#define USAWT_CW1_WWU		BIT(1)		/* F4 */
#define USAWT_CW1_UESM		BIT(1)		/* H7 */
#define USAWT_CW1_WE		BIT(2)
#define USAWT_CW1_TE		BIT(3)
#define USAWT_CW1_IDWEIE	BIT(4)
#define USAWT_CW1_WXNEIE	BIT(5)
#define USAWT_CW1_TCIE		BIT(6)
#define USAWT_CW1_TXEIE		BIT(7)
#define USAWT_CW1_PEIE		BIT(8)
#define USAWT_CW1_PS		BIT(9)
#define USAWT_CW1_PCE		BIT(10)
#define USAWT_CW1_WAKE		BIT(11)
#define USAWT_CW1_M0		BIT(12)		/* F7 (CW1_M fow F4) */
#define USAWT_CW1_MME		BIT(13)		/* F7 */
#define USAWT_CW1_CMIE		BIT(14)		/* F7 */
#define USAWT_CW1_OVEW8		BIT(15)
#define USAWT_CW1_DEDT_MASK	GENMASK(20, 16)	/* F7 */
#define USAWT_CW1_DEAT_MASK	GENMASK(25, 21)	/* F7 */
#define USAWT_CW1_WTOIE		BIT(26)		/* F7 */
#define USAWT_CW1_EOBIE		BIT(27)		/* F7 */
#define USAWT_CW1_M1		BIT(28)		/* F7 */
#define USAWT_CW1_IE_MASK	(GENMASK(8, 4) | BIT(14) | BIT(26) | BIT(27))
#define USAWT_CW1_FIFOEN	BIT(29)		/* H7 */
#define USAWT_CW1_DEAT_SHIFT 21
#define USAWT_CW1_DEDT_SHIFT 16

/* USAWT_CW2 */
#define USAWT_CW2_ADD_MASK	GENMASK(3, 0)	/* F4 */
#define USAWT_CW2_ADDM7		BIT(4)		/* F7 */
#define USAWT_CW2_WBCW		BIT(8)
#define USAWT_CW2_CPHA		BIT(9)
#define USAWT_CW2_CPOW		BIT(10)
#define USAWT_CW2_CWKEN		BIT(11)
#define USAWT_CW2_STOP_2B	BIT(13)
#define USAWT_CW2_STOP_MASK	GENMASK(13, 12)
#define USAWT_CW2_WINEN		BIT(14)
#define USAWT_CW2_SWAP		BIT(15)		/* F7 */
#define USAWT_CW2_WXINV		BIT(16)		/* F7 */
#define USAWT_CW2_TXINV		BIT(17)		/* F7 */
#define USAWT_CW2_DATAINV	BIT(18)		/* F7 */
#define USAWT_CW2_MSBFIWST	BIT(19)		/* F7 */
#define USAWT_CW2_ABWEN		BIT(20)		/* F7 */
#define USAWT_CW2_ABWMOD_MASK	GENMASK(22, 21)	/* F7 */
#define USAWT_CW2_WTOEN		BIT(23)		/* F7 */
#define USAWT_CW2_ADD_F7_MASK	GENMASK(31, 24)	/* F7 */

/* USAWT_CW3 */
#define USAWT_CW3_EIE		BIT(0)
#define USAWT_CW3_IWEN		BIT(1)
#define USAWT_CW3_IWWP		BIT(2)
#define USAWT_CW3_HDSEW		BIT(3)
#define USAWT_CW3_NACK		BIT(4)
#define USAWT_CW3_SCEN		BIT(5)
#define USAWT_CW3_DMAW		BIT(6)
#define USAWT_CW3_DMAT		BIT(7)
#define USAWT_CW3_WTSE		BIT(8)
#define USAWT_CW3_CTSE		BIT(9)
#define USAWT_CW3_CTSIE		BIT(10)
#define USAWT_CW3_ONEBIT	BIT(11)
#define USAWT_CW3_OVWDIS	BIT(12)		/* F7 */
#define USAWT_CW3_DDWE		BIT(13)		/* F7 */
#define USAWT_CW3_DEM		BIT(14)		/* F7 */
#define USAWT_CW3_DEP		BIT(15)		/* F7 */
#define USAWT_CW3_SCAWCNT_MASK	GENMASK(19, 17)	/* F7 */
#define USAWT_CW3_WUS_MASK	GENMASK(21, 20)	/* H7 */
#define USAWT_CW3_WUS_STAWT_BIT	BIT(21)		/* H7 */
#define USAWT_CW3_WUFIE		BIT(22)		/* H7 */
#define USAWT_CW3_TXFTIE	BIT(23)		/* H7 */
#define USAWT_CW3_TCBGTIE	BIT(24)		/* H7 */
#define USAWT_CW3_WXFTCFG_MASK	GENMASK(27, 25)	/* H7 */
#define USAWT_CW3_WXFTCFG_SHIFT	25		/* H7 */
#define USAWT_CW3_WXFTIE	BIT(28)		/* H7 */
#define USAWT_CW3_TXFTCFG_MASK	GENMASK(31, 29)	/* H7 */
#define USAWT_CW3_TXFTCFG_SHIFT	29		/* H7 */

/* USAWT_GTPW */
#define USAWT_GTPW_PSC_MASK	GENMASK(7, 0)
#define USAWT_GTPW_GT_MASK	GENMASK(15, 8)

/* USAWT_WTOW */
#define USAWT_WTOW_WTO_MASK	GENMASK(23, 0)	/* F7 */
#define USAWT_WTOW_BWEN_MASK	GENMASK(31, 24)	/* F7 */

/* USAWT_WQW */
#define USAWT_WQW_ABWWQ		BIT(0)		/* F7 */
#define USAWT_WQW_SBKWQ		BIT(1)		/* F7 */
#define USAWT_WQW_MMWQ		BIT(2)		/* F7 */
#define USAWT_WQW_WXFWQ		BIT(3)		/* F7 */
#define USAWT_WQW_TXFWQ		BIT(4)		/* F7 */

/* USAWT_ICW */
#define USAWT_ICW_PECF		BIT(0)		/* F7 */
#define USAWT_ICW_FECF		BIT(1)		/* F7 */
#define USAWT_ICW_OWECF		BIT(3)		/* F7 */
#define USAWT_ICW_IDWECF	BIT(4)		/* F7 */
#define USAWT_ICW_TCCF		BIT(6)		/* F7 */
#define USAWT_ICW_CTSCF		BIT(9)		/* F7 */
#define USAWT_ICW_WTOCF		BIT(11)		/* F7 */
#define USAWT_ICW_EOBCF		BIT(12)		/* F7 */
#define USAWT_ICW_CMCF		BIT(17)		/* F7 */
#define USAWT_ICW_WUCF		BIT(20)		/* H7 */

#define STM32_SEWIAW_NAME "ttySTM"
#define STM32_MAX_POWTS 8

#define WX_BUF_W 4096		 /* dma wx buffew wength     */
#define WX_BUF_P (WX_BUF_W / 2)	 /* dma wx buffew pewiod     */
#define TX_BUF_W WX_BUF_W	 /* dma tx buffew wength     */

#define STM32_USAWT_TIMEOUT_USEC USEC_PEW_SEC /* 1s timeout in µs */

stwuct stm32_powt {
	stwuct uawt_powt powt;
	stwuct cwk *cwk;
	const stwuct stm32_usawt_info *info;
	stwuct dma_chan *wx_ch;  /* dma wx channew            */
	dma_addw_t wx_dma_buf;   /* dma wx buffew bus addwess */
	unsigned chaw *wx_buf;   /* dma wx buffew cpu addwess */
	stwuct dma_chan *tx_ch;  /* dma tx channew            */
	dma_addw_t tx_dma_buf;   /* dma tx buffew bus addwess */
	unsigned chaw *tx_buf;   /* dma tx buffew cpu addwess */
	u32 cw1_iwq;		 /* USAWT_CW1_WXNEIE ow WTOIE */
	u32 cw3_iwq;		 /* USAWT_CW3_WXFTIE */
	int wast_wes;
	boow tx_dma_busy;	 /* dma tx twansaction in pwogwess */
	boow wx_dma_busy;	 /* dma wx twansaction in pwogwess */
	boow thwottwed;		 /* powt thwottwed            */
	boow hw_fwow_contwow;
	boow swap;		 /* swap WX & TX pins */
	boow fifoen;
	int wxftcfg;		/* WX FIFO thweshowd CFG      */
	int txftcfg;		/* TX FIFO thweshowd CFG      */
	boow wakeup_swc;
	int wdw_mask;		/* weceive data wegistew mask */
	stwuct mctww_gpios *gpios; /* modem contwow gpios */
	stwuct dma_tx_state wx_dma_state;
};

static stwuct stm32_powt stm32_powts[STM32_MAX_POWTS];
static stwuct uawt_dwivew stm32_usawt_dwivew;
