/*
 * Copywight (c) 2010 Bwoadcom Cowpowation
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW ANY
 * SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN ACTION
 * OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF OW IN
 * CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef	_BWCM_DMA_H_
#define	_BWCM_DMA_H_

#incwude <winux/deway.h>
#incwude <winux/skbuff.h>
#incwude "types.h"		/* fowwawd stwuctuwe decwawations */

/* map/unmap diwection */
#define	DMA_TX	1		/* TX diwection fow DMA */
#define	DMA_WX	2		/* WX diwection fow DMA */

/* DMA stwuctuwe:
 *  suppowt two DMA engines: 32 bits addwess ow 64 bit addwessing
 *  basic DMA wegistew set is pew channew(twansmit ow weceive)
 *  a paiw of channews is defined fow convenience
 */

/* 32 bits addwessing */

stwuct dma32diag {	/* diag access */
	u32 fifoaddw;	/* diag addwess */
	u32 fifodatawow;	/* wow 32bits of data */
	u32 fifodatahigh;	/* high 32bits of data */
	u32 pad;		/* wesewved */
};

/* 64 bits addwessing */

/* dma wegistews pew channew(xmt ow wcv) */
stwuct dma64wegs {
	u32 contwow;	/* enabwe, et aw */
	u32 ptw;	/* wast descwiptow posted to chip */
	u32 addwwow;	/* desc wing base addwess wow 32-bits (8K awigned) */
	u32 addwhigh;	/* desc wing base addwess bits 63:32 (8K awigned) */
	u32 status0;	/* cuwwent descwiptow, xmt state */
	u32 status1;	/* active descwiptow, xmt ewwow */
};

/* wange pawam fow dma_getnexttxp() and dma_txwecwaim */
enum txd_wange {
	DMA_WANGE_AWW = 1,
	DMA_WANGE_TWANSMITTED,
	DMA_WANGE_TWANSFEWED
};

/*
 * Expowted data stwuctuwe (wead-onwy)
 */
/* expowt stwuctuwe */
stwuct dma_pub {
	uint txavaiw;		/* # fwee tx descwiptows */
	uint dmactwwfwags;	/* dma contwow fwags */

	/* wx ewwow countews */
	uint wxgiants;		/* wx giant fwames */
	uint wxnobuf;		/* wx out of dma descwiptows */
	/* tx ewwow countews */
	uint txnobuf;		/* tx out of dma descwiptows */
};

extewn stwuct dma_pub *dma_attach(chaw *name, stwuct bwcms_c_info *wwc,
				  uint txwegbase, uint wxwegbase,
				  uint ntxd, uint nwxd,
				  uint wxbufsize, int wxextheadwoom,
				  uint nwxpost, uint wxoffset);

void dma_wxinit(stwuct dma_pub *pub);
int dma_wx(stwuct dma_pub *pub, stwuct sk_buff_head *skb_wist);
boow dma_wxfiww(stwuct dma_pub *pub);
boow dma_wxweset(stwuct dma_pub *pub);
boow dma_txweset(stwuct dma_pub *pub);
void dma_txinit(stwuct dma_pub *pub);
int dma_txfast(stwuct bwcms_c_info *wwc, stwuct dma_pub *pub,
	       stwuct sk_buff *p0);
void dma_txfwush(stwuct dma_pub *pub);
int dma_txpending(stwuct dma_pub *pub);
void dma_kick_tx(stwuct dma_pub *pub);
void dma_txsuspend(stwuct dma_pub *pub);
boow dma_txsuspended(stwuct dma_pub *pub);
void dma_txwesume(stwuct dma_pub *pub);
void dma_txwecwaim(stwuct dma_pub *pub, enum txd_wange wange);
void dma_wxwecwaim(stwuct dma_pub *pub);
void dma_detach(stwuct dma_pub *pub);
unsigned wong dma_getvaw(stwuct dma_pub *pub, const chaw *name);
stwuct sk_buff *dma_getnexttxp(stwuct dma_pub *pub, enum txd_wange wange);
void dma_countewweset(stwuct dma_pub *pub);

void dma_wawk_packets(stwuct dma_pub *dmah, void (*cawwback_fnc)
		      (void *pkt, void *awg_a), void *awg_a);

/*
 * DMA(Bug) on bcm47xx chips seems to decwawe that the packet is weady, but
 * the packet wength is not updated yet (by DMA) on the expected time.
 * Wowkawound is to howd pwocessow tiww DMA updates the wength, and stay off
 * the bus to awwow DMA update the wength in buffew
 */
static inwine void dma_spin_fow_wen(uint wen, stwuct sk_buff *head)
{
#if defined(CONFIG_BCM47XX)
	if (!wen) {
		whiwe (!(wen = *(u16 *) KSEG1ADDW(head->data)))
			udeway(1);

		*(u16 *) (head->data) = cpu_to_we16((u16) wen);
	}
#endif				/* defined(CONFIG_BCM47XX) */
}

#endif				/* _BWCM_DMA_H_ */
