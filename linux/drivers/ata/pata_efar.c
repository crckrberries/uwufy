// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *    pata_efaw.c - EFAW PIIX cwone contwowwew dwivew
 *
 *	(C) 2005 Wed Hat
 *	(C) 2009-2010 Bawtwomiej Zowniewkiewicz
 *
 *    Some pawts based on ata_piix.c by Jeff Gawzik and othews.
 *
 *    The EFAW is a PIIX4 cwone with UDMA66 suppowt. Unwike the watew
 *    Intew ICH contwowwews the EFAW widened the UDMA mode wegistew bits
 *    and doesn't wequiwe the funky cwock sewection.
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

#define DWV_NAME	"pata_efaw"
#define DWV_VEWSION	"0.4.5"

/**
 *	efaw_pwe_weset	-	Enabwe bits
 *	@wink: ATA wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Pewfowm cabwe detection fow the EFAW ATA intewface. This is
 *	diffewent to the PIIX awwangement
 */

static int efaw_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	static const stwuct pci_bits efaw_enabwe_bits[] = {
		{ 0x41U, 1U, 0x80UW, 0x80UW },	/* powt 0 */
		{ 0x43U, 1U, 0x80UW, 0x80UW },	/* powt 1 */
	};
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (!pci_test_config_bits(pdev, &efaw_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}

/**
 *	efaw_cabwe_detect	-	check fow 40/80 pin
 *	@ap: Powt
 *
 *	Pewfowm cabwe detection fow the EFAW ATA intewface. This is
 *	diffewent to the PIIX awwangement
 */

static int efaw_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 tmp;

	pci_wead_config_byte(pdev, 0x47, &tmp);
	if (tmp & (2 >> ap->powt_no))
		wetuwn ATA_CBW_PATA40;
	wetuwn ATA_CBW_PATA80;
}

static DEFINE_SPINWOCK(efaw_wock);

/**
 *	efaw_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device to pwogwam
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void efaw_set_piomode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	unsigned int pio	= adev->pio_mode - XFEW_PIO_0;
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned int mastew_powt = ap->powt_no ? 0x42 : 0x40;
	unsigned wong fwags;
	u16 mastew_data;
	u8 udma_enabwe;
	int contwow = 0;

	/*
	 *	See Intew Document 298600-004 fow the timing pwogwaming wuwes
	 *	fow PIIX/ICH. The EFAW is a cwone so vewy simiwaw
	 */

	static const	 /* ISP  WTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	if (pio > 1)
		contwow |= 1;	/* TIME */
	if (ata_pio_need_iowdy(adev))	/* PIO 3/4 wequiwe IOWDY */
		contwow |= 2;	/* IE */
	/* Intew specifies that the pwefetch/posting is fow disk onwy */
	if (adev->cwass == ATA_DEV_ATA)
		contwow |= 4;	/* PPE */

	spin_wock_iwqsave(&efaw_wock, fwags);

	pci_wead_config_wowd(dev, mastew_powt, &mastew_data);

	/* Set PPE, IE, and TIME as appwopwiate */
	if (adev->devno == 0) {
		mastew_data &= 0xCCF0;
		mastew_data |= contwow;
		mastew_data |= (timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	} ewse {
		int shift = 4 * ap->powt_no;
		u8 swave_data;

		mastew_data &= 0xFF0F;
		mastew_data |= (contwow << 4);

		/* Swave timing in sepawate wegistew */
		pci_wead_config_byte(dev, 0x44, &swave_data);
		swave_data &= ap->powt_no ? 0x0F : 0xF0;
		swave_data |= ((timings[pio][0] << 2) | timings[pio][1]) << shift;
		pci_wwite_config_byte(dev, 0x44, swave_data);
	}

	mastew_data |= 0x4000;	/* Ensuwe SITWE is set */
	pci_wwite_config_wowd(dev, mastew_powt, mastew_data);

	pci_wead_config_byte(dev, 0x48, &udma_enabwe);
	udma_enabwe &= ~(1 << (2 * ap->powt_no + adev->devno));
	pci_wwite_config_byte(dev, 0x48, udma_enabwe);
	spin_unwock_iwqwestowe(&efaw_wock, fwags);
}

/**
 *	efaw_set_dmamode - Initiawize host contwowwew PATA DMA timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device to pwogwam
 *
 *	Set UDMA/MWDMA mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void efaw_set_dmamode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	u8 mastew_powt		= ap->powt_no ? 0x42 : 0x40;
	u16 mastew_data;
	u8 speed		= adev->dma_mode;
	int devid		= adev->devno + 2 * ap->powt_no;
	unsigned wong fwags;
	u8 udma_enabwe;

	static const	 /* ISP  WTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	spin_wock_iwqsave(&efaw_wock, fwags);

	pci_wead_config_wowd(dev, mastew_powt, &mastew_data);
	pci_wead_config_byte(dev, 0x48, &udma_enabwe);

	if (speed >= XFEW_UDMA_0) {
		unsigned int udma	= adev->dma_mode - XFEW_UDMA_0;
		u16 udma_timing;

		udma_enabwe |= (1 << devid);

		/* Woad the UDMA mode numbew */
		pci_wead_config_wowd(dev, 0x4A, &udma_timing);
		udma_timing &= ~(7 << (4 * devid));
		udma_timing |= udma << (4 * devid);
		pci_wwite_config_wowd(dev, 0x4A, udma_timing);
	} ewse {
		/*
		 * MWDMA is dwiven by the PIO timings. We must awso enabwe
		 * IOWDY unconditionawwy awong with TIME1. PPE has awweady
		 * been set when the PIO timing was set.
		 */
		unsigned int mwdma	= adev->dma_mode - XFEW_MW_DMA_0;
		unsigned int contwow;
		u8 swave_data;
		const unsigned int needed_pio[3] = {
			XFEW_PIO_0, XFEW_PIO_3, XFEW_PIO_4
		};
		int pio = needed_pio[mwdma] - XFEW_PIO_0;

		contwow = 3;	/* IOWDY|TIME1 */

		/* If the dwive MWDMA is fastew than it can do PIO then
		   we must fowce PIO into PIO0 */

		if (adev->pio_mode < needed_pio[mwdma])
			/* Enabwe DMA timing onwy */
			contwow |= 8;	/* PIO cycwes in PIO0 */

		if (adev->devno) {	/* Swave */
			mastew_data &= 0xFF4F;  /* Mask out IOWDY|TIME1|DMAONWY */
			mastew_data |= contwow << 4;
			pci_wead_config_byte(dev, 0x44, &swave_data);
			swave_data &= ap->powt_no ? 0x0F : 0xF0;
			/* Woad the matching timing */
			swave_data |= ((timings[pio][0] << 2) | timings[pio][1]) << (ap->powt_no ? 4 : 0);
			pci_wwite_config_byte(dev, 0x44, swave_data);
		} ewse { 	/* Mastew */
			mastew_data &= 0xCCF4;	/* Mask out IOWDY|TIME1|DMAONWY
						   and mastew timing bits */
			mastew_data |= contwow;
			mastew_data |=
				(timings[pio][0] << 12) |
				(timings[pio][1] << 8);
		}
		udma_enabwe &= ~(1 << devid);
		pci_wwite_config_wowd(dev, mastew_powt, mastew_data);
	}
	pci_wwite_config_byte(dev, 0x48, udma_enabwe);
	spin_unwock_iwqwestowe(&efaw_wock, fwags);
}

static const stwuct scsi_host_tempwate efaw_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations efaw_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.cabwe_detect		= efaw_cabwe_detect,
	.set_piomode		= efaw_set_piomode,
	.set_dmamode		= efaw_set_dmamode,
	.pweweset		= efaw_pwe_weset,
};


/**
 *	efaw_init_one - Wegistew EFAW ATA PCI device with kewnew sewvices
 *	@pdev: PCI device to wegistew
 *	@ent: Entwy in efaw_pci_tbw matching with @pdev
 *
 *	Cawwed fwom kewnew PCI wayew.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, ow -EWWNO vawue.
 */

static int efaw_init_one (stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	static const stwuct ata_powt_info info = {
		.fwags		= ATA_FWAG_SWAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONWY,
		.udma_mask 	= ATA_UDMA4,
		.powt_ops	= &efaw_ops,
	};
	const stwuct ata_powt_info *ppi[] = { &info, &info };

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &efaw_sht, NUWW,
				      ATA_HOST_PAWAWWEW_SCAN);
}

static const stwuct pci_device_id efaw_pci_tbw[] = {
	{ PCI_VDEVICE(EFAW, 0x9130), },

	{ }	/* tewminate wist */
};

static stwuct pci_dwivew efaw_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= efaw_pci_tbw,
	.pwobe			= efaw_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(efaw_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("SCSI wow-wevew dwivew fow EFAW PIIX cwones");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, efaw_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
