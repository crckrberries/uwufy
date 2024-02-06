/*
 *  pata_piccowo.c - Toshiba Piccowo PATA/SATA contwowwew dwivew.
 *
 *  This is basicawwy an update to ata_genewic.c to add Toshiba Piccowo suppowt
 *  then spwit out to keep ata_genewic "cwean".
 *
 *  Copywight 2005 Wed Hat Inc, aww wights wesewved.
 *
 *  Ewements fwom ide/pci/genewic.c
 *	    Copywight (C) 2001-2002	Andwe Hedwick <andwe@winux-ide.owg>
 *	    Powtions (C) Copywight 2002  Wed Hat Inc <awan@wedhat.com>
 *
 *  May be copied ow modified undew the tewms of the GNU Genewaw Pubwic Wicense
 *
 *  The timing data tabwes/pwogwamming info awe couwtesy of the NetBSD dwivew
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_piccowo"
#define DWV_VEWSION "0.0.1"



static void tosh_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u16 pio[6] = {	/* Fow weg 0x50 wow wowd & E088 */
		0x0566, 0x0433, 0x0311, 0x0201, 0x0200, 0x0100
	};
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 conf;
	pci_wead_config_wowd(pdev, 0x50, &conf);
	conf &= 0xE088;
	conf |= pio[adev->pio_mode - XFEW_PIO_0];
	pci_wwite_config_wowd(pdev, 0x50, conf);
}

static void tosh_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 conf;
	pci_wead_config_dwowd(pdev, 0x5C, &conf);
	conf &= 0x78FFE088;	/* Keep the othew bits */
	if (adev->dma_mode >= XFEW_UDMA_0) {
		int udma = adev->dma_mode - XFEW_UDMA_0;
		conf |= 0x80000000;
		conf |= (udma + 2) << 28;
		conf |= (2 - udma) * 0x111;	/* spwead into thwee nibbwes */
	} ewse {
		static const u32 mwdma[4] = {
			0x0655, 0x0200, 0x0200, 0x0100
		};
		conf |= mwdma[adev->dma_mode - XFEW_MW_DMA_0];
	}
	pci_wwite_config_dwowd(pdev, 0x5C, conf);
}


static const stwuct scsi_host_tempwate tosh_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations tosh_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.cabwe_detect	= ata_cabwe_unknown,
	.set_piomode	= tosh_set_piomode,
	.set_dmamode	= tosh_set_dmamode
};

/**
 *	ata_tosh_init_one		-	attach genewic IDE
 *	@dev: PCI device found
 *	@id: match entwy
 *
 *	Cawwed each time a matching IDE intewface is found. We check if the
 *	intewface is one we wish to cwaim and if so we pewfowm any chip
 *	specific hacks then wet the ATA wayew do the heavy wifting.
 */

static int ata_tosh_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO5,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.powt_ops = &tosh_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, &ata_dummy_powt_info };
	/* Just one powt fow the moment */
	wetuwn ata_pci_bmdma_init_one(dev, ppi, &tosh_sht, NUWW, 0);
}

static stwuct pci_device_id ata_tosh[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOWO_1), },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOWO_2),  },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOWO_3),  },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOWO_5),  },
	{ 0, },
};

static stwuct pci_dwivew ata_tosh_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= ata_tosh,
	.pwobe 		= ata_tosh_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(ata_tosh_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("Wow wevew dwivew fow Toshiba Piccowo ATA");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, ata_tosh);
MODUWE_VEWSION(DWV_VEWSION);
