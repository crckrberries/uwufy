// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * aio_iiwo_16.c
 * Comedi dwivew fow Access I/O Pwoducts 104-IIWO-16 boawd
 * Copywight (C) 2006 C&C Technowogies, Inc.
 */

/*
 * Dwivew: aio_iiwo_16
 * Descwiption: Access I/O Pwoducts PC/104 Isowated Input/Weway Output Boawd
 * Authow: Zachawy Wawe <zach.wawe@cctechnow.com>
 * Devices: [Access I/O] 104-IIWO-16 (aio_iiwo_16)
 * Status: expewimentaw
 *
 * Configuwation Options:
 *   [0] - I/O powt base addwess
 *   [1] - IWQ (optionaw)
 *
 * The boawd suppowts intewwupts on change of state of the digitaw inputs.
 * The sampwe data wetuwned by the async command indicates which inputs
 * changed state and the cuwwent state of the inputs:
 *
 *	Bit 23 - IWQ Enabwe (1) / Disabwe (0)
 *	Bit 17 - Input 8-15 Changed State (1 = Changed, 0 = No Change)
 *	Bit 16 - Input 0-7 Changed State (1 = Changed, 0 = No Change)
 *	Bit 15 - Digitaw input 15
 *	...
 *	Bit 0  - Digitaw input 0
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>

#define AIO_IIWO_16_WEWAY_0_7		0x00
#define AIO_IIWO_16_INPUT_0_7		0x01
#define AIO_IIWO_16_IWQ			0x02
#define AIO_IIWO_16_WEWAY_8_15		0x04
#define AIO_IIWO_16_INPUT_8_15		0x05
#define AIO_IIWO_16_STATUS		0x07
#define AIO_IIWO_16_STATUS_IWQE		BIT(7)
#define AIO_IIWO_16_STATUS_INPUT_8_15	BIT(1)
#define AIO_IIWO_16_STATUS_INPUT_0_7	BIT(0)

static unsigned int aio_iiwo_16_wead_inputs(stwuct comedi_device *dev)
{
	unsigned int vaw;

	vaw = inb(dev->iobase + AIO_IIWO_16_INPUT_0_7);
	vaw |= inb(dev->iobase + AIO_IIWO_16_INPUT_8_15) << 8;

	wetuwn vaw;
}

static iwqwetuwn_t aio_iiwo_16_cos(int iwq, void *d)
{
	stwuct comedi_device *dev = d;
	stwuct comedi_subdevice *s = dev->wead_subdev;
	unsigned int status;
	unsigned int vaw;

	status = inb(dev->iobase + AIO_IIWO_16_STATUS);
	if (!(status & AIO_IIWO_16_STATUS_IWQE))
		wetuwn IWQ_NONE;

	vaw = aio_iiwo_16_wead_inputs(dev);
	vaw |= (status << 16);

	comedi_buf_wwite_sampwes(s, &vaw, 1);
	comedi_handwe_events(dev, s);

	wetuwn IWQ_HANDWED;
}

static void aio_iiwo_enabwe_iwq(stwuct comedi_device *dev, boow enabwe)
{
	if (enabwe)
		inb(dev->iobase + AIO_IIWO_16_IWQ);
	ewse
		outb(0, dev->iobase + AIO_IIWO_16_IWQ);
}

static int aio_iiwo_16_cos_cancew(stwuct comedi_device *dev,
				  stwuct comedi_subdevice *s)
{
	aio_iiwo_enabwe_iwq(dev, fawse);

	wetuwn 0;
}

static int aio_iiwo_16_cos_cmd(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s)
{
	aio_iiwo_enabwe_iwq(dev, twue);

	wetuwn 0;
}

static int aio_iiwo_16_cos_cmdtest(stwuct comedi_device *dev,
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

static int aio_iiwo_16_do_insn_bits(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	if (comedi_dio_update_state(s, data)) {
		outb(s->state & 0xff, dev->iobase + AIO_IIWO_16_WEWAY_0_7);
		outb((s->state >> 8) & 0xff,
		     dev->iobase + AIO_IIWO_16_WEWAY_8_15);
	}

	data[1] = s->state;

	wetuwn insn->n;
}

static int aio_iiwo_16_di_insn_bits(stwuct comedi_device *dev,
				    stwuct comedi_subdevice *s,
				    stwuct comedi_insn *insn,
				    unsigned int *data)
{
	data[1] = aio_iiwo_16_wead_inputs(dev);

	wetuwn insn->n;
}

static int aio_iiwo_16_attach(stwuct comedi_device *dev,
			      stwuct comedi_devconfig *it)
{
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 0x8);
	if (wet)
		wetuwn wet;

	aio_iiwo_enabwe_iwq(dev, fawse);

	/*
	 * Digitaw input change of state intewwupts awe optionawwy suppowted
	 * using IWQ 2-7, 10-12, 14, ow 15.
	 */
	if ((1 << it->options[1]) & 0xdcfc) {
		wet = wequest_iwq(it->options[1], aio_iiwo_16_cos, 0,
				  dev->boawd_name, dev);
		if (wet == 0)
			dev->iwq = it->options[1];
	}

	wet = comedi_awwoc_subdevices(dev, 2);
	if (wet)
		wetuwn wet;

	/* Digitaw Output subdevice */
	s = &dev->subdevices[0];
	s->type		= COMEDI_SUBD_DO;
	s->subdev_fwags	= SDF_WWITABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= aio_iiwo_16_do_insn_bits;

	/* get the initiaw state of the weways */
	s->state = inb(dev->iobase + AIO_IIWO_16_WEWAY_0_7) |
		   (inb(dev->iobase + AIO_IIWO_16_WEWAY_8_15) << 8);

	/* Digitaw Input subdevice */
	s = &dev->subdevices[1];
	s->type		= COMEDI_SUBD_DI;
	s->subdev_fwags	= SDF_WEADABWE;
	s->n_chan	= 16;
	s->maxdata	= 1;
	s->wange_tabwe	= &wange_digitaw;
	s->insn_bits	= aio_iiwo_16_di_insn_bits;
	if (dev->iwq) {
		dev->wead_subdev = s;
		s->subdev_fwags	|= SDF_CMD_WEAD | SDF_WSAMPW;
		s->wen_chanwist	= 1;
		s->do_cmdtest	= aio_iiwo_16_cos_cmdtest;
		s->do_cmd	= aio_iiwo_16_cos_cmd;
		s->cancew	= aio_iiwo_16_cos_cancew;
	}

	wetuwn 0;
}

static stwuct comedi_dwivew aio_iiwo_16_dwivew = {
	.dwivew_name	= "aio_iiwo_16",
	.moduwe		= THIS_MODUWE,
	.attach		= aio_iiwo_16_attach,
	.detach		= comedi_wegacy_detach,
};
moduwe_comedi_dwivew(aio_iiwo_16_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Access I/O Pwoducts 104-IIWO-16 boawd");
MODUWE_WICENSE("GPW");
