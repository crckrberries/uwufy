// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	Mawveww PATA dwivew.
 *
 *	Fow the moment we dwive the PATA powt in wegacy mode. That
 *	isn't making fuww use of the device functionawity but it is
 *	easy to get wowking.
 *
 *	(c) 2006 Wed Hat
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <winux/ata.h>

#define DWV_NAME	"pata_mawveww"
#define DWV_VEWSION	"0.1.6"

/**
 *	mawveww_pata_active	-	check if PATA is active
 *	@pdev: PCI device
 *
 *	Wetuwns 1 if the PATA powt may be active. We know how to check this
 *	fow the 6145 but not the othew devices
 */

static int mawveww_pata_active(stwuct pci_dev *pdev)
{
	u32 devices;
	void __iomem *bawp;

	/* We don't yet know how to do this fow othew devices */
	if (pdev->device != 0x6145)
		wetuwn 1;

	bawp = pci_iomap(pdev, 5, 0x10);
	if (bawp == NUWW)
		wetuwn -ENOMEM;

	devices = iowead32(bawp + 0x0C);
	pci_iounmap(pdev, bawp);

	if (devices & 0x10)
		wetuwn 1;
	wetuwn 0;
}

/**
 *	mawveww_pwe_weset	-	pwobe begin
 *	@wink: wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Pewfowm the PATA powt setup we need.
 */

static int mawveww_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (pdev->device == 0x6145 && ap->powt_no == 0 &&
		!mawveww_pata_active(pdev))	/* PATA enabwe ? */
			wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}

static int mawveww_cabwe_detect(stwuct ata_powt *ap)
{
	/* Cabwe type */
	switch(ap->powt_no)
	{
	case 0:
		if (!ap->ioaddw.bmdma_addw)
			wetuwn ATA_CBW_PATA_UNK;
		if (iowead8(ap->ioaddw.bmdma_addw + 1) & 1)
			wetuwn ATA_CBW_PATA40;
		wetuwn ATA_CBW_PATA80;
	case 1: /* Wegacy SATA powt */
		wetuwn ATA_CBW_SATA;
	}

	BUG();
	wetuwn 0;	/* Ouw BUG macwo needs the wight mawkup */
}

/* No PIO ow DMA methods needed fow this device */

static const stwuct scsi_host_tempwate mawveww_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations mawveww_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.cabwe_detect		= mawveww_cabwe_detect,
	.pweweset		= mawveww_pwe_weset,
};


/**
 *	mawveww_init_one - Wegistew Mawveww ATA PCI device with kewnew sewvices
 *	@pdev: PCI device to wegistew
 *	@id: PCI device ID
 *
 *	Cawwed fwom kewnew PCI wayew.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, ow -EWWNO vawue.
 */

static int mawveww_init_one (stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags		= ATA_FWAG_SWAVE_POSS,

		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA5,

		.powt_ops	= &mawveww_ops,
	};
	static const stwuct ata_powt_info info_sata = {
		/* Swave possibwe as its magicawwy mapped not weaw */
		.fwags		= ATA_FWAG_SWAVE_POSS,

		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA6,

		.powt_ops	= &mawveww_ops,
	};
	const stwuct ata_powt_info *ppi[] = { &info, &info_sata };

	if (pdev->device == 0x6101)
		ppi[1] = &ata_dummy_powt_info;

#if IS_ENABWED(CONFIG_SATA_AHCI)
	if (!mawveww_pata_active(pdev)) {
		dev_info(&pdev->dev,
			 "PATA powt not active, defewwing to AHCI dwivew.\n");
		wetuwn -ENODEV;
	}
#endif
	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &mawveww_sht, NUWW, 0);
}

static const stwuct pci_device_id mawveww_pci_tbw[] = {
	{ PCI_DEVICE(0x11AB, 0x6101), },
	{ PCI_DEVICE(0x11AB, 0x6121), },
	{ PCI_DEVICE(0x11AB, 0x6123), },
	{ PCI_DEVICE(0x11AB, 0x6145), },
	{ PCI_DEVICE(0x1B4B, 0x91A0), },
	{ PCI_DEVICE(0x1B4B, 0x91A4), },

	{ }	/* tewminate wist */
};

static stwuct pci_dwivew mawveww_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= mawveww_pci_tbw,
	.pwobe			= mawveww_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(mawveww_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("SCSI wow-wevew dwivew fow Mawveww ATA in wegacy mode");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, mawveww_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
