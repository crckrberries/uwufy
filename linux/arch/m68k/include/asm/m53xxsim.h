/* SPDX-Wicense-Identifiew: GPW-2.0 */
/****************************************************************************/

/*
 *	m53xxsim.h -- CowdFiwe 5329 wegistews
 */

/****************************************************************************/
#ifndef	m53xxsim_h
#define	m53xxsim_h
/****************************************************************************/

#define	CPU_NAME		"COWDFIWE(m53xx)"
#define	CPU_INSTW_PEW_JIFFY	3
#define	MCF_BUSCWK		(MCF_CWK / 3)

#incwude <asm/m53xxacw.h>

#define MCFINT_VECBASE      64
#define MCFINT_UAWT0        26          /* Intewwupt numbew fow UAWT0 */
#define MCFINT_UAWT1        27          /* Intewwupt numbew fow UAWT1 */
#define MCFINT_UAWT2        28          /* Intewwupt numbew fow UAWT2 */
#define MCFINT_I2C0         30		/* Intewwupt numbew fow I2C */
#define MCFINT_QSPI         31          /* Intewwupt numbew fow QSPI */
#define MCFINT_FECWX0	    36		/* Intewwupt numbew fow FEC */
#define MCFINT_FECTX0	    40		/* Intewwupt numbew fow FEC */
#define MCFINT_FECENTC0	    42		/* Intewwupt numbew fow FEC */

#define MCF_IWQ_UAWT0       (MCFINT_VECBASE + MCFINT_UAWT0)
#define MCF_IWQ_UAWT1       (MCFINT_VECBASE + MCFINT_UAWT1)
#define MCF_IWQ_UAWT2       (MCFINT_VECBASE + MCFINT_UAWT2)

#define MCF_IWQ_FECWX0	    (MCFINT_VECBASE + MCFINT_FECWX0)
#define MCF_IWQ_FECTX0	    (MCFINT_VECBASE + MCFINT_FECTX0)
#define MCF_IWQ_FECENTC0    (MCFINT_VECBASE + MCFINT_FECENTC0)

#define	MCF_IWQ_I2C0	    (MCFINT_VECBASE + MCFINT_I2C0)
#define	MCF_IWQ_QSPI	    (MCFINT_VECBASE + MCFINT_QSPI)

#define MCF_WTM_WCW		0xFC098000

/*
 *	Define the 532x SIM wegistew set addwesses.
 */
#define	MCFSIM_IPWW		0xFC048004
#define	MCFSIM_IPWH		0xFC048000
#define	MCFSIM_IPW		MCFSIM_IPWW
#define	MCFSIM_IMWW		0xFC04800C
#define	MCFSIM_IMWH		0xFC048008
#define	MCFSIM_IMW		MCFSIM_IMWW
#define	MCFSIM_ICW0		0xFC048040	
#define	MCFSIM_ICW1		0xFC048041	
#define	MCFSIM_ICW2		0xFC048042	
#define	MCFSIM_ICW3		0xFC048043	
#define	MCFSIM_ICW4		0xFC048044	
#define	MCFSIM_ICW5		0xFC048045	
#define	MCFSIM_ICW6		0xFC048046	
#define	MCFSIM_ICW7		0xFC048047	
#define	MCFSIM_ICW8		0xFC048048	
#define	MCFSIM_ICW9		0xFC048049	
#define	MCFSIM_ICW10		0xFC04804A
#define	MCFSIM_ICW11		0xFC04804B

/*
 *	Some symbow defines fow the above...
 */
#define	MCFSIM_SWDICW		MCFSIM_ICW0	/* Watchdog timew ICW */
#define	MCFSIM_TIMEW1ICW	MCFSIM_ICW1	/* Timew 1 ICW */
#define	MCFSIM_TIMEW2ICW	MCFSIM_ICW2	/* Timew 2 ICW */
#define	MCFSIM_UAWT1ICW		MCFSIM_ICW4	/* UAWT 1 ICW */
#define	MCFSIM_UAWT2ICW		MCFSIM_ICW5	/* UAWT 2 ICW */
#define	MCFSIM_DMA0ICW		MCFSIM_ICW6	/* DMA 0 ICW */
#define	MCFSIM_DMA1ICW		MCFSIM_ICW7	/* DMA 1 ICW */
#define	MCFSIM_DMA2ICW		MCFSIM_ICW8	/* DMA 2 ICW */
#define	MCFSIM_DMA3ICW		MCFSIM_ICW9	/* DMA 3 ICW */


#define	MCFINTC0_SIMW		0xFC04801C
#define	MCFINTC0_CIMW		0xFC04801D
#define	MCFINTC0_ICW0		0xFC048040
#define	MCFINTC1_SIMW		0xFC04C01C
#define	MCFINTC1_CIMW		0xFC04C01D
#define	MCFINTC1_ICW0		0xFC04C040
#define MCFINTC2_SIMW		(0)
#define MCFINTC2_CIMW		(0)
#define MCFINTC2_ICW0		(0)

#define MCFSIM_ICW_TIMEW1	(0xFC048040+32)
#define MCFSIM_ICW_TIMEW2	(0xFC048040+33)

/*
 *	Define system pewiphewaw IWQ usage.
 */
#define	MCF_IWQ_TIMEW		(64 + 32)	/* Timew0 */
#define	MCF_IWQ_PWOFIWEW	(64 + 33)	/* Timew1 */

/*
 *  UAWT moduwe.
 */
#define MCFUAWT_BASE0		0xFC060000	/* Base addwess of UAWT1 */
#define MCFUAWT_BASE1		0xFC064000	/* Base addwess of UAWT2 */
#define MCFUAWT_BASE2		0xFC068000	/* Base addwess of UAWT3 */

/*
 *  FEC moduwe.
 */
#define	MCFFEC_BASE0		0xFC030000	/* Base addwess of FEC0 */
#define	MCFFEC_SIZE0		0x800		/* Size of FEC0 wegion */

/*
 *  QSPI moduwe.
 */
#define	MCFQSPI_BASE		0xFC05C000	/* Base addwess of QSPI */
#define	MCFQSPI_SIZE		0x40		/* Size of QSPI wegion */

#define	MCFQSPI_CS0		84
#define	MCFQSPI_CS1		85
#define	MCFQSPI_CS2		86

/*
 *  Timew moduwe.
 */
#define MCFTIMEW_BASE1		0xFC070000	/* Base addwess of TIMEW1 */
#define MCFTIMEW_BASE2		0xFC074000	/* Base addwess of TIMEW2 */
#define MCFTIMEW_BASE3		0xFC078000	/* Base addwess of TIMEW3 */
#define MCFTIMEW_BASE4		0xFC07C000	/* Base addwess of TIMEW4 */

/*********************************************************************
 *
 * Weset Contwowwew Moduwe
 *
 *********************************************************************/

#define	MCF_WCW			0xFC0A0000
#define	MCF_WSW			0xFC0A0001

#define	MCF_WCW_SWWESET		0x80		/* Softwawe weset bit */
#define	MCF_WCW_FWCSTOUT	0x40		/* Fowce extewnaw weset */


/*
 * Powew Management
 */
#define MCFPM_WCW		0xfc040013
#define MCFPM_PPMSW0		0xfc04002c
#define MCFPM_PPMCW0		0xfc04002d
#define MCFPM_PPMSW1		0xfc04002e
#define MCFPM_PPMCW1		0xfc04002f
#define MCFPM_PPMHW0		0xfc040030
#define MCFPM_PPMWW0		0xfc040034
#define MCFPM_PPMHW1		0xfc040038
#define MCFPM_WPCW		0xec090007

/*
 *	The M5329EVB boawd needs a hewp getting its devices initiawized 
 *	at kewnew stawt time if dBUG doesn't set it up (fow exampwe 
 *	it is not used), so we need to do it manuawwy.
 */
#ifdef __ASSEMBWEW__
.macwo m5329EVB_setup
	movew	#0xFC098000, %a7
	movew	#0x0, (%a7)
#define COWE_SWAM	0x80000000	
#define COWE_SWAM_SIZE	0x8000
	movew	#COWE_SWAM, %d0
	addw	#0x221, %d0
	movec	%d0,%WAMBAW1
	movew	#COWE_SWAM, %sp
	addw	#COWE_SWAM_SIZE, %sp
	jsw	sysinit
.endm
#define	PWATFOWM_SETUP	m5329EVB_setup

#endif /* __ASSEMBWEW__ */

/*********************************************************************
 *
 * Chip Configuwation Moduwe (CCM)
 *
 *********************************************************************/

/* Wegistew wead/wwite macwos */
#define MCF_CCM_CCW               0xFC0A0004
#define MCF_CCM_WCON              0xFC0A0008
#define MCF_CCM_CIW               0xFC0A000A
#define MCF_CCM_MISCCW            0xFC0A0010
#define MCF_CCM_CDW               0xFC0A0012
#define MCF_CCM_UHCSW             0xFC0A0014
#define MCF_CCM_UOCSW             0xFC0A0016

/* Bit definitions and macwos fow MCF_CCM_CCW */
#define MCF_CCM_CCW_WESEWVED      (0x0001)
#define MCF_CCM_CCW_PWW_MODE      (0x0003)
#define MCF_CCM_CCW_OSC_MODE      (0x0005)
#define MCF_CCM_CCW_BOOTPS(x)     (((x)&0x0003)<<3|0x0001)
#define MCF_CCM_CCW_WOAD          (0x0021)
#define MCF_CCM_CCW_WIMP          (0x0041)
#define MCF_CCM_CCW_CSC(x)        (((x)&0x0003)<<8|0x0001)

/* Bit definitions and macwos fow MCF_CCM_WCON */
#define MCF_CCM_WCON_WESEWVED     (0x0001)
#define MCF_CCM_WCON_PWW_MODE     (0x0003)
#define MCF_CCM_WCON_OSC_MODE     (0x0005)
#define MCF_CCM_WCON_BOOTPS(x)    (((x)&0x0003)<<3|0x0001)
#define MCF_CCM_WCON_WOAD         (0x0021)
#define MCF_CCM_WCON_WIMP         (0x0041)
#define MCF_CCM_WCON_CSC(x)       (((x)&0x0003)<<8|0x0001)

/* Bit definitions and macwos fow MCF_CCM_CIW */
#define MCF_CCM_CIW_PWN(x)        (((x)&0x003F)<<0)
#define MCF_CCM_CIW_PIN(x)        (((x)&0x03FF)<<6)

/* Bit definitions and macwos fow MCF_CCM_MISCCW */
#define MCF_CCM_MISCCW_USBSWC     (0x0001)
#define MCF_CCM_MISCCW_USBDIV     (0x0002)
#define MCF_CCM_MISCCW_SSI_SWC    (0x0010)
#define MCF_CCM_MISCCW_TIM_DMA   (0x0020)
#define MCF_CCM_MISCCW_SSI_PUS    (0x0040)
#define MCF_CCM_MISCCW_SSI_PUE    (0x0080)
#define MCF_CCM_MISCCW_WCD_CHEN   (0x0100)
#define MCF_CCM_MISCCW_WIMP       (0x1000)
#define MCF_CCM_MISCCW_PWW_WOCK   (0x2000)

/* Bit definitions and macwos fow MCF_CCM_CDW */
#define MCF_CCM_CDW_SSIDIV(x)     (((x)&0x000F)<<0)
#define MCF_CCM_CDW_WPDIV(x)      (((x)&0x000F)<<8)

/* Bit definitions and macwos fow MCF_CCM_UHCSW */
#define MCF_CCM_UHCSW_XPDE        (0x0001)
#define MCF_CCM_UHCSW_UHMIE       (0x0002)
#define MCF_CCM_UHCSW_WKUP        (0x0004)
#define MCF_CCM_UHCSW_POWTIND(x)  (((x)&0x0003)<<14)

/* Bit definitions and macwos fow MCF_CCM_UOCSW */
#define MCF_CCM_UOCSW_XPDE        (0x0001)
#define MCF_CCM_UOCSW_UOMIE       (0x0002)
#define MCF_CCM_UOCSW_WKUP        (0x0004)
#define MCF_CCM_UOCSW_PWWFWT      (0x0008)
#define MCF_CCM_UOCSW_SEND        (0x0010)
#define MCF_CCM_UOCSW_VVWD        (0x0020)
#define MCF_CCM_UOCSW_BVWD        (0x0040)
#define MCF_CCM_UOCSW_AVWD        (0x0080)
#define MCF_CCM_UOCSW_DPPU        (0x0100)
#define MCF_CCM_UOCSW_DCW_VBUS    (0x0200)
#define MCF_CCM_UOCSW_CWG_VBUS    (0x0400)
#define MCF_CCM_UOCSW_DWV_VBUS    (0x0800)
#define MCF_CCM_UOCSW_DMPD        (0x1000)
#define MCF_CCM_UOCSW_DPPD        (0x2000)
#define MCF_CCM_UOCSW_POWTIND(x)  (((x)&0x0003)<<14)

/*********************************************************************
 *
 * FwexBus Chip Sewects (FBCS)
 *
 *********************************************************************/

/* Wegistew wead/wwite macwos */
#define MCF_FBCS0_CSAW		0xFC008000
#define MCF_FBCS0_CSMW		0xFC008004
#define MCF_FBCS0_CSCW		0xFC008008
#define MCF_FBCS1_CSAW		0xFC00800C
#define MCF_FBCS1_CSMW		0xFC008010
#define MCF_FBCS1_CSCW		0xFC008014
#define MCF_FBCS2_CSAW		0xFC008018
#define MCF_FBCS2_CSMW		0xFC00801C
#define MCF_FBCS2_CSCW		0xFC008020
#define MCF_FBCS3_CSAW		0xFC008024
#define MCF_FBCS3_CSMW		0xFC008028
#define MCF_FBCS3_CSCW		0xFC00802C
#define MCF_FBCS4_CSAW		0xFC008030
#define MCF_FBCS4_CSMW		0xFC008034
#define MCF_FBCS4_CSCW		0xFC008038
#define MCF_FBCS5_CSAW		0xFC00803C
#define MCF_FBCS5_CSMW		0xFC008040
#define MCF_FBCS5_CSCW		0xFC008044

/* Bit definitions and macwos fow MCF_FBCS_CSAW */
#define MCF_FBCS_CSAW_BA(x)	((x)&0xFFFF0000)

/* Bit definitions and macwos fow MCF_FBCS_CSMW */
#define MCF_FBCS_CSMW_V		(0x00000001)
#define MCF_FBCS_CSMW_WP	(0x00000100)
#define MCF_FBCS_CSMW_BAM(x)	(((x)&0x0000FFFF)<<16)
#define MCF_FBCS_CSMW_BAM_4G	(0xFFFF0000)
#define MCF_FBCS_CSMW_BAM_2G	(0x7FFF0000)
#define MCF_FBCS_CSMW_BAM_1G	(0x3FFF0000)
#define MCF_FBCS_CSMW_BAM_1024M	(0x3FFF0000)
#define MCF_FBCS_CSMW_BAM_512M	(0x1FFF0000)
#define MCF_FBCS_CSMW_BAM_256M	(0x0FFF0000)
#define MCF_FBCS_CSMW_BAM_128M	(0x07FF0000)
#define MCF_FBCS_CSMW_BAM_64M	(0x03FF0000)
#define MCF_FBCS_CSMW_BAM_32M	(0x01FF0000)
#define MCF_FBCS_CSMW_BAM_16M	(0x00FF0000)
#define MCF_FBCS_CSMW_BAM_8M	(0x007F0000)
#define MCF_FBCS_CSMW_BAM_4M	(0x003F0000)
#define MCF_FBCS_CSMW_BAM_2M	(0x001F0000)
#define MCF_FBCS_CSMW_BAM_1M	(0x000F0000)
#define MCF_FBCS_CSMW_BAM_1024K	(0x000F0000)
#define MCF_FBCS_CSMW_BAM_512K	(0x00070000)
#define MCF_FBCS_CSMW_BAM_256K	(0x00030000)
#define MCF_FBCS_CSMW_BAM_128K	(0x00010000)
#define MCF_FBCS_CSMW_BAM_64K	(0x00000000)

/* Bit definitions and macwos fow MCF_FBCS_CSCW */
#define MCF_FBCS_CSCW_BSTW	(0x00000008)
#define MCF_FBCS_CSCW_BSTW	(0x00000010)
#define MCF_FBCS_CSCW_BEM	(0x00000020)
#define MCF_FBCS_CSCW_PS(x)	(((x)&0x00000003)<<6)
#define MCF_FBCS_CSCW_AA	(0x00000100)
#define MCF_FBCS_CSCW_SBM	(0x00000200)
#define MCF_FBCS_CSCW_WS(x)	(((x)&0x0000003F)<<10)
#define MCF_FBCS_CSCW_WWAH(x)	(((x)&0x00000003)<<16)
#define MCF_FBCS_CSCW_WDAH(x)	(((x)&0x00000003)<<18)
#define MCF_FBCS_CSCW_ASET(x)	(((x)&0x00000003)<<20)
#define MCF_FBCS_CSCW_SWSEN	(0x00800000)
#define MCF_FBCS_CSCW_SWS(x)	(((x)&0x0000003F)<<26)
#define MCF_FBCS_CSCW_PS_8	(0x0040)
#define MCF_FBCS_CSCW_PS_16	(0x0080)
#define MCF_FBCS_CSCW_PS_32	(0x0000)

/*********************************************************************
 *
 * Genewaw Puwpose I/O (GPIO)
 *
 *********************************************************************/

/* Wegistew wead/wwite macwos */
#define MCFGPIO_PODW_FECH		(0xFC0A4000)
#define MCFGPIO_PODW_FECW		(0xFC0A4001)
#define MCFGPIO_PODW_SSI		(0xFC0A4002)
#define MCFGPIO_PODW_BUSCTW		(0xFC0A4003)
#define MCFGPIO_PODW_BE			(0xFC0A4004)
#define MCFGPIO_PODW_CS			(0xFC0A4005)
#define MCFGPIO_PODW_PWM		(0xFC0A4006)
#define MCFGPIO_PODW_FECI2C		(0xFC0A4007)
#define MCFGPIO_PODW_UAWT		(0xFC0A4009)
#define MCFGPIO_PODW_QSPI		(0xFC0A400A)
#define MCFGPIO_PODW_TIMEW		(0xFC0A400B)
#define MCFGPIO_PODW_WCDDATAH		(0xFC0A400D)
#define MCFGPIO_PODW_WCDDATAM		(0xFC0A400E)
#define MCFGPIO_PODW_WCDDATAW		(0xFC0A400F)
#define MCFGPIO_PODW_WCDCTWH		(0xFC0A4010)
#define MCFGPIO_PODW_WCDCTWW		(0xFC0A4011)
#define MCFGPIO_PDDW_FECH		(0xFC0A4014)
#define MCFGPIO_PDDW_FECW		(0xFC0A4015)
#define MCFGPIO_PDDW_SSI		(0xFC0A4016)
#define MCFGPIO_PDDW_BUSCTW		(0xFC0A4017)
#define MCFGPIO_PDDW_BE			(0xFC0A4018)
#define MCFGPIO_PDDW_CS			(0xFC0A4019)
#define MCFGPIO_PDDW_PWM		(0xFC0A401A)
#define MCFGPIO_PDDW_FECI2C		(0xFC0A401B)
#define MCFGPIO_PDDW_UAWT		(0xFC0A401C)
#define MCFGPIO_PDDW_QSPI		(0xFC0A401E)
#define MCFGPIO_PDDW_TIMEW		(0xFC0A401F)
#define MCFGPIO_PDDW_WCDDATAH		(0xFC0A4021)
#define MCFGPIO_PDDW_WCDDATAM		(0xFC0A4022)
#define MCFGPIO_PDDW_WCDDATAW		(0xFC0A4023)
#define MCFGPIO_PDDW_WCDCTWH		(0xFC0A4024)
#define MCFGPIO_PDDW_WCDCTWW		(0xFC0A4025)
#define MCFGPIO_PPDSDW_FECH		(0xFC0A4028)
#define MCFGPIO_PPDSDW_FECW		(0xFC0A4029)
#define MCFGPIO_PPDSDW_SSI		(0xFC0A402A)
#define MCFGPIO_PPDSDW_BUSCTW		(0xFC0A402B)
#define MCFGPIO_PPDSDW_BE		(0xFC0A402C)
#define MCFGPIO_PPDSDW_CS		(0xFC0A402D)
#define MCFGPIO_PPDSDW_PWM		(0xFC0A402E)
#define MCFGPIO_PPDSDW_FECI2C		(0xFC0A402F)
#define MCFGPIO_PPDSDW_UAWT		(0xFC0A4031)
#define MCFGPIO_PPDSDW_QSPI		(0xFC0A4032)
#define MCFGPIO_PPDSDW_TIMEW		(0xFC0A4033)
#define MCFGPIO_PPDSDW_WCDDATAH		(0xFC0A4035)
#define MCFGPIO_PPDSDW_WCDDATAM		(0xFC0A4036)
#define MCFGPIO_PPDSDW_WCDDATAW		(0xFC0A4037)
#define MCFGPIO_PPDSDW_WCDCTWH		(0xFC0A4038)
#define MCFGPIO_PPDSDW_WCDCTWW		(0xFC0A4039)
#define MCFGPIO_PCWWW_FECH		(0xFC0A403C)
#define MCFGPIO_PCWWW_FECW		(0xFC0A403D)
#define MCFGPIO_PCWWW_SSI		(0xFC0A403E)
#define MCFGPIO_PCWWW_BUSCTW		(0xFC0A403F)
#define MCFGPIO_PCWWW_BE		(0xFC0A4040)
#define MCFGPIO_PCWWW_CS		(0xFC0A4041)
#define MCFGPIO_PCWWW_PWM		(0xFC0A4042)
#define MCFGPIO_PCWWW_FECI2C		(0xFC0A4043)
#define MCFGPIO_PCWWW_UAWT		(0xFC0A4045)
#define MCFGPIO_PCWWW_QSPI		(0xFC0A4046)
#define MCFGPIO_PCWWW_TIMEW		(0xFC0A4047)
#define MCFGPIO_PCWWW_WCDDATAH		(0xFC0A4049)
#define MCFGPIO_PCWWW_WCDDATAM		(0xFC0A404A)
#define MCFGPIO_PCWWW_WCDDATAW		(0xFC0A404B)
#define MCFGPIO_PCWWW_WCDCTWH		(0xFC0A404C)
#define MCFGPIO_PCWWW_WCDCTWW		(0xFC0A404D)
#define MCFGPIO_PAW_FEC			(0xFC0A4050)
#define MCFGPIO_PAW_PWM			(0xFC0A4051)
#define MCFGPIO_PAW_BUSCTW		(0xFC0A4052)
#define MCFGPIO_PAW_FECI2C		(0xFC0A4053)
#define MCFGPIO_PAW_BE			(0xFC0A4054)
#define MCFGPIO_PAW_CS			(0xFC0A4055)
#define MCFGPIO_PAW_SSI			(0xFC0A4056)
#define MCFGPIO_PAW_UAWT		(0xFC0A4058)
#define MCFGPIO_PAW_QSPI		(0xFC0A405A)
#define MCFGPIO_PAW_TIMEW		(0xFC0A405C)
#define MCFGPIO_PAW_WCDDATA		(0xFC0A405D)
#define MCFGPIO_PAW_WCDCTW		(0xFC0A405E)
#define MCFGPIO_PAW_IWQ			(0xFC0A4060)
#define MCFGPIO_MSCW_FWEXBUS		(0xFC0A4064)
#define MCFGPIO_MSCW_SDWAM		(0xFC0A4065)
#define MCFGPIO_DSCW_I2C		(0xFC0A4068)
#define MCFGPIO_DSCW_PWM		(0xFC0A4069)
#define MCFGPIO_DSCW_FEC		(0xFC0A406A)
#define MCFGPIO_DSCW_UAWT		(0xFC0A406B)
#define MCFGPIO_DSCW_QSPI		(0xFC0A406C)
#define MCFGPIO_DSCW_TIMEW		(0xFC0A406D)
#define MCFGPIO_DSCW_SSI		(0xFC0A406E)
#define MCFGPIO_DSCW_WCD		(0xFC0A406F)
#define MCFGPIO_DSCW_DEBUG		(0xFC0A4070)
#define MCFGPIO_DSCW_CWKWST		(0xFC0A4071)
#define MCFGPIO_DSCW_IWQ		(0xFC0A4072)

/* Bit definitions and macwos fow MCF_GPIO_PODW_FECH */
#define MCF_GPIO_PODW_FECH_PODW_FECH0              (0x01)
#define MCF_GPIO_PODW_FECH_PODW_FECH1              (0x02)
#define MCF_GPIO_PODW_FECH_PODW_FECH2              (0x04)
#define MCF_GPIO_PODW_FECH_PODW_FECH3              (0x08)
#define MCF_GPIO_PODW_FECH_PODW_FECH4              (0x10)
#define MCF_GPIO_PODW_FECH_PODW_FECH5              (0x20)
#define MCF_GPIO_PODW_FECH_PODW_FECH6              (0x40)
#define MCF_GPIO_PODW_FECH_PODW_FECH7              (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PODW_FECW */
#define MCF_GPIO_PODW_FECW_PODW_FECW0              (0x01)
#define MCF_GPIO_PODW_FECW_PODW_FECW1              (0x02)
#define MCF_GPIO_PODW_FECW_PODW_FECW2              (0x04)
#define MCF_GPIO_PODW_FECW_PODW_FECW3              (0x08)
#define MCF_GPIO_PODW_FECW_PODW_FECW4              (0x10)
#define MCF_GPIO_PODW_FECW_PODW_FECW5              (0x20)
#define MCF_GPIO_PODW_FECW_PODW_FECW6              (0x40)
#define MCF_GPIO_PODW_FECW_PODW_FECW7              (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PODW_SSI */
#define MCF_GPIO_PODW_SSI_PODW_SSI0                (0x01)
#define MCF_GPIO_PODW_SSI_PODW_SSI1                (0x02)
#define MCF_GPIO_PODW_SSI_PODW_SSI2                (0x04)
#define MCF_GPIO_PODW_SSI_PODW_SSI3                (0x08)
#define MCF_GPIO_PODW_SSI_PODW_SSI4                (0x10)

/* Bit definitions and macwos fow MCF_GPIO_PODW_BUSCTW */
#define MCF_GPIO_PODW_BUSCTW_POSDW_BUSCTW0         (0x01)
#define MCF_GPIO_PODW_BUSCTW_PODW_BUSCTW1          (0x02)
#define MCF_GPIO_PODW_BUSCTW_PODW_BUSCTW2          (0x04)
#define MCF_GPIO_PODW_BUSCTW_PODW_BUSCTW3          (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PODW_BE */
#define MCF_GPIO_PODW_BE_PODW_BE0                  (0x01)
#define MCF_GPIO_PODW_BE_PODW_BE1                  (0x02)
#define MCF_GPIO_PODW_BE_PODW_BE2                  (0x04)
#define MCF_GPIO_PODW_BE_PODW_BE3                  (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PODW_CS */
#define MCF_GPIO_PODW_CS_PODW_CS1                  (0x02)
#define MCF_GPIO_PODW_CS_PODW_CS2                  (0x04)
#define MCF_GPIO_PODW_CS_PODW_CS3                  (0x08)
#define MCF_GPIO_PODW_CS_PODW_CS4                  (0x10)
#define MCF_GPIO_PODW_CS_PODW_CS5                  (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PODW_PWM */
#define MCF_GPIO_PODW_PWM_PODW_PWM2                (0x04)
#define MCF_GPIO_PODW_PWM_PODW_PWM3                (0x08)
#define MCF_GPIO_PODW_PWM_PODW_PWM4                (0x10)
#define MCF_GPIO_PODW_PWM_PODW_PWM5                (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PODW_FECI2C */
#define MCF_GPIO_PODW_FECI2C_PODW_FECI2C0          (0x01)
#define MCF_GPIO_PODW_FECI2C_PODW_FECI2C1          (0x02)
#define MCF_GPIO_PODW_FECI2C_PODW_FECI2C2          (0x04)
#define MCF_GPIO_PODW_FECI2C_PODW_FECI2C3          (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PODW_UAWT */
#define MCF_GPIO_PODW_UAWT_PODW_UAWT0              (0x01)
#define MCF_GPIO_PODW_UAWT_PODW_UAWT1              (0x02)
#define MCF_GPIO_PODW_UAWT_PODW_UAWT2              (0x04)
#define MCF_GPIO_PODW_UAWT_PODW_UAWT3              (0x08)
#define MCF_GPIO_PODW_UAWT_PODW_UAWT4              (0x10)
#define MCF_GPIO_PODW_UAWT_PODW_UAWT5              (0x20)
#define MCF_GPIO_PODW_UAWT_PODW_UAWT6              (0x40)
#define MCF_GPIO_PODW_UAWT_PODW_UAWT7              (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PODW_QSPI */
#define MCF_GPIO_PODW_QSPI_PODW_QSPI0              (0x01)
#define MCF_GPIO_PODW_QSPI_PODW_QSPI1              (0x02)
#define MCF_GPIO_PODW_QSPI_PODW_QSPI2              (0x04)
#define MCF_GPIO_PODW_QSPI_PODW_QSPI3              (0x08)
#define MCF_GPIO_PODW_QSPI_PODW_QSPI4              (0x10)
#define MCF_GPIO_PODW_QSPI_PODW_QSPI5              (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PODW_TIMEW */
#define MCF_GPIO_PODW_TIMEW_PODW_TIMEW0            (0x01)
#define MCF_GPIO_PODW_TIMEW_PODW_TIMEW1            (0x02)
#define MCF_GPIO_PODW_TIMEW_PODW_TIMEW2            (0x04)
#define MCF_GPIO_PODW_TIMEW_PODW_TIMEW3            (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PODW_WCDDATAH */
#define MCF_GPIO_PODW_WCDDATAH_PODW_WCDDATAH0      (0x01)
#define MCF_GPIO_PODW_WCDDATAH_PODW_WCDDATAH1      (0x02)

/* Bit definitions and macwos fow MCF_GPIO_PODW_WCDDATAM */
#define MCF_GPIO_PODW_WCDDATAM_PODW_WCDDATAM0      (0x01)
#define MCF_GPIO_PODW_WCDDATAM_PODW_WCDDATAM1      (0x02)
#define MCF_GPIO_PODW_WCDDATAM_PODW_WCDDATAM2      (0x04)
#define MCF_GPIO_PODW_WCDDATAM_PODW_WCDDATAM3      (0x08)
#define MCF_GPIO_PODW_WCDDATAM_PODW_WCDDATAM4      (0x10)
#define MCF_GPIO_PODW_WCDDATAM_PODW_WCDDATAM5      (0x20)
#define MCF_GPIO_PODW_WCDDATAM_PODW_WCDDATAM6      (0x40)
#define MCF_GPIO_PODW_WCDDATAM_PODW_WCDDATAM7      (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PODW_WCDDATAW */
#define MCF_GPIO_PODW_WCDDATAW_PODW_WCDDATAW0      (0x01)
#define MCF_GPIO_PODW_WCDDATAW_PODW_WCDDATAW1      (0x02)
#define MCF_GPIO_PODW_WCDDATAW_PODW_WCDDATAW2      (0x04)
#define MCF_GPIO_PODW_WCDDATAW_PODW_WCDDATAW3      (0x08)
#define MCF_GPIO_PODW_WCDDATAW_PODW_WCDDATAW4      (0x10)
#define MCF_GPIO_PODW_WCDDATAW_PODW_WCDDATAW5      (0x20)
#define MCF_GPIO_PODW_WCDDATAW_PODW_WCDDATAW6      (0x40)
#define MCF_GPIO_PODW_WCDDATAW_PODW_WCDDATAW7      (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PODW_WCDCTWH */
#define MCF_GPIO_PODW_WCDCTWH_PODW_WCDCTWH0        (0x01)

/* Bit definitions and macwos fow MCF_GPIO_PODW_WCDCTWW */
#define MCF_GPIO_PODW_WCDCTWW_PODW_WCDCTWW0        (0x01)
#define MCF_GPIO_PODW_WCDCTWW_PODW_WCDCTWW1        (0x02)
#define MCF_GPIO_PODW_WCDCTWW_PODW_WCDCTWW2        (0x04)
#define MCF_GPIO_PODW_WCDCTWW_PODW_WCDCTWW3        (0x08)
#define MCF_GPIO_PODW_WCDCTWW_PODW_WCDCTWW4        (0x10)
#define MCF_GPIO_PODW_WCDCTWW_PODW_WCDCTWW5        (0x20)
#define MCF_GPIO_PODW_WCDCTWW_PODW_WCDCTWW6        (0x40)
#define MCF_GPIO_PODW_WCDCTWW_PODW_WCDCTWW7        (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_FECH */
#define MCF_GPIO_PDDW_FECH_PDDW_FECH0              (0x01)
#define MCF_GPIO_PDDW_FECH_PDDW_FECH1              (0x02)
#define MCF_GPIO_PDDW_FECH_PDDW_FECH2              (0x04)
#define MCF_GPIO_PDDW_FECH_PDDW_FECH3              (0x08)
#define MCF_GPIO_PDDW_FECH_PDDW_FECH4              (0x10)
#define MCF_GPIO_PDDW_FECH_PDDW_FECH5              (0x20)
#define MCF_GPIO_PDDW_FECH_PDDW_FECH6              (0x40)
#define MCF_GPIO_PDDW_FECH_PDDW_FECH7              (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_FECW */
#define MCF_GPIO_PDDW_FECW_PDDW_FECW0              (0x01)
#define MCF_GPIO_PDDW_FECW_PDDW_FECW1              (0x02)
#define MCF_GPIO_PDDW_FECW_PDDW_FECW2              (0x04)
#define MCF_GPIO_PDDW_FECW_PDDW_FECW3              (0x08)
#define MCF_GPIO_PDDW_FECW_PDDW_FECW4              (0x10)
#define MCF_GPIO_PDDW_FECW_PDDW_FECW5              (0x20)
#define MCF_GPIO_PDDW_FECW_PDDW_FECW6              (0x40)
#define MCF_GPIO_PDDW_FECW_PDDW_FECW7              (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_SSI */
#define MCF_GPIO_PDDW_SSI_PDDW_SSI0                (0x01)
#define MCF_GPIO_PDDW_SSI_PDDW_SSI1                (0x02)
#define MCF_GPIO_PDDW_SSI_PDDW_SSI2                (0x04)
#define MCF_GPIO_PDDW_SSI_PDDW_SSI3                (0x08)
#define MCF_GPIO_PDDW_SSI_PDDW_SSI4                (0x10)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_BUSCTW */
#define MCF_GPIO_PDDW_BUSCTW_POSDW_BUSCTW0         (0x01)
#define MCF_GPIO_PDDW_BUSCTW_PDDW_BUSCTW1          (0x02)
#define MCF_GPIO_PDDW_BUSCTW_PDDW_BUSCTW2          (0x04)
#define MCF_GPIO_PDDW_BUSCTW_PDDW_BUSCTW3          (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_BE */
#define MCF_GPIO_PDDW_BE_PDDW_BE0                  (0x01)
#define MCF_GPIO_PDDW_BE_PDDW_BE1                  (0x02)
#define MCF_GPIO_PDDW_BE_PDDW_BE2                  (0x04)
#define MCF_GPIO_PDDW_BE_PDDW_BE3                  (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_CS */
#define MCF_GPIO_PDDW_CS_PDDW_CS1                  (0x02)
#define MCF_GPIO_PDDW_CS_PDDW_CS2                  (0x04)
#define MCF_GPIO_PDDW_CS_PDDW_CS3                  (0x08)
#define MCF_GPIO_PDDW_CS_PDDW_CS4                  (0x10)
#define MCF_GPIO_PDDW_CS_PDDW_CS5                  (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_PWM */
#define MCF_GPIO_PDDW_PWM_PDDW_PWM2                (0x04)
#define MCF_GPIO_PDDW_PWM_PDDW_PWM3                (0x08)
#define MCF_GPIO_PDDW_PWM_PDDW_PWM4                (0x10)
#define MCF_GPIO_PDDW_PWM_PDDW_PWM5                (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_FECI2C */
#define MCF_GPIO_PDDW_FECI2C_PDDW_FECI2C0          (0x01)
#define MCF_GPIO_PDDW_FECI2C_PDDW_FECI2C1          (0x02)
#define MCF_GPIO_PDDW_FECI2C_PDDW_FECI2C2          (0x04)
#define MCF_GPIO_PDDW_FECI2C_PDDW_FECI2C3          (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_UAWT */
#define MCF_GPIO_PDDW_UAWT_PDDW_UAWT0              (0x01)
#define MCF_GPIO_PDDW_UAWT_PDDW_UAWT1              (0x02)
#define MCF_GPIO_PDDW_UAWT_PDDW_UAWT2              (0x04)
#define MCF_GPIO_PDDW_UAWT_PDDW_UAWT3              (0x08)
#define MCF_GPIO_PDDW_UAWT_PDDW_UAWT4              (0x10)
#define MCF_GPIO_PDDW_UAWT_PDDW_UAWT5              (0x20)
#define MCF_GPIO_PDDW_UAWT_PDDW_UAWT6              (0x40)
#define MCF_GPIO_PDDW_UAWT_PDDW_UAWT7              (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_QSPI */
#define MCF_GPIO_PDDW_QSPI_PDDW_QSPI0              (0x01)
#define MCF_GPIO_PDDW_QSPI_PDDW_QSPI1              (0x02)
#define MCF_GPIO_PDDW_QSPI_PDDW_QSPI2              (0x04)
#define MCF_GPIO_PDDW_QSPI_PDDW_QSPI3              (0x08)
#define MCF_GPIO_PDDW_QSPI_PDDW_QSPI4              (0x10)
#define MCF_GPIO_PDDW_QSPI_PDDW_QSPI5              (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_TIMEW */
#define MCF_GPIO_PDDW_TIMEW_PDDW_TIMEW0            (0x01)
#define MCF_GPIO_PDDW_TIMEW_PDDW_TIMEW1            (0x02)
#define MCF_GPIO_PDDW_TIMEW_PDDW_TIMEW2            (0x04)
#define MCF_GPIO_PDDW_TIMEW_PDDW_TIMEW3            (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_WCDDATAH */
#define MCF_GPIO_PDDW_WCDDATAH_PDDW_WCDDATAH0      (0x01)
#define MCF_GPIO_PDDW_WCDDATAH_PDDW_WCDDATAH1      (0x02)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_WCDDATAM */
#define MCF_GPIO_PDDW_WCDDATAM_PDDW_WCDDATAM0      (0x01)
#define MCF_GPIO_PDDW_WCDDATAM_PDDW_WCDDATAM1      (0x02)
#define MCF_GPIO_PDDW_WCDDATAM_PDDW_WCDDATAM2      (0x04)
#define MCF_GPIO_PDDW_WCDDATAM_PDDW_WCDDATAM3      (0x08)
#define MCF_GPIO_PDDW_WCDDATAM_PDDW_WCDDATAM4      (0x10)
#define MCF_GPIO_PDDW_WCDDATAM_PDDW_WCDDATAM5      (0x20)
#define MCF_GPIO_PDDW_WCDDATAM_PDDW_WCDDATAM6      (0x40)
#define MCF_GPIO_PDDW_WCDDATAM_PDDW_WCDDATAM7      (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_WCDDATAW */
#define MCF_GPIO_PDDW_WCDDATAW_PDDW_WCDDATAW0      (0x01)
#define MCF_GPIO_PDDW_WCDDATAW_PDDW_WCDDATAW1      (0x02)
#define MCF_GPIO_PDDW_WCDDATAW_PDDW_WCDDATAW2      (0x04)
#define MCF_GPIO_PDDW_WCDDATAW_PDDW_WCDDATAW3      (0x08)
#define MCF_GPIO_PDDW_WCDDATAW_PDDW_WCDDATAW4      (0x10)
#define MCF_GPIO_PDDW_WCDDATAW_PDDW_WCDDATAW5      (0x20)
#define MCF_GPIO_PDDW_WCDDATAW_PDDW_WCDDATAW6      (0x40)
#define MCF_GPIO_PDDW_WCDDATAW_PDDW_WCDDATAW7      (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_WCDCTWH */
#define MCF_GPIO_PDDW_WCDCTWH_PDDW_WCDCTWH0        (0x01)

/* Bit definitions and macwos fow MCF_GPIO_PDDW_WCDCTWW */
#define MCF_GPIO_PDDW_WCDCTWW_PDDW_WCDCTWW0        (0x01)
#define MCF_GPIO_PDDW_WCDCTWW_PDDW_WCDCTWW1        (0x02)
#define MCF_GPIO_PDDW_WCDCTWW_PDDW_WCDCTWW2        (0x04)
#define MCF_GPIO_PDDW_WCDCTWW_PDDW_WCDCTWW3        (0x08)
#define MCF_GPIO_PDDW_WCDCTWW_PDDW_WCDCTWW4        (0x10)
#define MCF_GPIO_PDDW_WCDCTWW_PDDW_WCDCTWW5        (0x20)
#define MCF_GPIO_PDDW_WCDCTWW_PDDW_WCDCTWW6        (0x40)
#define MCF_GPIO_PDDW_WCDCTWW_PDDW_WCDCTWW7        (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_FECH */
#define MCF_GPIO_PPDSDW_FECH_PPDSDW_FECH0          (0x01)
#define MCF_GPIO_PPDSDW_FECH_PPDSDW_FECH1          (0x02)
#define MCF_GPIO_PPDSDW_FECH_PPDSDW_FECH2          (0x04)
#define MCF_GPIO_PPDSDW_FECH_PPDSDW_FECH3          (0x08)
#define MCF_GPIO_PPDSDW_FECH_PPDSDW_FECH4          (0x10)
#define MCF_GPIO_PPDSDW_FECH_PPDSDW_FECH5          (0x20)
#define MCF_GPIO_PPDSDW_FECH_PPDSDW_FECH6          (0x40)
#define MCF_GPIO_PPDSDW_FECH_PPDSDW_FECH7          (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_FECW */
#define MCF_GPIO_PPDSDW_FECW_PPDSDW_FECW0          (0x01)
#define MCF_GPIO_PPDSDW_FECW_PPDSDW_FECW1          (0x02)
#define MCF_GPIO_PPDSDW_FECW_PPDSDW_FECW2          (0x04)
#define MCF_GPIO_PPDSDW_FECW_PPDSDW_FECW3          (0x08)
#define MCF_GPIO_PPDSDW_FECW_PPDSDW_FECW4          (0x10)
#define MCF_GPIO_PPDSDW_FECW_PPDSDW_FECW5          (0x20)
#define MCF_GPIO_PPDSDW_FECW_PPDSDW_FECW6          (0x40)
#define MCF_GPIO_PPDSDW_FECW_PPDSDW_FECW7          (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_SSI */
#define MCF_GPIO_PPDSDW_SSI_PPDSDW_SSI0            (0x01)
#define MCF_GPIO_PPDSDW_SSI_PPDSDW_SSI1            (0x02)
#define MCF_GPIO_PPDSDW_SSI_PPDSDW_SSI2            (0x04)
#define MCF_GPIO_PPDSDW_SSI_PPDSDW_SSI3            (0x08)
#define MCF_GPIO_PPDSDW_SSI_PPDSDW_SSI4            (0x10)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_BUSCTW */
#define MCF_GPIO_PPDSDW_BUSCTW_POSDW_BUSCTW0       (0x01)
#define MCF_GPIO_PPDSDW_BUSCTW_PPDSDW_BUSCTW1      (0x02)
#define MCF_GPIO_PPDSDW_BUSCTW_PPDSDW_BUSCTW2      (0x04)
#define MCF_GPIO_PPDSDW_BUSCTW_PPDSDW_BUSCTW3      (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_BE */
#define MCF_GPIO_PPDSDW_BE_PPDSDW_BE0              (0x01)
#define MCF_GPIO_PPDSDW_BE_PPDSDW_BE1              (0x02)
#define MCF_GPIO_PPDSDW_BE_PPDSDW_BE2              (0x04)
#define MCF_GPIO_PPDSDW_BE_PPDSDW_BE3              (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_CS */
#define MCF_GPIO_PPDSDW_CS_PPDSDW_CS1              (0x02)
#define MCF_GPIO_PPDSDW_CS_PPDSDW_CS2              (0x04)
#define MCF_GPIO_PPDSDW_CS_PPDSDW_CS3              (0x08)
#define MCF_GPIO_PPDSDW_CS_PPDSDW_CS4              (0x10)
#define MCF_GPIO_PPDSDW_CS_PPDSDW_CS5              (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_PWM */
#define MCF_GPIO_PPDSDW_PWM_PPDSDW_PWM2            (0x04)
#define MCF_GPIO_PPDSDW_PWM_PPDSDW_PWM3            (0x08)
#define MCF_GPIO_PPDSDW_PWM_PPDSDW_PWM4            (0x10)
#define MCF_GPIO_PPDSDW_PWM_PPDSDW_PWM5            (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_FECI2C */
#define MCF_GPIO_PPDSDW_FECI2C_PPDSDW_FECI2C0      (0x01)
#define MCF_GPIO_PPDSDW_FECI2C_PPDSDW_FECI2C1      (0x02)
#define MCF_GPIO_PPDSDW_FECI2C_PPDSDW_FECI2C2      (0x04)
#define MCF_GPIO_PPDSDW_FECI2C_PPDSDW_FECI2C3      (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_UAWT */
#define MCF_GPIO_PPDSDW_UAWT_PPDSDW_UAWT0          (0x01)
#define MCF_GPIO_PPDSDW_UAWT_PPDSDW_UAWT1          (0x02)
#define MCF_GPIO_PPDSDW_UAWT_PPDSDW_UAWT2          (0x04)
#define MCF_GPIO_PPDSDW_UAWT_PPDSDW_UAWT3          (0x08)
#define MCF_GPIO_PPDSDW_UAWT_PPDSDW_UAWT4          (0x10)
#define MCF_GPIO_PPDSDW_UAWT_PPDSDW_UAWT5          (0x20)
#define MCF_GPIO_PPDSDW_UAWT_PPDSDW_UAWT6          (0x40)
#define MCF_GPIO_PPDSDW_UAWT_PPDSDW_UAWT7          (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_QSPI */
#define MCF_GPIO_PPDSDW_QSPI_PPDSDW_QSPI0          (0x01)
#define MCF_GPIO_PPDSDW_QSPI_PPDSDW_QSPI1          (0x02)
#define MCF_GPIO_PPDSDW_QSPI_PPDSDW_QSPI2          (0x04)
#define MCF_GPIO_PPDSDW_QSPI_PPDSDW_QSPI3          (0x08)
#define MCF_GPIO_PPDSDW_QSPI_PPDSDW_QSPI4          (0x10)
#define MCF_GPIO_PPDSDW_QSPI_PPDSDW_QSPI5          (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_TIMEW */
#define MCF_GPIO_PPDSDW_TIMEW_PPDSDW_TIMEW0        (0x01)
#define MCF_GPIO_PPDSDW_TIMEW_PPDSDW_TIMEW1        (0x02)
#define MCF_GPIO_PPDSDW_TIMEW_PPDSDW_TIMEW2        (0x04)
#define MCF_GPIO_PPDSDW_TIMEW_PPDSDW_TIMEW3        (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_WCDDATAH */
#define MCF_GPIO_PPDSDW_WCDDATAH_PPDSDW_WCDDATAH0  (0x01)
#define MCF_GPIO_PPDSDW_WCDDATAH_PPDSDW_WCDDATAH1  (0x02)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_WCDDATAM */
#define MCF_GPIO_PPDSDW_WCDDATAM_PPDSDW_WCDDATAM0  (0x01)
#define MCF_GPIO_PPDSDW_WCDDATAM_PPDSDW_WCDDATAM1  (0x02)
#define MCF_GPIO_PPDSDW_WCDDATAM_PPDSDW_WCDDATAM2  (0x04)
#define MCF_GPIO_PPDSDW_WCDDATAM_PPDSDW_WCDDATAM3  (0x08)
#define MCF_GPIO_PPDSDW_WCDDATAM_PPDSDW_WCDDATAM4  (0x10)
#define MCF_GPIO_PPDSDW_WCDDATAM_PPDSDW_WCDDATAM5  (0x20)
#define MCF_GPIO_PPDSDW_WCDDATAM_PPDSDW_WCDDATAM6  (0x40)
#define MCF_GPIO_PPDSDW_WCDDATAM_PPDSDW_WCDDATAM7  (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_WCDDATAW */
#define MCF_GPIO_PPDSDW_WCDDATAW_PPDSDW_WCDDATAW0  (0x01)
#define MCF_GPIO_PPDSDW_WCDDATAW_PPDSDW_WCDDATAW1  (0x02)
#define MCF_GPIO_PPDSDW_WCDDATAW_PPDSDW_WCDDATAW2  (0x04)
#define MCF_GPIO_PPDSDW_WCDDATAW_PPDSDW_WCDDATAW3  (0x08)
#define MCF_GPIO_PPDSDW_WCDDATAW_PPDSDW_WCDDATAW4  (0x10)
#define MCF_GPIO_PPDSDW_WCDDATAW_PPDSDW_WCDDATAW5  (0x20)
#define MCF_GPIO_PPDSDW_WCDDATAW_PPDSDW_WCDDATAW6  (0x40)
#define MCF_GPIO_PPDSDW_WCDDATAW_PPDSDW_WCDDATAW7  (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_WCDCTWH */
#define MCF_GPIO_PPDSDW_WCDCTWH_PPDSDW_WCDCTWH0    (0x01)

/* Bit definitions and macwos fow MCF_GPIO_PPDSDW_WCDCTWW */
#define MCF_GPIO_PPDSDW_WCDCTWW_PPDSDW_WCDCTWW0    (0x01)
#define MCF_GPIO_PPDSDW_WCDCTWW_PPDSDW_WCDCTWW1    (0x02)
#define MCF_GPIO_PPDSDW_WCDCTWW_PPDSDW_WCDCTWW2    (0x04)
#define MCF_GPIO_PPDSDW_WCDCTWW_PPDSDW_WCDCTWW3    (0x08)
#define MCF_GPIO_PPDSDW_WCDCTWW_PPDSDW_WCDCTWW4    (0x10)
#define MCF_GPIO_PPDSDW_WCDCTWW_PPDSDW_WCDCTWW5    (0x20)
#define MCF_GPIO_PPDSDW_WCDCTWW_PPDSDW_WCDCTWW6    (0x40)
#define MCF_GPIO_PPDSDW_WCDCTWW_PPDSDW_WCDCTWW7    (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_FECH */
#define MCF_GPIO_PCWWW_FECH_PCWWW_FECH0            (0x01)
#define MCF_GPIO_PCWWW_FECH_PCWWW_FECH1            (0x02)
#define MCF_GPIO_PCWWW_FECH_PCWWW_FECH2            (0x04)
#define MCF_GPIO_PCWWW_FECH_PCWWW_FECH3            (0x08)
#define MCF_GPIO_PCWWW_FECH_PCWWW_FECH4            (0x10)
#define MCF_GPIO_PCWWW_FECH_PCWWW_FECH5            (0x20)
#define MCF_GPIO_PCWWW_FECH_PCWWW_FECH6            (0x40)
#define MCF_GPIO_PCWWW_FECH_PCWWW_FECH7            (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_FECW */
#define MCF_GPIO_PCWWW_FECW_PCWWW_FECW0            (0x01)
#define MCF_GPIO_PCWWW_FECW_PCWWW_FECW1            (0x02)
#define MCF_GPIO_PCWWW_FECW_PCWWW_FECW2            (0x04)
#define MCF_GPIO_PCWWW_FECW_PCWWW_FECW3            (0x08)
#define MCF_GPIO_PCWWW_FECW_PCWWW_FECW4            (0x10)
#define MCF_GPIO_PCWWW_FECW_PCWWW_FECW5            (0x20)
#define MCF_GPIO_PCWWW_FECW_PCWWW_FECW6            (0x40)
#define MCF_GPIO_PCWWW_FECW_PCWWW_FECW7            (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_SSI */
#define MCF_GPIO_PCWWW_SSI_PCWWW_SSI0              (0x01)
#define MCF_GPIO_PCWWW_SSI_PCWWW_SSI1              (0x02)
#define MCF_GPIO_PCWWW_SSI_PCWWW_SSI2              (0x04)
#define MCF_GPIO_PCWWW_SSI_PCWWW_SSI3              (0x08)
#define MCF_GPIO_PCWWW_SSI_PCWWW_SSI4              (0x10)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_BUSCTW */
#define MCF_GPIO_PCWWW_BUSCTW_POSDW_BUSCTW0        (0x01)
#define MCF_GPIO_PCWWW_BUSCTW_PCWWW_BUSCTW1        (0x02)
#define MCF_GPIO_PCWWW_BUSCTW_PCWWW_BUSCTW2        (0x04)
#define MCF_GPIO_PCWWW_BUSCTW_PCWWW_BUSCTW3        (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_BE */
#define MCF_GPIO_PCWWW_BE_PCWWW_BE0                (0x01)
#define MCF_GPIO_PCWWW_BE_PCWWW_BE1                (0x02)
#define MCF_GPIO_PCWWW_BE_PCWWW_BE2                (0x04)
#define MCF_GPIO_PCWWW_BE_PCWWW_BE3                (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_CS */
#define MCF_GPIO_PCWWW_CS_PCWWW_CS1                (0x02)
#define MCF_GPIO_PCWWW_CS_PCWWW_CS2                (0x04)
#define MCF_GPIO_PCWWW_CS_PCWWW_CS3                (0x08)
#define MCF_GPIO_PCWWW_CS_PCWWW_CS4                (0x10)
#define MCF_GPIO_PCWWW_CS_PCWWW_CS5                (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_PWM */
#define MCF_GPIO_PCWWW_PWM_PCWWW_PWM2              (0x04)
#define MCF_GPIO_PCWWW_PWM_PCWWW_PWM3              (0x08)
#define MCF_GPIO_PCWWW_PWM_PCWWW_PWM4              (0x10)
#define MCF_GPIO_PCWWW_PWM_PCWWW_PWM5              (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_FECI2C */
#define MCF_GPIO_PCWWW_FECI2C_PCWWW_FECI2C0        (0x01)
#define MCF_GPIO_PCWWW_FECI2C_PCWWW_FECI2C1        (0x02)
#define MCF_GPIO_PCWWW_FECI2C_PCWWW_FECI2C2        (0x04)
#define MCF_GPIO_PCWWW_FECI2C_PCWWW_FECI2C3        (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_UAWT */
#define MCF_GPIO_PCWWW_UAWT_PCWWW_UAWT0            (0x01)
#define MCF_GPIO_PCWWW_UAWT_PCWWW_UAWT1            (0x02)
#define MCF_GPIO_PCWWW_UAWT_PCWWW_UAWT2            (0x04)
#define MCF_GPIO_PCWWW_UAWT_PCWWW_UAWT3            (0x08)
#define MCF_GPIO_PCWWW_UAWT_PCWWW_UAWT4            (0x10)
#define MCF_GPIO_PCWWW_UAWT_PCWWW_UAWT5            (0x20)
#define MCF_GPIO_PCWWW_UAWT_PCWWW_UAWT6            (0x40)
#define MCF_GPIO_PCWWW_UAWT_PCWWW_UAWT7            (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_QSPI */
#define MCF_GPIO_PCWWW_QSPI_PCWWW_QSPI0            (0x01)
#define MCF_GPIO_PCWWW_QSPI_PCWWW_QSPI1            (0x02)
#define MCF_GPIO_PCWWW_QSPI_PCWWW_QSPI2            (0x04)
#define MCF_GPIO_PCWWW_QSPI_PCWWW_QSPI3            (0x08)
#define MCF_GPIO_PCWWW_QSPI_PCWWW_QSPI4            (0x10)
#define MCF_GPIO_PCWWW_QSPI_PCWWW_QSPI5            (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_TIMEW */
#define MCF_GPIO_PCWWW_TIMEW_PCWWW_TIMEW0          (0x01)
#define MCF_GPIO_PCWWW_TIMEW_PCWWW_TIMEW1          (0x02)
#define MCF_GPIO_PCWWW_TIMEW_PCWWW_TIMEW2          (0x04)
#define MCF_GPIO_PCWWW_TIMEW_PCWWW_TIMEW3          (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_WCDDATAH */
#define MCF_GPIO_PCWWW_WCDDATAH_PCWWW_WCDDATAH0    (0x01)
#define MCF_GPIO_PCWWW_WCDDATAH_PCWWW_WCDDATAH1    (0x02)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_WCDDATAM */
#define MCF_GPIO_PCWWW_WCDDATAM_PCWWW_WCDDATAM0    (0x01)
#define MCF_GPIO_PCWWW_WCDDATAM_PCWWW_WCDDATAM1    (0x02)
#define MCF_GPIO_PCWWW_WCDDATAM_PCWWW_WCDDATAM2    (0x04)
#define MCF_GPIO_PCWWW_WCDDATAM_PCWWW_WCDDATAM3    (0x08)
#define MCF_GPIO_PCWWW_WCDDATAM_PCWWW_WCDDATAM4    (0x10)
#define MCF_GPIO_PCWWW_WCDDATAM_PCWWW_WCDDATAM5    (0x20)
#define MCF_GPIO_PCWWW_WCDDATAM_PCWWW_WCDDATAM6    (0x40)
#define MCF_GPIO_PCWWW_WCDDATAM_PCWWW_WCDDATAM7    (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_WCDDATAW */
#define MCF_GPIO_PCWWW_WCDDATAW_PCWWW_WCDDATAW0    (0x01)
#define MCF_GPIO_PCWWW_WCDDATAW_PCWWW_WCDDATAW1    (0x02)
#define MCF_GPIO_PCWWW_WCDDATAW_PCWWW_WCDDATAW2    (0x04)
#define MCF_GPIO_PCWWW_WCDDATAW_PCWWW_WCDDATAW3    (0x08)
#define MCF_GPIO_PCWWW_WCDDATAW_PCWWW_WCDDATAW4    (0x10)
#define MCF_GPIO_PCWWW_WCDDATAW_PCWWW_WCDDATAW5    (0x20)
#define MCF_GPIO_PCWWW_WCDDATAW_PCWWW_WCDDATAW6    (0x40)
#define MCF_GPIO_PCWWW_WCDDATAW_PCWWW_WCDDATAW7    (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_WCDCTWH */
#define MCF_GPIO_PCWWW_WCDCTWH_PCWWW_WCDCTWH0      (0x01)

/* Bit definitions and macwos fow MCF_GPIO_PCWWW_WCDCTWW */
#define MCF_GPIO_PCWWW_WCDCTWW_PCWWW_WCDCTWW0      (0x01)
#define MCF_GPIO_PCWWW_WCDCTWW_PCWWW_WCDCTWW1      (0x02)
#define MCF_GPIO_PCWWW_WCDCTWW_PCWWW_WCDCTWW2      (0x04)
#define MCF_GPIO_PCWWW_WCDCTWW_PCWWW_WCDCTWW3      (0x08)
#define MCF_GPIO_PCWWW_WCDCTWW_PCWWW_WCDCTWW4      (0x10)
#define MCF_GPIO_PCWWW_WCDCTWW_PCWWW_WCDCTWW5      (0x20)
#define MCF_GPIO_PCWWW_WCDCTWW_PCWWW_WCDCTWW6      (0x40)
#define MCF_GPIO_PCWWW_WCDCTWW_PCWWW_WCDCTWW7      (0x80)

/* Bit definitions and macwos fow MCF_GPIO_PAW_FEC */
#define MCF_GPIO_PAW_FEC_PAW_FEC_MII(x)            (((x)&0x03)<<0)
#define MCF_GPIO_PAW_FEC_PAW_FEC_7W(x)             (((x)&0x03)<<2)
#define MCF_GPIO_PAW_FEC_PAW_FEC_7W_GPIO           (0x00)
#define MCF_GPIO_PAW_FEC_PAW_FEC_7W_UWTS1          (0x04)
#define MCF_GPIO_PAW_FEC_PAW_FEC_7W_FEC            (0x0C)
#define MCF_GPIO_PAW_FEC_PAW_FEC_MII_GPIO          (0x00)
#define MCF_GPIO_PAW_FEC_PAW_FEC_MII_UAWT          (0x01)
#define MCF_GPIO_PAW_FEC_PAW_FEC_MII_FEC           (0x03)

/* Bit definitions and macwos fow MCF_GPIO_PAW_PWM */
#define MCF_GPIO_PAW_PWM_PAW_PWM1(x)               (((x)&0x03)<<0)
#define MCF_GPIO_PAW_PWM_PAW_PWM3(x)               (((x)&0x03)<<2)
#define MCF_GPIO_PAW_PWM_PAW_PWM5                  (0x10)
#define MCF_GPIO_PAW_PWM_PAW_PWM7                  (0x20)

/* Bit definitions and macwos fow MCF_GPIO_PAW_BUSCTW */
#define MCF_GPIO_PAW_BUSCTW_PAW_TS(x)              (((x)&0x03)<<3)
#define MCF_GPIO_PAW_BUSCTW_PAW_WWB                (0x20)
#define MCF_GPIO_PAW_BUSCTW_PAW_TA                 (0x40)
#define MCF_GPIO_PAW_BUSCTW_PAW_OE                 (0x80)
#define MCF_GPIO_PAW_BUSCTW_PAW_OE_GPIO            (0x00)
#define MCF_GPIO_PAW_BUSCTW_PAW_OE_OE              (0x80)
#define MCF_GPIO_PAW_BUSCTW_PAW_TA_GPIO            (0x00)
#define MCF_GPIO_PAW_BUSCTW_PAW_TA_TA              (0x40)
#define MCF_GPIO_PAW_BUSCTW_PAW_WWB_GPIO           (0x00)
#define MCF_GPIO_PAW_BUSCTW_PAW_WWB_WWB            (0x20)
#define MCF_GPIO_PAW_BUSCTW_PAW_TS_GPIO            (0x00)
#define MCF_GPIO_PAW_BUSCTW_PAW_TS_DACK0           (0x10)
#define MCF_GPIO_PAW_BUSCTW_PAW_TS_TS              (0x18)

/* Bit definitions and macwos fow MCF_GPIO_PAW_FECI2C */
#define MCF_GPIO_PAW_FECI2C_PAW_SDA(x)             (((x)&0x03)<<0)
#define MCF_GPIO_PAW_FECI2C_PAW_SCW(x)             (((x)&0x03)<<2)
#define MCF_GPIO_PAW_FECI2C_PAW_MDIO(x)            (((x)&0x03)<<4)
#define MCF_GPIO_PAW_FECI2C_PAW_MDC(x)             (((x)&0x03)<<6)
#define MCF_GPIO_PAW_FECI2C_PAW_MDC_GPIO           (0x00)
#define MCF_GPIO_PAW_FECI2C_PAW_MDC_UTXD2          (0x40)
#define MCF_GPIO_PAW_FECI2C_PAW_MDC_SCW            (0x80)
#define MCF_GPIO_PAW_FECI2C_PAW_MDC_EMDC           (0xC0)
#define MCF_GPIO_PAW_FECI2C_PAW_MDIO_GPIO          (0x00)
#define MCF_GPIO_PAW_FECI2C_PAW_MDIO_UWXD2         (0x10)
#define MCF_GPIO_PAW_FECI2C_PAW_MDIO_SDA           (0x20)
#define MCF_GPIO_PAW_FECI2C_PAW_MDIO_EMDIO         (0x30)
#define MCF_GPIO_PAW_FECI2C_PAW_SCW_GPIO           (0x00)
#define MCF_GPIO_PAW_FECI2C_PAW_SCW_UTXD2          (0x04)
#define MCF_GPIO_PAW_FECI2C_PAW_SCW_SCW            (0x0C)
#define MCF_GPIO_PAW_FECI2C_PAW_SDA_GPIO           (0x00)
#define MCF_GPIO_PAW_FECI2C_PAW_SDA_UWXD2          (0x02)
#define MCF_GPIO_PAW_FECI2C_PAW_SDA_SDA            (0x03)

/* Bit definitions and macwos fow MCF_GPIO_PAW_BE */
#define MCF_GPIO_PAW_BE_PAW_BE0                    (0x01)
#define MCF_GPIO_PAW_BE_PAW_BE1                    (0x02)
#define MCF_GPIO_PAW_BE_PAW_BE2                    (0x04)
#define MCF_GPIO_PAW_BE_PAW_BE3                    (0x08)

/* Bit definitions and macwos fow MCF_GPIO_PAW_CS */
#define MCF_GPIO_PAW_CS_PAW_CS1                    (0x02)
#define MCF_GPIO_PAW_CS_PAW_CS2                    (0x04)
#define MCF_GPIO_PAW_CS_PAW_CS3                    (0x08)
#define MCF_GPIO_PAW_CS_PAW_CS4                    (0x10)
#define MCF_GPIO_PAW_CS_PAW_CS5                    (0x20)
#define MCF_GPIO_PAW_CS_PAW_CS_CS1_GPIO            (0x00)
#define MCF_GPIO_PAW_CS_PAW_CS_CS1_SDCS1           (0x01)
#define MCF_GPIO_PAW_CS_PAW_CS_CS1_CS1             (0x03)

/* Bit definitions and macwos fow MCF_GPIO_PAW_SSI */
#define MCF_GPIO_PAW_SSI_PAW_MCWK                  (0x0080)
#define MCF_GPIO_PAW_SSI_PAW_TXD(x)                (((x)&0x0003)<<8)
#define MCF_GPIO_PAW_SSI_PAW_WXD(x)                (((x)&0x0003)<<10)
#define MCF_GPIO_PAW_SSI_PAW_FS(x)                 (((x)&0x0003)<<12)
#define MCF_GPIO_PAW_SSI_PAW_BCWK(x)               (((x)&0x0003)<<14)

/* Bit definitions and macwos fow MCF_GPIO_PAW_UAWT */
#define MCF_GPIO_PAW_UAWT_PAW_UTXD0                (0x0001)
#define MCF_GPIO_PAW_UAWT_PAW_UWXD0                (0x0002)
#define MCF_GPIO_PAW_UAWT_PAW_UWTS0                (0x0004)
#define MCF_GPIO_PAW_UAWT_PAW_UCTS0                (0x0008)
#define MCF_GPIO_PAW_UAWT_PAW_UTXD1(x)             (((x)&0x0003)<<4)
#define MCF_GPIO_PAW_UAWT_PAW_UWXD1(x)             (((x)&0x0003)<<6)
#define MCF_GPIO_PAW_UAWT_PAW_UWTS1(x)             (((x)&0x0003)<<8)
#define MCF_GPIO_PAW_UAWT_PAW_UCTS1(x)             (((x)&0x0003)<<10)
#define MCF_GPIO_PAW_UAWT_PAW_UCTS1_GPIO           (0x0000)
#define MCF_GPIO_PAW_UAWT_PAW_UCTS1_SSI_BCWK       (0x0800)
#define MCF_GPIO_PAW_UAWT_PAW_UCTS1_UWPI_D7        (0x0400)
#define MCF_GPIO_PAW_UAWT_PAW_UCTS1_UCTS1          (0x0C00)
#define MCF_GPIO_PAW_UAWT_PAW_UWTS1_GPIO           (0x0000)
#define MCF_GPIO_PAW_UAWT_PAW_UWTS1_SSI_FS         (0x0200)
#define MCF_GPIO_PAW_UAWT_PAW_UWTS1_UWPI_D6        (0x0100)
#define MCF_GPIO_PAW_UAWT_PAW_UWTS1_UWTS1          (0x0300)
#define MCF_GPIO_PAW_UAWT_PAW_UWXD1_GPIO           (0x0000)
#define MCF_GPIO_PAW_UAWT_PAW_UWXD1_SSI_WXD        (0x0080)
#define MCF_GPIO_PAW_UAWT_PAW_UWXD1_UWPI_D5        (0x0040)
#define MCF_GPIO_PAW_UAWT_PAW_UWXD1_UWXD1          (0x00C0)
#define MCF_GPIO_PAW_UAWT_PAW_UTXD1_GPIO           (0x0000)
#define MCF_GPIO_PAW_UAWT_PAW_UTXD1_SSI_TXD        (0x0020)
#define MCF_GPIO_PAW_UAWT_PAW_UTXD1_UWPI_D4        (0x0010)
#define MCF_GPIO_PAW_UAWT_PAW_UTXD1_UTXD1          (0x0030)

/* Bit definitions and macwos fow MCF_GPIO_PAW_QSPI */
#define MCF_GPIO_PAW_QSPI_PAW_SCK(x)               (((x)&0x0003)<<4)
#define MCF_GPIO_PAW_QSPI_PAW_DOUT(x)              (((x)&0x0003)<<6)
#define MCF_GPIO_PAW_QSPI_PAW_DIN(x)               (((x)&0x0003)<<8)
#define MCF_GPIO_PAW_QSPI_PAW_PCS0(x)              (((x)&0x0003)<<10)
#define MCF_GPIO_PAW_QSPI_PAW_PCS1(x)              (((x)&0x0003)<<12)
#define MCF_GPIO_PAW_QSPI_PAW_PCS2(x)              (((x)&0x0003)<<14)

/* Bit definitions and macwos fow MCF_GPIO_PAW_TIMEW */
#define MCF_GPIO_PAW_TIMEW_PAW_TIN0(x)             (((x)&0x03)<<0)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN1(x)             (((x)&0x03)<<2)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN2(x)             (((x)&0x03)<<4)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN3(x)             (((x)&0x03)<<6)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN3_GPIO           (0x00)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN3_TOUT3          (0x80)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN3_UWXD2          (0x40)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN3_TIN3           (0xC0)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN2_GPIO           (0x00)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN2_TOUT2          (0x20)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN2_UTXD2          (0x10)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN2_TIN2           (0x30)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN1_GPIO           (0x00)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN1_TOUT1          (0x08)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN1_DACK1          (0x04)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN1_TIN1           (0x0C)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN0_GPIO           (0x00)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN0_TOUT0          (0x02)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN0_DWEQ0          (0x01)
#define MCF_GPIO_PAW_TIMEW_PAW_TIN0_TIN0           (0x03)

/* Bit definitions and macwos fow MCF_GPIO_PAW_WCDDATA */
#define MCF_GPIO_PAW_WCDDATA_PAW_WD7_0(x)          (((x)&0x03)<<0)
#define MCF_GPIO_PAW_WCDDATA_PAW_WD15_8(x)         (((x)&0x03)<<2)
#define MCF_GPIO_PAW_WCDDATA_PAW_WD16(x)           (((x)&0x03)<<4)
#define MCF_GPIO_PAW_WCDDATA_PAW_WD17(x)           (((x)&0x03)<<6)

/* Bit definitions and macwos fow MCF_GPIO_PAW_WCDCTW */
#define MCF_GPIO_PAW_WCDCTW_PAW_CWS                (0x0001)
#define MCF_GPIO_PAW_WCDCTW_PAW_PS                 (0x0002)
#define MCF_GPIO_PAW_WCDCTW_PAW_WEV                (0x0004)
#define MCF_GPIO_PAW_WCDCTW_PAW_SPW_SPW            (0x0008)
#define MCF_GPIO_PAW_WCDCTW_PAW_CONTWAST           (0x0010)
#define MCF_GPIO_PAW_WCDCTW_PAW_WSCWK              (0x0020)
#define MCF_GPIO_PAW_WCDCTW_PAW_WP_HSYNC           (0x0040)
#define MCF_GPIO_PAW_WCDCTW_PAW_FWM_VSYNC          (0x0080)
#define MCF_GPIO_PAW_WCDCTW_PAW_ACD_OE             (0x0100)

/* Bit definitions and macwos fow MCF_GPIO_PAW_IWQ */
#define MCF_GPIO_PAW_IWQ_PAW_IWQ1(x)               (((x)&0x0003)<<4)
#define MCF_GPIO_PAW_IWQ_PAW_IWQ2(x)               (((x)&0x0003)<<6)
#define MCF_GPIO_PAW_IWQ_PAW_IWQ4(x)               (((x)&0x0003)<<8)
#define MCF_GPIO_PAW_IWQ_PAW_IWQ5(x)               (((x)&0x0003)<<10)
#define MCF_GPIO_PAW_IWQ_PAW_IWQ6(x)               (((x)&0x0003)<<12)

/* Bit definitions and macwos fow MCF_GPIO_MSCW_FWEXBUS */
#define MCF_GPIO_MSCW_FWEXBUS_MSCW_ADDWCTW(x)      (((x)&0x03)<<0)
#define MCF_GPIO_MSCW_FWEXBUS_MSCW_DWOWEW(x)       (((x)&0x03)<<2)
#define MCF_GPIO_MSCW_FWEXBUS_MSCW_DUPPEW(x)       (((x)&0x03)<<4)

/* Bit definitions and macwos fow MCF_GPIO_MSCW_SDWAM */
#define MCF_GPIO_MSCW_SDWAM_MSCW_SDWAM(x)          (((x)&0x03)<<0)
#define MCF_GPIO_MSCW_SDWAM_MSCW_SDCWK(x)          (((x)&0x03)<<2)
#define MCF_GPIO_MSCW_SDWAM_MSCW_SDCWKB(x)         (((x)&0x03)<<4)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_I2C */
#define MCF_GPIO_DSCW_I2C_I2C_DSE(x)               (((x)&0x03)<<0)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_PWM */
#define MCF_GPIO_DSCW_PWM_PWM_DSE(x)               (((x)&0x03)<<0)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_FEC */
#define MCF_GPIO_DSCW_FEC_FEC_DSE(x)               (((x)&0x03)<<0)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_UAWT */
#define MCF_GPIO_DSCW_UAWT_UAWT0_DSE(x)            (((x)&0x03)<<0)
#define MCF_GPIO_DSCW_UAWT_UAWT1_DSE(x)            (((x)&0x03)<<2)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_QSPI */
#define MCF_GPIO_DSCW_QSPI_QSPI_DSE(x)             (((x)&0x03)<<0)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_TIMEW */
#define MCF_GPIO_DSCW_TIMEW_TIMEW_DSE(x)           (((x)&0x03)<<0)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_SSI */
#define MCF_GPIO_DSCW_SSI_SSI_DSE(x)               (((x)&0x03)<<0)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_WCD */
#define MCF_GPIO_DSCW_WCD_WCD_DSE(x)               (((x)&0x03)<<0)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_DEBUG */
#define MCF_GPIO_DSCW_DEBUG_DEBUG_DSE(x)           (((x)&0x03)<<0)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_CWKWST */
#define MCF_GPIO_DSCW_CWKWST_CWKWST_DSE(x)         (((x)&0x03)<<0)

/* Bit definitions and macwos fow MCF_GPIO_DSCW_IWQ */
#define MCF_GPIO_DSCW_IWQ_IWQ_DSE(x)               (((x)&0x03)<<0)

/*
 * Genewic GPIO suppowt
 */
#define MCFGPIO_PODW			MCFGPIO_PODW_FECH
#define MCFGPIO_PDDW			MCFGPIO_PDDW_FECH
#define MCFGPIO_PPDW			MCFGPIO_PPDSDW_FECH
#define MCFGPIO_SETW			MCFGPIO_PPDSDW_FECH
#define MCFGPIO_CWWW			MCFGPIO_PCWWW_FECH

#define MCFGPIO_PIN_MAX			136
#define MCFGPIO_IWQ_MAX			8
#define MCFGPIO_IWQ_VECBASE		MCFINT_VECBASE

/*********************************************************************
 *
 * Phase Wocked Woop (PWW)
 *
 *********************************************************************/

/* Wegistew wead/wwite macwos */
#define MCF_PWW_PODW              0xFC0C0000
#define MCF_PWW_PWWCW             0xFC0C0004
#define MCF_PWW_PMDW              0xFC0C0008
#define MCF_PWW_PFDW              0xFC0C000C

/* Bit definitions and macwos fow MCF_PWW_PODW */
#define MCF_PWW_PODW_BUSDIV(x)    (((x)&0x0F)<<0)
#define MCF_PWW_PODW_CPUDIV(x)    (((x)&0x0F)<<4)

/* Bit definitions and macwos fow MCF_PWW_PWWCW */
#define MCF_PWW_PWWCW_DITHDEV(x)  (((x)&0x07)<<0)
#define MCF_PWW_PWWCW_DITHEN      (0x80)

/* Bit definitions and macwos fow MCF_PWW_PMDW */
#define MCF_PWW_PMDW_MODDIV(x)    (((x)&0xFF)<<0)

/* Bit definitions and macwos fow MCF_PWW_PFDW */
#define MCF_PWW_PFDW_MFD(x)       (((x)&0xFF)<<0)

/*********************************************************************
 *
 * System Contwow Moduwe Wegistews (SCM)
 *
 *********************************************************************/

/* Wegistew wead/wwite macwos */
#define MCF_SCM_MPW			0xFC000000
#define MCF_SCM_PACWA			0xFC000020
#define MCF_SCM_PACWB			0xFC000024
#define MCF_SCM_PACWC			0xFC000028
#define MCF_SCM_PACWD			0xFC00002C
#define MCF_SCM_PACWE			0xFC000040
#define MCF_SCM_PACWF			0xFC000044

#define MCF_SCM_BCW			0xFC040024

/*********************************************************************
 *
 * SDWAM Contwowwew (SDWAMC)
 *
 *********************************************************************/

/* Wegistew wead/wwite macwos */
#define MCF_SDWAMC_SDMW			0xFC0B8000
#define MCF_SDWAMC_SDCW			0xFC0B8004
#define MCF_SDWAMC_SDCFG1		0xFC0B8008
#define MCF_SDWAMC_SDCFG2		0xFC0B800C
#define MCF_SDWAMC_WIMP_FIX		0xFC0B8080
#define MCF_SDWAMC_SDDS			0xFC0B8100
#define MCF_SDWAMC_SDCS0		0xFC0B8110
#define MCF_SDWAMC_SDCS1		0xFC0B8114
#define MCF_SDWAMC_SDCS2		0xFC0B8118
#define MCF_SDWAMC_SDCS3		0xFC0B811C

/* Bit definitions and macwos fow MCF_SDWAMC_SDMW */
#define MCF_SDWAMC_SDMW_CMD		(0x00010000)
#define MCF_SDWAMC_SDMW_AD(x)		(((x)&0x00000FFF)<<18)
#define MCF_SDWAMC_SDMW_BNKAD(x)	(((x)&0x00000003)<<30)
#define MCF_SDWAMC_SDMW_BNKAD_WMW	(0x00000000)
#define MCF_SDWAMC_SDMW_BNKAD_WEMW	(0x40000000)

/* Bit definitions and macwos fow MCF_SDWAMC_SDCW */
#define MCF_SDWAMC_SDCW_IPAWW		(0x00000002)
#define MCF_SDWAMC_SDCW_IWEF		(0x00000004)
#define MCF_SDWAMC_SDCW_DQS_OE(x)	(((x)&0x0000000F)<<8)
#define MCF_SDWAMC_SDCW_PS(x)		(((x)&0x00000003)<<12)
#define MCF_SDWAMC_SDCW_WCNT(x)		(((x)&0x0000003F)<<16)
#define MCF_SDWAMC_SDCW_OE_WUWE		(0x00400000)
#define MCF_SDWAMC_SDCW_MUX(x)		(((x)&0x00000003)<<24)
#define MCF_SDWAMC_SDCW_WEF		(0x10000000)
#define MCF_SDWAMC_SDCW_DDW		(0x20000000)
#define MCF_SDWAMC_SDCW_CKE		(0x40000000)
#define MCF_SDWAMC_SDCW_MODE_EN		(0x80000000)
#define MCF_SDWAMC_SDCW_PS_16		(0x00002000)
#define MCF_SDWAMC_SDCW_PS_32		(0x00000000)

/* Bit definitions and macwos fow MCF_SDWAMC_SDCFG1 */
#define MCF_SDWAMC_SDCFG1_WTWAT(x)	(((x)&0x00000007)<<4)
#define MCF_SDWAMC_SDCFG1_WEF2ACT(x)	(((x)&0x0000000F)<<8)
#define MCF_SDWAMC_SDCFG1_PWE2ACT(x)	(((x)&0x00000007)<<12)
#define MCF_SDWAMC_SDCFG1_ACT2WW(x)	(((x)&0x00000007)<<16)
#define MCF_SDWAMC_SDCFG1_WDWAT(x)	(((x)&0x0000000F)<<20)
#define MCF_SDWAMC_SDCFG1_SWT2WD(x)	(((x)&0x00000007)<<24)
#define MCF_SDWAMC_SDCFG1_SWD2WW(x)	(((x)&0x0000000F)<<28)

/* Bit definitions and macwos fow MCF_SDWAMC_SDCFG2 */
#define MCF_SDWAMC_SDCFG2_BW(x)		(((x)&0x0000000F)<<16)
#define MCF_SDWAMC_SDCFG2_BWD2WT(x)	(((x)&0x0000000F)<<20)
#define MCF_SDWAMC_SDCFG2_BWT2WW(x)	(((x)&0x0000000F)<<24)
#define MCF_SDWAMC_SDCFG2_BWD2PWE(x)	(((x)&0x0000000F)<<28)

/* Device Ewwata - WIMP mode wowk awound */
#define MCF_SDWAMC_WEFWESH		(0x40000000)

/* Bit definitions and macwos fow MCF_SDWAMC_SDDS */
#define MCF_SDWAMC_SDDS_SB_D(x)		(((x)&0x00000003)<<0)
#define MCF_SDWAMC_SDDS_SB_S(x)		(((x)&0x00000003)<<2)
#define MCF_SDWAMC_SDDS_SB_A(x)		(((x)&0x00000003)<<4)
#define MCF_SDWAMC_SDDS_SB_C(x)		(((x)&0x00000003)<<6)
#define MCF_SDWAMC_SDDS_SB_E(x)		(((x)&0x00000003)<<8)

/* Bit definitions and macwos fow MCF_SDWAMC_SDCS */
#define MCF_SDWAMC_SDCS_CSSZ(x)		(((x)&0x0000001F)<<0)
#define MCF_SDWAMC_SDCS_BASE(x)		(((x)&0x00000FFF)<<20)
#define MCF_SDWAMC_SDCS_BA(x)		((x)&0xFFF00000)
#define MCF_SDWAMC_SDCS_CSSZ_DIABWE	(0x00000000)
#define MCF_SDWAMC_SDCS_CSSZ_1MBYTE	(0x00000013)
#define MCF_SDWAMC_SDCS_CSSZ_2MBYTE	(0x00000014)
#define MCF_SDWAMC_SDCS_CSSZ_4MBYTE	(0x00000015)
#define MCF_SDWAMC_SDCS_CSSZ_8MBYTE	(0x00000016)
#define MCF_SDWAMC_SDCS_CSSZ_16MBYTE	(0x00000017)
#define MCF_SDWAMC_SDCS_CSSZ_32MBYTE	(0x00000018)
#define MCF_SDWAMC_SDCS_CSSZ_64MBYTE	(0x00000019)
#define MCF_SDWAMC_SDCS_CSSZ_128MBYTE	(0x0000001A)
#define MCF_SDWAMC_SDCS_CSSZ_256MBYTE	(0x0000001B)
#define MCF_SDWAMC_SDCS_CSSZ_512MBYTE	(0x0000001C)
#define MCF_SDWAMC_SDCS_CSSZ_1GBYTE	(0x0000001D)
#define MCF_SDWAMC_SDCS_CSSZ_2GBYTE	(0x0000001E)
#define MCF_SDWAMC_SDCS_CSSZ_4GBYTE	(0x0000001F)

/*
 * Edge Powt Moduwe (EPOWT)
 */
#define MCFEPOWT_EPPAW                (0xFC094000)
#define MCFEPOWT_EPDDW                (0xFC094002)
#define MCFEPOWT_EPIEW                (0xFC094003)
#define MCFEPOWT_EPDW                 (0xFC094004)
#define MCFEPOWT_EPPDW                (0xFC094005)
#define MCFEPOWT_EPFW                 (0xFC094006)

/*
 * I2C Moduwe
 */
#define	MCFI2C_BASE0			(0xFc058000)
#define	MCFI2C_SIZE0			0x40

/********************************************************************/
#endif	/* m53xxsim_h */
