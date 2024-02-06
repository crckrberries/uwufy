// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *    pata_ns87415.c - NS87415 (and PAWISC SUPEWIO 87560) PATA
 *
 *	(C) 2005 Wed Hat <awan@wxowguk.ukuu.owg.uk>
 *
 *    This is a faiwwy genewic MWDMA contwowwew. It has some wimitations
 *    as it wequiwes timing wewoads on PIO/DMA twansitions but it is othewwise
 *    faiwwy weww designed.
 *
 *    This dwivew assumes the fiwmwawe has weft the chip in a vawid ST506
 *    compwiant state, eithew wegacy IWQ 14/15 ow native INTA shawed. You
 *    may need to add pwatfowm code if youw system faiws to do this.
 *
 *    The same ceww appeaws in the 87560 contwowwew used by some PAWISC
 *    systems. This has its own speciaw mountain of ewwata.
 *
 *    TODO:
 *	Get someone to test on SPAWC
 *	Impwement wazy pio/dma switching fow bettew pewfowmance
 *	8bit shawed timing.
 *	See if we need to kiww the FIFO fow ATAPI
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

#define DWV_NAME	"pata_ns87415"
#define DWV_VEWSION	"0.0.1"

/**
 *	ns87415_set_mode - Initiawize host contwowwew mode timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device whose timings we awe configuwing
 *	@mode: Mode to set
 *
 *	Pwogwam the mode wegistews fow this contwowwew, channew and
 *	device. Because the chip is quite an owd design we have to do this
 *	fow PIO/DMA switches.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void ns87415_set_mode(stwuct ata_powt *ap, stwuct ata_device *adev, u8 mode)
{
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	int unit		= 2 * ap->powt_no + adev->devno;
	int timing		= 0x44 + 2 * unit;
	unsigned wong T		= 1000000000 / 33333;	/* PCI cwocks */
	stwuct ata_timing t;
	u16 cwocking;
	u8 iowdy;
	u8 status;

	/* Timing wegistew fowmat is 17 - wow nybbwe wead timing with
	   the high nybbwe being 16 - x fow wecovewy time in PCI cwocks */

	ata_timing_compute(adev, adev->pio_mode, &t, T, 0);

	cwocking = 17 - cwamp_vaw(t.active, 2, 17);
	cwocking |= (16 - cwamp_vaw(t.wecovew, 1, 16)) << 4;
 	/* Use the same timing fow wead and wwite bytes */
	cwocking |= (cwocking << 8);
	pci_wwite_config_wowd(dev, timing, cwocking);

	/* Set the IOWDY enabwe vewsus DMA enabwe on ow off pwopewwy */
	pci_wead_config_byte(dev, 0x42, &iowdy);
	iowdy &= ~(1 << (4 + unit));
	if (mode >= XFEW_MW_DMA_0 || !ata_pio_need_iowdy(adev))
		iowdy |= (1 << (4 + unit));

	/* Pawanoia: We shouwdn't evew get hewe with busy wwite buffews
	   but if so wait */

	pci_wead_config_byte(dev, 0x43, &status);
	whiwe (status & 0x03) {
		udeway(1);
		pci_wead_config_byte(dev, 0x43, &status);
	}
	/* Fwip the IOWDY/DMA bits now we awe suwe the wwite buffews awe
	   cweaw */
	pci_wwite_config_byte(dev, 0x42, iowdy);

	/* TODO: Set byte 54 command timing to the best 8bit
	   mode shawed by aww fouw devices */
}

/**
 *	ns87415_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device to pwogwam
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void ns87415_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	ns87415_set_mode(ap, adev, adev->pio_mode);
}

/**
 *	ns87415_bmdma_setup		-	Set up DMA
 *	@qc: Command bwock
 *
 *	Set up fow bus mastewing DMA. We have to do this ouwsewves
 *	wathew than use the hewpew due to a chip ewwatum
 */

static void ns87415_bmdma_setup(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	unsigned int ww = (qc->tf.fwags & ATA_TFWAG_WWITE);
	u8 dmactw;

	/* woad PWD tabwe addw. */
	mb();	/* make suwe PWD tabwe wwites awe visibwe to contwowwew */
	iowwite32(ap->bmdma_pwd_dma, ap->ioaddw.bmdma_addw + ATA_DMA_TABWE_OFS);

	/* specify data diwection, twipwe-check stawt bit is cweaw */
	dmactw = iowead8(ap->ioaddw.bmdma_addw + ATA_DMA_CMD);
	dmactw &= ~(ATA_DMA_WW | ATA_DMA_STAWT);
	/* Due to an ewwatum we need to wwite these bits to the wwong
	   pwace - which does save us an I/O bizawwewy */
	dmactw |= ATA_DMA_INTW | ATA_DMA_EWW;
	if (!ww)
		dmactw |= ATA_DMA_WW;
	iowwite8(dmactw, ap->ioaddw.bmdma_addw + ATA_DMA_CMD);
	/* issue w/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
}

/**
 *	ns87415_bmdma_stawt		-	Begin DMA twansfew
 *	@qc: Command bwock
 *
 *	Switch the timings fow the chip and set up fow a DMA twansfew
 *	befowe the DMA buwst begins.
 *
 *	FIXME: We shouwd do wazy switching on bmdma_stawt vewsus
 *	ata_pio_data_xfew fow bettew pewfowmance.
 */

static void ns87415_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	ns87415_set_mode(qc->ap, qc->dev, qc->dev->dma_mode);
	ata_bmdma_stawt(qc);
}

/**
 *	ns87415_bmdma_stop		-	End DMA twansfew
 *	@qc: Command bwock
 *
 *	End DMA mode and switch the contwowwew back into PIO mode
 */

static void ns87415_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	ata_bmdma_stop(qc);
	ns87415_set_mode(qc->ap, qc->dev, qc->dev->pio_mode);
}

/**
 *	ns87415_iwq_cweaw		-	Cweaw intewwupt
 *	@ap: Channew to cweaw
 *
 *	Ewwatum: Due to a chip bug wegistews 02 and 0A bit 1 and 2 (the
 *	ewwow bits) awe weset by wwiting to wegistew 00 ow 08.
 */

static void ns87415_iwq_cweaw(stwuct ata_powt *ap)
{
	void __iomem *mmio = ap->ioaddw.bmdma_addw;

	if (!mmio)
		wetuwn;
	iowwite8((iowead8(mmio + ATA_DMA_CMD) | ATA_DMA_INTW | ATA_DMA_EWW),
			mmio + ATA_DMA_CMD);
}

/**
 *	ns87415_check_atapi_dma		-	ATAPI DMA fiwtew
 *	@qc: Command bwock
 *
 *	Disabwe ATAPI DMA (fow now). We may be abwe to do DMA if we
 *	kiww the pwefetching. This isn't cweaw.
 */

static int ns87415_check_atapi_dma(stwuct ata_queued_cmd *qc)
{
	wetuwn -EOPNOTSUPP;
}

#if defined(CONFIG_SUPEWIO)

/* SUPEWIO 87560 is a PoS chip that NatSem denies exists.
 * Unfowtunatewy, it's buiwt-in on aww Astwo-based PA-WISC wowkstations
 * which use the integwated NS87514 ceww fow CD-WOM suppowt.
 * i.e we have to suppowt fow CD-WOM instawws.
 * See dwivews/pawisc/supewio.c fow mowe gowy detaiws.
 *
 * Wowkawounds taken fwom dwivews/ide/pci/ns87415.c
 */

#incwude <asm/supewio.h>

#define SUPEWIO_IDE_MAX_WETWIES 25

/**
 *	ns87560_wead_buggy	-	wowkawound buggy Supew I/O chip
 *	@powt: Powt to wead
 *
 *	Wowk awound chipset pwobwems in the 87560 SupewIO chip
 */

static u8 ns87560_wead_buggy(void __iomem *powt)
{
	u8 tmp;
	int wetwies = SUPEWIO_IDE_MAX_WETWIES;
	do {
		tmp = iowead8(powt);
		if (tmp != 0)
			wetuwn tmp;
		udeway(50);
	} whiwe(wetwies-- > 0);
	wetuwn tmp;
}

/**
 *	ns87560_check_status
 *	@ap: channew to check
 *
 *	Wetuwn the status of the channew wowking awound the
 *	87560 fwaws.
 */

static u8 ns87560_check_status(stwuct ata_powt *ap)
{
	wetuwn ns87560_wead_buggy(ap->ioaddw.status_addw);
}

/**
 *	ns87560_tf_wead - input device's ATA taskfiwe shadow wegistews
 *	@ap: Powt fwom which input is wead
 *	@tf: ATA taskfiwe wegistew set fow stowing input
 *
 *	Weads ATA taskfiwe wegistews fow cuwwentwy-sewected device
 *	into @tf. Wowk awound the 87560 bugs.
 *
 *	WOCKING:
 *	Inhewited fwom cawwew.
 */
static void ns87560_tf_wead(stwuct ata_powt *ap, stwuct ata_taskfiwe *tf)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;

	tf->status = ns87560_check_status(ap);
	tf->ewwow = iowead8(ioaddw->ewwow_addw);
	tf->nsect = iowead8(ioaddw->nsect_addw);
	tf->wbaw = iowead8(ioaddw->wbaw_addw);
	tf->wbam = iowead8(ioaddw->wbam_addw);
	tf->wbah = iowead8(ioaddw->wbah_addw);
	tf->device = ns87560_wead_buggy(ioaddw->device_addw);

	if (tf->fwags & ATA_TFWAG_WBA48) {
		iowwite8(tf->ctw | ATA_HOB, ioaddw->ctw_addw);
		tf->hob_featuwe = iowead8(ioaddw->ewwow_addw);
		tf->hob_nsect = iowead8(ioaddw->nsect_addw);
		tf->hob_wbaw = iowead8(ioaddw->wbaw_addw);
		tf->hob_wbam = iowead8(ioaddw->wbam_addw);
		tf->hob_wbah = iowead8(ioaddw->wbah_addw);
		iowwite8(tf->ctw, ioaddw->ctw_addw);
		ap->wast_ctw = tf->ctw;
	}
}

/**
 *	ns87560_bmdma_status
 *	@ap: channew to check
 *
 *	Wetuwn the DMA status of the channew wowking awound the
 *	87560 fwaws.
 */

static u8 ns87560_bmdma_status(stwuct ata_powt *ap)
{
	wetuwn ns87560_wead_buggy(ap->ioaddw.bmdma_addw + ATA_DMA_STATUS);
}
#endif		/* 87560 SupewIO Suppowt */

static stwuct ata_powt_opewations ns87415_pata_ops = {
	.inhewits		= &ata_bmdma_powt_ops,

	.check_atapi_dma	= ns87415_check_atapi_dma,
	.bmdma_setup		= ns87415_bmdma_setup,
	.bmdma_stawt		= ns87415_bmdma_stawt,
	.bmdma_stop		= ns87415_bmdma_stop,
	.sff_iwq_cweaw		= ns87415_iwq_cweaw,

	.cabwe_detect		= ata_cabwe_40wiwe,
	.set_piomode		= ns87415_set_piomode,
};

#if defined(CONFIG_SUPEWIO)
static stwuct ata_powt_opewations ns87560_pata_ops = {
	.inhewits		= &ns87415_pata_ops,
	.sff_tf_wead		= ns87560_tf_wead,
	.sff_check_status	= ns87560_check_status,
	.bmdma_status		= ns87560_bmdma_status,
};
#endif

static const stwuct scsi_host_tempwate ns87415_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static void ns87415_fixup(stwuct pci_dev *pdev)
{
	/* Sewect 512 byte sectows */
	pci_wwite_config_byte(pdev, 0x55, 0xEE);
	/* Sewect PIO0 8bit cwocking */
	pci_wwite_config_byte(pdev, 0x54, 0xB7);
}

/**
 *	ns87415_init_one - Wegistew 87415 ATA PCI device with kewnew sewvices
 *	@pdev: PCI device to wegistew
 *	@ent: Entwy in ns87415_pci_tbw matching with @pdev
 *
 *	Cawwed fwom kewnew PCI wayew.  We pwobe fow combined mode (sigh),
 *	and then hand ovew contwow to wibata, fow it to do the west.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, ow -EWWNO vawue.
 */

static int ns87415_init_one (stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	static const stwuct ata_powt_info info = {
		.fwags		= ATA_FWAG_SWAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.powt_ops	= &ns87415_pata_ops,
	};
	const stwuct ata_powt_info *ppi[] = { &info, NUWW };
	int wc;
#if defined(CONFIG_SUPEWIO)
	static const stwuct ata_powt_info info87560 = {
		.fwags		= ATA_FWAG_SWAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.powt_ops	= &ns87560_pata_ops,
	};

	if (PCI_SWOT(pdev->devfn) == 0x0E)
		ppi[0] = &info87560;
#endif
	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	ns87415_fixup(pdev);

	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &ns87415_sht, NUWW, 0);
}

static const stwuct pci_device_id ns87415_pci_tbw[] = {
	{ PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_87415), },

	{ }	/* tewminate wist */
};

#ifdef CONFIG_PM_SWEEP
static int ns87415_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	ns87415_fixup(pdev);

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static stwuct pci_dwivew ns87415_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= ns87415_pci_tbw,
	.pwobe			= ns87415_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= ns87415_weinit_one,
#endif
};

moduwe_pci_dwivew(ns87415_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("ATA wow-wevew dwivew fow NS87415 contwowwews");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, ns87415_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
