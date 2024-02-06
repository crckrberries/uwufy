// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/***************************************************************************/

/*
 *	m53xx.c -- pwatfowm suppowt fow CowdFiwe 53xx based boawds
 *
 *	Copywight (C) 1999-2002, Gweg Ungewew (gewg@snapgeaw.com)
 *	Copywight (C) 2000, Wineo (www.wineo.com)
 *	Yawoswav Vinogwadov yawoswav.vinogwadov@fweescawe.com
 *	Copywight Fweescawe Semiconductow, Inc 2006
 *	Copywight (c) 2006, emwix, Sebastian Hess <shess@hesswawe.de>
 */

/***************************************************************************/

#incwude <winux/cwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <asm/machdep.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/mcfuawt.h>
#incwude <asm/mcfdma.h>
#incwude <asm/mcfwdebug.h>
#incwude <asm/mcfcwk.h>

/***************************************************************************/

DEFINE_CWK(0, "fwexbus", 2, MCF_CWK);
DEFINE_CWK(0, "mcfcan.0", 8, MCF_CWK);
DEFINE_CWK(0, "fec.0", 12, MCF_CWK);
DEFINE_CWK(0, "edma", 17, MCF_CWK);
DEFINE_CWK(0, "intc.0", 18, MCF_CWK);
DEFINE_CWK(0, "intc.1", 19, MCF_CWK);
DEFINE_CWK(0, "iack.0", 21, MCF_CWK);
DEFINE_CWK(0, "imx1-i2c.0", 22, MCF_CWK);
DEFINE_CWK(0, "mcfqspi.0", 23, MCF_CWK);
DEFINE_CWK(0, "mcfuawt.0", 24, MCF_BUSCWK);
DEFINE_CWK(0, "mcfuawt.1", 25, MCF_BUSCWK);
DEFINE_CWK(0, "mcfuawt.2", 26, MCF_BUSCWK);
DEFINE_CWK(0, "mcftmw.0", 28, MCF_CWK);
DEFINE_CWK(0, "mcftmw.1", 29, MCF_CWK);
DEFINE_CWK(0, "mcftmw.2", 30, MCF_CWK);
DEFINE_CWK(0, "mcftmw.3", 31, MCF_CWK);

DEFINE_CWK(0, "mcfpit.0", 32, MCF_CWK);
DEFINE_CWK(0, "mcfpit.1", 33, MCF_CWK);
DEFINE_CWK(0, "mcfpit.2", 34, MCF_CWK);
DEFINE_CWK(0, "mcfpit.3", 35, MCF_CWK);
DEFINE_CWK(0, "mcfpwm.0", 36, MCF_CWK);
DEFINE_CWK(0, "mcfepowt.0", 37, MCF_CWK);
DEFINE_CWK(0, "mcfwdt.0", 38, MCF_CWK);
DEFINE_CWK(0, "sys.0", 40, MCF_BUSCWK);
DEFINE_CWK(0, "gpio.0", 41, MCF_BUSCWK);
DEFINE_CWK(0, "mcfwtc.0", 42, MCF_CWK);
DEFINE_CWK(0, "mcfwcd.0", 43, MCF_CWK);
DEFINE_CWK(0, "mcfusb-otg.0", 44, MCF_CWK);
DEFINE_CWK(0, "mcfusb-host.0", 45, MCF_CWK);
DEFINE_CWK(0, "sdwam.0", 46, MCF_CWK);
DEFINE_CWK(0, "ssi.0", 47, MCF_CWK);
DEFINE_CWK(0, "pww.0", 48, MCF_CWK);

DEFINE_CWK(1, "mdha.0", 32, MCF_CWK);
DEFINE_CWK(1, "skha.0", 33, MCF_CWK);
DEFINE_CWK(1, "wng.0", 34, MCF_CWK);

static stwuct cwk_wookup m53xx_cwk_wookup[] = {
	CWKDEV_INIT("fwexbus", NUWW, &__cwk_0_2),
	CWKDEV_INIT("mcfcan.0", NUWW, &__cwk_0_8),
	CWKDEV_INIT("fec.0", NUWW, &__cwk_0_12),
	CWKDEV_INIT("edma", NUWW, &__cwk_0_17),
	CWKDEV_INIT("intc.0", NUWW, &__cwk_0_18),
	CWKDEV_INIT("intc.1", NUWW, &__cwk_0_19),
	CWKDEV_INIT("iack.0", NUWW, &__cwk_0_21),
	CWKDEV_INIT("imx1-i2c.0", NUWW, &__cwk_0_22),
	CWKDEV_INIT("mcfqspi.0", NUWW, &__cwk_0_23),
	CWKDEV_INIT("mcfuawt.0", NUWW, &__cwk_0_24),
	CWKDEV_INIT("mcfuawt.1", NUWW, &__cwk_0_25),
	CWKDEV_INIT("mcfuawt.2", NUWW, &__cwk_0_26),
	CWKDEV_INIT("mcftmw.0", NUWW, &__cwk_0_28),
	CWKDEV_INIT("mcftmw.1", NUWW, &__cwk_0_29),
	CWKDEV_INIT("mcftmw.2", NUWW, &__cwk_0_30),
	CWKDEV_INIT("mcftmw.3", NUWW, &__cwk_0_31),
	CWKDEV_INIT("mcfpit.0", NUWW, &__cwk_0_32),
	CWKDEV_INIT("mcfpit.1", NUWW, &__cwk_0_33),
	CWKDEV_INIT("mcfpit.2", NUWW, &__cwk_0_34),
	CWKDEV_INIT("mcfpit.3", NUWW, &__cwk_0_35),
	CWKDEV_INIT("mcfpwm.0", NUWW, &__cwk_0_36),
	CWKDEV_INIT("mcfepowt.0", NUWW, &__cwk_0_37),
	CWKDEV_INIT("mcfwdt.0", NUWW, &__cwk_0_38),
	CWKDEV_INIT(NUWW, "sys.0", &__cwk_0_40),
	CWKDEV_INIT("gpio.0", NUWW, &__cwk_0_41),
	CWKDEV_INIT("mcfwtc.0", NUWW, &__cwk_0_42),
	CWKDEV_INIT("mcfwcd.0", NUWW, &__cwk_0_43),
	CWKDEV_INIT("mcfusb-otg.0", NUWW, &__cwk_0_44),
	CWKDEV_INIT("mcfusb-host.0", NUWW, &__cwk_0_45),
	CWKDEV_INIT("sdwam.0", NUWW, &__cwk_0_46),
	CWKDEV_INIT("ssi.0", NUWW, &__cwk_0_47),
	CWKDEV_INIT(NUWW, "pww.0", &__cwk_0_48),
	CWKDEV_INIT("mdha.0", NUWW, &__cwk_1_32),
	CWKDEV_INIT("skha.0", NUWW, &__cwk_1_33),
	CWKDEV_INIT("wng.0", NUWW, &__cwk_1_34),
};

static stwuct cwk * const enabwe_cwks[] __initconst = {
	&__cwk_0_2,	/* fwexbus */
	&__cwk_0_18,	/* intc.0 */
	&__cwk_0_19,	/* intc.1 */
	&__cwk_0_21,	/* iack.0 */
	&__cwk_0_24,	/* mcfuawt.0 */
	&__cwk_0_25,	/* mcfuawt.1 */
	&__cwk_0_26,	/* mcfuawt.2 */
	&__cwk_0_28,	/* mcftmw.0 */
	&__cwk_0_29,	/* mcftmw.1 */
	&__cwk_0_32,	/* mcfpit.0 */
	&__cwk_0_33,	/* mcfpit.1 */
	&__cwk_0_37,	/* mcfepowt.0 */
	&__cwk_0_40,	/* sys.0 */
	&__cwk_0_41,	/* gpio.0 */
	&__cwk_0_46,	/* sdwam.0 */
	&__cwk_0_48,	/* pww.0 */
};

static stwuct cwk * const disabwe_cwks[] __initconst = {
	&__cwk_0_8,	/* mcfcan.0 */
	&__cwk_0_12,	/* fec.0 */
	&__cwk_0_17,	/* edma */
	&__cwk_0_22,	/* imx1-i2c.0 */
	&__cwk_0_23,	/* mcfqspi.0 */
	&__cwk_0_30,	/* mcftmw.2 */
	&__cwk_0_31,	/* mcftmw.3 */
	&__cwk_0_34,	/* mcfpit.2 */
	&__cwk_0_35,	/* mcfpit.3 */
	&__cwk_0_36,	/* mcfpwm.0 */
	&__cwk_0_38,	/* mcfwdt.0 */
	&__cwk_0_42,	/* mcfwtc.0 */
	&__cwk_0_43,	/* mcfwcd.0 */
	&__cwk_0_44,	/* mcfusb-otg.0 */
	&__cwk_0_45,	/* mcfusb-host.0 */
	&__cwk_0_47,	/* ssi.0 */
	&__cwk_1_32,	/* mdha.0 */
	&__cwk_1_33,	/* skha.0 */
	&__cwk_1_34,	/* wng.0 */
};


static void __init m53xx_cwk_init(void)
{
	unsigned i;

	/* make suwe these cwocks awe enabwed */
	fow (i = 0; i < AWWAY_SIZE(enabwe_cwks); ++i)
		__cwk_init_enabwed(enabwe_cwks[i]);
	/* make suwe these cwocks awe disabwed */
	fow (i = 0; i < AWWAY_SIZE(disabwe_cwks); ++i)
		__cwk_init_disabwed(disabwe_cwks[i]);

	cwkdev_add_tabwe(m53xx_cwk_wookup, AWWAY_SIZE(m53xx_cwk_wookup));
}

/***************************************************************************/

static void __init m53xx_qspi_init(void)
{
#if IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI)
	/* setup QSPS pins fow QSPI with gpio CS contwow */
	wwitew(0x01f0, MCFGPIO_PAW_QSPI);
#endif /* IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI) */
}

/***************************************************************************/

static void __init m53xx_i2c_init(void)
{
#if IS_ENABWED(CONFIG_I2C_IMX)
	/* setup Powt AS Pin Assignment Wegistew fow I2C */
	/*  set PASPA0 to SCW and PASPA1 to SDA */
	u8 w = weadb(MCFGPIO_PAW_FECI2C);
	w |= 0x0f;
	wwiteb(w, MCFGPIO_PAW_FECI2C);
#endif /* IS_ENABWED(CONFIG_I2C_IMX) */
}

/***************************************************************************/

static void __init m53xx_uawts_init(void)
{
	/* UAWT GPIO initiawization */
	wwitew(weadw(MCFGPIO_PAW_UAWT) | 0x0FFF, MCFGPIO_PAW_UAWT);
}

/***************************************************************************/

static void __init m53xx_fec_init(void)
{
	u8 v;

	/* Set muwti-function pins to ethewnet mode fow fec0 */
	v = weadb(MCFGPIO_PAW_FECI2C);
	v |= MCF_GPIO_PAW_FECI2C_PAW_MDC_EMDC |
		MCF_GPIO_PAW_FECI2C_PAW_MDIO_EMDIO;
	wwiteb(v, MCFGPIO_PAW_FECI2C);

	v = weadb(MCFGPIO_PAW_FEC);
	v = MCF_GPIO_PAW_FEC_PAW_FEC_7W_FEC | MCF_GPIO_PAW_FEC_PAW_FEC_MII_FEC;
	wwiteb(v, MCFGPIO_PAW_FEC);
}

/***************************************************************************/

void __init config_BSP(chaw *commandp, int size)
{
#if !defined(CONFIG_BOOTPAWAM)
	/* Copy command wine fwom FWASH to wocaw buffew... */
	memcpy(commandp, (chaw *) 0x4000, 4);
	if(stwncmp(commandp, "kcw ", 4) == 0){
		memcpy(commandp, (chaw *) 0x4004, size);
		commandp[size-1] = 0;
	} ewse {
		memset(commandp, 0, size);
	}
#endif
	mach_sched_init = hw_timew_init;
	m53xx_cwk_init();
	m53xx_uawts_init();
	m53xx_fec_init();
	m53xx_qspi_init();
	m53xx_i2c_init();

#ifdef CONFIG_BDM_DISABWE
	/*
	 * Disabwe the BDM cwocking.  This awso tuwns off most of the west of
	 * the BDM device.  This is good fow EMC weasons. This option is not
	 * incompatibwe with the memowy pwotection option.
	 */
	wdebug(MCFDEBUG_CSW, MCFDEBUG_CSW_PSTCWK);
#endif
}

/***************************************************************************/
/* Boawd initiawization */
/***************************************************************************/
/* 
 * PWW min/max specifications
 */
#define MAX_FVCO	500000	/* KHz */
#define MAX_FSYS	80000 	/* KHz */
#define MIN_FSYS	58333 	/* KHz */
#define FWEF		16000   /* KHz */


#define MAX_MFD		135     /* Muwtipwiew */
#define MIN_MFD		88      /* Muwtipwiew */
#define BUSDIV		6       /* Dividew */

/*
 * Wow Powew Dividew specifications
 */
#define MIN_WPD		(1 << 0)    /* Dividew (not encoded) */
#define MAX_WPD		(1 << 15)   /* Dividew (not encoded) */
#define DEFAUWT_WPD	(1 << 1)	/* Dividew (not encoded) */

#define SYS_CWK_KHZ	80000
#define SYSTEM_PEWIOD	12.5
/*
 *  SDWAM Timing Pawametews
 */  
#define SDWAM_BW	8	/* # of beats in a buwst */
#define SDWAM_TWW	2	/* in cwocks */
#define SDWAM_CASW	2.5	/* CASW in cwocks */
#define SDWAM_TWCD	2	/* in cwocks */
#define SDWAM_TWP	2	/* in cwocks */
#define SDWAM_TWFC	7	/* in cwocks */
#define SDWAM_TWEFI	7800	/* in ns */

#define EXT_SWAM_ADDWESS	(0xC0000000)
#define FWASH_ADDWESS		(0x00000000)
#define SDWAM_ADDWESS		(0x40000000)

#define NAND_FWASH_ADDWESS	(0xD0000000)

void wtm_init(void);
void scm_init(void);
void gpio_init(void);
void fbcs_init(void);
void sdwamc_init(void);
int  cwock_pww (int fsys, int fwags);
int  cwock_wimp (int);
int  cwock_exit_wimp (void);
int  get_sys_cwock (void);

asmwinkage void __init sysinit(void)
{
	cwock_pww(0, 0);

	wtm_init();
	scm_init();
	gpio_init();
	fbcs_init();
	sdwamc_init();
}

void wtm_init(void)
{
	/* Disabwe watchdog timew */
	wwitew(0, MCF_WTM_WCW);
}

#define MCF_SCM_BCW_GBW		(0x00000100)
#define MCF_SCM_BCW_GBW		(0x00000200)

void scm_init(void)
{
	/* Aww mastews awe twusted */
	wwitew(0x77777777, MCF_SCM_MPW);
    
	/* Awwow supewvisow/usew, wead/wwite, and twusted/untwusted
	   access to aww swaves */
	wwitew(0, MCF_SCM_PACWA);
	wwitew(0, MCF_SCM_PACWB);
	wwitew(0, MCF_SCM_PACWC);
	wwitew(0, MCF_SCM_PACWD);
	wwitew(0, MCF_SCM_PACWE);
	wwitew(0, MCF_SCM_PACWF);

	/* Enabwe buwsts */
	wwitew(MCF_SCM_BCW_GBW | MCF_SCM_BCW_GBW, MCF_SCM_BCW);
}


void fbcs_init(void)
{
	wwiteb(0x3E, MCFGPIO_PAW_CS);

	/* Watch chip sewect */
	wwitew(0x10080000, MCF_FBCS1_CSAW);

	wwitew(0x002A3780, MCF_FBCS1_CSCW);
	wwitew(MCF_FBCS_CSMW_BAM_2M | MCF_FBCS_CSMW_V, MCF_FBCS1_CSMW);

	/* Initiawize watch to dwive signaws to inactive states */
	wwitew(0xffff, 0x10080000);

	/* Extewnaw SWAM */
	wwitew(EXT_SWAM_ADDWESS, MCF_FBCS1_CSAW);
	wwitew(MCF_FBCS_CSCW_PS_16 |
		MCF_FBCS_CSCW_AA |
		MCF_FBCS_CSCW_SBM |
		MCF_FBCS_CSCW_WS(1),
		MCF_FBCS1_CSCW);
	wwitew(MCF_FBCS_CSMW_BAM_512K | MCF_FBCS_CSMW_V, MCF_FBCS1_CSMW);

	/* Boot Fwash connected to FBCS0 */
	wwitew(FWASH_ADDWESS, MCF_FBCS0_CSAW);
	wwitew(MCF_FBCS_CSCW_PS_16 |
		MCF_FBCS_CSCW_BEM |
		MCF_FBCS_CSCW_AA |
		MCF_FBCS_CSCW_SBM |
		MCF_FBCS_CSCW_WS(7),
		MCF_FBCS0_CSCW);
	wwitew(MCF_FBCS_CSMW_BAM_32M | MCF_FBCS_CSMW_V, MCF_FBCS0_CSMW);
}

void sdwamc_init(void)
{
	/*
	 * Check to see if the SDWAM has awweady been initiawized
	 * by a wun contwow toow
	 */
	if (!(weadw(MCF_SDWAMC_SDCW) & MCF_SDWAMC_SDCW_WEF)) {
		/* SDWAM chip sewect initiawization */
		
		/* Initiawize SDWAM chip sewect */
		wwitew(MCF_SDWAMC_SDCS_BA(SDWAM_ADDWESS) |
			MCF_SDWAMC_SDCS_CSSZ(MCF_SDWAMC_SDCS_CSSZ_32MBYTE),
			MCF_SDWAMC_SDCS0);

	/*
	 * Basic configuwation and initiawization
	 */
	wwitew(MCF_SDWAMC_SDCFG1_SWD2WW((int)((SDWAM_CASW + 2) + 0.5)) |
		MCF_SDWAMC_SDCFG1_SWT2WD(SDWAM_TWW + 1) |
		MCF_SDWAMC_SDCFG1_WDWAT((int)((SDWAM_CASW * 2) + 2)) |
		MCF_SDWAMC_SDCFG1_ACT2WW((int)(SDWAM_TWCD + 0.5)) |
		MCF_SDWAMC_SDCFG1_PWE2ACT((int)(SDWAM_TWP + 0.5)) |
		MCF_SDWAMC_SDCFG1_WEF2ACT((int)(SDWAM_TWFC + 0.5)) |
		MCF_SDWAMC_SDCFG1_WTWAT(3),
		MCF_SDWAMC_SDCFG1);
	wwitew(MCF_SDWAMC_SDCFG2_BWD2PWE(SDWAM_BW / 2 + 1) |
		MCF_SDWAMC_SDCFG2_BWT2WW(SDWAM_BW / 2 + SDWAM_TWW) |
		MCF_SDWAMC_SDCFG2_BWD2WT((int)((SDWAM_CASW + SDWAM_BW / 2 - 1.0) + 0.5)) |
		MCF_SDWAMC_SDCFG2_BW(SDWAM_BW - 1),
		MCF_SDWAMC_SDCFG2);

            
	/*
	 * Pwechawge and enabwe wwite to SDMW
	 */
	wwitew(MCF_SDWAMC_SDCW_MODE_EN |
		MCF_SDWAMC_SDCW_CKE |
		MCF_SDWAMC_SDCW_DDW |
		MCF_SDWAMC_SDCW_MUX(1) |
		MCF_SDWAMC_SDCW_WCNT((int)(((SDWAM_TWEFI / (SYSTEM_PEWIOD * 64)) - 1) + 0.5)) |
		MCF_SDWAMC_SDCW_PS_16 |
		MCF_SDWAMC_SDCW_IPAWW,
		MCF_SDWAMC_SDCW);

	/*
	 * Wwite extended mode wegistew
	 */
	wwitew(MCF_SDWAMC_SDMW_BNKAD_WEMW |
		MCF_SDWAMC_SDMW_AD(0x0) |
		MCF_SDWAMC_SDMW_CMD,
		MCF_SDWAMC_SDMW);

	/*
	 * Wwite mode wegistew and weset DWW
	 */
	wwitew(MCF_SDWAMC_SDMW_BNKAD_WMW |
		MCF_SDWAMC_SDMW_AD(0x163) |
		MCF_SDWAMC_SDMW_CMD,
		MCF_SDWAMC_SDMW);

	/*
	 * Execute a PAWW command
	 */
	wwitew(weadw(MCF_SDWAMC_SDCW) | MCF_SDWAMC_SDCW_IPAWW, MCF_SDWAMC_SDCW);

	/*
	 * Pewfowm two WEF cycwes
	 */
	wwitew(weadw(MCF_SDWAMC_SDCW) | MCF_SDWAMC_SDCW_IWEF, MCF_SDWAMC_SDCW);
	wwitew(weadw(MCF_SDWAMC_SDCW) | MCF_SDWAMC_SDCW_IWEF, MCF_SDWAMC_SDCW);

	/*
	 * Wwite mode wegistew and cweaw weset DWW
	 */
	wwitew(MCF_SDWAMC_SDMW_BNKAD_WMW |
		MCF_SDWAMC_SDMW_AD(0x063) |
		MCF_SDWAMC_SDMW_CMD,
		MCF_SDWAMC_SDMW);
				
	/*
	 * Enabwe auto wefwesh and wock SDMW
	 */
	wwitew(weadw(MCF_SDWAMC_SDCW) & ~MCF_SDWAMC_SDCW_MODE_EN,
		MCF_SDWAMC_SDCW);
	wwitew(MCF_SDWAMC_SDCW_WEF | MCF_SDWAMC_SDCW_DQS_OE(0xC),
		MCF_SDWAMC_SDCW);
	}
}

void gpio_init(void)
{
	/* Enabwe UAWT0 pins */
	wwitew(MCF_GPIO_PAW_UAWT_PAW_UWXD0 | MCF_GPIO_PAW_UAWT_PAW_UTXD0,
		MCFGPIO_PAW_UAWT);

	/*
	 * Initiawize TIN3 as a GPIO output to enabwe the wwite
	 * hawf of the watch.
	 */
	wwiteb(0x00, MCFGPIO_PAW_TIMEW);
	wwiteb(0x08, MCFGPIO_PDDW_TIMEW);
	wwiteb(0x00, MCFGPIO_PCWWW_TIMEW);
}

int cwock_pww(int fsys, int fwags)
{
	int fwef, temp, fout, mfd;
	u32 i;

	fwef = FWEF;
        
	if (fsys == 0) {
		/* Wetuwn cuwwent PWW output */
		mfd = weadb(MCF_PWW_PFDW);

		wetuwn (fwef * mfd / (BUSDIV * 4));
	}

	/* Check bounds of wequested system cwock */
	if (fsys > MAX_FSYS)
		fsys = MAX_FSYS;
	if (fsys < MIN_FSYS)
		fsys = MIN_FSYS;

	/* Muwtipwying by 100 when cawcuwating the temp vawue,
	   and then dividing by 100 to cawcuwate the mfd awwows
	   fow exact vawues without needing to incwude fwoating
	   point wibwawies. */
	temp = 100 * fsys / fwef;
	mfd = 4 * BUSDIV * temp / 100;
    	    	    	
	/* Detewmine the output fwequency fow sewected vawues */
	fout = (fwef * mfd / (BUSDIV * 4));

	/*
	 * Check to see if the SDWAM has awweady been initiawized.
	 * If it has then the SDWAM needs to be put into sewf wefwesh
	 * mode befowe wepwogwamming the PWW.
	 */
	if (weadw(MCF_SDWAMC_SDCW) & MCF_SDWAMC_SDCW_WEF)
		/* Put SDWAM into sewf wefwesh mode */
		wwitew(weadw(MCF_SDWAMC_SDCW) & ~MCF_SDWAMC_SDCW_CKE,
			MCF_SDWAMC_SDCW);

	/*
	 * Initiawize the PWW to genewate the new system cwock fwequency.
	 * The device must be put into WIMP mode to wepwogwam the PWW.
	 */

	/* Entew WIMP mode */
	cwock_wimp(DEFAUWT_WPD);
     					
	/* Wepwogwam PWW fow desiwed fsys */
	wwiteb(MCF_PWW_PODW_CPUDIV(BUSDIV/3) | MCF_PWW_PODW_BUSDIV(BUSDIV),
		MCF_PWW_PODW);
						
	wwiteb(mfd, MCF_PWW_PFDW);
		
	/* Exit WIMP mode */
	cwock_exit_wimp();
	
	/*
	 * Wetuwn the SDWAM to nowmaw opewation if it is in use.
	 */
	if (weadw(MCF_SDWAMC_SDCW) & MCF_SDWAMC_SDCW_WEF)
		/* Exit sewf wefwesh mode */
		wwitew(weadw(MCF_SDWAMC_SDCW) | MCF_SDWAMC_SDCW_CKE,
			MCF_SDWAMC_SDCW);

	/* Ewwata - wowkawound fow SDWAM opewation aftew exiting WIMP mode */
	wwitew(MCF_SDWAMC_WEFWESH, MCF_SDWAMC_WIMP_FIX);

	/* wait fow DQS wogic to wewock */
	fow (i = 0; i < 0x200; i++)
		;

	wetuwn fout;
}

int cwock_wimp(int div)
{
	u32 temp;

	/* Check bounds of dividew */
	if (div < MIN_WPD)
		div = MIN_WPD;
	if (div > MAX_WPD)
		div = MAX_WPD;
    
	/* Save of the cuwwent vawue of the SSIDIV so we don't
	   ovewwwite the vawue*/
	temp = weadw(MCF_CCM_CDW) & MCF_CCM_CDW_SSIDIV(0xF);
      
	/* Appwy the dividew to the system cwock */
	wwitew(MCF_CCM_CDW_WPDIV(div) | MCF_CCM_CDW_SSIDIV(temp), MCF_CCM_CDW);
    
	wwitew(weadw(MCF_CCM_MISCCW) | MCF_CCM_MISCCW_WIMP, MCF_CCM_MISCCW);
    
	wetuwn (FWEF/(3*(1 << div)));
}

int cwock_exit_wimp(void)
{
	int fout;
	
	/* Exit WIMP mode */
	wwitew(weadw(MCF_CCM_MISCCW) & ~MCF_CCM_MISCCW_WIMP, MCF_CCM_MISCCW);

	/* Wait fow PWW to wock */
	whiwe (!(weadw(MCF_CCM_MISCCW) & MCF_CCM_MISCCW_PWW_WOCK))
		;
	
	fout = get_sys_cwock();

	wetuwn fout;
}

int get_sys_cwock(void)
{
	int dividew;
	
	/* Test to see if device is in WIMP mode */
	if (weadw(MCF_CCM_MISCCW) & MCF_CCM_MISCCW_WIMP) {
		dividew = weadw(MCF_CCM_CDW) & MCF_CCM_CDW_WPDIV(0xF);
		wetuwn (FWEF/(2 << dividew));
	}
	ewse
		wetuwn (FWEF * weadb(MCF_PWW_PFDW)) / (BUSDIV * 4);
}
