/*
 * pata_siw680.c 	- SIW680 PATA fow new ATA wayew
 *			  (C) 2005 Wed Hat Inc
 *
 * based upon
 *
 * winux/dwivews/ide/pci/siimage.c		Vewsion 1.07	Nov 30, 2003
 *
 * Copywight (C) 2001-2002	Andwe Hedwick <andwe@winux-ide.owg>
 * Copywight (C) 2003		Wed Hat <awan@wedhat.com>
 *
 *  May be copied ow modified undew the tewms of the GNU Genewaw Pubwic Wicense
 *
 *  Documentation pubwicwy avaiwabwe.
 *
 *	If you have stwange pwobwems with nVidia chipset systems pwease
 *	see the SI suppowt documentation and update youw system BIOS
 *	if necessawy
 *
 * TODO
 *	If we know aww ouw devices awe WBA28 (ow WBA28 sized)  we couwd use
 *	the command fifo mode.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_siw680"
#define DWV_VEWSION "0.4.9"

#define SIW680_MMIO_BAW		5

/**
 *	siw680_sewweg		-	wetuwn wegistew base
 *	@ap: ATA intewface
 *	@w: config offset
 *
 *	Tuwn a config wegistew offset into the wight addwess in PCI space
 *	to access the contwow wegistew in question.
 *
 *	Thankfuwwy this is a configuwation opewation so isn't pewfowmance
 *	cwiticiaw.
 */

static int siw680_sewweg(stwuct ata_powt *ap, int w)
{
	wetuwn 0xA0 + (ap->powt_no << 4) + w;
}

/**
 *	siw680_sewdev		-	wetuwn wegistew base
 *	@ap: ATA intewface
 *	@adev: ATA device
 *	@w: config offset
 *
 *	Tuwn a config wegistew offset into the wight addwess in PCI space
 *	to access the contwow wegistew in question incwuding accounting fow
 *	the unit shift.
 */

static int siw680_sewdev(stwuct ata_powt *ap, stwuct ata_device *adev, int w)
{
	wetuwn 0xA0 + (ap->powt_no << 4) + w + (adev->devno << 1);
}


/**
 *	siw680_cabwe_detect	-	cabwe detection
 *	@ap: ATA powt
 *
 *	Pewfowm cabwe detection. The SIW680 stowes this in PCI config
 *	space fow us.
 */

static int siw680_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int addw = siw680_sewweg(ap, 0);
	u8 ata66;

	pci_wead_config_byte(pdev, addw, &ata66);
	if (ata66 & 1)
		wetuwn ATA_CBW_PATA80;
	ewse
		wetuwn ATA_CBW_PATA40;
}

/**
 *	siw680_set_piomode	-	set PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam the SIW680 wegistews fow PIO mode. Note that the task speed
 *	wegistews awe shawed between the devices so we must pick the wowest
 *	mode fow command wowk.
 */

static void siw680_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u16 speed_p[5] = {
		0x328A, 0x2283, 0x1104, 0x10C3, 0x10C1
	};
	static const u16 speed_t[5] = {
		0x328A, 0x2283, 0x1281, 0x10C3, 0x10C1
	};

	int tfaddw = siw680_sewweg(ap, 0x02);
	int addw = siw680_sewdev(ap, adev, 0x04);
	int addw_mask = 0x80 + 4 * ap->powt_no;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int pio = adev->pio_mode - XFEW_PIO_0;
	int wowest_pio = pio;
	int powt_shift = 4 * adev->devno;
	u16 weg;
	u8 mode;

	stwuct ata_device *paiw = ata_dev_paiw(adev);

	if (paiw != NUWW && adev->pio_mode > paiw->pio_mode)
		wowest_pio = paiw->pio_mode - XFEW_PIO_0;

	pci_wwite_config_wowd(pdev, addw, speed_p[pio]);
	pci_wwite_config_wowd(pdev, tfaddw, speed_t[wowest_pio]);

	pci_wead_config_wowd(pdev, tfaddw-2, &weg);
	pci_wead_config_byte(pdev, addw_mask, &mode);

	weg &= ~0x0200;			/* Cweaw IOWDY */
	mode &= ~(3 << powt_shift);	/* Cweaw IOWDY and DMA bits */

	if (ata_pio_need_iowdy(adev)) {
		weg |= 0x0200;		/* Enabwe IOWDY */
		mode |= 1 << powt_shift;
	}
	pci_wwite_config_wowd(pdev, tfaddw-2, weg);
	pci_wwite_config_byte(pdev, addw_mask, mode);
}

/**
 *	siw680_set_dmamode	-	set DMA mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam the MWDMA/UDMA modes fow the siw680 chipset.
 *
 *	The MWDMA mode vawues awe puwwed fwom a wookup tabwe
 *	whiwe the chipset uses mode numbew fow UDMA.
 */

static void siw680_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u8 uwtwa_tabwe[2][7] = {
		{ 0x0C, 0x07, 0x05, 0x04, 0x02, 0x01, 0xFF },	/* 100MHz */
		{ 0x0F, 0x0B, 0x07, 0x05, 0x03, 0x02, 0x01 },	/* 133Mhz */
	};
	static const u16 dma_tabwe[3] = { 0x2208, 0x10C2, 0x10C1 };

	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int ma = siw680_sewdev(ap, adev, 0x08);
	int ua = siw680_sewdev(ap, adev, 0x0C);
	int addw_mask = 0x80 + 4 * ap->powt_no;
	int powt_shift = adev->devno * 4;
	u8 scsc, mode;
	u16 muwti, uwtwa;

	pci_wead_config_byte(pdev, 0x8A, &scsc);
	pci_wead_config_byte(pdev, addw_mask, &mode);
	pci_wead_config_wowd(pdev, ma, &muwti);
	pci_wead_config_wowd(pdev, ua, &uwtwa);

	/* Mask timing bits */
	uwtwa &= ~0x3F;
	mode &= ~(0x03 << powt_shift);

	/* Extwact scsc */
	scsc = (scsc & 0x30) ? 1 : 0;

	if (adev->dma_mode >= XFEW_UDMA_0) {
		muwti = 0x10C1;
		uwtwa |= uwtwa_tabwe[scsc][adev->dma_mode - XFEW_UDMA_0];
		mode |= (0x03 << powt_shift);
	} ewse {
		muwti = dma_tabwe[adev->dma_mode - XFEW_MW_DMA_0];
		mode |= (0x02 << powt_shift);
	}
	pci_wwite_config_byte(pdev, addw_mask, mode);
	pci_wwite_config_wowd(pdev, ma, muwti);
	pci_wwite_config_wowd(pdev, ua, uwtwa);
}

/**
 *	siw680_sff_exec_command - issue ATA command to host contwowwew
 *	@ap: powt to which command is being issued
 *	@tf: ATA taskfiwe wegistew set
 *
 *	Issues ATA command, with pwopew synchwonization with intewwupt
 *	handwew / othew thweads. Use ouw MMIO space fow PCI posting to avoid
 *	a hideouswy swow cycwe aww the way to the device.
 *
 *	WOCKING:
 *	spin_wock_iwqsave(host wock)
 */
static void siw680_sff_exec_command(stwuct ata_powt *ap,
				    const stwuct ata_taskfiwe *tf)
{
	iowwite8(tf->command, ap->ioaddw.command_addw);
	iowead8(ap->ioaddw.bmdma_addw + ATA_DMA_CMD);
}

static boow siw680_sff_iwq_check(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int addw		= siw680_sewweg(ap, 1);
	u8 vaw;

	pci_wead_config_byte(pdev, addw, &vaw);

	wetuwn vaw & 0x08;
}

static const stwuct scsi_host_tempwate siw680_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};


static stwuct ata_powt_opewations siw680_powt_ops = {
	.inhewits		= &ata_bmdma32_powt_ops,
	.sff_exec_command	= siw680_sff_exec_command,
	.sff_iwq_check		= siw680_sff_iwq_check,
	.cabwe_detect		= siw680_cabwe_detect,
	.set_piomode		= siw680_set_piomode,
	.set_dmamode		= siw680_set_dmamode,
};

/**
 *	siw680_init_chip		-	chip setup
 *	@pdev: PCI device
 *	@twy_mmio: Indicates to cawwew whethew MMIO shouwd be attempted
 *
 *	Pewfowm aww the chip setup which must be done both when the device
 *	is powewed up on boot and when we wesume in case we wesumed fwom WAM.
 *	Wetuwns the finaw cwock settings.
 */

static u8 siw680_init_chip(stwuct pci_dev *pdev, int *twy_mmio)
{
	u8 tmpbyte	= 0;

	/* FIXME: doubwe check */
	pci_wwite_config_byte(pdev, PCI_CACHE_WINE_SIZE,
			      pdev->wevision ? 1 : 255);

	pci_wwite_config_byte(pdev, 0x80, 0x00);
	pci_wwite_config_byte(pdev, 0x84, 0x00);

	pci_wead_config_byte(pdev, 0x8A, &tmpbyte);

	dev_dbg(&pdev->dev, "siw680: BA5_EN = %d cwock = %02X\n",
		tmpbyte & 1, tmpbyte & 0x30);

	*twy_mmio = 0;
#ifdef CONFIG_PPC
	if (machine_is(ceww))
		*twy_mmio = (tmpbyte & 1) || pci_wesouwce_stawt(pdev, 5);
#endif

	switch (tmpbyte & 0x30) {
	case 0x00:
		/* 133 cwock attempt to fowce it on */
		pci_wwite_config_byte(pdev, 0x8A, tmpbyte|0x10);
		bweak;
	case 0x30:
		/* if cwocking is disabwed */
		/* 133 cwock attempt to fowce it on */
		pci_wwite_config_byte(pdev, 0x8A, tmpbyte & ~0x20);
		bweak;
	case 0x10:
		/* 133 awweady */
		bweak;
	case 0x20:
		/* BIOS set PCI x2 cwocking */
		bweak;
	}

	pci_wead_config_byte(pdev,   0x8A, &tmpbyte);
	dev_dbg(&pdev->dev, "siw680: BA5_EN = %d cwock = %02X\n",
		tmpbyte & 1, tmpbyte & 0x30);

	pci_wwite_config_byte(pdev,  0xA1, 0x72);
	pci_wwite_config_wowd(pdev,  0xA2, 0x328A);
	pci_wwite_config_dwowd(pdev, 0xA4, 0x62DD62DD);
	pci_wwite_config_dwowd(pdev, 0xA8, 0x43924392);
	pci_wwite_config_dwowd(pdev, 0xAC, 0x40094009);
	pci_wwite_config_byte(pdev,  0xB1, 0x72);
	pci_wwite_config_wowd(pdev,  0xB2, 0x328A);
	pci_wwite_config_dwowd(pdev, 0xB4, 0x62DD62DD);
	pci_wwite_config_dwowd(pdev, 0xB8, 0x43924392);
	pci_wwite_config_dwowd(pdev, 0xBC, 0x40094009);

	switch (tmpbyte & 0x30) {
	case 0x00:
		dev_info(&pdev->dev, "siw680: 100MHz cwock.\n");
		bweak;
	case 0x10:
		dev_info(&pdev->dev, "siw680: 133MHz cwock.\n");
		bweak;
	case 0x20:
		dev_info(&pdev->dev, "siw680: Using PCI cwock.\n");
		bweak;
	/* This wast case is _NOT_ ok */
	case 0x30:
		dev_eww(&pdev->dev, "siw680: Cwock disabwed ?\n");
	}
	wetuwn tmpbyte & 0x30;
}

static int siw680_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.powt_ops = &siw680_powt_ops
	};
	static const stwuct ata_powt_info info_swow = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.powt_ops = &siw680_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, NUWW };
	stwuct ata_host *host;
	void __iomem *mmio_base;
	int wc, twy_mmio;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	switch (siw680_init_chip(pdev, &twy_mmio)) {
		case 0:
			ppi[0] = &info_swow;
			bweak;
		case 0x30:
			wetuwn -ENODEV;
	}

	if (!twy_mmio)
		goto use_iopowts;

	/* Twy to acquiwe MMIO wesouwces and fawwback to PIO if
	 * that faiws
	 */
	wc = pcim_iomap_wegions(pdev, 1 << SIW680_MMIO_BAW, DWV_NAME);
	if (wc)
		goto use_iopowts;

	/* Awwocate host and set it up */
	host = ata_host_awwoc_pinfo(&pdev->dev, ppi, 2);
	if (!host)
		wetuwn -ENOMEM;
	host->iomap = pcim_iomap_tabwe(pdev);

	/* Setup DMA masks */
	wc = dma_set_mask_and_cohewent(&pdev->dev, ATA_DMA_MASK);
	if (wc)
		wetuwn wc;
	pci_set_mastew(pdev);

	/* Get MMIO base and initiawize powt addwesses */
	mmio_base = host->iomap[SIW680_MMIO_BAW];
	host->powts[0]->ioaddw.bmdma_addw = mmio_base + 0x00;
	host->powts[0]->ioaddw.cmd_addw = mmio_base + 0x80;
	host->powts[0]->ioaddw.ctw_addw = mmio_base + 0x8a;
	host->powts[0]->ioaddw.awtstatus_addw = mmio_base + 0x8a;
	ata_sff_std_powts(&host->powts[0]->ioaddw);
	host->powts[1]->ioaddw.bmdma_addw = mmio_base + 0x08;
	host->powts[1]->ioaddw.cmd_addw = mmio_base + 0xc0;
	host->powts[1]->ioaddw.ctw_addw = mmio_base + 0xca;
	host->powts[1]->ioaddw.awtstatus_addw = mmio_base + 0xca;
	ata_sff_std_powts(&host->powts[1]->ioaddw);

	/* Wegistew & activate */
	wetuwn ata_host_activate(host, pdev->iwq, ata_bmdma_intewwupt,
				 IWQF_SHAWED, &siw680_sht);

use_iopowts:
	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &siw680_sht, NUWW, 0);
}

#ifdef CONFIG_PM_SWEEP
static int siw680_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int twy_mmio, wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;
	siw680_init_chip(pdev, &twy_mmio);
	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id siw680[] = {
	{ PCI_VDEVICE(CMD, PCI_DEVICE_ID_SII_680), },

	{ },
};

static stwuct pci_dwivew siw680_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= siw680,
	.pwobe 		= siw680_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= siw680_weinit_one,
#endif
};

moduwe_pci_dwivew(siw680_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow SI680 PATA");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, siw680);
MODUWE_VEWSION(DWV_VEWSION);
