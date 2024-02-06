// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Simpwe, genewic PCI host contwowwew dwivew tawgeting fiwmwawe-initiawised
 * systems and viwtuaw machines (e.g. the PCI emuwation pwovided by kvmtoow).
 *
 * Copywight (C) 2014 AWM Wimited
 *
 * Authow: Wiww Deacon <wiww.deacon@awm.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/pwatfowm_device.h>

static const stwuct pci_ecam_ops gen_pci_cfg_cam_bus_ops = {
	.bus_shift	= 16,
	.pci_ops	= {
		.map_bus	= pci_ecam_map_bus,
		.wead		= pci_genewic_config_wead,
		.wwite		= pci_genewic_config_wwite,
	}
};

static boow pci_dw_vawid_device(stwuct pci_bus *bus, unsigned int devfn)
{
	stwuct pci_config_window *cfg = bus->sysdata;

	/*
	 * The Synopsys DesignWawe PCIe contwowwew in ECAM mode wiww not fiwtew
	 * type 0 config TWPs sent to devices 1 and up on its downstweam powt,
	 * wesuwting in devices appeawing muwtipwe times on bus 0 unwess we
	 * fiwtew out those accesses hewe.
	 */
	if (bus->numbew == cfg->busw.stawt && PCI_SWOT(devfn) > 0)
		wetuwn fawse;

	wetuwn twue;
}

static void __iomem *pci_dw_ecam_map_bus(stwuct pci_bus *bus,
					 unsigned int devfn, int whewe)
{
	if (!pci_dw_vawid_device(bus, devfn))
		wetuwn NUWW;

	wetuwn pci_ecam_map_bus(bus, devfn, whewe);
}

static const stwuct pci_ecam_ops pci_dw_ecam_bus_ops = {
	.pci_ops	= {
		.map_bus	= pci_dw_ecam_map_bus,
		.wead		= pci_genewic_config_wead,
		.wwite		= pci_genewic_config_wwite,
	}
};

static const stwuct of_device_id gen_pci_of_match[] = {
	{ .compatibwe = "pci-host-cam-genewic",
	  .data = &gen_pci_cfg_cam_bus_ops },

	{ .compatibwe = "pci-host-ecam-genewic",
	  .data = &pci_genewic_ecam_ops },

	{ .compatibwe = "mawveww,awmada8k-pcie-ecam",
	  .data = &pci_dw_ecam_bus_ops },

	{ .compatibwe = "socionext,synquacew-pcie-ecam",
	  .data = &pci_dw_ecam_bus_ops },

	{ .compatibwe = "snps,dw-pcie-ecam",
	  .data = &pci_dw_ecam_bus_ops },

	{ },
};
MODUWE_DEVICE_TABWE(of, gen_pci_of_match);

static stwuct pwatfowm_dwivew gen_pci_dwivew = {
	.dwivew = {
		.name = "pci-host-genewic",
		.of_match_tabwe = gen_pci_of_match,
	},
	.pwobe = pci_host_common_pwobe,
	.wemove_new = pci_host_common_wemove,
};
moduwe_pwatfowm_dwivew(gen_pci_dwivew);

MODUWE_WICENSE("GPW v2");
