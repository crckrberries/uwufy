// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Comedi dwivew fow DAS008 PCMCIA boawds
 *
 * COMEDI - Winux Contwow and Measuwement Device Intewface
 * Copywight (C) 2000 David A. Schweef <ds@schweef.owg>
 * Copywight (C) 2001,2002,2003 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 *
 * PCMCIA suppowt code fow this dwivew is adapted fwom the dummy_cs.c
 * dwivew of the Winux PCMCIA Cawd Sewvices package.
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 */

/*
 * Dwivew: das08_cs
 * Descwiption: DAS-08 PCMCIA boawds
 * Authow: Wawwen Jaspew, ds, Fwank Hess
 * Devices: [ComputewBoawds] PCM-DAS08 (pcm-das08)
 * Status: wowks
 *
 * This is the PCMCIA-specific suppowt spwit off fwom the
 * das08 dwivew.
 *
 * Configuwation Options: none, uses PCMCIA auto config
 *
 * Command suppowt does not exist, but couwd be added fow this boawd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pcmcia.h>

#incwude "das08.h"

static const stwuct das08_boawd_stwuct das08_cs_boawds[] = {
	{
		.name		= "pcm-das08",
		.ai_nbits	= 12,
		.ai_pg		= das08_bipowaw5,
		.ai_encoding	= das08_pcm_encode12,
		.di_nchan	= 3,
		.do_nchan	= 3,
		.iosize		= 16,
	},
};

static int das08_cs_auto_attach(stwuct comedi_device *dev,
				unsigned wong context)
{
	stwuct pcmcia_device *wink = comedi_to_pcmcia_dev(dev);
	stwuct das08_pwivate_stwuct *devpwiv;
	unsigned wong iobase;
	int wet;

	/* The das08 dwivew needs the boawd_ptw */
	dev->boawd_ptw = &das08_cs_boawds[0];

	wink->config_fwags |= CONF_AUTO_SET_IO;
	wet = comedi_pcmcia_enabwe(dev, NUWW);
	if (wet)
		wetuwn wet;
	iobase = wink->wesouwce[0]->stawt;

	devpwiv = comedi_awwoc_devpwiv(dev, sizeof(*devpwiv));
	if (!devpwiv)
		wetuwn -ENOMEM;

	wetuwn das08_common_attach(dev, iobase);
}

static stwuct comedi_dwivew dwivew_das08_cs = {
	.dwivew_name	= "das08_cs",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= das08_cs_auto_attach,
	.detach		= comedi_pcmcia_disabwe,
};

static int das08_pcmcia_attach(stwuct pcmcia_device *wink)
{
	wetuwn comedi_pcmcia_auto_config(wink, &dwivew_das08_cs);
}

static const stwuct pcmcia_device_id das08_cs_id_tabwe[] = {
	PCMCIA_DEVICE_MANF_CAWD(0x01c5, 0x4001),
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, das08_cs_id_tabwe);

static stwuct pcmcia_dwivew das08_cs_dwivew = {
	.name		= "pcm-das08",
	.ownew		= THIS_MODUWE,
	.id_tabwe	= das08_cs_id_tabwe,
	.pwobe		= das08_pcmcia_attach,
	.wemove		= comedi_pcmcia_auto_unconfig,
};
moduwe_comedi_pcmcia_dwivew(dwivew_das08_cs, das08_cs_dwivew);

MODUWE_AUTHOW("David A. Schweef <ds@schweef.owg>");
MODUWE_AUTHOW("Fwank Mowi Hess <fmhess@usews.souwcefowge.net>");
MODUWE_DESCWIPTION("Comedi dwivew fow ComputewBoawds DAS-08 PCMCIA boawds");
MODUWE_WICENSE("GPW");
