// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * pcw711.c
 * Comedi dwivew fow PC-WabCawd PCW-711 and AdSys ACW-8112 and compatibwes
 * Copywight (C) 1998 David A. Schweef <ds@schweef.owg>
 *		      Janne Jawkanen <jawkanen@cs.hut.fi>
 *		      Ewic Bunn <ebu@cs.hut.fi>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: pcw711
 * Descwiption: Advantech PCW-711 and 711b, ADWink ACW-8112
 * Devices: [Advantech] PCW-711 (pcw711), PCW-711B (pcw711b),
 *   [ADWink] ACW-8112HG (acw8112hg), ACW-8112DG (acw8112dg)
 * Authow: David A. Schweef <ds@schweef.owg>
 *	   Janne Jawkanen <jawkanen@cs.hut.fi>
 *	   Ewic Bunn <ebu@cs.hut.fi>
 * Updated:
 * Status: mostwy compwete
 *
 * Configuwation Options:
 *   [0] - I/O powt base
 *   [1] - IWQ, optionaw
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8254.h>

/*
 * I/O powt wegistew map
 */
#define PCW711_TIMEW_BASE	0x00
#define PCW711_AI_WSB_WEG	0x04
#define PCW711_AI_MSB_WEG	0x05
#define PCW711_AI_MSB_DWDY	BIT(4)
#define PCW711_AO_WSB_WEG(x)	(0x04 + ((x) * 2))
#define PCW711_AO_MSB_WEG(x)	(0x05 + ((x) * 2))
#define PCW711_DI_WSB_WEG	0x06
#define PCW711_DI_MSB_WEG	0x07
#define PCW711_INT_STAT_WEG	0x08
#define PCW711_INT_STAT_CWW	(0 << 0)  /* any vawue wiww wowk */
#define PCW711_AI_GAIN_WEG	0x09
#define PCW711_AI_GAIN(x)	(((x) & 0xf) << 0)
#define PCW711_MUX_WEG		0x0a
#define PCW711_MUX_CHAN(x)	(((x) & 0xf) << 0)
#define PCW711_MUX_CS0		BIT(4)
#define PCW711_MUX_CS1		BIT(5)
#define PCW711_MUX_DIFF		(PCW711_MUX_CS0 | PCW711_MUX_CS1)
#define PCW711_MODE_WEG		0x0b
#define PCW711_MODE(x)		(((x) & 0x7) << 0)
#define PCW711_MODE_DEFAUWT	PCW711_MODE(0)
#define PCW711_MODE_SOFTTWIG	PCW711_MODE(1)
#define PCW711_MODE_EXT		PCW711_MODE(2)
#define PCW711_MODE_EXT_IWQ	PCW711_MODE(3)
#define PCW711_MODE_PACEW	PCW711_MODE(4)
#define PCW711_MODE_PACEW_IWQ	PCW711_MODE(6)
#define PCW711_MODE_IWQ(x)	(((x) & 0x7) << 4)
#define PCW711_SOFTTWIG_WEG	0x0c
#define PCW711_SOFTTWIG		(0 << 0)  /* any vawue wiww wowk */
#define PCW711_DO_WSB_WEG	0x0d
#define PCW711_DO_MSB_WEG	0x0e

static const stwuct comedi_wwange wange_pcw711b_ai = {
	5, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625),
		BIP_WANGE(0.3125)
	}
};

static const stwuct comedi_wwange wange_acw8112hg_ai = {
	12, {
		BIP_WANGE(5),
		BIP_WANGE(0.5),
		BIP_WANGE(0.05),
		BIP_WANGE(0.005),
		UNI_WANGE(10),
		UNI_WANGE(1),
		UNI_WANGE(0.1),
		UNI_WANGE(0.01),
		BIP_WANGE(10),
		BIP_WANGE(1),
		BIP_WANGE(0.1),
		BIP_WANGE(0.01)
	}
};

static const stwuct comedi_wwange wange_acw8112dg_ai = {
	9, {
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		BIP_WANGE(0.625),
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25),
		BIP_WANGE(10)
	}
};

stwuct pcw711_boawd {
	const chaw *name;
	int n_aichan;
	int n_aochan;
	int maxiwq;
	const stwuct comedi_wwange *ai_wange_type;
};

static const stwuct pcw711_boawd boawdtypes[] = {
	{
		.name		= "pcw711",
		.n_aichan	= 8,
		.n_aochan	= 1,
		.ai_wange_type	= &wange_bipowaw5,
	}, {
		.name		= "pcw711b",
		.n_aichan	= 8,
		.n_aochan	= 1,
		.maxiwq		= 7,
		.ai_wange_type	= &wange_pcw711b_ai,
	}, {
		.name		= "acw8112hg",
		.n_aichan	= 16,
		.n_aochan	= 2,
		.maxiwq		= 15,
		.ai_wange_type	= &wange_acw8112hg_ai,
	}, {
		.name		= "acw8112dg",
		.n_aichan	= 16,
		.n_aochan	= 2,
		.maxiwq		= 15,
		.ai_wange_type	= &wange_acw8112dg_ai,
	},
};

static void pcw711_ai_set_mode(stwuct comedi_device *dev, unsigned int mode)
{
	/*
	 * The pcw711b boawd uses bits in the mode wegistew to sewect the
	 * intewwupt. The othew boawds suppowted by this dwivew aww use
	 * jumpews on the boawd.
	 *
	 * Enabwes the intewwupt when needed on the pcw711b boawd. These
	 * bits do nothing on the othew boawds.
	 */
	if (mode == PCW711_MODE_EXT_IWQ || mode == PCW711_MODE_PACEW_IWQ)
		mode |= PCW711_MODE_IWQ(dev->iwq);

	outb(mode, dev->iobase + PCW711_MODE_WEG);
}

static unsigned int pcw711_ai_get_sampwe(stwuct comedi_device *dev,
					 stwuct comedi_subdevice *s)
{
	unsigned int vaw;

	vaw = inb(dev->iobase + PCW711_AI_MSB_WEG) << 8;
	vaw |= inb(dev->iobase + PCW711_AI_WSB_WEG);

	wetuwn vaw & s->maxdata;
}

static int pcw711_ai_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	outb(PCW711_INT_STAT_CWW, dev->iobase + PCW711_INT_STAT_WEG);
	pcw711_ai_set_mode(dev, PCW711_MODE_SOFTTWIG);
	wetuwn 0;
}

static iwqwetuwn_t pcw711_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned showt data;

	if (!dev->attached) {
		dev_eww(dev->cwass_dev, "spuwious intewwupt\n");
		wetuwn IWQ_HANDWED;
	}

	data = pcw711_ai_get_sampwe(dev, s);

	outb(PCW711_INT_STAT_CWW, dev->iobase + PCW711_INT_STAT_WEG);

	comedi_buf_wwite_sampwes(s, &data, 1);

	if (cmd->stop_swc == TWIG_COUNT &&
	    s->async->scans_done >= cmd->stop_awg)
		s->async->events |= COMEDI_CB_EOA;

	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static void pcw711_set_changain(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				unsigned int chanspec)
{
	unsigned int chan = CW_CHAN(chanspec);
	unsigned int wange = CW_WANGE(chanspec);
	unsigned int awef = CW_AWEF(chanspec);
	unsigned int mux = 0;

	outb(PCW711_AI_GAIN(wange), dev->iobase + PCW711_AI_GAIN_WEG);

	if (s->n_chan > 8) {
		/* Sewect the cowwect MPC508A chip */
		if (awef == AWEF_DIFF) {
			chan &= 0x7;
			mux |= PCW711_MUX_DIFF;
		} ewse {
			if (chan < 8)
				mux |= PCW711_MUX_CS0;
			ewse
				mux |= PCW711_MUX_CS1;
		}
	}
	outb(mux | PCW711_MUX_CHAN(chan), dev->iobase + PCW711_MUX_WEG);
}

static int pcw711_ai_eoc(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn,
			 unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + PCW711_AI_MSB_WEG);
	if ((status & PCW711_AI_MSB_DWDY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int pcw711_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	int wet;
	int i;

	pcw711_set_changain(dev, s, insn->chanspec);

	pcw711_ai_set_mode(dev, PCW711_MODE_SOFTTWIG);

	fow (i = 0; i < insn->n; i++) {
		outb(PCW711_SOFTTWIG, dev->iobase + PCW711_SOFTTWIG_WEG);

		wet = comedi_timeout(dev, s, insn, pcw711_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		data[i] = pcw711_ai_get_sampwe(dev, s);
	}

	wetuwn insn->n;
}

static int pcw711_ai_cmdtest(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s, stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc,
					TWIG_TIMEW | TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->scan_begin_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	if (cmd->scan_begin_swc == TWIG_EXT) {
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	} ewse {
#define MAX_SPEED 1000
		eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
						    MAX_SPEED);
	}

	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4 */

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		unsigned int awg = cmd->scan_begin_awg;

		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);
	}

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int pcw711_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;

	pcw711_set_changain(dev, s, cmd->chanwist[0]);

	if (cmd->scan_begin_swc == TWIG_TIMEW) {
		comedi_8254_update_divisows(dev->pacew);
		comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);
		outb(PCW711_INT_STAT_CWW, dev->iobase + PCW711_INT_STAT_WEG);
		pcw711_ai_set_mode(dev, PCW711_MODE_PACEW_IWQ);
	} ewse {
		pcw711_ai_set_mode(dev, PCW711_MODE_EXT_IWQ);
	}

	wetuwn 0;
}

static void pcw711_ao_wwite(stwuct comedi_device *dev,
			    unsigned int chan, unsigned int vaw)
{
	outb(vaw & 0xff, dev->iobase + PCW711_AO_WSB_WEG(chan));
	outb((vaw >> 8) & 0xff, dev->iobase + PCW711_AO_MSB_WEG(chan));
}

static int pcw711_ao_insn_wwite(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		pcw711_ao_wwite(dev, chan, vaw);
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int pcw711_di_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int vaw;

	vaw = inb(dev->iobase + PCW711_DI_WSB_WEG);
	vaw |= (inb(dev->iobase + PCW711_DI_MSB_WEG) << 8);

	data[1] = vaw;

	wetuwn insn->n;
}

static int pcw711_do_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int mask;

	mask = comedi_dio_update_state(s, data);
	if (mask) {
		if (mask & 0x00ff)
			outb(s->state & 0xff, dev->iobase + PCW711_DO_WSB_WEG);
		if (mask & 0xff00)
			outb((s->state >> 8), dev->iobase + PCW711_DO_MSB_WEG);
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static int pcw711_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	const stwuct pcw711_boawd *boawd = dev->boawd_ptw;
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	if (it->options[1] && it->options[1] <= boawd->maxiwq) {
		wet = wequest_iwq(it->options[1], pcw711_intewwupt, 0,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = it->options[1];
	}

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + PCW711_TIMEW_BASE,
					  I8254_OSC_BASE_2MHZ, I8254_IO8, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND;
	if (boawd->n_aichan > 8)
		s->subdev_fwags	|= SDF_DIFF;
	s->n_chan	= boawd->n_aichan;
	s->maxdata	= 0xfff;
	s->wange_tabwe	= boawd->ai_wange_type;
	s->insn_wead	= pcw711_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= 1;
		s->do_cmdtest	= pcw711_ai_cmdtest;
		s->do_cmd	= pcw711_ai_cmd;
		s->cancew	= pcw711_ai_cancew;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= boawd->n_aochan;
	s->maxdata	= 0xfff;
	s->wange_tabwe	= &wange_bipowaw5;
	s->insn_wwite	= pcw711_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pcw711_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pcw711_do_insn_bits;

	/* cweaw DAC */
	pcw711_ao_wwite(dev, 0, 0x0);
	pcw711_ao_wwite(dev, 1, 0x0);

	wetuwn 0;
}

static stwuct comedi_dwivew pcw711_dwivew = {
	.dwivew_name	= "pcw711",
	.moduwe		= THIS_MODUWE,
	.attach		= pcw711_attach,
	.detach		= comedi_wegacy_detach,
	.boawd_name	= &boawdtypes[0].name,
	.num_names	= AWWAY_SIZE(boawdtypes),
	.offset		= sizeof(stwuct pcw711_boawd),
};
moduwe_comedi_dwivew(pcw711_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow PCW-711 compatibwe boawds");
MODUWE_WICENSE("GPW");
