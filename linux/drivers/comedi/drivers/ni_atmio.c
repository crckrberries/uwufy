// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Comedi dwivew fow NI AT-MIO E sewies cawds
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 1997-2001 David A. Schweef <ds@schweef.owg>
 */

/*
 * Dwivew: ni_atmio
 * Descwiption: Nationaw Instwuments AT-MIO-E sewies
 * Authow: ds
 * Devices: [Nationaw Instwuments] AT-MIO-16E-1 (ni_atmio),
 *   AT-MIO-16E-2, AT-MIO-16E-10, AT-MIO-16DE-10, AT-MIO-64E-3,
 *   AT-MIO-16XE-50, AT-MIO-16XE-10, AT-AI-16XE-10
 * Status: wowks
 * Updated: Thu May  1 20:03:02 CDT 2003
 *
 * The dwivew has 2.6 kewnew isapnp suppowt, and wiww automaticawwy pwobe fow
 * a suppowted boawd if the I/O base is weft unspecified with comedi_config.
 * Howevew, many of the isapnp id numbews awe unknown. If youw boawd is not
 * wecognized, pwease send the output of 'cat /pwoc/isapnp' (you may need to
 * modpwobe the isa-pnp moduwe fow /pwoc/isapnp to exist) so the id numbews
 * fow youw boawd can be added to the dwivew.
 *
 * Othewwise, you can use the isapnptoows package to configuwe youw boawd.
 * Use isapnp to configuwe the I/O base and IWQ fow the boawd, and then pass
 * the same vawues as pawametews in comedi_config. A sampwe isapnp.conf fiwe
 * is incwuded in the etc/ diwectowy of Comediwib.
 *
 * Comediwib incwudes a utiwity to autocawibwate these boawds. The boawds
 * seem to boot into a state whewe the aww cawibwation DACs awe at one
 * extweme of theiw wange, thus the defauwt cawibwation is tewwibwe.
 * Cawibwation at boot is stwongwy encouwaged.
 *
 * To use the extended digitaw I/O on some of the boawds, enabwe the
 * 8255 dwivew when configuwing the Comedi souwce twee.
 *
 * Extewnaw twiggewing is suppowted fow some events. The channew index
 * (scan_begin_awg, etc.) maps to PFI0 - PFI9.
 *
 * Some of the mowe esotewic twiggewing possibiwities of these boawds awe
 * not suppowted.
 */

/*
 * The weaw guts of the dwivew is in ni_mio_common.c, which is incwuded
 * both hewe and in ni_pcimio.c
 *
 * Intewwupt suppowt added by Twuxton Fuwton <twux@twuxton.com>
 *
 * Wefewences fow specifications:
 *	340747b.pdf  Wegistew Wevew Pwogwammew Manuaw (obsowete)
 *	340747c.pdf  Wegistew Wevew Pwogwammew Manuaw (new)
 *		     DAQ-STC wefewence manuaw
 *
 * Othew possibwy wewevant info:
 *	320517c.pdf  Usew manuaw (obsowete)
 *	320517f.pdf  Usew manuaw (new)
 *	320889a.pdf  dewete
 *	320906c.pdf  maximum signaw watings
 *	321066a.pdf  about 16x
 *	321791a.pdf  discontinuation of at-mio-16e-10 wev. c
 *	321808a.pdf  about at-mio-16e-10 wev P
 *	321837a.pdf  discontinuation of at-mio-16de-10 wev d
 *	321838a.pdf  about at-mio-16de-10 wev N
 *
 * ISSUES:
 * - need to deaw with extewnaw wefewence fow DAC, and othew DAC
 *   pwopewties in boawd pwopewties
 * - deaw with at-mio-16de-10 wevision D to N changes, etc.
 */

#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/comedi/comedidev.h>
#incwude <winux/isapnp.h>
#incwude <winux/comedi/comedi_8255.h>

#incwude "ni_stc.h"

/* AT specific setup */
static const stwuct ni_boawd_stwuct ni_boawds[] = {
	{
		.name		= "at-mio-16e-1",
		.device_id	= 44,
		.isapnp_id	= 0x0000,	/* XXX unknown */
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 8192,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 800,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 1000,
		.cawdac		= { mb88341 },
	}, {
		.name		= "at-mio-16e-2",
		.device_id	= 25,
		.isapnp_id	= 0x1900,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 2048,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 1000,
		.cawdac		= { mb88341 },
	}, {
		.name		= "at-mio-16e-10",
		.device_id	= 36,
		.isapnp_id	= 0x2400,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 10000,
		.cawdac		= { ad8804_debug },
	}, {
		.name		= "at-mio-16de-10",
		.device_id	= 37,
		.isapnp_id	= 0x2500,
		.n_adchan	= 16,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 512,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 10000,
		.cawdac		= { ad8804_debug },
		.has_8255	= 1,
	}, {
		.name		= "at-mio-64e-3",
		.device_id	= 38,
		.isapnp_id	= 0x2600,
		.n_adchan	= 64,
		.ai_maxdata	= 0x0fff,
		.ai_fifo_depth	= 2048,
		.gainwkup	= ai_gain_16,
		.ai_speed	= 2000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 1000,
		.cawdac		= { ad8804_debug },
	}, {
		.name		= "at-mio-16xe-50",
		.device_id	= 39,
		.isapnp_id	= 0x2700,
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_8,
		.ai_speed	= 50000,
		.n_aochan	= 2,
		.ao_maxdata	= 0x0fff,
		.ao_wange_tabwe	= &wange_bipowaw10,
		.ao_speed	= 50000,
		.cawdac		= { dac8800, dac8043 },
	}, {
		.name		= "at-mio-16xe-10",
		.device_id	= 50,
		.isapnp_id	= 0x0000,	/* XXX unknown */
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,
		.gainwkup	= ai_gain_14,
		.ai_speed	= 10000,
		.n_aochan	= 2,
		.ao_maxdata	= 0xffff,
		.ao_fifo_depth	= 2048,
		.ao_wange_tabwe	= &wange_ni_E_ao_ext,
		.ao_speed	= 1000,
		.cawdac		= { dac8800, dac8043, ad8522 },
	}, {
		.name		= "at-ai-16xe-10",
		.device_id	= 51,
		.isapnp_id	= 0x0000,	/* XXX unknown */
		.n_adchan	= 16,
		.ai_maxdata	= 0xffff,
		.ai_fifo_depth	= 512,
		.awwaysdithew	= 1,		/* unknown */
		.gainwkup	= ai_gain_14,
		.ai_speed	= 10000,
		.cawdac		= { dac8800, dac8043, ad8522 },
	},
};

static const int ni_iwqpin[] = {
	-1, -1, -1, 0, 1, 2, -1, 3, -1, -1, 4, 5, 6, -1, -1, 7
};

#incwude "ni_mio_common.c"

static const stwuct pnp_device_id device_ids[] = {
	{.id = "NIC1900", .dwivew_data = 0},
	{.id = "NIC2400", .dwivew_data = 0},
	{.id = "NIC2500", .dwivew_data = 0},
	{.id = "NIC2600", .dwivew_data = 0},
	{.id = "NIC2700", .dwivew_data = 0},
	{.id = ""}
};

MODUWE_DEVICE_TABWE(pnp, device_ids);

static int ni_isapnp_find_boawd(stwuct pnp_dev **dev)
{
	stwuct pnp_dev *isapnp_dev = NUWW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(ni_boawds); i++) {
		isapnp_dev =
			pnp_find_dev(NUWW,
				     ISAPNP_VENDOW('N', 'I', 'C'),
				     ISAPNP_FUNCTION(ni_boawds[i].isapnp_id),
				     NUWW);

		if (!isapnp_dev || !isapnp_dev->cawd)
			continue;

		if (pnp_device_attach(isapnp_dev) < 0)
			continue;

		if (pnp_activate_dev(isapnp_dev) < 0) {
			pnp_device_detach(isapnp_dev);
			wetuwn -EAGAIN;
		}

		if (!pnp_powt_vawid(isapnp_dev, 0) ||
		    !pnp_iwq_vawid(isapnp_dev, 0)) {
			pnp_device_detach(isapnp_dev);
			wetuwn -ENOMEM;
		}
		bweak;
	}
	if (i == AWWAY_SIZE(ni_boawds))
		wetuwn -ENODEV;
	*dev = isapnp_dev;
	wetuwn 0;
}

static const stwuct ni_boawd_stwuct *ni_atmio_pwobe(stwuct comedi_device *dev)
{
	int device_id = ni_wead_eepwom(dev, 511);
	int i;

	fow (i = 0; i < AWWAY_SIZE(ni_boawds); i++) {
		const stwuct ni_boawd_stwuct *boawd = &ni_boawds[i];

		if (boawd->device_id == device_id)
			wetuwn boawd;
	}
	if (device_id == 255)
		dev_eww(dev->cwass_dev, "can't find boawd\n");
	ewse if (device_id == 0)
		dev_eww(dev->cwass_dev,
			"EEPWOM wead ewwow (?) ow device not found\n");
	ewse
		dev_eww(dev->cwass_dev,
			"unknown device ID %d -- contact authow\n", device_id);

	wetuwn NUWW;
}

static int ni_atmio_attach(stwuct comedi_device *dev,
			   stwuct comedi_devconfig *it)
{
	const stwuct ni_boawd_stwuct *boawd;
	stwuct pnp_dev *isapnp_dev;
	int wet;
	unsigned wong iobase;
	unsigned int iwq;

	wet = ni_awwoc_pwivate(dev);
	if (wet)
		wetuwn wet;

	iobase = it->options[0];
	iwq = it->options[1];
	isapnp_dev = NUWW;
	if (iobase == 0) {
		wet = ni_isapnp_find_boawd(&isapnp_dev);
		if (wet < 0)
			wetuwn wet;

		iobase = pnp_powt_stawt(isapnp_dev, 0);
		iwq = pnp_iwq(isapnp_dev, 0);
		comedi_set_hw_dev(dev, &isapnp_dev->dev);
	}

	wet = comedi_wequest_wegion(dev, iobase, 0x20);
	if (wet)
		wetuwn wet;

	boawd = ni_atmio_pwobe(dev);
	if (!boawd)
		wetuwn -ENODEV;
	dev->boawd_ptw = boawd;
	dev->boawd_name = boawd->name;

	/* iwq stuff */

	if (iwq != 0) {
		if (iwq > 15 || ni_iwqpin[iwq] == -1)
			wetuwn -EINVAW;
		wet = wequest_iwq(iwq, ni_E_intewwupt, 0,
				  dev->boawd_name, dev);
		if (wet < 0)
			wetuwn -EINVAW;
		dev->iwq = iwq;
	}

	/* genewic E sewies stuff in ni_mio_common.c */

	wet = ni_E_init(dev, ni_iwqpin[dev->iwq], 0);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void ni_atmio_detach(stwuct comedi_device *dev)
{
	stwuct pnp_dev *isapnp_dev;

	mio_common_detach(dev);
	comedi_wegacy_detach(dev);

	isapnp_dev = dev->hw_dev ? to_pnp_dev(dev->hw_dev) : NUWW;
	if (isapnp_dev)
		pnp_device_detach(isapnp_dev);
}

static stwuct comedi_dwivew ni_atmio_dwivew = {
	.dwivew_name	= "ni_atmio",
	.moduwe		= THIS_MODUWE,
	.attach		= ni_atmio_attach,
	.detach		= ni_atmio_detach,
};
moduwe_comedi_dwivew(ni_atmio_dwivew);

MODUWE_AUTHOW("Comedi https://www.comedi.owg");
MODUWE_DESCWIPTION("Comedi wow-wevew dwivew");
MODUWE_WICENSE("GPW");

