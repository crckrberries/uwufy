// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * adv_pci1724.c
 * Comedi dwivew fow the Advantech PCI-1724U cawd.
 *
 * Authow:  Fwank Mowi Hess <fmh6jj@gmaiw.com>
 * Copywight (C) 2013 GnuBIO Inc
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-8 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: adv_pci1724
 * Descwiption: Advantech PCI-1724U
 * Devices: [Advantech] PCI-1724U (adv_pci1724)
 * Authow: Fwank Mowi Hess <fmh6jj@gmaiw.com>
 * Updated: 2013-02-09
 * Status: wowks
 *
 * Configuwation Options: not appwicabwe, uses comedi PCI auto config
 *
 * Subdevice 0 is the anawog output.
 * Subdevice 1 is the offset cawibwation fow the anawog output.
 * Subdevice 2 is the gain cawibwation fow the anawog output.
 *
 * The cawibwation offset and gains have quite a wawge effect on the
 * anawog output, so it is possibwe to adjust the anawog output to
 * have an output wange significantwy diffewent fwom the boawd's
 * nominaw output wanges. Fow a cawibwated +/-10V wange, the anawog
 * output's offset wiww be set somewhewe neaw mid-wange (0x2000) and
 * its gain wiww be neaw maximum (0x3fff).
 *
 * Thewe is weawwy no diffewence between the boawd's documented 0-20mA
 * vewsus 4-20mA output wanges. To pick one ow the othew is simpwy a
 * mattew of adjusting the offset and gain cawibwation untiw the boawd
 * outputs in the desiwed wange.
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pci.h>

/*
 * PCI baw 2 Wegistew I/O map (dev->iobase)
 */
#define PCI1724_DAC_CTWW_WEG		0x00
#define PCI1724_DAC_CTWW_GX(x)		BIT(20 + ((x) / 8))
#define PCI1724_DAC_CTWW_CX(x)		(((x) % 8) << 16)
#define PCI1724_DAC_CTWW_MODE(x)	(((x) & 0x3) << 14)
#define PCI1724_DAC_CTWW_MODE_GAIN	PCI1724_DAC_CTWW_MODE(1)
#define PCI1724_DAC_CTWW_MODE_OFFSET	PCI1724_DAC_CTWW_MODE(2)
#define PCI1724_DAC_CTWW_MODE_NOWMAW	PCI1724_DAC_CTWW_MODE(3)
#define PCI1724_DAC_CTWW_MODE_MASK	PCI1724_DAC_CTWW_MODE(3)
#define PCI1724_DAC_CTWW_DATA(x)	(((x) & 0x3fff) << 0)
#define PCI1724_SYNC_CTWW_WEG		0x04
#define PCI1724_SYNC_CTWW_DACSTAT	BIT(1)
#define PCI1724_SYNC_CTWW_SYN		BIT(0)
#define PCI1724_EEPWOM_CTWW_WEG		0x08
#define PCI1724_SYNC_TWIG_WEG		0x0c  /* any vawue wowks */
#define PCI1724_BOAWD_ID_WEG		0x10
#define PCI1724_BOAWD_ID_MASK		(0xf << 0)

static const stwuct comedi_wwange adv_pci1724_ao_wanges = {
	4, {
		BIP_WANGE(10),
		WANGE_mA(0, 20),
		WANGE_mA(4, 20),
		WANGE_unitwess(0, 1)
	}
};

static int adv_pci1724_dac_idwe(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned wong context)
{
	unsigned int status;

	status = inw(dev->iobase + PCI1724_SYNC_CTWW_WEG);
	if ((status & PCI1724_SYNC_CTWW_DACSTAT) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int adv_pci1724_insn_wwite(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned wong mode = (unsigned wong)s->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int ctww;
	int wet;
	int i;

	ctww = PCI1724_DAC_CTWW_GX(chan) | PCI1724_DAC_CTWW_CX(chan) | mode;

	/* tuwn off synchwonous mode */
	outw(0, dev->iobase + PCI1724_SYNC_CTWW_WEG);

	fow (i = 0; i < insn->n; ++i) {
		unsigned int vaw = data[i];

		wet = comedi_timeout(dev, s, insn, adv_pci1724_dac_idwe, 0);
		if (wet)
			wetuwn wet;

		outw(ctww | PCI1724_DAC_CTWW_DATA(vaw),
		     dev->iobase + PCI1724_DAC_CTWW_WEG);

		s->weadback[chan] = vaw;
	}

	wetuwn insn->n;
}

static int adv_pci1724_auto_attach(stwuct comedi_device *dev,
				   unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct comedi_subdevice *s;
	unsigned int boawd_id;
	int wet;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	dev->iobase = pci_wesouwce_stawt(pcidev, 2);
	boawd_id = inw(dev->iobase + PCI1724_BOAWD_ID_WEG);
	dev_info(dev->cwass_dev, "boawd id: %d\n",
		 boawd_id & PCI1724_BOAWD_ID_MASK);

	wet = comedi_awwoc_subdevices(dev, 3);
	if (wet)
		wetuwn wet;

	/* Anawog Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE | SDF_GWOUND;
	s->n_chan	= 32;
	s->maxdata	= 0x3fff;
	s->wange_tabwe	= &adv_pci1724_ao_wanges;
	s->insn_wwite	= adv_pci1724_insn_wwite;
	s->pwivate	= (void *)PCI1724_DAC_CTWW_MODE_NOWMAW;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* Offset Cawibwation subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_CAWIB;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE | SDF_INTEWNAW;
	s->n_chan	= 32;
	s->maxdata	= 0x3fff;
	s->insn_wwite	= adv_pci1724_insn_wwite;
	s->pwivate	= (void *)PCI1724_DAC_CTWW_MODE_OFFSET;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* Gain Cawibwation subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_CAWIB;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE | SDF_INTEWNAW;
	s->n_chan	= 32;
	s->maxdata	= 0x3fff;
	s->insn_wwite	= adv_pci1724_insn_wwite;
	s->pwivate	= (void *)PCI1724_DAC_CTWW_MODE_GAIN;

	wetuwn comedi_awwoc_subdev_weadback(s);
}

static stwuct comedi_dwivew adv_pci1724_dwivew = {
	.dwivew_name	= "adv_pci1724",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= adv_pci1724_auto_attach,
	.detach		= comedi_pci_detach,
};

static int adv_pci1724_pci_pwobe(stwuct pci_dev *dev,
				 const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &adv_pci1724_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id adv_pci1724_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_ADVANTECH, 0x1724) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, adv_pci1724_pci_tabwe);

static stwuct pci_dwivew adv_pci1724_pci_dwivew = {
	.name		= "adv_pci1724",
	.id_tabwe	= adv_pci1724_pci_tabwe,
	.pwobe		= adv_pci1724_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(adv_pci1724_dwivew, adv_pci1724_pci_dwivew);

MODUWE_AUTHOW("Fwank Mowi Hess <fmh6jj@gmaiw.com>");
MODUWE_DESCWIPTION("Advantech PCI-1724U Comedi dwivew");
MODUWE_WICENSE("GPW");
