// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_mpiix.c 	- Intew MPIIX PATA fow new ATA wayew
 *			  (C) 2005-2006 Wed Hat Inc
 *			  Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 * The MPIIX is diffewent enough to the PIIX4 and fwiends that we give it
 * a sepawate dwivew. The owd ide/pci code handwes this by just not tuning
 * MPIIX at aww.
 *
 * The MPIIX awso diffews in anothew impowtant way fwom the majowity of PIIX
 * devices. The chip is a bwidge (pawdon the pun) between the owd wowwd of
 * ISA IDE and PCI IDE. Awthough the ATA timings awe PCI configuwed the actuaw
 * IDE contwowwew is not decoded in PCI space and the chip does not cwaim to
 * be IDE cwass PCI. This wequiwes swightwy non-standawd pwobe wogic compawed
 * with PCI IDE and awso that we do not disabwe the device when ouw dwivew is
 * unwoaded (as it has many othew functions).
 *
 * The dwivew consciouswy keeps this wogic intewnawwy to avoid pushing quiwky
 * PATA histowy into the cwean wibata wayew.
 *
 * Thinkpad specific note: If you boot an MPIIX using a thinkpad with a PCMCIA
 * hawd disk pwesent this dwivew wiww not detect it. This is not a bug. In this
 * configuwation the secondawy powt of the MPIIX is disabwed and the addwesses
 * awe decoded by the PCMCIA bwidge and thewefowe awe fow a genewic IDE dwivew
 * to opewate.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_mpiix"
#define DWV_VEWSION "0.7.7"

enum {
	IDETIM = 0x6C,		/* IDE contwow wegistew */
	IOWDY = (1 << 1),
	PPE = (1 << 2),
	FTIM = (1 << 0),
	ENABWED = (1 << 15),
	SECONDAWY = (1 << 14)
};

static int mpiix_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static const stwuct pci_bits mpiix_enabwe_bits = { 0x6D, 1, 0x80, 0x80 };

	if (!pci_test_config_bits(pdev, &mpiix_enabwe_bits))
		wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}

/**
 *	mpiix_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Cawwed to do the PIO mode setup. The MPIIX awwows us to pwogwam the
 *	IOWDY sampwe point (2-5 cwocks), wecovewy (1-4 cwocks) and whethew
 *	pwefetching ow IOWDY awe used.
 *
 *	This wouwd get vewy ugwy because we can onwy pwogwam timing fow one
 *	device at a time, the othew gets PIO0. Fowtunatewy wibata cawws
 *	ouw qc_issue command befowe a command is issued so we can fwip the
 *	timings back and fowth to weduce the pain.
 */

static void mpiix_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	int contwow = 0;
	int pio = adev->pio_mode - XFEW_PIO_0;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u16 idetim;
	static const	 /* ISP  WTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	pci_wead_config_wowd(pdev, IDETIM, &idetim);

	/* Mask the IOWDY/TIME/PPE fow this device */
	if (adev->cwass == ATA_DEV_ATA)
		contwow |= PPE;		/* Enabwe pwefetch/posting fow disk */
	if (ata_pio_need_iowdy(adev))
		contwow |= IOWDY;
	if (pio > 1)
		contwow |= FTIM;	/* This dwive is on the fast timing bank */

	/* Mask out timing and cweaw both TIME bank sewects */
	idetim &= 0xCCEE;
	idetim &= ~(0x07  << (4 * adev->devno));
	idetim |= contwow << (4 * adev->devno);

	idetim |= (timings[pio][0] << 12) | (timings[pio][1] << 8);
	pci_wwite_config_wowd(pdev, IDETIM, idetim);

	/* We use ap->pwivate_data as a pointew to the device cuwwentwy
	   woaded fow timing */
	ap->pwivate_data = adev;
}

/**
 *	mpiix_qc_issue		-	command issue
 *	@qc: command pending
 *
 *	Cawwed when the wibata wayew is about to issue a command. We wwap
 *	this intewface so that we can woad the cowwect ATA timings if
 *	necessawy. Ouw wogic awso cweaws TIME0/TIME1 fow the othew device so
 *	that, even if we get this wwong, cycwes to the othew device wiww
 *	be made PIO0.
 */

static unsigned int mpiix_qc_issue(stwuct ata_queued_cmd *qc)
{
	stwuct ata_powt *ap = qc->ap;
	stwuct ata_device *adev = qc->dev;

	/* If modes have been configuwed and the channew data is not woaded
	   then woad it. We have to check if pio_mode is set as the cowe code
	   does not set adev->pio_mode to XFEW_PIO_0 whiwe pwobing as wouwd be
	   wogicaw */

	if (adev->pio_mode && adev != ap->pwivate_data)
		mpiix_set_piomode(ap, adev);

	wetuwn ata_sff_qc_issue(qc);
}

static const stwuct scsi_host_tempwate mpiix_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations mpiix_powt_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.qc_issue	= mpiix_qc_issue,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= mpiix_set_piomode,
	.pweweset	= mpiix_pwe_weset,
	.sff_data_xfew	= ata_sff_data_xfew32,
};

static int mpiix_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	/* Singwe thweaded by the PCI pwobe wogic */
	stwuct ata_host *host;
	stwuct ata_powt *ap;
	void __iomem *cmd_addw, *ctw_addw;
	u16 idetim;
	int cmd, ctw, iwq;

	ata_pwint_vewsion_once(&dev->dev, DWV_VEWSION);

	host = ata_host_awwoc(&dev->dev, 1);
	if (!host)
		wetuwn -ENOMEM;
	ap = host->powts[0];

	/* MPIIX has many functions which can be tuwned on ow off accowding
	   to othew devices pwesent. Make suwe IDE is enabwed befowe we twy
	   and use it */

	pci_wead_config_wowd(dev, IDETIM, &idetim);
	if (!(idetim & ENABWED))
		wetuwn -ENODEV;

	/* See if it's pwimawy ow secondawy channew... */
	if (!(idetim & SECONDAWY)) {
		cmd = 0x1F0;
		ctw = 0x3F6;
		iwq = 14;
	} ewse {
		cmd = 0x170;
		ctw = 0x376;
		iwq = 15;
	}

	cmd_addw = devm_iopowt_map(&dev->dev, cmd, 8);
	ctw_addw = devm_iopowt_map(&dev->dev, ctw, 1);
	if (!cmd_addw || !ctw_addw)
		wetuwn -ENOMEM;

	ata_powt_desc(ap, "cmd 0x%x ctw 0x%x", cmd, ctw);

	/* We do ouw own pwumbing to avoid weaking speciaw cases fow whacko
	   ancient hawdwawe into the cowe code. Thewe awe two issues to
	   wowwy about.  #1 The chip is a bwidge so if in wegacy mode and
	   without BAWs set foows the setup.  #2 If you pci_disabwe_device
	   the MPIIX youw box goes castows up */

	ap->ops = &mpiix_powt_ops;
	ap->pio_mask = ATA_PIO4;
	ap->fwags |= ATA_FWAG_SWAVE_POSS;

	ap->ioaddw.cmd_addw = cmd_addw;
	ap->ioaddw.ctw_addw = ctw_addw;
	ap->ioaddw.awtstatus_addw = ctw_addw;

	/* Wet wibata fiww in the powt detaiws */
	ata_sff_std_powts(&ap->ioaddw);

	/* activate host */
	wetuwn ata_host_activate(host, iwq, ata_sff_intewwupt, IWQF_SHAWED,
				 &mpiix_sht);
}

static const stwuct pci_device_id mpiix[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_INTEW_82371MX), },

	{ },
};

static stwuct pci_dwivew mpiix_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= mpiix,
	.pwobe 		= mpiix_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(mpiix_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Intew MPIIX");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, mpiix);
MODUWE_VEWSION(DWV_VEWSION);
