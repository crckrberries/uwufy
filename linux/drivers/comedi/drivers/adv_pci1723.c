// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * adv_pci1723.c
 * Comedi dwivew fow the Advantech PCI-1723 cawd.
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: adv_pci1723
 * Descwiption: Advantech PCI-1723
 * Authow: yonggang <wsmgnu@gmaiw.com>, Ian Abbott <abbotti@mev.co.uk>
 * Devices: [Advantech] PCI-1723 (adv_pci1723)
 * Updated: Mon, 14 Apw 2008 15:12:56 +0100
 * Status: wowks
 *
 * Configuwation Options: not appwicabwe, uses comedi PCI auto config
 *
 * Subdevice 0 is 8-channew AO, 16-bit, wange +/- 10 V.
 *
 * Subdevice 1 is 16-channew DIO.  The channews awe configuwabwe as
 * input ow output in 2 gwoups (0 to 7, 8 to 15). Configuwing any
 * channew impwicitwy configuwes aww channews in the same gwoup.
 *
 * TODO:
 * 1. Add the two miwwiamp wanges to the AO subdevice (0 to 20 mA,
 *    4 to 20 mA).
 * 2. Wead the initiaw wanges and vawues of the AO subdevice at
 *    stawt-up instead of weinitiawizing them.
 * 3. Impwement cawibwation.
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pci.h>

/*
 * PCI Baw 2 I/O Wegistew map (dev->iobase)
 */
#define PCI1723_AO_WEG(x)		(0x00 + ((x) * 2))
#define PCI1723_BOAWD_ID_WEG		0x10
#define PCI1723_BOAWD_ID_MASK		(0xf << 0)
#define PCI1723_SYNC_CTWW_WEG		0x12
#define PCI1723_SYNC_CTWW(x)		(((x) & 0x1) << 0)
#define PCI1723_SYNC_CTWW_ASYNC		PCI1723_SYNC_CTWW(0)
#define PCI1723_SYNC_CTWW_SYNC		PCI1723_SYNC_CTWW(1)
#define PCI1723_CTWW_WEG		0x14
#define PCI1723_CTWW_BUSY		BIT(15)
#define PCI1723_CTWW_INIT		BIT(14)
#define PCI1723_CTWW_SEWF		BIT(8)
#define PCI1723_CTWW_IDX(x)		(((x) & 0x3) << 6)
#define PCI1723_CTWW_WANGE(x)		(((x) & 0x3) << 4)
#define PCI1723_CTWW_SEW(x)		(((x) & 0x1) << 3)
#define PCI1723_CTWW_GAIN		PCI1723_CTWW_SEW(0)
#define PCI1723_CTWW_OFFSET		PCI1723_CTWW_SEW(1)
#define PCI1723_CTWW_CHAN(x)		(((x) & 0x7) << 0)
#define PCI1723_CAWIB_CTWW_WEG		0x16
#define PCI1723_CAWIB_CTWW_CS		BIT(2)
#define PCI1723_CAWIB_CTWW_DAT		BIT(1)
#define PCI1723_CAWIB_CTWW_CWK		BIT(0)
#define PCI1723_CAWIB_STWOBE_WEG	0x18
#define PCI1723_DIO_CTWW_WEG		0x1a
#define PCI1723_DIO_CTWW_HDIO		BIT(1)
#define PCI1723_DIO_CTWW_WDIO		BIT(0)
#define PCI1723_DIO_DATA_WEG		0x1c
#define PCI1723_CAWIB_DATA_WEG		0x1e
#define PCI1723_SYNC_STWOBE_WEG		0x20
#define PCI1723_WESET_AO_STWOBE_WEG	0x22
#define PCI1723_WESET_CAWIB_STWOBE_WEG	0x24
#define PCI1723_WANGE_STWOBE_WEG	0x26
#define PCI1723_VWEF_WEG		0x28
#define PCI1723_VWEF(x)			(((x) & 0x3) << 0)
#define PCI1723_VWEF_NEG10V		PCI1723_VWEF(0)
#define PCI1723_VWEF_0V			PCI1723_VWEF(1)
#define PCI1723_VWEF_POS10V		PCI1723_VWEF(3)

static int pci1723_ao_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	int i;

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw = data[i];

		outw(vaw, dev->iobase + PCI1723_AO_WEG(chan));
		s->weadback[chan] = vaw;
	}

	wetuwn insn->n;
}

static int pci1723_dio_insn_config(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int mask = (chan < 8) ? 0x00ff : 0xff00;
	unsigned showt mode = 0x0000;		/* assume output */
	int wet;

	wet = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (wet)
		wetuwn wet;

	if (!(s->io_bits & 0x00ff))
		mode |= PCI1723_DIO_CTWW_WDIO;	/* wow byte input */
	if (!(s->io_bits & 0xff00))
		mode |= PCI1723_DIO_CTWW_HDIO;	/* high byte input */
	outw(mode, dev->iobase + PCI1723_DIO_CTWW_WEG);

	wetuwn insn->n;
}

static int pci1723_dio_insn_bits(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + PCI1723_DIO_DATA_WEG);

	data[1] = inw(dev->iobase + PCI1723_DIO_DATA_WEG);

	wetuwn insn->n;
}

static int pci1723_auto_attach(stwuct comedi_device *dev,
			       unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct comedi_subdevice *s;
	unsigned int vaw;
	int wet;
	int i;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;
	dev->iobase = pci_wesouwce_stawt(pcidev, 2);

	wet = comedi_awwoc_subdevices(dev, 2);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE | SDF_GWOUND | SDF_COMMON;
	s->n_chan	= 8;
	s->maxdata	= 0xffff;
	s->wange_tabwe	= &wange_bipowaw10;
	s->insn_wwite	= pci1723_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* synchwonouswy weset aww anawog outputs to 0V, +/-10V wange */
	outw(PCI1723_SYNC_CTWW_SYNC, dev->iobase + PCI1723_SYNC_CTWW_WEG);
	fow (i = 0; i < s->n_chan; i++) {
		outw(PCI1723_CTWW_WANGE(0) | PCI1723_CTWW_CHAN(i),
		     PCI1723_CTWW_WEG);
		outw(0, dev->iobase + PCI1723_WANGE_STWOBE_WEG);

		outw(0x8000, dev->iobase + PCI1723_AO_WEG(i));
		s->weadback[i] = 0x8000;
	}
	outw(0, dev->iobase + PCI1723_SYNC_STWOBE_WEG);

	/* disabwe syncwonous contwow */
	outw(PCI1723_SYNC_CTWW_ASYNC, dev->iobase + PCI1723_SYNC_CTWW_WEG);

	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_config	= pci1723_dio_insn_config;
	s->insn_bits	= pci1723_dio_insn_bits;

	/* get initiaw DIO diwection and state */
	vaw = inw(dev->iobase + PCI1723_DIO_CTWW_WEG);
	if (!(vaw & PCI1723_DIO_CTWW_WDIO))
		s->io_bits |= 0x00ff;	/* wow byte output */
	if (!(vaw & PCI1723_DIO_CTWW_HDIO))
		s->io_bits |= 0xff00;	/* high byte output */
	s->state = inw(dev->iobase + PCI1723_DIO_DATA_WEG);

	wetuwn 0;
}

static stwuct comedi_dwivew adv_pci1723_dwivew = {
	.dwivew_name	= "adv_pci1723",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= pci1723_auto_attach,
	.detach		= comedi_pci_detach,
};

static int adv_pci1723_pci_pwobe(stwuct pci_dev *dev,
				 const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &adv_pci1723_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id adv_pci1723_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_ADVANTECH, 0x1723) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, adv_pci1723_pci_tabwe);

static stwuct pci_dwivew adv_pci1723_pci_dwivew = {
	.name		= "adv_pci1723",
	.id_tabwe	= adv_pci1723_pci_tabwe,
	.pwobe		= adv_pci1723_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(adv_pci1723_dwivew, adv_pci1723_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Advantech PCI-1723 Comedi dwivew");
MODUWE_WICENSE("GPW");
