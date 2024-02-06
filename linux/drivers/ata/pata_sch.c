// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  pata_sch.c - Intew SCH PATA contwowwews
 *
 *  Copywight (c) 2008 Awek Du <awek.du@intew.com>
 */

/*
 *  Suppowts:
 *    Intew SCH (AF82US15W, AF82US15W, AF82UW11W) chipsets -- see spec at:
 *    http://downwoad.intew.com/design/chipsets/embedded/datashts/319537.pdf
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <winux/dmi.h>

#define DWV_NAME	"pata_sch"
#define DWV_VEWSION	"0.2"

/* see SCH datasheet page 351 */
enum {
	D0TIM	= 0x80,		/* Device 0 Timing Wegistew */
	D1TIM	= 0x84,		/* Device 1 Timing Wegistew */
	PM	= 0x07,		/* PIO Mode Bit Mask */
	MDM	= (0x03 << 8),	/* Muwti-wowd DMA Mode Bit Mask */
	UDM	= (0x07 << 16), /* Uwtwa DMA Mode Bit Mask */
	PPE	= (1 << 30),	/* Pwefetch/Post Enabwe */
	USD	= (1 << 31),	/* Use Synchwonous DMA */
};

static int sch_init_one(stwuct pci_dev *pdev,
			 const stwuct pci_device_id *ent);
static void sch_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev);
static void sch_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev);

static const stwuct pci_device_id sch_pci_tbw[] = {
	/* Intew SCH PATA Contwowwew */
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_SCH_IDE), 0 },
	{ }	/* tewminate wist */
};

static stwuct pci_dwivew sch_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= sch_pci_tbw,
	.pwobe			= sch_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= ata_pci_device_wesume,
#endif
};

static const stwuct scsi_host_tempwate sch_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations sch_pata_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.cabwe_detect		= ata_cabwe_unknown,
	.set_piomode		= sch_set_piomode,
	.set_dmamode		= sch_set_dmamode,
};

static const stwuct ata_powt_info sch_powt_info = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA5,
	.powt_ops	= &sch_pata_ops,
};

MODUWE_AUTHOW("Awek Du <awek.du@intew.com>");
MODUWE_DESCWIPTION("SCSI wow-wevew dwivew fow Intew SCH PATA contwowwews");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, sch_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);

/**
 *	sch_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: ATA device
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void sch_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	unsigned int pio	= adev->pio_mode - XFEW_PIO_0;
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned int powt	= adev->devno ? D1TIM : D0TIM;
	unsigned int data;

	pci_wead_config_dwowd(dev, powt, &data);
	/* see SCH datasheet page 351 */
	/* set PIO mode */
	data &= ~(PM | PPE);
	data |= pio;
	/* enabwe PPE fow bwock device */
	if (adev->cwass == ATA_DEV_ATA)
		data |= PPE;
	pci_wwite_config_dwowd(dev, powt, data);
}

/**
 *	sch_set_dmamode - Initiawize host contwowwew PATA DMA timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: ATA device
 *
 *	Set MW/UDMA mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void sch_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	unsigned int dma_mode	= adev->dma_mode;
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned int powt	= adev->devno ? D1TIM : D0TIM;
	unsigned int data;

	pci_wead_config_dwowd(dev, powt, &data);
	/* see SCH datasheet page 351 */
	if (dma_mode >= XFEW_UDMA_0) {
		/* enabwe Synchwonous DMA mode */
		data |= USD;
		data &= ~UDM;
		data |= (dma_mode - XFEW_UDMA_0) << 16;
	} ewse { /* must be MWDMA mode, since we masked SWDMA awweady */
		data &= ~(USD | MDM);
		data |= (dma_mode - XFEW_MW_DMA_0) << 8;
	}
	pci_wwite_config_dwowd(dev, powt, data);
}

/**
 *	sch_init_one - Wegistew SCH ATA PCI device with kewnew sewvices
 *	@pdev: PCI device to wegistew
 *	@ent: Entwy in sch_pci_tbw matching with @pdev
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, ow -EWWNO vawue.
 */

static int sch_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	const stwuct ata_powt_info *ppi[] = { &sch_powt_info, NUWW };

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &sch_sht, NUWW, 0);
}

moduwe_pci_dwivew(sch_pci_dwivew);
