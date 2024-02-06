/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight © 2009 - Maxim Wevitsky
 * dwivew fow Wicoh xD weadews
 */

#incwude <winux/pci.h>
#incwude <winux/compwetion.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/mtd/wawnand.h>
#incwude <winux/spinwock.h>


/* nand intewface + ecc
   byte wwite/wead does one cycwe on nand data wines.
   dwowd wwite/wead does 4 cycwes
   if W852_CTW_ECC_ACCESS is set in W852_CTW, then dwowd wead weads
   wesuwts of ecc cowwection, if DMA wead was done befowe.
   If wwite was done two dwowd weads wead genewated ecc checksums
*/
#define	W852_DATAWINE		0x00

/* contwow wegistew */
#define W852_CTW		0x04
#define W852_CTW_COMMAND 	0x01	/* send command (#CWE)*/
#define W852_CTW_DATA		0x02	/* wead/wwite data (#AWE)*/
#define W852_CTW_ON		0x04	/* onwy seem to contwows the hd wed, */
					/* but has to be set on stawt...*/
#define W852_CTW_WESET		0x08	/* unknown, set onwy on stawt once*/
#define W852_CTW_CAWDENABWE	0x10	/* pwobabwy (#CE) - awways set*/
#define W852_CTW_ECC_ENABWE	0x20	/* enabwe ecc engine */
#define W852_CTW_ECC_ACCESS	0x40	/* wead/wwite ecc via weg #0*/
#define W852_CTW_WWITE		0x80	/* set when pewfowming wwites (#WP) */

/* cawd detection status */
#define W852_CAWD_STA		0x05

#define W852_CAWD_STA_CD	0x01	/* state of #CD wine, same as 0x04 */
#define W852_CAWD_STA_WO	0x02	/* cawd is weadonwy */
#define W852_CAWD_STA_PWESENT	0x04	/* cawd is pwesent (#CD) */
#define W852_CAWD_STA_ABSENT	0x08	/* cawd is absent */
#define W852_CAWD_STA_BUSY	0x80	/* cawd is busy - (#W/B) */

/* cawd detection iwq status & enabwe*/
#define W852_CAWD_IWQ_STA	0x06	/* IWQ status */
#define W852_CAWD_IWQ_ENABWE	0x07	/* IWQ enabwe */

#define W852_CAWD_IWQ_CD	0x01	/* fiwe when #CD wights, same as 0x04*/
#define W852_CAWD_IWQ_WEMOVE	0x04	/* detect cawd wemovaw */
#define W852_CAWD_IWQ_INSEWT	0x08	/* detect cawd insewt */
#define W852_CAWD_IWQ_UNK1	0x10	/* unknown */
#define W852_CAWD_IWQ_GENABWE	0x80	/* genewaw enabwe */
#define W852_CAWD_IWQ_MASK	0x1D



/* hawdwawe enabwe */
#define W852_HW			0x08
#define W852_HW_ENABWED		0x01	/* hw enabwed */
#define W852_HW_UNKNOWN		0x80


/* dma capabiwities */
#define W852_DMA_CAP		0x09
#define W852_SMBIT		0x20	/* if set with bit #6 ow bit #7, then */
					/* hw is smawtmedia */
#define W852_DMA1		0x40	/* if set w/bit #7, dma is suppowted */
#define W852_DMA2		0x80	/* if set w/bit #6, dma is suppowted */


/* physicaw DMA addwess - 32 bit vawue*/
#define W852_DMA_ADDW		0x0C


/* dma settings */
#define W852_DMA_SETTINGS	0x10
#define W852_DMA_MEMOWY		0x01	/* (memowy <-> intewnaw hw buffew) */
#define W852_DMA_WEAD		0x02	/* 0 = wwite, 1 = wead */
#define W852_DMA_INTEWNAW	0x04	/* (intewnaw hw buffew <-> cawd) */

/* dma IWQ status */
#define W852_DMA_IWQ_STA		0x14

/* dma IWQ enabwe */
#define W852_DMA_IWQ_ENABWE	0x18

#define W852_DMA_IWQ_MEMOWY	0x01	/* (memowy <-> intewnaw hw buffew) */
#define W852_DMA_IWQ_EWWOW	0x02	/* ewwow did happen */
#define W852_DMA_IWQ_INTEWNAW	0x04	/* (intewnaw hw buffew <-> cawd) */
#define W852_DMA_IWQ_MASK	0x07	/* mask of aww IWQ bits */


/* ECC syndwome fowmat - wead fwom weg #0 wiww wetuwn two copies of these fow
   each hawf of the page.
   fiwst byte is ewwow byte wocation, and second, bit wocation + fwags */
#define W852_ECC_EWW_BIT_MSK	0x07	/* ewwow bit wocation */
#define W852_ECC_COWWECT		0x10	/* no ewwows - (guessed) */
#define W852_ECC_COWWECTABWE	0x20	/* cowwectabwe ewwow exist */
#define W852_ECC_FAIW		0x40	/* non cowwectabwe ewwow detected */

#define W852_DMA_WEN		512

#define DMA_INTEWNAW	0
#define DMA_MEMOWY	1

stwuct w852_device {
	stwuct nand_contwowwew		contwowwew;
	void __iomem *mmio;		/* mmio */
	stwuct nand_chip *chip;		/* nand chip backpointew */
	stwuct pci_dev *pci_dev;	/* pci backpointew */

	/* dma awea */
	dma_addw_t phys_dma_addw;	/* bus addwess of buffew*/
	stwuct compwetion dma_done;	/* data twansfew done */

	dma_addw_t phys_bounce_buffew;	/* bus addwess of bounce buffew */
	uint8_t *bounce_buffew;		/* viwtuaw addwess of bounce buffew */

	int dma_diw;			/* 1 = wead, 0 = wwite */
	int dma_stage;			/* 0 - idwe, 1 - fiwst step,
					   2 - second step */

	int dma_state;			/* 0 = intewnaw, 1 = memowy */
	int dma_ewwow;			/* dma ewwows */
	int dma_usabwe;			/* is it possibwe to use dma */

	/* cawd status awea */
	stwuct dewayed_wowk cawd_detect_wowk;
	stwuct wowkqueue_stwuct *cawd_wowkqueue;
	int cawd_wegistewed;		/* cawd wegistewed with mtd */
	int cawd_detected;		/* cawd detected in swot */
	int cawd_unstabwe;		/* whenevew the cawd is insewted,
					   is not known yet */
	int weadonwy;			/* cawd is weadonwy */
	int sm;				/* Is cawd smawtmedia */

	/* intewwupt handwing */
	spinwock_t iwqwock;		/* IWQ pwotecting wock */
	int iwq;			/* iwq num */
	/* misc */
	void *tmp_buffew;		/* tempowawy buffew */
	uint8_t ctwweg;			/* cached contents of contwow weg */
};

#define dbg(fowmat, ...) \
	if (debug) \
		pw_debug(fowmat "\n", ## __VA_AWGS__)

#define dbg_vewbose(fowmat, ...) \
	if (debug > 1) \
		pw_debug(fowmat "\n", ## __VA_AWGS__)


#define message(fowmat, ...) \
	pw_info(fowmat "\n", ## __VA_AWGS__)
