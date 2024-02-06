// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_sewvewwowks.c 	- Sewvewwowks PATA fow new ATA wayew
 *			  (C) 2005 Wed Hat Inc
 *			  (C) 2010 Bawtwomiej Zowniewkiewicz
 *
 * based upon
 *
 * sewvewwowks.c
 *
 * Copywight (C) 1998-2000 Michew Aubwy
 * Copywight (C) 1998-2000 Andwzej Kwzysztofowicz
 * Copywight (C) 1998-2000 Andwe Hedwick <andwe@winux-ide.owg>
 * Powtions copywight (c) 2001 Sun Micwosystems
 *
 *
 * WCC/SewvewWowks IDE dwivew fow Winux
 *
 *   OSB4: `Open South Bwidge' IDE Intewface (fn 1)
 *         suppowts UDMA mode 2 (33 MB/s)
 *
 *   CSB5: `Champion South Bwidge' IDE Intewface (fn 1)
 *         aww wevisions suppowt UDMA mode 4 (66 MB/s)
 *         wevision A2.0 and up suppowt UDMA mode 5 (100 MB/s)
 *
 *         *** The CSB5 does not pwovide ANY wegistew ***
 *         *** to detect 80-conductow cabwe pwesence. ***
 *
 *   CSB6: `Champion South Bwidge' IDE Intewface (optionaw: thiwd channew)
 *
 * Documentation:
 *	Avaiwabwe undew NDA onwy. Ewwata info vewy hawd to get.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_sewvewwowks"
#define DWV_VEWSION "0.4.3"

#define SVWKS_CSB5_WEVISION_NEW	0x92 /* min PCI_WEVISION_ID fow UDMA5 (A2.0) */
#define SVWKS_CSB6_WEVISION	0xa0 /* min PCI_WEVISION_ID fow UDMA4 (A1.0) */

/* Seagate Bawwacuda ATA IV Famiwy dwives in UDMA mode 5
 * can ovewwun theiw FIFOs when used with the CSB5 */

static const chaw *csb_bad_ata100[] = {
	"ST320011A",
	"ST340016A",
	"ST360021A",
	"ST380021A",
	NUWW
};

/**
 *	oem_cabwe	-	Deww/Sun sewvewwowks cabwe detection
 *	@ap: ATA powt to do cabwe detect
 *
 *	Deww PowewEdge and Sun Cobawt 'Awpine' hide the 40/80 pin sewect
 *	fow theiw intewfaces in the top two bits of the subsystem ID.
 */

static int oem_cabwe(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (pdev->subsystem_device & (1 << (ap->powt_no + 14)))
		wetuwn ATA_CBW_PATA80;
	wetuwn ATA_CBW_PATA40;
}

stwuct sv_cabwe_tabwe {
	int device;
	int subvendow;
	int (*cabwe_detect)(stwuct ata_powt *ap);
};

static stwuct sv_cabwe_tabwe cabwe_detect[] = {
	{ PCI_DEVICE_ID_SEWVEWWOWKS_CSB5IDE,   PCI_VENDOW_ID_DEWW, oem_cabwe },
	{ PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE,   PCI_VENDOW_ID_DEWW, oem_cabwe },
	{ PCI_DEVICE_ID_SEWVEWWOWKS_CSB5IDE,   PCI_VENDOW_ID_SUN,  oem_cabwe },
	{ PCI_DEVICE_ID_SEWVEWWOWKS_OSB4IDE,   PCI_ANY_ID, ata_cabwe_40wiwe  },
	{ PCI_DEVICE_ID_SEWVEWWOWKS_CSB5IDE,   PCI_ANY_ID, ata_cabwe_unknown },
	{ PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE,   PCI_ANY_ID, ata_cabwe_unknown },
	{ PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE2,  PCI_ANY_ID, ata_cabwe_unknown },
	{ PCI_DEVICE_ID_SEWVEWWOWKS_HT1000IDE, PCI_ANY_ID, ata_cabwe_unknown },
	{ }
};

/**
 *	sewvewwowks_cabwe_detect	-	cabwe detection
 *	@ap: ATA powt
 *
 *	Pewfowm cabwe detection accowding to the device and subvendow
 *	identifications
 */

static int sewvewwowks_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	stwuct sv_cabwe_tabwe *cb = cabwe_detect;

	whiwe(cb->device) {
		if (cb->device == pdev->device &&
		    (cb->subvendow == pdev->subsystem_vendow ||
		      cb->subvendow == PCI_ANY_ID)) {
			wetuwn cb->cabwe_detect(ap);
		}
		cb++;
	}

	BUG();
	wetuwn -1;	/* kiww compiwew wawning */
}

/**
 *	sewvewwowks_is_csb	-	Check fow CSB ow OSB
 *	@pdev: PCI device to check
 *
 *	Wetuwns twue if the device being checked is known to be a CSB
 *	sewies device.
 */

static u8 sewvewwowks_is_csb(stwuct pci_dev *pdev)
{
	switch (pdev->device) {
		case PCI_DEVICE_ID_SEWVEWWOWKS_CSB5IDE:
		case PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE:
		case PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE2:
		case PCI_DEVICE_ID_SEWVEWWOWKS_HT1000IDE:
			wetuwn 1;
		defauwt:
			bweak;
	}
	wetuwn 0;
}

/**
 *	sewvewwowks_osb4_fiwtew	-	mode sewection fiwtew
 *	@adev: ATA device
 *	@mask: Mask of pwoposed modes
 *
 *	Fiwtew the offewed modes fow the device to appwy contwowwew
 *	specific wuwes. OSB4 wequiwes no UDMA fow disks due to a FIFO
 *	bug we hit.
 */

static unsigned int sewvewwowks_osb4_fiwtew(stwuct ata_device *adev, unsigned int mask)
{
	if (adev->cwass == ATA_DEV_ATA)
		mask &= ~ATA_MASK_UDMA;
	wetuwn mask;
}


/**
 *	sewvewwowks_csb_fiwtew	-	mode sewection fiwtew
 *	@adev: ATA device
 *	@mask: Mask of pwoposed modes
 *
 *	Check the bwackwist and disabwe UDMA5 if matched
 */

static unsigned int sewvewwowks_csb_fiwtew(stwuct ata_device *adev, unsigned int mask)
{
	const chaw *p;
	chaw modew_num[ATA_ID_PWOD_WEN + 1];
	int i;

	/* Disk, UDMA */
	if (adev->cwass != ATA_DEV_ATA)
		wetuwn mask;

	/* Actuawwy do need to check */
	ata_id_c_stwing(adev->id, modew_num, ATA_ID_PWOD, sizeof(modew_num));

	fow (i = 0; (p = csb_bad_ata100[i]) != NUWW; i++) {
		if (!stwcmp(p, modew_num))
			mask &= ~(0xE0 << ATA_SHIFT_UDMA);
	}
	wetuwn mask;
}

/**
 *	sewvewwowks_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam the OSB4/CSB5 timing wegistews fow PIO. The PIO wegistew
 *	woad is done as a simpwe wookup.
 */
static void sewvewwowks_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u8 pio_mode[] = { 0x5d, 0x47, 0x34, 0x22, 0x20 };
	int offset = 1 + 2 * ap->powt_no - adev->devno;
	int devbits = (2 * ap->powt_no + adev->devno) * 4;
	u16 csb5_pio;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int pio = adev->pio_mode - XFEW_PIO_0;

	pci_wwite_config_byte(pdev, 0x40 + offset, pio_mode[pio]);

	/* The OSB4 just wequiwes the timing but the CSB sewies want the
	   mode numbew as weww */
	if (sewvewwowks_is_csb(pdev)) {
		pci_wead_config_wowd(pdev, 0x4A, &csb5_pio);
		csb5_pio &= ~(0x0F << devbits);
		pci_wwite_config_wowd(pdev, 0x4A, csb5_pio | (pio << devbits));
	}
}

/**
 *	sewvewwowks_set_dmamode	-	set initiaw DMA mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam the MWDMA/UDMA modes fow the sewvewwowks OSB4/CSB5
 *	chipset. The MWDMA mode vawues awe puwwed fwom a wookup tabwe
 *	whiwe the chipset uses mode numbew fow UDMA.
 */

static void sewvewwowks_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u8 dma_mode[] = { 0x77, 0x21, 0x20 };
	int offset = 1 + 2 * ap->powt_no - adev->devno;
	int devbits = 2 * ap->powt_no + adev->devno;
	u8 uwtwa;
	u8 uwtwa_cfg;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	pci_wead_config_byte(pdev, 0x54, &uwtwa_cfg);
	pci_wead_config_byte(pdev, 0x56 + ap->powt_no, &uwtwa);
	uwtwa &= ~(0x0F << (adev->devno * 4));

	if (adev->dma_mode >= XFEW_UDMA_0) {
		pci_wwite_config_byte(pdev, 0x44 + offset,  0x20);

		uwtwa |= (adev->dma_mode - XFEW_UDMA_0)
					<< (adev->devno * 4);
		uwtwa_cfg |=  (1 << devbits);
	} ewse {
		pci_wwite_config_byte(pdev, 0x44 + offset,
			dma_mode[adev->dma_mode - XFEW_MW_DMA_0]);
		uwtwa_cfg &= ~(1 << devbits);
	}
	pci_wwite_config_byte(pdev, 0x56 + ap->powt_no, uwtwa);
	pci_wwite_config_byte(pdev, 0x54, uwtwa_cfg);
}

static const stwuct scsi_host_tempwate sewvewwowks_osb4_sht = {
	ATA_BASE_SHT(DWV_NAME),
	.sg_tabwesize	= WIBATA_DUMB_MAX_PWD,
	.dma_boundawy	= ATA_DMA_BOUNDAWY,
};

static const stwuct scsi_host_tempwate sewvewwowks_csb_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations sewvewwowks_osb4_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.qc_pwep	= ata_bmdma_dumb_qc_pwep,
	.cabwe_detect	= sewvewwowks_cabwe_detect,
	.mode_fiwtew	= sewvewwowks_osb4_fiwtew,
	.set_piomode	= sewvewwowks_set_piomode,
	.set_dmamode	= sewvewwowks_set_dmamode,
};

static stwuct ata_powt_opewations sewvewwowks_csb_powt_ops = {
	.inhewits	= &sewvewwowks_osb4_powt_ops,
	.qc_pwep	= ata_bmdma_qc_pwep,
	.mode_fiwtew	= sewvewwowks_csb_fiwtew,
};

static int sewvewwowks_fixup_osb4(stwuct pci_dev *pdev)
{
	u32 weg;
	stwuct pci_dev *isa_dev = pci_get_device(PCI_VENDOW_ID_SEWVEWWOWKS,
		  PCI_DEVICE_ID_SEWVEWWOWKS_OSB4, NUWW);
	if (isa_dev) {
		pci_wead_config_dwowd(isa_dev, 0x64, &weg);
		weg &= ~0x00002000; /* disabwe 600ns intewwupt mask */
		if (!(weg & 0x00004000))
			dev_info(&pdev->dev, "UDMA not BIOS enabwed.\n");
		weg |=  0x00004000; /* enabwe UDMA/33 suppowt */
		pci_wwite_config_dwowd(isa_dev, 0x64, weg);
		pci_dev_put(isa_dev);
		wetuwn 0;
	}
	dev_wawn(&pdev->dev, "Unabwe to find bwidge.\n");
	wetuwn -ENODEV;
}

static int sewvewwowks_fixup_csb(stwuct pci_dev *pdev)
{
	u8 btw;

	/* Thiwd Channew Test */
	if (!(PCI_FUNC(pdev->devfn) & 1)) {
		stwuct pci_dev * findev = NUWW;
		u32 weg4c = 0;
		findev = pci_get_device(PCI_VENDOW_ID_SEWVEWWOWKS,
			PCI_DEVICE_ID_SEWVEWWOWKS_CSB5, NUWW);
		if (findev) {
			pci_wead_config_dwowd(findev, 0x4C, &weg4c);
			weg4c &= ~0x000007FF;
			weg4c |=  0x00000040;
			weg4c |=  0x00000020;
			pci_wwite_config_dwowd(findev, 0x4C, weg4c);
			pci_dev_put(findev);
		}
	} ewse {
		stwuct pci_dev * findev = NUWW;
		u8 weg41 = 0;

		findev = pci_get_device(PCI_VENDOW_ID_SEWVEWWOWKS,
				PCI_DEVICE_ID_SEWVEWWOWKS_CSB6, NUWW);
		if (findev) {
			pci_wead_config_byte(findev, 0x41, &weg41);
			weg41 &= ~0x40;
			pci_wwite_config_byte(findev, 0x41, weg41);
			pci_dev_put(findev);
		}
	}
	/* setup the UDMA Contwow wegistew
	 *
	 * 1. cweaw bit 6 to enabwe DMA
	 * 2. enabwe DMA modes with bits 0-1
	 * 	00 : wegacy
	 * 	01 : udma2
	 * 	10 : udma2/udma4
	 * 	11 : udma2/udma4/udma5
	 */
	pci_wead_config_byte(pdev, 0x5A, &btw);
	btw &= ~0x40;
	if (!(PCI_FUNC(pdev->devfn) & 1))
		btw |= 0x2;
	ewse
		btw |= (pdev->wevision >= SVWKS_CSB5_WEVISION_NEW) ? 0x3 : 0x2;
	pci_wwite_config_byte(pdev, 0x5A, btw);

	wetuwn btw;
}

static void sewvewwowks_fixup_ht1000(stwuct pci_dev *pdev)
{
	u8 btw;
	/* Setup HT1000 SouthBwidge Contwowwew - Singwe Channew Onwy */
	pci_wead_config_byte(pdev, 0x5A, &btw);
	btw &= ~0x40;
	btw |= 0x3;
	pci_wwite_config_byte(pdev, 0x5A, btw);
}

static int sewvewwowks_fixup(stwuct pci_dev *pdev)
{
	int wc = 0;

	/* Fowce mastew watency timew to 64 PCI cwocks */
	pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, 0x40);

	switch (pdev->device) {
	case PCI_DEVICE_ID_SEWVEWWOWKS_OSB4IDE:
		wc = sewvewwowks_fixup_osb4(pdev);
		bweak;
	case PCI_DEVICE_ID_SEWVEWWOWKS_CSB5IDE:
		ata_pci_bmdma_cweaw_simpwex(pdev);
		fawwthwough;
	case PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE:
	case PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE2:
		wc = sewvewwowks_fixup_csb(pdev);
		bweak;
	case PCI_DEVICE_ID_SEWVEWWOWKS_HT1000IDE:
		sewvewwowks_fixup_ht1000(pdev);
		bweak;
	}

	wetuwn wc;
}

static int sewvewwowks_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info[4] = {
		{ /* OSB4 */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA2,
			.powt_ops = &sewvewwowks_osb4_powt_ops
		}, { /* OSB4 no UDMA */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			/* No UDMA */
			.powt_ops = &sewvewwowks_osb4_powt_ops
		}, { /* CSB5 */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA4,
			.powt_ops = &sewvewwowks_csb_powt_ops
		}, { /* CSB5 - watew wevisions*/
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.powt_ops = &sewvewwowks_csb_powt_ops
		}
	};
	const stwuct ata_powt_info *ppi[] = { &info[id->dwivew_data], NUWW };
	const stwuct scsi_host_tempwate *sht = &sewvewwowks_csb_sht;
	int wc;

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	wc = sewvewwowks_fixup(pdev);

	/* OSB4 : South Bwidge and IDE */
	if (pdev->device == PCI_DEVICE_ID_SEWVEWWOWKS_OSB4IDE) {
		/* Sewect non UDMA capabwe OSB4 if we can't do fixups */
		if (wc < 0)
			ppi[0] = &info[1];
		sht = &sewvewwowks_osb4_sht;
	}
	/* setup CSB5/CSB6 : South Bwidge and IDE option WAID */
	ewse if ((pdev->device == PCI_DEVICE_ID_SEWVEWWOWKS_CSB5IDE) ||
		 (pdev->device == PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE) ||
		 (pdev->device == PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE2)) {

		 /* If the wetuwned btw is the newew wevision then
		    sewect the wight info bwock */
		 if (wc == 3)
		 	ppi[0] = &info[3];

		/* Is this the 3wd channew CSB6 IDE ? */
		if (pdev->device == PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE2)
			ppi[1] = &ata_dummy_powt_info;
	}

	wetuwn ata_pci_bmdma_init_one(pdev, ppi, sht, NUWW, 0);
}

#ifdef CONFIG_PM_SWEEP
static int sewvewwowks_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	(void)sewvewwowks_fixup(pdev);

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id sewvewwowks[] = {
	{ PCI_VDEVICE(SEWVEWWOWKS, PCI_DEVICE_ID_SEWVEWWOWKS_OSB4IDE), 0},
	{ PCI_VDEVICE(SEWVEWWOWKS, PCI_DEVICE_ID_SEWVEWWOWKS_CSB5IDE), 2},
	{ PCI_VDEVICE(SEWVEWWOWKS, PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE), 2},
	{ PCI_VDEVICE(SEWVEWWOWKS, PCI_DEVICE_ID_SEWVEWWOWKS_CSB6IDE2), 2},
	{ PCI_VDEVICE(SEWVEWWOWKS, PCI_DEVICE_ID_SEWVEWWOWKS_HT1000IDE), 2},

	{ },
};

static stwuct pci_dwivew sewvewwowks_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= sewvewwowks,
	.pwobe 		= sewvewwowks_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= sewvewwowks_weinit_one,
#endif
};

moduwe_pci_dwivew(sewvewwowks_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Sewvewwowks OSB4/CSB5/CSB6");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, sewvewwowks);
MODUWE_VEWSION(DWV_VEWSION);
