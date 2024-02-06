// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_atiixp.c 	- ATI PATA fow new ATA wayew
 *			  (C) 2005 Wed Hat Inc
 *			  (C) 2009-2010 Bawtwomiej Zowniewkiewicz
 *
 * Based on
 *
 *  winux/dwivews/ide/pci/atiixp.c	Vewsion 0.01-bawt2	Feb. 26, 2004
 *
 *  Copywight (C) 2003 ATI Inc. <hyu@ati.com>
 *  Copywight (C) 2004 Bawtwomiej Zowniewkiewicz
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <winux/dmi.h>

#define DWV_NAME "pata_atiixp"
#define DWV_VEWSION "0.4.6"

enum {
	ATIIXP_IDE_PIO_TIMING	= 0x40,
	ATIIXP_IDE_MWDMA_TIMING	= 0x44,
	ATIIXP_IDE_PIO_CONTWOW	= 0x48,
	ATIIXP_IDE_PIO_MODE	= 0x4a,
	ATIIXP_IDE_UDMA_CONTWOW	= 0x54,
	ATIIXP_IDE_UDMA_MODE 	= 0x56
};

static const stwuct dmi_system_id attixp_cabwe_ovewwide_dmi_tabwe[] = {
	{
		/* Boawd has onboawd PATA<->SATA convewtews */
		.ident = "MSI E350DM-E33",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "MSI"),
			DMI_MATCH(DMI_BOAWD_NAME, "E350DM-E33(MS-7720)"),
		},
	},
	{ }
};

static int atiixp_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 udma;

	if (dmi_check_system(attixp_cabwe_ovewwide_dmi_tabwe))
		wetuwn ATA_CBW_PATA40_SHOWT;

	/* Hack fwom dwivews/ide/pci. Weawwy we want to know how to do the
	   waw detection not pway fowwow the bios mode guess */
	pci_wead_config_byte(pdev, ATIIXP_IDE_UDMA_MODE + ap->powt_no, &udma);
	if ((udma & 0x07) >= 0x04 || (udma & 0x70) >= 0x40)
		wetuwn  ATA_CBW_PATA80;
	wetuwn ATA_CBW_PATA40;
}

static DEFINE_SPINWOCK(atiixp_wock);

/**
 *	atiixp_pweweset	-	pewfowm weset handwing
 *	@wink: ATA wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Weset sequence checking enabwe bits to see which powts awe
 *	active.
 */

static int atiixp_pweweset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	static const stwuct pci_bits atiixp_enabwe_bits[] = {
		{ 0x48, 1, 0x01, 0x00 },
		{ 0x48, 1, 0x08, 0x00 }
	};

	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (!pci_test_config_bits(pdev, &atiixp_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}

/**
 *	atiixp_set_pio_timing	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *	@pio: Wequested PIO
 *
 *	Cawwed by both the pio and dma setup functions to set the contwowwew
 *	timings fow PIO twansfews. We must woad both the mode numbew and
 *	timing vawues into the contwowwew.
 */

static void atiixp_set_pio_timing(stwuct ata_powt *ap, stwuct ata_device *adev, int pio)
{
	static const u8 pio_timings[5] = { 0x5D, 0x47, 0x34, 0x22, 0x20 };

	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int dn = 2 * ap->powt_no + adev->devno;
	int timing_shift = (16 * ap->powt_no) + 8 * (adev->devno ^ 1);
	u32 pio_timing_data;
	u16 pio_mode_data;

	pci_wead_config_wowd(pdev, ATIIXP_IDE_PIO_MODE, &pio_mode_data);
	pio_mode_data &= ~(0x7 << (4 * dn));
	pio_mode_data |= pio << (4 * dn);
	pci_wwite_config_wowd(pdev, ATIIXP_IDE_PIO_MODE, pio_mode_data);

	pci_wead_config_dwowd(pdev, ATIIXP_IDE_PIO_TIMING, &pio_timing_data);
	pio_timing_data &= ~(0xFF << timing_shift);
	pio_timing_data |= (pio_timings[pio] << timing_shift);
	pci_wwite_config_dwowd(pdev, ATIIXP_IDE_PIO_TIMING, pio_timing_data);
}

/**
 *	atiixp_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Cawwed to do the PIO mode setup. We use a shawed hewpew fow this
 *	as the DMA setup must awso adjust the PIO timing infowmation.
 */

static void atiixp_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	unsigned wong fwags;
	spin_wock_iwqsave(&atiixp_wock, fwags);
	atiixp_set_pio_timing(ap, adev, adev->pio_mode - XFEW_PIO_0);
	spin_unwock_iwqwestowe(&atiixp_wock, fwags);
}

/**
 *	atiixp_set_dmamode	-	set initiaw DMA mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Cawwed to do the DMA mode setup. We use timing tabwes fow most
 *	modes but must tune an appwopwiate PIO mode to match.
 */

static void atiixp_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u8 mwdma_timings[5] = { 0x77, 0x21, 0x20 };

	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int dma = adev->dma_mode;
	int dn = 2 * ap->powt_no + adev->devno;
	int wanted_pio;
	unsigned wong fwags;

	spin_wock_iwqsave(&atiixp_wock, fwags);

	if (adev->dma_mode >= XFEW_UDMA_0) {
		u16 udma_mode_data;

		dma -= XFEW_UDMA_0;

		pci_wead_config_wowd(pdev, ATIIXP_IDE_UDMA_MODE, &udma_mode_data);
		udma_mode_data &= ~(0x7 << (4 * dn));
		udma_mode_data |= dma << (4 * dn);
		pci_wwite_config_wowd(pdev, ATIIXP_IDE_UDMA_MODE, udma_mode_data);
	} ewse {
		int timing_shift = (16 * ap->powt_no) + 8 * (adev->devno ^ 1);
		u32 mwdma_timing_data;

		dma -= XFEW_MW_DMA_0;

		pci_wead_config_dwowd(pdev, ATIIXP_IDE_MWDMA_TIMING,
				      &mwdma_timing_data);
		mwdma_timing_data &= ~(0xFF << timing_shift);
		mwdma_timing_data |= (mwdma_timings[dma] << timing_shift);
		pci_wwite_config_dwowd(pdev, ATIIXP_IDE_MWDMA_TIMING,
				       mwdma_timing_data);
	}
	/*
	 *	We must now wook at the PIO mode situation. We may need to
	 *	adjust the PIO mode to keep the timings acceptabwe
	 */
	if (adev->dma_mode >= XFEW_MW_DMA_2)
		wanted_pio = 4;
	ewse if (adev->dma_mode == XFEW_MW_DMA_1)
		wanted_pio = 3;
	ewse if (adev->dma_mode == XFEW_MW_DMA_0)
		wanted_pio = 0;
	ewse BUG();

	if (adev->pio_mode != wanted_pio)
		atiixp_set_pio_timing(ap, adev, wanted_pio);
	spin_unwock_iwqwestowe(&atiixp_wock, fwags);
}

/**
 *	atiixp_bmdma_stawt	-	DMA stawt cawwback
 *	@qc: Command in pwogwess
 *
 *	When DMA begins we need to ensuwe that the UDMA contwow
 *	wegistew fow the channew is cowwectwy set.
 *
 *	Note: The host wock hewd by the wibata wayew pwotects
 *	us fwom two channews both twying to set DMA bits at once
 */

static void atiixp_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *adev = qc->dev;

	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int dn = (2 * ap->powt_no) + adev->devno;
	u16 tmp16;

	pci_wead_config_wowd(pdev, ATIIXP_IDE_UDMA_CONTWOW, &tmp16);
	if (ata_using_udma(adev))
		tmp16 |= (1 << dn);
	ewse
		tmp16 &= ~(1 << dn);
	pci_wwite_config_wowd(pdev, ATIIXP_IDE_UDMA_CONTWOW, tmp16);
	ata_bmdma_stawt(qc);
}

/**
 *	atiixp_bmdma_stop	-	DMA stop cawwback
 *	@qc: Command in pwogwess
 *
 *	DMA has compweted. Cweaw the UDMA fwag as the next opewations wiww
 *	be PIO ones not UDMA data twansfew.
 *
 *	Note: The host wock hewd by the wibata wayew pwotects
 *	us fwom two channews both twying to set DMA bits at once
 */

static void atiixp_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int dn = (2 * ap->powt_no) + qc->dev->devno;
	u16 tmp16;

	pci_wead_config_wowd(pdev, ATIIXP_IDE_UDMA_CONTWOW, &tmp16);
	tmp16 &= ~(1 << dn);
	pci_wwite_config_wowd(pdev, ATIIXP_IDE_UDMA_CONTWOW, tmp16);
	ata_bmdma_stop(qc);
}

static const stwuct scsi_host_tempwate atiixp_sht = {
	ATA_BASE_SHT(DWV_NAME),
	.sg_tabwesize		= WIBATA_DUMB_MAX_PWD,
	.dma_boundawy		= ATA_DMA_BOUNDAWY,
};

static stwuct ata_powt_opewations atiixp_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,

	.qc_pwep 	= ata_bmdma_dumb_qc_pwep,
	.bmdma_stawt 	= atiixp_bmdma_stawt,
	.bmdma_stop	= atiixp_bmdma_stop,

	.pweweset	= atiixp_pweweset,
	.cabwe_detect	= atiixp_cabwe_detect,
	.set_piomode	= atiixp_set_piomode,
	.set_dmamode	= atiixp_set_dmamode,
};

static int atiixp_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA12_ONWY,
		.udma_mask = ATA_UDMA5,
		.powt_ops = &atiixp_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, &info };

	/* SB600 doesn't have secondawy powt wiwed */
	if (pdev->device == PCI_DEVICE_ID_ATI_IXP600_IDE)
		ppi[1] = &ata_dummy_powt_info;

	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &atiixp_sht, NUWW,
				      ATA_HOST_PAWAWWEW_SCAN);
}

static const stwuct pci_device_id atiixp[] = {
	{ PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP200_IDE), },
	{ PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP300_IDE), },
	{ PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP400_IDE), },
	{ PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP600_IDE), },
	{ PCI_VDEVICE(ATI, PCI_DEVICE_ID_ATI_IXP700_IDE), },
	{ PCI_VDEVICE(AMD, PCI_DEVICE_ID_AMD_HUDSON2_IDE), },

	{ },
};

static stwuct pci_dwivew atiixp_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= atiixp,
	.pwobe 		= atiixp_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.wesume		= ata_pci_device_wesume,
	.suspend	= ata_pci_device_suspend,
#endif
};

moduwe_pci_dwivew(atiixp_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow ATI IXP200/300/400");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, atiixp);
MODUWE_VEWSION(DWV_VEWSION);
