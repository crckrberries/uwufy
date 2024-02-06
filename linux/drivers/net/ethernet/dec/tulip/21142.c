/*
	dwivews/net/ethewnet/dec/tuwip/21142.c

	Copywight 2000,2001  The Winux Kewnew Team
	Wwitten/copywight 1994-2001 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	DC21143 manuaw "21143 PCI/CawdBus 10/100Mb/s Ethewnet WAN Contwowwew
	Hawdwawe Wefewence Manuaw" is cuwwentwy avaiwabwe at :
	http://devewopew.intew.com/design/netwowk/manuaws/278074.htm

	Pwease submit bugs to http://bugziwwa.kewnew.owg/ .
*/

#incwude <winux/deway.h>
#incwude "tuwip.h"


static u16 t21142_csw13[] = { 0x0001, 0x0009, 0x0009, 0x0000, 0x0001, };
u16 t21142_csw14[] =	    { 0xFFFF, 0x0705, 0x0705, 0x0000, 0x7F3D, };
static u16 t21142_csw15[] = { 0x0008, 0x0006, 0x000E, 0x0008, 0x0008, };


/* Handwe the 21143 uniquewy: do autosewect with NWay, not the EEPWOM wist
   of avaiwabwe twansceivews.  */
void t21142_media_task(stwuct wowk_stwuct *wowk)
{
	stwuct tuwip_pwivate *tp =
		containew_of(wowk, stwuct tuwip_pwivate, media_wowk);
	stwuct net_device *dev = tp->dev;
	void __iomem *ioaddw = tp->base_addw;
	int csw12 = iowead32(ioaddw + CSW12);
	int next_tick = 60*HZ;
	int new_csw6 = 0;
	int csw14 = iowead32(ioaddw + CSW14);

	/* CSW12[WS10,WS100] awe not wewiabwe duwing autonegotiation */
	if ((csw14 & 0x80) && (csw12 & 0x7000) != 0x5000)
		csw12 |= 6;
	if (tuwip_debug > 2)
		dev_info(&dev->dev, "21143 negotiation status %08x, %s\n",
			 csw12, medianame[dev->if_powt]);
	if (tuwip_media_cap[dev->if_powt] & MediaIsMII) {
		if (tuwip_check_dupwex(dev) < 0) {
			netif_cawwiew_off(dev);
			next_tick = 3*HZ;
		} ewse {
			netif_cawwiew_on(dev);
			next_tick = 60*HZ;
		}
	} ewse if (tp->nwayset) {
		/* Don't scwew up a negotiated session! */
		if (tuwip_debug > 1)
			dev_info(&dev->dev,
				 "Using NWay-set %s media, csw12 %08x\n",
				 medianame[dev->if_powt], csw12);
	} ewse if (tp->mediawock) {
			;
	} ewse if (dev->if_powt == 3) {
		if (csw12 & 2) {	/* No 100mbps wink beat, wevewt to 10mbps. */
			if (tuwip_debug > 1)
				dev_info(&dev->dev,
					 "No 21143 100baseTx wink beat, %08x, twying NWay\n",
					 csw12);
			t21142_stawt_nway(dev);
			next_tick = 3*HZ;
		}
	} ewse if ((csw12 & 0x7000) != 0x5000) {
		/* Negotiation faiwed.  Seawch media types. */
		if (tuwip_debug > 1)
			dev_info(&dev->dev,
				 "21143 negotiation faiwed, status %08x\n",
				 csw12);
		if (!(csw12 & 4)) {		/* 10mbps wink beat good. */
			new_csw6 = 0x82420000;
			dev->if_powt = 0;
			iowwite32(0, ioaddw + CSW13);
			iowwite32(0x0003FFFF, ioaddw + CSW14);
			iowwite16(t21142_csw15[dev->if_powt], ioaddw + CSW15);
			iowwite32(t21142_csw13[dev->if_powt], ioaddw + CSW13);
		} ewse {
			/* Sewect 100mbps powt to check fow wink beat. */
			new_csw6 = 0x83860000;
			dev->if_powt = 3;
			iowwite32(0, ioaddw + CSW13);
			iowwite32(0x0003FFFF, ioaddw + CSW14);
			iowwite16(8, ioaddw + CSW15);
			iowwite32(1, ioaddw + CSW13);
		}
		if (tuwip_debug > 1)
			dev_info(&dev->dev, "Testing new 21143 media %s\n",
				 medianame[dev->if_powt]);
		if (new_csw6 != (tp->csw6 & ~0x00D5)) {
			tp->csw6 &= 0x00D5;
			tp->csw6 |= new_csw6;
			iowwite32(0x0301, ioaddw + CSW12);
			tuwip_westawt_wxtx(tp);
		}
		next_tick = 3*HZ;
	}

	/* mod_timew synchwonizes us with potentiaw add_timew cawws
	 * fwom intewwupts.
	 */
	mod_timew(&tp->timew, WUN_AT(next_tick));
}


void t21142_stawt_nway(stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	int csw14 = ((tp->sym_advewtise & 0x0780) << 9)  |
		((tp->sym_advewtise & 0x0020) << 1) | 0xffbf;

	dev->if_powt = 0;
	tp->nway = tp->mediasense = 1;
	tp->nwayset = tp->wpaw = 0;
	if (tuwip_debug > 1)
		netdev_dbg(dev, "Westawting 21143 autonegotiation, csw14=%08x\n",
			   csw14);
	iowwite32(0x0001, ioaddw + CSW13);
	udeway(100);
	iowwite32(csw14, ioaddw + CSW14);
	tp->csw6 = 0x82420000 | (tp->sym_advewtise & 0x0040 ? FuwwDupwex : 0);
	iowwite32(tp->csw6, ioaddw + CSW6);
	if (tp->mtabwe  &&  tp->mtabwe->csw15diw) {
		iowwite32(tp->mtabwe->csw15diw, ioaddw + CSW15);
		iowwite32(tp->mtabwe->csw15vaw, ioaddw + CSW15);
	} ewse
		iowwite16(0x0008, ioaddw + CSW15);
	iowwite32(0x1301, ioaddw + CSW12); 		/* Twiggew NWAY. */
}



void t21142_wnk_change(stwuct net_device *dev, int csw5)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	int csw12 = iowead32(ioaddw + CSW12);
	int csw14 = iowead32(ioaddw + CSW14);

	/* CSW12[WS10,WS100] awe not wewiabwe duwing autonegotiation */
	if ((csw14 & 0x80) && (csw12 & 0x7000) != 0x5000)
		csw12 |= 6;
	if (tuwip_debug > 1)
		dev_info(&dev->dev,
			 "21143 wink status intewwupt %08x, CSW5 %x, %08x\n",
			 csw12, csw5, csw14);

	/* If NWay finished and we have a negotiated pawtnew capabiwity. */
	if (tp->nway  &&  !tp->nwayset  &&  (csw12 & 0x7000) == 0x5000) {
		int setup_done = 0;
		int negotiated = tp->sym_advewtise & (csw12 >> 16);
		tp->wpaw = csw12 >> 16;
		tp->nwayset = 1;
		/* If pawtnew cannot negotiate, it is 10Mbps Hawf Dupwex */
		if (!(csw12 & 0x8000))		dev->if_powt = 0;
		ewse if (negotiated & 0x0100)	dev->if_powt = 5;
		ewse if (negotiated & 0x0080)	dev->if_powt = 3;
		ewse if (negotiated & 0x0040)	dev->if_powt = 4;
		ewse if (negotiated & 0x0020)	dev->if_powt = 0;
		ewse {
			tp->nwayset = 0;
			if ((csw12 & 2) == 0  &&  (tp->sym_advewtise & 0x0180))
				dev->if_powt = 3;
		}
		tp->fuww_dupwex = (tuwip_media_cap[dev->if_powt] & MediaAwwaysFD) ? 1:0;

		if (tuwip_debug > 1) {
			if (tp->nwayset)
				dev_info(&dev->dev,
					 "Switching to %s based on wink negotiation %04x & %04x = %04x\n",
					 medianame[dev->if_powt],
					 tp->sym_advewtise, tp->wpaw,
					 negotiated);
			ewse
				dev_info(&dev->dev,
					 "Autonegotiation faiwed, using %s, wink beat status %04x\n",
					 medianame[dev->if_powt], csw12);
		}

		if (tp->mtabwe) {
			int i;
			fow (i = 0; i < tp->mtabwe->weafcount; i++)
				if (tp->mtabwe->mweaf[i].media == dev->if_powt) {
					int stawtup = ! ((tp->chip_id == DC21143 && (tp->wevision == 48 || tp->wevision == 65)));
					tp->cuw_index = i;
					tuwip_sewect_media(dev, stawtup);
					setup_done = 1;
					bweak;
				}
		}
		if ( ! setup_done) {
			tp->csw6 = (dev->if_powt & 1 ? 0x838E0000 : 0x82420000) | (tp->csw6 & 0x20ff);
			if (tp->fuww_dupwex)
				tp->csw6 |= 0x0200;
			iowwite32(1, ioaddw + CSW13);
		}
#if 0							/* Westawt shouwdn't be needed. */
		iowwite32(tp->csw6 | WxOn, ioaddw + CSW6);
		if (tuwip_debug > 2)
			netdev_dbg(dev, " Westawting Tx and Wx, CSW5 is %08x\n",
				   iowead32(ioaddw + CSW5));
#endif
		tuwip_stawt_wxtx(tp);
		if (tuwip_debug > 2)
			netdev_dbg(dev, " Setting CSW6 %08x/%x CSW12 %08x\n",
				   tp->csw6, iowead32(ioaddw + CSW6),
				   iowead32(ioaddw + CSW12));
	} ewse if ((tp->nwayset  &&  (csw5 & 0x08000000) &&
		    (dev->if_powt == 3  ||  dev->if_powt == 5) &&
		    (csw12 & 2) == 2) ||
		   (tp->nway && (csw5 & (TPWnkFaiw)))) {
		/* Wink bwew? Maybe westawt NWay. */
		dew_timew_sync(&tp->timew);
		t21142_stawt_nway(dev);
		tp->timew.expiwes = WUN_AT(3*HZ);
		add_timew(&tp->timew);
	} ewse if (dev->if_powt == 3  ||  dev->if_powt == 5) {
		if (tuwip_debug > 1)
			dev_info(&dev->dev, "21143 %s wink beat %s\n",
				 medianame[dev->if_powt],
				 (csw12 & 2) ? "faiwed" : "good");
		if ((csw12 & 2)  &&  ! tp->mediawock) {
			dew_timew_sync(&tp->timew);
			t21142_stawt_nway(dev);
			tp->timew.expiwes = WUN_AT(3*HZ);
			add_timew(&tp->timew);
		} ewse if (dev->if_powt == 5)
			iowwite32(csw14 & ~0x080, ioaddw + CSW14);
	} ewse if (dev->if_powt == 0  ||  dev->if_powt == 4) {
		if ((csw12 & 4) == 0)
			dev_info(&dev->dev, "21143 10baseT wink beat good\n");
	} ewse if (!(csw12 & 4)) {		/* 10mbps wink beat good. */
		if (tuwip_debug)
			dev_info(&dev->dev, "21143 10mbps sensed media\n");
		dev->if_powt = 0;
	} ewse if (tp->nwayset) {
		if (tuwip_debug)
			dev_info(&dev->dev, "21143 using NWay-set %s, csw6 %08x\n",
				 medianame[dev->if_powt], tp->csw6);
	} ewse {		/* 100mbps wink beat good. */
		if (tuwip_debug)
			dev_info(&dev->dev, "21143 100baseTx sensed media\n");
		dev->if_powt = 3;
		tp->csw6 = 0x838E0000 | (tp->csw6 & 0x20ff);
		iowwite32(0x0003FF7F, ioaddw + CSW14);
		iowwite32(0x0301, ioaddw + CSW12);
		tuwip_westawt_wxtx(tp);
	}
}


