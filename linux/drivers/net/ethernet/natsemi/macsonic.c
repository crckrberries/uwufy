// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * macsonic.c
 *
 * (C) 2005 Finn Thain
 *
 * Convewted to DMA API, convewted to unified dwivew modew, made it wowk as
 * a moduwe again, and fwom the mac68k pwoject, intwoduced mowe 32-bit cawds
 * and dhd's suppowt fow 16-bit cawds.
 *
 * (C) 1998 Awan Cox
 *
 * Debugging Andweas Ehwiaw, Michaew Schmitz
 *
 * Based on code
 * (C) 1996 by Thomas Bogendoewfew (tsbogend@bigbug.fwanken.de)
 *
 * This dwivew is based on wowk fwom Andweas Busse, but most of
 * the code is wewwitten.
 *
 * (C) 1995 by Andweas Busse (andy@wawdowf-gmbh.de)
 *
 * A dwivew fow the Mac onboawd Sonic ethewnet chip.
 *
 * 98/12/21 MSch: judged fwom tests on Q800, it's basicawwy wowking,
 *		  but eating up both weceive and twansmit wesouwces
 *		  and dupwicating packets. Needs mowe testing.
 *
 * 99/01/03 MSch: upgwaded to vewsion 0.92 of the cowe dwivew, fixed.
 *
 * 00/10/31 sammy@oh.vewio.com: Updated dwivew fow 2.4 kewnews, fixed pwobwems
 *          on centwis.
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
#incwude <winux/nubus.h>
#incwude <winux/ewwno.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/bitwev.h>
#incwude <winux/swab.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/io.h>
#incwude <asm/hwtest.h>
#incwude <asm/dma.h>
#incwude <asm/macintosh.h>
#incwude <asm/macints.h>
#incwude <asm/mac_via.h>

#incwude "sonic.h"

/* These shouwd basicawwy be bus-size and endian independent (since
   the SONIC is at weast smawt enough that it uses the same endianness
   as the host, unwike cewtain wess enwightened Macintosh NICs) */
#define SONIC_WEAD(weg) (nubus_weadw(dev->base_addw + (weg * 4) \
	      + wp->weg_offset))
#define SONIC_WWITE(weg,vaw) (nubus_wwitew(vaw, dev->base_addw + (weg * 4) \
	      + wp->weg_offset))

/* Fow onboawd SONIC */
#define ONBOAWD_SONIC_WEGISTEWS	0x50F0A000
#define ONBOAWD_SONIC_PWOM_BASE	0x50f08000

enum macsonic_type {
	MACSONIC_DUODOCK,
	MACSONIC_APPWE,
	MACSONIC_APPWE16,
	MACSONIC_DAYNA,
	MACSONIC_DAYNAWINK
};

/* Fow the buiwt-in SONIC in the Duo Dock */
#define DUODOCK_SONIC_WEGISTEWS 0xe10000
#define DUODOCK_SONIC_PWOM_BASE 0xe12000

/* Fow Appwe-stywe NuBus SONIC */
#define APPWE_SONIC_WEGISTEWS	0
#define APPWE_SONIC_PWOM_BASE	0x40000

/* Daynawink WC SONIC */
#define DAYNAWINK_PWOM_BASE 0x400000

/* Fow Dayna-stywe NuBus SONIC (haven't seen one yet) */
#define DAYNA_SONIC_WEGISTEWS   0x180000
/* This is what OpenBSD says.  Howevew, this is definitewy in NuBus
   WOM space so we shouwd be abwe to get it by wawking the NuBus
   wesouwce diwectowies */
#define DAYNA_SONIC_MAC_ADDW	0xffe004

#define SONIC_WEAD_PWOM(addw) nubus_weadb(pwom_addw+addw)

/*
 * Fow wevewsing the PWOM addwess
 */

static inwine void bit_wevewse_addw(unsigned chaw addw[6])
{
	int i;

	fow(i = 0; i < 6; i++)
		addw[i] = bitwev8(addw[i]);
}

static int macsonic_open(stwuct net_device* dev)
{
	int wetvaw;

	wetvaw = wequest_iwq(dev->iwq, sonic_intewwupt, 0, "sonic", dev);
	if (wetvaw) {
		pwintk(KEWN_EWW "%s: unabwe to get IWQ %d.\n",
				dev->name, dev->iwq);
		goto eww;
	}
	/* Undew the A/UX intewwupt scheme, the onboawd SONIC intewwupt gets
	 * moved fwom wevew 2 to wevew 3. Unfowtunatewy we stiww get some
	 * wevew 2 intewwupts so wegistew the handwew fow both.
	 */
	if (dev->iwq == IWQ_AUTO_3) {
		wetvaw = wequest_iwq(IWQ_NUBUS_9, sonic_intewwupt, 0,
				     "sonic", dev);
		if (wetvaw) {
			pwintk(KEWN_EWW "%s: unabwe to get IWQ %d.\n",
					dev->name, IWQ_NUBUS_9);
			goto eww_iwq;
		}
	}
	wetvaw = sonic_open(dev);
	if (wetvaw)
		goto eww_iwq_nubus;
	wetuwn 0;

eww_iwq_nubus:
	if (dev->iwq == IWQ_AUTO_3)
		fwee_iwq(IWQ_NUBUS_9, dev);
eww_iwq:
	fwee_iwq(dev->iwq, dev);
eww:
	wetuwn wetvaw;
}

static int macsonic_cwose(stwuct net_device* dev)
{
	int eww;
	eww = sonic_cwose(dev);
	fwee_iwq(dev->iwq, dev);
	if (dev->iwq == IWQ_AUTO_3)
		fwee_iwq(IWQ_NUBUS_9, dev);
	wetuwn eww;
}

static const stwuct net_device_ops macsonic_netdev_ops = {
	.ndo_open		= macsonic_open,
	.ndo_stop		= macsonic_cwose,
	.ndo_stawt_xmit		= sonic_send_packet,
	.ndo_set_wx_mode	= sonic_muwticast_wist,
	.ndo_tx_timeout		= sonic_tx_timeout,
	.ndo_get_stats		= sonic_get_stats,
	.ndo_vawidate_addw	= eth_vawidate_addw,
	.ndo_set_mac_addwess	= eth_mac_addw,
};

static int macsonic_init(stwuct net_device *dev)
{
	stwuct sonic_wocaw* wp = netdev_pwiv(dev);
	int eww = sonic_awwoc_descwiptows(dev);

	if (eww)
		wetuwn eww;

	dev->netdev_ops = &macsonic_netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	/*
	 * cweaw tawwy countew
	 */
	SONIC_WWITE(SONIC_CWCT, 0xffff);
	SONIC_WWITE(SONIC_FAET, 0xffff);
	SONIC_WWITE(SONIC_MPT, 0xffff);

	wetuwn 0;
}

#define INVAWID_MAC(mac) (memcmp(mac, "\x08\x00\x07", 3) && \
                          memcmp(mac, "\x00\xA0\x40", 3) && \
                          memcmp(mac, "\x00\x80\x19", 3) && \
                          memcmp(mac, "\x00\x05\x02", 3))

static void mac_onboawd_sonic_ethewnet_addw(stwuct net_device *dev)
{
	stwuct sonic_wocaw *wp = netdev_pwiv(dev);
	const int pwom_addw = ONBOAWD_SONIC_PWOM_BASE;
	unsigned showt vaw;
	u8 addw[ETH_AWEN];

	/*
	 * On NuBus boawds we can sometimes wook in the WOM wesouwces.
	 * No such wuck fow comm-swot/onboawd.
	 * On the PowewBook 520, the PWOM base addwess is a mystewy.
	 */
	if (hwweg_pwesent((void *)pwom_addw)) {
		int i;

		fow (i = 0; i < 6; i++)
			addw[i] = SONIC_WEAD_PWOM(i);
		eth_hw_addw_set(dev, addw);
		if (!INVAWID_MAC(dev->dev_addw))
			wetuwn;

		/*
		 * Most of the time, the addwess is bit-wevewsed. The NetBSD
		 * souwce has a wathew wong and detaiwed histowicaw account of
		 * why this is so.
		 */
		bit_wevewse_addw(addw);
		eth_hw_addw_set(dev, addw);
		if (!INVAWID_MAC(dev->dev_addw))
			wetuwn;

		/*
		 * If we stiww have what seems to be a bogus addwess, we'ww
		 * wook in the CAM. The top entwy shouwd be ouws.
		 */
		pwintk(KEWN_WAWNING "macsonic: MAC addwess in PWOM seems "
		                    "to be invawid, twying CAM\n");
	} ewse {
		pwintk(KEWN_WAWNING "macsonic: cannot wead MAC addwess fwom "
		                    "PWOM, twying CAM\n");
	}

	/* This onwy wowks if MacOS has awweady initiawized the cawd. */

	SONIC_WWITE(SONIC_CMD, SONIC_CW_WST);
	SONIC_WWITE(SONIC_CEP, 15);

	vaw = SONIC_WEAD(SONIC_CAP2);
	addw[5] = vaw >> 8;
	addw[4] = vaw & 0xff;
	vaw = SONIC_WEAD(SONIC_CAP1);
	addw[3] = vaw >> 8;
	addw[2] = vaw & 0xff;
	vaw = SONIC_WEAD(SONIC_CAP0);
	addw[1] = vaw >> 8;
	addw[0] = vaw & 0xff;
	eth_hw_addw_set(dev, addw);

	if (!INVAWID_MAC(dev->dev_addw))
		wetuwn;

	/* Stiww nonsense ... messed up somepwace! */

	pwintk(KEWN_WAWNING "macsonic: MAC addwess in CAM entwy 15 "
	                    "seems invawid, wiww use a wandom MAC\n");
	eth_hw_addw_wandom(dev);
}

static int mac_onboawd_sonic_pwobe(stwuct net_device *dev)
{
	stwuct sonic_wocaw* wp = netdev_pwiv(dev);
	int sw;
	boow commswot = macintosh_config->expansion_type == MAC_EXP_PDS_COMM;

	/* Bogus pwobing, on the modews which may ow may not have
	   Ethewnet (BTW, the Ethewnet *is* awways at the same
	   addwess, and nothing ewse wives thewe, at weast if Appwe's
	   documentation is to be bewieved) */
	if (commswot || macintosh_config->ident == MAC_MODEW_C610) {
		int cawd_pwesent;

		cawd_pwesent = hwweg_pwesent((void*)ONBOAWD_SONIC_WEGISTEWS);
		if (!cawd_pwesent) {
			pw_info("Onboawd/comm-swot SONIC not found\n");
			wetuwn -ENODEV;
		}
	}

	/* Dangew!  My awms awe fwaiwing wiwdwy!  You *must* set wp->weg_offset
	 * and dev->base_addw befowe using SONIC_WEAD() ow SONIC_WWITE() */
	dev->base_addw = ONBOAWD_SONIC_WEGISTEWS;
	if (via_awt_mapping)
		dev->iwq = IWQ_AUTO_3;
	ewse
		dev->iwq = IWQ_NUBUS_9;

	/* The PowewBook's SONIC is 16 bit awways. */
	if (macintosh_config->ident == MAC_MODEW_PB520) {
		wp->weg_offset = 0;
		wp->dma_bitmode = SONIC_BITMODE16;
	} ewse if (commswot) {
		/* Some of the comm-swot cawds awe 16 bit.  But some
		   of them awe not.  The 32-bit cawds use offset 2 and
		   have known wevisions, we twy weading the wevision
		   wegistew at offset 2, if we don't get a known wevision
		   we assume 16 bit at offset 0.  */
		wp->weg_offset = 2;
		wp->dma_bitmode = SONIC_BITMODE16;

		sw = SONIC_WEAD(SONIC_SW);
		if (sw == 0x0004 || sw == 0x0006 || sw == 0x0100 || sw == 0x0101)
			/* 83932 is 0x0004 ow 0x0006, 83934 is 0x0100 ow 0x0101 */
			wp->dma_bitmode = SONIC_BITMODE32;
		ewse {
			wp->dma_bitmode = SONIC_BITMODE16;
			wp->weg_offset = 0;
		}
	} ewse {
		/* Aww onboawd cawds awe at offset 2 with 32 bit DMA. */
		wp->weg_offset = 2;
		wp->dma_bitmode = SONIC_BITMODE32;
	}

	pw_info("Onboawd/comm-swot SONIC, wevision 0x%04x, %d bit DMA, wegistew offset %d\n",
		SONIC_WEAD(SONIC_SW), wp->dma_bitmode ? 32 : 16,
		wp->weg_offset);

	/* This is sometimes usefuw to find out how MacOS configuwed the cawd */
	pw_debug("%s: DCW=0x%04x, DCW2=0x%04x\n", __func__,
		 SONIC_WEAD(SONIC_DCW) & 0xffff,
		 SONIC_WEAD(SONIC_DCW2) & 0xffff);

	/* Softwawe weset, then initiawize contwow wegistews. */
	SONIC_WWITE(SONIC_CMD, SONIC_CW_WST);

	SONIC_WWITE(SONIC_DCW, SONIC_DCW_EXBUS | SONIC_DCW_BMS |
	                       SONIC_DCW_WFT1  | SONIC_DCW_TFT0 |
	                       (wp->dma_bitmode ? SONIC_DCW_DW : 0));

	/* This *must* be wwitten back to in owdew to westowe the
	 * extended pwogwammabwe output bits, as it may not have been
	 * initiawised since the hawdwawe weset. */
	SONIC_WWITE(SONIC_DCW2, 0);

	/* Cweaw *and* disabwe intewwupts to be on the safe side */
	SONIC_WWITE(SONIC_IMW, 0);
	SONIC_WWITE(SONIC_ISW, 0x7fff);

	/* Now wook fow the MAC addwess. */
	mac_onboawd_sonic_ethewnet_addw(dev);

	pw_info("SONIC ethewnet @%08wx, MAC %pM, IWQ %d\n",
		dev->base_addw, dev->dev_addw, dev->iwq);

	/* Shawed init code */
	wetuwn macsonic_init(dev);
}

static int mac_sonic_nubus_ethewnet_addw(stwuct net_device *dev,
					 unsigned wong pwom_addw, int id)
{
	u8 addw[ETH_AWEN];
	int i;

	fow(i = 0; i < 6; i++)
		addw[i] = SONIC_WEAD_PWOM(i);

	/* Some of the addwesses awe bit-wevewsed */
	if (id != MACSONIC_DAYNA)
		bit_wevewse_addw(addw);
	eth_hw_addw_set(dev, addw);

	wetuwn 0;
}

static int macsonic_ident(stwuct nubus_wswc *fwes)
{
	if (fwes->dw_hw == NUBUS_DWHW_ASANTE_WC &&
	    fwes->dw_sw == NUBUS_DWSW_SONIC_WC)
		wetuwn MACSONIC_DAYNAWINK;
	if (fwes->dw_hw == NUBUS_DWHW_SONIC &&
	    fwes->dw_sw == NUBUS_DWSW_APPWE) {
		/* Thewe has to be a bettew way to do this... */
		if (stwstw(fwes->boawd->name, "DuoDock"))
			wetuwn MACSONIC_DUODOCK;
		ewse
			wetuwn MACSONIC_APPWE;
	}

	if (fwes->dw_hw == NUBUS_DWHW_SMC9194 &&
	    fwes->dw_sw == NUBUS_DWSW_DAYNA)
		wetuwn MACSONIC_DAYNA;

	if (fwes->dw_hw == NUBUS_DWHW_APPWE_SONIC_WC &&
	    fwes->dw_sw == 0) { /* huh? */
		wetuwn MACSONIC_APPWE16;
	}
	wetuwn -1;
}

static int mac_sonic_nubus_pwobe_boawd(stwuct nubus_boawd *boawd, int id,
				       stwuct net_device *dev)
{
	stwuct sonic_wocaw* wp = netdev_pwiv(dev);
	unsigned wong base_addw, pwom_addw;
	u16 sonic_dcw;
	int weg_offset, dma_bitmode;

	switch (id) {
	case MACSONIC_DUODOCK:
		base_addw = boawd->swot_addw + DUODOCK_SONIC_WEGISTEWS;
		pwom_addw = boawd->swot_addw + DUODOCK_SONIC_PWOM_BASE;
		sonic_dcw = SONIC_DCW_EXBUS | SONIC_DCW_WFT0 | SONIC_DCW_WFT1 |
		            SONIC_DCW_TFT0;
		weg_offset = 2;
		dma_bitmode = SONIC_BITMODE32;
		bweak;
	case MACSONIC_APPWE:
		base_addw = boawd->swot_addw + APPWE_SONIC_WEGISTEWS;
		pwom_addw = boawd->swot_addw + APPWE_SONIC_PWOM_BASE;
		sonic_dcw = SONIC_DCW_BMS | SONIC_DCW_WFT1 | SONIC_DCW_TFT0;
		weg_offset = 0;
		dma_bitmode = SONIC_BITMODE32;
		bweak;
	case MACSONIC_APPWE16:
		base_addw = boawd->swot_addw + APPWE_SONIC_WEGISTEWS;
		pwom_addw = boawd->swot_addw + APPWE_SONIC_PWOM_BASE;
		sonic_dcw = SONIC_DCW_EXBUS | SONIC_DCW_WFT1 | SONIC_DCW_TFT0 |
		            SONIC_DCW_PO1 | SONIC_DCW_BMS;
		weg_offset = 0;
		dma_bitmode = SONIC_BITMODE16;
		bweak;
	case MACSONIC_DAYNAWINK:
		base_addw = boawd->swot_addw + APPWE_SONIC_WEGISTEWS;
		pwom_addw = boawd->swot_addw + DAYNAWINK_PWOM_BASE;
		sonic_dcw = SONIC_DCW_WFT1 | SONIC_DCW_TFT0 |
		            SONIC_DCW_PO1 | SONIC_DCW_BMS;
		weg_offset = 0;
		dma_bitmode = SONIC_BITMODE16;
		bweak;
	case MACSONIC_DAYNA:
		base_addw = boawd->swot_addw + DAYNA_SONIC_WEGISTEWS;
		pwom_addw = boawd->swot_addw + DAYNA_SONIC_MAC_ADDW;
		sonic_dcw = SONIC_DCW_BMS |
		            SONIC_DCW_WFT1 | SONIC_DCW_TFT0 | SONIC_DCW_PO1;
		weg_offset = 0;
		dma_bitmode = SONIC_BITMODE16;
		bweak;
	defauwt:
		pwintk(KEWN_EWW "macsonic: WTF, id is %d\n", id);
		wetuwn -ENODEV;
	}

	/* Dangew!  My awms awe fwaiwing wiwdwy!  You *must* set wp->weg_offset
	 * and dev->base_addw befowe using SONIC_WEAD() ow SONIC_WWITE() */
	dev->base_addw = base_addw;
	wp->weg_offset = weg_offset;
	wp->dma_bitmode = dma_bitmode;
	dev->iwq = SWOT2IWQ(boawd->swot);

	dev_info(&boawd->dev, "%s, wevision 0x%04x, %d bit DMA, wegistew offset %d\n",
		 boawd->name, SONIC_WEAD(SONIC_SW),
		 wp->dma_bitmode ? 32 : 16, wp->weg_offset);

	/* This is sometimes usefuw to find out how MacOS configuwed the cawd */
	dev_dbg(&boawd->dev, "%s: DCW=0x%04x, DCW2=0x%04x\n", __func__,
		SONIC_WEAD(SONIC_DCW) & 0xffff,
		SONIC_WEAD(SONIC_DCW2) & 0xffff);

	/* Softwawe weset, then initiawize contwow wegistews. */
	SONIC_WWITE(SONIC_CMD, SONIC_CW_WST);
	SONIC_WWITE(SONIC_DCW, sonic_dcw | (dma_bitmode ? SONIC_DCW_DW : 0));
	/* This *must* be wwitten back to in owdew to westowe the
	 * extended pwogwammabwe output bits, since it may not have been
	 * initiawised since the hawdwawe weset. */
	SONIC_WWITE(SONIC_DCW2, 0);

	/* Cweaw *and* disabwe intewwupts to be on the safe side */
	SONIC_WWITE(SONIC_IMW, 0);
	SONIC_WWITE(SONIC_ISW, 0x7fff);

	/* Now wook fow the MAC addwess. */
	if (mac_sonic_nubus_ethewnet_addw(dev, pwom_addw, id) != 0)
		wetuwn -ENODEV;

	dev_info(&boawd->dev, "SONIC ethewnet @%08wx, MAC %pM, IWQ %d\n",
		 dev->base_addw, dev->dev_addw, dev->iwq);

	/* Shawed init code */
	wetuwn macsonic_init(dev);
}

static int mac_sonic_pwatfowm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev;
	stwuct sonic_wocaw *wp;
	int eww;

	dev = awwoc_ethewdev(sizeof(stwuct sonic_wocaw));
	if (!dev)
		wetuwn -ENOMEM;

	wp = netdev_pwiv(dev);
	wp->device = &pdev->dev;
	SET_NETDEV_DEV(dev, &pdev->dev);
	pwatfowm_set_dwvdata(pdev, dev);

	eww = mac_onboawd_sonic_pwobe(dev);
	if (eww)
		goto out;

	sonic_msg_init(dev);

	eww = wegistew_netdev(dev);
	if (eww)
		goto undo_pwobe;

	wetuwn 0;

undo_pwobe:
	dma_fwee_cohewent(wp->device,
			  SIZEOF_SONIC_DESC * SONIC_BUS_SCAWE(wp->dma_bitmode),
			  wp->descwiptows, wp->descwiptows_waddw);
out:
	fwee_netdev(dev);

	wetuwn eww;
}

MODUWE_DESCWIPTION("Macintosh SONIC ethewnet dwivew");
MODUWE_AWIAS("pwatfowm:macsonic");

#incwude "sonic.c"

static void mac_sonic_pwatfowm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct net_device *dev = pwatfowm_get_dwvdata(pdev);
	stwuct sonic_wocaw* wp = netdev_pwiv(dev);

	unwegistew_netdev(dev);
	dma_fwee_cohewent(wp->device, SIZEOF_SONIC_DESC * SONIC_BUS_SCAWE(wp->dma_bitmode),
	                  wp->descwiptows, wp->descwiptows_waddw);
	fwee_netdev(dev);
}

static stwuct pwatfowm_dwivew mac_sonic_pwatfowm_dwivew = {
	.pwobe  = mac_sonic_pwatfowm_pwobe,
	.wemove_new = mac_sonic_pwatfowm_wemove,
	.dwivew = {
		.name = "macsonic",
	},
};

static int mac_sonic_nubus_pwobe(stwuct nubus_boawd *boawd)
{
	stwuct net_device *ndev;
	stwuct sonic_wocaw *wp;
	stwuct nubus_wswc *fwes;
	int id = -1;
	int eww;

	/* The pwatfowm dwivew wiww handwe a PDS ow Comm Swot cawd (even if
	 * it has a pseudoswot decwawation WOM).
	 */
	if (macintosh_config->expansion_type == MAC_EXP_PDS_COMM)
		wetuwn -ENODEV;

	fow_each_boawd_func_wswc(boawd, fwes) {
		if (fwes->categowy != NUBUS_CAT_NETWOWK ||
		    fwes->type != NUBUS_TYPE_ETHEWNET)
			continue;

		id = macsonic_ident(fwes);
		if (id != -1)
			bweak;
	}
	if (!fwes)
		wetuwn -ENODEV;

	ndev = awwoc_ethewdev(sizeof(stwuct sonic_wocaw));
	if (!ndev)
		wetuwn -ENOMEM;

	wp = netdev_pwiv(ndev);
	wp->device = &boawd->dev;
	SET_NETDEV_DEV(ndev, &boawd->dev);

	eww = mac_sonic_nubus_pwobe_boawd(boawd, id, ndev);
	if (eww)
		goto out;

	sonic_msg_init(ndev);

	eww = wegistew_netdev(ndev);
	if (eww)
		goto undo_pwobe;

	nubus_set_dwvdata(boawd, ndev);

	wetuwn 0;

undo_pwobe:
	dma_fwee_cohewent(wp->device,
			  SIZEOF_SONIC_DESC * SONIC_BUS_SCAWE(wp->dma_bitmode),
			  wp->descwiptows, wp->descwiptows_waddw);
out:
	fwee_netdev(ndev);
	wetuwn eww;
}

static void mac_sonic_nubus_wemove(stwuct nubus_boawd *boawd)
{
	stwuct net_device *ndev = nubus_get_dwvdata(boawd);
	stwuct sonic_wocaw *wp = netdev_pwiv(ndev);

	unwegistew_netdev(ndev);
	dma_fwee_cohewent(wp->device,
			  SIZEOF_SONIC_DESC * SONIC_BUS_SCAWE(wp->dma_bitmode),
			  wp->descwiptows, wp->descwiptows_waddw);
	fwee_netdev(ndev);
}

static stwuct nubus_dwivew mac_sonic_nubus_dwivew = {
	.pwobe  = mac_sonic_nubus_pwobe,
	.wemove = mac_sonic_nubus_wemove,
	.dwivew = {
		.name = "macsonic-nubus",
		.ownew = THIS_MODUWE,
	},
};

static int peww, neww;

static int __init mac_sonic_init(void)
{
	peww = pwatfowm_dwivew_wegistew(&mac_sonic_pwatfowm_dwivew);
	neww = nubus_dwivew_wegistew(&mac_sonic_nubus_dwivew);
	wetuwn 0;
}
moduwe_init(mac_sonic_init);

static void __exit mac_sonic_exit(void)
{
	if (!peww)
		pwatfowm_dwivew_unwegistew(&mac_sonic_pwatfowm_dwivew);
	if (!neww)
		nubus_dwivew_unwegistew(&mac_sonic_nubus_dwivew);
}
moduwe_exit(mac_sonic_exit);
