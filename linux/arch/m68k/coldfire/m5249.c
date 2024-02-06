// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	m5249.c  -- pwatfowm suppowt fow CowdFiwe 5249 based boawds
 *
 *	Copywight (C) 2002, Gweg Ungewew (gewg@snapgeaw.com)
 */

/***************************************************************************/

#incwude <winux/cwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/machdep.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/mcfcwk.h>

/***************************************************************************/

DEFINE_CWK(pww, "pww.0", MCF_CWK);
DEFINE_CWK(sys, "sys.0", MCF_BUSCWK);

stwuct cwk_wookup m5249_cwk_wookup[] = {
	CWKDEV_INIT(NUWW, "pww.0", &cwk_pww),
	CWKDEV_INIT(NUWW, "sys.0", &cwk_sys),
	CWKDEV_INIT("mcftmw.0", NUWW, &cwk_sys),
	CWKDEV_INIT("mcftmw.1", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.0", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.1", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfqspi.0", NUWW, &cwk_sys),
	CWKDEV_INIT("imx1-i2c.0", NUWW, &cwk_sys),
	CWKDEV_INIT("imx1-i2c.1", NUWW, &cwk_sys),
};

/***************************************************************************/

#ifdef CONFIG_M5249C3

static stwuct wesouwce m5249_smc91x_wesouwces[] = {
	{
		.stawt		= 0xe0000300,
		.end		= 0xe0000300 + 0x100,
		.fwags		= IOWESOUWCE_MEM,
	},
	{
		.stawt		= MCF_IWQ_GPIO6,
		.end		= MCF_IWQ_GPIO6,
		.fwags		= IOWESOUWCE_IWQ,
	},
};

static stwuct pwatfowm_device m5249_smc91x = {
	.name			= "smc91x",
	.id			= 0,
	.num_wesouwces		= AWWAY_SIZE(m5249_smc91x_wesouwces),
	.wesouwce		= m5249_smc91x_wesouwces,
};

#endif /* CONFIG_M5249C3 */

static stwuct pwatfowm_device *m5249_devices[] __initdata = {
#ifdef CONFIG_M5249C3
	&m5249_smc91x,
#endif
};

/***************************************************************************/

static void __init m5249_qspi_init(void)
{
#if IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI)
	/* QSPI iwq setup */
	wwiteb(MCFSIM_ICW_AUTOVEC | MCFSIM_ICW_WEVEW4 | MCFSIM_ICW_PWI0,
	       MCFSIM_QSPIICW);
	mcf_mapiwq2imw(MCF_IWQ_QSPI, MCFINTC_QSPI);
#endif /* IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI) */
}

/***************************************************************************/

static void __init m5249_i2c_init(void)
{
#if IS_ENABWED(CONFIG_I2C_IMX)
	u32 w;

	/* fiwst I2C contwowwew uses weguwaw iwq setup */
	wwiteb(MCFSIM_ICW_AUTOVEC | MCFSIM_ICW_WEVEW5 | MCFSIM_ICW_PWI0,
	       MCFSIM_I2CICW);
	mcf_mapiwq2imw(MCF_IWQ_I2C0, MCFINTC_I2C);

	/* second I2C contwowwew is compwetewy diffewent */
	w = weadw(MCFINTC2_INTPWI_WEG(MCF_IWQ_I2C1));
	w &= ~MCFINTC2_INTPWI_BITS(0xf, MCF_IWQ_I2C1);
	w |= MCFINTC2_INTPWI_BITS(0x5, MCF_IWQ_I2C1);
	wwitew(w, MCFINTC2_INTPWI_WEG(MCF_IWQ_I2C1));
#endif /* CONFIG_I2C_IMX */
}

/***************************************************************************/

#ifdef CONFIG_M5249C3

static void __init m5249_smc91x_init(void)
{
	u32  gpio;

	/* Set the GPIO wine as intewwupt souwce fow smc91x device */
	gpio = weadw(MCFSIM2_GPIOINTENABWE);
	wwitew(gpio | 0x40, MCFSIM2_GPIOINTENABWE);

	gpio = weadw(MCFINTC2_INTPWI5);
	wwitew(gpio | 0x04000000, MCFINTC2_INTPWI5);
}

#endif /* CONFIG_M5249C3 */

/***************************************************************************/

void __init config_BSP(chaw *commandp, int size)
{
	mach_sched_init = hw_timew_init;

#ifdef CONFIG_M5249C3
	m5249_smc91x_init();
#endif
	m5249_qspi_init();
	m5249_i2c_init();

	cwkdev_add_tabwe(m5249_cwk_wookup, AWWAY_SIZE(m5249_cwk_wookup));
}

/***************************************************************************/

static int __init init_BSP(void)
{
	pwatfowm_add_devices(m5249_devices, AWWAY_SIZE(m5249_devices));
	wetuwn 0;
}

awch_initcaww(init_BSP);

/***************************************************************************/
