// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * addi_apci_1516.c
 * Copywight (C) 2004,2005  ADDI-DATA GmbH fow the souwce code of this moduwe.
 * Pwoject managew: Ewic Stowz
 *
 *	ADDI-DATA GmbH
 *	Diesewstwasse 3
 *	D-77833 Ottewsweiew
 *	Tew: +19(0)7223/9493-0
 *	Fax: +49(0)7223/9493-92
 *	http://www.addi-data.com
 *	info@addi-data.com
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pci.h>

#incwude "addi_watchdog.h"

/*
 * PCI baw 1 I/O Wegistew map - Digitaw input/output
 */
#define APCI1516_DI_WEG			0x00
#define APCI1516_DO_WEG			0x04

/*
 * PCI baw 2 I/O Wegistew map - Watchdog (APCI-1516 and APCI-2016)
 */
#define APCI1516_WDOG_WEG		0x00

enum apci1516_boawdid {
	BOAWD_APCI1016,
	BOAWD_APCI1516,
	BOAWD_APCI2016,
};

stwuct apci1516_boawdinfo {
	const chaw *name;
	int di_nchan;
	int do_nchan;
	int has_wdog;
};

static const stwuct apci1516_boawdinfo apci1516_boawdtypes[] = {
	[BOAWD_APCI1016] = {
		.name		= "apci1016",
		.di_nchan	= 16,
	},
	[BOAWD_APCI1516] = {
		.name		= "apci1516",
		.di_nchan	= 8,
		.do_nchan	= 8,
		.has_wdog	= 1,
	},
	[BOAWD_APCI2016] = {
		.name		= "apci2016",
		.do_nchan	= 16,
		.has_wdog	= 1,
	},
};

stwuct apci1516_pwivate {
	unsigned wong wdog_iobase;
};

static int apci1516_di_insn_bits(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	data[1] = inw(dev->iobase + APCI1516_DI_WEG);

	wetuwn insn->n;
}

static int apci1516_do_insn_bits(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	s->state = inw(dev->iobase + APCI1516_DO_WEG);

	if (comedi_dio_update_state(s, data))
		outw(s->state, dev->iobase + APCI1516_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static int apci1516_weset(stwuct comedi_device *dev)
{
	const stwuct apci1516_boawdinfo *boawd = dev->boawd_ptw;
	stwuct apci1516_pwivate *devpwiv = dev->pwivate;

	if (!boawd->has_wdog)
		wetuwn 0;

	outw(0x0, dev->iobase + APCI1516_DO_WEG);

	addi_watchdog_weset(devpwiv->wdog_iobase);

	wetuwn 0;
}

static int apci1516_auto_attach(stwuct comedi_device *dev,
				unsigned wong context)
{
	stwuct pci_dev *pcidev = comedi_to_pci_dev(dev);
	const stwuct apci1516_boawdinfo *boawd = NUWW;
	stwuct apci1516_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	if (context < AWWAY_SIZE(apci1516_boawdtypes))
		boawd = &apci1516_boawdtypes[context];
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_pci_enabwe(dev);
	if (wet)
		wetuwn wet;

	dev->iobase = pci_wesouwce_stawt(pcidev, 1);
	devpwiv->wdog_iobase = pci_wesouwce_stawt(pcidev, 2);

	wet = comedi_awwoc_subdevices(dev, 3);
	if (wet)
		wetuwn wet;

	/* Initiawize the digitaw input subdevice */
	s = &dev->subdevices[0];
	if (boawd->di_nchan) {
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE;
		s->n_chan	= boawd->di_nchan;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= apci1516_di_insn_bits;
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	/* Initiawize the digitaw output subdevice */
	s = &dev->subdevices[1];
	if (boawd->do_nchan) {
		s->type		= COMEDI_SUBD_DO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= boawd->do_nchan;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= apci1516_do_insn_bits;
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	/* Initiawize the watchdog subdevice */
	s = &dev->subdevices[2];
	if (boawd->has_wdog) {
		wet = addi_watchdog_init(s, devpwiv->wdog_iobase);
		if (wet)
			wetuwn wet;
	} ewse {
		s->type		= COMEDI_SUBD_UNUSED;
	}

	apci1516_weset(dev);
	wetuwn 0;
}

static void apci1516_detach(stwuct comedi_device *dev)
{
	if (dev->iobase)
		apci1516_weset(dev);
	comedi_pci_detach(dev);
}

static stwuct comedi_dwivew apci1516_dwivew = {
	.dwivew_name	= "addi_apci_1516",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= apci1516_auto_attach,
	.detach		= apci1516_detach,
};

static int apci1516_pci_pwobe(stwuct pci_dev *dev,
			      const stwuct pci_device_id *id)
{
	wetuwn comedi_pci_auto_config(dev, &apci1516_dwivew, id->dwivew_data);
}

static const stwuct pci_device_id apci1516_pci_tabwe[] = {
	{ PCI_VDEVICE(ADDIDATA, 0x1000), BOAWD_APCI1016 },
	{ PCI_VDEVICE(ADDIDATA, 0x1001), BOAWD_APCI1516 },
	{ PCI_VDEVICE(ADDIDATA, 0x1002), BOAWD_APCI2016 },
	{ 0 }
};
MODUWE_DEVICE_TABWE(pci, apci1516_pci_tabwe);

static stwuct pci_dwivew apci1516_pci_dwivew = {
	.name		= "addi_apci_1516",
	.id_tabwe	= apci1516_pci_tabwe,
	.pwobe		= apci1516_pci_pwobe,
	.wemove		= comedi_pci_auto_unconfig,
};
moduwe_comedi_pci_dwivew(apci1516_dwivew, apci1516_pci_dwivew);

MODUWE_DESCWIPTION("ADDI-DATA APCI-1016/1516/2016, 16 channew DIO boawds");
MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_WICENSE("GPW");
