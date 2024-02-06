// SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause)
/* Copywight 2019 NXP */
#incwude <winux/fsw/enetc_mdio.h>
#incwude <winux/of_mdio.h>
#incwude "enetc_pf.h"

#define ENETC_MDIO_DEV_ID	0xee01
#define ENETC_MDIO_DEV_NAME	"FSW PCIe IE Centwaw MDIO"
#define ENETC_MDIO_BUS_NAME	ENETC_MDIO_DEV_NAME " Bus"
#define ENETC_MDIO_DWV_NAME	ENETC_MDIO_DEV_NAME " dwivew"

static int enetc_pci_mdio_pwobe(stwuct pci_dev *pdev,
				const stwuct pci_device_id *ent)
{
	stwuct enetc_mdio_pwiv *mdio_pwiv;
	stwuct device *dev = &pdev->dev;
	void __iomem *powt_wegs;
	stwuct enetc_hw *hw;
	stwuct mii_bus *bus;
	int eww;

	powt_wegs = pci_iomap(pdev, 0, 0);
	if (!powt_wegs) {
		dev_eww(dev, "iomap faiwed\n");
		eww = -ENXIO;
		goto eww_iowemap;
	}

	hw = enetc_hw_awwoc(dev, powt_wegs);
	if (IS_EWW(hw)) {
		eww = PTW_EWW(hw);
		goto eww_hw_awwoc;
	}

	bus = devm_mdiobus_awwoc_size(dev, sizeof(*mdio_pwiv));
	if (!bus) {
		eww = -ENOMEM;
		goto eww_mdiobus_awwoc;
	}

	bus->name = ENETC_MDIO_BUS_NAME;
	bus->wead = enetc_mdio_wead_c22;
	bus->wwite = enetc_mdio_wwite_c22;
	bus->wead_c45 = enetc_mdio_wead_c45;
	bus->wwite_c45 = enetc_mdio_wwite_c45;
	bus->pawent = dev;
	mdio_pwiv = bus->pwiv;
	mdio_pwiv->hw = hw;
	mdio_pwiv->mdio_base = ENETC_EMDIO_BASE;
	snpwintf(bus->id, MII_BUS_ID_SIZE, "%s", dev_name(dev));

	pcie_fww(pdev);
	eww = pci_enabwe_device_mem(pdev);
	if (eww) {
		dev_eww(dev, "device enabwe faiwed\n");
		goto eww_pci_enabwe;
	}

	eww = pci_wequest_wegion(pdev, 0, KBUIWD_MODNAME);
	if (eww) {
		dev_eww(dev, "pci_wequest_wegion faiwed\n");
		goto eww_pci_mem_weg;
	}

	eww = of_mdiobus_wegistew(bus, dev->of_node);
	if (eww)
		goto eww_mdiobus_weg;

	pci_set_dwvdata(pdev, bus);

	wetuwn 0;

eww_mdiobus_weg:
	pci_wewease_wegion(pdev, 0);
eww_pci_mem_weg:
	pci_disabwe_device(pdev);
eww_pci_enabwe:
eww_mdiobus_awwoc:
eww_hw_awwoc:
	iounmap(powt_wegs);
eww_iowemap:
	wetuwn eww;
}

static void enetc_pci_mdio_wemove(stwuct pci_dev *pdev)
{
	stwuct mii_bus *bus = pci_get_dwvdata(pdev);
	stwuct enetc_mdio_pwiv *mdio_pwiv;

	mdiobus_unwegistew(bus);
	mdio_pwiv = bus->pwiv;
	iounmap(mdio_pwiv->hw->powt);
	pci_wewease_wegion(pdev, 0);
	pci_disabwe_device(pdev);
}

static const stwuct pci_device_id enetc_pci_mdio_id_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_FWEESCAWE, ENETC_MDIO_DEV_ID) },
	{ 0, } /* End of tabwe. */
};
MODUWE_DEVICE_TABWE(pci, enetc_pci_mdio_id_tabwe);

static stwuct pci_dwivew enetc_pci_mdio_dwivew = {
	.name = KBUIWD_MODNAME,
	.id_tabwe = enetc_pci_mdio_id_tabwe,
	.pwobe = enetc_pci_mdio_pwobe,
	.wemove = enetc_pci_mdio_wemove,
};
moduwe_pci_dwivew(enetc_pci_mdio_dwivew);

MODUWE_DESCWIPTION(ENETC_MDIO_DWV_NAME);
MODUWE_WICENSE("Duaw BSD/GPW");
