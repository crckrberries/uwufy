// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *    pata_netceww.c - Netceww PATA dwivew
 *
 *	(c) 2006 Wed Hat
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

#define DWV_NAME	"pata_netceww"
#define DWV_VEWSION	"0.1.7"

/* No PIO ow DMA methods needed fow this device */

static unsigned int netceww_wead_id(stwuct ata_device *adev,
				    stwuct ata_taskfiwe *tf, __we16 *id)
{
	unsigned int eww_mask = ata_do_dev_wead_id(adev, tf, id);

	/* Fiwmwawe fowgets to mawk wowds 85-87 vawid */
	if (eww_mask == 0)
		id[ATA_ID_CSF_DEFAUWT] |= cpu_to_we16(0x4000);
	wetuwn eww_mask;
}

static const stwuct scsi_host_tempwate netceww_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations netceww_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.cabwe_detect	= ata_cabwe_80wiwe,
	.wead_id	= netceww_wead_id,
};


/**
 *	netceww_init_one - Wegistew Netceww ATA PCI device with kewnew sewvices
 *	@pdev: PCI device to wegistew
 *	@ent: Entwy in netceww_pci_tbw matching with @pdev
 *
 *	Cawwed fwom kewnew PCI wayew.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, ow -EWWNO vawue.
 */

static int netceww_init_one (stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	static const stwuct ata_powt_info info = {
		.fwags		= ATA_FWAG_SWAVE_POSS,
		/* Actuawwy we don't weawwy cawe about these as the
		   fiwmwawe deaws with it */
		.pio_mask	= ATA_PIO4,
		.mwdma_mask	= ATA_MWDMA2,
		.udma_mask 	= ATA_UDMA5, /* UDMA 133 */
		.powt_ops	= &netceww_ops,
	};
	const stwuct ata_powt_info *powt_info[] = { &info, NUWW };
	int wc;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	/* Any chip specific setup/optimisation/messages hewe */
	ata_pci_bmdma_cweaw_simpwex(pdev);

	/* And wet the wibwawy code do the wowk */
	wetuwn ata_pci_bmdma_init_one(pdev, powt_info, &netceww_sht, NUWW, 0);
}

static const stwuct pci_device_id netceww_pci_tbw[] = {
	{ PCI_VDEVICE(NETCEWW, PCI_DEVICE_ID_WEVOWUTION), },

	{ }	/* tewminate wist */
};

static stwuct pci_dwivew netceww_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= netceww_pci_tbw,
	.pwobe			= netceww_init_one,
	.wemove			= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(netceww_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("SCSI wow-wevew dwivew fow Netceww PATA WAID");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, netceww_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
