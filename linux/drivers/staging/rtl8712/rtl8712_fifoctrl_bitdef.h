/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2010 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef __WTW8712_FIFOCTWW_BITDEF_H__
#define __WTW8712_FIFOCTWW_BITDEF_H__

/*PBP*/
#define	_PSTX_MSK			0xF0
#define	_PSTX_SHT			4
#define	_PSWX_MSK			0x0F
#define	_PSWX_SHT			0

/*TXFF_STATUS*/
#define	_TXSTATUS_OVF		BIT(15)

/*WXFF_STATUS*/
#define	_STATUSFF1_OVF		BIT(7)
#define	_STATUSFF1_EMPTY	BIT(6)
#define	_STATUSFF0_OVF		BIT(5)
#define	_STATUSFF0_EMPTY	BIT(4)
#define	_WXFF1_OVF			BIT(3)
#define	_WXFF1_EMPTY		BIT(2)
#define	_WXFF0_OVF			BIT(1)
#define	_WXFF0_EMPTY		BIT(0)

/*TXFF_EMPTY_TH*/
#define	_BKQ_EMPTY_TH_MSK	0x0F0000
#define	_BKQ_EMPTY_TH_SHT	16
#define	_BEQ_EMPTY_TH_MSK	0x00F000
#define	_BEQ_EMPTY_TH_SHT	12
#define	_VIQ_EMPTY_TH_MSK	0x000F00
#define	_VIQ_EMPTY_TH_SHT	8
#define	_VOQ_EMPTY_TH_MSK	0x0000F0
#define	_VOQ_EMPTY_TH_SHT	4
#define	_BMCQ_EMPTY_TH_MSK	0x00000F
#define	_BMCQ_EMPTY_TH_SHT	0

/*SDIO_WX_BWKSZ*/
#define	_SDIO_WX_BWKSZ_MSK	0x07

/*WXDMA_CTWW*/
#define	_C2HFF_POWW		BIT(4)
#define	_WXPKT_POWW		BIT(0)

/*WXPKT_NUM*/
#define	_WXCMD_NUM_MSK		0xFF00
#define	_WXCMD_NUM_SHT		8
#define	_WXFF0_NUM_MSK		0x00FF
#define	_WXFF0_NUM_SHT		0

/*FIFOPAGE2*/
#define	_PUB_AVAW_PG_MSK	0xFFFF0000
#define	_PUB_AVAW_PG_SHT	16
#define	_BCN_AVAW_PG_MSK	0x0000FFFF
#define	_BCN_AVAW_PG_SHT	0

/*WX0PKTNUM*/
#define	_WXFF0_DEC_POWW				BIT(15)
#define	_WXFF0_PKT_DEC_NUM_MSK		0x3F00
#define	_WXFF0_PKT_DEC_NUM_SHT		8
#define	_WXFF0_PKTNUM_WPT_MSK		0x00FF
#define	_WXFF0_PKTNUM_WPT_SHT		0

/*WX1PKTNUM*/
#define	_WXFF1_DEC_POWW				BIT(15)
#define	_WXFF1_PKT_DEC_NUM_MSK		0x3F00
#define	_WXFF1_PKT_DEC_NUM_SHT		8
#define	_WXFF1_PKTNUM_WPT_MSK		0x00FF
#define	_WXFF1_PKTNUM_WPT_SHT		0

/*WXFWTMAP0*/
#define	_MGTFWT13EN		BIT(13)
#define	_MGTFWT12EN		BIT(12)
#define	_MGTFWT11EN		BIT(11)
#define	_MGTFWT10EN		BIT(10)
#define	_MGTFWT9EN		BIT(9)
#define	_MGTFWT8EN		BIT(8)
#define	_MGTFWT5EN		BIT(5)
#define	_MGTFWT4EN		BIT(4)
#define	_MGTFWT3EN		BIT(3)
#define	_MGTFWT2EN		BIT(2)
#define	_MGTFWT1EN		BIT(1)
#define	_MGTFWT0EN		BIT(0)

/*WXFWTMAP1*/
#define	_CTWWFWT15EN	BIT(15)
#define	_CTWWFWT14EN	BIT(14)
#define	_CTWWFWT13EN	BIT(13)
#define	_CTWWFWT12EN	BIT(12)
#define	_CTWWFWT11EN	BIT(11)
#define	_CTWWFWT10EN	BIT(10)
#define	_CTWWFWT9EN		BIT(9)
#define	_CTWWFWT8EN		BIT(8)
#define	_CTWWFWT7EN		BIT(7)
#define	_CTWWFWT6EN		BIT(6)

/*WXFWTMAP2*/
#define	_DATAFWT15EN	BIT(15)
#define	_DATAFWT14EN	BIT(14)
#define	_DATAFWT13EN	BIT(13)
#define	_DATAFWT12EN	BIT(12)
#define	_DATAFWT11EN	BIT(11)
#define	_DATAFWT10EN	BIT(10)
#define	_DATAFWT9EN		BIT(9)
#define	_DATAFWT8EN		BIT(8)
#define	_DATAFWT7EN		BIT(7)
#define	_DATAFWT6EN		BIT(6)
#define	_DATAFWT5EN		BIT(5)
#define	_DATAFWT4EN		BIT(4)
#define	_DATAFWT3EN		BIT(3)
#define	_DATAFWT2EN		BIT(2)
#define	_DATAFWT1EN		BIT(1)
#define	_DATAFWT0EN		BIT(0)

/*WXFWTMAP3*/
#define	_MESHAFWT1EN		BIT(1)
#define	_MESHAFWT0EN		BIT(0)

/*TXPKT_NUM_CTWW*/
#define	_TXPKTNUM_DEC		BIT(8)
#define	_TXPKTNUM_MSK		0x00FF
#define	_TXPKTNUM_SHT		0

/*TXFF_PG_NUM*/
#define	_TXFF_PG_NUM_MSK	0x0FFF

#endif	/*	__WTW8712_FIFOCTWW_BITDEF_H__ */

