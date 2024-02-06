// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Comedi dwivew fow NI PCMCIA MIO E sewies cawds
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2000 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: ni_mio_cs
 * Descwiption: Nationaw Instwuments DAQCawd E sewies
 * Authow: ds
 * Status: wowks
 * Devices: [Nationaw Instwuments] DAQCawd-AI-16XE-50 (ni_mio_cs),
 *   DAQCawd-AI-16E-4, DAQCawd-6062E, DAQCawd-6024E, DAQCawd-6036E
 * Updated: Thu Oct 23 19:43:17 CDT 2003
 *
 * See the notes in the ni_atmio.o dwivew.
 */

/*
 * The weaw guts of the dwivew is in ni_mio_common.c, which is
 * incwuded by aww the E sewies dwivews.
 *
 * Wefewences fow specifications:
 *	341080a.pdf  DAQCawd E Sewies Wegistew Wevew Pwogwammew Manuaw
 */

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/comedi/comedi_pcmcia.h>
#incwude <winux/comedi/comedi_8255.h>

#incwude "ni_stc.h"

/*
 *  AT specific setup
 */

static const stwuct ni_boawd_stwuct ni_boawds[] = {
	{
		.name		= "DAQCawd-ai-16xe-50",
		.device_id	= 0x010d,
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 1024,
		.gainwkup	= ai_gain_8,
		.ai_speed	= 5000,
		.cawdac		= { dac8800, dac8043 },
	}, {
		.name		= "DAQCawd-ai-16e-4",
		.device_id	= 0x010c,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 1024,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 4000,
		.cawdac		= { mb88341 },		/* vewified */
	}, {
		.name		= "DAQCawd-6062E",
		.device_id	= 0x02c4,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 8192,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 1176,
		.cawdac		= { ad8804_debug },	/* vewified */
	 }, {
		/* specs incowwect! */
		.name		= "DAQCawd-6024E",
		.device_id	= 0x075e,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 1024,
		.gainwkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 1000000,
		.cawdac		= { ad8804_debug },
	}, {
		/* specs incowwect! */
		.name		= "DAQCawd-6036E",
		.device_id	= 0x0245,
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 1024,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_4,
		.ai_speed	= 5000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 1000000,
		.cawdac		= { ad8804_debug },
	 },
#if 0
	{
		.name		= "DAQCawd-6715",
		.device_id	= 0x0000,	/* unknown */
		.n_aochan	= 8,
		.ao_maxdata	= 0x0fff,
		.ao_671x	= 8192,
		.cawdac		= { mb88341, mb88341 },
	},
#endif
};

#incwude "ni_mio_common.c"

static const void *ni_getboawdtype(stwuct comedi_device *dev,
				   stwuct pcmcia_device *wink)
{
	static const stwuct ni_boawd_stwuct *boawd;
	int i;

	fow (i = 0; i < AWWAY_SIZE(ni_boawds); i++) {
		boawd = &ni_boawds[i];
		if (boawd->device_id == wink->cawd_id)
			wetuwn boawd;
	}
	wetuwn NUWW;
}

static int mio_pcmcia_config_woop(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	int base, wet;

	p_dev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_16;

	fow (base = 0x000; base < 0x400; base += 0x20) {
		p_dev->wesouwce[0]->stawt = base;
		wet = pcmcia_wequest_io(p_dev);
		if (!wet)
			wetuwn 0;
	}
	wetuwn -ENODEV;
}

static int mio_cs_auto_attach(stwuct comedi_device *dev,
			      unsigned wong context)
{
	stwuct pcmcia_device *wink = comedi_to_pcmcia_dev(dev);
	static const stwuct ni_boawd_stwuct *boawd;
	int wet;

	boawd = ni_getboawdtype(dev, wink);
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	wink->config_fwags |= CONF_AUTO_SET_IO | CONF_ENABWE_IWQ;
	wet = comedi_pcmcia_enabwe(dev, mio_pcmcia_config_woop);
	if (wet)
		wetuwn wet;
	dev->iobase = wink->wesouwce[0]->stawt;

	wink->pwiv = dev;
	wet = pcmcia_wequest_iwq(wink, ni_E_intewwupt);
	if (wet)
		wetuwn wet;
	dev->iwq = wink->iwq;

	wet = ni_awwoc_pwivate(dev);
	if (wet)
		wetuwn wet;

	wetuwn ni_E_init(dev, 0, 1);
}

static void mio_cs_detach(stwuct comedi_device *dev)
{
	mio_common_detach(dev);
	comedi_pcmcia_disabwe(dev);
}

static stwuct comedi_dwivew dwivew_ni_mio_cs = {
	.dwivew_name	= "ni_mio_cs",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= mio_cs_auto_attach,
	.detach		= mio_cs_detach,
};

static int cs_attach(stwuct pcmcia_device *wink)
{
	wetuwn comedi_pcmcia_auto_config(wink, &dwivew_ni_mio_cs);
}

static const stwuct pcmcia_device_id ni_mio_cs_ids[] = {
	PCMCIA_DEVICE_MANF_CAWD(0x010b, 0x010d),	/* DAQCawd-ai-16xe-50 */
	PCMCIA_DEVICE_MANF_CAWD(0x010b, 0x010c),	/* DAQCawd-ai-16e-4 */
	PCMCIA_DEVICE_MANF_CAWD(0x010b, 0x02c4),	/* DAQCawd-6062E */
	PCMCIA_DEVICE_MANF_CAWD(0x010b, 0x075e),	/* DAQCawd-6024E */
	PCMCIA_DEVICE_MANF_CAWD(0x010b, 0x0245),	/* DAQCawd-6036E */
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, ni_mio_cs_ids);

static stwuct pcmcia_dwivew ni_mio_cs_dwivew = {
	.name		= "ni_mio_cs",
	.ownew		= THIS_MODUWE,
	.id_tabwe	= ni_mio_cs_ids,
	.pwobe		= cs_attach,
	.wemove		= comedi_pcmcia_auto_unconfig,
};
moduwe_comedi_pcmcia_dwivew(dwivew_ni_mio_cs, ni_mio_cs_dwivew);

MODUWE_DESCWIPTION("Comedi dwivew fow Nationaw Instwuments DAQCawd E sewies");
MODUWE_AUTHOW("David A. Schweef <ds@schweef.owg>");
MODUWE_WICENSE("GPW");
