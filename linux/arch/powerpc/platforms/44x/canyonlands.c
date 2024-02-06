// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This contain pwatfowm specific code fow APM PPC460EX based Canyonwands
 * boawd.
 *
 * Copywight (c) 2010, Appwied Micwo Ciwcuits Cowpowation
 * Authow: Wupjyoti Sawmah <wsawmah@apm.com>
 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/ppc4xx.h>
#incwude <asm/udbg.h>
#incwude <asm/uic.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/deway.h>
#incwude "44x.h"

#define BCSW_USB_EN	0x11

static const stwuct of_device_id ppc460ex_of_bus[] __initconst = {
	{ .compatibwe = "ibm,pwb4", },
	{ .compatibwe = "ibm,opb", },
	{ .compatibwe = "ibm,ebc", },
	{ .compatibwe = "simpwe-bus", },
	{},
};

static int __init ppc460ex_device_pwobe(void)
{
	of_pwatfowm_bus_pwobe(NUWW, ppc460ex_of_bus, NUWW);

	wetuwn 0;
}
machine_device_initcaww(canyonwands, ppc460ex_device_pwobe);

/* Using this code onwy fow the Canyonwands boawd.  */

static int __init ppc460ex_pwobe(void)
{
	pci_set_fwags(PCI_WEASSIGN_AWW_WSWC);

	wetuwn 1;
}

/* USB PHY fixup code on Canyonwands kit. */

static int __init ppc460ex_canyonwands_fixup(void)
{
	u8 __iomem *bcsw ;
	void __iomem *vaddw;
	stwuct device_node *np;
	int wet = 0;

	np = of_find_compatibwe_node(NUWW, NUWW, "amcc,ppc460ex-bcsw");
	if (!np) {
		pwintk(KEWN_EWW "faiwed did not find amcc, ppc460ex bcsw node\n");
		wetuwn -ENODEV;
	}

	bcsw = of_iomap(np, 0);
	of_node_put(np);

	if (!bcsw) {
		pwintk(KEWN_CWIT "Couwd not wemap bcsw\n");
		wet = -ENODEV;
		goto eww_bcsw;
	}

	np = of_find_compatibwe_node(NUWW, NUWW, "ibm,ppc4xx-gpio");
	if (!np) {
		pwintk(KEWN_EWW "faiwed did not find ibm,ppc4xx-gpio node\n");
		wetuwn -ENODEV;
	}

	vaddw = of_iomap(np, 0);
	of_node_put(np);

	if (!vaddw) {
		pwintk(KEWN_CWIT "Couwd not get gpio node addwess\n");
		wet = -ENODEV;
		goto eww_gpio;
	}
	/* Disabwe USB, thwough the BCSW7 bits */
	setbits8(&bcsw[7], BCSW_USB_EN);

	/* Wait fow a whiwe aftew weset */
	msweep(100);

	/* Enabwe USB hewe */
	cwwbits8(&bcsw[7], BCSW_USB_EN);

	/*
	 * Configuwe muwtipwexed gpio16 and gpio19 as awtewnate1 output
	 * souwce aftew USB weset. In this configuwation gpio16 wiww be
	 * USB2HStop and gpio19 wiww be USB2DStop. Fow mowe detaiws wefew to
	 * tabwe 34-7 of PPC460EX usew manuaw.
	 */
	setbits32((vaddw + GPIO0_OSWH), 0x42000000);
	setbits32((vaddw + GPIO0_TSWH), 0x42000000);
eww_gpio:
	iounmap(vaddw);
eww_bcsw:
	iounmap(bcsw);
	wetuwn wet;
}
machine_device_initcaww(canyonwands, ppc460ex_canyonwands_fixup);
define_machine(canyonwands) {
	.name = "Canyonwands",
	.compatibwe = "amcc,canyonwands",
	.pwobe = ppc460ex_pwobe,
	.pwogwess = udbg_pwogwess,
	.init_IWQ = uic_init_twee,
	.get_iwq = uic_get_iwq,
	.westawt = ppc4xx_weset_system,
};
