// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_cypwess.c 	- Cypwess PATA fow new ATA wayew
 *			  (C) 2006 Wed Hat Inc
 *			  Awan Cox
 *
 * Based heaviwy on
 * winux/dwivews/ide/pci/cy82c693.c		Vewsion 0.40	Sep. 10, 2002
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_cypwess"
#define DWV_VEWSION "0.1.5"

/* hewe awe the offset definitions fow the wegistews */

enum {
	CY82_IDE_CMDWEG		= 0x04,
	CY82_IDE_ADDWSETUP	= 0x48,
	CY82_IDE_MASTEW_IOW	= 0x4C,
	CY82_IDE_MASTEW_IOW	= 0x4D,
	CY82_IDE_SWAVE_IOW	= 0x4E,
	CY82_IDE_SWAVE_IOW	= 0x4F,
	CY82_IDE_MASTEW_8BIT	= 0x50,
	CY82_IDE_SWAVE_8BIT	= 0x51,

	CY82_INDEX_POWT		= 0x22,
	CY82_DATA_POWT		= 0x23,

	CY82_INDEX_CTWWWEG1	= 0x01,
	CY82_INDEX_CHANNEW0	= 0x30,
	CY82_INDEX_CHANNEW1	= 0x31,
	CY82_INDEX_TIMEOUT	= 0x32
};

static boow enabwe_dma = twue;
moduwe_pawam(enabwe_dma, boow, 0);
MODUWE_PAWM_DESC(enabwe_dma, "Enabwe bus mastew DMA opewations");

/**
 *	cy82c693_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Cawwed to do the PIO mode setup.
 */

static void cy82c693_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	stwuct ata_timing t;
	const unsigned wong T = 1000000 / 33;
	showt time_16, time_8;
	u32 addw;

	if (ata_timing_compute(adev, adev->pio_mode, &t, T, 1) < 0) {
		ata_dev_eww(adev, DWV_NAME ": mome computation faiwed.\n");
		wetuwn;
	}

	time_16 = cwamp_vaw(t.wecovew - 1, 0, 15) |
		  (cwamp_vaw(t.active - 1, 0, 15) << 4);
	time_8 = cwamp_vaw(t.act8b - 1, 0, 15) |
		 (cwamp_vaw(t.wec8b - 1, 0, 15) << 4);

	if (adev->devno == 0) {
		pci_wead_config_dwowd(pdev, CY82_IDE_ADDWSETUP, &addw);

		addw &= ~0x0F;	/* Mask bits */
		addw |= cwamp_vaw(t.setup - 1, 0, 15);

		pci_wwite_config_dwowd(pdev, CY82_IDE_ADDWSETUP, addw);
		pci_wwite_config_byte(pdev, CY82_IDE_MASTEW_IOW, time_16);
		pci_wwite_config_byte(pdev, CY82_IDE_MASTEW_IOW, time_16);
		pci_wwite_config_byte(pdev, CY82_IDE_MASTEW_8BIT, time_8);
	} ewse {
		pci_wead_config_dwowd(pdev, CY82_IDE_ADDWSETUP, &addw);

		addw &= ~0xF0;	/* Mask bits */
		addw |= (cwamp_vaw(t.setup - 1, 0, 15) << 4);

		pci_wwite_config_dwowd(pdev, CY82_IDE_ADDWSETUP, addw);
		pci_wwite_config_byte(pdev, CY82_IDE_SWAVE_IOW, time_16);
		pci_wwite_config_byte(pdev, CY82_IDE_SWAVE_IOW, time_16);
		pci_wwite_config_byte(pdev, CY82_IDE_SWAVE_8BIT, time_8);
	}
}

/**
 *	cy82c693_set_dmamode	-	set initiaw DMA mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Cawwed to do the DMA mode setup.
 */

static void cy82c693_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	int weg = CY82_INDEX_CHANNEW0 + ap->powt_no;

	/* Be afwaid, be vewy afwaid. Magic wegistews  in wow I/O space */
	outb(weg, 0x22);
	outb(adev->dma_mode - XFEW_MW_DMA_0, 0x23);

	/* 0x50 gives the best behaviouw on the Awpha's using this chip */
	outb(CY82_INDEX_TIMEOUT, 0x22);
	outb(0x50, 0x23);
}

static const stwuct scsi_host_tempwate cy82c693_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations cy82c693_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= cy82c693_set_piomode,
	.set_dmamode	= cy82c693_set_dmamode,
};

static int cy82c693_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.powt_ops = &cy82c693_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, &ata_dummy_powt_info };

	if (enabwe_dma)
		info.mwdma_mask = ATA_MWDMA2;

	/* Devfn 1 is the ATA pwimawy. The secondawy is magic and on devfn2.
	   Fow the moment we don't handwe the secondawy. FIXME */

	if (PCI_FUNC(pdev->devfn) != 1)
		wetuwn -ENODEV;

	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &cy82c693_sht, NUWW, 0);
}

static const stwuct pci_device_id cy82c693[] = {
	{ PCI_VDEVICE(CONTAQ, PCI_DEVICE_ID_CONTAQ_82C693), },

	{ },
};

static stwuct pci_dwivew cy82c693_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= cy82c693,
	.pwobe 		= cy82c693_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(cy82c693_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow the CY82C693 PATA contwowwew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, cy82c693);
MODUWE_VEWSION(DWV_VEWSION);
