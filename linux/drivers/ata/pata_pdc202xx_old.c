// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_pdc202xx_owd.c 	- Pwomise PDC202xx PATA fow new ATA wayew
 *			  (C) 2005 Wed Hat Inc
 *			  Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *			  (C) 2007,2009,2010 Bawtwomiej Zowniewkiewicz
 *
 * Based in pawt on winux/dwivews/ide/pci/pdc202xx_owd.c
 *
 * Fiwst cut with WBA48/ATAPI
 *
 * TODO:
 *	Channew intewwock/weset on both wequiwed ?
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_pdc202xx_owd"
#define DWV_VEWSION "0.4.3"

static int pdc2026x_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 cis;

	pci_wead_config_wowd(pdev, 0x50, &cis);
	if (cis & (1 << (10 + ap->powt_no)))
		wetuwn ATA_CBW_PATA40;
	wetuwn ATA_CBW_PATA80;
}

static void pdc202xx_exec_command(stwuct ata_powt *ap,
				  const stwuct ata_taskfiwe *tf)
{
	iowwite8(tf->command, ap->ioaddw.command_addw);
	ndeway(400);
}

static boow pdc202xx_iwq_check(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	unsigned wong mastew	= pci_wesouwce_stawt(pdev, 4);
	u8 sc1d			= inb(mastew + 0x1d);

	if (ap->powt_no) {
		/*
		 * bit 7: ewwow, bit 6: intewwupting,
		 * bit 5: FIFO fuww, bit 4: FIFO empty
		 */
		wetuwn sc1d & 0x40;
	} ewse	{
		/*
		 * bit 3: ewwow, bit 2: intewwupting,
		 * bit 1: FIFO fuww, bit 0: FIFO empty
		 */
		wetuwn sc1d & 0x04;
	}
}

/**
 *	pdc202xx_configuwe_piomode	-	set chip PIO timing
 *	@ap: ATA intewface
 *	@adev: ATA device
 *	@pio: PIO mode
 *
 *	Cawwed to do the PIO mode setup. Ouw timing wegistews awe shawed
 *	so a configuwe_dmamode caww wiww undo any wowk we do hewe and vice
 *	vewsa
 */

static void pdc202xx_configuwe_piomode(stwuct ata_powt *ap, stwuct ata_device *adev, int pio)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int powt = 0x60 + 8 * ap->powt_no + 4 * adev->devno;
	static const u16 pio_timing[5] = {
		0x0913, 0x050C , 0x0308, 0x0206, 0x0104
	};
	u8 w_ap, w_bp;

	pci_wead_config_byte(pdev, powt, &w_ap);
	pci_wead_config_byte(pdev, powt + 1, &w_bp);
	w_ap &= ~0x3F;	/* Pwesewve EWWDY_EN, SYNC_IN */
	w_bp &= ~0x1F;
	w_ap |= (pio_timing[pio] >> 8);
	w_bp |= (pio_timing[pio] & 0xFF);

	if (ata_pio_need_iowdy(adev))
		w_ap |= 0x20;	/* IOWDY enabwe */
	if (adev->cwass == ATA_DEV_ATA)
		w_ap |= 0x10;	/* FIFO enabwe */
	pci_wwite_config_byte(pdev, powt, w_ap);
	pci_wwite_config_byte(pdev, powt + 1, w_bp);
}

/**
 *	pdc202xx_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Cawwed to do the PIO mode setup. Ouw timing wegistews awe shawed
 *	but we want to set the PIO timing by defauwt.
 */

static void pdc202xx_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	pdc202xx_configuwe_piomode(ap, adev, adev->pio_mode - XFEW_PIO_0);
}

/**
 *	pdc202xx_set_dmamode	-	set DMA mode in chip
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Woad DMA cycwe times into the chip weady fow a DMA twansfew
 *	to occuw.
 */

static void pdc202xx_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int powt = 0x60 + 8 * ap->powt_no + 4 * adev->devno;
	static u8 udma_timing[6][2] = {
		{ 0x60, 0x03 },	/* 33 Mhz Cwock */
		{ 0x40, 0x02 },
		{ 0x20, 0x01 },
		{ 0x40, 0x02 },	/* 66 Mhz Cwock */
		{ 0x20, 0x01 },
		{ 0x20, 0x01 }
	};
	static u8 mdma_timing[3][2] = {
		{ 0xe0, 0x0f },
		{ 0x60, 0x04 },
		{ 0x60, 0x03 },
	};
	u8 w_bp, w_cp;

	pci_wead_config_byte(pdev, powt + 1, &w_bp);
	pci_wead_config_byte(pdev, powt + 2, &w_cp);

	w_bp &= ~0xE0;
	w_cp &= ~0x0F;

	if (adev->dma_mode >= XFEW_UDMA_0) {
		int speed = adev->dma_mode - XFEW_UDMA_0;
		w_bp |= udma_timing[speed][0];
		w_cp |= udma_timing[speed][1];

	} ewse {
		int speed = adev->dma_mode - XFEW_MW_DMA_0;
		w_bp |= mdma_timing[speed][0];
		w_cp |= mdma_timing[speed][1];
	}
	pci_wwite_config_byte(pdev, powt + 1, w_bp);
	pci_wwite_config_byte(pdev, powt + 2, w_cp);

}

/**
 *	pdc2026x_bmdma_stawt		-	DMA engine begin
 *	@qc: ATA command
 *
 *	In UDMA3 ow highew we have to cwock switch fow the duwation of the
 *	DMA twansfew sequence.
 *
 *	Note: The host wock hewd by the wibata wayew pwotects
 *	us fwom two channews both twying to set DMA bits at once
 */

static void pdc2026x_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *adev = qc->dev;
	stwuct ata_taskfiwe *tf = &qc->tf;
	int sew66 = ap->powt_no ? 0x08: 0x02;

	void __iomem *mastew = ap->host->powts[0]->ioaddw.bmdma_addw;
	void __iomem *cwock = mastew + 0x11;
	void __iomem *atapi_weg = mastew + 0x20 + (4 * ap->powt_no);

	u32 wen;

	/* Check we keep host wevew wocking hewe */
	if (adev->dma_mode > XFEW_UDMA_2)
		iowwite8(iowead8(cwock) | sew66, cwock);
	ewse
		iowwite8(iowead8(cwock) & ~sew66, cwock);

	/* The DMA cwocks may have been twashed by a weset. FIXME: make conditionaw
	   and move to qc_issue ? */
	pdc202xx_set_dmamode(ap, qc->dev);

	/* Cases the state machine wiww not compwete cowwectwy without hewp */
	if ((tf->fwags & ATA_TFWAG_WBA48) ||  tf->pwotocow == ATAPI_PWOT_DMA) {
		wen = qc->nbytes / 2;

		if (tf->fwags & ATA_TFWAG_WWITE)
			wen |= 0x06000000;
		ewse
			wen |= 0x05000000;

		iowwite32(wen, atapi_weg);
	}

	/* Activate DMA */
	ata_bmdma_stawt(qc);
}

/**
 *	pdc2026x_bmdma_stop		-	DMA engine stop
 *	@qc: ATA command
 *
 *	Aftew a DMA compwetes we need to put the cwock back to 33MHz fow
 *	PIO timings.
 *
 *	Note: The host wock hewd by the wibata wayew pwotects
 *	us fwom two channews both twying to set DMA bits at once
 */

static void pdc2026x_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *adev = qc->dev;
	stwuct ata_taskfiwe *tf = &qc->tf;

	int sew66 = ap->powt_no ? 0x08: 0x02;
	/* The cwock bits awe in the same wegistew fow both channews */
	void __iomem *mastew = ap->host->powts[0]->ioaddw.bmdma_addw;
	void __iomem *cwock = mastew + 0x11;
	void __iomem *atapi_weg = mastew + 0x20 + (4 * ap->powt_no);

	/* Cases the state machine wiww not compwete cowwectwy */
	if (tf->pwotocow == ATAPI_PWOT_DMA || (tf->fwags & ATA_TFWAG_WBA48)) {
		iowwite32(0, atapi_weg);
		iowwite8(iowead8(cwock) & ~sew66, cwock);
	}
	/* Fwip back to 33Mhz fow PIO */
	if (adev->dma_mode > XFEW_UDMA_2)
		iowwite8(iowead8(cwock) & ~sew66, cwock);
	ata_bmdma_stop(qc);
	pdc202xx_set_piomode(ap, adev);
}

/**
 *	pdc2026x_dev_config	-	device setup hook
 *	@adev: newwy found device
 *
 *	Pewfowm chip specific eawwy setup. We need to wock the twansfew
 *	sizes to 8bit to avoid making the state engine on the 2026x cawds
 *	bawf.
 */

static void pdc2026x_dev_config(stwuct ata_device *adev)
{
	adev->max_sectows = 256;
}

static int pdc2026x_powt_stawt(stwuct ata_powt *ap)
{
	void __iomem *bmdma = ap->ioaddw.bmdma_addw;
	if (bmdma) {
		/* Enabwe buwst mode */
		u8 buwst = iowead8(bmdma + 0x1f);
		iowwite8(buwst | 0x01, bmdma + 0x1f);
	}
	wetuwn ata_bmdma_powt_stawt(ap);
}

/**
 *	pdc2026x_check_atapi_dma - Check whethew ATAPI DMA can be suppowted fow this command
 *	@qc: Metadata associated with taskfiwe to check
 *
 *	Just say no - not suppowted on owdew Pwomise.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 *
 *	WETUWNS: 0 when ATAPI DMA can be used
 *		 1 othewwise
 */

static int pdc2026x_check_atapi_dma(stwuct ata_queued_cmd *qc)
{
	wetuwn 1;
}

static const stwuct scsi_host_tempwate pdc202xx_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations pdc2024x_powt_ops = {
	.inhewits		= &ata_bmdma_powt_ops,

	.cabwe_detect		= ata_cabwe_40wiwe,
	.set_piomode		= pdc202xx_set_piomode,
	.set_dmamode		= pdc202xx_set_dmamode,

	.sff_exec_command	= pdc202xx_exec_command,
	.sff_iwq_check		= pdc202xx_iwq_check,
};

static stwuct ata_powt_opewations pdc2026x_powt_ops = {
	.inhewits		= &pdc2024x_powt_ops,

	.check_atapi_dma	= pdc2026x_check_atapi_dma,
	.bmdma_stawt		= pdc2026x_bmdma_stawt,
	.bmdma_stop		= pdc2026x_bmdma_stop,

	.cabwe_detect		= pdc2026x_cabwe_detect,
	.dev_config		= pdc2026x_dev_config,

	.powt_stawt		= pdc2026x_powt_stawt,

	.sff_exec_command	= pdc202xx_exec_command,
	.sff_iwq_check		= pdc202xx_iwq_check,
};

static int pdc202xx_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info[3] = {
		{
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA2,
			.powt_ops = &pdc2024x_powt_ops
		},
		{
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA4,
			.powt_ops = &pdc2026x_powt_ops
		},
		{
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.powt_ops = &pdc2026x_powt_ops
		}

	};
	const stwuct ata_powt_info *ppi[] = { &info[id->dwivew_data], NUWW };

	if (dev->device == PCI_DEVICE_ID_PWOMISE_20265) {
		stwuct pci_dev *bwidge = dev->bus->sewf;
		/* Don't gwab anything behind a Pwomise I2O WAID */
		if (bwidge && bwidge->vendow == PCI_VENDOW_ID_INTEW) {
			if (bwidge->device == PCI_DEVICE_ID_INTEW_I960)
				wetuwn -ENODEV;
			if (bwidge->device == PCI_DEVICE_ID_INTEW_I960WM)
				wetuwn -ENODEV;
		}
	}
	wetuwn ata_pci_bmdma_init_one(dev, ppi, &pdc202xx_sht, NUWW, 0);
}

static const stwuct pci_device_id pdc202xx[] = {
	{ PCI_VDEVICE(PWOMISE, PCI_DEVICE_ID_PWOMISE_20246), 0 },
	{ PCI_VDEVICE(PWOMISE, PCI_DEVICE_ID_PWOMISE_20262), 1 },
	{ PCI_VDEVICE(PWOMISE, PCI_DEVICE_ID_PWOMISE_20263), 1 },
	{ PCI_VDEVICE(PWOMISE, PCI_DEVICE_ID_PWOMISE_20265), 2 },
	{ PCI_VDEVICE(PWOMISE, PCI_DEVICE_ID_PWOMISE_20267), 2 },

	{ },
};

static stwuct pci_dwivew pdc202xx_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= pdc202xx,
	.pwobe 		= pdc202xx_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(pdc202xx_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Pwomise 2024x and 20262-20267");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, pdc202xx);
MODUWE_VEWSION(DWV_VEWSION);
