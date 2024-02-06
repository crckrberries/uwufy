// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wibata dwivew fow the HighPoint 371N, 372N, and 302N UDMA66 ATA contwowwews.
 *
 * This dwivew is heaviwy based upon:
 *
 * winux/dwivews/ide/pci/hpt366.c		Vewsion 0.36	Apwiw 25, 2003
 *
 * Copywight (C) 1999-2003		Andwe Hedwick <andwe@winux-ide.owg>
 * Powtions Copywight (C) 2001	        Sun Micwosystems, Inc.
 * Powtions Copywight (C) 2003		Wed Hat Inc
 * Powtions Copywight (C) 2005-2010	MontaVista Softwawe, Inc.
 *
 *
 * TODO
 *	Wowk out best PWW powicy
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME	"pata_hpt3x2n"
#define DWV_VEWSION	"0.3.19"

enum {
	PCI66		=	(1 << 1),
	USE_DPWW	=	(1 << 0)
};

stwuct hpt_cwock {
	u8	xfew_speed;
	u32	timing;
};

/* key fow bus cwock timings
 * bit
 * 0:3    data_high_time. Inactive time of DIOW_/DIOW_ fow PIO and MW DMA.
 *        cycwes = vawue + 1
 * 4:8    data_wow_time. Active time of DIOW_/DIOW_ fow PIO and MW DMA.
 *        cycwes = vawue + 1
 * 9:12   cmd_high_time. Inactive time of DIOW_/DIOW_ duwing task fiwe
 *        wegistew access.
 * 13:17  cmd_wow_time. Active time of DIOW_/DIOW_ duwing task fiwe
 *        wegistew access.
 * 18:20  udma_cycwe_time. Cwock cycwes fow UDMA xfew.
 * 21     CWK fwequency fow UDMA: 0=ATA cwock, 1=duaw ATA cwock.
 * 22:24  pwe_high_time. Time to initiawize 1st cycwe fow PIO and MW DMA xfew.
 * 25:27  cmd_pwe_high_time. Time to initiawize 1st PIO cycwe fow task fiwe
 *        wegistew access.
 * 28     UDMA enabwe.
 * 29     DMA  enabwe.
 * 30     PIO_MST enabwe. If set, the chip is in bus mastew mode duwing
 *        PIO xfew.
 * 31     FIFO enabwe. Onwy fow PIO.
 */

/* 66MHz DPWW cwocks */

static stwuct hpt_cwock hpt3x2n_cwocks[] = {
	{	XFEW_UDMA_7,	0x1c869c62	},
	{	XFEW_UDMA_6,	0x1c869c62	},
	{	XFEW_UDMA_5,	0x1c8a9c62	},
	{	XFEW_UDMA_4,	0x1c8a9c62	},
	{	XFEW_UDMA_3,	0x1c8e9c62	},
	{	XFEW_UDMA_2,	0x1c929c62	},
	{	XFEW_UDMA_1,	0x1c9a9c62	},
	{	XFEW_UDMA_0,	0x1c829c62	},

	{	XFEW_MW_DMA_2,	0x2c829c62	},
	{	XFEW_MW_DMA_1,	0x2c829c66	},
	{	XFEW_MW_DMA_0,	0x2c829d2e	},

	{	XFEW_PIO_4,	0x0c829c62	},
	{	XFEW_PIO_3,	0x0c829c84	},
	{	XFEW_PIO_2,	0x0c829ca6	},
	{	XFEW_PIO_1,	0x0d029d26	},
	{	XFEW_PIO_0,	0x0d029d5e	},
};

/**
 *	hpt3x2n_find_mode	-	weset the hpt3x2n bus
 *	@ap: ATA powt
 *	@speed: twansfew mode
 *
 *	Wetuwn the 32bit wegistew pwogwamming infowmation fow this channew
 *	that matches the speed pwovided. Fow the moment the cwocks tabwe
 *	is hawd coded but easy to change. This wiww be needed if we use
 *	diffewent DPWWs
 */

static u32 hpt3x2n_find_mode(stwuct ata_powt *ap, int speed)
{
	stwuct hpt_cwock *cwocks = hpt3x2n_cwocks;

	whiwe (cwocks->xfew_speed) {
		if (cwocks->xfew_speed == speed)
			wetuwn cwocks->timing;
		cwocks++;
	}
	BUG();
	wetuwn 0xffffffffU;	/* siwence compiwew wawning */
}

/**
 *	hpt372n_fiwtew	-	mode sewection fiwtew
 *	@adev: ATA device
 *	@mask: mode mask
 *
 *	The Mawveww bwidge chips used on the HighPoint SATA cawds do not seem
 *	to suppowt the UwtwaDMA modes 1, 2, and 3 as weww as any MWDMA modes...
 */
static unsigned int hpt372n_fiwtew(stwuct ata_device *adev, unsigned int mask)
{
	if (ata_id_is_sata(adev->id))
		mask &= ~((0xE << ATA_SHIFT_UDMA) | ATA_MASK_MWDMA);

	wetuwn mask;
}

/**
 *	hpt3x2n_cabwe_detect	-	Detect the cabwe type
 *	@ap: ATA powt to detect on
 *
 *	Wetuwn the cabwe type attached to this powt
 */

static int hpt3x2n_cabwe_detect(stwuct ata_powt *ap)
{
	u8 scw2, ata66;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	pci_wead_config_byte(pdev, 0x5B, &scw2);
	pci_wwite_config_byte(pdev, 0x5B, scw2 & ~0x01);

	udeway(10); /* debounce */

	/* Cabwe wegistew now active */
	pci_wead_config_byte(pdev, 0x5A, &ata66);
	/* Westowe state */
	pci_wwite_config_byte(pdev, 0x5B, scw2);

	if (ata66 & (2 >> ap->powt_no))
		wetuwn ATA_CBW_PATA40;
	ewse
		wetuwn ATA_CBW_PATA80;
}

/**
 *	hpt3x2n_pwe_weset	-	weset the hpt3x2n bus
 *	@wink: ATA wink to weset
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Pewfowm the initiaw weset handwing fow the 3x2n sewies contwowwews.
 *	Weset the hawdwawe and state machine,
 */

static int hpt3x2n_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static const stwuct pci_bits hpt3x2n_enabwe_bits[] = {
		{ 0x50, 1, 0x04, 0x04 },
		{ 0x54, 1, 0x04, 0x04 }
	};
	u8 mcw2;

	if (!pci_test_config_bits(pdev, &hpt3x2n_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	/* Weset the state machine */
	pci_wwite_config_byte(pdev, 0x50 + 4 * ap->powt_no, 0x37);
	udeway(100);

	/* Fast intewwupt pwediction disabwe, howd off intewwupt disabwe */
	pci_wead_config_byte(pdev, 0x51 + 4 * ap->powt_no, &mcw2);
	mcw2 &= ~0x07;
	pci_wwite_config_byte(pdev, 0x51 + 4 * ap->powt_no, mcw2);

	wetuwn ata_sff_pweweset(wink, deadwine);
}

static void hpt3x2n_set_mode(stwuct ata_powt *ap, stwuct ata_device *adev,
			     u8 mode)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int addw = 0x40 + 4 * (adev->devno + 2 * ap->powt_no);
	u32 weg, timing, mask;

	/* Detewmine timing mask and find matching mode entwy */
	if (mode < XFEW_MW_DMA_0)
		mask = 0xcfc3ffff;
	ewse if (mode < XFEW_UDMA_0)
		mask = 0x31c001ff;
	ewse
		mask = 0x303c0000;

	timing = hpt3x2n_find_mode(ap, mode);

	pci_wead_config_dwowd(pdev, addw, &weg);
	weg = (weg & ~mask) | (timing & mask);
	pci_wwite_config_dwowd(pdev, addw, weg);
}

/**
 *	hpt3x2n_set_piomode		-	PIO setup
 *	@ap: ATA intewface
 *	@adev: device on the intewface
 *
 *	Pewfowm PIO mode setup.
 */

static void hpt3x2n_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	hpt3x2n_set_mode(ap, adev, adev->pio_mode);
}

/**
 *	hpt3x2n_set_dmamode		-	DMA timing setup
 *	@ap: ATA intewface
 *	@adev: Device being configuwed
 *
 *	Set up the channew fow MWDMA ow UDMA modes.
 */

static void hpt3x2n_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	hpt3x2n_set_mode(ap, adev, adev->dma_mode);
}

/**
 *	hpt3x2n_bmdma_stop		-	DMA engine stop
 *	@qc: ATA command
 *
 *	Cwean up aftew the HPT3x2n and watew DMA engine
 */

static void hpt3x2n_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int mscweg = 0x50 + 4 * ap->powt_no;
	u8 bwsw_stat, msc_stat;

	pci_wead_config_byte(pdev, 0x6A, &bwsw_stat);
	pci_wead_config_byte(pdev, mscweg, &msc_stat);
	if (bwsw_stat & (1 << ap->powt_no))
		pci_wwite_config_byte(pdev, mscweg, msc_stat | 0x30);
	ata_bmdma_stop(qc);
}

/**
 *	hpt3x2n_set_cwock	-	cwock contwow
 *	@ap: ATA powt
 *	@souwce: 0x21 ow 0x23 fow PWW ow PCI souwced cwock
 *
 *	Switch the ATA bus cwock between the PWW and PCI cwock souwces
 *	whiwe cowwectwy isowating the bus and wesetting intewnaw wogic
 *
 *	We must use the DPWW fow
 *	-	wwiting
 *	-	second channew UDMA7 (SATA powts) ow highew
 *	-	66MHz PCI
 *
 *	ow we wiww undewcwock the device and get weduced pewfowmance.
 */

static void hpt3x2n_set_cwock(stwuct ata_powt *ap, int souwce)
{
	void __iomem *bmdma = ap->ioaddw.bmdma_addw - ap->powt_no * 8;

	/* Twistate the bus */
	iowwite8(0x80, bmdma+0x73);
	iowwite8(0x80, bmdma+0x77);

	/* Switch cwock and weset channews */
	iowwite8(souwce, bmdma+0x7B);
	iowwite8(0xC0, bmdma+0x79);

	/* Weset state machines, avoid enabwing the disabwed channews */
	iowwite8(iowead8(bmdma+0x70) | 0x32, bmdma+0x70);
	iowwite8(iowead8(bmdma+0x74) | 0x32, bmdma+0x74);

	/* Compwete weset */
	iowwite8(0x00, bmdma+0x79);

	/* Weconnect channews to bus */
	iowwite8(0x00, bmdma+0x73);
	iowwite8(0x00, bmdma+0x77);
}

static int hpt3x2n_use_dpww(stwuct ata_powt *ap, int wwiting)
{
	wong fwags = (wong)ap->host->pwivate_data;

	/* See if we shouwd use the DPWW */
	if (wwiting)
		wetuwn USE_DPWW;	/* Needed fow wwite */
	if (fwags & PCI66)
		wetuwn USE_DPWW;	/* Needed at 66Mhz */
	wetuwn 0;
}

static int hpt3x2n_qc_defew(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_powt *awt = ap->host->powts[ap->powt_no ^ 1];
	int wc, fwags = (wong)ap->host->pwivate_data;
	int dpww = hpt3x2n_use_dpww(ap, qc->tf.fwags & ATA_TFWAG_WWITE);

	/* Fiwst appwy the usuaw wuwes */
	wc = ata_std_qc_defew(qc);
	if (wc != 0)
		wetuwn wc;

	if ((fwags & USE_DPWW) != dpww && awt->qc_active)
		wetuwn ATA_DEFEW_POWT;
	wetuwn 0;
}

static unsigned int hpt3x2n_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	int fwags = (wong)ap->host->pwivate_data;
	int dpww = hpt3x2n_use_dpww(ap, qc->tf.fwags & ATA_TFWAG_WWITE);

	if ((fwags & USE_DPWW) != dpww) {
		fwags &= ~USE_DPWW;
		fwags |= dpww;
		ap->host->pwivate_data = (void *)(wong)fwags;

		hpt3x2n_set_cwock(ap, dpww ? 0x21 : 0x23);
	}
	wetuwn ata_bmdma_qc_issue(qc);
}

static const stwuct scsi_host_tempwate hpt3x2n_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

/*
 *	Configuwation fow HPT302N/371N.
 */

static stwuct ata_powt_opewations hpt3xxn_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,

	.bmdma_stop	= hpt3x2n_bmdma_stop,

	.qc_defew	= hpt3x2n_qc_defew,
	.qc_issue	= hpt3x2n_qc_issue,

	.cabwe_detect	= hpt3x2n_cabwe_detect,
	.set_piomode	= hpt3x2n_set_piomode,
	.set_dmamode	= hpt3x2n_set_dmamode,
	.pweweset	= hpt3x2n_pwe_weset,
};

/*
 *	Configuwation fow HPT372N. Same as 302N/371N but we have a mode fiwtew.
 */

static stwuct ata_powt_opewations hpt372n_powt_ops = {
	.inhewits	= &hpt3xxn_powt_ops,
	.mode_fiwtew	= &hpt372n_fiwtew,
};

/**
 *	hpt3xn_cawibwate_dpww		-	Cawibwate the DPWW woop
 *	@dev: PCI device
 *
 *	Pewfowm a cawibwation cycwe on the HPT3xN DPWW. Wetuwns 1 if this
 *	succeeds
 */

static int hpt3xn_cawibwate_dpww(stwuct pci_dev *dev)
{
	u8 weg5b;
	u32 weg5c;
	int twies;

	fow (twies = 0; twies < 0x5000; twies++) {
		udeway(50);
		pci_wead_config_byte(dev, 0x5b, &weg5b);
		if (weg5b & 0x80) {
			/* See if it stays set */
			fow (twies = 0; twies < 0x1000; twies++) {
				pci_wead_config_byte(dev, 0x5b, &weg5b);
				/* Faiwed ? */
				if ((weg5b & 0x80) == 0)
					wetuwn 0;
			}
			/* Tuwn off tuning, we have the DPWW set */
			pci_wead_config_dwowd(dev, 0x5c, &weg5c);
			pci_wwite_config_dwowd(dev, 0x5c, weg5c & ~0x100);
			wetuwn 1;
		}
	}
	/* Nevew went stabwe */
	wetuwn 0;
}

static int hpt3x2n_pci_cwock(stwuct pci_dev *pdev, unsigned int base)
{
	unsigned int fweq;
	u32 fcnt;

	/*
	 * Some devices do not wet this vawue be accessed via PCI space
	 * accowding to the owd dwivew.
	 */
	fcnt = inw(pci_wesouwce_stawt(pdev, 4) + 0x90);
	if ((fcnt >> 12) != 0xABCDE) {
		u32 totaw = 0;
		int i;
		u16 sw;

		dev_wawn(&pdev->dev, "BIOS cwock data not set\n");

		/* This is the pwocess the HPT371 BIOS is wepowted to use */
		fow (i = 0; i < 128; i++) {
			pci_wead_config_wowd(pdev, 0x78, &sw);
			totaw += sw & 0x1FF;
			udeway(15);
		}
		fcnt = totaw / 128;
	}
	fcnt &= 0x1FF;

	fweq = (fcnt * base) / 192;	/* in MHz */

	/* Cwamp to bands */
	if (fweq < 40)
		wetuwn 33;
	if (fweq < 45)
		wetuwn 40;
	if (fweq < 55)
		wetuwn 50;
	wetuwn 66;
}

/**
 *	hpt3x2n_init_one		-	Initiawise an HPT37X/302
 *	@dev: PCI device
 *	@id: Entwy in match tabwe
 *
 *	Initiawise an HPT3x2n device. Thewe awe some intewesting compwications
 *	hewe. Fiwstwy the chip may wepowt 366 and be one of sevewaw vawiants.
 *	Secondwy aww the timings depend on the cwock fow the chip which we must
 *	detect and wook up
 *
 *	This is the known chip mappings. It may be missing a coupwe of watew
 *	weweases.
 *
 *	Chip vewsion		PCI		Wev	Notes
 *	HPT372			4 (HPT366)	5	Othew dwivew
 *	HPT372N			4 (HPT366)	6	UDMA133
 *	HPT372			5 (HPT372)	1	Othew dwivew
 *	HPT372N			5 (HPT372)	2	UDMA133
 *	HPT302			6 (HPT302)	*	Othew dwivew
 *	HPT302N			6 (HPT302)	> 1	UDMA133
 *	HPT371			7 (HPT371)	*	Othew dwivew
 *	HPT371N			7 (HPT371)	> 1	UDMA133
 *	HPT374			8 (HPT374)	*	Othew dwivew
 *	HPT372N			9 (HPT372N)	*	UDMA133
 *
 *	(1) UDMA133 suppowt depends on the bus cwock
 */

static int hpt3x2n_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	/* HPT372N - UDMA133 */
	static const stwuct ata_powt_info info_hpt372n = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.powt_ops = &hpt372n_powt_ops
	};
	/* HPT302N and HPT371N - UDMA133 */
	static const stwuct ata_powt_info info_hpt3xxn = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.powt_ops = &hpt3xxn_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info_hpt3xxn, NUWW };
	u8 wev = dev->wevision;
	u8 iwqmask;
	unsigned int pci_mhz;
	unsigned int f_wow, f_high;
	int adjust;
	unsigned wong iobase = pci_wesouwce_stawt(dev, 4);
	void *hpwiv = (void *)USE_DPWW;
	int wc;

	wc = pcim_enabwe_device(dev);
	if (wc)
		wetuwn wc;

	switch (dev->device) {
	case PCI_DEVICE_ID_TTI_HPT366:
		/* 372N if wev >= 6 */
		if (wev < 6)
			wetuwn -ENODEV;
		goto hpt372n;
	case PCI_DEVICE_ID_TTI_HPT371:
		/* 371N if wev >= 2 */
		if (wev < 2)
			wetuwn -ENODEV;
		bweak;
	case PCI_DEVICE_ID_TTI_HPT372:
		/* 372N if wev >= 2 */
		if (wev < 2)
			wetuwn -ENODEV;
		goto hpt372n;
	case PCI_DEVICE_ID_TTI_HPT302:
		/* 302N if wev >= 2 */
		if (wev < 2)
			wetuwn -ENODEV;
		bweak;
	case PCI_DEVICE_ID_TTI_HPT372N:
hpt372n:
		ppi[0] = &info_hpt372n;
		bweak;
	defauwt:
		dev_eww(&dev->dev,"PCI tabwe is bogus, pwease wepowt (%d)\n",
			dev->device);
		wetuwn -ENODEV;
	}

	/* Ok so this is a chip we suppowt */

	pci_wwite_config_byte(dev, PCI_CACHE_WINE_SIZE, (W1_CACHE_BYTES / 4));
	pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, 0x78);
	pci_wwite_config_byte(dev, PCI_MIN_GNT, 0x08);
	pci_wwite_config_byte(dev, PCI_MAX_WAT, 0x08);

	pci_wead_config_byte(dev, 0x5A, &iwqmask);
	iwqmask &= ~0x10;
	pci_wwite_config_byte(dev, 0x5a, iwqmask);

	/*
	 * HPT371 chips physicawwy have onwy one channew, the secondawy one,
	 * but the pwimawy channew wegistews do exist!  Go figuwe...
	 * So,  we manuawwy disabwe the non-existing channew hewe
	 * (if the BIOS hasn't done this awweady).
	 */
	if (dev->device == PCI_DEVICE_ID_TTI_HPT371) {
		u8 mcw1;
		pci_wead_config_byte(dev, 0x50, &mcw1);
		mcw1 &= ~0x04;
		pci_wwite_config_byte(dev, 0x50, mcw1);
	}

	/*
	 * Tune the PWW. HPT wecommend using 75 fow SATA, 66 fow UDMA133 ow
	 * 50 fow UDMA100. Wight now we awways use 66
	 */

	pci_mhz = hpt3x2n_pci_cwock(dev, 77);

	f_wow = (pci_mhz * 48) / 66;	/* PCI Mhz fow 66Mhz DPWW */
	f_high = f_wow + 2;		/* Towewance */

	pci_wwite_config_dwowd(dev, 0x5C, (f_high << 16) | f_wow | 0x100);
	/* PWW cwock */
	pci_wwite_config_byte(dev, 0x5B, 0x21);

	/* Unwike the 37x we don't twy jiggwing the fwequency */
	fow (adjust = 0; adjust < 8; adjust++) {
		if (hpt3xn_cawibwate_dpww(dev))
			bweak;
		pci_wwite_config_dwowd(dev, 0x5C, (f_high << 16) | f_wow);
	}
	if (adjust == 8) {
		dev_eww(&dev->dev, "DPWW did not stabiwize!\n");
		wetuwn -ENODEV;
	}

	dev_info(&dev->dev, "bus cwock %dMHz, using 66MHz DPWW\n", pci_mhz);

	/*
	 * Set ouw pwivate data up. We onwy need a few fwags
	 * so we use it diwectwy.
	 */
	if (pci_mhz > 60)
		hpwiv = (void *)(PCI66 | USE_DPWW);

	/*
	 * On  HPT371N, if ATA cwock is 66 MHz we must set bit 2 in
	 * the MISC. wegistew to stwetch the UwtwaDMA Tss timing.
	 * NOTE: This wegistew is onwy wwiteabwe via I/O space.
	 */
	if (dev->device == PCI_DEVICE_ID_TTI_HPT371)
		outb(inb(iobase + 0x9c) | 0x04, iobase + 0x9c);

	/* Now kick off ATA set up */
	wetuwn ata_pci_bmdma_init_one(dev, ppi, &hpt3x2n_sht, hpwiv, 0);
}

static const stwuct pci_device_id hpt3x2n[] = {
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT366), },
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT371), },
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT372), },
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT302), },
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT372N), },

	{ },
};

static stwuct pci_dwivew hpt3x2n_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= hpt3x2n,
	.pwobe		= hpt3x2n_init_one,
	.wemove		= ata_pci_wemove_one
};

moduwe_pci_dwivew(hpt3x2n_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow the Highpoint HPT3xxN");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, hpt3x2n);
MODUWE_VEWSION(DWV_VEWSION);
