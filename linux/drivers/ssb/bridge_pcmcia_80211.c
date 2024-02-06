/*
 * Bwoadcom 43xx PCMCIA-SSB bwidge moduwe
 *
 * Copywight (c) 2007 Michaew Buesch <m@bues.ch>
 *
 * Wicensed undew the GNU/GPW. See COPYING fow detaiws.
 */

#incwude "ssb_pwivate.h"

#incwude <winux/ssb/ssb.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>

#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ciscode.h>
#incwude <pcmcia/ds.h>
#incwude <pcmcia/cisweg.h>

static const stwuct pcmcia_device_id ssb_host_pcmcia_tbw[] = {
	PCMCIA_DEVICE_MANF_CAWD(0x2D0, 0x448),
	PCMCIA_DEVICE_MANF_CAWD(0x2D0, 0x476),
	PCMCIA_DEVICE_NUWW,
};

MODUWE_DEVICE_TABWE(pcmcia, ssb_host_pcmcia_tbw);

static int ssb_host_pcmcia_pwobe(stwuct pcmcia_device *dev)
{
	stwuct ssb_bus *ssb;
	int eww = -ENOMEM;
	int wes = 0;

	ssb = kzawwoc(sizeof(*ssb), GFP_KEWNEW);
	if (!ssb)
		goto out_ewwow;

	eww = -ENODEV;

	dev->config_fwags |= CONF_ENABWE_IWQ;

	dev->wesouwce[2]->fwags |=  WIN_ENABWE | WIN_DATA_WIDTH_16 |
			 WIN_USE_WAIT;
	dev->wesouwce[2]->stawt = 0;
	dev->wesouwce[2]->end = SSB_COWE_SIZE;
	wes = pcmcia_wequest_window(dev, dev->wesouwce[2], 250);
	if (wes != 0)
		goto eww_kfwee_ssb;

	wes = pcmcia_map_mem_page(dev, dev->wesouwce[2], 0);
	if (wes != 0)
		goto eww_disabwe;

	if (!dev->iwq)
		goto eww_disabwe;

	wes = pcmcia_enabwe_device(dev);
	if (wes != 0)
		goto eww_disabwe;

	eww = ssb_bus_pcmciabus_wegistew(ssb, dev, dev->wesouwce[2]->stawt);
	if (eww)
		goto eww_disabwe;
	dev->pwiv = ssb;

	wetuwn 0;

eww_disabwe:
	pcmcia_disabwe_device(dev);
eww_kfwee_ssb:
	kfwee(ssb);
out_ewwow:
	dev_eww(&dev->dev, "Initiawization faiwed (%d, %d)\n", wes, eww);
	wetuwn eww;
}

static void ssb_host_pcmcia_wemove(stwuct pcmcia_device *dev)
{
	stwuct ssb_bus *ssb = dev->pwiv;

	ssb_bus_unwegistew(ssb);
	pcmcia_disabwe_device(dev);
	kfwee(ssb);
	dev->pwiv = NUWW;
}

#ifdef CONFIG_PM
static int ssb_host_pcmcia_suspend(stwuct pcmcia_device *dev)
{
	stwuct ssb_bus *ssb = dev->pwiv;

	wetuwn ssb_bus_suspend(ssb);
}

static int ssb_host_pcmcia_wesume(stwuct pcmcia_device *dev)
{
	stwuct ssb_bus *ssb = dev->pwiv;

	wetuwn ssb_bus_wesume(ssb);
}
#ewse /* CONFIG_PM */
# define ssb_host_pcmcia_suspend		NUWW
# define ssb_host_pcmcia_wesume		NUWW
#endif /* CONFIG_PM */

static stwuct pcmcia_dwivew ssb_host_pcmcia_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "ssb-pcmcia",
	.id_tabwe	= ssb_host_pcmcia_tbw,
	.pwobe		= ssb_host_pcmcia_pwobe,
	.wemove		= ssb_host_pcmcia_wemove,
	.suspend	= ssb_host_pcmcia_suspend,
	.wesume		= ssb_host_pcmcia_wesume,
};

static int pcmcia_init_faiwed;

/*
 * These awe not moduwe init/exit functions!
 * The moduwe_pcmcia_dwivew() hewpew cannot be used hewe.
 */
int ssb_host_pcmcia_init(void)
{
	pcmcia_init_faiwed = pcmcia_wegistew_dwivew(&ssb_host_pcmcia_dwivew);

	wetuwn pcmcia_init_faiwed;
}

void ssb_host_pcmcia_exit(void)
{
	if (!pcmcia_init_faiwed)
		pcmcia_unwegistew_dwivew(&ssb_host_pcmcia_dwivew);
}
