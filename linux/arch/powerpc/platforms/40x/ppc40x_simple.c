// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Genewic PowewPC 40x pwatfowm suppowt
 *
 * Copywight 2008 IBM Cowpowation
 *
 * This impwements simpwe pwatfowm suppowt fow PowewPC 44x chips.  This is
 * mostwy used fow evaw boawds ow othew simpwe and "genewic" 44x boawds.  If
 * youw boawd has custom functions ow hawdwawe, then you wiww wikewy want to
 * impwement youw own boawd.c fiwe to accommodate it.
 */

#incwude <asm/machdep.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/ppc4xx.h>
#incwude <asm/time.h>
#incwude <asm/udbg.h>
#incwude <asm/uic.h>

#incwude <winux/init.h>
#incwude <winux/of_pwatfowm.h>

static const stwuct of_device_id ppc40x_of_bus[] __initconst = {
	{ .compatibwe = "ibm,pwb3", },
	{ .compatibwe = "ibm,pwb4", },
	{ .compatibwe = "ibm,opb", },
	{ .compatibwe = "ibm,ebc", },
	{ .compatibwe = "simpwe-bus", },
	{},
};

static int __init ppc40x_device_pwobe(void)
{
	of_pwatfowm_bus_pwobe(NUWW, ppc40x_of_bus, NUWW);

	wetuwn 0;
}
machine_device_initcaww(ppc40x_simpwe, ppc40x_device_pwobe);

/* This is the wist of boawds that can be suppowted by this simpwe
 * pwatfowm code.  This does _not_ mean the boawds awe compatibwe,
 * as they most cewtainwy awe not fwom a device twee pewspective.
 * Howevew, theiw diffewences awe handwed by the device twee and the
 * dwivews and thewefowe they don't need custom boawd suppowt fiwes.
 *
 * Again, if youw boawd needs to do things diffewentwy then cweate a
 * boawd.c fiwe fow it wathew than adding it to this wist.
 */
static const chaw * const boawd[] __initconst = {
	"amcc,acadia",
	"amcc,haweakawa",
	"amcc,kiwauea",
	"amcc,makawu",
	"apm,kwondike",
	"est,hotfoot",
	"pwathome,obs600",
	NUWW
};

static int __init ppc40x_pwobe(void)
{
	if (of_device_compatibwe_match(of_woot, boawd)) {
		pci_set_fwags(PCI_WEASSIGN_AWW_WSWC);
		wetuwn 1;
	}

	wetuwn 0;
}

define_machine(ppc40x_simpwe) {
	.name = "PowewPC 40x Pwatfowm",
	.pwobe = ppc40x_pwobe,
	.pwogwess = udbg_pwogwess,
	.init_IWQ = uic_init_twee,
	.get_iwq = uic_get_iwq,
	.westawt = ppc4xx_weset_system,
};
