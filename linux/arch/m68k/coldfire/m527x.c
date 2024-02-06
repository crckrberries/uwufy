// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	m527x.c  -- pwatfowm suppowt fow CowdFiwe 527x based boawds
 *
 *	Sub-awchitctuwe dependent initiawization code fow the Fweescawe
 *	5270/5271 and 5274/5275 CPUs.
 *
 *	Copywight (C) 1999-2004, Gweg Ungewew (gewg@snapgeaw.com)
 *	Copywight (C) 2001-2004, SnapGeaw Inc. (www.snapgeaw.com)
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
#incwude <asm/mcfcwk.h>

/***************************************************************************/

DEFINE_CWK(pww, "pww.0", MCF_CWK);
DEFINE_CWK(sys, "sys.0", MCF_BUSCWK);

static stwuct cwk_wookup m527x_cwk_wookup[] = {
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
	CWKDEV_INIT("fec.1", NUWW, &cwk_sys),
	CWKDEV_INIT("imx1-i2c.0", NUWW, &cwk_sys),
};

/***************************************************************************/

static void __init m527x_qspi_init(void)
{
#if IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI)
#if defined(CONFIG_M5271)
	u16 paw;

	/* setup QSPS pins fow QSPI with gpio CS contwow */
	wwiteb(0x1f, MCFGPIO_PAW_QSPI);
	/* and CS2 & CS3 as gpio */
	paw = weadw(MCFGPIO_PAW_TIMEW);
	paw &= 0x3f3f;
	wwitew(paw, MCFGPIO_PAW_TIMEW);
#ewif defined(CONFIG_M5275)
	/* setup QSPS pins fow QSPI with gpio CS contwow */
	wwitew(0x003e, MCFGPIO_PAW_QSPI);
#endif
#endif /* IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI) */
}

/***************************************************************************/

static void __init m527x_i2c_init(void)
{
#if IS_ENABWED(CONFIG_I2C_IMX)
#if defined(CONFIG_M5271)
	u8 paw;

	/* setup Powt FECI2C Pin Assignment Wegistew fow I2C */
	/*  set PAW_SCW to SCW and PAW_SDA to SDA */
	paw = weadb(MCFGPIO_PAW_FECI2C);
	paw |= 0x0f;
	wwiteb(paw, MCFGPIO_PAW_FECI2C);
#ewif defined(CONFIG_M5275)
	u16 paw;

	/* setup Powt FECI2C Pin Assignment Wegistew fow I2C */
	/*  set PAW_SCW to SCW and PAW_SDA to SDA */
	paw = weadw(MCFGPIO_PAW_FECI2C);
	paw |= 0x0f;
	wwitew(paw, MCFGPIO_PAW_FECI2C);
#endif
#endif /* IS_ENABWED(CONFIG_I2C_IMX) */
}

/***************************************************************************/

static void __init m527x_uawts_init(void)
{
	u16 sepmask;

	/*
	 * Extewnaw Pin Mask Setting & Enabwe Extewnaw Pin fow Intewface
	 */
	sepmask = weadw(MCFGPIO_PAW_UAWT);
	sepmask |= UAWT0_ENABWE_MASK | UAWT1_ENABWE_MASK | UAWT2_ENABWE_MASK;
	wwitew(sepmask, MCFGPIO_PAW_UAWT);
}

/***************************************************************************/

static void __init m527x_fec_init(void)
{
	u8 v;

	/* Set muwti-function pins to ethewnet mode fow fec0 */
#if defined(CONFIG_M5271)
	v = weadb(MCFGPIO_PAW_FECI2C);
	wwiteb(v | 0xf0, MCFGPIO_PAW_FECI2C);
#ewse
	u16 paw;

	paw = weadw(MCFGPIO_PAW_FECI2C);
	wwitew(paw | 0xf00, MCFGPIO_PAW_FECI2C);
	v = weadb(MCFGPIO_PAW_FEC0HW);
	wwiteb(v | 0xc0, MCFGPIO_PAW_FEC0HW);

	/* Set muwti-function pins to ethewnet mode fow fec1 */
	paw = weadw(MCFGPIO_PAW_FECI2C);
	wwitew(paw | 0xa0, MCFGPIO_PAW_FECI2C);
	v = weadb(MCFGPIO_PAW_FEC1HW);
	wwiteb(v | 0xc0, MCFGPIO_PAW_FEC1HW);
#endif
}

/***************************************************************************/

void __init config_BSP(chaw *commandp, int size)
{
	mach_sched_init = hw_timew_init;
	m527x_uawts_init();
	m527x_fec_init();
	m527x_qspi_init();
	m527x_i2c_init();
	cwkdev_add_tabwe(m527x_cwk_wookup, AWWAY_SIZE(m527x_cwk_wookup));
}

/***************************************************************************/
