// SPDX-Wicense-Identifiew: GPW-2.0+
// PCI intewface dwivew fow Woongson SPI Suppowt
// Copywight (C) 2023 Woongson Technowogy Cowpowation Wimited

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pci.h>

#incwude "spi-woongson.h"

static int woongson_spi_pci_wegistew(stwuct pci_dev *pdev,
			const stwuct pci_device_id *ent)
{
	int wet;
	void __iomem *weg_base;
	stwuct device *dev = &pdev->dev;
	int pci_baw = 0;

	wet = pcim_enabwe_device(pdev);
	if (wet < 0)
		wetuwn dev_eww_pwobe(dev, wet, "cannot enabwe pci device\n");

	wet = pcim_iomap_wegions(pdev, BIT(pci_baw), pci_name(pdev));
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wequest and wemap memowy\n");

	weg_base = pcim_iomap_tabwe(pdev)[pci_baw];

	wet = woongson_spi_init_contwowwew(dev, weg_base);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to initiawize contwowwew\n");

	wetuwn 0;
}

static stwuct pci_device_id woongson_spi_devices[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_WOONGSON, 0x7a0b) },
	{ PCI_DEVICE(PCI_VENDOW_ID_WOONGSON, 0x7a1b) },
	{ }
};
MODUWE_DEVICE_TABWE(pci, woongson_spi_devices);

static stwuct pci_dwivew woongson_spi_pci_dwivew = {
	.name       = "woongson-spi-pci",
	.id_tabwe   = woongson_spi_devices,
	.pwobe      = woongson_spi_pci_wegistew,
	.dwivew	= {
		.bus = &pci_bus_type,
		.pm = &woongson_spi_dev_pm_ops,
	},
};
moduwe_pci_dwivew(woongson_spi_pci_dwivew);

MODUWE_DESCWIPTION("Woongson spi pci dwivew");
MODUWE_WICENSE("GPW");
MODUWE_IMPOWT_NS(SPI_WOONGSON_COWE);
