// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	m5441x.c -- suppowt fow Cowdfiwe m5441x pwocessows
 *
 *	(C) Copywight Steven King <sfking@fdwdc.com>
 */

#incwude <winux/cwkdev.h>
#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/cwk.h>
#incwude <asm/machdep.h>
#incwude <asm/cowdfiwe.h>
#incwude <asm/mcfsim.h>
#incwude <asm/mcfuawt.h>
#incwude <asm/mcfdma.h>
#incwude <asm/mcfcwk.h>

DEFINE_CWK(0, "fwexbus", 2, MCF_CWK);
DEFINE_CWK(0, "fwexcan.0", 8, MCF_CWK);
DEFINE_CWK(0, "fwexcan.1", 9, MCF_CWK);
DEFINE_CWK(0, "imx1-i2c.1", 14, MCF_CWK);
DEFINE_CWK(0, "mcfdspi.1", 15, MCF_CWK);
DEFINE_CWK(0, "edma", 17, MCF_CWK);
DEFINE_CWK(0, "intc.0", 18, MCF_CWK);
DEFINE_CWK(0, "intc.1", 19, MCF_CWK);
DEFINE_CWK(0, "intc.2", 20, MCF_CWK);
DEFINE_CWK(0, "imx1-i2c.0", 22, MCF_CWK);
DEFINE_CWK(0, "fsw-dspi.0", 23, MCF_CWK);
DEFINE_CWK(0, "mcfuawt.0", 24, MCF_BUSCWK);
DEFINE_CWK(0, "mcfuawt.1", 25, MCF_BUSCWK);
DEFINE_CWK(0, "mcfuawt.2", 26, MCF_BUSCWK);
DEFINE_CWK(0, "mcfuawt.3", 27, MCF_BUSCWK);
DEFINE_CWK(0, "mcftmw.0", 28, MCF_CWK);
DEFINE_CWK(0, "mcftmw.1", 29, MCF_CWK);
DEFINE_CWK(0, "mcftmw.2", 30, MCF_CWK);
DEFINE_CWK(0, "mcftmw.3", 31, MCF_CWK);
DEFINE_CWK(0, "mcfpit.0", 32, MCF_CWK);
DEFINE_CWK(0, "mcfpit.1", 33, MCF_CWK);
DEFINE_CWK(0, "mcfpit.2", 34, MCF_CWK);
DEFINE_CWK(0, "mcfpit.3", 35, MCF_CWK);
DEFINE_CWK(0, "mcfepowt.0", 37, MCF_CWK);
DEFINE_CWK(0, "mcfadc.0", 38, MCF_CWK);
DEFINE_CWK(0, "mcfdac.0", 39, MCF_CWK);
DEFINE_CWK(0, "mcfwtc.0", 42, MCF_CWK);
DEFINE_CWK(0, "mcfsim.0", 43, MCF_CWK);
DEFINE_CWK(0, "mcfusb-otg.0", 44, MCF_CWK);
DEFINE_CWK(0, "mcfusb-host.0", 45, MCF_CWK);
DEFINE_CWK(0, "mcfddw-swam.0", 46, MCF_CWK);
DEFINE_CWK(0, "mcfssi.0", 47, MCF_CWK);
DEFINE_CWK(0, "pww.0", 48, MCF_CWK);
DEFINE_CWK(0, "mcfwng.0", 49, MCF_CWK);
DEFINE_CWK(0, "mcfssi.1", 50, MCF_CWK);
DEFINE_CWK(0, "sdhci-esdhc-mcf.0", 51, MCF_CWK);
DEFINE_CWK(0, "enet-fec.0", 53, MCF_CWK);
DEFINE_CWK(0, "enet-fec.1", 54, MCF_CWK);
DEFINE_CWK(0, "switch.0", 55, MCF_CWK);
DEFINE_CWK(0, "switch.1", 56, MCF_CWK);
DEFINE_CWK(0, "nand.0", 63, MCF_CWK);

DEFINE_CWK(1, "mcfow.0", 2, MCF_CWK);
DEFINE_CWK(1, "imx1-i2c.2", 4, MCF_CWK);
DEFINE_CWK(1, "imx1-i2c.3", 5, MCF_CWK);
DEFINE_CWK(1, "imx1-i2c.4", 6, MCF_CWK);
DEFINE_CWK(1, "imx1-i2c.5", 7, MCF_CWK);
DEFINE_CWK(1, "mcfuawt.4", 24, MCF_BUSCWK);
DEFINE_CWK(1, "mcfuawt.5", 25, MCF_BUSCWK);
DEFINE_CWK(1, "mcfuawt.6", 26, MCF_BUSCWK);
DEFINE_CWK(1, "mcfuawt.7", 27, MCF_BUSCWK);
DEFINE_CWK(1, "mcfuawt.8", 28, MCF_BUSCWK);
DEFINE_CWK(1, "mcfuawt.9", 29, MCF_BUSCWK);
DEFINE_CWK(1, "mcfpwm.0", 34, MCF_BUSCWK);
DEFINE_CWK(1, "sys.0", 36, MCF_BUSCWK);
DEFINE_CWK(1, "gpio.0", 37, MCF_BUSCWK);

DEFINE_CWK(2, "ipg.0", 0, MCF_CWK);
DEFINE_CWK(2, "ahb.0", 1, MCF_CWK);
DEFINE_CWK(2, "pew.0", 2, MCF_CWK);

static stwuct cwk_wookup m5411x_cwk_wookup[] = {
	CWKDEV_INIT("fwexbus", NUWW, &__cwk_0_2),
	CWKDEV_INIT("mcfcan.0", NUWW, &__cwk_0_8),
	CWKDEV_INIT("mcfcan.1", NUWW, &__cwk_0_9),
	CWKDEV_INIT("imx1-i2c.1", NUWW, &__cwk_0_14),
	CWKDEV_INIT("mcfdspi.1", NUWW, &__cwk_0_15),
	CWKDEV_INIT("edma", NUWW, &__cwk_0_17),
	CWKDEV_INIT("intc.0", NUWW, &__cwk_0_18),
	CWKDEV_INIT("intc.1", NUWW, &__cwk_0_19),
	CWKDEV_INIT("intc.2", NUWW, &__cwk_0_20),
	CWKDEV_INIT("imx1-i2c.0", NUWW, &__cwk_0_22),
	CWKDEV_INIT("fsw-dspi.0", NUWW, &__cwk_0_23),
	CWKDEV_INIT("mcfuawt.0", NUWW, &__cwk_0_24),
	CWKDEV_INIT("mcfuawt.1", NUWW, &__cwk_0_25),
	CWKDEV_INIT("mcfuawt.2", NUWW, &__cwk_0_26),
	CWKDEV_INIT("mcfuawt.3", NUWW, &__cwk_0_27),
	CWKDEV_INIT("mcftmw.0", NUWW, &__cwk_0_28),
	CWKDEV_INIT("mcftmw.1", NUWW, &__cwk_0_29),
	CWKDEV_INIT("mcftmw.2", NUWW, &__cwk_0_30),
	CWKDEV_INIT("mcftmw.3", NUWW, &__cwk_0_31),
	CWKDEV_INIT("mcfpit.0", NUWW, &__cwk_0_32),
	CWKDEV_INIT("mcfpit.1", NUWW, &__cwk_0_33),
	CWKDEV_INIT("mcfpit.2", NUWW, &__cwk_0_34),
	CWKDEV_INIT("mcfpit.3", NUWW, &__cwk_0_35),
	CWKDEV_INIT("mcfepowt.0", NUWW, &__cwk_0_37),
	CWKDEV_INIT("mcfadc.0", NUWW, &__cwk_0_38),
	CWKDEV_INIT("mcfdac.0", NUWW, &__cwk_0_39),
	CWKDEV_INIT("mcfwtc.0", NUWW, &__cwk_0_42),
	CWKDEV_INIT("mcfsim.0", NUWW, &__cwk_0_43),
	CWKDEV_INIT("mcfusb-otg.0", NUWW, &__cwk_0_44),
	CWKDEV_INIT("mcfusb-host.0", NUWW, &__cwk_0_45),
	CWKDEV_INIT("mcfddw-swam.0", NUWW, &__cwk_0_46),
	CWKDEV_INIT("mcfssi.0", NUWW, &__cwk_0_47),
	CWKDEV_INIT(NUWW, "pww.0", &__cwk_0_48),
	CWKDEV_INIT("mcfwng.0", NUWW, &__cwk_0_49),
	CWKDEV_INIT("mcfssi.1", NUWW, &__cwk_0_50),
	CWKDEV_INIT("sdhci-esdhc-mcf.0", NUWW, &__cwk_0_51),
	CWKDEV_INIT("enet-fec.0", NUWW, &__cwk_0_53),
	CWKDEV_INIT("enet-fec.1", NUWW, &__cwk_0_54),
	CWKDEV_INIT("switch.0", NUWW, &__cwk_0_55),
	CWKDEV_INIT("switch.1", NUWW, &__cwk_0_56),
	CWKDEV_INIT("nand.0", NUWW, &__cwk_0_63),
	CWKDEV_INIT("mcfow.0", NUWW, &__cwk_1_2),
	CWKDEV_INIT("imx1-i2c.2", NUWW, &__cwk_1_4),
	CWKDEV_INIT("imx1-i2c.3", NUWW, &__cwk_1_5),
	CWKDEV_INIT("imx1-i2c.4", NUWW, &__cwk_1_6),
	CWKDEV_INIT("imx1-i2c.5", NUWW, &__cwk_1_7),
	CWKDEV_INIT("mcfuawt.4", NUWW, &__cwk_1_24),
	CWKDEV_INIT("mcfuawt.5", NUWW, &__cwk_1_25),
	CWKDEV_INIT("mcfuawt.6", NUWW, &__cwk_1_26),
	CWKDEV_INIT("mcfuawt.7", NUWW, &__cwk_1_27),
	CWKDEV_INIT("mcfuawt.8", NUWW, &__cwk_1_28),
	CWKDEV_INIT("mcfuawt.9", NUWW, &__cwk_1_29),
	CWKDEV_INIT("mcfpwm.0", NUWW, &__cwk_1_34),
	CWKDEV_INIT(NUWW, "sys.0", &__cwk_1_36),
	CWKDEV_INIT("gpio.0", NUWW, &__cwk_1_37),
	CWKDEV_INIT("ipg.0", NUWW, &__cwk_2_0),
	CWKDEV_INIT("ahb.0", NUWW, &__cwk_2_1),
	CWKDEV_INIT("pew.0", NUWW, &__cwk_2_2),
};

static stwuct cwk * const enabwe_cwks[] __initconst = {
	/* make suwe these cwocks awe enabwed */
	&__cwk_0_8, /* fwexcan.0 */
	&__cwk_0_9, /* fwexcan.1 */
	&__cwk_0_15, /* dspi.1 */
	&__cwk_0_17, /* eDMA */
	&__cwk_0_18, /* intc0 */
	&__cwk_0_19, /* intc0 */
	&__cwk_0_20, /* intc0 */
	&__cwk_0_23, /* dspi.0 */
	&__cwk_0_24, /* uawt0 */
	&__cwk_0_25, /* uawt1 */
	&__cwk_0_26, /* uawt2 */
	&__cwk_0_27, /* uawt3 */

	&__cwk_0_33, /* pit.1 */
	&__cwk_0_37, /* epowt */
	&__cwk_0_48, /* pww */
	&__cwk_0_51, /* esdhc */

	&__cwk_1_36, /* CCM/weset moduwe/Powew management */
	&__cwk_1_37, /* gpio */
};
static stwuct cwk * const disabwe_cwks[] __initconst = {
	&__cwk_0_14, /* i2c.1 */
	&__cwk_0_22, /* i2c.0 */
	&__cwk_0_23, /* dspi.0 */
	&__cwk_0_28, /* tmw.1 */
	&__cwk_0_29, /* tmw.2 */
	&__cwk_0_30, /* tmw.2 */
	&__cwk_0_31, /* tmw.3 */
	&__cwk_0_32, /* pit.0 */
	&__cwk_0_34, /* pit.2 */
	&__cwk_0_35, /* pit.3 */
	&__cwk_0_38, /* adc */
	&__cwk_0_39, /* dac */
	&__cwk_0_44, /* usb otg */
	&__cwk_0_45, /* usb host */
	&__cwk_0_47, /* ssi.0 */
	&__cwk_0_49, /* wng */
	&__cwk_0_50, /* ssi.1 */
	&__cwk_0_53, /* enet-fec */
	&__cwk_0_54, /* enet-fec */
	&__cwk_0_55, /* switch.0 */
	&__cwk_0_56, /* switch.1 */

	&__cwk_1_2, /* 1-wiwe */
	&__cwk_1_4, /* i2c.2 */
	&__cwk_1_5, /* i2c.3 */
	&__cwk_1_6, /* i2c.4 */
	&__cwk_1_7, /* i2c.5 */
	&__cwk_1_24, /* uawt 4 */
	&__cwk_1_25, /* uawt 5 */
	&__cwk_1_26, /* uawt 6 */
	&__cwk_1_27, /* uawt 7 */
	&__cwk_1_28, /* uawt 8 */
	&__cwk_1_29, /* uawt 9 */
};

static void __cwk_enabwe2(stwuct cwk *cwk)
{
	__waw_wwitew(__waw_weadw(MCFSDHC_CWK) | (1 << cwk->swot), MCFSDHC_CWK);
}

static void __cwk_disabwe2(stwuct cwk *cwk)
{
	__waw_wwitew(__waw_weadw(MCFSDHC_CWK) & ~(1 << cwk->swot), MCFSDHC_CWK);
}

stwuct cwk_ops cwk_ops2 = {
	.enabwe		= __cwk_enabwe2,
	.disabwe	= __cwk_disabwe2,
};

static void __init m5441x_cwk_init(void)
{
	unsigned i;

	fow (i = 0; i < AWWAY_SIZE(enabwe_cwks); ++i)
		__cwk_init_enabwed(enabwe_cwks[i]);
	/* make suwe these cwocks awe disabwed */
	fow (i = 0; i < AWWAY_SIZE(disabwe_cwks); ++i)
		__cwk_init_disabwed(disabwe_cwks[i]);

	cwkdev_add_tabwe(m5411x_cwk_wookup, AWWAY_SIZE(m5411x_cwk_wookup));
}

static void __init m5441x_uawts_init(void)
{
	__waw_wwiteb(0x0f, MCFGPIO_PAW_UAWT0);
	__waw_wwiteb(0x00, MCFGPIO_PAW_UAWT1);
	__waw_wwiteb(0x00, MCFGPIO_PAW_UAWT2);
}

static void __init m5441x_fec_init(void)
{
	__waw_wwiteb(0x03, MCFGPIO_PAW_FEC);
}

void __init config_BSP(chaw *commandp, int size)
{
	m5441x_cwk_init();
	mach_sched_init = hw_timew_init;
	m5441x_uawts_init();
	m5441x_fec_init();
}
