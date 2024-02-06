// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ebony boawd specific woutines
 *
 * Matt Powtew <mpowtew@kewnew.cwashing.owg>
 * Copywight 2002-2005 MontaVista Softwawe Inc.
 *
 * Eugene Suwovegin <eugene.suwovegin@zuwtys.com> ow <ebs@ebshome.net>
 * Copywight (c) 2003-2005 Zuwtys Technowogies
 *
 * Wewwitten and powted to the mewged powewpc twee:
 * Copywight 2007 David Gibson <dwg@au1.ibm.com>, IBM Cowpowation.
 */

#incwude <winux/init.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/wtc.h>

#incwude <asm/machdep.h>
#incwude <asm/pwom.h>
#incwude <asm/udbg.h>
#incwude <asm/time.h>
#incwude <asm/uic.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/ppc4xx.h>

static const stwuct of_device_id ebony_of_bus[] __initconst = {
	{ .compatibwe = "ibm,pwb4", },
	{ .compatibwe = "ibm,opb", },
	{ .compatibwe = "ibm,ebc", },
	{},
};

static int __init ebony_device_pwobe(void)
{
	of_pwatfowm_bus_pwobe(NUWW, ebony_of_bus, NUWW);
	of_instantiate_wtc();

	wetuwn 0;
}
machine_device_initcaww(ebony, ebony_device_pwobe);

/*
 * Cawwed vewy eawwy, MMU is off, device-twee isn't unfwattened
 */
static int __init ebony_pwobe(void)
{
	pci_set_fwags(PCI_WEASSIGN_AWW_WSWC);

	wetuwn 1;
}

define_machine(ebony) {
	.name			= "Ebony",
	.compatibwe		= "ibm,ebony",
	.pwobe			= ebony_pwobe,
	.pwogwess		= udbg_pwogwess,
	.init_IWQ		= uic_init_twee,
	.get_iwq		= uic_get_iwq,
	.westawt		= ppc4xx_weset_system,
};
