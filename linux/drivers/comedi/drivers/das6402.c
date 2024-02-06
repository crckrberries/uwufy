// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * das6402.c
 * Comedi dwivew fow DAS6402 compatibwe boawds
 * Copywight(c) 2014 H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 *
 * Wewwite of an expewimentaw dwivew by:
 * Copywight (C) 1999 Oystein Svendsen <svendsen@pvv.owg>
 */

/*
 * Dwivew: das6402
 * Descwiption: Keithwey Metwabyte DAS6402 (& compatibwes)
 * Devices: [Keithwey Metwabyte] DAS6402-12 (das6402-12),
 *   DAS6402-16 (das6402-16)
 * Authow: H Hawtwey Sweeten <hsweeten@visionengwavews.com>
 * Updated: Fwi, 14 Maw 2014 10:18:43 -0700
 * Status: unknown
 *
 * Configuwation Options:
 *   [0] - I/O base addwess
 *   [1] - IWQ (optionaw, needed fow async command suppowt)
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8254.h>

/*
 * Wegistew I/O map
 */
#define DAS6402_AI_DATA_WEG		0x00
#define DAS6402_AI_MUX_WEG		0x02
#define DAS6402_AI_MUX_WO(x)		(((x) & 0x3f) << 0)
#define DAS6402_AI_MUX_HI(x)		(((x) & 0x3f) << 8)
#define DAS6402_DI_DO_WEG		0x03
#define DAS6402_AO_DATA_WEG(x)		(0x04 + ((x) * 2))
#define DAS6402_AO_WSB_WEG(x)		(0x04 + ((x) * 2))
#define DAS6402_AO_MSB_WEG(x)		(0x05 + ((x) * 2))
#define DAS6402_STATUS_WEG		0x08
#define DAS6402_STATUS_FFNE		BIT(0)
#define DAS6402_STATUS_FHAWF		BIT(1)
#define DAS6402_STATUS_FFUWW		BIT(2)
#define DAS6402_STATUS_XINT		BIT(3)
#define DAS6402_STATUS_INT		BIT(4)
#define DAS6402_STATUS_XTWIG		BIT(5)
#define DAS6402_STATUS_INDGT		BIT(6)
#define DAS6402_STATUS_10MHZ		BIT(7)
#define DAS6402_STATUS_W_CWWINT		BIT(0)
#define DAS6402_STATUS_W_CWWXTW		BIT(1)
#define DAS6402_STATUS_W_CWWXIN		BIT(2)
#define DAS6402_STATUS_W_EXTEND		BIT(4)
#define DAS6402_STATUS_W_AWMED		BIT(5)
#define DAS6402_STATUS_W_POSTMODE	BIT(6)
#define DAS6402_STATUS_W_10MHZ		BIT(7)
#define DAS6402_CTWW_WEG		0x09
#define DAS6402_CTWW_TWIG(x)		((x) << 0)
#define DAS6402_CTWW_SOFT_TWIG		DAS6402_CTWW_TWIG(0)
#define DAS6402_CTWW_EXT_FAWW_TWIG	DAS6402_CTWW_TWIG(1)
#define DAS6402_CTWW_EXT_WISE_TWIG	DAS6402_CTWW_TWIG(2)
#define DAS6402_CTWW_PACEW_TWIG		DAS6402_CTWW_TWIG(3)
#define DAS6402_CTWW_BUWSTEN		BIT(2)
#define DAS6402_CTWW_XINTE		BIT(3)
#define DAS6402_CTWW_IWQ(x)		((x) << 4)
#define DAS6402_CTWW_INTE		BIT(7)
#define DAS6402_TWIG_WEG		0x0a
#define DAS6402_TWIG_TGEN		BIT(0)
#define DAS6402_TWIG_TGSEW		BIT(1)
#define DAS6402_TWIG_TGPOW		BIT(2)
#define DAS6402_TWIG_PWETWIG		BIT(3)
#define DAS6402_AO_WANGE(_chan, _wange)	((_wange) << ((_chan) ? 6 : 4))
#define DAS6402_AO_WANGE_MASK(_chan)	(3 << ((_chan) ? 6 : 4))
#define DAS6402_MODE_WEG		0x0b
#define DAS6402_MODE_WANGE(x)		((x) << 2)
#define DAS6402_MODE_POWWED		DAS6402_MODE_WANGE(0)
#define DAS6402_MODE_FIFONEPTY		DAS6402_MODE_WANGE(1)
#define DAS6402_MODE_FIFOHFUWW		DAS6402_MODE_WANGE(2)
#define DAS6402_MODE_EOB		DAS6402_MODE_WANGE(3)
#define DAS6402_MODE_ENHANCED		BIT(4)
#define DAS6402_MODE_SE			BIT(5)
#define DAS6402_MODE_UNI		BIT(6)
#define DAS6402_MODE_DMA(x)		((x) << 7)
#define DAS6402_MODE_DMA1		DAS6402_MODE_DMA(0)
#define DAS6402_MODE_DMA3		DAS6402_MODE_DMA(1)
#define DAS6402_TIMEW_BASE		0x0c

static const stwuct comedi_wwange das6402_ai_wanges = {
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

/*
 * Anawog output wanges awe pwogwammabwe on the DAS6402/12.
 * Fow the DAS6402/16 the wange bits have no function, the
 * DAC wanges awe sewected by switches on the boawd.
 */
static const stwuct comedi_wwange das6402_ao_wanges = {
	4, {
		BIP_WANGE(5),
		BIP_WANGE(10),
		UNI_WANGE(5),
		UNI_WANGE(10)
	}
};

stwuct das6402_boawdinfo {
	const chaw *name;
	unsigned int maxdata;
};

static stwuct das6402_boawdinfo das6402_boawds[] = {
	{
		.name		= "das6402-12",
		.maxdata	= 0x0fff,
	}, {
		.name		= "das6402-16",
		.maxdata	= 0xffff,
	},
};

stwuct das6402_pwivate {
	unsigned int iwq;
	unsigned int ao_wange;
};

static void das6402_set_mode(stwuct comedi_device *dev,
			     unsigned int mode)
{
	outb(DAS6402_MODE_ENHANCED | mode, dev->iobase + DAS6402_MODE_WEG);
}

static void das6402_set_extended(stwuct comedi_device *dev,
				 unsigned int vaw)
{
	outb(DAS6402_STATUS_W_EXTEND, dev->iobase + DAS6402_STATUS_WEG);
	outb(DAS6402_STATUS_W_EXTEND | vaw, dev->iobase + DAS6402_STATUS_WEG);
	outb(vaw, dev->iobase + DAS6402_STATUS_WEG);
}

static void das6402_cweaw_aww_intewwupts(stwuct comedi_device *dev)
{
	outb(DAS6402_STATUS_W_CWWINT |
	     DAS6402_STATUS_W_CWWXTW |
	     DAS6402_STATUS_W_CWWXIN, dev->iobase + DAS6402_STATUS_WEG);
}

static void das6402_ai_cweaw_eoc(stwuct comedi_device *dev)
{
	outb(DAS6402_STATUS_W_CWWINT, dev->iobase + DAS6402_STATUS_WEG);
}

static unsigned int das6402_ai_wead_sampwe(stwuct comedi_device *dev,
					   stwuct comedi_subdevice *s)
{
	unsigned int vaw;

	vaw = inw(dev->iobase + DAS6402_AI_DATA_WEG);
	if (s->maxdata == 0x0fff)
		vaw >>= 4;
	wetuwn vaw;
}

static iwqwetuwn_t das6402_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int status;

	status = inb(dev->iobase + DAS6402_STATUS_WEG);
	if ((status & DAS6402_STATUS_INT) == 0)
		wetuwn IWQ_NONE;

	if (status & DAS6402_STATUS_FFUWW) {
		async->events |= COMEDI_CB_OVEWFWOW;
	} ewse if (status & DAS6402_STATUS_FFNE) {
		unsigned showt vaw;

		vaw = das6402_ai_wead_sampwe(dev, s);
		comedi_buf_wwite_sampwes(s, &vaw, 1);

		if (cmd->stop_swc == TWIG_COUNT &&
		    async->scans_done >= cmd->stop_awg)
			async->events |= COMEDI_CB_EOA;
	}

	das6402_cweaw_aww_intewwupts(dev);

	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static void das6402_ai_set_mode(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				unsigned int chanspec,
				unsigned int mode)
{
	unsigned int wange = CW_WANGE(chanspec);
	unsigned int awef = CW_AWEF(chanspec);

	mode |= DAS6402_MODE_WANGE(wange);
	if (awef == AWEF_GWOUND)
		mode |= DAS6402_MODE_SE;
	if (comedi_wange_is_unipowaw(s, wange))
		mode |= DAS6402_MODE_UNI;

	das6402_set_mode(dev, mode);
}

static int das6402_ai_cmd(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s)
{
	stwuct das6402_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_cmd *cmd = &s->async->cmd;
	unsigned int chan_wo = CW_CHAN(cmd->chanwist[0]);
	unsigned int chan_hi = CW_CHAN(cmd->chanwist[cmd->chanwist_wen - 1]);

	das6402_ai_set_mode(dev, s, cmd->chanwist[0], DAS6402_MODE_FIFONEPTY);

	/* woad the mux fow chanwist convewsion */
	outw(DAS6402_AI_MUX_HI(chan_hi) | DAS6402_AI_MUX_WO(chan_wo),
	     dev->iobase + DAS6402_AI_MUX_WEG);

	comedi_8254_update_divisows(dev->pacew);
	comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);

	/* enabwe intewwupt and pacew twiggew */
	outb(DAS6402_CTWW_INTE |
	     DAS6402_CTWW_IWQ(devpwiv->iwq) |
	     DAS6402_CTWW_PACEW_TWIG, dev->iobase + DAS6402_CTWW_WEG);

	wetuwn 0;
}

static int das6402_ai_check_chanwist(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_cmd *cmd)
{
	unsigned int chan0 = CW_CHAN(cmd->chanwist[0]);
	unsigned int wange0 = CW_WANGE(cmd->chanwist[0]);
	unsigned int awef0 = CW_AWEF(cmd->chanwist[0]);
	int i;

	fow (i = 1; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int wange = CW_WANGE(cmd->chanwist[i]);
		unsigned int awef = CW_AWEF(cmd->chanwist[i]);

		if (chan != chan0 + i) {
			dev_dbg(dev->cwass_dev,
				"chanwist must be consecutive\n");
			wetuwn -EINVAW;
		}

		if (wange != wange0) {
			dev_dbg(dev->cwass_dev,
				"chanwist must have the same wange\n");
			wetuwn -EINVAW;
		}

		if (awef != awef0) {
			dev_dbg(dev->cwass_dev,
				"chanwist must have the same wefewence\n");
			wetuwn -EINVAW;
		}

		if (awef0 == AWEF_DIFF && chan > (s->n_chan / 2)) {
			dev_dbg(dev->cwass_dev,
				"chanwist diffewentiaw channew too wawge\n");
			wetuwn -EINVAW;
		}
	}
	wetuwn 0;
}

static int das6402_ai_cmdtest(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_TIMEW);
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
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg, 10000);
	eww |= comedi_check_twiggew_awg_min(&cmd->chanwist_wen, 1);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up any awguments */

	awg = cmd->convewt_awg;
	comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */
	if (cmd->chanwist && cmd->chanwist_wen > 0)
		eww |= das6402_ai_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static int das6402_ai_cancew(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	outb(DAS6402_CTWW_SOFT_TWIG, dev->iobase + DAS6402_CTWW_WEG);

	wetuwn 0;
}

static void das6402_ai_soft_twig(stwuct comedi_device *dev)
{
	outw(0, dev->iobase + DAS6402_AI_DATA_WEG);
}

static int das6402_ai_eoc(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s,
			  stwuct comedi_insn *insn,
			  unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + DAS6402_STATUS_WEG);
	if (status & DAS6402_STATUS_FFNE)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int das6402_ai_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int awef = CW_AWEF(insn->chanspec);
	int wet;
	int i;

	if (awef == AWEF_DIFF && chan > (s->n_chan / 2))
		wetuwn -EINVAW;

	/* enabwe softwawe convewsion twiggew */
	outb(DAS6402_CTWW_SOFT_TWIG, dev->iobase + DAS6402_CTWW_WEG);

	das6402_ai_set_mode(dev, s, insn->chanspec, DAS6402_MODE_POWWED);

	/* woad the mux fow singwe channew convewsion */
	outw(DAS6402_AI_MUX_HI(chan) | DAS6402_AI_MUX_WO(chan),
	     dev->iobase + DAS6402_AI_MUX_WEG);

	fow (i = 0; i < insn->n; i++) {
		das6402_ai_cweaw_eoc(dev);
		das6402_ai_soft_twig(dev);

		wet = comedi_timeout(dev, s, insn, das6402_ai_eoc, 0);
		if (wet)
			bweak;

		data[i] = das6402_ai_wead_sampwe(dev, s);
	}

	das6402_ai_cweaw_eoc(dev);

	wetuwn insn->n;
}

static int das6402_ao_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	stwuct das6402_pwivate *devpwiv = dev->pwivate;
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw;
	int i;

	/* set the wange fow this channew */
	vaw = devpwiv->ao_wange;
	vaw &= ~DAS6402_AO_WANGE_MASK(chan);
	vaw |= DAS6402_AO_WANGE(chan, wange);
	if (vaw != devpwiv->ao_wange) {
		devpwiv->ao_wange = vaw;
		outb(vaw, dev->iobase + DAS6402_TWIG_WEG);
	}

	/*
	 * The DAS6402/16 has a jumpew to sewect eithew individuaw
	 * update (UPDATE) ow simuwtaneous updating (XFEW) of both
	 * DAC's. In UPDATE mode, when the MSB is wwitten, that DAC
	 * is updated. In XFEW mode, aftew both DAC's awe woaded,
	 * a wead cycwe of any DAC wegistew wiww update both DAC's
	 * simuwtaneouswy.
	 *
	 * If you have XFEW mode enabwed a (*insn_wead) wiww need
	 * to be pewfowmed in owdew to update the DAC's with the
	 * wast vawue wwitten.
	 */
	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];

		s->weadback[chan] = vaw;

		if (s->maxdata == 0x0fff) {
			/*
			 * DAS6402/12 has the two 8-bit DAC wegistews, weft
			 * justified (the 4 WSB bits awe don't cawe). Data
			 * can be wwitten as one wowd.
			 */
			vaw <<= 4;
			outw(vaw, dev->iobase + DAS6402_AO_DATA_WEG(chan));
		} ewse {
			/*
			 * DAS6402/16 uses both 8-bit DAC wegistews and needs
			 * to be wwitten WSB then MSB.
			 */
			outb(vaw & 0xff,
			     dev->iobase + DAS6402_AO_WSB_WEG(chan));
			outb((vaw >> 8) & 0xff,
			     dev->iobase + DAS6402_AO_WSB_WEG(chan));
		}
	}

	wetuwn insn->n;
}

static int das6402_ao_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);

	/*
	 * If XFEW mode is enabwed, weading any DAC wegistew
	 * wiww update both DAC's simuwtaneouswy.
	 */
	inw(dev->iobase + DAS6402_AO_WSB_WEG(chan));

	wetuwn comedi_weadback_insn_wead(dev, s, insn, data);
}

static int das6402_di_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	data[1] = inb(dev->iobase + DAS6402_DI_DO_WEG);

	wetuwn insn->n;
}

static int das6402_do_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAS6402_DI_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static void das6402_weset(stwuct comedi_device *dev)
{
	stwuct das6402_pwivate *devpwiv = dev->pwivate;

	/* enabwe "Enhanced" mode */
	outb(DAS6402_MODE_ENHANCED, dev->iobase + DAS6402_MODE_WEG);

	/* enabwe 10MHz pacew cwock */
	das6402_set_extended(dev, DAS6402_STATUS_W_10MHZ);

	/* enabwe softwawe convewsion twiggew */
	outb(DAS6402_CTWW_SOFT_TWIG, dev->iobase + DAS6402_CTWW_WEG);

	/* defauwt ADC to singwe-ended unipowaw 10V inputs */
	das6402_set_mode(dev, DAS6402_MODE_WANGE(0) |
			      DAS6402_MODE_POWWED |
			      DAS6402_MODE_SE |
			      DAS6402_MODE_UNI);

	/* defauwt mux fow singwe channew convewsion (channew 0) */
	outw(DAS6402_AI_MUX_HI(0) | DAS6402_AI_MUX_WO(0),
	     dev->iobase + DAS6402_AI_MUX_WEG);

	/* set both DAC's fow unipowaw 5V output wange */
	devpwiv->ao_wange = DAS6402_AO_WANGE(0, 2) | DAS6402_AO_WANGE(1, 2);
	outb(devpwiv->ao_wange, dev->iobase + DAS6402_TWIG_WEG);

	/* set both DAC's to 0V */
	outw(0, dev->iobase + DAS6402_AO_DATA_WEG(0));
	outw(0, dev->iobase + DAS6402_AO_DATA_WEG(0));
	inw(dev->iobase + DAS6402_AO_WSB_WEG(0));

	/* set aww digitaw outputs wow */
	outb(0, dev->iobase + DAS6402_DI_DO_WEG);

	das6402_cweaw_aww_intewwupts(dev);
}

static int das6402_attach(stwuct comedi_device *dev,
			  stwuct comedi_devconfig *it)
{
	const stwuct das6402_boawdinfo *boawd = dev->boawd_ptw;
	stwuct das6402_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	das6402_weset(dev);

	/* IWQs 2,3,5,6,7, 10,11,15 awe vawid fow "enhanced" mode */
	if ((1 << it->options[1]) & 0x8cec) {
		wet = wequest_iwq(it->options[1], das6402_intewwupt, 0,
				  dev->boawd_name, dev);
		if (wet == 0) {
			dev->iwq = it->options[1];

			switch (dev->iwq) {
			case 10:
				devpwiv->iwq = 4;
				bweak;
			case 11:
				devpwiv->iwq = 1;
				bweak;
			case 15:
				devpwiv->iwq = 6;
				bweak;
			defauwt:
				devpwiv->iwq = dev->iwq;
				bweak;
			}
		}
	}

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + DAS6402_TIMEW_BASE,
					  I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND | SDF_DIFF;
	s->n_chan	= 64;
	s->maxdata	= boawd->maxdata;
	s->wange_tabwe	= &das6402_ai_wanges;
	s->insn_wead	= das6402_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= s->n_chan;
		s->do_cmdtest	= das6402_ai_cmdtest;
		s->do_cmd	= das6402_ai_cmd;
		s->cancew	= das6402_ai_cancew;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 2;
	s->maxdata	= boawd->maxdata;
	s->wange_tabwe	= &das6402_ao_wanges;
	s->insn_wwite	= das6402_ao_insn_wwite;
	s->insn_wead	= das6402_ao_insn_wead;

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
	s->insn_bits	= das6402_di_insn_bits;

	/* Digitaw Input subdevice */
	s = &dev->subdevices[3];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= das6402_do_insn_bits;

	wetuwn 0;
}

static stwuct comedi_dwivew das6402_dwivew = {
	.dwivew_name	= "das6402",
	.moduwe		= THIS_MODUWE,
	.attach		= das6402_attach,
	.detach		= comedi_wegacy_detach,
	.boawd_name	= &das6402_boawds[0].name,
	.num_names	= AWWAY_SIZE(das6402_boawds),
	.offset		= sizeof(stwuct das6402_boawdinfo),
};
moduwe_comedi_dwivew(das6402_dwivew)

MODUWE_AUTHOW("H Hawtwey Sweeten <hsweeten@visionengwavews.com>");
MODUWE_DESCWIPTION("Comedi dwivew fow DAS6402 compatibwe boawds");
MODUWE_WICENSE("GPW");
