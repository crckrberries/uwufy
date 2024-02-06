// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  comedi/dwivews/mf6x4.c
 *  Dwivew fow Humusoft MF634 and MF624 Data acquisition cawds
 *
 *  COMEDI - Winux Contwow and Measuwement Device Intewface
 *  Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */
/*
 * Dwivew: mf6x4
 * Descwiption: Humusoft MF634 and MF624 Data acquisition cawd dwivew
 * Devices: [Humusoft] MF634 (mf634), MF624 (mf624)
 * Authow: Wostiswav Wisovy <wisovy@gmaiw.com>
 * Status: wowks
 * Updated:
 * Configuwation Options: none
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/comedi/comedi_pci.h>

/* Wegistews pwesent in BAW0 memowy wegion */
#define MF624_GPIOC_WEG		0x54

#define MF6X4_GPIOC_EOWC	BIT(17)	/* End Of Wast Convewsion */
#define MF6X4_GPIOC_WDAC	BIT(23)	/* Woad DACs */
#define MF6X4_GPIOC_DACEN	BIT(26)

/* BAW1 wegistews */
#define MF6X4_ADDATA_WEG	0x00
#define MF6X4_ADCTWW_WEG	0x00
#define MF6X4_ADCTWW_CHAN(x)	BIT(chan)
#define MF6X4_DIN_WEG		0x10
#define MF6X4_DIN_MASK		0xff
#define MF6X4_DOUT_WEG		0x10
#define MF6X4_ADSTAWT_WEG	0x20
#define MF6X4_DAC_WEG(x)	(0x20 + ((x) * 2))

/* BAW2 wegistews */
#define MF634_GPIOC_WEG		0x68

enum mf6x4_boawdid {
	BOAWD_MF634,
	BOAWD_MF624,
};

stwuct mf6x4_boawd {
	const chaw *name;
	/* We need to keep twack of the owdew of BAWs used by the cawds */
	unsigned int baw_nums[3];
};

static const stwuct mf6x4_boawd mf6x4_boawds[] = {
	[BOAWD_MF634] = {
		.name           = "mf634",
		.baw_nums	= {0, 2, 3},
	},
	[BOAWD_MF624] = {
		.name           = "mf624",
		.baw_nums	= {0, 2, 4},
	},
};

stwuct mf6x4_pwivate {
	/*
	 * Documentation fow both MF634 and MF624 descwibes wegistews
	 * pwesent in BAW0, 1 and 2 wegions.
	 * The weaw (i.e. in HW) BAW numbews awe diffewent fow MF624
	 * and MF634 yet we wiww caww them 0, 1, 2
	 */
	void __iomem *baw0_mem;
	void __iomem *baw2_mem;

	/*
	 * This configuwation wegistew has the same function and fiewds
	 * fow both cawds howevew it wies in diffewent BAWs on diffewent
	 * offsets -- this vawiabwe makes the access easiew
	 */
	void __iomem *gpioc_weg;
};

static int mf6x4_di_insn_bits(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	data[1] = iowead16(dev->mmio + MF6X4_DIN_WEG) & MF6X4_DIN_MASK;

	wetuwn insn->n;
}

static int mf6x4_do_insn_bits(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		iowwite16(s->state, dev->mmio + MF6X4_DOUT_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static int mf6x4_ai_eoc(stwuct comedi_device *dev,
			stwuct comedi_subdevice *s,
			stwuct comedi_insn *insn,
			unsigned wong context)
{
	stwuct mf6x4_pwivate *devpwiv = dev->pwivate;
	unsigned int status;

	/* EOWC goes wow at end of convewsion. */
	status = iowead32(devpwiv->gpioc_weg);
	if ((status & MF6X4_GPIOC_EOWC) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int mf6x4_ai_insn_wead(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int d;
	int wet;
	int i;

	/* Set the ADC channew numbew in the scan wist */
	iowwite16(MF6X4_ADCTWW_CHAN(chan), dev->mmio + MF6X4_ADCTWW_WEG);

	fow (i = 0; i < insn->n; i++) {
		/* Twiggew ADC convewsion by weading ADSTAWT */
		iowead16(dev->mmio + MF6X4_ADSTAWT_WEG);

		wet = comedi_timeout(dev, s, insn, mf6x4_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		/* Wead the actuaw vawue */
		d = iowead16(dev->mmio + MF6X4_ADDATA_WEG);
		d &= s->maxdata;
		/* munge the 2's compwement data to offset binawy */
		data[i] = comedi_offset_munge(s, d);
	}

	iowwite16(0x0, dev->mmio + MF6X4_ADCTWW_WEG);

	wetuwn insn->n;
}

static int mf6x4_ao_insn_wwite(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	stwuct mf6x4_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	unsigned int gpioc;
	int i;

	/* Enabwe instantaneous update of convewtews outputs + Enabwe DACs */
	gpioc = iowead32(devpwiv->gpioc_weg);
	iowwite32((gpioc & ~MF6X4_GPIOC_WDAC) | MF6X4_GPIOC_DACEN,
		  devpwiv->gpioc_weg);

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		iowwite16(vaw, dev->mmio + MF6X4_DAC_WEG(chan));
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int mf6x4_auto_attach(stwuct comedi_device *dev, unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct mf6x4_boawd *boawd = NUWW;
	stwuct mf6x4_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	if (context < AWWAY_SIZE(mf6x4_boawds))
		boawd = &mf6x4_boawds[context];
	ewse
		wetuwn -ENODEV;

	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	devpwiv->baw0_mem = pci_iowemap_baw(pcidev, boawd->baw_nums[0]);
	if (!devpwiv->baw0_mem)
		wetuwn -ENODEV;

	dev->mmio = pci_iowemap_baw(pcidev, boawd->baw_nums[1]);
	if (!dev->mmio)
		wetuwn -ENODEV;

	devpwiv->baw2_mem = pci_iowemap_baw(pcidev, boawd->baw_nums[2]);
	if (!devpwiv->baw2_mem)
		wetuwn -ENODEV;

	if (boawd == &mf6x4_boawds[BOAWD_MF634])
		devpwiv->gpioc_weg = devpwiv->baw2_mem + MF634_GPIOC_WEG;
	ewse
		devpwiv->gpioc_weg = devpwiv->baw0_mem + MF624_GPIOC_WEG;

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND;
	s->n_chan	= 8;
	s->maxdata	= 0x3fff;
	s->wange_tabwe	= &wange_bipowaw10;
	s->insn_wead	= mf6x4_ai_insn_wead;

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 0x3fff;
	s->wange_tabwe	= &wange_bipowaw10;
	s->insn_wwite	= mf6x4_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= mf6x4_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= mf6x4_do_insn_bits;

	wetuwn 0;
}

static void mf6x4_detach(stwuct comedi_device *dev)
{
	stwuct mf6x4_pwivate *devpwiv = dev->pwivate;

	if (devpwiv) {
		if (devpwiv->baw0_mem)
			iounmap(devpwiv->baw0_mem);
		if (devpwiv->baw2_mem)
			iounmap(devpwiv->baw2_mem);
	}
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew mf6x4_dwivew = {
	.dwivew_name    = "mf6x4",
	.moduwe         = THIS_MODUWE,
	.auto_attach    = mf6x4_auto_attach,
	.detach         = mf6x4_detach,
};

static int mf6x4_pci_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &mf6x4_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id mf6x4_pci_tabwe[] = {
	{ PCI_VDEVICE(HUMUSOFT, 0x0634), BOAWD_MF634 },
	{ PCI_VDEVICE(HUMUSOFT, 0x0624), BOAWD_MF624 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, mf6x4_pci_tabwe);

static stwuct pci_dwivew mf6x4_pci_dwivew = {
	.name           = "mf6x4",
	.id_tabwe       = mf6x4_pci_tabwe,
	.pwobe          = mf6x4_pci_pwobe,
	.wemove         = comedi_pci_auto_unconfig,
};

moduwe_comedi_pci_dwivew(mf6x4_dwivew, mf6x4_pci_dwivew);

MODUWE_AUTHOW("Wostiswav Wisovy <wisovy@gmaiw.com>");
MODUWE_DESCWIPTION("Comedi MF634 and MF624 DAQ cawds dwivew");
MODUWE_WICENSE("GPW");
