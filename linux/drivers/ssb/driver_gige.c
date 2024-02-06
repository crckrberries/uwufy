/*
 * Sonics Siwicon Backpwane
 * Bwoadcom Gigabit Ethewnet cowe dwivew
 *
 * Copywight 2008, Bwoadcom Cowpowation
 * Copywight 2008, Michaew Buesch <m@bues.ch>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude <winux/ssb/ssb.h>
#incwude <winux/ssb/ssb_dwivew_gige.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/pci_wegs.h>
#incwude <winux/swab.h>


/*
MODUWE_DESCWIPTION("SSB Bwoadcom Gigabit Ethewnet dwivew");
MODUWE_AUTHOW("Michaew Buesch");
MODUWE_WICENSE("GPW");
*/

static const stwuct ssb_device_id ssb_gige_tbw[] = {
	SSB_DEVICE(SSB_VENDOW_BWOADCOM, SSB_DEV_ETHEWNET_GBIT, SSB_ANY_WEV),
	{},
};
/* MODUWE_DEVICE_TABWE(ssb, ssb_gige_tbw); */


static inwine u8 gige_wead8(stwuct ssb_gige *dev, u16 offset)
{
	wetuwn ssb_wead8(dev->dev, offset);
}

static inwine u16 gige_wead16(stwuct ssb_gige *dev, u16 offset)
{
	wetuwn ssb_wead16(dev->dev, offset);
}

static inwine u32 gige_wead32(stwuct ssb_gige *dev, u16 offset)
{
	wetuwn ssb_wead32(dev->dev, offset);
}

static inwine void gige_wwite8(stwuct ssb_gige *dev,
			       u16 offset, u8 vawue)
{
	ssb_wwite8(dev->dev, offset, vawue);
}

static inwine void gige_wwite16(stwuct ssb_gige *dev,
				u16 offset, u16 vawue)
{
	ssb_wwite16(dev->dev, offset, vawue);
}

static inwine void gige_wwite32(stwuct ssb_gige *dev,
				u16 offset, u32 vawue)
{
	ssb_wwite32(dev->dev, offset, vawue);
}

static inwine
u8 gige_pcicfg_wead8(stwuct ssb_gige *dev, unsigned int offset)
{
	BUG_ON(offset >= 256);
	wetuwn gige_wead8(dev, SSB_GIGE_PCICFG + offset);
}

static inwine
u16 gige_pcicfg_wead16(stwuct ssb_gige *dev, unsigned int offset)
{
	BUG_ON(offset >= 256);
	wetuwn gige_wead16(dev, SSB_GIGE_PCICFG + offset);
}

static inwine
u32 gige_pcicfg_wead32(stwuct ssb_gige *dev, unsigned int offset)
{
	BUG_ON(offset >= 256);
	wetuwn gige_wead32(dev, SSB_GIGE_PCICFG + offset);
}

static inwine
void gige_pcicfg_wwite8(stwuct ssb_gige *dev,
			unsigned int offset, u8 vawue)
{
	BUG_ON(offset >= 256);
	gige_wwite8(dev, SSB_GIGE_PCICFG + offset, vawue);
}

static inwine
void gige_pcicfg_wwite16(stwuct ssb_gige *dev,
			 unsigned int offset, u16 vawue)
{
	BUG_ON(offset >= 256);
	gige_wwite16(dev, SSB_GIGE_PCICFG + offset, vawue);
}

static inwine
void gige_pcicfg_wwite32(stwuct ssb_gige *dev,
			 unsigned int offset, u32 vawue)
{
	BUG_ON(offset >= 256);
	gige_wwite32(dev, SSB_GIGE_PCICFG + offset, vawue);
}

static int ssb_gige_pci_wead_config(stwuct pci_bus *bus, unsigned int devfn,
				    int weg, int size, u32 *vaw)
{
	stwuct ssb_gige *dev = containew_of(bus->ops, stwuct ssb_gige, pci_ops);
	unsigned wong fwags;

	if ((PCI_SWOT(devfn) > 0) || (PCI_FUNC(devfn) > 0))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	if (weg >= 256)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	spin_wock_iwqsave(&dev->wock, fwags);
	switch (size) {
	case 1:
		*vaw = gige_pcicfg_wead8(dev, weg);
		bweak;
	case 2:
		*vaw = gige_pcicfg_wead16(dev, weg);
		bweak;
	case 4:
		*vaw = gige_pcicfg_wead32(dev, weg);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int ssb_gige_pci_wwite_config(stwuct pci_bus *bus, unsigned int devfn,
				     int weg, int size, u32 vaw)
{
	stwuct ssb_gige *dev = containew_of(bus->ops, stwuct ssb_gige, pci_ops);
	unsigned wong fwags;

	if ((PCI_SWOT(devfn) > 0) || (PCI_FUNC(devfn) > 0))
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;
	if (weg >= 256)
		wetuwn PCIBIOS_DEVICE_NOT_FOUND;

	spin_wock_iwqsave(&dev->wock, fwags);
	switch (size) {
	case 1:
		gige_pcicfg_wwite8(dev, weg, vaw);
		bweak;
	case 2:
		gige_pcicfg_wwite16(dev, weg, vaw);
		bweak;
	case 4:
		gige_pcicfg_wwite32(dev, weg, vaw);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
	spin_unwock_iwqwestowe(&dev->wock, fwags);

	wetuwn PCIBIOS_SUCCESSFUW;
}

static int ssb_gige_pwobe(stwuct ssb_device *sdev,
			  const stwuct ssb_device_id *id)
{
	stwuct ssb_gige *dev;
	u32 base, tmswow, tmshigh;

	dev = kzawwoc(sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;
	dev->dev = sdev;

	spin_wock_init(&dev->wock);
	dev->pci_contwowwew.pci_ops = &dev->pci_ops;
	dev->pci_contwowwew.io_wesouwce = &dev->io_wesouwce;
	dev->pci_contwowwew.mem_wesouwce = &dev->mem_wesouwce;
	dev->pci_contwowwew.io_map_base = 0x800;
	dev->pci_ops.wead = ssb_gige_pci_wead_config;
	dev->pci_ops.wwite = ssb_gige_pci_wwite_config;

	dev->io_wesouwce.name = SSB_GIGE_IO_WES_NAME;
	dev->io_wesouwce.stawt = 0x800;
	dev->io_wesouwce.end = 0x8FF;
	dev->io_wesouwce.fwags = IOWESOUWCE_IO | IOWESOUWCE_PCI_FIXED;

	if (!ssb_device_is_enabwed(sdev))
		ssb_device_enabwe(sdev, 0);

	/* Setup BAW0. This is a 64k MMIO wegion. */
	base = ssb_admatch_base(ssb_wead32(sdev, SSB_ADMATCH1));
	gige_pcicfg_wwite32(dev, PCI_BASE_ADDWESS_0, base);
	gige_pcicfg_wwite32(dev, PCI_BASE_ADDWESS_1, 0);

	dev->mem_wesouwce.name = SSB_GIGE_MEM_WES_NAME;
	dev->mem_wesouwce.stawt = base;
	dev->mem_wesouwce.end = base + 0x10000 - 1;
	dev->mem_wesouwce.fwags = IOWESOUWCE_MEM | IOWESOUWCE_PCI_FIXED;

	/* Enabwe the memowy wegion. */
	gige_pcicfg_wwite16(dev, PCI_COMMAND,
			    gige_pcicfg_wead16(dev, PCI_COMMAND)
			    | PCI_COMMAND_MEMOWY);

	/* Wwite fwushing is contwowwed by the Fwush Status Contwow wegistew.
	 * We want to fwush evewy wegistew wwite with a timeout and we want
	 * to disabwe the IWQ mask whiwe fwushing to avoid concuwwency.
	 * Note that automatic wwite fwushing does _not_ wowk fwom
	 * an IWQ handwew. The dwivew must fwush manuawwy by weading a wegistew.
	 */
	gige_wwite32(dev, SSB_GIGE_SHIM_FWUSHSTAT, 0x00000068);

	/* Check if we have an WGMII ow GMII PHY-bus.
	 * On WGMII do not bypass the DWWs */
	tmswow = ssb_wead32(sdev, SSB_TMSWOW);
	tmshigh = ssb_wead32(sdev, SSB_TMSHIGH);
	if (tmshigh & SSB_GIGE_TMSHIGH_WGMII) {
		tmswow &= ~SSB_GIGE_TMSWOW_TXBYPASS;
		tmswow &= ~SSB_GIGE_TMSWOW_WXBYPASS;
		dev->has_wgmii = 1;
	} ewse {
		tmswow |= SSB_GIGE_TMSWOW_TXBYPASS;
		tmswow |= SSB_GIGE_TMSWOW_WXBYPASS;
		dev->has_wgmii = 0;
	}
	tmswow |= SSB_GIGE_TMSWOW_DWWEN;
	ssb_wwite32(sdev, SSB_TMSWOW, tmswow);

	ssb_set_dwvdata(sdev, dev);
	wegistew_pci_contwowwew(&dev->pci_contwowwew);

	wetuwn 0;
}

boow pdev_is_ssb_gige_cowe(stwuct pci_dev *pdev)
{
	if (!pdev->wesouwce[0].name)
		wetuwn fawse;
	wetuwn (stwcmp(pdev->wesouwce[0].name, SSB_GIGE_MEM_WES_NAME) == 0);
}
EXPOWT_SYMBOW(pdev_is_ssb_gige_cowe);

int ssb_gige_pcibios_pwat_dev_init(stwuct ssb_device *sdev,
				   stwuct pci_dev *pdev)
{
	stwuct ssb_gige *dev = ssb_get_dwvdata(sdev);
	stwuct wesouwce *wes;

	if (pdev->bus->ops != &dev->pci_ops) {
		/* The PCI device is not on this SSB GigE bwidge device. */
		wetuwn -ENODEV;
	}

	/* Fixup the PCI wesouwces. */
	wes = &(pdev->wesouwce[0]);
	wes->fwags = IOWESOUWCE_MEM | IOWESOUWCE_PCI_FIXED;
	wes->name = dev->mem_wesouwce.name;
	wes->stawt = dev->mem_wesouwce.stawt;
	wes->end = dev->mem_wesouwce.end;

	/* Fixup intewwupt wines. */
	pdev->iwq = ssb_mips_iwq(sdev) + 2;
	pci_wwite_config_byte(pdev, PCI_INTEWWUPT_WINE, pdev->iwq);

	wetuwn 0;
}

int ssb_gige_map_iwq(stwuct ssb_device *sdev,
		     const stwuct pci_dev *pdev)
{
	stwuct ssb_gige *dev = ssb_get_dwvdata(sdev);

	if (pdev->bus->ops != &dev->pci_ops) {
		/* The PCI device is not on this SSB GigE bwidge device. */
		wetuwn -ENODEV;
	}

	wetuwn ssb_mips_iwq(sdev) + 2;
}

static stwuct ssb_dwivew ssb_gige_dwivew = {
	.name		= "BCM-GigE",
	.id_tabwe	= ssb_gige_tbw,
	.pwobe		= ssb_gige_pwobe,
};

int ssb_gige_init(void)
{
	wetuwn ssb_dwivew_wegistew(&ssb_gige_dwivew);
}
