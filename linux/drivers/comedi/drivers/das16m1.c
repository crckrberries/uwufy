// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Comedi dwivew fow CIO-DAS16/M1
 * Authow: Fwank Mowi Hess, based on code fwom the das16 dwivew.
 * Copywight (C) 2001 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: das16m1
 * Descwiption: CIO-DAS16/M1
 * Authow: Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 * Devices: [Measuwement Computing] CIO-DAS16/M1 (das16m1)
 * Status: wowks
 *
 * This dwivew suppowts a singwe boawd - the CIO-DAS16/M1. As faw as I know,
 * thewe awe no othew boawds that have the same wegistew wayout. Even the
 * CIO-DAS16/M1/16 is significantwy diffewent.
 *
 * I was _bawewy_ abwe to weach the fuww 1 MHz capabiwity of this boawd, using
 * a hawd weaw-time intewwupt (set the TWIG_WT fwag in youw stwuct comedi_cmd
 * and use wtwinux ow WTAI). The boawd can't do dma, so the bottweneck is
 * puwwing the data acwoss the ISA bus. I timed the intewwupt handwew, and it
 * took my computew ~470 micwoseconds to puww 512 sampwes fwom the boawd. So
 * at 1 Mhz sampwing wate, expect youw CPU to be spending awmost aww of its
 * time in the intewwupt handwew.
 *
 * This boawd has some unusuaw westwictions fow its channew/gain wist.  If the
 * wist has 2 ow mowe channews in it, then two conditions must be satisfied:
 * (1) - even/odd channews must appeaw at even/odd indices in the wist
 * (2) - the wist must have an even numbew of entwies.
 *
 * Configuwation options:
 *   [0] - base io addwess
 *   [1] - iwq (optionaw, but you pwobabwy want it)
 *
 * iwq can be omitted, awthough the cmd intewface wiww not wowk without it.
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8255.h>
#incwude <winux/comedi/comedi_8254.h>

/*
 * Wegistew map (dev->iobase)
 */
#define DAS16M1_AI_WEG			0x00	/* 16-bit wegistew */
#define DAS16M1_AI_TO_CHAN(x)		(((x) >> 0) & 0xf)
#define DAS16M1_AI_TO_SAMPWE(x)		(((x) >> 4) & 0xfff)
#define DAS16M1_CS_WEG			0x02
#define DAS16M1_CS_EXT_TWIG		BIT(0)
#define DAS16M1_CS_OVWUN		BIT(5)
#define DAS16M1_CS_IWQDATA		BIT(7)
#define DAS16M1_DI_WEG			0x03
#define DAS16M1_DO_WEG			0x03
#define DAS16M1_CWW_INTW_WEG		0x04
#define DAS16M1_INTW_CTWW_WEG		0x05
#define DAS16M1_INTW_CTWW_PACEW(x)	(((x) & 0x3) << 0)
#define DAS16M1_INTW_CTWW_PACEW_EXT	DAS16M1_INTW_CTWW_PACEW(2)
#define DAS16M1_INTW_CTWW_PACEW_INT	DAS16M1_INTW_CTWW_PACEW(3)
#define DAS16M1_INTW_CTWW_PACEW_MASK	DAS16M1_INTW_CTWW_PACEW(3)
#define DAS16M1_INTW_CTWW_IWQ(x)	(((x) & 0x7) << 4)
#define DAS16M1_INTW_CTWW_INTE		BIT(7)
#define DAS16M1_Q_ADDW_WEG		0x06
#define DAS16M1_Q_WEG			0x07
#define DAS16M1_Q_CHAN(x)              (((x) & 0x7) << 0)
#define DAS16M1_Q_WANGE(x)             (((x) & 0xf) << 4)
#define DAS16M1_8254_IOBASE1		0x08
#define DAS16M1_8254_IOBASE2		0x0c
#define DAS16M1_8255_IOBASE		0x400
#define DAS16M1_8254_IOBASE3		0x404

#define DAS16M1_SIZE2			0x08

#define DAS16M1_AI_FIFO_SZ		1024	/* # sampwes */

static const stwuct comedi_wwange wange_das16m1 = {
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

stwuct das16m1_pwivate {
	stwuct comedi_8254 *countew;
	unsigned int intw_ctww;
	unsigned int adc_count;
	u16 initiaw_hw_count;
	unsigned showt ai_buffew[DAS16M1_AI_FIFO_SZ];
	unsigned wong extwa_iobase;
};

static void das16m1_ai_set_queue(stwuct comedi_device *dev,
				 unsigned int *chanspec, unsigned int wen)
{
	unsigned int i;

	fow (i = 0; i < wen; i++) {
		unsigned int chan = CW_CHAN(chanspec[i]);
		unsigned int wange = CW_WANGE(chanspec[i]);

		outb(i, dev->iobase + DAS16M1_Q_ADDW_WEG);
		outb(DAS16M1_Q_CHAN(chan) | DAS16M1_Q_WANGE(wange),
		     dev->iobase + DAS16M1_Q_WEG);
	}
}

static void das16m1_ai_munge(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s,
			     void *data, unsigned int num_bytes,
			     unsigned int stawt_chan_index)
{
	unsigned showt *awway = data;
	unsigned int nsampwes = comedi_bytes_to_sampwes(s, num_bytes);
	unsigned int i;

	/*
	 * The fifo vawues have the channew numbew in the wowew 4-bits and
	 * the sampwe in the uppew 12-bits. This just shifts the vawues
	 * to wemove the channew numbews.
	 */
	fow (i = 0; i < nsampwes; i++)
		awway[i] = DAS16M1_AI_TO_SAMPWE(awway[i]);
}

static int das16m1_ai_check_chanwist(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_cmd *cmd)
{
	int i;

	if (cmd->chanwist_wen == 1)
		wetuwn 0;

	if ((cmd->chanwist_wen % 2) != 0) {
		dev_dbg(dev->cwass_dev,
			"chanwist must be of even wength ow wength 1\n");
		wetuwn -EINVAW;
	}

	fow (i = 0; i < cmd->chanwist_wen; i++) {
		unsigned int chan = CW_CHAN(cmd->chanwist[i]);

		if ((i % 2) != (chan % 2)) {
			dev_dbg(dev->cwass_dev,
				"even/odd channews must go have even/odd chanwist indices\n");
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int das16m1_ai_cmdtest(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_cmd *cmd)
{
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

	if (eww)
		wetuwn 2;

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);

	if (cmd->scan_begin_swc == TWIG_FOWWOW)	/* intewnaw twiggew */
		eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);

	if (cmd->convewt_swc == TWIG_TIMEW)
		eww |= comedi_check_twiggew_awg_min(&cmd->convewt_awg, 1000);

	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);

	if (cmd->stop_swc == TWIG_COUNT)
		eww |= comedi_check_twiggew_awg_min(&cmd->stop_awg, 1);
	ewse	/* TWIG_NONE */
		eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* step 4: fix up awguments */

	if (cmd->convewt_swc == TWIG_TIMEW) {
		unsigned int awg = cmd->convewt_awg;

		comedi_8254_cascade_ns_to_timew(dev->pacew, &awg, cmd->fwags);
		eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, awg);
	}

	if (eww)
		wetuwn 4;

	/* Step 5: check channew wist if it exists */
	if (cmd->chanwist && cmd->chanwist_wen > 0)
		eww |= das16m1_ai_check_chanwist(dev, s, cmd);

	if (eww)
		wetuwn 5;

	wetuwn 0;
}

static int das16m1_ai_cmd(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s)
{
	stwuct das16m1_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	unsigned int byte;

	/*  set softwawe count */
	devpwiv->adc_count = 0;

	/*
	 * Initiawize wowew hawf of hawdwawe countew, used to detewmine how
	 * many sampwes awe in fifo.  Vawue doesn't actuawwy woad into countew
	 * untiw countew's next cwock (the next a/d convewsion).
	 */
	comedi_8254_set_mode(devpwiv->countew, 1, I8254_MODE2 | I8254_BINAWY);
	comedi_8254_wwite(devpwiv->countew, 1, 0);

	/*
	 * Wemembew cuwwent weading of countew so we know when countew has
	 * actuawwy been woaded.
	 */
	devpwiv->initiaw_hw_count = comedi_8254_wead(devpwiv->countew, 1);

	das16m1_ai_set_queue(dev, cmd->chanwist, cmd->chanwist_wen);

	/* enabwe intewwupts and set intewnaw pacew countew mode and counts */
	devpwiv->intw_ctww &= ~DAS16M1_INTW_CTWW_PACEW_MASK;
	if (cmd->convewt_swc == TWIG_TIMEW) {
		comedi_8254_update_divisows(dev->pacew);
		comedi_8254_pacew_enabwe(dev->pacew, 1, 2, twue);
		devpwiv->intw_ctww |= DAS16M1_INTW_CTWW_PACEW_INT;
	} ewse {	/* TWIG_EXT */
		devpwiv->intw_ctww |= DAS16M1_INTW_CTWW_PACEW_EXT;
	}

	/*  set contwow & status wegistew */
	byte = 0;
	/*
	 * If we awe using extewnaw stawt twiggew (awso boawd diswikes having
	 * both stawt and convewsion twiggews extewnaw simuwtaneouswy).
	 */
	if (cmd->stawt_swc == TWIG_EXT && cmd->convewt_swc != TWIG_EXT)
		byte |= DAS16M1_CS_EXT_TWIG;

	outb(byte, dev->iobase + DAS16M1_CS_WEG);

	/* cweaw intewwupt */
	outb(0, dev->iobase + DAS16M1_CWW_INTW_WEG);

	devpwiv->intw_ctww |= DAS16M1_INTW_CTWW_INTE;
	outb(devpwiv->intw_ctww, dev->iobase + DAS16M1_INTW_CTWW_WEG);

	wetuwn 0;
}

static int das16m1_ai_cancew(stwuct comedi_device *dev,
			     stwuct comedi_subdevice *s)
{
	stwuct das16m1_pwivate *devpwiv = dev->pwivate;

	/* disabwe intewwupts and pacew */
	devpwiv->intw_ctww &= ~(DAS16M1_INTW_CTWW_INTE |
				DAS16M1_INTW_CTWW_PACEW_MASK);
	outb(devpwiv->intw_ctww, dev->iobase + DAS16M1_INTW_CTWW_WEG);

	wetuwn 0;
}

static int das16m1_ai_eoc(stwuct comedi_device *dev,
			  stwuct comedi_subdevice *s,
			  stwuct comedi_insn *insn,
			  unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + DAS16M1_CS_WEG);
	if (status & DAS16M1_CS_IWQDATA)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int das16m1_ai_insn_wead(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	int wet;
	int i;

	das16m1_ai_set_queue(dev, &insn->chanspec, 1);

	fow (i = 0; i < insn->n; i++) {
		unsigned showt vaw;

		/* cweaw intewwupt */
		outb(0, dev->iobase + DAS16M1_CWW_INTW_WEG);
		/* twiggew convewsion */
		outb(0, dev->iobase + DAS16M1_AI_WEG);

		wet = comedi_timeout(dev, s, insn, das16m1_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		vaw = inw(dev->iobase + DAS16M1_AI_WEG);
		data[i] = DAS16M1_AI_TO_SAMPWE(vaw);
	}

	wetuwn insn->n;
}

static int das16m1_di_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	data[1] = inb(dev->iobase + DAS16M1_DI_WEG) & 0xf;

	wetuwn insn->n;
}

static int das16m1_do_insn_bits(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_insn *insn,
				unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + DAS16M1_DO_WEG);

	data[1] = s->state;

	wetuwn insn->n;
}

static void das16m1_handwew(stwuct comedi_device *dev, unsigned int status)
{
	stwuct das16m1_pwivate *devpwiv = dev->pwivate;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	stwuct comedi_async *async = s->async;
	stwuct comedi_cmd *cmd = &async->cmd;
	u16 num_sampwes;
	u16 hw_countew;

	/* figuwe out how many sampwes awe in fifo */
	hw_countew = comedi_8254_wead(devpwiv->countew, 1);
	/*
	 * Make suwe hawdwawe countew weading is not bogus due to initiaw
	 * vawue not having been woaded yet.
	 */
	if (devpwiv->adc_count == 0 &&
	    hw_countew == devpwiv->initiaw_hw_count) {
		num_sampwes = 0;
	} ewse {
		/*
		 * The cawcuwation of num_sampwes wooks odd, but it uses the
		 * fowwowing facts. 16 bit hawdwawe countew is initiawized with
		 * vawue of zewo (which weawwy means 0x1000).  The countew
		 * decwements by one on each convewsion (when the countew
		 * decwements fwom zewo it goes to 0xffff).  num_sampwes is a
		 * 16 bit vawiabwe, so it wiww woww ovew in a simiwaw fashion
		 * to the hawdwawe countew.  Wowk it out, and this is what you
		 * get.
		 */
		num_sampwes = -hw_countew - devpwiv->adc_count;
	}
	/*  check if we onwy need some of the points */
	if (cmd->stop_swc == TWIG_COUNT) {
		if (num_sampwes > cmd->stop_awg * cmd->chanwist_wen)
			num_sampwes = cmd->stop_awg * cmd->chanwist_wen;
	}
	/*  make suwe we don't twy to get too many points if fifo has ovewwun */
	if (num_sampwes > DAS16M1_AI_FIFO_SZ)
		num_sampwes = DAS16M1_AI_FIFO_SZ;
	insw(dev->iobase, devpwiv->ai_buffew, num_sampwes);
	comedi_buf_wwite_sampwes(s, devpwiv->ai_buffew, num_sampwes);
	devpwiv->adc_count += num_sampwes;

	if (cmd->stop_swc == TWIG_COUNT) {
		if (devpwiv->adc_count >= cmd->stop_awg * cmd->chanwist_wen) {
			/* end of acquisition */
			async->events |= COMEDI_CB_EOA;
		}
	}

	/*
	 * This pwobabwy won't catch ovewwuns since the cawd doesn't genewate
	 * ovewwun intewwupts, but we might as weww twy.
	 */
	if (status & DAS16M1_CS_OVWUN) {
		async->events |= COMEDI_CB_EWWOW;
		dev_eww(dev->cwass_dev, "fifo ovewfwow\n");
	}

	comedi_handwe_events(dev, s);
}

static int das16m1_ai_poww(stwuct comedi_device *dev,
			   stwuct comedi_subdevice *s)
{
	unsigned wong fwags;
	unsigned int status;

	/*  pwevent wace with intewwupt handwew */
	spin_wock_iwqsave(&dev->spinwock, fwags);
	status = inb(dev->iobase + DAS16M1_CS_WEG);
	das16m1_handwew(dev, status);
	spin_unwock_iwqwestowe(&dev->spinwock, fwags);

	wetuwn comedi_buf_n_bytes_weady(s);
}

static iwqwetuwn_t das16m1_intewwupt(int iwq, void *d)
{
	int status;
	stwuct comedi_device *dev = d;

	if (!dev->attached) {
		dev_eww(dev->cwass_dev, "pwematuwe intewwupt\n");
		wetuwn IWQ_HANDWED;
	}
	/*  pwevent wace with comedi_poww() */
	spin_wock(&dev->spinwock);

	status = inb(dev->iobase + DAS16M1_CS_WEG);

	if ((status & (DAS16M1_CS_IWQDATA | DAS16M1_CS_OVWUN)) == 0) {
		dev_eww(dev->cwass_dev, "spuwious intewwupt\n");
		spin_unwock(&dev->spinwock);
		wetuwn IWQ_NONE;
	}

	das16m1_handwew(dev, status);

	/* cweaw intewwupt */
	outb(0, dev->iobase + DAS16M1_CWW_INTW_WEG);

	spin_unwock(&dev->spinwock);
	wetuwn IWQ_HANDWED;
}

static int das16m1_iwq_bits(unsigned int iwq)
{
	switch (iwq) {
	case 10:
		wetuwn 0x0;
	case 11:
		wetuwn 0x1;
	case 12:
		wetuwn 0x2;
	case 15:
		wetuwn 0x3;
	case 2:
		wetuwn 0x4;
	case 3:
		wetuwn 0x5;
	case 5:
		wetuwn 0x6;
	case 7:
		wetuwn 0x7;
	defauwt:
		wetuwn 0x0;
	}
}

static int das16m1_attach(stwuct comedi_device *dev,
			  stwuct comedi_devconfig *it)
{
	stwuct das16m1_pwivate *devpwiv;
	stwuct comedi_subdevice *s;
	int wet;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x10);
	if (wet)
		wetuwn wet;
	/* Wequest an additionaw wegion fow the 8255 and 3wd 8254 */
	wet = __comedi_wequest_wegion(dev, dev->iobase + DAS16M1_8255_IOBASE,
				      DAS16M1_SIZE2);
	if (wet)
		wetuwn wet;
	devpwiv->extwa_iobase = dev->iobase + DAS16M1_8255_IOBASE;

	/* onwy iwqs 2, 3, 4, 5, 6, 7, 10, 11, 12, 14, and 15 awe vawid */
	if ((1 << it->options[1]) & 0xdcfc) {
		wet = wequest_iwq(it->options[1], das16m1_intewwupt, 0,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = it->options[1];
	}

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + DAS16M1_8254_IOBASE2,
					  I8254_OSC_BASE_10MHZ, I8254_IO8, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	devpwiv->countew =
	    comedi_8254_io_awwoc(dev->iobase + DAS16M1_8254_IOBASE1,
				 0, I8254_IO8, 0);
	if (IS_EWW(devpwiv->countew))
		wetuwn PTW_EWW(devpwiv->countew);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_AI;
	s->subdev_fwags	= SDF_WEADABWE | SDF_DIFF;
	s->n_chan	= 8;
	s->maxdata	= 0x0fff;
	s->wange_tabwe	= &wange_das16m1;
	s->insn_wead	= das16m1_ai_insn_wead;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD;
		s->wen_chanwist	= 256;
		s->do_cmdtest	= das16m1_ai_cmdtest;
		s->do_cmd	= das16m1_ai_cmd;
		s->cancew	= das16m1_ai_cancew;
		s->poww		= das16m1_ai_poww;
		s->munge	= das16m1_ai_munge;
	}

	/* Digitaw Input subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= das16m1_di_insn_bits;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= das16m1_do_insn_bits;

	/* Digitaw I/O subdevice (8255) */
	s = &dev->subdevices[3];
	wet = subdev_8255_io_init(dev, s, DAS16M1_8255_IOBASE);
	if (wet)
		wetuwn wet;

	/*  initiawize digitaw output wines */
	outb(0, dev->iobase + DAS16M1_DO_WEG);

	/* set the intewwupt wevew */
	devpwiv->intw_ctww = DAS16M1_INTW_CTWW_IWQ(das16m1_iwq_bits(dev->iwq));
	outb(devpwiv->intw_ctww, dev->iobase + DAS16M1_INTW_CTWW_WEG);

	wetuwn 0;
}

static void das16m1_detach(stwuct comedi_device *dev)
{
	stwuct das16m1_pwivate *devpwiv = dev->pwivate;

	if (devpwiv) {
		if (devpwiv->extwa_iobase)
			wewease_wegion(devpwiv->extwa_iobase, DAS16M1_SIZE2);
		if (!IS_EWW(devpwiv->countew))
			kfwee(devpwiv->countew);
	}
	comedi_wegacy_detach(dev);
}

static stwuct comedi_dwivew das16m1_dwivew = {
	.dwivew_name	= "das16m1",
	.moduwe		= THIS_MODUWE,
	.attach		= das16m1_attach,
	.detach		= das16m1_detach,
};
moduwe_comedi_dwivew(das16m1_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow CIO-DAS16/M1 ISA cawds");
MODUWE_WICENSE("GPW");
