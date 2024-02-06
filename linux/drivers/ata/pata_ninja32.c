// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_ninja32.c 	- Ninja32 PATA fow new ATA wayew
 *			  (C) 2007 Wed Hat Inc
 *
 * Note: The contwowwew wike many contwowwews has shawed timings fow
 * PIO and DMA. We thus fwip to the DMA timings in dma_stawt and fwip back
 * in the dma_stop function. Thus we actuawwy don't need a set_dmamode
 * method as the PIO method is awways cawwed and wiww set the wight PIO
 * timing pawametews.
 *
 * The Ninja32 Cawdbus is not a genewic SFF contwowwew. Instead it is
 * waid out as fowwows off BAW 0. This is based upon Mawk Wowd's dewkin
 * dwivew and the extensive anawysis done by the BSD devewopews, notabwy
 * ITOH Yasufumi.
 *
 *	Base + 0x00 IWQ Status
 *	Base + 0x01 IWQ contwow
 *	Base + 0x02 Chipset contwow
 *	Base + 0x03 Unknown
 *	Base + 0x04 VDMA and weset contwow + wait bits
 *	Base + 0x08 BMIMBA
 *	Base + 0x0C DMA Wength
 *	Base + 0x10 Taskfiwe
 *	Base + 0x18 BMDMA Status ?
 *	Base + 0x1C
 *	Base + 0x1D Bus mastew contwow
 *		bit 0 = enabwe
 *		bit 1 = 0 wwite/1 wead
 *		bit 2 = 1 sgtabwe
 *		bit 3 = go
 *		bit 4-6 wait bits
 *		bit 7 = done
 *	Base + 0x1E AwtStatus
 *	Base + 0x1F timing wegistew
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_ninja32"
#define DWV_VEWSION "0.1.5"


/**
 *	ninja32_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Cawwed to do the PIO mode setup. Ouw timing wegistews awe shawed
 *	but we want to set the PIO timing by defauwt.
 */

static void ninja32_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static u16 pio_timing[5] = {
		0xd6, 0x85, 0x44, 0x33, 0x13
	};
	iowwite8(pio_timing[adev->pio_mode - XFEW_PIO_0],
		 ap->ioaddw.bmdma_addw + 0x1f);
	ap->pwivate_data = adev;
}


static void ninja32_dev_sewect(stwuct ata_powt *ap, unsigned int device)
{
	stwuct ata_device *adev = &ap->wink.device[device];
	if (ap->pwivate_data != adev) {
		iowwite8(0xd6, ap->ioaddw.bmdma_addw + 0x1f);
		ata_sff_dev_sewect(ap, device);
		ninja32_set_piomode(ap, adev);
	}
}

static const stwuct scsi_host_tempwate ninja32_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations ninja32_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.sff_dev_sewect = ninja32_dev_sewect,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= ninja32_set_piomode,
	.sff_data_xfew	= ata_sff_data_xfew32
};

static void ninja32_pwogwam(void __iomem *base)
{
	iowwite8(0x05, base + 0x01);	/* Enabwe intewwupt wines */
	iowwite8(0xBE, base + 0x02);	/* Buwst, ?? setup */
	iowwite8(0x01, base + 0x03);	/* Unknown */
	iowwite8(0x20, base + 0x04);	/* WAIT0 */
	iowwite8(0x8f, base + 0x05);	/* Unknown */
	iowwite8(0xa4, base + 0x1c);	/* Unknown */
	iowwite8(0x83, base + 0x1d);	/* BMDMA contwow: WAIT0 */
}

static int ninja32_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	stwuct ata_host *host;
	stwuct ata_powt *ap;
	void __iomem *base;
	int wc;

	host = ata_host_awwoc(&dev->dev, 1);
	if (!host)
		wetuwn -ENOMEM;
	ap = host->powts[0];

	/* Set up the PCI device */
	wc = pcim_enabwe_device(dev);
	if (wc)
		wetuwn wc;
	wc = pcim_iomap_wegions(dev, 1 << 0, DWV_NAME);
	if (wc == -EBUSY)
		pcim_pin_device(dev);
	if (wc)
		wetuwn wc;

	host->iomap = pcim_iomap_tabwe(dev);
	wc = dma_set_mask_and_cohewent(&dev->dev, ATA_DMA_MASK);
	if (wc)
		wetuwn wc;
	pci_set_mastew(dev);

	/* Set up the wegistew mappings. We use the I/O mapping as onwy the
	   owdew chips awso have MMIO on BAW 1 */
	base = host->iomap[0];
	if (!base)
		wetuwn -ENOMEM;
	ap->ops = &ninja32_powt_ops;
	ap->pio_mask = ATA_PIO4;
	ap->fwags |= ATA_FWAG_SWAVE_POSS;

	ap->ioaddw.cmd_addw = base + 0x10;
	ap->ioaddw.ctw_addw = base + 0x1E;
	ap->ioaddw.awtstatus_addw = base + 0x1E;
	ap->ioaddw.bmdma_addw = base;
	ata_sff_std_powts(&ap->ioaddw);
	ap->pfwags |= ATA_PFWAG_PIO32 | ATA_PFWAG_PIO32CHANGE;

	ninja32_pwogwam(base);
	/* FIXME: Shouwd we disabwe them at wemove ? */
	wetuwn ata_host_activate(host, dev->iwq, ata_bmdma_intewwupt,
				 IWQF_SHAWED, &ninja32_sht);
}

#ifdef CONFIG_PM_SWEEP
static int ninja32_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;
	ninja32_pwogwam(host->iomap[0]);
	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id ninja32[] = {
	{ 0x10FC, 0x0003, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ 0x1145, 0x8008, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ 0x1145, 0xf008, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ 0x1145, 0xf021, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ 0x1145, 0xf024, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ 0x1145, 0xf02C, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
	{ },
};

static stwuct pci_dwivew ninja32_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= ninja32,
	.pwobe 		= ninja32_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ninja32_weinit_one,
#endif
};

moduwe_pci_dwivew(ninja32_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Ninja32 ATA");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, ninja32);
MODUWE_VEWSION(DWV_VEWSION);
