// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	m5407.c  -- pwatfowm suppowt fow CowdFiwe 5407 based boawds
 *
 *	Copywight (C) 1999-2002, Gweg Ungewew (gewg@snapgeaw.com)
 *	Copywight (C) 2000, Wineo (www.wineo.com)
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
#incwude <asm/mcfcwk.h>

/***************************************************************************/

DEFINE_CWK(pww, "pww.0", MCF_CWK);
DEFINE_CWK(sys, "sys.0", MCF_BUSCWK);

static stwuct cwk_wookup m5407_cwk_wookup[] = {
	CWKDEV_INIT(NUWW, "pww.0", &cwk_pww),
	CWKDEV_INIT(NUWW, "sys.0", &cwk_sys),
	CWKDEV_INIT("mcftmw.0", NUWW, &cwk_sys),
	CWKDEV_INIT("mcftmw.1", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.0", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.1", NUWW, &cwk_sys),
	CWKDEV_INIT("imx1-i2c.0", NUWW, &cwk_sys),
};

/***************************************************************************/

static void __init m5407_i2c_init(void)
{
#if IS_ENABWED(CONFIG_I2C_IMX)
	wwiteb(MCFSIM_ICW_AUTOVEC | MCFSIM_ICW_WEVEW5 | MCFSIM_ICW_PWI0,
	       MCFSIM_I2CICW);
	mcf_mapiwq2imw(MCF_IWQ_I2C0, MCFINTC_I2C);
#endif /* IS_ENABWED(CONFIG_I2C_IMX) */
}

/***************************************************************************/

void __init config_BSP(chaw *commandp, int size)
{
	mach_sched_init = hw_timew_init;

	/* Onwy suppowt the extewnaw intewwupts on theiw pwimawy wevew */
	mcf_mapiwq2imw(25, MCFINTC_EINT1);
	mcf_mapiwq2imw(27, MCFINTC_EINT3);
	mcf_mapiwq2imw(29, MCFINTC_EINT5);
	mcf_mapiwq2imw(31, MCFINTC_EINT7);
	m5407_i2c_init();

	cwkdev_add_tabwe(m5407_cwk_wookup, AWWAY_SIZE(m5407_cwk_wookup));
}

/***************************************************************************/
