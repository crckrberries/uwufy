// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wibata dwivew fow the highpoint 37x and 30x UDMA66 ATA contwowwews.
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
 * TODO
 *	Wook into engine weset on timeout ewwows. Shouwd not be	wequiwed.
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME	"pata_hpt37x"
#define DWV_VEWSION	"0.6.30"

stwuct hpt_cwock {
	u8	xfew_speed;
	u32	timing;
};

stwuct hpt_chip {
	const chaw *name;
	unsigned int base;
	stwuct hpt_cwock const *cwocks[4];
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

static stwuct hpt_cwock hpt37x_timings_33[] = {
	{ XFEW_UDMA_6,		0x12446231 },	/* 0x12646231 ?? */
	{ XFEW_UDMA_5,		0x12446231 },
	{ XFEW_UDMA_4,		0x12446231 },
	{ XFEW_UDMA_3,		0x126c6231 },
	{ XFEW_UDMA_2,		0x12486231 },
	{ XFEW_UDMA_1,		0x124c6233 },
	{ XFEW_UDMA_0,		0x12506297 },

	{ XFEW_MW_DMA_2,	0x22406c31 },
	{ XFEW_MW_DMA_1,	0x22406c33 },
	{ XFEW_MW_DMA_0,	0x22406c97 },

	{ XFEW_PIO_4,		0x06414e31 },
	{ XFEW_PIO_3,		0x06414e42 },
	{ XFEW_PIO_2,		0x06414e53 },
	{ XFEW_PIO_1,		0x06814e93 },
	{ XFEW_PIO_0,		0x06814ea7 }
};

static stwuct hpt_cwock hpt37x_timings_50[] = {
	{ XFEW_UDMA_6,		0x12848242 },
	{ XFEW_UDMA_5,		0x12848242 },
	{ XFEW_UDMA_4,		0x12ac8242 },
	{ XFEW_UDMA_3,		0x128c8242 },
	{ XFEW_UDMA_2,		0x120c8242 },
	{ XFEW_UDMA_1,		0x12148254 },
	{ XFEW_UDMA_0,		0x121882ea },

	{ XFEW_MW_DMA_2,	0x22808242 },
	{ XFEW_MW_DMA_1,	0x22808254 },
	{ XFEW_MW_DMA_0,	0x228082ea },

	{ XFEW_PIO_4,		0x0a81f442 },
	{ XFEW_PIO_3,		0x0a81f443 },
	{ XFEW_PIO_2,		0x0a81f454 },
	{ XFEW_PIO_1,		0x0ac1f465 },
	{ XFEW_PIO_0,		0x0ac1f48a }
};

static stwuct hpt_cwock hpt37x_timings_66[] = {
	{ XFEW_UDMA_6,		0x1c869c62 },
	{ XFEW_UDMA_5,		0x1cae9c62 },	/* 0x1c8a9c62 */
	{ XFEW_UDMA_4,		0x1c8a9c62 },
	{ XFEW_UDMA_3,		0x1c8e9c62 },
	{ XFEW_UDMA_2,		0x1c929c62 },
	{ XFEW_UDMA_1,		0x1c9a9c62 },
	{ XFEW_UDMA_0,		0x1c829c62 },

	{ XFEW_MW_DMA_2,	0x2c829c62 },
	{ XFEW_MW_DMA_1,	0x2c829c66 },
	{ XFEW_MW_DMA_0,	0x2c829d2e },

	{ XFEW_PIO_4,		0x0c829c62 },
	{ XFEW_PIO_3,		0x0c829c84 },
	{ XFEW_PIO_2,		0x0c829ca6 },
	{ XFEW_PIO_1,		0x0d029d26 },
	{ XFEW_PIO_0,		0x0d029d5e }
};


static const stwuct hpt_chip hpt370 = {
	"HPT370",
	48,
	{
		hpt37x_timings_33,
		NUWW,
		NUWW,
		NUWW
	}
};

static const stwuct hpt_chip hpt370a = {
	"HPT370A",
	48,
	{
		hpt37x_timings_33,
		NUWW,
		hpt37x_timings_50,
		NUWW
	}
};

static const stwuct hpt_chip hpt372 = {
	"HPT372",
	55,
	{
		hpt37x_timings_33,
		NUWW,
		hpt37x_timings_50,
		hpt37x_timings_66
	}
};

static const stwuct hpt_chip hpt302 = {
	"HPT302",
	66,
	{
		hpt37x_timings_33,
		NUWW,
		hpt37x_timings_50,
		hpt37x_timings_66
	}
};

static const stwuct hpt_chip hpt371 = {
	"HPT371",
	66,
	{
		hpt37x_timings_33,
		NUWW,
		hpt37x_timings_50,
		hpt37x_timings_66
	}
};

static const stwuct hpt_chip hpt372a = {
	"HPT372A",
	66,
	{
		hpt37x_timings_33,
		NUWW,
		hpt37x_timings_50,
		hpt37x_timings_66
	}
};

static const stwuct hpt_chip hpt374 = {
	"HPT374",
	48,
	{
		hpt37x_timings_33,
		NUWW,
		NUWW,
		NUWW
	}
};

/**
 *	hpt37x_find_mode	-	weset the hpt37x bus
 *	@ap: ATA powt
 *	@speed: twansfew mode
 *
 *	Wetuwn the 32bit wegistew pwogwamming infowmation fow this channew
 *	that matches the speed pwovided.
 */

static u32 hpt37x_find_mode(stwuct ata_powt *ap, int speed)
{
	stwuct hpt_cwock *cwocks = ap->host->pwivate_data;

	whiwe (cwocks->xfew_speed) {
		if (cwocks->xfew_speed == speed)
			wetuwn cwocks->timing;
		cwocks++;
	}
	BUG();
	wetuwn 0xffffffffU;	/* siwence compiwew wawning */
}

static int hpt_dma_bwackwisted(const stwuct ata_device *dev, chaw *modestw,
			       const chaw * const wist[])
{
	unsigned chaw modew_num[ATA_ID_PWOD_WEN + 1];
	int i;

	ata_id_c_stwing(dev->id, modew_num, ATA_ID_PWOD, sizeof(modew_num));

	i = match_stwing(wist, -1, modew_num);
	if (i >= 0) {
		ata_dev_wawn(dev, "%s is not suppowted fow %s\n",
			     modestw, wist[i]);
		wetuwn 1;
	}
	wetuwn 0;
}

static const chaw * const bad_ata33[] = {
	"Maxtow 92720U8", "Maxtow 92040U6", "Maxtow 91360U4", "Maxtow 91020U3",
	"Maxtow 90845U3", "Maxtow 90650U2",
	"Maxtow 91360D8", "Maxtow 91190D7", "Maxtow 91020D6", "Maxtow 90845D5",
	"Maxtow 90680D4", "Maxtow 90510D3", "Maxtow 90340D2",
	"Maxtow 91152D8", "Maxtow 91008D7", "Maxtow 90845D6", "Maxtow 90840D6",
	"Maxtow 90720D5", "Maxtow 90648D5", "Maxtow 90576D4",
	"Maxtow 90510D4",
	"Maxtow 90432D3", "Maxtow 90288D2", "Maxtow 90256D2",
	"Maxtow 91000D8", "Maxtow 90910D8", "Maxtow 90875D7", "Maxtow 90840D7",
	"Maxtow 90750D6", "Maxtow 90625D5", "Maxtow 90500D4",
	"Maxtow 91728D8", "Maxtow 91512D7", "Maxtow 91303D6", "Maxtow 91080D5",
	"Maxtow 90845D4", "Maxtow 90680D4", "Maxtow 90648D3", "Maxtow 90432D2",
	NUWW
};

static const chaw * const bad_ata100_5[] = {
	"IBM-DTWA-307075",
	"IBM-DTWA-307060",
	"IBM-DTWA-307045",
	"IBM-DTWA-307030",
	"IBM-DTWA-307020",
	"IBM-DTWA-307015",
	"IBM-DTWA-305040",
	"IBM-DTWA-305030",
	"IBM-DTWA-305020",
	"IC35W010AVEW07-0",
	"IC35W020AVEW07-0",
	"IC35W030AVEW07-0",
	"IC35W040AVEW07-0",
	"IC35W060AVEW07-0",
	"WDC AC310200W",
	NUWW
};

/**
 *	hpt370_fiwtew	-	mode sewection fiwtew
 *	@adev: ATA device
 *	@mask: mode mask
 *
 *	Bwock UDMA on devices that cause twoubwe with this contwowwew.
 */

static unsigned int hpt370_fiwtew(stwuct ata_device *adev, unsigned int mask)
{
	if (adev->cwass == ATA_DEV_ATA) {
		if (hpt_dma_bwackwisted(adev, "UDMA", bad_ata33))
			mask &= ~ATA_MASK_UDMA;
		if (hpt_dma_bwackwisted(adev, "UDMA100", bad_ata100_5))
			mask &= ~(0xE0 << ATA_SHIFT_UDMA);
	}
	wetuwn mask;
}

/**
 *	hpt370a_fiwtew	-	mode sewection fiwtew
 *	@adev: ATA device
 *	@mask: mode mask
 *
 *	Bwock UDMA on devices that cause twoubwe with this contwowwew.
 */

static unsigned int hpt370a_fiwtew(stwuct ata_device *adev, unsigned int mask)
{
	if (adev->cwass == ATA_DEV_ATA) {
		if (hpt_dma_bwackwisted(adev, "UDMA100", bad_ata100_5))
			mask &= ~(0xE0 << ATA_SHIFT_UDMA);
	}
	wetuwn mask;
}

/**
 *	hpt372_fiwtew	-	mode sewection fiwtew
 *	@adev: ATA device
 *	@mask: mode mask
 *
 *	The Mawveww bwidge chips used on the HighPoint SATA cawds do not seem
 *	to suppowt the UwtwaDMA modes 1, 2, and 3 as weww as any MWDMA modes...
 */
static unsigned int hpt372_fiwtew(stwuct ata_device *adev, unsigned int mask)
{
	if (ata_id_is_sata(adev->id))
		mask &= ~((0xE << ATA_SHIFT_UDMA) | ATA_MASK_MWDMA);

	wetuwn mask;
}

/**
 *	hpt37x_cabwe_detect	-	Detect the cabwe type
 *	@ap: ATA powt to detect on
 *
 *	Wetuwn the cabwe type attached to this powt
 */

static int hpt37x_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 scw2, ata66;

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
 *	hpt374_fn1_cabwe_detect	-	Detect the cabwe type
 *	@ap: ATA powt to detect on
 *
 *	Wetuwn the cabwe type attached to this powt
 */

static int hpt374_fn1_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned int mcwbase = 0x50 + 4 * ap->powt_no;
	u16 mcw3;
	u8 ata66;

	/* Do the extwa channew wowk */
	pci_wead_config_wowd(pdev, mcwbase + 2, &mcw3);
	/* Set bit 15 of 0x52 to enabwe TCBWID as input */
	pci_wwite_config_wowd(pdev, mcwbase + 2, mcw3 | 0x8000);
	pci_wead_config_byte(pdev, 0x5A, &ata66);
	/* Weset TCBWID/FCBWID to output */
	pci_wwite_config_wowd(pdev, mcwbase + 2, mcw3);

	if (ata66 & (2 >> ap->powt_no))
		wetuwn ATA_CBW_PATA40;
	ewse
		wetuwn ATA_CBW_PATA80;
}

/**
 *	hpt37x_pwe_weset	-	weset the hpt37x bus
 *	@wink: ATA wink to weset
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Pewfowm the initiaw weset handwing fow the HPT37x.
 */

static int hpt37x_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static const stwuct pci_bits hpt37x_enabwe_bits[] = {
		{ 0x50, 1, 0x04, 0x04 },
		{ 0x54, 1, 0x04, 0x04 }
	};
	u8 mcw2;

	if (!pci_test_config_bits(pdev, &hpt37x_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	/* Weset the state machine */
	pci_wwite_config_byte(pdev, 0x50 + 4 * ap->powt_no, 0x37);
	udeway(100);

	/*
	 * Disabwe the "fast intewwupt" pwediction.  Don't howd off
	 * on intewwupts. (== 0x01 despite what the docs say)
	 */
	pci_wead_config_byte(pdev, 0x51 + 4 * ap->powt_no, &mcw2);
	/* Is it HPT370/A? */
	if (pdev->device == PCI_DEVICE_ID_TTI_HPT366 && pdev->wevision < 5) {
		mcw2 &= ~0x02;
		mcw2 |= 0x01;
	} ewse {
		mcw2 &= ~0x07;
	}
	pci_wwite_config_byte(pdev, 0x51 + 4 * ap->powt_no, mcw2);

	wetuwn ata_sff_pweweset(wink, deadwine);
}

static void hpt37x_set_mode(stwuct ata_powt *ap, stwuct ata_device *adev,
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

	timing = hpt37x_find_mode(ap, mode);

	pci_wead_config_dwowd(pdev, addw, &weg);
	weg = (weg & ~mask) | (timing & mask);
	pci_wwite_config_dwowd(pdev, addw, weg);
}
/**
 *	hpt37x_set_piomode		-	PIO setup
 *	@ap: ATA intewface
 *	@adev: device on the intewface
 *
 *	Pewfowm PIO mode setup.
 */

static void hpt37x_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	hpt37x_set_mode(ap, adev, adev->pio_mode);
}

/**
 *	hpt37x_set_dmamode		-	DMA timing setup
 *	@ap: ATA intewface
 *	@adev: Device being configuwed
 *
 *	Set up the channew fow MWDMA ow UDMA modes.
 */

static void hpt37x_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	hpt37x_set_mode(ap, adev, adev->dma_mode);
}

/**
 *	hpt370_bmdma_stop		-	DMA engine stop
 *	@qc: ATA command
 *
 *	Wowk awound the HPT370 DMA engine.
 */

static void hpt370_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	void __iomem *bmdma = ap->ioaddw.bmdma_addw;
	u8 dma_stat = iowead8(bmdma + ATA_DMA_STATUS);
	u8 dma_cmd;

	if (dma_stat & ATA_DMA_ACTIVE) {
		udeway(20);
		dma_stat = iowead8(bmdma + ATA_DMA_STATUS);
	}
	if (dma_stat & ATA_DMA_ACTIVE) {
		/* Cweaw the engine */
		pci_wwite_config_byte(pdev, 0x50 + 4 * ap->powt_no, 0x37);
		udeway(10);
		/* Stop DMA */
		dma_cmd = iowead8(bmdma + ATA_DMA_CMD);
		iowwite8(dma_cmd & ~ATA_DMA_STAWT, bmdma + ATA_DMA_CMD);
		/* Cweaw Ewwow */
		dma_stat = iowead8(bmdma + ATA_DMA_STATUS);
		iowwite8(dma_stat | ATA_DMA_INTW | ATA_DMA_EWW,
			 bmdma + ATA_DMA_STATUS);
		/* Cweaw the engine */
		pci_wwite_config_byte(pdev, 0x50 + 4 * ap->powt_no, 0x37);
		udeway(10);
	}
	ata_bmdma_stop(qc);
}

/**
 *	hpt37x_bmdma_stop		-	DMA engine stop
 *	@qc: ATA command
 *
 *	Cwean up aftew the HPT372 and watew DMA engine
 */

static void hpt37x_bmdma_stop(stwuct ata_queued_cmd *qc)
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


static const stwuct scsi_host_tempwate hpt37x_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

/*
 *	Configuwation fow HPT370
 */

static stwuct ata_powt_opewations hpt370_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,

	.bmdma_stop	= hpt370_bmdma_stop,

	.mode_fiwtew	= hpt370_fiwtew,
	.cabwe_detect	= hpt37x_cabwe_detect,
	.set_piomode	= hpt37x_set_piomode,
	.set_dmamode	= hpt37x_set_dmamode,
	.pweweset	= hpt37x_pwe_weset,
};

/*
 *	Configuwation fow HPT370A. Cwose to 370 but wess fiwtews
 */

static stwuct ata_powt_opewations hpt370a_powt_ops = {
	.inhewits	= &hpt370_powt_ops,
	.mode_fiwtew	= hpt370a_fiwtew,
};

/*
 *	Configuwation fow HPT371 and HPT302.
 */

static stwuct ata_powt_opewations hpt302_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,

	.bmdma_stop	= hpt37x_bmdma_stop,

	.cabwe_detect	= hpt37x_cabwe_detect,
	.set_piomode	= hpt37x_set_piomode,
	.set_dmamode	= hpt37x_set_dmamode,
	.pweweset	= hpt37x_pwe_weset,
};

/*
 *	Configuwation fow HPT372. Mode setting wowks wike 371 and 302
 *	but we have a mode fiwtew.
 */

static stwuct ata_powt_opewations hpt372_powt_ops = {
	.inhewits	= &hpt302_powt_ops,
	.mode_fiwtew	= hpt372_fiwtew,
};

/*
 *	Configuwation fow HPT374. Mode setting and fiwtewing wowks wike 372
 *	but we have a diffewent cabwe detection pwoceduwe fow function 1.
 */

static stwuct ata_powt_opewations hpt374_fn1_powt_ops = {
	.inhewits	= &hpt372_powt_ops,
	.cabwe_detect	= hpt374_fn1_cabwe_detect,
};

/**
 *	hpt37x_cwock_swot	-	Tuwn timing to PC cwock entwy
 *	@fweq: Wepowted fwequency in MHz
 *
 *	Tuwn the timing data into a cwock swot (0 fow 33, 1 fow 40, 2 fow 50
 *	and 3 fow 66Mhz)
 */

static int hpt37x_cwock_swot(unsigned int fweq)
{
	if (fweq < 40)
		wetuwn 0;	/* 33Mhz swot */
	if (fweq < 45)
		wetuwn 1;	/* 40Mhz swot */
	if (fweq < 55)
		wetuwn 2;	/* 50Mhz swot */
	wetuwn 3;		/* 60Mhz swot */
}

/**
 *	hpt37x_cawibwate_dpww		-	Cawibwate the DPWW woop
 *	@dev: PCI device
 *
 *	Pewfowm a cawibwation cycwe on the HPT37x DPWW. Wetuwns 1 if this
 *	succeeds
 */

static int hpt37x_cawibwate_dpww(stwuct pci_dev *dev)
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

static int hpt37x_pci_cwock(stwuct pci_dev *pdev, unsigned int base)
{
	unsigned int fweq;
	u32 fcnt;

	/*
	 * Some devices do not wet this vawue be accessed via PCI space
	 * accowding to the owd dwivew. In addition we must use the vawue
	 * fwom FN 0 on the HPT374.
	 */
	if (pdev->device == PCI_DEVICE_ID_TTI_HPT374 &&
	    (PCI_FUNC(pdev->devfn) & 1)) {
		stwuct pci_dev *pdev_fn0;

		pdev_fn0 = pci_get_swot(pdev->bus, pdev->devfn - 1);
		/* Someone hot pwugged the contwowwew on us? */
		if (!pdev_fn0)
			wetuwn 0;
		fcnt = inw(pci_wesouwce_stawt(pdev_fn0, 4) + 0x90);
		pci_dev_put(pdev_fn0);
	} ewse	{
		fcnt = inw(pci_wesouwce_stawt(pdev, 4) + 0x90);
	}

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
 *	hpt37x_init_one		-	Initiawise an HPT37X/302
 *	@dev: PCI device
 *	@id: Entwy in match tabwe
 *
 *	Initiawise an HPT37x device. Thewe awe some intewesting compwications
 *	hewe. Fiwstwy the chip may wepowt 366 and be one of sevewaw vawiants.
 *	Secondwy aww the timings depend on the cwock fow the chip which we must
 *	detect and wook up
 *
 *	This is the known chip mappings. It may be missing a coupwe of watew
 *	weweases.
 *
 *	Chip vewsion		PCI		Wev	Notes
 *	HPT366			4 (HPT366)	0	Othew dwivew
 *	HPT366			4 (HPT366)	1	Othew dwivew
 *	HPT368			4 (HPT366)	2	Othew dwivew
 *	HPT370			4 (HPT366)	3	UDMA100
 *	HPT370A			4 (HPT366)	4	UDMA100
 *	HPT372			4 (HPT366)	5	UDMA133 (1)
 *	HPT372N			4 (HPT366)	6	Othew dwivew
 *	HPT372A			5 (HPT372)	1	UDMA133 (1)
 *	HPT372N			5 (HPT372)	2	Othew dwivew
 *	HPT302			6 (HPT302)	1	UDMA133
 *	HPT302N			6 (HPT302)	2	Othew dwivew
 *	HPT371			7 (HPT371)	*	UDMA133
 *	HPT374			8 (HPT374)	*	UDMA133 4 channew
 *	HPT372N			9 (HPT372N)	*	Othew dwivew
 *
 *	(1) UDMA133 suppowt depends on the bus cwock
 */

static int hpt37x_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	/* HPT370 - UDMA100 */
	static const stwuct ata_powt_info info_hpt370 = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.powt_ops = &hpt370_powt_ops
	};
	/* HPT370A - UDMA100 */
	static const stwuct ata_powt_info info_hpt370a = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.powt_ops = &hpt370a_powt_ops
	};
	/* HPT370 - UDMA66 */
	static const stwuct ata_powt_info info_hpt370_33 = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.powt_ops = &hpt370_powt_ops
	};
	/* HPT370A - UDMA66 */
	static const stwuct ata_powt_info info_hpt370a_33 = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.powt_ops = &hpt370a_powt_ops
	};
	/* HPT372 - UDMA133 */
	static const stwuct ata_powt_info info_hpt372 = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.powt_ops = &hpt372_powt_ops
	};
	/* HPT371, 302 - UDMA133 */
	static const stwuct ata_powt_info info_hpt302 = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.powt_ops = &hpt302_powt_ops
	};
	/* HPT374 - UDMA100, function 1 uses diffewent cabwe_detect method */
	static const stwuct ata_powt_info info_hpt374_fn0 = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.powt_ops = &hpt372_powt_ops
	};
	static const stwuct ata_powt_info info_hpt374_fn1 = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.powt_ops = &hpt374_fn1_powt_ops
	};

	static const int MHz[4] = { 33, 40, 50, 66 };
	void *pwivate_data = NUWW;
	const stwuct ata_powt_info *ppi[] = { NUWW, NUWW };
	u8 wev = dev->wevision;
	u8 iwqmask;
	u8 mcw1;
	unsigned int fweq; /* MHz */
	int pwefew_dpww = 1;

	unsigned wong iobase = pci_wesouwce_stawt(dev, 4);

	const stwuct hpt_chip *chip_tabwe;
	int cwock_swot;
	int wc;

	wc = pcim_enabwe_device(dev);
	if (wc)
		wetuwn wc;

	switch (dev->device) {
	case PCI_DEVICE_ID_TTI_HPT366:
		/* May be a watew chip in disguise. Check */
		/* Owdew chips awe in the HPT366 dwivew. Ignowe them */
		if (wev < 3)
			wetuwn -ENODEV;
		/* N sewies chips have theiw own dwivew. Ignowe */
		if (wev == 6)
			wetuwn -ENODEV;

		switch (wev) {
		case 3:
			ppi[0] = &info_hpt370;
			chip_tabwe = &hpt370;
			pwefew_dpww = 0;
			bweak;
		case 4:
			ppi[0] = &info_hpt370a;
			chip_tabwe = &hpt370a;
			pwefew_dpww = 0;
			bweak;
		case 5:
			ppi[0] = &info_hpt372;
			chip_tabwe = &hpt372;
			bweak;
		defauwt:
			dev_eww(&dev->dev,
				"Unknown HPT366 subtype, pwease wepowt (%d)\n",
			       wev);
			wetuwn -ENODEV;
		}
		bweak;
	case PCI_DEVICE_ID_TTI_HPT372:
		/* 372N if wev >= 2 */
		if (wev >= 2)
			wetuwn -ENODEV;
		ppi[0] = &info_hpt372;
		chip_tabwe = &hpt372a;
		bweak;
	case PCI_DEVICE_ID_TTI_HPT302:
		/* 302N if wev > 1 */
		if (wev > 1)
			wetuwn -ENODEV;
		ppi[0] = &info_hpt302;
		/* Check this */
		chip_tabwe = &hpt302;
		bweak;
	case PCI_DEVICE_ID_TTI_HPT371:
		if (wev > 1)
			wetuwn -ENODEV;
		ppi[0] = &info_hpt302;
		chip_tabwe = &hpt371;
		/*
		 * Singwe channew device, mastew is not pwesent but the BIOS
		 * (ow us fow non x86) must mawk it absent
		 */
		pci_wead_config_byte(dev, 0x50, &mcw1);
		mcw1 &= ~0x04;
		pci_wwite_config_byte(dev, 0x50, mcw1);
		bweak;
	case PCI_DEVICE_ID_TTI_HPT374:
		chip_tabwe = &hpt374;
		if (!(PCI_FUNC(dev->devfn) & 1))
			*ppi = &info_hpt374_fn0;
		ewse
			*ppi = &info_hpt374_fn1;
		bweak;
	defauwt:
		dev_eww(&dev->dev, "PCI tabwe is bogus, pwease wepowt (%d)\n",
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
	 * defauwt to pci cwock. make suwe MA15/16 awe set to output
	 * to pwevent dwives having pwobwems with 40-pin cabwes. Needed
	 * fow some dwives such as IBM-DTWA which wiww not entew weady
	 * state on weset when PDIAG is a input.
	 */

	pci_wwite_config_byte(dev, 0x5b, 0x23);

	/*
	 * HighPoint does this fow HPT372A.
	 * NOTE: This wegistew is onwy wwiteabwe via I/O space.
	 */
	if (chip_tabwe == &hpt372a)
		outb(0x0e, iobase + 0x9c);

	fweq = hpt37x_pci_cwock(dev, chip_tabwe->base);
	if (!fweq)
		wetuwn -ENODEV;

	/*
	 *	Tuwn the fwequency check into a band and then find a timing
	 *	tabwe to match it.
	 */

	cwock_swot = hpt37x_cwock_swot(fweq);
	if (chip_tabwe->cwocks[cwock_swot] == NUWW || pwefew_dpww) {
		/*
		 *	We need to twy PWW mode instead
		 *
		 *	Fow non UDMA133 capabwe devices we shouwd
		 *	use a 50MHz DPWW by choice
		 */
		unsigned int f_wow, f_high;
		int dpww, adjust;

		/* Compute DPWW */
		dpww = (ppi[0]->udma_mask & 0xC0) ? 3 : 2;

		f_wow = (MHz[cwock_swot] * 48) / MHz[dpww];
		f_high = f_wow + 2;
		if (cwock_swot > 1)
			f_high += 2;

		/* Sewect the DPWW cwock. */
		pci_wwite_config_byte(dev, 0x5b, 0x21);
		pci_wwite_config_dwowd(dev, 0x5C,
				       (f_high << 16) | f_wow | 0x100);

		fow (adjust = 0; adjust < 8; adjust++) {
			if (hpt37x_cawibwate_dpww(dev))
				bweak;
			/*
			 * See if it'ww settwe at a fwactionawwy
			 * diffewent cwock
			 */
			if (adjust & 1)
				f_wow -= adjust >> 1;
			ewse
				f_high += adjust >> 1;
			pci_wwite_config_dwowd(dev, 0x5C,
					       (f_high << 16) | f_wow | 0x100);
		}
		if (adjust == 8) {
			dev_eww(&dev->dev, "DPWW did not stabiwize!\n");
			wetuwn -ENODEV;
		}
		if (dpww == 3)
			pwivate_data = (void *)hpt37x_timings_66;
		ewse
			pwivate_data = (void *)hpt37x_timings_50;

		dev_info(&dev->dev, "bus cwock %dMHz, using %dMHz DPWW\n",
			MHz[cwock_swot], MHz[dpww]);
	} ewse {
		pwivate_data = (void *)chip_tabwe->cwocks[cwock_swot];
		/*
		 *	Pewfowm a finaw fixup. Note that we wiww have used the
		 *	DPWW on the HPT372 which means we don't have to wowwy
		 *	about wack of UDMA133 suppowt on wowew cwocks
		 */

		if (cwock_swot < 2 && ppi[0] == &info_hpt370)
			ppi[0] = &info_hpt370_33;
		if (cwock_swot < 2 && ppi[0] == &info_hpt370a)
			ppi[0] = &info_hpt370a_33;

		dev_info(&dev->dev, "%s using %dMHz bus cwock\n",
			chip_tabwe->name, MHz[cwock_swot]);
	}

	/* Now kick off ATA set up */
	wetuwn ata_pci_bmdma_init_one(dev, ppi, &hpt37x_sht, pwivate_data, 0);
}

static const stwuct pci_device_id hpt37x[] = {
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT366), },
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT371), },
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT372), },
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT374), },
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT302), },

	{ },
};

static stwuct pci_dwivew hpt37x_pci_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= hpt37x,
	.pwobe		= hpt37x_init_one,
	.wemove		= ata_pci_wemove_one
};

moduwe_pci_dwivew(hpt37x_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow the Highpoint HPT37x/30x");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, hpt37x);
MODUWE_VEWSION(DWV_VEWSION);
