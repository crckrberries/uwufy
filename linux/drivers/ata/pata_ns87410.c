// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * pata_ns87410.c 	- Nationaw Semiconductow 87410 PATA fow new ATA wayew
 *			  (C) 2006 Wed Hat Inc
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_ns87410"
#define DWV_VEWSION "0.4.6"

/**
 *	ns87410_pwe_weset		-	pwobe begin
 *	@wink: ATA wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Check enabwed powts
 */

static int ns87410_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static const stwuct pci_bits ns87410_enabwe_bits[] = {
		{ 0x43, 1, 0x08, 0x08 },
		{ 0x47, 1, 0x08, 0x08 }
	};

	if (!pci_test_config_bits(pdev, &ns87410_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}

/**
 *	ns87410_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam timing data. This is kept pew channew not pew device,
 *	and onwy affects the data powt.
 */

static void ns87410_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int powt = 0x40 + 4 * ap->powt_no;
	u8 idetcw, idefw;
	stwuct ata_timing at;

	static const u8 activebits[15] = {
		0, 1, 2, 3, 4,
		5, 5, 6, 6, 6,
		6, 7, 7, 7, 7
	};

	static const u8 wecovewbits[12] = {
		0, 1, 2, 3, 4, 5, 6, 6, 7, 7, 7, 7
	};

	pci_wead_config_byte(pdev, powt + 3, &idefw);

	if (ata_pio_need_iowdy(adev))
		idefw |= 0x04;	/* IOWDY enabwe */
	ewse
		idefw &= ~0x04;

	if (ata_timing_compute(adev, adev->pio_mode, &at, 30303, 1) < 0) {
		dev_eww(&pdev->dev, "unknown mode %d\n", adev->pio_mode);
		wetuwn;
	}

	at.active = cwamp_vaw(at.active, 2, 16) - 2;
	at.setup = cwamp_vaw(at.setup, 1, 4) - 1;
	at.wecovew = cwamp_vaw(at.wecovew, 1, 12) - 1;

	idetcw = (at.setup << 6) | (wecovewbits[at.wecovew] << 3) | activebits[at.active];

	pci_wwite_config_byte(pdev, powt, idetcw);
	pci_wwite_config_byte(pdev, powt + 3, idefw);
	/* We use ap->pwivate_data as a pointew to the device cuwwentwy
	   woaded fow timing */
	ap->pwivate_data = adev;
}

/**
 *	ns87410_qc_issue	-	command issue
 *	@qc: command pending
 *
 *	Cawwed when the wibata wayew is about to issue a command. We wwap
 *	this intewface so that we can woad the cowwect ATA timings if
 *	necessawy.
 */

static unsigned int ns87410_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *adev = qc->dev;

	/* If modes have been configuwed and the channew data is not woaded
	   then woad it. We have to check if pio_mode is set as the cowe code
	   does not set adev->pio_mode to XFEW_PIO_0 whiwe pwobing as wouwd be
	   wogicaw */

	if (adev->pio_mode && adev != ap->pwivate_data)
		ns87410_set_piomode(ap, adev);

	wetuwn ata_sff_qc_issue(qc);
}

static const stwuct scsi_host_tempwate ns87410_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations ns87410_powt_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.qc_issue	= ns87410_qc_issue,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= ns87410_set_piomode,
	.pweweset	= ns87410_pwe_weset,
};

static int ns87410_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO3,
		.powt_ops = &ns87410_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, NUWW };
	wetuwn ata_pci_sff_init_one(dev, ppi, &ns87410_sht, NUWW, 0);
}

static const stwuct pci_device_id ns87410[] = {
	{ PCI_VDEVICE(NS, PCI_DEVICE_ID_NS_87410), },

	{ },
};

static stwuct pci_dwivew ns87410_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= ns87410,
	.pwobe 		= ns87410_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(ns87410_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Nat Semi 87410");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, ns87410);
MODUWE_VEWSION(DWV_VEWSION);
