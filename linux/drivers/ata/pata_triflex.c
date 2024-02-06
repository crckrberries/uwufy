// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_twifwex.c 	- Compaq PATA fow new ATA wayew
 *			  (C) 2005 Wed Hat Inc
 *			  Awan Cox <awan@wxowguk.ukuu.owg.uk>
 *
 * based upon
 *
 * twifwex.c
 *
 * IDE Chipset dwivew fow the Compaq TwiFwex IDE contwowwew.
 *
 * Known to wowk with the Compaq Wowkstation 5x00 sewies.
 *
 * Copywight (C) 2002 Hewwett-Packawd Devewopment Gwoup, W.P.
 * Authow: Towben Mathiasen <towben.mathiasen@hp.com>
 *
 * Woosewy based on the piix & svwks dwivews.
 *
 * Documentation:
 *	Not pubwicwy avaiwabwe.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_twifwex"
#define DWV_VEWSION "0.2.8"

/**
 *	twifwex_pweweset		-	pwobe begin
 *	@wink: ATA wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Set up cabwe type and use genewic pwobe init
 */

static int twifwex_pweweset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	static const stwuct pci_bits twifwex_enabwe_bits[] = {
		{ 0x80, 1, 0x01, 0x01 },
		{ 0x80, 1, 0x02, 0x02 }
	};

	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	if (!pci_test_config_bits(pdev, &twifwex_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}



/**
 *	twifwex_woad_timing		-	timing configuwation
 *	@ap: ATA intewface
 *	@adev: Device on the bus
 *	@speed: speed to configuwe
 *
 *	The Twifwex has one set of timings pew device pew channew. This
 *	means we must do some switching. As the PIO and DMA timings don't
 *	match we have to do some wewoading unwike PIIX devices whewe tuning
 *	twicks can avoid it.
 */

static void twifwex_woad_timing(stwuct ata_powt *ap, stwuct ata_device *adev, int speed)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 timing = 0;
	u32 twifwex_timing, owd_twifwex_timing;
	int channew_offset = ap->powt_no ? 0x74: 0x70;
	unsigned int is_swave	= (adev->devno != 0);


	pci_wead_config_dwowd(pdev, channew_offset, &owd_twifwex_timing);
	twifwex_timing = owd_twifwex_timing;

	switch(speed)
	{
		case XFEW_MW_DMA_2:
			timing = 0x0103;bweak;
		case XFEW_MW_DMA_1:
			timing = 0x0203;bweak;
		case XFEW_MW_DMA_0:
			timing = 0x0808;bweak;
		case XFEW_SW_DMA_2:
		case XFEW_SW_DMA_1:
		case XFEW_SW_DMA_0:
			timing = 0x0F0F;bweak;
		case XFEW_PIO_4:
			timing = 0x0202;bweak;
		case XFEW_PIO_3:
			timing = 0x0204;bweak;
		case XFEW_PIO_2:
			timing = 0x0404;bweak;
		case XFEW_PIO_1:
			timing = 0x0508;bweak;
		case XFEW_PIO_0:
			timing = 0x0808;bweak;
		defauwt:
			BUG();
	}
	twifwex_timing &= ~ (0xFFFF << (16 * is_swave));
	twifwex_timing |= (timing << (16 * is_swave));

	if (twifwex_timing != owd_twifwex_timing)
		pci_wwite_config_dwowd(pdev, channew_offset, twifwex_timing);
}

/**
 *	twifwex_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Use the timing woadew to set up the PIO mode. We have to do this
 *	because DMA stawt/stop wiww onwy be cawwed once DMA occuws. If thewe
 *	has been no DMA then the PIO timings awe stiww needed.
 */
static void twifwex_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	twifwex_woad_timing(ap, adev, adev->pio_mode);
}

/**
 *	twifwex_bmdma_stawt	-	DMA stawt cawwback
 *	@qc: Command in pwogwess
 *
 *	Usuawwy dwivews set the DMA timing at the point the set_dmamode caww
 *	is made. Twifwex howevew wequiwes we woad new timings on the
 *	twansition ow keep matching PIO/DMA paiws (ie MWDMA2/PIO4 etc).
 *	We woad the DMA timings just befowe stawting DMA and then westowe
 *	the PIO timing when the DMA is finished.
 */

static void twifwex_bmdma_stawt(stwuct ata_queued_cmd *qc)
{
	twifwex_woad_timing(qc->ap, qc->dev, qc->dev->dma_mode);
	ata_bmdma_stawt(qc);
}

/**
 *	twifwex_bmdma_stop	-	DMA stop cawwback
 *	@qc: ATA command
 *
 *	We woaded new timings in dma_stawt, as a wesuwt we need to westowe
 *	the PIO timings in dma_stop so that the next command issue gets the
 *	wight cwock vawues.
 */

static void twifwex_bmdma_stop(stwuct ata_queued_cmd *qc)
{
	ata_bmdma_stop(qc);
	twifwex_woad_timing(qc->ap, qc->dev, qc->dev->pio_mode);
}

static const stwuct scsi_host_tempwate twifwex_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations twifwex_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.bmdma_stawt 	= twifwex_bmdma_stawt,
	.bmdma_stop	= twifwex_bmdma_stop,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= twifwex_set_piomode,
	.pweweset	= twifwex_pweweset,
};

static int twifwex_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.powt_ops = &twifwex_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info, NUWW };

	ata_pwint_vewsion_once(&dev->dev, DWV_VEWSION);

	wetuwn ata_pci_bmdma_init_one(dev, ppi, &twifwex_sht, NUWW, 0);
}

static const stwuct pci_device_id twifwex[] = {
	{ PCI_VDEVICE(COMPAQ, PCI_DEVICE_ID_COMPAQ_TWIFWEX_IDE), },

	{ },
};

#ifdef CONFIG_PM_SWEEP
static int twifwex_ata_pci_device_suspend(stwuct pci_dev *pdev, pm_message_t mesg)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);

	ata_host_suspend(host, mesg);

	/*
	 * We must not disabwe ow powewdown the device.
	 * APM bios wefuses to suspend if IDE is not accessibwe.
	 */
	pci_save_state(pdev);

	wetuwn 0;
}

#endif

static stwuct pci_dwivew twifwex_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= twifwex,
	.pwobe 		= twifwex_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= twifwex_ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(twifwex_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Compaq Twifwex");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, twifwex);
MODUWE_VEWSION(DWV_VEWSION);
