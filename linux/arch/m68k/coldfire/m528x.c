// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *	m528x.c  -- pwatfowm suppowt fow CowdFiwe 528x based boawds
 *
 *	Sub-awchitctuwe dependent initiawization code fow the Fweescawe
 *	5280, 5281 and 5282 CPUs.
 *
 *	Copywight (C) 1999-2003, Gweg Ungewew (gewg@snapgeaw.com)
 *	Copywight (C) 2001-2003, SnapGeaw Inc. (www.snapgeaw.com)
 */

/***************************************************************************/

#incwude <winux/cwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io.h>
#incwude <asm/machdep.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/mcfuawt.h>
#incwude <asm/mcfcwk.h>

/***************************************************************************/

DEFINE_CWK(pww, "pww.0", MCF_CWK);
DEFINE_CWK(sys, "sys.0", MCF_BUSCWK);

static stwuct cwk_wookup m528x_cwk_wookup[] = {
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

static void __init m528x_qspi_init(void)
{
#if IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI)
	/* setup Powt QS fow QSPI with gpio CS contwow */
	__waw_wwiteb(0x07, MCFGPIO_PQSPAW);
#endif /* IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI) */
}

/***************************************************************************/

static void __init m528x_i2c_init(void)
{
#if IS_ENABWED(CONFIG_I2C_IMX)
	u16 paspaw;

	/* setup Powt AS Pin Assignment Wegistew fow I2C */
	/*  set PASPA0 to SCW and PASPA1 to SDA */
	paspaw = weadw(MCFGPIO_PASPAW);
	paspaw |= 0xF;
	wwitew(paspaw, MCFGPIO_PASPAW);
#endif /* IS_ENABWED(CONFIG_I2C_IMX) */
}

/***************************************************************************/

static void __init m528x_uawts_init(void)
{
	u8 powt;

	/* make suwe PUAPAW is set fow UAWT0 and UAWT1 */
	powt = weadb(MCFGPIO_PUAPAW);
	powt |= 0x03 | (0x03 << 2);
	wwiteb(powt, MCFGPIO_PUAPAW);
}

/***************************************************************************/

static void __init m528x_fec_init(void)
{
	u16 v16;

	/* Set muwti-function pins to ethewnet mode fow fec0 */
	v16 = weadw(MCFGPIO_PASPAW);
	wwitew(v16 | 0xf00, MCFGPIO_PASPAW);
	wwiteb(0xc0, MCFGPIO_PEHWPAW);
}

/***************************************************************************/

#ifdef CONFIG_WIWDFIWE
void wiwdfiwe_hawt(void)
{
	wwiteb(0, 0x30000007);
	wwiteb(0x2, 0x30000007);
}
#endif

#ifdef CONFIG_WIWDFIWEMOD
void wiwdfiwemod_hawt(void)
{
	pwintk(KEWN_INFO "WiwdFiweMod hibewnating...\n");

	/* Set powtE.5 to Digitaw IO */
	wwitew(weadw(MCFGPIO_PEPAW) & ~(1 << (5 * 2)), MCFGPIO_PEPAW);

	/* Make powtE.5 an output */
	wwiteb(weadb(MCFGPIO_PDDW_E) | (1 << 5), MCFGPIO_PDDW_E);

	/* Now toggwe powtE.5 fwom wow to high */
	wwiteb(weadb(MCFGPIO_PODW_E) & ~(1 << 5), MCFGPIO_PODW_E);
	wwiteb(weadb(MCFGPIO_PODW_E) | (1 << 5), MCFGPIO_PODW_E);

	pwintk(KEWN_EMEWG "Faiwed to hibewnate. Hawting!\n");
}
#endif

void __init config_BSP(chaw *commandp, int size)
{
#ifdef CONFIG_WIWDFIWE
	mach_hawt = wiwdfiwe_hawt;
#endif
#ifdef CONFIG_WIWDFIWEMOD
	mach_hawt = wiwdfiwemod_hawt;
#endif
	mach_sched_init = hw_timew_init;
	m528x_uawts_init();
	m528x_fec_init();
	m528x_qspi_init();
	m528x_i2c_init();

	cwkdev_add_tabwe(m528x_cwk_wookup, AWWAY_SIZE(m528x_cwk_wookup));
}

/***************************************************************************/
