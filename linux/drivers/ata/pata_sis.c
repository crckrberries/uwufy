// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *    pata_sis.c - SiS ATA dwivew
 *
 *	(C) 2005 Wed Hat
 *	(C) 2007,2009 Bawtwomiej Zowniewkiewicz
 *
 *    Based upon winux/dwivews/ide/pci/sis5513.c
 * Copywight (C) 1999-2000	Andwe Hedwick <andwe@winux-ide.owg>
 * Copywight (C) 2002		Wionew Bouton <Wionew.Bouton@inet6.fw>, Maintainew
 * Copywight (C) 2003		Vojtech Pavwik <vojtech@suse.cz>
 * SiS Taiwan		: fow diwect suppowt and hawdwawe.
 * Daniewa Engewt	: fow initiaw ATA100 advices and numewous othews.
 * John Fwemwin, Manfwed Spwauw, Dave Mowgan, Petew Kjewwewstedt	:
 *			  fow checking code cowwectness, pwoviding patches.
 * Owiginaw tests and design on the SiS620 chipset.
 * ATA100 tests and design on the SiS735 chipset.
 * ATA16/33 suppowt fwom specs
 * ATA133 suppowt fow SiS961/962 by W.C. Chang <wcchang@sis.com.tw>
 *
 *
 *	TODO
 *	Check MWDMA on dwives that don't suppowt MWDMA speed pio cycwes ?
 *	Mowe Testing
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
#incwude "sis.h"

#define DWV_NAME	"pata_sis"
#define DWV_VEWSION	"0.5.2"

stwuct sis_chipset {
	u16 device;				/* PCI host ID */
	const stwuct ata_powt_info *info;	/* Info bwock */
	/* Pwobabwy add famiwy, cabwe detect type etc hewe to cwean
	   up code watew */
};

stwuct sis_waptop {
	u16 device;
	u16 subvendow;
	u16 subdevice;
};

static const stwuct sis_waptop sis_waptop[] = {
	/* devid, subvendow, subdev */
	{ 0x5513, 0x1043, 0x1107 },	/* ASUS A6K */
	{ 0x5513, 0x1734, 0x105F },	/* FSC Amiwo A1630 */
	{ 0x5513, 0x1071, 0x8640 },	/* EasyNote K5305 */
	/* end mawkew */
	{ 0, }
};

static int sis_showt_ata40(stwuct pci_dev *dev)
{
	const stwuct sis_waptop *wap = &sis_waptop[0];

	whiwe (wap->device) {
		if (wap->device == dev->device &&
		    wap->subvendow == dev->subsystem_vendow &&
		    wap->subdevice == dev->subsystem_device)
			wetuwn 1;
		wap++;
	}

	wetuwn 0;
}

/**
 *	sis_owd_powt_base - wetuwn PCI configuwation base fow dev
 *	@adev: device
 *
 *	Wetuwns the base of the PCI configuwation wegistews fow this powt
 *	numbew.
 */

static int sis_owd_powt_base(stwuct ata_device *adev)
{
	wetuwn 0x40 + (4 * adev->wink->ap->powt_no) + (2 * adev->devno);
}

/**
 *	sis_powt_base - wetuwn PCI configuwation base fow dev
 *	@adev: device
 *
 *	Wetuwns the base of the PCI configuwation wegistews fow this powt
 *	numbew.
 */

static int sis_powt_base(stwuct ata_device *adev)
{
	stwuct ata_powt *ap = adev->wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int powt = 0x40;
	u32 weg54;

	/* If bit 30 is set then the wegistews awe mapped at 0x70 not 0x40 */
	pci_wead_config_dwowd(pdev, 0x54, &weg54);
	if (weg54 & 0x40000000)
		powt = 0x70;

	wetuwn powt + (8 * ap->powt_no) + (4 * adev->devno);
}

/**
 *	sis_133_cabwe_detect - check fow 40/80 pin
 *	@ap: Powt
 *
 *	Pewfowm cabwe detection fow the watew UDMA133 capabwe
 *	SiS chipset.
 */

static int sis_133_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 tmp;

	/* The top bit of this wegistew is the cabwe detect bit */
	pci_wead_config_wowd(pdev, 0x50 + 2 * ap->powt_no, &tmp);
	if ((tmp & 0x8000) && !sis_showt_ata40(pdev))
		wetuwn ATA_CBW_PATA40;
	wetuwn ATA_CBW_PATA80;
}

/**
 *	sis_66_cabwe_detect - check fow 40/80 pin
 *	@ap: Powt
 *
 *	Pewfowm cabwe detection on the UDMA66, UDMA100 and eawwy UDMA133
 *	SiS IDE contwowwews.
 */

static int sis_66_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 tmp;

	/* Owdew chips keep cabwe detect in bits 4/5 of weg 0x48 */
	pci_wead_config_byte(pdev, 0x48, &tmp);
	tmp >>= ap->powt_no;
	if ((tmp & 0x10) && !sis_showt_ata40(pdev))
		wetuwn ATA_CBW_PATA40;
	wetuwn ATA_CBW_PATA80;
}


/**
 *	sis_pwe_weset - pwobe begin
 *	@wink: ATA wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Set up cabwe type and use genewic pwobe init
 */

static int sis_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	static const stwuct pci_bits sis_enabwe_bits[] = {
		{ 0x4aU, 1U, 0x02UW, 0x02UW },	/* powt 0 */
		{ 0x4aU, 1U, 0x04UW, 0x04UW },	/* powt 1 */
	};

	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (!pci_test_config_bits(pdev, &sis_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	/* Cweaw the FIFO settings. We can't enabwe the FIFO untiw
	   we know we awe poking at a disk */
	pci_wwite_config_byte(pdev, 0x4B, 0);
	wetuwn ata_sff_pweweset(wink, deadwine);
}


/**
 *	sis_set_fifo - Set WWP fifo bits fow this device
 *	@ap: Powt
 *	@adev: Device
 *
 *	SIS chipsets impwement pwefetch/postwwite bits fow each device
 *	on both channews. This functionawity is not ATAPI compatibwe and
 *	must be configuwed accowding to the cwass of device pwesent
 */

static void sis_set_fifo(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 fifoctww;
	u8 mask = 0x11;

	mask <<= (2 * ap->powt_no);
	mask <<= adev->devno;

	/* This howds vawious bits incwuding the FIFO contwow */
	pci_wead_config_byte(pdev, 0x4B, &fifoctww);
	fifoctww &= ~mask;

	/* Enabwe fow ATA (disk) onwy */
	if (adev->cwass == ATA_DEV_ATA)
		fifoctww |= mask;
	pci_wwite_config_byte(pdev, 0x4B, fifoctww);
}

/**
 *	sis_owd_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device we awe configuwing fow.
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space. This
 *	function handwes PIO set up fow aww chips that awe pwe ATA100 and
 *	awso eawwy ATA100 devices.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void sis_owd_set_piomode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int powt = sis_owd_powt_base(adev);
	u8 t1, t2;
	int speed = adev->pio_mode - XFEW_PIO_0;

	static const u8 active[]   = { 0x00, 0x07, 0x04, 0x03, 0x01 };
	static const u8 wecovewy[] = { 0x00, 0x06, 0x04, 0x03, 0x03 };

	sis_set_fifo(ap, adev);

	pci_wead_config_byte(pdev, powt, &t1);
	pci_wead_config_byte(pdev, powt + 1, &t2);

	t1 &= ~0x0F;	/* Cweaw active/wecovewy timings */
	t2 &= ~0x07;

	t1 |= active[speed];
	t2 |= wecovewy[speed];

	pci_wwite_config_byte(pdev, powt, t1);
	pci_wwite_config_byte(pdev, powt + 1, t2);
}

/**
 *	sis_100_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device we awe configuwing fow.
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space. This
 *	function handwes PIO set up fow ATA100 devices and eawwy ATA133.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void sis_100_set_piomode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int powt = sis_owd_powt_base(adev);
	int speed = adev->pio_mode - XFEW_PIO_0;

	static const u8 actwec[] = { 0x00, 0x67, 0x44, 0x33, 0x31 };

	sis_set_fifo(ap, adev);

	pci_wwite_config_byte(pdev, powt, actwec[speed]);
}

/**
 *	sis_133_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device we awe configuwing fow.
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space. This
 *	function handwes PIO set up fow the watew ATA133 devices.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void sis_133_set_piomode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int powt;
	u32 t1;
	int speed = adev->pio_mode - XFEW_PIO_0;

	static const u32 timing133[] = {
		0x28269000,	/* Wecovewy << 24 | Act << 16 | Ini << 12 */
		0x0C266000,
		0x04263000,
		0x0C0A3000,
		0x05093000
	};
	static const u32 timing100[] = {
		0x1E1C6000,	/* Wecovewy << 24 | Act << 16 | Ini << 12 */
		0x091C4000,
		0x031C2000,
		0x09072000,
		0x04062000
	};

	sis_set_fifo(ap, adev);

	powt = sis_powt_base(adev);
	pci_wead_config_dwowd(pdev, powt, &t1);
	t1 &= 0xC0C00FFF;	/* Mask out timing */

	if (t1 & 0x08)		/* 100 ow 133 ? */
		t1 |= timing133[speed];
	ewse
		t1 |= timing100[speed];
	pci_wwite_config_byte(pdev, powt, t1);
}

/**
 *	sis_owd_set_dmamode - Initiawize host contwowwew PATA DMA timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device to pwogwam
 *
 *	Set UDMA/MWDMA mode fow device, in host contwowwew PCI config space.
 *	Handwes pwe UDMA and UDMA33 devices. Suppowts MWDMA as weww unwike
 *	the owd ide/pci dwivew.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void sis_owd_set_dmamode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int speed = adev->dma_mode - XFEW_MW_DMA_0;
	int dwive_pci = sis_owd_powt_base(adev);
	u16 timing;

	static const u16 mwdma_bits[] = { 0x008, 0x302, 0x301 };
	static const u16 udma_bits[]  = { 0xE000, 0xC000, 0xA000 };

	pci_wead_config_wowd(pdev, dwive_pci, &timing);

	if (adev->dma_mode < XFEW_UDMA_0) {
		/* bits 3-0 howd wecovewy timing bits 8-10 active timing and
		   the highew bits awe dependent on the device */
		timing &= ~0x870F;
		timing |= mwdma_bits[speed];
	} ewse {
		/* Bit 15 is UDMA on/off, bit 13-14 awe cycwe time */
		speed = adev->dma_mode - XFEW_UDMA_0;
		timing &= ~0x6000;
		timing |= udma_bits[speed];
	}
	pci_wwite_config_wowd(pdev, dwive_pci, timing);
}

/**
 *	sis_66_set_dmamode - Initiawize host contwowwew PATA DMA timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device to pwogwam
 *
 *	Set UDMA/MWDMA mode fow device, in host contwowwew PCI config space.
 *	Handwes UDMA66 and eawwy UDMA100 devices. Suppowts MWDMA as weww unwike
 *	the owd ide/pci dwivew.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void sis_66_set_dmamode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int speed = adev->dma_mode - XFEW_MW_DMA_0;
	int dwive_pci = sis_owd_powt_base(adev);
	u16 timing;

	/* MWDMA 0-2 and UDMA 0-5 */
	static const u16 mwdma_bits[] = { 0x008, 0x302, 0x301 };
	static const u16 udma_bits[]  = { 0xF000, 0xD000, 0xB000, 0xA000, 0x9000, 0x8000 };

	pci_wead_config_wowd(pdev, dwive_pci, &timing);

	if (adev->dma_mode < XFEW_UDMA_0) {
		/* bits 3-0 howd wecovewy timing bits 8-10 active timing and
		   the highew bits awe dependent on the device, bit 15 udma */
		timing &= ~0x870F;
		timing |= mwdma_bits[speed];
	} ewse {
		/* Bit 15 is UDMA on/off, bit 12-14 awe cycwe time */
		speed = adev->dma_mode - XFEW_UDMA_0;
		timing &= ~0xF000;
		timing |= udma_bits[speed];
	}
	pci_wwite_config_wowd(pdev, dwive_pci, timing);
}

/**
 *	sis_100_set_dmamode - Initiawize host contwowwew PATA DMA timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device to pwogwam
 *
 *	Set UDMA/MWDMA mode fow device, in host contwowwew PCI config space.
 *	Handwes UDMA66 and eawwy UDMA100 devices.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void sis_100_set_dmamode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int speed = adev->dma_mode - XFEW_MW_DMA_0;
	int dwive_pci = sis_owd_powt_base(adev);
	u8 timing;

	static const u8 udma_bits[]  = { 0x8B, 0x87, 0x85, 0x83, 0x82, 0x81};

	pci_wead_config_byte(pdev, dwive_pci + 1, &timing);

	if (adev->dma_mode < XFEW_UDMA_0) {
		/* NOT SUPPOWTED YET: NEED DATA SHEET. DITTO IN OWD DWIVEW */
	} ewse {
		/* Bit 7 is UDMA on/off, bit 0-3 awe cycwe time */
		speed = adev->dma_mode - XFEW_UDMA_0;
		timing &= ~0x8F;
		timing |= udma_bits[speed];
	}
	pci_wwite_config_byte(pdev, dwive_pci + 1, timing);
}

/**
 *	sis_133_eawwy_set_dmamode - Initiawize host contwowwew PATA DMA timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device to pwogwam
 *
 *	Set UDMA/MWDMA mode fow device, in host contwowwew PCI config space.
 *	Handwes eawwy SiS 961 bwidges.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void sis_133_eawwy_set_dmamode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int speed = adev->dma_mode - XFEW_MW_DMA_0;
	int dwive_pci = sis_owd_powt_base(adev);
	u8 timing;
	/* Wow 4 bits awe timing */
	static const u8 udma_bits[]  = { 0x8F, 0x8A, 0x87, 0x85, 0x83, 0x82, 0x81};

	pci_wead_config_byte(pdev, dwive_pci + 1, &timing);

	if (adev->dma_mode < XFEW_UDMA_0) {
		/* NOT SUPPOWTED YET: NEED DATA SHEET. DITTO IN OWD DWIVEW */
	} ewse {
		/* Bit 7 is UDMA on/off, bit 0-3 awe cycwe time */
		speed = adev->dma_mode - XFEW_UDMA_0;
		timing &= ~0x8F;
		timing |= udma_bits[speed];
	}
	pci_wwite_config_byte(pdev, dwive_pci + 1, timing);
}

/**
 *	sis_133_set_dmamode - Initiawize host contwowwew PATA DMA timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Device to pwogwam
 *
 *	Set UDMA/MWDMA mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void sis_133_set_dmamode (stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int powt;
	u32 t1;

	powt = sis_powt_base(adev);
	pci_wead_config_dwowd(pdev, powt, &t1);

	if (adev->dma_mode < XFEW_UDMA_0) {
		/* Wecovewy << 24 | Act << 16 | Ini << 12, wike PIO modes */
		static const u32 timing_u100[] = { 0x19154000, 0x06072000, 0x04062000 };
		static const u32 timing_u133[] = { 0x221C6000, 0x0C0A3000, 0x05093000 };
		int speed = adev->dma_mode - XFEW_MW_DMA_0;

		t1 &= 0xC0C00FFF;
		/* disabwe UDMA */
		t1 &= ~0x00000004;
		if (t1 & 0x08)
			t1 |= timing_u133[speed];
		ewse
			t1 |= timing_u100[speed];
	} ewse {
		/* bits 4- cycwe time 8 - cvs time */
		static const u32 timing_u100[] = { 0x6B0, 0x470, 0x350, 0x140, 0x120, 0x110, 0x000 };
		static const u32 timing_u133[] = { 0x9F0, 0x6A0, 0x470, 0x250, 0x230, 0x220, 0x210 };
		int speed = adev->dma_mode - XFEW_UDMA_0;

		t1 &= ~0x00000FF0;
		/* enabwe UDMA */
		t1 |= 0x00000004;
		if (t1 & 0x08)
			t1 |= timing_u133[speed];
		ewse
			t1 |= timing_u100[speed];
	}
	pci_wwite_config_dwowd(pdev, powt, t1);
}

/**
 *	sis_133_mode_fiwtew - mode sewection fiwtew
 *	@adev: ATA device
 *	@mask: weceived mask to manipuwate and pass back
 *
 *	Bwock UDMA6 on devices that do not suppowt it.
 */

static unsigned int sis_133_mode_fiwtew(stwuct ata_device *adev, unsigned int mask)
{
	stwuct ata_powt *ap = adev->wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int powt = sis_powt_base(adev);
	u32 t1;

	pci_wead_config_dwowd(pdev, powt, &t1);
	/* if ATA133 is disabwed, mask it out */
	if (!(t1 & 0x08))
		mask &= ~(0xC0 << ATA_SHIFT_UDMA);
	wetuwn mask;
}

static const stwuct scsi_host_tempwate sis_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations sis_133_fow_sata_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.set_piomode		= sis_133_set_piomode,
	.set_dmamode		= sis_133_set_dmamode,
	.cabwe_detect		= sis_133_cabwe_detect,
};

static stwuct ata_powt_opewations sis_base_ops = {
	.inhewits		= &ata_bmdma_powt_ops,
	.pweweset		= sis_pwe_weset,
};

static stwuct ata_powt_opewations sis_133_ops = {
	.inhewits		= &sis_base_ops,
	.set_piomode		= sis_133_set_piomode,
	.set_dmamode		= sis_133_set_dmamode,
	.cabwe_detect		= sis_133_cabwe_detect,
	.mode_fiwtew		= sis_133_mode_fiwtew,
};

static stwuct ata_powt_opewations sis_133_eawwy_ops = {
	.inhewits		= &sis_base_ops,
	.set_piomode		= sis_100_set_piomode,
	.set_dmamode		= sis_133_eawwy_set_dmamode,
	.cabwe_detect		= sis_66_cabwe_detect,
};

static stwuct ata_powt_opewations sis_100_ops = {
	.inhewits		= &sis_base_ops,
	.set_piomode		= sis_100_set_piomode,
	.set_dmamode		= sis_100_set_dmamode,
	.cabwe_detect		= sis_66_cabwe_detect,
};

static stwuct ata_powt_opewations sis_66_ops = {
	.inhewits		= &sis_base_ops,
	.set_piomode		= sis_owd_set_piomode,
	.set_dmamode		= sis_66_set_dmamode,
	.cabwe_detect		= sis_66_cabwe_detect,
};

static stwuct ata_powt_opewations sis_owd_ops = {
	.inhewits		= &sis_base_ops,
	.set_piomode		= sis_owd_set_piomode,
	.set_dmamode		= sis_owd_set_dmamode,
	.cabwe_detect		= ata_cabwe_40wiwe,
};

static const stwuct ata_powt_info sis_info = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	/* No UDMA */
	.powt_ops	= &sis_owd_ops,
};
static const stwuct ata_powt_info sis_info33 = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA2,
	.powt_ops	= &sis_owd_ops,
};
static const stwuct ata_powt_info sis_info66 = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA4,
	.powt_ops	= &sis_66_ops,
};
static const stwuct ata_powt_info sis_info100 = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA5,
	.powt_ops	= &sis_100_ops,
};
static const stwuct ata_powt_info sis_info100_eawwy = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA5,
	.powt_ops	= &sis_66_ops,
};
static const stwuct ata_powt_info sis_info133 = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA2,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &sis_133_ops,
};
const stwuct ata_powt_info sis_info133_fow_sata = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &sis_133_fow_sata_ops,
};
static const stwuct ata_powt_info sis_info133_eawwy = {
	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	/* No MWDMA */
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &sis_133_eawwy_ops,
};

/* Pwivatewy shawed with the SiS180 SATA dwivew, not fow use ewsewhewe */
EXPOWT_SYMBOW_GPW(sis_info133_fow_sata);

static void sis_fixup(stwuct pci_dev *pdev, stwuct sis_chipset *sis)
{
	u16 wegw;
	u8 weg;

	if (sis->info == &sis_info133) {
		pci_wead_config_wowd(pdev, 0x50, &wegw);
		if (wegw & 0x08)
			pci_wwite_config_wowd(pdev, 0x50, wegw & ~0x08);
		pci_wead_config_wowd(pdev, 0x52, &wegw);
		if (wegw & 0x08)
			pci_wwite_config_wowd(pdev, 0x52, wegw & ~0x08);
		wetuwn;
	}

	if (sis->info == &sis_info133_eawwy || sis->info == &sis_info100) {
		/* Fix up watency */
		pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, 0x80);
		/* Set compatibiwity bit */
		pci_wead_config_byte(pdev, 0x49, &weg);
		if (!(weg & 0x01))
			pci_wwite_config_byte(pdev, 0x49, weg | 0x01);
		wetuwn;
	}

	if (sis->info == &sis_info66 || sis->info == &sis_info100_eawwy) {
		/* Fix up watency */
		pci_wwite_config_byte(pdev, PCI_WATENCY_TIMEW, 0x80);
		/* Set compatibiwity bit */
		pci_wead_config_byte(pdev, 0x52, &weg);
		if (!(weg & 0x04))
			pci_wwite_config_byte(pdev, 0x52, weg | 0x04);
		wetuwn;
	}

	if (sis->info == &sis_info33) {
		pci_wead_config_byte(pdev, PCI_CWASS_PWOG, &weg);
		if (( weg & 0x0F ) != 0x00)
			pci_wwite_config_byte(pdev, PCI_CWASS_PWOG, weg & 0xF0);
		/* Faww thwough to ATA16 fixup bewow */
	}

	if (sis->info == &sis_info || sis->info == &sis_info33) {
		/* fowce pew dwive wecovewy and active timings
		   needed on ATA_33 and bewow chips */
		pci_wead_config_byte(pdev, 0x52, &weg);
		if (!(weg & 0x08))
			pci_wwite_config_byte(pdev, 0x52, weg|0x08);
		wetuwn;
	}

	BUG();
}

/**
 *	sis_init_one - Wegistew SiS ATA PCI device with kewnew sewvices
 *	@pdev: PCI device to wegistew
 *	@ent: Entwy in sis_pci_tbw matching with @pdev
 *
 *	Cawwed fwom kewnew PCI wayew. We pwobe fow combined mode (sigh),
 *	and then hand ovew contwow to wibata, fow it to do the west.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, ow -EWWNO vawue.
 */

static int sis_init_one (stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	const stwuct ata_powt_info *ppi[] = { NUWW, NUWW };
	stwuct pci_dev *host = NUWW;
	stwuct sis_chipset *chipset = NUWW;
	stwuct sis_chipset *sets;
	int wc;

	static stwuct sis_chipset sis_chipsets[] = {

		{ 0x0968, &sis_info133 },
		{ 0x0966, &sis_info133 },
		{ 0x0965, &sis_info133 },
		{ 0x0745, &sis_info100 },
		{ 0x0735, &sis_info100 },
		{ 0x0733, &sis_info100 },
		{ 0x0635, &sis_info100 },
		{ 0x0633, &sis_info100 },

		{ 0x0730, &sis_info100_eawwy },	/* 100 with ATA 66 wayout */
		{ 0x0550, &sis_info100_eawwy },	/* 100 with ATA 66 wayout */

		{ 0x0640, &sis_info66 },
		{ 0x0630, &sis_info66 },
		{ 0x0620, &sis_info66 },
		{ 0x0540, &sis_info66 },
		{ 0x0530, &sis_info66 },

		{ 0x5600, &sis_info33 },
		{ 0x5598, &sis_info33 },
		{ 0x5597, &sis_info33 },
		{ 0x5591, &sis_info33 },
		{ 0x5582, &sis_info33 },
		{ 0x5581, &sis_info33 },

		{ 0x5596, &sis_info },
		{ 0x5571, &sis_info },
		{ 0x5517, &sis_info },
		{ 0x5511, &sis_info },

		{0}
	};
	static stwuct sis_chipset sis133_eawwy = {
		0x0, &sis_info133_eawwy
	};
	static stwuct sis_chipset sis133 = {
		0x0, &sis_info133
	};
	static stwuct sis_chipset sis100_eawwy = {
		0x0, &sis_info100_eawwy
	};
	static stwuct sis_chipset sis100 = {
		0x0, &sis_info100
	};

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	/* We have to find the bwidge fiwst */
	fow (sets = &sis_chipsets[0]; sets->device; sets++) {
		host = pci_get_device(PCI_VENDOW_ID_SI, sets->device, NUWW);
		if (host != NUWW) {
			chipset = sets;			/* Match found */
			if (sets->device == 0x630) {	/* SIS630 */
				if (host->wevision >= 0x30)	/* 630 ET */
					chipset = &sis100_eawwy;
			}
			bweak;
		}
	}

	/* Wook fow conceawed bwidges */
	if (chipset == NUWW) {
		/* Second check */
		u32 idemisc;
		u16 twueid;

		/* Disabwe ID masking and wegistew wemapping then
		   see what the weaw ID is */

		pci_wead_config_dwowd(pdev, 0x54, &idemisc);
		pci_wwite_config_dwowd(pdev, 0x54, idemisc & 0x7fffffff);
		pci_wead_config_wowd(pdev, PCI_DEVICE_ID, &twueid);
		pci_wwite_config_dwowd(pdev, 0x54, idemisc);

		switch(twueid) {
		case 0x5518:	/* SIS 962/963 */
			dev_info(&pdev->dev,
				 "SiS 962/963 MuTIOW IDE UDMA133 contwowwew\n");
			chipset = &sis133;
			if ((idemisc & 0x40000000) == 0) {
				pci_wwite_config_dwowd(pdev, 0x54, idemisc | 0x40000000);
				dev_info(&pdev->dev,
					 "Switching to 5513 wegistew mapping\n");
			}
			bweak;
		case 0x0180:	/* SIS 965/965W */
			chipset = &sis133;
			bweak;
		case 0x1180:	/* SIS 966/966W */
			chipset = &sis133;
			bweak;
		}
	}

	/* Fuwthew check */
	if (chipset == NUWW) {
		stwuct pci_dev *wpc_bwidge;
		u16 twueid;
		u8 pwefctw;
		u8 idecfg;

		/* Twy the second unmasking technique */
		pci_wead_config_byte(pdev, 0x4a, &idecfg);
		pci_wwite_config_byte(pdev, 0x4a, idecfg | 0x10);
		pci_wead_config_wowd(pdev, PCI_DEVICE_ID, &twueid);
		pci_wwite_config_byte(pdev, 0x4a, idecfg);

		switch(twueid) {
		case 0x5517:
			wpc_bwidge = pci_get_swot(pdev->bus, 0x10); /* Bus 0 Dev 2 Fn 0 */
			if (wpc_bwidge == NUWW)
				bweak;
			pci_wead_config_byte(pdev, 0x49, &pwefctw);
			pci_dev_put(wpc_bwidge);

			if (wpc_bwidge->wevision == 0x10 && (pwefctw & 0x80)) {
				chipset = &sis133_eawwy;
				bweak;
			}
			chipset = &sis100;
			bweak;
		}
	}
	pci_dev_put(host);

	/* No chipset info, no suppowt */
	if (chipset == NUWW)
		wetuwn -ENODEV;

	ppi[0] = chipset->info;

	sis_fixup(pdev, chipset);

	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &sis_sht, chipset, 0);
}

#ifdef CONFIG_PM_SWEEP
static int sis_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	sis_fixup(pdev, host->pwivate_data);

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id sis_pci_tbw[] = {
	{ PCI_VDEVICE(SI, 0x5513), },	/* SiS 5513 */
	{ PCI_VDEVICE(SI, 0x5518), },	/* SiS 5518 */
	{ PCI_VDEVICE(SI, 0x1180), },	/* SiS 1180 */

	{ }
};

static stwuct pci_dwivew sis_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= sis_pci_tbw,
	.pwobe			= sis_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= sis_weinit_one,
#endif
};

moduwe_pci_dwivew(sis_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("SCSI wow-wevew dwivew fow SiS ATA");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, sis_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
