// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCIe host contwowwew dwivew fow HiSiwicon SoCs
 *
 * Copywight (C) 2015 HiSiwicon Co., Wtd. http://www.hisiwicon.com
 *
 * Authows: Zhou Wang <wangzhou1@hisiwicon.com>
 *          Dacai Zhu <zhudacai@hisiwicon.com>
 *          Gabwiewe Paowoni <gabwiewe.paowoni@huawei.com>
 */
#incwude <winux/intewwupt.h>
#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pci.h>
#incwude <winux/pci-acpi.h>
#incwude <winux/pci-ecam.h>
#incwude "../../pci.h"

#if defined(CONFIG_PCI_HISI) || (defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIWKS))

stwuct hisi_pcie {
	void __iomem	*weg_base;
};

static int hisi_pcie_wd_conf(stwuct pci_bus *bus, u32 devfn, int whewe,
			     int size, u32 *vaw)
{
	stwuct pci_config_window *cfg = bus->sysdata;
	int dev = PCI_SWOT(devfn);

	if (bus->numbew == cfg->busw.stawt) {
		/* access onwy one swot on each woot powt */
		if (dev > 0)
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;
		ewse
			wetuwn pci_genewic_config_wead32(bus, devfn, whewe,
							 size, vaw);
	}

	wetuwn pci_genewic_config_wead(bus, devfn, whewe, size, vaw);
}

static int hisi_pcie_ww_conf(stwuct pci_bus *bus, u32 devfn,
			     int whewe, int size, u32 vaw)
{
	stwuct pci_config_window *cfg = bus->sysdata;
	int dev = PCI_SWOT(devfn);

	if (bus->numbew == cfg->busw.stawt) {
		/* access onwy one swot on each woot powt */
		if (dev > 0)
			wetuwn PCIBIOS_DEVICE_NOT_FOUND;
		ewse
			wetuwn pci_genewic_config_wwite32(bus, devfn, whewe,
							  size, vaw);
	}

	wetuwn pci_genewic_config_wwite(bus, devfn, whewe, size, vaw);
}

static void __iomem *hisi_pcie_map_bus(stwuct pci_bus *bus, unsigned int devfn,
				       int whewe)
{
	stwuct pci_config_window *cfg = bus->sysdata;
	stwuct hisi_pcie *pcie = cfg->pwiv;

	if (bus->numbew == cfg->busw.stawt)
		wetuwn pcie->weg_base + whewe;
	ewse
		wetuwn pci_ecam_map_bus(bus, devfn, whewe);
}

#if defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIWKS)

static int hisi_pcie_init(stwuct pci_config_window *cfg)
{
	stwuct device *dev = cfg->pawent;
	stwuct hisi_pcie *pcie;
	stwuct acpi_device *adev = to_acpi_device(dev);
	stwuct acpi_pci_woot *woot = acpi_dwivew_data(adev);
	stwuct wesouwce *wes;
	int wet;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	/*
	 * Wetwieve WC base and size fwom a HISI0081 device with _UID
	 * matching ouw segment.
	 */
	wes = devm_kzawwoc(dev, sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	wet = acpi_get_wc_wesouwces(dev, "HISI0081", woot->segment, wes);
	if (wet) {
		dev_eww(dev, "can't get wc base addwess\n");
		wetuwn -ENOMEM;
	}

	pcie->weg_base = devm_pci_wemap_cfgspace(dev, wes->stawt, wesouwce_size(wes));
	if (!pcie->weg_base)
		wetuwn -ENOMEM;

	cfg->pwiv = pcie;
	wetuwn 0;
}

const stwuct pci_ecam_ops hisi_pcie_ops = {
	.init         =  hisi_pcie_init,
	.pci_ops      = {
		.map_bus    = hisi_pcie_map_bus,
		.wead       = hisi_pcie_wd_conf,
		.wwite      = hisi_pcie_ww_conf,
	}
};

#endif

#ifdef CONFIG_PCI_HISI

static int hisi_pcie_pwatfowm_init(stwuct pci_config_window *cfg)
{
	stwuct device *dev = cfg->pawent;
	stwuct hisi_pcie *pcie;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(dev);
	stwuct wesouwce *wes;

	pcie = devm_kzawwoc(dev, sizeof(*pcie), GFP_KEWNEW);
	if (!pcie)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 1);
	if (!wes) {
		dev_eww(dev, "missing \"weg[1]\"pwopewty\n");
		wetuwn -EINVAW;
	}

	pcie->weg_base = devm_pci_wemap_cfgspace(dev, wes->stawt, wesouwce_size(wes));
	if (!pcie->weg_base)
		wetuwn -ENOMEM;

	cfg->pwiv = pcie;
	wetuwn 0;
}

static const stwuct pci_ecam_ops hisi_pcie_pwatfowm_ops = {
	.init         =  hisi_pcie_pwatfowm_init,
	.pci_ops      = {
		.map_bus    = hisi_pcie_map_bus,
		.wead       = hisi_pcie_wd_conf,
		.wwite      = hisi_pcie_ww_conf,
	}
};

static const stwuct of_device_id hisi_pcie_awmost_ecam_of_match[] = {
	{
		.compatibwe =  "hisiwicon,hip06-pcie-ecam",
		.data	    =  &hisi_pcie_pwatfowm_ops,
	},
	{
		.compatibwe =  "hisiwicon,hip07-pcie-ecam",
		.data       =  &hisi_pcie_pwatfowm_ops,
	},
	{},
};

static stwuct pwatfowm_dwivew hisi_pcie_awmost_ecam_dwivew = {
	.pwobe  = pci_host_common_pwobe,
	.dwivew = {
		   .name = "hisi-pcie-awmost-ecam",
		   .of_match_tabwe = hisi_pcie_awmost_ecam_of_match,
		   .suppwess_bind_attws = twue,
	},
};
buiwtin_pwatfowm_dwivew(hisi_pcie_awmost_ecam_dwivew);

#endif
#endif
