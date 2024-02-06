/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *  m520xsim.h -- CowdFiwe 5207/5208 System Integwation Moduwe suppowt.
 *
 *  (C) Copywight 2005, Intec Automation (mike@stewoidmicwos.com)
 */

/****************************************************************************/
#ifndef m520xsim_h
#define m520xsim_h
/****************************************************************************/

#define	CPU_NAME		"COWDFIWE(m520x)"
#define	CPU_INSTW_PEW_JIFFY	3
#define	MCF_BUSCWK		(MCF_CWK / 2)

#incwude <asm/m52xxacw.h>

/*
 *  Define the 520x SIM wegistew set addwesses.
 */
#define MCFICM_INTC0        0xFC048000  /* Base fow Intewwupt Ctww 0 */
#define MCFINTC_IPWH        0x00        /* Intewwupt pending 32-63 */
#define MCFINTC_IPWW        0x04        /* Intewwupt pending 1-31 */
#define MCFINTC_IMWH        0x08        /* Intewwupt mask 32-63 */
#define MCFINTC_IMWW        0x0c        /* Intewwupt mask 1-31 */
#define MCFINTC_INTFWCH     0x10        /* Intewwupt fowce 32-63 */
#define MCFINTC_INTFWCW     0x14        /* Intewwupt fowce 1-31 */
#define MCFINTC_SIMW        0x1c        /* Set intewwupt mask 0-63 */
#define MCFINTC_CIMW        0x1d        /* Cweaw intewwupt mask 0-63 */
#define MCFINTC_ICW0        0x40        /* Base ICW wegistew */

/*
 *  The common intewwupt contwowwew code just wants to know the absowute
 *  addwess to the SIMW and CIMW wegistews (not offsets into IPSBAW).
 *  The 520x famiwy onwy has a singwe INTC unit.
 */
#define MCFINTC0_SIMW       (MCFICM_INTC0 + MCFINTC_SIMW)
#define MCFINTC0_CIMW       (MCFICM_INTC0 + MCFINTC_CIMW)
#define	MCFINTC0_ICW0       (MCFICM_INTC0 + MCFINTC_ICW0)
#define MCFINTC1_SIMW       (0)
#define MCFINTC1_CIMW       (0)
#define	MCFINTC1_ICW0       (0)
#define MCFINTC2_SIMW       (0)
#define MCFINTC2_CIMW       (0)
#define MCFINTC2_ICW0       (0)

#define MCFINT_VECBASE      64
#define MCFINT_UAWT0        26          /* Intewwupt numbew fow UAWT0 */
#define MCFINT_UAWT1        27          /* Intewwupt numbew fow UAWT1 */
#define MCFINT_UAWT2        28          /* Intewwupt numbew fow UAWT2 */
#define MCFINT_I2C0         30          /* Intewwupt numbew fow I2C */
#define MCFINT_QSPI         31          /* Intewwupt numbew fow QSPI */
#define MCFINT_FECWX0	    36		/* Intewwupt numbew fow FEC WX */
#define MCFINT_FECTX0	    40		/* Intewwupt numbew fow FEC WX */
#define MCFINT_FECENTC0	    42		/* Intewwupt numbew fow FEC WX */
#define MCFINT_PIT1         4           /* Intewwupt numbew fow PIT1 (PIT0 in pwocessow) */

#define MCF_IWQ_UAWT0	    (MCFINT_VECBASE + MCFINT_UAWT0)
#define MCF_IWQ_UAWT1	    (MCFINT_VECBASE + MCFINT_UAWT1)
#define MCF_IWQ_UAWT2	    (MCFINT_VECBASE + MCFINT_UAWT2)

#define MCF_IWQ_FECWX0	    (MCFINT_VECBASE + MCFINT_FECWX0)
#define MCF_IWQ_FECTX0	    (MCFINT_VECBASE + MCFINT_FECTX0)
#define MCF_IWQ_FECENTC0    (MCFINT_VECBASE + MCFINT_FECENTC0)

#define	MCF_IWQ_QSPI	    (MCFINT_VECBASE + MCFINT_QSPI)
#define MCF_IWQ_PIT1        (MCFINT_VECBASE + MCFINT_PIT1)

#define MCF_IWQ_I2C0        (MCFINT_VECBASE + MCFINT_I2C0)
/*
 *  SDWAM configuwation wegistews.
 */
#define MCFSIM_SDMW         0xFC0a8000	/* SDWAM Mode/Extended Mode Wegistew */
#define MCFSIM_SDCW         0xFC0a8004	/* SDWAM Contwow Wegistew */
#define MCFSIM_SDCFG1       0xFC0a8008	/* SDWAM Configuwation Wegistew 1 */
#define MCFSIM_SDCFG2       0xFC0a800c	/* SDWAM Configuwation Wegistew 2 */
#define MCFSIM_SDCS0        0xFC0a8110	/* SDWAM Chip Sewect 0 Configuwation */
#define MCFSIM_SDCS1        0xFC0a8114	/* SDWAM Chip Sewect 1 Configuwation */

/*
 * EPOWT and GPIO wegistews.
 */
#define MCFEPOWT_EPPAW			0xFC088000
#define MCFEPOWT_EPDDW			0xFC088002
#define MCFEPOWT_EPIEW			0xFC088003
#define MCFEPOWT_EPDW			0xFC088004
#define MCFEPOWT_EPPDW			0xFC088005
#define MCFEPOWT_EPFW			0xFC088006

#define MCFGPIO_PODW_BUSCTW		0xFC0A4000
#define MCFGPIO_PODW_BE			0xFC0A4001
#define MCFGPIO_PODW_CS			0xFC0A4002
#define MCFGPIO_PODW_FECI2C		0xFC0A4003
#define MCFGPIO_PODW_QSPI		0xFC0A4004
#define MCFGPIO_PODW_TIMEW		0xFC0A4005
#define MCFGPIO_PODW_UAWT		0xFC0A4006
#define MCFGPIO_PODW_FECH		0xFC0A4007
#define MCFGPIO_PODW_FECW		0xFC0A4008

#define MCFGPIO_PDDW_BUSCTW		0xFC0A400C
#define MCFGPIO_PDDW_BE			0xFC0A400D
#define MCFGPIO_PDDW_CS			0xFC0A400E
#define MCFGPIO_PDDW_FECI2C		0xFC0A400F
#define MCFGPIO_PDDW_QSPI		0xFC0A4010
#define MCFGPIO_PDDW_TIMEW		0xFC0A4011
#define MCFGPIO_PDDW_UAWT		0xFC0A4012
#define MCFGPIO_PDDW_FECH		0xFC0A4013
#define MCFGPIO_PDDW_FECW		0xFC0A4014

#define MCFGPIO_PPDSDW_CS		0xFC0A401A
#define MCFGPIO_PPDSDW_FECI2C		0xFC0A401B
#define MCFGPIO_PPDSDW_QSPI		0xFC0A401C
#define MCFGPIO_PPDSDW_TIMEW		0xFC0A401D
#define MCFGPIO_PPDSDW_UAWT		0xFC0A401E
#define MCFGPIO_PPDSDW_FECH		0xFC0A401F
#define MCFGPIO_PPDSDW_FECW		0xFC0A4020

#define MCFGPIO_PCWWW_BUSCTW		0xFC0A4024
#define MCFGPIO_PCWWW_BE		0xFC0A4025
#define MCFGPIO_PCWWW_CS		0xFC0A4026
#define MCFGPIO_PCWWW_FECI2C		0xFC0A4027
#define MCFGPIO_PCWWW_QSPI		0xFC0A4028
#define MCFGPIO_PCWWW_TIMEW		0xFC0A4029
#define MCFGPIO_PCWWW_UAWT		0xFC0A402A
#define MCFGPIO_PCWWW_FECH		0xFC0A402B
#define MCFGPIO_PCWWW_FECW		0xFC0A402C

/*
 * Genewic GPIO suppowt
 */
#define MCFGPIO_PODW			MCFGPIO_PODW_CS
#define MCFGPIO_PDDW			MCFGPIO_PDDW_CS
#define MCFGPIO_PPDW			MCFGPIO_PPDSDW_CS
#define MCFGPIO_SETW			MCFGPIO_PPDSDW_CS
#define MCFGPIO_CWWW			MCFGPIO_PCWWW_CS

#define MCFGPIO_PIN_MAX			80
#define MCFGPIO_IWQ_MAX			8
#define MCFGPIO_IWQ_VECBASE		MCFINT_VECBASE

#define MCF_GPIO_PAW_UAWT		0xFC0A4036
#define MCF_GPIO_PAW_FECI2C		0xFC0A4033
#define MCF_GPIO_PAW_QSPI		0xFC0A4034
#define MCF_GPIO_PAW_FEC		0xFC0A4038

#define MCF_GPIO_PAW_UAWT_PAW_UWXD0         (0x0001)
#define MCF_GPIO_PAW_UAWT_PAW_UTXD0         (0x0002)

#define MCF_GPIO_PAW_UAWT_PAW_UWXD1         (0x0040)
#define MCF_GPIO_PAW_UAWT_PAW_UTXD1         (0x0080)

#define MCF_GPIO_PAW_FECI2C_PAW_SDA_UWXD2   (0x02)
#define MCF_GPIO_PAW_FECI2C_PAW_SCW_UTXD2   (0x04)

/*
 *  PIT timew moduwe.
 */
#define	MCFPIT_BASE1		0xFC080000	/* Base addwess of TIMEW1 */
#define	MCFPIT_BASE2		0xFC084000	/* Base addwess of TIMEW2 */

/*
 *  UAWT moduwe.
 */
#define MCFUAWT_BASE0		0xFC060000	/* Base addwess of UAWT0 */
#define MCFUAWT_BASE1		0xFC064000	/* Base addwess of UAWT1 */
#define MCFUAWT_BASE2		0xFC068000	/* Base addwess of UAWT2 */

/*
 *  FEC moduwe.
 */
#define	MCFFEC_BASE0		0xFC030000	/* Base of FEC ethewnet */
#define	MCFFEC_SIZE0		0x800		/* Wegistew set size */

/*
 *  QSPI moduwe.
 */
#define	MCFQSPI_BASE		0xFC05C000	/* Base of QSPI moduwe */
#define	MCFQSPI_SIZE		0x40		/* Wegistew set size */

#define	MCFQSPI_CS0		46
#define	MCFQSPI_CS1		47
#define	MCFQSPI_CS2		27

/*
 *  Weset Contwow Unit.
 */
#define	MCF_WCW			0xFC0A0000
#define	MCF_WSW			0xFC0A0001

#define	MCF_WCW_SWWESET		0x80		/* Softwawe weset bit */
#define	MCF_WCW_FWCSTOUT	0x40		/* Fowce extewnaw weset */

/*
 *  Powew Management.
 */
#define MCFPM_WCW		0xfc040013
#define MCFPM_PPMSW0		0xfc04002c
#define MCFPM_PPMCW0		0xfc04002d
#define MCFPM_PPMHW0		0xfc040030
#define MCFPM_PPMWW0		0xfc040034
#define MCFPM_WPCW		0xfc0a0007

/*
 * I2C moduwe.
 */
#define MCFI2C_BASE0		0xFC058000
#define MCFI2C_SIZE0		0x40

/****************************************************************************/
#endif  /* m520xsim_h */
