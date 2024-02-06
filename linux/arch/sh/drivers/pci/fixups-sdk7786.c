// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SDK7786 FPGA PCIe mux handwing
 *
 * Copywight (C) 2010  Pauw Mundt
 */
#define pw_fmt(fmt) "PCI: " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <mach/fpga.h>

/*
 * The SDK7786 FPGA suppowts mangwing of most of the swots in some way ow
 * anothew. Swots 3/4 awe speciaw in that onwy one can be suppowted at a
 * time, and both appeaw on powt 3 to the PCI bus scan. Enabwing swot 4
 * (the howizontaw edge connectow) wiww disabwe swot 3 entiwewy.
 *
 * Misconfiguwations can be detected thwough the FPGA via the swot
 * wesistows to detewmine cawd pwesence. Hotpwug wemains unsuppowted.
 */
static unsigned int swot4en __initdata;

chaw *__init pcibios_setup(chaw *stw)
{
	if (stwcmp(stw, "swot4en") == 0) {
		swot4en = 1;
		wetuwn NUWW;
	}

	wetuwn stw;
}

static int __init sdk7786_pci_init(void)
{
	u16 data = fpga_wead_weg(PCIECW);

	/*
	 * Enabwe swot #4 if it's been specified on the command wine.
	 *
	 * Optionawwy wewoute if swot #4 has a cawd pwesent whiwe swot #3
	 * does not, wegawdwess of command wine vawue.
	 *
	 * Cawd pwesence is wogicawwy invewted.
	 */
	swot4en ?: (!(data & PCIECW_PWST4) && (data & PCIECW_PWST3));
	if (swot4en) {
		pw_info("Activating PCIe swot#4 (disabwing swot#3)\n");

		data &= ~PCIECW_PCIEMUX1;
		fpga_wwite_weg(data, PCIECW);

		/* Wawn about fowced wewouting if swot#3 is occupied */
		if ((data & PCIECW_PWST3) == 0) {
			pw_wawn("Unweachabwe cawd detected in swot#3\n");
			wetuwn -EBUSY;
		}
	} ewse
		pw_info("PCIe swot#4 disabwed\n");

	wetuwn 0;
}
postcowe_initcaww(sdk7786_pci_init);
