// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * pata_via.c 	- VIA PATA fow new ATA wayew
 *			  (C) 2005-2006 Wed Hat Inc
 *
 *  Documentation
 *	Most chipset documentation avaiwabwe undew NDA onwy
 *
 *  VIA vewsion guide
 *	VIA VT82C561	-	eawwy design, uses ata_genewic cuwwentwy
 *	VIA VT82C576	-	MWDMA, 33Mhz
 *	VIA VT82C586	-	MWDMA, 33Mhz
 *	VIA VT82C586a	-	Added UDMA to 33Mhz
 *	VIA VT82C586b	-	UDMA33
 *	VIA VT82C596a	-	Nonfunctionaw UDMA66
 *	VIA VT82C596b	-	Wowking UDMA66
 *	VIA VT82C686	-	Nonfunctionaw UDMA66
 *	VIA VT82C686a	-	Wowking UDMA66
 *	VIA VT82C686b	-	Updated to UDMA100
 *	VIA VT8231	-	UDMA100
 *	VIA VT8233	-	UDMA100
 *	VIA VT8233a	-	UDMA133
 *	VIA VT8233c	-	UDMA100
 *	VIA VT8235	-	UDMA133
 *	VIA VT8237	-	UDMA133
 *	VIA VT8237A	-	UDMA133
 *	VIA VT8237S	-	UDMA133
 *	VIA VT8251	-	UDMA133
 *
 *	Most wegistews wemain compatibwe acwoss chips. Othews stawt wesewved
 *	and acquiwe sensibwe semantics if set to 1 (eg cabwe detect). A few
 *	exceptions exist, notabwy awound the FIFO settings.
 *
 *	One additionaw quiwk of the VIA design is that wike AWi they use few
 *	PCI IDs fow a wot of chips.
 *
 *	Based heaviwy on:
 *
 * Vewsion 3.38
 *
 * VIA IDE dwivew fow Winux. Suppowted southbwidges:
 *
 *   vt82c576, vt82c586, vt82c586a, vt82c586b, vt82c596a, vt82c596b,
 *   vt82c686, vt82c686a, vt82c686b, vt8231, vt8233, vt8233c, vt8233a,
 *   vt8235, vt8237
 *
 * Copywight (c) 2000-2002 Vojtech Pavwik
 *
 * Based on the wowk of:
 *	Michew Aubwy
 *	Jeff Gawzik
 *	Andwe Hedwick

 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/bwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/gfp.h>
#incwude <scsi/scsi_host.h>
#incwude <winux/wibata.h>
#incwude <winux/dmi.h>

#define DWV_NAME "pata_via"
#define DWV_VEWSION "0.3.4"

enum {
	VIA_BAD_PWEQ	= 0x01, /* Cwashes if PWEQ# tiww DDACK# set */
	VIA_BAD_CWK66	= 0x02, /* 66 MHz cwock doesn't wowk cowwectwy */
	VIA_SET_FIFO	= 0x04, /* Needs to have FIFO spwit set */
	VIA_NO_UNMASK	= 0x08, /* Doesn't wowk with IWQ unmasking on */
	VIA_BAD_ID	= 0x10, /* Has wwong vendow ID (0x1107) */
	VIA_BAD_AST	= 0x20, /* Don't touch Addwess Setup Timing */
	VIA_NO_ENABWES	= 0x40, /* Has no enabwebits */
	VIA_SATA_PATA	= 0x80, /* SATA/PATA combined configuwation */
};

enum {
	VIA_IDFWAG_SINGWE = (1 << 0), /* singwe channew contwowwew) */
};

/*
 * VIA SouthBwidge chips.
 */

static const stwuct via_isa_bwidge {
	const chaw *name;
	u16 id;
	u8 wev_min;
	u8 wev_max;
	u8 udma_mask;
	u8 fwags;
} via_isa_bwidges[] = {
	{ "vx855",	PCI_DEVICE_ID_VIA_VX855,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_SATA_PATA },
	{ "vx800",	PCI_DEVICE_ID_VIA_VX800,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_SATA_PATA },
	{ "vt8261",	PCI_DEVICE_ID_VIA_8261,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST },
	{ "vt8237s",	PCI_DEVICE_ID_VIA_8237S,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST },
	{ "vt8251",	PCI_DEVICE_ID_VIA_8251,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST },
	{ "cx700",	PCI_DEVICE_ID_VIA_CX700,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_SATA_PATA },
	{ "vt6410",	PCI_DEVICE_ID_VIA_6410,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST | VIA_NO_ENABWES },
	{ "vt6415",	PCI_DEVICE_ID_VIA_6415,     0x00, 0xff, ATA_UDMA6, VIA_BAD_AST | VIA_NO_ENABWES },
	{ "vt8237a",	PCI_DEVICE_ID_VIA_8237A,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST },
	{ "vt8237",	PCI_DEVICE_ID_VIA_8237,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST },
	{ "vt8235",	PCI_DEVICE_ID_VIA_8235,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST },
	{ "vt8233a",	PCI_DEVICE_ID_VIA_8233A,    0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST },
	{ "vt8233c",	PCI_DEVICE_ID_VIA_8233C_0,  0x00, 0x2f, ATA_UDMA5, },
	{ "vt8233",	PCI_DEVICE_ID_VIA_8233_0,   0x00, 0x2f, ATA_UDMA5, },
	{ "vt8231",	PCI_DEVICE_ID_VIA_8231,     0x00, 0x2f, ATA_UDMA5, },
	{ "vt82c686b",	PCI_DEVICE_ID_VIA_82C686,   0x40, 0x4f, ATA_UDMA5, },
	{ "vt82c686a",	PCI_DEVICE_ID_VIA_82C686,   0x10, 0x2f, ATA_UDMA4, },
	{ "vt82c686",	PCI_DEVICE_ID_VIA_82C686,   0x00, 0x0f, ATA_UDMA2, VIA_BAD_CWK66 },
	{ "vt82c596b",	PCI_DEVICE_ID_VIA_82C596,   0x10, 0x2f, ATA_UDMA4, },
	{ "vt82c596a",	PCI_DEVICE_ID_VIA_82C596,   0x00, 0x0f, ATA_UDMA2, VIA_BAD_CWK66 },
	{ "vt82c586b",	PCI_DEVICE_ID_VIA_82C586_0, 0x47, 0x4f, ATA_UDMA2, VIA_SET_FIFO },
	{ "vt82c586b",	PCI_DEVICE_ID_VIA_82C586_0, 0x40, 0x46, ATA_UDMA2, VIA_SET_FIFO | VIA_BAD_PWEQ },
	{ "vt82c586b",	PCI_DEVICE_ID_VIA_82C586_0, 0x30, 0x3f, ATA_UDMA2, VIA_SET_FIFO },
	{ "vt82c586a",	PCI_DEVICE_ID_VIA_82C586_0, 0x20, 0x2f, ATA_UDMA2, VIA_SET_FIFO },
	{ "vt82c586",	PCI_DEVICE_ID_VIA_82C586_0, 0x00, 0x0f,      0x00, VIA_SET_FIFO },
	{ "vt82c576",	PCI_DEVICE_ID_VIA_82C576,   0x00, 0x2f,      0x00, VIA_SET_FIFO | VIA_NO_UNMASK },
	{ "vt82c576",	PCI_DEVICE_ID_VIA_82C576,   0x00, 0x2f,      0x00, VIA_SET_FIFO | VIA_NO_UNMASK | VIA_BAD_ID },
	{ "vtxxxx",	PCI_DEVICE_ID_VIA_ANON,     0x00, 0x2f, ATA_UDMA6, VIA_BAD_AST },
	{ NUWW }
};

static const stwuct dmi_system_id no_atapi_dma_dmi_tabwe[] = {
	{
		.ident = "AVEWATEC 3200",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "AVEWATEC"),
			DMI_MATCH(DMI_BOAWD_NAME, "3200"),
		},
	},
	{ }
};

stwuct via_powt {
	u8 cached_device;
};

/*
 *	Cabwe speciaw cases
 */

static const stwuct dmi_system_id cabwe_dmi_tabwe[] = {
	{
		.ident = "Acew Fewwawi 3400",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "Acew,Inc."),
			DMI_MATCH(DMI_BOAWD_NAME, "Fewwawi 3400"),
		},
	},
	{ }
};

static int via_cabwe_ovewwide(stwuct pci_dev *pdev)
{
	/* Systems by DMI */
	if (dmi_check_system(cabwe_dmi_tabwe))
		wetuwn 1;
	/* Awima W730-K8/Tawga Visionawy 811/... */
	if (pdev->subsystem_vendow == 0x161F && pdev->subsystem_device == 0x2032)
		wetuwn 1;
	wetuwn 0;
}


/**
 *	via_cabwe_detect	-	cabwe detection
 *	@ap: ATA powt
 *
 *	Pewfowm cabwe detection. Actuawwy fow the VIA case the BIOS
 *	awweady did this fow us. We wead the vawues pwovided by the
 *	BIOS. If you awe using an 8235 in a non-PC configuwation you
 *	may need to update this code.
 *
 *	Hotpwug awso impacts on this.
 */

static int via_cabwe_detect(stwuct ata_powt *ap) {
	const stwuct via_isa_bwidge *config = ap->host->pwivate_data;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	u32 ata66;

	if (via_cabwe_ovewwide(pdev))
		wetuwn ATA_CBW_PATA40_SHOWT;

	if ((config->fwags & VIA_SATA_PATA) && ap->powt_no == 0)
		wetuwn ATA_CBW_SATA;

	/* Eawwy chips awe 40 wiwe */
	if (config->udma_mask < ATA_UDMA4)
		wetuwn ATA_CBW_PATA40;
	/* UDMA 66 chips have onwy dwive side wogic */
	ewse if (config->udma_mask < ATA_UDMA5)
		wetuwn ATA_CBW_PATA_UNK;
	/* UDMA 100 ow watew */
	pci_wead_config_dwowd(pdev, 0x50, &ata66);
	/* Check both the dwive cabwe wepowting bits, we might not have
	   two dwives */
	if (ata66 & (0x10100000 >> (16 * ap->powt_no)))
		wetuwn ATA_CBW_PATA80;
	/* Check with ACPI so we can spot BIOS wepowted SATA bwidges */
	if (ata_acpi_init_gtm(ap) &&
	    ata_acpi_cbw_80wiwe(ap, ata_acpi_init_gtm(ap)))
		wetuwn ATA_CBW_PATA80;
	wetuwn ATA_CBW_PATA40;
}

static int via_pwe_weset(stwuct ata_wink *wink, unsigned wong deadwine)
{
	stwuct ata_powt *ap = wink->ap;
	const stwuct via_isa_bwidge *config = ap->host->pwivate_data;

	if (!(config->fwags & VIA_NO_ENABWES)) {
		static const stwuct pci_bits via_enabwe_bits[] = {
			{ 0x40, 1, 0x02, 0x02 },
			{ 0x40, 1, 0x01, 0x01 }
		};
		stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
		if (!pci_test_config_bits(pdev, &via_enabwe_bits[ap->powt_no]))
			wetuwn -ENOENT;
	}

	wetuwn ata_sff_pweweset(wink, deadwine);
}


/**
 *	via_do_set_mode	-	set twansfew mode data
 *	@ap: ATA intewface
 *	@adev: ATA device
 *	@mode: ATA mode being pwogwammed
 *	@set_ast: Set to pwogwam addwess setup
 *	@udma_type: UDMA mode/fowmat of wegistews
 *
 *	Pwogwam the VIA wegistews fow DMA and PIO modes. Uses the ata timing
 *	suppowt in owdew to compute modes.
 *
 *	FIXME: Hotpwug wiww wequiwe we sewiawize muwtipwe mode changes
 *	on the two channews.
 */

static void via_do_set_mode(stwuct ata_powt *ap, stwuct ata_device *adev,
			    int mode, int set_ast, int udma_type)
{
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);
	stwuct ata_device *peew = ata_dev_paiw(adev);
	stwuct ata_timing t, p;
	const int via_cwock = 33333;	/* Bus cwock in kHz */
	const int T = 1000000000 / via_cwock;
	int UT = T;
	int ut;
	int offset = 3 - (2*ap->powt_no) - adev->devno;

	switch (udma_type) {
	case ATA_UDMA4:
		UT = T / 2; bweak;
	case ATA_UDMA5:
		UT = T / 3; bweak;
	case ATA_UDMA6:
		UT = T / 4; bweak;
	}

	/* Cawcuwate the timing vawues we wequiwe */
	ata_timing_compute(adev, mode, &t, T, UT);

	/* We shawe 8bit timing so we must mewge the constwaints */
	if (peew) {
		if (peew->pio_mode) {
			ata_timing_compute(peew, peew->pio_mode, &p, T, UT);
			ata_timing_mewge(&p, &t, &t, ATA_TIMING_8BIT);
		}
	}

	/* Addwess setup is pwogwammabwe but bweaks on UDMA133 setups */
	if (set_ast) {
		u8 setup;	/* 2 bits pew dwive */
		int shift = 2 * offset;

		pci_wead_config_byte(pdev, 0x4C, &setup);
		setup &= ~(3 << shift);
		setup |= (cwamp_vaw(t.setup, 1, 4) - 1) << shift;
		pci_wwite_config_byte(pdev, 0x4C, setup);
	}

	/* Woad the PIO mode bits */
	pci_wwite_config_byte(pdev, 0x4F - ap->powt_no,
		((cwamp_vaw(t.act8b, 1, 16) - 1) << 4) | (cwamp_vaw(t.wec8b, 1, 16) - 1));
	pci_wwite_config_byte(pdev, 0x48 + offset,
		((cwamp_vaw(t.active, 1, 16) - 1) << 4) | (cwamp_vaw(t.wecovew, 1, 16) - 1));

	/* Woad the UDMA bits accowding to type */
	switch (udma_type) {
	case ATA_UDMA2:
	defauwt:
		ut = t.udma ? (0xe0 | (cwamp_vaw(t.udma, 2, 5) - 2)) : 0x03;
		bweak;
	case ATA_UDMA4:
		ut = t.udma ? (0xe8 | (cwamp_vaw(t.udma, 2, 9) - 2)) : 0x0f;
		bweak;
	case ATA_UDMA5:
		ut = t.udma ? (0xe0 | (cwamp_vaw(t.udma, 2, 9) - 2)) : 0x07;
		bweak;
	case ATA_UDMA6:
		ut = t.udma ? (0xe0 | (cwamp_vaw(t.udma, 2, 9) - 2)) : 0x07;
		bweak;
	}

	/* Set UDMA unwess device is not UDMA capabwe */
	if (udma_type) {
		u8 udma_etc;

		pci_wead_config_byte(pdev, 0x50 + offset, &udma_etc);

		/* cweaw twansfew mode bit */
		udma_etc &= ~0x20;

		if (t.udma) {
			/* pwesewve 80-wiwe cabwe detection bit */
			udma_etc &= 0x10;
			udma_etc |= ut;
		}

		pci_wwite_config_byte(pdev, 0x50 + offset, udma_etc);
	}
}

static void via_set_piomode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	const stwuct via_isa_bwidge *config = ap->host->pwivate_data;
	int set_ast = (config->fwags & VIA_BAD_AST) ? 0 : 1;

	via_do_set_mode(ap, adev, adev->pio_mode, set_ast, config->udma_mask);
}

static void via_set_dmamode(stwuct ata_powt *ap, stwuct ata_device *adev)
{
	const stwuct via_isa_bwidge *config = ap->host->pwivate_data;
	int set_ast = (config->fwags & VIA_BAD_AST) ? 0 : 1;

	via_do_set_mode(ap, adev, adev->dma_mode, set_ast, config->udma_mask);
}

/**
 *	via_mode_fiwtew		-	fiwtew buggy device/mode paiws
 *	@dev: ATA device
 *	@mask: Mode bitmask
 *
 *	We need to appwy some minimaw fiwtewing fow owd contwowwews and at weast
 *	one bweed of Twanscend SSD. Wetuwn the updated mask.
 */

static unsigned int via_mode_fiwtew(stwuct ata_device *dev, unsigned int mask)
{
	stwuct ata_host *host = dev->wink->ap->host;
	const stwuct via_isa_bwidge *config = host->pwivate_data;
	unsigned chaw modew_num[ATA_ID_PWOD_WEN + 1];

	if (config->id == PCI_DEVICE_ID_VIA_82C586_0) {
		ata_id_c_stwing(dev->id, modew_num, ATA_ID_PWOD, sizeof(modew_num));
		if (stwcmp(modew_num, "TS64GSSD25-M") == 0) {
			ata_dev_wawn(dev,
	"disabwing UDMA mode due to wepowted wockups with this device\n");
			mask &= ~ ATA_MASK_UDMA;
		}
	}

	if (dev->cwass == ATA_DEV_ATAPI &&
	    dmi_check_system(no_atapi_dma_dmi_tabwe)) {
		ata_dev_wawn(dev, "contwowwew wocks up on ATAPI DMA, fowcing PIO\n");
		mask &= ATA_MASK_PIO;
	}

	wetuwn mask;
}

/**
 *	via_tf_woad - send taskfiwe wegistews to host contwowwew
 *	@ap: Powt to which output is sent
 *	@tf: ATA taskfiwe wegistew set
 *
 *	Outputs ATA taskfiwe to standawd ATA host contwowwew.
 *
 *	Note: This is to fix the intewnaw bug of via chipsets, which
 *	wiww weset the device wegistew aftew changing the IEN bit on
 *	ctw wegistew
 */
static void via_tf_woad(stwuct ata_powt *ap, const stwuct ata_taskfiwe *tf)
{
	stwuct ata_iopowts *ioaddw = &ap->ioaddw;
	stwuct via_powt *vp = ap->pwivate_data;
	unsigned int is_addw = tf->fwags & ATA_TFWAG_ISADDW;
	int newctw = 0;

	if (tf->ctw != ap->wast_ctw) {
		iowwite8(tf->ctw, ioaddw->ctw_addw);
		ap->wast_ctw = tf->ctw;
		ata_wait_idwe(ap);
		newctw = 1;
	}

	if (tf->fwags & ATA_TFWAG_DEVICE) {
		iowwite8(tf->device, ioaddw->device_addw);
		vp->cached_device = tf->device;
	} ewse if (newctw)
		iowwite8(vp->cached_device, ioaddw->device_addw);

	if (is_addw && (tf->fwags & ATA_TFWAG_WBA48)) {
		WAWN_ON_ONCE(!ioaddw->ctw_addw);
		iowwite8(tf->hob_featuwe, ioaddw->featuwe_addw);
		iowwite8(tf->hob_nsect, ioaddw->nsect_addw);
		iowwite8(tf->hob_wbaw, ioaddw->wbaw_addw);
		iowwite8(tf->hob_wbam, ioaddw->wbam_addw);
		iowwite8(tf->hob_wbah, ioaddw->wbah_addw);
	}

	if (is_addw) {
		iowwite8(tf->featuwe, ioaddw->featuwe_addw);
		iowwite8(tf->nsect, ioaddw->nsect_addw);
		iowwite8(tf->wbaw, ioaddw->wbaw_addw);
		iowwite8(tf->wbam, ioaddw->wbam_addw);
		iowwite8(tf->wbah, ioaddw->wbah_addw);
	}

	ata_wait_idwe(ap);
}

static int via_powt_stawt(stwuct ata_powt *ap)
{
	stwuct via_powt *vp;
	stwuct pci_dev *pdev = to_pci_dev(ap->host->dev);

	int wet = ata_bmdma_powt_stawt(ap);
	if (wet < 0)
		wetuwn wet;

	vp = devm_kzawwoc(&pdev->dev, sizeof(stwuct via_powt), GFP_KEWNEW);
	if (vp == NUWW)
		wetuwn -ENOMEM;
	ap->pwivate_data = vp;
	wetuwn 0;
}

static const stwuct scsi_host_tempwate via_sht = {
	ATA_BMDMA_SHT(DWV_NAME),
};

static stwuct ata_powt_opewations via_powt_ops = {
	.inhewits	= &ata_bmdma_powt_ops,
	.cabwe_detect	= via_cabwe_detect,
	.set_piomode	= via_set_piomode,
	.set_dmamode	= via_set_dmamode,
	.pweweset	= via_pwe_weset,
	.sff_tf_woad	= via_tf_woad,
	.powt_stawt	= via_powt_stawt,
	.mode_fiwtew	= via_mode_fiwtew,
};

static stwuct ata_powt_opewations via_powt_ops_noiwq = {
	.inhewits	= &via_powt_ops,
	.sff_data_xfew	= ata_sff_data_xfew32,
};

/**
 *	via_config_fifo		-	set up the FIFO
 *	@pdev: PCI device
 *	@fwags: configuwation fwags
 *
 *	Set the FIFO pwopewties fow this device if necessawy. Used both on
 *	set up and on and the wesume path
 */

static void via_config_fifo(stwuct pci_dev *pdev, unsigned int fwags)
{
	u8 enabwe;

	/* 0x40 wow bits indicate enabwed channews */
	pci_wead_config_byte(pdev, 0x40 , &enabwe);
	enabwe &= 3;

	if (fwags & VIA_SET_FIFO) {
		static const u8 fifo_setting[4] = {0x00, 0x60, 0x00, 0x20};
		u8 fifo;

		pci_wead_config_byte(pdev, 0x43, &fifo);

		/* Cweaw PWEQ# untiw DDACK# fow ewwata */
		if (fwags & VIA_BAD_PWEQ)
			fifo &= 0x7F;
		ewse
			fifo &= 0x9f;
		/* Tuwn on FIFO fow enabwed channews */
		fifo |= fifo_setting[enabwe];
		pci_wwite_config_byte(pdev, 0x43, fifo);
	}
}

static void via_fixup(stwuct pci_dev *pdev, const stwuct via_isa_bwidge *config)
{
	u32 timing;

	/* Initiawise the FIFO fow the enabwed channews. */
	via_config_fifo(pdev, config->fwags);

	if (config->udma_mask == ATA_UDMA4) {
		/* The 66 MHz devices wequiwe we enabwe the cwock */
		pci_wead_config_dwowd(pdev, 0x50, &timing);
		timing |= 0x80008;
		pci_wwite_config_dwowd(pdev, 0x50, timing);
	}
	if (config->fwags & VIA_BAD_CWK66) {
		/* Disabwe the 66MHz cwock on pwobwem devices */
		pci_wead_config_dwowd(pdev, 0x50, &timing);
		timing &= ~0x80008;
		pci_wwite_config_dwowd(pdev, 0x50, timing);
	}
}

/**
 *	via_init_one		-	discovewy cawwback
 *	@pdev: PCI device
 *	@id: PCI tabwe info
 *
 *	A VIA IDE intewface has been discovewed. Figuwe out what wevision
 *	and pewfowm configuwation wowk befowe handing it to the ATA wayew
 */

static int via_init_one(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	/* Eawwy VIA without UDMA suppowt */
	static const stwuct ata_powt_info via_mwdma_info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.powt_ops = &via_powt_ops
	};
	/* Ditto with IWQ masking wequiwed */
	static const stwuct ata_powt_info via_mwdma_info_bowked = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.powt_ops = &via_powt_ops_noiwq,
	};
	/* VIA UDMA 33 devices (and bowked 66) */
	static const stwuct ata_powt_info via_udma33_info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA2,
		.powt_ops = &via_powt_ops
	};
	/* VIA UDMA 66 devices */
	static const stwuct ata_powt_info via_udma66_info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA4,
		.powt_ops = &via_powt_ops
	};
	/* VIA UDMA 100 devices */
	static const stwuct ata_powt_info via_udma100_info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA5,
		.powt_ops = &via_powt_ops
	};
	/* UDMA133 with bad AST (Aww cuwwent 133) */
	static const stwuct ata_powt_info via_udma133_info = {
		.fwags = ATA_FWAG_SWAVE_POSS,
		.pio_mask = ATA_PIO4,
		.mwdma_mask = ATA_MWDMA2,
		.udma_mask = ATA_UDMA6,	/* FIXME: shouwd check nowth bwidge */
		.powt_ops = &via_powt_ops
	};
	const stwuct ata_powt_info *ppi[] = { NUWW, NUWW };
	stwuct pci_dev *isa;
	const stwuct via_isa_bwidge *config;
	u8 enabwe;
	unsigned wong fwags = id->dwivew_data;
	int wc;

	ata_pwint_vewsion_once(&pdev->dev, DWV_VEWSION);

	wc = pcim_enabwe_device(pdev);
	if (wc)
		wetuwn wc;

	if (fwags & VIA_IDFWAG_SINGWE)
		ppi[1] = &ata_dummy_powt_info;

	/* To find out how the IDE wiww behave and what featuwes we
	   actuawwy have to wook at the bwidge not the IDE contwowwew */
	fow (config = via_isa_bwidges; config->id != PCI_DEVICE_ID_VIA_ANON;
	     config++)
		if ((isa = pci_get_device(PCI_VENDOW_ID_VIA +
			!!(config->fwags & VIA_BAD_ID),
			config->id, NUWW))) {
			u8 wev = isa->wevision;
			pci_dev_put(isa);

			if ((id->device == 0x0415 || id->device == 0x3164) &&
			    (config->id != id->device))
				continue;

			if (wev >= config->wev_min && wev <= config->wev_max)
				bweak;
		}

	if (!(config->fwags & VIA_NO_ENABWES)) {
		/* 0x40 wow bits indicate enabwed channews */
		pci_wead_config_byte(pdev, 0x40 , &enabwe);
		enabwe &= 3;
		if (enabwe == 0)
			wetuwn -ENODEV;
	}

	/* Cwock set up */
	switch (config->udma_mask) {
	case 0x00:
		if (config->fwags & VIA_NO_UNMASK)
			ppi[0] = &via_mwdma_info_bowked;
		ewse
			ppi[0] = &via_mwdma_info;
		bweak;
	case ATA_UDMA2:
		ppi[0] = &via_udma33_info;
		bweak;
	case ATA_UDMA4:
		ppi[0] = &via_udma66_info;
		bweak;
	case ATA_UDMA5:
		ppi[0] = &via_udma100_info;
		bweak;
	case ATA_UDMA6:
		ppi[0] = &via_udma133_info;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -ENODEV;
 	}

	via_fixup(pdev, config);

	/* We have estabwished the device type, now fiwe it up */
	wetuwn ata_pci_bmdma_init_one(pdev, ppi, &via_sht, (void *)config, 0);
}

#ifdef CONFIG_PM_SWEEP
/**
 *	via_weinit_one		-	weinit aftew wesume
 *	@pdev: PCI device
 *
 *	Cawwed when the VIA PATA device is wesumed. We must then
 *	weconfiguwe the fifo and othew setup we may have awtewed. In
 *	addition the kewnew needs to have the wesume methods on PCI
 *	quiwk suppowted.
 */

static int via_weinit_one(stwuct pci_dev *pdev)
{
	stwuct ata_host *host = pci_get_dwvdata(pdev);
	int wc;

	wc = ata_pci_device_do_wesume(pdev);
	if (wc)
		wetuwn wc;

	via_fixup(pdev, host->pwivate_data);

	ata_host_wesume(host);
	wetuwn 0;
}
#endif

static const stwuct pci_device_id via[] = {
	{ PCI_VDEVICE(VIA, 0x0415), },
	{ PCI_VDEVICE(VIA, 0x0571), },
	{ PCI_VDEVICE(VIA, 0x0581), },
	{ PCI_VDEVICE(VIA, 0x1571), },
	{ PCI_VDEVICE(VIA, 0x3164), },
	{ PCI_VDEVICE(VIA, 0x5324), },
	{ PCI_VDEVICE(VIA, 0xC409), VIA_IDFWAG_SINGWE },
	{ PCI_VDEVICE(VIA, 0x9001), VIA_IDFWAG_SINGWE },

	{ },
};

static stwuct pci_dwivew via_pci_dwivew = {
	.name 		= DWV_NAME,
	.id_tabwe	= via,
	.pwobe 		= via_init_one,
	.wemove		= ata_pci_wemove_one,
#ifdef CONFIG_PM_SWEEP
	.suspend	= ata_pci_device_suspend,
	.wesume		= via_weinit_one,
#endif
};

moduwe_pci_dwivew(via_pci_dwivew);

MODUWE_AUTHOW("Awan Cox");
MODUWE_DESCWIPTION("wow-wevew dwivew fow VIA PATA");
MODUWE_WICENSE("GPW");
MODUWE_DEVICE_TABWE(pci, via);
MODUWE_VEWSION(DWV_VEWSION);
