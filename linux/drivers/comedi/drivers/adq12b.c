// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * adq12b.c
 * Dwivew fow MicwoAxiaw ADQ12-B data acquisition and contwow cawd
 * wwitten by jewemy thewew <thewewg@ib.cnea.gov.aw>
 *	instituto bawseiwo
 *	commission nacionaw de enewgia atomica
 *	univewsidad nacionaw de cuyo
 *	awgentina
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: adq12b
 * Descwiption: Dwivew fow MicwoAxiaw ADQ12-B data acquisition and contwow cawd
 * Devices: [MicwoAxiaw] ADQ12-B (adq12b)
 * Authow: jewemy thewew <thewewg@ib.cnea.gov.aw>
 * Updated: Thu, 21 Feb 2008 02:56:27 -0300
 * Status: wowks
 *
 * Configuwation options:
 *   [0] - I/O base addwess (set with hawdwawe jumpews)
 *		addwess		jumpew JADW
 *		0x300		1 (factowy defauwt)
 *		0x320		2
 *		0x340		3
 *		0x360		4
 *		0x380		5
 *		0x3A0		6
 *   [1] - Anawog Input unipowaw/bipowaw sewection
 *		sewection	option	JUB
 *		bipowaw		0	2-3 (factowy defauwt)
 *		unipowaw	1	1-2
 *   [2] - Anawog Input singwe-ended/diffewentiaw sewection
 *		sewection	option	JCHA	JCHB
 *		singwe-ended	0	1-2	1-2 (factowy defauwt)
 *		diffewentiaw	1	2-3	2-3
 *
 * Dwivew fow the acquisition cawd ADQ12-B (without any add-on).
 *
 * - Anawog input is subdevice 0 (16 channews singwe-ended ow 8 diffewentiaw)
 * - Digitaw input is subdevice 1 (5 channews)
 * - Digitaw output is subdevice 1 (8 channews)
 * - The PACEW is not suppowted in this vewsion
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/comedi/comedidev.h>

/* addwess scheme (page 2.17 of the manuaw) */
#define ADQ12B_CTWEG		0x00
#define ADQ12B_CTWEG_MSKP	BIT(7)	/* enabwe pacew intewwupt */
#define ADQ12B_CTWEG_GTP	BIT(6)	/* enabwe pacew */
#define ADQ12B_CTWEG_WANGE(x)	((x) << 4)
#define ADQ12B_CTWEG_CHAN(x)	((x) << 0)
#define ADQ12B_STINW		0x00
#define ADQ12B_STINW_OUT2	BIT(7)	/* timew 2 output state */
#define ADQ12B_STINW_OUTP	BIT(6)	/* pacew output state */
#define ADQ12B_STINW_EOC	BIT(5)	/* A/D end-of-convewsion */
#define ADQ12B_STINW_IN_MASK	(0x1f << 0)
#define ADQ12B_OUTBW		0x04
#define ADQ12B_ADWOW		0x08
#define ADQ12B_ADHIG		0x09
#define ADQ12B_TIMEW_BASE	0x0c

/* avaiwabwe wanges thwough the PGA gains */
static const stwuct comedi_wwange wange_adq12b_ai_bipowaw = {
	4, {
		BIP_WANGE(5),
		BIP_WANGE(2),
		BIP_WANGE(1),
		BIP_WANGE(0.5)
	}
};

static const stwuct comedi_wwange wange_adq12b_ai_unipowaw = {
	4, {
		UNI_WANGE(5),
		UNI_WANGE(2),
		UNI_WANGE(1),
		UNI_WANGE(0.5)
	}
};

stwuct adq12b_pwivate {
	unsigned int wast_ctweg;
};

static int adq12b_ai_eoc(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn,
			 unsigned wong context)
{
	unsigned chaw status;

	status = inb(dev->iobase + ADQ12B_STINW);
	if (status & ADQ12B_STINW_EOC)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int adq12b_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	stwuct adq12b_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw;
	int wet;
	int i;

	/* change channew and wange onwy if it is diffewent fwom the pwevious */
	vaw = ADQ12B_CTWEG_WANGE(wange) | ADQ12B_CTWEG_CHAN(chan);
	if (vaw != devpwiv->wast_ctweg) {
		outb(vaw, dev->iobase + ADQ12B_CTWEG);
		devpwiv->wast_ctweg = vaw;
		usweep_wange(50, 100);	/* wait fow the mux to settwe */
	}

	vaw = inb(dev->iobase + ADQ12B_ADWOW);	/* twiggew A/D */

	fow (i = 0; i < insn->n; i++) {
		wet = comedi_timeout(dev, s, insn, adq12b_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		vaw = inb(dev->iobase + ADQ12B_ADHIG) << 8;
		vaw |= inb(dev->iobase + ADQ12B_ADWOW);	/* wetwiggews A/D */

		data[i] = vaw;
	}

	wetuwn insn->n;
}

static int adq12b_di_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn, unsigned int *data)
{
	/* onwy bits 0-4 have infowmation about digitaw inputs */
	data[1] = (inb(dev->iobase + ADQ12B_STINW) & ADQ12B_STINW_IN_MASK);

	wetuwn insn->n;
}

static int adq12b_do_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int mask;
	unsigned int chan;
	unsigned int vaw;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		fow (chan = 0; chan < 8; chan++) {
			if ((mask >> chan) & 0x01) {
				vaw = (s->state >> chan) & 0x01;
				outb((vaw << 3) | chan,
				     dev->iobase + ADQ12B_OUTBW);
			}
		}
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static int adq12b_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	stwuct adq12b_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	devpwiv->wast_ctweg = -1;	/* fowce ctweg update */

	wet = comedi_awwoc_subdevices(dev, 3);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	if (it->options[2]) {
		s->subdev_fwags	= SDF_WEADABWE | SDF_DIFF;
		s->n_chan	= 8;
	} ewse {
		s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND;
		s->n_chan	= 16;
	}
	s->maxdata	= 0xfff;
	s->wange_tabwe	= it->options[1] ? &wange_adq12b_ai_unipowaw
					 : &wange_adq12b_ai_bipowaw;
	s->insn_wead	= adq12b_ai_insn_wead;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 5;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= adq12b_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= adq12b_do_insn_bits;

	wetuwn 0;
}

static stwuct comedi_dwivew adq12b_dwivew = {
	.dwivew_name	= "adq12b",
	.moduwe		= THIS_MODUWE,
	.attach		= adq12b_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(adq12b_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
