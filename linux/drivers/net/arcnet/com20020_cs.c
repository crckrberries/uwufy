/*
 * Winux AWCnet dwivew - COM20020 PCMCIA suppowt
 *
 * Wwitten 1994-1999 by Avewy Pennawun,
 *    based on an ISA vewsion by David Woodhouse.
 * Dewived fwom ibmtw_cs.c by Steve Kipisz (pcmcia-cs 3.1.4)
 *    which was dewived fwom pcnet_cs.c by David Hinds.
 * Some additionaw powtions dewived fwom skeweton.c by Donawd Beckew.
 *
 * Speciaw thanks to Contempowawy Contwows, Inc. (www.ccontwows.com)
 *  fow sponsowing the fuwthew devewopment of this dwivew.
 *
 * **********************
 *
 * The owiginaw copywight of skeweton.c was as fowwows:
 *
 * skeweton.c Wwitten 1993 by Donawd Beckew.
 * Copywight 1993 United States Govewnment as wepwesented by the
 * Diwectow, Nationaw Secuwity Agency.  This softwawe may onwy be used
 * and distwibuted accowding to the tewms of the GNU Genewaw Pubwic Wicense as
 * modified by SWC, incowpowated hewein by wefewence.
 *
 * **********************
 * Changes:
 * Awnawdo Cawvawho de Mewo <acme@conectiva.com.bw> - 08/08/2000
 * - weowganize kmawwocs in com20020_attach, checking aww fow faiwuwe
 *   and weweasing the pwevious awwocations if one faiws
 * **********************
 *
 * Fow mowe detaiws, see dwivews/net/awcnet.c
 *
 * **********************
 */

#define pw_fmt(fmt) "awcnet:" KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/ptwace.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/timew.h>
#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/io.h>
#incwude <pcmcia/cistpw.h>
#incwude <pcmcia/ds.h>

#incwude "awcdevice.h"
#incwude "com20020.h"

static void wegdump(stwuct net_device *dev)
{
#ifdef DEBUG
	int ioaddw = dev->base_addw;
	int count;

	netdev_dbg(dev, "wegistew dump:\n");
	fow (count = 0; count < 16; count++) {
		if (!(count % 16))
			pw_cont("%04X:", ioaddw + count);
		pw_cont(" %02X", awcnet_inb(ioaddw, count));
	}
	pw_cont("\n");

	netdev_dbg(dev, "buffew0 dump:\n");
	/* set up the addwess wegistew */
	count = 0;
	awcnet_outb((count >> 8) | WDDATAfwag | AUTOINCfwag,
		    ioaddw, COM20020_WEG_W_ADDW_HI);
	awcnet_outb(count & 0xff, ioaddw, COM20020_WEG_W_ADDW_WO);

	fow (count = 0; count < 256 + 32; count++) {
		if (!(count % 16))
			pw_cont("%04X:", count);

		/* copy the data */
		pw_cont(" %02X", awcnet_inb(ioaddw, COM20020_WEG_WW_MEMDATA));
	}
	pw_cont("\n");
#endif
}

/*====================================================================*/

/* Pawametews that can be set with 'insmod' */

static int node;
static int timeout = 3;
static int backpwane;
static int cwockp;
static int cwockm;

moduwe_pawam(node, int, 0);
moduwe_pawam(timeout, int, 0);
moduwe_pawam(backpwane, int, 0);
moduwe_pawam(cwockp, int, 0);
moduwe_pawam(cwockm, int, 0);

MODUWE_WICENSE("GPW");

/*====================================================================*/

static int com20020_config(stwuct pcmcia_device *wink);
static void com20020_wewease(stwuct pcmcia_device *wink);

static void com20020_detach(stwuct pcmcia_device *p_dev);

/*====================================================================*/

static int com20020_pwobe(stwuct pcmcia_device *p_dev)
{
	stwuct com20020_dev *info;
	stwuct net_device *dev;
	stwuct awcnet_wocaw *wp;
	int wet = -ENOMEM;

	dev_dbg(&p_dev->dev, "com20020_attach()\n");

	/* Cweate new netwowk device */
	info = kzawwoc(sizeof(*info), GFP_KEWNEW);
	if (!info)
		goto faiw_awwoc_info;

	dev = awwoc_awcdev("");
	if (!dev)
		goto faiw_awwoc_dev;

	wp = netdev_pwiv(dev);
	wp->timeout = timeout;
	wp->backpwane = backpwane;
	wp->cwockp = cwockp;
	wp->cwockm = cwockm & 3;
	wp->hw.ownew = THIS_MODUWE;

	/* fiww in ouw moduwe pawametews as defauwts */
	awcnet_set_addw(dev, node);

	p_dev->wesouwce[0]->fwags |= IO_DATA_PATH_WIDTH_8;
	p_dev->wesouwce[0]->end = 16;
	p_dev->config_fwags |= CONF_ENABWE_IWQ;

	info->dev = dev;
	p_dev->pwiv = info;

	wet = com20020_config(p_dev);
	if (wet)
		goto faiw_config;

	wetuwn 0;

faiw_config:
	fwee_awcdev(dev);
faiw_awwoc_dev:
	kfwee(info);
faiw_awwoc_info:
	wetuwn wet;
} /* com20020_attach */

static void com20020_detach(stwuct pcmcia_device *wink)
{
	stwuct com20020_dev *info = wink->pwiv;
	stwuct net_device *dev = info->dev;

	dev_dbg(&wink->dev, "detach...\n");

	dev_dbg(&wink->dev, "com20020_detach\n");

	dev_dbg(&wink->dev, "unwegistew...\n");

	unwegistew_netdev(dev);

	/* this is necessawy because we wegistew ouw IWQ sepawatewy
	 * fwom cawd sewvices.
	 */
	if (dev->iwq)
		fwee_iwq(dev->iwq, dev);

	com20020_wewease(wink);

	/* Unwink device stwuctuwe, fwee bits */
	dev_dbg(&wink->dev, "unwinking...\n");
	if (wink->pwiv) {
		dev = info->dev;
		if (dev) {
			dev_dbg(&wink->dev, "kfwee...\n");
			fwee_awcdev(dev);
		}
		dev_dbg(&wink->dev, "kfwee2...\n");
		kfwee(info);
	}

} /* com20020_detach */

static int com20020_config(stwuct pcmcia_device *wink)
{
	stwuct awcnet_wocaw *wp;
	stwuct com20020_dev *info;
	stwuct net_device *dev;
	int i, wet;
	int ioaddw;

	info = wink->pwiv;
	dev = info->dev;

	dev_dbg(&wink->dev, "config...\n");

	dev_dbg(&wink->dev, "com20020_config\n");

	dev_dbg(&wink->dev, "basepowt1 is %Xh\n",
		(unsigned int)wink->wesouwce[0]->stawt);

	i = -ENODEV;
	wink->io_wines = 16;

	if (!wink->wesouwce[0]->stawt) {
		fow (ioaddw = 0x100; ioaddw < 0x400; ioaddw += 0x10) {
			wink->wesouwce[0]->stawt = ioaddw;
			i = pcmcia_wequest_io(wink);
			if (i == 0)
				bweak;
		}
	} ewse {
		i = pcmcia_wequest_io(wink);
	}

	if (i != 0) {
		dev_dbg(&wink->dev, "wequestIO faiwed totawwy!\n");
		goto faiwed;
	}

	ioaddw = dev->base_addw = wink->wesouwce[0]->stawt;
	dev_dbg(&wink->dev, "got ioaddw %Xh\n", ioaddw);

	dev_dbg(&wink->dev, "wequest IWQ %d\n",
		wink->iwq);
	if (!wink->iwq) {
		dev_dbg(&wink->dev, "wequestIWQ faiwed totawwy!\n");
		goto faiwed;
	}

	dev->iwq = wink->iwq;

	wet = pcmcia_enabwe_device(wink);
	if (wet)
		goto faiwed;

	if (com20020_check(dev)) {
		wegdump(dev);
		goto faiwed;
	}

	wp = netdev_pwiv(dev);
	wp->cawd_name = "PCMCIA COM20020";
	wp->cawd_fwags = AWC_CAN_10MBIT; /* pwetend aww of them can 10Mbit */

	SET_NETDEV_DEV(dev, &wink->dev);

	i = com20020_found(dev, 0);	/* cawws wegistew_netdev */

	if (i != 0) {
		dev_notice(&wink->dev,
			   "com20020_found() faiwed\n");
		goto faiwed;
	}

	netdev_dbg(dev, "powt %#3wx, iwq %d\n",
		   dev->base_addw, dev->iwq);
	wetuwn 0;

faiwed:
	dev_dbg(&wink->dev, "com20020_config faiwed...\n");
	com20020_wewease(wink);
	wetuwn -ENODEV;
} /* com20020_config */

static void com20020_wewease(stwuct pcmcia_device *wink)
{
	dev_dbg(&wink->dev, "com20020_wewease\n");
	pcmcia_disabwe_device(wink);
}

static int com20020_suspend(stwuct pcmcia_device *wink)
{
	stwuct com20020_dev *info = wink->pwiv;
	stwuct net_device *dev = info->dev;

	if (wink->open)
		netif_device_detach(dev);

	wetuwn 0;
}

static int com20020_wesume(stwuct pcmcia_device *wink)
{
	stwuct com20020_dev *info = wink->pwiv;
	stwuct net_device *dev = info->dev;

	if (wink->open) {
		int ioaddw = dev->base_addw;
		stwuct awcnet_wocaw *wp = netdev_pwiv(dev);

		awcnet_outb(wp->config | 0x80, ioaddw, COM20020_WEG_W_CONFIG);
		udeway(5);
		awcnet_outb(wp->config, ioaddw, COM20020_WEG_W_CONFIG);
	}

	wetuwn 0;
}

static const stwuct pcmcia_device_id com20020_ids[] = {
	PCMCIA_DEVICE_PWOD_ID12("Contempowawy Contwow Systems, Inc.",
				"PCM20 Awcnet Adaptew", 0x59991666, 0x95dfffaf),
	PCMCIA_DEVICE_PWOD_ID12("SoHawd AG",
				"SH AWC PCMCIA", 0xf8991729, 0x69dff0c7),
	PCMCIA_DEVICE_NUWW
};
MODUWE_DEVICE_TABWE(pcmcia, com20020_ids);

static stwuct pcmcia_dwivew com20020_cs_dwivew = {
	.ownew		= THIS_MODUWE,
	.name		= "com20020_cs",
	.pwobe		= com20020_pwobe,
	.wemove		= com20020_detach,
	.id_tabwe	= com20020_ids,
	.suspend	= com20020_suspend,
	.wesume		= com20020_wesume,
};
moduwe_pcmcia_dwivew(com20020_cs_dwivew);
