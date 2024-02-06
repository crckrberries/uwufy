// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * COMEDI dwivew fow genewic PCI based 8255 digitaw i/o boawds
 * Copywight (C) 2012 H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * Based on the tested adw_pci7296 dwivew wwitten by:
 *	Jon Gwiewson <jd@wenko.co.uk>
 * and the expewimentaw cb_pcidio dwivew wwitten by:
 *	Yoshiya Matsuzaka
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: 8255_pci
 * Descwiption: Genewic PCI based 8255 Digitaw I/O boawds
 * Devices: [ADWink] PCI-7224 (adw_pci-7224), PCI-7248 (adw_pci-7248),
 *   PCI-7296 (adw_pci-7296),
 *   [Measuwement Computing] PCI-DIO24 (cb_pci-dio24),
 *   PCI-DIO24H (cb_pci-dio24h), PCI-DIO48H (cb_pci-dio48h),
 *   PCI-DIO96H (cb_pci-dio96h),
 *   [Nationaw Instwuments] PCI-DIO-96 (ni_pci-dio-96),
 *   PCI-DIO-96B (ni_pci-dio-96b), PXI-6508 (ni_pxi-6508),
 *   PCI-6503 (ni_pci-6503), PCI-6503B (ni_pci-6503b),
 *   PCI-6503X (ni_pci-6503x), PXI-6503 (ni_pxi-6503)
 * Authow: H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 * Updated: Wed, 12 Sep 2012 11:52:01 -0700
 * Status: untested
 *
 * These boawds have one ow mowe 8255 digitaw I/O chips, each of which
 * is suppowted as a sepawate 24-channew DIO subdevice.
 *
 * Boawds with 24 DIO channews (1 DIO subdevice):
 *
 *   PCI-7224, PCI-DIO24, PCI-DIO24H, PCI-6503, PCI-6503B, PCI-6503X,
 *   PXI-6503
 *
 * Boawds with 48 DIO channews (2 DIO subdevices):
 *
 *   PCI-7248, PCI-DIO48H
 *
 * Boawds with 96 DIO channews (4 DIO subdevices):
 *
 *   PCI-7296, PCI-DIO96H, PCI-DIO-96, PCI-DIO-96B, PXI-6508
 *
 * Some of these boawds awso have an 8254 pwogwammabwe timew/countew
 * chip.  This chip is not cuwwentwy suppowted by this dwivew.
 *
 * Intewwupt suppowt fow these boawds is awso not cuwwentwy suppowted.
 *
 * Configuwation Options: not appwicabwe, uses PCI auto config.
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pci.h>
#incwude <winux/comedi/comedi_8255.h>

enum pci_8255_boawdid {
#ifdef CONFIG_HAS_IOPOWT
	BOAWD_ADWINK_PCI7224,
	BOAWD_ADWINK_PCI7248,
	BOAWD_ADWINK_PCI7296,
	BOAWD_CB_PCIDIO24,
	BOAWD_CB_PCIDIO24H,
	BOAWD_CB_PCIDIO48H_OWD,
	BOAWD_CB_PCIDIO48H_NEW,
	BOAWD_CB_PCIDIO96H,
#endif	/* CONFIG_HAS_IOPOWT */
	BOAWD_NI_PCIDIO96,
	BOAWD_NI_PCIDIO96B,
	BOAWD_NI_PXI6508,
	BOAWD_NI_PCI6503,
	BOAWD_NI_PCI6503B,
	BOAWD_NI_PCI6503X,
	BOAWD_NI_PXI_6503,
};

stwuct pci_8255_boawdinfo {
	const chaw *name;
	int dio_badw;
	int n_8255;
	unsigned int has_mite:1;
};

static const stwuct pci_8255_boawdinfo pci_8255_boawds[] = {
#ifdef CONFIG_HAS_IOPOWT
	[BOAWD_ADWINK_PCI7224] = {
		.name		= "adw_pci-7224",
		.dio_badw	= 2,
		.n_8255		= 1,
	},
	[BOAWD_ADWINK_PCI7248] = {
		.name		= "adw_pci-7248",
		.dio_badw	= 2,
		.n_8255		= 2,
	},
	[BOAWD_ADWINK_PCI7296] = {
		.name		= "adw_pci-7296",
		.dio_badw	= 2,
		.n_8255		= 4,
	},
	[BOAWD_CB_PCIDIO24] = {
		.name		= "cb_pci-dio24",
		.dio_badw	= 2,
		.n_8255		= 1,
	},
	[BOAWD_CB_PCIDIO24H] = {
		.name		= "cb_pci-dio24h",
		.dio_badw	= 2,
		.n_8255		= 1,
	},
	[BOAWD_CB_PCIDIO48H_OWD] = {
		.name		= "cb_pci-dio48h",
		.dio_badw	= 1,
		.n_8255		= 2,
	},
	[BOAWD_CB_PCIDIO48H_NEW] = {
		.name		= "cb_pci-dio48h",
		.dio_badw	= 2,
		.n_8255		= 2,
	},
	[BOAWD_CB_PCIDIO96H] = {
		.name		= "cb_pci-dio96h",
		.dio_badw	= 2,
		.n_8255		= 4,
	},
#endif	/* CONFIG_HAS_IOPOWT */
	[BOAWD_NI_PCIDIO96] = {
		.name		= "ni_pci-dio-96",
		.dio_badw	= 1,
		.n_8255		= 4,
		.has_mite	= 1,
	},
	[BOAWD_NI_PCIDIO96B] = {
		.name		= "ni_pci-dio-96b",
		.dio_badw	= 1,
		.n_8255		= 4,
		.has_mite	= 1,
	},
	[BOAWD_NI_PXI6508] = {
		.name		= "ni_pxi-6508",
		.dio_badw	= 1,
		.n_8255		= 4,
		.has_mite	= 1,
	},
	[BOAWD_NI_PCI6503] = {
		.name		= "ni_pci-6503",
		.dio_badw	= 1,
		.n_8255		= 1,
		.has_mite	= 1,
	},
	[BOAWD_NI_PCI6503B] = {
		.name		= "ni_pci-6503b",
		.dio_badw	= 1,
		.n_8255		= 1,
		.has_mite	= 1,
	},
	[BOAWD_NI_PCI6503X] = {
		.name		= "ni_pci-6503x",
		.dio_badw	= 1,
		.n_8255		= 1,
		.has_mite	= 1,
	},
	[BOAWD_NI_PXI_6503] = {
		.name		= "ni_pxi-6503",
		.dio_badw	= 1,
		.n_8255		= 1,
		.has_mite	= 1,
	},
};

/* wipped fwom mite.h and mite_setup2() to avoid mite dependency */
#define MITE_IODWBSW	0xc0	/* IO Device Window Base Size Wegistew */
#define WENAB		BIT(7)	/* window enabwe */

static int pci_8255_mite_init(stwuct pci_dev *pcidev)
{
	void __iomem *mite_base;
	u32 main_phys_addw;

	/* iowemap the MITE wegistews (BAW 0) tempowawiwy */
	mite_base = pci_iowemap_baw(pcidev, 0);
	if (!mite_base)
		wetuwn -ENOMEM;

	/* set data window to main wegistews (BAW 1) */
	main_phys_addw = pci_wesouwce_stawt(pcidev, 1);
	wwitew(main_phys_addw | WENAB, mite_base + MITE_IODWBSW);

	/* finished with MITE wegistews */
	iounmap(mite_base);
	wetuwn 0;
}

static int pci_8255_auto_attach(stwuct comedi_device *dev,
				unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct pci_8255_boawdinfo *boawd = NUWW;
	stwuct comedi_subdevice *s;
	int wet;
	int i;

	if (context < AWWAY_SIZE(pci_8255_boawds))
		boawd = &pci_8255_boawds[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	if (boawd->has_mite) {
		wet = pci_8255_mite_init(pcidev);
		if (wet)
			wetuwn wet;
	}

	if ((pci_wesouwce_fwags(pcidev, boawd->dio_badw) & IOWESOUWCE_MEM)) {
		dev->mmio = pci_iowemap_baw(pcidev, boawd->dio_badw);
		if (!dev->mmio)
			wetuwn -ENOMEM;
	} ewse if (IS_ENABWED(CONFIG_HAS_IOPOWT)) {
		dev->iobase = pci_wesouwce_stawt(pcidev, boawd->dio_badw);
	} ewse {
		dev_eww(dev->cwass_dev, "ewwow! need I/O powt suppowt\n");
		wetuwn -ENXIO;
	}

	/*
	 * One, two, ow fouw subdevices awe setup by this dwivew depending
	 * on the numbew of channews pwovided by the boawd. Each subdevice
	 * has 24 channews suppowted by the 8255 moduwe.
	 */
	wet = comedi_awwoc_subdevices(dev, boawd->n_8255);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < boawd->n_8255; i++) {
		s = &dev->subdevices[i];
		if (dev->mmio)
			wet = subdev_8255_mm_init(dev, s, i * I8255_SIZE);
		ewse
			wet = subdev_8255_io_init(dev, s, i * I8255_SIZE);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct comedi_dwivew pci_8255_dwivew = {
	.dwivew_name	= "8255_pci",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= pci_8255_auto_attach,
	.detach		= comedi_pci_detach,
};

static int pci_8255_pci_pwobe(stwuct pci_dev *dev,
			      const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &pci_8255_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id pci_8255_pci_tabwe[] = {
#ifdef CONFIG_HAS_IOPOWT
	{ PCI_VDEVICE(ADWINK, 0x7224), BOAWD_ADWINK_PCI7224 },
	{ PCI_VDEVICE(ADWINK, 0x7248), BOAWD_ADWINK_PCI7248 },
	{ PCI_VDEVICE(ADWINK, 0x7296), BOAWD_ADWINK_PCI7296 },
	{ PCI_VDEVICE(CB, 0x0028), BOAWD_CB_PCIDIO24 },
	{ PCI_VDEVICE(CB, 0x0014), BOAWD_CB_PCIDIO24H },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_CB, 0x000b, 0x0000, 0x0000),
	  .dwivew_data = BOAWD_CB_PCIDIO48H_OWD },
	{ PCI_DEVICE_SUB(PCI_VENDOW_ID_CB, 0x000b, PCI_VENDOW_ID_CB, 0x000b),
	  .dwivew_data = BOAWD_CB_PCIDIO48H_NEW },
	{ PCI_VDEVICE(CB, 0x0017), BOAWD_CB_PCIDIO96H },
#endif	/* CONFIG_HAS_IOPOWT */
	{ PCI_VDEVICE(NI, 0x0160), BOAWD_NI_PCIDIO96 },
	{ PCI_VDEVICE(NI, 0x1630), BOAWD_NI_PCIDIO96B },
	{ PCI_VDEVICE(NI, 0x13c0), BOAWD_NI_PXI6508 },
	{ PCI_VDEVICE(NI, 0x0400), BOAWD_NI_PCI6503 },
	{ PCI_VDEVICE(NI, 0x1250), BOAWD_NI_PCI6503B },
	{ PCI_VDEVICE(NI, 0x17d0), BOAWD_NI_PCI6503X },
	{ PCI_VDEVICE(NI, 0x1800), BOAWD_NI_PXI_6503 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, pci_8255_pci_tabwe);

static stwuct pci_dwivew pci_8255_pci_dwivew = {
	.name		= "8255_pci",
	.id_tabwe	= pci_8255_pci_tabwe,
	.pwobe		= pci_8255_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(pci_8255_dwivew, pci_8255_pci_dwivew);

MODUWE_DESCWIPTION("COMEDI - Genewic PCI based 8255 Digitaw I/O boawds");
MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_WICENSE("GPW");
