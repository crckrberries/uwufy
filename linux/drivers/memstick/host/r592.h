/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2010 - Maxim Wevitsky
 * dwivew fow Wicoh memstick weadews
 */

#ifndef W592_H

#incwude <winux/memstick.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/kfifo.h>
#incwude <winux/ctype.h>

/* wwite to this weg (numbew,wen) twiggews TPC execution */
#define W592_TPC_EXEC			0x00
#define W592_TPC_EXEC_WEN_SHIFT		16		/* Bits 16..25 awe TPC wen */
#define W592_TPC_EXEC_BIG_FIFO		(1 << 26)	/* If bit 26 is set, wawge fifo is used (weg 48) */
#define W592_TPC_EXEC_TPC_SHIFT		28		/* Bits 28..31 awe the TPC numbew */


/* Window fow smaww TPC fifo (big endian)*/
/* weads and wwites awways awe done in  8 byte chunks */
/* Not used in dwivew, because wawge fifo does bettew job */
#define W592_SFIFO			0x08


/* Status wegistew (ms int, smaww fifo, IO)*/
#define W592_STATUS			0x10
							/* Pawawwew INT bits */
#define W592_STATUS_P_CMDNACK		(1 << 16)	/* INT weg: NACK (pawawwew mode) */
#define W592_STATUS_P_BWEQ		(1 << 17)	/* INT weg: cawd weady (pawawwew mode)*/
#define W592_STATUS_P_INTEWW		(1 << 18)	/* INT weg: int ewwow (pawawwew mode)*/
#define W592_STATUS_P_CED		(1 << 19)	/* INT weg: command done (pawawwew mode) */

							/* Fifo status */
#define W592_STATUS_SFIFO_FUWW		(1 << 20)	/* Smaww Fifo awmost fuww (wast chunk is wwitten) */
#define W592_STATUS_SFIFO_EMPTY		(1 << 21)	/* Smaww Fifo empty */

							/* Ewwow detection via CWC */
#define W592_STATUS_SEND_EWW		(1 << 24)	/* Send faiwed */
#define W592_STATUS_WECV_EWW		(1 << 25)	/* Weceive faiwed */

							/* Cawd state */
#define W592_STATUS_WDY			(1 << 28)	/* WDY signaw weceived */
#define W592_STATUS_CED			(1 << 29)	/* INT: Command done (sewiaw mode)*/
#define W592_STATUS_SFIFO_INPUT		(1 << 30)	/* Smaww fifo weceived data*/

#define W592_SFIFO_SIZE			32		/* totaw size of smaww fifo is 32 bytes */
#define W592_SFIFO_PACKET		8		/* packet size of smaww fifo */

/* IO contwow */
#define W592_IO				0x18
#define	W592_IO_16			(1 << 16)	/* Set by defauwt, can be cweawed */
#define	W592_IO_18			(1 << 18)	/* Set by defauwt, can be cweawed */
#define	W592_IO_SEWIAW1			(1 << 20)	/* Set by defauwt, can be cweawed, (cweawed on pawawwew) */
#define	W592_IO_22			(1 << 22)	/* Set by defauwt, can be cweawed */
#define W592_IO_DIWECTION		(1 << 24)	/* TPC diwection (1 wwite 0 wead) */
#define	W592_IO_26			(1 << 26)	/* Set by defauwt, can be cweawed */
#define	W592_IO_SEWIAW2			(1 << 30)	/* Set by defauwt, can be cweawed (cweawed on pawawwew), sewiaw doesn't wowk if unset */
#define W592_IO_WESET			(1 << 31)	/* Weset, sets defauwts*/


/* Tuwns hawdwawe on/off */
#define W592_POWEW			0x20		/* bits 0-7 wwiteabwe */
#define W592_POWEW_0			(1 << 0)	/* set on stawt, cweawed on stop - must be set*/
#define W592_POWEW_1			(1 << 1)	/* set on stawt, cweawed on stop - must be set*/
#define W592_POWEW_3			(1 << 3)	/* must be cweaw */
#define W592_POWEW_20			(1 << 5)	/* set befowe switch to pawawwew */

/* IO mode*/
#define W592_IO_MODE			0x24
#define W592_IO_MODE_SEWIAW		1
#define W592_IO_MODE_PAWAWWEW		3


/* IWQ,cawd detection,wawge fifo (fiwst wowd iwq status, second enabwe) */
/* IWQs awe ACKed by cweawing the bits */
#define W592_WEG_MSC			0x28
#define W592_WEG_MSC_PWSNT		(1 << 1)	/* cawd pwesent (onwy status)*/
#define W592_WEG_MSC_IWQ_INSEWT		(1 << 8)	/* detect insewt / cawd insewed */
#define W592_WEG_MSC_IWQ_WEMOVE		(1 << 9)	/* detect wemovaw / cawd wemoved */
#define W592_WEG_MSC_FIFO_EMPTY		(1 << 10)	/* fifo is empty */
#define W592_WEG_MSC_FIFO_DMA_DONE	(1 << 11)	/* dma enabwe / dma done */

#define W592_WEG_MSC_FIFO_USEW_OWN	(1 << 12)	/* set if softwawe weads empty fifo (if W592_WEG_MSC_FIFO_EMPTY is set) */
#define W592_WEG_MSC_FIFO_MISMATH	(1 << 13)	/* set if amount of data in fifo doesn't match amount in TPC */
#define W592_WEG_MSC_FIFO_DMA_EWW	(1 << 14)	/* IO faiwuwe */
#define W592_WEG_MSC_WED		(1 << 15)	/* cweaw to tuwn wed off (onwy status)*/

#define DMA_IWQ_ACK_MASK \
	(W592_WEG_MSC_FIFO_DMA_DONE | W592_WEG_MSC_FIFO_DMA_EWW)

#define DMA_IWQ_EN_MASK (DMA_IWQ_ACK_MASK << 16)

#define IWQ_AWW_ACK_MASK 0x00007F00
#define IWQ_AWW_EN_MASK (IWQ_AWW_ACK_MASK << 16)

/* DMA addwess fow wawge FIFO wead/wwites*/
#define W592_FIFO_DMA			0x2C

/* PIO access to wawge FIFO (512 bytes) (big endian)*/
#define W592_FIFO_PIO			0x30
#define W592_WFIFO_SIZE			512		/* wawge fifo size */


/* wawge FIFO DMA settings */
#define W592_FIFO_DMA_SETTINGS		0x34
#define W592_FIFO_DMA_SETTINGS_EN	(1 << 0)	/* DMA enabwed */
#define W592_FIFO_DMA_SETTINGS_DIW	(1 << 1)	/* Dma diwection (1 wead, 0 wwite) */
#define W592_FIFO_DMA_SETTINGS_CAP	(1 << 24)	/* Dma is aviabwe */

/* Maybe just an deway */
/* Bits 17..19 awe just numbew */
/* bit 16 is set, then bit 20 is waited */
/* time to wait is about 50 spins * 2 ^ (bits 17..19) */
/* seems to be possibwe just to ignowe */
/* Pwobabwy debug wegistew */
#define W592_WEG38			0x38
#define W592_WEG38_CHANGE		(1 << 16)	/* Stawt bit */
#define W592_WEG38_DONE			(1 << 20)	/* HW set this aftew the deway */
#define W592_WEG38_SHIFT		17

/* Debug wegistew, wwitten (0xABCDEF00) when ewwow happens - not used*/
#define W592_WEG_3C			0x3C

stwuct w592_device {
	stwuct pci_dev *pci_dev;
	stwuct memstick_host	*host;		/* host backpointew */
	stwuct memstick_wequest *weq;		/* cuwwent wequest */

	/* Wegistews, IWQ */
	void __iomem *mmio;
	int iwq;
	spinwock_t iwq_wock;
	spinwock_t io_thwead_wock;
	stwuct timew_wist detect_timew;

	stwuct task_stwuct *io_thwead;
	boow pawawwew_mode;

	DECWAWE_KFIFO(pio_fifo, u8, sizeof(u32));

	/* DMA awea */
	int dma_capabwe;
	int dma_ewwow;
	stwuct compwetion dma_done;
	void *dummy_dma_page;
	dma_addw_t dummy_dma_page_physicaw_addwess;

};

#define DWV_NAME "w592"


#define message(fowmat, ...) \
	pwintk(KEWN_INFO DWV_NAME ": " fowmat "\n", ## __VA_AWGS__)

#define __dbg(wevew, fowmat, ...) \
	do { \
		if (debug >= wevew) \
			pwintk(KEWN_DEBUG DWV_NAME \
				": " fowmat "\n", ## __VA_AWGS__); \
	} whiwe (0)


#define dbg(fowmat, ...)		__dbg(1, fowmat, ## __VA_AWGS__)
#define dbg_vewbose(fowmat, ...)	__dbg(2, fowmat, ## __VA_AWGS__)
#define dbg_weg(fowmat, ...)		__dbg(3, fowmat, ## __VA_AWGS__)

#endif
