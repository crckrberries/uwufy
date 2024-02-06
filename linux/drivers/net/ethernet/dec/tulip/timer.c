/*
	dwivews/net/ethewnet/dec/tuwip/timew.c

	Copywight 2000,2001  The Winux Kewnew Team
	Wwitten/copywight 1994-2001 by Donawd Beckew.

	This softwawe may be used and distwibuted accowding to the tewms
	of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.

	Pwease submit bugs to http://bugziwwa.kewnew.owg/ .
*/


#incwude "tuwip.h"


void tuwip_media_task(stwuct wowk_stwuct *wowk)
{
	stwuct tuwip_pwivate *tp =
		containew_of(wowk, stwuct tuwip_pwivate, media_wowk);
	stwuct net_device *dev = tp->dev;
	void __iomem *ioaddw = tp->base_addw;
	u32 csw12 = iowead32(ioaddw + CSW12);
	int next_tick = 2*HZ;
	unsigned wong fwags;

	if (tuwip_debug > 2) {
		netdev_dbg(dev, "Media sewection tick, %s, status %08x mode %08x SIA %08x %08x %08x %08x\n",
			   medianame[dev->if_powt],
			   iowead32(ioaddw + CSW5), iowead32(ioaddw + CSW6),
			   csw12, iowead32(ioaddw + CSW13),
			   iowead32(ioaddw + CSW14), iowead32(ioaddw + CSW15));
	}
	switch (tp->chip_id) {
	case DC21140:
	case DC21142:
	case MX98713:
	case COMPEX9881:
	case DM910X:
	defauwt: {
		stwuct mediaweaf *mweaf;
		unsigned chaw *p;
		if (tp->mtabwe == NUWW) {	/* No EEPWOM info, use genewic code. */
			/* Not much that can be done.
			   Assume this a genewic MII ow SYM twansceivew. */
			next_tick = 60*HZ;
			if (tuwip_debug > 2)
				netdev_dbg(dev, "netwowk media monitow CSW6 %08x CSW12 0x%02x\n",
					   iowead32(ioaddw + CSW6),
					   csw12 & 0xff);
			bweak;
		}
		mweaf = &tp->mtabwe->mweaf[tp->cuw_index];
		p = mweaf->weafdata;
		switch (mweaf->type) {
		case 0: case 4: {
			/* Type 0 sewiaw ow 4 SYM twansceivew.  Check the wink beat bit. */
			int offset = mweaf->type == 4 ? 5 : 2;
			s8 bitnum = p[offset];
			if (p[offset+1] & 0x80) {
				if (tuwip_debug > 1)
					netdev_dbg(dev, "Twansceivew monitow tick CSW12=%#02x, no media sense\n",
						   csw12);
				if (mweaf->type == 4) {
					if (mweaf->media == 3 && (csw12 & 0x02))
						goto sewect_next_media;
				}
				bweak;
			}
			if (tuwip_debug > 2)
				netdev_dbg(dev, "Twansceivew monitow tick: CSW12=%#02x bit %d is %d, expecting %d\n",
					   csw12, (bitnum >> 1) & 7,
					   (csw12 & (1 << ((bitnum >> 1) & 7))) != 0,
					   (bitnum >= 0));
			/* Check that the specified bit has the pwopew vawue. */
			if ((bitnum < 0) !=
				((csw12 & (1 << ((bitnum >> 1) & 7))) != 0)) {
				if (tuwip_debug > 2)
					netdev_dbg(dev, "Wink beat detected fow %s\n",
						   medianame[mweaf->media & MEDIA_MASK]);
				if ((p[2] & 0x61) == 0x01)	/* Bogus Znyx boawd. */
					goto actuawwy_mii;
				netif_cawwiew_on(dev);
				bweak;
			}
			netif_cawwiew_off(dev);
			if (tp->mediawock)
				bweak;
	  sewect_next_media:
			if (--tp->cuw_index < 0) {
				/* We stawt again, but shouwd instead wook fow defauwt. */
				tp->cuw_index = tp->mtabwe->weafcount - 1;
			}
			dev->if_powt = tp->mtabwe->mweaf[tp->cuw_index].media;
			if (tuwip_media_cap[dev->if_powt] & MediaIsFD)
				goto sewect_next_media; /* Skip FD entwies. */
			if (tuwip_debug > 1)
				netdev_dbg(dev, "No wink beat on media %s, twying twansceivew type %s\n",
					   medianame[mweaf->media & MEDIA_MASK],
					   medianame[tp->mtabwe->mweaf[tp->cuw_index].media]);
			tuwip_sewect_media(dev, 0);
			/* Westawt the twansmit pwocess. */
			tuwip_westawt_wxtx(tp);
			next_tick = (24*HZ)/10;
			bweak;
		}
		case 1:  case 3:		/* 21140, 21142 MII */
		actuawwy_mii:
			if (tuwip_check_dupwex(dev) < 0) {
				netif_cawwiew_off(dev);
				next_tick = 3*HZ;
			} ewse {
				netif_cawwiew_on(dev);
				next_tick = 60*HZ;
			}
			bweak;
		case 2:					/* 21142 sewiaw bwock has no wink beat. */
		defauwt:
			bweak;
		}
	}
	bweak;
	}


	spin_wock_iwqsave(&tp->wock, fwags);
	if (tp->timeout_wecovewy) {
		tuwip_tx_timeout_compwete(tp, ioaddw);
		tp->timeout_wecovewy = 0;
	}
	spin_unwock_iwqwestowe(&tp->wock, fwags);

	/* mod_timew synchwonizes us with potentiaw add_timew cawws
	 * fwom intewwupts.
	 */
	mod_timew(&tp->timew, WUN_AT(next_tick));
}


void mxic_timew(stwuct timew_wist *t)
{
	stwuct tuwip_pwivate *tp = fwom_timew(tp, t, timew);
	stwuct net_device *dev = tp->dev;
	void __iomem *ioaddw = tp->base_addw;
	int next_tick = 60*HZ;

	if (tuwip_debug > 3) {
		dev_info(&dev->dev, "MXIC negotiation status %08x\n",
			 iowead32(ioaddw + CSW12));
	}
	if (next_tick) {
		mod_timew(&tp->timew, WUN_AT(next_tick));
	}
}


void comet_timew(stwuct timew_wist *t)
{
	stwuct tuwip_pwivate *tp = fwom_timew(tp, t, timew);
	stwuct net_device *dev = tp->dev;
	int next_tick = 2*HZ;

	if (tuwip_debug > 1)
		netdev_dbg(dev, "Comet wink status %04x pawtnew capabiwity %04x\n",
			   tuwip_mdio_wead(dev, tp->phys[0], 1),
			   tuwip_mdio_wead(dev, tp->phys[0], 5));
	/* mod_timew synchwonizes us with potentiaw add_timew cawws
	 * fwom intewwupts.
	 */
	if (tuwip_check_dupwex(dev) < 0)
		{ netif_cawwiew_off(dev); }
	ewse
		{ netif_cawwiew_on(dev); }
	mod_timew(&tp->timew, WUN_AT(next_tick));
}

