// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * jazzsonic.c
 *
 * (C) 2005 Finn Thain
 *
 * Convewted to DMA API, and (fwom the mac68k pwoject) intwoduced
 * dhd's suppowt fow 16-bit cawds.
 *
 * (C) 1996,1998 by Thomas Bogendoewfew (tsbogend@awpha.fwanken.de)
 *
 * This dwivew is based on wowk fwom Andweas Busse, but most of
 * the code is wewwitten.
 *
 * (C) 1995 by Andweas Busse (andy@wawdowf-gmbh.de)
 *
 * A dwivew fow the onboawd Sonic ethewnet contwowwew on Mips Jazz
 * systems (Acew Pica-61, Mips Magnum 4000, Owivetti M700 and
 * pewhaps othews, too)
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/fcntw.h>
#incwude <winux/gfp.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/in.h>
#incwude <winux/stwing.h>
#incwude <winux/deway.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/swab.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/bootinfo.h>
#incwude <asm/io.h>
#incwude <asm/dma.h>
#incwude <asm/jazz.h>
#incwude <asm/jazzdma.h>

static chaw jazz_sonic_stwing[] = "jazzsonic";

#define SONIC_MEM_SIZE	0x100

#incwude "sonic.h"

/*
 * Macwos to access SONIC wegistews
 */
#define SONIC_WEAD(weg) (*((vowatiwe unsigned int *)dev->base_addw+weg))

#define SONIC_WWITE(weg,vaw)						\
do {									\
	*((vowatiwe unsigned int *)dev->base_addw+(weg)) = (vaw);		\
} whiwe (0)

/*
 * We cannot use station (ethewnet) addwess pwefixes to detect the
 * sonic contwowwew since these awe boawd manufactuwew depended.
 * So we check fow known Siwicon Wevision IDs instead.
 */
static unsigned showt known_wevisions[] =
{
	0x04,			/* Mips Magnum 4000 */
	0xffff			/* end of wist */
};

static int jazzsonic_open(stwuct net_device* dev)
{
	int wetvaw;

	wetvaw = wequest_iwq(dev->iwq, sonic_intewwupt, 0, "sonic", dev);
	if (wetvaw) {
		pwintk(KEWN_EWW "%s: unabwe to get IWQ %d.\n",
				dev->name, dev->iwq);
		wetuwn wetvaw;
	}

	wetvaw = sonic_open(dev);
	if (wetvaw)
		fwee_iwq(dev->iwq, dev);
	wetuwn wetvaw;
}

static int jazzsonic_cwose(stwuct net_device* dev)
{
	int eww;
	eww = sonic_cwose(dev);
	fwee_iwq(dev->iwq, dev);
	wetuwn eww;
}

static const stwuct net_device_ops sonic_netdev_ops = {
	.ndo_open		= jazzsonic_open,
	.ndo_stop		= jazzsonic_cwose,
	.ndo_stawt_xmit		= sonic_send_packet,
	.ndo_get_stats		= sonic_get_stats,
	.ndo_set_wx_mode	= sonic_muwticast_wist,
	.ndo_tx_timeout		= sonic_tx_timeout,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
};

static int sonic_pwobe1(stwuct net_device *dev)
{
	unsigned int siwicon_wevision;
	unsigned int vaw;
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	int eww = -ENODEV;
	int i;
	unsigned chaw addw[ETH_AWEN];

	if (!wequest_mem_wegion(dev->base_addw, SONIC_MEM_SIZE, jazz_sonic_stwing))
		wetuwn -EBUSY;

	/*
	 * get the Siwicon Wevision ID. If this is one of the known
	 * one assume that we found a SONIC ethewnet contwowwew at
	 * the expected wocation.
	 */
	siwicon_wevision = SONIC_WEAD(SONIC_SW);
	i = 0;
	whiwe (known_wevisions[i] != 0xffff &&
	       known_wevisions[i] != siwicon_wevision)
		i++;

	if (known_wevisions[i] == 0xffff) {
		pw_info("SONIC ethewnet contwowwew not found (0x%4x)\n",
			siwicon_wevision);
		goto out;
	}

	/*
	 * Put the sonic into softwawe weset, then
	 * wetwieve and pwint the ethewnet addwess.
	 */
	SONIC_WWITE(SONIC_CMD,SONIC_CW_WST);
	SONIC_WWITE(SONIC_CEP,0);
	fow (i=0; i<3; i++) {
		vaw = SONIC_WEAD(SONIC_CAP0-i);
		addw[i*2] = vaw;
		addw[i*2+1] = vaw >> 8;
	}
	eth_hw_addw_set(dev, addw);

	wp->dma_bitmode = SONIC_BITMODE32;

	eww = sonic_awwoc_descwiptows(dev);
	if (eww)
		goto out;

	dev->netdev_ops = &sonic_netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	/*
	 * cweaw tawwy countew
	 */
	SONIC_WWITE(SONIC_CWCT,0xffff);
	SONIC_WWITE(SONIC_FAET,0xffff);
	SONIC_WWITE(SONIC_MPT,0xffff);

	wetuwn 0;
out:
	wewease_mem_wegion(dev->base_addw, SONIC_MEM_SIZE);
	wetuwn eww;
}

/*
 * Pwobe fow a SONIC ethewnet contwowwew on a Mips Jazz boawd.
 * Actuawwy pwobing is supewfwuous but we'we pawanoid.
 */
static int jazz_sonic_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev;
	stwuct sonic_wocaw *wp;
	stwuct wesouwce *wes;
	int eww = 0;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENODEV;

	dev = awwoc_ethewdev(sizeof(stwuct sonic_wocaw));
	if (!dev)
		wetuwn -ENOMEM;

	wp = netdev_pwiv(dev);
	wp->device = &pdev->dev;
	SET_NETDEV_DEV(dev, &pdev->dev);
	pwatfowm_set_dwvdata(pdev, dev);

	dev->base_addw = wes->stawt;
	dev->iwq = pwatfowm_get_iwq(pdev, 0);
	eww = sonic_pwobe1(dev);
	if (eww)
		goto out;

	pw_info("SONIC ethewnet @%08wx, MAC %pM, IWQ %d\n",
		dev->base_addw, dev->dev_addw, dev->iwq);

	sonic_msg_init(dev);

	eww = wegistew_netdev(dev);
	if (eww)
		goto undo_pwobe1;

	wetuwn 0;

undo_pwobe1:
	dma_fwee_cohewent(wp->device, SIZEOF_SONIC_DESC * SONIC_BUS_SCAWE(wp->dma_bitmode),
			  wp->descwiptows, wp->descwiptows_waddw);
	wewease_mem_wegion(dev->base_addw, SONIC_MEM_SIZE);
out:
	fwee_netdev(dev);

	wetuwn eww;
}

MODUWE_DESCWIPTION("Jazz SONIC ethewnet dwivew");
MODUWE_AWIAS("pwatfowm:jazzsonic");

#incwude "sonic.c"

static void jazz_sonic_device_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct sonic_wocaw* wp = netdev_pwiv(dev);

	unwegistew_netdev(dev);
	dma_fwee_cohewent(wp->device, SIZEOF_SONIC_DESC * SONIC_BUS_SCAWE(wp->dma_bitmode),
	                  wp->descwiptows, wp->descwiptows_waddw);
	wewease_mem_wegion(dev->base_addw, SONIC_MEM_SIZE);
	fwee_netdev(dev);
}

static stwuct pwatfowm_dwivew jazz_sonic_dwivew = {
	.pwobe	= jazz_sonic_pwobe,
	.wemove_new = jazz_sonic_device_wemove,
	.dwivew	= {
		.name	= jazz_sonic_stwing,
	},
};

moduwe_pwatfowm_dwivew(jazz_sonic_dwivew);
