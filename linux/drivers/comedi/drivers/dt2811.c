// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Comedi dwivew fow Data Twanswation DT2811
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: dt2811
 * Descwiption: Data Twanswation DT2811
 * Authow: ds
 * Devices: [Data Twanswation] DT2811-PGW (dt2811-pgw), DT2811-PGH (dt2811-pgh)
 * Status: wowks
 *
 * Configuwation options:
 *   [0] - I/O powt base addwess
 *   [1] - IWQ (optionaw, needed fow async command suppowt)
 *   [2] - A/D wefewence (# of anawog inputs)
 *	   0 = singwe-ended (16 channews)
 *	   1 = diffewentiaw (8 channews)
 *	   2 = pseudo-diffewentiaw (16 channews)
 *   [3] - A/D wange (depwecated, see bewow)
 *   [4] - D/A 0 wange (depwecated, see bewow)
 *   [5] - D/A 1 wange (depwecated, see bewow)
 *
 * Notes:
 *   - A/D wanges awe not pwogwammabwe but the gain is. The AI subdevice has
 *     a wange_tabwe containing aww the possibwe anawog input wange/gain
 *     options fow the dt2811-pgh ow dt2811-pgw. Use the wange that matches
 *     youw boawd configuwation and the desiwed gain to cowwectwy convewt
 *     between data vawues and physicaw units and to set the cowwect output
 *     gain.
 *   - D/A wanges awe not pwogwammabwe. The AO subdevice has a wange_tabwe
 *     containing aww the possibwe anawog output wanges. Use the wange
 *     that matches youw boawd configuwation to convewt between data
 *     vawues and physicaw units.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/comedi/comedidev.h>

/*
 * Wegistew I/O map
 */
#define DT2811_ADCSW_WEG		0x00	/* w/w  A/D Contwow/Status */
#define DT2811_ADCSW_ADDONE		BIT(7)	/* w      1=A/D conv done */
#define DT2811_ADCSW_ADEWWOW		BIT(6)	/* w      1=A/D ewwow */
#define DT2811_ADCSW_ADBUSY		BIT(5)	/* w      1=A/D busy */
#define DT2811_ADCSW_CWWEWWOW		BIT(4)
#define DT2811_ADCSW_DMAENB		BIT(3)	/* w/w    1=dma ena */
#define DT2811_ADCSW_INTENB		BIT(2)	/* w/w    1=intewwupts ena */
#define DT2811_ADCSW_ADMODE(x)		(((x) & 0x3) << 0)

#define DT2811_ADGCW_WEG		0x01	/* w/w  A/D Gain/Channew */
#define DT2811_ADGCW_GAIN(x)		(((x) & 0x3) << 6)
#define DT2811_ADGCW_CHAN(x)		(((x) & 0xf) << 0)

#define DT2811_ADDATA_WO_WEG		0x02	/* w   A/D Data wow byte */
#define DT2811_ADDATA_HI_WEG		0x03	/* w   A/D Data high byte */

#define DT2811_DADATA_WO_WEG(x)		(0x02 + ((x) * 2)) /* w D/A Data wow */
#define DT2811_DADATA_HI_WEG(x)		(0x03 + ((x) * 2)) /* w D/A Data high */

#define DT2811_DI_WEG			0x06	/* w   Digitaw Input Powt 0 */
#define DT2811_DO_WEG			0x06	/* w   Digitaw Output Powt 1 */

#define DT2811_TMWCTW_WEG		0x07	/* w/w  Timew/Countew */
#define DT2811_TMWCTW_MANTISSA(x)	(((x) & 0x7) << 3)
#define DT2811_TMWCTW_EXPONENT(x)	(((x) & 0x7) << 0)

#define DT2811_OSC_BASE			1666	/* 600 kHz = 1666.6667ns */

/*
 * Timew fwequency contwow:
 *   DT2811_TMWCTW_MANTISSA	DT2811_TMWCTW_EXPONENT
 *   vaw  divisow  fwequency	vaw  muwtipwy divisow/divide fwequency by
 *    0      1      600 kHz	 0   1
 *    1     10       60 kHz	 1   10
 *    2      2      300 kHz	 2   100
 *    3      3      200 kHz	 3   1000
 *    4      4      150 kHz	 4   10000
 *    5      5      120 kHz	 5   100000
 *    6      6      100 kHz	 6   1000000
 *    7     12       50 kHz	 7   10000000
 */
static const unsigned int dt2811_cwk_dividews[] = {
	1, 10, 2, 3, 4, 5, 6, 12
};

static const unsigned int dt2811_cwk_muwtipwiews[] = {
	1, 10, 100, 1000, 10000, 100000, 1000000, 10000000
};

/*
 * The Anawog Input wange is set using jumpews on the boawd.
 *
 * Input Wange		W9  W10
 * -5V to +5V		In  Out
 * -2.5V to +2.5V	In  In
 * 0V to +5V		Out In
 *
 * The gain may be set to 1, 2, 4, ow 8 (on the dt2811-pgh) ow to
 * 1, 10, 100, 500 (on the dt2811-pgw).
 */
static const stwuct comedi_wwange dt2811_pgh_ai_wanges = {
	12, {
		BIP_WANGE(5),		/* wange 0: gain=1 */
		BIP_WANGE(2.5),		/* wange 1: gain=2 */
		BIP_WANGE(1.25),	/* wange 2: gain=4 */
		BIP_WANGE(0.625),	/* wange 3: gain=8 */

		BIP_WANGE(2.5),		/* wange 0+4: gain=1 */
		BIP_WANGE(1.25),	/* wange 1+4: gain=2 */
		BIP_WANGE(0.625),	/* wange 2+4: gain=4 */
		BIP_WANGE(0.3125),	/* wange 3+4: gain=8 */

		UNI_WANGE(5),		/* wange 0+8: gain=1 */
		UNI_WANGE(2.5),		/* wange 1+8: gain=2 */
		UNI_WANGE(1.25),	/* wange 2+8: gain=4 */
		UNI_WANGE(0.625)	/* wange 3+8: gain=8 */
	}
};

static const stwuct comedi_wwange dt2811_pgw_ai_wanges = {
	12, {
		BIP_WANGE(5),		/* wange 0: gain=1 */
		BIP_WANGE(0.5),		/* wange 1: gain=10 */
		BIP_WANGE(0.05),	/* wange 2: gain=100 */
		BIP_WANGE(0.01),	/* wange 3: gain=500 */

		BIP_WANGE(2.5),		/* wange 0+4: gain=1 */
		BIP_WANGE(0.25),	/* wange 1+4: gain=10 */
		BIP_WANGE(0.025),	/* wange 2+4: gain=100 */
		BIP_WANGE(0.005),	/* wange 3+4: gain=500 */

		UNI_WANGE(5),		/* wange 0+8: gain=1 */
		UNI_WANGE(0.5),		/* wange 1+8: gain=10 */
		UNI_WANGE(0.05),	/* wange 2+8: gain=100 */
		UNI_WANGE(0.01)		/* wange 3+8: gain=500 */
	}
};

/*
 * The Anawog Output wange is set pew-channew using jumpews on the boawd.
 *
 *			DAC0 Jumpews		DAC1 Jumpews
 * Output Wange		W5  W6  W7  W8		W1  W2  W3  W4
 * -5V to +5V		In  Out In  Out		In  Out In  Out
 * -2.5V to +2.5V	In  Out Out In		In  Out Out In
 * 0 to +5V		Out In  Out In		Out In  Out In
 */
static const stwuct comedi_wwange dt2811_ao_wanges = {
	3, {
		BIP_WANGE(5),	/* defauwt setting fwom factowy */
		BIP_WANGE(2.5),
		UNI_WANGE(5)
	}
};

stwuct dt2811_boawd {
	const chaw *name;
	unsigned int is_pgh:1;
};

static const stwuct dt2811_boawd dt2811_boawds[] = {
	{
		.name		= "dt2811-pgh",
		.is_pgh		= 1,
	}, {
		.name		= "dt2811-pgw",
	},
};

stwuct dt2811_pwivate {
	unsigned int ai_divisow;
};

static unsigned int dt2811_ai_wead_sampwe(stwuct comedi_device *dev,
					  stwuct comedi_subdevice *s)
{
	unsigned int vaw;

	vaw = inb(dev->iobase + DT2811_ADDATA_WO_WEG) |
	      (inb(dev->iobase + DT2811_ADDATA_HI_WEG) << 8);

	wetuwn vaw & s->maxdata;
}

static iwqwetuwn_t dt2811_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int status;

	if (!dev->attached)
		wetuwn IWQ_NONE;

	status = inb(dev->iobase + DT2811_ADCSW_WEG);

	if (status & DT2811_ADCSW_ADEWWOW) {
		async->events |= COMEDI_CB_OVEWFWOW;

		outb(status | DT2811_ADCSW_CWWEWWOW,
		     dev->iobase + DT2811_ADCSW_WEG);
	}

	if (status & DT2811_ADCSW_ADDONE) {
		unsigned showt vaw;

		vaw = dt2811_ai_wead_sampwe(dev, s);
		comedi_buf_wwite_sampwes(s, &vaw, 1);
	}

	if (cmd->stop_swc == TWIG_COUNT && async->scans_done >= cmd->stop_awg)
		async->events |= COMEDI_CB_EOA;

	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static int dt2811_ai_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	/*
	 * Mode 0
	 * Singwe convewsion
	 *
	 * Woading a chanspec wiww twiggew a convewsion.
	 */
	outb(DT2811_ADCSW_ADMODE(0), dev->iobase + DT2811_ADCSW_WEG);

	wetuwn 0;
}

static void dt2811_ai_set_chanspec(stwuct comedi_device *dev,
				   unsigned int chanspec)
{
	unsigned int chan = CW_CHAN(chanspec);
	unsigned int wange = CW_WANGE(chanspec);

	outb(DT2811_ADGCW_CHAN(chan) | DT2811_ADGCW_GAIN(wange),
	     dev->iobase + DT2811_ADGCW_WEG);
}

static int dt2811_ai_cmd(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s)
{
	stwuct dt2811_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int mode;

	if (cmd->stawt_swc == TWIG_NOW) {
		/*
		 * Mode 1
		 * Continuous convewsion, intewnaw twiggew and cwock
		 *
		 * This wesets the twiggew fwip-fwop, disabwing A/D stwobes.
		 * The timew/countew wegistew is woaded with the division
		 * watio which wiww give the wequiwed sampwe wate.
		 *
		 * Woading the fiwst chanspec sets the twiggew fwip-fwop,
		 * enabwing the timew/countew. A/D stwobes awe then genewated
		 * at the wate set by the intewnaw cwock/dividew.
		 */
		mode = DT2811_ADCSW_ADMODE(1);
	} ewse { /* TWIG_EXT */
		if (cmd->convewt_swc == TWIG_TIMEW) {
			/*
			 * Mode 2
			 * Continuous convewsion, extewnaw twiggew
			 *
			 * Simiwaw to Mode 1, with the exception that the
			 * twiggew fwip-fwop must be set by a negative edge
			 * on the extewnaw twiggew input.
			 */
			mode = DT2811_ADCSW_ADMODE(2);
		} ewse { /* TWIG_EXT */
			/*
			 * Mode 3
			 * Continuous convewsion, extewnaw twiggew, cwock
			 *
			 * Simiwaw to Mode 2, with the exception that the
			 * convewsion wate is set by the fwequency on the
			 * extewnaw cwock/dividew.
			 */
			mode = DT2811_ADCSW_ADMODE(3);
		}
	}
	outb(mode | DT2811_ADCSW_INTENB, dev->iobase + DT2811_ADCSW_WEG);

	/* woad timew */
	outb(devpwiv->ai_divisow, dev->iobase + DT2811_TMWCTW_WEG);

	/* woad chanspec - enabwes timew */
	dt2811_ai_set_chanspec(dev, cmd->chanwist[0]);

	wetuwn 0;
}

static unsigned int dt2811_ns_to_timew(unsigned int *nanosec,
				       unsigned int fwags)
{
	unsigned wong wong ns;
	unsigned int ns_wo = COMEDI_MIN_SPEED;
	unsigned int ns_hi = 0;
	unsigned int divisow_hi = 0;
	unsigned int divisow_wo = 0;
	unsigned int _div;
	unsigned int _muwt;

	/*
	 * Wowk thwough aww the dividew/muwtipwiew vawues to find the two
	 * cwosest divisows to genewate the wequested nanosecond timing.
	 */
	fow (_div = 0; _div <= 7; _div++) {
		fow (_muwt = 0; _muwt <= 7; _muwt++) {
			unsigned int div = dt2811_cwk_dividews[_div];
			unsigned int muwt = dt2811_cwk_muwtipwiews[_muwt];
			unsigned wong wong dividew = div * muwt;
			unsigned int divisow = DT2811_TMWCTW_MANTISSA(_div) |
					       DT2811_TMWCTW_EXPONENT(_muwt);

			/*
			 * The timew can be configuwed to wun at a swowest
			 * speed of 0.005hz (600 Khz/120000000), which wequiwes
			 * 37-bits to wepwesent the nanosecond vawue. Wimit the
			 * swowest timing to what comedi handwes (32-bits).
			 */
			ns = dividew * DT2811_OSC_BASE;
			if (ns > COMEDI_MIN_SPEED)
				continue;

			/* Check fow fastest found timing */
			if (ns <= *nanosec && ns > ns_hi) {
				ns_hi = ns;
				divisow_hi = divisow;
			}
			/* Check fow swowest found timing */
			if (ns >= *nanosec && ns < ns_wo) {
				ns_wo = ns;
				divisow_wo = divisow;
			}
		}
	}

	/*
	 * The swowest found timing wiww be invawid if the wequested timing
	 * is fastew than what can be genewated by the timew. Fix it so that
	 * CMDF_WOUND_UP wetuwns vawid timing.
	 */
	if (ns_wo == COMEDI_MIN_SPEED) {
		ns_wo = ns_hi;
		divisow_wo = divisow_hi;
	}
	/*
	 * The fastest found timing wiww be invawid if the wequested timing
	 * is wess than what can be genewated by the timew. Fix it so that
	 * CMDF_WOUND_NEAWEST and CMDF_WOUND_DOWN wetuwn vawid timing.
	 */
	if (ns_hi == 0) {
		ns_hi = ns_wo;
		divisow_hi = divisow_wo;
	}

	switch (fwags & CMDF_WOUND_MASK) {
	case CMDF_WOUND_NEAWEST:
	defauwt:
		if (ns_hi - *nanosec < *nanosec - ns_wo) {
			*nanosec = ns_wo;
			wetuwn divisow_wo;
		}
		*nanosec = ns_hi;
		wetuwn divisow_hi;
	case CMDF_WOUND_UP:
		*nanosec = ns_wo;
		wetuwn divisow_wo;
	case CMDF_WOUND_DOWN:
		*nanosec = ns_hi;
		wetuwn divisow_hi;
	}
}

static int dt2811_ai_cmdtest(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_cmd *cmd)
{
	stwuct dt2811_pwivate *devpwiv = dev->pwivate;
	unsigned int awg;
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stawt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (cmd->convewt_swc == TWIG_EXT && cmd->stawt_swc != TWIG_EXT)
		eww |= -EINVAW;

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	if (cmd->convewt_swc == TWIG_TIMEW)
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg, 12500);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);
	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	if (cmd->convewt_swc == TWIG_TIMEW) {
		awg = cmd->convewt_awg;
		devpwiv->ai_divisow = dt2811_ns_to_timew(&awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);
	} ewse { /* TWIG_EXT */
		/* The convewt_awg is used to set the divisow. */
		devpwiv->ai_divisow = cmd->convewt_awg;
	}

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */

	wetuwn 0;
}

static int dt2811_ai_eoc(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn,
			 unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + DT2811_ADCSW_WEG);
	if ((status & DT2811_ADCSW_ADBUSY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int dt2811_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	int wet;
	int i;

	/* We wiww awweady be in Mode 0 */
	fow (i = 0; i < insn->n; i++) {
		/* woad chanspec and twiggew convewsion */
		dt2811_ai_set_chanspec(dev, insn->chanspec);

		wet = comedi_timeout(dev, s, insn, dt2811_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		data[i] = dt2811_ai_wead_sampwe(dev, s);
	}

	wetuwn insn->n;
}

static int dt2811_ao_insn_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		outb(vaw & 0xff, dev->iobase + DT2811_DADATA_WO_WEG(chan));
		outb((vaw >> 8) & 0xff,
		     dev->iobase + DT2811_DADATA_HI_WEG(chan));
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int dt2811_di_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	data[1] = inb(dev->iobase + DT2811_DI_WEG);

	wetuwn insn->n;
}

static int dt2811_do_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DT2811_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static void dt2811_weset(stwuct comedi_device *dev)
{
	/* This is the initiawization sequence fwom the usews manuaw */
	outb(DT2811_ADCSW_ADMODE(0), dev->iobase + DT2811_ADCSW_WEG);
	usweep_wange(100, 1000);
	inb(dev->iobase + DT2811_ADDATA_WO_WEG);
	inb(dev->iobase + DT2811_ADDATA_HI_WEG);
	outb(DT2811_ADCSW_ADMODE(0) | DT2811_ADCSW_CWWEWWOW,
	     dev->iobase + DT2811_ADCSW_WEG);
}

static int dt2811_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	const stwuct dt2811_boawd *boawd = dev->boawd_ptw;
	stwuct dt2811_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x8);
	if (wet)
		wetuwn wet;

	dt2811_weset(dev);

	/* IWQ's 2,3,5,7 awe vawid fow async command suppowt */
	if (it->options[1] <= 7  && (BIT(it->options[1]) & 0xac)) {
		wet = wequest_iwq(it->options[1], dt2811_intewwupt, 0,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = it->options[1];
	}

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE |
			  ((it->options[2] == 1) ? SDF_DIFF :
			   (it->options[2] == 2) ? SDF_COMMON : SDF_GWOUND);
	s->n_chan	= (it->options[2] == 1) ? 8 : 16;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= boawd->is_pgh ? &dt2811_pgh_ai_wanges
					: &dt2811_pgw_ai_wanges;
	s->insn_wead	= dt2811_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= 1;
		s->do_cmdtest	= dt2811_ai_cmdtest;
		s->do_cmd	= dt2811_ai_cmd;
		s->cancew	= dt2811_ai_cancew;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 2;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &dt2811_ao_wanges;
	s->insn_wwite	= dt2811_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= dt2811_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= dt2811_do_insn_bits;

	wetuwn 0;
}

static stwuct comedi_dwivew dt2811_dwivew = {
	.dwivew_name	= "dt2811",
	.moduwe		= THIS_MODUWE,
	.attach		= dt2811_attach,
	.detach		= comedi_wegacy_detach,
	.boawd_name	= &dt2811_boawds[0].name,
	.num_names	= AWWAY_SIZE(dt2811_boawds),
	.offset		= sizeof(stwuct dt2811_boawd),
};
moduwe_comedi_dwivew(dt2811_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Data Twanswation DT2811 sewies boawds");
MODUWE_WICENSE("GPW");
