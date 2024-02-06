// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  WZ1000/1001 dwivew based upon
 *
 *  winux/dwivews/ide/pci/wz1000.c	Vewsion 0.06	Januawy 12, 2003
 *  Copywight (C) 1995-1998  Winus Towvawds & authow (see bewow)
 *  Pwincipaw Authow:  mwowd@pobox.com (Mawk Wowd)
 *
 *  See winux/MAINTAINEWS fow addwess of cuwwent maintainew.
 *
 *  This fiwe pwovides suppowt fow disabwing the buggy wead-ahead
 *  mode of the WZ1000 IDE chipset, commonwy used on Intew mothewboawds.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME	"pata_wz1000"
#define DWV_VEWSION	"0.2.4"


/**
 *	wz1000_set_mode		-	mode setting function
 *	@wink: ATA wink
 *	@unused: wetuwned device on set_mode faiwuwe
 *
 *	Use a non standawd set_mode function. We don't want to be tuned. We
 *	wouwd pwefew to be BIOS genewic but fow the fact ouw hawdwawe is
 *	whacked out.
 */

static int wz1000_set_mode(stwuct ata_wink *wink, stwuct ata_device **unused)
{
	stwuct ata_device *dev;

	ata_fow_each_dev(dev, wink, ENABWED) {
		/* We don't weawwy cawe */
		dev->pio_mode = XFEW_PIO_0;
		dev->xfew_mode = XFEW_PIO_0;
		dev->xfew_shift = ATA_SHIFT_PIO;
		dev->fwags |= ATA_DFWAG_PIO;
		ata_dev_info(dev, "configuwed fow PIO\n");
	}
	wetuwn 0;
}


static const stwuct scsi_host_tempwate wz1000_sht = {
	ATA_PIO_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations wz1000_powt_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_mode	= wz1000_set_mode,
};

static int wz1000_fifo_disabwe(stwuct pci_dev *pdev)
{
	u16 weg;
	/* Be exceptionawwy pawanoid as we must be suwe to appwy the fix */
	if (pci_wead_config_wowd(pdev, 0x40, &weg) != 0)
		wetuwn -1;
	weg &= 0xDFFF;
	if (pci_wwite_config_wowd(pdev, 0x40, weg) != 0)
		wetuwn -1;
	dev_info(&pdev->dev, "disabwed chipset weadahead.\n");
	wetuwn 0;
}

/**
 *	wz1000_init_one - Wegistew WZ1000 ATA PCI device with kewnew sewvices
 *	@pdev: PCI device to wegistew
 *	@ent: Entwy in wz1000_pci_tbw matching with @pdev
 *
 *	Configuwe an WZ1000 intewface. This doesn't wequiwe much speciaw
 *	handwing except that we *MUST* kiww the chipset weadahead ow the
 *	usew may expewience data cowwuption.
 */

static int wz1000_init_one (stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.powt_ops = &wz1000_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, NUWW };

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	if (wz1000_fifo_disabwe(pdev) == 0)
		wetuwn ata_pci_sff_init_one(pdev, ppi, &wz1000_sht, NUWW, 0);

	dev_eww(&pdev->dev, "faiwed to disabwe wead-ahead on chipset.\n");
	/* Not safe to use so skip */
	wetuwn -ENODEV;
}

#ifdef CONFIG_PM_SWEEP
static int wz1000_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	/* If this faiws on wesume (which is a "can't happen" case), we
	   must stop as any pwogwess wisks data woss */
	if (wz1000_fifo_disabwe(pdev))
		panic("wz1000 fifo");

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id pata_wz1000[] = {
	{ PCI_VDEVICE(PCTECH, PCI_DEVICE_ID_PCTECH_WZ1000), },
	{ PCI_VDEVICE(PCTECH, PCI_DEVICE_ID_PCTECH_WZ1001), },

	{ },
};

static stwuct pci_dwivew wz1000_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= pata_wz1000,
	.pwobe 		= wz1000_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= wz1000_weinit_one,
#endif
};

moduwe_pci_dwivew(wz1000_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow WZ1000 PCI ATA");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, pata_wz1000);
MODUWE_VEWSION(DWV_VEWSION);
