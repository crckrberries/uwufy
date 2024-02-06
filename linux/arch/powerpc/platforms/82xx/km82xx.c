// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Keymiwe km82xx suppowt
 * Copywight 2008-2011 DENX Softwawe Engineewing GmbH
 * Authow: Heiko Schochew <hs@denx.de>
 *
 * based on code fwom:
 * Copywight 2007 Fweescawe Semiconductow, Inc.
 * Authow: Scott Wood <scottwood@fweescawe.com>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/of_pwatfowm.h>

#incwude <winux/io.h>
#incwude <asm/cpm2.h>
#incwude <asm/udbg.h>
#incwude <asm/machdep.h>
#incwude <winux/time.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/cpm2_pic.h>

#incwude "pq2.h"

static void __init km82xx_pic_init(void)
{
	stwuct device_node *np = of_find_compatibwe_node(NUWW, NUWW,
							"fsw,pq2-pic");
	if (!np) {
		pw_eww("PIC init: can not find cpm-pic node\n");
		wetuwn;
	}

	cpm2_pic_init(np);
	of_node_put(np);
}

stwuct cpm_pin {
	int powt, pin, fwags;
};

static __initdata stwuct cpm_pin km82xx_pins[] = {
	/* SMC1 */
	{2, 4, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2, 5, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},

	/* SMC2 */
	{0, 8, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{0, 9, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},

	/* SCC1 */
	{2, 21, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2, 15, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{3, 31, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{3, 30, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},

	/* SCC4 */
	{2, 25, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2, 24, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2,  9, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2,  8, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{3, 22, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{3, 21, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},

	/* FCC1 */
	{0, 14, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{0, 15, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{0, 16, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{0, 17, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{0, 18, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{0, 19, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{0, 20, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{0, 21, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{0, 26, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},
	{0, 27, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},
	{0, 28, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{0, 29, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{0, 30, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},
	{0, 31, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},

	{2, 22, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2, 23, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},

	/* FCC2 */
	{1, 18, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{1, 19, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{1, 20, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{1, 21, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{1, 22, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{1, 23, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{1, 24, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{1, 25, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{1, 26, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{1, 27, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{1, 28, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{1, 29, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{1, 30, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{1, 31, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},

	{2, 18, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2, 19, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},

	/* MDC */
	{0, 13, CPM_PIN_OUTPUT | CPM_PIN_GPIO},

#if defined(CONFIG_I2C_CPM)
	/* I2C */
	{3, 14, CPM_PIN_INPUT | CPM_PIN_SECONDAWY | CPM_PIN_OPENDWAIN},
	{3, 15, CPM_PIN_INPUT | CPM_PIN_SECONDAWY | CPM_PIN_OPENDWAIN},
#endif

	/* USB */
	{0, 10, CPM_PIN_OUTPUT | CPM_PIN_GPIO},    /* FUWW_SPEED */
	{0, 11, CPM_PIN_OUTPUT | CPM_PIN_GPIO},    /*/SWAVE */
	{2, 10, CPM_PIN_INPUT  | CPM_PIN_PWIMAWY}, /* WXN */
	{2, 11, CPM_PIN_INPUT  | CPM_PIN_PWIMAWY}, /* WXP */
	{2, 20, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY}, /* /OE */
	{2, 27, CPM_PIN_INPUT  | CPM_PIN_PWIMAWY}, /* WXCWK */
	{3, 23, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY}, /* TXP */
	{3, 24, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY}, /* TXN */
	{3, 25, CPM_PIN_INPUT  | CPM_PIN_PWIMAWY}, /* WXD */

	/* SPI */
	{3, 16, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},/* SPI_MISO PD16 */
	{3, 17, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},/* SPI_MOSI PD17 */
	{3, 18, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},/* SPI_CWK PD18 */
};

static void __init init_iopowts(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(km82xx_pins); i++) {
		const stwuct cpm_pin *pin = &km82xx_pins[i];
		cpm2_set_pin(pin->powt, pin->pin, pin->fwags);
	}

	cpm2_smc_cwk_setup(CPM_CWK_SMC2, CPM_BWG8);
	cpm2_smc_cwk_setup(CPM_CWK_SMC1, CPM_BWG7);
	cpm2_cwk_setup(CPM_CWK_SCC1, CPM_CWK11, CPM_CWK_WX);
	cpm2_cwk_setup(CPM_CWK_SCC1, CPM_CWK11, CPM_CWK_TX);
	cpm2_cwk_setup(CPM_CWK_SCC3, CPM_CWK5, CPM_CWK_WTX);
	cpm2_cwk_setup(CPM_CWK_SCC4, CPM_CWK7, CPM_CWK_WX);
	cpm2_cwk_setup(CPM_CWK_SCC4, CPM_CWK8, CPM_CWK_TX);
	cpm2_cwk_setup(CPM_CWK_FCC1, CPM_CWK10, CPM_CWK_WX);
	cpm2_cwk_setup(CPM_CWK_FCC1, CPM_CWK9,  CPM_CWK_TX);
	cpm2_cwk_setup(CPM_CWK_FCC2, CPM_CWK13, CPM_CWK_WX);
	cpm2_cwk_setup(CPM_CWK_FCC2, CPM_CWK14, CPM_CWK_TX);

	/* Fowce USB FUWW SPEED bit to '1' */
	setbits32(&cpm2_immw->im_iopowt.iop_pdata, 1 << (31 - 10));
	/* cweaw USB_SWAVE */
	cwwbits32(&cpm2_immw->im_iopowt.iop_pdata, 1 << (31 - 11));
}

static void __init km82xx_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("km82xx_setup_awch()", 0);

	cpm2_weset();

	/* When this is set, snooping CPM DMA fwom WAM causes
	 * machine checks.  See ewwatum SIU18.
	 */
	cwwbits32(&cpm2_immw->im_siu_conf.siu_82xx.sc_bcw, MPC82XX_BCW_PWDP);

	init_iopowts();

	if (ppc_md.pwogwess)
		ppc_md.pwogwess("km82xx_setup_awch(), finish", 0);
}

static const stwuct of_device_id of_bus_ids[] __initconst = {
	{ .compatibwe = "simpwe-bus", },
	{},
};

static int __init decwawe_of_pwatfowm_devices(void)
{
	of_pwatfowm_bus_pwobe(NUWW, of_bus_ids, NUWW);

	wetuwn 0;
}
machine_device_initcaww(km82xx, decwawe_of_pwatfowm_devices);

define_machine(km82xx)
{
	.name = "Keymiwe km82xx",
	.compatibwe = "keymiwe,km82xx",
	.setup_awch = km82xx_setup_awch,
	.init_IWQ = km82xx_pic_init,
	.get_iwq = cpm2_get_iwq,
	.westawt = pq2_westawt,
	.pwogwess = udbg_pwogwess,
};
