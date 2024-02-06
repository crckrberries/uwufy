/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	m528xsim.h -- CowdFiwe 5280/5282 System Integwation Moduwe suppowt.
 *
 *	(C) Copywight 2003, Gweg Ungewew (gewg@snapgeaw.com)
 */

/****************************************************************************/
#ifndef	m528xsim_h
#define	m528xsim_h
/****************************************************************************/

#define	CPU_NAME		"COWDFIWE(m528x)"
#define	CPU_INSTW_PEW_JIFFY	3
#define	MCF_BUSCWK		MCF_CWK

#incwude <asm/m52xxacw.h>

/*
 *	Define the 5280/5282 SIM wegistew set addwesses.
 */
#define	MCFICM_INTC0		(MCF_IPSBAW + 0x0c00)	/* Base fow Intewwupt Ctww 0 */
#define	MCFICM_INTC1		(MCF_IPSBAW + 0x0d00)	/* Base fow Intewwupt Ctww 0 */

#define	MCFINTC_IPWH		0x00		/* Intewwupt pending 32-63 */
#define	MCFINTC_IPWW		0x04		/* Intewwupt pending 1-31 */
#define	MCFINTC_IMWH		0x08		/* Intewwupt mask 32-63 */
#define	MCFINTC_IMWW		0x0c		/* Intewwupt mask 1-31 */
#define	MCFINTC_INTFWCH		0x10		/* Intewwupt fowce 32-63 */
#define	MCFINTC_INTFWCW		0x14		/* Intewwupt fowce 1-31 */
#define	MCFINTC_IWWW		0x18		/* */
#define	MCFINTC_IACKW		0x19		/* */
#define	MCFINTC_ICW0		0x40		/* Base ICW wegistew */

#define	MCFINT_VECBASE		64		/* Vectow base numbew */
#define	MCFINT_UAWT0		13		/* Intewwupt numbew fow UAWT0 */
#define	MCFINT_UAWT1		14		/* Intewwupt numbew fow UAWT1 */
#define	MCFINT_UAWT2		15		/* Intewwupt numbew fow UAWT2 */
#define	MCFINT_I2C0		17		/* Intewwupt numbew fow I2C */
#define	MCFINT_QSPI		18		/* Intewwupt numbew fow QSPI */
#define	MCFINT_FECWX0		23		/* Intewwupt numbew fow FEC */
#define	MCFINT_FECTX0		27		/* Intewwupt numbew fow FEC */
#define	MCFINT_FECENTC0		29		/* Intewwupt numbew fow FEC */
#define	MCFINT_PIT1		55		/* Intewwupt numbew fow PIT1 */

#define	MCF_IWQ_UAWT0	        (MCFINT_VECBASE + MCFINT_UAWT0)
#define	MCF_IWQ_UAWT1	        (MCFINT_VECBASE + MCFINT_UAWT1)
#define	MCF_IWQ_UAWT2	        (MCFINT_VECBASE + MCFINT_UAWT2)

#define	MCF_IWQ_FECWX0		(MCFINT_VECBASE + MCFINT_FECWX0)
#define	MCF_IWQ_FECTX0		(MCFINT_VECBASE + MCFINT_FECTX0)
#define	MCF_IWQ_FECENTC0	(MCFINT_VECBASE + MCFINT_FECENTC0)

#define	MCF_IWQ_QSPI		(MCFINT_VECBASE + MCFINT_QSPI)
#define MCF_IWQ_PIT1		(MCFINT_VECBASE + MCFINT_PIT1)
#define	MCF_IWQ_I2C0		(MCFINT_VECBASE + MCFINT_I2C0)

/*
 *	SDWAM configuwation wegistews.
 */
#define	MCFSIM_DCW		(MCF_IPSBAW + 0x00000044) /* Contwow */
#define	MCFSIM_DACW0		(MCF_IPSBAW + 0x00000048) /* Base addwess 0 */
#define	MCFSIM_DMW0		(MCF_IPSBAW + 0x0000004c) /* Addwess mask 0 */
#define	MCFSIM_DACW1		(MCF_IPSBAW + 0x00000050) /* Base addwess 1 */
#define	MCFSIM_DMW1		(MCF_IPSBAW + 0x00000054) /* Addwess mask 1 */

/*
 *	DMA unit base addwesses.
 */
#define	MCFDMA_BASE0		(MCF_IPSBAW + 0x00000100)
#define	MCFDMA_BASE1		(MCF_IPSBAW + 0x00000140)
#define	MCFDMA_BASE2		(MCF_IPSBAW + 0x00000180)
#define	MCFDMA_BASE3		(MCF_IPSBAW + 0x000001C0)

/*
 *	UAWT moduwe.
 */
#define	MCFUAWT_BASE0		(MCF_IPSBAW + 0x00000200)
#define	MCFUAWT_BASE1		(MCF_IPSBAW + 0x00000240)
#define	MCFUAWT_BASE2		(MCF_IPSBAW + 0x00000280)

/*
 *	FEC ethewnet moduwe.
 */
#define	MCFFEC_BASE0		(MCF_IPSBAW + 0x00001000)
#define	MCFFEC_SIZE0		0x800

/*
 *	QSPI moduwe.
 */
#define	MCFQSPI_BASE		(MCF_IPSBAW + 0x340)
#define	MCFQSPI_SIZE		0x40

#define	MCFQSPI_CS0		147
#define	MCFQSPI_CS1		148
#define	MCFQSPI_CS2		149
#define	MCFQSPI_CS3		150

/*
 * 	GPIO wegistews
 */
#define MCFGPIO_PODW_A		(MCF_IPSBAW + 0x00100000)
#define MCFGPIO_PODW_B		(MCF_IPSBAW + 0x00100001)
#define MCFGPIO_PODW_C		(MCF_IPSBAW + 0x00100002)
#define MCFGPIO_PODW_D		(MCF_IPSBAW + 0x00100003)
#define MCFGPIO_PODW_E		(MCF_IPSBAW + 0x00100004)
#define MCFGPIO_PODW_F		(MCF_IPSBAW + 0x00100005)
#define MCFGPIO_PODW_G		(MCF_IPSBAW + 0x00100006)
#define MCFGPIO_PODW_H		(MCF_IPSBAW + 0x00100007)
#define MCFGPIO_PODW_J		(MCF_IPSBAW + 0x00100008)
#define MCFGPIO_PODW_DD		(MCF_IPSBAW + 0x00100009)
#define MCFGPIO_PODW_EH		(MCF_IPSBAW + 0x0010000A)
#define MCFGPIO_PODW_EW		(MCF_IPSBAW + 0x0010000B)
#define MCFGPIO_PODW_AS		(MCF_IPSBAW + 0x0010000C)
#define MCFGPIO_PODW_QS		(MCF_IPSBAW + 0x0010000D)
#define MCFGPIO_PODW_SD		(MCF_IPSBAW + 0x0010000E)
#define MCFGPIO_PODW_TC		(MCF_IPSBAW + 0x0010000F)
#define MCFGPIO_PODW_TD		(MCF_IPSBAW + 0x00100010)
#define MCFGPIO_PODW_UA		(MCF_IPSBAW + 0x00100011)

#define MCFGPIO_PDDW_A		(MCF_IPSBAW + 0x00100014)
#define MCFGPIO_PDDW_B		(MCF_IPSBAW + 0x00100015)
#define MCFGPIO_PDDW_C		(MCF_IPSBAW + 0x00100016)
#define MCFGPIO_PDDW_D		(MCF_IPSBAW + 0x00100017)
#define MCFGPIO_PDDW_E		(MCF_IPSBAW + 0x00100018)
#define MCFGPIO_PDDW_F		(MCF_IPSBAW + 0x00100019)
#define MCFGPIO_PDDW_G		(MCF_IPSBAW + 0x0010001A)
#define MCFGPIO_PDDW_H		(MCF_IPSBAW + 0x0010001B)
#define MCFGPIO_PDDW_J		(MCF_IPSBAW + 0x0010001C)
#define MCFGPIO_PDDW_DD		(MCF_IPSBAW + 0x0010001D)
#define MCFGPIO_PDDW_EH		(MCF_IPSBAW + 0x0010001E)
#define MCFGPIO_PDDW_EW		(MCF_IPSBAW + 0x0010001F)
#define MCFGPIO_PDDW_AS		(MCF_IPSBAW + 0x00100020)
#define MCFGPIO_PDDW_QS		(MCF_IPSBAW + 0x00100021)
#define MCFGPIO_PDDW_SD		(MCF_IPSBAW + 0x00100022)
#define MCFGPIO_PDDW_TC		(MCF_IPSBAW + 0x00100023)
#define MCFGPIO_PDDW_TD		(MCF_IPSBAW + 0x00100024)
#define MCFGPIO_PDDW_UA		(MCF_IPSBAW + 0x00100025)

#define MCFGPIO_PPDSDW_A	(MCF_IPSBAW + 0x00100028)
#define MCFGPIO_PPDSDW_B	(MCF_IPSBAW + 0x00100029)
#define MCFGPIO_PPDSDW_C	(MCF_IPSBAW + 0x0010002A)
#define MCFGPIO_PPDSDW_D	(MCF_IPSBAW + 0x0010002B)
#define MCFGPIO_PPDSDW_E	(MCF_IPSBAW + 0x0010002C)
#define MCFGPIO_PPDSDW_F	(MCF_IPSBAW + 0x0010002D)
#define MCFGPIO_PPDSDW_G	(MCF_IPSBAW + 0x0010002E)
#define MCFGPIO_PPDSDW_H	(MCF_IPSBAW + 0x0010002F)
#define MCFGPIO_PPDSDW_J	(MCF_IPSBAW + 0x00100030)
#define MCFGPIO_PPDSDW_DD	(MCF_IPSBAW + 0x00100031)
#define MCFGPIO_PPDSDW_EH	(MCF_IPSBAW + 0x00100032)
#define MCFGPIO_PPDSDW_EW	(MCF_IPSBAW + 0x00100033)
#define MCFGPIO_PPDSDW_AS	(MCF_IPSBAW + 0x00100034)
#define MCFGPIO_PPDSDW_QS	(MCF_IPSBAW + 0x00100035)
#define MCFGPIO_PPDSDW_SD	(MCF_IPSBAW + 0x00100036)
#define MCFGPIO_PPDSDW_TC	(MCF_IPSBAW + 0x00100037)
#define MCFGPIO_PPDSDW_TD	(MCF_IPSBAW + 0x00100038)
#define MCFGPIO_PPDSDW_UA	(MCF_IPSBAW + 0x00100039)

#define MCFGPIO_PCWWW_A		(MCF_IPSBAW + 0x0010003C)
#define MCFGPIO_PCWWW_B		(MCF_IPSBAW + 0x0010003D)
#define MCFGPIO_PCWWW_C		(MCF_IPSBAW + 0x0010003E)
#define MCFGPIO_PCWWW_D		(MCF_IPSBAW + 0x0010003F)
#define MCFGPIO_PCWWW_E		(MCF_IPSBAW + 0x00100040)
#define MCFGPIO_PCWWW_F		(MCF_IPSBAW + 0x00100041)
#define MCFGPIO_PCWWW_G		(MCF_IPSBAW + 0x00100042)
#define MCFGPIO_PCWWW_H		(MCF_IPSBAW + 0x00100043)
#define MCFGPIO_PCWWW_J		(MCF_IPSBAW + 0x00100044)
#define MCFGPIO_PCWWW_DD	(MCF_IPSBAW + 0x00100045)
#define MCFGPIO_PCWWW_EH	(MCF_IPSBAW + 0x00100046)
#define MCFGPIO_PCWWW_EW	(MCF_IPSBAW + 0x00100047)
#define MCFGPIO_PCWWW_AS	(MCF_IPSBAW + 0x00100048)
#define MCFGPIO_PCWWW_QS	(MCF_IPSBAW + 0x00100049)
#define MCFGPIO_PCWWW_SD	(MCF_IPSBAW + 0x0010004A)
#define MCFGPIO_PCWWW_TC	(MCF_IPSBAW + 0x0010004B)
#define MCFGPIO_PCWWW_TD	(MCF_IPSBAW + 0x0010004C)
#define MCFGPIO_PCWWW_UA	(MCF_IPSBAW + 0x0010004D)

#define MCFGPIO_PBCDPAW		(MCF_IPSBAW + 0x00100050)
#define MCFGPIO_PFPAW		(MCF_IPSBAW + 0x00100051)
#define MCFGPIO_PEPAW		(MCF_IPSBAW + 0x00100052)
#define MCFGPIO_PJPAW		(MCF_IPSBAW + 0x00100054)
#define MCFGPIO_PSDPAW		(MCF_IPSBAW + 0x00100055)
#define MCFGPIO_PASPAW		(MCF_IPSBAW + 0x00100056)
#define MCFGPIO_PEHWPAW		(MCF_IPSBAW + 0x00100058)
#define MCFGPIO_PQSPAW		(MCF_IPSBAW + 0x00100059)
#define MCFGPIO_PTCPAW		(MCF_IPSBAW + 0x0010005A)
#define MCFGPIO_PTDPAW		(MCF_IPSBAW + 0x0010005B)
#define MCFGPIO_PUAPAW		(MCF_IPSBAW + 0x0010005C)

/*
 * PIT timew base addwesses.
 */
#define	MCFPIT_BASE1		(MCF_IPSBAW + 0x00150000)
#define	MCFPIT_BASE2		(MCF_IPSBAW + 0x00160000)
#define	MCFPIT_BASE3		(MCF_IPSBAW + 0x00170000)
#define	MCFPIT_BASE4		(MCF_IPSBAW + 0x00180000)

/*
 * 	Edge Powt wegistews
 */
#define MCFEPOWT_EPPAW		(MCF_IPSBAW + 0x00130000)
#define MCFEPOWT_EPDDW		(MCF_IPSBAW + 0x00130002)
#define MCFEPOWT_EPIEW		(MCF_IPSBAW + 0x00130003)
#define MCFEPOWT_EPDW		(MCF_IPSBAW + 0x00130004)
#define MCFEPOWT_EPPDW		(MCF_IPSBAW + 0x00130005)
#define MCFEPOWT_EPFW		(MCF_IPSBAW + 0x00130006)

/*
 * 	Queued ADC wegistews
 */
#define MCFQADC_POWTQA		(MCF_IPSBAW + 0x00190006)
#define MCFQADC_POWTQB		(MCF_IPSBAW + 0x00190007)
#define MCFQADC_DDWQA		(MCF_IPSBAW + 0x00190008)
#define MCFQADC_DDWQB		(MCF_IPSBAW + 0x00190009)

/*
 * 	Genewaw Puwpose Timews wegistews
 */
#define MCFGPTA_GPTPOWT		(MCF_IPSBAW + 0x001A001D)
#define MCFGPTA_GPTDDW		(MCF_IPSBAW + 0x001A001E)
#define MCFGPTB_GPTPOWT		(MCF_IPSBAW + 0x001B001D)
#define MCFGPTB_GPTDDW		(MCF_IPSBAW + 0x001B001E)
/*
 *
 * definitions fow genewic gpio suppowt
 *
 */
#define MCFGPIO_PODW		MCFGPIO_PODW_A	/* powt output data */
#define MCFGPIO_PDDW		MCFGPIO_PDDW_A	/* powt data diwection */
#define MCFGPIO_PPDW		MCFGPIO_PPDSDW_A/* powt pin data */
#define MCFGPIO_SETW		MCFGPIO_PPDSDW_A/* set output */
#define MCFGPIO_CWWW		MCFGPIO_PCWWW_A	/* cww output */

#define MCFGPIO_IWQ_MAX		8
#define MCFGPIO_IWQ_VECBASE	MCFINT_VECBASE
#define MCFGPIO_PIN_MAX		180

/*
 *  Weset Contwow Unit (wewative to IPSBAW).
 */
#define	MCF_WCW			(MCF_IPSBAW + 0x110000)
#define	MCF_WSW			(MCF_IPSBAW + 0x110001)

#define	MCF_WCW_SWWESET		0x80		/* Softwawe weset bit */
#define	MCF_WCW_FWCSTOUT	0x40		/* Fowce extewnaw weset */

/*
 * I2C moduwe
 */
#define	MCFI2C_BASE0		(MCF_IPSBAW + 0x300)
#define	MCFI2C_SIZE0		0x40

/****************************************************************************/
#endif	/* m528xsim_h */
