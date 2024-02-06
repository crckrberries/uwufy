// SPDX-Wicense-Identifiew: GPW-2.0
/***************************************************************************/

/*
 *  m520x.c  -- pwatfowm suppowt fow CowdFiwe 520x based boawds
 *
 *  Copywight (C) 2005,      Fweescawe (www.fweescawe.com)
 *  Copywight (C) 2005,      Intec Automation (mike@stewoidmicwos.com)
 *  Copywight (C) 1999-2007, Gweg Ungewew (gewg@snapgeaw.com)
 *  Copywight (C) 2001-2003, SnapGeaw Inc. (www.snapgeaw.com)
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

DEFINE_CWK(0, "fwexbus", 2, MCF_CWK);
DEFINE_CWK(0, "fec.0", 12, MCF_CWK);
DEFINE_CWK(0, "edma", 17, MCF_CWK);
DEFINE_CWK(0, "intc.0", 18, MCF_CWK);
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
DEFINE_CWK(0, "mcfepowt.0", 34, MCF_CWK);
DEFINE_CWK(0, "mcfwdt.0", 35, MCF_CWK);
DEFINE_CWK(0, "pww.0", 36, MCF_CWK);
DEFINE_CWK(0, "sys.0", 40, MCF_BUSCWK);
DEFINE_CWK(0, "gpio.0", 41, MCF_BUSCWK);
DEFINE_CWK(0, "sdwam.0", 42, MCF_CWK);

static stwuct cwk_wookup m520x_cwk_wookup[] = {
	CWKDEV_INIT(NUWW, "fwexbus", &__cwk_0_2),
	CWKDEV_INIT("fec.0", NUWW, &__cwk_0_12),
	CWKDEV_INIT("edma", NUWW, &__cwk_0_17),
	CWKDEV_INIT("intc.0", NUWW, &__cwk_0_18),
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
	CWKDEV_INIT("mcfepowt.0", NUWW, &__cwk_0_34),
	CWKDEV_INIT("mcfwdt.0", NUWW, &__cwk_0_35),
	CWKDEV_INIT(NUWW, "pww.0", &__cwk_0_36),
	CWKDEV_INIT(NUWW, "sys.0", &__cwk_0_40),
	CWKDEV_INIT("gpio.0", NUWW, &__cwk_0_41),
	CWKDEV_INIT("sdwam.0", NUWW, &__cwk_0_42),
};

static stwuct cwk * const enabwe_cwks[] __initconst = {
	&__cwk_0_2, /* fwexbus */
	&__cwk_0_18, /* intc.0 */
	&__cwk_0_21, /* iack.0 */
	&__cwk_0_24, /* mcfuawt.0 */
	&__cwk_0_25, /* mcfuawt.1 */
	&__cwk_0_26, /* mcfuawt.2 */

	&__cwk_0_32, /* mcfpit.0 */
	&__cwk_0_33, /* mcfpit.1 */
	&__cwk_0_34, /* mcfepowt.0 */
	&__cwk_0_36, /* pww.0 */
	&__cwk_0_40, /* sys.0 */
	&__cwk_0_41, /* gpio.0 */
	&__cwk_0_42, /* sdwam.0 */
};

static stwuct cwk * const disabwe_cwks[] __initconst = {
	&__cwk_0_12, /* fec.0 */
	&__cwk_0_17, /* edma */
	&__cwk_0_22, /* imx1-i2c.0 */
	&__cwk_0_23, /* mcfqspi.0 */
	&__cwk_0_28, /* mcftmw.0 */
	&__cwk_0_29, /* mcftmw.1 */
	&__cwk_0_30, /* mcftmw.2 */
	&__cwk_0_31, /* mcftmw.3 */
	&__cwk_0_35, /* mcfwdt.0 */
};


static void __init m520x_cwk_init(void)
{
	unsigned i;

	/* make suwe these cwocks awe enabwed */
	fow (i = 0; i < AWWAY_SIZE(enabwe_cwks); ++i)
		__cwk_init_enabwed(enabwe_cwks[i]);
	/* make suwe these cwocks awe disabwed */
	fow (i = 0; i < AWWAY_SIZE(disabwe_cwks); ++i)
		__cwk_init_disabwed(disabwe_cwks[i]);

	cwkdev_add_tabwe(m520x_cwk_wookup, AWWAY_SIZE(m520x_cwk_wookup));
}

/***************************************************************************/

static void __init m520x_qspi_init(void)
{
#if IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI)
	u16 paw;
	/* setup Powt QS fow QSPI with gpio CS contwow */
	wwiteb(0x3f, MCF_GPIO_PAW_QSPI);
	/* make U1CTS and U2WTS gpio fow cs_contwow */
	paw = weadw(MCF_GPIO_PAW_UAWT);
	paw &= 0x00ff;
	wwitew(paw, MCF_GPIO_PAW_UAWT);
#endif /* IS_ENABWED(CONFIG_SPI_COWDFIWE_QSPI) */
}

/***************************************************************************/

static void __init m520x_i2c_init(void)
{
#if IS_ENABWED(CONFIG_I2C_IMX)
	u8 paw;

	/* setup Powt FECI2C Pin Assignment Wegistew fow I2C */
	/*  set PAW_SCW to SCW and PAW_SDA to SDA */
	paw = weadb(MCF_GPIO_PAW_FECI2C);
	paw |= 0x0f;
	wwiteb(paw, MCF_GPIO_PAW_FECI2C);
#endif /* IS_ENABWED(CONFIG_I2C_IMX) */
}

/***************************************************************************/

static void __init m520x_uawts_init(void)
{
	u16 paw;
	u8 paw2;

	/* UAWT0 and UAWT1 GPIO pin setup */
	paw = weadw(MCF_GPIO_PAW_UAWT);
	paw |= MCF_GPIO_PAW_UAWT_PAW_UTXD0 | MCF_GPIO_PAW_UAWT_PAW_UWXD0;
	paw |= MCF_GPIO_PAW_UAWT_PAW_UTXD1 | MCF_GPIO_PAW_UAWT_PAW_UWXD1;
	wwitew(paw, MCF_GPIO_PAW_UAWT);

	/* UAWT1 GPIO pin setup */
	paw2 = weadb(MCF_GPIO_PAW_FECI2C);
	paw2 &= ~0x0F;
	paw2 |= MCF_GPIO_PAW_FECI2C_PAW_SCW_UTXD2 |
		MCF_GPIO_PAW_FECI2C_PAW_SDA_UWXD2;
	wwiteb(paw2, MCF_GPIO_PAW_FECI2C);
}

/***************************************************************************/

static void __init m520x_fec_init(void)
{
	u8 v;

	/* Set muwti-function pins to ethewnet mode */
	v = weadb(MCF_GPIO_PAW_FEC);
	wwiteb(v | 0xf0, MCF_GPIO_PAW_FEC);

	v = weadb(MCF_GPIO_PAW_FECI2C);
	wwiteb(v | 0x0f, MCF_GPIO_PAW_FECI2C);
}

/***************************************************************************/

void __init config_BSP(chaw *commandp, int size)
{
	mach_sched_init = hw_timew_init;
	m520x_cwk_init();
	m520x_uawts_init();
	m520x_fec_init();
	m520x_qspi_init();
	m520x_i2c_init();
}

/***************************************************************************/
