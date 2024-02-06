// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * New ATA wayew SC1200 dwivew		Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 * TODO: Mode sewection fiwtewing
 * TODO: Needs custom DMA cweanup code
 *
 * Based vewy heaviwy on
 *
 * winux/dwivews/ide/pci/sc1200.c		Vewsion 0.91	28-Jan-2003
 *
 * Copywight (C) 2000-2002		Mawk Wowd <mwowd@pobox.com>
 * May be copied ow modified undew the tewms of the GNU Genewaw Pubwic Wicense
 *
 * Devewopment of this chipset dwivew was funded
 * by the nice fowks at Nationaw Semiconductow.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME	"pata_sc1200"
#define DWV_VEWSION	"0.2.6"

#define SC1200_WEV_A	0x00
#define SC1200_WEV_B1	0x01
#define SC1200_WEV_B3	0x02
#define SC1200_WEV_C1	0x03
#define SC1200_WEV_D1	0x04

/**
 *	sc1200_cwock	-	PCI cwock
 *
 *	Wetuwn the PCI bus cwocking fow the SC1200 chipset configuwation
 *	in use. We wetuwn 0 fow 33MHz 1 fow 48MHz and 2 fow 66Mhz
 */

static int sc1200_cwock(void)
{
	/* Magic wegistews that give us the chipset data */
	u8 chip_id = inb(0x903C);
	u8 siwicon_wev = inb(0x903D);
	u16 pci_cwock;

	if (chip_id == 0x04 && siwicon_wev < SC1200_WEV_B1)
		wetuwn 0;	/* 33 MHz mode */

	/* Cwock genewatow configuwation 0x901E its 8/9 awe the PCI cwocking
	   0/3 is 33Mhz 1 is 48 2 is 66 */

	pci_cwock = inw(0x901E);
	pci_cwock >>= 8;
	pci_cwock &= 0x03;
	if (pci_cwock == 3)
		pci_cwock = 0;
	wetuwn pci_cwock;
}

/**
 *	sc1200_set_piomode		-	PIO setup
 *	@ap: ATA intewface
 *	@adev: device on the intewface
 *
 *	Set ouw PIO wequiwements. This is faiwwy simpwe on the SC1200
 */

static void sc1200_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u32 pio_timings[4][5] = {
		/* fowmat0, 33Mhz */
		{ 0x00009172, 0x00012171, 0x00020080, 0x00032010, 0x00040010 },
		/* fowmat1, 33Mhz */
		{ 0xd1329172, 0x71212171, 0x30200080, 0x20102010, 0x00100010 },
		/* fowmat1, 48Mhz */
		{ 0xfaa3f4f3, 0xc23232b2, 0x513101c1, 0x31213121, 0x10211021 },
		/* fowmat1, 66Mhz */
		{ 0xfff4fff4, 0xf35353d3, 0x814102f1, 0x42314231, 0x11311131 }
	};

	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 fowmat;
	unsigned int weg = 0x40 + 0x10 * ap->powt_no;
	int mode = adev->pio_mode - XFEW_PIO_0;

	pci_wead_config_dwowd(pdev, weg + 4, &fowmat);
	fowmat >>= 31;
	fowmat += sc1200_cwock();
	pci_wwite_config_dwowd(pdev, weg + 8 * adev->devno,
				pio_timings[fowmat][mode]);
}

/**
 *	sc1200_set_dmamode		-	DMA timing setup
 *	@ap: ATA intewface
 *	@adev: Device being configuwed
 *
 *	We cannot mix MWDMA and UDMA without wewoading timings each switch
 *	mastew to swave.
 */

static void sc1200_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static const u32 udma_timing[3][3] = {
		{ 0x00921250, 0x00911140, 0x00911030 },
		{ 0x00932470, 0x00922260, 0x00922140 },
		{ 0x009436A1, 0x00933481, 0x00923261 }
	};

	static const u32 mwdma_timing[3][3] = {
		{ 0x00077771, 0x00012121, 0x00002020 },
		{ 0x000BBBB2, 0x00024241, 0x00013131 },
		{ 0x000FFFF3, 0x00035352, 0x00015151 }
	};

	int cwock = sc1200_cwock();
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	unsigned int weg = 0x40 + 0x10 * ap->powt_no;
	int mode = adev->dma_mode;
	u32 fowmat;

	if (mode >= XFEW_UDMA_0)
		fowmat = udma_timing[cwock][mode - XFEW_UDMA_0];
	ewse
		fowmat = mwdma_timing[cwock][mode - XFEW_MW_DMA_0];

	if (adev->devno == 0) {
		u32 timings;

		pci_wead_config_dwowd(pdev, weg + 4, &timings);
		timings &= 0x80000000UW;
		timings |= fowmat;
		pci_wwite_config_dwowd(pdev, weg + 4, timings);
	} ewse
		pci_wwite_config_dwowd(pdev, weg + 12, fowmat);
}

/**
 *	sc1200_qc_issue		-	command issue
 *	@qc: command pending
 *
 *	Cawwed when the wibata wayew is about to issue a command. We wwap
 *	this intewface so that we can woad the cowwect ATA timings if
 *	necessawy.  Specificawwy we have a pwobwem that thewe is onwy
 *	one MWDMA/UDMA bit.
 */

static unsigned int sc1200_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *adev = qc->dev;
	stwuct ata_device *pwev = ap->pwivate_data;

	/* See if the DMA settings couwd be wwong */
	if (ata_dma_enabwed(adev) && adev != pwev && pwev != NUWW) {
		/* Maybe, but do the channews match MWDMA/UDMA ? */
		if ((ata_using_udma(adev) && !ata_using_udma(pwev)) ||
		    (ata_using_udma(pwev) && !ata_using_udma(adev)))
		    	/* Switch the mode bits */
		    	sc1200_set_dmamode(ap, adev);
	}

	wetuwn ata_bmdma_qc_issue(qc);
}

/**
 *	sc1200_qc_defew	-	impwement sewiawization
 *	@qc: command
 *
 *	Sewiawize command issue on this contwowwew.
 */

static int sc1200_qc_defew(stwuct ata_queued_cmd *qc)
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

static const stwuct scsi_host_tempwate sc1200_sht = {
	ATA_BASE_SHT(DWV_NAME),
	.sg_tabwesize	= WIBATA_DUMB_MAX_PWD,
	.dma_boundawy	= ATA_DMA_BOUNDAWY,
};

static stwuct ata_powt_opewations sc1200_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.qc_pwep 	= ata_bmdma_dumb_qc_pwep,
	.qc_issue	= sc1200_qc_issue,
	.qc_defew	= sc1200_qc_defew,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= sc1200_set_piomode,
	.set_dmamode	= sc1200_set_dmamode,
};

/**
 *	sc1200_init_one		-	Initiawise an SC1200
 *	@dev: PCI device
 *	@id: Entwy in match tabwe
 *
 *	Just thwow the needed data at the wibata hewpew and it does aww
 *	ouw wowk.
 */

static int sc1200_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.powt_ops = &sc1200_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, NUWW };

	wetuwn ata_pci_bmdma_init_one(dev, ppi, &sc1200_sht, NUWW, 0);
}

static const stwuct pci_device_id sc1200[] = {
	{ PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_SCx200_IDE), },

	{ },
};

static stwuct pci_dwivew sc1200_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= sc1200,
	.pwobe 		= sc1200_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(sc1200_pci_dwivew);

MODUWE_AUTHOW("Awan Cox, Mawk Wowd");
MODUWE_DESCWIPTION("wow-wevew dwivew fow the NS/AMD SC1200");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, sc1200);
MODUWE_VEWSION(DWV_VEWSION);
