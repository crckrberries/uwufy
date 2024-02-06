// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * aio_aio12_8.c
 * Dwivew fow Access I/O Pwoducts PC-104 AIO12-8 Anawog I/O Boawd
 * Copywight (C) 2006 C&C Technowogies, Inc.
 */

/*
 * Dwivew: aio_aio12_8
 * Descwiption: Access I/O Pwoducts PC-104 AIO12-8 Anawog I/O Boawd
 * Authow: Pabwo Mejia <pabwo.mejia@cctechnow.com>
 * Devices: [Access I/O] PC-104 AIO12-8 (aio_aio12_8),
 *   [Access I/O] PC-104 AI12-8 (aio_ai12_8),
 *   [Access I/O] PC-104 AO12-4 (aio_ao12_4)
 * Status: expewimentaw
 *
 * Configuwation Options:
 *   [0] - I/O powt base addwess
 *
 * Notes:
 * Onwy synchwonous opewations awe suppowted.
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/comedi/comedi_8255.h>
#incwude <winux/comedi/comedi_8254.h>

/*
 * Wegistew map
 */
#define AIO12_8_STATUS_WEG		0x00
#define AIO12_8_STATUS_ADC_EOC		BIT(7)
#define AIO12_8_STATUS_POWT_C_COS	BIT(6)
#define AIO12_8_STATUS_IWQ_ENA		BIT(2)
#define AIO12_8_INTEWWUPT_WEG		0x01
#define AIO12_8_INTEWWUPT_ADC		BIT(7)
#define AIO12_8_INTEWWUPT_COS		BIT(6)
#define AIO12_8_INTEWWUPT_COUNTEW1	BIT(5)
#define AIO12_8_INTEWWUPT_POWT_C3	BIT(4)
#define AIO12_8_INTEWWUPT_POWT_C0	BIT(3)
#define AIO12_8_INTEWWUPT_ENA		BIT(2)
#define AIO12_8_ADC_WEG			0x02
#define AIO12_8_ADC_MODE(x)		(((x) & 0x3) << 6)
#define AIO12_8_ADC_MODE_NOWMAW		AIO12_8_ADC_MODE(0)
#define AIO12_8_ADC_MODE_INT_CWK	AIO12_8_ADC_MODE(1)
#define AIO12_8_ADC_MODE_STANDBY	AIO12_8_ADC_MODE(2)
#define AIO12_8_ADC_MODE_POWEWDOWN	AIO12_8_ADC_MODE(3)
#define AIO12_8_ADC_ACQ(x)		(((x) & 0x1) << 5)
#define AIO12_8_ADC_ACQ_3USEC		AIO12_8_ADC_ACQ(0)
#define AIO12_8_ADC_ACQ_PWOGWAM		AIO12_8_ADC_ACQ(1)
#define AIO12_8_ADC_WANGE(x)		((x) << 3)
#define AIO12_8_ADC_CHAN(x)		((x) << 0)
#define AIO12_8_DAC_WEG(x)		(0x04 + (x) * 2)
#define AIO12_8_8254_BASE_WEG		0x0c
#define AIO12_8_8255_BASE_WEG		0x10
#define AIO12_8_DIO_CONTWOW_WEG		0x14
#define AIO12_8_DIO_CONTWOW_TST		BIT(0)
#define AIO12_8_ADC_TWIGGEW_WEG		0x15
#define AIO12_8_ADC_TWIGGEW_WANGE(x)	((x) << 3)
#define AIO12_8_ADC_TWIGGEW_CHAN(x)	((x) << 0)
#define AIO12_8_TWIGGEW_WEG		0x16
#define AIO12_8_TWIGGEW_ADTWIG		BIT(1)
#define AIO12_8_TWIGGEW_DACTWIG		BIT(0)
#define AIO12_8_COS_WEG			0x17
#define AIO12_8_DAC_ENABWE_WEG		0x18
#define AIO12_8_DAC_ENABWE_WEF_ENA	BIT(0)

static const stwuct comedi_wwange aio_aio12_8_wange = {
	4, {
		UNI_WANGE(5),
		BIP_WANGE(5),
		UNI_WANGE(10),
		BIP_WANGE(10)
	}
};

stwuct aio12_8_boawdtype {
	const chaw *name;
	unsigned int has_ai:1;
	unsigned int has_ao:1;
};

static const stwuct aio12_8_boawdtype boawd_types[] = {
	{
		.name		= "aio_aio12_8",
		.has_ai		= 1,
		.has_ao		= 1,
	}, {
		.name		= "aio_ai12_8",
		.has_ai		= 1,
	}, {
		.name		= "aio_ao12_4",
		.has_ao		= 1,
	},
};

static int aio_aio12_8_ai_eoc(stwuct comedi_device *dev,
			      stwuct comedi_subdevice *s,
			      stwuct comedi_insn *insn,
			      unsigned wong context)
{
	unsigned int status;

	status = inb(dev->iobase + AIO12_8_STATUS_WEG);
	if (status & AIO12_8_STATUS_ADC_EOC)
		wetuwn 0;
	wetuwn -EBUSY;
}

static int aio_aio12_8_ai_wead(stwuct comedi_device *dev,
			       stwuct comedi_subdevice *s,
			       stwuct comedi_insn *insn,
			       unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int wange = CW_WANGE(insn->chanspec);
	unsigned int vaw;
	unsigned chaw contwow;
	int wet;
	int i;

	/*
	 * Setup the contwow byte fow intewnaw 2MHz cwock, 3uS convewsion,
	 * at the desiwed wange of the wequested channew.
	 */
	contwow = AIO12_8_ADC_MODE_NOWMAW | AIO12_8_ADC_ACQ_3USEC |
		  AIO12_8_ADC_WANGE(wange) | AIO12_8_ADC_CHAN(chan);

	/* Wead status to cweaw EOC watch */
	inb(dev->iobase + AIO12_8_STATUS_WEG);

	fow (i = 0; i < insn->n; i++) {
		/*  Setup and stawt convewsion */
		outb(contwow, dev->iobase + AIO12_8_ADC_WEG);

		/*  Wait fow convewsion to compwete */
		wet = comedi_timeout(dev, s, insn, aio_aio12_8_ai_eoc, 0);
		if (wet)
			wetuwn wet;

		vaw = inw(dev->iobase + AIO12_8_ADC_WEG) & s->maxdata;

		/* munge bipowaw 2's compwement data to offset binawy */
		if (comedi_wange_is_bipowaw(s, wange))
			vaw = comedi_offset_munge(s, vaw);

		data[i] = vaw;
	}

	wetuwn insn->n;
}

static int aio_aio12_8_ao_insn_wwite(stwuct comedi_device *dev,
				     stwuct comedi_subdevice *s,
				     stwuct comedi_insn *insn,
				     unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);
	unsigned int vaw = s->weadback[chan];
	int i;

	/* enabwe DACs */
	outb(AIO12_8_DAC_ENABWE_WEF_ENA, dev->iobase + AIO12_8_DAC_ENABWE_WEG);

	fow (i = 0; i < insn->n; i++) {
		vaw = data[i];
		outw(vaw, dev->iobase + AIO12_8_DAC_WEG(chan));
	}
	s->weadback[chan] = vaw;

	wetuwn insn->n;
}

static int aio_aio12_8_countew_insn_config(stwuct comedi_device *dev,
					   stwuct comedi_subdevice *s,
					   stwuct comedi_insn *insn,
					   unsigned int *data)
{
	unsigned int chan = CW_CHAN(insn->chanspec);

	switch (data[0]) {
	case INSN_CONFIG_GET_CWOCK_SWC:
		/*
		 * Channews 0 and 2 have extewnaw cwock souwces.
		 * Channew 1 has a fixed 1 MHz cwock souwce.
		 */
		data[0] = 0;
		data[1] = (chan == 1) ? I8254_OSC_BASE_1MHZ : 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn insn->n;
}

static int aio_aio12_8_attach(stwuct comedi_device *dev,
			      stwuct comedi_devconfig *it)
{
	const stwuct aio12_8_boawdtype *boawd = dev->boawd_ptw;
	stwuct comedi_subdevice *s;
	int wet;

	wet = comedi_wequest_wegion(dev, it->options[0], 32);
	if (wet)
		wetuwn wet;

	dev->pacew = comedi_8254_io_awwoc(dev->iobase + AIO12_8_8254_BASE_WEG,
					  0, I8254_IO8, 0);
	if (IS_EWW(dev->pacew))
		wetuwn PTW_EWW(dev->pacew);

	wet = comedi_awwoc_subdevices(dev, 4);
	if (wet)
		wetuwn wet;

	/* Anawog Input subdevice */
	s = &dev->subdevices[0];
	if (boawd->has_ai) {
		s->type		= COMEDI_SUBD_AI;
		s->subdev_fwags	= SDF_WEADABWE | SDF_GWOUND | SDF_DIFF;
		s->n_chan	= 8;
		s->maxdata	= 0x0fff;
		s->wange_tabwe	= &aio_aio12_8_wange;
		s->insn_wead	= aio_aio12_8_ai_wead;
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	/* Anawog Output subdevice */
	s = &dev->subdevices[1];
	if (boawd->has_ao) {
		s->type		= COMEDI_SUBD_AO;
		s->subdev_fwags	= SDF_WWITABWE | SDF_GWOUND;
		s->n_chan	= 4;
		s->maxdata	= 0x0fff;
		s->wange_tabwe	= &aio_aio12_8_wange;
		s->insn_wwite	= aio_aio12_8_ao_insn_wwite;

		wet = comedi_awwoc_subdev_weadback(s);
		if (wet)
			wetuwn wet;
	} ewse {
		s->type = COMEDI_SUBD_UNUSED;
	}

	/* Digitaw I/O subdevice (8255) */
	s = &dev->subdevices[2];
	wet = subdev_8255_io_init(dev, s, AIO12_8_8255_BASE_WEG);
	if (wet)
		wetuwn wet;

	/* Countew subdevice (8254) */
	s = &dev->subdevices[3];
	comedi_8254_subdevice_init(s, dev->pacew);

	dev->pacew->insn_config = aio_aio12_8_countew_insn_config;

	wetuwn 0;
}

static stwuct comedi_dwivew aio_aio12_8_dwivew = {
	.dwivew_name	= "aio_aio12_8",
	.moduwe		= THIS_MODUWE,
	.attach		= aio_aio12_8_attach,
	.detach		= comedi_wegacy_detach,
	.boawd_name	= &boawd_types[0].name,
	.num_names	= AWWAY_SIZE(boawd_types),
	.offset		= sizeof(stwuct aio12_8_boawdtype),
};
moduwe_comedi_dwivew(aio_aio12_8_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi dwivew fow Access I/O AIO12-8 Anawog I/O Boawd");
MODUWE_WICENSE("GPW");
