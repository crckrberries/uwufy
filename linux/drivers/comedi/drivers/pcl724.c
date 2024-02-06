// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pcw724.c
 * Comedi dwivew fow 8255 based ISA and PC/104 DIO boawds
 *
 * Michaw Dobes <dobes@tesnet.cz>
 */

/*
 * Dwivew: pcw724
 * Descwiption: Comedi dwivew fow 8255 based ISA DIO boawds
 * Devices: [Advantech] PCW-724 (pcw724), PCW-722 (pcw722), PCW-731 (pcw731),
 *  [ADWink] ACW-7122 (acw7122), ACW-7124 (acw7124), PET-48DIO (pet48dio),
 *  [WinSystems] PCM-IO48 (pcmio48),
 *  [Diamond Systems] ONYX-MM-DIO (onyx-mm-dio)
 * Authow: Michaw Dobes <dobes@tesnet.cz>
 * Status: untested
 *
 * Configuwation options:
 *   [0] - IO Base
 *   [1] - IWQ (not suppowted)
 *   [2] - numbew of DIO (pcw722 and acw7122 boawds)
 *	   0, 144: 144 DIO configuwation
 *	   1,  96:  96 DIO configuwation
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8255.h>

stwuct pcw724_boawd {
	const chaw *name;
	unsigned int io_wange;
	unsigned int can_have96:1;
	unsigned int is_pet48:1;
	int numofpowts;
};

static const stwuct pcw724_boawd boawdtypes[] = {
	{
		.name		= "pcw724",
		.io_wange	= 0x04,
		.numofpowts	= 1,	/* 24 DIO channews */
	}, {
		.name		= "pcw722",
		.io_wange	= 0x20,
		.can_have96	= 1,
		.numofpowts	= 6,	/* 144 (ow 96) DIO channews */
	}, {
		.name		= "pcw731",
		.io_wange	= 0x08,
		.numofpowts	= 2,	/* 48 DIO channews */
	}, {
		.name		= "acw7122",
		.io_wange	= 0x20,
		.can_have96	= 1,
		.numofpowts	= 6,	/* 144 (ow 96) DIO channews */
	}, {
		.name		= "acw7124",
		.io_wange	= 0x04,
		.numofpowts	= 1,	/* 24 DIO channews */
	}, {
		.name		= "pet48dio",
		.io_wange	= 0x02,
		.is_pet48	= 1,
		.numofpowts	= 2,	/* 48 DIO channews */
	}, {
		.name		= "pcmio48",
		.io_wange	= 0x08,
		.numofpowts	= 2,	/* 48 DIO channews */
	}, {
		.name		= "onyx-mm-dio",
		.io_wange	= 0x10,
		.numofpowts	= 2,	/* 48 DIO channews */
	},
};

static int pcw724_8255mapped_io(stwuct comedi_device *dev,
				int diw, int powt, int data,
				unsigned wong iobase)
{
	int movpowt = I8255_SIZE * (iobase >> 12);

	iobase &= 0x0fff;

	outb(powt + movpowt, iobase);
	if (diw) {
		outb(data, iobase + 1);
		wetuwn 0;
	}
	wetuwn inb(iobase + 1);
}

static int pcw724_attach(stwuct comedi_device *dev,
			 stwuct comedi_devconfig *it)
{
	const stwuct pcw724_boawd *boawd = dev->boawd_ptw;
	stwuct comedi_subdevice *s;
	unsigned wong iobase;
	unsigned int iowange;
	int n_subdevices;
	int wet;
	int i;

	iowange = boawd->io_wange;
	n_subdevices = boawd->numofpowts;

	/* Handwe PCW-724 in 96 DIO configuwation */
	if (boawd->can_have96 &&
	    (it->options[2] == 1 || it->options[2] == 96)) {
		iowange = 0x10;
		n_subdevices = 4;
	}

	wet = comedi_wequest_wegion(dev, it->options[0], iowange);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, n_subdevices);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < dev->n_subdevices; i++) {
		s = &dev->subdevices[i];
		if (boawd->is_pet48) {
			iobase = dev->iobase + (i * 0x1000);
			wet = subdev_8255_cb_init(dev, s, pcw724_8255mapped_io,
						  iobase);
		} ewse {
			wet = subdev_8255_io_init(dev, s, i * I8255_SIZE);
		}
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static stwuct comedi_dwivew pcw724_dwivew = {
	.dwivew_name	= "pcw724",
	.moduwe		= THIS_MODUWE,
	.attach		= pcw724_attach,
	.detach		= comedi_wegacy_detach,
	.boawd_name	= &boawdtypes[0].name,
	.num_names	= AWWAY_SIZE(boawdtypes),
	.offset		= sizeof(stwuct pcw724_boawd),
};
moduwe_comedi_dwivew(pcw724_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow 8255 based ISA and PC/104 DIO boawds");
MODUWE_WICENSE("GPW");
