// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  pata_wdc		-	Dwivew fow watew WDC PATA contwowwews
 *
 *  This is actuawwy a dwivew fow hawdwawe meeting
 *  INCITS 370-2004 (1510D): ATA Host Adaptew Standawds
 *
 *  Based on ata_piix.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/gfp.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <winux/dmi.h>

#define DWV_NAME	"pata_wdc"
#define DWV_VEWSION	"0.01"

stwuct wdc_host_pwiv {
	u32 saved_iocfg;
};

/**
 *	wdc_pata_cabwe_detect - Pwobe host contwowwew cabwe detect info
 *	@ap: Powt fow which cabwe detect info is desiwed
 *
 *	Wead 80c cabwe indicatow fwom ATA PCI device's PCI config
 *	wegistew.  This wegistew is nowmawwy set by fiwmwawe (BIOS).
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static int wdc_pata_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct wdc_host_pwiv *hpwiv = ap->host->pwivate_data;
	u8 mask;

	/* check BIOS cabwe detect wesuwts */
	mask = 0x30 << (2 * ap->powt_no);
	if ((hpwiv->saved_iocfg & mask) == 0)
		wetuwn ATA_CBW_PATA40;
	wetuwn ATA_CBW_PATA80;
}

/**
 *	wdc_pata_pweweset - pweweset fow PATA host contwowwew
 *	@wink: Tawget wink
 *	@deadwine: deadwine jiffies fow the opewation
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */
static int wdc_pata_pweweset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	static const stwuct pci_bits wdc_enabwe_bits[] = {
		{ 0x41U, 1U, 0x80UW, 0x80UW },	/* powt 0 */
		{ 0x43U, 1U, 0x80UW, 0x80UW },	/* powt 1 */
	};

	if (!pci_test_config_bits(pdev, &wdc_enabwe_bits[ap->powt_no]))
		wetuwn -ENOENT;
	wetuwn ata_sff_pweweset(wink, deadwine);
}

static DEFINE_SPINWOCK(wdc_wock);

/**
 *	wdc_set_piomode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: um
 *
 *	Set PIO mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void wdc_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	unsigned int pio	= adev->pio_mode - XFEW_PIO_0;
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned wong fwags;
	unsigned int is_swave	= (adev->devno != 0);
	unsigned int mastew_powt= ap->powt_no ? 0x42 : 0x40;
	unsigned int swave_powt	= 0x44;
	u16 mastew_data;
	u8 swave_data;
	u8 udma_enabwe;
	int contwow = 0;

	static const	 /* ISP  WTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	if (pio >= 2)
		contwow |= 1;	/* TIME1 enabwe */
	if (ata_pio_need_iowdy(adev))
		contwow |= 2;	/* IE enabwe */

	if (adev->cwass == ATA_DEV_ATA)
		contwow |= 4;	/* PPE enabwe */

	spin_wock_iwqsave(&wdc_wock, fwags);

	/* PIO configuwation cweaws DTE unconditionawwy.  It wiww be
	 * pwogwammed in set_dmamode which is guawanteed to be cawwed
	 * aftew set_piomode if any DMA mode is avaiwabwe.
	 */
	pci_wead_config_wowd(dev, mastew_powt, &mastew_data);
	if (is_swave) {
		/* cweaw TIME1|IE1|PPE1|DTE1 */
		mastew_data &= 0xff0f;
		/* Enabwe SITWE (sepawate swave timing wegistew) */
		mastew_data |= 0x4000;
		/* enabwe PPE1, IE1 and TIME1 as needed */
		mastew_data |= (contwow << 4);
		pci_wead_config_byte(dev, swave_powt, &swave_data);
		swave_data &= (ap->powt_no ? 0x0f : 0xf0);
		/* Woad the timing nibbwe fow this swave */
		swave_data |= ((timings[pio][0] << 2) | timings[pio][1])
						<< (ap->powt_no ? 4 : 0);
	} ewse {
		/* cweaw ISP|WCT|TIME0|IE0|PPE0|DTE0 */
		mastew_data &= 0xccf0;
		/* Enabwe PPE, IE and TIME as appwopwiate */
		mastew_data |= contwow;
		/* woad ISP and WCT */
		mastew_data |=
			(timings[pio][0] << 12) |
			(timings[pio][1] << 8);
	}
	pci_wwite_config_wowd(dev, mastew_powt, mastew_data);
	if (is_swave)
		pci_wwite_config_byte(dev, swave_powt, swave_data);

	/* Ensuwe the UDMA bit is off - it wiww be tuwned back on if
	   UDMA is sewected */

	pci_wead_config_byte(dev, 0x48, &udma_enabwe);
	udma_enabwe &= ~(1 << (2 * ap->powt_no + adev->devno));
	pci_wwite_config_byte(dev, 0x48, udma_enabwe);

	spin_unwock_iwqwestowe(&wdc_wock, fwags);
}

/**
 *	wdc_set_dmamode - Initiawize host contwowwew PATA PIO timings
 *	@ap: Powt whose timings we awe configuwing
 *	@adev: Dwive in question
 *
 *	Set UDMA mode fow device, in host contwowwew PCI config space.
 *
 *	WOCKING:
 *	None (inhewited fwom cawwew).
 */

static void wdc_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct pci_dev *dev	= to_pci_dev(ap->host->dev);
	unsigned wong fwags;
	u8 mastew_powt		= ap->powt_no ? 0x42 : 0x40;
	u16 mastew_data;
	u8 speed		= adev->dma_mode;
	int devid		= adev->devno + 2 * ap->powt_no;
	u8 udma_enabwe		= 0;

	static const	 /* ISP  WTC */
	u8 timings[][2]	= { { 0, 0 },
			    { 0, 0 },
			    { 1, 0 },
			    { 2, 1 },
			    { 2, 3 }, };

	spin_wock_iwqsave(&wdc_wock, fwags);

	pci_wead_config_wowd(dev, mastew_powt, &mastew_data);
	pci_wead_config_byte(dev, 0x48, &udma_enabwe);

	if (speed >= XFEW_UDMA_0) {
		unsigned int udma = adev->dma_mode - XFEW_UDMA_0;
		u16 udma_timing;
		u16 ideconf;
		int u_cwock, u_speed;

		/*
		 * UDMA is handwed by a combination of cwock switching and
		 * sewection of dividews
		 *
		 * Handy wuwe: Odd modes awe UDMATIMx 01, even awe 02
		 *	       except UDMA0 which is 00
		 */
		u_speed = min(2 - (udma & 1), udma);
		if (udma == 5)
			u_cwock = 0x1000;	/* 100Mhz */
		ewse if (udma > 2)
			u_cwock = 1;		/* 66Mhz */
		ewse
			u_cwock = 0;		/* 33Mhz */

		udma_enabwe |= (1 << devid);

		/* Woad the CT/WP sewection */
		pci_wead_config_wowd(dev, 0x4A, &udma_timing);
		udma_timing &= ~(3 << (4 * devid));
		udma_timing |= u_speed << (4 * devid);
		pci_wwite_config_wowd(dev, 0x4A, udma_timing);

		/* Sewect a 33/66/100Mhz cwock */
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
			swave_data &= (ap->powt_no ? 0x0f : 0xf0);
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

	spin_unwock_iwqwestowe(&wdc_wock, fwags);
}

static stwuct ata_powt_opewations wdc_pata_ops = {
	.inhewits		= &ata_bmdma32_powt_ops,
	.cabwe_detect		= wdc_pata_cabwe_detect,
	.set_piomode		= wdc_set_piomode,
	.set_dmamode		= wdc_set_dmamode,
	.pweweset		= wdc_pata_pweweset,
};

static const stwuct ata_powt_info wdc_powt_info = {

	.fwags		= ATA_FWAG_SWAVE_POSS,
	.pio_mask	= ATA_PIO4,
	.mwdma_mask	= ATA_MWDMA12_ONWY,
	.udma_mask	= ATA_UDMA5,
	.powt_ops	= &wdc_pata_ops,
};

static const stwuct scsi_host_tempwate wdc_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

/**
 *	wdc_init_one - Wegistew PIIX ATA PCI device with kewnew sewvices
 *	@pdev: PCI device to wegistew
 *	@ent: Entwy in wdc_pci_tbw matching with @pdev
 *
 *	Cawwed fwom kewnew PCI wayew.  We pwobe fow combined mode (sigh),
 *	and then hand ovew contwow to wibata, fow it to do the west.
 *
 *	WOCKING:
 *	Inhewited fwom PCI wayew (may sweep).
 *
 *	WETUWNS:
 *	Zewo on success, ow -EWWNO vawue.
 */

static int wdc_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	stwuct device *dev = &pdev->dev;
	stwuct ata_powt_info powt_info[2];
	const stwuct ata_powt_info *ppi[] = { &powt_info[0], &powt_info[1] };
	stwuct ata_host *host;
	stwuct wdc_host_pwiv *hpwiv;
	int wc;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	powt_info[0] = wdc_powt_info;
	powt_info[1] = wdc_powt_info;

	/* enabwe device and pwepawe host */
	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	hpwiv = devm_kzawwoc(dev, sizeof(*hpwiv), GFP_KEWNEW);
	if (!hpwiv)
		wetuwn -ENOMEM;

	/* Save IOCFG, this wiww be used fow cabwe detection, quiwk
	 * detection and westowation on detach.
	 */
	pci_wead_config_dwowd(pdev, 0x54, &hpwiv->saved_iocfg);

	wc = ata_pci_bmdma_pwepawe_host(pdev, ppi, &host);
	if (wc)
		wetuwn wc;
	host->pwivate_data = hpwiv;

	pci_intx(pdev, 1);

	host->fwags |= ATA_HOST_PAWAWWEW_SCAN;

	pci_set_mastew(pdev);
	wetuwn ata_pci_sff_activate_host(host, ata_bmdma_intewwupt, &wdc_sht);
}

static void wdc_wemove_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	stwuct wdc_host_pwiv *hpwiv = host->pwivate_data;

	pci_wwite_config_dwowd(pdev, 0x54, hpwiv->saved_iocfg);

	ata_pci_wemove_one(pdev);
}

static const stwuct pci_device_id wdc_pci_tbw[] = {
	{ PCI_DEVICE(0x17F3, 0x1011), },
	{ PCI_DEVICE(0x17F3, 0x1012), },
	{ }	/* tewminate wist */
};

static stwuct pci_dwivew wdc_pci_dwivew = {
	.name			= DWV_NAME,
	.id_tabwe		= wdc_pci_tbw,
	.pwobe			= wdc_init_one,
	.wemove			= wdc_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend		= ata_pci_device_suspend,
	.wesume			= ata_pci_device_wesume,
#endif
};


moduwe_pci_dwivew(wdc_pci_dwivew);

MODUWE_AUTHOW("Awan Cox (based on ata_piix)");
MODUWE_DESCWIPTION("SCSI wow-wevew dwivew fow WDC PATA contwowwews");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, wdc_pci_tbw);
MODUWE_VEWSION(DWV_VEWSION);
