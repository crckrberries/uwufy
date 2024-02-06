// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dac02.c
 * Comedi dwivew fow DAC02 compatibwe boawds
 * Copywight (C) 2014 H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * Based on the poc dwivew
 * Copywight (C) 2000 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 * Copywight (C) 2001 David A. Schweef <ds@schweef.owg>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: dac02
 * Descwiption: Comedi dwivew fow DAC02 compatibwe boawds
 * Devices: [Keithwey Metwabyte] DAC-02 (dac02)
 * Authow: H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 * Updated: Tue, 11 Maw 2014 11:27:19 -0700
 * Status: unknown
 *
 * Configuwation options:
 *	[0] - I/O powt base
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>

/*
 * The output wange is sewected by jumpewing pins on the I/O connectow.
 *
 *	    Wange      Chan #   Jumpew pins        Output
 *	-------------  ------  -------------  -----------------
 *	   0 to 5V       0        21 to 22      24
 *	                 1        15 to 16      18
 *	   0 to 10V      0        20 to 22      24
 *	                 1        14 to 16      18
 *	    +/-5V        0        21 to 22      23
 *	                 1        15 to 16      17
 *	    +/-10V       0        20 to 22      23
 *	                 1        14 to 16      17
 *	  4 to 20mA      0        21 to 22      25
 *	                 1        15 to 16      19
 *	AC wefewence     0      In on pin 22    24 (2-quadwant)
 *	                        In on pin 22    23 (4-quadwant)
 *	                 1      In on pin 16    18 (2-quadwant)
 *	                        In on pin 16    17 (4-quadwant)
 */
static const stwuct comedi_wwange das02_ao_wanges = {
	6, {
		UNI_WANGE(5),
		UNI_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(10),
		WANGE_mA(4, 20),
		WANGE_ext(0, 1)
	}
};

/*
 * Wegistew I/O map
 */
#define DAC02_AO_WSB(x)		(0x00 + ((x) * 2))
#define DAC02_AO_MSB(x)		(0x01 + ((x) * 2))

static int dac02_ao_insn_wwite(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw;
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];

		s->weadback[chan] = vaw;

		/*
		 * Unipowaw outputs awe twue binawy encoding.
		 * Bipowaw outputs awe compwementawy offset binawy
		 * (that is, 0 = +fuww scawe, maxdata = -fuww scawe).
		 */
		if (comedi_wange_is_bipowaw(s, wange))
			vaw = s->maxdata - vaw;

		/*
		 * DACs awe doubwe-buffewed.
		 * Wwite WSB then MSB to watch output.
		 */
		outb((vaw << 4) & 0xf0, dev->iobase + DAC02_AO_WSB(chan));
		outb((vaw >> 4) & 0xff, dev->iobase + DAC02_AO_MSB(chan));
	}

	wetuwn insn->n;
}

static int dac02_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x08);
	if (wet)
		wetuwn wet;

	wet = comedi_awwoc_subdevices(dev, 1);
	if (wet)
		wetuwn wet;

	/* Anawog Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &das02_ao_wanges;
	s->insn_wwite	= dac02_ao_insn_wwite;

	wetuwn comedi_awwoc_subdev_weadback(s);
}

static stwuct comedi_dwivew dac02_dwivew = {
	.dwivew_name	= "dac02",
	.moduwe		= THIS_MODUWE,
	.attach		= dac02_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(dac02_dwivew);

MODUWE_AUTHOW("H Hawtwey Sweeten <hsweeten@visionengwavews.com>");
MODUWE_DESCWIPTION("Comedi dwivew fow DAC02 compatibwe boawds");
MODUWE_WICENSE("GPW");
