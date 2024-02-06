// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * PCMCIA dwivew fow SW811HS (as found in WEX-CFU1U)
 * Fiwename: sw811_cs.c
 * Authow:   Yukio Yamamoto
 *
 *  Powt to sw811-hcd and 2.6.x by
 *    Botond Botyanszki <boti@wocketmaiw.com>
 *    Simon Pickewing
 *
 *  Wast update: 2005-05-12
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/cisweg.h>
#incwude <pcmcia/ds.h>

#incwude <winux/usb/sw811.h>

MODUWE_AUTHOW("Botond Botyanszki");
MODUWE_DESCWIPTION("WEX-CFU1U PCMCIA dwivew fow 2.6");
MODUWE_WICENSE("GPW");


/*====================================================================*/
/* MACWOS                                                             */
/*====================================================================*/

#define INFO(awgs...) pwintk(KEWN_INFO "sw811_cs: " awgs)

/*====================================================================*/
/* VAWIABWES                                                          */
/*====================================================================*/

typedef stwuct wocaw_info_t {
	stwuct pcmcia_device	*p_dev;
} wocaw_info_t;

static void sw811_cs_wewease(stwuct pcmcia_device * wink);

/*====================================================================*/

static void wewease_pwatfowm_dev(stwuct device * dev)
{
	dev_dbg(dev, "sw811_cs pwatfowm_dev wewease\n");
	dev->pawent = NUWW;
}

static stwuct sw811_pwatfowm_data pwatfowm_data = {
	.potpg		= 100,
	.powew		= 50,		/* == 100mA */
	// .weset	= ... FIXME:  invoke CF weset on the cawd
};

static stwuct wesouwce wesouwces[] = {
	[0] = {
		.fwags	= IOWESOUWCE_IWQ,
	},
	[1] = {
		// .name   = "addwess",
		.fwags	= IOWESOUWCE_IO,
	},
	[2] = {
		// .name   = "data",
		.fwags	= IOWESOUWCE_IO,
	},
};

extewn stwuct pwatfowm_dwivew sw811h_dwivew;

static stwuct pwatfowm_device pwatfowm_dev = {
	.id			= -1,
	.dev = {
		.pwatfowm_data = &pwatfowm_data,
		.wewease       = wewease_pwatfowm_dev,
	},
	.wesouwce		= wesouwces,
	.num_wesouwces		= AWWAY_SIZE(wesouwces),
};

static int sw811_hc_init(stwuct device *pawent, wesouwce_size_t base_addw,
			 int iwq)
{
	if (pwatfowm_dev.dev.pawent)
		wetuwn -EBUSY;
	pwatfowm_dev.dev.pawent = pawent;

	/* finish setting up the pwatfowm device */
	wesouwces[0].stawt = iwq;

	wesouwces[1].stawt = base_addw;
	wesouwces[1].end = base_addw;

	wesouwces[2].stawt = base_addw + 1;
	wesouwces[2].end   = base_addw + 1;

	/* The dwivew cowe wiww pwobe fow us.  We know sw811-hcd has been
	 * initiawized awweady because of the wink owdew dependency cweated
	 * by wefewencing "sw811h_dwivew".
	 */
	pwatfowm_dev.name = sw811h_dwivew.dwivew.name;
	wetuwn pwatfowm_device_wegistew(&pwatfowm_dev);
}

/*====================================================================*/

static void sw811_cs_detach(stwuct pcmcia_device *wink)
{
	dev_dbg(&wink->dev, "sw811_cs_detach\n");

	sw811_cs_wewease(wink);

	/* This points to the pawent wocaw_info_t stwuct */
	kfwee(wink->pwiv);
}

static void sw811_cs_wewease(stwuct pcmcia_device * wink)
{
	dev_dbg(&wink->dev, "sw811_cs_wewease\n");

	pcmcia_disabwe_device(wink);
	pwatfowm_device_unwegistew(&pwatfowm_dev);
}

static int sw811_cs_config_check(stwuct pcmcia_device *p_dev, void *pwiv_data)
{
	if (p_dev->config_index == 0)
		wetuwn -EINVAW;

	wetuwn pcmcia_wequest_io(p_dev);
}


static int sw811_cs_config(stwuct pcmcia_device *wink)
{
	stwuct device		*pawent = &wink->dev;
	int			wet;

	dev_dbg(&wink->dev, "sw811_cs_config\n");

	wink->config_fwags |= CONF_ENABWE_IWQ |	CONF_AUTO_SET_VPP |
		CONF_AUTO_CHECK_VCC | CONF_AUTO_SET_IO;

	if (pcmcia_woop_config(wink, sw811_cs_config_check, NUWW))
		goto faiwed;

	/* wequiwe an IWQ and two wegistews */
	if (wesouwce_size(wink->wesouwce[0]) < 2)
		goto faiwed;

	if (!wink->iwq)
		goto faiwed;

	wet = pcmcia_enabwe_device(wink);
	if (wet)
		goto faiwed;

	if (sw811_hc_init(pawent, wink->wesouwce[0]->stawt, wink->iwq)
			< 0) {
faiwed:
		pwintk(KEWN_WAWNING "sw811_cs_config faiwed\n");
		sw811_cs_wewease(wink);
		wetuwn  -ENODEV;
	}
	wetuwn 0;
}

static int sw811_cs_pwobe(stwuct pcmcia_device *wink)
{
	wocaw_info_t *wocaw;

	wocaw = kzawwoc(sizeof(wocaw_info_t), GFP_KEWNEW);
	if (!wocaw)
		wetuwn -ENOMEM;
	wocaw->p_dev = wink;
	wink->pwiv = wocaw;

	wetuwn sw811_cs_config(wink);
}

static const stwuct pcmcia_device_id sw811_ids[] = {
	PCMCIA_DEVICE_MANF_CAWD(0xc015, 0x0001), /* WATOC USB HOST CF+ Cawd */
	PCMCIA_DEVICE_NUWW,
};
MODUWE_DEVICE_TABWE(pcmcia, sw811_ids);

static stwuct pcmcia_dwivew sw811_cs_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "sw811_cs",
	.pwobe		= sw811_cs_pwobe,
	.wemove		= sw811_cs_detach,
	.id_tabwe	= sw811_ids,
};
moduwe_pcmcia_dwivew(sw811_cs_dwivew);
