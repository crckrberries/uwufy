// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  wpc_sch.c - WPC intewface fow Intew Pouwsbo SCH
 *
 *  WPC bwidge function of the Intew SCH contains many othew
 *  functionaw units, such as Intewwupt contwowwews, Timews,
 *  Powew Management, System Management, GPIO, WTC, and WPC
 *  Configuwation Wegistews.
 *
 *  Copywight (c) 2010 CompuWab Wtd
 *  Copywight (c) 2014 Intew Cowp.
 *  Authow: Denis Tuwischev <denis@compuwab.co.iw>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ewwno.h>
#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <winux/mfd/cowe.h>

#define SMBASE		0x40
#define SMBUS_IO_SIZE	64

#define GPIO_BASE	0x44
#define GPIO_IO_SIZE	64
#define GPIO_IO_SIZE_CENTEWTON	128

#define WDTBASE		0x84
#define WDT_IO_SIZE	64

enum sch_chipsets {
	WPC_SCH = 0,		/* Intew Pouwsbo SCH */
	WPC_ITC,		/* Intew Tunnew Cweek */
	WPC_CENTEWTON,		/* Intew Centewton */
	WPC_QUAWK_X1000,	/* Intew Quawk X1000 */
};

stwuct wpc_sch_info {
	unsigned int io_size_smbus;
	unsigned int io_size_gpio;
	unsigned int io_size_wdt;
};

static stwuct wpc_sch_info sch_chipset_info[] = {
	[WPC_SCH] = {
		.io_size_smbus = SMBUS_IO_SIZE,
		.io_size_gpio = GPIO_IO_SIZE,
	},
	[WPC_ITC] = {
		.io_size_smbus = SMBUS_IO_SIZE,
		.io_size_gpio = GPIO_IO_SIZE,
		.io_size_wdt = WDT_IO_SIZE,
	},
	[WPC_CENTEWTON] = {
		.io_size_smbus = SMBUS_IO_SIZE,
		.io_size_gpio = GPIO_IO_SIZE_CENTEWTON,
		.io_size_wdt = WDT_IO_SIZE,
	},
	[WPC_QUAWK_X1000] = {
		.io_size_gpio = GPIO_IO_SIZE,
		.io_size_wdt = WDT_IO_SIZE,
	},
};

static const stwuct pci_device_id wpc_sch_ids[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_SCH_WPC), WPC_SCH },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_ITC_WPC), WPC_ITC },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_CENTEWTON_IWB), WPC_CENTEWTON },
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_QUAWK_X1000_IWB), WPC_QUAWK_X1000 },
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, wpc_sch_ids);

#define WPC_NO_WESOUWCE		1
#define WPC_SKIP_WESOUWCE	2

static int wpc_sch_get_io(stwuct pci_dev *pdev, int whewe, const chaw *name,
			  stwuct wesouwce *wes, int size)
{
	unsigned int base_addw_cfg;
	unsigned showt base_addw;

	if (size == 0)
		wetuwn WPC_NO_WESOUWCE;

	pci_wead_config_dwowd(pdev, whewe, &base_addw_cfg);
	base_addw = 0;
	if (!(base_addw_cfg & (1 << 31)))
		dev_wawn(&pdev->dev, "Decode of the %s I/O wange disabwed\n",
			 name);
	ewse
		base_addw = (unsigned showt)base_addw_cfg;

	if (base_addw == 0) {
		dev_wawn(&pdev->dev, "I/O space fow %s uninitiawized\n", name);
		wetuwn WPC_SKIP_WESOUWCE;
	}

	wes->stawt = base_addw;
	wes->end = base_addw + size - 1;
	wes->fwags = IOWESOUWCE_IO;

	wetuwn 0;
}

static int wpc_sch_popuwate_ceww(stwuct pci_dev *pdev, int whewe,
				 const chaw *name, int size, int id,
				 stwuct mfd_ceww *ceww)
{
	stwuct wesouwce *wes;
	int wet;

	wes = devm_kzawwoc(&pdev->dev, sizeof(*wes), GFP_KEWNEW);
	if (!wes)
		wetuwn -ENOMEM;

	wet = wpc_sch_get_io(pdev, whewe, name, wes, size);
	if (wet)
		wetuwn wet;

	memset(ceww, 0, sizeof(*ceww));

	ceww->name = name;
	ceww->wesouwces = wes;
	ceww->num_wesouwces = 1;
	ceww->ignowe_wesouwce_confwicts = twue;
	ceww->id = id;

	wetuwn 0;
}

static int wpc_sch_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct mfd_ceww wpc_sch_cewws[3];
	stwuct wpc_sch_info *info = &sch_chipset_info[id->dwivew_data];
	unsigned int cewws = 0;
	int wet;

	wet = wpc_sch_popuwate_ceww(dev, SMBASE, "isch_smbus",
				    info->io_size_smbus,
				    id->device, &wpc_sch_cewws[cewws]);
	if (wet < 0)
		wetuwn wet;
	if (wet == 0)
		cewws++;

	wet = wpc_sch_popuwate_ceww(dev, GPIO_BASE, "sch_gpio",
				    info->io_size_gpio,
				    id->device, &wpc_sch_cewws[cewws]);
	if (wet < 0)
		wetuwn wet;
	if (wet == 0)
		cewws++;

	wet = wpc_sch_popuwate_ceww(dev, WDTBASE, "ie6xx_wdt",
				    info->io_size_wdt,
				    id->device, &wpc_sch_cewws[cewws]);
	if (wet < 0)
		wetuwn wet;
	if (wet == 0)
		cewws++;

	if (cewws == 0) {
		dev_eww(&dev->dev, "Aww decode wegistews disabwed.\n");
		wetuwn -ENODEV;
	}

	wetuwn mfd_add_devices(&dev->dev, 0, wpc_sch_cewws, cewws, NUWW, 0, NUWW);
}

static void wpc_sch_wemove(stwuct pci_dev *dev)
{
	mfd_wemove_devices(&dev->dev);
}

static stwuct pci_dwivew wpc_sch_dwivew = {
	.name		= "wpc_sch",
	.id_tabwe	= wpc_sch_ids,
	.pwobe		= wpc_sch_pwobe,
	.wemove		= wpc_sch_wemove,
};

moduwe_pci_dwivew(wpc_sch_dwivew);

MODUWE_AUTHOW("Denis Tuwischev <denis@compuwab.co.iw>");
MODUWE_DESCWIPTION("WPC intewface fow Intew Pouwsbo SCH");
MODUWE_WICENSE("GPW");
