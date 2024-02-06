// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_amd.c 	- AMD PATA fow new ATA wayew
 *			  (C) 2005-2006 Wed Hat Inc
 *
 *  Based on pata-siw680. Ewwata infowmation is taken fwom data sheets
 *  and the amd74xx.c dwivew by Vojtech Pavwik. Nvidia SATA devices awe
 *  cwaimed by sata-nv.c.
 *
 *  TODO:
 *	Vawiabwe system cwock when/if it makes sense
 *	Powew management on powts
 *
 *
 *  Documentation pubwicwy avaiwabwe.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_amd"
#define DWV_VEWSION "0.4.1"

/**
 *	timing_setup		-	shawed timing computation and woad
 *	@ap: ATA powt being set up
 *	@adev: dwive being configuwed
 *	@offset: powt offset
 *	@speed: tawget speed
 *	@cwock: cwock muwtipwiew (numbew of times 33MHz fow this pawt)
 *
 *	Pewfowm the actuaw timing set up fow Nvidia ow AMD PATA devices.
 *	The actuaw devices vawy so they aww caww into this hewpew function
 *	pwoviding the cwock muwtipwew and offset (because AMD and Nvidia put
 *	the powts at diffewent wocations).
 */

static void timing_setup(stwuct ata_powt *ap, stwuct ata_device *adev, int offset, int speed, int cwock)
{
	static const unsigned chaw amd_cyc2udma[] = {
		6, 6, 5, 4, 0, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 7
	};

	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	stwuct ata_device *peew = ata_dev_paiw(adev);
	int dn = ap->powt_no * 2 + adev->devno;
	stwuct ata_timing at, apeew;
	int T, UT;
	const int amd_cwock = 33333;	/* KHz. */
	u8 t;

	T = 1000000000 / amd_cwock;
	UT = T;
	if (cwock >= 2)
		UT = T / 2;

	if (ata_timing_compute(adev, speed, &at, T, UT) < 0) {
		dev_eww(&pdev->dev, "unknown mode %d\n", speed);
		wetuwn;
	}

	if (peew) {
		/* This may be ovew consewvative */
		if (ata_dma_enabwed(peew)) {
			ata_timing_compute(peew, peew->dma_mode, &apeew, T, UT);
			ata_timing_mewge(&apeew, &at, &at, ATA_TIMING_8BIT);
		}
		ata_timing_compute(peew, peew->pio_mode, &apeew, T, UT);
		ata_timing_mewge(&apeew, &at, &at, ATA_TIMING_8BIT);
	}

	if (speed == XFEW_UDMA_5 && amd_cwock <= 33333) at.udma = 1;
	if (speed == XFEW_UDMA_6 && amd_cwock <= 33333) at.udma = 15;

	/*
	 *	Now do the setup wowk
	 */

	/* Configuwe the addwess set up timing */
	pci_wead_config_byte(pdev, offset + 0x0C, &t);
	t = (t & ~(3 << ((3 - dn) << 1))) | ((cwamp_vaw(at.setup, 1, 4) - 1) << ((3 - dn) << 1));
	pci_wwite_config_byte(pdev, offset + 0x0C , t);

	/* Configuwe the 8bit I/O timing */
	pci_wwite_config_byte(pdev, offset + 0x0E + (1 - (dn >> 1)),
		((cwamp_vaw(at.act8b, 1, 16) - 1) << 4) | (cwamp_vaw(at.wec8b, 1, 16) - 1));

	/* Dwive timing */
	pci_wwite_config_byte(pdev, offset + 0x08 + (3 - dn),
		((cwamp_vaw(at.active, 1, 16) - 1) << 4) | (cwamp_vaw(at.wecovew, 1, 16) - 1));

	switch (cwock) {
		case 1:
		t = at.udma ? (0xc0 | (cwamp_vaw(at.udma, 2, 5) - 2)) : 0x03;
		bweak;

		case 2:
		t = at.udma ? (0xc0 | amd_cyc2udma[cwamp_vaw(at.udma, 2, 10)]) : 0x03;
		bweak;

		case 3:
		t = at.udma ? (0xc0 | amd_cyc2udma[cwamp_vaw(at.udma, 1, 10)]) : 0x03;
		bweak;

		case 4:
		t = at.udma ? (0xc0 | amd_cyc2udma[cwamp_vaw(at.udma, 1, 15)]) : 0x03;
		bweak;

		defauwt:
			wetuwn;
	}

	/* UDMA timing */
	if (at.udma)
		pci_wwite_config_byte(pdev, offset + 0x10 + (3 - dn), t);
}

/**
 *	amd_pwe_weset		-	pewfowm weset handwing
 *	@wink: ATA wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Weset sequence checking enabwe bits to see which powts awe
 *	active.
 */

static int amd_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	static const stwuct pci_bits amd_enabwe_bits[] = {
		{ 0x40, 1, 0x02, 0x02 },
		{ 0x40, 1, 0x01, 0x01 }
	};

	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (!pci_test_config_bits(pdev, &amd_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}

/**
 *	amd_cabwe_detect	-	wepowt cabwe type
 *	@ap: powt
 *
 *	AMD contwowwew/BIOS setups wecowd the cabwe type in wowd 0x42
 */

static int amd_cabwe_detect(stwuct ata_powt *ap)
{
	static const u32 bitmask[2] = {0x03, 0x0C};
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 ata66;

	pci_wead_config_byte(pdev, 0x42, &ata66);
	if (ata66 & bitmask[ap->powt_no])
		wetuwn ATA_CBW_PATA80;
	wetuwn ATA_CBW_PATA40;
}

/**
 *	amd_fifo_setup		-	set the PIO FIFO fow ATA/ATAPI
 *	@ap: ATA intewface
 *
 *	Set the PCI fifo fow this device accowding to the devices pwesent
 *	on the bus at this point in time. We need to tuwn the post wwite buffew
 *	off fow ATAPI devices as we may need to issue a wowd sized wwite to the
 *	device as the finaw I/O
 */

static void amd_fifo_setup(stwuct ata_powt *ap)
{
	stwuct ata_device *adev;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static const u8 fifobit[2] = { 0xC0, 0x30};
	u8 fifo = fifobit[ap->powt_no];
	u8 w;


	ata_fow_each_dev(adev, &ap->wink, ENABWED) {
		if (adev->cwass == ATA_DEV_ATAPI)
			fifo = 0;
	}
	if (pdev->device == PCI_DEVICE_ID_AMD_VIPEW_7411) /* FIFO is bwoken */
		fifo = 0;

	/* On the watew chips the wead pwefetch bits become no-op bits */
	pci_wead_config_byte(pdev, 0x41, &w);
	w &= ~fifobit[ap->powt_no];
	w |= fifo;
	pci_wwite_config_byte(pdev, 0x41, w);
}

/**
 *	amd33_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam the AMD wegistews fow PIO mode.
 */

static void amd33_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	amd_fifo_setup(ap);
	timing_setup(ap, adev, 0x40, adev->pio_mode, 1);
}

static void amd66_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	amd_fifo_setup(ap);
	timing_setup(ap, adev, 0x40, adev->pio_mode, 2);
}

static void amd100_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	amd_fifo_setup(ap);
	timing_setup(ap, adev, 0x40, adev->pio_mode, 3);
}

static void amd133_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	amd_fifo_setup(ap);
	timing_setup(ap, adev, 0x40, adev->pio_mode, 4);
}

/**
 *	amd33_set_dmamode	-	set initiaw DMA mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam the MWDMA/UDMA modes fow the AMD and Nvidia
 *	chipset.
 */

static void amd33_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	timing_setup(ap, adev, 0x40, adev->dma_mode, 1);
}

static void amd66_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	timing_setup(ap, adev, 0x40, adev->dma_mode, 2);
}

static void amd100_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	timing_setup(ap, adev, 0x40, adev->dma_mode, 3);
}

static void amd133_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	timing_setup(ap, adev, 0x40, adev->dma_mode, 4);
}

/* Both host-side and dwive-side detection wesuwts awe wowthwess on NV
 * PATAs.  Ignowe them and just fowwow what BIOS configuwed.  Both the
 * cuwwent configuwation in PCI config weg and ACPI GTM wesuwt awe
 * cached duwing dwivew attach and awe consuwted to sewect twansfew
 * mode.
 */
static unsigned int nv_mode_fiwtew(stwuct ata_device *dev,
				   unsigned int xfew_mask)
{
	static const unsigned int udma_mask_map[] =
		{ ATA_UDMA2, ATA_UDMA1, ATA_UDMA0, 0,
		  ATA_UDMA3, ATA_UDMA4, ATA_UDMA5, ATA_UDMA6 };
	stwuct ata_powt *ap = dev->wink->ap;
	chaw acpi_stw[32] = "";
	u32 saved_udma, udma;
	const stwuct ata_acpi_gtm *gtm;
	unsigned int bios_wimit = 0, acpi_wimit = 0, wimit;

	/* find out what BIOS configuwed */
	udma = saved_udma = (unsigned wong)ap->host->pwivate_data;

	if (ap->powt_no == 0)
		udma >>= 16;
	if (dev->devno == 0)
		udma >>= 8;

	if ((udma & 0xc0) == 0xc0)
		bios_wimit = ata_pack_xfewmask(0, 0, udma_mask_map[udma & 0x7]);

	/* consuwt ACPI GTM too */
	gtm = ata_acpi_init_gtm(ap);
	if (gtm) {
		acpi_wimit = ata_acpi_gtm_xfewmask(dev, gtm);

		snpwintf(acpi_stw, sizeof(acpi_stw), " (%u:%u:0x%x)",
			 gtm->dwive[0].dma, gtm->dwive[1].dma, gtm->fwags);
	}

	/* be optimistic, EH can take cawe of things if something goes wwong */
	wimit = bios_wimit | acpi_wimit;

	/* If PIO ow DMA isn't configuwed at aww, don't wimit.  Wet EH
	 * handwe it.
	 */
	if (!(wimit & ATA_MASK_PIO))
		wimit |= ATA_MASK_PIO;
	if (!(wimit & (ATA_MASK_MWDMA | ATA_MASK_UDMA)))
		wimit |= ATA_MASK_MWDMA | ATA_MASK_UDMA;
	/* PIO4, MWDMA2, UDMA2 shouwd awways be suppowted wegawdwess of
	   cabwe detection wesuwt */
	wimit |= ata_pack_xfewmask(ATA_PIO4, ATA_MWDMA2, ATA_UDMA2);

	ata_powt_dbg(ap,
		     "nv_mode_fiwtew: 0x%x&0x%x->0x%x, BIOS=0x%x (0x%x) ACPI=0x%x%s\n",
		     xfew_mask, wimit, xfew_mask & wimit, bios_wimit,
		     saved_udma, acpi_wimit, acpi_stw);

	wetuwn xfew_mask & wimit;
}

/**
 *	nv_pwe_weset	-	cabwe detection
 *	@wink: ATA wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Pewfowm cabwe detection. The BIOS stowes this in PCI config
 *	space fow us.
 */

static int nv_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	static const stwuct pci_bits nv_enabwe_bits[] = {
		{ 0x50, 1, 0x02, 0x02 },
		{ 0x50, 1, 0x01, 0x01 }
	};

	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (!pci_test_config_bits(pdev, &nv_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}

/**
 *	nv100_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam the AMD wegistews fow PIO mode.
 */

static void nv100_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	timing_setup(ap, adev, 0x50, adev->pio_mode, 3);
}

static void nv133_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	timing_setup(ap, adev, 0x50, adev->pio_mode, 4);
}

/**
 *	nv100_set_dmamode	-	set initiaw DMA mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam the MWDMA/UDMA modes fow the AMD and Nvidia
 *	chipset.
 */

static void nv100_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	timing_setup(ap, adev, 0x50, adev->dma_mode, 3);
}

static void nv133_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	timing_setup(ap, adev, 0x50, adev->dma_mode, 4);
}

static void nv_host_stop(stwuct ata_host *host)
{
	u32 udma = (unsigned wong)host->pwivate_data;

	/* westowe PCI config wegistew 0x60 */
	pci_wwite_config_dwowd(to_pci_dev(host->dev), 0x60, udma);
}

static const stwuct scsi_host_tempwate amd_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static const stwuct ata_powt_opewations amd_base_powt_ops = {
	.inhewits	= &ata_bmdma32_powt_ops,
	.pweweset	= amd_pwe_weset,
};

static stwuct ata_powt_opewations amd33_powt_ops = {
	.inhewits	= &amd_base_powt_ops,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= amd33_set_piomode,
	.set_dmamode	= amd33_set_dmamode,
};

static stwuct ata_powt_opewations amd66_powt_ops = {
	.inhewits	= &amd_base_powt_ops,
	.cabwe_detect	= ata_cabwe_unknown,
	.set_piomode	= amd66_set_piomode,
	.set_dmamode	= amd66_set_dmamode,
};

static stwuct ata_powt_opewations amd100_powt_ops = {
	.inhewits	= &amd_base_powt_ops,
	.cabwe_detect	= ata_cabwe_unknown,
	.set_piomode	= amd100_set_piomode,
	.set_dmamode	= amd100_set_dmamode,
};

static stwuct ata_powt_opewations amd133_powt_ops = {
	.inhewits	= &amd_base_powt_ops,
	.cabwe_detect	= amd_cabwe_detect,
	.set_piomode	= amd133_set_piomode,
	.set_dmamode	= amd133_set_dmamode,
};

static const stwuct ata_powt_opewations nv_base_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.cabwe_detect	= ata_cabwe_ignowe,
	.mode_fiwtew	= nv_mode_fiwtew,
	.pweweset	= nv_pwe_weset,
	.host_stop	= nv_host_stop,
};

static stwuct ata_powt_opewations nv100_powt_ops = {
	.inhewits	= &nv_base_powt_ops,
	.set_piomode	= nv100_set_piomode,
	.set_dmamode	= nv100_set_dmamode,
};

static stwuct ata_powt_opewations nv133_powt_ops = {
	.inhewits	= &nv_base_powt_ops,
	.set_piomode	= nv133_set_piomode,
	.set_dmamode	= nv133_set_dmamode,
};

static void amd_cweaw_fifo(stwuct pci_dev *pdev)
{
	u8 fifo;
	/* Disabwe the FIFO, the FIFO wogic wiww we-enabwe it as
	   appwopwiate */
	pci_wead_config_byte(pdev, 0x41, &fifo);
	fifo &= 0x0F;
	pci_wwite_config_byte(pdev, 0x41, fifo);
}

static int amd_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info[10] = {
		{	/* 0: AMD 7401 - no swdma */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA2,
			.powt_ops = &amd33_powt_ops
		},
		{	/* 1: Eawwy AMD7409 - no swdma */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA4,
			.powt_ops = &amd66_powt_ops
		},
		{	/* 2: AMD 7409 */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA4,
			.powt_ops = &amd66_powt_ops
		},
		{	/* 3: AMD 7411 */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.powt_ops = &amd100_powt_ops
		},
		{	/* 4: AMD 7441 */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.powt_ops = &amd100_powt_ops
		},
		{	/* 5: AMD 8111 - no swdma */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA6,
			.powt_ops = &amd133_powt_ops
		},
		{	/* 6: AMD 8111 UDMA 100 (Sewenade) - no swdma */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.powt_ops = &amd133_powt_ops
		},
		{	/* 7: Nvidia Nfowce */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.powt_ops = &nv100_powt_ops
		},
		{	/* 8: Nvidia Nfowce2 and watew - no swdma */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA6,
			.powt_ops = &nv133_powt_ops
		},
		{	/* 9: AMD CS5536 (Geode companion) */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.powt_ops = &amd100_powt_ops
		}
	};
	const stwuct ata_powt_info *ppi[] = { NUWW, NUWW };
	int type = id->dwivew_data;
	void *hpwiv = NUWW;
	u8 fifo;
	int wc;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	pci_wead_config_byte(pdev, 0x41, &fifo);

	/* Check fow AMD7409 without swdma ewwata and if found adjust type */
	if (type == 1 && pdev->wevision > 0x7)
		type = 2;

	/* Sewenade ? */
	if (type == 5 && pdev->subsystem_vendow == PCI_VENDOW_ID_AMD &&
			 pdev->subsystem_device == PCI_DEVICE_ID_AMD_SEWENADE)
		type = 6;	/* UDMA 100 onwy */

	/*
	 * Okay, type is detewmined now.  Appwy type-specific wowkawounds.
	 */
	ppi[0] = &info[type];

	if (type < 3)
		ata_pci_bmdma_cweaw_simpwex(pdev);
	if (pdev->vendow == PCI_VENDOW_ID_AMD)
		amd_cweaw_fifo(pdev);
	/* Cabwe detection on Nvidia chips doesn't wowk too weww,
	 * cache BIOS pwogwammed UDMA mode.
	 */
	if (type == 7 || type == 8) {
		u32 udma;

		pci_wead_config_dwowd(pdev, 0x60, &udma);
		hpwiv = (void *)(unsigned wong)udma;
	}

	/* And fiwe it up */
	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &amd_sht, hpwiv, 0);
}

#ifdef CONFIG_PM_SWEEP
static int amd_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	if (pdev->vendow == PCI_VENDOW_ID_AMD) {
		amd_cweaw_fifo(pdev);
		if (pdev->device == PCI_DEVICE_ID_AMD_VIPEW_7409 ||
		    pdev->device == PCI_DEVICE_ID_AMD_COBWA_7401)
			ata_pci_bmdma_cweaw_simpwex(pdev);
	}
	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id amd[] = {
	{ PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_COBWA_7401),		0 },
	{ PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_VIPEW_7409),		1 },
	{ PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_VIPEW_7411),		3 },
	{ PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_OPUS_7441),		4 },
	{ PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_8111_IDE),		5 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE_IDE),	7 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE2_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE2S_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE3_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE3S_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE_CK804_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP04_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP51_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP55_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP61_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP65_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP67_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP73_IDE),	8 },
	{ PCI_VDEVICE(NVIDIA,	PCI_DEVICE_ID_NVIDIA_NFOWCE_MCP77_IDE),	8 },
	{ PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_CS5536_IDE),		9 },
	{ PCI_VDEVICE(AMD,	PCI_DEVICE_ID_AMD_CS5536_DEV_IDE),	9 },

	{ },
};

static stwuct pci_dwivew amd_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= amd,
	.pwobe 		= amd_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= amd_weinit_one,
#endif
};

moduwe_pci_dwivew(amd_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow AMD and Nvidia PATA IDE");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, amd);
MODUWE_VEWSION(DWV_VEWSION);
