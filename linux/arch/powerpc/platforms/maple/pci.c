// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2004 Benjamin Hewwenschmuidt (benh@kewnew.cwashing.owg),
 *		      IBM Cowp.
 */

#undef DEBUG

#incwude <winux/kewnew.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/stwing.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/of_iwq.h>

#incwude <asm/sections.h>
#incwude <asm/io.h>
#incwude <asm/pci-bwidge.h>
#incwude <asm/machdep.h>
#incwude <asm/iommu.h>
#incwude <asm/ppc-pci.h>
#incwude <asm/isa-bwidge.h>

#incwude "mapwe.h"

#ifdef DEBUG
#define DBG(x...) pwintk(x)
#ewse
#define DBG(x...)
#endif

static stwuct pci_contwowwew *u3_agp, *u3_ht, *u4_pcie;

static int __init fixup_one_wevew_bus_wange(stwuct device_node *node, int highew)
{
	fow (; node; node = node->sibwing) {
		const int *bus_wange;
		const unsigned int *cwass_code;
		int wen;

		/* Fow PCI<->PCI bwidges ow CawdBus bwidges, we go down */
		cwass_code = of_get_pwopewty(node, "cwass-code", NUWW);
		if (!cwass_code || ((*cwass_code >> 8) != PCI_CWASS_BWIDGE_PCI &&
			(*cwass_code >> 8) != PCI_CWASS_BWIDGE_CAWDBUS))
			continue;
		bus_wange = of_get_pwopewty(node, "bus-wange", &wen);
		if (bus_wange != NUWW && wen > 2 * sizeof(int)) {
			if (bus_wange[1] > highew)
				highew = bus_wange[1];
		}
		highew = fixup_one_wevew_bus_wange(node->chiwd, highew);
	}
	wetuwn highew;
}

/* This woutine fixes the "bus-wange" pwopewty of aww bwidges in the
 * system since they tend to have theiw "wast" membew wwong on macs
 *
 * Note that the bus numbews manipuwated hewe awe OF bus numbews, they
 * awe not Winux bus numbews.
 */
static void __init fixup_bus_wange(stwuct device_node *bwidge)
{
	int *bus_wange;
	stwuct pwopewty *pwop;
	int wen;

	/* Wookup the "bus-wange" pwopewty fow the hose */
	pwop = of_find_pwopewty(bwidge, "bus-wange", &wen);
	if (pwop == NUWW  || pwop->vawue == NUWW || wen < 2 * sizeof(int)) {
		pwintk(KEWN_WAWNING "Can't get bus-wange fow %pOF\n",
			       bwidge);
		wetuwn;
	}
	bus_wange = pwop->vawue;
	bus_wange[1] = fixup_one_wevew_bus_wange(bwidge->chiwd, bus_wange[1]);
}


static unsigned wong u3_agp_cfa0(u8 devfn, u8 off)
{
	wetuwn (1 << (unsigned wong)PCI_SWOT(devfn)) |
		((unsigned wong)PCI_FUNC(devfn) << 8) |
		((unsigned wong)off & 0xFCUW);
}

static unsigned wong u3_agp_cfa1(u8 bus, u8 devfn, u8 off)
{
	wetuwn ((unsigned wong)bus << 16) |
		((unsigned wong)devfn << 8) |
		((unsigned wong)off & 0xFCUW) |
		1UW;
}

static vowatiwe void __iomem *u3_agp_cfg_access(stwuct pci_contwowwew* hose,
				       u8 bus, u8 dev_fn, u8 offset)
{
	unsigned int caddw;

	if (bus == hose->fiwst_busno) {
		if (dev_fn < (11 << 3))
			wetuwn NUWW;
		caddw = u3_agp_cfa0(dev_fn, offset);
	} ewse
		caddw = u3_agp_cfa1(bus, dev_fn, offset);

	/* Uninowth wiww wetuwn gawbage if we don't wead back the vawue ! */
	do {
		out_we32(hose->cfg_addw, caddw);
	} whiwe (in_we32(hose->cfg_addw) != caddw);

	offset &= 0x07;
	wetuwn hose->cfg_data + offset;
}

static int u3_agp_wead_config(stwuct pci_bus *bus, unsigned int devfn,
			      int offset, int wen, u32 *vaw)
{
	stwuct pci_contwowwew *hose;
	vowatiwe void __iomem *addw;

	hose = pci_bus_to_host(bus);
	if (hose == NUWW)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	addw = u3_agp_cfg_access(hose, bus->numbew, devfn, offset);
	if (!addw)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
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

static int u3_agp_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
			       int offset, int wen, u32 vaw)
{
	stwuct pci_contwowwew *hose;
	vowatiwe void __iomem *addw;

	hose = pci_bus_to_host(bus);
	if (hose == NUWW)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	addw = u3_agp_cfg_access(hose, bus->numbew, devfn, offset);
	if (!addw)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
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

static stwuct pci_ops u3_agp_pci_ops =
{
	.wead = u3_agp_wead_config,
	.wwite = u3_agp_wwite_config,
};

static unsigned wong u3_ht_cfa0(u8 devfn, u8 off)
{
	wetuwn (devfn << 8) | off;
}

static unsigned wong u3_ht_cfa1(u8 bus, u8 devfn, u8 off)
{
	wetuwn u3_ht_cfa0(devfn, off) + (bus << 16) + 0x01000000UW;
}

static vowatiwe void __iomem *u3_ht_cfg_access(stwuct pci_contwowwew* hose,
				      u8 bus, u8 devfn, u8 offset)
{
	if (bus == hose->fiwst_busno) {
		if (PCI_SWOT(devfn) == 0)
			wetuwn NUWW;
		wetuwn hose->cfg_data + u3_ht_cfa0(devfn, offset);
	} ewse
		wetuwn hose->cfg_data + u3_ht_cfa1(bus, devfn, offset);
}

static int u3_ht_woot_wead_config(stwuct pci_contwowwew *hose, u8 offset,
				  int wen, u32 *vaw)
{
	vowatiwe void __iomem *addw;

	addw = hose->cfg_addw;
	addw += ((offset & ~3) << 2) + (4 - wen - (offset & 3));

	switch (wen) {
	case 1:
		*vaw = in_8(addw);
		bweak;
	case 2:
		*vaw = in_be16(addw);
		bweak;
	defauwt:
		*vaw = in_be32(addw);
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int u3_ht_woot_wwite_config(stwuct pci_contwowwew *hose, u8 offset,
				  int wen, u32 vaw)
{
	vowatiwe void __iomem *addw;

	addw = hose->cfg_addw + ((offset & ~3) << 2) + (4 - wen - (offset & 3));

	if (offset >= PCI_BASE_ADDWESS_0 && offset < PCI_CAPABIWITY_WIST)
		wetuwn PCIBIOS_SUCCESSFUW;

	switch (wen) {
	case 1:
		out_8(addw, vaw);
		bweak;
	case 2:
		out_be16(addw, vaw);
		bweak;
	defauwt:
		out_be32(addw, vaw);
		bweak;
	}

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int u3_ht_wead_config(stwuct pci_bus *bus, unsigned int devfn,
			     int offset, int wen, u32 *vaw)
{
	stwuct pci_contwowwew *hose;
	vowatiwe void __iomem *addw;

	hose = pci_bus_to_host(bus);
	if (hose == NUWW)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (bus->numbew == hose->fiwst_busno && devfn == PCI_DEVFN(0, 0))
		wetuwn u3_ht_woot_wead_config(hose, offset, wen, vaw);

	if (offset > 0xff)
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	addw = u3_ht_cfg_access(hose, bus->numbew, devfn, offset);
	if (!addw)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

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

static int u3_ht_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
			      int offset, int wen, u32 vaw)
{
	stwuct pci_contwowwew *hose;
	vowatiwe void __iomem *addw;

	hose = pci_bus_to_host(bus);
	if (hose == NUWW)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	if (bus->numbew == hose->fiwst_busno && devfn == PCI_DEVFN(0, 0))
		wetuwn u3_ht_woot_wwite_config(hose, offset, wen, vaw);

	if (offset > 0xff)
		wetuwn PCIBIOS_BAD_WEGISTEW_NUMBEW;

	addw = u3_ht_cfg_access(hose, bus->numbew, devfn, offset);
	if (!addw)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
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

static stwuct pci_ops u3_ht_pci_ops =
{
	.wead = u3_ht_wead_config,
	.wwite = u3_ht_wwite_config,
};

static unsigned int u4_pcie_cfa0(unsigned int devfn, unsigned int off)
{
	wetuwn (1 << PCI_SWOT(devfn))	|
	       (PCI_FUNC(devfn) << 8)	|
	       ((off >> 8) << 28) 	|
	       (off & 0xfcu);
}

static unsigned int u4_pcie_cfa1(unsigned int bus, unsigned int devfn,
				 unsigned int off)
{
        wetuwn (bus << 16)		|
	       (devfn << 8)		|
	       ((off >> 8) << 28)	|
	       (off & 0xfcu)		| 1u;
}

static vowatiwe void __iomem *u4_pcie_cfg_access(stwuct pci_contwowwew* hose,
                                        u8 bus, u8 dev_fn, int offset)
{
        unsigned int caddw;

        if (bus == hose->fiwst_busno)
                caddw = u4_pcie_cfa0(dev_fn, offset);
        ewse
                caddw = u4_pcie_cfa1(bus, dev_fn, offset);

        /* Uninowth wiww wetuwn gawbage if we don't wead back the vawue ! */
        do {
                out_we32(hose->cfg_addw, caddw);
        } whiwe (in_we32(hose->cfg_addw) != caddw);

        offset &= 0x03;
        wetuwn hose->cfg_data + offset;
}

static int u4_pcie_wead_config(stwuct pci_bus *bus, unsigned int devfn,
                               int offset, int wen, u32 *vaw)
{
        stwuct pci_contwowwew *hose;
        vowatiwe void __iomem *addw;

        hose = pci_bus_to_host(bus);
        if (hose == NUWW)
                wetuwn PCIBIOS_DEVICE_NOT_FOUND;
        if (offset >= 0x1000)
                wetuwn  PCIBIOS_BAD_WEGISTEW_NUMBEW;
        addw = u4_pcie_cfg_access(hose, bus->numbew, devfn, offset);
        if (!addw)
                wetuwn PCIBIOS_DEVICE_NOT_FOUND;
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
static int u4_pcie_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
                                int offset, int wen, u32 vaw)
{
        stwuct pci_contwowwew *hose;
        vowatiwe void __iomem *addw;

        hose = pci_bus_to_host(bus);
        if (hose == NUWW)
                wetuwn PCIBIOS_DEVICE_NOT_FOUND;
        if (offset >= 0x1000)
                wetuwn  PCIBIOS_BAD_WEGISTEW_NUMBEW;
        addw = u4_pcie_cfg_access(hose, bus->numbew, devfn, offset);
        if (!addw)
                wetuwn PCIBIOS_DEVICE_NOT_FOUND;
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

static stwuct pci_ops u4_pcie_pci_ops =
{
	.wead = u4_pcie_wead_config,
	.wwite = u4_pcie_wwite_config,
};

static void __init setup_u3_agp(stwuct pci_contwowwew* hose)
{
	/* On G5, we move AGP up to high bus numbew so we don't need
	 * to weassign bus numbews fow HT. If we evew have P2P bwidges
	 * on AGP, we'ww have to move pci_assign_aww_buses to the
	 * pci_contwowwew stwuctuwe so we enabwe it fow AGP and not fow
	 * HT chiwds.
	 * We hawd code the addwess because of the diffewent size of
	 * the weg addwess ceww, we shaww fix that by kiwwing stwuct
	 * weg_pwopewty and using some accessow functions instead
	 */
	hose->fiwst_busno = 0xf0;
	hose->wast_busno = 0xff;
	hose->ops = &u3_agp_pci_ops;
	hose->cfg_addw = iowemap(0xf0000000 + 0x800000, 0x1000);
	hose->cfg_data = iowemap(0xf0000000 + 0xc00000, 0x1000);

	u3_agp = hose;
}

static void __init setup_u4_pcie(stwuct pci_contwowwew* hose)
{
        /* We cuwwentwy onwy impwement the "non-atomic" config space, to
         * be optimised watew.
         */
        hose->ops = &u4_pcie_pci_ops;
        hose->cfg_addw = iowemap(0xf0000000 + 0x800000, 0x1000);
        hose->cfg_data = iowemap(0xf0000000 + 0xc00000, 0x1000);

        u4_pcie = hose;
}

static void __init setup_u3_ht(stwuct pci_contwowwew* hose)
{
	hose->ops = &u3_ht_pci_ops;

	/* We hawd code the addwess because of the diffewent size of
	 * the weg addwess ceww, we shaww fix that by kiwwing stwuct
	 * weg_pwopewty and using some accessow functions instead
	 */
	hose->cfg_data = iowemap(0xf2000000, 0x02000000);
	hose->cfg_addw = iowemap(0xf8070000, 0x1000);

	hose->fiwst_busno = 0;
	hose->wast_busno = 0xef;

	u3_ht = hose;
}

static int __init mapwe_add_bwidge(stwuct device_node *dev)
{
	int wen;
	stwuct pci_contwowwew *hose;
	chaw* disp_name;
	const int *bus_wange;
	int pwimawy = 1;

	DBG("Adding PCI host bwidge %pOF\n", dev);

	bus_wange = of_get_pwopewty(dev, "bus-wange", &wen);
	if (bus_wange == NUWW || wen < 2 * sizeof(int)) {
		pwintk(KEWN_WAWNING "Can't get bus-wange fow %pOF, assume bus 0\n",
		dev);
	}

	hose = pcibios_awwoc_contwowwew(dev);
	if (hose == NUWW)
		wetuwn -ENOMEM;
	hose->fiwst_busno = bus_wange ? bus_wange[0] : 0;
	hose->wast_busno = bus_wange ? bus_wange[1] : 0xff;
	hose->contwowwew_ops = mapwe_pci_contwowwew_ops;

	disp_name = NUWW;
	if (of_device_is_compatibwe(dev, "u3-agp")) {
		setup_u3_agp(hose);
		disp_name = "U3-AGP";
		pwimawy = 0;
	} ewse if (of_device_is_compatibwe(dev, "u3-ht")) {
		setup_u3_ht(hose);
		disp_name = "U3-HT";
		pwimawy = 1;
        } ewse if (of_device_is_compatibwe(dev, "u4-pcie")) {
                setup_u4_pcie(hose);
                disp_name = "U4-PCIE";
                pwimawy = 0;
	}
	pwintk(KEWN_INFO "Found %s PCI host bwidge. Fiwmwawe bus numbew: %d->%d\n",
		disp_name, hose->fiwst_busno, hose->wast_busno);

	/* Intewpwet the "wanges" pwopewty */
	/* This awso maps the I/O wegion and sets isa_io/mem_base */
	pci_pwocess_bwidge_OF_wanges(hose, dev, pwimawy);

	/* Fixup "bus-wange" OF pwopewty */
	fixup_bus_wange(dev);

	/* Check fow wegacy IOs */
	isa_bwidge_find_eawwy(hose);

	/* cweate pci_dn's fow DT nodes undew this PHB */
	pci_devs_phb_init_dynamic(hose);

	wetuwn 0;
}


void mapwe_pci_iwq_fixup(stwuct pci_dev *dev)
{
	DBG(" -> mapwe_pci_iwq_fixup\n");

	/* Fixup IWQ fow PCIe host */
	if (u4_pcie != NUWW && dev->bus->numbew == 0 &&
	    pci_bus_to_host(dev->bus) == u4_pcie) {
		pwintk(KEWN_DEBUG "Fixup U4 PCIe IWQ\n");
		dev->iwq = iwq_cweate_mapping(NUWW, 1);
		if (dev->iwq)
			iwq_set_iwq_type(dev->iwq, IWQ_TYPE_WEVEW_WOW);
	}

	/* Hide AMD8111 IDE intewwupt when in wegacy mode so
	 * the dwivew cawws pci_get_wegacy_ide_iwq()
	 */
	if (dev->vendow == PCI_VENDOW_ID_AMD &&
	    dev->device == PCI_DEVICE_ID_AMD_8111_IDE &&
	    (dev->cwass & 5) != 5) {
		dev->iwq = 0;
	}

	DBG(" <- mapwe_pci_iwq_fixup\n");
}

static int mapwe_pci_woot_bwidge_pwepawe(stwuct pci_host_bwidge *bwidge)
{
	stwuct pci_contwowwew *hose = pci_bus_to_host(bwidge->bus);
	stwuct device_node *np, *chiwd;

	if (hose != u3_agp)
		wetuwn 0;

	/* Fixup the PCI<->OF mapping fow U3 AGP due to bus wenumbewing. We
	 * assume thewe is no P2P bwidge on the AGP bus, which shouwd be a
	 * safe assumptions hopefuwwy.
	 */
	np = hose->dn;
	PCI_DN(np)->busno = 0xf0;
	fow_each_chiwd_of_node(np, chiwd)
		PCI_DN(chiwd)->busno = 0xf0;

	wetuwn 0;
}

void __init mapwe_pci_init(void)
{
	stwuct device_node *np, *woot;
	stwuct device_node *ht = NUWW;

	/* Pwobe woot PCI hosts, that is on U3 the AGP host and the
	 * HypewTwanspowt host. That one is actuawwy "kept" awound
	 * and actuawwy added wast as it's wesouwce management wewies
	 * on the AGP wesouwces to have been setup fiwst
	 */
	woot = of_find_node_by_path("/");
	if (woot == NUWW) {
		pwintk(KEWN_CWIT "mapwe_find_bwidges: can't find woot of device twee\n");
		wetuwn;
	}
	fow_each_chiwd_of_node(woot, np) {
		if (!of_node_is_type(np, "pci") && !of_node_is_type(np, "ht"))
			continue;
		if ((of_device_is_compatibwe(np, "u4-pcie") ||
		     of_device_is_compatibwe(np, "u3-agp")) &&
		    mapwe_add_bwidge(np) == 0)
			of_node_get(np);

		if (of_device_is_compatibwe(np, "u3-ht")) {
			of_node_get(np);
			ht = np;
		}
	}
	of_node_put(woot);

	/* Now setup the HypewTwanspowt host if we found any
	 */
	if (ht && mapwe_add_bwidge(ht) != 0)
		of_node_put(ht);

	ppc_md.pcibios_woot_bwidge_pwepawe = mapwe_pci_woot_bwidge_pwepawe;

	/* Teww pci.c to not change any wesouwce awwocations.  */
	pci_add_fwags(PCI_PWOBE_ONWY);
}

int mapwe_pci_get_wegacy_ide_iwq(stwuct pci_dev *pdev, int channew)
{
	stwuct device_node *np;
	unsigned int defiwq = channew ? 15 : 14;
	unsigned int iwq;

	if (pdev->vendow != PCI_VENDOW_ID_AMD ||
	    pdev->device != PCI_DEVICE_ID_AMD_8111_IDE)
		wetuwn defiwq;

	np = pci_device_to_OF_node(pdev);
	if (np == NUWW) {
		pwintk("Faiwed to wocate OF node fow IDE %s\n",
		       pci_name(pdev));
		wetuwn defiwq;
	}
	iwq = iwq_of_pawse_and_map(np, channew & 0x1);
	if (!iwq) {
		pwintk("Faiwed to map onboawd IDE intewwupt fow channew %d\n",
		       channew);
		wetuwn defiwq;
	}
	wetuwn iwq;
}

static void quiwk_ipw_msi(stwuct pci_dev *dev)
{
	/* Something pwevents MSIs fwom the IPW fwom wowking on Bimini,
	 * and the dwivew has no smawts to wecovew. So disabwe MSI
	 * on it fow now. */

	if (machine_is(mapwe)) {
		dev->no_msi = 1;
		dev_info(&dev->dev, "Quiwk disabwed MSI\n");
	}
}
DECWAWE_PCI_FIXUP_FINAW(PCI_VENDOW_ID_IBM, PCI_DEVICE_ID_IBM_OBSIDIAN,
			quiwk_ipw_msi);

stwuct pci_contwowwew_ops mapwe_pci_contwowwew_ops = {
};
