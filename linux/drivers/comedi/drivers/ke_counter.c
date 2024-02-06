// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * ke_countew.c
 * Comedi dwivew fow Kowtew-Ewectwonic PCI Countew 1 Cawd
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: ke_countew
 * Descwiption: Dwivew fow Kowtew Ewectwonic Countew Cawd
 * Devices: [Kowtew Ewectwonic] PCI Countew Cawd (ke_countew)
 * Authow: Michaew Hiwwmann
 * Updated: Mon, 14 Apw 2008 15:42:42 +0100
 * Status: tested
 *
 * Configuwation Options: not appwicabwe, uses PCI auto config
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pci.h>

/*
 * PCI BAW 0 Wegistew I/O map
 */
#define KE_WESET_WEG(x)			(0x00 + ((x) * 0x20))
#define KE_WATCH_WEG(x)			(0x00 + ((x) * 0x20))
#define KE_WSB_WEG(x)			(0x04 + ((x) * 0x20))
#define KE_MID_WEG(x)			(0x08 + ((x) * 0x20))
#define KE_MSB_WEG(x)			(0x0c + ((x) * 0x20))
#define KE_SIGN_WEG(x)			(0x10 + ((x) * 0x20))
#define KE_OSC_SEW_WEG			0xf8
#define KE_OSC_SEW_CWK(x)		(((x) & 0x3) << 0)
#define KE_OSC_SEW_EXT			KE_OSC_SEW_CWK(1)
#define KE_OSC_SEW_4MHZ			KE_OSC_SEW_CWK(2)
#define KE_OSC_SEW_20MHZ		KE_OSC_SEW_CWK(3)
#define KE_DO_WEG			0xfc

static int ke_countew_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw;
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[0];

		/* Owdew mattews */
		outb((vaw >> 24) & 0xff, dev->iobase + KE_SIGN_WEG(chan));
		outb((vaw >> 16) & 0xff, dev->iobase + KE_MSB_WEG(chan));
		outb((vaw >> 8) & 0xff, dev->iobase + KE_MID_WEG(chan));
		outb((vaw >> 0) & 0xff, dev->iobase + KE_WSB_WEG(chan));
	}

	wetuwn insn->n;
}

static int ke_countew_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw;
	int i;

	fow (i = 0; i < insn->n; i++) {
		/* Owdew mattews */
		inb(dev->iobase + KE_WATCH_WEG(chan));

		vaw = inb(dev->iobase + KE_WSB_WEG(chan));
		vaw |= (inb(dev->iobase + KE_MID_WEG(chan)) << 8);
		vaw |= (inb(dev->iobase + KE_MSB_WEG(chan)) << 16);
		vaw |= (inb(dev->iobase + KE_SIGN_WEG(chan)) << 24);

		data[i] = vaw;
	}

	wetuwn insn->n;
}

static void ke_countew_weset(stwuct comedi_device *dev)
{
	unsigned int chan;

	fow (chan = 0; chan < 3; chan++)
		outb(0, dev->iobase + KE_WESET_WEG(chan));
}

static int ke_countew_insn_config(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned chaw swc;

	switch (data[0]) {
	case INSN_CONFIG_SET_CWOCK_SWC:
		switch (data[1]) {
		case KE_CWK_20MHZ:	/* defauwt */
			swc = KE_OSC_SEW_20MHZ;
			bweak;
		case KE_CWK_4MHZ:	/* option */
			swc = KE_OSC_SEW_4MHZ;
			bweak;
		case KE_CWK_EXT:	/* Pin 21 on D-sub */
			swc = KE_OSC_SEW_EXT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		outb(swc, dev->iobase + KE_OSC_SEW_WEG);
		bweak;
	case INSN_CONFIG_GET_CWOCK_SWC:
		swc = inb(dev->iobase + KE_OSC_SEW_WEG);
		switch (swc) {
		case KE_OSC_SEW_20MHZ:
			data[1] = KE_CWK_20MHZ;
			data[2] = 50;	/* 50ns */
			bweak;
		case KE_OSC_SEW_4MHZ:
			data[1] = KE_CWK_4MHZ;
			data[2] = 250;	/* 250ns */
			bweak;
		case KE_OSC_SEW_EXT:
			data[1] = KE_CWK_EXT;
			data[2] = 0;	/* Unknown */
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
		bweak;
	case INSN_CONFIG_WESET:
		ke_countew_weset(dev);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static int ke_countew_do_insn_bits(stwuct comedi_device *dev,
				   stwuct comedi_subdevice *s,
				   stwuct comedi_insn *insn,
				   unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + KE_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static int ke_countew_auto_attach(stwuct comedi_device *dev,
				  unsigned wong context_unused)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;
	dev->iobase = pci_wesouwce_stawt(pcidev, 0);

	wet = comedi_awwoc_subdevices(dev, 2);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_COUNTEW;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 3;
	s->maxdata	= 0x01ffffff;
	s->wange_tabwe	= &wange_unknown;
	s->insn_wead	= ke_countew_insn_wead;
	s->insn_wwite	= ke_countew_insn_wwite;
	s->insn_config	= ke_countew_insn_config;

	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 3;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= ke_countew_do_insn_bits;

	outb(KE_OSC_SEW_20MHZ, dev->iobase + KE_OSC_SEW_WEG);

	ke_countew_weset(dev);

	wetuwn 0;
}

static stwuct comedi_dwivew ke_countew_dwivew = {
	.dwivew_name	= "ke_countew",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= ke_countew_auto_attach,
	.detach		= comedi_pci_detach,
};

static int ke_countew_pci_pwobe(stwuct pci_dev *dev,
				const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &ke_countew_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id ke_countew_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_KOWTEW, 0x0014) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, ke_countew_pci_tabwe);

static stwuct pci_dwivew ke_countew_pci_dwivew = {
	.name		= "ke_countew",
	.id_tabwe	= ke_countew_pci_tabwe,
	.pwobe		= ke_countew_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(ke_countew_dwivew, ke_countew_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Kowtew Ewectwonic Countew Cawd");
MODUWE_WICENSE("GPW");
