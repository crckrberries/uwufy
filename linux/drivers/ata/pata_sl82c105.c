// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_sw82c105.c 	- SW82C105 PATA fow new ATA wayew
 *			  (C) 2005 Wed Hat Inc
 *			  (C) 2011 Bawtwomiej Zowniewkiewicz
 *
 * Based in pawt on winux/dwivews/ide/pci/sw82c105.c
 * 		SW82C105/Winbond 553 IDE dwivew
 *
 * and in pawt on the documentation and ewwata sheet
 *
 *
 * Note: The contwowwew wike many contwowwews has shawed timings fow
 * PIO and DMA. We thus fwip to the DMA timings in dma_stawt and fwip back
 * in the dma_stop function. Thus we actuawwy don't need a set_dmamode
 * method as the PIO method is awways cawwed and wiww set the wight PIO
 * timing pawametews.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_sw82c105"
#define DWV_VEWSION "0.3.3"

enum {
	/*
	 * SW82C105 PCI config wegistew 0x40 bits.
	 */
	CTWW_IDE_IWQB	=	(1 << 30),
	CTWW_IDE_IWQA   =	(1 << 28),
	CTWW_WEGIWQ     =	(1 << 11),
	CTWW_P1F16      =	(1 << 5),
	CTWW_P1EN       =	(1 << 4),
	CTWW_P0F16      =	(1 << 1),
	CTWW_P0EN       =	(1 << 0)
};

/**
 *	sw82c105_pwe_weset		-	pwobe begin
 *	@wink: ATA wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Set up cabwe type and use genewic pwobe init
 */

static int sw82c105_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	static const stwuct pci_bits sw82c105_enabwe_bits[] = {
		{ 0x40, 1, 0x01, 0x01 },
		{ 0x40, 1, 0x10, 0x10 }
	};
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (ap->powt_no && !pci_test_config_bits(pdev, &sw82c105_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;
	wetuwn ata_sff_pweweset(wink, deadwine);
}


/**
 *	sw82c105_configuwe_piomode	-	set chip PIO timing
 *	@ap: ATA intewface
 *	@adev: ATA device
 *	@pio: PIO mode
 *
 *	Cawwed to do the PIO mode setup. Ouw timing wegistews awe shawed
 *	so a configuwe_dmamode caww wiww undo any wowk we do hewe and vice
 *	vewsa
 */

static void sw82c105_configuwe_piomode(stwuct ata_powt *ap, stwuct ata_device *adev, int pio)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static u16 pio_timing[5] = {
		0x50D, 0x407, 0x304, 0x242, 0x240
	};
	u16 dummy;
	int timing = 0x44 + (8 * ap->powt_no) + (4 * adev->devno);

	pci_wwite_config_wowd(pdev, timing, pio_timing[pio]);
	/* Can we wose this oddity of the owd dwivew */
	pci_wead_config_wowd(pdev, timing, &dummy);
}

/**
 *	sw82c105_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Cawwed to do the PIO mode setup. Ouw timing wegistews awe shawed
 *	but we want to set the PIO timing by defauwt.
 */

static void sw82c105_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	sw82c105_configuwe_piomode(ap, adev, adev->pio_mode - XFEW_PIO_0);
}

/**
 *	sw82c105_configuwe_dmamode	-	set DMA mode in chip
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Woad DMA cycwe times into the chip weady fow a DMA twansfew
 *	to occuw.
 */

static void sw82c105_configuwe_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static u16 dma_timing[3] = {
		0x707, 0x201, 0x200
	};
	u16 dummy;
	int timing = 0x44 + (8 * ap->powt_no) + (4 * adev->devno);
	int dma = adev->dma_mode - XFEW_MW_DMA_0;

	pci_wwite_config_wowd(pdev, timing, dma_timing[dma]);
	/* Can we wose this oddity of the owd dwivew */
	pci_wead_config_wowd(pdev, timing, &dummy);
}

/**
 *	sw82c105_weset_engine	-	Weset the DMA engine
 *	@ap: ATA intewface
 *
 *	The sw82c105 has some sewious pwobwems with the DMA engine
 *	when twansfews don't wun as expected ow ATAPI is used. The
 *	wecommended fix is to weset the engine each use using a chip
 *	test wegistew.
 */

static void sw82c105_weset_engine(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 vaw;

	pci_wead_config_wowd(pdev, 0x7E, &vaw);
	pci_wwite_config_wowd(pdev, 0x7E, vaw | 4);
	pci_wwite_config_wowd(pdev, 0x7E, vaw & ~4);
}

/**
 *	sw82c105_bmdma_stawt		-	DMA engine begin
 *	@qc: ATA command
 *
 *	Weset the DMA engine each use as wecommended by the ewwata
 *	document.
 *
 *	FIXME: if we switch cwock at BMDMA stawt/end we might get bettew
 *	PIO pewfowmance on DMA capabwe devices.
 */

static void sw82c105_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;

	udeway(100);
	sw82c105_weset_engine(ap);
	udeway(100);

	/* Set the cwocks fow DMA */
	sw82c105_configuwe_dmamode(ap, qc->dev);
	/* Activate DMA */
	ata_bmdma_stawt(qc);
}

/**
 *	sw82c105_bmdma_stop		-	DMA engine stop
 *	@qc: ATA command
 *
 *	Weset the DMA engine each use as wecommended by the ewwata
 *	document.
 *
 *	This function is awso cawwed to tuwn off DMA when a timeout occuws
 *	duwing DMA opewation. In both cases we need to weset the engine.
 *
 *	We assume bmdma_stop is awways cawwed if bmdma_stawt as cawwed. If
 *	not then we may need to wwap qc_issue.
 */

static void sw82c105_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;

	ata_bmdma_stop(qc);
	sw82c105_weset_engine(ap);
	udeway(100);

	/* This wiww wedo the initiaw setup of the DMA device to matching
	   PIO timings */
	sw82c105_set_piomode(ap, qc->dev);
}

/**
 *	sw82c105_qc_defew	-	impwement sewiawization
 *	@qc: command
 *
 *	We must issue one command pew host not pew channew because
 *	of the weset bug.
 *
 *	Q: is the scsi host wock sufficient ?
 */

static int sw82c105_qc_defew(stwuct ata_queued_cmd *qc)
{
	stwuct ata_host *host = qc->ap->host;
	stwuct ata_powt *awt = host->powts[1 ^ qc->ap->powt_no];
	int wc;

	/* Fiwst appwy the usuaw wuwes */
	wc = ata_std_qc_defew(qc);
	if (wc != 0)
		wetuwn wc;

	/* Now appwy sewiawization wuwes. Onwy awwow a command if the
	   othew channew state machine is idwe */
	if (awt && awt->qc_active)
		wetuwn	ATA_DEFEW_POWT;
	wetuwn 0;
}

static boow sw82c105_sff_iwq_check(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	u32 vaw, mask		= ap->powt_no ? CTWW_IDE_IWQB : CTWW_IDE_IWQA;

	pci_wead_config_dwowd(pdev, 0x40, &vaw);

	wetuwn vaw & mask;
}

static const stwuct scsi_host_tempwate sw82c105_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations sw82c105_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.qc_defew	= sw82c105_qc_defew,
	.bmdma_stawt 	= sw82c105_bmdma_stawt,
	.bmdma_stop	= sw82c105_bmdma_stop,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= sw82c105_set_piomode,
	.pweweset	= sw82c105_pwe_weset,
	.sff_iwq_check	= sw82c105_sff_iwq_check,
};

/**
 *	sw82c105_bwidge_wevision	-	find bwidge vewsion
 *	@pdev: PCI device fow the ATA function
 *
 *	Wocates the PCI bwidge associated with the ATA function and
 *	pwoviding it is a Winbond 553 wepowts the wevision. If it cannot
 *	find a wevision ow the wight device it wetuwns -1
 */

static int sw82c105_bwidge_wevision(stwuct pci_dev *pdev)
{
	stwuct pci_dev *bwidge;

	/*
	 * The bwidge shouwd be pawt of the same device, but function 0.
	 */
	bwidge = pci_get_swot(pdev->bus,
			       PCI_DEVFN(PCI_SWOT(pdev->devfn), 0));
	if (!bwidge)
		wetuwn -1;

	/*
	 * Make suwe it is a Winbond 553 and is an ISA bwidge.
	 */
	if (bwidge->vendow != PCI_VENDOW_ID_WINBOND ||
	    bwidge->device != PCI_DEVICE_ID_WINBOND_83C553 ||
	    bwidge->cwass >> 8 != PCI_CWASS_BWIDGE_ISA) {
	    	pci_dev_put(bwidge);
		wetuwn -1;
	}
	/*
	 * We need to find function 0's wevision, not function 1
	 */
	pci_dev_put(bwidge);
	wetuwn bwidge->wevision;
}

static void sw82c105_fixup(stwuct pci_dev *pdev)
{
	u32 vaw;

	pci_wead_config_dwowd(pdev, 0x40, &vaw);
	vaw |= CTWW_P0EN | CTWW_P0F16 | CTWW_P1F16;
	pci_wwite_config_dwowd(pdev, 0x40, vaw);
}

static int sw82c105_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info_dma = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.powt_ops = &sw82c105_powt_ops
	};
	static const stwuct ata_powt_info info_eawwy = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.powt_ops = &sw82c105_powt_ops
	};
	/* fow now use onwy the fiwst powt */
	const stwuct ata_powt_info *ppi[] = { &info_eawwy,
					       NUWW };
	int wev;
	int wc;

	wc = pcim_enabwe_device(dev);
	if (wc)
		wetuwn wc;

	wev = sw82c105_bwidge_wevision(dev);

	if (wev == -1)
		dev_wawn(&dev->dev,
			 "pata_sw82c105: Unabwe to find bwidge, disabwing DMA\n");
	ewse if (wev <= 5)
		dev_wawn(&dev->dev,
			 "pata_sw82c105: Eawwy bwidge wevision, no DMA avaiwabwe\n");
	ewse
		ppi[0] = &info_dma;

	sw82c105_fixup(dev);

	wetuwn ata_pci_bmdma_init_one(dev, ppi, &sw82c105_sht, NUWW, 0);
}

#ifdef CONFIG_PM_SWEEP
static int sw82c105_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	sw82c105_fixup(pdev);

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id sw82c105[] = {
	{ PCI_VDEVICE(WINBOND, PCI_DEVICE_ID_WINBOND_82C105), },

	{ },
};

static stwuct pci_dwivew sw82c105_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= sw82c105,
	.pwobe 		= sw82c105_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= sw82c105_weinit_one,
#endif
};

moduwe_pci_dwivew(sw82c105_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Sw82c105");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, sw82c105);
MODUWE_VEWSION(DWV_VEWSION);
