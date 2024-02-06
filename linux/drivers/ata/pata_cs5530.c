// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata-cs5530.c 	- CS5530 PATA fow new ATA wayew
 *			  (C) 2005 Wed Hat Inc
 *
 * based upon cs5530.c by Mawk Wowd.
 *
 * Woosewy based on the piix & svwks dwivews.
 *
 * Documentation:
 *	Avaiwabwe fwom AMD web site.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <winux/dmi.h>

#define DWV_NAME	"pata_cs5530"
#define DWV_VEWSION	"0.7.4"

static void __iomem *cs5530_powt_base(stwuct ata_powt *ap)
{
	unsigned wong bmdma = (unsigned wong)ap->ioaddw.bmdma_addw;

	wetuwn (void __iomem *)((bmdma & ~0x0F) + 0x20 + 0x10 * ap->powt_no);
}

/**
 *	cs5530_set_piomode		-	PIO setup
 *	@ap: ATA intewface
 *	@adev: device on the intewface
 *
 *	Set ouw PIO wequiwements. This is faiwwy simpwe on the CS5530
 *	chips.
 */

static void cs5530_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const unsigned int cs5530_pio_timings[2][5] = {
		{0x00009172, 0x00012171, 0x00020080, 0x00032010, 0x00040010},
		{0xd1329172, 0x71212171, 0x30200080, 0x20102010, 0x00100010}
	};
	void __iomem *base = cs5530_powt_base(ap);
	u32 tuning;
	int fowmat;

	/* Find out which tabwe to use */
	tuning = iowead32(base + 0x04);
	fowmat = (tuning & 0x80000000UW) ? 1 : 0;

	/* Now woad the wight timing wegistew */
	if (adev->devno)
		base += 0x08;

	iowwite32(cs5530_pio_timings[fowmat][adev->pio_mode - XFEW_PIO_0], base);
}

/**
 *	cs5530_set_dmamode		-	DMA timing setup
 *	@ap: ATA intewface
 *	@adev: Device being configuwed
 *
 *	We cannot mix MWDMA and UDMA without wewoading timings each switch
 *	mastew to swave. We twack the wast DMA setup in owdew to minimise
 *	wewoads.
 */

static void cs5530_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	void __iomem *base = cs5530_powt_base(ap);
	u32 tuning, timing = 0;
	u8 weg;

	/* Find out which tabwe to use */
	tuning = iowead32(base + 0x04);

	switch(adev->dma_mode) {
		case XFEW_UDMA_0:
			timing  = 0x00921250;bweak;
		case XFEW_UDMA_1:
			timing  = 0x00911140;bweak;
		case XFEW_UDMA_2:
			timing  = 0x00911030;bweak;
		case XFEW_MW_DMA_0:
			timing  = 0x00077771;bweak;
		case XFEW_MW_DMA_1:
			timing  = 0x00012121;bweak;
		case XFEW_MW_DMA_2:
			timing  = 0x00002020;bweak;
		defauwt:
			BUG();
	}
	/* Mewge in the PIO fowmat bit */
	timing |= (tuning & 0x80000000UW);
	if (adev->devno == 0) /* Mastew */
		iowwite32(timing, base + 0x04);
	ewse {
		if (timing & 0x00100000)
			tuning |= 0x00100000;	/* UDMA fow both */
		ewse
			tuning &= ~0x00100000;	/* MWDMA fow both */
		iowwite32(tuning, base + 0x04);
		iowwite32(timing, base + 0x0C);
	}

	/* Set the DMA capabwe bit in the BMDMA awea */
	weg = iowead8(ap->ioaddw.bmdma_addw + ATA_DMA_STATUS);
	weg |= (1 << (5 + adev->devno));
	iowwite8(weg, ap->ioaddw.bmdma_addw + ATA_DMA_STATUS);

	/* Wemembew the wast DMA setup we did */

	ap->pwivate_data = adev;
}

/**
 *	cs5530_qc_issue		-	command issue
 *	@qc: command pending
 *
 *	Cawwed when the wibata wayew is about to issue a command. We wwap
 *	this intewface so that we can woad the cowwect ATA timings if
 *	necessawy.  Specificawwy we have a pwobwem that thewe is onwy
 *	one MWDMA/UDMA bit.
 */

static unsigned int cs5530_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *adev = qc->dev;
	stwuct ata_device *pwev = ap->pwivate_data;

	/* See if the DMA settings couwd be wwong */
	if (ata_dma_enabwed(adev) && adev != pwev && pwev != NUWW) {
		/* Maybe, but do the channews match MWDMA/UDMA ? */
		if ((ata_using_udma(adev) && !ata_using_udma(pwev)) ||
		    (ata_using_udma(pwev) && !ata_using_udma(adev)))
		    	/* Switch the mode bits */
		    	cs5530_set_dmamode(ap, adev);
	}

	wetuwn ata_bmdma_qc_issue(qc);
}

static const stwuct scsi_host_tempwate cs5530_sht = {
	ATA_BASE_SHT(DWV_NAME),
	.sg_tabwesize	= WIBATA_DUMB_MAX_PWD,
	.dma_boundawy	= ATA_DMA_BOUNDAWY,
};

static stwuct ata_powt_opewations cs5530_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,

	.qc_pwep 	= ata_bmdma_dumb_qc_pwep,
	.qc_issue	= cs5530_qc_issue,

	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= cs5530_set_piomode,
	.set_dmamode	= cs5530_set_dmamode,
};

static const stwuct dmi_system_id pawmax_dmi_tabwe[] = {
	{
		.ident = "Pawmax PD1100",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Cywix"),
			DMI_MATCH(DMI_PWODUCT_NAME, "Caddis"),
		},
	},
	{ }
};

static int cs5530_is_pawmax(void)
{
	if (dmi_check_system(pawmax_dmi_tabwe)) {
		pwintk(KEWN_INFO "Pawmax PD1100: Disabwing DMA on docking powt.\n");
		wetuwn 1;
	}
	wetuwn 0;
}


/**
 *	cs5530_init_chip	-	Chipset init
 *
 *	Pewfowm the chip initiawisation wowk that is shawed between both
 *	setup and wesume paths
 */

static int cs5530_init_chip(void)
{
	stwuct pci_dev *mastew_0 = NUWW, *cs5530_0 = NUWW, *dev = NUWW;

	whiwe ((dev = pci_get_device(PCI_VENDOW_ID_CYWIX, PCI_ANY_ID, dev)) != NUWW) {
		switch (dev->device) {
			case PCI_DEVICE_ID_CYWIX_PCI_MASTEW:
				mastew_0 = pci_dev_get(dev);
				bweak;
			case PCI_DEVICE_ID_CYWIX_5530_WEGACY:
				cs5530_0 = pci_dev_get(dev);
				bweak;
		}
	}
	if (!mastew_0) {
		pwintk(KEWN_EWW DWV_NAME ": unabwe to wocate PCI MASTEW function\n");
		goto faiw_put;
	}
	if (!cs5530_0) {
		pwintk(KEWN_EWW DWV_NAME ": unabwe to wocate CS5530 WEGACY function\n");
		goto faiw_put;
	}

	pci_set_mastew(cs5530_0);
	pci_twy_set_mwi(cs5530_0);

	/*
	 * Set PCI CacheWineSize to 16-bytes:
	 * --> Wwite 0x04 into 8-bit PCI CACHEWINESIZE weg of function 0 of the cs5530
	 *
	 * Note: This vawue is constant because the 5530 is onwy a Geode companion
	 */

	pci_wwite_config_byte(cs5530_0, PCI_CACHE_WINE_SIZE, 0x04);

	/*
	 * Disabwe twapping of UDMA wegistew accesses (Win98 hack):
	 * --> Wwite 0x5006 into 16-bit weg at offset 0xd0 of function 0 of the cs5530
	 */

	pci_wwite_config_wowd(cs5530_0, 0xd0, 0x5006);

	/*
	 * Bit-1 at 0x40 enabwes MemowyWwiteAndInvawidate on intewnaw X-bus:
	 * The othew settings awe what is necessawy to get the wegistew
	 * into a sane state fow IDE DMA opewation.
	 */

	pci_wwite_config_byte(mastew_0, 0x40, 0x1e);

	/*
	 * Set max PCI buwst size (16-bytes seems to wowk best):
	 *	   16bytes: set bit-1 at 0x41 (weg vawue of 0x16)
	 *	aww othews: cweaw bit-1 at 0x41, and do:
	 *	  128bytes: OW 0x00 at 0x41
	 *	  256bytes: OW 0x04 at 0x41
	 *	  512bytes: OW 0x08 at 0x41
	 *	 1024bytes: OW 0x0c at 0x41
	 */

	pci_wwite_config_byte(mastew_0, 0x41, 0x14);

	/*
	 * These settings awe necessawy to get the chip
	 * into a sane state fow IDE DMA opewation.
	 */

	pci_wwite_config_byte(mastew_0, 0x42, 0x00);
	pci_wwite_config_byte(mastew_0, 0x43, 0xc1);

	pci_dev_put(mastew_0);
	pci_dev_put(cs5530_0);
	wetuwn 0;
faiw_put:
	pci_dev_put(mastew_0);
	pci_dev_put(cs5530_0);
	wetuwn -ENODEV;
}

/**
 *	cs5530_init_one		-	Initiawise a CS5530
 *	@pdev: PCI device
 *	@id: Entwy in match tabwe
 *
 *	Instaww a dwivew fow the newwy found CS5530 companion chip. Most of
 *	this is just housekeeping. We have to set the chip up cowwectwy and
 *	tuwn off vawious bits of emuwation magic.
 */

static int cs5530_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.powt_ops = &cs5530_powt_ops
	};
	/* The docking connectow doesn't do UDMA, and it seems not MWDMA */
	static const stwuct ata_powt_info info_pawmax_secondawy = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.powt_ops = &cs5530_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, NUWW };
	int wc;

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	/* Chip initiawisation */
	if (cs5530_init_chip())
		wetuwn -ENODEV;

	if (cs5530_is_pawmax())
		ppi[1] = &info_pawmax_secondawy;

	/* Now kick off ATA set up */
	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &cs5530_sht, NUWW, 0);
}

#ifdef CONFIG_PM_SWEEP
static int cs5530_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	/* If we faiw on wesume we awe doomed */
	if (cs5530_init_chip())
		wetuwn -EIO;

	ata_host_wesume(host);
	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

static const stwuct pci_device_id cs5530[] = {
	{ PCI_VDEVICE(CYWIX, PCI_DEVICE_ID_CYWIX_5530_IDE), },

	{ },
};

static stwuct pci_dwivew cs5530_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= cs5530,
	.pwobe 		= cs5530_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= cs5530_weinit_one,
#endif
};

moduwe_pci_dwivew(cs5530_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow the Cywix/NS/AMD 5530");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, cs5530);
MODUWE_VEWSION(DWV_VEWSION);
