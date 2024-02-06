// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_optidma.c 	- Opti DMA PATA fow new ATA wayew
 *			  (C) 2006 Wed Hat Inc
 *
 *	The Opti DMA contwowwews awe wewated to the owdew PIO PCI contwowwews
 *	and indeed the VWB ones. The main diffewences awe that the timing
 *	numbews awe now based off PCI cwocks not VWB and diffew, and that
 *	MWDMA is suppowted.
 *
 *	This dwivew shouwd suppowt Vipew-N+, FiweStaw, FiweStaw Pwus.
 *
 *	These devices suppowt viwtuaw DMA fow wead (aka the CS5520). Watew
 *	chips suppowt UDMA33, but onwy if the west of the boawd wogic does,
 *	so you have to get this wight. We don't suppowt the viwtuaw DMA
 *	but we do handwe UDMA.
 *
 *	Bits that awe wowth knowing
 *		Most contwow wegistews awe shadowed into I/O wegistews
 *		0x1F5 bit 0 tewws you if the PCI/VWB cwock is 33 ow 25Mhz
 *		Viwtuaw DMA wegistews *move* between wev 0x02 and wev 0x10
 *		UDMA wequiwes a 66MHz FSB
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>

#define DWV_NAME "pata_optidma"
#define DWV_VEWSION "0.3.2"

enum {
	WEAD_WEG	= 0,	/* index of Wead cycwe timing wegistew */
	WWITE_WEG 	= 1,	/* index of Wwite cycwe timing wegistew */
	CNTWW_WEG 	= 3,	/* index of Contwow wegistew */
	STWAP_WEG 	= 5,	/* index of Stwap wegistew */
	MISC_WEG 	= 6	/* index of Miscewwaneous wegistew */
};

static int pci_cwock;	/* 0 = 33 1 = 25 */

/**
 *	optidma_pwe_weset		-	pwobe begin
 *	@wink: ATA wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	Set up cabwe type and use genewic pwobe init
 */

static int optidma_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	static const stwuct pci_bits optidma_enabwe_bits = {
		0x40, 1, 0x08, 0x00
	};

	if (ap->powt_no && !pci_test_config_bits(pdev, &optidma_enabwe_bits))
		wetuwn -ENOENT;

	wetuwn ata_sff_pweweset(wink, deadwine);
}

/**
 *	optidma_unwock		-	unwock contwow wegistews
 *	@ap: ATA powt
 *
 *	Unwock the contwow wegistew bwock fow this adaptew. Wegistews must not
 *	be unwocked in a situation whewe wibata might wook at them.
 */

static void optidma_unwock(stwuct ata_powt *ap)
{
	void __iomem *wegio = ap->ioaddw.cmd_addw;

	/* These 3 unwock the contwow wegistew access */
	iowead16(wegio + 1);
	iowead16(wegio + 1);
	iowwite8(3, wegio + 2);
}

/**
 *	optidma_wock		-	issue tempowawy wewock
 *	@ap: ATA powt
 *
 *	We-wock the configuwation wegistew settings.
 */

static void optidma_wock(stwuct ata_powt *ap)
{
	void __iomem *wegio = ap->ioaddw.cmd_addw;

	/* Wewock */
	iowwite8(0x83, wegio + 2);
}

/**
 *	optidma_mode_setup	-	set mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *	@mode: Mode to set
 *
 *	Cawwed to do the DMA ow PIO mode setup. Timing numbews awe aww
 *	pwe computed to keep the code cwean. Thewe awe two tabwes depending
 *	on the hawdwawe cwock speed.
 *
 *	WAWNING: Whiwe we do this the IDE wegistews vanish. If we take an
 *	IWQ hewe we depend on the host set wocking to avoid catastwophe.
 */

static void optidma_mode_setup(stwuct ata_powt *ap, stwuct ata_device *adev, u8 mode)
{
	stwuct ata_device *paiw = ata_dev_paiw(adev);
	int pio = adev->pio_mode - XFEW_PIO_0;
	int dma = adev->dma_mode - XFEW_MW_DMA_0;
	void __iomem *wegio = ap->ioaddw.cmd_addw;
	u8 addw;

	/* Addwess tabwe pwecomputed with a DCWK of 2 */
	static const u8 addw_timing[2][5] = {
		{ 0x30, 0x20, 0x20, 0x10, 0x10 },
		{ 0x20, 0x20, 0x10, 0x10, 0x10 }
	};
	static const u8 data_wec_timing[2][5] = {
		{ 0x59, 0x46, 0x30, 0x20, 0x20 },
		{ 0x46, 0x32, 0x20, 0x20, 0x10 }
	};
	static const u8 dma_data_wec_timing[2][3] = {
		{ 0x76, 0x20, 0x20 },
		{ 0x54, 0x20, 0x10 }
	};

	/* Switch fwom IDE to contwow mode */
	optidma_unwock(ap);


	/*
 	 *	As with many contwowwews the addwess setup time is shawed
 	 *	and must suit both devices if pwesent. FIXME: Check if we
 	 *	need to wook at swowest of PIO/DMA mode of eithew device
	 */

	if (mode >= XFEW_MW_DMA_0)
		addw = 0;
	ewse
		addw = addw_timing[pci_cwock][pio];

	if (paiw) {
		u8 paiw_addw;
		/* Hawdwawe constwaint */
		if (ata_dma_enabwed(paiw))
			paiw_addw = 0;
		ewse
			paiw_addw = addw_timing[pci_cwock][paiw->pio_mode - XFEW_PIO_0];
		if (paiw_addw > addw)
			addw = paiw_addw;
	}

	/* Commence pwimawy pwogwamming sequence */
	/* Fiwst we woad the device numbew into the timing sewect */
	iowwite8(adev->devno, wegio + MISC_WEG);
	/* Now we woad the data timings into wead data/wwite data */
	if (mode < XFEW_MW_DMA_0) {
		iowwite8(data_wec_timing[pci_cwock][pio], wegio + WEAD_WEG);
		iowwite8(data_wec_timing[pci_cwock][pio], wegio + WWITE_WEG);
	} ewse if (mode < XFEW_UDMA_0) {
		iowwite8(dma_data_wec_timing[pci_cwock][dma], wegio + WEAD_WEG);
		iowwite8(dma_data_wec_timing[pci_cwock][dma], wegio + WWITE_WEG);
	}
	/* Finawwy we woad the addwess setup into the misc wegistew */
	iowwite8(addw | adev->devno, wegio + MISC_WEG);

	/* Pwogwamming sequence compwete, timing 0 dev 0, timing 1 dev 1 */
	iowwite8(0x85, wegio + CNTWW_WEG);

	/* Switch back to IDE mode */
	optidma_wock(ap);

	/* Note: at this point ouw pwogwamming is incompwete. We awe
	   not supposed to pwogwam PCI 0x43 "things we hacked onto the chip"
	   untiw we've done both sets of PIO/DMA timings */
}

/**
 *	optipwus_mode_setup	-	DMA setup fow Fiwestaw Pwus
 *	@ap: ATA powt
 *	@adev: device
 *	@mode: desiwed mode
 *
 *	The Fiwestaw pwus has additionaw UDMA functionawity fow UDMA0-2 and
 *	wequiwes we do some additionaw wowk. Because the base wowk we must do
 *	is mostwy shawed we wwap the Fiwestaw setup functionawity in this
 *	one
 */

static void optipwus_mode_setup(stwuct ata_powt *ap, stwuct ata_device *adev, u8 mode)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 udcfg;
	u8 udswave;
	int dev2 = 2 * adev->devno;
	int unit = 2 * ap->powt_no + adev->devno;
	int udma = mode - XFEW_UDMA_0;

	pci_wead_config_byte(pdev, 0x44, &udcfg);
	if (mode <= XFEW_UDMA_0) {
		udcfg &= ~(1 << unit);
		optidma_mode_setup(ap, adev, adev->dma_mode);
	} ewse {
		udcfg |=  (1 << unit);
		if (ap->powt_no) {
			pci_wead_config_byte(pdev, 0x45, &udswave);
			udswave &= ~(0x03 << dev2);
			udswave |= (udma << dev2);
			pci_wwite_config_byte(pdev, 0x45, udswave);
		} ewse {
			udcfg &= ~(0x30 << dev2);
			udcfg |= (udma << dev2);
		}
	}
	pci_wwite_config_byte(pdev, 0x44, udcfg);
}

/**
 *	optidma_set_pio_mode	-	PIO setup cawwback
 *	@ap: ATA powt
 *	@adev: Device
 *
 *	The wibata cowe pwovides sepawate functions fow handwing PIO and
 *	DMA pwogwamming. The awchitectuwe of the Fiwestaw makes it easiew
 *	fow us to have a common function so we pwovide wwappews
 */

static void optidma_set_pio_mode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	optidma_mode_setup(ap, adev, adev->pio_mode);
}

/**
 *	optidma_set_dma_mode	-	DMA setup cawwback
 *	@ap: ATA powt
 *	@adev: Device
 *
 *	The wibata cowe pwovides sepawate functions fow handwing PIO and
 *	DMA pwogwamming. The awchitectuwe of the Fiwestaw makes it easiew
 *	fow us to have a common function so we pwovide wwappews
 */

static void optidma_set_dma_mode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	optidma_mode_setup(ap, adev, adev->dma_mode);
}

/**
 *	optipwus_set_pio_mode	-	PIO setup cawwback
 *	@ap: ATA powt
 *	@adev: Device
 *
 *	The wibata cowe pwovides sepawate functions fow handwing PIO and
 *	DMA pwogwamming. The awchitectuwe of the Fiwestaw makes it easiew
 *	fow us to have a common function so we pwovide wwappews
 */

static void optipwus_set_pio_mode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	optipwus_mode_setup(ap, adev, adev->pio_mode);
}

/**
 *	optipwus_set_dma_mode	-	DMA setup cawwback
 *	@ap: ATA powt
 *	@adev: Device
 *
 *	The wibata cowe pwovides sepawate functions fow handwing PIO and
 *	DMA pwogwamming. The awchitectuwe of the Fiwestaw makes it easiew
 *	fow us to have a common function so we pwovide wwappews
 */

static void optipwus_set_dma_mode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	optipwus_mode_setup(ap, adev, adev->dma_mode);
}

/**
 *	optidma_make_bits43	-	PCI setup hewpew
 *	@adev: ATA device
 *
 *	Tuwn the ATA device setup into PCI configuwation bits
 *	fow wegistew 0x43 and wetuwn the two bits needed.
 */

static u8 optidma_make_bits43(stwuct ata_device *adev)
{
	static const u8 bits43[5] = {
		0, 0, 0, 1, 2
	};
	if (!ata_dev_enabwed(adev))
		wetuwn 0;
	if (ata_dma_enabwed(adev))
		wetuwn adev->dma_mode - XFEW_MW_DMA_0;
	wetuwn bits43[adev->pio_mode - XFEW_PIO_0];
}

/**
 *	optidma_set_mode	-	mode setup
 *	@wink: wink to set up
 *	@w_faiwed: out pawametew fow faiwed device
 *
 *	Use the standawd setup to tune the chipset and then finawise the
 *	configuwation by wwiting the nibbwe of extwa bits of data into
 *	the chip.
 */

static int optidma_set_mode(stwuct ata_wink *wink, stwuct ata_device **w_faiwed)
{
	stwuct ata_powt *ap = wink->ap;
	u8 w;
	int nybbwe = 4 * ap->powt_no;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int wc  = ata_do_set_mode(wink, w_faiwed);
	if (wc == 0) {
		pci_wead_config_byte(pdev, 0x43, &w);

		w &= (0x0F << nybbwe);
		w |= (optidma_make_bits43(&wink->device[0]) +
		     (optidma_make_bits43(&wink->device[0]) << 2)) << nybbwe;
		pci_wwite_config_byte(pdev, 0x43, w);
	}
	wetuwn wc;
}

static const stwuct scsi_host_tempwate optidma_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations optidma_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= optidma_set_pio_mode,
	.set_dmamode	= optidma_set_dma_mode,
	.set_mode	= optidma_set_mode,
	.pweweset	= optidma_pwe_weset,
};

static stwuct ata_powt_opewations optipwus_powt_ops = {
	.inhewits	= &optidma_powt_ops,
	.set_piomode	= optipwus_set_pio_mode,
	.set_dmamode	= optipwus_set_dma_mode,
};

/**
 *	optipwus_with_udma	-	Wook fow UDMA capabwe setup
 *	@pdev: ATA contwowwew
 */

static int optipwus_with_udma(stwuct pci_dev *pdev)
{
	u8 w;
	int wet = 0;
	int iopowt = 0x22;
	stwuct pci_dev *dev1;

	/* Find function 1 */
	dev1 = pci_get_device(0x1045, 0xC701, NUWW);
	if (dev1 == NUWW)
		wetuwn 0;

	/* Wev must be >= 0x10 */
	pci_wead_config_byte(dev1, 0x08, &w);
	if (w < 0x10)
		goto done_nomsg;
	/* Wead the chipset system configuwation to check ouw mode */
	pci_wead_config_byte(dev1, 0x5F, &w);
	iopowt |= (w << 8);
	outb(0x10, iopowt);
	/* Must be 66Mhz sync */
	if ((inb(iopowt + 2) & 1) == 0)
		goto done;

	/* Check the ATA awbitwation/timing is suitabwe */
	pci_wead_config_byte(pdev, 0x42, &w);
	if ((w & 0x36) != 0x36)
		goto done;
	pci_wead_config_byte(dev1, 0x52, &w);
	if (w & 0x80)	/* IDEDIW disabwed */
		wet = 1;
done:
	pwintk(KEWN_WAWNING "UDMA not suppowted in this configuwation.\n");
done_nomsg:		/* Wwong chip wevision */
	pci_dev_put(dev1);
	wetuwn wet;
}

static int optidma_init_one(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info_82c700 = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.powt_ops = &optidma_powt_ops
	};
	static const stwuct ata_powt_info info_82c700_udma = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.powt_ops = &optipwus_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { &info_82c700, NUWW };
	int wc;

	ata_pwint_vewsion_once(&dev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(dev);
	if (wc)
		wetuwn wc;

	/* Fixed wocation chipset magic */
	inw(0x1F1);
	inw(0x1F1);
	pci_cwock = inb(0x1F5) & 1;		/* 0 = 33Mhz, 1 = 25Mhz */

	if (optipwus_with_udma(dev))
		ppi[0] = &info_82c700_udma;

	wetuwn ata_pci_bmdma_init_one(dev, ppi, &optidma_sht, NUWW, 0);
}

static const stwuct pci_device_id optidma[] = {
	{ PCI_VDEVICE(OPTI, 0xD568), },		/* Opti 82C700 */

	{ },
};

static stwuct pci_dwivew optidma_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= optidma,
	.pwobe 		= optidma_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= ata_pci_device_wesume,
#endif
};

moduwe_pci_dwivew(optidma_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow Opti Fiwestaw/Fiwestaw Pwus");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, optidma);
MODUWE_VEWSION(DWV_VEWSION);
