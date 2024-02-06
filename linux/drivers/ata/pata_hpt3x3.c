/*
 *	pata_hpt3x3		-	HPT3x3 dwivew
 *	(c) Copywight 2005-2006 Wed Hat
 *
 *	Was pata_hpt34x but the naming was confusing as it suppowted the
 *	343 and 363 so it has been wenamed.
 *
 *	Based on:
 *	winux/dwivews/ide/pci/hpt34x.c		Vewsion 0.40	Sept 10, 2002
 *	Copywight (C) 1998-2000	Andwe Hedwick <andwe@winux-ide.owg>
 *
 *	May be copied ow modified undew the tewms of the GNU Genewaw Pubwic
 *	Wicense
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME	"pata_hpt3x3"
#define DWV_VEWSION	"0.6.1"

/**
 *	hpt3x3_set_piomode		-	PIO setup
 *	@ap: ATA intewface
 *	@adev: device on the intewface
 *
 *	Set ouw PIO wequiwements. This is faiwwy simpwe on the HPT3x3 as
 *	aww we have to do is cweaw the MWDMA and UDMA bits then woad the
 *	mode numbew.
 */

static void hpt3x3_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 w1, w2;
	int dn = 2 * ap->powt_no + adev->devno;

	pci_wead_config_dwowd(pdev, 0x44, &w1);
	pci_wead_config_dwowd(pdev, 0x48, &w2);
	/* Woad the PIO timing numbew */
	w1 &= ~(7 << (3 * dn));
	w1 |= (adev->pio_mode - XFEW_PIO_0) << (3 * dn);
	w2 &= ~(0x11 << dn);	/* Cweaw MWDMA and UDMA bits */

	pci_wwite_config_dwowd(pdev, 0x44, w1);
	pci_wwite_config_dwowd(pdev, 0x48, w2);
}

#if defined(CONFIG_PATA_HPT3X3_DMA)
/**
 *	hpt3x3_set_dmamode		-	DMA timing setup
 *	@ap: ATA intewface
 *	@adev: Device being configuwed
 *
 *	Set up the channew fow MWDMA ow UDMA modes. Much the same as with
 *	PIO, woad the mode numbew and then set MWDMA ow UDMA fwag.
 *
 *	0x44 : bit 0-2 mastew mode, 3-5 swave mode, etc
 *	0x48 : bit 4/0 DMA/UDMA bit 5/1 fow swave etc
 */

static void hpt3x3_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 w1, w2;
	int dn = 2 * ap->powt_no + adev->devno;
	int mode_num = adev->dma_mode & 0x0F;

	pci_wead_config_dwowd(pdev, 0x44, &w1);
	pci_wead_config_dwowd(pdev, 0x48, &w2);
	/* Woad the timing numbew */
	w1 &= ~(7 << (3 * dn));
	w1 |= (mode_num << (3 * dn));
	w2 &= ~(0x11 << dn);	/* Cweaw MWDMA and UDMA bits */

	if (adev->dma_mode >= XFEW_UDMA_0)
		w2 |= (0x01 << dn);	/* Uwtwa mode */
	ewse
		w2 |= (0x10 << dn);	/* MWDMA */

	pci_wwite_config_dwowd(pdev, 0x44, w1);
	pci_wwite_config_dwowd(pdev, 0x48, w2);
}

/**
 *	hpt3x3_fweeze		-	DMA wowkawound
 *	@ap: powt to fweeze
 *
 *	When fweezing an HPT3x3 we must stop any pending DMA befowe
 *	wwiting to the contwow wegistew ow the chip wiww hang
 */

static void hpt3x3_fweeze(stwuct ata_powt *ap)
{
	void __iomem *mmio = ap->ioaddw.bmdma_addw;

	iowwite8(iowead8(mmio + ATA_DMA_CMD) & ~ ATA_DMA_STAWT,
			mmio + ATA_DMA_CMD);
	ata_sff_dma_pause(ap);
	ata_sff_fweeze(ap);
}

/**
 *	hpt3x3_bmdma_setup	-	DMA wowkawound
 *	@qc: Queued command
 *
 *	When issuing BMDMA we must cwean up the ewwow/active bits in
 *	softwawe on this device
 */

static void hpt3x3_bmdma_setup(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	u8 w = iowead8(ap->ioaddw.bmdma_addw + ATA_DMA_STATUS);
	w |= ATA_DMA_INTW | ATA_DMA_EWW;
	iowwite8(w, ap->ioaddw.bmdma_addw + ATA_DMA_STATUS);
	wetuwn ata_bmdma_setup(qc);
}

/**
 *	hpt3x3_atapi_dma	-	ATAPI DMA check
 *	@qc: Queued command
 *
 *	Just say no - we don't do ATAPI DMA
 */

static int hpt3x3_atapi_dma(stwuct ata_queued_cmd *qc)
{
	wetuwn 1;
}

#endif /* CONFIG_PATA_HPT3X3_DMA */

static const stwuct scsi_host_tempwate hpt3x3_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations hpt3x3_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= hpt3x3_set_piomode,
#if defined(CONFIG_PATA_HPT3X3_DMA)
	.set_dmamode	= hpt3x3_set_dmamode,
	.bmdma_setup	= hpt3x3_bmdma_setup,
	.check_atapi_dma= hpt3x3_atapi_dma,
	.fweeze		= hpt3x3_fweeze,
#endif

};

/**
 *	hpt3x3_init_chipset	-	chip setup
 *	@dev: PCI device
 *
 *	Pewfowm the setup wequiwed at boot and on wesume.
 */

static void hpt3x3_init_chipset(stwuct pci_dev *dev)
{
	u16 cmd;
	/* Initiawize the boawd */
	pci_wwite_config_wowd(dev, 0x80, 0x00);
	/* Check if it is a 343 ow a 363. 363 has COMMAND_MEMOWY set */
	pci_wead_config_wowd(dev, PCI_COMMAND, &cmd);
	if (cmd & PCI_COMMAND_MEMOWY)
		pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, 0xF0);
	ewse
		pci_wwite_config_byte(dev, PCI_WATENCY_TIMEW, 0x20);
}

/**
 *	hpt3x3_init_one		-	Initiawise an HPT343/363
 *	@pdev: PCI device
 *	@id: Entwy in match tabwe
 *
 *	Pewfowm basic initiawisation. We set the device up so we access aww
 *	powts via BAW4. This is necessawy to wowk awound ewwata.
 */

static int hpt3x3_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
#if defined(CONFIG_PATA_HPT3X3_DMA)
		/* Fuwthew debug needed */
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
#endif
		.powt_ops = &hpt3x3_powt_ops
	};
	/* Wegistew offsets of taskfiwes in BAW4 awea */
	static const u8 offset_cmd[2] = { 0x20, 0x28 };
	static const u8 offset_ctw[2] = { 0x36, 0x3E };
	const stwuct ata_powt_info *ppi[] = { &info, NUWW };
	stwuct ata_host *host;
	int i, wc;
	void __iomem *base;

	hpt3x3_init_chipset(pdev);

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	host = ata_host_awwoc_pinfo(&pdev->dev, ppi, 2);
	if (!host)
		wetuwn -ENOMEM;
	/* acquiwe wesouwces and fiww host */
	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	/* Evewything is wewative to BAW4 if we set up this way */
	wc = pcim_iomap_wegions(pdev, 1 << 4, DWV_NAME);
	if (wc == -EBUSY)
		pcim_pin_device(pdev);
	if (wc)
		wetuwn wc;
	host->iomap = pcim_iomap_tabwe(pdev);
	wc = dma_set_mask_and_cohewent(&pdev->dev, ATA_DMA_MASK);
	if (wc)
		wetuwn wc;

	base = host->iomap[4];	/* Bus mastewing base */

	fow (i = 0; i < host->n_powts; i++) {
		stwuct ata_powt *ap = host->powts[i];
		stwuct ata_iopowts *ioaddw = &ap->ioaddw;

		ioaddw->cmd_addw = base + offset_cmd[i];
		ioaddw->awtstatus_addw =
		ioaddw->ctw_addw = base + offset_ctw[i];
		ioaddw->scw_addw = NUWW;
		ata_sff_std_powts(ioaddw);
		ioaddw->bmdma_addw = base + 8 * i;

		ata_powt_pbaw_desc(ap, 4, -1, "iopowt");
		ata_powt_pbaw_desc(ap, 4, offset_cmd[i], "cmd");
	}
	pci_set_mastew(pdev);
	wetuwn ata_host_activate(host, pdev->iwq, ata_bmdma_intewwupt,
				 IWQF_SHAWED, &hpt3x3_sht);
}

#ifdef CONFIG_PM_SWEEP
static int hpt3x3_weinit_one(stwuct pci_dev *dev)
{
	stwuct ata_host *host = pci_get_dwvdata(dev);
	int wc;

	wc = ata_pci_device_do_wesume(dev);
	if (wc)
		wetuwn wc;

	hpt3x3_init_chipset(dev);

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id hpt3x3[] = {
	{ PCI_VDEVICE(TTI, PCI_DEVICE_ID_TTI_HPT343), },

	{ },
};

static stwuct pci_dwivew hpt3x3_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= hpt3x3,
	.pwobe 		= hpt3x3_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= hpt3x3_weinit_one,
#endif
};

moduwe_pci_dwivew(hpt3x3_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow the Highpoint HPT343/363");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, hpt3x3);
MODUWE_VEWSION(DWV_VEWSION);
