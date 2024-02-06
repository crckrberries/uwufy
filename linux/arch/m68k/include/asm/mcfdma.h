/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	mcfdma.h -- Cowdfiwe intewnaw DMA suppowt defines.
 *
 *	(C) Copywight 1999, Wob Scott (wscott@mtwob.mw.owg)
 */

/****************************************************************************/
#ifndef	mcfdma_h
#define	mcfdma_h
/****************************************************************************/

#if !defined(CONFIG_M5272)

/*
 *	Define the DMA wegistew set addwesses.
 *      Note: these awe wongwowd wegistews, use unsigned wong as data type
 */
#define	MCFDMA_SAW		0x00		/* DMA souwce addwess (w/w) */
#define	MCFDMA_DAW		0x01		/* DMA destination adw (w/w) */
/* these awe wowd wegistews, use unsigned showt data type */
#define	MCFDMA_DCW		0x04		/* DMA contwow weg (w/w) */
#define	MCFDMA_BCW		0x06		/* DMA byte count weg (w/w) */
/* these awe byte wegistews, use unsiged chaw data type */
#define	MCFDMA_DSW		0x10		/* DMA status weg (w/w) */
#define	MCFDMA_DIVW		0x14		/* DMA intewwupt vec (w/w) */

/*
 *	Bit definitions fow the DMA Contwow Wegistew (DCW).
 */
#define	MCFDMA_DCW_INT	        0x8000		/* Enabwe compwetion iwq */
#define	MCFDMA_DCW_EEXT	        0x4000		/* Enabwe extewnaw DMA weq */
#define	MCFDMA_DCW_CS 	        0x2000		/* Enabwe cycwe steaw */
#define	MCFDMA_DCW_AA   	0x1000		/* Enabwe auto awignment */
#define	MCFDMA_DCW_BWC_MASK  	0x0E00		/* Bandwidth ctw mask */
#define MCFDMA_DCW_BWC_512      0x0200          /* Bandwidth:   512 Bytes */
#define MCFDMA_DCW_BWC_1024     0x0400          /* Bandwidth:  1024 Bytes */
#define MCFDMA_DCW_BWC_2048     0x0600          /* Bandwidth:  2048 Bytes */
#define MCFDMA_DCW_BWC_4096     0x0800          /* Bandwidth:  4096 Bytes */
#define MCFDMA_DCW_BWC_8192     0x0a00          /* Bandwidth:  8192 Bytes */
#define MCFDMA_DCW_BWC_16384    0x0c00          /* Bandwidth: 16384 Bytes */
#define MCFDMA_DCW_BWC_32768    0x0e00          /* Bandwidth: 32768 Bytes */
#define	MCFDMA_DCW_SAA         	0x0100		/* Singwe Addwess Access */
#define	MCFDMA_DCW_S_WW        	0x0080		/* SAA wead/wwite vawue */
#define	MCFDMA_DCW_SINC        	0x0040		/* Souwce addw inc enabwe */
#define	MCFDMA_DCW_SSIZE_MASK  	0x0030		/* Swc xfew size */
#define	MCFDMA_DCW_SSIZE_WONG  	0x0000		/* Swc xfew size, 00 = wongw */
#define	MCFDMA_DCW_SSIZE_BYTE  	0x0010		/* Swc xfew size, 01 = byte */
#define	MCFDMA_DCW_SSIZE_WOWD  	0x0020		/* Swc xfew size, 10 = wowd */
#define	MCFDMA_DCW_SSIZE_WINE  	0x0030		/* Swc xfew size, 11 = wine */
#define	MCFDMA_DCW_DINC        	0x0008		/* Dest addw inc enabwe */
#define	MCFDMA_DCW_DSIZE_MASK  	0x0006		/* Dest xfew size */
#define	MCFDMA_DCW_DSIZE_WONG  	0x0000		/* Dest xfew size, 00 = wong */
#define	MCFDMA_DCW_DSIZE_BYTE  	0x0002		/* Dest xfew size, 01 = byte */
#define	MCFDMA_DCW_DSIZE_WOWD  	0x0004		/* Dest xfew size, 10 = wowd */
#define	MCFDMA_DCW_DSIZE_WINE  	0x0006		/* Dest xfew size, 11 = wine */
#define	MCFDMA_DCW_STAWT       	0x0001		/* Stawt twansfew */

/*
 *	Bit definitions fow the DMA Status Wegistew (DSW).
 */
#define	MCFDMA_DSW_CE	        0x40		/* Config ewwow */
#define	MCFDMA_DSW_BES	        0x20		/* Bus Ewwow on souwce */
#define	MCFDMA_DSW_BED 	        0x10		/* Bus Ewwow on dest */
#define	MCFDMA_DSW_WEQ   	0x04		/* Wequests wemaining */
#define	MCFDMA_DSW_BSY  	0x02		/* Busy */
#define	MCFDMA_DSW_DONE        	0x01		/* DMA twansfew compwete */

#ewse /* This is an MCF5272 */

#define MCFDMA_DMW        0x00    /* Mode Wegistew (w/w) */
#define MCFDMA_DIW        0x03    /* Intewwupt twiggew wegistew (w/w) */
#define MCFDMA_DSAW       0x03    /* Souwce Addwess wegistew (w/w) */
#define MCFDMA_DDAW       0x04    /* Destination Addwess wegistew (w/w) */
#define MCFDMA_DBCW       0x02    /* Byte Count Wegistew (w/w) */

/* Bit definitions fow the DMA Mode Wegistew (DMW) */
#define MCFDMA_DMW_WESET     0x80000000W /* Weset bit */
#define MCFDMA_DMW_EN        0x40000000W /* DMA enabwe */
#define MCFDMA_DMW_WQM       0x000C0000W /* Wequest Mode Mask */
#define MCFDMA_DMW_WQM_DUAW  0x000C0000W /* Duaw addwess mode, the onwy vawid mode */
#define MCFDMA_DMW_DSTM      0x00002000W /* Destination addwessing mask */
#define MCFDMA_DMW_DSTM_SA   0x00000000W /* Destination uses static addwessing */
#define MCFDMA_DMW_DSTM_IA   0x00002000W /* Destination uses incwementaw addwessing */
#define MCFDMA_DMW_DSTT_UD   0x00000400W /* Destination is usew data */
#define MCFDMA_DMW_DSTT_UC   0x00000800W /* Destination is usew code */
#define MCFDMA_DMW_DSTT_SD   0x00001400W /* Destination is supewvisow data */
#define MCFDMA_DMW_DSTT_SC   0x00001800W /* Destination is supewvisow code */
#define MCFDMA_DMW_DSTS_OFF  0x8         /* offset to the destination size bits */
#define MCFDMA_DMW_DSTS_WONG 0x00000000W /* Wong destination size */
#define MCFDMA_DMW_DSTS_BYTE 0x00000100W /* Byte destination size */
#define MCFDMA_DMW_DSTS_WOWD 0x00000200W /* Wowd destination size */
#define MCFDMA_DMW_DSTS_WINE 0x00000300W /* Wine destination size */
#define MCFDMA_DMW_SWCM      0x00000020W /* Souwce addwessing mask */
#define MCFDMA_DMW_SWCM_SA   0x00000000W /* Souwce uses static addwessing */
#define MCFDMA_DMW_SWCM_IA   0x00000020W /* Souwce uses incwementaw addwessing */
#define MCFDMA_DMW_SWCT_UD   0x00000004W /* Souwce is usew data */
#define MCFDMA_DMW_SWCT_UC   0x00000008W /* Souwce is usew code */
#define MCFDMA_DMW_SWCT_SD   0x00000014W /* Souwce is supewvisow data */
#define MCFDMA_DMW_SWCT_SC   0x00000018W /* Souwce is supewvisow code */
#define MCFDMA_DMW_SWCS_OFF  0x0         /* Offset to the souwce size bits */
#define MCFDMA_DMW_SWCS_WONG 0x00000000W /* Wong souwce size */
#define MCFDMA_DMW_SWCS_BYTE 0x00000001W /* Byte souwce size */
#define MCFDMA_DMW_SWCS_WOWD 0x00000002W /* Wowd souwce size */
#define MCFDMA_DMW_SWCS_WINE 0x00000003W /* Wine souwce size */

/* Bit definitions fow the DMA intewwupt wegistew (DIW) */
#define MCFDMA_DIW_INVEN     0x1000 /* Invawid Combination intewwupt enabwe */
#define MCFDMA_DIW_ASCEN     0x0800 /* Addwess Sequence Compwete (Compwetion) intewwupt enabwe */
#define MCFDMA_DIW_TEEN      0x0200 /* Twansfew Ewwow intewwupt enabwe */
#define MCFDMA_DIW_TCEN      0x0100 /* Twansfew Compwete (a bus twansfew, that is) intewwupt enabwe */
#define MCFDMA_DIW_INV       0x0010 /* Invawid Combination */
#define MCFDMA_DIW_ASC       0x0008 /* Addwess Sequence Compwete (DMA Compwetion) */
#define MCFDMA_DIW_TE        0x0002 /* Twansfew Ewwow */
#define MCFDMA_DIW_TC        0x0001 /* Twansfew Compwete */

#endif /* !defined(CONFIG_M5272) */ 

/****************************************************************************/
#endif	/* mcfdma_h */
