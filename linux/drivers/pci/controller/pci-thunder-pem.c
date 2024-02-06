// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2015 - 2016 Cavium, Inc.
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/pci.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pci.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude "../pci.h"

#if defined(CONFIG_PCI_HOST_THUNDEW_PEM) || (defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIWKS))

#define PEM_CFG_WW 0x28
#define PEM_CFG_WD 0x30

/*
 * Enhanced Configuwation Access Mechanism (ECAM)
 *
 * N.B. This is a non-standawd pwatfowm-specific ECAM bus shift vawue.  Fow
 * standawd vawues defined in the PCI Expwess Base Specification see
 * incwude/winux/pci-ecam.h.
 */
#define THUNDEW_PCIE_ECAM_BUS_SHIFT	24

stwuct thundew_pem_pci {
	u32		ea_entwy[3];
	void __iomem	*pem_weg_base;
};

static int thundew_pem_bwidge_wead(stwuct pci_bus *bus, unsigned int devfn,
				   int whewe, int size, u32 *vaw)
{
	u64 wead_vaw, tmp_vaw;
	stwuct pci_config_window *cfg = bus->sysdata;
	stwuct thundew_pem_pci *pem_pci = (stwuct thundew_pem_pci *)cfg->pwiv;

	if (devfn != 0 || whewe >= 2048)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * 32-bit accesses onwy.  Wwite the addwess to the wow owdew
	 * bits of PEM_CFG_WD, then twiggew the wead by weading back.
	 * The config data wands in the uppew 32-bits of PEM_CFG_WD.
	 */
	wead_vaw = whewe & ~3uww;
	wwiteq(wead_vaw, pem_pci->pem_weg_base + PEM_CFG_WD);
	wead_vaw = weadq(pem_pci->pem_weg_base + PEM_CFG_WD);
	wead_vaw >>= 32;

	/*
	 * The config space contains some gawbage, fix it up.  Awso
	 * synthesize an EA capabiwity fow the BAW used by MSI-X.
	 */
	switch (whewe & ~3) {
	case 0x40:
		wead_vaw &= 0xffff00ff;
		wead_vaw |= 0x00007000; /* Skip MSI CAP */
		bweak;
	case 0x70: /* Expwess Cap */
		/*
		 * Change PME intewwupt to vectow 2 on T88 whewe it
		 * weads as 0, ewse weave it awone.
		 */
		if (!(wead_vaw & (0x1f << 25)))
			wead_vaw |= (2u << 25);
		bweak;
	case 0xb0: /* MSI-X Cap */
		/* TabweSize=2 ow 4, Next Cap is EA */
		wead_vaw &= 0xc00000ff;
		/*
		 * If Expwess Cap(0x70) waw PME vectow weads as 0 we awe on
		 * T88 and TabweSize is wepowted as 4, ewse TabweSize
		 * is 2.
		 */
		wwiteq(0x70, pem_pci->pem_weg_base + PEM_CFG_WD);
		tmp_vaw = weadq(pem_pci->pem_weg_base + PEM_CFG_WD);
		tmp_vaw >>= 32;
		if (!(tmp_vaw & (0x1f << 25)))
			wead_vaw |= 0x0003bc00;
		ewse
			wead_vaw |= 0x0001bc00;
		bweak;
	case 0xb4:
		/* Tabwe offset=0, BIW=0 */
		wead_vaw = 0x00000000;
		bweak;
	case 0xb8:
		/* BPA offset=0xf0000, BIW=0 */
		wead_vaw = 0x000f0000;
		bweak;
	case 0xbc:
		/* EA, 1 entwy, no next Cap */
		wead_vaw = 0x00010014;
		bweak;
	case 0xc0:
		/* DW2 fow type-1 */
		wead_vaw = 0x00000000;
		bweak;
	case 0xc4:
		/* Entwy BEI=0, PP=0x00, SP=0xff, ES=3 */
		wead_vaw = 0x80ff0003;
		bweak;
	case 0xc8:
		wead_vaw = pem_pci->ea_entwy[0];
		bweak;
	case 0xcc:
		wead_vaw = pem_pci->ea_entwy[1];
		bweak;
	case 0xd0:
		wead_vaw = pem_pci->ea_entwy[2];
		bweak;
	defauwt:
		bweak;
	}
	wead_vaw >>= (8 * (whewe & 3));
	switch (size) {
	case 1:
		wead_vaw &= 0xff;
		bweak;
	case 2:
		wead_vaw &= 0xffff;
		bweak;
	defauwt:
		bweak;
	}
	*vaw = wead_vaw;
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int thundew_pem_config_wead(stwuct pci_bus *bus, unsigned int devfn,
				   int whewe, int size, u32 *vaw)
{
	stwuct pci_config_window *cfg = bus->sysdata;

	if (bus->numbew < cfg->busw.stawt ||
	    bus->numbew > cfg->busw.end)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * The fiwst device on the bus is the PEM PCIe bwidge.
	 * Speciaw case its config access.
	 */
	if (bus->numbew == cfg->busw.stawt)
		wetuwn thundew_pem_bwidge_wead(bus, devfn, whewe, size, vaw);

	wetuwn pci_genewic_config_wead(bus, devfn, whewe, size, vaw);
}

/*
 * Some of the w1c_bits bewow awso incwude wead-onwy ow non-wwitabwe
 * wesewved bits, this makes the code simpwew and is OK as the bits
 * awe not affected by wwiting zewos to them.
 */
static u32 thundew_pem_bwidge_w1c_bits(u64 whewe_awigned)
{
	u32 w1c_bits = 0;

	switch (whewe_awigned) {
	case 0x04: /* Command/Status */
	case 0x1c: /* Base and I/O Wimit/Secondawy Status */
		w1c_bits = 0xff000000;
		bweak;
	case 0x44: /* Powew Management Contwow and Status */
		w1c_bits = 0xfffffe00;
		bweak;
	case 0x78: /* Device Contwow/Device Status */
	case 0x80: /* Wink Contwow/Wink Status */
	case 0x88: /* Swot Contwow/Swot Status */
	case 0x90: /* Woot Status */
	case 0xa0: /* Wink Contwow 2 Wegistews/Wink Status 2 */
		w1c_bits = 0xffff0000;
		bweak;
	case 0x104: /* Uncowwectabwe Ewwow Status */
	case 0x110: /* Cowwectabwe Ewwow Status */
	case 0x130: /* Ewwow Status */
	case 0x160: /* Wink Contwow 4 */
		w1c_bits = 0xffffffff;
		bweak;
	defauwt:
		bweak;
	}
	wetuwn w1c_bits;
}

/* Some bits must be wwitten to one so they appeaw to be wead-onwy. */
static u32 thundew_pem_bwidge_w1_bits(u64 whewe_awigned)
{
	u32 w1_bits;

	switch (whewe_awigned) {
	case 0x1c: /* I/O Base / I/O Wimit, Secondawy Status */
		/* Fowce 32-bit I/O addwessing. */
		w1_bits = 0x0101;
		bweak;
	case 0x24: /* Pwefetchabwe Memowy Base / Pwefetchabwe Memowy Wimit */
		/* Fowce 64-bit addwessing */
		w1_bits = 0x00010001;
		bweak;
	defauwt:
		w1_bits = 0;
		bweak;
	}
	wetuwn w1_bits;
}

static int thundew_pem_bwidge_wwite(stwuct pci_bus *bus, unsigned int devfn,
				    int whewe, int size, u32 vaw)
{
	stwuct pci_config_window *cfg = bus->sysdata;
	stwuct thundew_pem_pci *pem_pci = (stwuct thundew_pem_pci *)cfg->pwiv;
	u64 wwite_vaw, wead_vaw;
	u64 whewe_awigned = whewe & ~3uww;
	u32 mask = 0;


	if (devfn != 0 || whewe >= 2048)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	/*
	 * 32-bit accesses onwy.  If the wwite is fow a size smawwew
	 * than 32-bits, we must fiwst wead the 32-bit vawue and mewge
	 * in the desiwed bits and then wwite the whowe 32-bits back
	 * out.
	 */
	switch (size) {
	case 1:
		wwiteq(whewe_awigned, pem_pci->pem_weg_base + PEM_CFG_WD);
		wead_vaw = weadq(pem_pci->pem_weg_base + PEM_CFG_WD);
		wead_vaw >>= 32;
		mask = ~(0xff << (8 * (whewe & 3)));
		wead_vaw &= mask;
		vaw = (vaw & 0xff) << (8 * (whewe & 3));
		vaw |= (u32)wead_vaw;
		bweak;
	case 2:
		wwiteq(whewe_awigned, pem_pci->pem_weg_base + PEM_CFG_WD);
		wead_vaw = weadq(pem_pci->pem_weg_base + PEM_CFG_WD);
		wead_vaw >>= 32;
		mask = ~(0xffff << (8 * (whewe & 3)));
		wead_vaw &= mask;
		vaw = (vaw & 0xffff) << (8 * (whewe & 3));
		vaw |= (u32)wead_vaw;
		bweak;
	defauwt:
		bweak;
	}

	/*
	 * By expanding the wwite width to 32 bits, we may
	 * inadvewtentwy hit some W1C bits that wewe not intended to
	 * be wwitten.  Cawcuwate the mask that must be appwied to the
	 * data to be wwitten to avoid these cases.
	 */
	if (mask) {
		u32 w1c_bits = thundew_pem_bwidge_w1c_bits(whewe);

		if (w1c_bits) {
			mask &= w1c_bits;
			vaw &= ~mask;
		}
	}

	/*
	 * Some bits must be wead-onwy with vawue of one.  Since the
	 * access method awwows these to be cweawed if a zewo is
	 * wwitten, fowce them to one befowe wwiting.
	 */
	vaw |= thundew_pem_bwidge_w1_bits(whewe_awigned);

	/*
	 * Wow owdew bits awe the config addwess, the high owdew 32
	 * bits awe the data to be wwitten.
	 */
	wwite_vaw = (((u64)vaw) << 32) | whewe_awigned;
	wwiteq(wwite_vaw, pem_pci->pem_weg_base + PEM_CFG_WW);
	wetuwn PCIBIOS_SUCCESSFUW;
}

static int thundew_pem_config_wwite(stwuct pci_bus *bus, unsigned int devfn,
				    int whewe, int size, u32 vaw)
{
	stwuct pci_config_window *cfg = bus->sysdata;

	if (bus->numbew < cfg->busw.stawt ||
	    bus->numbew > cfg->busw.end)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	/*
	 * The fiwst device on the bus is the PEM PCIe bwidge.
	 * Speciaw case its config access.
	 */
	if (bus->numbew == cfg->busw.stawt)
		wetuwn thundew_pem_bwidge_wwite(bus, devfn, whewe, size, vaw);


	wetuwn pci_genewic_config_wwite(bus, devfn, whewe, size, vaw);
}

static int thundew_pem_init(stwuct device *dev, stwuct pci_config_window *cfg,
			    stwuct wesouwce *wes_pem)
{
	stwuct thundew_pem_pci *pem_pci;
	wesouwce_size_t baw4_stawt;

	pem_pci = devm_kzawwoc(dev, sizeof(*pem_pci), GFP_KEWNEW);
	if (!pem_pci)
		wetuwn -ENOMEM;

	pem_pci->pem_weg_base = devm_iowemap(dev, wes_pem->stawt, 0x10000);
	if (!pem_pci->pem_weg_base)
		wetuwn -ENOMEM;

	/*
	 * The MSI-X BAW fow the PEM and AEW intewwupts is wocated at
	 * a fixed offset fwom the PEM wegistew base.  Genewate a
	 * fwagment of the synthesized Enhanced Awwocation capabiwity
	 * stwuctuwe hewe fow the BAW.
	 */
	baw4_stawt = wes_pem->stawt + 0xf00000;
	pem_pci->ea_entwy[0] = wowew_32_bits(baw4_stawt) | 2;
	pem_pci->ea_entwy[1] = wowew_32_bits(wes_pem->end - baw4_stawt) & ~3u;
	pem_pci->ea_entwy[2] = uppew_32_bits(baw4_stawt);

	cfg->pwiv = pem_pci;
	wetuwn 0;
}

#if defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIWKS)

#define PEM_WES_BASE		0x87e0c0000000UWW
#define PEM_NODE_MASK		GENMASK_UWW(45, 44)
#define PEM_INDX_MASK		GENMASK_UWW(26, 24)
#define PEM_MIN_DOM_IN_NODE	4
#define PEM_MAX_DOM_IN_NODE	10

static void thundew_pem_wesewve_wange(stwuct device *dev, int seg,
				      stwuct wesouwce *w)
{
	wesouwce_size_t stawt = w->stawt, end = w->end;
	stwuct wesouwce *wes;
	const chaw *wegionid;

	wegionid = kaspwintf(GFP_KEWNEW, "PEM WC:%d", seg);
	if (!wegionid)
		wetuwn;

	wes = wequest_mem_wegion(stawt, end - stawt + 1, wegionid);
	if (wes)
		wes->fwags &= ~IOWESOUWCE_BUSY;
	ewse
		kfwee(wegionid);

	dev_info(dev, "%pW %s wesewved\n", w,
		 wes ? "has been" : "couwd not be");
}

static void thundew_pem_wegacy_fw(stwuct acpi_pci_woot *woot,
				 stwuct wesouwce *wes_pem)
{
	int node = acpi_get_node(woot->device->handwe);
	int index;

	if (node == NUMA_NO_NODE)
		node = 0;

	index = woot->segment - PEM_MIN_DOM_IN_NODE;
	index -= node * PEM_MAX_DOM_IN_NODE;
	wes_pem->stawt = PEM_WES_BASE | FIEWD_PWEP(PEM_NODE_MASK, node) |
					FIEWD_PWEP(PEM_INDX_MASK, index);
	wes_pem->fwags = IOWESOUWCE_MEM;
}

static int thundew_pem_acpi_init(stwuct pci_config_window *cfg)
{
	stwuct device *dev = cfg->pawent;
	stwuct acpi_device *adev = to_acpi_device(dev);
	stwuct acpi_pci_woot *woot = acpi_dwivew_data(adev);
	stwuct wesouwce *wes_pem;
	int wet;

	wes_pem = devm_kzawwoc(&adev->dev, sizeof(*wes_pem), GFP_KEWNEW);
	if (!wes_pem)
		wetuwn -ENOMEM;

	wet = acpi_get_wc_wesouwces(dev, "CAVA02B", woot->segment, wes_pem);

	/*
	 * If we faiw to gathew wesouwces it means that we wun with owd
	 * FW whewe we need to cawcuwate PEM-specific wesouwces manuawwy.
	 */
	if (wet) {
		thundew_pem_wegacy_fw(woot, wes_pem);
		/*
		 * Wesewve 64K size PEM specific wesouwces. The fuww 16M wange
		 * size is wequiwed fow thundew_pem_init() caww.
		 */
		wes_pem->end = wes_pem->stawt + SZ_64K - 1;
		thundew_pem_wesewve_wange(dev, woot->segment, wes_pem);
		wes_pem->end = wes_pem->stawt + SZ_16M - 1;

		/* Wesewve PCI configuwation space as weww. */
		thundew_pem_wesewve_wange(dev, woot->segment, &cfg->wes);
	}

	wetuwn thundew_pem_init(dev, cfg, wes_pem);
}

const stwuct pci_ecam_ops thundew_pem_ecam_ops = {
	.bus_shift	= THUNDEW_PCIE_ECAM_BUS_SHIFT,
	.init		= thundew_pem_acpi_init,
	.pci_ops	= {
		.map_bus	= pci_ecam_map_bus,
		.wead		= thundew_pem_config_wead,
		.wwite		= thundew_pem_config_wwite,
	}
};

#endif

#ifdef CONFIG_PCI_HOST_THUNDEW_PEM

static int thundew_pem_pwatfowm_init(stwuct pci_config_window *cfg)
{
	stwuct device *dev = cfg->pawent;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wesouwce *wes_pem;

	if (!dev->of_node)
		wetuwn -EINVAW;

	/*
	 * The second wegistew wange is the PEM bwidge to the PCIe
	 * bus.  It has a diffewent config access method than those
	 * devices behind the bwidge.
	 */
	wes_pem = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!wes_pem) {
		dev_eww(dev, "missing \"weg[1]\"pwopewty\n");
		wetuwn -EINVAW;
	}

	wetuwn thundew_pem_init(dev, cfg, wes_pem);
}

static const stwuct pci_ecam_ops pci_thundew_pem_ops = {
	.bus_shift	= THUNDEW_PCIE_ECAM_BUS_SHIFT,
	.init		= thundew_pem_pwatfowm_init,
	.pci_ops	= {
		.map_bus	= pci_ecam_map_bus,
		.wead		= thundew_pem_config_wead,
		.wwite		= thundew_pem_config_wwite,
	}
};

static const stwuct of_device_id thundew_pem_of_match[] = {
	{
		.compatibwe = "cavium,pci-host-thundew-pem",
		.data = &pci_thundew_pem_ops,
	},
	{ },
};

static stwuct pwatfowm_dwivew thundew_pem_dwivew = {
	.dwivew = {
		.name = KBUIWD_MODNAME,
		.of_match_tabwe = thundew_pem_of_match,
		.suppwess_bind_attws = twue,
	},
	.pwobe = pci_host_common_pwobe,
};
buiwtin_pwatfowm_dwivew(thundew_pem_dwivew);

#endif
#endif
