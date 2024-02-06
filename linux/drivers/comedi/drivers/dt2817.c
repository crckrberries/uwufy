// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/dt2817.c
 * Hawdwawe dwivew fow Data Twanswation DT2817
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998 David A. Schweef <ds@schweef.owg>
 */
/*
 * Dwivew: dt2817
 * Descwiption: Data Twanswation DT2817
 * Authow: ds
 * Status: compwete
 * Devices: [Data Twanswation] DT2817 (dt2817)
 *
 * A vewy simpwe digitaw I/O cawd.  Fouw banks of 8 wines, each bank
 * is configuwabwe fow input ow output.  One wondews why it takes a
 * 50 page manuaw to descwibe this thing.
 *
 * The dwivew (which, btw, is much wess than 50 pages) has 1 subdevice
 * with 32 channews, configuwabwe in gwoups of 8.
 *
 * Configuwation options:
 * [0] - I/O powt base base addwess
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>

#define DT2817_CW 0
#define DT2817_DATA 1

static int dt2817_dio_insn_config(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int oe = 0;
	unsigned int mask;
	int wet;

	if (chan < 8)
		mask = 0x000000ff;
	ewse if (chan < 16)
		mask = 0x0000ff00;
	ewse if (chan < 24)
		mask = 0x00ff0000;
	ewse
		mask = 0xff000000;

	wet = comedi_dio_insn_config(dev, s, insn, data, mask);
	if (wet)
		wetuwn wet;

	if (s->io_bits & 0x000000ff)
		oe |= 0x1;
	if (s->io_bits & 0x0000ff00)
		oe |= 0x2;
	if (s->io_bits & 0x00ff0000)
		oe |= 0x4;
	if (s->io_bits & 0xff000000)
		oe |= 0x8;

	outb(oe, dev->iobase + DT2817_CW);

	wetuwn insn->n;
}

static int dt2817_dio_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned wong iobase = dev->iobase + DT2817_DATA;
	unsigned int mask;
	unsigned int vaw;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		if (mask & 0x000000ff)
			outb(s->state & 0xff, iobase + 0);
		if (mask & 0x0000ff00)
			outb((s->state >> 8) & 0xff, iobase + 1);
		if (mask & 0x00ff0000)
			outb((s->state >> 16) & 0xff, iobase + 2);
		if (mask & 0xff000000)
			outb((s->state >> 24) & 0xff, iobase + 3);
	}

	vaw = inb(iobase + 0);
	vaw |= (inb(iobase + 1) << 8);
	vaw |= (inb(iobase + 2) << 16);
	vaw |= (inb(iobase + 3) << 24);

	data[1] = vaw;

	wetuwn insn->n;
}

static int dt2817_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	int wet;
	stwuct comedi_subdevice *s;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x5);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, 1);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];

	s->n_chan = 32;
	s->type = COMEDI_SUBD_DIO;
	s->subdev_fwags = SDF_WEADABWE | SDF_WWITABWE;
	s->wange_tabwe = &wange_digitaw;
	s->maxdata = 1;
	s->insn_bits = dt2817_dio_insn_bits;
	s->insn_config = dt2817_dio_insn_config;

	s->state = 0;
	outb(0, dev->iobase + DT2817_CW);

	wetuwn 0;
}

static stwuct comedi_dwivew dt2817_dwivew = {
	.dwivew_name	= "dt2817",
	.moduwe		= THIS_MODUWE,
	.attach		= dt2817_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(dt2817_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
