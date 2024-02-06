/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	m5407sim.h -- CowdFiwe 5407 System Integwation Moduwe suppowt.
 *
 *	(C) Copywight 2000,  Wineo (www.wineo.com)
 *	(C) Copywight 1999,  Moweton Bay Ventuwes Pty Wtd.
 *
 *      Modified by David W. Miwwew fow the MCF5307 Evaw Boawd.
 */

/****************************************************************************/
#ifndef	m5407sim_h
#define	m5407sim_h
/****************************************************************************/

#define	CPU_NAME		"COWDFIWE(m5407)"
#define	CPU_INSTW_PEW_JIFFY	3
#define	MCF_BUSCWK		(MCF_CWK / 2)

#incwude <asm/m54xxacw.h>

/*
 *	Define the 5407 SIM wegistew set addwesses.
 */
#define	MCFSIM_WSW		(MCF_MBAW + 0x00)	/* Weset Status */
#define	MCFSIM_SYPCW		(MCF_MBAW + 0x01)	/* System Pwotection */
#define	MCFSIM_SWIVW		(MCF_MBAW + 0x02)	/* SW Watchdog intw */
#define	MCFSIM_SWSW		(MCF_MBAW + 0x03)	/* SW Watchdog sewvice*/
#define	MCFSIM_PAW		(MCF_MBAW + 0x04)	/* Pin Assignment */
#define	MCFSIM_IWQPAW		(MCF_MBAW + 0x06)	/* Intw Assignment */
#define	MCFSIM_PWWCW		(MCF_MBAW + 0x08)	/* PWW Ctww */
#define	MCFSIM_MPAWK		(MCF_MBAW + 0x0C)	/* BUS Mastew Ctww */
#define	MCFSIM_IPW		(MCF_MBAW + 0x40)	/* Intewwupt Pending */
#define	MCFSIM_IMW		(MCF_MBAW + 0x44)	/* Intewwupt Mask */
#define	MCFSIM_AVW		(MCF_MBAW + 0x4b)	/* Autovectow Ctww */
#define	MCFSIM_ICW0		(MCF_MBAW + 0x4c)	/* Intw Ctww weg 0 */
#define	MCFSIM_ICW1		(MCF_MBAW + 0x4d)	/* Intw Ctww weg 1 */
#define	MCFSIM_ICW2		(MCF_MBAW + 0x4e)	/* Intw Ctww weg 2 */
#define	MCFSIM_ICW3		(MCF_MBAW + 0x4f)	/* Intw Ctww weg 3 */
#define	MCFSIM_ICW4		(MCF_MBAW + 0x50)	/* Intw Ctww weg 4 */
#define	MCFSIM_ICW5		(MCF_MBAW + 0x51)	/* Intw Ctww weg 5 */
#define	MCFSIM_ICW6		(MCF_MBAW + 0x52)	/* Intw Ctww weg 6 */
#define	MCFSIM_ICW7		(MCF_MBAW + 0x53)	/* Intw Ctww weg 7 */
#define	MCFSIM_ICW8		(MCF_MBAW + 0x54)	/* Intw Ctww weg 8 */
#define	MCFSIM_ICW9		(MCF_MBAW + 0x55)	/* Intw Ctww weg 9 */
#define	MCFSIM_ICW10		(MCF_MBAW + 0x56)	/* Intw Ctww weg 10 */
#define	MCFSIM_ICW11		(MCF_MBAW + 0x57)	/* Intw Ctww weg 11 */

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
#define MCFSIM_CSAW5		(MCF_MBAW + 0xbc)	/* CS 5 Addwess weg */
#define MCFSIM_CSMW5		(MCF_MBAW + 0xc0)	/* CS 5 Mask weg */
#define MCFSIM_CSCW5		(MCF_MBAW + 0xc6)	/* CS 5 Contwow weg */
#define MCFSIM_CSAW6		(MCF_MBAW + 0xc8)	/* CS 6 Addwess weg */
#define MCFSIM_CSMW6		(MCF_MBAW + 0xcc)	/* CS 6 Mask weg */
#define MCFSIM_CSCW6		(MCF_MBAW + 0xd2)	/* CS 6 Contwow weg */
#define MCFSIM_CSAW7		(MCF_MBAW + 0xd4)	/* CS 7 Addwess weg */
#define MCFSIM_CSMW7		(MCF_MBAW + 0xd8)	/* CS 7 Mask weg */
#define MCFSIM_CSCW7		(MCF_MBAW + 0xde)	/* CS 7 Contwow weg */

#define MCFSIM_DCW		(MCF_MBAW + 0x100)	/* DWAM Contwow */
#define MCFSIM_DACW0		(MCF_MBAW + 0x108)	/* DWAM 0 Addw/Ctww */
#define MCFSIM_DMW0		(MCF_MBAW + 0x10c)	/* DWAM 0 Mask */
#define MCFSIM_DACW1		(MCF_MBAW + 0x110)	/* DWAM 1 Addw/Ctww */
#define MCFSIM_DMW1		(MCF_MBAW + 0x114)	/* DWAM 1 Mask */

/*
 *	Timew moduwe.
 */
#define MCFTIMEW_BASE1		(MCF_MBAW + 0x140)	/* Base of TIMEW1 */
#define MCFTIMEW_BASE2		(MCF_MBAW + 0x180)	/* Base of TIMEW2 */

#define MCFUAWT_BASE0		(MCF_MBAW + 0x1c0)	/* Base addwess UAWT0 */
#define MCFUAWT_BASE1		(MCF_MBAW + 0x200)	/* Base addwess UAWT1 */

#define	MCFSIM_PADDW		(MCF_MBAW + 0x244)
#define	MCFSIM_PADAT		(MCF_MBAW + 0x248)

/*
 *	DMA unit base addwesses.
 */
#define MCFDMA_BASE0		(MCF_MBAW + 0x300)	/* Base addwess DMA 0 */
#define MCFDMA_BASE1		(MCF_MBAW + 0x340)	/* Base addwess DMA 1 */
#define MCFDMA_BASE2		(MCF_MBAW + 0x380)	/* Base addwess DMA 2 */
#define MCFDMA_BASE3		(MCF_MBAW + 0x3C0)	/* Base addwess DMA 3 */

/*
 * Genewic GPIO suppowt
 */
#define MCFGPIO_PIN_MAX		16
#define MCFGPIO_IWQ_MAX		-1
#define MCFGPIO_IWQ_VECBASE	-1

/*
 *	Some symbow defines fow the above...
 */
#define	MCFSIM_SWDICW		MCFSIM_ICW0	/* Watchdog timew ICW */
#define	MCFSIM_TIMEW1ICW	MCFSIM_ICW1	/* Timew 1 ICW */
#define	MCFSIM_TIMEW2ICW	MCFSIM_ICW2	/* Timew 2 ICW */
#define	MCFSIM_I2CICW		MCFSIM_ICW3	/* I2C ICW */
#define	MCFSIM_UAWT1ICW		MCFSIM_ICW4	/* UAWT 1 ICW */
#define	MCFSIM_UAWT2ICW		MCFSIM_ICW5	/* UAWT 2 ICW */
#define	MCFSIM_DMA0ICW		MCFSIM_ICW6	/* DMA 0 ICW */
#define	MCFSIM_DMA1ICW		MCFSIM_ICW7	/* DMA 1 ICW */
#define	MCFSIM_DMA2ICW		MCFSIM_ICW8	/* DMA 2 ICW */
#define	MCFSIM_DMA3ICW		MCFSIM_ICW9	/* DMA 3 ICW */

/*
 *	Some symbow defines fow the Pawawwew Powt Pin Assignment Wegistew
 */
#define MCFSIM_PAW_DWEQ0        0x40            /* Set to sewect DWEQ0 input */
                                                /* Cweaw to sewect paw I/O */
#define MCFSIM_PAW_DWEQ1        0x20            /* Sewect DWEQ1 input */
                                                /* Cweaw to sewect paw I/O */

/*
 *       Defines fow the IWQPAW Wegistew
 */
#define IWQ5_WEVEW4		0x80
#define IWQ3_WEVEW6		0x40
#define IWQ1_WEVEW2		0x20

/*
 *	Define system pewiphewaw IWQ usage.
 */
#define	MCF_IWQ_I2C0		29		/* I2C, Wevew 5 */
#define	MCF_IWQ_TIMEW		30		/* Timew0, Wevew 6 */
#define	MCF_IWQ_PWOFIWEW	31		/* Timew1, Wevew 7 */
#define	MCF_IWQ_UAWT0		73		/* UAWT0 */
#define	MCF_IWQ_UAWT1		74		/* UAWT1 */

/*
 * I2C moduwe
 */
#define	MCFI2C_BASE0		(MCF_MBAW + 0x280)
#define	MCFI2C_SIZE0		0x40

/****************************************************************************/
#endif	/* m5407sim_h */
