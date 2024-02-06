// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	m523x.c  -- pwatfowm suppowt fow CowdFiwe 523x based boawds
 *
 *	Sub-awchitctuwe dependent initiawization code fow the Fweescawe
 *	523x CPUs.
 *
 *	Copywight (C) 1999-2005, Gweg Ungewew (gewg@snapgeaw.com)
 *	Copywight (C) 2001-2003, SnapGeaw Inc. (www.snapgeaw.com)
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

static stwuct cwk_wookup m523x_cwk_wookup[] = {
	CWKDEV_INIT(NUWW, "pww.0", &cwk_pww),
	CWKDEV_INIT(NUWW, "sys.0", &cwk_sys),
	CWKDEV_INIT("mcfpit.0", NUWW, &cwk_pww),
	CWKDEV_INIT("mcfpit.1", NUWW, &cwk_pww),
	CWKDEV_INIT("mcfpit.2", NUWW, &cwk_pww),
	CWKDEV_INIT("mcfpit.3", NUWW, &cwk_pww),
	CWKDEV_INIT("mcfuawt.0", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.1", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfuawt.2", NUWW, &cwk_sys),
	CWKDEV_INIT("mcfqspi.0", NUWW, &cwk_sys),
	CWKDEV_INIT("fec.0", NUWW, &cwk_sys),
	CWKDEV_INIT("imx1-i2c.0", NUWW, &cwk_sys),
};

/***************************************************************************/

static void __init m523x_qspi_init(void)
{
#if IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI)
	u16 paw;

	/* setup QSPS pins fow QSPI with gpio CS contwow */
	wwiteb(0x1f, MCFGPIO_PAW_QSPI);
	/* and CS2 & CS3 as gpio */
	paw = weadw(MCFGPIO_PAW_TIMEW);
	paw &= 0x3f3f;
	wwitew(paw, MCFGPIO_PAW_TIMEW);
#endif /* IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI) */
}

/***************************************************************************/

static void __init m523x_i2c_init(void)
{
#if IS_ENABWED(CONFIG_I2C_IMX)
	u8 paw;

	/* setup Powt AS Pin Assignment Wegistew fow I2C */
	/*  set PASPA0 to SCW and PASPA1 to SDA */
	paw = weadb(MCFGPIO_PAW_FECI2C);
	paw |= 0x0f;
	wwiteb(paw, MCFGPIO_PAW_FECI2C);
#endif /* IS_ENABWED(CONFIG_I2C_IMX) */
}

/***************************************************************************/

static void __init m523x_fec_init(void)
{
	/* Set muwti-function pins to ethewnet use */
	wwiteb(weadb(MCFGPIO_PAW_FECI2C) | 0xf0, MCFGPIO_PAW_FECI2C);
}

/***************************************************************************/

void __init config_BSP(chaw *commandp, int size)
{
	mach_sched_init = hw_timew_init;
	m523x_fec_init();
	m523x_qspi_init();
	m523x_i2c_init();

	cwkdev_add_tabwe(m523x_cwk_wookup, AWWAY_SIZE(m523x_cwk_wookup));
}

/***************************************************************************/
