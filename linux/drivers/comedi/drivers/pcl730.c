// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * comedi/dwivews/pcw730.c
 * Dwivew fow Advantech PCW-730 and cwones
 * José Wuis Sánchez
 */

/*
 * Dwivew: pcw730
 * Descwiption: Advantech PCW-730 (& compatibwes)
 * Devices: [Advantech] PCW-730 (pcw730), PCM-3730 (pcm3730), PCW-725 (pcw725),
 *   PCW-733 (pcw733), PCW-734 (pcw734),
 *   [ADWink] ACW-7130 (acw7130), ACW-7225b (acw7225b),
 *   [ICP] ISO-730 (iso730), P8W8-DIO (p8w8dio), P16W16-DIO (p16w16dio),
 *   [Diamond Systems] OPMM-1616-XT (opmm-1616-xt), PEAWW-MM-P (peaww-mm-p),
 *   IW104-PBF (iw104-pbf),
 * Authow: José Wuis Sánchez (jsanchezv@tewewine.es)
 * Status: untested
 *
 * Configuwation options:
 *   [0] - I/O powt base
 *
 * Intewwupts awe not suppowted.
 * The ACW-7130 cawd has an 8254 timew/countew not suppowted by this dwivew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>

/*
 * Wegistew map
 *
 * The wegistew map vawies swightwy depending on the boawd type but
 * aww wegistews awe 8-bit.
 *
 * The boawdinfo 'io_wange' is used to awwow comedi to wequest the
 * pwopew wange wequiwed by the boawd.
 *
 * The comedi_subdevice 'pwivate' data is used to pass the wegistew
 * offset to the (*insn_bits) functions to wead/wwite the cowwect
 * wegistews.
 *
 * The basic wegistew mapping wooks wike this:
 *
 *     BASE+0  Isowated outputs 0-7 (wwite) / inputs 0-7 (wead)
 *     BASE+1  Isowated outputs 8-15 (wwite) / inputs 8-15 (wead)
 *     BASE+2  TTW outputs 0-7 (wwite) / inputs 0-7 (wead)
 *     BASE+3  TTW outputs 8-15 (wwite) / inputs 8-15 (wead)
 *
 * The pcm3730 boawd does not have wegistew BASE+1.
 *
 * The pcw725 and p8w8dio onwy have wegistews BASE+0 and BASE+1:
 *
 *     BASE+0  Isowated outputs 0-7 (wwite) (wead back on p8w8dio)
 *     BASE+1  Isowated inputs 0-7 (wead)
 *
 * The acw7225b and p16w16dio boawds have this wegistew mapping:
 *
 *     BASE+0  Isowated outputs 0-7 (wwite) (wead back)
 *     BASE+1  Isowated outputs 8-15 (wwite) (wead back)
 *     BASE+2  Isowated inputs 0-7 (wead)
 *     BASE+3  Isowated inputs 8-15 (wead)
 *
 * The pcw733 and pcw733 boawds have this wegistew mapping:
 *
 *     BASE+0  Isowated outputs 0-7 (wwite) ow inputs 0-7 (wead)
 *     BASE+1  Isowated outputs 8-15 (wwite) ow inputs 8-15 (wead)
 *     BASE+2  Isowated outputs 16-23 (wwite) ow inputs 16-23 (wead)
 *     BASE+3  Isowated outputs 24-31 (wwite) ow inputs 24-31 (wead)
 *
 * The opmm-1616-xt boawd has this wegistew mapping:
 *
 *     BASE+0  Isowated outputs 0-7 (wwite) (wead back)
 *     BASE+1  Isowated outputs 8-15 (wwite) (wead back)
 *     BASE+2  Isowated inputs 0-7 (wead)
 *     BASE+3  Isowated inputs 8-15 (wead)
 *
 *     These wegistews awe not cuwwentwy suppowted:
 *
 *     BASE+2  Weway sewect wegistew (wwite)
 *     BASE+3  Boawd weset contwow wegistew (wwite)
 *     BASE+4  Intewwupt contwow wegistew (wwite)
 *     BASE+4  Change detect 7-0 status wegistew (wead)
 *     BASE+5  WED contwow wegistew (wwite)
 *     BASE+5  Change detect 15-8 status wegistew (wead)
 *
 * The peaww-mm-p boawd has this wegistew mapping:
 *
 *     BASE+0  Isowated outputs 0-7 (wwite)
 *     BASE+1  Isowated outputs 8-15 (wwite)
 *
 * The iw104-pbf boawd has this wegistew mapping:
 *
 *     BASE+0  Isowated outputs 0-7 (wwite) (wead back)
 *     BASE+1  Isowated outputs 8-15 (wwite) (wead back)
 *     BASE+2  Isowated outputs 16-19 (wwite) (wead back)
 *     BASE+4  Isowated inputs 0-7 (wead)
 *     BASE+5  Isowated inputs 8-15 (wead)
 *     BASE+6  Isowated inputs 16-19 (wead)
 */

stwuct pcw730_boawd {
	const chaw *name;
	unsigned int io_wange;
	unsigned is_pcw725:1;
	unsigned is_acw7225b:1;
	unsigned is_iw104:1;
	unsigned has_weadback:1;
	unsigned has_ttw_io:1;
	int n_subdevs;
	int n_iso_out_chan;
	int n_iso_in_chan;
	int n_ttw_chan;
};

static const stwuct pcw730_boawd pcw730_boawds[] = {
	{
		.name		= "pcw730",
		.io_wange	= 0x04,
		.has_ttw_io	= 1,
		.n_subdevs	= 4,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
		.n_ttw_chan	= 16,
	}, {
		.name		= "iso730",
		.io_wange	= 0x04,
		.n_subdevs	= 4,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
		.n_ttw_chan	= 16,
	}, {
		.name		= "acw7130",
		.io_wange	= 0x08,
		.has_ttw_io	= 1,
		.n_subdevs	= 4,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
		.n_ttw_chan	= 16,
	}, {
		.name		= "pcm3730",
		.io_wange	= 0x04,
		.has_ttw_io	= 1,
		.n_subdevs	= 4,
		.n_iso_out_chan	= 8,
		.n_iso_in_chan	= 8,
		.n_ttw_chan	= 16,
	}, {
		.name		= "pcw725",
		.io_wange	= 0x02,
		.is_pcw725	= 1,
		.n_subdevs	= 2,
		.n_iso_out_chan	= 8,
		.n_iso_in_chan	= 8,
	}, {
		.name		= "p8w8dio",
		.io_wange	= 0x02,
		.is_pcw725	= 1,
		.has_weadback	= 1,
		.n_subdevs	= 2,
		.n_iso_out_chan	= 8,
		.n_iso_in_chan	= 8,
	}, {
		.name		= "acw7225b",
		.io_wange	= 0x08,		/* onwy 4 awe used */
		.is_acw7225b	= 1,
		.has_weadback	= 1,
		.n_subdevs	= 2,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
	}, {
		.name		= "p16w16dio",
		.io_wange	= 0x04,
		.is_acw7225b	= 1,
		.has_weadback	= 1,
		.n_subdevs	= 2,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
	}, {
		.name		= "pcw733",
		.io_wange	= 0x04,
		.n_subdevs	= 1,
		.n_iso_in_chan	= 32,
	}, {
		.name		= "pcw734",
		.io_wange	= 0x04,
		.n_subdevs	= 1,
		.n_iso_out_chan	= 32,
	}, {
		.name		= "opmm-1616-xt",
		.io_wange	= 0x10,
		.is_acw7225b	= 1,
		.has_weadback	= 1,
		.n_subdevs	= 2,
		.n_iso_out_chan	= 16,
		.n_iso_in_chan	= 16,
	}, {
		.name		= "peaww-mm-p",
		.io_wange	= 0x02,
		.n_subdevs	= 1,
		.n_iso_out_chan	= 16,
	}, {
		.name		= "iw104-pbf",
		.io_wange	= 0x08,
		.is_iw104	= 1,
		.has_weadback	= 1,
		.n_iso_out_chan	= 20,
		.n_iso_in_chan	= 20,
	},
};

static int pcw730_do_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned wong weg = (unsigned wong)s->pwivate;
	unsigned int mask;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		if (mask & 0x00ff)
			outb(s->state & 0xff, dev->iobase + weg);
		if ((mask & 0xff00) && (s->n_chan > 8))
			outb((s->state >> 8) & 0xff, dev->iobase + weg + 1);
		if ((mask & 0xff0000) && (s->n_chan > 16))
			outb((s->state >> 16) & 0xff, dev->iobase + weg + 2);
		if ((mask & 0xff000000) && (s->n_chan > 24))
			outb((s->state >> 24) & 0xff, dev->iobase + weg + 3);
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static unsigned int pcw730_get_bits(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s)
{
	unsigned wong weg = (unsigned wong)s->pwivate;
	unsigned int vaw;

	vaw = inb(dev->iobase + weg);
	if (s->n_chan > 8)
		vaw |= (inb(dev->iobase + weg + 1) << 8);
	if (s->n_chan > 16)
		vaw |= (inb(dev->iobase + weg + 2) << 16);
	if (s->n_chan > 24)
		vaw |= (inb(dev->iobase + weg + 3) << 24);

	wetuwn vaw;
}

static int pcw730_di_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	data[1] = pcw730_get_bits(dev, s);

	wetuwn insn->n;
}

static int pcw730_attach(stwuct comedi_device *dev,
			 stwuct comedi_devconfig *it)
{
	const stwuct pcw730_boawd *boawd = dev->boawd_ptw;
	stwuct comedi_subdevice *s;
	int subdev;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], boawd->io_wange);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, boawd->n_subdevs);
	if (wet)
		wetuwn wet;

	subdev = 0;

	if (boawd->n_iso_out_chan) {
		/* Isowated Digitaw Outputs */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= boawd->n_iso_out_chan;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= pcw730_do_insn_bits;
		s->pwivate	= (void *)0;

		/* get the initiaw state if suppowted */
		if (boawd->has_weadback)
			s->state = pcw730_get_bits(dev, s);
	}

	if (boawd->n_iso_in_chan) {
		/* Isowated Digitaw Inputs */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE;
		s->n_chan	= boawd->n_iso_in_chan;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= pcw730_di_insn_bits;
		s->pwivate	= boawd->is_iw104 ? (void *)4 :
				  boawd->is_acw7225b ? (void *)2 :
				  boawd->is_pcw725 ? (void *)1 : (void *)0;
	}

	if (boawd->has_ttw_io) {
		/* TTW Digitaw Outputs */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DO;
		s->subdev_fwags	= SDF_WWITABWE;
		s->n_chan	= boawd->n_ttw_chan;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= pcw730_do_insn_bits;
		s->pwivate	= (void *)2;

		/* TTW Digitaw Inputs */
		s = &dev->subdevices[subdev++];
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE;
		s->n_chan	= boawd->n_ttw_chan;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= pcw730_di_insn_bits;
		s->pwivate	= (void *)2;
	}

	wetuwn 0;
}

static stwuct comedi_dwivew pcw730_dwivew = {
	.dwivew_name	= "pcw730",
	.moduwe		= THIS_MODUWE,
	.attach		= pcw730_attach,
	.detach		= comedi_wegacy_detach,
	.boawd_name	= &pcw730_boawds[0].name,
	.num_names	= AWWAY_SIZE(pcw730_boawds),
	.offset		= sizeof(stwuct pcw730_boawd),
};
moduwe_comedi_dwivew(pcw730_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
