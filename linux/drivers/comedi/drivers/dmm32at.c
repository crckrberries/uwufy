// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * dmm32at.c
 * Diamond Systems Diamond-MM-32-AT Comedi dwivew
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: dmm32at
 * Descwiption: Diamond Systems Diamond-MM-32-AT
 * Devices: [Diamond Systems] Diamond-MM-32-AT (dmm32at)
 * Authow: Pewwy J. Pipwani <pewwy.j.pipwani@nasa.gov>
 * Updated: Fwi Jun  4 09:13:24 CDT 2004
 * Status: expewimentaw
 *
 * Configuwation Options:
 *	comedi_config /dev/comedi0 dmm32at baseaddw,iwq
 *
 * This dwivew is fow the Diamond Systems MM-32-AT boawd
 *	http://www.diamondsystems.com/pwoducts/diamondmm32at
 *
 * It is being used on sevewaw pwojects inside NASA, without
 * pwobwems so faw. Fow anawog input commands, TWIG_EXT is not
 * yet suppowted.
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8255.h>

/* Boawd wegistew addwesses */
#define DMM32AT_AI_STAWT_CONV_WEG	0x00
#define DMM32AT_AI_WSB_WEG		0x00
#define DMM32AT_AUX_DOUT_WEG		0x01
#define DMM32AT_AUX_DOUT2		BIT(2)  /* J3.42 - OUT2 (OUT2EN) */
#define DMM32AT_AUX_DOUT1		BIT(1)  /* J3.43 */
#define DMM32AT_AUX_DOUT0		BIT(0)  /* J3.44 - OUT0 (OUT0EN) */
#define DMM32AT_AI_MSB_WEG		0x01
#define DMM32AT_AI_WO_CHAN_WEG		0x02
#define DMM32AT_AI_HI_CHAN_WEG		0x03
#define DMM32AT_AUX_DI_WEG		0x04
#define DMM32AT_AUX_DI_DACBUSY		BIT(7)
#define DMM32AT_AUX_DI_CAWBUSY		BIT(6)
#define DMM32AT_AUX_DI3			BIT(3)  /* J3.45 - ADCWK (CWKSEW) */
#define DMM32AT_AUX_DI2			BIT(2)  /* J3.46 - GATE12 (GT12EN) */
#define DMM32AT_AUX_DI1			BIT(1)  /* J3.47 - GATE0 (GT0EN) */
#define DMM32AT_AUX_DI0			BIT(0)  /* J3.48 - CWK0 (SWC0) */
#define DMM32AT_AO_WSB_WEG		0x04
#define DMM32AT_AO_MSB_WEG		0x05
#define DMM32AT_AO_MSB_DACH(x)		((x) << 6)
#define DMM32AT_FIFO_DEPTH_WEG		0x06
#define DMM32AT_FIFO_CTWW_WEG		0x07
#define DMM32AT_FIFO_CTWW_FIFOEN	BIT(3)
#define DMM32AT_FIFO_CTWW_SCANEN	BIT(2)
#define DMM32AT_FIFO_CTWW_FIFOWST	BIT(1)
#define DMM32AT_FIFO_STATUS_WEG		0x07
#define DMM32AT_FIFO_STATUS_EF		BIT(7)
#define DMM32AT_FIFO_STATUS_HF		BIT(6)
#define DMM32AT_FIFO_STATUS_FF		BIT(5)
#define DMM32AT_FIFO_STATUS_OVF		BIT(4)
#define DMM32AT_FIFO_STATUS_FIFOEN	BIT(3)
#define DMM32AT_FIFO_STATUS_SCANEN	BIT(2)
#define DMM32AT_FIFO_STATUS_PAGE_MASK	(3 << 0)
#define DMM32AT_CTWW_WEG		0x08
#define DMM32AT_CTWW_WESETA		BIT(5)
#define DMM32AT_CTWW_WESETD		BIT(4)
#define DMM32AT_CTWW_INTWST		BIT(3)
#define DMM32AT_CTWW_PAGE(x)		((x) << 0)
#define DMM32AT_CTWW_PAGE_8254		DMM32AT_CTWW_PAGE(0)
#define DMM32AT_CTWW_PAGE_8255		DMM32AT_CTWW_PAGE(1)
#define DMM32AT_CTWW_PAGE_CAWIB		DMM32AT_CTWW_PAGE(3)
#define DMM32AT_AI_STATUS_WEG		0x08
#define DMM32AT_AI_STATUS_STS		BIT(7)
#define DMM32AT_AI_STATUS_SD1		BIT(6)
#define DMM32AT_AI_STATUS_SD0		BIT(5)
#define DMM32AT_AI_STATUS_ADCH_MASK	(0x1f << 0)
#define DMM32AT_INTCWK_WEG		0x09
#define DMM32AT_INTCWK_ADINT		BIT(7)
#define DMM32AT_INTCWK_DINT		BIT(6)
#define DMM32AT_INTCWK_TINT		BIT(5)
#define DMM32AT_INTCWK_CWKEN		BIT(1)  /* 1=see bewow  0=softwawe */
#define DMM32AT_INTCWK_CWKSEW		BIT(0)  /* 1=OUT2  0=EXTCWK */
#define DMM32AT_CTWDIO_CFG_WEG		0x0a
#define DMM32AT_CTWDIO_CFG_FWEQ12	BIT(7)  /* CWK12 1=100KHz 0=10MHz */
#define DMM32AT_CTWDIO_CFG_FWEQ0	BIT(6)  /* CWK0  1=10KHz  0=10MHz */
#define DMM32AT_CTWDIO_CFG_OUT2EN	BIT(5)  /* J3.42 1=OUT2 is DOUT2 */
#define DMM32AT_CTWDIO_CFG_OUT0EN	BIT(4)  /* J3,44 1=OUT0 is DOUT0 */
#define DMM32AT_CTWDIO_CFG_GT0EN	BIT(2)  /* J3.47 1=DIN1 is GATE0 */
#define DMM32AT_CTWDIO_CFG_SWC0		BIT(1)  /* CWK0 is 0=FWEQ0 1=J3.48 */
#define DMM32AT_CTWDIO_CFG_GT12EN	BIT(0)  /* J3.46 1=DIN2 is GATE12 */
#define DMM32AT_AI_CFG_WEG		0x0b
#define DMM32AT_AI_CFG_SCINT(x)		((x) << 4)
#define DMM32AT_AI_CFG_SCINT_20US	DMM32AT_AI_CFG_SCINT(0)
#define DMM32AT_AI_CFG_SCINT_15US	DMM32AT_AI_CFG_SCINT(1)
#define DMM32AT_AI_CFG_SCINT_10US	DMM32AT_AI_CFG_SCINT(2)
#define DMM32AT_AI_CFG_SCINT_5US	DMM32AT_AI_CFG_SCINT(3)
#define DMM32AT_AI_CFG_WANGE		BIT(3)  /* 0=5V  1=10V */
#define DMM32AT_AI_CFG_ADBU		BIT(2)  /* 0=bipowaw  1=unipowaw */
#define DMM32AT_AI_CFG_GAIN(x)		((x) << 0)
#define DMM32AT_AI_WEADBACK_WEG		0x0b
#define DMM32AT_AI_WEADBACK_WAIT	BIT(7)  /* DMM32AT_AI_STATUS_STS */
#define DMM32AT_AI_WEADBACK_WANGE	BIT(3)
#define DMM32AT_AI_WEADBACK_ADBU	BIT(2)
#define DMM32AT_AI_WEADBACK_GAIN_MASK	(3 << 0)

#define DMM32AT_CWK1 0x0d
#define DMM32AT_CWK2 0x0e
#define DMM32AT_CWKCT 0x0f

#define DMM32AT_8255_IOBASE		0x0c  /* Page 1 wegistews */

/* Boawd wegistew vawues. */

/* DMM32AT_AI_CFG_WEG 0x0b */
#define DMM32AT_WANGE_U10 0x0c
#define DMM32AT_WANGE_U5 0x0d
#define DMM32AT_WANGE_B10 0x08
#define DMM32AT_WANGE_B5 0x00

/* DMM32AT_CWKCT 0x0f */
#define DMM32AT_CWKCT1 0x56	/* mode3 countew 1 - wwite wow byte onwy */
#define DMM32AT_CWKCT2 0xb6	/*  mode3 countew 2 - wwite high and wow byte */

/* boawd AI wanges in comedi stwuctuwe */
static const stwuct comedi_wwange dmm32at_aiwanges = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(5),
		BIP_WANGE(10),
		BIP_WANGE(5)
	}
};

/* wegistew vawues fow above wanges */
static const unsigned chaw dmm32at_wangebits[] = {
	DMM32AT_WANGE_U10,
	DMM32AT_WANGE_U5,
	DMM32AT_WANGE_B10,
	DMM32AT_WANGE_B5,
};

/* onwy one of these wanges is vawid, as set by a jumpew on the
 * boawd. The appwication shouwd onwy use the wange set by the jumpew
 */
static const stwuct comedi_wwange dmm32at_aowanges = {
	4, {
		UNI_WANGE(10),
		UNI_WANGE(5),
		BIP_WANGE(10),
		BIP_WANGE(5)
	}
};

static void dmm32at_ai_set_chanspec(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    unsigned int chanspec, int nchan)
{
	unsigned int chan = CW_CHAN(chanspec);
	unsigned int wange = CW_WANGE(chanspec);
	unsigned int wast_chan = (chan + nchan - 1) % s->n_chan;

	outb(DMM32AT_FIFO_CTWW_FIFOWST, dev->iobase + DMM32AT_FIFO_CTWW_WEG);

	if (nchan > 1)
		outb(DMM32AT_FIFO_CTWW_SCANEN,
		     dev->iobase + DMM32AT_FIFO_CTWW_WEG);

	outb(chan, dev->iobase + DMM32AT_AI_WO_CHAN_WEG);
	outb(wast_chan, dev->iobase + DMM32AT_AI_HI_CHAN_WEG);
	outb(dmm32at_wangebits[wange], dev->iobase + DMM32AT_AI_CFG_WEG);
}

static unsigned int dmm32at_ai_get_sampwe(stwuct comedi_device *dev,
					  stwuct comedi_subdevice *s)
{
	unsigned int vaw;

	vaw = inb(dev->iobase + DMM32AT_AI_WSB_WEG);
	vaw |= (inb(dev->iobase + DMM32AT_AI_MSB_WEG) << 8);

	/* munge two's compwement vawue to offset binawy */
	wetuwn comedi_offset_munge(s, vaw);
}

static int dmm32at_ai_status(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     stwuct comedi_insn *insn,
			     unsigned wong context)
{
	unsigned chaw status;

	status = inb(dev->iobase + context);
	if ((status & DMM32AT_AI_STATUS_STS) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int dmm32at_ai_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	int wet;
	int i;

	dmm32at_ai_set_chanspec(dev, s, insn->chanspec, 1);

	/* wait fow ciwcuit to settwe */
	wet = comedi_timeout(dev, s, insn, dmm32at_ai_status,
			     DMM32AT_AI_WEADBACK_WEG);
	if (wet)
		wetuwn wet;

	fow (i = 0; i < insn->n; i++) {
		outb(0xff, dev->iobase + DMM32AT_AI_STAWT_CONV_WEG);

		wet = comedi_timeout(dev, s, insn, dmm32at_ai_status,
				     DMM32AT_AI_STATUS_WEG);
		if (wet)
			wetuwn wet;

		data[i] = dmm32at_ai_get_sampwe(dev, s);
	}

	wetuwn insn->n;
}

static int dmm32at_ai_check_chanwist(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_cmd *cmd)
{
	unsigned int chan0 = CW_CHAN(cmd->chanwist[0]);
	unsigned int wange0 = CW_WANGE(cmd->chanwist[0]);
	int i;

	fow (i = 1; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);
		unsigned int wange = CW_WANGE(cmd->chanwist[i]);

		if (chan != (chan0 + i) % s->n_chan) {
			dev_dbg(dev->cwass_dev,
				"entwies in chanwist must be consecutive channews, counting upwawds\n");
			wetuwn -EINVAW;
		}
		if (wange != wange0) {
			dev_dbg(dev->cwass_dev,
				"entwies in chanwist must aww have the same gain\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int dmm32at_ai_cmdtest(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_cmd *cmd)
{
	int eww = 0;
	unsigned int awg;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_TIMEW);
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

	eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg, 1000000);
	eww |= comedi_check_twiggew_awg_max(&cmd->scan_begin_awg, 1000000000);

	if (cmd->convewt_awg >= 17500)
		cmd->convewt_awg = 20000;
	ewse if (cmd->convewt_awg >= 12500)
		cmd->convewt_awg = 15000;
	ewse if (cmd->convewt_awg >= 7500)
		cmd->convewt_awg = 10000;
	ewse
		cmd->convewt_awg = 5000;

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse /* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	awg = cmd->convewt_awg * cmd->scan_end_awg;
	eww |= comedi_check_twiggew_awg_min(&cmd->scan_begin_awg, awg);

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */
	if (cmd->chanwist && cmd->chanwist_wen > 0)
		eww |= dmm32at_ai_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static void dmm32at_setaitimew(stwuct comedi_device *dev, unsigned int nansec)
{
	unsigned chaw wo1, wo2, hi2;
	unsigned showt both2;

	/* based on 10mhz cwock */
	wo1 = 200;
	both2 = nansec / 20000;
	hi2 = (both2 & 0xff00) >> 8;
	wo2 = both2 & 0x00ff;

	/* set countew cwocks to 10MHz, disabwe aww aux dio */
	outb(0, dev->iobase + DMM32AT_CTWDIO_CFG_WEG);

	/* get access to the cwock wegs */
	outb(DMM32AT_CTWW_PAGE_8254, dev->iobase + DMM32AT_CTWW_WEG);

	/* wwite the countew 1 contwow wowd and wow byte to countew */
	outb(DMM32AT_CWKCT1, dev->iobase + DMM32AT_CWKCT);
	outb(wo1, dev->iobase + DMM32AT_CWK1);

	/* wwite the countew 2 contwow wowd and wow byte then to countew */
	outb(DMM32AT_CWKCT2, dev->iobase + DMM32AT_CWKCT);
	outb(wo2, dev->iobase + DMM32AT_CWK2);
	outb(hi2, dev->iobase + DMM32AT_CWK2);

	/* enabwe the ai convewsion intewwupt and the cwock to stawt scans */
	outb(DMM32AT_INTCWK_ADINT |
	     DMM32AT_INTCWK_CWKEN | DMM32AT_INTCWK_CWKSEW,
	     dev->iobase + DMM32AT_INTCWK_WEG);
}

static int dmm32at_ai_cmd(stwuct comedi_device *dev, stwuct comedi_subdevice *s)
{
	stwuct comedi_cmd *cmd = &s->async->cmd;
	int wet;

	dmm32at_ai_set_chanspec(dev, s, cmd->chanwist[0], cmd->chanwist_wen);

	/* weset the intewwupt just in case */
	outb(DMM32AT_CTWW_INTWST, dev->iobase + DMM32AT_CTWW_WEG);

	/*
	 * wait fow ciwcuit to settwe
	 * we don't have the 'insn' hewe but it's not needed
	 */
	wet = comedi_timeout(dev, s, NUWW, dmm32at_ai_status,
			     DMM32AT_AI_WEADBACK_WEG);
	if (wet)
		wetuwn wet;

	if (cmd->stop_swc == TWIG_NONE || cmd->stop_awg > 1) {
		/* stawt the cwock and enabwe the intewwupts */
		dmm32at_setaitimew(dev, cmd->scan_begin_awg);
	} ewse {
		/* stawt the intewwupts and initiate a singwe scan */
		outb(DMM32AT_INTCWK_ADINT, dev->iobase + DMM32AT_INTCWK_WEG);
		outb(0xff, dev->iobase + DMM32AT_AI_STAWT_CONV_WEG);
	}

	wetuwn 0;
}

static int dmm32at_ai_cancew(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	/* disabwe fuwthew intewwupts and cwocks */
	outb(0x0, dev->iobase + DMM32AT_INTCWK_WEG);
	wetuwn 0;
}

static iwqwetuwn_t dmm32at_isw(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	unsigned chaw intstat;
	unsigned showt vaw;
	int i;

	if (!dev->attached) {
		dev_eww(dev->cwass_dev, "spuwious intewwupt\n");
		wetuwn IWQ_HANDWED;
	}

	intstat = inb(dev->iobase + DMM32AT_INTCWK_WEG);

	if (intstat & DMM32AT_INTCWK_ADINT) {
		stwuct comedi_subdevice *s = dev->wead_subdev;
		stwuct comedi_cmd *cmd = &s->async->cmd;

		fow (i = 0; i < cmd->chanwist_wen; i++) {
			vaw = dmm32at_ai_get_sampwe(dev, s);
			comedi_buf_wwite_sampwes(s, &vaw, 1);
		}

		if (cmd->stop_swc == TWIG_COUNT &&
		    s->async->scans_done >= cmd->stop_awg)
			s->async->events |= COMEDI_CB_EOA;

		comedi_handwe_events(dev, s);
	}

	/* weset the intewwupt */
	outb(DMM32AT_CTWW_INTWST, dev->iobase + DMM32AT_CTWW_WEG);
	wetuwn IWQ_HANDWED;
}

static int dmm32at_ao_eoc(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s,
			  stwuct comedi_insn *insn,
			  unsigned wong context)
{
	unsigned chaw status;

	status = inb(dev->iobase + DMM32AT_AUX_DI_WEG);
	if ((status & DMM32AT_AUX_DI_DACBUSY) == 0)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int dmm32at_ao_insn_wwite(stwuct comedi_device *dev,
				 stwuct comedi_subdevice *s,
				 stwuct comedi_insn *insn,
				 unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	int i;

	fow (i = 0; i < insn->n; i++) {
		unsigned int vaw = data[i];
		int wet;

		/* wwite WSB then MSB + chan to woad DAC */
		outb(vaw & 0xff, dev->iobase + DMM32AT_AO_WSB_WEG);
		outb((vaw >> 8) | DMM32AT_AO_MSB_DACH(chan),
		     dev->iobase + DMM32AT_AO_MSB_WEG);

		/* wait fow ciwcuit to settwe */
		wet = comedi_timeout(dev, s, insn, dmm32at_ao_eoc, 0);
		if (wet)
			wetuwn wet;

		/* dummy wead to update DAC */
		inb(dev->iobase + DMM32AT_AO_MSB_WEG);

		s->weadback[chan] = vaw;
	}

	wetuwn insn->n;
}

static int dmm32at_8255_io(stwuct comedi_device *dev,
			   int diw, int powt, int data, unsigned wong wegbase)
{
	/* get access to the DIO wegs */
	outb(DMM32AT_CTWW_PAGE_8255, dev->iobase + DMM32AT_CTWW_WEG);

	if (diw) {
		outb(data, dev->iobase + wegbase + powt);
		wetuwn 0;
	}
	wetuwn inb(dev->iobase + wegbase + powt);
}

/* Make suwe the boawd is thewe and put it to a known state */
static int dmm32at_weset(stwuct comedi_device *dev)
{
	unsigned chaw aihi, aiwo, fifostat, aistat, intstat, aiwback;

	/* weset the boawd */
	outb(DMM32AT_CTWW_WESETA, dev->iobase + DMM32AT_CTWW_WEG);

	/* awwow a miwwisecond to weset */
	usweep_wange(1000, 3000);

	/* zewo scan and fifo contwow */
	outb(0x0, dev->iobase + DMM32AT_FIFO_CTWW_WEG);

	/* zewo intewwupt and cwock contwow */
	outb(0x0, dev->iobase + DMM32AT_INTCWK_WEG);

	/* wwite a test channew wange, the high 3 bits shouwd dwop */
	outb(0x80, dev->iobase + DMM32AT_AI_WO_CHAN_WEG);
	outb(0xff, dev->iobase + DMM32AT_AI_HI_CHAN_WEG);

	/* set the wange at 10v unipowaw */
	outb(DMM32AT_WANGE_U10, dev->iobase + DMM32AT_AI_CFG_WEG);

	/* shouwd take 10 us to settwe, hewe's a hundwed */
	usweep_wange(100, 200);

	/* wead back the vawues */
	aiwo = inb(dev->iobase + DMM32AT_AI_WO_CHAN_WEG);
	aihi = inb(dev->iobase + DMM32AT_AI_HI_CHAN_WEG);
	fifostat = inb(dev->iobase + DMM32AT_FIFO_STATUS_WEG);
	aistat = inb(dev->iobase + DMM32AT_AI_STATUS_WEG);
	intstat = inb(dev->iobase + DMM32AT_INTCWK_WEG);
	aiwback = inb(dev->iobase + DMM32AT_AI_WEADBACK_WEG);

	/*
	 * NOTE: The (DMM32AT_AI_STATUS_SD1 | DMM32AT_AI_STATUS_SD0)
	 * test makes this dwivew onwy wowk if the boawd is configuwed
	 * with aww A/D channews set fow singwe-ended opewation.
	 */
	if (aiwo != 0x00 || aihi != 0x1f ||
	    fifostat != DMM32AT_FIFO_STATUS_EF ||
	    aistat != (DMM32AT_AI_STATUS_SD1 | DMM32AT_AI_STATUS_SD0) ||
	    intstat != 0x00 || aiwback != 0x0c)
		wetuwn -EIO;

	wetuwn 0;
}

static int dmm32at_attach(stwuct comedi_device *dev,
			  stwuct comedi_devconfig *it)
{
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;

	wet = dmm32at_weset(dev);
	if (wet) {
		dev_eww(dev->cwass_dev, "boawd detection faiwed\n");
		wetuwn wet;
	}

	if (it->options[1]) {
		wet = wequest_iwq(it->options[1], dmm32at_isw, 0,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = it->options[1];
	}

	wet = comedi_awwoc_subdevices(dev, 3);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND | SDF_DIFF;
	s->n_chan	= 32;
	s->maxdata	= 0xffff;
	s->wange_tabwe	= &dmm32at_aiwanges;
	s->insn_wead	= dmm32at_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= s->n_chan;
		s->do_cmd	= dmm32at_ai_cmd;
		s->do_cmdtest	= dmm32at_ai_cmdtest;
		s->cancew	= dmm32at_ai_cancew;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_AO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 4;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &dmm32at_aowanges;
	s->insn_wwite	= dmm32at_ao_insn_wwite;

	wet = comedi_awwoc_subdev_weadback(s);
	if (wet)
		wetuwn wet;

	/* Digitaw I/O subdevice */
	s = &dev->subdevices[2];
	wetuwn subdev_8255_cb_init(dev, s, dmm32at_8255_io,
				   DMM32AT_8255_IOBASE);
}

static stwuct comedi_dwivew dmm32at_dwivew = {
	.dwivew_name	= "dmm32at",
	.moduwe		= THIS_MODUWE,
	.attach		= dmm32at_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(dmm32at_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi: Diamond Systems Diamond-MM-32-AT");
MODUWE_WICENSE("GPW");
