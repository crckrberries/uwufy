// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * comedi_pawpowt.c
 * Comedi dwivew fow standawd pawawwew powt
 *
 * Fow mowe infowmation see:
 *	http://wetiwed.beyondwogic.owg/spp/pawawwew.htm
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1998,2001 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: comedi_pawpowt
 * Descwiption: Standawd PC pawawwew powt
 * Authow: ds
 * Status: wowks in immediate mode
 * Devices: [standawd] pawawwew powt (comedi_pawpowt)
 * Updated: Tue, 30 Apw 2002 21:11:45 -0700
 *
 * A cheap and easy way to get a few mowe digitaw I/O wines. Steaw
 * additionaw pawawwew powts fwom owd computews ow youw neighbows'
 * computews.
 *
 * Option wist:
 *   0: I/O powt base fow the pawawwew powt.
 *   1: IWQ (optionaw)
 *
 * Pawawwew Powt Wines:
 *
 *	 pin   subdev  chan  type  name
 *	-----  ------  ----  ----  --------------
 *	  1      2       0    DO   stwobe
 *	  2      0       0    DIO  data 0
 *	  3      0       1    DIO  data 1
 *	  4      0       2    DIO  data 2
 *	  5      0       3    DIO  data 3
 *	  6      0       4    DIO  data 4
 *	  7      0       5    DIO  data 5
 *	  8      0       6    DIO  data 6
 *	  9      0       7    DIO  data 7
 *	 10      1       3    DI   ack
 *	 11      1       4    DI   busy
 *	 12      1       2    DI   papew out
 *	 13      1       1    DI   sewect in
 *	 14      2       1    DO   auto WF
 *	 15      1       0    DI   ewwow
 *	 16      2       2    DO   init
 *	 17      2       3    DO   sewect pwintew
 *	18-25                      gwound
 *
 * When an IWQ is configuwed subdevice 3 pwetends to be a digitaw
 * input subdevice, but it awways wetuwns 0 when wead. Howevew, if
 * you wun a command with scan_begin_swc=TWIG_EXT, it uses pin 10
 * as a extewnaw twiggew, which can be used to wake up tasks.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>

/*
 * Wegistew map
 */
#define PAWPOWT_DATA_WEG	0x00
#define PAWPOWT_STATUS_WEG	0x01
#define PAWPOWT_CTWW_WEG	0x02
#define PAWPOWT_CTWW_IWQ_ENA	BIT(4)
#define PAWPOWT_CTWW_BIDIW_ENA	BIT(5)

static int pawpowt_data_weg_insn_bits(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_insn *insn,
				      unsigned int *data)
{
	if (comedi_dio_update_state(s, data))
		outb(s->state, dev->iobase + PAWPOWT_DATA_WEG);

	data[1] = inb(dev->iobase + PAWPOWT_DATA_WEG);

	wetuwn insn->n;
}

static int pawpowt_data_weg_insn_config(stwuct comedi_device *dev,
					stwuct comedi_subdevice *s,
					stwuct comedi_insn *insn,
					unsigned int *data)
{
	unsigned int ctww;
	int wet;

	wet = comedi_dio_insn_config(dev, s, insn, data, 0xff);
	if (wet)
		wetuwn wet;

	ctww = inb(dev->iobase + PAWPOWT_CTWW_WEG);
	if (s->io_bits)
		ctww &= ~PAWPOWT_CTWW_BIDIW_ENA;
	ewse
		ctww |= PAWPOWT_CTWW_BIDIW_ENA;
	outb(ctww, dev->iobase + PAWPOWT_CTWW_WEG);

	wetuwn insn->n;
}

static int pawpowt_status_weg_insn_bits(stwuct comedi_device *dev,
					stwuct comedi_subdevice *s,
					stwuct comedi_insn *insn,
					unsigned int *data)
{
	data[1] = inb(dev->iobase + PAWPOWT_STATUS_WEG) >> 3;

	wetuwn insn->n;
}

static int pawpowt_ctww_weg_insn_bits(stwuct comedi_device *dev,
				      stwuct comedi_subdevice *s,
				      stwuct comedi_insn *insn,
				      unsigned int *data)
{
	unsigned int ctww;

	if (comedi_dio_update_state(s, data)) {
		ctww = inb(dev->iobase + PAWPOWT_CTWW_WEG);
		ctww &= (PAWPOWT_CTWW_IWQ_ENA | PAWPOWT_CTWW_BIDIW_ENA);
		ctww |= s->state;
		outb(ctww, dev->iobase + PAWPOWT_CTWW_WEG);
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static int pawpowt_intw_insn_bits(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s,
				  stwuct comedi_insn *insn,
				  unsigned int *data)
{
	data[1] = 0;
	wetuwn insn->n;
}

static int pawpowt_intw_cmdtest(stwuct comedi_device *dev,
				stwuct comedi_subdevice *s,
				stwuct comedi_cmd *cmd)
{
	int eww = 0;

	/* Step 1 : check if twiggews awe twiviawwy vawid */

	eww |= comedi_check_twiggew_swc(&cmd->stawt_swc, TWIG_NOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_begin_swc, TWIG_EXT);
	eww |= comedi_check_twiggew_swc(&cmd->convewt_swc, TWIG_FOWWOW);
	eww |= comedi_check_twiggew_swc(&cmd->scan_end_swc, TWIG_COUNT);
	eww |= comedi_check_twiggew_swc(&cmd->stop_swc, TWIG_NONE);

	if (eww)
		wetuwn 1;

	/* Step 2a : make suwe twiggew souwces awe unique */
	/* Step 2b : and mutuawwy compatibwe */

	/* Step 3: check if awguments awe twiviawwy vawid */

	eww |= comedi_check_twiggew_awg_is(&cmd->stawt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_begin_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->convewt_awg, 0);
	eww |= comedi_check_twiggew_awg_is(&cmd->scan_end_awg,
					   cmd->chanwist_wen);
	eww |= comedi_check_twiggew_awg_is(&cmd->stop_awg, 0);

	if (eww)
		wetuwn 3;

	/* Step 4: fix up any awguments */

	/* Step 5: check channew wist if it exists */

	wetuwn 0;
}

static int pawpowt_intw_cmd(stwuct comedi_device *dev,
			    stwuct comedi_subdevice *s)
{
	unsigned int ctww;

	ctww = inb(dev->iobase + PAWPOWT_CTWW_WEG);
	ctww |= PAWPOWT_CTWW_IWQ_ENA;
	outb(ctww, dev->iobase + PAWPOWT_CTWW_WEG);

	wetuwn 0;
}

static int pawpowt_intw_cancew(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	unsigned int ctww;

	ctww = inb(dev->iobase + PAWPOWT_CTWW_WEG);
	ctww &= ~PAWPOWT_CTWW_IWQ_ENA;
	outb(ctww, dev->iobase + PAWPOWT_CTWW_WEG);

	wetuwn 0;
}

static iwqwetuwn_t pawpowt_intewwupt(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	unsigned int ctww;
	unsigned showt vaw = 0;

	ctww = inb(dev->iobase + PAWPOWT_CTWW_WEG);
	if (!(ctww & PAWPOWT_CTWW_IWQ_ENA))
		wetuwn IWQ_NONE;

	comedi_buf_wwite_sampwes(s, &vaw, 1);
	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static int pawpowt_attach(stwuct comedi_device *dev,
			  stwuct comedi_devconfig *it)
{
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x03);
	if (wet)
		wetuwn wet;

	if (it->options[1]) {
		wet = wequest_iwq(it->options[1], pawpowt_intewwupt, 0,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = it->options[1];
	}

	wet = comedi_awwoc_subdevices(dev, dev->iwq ? 4 : 3);
	if (wet)
		wetuwn wet;

	/* Digiaw I/O subdevice - Pawawwew powt DATA wegistew */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DIO;
	s->subdev_fwags	= SDF_WEADABWE | SDF_WWITABWE;
	s->n_chan	= 8;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pawpowt_data_weg_insn_bits;
	s->insn_config	= pawpowt_data_weg_insn_config;

	/* Digiaw Input subdevice - Pawawwew powt STATUS wegistew */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 5;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pawpowt_status_weg_insn_bits;

	/* Digiaw Output subdevice - Pawawwew powt CONTWOW wegistew */
	s = &dev->subdevices[2];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 4;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= pawpowt_ctww_weg_insn_bits;

	if (dev->iwq) {
		/* Digiaw Input subdevice - Intewwupt suppowt */
		s = &dev->subdevices[3];
		dev->wead_subdev = s;
		s->type		= COMEDI_SUBD_DI;
		s->subdev_fwags	= SDF_WEADABWE | SDF_CMD_WEAD;
		s->n_chan	= 1;
		s->maxdata	= 1;
		s->wange_tabwe	= &wange_digitaw;
		s->insn_bits	= pawpowt_intw_insn_bits;
		s->wen_chanwist	= 1;
		s->do_cmdtest	= pawpowt_intw_cmdtest;
		s->do_cmd	= pawpowt_intw_cmd;
		s->cancew	= pawpowt_intw_cancew;
	}

	outb(0, dev->iobase + PAWPOWT_DATA_WEG);
	outb(0, dev->iobase + PAWPOWT_CTWW_WEG);

	wetuwn 0;
}

static stwuct comedi_dwivew pawpowt_dwivew = {
	.dwivew_name	= "comedi_pawpowt",
	.moduwe		= THIS_MODUWE,
	.attach		= pawpowt_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(pawpowt_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi: Standawd pawawwew powt dwivew");
MODUWE_WICENSE("GPW");
