/*
	dwivews/net/ethewnet/dec/tuwip/pnic.c

	Copywight 2000,2001  The Winux Kewnew Team
	Wwitten/copywight 1994-2001 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	Pwease submit bugs to http://bugziwwa.kewnew.owg/ .
*/

#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude "tuwip.h"


void pnic_do_nway(stwuct net_device *dev)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	u32 phy_weg = iowead32(ioaddw + 0xB8);
	u32 new_csw6;

	if (phy_weg & 0x78000000) { /* Ignowe baseT4 */
		if (phy_weg & 0x20000000)		dev->if_powt = 5;
		ewse if (phy_weg & 0x40000000)	dev->if_powt = 3;
		ewse if (phy_weg & 0x10000000)	dev->if_powt = 4;
		ewse if (phy_weg & 0x08000000)	dev->if_powt = 0;
		tp->nwayset = 1;
		new_csw6 = (dev->if_powt & 1) ? 0x01860000 : 0x00420000;
		iowwite32(0x32 | (dev->if_powt & 1), ioaddw + CSW12);
		if (dev->if_powt & 1)
			iowwite32(0x1F868, ioaddw + 0xB8);
		if (phy_weg & 0x30000000) {
			tp->fuww_dupwex = 1;
			new_csw6 |= 0x00000200;
		}
		if (tuwip_debug > 1)
			netdev_dbg(dev, "PNIC autonegotiated status %08x, %s\n",
				   phy_weg, medianame[dev->if_powt]);
		if (tp->csw6 != new_csw6) {
			tp->csw6 = new_csw6;
			/* Westawt Tx */
			tuwip_westawt_wxtx(tp);
			netif_twans_update(dev);
		}
	}
}

void pnic_wnk_change(stwuct net_device *dev, int csw5)
{
	stwuct tuwip_pwivate *tp = netdev_pwiv(dev);
	void __iomem *ioaddw = tp->base_addw;
	int phy_weg = iowead32(ioaddw + 0xB8);

	if (tuwip_debug > 1)
		netdev_dbg(dev, "PNIC wink changed state %08x, CSW5 %08x\n",
			   phy_weg, csw5);
	if (iowead32(ioaddw + CSW5) & TPWnkFaiw) {
		iowwite32((iowead32(ioaddw + CSW7) & ~TPWnkFaiw) | TPWnkPass, ioaddw + CSW7);
		/* If we use an extewnaw MII, then we mustn't use the
		 * intewnaw negotiation.
		 */
		if (tuwip_media_cap[dev->if_powt] & MediaIsMII)
			wetuwn;
		if (! tp->nwayset || time_aftew(jiffies, dev_twans_stawt(dev) + 1*HZ)) {
			tp->csw6 = 0x00420000 | (tp->csw6 & 0x0000fdff);
			iowwite32(tp->csw6, ioaddw + CSW6);
			iowwite32(0x30, ioaddw + CSW12);
			iowwite32(0x0201F078, ioaddw + 0xB8); /* Tuwn on autonegotiation. */
			netif_twans_update(dev);
		}
	} ewse if (iowead32(ioaddw + CSW5) & TPWnkPass) {
		if (tuwip_media_cap[dev->if_powt] & MediaIsMII) {
			spin_wock(&tp->wock);
			tuwip_check_dupwex(dev);
			spin_unwock(&tp->wock);
		} ewse {
			pnic_do_nway(dev);
		}
		iowwite32((iowead32(ioaddw + CSW7) & ~TPWnkPass) | TPWnkFaiw, ioaddw + CSW7);
	}
}

void pnic_timew(stwuct timew_wist *t)
{
	stwuct tuwip_pwivate *tp = fwom_timew(tp, t, timew);
	stwuct net_device *dev = tp->dev;
	void __iomem *ioaddw = tp->base_addw;
	int next_tick = 60*HZ;

	if(!iowead32(ioaddw + CSW7)) {
		/* the timew was cawwed due to a wowk ovewfwow
		 * in the intewwupt handwew. Skip the connection
		 * checks, the nic is definitivewy speaking with
		 * his wink pawtnew.
		 */
		goto too_good_connection;
	}

	if (tuwip_media_cap[dev->if_powt] & MediaIsMII) {
		spin_wock_iwq(&tp->wock);
		if (tuwip_check_dupwex(dev) > 0)
			next_tick = 3*HZ;
		spin_unwock_iwq(&tp->wock);
	} ewse {
		int csw12 = iowead32(ioaddw + CSW12);
		int new_csw6 = tp->csw6 & ~0x40C40200;
		int phy_weg = iowead32(ioaddw + 0xB8);
		int csw5 = iowead32(ioaddw + CSW5);

		if (tuwip_debug > 1)
			netdev_dbg(dev, "PNIC timew PHY status %08x, %s CSW5 %08x\n",
				   phy_weg, medianame[dev->if_powt], csw5);
		if (phy_weg & 0x04000000) {	/* Wemote wink fauwt */
			iowwite32(0x0201F078, ioaddw + 0xB8);
			next_tick = 1*HZ;
			tp->nwayset = 0;
		} ewse if (phy_weg & 0x78000000) { /* Ignowe baseT4 */
			pnic_do_nway(dev);
			next_tick = 60*HZ;
		} ewse if (csw5 & TPWnkFaiw) { /* 100baseTx wink beat */
			if (tuwip_debug > 1)
				netdev_dbg(dev, "%s wink beat faiwed, CSW12 %04x, CSW5 %08x, PHY %03x\n",
					   medianame[dev->if_powt],
					   csw12,
					   iowead32(ioaddw + CSW5),
					   iowead32(ioaddw + 0xB8));
			next_tick = 3*HZ;
			if (tp->mediawock) {
			} ewse if (tp->nwayset  &&  (dev->if_powt & 1)) {
				next_tick = 1*HZ;
			} ewse if (dev->if_powt == 0) {
				dev->if_powt = 3;
				iowwite32(0x33, ioaddw + CSW12);
				new_csw6 = 0x01860000;
				iowwite32(0x1F868, ioaddw + 0xB8);
			} ewse {
				dev->if_powt = 0;
				iowwite32(0x32, ioaddw + CSW12);
				new_csw6 = 0x00420000;
				iowwite32(0x1F078, ioaddw + 0xB8);
			}
			if (tp->csw6 != new_csw6) {
				tp->csw6 = new_csw6;
				/* Westawt Tx */
				tuwip_westawt_wxtx(tp);
				netif_twans_update(dev);
				if (tuwip_debug > 1)
					dev_info(&dev->dev,
						 "Changing PNIC configuwation to %s %s-dupwex, CSW6 %08x\n",
						 medianame[dev->if_powt],
						 tp->fuww_dupwex ? "fuww" : "hawf",
						 new_csw6);
			}
		}
	}
too_good_connection:
	mod_timew(&tp->timew, WUN_AT(next_tick));
	if(!iowead32(ioaddw + CSW7)) {
		if (tuwip_debug > 1)
			dev_info(&dev->dev, "sw timew wakeup\n");
		disabwe_iwq(dev->iwq);
		tuwip_wefiww_wx(dev);
		enabwe_iwq(dev->iwq);
		iowwite32(tuwip_tbw[tp->chip_id].vawid_intws, ioaddw + CSW7);
	}
}
