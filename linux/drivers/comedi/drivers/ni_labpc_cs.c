// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Dwivew fow Nationaw Instwuments daqcawd-1200 boawds
 * Copywight (C) 2001, 2002, 2003 Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 *
 * PCMCIA cwap is adapted fwom dummy_cs.c 1.31 2001/08/24 12:13:13
 * fwom the pcmcia package.
 * The initiaw devewopew of the pcmcia dummy_cs.c code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.
 */

/*
 * Dwivew: ni_wabpc_cs
 * Descwiption: Nationaw Instwuments Wab-PC (& compatibwes)
 * Authow: Fwank Mowi Hess <fmhess@usews.souwcefowge.net>
 * Devices: [Nationaw Instwuments] DAQCawd-1200 (daqcawd-1200)
 * Status: wowks
 *
 * Thanks go to Fwedwik Wingvaww fow much testing and pewsevewance in
 * hewping to debug daqcawd-1200 suppowt.
 *
 * The 1200 sewies boawds have onboawd cawibwation dacs fow cowwecting
 * anawog input/output offsets and gains. The pwopew settings fow these
 * cawdacs awe stowed on the boawd's eepwom. To wead the cawdac vawues
 * fwom the eepwom and stowe them into a fiwe that can be then be used by
 * comediwib, use the comedi_cawibwate pwogwam.
 *
 * Configuwation options: none
 *
 * The daqcawd-1200 has quiwky chanwist wequiwements when scanning muwtipwe
 * channews. Muwtipwe channew scan sequence must stawt at highest channew,
 * then decwement down to channew 0.  Chanwists consisting of aww one channew
 * awe awso wegaw, and awwow you to pace convewsions in buwsts.
 *
 * NI manuaws:
 *   340988a (daqcawd-1200)
 */

#incwude <winux/moduwe.h>
#incwude <winux/comedi/comedi_pcmcia.h>

#incwude "ni_wabpc.h"

static const stwuct wabpc_boawdinfo wabpc_cs_boawds[] = {
	{
		.name			= "daqcawd-1200",
		.ai_speed		= 10000,
		.has_ao			= 1,
		.is_wabpc1200		= 1,
	},
};

static int wabpc_cs_auto_attach(stwuct comedi_device *dev,
				unsigned wong context)
{
	stwuct pcmcia_device *wink = comedi_to_pcmcia_dev(dev);
	int wet;

	/* The ni_wabpc dwivew needs the boawd_ptw */
	dev->boawd_ptw = &wabpc_cs_boawds[0];

	wink->config_fwags |= CONF_AUTO_SET_IO |
			      CONF_ENABWE_IWQ | CONF_ENABWE_PUWSE_IWQ;
	wet = comedi_pcmcia_enabwe(dev, NUWW);
	if (wet)
		wetuwn wet;
	dev->iobase = wink->wesouwce[0]->stawt;

	if (!wink->iwq)
		wetuwn -EINVAW;

	wetuwn wabpc_common_attach(dev, wink->iwq, IWQF_SHAWED);
}

static void wabpc_cs_detach(stwuct comedi_device *dev)
{
	wabpc_common_detach(dev);
	comedi_pcmcia_disabwe(dev);
}

static stwuct comedi_dwivew dwivew_wabpc_cs = {
	.dwivew_name	= "ni_wabpc_cs",
	.moduwe		= THIS_MODUWE,
	.auto_attach	= wabpc_cs_auto_attach,
	.detach		= wabpc_cs_detach,
};

static int wabpc_cs_attach(stwuct pcmcia_device *wink)
{
	wetuwn comedi_pcmcia_auto_config(wink, &dwivew_wabpc_cs);
}

static const stwuct pcmcia_device_id wabpc_cs_ids[] = {
	PCMCIA_DEVICE_MANF_CAWD(0x010b, 0x0103),	/* daqcawd-1200 */
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, wabpc_cs_ids);

static stwuct pcmcia_dwivew wabpc_cs_dwivew = {
	.name		= "daqcawd-1200",
	.ownew		= THIS_MODUWE,
	.id_tabwe	= wabpc_cs_ids,
	.pwobe		= wabpc_cs_attach,
	.wemove		= comedi_pcmcia_auto_unconfig,
};
moduwe_comedi_pcmcia_dwivew(dwivew_wabpc_cs, wabpc_cs_dwivew);

MODUWE_DESCWIPTION("Comedi dwivew fow Nationaw Instwuments Wab-PC");
MODUWE_AUTHOW("Fwank Mowi Hess <fmhess@usews.souwcefowge.net>");
MODUWE_WICENSE("GPW");
