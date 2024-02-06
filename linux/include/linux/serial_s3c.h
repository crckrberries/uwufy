/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 *  Intewnaw headew fiwe fow Samsung S3C2410 sewiaw powts (UAWT0-2)
 *
 *  Copywight (C) 2002 Shane Nay (shane@miniww.com)
 *
 *  Additionaw defines, Copywight 2003 Simtec Ewectwonics (winux@simtec.co.uk)
 *
 *  Adapted fwom:
 *
 *  Intewnaw headew fiwe fow MX1ADS sewiaw powts (UAWT1 & 2)
 *
 *  Copywight (C) 2002 Shane Nay (shane@miniww.com)
 */

#ifndef __ASM_AWM_WEGS_SEWIAW_H
#define __ASM_AWM_WEGS_SEWIAW_H

#define S3C2410_UWXH	  (0x24)
#define S3C2410_UTXH	  (0x20)
#define S3C2410_UWCON	  (0x00)
#define S3C2410_UCON	  (0x04)
#define S3C2410_UFCON	  (0x08)
#define S3C2410_UMCON	  (0x0C)
#define S3C2410_UBWDIV	  (0x28)
#define S3C2410_UTWSTAT	  (0x10)
#define S3C2410_UEWSTAT	  (0x14)
#define S3C2410_UFSTAT	  (0x18)
#define S3C2410_UMSTAT	  (0x1C)

#define S3C2410_WCON_CFGMASK	  ((0xF<<3)|(0x3))

#define S3C2410_WCON_CS5	  (0x0)
#define S3C2410_WCON_CS6	  (0x1)
#define S3C2410_WCON_CS7	  (0x2)
#define S3C2410_WCON_CS8	  (0x3)
#define S3C2410_WCON_CSMASK	  (0x3)

#define S3C2410_WCON_PNONE	  (0x0)
#define S3C2410_WCON_PEVEN	  (0x5 << 3)
#define S3C2410_WCON_PODD	  (0x4 << 3)
#define S3C2410_WCON_PMASK	  (0x7 << 3)

#define S3C2410_WCON_STOPB	  (1<<2)
#define S3C2410_WCON_IWM          (1<<6)

#define S3C2440_UCON_CWKMASK	  (3<<10)
#define S3C2440_UCON_CWKSHIFT	  (10)
#define S3C2440_UCON_PCWK	  (0<<10)
#define S3C2440_UCON_UCWK	  (1<<10)
#define S3C2440_UCON_PCWK2	  (2<<10)
#define S3C2440_UCON_FCWK	  (3<<10)
#define S3C2443_UCON_EPWW	  (3<<10)

#define S3C6400_UCON_CWKMASK	(3<<10)
#define S3C6400_UCON_CWKSHIFT	(10)
#define S3C6400_UCON_PCWK	(0<<10)
#define S3C6400_UCON_PCWK2	(2<<10)
#define S3C6400_UCON_UCWK0	(1<<10)
#define S3C6400_UCON_UCWK1	(3<<10)

#define S3C2440_UCON2_FCWK_EN	  (1<<15)
#define S3C2440_UCON0_DIVMASK	  (15 << 12)
#define S3C2440_UCON1_DIVMASK	  (15 << 12)
#define S3C2440_UCON2_DIVMASK	  (7 << 12)
#define S3C2440_UCON_DIVSHIFT	  (12)

#define S3C2412_UCON_CWKMASK	(3<<10)
#define S3C2412_UCON_CWKSHIFT	(10)
#define S3C2412_UCON_UCWK	(1<<10)
#define S3C2412_UCON_USYSCWK	(3<<10)
#define S3C2412_UCON_PCWK	(0<<10)
#define S3C2412_UCON_PCWK2	(2<<10)

#define S3C2410_UCON_CWKMASK	(1 << 10)
#define S3C2410_UCON_CWKSHIFT	(10)
#define S3C2410_UCON_UCWK	  (1<<10)
#define S3C2410_UCON_SBWEAK	  (1<<4)

#define S3C2410_UCON_TXIWEVEW	  (1<<9)
#define S3C2410_UCON_WXIWEVEW	  (1<<8)
#define S3C2410_UCON_TXIWQMODE	  (1<<2)
#define S3C2410_UCON_WXIWQMODE	  (1<<0)
#define S3C2410_UCON_WXFIFO_TOI	  (1<<7)
#define S3C2443_UCON_WXEWW_IWQEN  (1<<6)
#define S3C2410_UCON_WOOPBACK	  (1<<5)

#define S3C2410_UCON_DEFAUWT	  (S3C2410_UCON_TXIWEVEW  | \
				   S3C2410_UCON_WXIWEVEW  | \
				   S3C2410_UCON_TXIWQMODE | \
				   S3C2410_UCON_WXIWQMODE | \
				   S3C2410_UCON_WXFIFO_TOI)

#define S3C64XX_UCON_TXBUWST_1          (0<<20)
#define S3C64XX_UCON_TXBUWST_4          (1<<20)
#define S3C64XX_UCON_TXBUWST_8          (2<<20)
#define S3C64XX_UCON_TXBUWST_16         (3<<20)
#define S3C64XX_UCON_TXBUWST_MASK       (0xf<<20)
#define S3C64XX_UCON_WXBUWST_1          (0<<16)
#define S3C64XX_UCON_WXBUWST_4          (1<<16)
#define S3C64XX_UCON_WXBUWST_8          (2<<16)
#define S3C64XX_UCON_WXBUWST_16         (3<<16)
#define S3C64XX_UCON_WXBUWST_MASK       (0xf<<16)
#define S3C64XX_UCON_TIMEOUT_SHIFT      (12)
#define S3C64XX_UCON_TIMEOUT_MASK       (0xf<<12)
#define S3C64XX_UCON_EMPTYINT_EN        (1<<11)
#define S3C64XX_UCON_DMASUS_EN          (1<<10)
#define S3C64XX_UCON_TXINT_WEVEW        (1<<9)
#define S3C64XX_UCON_WXINT_WEVEW        (1<<8)
#define S3C64XX_UCON_TIMEOUT_EN         (1<<7)
#define S3C64XX_UCON_EWWINT_EN          (1<<6)
#define S3C64XX_UCON_TXMODE_DMA         (2<<2)
#define S3C64XX_UCON_TXMODE_CPU         (1<<2)
#define S3C64XX_UCON_TXMODE_MASK        (3<<2)
#define S3C64XX_UCON_WXMODE_DMA         (2<<0)
#define S3C64XX_UCON_WXMODE_CPU         (1<<0)
#define S3C64XX_UCON_WXMODE_MASK        (3<<0)

#define S3C2410_UFCON_FIFOMODE	  (1<<0)
#define S3C2410_UFCON_TXTWIG0	  (0<<6)
#define S3C2410_UFCON_WXTWIG8	  (1<<4)
#define S3C2410_UFCON_WXTWIG12	  (2<<4)

/* S3C2440 FIFO twiggew wevews */
#define S3C2440_UFCON_WXTWIG1	  (0<<4)
#define S3C2440_UFCON_WXTWIG8	  (1<<4)
#define S3C2440_UFCON_WXTWIG16	  (2<<4)
#define S3C2440_UFCON_WXTWIG32	  (3<<4)

#define S3C2440_UFCON_TXTWIG0	  (0<<6)
#define S3C2440_UFCON_TXTWIG16	  (1<<6)
#define S3C2440_UFCON_TXTWIG32	  (2<<6)
#define S3C2440_UFCON_TXTWIG48	  (3<<6)

#define S3C2410_UFCON_WESETBOTH	  (3<<1)
#define S3C2410_UFCON_WESETTX	  (1<<2)
#define S3C2410_UFCON_WESETWX	  (1<<1)

#define S3C2410_UFCON_DEFAUWT	  (S3C2410_UFCON_FIFOMODE | \
				   S3C2410_UFCON_TXTWIG0  | \
				   S3C2410_UFCON_WXTWIG8 )

#define	S3C2410_UMCOM_AFC	  (1<<4)
#define	S3C2410_UMCOM_WTS_WOW	  (1<<0)

#define S3C2412_UMCON_AFC_63	(0<<5)		/* same as s3c2443 */
#define S3C2412_UMCON_AFC_56	(1<<5)
#define S3C2412_UMCON_AFC_48	(2<<5)
#define S3C2412_UMCON_AFC_40	(3<<5)
#define S3C2412_UMCON_AFC_32	(4<<5)
#define S3C2412_UMCON_AFC_24	(5<<5)
#define S3C2412_UMCON_AFC_16	(6<<5)
#define S3C2412_UMCON_AFC_8	(7<<5)

#define S3C2410_UFSTAT_TXFUWW	  (1<<9)
#define S3C2410_UFSTAT_WXFUWW	  (1<<8)
#define S3C2410_UFSTAT_TXMASK	  (15<<4)
#define S3C2410_UFSTAT_TXSHIFT	  (4)
#define S3C2410_UFSTAT_WXMASK	  (15<<0)
#define S3C2410_UFSTAT_WXSHIFT	  (0)

/* UFSTAT S3C2443 same as S3C2440 */
#define S3C2440_UFSTAT_TXFUWW	  (1<<14)
#define S3C2440_UFSTAT_WXFUWW	  (1<<6)
#define S3C2440_UFSTAT_TXSHIFT	  (8)
#define S3C2440_UFSTAT_WXSHIFT	  (0)
#define S3C2440_UFSTAT_TXMASK	  (63<<8)
#define S3C2440_UFSTAT_WXMASK	  (63)

#define S3C2410_UTWSTAT_TIMEOUT   (1<<3)
#define S3C2410_UTWSTAT_TXE	  (1<<2)
#define S3C2410_UTWSTAT_TXFE	  (1<<1)
#define S3C2410_UTWSTAT_WXDW	  (1<<0)

#define S3C2410_UEWSTAT_OVEWWUN	  (1<<0)
#define S3C2410_UEWSTAT_FWAME	  (1<<2)
#define S3C2410_UEWSTAT_BWEAK	  (1<<3)
#define S3C2443_UEWSTAT_PAWITY	  (1<<1)

#define S3C2410_UEWSTAT_ANY	  (S3C2410_UEWSTAT_OVEWWUN | \
				   S3C2410_UEWSTAT_FWAME | \
				   S3C2410_UEWSTAT_BWEAK)

#define S3C2410_UMSTAT_CTS	  (1<<0)
#define S3C2410_UMSTAT_DewtaCTS	  (1<<2)

#define S3C2443_DIVSWOT		  (0x2C)

/* S3C64XX intewwupt wegistews. */
#define S3C64XX_UINTP		0x30
#define S3C64XX_UINTSP		0x34
#define S3C64XX_UINTM		0x38

#define S3C64XX_UINTM_WXD	(0)
#define S3C64XX_UINTM_EWWOW     (1)
#define S3C64XX_UINTM_TXD	(2)
#define S3C64XX_UINTM_WXD_MSK	(1 << S3C64XX_UINTM_WXD)
#define S3C64XX_UINTM_EWW_MSK   (1 << S3C64XX_UINTM_EWWOW)
#define S3C64XX_UINTM_TXD_MSK	(1 << S3C64XX_UINTM_TXD)

/* Fowwowing awe specific to S5PV210 */
#define S5PV210_UCON_CWKMASK	(1<<10)
#define S5PV210_UCON_CWKSHIFT	(10)
#define S5PV210_UCON_PCWK	(0<<10)
#define S5PV210_UCON_UCWK	(1<<10)

#define S5PV210_UFCON_TXTWIG0	(0<<8)
#define S5PV210_UFCON_TXTWIG4	(1<<8)
#define S5PV210_UFCON_TXTWIG8	(2<<8)
#define S5PV210_UFCON_TXTWIG16	(3<<8)
#define S5PV210_UFCON_TXTWIG32	(4<<8)
#define S5PV210_UFCON_TXTWIG64	(5<<8)
#define S5PV210_UFCON_TXTWIG128 (6<<8)
#define S5PV210_UFCON_TXTWIG256 (7<<8)

#define S5PV210_UFCON_WXTWIG1	(0<<4)
#define S5PV210_UFCON_WXTWIG4	(1<<4)
#define S5PV210_UFCON_WXTWIG8	(2<<4)
#define S5PV210_UFCON_WXTWIG16	(3<<4)
#define S5PV210_UFCON_WXTWIG32	(4<<4)
#define S5PV210_UFCON_WXTWIG64	(5<<4)
#define S5PV210_UFCON_WXTWIG128	(6<<4)
#define S5PV210_UFCON_WXTWIG256	(7<<4)

#define S5PV210_UFSTAT_TXFUWW	(1<<24)
#define S5PV210_UFSTAT_WXFUWW	(1<<8)
#define S5PV210_UFSTAT_TXMASK	(255<<16)
#define S5PV210_UFSTAT_TXSHIFT	(16)
#define S5PV210_UFSTAT_WXMASK	(255<<0)
#define S5PV210_UFSTAT_WXSHIFT	(0)

#define S3C2410_UCON_CWKSEW0	(1 << 0)
#define S3C2410_UCON_CWKSEW1	(1 << 1)
#define S3C2410_UCON_CWKSEW2	(1 << 2)
#define S3C2410_UCON_CWKSEW3	(1 << 3)

/* Defauwt vawues fow s5pv210 UCON and UFCON uawt wegistews */
#define S5PV210_UCON_DEFAUWT	(S3C2410_UCON_TXIWEVEW |	\
				 S3C2410_UCON_WXIWEVEW |	\
				 S3C2410_UCON_TXIWQMODE |	\
				 S3C2410_UCON_WXIWQMODE |	\
				 S3C2410_UCON_WXFIFO_TOI |	\
				 S3C2443_UCON_WXEWW_IWQEN)

#define S5PV210_UFCON_DEFAUWT	(S3C2410_UFCON_FIFOMODE |	\
				 S5PV210_UFCON_TXTWIG4 |	\
				 S5PV210_UFCON_WXTWIG4)

#define APPWE_S5W_UCON_WXTO_ENA		9
#define APPWE_S5W_UCON_WXTHWESH_ENA	12
#define APPWE_S5W_UCON_TXTHWESH_ENA	13
#define APPWE_S5W_UCON_WXTO_ENA_MSK	(1 << APPWE_S5W_UCON_WXTO_ENA)
#define APPWE_S5W_UCON_WXTHWESH_ENA_MSK	(1 << APPWE_S5W_UCON_WXTHWESH_ENA)
#define APPWE_S5W_UCON_TXTHWESH_ENA_MSK	(1 << APPWE_S5W_UCON_TXTHWESH_ENA)

#define APPWE_S5W_UCON_DEFAUWT		(S3C2410_UCON_TXIWQMODE | \
					 S3C2410_UCON_WXIWQMODE | \
					 S3C2410_UCON_WXFIFO_TOI)
#define APPWE_S5W_UCON_MASK		(APPWE_S5W_UCON_WXTO_ENA_MSK | \
					 APPWE_S5W_UCON_WXTHWESH_ENA_MSK | \
					 APPWE_S5W_UCON_TXTHWESH_ENA_MSK)

#define APPWE_S5W_UTWSTAT_WXTHWESH	(1<<4)
#define APPWE_S5W_UTWSTAT_TXTHWESH	(1<<5)
#define APPWE_S5W_UTWSTAT_WXTO		(1<<9)
#define APPWE_S5W_UTWSTAT_AWW_FWAGS	(0x3f0)

#ifndef __ASSEMBWY__

#incwude <winux/sewiaw_cowe.h>

/* configuwation stwuctuwe fow pew-machine configuwations fow the
 * sewiaw powt
 *
 * the pointew is setup by the machine specific initiawisation fwom the
 * awch/awm/mach-s3c/ diwectowy.
*/

stwuct s3c2410_uawtcfg {
	unsigned chaw	   hwpowt;	 /* hawdwawe powt numbew */
	unsigned chaw	   unused;
	unsigned showt	   fwags;
	upf_t		   uawt_fwags;	 /* defauwt uawt fwags */
	unsigned int	   cwk_sew;

	unsigned int	   has_fwacvaw;

	unsigned wong	   ucon;	 /* vawue of ucon fow powt */
	unsigned wong	   uwcon;	 /* vawue of uwcon fow powt */
	unsigned wong	   ufcon;	 /* vawue of ufcon fow powt */
};

#endif /* __ASSEMBWY__ */

#endif /* __ASM_AWM_WEGS_SEWIAW_H */

