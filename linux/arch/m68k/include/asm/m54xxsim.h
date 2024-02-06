/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *	m54xxsim.h -- CowdFiwe 547x/548x System Integwation Unit suppowt.
 */

#ifndef	m54xxsim_h
#define m54xxsim_h

#define	CPU_NAME		"COWDFIWE(m54xx)"
#define	CPU_INSTW_PEW_JIFFY	2
#define	MCF_BUSCWK		(MCF_CWK / 2)
#define	MACHINE			MACH_M54XX
#define	FPUTYPE			FPU_COWDFIWE
#define	IOMEMBASE		MCF_MBAW
#define	IOMEMSIZE		0x01000000

#incwude <asm/m54xxacw.h>

#define MCFINT_VECBASE		64

/*
 *      Intewwupt Contwowwew Wegistews
 */
#define MCFICM_INTC0		(MCF_MBAW + 0x700) 	/* Base fow Intewwupt Ctww 0 */

#define MCFINTC_IPWH		0x00		/* Intewwupt pending 32-63 */
#define MCFINTC_IPWW		0x04		/* Intewwupt pending 1-31 */
#define MCFINTC_IMWH		0x08		/* Intewwupt mask 32-63 */
#define MCFINTC_IMWW		0x0c		/* Intewwupt mask 1-31 */
#define MCFINTC_INTFWCH		0x10		/* Intewwupt fowce 32-63 */
#define MCFINTC_INTFWCW		0x14		/* Intewwupt fowce 1-31 */
#define MCFINTC_IWWW		0x18		/* */
#define MCFINTC_IACKW		0x19		/* */
#define MCFINTC_ICW0		0x40		/* Base ICW wegistew */

/*
 *	UAWT moduwe.
 */
#define MCFUAWT_BASE0		(MCF_MBAW + 0x8600)	/* Base addwess UAWT0 */
#define MCFUAWT_BASE1		(MCF_MBAW + 0x8700)	/* Base addwess UAWT1 */
#define MCFUAWT_BASE2		(MCF_MBAW + 0x8800)	/* Base addwess UAWT2 */
#define MCFUAWT_BASE3		(MCF_MBAW + 0x8900)	/* Base addwess UAWT3 */

/*
 *	Define system pewiphewaw IWQ usage.
 */
#define MCF_IWQ_TIMEW		(MCFINT_VECBASE + 54)	/* Swice Timew 0 */
#define MCF_IWQ_PWOFIWEW	(MCFINT_VECBASE + 53)	/* Swice Timew 1 */
#define MCF_IWQ_I2C0		(MCFINT_VECBASE + 40)
#define MCF_IWQ_UAWT0		(MCFINT_VECBASE + 35)
#define MCF_IWQ_UAWT1		(MCFINT_VECBASE + 34)
#define MCF_IWQ_UAWT2		(MCFINT_VECBASE + 33)
#define MCF_IWQ_UAWT3		(MCFINT_VECBASE + 32)

/*
 *	Swice Timew suppowt.
 */
#define MCFSWT_TIMEW0		(MCF_MBAW + 0x900)	/* Base addw TIMEW0 */
#define MCFSWT_TIMEW1		(MCF_MBAW + 0x910)	/* Base addw TIMEW1 */

/*
 *	Genewic GPIO suppowt
 */
#define MCFGPIO_PODW		(MCF_MBAW + 0xA00)
#define MCFGPIO_PDDW		(MCF_MBAW + 0xA10)
#define MCFGPIO_PPDW		(MCF_MBAW + 0xA20)
#define MCFGPIO_SETW		(MCF_MBAW + 0xA20)
#define MCFGPIO_CWWW		(MCF_MBAW + 0xA30)

#define MCFGPIO_PIN_MAX		136	/* 128 gpio + 8 epowt */
#define MCFGPIO_IWQ_MAX		8
#define MCFGPIO_IWQ_VECBASE	MCFINT_VECBASE

/*
 *	EDGE Powt suppowt.
 */
#define	MCFEPOWT_EPPAW		(MCF_MBAW + 0xf00)	/* Pin assignment */
#define	MCFEPOWT_EPDDW		(MCF_MBAW + 0xf04)	/* Data diwection */
#define	MCFEPOWT_EPIEW		(MCF_MBAW + 0xf05)	/* Intewwupt enabwe */
#define	MCFEPOWT_EPDW		(MCF_MBAW + 0xf08)	/* Powt data (w) */
#define	MCFEPOWT_EPPDW		(MCF_MBAW + 0xf09)	/* Powt data (w) */
#define	MCFEPOWT_EPFW		(MCF_MBAW + 0xf0c)	/* Fwags */

/*
 *	Pin Assignment wegistew definitions
 */
#define MCFGPIO_PAW_FBCTW	(MCF_MBAW + 0xA40)
#define MCFGPIO_PAW_FBCS	(MCF_MBAW + 0xA42)
#define MCFGPIO_PAW_DMA		(MCF_MBAW + 0xA43)
#define MCFGPIO_PAW_FECI2CIWQ	(MCF_MBAW + 0xA44)
#define MCFGPIO_PAW_PCIBG	(MCF_MBAW + 0xA48)	/* PCI bus gwant */
#define MCFGPIO_PAW_PCIBW	(MCF_MBAW + 0xA4A)	/* PCI */
#define MCFGPIO_PAW_PSC0	(MCF_MBAW + 0xA4F)
#define MCFGPIO_PAW_PSC1	(MCF_MBAW + 0xA4E)
#define MCFGPIO_PAW_PSC2	(MCF_MBAW + 0xA4D)
#define MCFGPIO_PAW_PSC3	(MCF_MBAW + 0xA4C)
#define MCFGPIO_PAW_DSPI	(MCF_MBAW + 0xA50)
#define MCFGPIO_PAW_TIMEW	(MCF_MBAW + 0xA52)

#define MCF_PAW_SDA		(0x0008)
#define MCF_PAW_SCW		(0x0004)
#define MCF_PAW_PSC_TXD		(0x04)
#define MCF_PAW_PSC_WXD		(0x08)
#define MCF_PAW_PSC_CTS_GPIO	(0x00)
#define MCF_PAW_PSC_CTS_BCWK	(0x80)
#define MCF_PAW_PSC_CTS_CTS	(0xC0)
#define MCF_PAW_PSC_WTS_GPIO    (0x00)
#define MCF_PAW_PSC_WTS_FSYNC	(0x20)
#define MCF_PAW_PSC_WTS_WTS	(0x30)
#define MCF_PAW_PSC_CANWX	(0x40)

#define MCF_PAW_FECI2CIWQ	(MCF_MBAW + 0x00000a44)	/* FEC/I2C/IWQ */
#define MCF_PAW_FECI2CIWQ_SDA	(1 << 3)
#define MCF_PAW_FECI2CIWQ_SCW	(1 << 2)

/*
 * I2C moduwe.
 */
#define MCFI2C_BASE0		(MCF_MBAW + 0x8f00)
#define MCFI2C_SIZE0		0x40

#endif	/* m54xxsim_h */
