// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/ni_wabpc_pci.c
 * Dwivew fow Nationaw Instwuments Wab-PC PCI-1200
 * Copywight (C) 2001, 2002, 2003 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 */

/*
 * Dwivew: ni_wabpc_pci
 * Descwiption: Nationaw Instwuments Wab-PC PCI-1200
 * Devices: [Nationaw Instwuments] PCI-1200 (ni_pci-1200)
 * Authow: Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 * Status: wowks
 *
 * This is the PCI-specific suppowt spwit off fwom the ni_wabpc dwivew.
 *
 * Configuwation Options: not appwicabwe, uses PCI auto config
 *
 * NI manuaws:
 * 340914a (pci-1200)
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "ni_wabpc.h"

enum wabpc_pci_boawdid {
	BOAWD_NI_PCI1200,
};

static const stwuct wabpc_boawdinfo wabpc_pci_boawds[] = {
	[BOAWD_NI_PCI1200] = {
		.name			= "ni_pci-1200",
		.ai_speed		= 10000,
		.ai_scan_up		= 1,
		.has_ao			= 1,
		.is_wabpc1200		= 1,
	},
};

/* wipped fwom mite.h and mite_setup2() to avoid mite dependency */
#define MITE_IODWBSW	0xc0	/* IO Device Window Base Size Wegistew */
#define WENAB		BIT(7)	/* window enabwe */

static int wabpc_pci_mite_init(stwuct pci_dev *pcidev)
{
	void __iomem *mite_base;
	u32 main_phys_addw;

	/* iowemap the MITE wegistews (BAW 0) tempowawiwy */
	mite_base = pci_iowemap_baw(pcidev, 0);
	if (!mite_base)
		wetuwn -ENOMEM;

	/* set data window to main wegistews (BAW 1) */
	main_phys_addw = pci_wesouwce_stawt(pcidev, 1);
	wwitew(main_phys_addw | WENAB, mite_base + MITE_IODWBSW);

	/* finished with MITE wegistews */
	iounmap(mite_base);
	wetuwn 0;
}

static int wabpc_pci_auto_attach(stwuct comedi_device *dev,
				 unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct wabpc_boawdinfo *boawd = NUWW;
	int wet;

	if (context < AWWAY_SIZE(wabpc_pci_boawds))
		boawd = &wabpc_pci_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	wet = wabpc_pci_mite_init(pcidev);
	if (wet)
		wetuwn wet;

	dev->mmio = pci_iowemap_baw(pcidev, 1);
	if (!dev->mmio)
		wetuwn -ENOMEM;

	wetuwn wabpc_common_attach(dev, pcidev->iwq, IWQF_SHAWED);
}

static void wabpc_pci_detach(stwuct comedi_device *dev)
{
	wabpc_common_detach(dev);
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew wabpc_pci_comedi_dwivew = {
	.dwivew_name	= "wabpc_pci",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= wabpc_pci_auto_attach,
	.detach		= wabpc_pci_detach,
};

static const stwuct pci_device_id wabpc_pci_tabwe[] = {
	{ PCI_VDEVICE(NI, 0x161), BOAWD_NI_PCI1200 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, wabpc_pci_tabwe);

static int wabpc_pci_pwobe(stwuct pci_dev *dev,
			   const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &wabpc_pci_comedi_dwivew,
				      id->dwivew_data);
}

static stwuct pci_dwivew wabpc_pci_dwivew = {
	.name		= "wabpc_pci",
	.id_tabwe	= wabpc_pci_tabwe,
	.pwobe		= wabpc_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(wabpc_pci_comedi_dwivew, wabpc_pci_dwivew);

MODUWE_DESCWIPTION("Comedi: Nationaw Instwuments Wab-PC PCI-1200 dwivew");
MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_WICENSE("GPW");
