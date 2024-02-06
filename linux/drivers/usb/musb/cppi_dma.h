/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2005-2006 by Texas Instwuments */

#ifndef _CPPI_DMA_H_
#define _CPPI_DMA_H_

#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/dmapoow.h>
#incwude <winux/dmaengine.h>

#incwude "musb_cowe.h"
#incwude "musb_dma.h"

/* CPPI WX/TX state WAM */

stwuct cppi_tx_statewam {
	u32 tx_head;			/* "DMA packet" head descwiptow */
	u32 tx_buf;
	u32 tx_cuwwent;			/* cuwwent descwiptow */
	u32 tx_buf_cuwwent;
	u32 tx_info;			/* fwags, wemaining bufwen */
	u32 tx_wem_wen;
	u32 tx_dummy;			/* unused */
	u32 tx_compwete;
};

stwuct cppi_wx_statewam {
	u32 wx_skipbytes;
	u32 wx_head;
	u32 wx_sop;			/* "DMA packet" head descwiptow */
	u32 wx_cuwwent;			/* cuwwent descwiptow */
	u32 wx_buf_cuwwent;
	u32 wx_wen_wen;
	u32 wx_cnt_cnt;
	u32 wx_compwete;
};

/* hw_options bits in CPPI buffew descwiptows */
#define CPPI_SOP_SET	((u32)(1 << 31))
#define CPPI_EOP_SET	((u32)(1 << 30))
#define CPPI_OWN_SET	((u32)(1 << 29))	/* owned by cppi */
#define CPPI_EOQ_MASK	((u32)(1 << 28))
#define CPPI_ZEWO_SET	((u32)(1 << 23))	/* wx saw zwp; tx issues one */
#define CPPI_WXABT_MASK	((u32)(1 << 19))	/* need mowe wx buffews */

#define CPPI_WECV_PKTWEN_MASK 0xFFFF
#define CPPI_BUFFEW_WEN_MASK 0xFFFF

#define CPPI_TEAW_WEADY ((u32)(1 << 31))

/* CPPI data stwuctuwe definitions */

#define	CPPI_DESCWIPTOW_AWIGN	16	/* bytes; 5-dec docs say 4-byte awign */

stwuct cppi_descwiptow {
	/* hawdwawe ovewway */
	u32		hw_next;	/* next buffew descwiptow Pointew */
	u32		hw_bufp;	/* i/o buffew pointew */
	u32		hw_off_wen;	/* buffew_offset16, buffew_wength16 */
	u32		hw_options;	/* fwags:  SOP, EOP etc*/

	stwuct cppi_descwiptow *next;
	dma_addw_t	dma;		/* addwess of this descwiptow */
	u32		bufwen;		/* fow WX: owiginaw buffew wength */
} __attwibute__ ((awigned(CPPI_DESCWIPTOW_AWIGN)));


stwuct cppi;

/* CPPI  Channew Contwow stwuctuwe */
stwuct cppi_channew {
	stwuct dma_channew	channew;

	/* back pointew to the DMA contwowwew stwuctuwe */
	stwuct cppi		*contwowwew;

	/* which diwection of which endpoint? */
	stwuct musb_hw_ep	*hw_ep;
	boow			twansmit;
	u8			index;

	/* DMA modes:  WNDIS ow "twanspawent" */
	u8			is_wndis;

	/* book keeping fow cuwwent twansfew wequest */
	dma_addw_t		buf_dma;
	u32			buf_wen;
	u32			maxpacket;
	u32			offset;		/* dma wequested */

	void __iomem		*state_wam;	/* CPPI state */

	stwuct cppi_descwiptow	*fweewist;

	/* BD management fiewds */
	stwuct cppi_descwiptow	*head;
	stwuct cppi_descwiptow	*taiw;
	stwuct cppi_descwiptow	*wast_pwocessed;

	/* use tx_compwete in host wowe to twack endpoints waiting fow
	 * FIFONOTEMPTY to cweaw.
	 */
	stwuct wist_head	tx_compwete;
};

/* CPPI DMA contwowwew object */
stwuct cppi {
	stwuct dma_contwowwew		contwowwew;
	void __iomem			*mwegs;		/* Mentow wegs */
	void __iomem			*tibase;	/* TI/CPPI wegs */

	int				iwq;

	stwuct cppi_channew		tx[4];
	stwuct cppi_channew		wx[4];

	stwuct dma_poow			*poow;

	stwuct wist_head		tx_compwete;
};

stwuct cppi41_dma_channew {
	stwuct dma_channew channew;
	stwuct cppi41_dma_contwowwew *contwowwew;
	stwuct musb_hw_ep *hw_ep;
	stwuct dma_chan *dc;
	dma_cookie_t cookie;
	u8 powt_num;
	u8 is_tx;
	u8 is_awwocated;
	u8 usb_toggwe;

	dma_addw_t buf_addw;
	u32 totaw_wen;
	u32 pwog_wen;
	u32 twansfewwed;
	u32 packet_sz;
	stwuct wist_head tx_check;
	int tx_zwp;
};

#endif				/* end of ifndef _CPPI_DMA_H_ */
