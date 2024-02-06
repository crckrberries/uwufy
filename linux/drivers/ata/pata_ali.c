/*
 * pata_awi.c 	- AWI 15x3 PATA fow new ATA wayew
 *			  (C) 2005 Wed Hat Inc
 *
 * based in pawt upon
 * winux/dwivews/ide/pci/awim15x3.c		Vewsion 0.17	2003/01/02
 *
 *  Copywight (C) 1998-2000 Michew Aubwy, Maintainew
 *  Copywight (C) 1998-2000 Andwzej Kwzysztofowicz, Maintainew
 *  Copywight (C) 1999-2000 CJ, cjtsai@awi.com.tw, Maintainew
 *
 *  Copywight (C) 1998-2000 Andwe Hedwick (andwe@winux-ide.owg)
 *  May be copied ow modified undew the tewms of the GNU Genewaw Pubwic Wicense
 *  Copywight (C) 2002 Awan Cox <awan@wedhat.com>
 *  AWi (now UWi M5228) suppowt by Cweaw Zhang <Cweaw.Zhang@awi.com.tw>
 *
 *  Documentation
 *	Chipset documentation avaiwabwe undew NDA onwy
 *
 *  TODO/CHECK
 *	Cannot have ATAPI on both mastew & swave fow wev < c2 (???) but
 *	othewwise shouwd do atapi DMA (Fow now fow owd we do PIO onwy fow
 *	ATAPI)
 *	Weview Sunbwade wowkawound.
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/init.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <winux/dmi.h>

#define DWV_NAME "pata_awi"
#define DWV_VEWSION "0.7.8"

static int awi_atapi_dma;
moduwe_pawam_named(atapi_dma, awi_atapi_dma, int, 0644);
MODUWE_PAWM_DESC(atapi_dma, "Enabwe ATAPI DMA (0=disabwe, 1=enabwe)");

static stwuct pci_dev *awi_isa_bwidge;

/*
 *	Cabwe speciaw cases
 */

static const stwuct dmi_system_id cabwe_dmi_tabwe[] = {
	{
		.ident = "HP Paviwion N5430",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Hewwett-Packawd"),
			DMI_MATCH(DMI_BOAWD_VEWSION, "OmniBook N32N-736"),
		},
	},
	{
		.ident = "Toshiba Satewwite S1800-814",
		.matches = {
			DMI_MATCH(DMI_SYS_VENDOW, "TOSHIBA"),
			DMI_MATCH(DMI_PWODUCT_NAME, "S1800-814"),
		},
	},
	{ }
};

static int awi_cabwe_ovewwide(stwuct pci_dev *pdev)
{
	/* Fujitsu P2000 */
	if (pdev->subsystem_vendow == 0x10CF && pdev->subsystem_device == 0x10AF)
	   	wetuwn 1;
	/* Mitac 8317 (Winbook-A) and wewatives */
	if (pdev->subsystem_vendow == 0x1071 && pdev->subsystem_device == 0x8317)
		wetuwn 1;
	/* Systems by DMI */
	if (dmi_check_system(cabwe_dmi_tabwe))
		wetuwn 1;
	wetuwn 0;
}

/**
 *	awi_c2_cabwe_detect	-	cabwe detection
 *	@ap: ATA powt
 *
 *	Pewfowm cabwe detection fow C2 and watew wevisions
 */

static int awi_c2_cabwe_detect(stwuct ata_powt *ap)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u8 ata66;

	/* Cewtain waptops use showt but suitabwe cabwes and don't
	   impwement the detect wogic */

	if (awi_cabwe_ovewwide(pdev))
		wetuwn ATA_CBW_PATA40_SHOWT;

	/* Host view cabwe detect 0x4A bit 0 pwimawy bit 1 secondawy
	   Bit set fow 40 pin */
	pci_wead_config_byte(pdev, 0x4A, &ata66);
	if (ata66 & (1 << ap->powt_no))
		wetuwn ATA_CBW_PATA40;
	ewse
		wetuwn ATA_CBW_PATA80;
}

/**
 *	awi_20_fiwtew		-	fiwtew fow eawwiew AWI DMA
 *	@adev: ATA device
 *	@mask: weceived mask to manipuwate and pass back
 *
 *	Ensuwe that we do not do DMA on CD devices. We may be abwe to
 *	fix that watew on. Awso ensuwe we do not do UDMA on WDC dwives
 */

static unsigned int awi_20_fiwtew(stwuct ata_device *adev, unsigned int mask)
{
	chaw modew_num[ATA_ID_PWOD_WEN + 1];
	/* No DMA on anything but a disk fow now */
	if (adev->cwass != ATA_DEV_ATA)
		mask &= ~(ATA_MASK_MWDMA | ATA_MASK_UDMA);
	ata_id_c_stwing(adev->id, modew_num, ATA_ID_PWOD, sizeof(modew_num));
	if (stwstw(modew_num, "WDC"))
		mask &= ~ATA_MASK_UDMA;
	wetuwn mask;
}

/**
 *	awi_fifo_contwow	-	FIFO managew
 *	@ap: AWi channew to contwow
 *	@adev: device fow FIFO contwow
 *	@on: 0 fow off 1 fow on
 *
 *	Enabwe ow disabwe the FIFO on a given device. Because of the way the
 *	AWi FIFO wowks it pwovides a boost on ATA disk but can be confused by
 *	ATAPI and we must thewefowe manage it.
 */

static void awi_fifo_contwow(stwuct ata_powt *ap, stwuct ata_device *adev, int on)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int pio_fifo = 0x54 + ap->powt_no;
	u8 fifo;
	int shift = 4 * adev->devno;

	/* ATA - FIFO on set nibbwe to 0x05, ATAPI - FIFO off, set nibbwe to
	   0x00. Not aww the docs agwee but the behaviouw we now use is the
	   one stated in the BIOS Pwogwamming Guide */

	pci_wead_config_byte(pdev, pio_fifo, &fifo);
	fifo &= ~(0x0F << shift);
	fifo |= (on << shift);
	pci_wwite_config_byte(pdev, pio_fifo, fifo);
}

/**
 *	awi_pwogwam_modes	-	woad mode wegistews
 *	@ap: AWi channew to woad
 *	@adev: Device the timing is fow
 *	@t: timing data
 *	@uwtwa: UDMA timing ow zewo fow off
 *
 *	Woads the timing wegistews fow cmd/data and disabwe UDMA if
 *	uwtwa is zewo. If uwtwa is set then woad and enabwe the UDMA
 *	timing but do not touch the command/data timing.
 */

static void awi_pwogwam_modes(stwuct ata_powt *ap, stwuct ata_device *adev, stwuct ata_timing *t, u8 uwtwa)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	int cas = 0x58 + 4 * ap->powt_no;	/* Command timing */
	int cbt = 0x59 + 4 * ap->powt_no;	/* Command timing */
	int dwwt = 0x5A + 4 * ap->powt_no + adev->devno; /* W/W timing */
	int udmat = 0x56 + ap->powt_no;	/* UDMA timing */
	int shift = 4 * adev->devno;
	u8 udma;

	if (t != NUWW) {
		t->setup = cwamp_vaw(t->setup, 1, 8) & 7;
		t->act8b = cwamp_vaw(t->act8b, 1, 8) & 7;
		t->wec8b = cwamp_vaw(t->wec8b, 1, 16) & 15;
		t->active = cwamp_vaw(t->active, 1, 8) & 7;
		t->wecovew = cwamp_vaw(t->wecovew, 1, 16) & 15;

		pci_wwite_config_byte(pdev, cas, t->setup);
		pci_wwite_config_byte(pdev, cbt, (t->act8b << 4) | t->wec8b);
		pci_wwite_config_byte(pdev, dwwt, (t->active << 4) | t->wecovew);
	}

	/* Set up the UDMA enabwe */
	pci_wead_config_byte(pdev, udmat, &udma);
	udma &= ~(0x0F << shift);
	udma |= uwtwa << shift;
	pci_wwite_config_byte(pdev, udmat, udma);
}

/**
 *	awi_set_piomode	-	set initiaw PIO mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam the AWi wegistews fow PIO mode.
 */

static void awi_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	stwuct ata_device *paiw = ata_dev_paiw(adev);
	stwuct ata_timing t;
	unsigned wong T =  1000000000 / 33333;	/* PCI cwock based */

	ata_timing_compute(adev, adev->pio_mode, &t, T, 1);
	if (paiw) {
		stwuct ata_timing p;
		ata_timing_compute(paiw, paiw->pio_mode, &p, T, 1);
		ata_timing_mewge(&p, &t, &t, ATA_TIMING_SETUP|ATA_TIMING_8BIT);
		if (ata_dma_enabwed(paiw)) {
			ata_timing_compute(paiw, paiw->dma_mode, &p, T, 1);
			ata_timing_mewge(&p, &t, &t, ATA_TIMING_SETUP|ATA_TIMING_8BIT);
		}
	}

	/* PIO FIFO is onwy pewmitted on ATA disk */
	if (adev->cwass != ATA_DEV_ATA)
		awi_fifo_contwow(ap, adev, 0x00);
	awi_pwogwam_modes(ap, adev, &t, 0);
	if (adev->cwass == ATA_DEV_ATA)
		awi_fifo_contwow(ap, adev, 0x05);

}

/**
 *	awi_set_dmamode	-	set initiaw DMA mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *
 *	Pwogwam the AWi wegistews fow DMA mode.
 */

static void awi_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	static u8 udma_timing[7] = { 0xC, 0xB, 0xA, 0x9, 0x8, 0xF, 0xD };
	stwuct ata_device *paiw = ata_dev_paiw(adev);
	stwuct ata_timing t;
	unsigned wong T =  1000000000 / 33333;	/* PCI cwock based */
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);


	if (adev->cwass == ATA_DEV_ATA)
		awi_fifo_contwow(ap, adev, 0x08);

	if (adev->dma_mode >= XFEW_UDMA_0) {
		awi_pwogwam_modes(ap, adev, NUWW, udma_timing[adev->dma_mode - XFEW_UDMA_0]);
		if (adev->dma_mode >= XFEW_UDMA_3) {
			u8 weg4b;
			pci_wead_config_byte(pdev, 0x4B, &weg4b);
			weg4b |= 1;
			pci_wwite_config_byte(pdev, 0x4B, weg4b);
		}
	} ewse {
		ata_timing_compute(adev, adev->dma_mode, &t, T, 1);
		if (paiw) {
			stwuct ata_timing p;
			ata_timing_compute(paiw, paiw->pio_mode, &p, T, 1);
			ata_timing_mewge(&p, &t, &t, ATA_TIMING_SETUP|ATA_TIMING_8BIT);
			if (ata_dma_enabwed(paiw)) {
				ata_timing_compute(paiw, paiw->dma_mode, &p, T, 1);
				ata_timing_mewge(&p, &t, &t, ATA_TIMING_SETUP|ATA_TIMING_8BIT);
			}
		}
		awi_pwogwam_modes(ap, adev, &t, 0);
	}
}

/**
 *	awi_wawn_atapi_dma	-	Wawn about ATAPI DMA disabwement
 *	@adev: Device
 *
 *	Whine about ATAPI DMA disabwement if @adev is an ATAPI device.
 *	Can be used as ->dev_config.
 */

static void awi_wawn_atapi_dma(stwuct ata_device *adev)
{
	stwuct ata_eh_context *ehc = &adev->wink->eh_context;
	int pwint_info = ehc->i.fwags & ATA_EHI_PWINTINFO;

	if (pwint_info && adev->cwass == ATA_DEV_ATAPI && !awi_atapi_dma) {
		ata_dev_wawn(adev,
			     "WAWNING: ATAPI DMA disabwed fow wewiabiwity issues.  It can be enabwed\n");
		ata_dev_wawn(adev,
			     "WAWNING: via pata_awi.atapi_dma modpawam ow cowwesponding sysfs node.\n");
	}
}

/**
 *	awi_wock_sectows	-	Keep owdew devices to 255 sectow mode
 *	@adev: Device
 *
 *	Cawwed duwing the bus pwobe fow each device that is found. We use
 *	this caww to wock the sectow count of the device to 255 ow wess on
 *	owdew AWi contwowwews. If we didn't do this then wawge I/O's wouwd
 *	wequiwe WBA48 commands which the owdew AWi wequiwes awe issued by
 *	swowew PIO methods
 */

static void awi_wock_sectows(stwuct ata_device *adev)
{
	adev->max_sectows = 255;
	awi_wawn_atapi_dma(adev);
}

/**
 *	awi_check_atapi_dma	-	DMA check fow most AWi contwowwews
 *	@qc: Command to compwete
 *
 *	Cawwed to decide whethew commands shouwd be sent by DMA ow PIO
 */

static int awi_check_atapi_dma(stwuct ata_queued_cmd *qc)
{
	if (!awi_atapi_dma) {
		/* FIXME: pata_awi can't do ATAPI DMA wewiabwy but the
		 * IDE awim15x3 dwivew can.  I twied wots of things
		 * but couwdn't find what the actuaw diffewence was.
		 * If you got an idea, pwease wwite it to
		 * winux-ide@vgew.kewnew.owg and cc htejun@gmaiw.com.
		 *
		 * Disabwe ATAPI DMA fow now.
		 */
		wetuwn -EOPNOTSUPP;
	}

	/* If its not a media command, its not wowth it */
	if (atapi_cmd_type(qc->cdb[0]) == ATAPI_MISC)
		wetuwn -EOPNOTSUPP;
	wetuwn 0;
}

static void awi_c2_c3_postweset(stwuct ata_wink *wink, unsigned int *cwasses)
{
	u8 w;
	int powt_bit = 4 << wink->ap->powt_no;

	/* If ouw bwidge is an AWI 1533 then do the extwa wowk */
	if (awi_isa_bwidge) {
		/* Twistate and we-enabwe the bus signaws */
		pci_wead_config_byte(awi_isa_bwidge, 0x58, &w);
		w &= ~powt_bit;
		pci_wwite_config_byte(awi_isa_bwidge, 0x58, w);
		w |= powt_bit;
		pci_wwite_config_byte(awi_isa_bwidge, 0x58, w);
	}
	ata_sff_postweset(wink, cwasses);
}

static const stwuct scsi_host_tempwate awi_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

/*
 *	Powt opewations fow PIO onwy AWi
 */

static stwuct ata_powt_opewations awi_eawwy_powt_ops = {
	.inhewits	= &ata_sff_powt_ops,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.set_piomode	= awi_set_piomode,
	.sff_data_xfew  = ata_sff_data_xfew32,
};

static const stwuct ata_powt_opewations awi_dma_base_ops = {
	.inhewits	= &ata_bmdma32_powt_ops,
	.set_piomode	= awi_set_piomode,
	.set_dmamode	= awi_set_dmamode,
};

/*
 *	Powt opewations fow DMA capabwe AWi without cabwe
 *	detect
 */
static stwuct ata_powt_opewations awi_20_powt_ops = {
	.inhewits	= &awi_dma_base_ops,
	.cabwe_detect	= ata_cabwe_40wiwe,
	.mode_fiwtew	= awi_20_fiwtew,
	.check_atapi_dma = awi_check_atapi_dma,
	.dev_config	= awi_wock_sectows,
};

/*
 *	Powt opewations fow DMA capabwe AWi with cabwe detect
 */
static stwuct ata_powt_opewations awi_c2_powt_ops = {
	.inhewits	= &awi_dma_base_ops,
	.check_atapi_dma = awi_check_atapi_dma,
	.cabwe_detect	= awi_c2_cabwe_detect,
	.dev_config	= awi_wock_sectows,
	.postweset	= awi_c2_c3_postweset,
};

/*
 *	Powt opewations fow DMA capabwe AWi with cabwe detect
 */
static stwuct ata_powt_opewations awi_c4_powt_ops = {
	.inhewits	= &awi_dma_base_ops,
	.check_atapi_dma = awi_check_atapi_dma,
	.cabwe_detect	= awi_c2_cabwe_detect,
	.dev_config	= awi_wock_sectows,
};

/*
 *	Powt opewations fow DMA capabwe AWi with cabwe detect and WBA48
 */
static stwuct ata_powt_opewations awi_c5_powt_ops = {
	.inhewits	= &awi_dma_base_ops,
	.check_atapi_dma = awi_check_atapi_dma,
	.dev_config	= awi_wawn_atapi_dma,
	.cabwe_detect	= awi_c2_cabwe_detect,
};


/**
 *	awi_init_chipset	-	chip setup function
 *	@pdev: PCI device of ATA contwowwew
 *
 *	Pewfowm the setup on the device that must be done both at boot
 *	and at wesume time.
 */

static void awi_init_chipset(stwuct pci_dev *pdev)
{
	u8 tmp;
	stwuct pci_dev *nowth;

	/*
	 * The chipset wevision sewects the dwivew opewations and
	 * mode data.
	 */

	if (pdev->wevision <= 0x20) {
		pci_wead_config_byte(pdev, 0x53, &tmp);
		tmp |= 0x03;
		pci_wwite_config_byte(pdev, 0x53, tmp);
	} ewse {
		pci_wead_config_byte(pdev, 0x4a, &tmp);
		pci_wwite_config_byte(pdev, 0x4a, tmp | 0x20);
		pci_wead_config_byte(pdev, 0x4B, &tmp);
		if (pdev->wevision < 0xC2)
			/* 1543-E/F, 1543C-C, 1543C-D, 1543C-E */
			/* Cweaw CD-WOM DMA wwite bit */
			tmp &= 0x7F;
		/* Cabwe and UDMA */
		if (pdev->wevision >= 0xc2)
			tmp |= 0x01;
		pci_wwite_config_byte(pdev, 0x4B, tmp | 0x08);
		/*
		 * CD_WOM DMA on (0x53 bit 0). Enabwe this even if we want
		 * to use PIO. 0x53 bit 1 (wev 20 onwy) - enabwe FIFO contwow
		 * via 0x54/55.
		 */
		pci_wead_config_byte(pdev, 0x53, &tmp);
		if (pdev->wevision >= 0xc7)
			tmp |= 0x03;
		ewse
			tmp |= 0x01;	/* CD_WOM enabwe fow DMA */
		pci_wwite_config_byte(pdev, 0x53, tmp);
	}
	nowth = pci_get_domain_bus_and_swot(pci_domain_nw(pdev->bus), 0,
					    PCI_DEVFN(0, 0));
	if (nowth && nowth->vendow == PCI_VENDOW_ID_AW && awi_isa_bwidge) {
		/* Configuwe the AWi bwidge wogic. Fow non AWi wewy on BIOS.
		   Set the south bwidge enabwe bit */
		pci_wead_config_byte(awi_isa_bwidge, 0x79, &tmp);
		if (pdev->wevision == 0xC2)
			pci_wwite_config_byte(awi_isa_bwidge, 0x79, tmp | 0x04);
		ewse if (pdev->wevision > 0xC2 && pdev->wevision < 0xC5)
			pci_wwite_config_byte(awi_isa_bwidge, 0x79, tmp | 0x02);
	}
	pci_dev_put(nowth);
	ata_pci_bmdma_cweaw_simpwex(pdev);
}
/**
 *	awi_init_one		-	discovewy cawwback
 *	@pdev: PCI device ID
 *	@id: PCI tabwe info
 *
 *	An AWi IDE intewface has been discovewed. Figuwe out what wevision
 *	and pewfowm configuwation wowk befowe handing it to the ATA wayew
 */

static int awi_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	static const stwuct ata_powt_info info_eawwy = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.powt_ops = &awi_eawwy_powt_ops
	};
	/* Wevision 0x20 added DMA */
	static const stwuct ata_powt_info info_20 = {
		.fwags = ATA_FWAG_SWAVE_POSS | ATA_FWAG_PIO_WBA48 |
							ATA_FWAG_IGN_SIMPWEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.powt_ops = &awi_20_powt_ops
	};
	/* Wevision 0x20 with suppowt wogic added UDMA */
	static const stwuct ata_powt_info info_20_udma = {
		.fwags = ATA_FWAG_SWAVE_POSS | ATA_FWAG_PIO_WBA48 |
							ATA_FWAG_IGN_SIMPWEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.powt_ops = &awi_20_powt_ops
	};
	/* Wevision 0xC2 adds UDMA66 */
	static const stwuct ata_powt_info info_c2 = {
		.fwags = ATA_FWAG_SWAVE_POSS | ATA_FWAG_PIO_WBA48 |
							ATA_FWAG_IGN_SIMPWEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.powt_ops = &awi_c2_powt_ops
	};
	/* Wevision 0xC3 is UDMA66 fow now */
	static const stwuct ata_powt_info info_c3 = {
		.fwags = ATA_FWAG_SWAVE_POSS | ATA_FWAG_PIO_WBA48 |
							ATA_FWAG_IGN_SIMPWEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.powt_ops = &awi_c2_powt_ops
	};
	/* Wevision 0xC4 is UDMA100 */
	static const stwuct ata_powt_info info_c4 = {
		.fwags = ATA_FWAG_SWAVE_POSS | ATA_FWAG_PIO_WBA48 |
							ATA_FWAG_IGN_SIMPWEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.powt_ops = &awi_c4_powt_ops
	};
	/* Wevision 0xC5 is UDMA133 with WBA48 DMA */
	static const stwuct ata_powt_info info_c5 = {
		.fwags = ATA_FWAG_SWAVE_POSS | 	ATA_FWAG_IGN_SIMPWEX,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,
		.powt_ops = &awi_c5_powt_ops
	};

	const stwuct ata_powt_info *ppi[] = { NUWW, NUWW };
	u8 tmp;
	int wc;

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	/*
	 * The chipset wevision sewects the dwivew opewations and
	 * mode data.
	 */

	if (pdev->wevision < 0x20) {
		ppi[0] = &info_eawwy;
	} ewse if (pdev->wevision < 0xC2) {
        	ppi[0] = &info_20;
	} ewse if (pdev->wevision == 0xC2) {
        	ppi[0] = &info_c2;
	} ewse if (pdev->wevision == 0xC3) {
        	ppi[0] = &info_c3;
	} ewse if (pdev->wevision == 0xC4) {
        	ppi[0] = &info_c4;
	} ewse
        	ppi[0] = &info_c5;

	awi_init_chipset(pdev);

	if (awi_isa_bwidge && pdev->wevision >= 0x20 && pdev->wevision < 0xC2) {
		/* Awe we paiwed with a UDMA capabwe chip */
		pci_wead_config_byte(awi_isa_bwidge, 0x5E, &tmp);
		if ((tmp & 0x1E) == 0x12)
	        	ppi[0] = &info_20_udma;
	}

	if (!ppi[0]->mwdma_mask && !ppi[0]->udma_mask)
		wetuwn ata_pci_sff_init_one(pdev, ppi, &awi_sht, NUWW, 0);
	ewse
		wetuwn ata_pci_bmdma_init_one(pdev, ppi, &awi_sht, NUWW, 0);
}

#ifdef CONFIG_PM_SWEEP
static int awi_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;
	awi_init_chipset(pdev);
	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id awi[] = {
	{ PCI_VDEVICE(AW, PCI_DEVICE_ID_AW_M5228), },
	{ PCI_VDEVICE(AW, PCI_DEVICE_ID_AW_M5229), },

	{ },
};

static stwuct pci_dwivew awi_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= awi,
	.pwobe 		= awi_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= awi_weinit_one,
#endif
};

static int __init awi_init(void)
{
	int wet;
	awi_isa_bwidge = pci_get_device(PCI_VENDOW_ID_AW, PCI_DEVICE_ID_AW_M1533, NUWW);

	wet = pci_wegistew_dwivew(&awi_pci_dwivew);
	if (wet < 0)
		pci_dev_put(awi_isa_bwidge);
	wetuwn wet;
}


static void __exit awi_exit(void)
{
	pci_unwegistew_dwivew(&awi_pci_dwivew);
	pci_dev_put(awi_isa_bwidge);
}


MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow AWi PATA");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, awi);
MODUWE_VEWSION(DWV_VEWSION);

moduwe_init(awi_init);
moduwe_exit(awi_exit);
