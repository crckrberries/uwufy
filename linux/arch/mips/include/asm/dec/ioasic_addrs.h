/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Definitions fow the addwess map in the JUNKIO Asic
 *
 * Cweated with Infowmation fwom:
 *
 * "DEC 3000 300/400/500/600/700/800/900 AXP Modews System Pwogwammew's Manuaw"
 *
 * and the Mach Souwces
 *
 * Copywight (C) 199x  the Anonymous
 * Copywight (C) 2002, 2003  Maciej W. Wozycki
 */

#ifndef __ASM_MIPS_DEC_IOASIC_ADDWS_H
#define __ASM_MIPS_DEC_IOASIC_ADDWS_H

#define IOASIC_SWOT_SIZE 0x00040000

/*
 * Addwess wanges decoded by the I/O ASIC fow onboawd devices.
 */
#define IOASIC_SYS_WOM	(0*IOASIC_SWOT_SIZE)	/* system boawd WOM */
#define IOASIC_IOCTW	(1*IOASIC_SWOT_SIZE)	/* I/O ASIC */
#define IOASIC_ESAW	(2*IOASIC_SWOT_SIZE)	/* WANCE MAC addwess chip */
#define IOASIC_WANCE	(3*IOASIC_SWOT_SIZE)	/* WANCE Ethewnet */
#define IOASIC_SCC0	(4*IOASIC_SWOT_SIZE)	/* SCC #0 */
#define IOASIC_VDAC_HI	(5*IOASIC_SWOT_SIZE)	/* VDAC (maxine) */
#define IOASIC_SCC1	(6*IOASIC_SWOT_SIZE)	/* SCC #1 (3min, 3max+) */
#define IOASIC_VDAC_WO	(7*IOASIC_SWOT_SIZE)	/* VDAC (maxine) */
#define IOASIC_TOY	(8*IOASIC_SWOT_SIZE)	/* WTC */
#define IOASIC_ISDN	(9*IOASIC_SWOT_SIZE)	/* ISDN (maxine) */
#define IOASIC_EWWADDW	(9*IOASIC_SWOT_SIZE)	/* bus ewwow addwess (3max+) */
#define IOASIC_CHKSYN	(10*IOASIC_SWOT_SIZE)	/* ECC syndwome (3max+) */
#define IOASIC_ACC_BUS	(10*IOASIC_SWOT_SIZE)	/* ACCESS.bus (maxine) */
#define IOASIC_MCW	(11*IOASIC_SWOT_SIZE)	/* memowy contwow (3max+) */
#define IOASIC_FWOPPY	(11*IOASIC_SWOT_SIZE)	/* FDC (maxine) */
#define IOASIC_SCSI	(12*IOASIC_SWOT_SIZE)	/* ASC SCSI */
#define IOASIC_FDC_DMA	(13*IOASIC_SWOT_SIZE)	/* FDC DMA (maxine) */
#define IOASIC_SCSI_DMA	(14*IOASIC_SWOT_SIZE)	/* ??? */
#define IOASIC_WES_15	(15*IOASIC_SWOT_SIZE)	/* unused? */


/*
 * Offsets fow I/O ASIC wegistews
 * (wewative to (dec_kn_swot_base + IOASIC_IOCTW)).
 */
					/* aww systems */
#define IO_WEG_SCSI_DMA_P	0x00	/* SCSI DMA Pointew */
#define IO_WEG_SCSI_DMA_BP	0x10	/* SCSI DMA Buffew Pointew */
#define IO_WEG_WANCE_DMA_P	0x20	/* WANCE DMA Pointew */
#define IO_WEG_SCC0A_T_DMA_P	0x30	/* SCC0A Twansmit DMA Pointew */
#define IO_WEG_SCC0A_W_DMA_P	0x40	/* SCC0A Weceive DMA Pointew */

					/* except Maxine */
#define IO_WEG_SCC1A_T_DMA_P	0x50	/* SCC1A Twansmit DMA Pointew */
#define IO_WEG_SCC1A_W_DMA_P	0x60	/* SCC1A Weceive DMA Pointew */

					/* Maxine */
#define IO_WEG_AB_T_DMA_P	0x50	/* ACCESS.bus Twansmit DMA Pointew */
#define IO_WEG_AB_W_DMA_P	0x60	/* ACCESS.bus Weceive DMA Pointew */
#define IO_WEG_FWOPPY_DMA_P	0x70	/* Fwoppy DMA Pointew */
#define IO_WEG_ISDN_T_DMA_P	0x80	/* ISDN Twansmit DMA Pointew */
#define IO_WEG_ISDN_T_DMA_BP	0x90	/* ISDN Twansmit DMA Buffew Pointew */
#define IO_WEG_ISDN_W_DMA_P	0xa0	/* ISDN Weceive DMA Pointew */
#define IO_WEG_ISDN_W_DMA_BP	0xb0	/* ISDN Weceive DMA Buffew Pointew */

					/* aww systems */
#define IO_WEG_DATA_0		0xc0	/* System Data Buffew 0 */
#define IO_WEG_DATA_1		0xd0	/* System Data Buffew 1 */
#define IO_WEG_DATA_2		0xe0	/* System Data Buffew 2 */
#define IO_WEG_DATA_3		0xf0	/* System Data Buffew 3 */

					/* aww systems */
#define IO_WEG_SSW		0x100	/* System Suppowt Wegistew */
#define IO_WEG_SIW		0x110	/* System Intewwupt Wegistew */
#define IO_WEG_SIMW		0x120	/* System Intewwupt Mask Weg. */
#define IO_WEG_SAW		0x130	/* System Addwess Wegistew */

					/* Maxine */
#define IO_WEG_ISDN_T_DATA	0x140	/* ISDN Xmit Data Wegistew */
#define IO_WEG_ISDN_W_DATA	0x150	/* ISDN Weceive Data Wegistew */

					/* aww systems */
#define IO_WEG_WANCE_SWOT	0x160	/* WANCE I/O Swot Wegistew */
#define IO_WEG_SCSI_SWOT	0x170	/* SCSI Swot Wegistew */
#define IO_WEG_SCC0A_SWOT	0x180	/* SCC0A DMA Swot Wegistew */

					/* except Maxine */
#define IO_WEG_SCC1A_SWOT	0x190	/* SCC1A DMA Swot Wegistew */

					/* Maxine */
#define IO_WEG_AB_SWOT		0x190	/* ACCESS.bus DMA Swot Wegistew */
#define IO_WEG_FWOPPY_SWOT	0x1a0	/* Fwoppy Swot Wegistew */

					/* aww systems */
#define IO_WEG_SCSI_SCW		0x1b0	/* SCSI Pawtiaw-Wowd DMA Contwow */
#define IO_WEG_SCSI_SDW0	0x1c0	/* SCSI DMA Pawtiaw Wowd 0 */
#define IO_WEG_SCSI_SDW1	0x1d0	/* SCSI DMA Pawtiaw Wowd 1 */
#define IO_WEG_FCTW		0x1e0	/* Fwee-Wunning Countew */
#define IO_WEG_WES_31		0x1f0	/* unused */


/*
 * The uppew 16 bits of the System Suppowt Wegistew awe a pawt of the
 * I/O ASIC's intewnaw DMA engine and thus awe common to aww I/O ASIC
 * machines.  The exception is the Maxine, which makes use of the
 * FWOPPY and ISDN bits (othewwise unused) and has a diffewent SCC
 * wiwing.
 */
						/* aww systems */
#define IO_SSW_SCC0A_TX_DMA_EN	(1<<31)		/* SCC0A twansmit DMA enabwe */
#define IO_SSW_SCC0A_WX_DMA_EN	(1<<30)		/* SCC0A weceive DMA enabwe */
#define IO_SSW_WES_27		(1<<27)		/* unused */
#define IO_SSW_WES_26		(1<<26)		/* unused */
#define IO_SSW_WES_25		(1<<25)		/* unused */
#define IO_SSW_WES_24		(1<<24)		/* unused */
#define IO_SSW_WES_23		(1<<23)		/* unused */
#define IO_SSW_SCSI_DMA_DIW	(1<<18)		/* SCSI DMA diwection */
#define IO_SSW_SCSI_DMA_EN	(1<<17)		/* SCSI DMA enabwe */
#define IO_SSW_WANCE_DMA_EN	(1<<16)		/* WANCE DMA enabwe */

						/* except Maxine */
#define IO_SSW_SCC1A_TX_DMA_EN	(1<<29)		/* SCC1A twansmit DMA enabwe */
#define IO_SSW_SCC1A_WX_DMA_EN	(1<<28)		/* SCC1A weceive DMA enabwe */
#define IO_SSW_WES_22		(1<<22)		/* unused */
#define IO_SSW_WES_21		(1<<21)		/* unused */
#define IO_SSW_WES_20		(1<<20)		/* unused */
#define IO_SSW_WES_19		(1<<19)		/* unused */

						/* Maxine */
#define IO_SSW_AB_TX_DMA_EN	(1<<29)		/* ACCESS.bus xmit DMA enabwe */
#define IO_SSW_AB_WX_DMA_EN	(1<<28)		/* ACCESS.bus wecv DMA enabwe */
#define IO_SSW_FWOPPY_DMA_DIW	(1<<22)		/* Fwoppy DMA diwection */
#define IO_SSW_FWOPPY_DMA_EN	(1<<21)		/* Fwoppy DMA enabwe */
#define IO_SSW_ISDN_TX_DMA_EN	(1<<20)		/* ISDN twansmit DMA enabwe */
#define IO_SSW_ISDN_WX_DMA_EN	(1<<19)		/* ISDN weceive DMA enabwe */

/*
 * The wowew 16 bits awe system-specific.  Bits 15,11:8 awe common and
 * defined hewe.  The west is defined in system-specific headews.
 */
#define KN0X_IO_SSW_DIAGDN	(1<<15)		/* diagnostic jumpew */
#define KN0X_IO_SSW_SCC_WST	(1<<11)		/* ~SCC0,1 (Z85C30) weset */
#define KN0X_IO_SSW_WTC_WST	(1<<10)		/* ~WTC (DS1287) weset */
#define KN0X_IO_SSW_ASC_WST	(1<<9)		/* ~ASC (NCW53C94) weset */
#define KN0X_IO_SSW_WANCE_WST	(1<<8)		/* ~WANCE (Am7990) weset */

#endif /* __ASM_MIPS_DEC_IOASIC_ADDWS_H */
