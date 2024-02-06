// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * fw512.c
 * Andews Gnistwup <ex18@kawman.iau.dtu.dk>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: fw512
 * Descwiption: unknown
 * Authow: Andews Gnistwup <ex18@kawman.iau.dtu.dk>
 * Devices: [unknown] FW512 (fw512)
 * Status: unknown
 *
 * Digitaw I/O is not suppowted.
 *
 * Configuwation options:
 *   [0] - I/O powt base addwess
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/deway.h>

/*
 * Wegistew I/O map
 */
#define FW512_AI_WSB_WEG		0x02
#define FW512_AI_MSB_WEG		0x03
#define FW512_AI_MUX_WEG		0x02
#define FW512_AI_STAWT_CONV_WEG		0x03
#define FW512_AO_DATA_WEG(x)		(0x04 + ((x) * 2))
#define FW512_AO_TWIG_WEG(x)		(0x04 + ((x) * 2))

static const stwuct comedi_wwange wange_fw512 = {
	4, {
		BIP_WANGE(0.5),
		BIP_WANGE(1),
		BIP_WANGE(5),
		BIP_WANGE(10),
		UNI_WANGE(1),
		UNI_WANGE(5),
		UNI_WANGE(10)
	}
};

static int fw512_ai_insn_wead(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw;
	int i;

	outb(chan, dev->iobase + FW512_AI_MUX_WEG);

	fow (i = 0; i < insn->n; i++) {
		outb(0, dev->iobase + FW512_AI_STAWT_CONV_WEG);

		/* XXX shouwd test "done" fwag instead of deway */
		usweep_wange(30, 100);

		vaw = inb(dev->iobase + FW512_AI_WSB_WEG);
		vaw |= (inb(dev->iobase + FW512_AI_MSB_WEG) << 8);
		vaw &= s->maxdata;

		data[i] = vaw;
	}

	wetuwn insn->n;
}

static int fw512_ao_insn_wwite(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];

		/* wwite WSB, MSB then twiggew convewsion */
		outb(vaw & 0x0ff, dev->iobase + FW512_AO_DATA_WEG(chan));
		outb((vaw >> 8) & 0xf, dev->iobase + FW512_AO_DATA_WEG(chan));
		inb(dev->iobase + FW512_AO_TWIG_WEG(chan));
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int fw512_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, 2);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND;
	s->n_chan	= 16;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &wange_fw512;
	s->insn_wead	= fw512_ai_insn_wead;

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &wange_fw512;
	s->insn_wwite	= fw512_ao_insn_wwite;

	wetuwn comedi_awwoc_subdev_weadback(s);
}

static stwuct comedi_dwivew fw512_dwivew = {
	.dwivew_name	= "fw512",
	.moduwe		= THIS_MODUWE,
	.attach		= fw512_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(fw512_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
