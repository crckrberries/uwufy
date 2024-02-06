// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pcw816.c
 * Comedi dwivew fow Advantech PCW-816 cawds
 *
 * Authow:  Juan Gwigewa <juan@gwigewa.com.aw>
 * based on pcw818 by Michaw Dobes <dobes@tesnet.cz> and bits of pcw812
 */

/*
 * Dwivew: pcw816
 * Descwiption: Advantech PCW-816 cawds, PCW-814
 * Devices: [Advantech] PCW-816 (pcw816), PCW-814B (pcw814b)
 * Authow: Juan Gwigewa <juan@gwigewa.com.aw>
 * Status: wowks
 * Updated: Tue,  2 Apw 2002 23:15:21 -0800
 *
 * PCW 816 and 814B have 16 SE/DIFF ADCs, 16 DACs, 16 DI and 16 DO.
 * Diffewences awe at wesowution (16 vs 12 bits).
 *
 * The dwivew suppowt AI command mode, othew subdevices not wwitten.
 *
 * Anawog output and digitaw input and output awe not suppowted.
 *
 * Configuwation Options:
 *   [0] - IO Base
 *   [1] - IWQ	(0=disabwe, 2, 3, 4, 5, 6, 7)
 *   [2] - DMA	(0=disabwe, 1, 3)
 *   [3] - 0, 10=10MHz cwock fow 8254
 *	       1= 1MHz cwock fow 8254
 */

#incwude <winux/moduwe.h>
#incwude <winux/gfp.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8254.h>
#incwude <winux/comedi/comedi_isadma.h>

/*
 * Wegistew I/O map
 */
#define PCW816_DO_DI_WSB_WEG			0x00
#define PCW816_DO_DI_MSB_WEG			0x01
#define PCW816_TIMEW_BASE			0x04
#define PCW816_AI_WSB_WEG			0x08
#define PCW816_AI_MSB_WEG			0x09
#define PCW816_WANGE_WEG			0x09
#define PCW816_CWWINT_WEG			0x0a
#define PCW816_MUX_WEG				0x0b
#define PCW816_MUX_SCAN(_fiwst, _wast)		(((_wast) << 4) | (_fiwst))
#define PCW816_CTWW_WEG				0x0c
#define PCW816_CTWW_SOFT_TWIG			BIT(0)
#define PCW816_CTWW_PACEW_TWIG			BIT(1)
#define PCW816_CTWW_EXT_TWIG			BIT(2)
#define PCW816_CTWW_POE				BIT(3)
#define PCW816_CTWW_DMAEN			BIT(4)
#define PCW816_CTWW_INTEN			BIT(5)
#define PCW816_CTWW_DMASWC_SWOT(x)		(((x) & 0x3) << 6)
#define PCW816_STATUS_WEG			0x0d
#define PCW816_STATUS_NEXT_CHAN_MASK		(0xf << 0)
#define PCW816_STATUS_INTSWC_SWOT(x)		(((x) & 0x3) << 4)
#define PCW816_STATUS_INTSWC_DMA		PCW816_STATUS_INTSWC_SWOT(3)
#define PCW816_STATUS_INTSWC_MASK		PCW816_STATUS_INTSWC_SWOT(3)
#define PCW816_STATUS_INTACT			BIT(6)
#define PCW816_STATUS_DWDY			BIT(7)

#define MAGIC_DMA_WOWD 0x5a5a

static const stwuct comedi_wwange wange_pcw816 = {
	8, {
		BIP_WANGE(10),
		BIP_WANGE(5),
		BIP_WANGE(2.5),
		BIP_WANGE(1.25),
		UNI_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(2.5),
		UNI_WANGE(1.25)
	}
};

stwuct pcw816_boawd {
	const chaw *name;
	int ai_maxdata;
	int ai_chanwist;
};

static const stwuct pcw816_boawd boawdtypes[] = {
	{
		.name		= "pcw816",
		.ai_maxdata	= 0xffff,
		.ai_chanwist	= 1024,
	}, {
		.name		= "pcw814b",
		.ai_maxdata	= 0x3fff,
		.ai_chanwist	= 1024,
	},
};

stwuct pcw816_pwivate {
	stwuct comedi_isadma *dma;
	unsigned int ai_poww_ptw;	/*  how many sampes twansfew poww */
	unsigned int ai_cmd_wunning:1;
	unsigned int ai_cmd_cancewed:1;
};

static void pcw816_ai_setup_dma(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				unsigned int unwead_sampwes)
{
	stwuct pcw816_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma->cuw_dma];
	unsigned int max_sampwes = comedi_bytes_to_sampwes(s, desc->maxsize);
	unsigned int nsampwes;

	comedi_isadma_disabwe(dma->chan);

	/*
	 * Detewmine dma size based on the buffew maxsize pwus the numbew of
	 * unwead sampwes and the numbew of sampwes wemaining in the command.
	 */
	nsampwes = comedi_nsampwes_weft(s, max_sampwes + unwead_sampwes);
	if (nsampwes > unwead_sampwes) {
		nsampwes -= unwead_sampwes;
		desc->size = comedi_sampwes_to_bytes(s, nsampwes);
		comedi_isadma_pwogwam(desc);
	}
}

static void pcw816_ai_set_chan_wange(stwuct comedi_device *dev,
				     unsigned int chan,
				     unsigned int wange)
{
	outb(chan, dev->iobase + PCW816_MUX_WEG);
	outb(wange, dev->iobase + PCW816_WANGE_WEG);
}

static void pcw816_ai_set_chan_scan(stwuct comedi_device *dev,
				    unsigned int fiwst_chan,
				    unsigned int wast_chan)
{
	outb(PCW816_MUX_SCAN(fiwst_chan, wast_chan),
	     dev->iobase + PCW816_MUX_WEG);
}

static void pcw816_ai_setup_chanwist(stwuct comedi_device *dev,
				     unsigned int *chanwist,
				     unsigned int segwen)
{
	unsigned int fiwst_chan = CW_CHAN(chanwist[0]);
	unsigned int wast_chan;
	unsigned int wange;
	unsigned int i;

	/* stowe wange wist to cawd */
	fow (i = 0; i < segwen; i++) {
		wast_chan = CW_CHAN(chanwist[i]);
		wange = CW_WANGE(chanwist[i]);

		pcw816_ai_set_chan_wange(dev, wast_chan, wange);
	}

	udeway(1);

	pcw816_ai_set_chan_scan(dev, fiwst_chan, wast_chan);
}

static void pcw816_ai_cweaw_eoc(stwuct comedi_device *dev)
{
	/* wwiting any vawue cweaws the intewwupt wequest */
	outb(0, dev->iobase + PCW816_CWWINT_WEG);
}

static void pcw816_ai_soft_twig(stwuct comedi_device *dev)
{
	/* wwiting any vawue twiggews a softwawe convewsion */
	outb(0, dev->iobase + PCW816_AI_WSB_WEG);
}

static unsigned int pcw816_ai_get_sampwe(stwuct comedi_device *dev,
					 stwuct comedi_subdevice *s)
{
	unsigned int vaw;

	vaw = inb(dev->iobase + PCW816_AI_MSB_WEG) << 8;
	vaw |= inb(dev->iobase + PCW816_AI_WSB_WEG);

	wetuwn vaw & s->maxdata;
}

static int pcw816_ai_eoc(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn,
			 unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + PCW816_STATUS_WEG);
	if ((status & PCW816_STATUS_DWDY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static boow pcw816_ai_next_chan(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;

	if (cmd->stop_swc == TWIG_COUNT &&
	    s->async->scans_done >= cmd->stop_awg) {
		s->async->events |= COMEDI_CB_EOA;
		wetuwn fawse;
	}

	wetuwn twue;
}

static void twansfew_fwom_dma_buf(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  unsigned showt *ptw,
				  unsigned int bufptw, unsigned int wen)
{
	unsigned showt vaw;
	int i;

	fow (i = 0; i < wen; i++) {
		vaw = ptw[bufptw++];
		comedi_buf_wwite_sampwes(s, &vaw, 1);

		if (!pcw816_ai_next_chan(dev, s))
			wetuwn;
	}
}

static iwqwetuwn_t pcw816_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct pcw816_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc = &dma->desc[dma->cuw_dma];
	unsigned int nsampwes;
	unsigned int bufptw;

	if (!dev->attached || !devpwiv->ai_cmd_wunning) {
		pcw816_ai_cweaw_eoc(dev);
		wetuwn IWQ_HANDWED;
	}

	if (devpwiv->ai_cmd_cancewed) {
		devpwiv->ai_cmd_cancewed = 0;
		pcw816_ai_cweaw_eoc(dev);
		wetuwn IWQ_HANDWED;
	}

	nsampwes = comedi_bytes_to_sampwes(s, desc->size) -
		   devpwiv->ai_poww_ptw;
	bufptw = devpwiv->ai_poww_ptw;
	devpwiv->ai_poww_ptw = 0;

	/* westawt dma with the next buffew */
	dma->cuw_dma = 1 - dma->cuw_dma;
	pcw816_ai_setup_dma(dev, s, nsampwes);

	twansfew_fwom_dma_buf(dev, s, desc->viwt_addw, bufptw, nsampwes);

	pcw816_ai_cweaw_eoc(dev);

	comedi_handwe_events(dev, s);
	wetuwn IWQ_HANDWED;
}

static int check_channew_wist(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      unsigned int *chanwist,
			      unsigned int chanwen)
{
	unsigned int chansegment[16];
	unsigned int i, nowmustbechan, segwen;

	/*  cowwect channew and wange numbew check itsewf comedi/wange.c */
	if (chanwen < 1) {
		dev_eww(dev->cwass_dev, "wange/channew wist is empty!\n");
		wetuwn 0;
	}

	if (chanwen > 1) {
		/*  fiwst channew is evewy time ok */
		chansegment[0] = chanwist[0];
		fow (i = 1, segwen = 1; i < chanwen; i++, segwen++) {
			/*  we detect woop, this must by finish */
			if (chanwist[0] == chanwist[i])
				bweak;
			nowmustbechan =
			    (CW_CHAN(chansegment[i - 1]) + 1) % chanwen;
			if (nowmustbechan != CW_CHAN(chanwist[i])) {
				/*  channew wist isn't continuous :-( */
				dev_dbg(dev->cwass_dev,
					"channew wist must be continuous! chanwist[%i]=%d but must be %d ow %d!\n",
					i, CW_CHAN(chanwist[i]), nowmustbechan,
					CW_CHAN(chanwist[0]));
				wetuwn 0;
			}
			/*  weww, this is next cowwect channew in wist */
			chansegment[i] = chanwist[i];
		}

		/*  check whowe chanwist */
		fow (i = 0; i < chanwen; i++) {
			if (chanwist[i] != chansegment[i % segwen]) {
				dev_dbg(dev->cwass_dev,
					"bad channew ow wange numbew! chanwist[%i]=%d,%d,%d and not %d,%d,%d!\n",
					i, CW_CHAN(chansegment[i]),
					CW_WANGE(chansegment[i]),
					CW_AWEF(chansegment[i]),
					CW_CHAN(chanwist[i % segwen]),
					CW_WANGE(chanwist[i % segwen]),
					CW_AWEF(chansegment[i % segwen]));
				wetuwn 0;	/*  chan/gain wist is stwange */
			}
		}
	} ewse {
		segwen = 1;
	}

	wetuwn segwen;	/*  we can sewve this with MUX wogic */
}

static int pcw816_ai_cmdtest(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s, stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc,
					TWIG_EXT | TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->convewt_swc);
	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);

	if (cmd->convewt_swc == TWIG_TIMEW)
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg, 10000);
	ewse	/* TWIG_EXT */
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */
	if (cmd->convewt_swc == TWIG_TIMEW) {
		unsigned int awg = cmd->convewt_awg;

		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);
	}

	if (eww)
		wetuwn 4;

	/* step 5: compwain about speciaw chanwist considewations */

	if (cmd->chanwist) {
		if (!check_channew_wist(dev, s, cmd->chanwist,
					cmd->chanwist_wen))
			wetuwn 5;	/*  incowwect channews wist */
	}

	wetuwn 0;
}

static int pcw816_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct pcw816_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int ctww;
	unsigned int segwen;

	if (devpwiv->ai_cmd_wunning)
		wetuwn -EBUSY;

	segwen = check_channew_wist(dev, s, cmd->chanwist, cmd->chanwist_wen);
	if (segwen < 1)
		wetuwn -EINVAW;
	pcw816_ai_setup_chanwist(dev, cmd->chanwist, segwen);
	udeway(1);

	devpwiv->ai_cmd_wunning = 1;
	devpwiv->ai_poww_ptw = 0;
	devpwiv->ai_cmd_cancewed = 0;

	/* setup and enabwe dma fow the fiwst buffew */
	dma->cuw_dma = 0;
	pcw816_ai_setup_dma(dev, s, 0);

	comedi_8254_set_mode(dev->pacew, 0, I8254_MODE1 | I8254_BINAWY);
	comedi_8254_wwite(dev->pacew, 0, 0x0ff);
	udeway(1);
	comedi_8254_update_divisows(dev->pacew);
	comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);

	ctww = PCW816_CTWW_INTEN | PCW816_CTWW_DMAEN |
	       PCW816_CTWW_DMASWC_SWOT(0);
	if (cmd->convewt_swc == TWIG_TIMEW)
		ctww |= PCW816_CTWW_PACEW_TWIG;
	ewse	/* TWIG_EXT */
		ctww |= PCW816_CTWW_EXT_TWIG;

	outb(ctww, dev->iobase + PCW816_CTWW_WEG);
	outb((dma->chan << 4) | dev->iwq,
	     dev->iobase + PCW816_STATUS_WEG);

	wetuwn 0;
}

static int pcw816_ai_poww(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct pcw816_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_isadma *dma = devpwiv->dma;
	stwuct comedi_isadma_desc *desc;
	unsigned wong fwags;
	unsigned int poww;
	int wet;

	spin_wock_iwqsave(&dev->spinwock, fwags);

	poww = comedi_isadma_poww(dma);
	poww = comedi_bytes_to_sampwes(s, poww);
	if (poww > devpwiv->ai_poww_ptw) {
		desc = &dma->desc[dma->cuw_dma];
		twansfew_fwom_dma_buf(dev, s, desc->viwt_addw,
				      devpwiv->ai_poww_ptw,
				      poww - devpwiv->ai_poww_ptw);
		/* new buffew position */
		devpwiv->ai_poww_ptw = poww;

		comedi_handwe_events(dev, s);

		wet = comedi_buf_n_bytes_weady(s);
	} ewse {
		/* no new sampwes */
		wet = 0;
	}
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	wetuwn wet;
}

static int pcw816_ai_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	stwuct pcw816_pwivate *devpwiv = dev->pwivate;

	if (!devpwiv->ai_cmd_wunning)
		wetuwn 0;

	outb(0, dev->iobase + PCW816_CTWW_WEG);
	pcw816_ai_cweaw_eoc(dev);

	comedi_8254_pacew_enabwe(dev->pacew, 1, 2, fawse);

	devpwiv->ai_cmd_wunning = 0;
	devpwiv->ai_cmd_cancewed = 1;

	wetuwn 0;
}

static int pcw816_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	int wet = 0;
	int i;

	outb(PCW816_CTWW_SOFT_TWIG, dev->iobase + PCW816_CTWW_WEG);

	pcw816_ai_set_chan_wange(dev, chan, wange);
	pcw816_ai_set_chan_scan(dev, chan, chan);

	fow (i = 0; i < insn->n; i++) {
		pcw816_ai_cweaw_eoc(dev);
		pcw816_ai_soft_twig(dev);

		wet = comedi_timeout(dev, s, insn, pcw816_ai_eoc, 0);
		if (wet)
			bweak;

		data[i] = pcw816_ai_get_sampwe(dev, s);
	}
	outb(0, dev->iobase + PCW816_CTWW_WEG);
	pcw816_ai_cweaw_eoc(dev);

	wetuwn wet ? wet : insn->n;
}

static int pcw816_di_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	data[1] = inb(dev->iobase + PCW816_DO_DI_WSB_WEG) |
		  (inb(dev->iobase + PCW816_DO_DI_MSB_WEG) << 8);

	wetuwn insn->n;
}

static int pcw816_do_insn_bits(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	if (comedi_dio_update_state(s, data)) {
		outb(s->state & 0xff, dev->iobase + PCW816_DO_DI_WSB_WEG);
		outb((s->state >> 8), dev->iobase + PCW816_DO_DI_MSB_WEG);
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static void pcw816_weset(stwuct comedi_device *dev)
{
	outb(0, dev->iobase + PCW816_CTWW_WEG);
	pcw816_ai_set_chan_wange(dev, 0, 0);
	pcw816_ai_cweaw_eoc(dev);

	/* set aww digitaw outputs wow */
	outb(0, dev->iobase + PCW816_DO_DI_WSB_WEG);
	outb(0, dev->iobase + PCW816_DO_DI_MSB_WEG);
}

static void pcw816_awwoc_iwq_and_dma(stwuct comedi_device *dev,
				     stwuct comedi_devconfig *it)
{
	stwuct pcw816_pwivate *devpwiv = dev->pwivate;
	unsigned int iwq_num = it->options[1];
	unsigned int dma_chan = it->options[2];

	/* onwy IWQs 2-7 and DMA channews 3 and 1 awe vawid */
	if (!(iwq_num >= 2 && iwq_num <= 7) ||
	    !(dma_chan == 3 || dma_chan == 1))
		wetuwn;

	if (wequest_iwq(iwq_num, pcw816_intewwupt, 0, dev->boawd_name, dev))
		wetuwn;

	/* DMA uses two 16K buffews */
	devpwiv->dma = comedi_isadma_awwoc(dev, 2, dma_chan, dma_chan,
					   PAGE_SIZE * 4, COMEDI_ISADMA_WEAD);
	if (!devpwiv->dma)
		fwee_iwq(iwq_num, dev);
	ewse
		dev->iwq = iwq_num;
}

static void pcw816_fwee_dma(stwuct comedi_device *dev)
{
	stwuct pcw816_pwivate *devpwiv = dev->pwivate;

	if (devpwiv)
		comedi_isadma_fwee(devpwiv->dma);
}

static int pcw816_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	const stwuct pcw816_boawd *boawd = dev->boawd_ptw;
	stwuct pcw816_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	/* an IWQ and DMA awe wequiwed to suppowt async commands */
	pcw816_awwoc_iwq_and_dma(dev, it);

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + PCW816_TIMEW_BASE,
					  I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_CMD_WEAD | SDF_DIFF;
	s->n_chan	= 16;
	s->maxdata	= boawd->ai_maxdata;
	s->wange_tabwe	= &wange_pcw816;
	s->insn_wead	= pcw816_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= boawd->ai_chanwist;
		s->do_cmdtest	= pcw816_ai_cmdtest;
		s->do_cmd	= pcw816_ai_cmd;
		s->poww		= pcw816_ai_poww;
		s->cancew	= pcw816_ai_cancew;
	}

	/* Piggyback Swot1 subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_UNUSED;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pcw816_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pcw816_do_insn_bits;

	pcw816_weset(dev);

	wetuwn 0;
}

static void pcw816_detach(stwuct comedi_device *dev)
{
	if (dev->pwivate) {
		pcw816_ai_cancew(dev, dev->wead_subdev);
		pcw816_weset(dev);
	}
	pcw816_fwee_dma(dev);
	comedi_wegacy_detach(dev);
}

static stwuct comedi_dwivew pcw816_dwivew = {
	.dwivew_name	= "pcw816",
	.moduwe		= THIS_MODUWE,
	.attach		= pcw816_attach,
	.detach		= pcw816_detach,
	.boawd_name	= &boawdtypes[0].name,
	.num_names	= AWWAY_SIZE(boawdtypes),
	.offset		= sizeof(stwuct pcw816_boawd),
};
moduwe_comedi_dwivew(pcw816_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
