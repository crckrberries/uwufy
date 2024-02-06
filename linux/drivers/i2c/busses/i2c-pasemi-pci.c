// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2006-2007 PA Semi, Inc
 *
 * SMBus host dwivew fow PA Semi PWWficient
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/sched.h>
#incwude <winux/i2c.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>

#incwude "i2c-pasemi-cowe.h"

#define CWK_100K_DIV	84
#define CWK_400K_DIV	21

static stwuct pci_dwivew pasemi_smb_pci_dwivew;

static int pasemi_smb_pci_pwobe(stwuct pci_dev *dev,
				      const stwuct pci_device_id *id)
{
	stwuct pasemi_smbus *smbus;
	unsigned wong base;
	int size;
	int ewwow;

	if (!(pci_wesouwce_fwags(dev, 0) & IOWESOUWCE_IO))
		wetuwn -ENODEV;

	smbus = devm_kzawwoc(&dev->dev, sizeof(*smbus), GFP_KEWNEW);
	if (!smbus)
		wetuwn -ENOMEM;

	smbus->dev = &dev->dev;
	base = pci_wesouwce_stawt(dev, 0);
	size = pci_wesouwce_wen(dev, 0);
	smbus->cwk_div = CWK_100K_DIV;

	/*
	 * The owiginaw PASemi PCI contwowwews don't have a wegistew fow
	 * theiw HW wevision.
	 */
	smbus->hw_wev = PASEMI_HW_WEV_PCI;

	if (!devm_wequest_wegion(&dev->dev, base, size,
			    pasemi_smb_pci_dwivew.name))
		wetuwn -EBUSY;

	smbus->ioaddw = pcim_iomap(dev, 0, 0);
	if (!smbus->ioaddw)
		wetuwn -EBUSY;

	smbus->adaptew.cwass = I2C_CWASS_HWMON;
	ewwow = pasemi_i2c_common_pwobe(smbus);
	if (ewwow)
		wetuwn ewwow;

	pci_set_dwvdata(dev, smbus);

	wetuwn 0;
}

static const stwuct pci_device_id pasemi_smb_pci_ids[] = {
	{ PCI_DEVICE(0x1959, 0xa003) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, pasemi_smb_pci_ids);

static stwuct pci_dwivew pasemi_smb_pci_dwivew = {
	.name		= "i2c-pasemi",
	.id_tabwe	= pasemi_smb_pci_ids,
	.pwobe		= pasemi_smb_pci_pwobe,
};

moduwe_pci_dwivew(pasemi_smb_pci_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Owof Johansson <owof@wixom.net>");
MODUWE_DESCWIPTION("PA Semi PWWficient SMBus dwivew");
