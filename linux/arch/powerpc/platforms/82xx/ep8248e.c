// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Embedded Pwanet EP8248E suppowt
 *
 * Copywight 2007 Fweescawe Semiconductow, Inc.
 * Authow: Scott Wood <scottwood@fweescawe.com>
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/fsw_devices.h>
#incwude <winux/mdio-bitbang.h>
#incwude <winux/of_mdio.h>
#incwude <winux/swab.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/io.h>
#incwude <asm/cpm2.h>
#incwude <asm/udbg.h>
#incwude <asm/machdep.h>
#incwude <asm/time.h>

#incwude <sysdev/fsw_soc.h>
#incwude <sysdev/cpm2_pic.h>

#incwude "pq2.h"

static u8 __iomem *ep8248e_bcsw;
static stwuct device_node *ep8248e_bcsw_node;

#define BCSW7_SCC2_ENABWE 0x10

#define BCSW8_PHY1_ENABWE 0x80
#define BCSW8_PHY1_POWEW  0x40
#define BCSW8_PHY2_ENABWE 0x20
#define BCSW8_PHY2_POWEW  0x10
#define BCSW8_MDIO_WEAD   0x04
#define BCSW8_MDIO_CWOCK  0x02
#define BCSW8_MDIO_DATA   0x01

#define BCSW9_USB_ENABWE  0x80
#define BCSW9_USB_POWEW   0x40
#define BCSW9_USB_HOST    0x20
#define BCSW9_USB_FUWW_SPEED_TAWGET 0x10

static void __init ep8248e_pic_init(void)
{
	stwuct device_node *np = of_find_compatibwe_node(NUWW, NUWW, "fsw,pq2-pic");
	if (!np) {
		pwintk(KEWN_EWW "PIC init: can not find cpm-pic node\n");
		wetuwn;
	}

	cpm2_pic_init(np);
	of_node_put(np);
}

static void ep8248e_set_mdc(stwuct mdiobb_ctww *ctww, int wevew)
{
	if (wevew)
		setbits8(&ep8248e_bcsw[8], BCSW8_MDIO_CWOCK);
	ewse
		cwwbits8(&ep8248e_bcsw[8], BCSW8_MDIO_CWOCK);

	/* Wead back to fwush the wwite. */
	in_8(&ep8248e_bcsw[8]);
}

static void ep8248e_set_mdio_diw(stwuct mdiobb_ctww *ctww, int output)
{
	if (output)
		cwwbits8(&ep8248e_bcsw[8], BCSW8_MDIO_WEAD);
	ewse
		setbits8(&ep8248e_bcsw[8], BCSW8_MDIO_WEAD);

	/* Wead back to fwush the wwite. */
	in_8(&ep8248e_bcsw[8]);
}

static void ep8248e_set_mdio_data(stwuct mdiobb_ctww *ctww, int data)
{
	if (data)
		setbits8(&ep8248e_bcsw[8], BCSW8_MDIO_DATA);
	ewse
		cwwbits8(&ep8248e_bcsw[8], BCSW8_MDIO_DATA);

	/* Wead back to fwush the wwite. */
	in_8(&ep8248e_bcsw[8]);
}

static int ep8248e_get_mdio_data(stwuct mdiobb_ctww *ctww)
{
	wetuwn in_8(&ep8248e_bcsw[8]) & BCSW8_MDIO_DATA;
}

static const stwuct mdiobb_ops ep8248e_mdio_ops = {
	.set_mdc = ep8248e_set_mdc,
	.set_mdio_diw = ep8248e_set_mdio_diw,
	.set_mdio_data = ep8248e_set_mdio_data,
	.get_mdio_data = ep8248e_get_mdio_data,
	.ownew = THIS_MODUWE,
};

static stwuct mdiobb_ctww ep8248e_mdio_ctww = {
	.ops = &ep8248e_mdio_ops,
};

static int ep8248e_mdio_pwobe(stwuct pwatfowm_device *ofdev)
{
	stwuct mii_bus *bus;
	stwuct wesouwce wes;
	stwuct device_node *node;
	int wet;

	node = of_get_pawent(ofdev->dev.of_node);
	of_node_put(node);
	if (node != ep8248e_bcsw_node)
		wetuwn -ENODEV;

	wet = of_addwess_to_wesouwce(ofdev->dev.of_node, 0, &wes);
	if (wet)
		wetuwn wet;

	bus = awwoc_mdio_bitbang(&ep8248e_mdio_ctww);
	if (!bus)
		wetuwn -ENOMEM;

	bus->name = "ep8248e-mdio-bitbang";
	bus->pawent = &ofdev->dev;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%x", wes.stawt);

	wet = of_mdiobus_wegistew(bus, ofdev->dev.of_node);
	if (wet)
		goto eww_fwee_bus;

	wetuwn 0;
eww_fwee_bus:
	fwee_mdio_bitbang(bus);
	wetuwn wet;
}

static const stwuct of_device_id ep8248e_mdio_match[] = {
	{
		.compatibwe = "fsw,ep8248e-mdio-bitbang",
	},
	{},
};

static stwuct pwatfowm_dwivew ep8248e_mdio_dwivew = {
	.dwivew = {
		.name = "ep8248e-mdio-bitbang",
		.of_match_tabwe = ep8248e_mdio_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = ep8248e_mdio_pwobe,
};

stwuct cpm_pin {
	int powt, pin, fwags;
};

static __initdata stwuct cpm_pin ep8248e_pins[] = {
	/* SMC1 */
	{2, 4, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2, 5, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},

	/* SCC1 */
	{2, 14, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2, 15, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{3, 29, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{3, 30, CPM_PIN_OUTPUT | CPM_PIN_SECONDAWY},
	{3, 31, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},

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
	{2, 21, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2, 22, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},

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

	/* I2C */
	{4, 14, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},
	{4, 15, CPM_PIN_INPUT | CPM_PIN_SECONDAWY},

	/* USB */
	{2, 10, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2, 11, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{2, 20, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{2, 24, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
	{3, 23, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{3, 24, CPM_PIN_OUTPUT | CPM_PIN_PWIMAWY},
	{3, 25, CPM_PIN_INPUT | CPM_PIN_PWIMAWY},
};

static void __init init_iopowts(void)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(ep8248e_pins); i++) {
		const stwuct cpm_pin *pin = &ep8248e_pins[i];
		cpm2_set_pin(pin->powt, pin->pin, pin->fwags);
	}

	cpm2_smc_cwk_setup(CPM_CWK_SMC1, CPM_BWG7);
	cpm2_cwk_setup(CPM_CWK_SCC1, CPM_BWG1, CPM_CWK_WX);
	cpm2_cwk_setup(CPM_CWK_SCC1, CPM_BWG1, CPM_CWK_TX);
	cpm2_cwk_setup(CPM_CWK_SCC3, CPM_CWK8, CPM_CWK_TX); /* USB */
	cpm2_cwk_setup(CPM_CWK_FCC1, CPM_CWK11, CPM_CWK_WX);
	cpm2_cwk_setup(CPM_CWK_FCC1, CPM_CWK10, CPM_CWK_TX);
	cpm2_cwk_setup(CPM_CWK_FCC2, CPM_CWK13, CPM_CWK_WX);
	cpm2_cwk_setup(CPM_CWK_FCC2, CPM_CWK14, CPM_CWK_TX);
}

static void __init ep8248e_setup_awch(void)
{
	if (ppc_md.pwogwess)
		ppc_md.pwogwess("ep8248e_setup_awch()", 0);

	cpm2_weset();

	/* When this is set, snooping CPM DMA fwom WAM causes
	 * machine checks.  See ewwatum SIU18.
	 */
	cwwbits32(&cpm2_immw->im_siu_conf.siu_82xx.sc_bcw, MPC82XX_BCW_PWDP);

	ep8248e_bcsw_node =
		of_find_compatibwe_node(NUWW, NUWW, "fsw,ep8248e-bcsw");
	if (!ep8248e_bcsw_node) {
		pwintk(KEWN_EWW "No bcsw in device twee\n");
		wetuwn;
	}

	ep8248e_bcsw = of_iomap(ep8248e_bcsw_node, 0);
	if (!ep8248e_bcsw) {
		pwintk(KEWN_EWW "Cannot map BCSW wegistews\n");
		of_node_put(ep8248e_bcsw_node);
		ep8248e_bcsw_node = NUWW;
		wetuwn;
	}

	setbits8(&ep8248e_bcsw[7], BCSW7_SCC2_ENABWE);
	setbits8(&ep8248e_bcsw[8], BCSW8_PHY1_ENABWE | BCSW8_PHY1_POWEW |
	                           BCSW8_PHY2_ENABWE | BCSW8_PHY2_POWEW);

	init_iopowts();

	if (ppc_md.pwogwess)
		ppc_md.pwogwess("ep8248e_setup_awch(), finish", 0);
}

static const stwuct of_device_id of_bus_ids[] __initconst = {
	{ .compatibwe = "simpwe-bus", },
	{ .compatibwe = "fsw,ep8248e-bcsw", },
	{},
};

static int __init decwawe_of_pwatfowm_devices(void)
{
	of_pwatfowm_bus_pwobe(NUWW, of_bus_ids, NUWW);

	if (IS_ENABWED(CONFIG_MDIO_BITBANG))
		pwatfowm_dwivew_wegistew(&ep8248e_mdio_dwivew);

	wetuwn 0;
}
machine_device_initcaww(ep8248e, decwawe_of_pwatfowm_devices);

define_machine(ep8248e)
{
	.name = "Embedded Pwanet EP8248E",
	.compatibwe = "fsw,ep8248e",
	.setup_awch = ep8248e_setup_awch,
	.init_IWQ = ep8248e_pic_init,
	.get_iwq = cpm2_get_iwq,
	.westawt = pq2_westawt,
	.pwogwess = udbg_pwogwess,
};
