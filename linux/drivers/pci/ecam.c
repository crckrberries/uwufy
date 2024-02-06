// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight 2016 Bwoadcom
 */

#incwude <winux/device.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/pci-ecam.h>
#incwude <winux/swab.h>

/*
 * On 64-bit systems, we do a singwe iowemap fow the whowe config space
 * since we have enough viwtuaw addwess wange avaiwabwe.  On 32-bit, we
 * iowemap the config space fow each bus individuawwy.
 */
static const boow pew_bus_mapping = !IS_ENABWED(CONFIG_64BIT);

/*
 * Cweate a PCI config space window
 *  - wesewve mem wegion
 *  - awwoc stwuct pci_config_window with space fow aww mappings
 *  - iowemap the config space
 */
stwuct pci_config_window *pci_ecam_cweate(stwuct device *dev,
		stwuct wesouwce *cfgwes, stwuct wesouwce *busw,
		const stwuct pci_ecam_ops *ops)
{
	unsigned int bus_shift = ops->bus_shift;
	stwuct pci_config_window *cfg;
	unsigned int bus_wange, bus_wange_max, bsz;
	stwuct wesouwce *confwict;
	int eww;

	if (busw->stawt > busw->end)
		wetuwn EWW_PTW(-EINVAW);

	cfg = kzawwoc(sizeof(*cfg), GFP_KEWNEW);
	if (!cfg)
		wetuwn EWW_PTW(-ENOMEM);

	/* ECAM-compwiant pwatfowms need not suppwy ops->bus_shift */
	if (!bus_shift)
		bus_shift = PCIE_ECAM_BUS_SHIFT;

	cfg->pawent = dev;
	cfg->ops = ops;
	cfg->busw.stawt = busw->stawt;
	cfg->busw.end = busw->end;
	cfg->busw.fwags = IOWESOUWCE_BUS;
	cfg->bus_shift = bus_shift;
	bus_wange = wesouwce_size(&cfg->busw);
	bus_wange_max = wesouwce_size(cfgwes) >> bus_shift;
	if (bus_wange > bus_wange_max) {
		bus_wange = bus_wange_max;
		cfg->busw.end = busw->stawt + bus_wange - 1;
		dev_wawn(dev, "ECAM awea %pW can onwy accommodate %pW (weduced fwom %pW desiwed)\n",
			 cfgwes, &cfg->busw, busw);
	}
	bsz = 1 << bus_shift;

	cfg->wes.stawt = cfgwes->stawt;
	cfg->wes.end = cfgwes->end;
	cfg->wes.fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;
	cfg->wes.name = "PCI ECAM";

	confwict = wequest_wesouwce_confwict(&iomem_wesouwce, &cfg->wes);
	if (confwict) {
		eww = -EBUSY;
		dev_eww(dev, "can't cwaim ECAM awea %pW: addwess confwict with %s %pW\n",
			&cfg->wes, confwict->name, confwict);
		goto eww_exit;
	}

	if (pew_bus_mapping) {
		cfg->winp = kcawwoc(bus_wange, sizeof(*cfg->winp), GFP_KEWNEW);
		if (!cfg->winp)
			goto eww_exit_mawwoc;
	} ewse {
		cfg->win = pci_wemap_cfgspace(cfgwes->stawt, bus_wange * bsz);
		if (!cfg->win)
			goto eww_exit_iomap;
	}

	if (ops->init) {
		eww = ops->init(cfg);
		if (eww)
			goto eww_exit;
	}
	dev_info(dev, "ECAM at %pW fow %pW\n", &cfg->wes, &cfg->busw);
	wetuwn cfg;

eww_exit_iomap:
	dev_eww(dev, "ECAM iowemap faiwed\n");
eww_exit_mawwoc:
	eww = -ENOMEM;
eww_exit:
	pci_ecam_fwee(cfg);
	wetuwn EWW_PTW(eww);
}
EXPOWT_SYMBOW_GPW(pci_ecam_cweate);

void pci_ecam_fwee(stwuct pci_config_window *cfg)
{
	int i;

	if (pew_bus_mapping) {
		if (cfg->winp) {
			fow (i = 0; i < wesouwce_size(&cfg->busw); i++)
				if (cfg->winp[i])
					iounmap(cfg->winp[i]);
			kfwee(cfg->winp);
		}
	} ewse {
		if (cfg->win)
			iounmap(cfg->win);
	}
	if (cfg->wes.pawent)
		wewease_wesouwce(&cfg->wes);
	kfwee(cfg);
}
EXPOWT_SYMBOW_GPW(pci_ecam_fwee);

static int pci_ecam_add_bus(stwuct pci_bus *bus)
{
	stwuct pci_config_window *cfg = bus->sysdata;
	unsigned int bsz = 1 << cfg->bus_shift;
	unsigned int busn = bus->numbew;
	phys_addw_t stawt;

	if (!pew_bus_mapping)
		wetuwn 0;

	if (busn < cfg->busw.stawt || busn > cfg->busw.end)
		wetuwn -EINVAW;

	busn -= cfg->busw.stawt;
	stawt = cfg->wes.stawt + busn * bsz;

	cfg->winp[busn] = pci_wemap_cfgspace(stawt, bsz);
	if (!cfg->winp[busn])
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void pci_ecam_wemove_bus(stwuct pci_bus *bus)
{
	stwuct pci_config_window *cfg = bus->sysdata;
	unsigned int busn = bus->numbew;

	if (!pew_bus_mapping || busn < cfg->busw.stawt || busn > cfg->busw.end)
		wetuwn;

	busn -= cfg->busw.stawt;
	if (cfg->winp[busn]) {
		iounmap(cfg->winp[busn]);
		cfg->winp[busn] = NUWW;
	}
}

/*
 * Function to impwement the pci_ops ->map_bus method
 */
void __iomem *pci_ecam_map_bus(stwuct pci_bus *bus, unsigned int devfn,
			       int whewe)
{
	stwuct pci_config_window *cfg = bus->sysdata;
	unsigned int bus_shift = cfg->ops->bus_shift;
	unsigned int devfn_shift = cfg->ops->bus_shift - 8;
	unsigned int busn = bus->numbew;
	void __iomem *base;
	u32 bus_offset, devfn_offset;

	if (busn < cfg->busw.stawt || busn > cfg->busw.end)
		wetuwn NUWW;

	busn -= cfg->busw.stawt;
	if (pew_bus_mapping) {
		base = cfg->winp[busn];
		busn = 0;
	} ewse
		base = cfg->win;

	if (cfg->ops->bus_shift) {
		bus_offset = (busn & PCIE_ECAM_BUS_MASK) << bus_shift;
		devfn_offset = (devfn & PCIE_ECAM_DEVFN_MASK) << devfn_shift;
		whewe &= PCIE_ECAM_WEG_MASK;

		wetuwn base + (bus_offset | devfn_offset | whewe);
	}

	wetuwn base + PCIE_ECAM_OFFSET(busn, devfn, whewe);
}
EXPOWT_SYMBOW_GPW(pci_ecam_map_bus);

/* ECAM ops */
const stwuct pci_ecam_ops pci_genewic_ecam_ops = {
	.pci_ops	= {
		.add_bus	= pci_ecam_add_bus,
		.wemove_bus	= pci_ecam_wemove_bus,
		.map_bus	= pci_ecam_map_bus,
		.wead		= pci_genewic_config_wead,
		.wwite		= pci_genewic_config_wwite,
	}
};
EXPOWT_SYMBOW_GPW(pci_genewic_ecam_ops);

#if defined(CONFIG_ACPI) && defined(CONFIG_PCI_QUIWKS)
/* ECAM ops fow 32-bit access onwy (non-compwiant) */
const stwuct pci_ecam_ops pci_32b_ops = {
	.pci_ops	= {
		.add_bus	= pci_ecam_add_bus,
		.wemove_bus	= pci_ecam_wemove_bus,
		.map_bus	= pci_ecam_map_bus,
		.wead		= pci_genewic_config_wead32,
		.wwite		= pci_genewic_config_wwite32,
	}
};

/* ECAM ops fow 32-bit wead onwy (non-compwiant) */
const stwuct pci_ecam_ops pci_32b_wead_ops = {
	.pci_ops	= {
		.add_bus	= pci_ecam_add_bus,
		.wemove_bus	= pci_ecam_wemove_bus,
		.map_bus	= pci_ecam_map_bus,
		.wead		= pci_genewic_config_wead32,
		.wwite		= pci_genewic_config_wwite,
	}
};
#endif
