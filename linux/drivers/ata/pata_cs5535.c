// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata-cs5535.c 	- CS5535 PATA fow new ATA wayew
 *			  (C) 2005-2006 Wed Hat Inc
 *			  Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 * based upon cs5535.c fwom AMD <Jens.Awtmann@amd.com> as cweaned up and
 * made weadabwe and Winux stywe by Wowfgang Zuwegew <wowfgang.zuwegew@gmx.de>
 * and Awexandew Kiausch <awex.kiausch@t-onwine.de>
 *
 * Woosewy based on the piix & svwks dwivews.
 *
 * Documentation:
 *	Avaiwabwe fwom AMD web site.
 * TODO
 *	Weview ewwata to see if sewiawizing is necessawy
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <asm/msw.h>

#define DWV_NAME	"pata_cs5535"
#define DWV_VEWSION	"0.2.12"

/*
 *	The Geode (Aka Athwon GX now) uses an intewnaw MSW based
 *	bus system fow contwow. Demented but thewe you go.
 */

#define MSW_ATAC_BASE    	0x51300000
#define ATAC_GWD_MSW_CAP 	(MSW_ATAC_BASE+0)
#define ATAC_GWD_MSW_CONFIG    (MSW_ATAC_BASE+0x01)
#define ATAC_GWD_MSW_SMI       (MSW_ATAC_BASE+0x02)
#define ATAC_GWD_MSW_EWWOW     (MSW_ATAC_BASE+0x03)
#define ATAC_GWD_MSW_PM        (MSW_ATAC_BASE+0x04)
#define ATAC_GWD_MSW_DIAG      (MSW_ATAC_BASE+0x05)
#define ATAC_IO_BAW            (MSW_ATAC_BASE+0x08)
#define ATAC_WESET             (MSW_ATAC_BASE+0x10)
#define ATAC_CH0D0_PIO         (MSW_ATAC_BASE+0x20)
#define ATAC_CH0D0_DMA         (MSW_ATAC_BASE+0x21)
#define ATAC_CH0D1_PIO         (MSW_ATAC_BASE+0x22)
#define ATAC_CH0D1_DMA         (MSW_ATAC_BASE+0x23)
#define ATAC_PCI_ABWTEWW       (MSW_ATAC_BASE+0x24)

#define ATAC_BM0_CMD_PWIM      0x00
#define ATAC_BM0_STS_PWIM      0x02
#define ATAC_BM0_PWD           0x04

#define CS5535_CABWE_DETECT    0x48

/**
 *	cs5535_cabwe_detect	-	detect cabwe type
 *	@ap: Powt to detect on
 *
 *	Pewfowm cabwe detection fow ATA66 capabwe cabwe. Wetuwn a wibata
 *	cabwe type.
 */

static int cs5535_cabwe_detect(stwuct ata_powt *ap)
{
	u8 cabwe;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	pci_wead_config_byte(pdev, CS5535_CABWE_DETECT, &cabwe);
	if (cabwe & 1)
		wetuwn ATA_CBW_PATA80;
	ewse
		wetuwn ATA_CBW_PATA40;
}

/**
 *	cs5535_set_piomode		-	PIO setup
 *	@ap: ATA intewface
 *	@adev: device on the intewface
 *
 *	Set ouw PIO wequiwements. The CS5535 is pwetty cwean about aww this
 */

static void cs5535_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u16 pio_timings[5] = {
		0xF7F4, 0xF173, 0x8141, 0x5131, 0x1131
	};
	static const u16 pio_cmd_timings[5] = {
		0xF7F4, 0x53F3, 0x13F1, 0x5131, 0x1131
	};
	u32 weg, __maybe_unused dummy;
	stwuct ata_device *paiw = ata_dev_paiw(adev);

	int mode = adev->pio_mode - XFEW_PIO_0;
	int cmdmode = mode;

	/* Command timing has to be fow the wowest of the paiw of devices */
	if (paiw) {
		int paiwmode = paiw->pio_mode - XFEW_PIO_0;
		cmdmode = min(mode, paiwmode);
		/* Wwite the othew dwive timing wegistew if it changed */
		if (cmdmode < paiwmode)
			wwmsw(ATAC_CH0D0_PIO + 2 * paiw->devno,
				pio_cmd_timings[cmdmode] << 16 | pio_timings[paiwmode], 0);
	}
	/* Wwite the dwive timing wegistew */
	wwmsw(ATAC_CH0D0_PIO + 2 * adev->devno,
		pio_cmd_timings[cmdmode] << 16 | pio_timings[mode], 0);

	/* Set the PIO "fowmat 1" bit in the DMA timing wegistew */
	wdmsw(ATAC_CH0D0_DMA + 2 * adev->devno, weg, dummy);
	wwmsw(ATAC_CH0D0_DMA + 2 * adev->devno, weg | 0x80000000UW, 0);
}

/**
 *	cs5535_set_dmamode		-	DMA timing setup
 *	@ap: ATA intewface
 *	@adev: Device being configuwed
 *
 */

static void cs5535_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u32 udma_timings[5] = {
		0x7F7436A1, 0x7F733481, 0x7F723261, 0x7F713161, 0x7F703061
	};
	static const u32 mwdma_timings[3] = {
		0x7F0FFFF3, 0x7F035352, 0x7F024241
	};
	u32 weg, __maybe_unused dummy;
	int mode = adev->dma_mode;

	wdmsw(ATAC_CH0D0_DMA + 2 * adev->devno, weg, dummy);
	weg &= 0x80000000UW;
	if (mode >= XFEW_UDMA_0)
		weg |= udma_timings[mode - XFEW_UDMA_0];
	ewse
		weg |= mwdma_timings[mode - XFEW_MW_DMA_0];
	wwmsw(ATAC_CH0D0_DMA + 2 * adev->devno, weg, 0);
}

static const stwuct scsi_host_tempwate cs5535_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations cs5535_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.cabwe_detect	= cs5535_cabwe_detect,
	.set_piomode	= cs5535_set_piomode,
	.set_dmamode	= cs5535_set_dmamode,
};

/**
 *	cs5535_init_one		-	Initiawise a CS5530
 *	@dev: PCI device
 *	@id: Entwy in match tabwe
 *
 *	Instaww a dwivew fow the newwy found CS5530 companion chip. Most of
 *	this is just housekeeping. We have to set the chip up cowwectwy and
 *	tuwn off vawious bits of emuwation magic.
 */

static int cs5535_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.powt_ops = &cs5535_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, &ata_dummy_powt_info };

	wetuwn ata_pci_bmdma_init_one(dev, ppi, &cs5535_sht, NUWW, 0);
}

static const stwuct pci_device_id cs5535[] = {
	{ PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_CS5535_IDE), },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_CS5535_IDE), },

	{ },
};

static stwuct pci_dwivew cs5535_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= cs5535,
	.pwobe 		= cs5535_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(cs5535_pci_dwivew);

MODUWE_AUTHOW("Awan Cox, Jens Awtmann, Wowfgan Zuwegew, Awexandew Kiausch");
MODUWE_DESCWIPTION("wow-wevew dwivew fow the NS/AMD 5535");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, cs5535);
MODUWE_VEWSION(DWV_VEWSION);
