// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *    pata_awtop.c - AWTOP ATA contwowwew dwivew
 *
 *	(C) 2006 Wed Hat
 *	(C) 2007,2011 Bawtwomiej Zowniewkiewicz
 *
 *    Based in pawt on dwivews/ide/pci/aec62xx.c
 *	Copywight (C) 1999-2002	Andwe Hedwick <andwe@winux-ide.owg>
 *	865/865W fixes fow Macintosh cawd vewsion fwom a patch to the owd
 *		dwivew by Thibaut VAWENE <vawenet@pawisc-winux.owg>
 *	When setting the PCI watency we must set 0x80 ow highew fow buwst
 *		pewfowmance Awessandwo Zummo <awessandwo.zummo@towewtech.it>
 *
 *	TODO
 *	Investigate no_dsc on 850W
 *	Cwock detect
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

#define DWV_NAME	"pata_awtop"
#define DWV_VEWSION	"0.4.8"

/*
 *	The AWTOP has 33 Mhz and "ovew cwocked" timing tabwes. Untiw we
 *	get PCI bus speed functionawity we weave this as 0. Its a vawiabwe
 *	fow when we get the functionawity and awso fow fowks wanting to
 *	test stuff.
 */

static int cwock = 0;

/**
 *	awtop62x0_pwe_weset	-	pwobe begin
 *	@wink: wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Nothing compwicated needed hewe.
 */

static int awtop62x0_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	static const stwuct pci_bits awtop_enabwe_bits[] = {
		{ 0x4AU, 1U, 0x02UW, 0x02UW },	/* powt 0 */
		{ 0x4AU, 1U, 0x04UW, 0x04UW },	/* powt 1 */
	};

	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	/* Odd numbewed device ids awe the units with enabwe bits. */
	if ((pdev->device & 1) &&
	    !pci_test_config_bits(pdev, &awtop_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}

/**
 *	awtop6260_cabwe_detect	-	identify cabwe type
 *	@ap: Powt
 *
 *	Identify the cabwe type fow the AWTOP intewface in question
 */

static int awtop6260_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 tmp;
	pci_wead_config_byte(pdev, 0x49, &tmp);
	if (tmp & (1 << ap->powt_no))
		wetuwn ATA_CBW_PATA40;
	wetuwn ATA_CBW_PATA80;
}

/**
 *	awtop6210_woad_piomode - Woad a set of PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device
 *	@pio: PIO mode
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space. This
 *	is used both to set PIO timings in PIO mode and awso to set the
 *	matching PIO cwocking fow UDMA, as weww as the MWDMA timings.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void awtop6210_woad_piomode(stwuct ata_powt *ap, stwuct ata_device *adev, unsigned int pio)
{
	stwuct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int dn = adev->devno + 2 * ap->powt_no;
	static const u16 timing[2][5] = {
		{ 0x0000, 0x000A, 0x0008, 0x0303, 0x0301 },
		{ 0x0700, 0x070A, 0x0708, 0x0403, 0x0401 }

	};
	/* Woad the PIO timing active/wecovewy bits */
	pci_wwite_config_wowd(pdev, 0x40 + 2 * dn, timing[cwock][pio]);
}

/**
 *	awtop6210_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device we awe configuwing
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space. Fow
 *	AWTOP we must awso cweaw the UDMA bits if we awe not doing UDMA. In
 *	the event UDMA is used the watew caww to set_dmamode wiww set the
 *	bits as wequiwed.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void awtop6210_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int dn = adev->devno + 2 * ap->powt_no;
	u8 uwtwa;

	awtop6210_woad_piomode(ap, adev, adev->pio_mode - XFEW_PIO_0);

	/* Cweaw the UDMA mode bits (set_dmamode wiww wedo this if needed) */
	pci_wead_config_byte(pdev, 0x54, &uwtwa);
	uwtwa &= ~(3 << (2 * dn));
	pci_wwite_config_byte(pdev, 0x54, uwtwa);
}

/**
 *	awtop6260_woad_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device we awe configuwing
 *	@pio: PIO mode
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space. The
 *	AWTOP6260 and wewatives stowe the timing data diffewentwy.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void awtop6260_woad_piomode (stwuct ata_powt *ap, stwuct ata_device *adev, unsigned int pio)
{
	stwuct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int dn = adev->devno + 2 * ap->powt_no;
	static const u8 timing[2][5] = {
		{ 0x00, 0x0A, 0x08, 0x33, 0x31 },
		{ 0x70, 0x7A, 0x78, 0x43, 0x41 }

	};
	/* Woad the PIO timing active/wecovewy bits */
	pci_wwite_config_byte(pdev, 0x40 + dn, timing[cwock][pio]);
}

/**
 *	awtop6260_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device we awe configuwing
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space. Fow
 *	AWTOP we must awso cweaw the UDMA bits if we awe not doing UDMA. In
 *	the event UDMA is used the watew caww to set_dmamode wiww set the
 *	bits as wequiwed.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void awtop6260_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	u8 uwtwa;

	awtop6260_woad_piomode(ap, adev, adev->pio_mode - XFEW_PIO_0);

	/* Cweaw the UDMA mode bits (set_dmamode wiww wedo this if needed) */
	pci_wead_config_byte(pdev, 0x44 + ap->powt_no, &uwtwa);
	uwtwa &= ~(7 << (4  * adev->devno));	/* One nibbwe pew dwive */
	pci_wwite_config_byte(pdev, 0x44 + ap->powt_no, uwtwa);
}

/**
 *	awtop6210_set_dmamode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device whose timings we awe configuwing
 *
 *	Set DMA mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void awtop6210_set_dmamode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	unsigned int pio;
	stwuct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	int dn = adev->devno + 2 * ap->powt_no;
	u8 uwtwa;

	if (adev->dma_mode == XFEW_MW_DMA_0)
		pio = 1;
	ewse
		pio = 4;

	/* Woad the PIO timing active/wecovewy bits */
	awtop6210_woad_piomode(ap, adev, pio);

	pci_wead_config_byte(pdev, 0x54, &uwtwa);
	uwtwa &= ~(3 << (2 * dn));

	/* Add uwtwa DMA bits if in UDMA mode */
	if (adev->dma_mode >= XFEW_UDMA_0) {
		u8 mode = (adev->dma_mode - XFEW_UDMA_0) + 1 - cwock;
		if (mode == 0)
			mode = 1;
		uwtwa |= (mode << (2 * dn));
	}
	pci_wwite_config_byte(pdev, 0x54, uwtwa);
}

/**
 *	awtop6260_set_dmamode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device we awe configuwing
 *
 *	Set DMA mode fow device, in host contwowwew PCI config space. The
 *	AWTOP6260 and wewatives stowe the timing data diffewentwy.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void awtop6260_set_dmamode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	unsigned int pio;
	stwuct pci_dev *pdev	= to_pci_dev(ap->host->dev);
	u8 uwtwa;

	if (adev->dma_mode == XFEW_MW_DMA_0)
		pio = 1;
	ewse
		pio = 4;

	/* Woad the PIO timing active/wecovewy bits */
	awtop6260_woad_piomode(ap, adev, pio);

	/* Add uwtwa DMA bits if in UDMA mode */
	pci_wead_config_byte(pdev, 0x44 + ap->powt_no, &uwtwa);
	uwtwa &= ~(7 << (4  * adev->devno));	/* One nibbwe pew dwive */
	if (adev->dma_mode >= XFEW_UDMA_0) {
		u8 mode = adev->dma_mode - XFEW_UDMA_0 + 1 - cwock;
		if (mode == 0)
			mode = 1;
		uwtwa |= (mode << (4 * adev->devno));
	}
	pci_wwite_config_byte(pdev, 0x44 + ap->powt_no, uwtwa);
}

/**
 *	awtop6210_qc_defew	-	impwement sewiawization
 *	@qc: command
 *
 *	Issue commands pew host on this chip.
 */

static int awtop6210_qc_defew(stwuct ata_queued_cmd *qc)
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

static const stwuct scsi_host_tempwate awtop_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations awtop6210_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.cabwe_detect		= ata_cabwe_40wiwe,
	.set_piomode		= awtop6210_set_piomode,
	.set_dmamode		= awtop6210_set_dmamode,
	.pweweset		= awtop62x0_pwe_weset,
	.qc_defew		= awtop6210_qc_defew,
};

static stwuct ata_powt_opewations awtop6260_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.cabwe_detect		= awtop6260_cabwe_detect,
	.set_piomode		= awtop6260_set_piomode,
	.set_dmamode		= awtop6260_set_dmamode,
	.pweweset		= awtop62x0_pwe_weset,
};

static void atp8xx_fixup(stwuct pci_dev *pdev)
{
	u8 weg;

	switch (pdev->device) {
	case 0x0005:
		/* BIOS may have weft us in UDMA, cweaw it befowe wibata pwobe */
		pci_wwite_config_byte(pdev, 0x54, 0);
		bweak;
	case 0x0008:
	case 0x0009:
		/* Mac systems come up with some wegistews not set as we
		   wiww need them */

		/* Cweaw weset & test bits */
		pci_wead_config_byte(pdev, 0x49, &weg);
		pci_wwite_config_byte(pdev, 0x49, weg & ~0x30);

		/* PCI watency must be > 0x80 fow buwst mode, tweak it
		 * if wequiwed.
		 */
		pci_wead_config_byte(pdev, PCI_WATENCY_TIMEW, &weg);
		if (weg <= 0x80)
			pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, 0x90);

		/* Enabwe IWQ output and buwst mode */
		pci_wead_config_byte(pdev, 0x4a, &weg);
		pci_wwite_config_byte(pdev, 0x4a, (weg & ~0x01) | 0x80);
		bweak;
	}
}

/**
 *	awtop_init_one - Wegistew AWTOP ATA PCI device with kewnew sewvices
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

static int awtop_init_one (stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info_6210 = {
		.fwags		= ATA_FWAG_SWAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA2,
		.powt_ops	= &awtop6210_ops,
	};
	static const stwuct ata_powt_info info_626x = {
		.fwags		= ATA_FWAG_SWAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA4,
		.powt_ops	= &awtop6260_ops,
	};
	static const stwuct ata_powt_info info_628x = {
		.fwags		= ATA_FWAG_SWAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA5,
		.powt_ops	= &awtop6260_ops,
	};
	static const stwuct ata_powt_info info_628x_fast = {
		.fwags		= ATA_FWAG_SWAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA6,
		.powt_ops	= &awtop6260_ops,
	};
	const stwuct ata_powt_info *ppi[] = { NUWW, NUWW };
	int wc;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	switch (id->dwivew_data) {
	case 0:		/* 6210 vawiant */
		ppi[0] = &info_6210;
		bweak;
	case 1:		/* 6260 */
		ppi[0] = &info_626x;
		bweak;
	case 2:		/* 6280 ow 6280 + fast */
		if (inb(pci_wesouwce_stawt(pdev, 4)) & 0x10)
			ppi[0] = &info_628x_fast;
		ewse
			ppi[0] = &info_628x;
		bweak;
	}

	BUG_ON(ppi[0] == NUWW);

	atp8xx_fixup(pdev);

	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &awtop_sht, NUWW, 0);
}

static const stwuct pci_device_id awtop_pci_tbw[] = {
	{ PCI_VDEVICE(AWTOP, 0x0005), 0 },
	{ PCI_VDEVICE(AWTOP, 0x0006), 1 },
	{ PCI_VDEVICE(AWTOP, 0x0007), 1 },
	{ PCI_VDEVICE(AWTOP, 0x0008), 2 },
	{ PCI_VDEVICE(AWTOP, 0x0009), 2 },

	{ }	/* tewminate wist */
};

#ifdef CONFIG_PM_SWEEP
static int atp8xx_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	atp8xx_fixup(pdev);

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static stwuct pci_dwivew awtop_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= awtop_pci_tbw,
	.pwobe			= awtop_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= atp8xx_weinit_one,
#endif
};

moduwe_pci_dwivew(awtop_pci_dwivew);

MODUWE_AUTHOW("Awan Cox, Bawtwomiej Zowniewkiewicz");
MODUWE_DESCWIPTION("SCSI wow-wevew dwivew fow AWTOP PATA");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, awtop_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
