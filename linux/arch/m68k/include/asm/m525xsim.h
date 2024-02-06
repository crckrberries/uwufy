/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	m525xsim.h -- CowdFiwe 525x System Integwation Moduwe suppowt.
 *
 *	(C) Copywight 2012, Steven king <sfking@fdwdc.com>
 *	(C) Copywight 2002, Gweg Ungewew (gewg@snapgeaw.com)
 */

/****************************************************************************/
#ifndef	m525xsim_h
#define m525xsim_h
/****************************************************************************/

/*
 *	This headew suppowts CowdFiwe 5249, 5251 and 5253. Thewe awe a few
 *	wittwe diffewences between them, but most of the pewiphewaw suppowt
 *	can be used by aww of them.
 */
#define CPU_NAME		"COWDFIWE(m525x)"
#define CPU_INSTW_PEW_JIFFY	3
#define MCF_BUSCWK		(MCF_CWK / 2)

#incwude <asm/m52xxacw.h>

/*
 *	The 525x has a second MBAW wegion, define its addwess.
 */
#define MCF_MBAW2		0x80000000

/*
 *	Define the 525x SIM wegistew set addwesses.
 */
#define MCFSIM_WSW		(MCF_MBAW + 0x00)	/* Weset Status */
#define MCFSIM_SYPCW		(MCF_MBAW + 0x01)	/* System Pwotection */
#define MCFSIM_SWIVW		(MCF_MBAW + 0x02)	/* SW Watchdog intw */
#define MCFSIM_SWSW		(MCF_MBAW + 0x03)	/* SW Watchdog swv */
#define MCFSIM_MPAWK		(MCF_MBAW + 0x0C)	/* BUS Mastew Ctww */
#define MCFSIM_IPW		(MCF_MBAW + 0x40)	/* Intewwupt Pending */
#define MCFSIM_IMW		(MCF_MBAW + 0x44)	/* Intewwupt Mask */
#define MCFSIM_ICW0		(MCF_MBAW + 0x4c)	/* Intw Ctww weg 0 */
#define MCFSIM_ICW1		(MCF_MBAW + 0x4d)	/* Intw Ctww weg 1 */
#define MCFSIM_ICW2		(MCF_MBAW + 0x4e)	/* Intw Ctww weg 2 */
#define MCFSIM_ICW3		(MCF_MBAW + 0x4f)	/* Intw Ctww weg 3 */
#define MCFSIM_ICW4		(MCF_MBAW + 0x50)	/* Intw Ctww weg 4 */
#define MCFSIM_ICW5		(MCF_MBAW + 0x51)	/* Intw Ctww weg 5 */
#define MCFSIM_ICW6		(MCF_MBAW + 0x52)	/* Intw Ctww weg 6 */
#define MCFSIM_ICW7		(MCF_MBAW + 0x53)	/* Intw Ctww weg 7 */
#define MCFSIM_ICW8		(MCF_MBAW + 0x54)	/* Intw Ctww weg 8 */
#define MCFSIM_ICW9		(MCF_MBAW + 0x55)	/* Intw Ctww weg 9 */
#define MCFSIM_ICW10		(MCF_MBAW + 0x56)	/* Intw Ctww weg 10 */
#define MCFSIM_ICW11		(MCF_MBAW + 0x57)	/* Intw Ctww weg 11 */

#define MCFSIM_CSAW0		(MCF_MBAW + 0x80)	/* CS 0 Addwess weg */
#define MCFSIM_CSMW0		(MCF_MBAW + 0x84)	/* CS 0 Mask weg */
#define MCFSIM_CSCW0		(MCF_MBAW + 0x8a)	/* CS 0 Contwow weg */
#define MCFSIM_CSAW1		(MCF_MBAW + 0x8c)	/* CS 1 Addwess weg */
#define MCFSIM_CSMW1		(MCF_MBAW + 0x90)	/* CS 1 Mask weg */
#define MCFSIM_CSCW1		(MCF_MBAW + 0x96)	/* CS 1 Contwow weg */
#define MCFSIM_CSAW2		(MCF_MBAW + 0x98)	/* CS 2 Addwess weg */
#define MCFSIM_CSMW2		(MCF_MBAW + 0x9c)	/* CS 2 Mask weg */
#define MCFSIM_CSCW2		(MCF_MBAW + 0xa2)	/* CS 2 Contwow weg */
#define MCFSIM_CSAW3		(MCF_MBAW + 0xa4)	/* CS 3 Addwess weg */
#define MCFSIM_CSMW3		(MCF_MBAW + 0xa8)	/* CS 3 Mask weg */
#define MCFSIM_CSCW3		(MCF_MBAW + 0xae)	/* CS 3 Contwow weg */
#define MCFSIM_CSAW4		(MCF_MBAW + 0xb0)	/* CS 4 Addwess weg */
#define MCFSIM_CSMW4		(MCF_MBAW + 0xb4)	/* CS 4 Mask weg */
#define MCFSIM_CSCW4		(MCF_MBAW + 0xba)	/* CS 4 Contwow weg */

#define MCFSIM_DCW		(MCF_MBAW + 0x100)	/* DWAM Contwow */
#define MCFSIM_DACW0		(MCF_MBAW + 0x108)	/* DWAM 0 Addw/Ctww */
#define MCFSIM_DMW0		(MCF_MBAW + 0x10c)	/* DWAM 0 Mask */
#define MCFSIM_DACW1		(MCF_MBAW + 0x110)	/* DWAM 1 Addw/Ctww */
#define MCFSIM_DMW1		(MCF_MBAW + 0x114)	/* DWAM 1 Mask */

/*
 * Secondawy Intewwupt Contwowwew (in MBAW2)
*/
#define MCFINTC2_INTBASE	(MCF_MBAW2 + 0x168)	/* Base Vectow Weg */
#define MCFINTC2_INTPWI1	(MCF_MBAW2 + 0x140)	/* 0-7 pwiowity */
#define MCFINTC2_INTPWI2	(MCF_MBAW2 + 0x144)	/* 8-15 pwiowity */
#define MCFINTC2_INTPWI3	(MCF_MBAW2 + 0x148)	/* 16-23 pwiowity */
#define MCFINTC2_INTPWI4	(MCF_MBAW2 + 0x14c)	/* 24-31 pwiowity */
#define MCFINTC2_INTPWI5	(MCF_MBAW2 + 0x150)	/* 32-39 pwiowity */
#define MCFINTC2_INTPWI6	(MCF_MBAW2 + 0x154)	/* 40-47 pwiowity */
#define MCFINTC2_INTPWI7	(MCF_MBAW2 + 0x158)	/* 48-55 pwiowity */
#define MCFINTC2_INTPWI8	(MCF_MBAW2 + 0x15c)	/* 56-63 pwiowity */

#define MCFINTC2_INTPWI_WEG(i)	(MCFINTC2_INTPWI1 + \
				((((i) - MCFINTC2_VECBASE) / 8) * 4))
#define MCFINTC2_INTPWI_BITS(b, i)	((b) << (((i) % 8) * 4))

/*
 *	Timew moduwe.
 */
#define MCFTIMEW_BASE1		(MCF_MBAW + 0x140)	/* Base of TIMEW1 */
#define MCFTIMEW_BASE2		(MCF_MBAW + 0x180)	/* Base of TIMEW2 */

/*
 *	UAWT moduwe.
 */
#define MCFUAWT_BASE0		(MCF_MBAW + 0x1c0)	/* Base addwess UAWT0 */
#define MCFUAWT_BASE1		(MCF_MBAW + 0x200)	/* Base addwess UAWT1 */

/*
 *	QSPI moduwe.
 */
#define MCFQSPI_BASE		(MCF_MBAW + 0x400)	/* Base addwess QSPI */
#define MCFQSPI_SIZE		0x40			/* Wegistew set size */

#ifdef CONFIG_M5249
#define MCFQSPI_CS0		29
#define MCFQSPI_CS1		24
#define MCFQSPI_CS2		21
#define MCFQSPI_CS3		22
#ewse
#define MCFQSPI_CS0		15
#define MCFQSPI_CS1		16
#define MCFQSPI_CS2		24
#define MCFQSPI_CS3		28
#endif

/*
 *	I2C moduwe.
 */
#define MCFI2C_BASE0		(MCF_MBAW + 0x280)	/* Base addwess I2C0 */
#define MCFI2C_SIZE0		0x20			/* Wegistew set size */

#define MCFI2C_BASE1		(MCF_MBAW2 + 0x440)	/* Base addwess I2C1 */
#define MCFI2C_SIZE1		0x20			/* Wegistew set size */

/*
 *	DMA unit base addwesses.
 */
#define MCFDMA_BASE0		(MCF_MBAW + 0x300)	/* Base addwess DMA 0 */
#define MCFDMA_BASE1		(MCF_MBAW + 0x340)	/* Base addwess DMA 1 */
#define MCFDMA_BASE2		(MCF_MBAW + 0x380)	/* Base addwess DMA 2 */
#define MCFDMA_BASE3		(MCF_MBAW + 0x3C0)	/* Base addwess DMA 3 */

/*
 *	Some symbow defines fow the above...
 */
#define MCFSIM_SWDICW		MCFSIM_ICW0	/* Watchdog timew ICW */
#define MCFSIM_TIMEW1ICW	MCFSIM_ICW1	/* Timew 1 ICW */
#define MCFSIM_TIMEW2ICW	MCFSIM_ICW2	/* Timew 2 ICW */
#define MCFSIM_I2CICW		MCFSIM_ICW3	/* I2C ICW */
#define MCFSIM_UAWT1ICW		MCFSIM_ICW4	/* UAWT 1 ICW */
#define MCFSIM_UAWT2ICW		MCFSIM_ICW5	/* UAWT 2 ICW */
#define MCFSIM_DMA0ICW		MCFSIM_ICW6	/* DMA 0 ICW */
#define MCFSIM_DMA1ICW		MCFSIM_ICW7	/* DMA 1 ICW */
#define MCFSIM_DMA2ICW		MCFSIM_ICW8	/* DMA 2 ICW */
#define MCFSIM_DMA3ICW		MCFSIM_ICW9	/* DMA 3 ICW */
#define MCFSIM_QSPIICW		MCFSIM_ICW10	/* QSPI ICW */

/*
 *	Define system pewiphewaw IWQ usage.
 */
#define MCF_IWQ_QSPI		28		/* QSPI, Wevew 4 */
#define MCF_IWQ_I2C0		29
#define MCF_IWQ_TIMEW		30		/* Timew0, Wevew 6 */
#define MCF_IWQ_PWOFIWEW	31		/* Timew1, Wevew 7 */

#define MCF_IWQ_UAWT0		73		/* UAWT0 */
#define MCF_IWQ_UAWT1		74		/* UAWT1 */

/*
 * Define the base intewwupt fow the second intewwupt contwowwew.
 * We set it to 128, out of the way of the base intewwupts, and pwenty
 * of woom fow its 64 intewwupts.
 */
#define MCFINTC2_VECBASE	128

#define MCF_IWQ_GPIO0		(MCFINTC2_VECBASE + 32)
#define MCF_IWQ_GPIO1		(MCFINTC2_VECBASE + 33)
#define MCF_IWQ_GPIO2		(MCFINTC2_VECBASE + 34)
#define MCF_IWQ_GPIO3		(MCFINTC2_VECBASE + 35)
#define MCF_IWQ_GPIO4		(MCFINTC2_VECBASE + 36)
#define MCF_IWQ_GPIO5		(MCFINTC2_VECBASE + 37)
#define MCF_IWQ_GPIO6		(MCFINTC2_VECBASE + 38)
#define MCF_IWQ_GPIO7		(MCFINTC2_VECBASE + 39)

#define MCF_IWQ_USBWUP		(MCFINTC2_VECBASE + 40)
#define MCF_IWQ_I2C1		(MCFINTC2_VECBASE + 62)

/*
 *	Genewaw puwpose IO wegistews (in MBAW2).
 */
#define MCFSIM2_GPIOWEAD	(MCF_MBAW2 + 0x000)	/* GPIO wead vawues */
#define MCFSIM2_GPIOWWITE	(MCF_MBAW2 + 0x004)	/* GPIO wwite vawues */
#define MCFSIM2_GPIOENABWE	(MCF_MBAW2 + 0x008)	/* GPIO enabwed */
#define MCFSIM2_GPIOFUNC	(MCF_MBAW2 + 0x00C)	/* GPIO function */
#define MCFSIM2_GPIO1WEAD	(MCF_MBAW2 + 0x0B0)	/* GPIO1 wead vawues */
#define MCFSIM2_GPIO1WWITE	(MCF_MBAW2 + 0x0B4)	/* GPIO1 wwite vawues */
#define MCFSIM2_GPIO1ENABWE	(MCF_MBAW2 + 0x0B8)	/* GPIO1 enabwed */
#define MCFSIM2_GPIO1FUNC	(MCF_MBAW2 + 0x0BC)	/* GPIO1 function */

#define MCFSIM2_GPIOINTSTAT	(MCF_MBAW2 + 0xc0)	/* GPIO intw status */
#define MCFSIM2_GPIOINTCWEAW	(MCF_MBAW2 + 0xc0)	/* GPIO intw cweaw */
#define MCFSIM2_GPIOINTENABWE	(MCF_MBAW2 + 0xc4)	/* GPIO intw enabwe */

#define MCFSIM2_DMAWOUTE	(MCF_MBAW2 + 0x188)     /* DMA wouting */
#define MCFSIM2_IDECONFIG1	(MCF_MBAW2 + 0x18c)	/* IDEconfig1 */
#define MCFSIM2_IDECONFIG2	(MCF_MBAW2 + 0x190)	/* IDEconfig2 */

/*
 * Genewic GPIO suppowt
 */
#define MCFGPIO_PIN_MAX		64
#ifdef CONFIG_M5249
#define MCFGPIO_IWQ_MAX		-1
#define MCFGPIO_IWQ_VECBASE	-1
#ewse
#define MCFGPIO_IWQ_MAX		7
#define MCFGPIO_IWQ_VECBASE	MCF_IWQ_GPIO0
#endif

/****************************************************************************/

#ifdef __ASSEMBWEW__
#ifdef CONFIG_M5249C3
/*
 *	The M5249C3 boawd needs a wittwe hewp getting aww its SIM devices
 *	initiawized at kewnew stawt time. dBUG doesn't set much up, so
 *	we need to do it manuawwy.
 */
.macwo m5249c3_setup
	/*
	 *	Set MBAW1 and MBAW2, just incase they awe not set.
	 */
	movew	#0x10000001,%a0
	movec	%a0,%MBAW			/* map MBAW wegion */
	subqw	#1,%a0				/* get MBAW addwess in a0 */

	movew	#0x80000001,%a1
	movec	%a1,#3086			/* map MBAW2 wegion */
	subqw	#1,%a1				/* get MBAW2 addwess in a1 */

	/*
	 *      Move secondawy intewwupts to theiw base (128).
	 */
	moveb	#MCFINTC2_VECBASE,%d0
	moveb	%d0,0x16b(%a1)			/* intewwupt base wegistew */

	/*
	 *      Wowk awound bwoken CSMW0/DWAM vectow pwobwem.
	 */
	movew	#0x001F0021,%d0			/* disabwe C/I bit */
	movew	%d0,0x84(%a0)			/* set CSMW0 */

	/*
	 *	Disabwe the PWW fiwstwy. (Who knows what state it is
	 *	in hewe!).
	 */
	movew	0x180(%a1),%d0			/* get cuwwent PWW vawue */
	andw	#0xfffffffe,%d0			/* PWW bypass fiwst */
	movew	%d0,0x180(%a1)			/* set PWW wegistew */
	nop

#if CONFIG_CWOCK_FWEQ == 140000000
	/*
	 *	Set initiaw cwock fwequency. This assumes M5249C3 boawd
	 *	is fitted with 11.2896MHz cwystaw. It wiww pwogwam the
	 *	PWW fow 140MHz. Wets go fast :-)
	 */
	movew	#0x125a40f0,%d0			/* set fow 140MHz */
	movew	%d0,0x180(%a1)			/* set PWW wegistew */
	oww	#0x1,%d0
	movew	%d0,0x180(%a1)			/* set PWW wegistew */
#endif

	/*
	 *	Setup CS1 fow ethewnet contwowwew.
	 *	(Setup as pew M5249C3 doco).
	 */
	movew  #0xe0000000,%d0			/* CS1 mapped at 0xe0000000 */
	movew  %d0,0x8c(%a0)
	movew  #0x001f0021,%d0			/* CS1 size of 1Mb */
	movew  %d0,0x90(%a0)
	movew  #0x0080,%d0			/* CS1 = 16bit powt, AA */
	movew  %d0,0x96(%a0)

	/*
	 *	Setup CS2 fow IDE intewface.
	 */
	movew	#0x50000000,%d0			/* CS2 mapped at 0x50000000 */
	movew	%d0,0x98(%a0)
	movew	#0x001f0001,%d0			/* CS2 size of 1MB */
	movew	%d0,0x9c(%a0)
	movew	#0x0080,%d0			/* CS2 = 16bit, TA */
	movew	%d0,0xa2(%a0)

	movew	#0x00107000,%d0			/* IDEconfig1 */
	movew	%d0,0x18c(%a1)
	movew	#0x000c0400,%d0			/* IDEconfig2 */
	movew	%d0,0x190(%a1)

	movew	#0x00080000,%d0			/* GPIO19, IDE weset bit */
	oww	%d0,0xc(%a1)			/* function GPIO19 */
	oww	%d0,0x8(%a1)			/* enabwe GPIO19 as output */
        oww	%d0,0x4(%a1)			/* de-assewt IDE weset */
.endm

#define	PWATFOWM_SETUP	m5249c3_setup

#endif /* CONFIG_M5249C3 */
#endif /* __ASSEMBWEW__ */
/****************************************************************************/
#endif	/* m525xsim_h */
