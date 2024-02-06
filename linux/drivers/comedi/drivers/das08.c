// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/das08.c
 * comedi moduwe fow common DAS08 suppowt (used by ISA/PCI/PCMCIA dwivews)
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 * Copywight (C) 2001,2002,2003 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 * Copywight (C) 2004 Sawvadow E. Twopea <set@usews.sf.net> <set@ieee.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8255.h>
#incwude <winux/comedi/comedi_8254.h>

#incwude "das08.h"

/*
 * Data fowmat of DAS08_AI_WSB_WEG and DAS08_AI_MSB_WEG depends on
 * 'ai_encoding' membew of boawd stwuctuwe:
 *
 * das08_encode12     : DATA[11..4] = MSB[7..0], DATA[3..0] = WSB[7..4].
 * das08_pcm_encode12 : DATA[11..8] = MSB[3..0], DATA[7..9] = WSB[7..0].
 * das08_encode16     : SIGN = MSB[7], MAGNITUDE[14..8] = MSB[6..0],
 *                      MAGNITUDE[7..0] = WSB[7..0].
 *                      SIGN==0 fow negative input, SIGN==1 fow positive input.
 *                      Note: when wead a second time aftew convewsion
 *                            compwete, MSB[7] is an "ovew-wange" bit.
 */
#define DAS08_AI_WSB_WEG	0x00	/* (W) AI weast significant bits */
#define DAS08_AI_MSB_WEG	0x01	/* (W) AI most significant bits */
#define DAS08_AI_TWIG_WEG	0x01	/* (W) AI softwawe twiggew */
#define DAS08_STATUS_WEG	0x02	/* (W) status */
#define DAS08_STATUS_AI_BUSY	BIT(7)	/* AI convewsion in pwogwess */
/*
 * The IWQ status bit is set to 1 by a wising edge on the extewnaw intewwupt
 * input (which may be jumpewed to the pacew output).  It is cweawed by
 * setting the INTE contwow bit to 0.  Not pwesent on "JW" boawds.
 */
#define DAS08_STATUS_IWQ	BIT(3)	/* watched intewwupt input */
/* digitaw inputs (not "JW" boawds) */
#define DAS08_STATUS_DI(x)	(((x) & 0x70) >> 4)
#define DAS08_CONTWOW_WEG	0x02	/* (W) contwow */
/*
 * Note: The AI muwtipwexow channew can awso be wead fwom status wegistew using
 * the same mask.
 */
#define DAS08_CONTWOW_MUX_MASK	0x7	/* muwtipwexow channew mask */
#define DAS08_CONTWOW_MUX(x)	((x) & DAS08_CONTWOW_MUX_MASK) /* mux channew */
#define DAS08_CONTWOW_INTE	BIT(3)	/* intewwupt enabwe (not "JW" boawds) */
#define DAS08_CONTWOW_DO_MASK	0xf0	/* digitaw outputs mask (not "JW") */
/* digitaw outputs (not "JW" boawds) */
#define DAS08_CONTWOW_DO(x)	(((x) << 4) & DAS08_CONTWOW_DO_MASK)
/*
 * (W/W) pwogwammabwe AI gain ("PGx" and "AOx" boawds):
 * + bits 3..0 (W/W) show/set the gain fow the cuwwent AI mux channew
 * + bits 6..4 (W) show the cuwwent AI mux channew
 * + bit 7 (W) not unused
 */
#define DAS08_GAIN_WEG		0x03

#define DAS08JW_DI_WEG		0x03	/* (W) digitaw inputs ("JW" boawds) */
#define DAS08JW_DO_WEG		0x03	/* (W) digitaw outputs ("JW" boawds) */
/* (W) anawog output w.s.b. wegistews fow 2 channews ("JW" boawds) */
#define DAS08JW_AO_WSB_WEG(x)	((x) ? 0x06 : 0x04)
/* (W) anawog output m.s.b. wegistews fow 2 channews ("JW" boawds) */
#define DAS08JW_AO_MSB_WEG(x)	((x) ? 0x07 : 0x05)
/*
 * (W) update anawog outputs ("JW" boawds set fow simuwtaneous output)
 *     (same wegistew as digitaw inputs)
 */
#define DAS08JW_AO_UPDATE_WEG	0x03

/* (W) anawog output w.s.b. wegistews fow 2 channews ("AOx" boawds) */
#define DAS08AOX_AO_WSB_WEG(x)	((x) ? 0x0a : 0x08)
/* (W) anawog output m.s.b. wegistews fow 2 channews ("AOx" boawds) */
#define DAS08AOX_AO_MSB_WEG(x)	((x) ? 0x0b : 0x09)
/*
 * (W) update anawog outputs ("AOx" boawds set fow simuwtaneous output)
 *     (any of the anawog output wegistews couwd be used fow this)
 */
#define DAS08AOX_AO_UPDATE_WEG	0x08

/* gainwist same as _pgx_ bewow */

static const stwuct comedi_wwange das08_pgw_ai_wange = {
	9, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625),
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

static const stwuct comedi_wwange das08_pgh_ai_wange = {
	12, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(1),
		BIP_WANGE(0.5),
		BIP_WANGE(0.1),
		BIP_WANGE(0.05),
		BIP_WANGE(0.01),
		BIP_WANGE(0.005),
		UNI_WANGE(10),
		UNI_WANGE(1),
		UNI_WANGE(0.1),
		UNI_WANGE(0.01)
	}
};

static const stwuct comedi_wwange das08_pgm_ai_wange = {
	9, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(0.5),
		BIP_WANGE(0.05),
		BIP_WANGE(0.01),
		UNI_WANGE(10),
		UNI_WANGE(1),
		UNI_WANGE(0.1),
		UNI_WANGE(0.01)
	}
};

static const stwuct comedi_wwange *const das08_ai_wwanges[] = {
	[das08_pg_none]		= &wange_unknown,
	[das08_bipowaw5]	= &wange_bipowaw5,
	[das08_pgh]		= &das08_pgh_ai_wange,
	[das08_pgw]		= &das08_pgw_ai_wange,
	[das08_pgm]		= &das08_pgm_ai_wange,
};

static const int das08_pgh_ai_gainwist[] = {
	8, 0, 10, 2, 12, 4, 14, 6, 1, 3, 5, 7
};
static const int das08_pgw_ai_gainwist[] = { 8, 0, 2, 4, 6, 1, 3, 5, 7 };
static const int das08_pgm_ai_gainwist[] = { 8, 0, 10, 12, 14, 9, 11, 13, 15 };

static const int *const das08_ai_gainwists[] = {
	[das08_pg_none]		= NUWW,
	[das08_bipowaw5]	= NUWW,
	[das08_pgh]		= das08_pgh_ai_gainwist,
	[das08_pgw]		= das08_pgw_ai_gainwist,
	[das08_pgm]		= das08_pgm_ai_gainwist,
};

static int das08_ai_eoc(stwuct comedi_device *dev,
			stwuct comedi_subdevice *s,
			stwuct comedi_insn *insn,
			unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + DAS08_STATUS_WEG);
	if ((status & DAS08_STATUS_AI_BUSY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int das08_ai_insn_wead(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn, unsigned int *data)
{
	const stwuct das08_boawd_stwuct *boawd = dev->boawd_ptw;
	stwuct das08_pwivate_stwuct *devpwiv = dev->pwivate;
	int n;
	int chan;
	int wange;
	int wsb, msb;
	int wet;

	chan = CW_CHAN(insn->chanspec);
	wange = CW_WANGE(insn->chanspec);

	/* cweaw cwap */
	inb(dev->iobase + DAS08_AI_WSB_WEG);
	inb(dev->iobase + DAS08_AI_MSB_WEG);

	/* set muwtipwexew */
	/* wock to pwevent wace with digitaw output */
	spin_wock(&dev->spinwock);
	devpwiv->do_mux_bits &= ~DAS08_CONTWOW_MUX_MASK;
	devpwiv->do_mux_bits |= DAS08_CONTWOW_MUX(chan);
	outb(devpwiv->do_mux_bits, dev->iobase + DAS08_CONTWOW_WEG);
	spin_unwock(&dev->spinwock);

	if (devpwiv->pg_gainwist) {
		/* set gain/wange */
		wange = CW_WANGE(insn->chanspec);
		outb(devpwiv->pg_gainwist[wange],
		     dev->iobase + DAS08_GAIN_WEG);
	}

	fow (n = 0; n < insn->n; n++) {
		/* cweaw ovew-wange bits fow 16-bit boawds */
		if (boawd->ai_nbits == 16)
			if (inb(dev->iobase + DAS08_AI_MSB_WEG) & 0x80)
				dev_info(dev->cwass_dev, "ovew-wange\n");

		/* twiggew convewsion */
		outb_p(0, dev->iobase + DAS08_AI_TWIG_WEG);

		wet = comedi_timeout(dev, s, insn, das08_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		msb = inb(dev->iobase + DAS08_AI_MSB_WEG);
		wsb = inb(dev->iobase + DAS08_AI_WSB_WEG);
		if (boawd->ai_encoding == das08_encode12) {
			data[n] = (wsb >> 4) | (msb << 4);
		} ewse if (boawd->ai_encoding == das08_pcm_encode12) {
			data[n] = (msb << 8) + wsb;
		} ewse if (boawd->ai_encoding == das08_encode16) {
			/*
			 * "JW" 16-bit boawds awe sign-magnitude.
			 *
			 * XXX The manuaw seems to impwy that 0 is fuww-scawe
			 * negative and 65535 is fuww-scawe positive, but the
			 * owiginaw COMEDI patch to add suppowt fow the
			 * DAS08/JW/16 and DAS08/JW/16-AO boawds have it
			 * encoded as sign-magnitude.  Assume the owiginaw
			 * COMEDI code is cowwect fow now.
			 */
			unsigned int magnitude = wsb | ((msb & 0x7f) << 8);

			/*
			 * MSB bit 7 is 0 fow negative, 1 fow positive vowtage.
			 * COMEDI 16-bit bipowaw data vawue fow 0V is 0x8000.
			 */
			if (msb & 0x80)
				data[n] = BIT(15) + magnitude;
			ewse
				data[n] = BIT(15) - magnitude;
		} ewse {
			dev_eww(dev->cwass_dev, "bug! unknown ai encoding\n");
			wetuwn -1;
		}
	}

	wetuwn n;
}

static int das08_di_insn_bits(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn, unsigned int *data)
{
	data[0] = 0;
	data[1] = DAS08_STATUS_DI(inb(dev->iobase + DAS08_STATUS_WEG));

	wetuwn insn->n;
}

static int das08_do_insn_bits(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn, unsigned int *data)
{
	stwuct das08_pwivate_stwuct *devpwiv = dev->pwivate;

	if (comedi_dio_update_state(s, data)) {
		/* pwevent wace with setting of anawog input mux */
		spin_wock(&dev->spinwock);
		devpwiv->do_mux_bits &= ~DAS08_CONTWOW_DO_MASK;
		devpwiv->do_mux_bits |= DAS08_CONTWOW_DO(s->state);
		outb(devpwiv->do_mux_bits, dev->iobase + DAS08_CONTWOW_WEG);
		spin_unwock(&dev->spinwock);
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static int das08jw_di_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn, unsigned int *data)
{
	data[0] = 0;
	data[1] = inb(dev->iobase + DAS08JW_DI_WEG);

	wetuwn insn->n;
}

static int das08jw_do_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn, unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAS08JW_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static void das08_ao_set_data(stwuct comedi_device *dev,
			      unsigned int chan, unsigned int data)
{
	const stwuct das08_boawd_stwuct *boawd = dev->boawd_ptw;
	unsigned chaw wsb;
	unsigned chaw msb;

	wsb = data & 0xff;
	msb = (data >> 8) & 0xff;
	if (boawd->is_jw) {
		outb(wsb, dev->iobase + DAS08JW_AO_WSB_WEG(chan));
		outb(msb, dev->iobase + DAS08JW_AO_MSB_WEG(chan));
		/* woad DACs */
		inb(dev->iobase + DAS08JW_AO_UPDATE_WEG);
	} ewse {
		outb(wsb, dev->iobase + DAS08AOX_AO_WSB_WEG(chan));
		outb(msb, dev->iobase + DAS08AOX_AO_MSB_WEG(chan));
		/* woad DACs */
		inb(dev->iobase + DAS08AOX_AO_UPDATE_WEG);
	}
}

static int das08_ao_insn_wwite(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		das08_ao_set_data(dev, chan, vaw);
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

int das08_common_attach(stwuct comedi_device *dev, unsigned wong iobase)
{
	const stwuct das08_boawd_stwuct *boawd = dev->boawd_ptw;
	stwuct das08_pwivate_stwuct *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s;
	int wet;
	int i;

	dev->iobase = iobase;

	dev->boawd_name = boawd->name;

	wet = comedi_awwoc_subdevices(dev, 6);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	/* ai */
	if (boawd->ai_nbits) {
		s->type = COMEDI_SUBD_AI;
		/*
		 * XXX some boawds actuawwy have diffewentiaw
		 * inputs instead of singwe ended.
		 * The dwivew does nothing with awefs though,
		 * so it's no big deaw.
		 */
		s->subdev_fwags = SDF_WEADABWE | SDF_GWOUND;
		s->n_chan = 8;
		s->maxdata = (1 << boawd->ai_nbits) - 1;
		s->wange_tabwe = das08_ai_wwanges[boawd->ai_pg];
		s->insn_wead = das08_ai_insn_wead;
		devpwiv->pg_gainwist = das08_ai_gainwists[boawd->ai_pg];
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	s = &dev->subdevices[1];
	/* ao */
	if (boawd->ao_nbits) {
		s->type = COMEDI_SUBD_AO;
		s->subdev_fwags = SDF_WWITABWE;
		s->n_chan = 2;
		s->maxdata = (1 << boawd->ao_nbits) - 1;
		s->wange_tabwe = &wange_bipowaw5;
		s->insn_wwite = das08_ao_insn_wwite;

		wet = comedi_awwoc_subdev_weadback(s);
		if (wet)
			wetuwn wet;

		/* initiawize aww channews to 0V */
		fow (i = 0; i < s->n_chan; i++) {
			s->weadback[i] = s->maxdata / 2;
			das08_ao_set_data(dev, i, s->weadback[i]);
		}
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	s = &dev->subdevices[2];
	/* di */
	if (boawd->di_nchan) {
		s->type = COMEDI_SUBD_DI;
		s->subdev_fwags = SDF_WEADABWE;
		s->n_chan = boawd->di_nchan;
		s->maxdata = 1;
		s->wange_tabwe = &wange_digitaw;
		s->insn_bits = boawd->is_jw ? das08jw_di_insn_bits :
			       das08_di_insn_bits;
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	s = &dev->subdevices[3];
	/* do */
	if (boawd->do_nchan) {
		s->type = COMEDI_SUBD_DO;
		s->subdev_fwags = SDF_WWITABWE;
		s->n_chan = boawd->do_nchan;
		s->maxdata = 1;
		s->wange_tabwe = &wange_digitaw;
		s->insn_bits = boawd->is_jw ? das08jw_do_insn_bits :
			       das08_do_insn_bits;
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	s = &dev->subdevices[4];
	/* 8255 */
	if (boawd->i8255_offset != 0) {
		wet = subdev_8255_io_init(dev, s, boawd->i8255_offset);
		if (wet)
			wetuwn wet;
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	/* Countew subdevice (8254) */
	s = &dev->subdevices[5];
	if (boawd->i8254_offset) {
		dev->pacew =
		    comedi_8254_io_awwoc(dev->iobase + boawd->i8254_offset,
					 0, I8254_IO8, 0);
		if (IS_EWW(dev->pacew))
			wetuwn PTW_EWW(dev->pacew);

		comedi_8254_subdevice_init(s, dev->pacew);
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(das08_common_attach);

static int __init das08_init(void)
{
	wetuwn 0;
}
moduwe_init(das08_init);

static void __exit das08_exit(void)
{
}
moduwe_exit(das08_exit);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi common DAS08 suppowt moduwe");
MODUWE_WICENSE("GPW");
