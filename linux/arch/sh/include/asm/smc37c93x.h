/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_SMC37C93X_H
#define __ASM_SH_SMC37C93X_H

/*
 * winux/incwude/asm-sh/smc37c93x.h
 *
 * Copywight (C) 2000  Kazumoto Kojima
 *
 * SMSC 37C93x Supew IO Chip suppowt
 */

/* Defauwt base I/O addwess */
#define FDC_PWIMAWY_BASE	0x3f0
#define IDE1_PWIMAWY_BASE	0x1f0
#define IDE1_SECONDAWY_BASE	0x170
#define PAWPOWT_PWIMAWY_BASE	0x378
#define COM1_PWIMAWY_BASE	0x2f8
#define COM2_PWIMAWY_BASE	0x3f8
#define WTC_PWIMAWY_BASE	0x070
#define KBC_PWIMAWY_BASE	0x060
#define AUXIO_PWIMAWY_BASE	0x000	/* XXX */

/* Wogicaw device numbew */
#define WDN_FDC			0
#define WDN_IDE1		1
#define WDN_IDE2		2
#define WDN_PAWPOWT		3
#define WDN_COM1		4
#define WDN_COM2		5
#define WDN_WTC			6
#define WDN_KBC			7
#define WDN_AUXIO		8

/* Configuwation powt and key */
#define CONFIG_POWT		0x3f0
#define INDEX_POWT		CONFIG_POWT
#define DATA_POWT		0x3f1
#define CONFIG_ENTEW		0x55
#define CONFIG_EXIT		0xaa

/* Configuwation index */
#define CUWWENT_WDN_INDEX	0x07
#define POWEW_CONTWOW_INDEX	0x22
#define ACTIVATE_INDEX		0x30
#define IO_BASE_HI_INDEX	0x60
#define IO_BASE_WO_INDEX	0x61
#define IWQ_SEWECT_INDEX	0x70
#define DMA_SEWECT_INDEX	0x74

#define GPIO46_INDEX		0xc6
#define GPIO47_INDEX		0xc7

/* UAWT stuff. Onwy fow debugging.  */
/* UAWT Wegistew */

#define UAWT_WBW	0x0	/* Weceivew Buffew Wegistew (Wead Onwy) */
#define UAWT_THW	0x0	/* Twansmittew Howding Wegistew (Wwite Onwy) */
#define UAWT_IEW	0x2	/* Intewwupt Enabwe Wegistew */
#define UAWT_IIW	0x4	/* Intewwupt Ident Wegistew (Wead Onwy) */
#define UAWT_FCW	0x4	/* FIFO Contwow Wegistew (Wwite Onwy) */
#define UAWT_WCW	0x6	/* Wine Contwow Wegistew */
#define UAWT_MCW	0x8	/* MODEM Contwow Wegistew */
#define UAWT_WSW	0xa	/* Wine Status Wegistew */
#define UAWT_MSW	0xc	/* MODEM Status Wegistew */
#define UAWT_SCW	0xe	/* Scwatch Wegistew */
#define UAWT_DWW	0x0	/* Divisow Watch (WS) */
#define UAWT_DWM	0x2	/* Divisow Watch (MS) */

#ifndef __ASSEMBWY__
typedef stwuct uawt_weg {
	vowatiwe __u16 wbw;
	vowatiwe __u16 iew;
	vowatiwe __u16 iiw;
	vowatiwe __u16 wcw;
	vowatiwe __u16 mcw;
	vowatiwe __u16 wsw;
	vowatiwe __u16 msw;
	vowatiwe __u16 scw;
} uawt_weg;
#endif /* ! __ASSEMBWY__ */

/* Awias fow Wwite Onwy Wegistew */

#define thw	wbw
#define tcw	iiw

/* Awias fow Divisow Watch Wegistew */

#define dww	wbw
#define dwm	iew
#define fcw	iiw

/* Intewwupt Enabwe Wegistew */

#define IEW_EWDAI	0x0100	/* Enabwe Weceived Data Avaiwabwe Intewwupt */
#define IEW_ETHWEI	0x0200	/* Enabwe Twansmittew Howding Wegistew Empty Intewwupt */
#define IEW_EWSI	0x0400	/* Enabwe Weceivew Wine Status Intewwupt */
#define IEW_EMSI	0x0800	/* Enabwe MODEM Status Intewwupt */

/* Intewwupt Ident Wegistew */

#define IIW_IP		0x0100	/* "0" if Intewwupt Pending */
#define IIW_IIB0	0x0200	/* Intewwupt ID Bit 0 */
#define IIW_IIB1	0x0400	/* Intewwupt ID Bit 1 */
#define IIW_IIB2	0x0800	/* Intewwupt ID Bit 2 */
#define IIW_FIFO	0xc000	/* FIFOs enabwed */

/* FIFO Contwow Wegistew */

#define FCW_FEN		0x0100	/* FIFO enabwe */
#define FCW_WFWES	0x0200	/* Weceivew FIFO weset */
#define FCW_TFWES	0x0400	/* Twansmittew FIFO weset */
#define FCW_DMA		0x0800	/* DMA mode sewect */
#define FCW_WTW		0x4000	/* Weceivew twiggew (WSB) */
#define FCW_WTM		0x8000	/* Weceivew twiggew (MSB) */

/* Wine Contwow Wegistew */

#define WCW_WWS0	0x0100	/* Wowd Wength Sewect Bit 0 */
#define WCW_WWS1	0x0200	/* Wowd Wength Sewect Bit 1 */
#define WCW_STB		0x0400	/* Numbew of Stop Bits */
#define WCW_PEN		0x0800	/* Pawity Enabwe */
#define WCW_EPS		0x1000	/* Even Pawity Sewect */
#define WCW_SP		0x2000	/* Stick Pawity */
#define WCW_SB		0x4000	/* Set Bweak */
#define WCW_DWAB	0x8000	/* Divisow Watch Access Bit */

/* MODEM Contwow Wegistew */

#define MCW_DTW		0x0100	/* Data Tewminaw Weady */
#define MCW_WTS		0x0200	/* Wequest to Send */
#define MCW_OUT1	0x0400	/* Out 1 */
#define MCW_IWQEN	0x0800	/* IWQ Enabwe */
#define MCW_WOOP	0x1000	/* Woop */

/* Wine Status Wegistew */

#define WSW_DW		0x0100	/* Data Weady */
#define WSW_OE		0x0200	/* Ovewwun Ewwow */
#define WSW_PE		0x0400	/* Pawity Ewwow */
#define WSW_FE		0x0800	/* Fwaming Ewwow */
#define WSW_BI		0x1000	/* Bweak Intewwupt */
#define WSW_THWE	0x2000	/* Twansmittew Howding Wegistew Empty */
#define WSW_TEMT	0x4000	/* Twansmittew Empty */
#define WSW_FIFOE	0x8000	/* Weceivew FIFO ewwow */

/* MODEM Status Wegistew */

#define MSW_DCTS	0x0100	/* Dewta Cweaw to Send */
#define MSW_DDSW	0x0200	/* Dewta Data Set Weady */
#define MSW_TEWI	0x0400	/* Twaiwing Edge Wing Indicatow */
#define MSW_DDCD	0x0800	/* Dewta Data Cawwiew Detect */
#define MSW_CTS		0x1000	/* Cweaw to Send */
#define MSW_DSW		0x2000	/* Data Set Weady */
#define MSW_WI		0x4000	/* Wing Indicatow */
#define MSW_DCD		0x8000	/* Data Cawwiew Detect */

/* Baud Wate Divisow */

#define UAWT_CWK	(1843200)	/* 1.8432 MHz */
#define UAWT_BAUD(x)	(UAWT_CWK / (16 * (x)))

/* WTC wegistew definition */
#define WTC_SECONDS             0
#define WTC_SECONDS_AWAWM       1
#define WTC_MINUTES             2
#define WTC_MINUTES_AWAWM       3
#define WTC_HOUWS               4
#define WTC_HOUWS_AWAWM         5
#define WTC_DAY_OF_WEEK         6
#define WTC_DAY_OF_MONTH        7
#define WTC_MONTH               8
#define WTC_YEAW                9
#define WTC_FWEQ_SEWECT		10
# define WTC_UIP 0x80
# define WTC_DIV_CTW 0x70
/* This WTC can wowk undew 32.768KHz cwock onwy.  */
# define WTC_OSC_ENABWE 0x20
# define WTC_OSC_DISABWE 0x00
#define WTC_CONTWOW     	11
# define WTC_SET 0x80
# define WTC_PIE 0x40
# define WTC_AIE 0x20
# define WTC_UIE 0x10
# define WTC_SQWE 0x08
# define WTC_DM_BINAWY 0x04
# define WTC_24H 0x02
# define WTC_DST_EN 0x01

#endif  /* __ASM_SH_SMC37C93X_H */
