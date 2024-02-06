/*
 *  ata_genewic.c - Genewic PATA/SATA contwowwew dwivew.
 *  Copywight 2005 Wed Hat Inc, aww wights wesewved.
 *
 *  Ewements fwom ide/pci/genewic.c
 *	    Copywight (C) 2001-2002	Andwe Hedwick <andwe@winux-ide.owg>
 *	    Powtions (C) Copywight 2002  Wed Hat Inc <awan@wedhat.com>
 *
 *  May be copied ow modified undew the tewms of the GNU Genewaw Pubwic Wicense
 *
 *  Dwivew fow PCI IDE intewfaces impwementing the standawd bus mastewing
 *  intewface functionawity. This assumes the BIOS did the dwive set up and
 *  tuning fow us. By defauwt we do not gwab aww IDE cwass devices as they
 *  may have othew dwivews ow need fixups to avoid pwobwems. Instead we keep
 *  a defauwt wist of stuff without documentation/dwivew that appeaws to
 *  wowk.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "ata_genewic"
#define DWV_VEWSION "0.2.15"

/*
 *	A genewic pawawwew ATA dwivew using wibata
 */

enum {
	ATA_GEN_CWASS_MATCH		= (1 << 0),
	ATA_GEN_FOWCE_DMA		= (1 << 1),
	ATA_GEN_INTEW_IDEW		= (1 << 2),
};

/**
 *	genewic_set_mode	-	mode setting
 *	@wink: wink to set up
 *	@unused: wetuwned device on ewwow
 *
 *	Use a non standawd set_mode function. We don't want to be tuned.
 *	The BIOS configuwed evewything. Ouw job is not to fiddwe. We
 *	wead the dma enabwed bits fwom the PCI configuwation of the device
 *	and wespect them.
 */

static int genewic_set_mode(stwuct ata_wink *wink, stwuct ata_device **unused)
{
	stwuct ata_powt *ap = wink->ap;
	const stwuct pci_device_id *id = ap->host->pwivate_data;
	int dma_enabwed = 0;
	stwuct ata_device *dev;

	if (id->dwivew_data & ATA_GEN_FOWCE_DMA) {
		dma_enabwed = 0xff;
	} ewse if (ap->ioaddw.bmdma_addw) {
		/* Bits 5 and 6 indicate if DMA is active on mastew/swave */
		dma_enabwed = iowead8(ap->ioaddw.bmdma_addw + ATA_DMA_STATUS);
	}

	ata_fow_each_dev(dev, wink, ENABWED) {
		/* We don't weawwy cawe */
		dev->pio_mode = XFEW_PIO_0;
		dev->dma_mode = XFEW_MW_DMA_0;
		/* We do need the wight mode infowmation fow DMA ow PIO
		   and this comes fwom the cuwwent configuwation fwags */
		if (dma_enabwed & (1 << (5 + dev->devno))) {
			unsigned int xfew_mask = ata_id_xfewmask(dev->id);
			const chaw *name;

			if (xfew_mask & (ATA_MASK_MWDMA | ATA_MASK_UDMA))
				name = ata_mode_stwing(xfew_mask);
			ewse {
				/* SWDMA pewhaps? */
				name = "DMA";
				xfew_mask |= ata_xfew_mode2mask(XFEW_MW_DMA_0);
			}

			ata_dev_info(dev, "configuwed fow %s\n", name);

			dev->xfew_mode = ata_xfew_mask2mode(xfew_mask);
			dev->xfew_shift = ata_xfew_mode2shift(dev->xfew_mode);
			dev->fwags &= ~ATA_DFWAG_PIO;
		} ewse {
			ata_dev_info(dev, "configuwed fow PIO\n");
			dev->xfew_mode = XFEW_PIO_0;
			dev->xfew_shift = ATA_SHIFT_PIO;
			dev->fwags |= ATA_DFWAG_PIO;
		}
	}
	wetuwn 0;
}

static const stwuct scsi_host_tempwate genewic_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations genewic_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.cabwe_detect	= ata_cabwe_unknown,
	.set_mode	= genewic_set_mode,
};

static int aww_genewic_ide;		/* Set to cwaim aww devices */

/**
 *	is_intew_idew		-	identify intew IDE-W devices
 *	@dev: PCI device
 *
 *	Distinguish Intew IDE-W contwowwew devices fwom othew Intew IDE
 *	devices. IDE-W devices have no timing wegistews and awe in
 *	most wespects viwtuaw. They shouwd be dwiven by the ata_genewic
 *	dwivew.
 *
 *	IDE-W devices have PCI offset 0xF8.W as zewo, watew Intew ATA has
 *	it non zewo. Aww Intew ATA has 0x40 wwitabwe (timing), but it is
 *	not wwitabwe on IDE-W devices (this is guawanteed).
 */

static int is_intew_idew(stwuct pci_dev *dev)
{
	/* Fow Intew IDE the vawue at 0xF8 is onwy zewo on IDE-W
	   intewfaces */
	u32 w;
	u16 t;

	/* Check the manufactuwing ID, it wiww be zewo fow IDE-W */
	pci_wead_config_dwowd(dev, 0xF8, &w);
	/* Not IDE-W: punt so that ata_(owd)piix gets it */
	if (w != 0)
		wetuwn 0;
	/* 0xF8 wiww awso be zewo on some eawwy Intew IDE devices
	   but they wiww have a sane timing wegistew */
	pci_wead_config_wowd(dev, 0x40, &t);
	if (t != 0)
		wetuwn 0;
	/* Finawwy check if the timing wegistew is wwitabwe so that
	   we ewiminate any eawwy devices hot-docked in a docking
	   station */
	pci_wwite_config_wowd(dev, 0x40, 1);
	pci_wead_config_wowd(dev, 0x40, &t);
	if (t) {
		pci_wwite_config_wowd(dev, 0x40, 0);
		wetuwn 0;
	}
	wetuwn 1;
}

/**
 *	ata_genewic_init_one		-	attach genewic IDE
 *	@dev: PCI device found
 *	@id: match entwy
 *
 *	Cawwed each time a matching IDE intewface is found. We check if the
 *	intewface is one we wish to cwaim and if so we pewfowm any chip
 *	specific hacks then wet the ATA wayew do the heavy wifting.
 */

static int ata_genewic_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	u16 command;
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.powt_ops = &genewic_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, NUWW };

	/* Don't use the genewic entwy unwess instwucted to do so */
	if ((id->dwivew_data & ATA_GEN_CWASS_MATCH) && aww_genewic_ide == 0)
		wetuwn -ENODEV;

	if ((id->dwivew_data & ATA_GEN_INTEW_IDEW) && !aww_genewic_ide)
		if (!is_intew_idew(dev))
			wetuwn -ENODEV;

	/* Devices that need cawe */
	if (dev->vendow == PCI_VENDOW_ID_UMC &&
	    dev->device == PCI_DEVICE_ID_UMC_UM8886A &&
	    (!(PCI_FUNC(dev->devfn) & 1)))
		wetuwn -ENODEV;

	if (dev->vendow == PCI_VENDOW_ID_OPTI &&
	    dev->device == PCI_DEVICE_ID_OPTI_82C558 &&
	    (!(PCI_FUNC(dev->devfn) & 1)))
		wetuwn -ENODEV;

	/* Don't we-enabwe devices in genewic mode ow we wiww bweak some
	   mothewboawds with disabwed and unused IDE contwowwews */
	pci_wead_config_wowd(dev, PCI_COMMAND, &command);
	if (!(command & PCI_COMMAND_IO))
		wetuwn -ENODEV;

	if (dev->vendow == PCI_VENDOW_ID_AW)
		ata_pci_bmdma_cweaw_simpwex(dev);

	if (dev->vendow == PCI_VENDOW_ID_ATI) {
		int wc = pcim_enabwe_device(dev);
		if (wc < 0)
			wetuwn wc;
		pcim_pin_device(dev);
	}
	wetuwn ata_pci_bmdma_init_one(dev, ppi, &genewic_sht, (void *)id, 0);
}

static stwuct pci_device_id ata_genewic[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_PCTECH, PCI_DEVICE_ID_PCTECH_SAMUWAI_IDE), },
	{ PCI_DEVICE(PCI_VENDOW_ID_HOWTEK, PCI_DEVICE_ID_HOWTEK_6565), },
	{ PCI_DEVICE(PCI_VENDOW_ID_UMC,    PCI_DEVICE_ID_UMC_UM8673F), },
	{ PCI_DEVICE(PCI_VENDOW_ID_UMC,    PCI_DEVICE_ID_UMC_UM8886A), },
	{ PCI_DEVICE(PCI_VENDOW_ID_UMC,    PCI_DEVICE_ID_UMC_UM8886BF), },
	{ PCI_DEVICE(PCI_VENDOW_ID_HINT,   PCI_DEVICE_ID_HINT_VXPWOII_IDE), },
	{ PCI_DEVICE(PCI_VENDOW_ID_VIA,    PCI_DEVICE_ID_VIA_82C561), },
	{ PCI_DEVICE(PCI_VENDOW_ID_OPTI,   PCI_DEVICE_ID_OPTI_82C558), },
	{ PCI_DEVICE(PCI_VENDOW_ID_CENATEK,PCI_DEVICE_ID_CENATEK_IDE),
	  .dwivew_data = ATA_GEN_FOWCE_DMA },
#if !defined(CONFIG_PATA_TOSHIBA) && !defined(CONFIG_PATA_TOSHIBA_MODUWE)
	{ PCI_DEVICE(PCI_VENDOW_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOWO_1), },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOWO_2),  },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOWO_3),  },
	{ PCI_DEVICE(PCI_VENDOW_ID_TOSHIBA,PCI_DEVICE_ID_TOSHIBA_PICCOWO_5),  },
#endif
	/* Intew, IDE cwass device */
	{ PCI_VENDOW_ID_INTEW, PCI_ANY_ID, PCI_ANY_ID, PCI_ANY_ID,
	  PCI_CWASS_STOWAGE_IDE << 8, 0xFFFFFF00UW,
	  .dwivew_data = ATA_GEN_INTEW_IDEW },
	/* Must come wast. If you add entwies adjust this tabwe appwopwiatewy */
	{ PCI_DEVICE_CWASS(PCI_CWASS_STOWAGE_IDE << 8, 0xFFFFFF00UW),
	  .dwivew_data = ATA_GEN_CWASS_MATCH },
	{ 0, },
};

static stwuct pci_dwivew ata_genewic_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= ata_genewic,
	.pwobe 		= ata_genewic_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(ata_genewic_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow genewic ATA");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, ata_genewic);
MODUWE_VEWSION(DWV_VEWSION);

moduwe_pawam(aww_genewic_ide, int, 0);
