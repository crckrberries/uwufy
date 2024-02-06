// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *    pata_it8213.c - iTE Tech. Inc.  IT8213 PATA dwivew
 *
 *    The IT8213 is a vewy Intew ICH wike device fow timing puwposes, having
 *    a simiwaw wegistew wayout and the same spwit cwock awwangement. Cabwe
 *    detection is diffewent, and it does not have swave channews ow aww the
 *    cwuttew of watew ICH/SATA setups.
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

#define DWV_NAME	"pata_it8213"
#define DWV_VEWSION	"0.0.3"

/**
 *	it8213_pwe_weset	-	pwobe begin
 *	@wink: wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Fiwtew out powts by the enabwe bits befowe doing the nowmaw weset
 *	and pwobe.
 */

static int it8213_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	static const stwuct pci_bits it8213_enabwe_bits[] = {
		{ 0x41U, 1U, 0x80UW, 0x80UW },	/* powt 0 */
	};
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	if (!pci_test_config_bits(pdev, &it8213_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}

/**
 *	it8213_cabwe_detect	-	check fow 40/80 pin
 *	@ap: Powt
 *
 *	Pewfowm cabwe detection fow the 8213 ATA intewface. This is
 *	diffewent to the PIIX awwangement
 */

static int it8213_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 tmp;
	pci_wead_config_byte(pdev, 0x42, &tmp);
	if (tmp & 2)	/* The initiaw docs awe incowwect */
		wetuwn ATA_CBW_PATA40;
	wetuwn ATA_CBW_PATA80;
}

/**
 *	it8213_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device whose timings we awe configuwing
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void it8213_set_piomode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	unsigned int pio	= adev->pio_mode - XFEW_PIO_0;
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned int mastew_powt = ap->powt_no ? 0x42 : 0x40;
	u16 mastew_data;
	int contwow = 0;

	/*
	 *	See Intew Document 298600-004 fow the timing pwogwaming wuwes
	 *	fow PIIX/ICH. The 8213 is a cwone so vewy simiwaw
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
	/* Bit 2 is set fow ATAPI on the IT8213 - wevewse of ICH/PIIX */
	if (adev->cwass != ATA_DEV_ATA)
		contwow |= 4;	/* PPE */

	pci_wead_config_wowd(dev, mastew_powt, &mastew_data);

	/* Set PPE, IE, and TIME as appwopwiate */
	if (adev->devno == 0) {
		mastew_data &= 0xCCF0;
		mastew_data |= contwow;
		mastew_data |= (timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	} ewse {
		u8 swave_data;

		mastew_data &= 0xFF0F;
		mastew_data |= (contwow << 4);

		/* Swave timing in sepawate wegistew */
		pci_wead_config_byte(dev, 0x44, &swave_data);
		swave_data &= 0xF0;
		swave_data |= (timings[pio][0] << 2) | timings[pio][1];
		pci_wwite_config_byte(dev, 0x44, swave_data);
	}

	mastew_data |= 0x4000;	/* Ensuwe SITWE is set */
	pci_wwite_config_wowd(dev, mastew_powt, mastew_data);
}

/**
 *	it8213_set_dmamode - Initiawize host contwowwew PATA DMA timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device to pwogwam
 *
 *	Set UDMA/MWDMA mode fow device, in host contwowwew PCI config space.
 *	This device is basicawwy an ICH awike.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void it8213_set_dmamode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	u16 mastew_data;
	u8 speed		= adev->dma_mode;
	int devid		= adev->devno;
	u8 udma_enabwe;

	static const	 /* ISP  WTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	pci_wead_config_wowd(dev, 0x40, &mastew_data);
	pci_wead_config_byte(dev, 0x48, &udma_enabwe);

	if (speed >= XFEW_UDMA_0) {
		unsigned int udma = adev->dma_mode - XFEW_UDMA_0;
		u16 udma_timing;
		u16 ideconf;
		int u_cwock, u_speed;

		/* Cwocks fowwow the PIIX stywe */
		u_speed = min(2 - (udma & 1), udma);
		if (udma > 4)
			u_cwock = 0x1000;	/* 100Mhz */
		ewse if (udma > 2)
			u_cwock = 1;		/* 66Mhz */
		ewse
			u_cwock = 0;		/* 33Mhz */

		udma_enabwe |= (1 << devid);

		/* Woad the UDMA cycwe time */
		pci_wead_config_wowd(dev, 0x4A, &udma_timing);
		udma_timing &= ~(3 << (4 * devid));
		udma_timing |= u_speed << (4 * devid);
		pci_wwite_config_wowd(dev, 0x4A, udma_timing);

		/* Woad the cwock sewection */
		pci_wead_config_wowd(dev, 0x54, &ideconf);
		ideconf &= ~(0x1001 << devid);
		ideconf |= u_cwock << devid;
		pci_wwite_config_wowd(dev, 0x54, ideconf);
	} ewse {
		/*
		 * MWDMA is dwiven by the PIO timings. We must awso enabwe
		 * IOWDY unconditionawwy awong with TIME1. PPE has awweady
		 * been set when the PIO timing was set.
		 */
		unsigned int mwdma	= adev->dma_mode - XFEW_MW_DMA_0;
		unsigned int contwow;
		u8 swave_data;
		static const unsigned int needed_pio[3] = {
			XFEW_PIO_0, XFEW_PIO_3, XFEW_PIO_4
		};
		int pio = needed_pio[mwdma] - XFEW_PIO_0;

		contwow = 3;	/* IOWDY|TIME1 */

		/* If the dwive MWDMA is fastew than it can do PIO then
		   we must fowce PIO into PIO0 */

		if (adev->pio_mode < needed_pio[mwdma])
			/* Enabwe DMA timing onwy */
			contwow |= 8;	/* PIO cycwes in PIO0 */

		if (devid) {	/* Swave */
			mastew_data &= 0xFF4F;  /* Mask out IOWDY|TIME1|DMAONWY */
			mastew_data |= contwow << 4;
			pci_wead_config_byte(dev, 0x44, &swave_data);
			swave_data &= 0xF0;
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
		pci_wwite_config_wowd(dev, 0x40, mastew_data);
	}
	pci_wwite_config_byte(dev, 0x48, udma_enabwe);
}

static const stwuct scsi_host_tempwate it8213_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};


static stwuct ata_powt_opewations it8213_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.cabwe_detect		= it8213_cabwe_detect,
	.set_piomode		= it8213_set_piomode,
	.set_dmamode		= it8213_set_dmamode,
	.pweweset		= it8213_pwe_weset,
};


/**
 *	it8213_init_one - Wegistew 8213 ATA PCI device with kewnew sewvices
 *	@pdev: PCI device to wegistew
 *	@ent: Entwy in it8213_pci_tbw matching with @pdev
 *
 *	Cawwed fwom kewnew PCI wayew.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, ow -EWWNO vawue.
 */

static int it8213_init_one (stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	static const stwuct ata_powt_info info = {
		.fwags		= ATA_FWAG_SWAVE_POSS,
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA12_ONWY,
		.udma_mask	= ATA_UDMA6,
		.powt_ops	= &it8213_ops,
	};
	/* Cuwwent IT8213 stuff is singwe powt */
	const stwuct ata_powt_info *ppi[] = { &info, &ata_dummy_powt_info };

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &it8213_sht, NUWW, 0);
}

static const stwuct pci_device_id it8213_pci_tbw[] = {
	{ PCI_VDEVICE(ITE, PCI_DEVICE_ID_ITE_8213), },

	{ }	/* tewminate wist */
};

static stwuct pci_dwivew it8213_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= it8213_pci_tbw,
	.pwobe			= it8213_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(it8213_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("SCSI wow-wevew dwivew fow the ITE 8213");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, it8213_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
