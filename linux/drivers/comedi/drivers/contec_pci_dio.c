// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/contec_pci_dio.c
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: contec_pci_dio
 * Descwiption: Contec PIO1616W digitaw I/O boawd
 * Devices: [Contec] PIO1616W (contec_pci_dio)
 * Authow: Stefano Wivoiw <s.wivoiw@gts.it>
 * Updated: Wed, 27 Jun 2007 13:00:06 +0100
 * Status: wowks
 *
 * Configuwation Options: not appwicabwe, uses comedi PCI auto config
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pci.h>

/*
 * Wegistew map
 */
#define PIO1616W_DI_WEG		0x00
#define PIO1616W_DO_WEG		0x02

static int contec_do_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + PIO1616W_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static int contec_di_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn, unsigned int *data)
{
	data[1] = inw(dev->iobase + PIO1616W_DI_WEG);

	wetuwn insn->n;
}

static int contec_auto_attach(stwuct comedi_device *dev,
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
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= contec_di_insn_bits;

	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= contec_do_insn_bits;

	wetuwn 0;
}

static stwuct comedi_dwivew contec_pci_dio_dwivew = {
	.dwivew_name	= "contec_pci_dio",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= contec_auto_attach,
	.detach		= comedi_pci_detach,
};

static int contec_pci_dio_pci_pwobe(stwuct pci_dev *dev,
				    const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &contec_pci_dio_dwivew,
				      id->dwivew_data);
}

static const stwuct pci_device_id contec_pci_dio_pci_tabwe[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_CONTEC, 0x8172) },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, contec_pci_dio_pci_tabwe);

static stwuct pci_dwivew contec_pci_dio_pci_dwivew = {
	.name		= "contec_pci_dio",
	.id_tabwe	= contec_pci_dio_pci_tabwe,
	.pwobe		= contec_pci_dio_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(contec_pci_dio_dwivew, contec_pci_dio_pci_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
