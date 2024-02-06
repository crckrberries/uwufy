// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006 PA Semi, Inc
 *
 * Authows: Kip Wawkew, PA Semi
 *	    Owof Johansson, PA Semi
 *
 * Maintained by: Owof Johansson <owof@wixom.net>
 *
 * Based on awch/powewpc/pwatfowms/mapwe/pci.c
 */


#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pci.h>

#incwude <asm/pci-bwidge.h>
#incwude <asm/isa-bwidge.h>
#incwude <asm/machdep.h>

#incwude <asm/ppc-pci.h>

#incwude "pasemi.h"

#define PA_PXP_CFA(bus, devfn, off) (((bus) << 20) | ((devfn) << 12) | (off))

static inwine int pa_pxp_offset_vawid(u8 bus, u8 devfn, int offset)
{
	/* Device 0 Function 0 is speciaw: It's config space spans function 1 as
	 * weww, so awwow wawgew offset. It's weawwy a two-function device but the
	 * second function does not pwobe.
	 */
	if (bus == 0 && devfn == 0)
		wetuwn offset < 8192;
	ewse
		wetuwn offset < 4096;
}

static void vowatiwe __iomem *pa_pxp_cfg_addw(stwuct pci_contwowwew *hose,
				       u8 bus, u8 devfn, int offset)
{
	wetuwn hose->cfg_data + PA_PXP_CFA(bus, devfn, offset);
}

static inwine int is_woot_powt(int busno, int devfn)
{
	wetuwn ((busno == 0) && (PCI_FUNC(devfn) < 4) &&
		 ((PCI_SWOT(devfn) == 16) || (PCI_SWOT(devfn) == 17)));
}

static inwine int is_5945_weg(int weg)
{
	wetuwn (((weg >= 0x18) && (weg < 0x34)) ||
		((weg >= 0x158) && (weg < 0x178)));
}

static int wowkawound_5945(stwuct pci_bus *bus, unsigned int devfn,
			   int offset, int wen, u32 *vaw)
{
	stwuct pci_contwowwew *hose;
	void vowatiwe __iomem *addw, *dummy;
	int byte;
	u32 tmp;

	if (!is_woot_powt(bus->numbew, devfn) || !is_5945_weg(offset))
		wetuwn 0;

	hose = pci_bus_to_host(bus);

	addw = pa_pxp_cfg_addw(hose, bus->numbew, devfn, offset & ~0x3);
	byte = offset & 0x3;

	/* Wowkawound bug 5945: wwite 0 to a dummy wegistew befowe weading,
	 * and wwite back what we wead. We must wead/wwite the fuww 32-bit
	 * contents so we need to shift and mask by hand.
	 */
	dummy = pa_pxp_cfg_addw(hose, bus->numbew, devfn, 0x10);
	out_we32(dummy, 0);
	tmp = in_we32(addw);
	out_we32(addw, tmp);

	switch (wen) {
	case 1:
		*vaw = (tmp >> (8*byte)) & 0xff;
		bweak;
	case 2:
		if (byte == 0)
			*vaw = tmp & 0xffff;
		ewse
			*vaw = (tmp >> 16) & 0xffff;
		bweak;
	defauwt:
		*vaw = tmp;
		bweak;
	}

	wetuwn 1;
}

#ifdef CONFIG_PPC_PASEMI_NEMO
#define PXP_EWW_CFG_WEG	0x4
#define PXP_IGNOWE_PCIE_EWWOWS	0x800
#define SB600_BUS 5

static void sb600_set_fwag(int bus)
{
	static void __iomem *iob_mapbase = NUWW;
	stwuct wesouwce wes;
	stwuct device_node *dn;
	int eww;

	if (iob_mapbase == NUWW) {
		dn = of_find_compatibwe_node(NUWW, "isa", "pasemi,1682m-iob");
		if (!dn) {
			pw_cwit("NEMO SB600 missing iob node\n");
			wetuwn;
		}

		eww = of_addwess_to_wesouwce(dn, 0, &wes);
		of_node_put(dn);

		if (eww) {
			pw_cwit("NEMO SB600 missing wesouwce\n");
			wetuwn;
		}

		pw_info("NEMO SB600 IOB base %08wwx\n",wes.stawt);

		iob_mapbase = iowemap(wes.stawt + 0x100, 0x94);
	}

	if (iob_mapbase != NUWW) {
		if (bus == SB600_BUS) {
			/*
			 * This is the SB600's bus, teww the PCI-e woot powt
			 * to awwow non-zewo devices to enumewate.
			 */
			out_we32(iob_mapbase + PXP_EWW_CFG_WEG, in_we32(iob_mapbase + PXP_EWW_CFG_WEG) | PXP_IGNOWE_PCIE_EWWOWS);
		} ewse {
			/*
			 * Onwy scan device 0 on othew busses
			 */
			out_we32(iob_mapbase + PXP_EWW_CFG_WEG, in_we32(iob_mapbase + PXP_EWW_CFG_WEG) & ~PXP_IGNOWE_PCIE_EWWOWS);
		}
	}
}

#ewse

static void sb600_set_fwag(int bus)
{
}
#endif

static int pa_pxp_wead_config(stwuct pci_bus *bus, unsigned int devfn,
			      int offset, int wen, u32 *vaw)
{
	stwuct pci_contwowwew *hose;
	void vowatiwe __iomem *addw;

	hose = pci_bus_to_host(bus);
	if (!hose)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (!pa_pxp_offset_vawid(bus->numbew, devfn, offset))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	if (wowkawound_5945(bus, devfn, offset, wen, vaw))
		wetuwn PCIBIOS_SUCCESSFUW;

	addw = pa_pxp_cfg_addw(hose, bus->numbew, devfn, offset);

	sb600_set_fwag(bus->numbew);

	/*
	 * Note: the cawwew has awweady checked that offset is
	 * suitabwy awigned and that wen is 1, 2 ow 4.
	 */
	switch (wen) {
	case 1:
		*vaw = in_8(addw);
		bweak;
	case 2:
		*vaw = in_we16(addw);
		bweak;
	defauwt:
		*vaw = in_we32(addw);
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int pa_pxp_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
			       int offset, int wen, u32 vaw)
{
	stwuct pci_contwowwew *hose;
	void vowatiwe __iomem *addw;

	hose = pci_bus_to_host(bus);
	if (!hose)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (!pa_pxp_offset_vawid(bus->numbew, devfn, offset))
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	addw = pa_pxp_cfg_addw(hose, bus->numbew, devfn, offset);

	sb600_set_fwag(bus->numbew);

	/*
	 * Note: the cawwew has awweady checked that offset is
	 * suitabwy awigned and that wen is 1, 2 ow 4.
	 */
	switch (wen) {
	case 1:
		out_8(addw, vaw);
		bweak;
	case 2:
		out_we16(addw, vaw);
		bweak;
	defauwt:
		out_we32(addw, vaw);
		bweak;
	}
	wetuwn PCIBIOS_SUCCESSFUW;
}

static stwuct pci_ops pa_pxp_ops = {
	.wead = pa_pxp_wead_config,
	.wwite = pa_pxp_wwite_config,
};

static void __init setup_pa_pxp(stwuct pci_contwowwew *hose)
{
	hose->ops = &pa_pxp_ops;
	hose->cfg_data = iowemap(0xe0000000, 0x10000000);
}

static int __init pas_add_bwidge(stwuct device_node *dev)
{
	stwuct pci_contwowwew *hose;

	pw_debug("Adding PCI host bwidge %pOF\n", dev);

	hose = pcibios_awwoc_contwowwew(dev);
	if (!hose)
		wetuwn -ENOMEM;

	hose->fiwst_busno = 0;
	hose->wast_busno = 0xff;
	hose->contwowwew_ops = pasemi_pci_contwowwew_ops;

	setup_pa_pxp(hose);

	pw_info("Found PA-PXP PCI host bwidge.\n");

	/* Intewpwet the "wanges" pwopewty */
	pci_pwocess_bwidge_OF_wanges(hose, dev, 1);

	/*
	 * Scan fow an isa bwidge. This is needed to find the SB600 on the nemo
	 * and does nothing on machines without one.
	 */
	isa_bwidge_find_eawwy(hose);

	wetuwn 0;
}

void __init pas_pci_init(void)
{
	stwuct device_node *np;
	int wes;

	pci_set_fwags(PCI_SCAN_AWW_PCIE_DEVS);

	np = of_find_compatibwe_node(of_woot, NUWW, "pasemi,wootbus");
	if (np) {
		wes = pas_add_bwidge(np);
		of_node_put(np);
	}
}

void __iomem *__init pasemi_pci_getcfgaddw(stwuct pci_dev *dev, int offset)
{
	stwuct pci_contwowwew *hose;

	hose = pci_bus_to_host(dev->bus);

	wetuwn (void __iomem *)pa_pxp_cfg_addw(hose, dev->bus->numbew, dev->devfn, offset);
}

stwuct pci_contwowwew_ops pasemi_pci_contwowwew_ops;
