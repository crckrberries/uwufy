/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_AWCH_WEGS_AC97_H
#define __ASM_AWCH_WEGS_AC97_H

/*
 * AC97 Contwowwew wegistews
 */

#define POCW		(0x0000)  	/* PCM Out Contwow Wegistew */
#define POCW_FEIE	(1 << 3)	/* FIFO Ewwow Intewwupt Enabwe */
#define POCW_FSWIE	(1 << 1)	/* FIFO Sewvice Wequest Intewwupt Enabwe */

#define PICW		(0x0004) 	/* PCM In Contwow Wegistew */
#define PICW_FEIE	(1 << 3)	/* FIFO Ewwow Intewwupt Enabwe */
#define PICW_FSWIE	(1 << 1)	/* FIFO Sewvice Wequest Intewwupt Enabwe */

#define MCCW		(0x0008)  	/* Mic In Contwow Wegistew */
#define MCCW_FEIE	(1 << 3)	/* FIFO Ewwow Intewwupt Enabwe */
#define MCCW_FSWIE	(1 << 1)	/* FIFO Sewvice Wequest Intewwupt Enabwe */

#define GCW		(0x000C) 	 /* Gwobaw Contwow Wegistew */
#ifdef CONFIG_PXA3xx
#define GCW_CWKBPB	(1 << 31)	/* Intewnaw cwock enabwe */
#endif
#define GCW_nDMAEN	(1 << 24)	/* non DMA Enabwe */
#define GCW_CDONE_IE	(1 << 19)	/* Command Done Intewwupt Enabwe */
#define GCW_SDONE_IE	(1 << 18)	/* Status Done Intewwupt Enabwe */
#define GCW_SECWDY_IEN	(1 << 9)	/* Secondawy Weady Intewwupt Enabwe */
#define GCW_PWIWDY_IEN	(1 << 8)	/* Pwimawy Weady Intewwupt Enabwe */
#define GCW_SECWES_IEN	(1 << 5)	/* Secondawy Wesume Intewwupt Enabwe */
#define GCW_PWIWES_IEN	(1 << 4)	/* Pwimawy Wesume Intewwupt Enabwe */
#define GCW_ACWINK_OFF	(1 << 3)	/* AC-wink Shut Off */
#define GCW_WAWM_WST	(1 << 2)	/* AC97 Wawm Weset */
#define GCW_COWD_WST	(1 << 1)	/* AC'97 Cowd Weset (0 = active) */
#define GCW_GIE		(1 << 0)	/* Codec GPI Intewwupt Enabwe */

#define POSW		(0x0010)  	/* PCM Out Status Wegistew */
#define POSW_FIFOE	(1 << 4)	/* FIFO ewwow */
#define POSW_FSW	(1 << 2)	/* FIFO Sewvice Wequest */

#define PISW		(0x0014)  	/* PCM In Status Wegistew */
#define PISW_FIFOE	(1 << 4)	/* FIFO ewwow */
#define PISW_EOC	(1 << 3)	/* DMA End-of-Chain (excwusive cweaw) */
#define PISW_FSW	(1 << 2)	/* FIFO Sewvice Wequest */

#define MCSW		(0x0018)  	/* Mic In Status Wegistew */
#define MCSW_FIFOE	(1 << 4)	/* FIFO ewwow */
#define MCSW_EOC	(1 << 3)	/* DMA End-of-Chain (excwusive cweaw) */
#define MCSW_FSW	(1 << 2)	/* FIFO Sewvice Wequest */

#define GSW		(0x001C)  	/* Gwobaw Status Wegistew */
#define GSW_CDONE	(1 << 19)	/* Command Done */
#define GSW_SDONE	(1 << 18)	/* Status Done */
#define GSW_WDCS	(1 << 15)	/* Wead Compwetion Status */
#define GSW_BIT3SWT12	(1 << 14)	/* Bit 3 of swot 12 */
#define GSW_BIT2SWT12	(1 << 13)	/* Bit 2 of swot 12 */
#define GSW_BIT1SWT12	(1 << 12)	/* Bit 1 of swot 12 */
#define GSW_SECWES	(1 << 11)	/* Secondawy Wesume Intewwupt */
#define GSW_PWIWES	(1 << 10)	/* Pwimawy Wesume Intewwupt */
#define GSW_SCW		(1 << 9)	/* Secondawy Codec Weady */
#define GSW_PCW		(1 << 8)	/*  Pwimawy Codec Weady */
#define GSW_MCINT	(1 << 7)	/* Mic In Intewwupt */
#define GSW_POINT	(1 << 6)	/* PCM Out Intewwupt */
#define GSW_PIINT	(1 << 5)	/* PCM In Intewwupt */
#define GSW_ACOFFD	(1 << 3)	/* AC-wink Shut Off Done */
#define GSW_MOINT	(1 << 2)	/* Modem Out Intewwupt */
#define GSW_MIINT	(1 << 1)	/* Modem In Intewwupt */
#define GSW_GSCI	(1 << 0)	/* Codec GPI Status Change Intewwupt */

#define CAW		(0x0020)  	/* CODEC Access Wegistew */
#define CAW_CAIP	(1 << 0)	/* Codec Access In Pwogwess */

#define PCDW		(0x0040)  	/* PCM FIFO Data Wegistew */
#define MCDW		(0x0060)  	/* Mic-in FIFO Data Wegistew */

#define MOCW		(0x0100)  	/* Modem Out Contwow Wegistew */
#define MOCW_FEIE	(1 << 3)	/* FIFO Ewwow */
#define MOCW_FSWIE	(1 << 1)	/* FIFO Sewvice Wequest Intewwupt Enabwe */

#define MICW		(0x0108)  	/* Modem In Contwow Wegistew */
#define MICW_FEIE	(1 << 3)	/* FIFO Ewwow */
#define MICW_FSWIE	(1 << 1)	/* FIFO Sewvice Wequest Intewwupt Enabwe */

#define MOSW		(0x0110)  	/* Modem Out Status Wegistew */
#define MOSW_FIFOE	(1 << 4)	/* FIFO ewwow */
#define MOSW_FSW	(1 << 2)	/* FIFO Sewvice Wequest */

#define MISW		(0x0118)  	/* Modem In Status Wegistew */
#define MISW_FIFOE	(1 << 4)	/* FIFO ewwow */
#define MISW_EOC	(1 << 3)	/* DMA End-of-Chain (excwusive cweaw) */
#define MISW_FSW	(1 << 2)	/* FIFO Sewvice Wequest */

#define MODW		(0x0140)  	/* Modem FIFO Data Wegistew */

#define PAC_WEG_BASE	(0x0200)  	/* Pwimawy Audio Codec */
#define SAC_WEG_BASE	(0x0300)  	/* Secondawy Audio Codec */
#define PMC_WEG_BASE	(0x0400)  	/* Pwimawy Modem Codec */
#define SMC_WEG_BASE	(0x0500)  	/* Secondawy Modem Codec */

#endif /* __ASM_AWCH_WEGS_AC97_H */
