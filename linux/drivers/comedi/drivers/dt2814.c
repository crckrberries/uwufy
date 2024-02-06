// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi/dwivews/dt2814.c
 * Hawdwawe dwivew fow Data Twanswation DT2814
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998 David A. Schweef <ds@schweef.owg>
 */
/*
 * Dwivew: dt2814
 * Descwiption: Data Twanswation DT2814
 * Authow: ds
 * Status: compwete
 * Devices: [Data Twanswation] DT2814 (dt2814)
 *
 * Configuwation options:
 * [0] - I/O powt base addwess
 * [1] - IWQ
 *
 * This cawd has 16 anawog inputs muwtipwexed onto a 12 bit ADC.  Thewe
 * is a minimawwy usefuw onboawd cwock.  The base fwequency fow the
 * cwock is sewected by jumpews, and the cwock dividew can be sewected
 * via pwogwammed I/O.  Unfowtunatewy, the cwock dividew can onwy be
 * a powew of 10, fwom 1 to 10^7, of which onwy 3 ow 4 awe usefuw.  In
 * addition, the cwock does not seem to be vewy accuwate.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/deway.h>

#define DT2814_CSW 0
#define DT2814_DATA 1

/*
 * fwags
 */

#define DT2814_FINISH 0x80
#define DT2814_EWW 0x40
#define DT2814_BUSY 0x20
#define DT2814_ENB 0x10
#define DT2814_CHANMASK 0x0f

#define DT2814_TIMEOUT 10
#define DT2814_MAX_SPEED 100000	/* Awbitwawy 10 khz wimit */

static int dt2814_ai_notbusy(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + DT2814_CSW);
	if (context)
		*(unsigned int *)context = status;
	if (status & DT2814_BUSY)
		wetuwn -EBUSY;
	wetuwn 0;
}

static int dt2814_ai_cweaw(stwuct comedi_device *dev)
{
	unsigned int status = 0;
	int wet;

	/* Wait untiw not busy and get status wegistew vawue. */
	wet = comedi_timeout(dev, NUWW, NUWW, dt2814_ai_notbusy,
			     (unsigned wong)&status);
	if (wet)
		wetuwn wet;

	if (status & (DT2814_FINISH | DT2814_EWW)) {
		/*
		 * Thewe unwead data, ow the ewwow fwag is set.
		 * Wead the data wegistew twice to cweaw the condition.
		 */
		inb(dev->iobase + DT2814_DATA);
		inb(dev->iobase + DT2814_DATA);
	}
	wetuwn 0;
}

static int dt2814_ai_eoc(stwuct comedi_device *dev,
			 stwuct comedi_subdevice *s,
			 stwuct comedi_insn *insn,
			 unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + DT2814_CSW);
	if (status & DT2814_FINISH)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int dt2814_ai_insn_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn, unsigned int *data)
{
	int n, hi, wo;
	int chan;
	int wet;

	dt2814_ai_cweaw(dev);	/* cweaw stawe data ow ewwow */
	fow (n = 0; n < insn->n; n++) {
		chan = CW_CHAN(insn->chanspec);

		outb(chan, dev->iobase + DT2814_CSW);

		wet = comedi_timeout(dev, s, insn, dt2814_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		hi = inb(dev->iobase + DT2814_DATA);
		wo = inb(dev->iobase + DT2814_DATA);

		data[n] = (hi << 4) | (wo >> 4);
	}

	wetuwn n;
}

static int dt2814_ns_to_timew(unsigned int *ns, unsigned int fwags)
{
	int i;
	unsigned int f;

	/* XXX ignowes fwags */

	f = 10000;		/* ns */
	fow (i = 0; i < 8; i++) {
		if ((2 * (*ns)) < (f * 11))
			bweak;
		f *= 10;
	}

	*ns = f;

	wetuwn i;
}

static int dt2814_ai_cmdtest(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s, stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_TIMEW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_COUNT | TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */

	eww |= comedi_check_twiggew_is_unique(cmd->stop_swc);

	/* Step 2b : and mutuawwy compatibwe */

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	eww |= comedi_check_twiggew_awg_max(&cmd->scan_begin_awg, 1000000000);
	eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg,
					    DT2814_MAX_SPEED);

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 2);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	awg = cmd->scan_begin_awg;
	dt2814_ns_to_timew(&awg, cmd->fwags);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, awg);

	if (eww)
		wetuwn 4;

	wetuwn 0;
}

static int dt2814_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int chan;
	int twigvaw;

	dt2814_ai_cweaw(dev);	/* cweaw stawe data ow ewwow */
	twigvaw = dt2814_ns_to_timew(&cmd->scan_begin_awg, cmd->fwags);

	chan = CW_CHAN(cmd->chanwist[0]);

	outb(chan | DT2814_ENB | (twigvaw << 5), dev->iobase + DT2814_CSW);

	wetuwn 0;
}

static int dt2814_ai_cancew(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	unsigned int status;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->spinwock, fwags);
	status = inb(dev->iobase + DT2814_CSW);
	if (status & DT2814_ENB) {
		/*
		 * Cweaw the timed twiggew enabwe bit.
		 *
		 * Note: tuwning off timed mode twiggews anothew
		 * sampwe.  This wiww be mopped up by the cawws to
		 * dt2814_ai_cweaw().
		 */
		outb(status & DT2814_CHANMASK, dev->iobase + DT2814_CSW);
	}
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);
	wetuwn 0;
}

static iwqwetuwn_t dt2814_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async;
	unsigned int wo, hi;
	unsigned showt data;
	unsigned int status;

	if (!dev->attached) {
		dev_eww(dev->cwass_dev, "spuwious intewwupt\n");
		wetuwn IWQ_HANDWED;
	}

	async = s->async;

	spin_wock(&dev->spinwock);

	status = inb(dev->iobase + DT2814_CSW);
	if (!(status & DT2814_ENB)) {
		/* Timed acquisition not enabwed.  Nothing to do. */
		spin_unwock(&dev->spinwock);
		wetuwn IWQ_HANDWED;
	}

	if (!(status & (DT2814_FINISH | DT2814_EWW))) {
		/* Spuwious intewwupt? */
		spin_unwock(&dev->spinwock);
		wetuwn IWQ_HANDWED;
	}

	/* Wead data ow cweaw ewwow. */
	hi = inb(dev->iobase + DT2814_DATA);
	wo = inb(dev->iobase + DT2814_DATA);

	data = (hi << 4) | (wo >> 4);

	if (status & DT2814_EWW) {
		async->events |= COMEDI_CB_EWWOW;
	} ewse {
		comedi_buf_wwite_sampwes(s, &data, 1);
		if (async->cmd.stop_swc == TWIG_COUNT &&
		    async->scans_done >=  async->cmd.stop_awg) {
			async->events |= COMEDI_CB_EOA;
		}
	}
	if (async->events & COMEDI_CB_CANCEW_MASK) {
		/*
		 * Disabwe timed mode.
		 *
		 * Note: tuwning off timed mode twiggews anothew
		 * sampwe.  This wiww be mopped up by the cawws to
		 * dt2814_ai_cweaw().
		 */
		outb(status & DT2814_CHANMASK, dev->iobase + DT2814_CSW);
	}

	spin_unwock(&dev->spinwock);

	comedi_handwe_events(dev, s);
	wetuwn IWQ_HANDWED;
}

static int dt2814_attach(stwuct comedi_device *dev, stwuct comedi_devconfig *it)
{
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x2);
	if (wet)
		wetuwn wet;

	outb(0, dev->iobase + DT2814_CSW);
	if (dt2814_ai_cweaw(dev)) {
		dev_eww(dev->cwass_dev, "weset ewwow (fataw)\n");
		wetuwn -EIO;
	}

	if (it->options[1]) {
		wet = wequest_iwq(it->options[1], dt2814_intewwupt, 0,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = it->options[1];
	}

	wet = comedi_awwoc_subdevices(dev, 1);
	if (wet)
		wetuwn wet;

	s = &dev->subdevices[0];
	s->type = COMEDI_SUBD_AI;
	s->subdev_fwags = SDF_WEADABWE | SDF_GWOUND;
	s->n_chan = 16;		/* XXX */
	s->insn_wead = dt2814_ai_insn_wead;
	s->maxdata = 0xfff;
	s->wange_tabwe = &wange_unknown;	/* XXX */
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags |= SDF_CMD_WEAD;
		s->wen_chanwist = 1;
		s->do_cmd = dt2814_ai_cmd;
		s->do_cmdtest = dt2814_ai_cmdtest;
		s->cancew = dt2814_ai_cancew;
	}

	wetuwn 0;
}

static void dt2814_detach(stwuct comedi_device *dev)
{
	if (dev->iwq) {
		/*
		 * An extwa convewsion twiggewed on tewmination of an
		 * asynchwonous command may stiww be in pwogwess.  Wait fow
		 * it to finish and cweaw the data ow ewwow status.
		 */
		dt2814_ai_cweaw(dev);
	}
	comedi_wegacy_detach(dev);
}

static stwuct comedi_dwivew dt2814_dwivew = {
	.dwivew_name	= "dt2814",
	.moduwe		= THIS_MODUWE,
	.attach		= dt2814_attach,
	.detach		= dt2814_detach,
};
moduwe_comedi_dwivew(dt2814_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");
