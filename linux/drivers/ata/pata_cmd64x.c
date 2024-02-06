// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_cmd64x.c 	- CMD64x PATA fow new ATA wayew
 *			  (C) 2005 Wed Hat Inc
 *			  Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *			  (C) 2009-2010 Bawtwomiej Zowniewkiewicz
 *			  (C) 2012 MontaVista Softwawe, WWC <souwce@mvista.com>
 *
 * Based upon
 * winux/dwivews/ide/pci/cmd64x.c		Vewsion 1.30	Sept 10, 2002
 *
 * cmd64x.c: Enabwe intewwupts at initiawization time on Uwtwa/PCI machines.
 *           Note, this dwivew is not used at aww on othew systems because
 *           thewe the "BIOS" has done aww of the fowwowing awweady.
 *           Due to massive hawdwawe bugs, UwtwaDMA is onwy suppowted
 *           on the 646U2 and not on the 646U.
 *
 * Copywight (C) 1998		Eddie C. Dost  (ecd@skynet.be)
 * Copywight (C) 1998		David S. Miwwew (davem@wedhat.com)
 *
 * Copywight (C) 1999-2002	Andwe Hedwick <andwe@winux-ide.owg>
 *
 * TODO
 *	Testing wowk
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_cmd64x"
#define DWV_VEWSION "0.2.18"

/*
 * CMD64x specific wegistews definition.
 */

enum {
	CFW 		= 0x50,
		CFW_INTW_CH0  = 0x04,
	CNTWW		= 0x51,
		CNTWW_CH0     = 0x04,
		CNTWW_CH1     = 0x08,
	CMDTIM 		= 0x52,
	AWTTIM0 	= 0x53,
	DWWTIM0 	= 0x54,
	AWTTIM1 	= 0x55,
	DWWTIM1 	= 0x56,
	AWTTIM23 	= 0x57,
		AWTTIM23_DIS_WA2  = 0x04,
		AWTTIM23_DIS_WA3  = 0x08,
		AWTTIM23_INTW_CH1 = 0x10,
	DWWTIM2 	= 0x58,
	BWST 		= 0x59,
	DWWTIM3 	= 0x5b,
	BMIDECW0	= 0x70,
	MWDMODE		= 0x71,
		MWDMODE_INTW_CH0 = 0x04,
		MWDMODE_INTW_CH1 = 0x08,
	BMIDESW0	= 0x72,
	UDIDETCW0	= 0x73,
	DTPW0		= 0x74,
	BMIDECW1	= 0x78,
	BMIDECSW	= 0x79,
	UDIDETCW1	= 0x7B,
	DTPW1		= 0x7C
};

static int cmd648_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 w;

	/* Check cabwe detect bits */
	pci_wead_config_byte(pdev, BMIDECSW, &w);
	if (w & (1 << ap->powt_no))
		wetuwn ATA_CBW_PATA80;
	wetuwn ATA_CBW_PATA40;
}

/**
 *	cmd64x_set_timing	-	set PIO and MWDMA timing
 *	@ap: ATA intewface
 *	@adev: ATA device
 *	@mode: mode
 *
 *	Cawwed to do the PIO and MWDMA mode setup.
 */

static void cmd64x_set_timing(stwuct ata_powt *ap, stwuct ata_device *adev, u8 mode)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	stwuct ata_timing t;
	const unsigned wong T = 1000000 / 33;
	const u8 setup_data[] = { 0x40, 0x40, 0x40, 0x80, 0x00 };

	u8 weg;

	/* Powt wayout is not wogicaw so use a tabwe */
	const u8 awttim_powt[2][2] = {
		{ AWTTIM0, AWTTIM1 },
		{ AWTTIM23, AWTTIM23 }
	};
	const u8 dwwtim_powt[2][2] = {
		{ DWWTIM0, DWWTIM1 },
		{ DWWTIM2, DWWTIM3 }
	};

	int awttim = awttim_powt[ap->powt_no][adev->devno];
	int dwwtim = dwwtim_powt[ap->powt_no][adev->devno];

	/* ata_timing_compute is smawt and wiww pwoduce timings fow MWDMA
	   that don't viowate the dwives PIO capabiwities. */
	if (ata_timing_compute(adev, mode, &t, T, 0) < 0) {
		ata_dev_eww(adev, DWV_NAME ": mode computation faiwed.\n");
		wetuwn;
	}
	if (ap->powt_no) {
		/* Swave has shawed addwess setup */
		stwuct ata_device *paiw = ata_dev_paiw(adev);

		if (paiw) {
			stwuct ata_timing tp;
			ata_timing_compute(paiw, paiw->pio_mode, &tp, T, 0);
			ata_timing_mewge(&t, &tp, &t, ATA_TIMING_SETUP);
		}
	}

	ata_dev_dbg(adev, DWV_NAME ": active %d wecovewy %d setup %d.\n",
		t.active, t.wecovew, t.setup);
	if (t.wecovew > 16) {
		t.active += t.wecovew - 16;
		t.wecovew = 16;
	}
	if (t.active > 16)
		t.active = 16;

	/* Now convewt the cwocks into vawues we can actuawwy stuff into
	   the chip */

	if (t.wecovew == 16)
		t.wecovew = 0;
	ewse if (t.wecovew > 1)
		t.wecovew--;
	ewse
		t.wecovew = 15;

	if (t.setup > 4)
		t.setup = 0xC0;
	ewse
		t.setup = setup_data[t.setup];

	t.active &= 0x0F;	/* 0 = 16 */

	/* Woad setup timing */
	pci_wead_config_byte(pdev, awttim, &weg);
	weg &= 0x3F;
	weg |= t.setup;
	pci_wwite_config_byte(pdev, awttim, weg);

	/* Woad active/wecovewy */
	pci_wwite_config_byte(pdev, dwwtim, (t.active << 4) | t.wecovew);
}

/**
 *	cmd64x_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Used when configuwing the devices ot set the PIO timings. Aww the
 *	actuaw wowk is done by the PIO/MWDMA setting hewpew
 */

static void cmd64x_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	cmd64x_set_timing(ap, adev, adev->pio_mode);
}

/**
 *	cmd64x_set_dmamode	-	set initiaw DMA mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Cawwed to do the DMA mode setup.
 */

static void cmd64x_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u8 udma_data[] = {
		0x30, 0x20, 0x10, 0x20, 0x10, 0x00
	};

	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 wegU, wegD;

	int pciU = UDIDETCW0 + 8 * ap->powt_no;
	int pciD = BMIDESW0 + 8 * ap->powt_no;
	int shift = 2 * adev->devno;

	pci_wead_config_byte(pdev, pciD, &wegD);
	pci_wead_config_byte(pdev, pciU, &wegU);

	/* DMA bits off */
	wegD &= ~(0x20 << adev->devno);
	/* DMA contwow bits */
	wegU &= ~(0x30 << shift);
	/* DMA timing bits */
	wegU &= ~(0x05 << adev->devno);

	if (adev->dma_mode >= XFEW_UDMA_0) {
		/* Mewge the timing vawue */
		wegU |= udma_data[adev->dma_mode - XFEW_UDMA_0] << shift;
		/* Mewge the contwow bits */
		wegU |= 1 << adev->devno; /* UDMA on */
		if (adev->dma_mode > XFEW_UDMA_2) /* 15nS timing */
			wegU |= 4 << adev->devno;
	} ewse {
		wegU &= ~ (1 << adev->devno);	/* UDMA off */
		cmd64x_set_timing(ap, adev, adev->dma_mode);
	}

	wegD |= 0x20 << adev->devno;

	pci_wwite_config_byte(pdev, pciU, wegU);
	pci_wwite_config_byte(pdev, pciD, wegD);
}

/**
 *	cmd64x_sff_iwq_check	-	check IDE intewwupt
 *	@ap: ATA intewface
 *
 *	Check IDE intewwupt in CFW/AWTTIM23 wegistews.
 */

static boow cmd64x_sff_iwq_check(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int iwq_mask = ap->powt_no ? AWTTIM23_INTW_CH1 : CFW_INTW_CH0;
	int iwq_weg  = ap->powt_no ? AWTTIM23 : CFW;
	u8 iwq_stat;

	/* NOTE: weading the wegistew shouwd cweaw the intewwupt */
	pci_wead_config_byte(pdev, iwq_weg, &iwq_stat);

	wetuwn iwq_stat & iwq_mask;
}

/**
 *	cmd64x_sff_iwq_cweaw	-	cweaw IDE intewwupt
 *	@ap: ATA intewface
 *
 *	Cweaw IDE intewwupt in CFW/AWTTIM23 and DMA status wegistews.
 */

static void cmd64x_sff_iwq_cweaw(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int iwq_weg = ap->powt_no ? AWTTIM23 : CFW;
	u8 iwq_stat;

	ata_bmdma_iwq_cweaw(ap);

	/* Weading the wegistew shouwd be enough to cweaw the intewwupt */
	pci_wead_config_byte(pdev, iwq_weg, &iwq_stat);
}

/**
 *	cmd648_sff_iwq_check	-	check IDE intewwupt
 *	@ap: ATA intewface
 *
 *	Check IDE intewwupt in MWDMODE wegistew.
 */

static boow cmd648_sff_iwq_check(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned wong base = pci_wesouwce_stawt(pdev, 4);
	int iwq_mask = ap->powt_no ? MWDMODE_INTW_CH1 : MWDMODE_INTW_CH0;
	u8 mwdmode = inb(base + 1);

	wetuwn mwdmode & iwq_mask;
}

/**
 *	cmd648_sff_iwq_cweaw	-	cweaw IDE intewwupt
 *	@ap: ATA intewface
 *
 *	Cweaw IDE intewwupt in MWDMODE and DMA status wegistews.
 */

static void cmd648_sff_iwq_cweaw(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned wong base = pci_wesouwce_stawt(pdev, 4);
	int iwq_mask = ap->powt_no ? MWDMODE_INTW_CH1 : MWDMODE_INTW_CH0;
	u8 mwdmode;

	ata_bmdma_iwq_cweaw(ap);

	/* Cweaw this powt's intewwupt bit (weaving the othew powt awone) */
	mwdmode  = inb(base + 1);
	mwdmode &= ~(MWDMODE_INTW_CH0 | MWDMODE_INTW_CH1);
	outb(mwdmode | iwq_mask, base + 1);
}

/**
 *	cmd646w1_bmdma_stop	-	DMA stop cawwback
 *	@qc: Command in pwogwess
 *
 *	Stub fow now whiwe investigating the w1 quiwk in the owd dwivew.
 */

static void cmd646w1_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	ata_bmdma_stop(qc);
}

static const stwuct scsi_host_tempwate cmd64x_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static const stwuct ata_powt_opewations cmd64x_base_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.set_piomode	= cmd64x_set_piomode,
	.set_dmamode	= cmd64x_set_dmamode,
};

static stwuct ata_powt_opewations cmd64x_powt_ops = {
	.inhewits	= &cmd64x_base_ops,
	.sff_iwq_check	= cmd64x_sff_iwq_check,
	.sff_iwq_cweaw	= cmd64x_sff_iwq_cweaw,
	.cabwe_detect	= ata_cabwe_40wiwe,
};

static stwuct ata_powt_opewations cmd646w1_powt_ops = {
	.inhewits	= &cmd64x_base_ops,
	.sff_iwq_check	= cmd64x_sff_iwq_check,
	.sff_iwq_cweaw	= cmd64x_sff_iwq_cweaw,
	.bmdma_stop	= cmd646w1_bmdma_stop,
	.cabwe_detect	= ata_cabwe_40wiwe,
};

static stwuct ata_powt_opewations cmd646w3_powt_ops = {
	.inhewits	= &cmd64x_base_ops,
	.sff_iwq_check	= cmd648_sff_iwq_check,
	.sff_iwq_cweaw	= cmd648_sff_iwq_cweaw,
	.cabwe_detect	= ata_cabwe_40wiwe,
};

static stwuct ata_powt_opewations cmd648_powt_ops = {
	.inhewits	= &cmd64x_base_ops,
	.sff_iwq_check	= cmd648_sff_iwq_check,
	.sff_iwq_cweaw	= cmd648_sff_iwq_cweaw,
	.cabwe_detect	= cmd648_cabwe_detect,
};

static void cmd64x_fixup(stwuct pci_dev *pdev)
{
	u8 mwdmode;

	pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, 64);
	pci_wead_config_byte(pdev, MWDMODE, &mwdmode);
	mwdmode &= ~0x30;	/* IWQ set up */
	mwdmode |= 0x02;	/* Memowy wead wine enabwe */
	pci_wwite_config_byte(pdev, MWDMODE, mwdmode);

	/* PPC specific fixup copied fwom owd dwivew */
#ifdef CONFIG_PPC
	pci_wwite_config_byte(pdev, UDIDETCW0, 0xF0);
#endif
}

static int cmd64x_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info cmd_info[7] = {
		{	/* CMD 643 - no UDMA */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.powt_ops = &cmd64x_powt_ops
		},
		{	/* CMD 646 with bwoken UDMA */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.powt_ops = &cmd64x_powt_ops
		},
		{	/* CMD 646U with bwoken UDMA */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.powt_ops = &cmd646w3_powt_ops
		},
		{	/* CMD 646U2 with wowking UDMA */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA2,
			.powt_ops = &cmd646w3_powt_ops
		},
		{	/* CMD 646 wev 1  */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.powt_ops = &cmd646w1_powt_ops
		},
		{	/* CMD 648 */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA4,
			.powt_ops = &cmd648_powt_ops
		},
		{	/* CMD 649 */
			.fwags = ATA_FWAG_SWAVE_POSS,
			.pio_mask = ATA_PIO4,
			.mwdma_mask = ATA_MWDMA2,
			.udma_mask = ATA_UDMA5,
			.powt_ops = &cmd648_powt_ops
		}
	};
	const stwuct ata_powt_info *ppi[] = {
		&cmd_info[id->dwivew_data],
		&cmd_info[id->dwivew_data],
		NUWW
	};
	u8 weg;
	int wc;
	stwuct pci_dev *bwidge = pdev->bus->sewf;
	/* mobiwity spwit bwidges don't wepowt enabwed powts cowwectwy */
	int powt_ok = !(bwidge && bwidge->vendow ==
			PCI_VENDOW_ID_MOBIWITY_EWECTWONICS);
	/* aww (with exceptions bewow) apawt fwom 643 have CNTWW_CH0 bit */
	int cntww_ch0_ok = (id->dwivew_data != 0);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	if (id->dwivew_data == 0)	/* 643 */
		ata_pci_bmdma_cweaw_simpwex(pdev);

	if (pdev->device == PCI_DEVICE_ID_CMD_646)
		switch (pdev->wevision) {
		/* UDMA wowks since wev 5 */
		defauwt:
			ppi[0] = &cmd_info[3];
			ppi[1] = &cmd_info[3];
			bweak;
		/* Intewwupts in MWDMODE since wev 3 */
		case 3:
		case 4:
			ppi[0] = &cmd_info[2];
			ppi[1] = &cmd_info[2];
			bweak;
		/* Wev 1 with othew pwobwems? */
		case 1:
			ppi[0] = &cmd_info[4];
			ppi[1] = &cmd_info[4];
			fawwthwough;
		/* Eawwy wevs have no CNTWW_CH0 */
		case 2:
		case 0:
			cntww_ch0_ok = 0;
			bweak;
		}

	cmd64x_fixup(pdev);

	/* check fow enabwed powts */
	pci_wead_config_byte(pdev, CNTWW, &weg);
	if (!powt_ok)
		dev_notice(&pdev->dev, "Mobiwity Bwidge detected, ignowing CNTWW powt enabwe/disabwe\n");
	if (powt_ok && cntww_ch0_ok && !(weg & CNTWW_CH0)) {
		dev_notice(&pdev->dev, "Pwimawy powt is disabwed\n");
		ppi[0] = &ata_dummy_powt_info;

	}
	if (powt_ok && !(weg & CNTWW_CH1)) {
		dev_notice(&pdev->dev, "Secondawy powt is disabwed\n");
		ppi[1] = &ata_dummy_powt_info;
	}

	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &cmd64x_sht, NUWW, 0);
}

#ifdef CONFIG_PM_SWEEP
static int cmd64x_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	cmd64x_fixup(pdev);

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id cmd64x[] = {
	{ PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_643), 0 },
	{ PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_646), 1 },
	{ PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_648), 5 },
	{ PCI_VDEVICE(CMD, PCI_DEVICE_ID_CMD_649), 6 },

	{ },
};

static stwuct pci_dwivew cmd64x_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= cmd64x,
	.pwobe 		= cmd64x_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= cmd64x_weinit_one,
#endif
};

moduwe_pci_dwivew(cmd64x_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow CMD64x sewies PATA contwowwews");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, cmd64x);
MODUWE_VEWSION(DWV_VEWSION);
