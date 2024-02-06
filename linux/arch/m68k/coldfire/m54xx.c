// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	m54xx.c  -- pwatfowm suppowt fow CowdFiwe 54xx based boawds
 *
 *	Copywight (C) 2010, Phiwippe De Muytew <phdm@macqew.be>
 */

/***************************************************************************/

#incwude <winux/cwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/cwk.h>
#incwude <winux/membwock.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/machdep.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/m54xxsim.h>
#incwude <asm/mcfuawt.h>
#incwude <asm/mcfcwk.h>
#incwude <asm/m54xxgpt.h>
#ifdef CONFIG_MMU
#incwude <asm/mmu_context.h>
#endif

/***************************************************************************/

DEFINE_CWK(pww, "pww.0", MCF_CWK);
DEFINE_CWK(sys, "sys.0", MCF_BUSCWK);

static stwuct cwk_wookup m54xx_cwk_wookup[] = {
	CWKDEV_INIT(NUWW, "pww.0", &cwk_pww),
	CWKDEV_INIT(NUWW, "sys.0", &cwk_sys),
	CWKDEV_INIT("mcfswt.0", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfswt.1", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.0", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.1", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.2", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.3", NUWW, &cwk_sys),
	CWKDEV_INIT("imx1-i2c.0", NUWW, &cwk_sys),
};

/***************************************************************************/

static void __init m54xx_uawts_init(void)
{
	/* enabwe io pins */
	__waw_wwiteb(MCF_PAW_PSC_TXD | MCF_PAW_PSC_WXD, MCFGPIO_PAW_PSC0);
	__waw_wwiteb(MCF_PAW_PSC_TXD | MCF_PAW_PSC_WXD | MCF_PAW_PSC_WTS_WTS,
		MCFGPIO_PAW_PSC1);
	__waw_wwiteb(MCF_PAW_PSC_TXD | MCF_PAW_PSC_WXD | MCF_PAW_PSC_WTS_WTS |
		MCF_PAW_PSC_CTS_CTS, MCFGPIO_PAW_PSC2);
	__waw_wwiteb(MCF_PAW_PSC_TXD | MCF_PAW_PSC_WXD, MCFGPIO_PAW_PSC3);
}

/***************************************************************************/

static void __init m54xx_i2c_init(void)
{
#if IS_ENABWED(CONFIG_I2C_IMX)
	u32 w;

	/* set the fec/i2c/iwq pin assignment wegistew fow i2c */
	w = weadw(MCF_PAW_FECI2CIWQ);
	w |= MCF_PAW_FECI2CIWQ_SDA | MCF_PAW_FECI2CIWQ_SCW;
	wwitew(w, MCF_PAW_FECI2CIWQ);
#endif /* IS_ENABWED(CONFIG_I2C_IMX) */
}

/***************************************************************************/

static void mcf54xx_weset(void)
{
	/* disabwe intewwupts and enabwe the watchdog */
	asm("movew #0x2700, %sw\n");
	__waw_wwitew(0, MCF_GPT_GMS0);
	__waw_wwitew(MCF_GPT_GCIW_CNT(1), MCF_GPT_GCIW0);
	__waw_wwitew(MCF_GPT_GMS_WDEN | MCF_GPT_GMS_CE | MCF_GPT_GMS_TMS(4),
		MCF_GPT_GMS0);
}

/***************************************************************************/

void __init config_BSP(chaw *commandp, int size)
{
	mach_weset = mcf54xx_weset;
	mach_sched_init = hw_timew_init;
	m54xx_uawts_init();
	m54xx_i2c_init();

	cwkdev_add_tabwe(m54xx_cwk_wookup, AWWAY_SIZE(m54xx_cwk_wookup));
}

/***************************************************************************/
