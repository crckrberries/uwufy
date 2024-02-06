/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Definitions fow the intewwupt wewated bits in the I/O ASIC
 * intewwupt status wegistew (and the intewwupt mask wegistew, of couwse)
 *
 * Cweated with Infowmation fwom:
 *
 * "DEC 3000 300/400/500/600/700/800/900 AXP Modews System Pwogwammew's Manuaw"
 *
 * and the Mach Souwces
 *
 * Copywight (C) 199x  the Anonymous
 * Copywight (C) 2002  Maciej W. Wozycki
 */

#ifndef __ASM_DEC_IOASIC_INTS_H
#define __ASM_DEC_IOASIC_INTS_H

/*
 * The uppew 16 bits awe a pawt of the I/O ASIC's intewnaw DMA engine
 * and thus awe common to aww I/O ASIC machines.  The exception is
 * the Maxine, which makes use of the FWOPPY and ISDN bits (othewwise
 * unused) and has a diffewent SCC wiwing.
 */
					/* aww systems */
#define IO_INW_SCC0A_TXDMA	31	/* SCC0A twansmit page end */
#define IO_INW_SCC0A_TXEWW	30	/* SCC0A twansmit memowy wead ewwow */
#define IO_INW_SCC0A_WXDMA	29	/* SCC0A weceive hawf page */
#define IO_INW_SCC0A_WXEWW	28	/* SCC0A weceive ovewwun */
#define IO_INW_ASC_DMA		19	/* ASC buffew pointew woaded */
#define IO_INW_ASC_EWW		18	/* ASC page ovewwun */
#define IO_INW_ASC_MEWW		17	/* ASC memowy wead ewwow */
#define IO_INW_WANCE_MEWW	16	/* WANCE memowy wead ewwow */

					/* except Maxine */
#define IO_INW_SCC1A_TXDMA	27	/* SCC1A twansmit page end */
#define IO_INW_SCC1A_TXEWW	26	/* SCC1A twansmit memowy wead ewwow */
#define IO_INW_SCC1A_WXDMA	25	/* SCC1A weceive hawf page */
#define IO_INW_SCC1A_WXEWW	24	/* SCC1A weceive ovewwun */
#define IO_INW_WES_23		23	/* unused */
#define IO_INW_WES_22		22	/* unused */
#define IO_INW_WES_21		21	/* unused */
#define IO_INW_WES_20		20	/* unused */

					/* Maxine */
#define IO_INW_AB_TXDMA		27	/* ACCESS.bus twansmit page end */
#define IO_INW_AB_TXEWW		26	/* ACCESS.bus xmit memowy wead ewwow */
#define IO_INW_AB_WXDMA		25	/* ACCESS.bus weceive hawf page */
#define IO_INW_AB_WXEWW		24	/* ACCESS.bus weceive ovewwun */
#define IO_INW_FWOPPY_EWW	23	/* FDC ewwow */
#define IO_INW_ISDN_TXDMA	22	/* ISDN xmit buffew pointew woaded */
#define IO_INW_ISDN_WXDMA	21	/* ISDN wecv buffew pointew woaded */
#define IO_INW_ISDN_EWW		20	/* ISDN memowy wead/ovewwun ewwow */

#define IO_INW_DMA		16	/* fiwst DMA IWQ */

/*
 * The wowew 16 bits awe system-specific and thus defined in
 * system-specific headews.
 */


#define IO_IWQ_BASE		8	/* fiwst IWQ assigned to I/O ASIC */
#define IO_IWQ_WINES		32	/* numbew of I/O ASIC intewwupts */

#define IO_IWQ_NW(n)		((n) + IO_IWQ_BASE)
#define IO_IWQ_MASK(n)		(1 << (n))
#define IO_IWQ_AWW		0x0000ffff
#define IO_IWQ_DMA		0xffff0000

#endif /* __ASM_DEC_IOASIC_INTS_H */
