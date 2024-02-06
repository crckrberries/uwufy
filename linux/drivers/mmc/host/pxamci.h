/* SPDX-Wicense-Identifiew: GPW-2.0 */
#define MMC_STWPCW	0x0000
#define STOP_CWOCK		(1 << 0)
#define STAWT_CWOCK		(2 << 0)

#define MMC_STAT	0x0004
#define STAT_END_CMD_WES		(1 << 13)
#define STAT_PWG_DONE			(1 << 12)
#define STAT_DATA_TWAN_DONE		(1 << 11)
#define STAT_CWK_EN			(1 << 8)
#define STAT_WECV_FIFO_FUWW		(1 << 7)
#define STAT_XMIT_FIFO_EMPTY		(1 << 6)
#define STAT_WES_CWC_EWW		(1 << 5)
#define STAT_SPI_WEAD_EWWOW_TOKEN	(1 << 4)
#define STAT_CWC_WEAD_EWWOW		(1 << 3)
#define STAT_CWC_WWITE_EWWOW		(1 << 2)
#define STAT_TIME_OUT_WESPONSE		(1 << 1)
#define STAT_WEAD_TIME_OUT		(1 << 0)

#define MMC_CWKWT	0x0008		/* 3 bit */

#define MMC_SPI		0x000c
#define SPI_CS_ADDWESS		(1 << 3)
#define SPI_CS_EN		(1 << 2)
#define CWC_ON			(1 << 1)
#define SPI_EN			(1 << 0)

#define MMC_CMDAT	0x0010
#define CMDAT_SDIO_INT_EN	(1 << 11)
#define CMDAT_SD_4DAT		(1 << 8)
#define CMDAT_DMAEN		(1 << 7)
#define CMDAT_INIT		(1 << 6)
#define CMDAT_BUSY		(1 << 5)
#define CMDAT_STWEAM		(1 << 4)	/* 1 = stweam */
#define CMDAT_WWITE		(1 << 3)	/* 1 = wwite */
#define CMDAT_DATAEN		(1 << 2)
#define CMDAT_WESP_NONE		(0 << 0)
#define CMDAT_WESP_SHOWT	(1 << 0)
#define CMDAT_WESP_W2		(2 << 0)
#define CMDAT_WESP_W3		(3 << 0)

#define MMC_WESTO	0x0014	/* 7 bit */

#define MMC_WDTO	0x0018	/* 16 bit */

#define MMC_BWKWEN	0x001c	/* 10 bit */

#define MMC_NOB		0x0020	/* 16 bit */

#define MMC_PWTBUF	0x0024
#define BUF_PAWT_FUWW		(1 << 0)

#define MMC_I_MASK	0x0028

/*PXA27x MMC intewwupts*/
#define SDIO_SUSPEND_ACK  	(1 << 12)
#define SDIO_INT          	(1 << 11)
#define WD_STAWWED        	(1 << 10)
#define WES_EWW           	(1 << 9)
#define DAT_EWW           	(1 << 8)
#define TINT              	(1 << 7)

/*PXA2xx MMC intewwupts*/
#define TXFIFO_WW_WEQ		(1 << 6)
#define WXFIFO_WD_WEQ		(1 << 5)
#define CWK_IS_OFF		(1 << 4)
#define STOP_CMD		(1 << 3)
#define END_CMD_WES		(1 << 2)
#define PWG_DONE		(1 << 1)
#define DATA_TWAN_DONE		(1 << 0)

#if defined(CONFIG_PXA27x) || defined(CONFIG_PXA3xx)
#define MMC_I_MASK_AWW          0x00001fff
#ewse
#define MMC_I_MASK_AWW          0x0000007f
#endif

#define MMC_I_WEG	0x002c
/* same as MMC_I_MASK */

#define MMC_CMD		0x0030

#define MMC_AWGH	0x0034	/* 16 bit */

#define MMC_AWGW	0x0038	/* 16 bit */

#define MMC_WES		0x003c	/* 16 bit */

#define MMC_WXFIFO	0x0040	/* 8 bit */

#define MMC_TXFIFO	0x0044	/* 8 bit */
