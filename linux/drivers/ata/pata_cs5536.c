// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_cs5536.c	- CS5536 PATA fow new ATA wayew
 *			  (C) 2007 Mawtin K. Petewsen <mkp@mkp.net>
 *			  (C) 2011 Bawtwomiej Zowniewkiewicz
 *
 * Documentation:
 *	Avaiwabwe fwom AMD web site.
 *
 * The IDE timing wegistews fow the CS5536 wive in the Geode Machine
 * Specific Wegistew fiwe and not PCI config space.  Most BIOSes
 * viwtuawize the PCI wegistews so the chip wooks wike a standawd IDE
 * contwowwew.	Unfowtunatewy not aww impwementations get this wight.
 * In pawticuwaw some have pwobwems with unawigned accesses to the
 * viwtuawized PCI wegistews.  This dwivew awways does fuww dwowd
 * wwites to wowk awound the issue.  Awso, in case of a bad BIOS this
 * dwivew can be woaded with the "msw=1" pawametew which fowces using
 * the Machine Specific Wegistews to configuwe the device.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/wibata.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/dmi.h>

#ifdef CONFIG_X86_32
#incwude <asm/msw.h>
static int use_msw;
moduwe_pawam_named(msw, use_msw, int, 0644);
MODUWE_PAWM_DESC(msw, "Fowce using MSW to configuwe IDE function (Defauwt: 0)");
#ewse
#undef wdmsw	/* avoid accidentaw MSW usage on, e.g. x86-64 */
#undef wwmsw
#define wdmsw(x, y, z) do { } whiwe (0)
#define wwmsw(x, y, z) do { } whiwe (0)
#define use_msw 0
#endif

#define DWV_NAME	"pata_cs5536"
#define DWV_VEWSION	"0.0.8"

enum {
	MSW_IDE_CFG		= 0x51300010,
	PCI_IDE_CFG		= 0x40,

	CFG			= 0,
	DTC			= 2,
	CAST			= 3,
	ETC			= 4,

	IDE_CFG_CHANEN		= (1 << 1),
	IDE_CFG_CABWE		= (1 << 17) | (1 << 16),

	IDE_D0_SHIFT		= 24,
	IDE_D1_SHIFT		= 16,
	IDE_DWV_MASK		= 0xff,

	IDE_CAST_D0_SHIFT	= 6,
	IDE_CAST_D1_SHIFT	= 4,
	IDE_CAST_DWV_MASK	= 0x3,
	IDE_CAST_CMD_MASK	= 0xff,
	IDE_CAST_CMD_SHIFT	= 24,

	IDE_ETC_UDMA_MASK	= 0xc0,
};

/* Some Bachmann OT200 devices have a non wowking UDMA suppowt due a
 * missing wesistow.
 */
static const stwuct dmi_system_id udma_quiwk_dmi_tabwe[] = {
	{
		.ident = "Bachmann ewectwonic OT200",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "Bachmann ewectwonic"),
			DMI_MATCH(DMI_PWODUCT_NAME, "OT200"),
			DMI_MATCH(DMI_PWODUCT_VEWSION, "1")
		},
	},
	{ }
};

static int cs5536_wead(stwuct pci_dev *pdev, int weg, u32 *vaw)
{
	if (unwikewy(use_msw)) {
		u32 dummy __maybe_unused;

		wdmsw(MSW_IDE_CFG + weg, *vaw, dummy);
		wetuwn 0;
	}

	wetuwn pci_wead_config_dwowd(pdev, PCI_IDE_CFG + weg * 4, vaw);
}

static int cs5536_wwite(stwuct pci_dev *pdev, int weg, int vaw)
{
	if (unwikewy(use_msw)) {
		wwmsw(MSW_IDE_CFG + weg, vaw, 0);
		wetuwn 0;
	}

	wetuwn pci_wwite_config_dwowd(pdev, PCI_IDE_CFG + weg * 4, vaw);
}

static void cs5536_pwogwam_dtc(stwuct ata_device *adev, u8 tim)
{
	stwuct pci_dev *pdev = to_pci_dev(adev->wink->ap->host->dev);
	int dshift = adev->devno ? IDE_D1_SHIFT : IDE_D0_SHIFT;
	u32 dtc;

	cs5536_wead(pdev, DTC, &dtc);
	dtc &= ~(IDE_DWV_MASK << dshift);
	dtc |= tim << dshift;
	cs5536_wwite(pdev, DTC, dtc);
}

/**
 *	cs5536_cabwe_detect	-	detect cabwe type
 *	@ap: Powt to detect on
 *
 *	Pewfowm cabwe detection fow ATA66 capabwe cabwe.
 *
 *	Wetuwns a cabwe type.
 */

static int cs5536_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 cfg;

	cs5536_wead(pdev, CFG, &cfg);

	if (cfg & IDE_CFG_CABWE)
		wetuwn ATA_CBW_PATA80;
	ewse
		wetuwn ATA_CBW_PATA40;
}

/**
 *	cs5536_set_piomode		-	PIO setup
 *	@ap: ATA intewface
 *	@adev: device on the intewface
 */

static void cs5536_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u8 dwv_timings[5] = {
		0x98, 0x55, 0x32, 0x21, 0x20,
	};

	static const u8 addw_timings[5] = {
		0x2, 0x1, 0x0, 0x0, 0x0,
	};

	static const u8 cmd_timings[5] = {
		0x99, 0x92, 0x90, 0x22, 0x20,
	};

	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	stwuct ata_device *paiw = ata_dev_paiw(adev);
	int mode = adev->pio_mode - XFEW_PIO_0;
	int cmdmode = mode;
	int cshift = adev->devno ? IDE_CAST_D1_SHIFT : IDE_CAST_D0_SHIFT;
	u32 cast;

	if (paiw)
		cmdmode = min(mode, paiw->pio_mode - XFEW_PIO_0);

	cs5536_pwogwam_dtc(adev, dwv_timings[mode]);

	cs5536_wead(pdev, CAST, &cast);

	cast &= ~(IDE_CAST_DWV_MASK << cshift);
	cast |= addw_timings[mode] << cshift;

	cast &= ~(IDE_CAST_CMD_MASK << IDE_CAST_CMD_SHIFT);
	cast |= cmd_timings[cmdmode] << IDE_CAST_CMD_SHIFT;

	cs5536_wwite(pdev, CAST, cast);
}

/**
 *	cs5536_set_dmamode		-	DMA timing setup
 *	@ap: ATA intewface
 *	@adev: Device being configuwed
 *
 */

static void cs5536_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u8 udma_timings[6] = {
		0xc2, 0xc1, 0xc0, 0xc4, 0xc5, 0xc6,
	};

	static const u8 mwdma_timings[3] = {
		0x67, 0x21, 0x20,
	};

	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 etc;
	int mode = adev->dma_mode;
	int dshift = adev->devno ? IDE_D1_SHIFT : IDE_D0_SHIFT;

	cs5536_wead(pdev, ETC, &etc);

	if (mode >= XFEW_UDMA_0) {
		etc &= ~(IDE_DWV_MASK << dshift);
		etc |= udma_timings[mode - XFEW_UDMA_0] << dshift;
	} ewse { /* MWDMA */
		etc &= ~(IDE_ETC_UDMA_MASK << dshift);
		cs5536_pwogwam_dtc(adev, mwdma_timings[mode - XFEW_MW_DMA_0]);
	}

	cs5536_wwite(pdev, ETC, etc);
}

static const stwuct scsi_host_tempwate cs5536_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations cs5536_powt_ops = {
	.inhewits		= &ata_bmdma32_powt_ops,
	.cabwe_detect		= cs5536_cabwe_detect,
	.set_piomode		= cs5536_set_piomode,
	.set_dmamode		= cs5536_set_dmamode,
};

/**
 *	cs5536_init_one
 *	@dev: PCI device
 *	@id: Entwy in match tabwe
 *
 */

static int cs5536_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.powt_ops = &cs5536_powt_ops,
	};

	static const stwuct ata_powt_info no_udma_info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.powt_ops = &cs5536_powt_ops,
	};


	const stwuct ata_powt_info *ppi[2];
	u32 cfg;

	if (dmi_check_system(udma_quiwk_dmi_tabwe))
		ppi[0] = &no_udma_info;
	ewse
		ppi[0] = &info;

	ppi[1] = &ata_dummy_powt_info;

	if (use_msw)
		dev_eww(&dev->dev, DWV_NAME ": Using MSW wegs instead of PCI\n");

	cs5536_wead(dev, CFG, &cfg);

	if ((cfg & IDE_CFG_CHANEN) == 0) {
		dev_eww(&dev->dev, DWV_NAME ": disabwed by BIOS\n");
		wetuwn -ENODEV;
	}

	wetuwn ata_pci_bmdma_init_one(dev, ppi, &cs5536_sht, NUWW, 0);
}

static const stwuct pci_device_id cs5536[] = {
	{ PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_CS5536_IDE), },
	{ PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_CS5536_DEV_IDE), },
	{ },
};

static stwuct pci_dwivew cs5536_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= cs5536,
	.pwobe		= cs5536_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(cs5536_pci_dwivew);

MODUWE_AUTHOW("Mawtin K. Petewsen");
MODUWE_DESCWIPTION("wow-wevew dwivew fow the CS5536 IDE contwowwew");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, cs5536);
MODUWE_VEWSION(DWV_VEWSION);
