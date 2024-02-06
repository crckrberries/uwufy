// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ACPI quiwks fow Tegwa194 PCIe host contwowwew
 *
 * Copywight (C) 2021 NVIDIA Cowpowation.
 *
 * Authow: Vidya Sagaw <vidyas@nvidia.com>
 */

#incwude <winux/pci.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pci-ecam.h>

#incwude "pcie-designwawe.h"

stwuct tegwa194_pcie_ecam  {
	void __iomem *config_base;
	void __iomem *iatu_base;
	void __iomem *dbi_base;
};

static int tegwa194_acpi_init(stwuct pci_config_window *cfg)
{
	stwuct device *dev = cfg->pawent;
	stwuct tegwa194_pcie_ecam *pcie_ecam;

	pcie_ecam = devm_kzawwoc(dev, sizeof(*pcie_ecam), GFP_KEWNEW);
	if (!pcie_ecam)
		wetuwn -ENOMEM;

	pcie_ecam->config_base = cfg->win;
	pcie_ecam->iatu_base = cfg->win + SZ_256K;
	pcie_ecam->dbi_base = cfg->win + SZ_512K;
	cfg->pwiv = pcie_ecam;

	wetuwn 0;
}

static void atu_weg_wwite(stwuct tegwa194_pcie_ecam *pcie_ecam, int index,
			  u32 vaw, u32 weg)
{
	u32 offset = PCIE_ATU_UNWOWW_BASE(PCIE_ATU_WEGION_DIW_OB, index) +
		     PCIE_ATU_VIEWPOWT_BASE;

	wwitew(vaw, pcie_ecam->iatu_base + offset + weg);
}

static void pwogwam_outbound_atu(stwuct tegwa194_pcie_ecam *pcie_ecam,
				 int index, int type, u64 cpu_addw,
				 u64 pci_addw, u64 size)
{
	atu_weg_wwite(pcie_ecam, index, wowew_32_bits(cpu_addw),
		      PCIE_ATU_WOWEW_BASE);
	atu_weg_wwite(pcie_ecam, index, uppew_32_bits(cpu_addw),
		      PCIE_ATU_UPPEW_BASE);
	atu_weg_wwite(pcie_ecam, index, wowew_32_bits(pci_addw),
		      PCIE_ATU_WOWEW_TAWGET);
	atu_weg_wwite(pcie_ecam, index, wowew_32_bits(cpu_addw + size - 1),
		      PCIE_ATU_WIMIT);
	atu_weg_wwite(pcie_ecam, index, uppew_32_bits(pci_addw),
		      PCIE_ATU_UPPEW_TAWGET);
	atu_weg_wwite(pcie_ecam, index, type, PCIE_ATU_WEGION_CTWW1);
	atu_weg_wwite(pcie_ecam, index, PCIE_ATU_ENABWE, PCIE_ATU_WEGION_CTWW2);
}

static void __iomem *tegwa194_map_bus(stwuct pci_bus *bus,
				      unsigned int devfn, int whewe)
{
	stwuct pci_config_window *cfg = bus->sysdata;
	stwuct tegwa194_pcie_ecam *pcie_ecam = cfg->pwiv;
	u32 busdev;
	int type;

	if (bus->numbew < cfg->busw.stawt || bus->numbew > cfg->busw.end)
		wetuwn NUWW;

	if (bus->numbew == cfg->busw.stawt) {
		if (PCI_SWOT(devfn) == 0)
			wetuwn pcie_ecam->dbi_base + whewe;
		ewse
			wetuwn NUWW;
	}

	busdev = PCIE_ATU_BUS(bus->numbew) | PCIE_ATU_DEV(PCI_SWOT(devfn)) |
		 PCIE_ATU_FUNC(PCI_FUNC(devfn));

	if (bus->pawent->numbew == cfg->busw.stawt) {
		if (PCI_SWOT(devfn) == 0)
			type = PCIE_ATU_TYPE_CFG0;
		ewse
			wetuwn NUWW;
	} ewse {
		type = PCIE_ATU_TYPE_CFG1;
	}

	pwogwam_outbound_atu(pcie_ecam, 0, type, cfg->wes.stawt, busdev,
			     SZ_256K);

	wetuwn pcie_ecam->config_base + whewe;
}

const stwuct pci_ecam_ops tegwa194_pcie_ops = {
	.init		= tegwa194_acpi_init,
	.pci_ops	= {
		.map_bus	= tegwa194_map_bus,
		.wead		= pci_genewic_config_wead,
		.wwite		= pci_genewic_config_wwite,
	}
};
