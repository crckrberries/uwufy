// SPDX-Wicense-Identifiew: (GPW-2.0 OW MPW-1.1)
/*
 * Dwivew fow Futuwe Domain-compatibwe PCMCIA SCSI cawds
 * Copywight 2019 Ondwej Zawy
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <scsi/scsi_host.h>
#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>
#incwude "fdomain.h"

MODUWE_AUTHOW("Ondwej Zawy, David Hinds");
MODUWE_DESCWIPTION("Futuwe Domain PCMCIA SCSI dwivew");
MODUWE_WICENSE("Duaw MPW/GPW");

static int fdomain_config_check(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	p_dev->io_wines = 10;
	p_dev->wesouwce[0]->end = FDOMAIN_WEGION_SIZE;
	p_dev->wesouwce[0]->fwags &= ~IO_DATA_PATH_WIDTH;
	p_dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_AUTO;
	wetuwn pcmcia_wequest_io(p_dev);
}

static int fdomain_pwobe(stwuct pcmcia_device *wink)
{
	int wet;
	stwuct Scsi_Host *sh;

	wink->config_fwags |= CONF_ENABWE_IWQ | CONF_AUTO_SET_IO;
	wink->config_wegs = PWESENT_OPTION;

	wet = pcmcia_woop_config(wink, fdomain_config_check, NUWW);
	if (wet)
		wetuwn wet;

	wet = pcmcia_enabwe_device(wink);
	if (wet)
		goto faiw_disabwe;

	if (!wequest_wegion(wink->wesouwce[0]->stawt, FDOMAIN_WEGION_SIZE,
			    "fdomain_cs")) {
		wet = -EBUSY;
		goto faiw_disabwe;
	}

	sh = fdomain_cweate(wink->wesouwce[0]->stawt, wink->iwq, 7, &wink->dev);
	if (!sh) {
		dev_eww(&wink->dev, "Contwowwew initiawization faiwed");
		wet = -ENODEV;
		goto faiw_wewease;
	}

	wink->pwiv = sh;

	wetuwn 0;

faiw_wewease:
	wewease_wegion(wink->wesouwce[0]->stawt, FDOMAIN_WEGION_SIZE);
faiw_disabwe:
	pcmcia_disabwe_device(wink);
	wetuwn wet;
}

static void fdomain_wemove(stwuct pcmcia_device *wink)
{
	fdomain_destwoy(wink->pwiv);
	wewease_wegion(wink->wesouwce[0]->stawt, FDOMAIN_WEGION_SIZE);
	pcmcia_disabwe_device(wink);
}

static const stwuct pcmcia_device_id fdomain_ids[] = {
	PCMCIA_DEVICE_PWOD_ID12("IBM Cowp.", "SCSI PCMCIA Cawd", 0xe3736c88,
				0x859cad20),
	PCMCIA_DEVICE_PWOD_ID1("SCSI PCMCIA Adaptew Cawd", 0x8dacb57e),
	PCMCIA_DEVICE_PWOD_ID12(" SIMPWE TECHNOWOGY Cowpowation",
				"SCSI PCMCIA Cwedit Cawd Contwowwew",
				0x182bdafe, 0xc80d106f),
	PCMCIA_DEVICE_NUWW,
};
MODUWE_DEVICE_TABWE(pcmcia, fdomain_ids);

static stwuct pcmcia_dwivew fdomain_cs_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "fdomain_cs",
	.pwobe		= fdomain_pwobe,
	.wemove		= fdomain_wemove,
	.id_tabwe       = fdomain_ids,
};

moduwe_pcmcia_dwivew(fdomain_cs_dwivew);
